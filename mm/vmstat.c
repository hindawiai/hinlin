<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/mm/vmstat.c
 *
 *  Manages VM statistics
 *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 *
 *  zoned VM statistics
 *  Copyright (C) 2006 Silicon Graphics, Inc.,
 *		Christoph Lameter <christoph@lameter.com>
 *  Copyright (C) 2008-2014 Christoph Lameter
 */
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/vmस्थिति.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/sched.h>
#समावेश <linux/math64.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/compaction.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/page_ext.h>
#समावेश <linux/page_owner.h>

#समावेश "internal.h"

#घोषणा NUMA_STATS_THRESHOLD (U16_MAX - 2)

#अगर_घोषित CONFIG_NUMA
पूर्णांक sysctl_vm_numa_stat = ENABLE_NUMA_STAT;

/* zero numa counters within a zone */
अटल व्योम zero_zone_numa_counters(काष्ठा zone *zone)
अणु
	पूर्णांक item, cpu;

	क्रम (item = 0; item < NR_VM_NUMA_STAT_ITEMS; item++) अणु
		atomic_दीर्घ_set(&zone->vm_numa_stat[item], 0);
		क्रम_each_online_cpu(cpu)
			per_cpu_ptr(zone->pageset, cpu)->vm_numa_stat_dअगरf[item]
						= 0;
	पूर्ण
पूर्ण

/* zero numa counters of all the populated zones */
अटल व्योम zero_zones_numa_counters(व्योम)
अणु
	काष्ठा zone *zone;

	क्रम_each_populated_zone(zone)
		zero_zone_numa_counters(zone);
पूर्ण

/* zero global numa counters */
अटल व्योम zero_global_numa_counters(व्योम)
अणु
	पूर्णांक item;

	क्रम (item = 0; item < NR_VM_NUMA_STAT_ITEMS; item++)
		atomic_दीर्घ_set(&vm_numa_stat[item], 0);
पूर्ण

अटल व्योम invalid_numa_statistics(व्योम)
अणु
	zero_zones_numa_counters();
	zero_global_numa_counters();
पूर्ण

अटल DEFINE_MUTEX(vm_numa_stat_lock);

पूर्णांक sysctl_vm_numa_stat_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *length, loff_t *ppos)
अणु
	पूर्णांक ret, oldval;

	mutex_lock(&vm_numa_stat_lock);
	अगर (ग_लिखो)
		oldval = sysctl_vm_numa_stat;
	ret = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, length, ppos);
	अगर (ret || !ग_लिखो)
		जाओ out;

	अगर (oldval == sysctl_vm_numa_stat)
		जाओ out;
	अन्यथा अगर (sysctl_vm_numa_stat == ENABLE_NUMA_STAT) अणु
		अटल_branch_enable(&vm_numa_stat_key);
		pr_info("enable numa statistics\n");
	पूर्ण अन्यथा अणु
		अटल_branch_disable(&vm_numa_stat_key);
		invalid_numa_statistics();
		pr_info("disable numa statistics, and clear numa counters\n");
	पूर्ण

out:
	mutex_unlock(&vm_numa_stat_lock);
	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_VM_EVENT_COUNTERS
DEFINE_PER_CPU(काष्ठा vm_event_state, vm_event_states) = अणुअणु0पूर्णपूर्ण;
EXPORT_PER_CPU_SYMBOL(vm_event_states);

अटल व्योम sum_vm_events(अचिन्हित दीर्घ *ret)
अणु
	पूर्णांक cpu;
	पूर्णांक i;

	स_रखो(ret, 0, NR_VM_EVENT_ITEMS * माप(अचिन्हित दीर्घ));

	क्रम_each_online_cpu(cpu) अणु
		काष्ठा vm_event_state *this = &per_cpu(vm_event_states, cpu);

		क्रम (i = 0; i < NR_VM_EVENT_ITEMS; i++)
			ret[i] += this->event[i];
	पूर्ण
पूर्ण

/*
 * Accumulate the vm event counters across all CPUs.
 * The result is unaव्योमably approximate - it can change
 * during and after execution of this function.
*/
व्योम all_vm_events(अचिन्हित दीर्घ *ret)
अणु
	get_online_cpus();
	sum_vm_events(ret);
	put_online_cpus();
पूर्ण
EXPORT_SYMBOL_GPL(all_vm_events);

/*
 * Fold the क्रमeign cpu events पूर्णांकo our own.
 *
 * This is adding to the events on one processor
 * but keeps the global counts स्थिरant.
 */
व्योम vm_events_fold_cpu(पूर्णांक cpu)
अणु
	काष्ठा vm_event_state *fold_state = &per_cpu(vm_event_states, cpu);
	पूर्णांक i;

	क्रम (i = 0; i < NR_VM_EVENT_ITEMS; i++) अणु
		count_vm_events(i, fold_state->event[i]);
		fold_state->event[i] = 0;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_VM_EVENT_COUNTERS */

/*
 * Manage combined zone based / global counters
 *
 * vm_stat contains the global counters
 */
atomic_दीर्घ_t vm_zone_stat[NR_VM_ZONE_STAT_ITEMS] __cacheline_aligned_in_smp;
atomic_दीर्घ_t vm_numa_stat[NR_VM_NUMA_STAT_ITEMS] __cacheline_aligned_in_smp;
atomic_दीर्घ_t vm_node_stat[NR_VM_NODE_STAT_ITEMS] __cacheline_aligned_in_smp;
EXPORT_SYMBOL(vm_zone_stat);
EXPORT_SYMBOL(vm_numa_stat);
EXPORT_SYMBOL(vm_node_stat);

#अगर_घोषित CONFIG_SMP

पूर्णांक calculate_pressure_threshold(काष्ठा zone *zone)
अणु
	पूर्णांक threshold;
	पूर्णांक watermark_distance;

	/*
	 * As vmstats are not up to date, there is drअगरt between the estimated
	 * and real values. For high thresholds and a high number of CPUs, it
	 * is possible क्रम the min watermark to be breached जबतक the estimated
	 * value looks fine. The pressure threshold is a reduced value such
	 * that even the maximum amount of drअगरt will not accidentally breach
	 * the min watermark
	 */
	watermark_distance = low_wmark_pages(zone) - min_wmark_pages(zone);
	threshold = max(1, (पूर्णांक)(watermark_distance / num_online_cpus()));

	/*
	 * Maximum threshold is 125
	 */
	threshold = min(125, threshold);

	वापस threshold;
पूर्ण

पूर्णांक calculate_normal_threshold(काष्ठा zone *zone)
अणु
	पूर्णांक threshold;
	पूर्णांक mem;	/* memory in 128 MB units */

	/*
	 * The threshold scales with the number of processors and the amount
	 * of memory per zone. More memory means that we can defer updates क्रम
	 * दीर्घer, more processors could lead to more contention.
 	 * fls() is used to have a cheap way of logarithmic scaling.
	 *
	 * Some sample thresholds:
	 *
	 * Threshold	Processors	(fls)	Zonesize	fls(mem+1)
	 * ------------------------------------------------------------------
	 * 8		1		1	0.9-1 GB	4
	 * 16		2		2	0.9-1 GB	4
	 * 20 		2		2	1-2 GB		5
	 * 24		2		2	2-4 GB		6
	 * 28		2		2	4-8 GB		7
	 * 32		2		2	8-16 GB		8
	 * 4		2		2	<128M		1
	 * 30		4		3	2-4 GB		5
	 * 48		4		3	8-16 GB		8
	 * 32		8		4	1-2 GB		4
	 * 32		8		4	0.9-1GB		4
	 * 10		16		5	<128M		1
	 * 40		16		5	900M		4
	 * 70		64		7	2-4 GB		5
	 * 84		64		7	4-8 GB		6
	 * 108		512		9	4-8 GB		6
	 * 125		1024		10	8-16 GB		8
	 * 125		1024		10	16-32 GB	9
	 */

	mem = zone_managed_pages(zone) >> (27 - PAGE_SHIFT);

	threshold = 2 * fls(num_online_cpus()) * (1 + fls(mem));

	/*
	 * Maximum threshold is 125
	 */
	threshold = min(125, threshold);

	वापस threshold;
पूर्ण

/*
 * Refresh the thresholds क्रम each zone.
 */
व्योम refresh_zone_stat_thresholds(व्योम)
अणु
	काष्ठा pglist_data *pgdat;
	काष्ठा zone *zone;
	पूर्णांक cpu;
	पूर्णांक threshold;

	/* Zero current pgdat thresholds */
	क्रम_each_online_pgdat(pgdat) अणु
		क्रम_each_online_cpu(cpu) अणु
			per_cpu_ptr(pgdat->per_cpu_nodestats, cpu)->stat_threshold = 0;
		पूर्ण
	पूर्ण

	क्रम_each_populated_zone(zone) अणु
		काष्ठा pglist_data *pgdat = zone->zone_pgdat;
		अचिन्हित दीर्घ max_drअगरt, tolerate_drअगरt;

		threshold = calculate_normal_threshold(zone);

		क्रम_each_online_cpu(cpu) अणु
			पूर्णांक pgdat_threshold;

			per_cpu_ptr(zone->pageset, cpu)->stat_threshold
							= threshold;

			/* Base nodestat threshold on the largest populated zone. */
			pgdat_threshold = per_cpu_ptr(pgdat->per_cpu_nodestats, cpu)->stat_threshold;
			per_cpu_ptr(pgdat->per_cpu_nodestats, cpu)->stat_threshold
				= max(threshold, pgdat_threshold);
		पूर्ण

		/*
		 * Only set percpu_drअगरt_mark अगर there is a danger that
		 * NR_FREE_PAGES reports the low watermark is ok when in fact
		 * the min watermark could be breached by an allocation
		 */
		tolerate_drअगरt = low_wmark_pages(zone) - min_wmark_pages(zone);
		max_drअगरt = num_online_cpus() * threshold;
		अगर (max_drअगरt > tolerate_drअगरt)
			zone->percpu_drअगरt_mark = high_wmark_pages(zone) +
					max_drअगरt;
	पूर्ण
पूर्ण

व्योम set_pgdat_percpu_threshold(pg_data_t *pgdat,
				पूर्णांक (*calculate_pressure)(काष्ठा zone *))
अणु
	काष्ठा zone *zone;
	पूर्णांक cpu;
	पूर्णांक threshold;
	पूर्णांक i;

	क्रम (i = 0; i < pgdat->nr_zones; i++) अणु
		zone = &pgdat->node_zones[i];
		अगर (!zone->percpu_drअगरt_mark)
			जारी;

		threshold = (*calculate_pressure)(zone);
		क्रम_each_online_cpu(cpu)
			per_cpu_ptr(zone->pageset, cpu)->stat_threshold
							= threshold;
	पूर्ण
पूर्ण

/*
 * For use when we know that पूर्णांकerrupts are disabled,
 * or when we know that preemption is disabled and that
 * particular counter cannot be updated from पूर्णांकerrupt context.
 */
व्योम __mod_zone_page_state(काष्ठा zone *zone, क्रमागत zone_stat_item item,
			   दीर्घ delta)
अणु
	काष्ठा per_cpu_pageset __percpu *pcp = zone->pageset;
	s8 __percpu *p = pcp->vm_stat_dअगरf + item;
	दीर्घ x;
	दीर्घ t;

	x = delta + __this_cpu_पढ़ो(*p);

	t = __this_cpu_पढ़ो(pcp->stat_threshold);

	अगर (unlikely(असल(x) > t)) अणु
		zone_page_state_add(x, zone, item);
		x = 0;
	पूर्ण
	__this_cpu_ग_लिखो(*p, x);
पूर्ण
EXPORT_SYMBOL(__mod_zone_page_state);

व्योम __mod_node_page_state(काष्ठा pglist_data *pgdat, क्रमागत node_stat_item item,
				दीर्घ delta)
अणु
	काष्ठा per_cpu_nodestat __percpu *pcp = pgdat->per_cpu_nodestats;
	s8 __percpu *p = pcp->vm_node_stat_dअगरf + item;
	दीर्घ x;
	दीर्घ t;

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

	x = delta + __this_cpu_पढ़ो(*p);

	t = __this_cpu_पढ़ो(pcp->stat_threshold);

	अगर (unlikely(असल(x) > t)) अणु
		node_page_state_add(x, pgdat, item);
		x = 0;
	पूर्ण
	__this_cpu_ग_लिखो(*p, x);
पूर्ण
EXPORT_SYMBOL(__mod_node_page_state);

/*
 * Optimized increment and decrement functions.
 *
 * These are only क्रम a single page and thereक्रमe can take a काष्ठा page *
 * argument instead of काष्ठा zone *. This allows the inclusion of the code
 * generated क्रम page_zone(page) पूर्णांकo the optimized functions.
 *
 * No overflow check is necessary and thereक्रमe the dअगरferential can be
 * incremented or decremented in place which may allow the compilers to
 * generate better code.
 * The increment or decrement is known and thereक्रमe one boundary check can
 * be omitted.
 *
 * NOTE: These functions are very perक्रमmance sensitive. Change only
 * with care.
 *
 * Some processors have inc/dec inकाष्ठाions that are atomic vs an पूर्णांकerrupt.
 * However, the code must first determine the dअगरferential location in a zone
 * based on the processor number and then inc/dec the counter. There is no
 * guarantee without disabling preemption that the processor will not change
 * in between and thereक्रमe the atomicity vs. पूर्णांकerrupt cannot be exploited
 * in a useful way here.
 */
व्योम __inc_zone_state(काष्ठा zone *zone, क्रमागत zone_stat_item item)
अणु
	काष्ठा per_cpu_pageset __percpu *pcp = zone->pageset;
	s8 __percpu *p = pcp->vm_stat_dअगरf + item;
	s8 v, t;

	v = __this_cpu_inc_वापस(*p);
	t = __this_cpu_पढ़ो(pcp->stat_threshold);
	अगर (unlikely(v > t)) अणु
		s8 overstep = t >> 1;

		zone_page_state_add(v + overstep, zone, item);
		__this_cpu_ग_लिखो(*p, -overstep);
	पूर्ण
पूर्ण

व्योम __inc_node_state(काष्ठा pglist_data *pgdat, क्रमागत node_stat_item item)
अणु
	काष्ठा per_cpu_nodestat __percpu *pcp = pgdat->per_cpu_nodestats;
	s8 __percpu *p = pcp->vm_node_stat_dअगरf + item;
	s8 v, t;

	VM_WARN_ON_ONCE(vmstat_item_in_bytes(item));

	v = __this_cpu_inc_वापस(*p);
	t = __this_cpu_पढ़ो(pcp->stat_threshold);
	अगर (unlikely(v > t)) अणु
		s8 overstep = t >> 1;

		node_page_state_add(v + overstep, pgdat, item);
		__this_cpu_ग_लिखो(*p, -overstep);
	पूर्ण
पूर्ण

व्योम __inc_zone_page_state(काष्ठा page *page, क्रमागत zone_stat_item item)
अणु
	__inc_zone_state(page_zone(page), item);
पूर्ण
EXPORT_SYMBOL(__inc_zone_page_state);

व्योम __inc_node_page_state(काष्ठा page *page, क्रमागत node_stat_item item)
अणु
	__inc_node_state(page_pgdat(page), item);
पूर्ण
EXPORT_SYMBOL(__inc_node_page_state);

व्योम __dec_zone_state(काष्ठा zone *zone, क्रमागत zone_stat_item item)
अणु
	काष्ठा per_cpu_pageset __percpu *pcp = zone->pageset;
	s8 __percpu *p = pcp->vm_stat_dअगरf + item;
	s8 v, t;

	v = __this_cpu_dec_वापस(*p);
	t = __this_cpu_पढ़ो(pcp->stat_threshold);
	अगर (unlikely(v < - t)) अणु
		s8 overstep = t >> 1;

		zone_page_state_add(v - overstep, zone, item);
		__this_cpu_ग_लिखो(*p, overstep);
	पूर्ण
पूर्ण

व्योम __dec_node_state(काष्ठा pglist_data *pgdat, क्रमागत node_stat_item item)
अणु
	काष्ठा per_cpu_nodestat __percpu *pcp = pgdat->per_cpu_nodestats;
	s8 __percpu *p = pcp->vm_node_stat_dअगरf + item;
	s8 v, t;

	VM_WARN_ON_ONCE(vmstat_item_in_bytes(item));

	v = __this_cpu_dec_वापस(*p);
	t = __this_cpu_पढ़ो(pcp->stat_threshold);
	अगर (unlikely(v < - t)) अणु
		s8 overstep = t >> 1;

		node_page_state_add(v - overstep, pgdat, item);
		__this_cpu_ग_लिखो(*p, overstep);
	पूर्ण
पूर्ण

व्योम __dec_zone_page_state(काष्ठा page *page, क्रमागत zone_stat_item item)
अणु
	__dec_zone_state(page_zone(page), item);
पूर्ण
EXPORT_SYMBOL(__dec_zone_page_state);

व्योम __dec_node_page_state(काष्ठा page *page, क्रमागत node_stat_item item)
अणु
	__dec_node_state(page_pgdat(page), item);
पूर्ण
EXPORT_SYMBOL(__dec_node_page_state);

#अगर_घोषित CONFIG_HAVE_CMPXCHG_LOCAL
/*
 * If we have cmpxchg_local support then we करो not need to incur the overhead
 * that comes with local_irq_save/restore अगर we use this_cpu_cmpxchg.
 *
 * mod_state() modअगरies the zone counter state through atomic per cpu
 * operations.
 *
 * Overstep mode specअगरies how overstep should handled:
 *     0       No overstepping
 *     1       Overstepping half of threshold
 *     -1      Overstepping minus half of threshold
*/
अटल अंतरभूत व्योम mod_zone_state(काष्ठा zone *zone,
       क्रमागत zone_stat_item item, दीर्घ delta, पूर्णांक overstep_mode)
अणु
	काष्ठा per_cpu_pageset __percpu *pcp = zone->pageset;
	s8 __percpu *p = pcp->vm_stat_dअगरf + item;
	दीर्घ o, n, t, z;

	करो अणु
		z = 0;  /* overflow to zone counters */

		/*
		 * The fetching of the stat_threshold is racy. We may apply
		 * a counter threshold to the wrong the cpu अगर we get
		 * rescheduled जबतक executing here. However, the next
		 * counter update will apply the threshold again and
		 * thereक्रमe bring the counter under the threshold again.
		 *
		 * Most of the समय the thresholds are the same anyways
		 * क्रम all cpus in a zone.
		 */
		t = this_cpu_पढ़ो(pcp->stat_threshold);

		o = this_cpu_पढ़ो(*p);
		n = delta + o;

		अगर (असल(n) > t) अणु
			पूर्णांक os = overstep_mode * (t >> 1) ;

			/* Overflow must be added to zone counters */
			z = n + os;
			n = -os;
		पूर्ण
	पूर्ण जबतक (this_cpu_cmpxchg(*p, o, n) != o);

	अगर (z)
		zone_page_state_add(z, zone, item);
पूर्ण

व्योम mod_zone_page_state(काष्ठा zone *zone, क्रमागत zone_stat_item item,
			 दीर्घ delta)
अणु
	mod_zone_state(zone, item, delta, 0);
पूर्ण
EXPORT_SYMBOL(mod_zone_page_state);

व्योम inc_zone_page_state(काष्ठा page *page, क्रमागत zone_stat_item item)
अणु
	mod_zone_state(page_zone(page), item, 1, 1);
पूर्ण
EXPORT_SYMBOL(inc_zone_page_state);

व्योम dec_zone_page_state(काष्ठा page *page, क्रमागत zone_stat_item item)
अणु
	mod_zone_state(page_zone(page), item, -1, -1);
पूर्ण
EXPORT_SYMBOL(dec_zone_page_state);

अटल अंतरभूत व्योम mod_node_state(काष्ठा pglist_data *pgdat,
       क्रमागत node_stat_item item, पूर्णांक delta, पूर्णांक overstep_mode)
अणु
	काष्ठा per_cpu_nodestat __percpu *pcp = pgdat->per_cpu_nodestats;
	s8 __percpu *p = pcp->vm_node_stat_dअगरf + item;
	दीर्घ o, n, t, z;

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

	करो अणु
		z = 0;  /* overflow to node counters */

		/*
		 * The fetching of the stat_threshold is racy. We may apply
		 * a counter threshold to the wrong the cpu अगर we get
		 * rescheduled जबतक executing here. However, the next
		 * counter update will apply the threshold again and
		 * thereक्रमe bring the counter under the threshold again.
		 *
		 * Most of the समय the thresholds are the same anyways
		 * क्रम all cpus in a node.
		 */
		t = this_cpu_पढ़ो(pcp->stat_threshold);

		o = this_cpu_पढ़ो(*p);
		n = delta + o;

		अगर (असल(n) > t) अणु
			पूर्णांक os = overstep_mode * (t >> 1) ;

			/* Overflow must be added to node counters */
			z = n + os;
			n = -os;
		पूर्ण
	पूर्ण जबतक (this_cpu_cmpxchg(*p, o, n) != o);

	अगर (z)
		node_page_state_add(z, pgdat, item);
पूर्ण

व्योम mod_node_page_state(काष्ठा pglist_data *pgdat, क्रमागत node_stat_item item,
					दीर्घ delta)
अणु
	mod_node_state(pgdat, item, delta, 0);
पूर्ण
EXPORT_SYMBOL(mod_node_page_state);

व्योम inc_node_state(काष्ठा pglist_data *pgdat, क्रमागत node_stat_item item)
अणु
	mod_node_state(pgdat, item, 1, 1);
पूर्ण

व्योम inc_node_page_state(काष्ठा page *page, क्रमागत node_stat_item item)
अणु
	mod_node_state(page_pgdat(page), item, 1, 1);
पूर्ण
EXPORT_SYMBOL(inc_node_page_state);

व्योम dec_node_page_state(काष्ठा page *page, क्रमागत node_stat_item item)
अणु
	mod_node_state(page_pgdat(page), item, -1, -1);
पूर्ण
EXPORT_SYMBOL(dec_node_page_state);
#अन्यथा
/*
 * Use पूर्णांकerrupt disable to serialize counter updates
 */
व्योम mod_zone_page_state(काष्ठा zone *zone, क्रमागत zone_stat_item item,
			 दीर्घ delta)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__mod_zone_page_state(zone, item, delta);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(mod_zone_page_state);

व्योम inc_zone_page_state(काष्ठा page *page, क्रमागत zone_stat_item item)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा zone *zone;

	zone = page_zone(page);
	local_irq_save(flags);
	__inc_zone_state(zone, item);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(inc_zone_page_state);

व्योम dec_zone_page_state(काष्ठा page *page, क्रमागत zone_stat_item item)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__dec_zone_page_state(page, item);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(dec_zone_page_state);

व्योम inc_node_state(काष्ठा pglist_data *pgdat, क्रमागत node_stat_item item)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__inc_node_state(pgdat, item);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(inc_node_state);

व्योम mod_node_page_state(काष्ठा pglist_data *pgdat, क्रमागत node_stat_item item,
					दीर्घ delta)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__mod_node_page_state(pgdat, item, delta);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(mod_node_page_state);

व्योम inc_node_page_state(काष्ठा page *page, क्रमागत node_stat_item item)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pglist_data *pgdat;

	pgdat = page_pgdat(page);
	local_irq_save(flags);
	__inc_node_state(pgdat, item);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(inc_node_page_state);

व्योम dec_node_page_state(काष्ठा page *page, क्रमागत node_stat_item item)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__dec_node_page_state(page, item);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(dec_node_page_state);
#पूर्ण_अगर

/*
 * Fold a dअगरferential पूर्णांकo the global counters.
 * Returns the number of counters updated.
 */
#अगर_घोषित CONFIG_NUMA
अटल पूर्णांक fold_dअगरf(पूर्णांक *zone_dअगरf, पूर्णांक *numa_dअगरf, पूर्णांक *node_dअगरf)
अणु
	पूर्णांक i;
	पूर्णांक changes = 0;

	क्रम (i = 0; i < NR_VM_ZONE_STAT_ITEMS; i++)
		अगर (zone_dअगरf[i]) अणु
			atomic_दीर्घ_add(zone_dअगरf[i], &vm_zone_stat[i]);
			changes++;
	पूर्ण

	क्रम (i = 0; i < NR_VM_NUMA_STAT_ITEMS; i++)
		अगर (numa_dअगरf[i]) अणु
			atomic_दीर्घ_add(numa_dअगरf[i], &vm_numa_stat[i]);
			changes++;
	पूर्ण

	क्रम (i = 0; i < NR_VM_NODE_STAT_ITEMS; i++)
		अगर (node_dअगरf[i]) अणु
			atomic_दीर्घ_add(node_dअगरf[i], &vm_node_stat[i]);
			changes++;
	पूर्ण
	वापस changes;
पूर्ण
#अन्यथा
अटल पूर्णांक fold_dअगरf(पूर्णांक *zone_dअगरf, पूर्णांक *node_dअगरf)
अणु
	पूर्णांक i;
	पूर्णांक changes = 0;

	क्रम (i = 0; i < NR_VM_ZONE_STAT_ITEMS; i++)
		अगर (zone_dअगरf[i]) अणु
			atomic_दीर्घ_add(zone_dअगरf[i], &vm_zone_stat[i]);
			changes++;
	पूर्ण

	क्रम (i = 0; i < NR_VM_NODE_STAT_ITEMS; i++)
		अगर (node_dअगरf[i]) अणु
			atomic_दीर्घ_add(node_dअगरf[i], &vm_node_stat[i]);
			changes++;
	पूर्ण
	वापस changes;
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA */

/*
 * Update the zone counters क्रम the current cpu.
 *
 * Note that refresh_cpu_vm_stats strives to only access
 * node local memory. The per cpu pagesets on remote zones are placed
 * in the memory local to the processor using that pageset. So the
 * loop over all zones will access a series of cachelines local to
 * the processor.
 *
 * The call to zone_page_state_add updates the cachelines with the
 * statistics in the remote zone काष्ठा as well as the global cachelines
 * with the global counters. These could cause remote node cache line
 * bouncing and will have to be only करोne when necessary.
 *
 * The function वापसs the number of global counters updated.
 */
अटल पूर्णांक refresh_cpu_vm_stats(bool करो_pagesets)
अणु
	काष्ठा pglist_data *pgdat;
	काष्ठा zone *zone;
	पूर्णांक i;
	पूर्णांक global_zone_dअगरf[NR_VM_ZONE_STAT_ITEMS] = अणु 0, पूर्ण;
#अगर_घोषित CONFIG_NUMA
	पूर्णांक global_numa_dअगरf[NR_VM_NUMA_STAT_ITEMS] = अणु 0, पूर्ण;
#पूर्ण_अगर
	पूर्णांक global_node_dअगरf[NR_VM_NODE_STAT_ITEMS] = अणु 0, पूर्ण;
	पूर्णांक changes = 0;

	क्रम_each_populated_zone(zone) अणु
		काष्ठा per_cpu_pageset __percpu *p = zone->pageset;

		क्रम (i = 0; i < NR_VM_ZONE_STAT_ITEMS; i++) अणु
			पूर्णांक v;

			v = this_cpu_xchg(p->vm_stat_dअगरf[i], 0);
			अगर (v) अणु

				atomic_दीर्घ_add(v, &zone->vm_stat[i]);
				global_zone_dअगरf[i] += v;
#अगर_घोषित CONFIG_NUMA
				/* 3 seconds idle till flush */
				__this_cpu_ग_लिखो(p->expire, 3);
#पूर्ण_अगर
			पूर्ण
		पूर्ण
#अगर_घोषित CONFIG_NUMA
		क्रम (i = 0; i < NR_VM_NUMA_STAT_ITEMS; i++) अणु
			पूर्णांक v;

			v = this_cpu_xchg(p->vm_numa_stat_dअगरf[i], 0);
			अगर (v) अणु

				atomic_दीर्घ_add(v, &zone->vm_numa_stat[i]);
				global_numa_dअगरf[i] += v;
				__this_cpu_ग_लिखो(p->expire, 3);
			पूर्ण
		पूर्ण

		अगर (करो_pagesets) अणु
			cond_resched();
			/*
			 * Deal with draining the remote pageset of this
			 * processor
			 *
			 * Check अगर there are pages reमुख्यing in this pageset
			 * अगर not then there is nothing to expire.
			 */
			अगर (!__this_cpu_पढ़ो(p->expire) ||
			       !__this_cpu_पढ़ो(p->pcp.count))
				जारी;

			/*
			 * We never drain zones local to this processor.
			 */
			अगर (zone_to_nid(zone) == numa_node_id()) अणु
				__this_cpu_ग_लिखो(p->expire, 0);
				जारी;
			पूर्ण

			अगर (__this_cpu_dec_वापस(p->expire))
				जारी;

			अगर (__this_cpu_पढ़ो(p->pcp.count)) अणु
				drain_zone_pages(zone, this_cpu_ptr(&p->pcp));
				changes++;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	क्रम_each_online_pgdat(pgdat) अणु
		काष्ठा per_cpu_nodestat __percpu *p = pgdat->per_cpu_nodestats;

		क्रम (i = 0; i < NR_VM_NODE_STAT_ITEMS; i++) अणु
			पूर्णांक v;

			v = this_cpu_xchg(p->vm_node_stat_dअगरf[i], 0);
			अगर (v) अणु
				atomic_दीर्घ_add(v, &pgdat->vm_stat[i]);
				global_node_dअगरf[i] += v;
			पूर्ण
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_NUMA
	changes += fold_dअगरf(global_zone_dअगरf, global_numa_dअगरf,
			     global_node_dअगरf);
#अन्यथा
	changes += fold_dअगरf(global_zone_dअगरf, global_node_dअगरf);
#पूर्ण_अगर
	वापस changes;
पूर्ण

/*
 * Fold the data क्रम an offline cpu पूर्णांकo the global array.
 * There cannot be any access by the offline cpu and thereक्रमe
 * synchronization is simplअगरied.
 */
व्योम cpu_vm_stats_fold(पूर्णांक cpu)
अणु
	काष्ठा pglist_data *pgdat;
	काष्ठा zone *zone;
	पूर्णांक i;
	पूर्णांक global_zone_dअगरf[NR_VM_ZONE_STAT_ITEMS] = अणु 0, पूर्ण;
#अगर_घोषित CONFIG_NUMA
	पूर्णांक global_numa_dअगरf[NR_VM_NUMA_STAT_ITEMS] = अणु 0, पूर्ण;
#पूर्ण_अगर
	पूर्णांक global_node_dअगरf[NR_VM_NODE_STAT_ITEMS] = अणु 0, पूर्ण;

	क्रम_each_populated_zone(zone) अणु
		काष्ठा per_cpu_pageset *p;

		p = per_cpu_ptr(zone->pageset, cpu);

		क्रम (i = 0; i < NR_VM_ZONE_STAT_ITEMS; i++)
			अगर (p->vm_stat_dअगरf[i]) अणु
				पूर्णांक v;

				v = p->vm_stat_dअगरf[i];
				p->vm_stat_dअगरf[i] = 0;
				atomic_दीर्घ_add(v, &zone->vm_stat[i]);
				global_zone_dअगरf[i] += v;
			पूर्ण

#अगर_घोषित CONFIG_NUMA
		क्रम (i = 0; i < NR_VM_NUMA_STAT_ITEMS; i++)
			अगर (p->vm_numa_stat_dअगरf[i]) अणु
				पूर्णांक v;

				v = p->vm_numa_stat_dअगरf[i];
				p->vm_numa_stat_dअगरf[i] = 0;
				atomic_दीर्घ_add(v, &zone->vm_numa_stat[i]);
				global_numa_dअगरf[i] += v;
			पूर्ण
#पूर्ण_अगर
	पूर्ण

	क्रम_each_online_pgdat(pgdat) अणु
		काष्ठा per_cpu_nodestat *p;

		p = per_cpu_ptr(pgdat->per_cpu_nodestats, cpu);

		क्रम (i = 0; i < NR_VM_NODE_STAT_ITEMS; i++)
			अगर (p->vm_node_stat_dअगरf[i]) अणु
				पूर्णांक v;

				v = p->vm_node_stat_dअगरf[i];
				p->vm_node_stat_dअगरf[i] = 0;
				atomic_दीर्घ_add(v, &pgdat->vm_stat[i]);
				global_node_dअगरf[i] += v;
			पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_NUMA
	fold_dअगरf(global_zone_dअगरf, global_numa_dअगरf, global_node_dअगरf);
#अन्यथा
	fold_dअगरf(global_zone_dअगरf, global_node_dअगरf);
#पूर्ण_अगर
पूर्ण

/*
 * this is only called अगर !populated_zone(zone), which implies no other users of
 * pset->vm_stat_dअगरf[] exist.
 */
व्योम drain_zonestat(काष्ठा zone *zone, काष्ठा per_cpu_pageset *pset)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_VM_ZONE_STAT_ITEMS; i++)
		अगर (pset->vm_stat_dअगरf[i]) अणु
			पूर्णांक v = pset->vm_stat_dअगरf[i];
			pset->vm_stat_dअगरf[i] = 0;
			atomic_दीर्घ_add(v, &zone->vm_stat[i]);
			atomic_दीर्घ_add(v, &vm_zone_stat[i]);
		पूर्ण

#अगर_घोषित CONFIG_NUMA
	क्रम (i = 0; i < NR_VM_NUMA_STAT_ITEMS; i++)
		अगर (pset->vm_numa_stat_dअगरf[i]) अणु
			पूर्णांक v = pset->vm_numa_stat_dअगरf[i];

			pset->vm_numa_stat_dअगरf[i] = 0;
			atomic_दीर्घ_add(v, &zone->vm_numa_stat[i]);
			atomic_दीर्घ_add(v, &vm_numa_stat[i]);
		पूर्ण
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NUMA
व्योम __inc_numa_state(काष्ठा zone *zone,
				 क्रमागत numa_stat_item item)
अणु
	काष्ठा per_cpu_pageset __percpu *pcp = zone->pageset;
	u16 __percpu *p = pcp->vm_numa_stat_dअगरf + item;
	u16 v;

	v = __this_cpu_inc_वापस(*p);

	अगर (unlikely(v > NUMA_STATS_THRESHOLD)) अणु
		zone_numa_state_add(v, zone, item);
		__this_cpu_ग_लिखो(*p, 0);
	पूर्ण
पूर्ण

/*
 * Determine the per node value of a stat item. This function
 * is called frequently in a NUMA machine, so try to be as
 * frugal as possible.
 */
अचिन्हित दीर्घ sum_zone_node_page_state(पूर्णांक node,
				 क्रमागत zone_stat_item item)
अणु
	काष्ठा zone *zones = NODE_DATA(node)->node_zones;
	पूर्णांक i;
	अचिन्हित दीर्घ count = 0;

	क्रम (i = 0; i < MAX_NR_ZONES; i++)
		count += zone_page_state(zones + i, item);

	वापस count;
पूर्ण

/*
 * Determine the per node value of a numa stat item. To aव्योम deviation,
 * the per cpu stat number in vm_numa_stat_dअगरf[] is also included.
 */
अचिन्हित दीर्घ sum_zone_numa_state(पूर्णांक node,
				 क्रमागत numa_stat_item item)
अणु
	काष्ठा zone *zones = NODE_DATA(node)->node_zones;
	पूर्णांक i;
	अचिन्हित दीर्घ count = 0;

	क्रम (i = 0; i < MAX_NR_ZONES; i++)
		count += zone_numa_state_snapshot(zones + i, item);

	वापस count;
पूर्ण

/*
 * Determine the per node value of a stat item.
 */
अचिन्हित दीर्घ node_page_state_pages(काष्ठा pglist_data *pgdat,
				    क्रमागत node_stat_item item)
अणु
	दीर्घ x = atomic_दीर्घ_पढ़ो(&pgdat->vm_stat[item]);
#अगर_घोषित CONFIG_SMP
	अगर (x < 0)
		x = 0;
#पूर्ण_अगर
	वापस x;
पूर्ण

अचिन्हित दीर्घ node_page_state(काष्ठा pglist_data *pgdat,
			      क्रमागत node_stat_item item)
अणु
	VM_WARN_ON_ONCE(vmstat_item_in_bytes(item));

	वापस node_page_state_pages(pgdat, item);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPACTION

काष्ठा contig_page_info अणु
	अचिन्हित दीर्घ मुक्त_pages;
	अचिन्हित दीर्घ मुक्त_blocks_total;
	अचिन्हित दीर्घ मुक्त_blocks_suitable;
पूर्ण;

/*
 * Calculate the number of मुक्त pages in a zone, how many contiguous
 * pages are मुक्त and how many are large enough to satisfy an allocation of
 * the target size. Note that this function makes no attempt to estimate
 * how many suitable मुक्त blocks there *might* be अगर MOVABLE pages were
 * migrated. Calculating that is possible, but expensive and can be
 * figured out from userspace
 */
अटल व्योम fill_contig_page_info(काष्ठा zone *zone,
				अचिन्हित पूर्णांक suitable_order,
				काष्ठा contig_page_info *info)
अणु
	अचिन्हित पूर्णांक order;

	info->मुक्त_pages = 0;
	info->मुक्त_blocks_total = 0;
	info->मुक्त_blocks_suitable = 0;

	क्रम (order = 0; order < MAX_ORDER; order++) अणु
		अचिन्हित दीर्घ blocks;

		/* Count number of मुक्त blocks */
		blocks = zone->मुक्त_area[order].nr_मुक्त;
		info->मुक्त_blocks_total += blocks;

		/* Count मुक्त base pages */
		info->मुक्त_pages += blocks << order;

		/* Count the suitable मुक्त blocks */
		अगर (order >= suitable_order)
			info->मुक्त_blocks_suitable += blocks <<
						(order - suitable_order);
	पूर्ण
पूर्ण

/*
 * A fragmentation index only makes sense अगर an allocation of a requested
 * size would fail. If that is true, the fragmentation index indicates
 * whether बाह्यal fragmentation or a lack of memory was the problem.
 * The value can be used to determine अगर page reclaim or compaction
 * should be used
 */
अटल पूर्णांक __fragmentation_index(अचिन्हित पूर्णांक order, काष्ठा contig_page_info *info)
अणु
	अचिन्हित दीर्घ requested = 1UL << order;

	अगर (WARN_ON_ONCE(order >= MAX_ORDER))
		वापस 0;

	अगर (!info->मुक्त_blocks_total)
		वापस 0;

	/* Fragmentation index only makes sense when a request would fail */
	अगर (info->मुक्त_blocks_suitable)
		वापस -1000;

	/*
	 * Index is between 0 and 1 so वापस within 3 decimal places
	 *
	 * 0 => allocation would fail due to lack of memory
	 * 1 => allocation would fail due to fragmentation
	 */
	वापस 1000 - भाग_u64( (1000+(भाग_u64(info->मुक्त_pages * 1000ULL, requested))), info->मुक्त_blocks_total);
पूर्ण

/*
 * Calculates बाह्यal fragmentation within a zone wrt the given order.
 * It is defined as the percentage of pages found in blocks of size
 * less than 1 << order. It वापसs values in range [0, 100].
 */
अचिन्हित पूर्णांक extfrag_क्रम_order(काष्ठा zone *zone, अचिन्हित पूर्णांक order)
अणु
	काष्ठा contig_page_info info;

	fill_contig_page_info(zone, order, &info);
	अगर (info.मुक्त_pages == 0)
		वापस 0;

	वापस भाग_u64((info.मुक्त_pages -
			(info.मुक्त_blocks_suitable << order)) * 100,
			info.मुक्त_pages);
पूर्ण

/* Same as __fragmentation index but allocs contig_page_info on stack */
पूर्णांक fragmentation_index(काष्ठा zone *zone, अचिन्हित पूर्णांक order)
अणु
	काष्ठा contig_page_info info;

	fill_contig_page_info(zone, order, &info);
	वापस __fragmentation_index(order, &info);
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PROC_FS) || defined(CONFIG_SYSFS) || \
    defined(CONFIG_NUMA) || defined(CONFIG_MEMCG)
#अगर_घोषित CONFIG_ZONE_DMA
#घोषणा TEXT_FOR_DMA(xx) xx "_dma",
#अन्यथा
#घोषणा TEXT_FOR_DMA(xx)
#पूर्ण_अगर

#अगर_घोषित CONFIG_ZONE_DMA32
#घोषणा TEXT_FOR_DMA32(xx) xx "_dma32",
#अन्यथा
#घोषणा TEXT_FOR_DMA32(xx)
#पूर्ण_अगर

#अगर_घोषित CONFIG_HIGHMEM
#घोषणा TEXT_FOR_HIGHMEM(xx) xx "_high",
#अन्यथा
#घोषणा TEXT_FOR_HIGHMEM(xx)
#पूर्ण_अगर

#घोषणा TEXTS_FOR_ZONES(xx) TEXT_FOR_DMA(xx) TEXT_FOR_DMA32(xx) xx "_normal", \
					TEXT_FOR_HIGHMEM(xx) xx "_movable",

स्थिर अक्षर * स्थिर vmstat_text[] = अणु
	/* क्रमागत zone_stat_item counters */
	"nr_free_pages",
	"nr_zone_inactive_anon",
	"nr_zone_active_anon",
	"nr_zone_inactive_file",
	"nr_zone_active_file",
	"nr_zone_unevictable",
	"nr_zone_write_pending",
	"nr_mlock",
	"nr_bounce",
#अगर IS_ENABLED(CONFIG_ZSMALLOC)
	"nr_zspages",
#पूर्ण_अगर
	"nr_free_cma",

	/* क्रमागत numa_stat_item counters */
#अगर_घोषित CONFIG_NUMA
	"numa_hit",
	"numa_miss",
	"numa_foreign",
	"numa_interleave",
	"numa_local",
	"numa_other",
#पूर्ण_अगर

	/* क्रमागत node_stat_item counters */
	"nr_inactive_anon",
	"nr_active_anon",
	"nr_inactive_file",
	"nr_active_file",
	"nr_unevictable",
	"nr_slab_reclaimable",
	"nr_slab_unreclaimable",
	"nr_isolated_anon",
	"nr_isolated_file",
	"workingset_nodes",
	"workingset_refault_anon",
	"workingset_refault_file",
	"workingset_activate_anon",
	"workingset_activate_file",
	"workingset_restore_anon",
	"workingset_restore_file",
	"workingset_nodereclaim",
	"nr_anon_pages",
	"nr_mapped",
	"nr_file_pages",
	"nr_dirty",
	"nr_writeback",
	"nr_writeback_temp",
	"nr_shmem",
	"nr_shmem_hugepages",
	"nr_shmem_pmdmapped",
	"nr_file_hugepages",
	"nr_file_pmdmapped",
	"nr_anon_transparent_hugepages",
	"nr_vmscan_write",
	"nr_vmscan_immediate_reclaim",
	"nr_dirtied",
	"nr_written",
	"nr_kernel_misc_reclaimable",
	"nr_foll_pin_acquired",
	"nr_foll_pin_released",
	"nr_kernel_stack",
#अगर IS_ENABLED(CONFIG_SHADOW_CALL_STACK)
	"nr_shadow_call_stack",
#पूर्ण_अगर
	"nr_page_table_pages",
#अगर_घोषित CONFIG_SWAP
	"nr_swapcached",
#पूर्ण_अगर

	/* क्रमागत ग_लिखोback_stat_item counters */
	"nr_dirty_threshold",
	"nr_dirty_background_threshold",

#अगर defined(CONFIG_VM_EVENT_COUNTERS) || defined(CONFIG_MEMCG)
	/* क्रमागत vm_event_item counters */
	"pgpgin",
	"pgpgout",
	"pswpin",
	"pswpout",

	TEXTS_FOR_ZONES("pgalloc")
	TEXTS_FOR_ZONES("allocstall")
	TEXTS_FOR_ZONES("pgskip")

	"pgfree",
	"pgactivate",
	"pgdeactivate",
	"pglazyfree",

	"pgfault",
	"pgmajfault",
	"pglazyfreed",

	"pgrefill",
	"pgreuse",
	"pgsteal_kswapd",
	"pgsteal_direct",
	"pgscan_kswapd",
	"pgscan_direct",
	"pgscan_direct_throttle",
	"pgscan_anon",
	"pgscan_file",
	"pgsteal_anon",
	"pgsteal_file",

#अगर_घोषित CONFIG_NUMA
	"zone_reclaim_failed",
#पूर्ण_अगर
	"pginodesteal",
	"slabs_scanned",
	"kswapd_inodesteal",
	"kswapd_low_wmark_hit_quickly",
	"kswapd_high_wmark_hit_quickly",
	"pageoutrun",

	"pgrotated",

	"drop_pagecache",
	"drop_slab",
	"oom_kill",

#अगर_घोषित CONFIG_NUMA_BALANCING
	"numa_pte_updates",
	"numa_huge_pte_updates",
	"numa_hint_faults",
	"numa_hint_faults_local",
	"numa_pages_migrated",
#पूर्ण_अगर
#अगर_घोषित CONFIG_MIGRATION
	"pgmigrate_success",
	"pgmigrate_fail",
	"thp_migration_success",
	"thp_migration_fail",
	"thp_migration_split",
#पूर्ण_अगर
#अगर_घोषित CONFIG_COMPACTION
	"compact_migrate_scanned",
	"compact_free_scanned",
	"compact_isolated",
	"compact_stall",
	"compact_fail",
	"compact_success",
	"compact_daemon_wake",
	"compact_daemon_migrate_scanned",
	"compact_daemon_free_scanned",
#पूर्ण_अगर

#अगर_घोषित CONFIG_HUGETLB_PAGE
	"htlb_buddy_alloc_success",
	"htlb_buddy_alloc_fail",
#पूर्ण_अगर
#अगर_घोषित CONFIG_CMA
	"cma_alloc_success",
	"cma_alloc_fail",
#पूर्ण_अगर
	"unevictable_pgs_culled",
	"unevictable_pgs_scanned",
	"unevictable_pgs_rescued",
	"unevictable_pgs_mlocked",
	"unevictable_pgs_munlocked",
	"unevictable_pgs_cleared",
	"unevictable_pgs_stranded",

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	"thp_fault_alloc",
	"thp_fault_fallback",
	"thp_fault_fallback_charge",
	"thp_collapse_alloc",
	"thp_collapse_alloc_failed",
	"thp_file_alloc",
	"thp_file_fallback",
	"thp_file_fallback_charge",
	"thp_file_mapped",
	"thp_split_page",
	"thp_split_page_failed",
	"thp_deferred_split_page",
	"thp_split_pmd",
#अगर_घोषित CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD
	"thp_split_pud",
#पूर्ण_अगर
	"thp_zero_page_alloc",
	"thp_zero_page_alloc_failed",
	"thp_swpout",
	"thp_swpout_fallback",
#पूर्ण_अगर
#अगर_घोषित CONFIG_MEMORY_BALLOON
	"balloon_inflate",
	"balloon_deflate",
#अगर_घोषित CONFIG_BALLOON_COMPACTION
	"balloon_migrate",
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_MEMORY_BALLOON */
#अगर_घोषित CONFIG_DEBUG_TLBFLUSH
	"nr_tlb_remote_flush",
	"nr_tlb_remote_flush_received",
	"nr_tlb_local_flush_all",
	"nr_tlb_local_flush_one",
#पूर्ण_अगर /* CONFIG_DEBUG_TLBFLUSH */

#अगर_घोषित CONFIG_DEBUG_VM_VMACACHE
	"vmacache_find_calls",
	"vmacache_find_hits",
#पूर्ण_अगर
#अगर_घोषित CONFIG_SWAP
	"swap_ra",
	"swap_ra_hit",
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86
	"direct_map_level2_splits",
	"direct_map_level3_splits",
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_VM_EVENT_COUNTERS || CONFIG_MEMCG */
पूर्ण;
#पूर्ण_अगर /* CONFIG_PROC_FS || CONFIG_SYSFS || CONFIG_NUMA || CONFIG_MEMCG */

#अगर (defined(CONFIG_DEBUG_FS) && defined(CONFIG_COMPACTION)) || \
     defined(CONFIG_PROC_FS)
अटल व्योम *frag_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	pg_data_t *pgdat;
	loff_t node = *pos;

	क्रम (pgdat = first_online_pgdat();
	     pgdat && node;
	     pgdat = next_online_pgdat(pgdat))
		--node;

	वापस pgdat;
पूर्ण

अटल व्योम *frag_next(काष्ठा seq_file *m, व्योम *arg, loff_t *pos)
अणु
	pg_data_t *pgdat = (pg_data_t *)arg;

	(*pos)++;
	वापस next_online_pgdat(pgdat);
पूर्ण

अटल व्योम frag_stop(काष्ठा seq_file *m, व्योम *arg)
अणु
पूर्ण

/*
 * Walk zones in a node and prपूर्णांक using a callback.
 * If @निश्चित_populated is true, only use callback क्रम zones that are populated.
 */
अटल व्योम walk_zones_in_node(काष्ठा seq_file *m, pg_data_t *pgdat,
		bool निश्चित_populated, bool nolock,
		व्योम (*prपूर्णांक)(काष्ठा seq_file *m, pg_data_t *, काष्ठा zone *))
अणु
	काष्ठा zone *zone;
	काष्ठा zone *node_zones = pgdat->node_zones;
	अचिन्हित दीर्घ flags;

	क्रम (zone = node_zones; zone - node_zones < MAX_NR_ZONES; ++zone) अणु
		अगर (निश्चित_populated && !populated_zone(zone))
			जारी;

		अगर (!nolock)
			spin_lock_irqsave(&zone->lock, flags);
		prपूर्णांक(m, pgdat, zone);
		अगर (!nolock)
			spin_unlock_irqrestore(&zone->lock, flags);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम frag_show_prपूर्णांक(काष्ठा seq_file *m, pg_data_t *pgdat,
						काष्ठा zone *zone)
अणु
	पूर्णांक order;

	seq_म_लिखो(m, "Node %d, zone %8s ", pgdat->node_id, zone->name);
	क्रम (order = 0; order < MAX_ORDER; ++order)
		seq_म_लिखो(m, "%6lu ", zone->मुक्त_area[order].nr_मुक्त);
	seq_अ_दो(m, '\n');
पूर्ण

/*
 * This walks the मुक्त areas क्रम each zone.
 */
अटल पूर्णांक frag_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	pg_data_t *pgdat = (pg_data_t *)arg;
	walk_zones_in_node(m, pgdat, true, false, frag_show_prपूर्णांक);
	वापस 0;
पूर्ण

अटल व्योम pagetypeinfo_showमुक्त_prपूर्णांक(काष्ठा seq_file *m,
					pg_data_t *pgdat, काष्ठा zone *zone)
अणु
	पूर्णांक order, mtype;

	क्रम (mtype = 0; mtype < MIGRATE_TYPES; mtype++) अणु
		seq_म_लिखो(m, "Node %4d, zone %8s, type %12s ",
					pgdat->node_id,
					zone->name,
					migratetype_names[mtype]);
		क्रम (order = 0; order < MAX_ORDER; ++order) अणु
			अचिन्हित दीर्घ मुक्तcount = 0;
			काष्ठा मुक्त_area *area;
			काष्ठा list_head *curr;
			bool overflow = false;

			area = &(zone->मुक्त_area[order]);

			list_क्रम_each(curr, &area->मुक्त_list[mtype]) अणु
				/*
				 * Cap the मुक्त_list iteration because it might
				 * be really large and we are under a spinlock
				 * so a दीर्घ समय spent here could trigger a
				 * hard lockup detector. Anyway this is a
				 * debugging tool so knowing there is a handful
				 * of pages of this order should be more than
				 * sufficient.
				 */
				अगर (++मुक्तcount >= 100000) अणु
					overflow = true;
					अवरोध;
				पूर्ण
			पूर्ण
			seq_म_लिखो(m, "%s%6lu ", overflow ? ">" : "", मुक्तcount);
			spin_unlock_irq(&zone->lock);
			cond_resched();
			spin_lock_irq(&zone->lock);
		पूर्ण
		seq_अ_दो(m, '\n');
	पूर्ण
पूर्ण

/* Prपूर्णांक out the मुक्त pages at each order क्रम each migatetype */
अटल पूर्णांक pagetypeinfo_showमुक्त(काष्ठा seq_file *m, व्योम *arg)
अणु
	पूर्णांक order;
	pg_data_t *pgdat = (pg_data_t *)arg;

	/* Prपूर्णांक header */
	seq_म_लिखो(m, "%-43s ", "Free pages count per migrate type at order");
	क्रम (order = 0; order < MAX_ORDER; ++order)
		seq_म_लिखो(m, "%6d ", order);
	seq_अ_दो(m, '\n');

	walk_zones_in_node(m, pgdat, true, false, pagetypeinfo_showमुक्त_prपूर्णांक);

	वापस 0;
पूर्ण

अटल व्योम pagetypeinfo_showblockcount_prपूर्णांक(काष्ठा seq_file *m,
					pg_data_t *pgdat, काष्ठा zone *zone)
अणु
	पूर्णांक mtype;
	अचिन्हित दीर्घ pfn;
	अचिन्हित दीर्घ start_pfn = zone->zone_start_pfn;
	अचिन्हित दीर्घ end_pfn = zone_end_pfn(zone);
	अचिन्हित दीर्घ count[MIGRATE_TYPES] = अणु 0, पूर्ण;

	क्रम (pfn = start_pfn; pfn < end_pfn; pfn += pageblock_nr_pages) अणु
		काष्ठा page *page;

		page = pfn_to_online_page(pfn);
		अगर (!page)
			जारी;

		अगर (page_zone(page) != zone)
			जारी;

		mtype = get_pageblock_migratetype(page);

		अगर (mtype < MIGRATE_TYPES)
			count[mtype]++;
	पूर्ण

	/* Prपूर्णांक counts */
	seq_म_लिखो(m, "Node %d, zone %8s ", pgdat->node_id, zone->name);
	क्रम (mtype = 0; mtype < MIGRATE_TYPES; mtype++)
		seq_म_लिखो(m, "%12lu ", count[mtype]);
	seq_अ_दो(m, '\n');
पूर्ण

/* Prपूर्णांक out the number of pageblocks क्रम each migratetype */
अटल पूर्णांक pagetypeinfo_showblockcount(काष्ठा seq_file *m, व्योम *arg)
अणु
	पूर्णांक mtype;
	pg_data_t *pgdat = (pg_data_t *)arg;

	seq_म_लिखो(m, "\n%-23s", "Number of blocks type ");
	क्रम (mtype = 0; mtype < MIGRATE_TYPES; mtype++)
		seq_म_लिखो(m, "%12s ", migratetype_names[mtype]);
	seq_अ_दो(m, '\n');
	walk_zones_in_node(m, pgdat, true, false,
		pagetypeinfo_showblockcount_prपूर्णांक);

	वापस 0;
पूर्ण

/*
 * Prपूर्णांक out the number of pageblocks क्रम each migratetype that contain pages
 * of other types. This gives an indication of how well fallbacks are being
 * contained by rmqueue_fallback(). It requires inक्रमmation from PAGE_OWNER
 * to determine what is going on
 */
अटल व्योम pagetypeinfo_showmixedcount(काष्ठा seq_file *m, pg_data_t *pgdat)
अणु
#अगर_घोषित CONFIG_PAGE_OWNER
	पूर्णांक mtype;

	अगर (!अटल_branch_unlikely(&page_owner_inited))
		वापस;

	drain_all_pages(शून्य);

	seq_म_लिखो(m, "\n%-23s", "Number of mixed blocks ");
	क्रम (mtype = 0; mtype < MIGRATE_TYPES; mtype++)
		seq_म_लिखो(m, "%12s ", migratetype_names[mtype]);
	seq_अ_दो(m, '\n');

	walk_zones_in_node(m, pgdat, true, true,
		pagetypeinfo_showmixedcount_prपूर्णांक);
#पूर्ण_अगर /* CONFIG_PAGE_OWNER */
पूर्ण

/*
 * This prपूर्णांकs out statistics in relation to grouping pages by mobility.
 * It is expensive to collect so करो not स्थिरantly पढ़ो the file.
 */
अटल पूर्णांक pagetypeinfo_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	pg_data_t *pgdat = (pg_data_t *)arg;

	/* check memoryless node */
	अगर (!node_state(pgdat->node_id, N_MEMORY))
		वापस 0;

	seq_म_लिखो(m, "Page block order: %d\n", pageblock_order);
	seq_म_लिखो(m, "Pages per block:  %lu\n", pageblock_nr_pages);
	seq_अ_दो(m, '\n');
	pagetypeinfo_showमुक्त(m, pgdat);
	pagetypeinfo_showblockcount(m, pgdat);
	pagetypeinfo_showmixedcount(m, pgdat);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations fragmentation_op = अणु
	.start	= frag_start,
	.next	= frag_next,
	.stop	= frag_stop,
	.show	= frag_show,
पूर्ण;

अटल स्थिर काष्ठा seq_operations pagetypeinfo_op = अणु
	.start	= frag_start,
	.next	= frag_next,
	.stop	= frag_stop,
	.show	= pagetypeinfo_show,
पूर्ण;

अटल bool is_zone_first_populated(pg_data_t *pgdat, काष्ठा zone *zone)
अणु
	पूर्णांक zid;

	क्रम (zid = 0; zid < MAX_NR_ZONES; zid++) अणु
		काष्ठा zone *compare = &pgdat->node_zones[zid];

		अगर (populated_zone(compare))
			वापस zone == compare;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम zoneinfo_show_prपूर्णांक(काष्ठा seq_file *m, pg_data_t *pgdat,
							काष्ठा zone *zone)
अणु
	पूर्णांक i;
	seq_म_लिखो(m, "Node %d, zone %8s", pgdat->node_id, zone->name);
	अगर (is_zone_first_populated(pgdat, zone)) अणु
		seq_म_लिखो(m, "\n  per-node stats");
		क्रम (i = 0; i < NR_VM_NODE_STAT_ITEMS; i++) अणु
			अचिन्हित दीर्घ pages = node_page_state_pages(pgdat, i);

			अगर (vmstat_item_prपूर्णांक_in_thp(i))
				pages /= HPAGE_PMD_NR;
			seq_म_लिखो(m, "\n      %-12s %lu", node_stat_name(i),
				   pages);
		पूर्ण
	पूर्ण
	seq_म_लिखो(m,
		   "\n  pages free     %lu"
		   "\n        min      %lu"
		   "\n        low      %lu"
		   "\n        high     %lu"
		   "\n        spanned  %lu"
		   "\n        present  %lu"
		   "\n        managed  %lu"
		   "\n        cma      %lu",
		   zone_page_state(zone, NR_FREE_PAGES),
		   min_wmark_pages(zone),
		   low_wmark_pages(zone),
		   high_wmark_pages(zone),
		   zone->spanned_pages,
		   zone->present_pages,
		   zone_managed_pages(zone),
		   zone_cma_pages(zone));

	seq_म_लिखो(m,
		   "\n        protection: (%ld",
		   zone->lowmem_reserve[0]);
	क्रम (i = 1; i < ARRAY_SIZE(zone->lowmem_reserve); i++)
		seq_म_लिखो(m, ", %ld", zone->lowmem_reserve[i]);
	seq_अ_दो(m, ')');

	/* If unpopulated, no other inक्रमmation is useful */
	अगर (!populated_zone(zone)) अणु
		seq_अ_दो(m, '\n');
		वापस;
	पूर्ण

	क्रम (i = 0; i < NR_VM_ZONE_STAT_ITEMS; i++)
		seq_म_लिखो(m, "\n      %-12s %lu", zone_stat_name(i),
			   zone_page_state(zone, i));

#अगर_घोषित CONFIG_NUMA
	क्रम (i = 0; i < NR_VM_NUMA_STAT_ITEMS; i++)
		seq_म_लिखो(m, "\n      %-12s %lu", numa_stat_name(i),
			   zone_numa_state_snapshot(zone, i));
#पूर्ण_अगर

	seq_म_लिखो(m, "\n  pagesets");
	क्रम_each_online_cpu(i) अणु
		काष्ठा per_cpu_pageset *pageset;

		pageset = per_cpu_ptr(zone->pageset, i);
		seq_म_लिखो(m,
			   "\n    cpu: %i"
			   "\n              count: %i"
			   "\n              high:  %i"
			   "\n              batch: %i",
			   i,
			   pageset->pcp.count,
			   pageset->pcp.high,
			   pageset->pcp.batch);
#अगर_घोषित CONFIG_SMP
		seq_म_लिखो(m, "\n  vm stats threshold: %d",
				pageset->stat_threshold);
#पूर्ण_अगर
	पूर्ण
	seq_म_लिखो(m,
		   "\n  node_unreclaimable:  %u"
		   "\n  start_pfn:           %lu",
		   pgdat->kswapd_failures >= MAX_RECLAIM_RETRIES,
		   zone->zone_start_pfn);
	seq_अ_दो(m, '\n');
पूर्ण

/*
 * Output inक्रमmation about zones in @pgdat.  All zones are prपूर्णांकed regardless
 * of whether they are populated or not: lowmem_reserve_ratio operates on the
 * set of all zones and userspace would not be aware of such zones अगर they are
 * suppressed here (zoneinfo displays the effect of lowmem_reserve_ratio).
 */
अटल पूर्णांक zoneinfo_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	pg_data_t *pgdat = (pg_data_t *)arg;
	walk_zones_in_node(m, pgdat, false, false, zoneinfo_show_prपूर्णांक);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations zoneinfo_op = अणु
	.start	= frag_start, /* iterate over all zones. The same as in
			       * fragmentation. */
	.next	= frag_next,
	.stop	= frag_stop,
	.show	= zoneinfo_show,
पूर्ण;

#घोषणा NR_VMSTAT_ITEMS (NR_VM_ZONE_STAT_ITEMS + \
			 NR_VM_NUMA_STAT_ITEMS + \
			 NR_VM_NODE_STAT_ITEMS + \
			 NR_VM_WRITEBACK_STAT_ITEMS + \
			 (IS_ENABLED(CONFIG_VM_EVENT_COUNTERS) ? \
			  NR_VM_EVENT_ITEMS : 0))

अटल व्योम *vmstat_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	अचिन्हित दीर्घ *v;
	पूर्णांक i;

	अगर (*pos >= NR_VMSTAT_ITEMS)
		वापस शून्य;

	BUILD_BUG_ON(ARRAY_SIZE(vmstat_text) < NR_VMSTAT_ITEMS);
	v = kदो_स्मृति_array(NR_VMSTAT_ITEMS, माप(अचिन्हित दीर्घ), GFP_KERNEL);
	m->निजी = v;
	अगर (!v)
		वापस ERR_PTR(-ENOMEM);
	क्रम (i = 0; i < NR_VM_ZONE_STAT_ITEMS; i++)
		v[i] = global_zone_page_state(i);
	v += NR_VM_ZONE_STAT_ITEMS;

#अगर_घोषित CONFIG_NUMA
	क्रम (i = 0; i < NR_VM_NUMA_STAT_ITEMS; i++)
		v[i] = global_numa_state(i);
	v += NR_VM_NUMA_STAT_ITEMS;
#पूर्ण_अगर

	क्रम (i = 0; i < NR_VM_NODE_STAT_ITEMS; i++) अणु
		v[i] = global_node_page_state_pages(i);
		अगर (vmstat_item_prपूर्णांक_in_thp(i))
			v[i] /= HPAGE_PMD_NR;
	पूर्ण
	v += NR_VM_NODE_STAT_ITEMS;

	global_dirty_limits(v + NR_सूचीTY_BG_THRESHOLD,
			    v + NR_सूचीTY_THRESHOLD);
	v += NR_VM_WRITEBACK_STAT_ITEMS;

#अगर_घोषित CONFIG_VM_EVENT_COUNTERS
	all_vm_events(v);
	v[PGPGIN] /= 2;		/* sectors -> kbytes */
	v[PGPGOUT] /= 2;
#पूर्ण_अगर
	वापस (अचिन्हित दीर्घ *)m->निजी + *pos;
पूर्ण

अटल व्योम *vmstat_next(काष्ठा seq_file *m, व्योम *arg, loff_t *pos)
अणु
	(*pos)++;
	अगर (*pos >= NR_VMSTAT_ITEMS)
		वापस शून्य;
	वापस (अचिन्हित दीर्घ *)m->निजी + *pos;
पूर्ण

अटल पूर्णांक vmstat_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	अचिन्हित दीर्घ *l = arg;
	अचिन्हित दीर्घ off = l - (अचिन्हित दीर्घ *)m->निजी;

	seq_माला_दो(m, vmstat_text[off]);
	seq_put_decimal_ull(m, " ", *l);
	seq_अ_दो(m, '\n');

	अगर (off == NR_VMSTAT_ITEMS - 1) अणु
		/*
		 * We've come to the end - add any deprecated counters to aव्योम
		 * अवरोधing userspace which might depend on them being present.
		 */
		seq_माला_दो(m, "nr_unstable 0\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम vmstat_stop(काष्ठा seq_file *m, व्योम *arg)
अणु
	kमुक्त(m->निजी);
	m->निजी = शून्य;
पूर्ण

अटल स्थिर काष्ठा seq_operations vmstat_op = अणु
	.start	= vmstat_start,
	.next	= vmstat_next,
	.stop	= vmstat_stop,
	.show	= vmstat_show,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PROC_FS */

#अगर_घोषित CONFIG_SMP
अटल DEFINE_PER_CPU(काष्ठा delayed_work, vmstat_work);
पूर्णांक sysctl_stat_पूर्णांकerval __पढ़ो_mostly = HZ;

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम refresh_vm_stats(काष्ठा work_काष्ठा *work)
अणु
	refresh_cpu_vm_stats(true);
पूर्ण

पूर्णांक vmstat_refresh(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	दीर्घ val;
	पूर्णांक err;
	पूर्णांक i;

	/*
	 * The regular update, every sysctl_stat_पूर्णांकerval, may come later
	 * than expected: leaving a signअगरicant amount in per_cpu buckets.
	 * This is particularly misleading when checking a quantity of HUGE
	 * pages, immediately after running a test.  /proc/sys/vm/stat_refresh,
	 * which can equally be echo'ed to or cat'ted from (by root),
	 * can be used to update the stats just beक्रमe पढ़ोing them.
	 *
	 * Oh, and since global_zone_page_state() etc. are so careful to hide
	 * transiently negative values, report an error here अगर any of
	 * the stats is negative, so we know to go looking क्रम imbalance.
	 */
	err = schedule_on_each_cpu(refresh_vm_stats);
	अगर (err)
		वापस err;
	क्रम (i = 0; i < NR_VM_ZONE_STAT_ITEMS; i++) अणु
		/*
		 * Skip checking stats known to go negative occasionally.
		 */
		चयन (i) अणु
		हाल NR_ZONE_WRITE_PENDING:
		हाल NR_FREE_CMA_PAGES:
			जारी;
		पूर्ण
		val = atomic_दीर्घ_पढ़ो(&vm_zone_stat[i]);
		अगर (val < 0) अणु
			pr_warn("%s: %s %ld\n",
				__func__, zone_stat_name(i), val);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < NR_VM_NODE_STAT_ITEMS; i++) अणु
		/*
		 * Skip checking stats known to go negative occasionally.
		 */
		चयन (i) अणु
		हाल NR_WRITEBACK:
			जारी;
		पूर्ण
		val = atomic_दीर्घ_पढ़ो(&vm_node_stat[i]);
		अगर (val < 0) अणु
			pr_warn("%s: %s %ld\n",
				__func__, node_stat_name(i), val);
		पूर्ण
	पूर्ण
	अगर (ग_लिखो)
		*ppos += *lenp;
	अन्यथा
		*lenp = 0;
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल व्योम vmstat_update(काष्ठा work_काष्ठा *w)
अणु
	अगर (refresh_cpu_vm_stats(true)) अणु
		/*
		 * Counters were updated so we expect more updates
		 * to occur in the future. Keep on running the
		 * update worker thपढ़ो.
		 */
		queue_delayed_work_on(smp_processor_id(), mm_percpu_wq,
				this_cpu_ptr(&vmstat_work),
				round_jअगरfies_relative(sysctl_stat_पूर्णांकerval));
	पूर्ण
पूर्ण

/*
 * Switch off vmstat processing and then fold all the reमुख्यing dअगरferentials
 * until the dअगरfs stay at zero. The function is used by NOHZ and can only be
 * invoked when tick processing is not active.
 */
/*
 * Check अगर the dअगरfs क्रम a certain cpu indicate that
 * an update is needed.
 */
अटल bool need_update(पूर्णांक cpu)
अणु
	pg_data_t *last_pgdat = शून्य;
	काष्ठा zone *zone;

	क्रम_each_populated_zone(zone) अणु
		काष्ठा per_cpu_pageset *p = per_cpu_ptr(zone->pageset, cpu);
		काष्ठा per_cpu_nodestat *n;
		/*
		 * The fast way of checking अगर there are any vmstat dअगरfs.
		 */
		अगर (स_प्रथम_inv(p->vm_stat_dअगरf, 0, NR_VM_ZONE_STAT_ITEMS *
			       माप(p->vm_stat_dअगरf[0])))
			वापस true;
#अगर_घोषित CONFIG_NUMA
		अगर (स_प्रथम_inv(p->vm_numa_stat_dअगरf, 0, NR_VM_NUMA_STAT_ITEMS *
			       माप(p->vm_numa_stat_dअगरf[0])))
			वापस true;
#पूर्ण_अगर
		अगर (last_pgdat == zone->zone_pgdat)
			जारी;
		last_pgdat = zone->zone_pgdat;
		n = per_cpu_ptr(zone->zone_pgdat->per_cpu_nodestats, cpu);
		अगर (स_प्रथम_inv(n->vm_node_stat_dअगरf, 0, NR_VM_NODE_STAT_ITEMS *
			       माप(n->vm_node_stat_dअगरf[0])))
		    वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Switch off vmstat processing and then fold all the reमुख्यing dअगरferentials
 * until the dअगरfs stay at zero. The function is used by NOHZ and can only be
 * invoked when tick processing is not active.
 */
व्योम quiet_vmstat(व्योम)
अणु
	अगर (प्रणाली_state != SYSTEM_RUNNING)
		वापस;

	अगर (!delayed_work_pending(this_cpu_ptr(&vmstat_work)))
		वापस;

	अगर (!need_update(smp_processor_id()))
		वापस;

	/*
	 * Just refresh counters and करो not care about the pending delayed
	 * vmstat_update. It करोesn't fire that often to matter and canceling
	 * it would be too expensive from this path.
	 * vmstat_shepherd will take care about that क्रम us.
	 */
	refresh_cpu_vm_stats(false);
पूर्ण

/*
 * Shepherd worker thपढ़ो that checks the
 * dअगरferentials of processors that have their worker
 * thपढ़ोs क्रम vm statistics updates disabled because of
 * inactivity.
 */
अटल व्योम vmstat_shepherd(काष्ठा work_काष्ठा *w);

अटल DECLARE_DEFERRABLE_WORK(shepherd, vmstat_shepherd);

अटल व्योम vmstat_shepherd(काष्ठा work_काष्ठा *w)
अणु
	पूर्णांक cpu;

	get_online_cpus();
	/* Check processors whose vmstat worker thपढ़ोs have been disabled */
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा delayed_work *dw = &per_cpu(vmstat_work, cpu);

		अगर (!delayed_work_pending(dw) && need_update(cpu))
			queue_delayed_work_on(cpu, mm_percpu_wq, dw, 0);

		cond_resched();
	पूर्ण
	put_online_cpus();

	schedule_delayed_work(&shepherd,
		round_jअगरfies_relative(sysctl_stat_पूर्णांकerval));
पूर्ण

अटल व्योम __init start_shepherd_समयr(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		INIT_DEFERRABLE_WORK(per_cpu_ptr(&vmstat_work, cpu),
			vmstat_update);

	schedule_delayed_work(&shepherd,
		round_jअगरfies_relative(sysctl_stat_पूर्णांकerval));
पूर्ण

अटल व्योम __init init_cpu_node_state(व्योम)
अणु
	पूर्णांक node;

	क्रम_each_online_node(node) अणु
		अगर (cpumask_weight(cpumask_of_node(node)) > 0)
			node_set_state(node, N_CPU);
	पूर्ण
पूर्ण

अटल पूर्णांक vmstat_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	refresh_zone_stat_thresholds();
	node_set_state(cpu_to_node(cpu), N_CPU);
	वापस 0;
पूर्ण

अटल पूर्णांक vmstat_cpu_करोwn_prep(अचिन्हित पूर्णांक cpu)
अणु
	cancel_delayed_work_sync(&per_cpu(vmstat_work, cpu));
	वापस 0;
पूर्ण

अटल पूर्णांक vmstat_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	स्थिर काष्ठा cpumask *node_cpus;
	पूर्णांक node;

	node = cpu_to_node(cpu);

	refresh_zone_stat_thresholds();
	node_cpus = cpumask_of_node(node);
	अगर (cpumask_weight(node_cpus) > 0)
		वापस 0;

	node_clear_state(node, N_CPU);
	वापस 0;
पूर्ण

#पूर्ण_अगर

काष्ठा workqueue_काष्ठा *mm_percpu_wq;

व्योम __init init_mm_पूर्णांकernals(व्योम)
अणु
	पूर्णांक ret __maybe_unused;

	mm_percpu_wq = alloc_workqueue("mm_percpu_wq", WQ_MEM_RECLAIM, 0);

#अगर_घोषित CONFIG_SMP
	ret = cpuhp_setup_state_nocalls(CPUHP_MM_VMSTAT_DEAD, "mm/vmstat:dead",
					शून्य, vmstat_cpu_dead);
	अगर (ret < 0)
		pr_err("vmstat: failed to register 'dead' hotplug state\n");

	ret = cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN, "mm/vmstat:online",
					vmstat_cpu_online,
					vmstat_cpu_करोwn_prep);
	अगर (ret < 0)
		pr_err("vmstat: failed to register 'online' hotplug state\n");

	get_online_cpus();
	init_cpu_node_state();
	put_online_cpus();

	start_shepherd_समयr();
#पूर्ण_अगर
#अगर_घोषित CONFIG_PROC_FS
	proc_create_seq("buddyinfo", 0444, शून्य, &fragmentation_op);
	proc_create_seq("pagetypeinfo", 0400, शून्य, &pagetypeinfo_op);
	proc_create_seq("vmstat", 0444, शून्य, &vmstat_op);
	proc_create_seq("zoneinfo", 0444, शून्य, &zoneinfo_op);
#पूर्ण_अगर
पूर्ण

#अगर defined(CONFIG_DEBUG_FS) && defined(CONFIG_COMPACTION)

/*
 * Return an index indicating how much of the available मुक्त memory is
 * unusable क्रम an allocation of the requested size.
 */
अटल पूर्णांक unusable_मुक्त_index(अचिन्हित पूर्णांक order,
				काष्ठा contig_page_info *info)
अणु
	/* No मुक्त memory is पूर्णांकerpreted as all मुक्त memory is unusable */
	अगर (info->मुक्त_pages == 0)
		वापस 1000;

	/*
	 * Index should be a value between 0 and 1. Return a value to 3
	 * decimal places.
	 *
	 * 0 => no fragmentation
	 * 1 => high fragmentation
	 */
	वापस भाग_u64((info->मुक्त_pages - (info->मुक्त_blocks_suitable << order)) * 1000ULL, info->मुक्त_pages);

पूर्ण

अटल व्योम unusable_show_prपूर्णांक(काष्ठा seq_file *m,
					pg_data_t *pgdat, काष्ठा zone *zone)
अणु
	अचिन्हित पूर्णांक order;
	पूर्णांक index;
	काष्ठा contig_page_info info;

	seq_म_लिखो(m, "Node %d, zone %8s ",
				pgdat->node_id,
				zone->name);
	क्रम (order = 0; order < MAX_ORDER; ++order) अणु
		fill_contig_page_info(zone, order, &info);
		index = unusable_मुक्त_index(order, &info);
		seq_म_लिखो(m, "%d.%03d ", index / 1000, index % 1000);
	पूर्ण

	seq_अ_दो(m, '\n');
पूर्ण

/*
 * Display unusable मुक्त space index
 *
 * The unusable मुक्त space index measures how much of the available मुक्त
 * memory cannot be used to satisfy an allocation of a given size and is a
 * value between 0 and 1. The higher the value, the more of मुक्त memory is
 * unusable and by implication, the worse the बाह्यal fragmentation is. This
 * can be expressed as a percentage by multiplying by 100.
 */
अटल पूर्णांक unusable_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	pg_data_t *pgdat = (pg_data_t *)arg;

	/* check memoryless node */
	अगर (!node_state(pgdat->node_id, N_MEMORY))
		वापस 0;

	walk_zones_in_node(m, pgdat, true, false, unusable_show_prपूर्णांक);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations unusable_sops = अणु
	.start	= frag_start,
	.next	= frag_next,
	.stop	= frag_stop,
	.show	= unusable_show,
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(unusable);

अटल व्योम extfrag_show_prपूर्णांक(काष्ठा seq_file *m,
					pg_data_t *pgdat, काष्ठा zone *zone)
अणु
	अचिन्हित पूर्णांक order;
	पूर्णांक index;

	/* Alloc on stack as पूर्णांकerrupts are disabled क्रम zone walk */
	काष्ठा contig_page_info info;

	seq_म_लिखो(m, "Node %d, zone %8s ",
				pgdat->node_id,
				zone->name);
	क्रम (order = 0; order < MAX_ORDER; ++order) अणु
		fill_contig_page_info(zone, order, &info);
		index = __fragmentation_index(order, &info);
		seq_म_लिखो(m, "%d.%03d ", index / 1000, index % 1000);
	पूर्ण

	seq_अ_दो(m, '\n');
पूर्ण

/*
 * Display fragmentation index क्रम orders that allocations would fail क्रम
 */
अटल पूर्णांक extfrag_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	pg_data_t *pgdat = (pg_data_t *)arg;

	walk_zones_in_node(m, pgdat, true, false, extfrag_show_prपूर्णांक);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations extfrag_sops = अणु
	.start	= frag_start,
	.next	= frag_next,
	.stop	= frag_stop,
	.show	= extfrag_show,
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(extfrag);

अटल पूर्णांक __init extfrag_debug_init(व्योम)
अणु
	काष्ठा dentry *extfrag_debug_root;

	extfrag_debug_root = debugfs_create_dir("extfrag", शून्य);

	debugfs_create_file("unusable_index", 0444, extfrag_debug_root, शून्य,
			    &unusable_fops);

	debugfs_create_file("extfrag_index", 0444, extfrag_debug_root, शून्य,
			    &extfrag_fops);

	वापस 0;
पूर्ण

module_init(extfrag_debug_init);
#पूर्ण_अगर
