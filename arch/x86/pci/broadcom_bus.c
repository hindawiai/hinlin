<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Read address ranges from a Broadcom CNB20LE Host Bridge
 *
 * Copyright (c) 2010 Ira W. Snyder <iws@ovro.caltech.edu>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/pci_x86.h>
#समावेश <यंत्र/pci-direct.h>

#समावेश "bus_numa.h"

अटल व्योम __init cnb20le_res(u8 bus, u8 slot, u8 func)
अणु
	काष्ठा pci_root_info *info;
	काष्ठा pci_root_res *root_res;
	काष्ठा resource res;
	u16 word1, word2;
	u8 fbus, lbus;

	/* पढ़ो the PCI bus numbers */
	fbus = पढ़ो_pci_config_byte(bus, slot, func, 0x44);
	lbus = पढ़ो_pci_config_byte(bus, slot, func, 0x45);
	info = alloc_pci_root_info(fbus, lbus, 0, 0);

	/*
	 * Add the legacy IDE ports on bus 0
	 *
	 * These करो not exist anywhere in the bridge रेजिस्टरs, AFAICT. I करो
	 * not have the datasheet, so this is the best I can करो.
	 */
	अगर (fbus == 0) अणु
		update_res(info, 0x01f0, 0x01f7, IORESOURCE_IO, 0);
		update_res(info, 0x03f6, 0x03f6, IORESOURCE_IO, 0);
		update_res(info, 0x0170, 0x0177, IORESOURCE_IO, 0);
		update_res(info, 0x0376, 0x0376, IORESOURCE_IO, 0);
		update_res(info, 0xffa0, 0xffaf, IORESOURCE_IO, 0);
	पूर्ण

	/* पढ़ो the non-prefetchable memory winकरोw */
	word1 = पढ़ो_pci_config_16(bus, slot, func, 0xc0);
	word2 = पढ़ो_pci_config_16(bus, slot, func, 0xc2);
	अगर (word1 != word2) अणु
		res.start = ((resource_माप_प्रकार) word1 << 16) | 0x0000;
		res.end   = ((resource_माप_प्रकार) word2 << 16) | 0xffff;
		res.flags = IORESOURCE_MEM;
		update_res(info, res.start, res.end, res.flags, 0);
	पूर्ण

	/* पढ़ो the prefetchable memory winकरोw */
	word1 = पढ़ो_pci_config_16(bus, slot, func, 0xc4);
	word2 = पढ़ो_pci_config_16(bus, slot, func, 0xc6);
	अगर (word1 != word2) अणु
		res.start = ((resource_माप_प्रकार) word1 << 16) | 0x0000;
		res.end   = ((resource_माप_प्रकार) word2 << 16) | 0xffff;
		res.flags = IORESOURCE_MEM | IORESOURCE_PREFETCH;
		update_res(info, res.start, res.end, res.flags, 0);
	पूर्ण

	/* पढ़ो the IO port winकरोw */
	word1 = पढ़ो_pci_config_16(bus, slot, func, 0xd0);
	word2 = पढ़ो_pci_config_16(bus, slot, func, 0xd2);
	अगर (word1 != word2) अणु
		res.start = word1;
		res.end   = word2;
		res.flags = IORESOURCE_IO;
		update_res(info, res.start, res.end, res.flags, 0);
	पूर्ण

	/* prपूर्णांक inक्रमmation about this host bridge */
	res.start = fbus;
	res.end   = lbus;
	res.flags = IORESOURCE_BUS;
	prपूर्णांकk(KERN_INFO "CNB20LE PCI Host Bridge (domain 0000 %pR)\n", &res);

	list_क्रम_each_entry(root_res, &info->resources, list)
		prपूर्णांकk(KERN_INFO "host bridge window %pR\n", &root_res->res);
पूर्ण

अटल पूर्णांक __init broadcom_postcore_init(व्योम)
अणु
	u8 bus = 0, slot = 0;
	u32 id;
	u16 venकरोr, device;

#अगर_घोषित CONFIG_ACPI
	/*
	 * We should get host bridge inक्रमmation from ACPI unless the BIOS
	 * करोesn't support it.
	 */
	अगर (!acpi_disabled && acpi_os_get_root_poपूर्णांकer())
		वापस 0;
#पूर्ण_अगर

	id = पढ़ो_pci_config(bus, slot, 0, PCI_VENDOR_ID);
	venकरोr = id & 0xffff;
	device = (id >> 16) & 0xffff;

	अगर (venकरोr == PCI_VENDOR_ID_SERVERWORKS &&
	    device == PCI_DEVICE_ID_SERVERWORKS_LE) अणु
		cnb20le_res(bus, slot, 0);
		cnb20le_res(bus, slot, 1);
	पूर्ण
	वापस 0;
पूर्ण

postcore_initcall(broadcom_postcore_init);
