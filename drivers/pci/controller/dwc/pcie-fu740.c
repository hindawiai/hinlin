<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FU740 DesignWare PCIe Controller पूर्णांकegration
 * Copyright (C) 2019-2021 SiFive, Inc.
 * Paul Walmsley
 * Greenसमय Hu
 *
 * Based in part on the i.MX6 PCIe host controller shim which is:
 *
 * Copyright (C) 2013 Kosagi
 *		https://www.kosagi.com
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/resource.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/reset.h>

#समावेश "pcie-designware.h"

#घोषणा to_fu740_pcie(x)	dev_get_drvdata((x)->dev)

काष्ठा fu740_pcie अणु
	काष्ठा dw_pcie pci;
	व्योम __iomem *mgmt_base;
	काष्ठा gpio_desc *reset;
	काष्ठा gpio_desc *pwren;
	काष्ठा clk *pcie_aux;
	काष्ठा reset_control *rst;
पूर्ण;

#घोषणा SIFIVE_DEVICESRESETREG		0x28

#घोषणा PCIEX8MGMT_PERST_N		0x0
#घोषणा PCIEX8MGMT_APP_LTSSM_ENABLE	0x10
#घोषणा PCIEX8MGMT_APP_HOLD_PHY_RST	0x18
#घोषणा PCIEX8MGMT_DEVICE_TYPE		0x708
#घोषणा PCIEX8MGMT_PHY0_CR_PARA_ADDR	0x860
#घोषणा PCIEX8MGMT_PHY0_CR_PARA_RD_EN	0x870
#घोषणा PCIEX8MGMT_PHY0_CR_PARA_RD_DATA	0x878
#घोषणा PCIEX8MGMT_PHY0_CR_PARA_SEL	0x880
#घोषणा PCIEX8MGMT_PHY0_CR_PARA_WR_DATA	0x888
#घोषणा PCIEX8MGMT_PHY0_CR_PARA_WR_EN	0x890
#घोषणा PCIEX8MGMT_PHY0_CR_PARA_ACK	0x898
#घोषणा PCIEX8MGMT_PHY1_CR_PARA_ADDR	0x8a0
#घोषणा PCIEX8MGMT_PHY1_CR_PARA_RD_EN	0x8b0
#घोषणा PCIEX8MGMT_PHY1_CR_PARA_RD_DATA	0x8b8
#घोषणा PCIEX8MGMT_PHY1_CR_PARA_SEL	0x8c0
#घोषणा PCIEX8MGMT_PHY1_CR_PARA_WR_DATA	0x8c8
#घोषणा PCIEX8MGMT_PHY1_CR_PARA_WR_EN	0x8d0
#घोषणा PCIEX8MGMT_PHY1_CR_PARA_ACK	0x8d8

#घोषणा PCIEX8MGMT_PHY_CDR_TRACK_EN	BIT(0)
#घोषणा PCIEX8MGMT_PHY_LOS_THRSHLD	BIT(5)
#घोषणा PCIEX8MGMT_PHY_TERM_EN		BIT(9)
#घोषणा PCIEX8MGMT_PHY_TERM_ACDC	BIT(10)
#घोषणा PCIEX8MGMT_PHY_EN		BIT(11)
#घोषणा PCIEX8MGMT_PHY_INIT_VAL		(PCIEX8MGMT_PHY_CDR_TRACK_EN|\
					 PCIEX8MGMT_PHY_LOS_THRSHLD|\
					 PCIEX8MGMT_PHY_TERM_EN|\
					 PCIEX8MGMT_PHY_TERM_ACDC|\
					 PCIEX8MGMT_PHY_EN)

#घोषणा PCIEX8MGMT_PHY_LANEN_DIG_ASIC_RX_OVRD_IN_3	0x1008
#घोषणा PCIEX8MGMT_PHY_LANE_OFF		0x100
#घोषणा PCIEX8MGMT_PHY_LANE0_BASE	(PCIEX8MGMT_PHY_LANEN_DIG_ASIC_RX_OVRD_IN_3 + 0x100 * 0)
#घोषणा PCIEX8MGMT_PHY_LANE1_BASE	(PCIEX8MGMT_PHY_LANEN_DIG_ASIC_RX_OVRD_IN_3 + 0x100 * 1)
#घोषणा PCIEX8MGMT_PHY_LANE2_BASE	(PCIEX8MGMT_PHY_LANEN_DIG_ASIC_RX_OVRD_IN_3 + 0x100 * 2)
#घोषणा PCIEX8MGMT_PHY_LANE3_BASE	(PCIEX8MGMT_PHY_LANEN_DIG_ASIC_RX_OVRD_IN_3 + 0x100 * 3)

अटल व्योम fu740_pcie_निश्चित_reset(काष्ठा fu740_pcie *afp)
अणु
	/* Assert PERST_N GPIO */
	gpiod_set_value_cansleep(afp->reset, 0);
	/* Assert controller PERST_N */
	ग_लिखोl_relaxed(0x0, afp->mgmt_base + PCIEX8MGMT_PERST_N);
पूर्ण

अटल व्योम fu740_pcie_deनिश्चित_reset(काष्ठा fu740_pcie *afp)
अणु
	/* Deनिश्चित controller PERST_N */
	ग_लिखोl_relaxed(0x1, afp->mgmt_base + PCIEX8MGMT_PERST_N);
	/* Deनिश्चित PERST_N GPIO */
	gpiod_set_value_cansleep(afp->reset, 1);
पूर्ण

अटल व्योम fu740_pcie_घातer_on(काष्ठा fu740_pcie *afp)
अणु
	gpiod_set_value_cansleep(afp->pwren, 1);
	/*
	 * Ensure that PERST has been निश्चितed क्रम at least 100 ms.
	 * Section 2.2 of PCI Express Card Electromechanical Specअगरication
	 * Revision 3.0
	 */
	msleep(100);
पूर्ण

अटल व्योम fu740_pcie_drive_reset(काष्ठा fu740_pcie *afp)
अणु
	fu740_pcie_निश्चित_reset(afp);
	fu740_pcie_घातer_on(afp);
	fu740_pcie_deनिश्चित_reset(afp);
पूर्ण

अटल व्योम fu740_phyregग_लिखो(स्थिर uपूर्णांक8_t phy, स्थिर uपूर्णांक16_t addr,
			      स्थिर uपूर्णांक16_t wrdata, काष्ठा fu740_pcie *afp)
अणु
	काष्ठा device *dev = afp->pci.dev;
	व्योम __iomem *phy_cr_para_addr;
	व्योम __iomem *phy_cr_para_wr_data;
	व्योम __iomem *phy_cr_para_wr_en;
	व्योम __iomem *phy_cr_para_ack;
	पूर्णांक ret, val;

	/* Setup */
	अगर (phy) अणु
		phy_cr_para_addr = afp->mgmt_base + PCIEX8MGMT_PHY1_CR_PARA_ADDR;
		phy_cr_para_wr_data = afp->mgmt_base + PCIEX8MGMT_PHY1_CR_PARA_WR_DATA;
		phy_cr_para_wr_en = afp->mgmt_base + PCIEX8MGMT_PHY1_CR_PARA_WR_EN;
		phy_cr_para_ack = afp->mgmt_base + PCIEX8MGMT_PHY1_CR_PARA_ACK;
	पूर्ण अन्यथा अणु
		phy_cr_para_addr = afp->mgmt_base + PCIEX8MGMT_PHY0_CR_PARA_ADDR;
		phy_cr_para_wr_data = afp->mgmt_base + PCIEX8MGMT_PHY0_CR_PARA_WR_DATA;
		phy_cr_para_wr_en = afp->mgmt_base + PCIEX8MGMT_PHY0_CR_PARA_WR_EN;
		phy_cr_para_ack = afp->mgmt_base + PCIEX8MGMT_PHY0_CR_PARA_ACK;
	पूर्ण

	ग_लिखोl_relaxed(addr, phy_cr_para_addr);
	ग_लिखोl_relaxed(wrdata, phy_cr_para_wr_data);
	ग_लिखोl_relaxed(1, phy_cr_para_wr_en);

	/* Wait क्रम रुको_idle */
	ret = पढ़ोl_poll_समयout(phy_cr_para_ack, val, val, 10, 5000);
	अगर (ret)
		dev_warn(dev, "Wait for wait_idle state failed!\n");

	/* Clear */
	ग_लिखोl_relaxed(0, phy_cr_para_wr_en);

	/* Wait क्रम ~रुको_idle */
	ret = पढ़ोl_poll_समयout(phy_cr_para_ack, val, !val, 10, 5000);
	अगर (ret)
		dev_warn(dev, "Wait for !wait_idle state failed!\n");
पूर्ण

अटल व्योम fu740_pcie_init_phy(काष्ठा fu740_pcie *afp)
अणु
	/* Enable phy cr_para_sel पूर्णांकerfaces */
	ग_लिखोl_relaxed(0x1, afp->mgmt_base + PCIEX8MGMT_PHY0_CR_PARA_SEL);
	ग_लिखोl_relaxed(0x1, afp->mgmt_base + PCIEX8MGMT_PHY1_CR_PARA_SEL);

	/*
	 * Wait 10 cr_para cycles to guarantee that the रेजिस्टरs are पढ़ोy
	 * to be edited.
	 */
	ndelay(10);

	/* Set PHY AC termination mode */
	fu740_phyregग_लिखो(0, PCIEX8MGMT_PHY_LANE0_BASE, PCIEX8MGMT_PHY_INIT_VAL, afp);
	fu740_phyregग_लिखो(0, PCIEX8MGMT_PHY_LANE1_BASE, PCIEX8MGMT_PHY_INIT_VAL, afp);
	fu740_phyregग_लिखो(0, PCIEX8MGMT_PHY_LANE2_BASE, PCIEX8MGMT_PHY_INIT_VAL, afp);
	fu740_phyregग_लिखो(0, PCIEX8MGMT_PHY_LANE3_BASE, PCIEX8MGMT_PHY_INIT_VAL, afp);
	fu740_phyregग_लिखो(1, PCIEX8MGMT_PHY_LANE0_BASE, PCIEX8MGMT_PHY_INIT_VAL, afp);
	fu740_phyregग_लिखो(1, PCIEX8MGMT_PHY_LANE1_BASE, PCIEX8MGMT_PHY_INIT_VAL, afp);
	fu740_phyregग_लिखो(1, PCIEX8MGMT_PHY_LANE2_BASE, PCIEX8MGMT_PHY_INIT_VAL, afp);
	fu740_phyregग_लिखो(1, PCIEX8MGMT_PHY_LANE3_BASE, PCIEX8MGMT_PHY_INIT_VAL, afp);
पूर्ण

अटल पूर्णांक fu740_pcie_start_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा device *dev = pci->dev;
	काष्ठा fu740_pcie *afp = dev_get_drvdata(dev);

	/* Enable LTSSM */
	ग_लिखोl_relaxed(0x1, afp->mgmt_base + PCIEX8MGMT_APP_LTSSM_ENABLE);
	वापस 0;
पूर्ण

अटल पूर्णांक fu740_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा fu740_pcie *afp = to_fu740_pcie(pci);
	काष्ठा device *dev = pci->dev;
	पूर्णांक ret;

	/* Power on reset */
	fu740_pcie_drive_reset(afp);

	/* Enable pcieauxclk */
	ret = clk_prepare_enable(afp->pcie_aux);
	अगर (ret) अणु
		dev_err(dev, "unable to enable pcie_aux clock\n");
		वापस ret;
	पूर्ण

	/*
	 * Assert hold_phy_rst (hold the controller LTSSM in reset after
	 * घातer_up_rst_n क्रम रेजिस्टर programming with cr_para)
	 */
	ग_लिखोl_relaxed(0x1, afp->mgmt_base + PCIEX8MGMT_APP_HOLD_PHY_RST);

	/* Deनिश्चित घातer_up_rst_n */
	ret = reset_control_deनिश्चित(afp->rst);
	अगर (ret) अणु
		dev_err(dev, "unable to deassert pcie_power_up_rst_n\n");
		वापस ret;
	पूर्ण

	fu740_pcie_init_phy(afp);

	/* Disable pcieauxclk */
	clk_disable_unprepare(afp->pcie_aux);
	/* Clear hold_phy_rst */
	ग_लिखोl_relaxed(0x0, afp->mgmt_base + PCIEX8MGMT_APP_HOLD_PHY_RST);
	/* Enable pcieauxclk */
	ret = clk_prepare_enable(afp->pcie_aux);
	/* Set RC mode */
	ग_लिखोl_relaxed(0x4, afp->mgmt_base + PCIEX8MGMT_DEVICE_TYPE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_host_ops fu740_pcie_host_ops = अणु
	.host_init = fu740_pcie_host_init,
पूर्ण;

अटल स्थिर काष्ठा dw_pcie_ops dw_pcie_ops = अणु
	.start_link = fu740_pcie_start_link,
पूर्ण;

अटल पूर्णांक fu740_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dw_pcie *pci;
	काष्ठा fu740_pcie *afp;

	afp = devm_kzalloc(dev, माप(*afp), GFP_KERNEL);
	अगर (!afp)
		वापस -ENOMEM;
	pci = &afp->pci;
	pci->dev = dev;
	pci->ops = &dw_pcie_ops;
	pci->pp.ops = &fu740_pcie_host_ops;

	/* SiFive specअगरic region: mgmt */
	afp->mgmt_base = devm_platक्रमm_ioremap_resource_byname(pdev, "mgmt");
	अगर (IS_ERR(afp->mgmt_base))
		वापस PTR_ERR(afp->mgmt_base);

	/* Fetch GPIOs */
	afp->reset = devm_gpiod_get_optional(dev, "reset-gpios", GPIOD_OUT_LOW);
	अगर (IS_ERR(afp->reset))
		वापस dev_err_probe(dev, PTR_ERR(afp->reset), "unable to get reset-gpios\n");

	afp->pwren = devm_gpiod_get_optional(dev, "pwren-gpios", GPIOD_OUT_LOW);
	अगर (IS_ERR(afp->pwren))
		वापस dev_err_probe(dev, PTR_ERR(afp->pwren), "unable to get pwren-gpios\n");

	/* Fetch घड़ीs */
	afp->pcie_aux = devm_clk_get(dev, "pcie_aux");
	अगर (IS_ERR(afp->pcie_aux))
		वापस dev_err_probe(dev, PTR_ERR(afp->pcie_aux),
					     "pcie_aux clock source missing or invalid\n");

	/* Fetch reset */
	afp->rst = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(afp->rst))
		वापस dev_err_probe(dev, PTR_ERR(afp->rst), "unable to get reset\n");

	platक्रमm_set_drvdata(pdev, afp);

	वापस dw_pcie_host_init(&pci->pp);
पूर्ण

अटल व्योम fu740_pcie_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fu740_pcie *afp = platक्रमm_get_drvdata(pdev);

	/* Bring करोwn link, so bootloader माला_लो clean state in हाल of reboot */
	fu740_pcie_निश्चित_reset(afp);
पूर्ण

अटल स्थिर काष्ठा of_device_id fu740_pcie_of_match[] = अणु
	अणु .compatible = "sifive,fu740-pcie", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver fu740_pcie_driver = अणु
	.driver = अणु
		   .name = "fu740-pcie",
		   .of_match_table = fu740_pcie_of_match,
		   .suppress_bind_attrs = true,
	पूर्ण,
	.probe = fu740_pcie_probe,
	.shutकरोwn = fu740_pcie_shutकरोwn,
पूर्ण;

builtin_platक्रमm_driver(fu740_pcie_driver);
