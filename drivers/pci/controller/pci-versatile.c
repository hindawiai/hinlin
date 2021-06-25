<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2004 Koninklijke Philips Electronics NV
 *
 * Conversion to platक्रमm driver and DT:
 * Copyright 2014 Linaro Ltd.
 *
 * 14/04/2005 Initial version, colin.king@philips.com
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "../pci.h"

अटल व्योम __iomem *versatile_pci_base;
अटल व्योम __iomem *versatile_cfg_base[2];

#घोषणा PCI_IMAP(m)		(versatile_pci_base + ((m) * 4))
#घोषणा PCI_SMAP(m)		(versatile_pci_base + 0x14 + ((m) * 4))
#घोषणा PCI_SELFID		(versatile_pci_base + 0xc)

#घोषणा VP_PCI_DEVICE_ID		0x030010ee
#घोषणा VP_PCI_CLASS_ID			0x0b400000

अटल u32 pci_slot_ignore;

अटल पूर्णांक __init versatile_pci_slot_ignore(अक्षर *str)
अणु
	पूर्णांक retval;
	पूर्णांक slot;

	जबतक ((retval = get_option(&str, &slot))) अणु
		अगर ((slot < 0) || (slot > 31))
			pr_err("Illegal slot value: %d\n", slot);
		अन्यथा
			pci_slot_ignore |= (1 << slot);
	पूर्ण
	वापस 1;
पूर्ण
__setup("pci_slot_ignore=", versatile_pci_slot_ignore);


अटल व्योम __iomem *versatile_map_bus(काष्ठा pci_bus *bus,
				       अचिन्हित पूर्णांक devfn, पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक busnr = bus->number;

	अगर (pci_slot_ignore & (1 << PCI_SLOT(devfn)))
		वापस शून्य;

	वापस versatile_cfg_base[1] + ((busnr << 16) | (devfn << 8) | offset);
पूर्ण

अटल काष्ठा pci_ops pci_versatile_ops = अणु
	.map_bus = versatile_map_bus,
	.पढ़ो	= pci_generic_config_पढ़ो32,
	.ग_लिखो	= pci_generic_config_ग_लिखो,
पूर्ण;

अटल पूर्णांक versatile_pci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा resource_entry *entry;
	पूर्णांक i, myslot = -1, mem = 1;
	u32 val;
	व्योम __iomem *local_pci_cfg_base;
	काष्ठा pci_host_bridge *bridge;

	bridge = devm_pci_alloc_host_bridge(dev, 0);
	अगर (!bridge)
		वापस -ENOMEM;

	versatile_pci_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(versatile_pci_base))
		वापस PTR_ERR(versatile_pci_base);

	versatile_cfg_base[0] = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(versatile_cfg_base[0]))
		वापस PTR_ERR(versatile_cfg_base[0]);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 2);
	versatile_cfg_base[1] = devm_pci_remap_cfg_resource(dev, res);
	अगर (IS_ERR(versatile_cfg_base[1]))
		वापस PTR_ERR(versatile_cfg_base[1]);

	resource_list_क्रम_each_entry(entry, &bridge->winकरोws) अणु
		अगर (resource_type(entry->res) == IORESOURCE_MEM) अणु
			ग_लिखोl(entry->res->start >> 28, PCI_IMAP(mem));
			ग_लिखोl(__pa(PAGE_OFFSET) >> 28, PCI_SMAP(mem));
			mem++;
		पूर्ण
	पूर्ण

	/*
	 * We need to discover the PCI core first to configure itself
	 * beक्रमe the मुख्य PCI probing is perक्रमmed
	 */
	क्रम (i = 0; i < 32; i++) अणु
		अगर ((पढ़ोl(versatile_cfg_base[0] + (i << 11) + PCI_VENDOR_ID) == VP_PCI_DEVICE_ID) &&
		    (पढ़ोl(versatile_cfg_base[0] + (i << 11) + PCI_CLASS_REVISION) == VP_PCI_CLASS_ID)) अणु
			myslot = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (myslot == -1) अणु
		dev_err(dev, "Cannot find PCI core!\n");
		वापस -EIO;
	पूर्ण
	/*
	 * Do not to map Versatile FPGA PCI device पूर्णांकo memory space
	 */
	pci_slot_ignore |= (1 << myslot);

	dev_info(dev, "PCI core found (slot %d)\n", myslot);

	ग_लिखोl(myslot, PCI_SELFID);
	local_pci_cfg_base = versatile_cfg_base[1] + (myslot << 11);

	val = पढ़ोl(local_pci_cfg_base + PCI_COMMAND);
	val |= PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER | PCI_COMMAND_INVALIDATE;
	ग_लिखोl(val, local_pci_cfg_base + PCI_COMMAND);

	/*
	 * Configure the PCI inbound memory winकरोws to be 1:1 mapped to SDRAM
	 */
	ग_लिखोl(__pa(PAGE_OFFSET), local_pci_cfg_base + PCI_BASE_ADDRESS_0);
	ग_लिखोl(__pa(PAGE_OFFSET), local_pci_cfg_base + PCI_BASE_ADDRESS_1);
	ग_लिखोl(__pa(PAGE_OFFSET), local_pci_cfg_base + PCI_BASE_ADDRESS_2);

	/*
	 * For many years the kernel and QEMU were symbiotically buggy
	 * in that they both assumed the same broken IRQ mapping.
	 * QEMU thereक्रमe attempts to स्वतः-detect old broken kernels
	 * so that they still work on newer QEMU as they did on old
	 * QEMU. Since we now use the correct (ie matching-hardware)
	 * IRQ mapping we ग_लिखो a definitely dअगरferent value to a
	 * PCI_INTERRUPT_LINE रेजिस्टर to tell QEMU that we expect
	 * real hardware behaviour and it need not be backwards
	 * compatible क्रम us. This ग_लिखो is harmless on real hardware.
	 */
	ग_लिखोl(0, versatile_cfg_base[0] + PCI_INTERRUPT_LINE);

	pci_add_flags(PCI_REASSIGN_ALL_BUS);

	bridge->ops = &pci_versatile_ops;

	वापस pci_host_probe(bridge);
पूर्ण

अटल स्थिर काष्ठा of_device_id versatile_pci_of_match[] = अणु
	अणु .compatible = "arm,versatile-pci", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, versatile_pci_of_match);

अटल काष्ठा platक्रमm_driver versatile_pci_driver = अणु
	.driver = अणु
		.name = "versatile-pci",
		.of_match_table = versatile_pci_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = versatile_pci_probe,
पूर्ण;
module_platक्रमm_driver(versatile_pci_driver);

MODULE_DESCRIPTION("Versatile PCI driver");
MODULE_LICENSE("GPL v2");
