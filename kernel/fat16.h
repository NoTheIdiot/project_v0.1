#ifndef FAT16_H
#define FAT16_h

#pragma pack(push, 1)
typedef struct BootSector;
typedef struct DirEntry;
#pragma pack(pop)

typedef struct FileEntry;

void disk_init(uint32_t lba_start);
uint16_t disk_next_cluster(uint16_t cluster, uint32_t fat_lba);
void disk_read_file_id(int id);
void disk_read_file(const char* filename);
#endif