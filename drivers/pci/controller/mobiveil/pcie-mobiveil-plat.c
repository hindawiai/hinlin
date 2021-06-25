<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe host controller driver क्रम Mobiveil PCIe Host controller
 *
 * Copyright (c) 2018 Mobiveil Inc.
 * Copyright 2019 NXP
 *
 * Author: Subrahmanya Lingappa <l.subrahmanya@mobiveil.co.in>
 *	   Hou Zhiqiang <Zhiqiang.Hou@nxp.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "pcie-mobiveil.h"

अटल पूर्णांक mobiveil_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mobiveil_pcie *pcie;
	काष्ठा pci_host_bridge *bridge;
	काष्ठा device *dev = &pdev->dev;

	/* allocate the PCIe port */
	bridge = devm_pci_alloc_host_bridge(dev, माप(*pcie));
	अगर (!bridge)
		वापस -ENOMEM;

	pcie = pci_host_bridge_priv(bridge);
	pcie->rp.bridge = bridge;

	pcie->pdev = pdev;

	वापस mobiveil_pcie_host_probe(pcie);
पूर्ण

अटल स्थिर काष्ठा of_device_id mobiveil_pcie_of_match[] = अणु
	अणु.compatible = "mbvl,gpex40-pcie",पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, mobiveil_pcie_of_match);

अटल काष्ठा platक्रमm_driver mobiveil_pcie_driver = अणु
	.probe = mobiveil_pcie_probe,
	.driver = अणु
		.name = "mobiveil-pcie",
		.of_match_table = mobiveil_pcie_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(mobiveil_pcie_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Mobiveil PCIe host controller driver");
MODULE_AUTHOR("Subrahmanya Lingappa <l.subrahmanya@mobiveil.co.in>");
