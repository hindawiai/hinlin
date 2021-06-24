<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implement the शेष iomap पूर्णांकerfaces
 *
 * (C) Copyright 2004 Linus Torvalds
 * (C) Copyright 2006 Ralf Baechle <ralf@linux-mips.org>
 * (C) Copyright 2007 MIPS Technologies, Inc.
 *     written by Ralf Baechle <ralf@linux-mips.org>
 */
#समावेश <linux/pci.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/पन.स>

#अगर_घोषित CONFIG_PCI_DRIVERS_LEGACY

व्योम __iomem *__pci_ioport_map(काष्ठा pci_dev *dev,
			       अचिन्हित दीर्घ port, अचिन्हित पूर्णांक nr)
अणु
	काष्ठा pci_controller *ctrl = dev->bus->sysdata;
	अचिन्हित दीर्घ base = ctrl->io_map_base;

	/* This will eventually become a BUG_ON but क्रम now be gentle */
	अगर (unlikely(!ctrl->io_map_base)) अणु
		काष्ठा pci_bus *bus = dev->bus;
		अक्षर name[8];

		जबतक (bus->parent)
			bus = bus->parent;

		ctrl->io_map_base = base = mips_io_port_base;

		प्र_लिखो(name, "%04x:%02x", pci_करोमुख्य_nr(bus), bus->number);
		prपूर्णांकk(KERN_WARNING "io_map_base of root PCI bus %s unset.  "
		       "Trying to continue but you better\nfix this issue or "
		       "report it to linux-mips@vger.kernel.org or your "
		       "vendor.\n", name);
#अगर_घोषित CONFIG_PCI_DOMAINS
		panic("To avoid data corruption io_map_base MUST be set with "
		      "multiple PCI domains.");
#पूर्ण_अगर
	पूर्ण

	वापस (व्योम __iomem *) (ctrl->io_map_base + port);
पूर्ण

#पूर्ण_अगर /* CONFIG_PCI_DRIVERS_LEGACY */
