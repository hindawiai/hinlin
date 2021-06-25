<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas Solutions Highlander R7785RP Support.
 *
 * Copyright (C) 2002  Atom Create Engineering Co., Ltd.
 * Copyright (C) 2006 - 2008  Paul Mundt
 * Copyright (C) 2007  Magnus Damm
 */
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <mach/highlander.h>

क्रमागत अणु
	UNUSED = 0,

	/* FPGA specअगरic पूर्णांकerrupt sources */
	CF,		/* Compact Flash */
	SMBUS,		/* SMBUS */
	TP,		/* Touch panel */
	RTC,		/* RTC Alarm */
	TH_ALERT,	/* Temperature sensor */
	AX88796,	/* Ethernet controller */

	/* बाह्यal bus connector */
	EXT0, EXT1, EXT2, EXT3, EXT4, EXT5, EXT6, EXT7,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_IRQ(CF, IRQ_CF),
	INTC_IRQ(SMBUS, IRQ_SMBUS),
	INTC_IRQ(TP, IRQ_TP),
	INTC_IRQ(RTC, IRQ_RTC),
	INTC_IRQ(TH_ALERT, IRQ_TH_ALERT),

	INTC_IRQ(EXT0, IRQ_EXT0), INTC_IRQ(EXT1, IRQ_EXT1),
	INTC_IRQ(EXT2, IRQ_EXT2), INTC_IRQ(EXT3, IRQ_EXT3),

	INTC_IRQ(EXT4, IRQ_EXT4), INTC_IRQ(EXT5, IRQ_EXT5),
	INTC_IRQ(EXT6, IRQ_EXT6), INTC_IRQ(EXT7, IRQ_EXT7),

	INTC_IRQ(AX88796, IRQ_AX88796),
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xa4000010, 0, 16, /* IRLMCR1 */
	  अणु 0, 0, 0, 0, CF, AX88796, SMBUS, TP,
	    RTC, 0, TH_ALERT, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
	अणु 0xa4000012, 0, 16, /* IRLMCR2 */
	  अणु 0, 0, 0, 0, 0, 0, 0, 0,
	    EXT7, EXT6, EXT5, EXT4, EXT3, EXT2, EXT1, EXT0 पूर्ण पूर्ण,
पूर्ण;

अटल अचिन्हित अक्षर irl2irq[HL_NR_IRL] __initdata = अणु
	0, IRQ_CF, IRQ_EXT4, IRQ_EXT5,
	IRQ_EXT6, IRQ_EXT7, IRQ_SMBUS, IRQ_TP,
	IRQ_RTC, IRQ_TH_ALERT, IRQ_AX88796, IRQ_EXT0,
	IRQ_EXT1, IRQ_EXT2, IRQ_EXT3,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "r7785rp", vectors,
			 शून्य, mask_रेजिस्टरs, शून्य, शून्य);

अचिन्हित अक्षर * __init highlander_plat_irq_setup(व्योम)
अणु
	अगर ((__raw_पढ़ोw(0xa4000158) & 0xf000) != 0x1000)
		वापस शून्य;

	prपूर्णांकk(KERN_INFO "Using r7785rp interrupt controller.\n");

	__raw_ग_लिखोw(0x0000, PA_IRLSSR1);	/* FPGA IRLSSR1(CF_CD clear) */

	/* Setup the FPGA IRL */
	__raw_ग_लिखोw(0x0000, PA_IRLPRA);	/* FPGA IRLA */
	__raw_ग_लिखोw(0xe598, PA_IRLPRB);	/* FPGA IRLB */
	__raw_ग_लिखोw(0x7060, PA_IRLPRC);	/* FPGA IRLC */
	__raw_ग_लिखोw(0x0000, PA_IRLPRD);	/* FPGA IRLD */
	__raw_ग_लिखोw(0x4321, PA_IRLPRE);	/* FPGA IRLE */
	__raw_ग_लिखोw(0xdcba, PA_IRLPRF);	/* FPGA IRLF */

	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
	वापस irl2irq;
पूर्ण
