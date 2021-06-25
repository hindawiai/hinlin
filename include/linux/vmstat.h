<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_VMSTAT_H
#घोषणा _LINUX_VMSTAT_H

#समावेश <linux/types.h>
#समावेश <linux/percpu.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/vm_event_item.h>
#समावेश <linux/atomic.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/mmdebug.h>

बाह्य पूर्णांक sysctl_stat_पूर्णांकerval;

#अगर_घोषित CONFIG_NUMA
#घोषणा ENABLE_NUMA_STAT   1
#घोषणा DISABLE_NUMA_STAT   0
बाह्य पूर्णांक sysctl_vm_numa_stat;
DECLARE_STATIC_KEY_TRUE(vm_numa_stat_key);
पूर्णांक sysctl_vm_numa_stat_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *length, loff_t *ppos);
#पूर्ण_अगर

काष्ठा reclaim_stat अणु
	अचिन्हित nr_dirty;
	अचिन्हित nr_unqueued_dirty;
	अचिन्हित nr_congested;
	अचिन्हित nr_ग_लिखोback;
	अचिन्हित nr_immediate;
	अचिन्हित nr_pageout;
	अचिन्हित nr_activate[ANON_AND_खाता];
	अचिन्हित nr_ref_keep;
	अचिन्हित nr_unmap_fail;
	अचिन्हित nr_lazyमुक्त_fail;
पूर्ण;

क्रमागत ग_लिखोback_stat_item अणु
	NR_सूचीTY_THRESHOLD,
	NR_सूचीTY_BG_THRESHOLD,
	NR_VM_WRITEBACK_STAT_ITEMS,
पूर्ण;

#अगर_घोषित CONFIG_VM_EVENT_COUNTERS
/*
 * Light weight per cpu counter implementation.
 *
 * Counters should only be incremented and no critical kernel component
 * should rely on the counter values.
 *
 * Counters are handled completely अंतरभूत. On many platक्रमms the code
 * generated will simply be the increment of a global address.
 */

काष्ठा vm_event_state अणु
	अचिन्हित दीर्घ event[NR_VM_EVENT_ITEMS];
पूर्ण;

DECLARE_PER_CPU(काष्ठा vm_event_state, vm_event_states);

/*
 * vm counters are allowed to be racy. Use raw_cpu_ops to aव्योम the
 * local_irq_disable overhead.
 */
अटल अंतरभूत व्योम __count_vm_event(क्रमागत vm_event_item item)
अणु
	raw_cpu_inc(vm_event_states.event[item]);
पूर्ण

अटल अंतरभूत व्योम count_vm_event(क्रमागत vm_event_item item)
अणु
	this_cpu_inc(vm_event_states.event[item]);
पूर्ण

अटल अंतरभूत व्योम __count_vm_events(क्रमागत vm_event_item item, दीर्घ delta)
अणु
	raw_cpu_add(vm_event_states.event[item], delta);
पूर्ण

अटल अंतरभूत व्योम count_vm_events(क्रमागत vm_event_item item, दीर्घ delta)
अणु
	this_cpu_add(vm_event_states.event[item], delta);
पूर्ण

बाह्य व्योम all_vm_events(अचिन्हित दीर्घ *);

बाह्य व्योम vm_events_fold_cpu(पूर्णांक cpu);

#अन्यथा

/* Disable counters */
अटल अंतरभूत व्योम count_vm_event(क्रमागत vm_event_item item)
अणु
पूर्ण
अटल अंतरभूत व्योम count_vm_events(क्रमागत vm_event_item item, दीर्घ delta)
अणु
पूर्ण
अटल अंतरभूत व्योम __count_vm_event(क्रमागत vm_event_item item)
अणु
पूर्ण
अटल अंतरभूत व्योम __count_vm_events(क्रमागत vm_event_item item, दीर्घ delta)
अणु
पूर्ण
अटल अंतरभूत व्योम all_vm_events(अचिन्हित दीर्घ *ret)
अणु
पूर्ण
अटल अंतरभूत व्योम vm_events_fold_cpu(पूर्णांक cpu)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_VM_EVENT_COUNTERS */

#अगर_घोषित CONFIG_NUMA_BALANCING
#घोषणा count_vm_numa_event(x)     count_vm_event(x)
#घोषणा count_vm_numa_events(x, y) count_vm_events(x, y)
#अन्यथा
#घोषणा count_vm_numa_event(x) करो अणुपूर्ण जबतक (0)
#घोषणा count_vm_numa_events(x, y) करो अणु (व्योम)(y); पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */

#अगर_घोषित CONFIG_DEBUG_TLBFLUSH
#घोषणा count_vm_tlb_event(x)	   count_vm_event(x)
#घोषणा count_vm_tlb_events(x, y)  count_vm_events(x, y)
#अन्यथा
#घोषणा count_vm_tlb_event(x)     करो अणुपूर्ण जबतक (0)
#घोषणा count_vm_tlb_events(x, y) करो अणु (व्योम)(y); पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_VM_VMACACHE
#घोषणा count_vm_vmacache_event(x) count_vm_event(x)
#अन्यथा
#घोषणा count_vm_vmacache_event(x) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा __count_zid_vm_events(item, zid, delta) \
	__count_vm_events(item##_NORMAL - ZONE_NORMAL + zid, delta)

/*
 * Zone and node-based page accounting with per cpu dअगरferentials.
 */
बाह्य atomic_दीर्घ_t vm_zone_stat[NR_VM_ZONE_STAT_ITEMS];
बाह्य atomic_दीर्घ_t vm_numa_stat[NR_VM_NUMA_STAT_ITEMS];
बाह्य atomic_दीर्घ_t vm_node_stat[NR_VM_NODE_STAT_ITEMS];

#अगर_घोषित CONFIG_NUMA
अटल अंतरभूत व्योम zone_numa_state_add(दीर्घ x, काष्ठा zone *zone,
				 क्रमागत numa_stat_item item)
अणु
	atomic_दीर्घ_add(x, &zone->vm_numa_stat[item]);
	atomic_दीर्घ_add(x, &vm_numa_stat[item]);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ global_numa_state(क्रमागत numa_stat_item item)
अणु
	दीर्घ x = atomic_दीर्घ_पढ़ो(&vm_numa_stat[item]);

	वापस x;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ zone_numa_state_snapshot(काष्ठा zone *zone,
					क्रमागत numa_stat_item item)
अणु
	दीर्घ x = atomic_दीर्घ_पढ़ो(&zone->vm_numa_stat[item]);
	पूर्णांक cpu;

	क्रम_each_online_cpu(cpu)
		x += per_cpu_ptr(zone->pageset, cpu)->vm_numa_stat_dअगरf[item];

	वापस x;
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA */

अटल अंतरभूत व्योम zone_page_state_add(दीर्घ x, काष्ठा zone *zone,
				 क्रमागत zone_stat_item item)
अणु
	atomic_दीर्घ_add(x, &zone->vm_stat[item]);
	atomic_दीर्घ_add(x, &vm_zone_stat[item]);
पूर्ण

अटल अंतरभूत व्योम node_page_state_add(दीर्घ x, काष्ठा pglist_data *pgdat,
				 क्रमागत node_stat_item item)
अणु
	atomic_दीर्घ_add(x, &pgdat->vm_stat[item]);
	atomic_दीर्घ_add(x, &vm_node_stat[item]);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ global_zone_page_state(क्रमागत zone_stat_item item)
अणु
	दीर्घ x = atomic_दीर्घ_पढ़ो(&vm_zone_stat[item]);
#अगर_घोषित CONFIG_SMP
	अगर (x < 0)
		x = 0;
#पूर्ण_अगर
	वापस x;
पूर्ण

अटल अंतरभूत
अचिन्हित दीर्घ global_node_page_state_pages(क्रमागत node_stat_item item)
अणु
	दीर्घ x = atomic_दीर्घ_पढ़ो(&vm_node_stat[item]);
#अगर_घोषित CONFIG_SMP
	अगर (x < 0)
		x = 0;
#पूर्ण_अगर
	वापस x;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ global_node_page_state(क्रमागत node_stat_item item)
अणु
	VM_WARN_ON_ONCE(vmstat_item_in_bytes(item));

	वापस global_node_page_state_pages(item);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ zone_page_state(काष्ठा zone *zone,
					क्रमागत zone_stat_item item)
अणु
	दीर्घ x = atomic_दीर्घ_पढ़ो(&zone->vm_stat[item]);
#अगर_घोषित CONFIG_SMP
	अगर (x < 0)
		x = 0;
#पूर्ण_अगर
	वापस x;
पूर्ण

/*
 * More accurate version that also considers the currently pending
 * deltas. For that we need to loop over all cpus to find the current
 * deltas. There is no synchronization so the result cannot be
 * exactly accurate either.
 */
अटल अंतरभूत अचिन्हित दीर्घ zone_page_state_snapshot(काष्ठा zone *zone,
					क्रमागत zone_stat_item item)
अणु
	दीर्घ x = atomic_दीर्घ_पढ़ो(&zone->vm_stat[item]);

#अगर_घोषित CONFIG_SMP
	पूर्णांक cpu;
	क्रम_each_online_cpu(cpu)
		x += per_cpu_ptr(zone->pageset, cpu)->vm_stat_dअगरf[item];

	अगर (x < 0)
		x = 0;
#पूर्ण_अगर
	वापस x;
पूर्ण

#अगर_घोषित CONFIG_NUMA
बाह्य व्योम __inc_numa_state(काष्ठा zone *zone, क्रमागत numa_stat_item item);
बाह्य अचिन्हित दीर्घ sum_zone_node_page_state(पूर्णांक node,
					      क्रमागत zone_stat_item item);
बाह्य अचिन्हित दीर्घ sum_zone_numa_state(पूर्णांक node, क्रमागत numa_stat_item item);
बाह्य अचिन्हित दीर्घ node_page_state(काष्ठा pglist_data *pgdat,
						क्रमागत node_stat_item item);
बाह्य अचिन्हित दीर्घ node_page_state_pages(काष्ठा pglist_data *pgdat,
					   क्रमागत node_stat_item item);
#अन्यथा
#घोषणा sum_zone_node_page_state(node, item) global_zone_page_state(item)
#घोषणा node_page_state(node, item) global_node_page_state(item)
#घोषणा node_page_state_pages(node, item) global_node_page_state_pages(item)
#पूर्ण_अगर /* CONFIG_NUMA */

#अगर_घोषित CONFIG_SMP
व्योम __mod_zone_page_state(काष्ठा zone *, क्रमागत zone_stat_item item, दीर्घ);
व्योम __inc_zone_page_state(काष्ठा page *, क्रमागत zone_stat_item);
व्योम __dec_zone_page_state(काष्ठा page *, क्रमागत zone_stat_item);

व्योम __mod_node_page_state(काष्ठा pglist_data *, क्रमागत node_stat_item item, दीर्घ);
व्योम __inc_node_page_state(काष्ठा page *, क्रमागत node_stat_item);
व्योम __dec_node_page_state(काष्ठा page *, क्रमागत node_stat_item);

व्योम mod_zone_page_state(काष्ठा zone *, क्रमागत zone_stat_item, दीर्घ);
व्योम inc_zone_page_state(काष्ठा page *, क्रमागत zone_stat_item);
व्योम dec_zone_page_state(काष्ठा page *, क्रमागत zone_stat_item);

व्योम mod_node_page_state(काष्ठा pglist_data *, क्रमागत node_stat_item, दीर्घ);
व्योम inc_node_page_state(काष्ठा page *, क्रमागत node_stat_item);
व्योम dec_node_page_state(काष्ठा page *, क्रमागत node_stat_item);

बाह्य व्योम inc_node_state(काष्ठा pglist_data *, क्रमागत node_stat_item);
बाह्य व्योम __inc_zone_state(काष्ठा zone *, क्रमागत zone_stat_item);
बाह्य व्योम __inc_node_state(काष्ठा pglist_data *, क्रमागत node_stat_item);
बाह्य व्योम dec_zone_state(काष्ठा zone *, क्रमागत zone_stat_item);
बाह्य व्योम __dec_zone_state(काष्ठा zone *, क्रमागत zone_stat_item);
बाह्य व्योम __dec_node_state(काष्ठा pglist_data *, क्रमागत node_stat_item);

व्योम quiet_vmstat(व्योम);
व्योम cpu_vm_stats_fold(पूर्णांक cpu);
व्योम refresh_zone_stat_thresholds(व्योम);

काष्ठा ctl_table;
पूर्णांक vmstat_refresh(काष्ठा ctl_table *, पूर्णांक ग_लिखो, व्योम *buffer, माप_प्रकार *lenp,
		loff_t *ppos);

व्योम drain_zonestat(काष्ठा zone *zone, काष्ठा per_cpu_pageset *);

पूर्णांक calculate_pressure_threshold(काष्ठा zone *zone);
पूर्णांक calculate_normal_threshold(काष्ठा zone *zone);
व्योम set_pgdat_percpu_threshold(pg_data_t *pgdat,
				पूर्णांक (*calculate_pressure)(काष्ठा zone *));
#अन्यथा /* CONFIG_SMP */

/*
 * We करो not मुख्यtain dअगरferentials in a single processor configuration.
 * The functions directly modअगरy the zone and global counters.
 */
अटल अंतरभूत व्योम __mod_zone_page_state(काष्ठा zone *zone,
			क्रमागत zone_stat_item item, दीर्घ delta)
अणु
	zone_page_state_add(delta, zone, item);
पूर्ण

अटल अंतरभूत व्योम __mod_node_page_state(काष्ठा pglist_data *pgdat,
			क्रमागत node_stat_item item, पूर्णांक delta)
अणु
	अगर (vmstat_item_in_bytes(item)) अणु
		/*
		 * Only cgroups use subpage accounting right now; at
		 * the global level, these items still change in
		 * multiples of whole pages. Store them as pages
		 * पूर्णांकernally to keep the per-cpu counters compact.
		 */
		VM_WARN_ON_ONCE(delta & (PAGE_SIZE - 1));
		delta >>= PAGE_SHIFT;
	पूर्ण

	node_page_state_add(delta, pgdat, item);
पूर्ण

अटल अंतरभूत व्योम __inc_zone_state(काष्ठा zone *zone, क्रमागत zone_stat_item item)
अणु
	atomic_दीर्घ_inc(&zone->vm_stat[item]);
	atomic_दीर्घ_inc(&vm_zone_stat[item]);
पूर्ण

अटल अंतरभूत व्योम __inc_node_state(काष्ठा pglist_data *pgdat, क्रमागत node_stat_item item)
अणु
	atomic_दीर्घ_inc(&pgdat->vm_stat[item]);
	atomic_दीर्घ_inc(&vm_node_stat[item]);
पूर्ण

अटल अंतरभूत व्योम __dec_zone_state(काष्ठा zone *zone, क्रमागत zone_stat_item item)
अणु
	atomic_दीर्घ_dec(&zone->vm_stat[item]);
	atomic_दीर्घ_dec(&vm_zone_stat[item]);
पूर्ण

अटल अंतरभूत व्योम __dec_node_state(काष्ठा pglist_data *pgdat, क्रमागत node_stat_item item)
अणु
	atomic_दीर्घ_dec(&pgdat->vm_stat[item]);
	atomic_दीर्घ_dec(&vm_node_stat[item]);
पूर्ण

अटल अंतरभूत व्योम __inc_zone_page_state(काष्ठा page *page,
			क्रमागत zone_stat_item item)
अणु
	__inc_zone_state(page_zone(page), item);
पूर्ण

अटल अंतरभूत व्योम __inc_node_page_state(काष्ठा page *page,
			क्रमागत node_stat_item item)
अणु
	__inc_node_state(page_pgdat(page), item);
पूर्ण


अटल अंतरभूत व्योम __dec_zone_page_state(काष्ठा page *page,
			क्रमागत zone_stat_item item)
अणु
	__dec_zone_state(page_zone(page), item);
पूर्ण

अटल अंतरभूत व्योम __dec_node_page_state(काष्ठा page *page,
			क्रमागत node_stat_item item)
अणु
	__dec_node_state(page_pgdat(page), item);
पूर्ण


/*
 * We only use atomic operations to update counters. So there is no need to
 * disable पूर्णांकerrupts.
 */
#घोषणा inc_zone_page_state __inc_zone_page_state
#घोषणा dec_zone_page_state __dec_zone_page_state
#घोषणा mod_zone_page_state __mod_zone_page_state

#घोषणा inc_node_page_state __inc_node_page_state
#घोषणा dec_node_page_state __dec_node_page_state
#घोषणा mod_node_page_state __mod_node_page_state

#घोषणा inc_zone_state __inc_zone_state
#घोषणा inc_node_state __inc_node_state
#घोषणा dec_zone_state __dec_zone_state

#घोषणा set_pgdat_percpu_threshold(pgdat, callback) अणु पूर्ण

अटल अंतरभूत व्योम refresh_zone_stat_thresholds(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम cpu_vm_stats_fold(पूर्णांक cpu) अणु पूर्ण
अटल अंतरभूत व्योम quiet_vmstat(व्योम) अणु पूर्ण

अटल अंतरभूत व्योम drain_zonestat(काष्ठा zone *zone,
			काष्ठा per_cpu_pageset *pset) अणु पूर्ण
#पूर्ण_अगर		/* CONFIG_SMP */

अटल अंतरभूत व्योम __mod_zone_मुक्तpage_state(काष्ठा zone *zone, पूर्णांक nr_pages,
					     पूर्णांक migratetype)
अणु
	__mod_zone_page_state(zone, NR_FREE_PAGES, nr_pages);
	अगर (is_migrate_cma(migratetype))
		__mod_zone_page_state(zone, NR_FREE_CMA_PAGES, nr_pages);
पूर्ण

बाह्य स्थिर अक्षर * स्थिर vmstat_text[];

अटल अंतरभूत स्थिर अक्षर *zone_stat_name(क्रमागत zone_stat_item item)
अणु
	वापस vmstat_text[item];
पूर्ण

#अगर_घोषित CONFIG_NUMA
अटल अंतरभूत स्थिर अक्षर *numa_stat_name(क्रमागत numa_stat_item item)
अणु
	वापस vmstat_text[NR_VM_ZONE_STAT_ITEMS +
			   item];
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA */

अटल अंतरभूत स्थिर अक्षर *node_stat_name(क्रमागत node_stat_item item)
अणु
	वापस vmstat_text[NR_VM_ZONE_STAT_ITEMS +
			   NR_VM_NUMA_STAT_ITEMS +
			   item];
पूर्ण

अटल अंतरभूत स्थिर अक्षर *lru_list_name(क्रमागत lru_list lru)
अणु
	वापस node_stat_name(NR_LRU_BASE + lru) + 3; // skip "nr_"
पूर्ण

अटल अंतरभूत स्थिर अक्षर *ग_लिखोback_stat_name(क्रमागत ग_लिखोback_stat_item item)
अणु
	वापस vmstat_text[NR_VM_ZONE_STAT_ITEMS +
			   NR_VM_NUMA_STAT_ITEMS +
			   NR_VM_NODE_STAT_ITEMS +
			   item];
पूर्ण

#अगर defined(CONFIG_VM_EVENT_COUNTERS) || defined(CONFIG_MEMCG)
अटल अंतरभूत स्थिर अक्षर *vm_event_name(क्रमागत vm_event_item item)
अणु
	वापस vmstat_text[NR_VM_ZONE_STAT_ITEMS +
			   NR_VM_NUMA_STAT_ITEMS +
			   NR_VM_NODE_STAT_ITEMS +
			   NR_VM_WRITEBACK_STAT_ITEMS +
			   item];
पूर्ण
#पूर्ण_अगर /* CONFIG_VM_EVENT_COUNTERS || CONFIG_MEMCG */

#अगर_घोषित CONFIG_MEMCG

व्योम __mod_lruvec_state(काष्ठा lruvec *lruvec, क्रमागत node_stat_item idx,
			पूर्णांक val);

अटल अंतरभूत व्योम mod_lruvec_state(काष्ठा lruvec *lruvec,
				    क्रमागत node_stat_item idx, पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__mod_lruvec_state(lruvec, idx, val);
	local_irq_restore(flags);
पूर्ण

व्योम __mod_lruvec_page_state(काष्ठा page *page,
			     क्रमागत node_stat_item idx, पूर्णांक val);

अटल अंतरभूत व्योम mod_lruvec_page_state(काष्ठा page *page,
					 क्रमागत node_stat_item idx, पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__mod_lruvec_page_state(page, idx, val);
	local_irq_restore(flags);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम __mod_lruvec_state(काष्ठा lruvec *lruvec,
				      क्रमागत node_stat_item idx, पूर्णांक val)
अणु
	__mod_node_page_state(lruvec_pgdat(lruvec), idx, val);
पूर्ण

अटल अंतरभूत व्योम mod_lruvec_state(काष्ठा lruvec *lruvec,
				    क्रमागत node_stat_item idx, पूर्णांक val)
अणु
	mod_node_page_state(lruvec_pgdat(lruvec), idx, val);
पूर्ण

अटल अंतरभूत व्योम __mod_lruvec_page_state(काष्ठा page *page,
					   क्रमागत node_stat_item idx, पूर्णांक val)
अणु
	__mod_node_page_state(page_pgdat(page), idx, val);
पूर्ण

अटल अंतरभूत व्योम mod_lruvec_page_state(काष्ठा page *page,
					 क्रमागत node_stat_item idx, पूर्णांक val)
अणु
	mod_node_page_state(page_pgdat(page), idx, val);
पूर्ण

#पूर्ण_अगर /* CONFIG_MEMCG */

अटल अंतरभूत व्योम inc_lruvec_state(काष्ठा lruvec *lruvec,
				    क्रमागत node_stat_item idx)
अणु
	mod_lruvec_state(lruvec, idx, 1);
पूर्ण

अटल अंतरभूत व्योम __inc_lruvec_page_state(काष्ठा page *page,
					   क्रमागत node_stat_item idx)
अणु
	__mod_lruvec_page_state(page, idx, 1);
पूर्ण

अटल अंतरभूत व्योम __dec_lruvec_page_state(काष्ठा page *page,
					   क्रमागत node_stat_item idx)
अणु
	__mod_lruvec_page_state(page, idx, -1);
पूर्ण

अटल अंतरभूत व्योम inc_lruvec_page_state(काष्ठा page *page,
					 क्रमागत node_stat_item idx)
अणु
	mod_lruvec_page_state(page, idx, 1);
पूर्ण

अटल अंतरभूत व्योम dec_lruvec_page_state(काष्ठा page *page,
					 क्रमागत node_stat_item idx)
अणु
	mod_lruvec_page_state(page, idx, -1);
पूर्ण

#पूर्ण_अगर /* _LINUX_VMSTAT_H */
