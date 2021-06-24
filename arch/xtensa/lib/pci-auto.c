<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/xtensa/lib/pci-स्वतः.c
 *
 * PCI स्वतःconfiguration library
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 *
 * Chris Zankel <zankel@tensilica.com, cez@zankel.net>
 *
 * Based on work from Matt Porter <mporter@mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/pci-bridge.h>


/*
 *
 * Setting up a PCI
 *
 * pci_ctrl->first_busno = <first bus number (0)>
 * pci_ctrl->last_busno = <last bus number (0xff)>
 * pci_ctrl->ops = <PCI config operations>
 * pci_ctrl->map_irq = <function to वापस the पूर्णांकerrupt number क्रम a device>
 *
 * pci_ctrl->io_space.start = <IO space start address (PCI view)>
 * pci_ctrl->io_space.end = <IO space end address (PCI view)>
 * pci_ctrl->io_space.base = <IO space offset: address 0 from CPU space>
 * pci_ctrl->mem_space.start = <MEM space start address (PCI view)>
 * pci_ctrl->mem_space.end = <MEM space end address (PCI view)>
 * pci_ctrl->mem_space.base = <MEM space offset: address 0 from CPU space>
 *
 * pcibios_init_resource(&pci_ctrl->io_resource, <IO space start>,
 * 			 <IO space end>, IORESOURCE_IO, "PCI host bridge");
 * pcibios_init_resource(&pci_ctrl->mem_resources[0], <MEM space start>,
 * 			 <MEM space end>, IORESOURCE_MEM, "PCI host bridge");
 *
 * pci_ctrl->last_busno = pciस्वतः_bus_scan(pci_ctrl,pci_ctrl->first_busno);
 *
 * पूर्णांक __init pciस्वतः_bus_scan(काष्ठा pci_controller *pci_ctrl, पूर्णांक current_bus)
 *
 */

अटल पूर्णांक pciस्वतः_upper_iospc;
अटल पूर्णांक pciस्वतः_upper_memspc;

अटल काष्ठा pci_dev pciस्वतः_dev;
अटल काष्ठा pci_bus pciस्वतः_bus;

/*
 * Helper functions
 */

/* Initialize the bars of a PCI device.  */

अटल व्योम __init
pciस्वतः_setup_bars(काष्ठा pci_dev *dev, पूर्णांक bar_limit)
अणु
	पूर्णांक bar_size;
	पूर्णांक bar, bar_nr;
	पूर्णांक *upper_limit;
	पूर्णांक found_mem64 = 0;

	क्रम (bar = PCI_BASE_ADDRESS_0, bar_nr = 0;
	     bar <= bar_limit;
	     bar+=4, bar_nr++)
	अणु
		/* Tickle the BAR and get the size */
		pci_ग_लिखो_config_dword(dev, bar, 0xffffffff);
		pci_पढ़ो_config_dword(dev, bar, &bar_size);

		/* If BAR is not implemented go to the next BAR */
		अगर (!bar_size)
			जारी;

		/* Check the BAR type and set our address mask */
		अगर (bar_size & PCI_BASE_ADDRESS_SPACE_IO)
		अणु
			bar_size &= PCI_BASE_ADDRESS_IO_MASK;
			upper_limit = &pciस्वतः_upper_iospc;
			pr_debug("PCI Autoconfig: BAR %d, I/O, ", bar_nr);
		पूर्ण
		अन्यथा
		अणु
			अगर ((bar_size & PCI_BASE_ADDRESS_MEM_TYPE_MASK) ==
			    PCI_BASE_ADDRESS_MEM_TYPE_64)
				found_mem64 = 1;

			bar_size &= PCI_BASE_ADDRESS_MEM_MASK;
			upper_limit = &pciस्वतः_upper_memspc;
			pr_debug("PCI Autoconfig: BAR %d, Mem, ", bar_nr);
		पूर्ण

		/* Allocate a base address (bar_size is negative!) */
		*upper_limit = (*upper_limit + bar_size) & bar_size;

		/* Write it out and update our limit */
		pci_ग_लिखो_config_dword(dev, bar, *upper_limit);

		/*
		 * If we are a 64-bit decoder then increment to the
		 * upper 32 bits of the bar and क्रमce it to locate
		 * in the lower 4GB of memory.
		 */

		अगर (found_mem64)
			pci_ग_लिखो_config_dword(dev, (bar+=4), 0x00000000);

		pr_debug("size=0x%x, address=0x%x\n",
			 ~bar_size + 1, *upper_limit);
	पूर्ण
पूर्ण

/* Initialize the पूर्णांकerrupt number. */

अटल व्योम __init
pciस्वतः_setup_irq(काष्ठा pci_controller* pci_ctrl,काष्ठा pci_dev *dev,पूर्णांक devfn)
अणु
	u8 pin;
	पूर्णांक irq = 0;

	pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_PIN, &pin);

	/* Fix illegal pin numbers. */

	अगर (pin == 0 || pin > 4)
		pin = 1;

	अगर (pci_ctrl->map_irq)
		irq = pci_ctrl->map_irq(dev, PCI_SLOT(devfn), pin);

	अगर (irq == -1)
		irq = 0;

	pr_debug("PCI Autoconfig: Interrupt %d, pin %d\n", irq, pin);

	pci_ग_लिखो_config_byte(dev, PCI_INTERRUPT_LINE, irq);
पूर्ण


अटल व्योम __init
pciस्वतः_prescan_setup_bridge(काष्ठा pci_dev *dev, पूर्णांक current_bus,
			     पूर्णांक sub_bus, पूर्णांक *iosave, पूर्णांक *memsave)
अणु
	/* Configure bus number रेजिस्टरs */
	pci_ग_लिखो_config_byte(dev, PCI_PRIMARY_BUS, current_bus);
	pci_ग_लिखो_config_byte(dev, PCI_SECONDARY_BUS, sub_bus + 1);
	pci_ग_लिखो_config_byte(dev, PCI_SUBORDINATE_BUS,	0xff);

	/* Round memory allocator to 1MB boundary */
	pciस्वतः_upper_memspc &= ~(0x100000 - 1);
	*memsave = pciस्वतः_upper_memspc;

	/* Round I/O allocator to 4KB boundary */
	pciस्वतः_upper_iospc &= ~(0x1000 - 1);
	*iosave = pciस्वतः_upper_iospc;

	/* Set up memory and I/O filter limits, assume 32-bit I/O space */
	pci_ग_लिखो_config_word(dev, PCI_MEMORY_LIMIT,
			      ((pciस्वतः_upper_memspc - 1) & 0xfff00000) >> 16);
	pci_ग_लिखो_config_byte(dev, PCI_IO_LIMIT,
			      ((pciस्वतः_upper_iospc - 1) & 0x0000f000) >> 8);
	pci_ग_लिखो_config_word(dev, PCI_IO_LIMIT_UPPER16,
			      ((pciस्वतः_upper_iospc - 1) & 0xffff0000) >> 16);
पूर्ण

अटल व्योम __init
pciस्वतः_postscan_setup_bridge(काष्ठा pci_dev *dev, पूर्णांक current_bus, पूर्णांक sub_bus,
			      पूर्णांक *iosave, पूर्णांक *memsave)
अणु
	पूर्णांक cmdstat;

	/* Configure bus number रेजिस्टरs */
	pci_ग_लिखो_config_byte(dev, PCI_SUBORDINATE_BUS,	sub_bus);

	/*
	 * Round memory allocator to 1MB boundary.
	 * If no space used, allocate minimum.
	 */
	pciस्वतः_upper_memspc &= ~(0x100000 - 1);
	अगर (*memsave == pciस्वतः_upper_memspc)
		pciस्वतः_upper_memspc -= 0x00100000;

	pci_ग_लिखो_config_word(dev, PCI_MEMORY_BASE, pciस्वतः_upper_memspc >> 16);

	/* Allocate 1MB क्रम pre-fretch */
	pci_ग_लिखो_config_word(dev, PCI_PREF_MEMORY_LIMIT,
			      ((pciस्वतः_upper_memspc - 1) & 0xfff00000) >> 16);

	pciस्वतः_upper_memspc -= 0x100000;

	pci_ग_लिखो_config_word(dev, PCI_PREF_MEMORY_BASE,
			      pciस्वतः_upper_memspc >> 16);

	/* Round I/O allocator to 4KB boundary */
	pciस्वतः_upper_iospc &= ~(0x1000 - 1);
	अगर (*iosave == pciस्वतः_upper_iospc)
		pciस्वतः_upper_iospc -= 0x1000;

	pci_ग_लिखो_config_byte(dev, PCI_IO_BASE,
			      (pciस्वतः_upper_iospc & 0x0000f000) >> 8);
	pci_ग_लिखो_config_word(dev, PCI_IO_BASE_UPPER16,
			      pciस्वतः_upper_iospc >> 16);

	/* Enable memory and I/O accesses, enable bus master */
	pci_पढ़ो_config_dword(dev, PCI_COMMAND, &cmdstat);
	pci_ग_लिखो_config_dword(dev, PCI_COMMAND,
			       cmdstat |
			       PCI_COMMAND_IO |
			       PCI_COMMAND_MEMORY |
			       PCI_COMMAND_MASTER);
पूर्ण

/*
 * Scan the current PCI bus.
 */


पूर्णांक __init pciस्वतः_bus_scan(काष्ठा pci_controller *pci_ctrl, पूर्णांक current_bus)
अणु
	पूर्णांक sub_bus, pci_devfn, pci_class, cmdstat, found_multi=0;
	अचिन्हित लघु vid;
	अचिन्हित अक्षर header_type;
	काष्ठा pci_dev *dev = &pciस्वतः_dev;

	pciस्वतः_dev.bus = &pciस्वतः_bus;
	pciस्वतः_dev.sysdata = pci_ctrl;
	pciस्वतः_bus.ops = pci_ctrl->ops;

	/*
	 * Fetch our I/O and memory space upper boundaries used
	 * to allocated base addresses on this pci_controller.
	 */

	अगर (current_bus == pci_ctrl->first_busno)
	अणु
		pciस्वतः_upper_iospc = pci_ctrl->io_resource.end + 1;
		pciस्वतः_upper_memspc = pci_ctrl->mem_resources[0].end + 1;
	पूर्ण

	sub_bus = current_bus;

	क्रम (pci_devfn = 0; pci_devfn < 0xff; pci_devfn++)
	अणु
		/* Skip our host bridge */
		अगर ((current_bus == pci_ctrl->first_busno) && (pci_devfn == 0))
			जारी;

		अगर (PCI_FUNC(pci_devfn) && !found_multi)
			जारी;

		pciस्वतः_bus.number = current_bus;
		pciस्वतः_dev.devfn = pci_devfn;

		/* If config space पढ़ो fails from this device, move on */
		अगर (pci_पढ़ो_config_byte(dev, PCI_HEADER_TYPE, &header_type))
			जारी;

		अगर (!PCI_FUNC(pci_devfn))
			found_multi = header_type & 0x80;
		pci_पढ़ो_config_word(dev, PCI_VENDOR_ID, &vid);

		अगर (vid == 0xffff || vid == 0x0000) अणु
			found_multi = 0;
			जारी;
		पूर्ण

		pci_पढ़ो_config_dword(dev, PCI_CLASS_REVISION, &pci_class);

		अगर ((pci_class >> 16) == PCI_CLASS_BRIDGE_PCI) अणु

			पूर्णांक iosave, memsave;

			pr_debug("PCI Autoconfig: Found P2P bridge, device %d\n",
				 PCI_SLOT(pci_devfn));

			/* Allocate PCI I/O and/or memory space */
			pciस्वतः_setup_bars(dev, PCI_BASE_ADDRESS_1);

			pciस्वतः_prescan_setup_bridge(dev, current_bus, sub_bus,
					&iosave, &memsave);
			sub_bus = pciस्वतः_bus_scan(pci_ctrl, sub_bus+1);
			pciस्वतः_postscan_setup_bridge(dev, current_bus, sub_bus,
					&iosave, &memsave);
			pciस्वतः_bus.number = current_bus;

			जारी;

		पूर्ण

		/*
		 * Found a peripheral, enable some standard
		 * settings
		 */

		pci_पढ़ो_config_dword(dev, PCI_COMMAND,	&cmdstat);
		pci_ग_लिखो_config_dword(dev, PCI_COMMAND,
				cmdstat |
					PCI_COMMAND_IO |
					PCI_COMMAND_MEMORY |
					PCI_COMMAND_MASTER);
		pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, 0x80);

		/* Allocate PCI I/O and/or memory space */
		pr_debug("PCI Autoconfig: Found Bus %d, Device %d, Function %d\n",
			 current_bus, PCI_SLOT(pci_devfn), PCI_FUNC(pci_devfn));

		pciस्वतः_setup_bars(dev, PCI_BASE_ADDRESS_5);
		pciस्वतः_setup_irq(pci_ctrl, dev, pci_devfn);
	पूर्ण
	वापस sub_bus;
पूर्ण
