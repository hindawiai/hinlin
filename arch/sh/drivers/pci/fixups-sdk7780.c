<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/drivers/pci/fixups-sdk7780.c
 *
 * PCI fixups क्रम the SDK7780SE03
 *
 * Copyright (C) 2003  Lineo uSolutions, Inc.
 * Copyright (C) 2004 - 2006  Paul Mundt
 * Copyright (C) 2006  Nobuhiro Iwamatsu
 */
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश "pci-sh4.h"

#घोषणा IRQ_INTA	evt2irq(0xa20)
#घोषणा IRQ_INTB	evt2irq(0xa40)
#घोषणा IRQ_INTC	evt2irq(0xa60)
#घोषणा IRQ_INTD	evt2irq(0xa80)

/* IDSEL [16][17][18][19][20][21][22][23][24][25][26][27][28][29][30][31] */
अटल अक्षर sdk7780_irq_tab[4][16] = अणु
	/* INTA */
	अणु IRQ_INTA, IRQ_INTD, IRQ_INTC, IRQ_INTD, -1, -1, -1, -1, -1, -1,
	  -1, -1, -1, -1, -1, -1 पूर्ण,
	/* INTB */
	अणु IRQ_INTB, IRQ_INTA, -1, IRQ_INTA, -1, -1, -1, -1, -1, -1, -1, -1,
	  -1, -1, -1, -1 पूर्ण,
	/* INTC */
	अणु IRQ_INTC, IRQ_INTB, -1, IRQ_INTB, -1, -1, -1, -1, -1, -1, -1, -1,
	  -1, -1, -1, -1 पूर्ण,
	/* INTD */
	अणु IRQ_INTD, IRQ_INTC, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	  -1, -1, -1 पूर्ण,
पूर्ण;

पूर्णांक pcibios_map_platक्रमm_irq(स्थिर काष्ठा pci_dev *pdev, u8 slot, u8 pin)
अणु
       वापस sdk7780_irq_tab[pin-1][slot];
पूर्ण
