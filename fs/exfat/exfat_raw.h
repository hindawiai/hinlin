<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2012-2013 Samsung Electronics Co., Ltd.
 */

#अगर_अघोषित _EXFAT_RAW_H
#घोषणा _EXFAT_RAW_H

#समावेश <linux/types.h>

#घोषणा BOOT_SIGNATURE		0xAA55
#घोषणा EXBOOT_SIGNATURE	0xAA550000
#घोषणा STR_EXFAT		"EXFAT   "	/* size should be 8 */

#घोषणा EXFAT_MAX_खाता_LEN	255

#घोषणा VOLUME_सूचीTY		0x0002
#घोषणा MEDIA_FAILURE		0x0004

#घोषणा EXFAT_खातापूर्ण_CLUSTER	0xFFFFFFFFu
#घोषणा EXFAT_BAD_CLUSTER	0xFFFFFFF7u
#घोषणा EXFAT_FREE_CLUSTER	0
/* Cluster 0, 1 are reserved, the first cluster is 2 in the cluster heap. */
#घोषणा EXFAT_RESERVED_CLUSTERS	2
#घोषणा EXFAT_FIRST_CLUSTER	2
#घोषणा EXFAT_DATA_CLUSTER_COUNT(sbi)	\
	((sbi)->num_clusters - EXFAT_RESERVED_CLUSTERS)

/* AllocationPossible and NoFatChain field in GeneralSecondaryFlags Field */
#घोषणा ALLOC_FAT_CHAIN		0x01
#घोषणा ALLOC_NO_FAT_CHAIN	0x03

#घोषणा DENTRY_SIZE		32 /* directory entry size */
#घोषणा DENTRY_SIZE_BITS	5
/* exFAT allows 8388608(256MB) directory entries */
#घोषणा MAX_EXFAT_DENTRIES	8388608

/* dentry types */
#घोषणा EXFAT_UNUSED		0x00	/* end of directory */
#घोषणा EXFAT_DELETE		(~0x80)
#घोषणा IS_EXFAT_DELETED(x)	((x) < 0x80) /* deleted file (0x01~0x7F) */
#घोषणा EXFAT_INVAL		0x80	/* invalid value */
#घोषणा EXFAT_BITMAP		0x81	/* allocation biपंचांगap */
#घोषणा EXFAT_UPCASE		0x82	/* upहाल table */
#घोषणा EXFAT_VOLUME		0x83	/* volume label */
#घोषणा EXFAT_खाता		0x85	/* file or dir */
#घोषणा EXFAT_GUID		0xA0
#घोषणा EXFAT_PADDING		0xA1
#घोषणा EXFAT_ACLTAB		0xA2
#घोषणा EXFAT_STREAM		0xC0	/* stream entry */
#घोषणा EXFAT_NAME		0xC1	/* file name entry */
#घोषणा EXFAT_ACL		0xC2	/* stream entry */

#घोषणा IS_EXFAT_CRITICAL_PRI(x)	(x < 0xA0)
#घोषणा IS_EXFAT_BENIGN_PRI(x)		(x < 0xC0)
#घोषणा IS_EXFAT_CRITICAL_SEC(x)	(x < 0xE0)

/* checksum types */
#घोषणा CS_सूची_ENTRY		0
#घोषणा CS_BOOT_SECTOR		1
#घोषणा CS_DEFAULT		2

/* file attributes */
#घोषणा ATTR_READONLY		0x0001
#घोषणा ATTR_HIDDEN		0x0002
#घोषणा ATTR_SYSTEM		0x0004
#घोषणा ATTR_VOLUME		0x0008
#घोषणा ATTR_SUBसूची		0x0010
#घोषणा ATTR_ARCHIVE		0x0020

#घोषणा ATTR_RWMASK		(ATTR_HIDDEN | ATTR_SYSTEM | ATTR_VOLUME | \
				 ATTR_SUBसूची | ATTR_ARCHIVE)

#घोषणा BOOTSEC_JUMP_BOOT_LEN		3
#घोषणा BOOTSEC_FS_NAME_LEN		8
#घोषणा BOOTSEC_OLDBPB_LEN		53

#घोषणा EXFAT_खाता_NAME_LEN		15

#घोषणा EXFAT_MIN_SECT_SIZE_BITS		9
#घोषणा EXFAT_MAX_SECT_SIZE_BITS		12
#घोषणा EXFAT_MAX_SECT_PER_CLUS_BITS(x)		(25 - (x)->sect_size_bits)

/* EXFAT: Main and Backup Boot Sector (512 bytes) */
काष्ठा boot_sector अणु
	__u8	jmp_boot[BOOTSEC_JUMP_BOOT_LEN];
	__u8	fs_name[BOOTSEC_FS_NAME_LEN];
	__u8	must_be_zero[BOOTSEC_OLDBPB_LEN];
	__le64	partition_offset;
	__le64	vol_length;
	__le32	fat_offset;
	__le32	fat_length;
	__le32	clu_offset;
	__le32	clu_count;
	__le32	root_cluster;
	__le32	vol_serial;
	__u8	fs_revision[2];
	__le16	vol_flags;
	__u8	sect_size_bits;
	__u8	sect_per_clus_bits;
	__u8	num_fats;
	__u8	drv_sel;
	__u8	percent_in_use;
	__u8	reserved[7];
	__u8	boot_code[390];
	__le16	signature;
पूर्ण __packed;

काष्ठा exfat_dentry अणु
	__u8 type;
	जोड़ अणु
		काष्ठा अणु
			__u8 num_ext;
			__le16 checksum;
			__le16 attr;
			__le16 reserved1;
			__le16 create_समय;
			__le16 create_date;
			__le16 modअगरy_समय;
			__le16 modअगरy_date;
			__le16 access_समय;
			__le16 access_date;
			__u8 create_समय_cs;
			__u8 modअगरy_समय_cs;
			__u8 create_tz;
			__u8 modअगरy_tz;
			__u8 access_tz;
			__u8 reserved2[7];
		पूर्ण __packed file; /* file directory entry */
		काष्ठा अणु
			__u8 flags;
			__u8 reserved1;
			__u8 name_len;
			__le16 name_hash;
			__le16 reserved2;
			__le64 valid_size;
			__le32 reserved3;
			__le32 start_clu;
			__le64 size;
		पूर्ण __packed stream; /* stream extension directory entry */
		काष्ठा अणु
			__u8 flags;
			__le16 unicode_0_14[EXFAT_खाता_NAME_LEN];
		पूर्ण __packed name; /* file name directory entry */
		काष्ठा अणु
			__u8 flags;
			__u8 reserved[18];
			__le32 start_clu;
			__le64 size;
		पूर्ण __packed biपंचांगap; /* allocation biपंचांगap directory entry */
		काष्ठा अणु
			__u8 reserved1[3];
			__le32 checksum;
			__u8 reserved2[12];
			__le32 start_clu;
			__le64 size;
		पूर्ण __packed upहाल; /* up-हाल table directory entry */
	पूर्ण __packed dentry;
पूर्ण __packed;

#घोषणा EXFAT_TZ_VALID		(1 << 7)

/* Jan 1 GMT 00:00:00 1980 */
#घोषणा EXFAT_MIN_TIMESTAMP_SECS    315532800LL
/* Dec 31 GMT 23:59:59 2107 */
#घोषणा EXFAT_MAX_TIMESTAMP_SECS    4354819199LL

#पूर्ण_अगर /* !_EXFAT_RAW_H */
