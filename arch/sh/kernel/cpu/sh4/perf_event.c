<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Perक्रमmance events support क्रम SH7750-style perक्रमmance counters
 *
 *  Copyright (C) 2009  Paul Mundt
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/processor.h>

#घोषणा PM_CR_BASE	0xff000084	/* 16-bit */
#घोषणा PM_CTR_BASE	0xff100004	/* 32-bit */

#घोषणा PMCR(n)		(PM_CR_BASE + ((n) * 0x04))
#घोषणा PMCTRH(n)	(PM_CTR_BASE + 0x00 + ((n) * 0x08))
#घोषणा PMCTRL(n)	(PM_CTR_BASE + 0x04 + ((n) * 0x08))

#घोषणा PMCR_PMM_MASK	0x0000003f

#घोषणा PMCR_CLKF	0x00000100
#घोषणा PMCR_PMCLR	0x00002000
#घोषणा PMCR_PMST	0x00004000
#घोषणा PMCR_PMEN	0x00008000

अटल काष्ठा sh_pmu sh7750_pmu;

/*
 * There are a number of events supported by each counter (33 in total).
 * Since we have 2 counters, each counter will take the event code as it
 * corresponds to the PMCR PMM setting. Each counter can be configured
 * independently.
 *
 *	Event Code	Description
 *	----------	-----------
 *
 *	0x01		Opeअक्रम पढ़ो access
 *	0x02		Opeअक्रम ग_लिखो access
 *	0x03		UTLB miss
 *	0x04		Opeअक्रम cache पढ़ो miss
 *	0x05		Opeअक्रम cache ग_लिखो miss
 *	0x06		Inकाष्ठाion fetch (w/ cache)
 *	0x07		Inकाष्ठाion TLB miss
 *	0x08		Inकाष्ठाion cache miss
 *	0x09		All opeअक्रम accesses
 *	0x0a		All inकाष्ठाion accesses
 *	0x0b		OC RAM opeअक्रम access
 *	0x0d		On-chip I/O space access
 *	0x0e		Opeअक्रम access (r/w)
 *	0x0f		Opeअक्रम cache miss (r/w)
 *	0x10		Branch inकाष्ठाion
 *	0x11		Branch taken
 *	0x12		BSR/BSRF/JSR
 *	0x13		Inकाष्ठाion execution
 *	0x14		Inकाष्ठाion execution in parallel
 *	0x15		FPU Inकाष्ठाion execution
 *	0x16		Interrupt
 *	0x17		NMI
 *	0x18		trapa inकाष्ठाion execution
 *	0x19		UBCA match
 *	0x1a		UBCB match
 *	0x21		Inकाष्ठाion cache fill
 *	0x22		Opeअक्रम cache fill
 *	0x23		Elapsed समय
 *	0x24		Pipeline मुक्तze by I-cache miss
 *	0x25		Pipeline मुक्तze by D-cache miss
 *	0x27		Pipeline मुक्तze by branch inकाष्ठाion
 *	0x28		Pipeline मुक्तze by CPU रेजिस्टर
 *	0x29		Pipeline मुक्तze by FPU
 */

अटल स्थिर पूर्णांक sh7750_general_events[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES]		= 0x0023,
	[PERF_COUNT_HW_INSTRUCTIONS]		= 0x000a,
	[PERF_COUNT_HW_CACHE_REFERENCES]	= 0x0006,	/* I-cache */
	[PERF_COUNT_HW_CACHE_MISSES]		= 0x0008,	/* I-cache */
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= 0x0010,
	[PERF_COUNT_HW_BRANCH_MISSES]		= -1,
	[PERF_COUNT_HW_BUS_CYCLES]		= -1,
पूर्ण;

#घोषणा C(x)	PERF_COUNT_HW_CACHE_##x

अटल स्थिर पूर्णांक sh7750_cache_events
			[PERF_COUNT_HW_CACHE_MAX]
			[PERF_COUNT_HW_CACHE_OP_MAX]
			[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
	[ C(L1D) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = 0x0001,
			[ C(RESULT_MISS)   ] = 0x0004,
		पूर्ण,
		[ C(OP_WRITE) ] = अणु
			[ C(RESULT_ACCESS) ] = 0x0002,
			[ C(RESULT_MISS)   ] = 0x0005,
		पूर्ण,
		[ C(OP_PREFETCH) ] = अणु
			[ C(RESULT_ACCESS) ] = 0,
			[ C(RESULT_MISS)   ] = 0,
		पूर्ण,
	पूर्ण,

	[ C(L1I) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = 0x0006,
			[ C(RESULT_MISS)   ] = 0x0008,
		पूर्ण,
		[ C(OP_WRITE) ] = अणु
			[ C(RESULT_ACCESS) ] = -1,
			[ C(RESULT_MISS)   ] = -1,
		पूर्ण,
		[ C(OP_PREFETCH) ] = अणु
			[ C(RESULT_ACCESS) ] = 0,
			[ C(RESULT_MISS)   ] = 0,
		पूर्ण,
	पूर्ण,

	[ C(LL) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = 0,
			[ C(RESULT_MISS)   ] = 0,
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

	[ C(DTLB) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = 0,
			[ C(RESULT_MISS)   ] = 0x0003,
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
			[ C(RESULT_ACCESS) ] = 0,
			[ C(RESULT_MISS)   ] = 0x0007,
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

	[ C(BPU) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = -1,
			[ C(RESULT_MISS)   ] = -1,
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
			[ C(RESULT_ACCESS) ] = -1,
			[ C(RESULT_MISS)   ] = -1,
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

अटल पूर्णांक sh7750_event_map(पूर्णांक event)
अणु
	वापस sh7750_general_events[event];
पूर्ण

अटल u64 sh7750_pmu_पढ़ो(पूर्णांक idx)
अणु
	वापस (u64)((u64)(__raw_पढ़ोl(PMCTRH(idx)) & 0xffff) << 32) |
			   __raw_पढ़ोl(PMCTRL(idx));
पूर्ण

अटल व्योम sh7750_pmu_disable(काष्ठा hw_perf_event *hwc, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	पंचांगp = __raw_पढ़ोw(PMCR(idx));
	पंचांगp &= ~(PMCR_PMM_MASK | PMCR_PMEN);
	__raw_ग_लिखोw(पंचांगp, PMCR(idx));
पूर्ण

अटल व्योम sh7750_pmu_enable(काष्ठा hw_perf_event *hwc, पूर्णांक idx)
अणु
	__raw_ग_लिखोw(__raw_पढ़ोw(PMCR(idx)) | PMCR_PMCLR, PMCR(idx));
	__raw_ग_लिखोw(hwc->config | PMCR_PMEN | PMCR_PMST, PMCR(idx));
पूर्ण

अटल व्योम sh7750_pmu_disable_all(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sh7750_pmu.num_events; i++)
		__raw_ग_लिखोw(__raw_पढ़ोw(PMCR(i)) & ~PMCR_PMEN, PMCR(i));
पूर्ण

अटल व्योम sh7750_pmu_enable_all(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sh7750_pmu.num_events; i++)
		__raw_ग_लिखोw(__raw_पढ़ोw(PMCR(i)) | PMCR_PMEN, PMCR(i));
पूर्ण

अटल काष्ठा sh_pmu sh7750_pmu = अणु
	.name		= "sh7750",
	.num_events	= 2,
	.event_map	= sh7750_event_map,
	.max_events	= ARRAY_SIZE(sh7750_general_events),
	.raw_event_mask	= PMCR_PMM_MASK,
	.cache_events	= &sh7750_cache_events,
	.पढ़ो		= sh7750_pmu_पढ़ो,
	.disable	= sh7750_pmu_disable,
	.enable		= sh7750_pmu_enable,
	.disable_all	= sh7750_pmu_disable_all,
	.enable_all	= sh7750_pmu_enable_all,
पूर्ण;

अटल पूर्णांक __init sh7750_pmu_init(व्योम)
अणु
	/*
	 * Make sure this CPU actually has perf counters.
	 */
	अगर (!(boot_cpu_data.flags & CPU_HAS_PERF_COUNTER)) अणु
		pr_notice("HW perf events unsupported, software events only.\n");
		वापस -ENODEV;
	पूर्ण

	वापस रेजिस्टर_sh_pmu(&sh7750_pmu);
पूर्ण
early_initcall(sh7750_pmu_init);
