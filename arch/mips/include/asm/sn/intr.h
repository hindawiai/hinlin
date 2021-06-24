<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1992 - 1997 Silicon Graphics, Inc.
 */
#अगर_अघोषित __ASM_SN_INTR_H
#घोषणा __ASM_SN_INTR_H

/*
 * Macros to manipulate the पूर्णांकerrupt रेजिस्टर on the calling hub chip.
 */

#घोषणा LOCAL_HUB_SEND_INTR(level)				\
	LOCAL_HUB_S(PI_INT_PEND_MOD, (0x100 | (level)))
#घोषणा REMOTE_HUB_SEND_INTR(hub, level)			\
	REMOTE_HUB_S((hub), PI_INT_PEND_MOD, (0x100 | (level)))

/*
 * When clearing the पूर्णांकerrupt, make sure this clear करोes make it
 * to the hub. Otherwise we could end up losing पूर्णांकerrupts.
 * We करो an uncached load of the पूर्णांक_pend0 रेजिस्टर to ensure this.
 */

#घोषणा LOCAL_HUB_CLR_INTR(level)				\
करो अणु								\
	LOCAL_HUB_S(PI_INT_PEND_MOD, (level));			\
	LOCAL_HUB_L(PI_INT_PEND0);				\
पूर्ण जबतक (0);

#घोषणा REMOTE_HUB_CLR_INTR(hub, level)				\
करो अणु								\
	nasid_t	 __hub = (hub);					\
								\
	REMOTE_HUB_S(__hub, PI_INT_PEND_MOD, (level));		\
	REMOTE_HUB_L(__hub, PI_INT_PEND0);			\
पूर्ण जबतक (0);

/*
 * Hard-coded पूर्णांकerrupt levels:
 */

/*
 *	L0 = SW1
 *	L1 = SW2
 *	L2 = INT_PEND0
 *	L3 = INT_PEND1
 *	L4 = RTC
 *	L5 = Profiling Timer
 *	L6 = Hub Errors
 *	L7 = Count/Compare (T5 counters)
 */


/*
 * INT_PEND0 hard-coded bits.
 */

/*
 * INT_PEND0 bits determined by hardware:
 */
#घोषणा RESERVED_INTR		 0	/* What is this bit? */
#घोषणा GFX_INTR_A		 1
#घोषणा GFX_INTR_B		 2
#घोषणा PG_MIG_INTR		 3
#घोषणा UART_INTR		 4
#घोषणा CC_PEND_A		 5
#घोषणा CC_PEND_B		 6

/*
 * INT_PEND0 used by the kernel क्रम itself ...
 */
#घोषणा CPU_RESCHED_A_IRQ	 7
#घोषणा CPU_RESCHED_B_IRQ	 8
#घोषणा CPU_CALL_A_IRQ		 9
#घोषणा CPU_CALL_B_IRQ		10

/*
 * INT_PEND1 hard-coded bits:
 */
#घोषणा NI_BRDCAST_ERR_A	39
#घोषणा NI_BRDCAST_ERR_B	40

#घोषणा LLP_PFAIL_INTR_A	41	/* see ml/SN/SN0/sysctlr.c */
#घोषणा LLP_PFAIL_INTR_B	42

#घोषणा TLB_INTR_A		43	/* used क्रम tlb flush अक्रमom */
#घोषणा TLB_INTR_B		44

#घोषणा IP27_INTR_0		45	/* Reserved क्रम PROM use */
#घोषणा IP27_INTR_1		46	/* करो not use in Kernel */
#घोषणा IP27_INTR_2		47
#घोषणा IP27_INTR_3		48
#घोषणा IP27_INTR_4		49
#घोषणा IP27_INTR_5		50
#घोषणा IP27_INTR_6		51
#घोषणा IP27_INTR_7		52

#घोषणा BRIDGE_ERROR_INTR	53	/* Setup by PROM to catch	*/
					/* Bridge Errors */
#घोषणा DEBUG_INTR_A		54
#घोषणा DEBUG_INTR_B		55	/* Used by symmon to stop all cpus */
#घोषणा IO_ERROR_INTR		57	/* Setup by PROM */
#घोषणा CLK_ERR_INTR		58
#घोषणा COR_ERR_INTR_A		59
#घोषणा COR_ERR_INTR_B		60
#घोषणा MD_COR_ERR_INTR		61
#घोषणा NI_ERROR_INTR		62
#घोषणा MSC_PANIC_INTR		63

#पूर्ण_अगर /* __ASM_SN_INTR_H */
