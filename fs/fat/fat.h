<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FAT_H
#घोषणा _FAT_H

#समावेश <linux/buffer_head.h>
#समावेश <linux/nls.h>
#समावेश <linux/hash.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/msकरोs_fs.h>

/*
 * vfat लघुname flags
 */
#घोषणा VFAT_SFN_DISPLAY_LOWER	0x0001 /* convert to lowerहाल क्रम display */
#घोषणा VFAT_SFN_DISPLAY_WIN95	0x0002 /* emulate win95 rule क्रम display */
#घोषणा VFAT_SFN_DISPLAY_WINNT	0x0004 /* emulate winnt rule क्रम display */
#घोषणा VFAT_SFN_CREATE_WIN95	0x0100 /* emulate win95 rule क्रम create */
#घोषणा VFAT_SFN_CREATE_WINNT	0x0200 /* emulate winnt rule क्रम create */

#घोषणा FAT_ERRORS_CONT		1      /* ignore error and जारी */
#घोषणा FAT_ERRORS_PANIC	2      /* panic on error */
#घोषणा FAT_ERRORS_RO		3      /* remount r/o on error */

#घोषणा FAT_NFS_STALE_RW	1      /* NFS RW support, can cause ESTALE */
#घोषणा FAT_NFS_NOSTALE_RO	2      /* NFS RO support, no ESTALE issue */

काष्ठा fat_mount_options अणु
	kuid_t fs_uid;
	kgid_t fs_gid;
	अचिन्हित लघु fs_fmask;
	अचिन्हित लघु fs_dmask;
	अचिन्हित लघु codepage;   /* Codepage क्रम लघुname conversions */
	पूर्णांक समय_offset;	   /* Offset of बारtamps from UTC (in minutes) */
	अक्षर *ioअक्षरset;           /* Charset used क्रम filename input/display */
	अचिन्हित लघु लघुname;  /* flags क्रम लघुname display/create rule */
	अचिन्हित अक्षर name_check;  /* r = relaxed, n = normal, s = strict */
	अचिन्हित अक्षर errors;	   /* On error: जारी, panic, remount-ro */
	अचिन्हित अक्षर nfs;	  /* NFS support: nostale_ro, stale_rw */
	अचिन्हित लघु allow_uसमय;/* permission क्रम setting the [am]समय */
	अचिन्हित quiet:1,          /* set = fake successful chmods and chowns */
		 showexec:1,       /* set = only set x bit क्रम com/exe/bat */
		 sys_immutable:1,  /* set = प्रणाली files are immutable */
		 करोtsOK:1,         /* set = hidden and प्रणाली files are named '.filename' */
		 isvfat:1,         /* 0=no vfat दीर्घ filename support, 1=vfat support */
		 utf8:1,	   /* Use of UTF-8 अक्षरacter set (Default) */
		 unicode_xlate:1,  /* create escape sequences क्रम unhandled Unicode */
		 numtail:1,        /* Does first alias have a numeric '~1' type tail? */
		 flush:1,	   /* ग_लिखो things quickly */
		 noहाल:1,	   /* Does this need हाल conversion? 0=need हाल conversion*/
		 useमुक्त:1,	   /* Use मुक्त_clusters क्रम FAT32 */
		 tz_set:1,	   /* Fileप्रणाली बारtamps' offset set */
		 rodir:1,	   /* allow ATTR_RO क्रम directory */
		 discard:1,	   /* Issue discard requests on deletions */
		 करोs1xfloppy:1;	   /* Assume शेष BPB क्रम DOS 1.x floppies */
पूर्ण;

#घोषणा FAT_HASH_BITS	8
#घोषणा FAT_HASH_SIZE	(1UL << FAT_HASH_BITS)

/*
 * MS-DOS file प्रणाली in-core superblock data
 */
काष्ठा msकरोs_sb_info अणु
	अचिन्हित लघु sec_per_clus;  /* sectors/cluster */
	अचिन्हित लघु cluster_bits;  /* log2(cluster_size) */
	अचिन्हित पूर्णांक cluster_size;    /* cluster size */
	अचिन्हित अक्षर fats, fat_bits; /* number of FATs, FAT bits (12,16 or 32) */
	अचिन्हित लघु fat_start;
	अचिन्हित दीर्घ fat_length;     /* FAT start & length (sec.) */
	अचिन्हित दीर्घ dir_start;
	अचिन्हित लघु dir_entries;   /* root dir start & entries */
	अचिन्हित दीर्घ data_start;     /* first data sector */
	अचिन्हित दीर्घ max_cluster;    /* maximum cluster number */
	अचिन्हित दीर्घ root_cluster;   /* first cluster of the root directory */
	अचिन्हित दीर्घ fsinfo_sector;  /* sector number of FAT32 fsinfo */
	काष्ठा mutex fat_lock;
	काष्ठा mutex nfs_build_inode_lock;
	काष्ठा mutex s_lock;
	अचिन्हित पूर्णांक prev_मुक्त;      /* previously allocated cluster number */
	अचिन्हित पूर्णांक मुक्त_clusters;  /* -1 अगर undefined */
	अचिन्हित पूर्णांक मुक्त_clus_valid; /* is मुक्त_clusters valid? */
	काष्ठा fat_mount_options options;
	काष्ठा nls_table *nls_disk;   /* Codepage used on disk */
	काष्ठा nls_table *nls_io;     /* Charset used क्रम input and display */
	स्थिर व्योम *dir_ops;	      /* Opaque; शेष directory operations */
	पूर्णांक dir_per_block;	      /* dir entries per block */
	पूर्णांक dir_per_block_bits;	      /* log2(dir_per_block) */
	अचिन्हित पूर्णांक vol_id;		/*volume ID*/

	पूर्णांक fatent_shअगरt;
	स्थिर काष्ठा fatent_operations *fatent_ops;
	काष्ठा inode *fat_inode;
	काष्ठा inode *fsinfo_inode;

	काष्ठा ratelimit_state ratelimit;

	spinlock_t inode_hash_lock;
	काष्ठा hlist_head inode_hashtable[FAT_HASH_SIZE];

	spinlock_t dir_hash_lock;
	काष्ठा hlist_head dir_hashtable[FAT_HASH_SIZE];

	अचिन्हित पूर्णांक dirty;           /* fs state beक्रमe mount */
	काष्ठा rcu_head rcu;
पूर्ण;

#घोषणा FAT_CACHE_VALID	0	/* special हाल क्रम valid cache */

/*
 * MS-DOS file प्रणाली inode data in memory
 */
काष्ठा msकरोs_inode_info अणु
	spinlock_t cache_lru_lock;
	काष्ठा list_head cache_lru;
	पूर्णांक nr_caches;
	/* क्रम aव्योमing the race between fat_मुक्त() and fat_get_cluster() */
	अचिन्हित पूर्णांक cache_valid_id;

	/* NOTE: mmu_निजी is 64bits, so must hold ->i_mutex to access */
	loff_t mmu_निजी;	/* physically allocated size */

	पूर्णांक i_start;		/* first cluster or 0 */
	पूर्णांक i_logstart;		/* logical first cluster */
	पूर्णांक i_attrs;		/* unused attribute bits */
	loff_t i_pos;		/* on-disk position of directory entry or 0 */
	काष्ठा hlist_node i_fat_hash;	/* hash by i_location */
	काष्ठा hlist_node i_dir_hash;	/* hash by i_logstart */
	काष्ठा rw_semaphore truncate_lock; /* protect bmap against truncate */
	काष्ठा inode vfs_inode;
पूर्ण;

काष्ठा fat_slot_info अणु
	loff_t i_pos;		/* on-disk position of directory entry */
	loff_t slot_off;	/* offset क्रम slot or de start */
	पूर्णांक nr_slots;		/* number of slots + 1(de) in filename */
	काष्ठा msकरोs_dir_entry *de;
	काष्ठा buffer_head *bh;
पूर्ण;

अटल अंतरभूत काष्ठा msकरोs_sb_info *MSDOS_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

/*
 * Functions that determine the variant of the FAT file प्रणाली (i.e.,
 * whether this is FAT12, FAT16 or FAT32.
 */
अटल अंतरभूत bool is_fat12(स्थिर काष्ठा msकरोs_sb_info *sbi)
अणु
	वापस sbi->fat_bits == 12;
पूर्ण

अटल अंतरभूत bool is_fat16(स्थिर काष्ठा msकरोs_sb_info *sbi)
अणु
	वापस sbi->fat_bits == 16;
पूर्ण

अटल अंतरभूत bool is_fat32(स्थिर काष्ठा msकरोs_sb_info *sbi)
अणु
	वापस sbi->fat_bits == 32;
पूर्ण

/* Maximum number of clusters */
अटल अंतरभूत u32 max_fat(काष्ठा super_block *sb)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);

	वापस is_fat32(sbi) ? MAX_FAT32 :
		is_fat16(sbi) ? MAX_FAT16 : MAX_FAT12;
पूर्ण

अटल अंतरभूत काष्ठा msकरोs_inode_info *MSDOS_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा msकरोs_inode_info, vfs_inode);
पूर्ण

/*
 * If ->i_mode can't hold S_IWUGO (i.e. ATTR_RO), we use ->i_attrs to
 * save ATTR_RO instead of ->i_mode.
 *
 * If it's directory and !sbi->options.rodir, ATTR_RO isn't पढ़ो-only
 * bit, it's just used as flag क्रम app.
 */
अटल अंतरभूत पूर्णांक fat_mode_can_hold_ro(काष्ठा inode *inode)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(inode->i_sb);
	umode_t mask;

	अगर (S_ISसूची(inode->i_mode)) अणु
		अगर (!sbi->options.rodir)
			वापस 0;
		mask = ~sbi->options.fs_dmask;
	पूर्ण अन्यथा
		mask = ~sbi->options.fs_fmask;

	अगर (!(mask & S_IWUGO))
		वापस 0;
	वापस 1;
पूर्ण

/* Convert attribute bits and a mask to the UNIX mode. */
अटल अंतरभूत umode_t fat_make_mode(काष्ठा msकरोs_sb_info *sbi,
				   u8 attrs, umode_t mode)
अणु
	अगर (attrs & ATTR_RO && !((attrs & ATTR_सूची) && !sbi->options.rodir))
		mode &= ~S_IWUGO;

	अगर (attrs & ATTR_सूची)
		वापस (mode & ~sbi->options.fs_dmask) | S_IFसूची;
	अन्यथा
		वापस (mode & ~sbi->options.fs_fmask) | S_IFREG;
पूर्ण

/* Return the FAT attribute byte क्रम this inode */
अटल अंतरभूत u8 fat_make_attrs(काष्ठा inode *inode)
अणु
	u8 attrs = MSDOS_I(inode)->i_attrs;
	अगर (S_ISसूची(inode->i_mode))
		attrs |= ATTR_सूची;
	अगर (fat_mode_can_hold_ro(inode) && !(inode->i_mode & S_IWUGO))
		attrs |= ATTR_RO;
	वापस attrs;
पूर्ण

अटल अंतरभूत व्योम fat_save_attrs(काष्ठा inode *inode, u8 attrs)
अणु
	अगर (fat_mode_can_hold_ro(inode))
		MSDOS_I(inode)->i_attrs = attrs & ATTR_UNUSED;
	अन्यथा
		MSDOS_I(inode)->i_attrs = attrs & (ATTR_UNUSED | ATTR_RO);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर fat_checksum(स्थिर __u8 *name)
अणु
	अचिन्हित अक्षर s = name[0];
	s = (s<<7) + (s>>1) + name[1];	s = (s<<7) + (s>>1) + name[2];
	s = (s<<7) + (s>>1) + name[3];	s = (s<<7) + (s>>1) + name[4];
	s = (s<<7) + (s>>1) + name[5];	s = (s<<7) + (s>>1) + name[6];
	s = (s<<7) + (s>>1) + name[7];	s = (s<<7) + (s>>1) + name[8];
	s = (s<<7) + (s>>1) + name[9];	s = (s<<7) + (s>>1) + name[10];
	वापस s;
पूर्ण

अटल अंतरभूत sector_t fat_clus_to_blknr(काष्ठा msकरोs_sb_info *sbi, पूर्णांक clus)
अणु
	वापस ((sector_t)clus - FAT_START_ENT) * sbi->sec_per_clus
		+ sbi->data_start;
पूर्ण

अटल अंतरभूत व्योम fat_get_blknr_offset(काष्ठा msकरोs_sb_info *sbi,
				loff_t i_pos, sector_t *blknr, पूर्णांक *offset)
अणु
	*blknr = i_pos >> sbi->dir_per_block_bits;
	*offset = i_pos & (sbi->dir_per_block - 1);
पूर्ण

अटल अंतरभूत loff_t fat_i_pos_पढ़ो(काष्ठा msकरोs_sb_info *sbi,
					काष्ठा inode *inode)
अणु
	loff_t i_pos;
#अगर BITS_PER_LONG == 32
	spin_lock(&sbi->inode_hash_lock);
#पूर्ण_अगर
	i_pos = MSDOS_I(inode)->i_pos;
#अगर BITS_PER_LONG == 32
	spin_unlock(&sbi->inode_hash_lock);
#पूर्ण_अगर
	वापस i_pos;
पूर्ण

अटल अंतरभूत व्योम fat16_towअक्षर(ब_अक्षर_प्रकार *dst, स्थिर __u8 *src, माप_प्रकार len)
अणु
#अगर_घोषित __BIG_ENDIAN
	जबतक (len--) अणु
		*dst++ = src[0] | (src[1] << 8);
		src += 2;
	पूर्ण
#अन्यथा
	स_नकल(dst, src, len * 2);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक fat_get_start(स्थिर काष्ठा msकरोs_sb_info *sbi,
				स्थिर काष्ठा msकरोs_dir_entry *de)
अणु
	पूर्णांक cluster = le16_to_cpu(de->start);
	अगर (is_fat32(sbi))
		cluster |= (le16_to_cpu(de->starthi) << 16);
	वापस cluster;
पूर्ण

अटल अंतरभूत व्योम fat_set_start(काष्ठा msकरोs_dir_entry *de, पूर्णांक cluster)
अणु
	de->start   = cpu_to_le16(cluster);
	de->starthi = cpu_to_le16(cluster >> 16);
पूर्ण

अटल अंतरभूत व्योम fatब_अक्षर_प्रकारo16(__u8 *dst, स्थिर ब_अक्षर_प्रकार *src, माप_प्रकार len)
अणु
#अगर_घोषित __BIG_ENDIAN
	जबतक (len--) अणु
		dst[0] = *src & 0x00FF;
		dst[1] = (*src & 0xFF00) >> 8;
		dst += 2;
		src++;
	पूर्ण
#अन्यथा
	स_नकल(dst, src, len * 2);
#पूर्ण_अगर
पूर्ण

/* fat/cache.c */
बाह्य व्योम fat_cache_inval_inode(काष्ठा inode *inode);
बाह्य पूर्णांक fat_get_cluster(काष्ठा inode *inode, पूर्णांक cluster,
			   पूर्णांक *fclus, पूर्णांक *dclus);
बाह्य पूर्णांक fat_get_mapped_cluster(काष्ठा inode *inode, sector_t sector,
				  sector_t last_block,
				  अचिन्हित दीर्घ *mapped_blocks, sector_t *bmap);
बाह्य पूर्णांक fat_bmap(काष्ठा inode *inode, sector_t sector, sector_t *phys,
		    अचिन्हित दीर्घ *mapped_blocks, पूर्णांक create, bool from_bmap);

/* fat/dir.c */
बाह्य स्थिर काष्ठा file_operations fat_dir_operations;
बाह्य पूर्णांक fat_search_दीर्घ(काष्ठा inode *inode, स्थिर अचिन्हित अक्षर *name,
			   पूर्णांक name_len, काष्ठा fat_slot_info *sinfo);
बाह्य पूर्णांक fat_dir_empty(काष्ठा inode *dir);
बाह्य पूर्णांक fat_subdirs(काष्ठा inode *dir);
बाह्य पूर्णांक fat_scan(काष्ठा inode *dir, स्थिर अचिन्हित अक्षर *name,
		    काष्ठा fat_slot_info *sinfo);
बाह्य पूर्णांक fat_scan_logstart(काष्ठा inode *dir, पूर्णांक i_logstart,
			     काष्ठा fat_slot_info *sinfo);
बाह्य पूर्णांक fat_get_करोtकरोt_entry(काष्ठा inode *dir, काष्ठा buffer_head **bh,
				काष्ठा msकरोs_dir_entry **de);
बाह्य पूर्णांक fat_alloc_new_dir(काष्ठा inode *dir, काष्ठा बारpec64 *ts);
बाह्य पूर्णांक fat_add_entries(काष्ठा inode *dir, व्योम *slots, पूर्णांक nr_slots,
			   काष्ठा fat_slot_info *sinfo);
बाह्य पूर्णांक fat_हटाओ_entries(काष्ठा inode *dir, काष्ठा fat_slot_info *sinfo);

/* fat/fatent.c */
काष्ठा fat_entry अणु
	पूर्णांक entry;
	जोड़ अणु
		u8 *ent12_p[2];
		__le16 *ent16_p;
		__le32 *ent32_p;
	पूर्ण u;
	पूर्णांक nr_bhs;
	काष्ठा buffer_head *bhs[2];
	काष्ठा inode *fat_inode;
पूर्ण;

अटल अंतरभूत व्योम fatent_init(काष्ठा fat_entry *fatent)
अणु
	fatent->nr_bhs = 0;
	fatent->entry = 0;
	fatent->u.ent32_p = शून्य;
	fatent->bhs[0] = fatent->bhs[1] = शून्य;
	fatent->fat_inode = शून्य;
पूर्ण

अटल अंतरभूत व्योम fatent_set_entry(काष्ठा fat_entry *fatent, पूर्णांक entry)
अणु
	fatent->entry = entry;
	fatent->u.ent32_p = शून्य;
पूर्ण

अटल अंतरभूत व्योम fatent_brअन्यथा(काष्ठा fat_entry *fatent)
अणु
	पूर्णांक i;
	fatent->u.ent32_p = शून्य;
	क्रम (i = 0; i < fatent->nr_bhs; i++)
		brअन्यथा(fatent->bhs[i]);
	fatent->nr_bhs = 0;
	fatent->bhs[0] = fatent->bhs[1] = शून्य;
	fatent->fat_inode = शून्य;
पूर्ण

अटल अंतरभूत bool fat_valid_entry(काष्ठा msकरोs_sb_info *sbi, पूर्णांक entry)
अणु
	वापस FAT_START_ENT <= entry && entry < sbi->max_cluster;
पूर्ण

बाह्य व्योम fat_ent_access_init(काष्ठा super_block *sb);
बाह्य पूर्णांक fat_ent_पढ़ो(काष्ठा inode *inode, काष्ठा fat_entry *fatent,
			पूर्णांक entry);
बाह्य पूर्णांक fat_ent_ग_लिखो(काष्ठा inode *inode, काष्ठा fat_entry *fatent,
			 पूर्णांक new, पूर्णांक रुको);
बाह्य पूर्णांक fat_alloc_clusters(काष्ठा inode *inode, पूर्णांक *cluster,
			      पूर्णांक nr_cluster);
बाह्य पूर्णांक fat_मुक्त_clusters(काष्ठा inode *inode, पूर्णांक cluster);
बाह्य पूर्णांक fat_count_मुक्त_clusters(काष्ठा super_block *sb);
बाह्य पूर्णांक fat_trim_fs(काष्ठा inode *inode, काष्ठा fstrim_range *range);

/* fat/file.c */
बाह्य दीर्घ fat_generic_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg);
बाह्य स्थिर काष्ठा file_operations fat_file_operations;
बाह्य स्थिर काष्ठा inode_operations fat_file_inode_operations;
बाह्य पूर्णांक fat_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		       काष्ठा iattr *attr);
बाह्य व्योम fat_truncate_blocks(काष्ठा inode *inode, loff_t offset);
बाह्य पूर्णांक fat_getattr(काष्ठा user_namespace *mnt_userns,
		       स्थिर काष्ठा path *path, काष्ठा kstat *stat,
		       u32 request_mask, अचिन्हित पूर्णांक flags);
बाह्य पूर्णांक fat_file_fsync(काष्ठा file *file, loff_t start, loff_t end,
			  पूर्णांक datasync);

/* fat/inode.c */
बाह्य पूर्णांक fat_block_truncate_page(काष्ठा inode *inode, loff_t from);
बाह्य व्योम fat_attach(काष्ठा inode *inode, loff_t i_pos);
बाह्य व्योम fat_detach(काष्ठा inode *inode);
बाह्य काष्ठा inode *fat_iget(काष्ठा super_block *sb, loff_t i_pos);
बाह्य काष्ठा inode *fat_build_inode(काष्ठा super_block *sb,
			काष्ठा msकरोs_dir_entry *de, loff_t i_pos);
बाह्य पूर्णांक fat_sync_inode(काष्ठा inode *inode);
बाह्य पूर्णांक fat_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent,
			  पूर्णांक isvfat, व्योम (*setup)(काष्ठा super_block *));
बाह्य पूर्णांक fat_fill_inode(काष्ठा inode *inode, काष्ठा msकरोs_dir_entry *de);

बाह्य पूर्णांक fat_flush_inodes(काष्ठा super_block *sb, काष्ठा inode *i1,
			    काष्ठा inode *i2);
अटल अंतरभूत अचिन्हित दीर्घ fat_dir_hash(पूर्णांक logstart)
अणु
	वापस hash_32(logstart, FAT_HASH_BITS);
पूर्ण
बाह्य पूर्णांक fat_add_cluster(काष्ठा inode *inode);

/* fat/misc.c */
बाह्य __म_लिखो(3, 4) __cold
व्योम __fat_fs_error(काष्ठा super_block *sb, पूर्णांक report, स्थिर अक्षर *fmt, ...);
#घोषणा fat_fs_error(sb, fmt, args...)		\
	__fat_fs_error(sb, 1, fmt , ## args)
#घोषणा fat_fs_error_ratelimit(sb, fmt, args...) \
	__fat_fs_error(sb, __ratelimit(&MSDOS_SB(sb)->ratelimit), fmt , ## args)
__म_लिखो(3, 4) __cold
व्योम fat_msg(काष्ठा super_block *sb, स्थिर अक्षर *level, स्थिर अक्षर *fmt, ...);
#घोषणा fat_msg_ratelimit(sb, level, fmt, args...)	\
	करो अणु	\
			अगर (__ratelimit(&MSDOS_SB(sb)->ratelimit))	\
				fat_msg(sb, level, fmt, ## args);	\
	 पूर्ण जबतक (0)
बाह्य पूर्णांक fat_clusters_flush(काष्ठा super_block *sb);
बाह्य पूर्णांक fat_chain_add(काष्ठा inode *inode, पूर्णांक new_dclus, पूर्णांक nr_cluster);
बाह्य व्योम fat_समय_fat2unix(काष्ठा msकरोs_sb_info *sbi, काष्ठा बारpec64 *ts,
			      __le16 __समय, __le16 __date, u8 समय_cs);
बाह्य व्योम fat_समय_unix2fat(काष्ठा msकरोs_sb_info *sbi, काष्ठा बारpec64 *ts,
			      __le16 *समय, __le16 *date, u8 *समय_cs);
बाह्य पूर्णांक fat_truncate_समय(काष्ठा inode *inode, काष्ठा बारpec64 *now,
			     पूर्णांक flags);
बाह्य पूर्णांक fat_update_समय(काष्ठा inode *inode, काष्ठा बारpec64 *now,
			   पूर्णांक flags);
बाह्य पूर्णांक fat_sync_bhs(काष्ठा buffer_head **bhs, पूर्णांक nr_bhs);

पूर्णांक fat_cache_init(व्योम);
व्योम fat_cache_destroy(व्योम);

/* fat/nfs.c */
बाह्य स्थिर काष्ठा export_operations fat_export_ops;
बाह्य स्थिर काष्ठा export_operations fat_export_ops_nostale;

/* helper क्रम prपूर्णांकk */
प्रकार अचिन्हित दीर्घ दीर्घ	llu;

#पूर्ण_अगर /* !_FAT_H */
