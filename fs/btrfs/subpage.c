<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/slab.h>
#समावेश "ctree.h"
#समावेश "subpage.h"

/*
 * Subpage (sectorsize < PAGE_SIZE) support overview:
 *
 * Limitations:
 *
 * - Only support 64K page size क्रम now
 *   This is to make metadata handling easier, as 64K page would ensure
 *   all nodesize would fit inside one page, thus we करोn't need to handle
 *   हालs where a tree block crosses several pages.
 *
 * - Only metadata पढ़ो-ग_लिखो क्रम now
 *   The data पढ़ो-ग_लिखो part is in development.
 *
 * - Metadata can't cross 64K page boundary
 *   btrfs-progs and kernel have करोne that क्रम a जबतक, thus only ancient
 *   fileप्रणालीs could have such problem.  For such हाल, करो a graceful
 *   rejection.
 *
 * Special behavior:
 *
 * - Metadata
 *   Metadata पढ़ो is fully supported.
 *   Meaning when पढ़ोing one tree block will only trigger the पढ़ो क्रम the
 *   needed range, other unrelated range in the same page will not be touched.
 *
 *   Metadata ग_लिखो support is partial.
 *   The ग_लिखोback is still क्रम the full page, but we will only submit
 *   the dirty extent buffers in the page.
 *
 *   This means, अगर we have a metadata page like this:
 *
 *   Page offset
 *   0         16K         32K         48K        64K
 *   |/////////|           |///////////|
 *        \- Tree block A        \- Tree block B
 *
 *   Even अगर we just want to ग_लिखोback tree block A, we will also ग_लिखोback
 *   tree block B अगर it's also dirty.
 *
 *   This may cause extra metadata ग_लिखोback which results more COW.
 *
 * Implementation:
 *
 * - Common
 *   Both metadata and data will use a new काष्ठाure, btrfs_subpage, to
 *   record the status of each sector inside a page.  This provides the extra
 *   granularity needed.
 *
 * - Metadata
 *   Since we have multiple tree blocks inside one page, we can't rely on page
 *   locking anymore, or we will have greatly reduced concurrency or even
 *   deadlocks (hold one tree lock जबतक trying to lock another tree lock in
 *   the same page).
 *
 *   Thus क्रम metadata locking, subpage support relies on io_tree locking only.
 *   This means a slightly higher tree locking latency.
 */

पूर्णांक btrfs_attach_subpage(स्थिर काष्ठा btrfs_fs_info *fs_info,
			 काष्ठा page *page, क्रमागत btrfs_subpage_type type)
अणु
	काष्ठा btrfs_subpage *subpage = शून्य;
	पूर्णांक ret;

	/*
	 * We have हालs like a dummy extent buffer page, which is not mappped
	 * and करोesn't need to be locked.
	 */
	अगर (page->mapping)
		ASSERT(PageLocked(page));
	/* Either not subpage, or the page alपढ़ोy has निजी attached */
	अगर (fs_info->sectorsize == PAGE_SIZE || PagePrivate(page))
		वापस 0;

	ret = btrfs_alloc_subpage(fs_info, &subpage, type);
	अगर (ret < 0)
		वापस ret;
	attach_page_निजी(page, subpage);
	वापस 0;
पूर्ण

व्योम btrfs_detach_subpage(स्थिर काष्ठा btrfs_fs_info *fs_info,
			  काष्ठा page *page)
अणु
	काष्ठा btrfs_subpage *subpage;

	/* Either not subpage, or alपढ़ोy detached */
	अगर (fs_info->sectorsize == PAGE_SIZE || !PagePrivate(page))
		वापस;

	subpage = (काष्ठा btrfs_subpage *)detach_page_निजी(page);
	ASSERT(subpage);
	btrfs_मुक्त_subpage(subpage);
पूर्ण

पूर्णांक btrfs_alloc_subpage(स्थिर काष्ठा btrfs_fs_info *fs_info,
			काष्ठा btrfs_subpage **ret,
			क्रमागत btrfs_subpage_type type)
अणु
	अगर (fs_info->sectorsize == PAGE_SIZE)
		वापस 0;

	*ret = kzalloc(माप(काष्ठा btrfs_subpage), GFP_NOFS);
	अगर (!*ret)
		वापस -ENOMEM;
	spin_lock_init(&(*ret)->lock);
	अगर (type == BTRFS_SUBPAGE_METADATA)
		atomic_set(&(*ret)->eb_refs, 0);
	अन्यथा
		atomic_set(&(*ret)->पढ़ोers, 0);
	वापस 0;
पूर्ण

व्योम btrfs_मुक्त_subpage(काष्ठा btrfs_subpage *subpage)
अणु
	kमुक्त(subpage);
पूर्ण

/*
 * Increase the eb_refs of current subpage.
 *
 * This is important क्रम eb allocation, to prevent race with last eb मुक्तing
 * of the same page.
 * With the eb_refs increased beक्रमe the eb inserted पूर्णांकo radix tree,
 * detach_extent_buffer_page() won't detach the page private while we're still
 * allocating the extent buffer.
 */
व्योम btrfs_page_inc_eb_refs(स्थिर काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा page *page)
अणु
	काष्ठा btrfs_subpage *subpage;

	अगर (fs_info->sectorsize == PAGE_SIZE)
		वापस;

	ASSERT(PagePrivate(page) && page->mapping);
	lockdep_निश्चित_held(&page->mapping->निजी_lock);

	subpage = (काष्ठा btrfs_subpage *)page->निजी;
	atomic_inc(&subpage->eb_refs);
पूर्ण

व्योम btrfs_page_dec_eb_refs(स्थिर काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा page *page)
अणु
	काष्ठा btrfs_subpage *subpage;

	अगर (fs_info->sectorsize == PAGE_SIZE)
		वापस;

	ASSERT(PagePrivate(page) && page->mapping);
	lockdep_निश्चित_held(&page->mapping->निजी_lock);

	subpage = (काष्ठा btrfs_subpage *)page->निजी;
	ASSERT(atomic_पढ़ो(&subpage->eb_refs));
	atomic_dec(&subpage->eb_refs);
पूर्ण

अटल व्योम btrfs_subpage_निश्चित(स्थिर काष्ठा btrfs_fs_info *fs_info,
		काष्ठा page *page, u64 start, u32 len)
अणु
	/* Basic checks */
	ASSERT(PagePrivate(page) && page->निजी);
	ASSERT(IS_ALIGNED(start, fs_info->sectorsize) &&
	       IS_ALIGNED(len, fs_info->sectorsize));
	/*
	 * The range check only works क्रम mapped page, we can still have
	 * unmapped page like dummy extent buffer pages.
	 */
	अगर (page->mapping)
		ASSERT(page_offset(page) <= start &&
		       start + len <= page_offset(page) + PAGE_SIZE);
पूर्ण

व्योम btrfs_subpage_start_पढ़ोer(स्थिर काष्ठा btrfs_fs_info *fs_info,
		काष्ठा page *page, u64 start, u32 len)
अणु
	काष्ठा btrfs_subpage *subpage = (काष्ठा btrfs_subpage *)page->निजी;
	स्थिर पूर्णांक nbits = len >> fs_info->sectorsize_bits;
	पूर्णांक ret;

	btrfs_subpage_निश्चित(fs_info, page, start, len);

	ret = atomic_add_वापस(nbits, &subpage->पढ़ोers);
	ASSERT(ret == nbits);
पूर्ण

व्योम btrfs_subpage_end_पढ़ोer(स्थिर काष्ठा btrfs_fs_info *fs_info,
		काष्ठा page *page, u64 start, u32 len)
अणु
	काष्ठा btrfs_subpage *subpage = (काष्ठा btrfs_subpage *)page->निजी;
	स्थिर पूर्णांक nbits = len >> fs_info->sectorsize_bits;

	btrfs_subpage_निश्चित(fs_info, page, start, len);
	ASSERT(atomic_पढ़ो(&subpage->पढ़ोers) >= nbits);
	अगर (atomic_sub_and_test(nbits, &subpage->पढ़ोers))
		unlock_page(page);
पूर्ण

/*
 * Convert the [start, start + len) range पूर्णांकo a u16 biपंचांगap
 *
 * For example: अगर start == page_offset() + 16K, len = 16K, we get 0x00f0.
 */
अटल u16 btrfs_subpage_calc_biपंचांगap(स्थिर काष्ठा btrfs_fs_info *fs_info,
		काष्ठा page *page, u64 start, u32 len)
अणु
	स्थिर पूर्णांक bit_start = offset_in_page(start) >> fs_info->sectorsize_bits;
	स्थिर पूर्णांक nbits = len >> fs_info->sectorsize_bits;

	btrfs_subpage_निश्चित(fs_info, page, start, len);

	/*
	 * Here nbits can be 16, thus can go beyond u16 range. We make the
	 * first left shअगरt to be calculate in अचिन्हित दीर्घ (at least u32),
	 * then truncate the result to u16.
	 */
	वापस (u16)(((1UL << nbits) - 1) << bit_start);
पूर्ण

व्योम btrfs_subpage_set_uptodate(स्थिर काष्ठा btrfs_fs_info *fs_info,
		काष्ठा page *page, u64 start, u32 len)
अणु
	काष्ठा btrfs_subpage *subpage = (काष्ठा btrfs_subpage *)page->निजी;
	स्थिर u16 पंचांगp = btrfs_subpage_calc_biपंचांगap(fs_info, page, start, len);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&subpage->lock, flags);
	subpage->uptodate_biपंचांगap |= पंचांगp;
	अगर (subpage->uptodate_biपंचांगap == U16_MAX)
		SetPageUptodate(page);
	spin_unlock_irqrestore(&subpage->lock, flags);
पूर्ण

व्योम btrfs_subpage_clear_uptodate(स्थिर काष्ठा btrfs_fs_info *fs_info,
		काष्ठा page *page, u64 start, u32 len)
अणु
	काष्ठा btrfs_subpage *subpage = (काष्ठा btrfs_subpage *)page->निजी;
	स्थिर u16 पंचांगp = btrfs_subpage_calc_biपंचांगap(fs_info, page, start, len);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&subpage->lock, flags);
	subpage->uptodate_biपंचांगap &= ~पंचांगp;
	ClearPageUptodate(page);
	spin_unlock_irqrestore(&subpage->lock, flags);
पूर्ण

व्योम btrfs_subpage_set_error(स्थिर काष्ठा btrfs_fs_info *fs_info,
		काष्ठा page *page, u64 start, u32 len)
अणु
	काष्ठा btrfs_subpage *subpage = (काष्ठा btrfs_subpage *)page->निजी;
	स्थिर u16 पंचांगp = btrfs_subpage_calc_biपंचांगap(fs_info, page, start, len);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&subpage->lock, flags);
	subpage->error_biपंचांगap |= पंचांगp;
	SetPageError(page);
	spin_unlock_irqrestore(&subpage->lock, flags);
पूर्ण

व्योम btrfs_subpage_clear_error(स्थिर काष्ठा btrfs_fs_info *fs_info,
		काष्ठा page *page, u64 start, u32 len)
अणु
	काष्ठा btrfs_subpage *subpage = (काष्ठा btrfs_subpage *)page->निजी;
	स्थिर u16 पंचांगp = btrfs_subpage_calc_biपंचांगap(fs_info, page, start, len);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&subpage->lock, flags);
	subpage->error_biपंचांगap &= ~पंचांगp;
	अगर (subpage->error_biपंचांगap == 0)
		ClearPageError(page);
	spin_unlock_irqrestore(&subpage->lock, flags);
पूर्ण

व्योम btrfs_subpage_set_dirty(स्थिर काष्ठा btrfs_fs_info *fs_info,
		काष्ठा page *page, u64 start, u32 len)
अणु
	काष्ठा btrfs_subpage *subpage = (काष्ठा btrfs_subpage *)page->निजी;
	u16 पंचांगp = btrfs_subpage_calc_biपंचांगap(fs_info, page, start, len);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&subpage->lock, flags);
	subpage->dirty_biपंचांगap |= पंचांगp;
	spin_unlock_irqrestore(&subpage->lock, flags);
	set_page_dirty(page);
पूर्ण

/*
 * Extra clear_and_test function क्रम subpage dirty biपंचांगap.
 *
 * Return true अगर we're the last bits in the dirty_biपंचांगap and clear the
 * dirty_biपंचांगap.
 * Return false otherwise.
 *
 * NOTE: Callers should manually clear page dirty क्रम true हाल, as we have
 * extra handling क्रम tree blocks.
 */
bool btrfs_subpage_clear_and_test_dirty(स्थिर काष्ठा btrfs_fs_info *fs_info,
		काष्ठा page *page, u64 start, u32 len)
अणु
	काष्ठा btrfs_subpage *subpage = (काष्ठा btrfs_subpage *)page->निजी;
	u16 पंचांगp = btrfs_subpage_calc_biपंचांगap(fs_info, page, start, len);
	अचिन्हित दीर्घ flags;
	bool last = false;

	spin_lock_irqsave(&subpage->lock, flags);
	subpage->dirty_biपंचांगap &= ~पंचांगp;
	अगर (subpage->dirty_biपंचांगap == 0)
		last = true;
	spin_unlock_irqrestore(&subpage->lock, flags);
	वापस last;
पूर्ण

व्योम btrfs_subpage_clear_dirty(स्थिर काष्ठा btrfs_fs_info *fs_info,
		काष्ठा page *page, u64 start, u32 len)
अणु
	bool last;

	last = btrfs_subpage_clear_and_test_dirty(fs_info, page, start, len);
	अगर (last)
		clear_page_dirty_क्रम_io(page);
पूर्ण

व्योम btrfs_subpage_set_ग_लिखोback(स्थिर काष्ठा btrfs_fs_info *fs_info,
		काष्ठा page *page, u64 start, u32 len)
अणु
	काष्ठा btrfs_subpage *subpage = (काष्ठा btrfs_subpage *)page->निजी;
	u16 पंचांगp = btrfs_subpage_calc_biपंचांगap(fs_info, page, start, len);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&subpage->lock, flags);
	subpage->ग_लिखोback_biपंचांगap |= पंचांगp;
	set_page_ग_लिखोback(page);
	spin_unlock_irqrestore(&subpage->lock, flags);
पूर्ण

व्योम btrfs_subpage_clear_ग_लिखोback(स्थिर काष्ठा btrfs_fs_info *fs_info,
		काष्ठा page *page, u64 start, u32 len)
अणु
	काष्ठा btrfs_subpage *subpage = (काष्ठा btrfs_subpage *)page->निजी;
	u16 पंचांगp = btrfs_subpage_calc_biपंचांगap(fs_info, page, start, len);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&subpage->lock, flags);
	subpage->ग_लिखोback_biपंचांगap &= ~पंचांगp;
	अगर (subpage->ग_लिखोback_biपंचांगap == 0)
		end_page_ग_लिखोback(page);
	spin_unlock_irqrestore(&subpage->lock, flags);
पूर्ण

/*
 * Unlike set/clear which is dependent on each page status, क्रम test all bits
 * are tested in the same way.
 */
#घोषणा IMPLEMENT_BTRFS_SUBPAGE_TEST_OP(name)				\
bool btrfs_subpage_test_##name(स्थिर काष्ठा btrfs_fs_info *fs_info,	\
		काष्ठा page *page, u64 start, u32 len)			\
अणु									\
	काष्ठा btrfs_subpage *subpage = (काष्ठा btrfs_subpage *)page->निजी; \
	स्थिर u16 पंचांगp = btrfs_subpage_calc_biपंचांगap(fs_info, page, start, len); \
	अचिन्हित दीर्घ flags;						\
	bool ret;							\
									\
	spin_lock_irqsave(&subpage->lock, flags);			\
	ret = ((subpage->name##_biपंचांगap & पंचांगp) == पंचांगp);			\
	spin_unlock_irqrestore(&subpage->lock, flags);			\
	वापस ret;							\
पूर्ण
IMPLEMENT_BTRFS_SUBPAGE_TEST_OP(uptodate);
IMPLEMENT_BTRFS_SUBPAGE_TEST_OP(error);
IMPLEMENT_BTRFS_SUBPAGE_TEST_OP(dirty);
IMPLEMENT_BTRFS_SUBPAGE_TEST_OP(ग_लिखोback);

/*
 * Note that, in selftests (extent-io-tests), we can have empty fs_info passed
 * in.  We only test sectorsize == PAGE_SIZE हालs so far, thus we can fall
 * back to regular sectorsize branch.
 */
#घोषणा IMPLEMENT_BTRFS_PAGE_OPS(name, set_page_func, clear_page_func,	\
			       test_page_func)				\
व्योम btrfs_page_set_##name(स्थिर काष्ठा btrfs_fs_info *fs_info,		\
		काष्ठा page *page, u64 start, u32 len)			\
अणु									\
	अगर (unlikely(!fs_info) || fs_info->sectorsize == PAGE_SIZE) अणु	\
		set_page_func(page);					\
		वापस;							\
	पूर्ण								\
	btrfs_subpage_set_##name(fs_info, page, start, len);		\
पूर्ण									\
व्योम btrfs_page_clear_##name(स्थिर काष्ठा btrfs_fs_info *fs_info,	\
		काष्ठा page *page, u64 start, u32 len)			\
अणु									\
	अगर (unlikely(!fs_info) || fs_info->sectorsize == PAGE_SIZE) अणु	\
		clear_page_func(page);					\
		वापस;							\
	पूर्ण								\
	btrfs_subpage_clear_##name(fs_info, page, start, len);		\
पूर्ण									\
bool btrfs_page_test_##name(स्थिर काष्ठा btrfs_fs_info *fs_info,	\
		काष्ठा page *page, u64 start, u32 len)			\
अणु									\
	अगर (unlikely(!fs_info) || fs_info->sectorsize == PAGE_SIZE)	\
		वापस test_page_func(page);				\
	वापस btrfs_subpage_test_##name(fs_info, page, start, len);	\
पूर्ण
IMPLEMENT_BTRFS_PAGE_OPS(uptodate, SetPageUptodate, ClearPageUptodate,
			 PageUptodate);
IMPLEMENT_BTRFS_PAGE_OPS(error, SetPageError, ClearPageError, PageError);
IMPLEMENT_BTRFS_PAGE_OPS(dirty, set_page_dirty, clear_page_dirty_क्रम_io,
			 PageDirty);
IMPLEMENT_BTRFS_PAGE_OPS(ग_लिखोback, set_page_ग_लिखोback, end_page_ग_लिखोback,
			 PageWriteback);
