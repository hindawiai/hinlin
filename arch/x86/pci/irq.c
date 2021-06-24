<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Low-Level PCI Support क्रम PC -- Routing of Interrupts
 *
 *	(c) 1999--2000 Martin Mares <mj@ucw.cz>
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dmi.h>
#समावेश <linux/पन.स>
#समावेश <linux/smp.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <linux/irq.h>
#समावेश <linux/acpi.h>
#समावेश <यंत्र/pci_x86.h>

#घोषणा PIRQ_SIGNATURE	(('$' << 0) + ('P' << 8) + ('I' << 16) + ('R' << 24))
#घोषणा PIRQ_VERSION 0x0100

अटल पूर्णांक broken_hp_bios_irq9;
अटल पूर्णांक acer_पंचांग360_irqrouting;

अटल काष्ठा irq_routing_table *pirq_table;

अटल पूर्णांक pirq_enable_irq(काष्ठा pci_dev *dev);
अटल व्योम pirq_disable_irq(काष्ठा pci_dev *dev);

/*
 * Never use: 0, 1, 2 (समयr, keyboard, and cascade)
 * Aव्योम using: 13, 14 and 15 (FP error and IDE).
 * Penalize: 3, 4, 6, 7, 12 (known ISA uses: serial, floppy, parallel and mouse)
 */
अचिन्हित पूर्णांक pcibios_irq_mask = 0xfff8;

अटल पूर्णांक pirq_penalty[16] = अणु
	1000000, 1000000, 1000000, 1000, 1000, 0, 1000, 1000,
	0, 0, 0, 0, 1000, 100000, 100000, 100000
पूर्ण;

काष्ठा irq_router अणु
	अक्षर *name;
	u16 venकरोr, device;
	पूर्णांक (*get)(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq);
	पूर्णांक (*set)(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq,
		पूर्णांक new);
पूर्ण;

काष्ठा irq_router_handler अणु
	u16 venकरोr;
	पूर्णांक (*probe)(काष्ठा irq_router *r, काष्ठा pci_dev *router, u16 device);
पूर्ण;

पूर्णांक (*pcibios_enable_irq)(काष्ठा pci_dev *dev) = pirq_enable_irq;
व्योम (*pcibios_disable_irq)(काष्ठा pci_dev *dev) = pirq_disable_irq;

/*
 *  Check passed address क्रम the PCI IRQ Routing Table signature
 *  and perक्रमm checksum verअगरication.
 */

अटल अंतरभूत काष्ठा irq_routing_table *pirq_check_routing_table(u8 *addr)
अणु
	काष्ठा irq_routing_table *rt;
	पूर्णांक i;
	u8 sum;

	rt = (काष्ठा irq_routing_table *) addr;
	अगर (rt->signature != PIRQ_SIGNATURE ||
	    rt->version != PIRQ_VERSION ||
	    rt->size % 16 ||
	    rt->size < माप(काष्ठा irq_routing_table))
		वापस शून्य;
	sum = 0;
	क्रम (i = 0; i < rt->size; i++)
		sum += addr[i];
	अगर (!sum) अणु
		DBG(KERN_DEBUG "PCI: Interrupt Routing Table found at 0x%p\n",
			rt);
		वापस rt;
	पूर्ण
	वापस शून्य;
पूर्ण



/*
 *  Search 0xf0000 -- 0xfffff क्रम the PCI IRQ Routing Table.
 */

अटल काष्ठा irq_routing_table * __init pirq_find_routing_table(व्योम)
अणु
	u8 *addr;
	काष्ठा irq_routing_table *rt;

	अगर (pirq_table_addr) अणु
		rt = pirq_check_routing_table((u8 *) __va(pirq_table_addr));
		अगर (rt)
			वापस rt;
		prपूर्णांकk(KERN_WARNING "PCI: PIRQ table NOT found at pirqaddr\n");
	पूर्ण
	क्रम (addr = (u8 *) __va(0xf0000); addr < (u8 *) __va(0x100000); addr += 16) अणु
		rt = pirq_check_routing_table(addr);
		अगर (rt)
			वापस rt;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 *  If we have a IRQ routing table, use it to search क्रम peer host
 *  bridges.  It's a gross hack, but since there are no other known
 *  ways how to get a list of buses, we have to go this way.
 */

अटल व्योम __init pirq_peer_trick(व्योम)
अणु
	काष्ठा irq_routing_table *rt = pirq_table;
	u8 busmap[256];
	पूर्णांक i;
	काष्ठा irq_info *e;

	स_रखो(busmap, 0, माप(busmap));
	क्रम (i = 0; i < (rt->size - माप(काष्ठा irq_routing_table)) / माप(काष्ठा irq_info); i++) अणु
		e = &rt->slots[i];
#अगर_घोषित DEBUG
		अणु
			पूर्णांक j;
			DBG(KERN_DEBUG "%02x:%02x slot=%02x", e->bus, e->devfn/8, e->slot);
			क्रम (j = 0; j < 4; j++)
				DBG(" %d:%02x/%04x", j, e->irq[j].link, e->irq[j].biपंचांगap);
			DBG("\n");
		पूर्ण
#पूर्ण_अगर
		busmap[e->bus] = 1;
	पूर्ण
	क्रम (i = 1; i < 256; i++) अणु
		अगर (!busmap[i] || pci_find_bus(0, i))
			जारी;
		pcibios_scan_root(i);
	पूर्ण
	pcibios_last_bus = -1;
पूर्ण

/*
 *  Code क्रम querying and setting of IRQ routes on various पूर्णांकerrupt routers.
 *  PIC Edge/Level Control Registers (ELCR) 0x4d0 & 0x4d1.
 */

व्योम elcr_set_level_irq(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित अक्षर mask = 1 << (irq & 7);
	अचिन्हित पूर्णांक port = 0x4d0 + (irq >> 3);
	अचिन्हित अक्षर val;
	अटल u16 elcr_irq_mask;

	अगर (irq >= 16 || (1 << irq) & elcr_irq_mask)
		वापस;

	elcr_irq_mask |= (1 << irq);
	prपूर्णांकk(KERN_DEBUG "PCI: setting IRQ %u as level-triggered\n", irq);
	val = inb(port);
	अगर (!(val & mask)) अणु
		DBG(KERN_DEBUG " -> edge");
		outb(val | mask, port);
	पूर्ण
पूर्ण

/*
 * Common IRQ routing practice: nibbles in config space,
 * offset by some magic स्थिरant.
 */
अटल अचिन्हित पूर्णांक पढ़ो_config_nybble(काष्ठा pci_dev *router, अचिन्हित offset, अचिन्हित nr)
अणु
	u8 x;
	अचिन्हित reg = offset + (nr >> 1);

	pci_पढ़ो_config_byte(router, reg, &x);
	वापस (nr & 1) ? (x >> 4) : (x & 0xf);
पूर्ण

अटल व्योम ग_लिखो_config_nybble(काष्ठा pci_dev *router, अचिन्हित offset,
	अचिन्हित nr, अचिन्हित पूर्णांक val)
अणु
	u8 x;
	अचिन्हित reg = offset + (nr >> 1);

	pci_पढ़ो_config_byte(router, reg, &x);
	x = (nr & 1) ? ((x & 0x0f) | (val << 4)) : ((x & 0xf0) | val);
	pci_ग_लिखो_config_byte(router, reg, x);
पूर्ण

/*
 * ALI pirq entries are damn ugly, and completely unकरोcumented.
 * This has been figured out from pirq tables, and it's not a pretty
 * picture.
 */
अटल पूर्णांक pirq_ali_get(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq)
अणु
	अटल स्थिर अचिन्हित अक्षर irqmap[16] = अणु 0, 9, 3, 10, 4, 5, 7, 6, 1, 11, 0, 12, 0, 14, 0, 15 पूर्ण;

	WARN_ON_ONCE(pirq > 16);
	वापस irqmap[पढ़ो_config_nybble(router, 0x48, pirq-1)];
पूर्ण

अटल पूर्णांक pirq_ali_set(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq, पूर्णांक irq)
अणु
	अटल स्थिर अचिन्हित अक्षर irqmap[16] = अणु 0, 8, 0, 2, 4, 5, 7, 6, 0, 1, 3, 9, 11, 0, 13, 15 पूर्ण;
	अचिन्हित पूर्णांक val = irqmap[irq];

	WARN_ON_ONCE(pirq > 16);
	अगर (val) अणु
		ग_लिखो_config_nybble(router, 0x48, pirq-1, val);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * The Intel PIIX4 pirq rules are fairly simple: "pirq" is
 * just a poपूर्णांकer to the config space.
 */
अटल पूर्णांक pirq_piix_get(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq)
अणु
	u8 x;

	pci_पढ़ो_config_byte(router, pirq, &x);
	वापस (x < 16) ? x : 0;
पूर्ण

अटल पूर्णांक pirq_piix_set(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq, पूर्णांक irq)
अणु
	pci_ग_लिखो_config_byte(router, pirq, irq);
	वापस 1;
पूर्ण

/*
 * The VIA pirq rules are nibble-based, like ALI,
 * but without the ugly irq number munging.
 * However, PIRQD is in the upper instead of lower 4 bits.
 */
अटल पूर्णांक pirq_via_get(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq)
अणु
	वापस पढ़ो_config_nybble(router, 0x55, pirq == 4 ? 5 : pirq);
पूर्ण

अटल पूर्णांक pirq_via_set(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq, पूर्णांक irq)
अणु
	ग_लिखो_config_nybble(router, 0x55, pirq == 4 ? 5 : pirq, irq);
	वापस 1;
पूर्ण

/*
 * The VIA pirq rules are nibble-based, like ALI,
 * but without the ugly irq number munging.
 * However, क्रम 82C586, nibble map is dअगरferent .
 */
अटल पूर्णांक pirq_via586_get(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq)
अणु
	अटल स्थिर अचिन्हित पूर्णांक pirqmap[5] = अणु 3, 2, 5, 1, 1 पूर्ण;

	WARN_ON_ONCE(pirq > 5);
	वापस पढ़ो_config_nybble(router, 0x55, pirqmap[pirq-1]);
पूर्ण

अटल पूर्णांक pirq_via586_set(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq, पूर्णांक irq)
अणु
	अटल स्थिर अचिन्हित पूर्णांक pirqmap[5] = अणु 3, 2, 5, 1, 1 पूर्ण;

	WARN_ON_ONCE(pirq > 5);
	ग_लिखो_config_nybble(router, 0x55, pirqmap[pirq-1], irq);
	वापस 1;
पूर्ण

/*
 * ITE 8330G pirq rules are nibble-based
 * FIXME: pirqmap may be अणु 1, 0, 3, 2 पूर्ण,
 * 	  2+3 are both mapped to irq 9 on my प्रणाली
 */
अटल पूर्णांक pirq_ite_get(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq)
अणु
	अटल स्थिर अचिन्हित अक्षर pirqmap[4] = अणु 1, 0, 2, 3 पूर्ण;

	WARN_ON_ONCE(pirq > 4);
	वापस पढ़ो_config_nybble(router, 0x43, pirqmap[pirq-1]);
पूर्ण

अटल पूर्णांक pirq_ite_set(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq, पूर्णांक irq)
अणु
	अटल स्थिर अचिन्हित अक्षर pirqmap[4] = अणु 1, 0, 2, 3 पूर्ण;

	WARN_ON_ONCE(pirq > 4);
	ग_लिखो_config_nybble(router, 0x43, pirqmap[pirq-1], irq);
	वापस 1;
पूर्ण

/*
 * OPTI: high four bits are nibble poपूर्णांकer..
 * I wonder what the low bits करो?
 */
अटल पूर्णांक pirq_opti_get(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq)
अणु
	वापस पढ़ो_config_nybble(router, 0xb8, pirq >> 4);
पूर्ण

अटल पूर्णांक pirq_opti_set(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq, पूर्णांक irq)
अणु
	ग_लिखो_config_nybble(router, 0xb8, pirq >> 4, irq);
	वापस 1;
पूर्ण

/*
 * Cyrix: nibble offset 0x5C
 * 0x5C bits 7:4 is INTB bits 3:0 is INTA
 * 0x5D bits 7:4 is INTD bits 3:0 is INTC
 */
अटल पूर्णांक pirq_cyrix_get(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq)
अणु
	वापस पढ़ो_config_nybble(router, 0x5C, (pirq-1)^1);
पूर्ण

अटल पूर्णांक pirq_cyrix_set(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq, पूर्णांक irq)
अणु
	ग_लिखो_config_nybble(router, 0x5C, (pirq-1)^1, irq);
	वापस 1;
पूर्ण

/*
 *	PIRQ routing क्रम SiS 85C503 router used in several SiS chipsets.
 *	We have to deal with the following issues here:
 *	- venकरोrs have dअगरferent ideas about the meaning of link values
 *	- some onboard devices (पूर्णांकegrated in the chipset) have special
 *	  links and are thus routed dअगरferently (i.e. not via PCI INTA-INTD)
 *	- dअगरferent revision of the router have a dअगरferent layout क्रम
 *	  the routing रेजिस्टरs, particularly क्रम the onchip devices
 *
 *	For all routing रेजिस्टरs the common thing is we have one byte
 *	per routeable link which is defined as:
 *		 bit 7      IRQ mapping enabled (0) or disabled (1)
 *		 bits [6:4] reserved (someबार used क्रम onchip devices)
 *		 bits [3:0] IRQ to map to
 *		     allowed: 3-7, 9-12, 14-15
 *		     reserved: 0, 1, 2, 8, 13
 *
 *	The config-space रेजिस्टरs located at 0x41/0x42/0x43/0x44 are
 *	always used to route the normal PCI INT A/B/C/D respectively.
 *	Apparently there are प्रणालीs implementing PCI routing table using
 *	link values 0x01-0x04 and others using 0x41-0x44 क्रम PCI INTA..D.
 *	We try our best to handle both link mappings.
 *
 *	Currently (2003-05-21) it appears most SiS chipsets follow the
 *	definition of routing रेजिस्टरs from the SiS-5595 southbridge.
 *	According to the SiS 5595 datasheets the revision id's of the
 *	router (ISA-bridge) should be 0x01 or 0xb0.
 *
 *	Furthermore we've also seen lspci dumps with revision 0x00 and 0xb1.
 *	Looks like these are used in a number of SiS 5xx/6xx/7xx chipsets.
 *	They seem to work with the current routing code. However there is
 *	some concern because of the two USB-OHCI HCs (original SiS 5595
 *	had only one). YMMV.
 *
 *	Onchip routing क्रम router rev-id 0x01/0xb0 and probably 0x00/0xb1:
 *
 *	0x61:	IDEIRQ:
 *		bits [6:5] must be written 01
 *		bit 4 channel-select primary (0), secondary (1)
 *
 *	0x62:	USBIRQ:
 *		bit 6 OHCI function disabled (0), enabled (1)
 *
 *	0x6a:	ACPI/SCI IRQ: bits 4-6 reserved
 *
 *	0x7e:	Data Acq. Module IRQ - bits 4-6 reserved
 *
 *	We support USBIRQ (in addition to INTA-INTD) and keep the
 *	IDE, ACPI and DAQ routing untouched as set by the BIOS.
 *
 *	Currently the only reported exception is the new SiS 65x chipset
 *	which includes the SiS 69x southbridge. Here we have the 85C503
 *	router revision 0x04 and there are changes in the रेजिस्टर layout
 *	mostly related to the dअगरferent USB HCs with USB 2.0 support.
 *
 *	Onchip routing क्रम router rev-id 0x04 (try-and-error observation)
 *
 *	0x60/0x61/0x62/0x63:	1xEHCI and 3xOHCI (companion) USB-HCs
 *				bit 6-4 are probably unused, not like 5595
 */

#घोषणा PIRQ_SIS_IRQ_MASK	0x0f
#घोषणा PIRQ_SIS_IRQ_DISABLE	0x80
#घोषणा PIRQ_SIS_USB_ENABLE	0x40

अटल पूर्णांक pirq_sis_get(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq)
अणु
	u8 x;
	पूर्णांक reg;

	reg = pirq;
	अगर (reg >= 0x01 && reg <= 0x04)
		reg += 0x40;
	pci_पढ़ो_config_byte(router, reg, &x);
	वापस (x & PIRQ_SIS_IRQ_DISABLE) ? 0 : (x & PIRQ_SIS_IRQ_MASK);
पूर्ण

अटल पूर्णांक pirq_sis_set(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq, पूर्णांक irq)
अणु
	u8 x;
	पूर्णांक reg;

	reg = pirq;
	अगर (reg >= 0x01 && reg <= 0x04)
		reg += 0x40;
	pci_पढ़ो_config_byte(router, reg, &x);
	x &= ~(PIRQ_SIS_IRQ_MASK | PIRQ_SIS_IRQ_DISABLE);
	x |= irq ? irq: PIRQ_SIS_IRQ_DISABLE;
	pci_ग_लिखो_config_byte(router, reg, x);
	वापस 1;
पूर्ण


/*
 * VLSI: nibble offset 0x74 - educated guess due to routing table and
 *       config space of VLSI 82C534 PCI-bridge/router (1004:0102)
 *       Tested on HP OmniBook 800 covering PIRQ 1, 2, 4, 8 क्रम onboard
 *       devices, PIRQ 3 क्रम non-pci(!) soundchip and (untested) PIRQ 6
 *       क्रम the busbridge to the करोcking station.
 */

अटल पूर्णांक pirq_vlsi_get(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq)
अणु
	WARN_ON_ONCE(pirq >= 9);
	अगर (pirq > 8) अणु
		dev_info(&dev->dev, "VLSI router PIRQ escape (%d)\n", pirq);
		वापस 0;
	पूर्ण
	वापस पढ़ो_config_nybble(router, 0x74, pirq-1);
पूर्ण

अटल पूर्णांक pirq_vlsi_set(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq, पूर्णांक irq)
अणु
	WARN_ON_ONCE(pirq >= 9);
	अगर (pirq > 8) अणु
		dev_info(&dev->dev, "VLSI router PIRQ escape (%d)\n", pirq);
		वापस 0;
	पूर्ण
	ग_लिखो_config_nybble(router, 0x74, pirq-1, irq);
	वापस 1;
पूर्ण

/*
 * ServerWorks: PCI पूर्णांकerrupts mapped to प्रणाली IRQ lines through Index
 * and Redirect I/O रेजिस्टरs (0x0c00 and 0x0c01).  The Index रेजिस्टर
 * क्रमmat is (PCIIRQ## | 0x10), e.g.: PCIIRQ10=0x1a.  The Redirect
 * रेजिस्टर is a straight binary coding of desired PIC IRQ (low nibble).
 *
 * The 'link' value in the PIRQ table is alपढ़ोy in the correct क्रमmat
 * क्रम the Index रेजिस्टर.  There are some special index values:
 * 0x00 क्रम ACPI (SCI), 0x01 क्रम USB, 0x02 क्रम IDE0, 0x04 क्रम IDE1,
 * and 0x03 क्रम SMBus.
 */
अटल पूर्णांक pirq_serverworks_get(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq)
अणु
	outb(pirq, 0xc00);
	वापस inb(0xc01) & 0xf;
पूर्ण

अटल पूर्णांक pirq_serverworks_set(काष्ठा pci_dev *router, काष्ठा pci_dev *dev,
	पूर्णांक pirq, पूर्णांक irq)
अणु
	outb(pirq, 0xc00);
	outb(irq, 0xc01);
	वापस 1;
पूर्ण

/* Support क्रम AMD756 PCI IRQ Routing
 * Jhon H. Caiceकरो <jhcaiced@osso.org.co>
 * Jun/21/2001 0.2.0 Release, fixed to use "nybble" functions... (jhcaiced)
 * Jun/19/2001 Alpha Release 0.1.0 (jhcaiced)
 * The AMD756 pirq rules are nibble-based
 * offset 0x56 0-3 PIRQA  4-7  PIRQB
 * offset 0x57 0-3 PIRQC  4-7  PIRQD
 */
अटल पूर्णांक pirq_amd756_get(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq)
अणु
	u8 irq;
	irq = 0;
	अगर (pirq <= 4)
		irq = पढ़ो_config_nybble(router, 0x56, pirq - 1);
	dev_info(&dev->dev,
		 "AMD756: dev [%04x:%04x], router PIRQ %d get IRQ %d\n",
		 dev->venकरोr, dev->device, pirq, irq);
	वापस irq;
पूर्ण

अटल पूर्णांक pirq_amd756_set(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq, पूर्णांक irq)
अणु
	dev_info(&dev->dev,
		 "AMD756: dev [%04x:%04x], router PIRQ %d set IRQ %d\n",
		 dev->venकरोr, dev->device, pirq, irq);
	अगर (pirq <= 4)
		ग_लिखो_config_nybble(router, 0x56, pirq - 1, irq);
	वापस 1;
पूर्ण

/*
 * PicoPower PT86C523
 */
अटल पूर्णांक pirq_pico_get(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq)
अणु
	outb(0x10 + ((pirq - 1) >> 1), 0x24);
	वापस ((pirq - 1) & 1) ? (inb(0x26) >> 4) : (inb(0x26) & 0xf);
पूर्ण

अटल पूर्णांक pirq_pico_set(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq,
			पूर्णांक irq)
अणु
	अचिन्हित पूर्णांक x;
	outb(0x10 + ((pirq - 1) >> 1), 0x24);
	x = inb(0x26);
	x = ((pirq - 1) & 1) ? ((x & 0x0f) | (irq << 4)) : ((x & 0xf0) | (irq));
	outb(x, 0x26);
	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_PCI_BIOS

अटल पूर्णांक pirq_bios_set(काष्ठा pci_dev *router, काष्ठा pci_dev *dev, पूर्णांक pirq, पूर्णांक irq)
अणु
	काष्ठा pci_dev *bridge;
	पूर्णांक pin = pci_get_पूर्णांकerrupt_pin(dev, &bridge);
	वापस pcibios_set_irq_routing(bridge, pin - 1, irq);
पूर्ण

#पूर्ण_अगर

अटल __init पूर्णांक पूर्णांकel_router_probe(काष्ठा irq_router *r, काष्ठा pci_dev *router, u16 device)
अणु
	अटल काष्ठा pci_device_id __initdata pirq_440gx[] = अणु
		अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82443GX_0) पूर्ण,
		अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82443GX_2) पूर्ण,
		अणु पूर्ण,
	पूर्ण;

	/* 440GX has a proprietary PIRQ router -- करोn't use it */
	अगर (pci_dev_present(pirq_440gx))
		वापस 0;

	चयन (device) अणु
	हाल PCI_DEVICE_ID_INTEL_82371FB_0:
	हाल PCI_DEVICE_ID_INTEL_82371SB_0:
	हाल PCI_DEVICE_ID_INTEL_82371AB_0:
	हाल PCI_DEVICE_ID_INTEL_82371MX:
	हाल PCI_DEVICE_ID_INTEL_82443MX_0:
	हाल PCI_DEVICE_ID_INTEL_82801AA_0:
	हाल PCI_DEVICE_ID_INTEL_82801AB_0:
	हाल PCI_DEVICE_ID_INTEL_82801BA_0:
	हाल PCI_DEVICE_ID_INTEL_82801BA_10:
	हाल PCI_DEVICE_ID_INTEL_82801CA_0:
	हाल PCI_DEVICE_ID_INTEL_82801CA_12:
	हाल PCI_DEVICE_ID_INTEL_82801DB_0:
	हाल PCI_DEVICE_ID_INTEL_82801E_0:
	हाल PCI_DEVICE_ID_INTEL_82801EB_0:
	हाल PCI_DEVICE_ID_INTEL_ESB_1:
	हाल PCI_DEVICE_ID_INTEL_ICH6_0:
	हाल PCI_DEVICE_ID_INTEL_ICH6_1:
	हाल PCI_DEVICE_ID_INTEL_ICH7_0:
	हाल PCI_DEVICE_ID_INTEL_ICH7_1:
	हाल PCI_DEVICE_ID_INTEL_ICH7_30:
	हाल PCI_DEVICE_ID_INTEL_ICH7_31:
	हाल PCI_DEVICE_ID_INTEL_TGP_LPC:
	हाल PCI_DEVICE_ID_INTEL_ESB2_0:
	हाल PCI_DEVICE_ID_INTEL_ICH8_0:
	हाल PCI_DEVICE_ID_INTEL_ICH8_1:
	हाल PCI_DEVICE_ID_INTEL_ICH8_2:
	हाल PCI_DEVICE_ID_INTEL_ICH8_3:
	हाल PCI_DEVICE_ID_INTEL_ICH8_4:
	हाल PCI_DEVICE_ID_INTEL_ICH9_0:
	हाल PCI_DEVICE_ID_INTEL_ICH9_1:
	हाल PCI_DEVICE_ID_INTEL_ICH9_2:
	हाल PCI_DEVICE_ID_INTEL_ICH9_3:
	हाल PCI_DEVICE_ID_INTEL_ICH9_4:
	हाल PCI_DEVICE_ID_INTEL_ICH9_5:
	हाल PCI_DEVICE_ID_INTEL_EP80579_0:
	हाल PCI_DEVICE_ID_INTEL_ICH10_0:
	हाल PCI_DEVICE_ID_INTEL_ICH10_1:
	हाल PCI_DEVICE_ID_INTEL_ICH10_2:
	हाल PCI_DEVICE_ID_INTEL_ICH10_3:
	हाल PCI_DEVICE_ID_INTEL_PATSBURG_LPC_0:
	हाल PCI_DEVICE_ID_INTEL_PATSBURG_LPC_1:
		r->name = "PIIX/ICH";
		r->get = pirq_piix_get;
		r->set = pirq_piix_set;
		वापस 1;
	पूर्ण

	अगर ((device >= PCI_DEVICE_ID_INTEL_5_3400_SERIES_LPC_MIN && 
	     device <= PCI_DEVICE_ID_INTEL_5_3400_SERIES_LPC_MAX) 
	||  (device >= PCI_DEVICE_ID_INTEL_COUGARPOINT_LPC_MIN && 
	     device <= PCI_DEVICE_ID_INTEL_COUGARPOINT_LPC_MAX)
	||  (device >= PCI_DEVICE_ID_INTEL_DH89XXCC_LPC_MIN &&
	     device <= PCI_DEVICE_ID_INTEL_DH89XXCC_LPC_MAX)
	||  (device >= PCI_DEVICE_ID_INTEL_PANTHERPOINT_LPC_MIN &&
	     device <= PCI_DEVICE_ID_INTEL_PANTHERPOINT_LPC_MAX)) अणु
		r->name = "PIIX/ICH";
		r->get = pirq_piix_get;
		r->set = pirq_piix_set;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल __init पूर्णांक via_router_probe(काष्ठा irq_router *r,
				काष्ठा pci_dev *router, u16 device)
अणु
	/* FIXME: We should move some of the quirk fixup stuff here */

	/*
	 * workarounds क्रम some buggy BIOSes
	 */
	अगर (device == PCI_DEVICE_ID_VIA_82C586_0) अणु
		चयन (router->device) अणु
		हाल PCI_DEVICE_ID_VIA_82C686:
			/*
			 * Asus k7m bios wrongly reports 82C686A
			 * as 586-compatible
			 */
			device = PCI_DEVICE_ID_VIA_82C686;
			अवरोध;
		हाल PCI_DEVICE_ID_VIA_8235:
			/**
			 * Asus a7v-x bios wrongly reports 8235
			 * as 586-compatible
			 */
			device = PCI_DEVICE_ID_VIA_8235;
			अवरोध;
		हाल PCI_DEVICE_ID_VIA_8237:
			/**
			 * Asus a7v600 bios wrongly reports 8237
			 * as 586-compatible
			 */
			device = PCI_DEVICE_ID_VIA_8237;
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (device) अणु
	हाल PCI_DEVICE_ID_VIA_82C586_0:
		r->name = "VIA";
		r->get = pirq_via586_get;
		r->set = pirq_via586_set;
		वापस 1;
	हाल PCI_DEVICE_ID_VIA_82C596:
	हाल PCI_DEVICE_ID_VIA_82C686:
	हाल PCI_DEVICE_ID_VIA_8231:
	हाल PCI_DEVICE_ID_VIA_8233A:
	हाल PCI_DEVICE_ID_VIA_8235:
	हाल PCI_DEVICE_ID_VIA_8237:
		/* FIXME: add new ones क्रम 8233/5 */
		r->name = "VIA";
		r->get = pirq_via_get;
		r->set = pirq_via_set;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल __init पूर्णांक vlsi_router_probe(काष्ठा irq_router *r, काष्ठा pci_dev *router, u16 device)
अणु
	चयन (device) अणु
	हाल PCI_DEVICE_ID_VLSI_82C534:
		r->name = "VLSI 82C534";
		r->get = pirq_vlsi_get;
		r->set = pirq_vlsi_set;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण


अटल __init पूर्णांक serverworks_router_probe(काष्ठा irq_router *r,
		काष्ठा pci_dev *router, u16 device)
अणु
	चयन (device) अणु
	हाल PCI_DEVICE_ID_SERVERWORKS_OSB4:
	हाल PCI_DEVICE_ID_SERVERWORKS_CSB5:
		r->name = "ServerWorks";
		r->get = pirq_serverworks_get;
		r->set = pirq_serverworks_set;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल __init पूर्णांक sis_router_probe(काष्ठा irq_router *r, काष्ठा pci_dev *router, u16 device)
अणु
	अगर (device != PCI_DEVICE_ID_SI_503)
		वापस 0;

	r->name = "SIS";
	r->get = pirq_sis_get;
	r->set = pirq_sis_set;
	वापस 1;
पूर्ण

अटल __init पूर्णांक cyrix_router_probe(काष्ठा irq_router *r, काष्ठा pci_dev *router, u16 device)
अणु
	चयन (device) अणु
	हाल PCI_DEVICE_ID_CYRIX_5520:
		r->name = "NatSemi";
		r->get = pirq_cyrix_get;
		r->set = pirq_cyrix_set;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल __init पूर्णांक opti_router_probe(काष्ठा irq_router *r, काष्ठा pci_dev *router, u16 device)
अणु
	चयन (device) अणु
	हाल PCI_DEVICE_ID_OPTI_82C700:
		r->name = "OPTI";
		r->get = pirq_opti_get;
		r->set = pirq_opti_set;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल __init पूर्णांक ite_router_probe(काष्ठा irq_router *r, काष्ठा pci_dev *router, u16 device)
अणु
	चयन (device) अणु
	हाल PCI_DEVICE_ID_ITE_IT8330G_0:
		r->name = "ITE";
		r->get = pirq_ite_get;
		r->set = pirq_ite_set;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल __init पूर्णांक ali_router_probe(काष्ठा irq_router *r, काष्ठा pci_dev *router, u16 device)
अणु
	चयन (device) अणु
	हाल PCI_DEVICE_ID_AL_M1533:
	हाल PCI_DEVICE_ID_AL_M1563:
		r->name = "ALI";
		r->get = pirq_ali_get;
		r->set = pirq_ali_set;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल __init पूर्णांक amd_router_probe(काष्ठा irq_router *r, काष्ठा pci_dev *router, u16 device)
अणु
	चयन (device) अणु
	हाल PCI_DEVICE_ID_AMD_VIPER_740B:
		r->name = "AMD756";
		अवरोध;
	हाल PCI_DEVICE_ID_AMD_VIPER_7413:
		r->name = "AMD766";
		अवरोध;
	हाल PCI_DEVICE_ID_AMD_VIPER_7443:
		r->name = "AMD768";
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	r->get = pirq_amd756_get;
	r->set = pirq_amd756_set;
	वापस 1;
पूर्ण

अटल __init पूर्णांक pico_router_probe(काष्ठा irq_router *r, काष्ठा pci_dev *router, u16 device)
अणु
	चयन (device) अणु
	हाल PCI_DEVICE_ID_PICOPOWER_PT86C523:
		r->name = "PicoPower PT86C523";
		r->get = pirq_pico_get;
		r->set = pirq_pico_set;
		वापस 1;

	हाल PCI_DEVICE_ID_PICOPOWER_PT86C523BBP:
		r->name = "PicoPower PT86C523 rev. BB+";
		r->get = pirq_pico_get;
		r->set = pirq_pico_set;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल __initdata काष्ठा irq_router_handler pirq_routers[] = अणु
	अणु PCI_VENDOR_ID_INTEL, पूर्णांकel_router_probe पूर्ण,
	अणु PCI_VENDOR_ID_AL, ali_router_probe पूर्ण,
	अणु PCI_VENDOR_ID_ITE, ite_router_probe पूर्ण,
	अणु PCI_VENDOR_ID_VIA, via_router_probe पूर्ण,
	अणु PCI_VENDOR_ID_OPTI, opti_router_probe पूर्ण,
	अणु PCI_VENDOR_ID_SI, sis_router_probe पूर्ण,
	अणु PCI_VENDOR_ID_CYRIX, cyrix_router_probe पूर्ण,
	अणु PCI_VENDOR_ID_VLSI, vlsi_router_probe पूर्ण,
	अणु PCI_VENDOR_ID_SERVERWORKS, serverworks_router_probe पूर्ण,
	अणु PCI_VENDOR_ID_AMD, amd_router_probe पूर्ण,
	अणु PCI_VENDOR_ID_PICOPOWER, pico_router_probe पूर्ण,
	/* Someone with करोcs needs to add the ATI Radeon IGP */
	अणु 0, शून्य पूर्ण
पूर्ण;
अटल काष्ठा irq_router pirq_router;
अटल काष्ठा pci_dev *pirq_router_dev;


/*
 *	FIXME: should we have an option to say "generic क्रम
 *	chipset" ?
 */

अटल व्योम __init pirq_find_router(काष्ठा irq_router *r)
अणु
	काष्ठा irq_routing_table *rt = pirq_table;
	काष्ठा irq_router_handler *h;

#अगर_घोषित CONFIG_PCI_BIOS
	अगर (!rt->signature) अणु
		prपूर्णांकk(KERN_INFO "PCI: Using BIOS for IRQ routing\n");
		r->set = pirq_bios_set;
		r->name = "BIOS";
		वापस;
	पूर्ण
#पूर्ण_अगर

	/* Default unless a driver reloads it */
	r->name = "default";
	r->get = शून्य;
	r->set = शून्य;

	DBG(KERN_DEBUG "PCI: Attempting to find IRQ router for [%04x:%04x]\n",
	    rt->rtr_venकरोr, rt->rtr_device);

	pirq_router_dev = pci_get_करोमुख्य_bus_and_slot(0, rt->rtr_bus,
						      rt->rtr_devfn);
	अगर (!pirq_router_dev) अणु
		DBG(KERN_DEBUG "PCI: Interrupt router not found at "
			"%02x:%02x\n", rt->rtr_bus, rt->rtr_devfn);
		वापस;
	पूर्ण

	क्रम (h = pirq_routers; h->venकरोr; h++) अणु
		/* First look क्रम a router match */
		अगर (rt->rtr_venकरोr == h->venकरोr &&
			h->probe(r, pirq_router_dev, rt->rtr_device))
			अवरोध;
		/* Fall back to a device match */
		अगर (pirq_router_dev->venकरोr == h->venकरोr &&
			h->probe(r, pirq_router_dev, pirq_router_dev->device))
			अवरोध;
	पूर्ण
	dev_info(&pirq_router_dev->dev, "%s IRQ router [%04x:%04x]\n",
		 pirq_router.name,
		 pirq_router_dev->venकरोr, pirq_router_dev->device);

	/* The device reमुख्यs referenced क्रम the kernel lअगरeसमय */
पूर्ण

अटल काष्ठा irq_info *pirq_get_info(काष्ठा pci_dev *dev)
अणु
	काष्ठा irq_routing_table *rt = pirq_table;
	पूर्णांक entries = (rt->size - माप(काष्ठा irq_routing_table)) /
		माप(काष्ठा irq_info);
	काष्ठा irq_info *info;

	क्रम (info = rt->slots; entries--; info++)
		अगर (info->bus == dev->bus->number &&
			PCI_SLOT(info->devfn) == PCI_SLOT(dev->devfn))
			वापस info;
	वापस शून्य;
पूर्ण

अटल पूर्णांक pcibios_lookup_irq(काष्ठा pci_dev *dev, पूर्णांक assign)
अणु
	u8 pin;
	काष्ठा irq_info *info;
	पूर्णांक i, pirq, newirq;
	पूर्णांक irq = 0;
	u32 mask;
	काष्ठा irq_router *r = &pirq_router;
	काष्ठा pci_dev *dev2 = शून्य;
	अक्षर *msg = शून्य;

	/* Find IRQ pin */
	pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_PIN, &pin);
	अगर (!pin) अणु
		dev_dbg(&dev->dev, "no interrupt pin\n");
		वापस 0;
	पूर्ण

	अगर (io_apic_assign_pci_irqs)
		वापस 0;

	/* Find IRQ routing entry */

	अगर (!pirq_table)
		वापस 0;

	info = pirq_get_info(dev);
	अगर (!info) अणु
		dev_dbg(&dev->dev, "PCI INT %c not found in routing table\n",
			'A' + pin - 1);
		वापस 0;
	पूर्ण
	pirq = info->irq[pin - 1].link;
	mask = info->irq[pin - 1].biपंचांगap;
	अगर (!pirq) अणु
		dev_dbg(&dev->dev, "PCI INT %c not routed\n", 'A' + pin - 1);
		वापस 0;
	पूर्ण
	dev_dbg(&dev->dev, "PCI INT %c -> PIRQ %02x, mask %04x, excl %04x",
		'A' + pin - 1, pirq, mask, pirq_table->exclusive_irqs);
	mask &= pcibios_irq_mask;

	/* Work around broken HP Pavilion Notebooks which assign USB to
	   IRQ 9 even though it is actually wired to IRQ 11 */

	अगर (broken_hp_bios_irq9 && pirq == 0x59 && dev->irq == 9) अणु
		dev->irq = 11;
		pci_ग_लिखो_config_byte(dev, PCI_INTERRUPT_LINE, 11);
		r->set(pirq_router_dev, dev, pirq, 11);
	पूर्ण

	/* same क्रम Acer Travelmate 360, but with CB and irq 11 -> 10 */
	अगर (acer_पंचांग360_irqrouting && dev->irq == 11 &&
		dev->venकरोr == PCI_VENDOR_ID_O2) अणु
		pirq = 0x68;
		mask = 0x400;
		dev->irq = r->get(pirq_router_dev, dev, pirq);
		pci_ग_लिखो_config_byte(dev, PCI_INTERRUPT_LINE, dev->irq);
	पूर्ण

	/*
	 * Find the best IRQ to assign: use the one
	 * reported by the device अगर possible.
	 */
	newirq = dev->irq;
	अगर (newirq && !((1 << newirq) & mask)) अणु
		अगर (pci_probe & PCI_USE_PIRQ_MASK)
			newirq = 0;
		अन्यथा
			dev_warn(&dev->dev, "IRQ %d doesn't match PIRQ mask "
				 "%#x; try pci=usepirqmask\n", newirq, mask);
	पूर्ण
	अगर (!newirq && assign) अणु
		क्रम (i = 0; i < 16; i++) अणु
			अगर (!(mask & (1 << i)))
				जारी;
			अगर (pirq_penalty[i] < pirq_penalty[newirq] &&
				can_request_irq(i, IRQF_SHARED))
				newirq = i;
		पूर्ण
	पूर्ण
	dev_dbg(&dev->dev, "PCI INT %c -> newirq %d", 'A' + pin - 1, newirq);

	/* Check अगर it is hardcoded */
	अगर ((pirq & 0xf0) == 0xf0) अणु
		irq = pirq & 0xf;
		msg = "hardcoded";
	पूर्ण अन्यथा अगर (r->get && (irq = r->get(pirq_router_dev, dev, pirq)) && \
	((!(pci_probe & PCI_USE_PIRQ_MASK)) || ((1 << irq) & mask))) अणु
		msg = "found";
		elcr_set_level_irq(irq);
	पूर्ण अन्यथा अगर (newirq && r->set &&
		(dev->class >> 8) != PCI_CLASS_DISPLAY_VGA) अणु
		अगर (r->set(pirq_router_dev, dev, pirq, newirq)) अणु
			elcr_set_level_irq(newirq);
			msg = "assigned";
			irq = newirq;
		पूर्ण
	पूर्ण

	अगर (!irq) अणु
		अगर (newirq && mask == (1 << newirq)) अणु
			msg = "guessed";
			irq = newirq;
		पूर्ण अन्यथा अणु
			dev_dbg(&dev->dev, "can't route interrupt\n");
			वापस 0;
		पूर्ण
	पूर्ण
	dev_info(&dev->dev, "%s PCI INT %c -> IRQ %d\n", msg, 'A' + pin - 1, irq);

	/* Update IRQ क्रम all devices with the same pirq value */
	क्रम_each_pci_dev(dev2) अणु
		pci_पढ़ो_config_byte(dev2, PCI_INTERRUPT_PIN, &pin);
		अगर (!pin)
			जारी;

		info = pirq_get_info(dev2);
		अगर (!info)
			जारी;
		अगर (info->irq[pin - 1].link == pirq) अणु
			/*
			 * We refuse to override the dev->irq
			 * inक्रमmation. Give a warning!
			 */
			अगर (dev2->irq && dev2->irq != irq && \
			(!(pci_probe & PCI_USE_PIRQ_MASK) || \
			((1 << dev2->irq) & mask))) अणु
#अगर_अघोषित CONFIG_PCI_MSI
				dev_info(&dev2->dev, "IRQ routing conflict: "
					 "have IRQ %d, want IRQ %d\n",
					 dev2->irq, irq);
#पूर्ण_अगर
				जारी;
			पूर्ण
			dev2->irq = irq;
			pirq_penalty[irq]++;
			अगर (dev != dev2)
				dev_info(&dev->dev, "sharing IRQ %d with %s\n",
					 irq, pci_name(dev2));
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

व्योम __init pcibios_fixup_irqs(व्योम)
अणु
	काष्ठा pci_dev *dev = शून्य;
	u8 pin;

	DBG(KERN_DEBUG "PCI: IRQ fixup\n");
	क्रम_each_pci_dev(dev) अणु
		/*
		 * If the BIOS has set an out of range IRQ number, just
		 * ignore it.  Also keep track of which IRQ's are
		 * alपढ़ोy in use.
		 */
		अगर (dev->irq >= 16) अणु
			dev_dbg(&dev->dev, "ignoring bogus IRQ %d\n", dev->irq);
			dev->irq = 0;
		पूर्ण
		/*
		 * If the IRQ is alपढ़ोy asचिन्हित to a PCI device,
		 * ignore its ISA use penalty
		 */
		अगर (pirq_penalty[dev->irq] >= 100 &&
				pirq_penalty[dev->irq] < 100000)
			pirq_penalty[dev->irq] = 0;
		pirq_penalty[dev->irq]++;
	पूर्ण

	अगर (io_apic_assign_pci_irqs)
		वापस;

	dev = शून्य;
	क्रम_each_pci_dev(dev) अणु
		pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_PIN, &pin);
		अगर (!pin)
			जारी;

		/*
		 * Still no IRQ? Try to lookup one...
		 */
		अगर (!dev->irq)
			pcibios_lookup_irq(dev, 0);
	पूर्ण
पूर्ण

/*
 * Work around broken HP Pavilion Notebooks which assign USB to
 * IRQ 9 even though it is actually wired to IRQ 11
 */
अटल पूर्णांक __init fix_broken_hp_bios_irq9(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (!broken_hp_bios_irq9) अणु
		broken_hp_bios_irq9 = 1;
		prपूर्णांकk(KERN_INFO "%s detected - fixing broken IRQ routing\n",
			d->ident);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Work around broken Acer TravelMate 360 Notebooks which assign
 * Cardbus to IRQ 11 even though it is actually wired to IRQ 10
 */
अटल पूर्णांक __init fix_acer_पंचांग360_irqrouting(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (!acer_पंचांग360_irqrouting) अणु
		acer_पंचांग360_irqrouting = 1;
		prपूर्णांकk(KERN_INFO "%s detected - fixing broken IRQ routing\n",
			d->ident);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id pciirq_dmi_table[] __initस्थिर = अणु
	अणु
		.callback = fix_broken_hp_bios_irq9,
		.ident = "HP Pavilion N5400 Series Laptop",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_BIOS_VERSION, "GE.M1.03"),
			DMI_MATCH(DMI_PRODUCT_VERSION,
				"HP Pavilion Notebook Model GE"),
			DMI_MATCH(DMI_BOARD_VERSION, "OmniBook N32N-736"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = fix_acer_पंचांग360_irqrouting,
		.ident = "Acer TravelMate 36x Laptop",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 360"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

व्योम __init pcibios_irq_init(व्योम)
अणु
	काष्ठा irq_routing_table *rtable = शून्य;

	DBG(KERN_DEBUG "PCI: IRQ init\n");

	अगर (raw_pci_ops == शून्य)
		वापस;

	dmi_check_प्रणाली(pciirq_dmi_table);

	pirq_table = pirq_find_routing_table();

#अगर_घोषित CONFIG_PCI_BIOS
	अगर (!pirq_table && (pci_probe & PCI_BIOS_IRQ_SCAN)) अणु
		pirq_table = pcibios_get_irq_routing_table();
		rtable = pirq_table;
	पूर्ण
#पूर्ण_अगर
	अगर (pirq_table) अणु
		pirq_peer_trick();
		pirq_find_router(&pirq_router);
		अगर (pirq_table->exclusive_irqs) अणु
			पूर्णांक i;
			क्रम (i = 0; i < 16; i++)
				अगर (!(pirq_table->exclusive_irqs & (1 << i)))
					pirq_penalty[i] += 100;
		पूर्ण
		/*
		 * If we're using the I/O APIC, aव्योम using the PCI IRQ
		 * routing table
		 */
		अगर (io_apic_assign_pci_irqs) अणु
			kमुक्त(rtable);
			pirq_table = शून्य;
		पूर्ण
	पूर्ण

	x86_init.pci.fixup_irqs();

	अगर (io_apic_assign_pci_irqs && pci_routeirq) अणु
		काष्ठा pci_dev *dev = शून्य;
		/*
		 * PCI IRQ routing is set up by pci_enable_device(), but we
		 * also करो it here in हाल there are still broken drivers that
		 * करोn't use pci_enable_device().
		 */
		prपूर्णांकk(KERN_INFO "PCI: Routing PCI interrupts for all devices because \"pci=routeirq\" specified\n");
		क्रम_each_pci_dev(dev)
			pirq_enable_irq(dev);
	पूर्ण
पूर्ण

अटल व्योम pirq_penalize_isa_irq(पूर्णांक irq, पूर्णांक active)
अणु
	/*
	 *  If any ISAPnP device reports an IRQ in its list of possible
	 *  IRQ's, we try to aव्योम assigning it to PCI devices.
	 */
	अगर (irq < 16) अणु
		अगर (active)
			pirq_penalty[irq] += 1000;
		अन्यथा
			pirq_penalty[irq] += 100;
	पूर्ण
पूर्ण

व्योम pcibios_penalize_isa_irq(पूर्णांक irq, पूर्णांक active)
अणु
#अगर_घोषित CONFIG_ACPI
	अगर (!acpi_noirq)
		acpi_penalize_isa_irq(irq, active);
	अन्यथा
#पूर्ण_अगर
		pirq_penalize_isa_irq(irq, active);
पूर्ण

अटल पूर्णांक pirq_enable_irq(काष्ठा pci_dev *dev)
अणु
	u8 pin = 0;

	pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_PIN, &pin);
	अगर (pin && !pcibios_lookup_irq(dev, 1)) अणु
		अक्षर *msg = "";

		अगर (!io_apic_assign_pci_irqs && dev->irq)
			वापस 0;

		अगर (io_apic_assign_pci_irqs) अणु
#अगर_घोषित CONFIG_X86_IO_APIC
			काष्ठा pci_dev *temp_dev;
			पूर्णांक irq;

			अगर (dev->irq_managed && dev->irq > 0)
				वापस 0;

			irq = IO_APIC_get_PCI_irq_vector(dev->bus->number,
						PCI_SLOT(dev->devfn), pin - 1);
			/*
			 * Busses behind bridges are typically not listed in the MP-table.
			 * In this हाल we have to look up the IRQ based on the parent bus,
			 * parent slot, and pin number. The SMP code detects such bridged
			 * busses itself so we should get पूर्णांकo this branch reliably.
			 */
			temp_dev = dev;
			जबतक (irq < 0 && dev->bus->parent) अणु /* go back to the bridge */
				काष्ठा pci_dev *bridge = dev->bus->self;

				pin = pci_swizzle_पूर्णांकerrupt_pin(dev, pin);
				irq = IO_APIC_get_PCI_irq_vector(bridge->bus->number,
						PCI_SLOT(bridge->devfn),
						pin - 1);
				अगर (irq >= 0)
					dev_warn(&dev->dev, "using bridge %s "
						 "INT %c to get IRQ %d\n",
						 pci_name(bridge), 'A' + pin - 1,
						 irq);
				dev = bridge;
			पूर्ण
			dev = temp_dev;
			अगर (irq >= 0) अणु
				dev->irq_managed = 1;
				dev->irq = irq;
				dev_info(&dev->dev, "PCI->APIC IRQ transform: "
					 "INT %c -> IRQ %d\n", 'A' + pin - 1, irq);
				वापस 0;
			पूर्ण अन्यथा
				msg = "; probably buggy MP table";
#पूर्ण_अगर
		पूर्ण अन्यथा अगर (pci_probe & PCI_BIOS_IRQ_SCAN)
			msg = "";
		अन्यथा
			msg = "; please try using pci=biosirq";

		/*
		 * With IDE legacy devices the IRQ lookup failure is not
		 * a problem..
		 */
		अगर (dev->class >> 8 == PCI_CLASS_STORAGE_IDE &&
				!(dev->class & 0x5))
			वापस 0;

		dev_warn(&dev->dev, "can't find IRQ for PCI INT %c%s\n",
			 'A' + pin - 1, msg);
	पूर्ण
	वापस 0;
पूर्ण

bool mp_should_keep_irq(काष्ठा device *dev)
अणु
	अगर (dev->घातer.is_prepared)
		वापस true;
#अगर_घोषित CONFIG_PM
	अगर (dev->घातer.runसमय_status == RPM_SUSPENDING)
		वापस true;
#पूर्ण_अगर

	वापस false;
पूर्ण

अटल व्योम pirq_disable_irq(काष्ठा pci_dev *dev)
अणु
	अगर (io_apic_assign_pci_irqs && !mp_should_keep_irq(&dev->dev) &&
	    dev->irq_managed && dev->irq) अणु
		mp_unmap_irq(dev->irq);
		dev->irq = 0;
		dev->irq_managed = 0;
	पूर्ण
पूर्ण
