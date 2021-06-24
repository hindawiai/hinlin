<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित BTRFS_EXTENT_IO_H
#घोषणा BTRFS_EXTENT_IO_H

#समावेश <linux/rbtree.h>
#समावेश <linux/refcount.h>
#समावेश <linux/fiemap.h>
#समावेश <linux/btrfs_tree.h>
#समावेश "ulist.h"

/*
 * flags क्रम bio submission. The high bits indicate the compression
 * type क्रम this bio
 */
#घोषणा EXTENT_BIO_COMPRESSED 1
#घोषणा EXTENT_BIO_FLAG_SHIFT 16

क्रमागत अणु
	EXTENT_BUFFER_UPTODATE,
	EXTENT_BUFFER_सूचीTY,
	EXTENT_BUFFER_CORRUPT,
	/* this got triggered by पढ़ोahead */
	EXTENT_BUFFER_READAHEAD,
	EXTENT_BUFFER_TREE_REF,
	EXTENT_BUFFER_STALE,
	EXTENT_BUFFER_WRITEBACK,
	/* पढ़ो IO error */
	EXTENT_BUFFER_READ_ERR,
	EXTENT_BUFFER_UNMAPPED,
	EXTENT_BUFFER_IN_TREE,
	/* ग_लिखो IO error */
	EXTENT_BUFFER_WRITE_ERR,
	EXTENT_BUFFER_NO_CHECK,
पूर्ण;

/* these are flags क्रम __process_pages_contig */
#घोषणा PAGE_UNLOCK		(1 << 0)
/* Page starts ग_लिखोback, clear dirty bit and set ग_लिखोback bit */
#घोषणा PAGE_START_WRITEBACK	(1 << 1)
#घोषणा PAGE_END_WRITEBACK	(1 << 2)
#घोषणा PAGE_SET_PRIVATE2	(1 << 3)
#घोषणा PAGE_SET_ERROR		(1 << 4)
#घोषणा PAGE_LOCK		(1 << 5)

/*
 * page->निजी values.  Every page that is controlled by the extent
 * map has page->निजी set to one.
 */
#घोषणा EXTENT_PAGE_PRIVATE 1

/*
 * The extent buffer biपंचांगap operations are करोne with byte granularity instead of
 * word granularity क्रम two reasons:
 * 1. The biपंचांगaps must be little-endian on disk.
 * 2. Biपंचांगap items are not guaranteed to be aligned to a word and thereक्रमe a
 *    single word in a biपंचांगap may straddle two pages in the extent buffer.
 */
#घोषणा BIT_BYTE(nr) ((nr) / BITS_PER_BYTE)
#घोषणा BYTE_MASK ((1 << BITS_PER_BYTE) - 1)
#घोषणा BITMAP_FIRST_BYTE_MASK(start) \
	((BYTE_MASK << ((start) & (BITS_PER_BYTE - 1))) & BYTE_MASK)
#घोषणा BITMAP_LAST_BYTE_MASK(nbits) \
	(BYTE_MASK >> (-(nbits) & (BITS_PER_BYTE - 1)))

काष्ठा btrfs_root;
काष्ठा btrfs_inode;
काष्ठा btrfs_io_bio;
काष्ठा btrfs_fs_info;
काष्ठा io_failure_record;
काष्ठा extent_io_tree;

प्रकार blk_status_t (submit_bio_hook_t)(काष्ठा inode *inode, काष्ठा bio *bio,
					 पूर्णांक mirror_num,
					 अचिन्हित दीर्घ bio_flags);

प्रकार blk_status_t (extent_submit_bio_start_t)(काष्ठा inode *inode,
		काष्ठा bio *bio, u64 dio_file_offset);

#घोषणा INLINE_EXTENT_BUFFER_PAGES     (BTRFS_MAX_METADATA_BLOCKSIZE / PAGE_SIZE)
काष्ठा extent_buffer अणु
	u64 start;
	अचिन्हित दीर्घ len;
	अचिन्हित दीर्घ bflags;
	काष्ठा btrfs_fs_info *fs_info;
	spinlock_t refs_lock;
	atomic_t refs;
	atomic_t io_pages;
	पूर्णांक पढ़ो_mirror;
	काष्ठा rcu_head rcu_head;
	pid_t lock_owner;
	/* >= 0 अगर eb beदीर्घs to a log tree, -1 otherwise */
	s8 log_index;

	काष्ठा rw_semaphore lock;

	काष्ठा page *pages[INLINE_EXTENT_BUFFER_PAGES];
	काष्ठा list_head release_list;
#अगर_घोषित CONFIG_BTRFS_DEBUG
	काष्ठा list_head leak_list;
#पूर्ण_अगर
पूर्ण;

/*
 * Structure to record how many bytes and which ranges are set/cleared
 */
काष्ठा extent_changeset अणु
	/* How many bytes are set/cleared in this operation */
	अचिन्हित पूर्णांक bytes_changed;

	/* Changed ranges */
	काष्ठा ulist range_changed;
पूर्ण;

अटल अंतरभूत व्योम extent_changeset_init(काष्ठा extent_changeset *changeset)
अणु
	changeset->bytes_changed = 0;
	ulist_init(&changeset->range_changed);
पूर्ण

अटल अंतरभूत काष्ठा extent_changeset *extent_changeset_alloc(व्योम)
अणु
	काष्ठा extent_changeset *ret;

	ret = kदो_स्मृति(माप(*ret), GFP_KERNEL);
	अगर (!ret)
		वापस शून्य;

	extent_changeset_init(ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम extent_changeset_release(काष्ठा extent_changeset *changeset)
अणु
	अगर (!changeset)
		वापस;
	changeset->bytes_changed = 0;
	ulist_release(&changeset->range_changed);
पूर्ण

अटल अंतरभूत व्योम extent_changeset_मुक्त(काष्ठा extent_changeset *changeset)
अणु
	अगर (!changeset)
		वापस;
	extent_changeset_release(changeset);
	kमुक्त(changeset);
पूर्ण

अटल अंतरभूत व्योम extent_set_compress_type(अचिन्हित दीर्घ *bio_flags,
					    पूर्णांक compress_type)
अणु
	*bio_flags |= compress_type << EXTENT_BIO_FLAG_SHIFT;
पूर्ण

अटल अंतरभूत पूर्णांक extent_compress_type(अचिन्हित दीर्घ bio_flags)
अणु
	वापस bio_flags >> EXTENT_BIO_FLAG_SHIFT;
पूर्ण

काष्ठा extent_map_tree;

प्रकार काष्ठा extent_map *(get_extent_t)(काष्ठा btrfs_inode *inode,
					  काष्ठा page *page, माप_प्रकार pg_offset,
					  u64 start, u64 len);

पूर्णांक try_release_extent_mapping(काष्ठा page *page, gfp_t mask);
पूर्णांक try_release_extent_buffer(काष्ठा page *page);

पूर्णांक __must_check submit_one_bio(काष्ठा bio *bio, पूर्णांक mirror_num,
				अचिन्हित दीर्घ bio_flags);
पूर्णांक btrfs_करो_पढ़ोpage(काष्ठा page *page, काष्ठा extent_map **em_cached,
		      काष्ठा bio **bio, अचिन्हित दीर्घ *bio_flags,
		      अचिन्हित पूर्णांक पढ़ो_flags, u64 *prev_em_start);
पूर्णांक extent_ग_लिखो_full_page(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc);
पूर्णांक extent_ग_लिखो_locked_range(काष्ठा inode *inode, u64 start, u64 end,
			      पूर्णांक mode);
पूर्णांक extent_ग_लिखोpages(काष्ठा address_space *mapping,
		      काष्ठा ग_लिखोback_control *wbc);
पूर्णांक btree_ग_लिखो_cache_pages(काष्ठा address_space *mapping,
			    काष्ठा ग_लिखोback_control *wbc);
व्योम extent_पढ़ोahead(काष्ठा पढ़ोahead_control *rac);
पूर्णांक extent_fiemap(काष्ठा btrfs_inode *inode, काष्ठा fiemap_extent_info *fieinfo,
		  u64 start, u64 len);
पूर्णांक set_page_extent_mapped(काष्ठा page *page);
व्योम clear_page_extent_mapped(काष्ठा page *page);

काष्ठा extent_buffer *alloc_extent_buffer(काष्ठा btrfs_fs_info *fs_info,
					  u64 start, u64 owner_root, पूर्णांक level);
काष्ठा extent_buffer *__alloc_dummy_extent_buffer(काष्ठा btrfs_fs_info *fs_info,
						  u64 start, अचिन्हित दीर्घ len);
काष्ठा extent_buffer *alloc_dummy_extent_buffer(काष्ठा btrfs_fs_info *fs_info,
						u64 start);
काष्ठा extent_buffer *btrfs_clone_extent_buffer(स्थिर काष्ठा extent_buffer *src);
काष्ठा extent_buffer *find_extent_buffer(काष्ठा btrfs_fs_info *fs_info,
					 u64 start);
व्योम मुक्त_extent_buffer(काष्ठा extent_buffer *eb);
व्योम मुक्त_extent_buffer_stale(काष्ठा extent_buffer *eb);
#घोषणा WAIT_NONE	0
#घोषणा WAIT_COMPLETE	1
#घोषणा WAIT_PAGE_LOCK	2
पूर्णांक पढ़ो_extent_buffer_pages(काष्ठा extent_buffer *eb, पूर्णांक रुको,
			     पूर्णांक mirror_num);
व्योम रुको_on_extent_buffer_ग_लिखोback(काष्ठा extent_buffer *eb);
व्योम btrfs_पढ़ोahead_tree_block(काष्ठा btrfs_fs_info *fs_info,
				u64 bytenr, u64 owner_root, u64 gen, पूर्णांक level);
व्योम btrfs_पढ़ोahead_node_child(काष्ठा extent_buffer *node, पूर्णांक slot);

अटल अंतरभूत पूर्णांक num_extent_pages(स्थिर काष्ठा extent_buffer *eb)
अणु
	/*
	 * For sectorsize == PAGE_SIZE हाल, since nodesize is always aligned to
	 * sectorsize, it's just eb->len >> PAGE_SHIFT.
	 *
	 * For sectorsize < PAGE_SIZE हाल, we could have nodesize < PAGE_SIZE,
	 * thus have to ensure we get at least one page.
	 */
	वापस (eb->len >> PAGE_SHIFT) ?: 1;
पूर्ण

अटल अंतरभूत पूर्णांक extent_buffer_uptodate(स्थिर काष्ठा extent_buffer *eb)
अणु
	वापस test_bit(EXTENT_BUFFER_UPTODATE, &eb->bflags);
पूर्ण

पूर्णांक स_भेद_extent_buffer(स्थिर काष्ठा extent_buffer *eb, स्थिर व्योम *ptrv,
			 अचिन्हित दीर्घ start, अचिन्हित दीर्घ len);
व्योम पढ़ो_extent_buffer(स्थिर काष्ठा extent_buffer *eb, व्योम *dst,
			अचिन्हित दीर्घ start,
			अचिन्हित दीर्घ len);
पूर्णांक पढ़ो_extent_buffer_to_user_nofault(स्थिर काष्ठा extent_buffer *eb,
				       व्योम __user *dst, अचिन्हित दीर्घ start,
				       अचिन्हित दीर्घ len);
व्योम ग_लिखो_extent_buffer_fsid(स्थिर काष्ठा extent_buffer *eb, स्थिर व्योम *src);
व्योम ग_लिखो_extent_buffer_chunk_tree_uuid(स्थिर काष्ठा extent_buffer *eb,
		स्थिर व्योम *src);
व्योम ग_लिखो_extent_buffer(स्थिर काष्ठा extent_buffer *eb, स्थिर व्योम *src,
			 अचिन्हित दीर्घ start, अचिन्हित दीर्घ len);
व्योम copy_extent_buffer_full(स्थिर काष्ठा extent_buffer *dst,
			     स्थिर काष्ठा extent_buffer *src);
व्योम copy_extent_buffer(स्थिर काष्ठा extent_buffer *dst,
			स्थिर काष्ठा extent_buffer *src,
			अचिन्हित दीर्घ dst_offset, अचिन्हित दीर्घ src_offset,
			अचिन्हित दीर्घ len);
व्योम स_नकल_extent_buffer(स्थिर काष्ठा extent_buffer *dst,
			  अचिन्हित दीर्घ dst_offset, अचिन्हित दीर्घ src_offset,
			  अचिन्हित दीर्घ len);
व्योम स_हटाओ_extent_buffer(स्थिर काष्ठा extent_buffer *dst,
			   अचिन्हित दीर्घ dst_offset, अचिन्हित दीर्घ src_offset,
			   अचिन्हित दीर्घ len);
व्योम memzero_extent_buffer(स्थिर काष्ठा extent_buffer *eb, अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ len);
पूर्णांक extent_buffer_test_bit(स्थिर काष्ठा extent_buffer *eb, अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ pos);
व्योम extent_buffer_biपंचांगap_set(स्थिर काष्ठा extent_buffer *eb, अचिन्हित दीर्घ start,
			      अचिन्हित दीर्घ pos, अचिन्हित दीर्घ len);
व्योम extent_buffer_biपंचांगap_clear(स्थिर काष्ठा extent_buffer *eb,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ pos,
				अचिन्हित दीर्घ len);
व्योम clear_extent_buffer_dirty(स्थिर काष्ठा extent_buffer *eb);
bool set_extent_buffer_dirty(काष्ठा extent_buffer *eb);
व्योम set_extent_buffer_uptodate(काष्ठा extent_buffer *eb);
व्योम clear_extent_buffer_uptodate(काष्ठा extent_buffer *eb);
पूर्णांक extent_buffer_under_io(स्थिर काष्ठा extent_buffer *eb);
व्योम extent_range_clear_dirty_क्रम_io(काष्ठा inode *inode, u64 start, u64 end);
व्योम extent_range_redirty_क्रम_io(काष्ठा inode *inode, u64 start, u64 end);
व्योम extent_clear_unlock_delalloc(काष्ठा btrfs_inode *inode, u64 start, u64 end,
				  काष्ठा page *locked_page,
				  u32 bits_to_clear, अचिन्हित दीर्घ page_ops);
काष्ठा bio *btrfs_bio_alloc(u64 first_byte);
काष्ठा bio *btrfs_io_bio_alloc(अचिन्हित पूर्णांक nr_iovecs);
काष्ठा bio *btrfs_bio_clone(काष्ठा bio *bio);
काष्ठा bio *btrfs_bio_clone_partial(काष्ठा bio *orig, पूर्णांक offset, पूर्णांक size);

पूर्णांक repair_io_failure(काष्ठा btrfs_fs_info *fs_info, u64 ino, u64 start,
		      u64 length, u64 logical, काष्ठा page *page,
		      अचिन्हित पूर्णांक pg_offset, पूर्णांक mirror_num);
व्योम end_extent_ग_लिखोpage(काष्ठा page *page, पूर्णांक err, u64 start, u64 end);
पूर्णांक btrfs_repair_eb_io_failure(स्थिर काष्ठा extent_buffer *eb, पूर्णांक mirror_num);

/*
 * When IO fails, either with EIO or csum verअगरication fails, we
 * try other mirrors that might have a good copy of the data.  This
 * io_failure_record is used to record state as we go through all the
 * mirrors.  If another mirror has good data, the page is set up to date
 * and things जारी.  If a good mirror can't be found, the original
 * bio end_io callback is called to indicate things have failed.
 */
काष्ठा io_failure_record अणु
	काष्ठा page *page;
	u64 start;
	u64 len;
	u64 logical;
	अचिन्हित दीर्घ bio_flags;
	पूर्णांक this_mirror;
	पूर्णांक failed_mirror;
	पूर्णांक in_validation;
पूर्ण;


blk_status_t btrfs_submit_पढ़ो_repair(काष्ठा inode *inode,
				      काष्ठा bio *failed_bio, u32 bio_offset,
				      काष्ठा page *page, अचिन्हित पूर्णांक pgoff,
				      u64 start, u64 end, पूर्णांक failed_mirror,
				      submit_bio_hook_t *submit_bio_hook);

#अगर_घोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
bool find_lock_delalloc_range(काष्ठा inode *inode,
			     काष्ठा page *locked_page, u64 *start,
			     u64 *end);
#पूर्ण_अगर
काष्ठा extent_buffer *alloc_test_extent_buffer(काष्ठा btrfs_fs_info *fs_info,
					       u64 start);

#अगर_घोषित CONFIG_BTRFS_DEBUG
व्योम btrfs_extent_buffer_leak_debug_check(काष्ठा btrfs_fs_info *fs_info);
#अन्यथा
#घोषणा btrfs_extent_buffer_leak_debug_check(fs_info)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर
