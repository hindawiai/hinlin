<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Perक्रमmance event support क्रम sparc64.
 *
 * Copyright (C) 2009, 2010 David S. Miller <davem@davemloft.net>
 *
 * This code is based almost entirely upon the x86 perf event
 * code, which is:
 *
 *  Copyright (C) 2008 Thomas Gleixner <tglx@linutronix.de>
 *  Copyright (C) 2008-2009 Red Hat, Inc., Ingo Molnar
 *  Copyright (C) 2009 Jaswinder Singh Rajput
 *  Copyright (C) 2009 Advanced Micro Devices, Inc., Robert Richter
 *  Copyright (C) 2008-2009 Red Hat, Inc., Peter Zijlstra
 */

#समावेश <linux/perf_event.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/mutex.h>

#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/cpudata.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/pcr.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश "kernel.h"
#समावेश "kstack.h"

/* Two classes of sparc64 chips currently exist.  All of which have
 * 32-bit counters which can generate overflow पूर्णांकerrupts on the
 * transition from 0xffffffff to 0.
 *
 * All chips upto and including SPARC-T3 have two perक्रमmance
 * counters.  The two 32-bit counters are accessed in one go using a
 * single 64-bit रेजिस्टर.
 *
 * On these older chips both counters are controlled using a single
 * control रेजिस्टर.  The only way to stop all sampling is to clear
 * all of the context (user, supervisor, hypervisor) sampling enable
 * bits.  But these bits apply to both counters, thus the two counters
 * can't be enabled/disabled inभागidually.
 *
 * Furthermore, the control रेजिस्टर on these older chips have two
 * event fields, one क्रम each of the two counters.  It's thus nearly
 * impossible to have one counter going जबतक keeping the other one
 * stopped.  Thereक्रमe it is possible to get overflow पूर्णांकerrupts क्रम
 * counters not currently "in use" and that condition must be checked
 * in the overflow पूर्णांकerrupt handler.
 *
 * So we use a hack, in that we program inactive counters with the
 * "sw_count0" and "sw_count1" events.  These count how many बार
 * the inकाष्ठाion "sethi %hi(0xfc000), %g0" is executed.  It's an
 * unusual way to encode a NOP and thereक्रमe will not trigger in
 * normal code.
 *
 * Starting with SPARC-T4 we have one control रेजिस्टर per counter.
 * And the counters are stored in inभागidual रेजिस्टरs.  The रेजिस्टरs
 * क्रम the counters are 64-bit but only a 32-bit counter is
 * implemented.  The event selections on SPARC-T4 lack any
 * restrictions, thereक्रमe we can elide all of the complicated
 * conflict resolution code we have क्रम SPARC-T3 and earlier chips.
 */

#घोषणा MAX_HWEVENTS			4
#घोषणा MAX_PCRS			4
#घोषणा MAX_PERIOD			((1UL << 32) - 1)

#घोषणा PIC_UPPER_INDEX			0
#घोषणा PIC_LOWER_INDEX			1
#घोषणा PIC_NO_INDEX			-1

काष्ठा cpu_hw_events अणु
	/* Number of events currently scheduled onto this cpu.
	 * This tells how many entries in the arrays below
	 * are valid.
	 */
	पूर्णांक			n_events;

	/* Number of new events added since the last hw_perf_disable().
	 * This works because the perf event layer always adds new
	 * events inside of a perf_अणुdisable,enableपूर्ण() sequence.
	 */
	पूर्णांक			n_added;

	/* Array of events current scheduled on this cpu.  */
	काष्ठा perf_event	*event[MAX_HWEVENTS];

	/* Array of encoded दीर्घs, specअगरying the %pcr रेजिस्टर
	 * encoding and the mask of PIC counters this even can
	 * be scheduled on.  See perf_event_encode() et al.
	 */
	अचिन्हित दीर्घ		events[MAX_HWEVENTS];

	/* The current counter index asचिन्हित to an event.  When the
	 * event hasn't been programmed पूर्णांकo the cpu yet, this will
	 * hold PIC_NO_INDEX.  The event->hw.idx value tells us where
	 * we ought to schedule the event.
	 */
	पूर्णांक			current_idx[MAX_HWEVENTS];

	/* Software copy of %pcr रेजिस्टर(s) on this cpu.  */
	u64			pcr[MAX_HWEVENTS];

	/* Enabled/disable state.  */
	पूर्णांक			enabled;

	अचिन्हित पूर्णांक		txn_flags;
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा cpu_hw_events, cpu_hw_events) = अणु .enabled = 1, पूर्ण;

/* An event map describes the अक्षरacteristics of a perक्रमmance
 * counter event.  In particular it gives the encoding as well as
 * a mask telling which counters the event can be measured on.
 *
 * The mask is unused on SPARC-T4 and later.
 */
काष्ठा perf_event_map अणु
	u16	encoding;
	u8	pic_mask;
#घोषणा PIC_NONE	0x00
#घोषणा PIC_UPPER	0x01
#घोषणा PIC_LOWER	0x02
पूर्ण;

/* Encode a perf_event_map entry पूर्णांकo a दीर्घ.  */
अटल अचिन्हित दीर्घ perf_event_encode(स्थिर काष्ठा perf_event_map *pmap)
अणु
	वापस ((अचिन्हित दीर्घ) pmap->encoding << 16) | pmap->pic_mask;
पूर्ण

अटल u8 perf_event_get_msk(अचिन्हित दीर्घ val)
अणु
	वापस val & 0xff;
पूर्ण

अटल u64 perf_event_get_enc(अचिन्हित दीर्घ val)
अणु
	वापस val >> 16;
पूर्ण

#घोषणा C(x) PERF_COUNT_HW_CACHE_##x

#घोषणा CACHE_OP_UNSUPPORTED	0xfffe
#घोषणा CACHE_OP_NONSENSE	0xffff

प्रकार काष्ठा perf_event_map cache_map_t
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX];

काष्ठा sparc_pmu अणु
	स्थिर काष्ठा perf_event_map	*(*event_map)(पूर्णांक);
	स्थिर cache_map_t		*cache_map;
	पूर्णांक				max_events;
	u32				(*पढ़ो_pmc)(पूर्णांक);
	व्योम				(*ग_लिखो_pmc)(पूर्णांक, u64);
	पूर्णांक				upper_shअगरt;
	पूर्णांक				lower_shअगरt;
	पूर्णांक				event_mask;
	पूर्णांक				user_bit;
	पूर्णांक				priv_bit;
	पूर्णांक				hv_bit;
	पूर्णांक				irq_bit;
	पूर्णांक				upper_nop;
	पूर्णांक				lower_nop;
	अचिन्हित पूर्णांक			flags;
#घोषणा SPARC_PMU_ALL_EXCLUDES_SAME	0x00000001
#घोषणा SPARC_PMU_HAS_CONFLICTS		0x00000002
	पूर्णांक				max_hw_events;
	पूर्णांक				num_pcrs;
	पूर्णांक				num_pic_regs;
पूर्ण;

अटल u32 sparc_शेष_पढ़ो_pmc(पूर्णांक idx)
अणु
	u64 val;

	val = pcr_ops->पढ़ो_pic(0);
	अगर (idx == PIC_UPPER_INDEX)
		val >>= 32;

	वापस val & 0xffffffff;
पूर्ण

अटल व्योम sparc_शेष_ग_लिखो_pmc(पूर्णांक idx, u64 val)
अणु
	u64 shअगरt, mask, pic;

	shअगरt = 0;
	अगर (idx == PIC_UPPER_INDEX)
		shअगरt = 32;

	mask = ((u64) 0xffffffff) << shअगरt;
	val <<= shअगरt;

	pic = pcr_ops->पढ़ो_pic(0);
	pic &= ~mask;
	pic |= val;
	pcr_ops->ग_लिखो_pic(0, pic);
पूर्ण

अटल स्थिर काष्ठा perf_event_map ultra3_perfmon_event_map[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] = अणु 0x0000, PIC_UPPER | PIC_LOWER पूर्ण,
	[PERF_COUNT_HW_INSTRUCTIONS] = अणु 0x0001, PIC_UPPER | PIC_LOWER पूर्ण,
	[PERF_COUNT_HW_CACHE_REFERENCES] = अणु 0x0009, PIC_LOWER पूर्ण,
	[PERF_COUNT_HW_CACHE_MISSES] = अणु 0x0009, PIC_UPPER पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा perf_event_map *ultra3_event_map(पूर्णांक event_id)
अणु
	वापस &ultra3_perfmon_event_map[event_id];
पूर्ण

अटल स्थिर cache_map_t ultra3_cache_map = अणु
[C(L1D)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु 0x09, PIC_LOWER, पूर्ण,
		[C(RESULT_MISS)] = अणु 0x09, PIC_UPPER, पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = अणु 0x0a, PIC_LOWER पूर्ण,
		[C(RESULT_MISS)] = अणु 0x0a, PIC_UPPER पूर्ण,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(L1I)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु 0x09, PIC_LOWER, पूर्ण,
		[C(RESULT_MISS)] = अणु 0x09, PIC_UPPER, पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_NONSENSE पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_NONSENSE पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(LL)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु 0x0c, PIC_LOWER, पूर्ण,
		[C(RESULT_MISS)] = अणु 0x0c, PIC_UPPER, पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = अणु 0x0c, PIC_LOWER पूर्ण,
		[C(RESULT_MISS)] = अणु 0x0c, PIC_UPPER पूर्ण,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(DTLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु 0x12, PIC_UPPER, पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(ITLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु 0x11, PIC_UPPER, पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(BPU)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(NODE)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)  ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sparc_pmu ultra3_pmu = अणु
	.event_map	= ultra3_event_map,
	.cache_map	= &ultra3_cache_map,
	.max_events	= ARRAY_SIZE(ultra3_perfmon_event_map),
	.पढ़ो_pmc	= sparc_शेष_पढ़ो_pmc,
	.ग_लिखो_pmc	= sparc_शेष_ग_लिखो_pmc,
	.upper_shअगरt	= 11,
	.lower_shअगरt	= 4,
	.event_mask	= 0x3f,
	.user_bit	= PCR_UTRACE,
	.priv_bit	= PCR_STRACE,
	.upper_nop	= 0x1c,
	.lower_nop	= 0x14,
	.flags		= (SPARC_PMU_ALL_EXCLUDES_SAME |
			   SPARC_PMU_HAS_CONFLICTS),
	.max_hw_events	= 2,
	.num_pcrs	= 1,
	.num_pic_regs	= 1,
पूर्ण;

/* Niagara1 is very limited.  The upper PIC is hard-locked to count
 * only inकाष्ठाions, so it is मुक्त running which creates all kinds of
 * problems.  Some hardware designs make one wonder अगर the creator
 * even looked at how this stuff माला_लो used by software.
 */
अटल स्थिर काष्ठा perf_event_map niagara1_perfmon_event_map[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] = अणु 0x00, PIC_UPPER पूर्ण,
	[PERF_COUNT_HW_INSTRUCTIONS] = अणु 0x00, PIC_UPPER पूर्ण,
	[PERF_COUNT_HW_CACHE_REFERENCES] = अणु 0, PIC_NONE पूर्ण,
	[PERF_COUNT_HW_CACHE_MISSES] = अणु 0x03, PIC_LOWER पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा perf_event_map *niagara1_event_map(पूर्णांक event_id)
अणु
	वापस &niagara1_perfmon_event_map[event_id];
पूर्ण

अटल स्थिर cache_map_t niagara1_cache_map = अणु
[C(L1D)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु 0x03, PIC_LOWER, पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु 0x03, PIC_LOWER, पूर्ण,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(L1I)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु 0x00, PIC_UPPER पूर्ण,
		[C(RESULT_MISS)] = अणु 0x02, PIC_LOWER, पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_NONSENSE पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_NONSENSE पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(LL)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु 0x07, PIC_LOWER, पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु 0x07, PIC_LOWER, पूर्ण,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(DTLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु 0x05, PIC_LOWER, पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(ITLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु 0x04, PIC_LOWER, पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(BPU)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(NODE)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)  ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sparc_pmu niagara1_pmu = अणु
	.event_map	= niagara1_event_map,
	.cache_map	= &niagara1_cache_map,
	.max_events	= ARRAY_SIZE(niagara1_perfmon_event_map),
	.पढ़ो_pmc	= sparc_शेष_पढ़ो_pmc,
	.ग_लिखो_pmc	= sparc_शेष_ग_लिखो_pmc,
	.upper_shअगरt	= 0,
	.lower_shअगरt	= 4,
	.event_mask	= 0x7,
	.user_bit	= PCR_UTRACE,
	.priv_bit	= PCR_STRACE,
	.upper_nop	= 0x0,
	.lower_nop	= 0x0,
	.flags		= (SPARC_PMU_ALL_EXCLUDES_SAME |
			   SPARC_PMU_HAS_CONFLICTS),
	.max_hw_events	= 2,
	.num_pcrs	= 1,
	.num_pic_regs	= 1,
पूर्ण;

अटल स्थिर काष्ठा perf_event_map niagara2_perfmon_event_map[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] = अणु 0x02ff, PIC_UPPER | PIC_LOWER पूर्ण,
	[PERF_COUNT_HW_INSTRUCTIONS] = अणु 0x02ff, PIC_UPPER | PIC_LOWER पूर्ण,
	[PERF_COUNT_HW_CACHE_REFERENCES] = अणु 0x0208, PIC_UPPER | PIC_LOWER पूर्ण,
	[PERF_COUNT_HW_CACHE_MISSES] = अणु 0x0302, PIC_UPPER | PIC_LOWER पूर्ण,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = अणु 0x0201, PIC_UPPER | PIC_LOWER पूर्ण,
	[PERF_COUNT_HW_BRANCH_MISSES] = अणु 0x0202, PIC_UPPER | PIC_LOWER पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा perf_event_map *niagara2_event_map(पूर्णांक event_id)
अणु
	वापस &niagara2_perfmon_event_map[event_id];
पूर्ण

अटल स्थिर cache_map_t niagara2_cache_map = अणु
[C(L1D)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु 0x0208, PIC_UPPER | PIC_LOWER, पूर्ण,
		[C(RESULT_MISS)] = अणु 0x0302, PIC_UPPER | PIC_LOWER, पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = अणु 0x0210, PIC_UPPER | PIC_LOWER, पूर्ण,
		[C(RESULT_MISS)] = अणु 0x0302, PIC_UPPER | PIC_LOWER, पूर्ण,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(L1I)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु 0x02ff, PIC_UPPER | PIC_LOWER, पूर्ण,
		[C(RESULT_MISS)] = अणु 0x0301, PIC_UPPER | PIC_LOWER, पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_NONSENSE पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_NONSENSE पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(LL)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु 0x0208, PIC_UPPER | PIC_LOWER, पूर्ण,
		[C(RESULT_MISS)] = अणु 0x0330, PIC_UPPER | PIC_LOWER, पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = अणु 0x0210, PIC_UPPER | PIC_LOWER, पूर्ण,
		[C(RESULT_MISS)] = अणु 0x0320, PIC_UPPER | PIC_LOWER, पूर्ण,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(DTLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु 0x0b08, PIC_UPPER | PIC_LOWER, पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(ITLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु 0xb04, PIC_UPPER | PIC_LOWER, पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(BPU)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(NODE)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)  ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sparc_pmu niagara2_pmu = अणु
	.event_map	= niagara2_event_map,
	.cache_map	= &niagara2_cache_map,
	.max_events	= ARRAY_SIZE(niagara2_perfmon_event_map),
	.पढ़ो_pmc	= sparc_शेष_पढ़ो_pmc,
	.ग_लिखो_pmc	= sparc_शेष_ग_लिखो_pmc,
	.upper_shअगरt	= 19,
	.lower_shअगरt	= 6,
	.event_mask	= 0xfff,
	.user_bit	= PCR_UTRACE,
	.priv_bit	= PCR_STRACE,
	.hv_bit		= PCR_N2_HTRACE,
	.irq_bit	= 0x30,
	.upper_nop	= 0x220,
	.lower_nop	= 0x220,
	.flags		= (SPARC_PMU_ALL_EXCLUDES_SAME |
			   SPARC_PMU_HAS_CONFLICTS),
	.max_hw_events	= 2,
	.num_pcrs	= 1,
	.num_pic_regs	= 1,
पूर्ण;

अटल स्थिर काष्ठा perf_event_map niagara4_perfmon_event_map[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] = अणु (26 << 6) पूर्ण,
	[PERF_COUNT_HW_INSTRUCTIONS] = अणु (3 << 6) | 0x3f पूर्ण,
	[PERF_COUNT_HW_CACHE_REFERENCES] = अणु (3 << 6) | 0x04 पूर्ण,
	[PERF_COUNT_HW_CACHE_MISSES] = अणु (16 << 6) | 0x07 पूर्ण,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = अणु (4 << 6) | 0x01 पूर्ण,
	[PERF_COUNT_HW_BRANCH_MISSES] = अणु (25 << 6) | 0x0f पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा perf_event_map *niagara4_event_map(पूर्णांक event_id)
अणु
	वापस &niagara4_perfmon_event_map[event_id];
पूर्ण

अटल स्थिर cache_map_t niagara4_cache_map = अणु
[C(L1D)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु (3 << 6) | 0x04 पूर्ण,
		[C(RESULT_MISS)] = अणु (16 << 6) | 0x07 पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = अणु (3 << 6) | 0x08 पूर्ण,
		[C(RESULT_MISS)] = अणु (16 << 6) | 0x07 पूर्ण,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(L1I)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु (3 << 6) | 0x3f पूर्ण,
		[C(RESULT_MISS)] = अणु (11 << 6) | 0x03 पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_NONSENSE पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_NONSENSE पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(LL)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु (3 << 6) | 0x04 पूर्ण,
		[C(RESULT_MISS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)] = अणु (3 << 6) | 0x08 पूर्ण,
		[C(RESULT_MISS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(DTLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु (17 << 6) | 0x3f पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(ITLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु (6 << 6) | 0x3f पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(BPU)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
[C(NODE)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[C(RESULT_MISS)  ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
		[ C(RESULT_MISS)   ] = अणु CACHE_OP_UNSUPPORTED पूर्ण,
	पूर्ण,
पूर्ण,
पूर्ण;

अटल u32 sparc_vt_पढ़ो_pmc(पूर्णांक idx)
अणु
	u64 val = pcr_ops->पढ़ो_pic(idx);

	वापस val & 0xffffffff;
पूर्ण

अटल व्योम sparc_vt_ग_लिखो_pmc(पूर्णांक idx, u64 val)
अणु
	u64 pcr;

	pcr = pcr_ops->पढ़ो_pcr(idx);
	/* ensure ov and ntc are reset */
	pcr &= ~(PCR_N4_OV | PCR_N4_NTC);

	pcr_ops->ग_लिखो_pic(idx, val & 0xffffffff);

	pcr_ops->ग_लिखो_pcr(idx, pcr);
पूर्ण

अटल स्थिर काष्ठा sparc_pmu niagara4_pmu = अणु
	.event_map	= niagara4_event_map,
	.cache_map	= &niagara4_cache_map,
	.max_events	= ARRAY_SIZE(niagara4_perfmon_event_map),
	.पढ़ो_pmc	= sparc_vt_पढ़ो_pmc,
	.ग_लिखो_pmc	= sparc_vt_ग_लिखो_pmc,
	.upper_shअगरt	= 5,
	.lower_shअगरt	= 5,
	.event_mask	= 0x7ff,
	.user_bit	= PCR_N4_UTRACE,
	.priv_bit	= PCR_N4_STRACE,

	/* We explicitly करोn't support hypervisor tracing.  The T4
	 * generates the overflow event क्रम precise events via a trap
	 * which will not be generated (ie. it's completely lost) अगर
	 * we happen to be in the hypervisor when the event triggers.
	 * Essentially, the overflow event reporting is completely
	 * unusable when you have hypervisor mode tracing enabled.
	 */
	.hv_bit		= 0,

	.irq_bit	= PCR_N4_TOE,
	.upper_nop	= 0,
	.lower_nop	= 0,
	.flags		= 0,
	.max_hw_events	= 4,
	.num_pcrs	= 4,
	.num_pic_regs	= 4,
पूर्ण;

अटल स्थिर काष्ठा sparc_pmu sparc_m7_pmu = अणु
	.event_map	= niagara4_event_map,
	.cache_map	= &niagara4_cache_map,
	.max_events	= ARRAY_SIZE(niagara4_perfmon_event_map),
	.पढ़ो_pmc	= sparc_vt_पढ़ो_pmc,
	.ग_लिखो_pmc	= sparc_vt_ग_लिखो_pmc,
	.upper_shअगरt	= 5,
	.lower_shअगरt	= 5,
	.event_mask	= 0x7ff,
	.user_bit	= PCR_N4_UTRACE,
	.priv_bit	= PCR_N4_STRACE,

	/* We explicitly करोn't support hypervisor tracing. */
	.hv_bit		= 0,

	.irq_bit	= PCR_N4_TOE,
	.upper_nop	= 0,
	.lower_nop	= 0,
	.flags		= 0,
	.max_hw_events	= 4,
	.num_pcrs	= 4,
	.num_pic_regs	= 4,
पूर्ण;
अटल स्थिर काष्ठा sparc_pmu *sparc_pmu __पढ़ो_mostly;

अटल u64 event_encoding(u64 event_id, पूर्णांक idx)
अणु
	अगर (idx == PIC_UPPER_INDEX)
		event_id <<= sparc_pmu->upper_shअगरt;
	अन्यथा
		event_id <<= sparc_pmu->lower_shअगरt;
	वापस event_id;
पूर्ण

अटल u64 mask_क्रम_index(पूर्णांक idx)
अणु
	वापस event_encoding(sparc_pmu->event_mask, idx);
पूर्ण

अटल u64 nop_क्रम_index(पूर्णांक idx)
अणु
	वापस event_encoding(idx == PIC_UPPER_INDEX ?
			      sparc_pmu->upper_nop :
			      sparc_pmu->lower_nop, idx);
पूर्ण

अटल अंतरभूत व्योम sparc_pmu_enable_event(काष्ठा cpu_hw_events *cpuc, काष्ठा hw_perf_event *hwc, पूर्णांक idx)
अणु
	u64 enc, val, mask = mask_क्रम_index(idx);
	पूर्णांक pcr_index = 0;

	अगर (sparc_pmu->num_pcrs > 1)
		pcr_index = idx;

	enc = perf_event_get_enc(cpuc->events[idx]);

	val = cpuc->pcr[pcr_index];
	val &= ~mask;
	val |= event_encoding(enc, idx);
	cpuc->pcr[pcr_index] = val;

	pcr_ops->ग_लिखो_pcr(pcr_index, cpuc->pcr[pcr_index]);
पूर्ण

अटल अंतरभूत व्योम sparc_pmu_disable_event(काष्ठा cpu_hw_events *cpuc, काष्ठा hw_perf_event *hwc, पूर्णांक idx)
अणु
	u64 mask = mask_क्रम_index(idx);
	u64 nop = nop_क्रम_index(idx);
	पूर्णांक pcr_index = 0;
	u64 val;

	अगर (sparc_pmu->num_pcrs > 1)
		pcr_index = idx;

	val = cpuc->pcr[pcr_index];
	val &= ~mask;
	val |= nop;
	cpuc->pcr[pcr_index] = val;

	pcr_ops->ग_लिखो_pcr(pcr_index, cpuc->pcr[pcr_index]);
पूर्ण

अटल u64 sparc_perf_event_update(काष्ठा perf_event *event,
				   काष्ठा hw_perf_event *hwc, पूर्णांक idx)
अणु
	पूर्णांक shअगरt = 64 - 32;
	u64 prev_raw_count, new_raw_count;
	s64 delta;

again:
	prev_raw_count = local64_पढ़ो(&hwc->prev_count);
	new_raw_count = sparc_pmu->पढ़ो_pmc(idx);

	अगर (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
			     new_raw_count) != prev_raw_count)
		जाओ again;

	delta = (new_raw_count << shअगरt) - (prev_raw_count << shअगरt);
	delta >>= shअगरt;

	local64_add(delta, &event->count);
	local64_sub(delta, &hwc->period_left);

	वापस new_raw_count;
पूर्ण

अटल पूर्णांक sparc_perf_event_set_period(काष्ठा perf_event *event,
				       काष्ठा hw_perf_event *hwc, पूर्णांक idx)
अणु
	s64 left = local64_पढ़ो(&hwc->period_left);
	s64 period = hwc->sample_period;
	पूर्णांक ret = 0;

	/* The period may have been changed by PERF_EVENT_IOC_PERIOD */
	अगर (unlikely(period != hwc->last_period))
		left = period - (hwc->last_period - left);

	अगर (unlikely(left <= -period)) अणु
		left = period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	पूर्ण

	अगर (unlikely(left <= 0)) अणु
		left += period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	पूर्ण
	अगर (left > MAX_PERIOD)
		left = MAX_PERIOD;

	local64_set(&hwc->prev_count, (u64)-left);

	sparc_pmu->ग_लिखो_pmc(idx, (u64)(-left) & 0xffffffff);

	perf_event_update_userpage(event);

	वापस ret;
पूर्ण

अटल व्योम पढ़ो_in_all_counters(काष्ठा cpu_hw_events *cpuc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cpuc->n_events; i++) अणु
		काष्ठा perf_event *cp = cpuc->event[i];

		अगर (cpuc->current_idx[i] != PIC_NO_INDEX &&
		    cpuc->current_idx[i] != cp->hw.idx) अणु
			sparc_perf_event_update(cp, &cp->hw,
						cpuc->current_idx[i]);
			cpuc->current_idx[i] = PIC_NO_INDEX;
			अगर (cp->hw.state & PERF_HES_STOPPED)
				cp->hw.state |= PERF_HES_ARCH;
		पूर्ण
	पूर्ण
पूर्ण

/* On this PMU all PICs are programmed using a single PCR.  Calculate
 * the combined control रेजिस्टर value.
 *
 * For such chips we require that all of the events have the same
 * configuration, so just fetch the settings from the first entry.
 */
अटल व्योम calculate_single_pcr(काष्ठा cpu_hw_events *cpuc)
अणु
	पूर्णांक i;

	अगर (!cpuc->n_added)
		जाओ out;

	/* Assign to counters all unasचिन्हित events.  */
	क्रम (i = 0; i < cpuc->n_events; i++) अणु
		काष्ठा perf_event *cp = cpuc->event[i];
		काष्ठा hw_perf_event *hwc = &cp->hw;
		पूर्णांक idx = hwc->idx;
		u64 enc;

		अगर (cpuc->current_idx[i] != PIC_NO_INDEX)
			जारी;

		sparc_perf_event_set_period(cp, hwc, idx);
		cpuc->current_idx[i] = idx;

		enc = perf_event_get_enc(cpuc->events[i]);
		cpuc->pcr[0] &= ~mask_क्रम_index(idx);
		अगर (hwc->state & PERF_HES_ARCH) अणु
			cpuc->pcr[0] |= nop_क्रम_index(idx);
		पूर्ण अन्यथा अणु
			cpuc->pcr[0] |= event_encoding(enc, idx);
			hwc->state = 0;
		पूर्ण
	पूर्ण
out:
	cpuc->pcr[0] |= cpuc->event[0]->hw.config_base;
पूर्ण

अटल व्योम sparc_pmu_start(काष्ठा perf_event *event, पूर्णांक flags);

/* On this PMU each PIC has it's own PCR control रेजिस्टर.  */
अटल व्योम calculate_multiple_pcrs(काष्ठा cpu_hw_events *cpuc)
अणु
	पूर्णांक i;

	अगर (!cpuc->n_added)
		जाओ out;

	क्रम (i = 0; i < cpuc->n_events; i++) अणु
		काष्ठा perf_event *cp = cpuc->event[i];
		काष्ठा hw_perf_event *hwc = &cp->hw;
		पूर्णांक idx = hwc->idx;

		अगर (cpuc->current_idx[i] != PIC_NO_INDEX)
			जारी;

		cpuc->current_idx[i] = idx;

		अगर (cp->hw.state & PERF_HES_ARCH)
			जारी;

		sparc_pmu_start(cp, PERF_EF_RELOAD);
	पूर्ण
out:
	क्रम (i = 0; i < cpuc->n_events; i++) अणु
		काष्ठा perf_event *cp = cpuc->event[i];
		पूर्णांक idx = cp->hw.idx;

		cpuc->pcr[idx] |= cp->hw.config_base;
	पूर्ण
पूर्ण

/* If perक्रमmance event entries have been added, move existing events
 * around (अगर necessary) and then assign new entries to counters.
 */
अटल व्योम update_pcrs_क्रम_enable(काष्ठा cpu_hw_events *cpuc)
अणु
	अगर (cpuc->n_added)
		पढ़ो_in_all_counters(cpuc);

	अगर (sparc_pmu->num_pcrs == 1) अणु
		calculate_single_pcr(cpuc);
	पूर्ण अन्यथा अणु
		calculate_multiple_pcrs(cpuc);
	पूर्ण
पूर्ण

अटल व्योम sparc_pmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक i;

	अगर (cpuc->enabled)
		वापस;

	cpuc->enabled = 1;
	barrier();

	अगर (cpuc->n_events)
		update_pcrs_क्रम_enable(cpuc);

	क्रम (i = 0; i < sparc_pmu->num_pcrs; i++)
		pcr_ops->ग_लिखो_pcr(i, cpuc->pcr[i]);
पूर्ण

अटल व्योम sparc_pmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक i;

	अगर (!cpuc->enabled)
		वापस;

	cpuc->enabled = 0;
	cpuc->n_added = 0;

	क्रम (i = 0; i < sparc_pmu->num_pcrs; i++) अणु
		u64 val = cpuc->pcr[i];

		val &= ~(sparc_pmu->user_bit | sparc_pmu->priv_bit |
			 sparc_pmu->hv_bit | sparc_pmu->irq_bit);
		cpuc->pcr[i] = val;
		pcr_ops->ग_लिखो_pcr(i, cpuc->pcr[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक active_event_index(काष्ठा cpu_hw_events *cpuc,
			      काष्ठा perf_event *event)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cpuc->n_events; i++) अणु
		अगर (cpuc->event[i] == event)
			अवरोध;
	पूर्ण
	BUG_ON(i == cpuc->n_events);
	वापस cpuc->current_idx[i];
पूर्ण

अटल व्योम sparc_pmu_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक idx = active_event_index(cpuc, event);

	अगर (flags & PERF_EF_RELOAD) अणु
		WARN_ON_ONCE(!(event->hw.state & PERF_HES_UPTODATE));
		sparc_perf_event_set_period(event, &event->hw, idx);
	पूर्ण

	event->hw.state = 0;

	sparc_pmu_enable_event(cpuc, &event->hw, idx);

	perf_event_update_userpage(event);
पूर्ण

अटल व्योम sparc_pmu_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक idx = active_event_index(cpuc, event);

	अगर (!(event->hw.state & PERF_HES_STOPPED)) अणु
		sparc_pmu_disable_event(cpuc, &event->hw, idx);
		event->hw.state |= PERF_HES_STOPPED;
	पूर्ण

	अगर (!(event->hw.state & PERF_HES_UPTODATE) && (flags & PERF_EF_UPDATE)) अणु
		sparc_perf_event_update(event, &event->hw, idx);
		event->hw.state |= PERF_HES_UPTODATE;
	पूर्ण
पूर्ण

अटल व्योम sparc_pmu_del(काष्ठा perf_event *event, पूर्णांक _flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	local_irq_save(flags);

	क्रम (i = 0; i < cpuc->n_events; i++) अणु
		अगर (event == cpuc->event[i]) अणु
			/* Absorb the final count and turn off the
			 * event.
			 */
			sparc_pmu_stop(event, PERF_EF_UPDATE);

			/* Shअगरt reमुख्यing entries करोwn पूर्णांकo
			 * the existing slot.
			 */
			जबतक (++i < cpuc->n_events) अणु
				cpuc->event[i - 1] = cpuc->event[i];
				cpuc->events[i - 1] = cpuc->events[i];
				cpuc->current_idx[i - 1] =
					cpuc->current_idx[i];
			पूर्ण

			perf_event_update_userpage(event);

			cpuc->n_events--;
			अवरोध;
		पूर्ण
	पूर्ण

	local_irq_restore(flags);
पूर्ण

अटल व्योम sparc_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक idx = active_event_index(cpuc, event);
	काष्ठा hw_perf_event *hwc = &event->hw;

	sparc_perf_event_update(event, hwc, idx);
पूर्ण

अटल atomic_t active_events = ATOMIC_INIT(0);
अटल DEFINE_MUTEX(pmc_grab_mutex);

अटल व्योम perf_stop_nmi_watchकरोg(व्योम *unused)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक i;

	stop_nmi_watchकरोg(शून्य);
	क्रम (i = 0; i < sparc_pmu->num_pcrs; i++)
		cpuc->pcr[i] = pcr_ops->पढ़ो_pcr(i);
पूर्ण

अटल व्योम perf_event_grab_pmc(व्योम)
अणु
	अगर (atomic_inc_not_zero(&active_events))
		वापस;

	mutex_lock(&pmc_grab_mutex);
	अगर (atomic_पढ़ो(&active_events) == 0) अणु
		अगर (atomic_पढ़ो(&nmi_active) > 0) अणु
			on_each_cpu(perf_stop_nmi_watchकरोg, शून्य, 1);
			BUG_ON(atomic_पढ़ो(&nmi_active) != 0);
		पूर्ण
		atomic_inc(&active_events);
	पूर्ण
	mutex_unlock(&pmc_grab_mutex);
पूर्ण

अटल व्योम perf_event_release_pmc(व्योम)
अणु
	अगर (atomic_dec_and_mutex_lock(&active_events, &pmc_grab_mutex)) अणु
		अगर (atomic_पढ़ो(&nmi_active) == 0)
			on_each_cpu(start_nmi_watchकरोg, शून्य, 1);
		mutex_unlock(&pmc_grab_mutex);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा perf_event_map *sparc_map_cache_event(u64 config)
अणु
	अचिन्हित पूर्णांक cache_type, cache_op, cache_result;
	स्थिर काष्ठा perf_event_map *pmap;

	अगर (!sparc_pmu->cache_map)
		वापस ERR_PTR(-ENOENT);

	cache_type = (config >>  0) & 0xff;
	अगर (cache_type >= PERF_COUNT_HW_CACHE_MAX)
		वापस ERR_PTR(-EINVAL);

	cache_op = (config >>  8) & 0xff;
	अगर (cache_op >= PERF_COUNT_HW_CACHE_OP_MAX)
		वापस ERR_PTR(-EINVAL);

	cache_result = (config >> 16) & 0xff;
	अगर (cache_result >= PERF_COUNT_HW_CACHE_RESULT_MAX)
		वापस ERR_PTR(-EINVAL);

	pmap = &((*sparc_pmu->cache_map)[cache_type][cache_op][cache_result]);

	अगर (pmap->encoding == CACHE_OP_UNSUPPORTED)
		वापस ERR_PTR(-ENOENT);

	अगर (pmap->encoding == CACHE_OP_NONSENSE)
		वापस ERR_PTR(-EINVAL);

	वापस pmap;
पूर्ण

अटल व्योम hw_perf_event_destroy(काष्ठा perf_event *event)
अणु
	perf_event_release_pmc();
पूर्ण

/* Make sure all events can be scheduled पूर्णांकo the hardware at
 * the same समय.  This is simplअगरied by the fact that we only
 * need to support 2 simultaneous HW events.
 *
 * As a side effect, the evts[]->hw.idx values will be asचिन्हित
 * on success.  These are pending indexes.  When the events are
 * actually programmed पूर्णांकo the chip, these values will propagate
 * to the per-cpu cpuc->current_idx[] slots, see the code in
 * maybe_change_configuration() क्रम details.
 */
अटल पूर्णांक sparc_check_स्थिरraपूर्णांकs(काष्ठा perf_event **evts,
				   अचिन्हित दीर्घ *events, पूर्णांक n_ev)
अणु
	u8 msk0 = 0, msk1 = 0;
	पूर्णांक idx0 = 0;

	/* This हाल is possible when we are invoked from
	 * hw_perf_group_sched_in().
	 */
	अगर (!n_ev)
		वापस 0;

	अगर (n_ev > sparc_pmu->max_hw_events)
		वापस -1;

	अगर (!(sparc_pmu->flags & SPARC_PMU_HAS_CONFLICTS)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < n_ev; i++)
			evts[i]->hw.idx = i;
		वापस 0;
	पूर्ण

	msk0 = perf_event_get_msk(events[0]);
	अगर (n_ev == 1) अणु
		अगर (msk0 & PIC_LOWER)
			idx0 = 1;
		जाओ success;
	पूर्ण
	BUG_ON(n_ev != 2);
	msk1 = perf_event_get_msk(events[1]);

	/* If both events can go on any counter, OK.  */
	अगर (msk0 == (PIC_UPPER | PIC_LOWER) &&
	    msk1 == (PIC_UPPER | PIC_LOWER))
		जाओ success;

	/* If one event is limited to a specअगरic counter,
	 * and the other can go on both, OK.
	 */
	अगर ((msk0 == PIC_UPPER || msk0 == PIC_LOWER) &&
	    msk1 == (PIC_UPPER | PIC_LOWER)) अणु
		अगर (msk0 & PIC_LOWER)
			idx0 = 1;
		जाओ success;
	पूर्ण

	अगर ((msk1 == PIC_UPPER || msk1 == PIC_LOWER) &&
	    msk0 == (PIC_UPPER | PIC_LOWER)) अणु
		अगर (msk1 & PIC_UPPER)
			idx0 = 1;
		जाओ success;
	पूर्ण

	/* If the events are fixed to dअगरferent counters, OK.  */
	अगर ((msk0 == PIC_UPPER && msk1 == PIC_LOWER) ||
	    (msk0 == PIC_LOWER && msk1 == PIC_UPPER)) अणु
		अगर (msk0 & PIC_LOWER)
			idx0 = 1;
		जाओ success;
	पूर्ण

	/* Otherwise, there is a conflict.  */
	वापस -1;

success:
	evts[0]->hw.idx = idx0;
	अगर (n_ev == 2)
		evts[1]->hw.idx = idx0 ^ 1;
	वापस 0;
पूर्ण

अटल पूर्णांक check_excludes(काष्ठा perf_event **evts, पूर्णांक n_prev, पूर्णांक n_new)
अणु
	पूर्णांक eu = 0, ek = 0, eh = 0;
	काष्ठा perf_event *event;
	पूर्णांक i, n, first;

	अगर (!(sparc_pmu->flags & SPARC_PMU_ALL_EXCLUDES_SAME))
		वापस 0;

	n = n_prev + n_new;
	अगर (n <= 1)
		वापस 0;

	first = 1;
	क्रम (i = 0; i < n; i++) अणु
		event = evts[i];
		अगर (first) अणु
			eu = event->attr.exclude_user;
			ek = event->attr.exclude_kernel;
			eh = event->attr.exclude_hv;
			first = 0;
		पूर्ण अन्यथा अगर (event->attr.exclude_user != eu ||
			   event->attr.exclude_kernel != ek ||
			   event->attr.exclude_hv != eh) अणु
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक collect_events(काष्ठा perf_event *group, पूर्णांक max_count,
			  काष्ठा perf_event *evts[], अचिन्हित दीर्घ *events,
			  पूर्णांक *current_idx)
अणु
	काष्ठा perf_event *event;
	पूर्णांक n = 0;

	अगर (!is_software_event(group)) अणु
		अगर (n >= max_count)
			वापस -1;
		evts[n] = group;
		events[n] = group->hw.event_base;
		current_idx[n++] = PIC_NO_INDEX;
	पूर्ण
	क्रम_each_sibling_event(event, group) अणु
		अगर (!is_software_event(event) &&
		    event->state != PERF_EVENT_STATE_OFF) अणु
			अगर (n >= max_count)
				वापस -1;
			evts[n] = event;
			events[n] = event->hw.event_base;
			current_idx[n++] = PIC_NO_INDEX;
		पूर्ण
	पूर्ण
	वापस n;
पूर्ण

अटल पूर्णांक sparc_pmu_add(काष्ठा perf_event *event, पूर्णांक ef_flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक n0, ret = -EAGAIN;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	n0 = cpuc->n_events;
	अगर (n0 >= sparc_pmu->max_hw_events)
		जाओ out;

	cpuc->event[n0] = event;
	cpuc->events[n0] = event->hw.event_base;
	cpuc->current_idx[n0] = PIC_NO_INDEX;

	event->hw.state = PERF_HES_UPTODATE | PERF_HES_STOPPED;
	अगर (!(ef_flags & PERF_EF_START))
		event->hw.state |= PERF_HES_ARCH;

	/*
	 * If group events scheduling transaction was started,
	 * skip the schedulability test here, it will be perक्रमmed
	 * at commit समय(->commit_txn) as a whole
	 */
	अगर (cpuc->txn_flags & PERF_PMU_TXN_ADD)
		जाओ nocheck;

	अगर (check_excludes(cpuc->event, n0, 1))
		जाओ out;
	अगर (sparc_check_स्थिरraपूर्णांकs(cpuc->event, cpuc->events, n0 + 1))
		जाओ out;

nocheck:
	cpuc->n_events++;
	cpuc->n_added++;

	ret = 0;
out:
	local_irq_restore(flags);
	वापस ret;
पूर्ण

अटल पूर्णांक sparc_pmu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	काष्ठा perf_event *evts[MAX_HWEVENTS];
	काष्ठा hw_perf_event *hwc = &event->hw;
	अचिन्हित दीर्घ events[MAX_HWEVENTS];
	पूर्णांक current_idx_dmy[MAX_HWEVENTS];
	स्थिर काष्ठा perf_event_map *pmap;
	पूर्णांक n;

	अगर (atomic_पढ़ो(&nmi_active) < 0)
		वापस -ENODEV;

	/* करोes not support taken branch sampling */
	अगर (has_branch_stack(event))
		वापस -EOPNOTSUPP;

	चयन (attr->type) अणु
	हाल PERF_TYPE_HARDWARE:
		अगर (attr->config >= sparc_pmu->max_events)
			वापस -EINVAL;
		pmap = sparc_pmu->event_map(attr->config);
		अवरोध;

	हाल PERF_TYPE_HW_CACHE:
		pmap = sparc_map_cache_event(attr->config);
		अगर (IS_ERR(pmap))
			वापस PTR_ERR(pmap);
		अवरोध;

	हाल PERF_TYPE_RAW:
		pmap = शून्य;
		अवरोध;

	शेष:
		वापस -ENOENT;

	पूर्ण

	अगर (pmap) अणु
		hwc->event_base = perf_event_encode(pmap);
	पूर्ण अन्यथा अणु
		/*
		 * User gives us "(encoding << 16) | pic_mask" क्रम
		 * PERF_TYPE_RAW events.
		 */
		hwc->event_base = attr->config;
	पूर्ण

	/* We save the enable bits in the config_base.  */
	hwc->config_base = sparc_pmu->irq_bit;
	अगर (!attr->exclude_user)
		hwc->config_base |= sparc_pmu->user_bit;
	अगर (!attr->exclude_kernel)
		hwc->config_base |= sparc_pmu->priv_bit;
	अगर (!attr->exclude_hv)
		hwc->config_base |= sparc_pmu->hv_bit;

	n = 0;
	अगर (event->group_leader != event) अणु
		n = collect_events(event->group_leader,
				   sparc_pmu->max_hw_events - 1,
				   evts, events, current_idx_dmy);
		अगर (n < 0)
			वापस -EINVAL;
	पूर्ण
	events[n] = hwc->event_base;
	evts[n] = event;

	अगर (check_excludes(evts, n, 1))
		वापस -EINVAL;

	अगर (sparc_check_स्थिरraपूर्णांकs(evts, events, n + 1))
		वापस -EINVAL;

	hwc->idx = PIC_NO_INDEX;

	/* Try to करो all error checking beक्रमe this poपूर्णांक, as unwinding
	 * state after grabbing the PMC is dअगरficult.
	 */
	perf_event_grab_pmc();
	event->destroy = hw_perf_event_destroy;

	अगर (!hwc->sample_period) अणु
		hwc->sample_period = MAX_PERIOD;
		hwc->last_period = hwc->sample_period;
		local64_set(&hwc->period_left, hwc->sample_period);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Start group events scheduling transaction
 * Set the flag to make pmu::enable() not perक्रमm the
 * schedulability test, it will be perक्रमmed at commit समय
 */
अटल व्योम sparc_pmu_start_txn(काष्ठा pmu *pmu, अचिन्हित पूर्णांक txn_flags)
अणु
	काष्ठा cpu_hw_events *cpuhw = this_cpu_ptr(&cpu_hw_events);

	WARN_ON_ONCE(cpuhw->txn_flags);		/* txn alपढ़ोy in flight */

	cpuhw->txn_flags = txn_flags;
	अगर (txn_flags & ~PERF_PMU_TXN_ADD)
		वापस;

	perf_pmu_disable(pmu);
पूर्ण

/*
 * Stop group events scheduling transaction
 * Clear the flag and pmu::enable() will perक्रमm the
 * schedulability test.
 */
अटल व्योम sparc_pmu_cancel_txn(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_hw_events *cpuhw = this_cpu_ptr(&cpu_hw_events);
	अचिन्हित पूर्णांक txn_flags;

	WARN_ON_ONCE(!cpuhw->txn_flags);	/* no txn in flight */

	txn_flags = cpuhw->txn_flags;
	cpuhw->txn_flags = 0;
	अगर (txn_flags & ~PERF_PMU_TXN_ADD)
		वापस;

	perf_pmu_enable(pmu);
पूर्ण

/*
 * Commit group events scheduling transaction
 * Perक्रमm the group schedulability test as a whole
 * Return 0 अगर success
 */
अटल पूर्णांक sparc_pmu_commit_txn(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक n;

	अगर (!sparc_pmu)
		वापस -EINVAL;

	WARN_ON_ONCE(!cpuc->txn_flags);	/* no txn in flight */

	अगर (cpuc->txn_flags & ~PERF_PMU_TXN_ADD) अणु
		cpuc->txn_flags = 0;
		वापस 0;
	पूर्ण

	n = cpuc->n_events;
	अगर (check_excludes(cpuc->event, 0, n))
		वापस -EINVAL;
	अगर (sparc_check_स्थिरraपूर्णांकs(cpuc->event, cpuc->events, n))
		वापस -EAGAIN;

	cpuc->txn_flags = 0;
	perf_pmu_enable(pmu);
	वापस 0;
पूर्ण

अटल काष्ठा pmu pmu = अणु
	.pmu_enable	= sparc_pmu_enable,
	.pmu_disable	= sparc_pmu_disable,
	.event_init	= sparc_pmu_event_init,
	.add		= sparc_pmu_add,
	.del		= sparc_pmu_del,
	.start		= sparc_pmu_start,
	.stop		= sparc_pmu_stop,
	.पढ़ो		= sparc_pmu_पढ़ो,
	.start_txn	= sparc_pmu_start_txn,
	.cancel_txn	= sparc_pmu_cancel_txn,
	.commit_txn	= sparc_pmu_commit_txn,
पूर्ण;

व्योम perf_event_prपूर्णांक_debug(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक cpu, i;

	अगर (!sparc_pmu)
		वापस;

	local_irq_save(flags);

	cpu = smp_processor_id();

	pr_info("\n");
	क्रम (i = 0; i < sparc_pmu->num_pcrs; i++)
		pr_info("CPU#%d: PCR%d[%016llx]\n",
			cpu, i, pcr_ops->पढ़ो_pcr(i));
	क्रम (i = 0; i < sparc_pmu->num_pic_regs; i++)
		pr_info("CPU#%d: PIC%d[%016llx]\n",
			cpu, i, pcr_ops->पढ़ो_pic(i));

	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक __kprobes perf_event_nmi_handler(काष्ठा notअगरier_block *self,
					    अचिन्हित दीर्घ cmd, व्योम *__args)
अणु
	काष्ठा die_args *args = __args;
	काष्ठा perf_sample_data data;
	काष्ठा cpu_hw_events *cpuc;
	काष्ठा pt_regs *regs;
	u64 finish_घड़ी;
	u64 start_घड़ी;
	पूर्णांक i;

	अगर (!atomic_पढ़ो(&active_events))
		वापस NOTIFY_DONE;

	चयन (cmd) अणु
	हाल DIE_NMI:
		अवरोध;

	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	start_घड़ी = sched_घड़ी();

	regs = args->regs;

	cpuc = this_cpu_ptr(&cpu_hw_events);

	/* If the PMU has the TOE IRQ enable bits, we need to करो a
	 * dummy ग_लिखो to the %pcr to clear the overflow bits and thus
	 * the पूर्णांकerrupt.
	 *
	 * Do this beक्रमe we peek at the counters to determine
	 * overflow so we करोn't lose any events.
	 */
	अगर (sparc_pmu->irq_bit &&
	    sparc_pmu->num_pcrs == 1)
		pcr_ops->ग_लिखो_pcr(0, cpuc->pcr[0]);

	क्रम (i = 0; i < cpuc->n_events; i++) अणु
		काष्ठा perf_event *event = cpuc->event[i];
		पूर्णांक idx = cpuc->current_idx[i];
		काष्ठा hw_perf_event *hwc;
		u64 val;

		अगर (sparc_pmu->irq_bit &&
		    sparc_pmu->num_pcrs > 1)
			pcr_ops->ग_लिखो_pcr(idx, cpuc->pcr[idx]);

		hwc = &event->hw;
		val = sparc_perf_event_update(event, hwc, idx);
		अगर (val & (1ULL << 31))
			जारी;

		perf_sample_data_init(&data, 0, hwc->last_period);
		अगर (!sparc_perf_event_set_period(event, hwc, idx))
			जारी;

		अगर (perf_event_overflow(event, &data, regs))
			sparc_pmu_stop(event, 0);
	पूर्ण

	finish_घड़ी = sched_घड़ी();

	perf_sample_event_took(finish_घड़ी - start_घड़ी);

	वापस NOTIFY_STOP;
पूर्ण

अटल __पढ़ो_mostly काष्ठा notअगरier_block perf_event_nmi_notअगरier = अणु
	.notअगरier_call		= perf_event_nmi_handler,
पूर्ण;

अटल bool __init supported_pmu(व्योम)
अणु
	अगर (!म_भेद(sparc_pmu_type, "ultra3") ||
	    !म_भेद(sparc_pmu_type, "ultra3+") ||
	    !म_भेद(sparc_pmu_type, "ultra3i") ||
	    !म_भेद(sparc_pmu_type, "ultra4+")) अणु
		sparc_pmu = &ultra3_pmu;
		वापस true;
	पूर्ण
	अगर (!म_भेद(sparc_pmu_type, "niagara")) अणु
		sparc_pmu = &niagara1_pmu;
		वापस true;
	पूर्ण
	अगर (!म_भेद(sparc_pmu_type, "niagara2") ||
	    !म_भेद(sparc_pmu_type, "niagara3")) अणु
		sparc_pmu = &niagara2_pmu;
		वापस true;
	पूर्ण
	अगर (!म_भेद(sparc_pmu_type, "niagara4") ||
	    !म_भेद(sparc_pmu_type, "niagara5")) अणु
		sparc_pmu = &niagara4_pmu;
		वापस true;
	पूर्ण
	अगर (!म_भेद(sparc_pmu_type, "sparc-m7")) अणु
		sparc_pmu = &sparc_m7_pmu;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक __init init_hw_perf_events(व्योम)
अणु
	पूर्णांक err;

	pr_info("Performance events: ");

	err = pcr_arch_init();
	अगर (err || !supported_pmu()) अणु
		pr_cont("No support for PMU type '%s'\n", sparc_pmu_type);
		वापस 0;
	पूर्ण

	pr_cont("Supported PMU type is '%s'\n", sparc_pmu_type);

	perf_pmu_रेजिस्टर(&pmu, "cpu", PERF_TYPE_RAW);
	रेजिस्टर_die_notअगरier(&perf_event_nmi_notअगरier);

	वापस 0;
पूर्ण
pure_initcall(init_hw_perf_events);

व्योम perf_callchain_kernel(काष्ठा perf_callchain_entry_ctx *entry,
			   काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ ksp, fp;
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	पूर्णांक graph = 0;
#पूर्ण_अगर

	stack_trace_flush();

	perf_callchain_store(entry, regs->tpc);

	ksp = regs->u_regs[UREG_I6];
	fp = ksp + STACK_BIAS;
	करो अणु
		काष्ठा sparc_stackf *sf;
		काष्ठा pt_regs *regs;
		अचिन्हित दीर्घ pc;

		अगर (!kstack_valid(current_thपढ़ो_info(), fp))
			अवरोध;

		sf = (काष्ठा sparc_stackf *) fp;
		regs = (काष्ठा pt_regs *) (sf + 1);

		अगर (kstack_is_trap_frame(current_thपढ़ो_info(), regs)) अणु
			अगर (user_mode(regs))
				अवरोध;
			pc = regs->tpc;
			fp = regs->u_regs[UREG_I6] + STACK_BIAS;
		पूर्ण अन्यथा अणु
			pc = sf->callers_pc;
			fp = (अचिन्हित दीर्घ)sf->fp + STACK_BIAS;
		पूर्ण
		perf_callchain_store(entry, pc);
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
		अगर ((pc + 8UL) == (अचिन्हित दीर्घ) &वापस_to_handler) अणु
			काष्ठा ftrace_ret_stack *ret_stack;
			ret_stack = ftrace_graph_get_ret_stack(current,
							       graph);
			अगर (ret_stack) अणु
				pc = ret_stack->ret;
				perf_callchain_store(entry, pc);
				graph++;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण जबतक (entry->nr < entry->max_stack);
पूर्ण

अटल अंतरभूत पूर्णांक
valid_user_frame(स्थिर व्योम __user *fp, अचिन्हित दीर्घ size)
अणु
	/* addresses should be at least 4-byte aligned */
	अगर (((अचिन्हित दीर्घ) fp) & 3)
		वापस 0;

	वापस (__range_not_ok(fp, size, TASK_SIZE) == 0);
पूर्ण

अटल व्योम perf_callchain_user_64(काष्ठा perf_callchain_entry_ctx *entry,
				   काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ ufp;

	ufp = regs->u_regs[UREG_FP] + STACK_BIAS;
	करो अणु
		काष्ठा sparc_stackf __user *usf;
		काष्ठा sparc_stackf sf;
		अचिन्हित दीर्घ pc;

		usf = (काष्ठा sparc_stackf __user *)ufp;
		अगर (!valid_user_frame(usf, माप(sf)))
			अवरोध;

		अगर (__copy_from_user_inatomic(&sf, usf, माप(sf)))
			अवरोध;

		pc = sf.callers_pc;
		ufp = (अचिन्हित दीर्घ)sf.fp + STACK_BIAS;
		perf_callchain_store(entry, pc);
	पूर्ण जबतक (entry->nr < entry->max_stack);
पूर्ण

अटल व्योम perf_callchain_user_32(काष्ठा perf_callchain_entry_ctx *entry,
				   काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ ufp;

	ufp = regs->u_regs[UREG_FP] & 0xffffffffUL;
	करो अणु
		अचिन्हित दीर्घ pc;

		अगर (thपढ़ो32_stack_is_64bit(ufp)) अणु
			काष्ठा sparc_stackf __user *usf;
			काष्ठा sparc_stackf sf;

			ufp += STACK_BIAS;
			usf = (काष्ठा sparc_stackf __user *)ufp;
			अगर (__copy_from_user_inatomic(&sf, usf, माप(sf)))
				अवरोध;
			pc = sf.callers_pc & 0xffffffff;
			ufp = ((अचिन्हित दीर्घ) sf.fp) & 0xffffffff;
		पूर्ण अन्यथा अणु
			काष्ठा sparc_stackf32 __user *usf;
			काष्ठा sparc_stackf32 sf;
			usf = (काष्ठा sparc_stackf32 __user *)ufp;
			अगर (__copy_from_user_inatomic(&sf, usf, माप(sf)))
				अवरोध;
			pc = sf.callers_pc;
			ufp = (अचिन्हित दीर्घ)sf.fp;
		पूर्ण
		perf_callchain_store(entry, pc);
	पूर्ण जबतक (entry->nr < entry->max_stack);
पूर्ण

व्योम
perf_callchain_user(काष्ठा perf_callchain_entry_ctx *entry, काष्ठा pt_regs *regs)
अणु
	u64 saved_fault_address = current_thपढ़ो_info()->fault_address;
	u8 saved_fault_code = get_thपढ़ो_fault_code();

	perf_callchain_store(entry, regs->tpc);

	अगर (!current->mm)
		वापस;

	flushw_user();

	pagefault_disable();

	अगर (test_thपढ़ो_flag(TIF_32BIT))
		perf_callchain_user_32(entry, regs);
	अन्यथा
		perf_callchain_user_64(entry, regs);

	pagefault_enable();

	set_thपढ़ो_fault_code(saved_fault_code);
	current_thपढ़ो_info()->fault_address = saved_fault_address;
पूर्ण
