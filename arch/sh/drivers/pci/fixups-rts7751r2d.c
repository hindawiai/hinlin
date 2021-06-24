<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/drivers/pci/fixups-rts7751r2d.c
 *
 * RTS7751R2D / LBOXRE2 PCI fixups
 *
 * Copyright (C) 2003  Lineo uSolutions, Inc.
 * Copyright (C) 2004  Paul Mundt
 * Copyright (C) 2007  Nobuhiro Iwamatsu
 */
#समावेश <linux/pci.h>
#समावेश <mach/lboxre2.h>
#समावेश <mach/r2d.h>
#समावेश "pci-sh4.h"
#समावेश <generated/machtypes.h>

#घोषणा PCIMCR_MRSET_OFF	0xBFFFFFFF
#घोषणा PCIMCR_RFSH_OFF		0xFFFFFFFB

अटल u8 rts7751r2d_irq_tab[] = अणु
	IRQ_PCI_INTA,
	IRQ_PCI_INTB,
	IRQ_PCI_INTC,
	IRQ_PCI_INTD,
पूर्ण;

अटल अक्षर lboxre2_irq_tab[] = अणु
	IRQ_ETH0, IRQ_ETH1, IRQ_INTA, IRQ_INTD,
पूर्ण;

पूर्णांक pcibios_map_platक्रमm_irq(स्थिर काष्ठा pci_dev *pdev, u8 slot, u8 pin)
अणु
	अगर (mach_is_lboxre2())
		वापस lboxre2_irq_tab[slot];
	अन्यथा
		वापस rts7751r2d_irq_tab[slot];
पूर्ण

पूर्णांक pci_fixup_pcic(काष्ठा pci_channel *chan)
अणु
	अचिन्हित दीर्घ bcr1, mcr;

	bcr1 = __raw_पढ़ोl(SH7751_BCR1);
	bcr1 |= 0x40080000;	/* Enable Bit 19 BREQEN, set PCIC to slave */
	pci_ग_लिखो_reg(chan, bcr1, SH4_PCIBCR1);

	/* Enable all पूर्णांकerrupts, so we known what to fix */
	pci_ग_लिखो_reg(chan, 0x0000c3ff, SH4_PCIINTM);
	pci_ग_लिखो_reg(chan, 0x0000380f, SH4_PCIAINTM);

	pci_ग_लिखो_reg(chan, 0xfb900047, SH7751_PCICONF1);
	pci_ग_लिखो_reg(chan, 0xab000001, SH7751_PCICONF4);

	mcr = __raw_पढ़ोl(SH7751_MCR);
	mcr = (mcr & PCIMCR_MRSET_OFF) & PCIMCR_RFSH_OFF;
	pci_ग_लिखो_reg(chan, mcr, SH4_PCIMCR);

	pci_ग_लिखो_reg(chan, 0x0c000000, SH7751_PCICONF5);
	pci_ग_लिखो_reg(chan, 0xd0000000, SH7751_PCICONF6);
	pci_ग_लिखो_reg(chan, 0x0c000000, SH4_PCILAR0);
	pci_ग_लिखो_reg(chan, 0x00000000, SH4_PCILAR1);

	वापस 0;
पूर्ण
