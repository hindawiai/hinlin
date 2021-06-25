<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe host controller driver क्रम Kirin Phone SoCs
 *
 * Copyright (C) 2017 HiSilicon Electronics Co., Ltd.
 *		https://www.huawei.com
 *
 * Author: Xiaowei Song <songxiaowei@huawei.com>
 */

#समावेश <linux/compiler.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/resource.h>
#समावेश <linux/types.h>
#समावेश "pcie-designware.h"

#घोषणा to_kirin_pcie(x) dev_get_drvdata((x)->dev)

#घोषणा REF_CLK_FREQ			100000000

/* PCIe ELBI रेजिस्टरs */
#घोषणा SOC_PCIECTRL_CTRL0_ADDR		0x000
#घोषणा SOC_PCIECTRL_CTRL1_ADDR		0x004
#घोषणा SOC_PCIEPHY_CTRL2_ADDR		0x008
#घोषणा SOC_PCIEPHY_CTRL3_ADDR		0x00c
#घोषणा PCIE_ELBI_SLV_DBI_ENABLE	(0x1 << 21)

/* info located in APB */
#घोषणा PCIE_APP_LTSSM_ENABLE	0x01c
#घोषणा PCIE_APB_PHY_CTRL0	0x0
#घोषणा PCIE_APB_PHY_CTRL1	0x4
#घोषणा PCIE_APB_PHY_STATUS0	0x400
#घोषणा PCIE_LINKUP_ENABLE	(0x8020)
#घोषणा PCIE_LTSSM_ENABLE_BIT	(0x1 << 11)
#घोषणा PIPE_CLK_STABLE		(0x1 << 19)
#घोषणा PHY_REF_PAD_BIT		(0x1 << 8)
#घोषणा PHY_PWR_DOWN_BIT	(0x1 << 22)
#घोषणा PHY_RST_ACK_BIT		(0x1 << 16)

/* info located in sysctrl */
#घोषणा SCTRL_PCIE_CMOS_OFFSET	0x60
#घोषणा SCTRL_PCIE_CMOS_BIT	0x10
#घोषणा SCTRL_PCIE_ISO_OFFSET	0x44
#घोषणा SCTRL_PCIE_ISO_BIT	0x30
#घोषणा SCTRL_PCIE_HPCLK_OFFSET	0x190
#घोषणा SCTRL_PCIE_HPCLK_BIT	0x184000
#घोषणा SCTRL_PCIE_OE_OFFSET	0x14a
#घोषणा PCIE_DEBOUNCE_PARAM	0xF0F400
#घोषणा PCIE_OE_BYPASS		(0x3 << 28)

/* peri_crg ctrl */
#घोषणा CRGCTRL_PCIE_ASSERT_OFFSET	0x88
#घोषणा CRGCTRL_PCIE_ASSERT_BIT		0x8c000000

/* Time क्रम delay */
#घोषणा REF_2_PERST_MIN		20000
#घोषणा REF_2_PERST_MAX		25000
#घोषणा PERST_2_ACCESS_MIN	10000
#घोषणा PERST_2_ACCESS_MAX	12000
#घोषणा LINK_WAIT_MIN		900
#घोषणा LINK_WAIT_MAX		1000
#घोषणा PIPE_CLK_WAIT_MIN	550
#घोषणा PIPE_CLK_WAIT_MAX	600
#घोषणा TIME_CMOS_MIN		100
#घोषणा TIME_CMOS_MAX		105
#घोषणा TIME_PHY_PD_MIN		10
#घोषणा TIME_PHY_PD_MAX		11

काष्ठा kirin_pcie अणु
	काष्ठा dw_pcie	*pci;
	व्योम __iomem	*apb_base;
	व्योम __iomem	*phy_base;
	काष्ठा regmap	*crgctrl;
	काष्ठा regmap	*sysctrl;
	काष्ठा clk	*apb_sys_clk;
	काष्ठा clk	*apb_phy_clk;
	काष्ठा clk	*phy_ref_clk;
	काष्ठा clk	*pcie_aclk;
	काष्ठा clk	*pcie_aux_clk;
	पूर्णांक		gpio_id_reset;
पूर्ण;

/* Registers in PCIeCTRL */
अटल अंतरभूत व्योम kirin_apb_ctrl_ग_लिखोl(काष्ठा kirin_pcie *kirin_pcie,
					 u32 val, u32 reg)
अणु
	ग_लिखोl(val, kirin_pcie->apb_base + reg);
पूर्ण

अटल अंतरभूत u32 kirin_apb_ctrl_पढ़ोl(काष्ठा kirin_pcie *kirin_pcie, u32 reg)
अणु
	वापस पढ़ोl(kirin_pcie->apb_base + reg);
पूर्ण

/* Registers in PCIePHY */
अटल अंतरभूत व्योम kirin_apb_phy_ग_लिखोl(काष्ठा kirin_pcie *kirin_pcie,
					u32 val, u32 reg)
अणु
	ग_लिखोl(val, kirin_pcie->phy_base + reg);
पूर्ण

अटल अंतरभूत u32 kirin_apb_phy_पढ़ोl(काष्ठा kirin_pcie *kirin_pcie, u32 reg)
अणु
	वापस पढ़ोl(kirin_pcie->phy_base + reg);
पूर्ण

अटल दीर्घ kirin_pcie_get_clk(काष्ठा kirin_pcie *kirin_pcie,
			       काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	kirin_pcie->phy_ref_clk = devm_clk_get(dev, "pcie_phy_ref");
	अगर (IS_ERR(kirin_pcie->phy_ref_clk))
		वापस PTR_ERR(kirin_pcie->phy_ref_clk);

	kirin_pcie->pcie_aux_clk = devm_clk_get(dev, "pcie_aux");
	अगर (IS_ERR(kirin_pcie->pcie_aux_clk))
		वापस PTR_ERR(kirin_pcie->pcie_aux_clk);

	kirin_pcie->apb_phy_clk = devm_clk_get(dev, "pcie_apb_phy");
	अगर (IS_ERR(kirin_pcie->apb_phy_clk))
		वापस PTR_ERR(kirin_pcie->apb_phy_clk);

	kirin_pcie->apb_sys_clk = devm_clk_get(dev, "pcie_apb_sys");
	अगर (IS_ERR(kirin_pcie->apb_sys_clk))
		वापस PTR_ERR(kirin_pcie->apb_sys_clk);

	kirin_pcie->pcie_aclk = devm_clk_get(dev, "pcie_aclk");
	अगर (IS_ERR(kirin_pcie->pcie_aclk))
		वापस PTR_ERR(kirin_pcie->pcie_aclk);

	वापस 0;
पूर्ण

अटल दीर्घ kirin_pcie_get_resource(काष्ठा kirin_pcie *kirin_pcie,
				    काष्ठा platक्रमm_device *pdev)
अणु
	kirin_pcie->apb_base =
		devm_platक्रमm_ioremap_resource_byname(pdev, "apb");
	अगर (IS_ERR(kirin_pcie->apb_base))
		वापस PTR_ERR(kirin_pcie->apb_base);

	kirin_pcie->phy_base =
		devm_platक्रमm_ioremap_resource_byname(pdev, "phy");
	अगर (IS_ERR(kirin_pcie->phy_base))
		वापस PTR_ERR(kirin_pcie->phy_base);

	kirin_pcie->crgctrl =
		syscon_regmap_lookup_by_compatible("hisilicon,hi3660-crgctrl");
	अगर (IS_ERR(kirin_pcie->crgctrl))
		वापस PTR_ERR(kirin_pcie->crgctrl);

	kirin_pcie->sysctrl =
		syscon_regmap_lookup_by_compatible("hisilicon,hi3660-sctrl");
	अगर (IS_ERR(kirin_pcie->sysctrl))
		वापस PTR_ERR(kirin_pcie->sysctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक kirin_pcie_phy_init(काष्ठा kirin_pcie *kirin_pcie)
अणु
	काष्ठा device *dev = kirin_pcie->pci->dev;
	u32 reg_val;

	reg_val = kirin_apb_phy_पढ़ोl(kirin_pcie, PCIE_APB_PHY_CTRL1);
	reg_val &= ~PHY_REF_PAD_BIT;
	kirin_apb_phy_ग_लिखोl(kirin_pcie, reg_val, PCIE_APB_PHY_CTRL1);

	reg_val = kirin_apb_phy_पढ़ोl(kirin_pcie, PCIE_APB_PHY_CTRL0);
	reg_val &= ~PHY_PWR_DOWN_BIT;
	kirin_apb_phy_ग_लिखोl(kirin_pcie, reg_val, PCIE_APB_PHY_CTRL0);
	usleep_range(TIME_PHY_PD_MIN, TIME_PHY_PD_MAX);

	reg_val = kirin_apb_phy_पढ़ोl(kirin_pcie, PCIE_APB_PHY_CTRL1);
	reg_val &= ~PHY_RST_ACK_BIT;
	kirin_apb_phy_ग_लिखोl(kirin_pcie, reg_val, PCIE_APB_PHY_CTRL1);

	usleep_range(PIPE_CLK_WAIT_MIN, PIPE_CLK_WAIT_MAX);
	reg_val = kirin_apb_phy_पढ़ोl(kirin_pcie, PCIE_APB_PHY_STATUS0);
	अगर (reg_val & PIPE_CLK_STABLE) अणु
		dev_err(dev, "PIPE clk is not stable\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम kirin_pcie_oe_enable(काष्ठा kirin_pcie *kirin_pcie)
अणु
	u32 val;

	regmap_पढ़ो(kirin_pcie->sysctrl, SCTRL_PCIE_OE_OFFSET, &val);
	val |= PCIE_DEBOUNCE_PARAM;
	val &= ~PCIE_OE_BYPASS;
	regmap_ग_लिखो(kirin_pcie->sysctrl, SCTRL_PCIE_OE_OFFSET, val);
पूर्ण

अटल पूर्णांक kirin_pcie_clk_ctrl(काष्ठा kirin_pcie *kirin_pcie, bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (!enable)
		जाओ बंद_clk;

	ret = clk_set_rate(kirin_pcie->phy_ref_clk, REF_CLK_FREQ);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(kirin_pcie->phy_ref_clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(kirin_pcie->apb_sys_clk);
	अगर (ret)
		जाओ apb_sys_fail;

	ret = clk_prepare_enable(kirin_pcie->apb_phy_clk);
	अगर (ret)
		जाओ apb_phy_fail;

	ret = clk_prepare_enable(kirin_pcie->pcie_aclk);
	अगर (ret)
		जाओ aclk_fail;

	ret = clk_prepare_enable(kirin_pcie->pcie_aux_clk);
	अगर (ret)
		जाओ aux_clk_fail;

	वापस 0;

बंद_clk:
	clk_disable_unprepare(kirin_pcie->pcie_aux_clk);
aux_clk_fail:
	clk_disable_unprepare(kirin_pcie->pcie_aclk);
aclk_fail:
	clk_disable_unprepare(kirin_pcie->apb_phy_clk);
apb_phy_fail:
	clk_disable_unprepare(kirin_pcie->apb_sys_clk);
apb_sys_fail:
	clk_disable_unprepare(kirin_pcie->phy_ref_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक kirin_pcie_घातer_on(काष्ठा kirin_pcie *kirin_pcie)
अणु
	पूर्णांक ret;

	/* Power supply क्रम Host */
	regmap_ग_लिखो(kirin_pcie->sysctrl,
		     SCTRL_PCIE_CMOS_OFFSET, SCTRL_PCIE_CMOS_BIT);
	usleep_range(TIME_CMOS_MIN, TIME_CMOS_MAX);
	kirin_pcie_oe_enable(kirin_pcie);

	ret = kirin_pcie_clk_ctrl(kirin_pcie, true);
	अगर (ret)
		वापस ret;

	/* ISO disable, PCIeCtrl, PHY निश्चित and clk gate clear */
	regmap_ग_लिखो(kirin_pcie->sysctrl,
		     SCTRL_PCIE_ISO_OFFSET, SCTRL_PCIE_ISO_BIT);
	regmap_ग_लिखो(kirin_pcie->crgctrl,
		     CRGCTRL_PCIE_ASSERT_OFFSET, CRGCTRL_PCIE_ASSERT_BIT);
	regmap_ग_लिखो(kirin_pcie->sysctrl,
		     SCTRL_PCIE_HPCLK_OFFSET, SCTRL_PCIE_HPCLK_BIT);

	ret = kirin_pcie_phy_init(kirin_pcie);
	अगर (ret)
		जाओ बंद_clk;

	/* perst निश्चित Endpoपूर्णांक */
	अगर (!gpio_request(kirin_pcie->gpio_id_reset, "pcie_perst")) अणु
		usleep_range(REF_2_PERST_MIN, REF_2_PERST_MAX);
		ret = gpio_direction_output(kirin_pcie->gpio_id_reset, 1);
		अगर (ret)
			जाओ बंद_clk;
		usleep_range(PERST_2_ACCESS_MIN, PERST_2_ACCESS_MAX);

		वापस 0;
	पूर्ण

बंद_clk:
	kirin_pcie_clk_ctrl(kirin_pcie, false);
	वापस ret;
पूर्ण

अटल व्योम kirin_pcie_sideband_dbi_w_mode(काष्ठा kirin_pcie *kirin_pcie,
					   bool on)
अणु
	u32 val;

	val = kirin_apb_ctrl_पढ़ोl(kirin_pcie, SOC_PCIECTRL_CTRL0_ADDR);
	अगर (on)
		val = val | PCIE_ELBI_SLV_DBI_ENABLE;
	अन्यथा
		val = val & ~PCIE_ELBI_SLV_DBI_ENABLE;

	kirin_apb_ctrl_ग_लिखोl(kirin_pcie, val, SOC_PCIECTRL_CTRL0_ADDR);
पूर्ण

अटल व्योम kirin_pcie_sideband_dbi_r_mode(काष्ठा kirin_pcie *kirin_pcie,
					   bool on)
अणु
	u32 val;

	val = kirin_apb_ctrl_पढ़ोl(kirin_pcie, SOC_PCIECTRL_CTRL1_ADDR);
	अगर (on)
		val = val | PCIE_ELBI_SLV_DBI_ENABLE;
	अन्यथा
		val = val & ~PCIE_ELBI_SLV_DBI_ENABLE;

	kirin_apb_ctrl_ग_लिखोl(kirin_pcie, val, SOC_PCIECTRL_CTRL1_ADDR);
पूर्ण

अटल पूर्णांक kirin_pcie_rd_own_conf(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
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

अटल पूर्णांक kirin_pcie_wr_own_conf(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				  पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(bus->sysdata);

	अगर (PCI_SLOT(devfn))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	dw_pcie_ग_लिखो_dbi(pci, where, size, val);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops kirin_pci_ops = अणु
	.पढ़ो = kirin_pcie_rd_own_conf,
	.ग_लिखो = kirin_pcie_wr_own_conf,
पूर्ण;

अटल u32 kirin_pcie_पढ़ो_dbi(काष्ठा dw_pcie *pci, व्योम __iomem *base,
			       u32 reg, माप_प्रकार size)
अणु
	काष्ठा kirin_pcie *kirin_pcie = to_kirin_pcie(pci);
	u32 ret;

	kirin_pcie_sideband_dbi_r_mode(kirin_pcie, true);
	dw_pcie_पढ़ो(base + reg, size, &ret);
	kirin_pcie_sideband_dbi_r_mode(kirin_pcie, false);

	वापस ret;
पूर्ण

अटल व्योम kirin_pcie_ग_लिखो_dbi(काष्ठा dw_pcie *pci, व्योम __iomem *base,
				 u32 reg, माप_प्रकार size, u32 val)
अणु
	काष्ठा kirin_pcie *kirin_pcie = to_kirin_pcie(pci);

	kirin_pcie_sideband_dbi_w_mode(kirin_pcie, true);
	dw_pcie_ग_लिखो(base + reg, size, val);
	kirin_pcie_sideband_dbi_w_mode(kirin_pcie, false);
पूर्ण

अटल पूर्णांक kirin_pcie_link_up(काष्ठा dw_pcie *pci)
अणु
	काष्ठा kirin_pcie *kirin_pcie = to_kirin_pcie(pci);
	u32 val = kirin_apb_ctrl_पढ़ोl(kirin_pcie, PCIE_APB_PHY_STATUS0);

	अगर ((val & PCIE_LINKUP_ENABLE) == PCIE_LINKUP_ENABLE)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक kirin_pcie_start_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा kirin_pcie *kirin_pcie = to_kirin_pcie(pci);

	/* निश्चित LTSSM enable */
	kirin_apb_ctrl_ग_लिखोl(kirin_pcie, PCIE_LTSSM_ENABLE_BIT,
			      PCIE_APP_LTSSM_ENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक kirin_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	pp->bridge->ops = &kirin_pci_ops;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ops kirin_dw_pcie_ops = अणु
	.पढ़ो_dbi = kirin_pcie_पढ़ो_dbi,
	.ग_लिखो_dbi = kirin_pcie_ग_लिखो_dbi,
	.link_up = kirin_pcie_link_up,
	.start_link = kirin_pcie_start_link,
पूर्ण;

अटल स्थिर काष्ठा dw_pcie_host_ops kirin_pcie_host_ops = अणु
	.host_init = kirin_pcie_host_init,
पूर्ण;

अटल पूर्णांक kirin_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा kirin_pcie *kirin_pcie;
	काष्ठा dw_pcie *pci;
	पूर्णांक ret;

	अगर (!dev->of_node) अणु
		dev_err(dev, "NULL node\n");
		वापस -EINVAL;
	पूर्ण

	kirin_pcie = devm_kzalloc(dev, माप(काष्ठा kirin_pcie), GFP_KERNEL);
	अगर (!kirin_pcie)
		वापस -ENOMEM;

	pci = devm_kzalloc(dev, माप(*pci), GFP_KERNEL);
	अगर (!pci)
		वापस -ENOMEM;

	pci->dev = dev;
	pci->ops = &kirin_dw_pcie_ops;
	pci->pp.ops = &kirin_pcie_host_ops;
	kirin_pcie->pci = pci;

	ret = kirin_pcie_get_clk(kirin_pcie, pdev);
	अगर (ret)
		वापस ret;

	ret = kirin_pcie_get_resource(kirin_pcie, pdev);
	अगर (ret)
		वापस ret;

	kirin_pcie->gpio_id_reset = of_get_named_gpio(dev->of_node,
						      "reset-gpios", 0);
	अगर (kirin_pcie->gpio_id_reset == -EPROBE_DEFER) अणु
		वापस -EPROBE_DEFER;
	पूर्ण अन्यथा अगर (!gpio_is_valid(kirin_pcie->gpio_id_reset)) अणु
		dev_err(dev, "unable to get a valid gpio pin\n");
		वापस -ENODEV;
	पूर्ण

	ret = kirin_pcie_घातer_on(kirin_pcie);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, kirin_pcie);

	वापस dw_pcie_host_init(&pci->pp);
पूर्ण

अटल स्थिर काष्ठा of_device_id kirin_pcie_match[] = अणु
	अणु .compatible = "hisilicon,kirin960-pcie" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver kirin_pcie_driver = अणु
	.probe			= kirin_pcie_probe,
	.driver			= अणु
		.name			= "kirin-pcie",
		.of_match_table = kirin_pcie_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(kirin_pcie_driver);
