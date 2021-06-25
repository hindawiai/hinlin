<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_RC32434_IRQ_H
#घोषणा __ASM_RC32434_IRQ_H

#घोषणा NR_IRQS 256

#समावेश <यंत्र/mach-generic/irq.h>
#समावेश <यंत्र/mach-rc32434/rb.h>

/* Interrupt Controller */
#घोषणा IC_GROUP0_PEND		(REGBASE + 0x38000)
#घोषणा IC_GROUP0_MASK		(REGBASE + 0x38008)
#घोषणा IC_GROUP_OFFSET		0x0C

#घोषणा NUM_INTR_GROUPS		5

/* 16550 UARTs */
#घोषणा GROUP0_IRQ_BASE		8	/* GRP2 IRQ numbers start here */
					/* GRP3 IRQ numbers start here */
#घोषणा GROUP1_IRQ_BASE		(GROUP0_IRQ_BASE + 32)
					/* GRP4 IRQ numbers start here */
#घोषणा GROUP2_IRQ_BASE		(GROUP1_IRQ_BASE + 32)
					/* GRP5 IRQ numbers start here */
#घोषणा GROUP3_IRQ_BASE		(GROUP2_IRQ_BASE + 32)
#घोषणा GROUP4_IRQ_BASE		(GROUP3_IRQ_BASE + 32)

#घोषणा UART0_IRQ		(GROUP3_IRQ_BASE + 0)

#घोषणा ETH0_DMA_RX_IRQ		(GROUP1_IRQ_BASE + 0)
#घोषणा ETH0_DMA_TX_IRQ		(GROUP1_IRQ_BASE + 1)
#घोषणा ETH0_RX_OVR_IRQ		(GROUP3_IRQ_BASE + 9)
#घोषणा ETH0_TX_UND_IRQ		(GROUP3_IRQ_BASE + 10)

#घोषणा GPIO_MAPPED_IRQ_BASE	GROUP4_IRQ_BASE
#घोषणा GPIO_MAPPED_IRQ_GROUP	4

#पूर्ण_अगर	/* __ASM_RC32434_IRQ_H */
