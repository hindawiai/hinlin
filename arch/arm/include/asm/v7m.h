<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common defines क्रम v7m cpus
 */
#घोषणा V7M_SCS_ICTR			IOMEM(0xe000e004)
#घोषणा V7M_SCS_ICTR_INTLINESNUM_MASK		0x0000000f

#घोषणा BASEADDR_V7M_SCB		IOMEM(0xe000ed00)

#घोषणा V7M_SCB_CPUID			0x00

#घोषणा V7M_SCB_ICSR			0x04
#घोषणा V7M_SCB_ICSR_PENDSVSET			(1 << 28)
#घोषणा V7M_SCB_ICSR_PENDSVCLR			(1 << 27)
#घोषणा V7M_SCB_ICSR_RETTOBASE			(1 << 11)

#घोषणा V7M_SCB_VTOR			0x08

#घोषणा V7M_SCB_AIRCR			0x0c
#घोषणा V7M_SCB_AIRCR_VECTKEY			(0x05fa << 16)
#घोषणा V7M_SCB_AIRCR_SYSRESETREQ		(1 << 2)

#घोषणा V7M_SCB_SCR			0x10
#घोषणा V7M_SCB_SCR_SLEEPDEEP			(1 << 2)

#घोषणा V7M_SCB_CCR			0x14
#घोषणा V7M_SCB_CCR_STKALIGN			(1 << 9)
#घोषणा V7M_SCB_CCR_DC				(1 << 16)
#घोषणा V7M_SCB_CCR_IC				(1 << 17)
#घोषणा V7M_SCB_CCR_BP				(1 << 18)

#घोषणा V7M_SCB_SHPR2			0x1c
#घोषणा V7M_SCB_SHPR3			0x20

#घोषणा V7M_SCB_SHCSR			0x24
#घोषणा V7M_SCB_SHCSR_USGFAULTENA		(1 << 18)
#घोषणा V7M_SCB_SHCSR_BUSFAULTENA		(1 << 17)
#घोषणा V7M_SCB_SHCSR_MEMFAULTENA		(1 << 16)

#घोषणा V7M_xPSR_FRAMEPTRALIGN			0x00000200
#घोषणा V7M_xPSR_EXCEPTIONNO			0x000001ff

/*
 * When branching to an address that has bits [31:28] == 0xf an exception वापस
 * occurs. Bits [27:5] are reserved (SBOP). If the processor implements the FP
 * extension Bit [4] defines अगर the exception frame has space allocated क्रम FP
 * state inक्रमmation, SBOP otherwise. Bit [3] defines the mode that is वापसed
 * to (0 -> handler mode; 1 -> thपढ़ो mode). Bit [2] defines which sp is used
 * (0 -> msp; 1 -> psp). Bits [1:0] are fixed to 0b01.
 */
#घोषणा EXC_RET_STACK_MASK			0x00000004
#घोषणा EXC_RET_THREADMODE_PROCESSSTACK		(3 << 2)

/* Cache related definitions */

#घोषणा	V7M_SCB_CLIDR		0x78	/* Cache Level ID रेजिस्टर */
#घोषणा	V7M_SCB_CTR		0x7c	/* Cache Type रेजिस्टर */
#घोषणा	V7M_SCB_CCSIDR		0x80	/* Cache size ID रेजिस्टर */
#घोषणा	V7M_SCB_CSSELR		0x84	/* Cache size selection रेजिस्टर */

/* Memory-mapped MPU रेजिस्टरs क्रम M-class */
#घोषणा MPU_TYPE		0x90
#घोषणा MPU_CTRL		0x94
#घोषणा MPU_CTRL_ENABLE		1
#घोषणा MPU_CTRL_PRIVDEFENA	(1 << 2)

#घोषणा PMSAv7_RNR		0x98
#घोषणा PMSAv7_RBAR		0x9c
#घोषणा PMSAv7_RASR		0xa0

#घोषणा PMSAv8_RNR		0x98
#घोषणा PMSAv8_RBAR		0x9c
#घोषणा PMSAv8_RLAR		0xa0
#घोषणा PMSAv8_RBAR_A(n)	(PMSAv8_RBAR + 8*(n))
#घोषणा PMSAv8_RLAR_A(n)	(PMSAv8_RLAR + 8*(n))
#घोषणा PMSAv8_MAIR0		0xc0
#घोषणा PMSAv8_MAIR1		0xc4

/* Cache opeartions */
#घोषणा	V7M_SCB_ICIALLU		0x250	/* I-cache invalidate all to PoU */
#घोषणा	V7M_SCB_ICIMVAU		0x258	/* I-cache invalidate by MVA to PoU */
#घोषणा	V7M_SCB_DCIMVAC		0x25c	/* D-cache invalidate by MVA to PoC */
#घोषणा	V7M_SCB_DCISW		0x260	/* D-cache invalidate by set-way */
#घोषणा	V7M_SCB_DCCMVAU		0x264	/* D-cache clean by MVA to PoU */
#घोषणा	V7M_SCB_DCCMVAC		0x268	/* D-cache clean by MVA to PoC */
#घोषणा	V7M_SCB_DCCSW		0x26c	/* D-cache clean by set-way */
#घोषणा	V7M_SCB_DCCIMVAC	0x270	/* D-cache clean and invalidate by MVA to PoC */
#घोषणा	V7M_SCB_DCCISW		0x274	/* D-cache clean and invalidate by set-way */
#घोषणा	V7M_SCB_BPIALL		0x278	/* D-cache clean and invalidate by set-way */

#अगर_अघोषित __ASSEMBLY__

क्रमागत reboot_mode;

व्योम armv7m_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd);

#पूर्ण_अगर /* __ASSEMBLY__ */
