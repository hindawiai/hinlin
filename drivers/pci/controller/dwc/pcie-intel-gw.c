<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe host controller driver क्रम Intel Gateway SoCs
 *
 * Copyright (c) 2019 Intel Corporation.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश "../../pci.h"
#समावेश "pcie-designware.h"

#घोषणा PORT_AFR_N_FTS_GEN12_DFT	(SZ_128 - 1)
#घोषणा PORT_AFR_N_FTS_GEN3		180
#घोषणा PORT_AFR_N_FTS_GEN4		196

/* PCIe Application logic Registers */
#घोषणा PCIE_APP_CCR			0x10
#घोषणा PCIE_APP_CCR_LTSSM_ENABLE	BIT(0)

#घोषणा PCIE_APP_MSG_CR			0x30
#घोषणा PCIE_APP_MSG_XMT_PM_TURNOFF	BIT(0)

#घोषणा PCIE_APP_PMC			0x44
#घोषणा PCIE_APP_PMC_IN_L2		BIT(20)

#घोषणा PCIE_APP_IRNEN			0xF4
#घोषणा PCIE_APP_IRNCR			0xF8
#घोषणा PCIE_APP_IRN_AER_REPORT		BIT(0)
#घोषणा PCIE_APP_IRN_PME		BIT(2)
#घोषणा PCIE_APP_IRN_RX_VDM_MSG		BIT(4)
#घोषणा PCIE_APP_IRN_PM_TO_ACK		BIT(9)
#घोषणा PCIE_APP_IRN_LINK_AUTO_BW_STAT	BIT(11)
#घोषणा PCIE_APP_IRN_BW_MGT		BIT(12)
#घोषणा PCIE_APP_IRN_MSG_LTR		BIT(18)
#घोषणा PCIE_APP_IRN_SYS_ERR_RC		BIT(29)
#घोषणा PCIE_APP_INTX_OFST		12

#घोषणा PCIE_APP_IRN_INT \
	(PCIE_APP_IRN_AER_REPORT | PCIE_APP_IRN_PME | \
	PCIE_APP_IRN_RX_VDM_MSG | PCIE_APP_IRN_SYS_ERR_RC | \
	PCIE_APP_IRN_PM_TO_ACK | PCIE_APP_IRN_MSG_LTR | \
	PCIE_APP_IRN_BW_MGT | PCIE_APP_IRN_LINK_AUTO_BW_STAT | \
	(PCIE_APP_INTX_OFST + PCI_INTERRUPT_INTA) | \
	(PCIE_APP_INTX_OFST + PCI_INTERRUPT_INTB) | \
	(PCIE_APP_INTX_OFST + PCI_INTERRUPT_INTC) | \
	(PCIE_APP_INTX_OFST + PCI_INTERRUPT_INTD))

#घोषणा BUS_IATU_OFFSET			SZ_256M
#घोषणा RESET_INTERVAL_MS		100

काष्ठा पूर्णांकel_pcie_soc अणु
	अचिन्हित पूर्णांक	pcie_ver;
पूर्ण;

काष्ठा पूर्णांकel_pcie_port अणु
	काष्ठा dw_pcie		pci;
	व्योम __iomem		*app_base;
	काष्ठा gpio_desc	*reset_gpio;
	u32			rst_पूर्णांकrvl;
	काष्ठा clk		*core_clk;
	काष्ठा reset_control	*core_rst;
	काष्ठा phy		*phy;
पूर्ण;

अटल व्योम pcie_update_bits(व्योम __iomem *base, u32 ofs, u32 mask, u32 val)
अणु
	u32 old;

	old = पढ़ोl(base + ofs);
	val = (old & ~mask) | (val & mask);

	अगर (val != old)
		ग_लिखोl(val, base + ofs);
पूर्ण

अटल अंतरभूत व्योम pcie_app_wr(काष्ठा पूर्णांकel_pcie_port *lpp, u32 ofs, u32 val)
अणु
	ग_लिखोl(val, lpp->app_base + ofs);
पूर्ण

अटल व्योम pcie_app_wr_mask(काष्ठा पूर्णांकel_pcie_port *lpp, u32 ofs,
			     u32 mask, u32 val)
अणु
	pcie_update_bits(lpp->app_base, ofs, mask, val);
पूर्ण

अटल अंतरभूत u32 pcie_rc_cfg_rd(काष्ठा पूर्णांकel_pcie_port *lpp, u32 ofs)
अणु
	वापस dw_pcie_पढ़ोl_dbi(&lpp->pci, ofs);
पूर्ण

अटल अंतरभूत व्योम pcie_rc_cfg_wr(काष्ठा पूर्णांकel_pcie_port *lpp, u32 ofs, u32 val)
अणु
	dw_pcie_ग_लिखोl_dbi(&lpp->pci, ofs, val);
पूर्ण

अटल व्योम pcie_rc_cfg_wr_mask(काष्ठा पूर्णांकel_pcie_port *lpp, u32 ofs,
				u32 mask, u32 val)
अणु
	pcie_update_bits(lpp->pci.dbi_base, ofs, mask, val);
पूर्ण

अटल व्योम पूर्णांकel_pcie_ltssm_enable(काष्ठा पूर्णांकel_pcie_port *lpp)
अणु
	pcie_app_wr_mask(lpp, PCIE_APP_CCR, PCIE_APP_CCR_LTSSM_ENABLE,
			 PCIE_APP_CCR_LTSSM_ENABLE);
पूर्ण

अटल व्योम पूर्णांकel_pcie_ltssm_disable(काष्ठा पूर्णांकel_pcie_port *lpp)
अणु
	pcie_app_wr_mask(lpp, PCIE_APP_CCR, PCIE_APP_CCR_LTSSM_ENABLE, 0);
पूर्ण

अटल व्योम पूर्णांकel_pcie_link_setup(काष्ठा पूर्णांकel_pcie_port *lpp)
अणु
	u32 val;
	u8 offset = dw_pcie_find_capability(&lpp->pci, PCI_CAP_ID_EXP);

	val = pcie_rc_cfg_rd(lpp, offset + PCI_EXP_LNKCTL);

	val &= ~(PCI_EXP_LNKCTL_LD | PCI_EXP_LNKCTL_ASPMC);
	pcie_rc_cfg_wr(lpp, offset + PCI_EXP_LNKCTL, val);
पूर्ण

अटल व्योम पूर्णांकel_pcie_init_n_fts(काष्ठा dw_pcie *pci)
अणु
	चयन (pci->link_gen) अणु
	हाल 3:
		pci->n_fts[1] = PORT_AFR_N_FTS_GEN3;
		अवरोध;
	हाल 4:
		pci->n_fts[1] = PORT_AFR_N_FTS_GEN4;
		अवरोध;
	शेष:
		pci->n_fts[1] = PORT_AFR_N_FTS_GEN12_DFT;
		अवरोध;
	पूर्ण
	pci->n_fts[0] = PORT_AFR_N_FTS_GEN12_DFT;
पूर्ण

अटल पूर्णांक पूर्णांकel_pcie_ep_rst_init(काष्ठा पूर्णांकel_pcie_port *lpp)
अणु
	काष्ठा device *dev = lpp->pci.dev;
	पूर्णांक ret;

	lpp->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(lpp->reset_gpio)) अणु
		ret = PTR_ERR(lpp->reset_gpio);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to request PCIe GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Make initial reset last क्रम 100us */
	usleep_range(100, 200);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_pcie_core_rst_निश्चित(काष्ठा पूर्णांकel_pcie_port *lpp)
अणु
	reset_control_निश्चित(lpp->core_rst);
पूर्ण

अटल व्योम पूर्णांकel_pcie_core_rst_deनिश्चित(काष्ठा पूर्णांकel_pcie_port *lpp)
अणु
	/*
	 * One micro-second delay to make sure the reset pulse
	 * wide enough so that core reset is clean.
	 */
	udelay(1);
	reset_control_deनिश्चित(lpp->core_rst);

	/*
	 * Some SoC core reset also reset PHY, more delay needed
	 * to make sure the reset process is करोne.
	 */
	usleep_range(1000, 2000);
पूर्ण

अटल व्योम पूर्णांकel_pcie_device_rst_निश्चित(काष्ठा पूर्णांकel_pcie_port *lpp)
अणु
	gpiod_set_value_cansleep(lpp->reset_gpio, 1);
पूर्ण

अटल व्योम पूर्णांकel_pcie_device_rst_deनिश्चित(काष्ठा पूर्णांकel_pcie_port *lpp)
अणु
	msleep(lpp->rst_पूर्णांकrvl);
	gpiod_set_value_cansleep(lpp->reset_gpio, 0);
पूर्ण

अटल व्योम पूर्णांकel_pcie_core_irq_disable(काष्ठा पूर्णांकel_pcie_port *lpp)
अणु
	pcie_app_wr(lpp, PCIE_APP_IRNEN, 0);
	pcie_app_wr(lpp, PCIE_APP_IRNCR, PCIE_APP_IRN_INT);
पूर्ण

अटल पूर्णांक पूर्णांकel_pcie_get_resources(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_pcie_port *lpp = platक्रमm_get_drvdata(pdev);
	काष्ठा dw_pcie *pci = &lpp->pci;
	काष्ठा device *dev = pci->dev;
	पूर्णांक ret;

	lpp->core_clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(lpp->core_clk)) अणु
		ret = PTR_ERR(lpp->core_clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get clks: %d\n", ret);
		वापस ret;
	पूर्ण

	lpp->core_rst = devm_reset_control_get(dev, शून्य);
	अगर (IS_ERR(lpp->core_rst)) अणु
		ret = PTR_ERR(lpp->core_rst);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get resets: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = device_property_पढ़ो_u32(dev, "reset-assert-ms",
				       &lpp->rst_पूर्णांकrvl);
	अगर (ret)
		lpp->rst_पूर्णांकrvl = RESET_INTERVAL_MS;

	lpp->app_base = devm_platक्रमm_ioremap_resource_byname(pdev, "app");
	अगर (IS_ERR(lpp->app_base))
		वापस PTR_ERR(lpp->app_base);

	lpp->phy = devm_phy_get(dev, "pcie");
	अगर (IS_ERR(lpp->phy)) अणु
		ret = PTR_ERR(lpp->phy);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Couldn't get pcie-phy: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pcie_रुको_l2(काष्ठा पूर्णांकel_pcie_port *lpp)
अणु
	u32 value;
	पूर्णांक ret;
	काष्ठा dw_pcie *pci = &lpp->pci;

	अगर (pci->link_gen < 3)
		वापस 0;

	/* Send PME_TURN_OFF message */
	pcie_app_wr_mask(lpp, PCIE_APP_MSG_CR, PCIE_APP_MSG_XMT_PM_TURNOFF,
			 PCIE_APP_MSG_XMT_PM_TURNOFF);

	/* Read PMC status and रुको क्रम falling पूर्णांकo L2 link state */
	ret = पढ़ोl_poll_समयout(lpp->app_base + PCIE_APP_PMC, value,
				 value & PCIE_APP_PMC_IN_L2, 20,
				 jअगरfies_to_usecs(5 * HZ));
	अगर (ret)
		dev_err(lpp->pci.dev, "PCIe link enter L2 timeout!\n");

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_pcie_turn_off(काष्ठा पूर्णांकel_pcie_port *lpp)
अणु
	अगर (dw_pcie_link_up(&lpp->pci))
		पूर्णांकel_pcie_रुको_l2(lpp);

	/* Put endpoपूर्णांक device in reset state */
	पूर्णांकel_pcie_device_rst_निश्चित(lpp);
	pcie_rc_cfg_wr_mask(lpp, PCI_COMMAND, PCI_COMMAND_MEMORY, 0);
पूर्ण

अटल पूर्णांक पूर्णांकel_pcie_host_setup(काष्ठा पूर्णांकel_pcie_port *lpp)
अणु
	पूर्णांक ret;
	काष्ठा dw_pcie *pci = &lpp->pci;

	पूर्णांकel_pcie_core_rst_निश्चित(lpp);
	पूर्णांकel_pcie_device_rst_निश्चित(lpp);

	ret = phy_init(lpp->phy);
	अगर (ret)
		वापस ret;

	पूर्णांकel_pcie_core_rst_deनिश्चित(lpp);

	ret = clk_prepare_enable(lpp->core_clk);
	अगर (ret) अणु
		dev_err(lpp->pci.dev, "Core clock enable failed: %d\n", ret);
		जाओ clk_err;
	पूर्ण

	pci->atu_base = pci->dbi_base + 0xC0000;

	पूर्णांकel_pcie_ltssm_disable(lpp);
	पूर्णांकel_pcie_link_setup(lpp);
	पूर्णांकel_pcie_init_n_fts(pci);
	dw_pcie_setup_rc(&pci->pp);
	dw_pcie_upconfig_setup(pci);

	पूर्णांकel_pcie_device_rst_deनिश्चित(lpp);
	पूर्णांकel_pcie_ltssm_enable(lpp);

	ret = dw_pcie_रुको_क्रम_link(pci);
	अगर (ret)
		जाओ app_init_err;

	/* Enable पूर्णांकegrated पूर्णांकerrupts */
	pcie_app_wr_mask(lpp, PCIE_APP_IRNEN, PCIE_APP_IRN_INT,
			 PCIE_APP_IRN_INT);

	वापस 0;

app_init_err:
	clk_disable_unprepare(lpp->core_clk);
clk_err:
	पूर्णांकel_pcie_core_rst_निश्चित(lpp);
	phy_निकास(lpp->phy);

	वापस ret;
पूर्ण

अटल व्योम __पूर्णांकel_pcie_हटाओ(काष्ठा पूर्णांकel_pcie_port *lpp)
अणु
	पूर्णांकel_pcie_core_irq_disable(lpp);
	पूर्णांकel_pcie_turn_off(lpp);
	clk_disable_unprepare(lpp->core_clk);
	पूर्णांकel_pcie_core_rst_निश्चित(lpp);
	phy_निकास(lpp->phy);
पूर्ण

अटल पूर्णांक पूर्णांकel_pcie_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_pcie_port *lpp = platक्रमm_get_drvdata(pdev);
	काष्ठा pcie_port *pp = &lpp->pci.pp;

	dw_pcie_host_deinit(pp);
	__पूर्णांकel_pcie_हटाओ(lpp);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused पूर्णांकel_pcie_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_pcie_port *lpp = dev_get_drvdata(dev);
	पूर्णांक ret;

	पूर्णांकel_pcie_core_irq_disable(lpp);
	ret = पूर्णांकel_pcie_रुको_l2(lpp);
	अगर (ret)
		वापस ret;

	phy_निकास(lpp->phy);
	clk_disable_unprepare(lpp->core_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused पूर्णांकel_pcie_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_pcie_port *lpp = dev_get_drvdata(dev);

	वापस पूर्णांकel_pcie_host_setup(lpp);
पूर्ण

अटल पूर्णांक पूर्णांकel_pcie_rc_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा पूर्णांकel_pcie_port *lpp = dev_get_drvdata(pci->dev);

	वापस पूर्णांकel_pcie_host_setup(lpp);
पूर्ण

अटल u64 पूर्णांकel_pcie_cpu_addr(काष्ठा dw_pcie *pcie, u64 cpu_addr)
अणु
	वापस cpu_addr + BUS_IATU_OFFSET;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ops पूर्णांकel_pcie_ops = अणु
	.cpu_addr_fixup = पूर्णांकel_pcie_cpu_addr,
पूर्ण;

अटल स्थिर काष्ठा dw_pcie_host_ops पूर्णांकel_pcie_dw_ops = अणु
	.host_init =		पूर्णांकel_pcie_rc_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pcie_soc pcie_data = अणु
	.pcie_ver =		0x520A,
पूर्ण;

अटल पूर्णांक पूर्णांकel_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा पूर्णांकel_pcie_soc *data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा पूर्णांकel_pcie_port *lpp;
	काष्ठा pcie_port *pp;
	काष्ठा dw_pcie *pci;
	पूर्णांक ret;

	lpp = devm_kzalloc(dev, माप(*lpp), GFP_KERNEL);
	अगर (!lpp)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, lpp);
	pci = &lpp->pci;
	pci->dev = dev;
	pp = &pci->pp;

	ret = पूर्णांकel_pcie_get_resources(pdev);
	अगर (ret)
		वापस ret;

	ret = पूर्णांकel_pcie_ep_rst_init(lpp);
	अगर (ret)
		वापस ret;

	data = device_get_match_data(dev);
	अगर (!data)
		वापस -ENODEV;

	pci->ops = &पूर्णांकel_pcie_ops;
	pci->version = data->pcie_ver;
	pp->ops = &पूर्णांकel_pcie_dw_ops;

	ret = dw_pcie_host_init(pp);
	अगर (ret) अणु
		dev_err(dev, "Cannot initialize host\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops पूर्णांकel_pcie_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(पूर्णांकel_pcie_suspend_noirq,
				      पूर्णांकel_pcie_resume_noirq)
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_पूर्णांकel_pcie_match[] = अणु
	अणु .compatible = "intel,lgm-pcie", .data = &pcie_data पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver पूर्णांकel_pcie_driver = अणु
	.probe = पूर्णांकel_pcie_probe,
	.हटाओ = पूर्णांकel_pcie_हटाओ,
	.driver = अणु
		.name = "intel-gw-pcie",
		.of_match_table = of_पूर्णांकel_pcie_match,
		.pm = &पूर्णांकel_pcie_pm_ops,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(पूर्णांकel_pcie_driver);
