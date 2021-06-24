<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#अगर_अघोषित BTRFS_INODE_H
#घोषणा BTRFS_INODE_H

#समावेश <linux/hash.h>
#समावेश <linux/refcount.h>
#समावेश "extent_map.h"
#समावेश "extent_io.h"
#समावेश "ordered-data.h"
#समावेश "delayed-inode.h"

/*
 * ordered_data_बंद is set by truncate when a file that used
 * to have good data has been truncated to zero.  When it is set
 * the btrfs file release call will add this inode to the
 * ordered operations list so that we make sure to flush out any
 * new data the application may have written beक्रमe commit.
 */
क्रमागत अणु
	BTRFS_INODE_FLUSH_ON_CLOSE,
	BTRFS_INODE_DUMMY,
	BTRFS_INODE_IN_DEFRAG,
	BTRFS_INODE_HAS_ASYNC_EXTENT,
	 /*
	  * Always set under the VFS' inode lock, otherwise it can cause races
	  * during fsync (we start as a fast fsync and then end up in a full
	  * fsync racing with ordered extent completion).
	  */
	BTRFS_INODE_NEEDS_FULL_SYNC,
	BTRFS_INODE_COPY_EVERYTHING,
	BTRFS_INODE_IN_DELALLOC_LIST,
	BTRFS_INODE_HAS_PROPS,
	BTRFS_INODE_SNAPSHOT_FLUSH,
	/*
	 * Set and used when logging an inode and it serves to संकेत that an
	 * inode करोes not have xattrs, so subsequent fsyncs can aव्योम searching
	 * क्रम xattrs to log. This bit must be cleared whenever a xattr is added
	 * to an inode.
	 */
	BTRFS_INODE_NO_XATTRS,
	/*
	 * Set when we are in a context where we need to start a transaction and
	 * have dirty pages with the respective file range locked. This is to
	 * ensure that when reserving space क्रम the transaction, अगर we are low
	 * on available space and need to flush delalloc, we will not flush
	 * delalloc क्रम this inode, because that could result in a deadlock (on
	 * the file range, inode's io_tree).
	 */
	BTRFS_INODE_NO_DELALLOC_FLUSH,
पूर्ण;

/* in memory btrfs inode */
काष्ठा btrfs_inode अणु
	/* which subvolume this inode beदीर्घs to */
	काष्ठा btrfs_root *root;

	/* key used to find this inode on disk.  This is used by the code
	 * to पढ़ो in roots of subvolumes
	 */
	काष्ठा btrfs_key location;

	/*
	 * Lock क्रम counters and all fields used to determine अगर the inode is in
	 * the log or not (last_trans, last_sub_trans, last_log_commit,
	 * logged_trans), to access/update new_delalloc_bytes and to update the
	 * VFS' inode number of bytes used.
	 */
	spinlock_t lock;

	/* the extent_tree has caches of all the extent mappings to disk */
	काष्ठा extent_map_tree extent_tree;

	/* the io_tree करोes range state (सूचीTY, LOCKED etc) */
	काष्ठा extent_io_tree io_tree;

	/* special utility tree used to record which mirrors have alपढ़ोy been
	 * tried when checksums fail क्रम a given block
	 */
	काष्ठा extent_io_tree io_failure_tree;

	/*
	 * Keep track of where the inode has extent items mapped in order to
	 * make sure the i_size adjusपंचांगents are accurate
	 */
	काष्ठा extent_io_tree file_extent_tree;

	/* held जबतक logging the inode in tree-log.c */
	काष्ठा mutex log_mutex;

	/* used to order data wrt metadata */
	काष्ठा btrfs_ordered_inode_tree ordered_tree;

	/* list of all the delalloc inodes in the FS.  There are बार we need
	 * to ग_लिखो all the delalloc pages to disk, and this list is used
	 * to walk them all.
	 */
	काष्ठा list_head delalloc_inodes;

	/* node क्रम the red-black tree that links inodes in subvolume root */
	काष्ठा rb_node rb_node;

	अचिन्हित दीर्घ runसमय_flags;

	/* Keep track of who's O_SYNC/fsyncing currently */
	atomic_t sync_ग_लिखोrs;

	/* full 64 bit generation number, काष्ठा vfs_inode करोesn't have a big
	 * enough field क्रम this.
	 */
	u64 generation;

	/*
	 * transid of the trans_handle that last modअगरied this inode
	 */
	u64 last_trans;

	/*
	 * transid that last logged this inode
	 */
	u64 logged_trans;

	/*
	 * log transid when this inode was last modअगरied
	 */
	पूर्णांक last_sub_trans;

	/* a local copy of root's last_log_commit */
	पूर्णांक last_log_commit;

	/* total number of bytes pending delalloc, used by stat to calc the
	 * real block usage of the file
	 */
	u64 delalloc_bytes;

	/*
	 * Total number of bytes pending delalloc that fall within a file
	 * range that is either a hole or beyond खातापूर्ण (and no pपुनः_स्मृति extent
	 * exists in the range). This is always <= delalloc_bytes.
	 */
	u64 new_delalloc_bytes;

	/*
	 * total number of bytes pending defrag, used by stat to check whether
	 * it needs COW.
	 */
	u64 defrag_bytes;

	/*
	 * the size of the file stored in the metadata on disk.  data=ordered
	 * means the in-memory i_size might be larger than the size on disk
	 * because not all the blocks are written yet.
	 */
	u64 disk_i_size;

	/*
	 * अगर this is a directory then index_cnt is the counter क्रम the index
	 * number क्रम new files that are created
	 */
	u64 index_cnt;

	/* Cache the directory index number to speed the dir/file हटाओ */
	u64 dir_index;

	/* the fsync log has some corner हालs that mean we have to check
	 * directories to see अगर any unlinks have been करोne beक्रमe
	 * the directory was logged.  See tree-log.c क्रम all the
	 * details
	 */
	u64 last_unlink_trans;

	/*
	 * The id/generation of the last transaction where this inode was
	 * either the source or the destination of a clone/dedupe operation.
	 * Used when logging an inode to know अगर there are shared extents that
	 * need special care when logging checksum items, to aव्योम duplicate
	 * checksum items in a log (which can lead to a corruption where we end
	 * up with missing checksum ranges after log replay).
	 * Protected by the vfs inode lock.
	 */
	u64 last_reflink_trans;

	/*
	 * Number of bytes outstanding that are going to need csums.  This is
	 * used in ENOSPC accounting.
	 */
	u64 csum_bytes;

	/* flags field from the on disk inode */
	u32 flags;

	/*
	 * Counters to keep track of the number of extent item's we may use due
	 * to delalloc and such.  outstanding_extents is the number of extent
	 * items we think we'll end up using, and reserved_extents is the number
	 * of extent items we've reserved metadata क्रम.
	 */
	अचिन्हित outstanding_extents;

	काष्ठा btrfs_block_rsv block_rsv;

	/*
	 * Cached values of inode properties
	 */
	अचिन्हित prop_compress;		/* per-file compression algorithm */
	/*
	 * Force compression on the file using the defrag ioctl, could be
	 * dअगरferent from prop_compress and takes precedence अगर set
	 */
	अचिन्हित defrag_compress;

	काष्ठा btrfs_delayed_node *delayed_node;

	/* File creation समय. */
	काष्ठा बारpec64 i_oसमय;

	/* Hook पूर्णांकo fs_info->delayed_iमाला_दो */
	काष्ठा list_head delayed_iput;

	काष्ठा rw_semaphore i_mmap_lock;
	काष्ठा inode vfs_inode;
पूर्ण;

अटल अंतरभूत u32 btrfs_inode_sectorsize(स्थिर काष्ठा btrfs_inode *inode)
अणु
	वापस inode->root->fs_info->sectorsize;
पूर्ण

अटल अंतरभूत काष्ठा btrfs_inode *BTRFS_I(स्थिर काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा btrfs_inode, vfs_inode);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ btrfs_inode_hash(u64 objectid,
					     स्थिर काष्ठा btrfs_root *root)
अणु
	u64 h = objectid ^ (root->root_key.objectid * GOLDEN_RATIO_PRIME);

#अगर BITS_PER_LONG == 32
	h = (h >> 32) ^ (h & 0xffffffff);
#पूर्ण_अगर

	वापस (अचिन्हित दीर्घ)h;
पूर्ण

अटल अंतरभूत व्योम btrfs_insert_inode_hash(काष्ठा inode *inode)
अणु
	अचिन्हित दीर्घ h = btrfs_inode_hash(inode->i_ino, BTRFS_I(inode)->root);

	__insert_inode_hash(inode, h);
पूर्ण

अटल अंतरभूत u64 btrfs_ino(स्थिर काष्ठा btrfs_inode *inode)
अणु
	u64 ino = inode->location.objectid;

	/*
	 * !ino: btree_inode
	 * type == BTRFS_ROOT_ITEM_KEY: subvol dir
	 */
	अगर (!ino || inode->location.type == BTRFS_ROOT_ITEM_KEY)
		ino = inode->vfs_inode.i_ino;
	वापस ino;
पूर्ण

अटल अंतरभूत व्योम btrfs_i_size_ग_लिखो(काष्ठा btrfs_inode *inode, u64 size)
अणु
	i_size_ग_लिखो(&inode->vfs_inode, size);
	inode->disk_i_size = size;
पूर्ण

अटल अंतरभूत bool btrfs_is_मुक्त_space_inode(काष्ठा btrfs_inode *inode)
अणु
	काष्ठा btrfs_root *root = inode->root;

	अगर (root == root->fs_info->tree_root &&
	    btrfs_ino(inode) != BTRFS_BTREE_INODE_OBJECTID)
		वापस true;
	अगर (inode->location.objectid == BTRFS_FREE_INO_OBJECTID)
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool is_data_inode(काष्ठा inode *inode)
अणु
	वापस btrfs_ino(BTRFS_I(inode)) != BTRFS_BTREE_INODE_OBJECTID;
पूर्ण

अटल अंतरभूत व्योम btrfs_mod_outstanding_extents(काष्ठा btrfs_inode *inode,
						 पूर्णांक mod)
अणु
	lockdep_निश्चित_held(&inode->lock);
	inode->outstanding_extents += mod;
	अगर (btrfs_is_मुक्त_space_inode(inode))
		वापस;
	trace_btrfs_inode_mod_outstanding_extents(inode->root, btrfs_ino(inode),
						  mod);
पूर्ण

/*
 * Called every समय after करोing a buffered, direct IO or memory mapped ग_लिखो.
 *
 * This is to ensure that अगर we ग_लिखो to a file that was previously fsynced in
 * the current transaction, then try to fsync it again in the same transaction,
 * we will know that there were changes in the file and that it needs to be
 * logged.
 */
अटल अंतरभूत व्योम btrfs_set_inode_last_sub_trans(काष्ठा btrfs_inode *inode)
अणु
	spin_lock(&inode->lock);
	inode->last_sub_trans = inode->root->log_transid;
	spin_unlock(&inode->lock);
पूर्ण

अटल अंतरभूत bool btrfs_inode_in_log(काष्ठा btrfs_inode *inode, u64 generation)
अणु
	bool ret = false;

	spin_lock(&inode->lock);
	अगर (inode->logged_trans == generation &&
	    inode->last_sub_trans <= inode->last_log_commit &&
	    inode->last_sub_trans <= inode->root->last_log_commit)
		ret = true;
	spin_unlock(&inode->lock);
	वापस ret;
पूर्ण

काष्ठा btrfs_dio_निजी अणु
	काष्ठा inode *inode;
	u64 logical_offset;
	u64 disk_bytenr;
	/* Used क्रम bio::bi_size */
	u32 bytes;

	/*
	 * References to this काष्ठाure. There is one reference per in-flight
	 * bio plus one जबतक we're still setting up.
	 */
	refcount_t refs;

	/* dio_bio came from fs/direct-io.c */
	काष्ठा bio *dio_bio;

	/* Array of checksums */
	u8 csums[];
पूर्ण;

/* Array of bytes with variable length, hexadecimal क्रमmat 0x1234 */
#घोषणा CSUM_FMT				"0x%*phN"
#घोषणा CSUM_FMT_VALUE(size, bytes)		size, bytes

अटल अंतरभूत व्योम btrfs_prपूर्णांक_data_csum_error(काष्ठा btrfs_inode *inode,
		u64 logical_start, u8 *csum, u8 *csum_expected, पूर्णांक mirror_num)
अणु
	काष्ठा btrfs_root *root = inode->root;
	स्थिर u32 csum_size = root->fs_info->csum_size;

	/* Output minus objectid, which is more meaningful */
	अगर (root->root_key.objectid >= BTRFS_LAST_FREE_OBJECTID)
		btrfs_warn_rl(root->fs_info,
"csum failed root %lld ino %lld off %llu csum " CSUM_FMT " expected csum " CSUM_FMT " mirror %d",
			root->root_key.objectid, btrfs_ino(inode),
			logical_start,
			CSUM_FMT_VALUE(csum_size, csum),
			CSUM_FMT_VALUE(csum_size, csum_expected),
			mirror_num);
	अन्यथा
		btrfs_warn_rl(root->fs_info,
"csum failed root %llu ino %llu off %llu csum " CSUM_FMT " expected csum " CSUM_FMT " mirror %d",
			root->root_key.objectid, btrfs_ino(inode),
			logical_start,
			CSUM_FMT_VALUE(csum_size, csum),
			CSUM_FMT_VALUE(csum_size, csum_expected),
			mirror_num);
पूर्ण

#पूर्ण_अगर
