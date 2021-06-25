<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * (C) Copyright 2005 Tundra Semiconductor Corp.
 * Alex Bounine, <alexandreb at tundra.com).
 *
 * See file CREDITS क्रम list of people who contributed to this
 * project.
 */

/*
 * definitions क्रम पूर्णांकerrupt controller initialization and बाह्यal पूर्णांकerrupt
 * demultiplexing on TSI108EMU/SVB boards.
 */

#अगर_अघोषित _ASM_POWERPC_TSI108_IRQ_H
#घोषणा _ASM_POWERPC_TSI108_IRQ_H

/*
 * Tsi108 पूर्णांकerrupts
 */
#अगर_अघोषित TSI108_IRQ_REG_BASE
#घोषणा TSI108_IRQ_REG_BASE		0
#पूर्ण_अगर

#घोषणा TSI108_IRQ(x)		(TSI108_IRQ_REG_BASE + (x))

#घोषणा TSI108_MAX_VECTORS	(36 + 4)	/* 36 sources + PCI INT demux */
#घोषणा MAX_TASK_PRIO	0xF

#घोषणा TSI108_IRQ_SPURIOUS	(TSI108_MAX_VECTORS)

#घोषणा DEFAULT_PRIO_LVL	10	/* initial priority level */

/* Interrupt vectors assignment to बाह्यal and पूर्णांकernal
 * sources of requests. */

/* EXTERNAL INTERRUPT SOURCES */

#घोषणा IRQ_TSI108_EXT_INT0	TSI108_IRQ(0)	/* External Source at INT[0] */
#घोषणा IRQ_TSI108_EXT_INT1	TSI108_IRQ(1)	/* External Source at INT[1] */
#घोषणा IRQ_TSI108_EXT_INT2	TSI108_IRQ(2)	/* External Source at INT[2] */
#घोषणा IRQ_TSI108_EXT_INT3	TSI108_IRQ(3)	/* External Source at INT[3] */

/* INTERNAL INTERRUPT SOURCES */

#घोषणा IRQ_TSI108_RESERVED0	TSI108_IRQ(4)	/* Reserved IRQ */
#घोषणा IRQ_TSI108_RESERVED1	TSI108_IRQ(5)	/* Reserved IRQ */
#घोषणा IRQ_TSI108_RESERVED2	TSI108_IRQ(6)	/* Reserved IRQ */
#घोषणा IRQ_TSI108_RESERVED3	TSI108_IRQ(7)	/* Reserved IRQ */
#घोषणा IRQ_TSI108_DMA0		TSI108_IRQ(8)	/* DMA0 */
#घोषणा IRQ_TSI108_DMA1		TSI108_IRQ(9)	/* DMA1 */
#घोषणा IRQ_TSI108_DMA2		TSI108_IRQ(10)	/* DMA2 */
#घोषणा IRQ_TSI108_DMA3		TSI108_IRQ(11)	/* DMA3 */
#घोषणा IRQ_TSI108_UART0	TSI108_IRQ(12)	/* UART0 */
#घोषणा IRQ_TSI108_UART1	TSI108_IRQ(13)	/* UART1 */
#घोषणा IRQ_TSI108_I2C		TSI108_IRQ(14)	/* I2C */
#घोषणा IRQ_TSI108_GPIO		TSI108_IRQ(15)	/* GPIO */
#घोषणा IRQ_TSI108_GIGE0	TSI108_IRQ(16)	/* GIGE0 */
#घोषणा IRQ_TSI108_GIGE1	TSI108_IRQ(17)	/* GIGE1 */
#घोषणा IRQ_TSI108_RESERVED4	TSI108_IRQ(18)	/* Reserved IRQ */
#घोषणा IRQ_TSI108_HLP		TSI108_IRQ(19)	/* HLP */
#घोषणा IRQ_TSI108_SDRAM	TSI108_IRQ(20)	/* SDC */
#घोषणा IRQ_TSI108_PROC_IF	TSI108_IRQ(21)	/* Processor IF */
#घोषणा IRQ_TSI108_RESERVED5	TSI108_IRQ(22)	/* Reserved IRQ */
#घोषणा IRQ_TSI108_PCI		TSI108_IRQ(23)	/* PCI/X block */

#घोषणा IRQ_TSI108_MBOX0	TSI108_IRQ(24)	/* Mailbox 0 रेजिस्टर */
#घोषणा IRQ_TSI108_MBOX1	TSI108_IRQ(25)	/* Mailbox 1 रेजिस्टर */
#घोषणा IRQ_TSI108_MBOX2	TSI108_IRQ(26)	/* Mailbox 2 रेजिस्टर */
#घोषणा IRQ_TSI108_MBOX3	TSI108_IRQ(27)	/* Mailbox 3 रेजिस्टर */

#घोषणा IRQ_TSI108_DBELL0	TSI108_IRQ(28)	/* Doorbell 0 */
#घोषणा IRQ_TSI108_DBELL1	TSI108_IRQ(29)	/* Doorbell 1 */
#घोषणा IRQ_TSI108_DBELL2	TSI108_IRQ(30)	/* Doorbell 2 */
#घोषणा IRQ_TSI108_DBELL3	TSI108_IRQ(31)	/* Doorbell 3 */

#घोषणा IRQ_TSI108_TIMER0	TSI108_IRQ(32)	/* Global Timer 0 */
#घोषणा IRQ_TSI108_TIMER1	TSI108_IRQ(33)	/* Global Timer 1 */
#घोषणा IRQ_TSI108_TIMER2	TSI108_IRQ(34)	/* Global Timer 2 */
#घोषणा IRQ_TSI108_TIMER3	TSI108_IRQ(35)	/* Global Timer 3 */

/*
 * PCI bus INTA# - INTD# lines demultiplexor
 */
#घोषणा IRQ_PCI_INTAD_BASE	TSI108_IRQ(36)
#घोषणा IRQ_PCI_INTA		(IRQ_PCI_INTAD_BASE + 0)
#घोषणा IRQ_PCI_INTB		(IRQ_PCI_INTAD_BASE + 1)
#घोषणा IRQ_PCI_INTC		(IRQ_PCI_INTAD_BASE + 2)
#घोषणा IRQ_PCI_INTD		(IRQ_PCI_INTAD_BASE + 3)
#घोषणा NUM_PCI_IRQS		(4)

/* number of entries in vector dispatch table */
#घोषणा IRQ_TSI108_TAB_SIZE	(TSI108_MAX_VECTORS + 1)

/* Mapping of MPIC outमाला_दो to processors' पूर्णांकerrupt pins */

#घोषणा Iसूची_INT_OUT0		0x1
#घोषणा Iसूची_INT_OUT1		0x2
#घोषणा Iसूची_INT_OUT2		0x4
#घोषणा Iसूची_INT_OUT3		0x8

/*---------------------------------------------------------------
 * IRQ line configuration parameters */

/* Interrupt delivery modes */
प्रकार क्रमागत अणु
	TSI108_IRQ_सूचीECTED,
	TSI108_IRQ_DISTRIBUTED,
पूर्ण TSI108_IRQ_MODE;
#पूर्ण_अगर				/*  _ASM_POWERPC_TSI108_IRQ_H */
