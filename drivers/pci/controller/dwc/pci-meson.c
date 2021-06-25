<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe host controller driver क्रम Amlogic MESON SoCs
 *
 * Copyright (c) 2018 Amlogic, inc.
 * Author: Yue Wang <yue.wang@amlogic.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/resource.h>
#समावेश <linux/types.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/module.h>

#समावेश "pcie-designware.h"

#घोषणा to_meson_pcie(x) dev_get_drvdata((x)->dev)

#घोषणा PCIE_CAP_MAX_PAYLOAD_SIZE(x)	((x) << 5)
#घोषणा PCIE_CAP_MAX_READ_REQ_SIZE(x)	((x) << 12)

/* PCIe specअगरic config रेजिस्टरs */
#घोषणा PCIE_CFG0			0x0
#घोषणा APP_LTSSM_ENABLE		BIT(7)

#घोषणा PCIE_CFG_STATUS12		0x30
#घोषणा IS_SMLH_LINK_UP(x)		((x) & (1 << 6))
#घोषणा IS_RDLH_LINK_UP(x)		((x) & (1 << 16))
#घोषणा IS_LTSSM_UP(x)			((((x) >> 10) & 0x1f) == 0x11)

#घोषणा PCIE_CFG_STATUS17		0x44
#घोषणा PM_CURRENT_STATE(x)		(((x) >> 7) & 0x1)

#घोषणा WAIT_LINKUP_TIMEOUT		4000
#घोषणा PORT_CLK_RATE			100000000UL
#घोषणा MAX_PAYLOAD_SIZE		256
#घोषणा MAX_READ_REQ_SIZE		256
#घोषणा PCIE_RESET_DELAY		500
#घोषणा PCIE_SHARED_RESET		1
#घोषणा PCIE_NORMAL_RESET		0

क्रमागत pcie_data_rate अणु
	PCIE_GEN1,
	PCIE_GEN2,
	PCIE_GEN3,
	PCIE_GEN4
पूर्ण;

काष्ठा meson_pcie_clk_res अणु
	काष्ठा clk *clk;
	काष्ठा clk *port_clk;
	काष्ठा clk *general_clk;
पूर्ण;

काष्ठा meson_pcie_rc_reset अणु
	काष्ठा reset_control *port;
	काष्ठा reset_control *apb;
पूर्ण;

काष्ठा meson_pcie अणु
	काष्ठा dw_pcie pci;
	व्योम __iomem *cfg_base;
	काष्ठा meson_pcie_clk_res clk_res;
	काष्ठा meson_pcie_rc_reset mrst;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा phy *phy;
पूर्ण;

अटल काष्ठा reset_control *meson_pcie_get_reset(काष्ठा meson_pcie *mp,
						  स्थिर अक्षर *id,
						  u32 reset_type)
अणु
	काष्ठा device *dev = mp->pci.dev;
	काष्ठा reset_control *reset;

	अगर (reset_type == PCIE_SHARED_RESET)
		reset = devm_reset_control_get_shared(dev, id);
	अन्यथा
		reset = devm_reset_control_get(dev, id);

	वापस reset;
पूर्ण

अटल पूर्णांक meson_pcie_get_resets(काष्ठा meson_pcie *mp)
अणु
	काष्ठा meson_pcie_rc_reset *mrst = &mp->mrst;

	mrst->port = meson_pcie_get_reset(mp, "port", PCIE_NORMAL_RESET);
	अगर (IS_ERR(mrst->port))
		वापस PTR_ERR(mrst->port);
	reset_control_deनिश्चित(mrst->port);

	mrst->apb = meson_pcie_get_reset(mp, "apb", PCIE_SHARED_RESET);
	अगर (IS_ERR(mrst->apb))
		वापस PTR_ERR(mrst->apb);
	reset_control_deनिश्चित(mrst->apb);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_pcie_get_mems(काष्ठा platक्रमm_device *pdev,
			       काष्ठा meson_pcie *mp)
अणु
	काष्ठा dw_pcie *pci = &mp->pci;

	pci->dbi_base = devm_platक्रमm_ioremap_resource_byname(pdev, "elbi");
	अगर (IS_ERR(pci->dbi_base))
		वापस PTR_ERR(pci->dbi_base);

	mp->cfg_base = devm_platक्रमm_ioremap_resource_byname(pdev, "cfg");
	अगर (IS_ERR(mp->cfg_base))
		वापस PTR_ERR(mp->cfg_base);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_pcie_घातer_on(काष्ठा meson_pcie *mp)
अणु
	पूर्णांक ret = 0;

	ret = phy_init(mp->phy);
	अगर (ret)
		वापस ret;

	ret = phy_घातer_on(mp->phy);
	अगर (ret) अणु
		phy_निकास(mp->phy);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम meson_pcie_घातer_off(काष्ठा meson_pcie *mp)
अणु
	phy_घातer_off(mp->phy);
	phy_निकास(mp->phy);
पूर्ण

अटल पूर्णांक meson_pcie_reset(काष्ठा meson_pcie *mp)
अणु
	काष्ठा meson_pcie_rc_reset *mrst = &mp->mrst;
	पूर्णांक ret = 0;

	ret = phy_reset(mp->phy);
	अगर (ret)
		वापस ret;

	reset_control_निश्चित(mrst->port);
	reset_control_निश्चित(mrst->apb);
	udelay(PCIE_RESET_DELAY);
	reset_control_deनिश्चित(mrst->port);
	reset_control_deनिश्चित(mrst->apb);
	udelay(PCIE_RESET_DELAY);

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा clk *meson_pcie_probe_घड़ी(काष्ठा device *dev,
						 स्थिर अक्षर *id, u64 rate)
अणु
	काष्ठा clk *clk;
	पूर्णांक ret;

	clk = devm_clk_get(dev, id);
	अगर (IS_ERR(clk))
		वापस clk;

	अगर (rate) अणु
		ret = clk_set_rate(clk, rate);
		अगर (ret) अणु
			dev_err(dev, "set clk rate failed, ret = %d\n", ret);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(dev, "couldn't enable clk\n");
		वापस ERR_PTR(ret);
	पूर्ण

	devm_add_action_or_reset(dev,
				 (व्योम (*) (व्योम *))clk_disable_unprepare,
				 clk);

	वापस clk;
पूर्ण

अटल पूर्णांक meson_pcie_probe_घड़ीs(काष्ठा meson_pcie *mp)
अणु
	काष्ठा device *dev = mp->pci.dev;
	काष्ठा meson_pcie_clk_res *res = &mp->clk_res;

	res->port_clk = meson_pcie_probe_घड़ी(dev, "port", PORT_CLK_RATE);
	अगर (IS_ERR(res->port_clk))
		वापस PTR_ERR(res->port_clk);

	res->general_clk = meson_pcie_probe_घड़ी(dev, "general", 0);
	अगर (IS_ERR(res->general_clk))
		वापस PTR_ERR(res->general_clk);

	res->clk = meson_pcie_probe_घड़ी(dev, "pclk", 0);
	अगर (IS_ERR(res->clk))
		वापस PTR_ERR(res->clk);

	वापस 0;
पूर्ण

अटल अंतरभूत u32 meson_cfg_पढ़ोl(काष्ठा meson_pcie *mp, u32 reg)
अणु
	वापस पढ़ोl(mp->cfg_base + reg);
पूर्ण

अटल अंतरभूत व्योम meson_cfg_ग_लिखोl(काष्ठा meson_pcie *mp, u32 val, u32 reg)
अणु
	ग_लिखोl(val, mp->cfg_base + reg);
पूर्ण

अटल व्योम meson_pcie_निश्चित_reset(काष्ठा meson_pcie *mp)
अणु
	gpiod_set_value_cansleep(mp->reset_gpio, 1);
	udelay(500);
	gpiod_set_value_cansleep(mp->reset_gpio, 0);
पूर्ण

अटल व्योम meson_pcie_ltssm_enable(काष्ठा meson_pcie *mp)
अणु
	u32 val;

	val = meson_cfg_पढ़ोl(mp, PCIE_CFG0);
	val |= APP_LTSSM_ENABLE;
	meson_cfg_ग_लिखोl(mp, val, PCIE_CFG0);
पूर्ण

अटल पूर्णांक meson_माप_प्रकारo_payload(काष्ठा meson_pcie *mp, पूर्णांक size)
अणु
	काष्ठा device *dev = mp->pci.dev;

	/*
	 * dwc supports 2^(val+7) payload size, which val is 0~5 शेष to 1.
	 * So अगर input size is not 2^order alignment or less than 2^7 or bigger
	 * than 2^12, just set to शेष size 2^(1+7).
	 */
	अगर (!is_घातer_of_2(size) || size < 128 || size > 4096) अणु
		dev_warn(dev, "payload size %d, set to default 256\n", size);
		वापस 1;
	पूर्ण

	वापस fls(size) - 8;
पूर्ण

अटल व्योम meson_set_max_payload(काष्ठा meson_pcie *mp, पूर्णांक size)
अणु
	काष्ठा dw_pcie *pci = &mp->pci;
	u32 val;
	u16 offset = dw_pcie_find_capability(pci, PCI_CAP_ID_EXP);
	पूर्णांक max_payload_size = meson_माप_प्रकारo_payload(mp, size);

	val = dw_pcie_पढ़ोl_dbi(pci, offset + PCI_EXP_DEVCTL);
	val &= ~PCI_EXP_DEVCTL_PAYLOAD;
	dw_pcie_ग_लिखोl_dbi(pci, offset + PCI_EXP_DEVCTL, val);

	val = dw_pcie_पढ़ोl_dbi(pci, offset + PCI_EXP_DEVCTL);
	val |= PCIE_CAP_MAX_PAYLOAD_SIZE(max_payload_size);
	dw_pcie_ग_लिखोl_dbi(pci, offset + PCI_EXP_DEVCTL, val);
पूर्ण

अटल व्योम meson_set_max_rd_req_size(काष्ठा meson_pcie *mp, पूर्णांक size)
अणु
	काष्ठा dw_pcie *pci = &mp->pci;
	u32 val;
	u16 offset = dw_pcie_find_capability(pci, PCI_CAP_ID_EXP);
	पूर्णांक max_rd_req_size = meson_माप_प्रकारo_payload(mp, size);

	val = dw_pcie_पढ़ोl_dbi(pci, offset + PCI_EXP_DEVCTL);
	val &= ~PCI_EXP_DEVCTL_READRQ;
	dw_pcie_ग_लिखोl_dbi(pci, offset + PCI_EXP_DEVCTL, val);

	val = dw_pcie_पढ़ोl_dbi(pci, offset + PCI_EXP_DEVCTL);
	val |= PCIE_CAP_MAX_READ_REQ_SIZE(max_rd_req_size);
	dw_pcie_ग_लिखोl_dbi(pci, offset + PCI_EXP_DEVCTL, val);
पूर्ण

अटल पूर्णांक meson_pcie_start_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा meson_pcie *mp = to_meson_pcie(pci);

	meson_pcie_ltssm_enable(mp);
	meson_pcie_निश्चित_reset(mp);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_pcie_rd_own_conf(काष्ठा pci_bus *bus, u32 devfn,
				  पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	पूर्णांक ret;

	ret = pci_generic_config_पढ़ो(bus, devfn, where, size, val);
	अगर (ret != PCIBIOS_SUCCESSFUL)
		वापस ret;

	/*
	 * There is a bug in the MESON AXG PCIe controller whereby software
	 * cannot program the PCI_CLASS_DEVICE रेजिस्टर, so we must fabricate
	 * the वापस value in the config accessors.
	 */
	अगर (where == PCI_CLASS_REVISION && size == 4)
		*val = (PCI_CLASS_BRIDGE_PCI << 16) | (*val & 0xffff);
	अन्यथा अगर (where == PCI_CLASS_DEVICE && size == 2)
		*val = PCI_CLASS_BRIDGE_PCI;
	अन्यथा अगर (where == PCI_CLASS_DEVICE && size == 1)
		*val = PCI_CLASS_BRIDGE_PCI & 0xff;
	अन्यथा अगर (where == PCI_CLASS_DEVICE + 1 && size == 1)
		*val = (PCI_CLASS_BRIDGE_PCI >> 8) & 0xff;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops meson_pci_ops = अणु
	.map_bus = dw_pcie_own_conf_map_bus,
	.पढ़ो = meson_pcie_rd_own_conf,
	.ग_लिखो = pci_generic_config_ग_लिखो,
पूर्ण;

अटल पूर्णांक meson_pcie_link_up(काष्ठा dw_pcie *pci)
अणु
	काष्ठा meson_pcie *mp = to_meson_pcie(pci);
	काष्ठा device *dev = pci->dev;
	u32 speed_okay = 0;
	u32 cnt = 0;
	u32 state12, state17, smlh_up, ltssm_up, rdlh_up;

	करो अणु
		state12 = meson_cfg_पढ़ोl(mp, PCIE_CFG_STATUS12);
		state17 = meson_cfg_पढ़ोl(mp, PCIE_CFG_STATUS17);
		smlh_up = IS_SMLH_LINK_UP(state12);
		rdlh_up = IS_RDLH_LINK_UP(state12);
		ltssm_up = IS_LTSSM_UP(state12);

		अगर (PM_CURRENT_STATE(state17) < PCIE_GEN3)
			speed_okay = 1;

		अगर (smlh_up)
			dev_dbg(dev, "smlh_link_up is on\n");
		अगर (rdlh_up)
			dev_dbg(dev, "rdlh_link_up is on\n");
		अगर (ltssm_up)
			dev_dbg(dev, "ltssm_up is on\n");
		अगर (speed_okay)
			dev_dbg(dev, "speed_okay\n");

		अगर (smlh_up && rdlh_up && ltssm_up && speed_okay)
			वापस 1;

		cnt++;

		udelay(10);
	पूर्ण जबतक (cnt < WAIT_LINKUP_TIMEOUT);

	dev_err(dev, "error: wait linkup timeout\n");
	वापस 0;
पूर्ण

अटल पूर्णांक meson_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा meson_pcie *mp = to_meson_pcie(pci);

	pp->bridge->ops = &meson_pci_ops;

	meson_set_max_payload(mp, MAX_PAYLOAD_SIZE);
	meson_set_max_rd_req_size(mp, MAX_READ_REQ_SIZE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_host_ops meson_pcie_host_ops = अणु
	.host_init = meson_pcie_host_init,
पूर्ण;

अटल स्थिर काष्ठा dw_pcie_ops dw_pcie_ops = अणु
	.link_up = meson_pcie_link_up,
	.start_link = meson_pcie_start_link,
पूर्ण;

अटल पूर्णांक meson_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dw_pcie *pci;
	काष्ठा meson_pcie *mp;
	पूर्णांक ret;

	mp = devm_kzalloc(dev, माप(*mp), GFP_KERNEL);
	अगर (!mp)
		वापस -ENOMEM;

	pci = &mp->pci;
	pci->dev = dev;
	pci->ops = &dw_pcie_ops;
	pci->pp.ops = &meson_pcie_host_ops;
	pci->num_lanes = 1;

	mp->phy = devm_phy_get(dev, "pcie");
	अगर (IS_ERR(mp->phy)) अणु
		dev_err(dev, "get phy failed, %ld\n", PTR_ERR(mp->phy));
		वापस PTR_ERR(mp->phy);
	पूर्ण

	mp->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(mp->reset_gpio)) अणु
		dev_err(dev, "get reset gpio failed\n");
		वापस PTR_ERR(mp->reset_gpio);
	पूर्ण

	ret = meson_pcie_get_resets(mp);
	अगर (ret) अणु
		dev_err(dev, "get reset resource failed, %d\n", ret);
		वापस ret;
	पूर्ण

	ret = meson_pcie_get_mems(pdev, mp);
	अगर (ret) अणु
		dev_err(dev, "get memory resource failed, %d\n", ret);
		वापस ret;
	पूर्ण

	ret = meson_pcie_घातer_on(mp);
	अगर (ret) अणु
		dev_err(dev, "phy power on failed, %d\n", ret);
		वापस ret;
	पूर्ण

	ret = meson_pcie_reset(mp);
	अगर (ret) अणु
		dev_err(dev, "reset failed, %d\n", ret);
		जाओ err_phy;
	पूर्ण

	ret = meson_pcie_probe_घड़ीs(mp);
	अगर (ret) अणु
		dev_err(dev, "init clock resources failed, %d\n", ret);
		जाओ err_phy;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mp);

	ret = dw_pcie_host_init(&pci->pp);
	अगर (ret < 0) अणु
		dev_err(dev, "Add PCIe port failed, %d\n", ret);
		जाओ err_phy;
	पूर्ण

	वापस 0;

err_phy:
	meson_pcie_घातer_off(mp);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id meson_pcie_of_match[] = अणु
	अणु
		.compatible = "amlogic,axg-pcie",
	पूर्ण,
	अणु
		.compatible = "amlogic,g12a-pcie",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_pcie_of_match);

अटल काष्ठा platक्रमm_driver meson_pcie_driver = अणु
	.probe = meson_pcie_probe,
	.driver = अणु
		.name = "meson-pcie",
		.of_match_table = meson_pcie_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_pcie_driver);

MODULE_AUTHOR("Yue Wang <yue.wang@amlogic.com>");
MODULE_DESCRIPTION("Amlogic PCIe Controller driver");
MODULE_LICENSE("GPL v2");
