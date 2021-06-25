<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/include/linux/hfsplus_fs.h
 *
 * Copyright (C) 1999
 * Brad Boyer (flar@pants.nu)
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 *
 */

#अगर_अघोषित _LINUX_HFSPLUS_FS_H
#घोषणा _LINUX_HFSPLUS_FS_H

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/fs.h>
#समावेश <linux/mutex.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/blkdev.h>
#समावेश "hfsplus_raw.h"

#घोषणा DBG_BNODE_REFS	0x00000001
#घोषणा DBG_BNODE_MOD	0x00000002
#घोषणा DBG_CAT_MOD	0x00000004
#घोषणा DBG_INODE	0x00000008
#घोषणा DBG_SUPER	0x00000010
#घोषणा DBG_EXTENT	0x00000020
#घोषणा DBG_BITMAP	0x00000040
#घोषणा DBG_ATTR_MOD	0x00000080

#अगर 0
#घोषणा DBG_MASK	(DBG_EXTENT|DBG_INODE|DBG_BNODE_MOD)
#घोषणा DBG_MASK	(DBG_BNODE_MOD|DBG_CAT_MOD|DBG_INODE)
#घोषणा DBG_MASK	(DBG_CAT_MOD|DBG_BNODE_REFS|DBG_INODE|DBG_EXTENT)
#पूर्ण_अगर
#घोषणा DBG_MASK	(0)

#घोषणा hfs_dbg(flg, fmt, ...)					\
करो अणु								\
	अगर (DBG_##flg & DBG_MASK)				\
		prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा hfs_dbg_cont(flg, fmt, ...)				\
करो अणु								\
	अगर (DBG_##flg & DBG_MASK)				\
		pr_cont(fmt, ##__VA_ARGS__);			\
पूर्ण जबतक (0)

/* Runसमय config options */
#घोषणा HFSPLUS_DEF_CR_TYPE    0x3F3F3F3F  /* '????' */

#घोषणा HFSPLUS_TYPE_DATA 0x00
#घोषणा HFSPLUS_TYPE_RSRC 0xFF

प्रकार पूर्णांक (*btree_keycmp)(स्थिर hfsplus_btree_key *,
		स्थिर hfsplus_btree_key *);

#घोषणा NODE_HASH_SIZE	256

/* B-tree mutex nested subclasses */
क्रमागत hfsplus_btree_mutex_classes अणु
	CATALOG_BTREE_MUTEX,
	EXTENTS_BTREE_MUTEX,
	ATTR_BTREE_MUTEX,
पूर्ण;

/* An HFS+ BTree held in memory */
काष्ठा hfs_btree अणु
	काष्ठा super_block *sb;
	काष्ठा inode *inode;
	btree_keycmp keycmp;

	u32 cnid;
	u32 root;
	u32 leaf_count;
	u32 leaf_head;
	u32 leaf_tail;
	u32 node_count;
	u32 मुक्त_nodes;
	u32 attributes;

	अचिन्हित पूर्णांक node_size;
	अचिन्हित पूर्णांक node_size_shअगरt;
	अचिन्हित पूर्णांक max_key_len;
	अचिन्हित पूर्णांक depth;

	काष्ठा mutex tree_lock;

	अचिन्हित पूर्णांक pages_per_bnode;
	spinlock_t hash_lock;
	काष्ठा hfs_bnode *node_hash[NODE_HASH_SIZE];
	पूर्णांक node_hash_cnt;
पूर्ण;

काष्ठा page;

/* An HFS+ BTree node in memory */
काष्ठा hfs_bnode अणु
	काष्ठा hfs_btree *tree;

	u32 prev;
	u32 this;
	u32 next;
	u32 parent;

	u16 num_recs;
	u8 type;
	u8 height;

	काष्ठा hfs_bnode *next_hash;
	अचिन्हित दीर्घ flags;
	रुको_queue_head_t lock_wq;
	atomic_t refcnt;
	अचिन्हित पूर्णांक page_offset;
	काष्ठा page *page[];
पूर्ण;

#घोषणा HFS_BNODE_LOCK		0
#घोषणा HFS_BNODE_ERROR		1
#घोषणा HFS_BNODE_NEW		2
#घोषणा HFS_BNODE_सूचीTY		3
#घोषणा HFS_BNODE_DELETED	4

/*
 * Attributes file states
 */
#घोषणा HFSPLUS_EMPTY_ATTR_TREE		0
#घोषणा HFSPLUS_CREATING_ATTR_TREE	1
#घोषणा HFSPLUS_VALID_ATTR_TREE		2
#घोषणा HFSPLUS_FAILED_ATTR_TREE	3

/*
 * HFS+ superblock info (built from Volume Header on disk)
 */

काष्ठा hfsplus_vh;
काष्ठा hfs_btree;

काष्ठा hfsplus_sb_info अणु
	व्योम *s_vhdr_buf;
	काष्ठा hfsplus_vh *s_vhdr;
	व्योम *s_backup_vhdr_buf;
	काष्ठा hfsplus_vh *s_backup_vhdr;
	काष्ठा hfs_btree *ext_tree;
	काष्ठा hfs_btree *cat_tree;
	काष्ठा hfs_btree *attr_tree;
	atomic_t attr_tree_state;
	काष्ठा inode *alloc_file;
	काष्ठा inode *hidden_dir;
	काष्ठा nls_table *nls;

	/* Runसमय variables */
	u32 blockoffset;
	sector_t part_start;
	sector_t sect_count;
	पूर्णांक fs_shअगरt;

	/* immutable data from the volume header */
	u32 alloc_blksz;
	पूर्णांक alloc_blksz_shअगरt;
	u32 total_blocks;
	u32 data_clump_blocks, rsrc_clump_blocks;

	/* mutable data from the volume header, रक्षित by alloc_mutex */
	u32 मुक्त_blocks;
	काष्ठा mutex alloc_mutex;

	/* mutable data from the volume header, रक्षित by vh_mutex */
	u32 next_cnid;
	u32 file_count;
	u32 folder_count;
	काष्ठा mutex vh_mutex;

	/* Config options */
	u32 creator;
	u32 type;

	umode_t umask;
	kuid_t uid;
	kgid_t gid;

	पूर्णांक part, session;
	अचिन्हित दीर्घ flags;

	पूर्णांक work_queued;               /* non-zero delayed work is queued */
	काष्ठा delayed_work sync_work; /* FS sync delayed work */
	spinlock_t work_lock;          /* protects sync_work and work_queued */
पूर्ण;

#घोषणा HFSPLUS_SB_WRITEBACKUP	0
#घोषणा HFSPLUS_SB_NODECOMPOSE	1
#घोषणा HFSPLUS_SB_FORCE	2
#घोषणा HFSPLUS_SB_HFSX		3
#घोषणा HFSPLUS_SB_CASEFOLD	4
#घोषणा HFSPLUS_SB_NOBARRIER	5

अटल अंतरभूत काष्ठा hfsplus_sb_info *HFSPLUS_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण


काष्ठा hfsplus_inode_info अणु
	atomic_t खोलोcnt;

	/*
	 * Extent allocation inक्रमmation, रक्षित by extents_lock.
	 */
	u32 first_blocks;
	u32 clump_blocks;
	u32 alloc_blocks;
	u32 cached_start;
	u32 cached_blocks;
	hfsplus_extent_rec first_extents;
	hfsplus_extent_rec cached_extents;
	अचिन्हित पूर्णांक extent_state;
	काष्ठा mutex extents_lock;

	/*
	 * Immutable data.
	 */
	काष्ठा inode *rsrc_inode;
	__be32 create_date;

	/*
	 * Protected by sbi->vh_mutex.
	 */
	u32 linkid;

	/*
	 * Accessed using atomic bitops.
	 */
	अचिन्हित दीर्घ flags;

	/*
	 * Protected by i_mutex.
	 */
	sector_t fs_blocks;
	u8 userflags;		/* BSD user file flags */
	u32 subfolders;		/* Subfolder count (HFSX only) */
	काष्ठा list_head खोलो_dir_list;
	spinlock_t खोलो_dir_lock;
	loff_t phys_size;

	काष्ठा inode vfs_inode;
पूर्ण;

#घोषणा HFSPLUS_EXT_सूचीTY	0x0001
#घोषणा HFSPLUS_EXT_NEW		0x0002

#घोषणा HFSPLUS_I_RSRC		0	/* represents a resource विभाजन */
#घोषणा HFSPLUS_I_CAT_सूचीTY	1	/* has changes in the catalog tree */
#घोषणा HFSPLUS_I_EXT_सूचीTY	2	/* has changes in the extent tree */
#घोषणा HFSPLUS_I_ALLOC_सूचीTY	3	/* has changes in the allocation file */
#घोषणा HFSPLUS_I_ATTR_सूचीTY	4	/* has changes in the attributes tree */

#घोषणा HFSPLUS_IS_RSRC(inode) \
	test_bit(HFSPLUS_I_RSRC, &HFSPLUS_I(inode)->flags)

अटल अंतरभूत काष्ठा hfsplus_inode_info *HFSPLUS_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा hfsplus_inode_info, vfs_inode);
पूर्ण

/*
 * Mark an inode dirty, and also mark the btree in which the
 * specअगरic type of metadata is stored.
 * For data or metadata that माला_लो written back by पूर्णांकo the catalog btree
 * by hfsplus_ग_लिखो_inode a plain mark_inode_dirty call is enough.
 */
अटल अंतरभूत व्योम hfsplus_mark_inode_dirty(काष्ठा inode *inode,
		अचिन्हित पूर्णांक flag)
अणु
	set_bit(flag, &HFSPLUS_I(inode)->flags);
	mark_inode_dirty(inode);
पूर्ण

काष्ठा hfs_find_data अणु
	/* filled by caller */
	hfsplus_btree_key *search_key;
	hfsplus_btree_key *key;
	/* filled by find */
	काष्ठा hfs_btree *tree;
	काष्ठा hfs_bnode *bnode;
	/* filled by findrec */
	पूर्णांक record;
	पूर्णांक keyoffset, keylength;
	पूर्णांक entryoffset, entrylength;
पूर्ण;

काष्ठा hfsplus_सूची_पढ़ो_data अणु
	काष्ठा list_head list;
	काष्ठा file *file;
	काष्ठा hfsplus_cat_key key;
पूर्ण;

/*
 * Find minimum acceptible I/O size क्रम an hfsplus sb.
 */
अटल अंतरभूत अचिन्हित लघु hfsplus_min_io_size(काष्ठा super_block *sb)
अणु
	वापस max_t(अचिन्हित लघु, bdev_logical_block_size(sb->s_bdev),
		     HFSPLUS_SECTOR_SIZE);
पूर्ण

#घोषणा hfs_btree_खोलो hfsplus_btree_खोलो
#घोषणा hfs_btree_बंद hfsplus_btree_बंद
#घोषणा hfs_btree_ग_लिखो hfsplus_btree_ग_लिखो
#घोषणा hfs_bmap_reserve hfsplus_bmap_reserve
#घोषणा hfs_bmap_alloc hfsplus_bmap_alloc
#घोषणा hfs_bmap_मुक्त hfsplus_bmap_मुक्त
#घोषणा hfs_bnode_पढ़ो hfsplus_bnode_पढ़ो
#घोषणा hfs_bnode_पढ़ो_u16 hfsplus_bnode_पढ़ो_u16
#घोषणा hfs_bnode_पढ़ो_u8 hfsplus_bnode_पढ़ो_u8
#घोषणा hfs_bnode_पढ़ो_key hfsplus_bnode_पढ़ो_key
#घोषणा hfs_bnode_ग_लिखो hfsplus_bnode_ग_लिखो
#घोषणा hfs_bnode_ग_लिखो_u16 hfsplus_bnode_ग_लिखो_u16
#घोषणा hfs_bnode_clear hfsplus_bnode_clear
#घोषणा hfs_bnode_copy hfsplus_bnode_copy
#घोषणा hfs_bnode_move hfsplus_bnode_move
#घोषणा hfs_bnode_dump hfsplus_bnode_dump
#घोषणा hfs_bnode_unlink hfsplus_bnode_unlink
#घोषणा hfs_bnode_findhash hfsplus_bnode_findhash
#घोषणा hfs_bnode_find hfsplus_bnode_find
#घोषणा hfs_bnode_unhash hfsplus_bnode_unhash
#घोषणा hfs_bnode_मुक्त hfsplus_bnode_मुक्त
#घोषणा hfs_bnode_create hfsplus_bnode_create
#घोषणा hfs_bnode_get hfsplus_bnode_get
#घोषणा hfs_bnode_put hfsplus_bnode_put
#घोषणा hfs_brec_lenoff hfsplus_brec_lenoff
#घोषणा hfs_brec_keylen hfsplus_brec_keylen
#घोषणा hfs_brec_insert hfsplus_brec_insert
#घोषणा hfs_brec_हटाओ hfsplus_brec_हटाओ
#घोषणा hfs_find_init hfsplus_find_init
#घोषणा hfs_find_निकास hfsplus_find_निकास
#घोषणा __hfs_brec_find __hfsplus_brec_find
#घोषणा hfs_brec_find hfsplus_brec_find
#घोषणा hfs_brec_पढ़ो hfsplus_brec_पढ़ो
#घोषणा hfs_brec_जाओ hfsplus_brec_जाओ
#घोषणा hfs_part_find hfsplus_part_find

/*
 * hfs+-specअगरic ioctl क्रम making the fileप्रणाली bootable
 */
#घोषणा HFSPLUS_IOC_BLESS _IO('h', 0x80)

प्रकार पूर्णांक (*search_strategy_t)(काष्ठा hfs_bnode *,
				काष्ठा hfs_find_data *,
				पूर्णांक *, पूर्णांक *, पूर्णांक *);

/*
 * Functions in any *.c used in other files
 */

/* attributes.c */
पूर्णांक __init hfsplus_create_attr_tree_cache(व्योम);
व्योम hfsplus_destroy_attr_tree_cache(व्योम);
पूर्णांक hfsplus_attr_bin_cmp_key(स्थिर hfsplus_btree_key *k1,
			     स्थिर hfsplus_btree_key *k2);
पूर्णांक hfsplus_attr_build_key(काष्ठा super_block *sb, hfsplus_btree_key *key,
			   u32 cnid, स्थिर अक्षर *name);
hfsplus_attr_entry *hfsplus_alloc_attr_entry(व्योम);
व्योम hfsplus_destroy_attr_entry(hfsplus_attr_entry *entry);
पूर्णांक hfsplus_find_attr(काष्ठा super_block *sb, u32 cnid, स्थिर अक्षर *name,
		      काष्ठा hfs_find_data *fd);
पूर्णांक hfsplus_attr_exists(काष्ठा inode *inode, स्थिर अक्षर *name);
पूर्णांक hfsplus_create_attr(काष्ठा inode *inode, स्थिर अक्षर *name,
			स्थिर व्योम *value, माप_प्रकार size);
पूर्णांक hfsplus_delete_attr(काष्ठा inode *inode, स्थिर अक्षर *name);
पूर्णांक hfsplus_delete_all_attrs(काष्ठा inode *dir, u32 cnid);

/* biपंचांगap.c */
पूर्णांक hfsplus_block_allocate(काष्ठा super_block *sb, u32 size, u32 offset,
			   u32 *max);
पूर्णांक hfsplus_block_मुक्त(काष्ठा super_block *sb, u32 offset, u32 count);

/* btree.c */
u32 hfsplus_calc_btree_clump_size(u32 block_size, u32 node_size, u64 sectors,
				  पूर्णांक file_id);
काष्ठा hfs_btree *hfs_btree_खोलो(काष्ठा super_block *sb, u32 id);
व्योम hfs_btree_बंद(काष्ठा hfs_btree *tree);
पूर्णांक hfs_btree_ग_लिखो(काष्ठा hfs_btree *tree);
पूर्णांक hfs_bmap_reserve(काष्ठा hfs_btree *tree, पूर्णांक rsvd_nodes);
काष्ठा hfs_bnode *hfs_bmap_alloc(काष्ठा hfs_btree *tree);
व्योम hfs_bmap_मुक्त(काष्ठा hfs_bnode *node);

/* bnode.c */
व्योम hfs_bnode_पढ़ो(काष्ठा hfs_bnode *node, व्योम *buf, पूर्णांक off, पूर्णांक len);
u16 hfs_bnode_पढ़ो_u16(काष्ठा hfs_bnode *node, पूर्णांक off);
u8 hfs_bnode_पढ़ो_u8(काष्ठा hfs_bnode *node, पूर्णांक off);
व्योम hfs_bnode_पढ़ो_key(काष्ठा hfs_bnode *node, व्योम *key, पूर्णांक off);
व्योम hfs_bnode_ग_लिखो(काष्ठा hfs_bnode *node, व्योम *buf, पूर्णांक off, पूर्णांक len);
व्योम hfs_bnode_ग_लिखो_u16(काष्ठा hfs_bnode *node, पूर्णांक off, u16 data);
व्योम hfs_bnode_clear(काष्ठा hfs_bnode *node, पूर्णांक off, पूर्णांक len);
व्योम hfs_bnode_copy(काष्ठा hfs_bnode *dst_node, पूर्णांक dst,
		    काष्ठा hfs_bnode *src_node, पूर्णांक src, पूर्णांक len);
व्योम hfs_bnode_move(काष्ठा hfs_bnode *node, पूर्णांक dst, पूर्णांक src, पूर्णांक len);
व्योम hfs_bnode_dump(काष्ठा hfs_bnode *node);
व्योम hfs_bnode_unlink(काष्ठा hfs_bnode *node);
काष्ठा hfs_bnode *hfs_bnode_findhash(काष्ठा hfs_btree *tree, u32 cnid);
व्योम hfs_bnode_unhash(काष्ठा hfs_bnode *node);
काष्ठा hfs_bnode *hfs_bnode_find(काष्ठा hfs_btree *tree, u32 num);
व्योम hfs_bnode_मुक्त(काष्ठा hfs_bnode *node);
काष्ठा hfs_bnode *hfs_bnode_create(काष्ठा hfs_btree *tree, u32 num);
व्योम hfs_bnode_get(काष्ठा hfs_bnode *node);
व्योम hfs_bnode_put(काष्ठा hfs_bnode *node);
bool hfs_bnode_need_zeroout(काष्ठा hfs_btree *tree);

/* brec.c */
u16 hfs_brec_lenoff(काष्ठा hfs_bnode *node, u16 rec, u16 *off);
u16 hfs_brec_keylen(काष्ठा hfs_bnode *node, u16 rec);
पूर्णांक hfs_brec_insert(काष्ठा hfs_find_data *fd, व्योम *entry, पूर्णांक entry_len);
पूर्णांक hfs_brec_हटाओ(काष्ठा hfs_find_data *fd);

/* bfind.c */
पूर्णांक hfs_find_init(काष्ठा hfs_btree *tree, काष्ठा hfs_find_data *fd);
व्योम hfs_find_निकास(काष्ठा hfs_find_data *fd);
पूर्णांक hfs_find_1st_rec_by_cnid(काष्ठा hfs_bnode *bnode, काष्ठा hfs_find_data *fd,
			     पूर्णांक *begin, पूर्णांक *end, पूर्णांक *cur_rec);
पूर्णांक hfs_find_rec_by_key(काष्ठा hfs_bnode *bnode, काष्ठा hfs_find_data *fd,
			पूर्णांक *begin, पूर्णांक *end, पूर्णांक *cur_rec);
पूर्णांक __hfs_brec_find(काष्ठा hfs_bnode *bnode, काष्ठा hfs_find_data *fd,
		    search_strategy_t rec_found);
पूर्णांक hfs_brec_find(काष्ठा hfs_find_data *fd, search_strategy_t करो_key_compare);
पूर्णांक hfs_brec_पढ़ो(काष्ठा hfs_find_data *fd, व्योम *rec, पूर्णांक rec_len);
पूर्णांक hfs_brec_जाओ(काष्ठा hfs_find_data *fd, पूर्णांक cnt);

/* catalog.c */
पूर्णांक hfsplus_cat_हाल_cmp_key(स्थिर hfsplus_btree_key *k1,
			     स्थिर hfsplus_btree_key *k2);
पूर्णांक hfsplus_cat_bin_cmp_key(स्थिर hfsplus_btree_key *k1,
			    स्थिर hfsplus_btree_key *k2);
पूर्णांक hfsplus_cat_build_key(काष्ठा super_block *sb, hfsplus_btree_key *key,
			   u32 parent, स्थिर काष्ठा qstr *str);
व्योम hfsplus_cat_build_key_with_cnid(काष्ठा super_block *sb,
				     hfsplus_btree_key *key, u32 parent);
व्योम hfsplus_cat_set_perms(काष्ठा inode *inode, काष्ठा hfsplus_perm *perms);
पूर्णांक hfsplus_find_cat(काष्ठा super_block *sb, u32 cnid,
		     काष्ठा hfs_find_data *fd);
पूर्णांक hfsplus_create_cat(u32 cnid, काष्ठा inode *dir, स्थिर काष्ठा qstr *str,
		       काष्ठा inode *inode);
पूर्णांक hfsplus_delete_cat(u32 cnid, काष्ठा inode *dir, स्थिर काष्ठा qstr *str);
पूर्णांक hfsplus_नाम_cat(u32 cnid, काष्ठा inode *src_dir, स्थिर काष्ठा qstr *src_name,
		       काष्ठा inode *dst_dir, स्थिर काष्ठा qstr *dst_name);

/* dir.c */
बाह्य स्थिर काष्ठा inode_operations hfsplus_dir_inode_operations;
बाह्य स्थिर काष्ठा file_operations hfsplus_dir_operations;

/* extents.c */
पूर्णांक hfsplus_ext_cmp_key(स्थिर hfsplus_btree_key *k1,
			स्थिर hfsplus_btree_key *k2);
पूर्णांक hfsplus_ext_ग_लिखो_extent(काष्ठा inode *inode);
पूर्णांक hfsplus_get_block(काष्ठा inode *inode, sector_t iblock,
		      काष्ठा buffer_head *bh_result, पूर्णांक create);
पूर्णांक hfsplus_मुक्त_विभाजन(काष्ठा super_block *sb, u32 cnid,
		      काष्ठा hfsplus_विभाजन_raw *विभाजन, पूर्णांक type);
पूर्णांक hfsplus_file_extend(काष्ठा inode *inode, bool zeroout);
व्योम hfsplus_file_truncate(काष्ठा inode *inode);

/* inode.c */
बाह्य स्थिर काष्ठा address_space_operations hfsplus_aops;
बाह्य स्थिर काष्ठा address_space_operations hfsplus_btree_aops;
बाह्य स्थिर काष्ठा dentry_operations hfsplus_dentry_operations;

काष्ठा inode *hfsplus_new_inode(काष्ठा super_block *sb, काष्ठा inode *dir,
				umode_t mode);
व्योम hfsplus_delete_inode(काष्ठा inode *inode);
व्योम hfsplus_inode_पढ़ो_विभाजन(काष्ठा inode *inode,
			     काष्ठा hfsplus_विभाजन_raw *विभाजन);
व्योम hfsplus_inode_ग_लिखो_विभाजन(काष्ठा inode *inode,
			      काष्ठा hfsplus_विभाजन_raw *विभाजन);
पूर्णांक hfsplus_cat_पढ़ो_inode(काष्ठा inode *inode, काष्ठा hfs_find_data *fd);
पूर्णांक hfsplus_cat_ग_लिखो_inode(काष्ठा inode *inode);
पूर्णांक hfsplus_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		    काष्ठा kstat *stat, u32 request_mask,
		    अचिन्हित पूर्णांक query_flags);
पूर्णांक hfsplus_file_fsync(काष्ठा file *file, loff_t start, loff_t end,
		       पूर्णांक datasync);
पूर्णांक hfsplus_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa);
पूर्णांक hfsplus_fileattr_set(काष्ठा user_namespace *mnt_userns,
			 काष्ठा dentry *dentry, काष्ठा fileattr *fa);

/* ioctl.c */
दीर्घ hfsplus_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

/* options.c */
व्योम hfsplus_fill_शेषs(काष्ठा hfsplus_sb_info *opts);
पूर्णांक hfsplus_parse_options_remount(अक्षर *input, पूर्णांक *क्रमce);
पूर्णांक hfsplus_parse_options(अक्षर *input, काष्ठा hfsplus_sb_info *sbi);
पूर्णांक hfsplus_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root);

/* part_tbl.c */
पूर्णांक hfs_part_find(काष्ठा super_block *sb, sector_t *part_start,
		  sector_t *part_size);

/* super.c */
काष्ठा inode *hfsplus_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ ino);
व्योम hfsplus_mark_mdb_dirty(काष्ठा super_block *sb);

/* tables.c */
बाह्य u16 hfsplus_हाल_fold_table[];
बाह्य u16 hfsplus_decompose_table[];
बाह्य u16 hfsplus_compose_table[];

/* unicode.c */
पूर्णांक hfsplus_strहालcmp(स्थिर काष्ठा hfsplus_unistr *s1,
		       स्थिर काष्ठा hfsplus_unistr *s2);
पूर्णांक hfsplus_म_भेद(स्थिर काष्ठा hfsplus_unistr *s1,
		   स्थिर काष्ठा hfsplus_unistr *s2);
पूर्णांक hfsplus_uni2asc(काष्ठा super_block *sb, स्थिर काष्ठा hfsplus_unistr *ustr,
		    अक्षर *astr, पूर्णांक *len_p);
पूर्णांक hfsplus_asc2uni(काष्ठा super_block *sb, काष्ठा hfsplus_unistr *ustr,
		    पूर्णांक max_unistr_len, स्थिर अक्षर *astr, पूर्णांक len);
पूर्णांक hfsplus_hash_dentry(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *str);
पूर्णांक hfsplus_compare_dentry(स्थिर काष्ठा dentry *dentry, अचिन्हित पूर्णांक len,
			   स्थिर अक्षर *str, स्थिर काष्ठा qstr *name);

/* wrapper.c */
पूर्णांक hfsplus_submit_bio(काष्ठा super_block *sb, sector_t sector, व्योम *buf,
		       व्योम **data, पूर्णांक op, पूर्णांक op_flags);
पूर्णांक hfsplus_पढ़ो_wrapper(काष्ठा super_block *sb);

/*
 * समय helpers: convert between 1904-base and 1970-base बारtamps
 *
 * HFS+ implementations are highly inconsistent, this one matches the
 * traditional behavior of 64-bit Linux, giving the most useful
 * समय range between 1970 and 2106, by treating any on-disk बारtamp
 * under HFSPLUS_UTC_OFFSET (Jan 1 1970) as a समय between 2040 and 2106.
 */
#घोषणा HFSPLUS_UTC_OFFSET 2082844800U

अटल अंतरभूत समय64_t __hfsp_mt2ut(__be32 mt)
अणु
	समय64_t ut = (u32)(be32_to_cpu(mt) - HFSPLUS_UTC_OFFSET);

	वापस ut;
पूर्ण

अटल अंतरभूत __be32 __hfsp_ut2mt(समय64_t ut)
अणु
	वापस cpu_to_be32(lower_32_bits(ut) + HFSPLUS_UTC_OFFSET);
पूर्ण

/* compatibility */
#घोषणा hfsp_mt2ut(t)		(काष्ठा बारpec64)अणु .tv_sec = __hfsp_mt2ut(t) पूर्ण
#घोषणा hfsp_ut2mt(t)		__hfsp_ut2mt((t).tv_sec)
#घोषणा hfsp_now2mt()		__hfsp_ut2mt(kसमय_get_real_seconds())

#पूर्ण_अगर
