<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas Solutions Highlander R7780MP Support.
 *
 * Copyright (C) 2002  Atom Create Engineering Co., Ltd.
 * Copyright (C) 2006  Paul Mundt
 * Copyright (C) 2007  Magnus Damm
 */
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <mach/highlander.h>

क्रमागत अणु
	UNUSED = 0,

	/* board specअगरic पूर्णांकerrupt sources */
	CF,		/* Compact Flash */
	TP,		/* Touch panel */
	SCIF1,		/* FPGA SCIF1 */
	SCIF0,		/* FPGA SCIF0 */
	SMBUS,		/* SMBUS */
	RTC,		/* RTC Alarm */
	AX88796,	/* Ethernet controller */
	PSW,		/* Push Switch */

	/* बाह्यal bus connector */
	EXT1, EXT2, EXT4, EXT5, EXT6,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_IRQ(CF, IRQ_CF),
	INTC_IRQ(TP, IRQ_TP),
	INTC_IRQ(SCIF1, IRQ_SCIF1),
	INTC_IRQ(SCIF0, IRQ_SCIF0),
	INTC_IRQ(SMBUS, IRQ_SMBUS),
	INTC_IRQ(RTC, IRQ_RTC),
	INTC_IRQ(AX88796, IRQ_AX88796),
	INTC_IRQ(PSW, IRQ_PSW),

	INTC_IRQ(EXT1, IRQ_EXT1), INTC_IRQ(EXT2, IRQ_EXT2),
	INTC_IRQ(EXT4, IRQ_EXT4), INTC_IRQ(EXT5, IRQ_EXT5),
	INTC_IRQ(EXT6, IRQ_EXT6),
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xa4000000, 0, 16, /* IRLMSK */
	  अणु SCIF0, SCIF1, RTC, 0, CF, 0, TP, SMBUS,
	    0, EXT6, EXT5, EXT4, EXT2, EXT1, PSW, AX88796 पूर्ण पूर्ण,
पूर्ण;

अटल अचिन्हित अक्षर irl2irq[HL_NR_IRL] __initdata = अणु
	0, IRQ_CF, IRQ_TP, IRQ_SCIF1,
	IRQ_SCIF0, IRQ_SMBUS, IRQ_RTC, IRQ_EXT6,
	IRQ_EXT5, IRQ_EXT4, IRQ_EXT2, IRQ_EXT1,
	0, IRQ_AX88796, IRQ_PSW,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "r7780mp", vectors,
			 शून्य, mask_रेजिस्टरs, शून्य, शून्य);

अचिन्हित अक्षर * __init highlander_plat_irq_setup(व्योम)
अणु
	अगर ((__raw_पढ़ोw(0xa4000700) & 0xf000) == 0x2000) अणु
		prपूर्णांकk(KERN_INFO "Using r7780mp interrupt controller.\n");
		रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
		वापस irl2irq;
	पूर्ण

	वापस शून्य;
पूर्ण
