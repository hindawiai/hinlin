<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2014 Oleksij Rempel <linux@rempel-privat.de>
 */

#अगर_अघोषित _ALPHASCALE_ASM9260_ICOLL_H
#घोषणा _ALPHASCALE_ASM9260_ICOLL_H

#घोषणा ASM9260_NUM_IRQS		64
/*
 * this device provide 4 offsets क्रम each रेजिस्टर:
 * 0x0 - plain पढ़ो ग_लिखो mode
 * 0x4 - set mode, OR logic.
 * 0x8 - clr mode, XOR logic.
 * 0xc - togle mode.
 */

#घोषणा ASM9260_HW_ICOLL_VECTOR				0x0000
/*
 * bits 31:2
 * This रेजिस्टर presents the vector address क्रम the पूर्णांकerrupt currently
 * active on the CPU IRQ input. Writing to this रेजिस्टर notअगरies the
 * पूर्णांकerrupt collector that the पूर्णांकerrupt service routine क्रम the current
 * पूर्णांकerrupt has been entered.
 * The exception trap should have a LDPC inकाष्ठाion from this address:
 * LDPC ASM9260_HW_ICOLL_VECTOR_ADDR; IRQ exception at 0xffff0018
 */

/*
 * The Interrupt Collector Level Acknowledge Register is used by software to
 * indicate the completion of an पूर्णांकerrupt on a specअगरic level.
 * This रेजिस्टर is written at the very end of an पूर्णांकerrupt service routine. If
 * nesting is used then the CPU irq must be turned on beक्रमe writing to this
 * रेजिस्टर to aव्योम a race condition in the CPU पूर्णांकerrupt hardware.
 */
#घोषणा ASM9260_HW_ICOLL_LEVELACK			0x0010
#घोषणा ASM9260_BM_LEVELn(nr)				BIT(nr)

#घोषणा ASM9260_HW_ICOLL_CTRL				0x0020
/*
 * ASM9260_BM_CTRL_SFTRST and ASM9260_BM_CTRL_CLKGATE are not available on
 * यंत्र9260.
 */
#घोषणा ASM9260_BM_CTRL_SFTRST				BIT(31)
#घोषणा ASM9260_BM_CTRL_CLKGATE				BIT(30)
/* disable पूर्णांकerrupt level nesting */
#घोषणा ASM9260_BM_CTRL_NO_NESTING			BIT(19)
/*
 * Set this bit to one enable the RISC32-style पढ़ो side effect associated with
 * the vector address रेजिस्टर. In this mode, पूर्णांकerrupt in-service is संकेतed
 * by the पढ़ो of the ASM9260_HW_ICOLL_VECTOR रेजिस्टर to acquire the पूर्णांकerrupt
 * vector address. Set this bit to zero क्रम normal operation, in which the ISR
 * संकेतs in-service explicitly by means of a ग_लिखो to the
 * ASM9260_HW_ICOLL_VECTOR रेजिस्टर.
 * 0 - Must Write to Vector रेजिस्टर to go in-service.
 * 1 - Go in-service as a पढ़ो side effect
 */
#घोषणा ASM9260_BM_CTRL_ARM_RSE_MODE			BIT(18)
#घोषणा ASM9260_BM_CTRL_IRQ_ENABLE			BIT(16)

#घोषणा ASM9260_HW_ICOLL_STAT_OFFSET			0x0030
/*
 * bits 5:0
 * Vector number of current पूर्णांकerrupt. Multiply by 4 and add to vector base
 * address to obtain the value in ASM9260_HW_ICOLL_VECTOR.
 */

/*
 * RAW0 and RAW1 provides a पढ़ो-only view of the raw पूर्णांकerrupt request lines
 * coming from various parts of the chip. Its purpose is to improve diagnostic
 * observability.
 */
#घोषणा ASM9260_HW_ICOLL_RAW0				0x0040
#घोषणा ASM9260_HW_ICOLL_RAW1				0x0050

#घोषणा ASM9260_HW_ICOLL_INTERRUPT0			0x0060
#घोषणा ASM9260_HW_ICOLL_INTERRUPTn(n)		(0x0060 + ((n) >> 2) * 0x10)
/*
 * WARNING: Modअगरying the priority of an enabled पूर्णांकerrupt may result in
 * undefined behavior.
 */
#घोषणा ASM9260_BM_INT_PRIORITY_MASK			0x3
#घोषणा ASM9260_BM_INT_ENABLE				BIT(2)
#घोषणा ASM9260_BM_INT_SOFTIRQ				BIT(3)

#घोषणा ASM9260_BM_ICOLL_INTERRUPTn_SHIFT(n)		(((n) & 0x3) << 3)
#घोषणा ASM9260_BM_ICOLL_INTERRUPTn_ENABLE(n)		(1 << (2 + \
			ASM9260_BM_ICOLL_INTERRUPTn_SHIFT(n)))

#घोषणा ASM9260_HW_ICOLL_VBASE				0x0160
/*
 * bits 31:2
 * This bitfield holds the upper 30 bits of the base address of the vector
 * table.
 */

#घोषणा ASM9260_HW_ICOLL_CLEAR0				0x01d0
#घोषणा ASM9260_HW_ICOLL_CLEAR1				0x01e0
#घोषणा ASM9260_HW_ICOLL_CLEARn(n)			(((n >> 5) * 0x10) \
							+ SET_REG)
#घोषणा ASM9260_BM_CLEAR_BIT(n)				BIT(n & 0x1f)

/* Scratchpad */
#घोषणा ASM9260_HW_ICOLL_UNDEF_VECTOR			0x01f0
#पूर्ण_अगर
