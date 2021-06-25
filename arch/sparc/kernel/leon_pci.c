<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * leon_pci.c: LEON Host PCI support
 *
 * Copyright (C) 2011 Aeroflex Gaisler AB, Daniel Hellstrom
 *
 * Code is partially derived from pcic.c
 */

#समावेश <linux/of_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/leon.h>
#समावेश <यंत्र/leon_pci.h>

/* The LEON architecture करोes not rely on a BIOS or bootloader to setup
 * PCI क्रम us. The Linux generic routines are used to setup resources,
 * reset values of configuration-space रेजिस्टर settings are preserved.
 *
 * PCI Memory and Prefetchable Memory is direct-mapped. However I/O Space is
 * accessed through a Winकरोw which is translated to low 64KB in PCI space, the
 * first 4KB is not used so 60KB is available.
 */
व्योम leon_pci_init(काष्ठा platक्रमm_device *ofdev, काष्ठा leon_pci_info *info)
अणु
	LIST_HEAD(resources);
	काष्ठा pci_bus *root_bus;
	काष्ठा pci_host_bridge *bridge;
	पूर्णांक ret;

	bridge = pci_alloc_host_bridge(0);
	अगर (!bridge)
		वापस;

	pci_add_resource_offset(&resources, &info->io_space,
				info->io_space.start - 0x1000);
	pci_add_resource(&resources, &info->mem_space);
	info->busn.flags = IORESOURCE_BUS;
	pci_add_resource(&resources, &info->busn);

	list_splice_init(&resources, &bridge->winकरोws);
	bridge->dev.parent = &ofdev->dev;
	bridge->sysdata = info;
	bridge->busnr = 0;
	bridge->ops = info->ops;
	bridge->swizzle_irq = pci_common_swizzle;
	bridge->map_irq = info->map_irq;

	ret = pci_scan_root_bus_bridge(bridge);
	अगर (ret) अणु
		pci_मुक्त_host_bridge(bridge);
		वापस;
	पूर्ण

	root_bus = bridge->bus;

	/* Assign devices with resources */
	pci_assign_unasचिन्हित_resources();
	pci_bus_add_devices(root_bus);
पूर्ण

पूर्णांक pcibios_enable_device(काष्ठा pci_dev *dev, पूर्णांक mask)
अणु
	u16 cmd, oldcmd;
	पूर्णांक i;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
	oldcmd = cmd;

	क्रम (i = 0; i < PCI_NUM_RESOURCES; i++) अणु
		काष्ठा resource *res = &dev->resource[i];

		/* Only set up the requested stuff */
		अगर (!(mask & (1<<i)))
			जारी;

		अगर (res->flags & IORESOURCE_IO)
			cmd |= PCI_COMMAND_IO;
		अगर (res->flags & IORESOURCE_MEM)
			cmd |= PCI_COMMAND_MEMORY;
	पूर्ण

	अगर (cmd != oldcmd) अणु
		pci_info(dev, "enabling device (%04x -> %04x)\n", oldcmd, cmd);
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);
	पूर्ण
	वापस 0;
पूर्ण
