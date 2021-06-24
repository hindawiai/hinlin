<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/renesas/sdk7780/irq.c
 *
 * Renesas Technology Europe SDK7780 Support.
 *
 * Copyright (C) 2008  Nicholas Beck <nbeck@mpc-data.co.uk>
 */
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <mach/sdk7780.h>

क्रमागत अणु
	UNUSED = 0,
	/* board specअगरic पूर्णांकerrupt sources */
	SMC91C111,	/* Ethernet controller */
पूर्ण;

अटल काष्ठा पूर्णांकc_vect fpga_vectors[] __initdata = अणु
	INTC_IRQ(SMC91C111, IRQ_ETHERNET),
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg fpga_mask_रेजिस्टरs[] __initdata = अणु
	अणु 0, FPGA_IRQ0MR, 16,
	  अणु 0, 0, 0, 0, 0, 0, 0, 0,
	    0, 0, 0, SMC91C111, 0, 0, 0, 0 पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(fpga_पूर्णांकc_desc, "sdk7780-irq", fpga_vectors,
			 शून्य, fpga_mask_रेजिस्टरs, शून्य, शून्य);

व्योम __init init_sdk7780_IRQ(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "Using SDK7780 interrupt controller.\n");

	__raw_ग_लिखोw(0xFFFF, FPGA_IRQ0MR);
	/* Setup IRL 0-3 */
	__raw_ग_लिखोw(0x0003, FPGA_IMSR);
	plat_irq_setup_pins(IRQ_MODE_IRL3210);

	रेजिस्टर_पूर्णांकc_controller(&fpga_पूर्णांकc_desc);
पूर्ण
