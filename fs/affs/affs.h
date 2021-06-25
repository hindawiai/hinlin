<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश "amigaffs.h"
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>

/* Ugly macros make the code more pretty. */

#घोषणा GET_END_PTR(st,p,sz)		 ((st *)((अक्षर *)(p)+((sz)-माप(st))))
#घोषणा AFFS_GET_HASHENTRY(data,hashkey) be32_to_cpu(((काष्ठा dir_front *)data)->hashtable[hashkey])
#घोषणा AFFS_BLOCK(sb, bh, blk)		(AFFS_HEAD(bh)->table[AFFS_SB(sb)->s_hashsize-1-(blk)])

#घोषणा AFFS_HEAD(bh)		((काष्ठा affs_head *)(bh)->b_data)
#घोषणा AFFS_TAIL(sb, bh)	((काष्ठा affs_tail *)((bh)->b_data+(sb)->s_blocksize-माप(काष्ठा affs_tail)))
#घोषणा AFFS_ROOT_HEAD(bh)	((काष्ठा affs_root_head *)(bh)->b_data)
#घोषणा AFFS_ROOT_TAIL(sb, bh)	((काष्ठा affs_root_tail *)((bh)->b_data+(sb)->s_blocksize-माप(काष्ठा affs_root_tail)))
#घोषणा AFFS_DATA_HEAD(bh)	((काष्ठा affs_data_head *)(bh)->b_data)
#घोषणा AFFS_DATA(bh)		(((काष्ठा affs_data_head *)(bh)->b_data)->data)

#घोषणा AFFS_CACHE_SIZE		PAGE_SIZE

#घोषणा AFFS_LC_SIZE		(AFFS_CACHE_SIZE/माप(u32)/2)
#घोषणा AFFS_AC_SIZE		(AFFS_CACHE_SIZE/माप(काष्ठा affs_ext_key)/2)
#घोषणा AFFS_AC_MASK		(AFFS_AC_SIZE-1)

#घोषणा AFFSNAMEMAX 30U

काष्ठा affs_ext_key अणु
	u32	ext;				/* idx of the extended block */
	u32	key;				/* block number */
पूर्ण;

/*
 * affs fs inode data in memory
 */
काष्ठा affs_inode_info अणु
	atomic_t i_खोलोcnt;
	काष्ठा mutex i_link_lock;		/* Protects पूर्णांकernal inode access. */
	काष्ठा mutex i_ext_lock;		/* Protects पूर्णांकernal inode access. */
#घोषणा i_hash_lock i_ext_lock
	u32	 i_blkcnt;			/* block count */
	u32	 i_extcnt;			/* extended block count */
	u32	*i_lc;				/* linear cache of extended blocks */
	u32	 i_lc_size;
	u32	 i_lc_shअगरt;
	u32	 i_lc_mask;
	काष्ठा affs_ext_key *i_ac;		/* associative cache of extended blocks */
	u32	 i_ext_last;			/* last accessed extended block */
	काष्ठा buffer_head *i_ext_bh;		/* bh of last extended block */
	loff_t	 mmu_निजी;
	u32	 i_protect;			/* unused attribute bits */
	u32	 i_lastalloc;			/* last allocated block */
	पूर्णांक	 i_pa_cnt;			/* number of pपुनः_स्मृतिated blocks */
	काष्ठा inode vfs_inode;
पूर्ण;

/* लघु cut to get to the affs specअगरic inode data */
अटल अंतरभूत काष्ठा affs_inode_info *AFFS_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा affs_inode_info, vfs_inode);
पूर्ण

/*
 * super-block data in memory
 *
 * Block numbers are adjusted क्रम their actual size
 *
 */

काष्ठा affs_bm_info अणु
	u32 bm_key;			/* Disk block number */
	u32 bm_मुक्त;			/* Free blocks in here */
पूर्ण;

काष्ठा affs_sb_info अणु
	पूर्णांक s_partition_size;		/* Partition size in blocks. */
	पूर्णांक s_reserved;			/* Number of reserved blocks. */
	//u32 s_blksize;			/* Initial device blksize */
	u32 s_data_blksize;		/* size of the data block w/o header */
	u32 s_root_block;		/* FFS root block number. */
	पूर्णांक s_hashsize;			/* Size of hash table. */
	अचिन्हित दीर्घ s_flags;		/* See below. */
	kuid_t s_uid;			/* uid to override */
	kgid_t s_gid;			/* gid to override */
	umode_t s_mode;			/* mode to override */
	काष्ठा buffer_head *s_root_bh;	/* Cached root block. */
	काष्ठा mutex s_bmlock;		/* Protects biपंचांगap access. */
	काष्ठा affs_bm_info *s_biपंचांगap;	/* Biपंचांगap infos. */
	u32 s_bmap_count;		/* # of biपंचांगap blocks. */
	u32 s_bmap_bits;		/* # of bits in one biपंचांगap blocks */
	u32 s_last_bmap;
	काष्ठा buffer_head *s_bmap_bh;
	अक्षर *s_prefix;			/* Prefix क्रम volumes and assigns. */
	अक्षर s_volume[32];		/* Volume prefix क्रम असलolute symlinks. */
	spinlock_t symlink_lock;	/* protects the previous two */
	काष्ठा super_block *sb;		/* the VFS superblock object */
	पूर्णांक work_queued;		/* non-zero delayed work is queued */
	काष्ठा delayed_work sb_work;	/* superblock flush delayed work */
	spinlock_t work_lock;		/* protects sb_work and work_queued */
पूर्ण;

#घोषणा AFFS_MOUNT_SF_INTL		0x0001 /* International fileप्रणाली. */
#घोषणा AFFS_MOUNT_SF_BM_VALID		0x0002 /* Biपंचांगap is valid. */
#घोषणा AFFS_MOUNT_SF_IMMUTABLE		0x0004 /* Protection bits cannot be changed */
#घोषणा AFFS_MOUNT_SF_QUIET		0x0008 /* chmod errors will be not reported */
#घोषणा AFFS_MOUNT_SF_SETUID		0x0010 /* Ignore Amiga uid */
#घोषणा AFFS_MOUNT_SF_SETGID		0x0020 /* Ignore Amiga gid */
#घोषणा AFFS_MOUNT_SF_SETMODE		0x0040 /* Ignore Amiga protection bits */
#घोषणा AFFS_MOUNT_SF_MUFS		0x0100 /* Use MUFS uid/gid mapping */
#घोषणा AFFS_MOUNT_SF_OFS		0x0200 /* Old fileप्रणाली */
#घोषणा AFFS_MOUNT_SF_PREFIX		0x0400 /* Buffer क्रम prefix is allocated */
#घोषणा AFFS_MOUNT_SF_VERBOSE		0x0800 /* Talk about fs when mounting */
#घोषणा AFFS_MOUNT_SF_NO_TRUNCATE	0x1000 /* Don't truncate filenames */

#घोषणा affs_clear_opt(o, opt)    (o &= ~AFFS_MOUNT_##opt)
#घोषणा affs_set_opt(o, opt)      (o |= AFFS_MOUNT_##opt)
#घोषणा affs_test_opt(o, opt)     ((o) & AFFS_MOUNT_##opt)

/* लघु cut to get to the affs specअगरic sb data */
अटल अंतरभूत काष्ठा affs_sb_info *AFFS_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

व्योम affs_mark_sb_dirty(काष्ठा super_block *sb);

/* amigaffs.c */

बाह्य पूर्णांक	affs_insert_hash(काष्ठा inode *inode, काष्ठा buffer_head *bh);
बाह्य पूर्णांक	affs_हटाओ_hash(काष्ठा inode *dir, काष्ठा buffer_head *rem_bh);
बाह्य पूर्णांक	affs_हटाओ_header(काष्ठा dentry *dentry);
बाह्य u32	affs_checksum_block(काष्ठा super_block *sb, काष्ठा buffer_head *bh);
बाह्य व्योम	affs_fix_checksum(काष्ठा super_block *sb, काष्ठा buffer_head *bh);
बाह्य व्योम	affs_secs_to_datestamp(समय64_t secs, काष्ठा affs_date *ds);
बाह्य umode_t	affs_prot_to_mode(u32 prot);
बाह्य व्योम	affs_mode_to_prot(काष्ठा inode *inode);
__म_लिखो(3, 4)
बाह्य व्योम	affs_error(काष्ठा super_block *sb, स्थिर अक्षर *function,
			   स्थिर अक्षर *fmt, ...);
__म_लिखो(3, 4)
बाह्य व्योम	affs_warning(काष्ठा super_block *sb, स्थिर अक्षर *function,
			     स्थिर अक्षर *fmt, ...);
बाह्य bool	affs_nofilenametruncate(स्थिर काष्ठा dentry *dentry);
बाह्य पूर्णांक	affs_check_name(स्थिर अचिन्हित अक्षर *name, पूर्णांक len,
				bool notruncate);
बाह्य पूर्णांक	affs_copy_name(अचिन्हित अक्षर *bstr, काष्ठा dentry *dentry);

/* biपंचांगap. c */

बाह्य u32	affs_count_मुक्त_blocks(काष्ठा super_block *s);
बाह्य व्योम	affs_मुक्त_block(काष्ठा super_block *sb, u32 block);
बाह्य u32	affs_alloc_block(काष्ठा inode *inode, u32 goal);
बाह्य पूर्णांक	affs_init_biपंचांगap(काष्ठा super_block *sb, पूर्णांक *flags);
बाह्य व्योम	affs_मुक्त_biपंचांगap(काष्ठा super_block *sb);

/* namei.c */

बाह्य स्थिर काष्ठा export_operations affs_export_ops;
बाह्य पूर्णांक	affs_hash_name(काष्ठा super_block *sb, स्थिर u8 *name, अचिन्हित पूर्णांक len);
बाह्य काष्ठा dentry *affs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक);
बाह्य पूर्णांक	affs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry);
बाह्य पूर्णांक	affs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, umode_t mode, bool);
बाह्य पूर्णांक	affs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, umode_t mode);
बाह्य पूर्णांक	affs_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry);
बाह्य पूर्णांक	affs_link(काष्ठा dentry *olddentry, काष्ठा inode *dir,
			  काष्ठा dentry *dentry);
बाह्य पूर्णांक	affs_symlink(काष्ठा user_namespace *mnt_userns,
			काष्ठा inode *dir, काष्ठा dentry *dentry,
			स्थिर अक्षर *symname);
बाह्य पूर्णांक	affs_नाम2(काष्ठा user_namespace *mnt_userns,
			काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			अचिन्हित पूर्णांक flags);

/* inode.c */

बाह्य काष्ठा inode		*affs_new_inode(काष्ठा inode *dir);
बाह्य पूर्णांक			 affs_notअगरy_change(काष्ठा user_namespace *mnt_userns,
					काष्ठा dentry *dentry, काष्ठा iattr *attr);
बाह्य व्योम			 affs_evict_inode(काष्ठा inode *inode);
बाह्य काष्ठा inode		*affs_iget(काष्ठा super_block *sb,
					अचिन्हित दीर्घ ino);
बाह्य पूर्णांक			 affs_ग_लिखो_inode(काष्ठा inode *inode,
					काष्ठा ग_लिखोback_control *wbc);
बाह्य पूर्णांक			 affs_add_entry(काष्ठा inode *dir, काष्ठा inode *inode,
					काष्ठा dentry *dentry, s32 type);

/* file.c */

व्योम		affs_मुक्त_pपुनः_स्मृति(काष्ठा inode *inode);
बाह्य व्योम	affs_truncate(काष्ठा inode *);
पूर्णांक		affs_file_fsync(काष्ठा file *, loff_t, loff_t, पूर्णांक);

/* dir.c */

बाह्य व्योम   affs_dir_truncate(काष्ठा inode *);

/* jump tables */

बाह्य स्थिर काष्ठा inode_operations	 affs_file_inode_operations;
बाह्य स्थिर काष्ठा inode_operations	 affs_dir_inode_operations;
बाह्य स्थिर काष्ठा inode_operations   affs_symlink_inode_operations;
बाह्य स्थिर काष्ठा file_operations	 affs_file_operations;
बाह्य स्थिर काष्ठा file_operations	 affs_file_operations_ofs;
बाह्य स्थिर काष्ठा file_operations	 affs_dir_operations;
बाह्य स्थिर काष्ठा address_space_operations	 affs_symlink_aops;
बाह्य स्थिर काष्ठा address_space_operations	 affs_aops;
बाह्य स्थिर काष्ठा address_space_operations	 affs_aops_ofs;

बाह्य स्थिर काष्ठा dentry_operations	 affs_dentry_operations;
बाह्य स्थिर काष्ठा dentry_operations	 affs_पूर्णांकl_dentry_operations;

अटल अंतरभूत bool affs_validblock(काष्ठा super_block *sb, पूर्णांक block)
अणु
	वापस(block >= AFFS_SB(sb)->s_reserved &&
	       block < AFFS_SB(sb)->s_partition_size);
पूर्ण

अटल अंतरभूत व्योम
affs_set_blocksize(काष्ठा super_block *sb, पूर्णांक size)
अणु
	sb_set_blocksize(sb, size);
पूर्ण
अटल अंतरभूत काष्ठा buffer_head *
affs_bपढ़ो(काष्ठा super_block *sb, पूर्णांक block)
अणु
	pr_debug("%s: %d\n", __func__, block);
	अगर (affs_validblock(sb, block))
		वापस sb_bपढ़ो(sb, block);
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा buffer_head *
affs_getblk(काष्ठा super_block *sb, पूर्णांक block)
अणु
	pr_debug("%s: %d\n", __func__, block);
	अगर (affs_validblock(sb, block))
		वापस sb_getblk(sb, block);
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा buffer_head *
affs_getzeroblk(काष्ठा super_block *sb, पूर्णांक block)
अणु
	काष्ठा buffer_head *bh;
	pr_debug("%s: %d\n", __func__, block);
	अगर (affs_validblock(sb, block)) अणु
		bh = sb_getblk(sb, block);
		lock_buffer(bh);
		स_रखो(bh->b_data, 0 , sb->s_blocksize);
		set_buffer_uptodate(bh);
		unlock_buffer(bh);
		वापस bh;
	पूर्ण
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा buffer_head *
affs_getemptyblk(काष्ठा super_block *sb, पूर्णांक block)
अणु
	काष्ठा buffer_head *bh;
	pr_debug("%s: %d\n", __func__, block);
	अगर (affs_validblock(sb, block)) अणु
		bh = sb_getblk(sb, block);
		रुको_on_buffer(bh);
		set_buffer_uptodate(bh);
		वापस bh;
	पूर्ण
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम
affs_brअन्यथा(काष्ठा buffer_head *bh)
अणु
	अगर (bh)
		pr_debug("%s: %lld\n", __func__, (दीर्घ दीर्घ) bh->b_blocknr);
	brअन्यथा(bh);
पूर्ण

अटल अंतरभूत व्योम
affs_adjust_checksum(काष्ठा buffer_head *bh, u32 val)
अणु
	u32 पंचांगp = be32_to_cpu(((__be32 *)bh->b_data)[5]);
	((__be32 *)bh->b_data)[5] = cpu_to_be32(पंचांगp - val);
पूर्ण
अटल अंतरभूत व्योम
affs_adjust_biपंचांगapchecksum(काष्ठा buffer_head *bh, u32 val)
अणु
	u32 पंचांगp = be32_to_cpu(((__be32 *)bh->b_data)[0]);
	((__be32 *)bh->b_data)[0] = cpu_to_be32(पंचांगp - val);
पूर्ण

अटल अंतरभूत व्योम
affs_lock_link(काष्ठा inode *inode)
अणु
	mutex_lock(&AFFS_I(inode)->i_link_lock);
पूर्ण
अटल अंतरभूत व्योम
affs_unlock_link(काष्ठा inode *inode)
अणु
	mutex_unlock(&AFFS_I(inode)->i_link_lock);
पूर्ण
अटल अंतरभूत व्योम
affs_lock_dir(काष्ठा inode *inode)
अणु
	mutex_lock_nested(&AFFS_I(inode)->i_hash_lock, SINGLE_DEPTH_NESTING);
पूर्ण
अटल अंतरभूत व्योम
affs_unlock_dir(काष्ठा inode *inode)
अणु
	mutex_unlock(&AFFS_I(inode)->i_hash_lock);
पूर्ण
अटल अंतरभूत व्योम
affs_lock_ext(काष्ठा inode *inode)
अणु
	mutex_lock(&AFFS_I(inode)->i_ext_lock);
पूर्ण
अटल अंतरभूत व्योम
affs_unlock_ext(काष्ठा inode *inode)
अणु
	mutex_unlock(&AFFS_I(inode)->i_ext_lock);
पूर्ण
