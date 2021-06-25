<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2008 Lemote Technology
 * Copyright (C) 2004 ICT CAS
 * Author: Li xiaoyu, lixy@ict.ac.cn
 *
 * Copyright (C) 2007 Lemote, Inc.
 * Author: Fuxin Zhang, zhangfx@lemote.com
 */
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#समावेश <loongson.h>
#समावेश <cs5536/cs5536.h>
#समावेश <cs5536/cs5536_pci.h>

/* PCI पूर्णांकerrupt pins
 *
 * These should not be changed, or you should consider loongson2f पूर्णांकerrupt
 * रेजिस्टर and your pci card dispatch
 */

#घोषणा PCIA		4
#घोषणा PCIB		5
#घोषणा PCIC		6
#घोषणा PCID		7

/* all the pci device has the PCIA pin, check the datasheet. */
अटल अक्षर irq_tab[][5] = अणु
	/*	INTA	INTB	INTC	INTD */
	अणु0, 0, 0, 0, 0पूर्ण,	/*  11: Unused */
	अणु0, 0, 0, 0, 0पूर्ण,	/*  12: Unused */
	अणु0, 0, 0, 0, 0पूर्ण,	/*  13: Unused */
	अणु0, 0, 0, 0, 0पूर्ण,	/*  14: Unused */
	अणु0, 0, 0, 0, 0पूर्ण,	/*  15: Unused */
	अणु0, 0, 0, 0, 0पूर्ण,	/*  16: Unused */
	अणु0, PCIA, 0, 0, 0पूर्ण,	/*  17: RTL8110-0 */
	अणु0, PCIB, 0, 0, 0पूर्ण,	/*  18: RTL8110-1 */
	अणु0, PCIC, 0, 0, 0पूर्ण,	/*  19: SiI3114 */
	अणु0, PCID, 0, 0, 0पूर्ण,	/*  20: 3-ports nec usb */
	अणु0, PCIA, PCIB, PCIC, PCIDपूर्ण,	/*  21: PCI-SLOT */
	अणु0, 0, 0, 0, 0पूर्ण,	/*  22: Unused */
	अणु0, 0, 0, 0, 0पूर्ण,	/*  23: Unused */
	अणु0, 0, 0, 0, 0पूर्ण,	/*  24: Unused */
	अणु0, 0, 0, 0, 0पूर्ण,	/*  25: Unused */
	अणु0, 0, 0, 0, 0पूर्ण,	/*  26: Unused */
	अणु0, 0, 0, 0, 0पूर्ण,	/*  27: Unused */
पूर्ण;

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक virq;

	अगर ((PCI_SLOT(dev->devfn) != PCI_IDSEL_CS5536)
	    && (PCI_SLOT(dev->devfn) < 32)) अणु
		virq = irq_tab[slot][pin];
		prपूर्णांकk(KERN_INFO "slot: %d, pin: %d, irq: %d\n", slot, pin,
		       virq + LOONGSON_IRQ_BASE);
		अगर (virq != 0)
			वापस LOONGSON_IRQ_BASE + virq;
		अन्यथा
			वापस 0;
	पूर्ण अन्यथा अगर (PCI_SLOT(dev->devfn) == PCI_IDSEL_CS5536) अणु	/*  cs5536 */
		चयन (PCI_FUNC(dev->devfn)) अणु
		हाल 2:
			pci_ग_लिखो_config_byte(dev, PCI_INTERRUPT_LINE,
					      CS5536_IDE_INTR);
			वापस CS5536_IDE_INTR; /*  क्रम IDE */
		हाल 3:
			pci_ग_लिखो_config_byte(dev, PCI_INTERRUPT_LINE,
					      CS5536_ACC_INTR);
			वापस CS5536_ACC_INTR; /*  क्रम AUDIO */
		हाल 4: /*  क्रम OHCI */
		हाल 5: /*  क्रम EHCI */
		हाल 6: /*  क्रम UDC */
		हाल 7: /*  क्रम OTG */
			pci_ग_लिखो_config_byte(dev, PCI_INTERRUPT_LINE,
					      CS5536_USB_INTR);
			वापस CS5536_USB_INTR;
		पूर्ण
		वापस dev->irq;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO " strange pci slot number.\n");
		वापस 0;
	पूर्ण
पूर्ण

/* Do platक्रमm specअगरic device initialization at pci_enable_device() समय */
पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण

/* CS5536 SPEC. fixup */
अटल व्योम loongson_cs5536_isa_fixup(काष्ठा pci_dev *pdev)
अणु
	/* the uart1 and uart2 पूर्णांकerrupt in PIC is enabled as शेष */
	pci_ग_लिखो_config_dword(pdev, PCI_UART1_INT_REG, 1);
	pci_ग_लिखो_config_dword(pdev, PCI_UART2_INT_REG, 1);
पूर्ण

अटल व्योम loongson_cs5536_ide_fixup(काष्ठा pci_dev *pdev)
अणु
	/* setting the mutex pin as IDE function */
	pci_ग_लिखो_config_dword(pdev, PCI_IDE_CFG_REG,
			       CS5536_IDE_FLASH_SIGNATURE);
पूर्ण

अटल व्योम loongson_cs5536_acc_fixup(काष्ठा pci_dev *pdev)
अणु
	/* enable the AUDIO पूर्णांकerrupt in PIC  */
	pci_ग_लिखो_config_dword(pdev, PCI_ACC_INT_REG, 1);

	pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 0xc0);
पूर्ण

अटल व्योम loongson_cs5536_ohci_fixup(काष्ठा pci_dev *pdev)
अणु
	/* enable the OHCI पूर्णांकerrupt in PIC */
	/* THE OHCI, EHCI, UDC, OTG are shared with पूर्णांकerrupt in PIC */
	pci_ग_लिखो_config_dword(pdev, PCI_OHCI_INT_REG, 1);
पूर्ण

अटल व्योम loongson_cs5536_ehci_fixup(काष्ठा pci_dev *pdev)
अणु
	u32 hi, lo;

	/* Serial लघु detect enable */
	_rdmsr(USB_MSR_REG(USB_CONFIG), &hi, &lo);
	_wrmsr(USB_MSR_REG(USB_CONFIG), (1 << 1) | (1 << 3), lo);

	/* setting the USB2.0 micro frame length */
	pci_ग_लिखो_config_dword(pdev, PCI_EHCI_FLADJ_REG, 0x2000);
पूर्ण

अटल व्योम loongson_nec_fixup(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित पूर्णांक val;

	pci_पढ़ो_config_dword(pdev, 0xe0, &val);
	/* Only 2 port be used */
	pci_ग_लिखो_config_dword(pdev, 0xe0, (val & ~3) | 0x2);
पूर्ण

DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_CS5536_ISA,
			 loongson_cs5536_isa_fixup);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_CS5536_OHC,
			 loongson_cs5536_ohci_fixup);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_CS5536_EHC,
			 loongson_cs5536_ehci_fixup);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_CS5536_AUDIO,
			 loongson_cs5536_acc_fixup);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_CS5536_IDE,
			 loongson_cs5536_ide_fixup);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NEC, PCI_DEVICE_ID_NEC_USB,
			 loongson_nec_fixup);
