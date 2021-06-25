<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Simple zone file प्रणाली क्रम zoned block devices.
 *
 * Copyright (C) 2019 Western Digital Corporation or its affiliates.
 */
#अगर_अघोषित __ZONEFS_H__
#घोषणा __ZONEFS_H__

#समावेश <linux/fs.h>
#समावेश <linux/magic.h>
#समावेश <linux/uuid.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rwsem.h>

/*
 * Maximum length of file names: this only needs to be large enough to fit
 * the zone group directory names and a decimal zone number क्रम file names.
 * 16 अक्षरacters is plenty.
 */
#घोषणा ZONEFS_NAME_MAX		16

/*
 * Zone types: ZONEFS_ZTYPE_SEQ is used क्रम all sequential zone types
 * defined in linux/blkzoned.h, that is, BLK_ZONE_TYPE_SEQWRITE_REQ and
 * BLK_ZONE_TYPE_SEQWRITE_PREF.
 */
क्रमागत zonefs_ztype अणु
	ZONEFS_ZTYPE_CNV,
	ZONEFS_ZTYPE_SEQ,
	ZONEFS_ZTYPE_MAX,
पूर्ण;

अटल अंतरभूत क्रमागत zonefs_ztype zonefs_zone_type(काष्ठा blk_zone *zone)
अणु
	अगर (zone->type == BLK_ZONE_TYPE_CONVENTIONAL)
		वापस ZONEFS_ZTYPE_CNV;
	वापस ZONEFS_ZTYPE_SEQ;
पूर्ण

#घोषणा ZONEFS_ZONE_OPEN	(1 << 0)

/*
 * In-memory inode data.
 */
काष्ठा zonefs_inode_info अणु
	काष्ठा inode		i_vnode;

	/* File zone type */
	क्रमागत zonefs_ztype	i_ztype;

	/* File zone start sector (512B unit) */
	sector_t		i_zsector;

	/* File zone ग_लिखो poपूर्णांकer position (sequential zones only) */
	loff_t			i_wpoffset;

	/* File maximum size */
	loff_t			i_max_size;

	/* File zone size */
	loff_t			i_zone_size;

	/*
	 * To serialise fully against both syscall and mmap based IO and
	 * sequential file truncation, two locks are used. For serializing
	 * zonefs_seq_file_truncate() against zonefs_iomap_begin(), that is,
	 * file truncate operations against block mapping, i_truncate_mutex is
	 * used. i_truncate_mutex also protects against concurrent accesses
	 * and changes to the inode निजी data, and in particular changes to
	 * a sequential file size on completion of direct IO ग_लिखोs.
	 * Serialization of mmap पढ़ो IOs with truncate and syscall IO
	 * operations is करोne with i_mmap_sem in addition to i_truncate_mutex.
	 * Only zonefs_seq_file_truncate() takes both lock (i_mmap_sem first,
	 * i_truncate_mutex second).
	 */
	काष्ठा mutex		i_truncate_mutex;
	काष्ठा rw_semaphore	i_mmap_sem;

	/* guarded by i_truncate_mutex */
	अचिन्हित पूर्णांक		i_wr_refcnt;
	अचिन्हित पूर्णांक		i_flags;
पूर्ण;

अटल अंतरभूत काष्ठा zonefs_inode_info *ZONEFS_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा zonefs_inode_info, i_vnode);
पूर्ण

/*
 * On-disk super block (block 0).
 */
#घोषणा ZONEFS_LABEL_LEN	64
#घोषणा ZONEFS_UUID_SIZE	16
#घोषणा ZONEFS_SUPER_SIZE	4096

काष्ठा zonefs_super अणु

	/* Magic number */
	__le32		s_magic;

	/* Checksum */
	__le32		s_crc;

	/* Volume label */
	अक्षर		s_label[ZONEFS_LABEL_LEN];

	/* 128-bit uuid */
	__u8		s_uuid[ZONEFS_UUID_SIZE];

	/* Features */
	__le64		s_features;

	/* UID/GID to use क्रम files */
	__le32		s_uid;
	__le32		s_gid;

	/* File permissions */
	__le32		s_perm;

	/* Padding to ZONEFS_SUPER_SIZE bytes */
	__u8		s_reserved[3988];

पूर्ण __packed;

/*
 * Feature flags: specअगरied in the s_features field of the on-disk super
 * block काष्ठा zonefs_super and in-memory in the s_feartures field of
 * काष्ठा zonefs_sb_info.
 */
क्रमागत zonefs_features अणु
	/*
	 * Aggregate contiguous conventional zones पूर्णांकo a single file.
	 */
	ZONEFS_F_AGGRCNV = 1ULL << 0,
	/*
	 * Use super block specअगरied UID क्रम files instead of शेष 0.
	 */
	ZONEFS_F_UID = 1ULL << 1,
	/*
	 * Use super block specअगरied GID क्रम files instead of शेष 0.
	 */
	ZONEFS_F_GID = 1ULL << 2,
	/*
	 * Use super block specअगरied file permissions instead of शेष 640.
	 */
	ZONEFS_F_PERM = 1ULL << 3,
पूर्ण;

#घोषणा ZONEFS_F_DEFINED_FEATURES \
	(ZONEFS_F_AGGRCNV | ZONEFS_F_UID | ZONEFS_F_GID | ZONEFS_F_PERM)

/*
 * Mount options क्रम zone ग_लिखो poपूर्णांकer error handling.
 */
#घोषणा ZONEFS_MNTOPT_ERRORS_RO		(1 << 0) /* Make zone file पढ़ोonly */
#घोषणा ZONEFS_MNTOPT_ERRORS_ZRO	(1 << 1) /* Make zone file offline */
#घोषणा ZONEFS_MNTOPT_ERRORS_ZOL	(1 << 2) /* Make zone file offline */
#घोषणा ZONEFS_MNTOPT_ERRORS_REPAIR	(1 << 3) /* Remount पढ़ो-only */
#घोषणा ZONEFS_MNTOPT_ERRORS_MASK	\
	(ZONEFS_MNTOPT_ERRORS_RO | ZONEFS_MNTOPT_ERRORS_ZRO | \
	 ZONEFS_MNTOPT_ERRORS_ZOL | ZONEFS_MNTOPT_ERRORS_REPAIR)
#घोषणा ZONEFS_MNTOPT_EXPLICIT_OPEN	(1 << 4) /* Explicit खोलो/बंद of zones on खोलो/बंद */

/*
 * In-memory Super block inक्रमmation.
 */
काष्ठा zonefs_sb_info अणु

	अचिन्हित दीर्घ		s_mount_opts;

	spinlock_t		s_lock;

	अचिन्हित दीर्घ दीर्घ	s_features;
	kuid_t			s_uid;
	kgid_t			s_gid;
	umode_t			s_perm;
	uuid_t			s_uuid;
	अचिन्हित पूर्णांक		s_zone_sectors_shअगरt;

	अचिन्हित पूर्णांक		s_nr_files[ZONEFS_ZTYPE_MAX];

	loff_t			s_blocks;
	loff_t			s_used_blocks;

	अचिन्हित पूर्णांक		s_max_खोलो_zones;
	atomic_t		s_खोलो_zones;
पूर्ण;

अटल अंतरभूत काष्ठा zonefs_sb_info *ZONEFS_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

#घोषणा zonefs_info(sb, क्रमmat, args...)	\
	pr_info("zonefs (%s): " क्रमmat, sb->s_id, ## args)
#घोषणा zonefs_err(sb, क्रमmat, args...)		\
	pr_err("zonefs (%s) ERROR: " क्रमmat, sb->s_id, ## args)
#घोषणा zonefs_warn(sb, क्रमmat, args...)	\
	pr_warn("zonefs (%s) WARNING: " क्रमmat, sb->s_id, ## args)

#पूर्ण_अगर
