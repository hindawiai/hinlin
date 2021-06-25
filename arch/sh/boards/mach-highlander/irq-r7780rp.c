<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas Solutions Highlander R7780RP-1 Support.
 *
 * Copyright (C) 2002  Atom Create Engineering Co., Ltd.
 * Copyright (C) 2006  Paul Mundt
 * Copyright (C) 2008  Magnus Damm
 */
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <mach/highlander.h>

क्रमागत अणु
	UNUSED = 0,

	/* board specअगरic पूर्णांकerrupt sources */

	AX88796,          /* Ethernet controller */
	PSW,              /* Push Switch */
	CF,               /* Compact Flash */

	PCI_A,
	PCI_B,
	PCI_C,
	PCI_D,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_IRQ(PCI_A, 65), /* dirty: overग_लिखो cpu vectors क्रम pci */
	INTC_IRQ(PCI_B, 66),
	INTC_IRQ(PCI_C, 67),
	INTC_IRQ(PCI_D, 68),
	INTC_IRQ(CF, IRQ_CF),
	INTC_IRQ(PSW, IRQ_PSW),
	INTC_IRQ(AX88796, IRQ_AX88796),
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xa5000000, 0, 16, /* IRLMSK */
	  अणु PCI_A, PCI_B, PCI_C, PCI_D, CF, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, PSW, AX88796 पूर्ण पूर्ण,
पूर्ण;

अटल अचिन्हित अक्षर irl2irq[HL_NR_IRL] __initdata = अणु
	65, 66, 67, 68,
	IRQ_CF, 0, 0, 0,
	0, 0, 0, 0,
	IRQ_AX88796, IRQ_PSW
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "r7780rp", vectors,
			 शून्य, mask_रेजिस्टरs, शून्य, शून्य);

अचिन्हित अक्षर * __init highlander_plat_irq_setup(व्योम)
अणु
	अगर (__raw_पढ़ोw(0xa5000600)) अणु
		prपूर्णांकk(KERN_INFO "Using r7780rp interrupt controller.\n");
		रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
		वापस irl2irq;
	पूर्ण

	वापस शून्य;
पूर्ण
