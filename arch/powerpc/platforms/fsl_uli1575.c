<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ULI M1575 setup code - specअगरic to Freescale boards
 *
 * Copyright 2007 Freescale Semiconductor Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mc146818rtc.h>

#समावेश <यंत्र/pci-bridge.h>

#घोषणा ULI_PIRQA	0x08
#घोषणा ULI_PIRQB	0x09
#घोषणा ULI_PIRQC	0x0a
#घोषणा ULI_PIRQD	0x0b
#घोषणा ULI_PIRQE	0x0c
#घोषणा ULI_PIRQF	0x0d
#घोषणा ULI_PIRQG	0x0e

#घोषणा ULI_8259_NONE	0x00
#घोषणा ULI_8259_IRQ1	0x08
#घोषणा ULI_8259_IRQ3	0x02
#घोषणा ULI_8259_IRQ4	0x04
#घोषणा ULI_8259_IRQ5	0x05
#घोषणा ULI_8259_IRQ6	0x07
#घोषणा ULI_8259_IRQ7	0x06
#घोषणा ULI_8259_IRQ9	0x01
#घोषणा ULI_8259_IRQ10	0x03
#घोषणा ULI_8259_IRQ11	0x09
#घोषणा ULI_8259_IRQ12	0x0b
#घोषणा ULI_8259_IRQ14	0x0d
#घोषणा ULI_8259_IRQ15	0x0f

u8 uli_pirq_to_irq[8] = अणु
	ULI_8259_IRQ9,		/* PIRQA */
	ULI_8259_IRQ10,		/* PIRQB */
	ULI_8259_IRQ11,		/* PIRQC */
	ULI_8259_IRQ12,		/* PIRQD */
	ULI_8259_IRQ5,		/* PIRQE */
	ULI_8259_IRQ6,		/* PIRQF */
	ULI_8259_IRQ7,		/* PIRQG */
	ULI_8259_NONE,		/* PIRQH */
पूर्ण;

अटल अंतरभूत bool is_quirk_valid(व्योम)
अणु
	वापस (machine_is(mpc86xx_hpcn) ||
		machine_is(mpc8544_ds) ||
		machine_is(p2020_ds) ||
		machine_is(mpc8572_ds));
पूर्ण

/* Bridge */
अटल व्योम early_uli5249(काष्ठा pci_dev *dev)
अणु
	अचिन्हित अक्षर temp;

	अगर (!is_quirk_valid())
		वापस;

	pci_ग_लिखो_config_word(dev, PCI_COMMAND, PCI_COMMAND_IO |
		 PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);

	/* पढ़ो/ग_लिखो lock */
	pci_पढ़ो_config_byte(dev, 0x7c, &temp);
	pci_ग_लिखो_config_byte(dev, 0x7c, 0x80);

	/* set as P2P bridge */
	pci_ग_लिखो_config_byte(dev, PCI_CLASS_PROG, 0x01);
	dev->class |= 0x1;

	/* restore lock */
	pci_ग_लिखो_config_byte(dev, 0x7c, temp);
पूर्ण


अटल व्योम quirk_uli1575(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;

	अगर (!is_quirk_valid())
		वापस;

	/*
	 * ULI1575 पूर्णांकerrupts route setup
	 */

	/* ULI1575 IRQ mapping conf रेजिस्टर maps PIRQx to IRQn */
	क्रम (i = 0; i < 4; i++) अणु
		u8 val = uli_pirq_to_irq[i*2] | (uli_pirq_to_irq[i*2+1] << 4);
		pci_ग_लिखो_config_byte(dev, 0x48 + i, val);
	पूर्ण

	/* USB 1.1 OHCI controller 1: dev 28, func 0 - IRQ12 */
	pci_ग_लिखो_config_byte(dev, 0x86, ULI_PIRQD);

	/* USB 1.1 OHCI controller 2: dev 28, func 1 - IRQ9 */
	pci_ग_लिखो_config_byte(dev, 0x87, ULI_PIRQA);

	/* USB 1.1 OHCI controller 3: dev 28, func 2 - IRQ10 */
	pci_ग_लिखो_config_byte(dev, 0x88, ULI_PIRQB);

	/* Lan controller: dev 27, func 0 - IRQ6 */
	pci_ग_लिखो_config_byte(dev, 0x89, ULI_PIRQF);

	/* AC97 Audio controller: dev 29, func 0 - IRQ6 */
	pci_ग_लिखो_config_byte(dev, 0x8a, ULI_PIRQF);

	/* Modem controller: dev 29, func 1 - IRQ6 */
	pci_ग_लिखो_config_byte(dev, 0x8b, ULI_PIRQF);

	/* HD Audio controller: dev 29, func 2 - IRQ6 */
	pci_ग_लिखो_config_byte(dev, 0x8c, ULI_PIRQF);

	/* SATA controller: dev 31, func 1 - IRQ5 */
	pci_ग_लिखो_config_byte(dev, 0x8d, ULI_PIRQE);

	/* SMB पूर्णांकerrupt: dev 30, func 1 - IRQ7 */
	pci_ग_लिखो_config_byte(dev, 0x8e, ULI_PIRQG);

	/* PMU ACPI SCI पूर्णांकerrupt: dev 30, func 2 - IRQ7 */
	pci_ग_लिखो_config_byte(dev, 0x8f, ULI_PIRQG);

	/* USB 2.0 controller: dev 28, func 3 */
	pci_ग_लिखो_config_byte(dev, 0x74, ULI_8259_IRQ11);

	/* Primary PATA IDE IRQ: 14
	 * Secondary PATA IDE IRQ: 15
	 */
	pci_ग_लिखो_config_byte(dev, 0x44, 0x30 | ULI_8259_IRQ14);
	pci_ग_लिखो_config_byte(dev, 0x75, ULI_8259_IRQ15);
पूर्ण

अटल व्योम quirk_final_uli1575(काष्ठा pci_dev *dev)
अणु
	/* Set i8259 पूर्णांकerrupt trigger
	 * IRQ 3:  Level
	 * IRQ 4:  Level
	 * IRQ 5:  Level
	 * IRQ 6:  Level
	 * IRQ 7:  Level
	 * IRQ 9:  Level
	 * IRQ 10: Level
	 * IRQ 11: Level
	 * IRQ 12: Level
	 * IRQ 14: Edge
	 * IRQ 15: Edge
	 */
	अगर (!is_quirk_valid())
		वापस;

	outb(0xfa, 0x4d0);
	outb(0x1e, 0x4d1);

	/* setup RTC */
	CMOS_WRITE(RTC_SET, RTC_CONTROL);
	CMOS_WRITE(RTC_24H, RTC_CONTROL);

	/* ensure month, date, and week alarm fields are ignored */
	CMOS_WRITE(0, RTC_VALID);

	outb_p(0x7c, 0x72);
	outb_p(RTC_ALARM_DONT_CARE, 0x73);

	outb_p(0x7d, 0x72);
	outb_p(RTC_ALARM_DONT_CARE, 0x73);
पूर्ण

/* SATA */
अटल व्योम quirk_uli5288(काष्ठा pci_dev *dev)
अणु
	अचिन्हित अक्षर c;
	अचिन्हित पूर्णांक d;

	अगर (!is_quirk_valid())
		वापस;

	/* पढ़ो/ग_लिखो lock */
	pci_पढ़ो_config_byte(dev, 0x83, &c);
	pci_ग_लिखो_config_byte(dev, 0x83, c|0x80);

	pci_पढ़ो_config_dword(dev, PCI_CLASS_REVISION, &d);
	d = (d & 0xff) | (PCI_CLASS_STORAGE_SATA_AHCI << 8);
	pci_ग_लिखो_config_dword(dev, PCI_CLASS_REVISION, d);

	/* restore lock */
	pci_ग_लिखो_config_byte(dev, 0x83, c);

	/* disable emulated PATA mode enabled */
	pci_पढ़ो_config_byte(dev, 0x84, &c);
	pci_ग_लिखो_config_byte(dev, 0x84, c & ~0x01);
पूर्ण

/* PATA */
अटल व्योम quirk_uli5229(काष्ठा pci_dev *dev)
अणु
	अचिन्हित लघु temp;

	अगर (!is_quirk_valid())
		वापस;

	pci_ग_लिखो_config_word(dev, PCI_COMMAND, PCI_COMMAND_INTX_DISABLE |
		PCI_COMMAND_MASTER | PCI_COMMAND_IO);

	/* Enable Native IRQ 14/15 */
	pci_पढ़ो_config_word(dev, 0x4a, &temp);
	pci_ग_लिखो_config_word(dev, 0x4a, temp | 0x1000);
पूर्ण

/* We have to करो a dummy पढ़ो on the P2P क्रम the RTC to work, WTF */
अटल व्योम quirk_final_uli5249(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;
	u8 *dummy;
	काष्ठा pci_bus *bus = dev->bus;
	काष्ठा resource *res;
	resource_माप_प्रकार end = 0;

	क्रम (i = PCI_BRIDGE_RESOURCES; i < PCI_BRIDGE_RESOURCES+3; i++) अणु
		अचिन्हित दीर्घ flags = pci_resource_flags(dev, i);
		अगर ((flags & (IORESOURCE_MEM|IORESOURCE_PREFETCH)) == IORESOURCE_MEM)
			end = pci_resource_end(dev, i);
	पूर्ण

	pci_bus_क्रम_each_resource(bus, res, i) अणु
		अगर (res && res->flags & IORESOURCE_MEM) अणु
			अगर (res->end == end)
				dummy = ioremap(res->start, 0x4);
			अन्यथा
				dummy = ioremap(res->end - 3, 0x4);
			अगर (dummy) अणु
				in_8(dummy);
				iounmap(dummy);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_AL, 0x5249, early_uli5249);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_AL, 0x1575, quirk_uli1575);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_AL, 0x5288, quirk_uli5288);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_AL, 0x5229, quirk_uli5229);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AL, 0x5249, quirk_final_uli5249);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AL, 0x1575, quirk_final_uli1575);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_AL, 0x5229, quirk_uli5229);

अटल व्योम hpcd_quirk_uli1575(काष्ठा pci_dev *dev)
अणु
	u32 temp32;

	अगर (!machine_is(mpc86xx_hpcd))
		वापस;

	/* Disable INTx */
	pci_पढ़ो_config_dword(dev, 0x48, &temp32);
	pci_ग_लिखो_config_dword(dev, 0x48, (temp32 | 1<<26));

	/* Enable sideband पूर्णांकerrupt */
	pci_पढ़ो_config_dword(dev, 0x90, &temp32);
	pci_ग_लिखो_config_dword(dev, 0x90, (temp32 | 1<<22));
पूर्ण

अटल व्योम hpcd_quirk_uli5288(काष्ठा pci_dev *dev)
अणु
	अचिन्हित अक्षर c;

	अगर (!machine_is(mpc86xx_hpcd))
		वापस;

	pci_पढ़ो_config_byte(dev, 0x83, &c);
	c |= 0x80;
	pci_ग_लिखो_config_byte(dev, 0x83, c);

	pci_ग_लिखो_config_byte(dev, PCI_CLASS_PROG, 0x01);
	pci_ग_लिखो_config_byte(dev, PCI_CLASS_DEVICE, 0x06);

	pci_पढ़ो_config_byte(dev, 0x83, &c);
	c &= 0x7f;
	pci_ग_लिखो_config_byte(dev, 0x83, c);
पूर्ण

/*
 * Since 8259PIC was disabled on the board, the IDE device can not
 * use the legacy IRQ, we need to let the IDE device work under
 * native mode and use the पूर्णांकerrupt line like other PCI devices.
 * IRQ14 is a sideband पूर्णांकerrupt from IDE device to CPU and we use this
 * as the पूर्णांकerrupt क्रम IDE device.
 */
अटल व्योम hpcd_quirk_uli5229(काष्ठा pci_dev *dev)
अणु
	अचिन्हित अक्षर c;

	अगर (!machine_is(mpc86xx_hpcd))
		वापस;

	pci_पढ़ो_config_byte(dev, 0x4b, &c);
	c |= 0x10;
	pci_ग_लिखो_config_byte(dev, 0x4b, c);
पूर्ण

/*
 * SATA पूर्णांकerrupt pin bug fix
 * There's a chip bug क्रम 5288, The पूर्णांकerrupt pin should be 2,
 * not the पढ़ो only value 1, So it use INTB#, not INTA# which
 * actually used by the IDE device 5229.
 * As of this bug, during the PCI initialization, 5288 पढ़ो the
 * irq of IDE device from the device tree, this function fix this
 * bug by re-assigning a correct irq to 5288.
 *
 */
अटल व्योम hpcd_final_uli5288(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(dev->bus);
	काष्ठा device_node *hosenode = hose ? hose->dn : शून्य;
	काष्ठा of_phandle_args oirq;
	u32 laddr[3];

	अगर (!machine_is(mpc86xx_hpcd))
		वापस;

	अगर (!hosenode)
		वापस;

	oirq.np = hosenode;
	oirq.args[0] = 2;
	oirq.args_count = 1;
	laddr[0] = (hose->first_busno << 16) | (PCI_DEVFN(31, 0) << 8);
	laddr[1] = laddr[2] = 0;
	of_irq_parse_raw(laddr, &oirq);
	dev->irq = irq_create_of_mapping(&oirq);
पूर्ण

DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_AL, 0x1575, hpcd_quirk_uli1575);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_AL, 0x5288, hpcd_quirk_uli5288);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_AL, 0x5229, hpcd_quirk_uli5229);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AL, 0x5288, hpcd_final_uli5288);

पूर्णांक uli_exclude_device(काष्ठा pci_controller *hose,
			u_अक्षर bus, u_अक्षर devfn)
अणु
	अगर (bus == (hose->first_busno + 2)) अणु
		/* exclude Modem controller */
		अगर ((PCI_SLOT(devfn) == 29) && (PCI_FUNC(devfn) == 1))
			वापस PCIBIOS_DEVICE_NOT_FOUND;

		/* exclude HD Audio controller */
		अगर ((PCI_SLOT(devfn) == 29) && (PCI_FUNC(devfn) == 2))
			वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण
