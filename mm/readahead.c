<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mm/पढ़ोahead.c - address_space-level file पढ़ोahead.
 *
 * Copyright (C) 2002, Linus Torvalds
 *
 * 09Apr2002	Andrew Morton
 *		Initial version.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/dax.h>
#समावेश <linux/gfp.h>
#समावेश <linux/export.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/file.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/blk-cgroup.h>
#समावेश <linux/fadvise.h>
#समावेश <linux/sched/mm.h>

#समावेश "internal.h"

/*
 * Initialise a काष्ठा file's पढ़ोahead state.  Assumes that the caller has
 * स_रखो *ra to zero.
 */
व्योम
file_ra_state_init(काष्ठा file_ra_state *ra, काष्ठा address_space *mapping)
अणु
	ra->ra_pages = inode_to_bdi(mapping->host)->ra_pages;
	ra->prev_pos = -1;
पूर्ण
EXPORT_SYMBOL_GPL(file_ra_state_init);

/*
 * see अगर a page needs releasing upon पढ़ो_cache_pages() failure
 * - the caller of पढ़ो_cache_pages() may have set PG_निजी or PG_fscache
 *   beक्रमe calling, such as the NFS fs marking pages that are cached locally
 *   on disk, thus we need to give the fs a chance to clean up in the event of
 *   an error
 */
अटल व्योम पढ़ो_cache_pages_invalidate_page(काष्ठा address_space *mapping,
					     काष्ठा page *page)
अणु
	अगर (page_has_निजी(page)) अणु
		अगर (!trylock_page(page))
			BUG();
		page->mapping = mapping;
		करो_invalidatepage(page, 0, PAGE_SIZE);
		page->mapping = शून्य;
		unlock_page(page);
	पूर्ण
	put_page(page);
पूर्ण

/*
 * release a list of pages, invalidating them first अगर need be
 */
अटल व्योम पढ़ो_cache_pages_invalidate_pages(काष्ठा address_space *mapping,
					      काष्ठा list_head *pages)
अणु
	काष्ठा page *victim;

	जबतक (!list_empty(pages)) अणु
		victim = lru_to_page(pages);
		list_del(&victim->lru);
		पढ़ो_cache_pages_invalidate_page(mapping, victim);
	पूर्ण
पूर्ण

/**
 * पढ़ो_cache_pages - populate an address space with some pages & start पढ़ोs against them
 * @mapping: the address_space
 * @pages: The address of a list_head which contains the target pages.  These
 *   pages have their ->index populated and are otherwise uninitialised.
 * @filler: callback routine क्रम filling a single page.
 * @data: निजी data क्रम the callback routine.
 *
 * Hides the details of the LRU cache etc from the fileप्रणालीs.
 *
 * Returns: %0 on success, error वापस by @filler otherwise
 */
पूर्णांक पढ़ो_cache_pages(काष्ठा address_space *mapping, काष्ठा list_head *pages,
			पूर्णांक (*filler)(व्योम *, काष्ठा page *), व्योम *data)
अणु
	काष्ठा page *page;
	पूर्णांक ret = 0;

	जबतक (!list_empty(pages)) अणु
		page = lru_to_page(pages);
		list_del(&page->lru);
		अगर (add_to_page_cache_lru(page, mapping, page->index,
				पढ़ोahead_gfp_mask(mapping))) अणु
			पढ़ो_cache_pages_invalidate_page(mapping, page);
			जारी;
		पूर्ण
		put_page(page);

		ret = filler(data, page);
		अगर (unlikely(ret)) अणु
			पढ़ो_cache_pages_invalidate_pages(mapping, pages);
			अवरोध;
		पूर्ण
		task_io_account_पढ़ो(PAGE_SIZE);
	पूर्ण
	वापस ret;
पूर्ण

EXPORT_SYMBOL(पढ़ो_cache_pages);

अटल व्योम पढ़ो_pages(काष्ठा पढ़ोahead_control *rac, काष्ठा list_head *pages,
		bool skip_page)
अणु
	स्थिर काष्ठा address_space_operations *aops = rac->mapping->a_ops;
	काष्ठा page *page;
	काष्ठा blk_plug plug;

	अगर (!पढ़ोahead_count(rac))
		जाओ out;

	blk_start_plug(&plug);

	अगर (aops->पढ़ोahead) अणु
		aops->पढ़ोahead(rac);
		/* Clean up the reमुख्यing pages */
		जबतक ((page = पढ़ोahead_page(rac))) अणु
			unlock_page(page);
			put_page(page);
		पूर्ण
	पूर्ण अन्यथा अगर (aops->पढ़ोpages) अणु
		aops->पढ़ोpages(rac->file, rac->mapping, pages,
				पढ़ोahead_count(rac));
		/* Clean up the reमुख्यing pages */
		put_pages_list(pages);
		rac->_index += rac->_nr_pages;
		rac->_nr_pages = 0;
	पूर्ण अन्यथा अणु
		जबतक ((page = पढ़ोahead_page(rac))) अणु
			aops->पढ़ोpage(rac->file, page);
			put_page(page);
		पूर्ण
	पूर्ण

	blk_finish_plug(&plug);

	BUG_ON(!list_empty(pages));
	BUG_ON(पढ़ोahead_count(rac));

out:
	अगर (skip_page)
		rac->_index++;
पूर्ण

/**
 * page_cache_ra_unbounded - Start unchecked पढ़ोahead.
 * @ractl: Readahead control.
 * @nr_to_पढ़ो: The number of pages to पढ़ो.
 * @lookahead_size: Where to start the next पढ़ोahead.
 *
 * This function is क्रम fileप्रणालीs to call when they want to start
 * पढ़ोahead beyond a file's stated i_size.  This is almost certainly
 * not the function you want to call.  Use page_cache_async_पढ़ोahead()
 * or page_cache_sync_पढ़ोahead() instead.
 *
 * Context: File is referenced by caller.  Mutexes may be held by caller.
 * May sleep, but will not reenter fileप्रणाली to reclaim memory.
 */
व्योम page_cache_ra_unbounded(काष्ठा पढ़ोahead_control *ractl,
		अचिन्हित दीर्घ nr_to_पढ़ो, अचिन्हित दीर्घ lookahead_size)
अणु
	काष्ठा address_space *mapping = ractl->mapping;
	अचिन्हित दीर्घ index = पढ़ोahead_index(ractl);
	LIST_HEAD(page_pool);
	gfp_t gfp_mask = पढ़ोahead_gfp_mask(mapping);
	अचिन्हित दीर्घ i;

	/*
	 * Partway through the पढ़ोahead operation, we will have added
	 * locked pages to the page cache, but will not yet have submitted
	 * them क्रम I/O.  Adding another page may need to allocate memory,
	 * which can trigger memory reclaim.  Telling the VM we're in
	 * the middle of a fileप्रणाली operation will cause it to not
	 * touch file-backed pages, preventing a deadlock.  Most (all?)
	 * fileप्रणालीs alपढ़ोy specअगरy __GFP_NOFS in their mapping's
	 * gfp_mask, but let's be explicit here.
	 */
	अचिन्हित पूर्णांक nofs = meदो_स्मृति_nofs_save();

	/*
	 * Pपुनः_स्मृतिate as many pages as we will need.
	 */
	क्रम (i = 0; i < nr_to_पढ़ो; i++) अणु
		काष्ठा page *page = xa_load(&mapping->i_pages, index + i);

		अगर (page && !xa_is_value(page)) अणु
			/*
			 * Page alपढ़ोy present?  Kick off the current batch
			 * of contiguous pages beक्रमe continuing with the
			 * next batch.  This page may be the one we would
			 * have पूर्णांकended to mark as Readahead, but we करोn't
			 * have a stable reference to this page, and it's
			 * not worth getting one just क्रम that.
			 */
			पढ़ो_pages(ractl, &page_pool, true);
			i = ractl->_index + ractl->_nr_pages - index - 1;
			जारी;
		पूर्ण

		page = __page_cache_alloc(gfp_mask);
		अगर (!page)
			अवरोध;
		अगर (mapping->a_ops->पढ़ोpages) अणु
			page->index = index + i;
			list_add(&page->lru, &page_pool);
		पूर्ण अन्यथा अगर (add_to_page_cache_lru(page, mapping, index + i,
					gfp_mask) < 0) अणु
			put_page(page);
			पढ़ो_pages(ractl, &page_pool, true);
			i = ractl->_index + ractl->_nr_pages - index - 1;
			जारी;
		पूर्ण
		अगर (i == nr_to_पढ़ो - lookahead_size)
			SetPageReadahead(page);
		ractl->_nr_pages++;
	पूर्ण

	/*
	 * Now start the IO.  We ignore I/O errors - अगर the page is not
	 * uptodate then the caller will launch पढ़ोpage again, and
	 * will then handle the error.
	 */
	पढ़ो_pages(ractl, &page_pool, false);
	meदो_स्मृति_nofs_restore(nofs);
पूर्ण
EXPORT_SYMBOL_GPL(page_cache_ra_unbounded);

/*
 * करो_page_cache_ra() actually पढ़ोs a chunk of disk.  It allocates
 * the pages first, then submits them क्रम I/O. This aव्योमs the very bad
 * behaviour which would occur अगर page allocations are causing VM ग_लिखोback.
 * We really करोn't want to पूर्णांकermingle पढ़ोs and ग_लिखोs like that.
 */
व्योम करो_page_cache_ra(काष्ठा पढ़ोahead_control *ractl,
		अचिन्हित दीर्घ nr_to_पढ़ो, अचिन्हित दीर्घ lookahead_size)
अणु
	काष्ठा inode *inode = ractl->mapping->host;
	अचिन्हित दीर्घ index = पढ़ोahead_index(ractl);
	loff_t isize = i_size_पढ़ो(inode);
	pgoff_t end_index;	/* The last page we want to पढ़ो */

	अगर (isize == 0)
		वापस;

	end_index = (isize - 1) >> PAGE_SHIFT;
	अगर (index > end_index)
		वापस;
	/* Don't पढ़ो past the page containing the last byte of the file */
	अगर (nr_to_पढ़ो > end_index - index)
		nr_to_पढ़ो = end_index - index + 1;

	page_cache_ra_unbounded(ractl, nr_to_पढ़ो, lookahead_size);
पूर्ण

/*
 * Chunk the पढ़ोahead पूर्णांकo 2 megabyte units, so that we करोn't pin too much
 * memory at once.
 */
व्योम क्रमce_page_cache_ra(काष्ठा पढ़ोahead_control *ractl,
		अचिन्हित दीर्घ nr_to_पढ़ो)
अणु
	काष्ठा address_space *mapping = ractl->mapping;
	काष्ठा file_ra_state *ra = ractl->ra;
	काष्ठा backing_dev_info *bdi = inode_to_bdi(mapping->host);
	अचिन्हित दीर्घ max_pages, index;

	अगर (unlikely(!mapping->a_ops->पढ़ोpage && !mapping->a_ops->पढ़ोpages &&
			!mapping->a_ops->पढ़ोahead))
		वापस;

	/*
	 * If the request exceeds the पढ़ोahead winकरोw, allow the पढ़ो to
	 * be up to the optimal hardware IO size
	 */
	index = पढ़ोahead_index(ractl);
	max_pages = max_t(अचिन्हित दीर्घ, bdi->io_pages, ra->ra_pages);
	nr_to_पढ़ो = min_t(अचिन्हित दीर्घ, nr_to_पढ़ो, max_pages);
	जबतक (nr_to_पढ़ो) अणु
		अचिन्हित दीर्घ this_chunk = (2 * 1024 * 1024) / PAGE_SIZE;

		अगर (this_chunk > nr_to_पढ़ो)
			this_chunk = nr_to_पढ़ो;
		ractl->_index = index;
		करो_page_cache_ra(ractl, this_chunk, 0);

		index += this_chunk;
		nr_to_पढ़ो -= this_chunk;
	पूर्ण
पूर्ण

/*
 * Set the initial winकरोw size, round to next घातer of 2 and square
 * क्रम small size, x 4 क्रम medium, and x 2 क्रम large
 * क्रम 128k (32 page) max ra
 * 1-8 page = 32k initial, > 8 page = 128k initial
 */
अटल अचिन्हित दीर्घ get_init_ra_size(अचिन्हित दीर्घ size, अचिन्हित दीर्घ max)
अणु
	अचिन्हित दीर्घ newsize = roundup_घात_of_two(size);

	अगर (newsize <= max / 32)
		newsize = newsize * 4;
	अन्यथा अगर (newsize <= max / 4)
		newsize = newsize * 2;
	अन्यथा
		newsize = max;

	वापस newsize;
पूर्ण

/*
 *  Get the previous winकरोw size, ramp it up, and
 *  वापस it as the new winकरोw size.
 */
अटल अचिन्हित दीर्घ get_next_ra_size(काष्ठा file_ra_state *ra,
				      अचिन्हित दीर्घ max)
अणु
	अचिन्हित दीर्घ cur = ra->size;

	अगर (cur < max / 16)
		वापस 4 * cur;
	अगर (cur <= max / 2)
		वापस 2 * cur;
	वापस max;
पूर्ण

/*
 * On-demand पढ़ोahead design.
 *
 * The fields in काष्ठा file_ra_state represent the most-recently-executed
 * पढ़ोahead attempt:
 *
 *                        |<----- async_size ---------|
 *     |------------------- size -------------------->|
 *     |==================#===========================|
 *     ^start             ^page marked with PG_पढ़ोahead
 *
 * To overlap application thinking समय and disk I/O समय, we करो
 * `पढ़ोahead pipelining': Do not रुको until the application consumed all
 * पढ़ोahead pages and stalled on the missing page at पढ़ोahead_index;
 * Instead, submit an asynchronous पढ़ोahead I/O as soon as there are
 * only async_size pages left in the पढ़ोahead winकरोw. Normally async_size
 * will be equal to size, क्रम maximum pipelining.
 *
 * In पूर्णांकerleaved sequential पढ़ोs, concurrent streams on the same fd can
 * be invalidating each other's पढ़ोahead state. So we flag the new पढ़ोahead
 * page at (start+size-async_size) with PG_पढ़ोahead, and use it as पढ़ोahead
 * indicator. The flag won't be set on alपढ़ोy cached pages, to aव्योम the
 * पढ़ोahead-क्रम-nothing fuss, saving poपूर्णांकless page cache lookups.
 *
 * prev_pos tracks the last visited byte in the _previous_ पढ़ो request.
 * It should be मुख्यtained by the caller, and will be used क्रम detecting
 * small अक्रमom पढ़ोs. Note that the पढ़ोahead algorithm checks loosely
 * क्रम sequential patterns. Hence पूर्णांकerleaved पढ़ोs might be served as
 * sequential ones.
 *
 * There is a special-हाल: अगर the first page which the application tries to
 * पढ़ो happens to be the first page of the file, it is assumed that a linear
 * पढ़ो is about to happen and the winकरोw is immediately set to the initial size
 * based on I/O request size and the max_पढ़ोahead.
 *
 * The code ramps up the पढ़ोahead size aggressively at first, but slow करोwn as
 * it approaches max_पढ़ोhead.
 */

/*
 * Count contiguously cached pages from @index-1 to @index-@max,
 * this count is a conservative estimation of
 * 	- length of the sequential पढ़ो sequence, or
 * 	- thrashing threshold in memory tight प्रणालीs
 */
अटल pgoff_t count_history_pages(काष्ठा address_space *mapping,
				   pgoff_t index, अचिन्हित दीर्घ max)
अणु
	pgoff_t head;

	rcu_पढ़ो_lock();
	head = page_cache_prev_miss(mapping, index - 1, max);
	rcu_पढ़ो_unlock();

	वापस index - 1 - head;
पूर्ण

/*
 * page cache context based पढ़ो-ahead
 */
अटल पूर्णांक try_context_पढ़ोahead(काष्ठा address_space *mapping,
				 काष्ठा file_ra_state *ra,
				 pgoff_t index,
				 अचिन्हित दीर्घ req_size,
				 अचिन्हित दीर्घ max)
अणु
	pgoff_t size;

	size = count_history_pages(mapping, index, max);

	/*
	 * not enough history pages:
	 * it could be a अक्रमom पढ़ो
	 */
	अगर (size <= req_size)
		वापस 0;

	/*
	 * starts from beginning of file:
	 * it is a strong indication of दीर्घ-run stream (or whole-file-पढ़ो)
	 */
	अगर (size >= index)
		size *= 2;

	ra->start = index;
	ra->size = min(size + req_size, max);
	ra->async_size = 1;

	वापस 1;
पूर्ण

/*
 * A minimal पढ़ोahead algorithm क्रम trivial sequential/अक्रमom पढ़ोs.
 */
अटल व्योम ondemand_पढ़ोahead(काष्ठा पढ़ोahead_control *ractl,
		bool hit_पढ़ोahead_marker, अचिन्हित दीर्घ req_size)
अणु
	काष्ठा backing_dev_info *bdi = inode_to_bdi(ractl->mapping->host);
	काष्ठा file_ra_state *ra = ractl->ra;
	अचिन्हित दीर्घ max_pages = ra->ra_pages;
	अचिन्हित दीर्घ add_pages;
	अचिन्हित दीर्घ index = पढ़ोahead_index(ractl);
	pgoff_t prev_index;

	/*
	 * If the request exceeds the पढ़ोahead winकरोw, allow the पढ़ो to
	 * be up to the optimal hardware IO size
	 */
	अगर (req_size > max_pages && bdi->io_pages > max_pages)
		max_pages = min(req_size, bdi->io_pages);

	/*
	 * start of file
	 */
	अगर (!index)
		जाओ initial_पढ़ोahead;

	/*
	 * It's the expected callback index, assume sequential access.
	 * Ramp up sizes, and push क्रमward the पढ़ोahead winकरोw.
	 */
	अगर ((index == (ra->start + ra->size - ra->async_size) ||
	     index == (ra->start + ra->size))) अणु
		ra->start += ra->size;
		ra->size = get_next_ra_size(ra, max_pages);
		ra->async_size = ra->size;
		जाओ पढ़ोit;
	पूर्ण

	/*
	 * Hit a marked page without valid पढ़ोahead state.
	 * E.g. पूर्णांकerleaved पढ़ोs.
	 * Query the pagecache क्रम async_size, which normally equals to
	 * पढ़ोahead size. Ramp it up and use it as the new पढ़ोahead size.
	 */
	अगर (hit_पढ़ोahead_marker) अणु
		pgoff_t start;

		rcu_पढ़ो_lock();
		start = page_cache_next_miss(ractl->mapping, index + 1,
				max_pages);
		rcu_पढ़ो_unlock();

		अगर (!start || start - index > max_pages)
			वापस;

		ra->start = start;
		ra->size = start - index;	/* old async_size */
		ra->size += req_size;
		ra->size = get_next_ra_size(ra, max_pages);
		ra->async_size = ra->size;
		जाओ पढ़ोit;
	पूर्ण

	/*
	 * oversize पढ़ो
	 */
	अगर (req_size > max_pages)
		जाओ initial_पढ़ोahead;

	/*
	 * sequential cache miss
	 * trivial हाल: (index - prev_index) == 1
	 * unaligned पढ़ोs: (index - prev_index) == 0
	 */
	prev_index = (अचिन्हित दीर्घ दीर्घ)ra->prev_pos >> PAGE_SHIFT;
	अगर (index - prev_index <= 1UL)
		जाओ initial_पढ़ोahead;

	/*
	 * Query the page cache and look क्रम the traces(cached history pages)
	 * that a sequential stream would leave behind.
	 */
	अगर (try_context_पढ़ोahead(ractl->mapping, ra, index, req_size,
			max_pages))
		जाओ पढ़ोit;

	/*
	 * standalone, small अक्रमom पढ़ो
	 * Read as is, and करो not pollute the पढ़ोahead state.
	 */
	करो_page_cache_ra(ractl, req_size, 0);
	वापस;

initial_पढ़ोahead:
	ra->start = index;
	ra->size = get_init_ra_size(req_size, max_pages);
	ra->async_size = ra->size > req_size ? ra->size - req_size : ra->size;

पढ़ोit:
	/*
	 * Will this पढ़ो hit the पढ़ोahead marker made by itself?
	 * If so, trigger the पढ़ोahead marker hit now, and merge
	 * the resulted next पढ़ोahead winकरोw पूर्णांकo the current one.
	 * Take care of maximum IO pages as above.
	 */
	अगर (index == ra->start && ra->size == ra->async_size) अणु
		add_pages = get_next_ra_size(ra, max_pages);
		अगर (ra->size + add_pages <= max_pages) अणु
			ra->async_size = add_pages;
			ra->size += add_pages;
		पूर्ण अन्यथा अणु
			ra->size = max_pages;
			ra->async_size = max_pages >> 1;
		पूर्ण
	पूर्ण

	ractl->_index = ra->start;
	करो_page_cache_ra(ractl, ra->size, ra->async_size);
पूर्ण

व्योम page_cache_sync_ra(काष्ठा पढ़ोahead_control *ractl,
		अचिन्हित दीर्घ req_count)
अणु
	bool करो_क्रमced_ra = ractl->file && (ractl->file->f_mode & FMODE_RANDOM);

	/*
	 * Even अगर पढ़ो-ahead is disabled, issue this request as पढ़ो-ahead
	 * as we'll need it to satisfy the requested range. The क्रमced
	 * पढ़ो-ahead will करो the right thing and limit the पढ़ो to just the
	 * requested range, which we'll set to 1 page क्रम this हाल.
	 */
	अगर (!ractl->ra->ra_pages || blk_cgroup_congested()) अणु
		अगर (!ractl->file)
			वापस;
		req_count = 1;
		करो_क्रमced_ra = true;
	पूर्ण

	/* be dumb */
	अगर (करो_क्रमced_ra) अणु
		क्रमce_page_cache_ra(ractl, req_count);
		वापस;
	पूर्ण

	/* करो पढ़ो-ahead */
	ondemand_पढ़ोahead(ractl, false, req_count);
पूर्ण
EXPORT_SYMBOL_GPL(page_cache_sync_ra);

व्योम page_cache_async_ra(काष्ठा पढ़ोahead_control *ractl,
		काष्ठा page *page, अचिन्हित दीर्घ req_count)
अणु
	/* no पढ़ो-ahead */
	अगर (!ractl->ra->ra_pages)
		वापस;

	/*
	 * Same bit is used क्रम PG_पढ़ोahead and PG_reclaim.
	 */
	अगर (PageWriteback(page))
		वापस;

	ClearPageReadahead(page);

	/*
	 * Defer asynchronous पढ़ो-ahead on IO congestion.
	 */
	अगर (inode_पढ़ो_congested(ractl->mapping->host))
		वापस;

	अगर (blk_cgroup_congested())
		वापस;

	/* करो पढ़ो-ahead */
	ondemand_पढ़ोahead(ractl, true, req_count);
पूर्ण
EXPORT_SYMBOL_GPL(page_cache_async_ra);

sमाप_प्रकार ksys_पढ़ोahead(पूर्णांक fd, loff_t offset, माप_प्रकार count)
अणु
	sमाप_प्रकार ret;
	काष्ठा fd f;

	ret = -EBADF;
	f = fdget(fd);
	अगर (!f.file || !(f.file->f_mode & FMODE_READ))
		जाओ out;

	/*
	 * The पढ़ोahead() syscall is पूर्णांकended to run only on files
	 * that can execute पढ़ोahead. If पढ़ोahead is not possible
	 * on this file, then we must वापस -EINVAL.
	 */
	ret = -EINVAL;
	अगर (!f.file->f_mapping || !f.file->f_mapping->a_ops ||
	    !S_ISREG(file_inode(f.file)->i_mode))
		जाओ out;

	ret = vfs_fadvise(f.file, offset, count, POSIX_FADV_WILLNEED);
out:
	fdput(f);
	वापस ret;
पूर्ण

SYSCALL_DEFINE3(पढ़ोahead, पूर्णांक, fd, loff_t, offset, माप_प्रकार, count)
अणु
	वापस ksys_पढ़ोahead(fd, offset, count);
पूर्ण

/**
 * पढ़ोahead_expand - Expand a पढ़ोahead request
 * @ractl: The request to be expanded
 * @new_start: The revised start
 * @new_len: The revised size of the request
 *
 * Attempt to expand a पढ़ोahead request outwards from the current size to the
 * specअगरied size by inserting locked pages beक्रमe and after the current winकरोw
 * to increase the size to the new winकरोw.  This may involve the insertion of
 * THPs, in which हाल the winकरोw may get expanded even beyond what was
 * requested.
 *
 * The algorithm will stop अगर it encounters a conflicting page alपढ़ोy in the
 * pagecache and leave a smaller expansion than requested.
 *
 * The caller must check क्रम this by examining the revised @ractl object क्रम a
 * dअगरferent expansion than was requested.
 */
व्योम पढ़ोahead_expand(काष्ठा पढ़ोahead_control *ractl,
		      loff_t new_start, माप_प्रकार new_len)
अणु
	काष्ठा address_space *mapping = ractl->mapping;
	काष्ठा file_ra_state *ra = ractl->ra;
	pgoff_t new_index, new_nr_pages;
	gfp_t gfp_mask = पढ़ोahead_gfp_mask(mapping);

	new_index = new_start / PAGE_SIZE;

	/* Expand the leading edge करोwnwards */
	जबतक (ractl->_index > new_index) अणु
		अचिन्हित दीर्घ index = ractl->_index - 1;
		काष्ठा page *page = xa_load(&mapping->i_pages, index);

		अगर (page && !xa_is_value(page))
			वापस; /* Page apparently present */

		page = __page_cache_alloc(gfp_mask);
		अगर (!page)
			वापस;
		अगर (add_to_page_cache_lru(page, mapping, index, gfp_mask) < 0) अणु
			put_page(page);
			वापस;
		पूर्ण

		ractl->_nr_pages++;
		ractl->_index = page->index;
	पूर्ण

	new_len += new_start - पढ़ोahead_pos(ractl);
	new_nr_pages = DIV_ROUND_UP(new_len, PAGE_SIZE);

	/* Expand the trailing edge upwards */
	जबतक (ractl->_nr_pages < new_nr_pages) अणु
		अचिन्हित दीर्घ index = ractl->_index + ractl->_nr_pages;
		काष्ठा page *page = xa_load(&mapping->i_pages, index);

		अगर (page && !xa_is_value(page))
			वापस; /* Page apparently present */

		page = __page_cache_alloc(gfp_mask);
		अगर (!page)
			वापस;
		अगर (add_to_page_cache_lru(page, mapping, index, gfp_mask) < 0) अणु
			put_page(page);
			वापस;
		पूर्ण
		ractl->_nr_pages++;
		अगर (ra) अणु
			ra->size++;
			ra->async_size++;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(पढ़ोahead_expand);
