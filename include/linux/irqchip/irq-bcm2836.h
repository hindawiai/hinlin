<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Root पूर्णांकerrupt controller क्रम the BCM2836 (Raspberry Pi 2).
 *
 * Copyright 2015 Broadcom
 */

#घोषणा LOCAL_CONTROL			0x000
#घोषणा LOCAL_PRESCALER			0x008

/*
 * The low 2 bits identअगरy the CPU that the GPU IRQ goes to, and the
 * next 2 bits identअगरy the CPU that the GPU FIQ goes to.
 */
#घोषणा LOCAL_GPU_ROUTING		0x00c
/* When setting bits 0-3, enables PMU पूर्णांकerrupts on that CPU. */
#घोषणा LOCAL_PM_ROUTING_SET		0x010
/* When setting bits 0-3, disables PMU पूर्णांकerrupts on that CPU. */
#घोषणा LOCAL_PM_ROUTING_CLR		0x014
/*
 * The low 4 bits of this are the CPU's समयr IRQ enables, and the
 * next 4 bits are the CPU's समयr FIQ enables (which override the IRQ
 * bits).
 */
#घोषणा LOCAL_TIMER_INT_CONTROL0	0x040
/*
 * The low 4 bits of this are the CPU's per-mailbox IRQ enables, and
 * the next 4 bits are the CPU's per-mailbox FIQ enables (which
 * override the IRQ bits).
 */
#घोषणा LOCAL_MAILBOX_INT_CONTROL0	0x050
/*
 * The CPU's पूर्णांकerrupt status रेजिस्टर.  Bits are defined by the
 * LOCAL_IRQ_* bits below.
 */
#घोषणा LOCAL_IRQ_PENDING0		0x060
/* Same status bits as above, but क्रम FIQ. */
#घोषणा LOCAL_FIQ_PENDING0		0x070
/*
 * Mailbox ग_लिखो-to-set bits.  There are 16 mailboxes, 4 per CPU, and
 * these bits are organized by mailbox number and then CPU number.  We
 * use mailbox 0 क्रम IPIs.  The mailbox's पूर्णांकerrupt is उठाओd जबतक
 * any bit is set.
 */
#घोषणा LOCAL_MAILBOX0_SET0		0x080
#घोषणा LOCAL_MAILBOX3_SET0		0x08c
/* Mailbox ग_लिखो-to-clear bits. */
#घोषणा LOCAL_MAILBOX0_CLR0		0x0c0
#घोषणा LOCAL_MAILBOX3_CLR0		0x0cc

#घोषणा LOCAL_IRQ_CNTPSIRQ	0
#घोषणा LOCAL_IRQ_CNTPNSIRQ	1
#घोषणा LOCAL_IRQ_CNTHPIRQ	2
#घोषणा LOCAL_IRQ_CNTVIRQ	3
#घोषणा LOCAL_IRQ_MAILBOX0	4
#घोषणा LOCAL_IRQ_MAILBOX1	5
#घोषणा LOCAL_IRQ_MAILBOX2	6
#घोषणा LOCAL_IRQ_MAILBOX3	7
#घोषणा LOCAL_IRQ_GPU_FAST	8
#घोषणा LOCAL_IRQ_PMU_FAST	9
#घोषणा LAST_IRQ		LOCAL_IRQ_PMU_FAST
