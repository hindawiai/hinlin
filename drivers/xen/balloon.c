<शैली गुरु>
/******************************************************************************
 * Xen balloon driver - enables वापसing/claiming memory to/from Xen.
 *
 * Copyright (c) 2003, B Dragovic
 * Copyright (c) 2003-2004, M Williamson, K Fraser
 * Copyright (c) 2005 Dan M. Smith, IBM Corporation
 * Copyright (c) 2010 Daniel Kiper
 *
 * Memory hotplug support was written by Daniel Kiper. Work on
 * it was sponsored by Google under Google Summer of Code 2010
 * program. Jeremy Fitzhardinge from Citrix was the mentor क्रम
 * this project.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#घोषणा pr_fmt(fmt) "xen:" KBUILD_MODNAME ": " fmt

#समावेश <linux/cpu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/gfp.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/memory.h>
#समावेश <linux/memory_hotplug.h>
#समावेश <linux/percpu-defs.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysctl.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/tlb.h>

#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/xen/hypercall.h>

#समावेश <xen/xen.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/memory.h>
#समावेश <xen/balloon.h>
#समावेश <xen/features.h>
#समावेश <xen/page.h>
#समावेश <xen/mem-reservation.h>

अटल पूर्णांक xen_hotplug_unpopulated;

#अगर_घोषित CONFIG_XEN_BALLOON_MEMORY_HOTPLUG

अटल काष्ठा ctl_table balloon_table[] = अणु
	अणु
		.procname	= "hotplug_unpopulated",
		.data		= &xen_hotplug_unpopulated,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1         = SYSCTL_ZERO,
		.extra2         = SYSCTL_ONE,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table balloon_root[] = अणु
	अणु
		.procname	= "balloon",
		.mode		= 0555,
		.child		= balloon_table,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table xen_root[] = अणु
	अणु
		.procname	= "xen",
		.mode		= 0555,
		.child		= balloon_root,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

#पूर्ण_अगर

/*
 * Use one extent per PAGE_SIZE to aव्योम to अवरोध करोwn the page पूर्णांकo
 * multiple frame.
 */
#घोषणा EXTENT_ORDER (fls(XEN_PFN_PER_PAGE) - 1)

/*
 * balloon_process() state:
 *
 * BP_DONE: करोne or nothing to करो,
 * BP_WAIT: रुको to be rescheduled,
 * BP_EAGAIN: error, go to sleep,
 * BP_ECANCELED: error, balloon operation canceled.
 */

क्रमागत bp_state अणु
	BP_DONE,
	BP_WAIT,
	BP_EAGAIN,
	BP_ECANCELED
पूर्ण;


अटल DEFINE_MUTEX(balloon_mutex);

काष्ठा balloon_stats balloon_stats;
EXPORT_SYMBOL_GPL(balloon_stats);

/* We increase/decrease in batches which fit in a page */
अटल xen_pfn_t frame_list[PAGE_SIZE / माप(xen_pfn_t)];


/* List of ballooned pages, thपढ़ोed through the mem_map array. */
अटल LIST_HEAD(ballooned_pages);
अटल DECLARE_WAIT_QUEUE_HEAD(balloon_wq);

/* Main work function, always executed in process context. */
अटल व्योम balloon_process(काष्ठा work_काष्ठा *work);
अटल DECLARE_DELAYED_WORK(balloon_worker, balloon_process);

/* When ballooning out (allocating memory to वापस to Xen) we करोn't really
   want the kernel to try too hard since that can trigger the oom समाप्तer. */
#घोषणा GFP_BALLOON \
	(GFP_HIGHUSER | __GFP_NOWARN | __GFP_NORETRY | __GFP_NOMEMALLOC)

/* balloon_append: add the given page to the balloon. */
अटल व्योम balloon_append(काष्ठा page *page)
अणु
	__SetPageOffline(page);

	/* Lowmem is re-populated first, so highmem pages go at list tail. */
	अगर (PageHighMem(page)) अणु
		list_add_tail(&page->lru, &ballooned_pages);
		balloon_stats.balloon_high++;
	पूर्ण अन्यथा अणु
		list_add(&page->lru, &ballooned_pages);
		balloon_stats.balloon_low++;
	पूर्ण
	wake_up(&balloon_wq);
पूर्ण

/* balloon_retrieve: rescue a page from the balloon, अगर it is not empty. */
अटल काष्ठा page *balloon_retrieve(bool require_lowmem)
अणु
	काष्ठा page *page;

	अगर (list_empty(&ballooned_pages))
		वापस शून्य;

	page = list_entry(ballooned_pages.next, काष्ठा page, lru);
	अगर (require_lowmem && PageHighMem(page))
		वापस शून्य;
	list_del(&page->lru);

	अगर (PageHighMem(page))
		balloon_stats.balloon_high--;
	अन्यथा
		balloon_stats.balloon_low--;

	__ClearPageOffline(page);
	वापस page;
पूर्ण

अटल काष्ठा page *balloon_next_page(काष्ठा page *page)
अणु
	काष्ठा list_head *next = page->lru.next;
	अगर (next == &ballooned_pages)
		वापस शून्य;
	वापस list_entry(next, काष्ठा page, lru);
पूर्ण

अटल क्रमागत bp_state update_schedule(क्रमागत bp_state state)
अणु
	अगर (state == BP_WAIT)
		वापस BP_WAIT;

	अगर (state == BP_ECANCELED)
		वापस BP_ECANCELED;

	अगर (state == BP_DONE) अणु
		balloon_stats.schedule_delay = 1;
		balloon_stats.retry_count = 1;
		वापस BP_DONE;
	पूर्ण

	++balloon_stats.retry_count;

	अगर (balloon_stats.max_retry_count != RETRY_UNLIMITED &&
			balloon_stats.retry_count > balloon_stats.max_retry_count) अणु
		balloon_stats.schedule_delay = 1;
		balloon_stats.retry_count = 1;
		वापस BP_ECANCELED;
	पूर्ण

	balloon_stats.schedule_delay <<= 1;

	अगर (balloon_stats.schedule_delay > balloon_stats.max_schedule_delay)
		balloon_stats.schedule_delay = balloon_stats.max_schedule_delay;

	वापस BP_EAGAIN;
पूर्ण

#अगर_घोषित CONFIG_XEN_BALLOON_MEMORY_HOTPLUG
अटल व्योम release_memory_resource(काष्ठा resource *resource)
अणु
	अगर (!resource)
		वापस;

	/*
	 * No need to reset region to identity mapped since we now
	 * know that no I/O can be in this region
	 */
	release_resource(resource);
	kमुक्त(resource);
पूर्ण

अटल काष्ठा resource *additional_memory_resource(phys_addr_t size)
अणु
	काष्ठा resource *res;
	पूर्णांक ret;

	res = kzalloc(माप(*res), GFP_KERNEL);
	अगर (!res)
		वापस शून्य;

	res->name = "System RAM";
	res->flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;

	ret = allocate_resource(&iomem_resource, res,
				size, 0, -1,
				PAGES_PER_SECTION * PAGE_SIZE, शून्य, शून्य);
	अगर (ret < 0) अणु
		pr_err("Cannot allocate new System RAM resource\n");
		kमुक्त(res);
		वापस शून्य;
	पूर्ण

	वापस res;
पूर्ण

अटल क्रमागत bp_state reserve_additional_memory(व्योम)
अणु
	दीर्घ credit;
	काष्ठा resource *resource;
	पूर्णांक nid, rc;
	अचिन्हित दीर्घ balloon_hotplug;

	credit = balloon_stats.target_pages + balloon_stats.target_unpopulated
		- balloon_stats.total_pages;

	/*
	 * Alपढ़ोy hotplugged enough pages?  Wait क्रम them to be
	 * onlined.
	 */
	अगर (credit <= 0)
		वापस BP_WAIT;

	balloon_hotplug = round_up(credit, PAGES_PER_SECTION);

	resource = additional_memory_resource(balloon_hotplug * PAGE_SIZE);
	अगर (!resource)
		जाओ err;

	nid = memory_add_physaddr_to_nid(resource->start);

#अगर_घोषित CONFIG_XEN_HAVE_PVMMU
	/*
	 * We करोn't support PV MMU when Linux and Xen is using
	 * dअगरferent page granularity.
	 */
	BUILD_BUG_ON(XEN_PAGE_SIZE != PAGE_SIZE);

        /*
         * add_memory() will build page tables क्रम the new memory so
         * the p2m must contain invalid entries so the correct
         * non-present PTEs will be written.
         *
         * If a failure occurs, the original (identity) p2m entries
         * are not restored since this region is now known not to
         * conflict with any devices.
         */ 
	अगर (!xen_feature(XENFEAT_स्वतः_translated_physmap)) अणु
		अचिन्हित दीर्घ pfn, i;

		pfn = PFN_DOWN(resource->start);
		क्रम (i = 0; i < balloon_hotplug; i++) अणु
			अगर (!set_phys_to_machine(pfn + i, INVALID_P2M_ENTRY)) अणु
				pr_warn("set_phys_to_machine() failed, no memory added\n");
				जाओ err;
			पूर्ण
                पूर्ण
	पूर्ण
#पूर्ण_अगर

	/*
	 * add_memory_resource() will call online_pages() which in its turn
	 * will call xen_online_page() callback causing deadlock अगर we करोn't
	 * release balloon_mutex here. Unlocking here is safe because the
	 * callers drop the mutex beक्रमe trying again.
	 */
	mutex_unlock(&balloon_mutex);
	/* add_memory_resource() requires the device_hotplug lock */
	lock_device_hotplug();
	rc = add_memory_resource(nid, resource, MHP_MERGE_RESOURCE);
	unlock_device_hotplug();
	mutex_lock(&balloon_mutex);

	अगर (rc) अणु
		pr_warn("Cannot add additional memory (%i)\n", rc);
		जाओ err;
	पूर्ण

	balloon_stats.total_pages += balloon_hotplug;

	वापस BP_WAIT;
  err:
	release_memory_resource(resource);
	वापस BP_ECANCELED;
पूर्ण

अटल व्योम xen_online_page(काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
	अचिन्हित दीर्घ i, size = (1 << order);
	अचिन्हित दीर्घ start_pfn = page_to_pfn(page);
	काष्ठा page *p;

	pr_debug("Online %lu pages starting at pfn 0x%lx\n", size, start_pfn);
	mutex_lock(&balloon_mutex);
	क्रम (i = 0; i < size; i++) अणु
		p = pfn_to_page(start_pfn + i);
		balloon_append(p);
	पूर्ण
	mutex_unlock(&balloon_mutex);
पूर्ण

अटल पूर्णांक xen_memory_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val, व्योम *v)
अणु
	अगर (val == MEM_ONLINE)
		schedule_delayed_work(&balloon_worker, 0);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block xen_memory_nb = अणु
	.notअगरier_call = xen_memory_notअगरier,
	.priority = 0
पूर्ण;
#अन्यथा
अटल क्रमागत bp_state reserve_additional_memory(व्योम)
अणु
	balloon_stats.target_pages = balloon_stats.current_pages +
				     balloon_stats.target_unpopulated;
	वापस BP_ECANCELED;
पूर्ण
#पूर्ण_अगर /* CONFIG_XEN_BALLOON_MEMORY_HOTPLUG */

अटल दीर्घ current_credit(व्योम)
अणु
	वापस balloon_stats.target_pages - balloon_stats.current_pages;
पूर्ण

अटल bool balloon_is_inflated(व्योम)
अणु
	वापस balloon_stats.balloon_low || balloon_stats.balloon_high;
पूर्ण

अटल क्रमागत bp_state increase_reservation(अचिन्हित दीर्घ nr_pages)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ i;
	काष्ठा page   *page;

	अगर (nr_pages > ARRAY_SIZE(frame_list))
		nr_pages = ARRAY_SIZE(frame_list);

	page = list_first_entry_or_null(&ballooned_pages, काष्ठा page, lru);
	क्रम (i = 0; i < nr_pages; i++) अणु
		अगर (!page) अणु
			nr_pages = i;
			अवरोध;
		पूर्ण

		frame_list[i] = page_to_xen_pfn(page);
		page = balloon_next_page(page);
	पूर्ण

	rc = xenmem_reservation_increase(nr_pages, frame_list);
	अगर (rc <= 0)
		वापस BP_EAGAIN;

	क्रम (i = 0; i < rc; i++) अणु
		page = balloon_retrieve(false);
		BUG_ON(page == शून्य);

		xenmem_reservation_va_mapping_update(1, &page, &frame_list[i]);

		/* Relinquish the page back to the allocator. */
		मुक्त_reserved_page(page);
	पूर्ण

	balloon_stats.current_pages += rc;

	वापस BP_DONE;
पूर्ण

अटल क्रमागत bp_state decrease_reservation(अचिन्हित दीर्घ nr_pages, gfp_t gfp)
अणु
	क्रमागत bp_state state = BP_DONE;
	अचिन्हित दीर्घ i;
	काष्ठा page *page, *पंचांगp;
	पूर्णांक ret;
	LIST_HEAD(pages);

	अगर (nr_pages > ARRAY_SIZE(frame_list))
		nr_pages = ARRAY_SIZE(frame_list);

	क्रम (i = 0; i < nr_pages; i++) अणु
		page = alloc_page(gfp);
		अगर (page == शून्य) अणु
			nr_pages = i;
			state = BP_EAGAIN;
			अवरोध;
		पूर्ण
		adjust_managed_page_count(page, -1);
		xenmem_reservation_scrub_page(page);
		list_add(&page->lru, &pages);
	पूर्ण

	/*
	 * Ensure that ballooned highmem pages करोn't have kmaps.
	 *
	 * Do this beक्रमe changing the p2m as kmap_flush_unused()
	 * पढ़ोs PTEs to obtain pages (and hence needs the original
	 * p2m entry).
	 */
	kmap_flush_unused();

	/*
	 * Setup the frame, update direct mapping, invalidate P2M,
	 * and add to balloon.
	 */
	i = 0;
	list_क्रम_each_entry_safe(page, पंचांगp, &pages, lru) अणु
		frame_list[i++] = xen_page_to_gfn(page);

		xenmem_reservation_va_mapping_reset(1, &page);

		list_del(&page->lru);

		balloon_append(page);
	पूर्ण

	flush_tlb_all();

	ret = xenmem_reservation_decrease(nr_pages, frame_list);
	BUG_ON(ret != nr_pages);

	balloon_stats.current_pages -= nr_pages;

	वापस state;
पूर्ण

/*
 * As this is a work item it is guaranteed to run as a single instance only.
 * We may of course race updates of the target counts (which are रक्षित
 * by the balloon lock), or with changes to the Xen hard limit, but we will
 * recover from these in समय.
 */
अटल व्योम balloon_process(काष्ठा work_काष्ठा *work)
अणु
	क्रमागत bp_state state = BP_DONE;
	दीर्घ credit;


	करो अणु
		mutex_lock(&balloon_mutex);

		credit = current_credit();

		अगर (credit > 0) अणु
			अगर (balloon_is_inflated())
				state = increase_reservation(credit);
			अन्यथा
				state = reserve_additional_memory();
		पूर्ण

		अगर (credit < 0) अणु
			दीर्घ n_pages;

			n_pages = min(-credit, si_mem_available());
			state = decrease_reservation(n_pages, GFP_BALLOON);
			अगर (state == BP_DONE && n_pages != -credit &&
			    n_pages < totalreserve_pages)
				state = BP_EAGAIN;
		पूर्ण

		state = update_schedule(state);

		mutex_unlock(&balloon_mutex);

		cond_resched();

	पूर्ण जबतक (credit && state == BP_DONE);

	/* Schedule more work अगर there is some still to be करोne. */
	अगर (state == BP_EAGAIN)
		schedule_delayed_work(&balloon_worker, balloon_stats.schedule_delay * HZ);
पूर्ण

/* Resets the Xen limit, sets new target, and kicks off processing. */
व्योम balloon_set_new_target(अचिन्हित दीर्घ target)
अणु
	/* No need क्रम lock. Not पढ़ो-modअगरy-ग_लिखो updates. */
	balloon_stats.target_pages = target;
	schedule_delayed_work(&balloon_worker, 0);
पूर्ण
EXPORT_SYMBOL_GPL(balloon_set_new_target);

अटल पूर्णांक add_ballooned_pages(पूर्णांक nr_pages)
अणु
	क्रमागत bp_state st;

	अगर (xen_hotplug_unpopulated) अणु
		st = reserve_additional_memory();
		अगर (st != BP_ECANCELED) अणु
			पूर्णांक rc;

			mutex_unlock(&balloon_mutex);
			rc = रुको_event_पूर्णांकerruptible(balloon_wq,
				   !list_empty(&ballooned_pages));
			mutex_lock(&balloon_mutex);
			वापस rc ? -ENOMEM : 0;
		पूर्ण
	पूर्ण

	अगर (si_mem_available() < nr_pages)
		वापस -ENOMEM;

	st = decrease_reservation(nr_pages, GFP_USER);
	अगर (st != BP_DONE)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * alloc_xenballooned_pages - get pages that have been ballooned out
 * @nr_pages: Number of pages to get
 * @pages: pages वापसed
 * @वापस 0 on success, error otherwise
 */
पूर्णांक alloc_xenballooned_pages(पूर्णांक nr_pages, काष्ठा page **pages)
अणु
	पूर्णांक pgno = 0;
	काष्ठा page *page;
	पूर्णांक ret;

	mutex_lock(&balloon_mutex);

	balloon_stats.target_unpopulated += nr_pages;

	जबतक (pgno < nr_pages) अणु
		page = balloon_retrieve(true);
		अगर (page) अणु
			pages[pgno++] = page;
#अगर_घोषित CONFIG_XEN_HAVE_PVMMU
			/*
			 * We करोn't support PV MMU when Linux and Xen is using
			 * dअगरferent page granularity.
			 */
			BUILD_BUG_ON(XEN_PAGE_SIZE != PAGE_SIZE);

			अगर (!xen_feature(XENFEAT_स्वतः_translated_physmap)) अणु
				ret = xen_alloc_p2m_entry(page_to_pfn(page));
				अगर (ret < 0)
					जाओ out_unकरो;
			पूर्ण
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			ret = add_ballooned_pages(nr_pages - pgno);
			अगर (ret < 0)
				जाओ out_unकरो;
		पूर्ण
	पूर्ण
	mutex_unlock(&balloon_mutex);
	वापस 0;
 out_unकरो:
	mutex_unlock(&balloon_mutex);
	मुक्त_xenballooned_pages(pgno, pages);
	/*
	 * NB: मुक्त_xenballooned_pages will only subtract pgno pages, but since
	 * target_unpopulated is incremented with nr_pages at the start we need
	 * to हटाओ the reमुख्यing ones also, or accounting will be screwed.
	 */
	balloon_stats.target_unpopulated -= nr_pages - pgno;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(alloc_xenballooned_pages);

/**
 * मुक्त_xenballooned_pages - वापस pages retrieved with get_ballooned_pages
 * @nr_pages: Number of pages
 * @pages: pages to वापस
 */
व्योम मुक्त_xenballooned_pages(पूर्णांक nr_pages, काष्ठा page **pages)
अणु
	पूर्णांक i;

	mutex_lock(&balloon_mutex);

	क्रम (i = 0; i < nr_pages; i++) अणु
		अगर (pages[i])
			balloon_append(pages[i]);
	पूर्ण

	balloon_stats.target_unpopulated -= nr_pages;

	/* The balloon may be too large now. Shrink it अगर needed. */
	अगर (current_credit())
		schedule_delayed_work(&balloon_worker, 0);

	mutex_unlock(&balloon_mutex);
पूर्ण
EXPORT_SYMBOL(मुक्त_xenballooned_pages);

#अगर defined(CONFIG_XEN_PV) && !defined(CONFIG_XEN_UNPOPULATED_ALLOC)
अटल व्योम __init balloon_add_region(अचिन्हित दीर्घ start_pfn,
				      अचिन्हित दीर्घ pages)
अणु
	अचिन्हित दीर्घ pfn, extra_pfn_end;

	/*
	 * If the amount of usable memory has been limited (e.g., with
	 * the 'mem' command line parameter), don't add pages beyond
	 * this limit.
	 */
	extra_pfn_end = min(max_pfn, start_pfn + pages);

	क्रम (pfn = start_pfn; pfn < extra_pfn_end; pfn++) अणु
		/* totalram_pages and totalhigh_pages करो not
		   include the boot-समय balloon extension, so
		   करोn't subtract from it. */
		balloon_append(pfn_to_page(pfn));
	पूर्ण

	balloon_stats.total_pages += extra_pfn_end - start_pfn;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init balloon_init(व्योम)
अणु
	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	pr_info("Initialising balloon driver\n");

#अगर_घोषित CONFIG_XEN_PV
	balloon_stats.current_pages = xen_pv_करोमुख्य()
		? min(xen_start_info->nr_pages - xen_released_pages, max_pfn)
		: get_num_physpages();
#अन्यथा
	balloon_stats.current_pages = get_num_physpages();
#पूर्ण_अगर
	balloon_stats.target_pages  = balloon_stats.current_pages;
	balloon_stats.balloon_low   = 0;
	balloon_stats.balloon_high  = 0;
	balloon_stats.total_pages   = balloon_stats.current_pages;

	balloon_stats.schedule_delay = 1;
	balloon_stats.max_schedule_delay = 32;
	balloon_stats.retry_count = 1;
	balloon_stats.max_retry_count = 4;

#अगर_घोषित CONFIG_XEN_BALLOON_MEMORY_HOTPLUG
	set_online_page_callback(&xen_online_page);
	रेजिस्टर_memory_notअगरier(&xen_memory_nb);
	रेजिस्टर_sysctl_table(xen_root);
#पूर्ण_अगर

#अगर defined(CONFIG_XEN_PV) && !defined(CONFIG_XEN_UNPOPULATED_ALLOC)
	अणु
		पूर्णांक i;

		/*
		 * Initialize the balloon with pages from the extra memory
		 * regions (see arch/x86/xen/setup.c).
		 */
		क्रम (i = 0; i < XEN_EXTRA_MEM_MAX_REGIONS; i++)
			अगर (xen_extra_mem[i].n_pfns)
				balloon_add_region(xen_extra_mem[i].start_pfn,
						   xen_extra_mem[i].n_pfns);
	पूर्ण
#पूर्ण_अगर

	/* Init the xen-balloon driver. */
	xen_balloon_init();

	वापस 0;
पूर्ण
subsys_initcall(balloon_init);
