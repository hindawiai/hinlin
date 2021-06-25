<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boards/mach-landisk/irq.c
 *
 * I-O DATA Device, Inc. LANDISK Support
 *
 * Copyright (C) 2005-2007 kogiidena
 * Copyright (C) 2011 Nobuhiro Iwamatsu
 *
 * Copyright (C) 2001  Ian da Silva, Jeremy Siegel
 * Based largely on io_se.c.
 */

#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <mach-landisk/mach/iodata_landisk.h>

क्रमागत अणु
	UNUSED = 0,

	PCI_INTA, /* PCI पूर्णांक A */
	PCI_INTB, /* PCI पूर्णांक B */
	PCI_INTC, /* PCI पूर्णांक C */
	PCI_INTD, /* PCI पूर्णांक D */
	ATA,	  /* ATA */
	FATA,	  /* CF */
	POWER,	  /* Power swtich */
	BUTTON,	  /* Button swtich */
पूर्ण;

/* Vectors क्रम LANDISK */
अटल काष्ठा पूर्णांकc_vect vectors_landisk[] __initdata = अणु
	INTC_IRQ(PCI_INTA, IRQ_PCIINTA),
	INTC_IRQ(PCI_INTB, IRQ_PCIINTB),
	INTC_IRQ(PCI_INTC, IRQ_PCIINTC),
	INTC_IRQ(PCI_INTD, IRQ_PCIINTD),
	INTC_IRQ(ATA, IRQ_ATA),
	INTC_IRQ(FATA, IRQ_FATA),
	INTC_IRQ(POWER, IRQ_POWER),
	INTC_IRQ(BUTTON, IRQ_BUTTON),
पूर्ण;

/* IRLMSK mask रेजिस्टर layout क्रम LANDISK */
अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs_landisk[] __initdata = अणु
	अणु PA_IMASK, 0, 8, /* IRLMSK */
	  अणु  BUTTON, POWER, FATA, ATA,
	     PCI_INTD, PCI_INTC, PCI_INTB, PCI_INTA,
	  पूर्ण
	पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc_landisk, "landisk", vectors_landisk, शून्य,
			mask_रेजिस्टरs_landisk, शून्य, शून्य);
/*
 * Initialize IRQ setting
 */
व्योम __init init_landisk_IRQ(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_landisk);
	__raw_ग_लिखोb(0x00, PA_PWRINT_CLR);
पूर्ण
