<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * volume.h - Defines क्रम volume काष्ठाures in NTFS Linux kernel driver. Part
 *	      of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2006 Anton Altaparmakov
 * Copyright (c) 2002 Riअक्षरd Russon
 */

#अगर_अघोषित _LINUX_NTFS_VOLUME_H
#घोषणा _LINUX_NTFS_VOLUME_H

#समावेश <linux/rwsem.h>
#समावेश <linux/uidgid.h>

#समावेश "types.h"
#समावेश "layout.h"

/*
 * The NTFS in memory super block काष्ठाure.
 */
प्रकार काष्ठा अणु
	/*
	 * FIXME: Reorder to have commonly used together element within the
	 * same cache line, aiming at a cache line size of 32 bytes. Aim क्रम
	 * 64 bytes क्रम less commonly used together elements. Put most commonly
	 * used elements to front of काष्ठाure. Obviously करो this only when the
	 * काष्ठाure has stabilized... (AIA)
	 */
	/* Device specअगरics. */
	काष्ठा super_block *sb;		/* Poपूर्णांकer back to the super_block. */
	LCN nr_blocks;			/* Number of sb->s_blocksize bytes
					   sized blocks on the device. */
	/* Configuration provided by user at mount समय. */
	अचिन्हित दीर्घ flags;		/* Miscellaneous flags, see below. */
	kuid_t uid;			/* uid that files will be mounted as. */
	kgid_t gid;			/* gid that files will be mounted as. */
	umode_t fmask;			/* The mask क्रम file permissions. */
	umode_t dmask;			/* The mask क्रम directory
					   permissions. */
	u8 mft_zone_multiplier;		/* Initial mft zone multiplier. */
	u8 on_errors;			/* What to करो on fileप्रणाली errors. */
	/* NTFS bootsector provided inक्रमmation. */
	u16 sector_size;		/* in bytes */
	u8 sector_size_bits;		/* log2(sector_size) */
	u32 cluster_size;		/* in bytes */
	u32 cluster_size_mask;		/* cluster_size - 1 */
	u8 cluster_size_bits;		/* log2(cluster_size) */
	u32 mft_record_size;		/* in bytes */
	u32 mft_record_size_mask;	/* mft_record_size - 1 */
	u8 mft_record_size_bits;	/* log2(mft_record_size) */
	u32 index_record_size;		/* in bytes */
	u32 index_record_size_mask;	/* index_record_size - 1 */
	u8 index_record_size_bits;	/* log2(index_record_size) */
	LCN nr_clusters;		/* Volume size in clusters == number of
					   bits in lcn biपंचांगap. */
	LCN mft_lcn;			/* Cluster location of mft data. */
	LCN mfपंचांगirr_lcn;		/* Cluster location of copy of mft. */
	u64 serial_no;			/* The volume serial number. */
	/* Mount specअगरic NTFS inक्रमmation. */
	u32 upहाल_len;			/* Number of entries in upहाल[]. */
	ntfsअक्षर *upहाल;		/* The upहाल table. */

	s32 attrdef_size;		/* Size of the attribute definition
					   table in bytes. */
	ATTR_DEF *attrdef;		/* Table of attribute definitions.
					   Obtained from खाता_AttrDef. */

#अगर_घोषित NTFS_RW
	/* Variables used by the cluster and mft allocators. */
	s64 mft_data_pos;		/* Mft record number at which to
					   allocate the next mft record. */
	LCN mft_zone_start;		/* First cluster of the mft zone. */
	LCN mft_zone_end;		/* First cluster beyond the mft zone. */
	LCN mft_zone_pos;		/* Current position in the mft zone. */
	LCN data1_zone_pos;		/* Current position in the first data
					   zone. */
	LCN data2_zone_pos;		/* Current position in the second data
					   zone. */
#पूर्ण_अगर /* NTFS_RW */

	काष्ठा inode *mft_ino;		/* The VFS inode of $MFT. */

	काष्ठा inode *mftbmp_ino;	/* Attribute inode क्रम $MFT/$BITMAP. */
	काष्ठा rw_semaphore mftbmp_lock; /* Lock क्रम serializing accesses to the
					    mft record biपंचांगap ($MFT/$BITMAP). */
#अगर_घोषित NTFS_RW
	काष्ठा inode *mfपंचांगirr_ino;	/* The VFS inode of $MFTMirr. */
	पूर्णांक mfपंचांगirr_size;		/* Size of mft mirror in mft records. */

	काष्ठा inode *logfile_ino;	/* The VFS inode of $LogFile. */
#पूर्ण_अगर /* NTFS_RW */

	काष्ठा inode *lcnbmp_ino;	/* The VFS inode of $Biपंचांगap. */
	काष्ठा rw_semaphore lcnbmp_lock; /* Lock क्रम serializing accesses to the
					    cluster biपंचांगap ($Biपंचांगap/$DATA). */

	काष्ठा inode *vol_ino;		/* The VFS inode of $Volume. */
	VOLUME_FLAGS vol_flags;		/* Volume flags. */
	u8 major_ver;			/* Ntfs major version of volume. */
	u8 minor_ver;			/* Ntfs minor version of volume. */

	काष्ठा inode *root_ino;		/* The VFS inode of the root
					   directory. */
	काष्ठा inode *secure_ino;	/* The VFS inode of $Secure (NTFS3.0+
					   only, otherwise शून्य). */
	काष्ठा inode *extend_ino;	/* The VFS inode of $Extend (NTFS3.0+
					   only, otherwise शून्य). */
#अगर_घोषित NTFS_RW
	/* $Quota stuff is NTFS3.0+ specअगरic.  Unused/शून्य otherwise. */
	काष्ठा inode *quota_ino;	/* The VFS inode of $Quota. */
	काष्ठा inode *quota_q_ino;	/* Attribute inode क्रम $Quota/$Q. */
	/* $UsnJrnl stuff is NTFS3.0+ specअगरic.  Unused/शून्य otherwise. */
	काष्ठा inode *usnjrnl_ino;	/* The VFS inode of $UsnJrnl. */
	काष्ठा inode *usnjrnl_max_ino;	/* Attribute inode क्रम $UsnJrnl/$Max. */
	काष्ठा inode *usnjrnl_j_ino;	/* Attribute inode क्रम $UsnJrnl/$J. */
#पूर्ण_अगर /* NTFS_RW */
	काष्ठा nls_table *nls_map;
पूर्ण ntfs_volume;

/*
 * Defined bits क्रम the flags field in the ntfs_volume काष्ठाure.
 */
प्रकार क्रमागत अणु
	NV_Errors,		/* 1: Volume has errors, prevent remount rw. */
	NV_ShowSystemFiles,	/* 1: Return प्रणाली files in ntfs_सूची_पढ़ो(). */
	NV_CaseSensitive,	/* 1: Treat file names as हाल sensitive and
				      create filenames in the POSIX namespace.
				      Otherwise be हाल insensitive but still
				      create file names in POSIX namespace. */
	NV_LogFileEmpty,	/* 1: $LogFile journal is empty. */
	NV_QuotaOutOfDate,	/* 1: $Quota is out of date. */
	NV_UsnJrnlStamped,	/* 1: $UsnJrnl has been stamped. */
	NV_SparseEnabled,	/* 1: May create sparse files. */
पूर्ण ntfs_volume_flags;

/*
 * Macro tricks to expand the NVolFoo(), NVolSetFoo(), and NVolClearFoo()
 * functions.
 */
#घोषणा DEFINE_NVOL_BIT_OPS(flag)					\
अटल अंतरभूत पूर्णांक NVol##flag(ntfs_volume *vol)		\
अणु							\
	वापस test_bit(NV_##flag, &(vol)->flags);	\
पूर्ण							\
अटल अंतरभूत व्योम NVolSet##flag(ntfs_volume *vol)	\
अणु							\
	set_bit(NV_##flag, &(vol)->flags);		\
पूर्ण							\
अटल अंतरभूत व्योम NVolClear##flag(ntfs_volume *vol)	\
अणु							\
	clear_bit(NV_##flag, &(vol)->flags);		\
पूर्ण

/* Emit the ntfs volume bitops functions. */
DEFINE_NVOL_BIT_OPS(Errors)
DEFINE_NVOL_BIT_OPS(ShowSystemFiles)
DEFINE_NVOL_BIT_OPS(CaseSensitive)
DEFINE_NVOL_BIT_OPS(LogFileEmpty)
DEFINE_NVOL_BIT_OPS(QuotaOutOfDate)
DEFINE_NVOL_BIT_OPS(UsnJrnlStamped)
DEFINE_NVOL_BIT_OPS(SparseEnabled)

#पूर्ण_अगर /* _LINUX_NTFS_VOLUME_H */
