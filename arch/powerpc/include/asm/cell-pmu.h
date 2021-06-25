<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Cell Broadband Engine Perक्रमmance Monitor
 *
 * (C) Copyright IBM Corporation 2006
 *
 * Author:
 *   David Erb (djerb@us.ibm.com)
 *   Kevin Corry (kevcorry@us.ibm.com)
 */

#अगर_अघोषित __ASM_CELL_PMU_H__
#घोषणा __ASM_CELL_PMU_H__

/* The Cell PMU has four hardware perक्रमmance counters, which can be
 * configured as four 32-bit counters or eight 16-bit counters.
 */
#घोषणा NR_PHYS_CTRS 4
#घोषणा NR_CTRS      (NR_PHYS_CTRS * 2)

/* Macros क्रम the pm_control रेजिस्टर. */
#घोषणा CBE_PM_16BIT_CTR(ctr)              (1 << (24 - ((ctr) & (NR_PHYS_CTRS - 1))))
#घोषणा CBE_PM_ENABLE_PERF_MON             0x80000000
#घोषणा CBE_PM_STOP_AT_MAX                 0x40000000
#घोषणा CBE_PM_TRACE_MODE_GET(pm_control)  (((pm_control) >> 28) & 0x3)
#घोषणा CBE_PM_TRACE_MODE_SET(mode)        (((mode)  & 0x3) << 28)
#घोषणा CBE_PM_TRACE_BUF_OVFLW(bit)        (((bit) & 0x1) << 17)
#घोषणा CBE_PM_COUNT_MODE_SET(count)       (((count) & 0x3) << 18)
#घोषणा CBE_PM_FREEZE_ALL_CTRS             0x00100000
#घोषणा CBE_PM_ENABLE_EXT_TRACE            0x00008000
#घोषणा CBE_PM_SPU_ADDR_TRACE_SET(msk)     (((msk) & 0x3) << 9)

/* Macros क्रम the trace_address रेजिस्टर. */
#घोषणा CBE_PM_TRACE_BUF_FULL              0x00000800
#घोषणा CBE_PM_TRACE_BUF_EMPTY             0x00000400
#घोषणा CBE_PM_TRACE_BUF_DATA_COUNT(ta)    ((ta) & 0x3ff)
#घोषणा CBE_PM_TRACE_BUF_MAX_COUNT         0x400

/* Macros क्रम the pm07_control रेजिस्टरs. */
#घोषणा CBE_PM_CTR_INPUT_MUX(pm07_control) (((pm07_control) >> 26) & 0x3f)
#घोषणा CBE_PM_CTR_INPUT_CONTROL           0x02000000
#घोषणा CBE_PM_CTR_POLARITY                0x01000000
#घोषणा CBE_PM_CTR_COUNT_CYCLES            0x00800000
#घोषणा CBE_PM_CTR_ENABLE                  0x00400000
#घोषणा PM07_CTR_INPUT_MUX(x)              (((x) & 0x3F) << 26)
#घोषणा PM07_CTR_INPUT_CONTROL(x)          (((x) & 1) << 25)
#घोषणा PM07_CTR_POLARITY(x)               (((x) & 1) << 24)
#घोषणा PM07_CTR_COUNT_CYCLES(x)           (((x) & 1) << 23)
#घोषणा PM07_CTR_ENABLE(x)                 (((x) & 1) << 22)

/* Macros क्रम the pm_status रेजिस्टर. */
#घोषणा CBE_PM_CTR_OVERFLOW_INTR(ctr)      (1 << (31 - ((ctr) & 7)))

क्रमागत pm_reg_name अणु
	group_control,
	debug_bus_control,
	trace_address,
	ext_tr_समयr,
	pm_status,
	pm_control,
	pm_पूर्णांकerval,
	pm_start_stop,
पूर्ण;

/* Routines क्रम पढ़ोing/writing the PMU रेजिस्टरs. */
बाह्य u32  cbe_पढ़ो_phys_ctr(u32 cpu, u32 phys_ctr);
बाह्य व्योम cbe_ग_लिखो_phys_ctr(u32 cpu, u32 phys_ctr, u32 val);
बाह्य u32  cbe_पढ़ो_ctr(u32 cpu, u32 ctr);
बाह्य व्योम cbe_ग_लिखो_ctr(u32 cpu, u32 ctr, u32 val);

बाह्य u32  cbe_पढ़ो_pm07_control(u32 cpu, u32 ctr);
बाह्य व्योम cbe_ग_लिखो_pm07_control(u32 cpu, u32 ctr, u32 val);
बाह्य u32  cbe_पढ़ो_pm(u32 cpu, क्रमागत pm_reg_name reg);
बाह्य व्योम cbe_ग_लिखो_pm(u32 cpu, क्रमागत pm_reg_name reg, u32 val);

बाह्य u32  cbe_get_ctr_size(u32 cpu, u32 phys_ctr);
बाह्य व्योम cbe_set_ctr_size(u32 cpu, u32 phys_ctr, u32 ctr_size);

बाह्य व्योम cbe_enable_pm(u32 cpu);
बाह्य व्योम cbe_disable_pm(u32 cpu);

बाह्य व्योम cbe_पढ़ो_trace_buffer(u32 cpu, u64 *buf);

बाह्य व्योम cbe_enable_pm_पूर्णांकerrupts(u32 cpu, u32 thपढ़ो, u32 mask);
बाह्य व्योम cbe_disable_pm_पूर्णांकerrupts(u32 cpu);
बाह्य u32  cbe_get_and_clear_pm_पूर्णांकerrupts(u32 cpu);
बाह्य व्योम cbe_sync_irq(पूर्णांक node);

#घोषणा CBE_COUNT_SUPERVISOR_MODE       0
#घोषणा CBE_COUNT_HYPERVISOR_MODE       1
#घोषणा CBE_COUNT_PROBLEM_MODE          2
#घोषणा CBE_COUNT_ALL_MODES             3

#पूर्ण_अगर /* __ASM_CELL_PMU_H__ */
