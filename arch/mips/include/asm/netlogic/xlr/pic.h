<शैली गुरु>
/*
 * Copyright 2003-2011 NetLogic Microप्रणालीs, Inc. (NetLogic). All rights
 * reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the NetLogic
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NETLOGIC ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _ASM_NLM_XLR_PIC_H
#घोषणा _ASM_NLM_XLR_PIC_H

#घोषणा PIC_CLK_HZ			66666666
#घोषणा pic_समयr_freq()		PIC_CLK_HZ

/* PIC hardware पूर्णांकerrupt numbers */
#घोषणा PIC_IRT_WD_INDEX		0
#घोषणा PIC_IRT_TIMER_0_INDEX		1
#घोषणा PIC_IRT_TIMER_INDEX(i)		((i) + PIC_IRT_TIMER_0_INDEX)
#घोषणा PIC_IRT_TIMER_1_INDEX		2
#घोषणा PIC_IRT_TIMER_2_INDEX		3
#घोषणा PIC_IRT_TIMER_3_INDEX		4
#घोषणा PIC_IRT_TIMER_4_INDEX		5
#घोषणा PIC_IRT_TIMER_5_INDEX		6
#घोषणा PIC_IRT_TIMER_6_INDEX		7
#घोषणा PIC_IRT_TIMER_7_INDEX		8
#घोषणा PIC_IRT_CLOCK_INDEX		PIC_IRT_TIMER_7_INDEX
#घोषणा PIC_IRT_UART_0_INDEX		9
#घोषणा PIC_IRT_UART_1_INDEX		10
#घोषणा PIC_IRT_I2C_0_INDEX		11
#घोषणा PIC_IRT_I2C_1_INDEX		12
#घोषणा PIC_IRT_PCMCIA_INDEX		13
#घोषणा PIC_IRT_GPIO_INDEX		14
#घोषणा PIC_IRT_HYPER_INDEX		15
#घोषणा PIC_IRT_PCIX_INDEX		16
/* XLS */
#घोषणा PIC_IRT_CDE_INDEX		15
#घोषणा PIC_IRT_BRIDGE_TB_XLS_INDEX	16
/* XLS */
#घोषणा PIC_IRT_GMAC0_INDEX		17
#घोषणा PIC_IRT_GMAC1_INDEX		18
#घोषणा PIC_IRT_GMAC2_INDEX		19
#घोषणा PIC_IRT_GMAC3_INDEX		20
#घोषणा PIC_IRT_XGS0_INDEX		21
#घोषणा PIC_IRT_XGS1_INDEX		22
#घोषणा PIC_IRT_HYPER_FATAL_INDEX	23
#घोषणा PIC_IRT_PCIX_FATAL_INDEX	24
#घोषणा PIC_IRT_BRIDGE_AERR_INDEX	25
#घोषणा PIC_IRT_BRIDGE_BERR_INDEX	26
#घोषणा PIC_IRT_BRIDGE_TB_XLR_INDEX	27
#घोषणा PIC_IRT_BRIDGE_AERR_NMI_INDEX	28
/* XLS */
#घोषणा PIC_IRT_GMAC4_INDEX		21
#घोषणा PIC_IRT_GMAC5_INDEX		22
#घोषणा PIC_IRT_GMAC6_INDEX		23
#घोषणा PIC_IRT_GMAC7_INDEX		24
#घोषणा PIC_IRT_BRIDGE_ERR_INDEX	25
#घोषणा PIC_IRT_PCIE_LINK0_INDEX	26
#घोषणा PIC_IRT_PCIE_LINK1_INDEX	27
#घोषणा PIC_IRT_PCIE_LINK2_INDEX	23
#घोषणा PIC_IRT_PCIE_LINK3_INDEX	24
#घोषणा PIC_IRT_PCIE_XLSB0_LINK2_INDEX	28
#घोषणा PIC_IRT_PCIE_XLSB0_LINK3_INDEX	29
#घोषणा PIC_IRT_SRIO_LINK0_INDEX	26
#घोषणा PIC_IRT_SRIO_LINK1_INDEX	27
#घोषणा PIC_IRT_SRIO_LINK2_INDEX	28
#घोषणा PIC_IRT_SRIO_LINK3_INDEX	29
#घोषणा PIC_IRT_PCIE_INT_INDEX		28
#घोषणा PIC_IRT_PCIE_FATAL_INDEX	29
#घोषणा PIC_IRT_GPIO_B_INDEX		30
#घोषणा PIC_IRT_USB_INDEX		31
/* XLS */
#घोषणा PIC_NUM_IRTS			32


#घोषणा PIC_CLOCK_TIMER			7

/* PIC Registers */
#घोषणा PIC_CTRL			0x00
#घोषणा PIC_CTRL_STE			8	/* समयr enable start bit */
#घोषणा PIC_IPI				0x04
#घोषणा PIC_INT_ACK			0x06

#घोषणा WD_MAX_VAL_0			0x08
#घोषणा WD_MAX_VAL_1			0x09
#घोषणा WD_MASK_0			0x0a
#घोषणा WD_MASK_1			0x0b
#घोषणा WD_HEARBEAT_0			0x0c
#घोषणा WD_HEARBEAT_1			0x0d

#घोषणा PIC_IRT_0_BASE			0x40
#घोषणा PIC_IRT_1_BASE			0x80
#घोषणा PIC_TIMER_MAXVAL_0_BASE		0x100
#घोषणा PIC_TIMER_MAXVAL_1_BASE		0x110
#घोषणा PIC_TIMER_COUNT_0_BASE		0x120
#घोषणा PIC_TIMER_COUNT_1_BASE		0x130

#घोषणा PIC_IRT_0(picपूर्णांकr)	(PIC_IRT_0_BASE + (picपूर्णांकr))
#घोषणा PIC_IRT_1(picपूर्णांकr)	(PIC_IRT_1_BASE + (picपूर्णांकr))

#घोषणा PIC_TIMER_MAXVAL_0(i)	(PIC_TIMER_MAXVAL_0_BASE + (i))
#घोषणा PIC_TIMER_MAXVAL_1(i)	(PIC_TIMER_MAXVAL_1_BASE + (i))
#घोषणा PIC_TIMER_COUNT_0(i)	(PIC_TIMER_COUNT_0_BASE + (i))
#घोषणा PIC_TIMER_COUNT_1(i)	(PIC_TIMER_COUNT_0_BASE + (i))

/*
 * Mapping between hardware पूर्णांकerrupt numbers and IRQs on CPU
 * we use a simple scheme to map PIC पूर्णांकerrupts 0-31 to IRQs
 * 8-39. This leaves the IRQ 0-7 क्रम cpu पूर्णांकerrupts like
 * count/compare and FMN
 */
#घोषणा PIC_IRQ_BASE		8
#घोषणा PIC_INTR_TO_IRQ(i)	(PIC_IRQ_BASE + (i))
#घोषणा PIC_IRQ_TO_INTR(i)	((i) - PIC_IRQ_BASE)

#घोषणा PIC_IRT_FIRST_IRQ	PIC_IRQ_BASE
#घोषणा PIC_WD_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_WD_INDEX)
#घोषणा PIC_TIMER_0_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_TIMER_0_INDEX)
#घोषणा PIC_TIMER_1_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_TIMER_1_INDEX)
#घोषणा PIC_TIMER_2_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_TIMER_2_INDEX)
#घोषणा PIC_TIMER_3_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_TIMER_3_INDEX)
#घोषणा PIC_TIMER_4_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_TIMER_4_INDEX)
#घोषणा PIC_TIMER_5_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_TIMER_5_INDEX)
#घोषणा PIC_TIMER_6_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_TIMER_6_INDEX)
#घोषणा PIC_TIMER_7_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_TIMER_7_INDEX)
#घोषणा PIC_CLOCK_IRQ		(PIC_TIMER_7_IRQ)
#घोषणा PIC_UART_0_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_UART_0_INDEX)
#घोषणा PIC_UART_1_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_UART_1_INDEX)
#घोषणा PIC_I2C_0_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_I2C_0_INDEX)
#घोषणा PIC_I2C_1_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_I2C_1_INDEX)
#घोषणा PIC_PCMCIA_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_PCMCIA_INDEX)
#घोषणा PIC_GPIO_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_GPIO_INDEX)
#घोषणा PIC_HYPER_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_HYPER_INDEX)
#घोषणा PIC_PCIX_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_PCIX_INDEX)
/* XLS */
#घोषणा PIC_CDE_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_CDE_INDEX)
#घोषणा PIC_BRIDGE_TB_XLS_IRQ	PIC_INTR_TO_IRQ(PIC_IRT_BRIDGE_TB_XLS_INDEX)
/* end XLS */
#घोषणा PIC_GMAC_0_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_GMAC0_INDEX)
#घोषणा PIC_GMAC_1_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_GMAC1_INDEX)
#घोषणा PIC_GMAC_2_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_GMAC2_INDEX)
#घोषणा PIC_GMAC_3_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_GMAC3_INDEX)
#घोषणा PIC_XGS_0_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_XGS0_INDEX)
#घोषणा PIC_XGS_1_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_XGS1_INDEX)
#घोषणा PIC_HYPER_FATAL_IRQ	PIC_INTR_TO_IRQ(PIC_IRT_HYPER_FATAL_INDEX)
#घोषणा PIC_PCIX_FATAL_IRQ	PIC_INTR_TO_IRQ(PIC_IRT_PCIX_FATAL_INDEX)
#घोषणा PIC_BRIDGE_AERR_IRQ	PIC_INTR_TO_IRQ(PIC_IRT_BRIDGE_AERR_INDEX)
#घोषणा PIC_BRIDGE_BERR_IRQ	PIC_INTR_TO_IRQ(PIC_IRT_BRIDGE_BERR_INDEX)
#घोषणा PIC_BRIDGE_TB_XLR_IRQ	PIC_INTR_TO_IRQ(PIC_IRT_BRIDGE_TB_XLR_INDEX)
#घोषणा PIC_BRIDGE_AERR_NMI_IRQ PIC_INTR_TO_IRQ(PIC_IRT_BRIDGE_AERR_NMI_INDEX)
/* XLS defines */
#घोषणा PIC_GMAC_4_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_GMAC4_INDEX)
#घोषणा PIC_GMAC_5_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_GMAC5_INDEX)
#घोषणा PIC_GMAC_6_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_GMAC6_INDEX)
#घोषणा PIC_GMAC_7_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_GMAC7_INDEX)
#घोषणा PIC_BRIDGE_ERR_IRQ	PIC_INTR_TO_IRQ(PIC_IRT_BRIDGE_ERR_INDEX)
#घोषणा PIC_PCIE_LINK0_IRQ	PIC_INTR_TO_IRQ(PIC_IRT_PCIE_LINK0_INDEX)
#घोषणा PIC_PCIE_LINK1_IRQ	PIC_INTR_TO_IRQ(PIC_IRT_PCIE_LINK1_INDEX)
#घोषणा PIC_PCIE_LINK2_IRQ	PIC_INTR_TO_IRQ(PIC_IRT_PCIE_LINK2_INDEX)
#घोषणा PIC_PCIE_LINK3_IRQ	PIC_INTR_TO_IRQ(PIC_IRT_PCIE_LINK3_INDEX)
#घोषणा PIC_PCIE_XLSB0_LINK2_IRQ PIC_INTR_TO_IRQ(PIC_IRT_PCIE_XLSB0_LINK2_INDEX)
#घोषणा PIC_PCIE_XLSB0_LINK3_IRQ PIC_INTR_TO_IRQ(PIC_IRT_PCIE_XLSB0_LINK3_INDEX)
#घोषणा PIC_SRIO_LINK0_IRQ	PIC_INTR_TO_IRQ(PIC_IRT_SRIO_LINK0_INDEX)
#घोषणा PIC_SRIO_LINK1_IRQ	PIC_INTR_TO_IRQ(PIC_IRT_SRIO_LINK1_INDEX)
#घोषणा PIC_SRIO_LINK2_IRQ	PIC_INTR_TO_IRQ(PIC_IRT_SRIO_LINK2_INDEX)
#घोषणा PIC_SRIO_LINK3_IRQ	PIC_INTR_TO_IRQ(PIC_IRT_SRIO_LINK3_INDEX)
#घोषणा PIC_PCIE_INT_IRQ	PIC_INTR_TO_IRQ(PIC_IRT_PCIE_INT__INDEX)
#घोषणा PIC_PCIE_FATAL_IRQ	PIC_INTR_TO_IRQ(PIC_IRT_PCIE_FATAL_INDEX)
#घोषणा PIC_GPIO_B_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_GPIO_B_INDEX)
#घोषणा PIC_USB_IRQ		PIC_INTR_TO_IRQ(PIC_IRT_USB_INDEX)
#घोषणा PIC_IRT_LAST_IRQ	PIC_USB_IRQ
/* end XLS */

#अगर_अघोषित __ASSEMBLY__

#घोषणा PIC_IRQ_IS_EDGE_TRIGGERED(irq)	(((irq) >= PIC_TIMER_0_IRQ) && \
					((irq) <= PIC_TIMER_7_IRQ))
#घोषणा PIC_IRQ_IS_IRT(irq)		(((irq) >= PIC_IRT_FIRST_IRQ) && \
					((irq) <= PIC_IRT_LAST_IRQ))

अटल अंतरभूत पूर्णांक
nlm_irq_to_irt(पूर्णांक irq)
अणु
	अगर (PIC_IRQ_IS_IRT(irq) == 0)
		वापस -1;

	वापस PIC_IRQ_TO_INTR(irq);
पूर्ण

अटल अंतरभूत पूर्णांक
nlm_irt_to_irq(पूर्णांक irt)
अणु

	वापस PIC_INTR_TO_IRQ(irt);
पूर्ण

अटल अंतरभूत व्योम
nlm_pic_enable_irt(uपूर्णांक64_t base, पूर्णांक irt)
अणु
	uपूर्णांक32_t reg;

	reg = nlm_पढ़ो_reg(base, PIC_IRT_1(irt));
	nlm_ग_लिखो_reg(base, PIC_IRT_1(irt), reg | (1u << 31));
पूर्ण

अटल अंतरभूत व्योम
nlm_pic_disable_irt(uपूर्णांक64_t base, पूर्णांक irt)
अणु
	uपूर्णांक32_t reg;

	reg = nlm_पढ़ो_reg(base, PIC_IRT_1(irt));
	nlm_ग_लिखो_reg(base, PIC_IRT_1(irt), reg & ~(1u << 31));
पूर्ण

अटल अंतरभूत व्योम
nlm_pic_send_ipi(uपूर्णांक64_t base, पूर्णांक hwt, पूर्णांक irq, पूर्णांक nmi)
अणु
	अचिन्हित पूर्णांक tid, pid;

	tid = hwt & 0x3;
	pid = (hwt >> 2) & 0x07;
	nlm_ग_लिखो_reg(base, PIC_IPI,
		(pid << 20) | (tid << 16) | (nmi << 8) | irq);
पूर्ण

अटल अंतरभूत व्योम
nlm_pic_ack(uपूर्णांक64_t base, पूर्णांक irt)
अणु
	nlm_ग_लिखो_reg(base, PIC_INT_ACK, 1u << irt);
पूर्ण

अटल अंतरभूत व्योम
nlm_pic_init_irt(uपूर्णांक64_t base, पूर्णांक irt, पूर्णांक irq, पूर्णांक hwt, पूर्णांक en)
अणु
	nlm_ग_लिखो_reg(base, PIC_IRT_0(irt), (1u << hwt));
	/* local scheduling, invalid, level by शेष */
	nlm_ग_लिखो_reg(base, PIC_IRT_1(irt),
		(en << 30) | (1 << 6) | irq);
पूर्ण

अटल अंतरभूत uपूर्णांक64_t
nlm_pic_पढ़ो_समयr(uपूर्णांक64_t base, पूर्णांक समयr)
अणु
	uपूर्णांक32_t up1, up2, low;

	up1 = nlm_पढ़ो_reg(base, PIC_TIMER_COUNT_1(समयr));
	low = nlm_पढ़ो_reg(base, PIC_TIMER_COUNT_0(समयr));
	up2 = nlm_पढ़ो_reg(base, PIC_TIMER_COUNT_1(समयr));

	अगर (up1 != up2) /* wrapped, get the new low */
		low = nlm_पढ़ो_reg(base, PIC_TIMER_COUNT_0(समयr));
	वापस ((uपूर्णांक64_t)up2 << 32) | low;

पूर्ण

अटल अंतरभूत uपूर्णांक32_t
nlm_pic_पढ़ो_समयr32(uपूर्णांक64_t base, पूर्णांक समयr)
अणु
	वापस nlm_पढ़ो_reg(base, PIC_TIMER_COUNT_0(समयr));
पूर्ण

अटल अंतरभूत व्योम
nlm_pic_set_समयr(uपूर्णांक64_t base, पूर्णांक समयr, uपूर्णांक64_t value, पूर्णांक irq, पूर्णांक cpu)
अणु
	uपूर्णांक32_t up, low;
	uपूर्णांक64_t pic_ctrl = nlm_पढ़ो_reg(base, PIC_CTRL);
	पूर्णांक en;

	en = (irq > 0);
	up = value >> 32;
	low = value & 0xFFFFFFFF;
	nlm_ग_लिखो_reg(base, PIC_TIMER_MAXVAL_0(समयr), low);
	nlm_ग_लिखो_reg(base, PIC_TIMER_MAXVAL_1(समयr), up);
	nlm_pic_init_irt(base, PIC_IRT_TIMER_INDEX(समयr), irq, cpu, 0);

	/* enable the समयr */
	pic_ctrl |= (1 << (PIC_CTRL_STE + समयr));
	nlm_ग_लिखो_reg(base, PIC_CTRL, pic_ctrl);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _ASM_NLM_XLR_PIC_H */
