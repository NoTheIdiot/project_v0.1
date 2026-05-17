// include files
#include <stdint.h>
#include <stddef.h>
#include <dogeio.h>
#include <dogeports.h>
#include <dogebool.h>

// ________________ATA PIO DRIVER_________________
#define ATA_PRIMARY_IO 		0x1F0
#define ATA_REG_DATA		0x00
#define ATA_SECCOUNT		0x02
#define ATA_REG_LBA0       0x03
#define ATA_REG_LBA1       0x04
#define ATA_REG_LBA2       0x05
#define ATA_REG_HDDEVSEL   0x06
#define ATA_REG_COMMAND    0x07
#define ATA_REG_STATUS     0x07

#define ATA_CMD_READ_SECTORS  0x20
#define ATA_SR_BSY  0x80
#define ATA_SR_DRQ  0x08
#define ATA_SR_ERR  0x01

// basic functions
void ata_wait_ready() {
    while (inb(ATA_PRIMARY_IO + ATA_REG_STATUS) & ATA_SR_BSY);
}

int ata_read_sector(uint32_t lba, uint8_t* buffer) {
    ata_wait_ready();
    ports_outb(ATA_PRIMARY_IO + ATA_REG_SECCOUNT, 1);
    ports_outb(ATA_PRIMARY_IO + ATA_REG_LBA0, (uint8_t)(lba));
    ports_outb(ATA_PRIMARY_IO + ATA_REG_LBA1, (uint8_t)(lba >> 8));
    ports_outb(ATA_PRIMARY_IO + ATA_REG_LBA2, (uint8_t)(lba >> 16));
   	ports_outb(ATA_PRIMARY_IO + ATA_REG_HDDEVSEL, 0xE0 | ((lba >> 24) & 0x0F));
    porst_outb(ATA_PRIMARY_IO + ATA_REG_COMMAND, ATA_CMD_READ_SECTORS);
    while (!(ports_inb(ATA_PRIMARY_IO + ATA_REG_STATUS) & ATA_SR_DRQ));
    ports_insw(ATA_PRIMARY_IO + ATA_REG_DATA, buffer, 256);
    if (ports_inb(ATA_PRIMARY_IO + ATA_REG_STATUS) & ATA_SR_ERR) return -1;
    return 0;
}

//______________________FAT16 STRUCT_________________________
#pragma pack(push, 1)
typedef struct {
    uint8_t  jump[3];
    char     oem[8];
    uint16_t bytes_per_sector;
    uint8_t  sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t  num_fats;
    uint16_t root_entries;
    uint16_t total_sectors_short;
    uint8_t  media_descriptor;
    uint16_t sectors_per_fat;
    uint16_t sectors_per_track;
    uint16_t num_heads;
    uint32_t hidden_sectors;
    uint32_t total_sectors_long;
} BootSector;

typedef struct {
    char     filename[8];
    char     ext[3];
    uint8_t  attr;
    uint8_t  reserved[10];
    uint16_t time;
    uint16_t date;
    uint16_t start_cluster;
    uint32_t file_size;
} DirEntry;
#pragma pack(pop)

//___________________FILE TABLE______________________________
typedef struct {
	int id;
	char name[13];
	uint16_t start_cluster;
	uint32_t file_size;
} FileEntry;

Bootsector g_bs;
unit32_t g_first_data_sector
uint32_t g_root_dir;
FileEntry g_file_table[256];
int g_file_count = 0;

//__________________INIT FAT16______________________________
void disk_init(uint32_t lba_start) {
	uint8_t buffer[512];
	ata_read_sector(lba_start, buffer);
	uint32_t root_dir_sectors = ((g_bs.root_entries * 32) + (g_bs.bytes_per_sector - 1)) / g_bs.bytes_per_sector;
	g_root_dir_lba = lba_start + g_bs.reserved_sectors + (g_bs.num_fats * g_bs.sectors_per_fat);
	g_first_data_sector = g_root_dir_lba + root_dir_sectors;
}

//________________OTHERS___________________________________
uint16_t disk_next_cluster(uint16_t cluster, uint32)t fat_lba {
	uint8_t buffer[512];
	ata_read_sector(fat_lba + (cluster * / g_bs.bytes_per_sector), buffer);
	uint16_t* fat = (uint16_t*)buffer;
	return fat[cluster & (g_bs.bytes_per_sector / 1)];
}

void disk_read_file(uint16_t start_cluster, uint32_t file_size, uint2_t fat_lb) {
	uint8_t buffer[512];
	uint32_t bytes_read = 0;
	uint16_t cluster = start_cluster;

	while (cluster < 0x0FFF8 && bytes_read < file_size) {
		uint32_t lba = g_first_data_sector + (cluster - 2) * g_bs.sectors_per_cluster;
		for (uint8_t s = 0; s < g_bs.sectors_per_cluster; s++) {
			ata_read_sector(lba + s, buffer);
			for (uint32_t i = 0; i < g_bs.bytes_per_sector && bytes_read < file_size; i++) {
				dogeio_print_char(buffer[i]);
				bytes_read++;
			}
		}
	}
	cluster = fat_next_cluster(cluster, fat_lba);
}

//_____________________FILE TABLE___________________________
void disk_read_file_id(int id) {
    if (id < 0 || id >= g_file_count) {
        dogeio_println("Invalid file ID");
        return;
    }
    FileEntry* fe = &g_file_table[id];
    uint32_t fat_lba = 0 + g_bs.reserved_sectors;
    dogeio_print("Reading file "); dogeio_print(fe->name); dogeio_putchar('\n');
    fat16_read_file(fe->start_cluster, fe->file_size, fat_lba);
}

void disk_read_file(const char* filename) {
    for (int i = 0; i < g_file_count; i++) {
        if (string_strcmp(g_file_table[i].name, filename) == 0) {
            disk_read_file_id(i);
            return;
        }
    }
    dogeio_println("File not found");
}
