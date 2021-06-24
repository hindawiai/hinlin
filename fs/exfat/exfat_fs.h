<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2012-2013 Samsung Electronics Co., Ltd.
 */

#अगर_अघोषित _EXFAT_FS_H
#घोषणा _EXFAT_FS_H

#समावेश <linux/fs.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/nls.h>

#घोषणा EXFAT_SUPER_MAGIC       0x2011BAB0UL
#घोषणा EXFAT_ROOT_INO		1

#घोषणा EXFAT_CLUSTERS_UNTRACKED (~0u)

/*
 * exfat error flags
 */
क्रमागत exfat_error_mode अणु
	EXFAT_ERRORS_CONT,	/* ignore error and जारी */
	EXFAT_ERRORS_PANIC,	/* panic on error */
	EXFAT_ERRORS_RO,	/* remount r/o on error */
पूर्ण;

/*
 * exfat nls lossy flag
 */
क्रमागत अणु
	NLS_NAME_NO_LOSSY,	/* no lossy */
	NLS_NAME_LOSSY,		/* just detected incorrect filename(s) */
	NLS_NAME_OVERLEN,	/* the length is over than its limit */
पूर्ण;

#घोषणा EXFAT_HASH_BITS		8
#घोषणा EXFAT_HASH_SIZE		(1UL << EXFAT_HASH_BITS)

/*
 * Type Definitions
 */
#घोषणा ES_2_ENTRIES		2
#घोषणा ES_ALL_ENTRIES		0

#घोषणा सूची_DELETED		0xFFFF0321

/* type values */
#घोषणा TYPE_UNUSED		0x0000
#घोषणा TYPE_DELETED		0x0001
#घोषणा TYPE_INVALID		0x0002
#घोषणा TYPE_CRITICAL_PRI	0x0100
#घोषणा TYPE_BITMAP		0x0101
#घोषणा TYPE_UPCASE		0x0102
#घोषणा TYPE_VOLUME		0x0103
#घोषणा TYPE_सूची		0x0104
#घोषणा TYPE_खाता		0x011F
#घोषणा TYPE_CRITICAL_SEC	0x0200
#घोषणा TYPE_STREAM		0x0201
#घोषणा TYPE_EXTEND		0x0202
#घोषणा TYPE_ACL		0x0203
#घोषणा TYPE_BENIGN_PRI		0x0400
#घोषणा TYPE_GUID		0x0401
#घोषणा TYPE_PADDING		0x0402
#घोषणा TYPE_ACLTAB		0x0403
#घोषणा TYPE_BENIGN_SEC		0x0800
#घोषणा TYPE_ALL		0x0FFF

#घोषणा MAX_CHARSET_SIZE	6 /* max size of multi-byte अक्षरacter */
#घोषणा MAX_NAME_LENGTH		255 /* max len of file name excluding शून्य */
#घोषणा MAX_VFSNAME_BUF_SIZE	((MAX_NAME_LENGTH + 1) * MAX_CHARSET_SIZE)

/* Enough size to hold 256 dentry (even 512 Byte sector) */
#घोषणा सूची_CACHE_SIZE		(256*माप(काष्ठा exfat_dentry)/512+1)

#घोषणा EXFAT_HINT_NONE		-1
#घोषणा EXFAT_MIN_SUBसूची	2

/*
 * helpers क्रम cluster size to byte conversion.
 */
#घोषणा EXFAT_CLU_TO_B(b, sbi)		((b) << (sbi)->cluster_size_bits)
#घोषणा EXFAT_B_TO_CLU(b, sbi)		((b) >> (sbi)->cluster_size_bits)
#घोषणा EXFAT_B_TO_CLU_ROUND_UP(b, sbi)	\
	(((b - 1) >> (sbi)->cluster_size_bits) + 1)
#घोषणा EXFAT_CLU_OFFSET(off, sbi)	((off) & ((sbi)->cluster_size - 1))

/*
 * helpers क्रम block size to byte conversion.
 */
#घोषणा EXFAT_BLK_TO_B(b, sb)		((b) << (sb)->s_blocksize_bits)
#घोषणा EXFAT_B_TO_BLK(b, sb)		((b) >> (sb)->s_blocksize_bits)
#घोषणा EXFAT_B_TO_BLK_ROUND_UP(b, sb)	\
	(((b - 1) >> (sb)->s_blocksize_bits) + 1)
#घोषणा EXFAT_BLK_OFFSET(off, sb)	((off) & ((sb)->s_blocksize - 1))

/*
 * helpers क्रम block size to dentry size conversion.
 */
#घोषणा EXFAT_B_TO_DEN_IDX(b, sbi)	\
	((b) << ((sbi)->cluster_size_bits - DENTRY_SIZE_BITS))
#घोषणा EXFAT_B_TO_DEN(b)		((b) >> DENTRY_SIZE_BITS)
#घोषणा EXFAT_DEN_TO_B(b)		((b) << DENTRY_SIZE_BITS)

/*
 * helpers क्रम fat entry.
 */
#घोषणा FAT_ENT_SIZE (4)
#घोषणा FAT_ENT_SIZE_BITS (2)
#घोषणा FAT_ENT_OFFSET_SECTOR(sb, loc) (EXFAT_SB(sb)->FAT1_start_sector + \
	(((u64)loc << FAT_ENT_SIZE_BITS) >> sb->s_blocksize_bits))
#घोषणा FAT_ENT_OFFSET_BYTE_IN_SECTOR(sb, loc)	\
	((loc << FAT_ENT_SIZE_BITS) & (sb->s_blocksize - 1))

/*
 * helpers क्रम biपंचांगap.
 */
#घोषणा CLUSTER_TO_BITMAP_ENT(clu) ((clu) - EXFAT_RESERVED_CLUSTERS)
#घोषणा BITMAP_ENT_TO_CLUSTER(ent) ((ent) + EXFAT_RESERVED_CLUSTERS)
#घोषणा BITS_PER_SECTOR(sb) ((sb)->s_blocksize * BITS_PER_BYTE)
#घोषणा BITS_PER_SECTOR_MASK(sb) (BITS_PER_SECTOR(sb) - 1)
#घोषणा BITMAP_OFFSET_SECTOR_INDEX(sb, ent) \
	((ent / BITS_PER_BYTE) >> (sb)->s_blocksize_bits)
#घोषणा BITMAP_OFFSET_BIT_IN_SECTOR(sb, ent) (ent & BITS_PER_SECTOR_MASK(sb))
#घोषणा BITMAP_OFFSET_BYTE_IN_SECTOR(sb, ent) \
	((ent / BITS_PER_BYTE) & ((sb)->s_blocksize - 1))
#घोषणा BITS_PER_BYTE_MASK	0x7
#घोषणा IGNORED_BITS_REMAINED(clu, clu_base) ((1 << ((clu) - (clu_base))) - 1)

काष्ठा exfat_dentry_namebuf अणु
	अक्षर *lfn;
	पूर्णांक lfnbuf_len; /* usually MAX_UNINAME_BUF_SIZE */
पूर्ण;

/* unicode name काष्ठाure */
काष्ठा exfat_uni_name अणु
	/* +3 क्रम null and क्रम converting */
	अचिन्हित लघु name[MAX_NAME_LENGTH + 3];
	u16 name_hash;
	अचिन्हित अक्षर name_len;
पूर्ण;

/* directory काष्ठाure */
काष्ठा exfat_chain अणु
	अचिन्हित पूर्णांक dir;
	अचिन्हित पूर्णांक size;
	अचिन्हित अक्षर flags;
पूर्ण;

/* first empty entry hपूर्णांक inक्रमmation */
काष्ठा exfat_hपूर्णांक_femp अणु
	/* entry index of a directory */
	पूर्णांक eidx;
	/* count of continuous empty entry */
	पूर्णांक count;
	/* the cluster that first empty slot exists in */
	काष्ठा exfat_chain cur;
पूर्ण;

/* hपूर्णांक काष्ठाure */
काष्ठा exfat_hपूर्णांक अणु
	अचिन्हित पूर्णांक clu;
	जोड़ अणु
		अचिन्हित पूर्णांक off; /* cluster offset */
		पूर्णांक eidx; /* entry index */
	पूर्ण;
पूर्ण;

काष्ठा exfat_entry_set_cache अणु
	काष्ठा super_block *sb;
	bool modअगरied;
	अचिन्हित पूर्णांक start_off;
	पूर्णांक num_bh;
	काष्ठा buffer_head *bh[सूची_CACHE_SIZE];
	अचिन्हित पूर्णांक num_entries;
पूर्ण;

काष्ठा exfat_dir_entry अणु
	काष्ठा exfat_chain dir;
	पूर्णांक entry;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक start_clu;
	अचिन्हित अक्षर flags;
	अचिन्हित लघु attr;
	loff_t size;
	अचिन्हित पूर्णांक num_subdirs;
	काष्ठा बारpec64 aसमय;
	काष्ठा बारpec64 mसमय;
	काष्ठा बारpec64 crसमय;
	काष्ठा exfat_dentry_namebuf namebuf;
पूर्ण;

/*
 * exfat mount in-memory data
 */
काष्ठा exfat_mount_options अणु
	kuid_t fs_uid;
	kgid_t fs_gid;
	अचिन्हित लघु fs_fmask;
	अचिन्हित लघु fs_dmask;
	/* permission क्रम setting the [am]समय */
	अचिन्हित लघु allow_uसमय;
	/* अक्षरset क्रम filename input/display */
	अक्षर *ioअक्षरset;
	/* on error: जारी, panic, remount-ro */
	क्रमागत exfat_error_mode errors;
	अचिन्हित utf8:1, /* Use of UTF-8 अक्षरacter set */
		 discard:1; /* Issue discard requests on deletions */
	पूर्णांक समय_offset; /* Offset of बारtamps from UTC (in minutes) */
पूर्ण;

/*
 * EXFAT file प्रणाली superblock in-memory data
 */
काष्ठा exfat_sb_info अणु
	अचिन्हित दीर्घ दीर्घ num_sectors; /* num of sectors in volume */
	अचिन्हित पूर्णांक num_clusters; /* num of clusters in volume */
	अचिन्हित पूर्णांक cluster_size; /* cluster size in bytes */
	अचिन्हित पूर्णांक cluster_size_bits;
	अचिन्हित पूर्णांक sect_per_clus; /* cluster size in sectors */
	अचिन्हित पूर्णांक sect_per_clus_bits;
	अचिन्हित दीर्घ दीर्घ FAT1_start_sector; /* FAT1 start sector */
	अचिन्हित दीर्घ दीर्घ FAT2_start_sector; /* FAT2 start sector */
	अचिन्हित दीर्घ दीर्घ data_start_sector; /* data area start sector */
	अचिन्हित पूर्णांक num_FAT_sectors; /* num of FAT sectors */
	अचिन्हित पूर्णांक root_dir; /* root dir cluster */
	अचिन्हित पूर्णांक dentries_per_clu; /* num of dentries per cluster */
	अचिन्हित पूर्णांक vol_flags; /* volume flags */
	अचिन्हित पूर्णांक vol_flags_persistent; /* volume flags to retain */
	काष्ठा buffer_head *boot_bh; /* buffer_head of BOOT sector */

	अचिन्हित पूर्णांक map_clu; /* allocation biपंचांगap start cluster */
	अचिन्हित पूर्णांक map_sectors; /* num of allocation biपंचांगap sectors */
	काष्ठा buffer_head **vol_amap; /* allocation biपंचांगap */

	अचिन्हित लघु *vol_utbl; /* upहाल table */

	अचिन्हित पूर्णांक clu_srch_ptr; /* cluster search poपूर्णांकer */
	अचिन्हित पूर्णांक used_clusters; /* number of used clusters */

	काष्ठा mutex s_lock; /* superblock lock */
	काष्ठा mutex biपंचांगap_lock; /* biपंचांगap lock */
	काष्ठा exfat_mount_options options;
	काष्ठा nls_table *nls_io; /* Charset used क्रम input and display */
	काष्ठा ratelimit_state ratelimit;

	spinlock_t inode_hash_lock;
	काष्ठा hlist_head inode_hashtable[EXFAT_HASH_SIZE];

	काष्ठा rcu_head rcu;
पूर्ण;

#घोषणा EXFAT_CACHE_VALID	0

/*
 * EXFAT file प्रणाली inode in-memory data
 */
काष्ठा exfat_inode_info अणु
	काष्ठा exfat_chain dir;
	पूर्णांक entry;
	अचिन्हित पूर्णांक type;
	अचिन्हित लघु attr;
	अचिन्हित पूर्णांक start_clu;
	अचिन्हित अक्षर flags;
	/*
	 * the copy of low 32bit of i_version to check
	 * the validation of hपूर्णांक_stat.
	 */
	अचिन्हित पूर्णांक version;

	/* hपूर्णांक क्रम cluster last accessed */
	काष्ठा exfat_hपूर्णांक hपूर्णांक_bmap;
	/* hपूर्णांक क्रम entry index we try to lookup next समय */
	काष्ठा exfat_hपूर्णांक hपूर्णांक_stat;
	/* hपूर्णांक क्रम first empty entry */
	काष्ठा exfat_hपूर्णांक_femp hपूर्णांक_femp;

	spinlock_t cache_lru_lock;
	काष्ठा list_head cache_lru;
	पूर्णांक nr_caches;
	/* क्रम aव्योमing the race between alloc and मुक्त */
	अचिन्हित पूर्णांक cache_valid_id;

	/*
	 * NOTE: i_size_ondisk is 64bits, so must hold ->inode_lock to access.
	 * physically allocated size.
	 */
	loff_t i_size_ondisk;
	/* block-aligned i_size (used in cont_ग_लिखो_begin) */
	loff_t i_size_aligned;
	/* on-disk position of directory entry or 0 */
	loff_t i_pos;
	/* hash by i_location */
	काष्ठा hlist_node i_hash_fat;
	/* protect bmap against truncate */
	काष्ठा rw_semaphore truncate_lock;
	काष्ठा inode vfs_inode;
	/* File creation समय */
	काष्ठा बारpec64 i_crसमय;
पूर्ण;

अटल अंतरभूत काष्ठा exfat_sb_info *EXFAT_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

अटल अंतरभूत काष्ठा exfat_inode_info *EXFAT_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा exfat_inode_info, vfs_inode);
पूर्ण

/*
 * If ->i_mode can't hold 0222 (i.e. ATTR_RO), we use ->i_attrs to
 * save ATTR_RO instead of ->i_mode.
 *
 * If it's directory and !sbi->options.rodir, ATTR_RO isn't पढ़ो-only
 * bit, it's just used as flag क्रम app.
 */
अटल अंतरभूत पूर्णांक exfat_mode_can_hold_ro(काष्ठा inode *inode)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(inode->i_sb);

	अगर (S_ISसूची(inode->i_mode))
		वापस 0;

	अगर ((~sbi->options.fs_fmask) & 0222)
		वापस 1;
	वापस 0;
पूर्ण

/* Convert attribute bits and a mask to the UNIX mode. */
अटल अंतरभूत mode_t exfat_make_mode(काष्ठा exfat_sb_info *sbi,
		अचिन्हित लघु attr, mode_t mode)
अणु
	अगर ((attr & ATTR_READONLY) && !(attr & ATTR_SUBसूची))
		mode &= ~0222;

	अगर (attr & ATTR_SUBसूची)
		वापस (mode & ~sbi->options.fs_dmask) | S_IFसूची;

	वापस (mode & ~sbi->options.fs_fmask) | S_IFREG;
पूर्ण

/* Return the FAT attribute byte क्रम this inode */
अटल अंतरभूत अचिन्हित लघु exfat_make_attr(काष्ठा inode *inode)
अणु
	अचिन्हित लघु attr = EXFAT_I(inode)->attr;

	अगर (S_ISसूची(inode->i_mode))
		attr |= ATTR_SUBसूची;
	अगर (exfat_mode_can_hold_ro(inode) && !(inode->i_mode & 0222))
		attr |= ATTR_READONLY;
	वापस attr;
पूर्ण

अटल अंतरभूत व्योम exfat_save_attr(काष्ठा inode *inode, अचिन्हित लघु attr)
अणु
	अगर (exfat_mode_can_hold_ro(inode))
		EXFAT_I(inode)->attr = attr & (ATTR_RWMASK | ATTR_READONLY);
	अन्यथा
		EXFAT_I(inode)->attr = attr & ATTR_RWMASK;
पूर्ण

अटल अंतरभूत bool exfat_is_last_sector_in_cluster(काष्ठा exfat_sb_info *sbi,
		sector_t sec)
अणु
	वापस ((sec - sbi->data_start_sector + 1) &
		((1 << sbi->sect_per_clus_bits) - 1)) == 0;
पूर्ण

अटल अंतरभूत sector_t exfat_cluster_to_sector(काष्ठा exfat_sb_info *sbi,
		अचिन्हित पूर्णांक clus)
अणु
	वापस ((sector_t)(clus - EXFAT_RESERVED_CLUSTERS) << sbi->sect_per_clus_bits) +
		sbi->data_start_sector;
पूर्ण

अटल अंतरभूत पूर्णांक exfat_sector_to_cluster(काष्ठा exfat_sb_info *sbi,
		sector_t sec)
अणु
	वापस ((sec - sbi->data_start_sector) >> sbi->sect_per_clus_bits) +
		EXFAT_RESERVED_CLUSTERS;
पूर्ण

/* super.c */
पूर्णांक exfat_set_volume_dirty(काष्ठा super_block *sb);
पूर्णांक exfat_clear_volume_dirty(काष्ठा super_block *sb);

/* fatent.c */
#घोषणा exfat_get_next_cluster(sb, pclu) exfat_ent_get(sb, *(pclu), pclu)

पूर्णांक exfat_alloc_cluster(काष्ठा inode *inode, अचिन्हित पूर्णांक num_alloc,
		काष्ठा exfat_chain *p_chain, bool sync_bmap);
पूर्णांक exfat_मुक्त_cluster(काष्ठा inode *inode, काष्ठा exfat_chain *p_chain);
पूर्णांक exfat_ent_get(काष्ठा super_block *sb, अचिन्हित पूर्णांक loc,
		अचिन्हित पूर्णांक *content);
पूर्णांक exfat_ent_set(काष्ठा super_block *sb, अचिन्हित पूर्णांक loc,
		अचिन्हित पूर्णांक content);
पूर्णांक exfat_count_ext_entries(काष्ठा super_block *sb, काष्ठा exfat_chain *p_dir,
		पूर्णांक entry, काष्ठा exfat_dentry *p_entry);
पूर्णांक exfat_chain_cont_cluster(काष्ठा super_block *sb, अचिन्हित पूर्णांक chain,
		अचिन्हित पूर्णांक len);
पूर्णांक exfat_zeroed_cluster(काष्ठा inode *dir, अचिन्हित पूर्णांक clu);
पूर्णांक exfat_find_last_cluster(काष्ठा super_block *sb, काष्ठा exfat_chain *p_chain,
		अचिन्हित पूर्णांक *ret_clu);
पूर्णांक exfat_count_num_clusters(काष्ठा super_block *sb,
		काष्ठा exfat_chain *p_chain, अचिन्हित पूर्णांक *ret_count);

/* balloc.c */
पूर्णांक exfat_load_biपंचांगap(काष्ठा super_block *sb);
व्योम exfat_मुक्त_biपंचांगap(काष्ठा exfat_sb_info *sbi);
पूर्णांक exfat_set_biपंचांगap(काष्ठा inode *inode, अचिन्हित पूर्णांक clu, bool sync);
व्योम exfat_clear_biपंचांगap(काष्ठा inode *inode, अचिन्हित पूर्णांक clu, bool sync);
अचिन्हित पूर्णांक exfat_find_मुक्त_biपंचांगap(काष्ठा super_block *sb, अचिन्हित पूर्णांक clu);
पूर्णांक exfat_count_used_clusters(काष्ठा super_block *sb, अचिन्हित पूर्णांक *ret_count);
पूर्णांक exfat_trim_fs(काष्ठा inode *inode, काष्ठा fstrim_range *range);

/* file.c */
बाह्य स्थिर काष्ठा file_operations exfat_file_operations;
पूर्णांक __exfat_truncate(काष्ठा inode *inode, loff_t new_size);
व्योम exfat_truncate(काष्ठा inode *inode, loff_t size);
पूर्णांक exfat_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		  काष्ठा iattr *attr);
पूर्णांक exfat_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		  काष्ठा kstat *stat, अचिन्हित पूर्णांक request_mask,
		  अचिन्हित पूर्णांक query_flags);
पूर्णांक exfat_file_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync);
दीर्घ exfat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
दीर्घ exfat_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg);

/* namei.c */
बाह्य स्थिर काष्ठा dentry_operations exfat_dentry_ops;
बाह्य स्थिर काष्ठा dentry_operations exfat_utf8_dentry_ops;

/* cache.c */
पूर्णांक exfat_cache_init(व्योम);
व्योम exfat_cache_shutकरोwn(व्योम);
व्योम exfat_cache_inval_inode(काष्ठा inode *inode);
पूर्णांक exfat_get_cluster(काष्ठा inode *inode, अचिन्हित पूर्णांक cluster,
		अचिन्हित पूर्णांक *fclus, अचिन्हित पूर्णांक *dclus,
		अचिन्हित पूर्णांक *last_dclus, पूर्णांक allow_eof);

/* dir.c */
बाह्य स्थिर काष्ठा inode_operations exfat_dir_inode_operations;
बाह्य स्थिर काष्ठा file_operations exfat_dir_operations;
अचिन्हित पूर्णांक exfat_get_entry_type(काष्ठा exfat_dentry *p_entry);
पूर्णांक exfat_init_dir_entry(काष्ठा inode *inode, काष्ठा exfat_chain *p_dir,
		पूर्णांक entry, अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक start_clu,
		अचिन्हित दीर्घ दीर्घ size);
पूर्णांक exfat_init_ext_entry(काष्ठा inode *inode, काष्ठा exfat_chain *p_dir,
		पूर्णांक entry, पूर्णांक num_entries, काष्ठा exfat_uni_name *p_uniname);
पूर्णांक exfat_हटाओ_entries(काष्ठा inode *inode, काष्ठा exfat_chain *p_dir,
		पूर्णांक entry, पूर्णांक order, पूर्णांक num_entries);
पूर्णांक exfat_update_dir_chksum(काष्ठा inode *inode, काष्ठा exfat_chain *p_dir,
		पूर्णांक entry);
व्योम exfat_update_dir_chksum_with_entry_set(काष्ठा exfat_entry_set_cache *es);
पूर्णांक exfat_calc_num_entries(काष्ठा exfat_uni_name *p_uniname);
पूर्णांक exfat_find_dir_entry(काष्ठा super_block *sb, काष्ठा exfat_inode_info *ei,
		काष्ठा exfat_chain *p_dir, काष्ठा exfat_uni_name *p_uniname,
		पूर्णांक num_entries, अचिन्हित पूर्णांक type, काष्ठा exfat_hपूर्णांक *hपूर्णांक_opt);
पूर्णांक exfat_alloc_new_dir(काष्ठा inode *inode, काष्ठा exfat_chain *clu);
पूर्णांक exfat_find_location(काष्ठा super_block *sb, काष्ठा exfat_chain *p_dir,
		पूर्णांक entry, sector_t *sector, पूर्णांक *offset);
काष्ठा exfat_dentry *exfat_get_dentry(काष्ठा super_block *sb,
		काष्ठा exfat_chain *p_dir, पूर्णांक entry, काष्ठा buffer_head **bh,
		sector_t *sector);
काष्ठा exfat_dentry *exfat_get_dentry_cached(काष्ठा exfat_entry_set_cache *es,
		पूर्णांक num);
काष्ठा exfat_entry_set_cache *exfat_get_dentry_set(काष्ठा super_block *sb,
		काष्ठा exfat_chain *p_dir, पूर्णांक entry, अचिन्हित पूर्णांक type);
पूर्णांक exfat_मुक्त_dentry_set(काष्ठा exfat_entry_set_cache *es, पूर्णांक sync);
पूर्णांक exfat_count_dir_entries(काष्ठा super_block *sb, काष्ठा exfat_chain *p_dir);

/* inode.c */
बाह्य स्थिर काष्ठा inode_operations exfat_file_inode_operations;
व्योम exfat_sync_inode(काष्ठा inode *inode);
काष्ठा inode *exfat_build_inode(काष्ठा super_block *sb,
		काष्ठा exfat_dir_entry *info, loff_t i_pos);
व्योम exfat_hash_inode(काष्ठा inode *inode, loff_t i_pos);
व्योम exfat_unhash_inode(काष्ठा inode *inode);
काष्ठा inode *exfat_iget(काष्ठा super_block *sb, loff_t i_pos);
पूर्णांक exfat_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc);
व्योम exfat_evict_inode(काष्ठा inode *inode);
पूर्णांक exfat_block_truncate_page(काष्ठा inode *inode, loff_t from);

/* exfat/nls.c */
अचिन्हित लघु exfat_बड़े(काष्ठा super_block *sb, अचिन्हित लघु a);
पूर्णांक exfat_uniname_ncmp(काष्ठा super_block *sb, अचिन्हित लघु *a,
		अचिन्हित लघु *b, अचिन्हित पूर्णांक len);
पूर्णांक exfat_utf16_to_nls(काष्ठा super_block *sb,
		काष्ठा exfat_uni_name *uniname, अचिन्हित अक्षर *p_cstring,
		पूर्णांक len);
पूर्णांक exfat_nls_to_utf16(काष्ठा super_block *sb,
		स्थिर अचिन्हित अक्षर *p_cstring, स्थिर पूर्णांक len,
		काष्ठा exfat_uni_name *uniname, पूर्णांक *p_lossy);
पूर्णांक exfat_create_upहाल_table(काष्ठा super_block *sb);
व्योम exfat_मुक्त_upहाल_table(काष्ठा exfat_sb_info *sbi);

/* exfat/misc.c */
व्योम __exfat_fs_error(काष्ठा super_block *sb, पूर्णांक report, स्थिर अक्षर *fmt, ...)
		__म_लिखो(3, 4) __cold;
#घोषणा exfat_fs_error(sb, fmt, args...)          \
		__exfat_fs_error(sb, 1, fmt, ## args)
#घोषणा exfat_fs_error_ratelimit(sb, fmt, args...) \
		__exfat_fs_error(sb, __ratelimit(&EXFAT_SB(sb)->ratelimit), \
		fmt, ## args)
व्योम exfat_msg(काष्ठा super_block *sb, स्थिर अक्षर *lv, स्थिर अक्षर *fmt, ...)
		__म_लिखो(3, 4) __cold;
#घोषणा exfat_err(sb, fmt, ...)						\
	exfat_msg(sb, KERN_ERR, fmt, ##__VA_ARGS__)
#घोषणा exfat_warn(sb, fmt, ...)					\
	exfat_msg(sb, KERN_WARNING, fmt, ##__VA_ARGS__)
#घोषणा exfat_info(sb, fmt, ...)					\
	exfat_msg(sb, KERN_INFO, fmt, ##__VA_ARGS__)

व्योम exfat_get_entry_समय(काष्ठा exfat_sb_info *sbi, काष्ठा बारpec64 *ts,
		u8 tz, __le16 समय, __le16 date, u8 समय_cs);
व्योम exfat_truncate_aसमय(काष्ठा बारpec64 *ts);
व्योम exfat_set_entry_समय(काष्ठा exfat_sb_info *sbi, काष्ठा बारpec64 *ts,
		u8 *tz, __le16 *समय, __le16 *date, u8 *समय_cs);
u16 exfat_calc_chksum16(व्योम *data, पूर्णांक len, u16 chksum, पूर्णांक type);
u32 exfat_calc_chksum32(व्योम *data, पूर्णांक len, u32 chksum, पूर्णांक type);
व्योम exfat_update_bh(काष्ठा buffer_head *bh, पूर्णांक sync);
पूर्णांक exfat_update_bhs(काष्ठा buffer_head **bhs, पूर्णांक nr_bhs, पूर्णांक sync);
व्योम exfat_chain_set(काष्ठा exfat_chain *ec, अचिन्हित पूर्णांक dir,
		अचिन्हित पूर्णांक size, अचिन्हित अक्षर flags);
व्योम exfat_chain_dup(काष्ठा exfat_chain *dup, काष्ठा exfat_chain *ec);

#पूर्ण_अगर /* !_EXFAT_FS_H */
