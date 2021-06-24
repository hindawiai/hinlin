<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_MSDOS_FS_H
#घोषणा _UAPI_LINUX_MSDOS_FS_H

#समावेश <linux/types.h>
#समावेश <linux/magic.h>
#समावेश <यंत्र/byteorder.h>

/*
 * The MS-DOS fileप्रणाली स्थिरants/काष्ठाures
 */

#अगर_अघोषित SECTOR_SIZE
#घोषणा SECTOR_SIZE	512		/* sector size (bytes) */
#पूर्ण_अगर
#घोषणा SECTOR_BITS	9		/* log2(SECTOR_SIZE) */
#घोषणा MSDOS_DPB	(MSDOS_DPS)	/* dir entries per block */
#घोषणा MSDOS_DPB_BITS	4		/* log2(MSDOS_DPB) */
#घोषणा MSDOS_DPS	(SECTOR_SIZE / माप(काष्ठा msकरोs_dir_entry))
#घोषणा MSDOS_DPS_BITS	4		/* log2(MSDOS_DPS) */
#घोषणा MSDOS_LONGNAME	256		/* maximum name length */
#घोषणा CF_LE_W(v)	le16_to_cpu(v)
#घोषणा CF_LE_L(v)	le32_to_cpu(v)
#घोषणा CT_LE_W(v)	cpu_to_le16(v)
#घोषणा CT_LE_L(v)	cpu_to_le32(v)

#घोषणा MSDOS_ROOT_INO	 1	/* The root inode number */
#घोषणा MSDOS_FSINFO_INO 2	/* Used क्रम managing the FSINFO block */

#घोषणा MSDOS_सूची_BITS	5	/* log2(माप(काष्ठा msकरोs_dir_entry)) */

/* directory limit */
#घोषणा FAT_MAX_सूची_ENTRIES	(65536)
#घोषणा FAT_MAX_सूची_SIZE	(FAT_MAX_सूची_ENTRIES << MSDOS_सूची_BITS)

#घोषणा ATTR_NONE	0	/* no attribute bits */
#घोषणा ATTR_RO		1	/* पढ़ो-only */
#घोषणा ATTR_HIDDEN	2	/* hidden */
#घोषणा ATTR_SYS	4	/* प्रणाली */
#घोषणा ATTR_VOLUME	8	/* volume label */
#घोषणा ATTR_सूची	16	/* directory */
#घोषणा ATTR_ARCH	32	/* archived */

/* attribute bits that are copied "as is" */
#घोषणा ATTR_UNUSED	(ATTR_VOLUME | ATTR_ARCH | ATTR_SYS | ATTR_HIDDEN)
/* bits that are used by the Winकरोws 95/Winकरोws NT extended FAT */
#घोषणा ATTR_EXT	(ATTR_RO | ATTR_HIDDEN | ATTR_SYS | ATTR_VOLUME)

#घोषणा CASE_LOWER_BASE	8	/* base is lower हाल */
#घोषणा CASE_LOWER_EXT	16	/* extension is lower हाल */

#घोषणा DELETED_FLAG	0xe5	/* marks file as deleted when in name[0] */
#घोषणा IS_FREE(n)	(!*(n) || *(n) == DELETED_FLAG)

#घोषणा FAT_LFN_LEN	255	/* maximum दीर्घ name length */
#घोषणा MSDOS_NAME	11	/* maximum name length */
#घोषणा MSDOS_SLOTS	21	/* max # of slots क्रम लघु and दीर्घ names */
#घोषणा MSDOS_DOT	".          "	/* ".", padded to MSDOS_NAME अक्षरs */
#घोषणा MSDOS_DOTDOT	"..         "	/* "..", padded to MSDOS_NAME अक्षरs */

/* start of data cluster's entry (number of reserved clusters) */
#घोषणा FAT_START_ENT	2

/* maximum number of clusters */
#घोषणा MAX_FAT12	0xFF4
#घोषणा MAX_FAT16	0xFFF4
#घोषणा MAX_FAT32	0x0FFFFFF6

/* bad cluster mark */
#घोषणा BAD_FAT12	0xFF7
#घोषणा BAD_FAT16	0xFFF7
#घोषणा BAD_FAT32	0x0FFFFFF7

/* standard खातापूर्ण */
#घोषणा खातापूर्ण_FAT12	0xFFF
#घोषणा खातापूर्ण_FAT16	0xFFFF
#घोषणा खातापूर्ण_FAT32	0x0FFFFFFF

#घोषणा FAT_ENT_FREE	(0)
#घोषणा FAT_ENT_BAD	(BAD_FAT32)
#घोषणा FAT_ENT_खातापूर्ण	(खातापूर्ण_FAT32)

#घोषणा FAT_FSINFO_SIG1	0x41615252
#घोषणा FAT_FSINFO_SIG2	0x61417272
#घोषणा IS_FSINFO(x)	(le32_to_cpu((x)->signature1) == FAT_FSINFO_SIG1 \
			 && le32_to_cpu((x)->signature2) == FAT_FSINFO_SIG2)

#घोषणा FAT_STATE_सूचीTY 0x01

काष्ठा __fat_dirent अणु
	दीर्घ		d_ino;
	__kernel_off_t	d_off;
	अचिन्हित लघु	d_reclen;
	अक्षर		d_name[256]; /* We must not include सीमा.स! */
पूर्ण;

/*
 * ioctl commands
 */
#घोषणा VFAT_IOCTL_READसूची_BOTH		_IOR('r', 1, काष्ठा __fat_dirent[2])
#घोषणा VFAT_IOCTL_READसूची_SHORT	_IOR('r', 2, काष्ठा __fat_dirent[2])
/* <linux/videotext.h> has used 0x72 ('r') in collision, so skip a few */
#घोषणा FAT_IOCTL_GET_ATTRIBUTES	_IOR('r', 0x10, __u32)
#घोषणा FAT_IOCTL_SET_ATTRIBUTES	_IOW('r', 0x11, __u32)
/*Android kernel has used 0x12, so we use 0x13*/
#घोषणा FAT_IOCTL_GET_VOLUME_ID		_IOR('r', 0x13, __u32)

काष्ठा fat_boot_sector अणु
	__u8	ignored[3];	/* Boot strap लघु or near jump */
	__u8	प्रणाली_id[8];	/* Name - can be used to special हाल
				   partition manager volumes */
	__u8	sector_size[2];	/* bytes per logical sector */
	__u8	sec_per_clus;	/* sectors/cluster */
	__le16	reserved;	/* reserved sectors */
	__u8	fats;		/* number of FATs */
	__u8	dir_entries[2];	/* root directory entries */
	__u8	sectors[2];	/* number of sectors */
	__u8	media;		/* media code */
	__le16	fat_length;	/* sectors/FAT */
	__le16	secs_track;	/* sectors per track */
	__le16	heads;		/* number of heads */
	__le32	hidden;		/* hidden sectors (unused) */
	__le32	total_sect;	/* number of sectors (अगर sectors == 0) */

	जोड़ अणु
		काष्ठा अणु
			/*  Extended BPB Fields क्रम FAT16 */
			__u8	drive_number;	/* Physical drive number */
			__u8	state;		/* unकरोcumented, but used
						   क्रम mount state. */
			__u8	signature;  /* extended boot signature */
			__u8	vol_id[4];	/* volume ID */
			__u8	vol_label[MSDOS_NAME];	/* volume label */
			__u8	fs_type[8];		/* file प्रणाली type */
			/* other fields are not added here */
		पूर्ण fat16;

		काष्ठा अणु
			/* only used by FAT32 */
			__le32	length;		/* sectors/FAT */
			__le16	flags;		/* bit 8: fat mirroring,
						   low 4: active fat */
			__u8	version[2];	/* major, minor fileप्रणाली
						   version */
			__le32	root_cluster;	/* first cluster in
						   root directory */
			__le16	info_sector;	/* fileप्रणाली info sector */
			__le16	backup_boot;	/* backup boot sector */
			__le16	reserved2[6];	/* Unused */
			/* Extended BPB Fields क्रम FAT32 */
			__u8	drive_number;   /* Physical drive number */
			__u8    state;       	/* unकरोcumented, but used
						   क्रम mount state. */
			__u8	signature;  /* extended boot signature */
			__u8	vol_id[4];	/* volume ID */
			__u8	vol_label[MSDOS_NAME];	/* volume label */
			__u8	fs_type[8];		/* file प्रणाली type */
			/* other fields are not added here */
		पूर्ण fat32;
	पूर्ण;
पूर्ण;

काष्ठा fat_boot_fsinfo अणु
	__le32   signature1;	/* 0x41615252L */
	__le32   reserved1[120];	/* Nothing as far as I can tell */
	__le32   signature2;	/* 0x61417272L */
	__le32   मुक्त_clusters;	/* Free cluster count.  -1 अगर unknown */
	__le32   next_cluster;	/* Most recently allocated cluster */
	__le32   reserved2[4];
पूर्ण;

काष्ठा msकरोs_dir_entry अणु
	__u8	name[MSDOS_NAME];/* name and extension */
	__u8	attr;		/* attribute bits */
	__u8    lहाल;		/* Case क्रम base and extension */
	__u8	स_समय_cs;	/* Creation समय, centiseconds (0-199) */
	__le16	स_समय;		/* Creation समय */
	__le16	cdate;		/* Creation date */
	__le16	adate;		/* Last access date */
	__le16	starthi;	/* High 16 bits of cluster in FAT32 */
	__le16	समय,date,start;/* समय, date and first cluster */
	__le32	size;		/* file size (in bytes) */
पूर्ण;

/* Up to 13 अक्षरacters of the name */
काष्ठा msकरोs_dir_slot अणु
	__u8    id;		/* sequence number क्रम slot */
	__u8    name0_4[10];	/* first 5 अक्षरacters in name */
	__u8    attr;		/* attribute byte */
	__u8    reserved;	/* always 0 */
	__u8    alias_checksum;	/* checksum क्रम 8.3 alias */
	__u8    name5_10[12];	/* 6 more अक्षरacters in name */
	__le16   start;		/* starting cluster number, 0 in दीर्घ slots */
	__u8    name11_12[4];	/* last 2 अक्षरacters in name */
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_MSDOS_FS_H */
