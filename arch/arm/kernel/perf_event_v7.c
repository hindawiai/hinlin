<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ARMv7 Cortex-A8 and Cortex-A9 Perक्रमmance Events handling code.
 *
 * ARMv7 support: Jean Pihet <jpihet@mvista.com>
 * 2010 (c) MontaVista Software, LLC.
 *
 * Copied from ARMv6 code, with the low level code inspired
 *  by the ARMv7 Oprofile code.
 *
 * Cortex-A8 has up to 4 configurable perक्रमmance counters and
 *  a single cycle counter.
 * Cortex-A9 has up to 31 configurable perक्रमmance counters and
 *  a single cycle counter.
 *
 * All counters can be enabled/disabled and IRQ masked separately. The cycle
 *  counter and all 4 perक्रमmance counters together can be reset separately.
 */

#अगर_घोषित CONFIG_CPU_V7

#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/vfp.h>
#समावेश "../vfp/vfpinstr.h"

#समावेश <linux/of.h>
#समावेश <linux/perf/arm_pmu.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * Common ARMv7 event types
 *
 * Note: An implementation may not be able to count all of these events
 * but the encodings are considered to be `reserved' in the हाल that
 * they are not available.
 */
#घोषणा ARMV7_PERFCTR_PMNC_SW_INCR			0x00
#घोषणा ARMV7_PERFCTR_L1_ICACHE_REFILL			0x01
#घोषणा ARMV7_PERFCTR_ITLB_REFILL			0x02
#घोषणा ARMV7_PERFCTR_L1_DCACHE_REFILL			0x03
#घोषणा ARMV7_PERFCTR_L1_DCACHE_ACCESS			0x04
#घोषणा ARMV7_PERFCTR_DTLB_REFILL			0x05
#घोषणा ARMV7_PERFCTR_MEM_READ				0x06
#घोषणा ARMV7_PERFCTR_MEM_WRITE				0x07
#घोषणा ARMV7_PERFCTR_INSTR_EXECUTED			0x08
#घोषणा ARMV7_PERFCTR_EXC_TAKEN				0x09
#घोषणा ARMV7_PERFCTR_EXC_EXECUTED			0x0A
#घोषणा ARMV7_PERFCTR_CID_WRITE				0x0B

/*
 * ARMV7_PERFCTR_PC_WRITE is equivalent to HW_BRANCH_INSTRUCTIONS.
 * It counts:
 *  - all (taken) branch inकाष्ठाions,
 *  - inकाष्ठाions that explicitly ग_लिखो the PC,
 *  - exception generating inकाष्ठाions.
 */
#घोषणा ARMV7_PERFCTR_PC_WRITE				0x0C
#घोषणा ARMV7_PERFCTR_PC_IMM_BRANCH			0x0D
#घोषणा ARMV7_PERFCTR_PC_PROC_RETURN			0x0E
#घोषणा ARMV7_PERFCTR_MEM_UNALIGNED_ACCESS		0x0F
#घोषणा ARMV7_PERFCTR_PC_BRANCH_MIS_PRED		0x10
#घोषणा ARMV7_PERFCTR_CLOCK_CYCLES			0x11
#घोषणा ARMV7_PERFCTR_PC_BRANCH_PRED			0x12

/* These events are defined by the PMUv2 supplement (ARM DDI 0457A). */
#घोषणा ARMV7_PERFCTR_MEM_ACCESS			0x13
#घोषणा ARMV7_PERFCTR_L1_ICACHE_ACCESS			0x14
#घोषणा ARMV7_PERFCTR_L1_DCACHE_WB			0x15
#घोषणा ARMV7_PERFCTR_L2_CACHE_ACCESS			0x16
#घोषणा ARMV7_PERFCTR_L2_CACHE_REFILL			0x17
#घोषणा ARMV7_PERFCTR_L2_CACHE_WB			0x18
#घोषणा ARMV7_PERFCTR_BUS_ACCESS			0x19
#घोषणा ARMV7_PERFCTR_MEM_ERROR				0x1A
#घोषणा ARMV7_PERFCTR_INSTR_SPEC			0x1B
#घोषणा ARMV7_PERFCTR_TTBR_WRITE			0x1C
#घोषणा ARMV7_PERFCTR_BUS_CYCLES			0x1D

#घोषणा ARMV7_PERFCTR_CPU_CYCLES			0xFF

/* ARMv7 Cortex-A8 specअगरic event types */
#घोषणा ARMV7_A8_PERFCTR_L2_CACHE_ACCESS		0x43
#घोषणा ARMV7_A8_PERFCTR_L2_CACHE_REFILL		0x44
#घोषणा ARMV7_A8_PERFCTR_L1_ICACHE_ACCESS		0x50
#घोषणा ARMV7_A8_PERFCTR_STALL_ISIDE			0x56

/* ARMv7 Cortex-A9 specअगरic event types */
#घोषणा ARMV7_A9_PERFCTR_INSTR_CORE_RENAME		0x68
#घोषणा ARMV7_A9_PERFCTR_STALL_ICACHE			0x60
#घोषणा ARMV7_A9_PERFCTR_STALL_DISPATCH			0x66

/* ARMv7 Cortex-A5 specअगरic event types */
#घोषणा ARMV7_A5_PERFCTR_PREFETCH_LINEFILL		0xc2
#घोषणा ARMV7_A5_PERFCTR_PREFETCH_LINEFILL_DROP		0xc3

/* ARMv7 Cortex-A15 specअगरic event types */
#घोषणा ARMV7_A15_PERFCTR_L1_DCACHE_ACCESS_READ		0x40
#घोषणा ARMV7_A15_PERFCTR_L1_DCACHE_ACCESS_WRITE	0x41
#घोषणा ARMV7_A15_PERFCTR_L1_DCACHE_REFILL_READ		0x42
#घोषणा ARMV7_A15_PERFCTR_L1_DCACHE_REFILL_WRITE	0x43

#घोषणा ARMV7_A15_PERFCTR_DTLB_REFILL_L1_READ		0x4C
#घोषणा ARMV7_A15_PERFCTR_DTLB_REFILL_L1_WRITE		0x4D

#घोषणा ARMV7_A15_PERFCTR_L2_CACHE_ACCESS_READ		0x50
#घोषणा ARMV7_A15_PERFCTR_L2_CACHE_ACCESS_WRITE		0x51
#घोषणा ARMV7_A15_PERFCTR_L2_CACHE_REFILL_READ		0x52
#घोषणा ARMV7_A15_PERFCTR_L2_CACHE_REFILL_WRITE		0x53

#घोषणा ARMV7_A15_PERFCTR_PC_WRITE_SPEC			0x76

/* ARMv7 Cortex-A12 specअगरic event types */
#घोषणा ARMV7_A12_PERFCTR_L1_DCACHE_ACCESS_READ		0x40
#घोषणा ARMV7_A12_PERFCTR_L1_DCACHE_ACCESS_WRITE	0x41

#घोषणा ARMV7_A12_PERFCTR_L2_CACHE_ACCESS_READ		0x50
#घोषणा ARMV7_A12_PERFCTR_L2_CACHE_ACCESS_WRITE		0x51

#घोषणा ARMV7_A12_PERFCTR_PC_WRITE_SPEC			0x76

#घोषणा ARMV7_A12_PERFCTR_PF_TLB_REFILL			0xe7

/* ARMv7 Krait specअगरic event types */
#घोषणा KRAIT_PMRESR0_GROUP0				0xcc
#घोषणा KRAIT_PMRESR1_GROUP0				0xd0
#घोषणा KRAIT_PMRESR2_GROUP0				0xd4
#घोषणा KRAIT_VPMRESR0_GROUP0				0xd8

#घोषणा KRAIT_PERFCTR_L1_ICACHE_ACCESS			0x10011
#घोषणा KRAIT_PERFCTR_L1_ICACHE_MISS			0x10010

#घोषणा KRAIT_PERFCTR_L1_ITLB_ACCESS			0x12222
#घोषणा KRAIT_PERFCTR_L1_DTLB_ACCESS			0x12210

/* ARMv7 Scorpion specअगरic event types */
#घोषणा SCORPION_LPM0_GROUP0				0x4c
#घोषणा SCORPION_LPM1_GROUP0				0x50
#घोषणा SCORPION_LPM2_GROUP0				0x54
#घोषणा SCORPION_L2LPM_GROUP0				0x58
#घोषणा SCORPION_VLPM_GROUP0				0x5c

#घोषणा SCORPION_ICACHE_ACCESS				0x10053
#घोषणा SCORPION_ICACHE_MISS				0x10052

#घोषणा SCORPION_DTLB_ACCESS				0x12013
#घोषणा SCORPION_DTLB_MISS				0x12012

#घोषणा SCORPION_ITLB_MISS				0x12021

/*
 * Cortex-A8 HW events mapping
 *
 * The hardware events that we support. We करो support cache operations but
 * we have harvard caches and no way to combine inकाष्ठाion and data
 * accesses/misses in hardware.
 */
अटल स्थिर अचिन्हित armv7_a8_perf_map[PERF_COUNT_HW_MAX] = अणु
	PERF_MAP_ALL_UNSUPPORTED,
	[PERF_COUNT_HW_CPU_CYCLES]		= ARMV7_PERFCTR_CPU_CYCLES,
	[PERF_COUNT_HW_INSTRUCTIONS]		= ARMV7_PERFCTR_INSTR_EXECUTED,
	[PERF_COUNT_HW_CACHE_REFERENCES]	= ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[PERF_COUNT_HW_CACHE_MISSES]		= ARMV7_PERFCTR_L1_DCACHE_REFILL,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= ARMV7_PERFCTR_PC_WRITE,
	[PERF_COUNT_HW_BRANCH_MISSES]		= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
	[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND]	= ARMV7_A8_PERFCTR_STALL_ISIDE,
पूर्ण;

अटल स्थिर अचिन्हित armv7_a8_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
					  [PERF_COUNT_HW_CACHE_OP_MAX]
					  [PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	PERF_CACHE_MAP_ALL_UNSUPPORTED,

	/*
	 * The perक्रमmance counters करोn't dअगरferentiate between पढ़ो and ग_लिखो
	 * accesses/misses so this isn't strictly correct, but it's the best we
	 * can करो. Writes and पढ़ोs get combined.
	 */
	[C(L1D)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[C(L1D)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_DCACHE_REFILL,
	[C(L1D)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[C(L1D)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_DCACHE_REFILL,

	[C(L1I)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_A8_PERFCTR_L1_ICACHE_ACCESS,
	[C(L1I)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_ICACHE_REFILL,

	[C(LL)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_A8_PERFCTR_L2_CACHE_ACCESS,
	[C(LL)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_A8_PERFCTR_L2_CACHE_REFILL,
	[C(LL)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_A8_PERFCTR_L2_CACHE_ACCESS,
	[C(LL)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_A8_PERFCTR_L2_CACHE_REFILL,

	[C(DTLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_DTLB_REFILL,
	[C(DTLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_DTLB_REFILL,

	[C(ITLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_ITLB_REFILL,
	[C(ITLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_ITLB_REFILL,

	[C(BPU)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_PC_BRANCH_PRED,
	[C(BPU)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
	[C(BPU)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_PC_BRANCH_PRED,
	[C(BPU)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
पूर्ण;

/*
 * Cortex-A9 HW events mapping
 */
अटल स्थिर अचिन्हित armv7_a9_perf_map[PERF_COUNT_HW_MAX] = अणु
	PERF_MAP_ALL_UNSUPPORTED,
	[PERF_COUNT_HW_CPU_CYCLES]		= ARMV7_PERFCTR_CPU_CYCLES,
	[PERF_COUNT_HW_INSTRUCTIONS]		= ARMV7_A9_PERFCTR_INSTR_CORE_RENAME,
	[PERF_COUNT_HW_CACHE_REFERENCES]	= ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[PERF_COUNT_HW_CACHE_MISSES]		= ARMV7_PERFCTR_L1_DCACHE_REFILL,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= ARMV7_PERFCTR_PC_WRITE,
	[PERF_COUNT_HW_BRANCH_MISSES]		= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
	[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND]	= ARMV7_A9_PERFCTR_STALL_ICACHE,
	[PERF_COUNT_HW_STALLED_CYCLES_BACKEND]	= ARMV7_A9_PERFCTR_STALL_DISPATCH,
पूर्ण;

अटल स्थिर अचिन्हित armv7_a9_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
					  [PERF_COUNT_HW_CACHE_OP_MAX]
					  [PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	PERF_CACHE_MAP_ALL_UNSUPPORTED,

	/*
	 * The perक्रमmance counters करोn't dअगरferentiate between पढ़ो and ग_लिखो
	 * accesses/misses so this isn't strictly correct, but it's the best we
	 * can करो. Writes and पढ़ोs get combined.
	 */
	[C(L1D)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[C(L1D)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_DCACHE_REFILL,
	[C(L1D)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[C(L1D)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_DCACHE_REFILL,

	[C(L1I)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_ICACHE_REFILL,

	[C(DTLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_DTLB_REFILL,
	[C(DTLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_DTLB_REFILL,

	[C(ITLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_ITLB_REFILL,
	[C(ITLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_ITLB_REFILL,

	[C(BPU)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_PC_BRANCH_PRED,
	[C(BPU)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
	[C(BPU)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_PC_BRANCH_PRED,
	[C(BPU)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
पूर्ण;

/*
 * Cortex-A5 HW events mapping
 */
अटल स्थिर अचिन्हित armv7_a5_perf_map[PERF_COUNT_HW_MAX] = अणु
	PERF_MAP_ALL_UNSUPPORTED,
	[PERF_COUNT_HW_CPU_CYCLES]		= ARMV7_PERFCTR_CPU_CYCLES,
	[PERF_COUNT_HW_INSTRUCTIONS]		= ARMV7_PERFCTR_INSTR_EXECUTED,
	[PERF_COUNT_HW_CACHE_REFERENCES]	= ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[PERF_COUNT_HW_CACHE_MISSES]		= ARMV7_PERFCTR_L1_DCACHE_REFILL,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= ARMV7_PERFCTR_PC_WRITE,
	[PERF_COUNT_HW_BRANCH_MISSES]		= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
पूर्ण;

अटल स्थिर अचिन्हित armv7_a5_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
					[PERF_COUNT_HW_CACHE_OP_MAX]
					[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	PERF_CACHE_MAP_ALL_UNSUPPORTED,

	[C(L1D)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[C(L1D)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_DCACHE_REFILL,
	[C(L1D)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[C(L1D)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_DCACHE_REFILL,
	[C(L1D)][C(OP_PREFETCH)][C(RESULT_ACCESS)]	= ARMV7_A5_PERFCTR_PREFETCH_LINEFILL,
	[C(L1D)][C(OP_PREFETCH)][C(RESULT_MISS)]	= ARMV7_A5_PERFCTR_PREFETCH_LINEFILL_DROP,

	[C(L1I)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_L1_ICACHE_ACCESS,
	[C(L1I)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_ICACHE_REFILL,
	/*
	 * The prefetch counters करोn't dअगरferentiate between the I side and the
	 * D side.
	 */
	[C(L1I)][C(OP_PREFETCH)][C(RESULT_ACCESS)]	= ARMV7_A5_PERFCTR_PREFETCH_LINEFILL,
	[C(L1I)][C(OP_PREFETCH)][C(RESULT_MISS)]	= ARMV7_A5_PERFCTR_PREFETCH_LINEFILL_DROP,

	[C(DTLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_DTLB_REFILL,
	[C(DTLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_DTLB_REFILL,

	[C(ITLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_ITLB_REFILL,
	[C(ITLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_ITLB_REFILL,

	[C(BPU)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_PC_BRANCH_PRED,
	[C(BPU)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
	[C(BPU)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_PC_BRANCH_PRED,
	[C(BPU)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
पूर्ण;

/*
 * Cortex-A15 HW events mapping
 */
अटल स्थिर अचिन्हित armv7_a15_perf_map[PERF_COUNT_HW_MAX] = अणु
	PERF_MAP_ALL_UNSUPPORTED,
	[PERF_COUNT_HW_CPU_CYCLES]		= ARMV7_PERFCTR_CPU_CYCLES,
	[PERF_COUNT_HW_INSTRUCTIONS]		= ARMV7_PERFCTR_INSTR_EXECUTED,
	[PERF_COUNT_HW_CACHE_REFERENCES]	= ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[PERF_COUNT_HW_CACHE_MISSES]		= ARMV7_PERFCTR_L1_DCACHE_REFILL,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= ARMV7_A15_PERFCTR_PC_WRITE_SPEC,
	[PERF_COUNT_HW_BRANCH_MISSES]		= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
	[PERF_COUNT_HW_BUS_CYCLES]		= ARMV7_PERFCTR_BUS_CYCLES,
पूर्ण;

अटल स्थिर अचिन्हित armv7_a15_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
					[PERF_COUNT_HW_CACHE_OP_MAX]
					[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	PERF_CACHE_MAP_ALL_UNSUPPORTED,

	[C(L1D)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_A15_PERFCTR_L1_DCACHE_ACCESS_READ,
	[C(L1D)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_A15_PERFCTR_L1_DCACHE_REFILL_READ,
	[C(L1D)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_A15_PERFCTR_L1_DCACHE_ACCESS_WRITE,
	[C(L1D)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_A15_PERFCTR_L1_DCACHE_REFILL_WRITE,

	/*
	 * Not all perक्रमmance counters dअगरferentiate between पढ़ो and ग_लिखो
	 * accesses/misses so we're not always strictly correct, but it's the
	 * best we can करो. Writes and पढ़ोs get combined in these हालs.
	 */
	[C(L1I)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_L1_ICACHE_ACCESS,
	[C(L1I)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_ICACHE_REFILL,

	[C(LL)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_A15_PERFCTR_L2_CACHE_ACCESS_READ,
	[C(LL)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_A15_PERFCTR_L2_CACHE_REFILL_READ,
	[C(LL)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_A15_PERFCTR_L2_CACHE_ACCESS_WRITE,
	[C(LL)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_A15_PERFCTR_L2_CACHE_REFILL_WRITE,

	[C(DTLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_A15_PERFCTR_DTLB_REFILL_L1_READ,
	[C(DTLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_A15_PERFCTR_DTLB_REFILL_L1_WRITE,

	[C(ITLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_ITLB_REFILL,
	[C(ITLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_ITLB_REFILL,

	[C(BPU)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_PC_BRANCH_PRED,
	[C(BPU)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
	[C(BPU)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_PC_BRANCH_PRED,
	[C(BPU)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
पूर्ण;

/*
 * Cortex-A7 HW events mapping
 */
अटल स्थिर अचिन्हित armv7_a7_perf_map[PERF_COUNT_HW_MAX] = अणु
	PERF_MAP_ALL_UNSUPPORTED,
	[PERF_COUNT_HW_CPU_CYCLES]		= ARMV7_PERFCTR_CPU_CYCLES,
	[PERF_COUNT_HW_INSTRUCTIONS]		= ARMV7_PERFCTR_INSTR_EXECUTED,
	[PERF_COUNT_HW_CACHE_REFERENCES]	= ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[PERF_COUNT_HW_CACHE_MISSES]		= ARMV7_PERFCTR_L1_DCACHE_REFILL,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= ARMV7_PERFCTR_PC_WRITE,
	[PERF_COUNT_HW_BRANCH_MISSES]		= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
	[PERF_COUNT_HW_BUS_CYCLES]		= ARMV7_PERFCTR_BUS_CYCLES,
पूर्ण;

अटल स्थिर अचिन्हित armv7_a7_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
					[PERF_COUNT_HW_CACHE_OP_MAX]
					[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	PERF_CACHE_MAP_ALL_UNSUPPORTED,

	/*
	 * The perक्रमmance counters करोn't dअगरferentiate between पढ़ो and ग_लिखो
	 * accesses/misses so this isn't strictly correct, but it's the best we
	 * can करो. Writes and पढ़ोs get combined.
	 */
	[C(L1D)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[C(L1D)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_DCACHE_REFILL,
	[C(L1D)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[C(L1D)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_DCACHE_REFILL,

	[C(L1I)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_L1_ICACHE_ACCESS,
	[C(L1I)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_ICACHE_REFILL,

	[C(LL)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_L2_CACHE_ACCESS,
	[C(LL)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L2_CACHE_REFILL,
	[C(LL)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_L2_CACHE_ACCESS,
	[C(LL)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L2_CACHE_REFILL,

	[C(DTLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_DTLB_REFILL,
	[C(DTLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_DTLB_REFILL,

	[C(ITLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_ITLB_REFILL,
	[C(ITLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_ITLB_REFILL,

	[C(BPU)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_PC_BRANCH_PRED,
	[C(BPU)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
	[C(BPU)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_PC_BRANCH_PRED,
	[C(BPU)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
पूर्ण;

/*
 * Cortex-A12 HW events mapping
 */
अटल स्थिर अचिन्हित armv7_a12_perf_map[PERF_COUNT_HW_MAX] = अणु
	PERF_MAP_ALL_UNSUPPORTED,
	[PERF_COUNT_HW_CPU_CYCLES]		= ARMV7_PERFCTR_CPU_CYCLES,
	[PERF_COUNT_HW_INSTRUCTIONS]		= ARMV7_PERFCTR_INSTR_EXECUTED,
	[PERF_COUNT_HW_CACHE_REFERENCES]	= ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[PERF_COUNT_HW_CACHE_MISSES]		= ARMV7_PERFCTR_L1_DCACHE_REFILL,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= ARMV7_A12_PERFCTR_PC_WRITE_SPEC,
	[PERF_COUNT_HW_BRANCH_MISSES]		= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
	[PERF_COUNT_HW_BUS_CYCLES]		= ARMV7_PERFCTR_BUS_CYCLES,
पूर्ण;

अटल स्थिर अचिन्हित armv7_a12_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
					[PERF_COUNT_HW_CACHE_OP_MAX]
					[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	PERF_CACHE_MAP_ALL_UNSUPPORTED,

	[C(L1D)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_A12_PERFCTR_L1_DCACHE_ACCESS_READ,
	[C(L1D)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_DCACHE_REFILL,
	[C(L1D)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_A12_PERFCTR_L1_DCACHE_ACCESS_WRITE,
	[C(L1D)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_DCACHE_REFILL,

	/*
	 * Not all perक्रमmance counters dअगरferentiate between पढ़ो and ग_लिखो
	 * accesses/misses so we're not always strictly correct, but it's the
	 * best we can करो. Writes and पढ़ोs get combined in these हालs.
	 */
	[C(L1I)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_L1_ICACHE_ACCESS,
	[C(L1I)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_ICACHE_REFILL,

	[C(LL)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_A12_PERFCTR_L2_CACHE_ACCESS_READ,
	[C(LL)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L2_CACHE_REFILL,
	[C(LL)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_A12_PERFCTR_L2_CACHE_ACCESS_WRITE,
	[C(LL)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L2_CACHE_REFILL,

	[C(DTLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_DTLB_REFILL,
	[C(DTLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_DTLB_REFILL,
	[C(DTLB)][C(OP_PREFETCH)][C(RESULT_MISS)]	= ARMV7_A12_PERFCTR_PF_TLB_REFILL,

	[C(ITLB)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_ITLB_REFILL,
	[C(ITLB)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_ITLB_REFILL,

	[C(BPU)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_PC_BRANCH_PRED,
	[C(BPU)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
	[C(BPU)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_PC_BRANCH_PRED,
	[C(BPU)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
पूर्ण;

/*
 * Krait HW events mapping
 */
अटल स्थिर अचिन्हित krait_perf_map[PERF_COUNT_HW_MAX] = अणु
	PERF_MAP_ALL_UNSUPPORTED,
	[PERF_COUNT_HW_CPU_CYCLES]	    = ARMV7_PERFCTR_CPU_CYCLES,
	[PERF_COUNT_HW_INSTRUCTIONS]	    = ARMV7_PERFCTR_INSTR_EXECUTED,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = ARMV7_PERFCTR_PC_WRITE,
	[PERF_COUNT_HW_BRANCH_MISSES]	    = ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
	[PERF_COUNT_HW_BUS_CYCLES]	    = ARMV7_PERFCTR_CLOCK_CYCLES,
पूर्ण;

अटल स्थिर अचिन्हित krait_perf_map_no_branch[PERF_COUNT_HW_MAX] = अणु
	PERF_MAP_ALL_UNSUPPORTED,
	[PERF_COUNT_HW_CPU_CYCLES]	    = ARMV7_PERFCTR_CPU_CYCLES,
	[PERF_COUNT_HW_INSTRUCTIONS]	    = ARMV7_PERFCTR_INSTR_EXECUTED,
	[PERF_COUNT_HW_BRANCH_MISSES]	    = ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
	[PERF_COUNT_HW_BUS_CYCLES]	    = ARMV7_PERFCTR_CLOCK_CYCLES,
पूर्ण;

अटल स्थिर अचिन्हित krait_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
					  [PERF_COUNT_HW_CACHE_OP_MAX]
					  [PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	PERF_CACHE_MAP_ALL_UNSUPPORTED,

	/*
	 * The perक्रमmance counters करोn't dअगरferentiate between पढ़ो and ग_लिखो
	 * accesses/misses so this isn't strictly correct, but it's the best we
	 * can करो. Writes and पढ़ोs get combined.
	 */
	[C(L1D)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[C(L1D)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_DCACHE_REFILL,
	[C(L1D)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[C(L1D)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_L1_DCACHE_REFILL,

	[C(L1I)][C(OP_READ)][C(RESULT_ACCESS)]	= KRAIT_PERFCTR_L1_ICACHE_ACCESS,
	[C(L1I)][C(OP_READ)][C(RESULT_MISS)]	= KRAIT_PERFCTR_L1_ICACHE_MISS,

	[C(DTLB)][C(OP_READ)][C(RESULT_ACCESS)]	= KRAIT_PERFCTR_L1_DTLB_ACCESS,
	[C(DTLB)][C(OP_WRITE)][C(RESULT_ACCESS)]	= KRAIT_PERFCTR_L1_DTLB_ACCESS,

	[C(ITLB)][C(OP_READ)][C(RESULT_ACCESS)]	= KRAIT_PERFCTR_L1_ITLB_ACCESS,
	[C(ITLB)][C(OP_WRITE)][C(RESULT_ACCESS)]	= KRAIT_PERFCTR_L1_ITLB_ACCESS,

	[C(BPU)][C(OP_READ)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_PC_BRANCH_PRED,
	[C(BPU)][C(OP_READ)][C(RESULT_MISS)]	= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
	[C(BPU)][C(OP_WRITE)][C(RESULT_ACCESS)]	= ARMV7_PERFCTR_PC_BRANCH_PRED,
	[C(BPU)][C(OP_WRITE)][C(RESULT_MISS)]	= ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
पूर्ण;

/*
 * Scorpion HW events mapping
 */
अटल स्थिर अचिन्हित scorpion_perf_map[PERF_COUNT_HW_MAX] = अणु
	PERF_MAP_ALL_UNSUPPORTED,
	[PERF_COUNT_HW_CPU_CYCLES]	    = ARMV7_PERFCTR_CPU_CYCLES,
	[PERF_COUNT_HW_INSTRUCTIONS]	    = ARMV7_PERFCTR_INSTR_EXECUTED,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = ARMV7_PERFCTR_PC_WRITE,
	[PERF_COUNT_HW_BRANCH_MISSES]	    = ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
	[PERF_COUNT_HW_BUS_CYCLES]	    = ARMV7_PERFCTR_CLOCK_CYCLES,
पूर्ण;

अटल स्थिर अचिन्हित scorpion_perf_cache_map[PERF_COUNT_HW_CACHE_MAX]
					    [PERF_COUNT_HW_CACHE_OP_MAX]
					    [PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	PERF_CACHE_MAP_ALL_UNSUPPORTED,
	/*
	 * The perक्रमmance counters करोn't dअगरferentiate between पढ़ो and ग_लिखो
	 * accesses/misses so this isn't strictly correct, but it's the best we
	 * can करो. Writes and पढ़ोs get combined.
	 */
	[C(L1D)][C(OP_READ)][C(RESULT_ACCESS)] = ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[C(L1D)][C(OP_READ)][C(RESULT_MISS)] = ARMV7_PERFCTR_L1_DCACHE_REFILL,
	[C(L1D)][C(OP_WRITE)][C(RESULT_ACCESS)] = ARMV7_PERFCTR_L1_DCACHE_ACCESS,
	[C(L1D)][C(OP_WRITE)][C(RESULT_MISS)] = ARMV7_PERFCTR_L1_DCACHE_REFILL,
	[C(L1I)][C(OP_READ)][C(RESULT_ACCESS)] = SCORPION_ICACHE_ACCESS,
	[C(L1I)][C(OP_READ)][C(RESULT_MISS)] = SCORPION_ICACHE_MISS,
	/*
	 * Only ITLB misses and DTLB refills are supported.  If users want the
	 * DTLB refills misses a raw counter must be used.
	 */
	[C(DTLB)][C(OP_READ)][C(RESULT_ACCESS)] = SCORPION_DTLB_ACCESS,
	[C(DTLB)][C(OP_READ)][C(RESULT_MISS)] = SCORPION_DTLB_MISS,
	[C(DTLB)][C(OP_WRITE)][C(RESULT_ACCESS)] = SCORPION_DTLB_ACCESS,
	[C(DTLB)][C(OP_WRITE)][C(RESULT_MISS)] = SCORPION_DTLB_MISS,
	[C(ITLB)][C(OP_READ)][C(RESULT_MISS)] = SCORPION_ITLB_MISS,
	[C(ITLB)][C(OP_WRITE)][C(RESULT_MISS)] = SCORPION_ITLB_MISS,
	[C(BPU)][C(OP_READ)][C(RESULT_ACCESS)] = ARMV7_PERFCTR_PC_BRANCH_PRED,
	[C(BPU)][C(OP_READ)][C(RESULT_MISS)] = ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
	[C(BPU)][C(OP_WRITE)][C(RESULT_ACCESS)] = ARMV7_PERFCTR_PC_BRANCH_PRED,
	[C(BPU)][C(OP_WRITE)][C(RESULT_MISS)] = ARMV7_PERFCTR_PC_BRANCH_MIS_PRED,
पूर्ण;

PMU_FORMAT_ATTR(event, "config:0-7");

अटल काष्ठा attribute *armv7_pmu_क्रमmat_attrs[] = अणु
	&क्रमmat_attr_event.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group armv7_pmu_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = armv7_pmu_क्रमmat_attrs,
पूर्ण;

#घोषणा ARMV7_EVENT_ATTR_RESOLVE(m) #m
#घोषणा ARMV7_EVENT_ATTR(name, config) \
	PMU_EVENT_ATTR_STRING(name, armv7_event_attr_##name, \
			      "event=" ARMV7_EVENT_ATTR_RESOLVE(config))

ARMV7_EVENT_ATTR(sw_incr, ARMV7_PERFCTR_PMNC_SW_INCR);
ARMV7_EVENT_ATTR(l1i_cache_refill, ARMV7_PERFCTR_L1_ICACHE_REFILL);
ARMV7_EVENT_ATTR(l1i_tlb_refill, ARMV7_PERFCTR_ITLB_REFILL);
ARMV7_EVENT_ATTR(l1d_cache_refill, ARMV7_PERFCTR_L1_DCACHE_REFILL);
ARMV7_EVENT_ATTR(l1d_cache, ARMV7_PERFCTR_L1_DCACHE_ACCESS);
ARMV7_EVENT_ATTR(l1d_tlb_refill, ARMV7_PERFCTR_DTLB_REFILL);
ARMV7_EVENT_ATTR(ld_retired, ARMV7_PERFCTR_MEM_READ);
ARMV7_EVENT_ATTR(st_retired, ARMV7_PERFCTR_MEM_WRITE);
ARMV7_EVENT_ATTR(inst_retired, ARMV7_PERFCTR_INSTR_EXECUTED);
ARMV7_EVENT_ATTR(exc_taken, ARMV7_PERFCTR_EXC_TAKEN);
ARMV7_EVENT_ATTR(exc_वापस, ARMV7_PERFCTR_EXC_EXECUTED);
ARMV7_EVENT_ATTR(cid_ग_लिखो_retired, ARMV7_PERFCTR_CID_WRITE);
ARMV7_EVENT_ATTR(pc_ग_लिखो_retired, ARMV7_PERFCTR_PC_WRITE);
ARMV7_EVENT_ATTR(br_immed_retired, ARMV7_PERFCTR_PC_IMM_BRANCH);
ARMV7_EVENT_ATTR(br_वापस_retired, ARMV7_PERFCTR_PC_PROC_RETURN);
ARMV7_EVENT_ATTR(unaligned_ldst_retired, ARMV7_PERFCTR_MEM_UNALIGNED_ACCESS);
ARMV7_EVENT_ATTR(br_mis_pred, ARMV7_PERFCTR_PC_BRANCH_MIS_PRED);
ARMV7_EVENT_ATTR(cpu_cycles, ARMV7_PERFCTR_CLOCK_CYCLES);
ARMV7_EVENT_ATTR(br_pred, ARMV7_PERFCTR_PC_BRANCH_PRED);

अटल काष्ठा attribute *armv7_pmuv1_event_attrs[] = अणु
	&armv7_event_attr_sw_incr.attr.attr,
	&armv7_event_attr_l1i_cache_refill.attr.attr,
	&armv7_event_attr_l1i_tlb_refill.attr.attr,
	&armv7_event_attr_l1d_cache_refill.attr.attr,
	&armv7_event_attr_l1d_cache.attr.attr,
	&armv7_event_attr_l1d_tlb_refill.attr.attr,
	&armv7_event_attr_ld_retired.attr.attr,
	&armv7_event_attr_st_retired.attr.attr,
	&armv7_event_attr_inst_retired.attr.attr,
	&armv7_event_attr_exc_taken.attr.attr,
	&armv7_event_attr_exc_वापस.attr.attr,
	&armv7_event_attr_cid_ग_लिखो_retired.attr.attr,
	&armv7_event_attr_pc_ग_लिखो_retired.attr.attr,
	&armv7_event_attr_br_immed_retired.attr.attr,
	&armv7_event_attr_br_वापस_retired.attr.attr,
	&armv7_event_attr_unaligned_ldst_retired.attr.attr,
	&armv7_event_attr_br_mis_pred.attr.attr,
	&armv7_event_attr_cpu_cycles.attr.attr,
	&armv7_event_attr_br_pred.attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group armv7_pmuv1_events_attr_group = अणु
	.name = "events",
	.attrs = armv7_pmuv1_event_attrs,
पूर्ण;

ARMV7_EVENT_ATTR(mem_access, ARMV7_PERFCTR_MEM_ACCESS);
ARMV7_EVENT_ATTR(l1i_cache, ARMV7_PERFCTR_L1_ICACHE_ACCESS);
ARMV7_EVENT_ATTR(l1d_cache_wb, ARMV7_PERFCTR_L1_DCACHE_WB);
ARMV7_EVENT_ATTR(l2d_cache, ARMV7_PERFCTR_L2_CACHE_ACCESS);
ARMV7_EVENT_ATTR(l2d_cache_refill, ARMV7_PERFCTR_L2_CACHE_REFILL);
ARMV7_EVENT_ATTR(l2d_cache_wb, ARMV7_PERFCTR_L2_CACHE_WB);
ARMV7_EVENT_ATTR(bus_access, ARMV7_PERFCTR_BUS_ACCESS);
ARMV7_EVENT_ATTR(memory_error, ARMV7_PERFCTR_MEM_ERROR);
ARMV7_EVENT_ATTR(inst_spec, ARMV7_PERFCTR_INSTR_SPEC);
ARMV7_EVENT_ATTR(ttbr_ग_लिखो_retired, ARMV7_PERFCTR_TTBR_WRITE);
ARMV7_EVENT_ATTR(bus_cycles, ARMV7_PERFCTR_BUS_CYCLES);

अटल काष्ठा attribute *armv7_pmuv2_event_attrs[] = अणु
	&armv7_event_attr_sw_incr.attr.attr,
	&armv7_event_attr_l1i_cache_refill.attr.attr,
	&armv7_event_attr_l1i_tlb_refill.attr.attr,
	&armv7_event_attr_l1d_cache_refill.attr.attr,
	&armv7_event_attr_l1d_cache.attr.attr,
	&armv7_event_attr_l1d_tlb_refill.attr.attr,
	&armv7_event_attr_ld_retired.attr.attr,
	&armv7_event_attr_st_retired.attr.attr,
	&armv7_event_attr_inst_retired.attr.attr,
	&armv7_event_attr_exc_taken.attr.attr,
	&armv7_event_attr_exc_वापस.attr.attr,
	&armv7_event_attr_cid_ग_लिखो_retired.attr.attr,
	&armv7_event_attr_pc_ग_लिखो_retired.attr.attr,
	&armv7_event_attr_br_immed_retired.attr.attr,
	&armv7_event_attr_br_वापस_retired.attr.attr,
	&armv7_event_attr_unaligned_ldst_retired.attr.attr,
	&armv7_event_attr_br_mis_pred.attr.attr,
	&armv7_event_attr_cpu_cycles.attr.attr,
	&armv7_event_attr_br_pred.attr.attr,
	&armv7_event_attr_mem_access.attr.attr,
	&armv7_event_attr_l1i_cache.attr.attr,
	&armv7_event_attr_l1d_cache_wb.attr.attr,
	&armv7_event_attr_l2d_cache.attr.attr,
	&armv7_event_attr_l2d_cache_refill.attr.attr,
	&armv7_event_attr_l2d_cache_wb.attr.attr,
	&armv7_event_attr_bus_access.attr.attr,
	&armv7_event_attr_memory_error.attr.attr,
	&armv7_event_attr_inst_spec.attr.attr,
	&armv7_event_attr_ttbr_ग_लिखो_retired.attr.attr,
	&armv7_event_attr_bus_cycles.attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group armv7_pmuv2_events_attr_group = अणु
	.name = "events",
	.attrs = armv7_pmuv2_event_attrs,
पूर्ण;

/*
 * Perf Events' indices
 */
#घोषणा	ARMV7_IDX_CYCLE_COUNTER	0
#घोषणा	ARMV7_IDX_COUNTER0	1
#घोषणा	ARMV7_IDX_COUNTER_LAST(cpu_pmu) \
	(ARMV7_IDX_CYCLE_COUNTER + cpu_pmu->num_events - 1)

#घोषणा	ARMV7_MAX_COUNTERS	32
#घोषणा	ARMV7_COUNTER_MASK	(ARMV7_MAX_COUNTERS - 1)

/*
 * ARMv7 low level PMNC access
 */

/*
 * Perf Event to low level counters mapping
 */
#घोषणा	ARMV7_IDX_TO_COUNTER(x)	\
	(((x) - ARMV7_IDX_COUNTER0) & ARMV7_COUNTER_MASK)

/*
 * Per-CPU PMNC: config reg
 */
#घोषणा ARMV7_PMNC_E		(1 << 0) /* Enable all counters */
#घोषणा ARMV7_PMNC_P		(1 << 1) /* Reset all counters */
#घोषणा ARMV7_PMNC_C		(1 << 2) /* Cycle counter reset */
#घोषणा ARMV7_PMNC_D		(1 << 3) /* CCNT counts every 64th cpu cycle */
#घोषणा ARMV7_PMNC_X		(1 << 4) /* Export to ETM */
#घोषणा ARMV7_PMNC_DP		(1 << 5) /* Disable CCNT अगर non-invasive debug*/
#घोषणा	ARMV7_PMNC_N_SHIFT	11	 /* Number of counters supported */
#घोषणा	ARMV7_PMNC_N_MASK	0x1f
#घोषणा	ARMV7_PMNC_MASK		0x3f	 /* Mask क्रम writable bits */

/*
 * FLAG: counters overflow flag status reg
 */
#घोषणा	ARMV7_FLAG_MASK		0xffffffff	/* Mask क्रम writable bits */
#घोषणा	ARMV7_OVERFLOWED_MASK	ARMV7_FLAG_MASK

/*
 * PMXEVTYPER: Event selection reg
 */
#घोषणा	ARMV7_EVTYPE_MASK	0xc80000ff	/* Mask क्रम writable bits */
#घोषणा	ARMV7_EVTYPE_EVENT	0xff		/* Mask क्रम EVENT bits */

/*
 * Event filters क्रम PMUv2
 */
#घोषणा	ARMV7_EXCLUDE_PL1	BIT(31)
#घोषणा	ARMV7_EXCLUDE_USER	BIT(30)
#घोषणा	ARMV7_INCLUDE_HYP	BIT(27)

/*
 * Secure debug enable reg
 */
#घोषणा ARMV7_SDER_SUNIDEN	BIT(1) /* Permit non-invasive debug */

अटल अंतरभूत u32 armv7_pmnc_पढ़ो(व्योम)
अणु
	u32 val;
	यंत्र अस्थिर("mrc p15, 0, %0, c9, c12, 0" : "=r"(val));
	वापस val;
पूर्ण

अटल अंतरभूत व्योम armv7_pmnc_ग_लिखो(u32 val)
अणु
	val &= ARMV7_PMNC_MASK;
	isb();
	यंत्र अस्थिर("mcr p15, 0, %0, c9, c12, 0" : : "r"(val));
पूर्ण

अटल अंतरभूत पूर्णांक armv7_pmnc_has_overflowed(u32 pmnc)
अणु
	वापस pmnc & ARMV7_OVERFLOWED_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक armv7_pmnc_counter_valid(काष्ठा arm_pmu *cpu_pmu, पूर्णांक idx)
अणु
	वापस idx >= ARMV7_IDX_CYCLE_COUNTER &&
		idx <= ARMV7_IDX_COUNTER_LAST(cpu_pmu);
पूर्ण

अटल अंतरभूत पूर्णांक armv7_pmnc_counter_has_overflowed(u32 pmnc, पूर्णांक idx)
अणु
	वापस pmnc & BIT(ARMV7_IDX_TO_COUNTER(idx));
पूर्ण

अटल अंतरभूत व्योम armv7_pmnc_select_counter(पूर्णांक idx)
अणु
	u32 counter = ARMV7_IDX_TO_COUNTER(idx);
	यंत्र अस्थिर("mcr p15, 0, %0, c9, c12, 5" : : "r" (counter));
	isb();
पूर्ण

अटल अंतरभूत u64 armv7pmu_पढ़ो_counter(काष्ठा perf_event *event)
अणु
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;
	u32 value = 0;

	अगर (!armv7_pmnc_counter_valid(cpu_pmu, idx)) अणु
		pr_err("CPU%u reading wrong counter %d\n",
			smp_processor_id(), idx);
	पूर्ण अन्यथा अगर (idx == ARMV7_IDX_CYCLE_COUNTER) अणु
		यंत्र अस्थिर("mrc p15, 0, %0, c9, c13, 0" : "=r" (value));
	पूर्ण अन्यथा अणु
		armv7_pmnc_select_counter(idx);
		यंत्र अस्थिर("mrc p15, 0, %0, c9, c13, 2" : "=r" (value));
	पूर्ण

	वापस value;
पूर्ण

अटल अंतरभूत व्योम armv7pmu_ग_लिखो_counter(काष्ठा perf_event *event, u64 value)
अणु
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	अगर (!armv7_pmnc_counter_valid(cpu_pmu, idx)) अणु
		pr_err("CPU%u writing wrong counter %d\n",
			smp_processor_id(), idx);
	पूर्ण अन्यथा अगर (idx == ARMV7_IDX_CYCLE_COUNTER) अणु
		यंत्र अस्थिर("mcr p15, 0, %0, c9, c13, 0" : : "r" (value));
	पूर्ण अन्यथा अणु
		armv7_pmnc_select_counter(idx);
		यंत्र अस्थिर("mcr p15, 0, %0, c9, c13, 2" : : "r" (value));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम armv7_pmnc_ग_लिखो_evtsel(पूर्णांक idx, u32 val)
अणु
	armv7_pmnc_select_counter(idx);
	val &= ARMV7_EVTYPE_MASK;
	यंत्र अस्थिर("mcr p15, 0, %0, c9, c13, 1" : : "r" (val));
पूर्ण

अटल अंतरभूत व्योम armv7_pmnc_enable_counter(पूर्णांक idx)
अणु
	u32 counter = ARMV7_IDX_TO_COUNTER(idx);
	यंत्र अस्थिर("mcr p15, 0, %0, c9, c12, 1" : : "r" (BIT(counter)));
पूर्ण

अटल अंतरभूत व्योम armv7_pmnc_disable_counter(पूर्णांक idx)
अणु
	u32 counter = ARMV7_IDX_TO_COUNTER(idx);
	यंत्र अस्थिर("mcr p15, 0, %0, c9, c12, 2" : : "r" (BIT(counter)));
पूर्ण

अटल अंतरभूत व्योम armv7_pmnc_enable_पूर्णांकens(पूर्णांक idx)
अणु
	u32 counter = ARMV7_IDX_TO_COUNTER(idx);
	यंत्र अस्थिर("mcr p15, 0, %0, c9, c14, 1" : : "r" (BIT(counter)));
पूर्ण

अटल अंतरभूत व्योम armv7_pmnc_disable_पूर्णांकens(पूर्णांक idx)
अणु
	u32 counter = ARMV7_IDX_TO_COUNTER(idx);
	यंत्र अस्थिर("mcr p15, 0, %0, c9, c14, 2" : : "r" (BIT(counter)));
	isb();
	/* Clear the overflow flag in हाल an पूर्णांकerrupt is pending. */
	यंत्र अस्थिर("mcr p15, 0, %0, c9, c12, 3" : : "r" (BIT(counter)));
	isb();
पूर्ण

अटल अंतरभूत u32 armv7_pmnc_getreset_flags(व्योम)
अणु
	u32 val;

	/* Read */
	यंत्र अस्थिर("mrc p15, 0, %0, c9, c12, 3" : "=r" (val));

	/* Write to clear flags */
	val &= ARMV7_FLAG_MASK;
	यंत्र अस्थिर("mcr p15, 0, %0, c9, c12, 3" : : "r" (val));

	वापस val;
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम armv7_pmnc_dump_regs(काष्ठा arm_pmu *cpu_pmu)
अणु
	u32 val;
	अचिन्हित पूर्णांक cnt;

	pr_info("PMNC registers dump:\n");

	यंत्र अस्थिर("mrc p15, 0, %0, c9, c12, 0" : "=r" (val));
	pr_info("PMNC  =0x%08x\n", val);

	यंत्र अस्थिर("mrc p15, 0, %0, c9, c12, 1" : "=r" (val));
	pr_info("CNTENS=0x%08x\n", val);

	यंत्र अस्थिर("mrc p15, 0, %0, c9, c14, 1" : "=r" (val));
	pr_info("INTENS=0x%08x\n", val);

	यंत्र अस्थिर("mrc p15, 0, %0, c9, c12, 3" : "=r" (val));
	pr_info("FLAGS =0x%08x\n", val);

	यंत्र अस्थिर("mrc p15, 0, %0, c9, c12, 5" : "=r" (val));
	pr_info("SELECT=0x%08x\n", val);

	यंत्र अस्थिर("mrc p15, 0, %0, c9, c13, 0" : "=r" (val));
	pr_info("CCNT  =0x%08x\n", val);

	क्रम (cnt = ARMV7_IDX_COUNTER0;
			cnt <= ARMV7_IDX_COUNTER_LAST(cpu_pmu); cnt++) अणु
		armv7_pmnc_select_counter(cnt);
		यंत्र अस्थिर("mrc p15, 0, %0, c9, c13, 2" : "=r" (val));
		pr_info("CNT[%d] count =0x%08x\n",
			ARMV7_IDX_TO_COUNTER(cnt), val);
		यंत्र अस्थिर("mrc p15, 0, %0, c9, c13, 1" : "=r" (val));
		pr_info("CNT[%d] evtsel=0x%08x\n",
			ARMV7_IDX_TO_COUNTER(cnt), val);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम armv7pmu_enable_event(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);
	पूर्णांक idx = hwc->idx;

	अगर (!armv7_pmnc_counter_valid(cpu_pmu, idx)) अणु
		pr_err("CPU%u enabling wrong PMNC counter IRQ enable %d\n",
			smp_processor_id(), idx);
		वापस;
	पूर्ण

	/*
	 * Enable counter and पूर्णांकerrupt, and set the counter to count
	 * the event that we're पूर्णांकerested in.
	 */
	raw_spin_lock_irqsave(&events->pmu_lock, flags);

	/*
	 * Disable counter
	 */
	armv7_pmnc_disable_counter(idx);

	/*
	 * Set event (अगर destined क्रम PMNx counters)
	 * We only need to set the event क्रम the cycle counter अगर we
	 * have the ability to perक्रमm event filtering.
	 */
	अगर (cpu_pmu->set_event_filter || idx != ARMV7_IDX_CYCLE_COUNTER)
		armv7_pmnc_ग_लिखो_evtsel(idx, hwc->config_base);

	/*
	 * Enable पूर्णांकerrupt क्रम this counter
	 */
	armv7_pmnc_enable_पूर्णांकens(idx);

	/*
	 * Enable counter
	 */
	armv7_pmnc_enable_counter(idx);

	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल व्योम armv7pmu_disable_event(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);
	पूर्णांक idx = hwc->idx;

	अगर (!armv7_pmnc_counter_valid(cpu_pmu, idx)) अणु
		pr_err("CPU%u disabling wrong PMNC counter IRQ enable %d\n",
			smp_processor_id(), idx);
		वापस;
	पूर्ण

	/*
	 * Disable counter and पूर्णांकerrupt
	 */
	raw_spin_lock_irqsave(&events->pmu_lock, flags);

	/*
	 * Disable counter
	 */
	armv7_pmnc_disable_counter(idx);

	/*
	 * Disable पूर्णांकerrupt क्रम this counter
	 */
	armv7_pmnc_disable_पूर्णांकens(idx);

	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल irqवापस_t armv7pmu_handle_irq(काष्ठा arm_pmu *cpu_pmu)
अणु
	u32 pmnc;
	काष्ठा perf_sample_data data;
	काष्ठा pmu_hw_events *cpuc = this_cpu_ptr(cpu_pmu->hw_events);
	काष्ठा pt_regs *regs;
	पूर्णांक idx;

	/*
	 * Get and reset the IRQ flags
	 */
	pmnc = armv7_pmnc_getreset_flags();

	/*
	 * Did an overflow occur?
	 */
	अगर (!armv7_pmnc_has_overflowed(pmnc))
		वापस IRQ_NONE;

	/*
	 * Handle the counter(s) overflow(s)
	 */
	regs = get_irq_regs();

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
		अगर (!armv7_pmnc_counter_has_overflowed(pmnc, idx))
			जारी;

		hwc = &event->hw;
		armpmu_event_update(event);
		perf_sample_data_init(&data, 0, hwc->last_period);
		अगर (!armpmu_event_set_period(event))
			जारी;

		अगर (perf_event_overflow(event, &data, regs))
			cpu_pmu->disable(event);
	पूर्ण

	/*
	 * Handle the pending perf events.
	 *
	 * Note: this call *must* be run with पूर्णांकerrupts disabled. For
	 * platक्रमms that can have the PMU पूर्णांकerrupts उठाओd as an NMI, this
	 * will not work.
	 */
	irq_work_run();

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम armv7pmu_start(काष्ठा arm_pmu *cpu_pmu)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);

	raw_spin_lock_irqsave(&events->pmu_lock, flags);
	/* Enable all counters */
	armv7_pmnc_ग_लिखो(armv7_pmnc_पढ़ो() | ARMV7_PMNC_E);
	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल व्योम armv7pmu_stop(काष्ठा arm_pmu *cpu_pmu)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);

	raw_spin_lock_irqsave(&events->pmu_lock, flags);
	/* Disable all counters */
	armv7_pmnc_ग_लिखो(armv7_pmnc_पढ़ो() & ~ARMV7_PMNC_E);
	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल पूर्णांक armv7pmu_get_event_idx(काष्ठा pmu_hw_events *cpuc,
				  काष्ठा perf_event *event)
अणु
	पूर्णांक idx;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	अचिन्हित दीर्घ evtype = hwc->config_base & ARMV7_EVTYPE_EVENT;

	/* Always place a cycle counter पूर्णांकo the cycle counter. */
	अगर (evtype == ARMV7_PERFCTR_CPU_CYCLES) अणु
		अगर (test_and_set_bit(ARMV7_IDX_CYCLE_COUNTER, cpuc->used_mask))
			वापस -EAGAIN;

		वापस ARMV7_IDX_CYCLE_COUNTER;
	पूर्ण

	/*
	 * For anything other than a cycle counter, try and use
	 * the events counters
	 */
	क्रम (idx = ARMV7_IDX_COUNTER0; idx < cpu_pmu->num_events; ++idx) अणु
		अगर (!test_and_set_bit(idx, cpuc->used_mask))
			वापस idx;
	पूर्ण

	/* The counters are all in use. */
	वापस -EAGAIN;
पूर्ण

अटल व्योम armv7pmu_clear_event_idx(काष्ठा pmu_hw_events *cpuc,
				     काष्ठा perf_event *event)
अणु
	clear_bit(event->hw.idx, cpuc->used_mask);
पूर्ण

/*
 * Add an event filter to a given event. This will only work क्रम PMUv2 PMUs.
 */
अटल पूर्णांक armv7pmu_set_event_filter(काष्ठा hw_perf_event *event,
				     काष्ठा perf_event_attr *attr)
अणु
	अचिन्हित दीर्घ config_base = 0;

	अगर (attr->exclude_idle)
		वापस -EPERM;
	अगर (attr->exclude_user)
		config_base |= ARMV7_EXCLUDE_USER;
	अगर (attr->exclude_kernel)
		config_base |= ARMV7_EXCLUDE_PL1;
	अगर (!attr->exclude_hv)
		config_base |= ARMV7_INCLUDE_HYP;

	/*
	 * Install the filter पूर्णांकo config_base as this is used to
	 * स्थिरruct the event type.
	 */
	event->config_base = config_base;

	वापस 0;
पूर्ण

अटल व्योम armv7pmu_reset(व्योम *info)
अणु
	काष्ठा arm_pmu *cpu_pmu = (काष्ठा arm_pmu *)info;
	u32 idx, nb_cnt = cpu_pmu->num_events, val;

	अगर (cpu_pmu->secure_access) अणु
		यंत्र अस्थिर("mrc p15, 0, %0, c1, c1, 1" : "=r" (val));
		val |= ARMV7_SDER_SUNIDEN;
		यंत्र अस्थिर("mcr p15, 0, %0, c1, c1, 1" : : "r" (val));
	पूर्ण

	/* The counter and पूर्णांकerrupt enable रेजिस्टरs are unknown at reset. */
	क्रम (idx = ARMV7_IDX_CYCLE_COUNTER; idx < nb_cnt; ++idx) अणु
		armv7_pmnc_disable_counter(idx);
		armv7_pmnc_disable_पूर्णांकens(idx);
	पूर्ण

	/* Initialize & Reset PMNC: C and P bits */
	armv7_pmnc_ग_लिखो(ARMV7_PMNC_P | ARMV7_PMNC_C);
पूर्ण

अटल पूर्णांक armv7_a8_map_event(काष्ठा perf_event *event)
अणु
	वापस armpmu_map_event(event, &armv7_a8_perf_map,
				&armv7_a8_perf_cache_map, 0xFF);
पूर्ण

अटल पूर्णांक armv7_a9_map_event(काष्ठा perf_event *event)
अणु
	वापस armpmu_map_event(event, &armv7_a9_perf_map,
				&armv7_a9_perf_cache_map, 0xFF);
पूर्ण

अटल पूर्णांक armv7_a5_map_event(काष्ठा perf_event *event)
अणु
	वापस armpmu_map_event(event, &armv7_a5_perf_map,
				&armv7_a5_perf_cache_map, 0xFF);
पूर्ण

अटल पूर्णांक armv7_a15_map_event(काष्ठा perf_event *event)
अणु
	वापस armpmu_map_event(event, &armv7_a15_perf_map,
				&armv7_a15_perf_cache_map, 0xFF);
पूर्ण

अटल पूर्णांक armv7_a7_map_event(काष्ठा perf_event *event)
अणु
	वापस armpmu_map_event(event, &armv7_a7_perf_map,
				&armv7_a7_perf_cache_map, 0xFF);
पूर्ण

अटल पूर्णांक armv7_a12_map_event(काष्ठा perf_event *event)
अणु
	वापस armpmu_map_event(event, &armv7_a12_perf_map,
				&armv7_a12_perf_cache_map, 0xFF);
पूर्ण

अटल पूर्णांक krait_map_event(काष्ठा perf_event *event)
अणु
	वापस armpmu_map_event(event, &krait_perf_map,
				&krait_perf_cache_map, 0xFFFFF);
पूर्ण

अटल पूर्णांक krait_map_event_no_branch(काष्ठा perf_event *event)
अणु
	वापस armpmu_map_event(event, &krait_perf_map_no_branch,
				&krait_perf_cache_map, 0xFFFFF);
पूर्ण

अटल पूर्णांक scorpion_map_event(काष्ठा perf_event *event)
अणु
	वापस armpmu_map_event(event, &scorpion_perf_map,
				&scorpion_perf_cache_map, 0xFFFFF);
पूर्ण

अटल व्योम armv7pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	cpu_pmu->handle_irq	= armv7pmu_handle_irq;
	cpu_pmu->enable		= armv7pmu_enable_event;
	cpu_pmu->disable	= armv7pmu_disable_event;
	cpu_pmu->पढ़ो_counter	= armv7pmu_पढ़ो_counter;
	cpu_pmu->ग_लिखो_counter	= armv7pmu_ग_लिखो_counter;
	cpu_pmu->get_event_idx	= armv7pmu_get_event_idx;
	cpu_pmu->clear_event_idx = armv7pmu_clear_event_idx;
	cpu_pmu->start		= armv7pmu_start;
	cpu_pmu->stop		= armv7pmu_stop;
	cpu_pmu->reset		= armv7pmu_reset;
पूर्ण;

अटल व्योम armv7_पढ़ो_num_pmnc_events(व्योम *info)
अणु
	पूर्णांक *nb_cnt = info;

	/* Read the nb of CNTx counters supported from PMNC */
	*nb_cnt = (armv7_pmnc_पढ़ो() >> ARMV7_PMNC_N_SHIFT) & ARMV7_PMNC_N_MASK;

	/* Add the CPU cycles counter */
	*nb_cnt += 1;
पूर्ण

अटल पूर्णांक armv7_probe_num_events(काष्ठा arm_pmu *arm_pmu)
अणु
	वापस smp_call_function_any(&arm_pmu->supported_cpus,
				     armv7_पढ़ो_num_pmnc_events,
				     &arm_pmu->num_events, 1);
पूर्ण

अटल पूर्णांक armv7_a8_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	armv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "armv7_cortex_a8";
	cpu_pmu->map_event	= armv7_a8_map_event;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_EVENTS] =
		&armv7_pmuv1_events_attr_group;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_FORMATS] =
		&armv7_pmu_क्रमmat_attr_group;
	वापस armv7_probe_num_events(cpu_pmu);
पूर्ण

अटल पूर्णांक armv7_a9_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	armv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "armv7_cortex_a9";
	cpu_pmu->map_event	= armv7_a9_map_event;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_EVENTS] =
		&armv7_pmuv1_events_attr_group;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_FORMATS] =
		&armv7_pmu_क्रमmat_attr_group;
	वापस armv7_probe_num_events(cpu_pmu);
पूर्ण

अटल पूर्णांक armv7_a5_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	armv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "armv7_cortex_a5";
	cpu_pmu->map_event	= armv7_a5_map_event;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_EVENTS] =
		&armv7_pmuv1_events_attr_group;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_FORMATS] =
		&armv7_pmu_क्रमmat_attr_group;
	वापस armv7_probe_num_events(cpu_pmu);
पूर्ण

अटल पूर्णांक armv7_a15_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	armv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "armv7_cortex_a15";
	cpu_pmu->map_event	= armv7_a15_map_event;
	cpu_pmu->set_event_filter = armv7pmu_set_event_filter;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_EVENTS] =
		&armv7_pmuv2_events_attr_group;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_FORMATS] =
		&armv7_pmu_क्रमmat_attr_group;
	वापस armv7_probe_num_events(cpu_pmu);
पूर्ण

अटल पूर्णांक armv7_a7_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	armv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "armv7_cortex_a7";
	cpu_pmu->map_event	= armv7_a7_map_event;
	cpu_pmu->set_event_filter = armv7pmu_set_event_filter;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_EVENTS] =
		&armv7_pmuv2_events_attr_group;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_FORMATS] =
		&armv7_pmu_क्रमmat_attr_group;
	वापस armv7_probe_num_events(cpu_pmu);
पूर्ण

अटल पूर्णांक armv7_a12_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	armv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "armv7_cortex_a12";
	cpu_pmu->map_event	= armv7_a12_map_event;
	cpu_pmu->set_event_filter = armv7pmu_set_event_filter;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_EVENTS] =
		&armv7_pmuv2_events_attr_group;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_FORMATS] =
		&armv7_pmu_क्रमmat_attr_group;
	वापस armv7_probe_num_events(cpu_pmu);
पूर्ण

अटल पूर्णांक armv7_a17_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	पूर्णांक ret = armv7_a12_pmu_init(cpu_pmu);
	cpu_pmu->name = "armv7_cortex_a17";
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_EVENTS] =
		&armv7_pmuv2_events_attr_group;
	cpu_pmu->attr_groups[ARMPMU_ATTR_GROUP_FORMATS] =
		&armv7_pmu_क्रमmat_attr_group;
	वापस ret;
पूर्ण

/*
 * Krait Perक्रमmance Monitor Region Event Selection Register (PMRESRn)
 *
 *            31   30     24     16     8      0
 *            +--------------------------------+
 *  PMRESR0   | EN |  CC  |  CC  |  CC  |  CC  |   N = 1, R = 0
 *            +--------------------------------+
 *  PMRESR1   | EN |  CC  |  CC  |  CC  |  CC  |   N = 1, R = 1
 *            +--------------------------------+
 *  PMRESR2   | EN |  CC  |  CC  |  CC  |  CC  |   N = 1, R = 2
 *            +--------------------------------+
 *  VPMRESR0  | EN |  CC  |  CC  |  CC  |  CC  |   N = 2, R = ?
 *            +--------------------------------+
 *              EN | G=3  | G=2  | G=1  | G=0
 *
 *  Event Encoding:
 *
 *      hwc->config_base = 0xNRCCG
 *
 *      N  = prefix, 1 क्रम Krait CPU (PMRESRn), 2 क्रम Vक्रमागत VFP (VPMRESR)
 *      R  = region रेजिस्टर
 *      CC = class of events the group G is choosing from
 *      G  = group or particular event
 *
 *  Example: 0x12021 is a Krait CPU event in PMRESR2's group 1 with code 2
 *
 *  A region (R) corresponds to a piece of the CPU (execution unit, inकाष्ठाion
 *  unit, etc.) जबतक the event code (CC) corresponds to a particular class of
 *  events (पूर्णांकerrupts क्रम example). An event code is broken करोwn पूर्णांकo
 *  groups (G) that can be mapped पूर्णांकo the PMU (irq, fiqs, and irq+fiqs क्रम
 *  example).
 */

#घोषणा KRAIT_EVENT		(1 << 16)
#घोषणा VENUM_EVENT		(2 << 16)
#घोषणा KRAIT_EVENT_MASK	(KRAIT_EVENT | VENUM_EVENT)
#घोषणा PMRESRn_EN		BIT(31)

#घोषणा EVENT_REGION(event)	(((event) >> 12) & 0xf)		/* R */
#घोषणा EVENT_GROUP(event)	((event) & 0xf)			/* G */
#घोषणा EVENT_CODE(event)	(((event) >> 4) & 0xff)		/* CC */
#घोषणा EVENT_VENUM(event)	(!!(event & VENUM_EVENT))	/* N=2 */
#घोषणा EVENT_CPU(event)	(!!(event & KRAIT_EVENT))	/* N=1 */

अटल u32 krait_पढ़ो_pmresrn(पूर्णांक n)
अणु
	u32 val;

	चयन (n) अणु
	हाल 0:
		यंत्र अस्थिर("mrc p15, 1, %0, c9, c15, 0" : "=r" (val));
		अवरोध;
	हाल 1:
		यंत्र अस्थिर("mrc p15, 1, %0, c9, c15, 1" : "=r" (val));
		अवरोध;
	हाल 2:
		यंत्र अस्थिर("mrc p15, 1, %0, c9, c15, 2" : "=r" (val));
		अवरोध;
	शेष:
		BUG(); /* Should be validated in krait_pmu_get_event_idx() */
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम krait_ग_लिखो_pmresrn(पूर्णांक n, u32 val)
अणु
	चयन (n) अणु
	हाल 0:
		यंत्र अस्थिर("mcr p15, 1, %0, c9, c15, 0" : : "r" (val));
		अवरोध;
	हाल 1:
		यंत्र अस्थिर("mcr p15, 1, %0, c9, c15, 1" : : "r" (val));
		अवरोध;
	हाल 2:
		यंत्र अस्थिर("mcr p15, 1, %0, c9, c15, 2" : : "r" (val));
		अवरोध;
	शेष:
		BUG(); /* Should be validated in krait_pmu_get_event_idx() */
	पूर्ण
पूर्ण

अटल u32 vक्रमागत_पढ़ो_pmresr(व्योम)
अणु
	u32 val;
	यंत्र अस्थिर("mrc p10, 7, %0, c11, c0, 0" : "=r" (val));
	वापस val;
पूर्ण

अटल व्योम vक्रमागत_ग_लिखो_pmresr(u32 val)
अणु
	यंत्र अस्थिर("mcr p10, 7, %0, c11, c0, 0" : : "r" (val));
पूर्ण

अटल व्योम vक्रमागत_pre_pmresr(u32 *vक्रमागत_orig_val, u32 *fp_orig_val)
अणु
	u32 vक्रमागत_new_val;
	u32 fp_new_val;

	BUG_ON(preemptible());
	/* CPACR Enable CP10 and CP11 access */
	*vक्रमागत_orig_val = get_copro_access();
	vक्रमागत_new_val = *vक्रमागत_orig_val | CPACC_SVC(10) | CPACC_SVC(11);
	set_copro_access(vक्रमागत_new_val);

	/* Enable FPEXC */
	*fp_orig_val = fmrx(FPEXC);
	fp_new_val = *fp_orig_val | FPEXC_EN;
	fmxr(FPEXC, fp_new_val);
पूर्ण

अटल व्योम vक्रमागत_post_pmresr(u32 vक्रमागत_orig_val, u32 fp_orig_val)
अणु
	BUG_ON(preemptible());
	/* Restore FPEXC */
	fmxr(FPEXC, fp_orig_val);
	isb();
	/* Restore CPACR */
	set_copro_access(vक्रमागत_orig_val);
पूर्ण

अटल u32 krait_get_pmresrn_event(अचिन्हित पूर्णांक region)
अणु
	अटल स्थिर u32 pmresrn_table[] = अणु KRAIT_PMRESR0_GROUP0,
					     KRAIT_PMRESR1_GROUP0,
					     KRAIT_PMRESR2_GROUP0 पूर्ण;
	वापस pmresrn_table[region];
पूर्ण

अटल व्योम krait_evt_setup(पूर्णांक idx, u32 config_base)
अणु
	u32 val;
	u32 mask;
	u32 vval, fval;
	अचिन्हित पूर्णांक region = EVENT_REGION(config_base);
	अचिन्हित पूर्णांक group = EVENT_GROUP(config_base);
	अचिन्हित पूर्णांक code = EVENT_CODE(config_base);
	अचिन्हित पूर्णांक group_shअगरt;
	bool vक्रमागत_event = EVENT_VENUM(config_base);

	group_shअगरt = group * 8;
	mask = 0xff << group_shअगरt;

	/* Configure evtsel क्रम the region and group */
	अगर (vक्रमागत_event)
		val = KRAIT_VPMRESR0_GROUP0;
	अन्यथा
		val = krait_get_pmresrn_event(region);
	val += group;
	/* Mix in mode-exclusion bits */
	val |= config_base & (ARMV7_EXCLUDE_USER | ARMV7_EXCLUDE_PL1);
	armv7_pmnc_ग_लिखो_evtsel(idx, val);

	अगर (vक्रमागत_event) अणु
		vक्रमागत_pre_pmresr(&vval, &fval);
		val = vक्रमागत_पढ़ो_pmresr();
		val &= ~mask;
		val |= code << group_shअगरt;
		val |= PMRESRn_EN;
		vक्रमागत_ग_लिखो_pmresr(val);
		vक्रमागत_post_pmresr(vval, fval);
	पूर्ण अन्यथा अणु
		val = krait_पढ़ो_pmresrn(region);
		val &= ~mask;
		val |= code << group_shअगरt;
		val |= PMRESRn_EN;
		krait_ग_लिखो_pmresrn(region, val);
	पूर्ण
पूर्ण

अटल u32 clear_pmresrn_group(u32 val, पूर्णांक group)
अणु
	u32 mask;
	पूर्णांक group_shअगरt;

	group_shअगरt = group * 8;
	mask = 0xff << group_shअगरt;
	val &= ~mask;

	/* Don't clear enable bit if entire region isn't disabled */
	अगर (val & ~PMRESRn_EN)
		वापस val |= PMRESRn_EN;

	वापस 0;
पूर्ण

अटल व्योम krait_clearpmu(u32 config_base)
अणु
	u32 val;
	u32 vval, fval;
	अचिन्हित पूर्णांक region = EVENT_REGION(config_base);
	अचिन्हित पूर्णांक group = EVENT_GROUP(config_base);
	bool vक्रमागत_event = EVENT_VENUM(config_base);

	अगर (vक्रमागत_event) अणु
		vक्रमागत_pre_pmresr(&vval, &fval);
		val = vक्रमागत_पढ़ो_pmresr();
		val = clear_pmresrn_group(val, group);
		vक्रमागत_ग_लिखो_pmresr(val);
		vक्रमागत_post_pmresr(vval, fval);
	पूर्ण अन्यथा अणु
		val = krait_पढ़ो_pmresrn(region);
		val = clear_pmresrn_group(val, group);
		krait_ग_लिखो_pmresrn(region, val);
	पूर्ण
पूर्ण

अटल व्योम krait_pmu_disable_event(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);

	/* Disable counter and पूर्णांकerrupt */
	raw_spin_lock_irqsave(&events->pmu_lock, flags);

	/* Disable counter */
	armv7_pmnc_disable_counter(idx);

	/*
	 * Clear pmresr code (अगर destined क्रम PMNx counters)
	 */
	अगर (hwc->config_base & KRAIT_EVENT_MASK)
		krait_clearpmu(hwc->config_base);

	/* Disable पूर्णांकerrupt क्रम this counter */
	armv7_pmnc_disable_पूर्णांकens(idx);

	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल व्योम krait_pmu_enable_event(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);

	/*
	 * Enable counter and पूर्णांकerrupt, and set the counter to count
	 * the event that we're पूर्णांकerested in.
	 */
	raw_spin_lock_irqsave(&events->pmu_lock, flags);

	/* Disable counter */
	armv7_pmnc_disable_counter(idx);

	/*
	 * Set event (अगर destined क्रम PMNx counters)
	 * We set the event क्रम the cycle counter because we
	 * have the ability to perक्रमm event filtering.
	 */
	अगर (hwc->config_base & KRAIT_EVENT_MASK)
		krait_evt_setup(idx, hwc->config_base);
	अन्यथा
		armv7_pmnc_ग_लिखो_evtsel(idx, hwc->config_base);

	/* Enable पूर्णांकerrupt क्रम this counter */
	armv7_pmnc_enable_पूर्णांकens(idx);

	/* Enable counter */
	armv7_pmnc_enable_counter(idx);

	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल व्योम krait_pmu_reset(व्योम *info)
अणु
	u32 vval, fval;
	काष्ठा arm_pmu *cpu_pmu = info;
	u32 idx, nb_cnt = cpu_pmu->num_events;

	armv7pmu_reset(info);

	/* Clear all pmresrs */
	krait_ग_लिखो_pmresrn(0, 0);
	krait_ग_लिखो_pmresrn(1, 0);
	krait_ग_लिखो_pmresrn(2, 0);

	vक्रमागत_pre_pmresr(&vval, &fval);
	vक्रमागत_ग_लिखो_pmresr(0);
	vक्रमागत_post_pmresr(vval, fval);

	/* Reset PMxEVNCTCR to sane शेष */
	क्रम (idx = ARMV7_IDX_CYCLE_COUNTER; idx < nb_cnt; ++idx) अणु
		armv7_pmnc_select_counter(idx);
		यंत्र अस्थिर("mcr p15, 0, %0, c9, c15, 0" : : "r" (0));
	पूर्ण

पूर्ण

अटल पूर्णांक krait_event_to_bit(काष्ठा perf_event *event, अचिन्हित पूर्णांक region,
			      अचिन्हित पूर्णांक group)
अणु
	पूर्णांक bit;
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);

	अगर (hwc->config_base & VENUM_EVENT)
		bit = KRAIT_VPMRESR0_GROUP0;
	अन्यथा
		bit = krait_get_pmresrn_event(region);
	bit -= krait_get_pmresrn_event(0);
	bit += group;
	/*
	 * Lower bits are reserved क्रम use by the counters (see
	 * armv7pmu_get_event_idx() क्रम more info)
	 */
	bit += ARMV7_IDX_COUNTER_LAST(cpu_pmu) + 1;

	वापस bit;
पूर्ण

/*
 * We check क्रम column exclusion स्थिरraपूर्णांकs here.
 * Two events cant use the same group within a pmresr रेजिस्टर.
 */
अटल पूर्णांक krait_pmu_get_event_idx(काष्ठा pmu_hw_events *cpuc,
				   काष्ठा perf_event *event)
अणु
	पूर्णांक idx;
	पूर्णांक bit = -1;
	काष्ठा hw_perf_event *hwc = &event->hw;
	अचिन्हित पूर्णांक region = EVENT_REGION(hwc->config_base);
	अचिन्हित पूर्णांक code = EVENT_CODE(hwc->config_base);
	अचिन्हित पूर्णांक group = EVENT_GROUP(hwc->config_base);
	bool vक्रमागत_event = EVENT_VENUM(hwc->config_base);
	bool krait_event = EVENT_CPU(hwc->config_base);

	अगर (vक्रमागत_event || krait_event) अणु
		/* Ignore invalid events */
		अगर (group > 3 || region > 2)
			वापस -EINVAL;
		अगर (vक्रमागत_event && (code & 0xe0))
			वापस -EINVAL;

		bit = krait_event_to_bit(event, region, group);
		अगर (test_and_set_bit(bit, cpuc->used_mask))
			वापस -EAGAIN;
	पूर्ण

	idx = armv7pmu_get_event_idx(cpuc, event);
	अगर (idx < 0 && bit >= 0)
		clear_bit(bit, cpuc->used_mask);

	वापस idx;
पूर्ण

अटल व्योम krait_pmu_clear_event_idx(काष्ठा pmu_hw_events *cpuc,
				      काष्ठा perf_event *event)
अणु
	पूर्णांक bit;
	काष्ठा hw_perf_event *hwc = &event->hw;
	अचिन्हित पूर्णांक region = EVENT_REGION(hwc->config_base);
	अचिन्हित पूर्णांक group = EVENT_GROUP(hwc->config_base);
	bool vक्रमागत_event = EVENT_VENUM(hwc->config_base);
	bool krait_event = EVENT_CPU(hwc->config_base);

	armv7pmu_clear_event_idx(cpuc, event);
	अगर (vक्रमागत_event || krait_event) अणु
		bit = krait_event_to_bit(event, region, group);
		clear_bit(bit, cpuc->used_mask);
	पूर्ण
पूर्ण

अटल पूर्णांक krait_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	armv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "armv7_krait";
	/* Some early versions of Krait करोn't support PC ग_लिखो events */
	अगर (of_property_पढ़ो_bool(cpu_pmu->plat_device->dev.of_node,
				  "qcom,no-pc-write"))
		cpu_pmu->map_event = krait_map_event_no_branch;
	अन्यथा
		cpu_pmu->map_event = krait_map_event;
	cpu_pmu->set_event_filter = armv7pmu_set_event_filter;
	cpu_pmu->reset		= krait_pmu_reset;
	cpu_pmu->enable		= krait_pmu_enable_event;
	cpu_pmu->disable	= krait_pmu_disable_event;
	cpu_pmu->get_event_idx	= krait_pmu_get_event_idx;
	cpu_pmu->clear_event_idx = krait_pmu_clear_event_idx;
	वापस armv7_probe_num_events(cpu_pmu);
पूर्ण

/*
 * Scorpion Local Perक्रमmance Monitor Register (LPMn)
 *
 *            31   30     24     16     8      0
 *            +--------------------------------+
 *  LPM0      | EN |  CC  |  CC  |  CC  |  CC  |   N = 1, R = 0
 *            +--------------------------------+
 *  LPM1      | EN |  CC  |  CC  |  CC  |  CC  |   N = 1, R = 1
 *            +--------------------------------+
 *  LPM2      | EN |  CC  |  CC  |  CC  |  CC  |   N = 1, R = 2
 *            +--------------------------------+
 *  L2LPM     | EN |  CC  |  CC  |  CC  |  CC  |   N = 1, R = 3
 *            +--------------------------------+
 *  VLPM      | EN |  CC  |  CC  |  CC  |  CC  |   N = 2, R = ?
 *            +--------------------------------+
 *              EN | G=3  | G=2  | G=1  | G=0
 *
 *
 *  Event Encoding:
 *
 *      hwc->config_base = 0xNRCCG
 *
 *      N  = prefix, 1 क्रम Scorpion CPU (LPMn/L2LPM), 2 क्रम Vक्रमागत VFP (VLPM)
 *      R  = region रेजिस्टर
 *      CC = class of events the group G is choosing from
 *      G  = group or particular event
 *
 *  Example: 0x12021 is a Scorpion CPU event in LPM2's group 1 with code 2
 *
 *  A region (R) corresponds to a piece of the CPU (execution unit, inकाष्ठाion
 *  unit, etc.) जबतक the event code (CC) corresponds to a particular class of
 *  events (पूर्णांकerrupts क्रम example). An event code is broken करोwn पूर्णांकo
 *  groups (G) that can be mapped पूर्णांकo the PMU (irq, fiqs, and irq+fiqs क्रम
 *  example).
 */

अटल u32 scorpion_पढ़ो_pmresrn(पूर्णांक n)
अणु
	u32 val;

	चयन (n) अणु
	हाल 0:
		यंत्र अस्थिर("mrc p15, 0, %0, c15, c0, 0" : "=r" (val));
		अवरोध;
	हाल 1:
		यंत्र अस्थिर("mrc p15, 1, %0, c15, c0, 0" : "=r" (val));
		अवरोध;
	हाल 2:
		यंत्र अस्थिर("mrc p15, 2, %0, c15, c0, 0" : "=r" (val));
		अवरोध;
	हाल 3:
		यंत्र अस्थिर("mrc p15, 3, %0, c15, c2, 0" : "=r" (val));
		अवरोध;
	शेष:
		BUG(); /* Should be validated in scorpion_pmu_get_event_idx() */
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम scorpion_ग_लिखो_pmresrn(पूर्णांक n, u32 val)
अणु
	चयन (n) अणु
	हाल 0:
		यंत्र अस्थिर("mcr p15, 0, %0, c15, c0, 0" : : "r" (val));
		अवरोध;
	हाल 1:
		यंत्र अस्थिर("mcr p15, 1, %0, c15, c0, 0" : : "r" (val));
		अवरोध;
	हाल 2:
		यंत्र अस्थिर("mcr p15, 2, %0, c15, c0, 0" : : "r" (val));
		अवरोध;
	हाल 3:
		यंत्र अस्थिर("mcr p15, 3, %0, c15, c2, 0" : : "r" (val));
		अवरोध;
	शेष:
		BUG(); /* Should be validated in scorpion_pmu_get_event_idx() */
	पूर्ण
पूर्ण

अटल u32 scorpion_get_pmresrn_event(अचिन्हित पूर्णांक region)
अणु
	अटल स्थिर u32 pmresrn_table[] = अणु SCORPION_LPM0_GROUP0,
					     SCORPION_LPM1_GROUP0,
					     SCORPION_LPM2_GROUP0,
					     SCORPION_L2LPM_GROUP0 पूर्ण;
	वापस pmresrn_table[region];
पूर्ण

अटल व्योम scorpion_evt_setup(पूर्णांक idx, u32 config_base)
अणु
	u32 val;
	u32 mask;
	u32 vval, fval;
	अचिन्हित पूर्णांक region = EVENT_REGION(config_base);
	अचिन्हित पूर्णांक group = EVENT_GROUP(config_base);
	अचिन्हित पूर्णांक code = EVENT_CODE(config_base);
	अचिन्हित पूर्णांक group_shअगरt;
	bool vक्रमागत_event = EVENT_VENUM(config_base);

	group_shअगरt = group * 8;
	mask = 0xff << group_shअगरt;

	/* Configure evtsel क्रम the region and group */
	अगर (vक्रमागत_event)
		val = SCORPION_VLPM_GROUP0;
	अन्यथा
		val = scorpion_get_pmresrn_event(region);
	val += group;
	/* Mix in mode-exclusion bits */
	val |= config_base & (ARMV7_EXCLUDE_USER | ARMV7_EXCLUDE_PL1);
	armv7_pmnc_ग_लिखो_evtsel(idx, val);

	यंत्र अस्थिर("mcr p15, 0, %0, c9, c15, 0" : : "r" (0));

	अगर (vक्रमागत_event) अणु
		vक्रमागत_pre_pmresr(&vval, &fval);
		val = vक्रमागत_पढ़ो_pmresr();
		val &= ~mask;
		val |= code << group_shअगरt;
		val |= PMRESRn_EN;
		vक्रमागत_ग_लिखो_pmresr(val);
		vक्रमागत_post_pmresr(vval, fval);
	पूर्ण अन्यथा अणु
		val = scorpion_पढ़ो_pmresrn(region);
		val &= ~mask;
		val |= code << group_shअगरt;
		val |= PMRESRn_EN;
		scorpion_ग_लिखो_pmresrn(region, val);
	पूर्ण
पूर्ण

अटल व्योम scorpion_clearpmu(u32 config_base)
अणु
	u32 val;
	u32 vval, fval;
	अचिन्हित पूर्णांक region = EVENT_REGION(config_base);
	अचिन्हित पूर्णांक group = EVENT_GROUP(config_base);
	bool vक्रमागत_event = EVENT_VENUM(config_base);

	अगर (vक्रमागत_event) अणु
		vक्रमागत_pre_pmresr(&vval, &fval);
		val = vक्रमागत_पढ़ो_pmresr();
		val = clear_pmresrn_group(val, group);
		vक्रमागत_ग_लिखो_pmresr(val);
		vक्रमागत_post_pmresr(vval, fval);
	पूर्ण अन्यथा अणु
		val = scorpion_पढ़ो_pmresrn(region);
		val = clear_pmresrn_group(val, group);
		scorpion_ग_लिखो_pmresrn(region, val);
	पूर्ण
पूर्ण

अटल व्योम scorpion_pmu_disable_event(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);

	/* Disable counter and पूर्णांकerrupt */
	raw_spin_lock_irqsave(&events->pmu_lock, flags);

	/* Disable counter */
	armv7_pmnc_disable_counter(idx);

	/*
	 * Clear pmresr code (अगर destined क्रम PMNx counters)
	 */
	अगर (hwc->config_base & KRAIT_EVENT_MASK)
		scorpion_clearpmu(hwc->config_base);

	/* Disable पूर्णांकerrupt क्रम this counter */
	armv7_pmnc_disable_पूर्णांकens(idx);

	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल व्योम scorpion_pmu_enable_event(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	काष्ठा pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);

	/*
	 * Enable counter and पूर्णांकerrupt, and set the counter to count
	 * the event that we're पूर्णांकerested in.
	 */
	raw_spin_lock_irqsave(&events->pmu_lock, flags);

	/* Disable counter */
	armv7_pmnc_disable_counter(idx);

	/*
	 * Set event (अगर destined क्रम PMNx counters)
	 * We करोn't set the event क्रम the cycle counter because we
	 * करोn't have the ability to perक्रमm event filtering.
	 */
	अगर (hwc->config_base & KRAIT_EVENT_MASK)
		scorpion_evt_setup(idx, hwc->config_base);
	अन्यथा अगर (idx != ARMV7_IDX_CYCLE_COUNTER)
		armv7_pmnc_ग_लिखो_evtsel(idx, hwc->config_base);

	/* Enable पूर्णांकerrupt क्रम this counter */
	armv7_pmnc_enable_पूर्णांकens(idx);

	/* Enable counter */
	armv7_pmnc_enable_counter(idx);

	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल व्योम scorpion_pmu_reset(व्योम *info)
अणु
	u32 vval, fval;
	काष्ठा arm_pmu *cpu_pmu = info;
	u32 idx, nb_cnt = cpu_pmu->num_events;

	armv7pmu_reset(info);

	/* Clear all pmresrs */
	scorpion_ग_लिखो_pmresrn(0, 0);
	scorpion_ग_लिखो_pmresrn(1, 0);
	scorpion_ग_लिखो_pmresrn(2, 0);
	scorpion_ग_लिखो_pmresrn(3, 0);

	vक्रमागत_pre_pmresr(&vval, &fval);
	vक्रमागत_ग_लिखो_pmresr(0);
	vक्रमागत_post_pmresr(vval, fval);

	/* Reset PMxEVNCTCR to sane शेष */
	क्रम (idx = ARMV7_IDX_CYCLE_COUNTER; idx < nb_cnt; ++idx) अणु
		armv7_pmnc_select_counter(idx);
		यंत्र अस्थिर("mcr p15, 0, %0, c9, c15, 0" : : "r" (0));
	पूर्ण
पूर्ण

अटल पूर्णांक scorpion_event_to_bit(काष्ठा perf_event *event, अचिन्हित पूर्णांक region,
			      अचिन्हित पूर्णांक group)
अणु
	पूर्णांक bit;
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);

	अगर (hwc->config_base & VENUM_EVENT)
		bit = SCORPION_VLPM_GROUP0;
	अन्यथा
		bit = scorpion_get_pmresrn_event(region);
	bit -= scorpion_get_pmresrn_event(0);
	bit += group;
	/*
	 * Lower bits are reserved क्रम use by the counters (see
	 * armv7pmu_get_event_idx() क्रम more info)
	 */
	bit += ARMV7_IDX_COUNTER_LAST(cpu_pmu) + 1;

	वापस bit;
पूर्ण

/*
 * We check क्रम column exclusion स्थिरraपूर्णांकs here.
 * Two events cant use the same group within a pmresr रेजिस्टर.
 */
अटल पूर्णांक scorpion_pmu_get_event_idx(काष्ठा pmu_hw_events *cpuc,
				   काष्ठा perf_event *event)
अणु
	पूर्णांक idx;
	पूर्णांक bit = -1;
	काष्ठा hw_perf_event *hwc = &event->hw;
	अचिन्हित पूर्णांक region = EVENT_REGION(hwc->config_base);
	अचिन्हित पूर्णांक group = EVENT_GROUP(hwc->config_base);
	bool vक्रमागत_event = EVENT_VENUM(hwc->config_base);
	bool scorpion_event = EVENT_CPU(hwc->config_base);

	अगर (vक्रमागत_event || scorpion_event) अणु
		/* Ignore invalid events */
		अगर (group > 3 || region > 3)
			वापस -EINVAL;

		bit = scorpion_event_to_bit(event, region, group);
		अगर (test_and_set_bit(bit, cpuc->used_mask))
			वापस -EAGAIN;
	पूर्ण

	idx = armv7pmu_get_event_idx(cpuc, event);
	अगर (idx < 0 && bit >= 0)
		clear_bit(bit, cpuc->used_mask);

	वापस idx;
पूर्ण

अटल व्योम scorpion_pmu_clear_event_idx(काष्ठा pmu_hw_events *cpuc,
				      काष्ठा perf_event *event)
अणु
	पूर्णांक bit;
	काष्ठा hw_perf_event *hwc = &event->hw;
	अचिन्हित पूर्णांक region = EVENT_REGION(hwc->config_base);
	अचिन्हित पूर्णांक group = EVENT_GROUP(hwc->config_base);
	bool vक्रमागत_event = EVENT_VENUM(hwc->config_base);
	bool scorpion_event = EVENT_CPU(hwc->config_base);

	armv7pmu_clear_event_idx(cpuc, event);
	अगर (vक्रमागत_event || scorpion_event) अणु
		bit = scorpion_event_to_bit(event, region, group);
		clear_bit(bit, cpuc->used_mask);
	पूर्ण
पूर्ण

अटल पूर्णांक scorpion_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	armv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "armv7_scorpion";
	cpu_pmu->map_event	= scorpion_map_event;
	cpu_pmu->reset		= scorpion_pmu_reset;
	cpu_pmu->enable		= scorpion_pmu_enable_event;
	cpu_pmu->disable	= scorpion_pmu_disable_event;
	cpu_pmu->get_event_idx	= scorpion_pmu_get_event_idx;
	cpu_pmu->clear_event_idx = scorpion_pmu_clear_event_idx;
	वापस armv7_probe_num_events(cpu_pmu);
पूर्ण

अटल पूर्णांक scorpion_mp_pmu_init(काष्ठा arm_pmu *cpu_pmu)
अणु
	armv7pmu_init(cpu_pmu);
	cpu_pmu->name		= "armv7_scorpion_mp";
	cpu_pmu->map_event	= scorpion_map_event;
	cpu_pmu->reset		= scorpion_pmu_reset;
	cpu_pmu->enable		= scorpion_pmu_enable_event;
	cpu_pmu->disable	= scorpion_pmu_disable_event;
	cpu_pmu->get_event_idx	= scorpion_pmu_get_event_idx;
	cpu_pmu->clear_event_idx = scorpion_pmu_clear_event_idx;
	वापस armv7_probe_num_events(cpu_pmu);
पूर्ण

अटल स्थिर काष्ठा of_device_id armv7_pmu_of_device_ids[] = अणु
	अणु.compatible = "arm,cortex-a17-pmu",	.data = armv7_a17_pmu_initपूर्ण,
	अणु.compatible = "arm,cortex-a15-pmu",	.data = armv7_a15_pmu_initपूर्ण,
	अणु.compatible = "arm,cortex-a12-pmu",	.data = armv7_a12_pmu_initपूर्ण,
	अणु.compatible = "arm,cortex-a9-pmu",	.data = armv7_a9_pmu_initपूर्ण,
	अणु.compatible = "arm,cortex-a8-pmu",	.data = armv7_a8_pmu_initपूर्ण,
	अणु.compatible = "arm,cortex-a7-pmu",	.data = armv7_a7_pmu_initपूर्ण,
	अणु.compatible = "arm,cortex-a5-pmu",	.data = armv7_a5_pmu_initपूर्ण,
	अणु.compatible = "qcom,krait-pmu",	.data = krait_pmu_initपूर्ण,
	अणु.compatible = "qcom,scorpion-pmu",	.data = scorpion_pmu_initपूर्ण,
	अणु.compatible = "qcom,scorpion-mp-pmu",	.data = scorpion_mp_pmu_initपूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmu_probe_info armv7_pmu_probe_table[] = अणु
	ARM_PMU_PROBE(ARM_CPU_PART_CORTEX_A8, armv7_a8_pmu_init),
	ARM_PMU_PROBE(ARM_CPU_PART_CORTEX_A9, armv7_a9_pmu_init),
	अणु /* sentinel value */ पूर्ण
पूर्ण;


अटल पूर्णांक armv7_pmu_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस arm_pmu_device_probe(pdev, armv7_pmu_of_device_ids,
				    armv7_pmu_probe_table);
पूर्ण

अटल काष्ठा platक्रमm_driver armv7_pmu_driver = अणु
	.driver		= अणु
		.name	= "armv7-pmu",
		.of_match_table = armv7_pmu_of_device_ids,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= armv7_pmu_device_probe,
पूर्ण;

builtin_platक्रमm_driver(armv7_pmu_driver);
#पूर्ण_अगर	/* CONFIG_CPU_V7 */
