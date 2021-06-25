<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2008-2018 Andes Technology Corporation */

#अगर_अघोषित __ASM_PMU_H
#घोषणा __ASM_PMU_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/bitfield.h>

/* Has special meaning क्रम perf core implementation */
#घोषणा HW_OP_UNSUPPORTED		0x0
#घोषणा C(_x)				PERF_COUNT_HW_CACHE_##_x
#घोषणा CACHE_OP_UNSUPPORTED		0x0

/* Enough क्रम both software and hardware defined events */
#घोषणा SOFTWARE_EVENT_MASK		0xFF

#घोषणा PFM_OFFSET_MAGIC_0		2	/* DO NOT START FROM 0 */
#घोषणा PFM_OFFSET_MAGIC_1		(PFM_OFFSET_MAGIC_0 + 36)
#घोषणा PFM_OFFSET_MAGIC_2		(PFM_OFFSET_MAGIC_1 + 36)

क्रमागत अणु PFMC0, PFMC1, PFMC2, MAX_COUNTERS पूर्ण;

u32 PFM_CTL_OVF[3] = अणु PFM_CTL_mskOVF0, PFM_CTL_mskOVF1,
		       PFM_CTL_mskOVF2 पूर्ण;
u32 PFM_CTL_EN[3] = अणु PFM_CTL_mskEN0, PFM_CTL_mskEN1,
		      PFM_CTL_mskEN2 पूर्ण;
u32 PFM_CTL_OFFSEL[3] = अणु PFM_CTL_offSEL0, PFM_CTL_offSEL1,
			  PFM_CTL_offSEL2 पूर्ण;
u32 PFM_CTL_IE[3] = अणु PFM_CTL_mskIE0, PFM_CTL_mskIE1, PFM_CTL_mskIE2 पूर्ण;
u32 PFM_CTL_KS[3] = अणु PFM_CTL_mskKS0, PFM_CTL_mskKS1, PFM_CTL_mskKS2 पूर्ण;
u32 PFM_CTL_KU[3] = अणु PFM_CTL_mskKU0, PFM_CTL_mskKU1, PFM_CTL_mskKU2 पूर्ण;
u32 PFM_CTL_SEL[3] = अणु PFM_CTL_mskSEL0, PFM_CTL_mskSEL1, PFM_CTL_mskSEL2 पूर्ण;
/*
 * Perf Events' indices
 */
#घोषणा NDS32_IDX_CYCLE_COUNTER			0
#घोषणा NDS32_IDX_COUNTER0			1
#घोषणा NDS32_IDX_COUNTER1			2

/* The events क्रम a given PMU रेजिस्टर set. */
काष्ठा pmu_hw_events अणु
	/*
	 * The events that are active on the PMU क्रम the given index.
	 */
	काष्ठा perf_event *events[MAX_COUNTERS];

	/*
	 * A 1 bit क्रम an index indicates that the counter is being used क्रम
	 * an event. A 0 means that the counter can be used.
	 */
	अचिन्हित दीर्घ used_mask[BITS_TO_LONGS(MAX_COUNTERS)];

	/*
	 * Hardware lock to serialize accesses to PMU रेजिस्टरs. Needed क्रम the
	 * पढ़ो/modअगरy/ग_लिखो sequences.
	 */
	raw_spinlock_t pmu_lock;
पूर्ण;

काष्ठा nds32_pmu अणु
	काष्ठा pmu pmu;
	cpumask_t active_irqs;
	अक्षर *name;
	 irqवापस_t (*handle_irq)(पूर्णांक irq_num, व्योम *dev);
	व्योम (*enable)(काष्ठा perf_event *event);
	व्योम (*disable)(काष्ठा perf_event *event);
	पूर्णांक (*get_event_idx)(काष्ठा pmu_hw_events *hw_events,
			     काष्ठा perf_event *event);
	पूर्णांक (*set_event_filter)(काष्ठा hw_perf_event *evt,
				काष्ठा perf_event_attr *attr);
	u32 (*पढ़ो_counter)(काष्ठा perf_event *event);
	व्योम (*ग_लिखो_counter)(काष्ठा perf_event *event, u32 val);
	व्योम (*start)(काष्ठा nds32_pmu *nds32_pmu);
	व्योम (*stop)(काष्ठा nds32_pmu *nds32_pmu);
	व्योम (*reset)(व्योम *data);
	पूर्णांक (*request_irq)(काष्ठा nds32_pmu *nds32_pmu, irq_handler_t handler);
	व्योम (*मुक्त_irq)(काष्ठा nds32_pmu *nds32_pmu);
	पूर्णांक (*map_event)(काष्ठा perf_event *event);
	पूर्णांक num_events;
	atomic_t active_events;
	u64 max_period;
	काष्ठा platक्रमm_device *plat_device;
	काष्ठा pmu_hw_events *(*get_hw_events)(व्योम);
पूर्ण;

#घोषणा to_nds32_pmu(p)			(container_of(p, काष्ठा nds32_pmu, pmu))

पूर्णांक nds32_pmu_रेजिस्टर(काष्ठा nds32_pmu *nds32_pmu, पूर्णांक type);

u64 nds32_pmu_event_update(काष्ठा perf_event *event);

पूर्णांक nds32_pmu_event_set_period(काष्ठा perf_event *event);

/*
 * Common NDS32 SPAv3 event types
 *
 * Note: An implementation may not be able to count all of these events
 * but the encodings are considered to be `reserved' in the हाल that
 * they are not available.
 *
 * SEL_TOTAL_CYCLES will add an offset is due to ZERO is defined as
 * NOT_SUPPORTED EVENT mapping in generic perf code.
 * You will need to deal it in the event writing implementation.
 */
क्रमागत spav3_counter_0_perf_types अणु
	SPAV3_0_SEL_BASE = -1 + PFM_OFFSET_MAGIC_0,	/* counting symbol */
	SPAV3_0_SEL_TOTAL_CYCLES = 0 + PFM_OFFSET_MAGIC_0,
	SPAV3_0_SEL_COMPLETED_INSTRUCTION = 1 + PFM_OFFSET_MAGIC_0,
	SPAV3_0_SEL_LAST	/* counting symbol */
पूर्ण;

क्रमागत spav3_counter_1_perf_types अणु
	SPAV3_1_SEL_BASE = -1 + PFM_OFFSET_MAGIC_1,	/* counting symbol */
	SPAV3_1_SEL_TOTAL_CYCLES = 0 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_COMPLETED_INSTRUCTION = 1 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_CONDITIONAL_BRANCH = 2 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_TAKEN_CONDITIONAL_BRANCH = 3 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_PREFETCH_INSTRUCTION = 4 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_RET_INST = 5 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_JR_INST = 6 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_JAL_JRAL_INST = 7 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_NOP_INST = 8 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_SCW_INST = 9 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_ISB_DSB_INST = 10 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_CCTL_INST = 11 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_TAKEN_INTERRUPTS = 12 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_LOADS_COMPLETED = 13 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_UITLB_ACCESS = 14 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_UDTLB_ACCESS = 15 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_MTLB_ACCESS = 16 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_CODE_CACHE_ACCESS = 17 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_DATA_DEPENDENCY_STALL_CYCLES = 18 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_DATA_CACHE_MISS_STALL_CYCLES = 19 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_DATA_CACHE_ACCESS = 20 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_DATA_CACHE_MISS = 21 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_LOAD_DATA_CACHE_ACCESS = 22 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_STORE_DATA_CACHE_ACCESS = 23 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_ILM_ACCESS = 24 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_LSU_BIU_CYCLES = 25 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_HPTWK_BIU_CYCLES = 26 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_DMA_BIU_CYCLES = 27 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_CODE_CACHE_FILL_BIU_CYCLES = 28 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_LEGAL_UNALIGN_DCACHE_ACCESS = 29 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_PUSH25 = 30 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_SYSCALLS_INST = 31 + PFM_OFFSET_MAGIC_1,
	SPAV3_1_SEL_LAST	/* counting symbol */
पूर्ण;

क्रमागत spav3_counter_2_perf_types अणु
	SPAV3_2_SEL_BASE = -1 + PFM_OFFSET_MAGIC_2,	/* counting symbol */
	SPAV3_2_SEL_TOTAL_CYCLES = 0 + PFM_OFFSET_MAGIC_2,
	SPAV3_2_SEL_COMPLETED_INSTRUCTION = 1 + PFM_OFFSET_MAGIC_2,
	SPAV3_2_SEL_CONDITIONAL_BRANCH_MISPREDICT = 2 + PFM_OFFSET_MAGIC_2,
	SPAV3_2_SEL_TAKEN_CONDITIONAL_BRANCH_MISPREDICT =
	    3 + PFM_OFFSET_MAGIC_2,
	SPAV3_2_SEL_PREFETCH_INSTRUCTION_CACHE_HIT = 4 + PFM_OFFSET_MAGIC_2,
	SPAV3_1_SEL_RET_MISPREDICT = 5 + PFM_OFFSET_MAGIC_2,
	SPAV3_1_SEL_IMMEDIATE_J_INST = 6 + PFM_OFFSET_MAGIC_2,
	SPAV3_1_SEL_MULTIPLY_INST = 7 + PFM_OFFSET_MAGIC_2,
	SPAV3_1_SEL_16_BIT_INST = 8 + PFM_OFFSET_MAGIC_2,
	SPAV3_1_SEL_FAILED_SCW_INST = 9 + PFM_OFFSET_MAGIC_2,
	SPAV3_1_SEL_LD_AFTER_ST_CONFLICT_REPLAYS = 10 + PFM_OFFSET_MAGIC_2,
	SPAV3_1_SEL_TAKEN_EXCEPTIONS = 12 + PFM_OFFSET_MAGIC_2,
	SPAV3_1_SEL_STORES_COMPLETED = 13 + PFM_OFFSET_MAGIC_2,
	SPAV3_2_SEL_UITLB_MISS = 14 + PFM_OFFSET_MAGIC_2,
	SPAV3_2_SEL_UDTLB_MISS = 15 + PFM_OFFSET_MAGIC_2,
	SPAV3_2_SEL_MTLB_MISS = 16 + PFM_OFFSET_MAGIC_2,
	SPAV3_2_SEL_CODE_CACHE_MISS = 17 + PFM_OFFSET_MAGIC_2,
	SPAV3_1_SEL_EMPTY_INST_QUEUE_STALL_CYCLES = 18 + PFM_OFFSET_MAGIC_2,
	SPAV3_1_SEL_DATA_WRITE_BACK = 19 + PFM_OFFSET_MAGIC_2,
	SPAV3_2_SEL_DATA_CACHE_MISS = 21 + PFM_OFFSET_MAGIC_2,
	SPAV3_2_SEL_LOAD_DATA_CACHE_MISS = 22 + PFM_OFFSET_MAGIC_2,
	SPAV3_2_SEL_STORE_DATA_CACHE_MISS = 23 + PFM_OFFSET_MAGIC_2,
	SPAV3_1_SEL_DLM_ACCESS = 24 + PFM_OFFSET_MAGIC_2,
	SPAV3_1_SEL_LSU_BIU_REQUEST = 25 + PFM_OFFSET_MAGIC_2,
	SPAV3_1_SEL_HPTWK_BIU_REQUEST = 26 + PFM_OFFSET_MAGIC_2,
	SPAV3_1_SEL_DMA_BIU_REQUEST = 27 + PFM_OFFSET_MAGIC_2,
	SPAV3_1_SEL_CODE_CACHE_FILL_BIU_REQUEST = 28 + PFM_OFFSET_MAGIC_2,
	SPAV3_1_SEL_EXTERNAL_EVENTS = 29 + PFM_OFFSET_MAGIC_2,
	SPAV3_1_SEL_POP25 = 30 + PFM_OFFSET_MAGIC_2,
	SPAV3_2_SEL_LAST	/* counting symbol */
पूर्ण;

/* Get converted event counter index */
अटल अंतरभूत पूर्णांक get_converted_event_idx(अचिन्हित दीर्घ event)
अणु
	पूर्णांक idx;

	अगर ((event) > SPAV3_0_SEL_BASE && event < SPAV3_0_SEL_LAST) अणु
		idx = 0;
	पूर्ण अन्यथा अगर ((event) > SPAV3_1_SEL_BASE && event < SPAV3_1_SEL_LAST) अणु
		idx = 1;
	पूर्ण अन्यथा अगर ((event) > SPAV3_2_SEL_BASE && event < SPAV3_2_SEL_LAST) अणु
		idx = 2;
	पूर्ण अन्यथा अणु
		pr_err("GET_CONVERTED_EVENT_IDX PFM counter range error\n");
		वापस -EPERM;
	पूर्ण

	वापस idx;
पूर्ण

/* Get converted hardware event number */
अटल अंतरभूत u32 get_converted_evet_hw_num(u32 event)
अणु
	अगर (event > SPAV3_0_SEL_BASE && event < SPAV3_0_SEL_LAST)
		event -= PFM_OFFSET_MAGIC_0;
	अन्यथा अगर (event > SPAV3_1_SEL_BASE && event < SPAV3_1_SEL_LAST)
		event -= PFM_OFFSET_MAGIC_1;
	अन्यथा अगर (event > SPAV3_2_SEL_BASE && event < SPAV3_2_SEL_LAST)
		event -= PFM_OFFSET_MAGIC_2;
	अन्यथा अगर (event != 0)
		pr_err("GET_CONVERTED_EVENT_HW_NUM PFM counter range error\n");

	वापस event;
पूर्ण

/*
 * NDS32 HW events mapping
 *
 * The hardware events that we support. We करो support cache operations but
 * we have harvard caches and no way to combine inकाष्ठाion and data
 * accesses/misses in hardware.
 */
अटल स्थिर अचिन्हित पूर्णांक nds32_pfm_perf_map[PERF_COUNT_HW_MAX] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] = SPAV3_0_SEL_TOTAL_CYCLES,
	[PERF_COUNT_HW_INSTRUCTIONS] = SPAV3_1_SEL_COMPLETED_INSTRUCTION,
	[PERF_COUNT_HW_CACHE_REFERENCES] = SPAV3_1_SEL_DATA_CACHE_ACCESS,
	[PERF_COUNT_HW_CACHE_MISSES] = SPAV3_2_SEL_DATA_CACHE_MISS,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = HW_OP_UNSUPPORTED,
	[PERF_COUNT_HW_BRANCH_MISSES] = HW_OP_UNSUPPORTED,
	[PERF_COUNT_HW_BUS_CYCLES] = HW_OP_UNSUPPORTED,
	[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND] = HW_OP_UNSUPPORTED,
	[PERF_COUNT_HW_STALLED_CYCLES_BACKEND] = HW_OP_UNSUPPORTED,
	[PERF_COUNT_HW_REF_CPU_CYCLES] = HW_OP_UNSUPPORTED
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक nds32_pfm_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
	[PERF_COUNT_HW_CACHE_OP_MAX]
	[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	[C(L1D)] = अणु
		    [C(OP_READ)] = अणु
				    [C(RESULT_ACCESS)] =
				    SPAV3_1_SEL_LOAD_DATA_CACHE_ACCESS,
				    [C(RESULT_MISS)] =
				    SPAV3_2_SEL_LOAD_DATA_CACHE_MISS,
				    पूर्ण,
		    [C(OP_WRITE)] = अणु
				     [C(RESULT_ACCESS)] =
				     SPAV3_1_SEL_STORE_DATA_CACHE_ACCESS,
				     [C(RESULT_MISS)] =
				     SPAV3_2_SEL_STORE_DATA_CACHE_MISS,
				     पूर्ण,
		    [C(OP_PREFETCH)] = अणु
					[C(RESULT_ACCESS)] =
						CACHE_OP_UNSUPPORTED,
					[C(RESULT_MISS)] =
						CACHE_OP_UNSUPPORTED,
					पूर्ण,
		    पूर्ण,
	[C(L1I)] = अणु
		    [C(OP_READ)] = अणु
				    [C(RESULT_ACCESS)] =
				    SPAV3_1_SEL_CODE_CACHE_ACCESS,
				    [C(RESULT_MISS)] =
				    SPAV3_2_SEL_CODE_CACHE_MISS,
				    पूर्ण,
		    [C(OP_WRITE)] = अणु
				     [C(RESULT_ACCESS)] =
				     SPAV3_1_SEL_CODE_CACHE_ACCESS,
				     [C(RESULT_MISS)] =
				     SPAV3_2_SEL_CODE_CACHE_MISS,
				     पूर्ण,
		    [C(OP_PREFETCH)] = अणु
					[C(RESULT_ACCESS)] =
					CACHE_OP_UNSUPPORTED,
					[C(RESULT_MISS)] = CACHE_OP_UNSUPPORTED,
					पूर्ण,
		    पूर्ण,
	/* TODO: L2CC */
	[C(LL)] = अणु
		   [C(OP_READ)] = अणु
				   [C(RESULT_ACCESS)] = CACHE_OP_UNSUPPORTED,
				   [C(RESULT_MISS)] = CACHE_OP_UNSUPPORTED,
				   पूर्ण,
		   [C(OP_WRITE)] = अणु
				    [C(RESULT_ACCESS)] = CACHE_OP_UNSUPPORTED,
				    [C(RESULT_MISS)] = CACHE_OP_UNSUPPORTED,
				    पूर्ण,
		   [C(OP_PREFETCH)] = अणु
				       [C(RESULT_ACCESS)] =
				       CACHE_OP_UNSUPPORTED,
				       [C(RESULT_MISS)] = CACHE_OP_UNSUPPORTED,
				       पूर्ण,
		   पूर्ण,
	/* NDS32 PMU करोes not support TLB पढ़ो/ग_लिखो hit/miss,
	 * However, it can count access/miss, which mixed with पढ़ो and ग_लिखो.
	 * Thereक्रमe, only READ counter will use it.
	 * We करो as possible as we can.
	 */
	[C(DTLB)] = अणु
		     [C(OP_READ)] = अणु
				     [C(RESULT_ACCESS)] =
					SPAV3_1_SEL_UDTLB_ACCESS,
				     [C(RESULT_MISS)] =
					SPAV3_2_SEL_UDTLB_MISS,
				     पूर्ण,
		     [C(OP_WRITE)] = अणु
				      [C(RESULT_ACCESS)] = CACHE_OP_UNSUPPORTED,
				      [C(RESULT_MISS)] = CACHE_OP_UNSUPPORTED,
				      पूर्ण,
		     [C(OP_PREFETCH)] = अणु
					 [C(RESULT_ACCESS)] =
					 CACHE_OP_UNSUPPORTED,
					 [C(RESULT_MISS)] =
					 CACHE_OP_UNSUPPORTED,
					 पूर्ण,
		     पूर्ण,
	[C(ITLB)] = अणु
		     [C(OP_READ)] = अणु
				     [C(RESULT_ACCESS)] =
					SPAV3_1_SEL_UITLB_ACCESS,
				     [C(RESULT_MISS)] =
					SPAV3_2_SEL_UITLB_MISS,
				     पूर्ण,
		     [C(OP_WRITE)] = अणु
				      [C(RESULT_ACCESS)] =
					CACHE_OP_UNSUPPORTED,
				      [C(RESULT_MISS)] =
					CACHE_OP_UNSUPPORTED,
				      पूर्ण,
		     [C(OP_PREFETCH)] = अणु
					 [C(RESULT_ACCESS)] =
						CACHE_OP_UNSUPPORTED,
					 [C(RESULT_MISS)] =
						CACHE_OP_UNSUPPORTED,
					 पूर्ण,
		     पूर्ण,
	[C(BPU)] = अणु		/* What is BPU? */
		    [C(OP_READ)] = अणु
				    [C(RESULT_ACCESS)] =
					CACHE_OP_UNSUPPORTED,
				    [C(RESULT_MISS)] =
					CACHE_OP_UNSUPPORTED,
				    पूर्ण,
		    [C(OP_WRITE)] = अणु
				     [C(RESULT_ACCESS)] =
					CACHE_OP_UNSUPPORTED,
				     [C(RESULT_MISS)] =
					CACHE_OP_UNSUPPORTED,
				     पूर्ण,
		    [C(OP_PREFETCH)] = अणु
					[C(RESULT_ACCESS)] =
						CACHE_OP_UNSUPPORTED,
					[C(RESULT_MISS)] =
						CACHE_OP_UNSUPPORTED,
					पूर्ण,
		    पूर्ण,
	[C(NODE)] = अणु		/* What is NODE? */
		     [C(OP_READ)] = अणु
				     [C(RESULT_ACCESS)] = CACHE_OP_UNSUPPORTED,
				     [C(RESULT_MISS)] = CACHE_OP_UNSUPPORTED,
				     पूर्ण,
		     [C(OP_WRITE)] = अणु
				      [C(RESULT_ACCESS)] = CACHE_OP_UNSUPPORTED,
				      [C(RESULT_MISS)] = CACHE_OP_UNSUPPORTED,
				      पूर्ण,
		     [C(OP_PREFETCH)] = अणु
					 [C(RESULT_ACCESS)] =
						CACHE_OP_UNSUPPORTED,
					 [C(RESULT_MISS)] =
						CACHE_OP_UNSUPPORTED,
					 पूर्ण,
		     पूर्ण,
पूर्ण;

पूर्णांक nds32_pmu_map_event(काष्ठा perf_event *event,
			स्थिर अचिन्हित पूर्णांक (*event_map)[PERF_COUNT_HW_MAX],
			स्थिर अचिन्हित पूर्णांक (*cache_map)[PERF_COUNT_HW_CACHE_MAX]
			[PERF_COUNT_HW_CACHE_OP_MAX]
			[PERF_COUNT_HW_CACHE_RESULT_MAX], u32 raw_event_mask);

#पूर्ण_अगर /* __ASM_PMU_H */
