<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 SiFive
 * Copyright (C) 2018 Andes Technology Corporation
 *
 */

#अगर_अघोषित _ASM_RISCV_PERF_EVENT_H
#घोषणा _ASM_RISCV_PERF_EVENT_H

#समावेश <linux/perf_event.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/पूर्णांकerrupt.h>

#अगर_घोषित CONFIG_RISCV_BASE_PMU
#घोषणा RISCV_BASE_COUNTERS	2

/*
 * The RISCV_MAX_COUNTERS parameter should be specअगरied.
 */

#घोषणा RISCV_MAX_COUNTERS	2

/*
 * These are the indexes of bits in counteren रेजिस्टर *minus* 1,
 * except क्रम cycle.  It would be coherent अगर it can directly mapped
 * to counteren bit definition, but there is a *समय* रेजिस्टर at
 * counteren[1].  Per-cpu काष्ठाure is scarce resource here.
 *
 * According to the spec, an implementation can support counter up to
 * mhpmcounter31, but many high-end processors has at most 6 general
 * PMCs, we give the definition to MHPMCOUNTER8 here.
 */
#घोषणा RISCV_PMU_CYCLE		0
#घोषणा RISCV_PMU_INSTRET	1
#घोषणा RISCV_PMU_MHPMCOUNTER3	2
#घोषणा RISCV_PMU_MHPMCOUNTER4	3
#घोषणा RISCV_PMU_MHPMCOUNTER5	4
#घोषणा RISCV_PMU_MHPMCOUNTER6	5
#घोषणा RISCV_PMU_MHPMCOUNTER7	6
#घोषणा RISCV_PMU_MHPMCOUNTER8	7

#घोषणा RISCV_OP_UNSUPP		(-EOPNOTSUPP)

काष्ठा cpu_hw_events अणु
	/* # currently enabled events*/
	पूर्णांक			n_events;
	/* currently enabled events */
	काष्ठा perf_event	*events[RISCV_MAX_COUNTERS];
	/* venकरोr-defined PMU data */
	व्योम			*platक्रमm;
पूर्ण;

काष्ठा riscv_pmu अणु
	काष्ठा pmu	*pmu;

	/* generic hw/cache events table */
	स्थिर पूर्णांक	*hw_events;
	स्थिर पूर्णांक	(*cache_events)[PERF_COUNT_HW_CACHE_MAX]
				       [PERF_COUNT_HW_CACHE_OP_MAX]
				       [PERF_COUNT_HW_CACHE_RESULT_MAX];
	/* method used to map hw/cache events */
	पूर्णांक		(*map_hw_event)(u64 config);
	पूर्णांक		(*map_cache_event)(u64 config);

	/* max generic hw events in map */
	पूर्णांक		max_events;
	/* number total counters, 2(base) + x(general) */
	पूर्णांक		num_counters;
	/* the width of the counter */
	पूर्णांक		counter_width;

	/* venकरोr-defined PMU features */
	व्योम		*platक्रमm;

	irqवापस_t	(*handle_irq)(पूर्णांक irq_num, व्योम *dev);
	पूर्णांक		irq;
पूर्ण;

#पूर्ण_अगर
#अगर_घोषित CONFIG_PERF_EVENTS
#घोषणा perf_arch_bpf_user_pt_regs(regs) (काष्ठा user_regs_काष्ठा *)regs
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_RISCV_PERF_EVENT_H */
