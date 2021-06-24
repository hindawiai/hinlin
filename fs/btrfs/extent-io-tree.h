<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित BTRFS_EXTENT_IO_TREE_H
#घोषणा BTRFS_EXTENT_IO_TREE_H

काष्ठा extent_changeset;
काष्ठा io_failure_record;

/* Bits क्रम the extent state */
#घोषणा EXTENT_सूचीTY		(1U << 0)
#घोषणा EXTENT_UPTODATE		(1U << 1)
#घोषणा EXTENT_LOCKED		(1U << 2)
#घोषणा EXTENT_NEW		(1U << 3)
#घोषणा EXTENT_DELALLOC		(1U << 4)
#घोषणा EXTENT_DEFRAG		(1U << 5)
#घोषणा EXTENT_BOUNDARY		(1U << 6)
#घोषणा EXTENT_NODATASUM	(1U << 7)
#घोषणा EXTENT_CLEAR_META_RESV	(1U << 8)
#घोषणा EXTENT_NEED_WAIT	(1U << 9)
#घोषणा EXTENT_DAMAGED		(1U << 10)
#घोषणा EXTENT_NORESERVE	(1U << 11)
#घोषणा EXTENT_QGROUP_RESERVED	(1U << 12)
#घोषणा EXTENT_CLEAR_DATA_RESV	(1U << 13)
/*
 * Must be cleared only during ordered extent completion or on error paths अगर we
 * did not manage to submit bios and create the ordered extents क्रम the range.
 * Should not be cleared during page release and page invalidation (अगर there is
 * an ordered extent in flight), that is left क्रम the ordered extent completion.
 */
#घोषणा EXTENT_DELALLOC_NEW	(1U << 14)
/*
 * When an ordered extent successfully completes क्रम a region marked as a new
 * delalloc range, use this flag when clearing a new delalloc range to indicate
 * that the VFS' inode number of bytes should be incremented and the inode's new
 * delalloc bytes decremented, in an atomic way to prevent races with stat(2).
 */
#घोषणा EXTENT_ADD_INODE_BYTES  (1U << 15)
#घोषणा EXTENT_DO_ACCOUNTING    (EXTENT_CLEAR_META_RESV | \
				 EXTENT_CLEAR_DATA_RESV)
#घोषणा EXTENT_CTLBITS		(EXTENT_DO_ACCOUNTING | \
				 EXTENT_ADD_INODE_BYTES)

/*
 * Redefined bits above which are used only in the device allocation tree,
 * shouldn't be using EXTENT_LOCKED / EXTENT_BOUNDARY / EXTENT_CLEAR_META_RESV
 * / EXTENT_CLEAR_DATA_RESV because they have special meaning to the bit
 * manipulation functions
 */
#घोषणा CHUNK_ALLOCATED				EXTENT_सूचीTY
#घोषणा CHUNK_TRIMMED				EXTENT_DEFRAG
#घोषणा CHUNK_STATE_MASK			(CHUNK_ALLOCATED |		\
						 CHUNK_TRIMMED)

क्रमागत अणु
	IO_TREE_FS_PINNED_EXTENTS,
	IO_TREE_FS_EXCLUDED_EXTENTS,
	IO_TREE_BTREE_INODE_IO,
	IO_TREE_INODE_IO,
	IO_TREE_INODE_IO_FAILURE,
	IO_TREE_RELOC_BLOCKS,
	IO_TREE_TRANS_सूचीTY_PAGES,
	IO_TREE_ROOT_सूचीTY_LOG_PAGES,
	IO_TREE_INODE_खाता_EXTENT,
	IO_TREE_LOG_CSUM_RANGE,
	IO_TREE_SELFTEST,
	IO_TREE_DEVICE_ALLOC_STATE,
पूर्ण;

काष्ठा extent_io_tree अणु
	काष्ठा rb_root state;
	काष्ठा btrfs_fs_info *fs_info;
	व्योम *निजी_data;
	u64 dirty_bytes;
	bool track_uptodate;

	/* Who owns this io tree, should be one of IO_TREE_* */
	u8 owner;

	spinlock_t lock;
पूर्ण;

काष्ठा extent_state अणु
	u64 start;
	u64 end; /* inclusive */
	काष्ठा rb_node rb_node;

	/* ADD NEW ELEMENTS AFTER THIS */
	रुको_queue_head_t wq;
	refcount_t refs;
	u32 state;

	काष्ठा io_failure_record *failrec;

#अगर_घोषित CONFIG_BTRFS_DEBUG
	काष्ठा list_head leak_list;
#पूर्ण_अगर
पूर्ण;

पूर्णांक __init extent_state_cache_init(व्योम);
व्योम __cold extent_state_cache_निकास(व्योम);

व्योम extent_io_tree_init(काष्ठा btrfs_fs_info *fs_info,
			 काष्ठा extent_io_tree *tree, अचिन्हित पूर्णांक owner,
			 व्योम *निजी_data);
व्योम extent_io_tree_release(काष्ठा extent_io_tree *tree);

पूर्णांक lock_extent_bits(काष्ठा extent_io_tree *tree, u64 start, u64 end,
		     काष्ठा extent_state **cached);

अटल अंतरभूत पूर्णांक lock_extent(काष्ठा extent_io_tree *tree, u64 start, u64 end)
अणु
	वापस lock_extent_bits(tree, start, end, शून्य);
पूर्ण

पूर्णांक try_lock_extent(काष्ठा extent_io_tree *tree, u64 start, u64 end);

पूर्णांक __init extent_io_init(व्योम);
व्योम __cold extent_io_निकास(व्योम);

u64 count_range_bits(काष्ठा extent_io_tree *tree,
		     u64 *start, u64 search_end,
		     u64 max_bytes, u32 bits, पूर्णांक contig);

व्योम मुक्त_extent_state(काष्ठा extent_state *state);
पूर्णांक test_range_bit(काष्ठा extent_io_tree *tree, u64 start, u64 end,
		   u32 bits, पूर्णांक filled, काष्ठा extent_state *cached_state);
पूर्णांक clear_record_extent_bits(काष्ठा extent_io_tree *tree, u64 start, u64 end,
			     u32 bits, काष्ठा extent_changeset *changeset);
पूर्णांक clear_extent_bit(काष्ठा extent_io_tree *tree, u64 start, u64 end,
		     u32 bits, पूर्णांक wake, पूर्णांक delete,
		     काष्ठा extent_state **cached);
पूर्णांक __clear_extent_bit(काष्ठा extent_io_tree *tree, u64 start, u64 end,
		     u32 bits, पूर्णांक wake, पूर्णांक delete,
		     काष्ठा extent_state **cached, gfp_t mask,
		     काष्ठा extent_changeset *changeset);

अटल अंतरभूत पूर्णांक unlock_extent(काष्ठा extent_io_tree *tree, u64 start, u64 end)
अणु
	वापस clear_extent_bit(tree, start, end, EXTENT_LOCKED, 1, 0, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक unlock_extent_cached(काष्ठा extent_io_tree *tree, u64 start,
		u64 end, काष्ठा extent_state **cached)
अणु
	वापस __clear_extent_bit(tree, start, end, EXTENT_LOCKED, 1, 0, cached,
				GFP_NOFS, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक unlock_extent_cached_atomic(काष्ठा extent_io_tree *tree,
		u64 start, u64 end, काष्ठा extent_state **cached)
अणु
	वापस __clear_extent_bit(tree, start, end, EXTENT_LOCKED, 1, 0, cached,
				GFP_ATOMIC, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक clear_extent_bits(काष्ठा extent_io_tree *tree, u64 start,
				    u64 end, u32 bits)
अणु
	पूर्णांक wake = 0;

	अगर (bits & EXTENT_LOCKED)
		wake = 1;

	वापस clear_extent_bit(tree, start, end, bits, wake, 0, शून्य);
पूर्ण

पूर्णांक set_record_extent_bits(काष्ठा extent_io_tree *tree, u64 start, u64 end,
			   u32 bits, काष्ठा extent_changeset *changeset);
पूर्णांक set_extent_bit(काष्ठा extent_io_tree *tree, u64 start, u64 end,
		   u32 bits, अचिन्हित exclusive_bits, u64 *failed_start,
		   काष्ठा extent_state **cached_state, gfp_t mask,
		   काष्ठा extent_changeset *changeset);
पूर्णांक set_extent_bits_noरुको(काष्ठा extent_io_tree *tree, u64 start, u64 end,
			   u32 bits);

अटल अंतरभूत पूर्णांक set_extent_bits(काष्ठा extent_io_tree *tree, u64 start,
		u64 end, u32 bits)
अणु
	वापस set_extent_bit(tree, start, end, bits, 0, शून्य, शून्य, GFP_NOFS,
			      शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक clear_extent_uptodate(काष्ठा extent_io_tree *tree, u64 start,
		u64 end, काष्ठा extent_state **cached_state)
अणु
	वापस __clear_extent_bit(tree, start, end, EXTENT_UPTODATE, 0, 0,
				cached_state, GFP_NOFS, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक set_extent_dirty(काष्ठा extent_io_tree *tree, u64 start,
		u64 end, gfp_t mask)
अणु
	वापस set_extent_bit(tree, start, end, EXTENT_सूचीTY, 0, शून्य, शून्य,
			      mask, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक clear_extent_dirty(काष्ठा extent_io_tree *tree, u64 start,
				     u64 end, काष्ठा extent_state **cached)
अणु
	वापस clear_extent_bit(tree, start, end,
				EXTENT_सूचीTY | EXTENT_DELALLOC |
				EXTENT_DO_ACCOUNTING, 0, 0, cached);
पूर्ण

पूर्णांक convert_extent_bit(काष्ठा extent_io_tree *tree, u64 start, u64 end,
		       u32 bits, u32 clear_bits,
		       काष्ठा extent_state **cached_state);

अटल अंतरभूत पूर्णांक set_extent_delalloc(काष्ठा extent_io_tree *tree, u64 start,
				      u64 end, u32 extra_bits,
				      काष्ठा extent_state **cached_state)
अणु
	वापस set_extent_bit(tree, start, end,
			      EXTENT_DELALLOC | EXTENT_UPTODATE | extra_bits,
			      0, शून्य, cached_state, GFP_NOFS, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक set_extent_defrag(काष्ठा extent_io_tree *tree, u64 start,
		u64 end, काष्ठा extent_state **cached_state)
अणु
	वापस set_extent_bit(tree, start, end,
			      EXTENT_DELALLOC | EXTENT_UPTODATE | EXTENT_DEFRAG,
			      0, शून्य, cached_state, GFP_NOFS, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक set_extent_new(काष्ठा extent_io_tree *tree, u64 start,
		u64 end)
अणु
	वापस set_extent_bit(tree, start, end, EXTENT_NEW, 0, शून्य, शून्य,
			      GFP_NOFS, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक set_extent_uptodate(काष्ठा extent_io_tree *tree, u64 start,
		u64 end, काष्ठा extent_state **cached_state, gfp_t mask)
अणु
	वापस set_extent_bit(tree, start, end, EXTENT_UPTODATE, 0, शून्य,
			      cached_state, mask, शून्य);
पूर्ण

पूर्णांक find_first_extent_bit(काष्ठा extent_io_tree *tree, u64 start,
			  u64 *start_ret, u64 *end_ret, u32 bits,
			  काष्ठा extent_state **cached_state);
व्योम find_first_clear_extent_bit(काष्ठा extent_io_tree *tree, u64 start,
				 u64 *start_ret, u64 *end_ret, u32 bits);
पूर्णांक find_contiguous_extent_bit(काष्ठा extent_io_tree *tree, u64 start,
			       u64 *start_ret, u64 *end_ret, u32 bits);
पूर्णांक extent_invalidatepage(काष्ठा extent_io_tree *tree,
			  काष्ठा page *page, अचिन्हित दीर्घ offset);
bool btrfs_find_delalloc_range(काष्ठा extent_io_tree *tree, u64 *start,
			       u64 *end, u64 max_bytes,
			       काष्ठा extent_state **cached_state);

/* This should be reworked in the future and put अन्यथाwhere. */
काष्ठा io_failure_record *get_state_failrec(काष्ठा extent_io_tree *tree, u64 start);
पूर्णांक set_state_failrec(काष्ठा extent_io_tree *tree, u64 start,
		      काष्ठा io_failure_record *failrec);
व्योम btrfs_मुक्त_io_failure_record(काष्ठा btrfs_inode *inode, u64 start,
		u64 end);
पूर्णांक मुक्त_io_failure(काष्ठा extent_io_tree *failure_tree,
		    काष्ठा extent_io_tree *io_tree,
		    काष्ठा io_failure_record *rec);
पूर्णांक clean_io_failure(काष्ठा btrfs_fs_info *fs_info,
		     काष्ठा extent_io_tree *failure_tree,
		     काष्ठा extent_io_tree *io_tree, u64 start,
		     काष्ठा page *page, u64 ino, अचिन्हित पूर्णांक pg_offset);

#पूर्ण_अगर /* BTRFS_EXTENT_IO_TREE_H */
