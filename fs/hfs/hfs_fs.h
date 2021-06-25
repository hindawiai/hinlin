<शैली गुरु>
/*
 *  linux/fs/hfs/hfs_fs.h
 *
 * Copyright (C) 1995-1997  Paul H. Hargrove
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 * This file may be distributed under the terms of the GNU General Public License.
 */

#अगर_अघोषित _LINUX_HFS_FS_H
#घोषणा _LINUX_HFS_FS_H

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/fs.h>
#समावेश <linux/workqueue.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>

#समावेश "hfs.h"

#घोषणा DBG_BNODE_REFS	0x00000001
#घोषणा DBG_BNODE_MOD	0x00000002
#घोषणा DBG_CAT_MOD	0x00000004
#घोषणा DBG_INODE	0x00000008
#घोषणा DBG_SUPER	0x00000010
#घोषणा DBG_EXTENT	0x00000020
#घोषणा DBG_BITMAP	0x00000040

//#घोषणा DBG_MASK	(DBG_EXTENT|DBG_INODE|DBG_BNODE_MOD|DBG_CAT_MOD|DBG_BITMAP)
//#घोषणा DBG_MASK	(DBG_BNODE_MOD|DBG_CAT_MOD|DBG_INODE)
//#घोषणा DBG_MASK	(DBG_CAT_MOD|DBG_BNODE_REFS|DBG_INODE|DBG_EXTENT)
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


/*
 * काष्ठा hfs_inode_info
 *
 * The HFS-specअगरic part of a Linux (काष्ठा inode)
 */
काष्ठा hfs_inode_info अणु
	atomic_t खोलोcnt;

	अचिन्हित पूर्णांक flags;

	/* to deal with स_स्थानीय ugliness */
	पूर्णांक tz_secondswest;

	काष्ठा hfs_cat_key cat_key;

	काष्ठा list_head खोलो_dir_list;
	spinlock_t खोलो_dir_lock;
	काष्ठा inode *rsrc_inode;

	काष्ठा mutex extents_lock;

	u16 alloc_blocks, clump_blocks;
	sector_t fs_blocks;
	/* Allocation extents from catlog record or volume header */
	hfs_extent_rec first_extents;
	u16 first_blocks;
	hfs_extent_rec cached_extents;
	u16 cached_start, cached_blocks;

	loff_t phys_size;
	काष्ठा inode vfs_inode;
पूर्ण;

#घोषणा HFS_FLG_RSRC		0x0001
#घोषणा HFS_FLG_EXT_सूचीTY	0x0002
#घोषणा HFS_FLG_EXT_NEW		0x0004

#घोषणा HFS_IS_RSRC(inode)	(HFS_I(inode)->flags & HFS_FLG_RSRC)

/*
 * काष्ठा hfs_sb_info
 *
 * The HFS-specअगरic part of a Linux (काष्ठा super_block)
 */
काष्ठा hfs_sb_info अणु
	काष्ठा buffer_head *mdb_bh;		/* The hfs_buffer
						   holding the real
						   superblock (aka VIB
						   or MDB) */
	काष्ठा hfs_mdb *mdb;
	काष्ठा buffer_head *alt_mdb_bh;		/* The hfs_buffer holding
						   the alternate superblock */
	काष्ठा hfs_mdb *alt_mdb;
	__be32 *biपंचांगap;				/* The page holding the
						   allocation biपंचांगap */
	काष्ठा hfs_btree *ext_tree;			/* Inक्रमmation about
						   the extents b-tree */
	काष्ठा hfs_btree *cat_tree;			/* Inक्रमmation about
						   the catalog b-tree */
	u32 file_count;				/* The number of
						   regular files in
						   the fileप्रणाली */
	u32 folder_count;			/* The number of
						   directories in the
						   fileप्रणाली */
	u32 next_id;				/* The next available
						   file id number */
	u32 clumpablks;				/* The number of allocation
						   blocks to try to add when
						   extending a file */
	u32 fs_start;				/* The first 512-byte
						   block represented
						   in the biपंचांगap */
	u32 part_start;
	u16 root_files;				/* The number of
						   regular
						   (non-directory)
						   files in the root
						   directory */
	u16 root_dirs;				/* The number of
						   directories in the
						   root directory */
	u16 fs_ablocks;				/* The number of
						   allocation blocks
						   in the fileप्रणाली */
	u16 मुक्त_ablocks;			/* the number of unused
						   allocation blocks
						   in the fileप्रणाली */
	u32 alloc_blksz;			/* The size of an
						   "allocation block" */
	पूर्णांक s_quiet;				/* Silent failure when
						   changing owner or mode? */
	__be32 s_type;				/* Type क्रम new files */
	__be32 s_creator;			/* Creator क्रम new files */
	umode_t s_file_umask;			/* The umask applied to the
						   permissions on all files */
	umode_t s_dir_umask;			/* The umask applied to the
						   permissions on all dirs */
	kuid_t s_uid;				/* The uid of all files */
	kgid_t s_gid;				/* The gid of all files */

	पूर्णांक session, part;
	काष्ठा nls_table *nls_io, *nls_disk;
	काष्ठा mutex biपंचांगap_lock;
	अचिन्हित दीर्घ flags;
	u16 blockoffset;
	पूर्णांक fs_भाग;
	काष्ठा super_block *sb;
	पूर्णांक work_queued;		/* non-zero delayed work is queued */
	काष्ठा delayed_work mdb_work;	/* MDB flush delayed work */
	spinlock_t work_lock;		/* protects mdb_work and work_queued */
पूर्ण;

#घोषणा HFS_FLG_BITMAP_सूचीTY	0
#घोषणा HFS_FLG_MDB_सूचीTY	1
#घोषणा HFS_FLG_ALT_MDB_सूचीTY	2

/* biपंचांगap.c */
बाह्य u32 hfs_vbm_search_मुक्त(काष्ठा super_block *, u32, u32 *);
बाह्य पूर्णांक hfs_clear_vbm_bits(काष्ठा super_block *, u16, u16);

/* catalog.c */
बाह्य पूर्णांक hfs_cat_keycmp(स्थिर btree_key *, स्थिर btree_key *);
काष्ठा hfs_find_data;
बाह्य पूर्णांक hfs_cat_find_brec(काष्ठा super_block *, u32, काष्ठा hfs_find_data *);
बाह्य पूर्णांक hfs_cat_create(u32, काष्ठा inode *, स्थिर काष्ठा qstr *, काष्ठा inode *);
बाह्य पूर्णांक hfs_cat_delete(u32, काष्ठा inode *, स्थिर काष्ठा qstr *);
बाह्य पूर्णांक hfs_cat_move(u32, काष्ठा inode *, स्थिर काष्ठा qstr *,
			काष्ठा inode *, स्थिर काष्ठा qstr *);
बाह्य व्योम hfs_cat_build_key(काष्ठा super_block *, btree_key *, u32, स्थिर काष्ठा qstr *);

/* dir.c */
बाह्य स्थिर काष्ठा file_operations hfs_dir_operations;
बाह्य स्थिर काष्ठा inode_operations hfs_dir_inode_operations;

/* extent.c */
बाह्य पूर्णांक hfs_ext_keycmp(स्थिर btree_key *, स्थिर btree_key *);
बाह्य पूर्णांक hfs_मुक्त_विभाजन(काष्ठा super_block *, काष्ठा hfs_cat_file *, पूर्णांक);
बाह्य पूर्णांक hfs_ext_ग_लिखो_extent(काष्ठा inode *);
बाह्य पूर्णांक hfs_extend_file(काष्ठा inode *);
बाह्य व्योम hfs_file_truncate(काष्ठा inode *);

बाह्य पूर्णांक hfs_get_block(काष्ठा inode *, sector_t, काष्ठा buffer_head *, पूर्णांक);

/* inode.c */
बाह्य स्थिर काष्ठा address_space_operations hfs_aops;
बाह्य स्थिर काष्ठा address_space_operations hfs_btree_aops;

बाह्य काष्ठा inode *hfs_new_inode(काष्ठा inode *, स्थिर काष्ठा qstr *, umode_t);
बाह्य व्योम hfs_inode_ग_लिखो_विभाजन(काष्ठा inode *, काष्ठा hfs_extent *, __be32 *, __be32 *);
बाह्य पूर्णांक hfs_ग_लिखो_inode(काष्ठा inode *, काष्ठा ग_लिखोback_control *);
बाह्य पूर्णांक hfs_inode_setattr(काष्ठा user_namespace *, काष्ठा dentry *,
			     काष्ठा iattr *);
बाह्य व्योम hfs_inode_पढ़ो_विभाजन(काष्ठा inode *inode, काष्ठा hfs_extent *ext,
			__be32 log_size, __be32 phys_size, u32 clump_size);
बाह्य काष्ठा inode *hfs_iget(काष्ठा super_block *, काष्ठा hfs_cat_key *, hfs_cat_rec *);
बाह्य व्योम hfs_evict_inode(काष्ठा inode *);
बाह्य व्योम hfs_delete_inode(काष्ठा inode *);

/* attr.c */
बाह्य स्थिर काष्ठा xattr_handler *hfs_xattr_handlers[];

/* mdb.c */
बाह्य पूर्णांक hfs_mdb_get(काष्ठा super_block *);
बाह्य व्योम hfs_mdb_commit(काष्ठा super_block *);
बाह्य व्योम hfs_mdb_बंद(काष्ठा super_block *);
बाह्य व्योम hfs_mdb_put(काष्ठा super_block *);

/* part_tbl.c */
बाह्य पूर्णांक hfs_part_find(काष्ठा super_block *, sector_t *, sector_t *);

/* string.c */
बाह्य स्थिर काष्ठा dentry_operations hfs_dentry_operations;

बाह्य पूर्णांक hfs_hash_dentry(स्थिर काष्ठा dentry *, काष्ठा qstr *);
बाह्य पूर्णांक hfs_म_भेद(स्थिर अचिन्हित अक्षर *, अचिन्हित पूर्णांक,
		      स्थिर अचिन्हित अक्षर *, अचिन्हित पूर्णांक);
बाह्य पूर्णांक hfs_compare_dentry(स्थिर काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str, स्थिर काष्ठा qstr *name);

/* trans.c */
बाह्य व्योम hfs_asc2mac(काष्ठा super_block *, काष्ठा hfs_name *, स्थिर काष्ठा qstr *);
बाह्य पूर्णांक hfs_mac2asc(काष्ठा super_block *, अक्षर *, स्थिर काष्ठा hfs_name *);

/* super.c */
बाह्य व्योम hfs_mark_mdb_dirty(काष्ठा super_block *sb);

/*
 * There are two समय प्रणालीs.  Both are based on seconds since
 * a particular समय/date.
 *	Unix:	चिन्हित little-endian since 00:00 GMT, Jan. 1, 1970
 *	mac:	अचिन्हित big-endian since 00:00 GMT, Jan. 1, 1904
 *
 * HFS implementations are highly inconsistent, this one matches the
 * traditional behavior of 64-bit Linux, giving the most useful
 * समय range between 1970 and 2106, by treating any on-disk बारtamp
 * under HFS_UTC_OFFSET (Jan 1 1970) as a समय between 2040 and 2106.
 */
#घोषणा HFS_UTC_OFFSET 2082844800U

अटल अंतरभूत समय64_t __hfs_m_to_uसमय(__be32 mt)
अणु
	समय64_t ut = (u32)(be32_to_cpu(mt) - HFS_UTC_OFFSET);

	वापस ut + sys_tz.tz_minuteswest * 60;
पूर्ण

अटल अंतरभूत __be32 __hfs_u_to_mसमय(समय64_t ut)
अणु
	ut -= sys_tz.tz_minuteswest * 60;

	वापस cpu_to_be32(lower_32_bits(ut) + HFS_UTC_OFFSET);
पूर्ण
#घोषणा HFS_I(inode)	(container_of(inode, काष्ठा hfs_inode_info, vfs_inode))
#घोषणा HFS_SB(sb)	((काष्ठा hfs_sb_info *)(sb)->s_fs_info)

#घोषणा hfs_m_to_uसमय(समय)   (काष्ठा बारpec64)अणु .tv_sec = __hfs_m_to_uसमय(समय) पूर्ण
#घोषणा hfs_u_to_mसमय(समय)   __hfs_u_to_mसमय((समय).tv_sec)
#घोषणा hfs_mसमय()		__hfs_u_to_mसमय(kसमय_get_real_seconds())

अटल अंतरभूत स्थिर अक्षर *hfs_mdb_name(काष्ठा super_block *sb)
अणु
	वापस sb->s_id;
पूर्ण

अटल अंतरभूत व्योम hfs_biपंचांगap_dirty(काष्ठा super_block *sb)
अणु
	set_bit(HFS_FLG_BITMAP_सूचीTY, &HFS_SB(sb)->flags);
	hfs_mark_mdb_dirty(sb);
पूर्ण

#घोषणा sb_bपढ़ो512(sb, sec, data) (अणु			\
	काष्ठा buffer_head *__bh;			\
	sector_t __block;				\
	loff_t __start;					\
	पूर्णांक __offset;					\
							\
	__start = (loff_t)(sec) << HFS_SECTOR_SIZE_BITS;\
	__block = __start >> (sb)->s_blocksize_bits;	\
	__offset = __start & ((sb)->s_blocksize - 1);	\
	__bh = sb_bपढ़ो((sb), __block);			\
	अगर (likely(__bh != शून्य))			\
		data = (व्योम *)(__bh->b_data + __offset);\
	अन्यथा						\
		data = शून्य;				\
	__bh;						\
पूर्ण)

#पूर्ण_अगर
