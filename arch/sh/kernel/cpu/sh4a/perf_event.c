<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Perक्रमmance events support क्रम SH-4A perक्रमmance counters
 *
 *  Copyright (C) 2009, 2010  Paul Mundt
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/processor.h>

#घोषणा PPC_CCBR(idx)	(0xff200800 + (माप(u32) * idx))
#घोषणा PPC_PMCTR(idx)	(0xfc100000 + (माप(u32) * idx))

#घोषणा CCBR_CIT_MASK	(0x7ff << 6)
#घोषणा CCBR_DUC	(1 << 3)
#घोषणा CCBR_CMDS	(1 << 1)
#घोषणा CCBR_PPCE	(1 << 0)

#अगर_घोषित CONFIG_CPU_SHX3
/*
 * The PMCAT location क्रम SH-X3 CPUs was quietly moved, जबतक the CCBR
 * and PMCTR locations reमुख्यs tentatively स्थिरant. This change reमुख्यs
 * wholly unकरोcumented, and was simply found through trial and error.
 *
 * Early cuts of SH-X3 still appear to use the SH-X/SH-X2 locations, and
 * it's unclear when this ceased to be the हाल. For now we always use
 * the new location (अगर future parts keep up with this trend then
 * scanning क्रम them at runसमय also reमुख्यs a viable option.)
 *
 * The gap in the रेजिस्टर space also suggests that there are other
 * unकरोcumented counters, so this will need to be revisited at a later
 * poपूर्णांक in समय.
 */
#घोषणा PPC_PMCAT	0xfc100240
#अन्यथा
#घोषणा PPC_PMCAT	0xfc100080
#पूर्ण_अगर

#घोषणा PMCAT_OVF3	(1 << 27)
#घोषणा PMCAT_CNN3	(1 << 26)
#घोषणा PMCAT_CLR3	(1 << 25)
#घोषणा PMCAT_OVF2	(1 << 19)
#घोषणा PMCAT_CLR2	(1 << 17)
#घोषणा PMCAT_OVF1	(1 << 11)
#घोषणा PMCAT_CNN1	(1 << 10)
#घोषणा PMCAT_CLR1	(1 << 9)
#घोषणा PMCAT_OVF0	(1 << 3)
#घोषणा PMCAT_CLR0	(1 << 1)

अटल काष्ठा sh_pmu sh4a_pmu;

/*
 * Supported raw event codes:
 *
 *	Event Code	Description
 *	----------	-----------
 *
 *	0x0000		number of elapsed cycles
 *	0x0200		number of elapsed cycles in privileged mode
 *	0x0280		number of elapsed cycles जबतक SR.BL is निश्चितed
 *	0x0202		inकाष्ठाion execution
 *	0x0203		inकाष्ठाion execution in parallel
 *	0x0204		number of unconditional branches
 *	0x0208		number of exceptions
 *	0x0209		number of पूर्णांकerrupts
 *	0x0220		UTLB miss caused by inकाष्ठाion fetch
 *	0x0222		UTLB miss caused by opeअक्रम access
 *	0x02a0		number of ITLB misses
 *	0x0028		number of accesses to inकाष्ठाion memories
 *	0x0029		number of accesses to inकाष्ठाion cache
 *	0x002a		inकाष्ठाion cache miss
 *	0x022e		number of access to inकाष्ठाion X/Y memory
 *	0x0030		number of पढ़ोs to opeअक्रम memories
 *	0x0038		number of ग_लिखोs to opeअक्रम memories
 *	0x0031		number of opeअक्रम cache पढ़ो accesses
 *	0x0039		number of opeअक्रम cache ग_लिखो accesses
 *	0x0032		opeअक्रम cache पढ़ो miss
 *	0x003a		opeअक्रम cache ग_लिखो miss
 *	0x0236		number of पढ़ोs to opeअक्रम X/Y memory
 *	0x023e		number of ग_लिखोs to opeअक्रम X/Y memory
 *	0x0237		number of पढ़ोs to opeअक्रम U memory
 *	0x023f		number of ग_लिखोs to opeअक्रम U memory
 *	0x0337		number of U memory पढ़ो buffer misses
 *	0x02b4		number of रुको cycles due to opeअक्रम पढ़ो access
 *	0x02bc		number of रुको cycles due to opeअक्रम ग_लिखो access
 *	0x0033		number of रुको cycles due to opeअक्रम cache पढ़ो miss
 *	0x003b		number of रुको cycles due to opeअक्रम cache ग_लिखो miss
 */

/*
 * Special reserved bits used by hardware emulators, पढ़ो values will
 * vary, but ग_लिखोs must always be 0.
 */
#घोषणा PMCAT_EMU_CLR_MASK	((1 << 24) | (1 << 16) | (1 << 8) | (1 << 0))

अटल स्थिर पूर्णांक sh4a_general_events[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES]		= 0x0000,
	[PERF_COUNT_HW_INSTRUCTIONS]		= 0x0202,
	[PERF_COUNT_HW_CACHE_REFERENCES]	= 0x0029,	/* I-cache */
	[PERF_COUNT_HW_CACHE_MISSES]		= 0x002a,	/* I-cache */
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= 0x0204,
	[PERF_COUNT_HW_BRANCH_MISSES]		= -1,
	[PERF_COUNT_HW_BUS_CYCLES]		= -1,
पूर्ण;

#घोषणा C(x)	PERF_COUNT_HW_CACHE_##x

अटल स्थिर पूर्णांक sh4a_cache_events
			[PERF_COUNT_HW_CACHE_MAX]
			[PERF_COUNT_HW_CACHE_OP_MAX]
			[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
	[ C(L1D) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = 0x0031,
			[ C(RESULT_MISS)   ] = 0x0032,
		पूर्ण,
		[ C(OP_WRITE) ] = अणु
			[ C(RESULT_ACCESS) ] = 0x0039,
			[ C(RESULT_MISS)   ] = 0x003a,
		पूर्ण,
		[ C(OP_PREFETCH) ] = अणु
			[ C(RESULT_ACCESS) ] = 0,
			[ C(RESULT_MISS)   ] = 0,
		पूर्ण,
	पूर्ण,

	[ C(L1I) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = 0x0029,
			[ C(RESULT_MISS)   ] = 0x002a,
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
			[ C(RESULT_ACCESS) ] = 0x0030,
			[ C(RESULT_MISS)   ] = 0,
		पूर्ण,
		[ C(OP_WRITE) ] = अणु
			[ C(RESULT_ACCESS) ] = 0x0038,
			[ C(RESULT_MISS)   ] = 0,
		पूर्ण,
		[ C(OP_PREFETCH) ] = अणु
			[ C(RESULT_ACCESS) ] = 0,
			[ C(RESULT_MISS)   ] = 0,
		पूर्ण,
	पूर्ण,

	[ C(DTLB) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = 0x0222,
			[ C(RESULT_MISS)   ] = 0x0220,
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
			[ C(RESULT_MISS)   ] = 0x02a0,
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

अटल पूर्णांक sh4a_event_map(पूर्णांक event)
अणु
	वापस sh4a_general_events[event];
पूर्ण

अटल u64 sh4a_pmu_पढ़ो(पूर्णांक idx)
अणु
	वापस __raw_पढ़ोl(PPC_PMCTR(idx));
पूर्ण

अटल व्योम sh4a_pmu_disable(काष्ठा hw_perf_event *hwc, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	पंचांगp = __raw_पढ़ोl(PPC_CCBR(idx));
	पंचांगp &= ~(CCBR_CIT_MASK | CCBR_DUC);
	__raw_ग_लिखोl(पंचांगp, PPC_CCBR(idx));
पूर्ण

अटल व्योम sh4a_pmu_enable(काष्ठा hw_perf_event *hwc, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	पंचांगp = __raw_पढ़ोl(PPC_PMCAT);
	पंचांगp &= ~PMCAT_EMU_CLR_MASK;
	पंचांगp |= idx ? PMCAT_CLR1 : PMCAT_CLR0;
	__raw_ग_लिखोl(पंचांगp, PPC_PMCAT);

	पंचांगp = __raw_पढ़ोl(PPC_CCBR(idx));
	पंचांगp |= (hwc->config << 6) | CCBR_CMDS | CCBR_PPCE;
	__raw_ग_लिखोl(पंचांगp, PPC_CCBR(idx));

	__raw_ग_लिखोl(__raw_पढ़ोl(PPC_CCBR(idx)) | CCBR_DUC, PPC_CCBR(idx));
पूर्ण

अटल व्योम sh4a_pmu_disable_all(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sh4a_pmu.num_events; i++)
		__raw_ग_लिखोl(__raw_पढ़ोl(PPC_CCBR(i)) & ~CCBR_DUC, PPC_CCBR(i));
पूर्ण

अटल व्योम sh4a_pmu_enable_all(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sh4a_pmu.num_events; i++)
		__raw_ग_लिखोl(__raw_पढ़ोl(PPC_CCBR(i)) | CCBR_DUC, PPC_CCBR(i));
पूर्ण

अटल काष्ठा sh_pmu sh4a_pmu = अणु
	.name		= "sh4a",
	.num_events	= 2,
	.event_map	= sh4a_event_map,
	.max_events	= ARRAY_SIZE(sh4a_general_events),
	.raw_event_mask	= 0x3ff,
	.cache_events	= &sh4a_cache_events,
	.पढ़ो		= sh4a_pmu_पढ़ो,
	.disable	= sh4a_pmu_disable,
	.enable		= sh4a_pmu_enable,
	.disable_all	= sh4a_pmu_disable_all,
	.enable_all	= sh4a_pmu_enable_all,
पूर्ण;

अटल पूर्णांक __init sh4a_pmu_init(व्योम)
अणु
	/*
	 * Make sure this CPU actually has perf counters.
	 */
	अगर (!(boot_cpu_data.flags & CPU_HAS_PERF_COUNTER)) अणु
		pr_notice("HW perf events unsupported, software events only.\n");
		वापस -ENODEV;
	पूर्ण

	वापस रेजिस्टर_sh_pmu(&sh4a_pmu);
पूर्ण
early_initcall(sh4a_pmu_init);
