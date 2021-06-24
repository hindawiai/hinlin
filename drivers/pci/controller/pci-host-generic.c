<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Simple, generic PCI host controller driver targeting firmware-initialised
 * प्रणालीs and भव machines (e.g. the PCI emulation provided by kvmtool).
 *
 * Copyright (C) 2014 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/pci-ecam.h>
#समावेश <linux/platक्रमm_device.h>

अटल स्थिर काष्ठा pci_ecam_ops gen_pci_cfg_cam_bus_ops = अणु
	.bus_shअगरt	= 16,
	.pci_ops	= अणु
		.map_bus	= pci_ecam_map_bus,
		.पढ़ो		= pci_generic_config_पढ़ो,
		.ग_लिखो		= pci_generic_config_ग_लिखो,
	पूर्ण
पूर्ण;

अटल bool pci_dw_valid_device(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn)
अणु
	काष्ठा pci_config_winकरोw *cfg = bus->sysdata;

	/*
	 * The Synopsys DesignWare PCIe controller in ECAM mode will not filter
	 * type 0 config TLPs sent to devices 1 and up on its करोwnstream port,
	 * resulting in devices appearing multiple बार on bus 0 unless we
	 * filter out those accesses here.
	 */
	अगर (bus->number == cfg->busr.start && PCI_SLOT(devfn) > 0)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम __iomem *pci_dw_ecam_map_bus(काष्ठा pci_bus *bus,
					 अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	अगर (!pci_dw_valid_device(bus, devfn))
		वापस शून्य;

	वापस pci_ecam_map_bus(bus, devfn, where);
पूर्ण

अटल स्थिर काष्ठा pci_ecam_ops pci_dw_ecam_bus_ops = अणु
	.pci_ops	= अणु
		.map_bus	= pci_dw_ecam_map_bus,
		.पढ़ो		= pci_generic_config_पढ़ो,
		.ग_लिखो		= pci_generic_config_ग_लिखो,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id gen_pci_of_match[] = अणु
	अणु .compatible = "pci-host-cam-generic",
	  .data = &gen_pci_cfg_cam_bus_ops पूर्ण,

	अणु .compatible = "pci-host-ecam-generic",
	  .data = &pci_generic_ecam_ops पूर्ण,

	अणु .compatible = "marvell,armada8k-pcie-ecam",
	  .data = &pci_dw_ecam_bus_ops पूर्ण,

	अणु .compatible = "socionext,synquacer-pcie-ecam",
	  .data = &pci_dw_ecam_bus_ops पूर्ण,

	अणु .compatible = "snps,dw-pcie-ecam",
	  .data = &pci_dw_ecam_bus_ops पूर्ण,

	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gen_pci_of_match);

अटल काष्ठा platक्रमm_driver gen_pci_driver = अणु
	.driver = अणु
		.name = "pci-host-generic",
		.of_match_table = gen_pci_of_match,
	पूर्ण,
	.probe = pci_host_common_probe,
	.हटाओ = pci_host_common_हटाओ,
पूर्ण;
module_platक्रमm_driver(gen_pci_driver);

MODULE_LICENSE("GPL v2");
