<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe host controller driver क्रम HiSilicon SoCs
 *
 * Copyright (C) 2015 HiSilicon Co., Ltd. http://www.hisilicon.com
 *
 * Authors: Zhou Wang <wangzhou1@hisilicon.com>
 *          Dacai Zhu <zhudacai@hisilicon.com>
 *          Gabriele Paoloni <gabriele.paoloni@huawei.com>
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-acpi.h>
#समावेश <linux/pci-ecam.h>
#समावेश "../../pci.h"

#अगर defined(CONFIG_PCI_HISI) || (defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIRKS))

अटल पूर्णांक hisi_pcie_rd_conf(काष्ठा pci_bus *bus, u32 devfn, पूर्णांक where,
			     पूर्णांक size, u32 *val)
अणु
	काष्ठा pci_config_winकरोw *cfg = bus->sysdata;
	पूर्णांक dev = PCI_SLOT(devfn);

	अगर (bus->number == cfg->busr.start) अणु
		/* access only one slot on each root port */
		अगर (dev > 0)
			वापस PCIBIOS_DEVICE_NOT_FOUND;
		अन्यथा
			वापस pci_generic_config_पढ़ो32(bus, devfn, where,
							 size, val);
	पूर्ण

	वापस pci_generic_config_पढ़ो(bus, devfn, where, size, val);
पूर्ण

अटल पूर्णांक hisi_pcie_wr_conf(काष्ठा pci_bus *bus, u32 devfn,
			     पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा pci_config_winकरोw *cfg = bus->sysdata;
	पूर्णांक dev = PCI_SLOT(devfn);

	अगर (bus->number == cfg->busr.start) अणु
		/* access only one slot on each root port */
		अगर (dev > 0)
			वापस PCIBIOS_DEVICE_NOT_FOUND;
		अन्यथा
			वापस pci_generic_config_ग_लिखो32(bus, devfn, where,
							  size, val);
	पूर्ण

	वापस pci_generic_config_ग_लिखो(bus, devfn, where, size, val);
पूर्ण

अटल व्योम __iomem *hisi_pcie_map_bus(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				       पूर्णांक where)
अणु
	काष्ठा pci_config_winकरोw *cfg = bus->sysdata;
	व्योम __iomem *reg_base = cfg->priv;

	अगर (bus->number == cfg->busr.start)
		वापस reg_base + where;
	अन्यथा
		वापस pci_ecam_map_bus(bus, devfn, where);
पूर्ण

#अगर defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIRKS)

अटल पूर्णांक hisi_pcie_init(काष्ठा pci_config_winकरोw *cfg)
अणु
	काष्ठा device *dev = cfg->parent;
	काष्ठा acpi_device *adev = to_acpi_device(dev);
	काष्ठा acpi_pci_root *root = acpi_driver_data(adev);
	काष्ठा resource *res;
	व्योम __iomem *reg_base;
	पूर्णांक ret;

	/*
	 * Retrieve RC base and size from a HISI0081 device with _UID
	 * matching our segment.
	 */
	res = devm_kzalloc(dev, माप(*res), GFP_KERNEL);
	अगर (!res)
		वापस -ENOMEM;

	ret = acpi_get_rc_resources(dev, "HISI0081", root->segment, res);
	अगर (ret) अणु
		dev_err(dev, "can't get rc base address\n");
		वापस -ENOMEM;
	पूर्ण

	reg_base = devm_pci_remap_cfgspace(dev, res->start, resource_size(res));
	अगर (!reg_base)
		वापस -ENOMEM;

	cfg->priv = reg_base;
	वापस 0;
पूर्ण

स्थिर काष्ठा pci_ecam_ops hisi_pcie_ops = अणु
	.init         =  hisi_pcie_init,
	.pci_ops      = अणु
		.map_bus    = hisi_pcie_map_bus,
		.पढ़ो       = hisi_pcie_rd_conf,
		.ग_लिखो      = hisi_pcie_wr_conf,
	पूर्ण
पूर्ण;

#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI_HISI

अटल पूर्णांक hisi_pcie_platक्रमm_init(काष्ठा pci_config_winकरोw *cfg)
अणु
	काष्ठा device *dev = cfg->parent;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource *res;
	व्योम __iomem *reg_base;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!res) अणु
		dev_err(dev, "missing \"reg[1]\"property\n");
		वापस -EINVAL;
	पूर्ण

	reg_base = devm_pci_remap_cfgspace(dev, res->start, resource_size(res));
	अगर (!reg_base)
		वापस -ENOMEM;

	cfg->priv = reg_base;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_ecam_ops hisi_pcie_platक्रमm_ops = अणु
	.init         =  hisi_pcie_platक्रमm_init,
	.pci_ops      = अणु
		.map_bus    = hisi_pcie_map_bus,
		.पढ़ो       = hisi_pcie_rd_conf,
		.ग_लिखो      = hisi_pcie_wr_conf,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id hisi_pcie_almost_ecam_of_match[] = अणु
	अणु
		.compatible =  "hisilicon,hip06-pcie-ecam",
		.data	    =  &hisi_pcie_platक्रमm_ops,
	पूर्ण,
	अणु
		.compatible =  "hisilicon,hip07-pcie-ecam",
		.data       =  &hisi_pcie_platक्रमm_ops,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver hisi_pcie_almost_ecam_driver = अणु
	.probe  = pci_host_common_probe,
	.driver = अणु
		   .name = "hisi-pcie-almost-ecam",
		   .of_match_table = hisi_pcie_almost_ecam_of_match,
		   .suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(hisi_pcie_almost_ecam_driver);

#पूर्ण_अगर
#पूर्ण_अगर
