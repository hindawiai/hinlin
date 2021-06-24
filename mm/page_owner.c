<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/debugfs.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/memblock.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/page_owner.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/migrate.h>
#समावेश <linux/stackdepot.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sched/घड़ी.h>

#समावेश "internal.h"

/*
 * TODO: teach PAGE_OWNER_STACK_DEPTH (__dump_page_owner and save_stack)
 * to use off stack temporal storage
 */
#घोषणा PAGE_OWNER_STACK_DEPTH (16)

काष्ठा page_owner अणु
	अचिन्हित लघु order;
	लघु last_migrate_reason;
	gfp_t gfp_mask;
	depot_stack_handle_t handle;
	depot_stack_handle_t मुक्त_handle;
	u64 ts_nsec;
	u64 मुक्त_ts_nsec;
	pid_t pid;
पूर्ण;

अटल bool page_owner_enabled = false;
DEFINE_STATIC_KEY_FALSE(page_owner_inited);

अटल depot_stack_handle_t dummy_handle;
अटल depot_stack_handle_t failure_handle;
अटल depot_stack_handle_t early_handle;

अटल व्योम init_early_allocated_pages(व्योम);

अटल पूर्णांक __init early_page_owner_param(अक्षर *buf)
अणु
	वापस kstrtobool(buf, &page_owner_enabled);
पूर्ण
early_param("page_owner", early_page_owner_param);

अटल bool need_page_owner(व्योम)
अणु
	वापस page_owner_enabled;
पूर्ण

अटल __always_अंतरभूत depot_stack_handle_t create_dummy_stack(व्योम)
अणु
	अचिन्हित दीर्घ entries[4];
	अचिन्हित पूर्णांक nr_entries;

	nr_entries = stack_trace_save(entries, ARRAY_SIZE(entries), 0);
	वापस stack_depot_save(entries, nr_entries, GFP_KERNEL);
पूर्ण

अटल noअंतरभूत व्योम रेजिस्टर_dummy_stack(व्योम)
अणु
	dummy_handle = create_dummy_stack();
पूर्ण

अटल noअंतरभूत व्योम रेजिस्टर_failure_stack(व्योम)
अणु
	failure_handle = create_dummy_stack();
पूर्ण

अटल noअंतरभूत व्योम रेजिस्टर_early_stack(व्योम)
अणु
	early_handle = create_dummy_stack();
पूर्ण

अटल व्योम init_page_owner(व्योम)
अणु
	अगर (!page_owner_enabled)
		वापस;

	रेजिस्टर_dummy_stack();
	रेजिस्टर_failure_stack();
	रेजिस्टर_early_stack();
	अटल_branch_enable(&page_owner_inited);
	init_early_allocated_pages();
पूर्ण

काष्ठा page_ext_operations page_owner_ops = अणु
	.size = माप(काष्ठा page_owner),
	.need = need_page_owner,
	.init = init_page_owner,
पूर्ण;

अटल अंतरभूत काष्ठा page_owner *get_page_owner(काष्ठा page_ext *page_ext)
अणु
	वापस (व्योम *)page_ext + page_owner_ops.offset;
पूर्ण

अटल noअंतरभूत depot_stack_handle_t save_stack(gfp_t flags)
अणु
	अचिन्हित दीर्घ entries[PAGE_OWNER_STACK_DEPTH];
	depot_stack_handle_t handle;
	अचिन्हित पूर्णांक nr_entries;

	/*
	 * Aव्योम recursion.
	 *
	 * Someबार page metadata allocation tracking requires more
	 * memory to be allocated:
	 * - when new stack trace is saved to stack depot
	 * - when backtrace itself is calculated (ia64)
	 */
	अगर (current->in_page_owner)
		वापस dummy_handle;
	current->in_page_owner = 1;

	nr_entries = stack_trace_save(entries, ARRAY_SIZE(entries), 2);
	handle = stack_depot_save(entries, nr_entries, flags);
	अगर (!handle)
		handle = failure_handle;

	current->in_page_owner = 0;
	वापस handle;
पूर्ण

व्योम __reset_page_owner(काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
	पूर्णांक i;
	काष्ठा page_ext *page_ext;
	depot_stack_handle_t handle;
	काष्ठा page_owner *page_owner;
	u64 मुक्त_ts_nsec = local_घड़ी();

	page_ext = lookup_page_ext(page);
	अगर (unlikely(!page_ext))
		वापस;

	handle = save_stack(GFP_NOWAIT | __GFP_NOWARN);
	क्रम (i = 0; i < (1 << order); i++) अणु
		__clear_bit(PAGE_EXT_OWNER_ALLOCATED, &page_ext->flags);
		page_owner = get_page_owner(page_ext);
		page_owner->मुक्त_handle = handle;
		page_owner->मुक्त_ts_nsec = मुक्त_ts_nsec;
		page_ext = page_ext_next(page_ext);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __set_page_owner_handle(काष्ठा page_ext *page_ext,
					depot_stack_handle_t handle,
					अचिन्हित पूर्णांक order, gfp_t gfp_mask)
अणु
	काष्ठा page_owner *page_owner;
	पूर्णांक i;

	क्रम (i = 0; i < (1 << order); i++) अणु
		page_owner = get_page_owner(page_ext);
		page_owner->handle = handle;
		page_owner->order = order;
		page_owner->gfp_mask = gfp_mask;
		page_owner->last_migrate_reason = -1;
		page_owner->pid = current->pid;
		page_owner->ts_nsec = local_घड़ी();
		__set_bit(PAGE_EXT_OWNER, &page_ext->flags);
		__set_bit(PAGE_EXT_OWNER_ALLOCATED, &page_ext->flags);

		page_ext = page_ext_next(page_ext);
	पूर्ण
पूर्ण

noअंतरभूत व्योम __set_page_owner(काष्ठा page *page, अचिन्हित पूर्णांक order,
					gfp_t gfp_mask)
अणु
	काष्ठा page_ext *page_ext = lookup_page_ext(page);
	depot_stack_handle_t handle;

	अगर (unlikely(!page_ext))
		वापस;

	handle = save_stack(gfp_mask);
	__set_page_owner_handle(page_ext, handle, order, gfp_mask);
पूर्ण

व्योम __set_page_owner_migrate_reason(काष्ठा page *page, पूर्णांक reason)
अणु
	काष्ठा page_ext *page_ext = lookup_page_ext(page);
	काष्ठा page_owner *page_owner;

	अगर (unlikely(!page_ext))
		वापस;

	page_owner = get_page_owner(page_ext);
	page_owner->last_migrate_reason = reason;
पूर्ण

व्योम __split_page_owner(काष्ठा page *page, अचिन्हित पूर्णांक nr)
अणु
	पूर्णांक i;
	काष्ठा page_ext *page_ext = lookup_page_ext(page);
	काष्ठा page_owner *page_owner;

	अगर (unlikely(!page_ext))
		वापस;

	क्रम (i = 0; i < nr; i++) अणु
		page_owner = get_page_owner(page_ext);
		page_owner->order = 0;
		page_ext = page_ext_next(page_ext);
	पूर्ण
पूर्ण

व्योम __copy_page_owner(काष्ठा page *oldpage, काष्ठा page *newpage)
अणु
	काष्ठा page_ext *old_ext = lookup_page_ext(oldpage);
	काष्ठा page_ext *new_ext = lookup_page_ext(newpage);
	काष्ठा page_owner *old_page_owner, *new_page_owner;

	अगर (unlikely(!old_ext || !new_ext))
		वापस;

	old_page_owner = get_page_owner(old_ext);
	new_page_owner = get_page_owner(new_ext);
	new_page_owner->order = old_page_owner->order;
	new_page_owner->gfp_mask = old_page_owner->gfp_mask;
	new_page_owner->last_migrate_reason =
		old_page_owner->last_migrate_reason;
	new_page_owner->handle = old_page_owner->handle;
	new_page_owner->pid = old_page_owner->pid;
	new_page_owner->ts_nsec = old_page_owner->ts_nsec;
	new_page_owner->मुक्त_ts_nsec = old_page_owner->ts_nsec;

	/*
	 * We करोn't clear the bit on the oldpage as it's going to be मुक्तd
	 * after migration. Until then, the info can be useful in हाल of
	 * a bug, and the overall stats will be off a bit only temporarily.
	 * Also, migrate_misplaced_transhuge_page() can still fail the
	 * migration and then we want the oldpage to retain the info. But
	 * in that हाल we also करोn't need to explicitly clear the info from
	 * the new page, which will be मुक्तd.
	 */
	__set_bit(PAGE_EXT_OWNER, &new_ext->flags);
	__set_bit(PAGE_EXT_OWNER_ALLOCATED, &new_ext->flags);
पूर्ण

व्योम pagetypeinfo_showmixedcount_prपूर्णांक(काष्ठा seq_file *m,
				       pg_data_t *pgdat, काष्ठा zone *zone)
अणु
	काष्ठा page *page;
	काष्ठा page_ext *page_ext;
	काष्ठा page_owner *page_owner;
	अचिन्हित दीर्घ pfn, block_end_pfn;
	अचिन्हित दीर्घ end_pfn = zone_end_pfn(zone);
	अचिन्हित दीर्घ count[MIGRATE_TYPES] = अणु 0, पूर्ण;
	पूर्णांक pageblock_mt, page_mt;
	पूर्णांक i;

	/* Scan block by block. First and last block may be incomplete */
	pfn = zone->zone_start_pfn;

	/*
	 * Walk the zone in pageblock_nr_pages steps. If a page block spans
	 * a zone boundary, it will be द्विगुन counted between zones. This करोes
	 * not matter as the mixed block count will still be correct
	 */
	क्रम (; pfn < end_pfn; ) अणु
		page = pfn_to_online_page(pfn);
		अगर (!page) अणु
			pfn = ALIGN(pfn + 1, MAX_ORDER_NR_PAGES);
			जारी;
		पूर्ण

		block_end_pfn = ALIGN(pfn + 1, pageblock_nr_pages);
		block_end_pfn = min(block_end_pfn, end_pfn);

		pageblock_mt = get_pageblock_migratetype(page);

		क्रम (; pfn < block_end_pfn; pfn++) अणु
			अगर (!pfn_valid_within(pfn))
				जारी;

			/* The pageblock is online, no need to recheck. */
			page = pfn_to_page(pfn);

			अगर (page_zone(page) != zone)
				जारी;

			अगर (PageBuddy(page)) अणु
				अचिन्हित दीर्घ मुक्तpage_order;

				मुक्तpage_order = buddy_order_unsafe(page);
				अगर (मुक्तpage_order < MAX_ORDER)
					pfn += (1UL << मुक्तpage_order) - 1;
				जारी;
			पूर्ण

			अगर (PageReserved(page))
				जारी;

			page_ext = lookup_page_ext(page);
			अगर (unlikely(!page_ext))
				जारी;

			अगर (!test_bit(PAGE_EXT_OWNER_ALLOCATED, &page_ext->flags))
				जारी;

			page_owner = get_page_owner(page_ext);
			page_mt = gfp_migratetype(page_owner->gfp_mask);
			अगर (pageblock_mt != page_mt) अणु
				अगर (is_migrate_cma(pageblock_mt))
					count[MIGRATE_MOVABLE]++;
				अन्यथा
					count[pageblock_mt]++;

				pfn = block_end_pfn;
				अवरोध;
			पूर्ण
			pfn += (1UL << page_owner->order) - 1;
		पूर्ण
	पूर्ण

	/* Prपूर्णांक counts */
	seq_म_लिखो(m, "Node %d, zone %8s ", pgdat->node_id, zone->name);
	क्रम (i = 0; i < MIGRATE_TYPES; i++)
		seq_म_लिखो(m, "%12lu ", count[i]);
	seq_अ_दो(m, '\n');
पूर्ण

अटल sमाप_प्रकार
prपूर्णांक_page_owner(अक्षर __user *buf, माप_प्रकार count, अचिन्हित दीर्घ pfn,
		काष्ठा page *page, काष्ठा page_owner *page_owner,
		depot_stack_handle_t handle)
अणु
	पूर्णांक ret, pageblock_mt, page_mt;
	अचिन्हित दीर्घ *entries;
	अचिन्हित पूर्णांक nr_entries;
	अक्षर *kbuf;

	count = min_t(माप_प्रकार, count, PAGE_SIZE);
	kbuf = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!kbuf)
		वापस -ENOMEM;

	ret = snम_लिखो(kbuf, count,
			"Page allocated via order %u, mask %#x(%pGg), pid %d, ts %llu ns, free_ts %llu ns\n",
			page_owner->order, page_owner->gfp_mask,
			&page_owner->gfp_mask, page_owner->pid,
			page_owner->ts_nsec, page_owner->मुक्त_ts_nsec);

	अगर (ret >= count)
		जाओ err;

	/* Prपूर्णांक inक्रमmation relevant to grouping pages by mobility */
	pageblock_mt = get_pageblock_migratetype(page);
	page_mt  = gfp_migratetype(page_owner->gfp_mask);
	ret += snम_लिखो(kbuf + ret, count - ret,
			"PFN %lu type %s Block %lu type %s Flags %#lx(%pGp)\n",
			pfn,
			migratetype_names[page_mt],
			pfn >> pageblock_order,
			migratetype_names[pageblock_mt],
			page->flags, &page->flags);

	अगर (ret >= count)
		जाओ err;

	nr_entries = stack_depot_fetch(handle, &entries);
	ret += stack_trace_snprपूर्णांक(kbuf + ret, count - ret, entries, nr_entries, 0);
	अगर (ret >= count)
		जाओ err;

	अगर (page_owner->last_migrate_reason != -1) अणु
		ret += snम_लिखो(kbuf + ret, count - ret,
			"Page has been migrated, last migrate reason: %s\n",
			migrate_reason_names[page_owner->last_migrate_reason]);
		अगर (ret >= count)
			जाओ err;
	पूर्ण

	ret += snम_लिखो(kbuf + ret, count - ret, "\n");
	अगर (ret >= count)
		जाओ err;

	अगर (copy_to_user(buf, kbuf, ret))
		ret = -EFAULT;

	kमुक्त(kbuf);
	वापस ret;

err:
	kमुक्त(kbuf);
	वापस -ENOMEM;
पूर्ण

व्योम __dump_page_owner(काष्ठा page *page)
अणु
	काष्ठा page_ext *page_ext = lookup_page_ext(page);
	काष्ठा page_owner *page_owner;
	depot_stack_handle_t handle;
	अचिन्हित दीर्घ *entries;
	अचिन्हित पूर्णांक nr_entries;
	gfp_t gfp_mask;
	पूर्णांक mt;

	अगर (unlikely(!page_ext)) अणु
		pr_alert("There is not page extension available.\n");
		वापस;
	पूर्ण

	page_owner = get_page_owner(page_ext);
	gfp_mask = page_owner->gfp_mask;
	mt = gfp_migratetype(gfp_mask);

	अगर (!test_bit(PAGE_EXT_OWNER, &page_ext->flags)) अणु
		pr_alert("page_owner info is not present (never set?)\n");
		वापस;
	पूर्ण

	अगर (test_bit(PAGE_EXT_OWNER_ALLOCATED, &page_ext->flags))
		pr_alert("page_owner tracks the page as allocated\n");
	अन्यथा
		pr_alert("page_owner tracks the page as freed\n");

	pr_alert("page last allocated via order %u, migratetype %s, gfp_mask %#x(%pGg), pid %d, ts %llu, free_ts %llu\n",
		 page_owner->order, migratetype_names[mt], gfp_mask, &gfp_mask,
		 page_owner->pid, page_owner->ts_nsec, page_owner->मुक्त_ts_nsec);

	handle = READ_ONCE(page_owner->handle);
	अगर (!handle) अणु
		pr_alert("page_owner allocation stack trace missing\n");
	पूर्ण अन्यथा अणु
		nr_entries = stack_depot_fetch(handle, &entries);
		stack_trace_prपूर्णांक(entries, nr_entries, 0);
	पूर्ण

	handle = READ_ONCE(page_owner->मुक्त_handle);
	अगर (!handle) अणु
		pr_alert("page_owner free stack trace missing\n");
	पूर्ण अन्यथा अणु
		nr_entries = stack_depot_fetch(handle, &entries);
		pr_alert("page last free stack trace:\n");
		stack_trace_prपूर्णांक(entries, nr_entries, 0);
	पूर्ण

	अगर (page_owner->last_migrate_reason != -1)
		pr_alert("page has been migrated, last migrate reason: %s\n",
			migrate_reason_names[page_owner->last_migrate_reason]);
पूर्ण

अटल sमाप_प्रकार
पढ़ो_page_owner(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित दीर्घ pfn;
	काष्ठा page *page;
	काष्ठा page_ext *page_ext;
	काष्ठा page_owner *page_owner;
	depot_stack_handle_t handle;

	अगर (!अटल_branch_unlikely(&page_owner_inited))
		वापस -EINVAL;

	page = शून्य;
	pfn = min_low_pfn + *ppos;

	/* Find a valid PFN or the start of a MAX_ORDER_NR_PAGES area */
	जबतक (!pfn_valid(pfn) && (pfn & (MAX_ORDER_NR_PAGES - 1)) != 0)
		pfn++;

	drain_all_pages(शून्य);

	/* Find an allocated page */
	क्रम (; pfn < max_pfn; pfn++) अणु
		/*
		 * If the new page is in a new MAX_ORDER_NR_PAGES area,
		 * validate the area as existing, skip it अगर not
		 */
		अगर ((pfn & (MAX_ORDER_NR_PAGES - 1)) == 0 && !pfn_valid(pfn)) अणु
			pfn += MAX_ORDER_NR_PAGES - 1;
			जारी;
		पूर्ण

		/* Check क्रम holes within a MAX_ORDER area */
		अगर (!pfn_valid_within(pfn))
			जारी;

		page = pfn_to_page(pfn);
		अगर (PageBuddy(page)) अणु
			अचिन्हित दीर्घ मुक्तpage_order = buddy_order_unsafe(page);

			अगर (मुक्तpage_order < MAX_ORDER)
				pfn += (1UL << मुक्तpage_order) - 1;
			जारी;
		पूर्ण

		page_ext = lookup_page_ext(page);
		अगर (unlikely(!page_ext))
			जारी;

		/*
		 * Some pages could be missed by concurrent allocation or मुक्त,
		 * because we करोn't hold the zone lock.
		 */
		अगर (!test_bit(PAGE_EXT_OWNER, &page_ext->flags))
			जारी;

		/*
		 * Although we करो have the info about past allocation of मुक्त
		 * pages, it's not relevant क्रम current memory usage.
		 */
		अगर (!test_bit(PAGE_EXT_OWNER_ALLOCATED, &page_ext->flags))
			जारी;

		page_owner = get_page_owner(page_ext);

		/*
		 * Don't prपूर्णांक "tail" pages of high-order allocations as that
		 * would inflate the stats.
		 */
		अगर (!IS_ALIGNED(pfn, 1 << page_owner->order))
			जारी;

		/*
		 * Access to page_ext->handle isn't synchronous so we should
		 * be careful to access it.
		 */
		handle = READ_ONCE(page_owner->handle);
		अगर (!handle)
			जारी;

		/* Record the next PFN to पढ़ो in the file offset */
		*ppos = (pfn - min_low_pfn) + 1;

		वापस prपूर्णांक_page_owner(buf, count, pfn, page,
				page_owner, handle);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम init_pages_in_zone(pg_data_t *pgdat, काष्ठा zone *zone)
अणु
	अचिन्हित दीर्घ pfn = zone->zone_start_pfn;
	अचिन्हित दीर्घ end_pfn = zone_end_pfn(zone);
	अचिन्हित दीर्घ count = 0;

	/*
	 * Walk the zone in pageblock_nr_pages steps. If a page block spans
	 * a zone boundary, it will be द्विगुन counted between zones. This करोes
	 * not matter as the mixed block count will still be correct
	 */
	क्रम (; pfn < end_pfn; ) अणु
		अचिन्हित दीर्घ block_end_pfn;

		अगर (!pfn_valid(pfn)) अणु
			pfn = ALIGN(pfn + 1, MAX_ORDER_NR_PAGES);
			जारी;
		पूर्ण

		block_end_pfn = ALIGN(pfn + 1, pageblock_nr_pages);
		block_end_pfn = min(block_end_pfn, end_pfn);

		क्रम (; pfn < block_end_pfn; pfn++) अणु
			काष्ठा page *page;
			काष्ठा page_ext *page_ext;

			अगर (!pfn_valid_within(pfn))
				जारी;

			page = pfn_to_page(pfn);

			अगर (page_zone(page) != zone)
				जारी;

			/*
			 * To aव्योम having to grab zone->lock, be a little
			 * careful when पढ़ोing buddy page order. The only
			 * danger is that we skip too much and potentially miss
			 * some early allocated pages, which is better than
			 * heavy lock contention.
			 */
			अगर (PageBuddy(page)) अणु
				अचिन्हित दीर्घ order = buddy_order_unsafe(page);

				अगर (order > 0 && order < MAX_ORDER)
					pfn += (1UL << order) - 1;
				जारी;
			पूर्ण

			अगर (PageReserved(page))
				जारी;

			page_ext = lookup_page_ext(page);
			अगर (unlikely(!page_ext))
				जारी;

			/* Maybe overlapping zone */
			अगर (test_bit(PAGE_EXT_OWNER, &page_ext->flags))
				जारी;

			/* Found early allocated page */
			__set_page_owner_handle(page_ext, early_handle,
						0, 0);
			count++;
		पूर्ण
		cond_resched();
	पूर्ण

	pr_info("Node %d, zone %8s: page owner found early allocated %lu pages\n",
		pgdat->node_id, zone->name, count);
पूर्ण

अटल व्योम init_zones_in_node(pg_data_t *pgdat)
अणु
	काष्ठा zone *zone;
	काष्ठा zone *node_zones = pgdat->node_zones;

	क्रम (zone = node_zones; zone - node_zones < MAX_NR_ZONES; ++zone) अणु
		अगर (!populated_zone(zone))
			जारी;

		init_pages_in_zone(pgdat, zone);
	पूर्ण
पूर्ण

अटल व्योम init_early_allocated_pages(व्योम)
अणु
	pg_data_t *pgdat;

	क्रम_each_online_pgdat(pgdat)
		init_zones_in_node(pgdat);
पूर्ण

अटल स्थिर काष्ठा file_operations proc_page_owner_operations = अणु
	.पढ़ो		= पढ़ो_page_owner,
पूर्ण;

अटल पूर्णांक __init pageowner_init(व्योम)
अणु
	अगर (!अटल_branch_unlikely(&page_owner_inited)) अणु
		pr_info("page_owner is disabled\n");
		वापस 0;
	पूर्ण

	debugfs_create_file("page_owner", 0400, शून्य, शून्य,
			    &proc_page_owner_operations);

	वापस 0;
पूर्ण
late_initcall(pageowner_init)
