<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Perक्रमmance counter support क्रम e6500 family processors.
 *
 * Author: Priyanka Jain, Priyanka.Jain@मुक्तscale.com
 * Based on e500-pmu.c
 * Copyright 2013 Freescale Semiconductor, Inc.
 * Copyright 2008-2009 Paul Mackerras, IBM Corporation.
 */

#समावेश <linux/माला.स>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/cputable.h>

/*
 * Map of generic hardware event types to hardware events
 * Zero अगर unsupported
 */
अटल पूर्णांक e6500_generic_events[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] = 1,
	[PERF_COUNT_HW_INSTRUCTIONS] = 2,
	[PERF_COUNT_HW_CACHE_MISSES] = 221,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = 12,
	[PERF_COUNT_HW_BRANCH_MISSES] = 15,
पूर्ण;

#घोषणा C(x)	PERF_COUNT_HW_CACHE_##x

/*
 * Table of generalized cache-related events.
 * 0 means not supported, -1 means nonsensical, other values
 * are event codes.
 */
अटल पूर्णांक e6500_cache_events[C(MAX)][C(OP_MAX)][C(RESULT_MAX)] = अणु
	[C(L1D)] = अणु
				/*RESULT_ACCESS		RESULT_MISS */
		[C(OP_READ)] = अणु	27,		222	पूर्ण,
		[C(OP_WRITE)] = अणु	28,		223	पूर्ण,
		[C(OP_PREFETCH)] = अणु	29,		0	पूर्ण,
	पूर्ण,
	[C(L1I)] = अणु
				/*RESULT_ACCESS		RESULT_MISS */
		[C(OP_READ)] = अणु	2,		254	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	37,		0	पूर्ण,
	पूर्ण,
	/*
	 * Assuming LL means L2, it's not a good match क्रम this model.
	 * It करोes not have separate पढ़ो/ग_लिखो events (but it करोes have
	 * separate inकाष्ठाion/data events).
	 */
	[C(LL)] = अणु
				/*RESULT_ACCESS		RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0	पूर्ण,
		[C(OP_WRITE)] = अणु	0,		0	पूर्ण,
		[C(OP_PREFETCH)] = अणु	0,		0	पूर्ण,
	पूर्ण,
	/*
	 * There are data/inकाष्ठाion MMU misses, but that's a miss on
	 * the chip's पूर्णांकernal level-one TLB which is probably not
	 * what the user wants.  Instead, unअगरied level-two TLB misses
	 * are reported here.
	 */
	[C(DTLB)] = अणु
				/*RESULT_ACCESS		RESULT_MISS */
		[C(OP_READ)] = अणु	26,		66	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1	पूर्ण,
	पूर्ण,
	[C(BPU)] = अणु
				/*RESULT_ACCESS		RESULT_MISS */
		[C(OP_READ)] = अणु	12,		15	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1	पूर्ण,
	पूर्ण,
	[C(NODE)] = अणु
				/* RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	-1,		-1	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1	पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक num_events = 512;

/* Upper half of event id is PMLCb, क्रम threshold events */
अटल u64 e6500_xlate_event(u64 event_id)
अणु
	u32 event_low = (u32)event_id;
	अगर (event_low >= num_events ||
		(event_id & (FSL_EMB_EVENT_THRESHMUL | FSL_EMB_EVENT_THRESH)))
		वापस 0;

	वापस FSL_EMB_EVENT_VALID;
पूर्ण

अटल काष्ठा fsl_emb_pmu e6500_pmu = अणु
	.name			= "e6500 family",
	.n_counter		= 6,
	.n_restricted		= 0,
	.xlate_event		= e6500_xlate_event,
	.n_generic		= ARRAY_SIZE(e6500_generic_events),
	.generic_events		= e6500_generic_events,
	.cache_events		= &e6500_cache_events,
पूर्ण;

अटल पूर्णांक init_e6500_pmu(व्योम)
अणु
	अगर (!cur_cpu_spec->oprofile_cpu_type ||
		म_भेद(cur_cpu_spec->oprofile_cpu_type, "ppc/e6500"))
		वापस -ENODEV;

	वापस रेजिस्टर_fsl_emb_pmu(&e6500_pmu);
पूर्ण

early_initcall(init_e6500_pmu);
