<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe host controller driver क्रम HiSilicon STB SoCs
 *
 * Copyright (C) 2016-2017 HiSilicon Co., Ltd. http://www.hisilicon.com
 *
 * Authors: Ruqiang Ju <juruqiang@hisilicon.com>
 *          Jianguo Sun <sunjianguo1@huawei.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pci.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/resource.h>
#समावेश <linux/reset.h>

#समावेश "pcie-designware.h"

#घोषणा to_histb_pcie(x)	dev_get_drvdata((x)->dev)

#घोषणा PCIE_SYS_CTRL0			0x0000
#घोषणा PCIE_SYS_CTRL1			0x0004
#घोषणा PCIE_SYS_CTRL7			0x001C
#घोषणा PCIE_SYS_CTRL13			0x0034
#घोषणा PCIE_SYS_CTRL15			0x003C
#घोषणा PCIE_SYS_CTRL16			0x0040
#घोषणा PCIE_SYS_CTRL17			0x0044

#घोषणा PCIE_SYS_STAT0			0x0100
#घोषणा PCIE_SYS_STAT4			0x0110

#घोषणा PCIE_RDLH_LINK_UP		BIT(5)
#घोषणा PCIE_XMLH_LINK_UP		BIT(15)
#घोषणा PCIE_ELBI_SLV_DBI_ENABLE	BIT(21)
#घोषणा PCIE_APP_LTSSM_ENABLE		BIT(11)

#घोषणा PCIE_DEVICE_TYPE_MASK		GENMASK(31, 28)
#घोषणा PCIE_WM_EP			0
#घोषणा PCIE_WM_LEGACY			BIT(1)
#घोषणा PCIE_WM_RC			BIT(30)

#घोषणा PCIE_LTSSM_STATE_MASK		GENMASK(5, 0)
#घोषणा PCIE_LTSSM_STATE_ACTIVE		0x11

काष्ठा histb_pcie अणु
	काष्ठा dw_pcie *pci;
	काष्ठा clk *aux_clk;
	काष्ठा clk *pipe_clk;
	काष्ठा clk *sys_clk;
	काष्ठा clk *bus_clk;
	काष्ठा phy *phy;
	काष्ठा reset_control *soft_reset;
	काष्ठा reset_control *sys_reset;
	काष्ठा reset_control *bus_reset;
	व्योम __iomem *ctrl;
	पूर्णांक reset_gpio;
	काष्ठा regulator *vpcie;
पूर्ण;

अटल u32 histb_pcie_पढ़ोl(काष्ठा histb_pcie *histb_pcie, u32 reg)
अणु
	वापस पढ़ोl(histb_pcie->ctrl + reg);
पूर्ण

अटल व्योम histb_pcie_ग_लिखोl(काष्ठा histb_pcie *histb_pcie, u32 reg, u32 val)
अणु
	ग_लिखोl(val, histb_pcie->ctrl + reg);
पूर्ण

अटल व्योम histb_pcie_dbi_w_mode(काष्ठा pcie_port *pp, bool enable)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा histb_pcie *hipcie = to_histb_pcie(pci);
	u32 val;

	val = histb_pcie_पढ़ोl(hipcie, PCIE_SYS_CTRL0);
	अगर (enable)
		val |= PCIE_ELBI_SLV_DBI_ENABLE;
	अन्यथा
		val &= ~PCIE_ELBI_SLV_DBI_ENABLE;
	histb_pcie_ग_लिखोl(hipcie, PCIE_SYS_CTRL0, val);
पूर्ण

अटल व्योम histb_pcie_dbi_r_mode(काष्ठा pcie_port *pp, bool enable)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा histb_pcie *hipcie = to_histb_pcie(pci);
	u32 val;

	val = histb_pcie_पढ़ोl(hipcie, PCIE_SYS_CTRL1);
	अगर (enable)
		val |= PCIE_ELBI_SLV_DBI_ENABLE;
	अन्यथा
		val &= ~PCIE_ELBI_SLV_DBI_ENABLE;
	histb_pcie_ग_लिखोl(hipcie, PCIE_SYS_CTRL1, val);
पूर्ण

अटल u32 histb_pcie_पढ़ो_dbi(काष्ठा dw_pcie *pci, व्योम __iomem *base,
			       u32 reg, माप_प्रकार size)
अणु
	u32 val;

	histb_pcie_dbi_r_mode(&pci->pp, true);
	dw_pcie_पढ़ो(base + reg, size, &val);
	histb_pcie_dbi_r_mode(&pci->pp, false);

	वापस val;
पूर्ण

अटल व्योम histb_pcie_ग_लिखो_dbi(काष्ठा dw_pcie *pci, व्योम __iomem *base,
				 u32 reg, माप_प्रकार size, u32 val)
अणु
	histb_pcie_dbi_w_mode(&pci->pp, true);
	dw_pcie_ग_लिखो(base + reg, size, val);
	histb_pcie_dbi_w_mode(&pci->pp, false);
पूर्ण

अटल पूर्णांक histb_pcie_rd_own_conf(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				  पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(bus->sysdata);

	अगर (PCI_SLOT(devfn)) अणु
		*val = ~0;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	*val = dw_pcie_पढ़ो_dbi(pci, where, size);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक histb_pcie_wr_own_conf(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				  पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(bus->sysdata);

	अगर (PCI_SLOT(devfn))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	dw_pcie_ग_लिखो_dbi(pci, where, size, val);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops histb_pci_ops = अणु
	.पढ़ो = histb_pcie_rd_own_conf,
	.ग_लिखो = histb_pcie_wr_own_conf,
पूर्ण;

अटल पूर्णांक histb_pcie_link_up(काष्ठा dw_pcie *pci)
अणु
	काष्ठा histb_pcie *hipcie = to_histb_pcie(pci);
	u32 regval;
	u32 status;

	regval = histb_pcie_पढ़ोl(hipcie, PCIE_SYS_STAT0);
	status = histb_pcie_पढ़ोl(hipcie, PCIE_SYS_STAT4);
	status &= PCIE_LTSSM_STATE_MASK;
	अगर ((regval & PCIE_XMLH_LINK_UP) && (regval & PCIE_RDLH_LINK_UP) &&
	    (status == PCIE_LTSSM_STATE_ACTIVE))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक histb_pcie_start_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा histb_pcie *hipcie = to_histb_pcie(pci);
	u32 regval;

	/* निश्चित LTSSM enable */
	regval = histb_pcie_पढ़ोl(hipcie, PCIE_SYS_CTRL7);
	regval |= PCIE_APP_LTSSM_ENABLE;
	histb_pcie_ग_लिखोl(hipcie, PCIE_SYS_CTRL7, regval);

	वापस 0;
पूर्ण

अटल पूर्णांक histb_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा histb_pcie *hipcie = to_histb_pcie(pci);
	u32 regval;

	pp->bridge->ops = &histb_pci_ops;

	/* PCIe RC work mode */
	regval = histb_pcie_पढ़ोl(hipcie, PCIE_SYS_CTRL0);
	regval &= ~PCIE_DEVICE_TYPE_MASK;
	regval |= PCIE_WM_RC;
	histb_pcie_ग_लिखोl(hipcie, PCIE_SYS_CTRL0, regval);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_host_ops histb_pcie_host_ops = अणु
	.host_init = histb_pcie_host_init,
पूर्ण;

अटल व्योम histb_pcie_host_disable(काष्ठा histb_pcie *hipcie)
अणु
	reset_control_निश्चित(hipcie->soft_reset);
	reset_control_निश्चित(hipcie->sys_reset);
	reset_control_निश्चित(hipcie->bus_reset);

	clk_disable_unprepare(hipcie->aux_clk);
	clk_disable_unprepare(hipcie->pipe_clk);
	clk_disable_unprepare(hipcie->sys_clk);
	clk_disable_unprepare(hipcie->bus_clk);

	अगर (gpio_is_valid(hipcie->reset_gpio))
		gpio_set_value_cansleep(hipcie->reset_gpio, 0);

	अगर (hipcie->vpcie)
		regulator_disable(hipcie->vpcie);
पूर्ण

अटल पूर्णांक histb_pcie_host_enable(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा histb_pcie *hipcie = to_histb_pcie(pci);
	काष्ठा device *dev = pci->dev;
	पूर्णांक ret;

	/* घातer on PCIe device अगर have */
	अगर (hipcie->vpcie) अणु
		ret = regulator_enable(hipcie->vpcie);
		अगर (ret) अणु
			dev_err(dev, "failed to enable regulator: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (gpio_is_valid(hipcie->reset_gpio))
		gpio_set_value_cansleep(hipcie->reset_gpio, 1);

	ret = clk_prepare_enable(hipcie->bus_clk);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable bus clk\n");
		जाओ err_bus_clk;
	पूर्ण

	ret = clk_prepare_enable(hipcie->sys_clk);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable sys clk\n");
		जाओ err_sys_clk;
	पूर्ण

	ret = clk_prepare_enable(hipcie->pipe_clk);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable pipe clk\n");
		जाओ err_pipe_clk;
	पूर्ण

	ret = clk_prepare_enable(hipcie->aux_clk);
	अगर (ret) अणु
		dev_err(dev, "cannot prepare/enable aux clk\n");
		जाओ err_aux_clk;
	पूर्ण

	reset_control_निश्चित(hipcie->soft_reset);
	reset_control_deनिश्चित(hipcie->soft_reset);

	reset_control_निश्चित(hipcie->sys_reset);
	reset_control_deनिश्चित(hipcie->sys_reset);

	reset_control_निश्चित(hipcie->bus_reset);
	reset_control_deनिश्चित(hipcie->bus_reset);

	वापस 0;

err_aux_clk:
	clk_disable_unprepare(hipcie->pipe_clk);
err_pipe_clk:
	clk_disable_unprepare(hipcie->sys_clk);
err_sys_clk:
	clk_disable_unprepare(hipcie->bus_clk);
err_bus_clk:
	अगर (hipcie->vpcie)
		regulator_disable(hipcie->vpcie);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ops dw_pcie_ops = अणु
	.पढ़ो_dbi = histb_pcie_पढ़ो_dbi,
	.ग_लिखो_dbi = histb_pcie_ग_लिखो_dbi,
	.link_up = histb_pcie_link_up,
	.start_link = histb_pcie_start_link,
पूर्ण;

अटल पूर्णांक histb_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा histb_pcie *hipcie;
	काष्ठा dw_pcie *pci;
	काष्ठा pcie_port *pp;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	क्रमागत of_gpio_flags of_flags;
	अचिन्हित दीर्घ flag = GPIOF_सूची_OUT;
	पूर्णांक ret;

	hipcie = devm_kzalloc(dev, माप(*hipcie), GFP_KERNEL);
	अगर (!hipcie)
		वापस -ENOMEM;

	pci = devm_kzalloc(dev, माप(*pci), GFP_KERNEL);
	अगर (!pci)
		वापस -ENOMEM;

	hipcie->pci = pci;
	pp = &pci->pp;
	pci->dev = dev;
	pci->ops = &dw_pcie_ops;

	hipcie->ctrl = devm_platक्रमm_ioremap_resource_byname(pdev, "control");
	अगर (IS_ERR(hipcie->ctrl)) अणु
		dev_err(dev, "cannot get control reg base\n");
		वापस PTR_ERR(hipcie->ctrl);
	पूर्ण

	pci->dbi_base = devm_platक्रमm_ioremap_resource_byname(pdev, "rc-dbi");
	अगर (IS_ERR(pci->dbi_base)) अणु
		dev_err(dev, "cannot get rc-dbi base\n");
		वापस PTR_ERR(pci->dbi_base);
	पूर्ण

	hipcie->vpcie = devm_regulator_get_optional(dev, "vpcie");
	अगर (IS_ERR(hipcie->vpcie)) अणु
		अगर (PTR_ERR(hipcie->vpcie) != -ENODEV)
			वापस PTR_ERR(hipcie->vpcie);
		hipcie->vpcie = शून्य;
	पूर्ण

	hipcie->reset_gpio = of_get_named_gpio_flags(np,
				"reset-gpios", 0, &of_flags);
	अगर (of_flags & OF_GPIO_ACTIVE_LOW)
		flag |= GPIOF_ACTIVE_LOW;
	अगर (gpio_is_valid(hipcie->reset_gpio)) अणु
		ret = devm_gpio_request_one(dev, hipcie->reset_gpio,
				flag, "PCIe device power control");
		अगर (ret) अणु
			dev_err(dev, "unable to request gpio\n");
			वापस ret;
		पूर्ण
	पूर्ण

	hipcie->aux_clk = devm_clk_get(dev, "aux");
	अगर (IS_ERR(hipcie->aux_clk)) अणु
		dev_err(dev, "Failed to get PCIe aux clk\n");
		वापस PTR_ERR(hipcie->aux_clk);
	पूर्ण

	hipcie->pipe_clk = devm_clk_get(dev, "pipe");
	अगर (IS_ERR(hipcie->pipe_clk)) अणु
		dev_err(dev, "Failed to get PCIe pipe clk\n");
		वापस PTR_ERR(hipcie->pipe_clk);
	पूर्ण

	hipcie->sys_clk = devm_clk_get(dev, "sys");
	अगर (IS_ERR(hipcie->sys_clk)) अणु
		dev_err(dev, "Failed to get PCIEe sys clk\n");
		वापस PTR_ERR(hipcie->sys_clk);
	पूर्ण

	hipcie->bus_clk = devm_clk_get(dev, "bus");
	अगर (IS_ERR(hipcie->bus_clk)) अणु
		dev_err(dev, "Failed to get PCIe bus clk\n");
		वापस PTR_ERR(hipcie->bus_clk);
	पूर्ण

	hipcie->soft_reset = devm_reset_control_get(dev, "soft");
	अगर (IS_ERR(hipcie->soft_reset)) अणु
		dev_err(dev, "couldn't get soft reset\n");
		वापस PTR_ERR(hipcie->soft_reset);
	पूर्ण

	hipcie->sys_reset = devm_reset_control_get(dev, "sys");
	अगर (IS_ERR(hipcie->sys_reset)) अणु
		dev_err(dev, "couldn't get sys reset\n");
		वापस PTR_ERR(hipcie->sys_reset);
	पूर्ण

	hipcie->bus_reset = devm_reset_control_get(dev, "bus");
	अगर (IS_ERR(hipcie->bus_reset)) अणु
		dev_err(dev, "couldn't get bus reset\n");
		वापस PTR_ERR(hipcie->bus_reset);
	पूर्ण

	hipcie->phy = devm_phy_get(dev, "phy");
	अगर (IS_ERR(hipcie->phy)) अणु
		dev_info(dev, "no pcie-phy found\n");
		hipcie->phy = शून्य;
		/* fall through here!
		 * अगर no pcie-phy found, phy init
		 * should be करोne under boot!
		 */
	पूर्ण अन्यथा अणु
		phy_init(hipcie->phy);
	पूर्ण

	pp->ops = &histb_pcie_host_ops;

	platक्रमm_set_drvdata(pdev, hipcie);

	ret = histb_pcie_host_enable(pp);
	अगर (ret) अणु
		dev_err(dev, "failed to enable host\n");
		वापस ret;
	पूर्ण

	ret = dw_pcie_host_init(pp);
	अगर (ret) अणु
		dev_err(dev, "failed to initialize host\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक histb_pcie_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा histb_pcie *hipcie = platक्रमm_get_drvdata(pdev);

	histb_pcie_host_disable(hipcie);

	अगर (hipcie->phy)
		phy_निकास(hipcie->phy);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id histb_pcie_of_match[] = अणु
	अणु .compatible = "hisilicon,hi3798cv200-pcie", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, histb_pcie_of_match);

अटल काष्ठा platक्रमm_driver histb_pcie_platक्रमm_driver = अणु
	.probe	= histb_pcie_probe,
	.हटाओ	= histb_pcie_हटाओ,
	.driver = अणु
		.name = "histb-pcie",
		.of_match_table = histb_pcie_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(histb_pcie_platक्रमm_driver);

MODULE_DESCRIPTION("HiSilicon STB PCIe host controller driver");
MODULE_LICENSE("GPL v2");
