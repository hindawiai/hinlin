<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/renesas/rts7751r2d/irq.c
 *
 * Copyright (C) 2007  Magnus Damm
 * Copyright (C) 2000  Kazumoto Kojima
 *
 * Renesas Technology Sales RTS7751R2D Support, R2D-PLUS and R2D-1.
 *
 * Modअगरied क्रम RTS7751R2D by
 * Atom Create Engineering Co., Ltd. 2002.
 */
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <mach/r2d.h>

#घोषणा R2D_NR_IRL 13

क्रमागत अणु
	UNUSED = 0,

	/* board specअगरic पूर्णांकerrupt sources (R2D-1 and R2D-PLUS) */
	EXT,              /* EXT_INT0-3 */
	RTC_T, RTC_A,     /* Real Time Clock */
	AX88796,          /* Ethernet controller (R2D-1 board) */
	KEY,              /* Key input (R2D-PLUS board) */
	SDCARD,           /* SD Card */
	CF_CD, CF_IDE,    /* CF Card Detect + CF IDE */
	SM501,            /* SM501 aka Voyager */
	PCI_INTD_RTL8139, /* Ethernet controller */
	PCI_INTC_PCI1520, /* Cardbus/PCMCIA bridge */
	PCI_INTB_RTL8139, /* Ethernet controller with HUB (R2D-PLUS board) */
	PCI_INTB_SLOT,    /* PCI Slot 3.3v (R2D-1 board) */
	PCI_INTA_SLOT,    /* PCI Slot 3.3v */
	TP,               /* Touch Panel */
पूर्ण;

#अगर_घोषित CONFIG_RTS7751R2D_1

/* Vectors क्रम R2D-1 */
अटल काष्ठा पूर्णांकc_vect vectors_r2d_1[] __initdata = अणु
	INTC_IRQ(EXT, IRQ_EXT),
	INTC_IRQ(RTC_T, IRQ_RTC_T), INTC_IRQ(RTC_A, IRQ_RTC_A),
	INTC_IRQ(AX88796, IRQ_AX88796), INTC_IRQ(SDCARD, IRQ_SDCARD),
	INTC_IRQ(CF_CD, IRQ_CF_CD), INTC_IRQ(CF_IDE, IRQ_CF_IDE), /* ng */
	INTC_IRQ(SM501, IRQ_VOYAGER),
	INTC_IRQ(PCI_INTD_RTL8139, IRQ_PCI_INTD),
	INTC_IRQ(PCI_INTC_PCI1520, IRQ_PCI_INTC),
	INTC_IRQ(PCI_INTB_SLOT, IRQ_PCI_INTB),
	INTC_IRQ(PCI_INTA_SLOT, IRQ_PCI_INTA),
	INTC_IRQ(TP, IRQ_TP),
पूर्ण;

/* IRLMSK mask रेजिस्टर layout क्रम R2D-1 */
अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs_r2d_1[] __initdata = अणु
	अणु 0xa4000000, 0, 16, /* IRLMSK */
	  अणु TP, PCI_INTA_SLOT, PCI_INTB_SLOT,
	    PCI_INTC_PCI1520, PCI_INTD_RTL8139,
	    SM501, CF_IDE, CF_CD, SDCARD, AX88796,
	    RTC_A, RTC_T, 0, 0, 0, EXT पूर्ण पूर्ण,
पूर्ण;

/* IRLn to IRQ table क्रम R2D-1 */
अटल अचिन्हित अक्षर irl2irq_r2d_1[R2D_NR_IRL] __initdata = अणु
	IRQ_PCI_INTD, IRQ_CF_IDE, IRQ_CF_CD, IRQ_PCI_INTC,
	IRQ_VOYAGER, IRQ_AX88796, IRQ_RTC_A, IRQ_RTC_T,
	IRQ_SDCARD, IRQ_PCI_INTA, IRQ_PCI_INTB, IRQ_EXT,
	IRQ_TP,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc_r2d_1, "r2d-1", vectors_r2d_1,
			 शून्य, mask_रेजिस्टरs_r2d_1, शून्य, शून्य);

#पूर्ण_अगर /* CONFIG_RTS7751R2D_1 */

#अगर_घोषित CONFIG_RTS7751R2D_PLUS

/* Vectors क्रम R2D-PLUS */
अटल काष्ठा पूर्णांकc_vect vectors_r2d_plus[] __initdata = अणु
	INTC_IRQ(EXT, IRQ_EXT),
	INTC_IRQ(RTC_T, IRQ_RTC_T), INTC_IRQ(RTC_A, IRQ_RTC_A),
	INTC_IRQ(KEY, IRQ_KEY), INTC_IRQ(SDCARD, IRQ_SDCARD),
	INTC_IRQ(CF_CD, IRQ_CF_CD), INTC_IRQ(CF_IDE, IRQ_CF_IDE),
	INTC_IRQ(SM501, IRQ_VOYAGER),
	INTC_IRQ(PCI_INTD_RTL8139, IRQ_PCI_INTD),
	INTC_IRQ(PCI_INTC_PCI1520, IRQ_PCI_INTC),
	INTC_IRQ(PCI_INTB_RTL8139, IRQ_PCI_INTB),
	INTC_IRQ(PCI_INTA_SLOT, IRQ_PCI_INTA),
	INTC_IRQ(TP, IRQ_TP),
पूर्ण;

/* IRLMSK mask रेजिस्टर layout क्रम R2D-PLUS */
अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs_r2d_plus[] __initdata = अणु
	अणु 0xa4000000, 0, 16, /* IRLMSK */
	  अणु TP, PCI_INTA_SLOT, PCI_INTB_RTL8139,
	    PCI_INTC_PCI1520, PCI_INTD_RTL8139,
	    SM501, CF_IDE, CF_CD, SDCARD, KEY,
	    RTC_A, RTC_T, 0, 0, 0, EXT पूर्ण पूर्ण,
पूर्ण;

/* IRLn to IRQ table क्रम R2D-PLUS */
अटल अचिन्हित अक्षर irl2irq_r2d_plus[R2D_NR_IRL] __initdata = अणु
	IRQ_PCI_INTD, IRQ_CF_IDE, IRQ_CF_CD, IRQ_PCI_INTC,
	IRQ_VOYAGER, IRQ_KEY, IRQ_RTC_A, IRQ_RTC_T,
	IRQ_SDCARD, IRQ_PCI_INTA, IRQ_PCI_INTB, IRQ_EXT,
	IRQ_TP,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc_r2d_plus, "r2d-plus", vectors_r2d_plus,
			 शून्य, mask_रेजिस्टरs_r2d_plus, शून्य, शून्य);

#पूर्ण_अगर /* CONFIG_RTS7751R2D_PLUS */

अटल अचिन्हित अक्षर irl2irq[R2D_NR_IRL];

पूर्णांक rts7751r2d_irq_demux(पूर्णांक irq)
अणु
	अगर (irq >= R2D_NR_IRL || irq < 0 || !irl2irq[irq])
		वापस irq;

	वापस irl2irq[irq];
पूर्ण

/*
 * Initialize IRQ setting
 */
व्योम __init init_rts7751r2d_IRQ(व्योम)
अणु
	काष्ठा पूर्णांकc_desc *d;

	चयन (__raw_पढ़ोw(PA_VERREG) & 0xf0) अणु
#अगर_घोषित CONFIG_RTS7751R2D_PLUS
	हाल 0x10:
		prपूर्णांकk(KERN_INFO "Using R2D-PLUS interrupt controller.\n");
		d = &पूर्णांकc_desc_r2d_plus;
		स_नकल(irl2irq, irl2irq_r2d_plus, R2D_NR_IRL);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_RTS7751R2D_1
	हाल 0x00: /* according to manual */
	हाल 0x30: /* in reality */
		prपूर्णांकk(KERN_INFO "Using R2D-1 interrupt controller.\n");
		d = &पूर्णांकc_desc_r2d_1;
		स_नकल(irl2irq, irl2irq_r2d_1, R2D_NR_IRL);
		अवरोध;
#पूर्ण_अगर
	शेष:
		prपूर्णांकk(KERN_INFO "Unknown R2D interrupt controller 0x%04x\n",
		       __raw_पढ़ोw(PA_VERREG));
		वापस;
	पूर्ण

	रेजिस्टर_पूर्णांकc_controller(d);
पूर्ण
