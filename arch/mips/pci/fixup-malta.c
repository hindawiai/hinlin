<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/mips-boards/piix4.h>

/* PCI पूर्णांकerrupt pins */
#घोषणा PCIA		1
#घोषणा PCIB		2
#घोषणा PCIC		3
#घोषणा PCID		4

/* This table is filled in by पूर्णांकerrogating the PIIX4 chip */
अटल अक्षर pci_irq[5] = अणु
पूर्ण;

अटल अक्षर irq_tab[][5] = अणु
	/*	INTA	INTB	INTC	INTD */
	अणु0,	0,	0,	0,	0 पूर्ण,	/*  0: GT64120 PCI bridge */
	अणु0,	0,	0,	0,	0 पूर्ण,	/*  1: Unused */
	अणु0,	0,	0,	0,	0 पूर्ण,	/*  2: Unused */
	अणु0,	0,	0,	0,	0 पूर्ण,	/*  3: Unused */
	अणु0,	0,	0,	0,	0 पूर्ण,	/*  4: Unused */
	अणु0,	0,	0,	0,	0 पूर्ण,	/*  5: Unused */
	अणु0,	0,	0,	0,	0 पूर्ण,	/*  6: Unused */
	अणु0,	0,	0,	0,	0 पूर्ण,	/*  7: Unused */
	अणु0,	0,	0,	0,	0 पूर्ण,	/*  8: Unused */
	अणु0,	0,	0,	0,	0 पूर्ण,	/*  9: Unused */
	अणु0,	0,	0,	0,	PCID पूर्ण, /* 10: PIIX4 USB */
	अणु0,	PCIB,	0,	0,	0 पूर्ण,	/* 11: AMD 79C973 Ethernet */
	अणु0,	PCIC,	0,	0,	0 पूर्ण,	/* 12: Crystal 4281 Sound */
	अणु0,	0,	0,	0,	0 पूर्ण,	/* 13: Unused */
	अणु0,	0,	0,	0,	0 पूर्ण,	/* 14: Unused */
	अणु0,	0,	0,	0,	0 पूर्ण,	/* 15: Unused */
	अणु0,	0,	0,	0,	0 पूर्ण,	/* 16: Unused */
	अणु0,	0,	0,	0,	0 पूर्ण,	/* 17: Bonito/SOC-it PCI Bridge*/
	अणु0,	PCIA,	PCIB,	PCIC,	PCID पूर्ण, /* 18: PCI Slot 1 */
	अणु0,	PCIB,	PCIC,	PCID,	PCIA पूर्ण, /* 19: PCI Slot 2 */
	अणु0,	PCIC,	PCID,	PCIA,	PCIB पूर्ण, /* 20: PCI Slot 3 */
	अणु0,	PCID,	PCIA,	PCIB,	PCIC पूर्ण	/* 21: PCI Slot 4 */
पूर्ण;

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक virq;
	virq = irq_tab[slot][pin];
	वापस pci_irq[virq];
पूर्ण

/* Do platक्रमm specअगरic device initialization at pci_enable_device() समय */
पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण

अटल व्योम malta_piix_func3_base_fixup(काष्ठा pci_dev *dev)
अणु
	/* Set a sane PM I/O base address */
	pci_ग_लिखो_config_word(dev, PIIX4_FUNC3_PMBA, 0x1000);

	/* Enable access to the PM I/O region */
	pci_ग_लिखो_config_byte(dev, PIIX4_FUNC3_PMREGMISC,
			      PIIX4_FUNC3_PMREGMISC_EN);
पूर्ण

DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82371AB_3,
			malta_piix_func3_base_fixup);

अटल व्योम malta_piix_func0_fixup(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित अक्षर reg_val;
	u32 reg_val32;
	u16 reg_val16;
	/* PIIX PIRQC[A:D] irq mappings */
	अटल पूर्णांक piixirqmap[PIIX4_FUNC0_PIRQRC_IRQ_ROUTING_MAX] = अणु
		0,  0,	0,  3,
		4,  5,	6,  7,
		0,  9, 10, 11,
		12, 0, 14, 15
	पूर्ण;
	पूर्णांक i;

	/* Interrogate PIIX4 to get PCI IRQ mapping */
	क्रम (i = 0; i <= 3; i++) अणु
		pci_पढ़ो_config_byte(pdev, PIIX4_FUNC0_PIRQRC+i, &reg_val);
		अगर (reg_val & PIIX4_FUNC0_PIRQRC_IRQ_ROUTING_DISABLE)
			pci_irq[PCIA+i] = 0;	/* Disabled */
		अन्यथा
			pci_irq[PCIA+i] = piixirqmap[reg_val &
				PIIX4_FUNC0_PIRQRC_IRQ_ROUTING_MASK];
	पूर्ण

	/* Done by YAMON 2.00 onwards */
	अगर (PCI_SLOT(pdev->devfn) == 10) अणु
		/*
		 * Set top of मुख्य memory accessible by ISA or DMA
		 * devices to 16 Mb.
		 */
		pci_पढ़ो_config_byte(pdev, PIIX4_FUNC0_TOM, &reg_val);
		pci_ग_लिखो_config_byte(pdev, PIIX4_FUNC0_TOM, reg_val |
				PIIX4_FUNC0_TOM_TOP_OF_MEMORY_MASK);
	पूर्ण

	/* Mux SERIRQ to its pin */
	pci_पढ़ो_config_dword(pdev, PIIX4_FUNC0_GENCFG, &reg_val32);
	pci_ग_लिखो_config_dword(pdev, PIIX4_FUNC0_GENCFG,
			       reg_val32 | PIIX4_FUNC0_GENCFG_SERIRQ);

	/* Enable SERIRQ */
	pci_पढ़ो_config_byte(pdev, PIIX4_FUNC0_SERIRQC, &reg_val);
	reg_val |= PIIX4_FUNC0_SERIRQC_EN | PIIX4_FUNC0_SERIRQC_CONT;
	pci_ग_लिखो_config_byte(pdev, PIIX4_FUNC0_SERIRQC, reg_val);

	/* Enable response to special cycles */
	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &reg_val16);
	pci_ग_लिखो_config_word(pdev, PCI_COMMAND,
			      reg_val16 | PCI_COMMAND_SPECIAL);
पूर्ण

DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82371AB_0,
	 malta_piix_func0_fixup);

अटल व्योम malta_piix_func1_fixup(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित अक्षर reg_val;

	/* Done by YAMON 2.02 onwards */
	अगर (PCI_SLOT(pdev->devfn) == 10) अणु
		/*
		 * IDE Decode enable.
		 */
		pci_पढ़ो_config_byte(pdev, PIIX4_FUNC1_IDETIM_PRIMARY_HI,
			&reg_val);
		pci_ग_लिखो_config_byte(pdev, PIIX4_FUNC1_IDETIM_PRIMARY_HI,
			reg_val|PIIX4_FUNC1_IDETIM_PRIMARY_HI_IDE_DECODE_EN);
		pci_पढ़ो_config_byte(pdev, PIIX4_FUNC1_IDETIM_SECONDARY_HI,
			&reg_val);
		pci_ग_लिखो_config_byte(pdev, PIIX4_FUNC1_IDETIM_SECONDARY_HI,
			reg_val|PIIX4_FUNC1_IDETIM_SECONDARY_HI_IDE_DECODE_EN);
	पूर्ण
पूर्ण

DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82371AB,
	 malta_piix_func1_fixup);

/* Enable PCI 2.1 compatibility in PIIX4 */
अटल व्योम quirk_dlcsetup(काष्ठा pci_dev *dev)
अणु
	u8 odlc, ndlc;

	(व्योम) pci_पढ़ो_config_byte(dev, PIIX4_FUNC0_DLC, &odlc);
	/* Enable passive releases and delayed transaction */
	ndlc = odlc | PIIX4_FUNC0_DLC_USBPR_EN |
		      PIIX4_FUNC0_DLC_PASSIVE_RELEASE_EN |
		      PIIX4_FUNC0_DLC_DELAYED_TRANSACTION_EN;
	(व्योम) pci_ग_लिखो_config_byte(dev, PIIX4_FUNC0_DLC, ndlc);
पूर्ण

DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82371AB_0,
	quirk_dlcsetup);
