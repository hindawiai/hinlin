<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SDK7786 FPGA IRQ Controller Support.
 *
 * Copyright (C) 2010  Matt Fleming
 * Copyright (C) 2010  Paul Mundt
 */
#समावेश <linux/irq.h>
#समावेश <mach/fpga.h>
#समावेश <mach/irq.h>

क्रमागत अणु
	ATA_IRQ_BIT		= 1,
	SPI_BUSY_BIT		= 2,
	LIRQ5_BIT		= 3,
	LIRQ6_BIT		= 4,
	LIRQ7_BIT		= 5,
	LIRQ8_BIT		= 6,
	KEY_IRQ_BIT		= 7,
	PEN_IRQ_BIT		= 8,
	ETH_IRQ_BIT		= 9,
	RTC_ALARM_BIT		= 10,
	CRYSTAL_FAIL_BIT	= 12,
	ETH_PME_BIT		= 14,
पूर्ण;

व्योम __init sdk7786_init_irq(व्योम)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	/* Enable priority encoding क्रम all IRLs */
	fpga_ग_लिखो_reg(fpga_पढ़ो_reg(INTMSR) | 0x0303, INTMSR);

	/* Clear FPGA पूर्णांकerrupt status रेजिस्टरs */
	fpga_ग_लिखो_reg(0x0000, INTASR);
	fpga_ग_लिखो_reg(0x0000, INTBSR);

	/* Unmask FPGA पूर्णांकerrupts */
	पंचांगp = fpga_पढ़ो_reg(INTAMR);
	पंचांगp &= ~(1 << ETH_IRQ_BIT);
	fpga_ग_लिखो_reg(पंचांगp, INTAMR);

	plat_irq_setup_pins(IRQ_MODE_IRL7654_MASK);
	plat_irq_setup_pins(IRQ_MODE_IRL3210_MASK);
पूर्ण
