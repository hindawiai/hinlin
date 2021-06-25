<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/drivers/pci/fixups-landisk.c
 *
 * PCI initialization क्रम the I-O DATA Device, Inc. LANDISK board
 *
 * Copyright (C) 2006 kogiidena
 * Copyright (C) 2010 Nobuhiro Iwamatsu
 */
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश "pci-sh4.h"

#घोषणा PCIMCR_MRSET_OFF	0xBFFFFFFF
#घोषणा PCIMCR_RFSH_OFF		0xFFFFFFFB

पूर्णांक pcibios_map_platक्रमm_irq(स्थिर काष्ठा pci_dev *pdev, u8 slot, u8 pin)
अणु
	/*
	 * slot0: pin1-4 = irq5,6,7,8
	 * slot1: pin1-4 = irq6,7,8,5
	 * slot2: pin1-4 = irq7,8,5,6
	 * slot3: pin1-4 = irq8,5,6,7
	 */
	पूर्णांक irq = ((slot + pin - 1) & 0x3) + evt2irq(0x2a0);

	अगर ((slot | (pin - 1)) > 0x3) अणु
		prपूर्णांकk(KERN_WARNING "PCI: Bad IRQ mapping request for slot %d pin %c\n",
		       slot, pin - 1 + 'A');
		वापस -1;
	पूर्ण
	वापस irq;
पूर्ण

पूर्णांक pci_fixup_pcic(काष्ठा pci_channel *chan)
अणु
	अचिन्हित दीर्घ bcr1, mcr;

	bcr1 = __raw_पढ़ोl(SH7751_BCR1);
	bcr1 |= 0x40080000;	/* Enable Bit 19 BREQEN, set PCIC to slave */
	pci_ग_लिखो_reg(chan, bcr1, SH4_PCIBCR1);

	mcr = __raw_पढ़ोl(SH7751_MCR);
	mcr = (mcr & PCIMCR_MRSET_OFF) & PCIMCR_RFSH_OFF;
	pci_ग_लिखो_reg(chan, mcr, SH4_PCIMCR);

	pci_ग_लिखो_reg(chan, 0x0c000000, SH7751_PCICONF5);
	pci_ग_लिखो_reg(chan, 0xd0000000, SH7751_PCICONF6);
	pci_ग_लिखो_reg(chan, 0x0c000000, SH4_PCILAR0);
	pci_ग_लिखो_reg(chan, 0x00000000, SH4_PCILAR1);

	वापस 0;
पूर्ण
