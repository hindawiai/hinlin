<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  pci_irq.c - ACPI PCI Interrupt Routing ($Revision: 11 $)
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 *  Copyright (C) 2002       Dominik Broकरोwski <devel@broकरो.de>
 *  (c) Copyright 2008 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */

#घोषणा pr_fmt(fmt) "ACPI: PCI: " fmt

#समावेश <linux/dmi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pm.h>
#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>

काष्ठा acpi_prt_entry अणु
	काष्ठा acpi_pci_id	id;
	u8			pin;
	acpi_handle		link;
	u32			index;		/* GSI, or link _CRS index */
पूर्ण;

अटल अंतरभूत अक्षर pin_name(पूर्णांक pin)
अणु
	वापस 'A' + pin - 1;
पूर्ण

/* --------------------------------------------------------------------------
                         PCI IRQ Routing Table (PRT) Support
   -------------------------------------------------------------------------- */

/* http://bugzilla.kernel.org/show_bug.cgi?id=4773 */
अटल स्थिर काष्ठा dmi_प्रणाली_id medion_md9580[] = अणु
	अणु
		.ident = "Medion MD9580-F laptop",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MEDIONNB"),
			DMI_MATCH(DMI_PRODUCT_NAME, "A555"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/* http://bugzilla.kernel.org/show_bug.cgi?id=5044 */
अटल स्थिर काष्ठा dmi_प्रणाली_id dell_optiplex[] = अणु
	अणु
		.ident = "Dell Optiplex GX1",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Computer Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "OptiPlex GX1 600S+"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/* http://bugzilla.kernel.org/show_bug.cgi?id=10138 */
अटल स्थिर काष्ठा dmi_प्रणाली_id hp_t5710[] = अणु
	अणु
		.ident = "HP t5710",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "hp t5000 series"),
			DMI_MATCH(DMI_BOARD_NAME, "098Ch"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

काष्ठा prt_quirk अणु
	स्थिर काष्ठा dmi_प्रणाली_id *प्रणाली;
	अचिन्हित पूर्णांक		segment;
	अचिन्हित पूर्णांक		bus;
	अचिन्हित पूर्णांक		device;
	अचिन्हित अक्षर		pin;
	स्थिर अक्षर		*source;	/* according to BIOS */
	स्थिर अक्षर		*actual_source;
पूर्ण;

#घोषणा PCI_INTX_PIN(c)		(c - 'A' + 1)

/*
 * These प्रणालीs have incorrect _PRT entries.  The BIOS claims the PCI
 * पूर्णांकerrupt at the listed segment/bus/device/pin is connected to the first
 * link device, but it is actually connected to the second.
 */
अटल स्थिर काष्ठा prt_quirk prt_quirks[] = अणु
	अणु medion_md9580, 0, 0, 9, PCI_INTX_PIN('A'),
		"\\_SB_.PCI0.ISA_.LNKA",
		"\\_SB_.PCI0.ISA_.LNKB"पूर्ण,
	अणु dell_optiplex, 0, 0, 0xd, PCI_INTX_PIN('A'),
		"\\_SB_.LNKB",
		"\\_SB_.LNKA"पूर्ण,
	अणु hp_t5710, 0, 0, 1, PCI_INTX_PIN('A'),
		"\\_SB_.PCI0.LNK1",
		"\\_SB_.PCI0.LNK3"पूर्ण,
पूर्ण;

अटल व्योम करो_prt_fixups(काष्ठा acpi_prt_entry *entry,
			  काष्ठा acpi_pci_routing_table *prt)
अणु
	पूर्णांक i;
	स्थिर काष्ठा prt_quirk *quirk;

	क्रम (i = 0; i < ARRAY_SIZE(prt_quirks); i++) अणु
		quirk = &prt_quirks[i];

		/* All current quirks involve link devices, not GSIs */
		अगर (dmi_check_प्रणाली(quirk->प्रणाली) &&
		    entry->id.segment == quirk->segment &&
		    entry->id.bus == quirk->bus &&
		    entry->id.device == quirk->device &&
		    entry->pin == quirk->pin &&
		    !म_भेद(prt->source, quirk->source) &&
		    म_माप(prt->source) >= म_माप(quirk->actual_source)) अणु
			pr_warn("Firmware reports "
				"%04x:%02x:%02x PCI INT %c connected to %s; "
				"changing to %s\n",
				entry->id.segment, entry->id.bus,
				entry->id.device, pin_name(entry->pin),
				prt->source, quirk->actual_source);
			म_नकल(prt->source, quirk->actual_source);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_pci_irq_check_entry(acpi_handle handle, काष्ठा pci_dev *dev,
				  पूर्णांक pin, काष्ठा acpi_pci_routing_table *prt,
				  काष्ठा acpi_prt_entry **entry_ptr)
अणु
	पूर्णांक segment = pci_करोमुख्य_nr(dev->bus);
	पूर्णांक bus = dev->bus->number;
	पूर्णांक device = pci_ari_enabled(dev->bus) ? 0 : PCI_SLOT(dev->devfn);
	काष्ठा acpi_prt_entry *entry;

	अगर (((prt->address >> 16) & 0xffff) != device ||
	    prt->pin + 1 != pin)
		वापस -ENODEV;

	entry = kzalloc(माप(काष्ठा acpi_prt_entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	/*
	 * Note that the _PRT uses 0=INTA, 1=INTB, etc, जबतक PCI uses
	 * 1=INTA, 2=INTB.  We use the PCI encoding throughout, so convert
	 * it here.
	 */
	entry->id.segment = segment;
	entry->id.bus = bus;
	entry->id.device = (prt->address >> 16) & 0xFFFF;
	entry->pin = prt->pin + 1;

	करो_prt_fixups(entry, prt);

	entry->index = prt->source_index;

	/*
	 * Type 1: Dynamic
	 * ---------------
	 * The 'source' field specअगरies the PCI पूर्णांकerrupt link device used to
	 * configure the IRQ asचिन्हित to this slot|dev|pin.  The 'source_index'
	 * indicates which resource descriptor in the resource ढाँचा (of
	 * the link device) this पूर्णांकerrupt is allocated from.
	 *
	 * NOTE: Don't query the Link Device क्रम IRQ inक्रमmation at this समय
	 *       because Link Device क्रमागतeration may not have occurred yet
	 *       (e.g. exists somewhere 'below' this _PRT entry in the ACPI
	 *       namespace).
	 */
	अगर (prt->source[0])
		acpi_get_handle(handle, prt->source, &entry->link);

	/*
	 * Type 2: Static
	 * --------------
	 * The 'source' field is NULL, and the 'source_index' field specअगरies
	 * the IRQ value, which is hardwired to specअगरic पूर्णांकerrupt inमाला_दो on
	 * the पूर्णांकerrupt controller.
	 */
	pr_debug("%04x:%02x:%02x[%c] -> %s[%d]\n",
		 entry->id.segment, entry->id.bus, entry->id.device,
		 pin_name(entry->pin), prt->source, entry->index);

	*entry_ptr = entry;

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_pci_irq_find_prt_entry(काष्ठा pci_dev *dev,
			  पूर्णांक pin, काष्ठा acpi_prt_entry **entry_ptr)
अणु
	acpi_status status;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_pci_routing_table *entry;
	acpi_handle handle = शून्य;

	अगर (dev->bus->bridge)
		handle = ACPI_HANDLE(dev->bus->bridge);

	अगर (!handle)
		वापस -ENODEV;

	/* 'handle' is the _PRT's parent (root bridge or PCI-PCI bridge) */
	status = acpi_get_irq_routing_table(handle, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		kमुक्त(buffer.poपूर्णांकer);
		वापस -ENODEV;
	पूर्ण

	entry = buffer.poपूर्णांकer;
	जबतक (entry && (entry->length > 0)) अणु
		अगर (!acpi_pci_irq_check_entry(handle, dev, pin,
						 entry, entry_ptr))
			अवरोध;
		entry = (काष्ठा acpi_pci_routing_table *)
		    ((अचिन्हित दीर्घ)entry + entry->length);
	पूर्ण

	kमुक्त(buffer.poपूर्णांकer);
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------------
                          PCI Interrupt Routing Support
   -------------------------------------------------------------------------- */
#अगर_घोषित CONFIG_X86_IO_APIC
बाह्य पूर्णांक noioapicquirk;
बाह्य पूर्णांक noioapicreroute;

अटल पूर्णांक bridge_has_boot_पूर्णांकerrupt_variant(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_bus *bus_it;

	क्रम (bus_it = bus ; bus_it ; bus_it = bus_it->parent) अणु
		अगर (!bus_it->self)
			वापस 0;
		अगर (bus_it->self->irq_reroute_variant)
			वापस bus_it->self->irq_reroute_variant;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Some chipsets (e.g. Intel 6700PXH) generate a legacy INTx when the IRQ
 * entry in the chipset's IO-APIC is masked (as, e.g. the RT kernel करोes
 * during पूर्णांकerrupt handling). When this INTx generation cannot be disabled,
 * we reroute these पूर्णांकerrupts to their legacy equivalent to get rid of
 * spurious पूर्णांकerrupts.
 */
अटल पूर्णांक acpi_reroute_boot_पूर्णांकerrupt(काष्ठा pci_dev *dev,
				       काष्ठा acpi_prt_entry *entry)
अणु
	अगर (noioapicquirk || noioapicreroute) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		चयन (bridge_has_boot_पूर्णांकerrupt_variant(dev->bus)) अणु
		हाल 0:
			/* no rerouting necessary */
			वापस 0;
		हाल INTEL_IRQ_REROUTE_VARIANT:
			/*
			 * Remap according to INTx routing table in 6700PXH
			 * specs, पूर्णांकel order number 302628-002, section
			 * 2.15.2. Other chipsets (80332, ...) have the same
			 * mapping and are handled here as well.
			 */
			dev_info(&dev->dev, "PCI IRQ %d -> rerouted to legacy "
				 "IRQ %d\n", entry->index,
				 (entry->index % 4) + 16);
			entry->index = (entry->index % 4) + 16;
			वापस 1;
		शेष:
			dev_warn(&dev->dev, "Cannot reroute IRQ %d to legacy "
				 "IRQ: unknown mapping\n", entry->index);
			वापस -1;
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_IO_APIC */

अटल काष्ठा acpi_prt_entry *acpi_pci_irq_lookup(काष्ठा pci_dev *dev, पूर्णांक pin)
अणु
	काष्ठा acpi_prt_entry *entry = शून्य;
	काष्ठा pci_dev *bridge;
	u8 bridge_pin, orig_pin = pin;
	पूर्णांक ret;

	ret = acpi_pci_irq_find_prt_entry(dev, pin, &entry);
	अगर (!ret && entry) अणु
#अगर_घोषित CONFIG_X86_IO_APIC
		acpi_reroute_boot_पूर्णांकerrupt(dev, entry);
#पूर्ण_अगर /* CONFIG_X86_IO_APIC */
		dev_dbg(&dev->dev, "Found [%c] _PRT entry\n", pin_name(pin));
		वापस entry;
	पूर्ण

	/*
	 * Attempt to derive an IRQ क्रम this device from a parent bridge's
	 * PCI पूर्णांकerrupt routing entry (eg. yenta bridge and add-in card bridge).
	 */
	bridge = dev->bus->self;
	जबतक (bridge) अणु
		pin = pci_swizzle_पूर्णांकerrupt_pin(dev, pin);

		अगर ((bridge->class >> 8) == PCI_CLASS_BRIDGE_CARDBUS) अणु
			/* PC card has the same IRQ as its cardbridge */
			bridge_pin = bridge->pin;
			अगर (!bridge_pin) अणु
				dev_dbg(&bridge->dev, "No interrupt pin configured\n");
				वापस शून्य;
			पूर्ण
			pin = bridge_pin;
		पूर्ण

		ret = acpi_pci_irq_find_prt_entry(bridge, pin, &entry);
		अगर (!ret && entry) अणु
			dev_dbg(&dev->dev, "Derived GSI INT %c from %s\n",
				pin_name(orig_pin), pci_name(bridge));
			वापस entry;
		पूर्ण

		dev = bridge;
		bridge = dev->bus->self;
	पूर्ण

	dev_warn(&dev->dev, "can't derive routing for PCI INT %c\n",
		 pin_name(orig_pin));
	वापस शून्य;
पूर्ण

#अगर IS_ENABLED(CONFIG_ISA) || IS_ENABLED(CONFIG_EISA)
अटल पूर्णांक acpi_isa_रेजिस्टर_gsi(काष्ठा pci_dev *dev)
अणु
	u32 dev_gsi;

	/* Interrupt Line values above 0xF are क्रमbidden */
	अगर (dev->irq > 0 && (dev->irq <= 0xF) &&
	    acpi_isa_irq_available(dev->irq) &&
	    (acpi_isa_irq_to_gsi(dev->irq, &dev_gsi) == 0)) अणु
		dev_warn(&dev->dev, "PCI INT %c: no GSI - using ISA IRQ %d\n",
			 pin_name(dev->pin), dev->irq);
		acpi_रेजिस्टर_gsi(&dev->dev, dev_gsi,
				  ACPI_LEVEL_SENSITIVE,
				  ACPI_ACTIVE_LOW);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_isa_रेजिस्टर_gsi(काष्ठा pci_dev *dev)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool acpi_pci_irq_valid(काष्ठा pci_dev *dev, u8 pin)
अणु
#अगर_घोषित CONFIG_X86
	/*
	 * On x86 irq line 0xff means "unknown" or "no connection"
	 * (PCI 3.0, Section 6.2.4, footnote on page 223).
	 */
	अगर (dev->irq == 0xff) अणु
		dev->irq = IRQ_NOTCONNECTED;
		dev_warn(&dev->dev, "PCI INT %c: not connected\n",
			 pin_name(pin));
		वापस false;
	पूर्ण
#पूर्ण_अगर
	वापस true;
पूर्ण

पूर्णांक acpi_pci_irq_enable(काष्ठा pci_dev *dev)
अणु
	काष्ठा acpi_prt_entry *entry;
	पूर्णांक gsi;
	u8 pin;
	पूर्णांक triggering = ACPI_LEVEL_SENSITIVE;
	/*
	 * On ARM प्रणालीs with the GIC पूर्णांकerrupt model, level पूर्णांकerrupts
	 * are always polarity high by specअगरication; PCI legacy
	 * IRQs lines are inverted beक्रमe reaching the पूर्णांकerrupt
	 * controller and must thereक्रमe be considered active high
	 * as शेष.
	 */
	पूर्णांक polarity = acpi_irq_model == ACPI_IRQ_MODEL_GIC ?
				      ACPI_ACTIVE_HIGH : ACPI_ACTIVE_LOW;
	अक्षर *link = शून्य;
	अक्षर link_desc[16];
	पूर्णांक rc;

	pin = dev->pin;
	अगर (!pin) अणु
		dev_dbg(&dev->dev, "No interrupt pin configured\n");
		वापस 0;
	पूर्ण

	अगर (dev->irq_managed && dev->irq > 0)
		वापस 0;

	entry = acpi_pci_irq_lookup(dev, pin);
	अगर (!entry) अणु
		/*
		 * IDE legacy mode controller IRQs are magic. Why करो compat
		 * extensions always make such a nasty mess.
		 */
		अगर (dev->class >> 8 == PCI_CLASS_STORAGE_IDE &&
				(dev->class & 0x05) == 0)
			वापस 0;
	पूर्ण

	अगर (entry) अणु
		अगर (entry->link)
			gsi = acpi_pci_link_allocate_irq(entry->link,
							 entry->index,
							 &triggering, &polarity,
							 &link);
		अन्यथा
			gsi = entry->index;
	पूर्ण अन्यथा
		gsi = -1;

	अगर (gsi < 0) अणु
		/*
		 * No IRQ known to the ACPI subप्रणाली - maybe the BIOS /
		 * driver reported one, then use it. Exit in any हाल.
		 */
		अगर (!acpi_pci_irq_valid(dev, pin)) अणु
			kमुक्त(entry);
			वापस 0;
		पूर्ण

		अगर (acpi_isa_रेजिस्टर_gsi(dev))
			dev_warn(&dev->dev, "PCI INT %c: no GSI\n",
				 pin_name(pin));

		kमुक्त(entry);
		वापस 0;
	पूर्ण

	rc = acpi_रेजिस्टर_gsi(&dev->dev, gsi, triggering, polarity);
	अगर (rc < 0) अणु
		dev_warn(&dev->dev, "PCI INT %c: failed to register GSI\n",
			 pin_name(pin));
		kमुक्त(entry);
		वापस rc;
	पूर्ण
	dev->irq = rc;
	dev->irq_managed = 1;

	अगर (link)
		snम_लिखो(link_desc, माप(link_desc), " -> Link[%s]", link);
	अन्यथा
		link_desc[0] = '\0';

	dev_dbg(&dev->dev, "PCI INT %c%s -> GSI %u (%s, %s) -> IRQ %d\n",
		pin_name(pin), link_desc, gsi,
		(triggering == ACPI_LEVEL_SENSITIVE) ? "level" : "edge",
		(polarity == ACPI_ACTIVE_LOW) ? "low" : "high", dev->irq);

	kमुक्त(entry);
	वापस 0;
पूर्ण

व्योम acpi_pci_irq_disable(काष्ठा pci_dev *dev)
अणु
	काष्ठा acpi_prt_entry *entry;
	पूर्णांक gsi;
	u8 pin;

	pin = dev->pin;
	अगर (!pin || !dev->irq_managed || dev->irq <= 0)
		वापस;

	/* Keep IOAPIC pin configuration when suspending */
	अगर (dev->dev.घातer.is_prepared)
		वापस;
#अगर_घोषित	CONFIG_PM
	अगर (dev->dev.घातer.runसमय_status == RPM_SUSPENDING)
		वापस;
#पूर्ण_अगर

	entry = acpi_pci_irq_lookup(dev, pin);
	अगर (!entry)
		वापस;

	अगर (entry->link)
		gsi = acpi_pci_link_मुक्त_irq(entry->link);
	अन्यथा
		gsi = entry->index;

	kमुक्त(entry);

	/*
	 * TBD: It might be worth clearing dev->irq by magic स्थिरant
	 * (e.g. PCI_UNDEFINED_IRQ).
	 */

	dev_dbg(&dev->dev, "PCI INT %c disabled\n", pin_name(pin));
	अगर (gsi >= 0) अणु
		acpi_unरेजिस्टर_gsi(gsi);
		dev->irq_managed = 0;
	पूर्ण
पूर्ण
