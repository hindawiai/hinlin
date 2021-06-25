<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2004 ICT CAS
 * Author: Li xiaoyu, ICT CAS
 *   lixy@ict.ac.cn
 *
 * Copyright (C) 2007 Lemote, Inc. & Institute of Computing Technology
 * Author: Fuxin Zhang, zhangfx@lemote.com
 */
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#समावेश <loongson.h>

/* South bridge slot number is set by the pci probe process */
अटल u8 sb_slot = 5;

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक irq = 0;

	अगर (slot == sb_slot) अणु
		चयन (PCI_FUNC(dev->devfn)) अणु
		हाल 2:
			irq = 10;
			अवरोध;
		हाल 3:
			irq = 11;
			अवरोध;
		हाल 5:
			irq = 9;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		irq = LOONGSON_IRQ_BASE + 25 + pin;
	पूर्ण
	वापस irq;

पूर्ण

/* Do platक्रमm specअगरic device initialization at pci_enable_device() समय */
पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण

अटल व्योम loongson2e_nec_fixup(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित पूर्णांक val;

	/* Configures port 1, 2, 3, 4 to be validate*/
	pci_पढ़ो_config_dword(pdev, 0xe0, &val);
	pci_ग_लिखो_config_dword(pdev, 0xe0, (val & ~7) | 0x4);

	/* System घड़ी is 48-MHz Oscillator. */
	pci_ग_लिखो_config_dword(pdev, 0xe4, 1 << 5);
पूर्ण

अटल व्योम loongson2e_686b_func0_fixup(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित अक्षर c;

	sb_slot = PCI_SLOT(pdev->devfn);

	prपूर्णांकk(KERN_INFO "via686b fix: ISA bridge\n");

	/*  Enable I/O Recovery समय */
	pci_ग_लिखो_config_byte(pdev, 0x40, 0x08);

	/*  Enable ISA refresh */
	pci_ग_लिखो_config_byte(pdev, 0x41, 0x01);

	/*  disable ISA line buffer */
	pci_ग_लिखो_config_byte(pdev, 0x45, 0x00);

	/*  Gate INTR, and flush line buffer */
	pci_ग_लिखो_config_byte(pdev, 0x46, 0xe0);

	/*  Disable PCI Delay Transaction, Enable EISA ports 4D0/4D1. */
	/* pci_ग_लिखो_config_byte(pdev, 0x47, 0x20); */

	/*
	 *  enable PCI Delay Transaction, Enable EISA ports 4D0/4D1.
	 *  enable समय-out समयr
	 */
	pci_ग_लिखो_config_byte(pdev, 0x47, 0xe6);

	/*
	 * enable level trigger on pci irqs: 9,10,11,13
	 * important! without this PCI पूर्णांकerrupts won't work
	 */
	outb(0x2e, 0x4d1);

	/*  512 K PCI Decode */
	pci_ग_लिखो_config_byte(pdev, 0x48, 0x01);

	/*  Wait क्रम PGNT beक्रमe grant to ISA Master/DMA */
	pci_ग_लिखो_config_byte(pdev, 0x4a, 0x84);

	/*
	 * Plug'n'Play
	 *
	 *  Parallel DRQ 3, Floppy DRQ 2 (शेष)
	 */
	pci_ग_लिखो_config_byte(pdev, 0x50, 0x0e);

	/*
	 * IRQ Routing क्रम Floppy and Parallel port
	 *
	 *  IRQ 6 क्रम floppy, IRQ 7 क्रम parallel port
	 */
	pci_ग_लिखो_config_byte(pdev, 0x51, 0x76);

	/* IRQ Routing क्रम serial ports (take IRQ 3 and 4) */
	pci_ग_लिखो_config_byte(pdev, 0x52, 0x34);

	/*  All IRQ's level triggered. */
	pci_ग_लिखो_config_byte(pdev, 0x54, 0x00);

	/* route PIRQA-D irq */
	pci_ग_लिखो_config_byte(pdev, 0x55, 0x90);	/* bit 7-4, PIRQA */
	pci_ग_लिखो_config_byte(pdev, 0x56, 0xba);	/* bit 7-4, PIRQC; */
							/* 3-0, PIRQB */
	pci_ग_लिखो_config_byte(pdev, 0x57, 0xd0);	/* bit 7-4, PIRQD */

	/* enable function 5/6, audio/modem */
	pci_पढ़ो_config_byte(pdev, 0x85, &c);
	c &= ~(0x3 << 2);
	pci_ग_लिखो_config_byte(pdev, 0x85, c);

	prपूर्णांकk(KERN_INFO"via686b fix: ISA bridge done\n");
पूर्ण

अटल व्योम loongson2e_686b_func1_fixup(काष्ठा pci_dev *pdev)
अणु
	prपूर्णांकk(KERN_INFO"via686b fix: IDE\n");

	/* Modअगरy IDE controller setup */
	pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 48);
	pci_ग_लिखो_config_byte(pdev, PCI_COMMAND,
			      PCI_COMMAND_IO | PCI_COMMAND_MEMORY |
			      PCI_COMMAND_MASTER);
	pci_ग_लिखो_config_byte(pdev, 0x40, 0x0b);
	/* legacy mode */
	pci_ग_लिखो_config_byte(pdev, 0x42, 0x09);

#अगर 1/* play safe, otherwise we may see notebook's usb keyboard lockup */
	/* disable पढ़ो prefetch/ग_लिखो post buffers */
	pci_ग_लिखो_config_byte(pdev, 0x41, 0x02);

	/* use 3/4 as fअगरo thresh hold	*/
	pci_ग_लिखो_config_byte(pdev, 0x43, 0x0a);
	pci_ग_लिखो_config_byte(pdev, 0x44, 0x00);

	pci_ग_लिखो_config_byte(pdev, 0x45, 0x00);
#अन्यथा
	pci_ग_लिखो_config_byte(pdev, 0x41, 0xc2);
	pci_ग_लिखो_config_byte(pdev, 0x43, 0x35);
	pci_ग_लिखो_config_byte(pdev, 0x44, 0x1c);

	pci_ग_लिखो_config_byte(pdev, 0x45, 0x10);
#पूर्ण_अगर

	prपूर्णांकk(KERN_INFO"via686b fix: IDE done\n");
पूर्ण

अटल व्योम loongson2e_686b_func2_fixup(काष्ठा pci_dev *pdev)
अणु
	/* irq routing */
	pci_ग_लिखो_config_byte(pdev, PCI_INTERRUPT_LINE, 10);
पूर्ण

अटल व्योम loongson2e_686b_func3_fixup(काष्ठा pci_dev *pdev)
अणु
	/* irq routing */
	pci_ग_लिखो_config_byte(pdev, PCI_INTERRUPT_LINE, 11);
पूर्ण

अटल व्योम loongson2e_686b_func5_fixup(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित अक्षर c;

	/* enable IO */
	pci_ग_लिखो_config_byte(pdev, PCI_COMMAND,
			      PCI_COMMAND_IO | PCI_COMMAND_MEMORY |
			      PCI_COMMAND_MASTER);
	pci_पढ़ो_config_dword(pdev, 0x4, &val);
	pci_ग_लिखो_config_dword(pdev, 0x4, val | 1);

	/* route ac97 IRQ */
	pci_ग_लिखो_config_byte(pdev, 0x3c, 9);

	pci_पढ़ो_config_byte(pdev, 0x8, &c);

	/* link control: enable link & SGD PCM output */
	pci_ग_लिखो_config_byte(pdev, 0x41, 0xcc);

	/* disable game port, FM, midi, sb, enable ग_लिखो to reg2c-2f */
	pci_ग_लिखो_config_byte(pdev, 0x42, 0x20);

	/* we are using Avance logic codec */
	pci_ग_लिखो_config_word(pdev, 0x2c, 0x1005);
	pci_ग_लिखो_config_word(pdev, 0x2e, 0x4710);
	pci_पढ़ो_config_dword(pdev, 0x2c, &val);

	pci_ग_लिखो_config_byte(pdev, 0x42, 0x0);
पूर्ण

DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_82C686,
			 loongson2e_686b_func0_fixup);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_82C586_1,
			 loongson2e_686b_func1_fixup);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_82C586_2,
			 loongson2e_686b_func2_fixup);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_82C586_3,
			 loongson2e_686b_func3_fixup);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_82C686_5,
			 loongson2e_686b_func5_fixup);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NEC, PCI_DEVICE_ID_NEC_USB,
			 loongson2e_nec_fixup);
