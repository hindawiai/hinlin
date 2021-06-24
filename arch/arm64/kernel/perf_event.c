<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARMv8 PMUv3 Perक्रमmance Events handling code.
 *
 * Copyright (C) 2012 ARM Limited
 * Author: Will Deacon <will.deacon@arm.com>
 *
 * This code is based heavily on the ARMv7 perf event code.
 */

#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/perf_event.h>
#समावेश <यंत्र/sysreg.h>
#समावेश <यंत्र/virt.h>

#समावेश <घड़ीsource/arm_arch_समयr.h>

#समावेश <linux/acpi.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/of.h>
#समावेश <linux/perf/arm_pmu.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/smp.h>

/* ARMv8 Cortex-A53 specअगरic event types. */
#घोषणा ARMV8_A53_PERFCTR_PREF_LINEFILL				0xC2

/* ARMv8 Cavium ThunderX specअगरic event types. */
#घोषणा ARMV8_THUNDER_PERFCTR_L1D_CACHE_MISS_ST			0xE9
#घोषणा ARMV8_THUNDER_PERFCTR_L1D_CACHE_PREF_ACCESS		0xEA
#घोषणा ARMV8_THUNDER_PERFCTR_L1D_CACHE_PREF_MISS		0xEB
#घोषणा ARMV8_THUNDER_PERFCTR_L1I_CACHE_PREF_ACCESS		0xEC
#घोषणा ARMV8_THUNDER_PERFCTR_L1I_CACHE_PREF_MISS		0xED

/*
 * ARMv8 Architectural defined events, not all of these may
 * be supported on any given implementation. Unsupported events will
 * be disabled at run-समय based on the PMCEID रेजिस्टरs.
 */
अटल स्थिर अचिन्हित armv8_pmuv3_perf_map[PERF_COUNT_HW_MAX] = अणु
	PERF_MAP_ALL_UNSUPPORTED,
	[PERF_COUNT_HW_CPU_CYCLES]		= ARMV8_PMUV3_PERFCTR_CPU_CYCLES,
	[PERF_COUNT_HW_INSTRUCTIONS]		= ARMV8_PMUV3_PERFCTR_INST_RETIRED,
	[PERF_COUNT_HW_CACHE_REFERENCES]	= ARMV8_PMUV3_PERFCTR_L1D_CACHE,
	[PERF_COUNT_HW_CACHE_MISSES]		= ARMV8_PMUV3_PERFCTR_L1D_CACHE_REFILL,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= ARMV8_PMUV3_PERFCTR_PC_WRITE_RETIRED,
	[PERF_COUNT_HW_BRANCH_MISSES]		= ARMV8_PMUV3_PERFCTR_BR_MIS_PRED,
	[PERF_COUNT_HW_BUS_CYCLES]		= ARMV8_PMUV3_PERFCTR_BUS_CYCLES,
	[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND]	= ARMV8_PMUV3_PERFCTR_STALL_FRONTEND,
	[PERF_COUNT_HW_STALLED_CYCLES_BACKEND]	= ARMV8_PMUV3_PERFCTR_STALL_BACKEND,
पूर्ण;

अटल स्थिर अचिन्हित armv8_pmuv3_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
						[PERF_COUNT_HW_CACHE_OP_MAX]
						[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	PERF_CACHE_MAP_ALL_UNSUPPORTED,

	[C(L1D)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV8_PMUV3_PERFCTR_L1D_CACHE,
	[C(L1D)][C(OP_READ)][C(RESULT_MISS)]	= ARMV8_PMUV3_PERFCTR_L1D_CACHE_REFILL,

	[C(L1I)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV8_PMUV3_PERFCTR_L1I_CACHE,
	[C(L1I)][C(OP_READ)][C(RESULT_MISS)]	= ARMV8_PMUV3_PERFCTR_L1I_CACHE_REFILL,

	[C(DTLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV8_PMUV3_PERFCTR_L1D_TLB_REFILL,
	[C(DTLB)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV8_PMUV3_PERFCTR_L1D_TLB,

	[C(ITLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV8_PMUV3_PERFCTR_L1I_TLB_REFILL,
	[C(ITLB)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV8_PMUV3_PERFCTR_L1I_TLB,

	[C(LL)][C(OP_READ)][C(RESULT_MISS)]	= ARMV8_PMUV3_PERFCTR_LL_CACHE_MISS_RD,
	[C(LL)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV8_PMUV3_PERFCTR_LL_CACHE_RD,

	[C(BPU)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV8_PMUV3_PERFCTR_BR_PRED,
	[C(BPU)][C(OP_READ)][C(RESULT_MISS)]	= ARMV8_PMUV3_PERFCTR_BR_MIS_PRED,
पूर्ण;

अटल स्थिर अचिन्हित armv8_a53_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
					      [PERF_COUNT_HW_CACHE_OP_MAX]
					      [PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	PERF_CACHE_MAP_ALL_UNSUPPORTED,

	[C(L1D)][C(OP_PREFETCH)][C(RESULT_MISS)] = ARMV8_A53_PERFCTR_PREF_LINEFILL,

	[C(NODE)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV8_IMPDEF_PERFCTR_BUS_ACCESS_RD,
	[C(NODE)][C(OP_WRITE)][C(RESULT_ACCESS)] = ARMV8_IMPDEF_PERFCTR_BUS_ACCESS_WR,
पूर्ण;

अटल स्थिर अचिन्हित armv8_a57_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
					      [PERF_COUNT_HW_CACHE_OP_MAX]
					      [PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	PERF_CACHE_MAP_ALL_UNSUPPORTED,

	[C(L1D)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV8_IMPDEF_PERFCTR_L1D_CACHE_RD,
	[C(L1D)][C(OP_READ)][C(RESULT_MISS)]	= ARMV8_IMPDEF_PERFCTR_L1D_CACHE_REFILL_RD,
	[C(L1D)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV8_IMPDEF_PERFCTR_L1D_CACHE_WR,
	[C(L1D)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV8_IMPDEF_PERFCTR_L1D_CACHE_REFILL_WR,

	[C(DTLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV8_IMPDEF_PERFCTR_L1D_TLB_REFILL_RD,
	[C(DTLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV8_IMPDEF_PERFCTR_L1D_TLB_REFILL_WR,

	[C(NODE)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV8_IMPDEF_PERFCTR_BUS_ACCESS_RD,
	[C(NODE)][C(OP_WRITE)][C(RESULT_ACCESS)] = ARMV8_IMPDEF_PERFCTR_BUS_ACCESS_WR,
पूर्ण;

अटल स्थिर अचिन्हित armv8_a73_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
					      [PERF_COUNT_HW_CACHE_OP_MAX]
					      [PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	PERF_CACHE_MAP_ALL_UNSUPPORTED,

	[C(L1D)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV8_IMPDEF_PERFCTR_L1D_CACHE_RD,
	[C(L1D)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV8_IMPDEF_PERFCTR_L1D_CACHE_WR,
पूर्ण;

अटल स्थिर अचिन्हित armv8_thunder_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
						   [PERF_COUNT_HW_CACHE_OP_MAX]
						   [PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	PERF_CACHE_MAP_ALL_UNSUPPORTED,

	[C(L1D)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV8_IMPDEF_PERFCTR_L1D_CACHE_RD,
	[C(L1D)][C(OP_READ)][C(RESULT_MISS)]	= ARMV8_IMPDEF_PERFCTR_L1D_CACHE_REFILL_RD,
	[C(L1D)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV8_IMPDEF_PERFCTR_L1D_CACHE_WR,
	[C(L1D)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV8_THUNDER_PERFCTR_L1D_CACHE_MISS_ST,
	[C(L1D)][C(OP_PREFETCH)][C(RESULT_ACCESS)] = ARMV8_THUNDER_PERFCTR_L1D_CACHE_PREF_ACCESS,
	[C(L1D)][C(OP_PREFETCH)][C(RESULT_MISS)] = ARMV8_THUNDER_PERFCTR_L1D_CACHE_PREF_MISS,

	[C(L1I)][C(OP_PREFETCH)][C(RESULT_ACCESS)] = ARMV8_THUNDER_PERFCTR_L1I_CACHE_PREF_ACCESS,
	[C(L1I)][C(OP_PREFETCH)][C(RESULT_MISS)] = ARMV8_THUNDER_PERFCTR_L1I_CACHE_PREF_MISS,

	[C(DTLB)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV8_IMPDEF_PERFCTR_L1D_TLB_RD,
	[C(DTLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV8_IMPDEF_PERFCTR_L1D_TLB_REFILL_RD,
	[C(DTLB)][C(OP_WRITE)][C(RESULT_ACCESS)] = ARMV8_IMPDEF_PERFCTR_L1D_TLB_WR,
	[C(DTLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV8_IMPDEF_PERFCTR_L1D_TLB_REFILL_WR,
पूर्ण;

अटल स्थिर अचिन्हित armv8_vulcan_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
					      [PERF_COUNT_HW_CACHE_OP_MAX]
					      [PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	PERF_CACHE_MAP_ALL_UNSUPPORTED,

	[C(L1D)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV8_IMPDEF_PERFCTR_L1D_CACHE_RD,
	[C(L1D)][C(OP_READ)][C(RESULT_MISS)]	= ARMV8_IMPDEF_PERFCTR_L1D_CACHE_REFILL_RD,
	[C(L1D)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV8_IMPDEF_PERFCTR_L1D_CACHE_WR,
	[C(L1D)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV8_IMPDEF_PERFCTR_L1D_CACHE_REFILL_WR,

	[C(DTLB)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV8_IMPDEF_PERFCTR_L1D_TLB_RD,
	[C(DTLB)][C(OP_WRITE)][C(RESULT_ACCESS)] = ARMV8_IMPDEF_PERFCTR_L1D_TLB_WR,
	[C(DTLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV8_IMPDEF_PERFCTR_L1D_TLB_REFILL_RD,
	[C(DTLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV8_IMPDEF_PERFCTR_L1D_TLB_REFILL_WR,

	[C(NODE)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV8_IMPDEF_PERFCTR_BUS_ACCESS_RD,
	[C(NODE)][C(OP_WRITE)][C(RESULT_ACCESS)] = ARMV8_IMPDEF_PERFCTR_BUS_ACCESS_WR,
पूर्ण;

अटल sमाप_प्रकार
armv8pmu_events_sysfs_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *page)
अणु
	काष्ठा perf_pmu_events_attr *pmu_attr;

	pmu_attr = container_of(attr, काष्ठा perf_pmu_events_attr, attr);

	वापस प्र_लिखो(page, "event=0x%04llx\n", pmu_attr->id);
पूर्ण

#घोषणा ARMV8_EVENT_ATTR(name, config)						\
	(&((काष्ठा perf_pmu_events_attr) अणु					\
		.attr = __ATTR(name, 0444, armv8pmu_events_sysfs_show, शून्य),	\
		.id = config,							\
	पूर्ण).attr.attr)

अटल काष्ठा attribute *armv8_pmuv3_event_attrs[] = अणु
	ARMV8_EVENT_ATTR(sw_incr, ARMV8_PMUV3_PERFCTR_SW_INCR),
	ARMV8_EVENT_ATTR(l1i_cache_refill, ARMV8_PMUV3_PERFCTR_L1I_CACHE_REFILL),
	ARMV8_EVENT_ATTR(l1i_tlb_refill, ARMV8_PMUV3_PERFCTR_L1I_TLB_REFILL),
	ARMV8_EVENT_ATTR(l1d_cache_refill, ARMV8_PMUV3_PERFCTR_L1D_CACHE_REFILL),
	ARMV8_EVENT_ATTR(l1d_cache, ARMV8_PMUV3_PERFCTR_L1D_CACHE),
	ARMV8_EVENT_ATTR(l1d_tlb_refill, ARMV8_PMUV3_PERFCTR_L1D_TLB_REFILL),
	ARMV8_EVENT_ATTR(ld_retired, ARMV8_PMUV3_PERFCTR_LD_RETIRED),
	ARMV8_EVENT_ATTR(st_retired, ARMV8_PMUV3_PERFCTR_ST_RETIRED),
	ARMV8_EVENT_ATTR(inst_retired, ARMV8_PMUV3_PERFCTR_INST_RETIRED),
	ARMV8_EVENT_ATTR(exc_taken, ARMV8_PMUV3_PERFCTR_EXC_TAKEN),
	ARMV8_EVENT_ATTR(exc_वापस, ARMV8_PMUV3_PERFCTR_EXC_RETURN),
	ARMV8_EVENT_ATTR(cid_ग_लिखो_retired, ARMV8_PMUV3_PERFCTR_CID_WRITE_RETIRED),
	ARMV8_EVENT_ATTR(pc_ग_लिखो_retired, ARMV8_PMUV3_PERFCTR_PC_WRITE_RETIRED),
	ARMV8_EVENT_ATTR(br_immed_retired, ARMV8_PMUV3_PERFCTR_BR_IMMED_RETIRED),
	ARMV8_EVENT_ATTR(br_वापस_retired, ARMV8_PMUV3_PERFCTR_BR_RETURN_RETIRED),
	ARMV8_EVENT_ATTR(unaligned_ldst_retired, ARMV8_PMUV3_PERFCTR_UNALIGNED_LDST_RETIRED),
	ARMV8_EVENT_ATTR(br_mis_pred, ARMV8_PMUV3_PERFCTR_BR_MIS_PRED),
	ARMV8_EVENT_ATTR(cpu_cycles, ARMV8_PMUV3_PERFCTR_CPU_CYCLES),
	ARMV8_EVENT_ATTR(br_pred, ARMV8_PMUV3_PERFCTR_BR_PRED),
	ARMV8_EVENT_ATTR(mem_access, ARMV8_PMUV3_PERFCTR_MEM_ACCESS),
	ARMV8_EVENT_ATTR(l1i_cache, ARMV8_PMUV3_PERFCTR_L1I_CACHE),
	ARMV8_EVENT_ATTR(l1d_cache_wb, ARMV8_PMUV3_PERFCTR_L1D_CACHE_WB),
	ARMV8_EVENT_ATTR(l2d_cache, ARMV8_PMUV3_PERFCTR_L2D_CACHE),
	ARMV8_EVENT_ATTR(l2d_cache_refill, ARMV8_PMUV3_PERFCTR_L2D_CACHE_REFILL),
	ARMV8_EVENT_ATTR(l2d_cache_wb, ARMV8_PMUV3_PERFCTR_L2D_CACHE_WB),
	ARMV8_EVENT_ATTR(bus_access, ARMV8_PMUV3_PERFCTR_BUS_ACCESS),
	ARMV8_EVENT_ATTR(memory_error, ARMV8_PMUV3_PERFCTR_MEMORY_ERROR),
	ARMV8_EVENT_ATTR(inst_spec, ARMV8_PMUV3_PERFCTR_INST_SPEC),
	ARMV8_EVENT_ATTR(ttbr_ग_लिखो_retired, ARMV8_PMUV3_PERFCTR_TTBR_WRITE_RETIRED),
	ARMV8_EVENT_ATTR(bus_cycles, ARMV8_PMUV3_PERFCTR_BUS_CYCLES),
	/* Don't expose the chain event in /sys, since it's useless in isolation */
	ARMV8_EVENT_ATTR(l1d_cache_allocate, ARMV8_PMUV3_PERFCTR_L1D_CACHE_ALLOCATE),
	ARMV8_EVENT_ATTR(l2d_cache_allocate, ARMV8_PMUV3_PERFCTR_L2D_CACHE_ALLOCATE),
	ARMV8_EVENT_ATTR(br_retired, ARMV8_PMUV3_PERFCTR_BR_RETIRED),
	ARMV8_EVENT_ATTR(br_mis_pred_retired, ARMV8_PMUV3_PERFCTR_BR_MIS_PRED_RETIRED),
	ARMV8_EVENT_ATTR(stall_frontend, ARMV8_PMUV3_PERFCTR_STALL_FRONTEND),
	ARMV8_EVENT_ATTR(stall_backend, ARMV8_PMUV3_PERFCTR_STALL_BACKEND),
	ARMV8_EVENT_ATTR(l1d_tlb, ARMV8_PMUV3_PERFCTR_L1D_TLB),
	ARMV8_EVENT_ATTR(l1i_tlb, ARMV8_PMUV3_PERFCTR_L1I_TLB),
	ARMV8_EVENT_ATTR(l2i_cache, ARMV8_PMUV3_PERFCTR_L2I_CACHE),
	ARMV8_EVENT_ATTR(l2i_cache_refill, ARMV8_PMUV3_PERFCTR_L2I_CACHE_REFILL),
	ARMV8_EVENT_ATTR(l3d_cache_allocate, ARMV8_PMUV3_PERFCTR_L3D_CACHE_ALLOCATE),
	ARMV8_EVENT_ATTR(l3d_cache_refill, ARMV8_PMUV3_PERFCTR_L3D_CACHE_REFILL),
	ARMV8_EVENT_ATTR(l3d_cache, ARMV8_PMUV3_PERFCTR_L3D_CACHE),
	ARMV8_EVENT_ATTR(l3d_cache_wb, ARMV8_PMUV3_PERFCTR_L3D_CACHE_WB),
	ARMV8_EVENT_ATTR(l2d_tlb_refill, ARMV8_PMUV3_PERFCTR_L2D_TLB_REFILL),
	ARMV8_EVENT_ATTR(l2i_tlb_refill, ARMV8_PMUV3_PERFCTR_L2I_TLB_REFILL),
	ARMV8_EVENT_ATTR(l2d_tlb, ARMV8_PMUV3_PERFCTR_L2D_TLB),
	ARMV8_EVENT_ATTR(l2i_tlb, ARMV8_PMUV3_PERFCTR_L2I_TLB),
	ARMV8_EVENT_ATTR(remote_access, ARMV8_PMUV3_PERFCTR_REMOTE_ACCESS),
	ARMV8_EVENT_ATTR(ll_cache, ARMV8_PMUV3_PERFCTR_LL_CACHE),
	ARMV8_EVENT_ATTR(ll_cache_miss, ARMV8_PMUV3_PERFCTR_LL_CACHE_MISS),
	ARMV8_EVENT_ATTR(dtlb_walk, ARMV8_PMUV3_PERFCTR_DTLB_WALK),
	ARMV8_EVENT_ATTR(itlb_walk, ARMV8_PMUV3_PERFCTR_ITLB_WALK),
	ARMV8_EVENT_ATTR(ll_cache_rd, ARMV8_PMUV3_PERFCTR_LL_CACHE_RD),
	ARMV8_EVENT_ATTR(ll_cache_miss_rd, ARMV8_PMUV3_PERFCTR_LL_CACHE_MISS_RD),
	ARMV8_EVENT_ATTR(remote_access_rd, ARMV8_PMUV3_PERFCTR_REMOTE_ACCESS_RD),
	ARMV8_EVENT_ATTR(l1d_cache_lmiss_rd, ARMV8_PMUV3_PERFCTR_L1D_CACHE_LMISS_RD),
	ARMV8_EVENT_ATTR(op_retired, ARMV8_PMUV3_PERFCTR_OP_RETIRED),
	ARMV8_EVENT_ATTR(op_spec, ARMV8_PMUV3_PERFCTR_OP_SPEC),
	ARMV8_EVENT_ATTR(stall, ARMV8_PMUV3_PERFCTR_STALL),
	ARMV8_EVENT_ATTR(stall_slot_backend, ARMV8_PMUV3_PERFCTR_STALL_SLOT_BACKEND),
	ARMV8_EVENT_ATTR(stall_slot_frontend, ARMV8_PMUV3_PERFCTR_STALL_SLOT_FRONTEND),
	ARMV8_EVENT_ATTR(stall_slot, ARMV8_PMUV3_PERFCTR_STALL_SLOT),
	ARMV8_EVENT_ATTR(sample_pop, ARMV8_SPE_PERFCTR_SAMPLE_POP),
	ARMV8_EVENT_ATTR(sample_feed, ARMV8_SPE_PERFCTR_SAMPLE_FEED),
	ARMV8_EVENT_ATTR(sample_filtrate, ARMV8_SPE_PERFCTR_SAMPLE_FILTRATE),
	ARMV8_EVENT_ATTR(sample_collision, ARMV8_SPE_PERFCTR_SAMPLE_COLLISION),
	ARMV8_EVENT_ATTR(cnt_cycles, ARMV8_AMU_PERFCTR_CNT_CYCLES),
	ARMV8_EVENT_ATTR(stall_backend_mem, ARMV8_AMU_PERFCTR_STALL_BACKEND_MEM),
	ARMV8_EVENT_ATTR(l1i_cache_lmiss, ARMV8_PMUV3_PERFCTR_L1I_CACHE_LMISS),
	ARMV8_EVENT_ATTR(l2d_cache_lmiss_rd, ARMV8_PMUV3_PERFCTR_L2D_CACHE_LMISS_RD),
	ARMV8_EVENT_ATTR(l2i_cache_lmiss, ARMV8_PMUV3_PERFCTR_L2I_CACHE_LMISS),
	ARMV8_EVENT_ATTR(l3d_cache_lmiss_rd, ARMV8_PMUV3_PERFCTR_L3D_CACHE_LMISS_RD),
	ARMV8_EVENT_ATTR(ldst_align_lat, ARMV8_PMUV3_PERFCTR_LDST_ALIGN_LAT),
	ARMV8_EVENT_ATTR(ld_align_lat, ARMV8_PMUV3_PERFCTR_LD_ALIGN_LAT),
	ARMV8_EVENT_ATTR(st_align_lat, ARMV8_PMUV3_PERFCTR_ST_ALIGN_LAT),
	ARMV8_EVENT_ATTR(mem_access_checked, ARMV8_MTE_PERFCTR_MEM_ACCESS_CHECKED),
	ARMV8_EVENT_ATTR(mem_access_checked_rd, ARMV8_MTE_PERFCTR_MEM_ACCESS_CHECKED_RD),
	ARMV8_EVENT_ATTR(mem_access_checked_wr, ARMV8_MTE_PERFCTR_MEM_ACCESS_CHECKED_WR),
	शून्य,
पूर्ण;

अटल umode_t
armv8pmu_event_attr_is_visible(काष्ठा kobject *kobj,
			       काष्ठा attribute *attr, पूर्णांक unused)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा pmu *pmu = dev_get_drvdata(dev);
	काष्ठा arm_pmu *cpu_pmu = container_of(pmu, काष्ठा arm_pmu, pmu);
	काष्ठा perf_pmu_events_attr *pmu_attr;

	pmu_attr = container_of(attr, काष्ठा perf_pmu_events_attr, attr.attr);

	अगर (pmu_attr->id < ARMV8_PMUV3_MAX_COMMON_EVENTS &&
	    test_bit(pmu_attr->id, cpu_pmu->pmceid_biपंचांगap))
		वापस attr->mode;

	अगर (pmu_attr->id >= ARMV8_PMUV3_EXT_COMMON_EVENT_BASE) अणु
		u64 id = pmu_attr->id - ARMV8_PMUV3_EXT_COMMON_EVENT_BASE;

		अगर (id < ARMV8_PMUV3_MAX_COMMON_EVENTS &&
		    test_bit(id, cpu_pmu->pmceid_ext_biपंचांगap))
			वापस attr->mode;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group armv8_pmuv3_events_attr_group = अणु
	.name = "events",
	.attrs = armv8_pmuv3_event_attrs,
	.is_visible = armv8pmu_event_attr_is_visible,
पूर्ण;

PMU_FORMAT_ATTR(event, "config:0-15");
PMU_FORMAT_ATTR(दीर्घ, "config1:0");

अटल अंतरभूत bool armv8pmu_event_is_64bit(काष्ठा perf_event *event)
अणु
	वापस event->attr.config1 & 0x1;
पूर्ण

अटल काष्ठा attribute *armv8_pmuv3_क्रमmat_attrs[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_दीर्घ.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group armv8_pmuv3_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = armv8_pmuv3_क्रमmat_attrs,
पूर्ण;

अटल sमाप_प्रकार slots_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *page)
अणु
	काष्ठा pmu *pmu = dev_get_drvdata(dev);
	काष्ठा arm_pmu *cpu_pmu = container_of(pmu, काष्ठा arm_pmu, pmu);
	u32 slots = cpu_pmu->reg_pmmir & ARMV8_PMU_SLOTS_MASK;

	वापस snम_लिखो(page, PAGE_SIZE, "0x%08x\n", slots);
पूर्ण

अटल DEVICE_ATTR_RO(slots);

अटल काष्ठा attribute *armv8_pmuv3_caps_attrs[] = अणु
	&dev_attr_slots.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group armv8_pmuv3_caps_attr_group = अणु
	.name = "caps",
	.attrs = armv8_pmuv3_caps_attrs,
पूर्ण;

/*
 * Perf Events' indices
 */
#घोषणा	ARMV8_IDX_CYCLE_COUNTER	0
#घोषणा	ARMV8_IDX_COUNTER0	1


/*
 * We unconditionally enable ARMv8.5-PMU दीर्घ event counter support
 * (64-bit events) where supported. Indicate अगर this arm_pmu has दीर्घ
 * event counter support.
 */
अटल bool armv8pmu_has_दीर्घ_event(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस (cpu_pmu->pmuver >= ID_AA64DFR0_PMUVER_8_5);
पूर्ण

/*
 * We must chain two programmable counters क्रम 64 bit events,
 * except when we have allocated the 64bit cycle counter (क्रम CPU
 * cycles event). This must be called only when the event has
 * a counter allocated.
 */
अटल अंतरभूत bool armv8pmu_event_is_chained(काष्ठा perf_event *event)
अणु
	पूर्णांक idx = event->hw.idx;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);

	वापस !WARN_ON(idx < 0) &&
	       armv8pmu_event_is_64bit(event) &&
	       !armv8pmu_has_दीर्घ_event(cpu_pmu) &&
	       (idx != ARMV8_IDX_CYCLE_COUNTER);
पूर्ण

/*
 * ARMv8 low level PMU access
 */

/*
 * Perf Event to low level counters mapping
 */
#घोषणा	ARMV8_IDX_TO_COUNTER(x)	\
	(((x) - ARMV8_IDX_COUNTER0) & ARMV8_PMU_COUNTER_MASK)

/*
 * This code is really good
 */

#घोषणा PMEVN_CASE(n, हाल_macro) \
	हाल n: हाल_macro(n); अवरोध

#घोषणा PMEVN_SWITCH(x, हाल_macro)				\
	करो अणु							\
		चयन (x) अणु					\
		PMEVN_CASE(0,  हाल_macro);			\
		PMEVN_CASE(1,  हाल_macro);			\
		PMEVN_CASE(2,  हाल_macro);			\
		PMEVN_CASE(3,  हाल_macro);			\
		PMEVN_CASE(4,  हाल_macro);			\
		PMEVN_CASE(5,  हाल_macro);			\
		PMEVN_CASE(6,  हाल_macro);			\
		PMEVN_CASE(7,  हाल_macro);			\
		PMEVN_CASE(8,  हाल_macro);			\
		PMEVN_CASE(9,  हाल_macro);			\
		PMEVN_CASE(10, हाल_macro);			\
		PMEVN_CASE(11, हाल_macro);			\
		PMEVN_CASE(12, हाल_macro);			\
		PMEVN_CASE(13, हाल_macro);			\
		PMEVN_CASE(14, हाल_macro);			\
		PMEVN_CASE(15, हाल_macro);			\
		PMEVN_CASE(16, हाल_macro);			\
		PMEVN_CASE(17, हाल_macro);			\
		PMEVN_CASE(18, हाल_macro);			\
		PMEVN_CASE(19, हाल_macro);			\
		PMEVN_CASE(20, हाल_macro);			\
		PMEVN_CASE(21, हाल_macro);			\
		PMEVN_CASE(22, हाल_macro);			\
		PMEVN_CASE(23, हाल_macro);			\
		PMEVN_CASE(24, हाल_macro);			\
		PMEVN_CASE(25, हाल_macro);			\
		PMEVN_CASE(26, हाल_macro);			\
		PMEVN_CASE(27, हाल_macro);			\
		PMEVN_CASE(28, हाल_macro);			\
		PMEVN_CASE(29, हाल_macro);			\
		PMEVN_CASE(30, हाल_macro);			\
		शेष: WARN(1, "Invalid PMEV* index\n");	\
		पूर्ण						\
	पूर्ण जबतक (0)

#घोषणा RETURN_READ_PMEVCNTRN(n) \
	वापस पढ़ो_sysreg(pmevcntr##n##_el0)
अटल अचिन्हित दीर्घ पढ़ो_pmevcntrn(पूर्णांक n)
अणु
	PMEVN_SWITCH(n, RETURN_READ_PMEVCNTRN);
	वापस 0;
पूर्ण

#घोषणा WRITE_PMEVCNTRN(n) \
	ग_लिखो_sysreg(val, pmevcntr##n##_el0)
अटल व्योम ग_लिखो_pmevcntrn(पूर्णांक n, अचिन्हित दीर्घ val)
अणु
	PMEVN_SWITCH(n, WRITE_PMEVCNTRN);
पूर्ण

#घोषणा WRITE_PMEVTYPERN(n) \
	ग_लिखो_sysreg(val, pmevtyper##n##_el0)
अटल व्योम ग_लिखो_pmevtypern(पूर्णांक n, अचिन्हित दीर्घ val)
अणु
	PMEVN_SWITCH(n, WRITE_PMEVTYPERN);
पूर्ण

अटल अंतरभूत u32 armv8pmu_pmcr_पढ़ो(व्योम)
अणु
	वापस पढ़ो_sysreg(pmcr_el0);
पूर्ण

अटल अंतरभूत व्योम armv8pmu_pmcr_ग_लिखो(u32 val)
अणु
	val &= ARMV8_PMU_PMCR_MASK;
	isb();
	ग_लिखो_sysreg(val, pmcr_el0);
पूर्ण

अटल अंतरभूत पूर्णांक armv8pmu_has_overflowed(u32 pmovsr)
अणु
	वापस pmovsr & ARMV8_PMU_OVERFLOWED_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक armv8pmu_counter_has_overflowed(u32 pmnc, पूर्णांक idx)
अणु
	वापस pmnc & BIT(ARMV8_IDX_TO_COUNTER(idx));
पूर्ण

अटल अंतरभूत u64 armv8pmu_पढ़ो_evcntr(पूर्णांक idx)
अणु
	u32 counter = ARMV8_IDX_TO_COUNTER(idx);

	वापस पढ़ो_pmevcntrn(counter);
पूर्ण

अटल अंतरभूत u64 armv8pmu_पढ़ो_hw_counter(काष्ठा perf_event *event)
अणु
	पूर्णांक idx = event->hw.idx;
	u64 val = armv8pmu_पढ़ो_evcntr(idx);

	अगर (armv8pmu_event_is_chained(event))
		val = (val << 32) | armv8pmu_पढ़ो_evcntr(idx - 1);
	वापस val;
पूर्ण

/*
 * The cycle counter is always a 64-bit counter. When ARMV8_PMU_PMCR_LP
 * is set the event counters also become 64-bit counters. Unless the
 * user has requested a दीर्घ counter (attr.config1) then we want to
 * पूर्णांकerrupt upon 32-bit overflow - we achieve this by applying a bias.
 */
अटल bool armv8pmu_event_needs_bias(काष्ठा perf_event *event)
अणु
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	अगर (armv8pmu_event_is_64bit(event))
		वापस false;

	अगर (armv8pmu_has_दीर्घ_event(cpu_pmu) ||
	    idx == ARMV8_IDX_CYCLE_COUNTER)
		वापस true;

	वापस false;
पूर्ण

अटल u64 armv8pmu_bias_दीर्घ_counter(काष्ठा perf_event *event, u64 value)
अणु
	अगर (armv8pmu_event_needs_bias(event))
		value |= GENMASK(63, 32);

	वापस value;
पूर्ण

अटल u64 armv8pmu_unbias_दीर्घ_counter(काष्ठा perf_event *event, u64 value)
अणु
	अगर (armv8pmu_event_needs_bias(event))
		value &= ~GENMASK(63, 32);

	वापस value;
पूर्ण

अटल u64 armv8pmu_पढ़ो_counter(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;
	u64 value;

	अगर (idx == ARMV8_IDX_CYCLE_COUNTER)
		value = पढ़ो_sysreg(pmccntr_el0);
	अन्यथा
		value = armv8pmu_पढ़ो_hw_counter(event);

	वापस  armv8pmu_unbias_दीर्घ_counter(event, value);
पूर्ण

अटल अंतरभूत व्योम armv8pmu_ग_लिखो_evcntr(पूर्णांक idx, u64 value)
अणु
	u32 counter = ARMV8_IDX_TO_COUNTER(idx);

	ग_लिखो_pmevcntrn(counter, value);
पूर्ण

अटल अंतरभूत व्योम armv8pmu_ग_लिखो_hw_counter(काष्ठा perf_event *event,
					     u64 value)
अणु
	पूर्णांक idx = event->hw.idx;

	अगर (armv8pmu_event_is_chained(event)) अणु
		armv8pmu_ग_लिखो_evcntr(idx, upper_32_bits(value));
		armv8pmu_ग_लिखो_evcntr(idx - 1, lower_32_bits(value));
	पूर्ण अन्यथा अणु
		armv8pmu_ग_लिखो_evcntr(idx, value);
	पूर्ण
पूर्ण

अटल व्योम armv8pmu_ग_लिखो_counter(काष्ठा perf_event *event, u64 value)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	value = armv8pmu_bias_दीर्घ_counter(event, value);

	अगर (idx == ARMV8_IDX_CYCLE_COUNTER)
		ग_लिखो_sysreg(value, pmccntr_el0);
	अन्यथा
		armv8pmu_ग_लिखो_hw_counter(event, value);
पूर्ण

अटल अंतरभूत व्योम armv8pmu_ग_लिखो_evtype(पूर्णांक idx, u32 val)
अणु
	u32 counter = ARMV8_IDX_TO_COUNTER(idx);

	val &= ARMV8_PMU_EVTYPE_MASK;
	ग_लिखो_pmevtypern(counter, val);
पूर्ण

अटल अंतरभूत व्योम armv8pmu_ग_लिखो_event_type(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	/*
	 * For chained events, the low counter is programmed to count
	 * the event of पूर्णांकerest and the high counter is programmed
	 * with CHAIN event code with filters set to count at all ELs.
	 */
	अगर (armv8pmu_event_is_chained(event)) अणु
		u32 chain_evt = ARMV8_PMUV3_PERFCTR_CHAIN |
				ARMV8_PMU_INCLUDE_EL2;

		armv8pmu_ग_लिखो_evtype(idx - 1, hwc->config_base);
		armv8pmu_ग_लिखो_evtype(idx, chain_evt);
	पूर्ण अन्यथा अणु
		अगर (idx == ARMV8_IDX_CYCLE_COUNTER)
			ग_लिखो_sysreg(hwc->config_base, pmccfiltr_el0);
		अन्यथा
			armv8pmu_ग_लिखो_evtype(idx, hwc->config_base);
	पूर्ण
पूर्ण

अटल u32 armv8pmu_event_cnten_mask(काष्ठा perf_event *event)
अणु
	पूर्णांक counter = ARMV8_IDX_TO_COUNTER(event->hw.idx);
	u32 mask = BIT(counter);

	अगर (armv8pmu_event_is_chained(event))
		mask |= BIT(counter - 1);
	वापस mask;
पूर्ण

अटल अंतरभूत व्योम armv8pmu_enable_counter(u32 mask)
अणु
	/*
	 * Make sure event configuration रेजिस्टर ग_लिखोs are visible beक्रमe we
	 * enable the counter.
	 * */
	isb();
	ग_लिखो_sysreg(mask, pmcntenset_el0);
पूर्ण

अटल अंतरभूत व्योम armv8pmu_enable_event_counter(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	u32 mask = armv8pmu_event_cnten_mask(event);

	kvm_set_pmu_events(mask, attr);

	/* We rely on the hypervisor चयन code to enable guest counters */
	अगर (!kvm_pmu_counter_deferred(attr))
		armv8pmu_enable_counter(mask);
पूर्ण

अटल अंतरभूत व्योम armv8pmu_disable_counter(u32 mask)
अणु
	ग_लिखो_sysreg(mask, pmcntenclr_el0);
	/*
	 * Make sure the effects of disabling the counter are visible beक्रमe we
	 * start configuring the event.
	 */
	isb();
पूर्ण

अटल अंतरभूत व्योम armv8pmu_disable_event_counter(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	u32 mask = armv8pmu_event_cnten_mask(event);

	kvm_clr_pmu_events(mask);

	/* We rely on the hypervisor चयन code to disable guest counters */
	अगर (!kvm_pmu_counter_deferred(attr))
		armv8pmu_disable_counter(mask);
पूर्ण

अटल अंतरभूत व्योम armv8pmu_enable_पूर्णांकens(u32 mask)
अणु
	ग_लिखो_sysreg(mask, pmपूर्णांकenset_el1);
पूर्ण

अटल अंतरभूत व्योम armv8pmu_enable_event_irq(काष्ठा perf_event *event)
अणु
	u32 counter = ARMV8_IDX_TO_COUNTER(event->hw.idx);
	armv8pmu_enable_पूर्णांकens(BIT(counter));
पूर्ण

अटल अंतरभूत व्योम armv8pmu_disable_पूर्णांकens(u32 mask)
अणु
	ग_लिखो_sysreg(mask, pmपूर्णांकenclr_el1);
	isb();
	/* Clear the overflow flag in हाल an पूर्णांकerrupt is pending. */
	ग_लिखो_sysreg(mask, pmovsclr_el0);
	isb();
पूर्ण

अटल अंतरभूत व्योम armv8pmu_disable_event_irq(काष्ठा perf_event *event)
अणु
	u32 counter = ARMV8_IDX_TO_COUNTER(event->hw.idx);
	armv8pmu_disable_पूर्णांकens(BIT(counter));
पूर्ण

अटल अंतरभूत u32 armv8pmu_getreset_flags(व्योम)
अणु
	u32 value;

	/* Read */
	value = पढ़ो_sysreg(pmovsclr_el0);

	/* Write to clear flags */
	value &= ARMV8_PMU_OVSR_MASK;
	ग_लिखो_sysreg(value, pmovsclr_el0);

	वापस value;
पूर्ण

अटल व्योम armv8pmu_enable_event(काष्ठा perf_event *event)
अणु
	/*
	 * Enable counter and पूर्णांकerrupt, and set the counter to count
	 * the event that we're पूर्णांकerested in.
	 */

	/*
	 * Disable counter
	 */
	armv8pmu_disable_event_counter(event);

	/*
	 * Set event.
	 */
	armv8pmu_ग_लिखो_event_type(event);

	/*
	 * Enable पूर्णांकerrupt क्रम this counter
	 */
	armv8pmu_enable_event_irq(event);

	/*
	 * Enable counter
	 */
	armv8pmu_enable_event_counter(event);
पूर्ण

अटल व्योम armv8pmu_disable_event(काष्ठा perf_event *event)
अणु
	/*
	 * Disable counter
	 */
	armv8pmu_disable_event_counter(event);

	/*
	 * Disable पूर्णांकerrupt क्रम this counter
	 */
	armv8pmu_disable_event_irq(event);
पूर्ण

अटल व्योम armv8pmu_start(काष्ठा arm_pmu *cpu_pmu)
अणु
	/* Enable all counters */
	armv8pmu_pmcr_ग_लिखो(armv8pmu_pmcr_पढ़ो() | ARMV8_PMU_PMCR_E);
पूर्ण

अटल व्योम armv8pmu_stop(काष्ठा arm_pmu *cpu_pmu)
अणु
	/* Disable all counters */
	armv8pmu_pmcr_ग_लिखो(armv8pmu_pmcr_पढ़ो() & ~ARMV8_PMU_PMCR_E);
पूर्ण

अटल irqवापस_t armv8pmu_handle_irq(काष्ठा arm_pmu *cpu_pmu)
अणु
	u32 pmovsr;
	काष्ठा perf_sample_data data;
	काष्ठा pmu_hw_events *cpuc = this_cpu_ptr(cpu_pmu->hw_events);
	काष्ठा pt_regs *regs;
	पूर्णांक idx;

	/*
	 * Get and reset the IRQ flags
	 */
	pmovsr = armv8pmu_getreset_flags();

	/*
	 * Did an overflow occur?
	 */
	अगर (!armv8pmu_has_overflowed(pmovsr))
		वापस IRQ_NONE;

	/*
	 * Handle the counter(s) overflow(s)
	 */
	regs = get_irq_regs();

	/*
	 * Stop the PMU जबतक processing the counter overflows
	 * to prevent skews in group events.
	 */
	armv8pmu_stop(cpu_pmu);
	क्रम (idx = 0; idx < cpu_pmu->num_events; ++idx) अणु
		काष्ठा perf_event *event = cpuc->events[idx];
		काष्ठा hw_perf_event *hwc;

		/* Ignore अगर we करोn't have an event. */
		अगर (!event)
			जारी;

		/*
		 * We have a single पूर्णांकerrupt क्रम all counters. Check that
		 * each counter has overflowed beक्रमe we process it.
		 */
		अगर (!armv8pmu_counter_has_overflowed(pmovsr, idx))
			जारी;

		hwc = &event->hw;
		armpmu_event_update(event);
		perf_sample_data_init(&data, 0, hwc->last_period);
		अगर (!armpmu_event_set_period(event))
			जारी;

		/*
		 * Perf event overflow will queue the processing of the event as
		 * an irq_work which will be taken care of in the handling of
		 * IPI_IRQ_WORK.
		 */
		अगर (perf_event_overflow(event, &data, regs))
			cpu_pmu->disable(event);
	पूर्ण
	armv8pmu_start(cpu_pmu);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक armv8pmu_get_single_idx(काष्ठा pmu_hw_events *cpuc,
				    काष्ठा arm_pmu *cpu_pmu)
अणु
	पूर्णांक idx;

	क्रम (idx = ARMV8_IDX_COUNTER0; idx < cpu_pmu->num_events; idx++) अणु
		अगर (!test_and_set_bit(idx, cpuc->used_mask))
			वापस idx;
	पूर्ण
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक armv8pmu_get_chain_idx(काष्ठा pmu_hw_events *cpuc,
				   काष्ठा arm_pmu *cpu_pmu)
अणु
	पूर्णांक idx;

	/*
	 * Chaining requires two consecutive event counters, where
	 * the lower idx must be even.
	 */
	क्रम (idx = ARMV8_IDX_COUNTER0 + 1; idx < cpu_pmu->num_events; idx += 2) अणु
		अगर (!test_and_set_bit(idx, cpuc->used_mask)) अणु
			/* Check अगर the preceding even counter is available */
			अगर (!test_and_set_bit(idx - 1, cpuc->used_mask))
				वापस idx;
			/* Release the Odd counter */
			clear_bit(idx, cpuc->used_mask);
		पूर्ण
	पूर्ण
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक armv8pmu_get_event_idx(काष्ठा pmu_hw_events *cpuc,
				  काष्ठा perf_event *event)
अणु
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	अचिन्हित दीर्घ evtype = hwc->config_base & ARMV8_PMU_EVTYPE_EVENT;

	/* Always prefer to place a cycle counter पूर्णांकo the cycle counter. */
	अगर (evtype == ARMV8_PMUV3_PERFCTR_CPU_CYCLES) अणु
		अगर (!test_and_set_bit(ARMV8_IDX_CYCLE_COUNTER, cpuc->used_mask))
			वापस ARMV8_IDX_CYCLE_COUNTER;
	पूर्ण

	/*
	 * Otherwise use events counters
	 */
	अगर (armv8pmu_event_is_64bit(event) &&
	    !armv8pmu_has_दीर्घ_event(cpu_pmu))
		वापस	armv8pmu_get_chain_idx(cpuc, cpu_pmu);
	अन्यथा
		वापस armv8pmu_get_single_idx(cpuc, cpu_pmu);
पूर्ण

अटल व्योम armv8pmu_clear_event_idx(काष्ठा pmu_hw_events *cpuc,
				     काष्ठा perf_event *event)
अणु
	पूर्णांक idx = event->hw.idx;

	clear_bit(idx, cpuc->used_mask);
	अगर (armv8pmu_event_is_chained(event))
		clear_bit(idx - 1, cpuc->used_mask);
पूर्ण

/*
 * Add an event filter to a given event.
 */
अटल पूर्णांक armv8pmu_set_event_filter(काष्ठा hw_perf_event *event,
				     काष्ठा perf_event_attr *attr)
अणु
	अचिन्हित दीर्घ config_base = 0;

	अगर (attr->exclude_idle)
		वापस -EPERM;

	/*
	 * If we're running in hyp mode, then we *are* the hypervisor.
	 * Thereक्रमe we ignore exclude_hv in this configuration, since
	 * there's no hypervisor to sample anyway. This is consistent
	 * with other architectures (x86 and Power).
	 */
	अगर (is_kernel_in_hyp_mode()) अणु
		अगर (!attr->exclude_kernel && !attr->exclude_host)
			config_base |= ARMV8_PMU_INCLUDE_EL2;
		अगर (attr->exclude_guest)
			config_base |= ARMV8_PMU_EXCLUDE_EL1;
		अगर (attr->exclude_host)
			config_base |= ARMV8_PMU_EXCLUDE_EL0;
	पूर्ण अन्यथा अणु
		अगर (!attr->exclude_hv && !attr->exclude_host)
			config_base |= ARMV8_PMU_INCLUDE_EL2;
	पूर्ण

	/*
	 * Filter out !VHE kernels and guest kernels
	 */
	अगर (attr->exclude_kernel)
		config_base |= ARMV8_PMU_EXCLUDE_EL1;

	अगर (attr->exclude_user)
		config_base |= ARMV8_PMU_EXCLUDE_EL0;

	/*
	 * Install the filter पूर्णांकo config_base as this is used to
	 * स्थिरruct the event type.
	 */
	event->config_base = config_base;

	वापस 0;
पूर्ण

अटल पूर्णांक armv8pmu_filter_match(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ evtype = event->hw.config_base & ARMV8_PMU_EVTYPE_EVENT;
	वापस evtype != ARMV8_PMUV3_PERFCTR_CHAIN;
पूर्ण

अटल व्योम armv8pmu_reset(व्योम *info)
अणु
	काष्ठा arm_pmu *cpu_pmu = (काष्ठा arm_pmu *)info;
	u32 pmcr;

	/* The counter and पूर्णांकerrupt enable रेजिस्टरs are unknown at reset. */
	armv8pmu_disable_counter(U32_MAX);
	armv8pmu_disable_पूर्णांकens(U32_MAX);

	/* Clear the counters we flip at guest entry/निकास */
	kvm_clr_pmu_events(U32_MAX);

	/*
	 * Initialize & Reset PMNC. Request overflow पूर्णांकerrupt क्रम
	 * 64 bit cycle counter but cheat in armv8pmu_ग_लिखो_counter().
	 */
	pmcr = ARMV8_PMU_PMCR_P | ARMV8_PMU_PMCR_C | ARMV8_PMU_PMCR_LC;

	/* Enable दीर्घ event counter support where available */
	अगर (armv8pmu_has_दीर्घ_event(cpu_pmu))
		pmcr |= ARMV8_PMU_PMCR_LP;

	armv8pmu_pmcr_ग_लिखो(pmcr);
पूर्ण

अटल पूर्णांक __armv8_pmuv3_map_event(काष्ठा perf_event *event,
				   स्थिर अचिन्हित (*extra_event_map)
						  [PERF_COUNT_HW_MAX],
				   स्थिर अचिन्हित (*extra_cache_map)
						  [PERF_COUNT_HW_CACHE_MAX]
						  [PERF_COUNT_HW_CACHE_OP_MAX]
						  [PERF_COUNT_HW_CACHE_RESULT_MAX])
अणु
	पूर्णांक hw_event_id;
	काष्ठा arm_pmu *armpmu = to_arm_pmu(event->pmu);

	hw_event_id = armpmu_map_event(event, &armv8_pmuv3_perf_map,
				       &armv8_pmuv3_perf_cache_map,
				       ARMV8_PMU_EVTYPE_EVENT);

	अगर (armv8pmu_event_is_64bit(event))
		event->hw.flags |= ARMPMU_EVT_64BIT;

	/* Only expose micro/arch events supported by this PMU */
	अगर ((hw_event_id > 0) && (hw_event_id < ARMV8_PMUV3_MAX_COMMON_EVENTS)
	    && test_bit(hw_event_id, armpmu->pmceid_biपंचांगap)) अणु
		वापस hw_event_id;
	पूर्ण

	वापस armpmu_map_event(event, extra_event_map, extra_cache_map,
				ARMV8_PMU_EVTYPE_EVENT);
पूर्ण

अटल पूर्णांक armv8_pmuv3_map_event(काष्ठा perf_event *event)
अणु
	वापस __armv8_pmuv3_map_event(event, शून्य, शून्य);
पूर्ण

अटल पूर्णांक armv8_a53_map_event(काष्ठा perf_event *event)
अणु
	वापस __armv8_pmuv3_map_event(event, शून्य, &armv8_a53_perf_cache_map);
पूर्ण

अटल पूर्णांक armv8_a57_map_event(काष्ठा perf_event *event)
अणु
	वापस __armv8_pmuv3_map_event(event, शून्य, &armv8_a57_perf_cache_map);
पूर्ण

अटल पूर्णांक armv8_a73_map_event(काष्ठा perf_event *event)
अणु
	वापस __armv8_pmuv3_map_event(event, शून्य, &armv8_a73_perf_cache_map);
पूर्ण

अटल पूर्णांक armv8_thunder_map_event(काष्ठा perf_event *event)
अणु
	वापस __armv8_pmuv3_map_event(event, शून्य,
				       &armv8_thunder_perf_cache_map);
पूर्ण

अटल पूर्णांक armv8_vulcan_map_event(काष्ठा perf_event *event)
अणु
	वापस __armv8_pmuv3_map_event(event, शून्य,
				       &armv8_vulcan_perf_cache_map);
पूर्ण

काष्ठा armv8pmu_probe_info अणु
	काष्ठा arm_pmu *pmu;
	bool present;
पूर्ण;

अटल व्योम __armv8pmu_probe_pmu(व्योम *info)
अणु
	काष्ठा armv8pmu_probe_info *probe = info;
	काष्ठा arm_pmu *cpu_pmu = probe->pmu;
	u64 dfr0;
	u64 pmceid_raw[2];
	u32 pmceid[2];
	पूर्णांक pmuver;

	dfr0 = पढ़ो_sysreg(id_aa64dfr0_el1);
	pmuver = cpuid_feature_extract_अचिन्हित_field(dfr0,
			ID_AA64DFR0_PMUVER_SHIFT);
	अगर (pmuver == 0xf || pmuver == 0)
		वापस;

	cpu_pmu->pmuver = pmuver;
	probe->present = true;

	/* Read the nb of CNTx counters supported from PMNC */
	cpu_pmu->num_events = (armv8pmu_pmcr_पढ़ो() >> ARMV8_PMU_PMCR_N_SHIFT)
		& ARMV8_PMU_PMCR_N_MASK;

	/* Add the CPU cycles counter */
	cpu_pmu->num_events += 1;

	pmceid[0] = pmceid_raw[0] = पढ़ो_sysreg(pmceid0_el0);
	pmceid[1] = pmceid_raw[1] = पढ़ो_sysreg(pmceid1_el0);

	biपंचांगap_from_arr32(cpu_pmu->pmceid_biपंचांगap,
			     pmceid, ARMV8_PMUV3_MAX_COMMON_EVENTS);

	pmceid[0] = pmceid_raw[0] >> 32;
	pmceid[1] = pmceid_raw[1] >> 32;

	biपंचांगap_from_arr32(cpu_pmu->pmceid_ext_biपंचांगap,
			     pmceid, ARMV8_PMUV3_MAX_COMMON_EVENTS);

	/* store PMMIR_EL1 रेजिस्टर क्रम sysfs */
	अगर (pmuver >= ID_AA64DFR0_PMUVER_8_4 && (pmceid_raw[1] & BIT(31)))
		cpu_pmu->reg_pmmir = पढ़ो_cpuid(PMMIR_EL1);
	अन्यथा
		cpu_pmu->reg_pmmir = 0;
पूर्ण

अटल पूर्णांक armv8pmu_probe_pmu(काष्ठा arm_pmu *cpu_pmu)
अणु
	काष्ठा armv8pmu_probe_info probe = अणु
		.pmu = cpu_pmu,
		.present = false,
	पूर्ण;
	पूर्णांक ret;

	ret = smp_call_function_any(&cpu_pmu->supported_cpus,
				    __armv8pmu_probe_pmu,
				    &probe, 1);
	अगर (ret)
		वापस ret;

	वापस probe.present ? 0 : -ENODEV;
पूर्ण

अटल पूर्णांक armv8_pmu_init(काष्ठा arm_pmu *cpu_pmu, अक्षर *name,
			  पूर्णांक (*map_event)(काष्ठा perf_event *event),
			  स्थिर काष्ठा attribute_group *events,
			  स्थिर काष्ठा attribute_group *क्रमmat,
			  स्थिर काष्ठा attribute_group *caps)
अणु
	पूर्णांक ret = armv8pmu_probe_pmu(cpu_pmu);
	अगर (ret)
		वापस ret;

	cpu_pmu->handle_irq		= armv8pmu_handle_irq;
	cpu_pmu->enable			= armv8pmu_enable_event;
	cpu_pmu->disable		= armv8pmu_disable_event;
	cpu_pmu->पढ़ो_counter		= armv8pmu_पढ़ो_counter;
	cpu_pmu->ग_लिखो_counter		= armv8pmu_ग_लिखो_counter;
	cpu_pmu->get_event_idx		= armv8pmu_get_event_idx;
	cpu_pmu->clear_event_idx	= armv8pmu_clear_event_idx;
	cpu_pmu->start			= armv8pmu_start;
	cpu_pmu->stop			= armv8pmu_stop;
	cpu_pmu->reset			= armv8pmu_reset;
	cpu_pmu->set_event_filter	= armv8pmu_set_event_filter;
	cpu_pmu->filter_match		= armv8pmu_filter_match;

	cpu_pmu->name			= name;
	cpu_pmu->map_event		= map_event;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_EVENTS] = events ?
			events : &armv8_pmuv3_events_attr_group;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_FORMATS] = क्रमmat ?
			क्रमmat : &armv8_pmuv3_क्रमmat_attr_group;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_CAPS] = caps ?
			caps : &armv8_pmuv3_caps_attr_group;

	वापस 0;
पूर्ण

अटल पूर्णांक armv8_pmu_init_nogroups(काष्ठा arm_pmu *cpu_pmu, अक्षर *name,
				   पूर्णांक (*map_event)(काष्ठा perf_event *event))
अणु
	वापस armv8_pmu_init(cpu_pmu, name, map_event, शून्य, शून्य, शून्य);
पूर्ण

अटल पूर्णांक armv8_pmuv3_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस armv8_pmu_init_nogroups(cpu_pmu, "armv8_pmuv3",
				       armv8_pmuv3_map_event);
पूर्ण

अटल पूर्णांक armv8_a34_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस armv8_pmu_init_nogroups(cpu_pmu, "armv8_cortex_a34",
				       armv8_pmuv3_map_event);
पूर्ण

अटल पूर्णांक armv8_a35_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस armv8_pmu_init_nogroups(cpu_pmu, "armv8_cortex_a35",
				       armv8_a53_map_event);
पूर्ण

अटल पूर्णांक armv8_a53_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस armv8_pmu_init_nogroups(cpu_pmu, "armv8_cortex_a53",
				       armv8_a53_map_event);
पूर्ण

अटल पूर्णांक armv8_a55_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस armv8_pmu_init_nogroups(cpu_pmu, "armv8_cortex_a55",
				       armv8_pmuv3_map_event);
पूर्ण

अटल पूर्णांक armv8_a57_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस armv8_pmu_init_nogroups(cpu_pmu, "armv8_cortex_a57",
				       armv8_a57_map_event);
पूर्ण

अटल पूर्णांक armv8_a65_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस armv8_pmu_init_nogroups(cpu_pmu, "armv8_cortex_a65",
				       armv8_pmuv3_map_event);
पूर्ण

अटल पूर्णांक armv8_a72_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस armv8_pmu_init_nogroups(cpu_pmu, "armv8_cortex_a72",
				       armv8_a57_map_event);
पूर्ण

अटल पूर्णांक armv8_a73_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस armv8_pmu_init_nogroups(cpu_pmu, "armv8_cortex_a73",
				       armv8_a73_map_event);
पूर्ण

अटल पूर्णांक armv8_a75_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस armv8_pmu_init_nogroups(cpu_pmu, "armv8_cortex_a75",
				       armv8_pmuv3_map_event);
पूर्ण

अटल पूर्णांक armv8_a76_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस armv8_pmu_init_nogroups(cpu_pmu, "armv8_cortex_a76",
				       armv8_pmuv3_map_event);
पूर्ण

अटल पूर्णांक armv8_a77_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस armv8_pmu_init_nogroups(cpu_pmu, "armv8_cortex_a77",
				       armv8_pmuv3_map_event);
पूर्ण

अटल पूर्णांक armv8_a78_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस armv8_pmu_init_nogroups(cpu_pmu, "armv8_cortex_a78",
				       armv8_pmuv3_map_event);
पूर्ण

अटल पूर्णांक armv8_e1_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस armv8_pmu_init_nogroups(cpu_pmu, "armv8_neoverse_e1",
				       armv8_pmuv3_map_event);
पूर्ण

अटल पूर्णांक armv8_n1_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस armv8_pmu_init_nogroups(cpu_pmu, "armv8_neoverse_n1",
				       armv8_pmuv3_map_event);
पूर्ण

अटल पूर्णांक armv8_thunder_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस armv8_pmu_init_nogroups(cpu_pmu, "armv8_cavium_thunder",
				       armv8_thunder_map_event);
पूर्ण

अटल पूर्णांक armv8_vulcan_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	वापस armv8_pmu_init_nogroups(cpu_pmu, "armv8_brcm_vulcan",
				       armv8_vulcan_map_event);
पूर्ण

अटल स्थिर काष्ठा of_device_id armv8_pmu_of_device_ids[] = अणु
	अणु.compatible = "arm,armv8-pmuv3",	.data = armv8_pmuv3_initपूर्ण,
	अणु.compatible = "arm,cortex-a34-pmu",	.data = armv8_a34_pmu_initपूर्ण,
	अणु.compatible = "arm,cortex-a35-pmu",	.data = armv8_a35_pmu_initपूर्ण,
	अणु.compatible = "arm,cortex-a53-pmu",	.data = armv8_a53_pmu_initपूर्ण,
	अणु.compatible = "arm,cortex-a55-pmu",	.data = armv8_a55_pmu_initपूर्ण,
	अणु.compatible = "arm,cortex-a57-pmu",	.data = armv8_a57_pmu_initपूर्ण,
	अणु.compatible = "arm,cortex-a65-pmu",	.data = armv8_a65_pmu_initपूर्ण,
	अणु.compatible = "arm,cortex-a72-pmu",	.data = armv8_a72_pmu_initपूर्ण,
	अणु.compatible = "arm,cortex-a73-pmu",	.data = armv8_a73_pmu_initपूर्ण,
	अणु.compatible = "arm,cortex-a75-pmu",	.data = armv8_a75_pmu_initपूर्ण,
	अणु.compatible = "arm,cortex-a76-pmu",	.data = armv8_a76_pmu_initपूर्ण,
	अणु.compatible = "arm,cortex-a77-pmu",	.data = armv8_a77_pmu_initपूर्ण,
	अणु.compatible = "arm,cortex-a78-pmu",	.data = armv8_a78_pmu_initपूर्ण,
	अणु.compatible = "arm,neoverse-e1-pmu",	.data = armv8_e1_pmu_initपूर्ण,
	अणु.compatible = "arm,neoverse-n1-pmu",	.data = armv8_n1_pmu_initपूर्ण,
	अणु.compatible = "cavium,thunder-pmu",	.data = armv8_thunder_pmu_initपूर्ण,
	अणु.compatible = "brcm,vulcan-pmu",	.data = armv8_vulcan_pmu_initपूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक armv8_pmu_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस arm_pmu_device_probe(pdev, armv8_pmu_of_device_ids, शून्य);
पूर्ण

अटल काष्ठा platक्रमm_driver armv8_pmu_driver = अणु
	.driver		= अणु
		.name	= ARMV8_PMU_PDEV_NAME,
		.of_match_table = armv8_pmu_of_device_ids,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= armv8_pmu_device_probe,
पूर्ण;

अटल पूर्णांक __init armv8_pmu_driver_init(व्योम)
अणु
	अगर (acpi_disabled)
		वापस platक्रमm_driver_रेजिस्टर(&armv8_pmu_driver);
	अन्यथा
		वापस arm_pmu_acpi_probe(armv8_pmuv3_init);
पूर्ण
device_initcall(armv8_pmu_driver_init)

व्योम arch_perf_update_userpage(काष्ठा perf_event *event,
			       काष्ठा perf_event_mmap_page *userpg, u64 now)
अणु
	काष्ठा घड़ी_पढ़ो_data *rd;
	अचिन्हित पूर्णांक seq;
	u64 ns;

	userpg->cap_user_समय = 0;
	userpg->cap_user_समय_zero = 0;
	userpg->cap_user_समय_लघु = 0;

	करो अणु
		rd = sched_घड़ी_पढ़ो_begin(&seq);

		अगर (rd->पढ़ो_sched_घड़ी != arch_समयr_पढ़ो_counter)
			वापस;

		userpg->समय_mult = rd->mult;
		userpg->समय_shअगरt = rd->shअगरt;
		userpg->समय_zero = rd->epoch_ns;
		userpg->समय_cycles = rd->epoch_cyc;
		userpg->समय_mask = rd->sched_घड़ी_mask;

		/*
		 * Subtract the cycle base, such that software that
		 * करोesn't know about cap_user_time_short still 'works'
		 * assuming no wraps.
		 */
		ns = mul_u64_u32_shr(rd->epoch_cyc, rd->mult, rd->shअगरt);
		userpg->समय_zero -= ns;

	पूर्ण जबतक (sched_घड़ी_पढ़ो_retry(seq));

	userpg->समय_offset = userpg->समय_zero - now;

	/*
	 * समय_shअगरt is not expected to be greater than 31 due to
	 * the original published conversion algorithm shअगरting a
	 * 32-bit value (now specअगरies a 64-bit value) - refer
	 * perf_event_mmap_page करोcumentation in perf_event.h.
	 */
	अगर (userpg->समय_shअगरt == 32) अणु
		userpg->समय_shअगरt = 31;
		userpg->समय_mult >>= 1;
	पूर्ण

	/*
	 * Internal समयkeeping क्रम enabled/running/stopped बार
	 * is always computed with the sched_घड़ी.
	 */
	userpg->cap_user_समय = 1;
	userpg->cap_user_समय_zero = 1;
	userpg->cap_user_समय_लघु = 1;
पूर्ण
