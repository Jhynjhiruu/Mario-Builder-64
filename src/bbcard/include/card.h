#ifndef __CARD_H__
#define __CARD_H__

#include <PR/os_bbfs.h>

typedef s32 FIL;
typedef OSBbDirEnt FILINFO;
typedef OSBbFs FATFS;

typedef char TCHAR;

typedef s32 FRESULT;
#define FR_OK (0)
#define FR_NO_FILE (BBFS_ERR_ENTRY)

#define f_mount(fs, path, opt) osBbFInit(fs)
#define f_stat(path, stat) osBbFStat(path, stat, NULL, 0)

int cart_init(void);

#endif