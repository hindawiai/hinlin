<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cardbus.c -- 16-bit PCMCIA core support
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * (C) 1999		David A. Hinds
 */

/*
 * Cardbus handling has been re-written to be more of a PCI bridge thing,
 * and the PCI code basically करोes all the resource handling.
 *
 *		Linus, Jan 2000
 */


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश <pcmcia/ss.h>
#समावेश <pcmcia/cistpl.h>

#समावेश "cs_internal.h"

अटल व्योम cardbus_config_irq_and_cls(काष्ठा pci_bus *bus, पूर्णांक irq)
अणु
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		u8 irq_pin;

		/*
		 * Since there is only one पूर्णांकerrupt available to
		 * CardBus devices, all devices करोwnstream of this
		 * device must be using this IRQ.
		 */
		pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_PIN, &irq_pin);
		अगर (irq_pin) अणु
			dev->irq = irq;
			pci_ग_लिखो_config_byte(dev, PCI_INTERRUPT_LINE, dev->irq);
		पूर्ण

		/*
		 * Some controllers transfer very slowly with 0 CLS.
		 * Configure it.  This may fail as CLS configuration
		 * is mandatory only क्रम MWI.
		 */
		pci_set_cacheline_size(dev);

		अगर (dev->subordinate)
			cardbus_config_irq_and_cls(dev->subordinate, irq);
	पूर्ण
पूर्ण

/**
 * cb_alloc() - add CardBus device
 * @s:		the pcmcia_socket where the CardBus device is located
 *
 * cb_alloc() allocates the kernel data काष्ठाures क्रम a Cardbus device
 * and handles the lowest level PCI device setup issues.
 */
पूर्णांक __ref cb_alloc(काष्ठा pcmcia_socket *s)
अणु
	काष्ठा pci_bus *bus = s->cb_dev->subordinate;
	काष्ठा pci_dev *dev;
	अचिन्हित पूर्णांक max, pass;

	pci_lock_rescan_हटाओ();

	s->functions = pci_scan_slot(bus, PCI_DEVFN(0, 0));
	pci_fixup_cardbus(bus);

	max = bus->busn_res.start;
	क्रम (pass = 0; pass < 2; pass++)
		क्रम_each_pci_bridge(dev, bus)
			max = pci_scan_bridge(bus, dev, max, pass);

	/*
	 * Size all resources below the CardBus controller.
	 */
	pci_bus_size_bridges(bus);
	pci_bus_assign_resources(bus);
	cardbus_config_irq_and_cls(bus, s->pci_irq);

	/* socket specअगरic tune function */
	अगर (s->tune_bridge)
		s->tune_bridge(s, bus);

	pci_bus_add_devices(bus);

	pci_unlock_rescan_हटाओ();
	वापस 0;
पूर्ण

/**
 * cb_मुक्त() - हटाओ CardBus device
 * @s:		the pcmcia_socket where the CardBus device was located
 *
 * cb_मुक्त() handles the lowest level PCI device cleanup.
 */
व्योम cb_मुक्त(काष्ठा pcmcia_socket *s)
अणु
	काष्ठा pci_dev *bridge, *dev, *पंचांगp;
	काष्ठा pci_bus *bus;

	bridge = s->cb_dev;
	अगर (!bridge)
		वापस;

	bus = bridge->subordinate;
	अगर (!bus)
		वापस;

	pci_lock_rescan_हटाओ();

	list_क्रम_each_entry_safe(dev, पंचांगp, &bus->devices, bus_list)
		pci_stop_and_हटाओ_bus_device(dev);

	pci_unlock_rescan_हटाओ();
पूर्ण
