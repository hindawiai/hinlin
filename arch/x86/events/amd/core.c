<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/perf_event.h>
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <यंत्र/apicdef.h>
#समावेश <यंत्र/nmi.h>

#समावेश "../perf_event.h"

अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, perf_nmi_tstamp);
अटल अचिन्हित दीर्घ perf_nmi_winकरोw;

/* AMD Event 0xFFF: Merge.  Used with Large Increment per Cycle events */
#घोषणा AMD_MERGE_EVENT ((0xFULL << 32) | 0xFFULL)
#घोषणा AMD_MERGE_EVENT_ENABLE (AMD_MERGE_EVENT | ARCH_PERFMON_EVENTSEL_ENABLE)

अटल __initस्थिर स्थिर u64 amd_hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(L1D) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0040, /* Data Cache Accesses        */
		[ C(RESULT_MISS)   ] = 0x0141, /* Data Cache Misses          */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0267, /* Data Prefetcher :attempts  */
		[ C(RESULT_MISS)   ] = 0x0167, /* Data Prefetcher :cancelled */
	पूर्ण,
 पूर्ण,
 [ C(L1I ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0080, /* Inकाष्ठाion cache fetches  */
		[ C(RESULT_MISS)   ] = 0x0081, /* Inकाष्ठाion cache misses   */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x014B, /* Prefetch Inकाष्ठाions :Load */
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
 पूर्ण,
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x037D, /* Requests to L2 Cache :IC+DC */
		[ C(RESULT_MISS)   ] = 0x037E, /* L2 Cache Misses : IC+DC     */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x017F, /* L2 Fill/Writeback           */
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
 पूर्ण,
 [ C(DTLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0040, /* Data Cache Accesses        */
		[ C(RESULT_MISS)   ] = 0x0746, /* L1_DTLB_AND_L2_DLTB_MISS.ALL */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
 पूर्ण,
 [ C(ITLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0080, /* Inकाष्ठाion fecthes        */
		[ C(RESULT_MISS)   ] = 0x0385, /* L1_ITLB_AND_L2_ITLB_MISS.ALL */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(BPU ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x00c2, /* Retired Branch Instr.      */
		[ C(RESULT_MISS)   ] = 0x00c3, /* Retired Mispredicted BI    */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(NODE) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0xb8e9, /* CPU Request to Memory, l+r */
		[ C(RESULT_MISS)   ] = 0x98e9, /* CPU Request to Memory, r   */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
पूर्ण;

अटल __initस्थिर स्थिर u64 amd_hw_cache_event_ids_f17h
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
[C(L1D)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0x0040, /* Data Cache Accesses */
		[C(RESULT_MISS)]   = 0xc860, /* L2$ access from DC Miss */
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = 0,
		[C(RESULT_MISS)]   = 0,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = 0xff5a, /* h/w prefetch DC Fills */
		[C(RESULT_MISS)]   = 0,
	पूर्ण,
पूर्ण,
[C(L1I)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0x0080, /* Inकाष्ठाion cache fetches  */
		[C(RESULT_MISS)]   = 0x0081, /* Inकाष्ठाion cache misses   */
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)]   = -1,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = 0,
		[C(RESULT_MISS)]   = 0,
	पूर्ण,
पूर्ण,
[C(LL)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0,
		[C(RESULT_MISS)]   = 0,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = 0,
		[C(RESULT_MISS)]   = 0,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = 0,
		[C(RESULT_MISS)]   = 0,
	पूर्ण,
पूर्ण,
[C(DTLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0xff45, /* All L2 DTLB accesses */
		[C(RESULT_MISS)]   = 0xf045, /* L2 DTLB misses (PT walks) */
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = 0,
		[C(RESULT_MISS)]   = 0,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = 0,
		[C(RESULT_MISS)]   = 0,
	पूर्ण,
पूर्ण,
[C(ITLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0x0084, /* L1 ITLB misses, L2 ITLB hits */
		[C(RESULT_MISS)]   = 0xff85, /* L1 ITLB misses, L2 misses */
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)]   = -1,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)]   = -1,
	पूर्ण,
पूर्ण,
[C(BPU)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0x00c2, /* Retired Branch Instr.      */
		[C(RESULT_MISS)]   = 0x00c3, /* Retired Mispredicted BI    */
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)]   = -1,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)]   = -1,
	पूर्ण,
पूर्ण,
[C(NODE)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = 0,
		[C(RESULT_MISS)]   = 0,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)]   = -1,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = -1,
		[C(RESULT_MISS)]   = -1,
	पूर्ण,
पूर्ण,
पूर्ण;

/*
 * AMD Perक्रमmance Monitor K7 and later, up to and including Family 16h:
 */
अटल स्थिर u64 amd_perfmon_event_map[PERF_COUNT_HW_MAX] =
अणु
	[PERF_COUNT_HW_CPU_CYCLES]		= 0x0076,
	[PERF_COUNT_HW_INSTRUCTIONS]		= 0x00c0,
	[PERF_COUNT_HW_CACHE_REFERENCES]	= 0x077d,
	[PERF_COUNT_HW_CACHE_MISSES]		= 0x077e,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= 0x00c2,
	[PERF_COUNT_HW_BRANCH_MISSES]		= 0x00c3,
	[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND]	= 0x00d0, /* "Decoder empty" event */
	[PERF_COUNT_HW_STALLED_CYCLES_BACKEND]	= 0x00d1, /* "Dispatch stalls" event */
पूर्ण;

/*
 * AMD Perक्रमmance Monitor Family 17h and later:
 */
अटल स्थिर u64 amd_f17h_perfmon_event_map[PERF_COUNT_HW_MAX] =
अणु
	[PERF_COUNT_HW_CPU_CYCLES]		= 0x0076,
	[PERF_COUNT_HW_INSTRUCTIONS]		= 0x00c0,
	[PERF_COUNT_HW_CACHE_REFERENCES]	= 0xff60,
	[PERF_COUNT_HW_CACHE_MISSES]		= 0x0964,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= 0x00c2,
	[PERF_COUNT_HW_BRANCH_MISSES]		= 0x00c3,
	[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND]	= 0x0287,
	[PERF_COUNT_HW_STALLED_CYCLES_BACKEND]	= 0x0187,
पूर्ण;

अटल u64 amd_pmu_event_map(पूर्णांक hw_event)
अणु
	अगर (boot_cpu_data.x86 >= 0x17)
		वापस amd_f17h_perfmon_event_map[hw_event];

	वापस amd_perfmon_event_map[hw_event];
पूर्ण

/*
 * Previously calculated offsets
 */
अटल अचिन्हित पूर्णांक event_offsets[X86_PMC_IDX_MAX] __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक count_offsets[X86_PMC_IDX_MAX] __पढ़ो_mostly;

/*
 * Legacy CPUs:
 *   4 counters starting at 0xc0010000 each offset by 1
 *
 * CPUs with core perक्रमmance counter extensions:
 *   6 counters starting at 0xc0010200 each offset by 2
 */
अटल अंतरभूत पूर्णांक amd_pmu_addr_offset(पूर्णांक index, bool eventsel)
अणु
	पूर्णांक offset;

	अगर (!index)
		वापस index;

	अगर (eventsel)
		offset = event_offsets[index];
	अन्यथा
		offset = count_offsets[index];

	अगर (offset)
		वापस offset;

	अगर (!boot_cpu_has(X86_FEATURE_PERFCTR_CORE))
		offset = index;
	अन्यथा
		offset = index << 1;

	अगर (eventsel)
		event_offsets[index] = offset;
	अन्यथा
		count_offsets[index] = offset;

	वापस offset;
पूर्ण

/*
 * AMD64 events are detected based on their event codes.
 */
अटल अंतरभूत अचिन्हित पूर्णांक amd_get_event_code(काष्ठा hw_perf_event *hwc)
अणु
	वापस ((hwc->config >> 24) & 0x0f00) | (hwc->config & 0x00ff);
पूर्ण

अटल अंतरभूत bool amd_is_pair_event_code(काष्ठा hw_perf_event *hwc)
अणु
	अगर (!(x86_pmu.flags & PMU_FL_PAIR))
		वापस false;

	चयन (amd_get_event_code(hwc)) अणु
	हाल 0x003:	वापस true;	/* Retired SSE/AVX FLOPs */
	शेष:	वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक amd_core_hw_config(काष्ठा perf_event *event)
अणु
	अगर (event->attr.exclude_host && event->attr.exclude_guest)
		/*
		 * When HO == GO == 1 the hardware treats that as GO == HO == 0
		 * and will count in both modes. We करोn't want to count in that
		 * हाल so we emulate no-counting by setting US = OS = 0.
		 */
		event->hw.config &= ~(ARCH_PERFMON_EVENTSEL_USR |
				      ARCH_PERFMON_EVENTSEL_OS);
	अन्यथा अगर (event->attr.exclude_host)
		event->hw.config |= AMD64_EVENTSEL_GUESTONLY;
	अन्यथा अगर (event->attr.exclude_guest)
		event->hw.config |= AMD64_EVENTSEL_HOSTONLY;

	अगर ((x86_pmu.flags & PMU_FL_PAIR) && amd_is_pair_event_code(&event->hw))
		event->hw.flags |= PERF_X86_EVENT_PAIR;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक amd_is_nb_event(काष्ठा hw_perf_event *hwc)
अणु
	वापस (hwc->config & 0xe0) == 0xe0;
पूर्ण

अटल अंतरभूत पूर्णांक amd_has_nb(काष्ठा cpu_hw_events *cpuc)
अणु
	काष्ठा amd_nb *nb = cpuc->amd_nb;

	वापस nb && nb->nb_id != -1;
पूर्ण

अटल पूर्णांक amd_pmu_hw_config(काष्ठा perf_event *event)
अणु
	पूर्णांक ret;

	/* pass precise event sampling to ibs: */
	अगर (event->attr.precise_ip && get_ibs_caps())
		वापस -ENOENT;

	अगर (has_branch_stack(event))
		वापस -EOPNOTSUPP;

	ret = x86_pmu_hw_config(event);
	अगर (ret)
		वापस ret;

	अगर (event->attr.type == PERF_TYPE_RAW)
		event->hw.config |= event->attr.config & AMD64_RAW_EVENT_MASK;

	वापस amd_core_hw_config(event);
पूर्ण

अटल व्योम __amd_put_nb_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc,
					   काष्ठा perf_event *event)
अणु
	काष्ठा amd_nb *nb = cpuc->amd_nb;
	पूर्णांक i;

	/*
	 * need to scan whole list because event may not have
	 * been asचिन्हित during scheduling
	 *
	 * no race condition possible because event can only
	 * be हटाओd on one CPU at a समय AND PMU is disabled
	 * when we come here
	 */
	क्रम (i = 0; i < x86_pmu.num_counters; i++) अणु
		अगर (cmpxchg(nb->owners + i, event, शून्य) == event)
			अवरोध;
	पूर्ण
पूर्ण

 /*
  * AMD64 NorthBridge events need special treaपंचांगent because
  * counter access needs to be synchronized across all cores
  * of a package. Refer to BKDG section 3.12
  *
  * NB events are events measuring L3 cache, Hypertransport
  * traffic. They are identअगरied by an event code >= 0xe00.
  * They measure events on the NorthBride which is shared
  * by all cores on a package. NB events are counted on a
  * shared set of counters. When a NB event is programmed
  * in a counter, the data actually comes from a shared
  * counter. Thus, access to those counters needs to be
  * synchronized.
  *
  * We implement the synchronization such that no two cores
  * can be measuring NB events using the same counters. Thus,
  * we मुख्यtain a per-NB allocation table. The available slot
  * is propagated using the event_स्थिरraपूर्णांक काष्ठाure.
  *
  * We provide only one choice क्रम each NB event based on
  * the fact that only NB events have restrictions. Consequently,
  * अगर a counter is available, there is a guarantee the NB event
  * will be asचिन्हित to it. If no slot is available, an empty
  * स्थिरraपूर्णांक is वापसed and scheduling will eventually fail
  * क्रम this event.
  *
  * Note that all cores attached the same NB compete क्रम the same
  * counters to host NB events, this is why we use atomic ops. Some
  * multi-chip CPUs may have more than one NB.
  *
  * Given that resources are allocated (cmpxchg), they must be
  * eventually मुक्तd क्रम others to use. This is accomplished by
  * calling __amd_put_nb_event_स्थिरraपूर्णांकs()
  *
  * Non NB events are not impacted by this restriction.
  */
अटल काष्ठा event_स्थिरraपूर्णांक *
__amd_get_nb_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc, काष्ठा perf_event *event,
			       काष्ठा event_स्थिरraपूर्णांक *c)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा amd_nb *nb = cpuc->amd_nb;
	काष्ठा perf_event *old;
	पूर्णांक idx, new = -1;

	अगर (!c)
		c = &unस्थिरrained;

	अगर (cpuc->is_fake)
		वापस c;

	/*
	 * detect अगर alपढ़ोy present, अगर so reuse
	 *
	 * cannot merge with actual allocation
	 * because of possible holes
	 *
	 * event can alपढ़ोy be present yet not asचिन्हित (in hwc->idx)
	 * because of successive calls to x86_schedule_events() from
	 * hw_perf_group_sched_in() without hw_perf_enable()
	 */
	क्रम_each_set_bit(idx, c->idxmsk, x86_pmu.num_counters) अणु
		अगर (new == -1 || hwc->idx == idx)
			/* assign मुक्त slot, prefer hwc->idx */
			old = cmpxchg(nb->owners + idx, शून्य, event);
		अन्यथा अगर (nb->owners[idx] == event)
			/* event alपढ़ोy present */
			old = event;
		अन्यथा
			जारी;

		अगर (old && old != event)
			जारी;

		/* reassign to this slot */
		अगर (new != -1)
			cmpxchg(nb->owners + new, event, शून्य);
		new = idx;

		/* alपढ़ोy present, reuse */
		अगर (old == event)
			अवरोध;
	पूर्ण

	अगर (new == -1)
		वापस &emptyस्थिरraपूर्णांक;

	वापस &nb->event_स्थिरraपूर्णांकs[new];
पूर्ण

अटल काष्ठा amd_nb *amd_alloc_nb(पूर्णांक cpu)
अणु
	काष्ठा amd_nb *nb;
	पूर्णांक i;

	nb = kzalloc_node(माप(काष्ठा amd_nb), GFP_KERNEL, cpu_to_node(cpu));
	अगर (!nb)
		वापस शून्य;

	nb->nb_id = -1;

	/*
	 * initialize all possible NB स्थिरraपूर्णांकs
	 */
	क्रम (i = 0; i < x86_pmu.num_counters; i++) अणु
		__set_bit(i, nb->event_स्थिरraपूर्णांकs[i].idxmsk);
		nb->event_स्थिरraपूर्णांकs[i].weight = 1;
	पूर्ण
	वापस nb;
पूर्ण

अटल पूर्णांक amd_pmu_cpu_prepare(पूर्णांक cpu)
अणु
	काष्ठा cpu_hw_events *cpuc = &per_cpu(cpu_hw_events, cpu);

	WARN_ON_ONCE(cpuc->amd_nb);

	अगर (!x86_pmu.amd_nb_स्थिरraपूर्णांकs)
		वापस 0;

	cpuc->amd_nb = amd_alloc_nb(cpu);
	अगर (!cpuc->amd_nb)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम amd_pmu_cpu_starting(पूर्णांक cpu)
अणु
	काष्ठा cpu_hw_events *cpuc = &per_cpu(cpu_hw_events, cpu);
	व्योम **onln = &cpuc->kमुक्त_on_online[X86_PERF_KFREE_SHARED];
	काष्ठा amd_nb *nb;
	पूर्णांक i, nb_id;

	cpuc->perf_ctr_virt_mask = AMD64_EVENTSEL_HOSTONLY;

	अगर (!x86_pmu.amd_nb_स्थिरraपूर्णांकs)
		वापस;

	nb_id = topology_die_id(cpu);
	WARN_ON_ONCE(nb_id == BAD_APICID);

	क्रम_each_online_cpu(i) अणु
		nb = per_cpu(cpu_hw_events, i).amd_nb;
		अगर (WARN_ON_ONCE(!nb))
			जारी;

		अगर (nb->nb_id == nb_id) अणु
			*onln = cpuc->amd_nb;
			cpuc->amd_nb = nb;
			अवरोध;
		पूर्ण
	पूर्ण

	cpuc->amd_nb->nb_id = nb_id;
	cpuc->amd_nb->refcnt++;
पूर्ण

अटल व्योम amd_pmu_cpu_dead(पूर्णांक cpu)
अणु
	काष्ठा cpu_hw_events *cpuhw;

	अगर (!x86_pmu.amd_nb_स्थिरraपूर्णांकs)
		वापस;

	cpuhw = &per_cpu(cpu_hw_events, cpu);

	अगर (cpuhw->amd_nb) अणु
		काष्ठा amd_nb *nb = cpuhw->amd_nb;

		अगर (nb->nb_id == -1 || --nb->refcnt == 0)
			kमुक्त(nb);

		cpuhw->amd_nb = शून्य;
	पूर्ण
पूर्ण

/*
 * When a PMC counter overflows, an NMI is used to process the event and
 * reset the counter. NMI latency can result in the counter being updated
 * beक्रमe the NMI can run, which can result in what appear to be spurious
 * NMIs. This function is पूर्णांकended to रुको क्रम the NMI to run and reset
 * the counter to aव्योम possible unhandled NMI messages.
 */
#घोषणा OVERFLOW_WAIT_COUNT	50

अटल व्योम amd_pmu_रुको_on_overflow(पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक i;
	u64 counter;

	/*
	 * Wait क्रम the counter to be reset अगर it has overflowed. This loop
	 * should निकास very, very quickly, but just in हाल, करोn't रुको
	 * क्रमever...
	 */
	क्रम (i = 0; i < OVERFLOW_WAIT_COUNT; i++) अणु
		rdmsrl(x86_pmu_event_addr(idx), counter);
		अगर (counter & (1ULL << (x86_pmu.cntval_bits - 1)))
			अवरोध;

		/* Might be in IRQ context, so can't sleep */
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम amd_pmu_disable_all(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक idx;

	x86_pmu_disable_all();

	/*
	 * This shouldn't be called from NMI context, but add a safeguard here
	 * to वापस, since अगर we're in NMI context we can't रुको क्रम an NMI
	 * to reset an overflowed counter value.
	 */
	अगर (in_nmi())
		वापस;

	/*
	 * Check each counter क्रम overflow and रुको क्रम it to be reset by the
	 * NMI अगर it has overflowed. This relies on the fact that all active
	 * counters are always enabled when this function is called and
	 * ARCH_PERFMON_EVENTSEL_INT is always set.
	 */
	क्रम (idx = 0; idx < x86_pmu.num_counters; idx++) अणु
		अगर (!test_bit(idx, cpuc->active_mask))
			जारी;

		amd_pmu_रुको_on_overflow(idx);
	पूर्ण
पूर्ण

अटल व्योम amd_pmu_disable_event(काष्ठा perf_event *event)
अणु
	x86_pmu_disable_event(event);

	/*
	 * This can be called from NMI context (via x86_pmu_stop). The counter
	 * may have overflowed, but either way, we'll never see it get reset
	 * by the NMI अगर we're alपढ़ोy in the NMI. And the NMI latency support
	 * below will take care of any pending NMI that might have been
	 * generated by the overflow.
	 */
	अगर (in_nmi())
		वापस;

	amd_pmu_रुको_on_overflow(event->hw.idx);
पूर्ण

/*
 * Because of NMI latency, अगर multiple PMC counters are active or other sources
 * of NMIs are received, the perf NMI handler can handle one or more overflowed
 * PMC counters outside of the NMI associated with the PMC overflow. If the NMI
 * करोesn't arrive at the LAPIC in समय to become a pending NMI, then the kernel
 * back-to-back NMI support won't be active. This PMC handler needs to take पूर्णांकo
 * account that this can occur, otherwise this could result in unknown NMI
 * messages being issued. Examples of this is PMC overflow जबतक in the NMI
 * handler when multiple PMCs are active or PMC overflow जबतक handling some
 * other source of an NMI.
 *
 * Attempt to mitigate this by creating an NMI winकरोw in which un-handled NMIs
 * received during this winकरोw will be claimed. This prevents extending the
 * winकरोw past when it is possible that latent NMIs should be received. The
 * per-CPU perf_nmi_tstamp will be set to the winकरोw end समय whenever perf has
 * handled a counter. When an un-handled NMI is received, it will be claimed
 * only अगर arriving within that winकरोw.
 */
अटल पूर्णांक amd_pmu_handle_irq(काष्ठा pt_regs *regs)
अणु
	पूर्णांक handled;

	/* Process any counter overflows */
	handled = x86_pmu_handle_irq(regs);

	/*
	 * If a counter was handled, record a बारtamp such that un-handled
	 * NMIs will be claimed अगर arriving within that winकरोw.
	 */
	अगर (handled) अणु
		this_cpu_ग_लिखो(perf_nmi_tstamp, jअगरfies + perf_nmi_winकरोw);

		वापस handled;
	पूर्ण

	अगर (समय_after(jअगरfies, this_cpu_पढ़ो(perf_nmi_tstamp)))
		वापस NMI_DONE;

	वापस NMI_HANDLED;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
amd_get_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx,
			  काष्ठा perf_event *event)
अणु
	/*
	 * अगर not NB event or no NB, then no स्थिरraपूर्णांकs
	 */
	अगर (!(amd_has_nb(cpuc) && amd_is_nb_event(&event->hw)))
		वापस &unस्थिरrained;

	वापस __amd_get_nb_event_स्थिरraपूर्णांकs(cpuc, event, शून्य);
पूर्ण

अटल व्योम amd_put_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc,
				      काष्ठा perf_event *event)
अणु
	अगर (amd_has_nb(cpuc) && amd_is_nb_event(&event->hw))
		__amd_put_nb_event_स्थिरraपूर्णांकs(cpuc, event);
पूर्ण

PMU_FORMAT_ATTR(event,	"config:0-7,32-35");
PMU_FORMAT_ATTR(umask,	"config:8-15"	);
PMU_FORMAT_ATTR(edge,	"config:18"	);
PMU_FORMAT_ATTR(inv,	"config:23"	);
PMU_FORMAT_ATTR(cmask,	"config:24-31"	);

अटल काष्ठा attribute *amd_क्रमmat_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_cmask.attr,
	शून्य,
पूर्ण;

/* AMD Family 15h */

#घोषणा AMD_EVENT_TYPE_MASK	0x000000F0ULL

#घोषणा AMD_EVENT_FP		0x00000000ULL ... 0x00000010ULL
#घोषणा AMD_EVENT_LS		0x00000020ULL ... 0x00000030ULL
#घोषणा AMD_EVENT_DC		0x00000040ULL ... 0x00000050ULL
#घोषणा AMD_EVENT_CU		0x00000060ULL ... 0x00000070ULL
#घोषणा AMD_EVENT_IC_DE		0x00000080ULL ... 0x00000090ULL
#घोषणा AMD_EVENT_EX_LS		0x000000C0ULL
#घोषणा AMD_EVENT_DE		0x000000D0ULL
#घोषणा AMD_EVENT_NB		0x000000E0ULL ... 0x000000F0ULL

/*
 * AMD family 15h event code/PMC mappings:
 *
 * type = event_code & 0x0F0:
 *
 * 0x000	FP	PERF_CTL[5:3]
 * 0x010	FP	PERF_CTL[5:3]
 * 0x020	LS	PERF_CTL[5:0]
 * 0x030	LS	PERF_CTL[5:0]
 * 0x040	DC	PERF_CTL[5:0]
 * 0x050	DC	PERF_CTL[5:0]
 * 0x060	CU	PERF_CTL[2:0]
 * 0x070	CU	PERF_CTL[2:0]
 * 0x080	IC/DE	PERF_CTL[2:0]
 * 0x090	IC/DE	PERF_CTL[2:0]
 * 0x0A0	---
 * 0x0B0	---
 * 0x0C0	EX/LS	PERF_CTL[5:0]
 * 0x0D0	DE	PERF_CTL[2:0]
 * 0x0E0	NB	NB_PERF_CTL[3:0]
 * 0x0F0	NB	NB_PERF_CTL[3:0]
 *
 * Exceptions:
 *
 * 0x000	FP	PERF_CTL[3], PERF_CTL[5:3] (*)
 * 0x003	FP	PERF_CTL[3]
 * 0x004	FP	PERF_CTL[3], PERF_CTL[5:3] (*)
 * 0x00B	FP	PERF_CTL[3]
 * 0x00D	FP	PERF_CTL[3]
 * 0x023	DE	PERF_CTL[2:0]
 * 0x02D	LS	PERF_CTL[3]
 * 0x02E	LS	PERF_CTL[3,0]
 * 0x031	LS	PERF_CTL[2:0] (**)
 * 0x043	CU	PERF_CTL[2:0]
 * 0x045	CU	PERF_CTL[2:0]
 * 0x046	CU	PERF_CTL[2:0]
 * 0x054	CU	PERF_CTL[2:0]
 * 0x055	CU	PERF_CTL[2:0]
 * 0x08F	IC	PERF_CTL[0]
 * 0x187	DE	PERF_CTL[0]
 * 0x188	DE	PERF_CTL[0]
 * 0x0DB	EX	PERF_CTL[5:0]
 * 0x0DC	LS	PERF_CTL[5:0]
 * 0x0DD	LS	PERF_CTL[5:0]
 * 0x0DE	LS	PERF_CTL[5:0]
 * 0x0DF	LS	PERF_CTL[5:0]
 * 0x1C0	EX	PERF_CTL[5:3]
 * 0x1D6	EX	PERF_CTL[5:0]
 * 0x1D8	EX	PERF_CTL[5:0]
 *
 * (*)  depending on the umask all FPU counters may be used
 * (**) only one uniपंचांगask enabled at a समय
 */

अटल काष्ठा event_स्थिरraपूर्णांक amd_f15_PMC0  = EVENT_CONSTRAINT(0, 0x01, 0);
अटल काष्ठा event_स्थिरraपूर्णांक amd_f15_PMC20 = EVENT_CONSTRAINT(0, 0x07, 0);
अटल काष्ठा event_स्थिरraपूर्णांक amd_f15_PMC3  = EVENT_CONSTRAINT(0, 0x08, 0);
अटल काष्ठा event_स्थिरraपूर्णांक amd_f15_PMC30 = EVENT_CONSTRAINT_OVERLAP(0, 0x09, 0);
अटल काष्ठा event_स्थिरraपूर्णांक amd_f15_PMC50 = EVENT_CONSTRAINT(0, 0x3F, 0);
अटल काष्ठा event_स्थिरraपूर्णांक amd_f15_PMC53 = EVENT_CONSTRAINT(0, 0x38, 0);

अटल काष्ठा event_स्थिरraपूर्णांक *
amd_get_event_स्थिरraपूर्णांकs_f15h(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx,
			       काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	अचिन्हित पूर्णांक event_code = amd_get_event_code(hwc);

	चयन (event_code & AMD_EVENT_TYPE_MASK) अणु
	हाल AMD_EVENT_FP:
		चयन (event_code) अणु
		हाल 0x000:
			अगर (!(hwc->config & 0x0000F000ULL))
				अवरोध;
			अगर (!(hwc->config & 0x00000F00ULL))
				अवरोध;
			वापस &amd_f15_PMC3;
		हाल 0x004:
			अगर (hweight_दीर्घ(hwc->config & ARCH_PERFMON_EVENTSEL_UMASK) <= 1)
				अवरोध;
			वापस &amd_f15_PMC3;
		हाल 0x003:
		हाल 0x00B:
		हाल 0x00D:
			वापस &amd_f15_PMC3;
		पूर्ण
		वापस &amd_f15_PMC53;
	हाल AMD_EVENT_LS:
	हाल AMD_EVENT_DC:
	हाल AMD_EVENT_EX_LS:
		चयन (event_code) अणु
		हाल 0x023:
		हाल 0x043:
		हाल 0x045:
		हाल 0x046:
		हाल 0x054:
		हाल 0x055:
			वापस &amd_f15_PMC20;
		हाल 0x02D:
			वापस &amd_f15_PMC3;
		हाल 0x02E:
			वापस &amd_f15_PMC30;
		हाल 0x031:
			अगर (hweight_दीर्घ(hwc->config & ARCH_PERFMON_EVENTSEL_UMASK) <= 1)
				वापस &amd_f15_PMC20;
			वापस &emptyस्थिरraपूर्णांक;
		हाल 0x1C0:
			वापस &amd_f15_PMC53;
		शेष:
			वापस &amd_f15_PMC50;
		पूर्ण
	हाल AMD_EVENT_CU:
	हाल AMD_EVENT_IC_DE:
	हाल AMD_EVENT_DE:
		चयन (event_code) अणु
		हाल 0x08F:
		हाल 0x187:
		हाल 0x188:
			वापस &amd_f15_PMC0;
		हाल 0x0DB ... 0x0DF:
		हाल 0x1D6:
		हाल 0x1D8:
			वापस &amd_f15_PMC50;
		शेष:
			वापस &amd_f15_PMC20;
		पूर्ण
	हाल AMD_EVENT_NB:
		/* moved to uncore.c */
		वापस &emptyस्थिरraपूर्णांक;
	शेष:
		वापस &emptyस्थिरraपूर्णांक;
	पूर्ण
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक pair_स्थिरraपूर्णांक;

अटल काष्ठा event_स्थिरraपूर्णांक *
amd_get_event_स्थिरraपूर्णांकs_f17h(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx,
			       काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (amd_is_pair_event_code(hwc))
		वापस &pair_स्थिरraपूर्णांक;

	वापस &unस्थिरrained;
पूर्ण

अटल व्योम amd_put_event_स्थिरraपूर्णांकs_f17h(काष्ठा cpu_hw_events *cpuc,
					   काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (is_counter_pair(hwc))
		--cpuc->n_pair;
पूर्ण

अटल sमाप_प्रकार amd_event_sysfs_show(अक्षर *page, u64 config)
अणु
	u64 event = (config & ARCH_PERFMON_EVENTSEL_EVENT) |
		    (config & AMD64_EVENTSEL_EVENT) >> 24;

	वापस x86_event_sysfs_show(page, config, event);
पूर्ण

अटल __initस्थिर स्थिर काष्ठा x86_pmu amd_pmu = अणु
	.name			= "AMD",
	.handle_irq		= amd_pmu_handle_irq,
	.disable_all		= amd_pmu_disable_all,
	.enable_all		= x86_pmu_enable_all,
	.enable			= x86_pmu_enable_event,
	.disable		= amd_pmu_disable_event,
	.hw_config		= amd_pmu_hw_config,
	.schedule_events	= x86_schedule_events,
	.eventsel		= MSR_K7_EVNTSEL0,
	.perfctr		= MSR_K7_PERFCTR0,
	.addr_offset            = amd_pmu_addr_offset,
	.event_map		= amd_pmu_event_map,
	.max_events		= ARRAY_SIZE(amd_perfmon_event_map),
	.num_counters		= AMD64_NUM_COUNTERS,
	.cntval_bits		= 48,
	.cntval_mask		= (1ULL << 48) - 1,
	.apic			= 1,
	/* use highest bit to detect overflow */
	.max_period		= (1ULL << 47) - 1,
	.get_event_स्थिरraपूर्णांकs	= amd_get_event_स्थिरraपूर्णांकs,
	.put_event_स्थिरraपूर्णांकs	= amd_put_event_स्थिरraपूर्णांकs,

	.क्रमmat_attrs		= amd_क्रमmat_attr,
	.events_sysfs_show	= amd_event_sysfs_show,

	.cpu_prepare		= amd_pmu_cpu_prepare,
	.cpu_starting		= amd_pmu_cpu_starting,
	.cpu_dead		= amd_pmu_cpu_dead,

	.amd_nb_स्थिरraपूर्णांकs	= 1,
पूर्ण;

अटल पूर्णांक __init amd_core_pmu_init(व्योम)
अणु
	u64 even_ctr_mask = 0ULL;
	पूर्णांक i;

	अगर (!boot_cpu_has(X86_FEATURE_PERFCTR_CORE))
		वापस 0;

	/* Aव्योम calculating the value each समय in the NMI handler */
	perf_nmi_winकरोw = msecs_to_jअगरfies(100);

	/*
	 * If core perक्रमmance counter extensions exists, we must use
	 * MSR_F15H_PERF_CTL/MSR_F15H_PERF_CTR msrs. See also
	 * amd_pmu_addr_offset().
	 */
	x86_pmu.eventsel	= MSR_F15H_PERF_CTL;
	x86_pmu.perfctr		= MSR_F15H_PERF_CTR;
	x86_pmu.num_counters	= AMD64_NUM_COUNTERS_CORE;
	/*
	 * AMD Core perfctr has separate MSRs क्रम the NB events, see
	 * the amd/uncore.c driver.
	 */
	x86_pmu.amd_nb_स्थिरraपूर्णांकs = 0;

	अगर (boot_cpu_data.x86 == 0x15) अणु
		pr_cont("Fam15h ");
		x86_pmu.get_event_स्थिरraपूर्णांकs = amd_get_event_स्थिरraपूर्णांकs_f15h;
	पूर्ण
	अगर (boot_cpu_data.x86 >= 0x17) अणु
		pr_cont("Fam17h+ ");
		/*
		 * Family 17h and compatibles have स्थिरraपूर्णांकs क्रम Large
		 * Increment per Cycle events: they may only be asचिन्हित an
		 * even numbered counter that has a consecutive adjacent odd
		 * numbered counter following it.
		 */
		क्रम (i = 0; i < x86_pmu.num_counters - 1; i += 2)
			even_ctr_mask |= 1 << i;

		pair_स्थिरraपूर्णांक = (काष्ठा event_स्थिरraपूर्णांक)
				    __EVENT_CONSTRAINT(0, even_ctr_mask, 0,
				    x86_pmu.num_counters / 2, 0,
				    PERF_X86_EVENT_PAIR);

		x86_pmu.get_event_स्थिरraपूर्णांकs = amd_get_event_स्थिरraपूर्णांकs_f17h;
		x86_pmu.put_event_स्थिरraपूर्णांकs = amd_put_event_स्थिरraपूर्णांकs_f17h;
		x86_pmu.perf_ctr_pair_en = AMD_MERGE_EVENT_ENABLE;
		x86_pmu.flags |= PMU_FL_PAIR;
	पूर्ण

	pr_cont("core perfctr, ");
	वापस 0;
पूर्ण

__init पूर्णांक amd_pmu_init(व्योम)
अणु
	पूर्णांक ret;

	/* Perक्रमmance-monitoring supported from K7 and later: */
	अगर (boot_cpu_data.x86 < 6)
		वापस -ENODEV;

	x86_pmu = amd_pmu;

	ret = amd_core_pmu_init();
	अगर (ret)
		वापस ret;

	अगर (num_possible_cpus() == 1) अणु
		/*
		 * No poपूर्णांक in allocating data काष्ठाures to serialize
		 * against other CPUs, when there is only the one CPU.
		 */
		x86_pmu.amd_nb_स्थिरraपूर्णांकs = 0;
	पूर्ण

	अगर (boot_cpu_data.x86 >= 0x17)
		स_नकल(hw_cache_event_ids, amd_hw_cache_event_ids_f17h, माप(hw_cache_event_ids));
	अन्यथा
		स_नकल(hw_cache_event_ids, amd_hw_cache_event_ids, माप(hw_cache_event_ids));

	वापस 0;
पूर्ण

व्योम amd_pmu_enable_virt(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	cpuc->perf_ctr_virt_mask = 0;

	/* Reload all events */
	amd_pmu_disable_all();
	x86_pmu_enable_all(0);
पूर्ण
EXPORT_SYMBOL_GPL(amd_pmu_enable_virt);

व्योम amd_pmu_disable_virt(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	/*
	 * We only mask out the Host-only bit so that host-only counting works
	 * when SVM is disabled. If someone sets up a guest-only counter when
	 * SVM is disabled the Guest-only bits still माला_लो set and the counter
	 * will not count anything.
	 */
	cpuc->perf_ctr_virt_mask = AMD64_EVENTSEL_HOSTONLY;

	/* Reload all events */
	amd_pmu_disable_all();
	x86_pmu_enable_all(0);
पूर्ण
EXPORT_SYMBOL_GPL(amd_pmu_disable_virt);
