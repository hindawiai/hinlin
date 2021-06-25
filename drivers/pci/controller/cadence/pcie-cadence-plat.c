<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cadence PCIe platक्रमm  driver.
 *
 * Copyright (c) 2019, Cadence Design Systems
 * Author: Tom Joseph <tjoseph@cadence.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of_device.h>
#समावेश "pcie-cadence.h"

#घोषणा CDNS_PLAT_CPU_TO_BUS_ADDR	0x0FFFFFFF

/**
 * काष्ठा cdns_plat_pcie - निजी data क्रम this PCIe platक्रमm driver
 * @pcie: Cadence PCIe controller
 * @is_rc: Set to 1 indicates the PCIe controller mode is Root Complex,
 *         अगर 0 it is in Endpoपूर्णांक mode.
 */
काष्ठा cdns_plat_pcie अणु
	काष्ठा cdns_pcie        *pcie;
	bool is_rc;
पूर्ण;

काष्ठा cdns_plat_pcie_of_data अणु
	bool is_rc;
पूर्ण;

अटल स्थिर काष्ठा of_device_id cdns_plat_pcie_of_match[];

अटल u64 cdns_plat_cpu_addr_fixup(काष्ठा cdns_pcie *pcie, u64 cpu_addr)
अणु
	वापस cpu_addr & CDNS_PLAT_CPU_TO_BUS_ADDR;
पूर्ण

अटल स्थिर काष्ठा cdns_pcie_ops cdns_plat_ops = अणु
	.cpu_addr_fixup = cdns_plat_cpu_addr_fixup,
पूर्ण;

अटल पूर्णांक cdns_plat_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा cdns_plat_pcie_of_data *data;
	काष्ठा cdns_plat_pcie *cdns_plat_pcie;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pci_host_bridge *bridge;
	काष्ठा cdns_pcie_ep *ep;
	काष्ठा cdns_pcie_rc *rc;
	पूर्णांक phy_count;
	bool is_rc;
	पूर्णांक ret;

	match = of_match_device(cdns_plat_pcie_of_match, dev);
	अगर (!match)
		वापस -EINVAL;

	data = (काष्ठा cdns_plat_pcie_of_data *)match->data;
	is_rc = data->is_rc;

	pr_debug(" Started %s with is_rc: %d\n", __func__, is_rc);
	cdns_plat_pcie = devm_kzalloc(dev, माप(*cdns_plat_pcie), GFP_KERNEL);
	अगर (!cdns_plat_pcie)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, cdns_plat_pcie);
	अगर (is_rc) अणु
		अगर (!IS_ENABLED(CONFIG_PCIE_CADENCE_PLAT_HOST))
			वापस -ENODEV;

		bridge = devm_pci_alloc_host_bridge(dev, माप(*rc));
		अगर (!bridge)
			वापस -ENOMEM;

		rc = pci_host_bridge_priv(bridge);
		rc->pcie.dev = dev;
		rc->pcie.ops = &cdns_plat_ops;
		cdns_plat_pcie->pcie = &rc->pcie;
		cdns_plat_pcie->is_rc = is_rc;

		ret = cdns_pcie_init_phy(dev, cdns_plat_pcie->pcie);
		अगर (ret) अणु
			dev_err(dev, "failed to init phy\n");
			वापस ret;
		पूर्ण
		pm_runसमय_enable(dev);
		ret = pm_runसमय_get_sync(dev);
		अगर (ret < 0) अणु
			dev_err(dev, "pm_runtime_get_sync() failed\n");
			जाओ err_get_sync;
		पूर्ण

		ret = cdns_pcie_host_setup(rc);
		अगर (ret)
			जाओ err_init;
	पूर्ण अन्यथा अणु
		अगर (!IS_ENABLED(CONFIG_PCIE_CADENCE_PLAT_EP))
			वापस -ENODEV;

		ep = devm_kzalloc(dev, माप(*ep), GFP_KERNEL);
		अगर (!ep)
			वापस -ENOMEM;

		ep->pcie.dev = dev;
		ep->pcie.ops = &cdns_plat_ops;
		cdns_plat_pcie->pcie = &ep->pcie;
		cdns_plat_pcie->is_rc = is_rc;

		ret = cdns_pcie_init_phy(dev, cdns_plat_pcie->pcie);
		अगर (ret) अणु
			dev_err(dev, "failed to init phy\n");
			वापस ret;
		पूर्ण

		pm_runसमय_enable(dev);
		ret = pm_runसमय_get_sync(dev);
		अगर (ret < 0) अणु
			dev_err(dev, "pm_runtime_get_sync() failed\n");
			जाओ err_get_sync;
		पूर्ण

		ret = cdns_pcie_ep_setup(ep);
		अगर (ret)
			जाओ err_init;
	पूर्ण

 err_init:
 err_get_sync:
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
	cdns_pcie_disable_phy(cdns_plat_pcie->pcie);
	phy_count = cdns_plat_pcie->pcie->phy_count;
	जबतक (phy_count--)
		device_link_del(cdns_plat_pcie->pcie->link[phy_count]);

	वापस 0;
पूर्ण

अटल व्योम cdns_plat_pcie_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cdns_pcie *pcie = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pm_runसमय_put_sync(dev);
	अगर (ret < 0)
		dev_dbg(dev, "pm_runtime_put_sync failed\n");

	pm_runसमय_disable(dev);

	cdns_pcie_disable_phy(pcie);
पूर्ण

अटल स्थिर काष्ठा cdns_plat_pcie_of_data cdns_plat_pcie_host_of_data = अणु
	.is_rc = true,
पूर्ण;

अटल स्थिर काष्ठा cdns_plat_pcie_of_data cdns_plat_pcie_ep_of_data = अणु
	.is_rc = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id cdns_plat_pcie_of_match[] = अणु
	अणु
		.compatible = "cdns,cdns-pcie-host",
		.data = &cdns_plat_pcie_host_of_data,
	पूर्ण,
	अणु
		.compatible = "cdns,cdns-pcie-ep",
		.data = &cdns_plat_pcie_ep_of_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver cdns_plat_pcie_driver = अणु
	.driver = अणु
		.name = "cdns-pcie",
		.of_match_table = cdns_plat_pcie_of_match,
		.pm	= &cdns_pcie_pm_ops,
	पूर्ण,
	.probe = cdns_plat_pcie_probe,
	.shutकरोwn = cdns_plat_pcie_shutकरोwn,
पूर्ण;
builtin_platक्रमm_driver(cdns_plat_pcie_driver);
