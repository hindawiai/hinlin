<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Combo-PHY driver
 *
 * Copyright (C) 2019-2020 Intel Corporation.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश <dt-bindings/phy/phy.h>

#घोषणा PCIE_PHY_GEN_CTRL	0x00
#घोषणा PCIE_PHY_CLK_PAD	BIT(17)

#घोषणा PAD_DIS_CFG		0x174

#घोषणा PCS_XF_ATE_OVRD_IN_2	0x3008
#घोषणा ADAPT_REQ_MSK		GENMASK(5, 4)

#घोषणा PCS_XF_RX_ADAPT_ACK	0x3010
#घोषणा RX_ADAPT_ACK_BIT	BIT(0)

#घोषणा CR_ADDR(addr, lane)	(((addr) + (lane) * 0x100) << 2)
#घोषणा REG_COMBO_MODE(x)	((x) * 0x200)
#घोषणा REG_CLK_DISABLE(x)	((x) * 0x200 + 0x124)

#घोषणा COMBO_PHY_ID(x)		((x)->parent->id)
#घोषणा PHY_ID(x)		((x)->id)

#घोषणा CLK_100MHZ		100000000
#घोषणा CLK_156_25MHZ		156250000

अटल स्थिर अचिन्हित दीर्घ पूर्णांकel_iphy_clk_rates[] = अणु
	CLK_100MHZ, CLK_156_25MHZ, CLK_100MHZ,
पूर्ण;

क्रमागत अणु
	PHY_0,
	PHY_1,
	PHY_MAX_NUM
पूर्ण;

/*
 * Clock Register bit fields to enable घड़ीs
 * क्रम ComboPhy according to the mode.
 */
क्रमागत पूर्णांकel_phy_mode अणु
	PHY_PCIE_MODE = 0,
	PHY_XPCS_MODE,
	PHY_SATA_MODE,
पूर्ण;

/* ComboPhy mode Register values */
क्रमागत पूर्णांकel_combo_mode अणु
	PCIE0_PCIE1_MODE = 0,
	PCIE_DL_MODE,
	RXAUI_MODE,
	XPCS0_XPCS1_MODE,
	SATA0_SATA1_MODE,
पूर्ण;

क्रमागत aggregated_mode अणु
	PHY_SL_MODE,
	PHY_DL_MODE,
पूर्ण;

काष्ठा पूर्णांकel_combo_phy;

काष्ठा पूर्णांकel_cbphy_iphy अणु
	काष्ठा phy		*phy;
	काष्ठा पूर्णांकel_combo_phy	*parent;
	काष्ठा reset_control	*app_rst;
	u32			id;
पूर्ण;

काष्ठा पूर्णांकel_combo_phy अणु
	काष्ठा device		*dev;
	काष्ठा clk		*core_clk;
	अचिन्हित दीर्घ		clk_rate;
	व्योम __iomem		*app_base;
	व्योम __iomem		*cr_base;
	काष्ठा regmap		*syscfg;
	काष्ठा regmap		*hsiocfg;
	u32			id;
	u32			bid;
	काष्ठा reset_control	*phy_rst;
	काष्ठा reset_control	*core_rst;
	काष्ठा पूर्णांकel_cbphy_iphy	iphy[PHY_MAX_NUM];
	क्रमागत पूर्णांकel_phy_mode	phy_mode;
	क्रमागत aggregated_mode	aggr_mode;
	u32			init_cnt;
	काष्ठा mutex		lock;
पूर्ण;

अटल पूर्णांक पूर्णांकel_cbphy_iphy_enable(काष्ठा पूर्णांकel_cbphy_iphy *iphy, bool set)
अणु
	काष्ठा पूर्णांकel_combo_phy *cbphy = iphy->parent;
	u32 mask = BIT(cbphy->phy_mode * 2 + iphy->id);
	u32 val;

	/* Register: 0 is enable, 1 is disable */
	val = set ? 0 : mask;

	वापस regmap_update_bits(cbphy->hsiocfg, REG_CLK_DISABLE(cbphy->bid),
				  mask, val);
पूर्ण

अटल पूर्णांक पूर्णांकel_cbphy_pcie_refclk_cfg(काष्ठा पूर्णांकel_cbphy_iphy *iphy, bool set)
अणु
	काष्ठा पूर्णांकel_combo_phy *cbphy = iphy->parent;
	u32 mask = BIT(cbphy->id * 2 + iphy->id);
	u32 val;

	/* Register: 0 is enable, 1 is disable */
	val = set ? 0 : mask;

	वापस regmap_update_bits(cbphy->syscfg, PAD_DIS_CFG, mask, val);
पूर्ण

अटल अंतरभूत व्योम combo_phy_w32_off_mask(व्योम __iomem *base, अचिन्हित पूर्णांक reg,
					  u32 mask, u32 val)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(base + reg);
	reg_val &= ~mask;
	reg_val |= val;
	ग_लिखोl(reg_val, base + reg);
पूर्ण

अटल पूर्णांक पूर्णांकel_cbphy_iphy_cfg(काष्ठा पूर्णांकel_cbphy_iphy *iphy,
				पूर्णांक (*phy_cfg)(काष्ठा पूर्णांकel_cbphy_iphy *))
अणु
	काष्ठा पूर्णांकel_combo_phy *cbphy = iphy->parent;
	पूर्णांक ret;

	ret = phy_cfg(iphy);
	अगर (ret)
		वापस ret;

	अगर (cbphy->aggr_mode != PHY_DL_MODE)
		वापस 0;

	वापस phy_cfg(&cbphy->iphy[PHY_1]);
पूर्ण

अटल पूर्णांक पूर्णांकel_cbphy_pcie_en_pad_refclk(काष्ठा पूर्णांकel_cbphy_iphy *iphy)
अणु
	काष्ठा पूर्णांकel_combo_phy *cbphy = iphy->parent;
	पूर्णांक ret;

	ret = पूर्णांकel_cbphy_pcie_refclk_cfg(iphy, true);
	अगर (ret) अणु
		dev_err(cbphy->dev, "Failed to enable PCIe pad refclk\n");
		वापस ret;
	पूर्ण

	अगर (cbphy->init_cnt)
		वापस 0;

	combo_phy_w32_off_mask(cbphy->app_base, PCIE_PHY_GEN_CTRL,
			       PCIE_PHY_CLK_PAD, FIELD_PREP(PCIE_PHY_CLK_PAD, 0));

	/* Delay क्रम stable घड़ी PLL */
	usleep_range(50, 100);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_cbphy_pcie_dis_pad_refclk(काष्ठा पूर्णांकel_cbphy_iphy *iphy)
अणु
	काष्ठा पूर्णांकel_combo_phy *cbphy = iphy->parent;
	पूर्णांक ret;

	ret = पूर्णांकel_cbphy_pcie_refclk_cfg(iphy, false);
	अगर (ret) अणु
		dev_err(cbphy->dev, "Failed to disable PCIe pad refclk\n");
		वापस ret;
	पूर्ण

	अगर (cbphy->init_cnt)
		वापस 0;

	combo_phy_w32_off_mask(cbphy->app_base, PCIE_PHY_GEN_CTRL,
			       PCIE_PHY_CLK_PAD, FIELD_PREP(PCIE_PHY_CLK_PAD, 1));

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_cbphy_set_mode(काष्ठा पूर्णांकel_combo_phy *cbphy)
अणु
	क्रमागत पूर्णांकel_combo_mode cb_mode;
	क्रमागत aggregated_mode aggr = cbphy->aggr_mode;
	काष्ठा device *dev = cbphy->dev;
	क्रमागत पूर्णांकel_phy_mode mode;
	पूर्णांक ret;

	mode = cbphy->phy_mode;

	चयन (mode) अणु
	हाल PHY_PCIE_MODE:
		cb_mode = (aggr == PHY_DL_MODE) ? PCIE_DL_MODE : PCIE0_PCIE1_MODE;
		अवरोध;

	हाल PHY_XPCS_MODE:
		cb_mode = (aggr == PHY_DL_MODE) ? RXAUI_MODE : XPCS0_XPCS1_MODE;
		अवरोध;

	हाल PHY_SATA_MODE:
		अगर (aggr == PHY_DL_MODE) अणु
			dev_err(dev, "Mode:%u not support dual lane!\n", mode);
			वापस -EINVAL;
		पूर्ण

		cb_mode = SATA0_SATA1_MODE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_ग_लिखो(cbphy->hsiocfg, REG_COMBO_MODE(cbphy->bid), cb_mode);
	अगर (ret)
		dev_err(dev, "Failed to set ComboPhy mode: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_cbphy_rst_निश्चित(काष्ठा पूर्णांकel_combo_phy *cbphy)
अणु
	reset_control_निश्चित(cbphy->core_rst);
	reset_control_निश्चित(cbphy->phy_rst);
पूर्ण

अटल व्योम पूर्णांकel_cbphy_rst_deनिश्चित(काष्ठा पूर्णांकel_combo_phy *cbphy)
अणु
	reset_control_deनिश्चित(cbphy->core_rst);
	reset_control_deनिश्चित(cbphy->phy_rst);
	/* Delay to ensure reset process is करोne */
	usleep_range(10, 20);
पूर्ण

अटल पूर्णांक पूर्णांकel_cbphy_iphy_घातer_on(काष्ठा पूर्णांकel_cbphy_iphy *iphy)
अणु
	काष्ठा पूर्णांकel_combo_phy *cbphy = iphy->parent;
	पूर्णांक ret;

	अगर (!cbphy->init_cnt) अणु
		ret = clk_prepare_enable(cbphy->core_clk);
		अगर (ret) अणु
			dev_err(cbphy->dev, "Clock enable failed!\n");
			वापस ret;
		पूर्ण

		ret = clk_set_rate(cbphy->core_clk, cbphy->clk_rate);
		अगर (ret) अणु
			dev_err(cbphy->dev, "Clock freq set to %lu failed!\n",
				cbphy->clk_rate);
			जाओ clk_err;
		पूर्ण

		पूर्णांकel_cbphy_rst_निश्चित(cbphy);
		पूर्णांकel_cbphy_rst_deनिश्चित(cbphy);
		ret = पूर्णांकel_cbphy_set_mode(cbphy);
		अगर (ret)
			जाओ clk_err;
	पूर्ण

	ret = पूर्णांकel_cbphy_iphy_enable(iphy, true);
	अगर (ret) अणु
		dev_err(cbphy->dev, "Failed enabling PHY core\n");
		जाओ clk_err;
	पूर्ण

	ret = reset_control_deनिश्चित(iphy->app_rst);
	अगर (ret) अणु
		dev_err(cbphy->dev, "PHY(%u:%u) reset deassert failed!\n",
			COMBO_PHY_ID(iphy), PHY_ID(iphy));
		जाओ clk_err;
	पूर्ण

	/* Delay to ensure reset process is करोne */
	udelay(1);

	वापस 0;

clk_err:
	clk_disable_unprepare(cbphy->core_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_cbphy_iphy_घातer_off(काष्ठा पूर्णांकel_cbphy_iphy *iphy)
अणु
	काष्ठा पूर्णांकel_combo_phy *cbphy = iphy->parent;
	पूर्णांक ret;

	ret = reset_control_निश्चित(iphy->app_rst);
	अगर (ret) अणु
		dev_err(cbphy->dev, "PHY(%u:%u) reset assert failed!\n",
			COMBO_PHY_ID(iphy), PHY_ID(iphy));
		वापस ret;
	पूर्ण

	ret = पूर्णांकel_cbphy_iphy_enable(iphy, false);
	अगर (ret) अणु
		dev_err(cbphy->dev, "Failed disabling PHY core\n");
		वापस ret;
	पूर्ण

	अगर (cbphy->init_cnt)
		वापस 0;

	clk_disable_unprepare(cbphy->core_clk);
	पूर्णांकel_cbphy_rst_निश्चित(cbphy);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_cbphy_init(काष्ठा phy *phy)
अणु
	काष्ठा पूर्णांकel_cbphy_iphy *iphy = phy_get_drvdata(phy);
	काष्ठा पूर्णांकel_combo_phy *cbphy = iphy->parent;
	पूर्णांक ret;

	mutex_lock(&cbphy->lock);
	ret = पूर्णांकel_cbphy_iphy_cfg(iphy, पूर्णांकel_cbphy_iphy_घातer_on);
	अगर (ret)
		जाओ err;

	अगर (cbphy->phy_mode == PHY_PCIE_MODE) अणु
		ret = पूर्णांकel_cbphy_iphy_cfg(iphy, पूर्णांकel_cbphy_pcie_en_pad_refclk);
		अगर (ret)
			जाओ err;
	पूर्ण

	cbphy->init_cnt++;

err:
	mutex_unlock(&cbphy->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_cbphy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा पूर्णांकel_cbphy_iphy *iphy = phy_get_drvdata(phy);
	काष्ठा पूर्णांकel_combo_phy *cbphy = iphy->parent;
	पूर्णांक ret;

	mutex_lock(&cbphy->lock);
	cbphy->init_cnt--;
	अगर (cbphy->phy_mode == PHY_PCIE_MODE) अणु
		ret = पूर्णांकel_cbphy_iphy_cfg(iphy, पूर्णांकel_cbphy_pcie_dis_pad_refclk);
		अगर (ret)
			जाओ err;
	पूर्ण

	ret = पूर्णांकel_cbphy_iphy_cfg(iphy, पूर्णांकel_cbphy_iphy_घातer_off);

err:
	mutex_unlock(&cbphy->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_cbphy_calibrate(काष्ठा phy *phy)
अणु
	काष्ठा पूर्णांकel_cbphy_iphy *iphy = phy_get_drvdata(phy);
	काष्ठा पूर्णांकel_combo_phy *cbphy = iphy->parent;
	व्योम __iomem *cr_base = cbphy->cr_base;
	पूर्णांक val, ret, id;

	अगर (cbphy->phy_mode != PHY_XPCS_MODE)
		वापस 0;

	id = PHY_ID(iphy);

	/* trigger स्वतः RX adaptation */
	combo_phy_w32_off_mask(cr_base, CR_ADDR(PCS_XF_ATE_OVRD_IN_2, id),
			       ADAPT_REQ_MSK, FIELD_PREP(ADAPT_REQ_MSK, 3));
	/* Wait RX adaptation to finish */
	ret = पढ़ोl_poll_समयout(cr_base + CR_ADDR(PCS_XF_RX_ADAPT_ACK, id),
				 val, val & RX_ADAPT_ACK_BIT, 10, 5000);
	अगर (ret)
		dev_err(cbphy->dev, "RX Adaptation failed!\n");
	अन्यथा
		dev_dbg(cbphy->dev, "RX Adaptation success!\n");

	/* Stop RX adaptation */
	combo_phy_w32_off_mask(cr_base, CR_ADDR(PCS_XF_ATE_OVRD_IN_2, id),
			       ADAPT_REQ_MSK, FIELD_PREP(ADAPT_REQ_MSK, 0));

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_cbphy_fwnode_parse(काष्ठा पूर्णांकel_combo_phy *cbphy)
अणु
	काष्ठा device *dev = cbphy->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा fwnode_handle *fwnode = dev_fwnode(dev);
	काष्ठा fwnode_reference_args ref;
	पूर्णांक ret;
	u32 val;

	cbphy->core_clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(cbphy->core_clk)) अणु
		ret = PTR_ERR(cbphy->core_clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Get clk failed:%d!\n", ret);
		वापस ret;
	पूर्ण

	cbphy->core_rst = devm_reset_control_get_optional(dev, "core");
	अगर (IS_ERR(cbphy->core_rst)) अणु
		ret = PTR_ERR(cbphy->core_rst);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Get core reset control err: %d!\n", ret);
		वापस ret;
	पूर्ण

	cbphy->phy_rst = devm_reset_control_get_optional(dev, "phy");
	अगर (IS_ERR(cbphy->phy_rst)) अणु
		ret = PTR_ERR(cbphy->phy_rst);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Get PHY reset control err: %d!\n", ret);
		वापस ret;
	पूर्ण

	cbphy->iphy[0].app_rst = devm_reset_control_get_optional(dev, "iphy0");
	अगर (IS_ERR(cbphy->iphy[0].app_rst)) अणु
		ret = PTR_ERR(cbphy->iphy[0].app_rst);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Get phy0 reset control err: %d!\n", ret);
		वापस ret;
	पूर्ण

	cbphy->iphy[1].app_rst = devm_reset_control_get_optional(dev, "iphy1");
	अगर (IS_ERR(cbphy->iphy[1].app_rst)) अणु
		ret = PTR_ERR(cbphy->iphy[1].app_rst);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Get phy1 reset control err: %d!\n", ret);
		वापस ret;
	पूर्ण

	cbphy->app_base = devm_platक्रमm_ioremap_resource_byname(pdev, "app");
	अगर (IS_ERR(cbphy->app_base))
		वापस PTR_ERR(cbphy->app_base);

	cbphy->cr_base = devm_platक्रमm_ioremap_resource_byname(pdev, "core");
	अगर (IS_ERR(cbphy->cr_base))
		वापस PTR_ERR(cbphy->cr_base);

	/*
	 * syscfg and hsiocfg variables stores the handle of the रेजिस्टरs set
	 * in which ComboPhy subप्रणाली specअगरic रेजिस्टरs are subset. Using
	 * Register map framework to access the रेजिस्टरs set.
	 */
	ret = fwnode_property_get_reference_args(fwnode, "intel,syscfg", शून्य,
						 1, 0, &ref);
	अगर (ret < 0)
		वापस ret;

	cbphy->id = ref.args[0];
	cbphy->syscfg = device_node_to_regmap(to_of_node(ref.fwnode));
	fwnode_handle_put(ref.fwnode);

	ret = fwnode_property_get_reference_args(fwnode, "intel,hsio", शून्य, 1,
						 0, &ref);
	अगर (ret < 0)
		वापस ret;

	cbphy->bid = ref.args[0];
	cbphy->hsiocfg = device_node_to_regmap(to_of_node(ref.fwnode));
	fwnode_handle_put(ref.fwnode);

	ret = fwnode_property_पढ़ो_u32_array(fwnode, "intel,phy-mode", &val, 1);
	अगर (ret)
		वापस ret;

	चयन (val) अणु
	हाल PHY_TYPE_PCIE:
		cbphy->phy_mode = PHY_PCIE_MODE;
		अवरोध;

	हाल PHY_TYPE_SATA:
		cbphy->phy_mode = PHY_SATA_MODE;
		अवरोध;

	हाल PHY_TYPE_XPCS:
		cbphy->phy_mode = PHY_XPCS_MODE;
		अवरोध;

	शेष:
		dev_err(dev, "Invalid PHY mode: %u\n", val);
		वापस -EINVAL;
	पूर्ण

	cbphy->clk_rate = पूर्णांकel_iphy_clk_rates[cbphy->phy_mode];

	अगर (fwnode_property_present(fwnode, "intel,aggregation"))
		cbphy->aggr_mode = PHY_DL_MODE;
	अन्यथा
		cbphy->aggr_mode = PHY_SL_MODE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops पूर्णांकel_cbphy_ops = अणु
	.init		= पूर्णांकel_cbphy_init,
	.निकास		= पूर्णांकel_cbphy_निकास,
	.calibrate	= पूर्णांकel_cbphy_calibrate,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा phy *पूर्णांकel_cbphy_xlate(काष्ठा device *dev,
				     काष्ठा of_phandle_args *args)
अणु
	काष्ठा पूर्णांकel_combo_phy *cbphy = dev_get_drvdata(dev);
	u32 iphy_id;

	अगर (args->args_count < 1) अणु
		dev_err(dev, "Invalid number of arguments\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	iphy_id = args->args[0];
	अगर (iphy_id >= PHY_MAX_NUM) अणु
		dev_err(dev, "Invalid phy instance %d\n", iphy_id);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (cbphy->aggr_mode == PHY_DL_MODE && iphy_id == PHY_1) अणु
		dev_err(dev, "Invalid. ComboPhy is in Dual lane mode %d\n", iphy_id);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस cbphy->iphy[iphy_id].phy;
पूर्ण

अटल पूर्णांक पूर्णांकel_cbphy_create(काष्ठा पूर्णांकel_combo_phy *cbphy)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा device *dev = cbphy->dev;
	काष्ठा पूर्णांकel_cbphy_iphy *iphy;
	पूर्णांक i;

	क्रम (i = 0; i < PHY_MAX_NUM; i++) अणु
		iphy = &cbphy->iphy[i];
		iphy->parent = cbphy;
		iphy->id = i;

		/* In dual lane mode skip phy creation क्रम the second phy */
		अगर (cbphy->aggr_mode == PHY_DL_MODE && iphy->id == PHY_1)
			जारी;

		iphy->phy = devm_phy_create(dev, शून्य, &पूर्णांकel_cbphy_ops);
		अगर (IS_ERR(iphy->phy)) अणु
			dev_err(dev, "PHY[%u:%u]: create PHY instance failed!\n",
				COMBO_PHY_ID(iphy), PHY_ID(iphy));

			वापस PTR_ERR(iphy->phy);
		पूर्ण

		phy_set_drvdata(iphy->phy, iphy);
	पूर्ण

	dev_set_drvdata(dev, cbphy);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, पूर्णांकel_cbphy_xlate);
	अगर (IS_ERR(phy_provider))
		dev_err(dev, "Register PHY provider failed!\n");

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल पूर्णांक पूर्णांकel_cbphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा पूर्णांकel_combo_phy *cbphy;
	पूर्णांक ret;

	cbphy = devm_kzalloc(dev, माप(*cbphy), GFP_KERNEL);
	अगर (!cbphy)
		वापस -ENOMEM;

	cbphy->dev = dev;
	cbphy->init_cnt = 0;
	mutex_init(&cbphy->lock);
	ret = पूर्णांकel_cbphy_fwnode_parse(cbphy);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, cbphy);

	वापस पूर्णांकel_cbphy_create(cbphy);
पूर्ण

अटल पूर्णांक पूर्णांकel_cbphy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_combo_phy *cbphy = platक्रमm_get_drvdata(pdev);

	पूर्णांकel_cbphy_rst_निश्चित(cbphy);
	clk_disable_unprepare(cbphy->core_clk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_पूर्णांकel_cbphy_match[] = अणु
	अणु .compatible = "intel,combo-phy" पूर्ण,
	अणु .compatible = "intel,combophy-lgm" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver पूर्णांकel_cbphy_driver = अणु
	.probe = पूर्णांकel_cbphy_probe,
	.हटाओ = पूर्णांकel_cbphy_हटाओ,
	.driver = अणु
		.name = "intel-combo-phy",
		.of_match_table = of_पूर्णांकel_cbphy_match,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(पूर्णांकel_cbphy_driver);

MODULE_DESCRIPTION("Intel Combo-phy driver");
MODULE_LICENSE("GPL v2");
