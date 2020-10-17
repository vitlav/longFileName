#include <stdio.h>
#include <errno.h>
#include <sys/vfs.h>
#include <string.h>

#define AFFS_SUPER_MAGIC      0xADFF
#define EFS_SUPER_MAGIC       0x00414A53
#define EXT_SUPER_MAGIC       0x137D
#define EXT2_OLD_SUPER_MAGIC  0xEF51
#define EXT2_SUPER_MAGIC      0xEF53
#define HPFS_SUPER_MAGIC      0xF995E849
#define ISOFS_SUPER_MAGIC     0x9660
#define MINIX_SUPER_MAGIC     0x137F 
#define MINIX_SUPER_MAGIC2    0x138F
#define MINIX2_SUPER_MAGIC    0x2468
#define MINIX2_SUPER_MAGIC2   0x2478
#define MSDOS_SUPER_MAGIC     0x4d44
#define NCP_SUPER_MAGIC       0x564c
#define NFS_SUPER_MAGIC       0x6969
#define PROC_SUPER_MAGIC      0x9fa0
#define SMB_SUPER_MAGIC       0x517B
#define XENIX_SUPER_MAGIC     0x012FF7B4
#define SYSV4_SUPER_MAGIC     0x012FF7B5
#define SYSV2_SUPER_MAGIC     0x012FF7B6
#define COH_SUPER_MAGIC       0x012FF7B7
#define UFS_MAGIC             0x00011954
#define XFS_SUPER_MAGIC       0x58465342
#define _XIAFS_SUPER_MAGIC    0x012FD16D

const char *fsType2str(long type) {
	static struct fsname {
		long type;
		const char *name;
	} table[] = {
		{ AFFS_SUPER_MAGIC, "AFFS" },
		{ COH_SUPER_MAGIC, "COH" },
		{ EXT2_OLD_SUPER_MAGIC, "OLD EXT2" },
		{ EXT2_SUPER_MAGIC, "EXT2" },
		{ HPFS_SUPER_MAGIC, "HPFS" },
		{ ISOFS_SUPER_MAGIC, "ISOFS" },
		{ MINIX2_SUPER_MAGIC, "MINIX V2" },
		{ MINIX2_SUPER_MAGIC2, "MINIX V2 30 char" },
		{ MINIX_SUPER_MAGIC, "MINIX" },
		{ MINIX_SUPER_MAGIC2, "MINIX 30 char" },
		{ MSDOS_SUPER_MAGIC, "MSDOS" },
		{ NCP_SUPER_MAGIC, "NCP" },
		{ NFS_SUPER_MAGIC, "NFS" },
		{ PROC_SUPER_MAGIC, "PROC" },
		{ SMB_SUPER_MAGIC, "SMB" },
		{ SYSV2_SUPER_MAGIC, "SYSV2" },
		{ SYSV4_SUPER_MAGIC, "SYSV4" },
		{ UFS_MAGIC, "UFS" },
		{ XENIX_SUPER_MAGIC, "XENIX" },
		{ _XIAFS_SUPER_MAGIC, "XIAFS" },
		{ 0, NULL },
	};
	static char unknown[100];
	int i;

	for (i = 0; table[i].type != 0; i++)
		if (table[i].type == type)
			return table[i].name;

	sprintf(unknown, "unknown type: %#lx", type);
	return unknown;
}

int main(int argc, char *argv[]) {
    struct statfs fs;
    char *file = argv[1];
    int result = statfs(file, & fs);
    if (result != 0) {
        fprintf(stderr, "File: %s, An error occured: %s\n",
                argv[1], strerror(errno));
        return errno;
    }
    printf("tf_type: %s\n", fsType2str(fs.f_type));
    printf("tf_namelen: %ld\n", fs.f_namelen);
    return 0;
}