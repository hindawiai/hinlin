<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#अगर_अघोषित BTRFS_ORDERED_DATA_H
#घोषणा BTRFS_ORDERED_DATA_H

/* one of these per inode */
काष्ठा btrfs_ordered_inode_tree अणु
	spinlock_t lock;
	काष्ठा rb_root tree;
	काष्ठा rb_node *last;
पूर्ण;

काष्ठा btrfs_ordered_sum अणु
	/* bytenr is the start of this extent on disk */
	u64 bytenr;

	/*
	 * this is the length in bytes covered by the sums array below.
	 */
	पूर्णांक len;
	काष्ठा list_head list;
	/* last field is a variable length array of csums */
	u8 sums[];
पूर्ण;

/*
 * Bits क्रम btrfs_ordered_extent::flags.
 *
 * BTRFS_ORDERED_IO_DONE is set when all of the blocks are written.
 * It is used to make sure metadata is inserted पूर्णांकo the tree only once
 * per extent.
 *
 * BTRFS_ORDERED_COMPLETE is set when the extent is हटाओd from the
 * rbtree, just beक्रमe waking any रुकोers.  It is used to indicate the
 * IO is करोne and any metadata is inserted पूर्णांकo the tree.
 */
क्रमागत अणु
	/*
	 * Dअगरferent types क्रम ordered extents, one and only one of the 4 types
	 * need to be set when creating ordered extent.
	 *
	 * REGULAR:	For regular non-compressed COW ग_लिखो
	 * NOCOW:	For NOCOW ग_लिखो पूर्णांकo existing non-hole extent
	 * PREALLOC:	For NOCOW ग_लिखो पूर्णांकo pपुनः_स्मृतिated extent
	 * COMPRESSED:	For compressed COW ग_लिखो
	 */
	BTRFS_ORDERED_REGULAR,
	BTRFS_ORDERED_NOCOW,
	BTRFS_ORDERED_PREALLOC,
	BTRFS_ORDERED_COMPRESSED,

	/*
	 * Extra bit क्रम direct io, can only be set क्रम
	 * REGULAR/NOCOW/PREALLOC. No direct io क्रम compressed extent.
	 */
	BTRFS_ORDERED_सूचीECT,

	/* Extra status bits क्रम ordered extents */

	/* set when all the pages are written */
	BTRFS_ORDERED_IO_DONE,
	/* set when हटाओd from the tree */
	BTRFS_ORDERED_COMPLETE,
	/* We had an io error when writing this out */
	BTRFS_ORDERED_IOERR,
	/* Set when we have to truncate an extent */
	BTRFS_ORDERED_TRUNCATED,
	/* Used during fsync to track alपढ़ोy logged extents */
	BTRFS_ORDERED_LOGGED,
	/* We have alपढ़ोy logged all the csums of the ordered extent */
	BTRFS_ORDERED_LOGGED_CSUM,
	/* We रुको क्रम this extent to complete in the current transaction */
	BTRFS_ORDERED_PENDING,
पूर्ण;

काष्ठा btrfs_ordered_extent अणु
	/* logical offset in the file */
	u64 file_offset;

	/*
	 * These fields directly correspond to the same fields in
	 * btrfs_file_extent_item.
	 */
	u64 disk_bytenr;
	u64 num_bytes;
	u64 disk_num_bytes;

	/* number of bytes that still need writing */
	u64 bytes_left;

	/*
	 * the end of the ordered extent which is behind it but
	 * didn't update disk_i_size. Please see the comment of
	 * btrfs_ordered_update_i_size();
	 */
	u64 outstanding_isize;

	/*
	 * If we get truncated we need to adjust the file extent we enter क्रम
	 * this ordered extent so that we करो not expose stale data.
	 */
	u64 truncated_len;

	/* flags (described above) */
	अचिन्हित दीर्घ flags;

	/* compression algorithm */
	पूर्णांक compress_type;

	/* Qgroup reserved space */
	पूर्णांक qgroup_rsv;

	/* reference count */
	refcount_t refs;

	/* the inode we beदीर्घ to */
	काष्ठा inode *inode;

	/* list of checksums क्रम insertion when the extent io is करोne */
	काष्ठा list_head list;

	/* used क्रम fast fsyncs */
	काष्ठा list_head log_list;

	/* used to रुको क्रम the BTRFS_ORDERED_COMPLETE bit */
	रुको_queue_head_t रुको;

	/* our मित्रly rbtree entry */
	काष्ठा rb_node rb_node;

	/* a per root list of all the pending ordered extents */
	काष्ठा list_head root_extent_list;

	काष्ठा btrfs_work work;

	काष्ठा completion completion;
	काष्ठा btrfs_work flush_work;
	काष्ठा list_head work_list;

	/*
	 * Used to reverse-map physical address वापसed from ZONE_APPEND ग_लिखो
	 * command in a workqueue context
	 */
	u64 physical;
	काष्ठा gendisk *disk;
	u8 partno;
पूर्ण;

/*
 * calculates the total size you need to allocate क्रम an ordered sum
 * काष्ठाure spanning 'bytes' in the file
 */
अटल अंतरभूत पूर्णांक btrfs_ordered_sum_size(काष्ठा btrfs_fs_info *fs_info,
					 अचिन्हित दीर्घ bytes)
अणु
	पूर्णांक num_sectors = (पूर्णांक)DIV_ROUND_UP(bytes, fs_info->sectorsize);

	वापस माप(काष्ठा btrfs_ordered_sum) + num_sectors * fs_info->csum_size;
पूर्ण

अटल अंतरभूत व्योम
btrfs_ordered_inode_tree_init(काष्ठा btrfs_ordered_inode_tree *t)
अणु
	spin_lock_init(&t->lock);
	t->tree = RB_ROOT;
	t->last = शून्य;
पूर्ण

व्योम btrfs_put_ordered_extent(काष्ठा btrfs_ordered_extent *entry);
व्योम btrfs_हटाओ_ordered_extent(काष्ठा btrfs_inode *btrfs_inode,
				काष्ठा btrfs_ordered_extent *entry);
bool btrfs_dec_test_ordered_pending(काष्ठा btrfs_inode *inode,
				    काष्ठा btrfs_ordered_extent **cached,
				    u64 file_offset, u64 io_size, पूर्णांक uptodate);
bool btrfs_dec_test_first_ordered_pending(काष्ठा btrfs_inode *inode,
				   काष्ठा btrfs_ordered_extent **finished_ret,
				   u64 *file_offset, u64 io_size,
				   पूर्णांक uptodate);
पूर्णांक btrfs_add_ordered_extent(काष्ठा btrfs_inode *inode, u64 file_offset,
			     u64 disk_bytenr, u64 num_bytes, u64 disk_num_bytes,
			     पूर्णांक type);
पूर्णांक btrfs_add_ordered_extent_dio(काष्ठा btrfs_inode *inode, u64 file_offset,
				 u64 disk_bytenr, u64 num_bytes,
				 u64 disk_num_bytes, पूर्णांक type);
पूर्णांक btrfs_add_ordered_extent_compress(काष्ठा btrfs_inode *inode, u64 file_offset,
				      u64 disk_bytenr, u64 num_bytes,
				      u64 disk_num_bytes, पूर्णांक compress_type);
व्योम btrfs_add_ordered_sum(काष्ठा btrfs_ordered_extent *entry,
			   काष्ठा btrfs_ordered_sum *sum);
काष्ठा btrfs_ordered_extent *btrfs_lookup_ordered_extent(काष्ठा btrfs_inode *inode,
							 u64 file_offset);
व्योम btrfs_start_ordered_extent(काष्ठा btrfs_ordered_extent *entry, पूर्णांक रुको);
पूर्णांक btrfs_रुको_ordered_range(काष्ठा inode *inode, u64 start, u64 len);
काष्ठा btrfs_ordered_extent *
btrfs_lookup_first_ordered_extent(काष्ठा btrfs_inode *inode, u64 file_offset);
काष्ठा btrfs_ordered_extent *btrfs_lookup_ordered_range(
		काष्ठा btrfs_inode *inode,
		u64 file_offset,
		u64 len);
व्योम btrfs_get_ordered_extents_क्रम_logging(काष्ठा btrfs_inode *inode,
					   काष्ठा list_head *list);
u64 btrfs_रुको_ordered_extents(काष्ठा btrfs_root *root, u64 nr,
			       स्थिर u64 range_start, स्थिर u64 range_len);
व्योम btrfs_रुको_ordered_roots(काष्ठा btrfs_fs_info *fs_info, u64 nr,
			      स्थिर u64 range_start, स्थिर u64 range_len);
व्योम btrfs_lock_and_flush_ordered_range(काष्ठा btrfs_inode *inode, u64 start,
					u64 end,
					काष्ठा extent_state **cached_state);
पूर्णांक btrfs_split_ordered_extent(काष्ठा btrfs_ordered_extent *ordered, u64 pre,
			       u64 post);
पूर्णांक __init ordered_data_init(व्योम);
व्योम __cold ordered_data_निकास(व्योम);

#पूर्ण_अगर
