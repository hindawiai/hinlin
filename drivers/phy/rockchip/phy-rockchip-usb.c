<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Rockchip usb PHY driver
 *
 * Copyright (C) 2014 Yunzhi Li <lyz@rock-chips.com>
 * Copyright (C) 2014 ROCKCHIP, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/delay.h>

अटल पूर्णांक enable_usb_uart;

#घोषणा HIWORD_UPDATE(val, mask) \
		((val) | (mask) << 16)

#घोषणा UOC_CON0					0x00
#घोषणा UOC_CON0_SIDDQ					BIT(13)
#घोषणा UOC_CON0_DISABLE				BIT(4)
#घोषणा UOC_CON0_COMMON_ON_N				BIT(0)

#घोषणा UOC_CON2					0x08
#घोषणा UOC_CON2_SOFT_CON_SEL				BIT(2)

#घोषणा UOC_CON3					0x0c
/* bits present on rk3188 and rk3288 phys */
#घोषणा UOC_CON3_UTMI_TERMSEL_FULLSPEED			BIT(5)
#घोषणा UOC_CON3_UTMI_XCVRSEELCT_FSTRANSC		(1 << 3)
#घोषणा UOC_CON3_UTMI_XCVRSEELCT_MASK			(3 << 3)
#घोषणा UOC_CON3_UTMI_OPMODE_NODRIVING			(1 << 1)
#घोषणा UOC_CON3_UTMI_OPMODE_MASK			(3 << 1)
#घोषणा UOC_CON3_UTMI_SUSPENDN				BIT(0)

काष्ठा rockchip_usb_phys अणु
	पूर्णांक reg;
	स्थिर अक्षर *pll_name;
पूर्ण;

काष्ठा rockchip_usb_phy_base;
काष्ठा rockchip_usb_phy_pdata अणु
	काष्ठा rockchip_usb_phys *phys;
	पूर्णांक (*init_usb_uart)(काष्ठा regmap *grf,
			     स्थिर काष्ठा rockchip_usb_phy_pdata *pdata);
	पूर्णांक usb_uart_phy;
पूर्ण;

काष्ठा rockchip_usb_phy_base अणु
	काष्ठा device *dev;
	काष्ठा regmap *reg_base;
	स्थिर काष्ठा rockchip_usb_phy_pdata *pdata;
पूर्ण;

काष्ठा rockchip_usb_phy अणु
	काष्ठा rockchip_usb_phy_base *base;
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक	reg_offset;
	काष्ठा clk	*clk;
	काष्ठा clk      *clk480m;
	काष्ठा clk_hw	clk480m_hw;
	काष्ठा phy	*phy;
	bool		uart_enabled;
	काष्ठा reset_control *reset;
	काष्ठा regulator *vbus;
पूर्ण;

अटल पूर्णांक rockchip_usb_phy_घातer(काष्ठा rockchip_usb_phy *phy,
					   bool siddq)
अणु
	u32 val = HIWORD_UPDATE(siddq ? UOC_CON0_SIDDQ : 0, UOC_CON0_SIDDQ);

	वापस regmap_ग_लिखो(phy->base->reg_base, phy->reg_offset, val);
पूर्ण

अटल अचिन्हित दीर्घ rockchip_usb_phy480m_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	वापस 480000000;
पूर्ण

अटल व्योम rockchip_usb_phy480m_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_usb_phy *phy = container_of(hw,
						    काष्ठा rockchip_usb_phy,
						    clk480m_hw);

	अगर (phy->vbus)
		regulator_disable(phy->vbus);

	/* Power करोwn usb phy analog blocks by set siddq 1 */
	rockchip_usb_phy_घातer(phy, 1);
पूर्ण

अटल पूर्णांक rockchip_usb_phy480m_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_usb_phy *phy = container_of(hw,
						    काष्ठा rockchip_usb_phy,
						    clk480m_hw);

	/* Power up usb phy analog blocks by set siddq 0 */
	वापस rockchip_usb_phy_घातer(phy, 0);
पूर्ण

अटल पूर्णांक rockchip_usb_phy480m_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_usb_phy *phy = container_of(hw,
						    काष्ठा rockchip_usb_phy,
						    clk480m_hw);
	पूर्णांक ret;
	u32 val;

	ret = regmap_पढ़ो(phy->base->reg_base, phy->reg_offset, &val);
	अगर (ret < 0)
		वापस ret;

	वापस (val & UOC_CON0_SIDDQ) ? 0 : 1;
पूर्ण

अटल स्थिर काष्ठा clk_ops rockchip_usb_phy480m_ops = अणु
	.enable = rockchip_usb_phy480m_enable,
	.disable = rockchip_usb_phy480m_disable,
	.is_enabled = rockchip_usb_phy480m_is_enabled,
	.recalc_rate = rockchip_usb_phy480m_recalc_rate,
पूर्ण;

अटल पूर्णांक rockchip_usb_phy_घातer_off(काष्ठा phy *_phy)
अणु
	काष्ठा rockchip_usb_phy *phy = phy_get_drvdata(_phy);

	अगर (phy->uart_enabled)
		वापस -EBUSY;

	clk_disable_unprepare(phy->clk480m);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_usb_phy_घातer_on(काष्ठा phy *_phy)
अणु
	काष्ठा rockchip_usb_phy *phy = phy_get_drvdata(_phy);

	अगर (phy->uart_enabled)
		वापस -EBUSY;

	अगर (phy->vbus) अणु
		पूर्णांक ret;

		ret = regulator_enable(phy->vbus);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस clk_prepare_enable(phy->clk480m);
पूर्ण

अटल पूर्णांक rockchip_usb_phy_reset(काष्ठा phy *_phy)
अणु
	काष्ठा rockchip_usb_phy *phy = phy_get_drvdata(_phy);

	अगर (phy->reset) अणु
		reset_control_निश्चित(phy->reset);
		udelay(10);
		reset_control_deनिश्चित(phy->reset);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops ops = अणु
	.घातer_on	= rockchip_usb_phy_घातer_on,
	.घातer_off	= rockchip_usb_phy_घातer_off,
	.reset		= rockchip_usb_phy_reset,
	.owner		= THIS_MODULE,
पूर्ण;

अटल व्योम rockchip_usb_phy_action(व्योम *data)
अणु
	काष्ठा rockchip_usb_phy *rk_phy = data;

	अगर (!rk_phy->uart_enabled) अणु
		of_clk_del_provider(rk_phy->np);
		clk_unरेजिस्टर(rk_phy->clk480m);
	पूर्ण

	अगर (rk_phy->clk)
		clk_put(rk_phy->clk);
पूर्ण

अटल पूर्णांक rockchip_usb_phy_init(काष्ठा rockchip_usb_phy_base *base,
				 काष्ठा device_node *child)
अणु
	काष्ठा rockchip_usb_phy *rk_phy;
	अचिन्हित पूर्णांक reg_offset;
	स्थिर अक्षर *clk_name;
	काष्ठा clk_init_data init;
	पूर्णांक err, i;

	rk_phy = devm_kzalloc(base->dev, माप(*rk_phy), GFP_KERNEL);
	अगर (!rk_phy)
		वापस -ENOMEM;

	rk_phy->base = base;
	rk_phy->np = child;

	अगर (of_property_पढ़ो_u32(child, "reg", &reg_offset)) अणु
		dev_err(base->dev, "missing reg property in node %pOFn\n",
			child);
		वापस -EINVAL;
	पूर्ण

	rk_phy->reset = of_reset_control_get(child, "phy-reset");
	अगर (IS_ERR(rk_phy->reset))
		rk_phy->reset = शून्य;

	rk_phy->reg_offset = reg_offset;

	rk_phy->clk = of_clk_get_by_name(child, "phyclk");
	अगर (IS_ERR(rk_phy->clk))
		rk_phy->clk = शून्य;

	i = 0;
	init.name = शून्य;
	जबतक (base->pdata->phys[i].reg) अणु
		अगर (base->pdata->phys[i].reg == reg_offset) अणु
			init.name = base->pdata->phys[i].pll_name;
			अवरोध;
		पूर्ण
		i++;
	पूर्ण

	अगर (!init.name) अणु
		dev_err(base->dev, "phy data not found\n");
		वापस -EINVAL;
	पूर्ण

	अगर (enable_usb_uart && base->pdata->usb_uart_phy == i) अणु
		dev_dbg(base->dev, "phy%d used as uart output\n", i);
		rk_phy->uart_enabled = true;
	पूर्ण अन्यथा अणु
		अगर (rk_phy->clk) अणु
			clk_name = __clk_get_name(rk_phy->clk);
			init.flags = 0;
			init.parent_names = &clk_name;
			init.num_parents = 1;
		पूर्ण अन्यथा अणु
			init.flags = 0;
			init.parent_names = शून्य;
			init.num_parents = 0;
		पूर्ण

		init.ops = &rockchip_usb_phy480m_ops;
		rk_phy->clk480m_hw.init = &init;

		rk_phy->clk480m = clk_रेजिस्टर(base->dev, &rk_phy->clk480m_hw);
		अगर (IS_ERR(rk_phy->clk480m)) अणु
			err = PTR_ERR(rk_phy->clk480m);
			जाओ err_clk;
		पूर्ण

		err = of_clk_add_provider(child, of_clk_src_simple_get,
					rk_phy->clk480m);
		अगर (err < 0)
			जाओ err_clk_prov;
	पूर्ण

	err = devm_add_action_or_reset(base->dev, rockchip_usb_phy_action,
				       rk_phy);
	अगर (err)
		वापस err;

	rk_phy->phy = devm_phy_create(base->dev, child, &ops);
	अगर (IS_ERR(rk_phy->phy)) अणु
		dev_err(base->dev, "failed to create PHY\n");
		वापस PTR_ERR(rk_phy->phy);
	पूर्ण
	phy_set_drvdata(rk_phy->phy, rk_phy);

	rk_phy->vbus = devm_regulator_get_optional(&rk_phy->phy->dev, "vbus");
	अगर (IS_ERR(rk_phy->vbus)) अणु
		अगर (PTR_ERR(rk_phy->vbus) == -EPROBE_DEFER)
			वापस PTR_ERR(rk_phy->vbus);
		rk_phy->vbus = शून्य;
	पूर्ण

	/*
	 * When acting as uart-pipe, just keep घड़ी on otherwise
	 * only घातer up usb phy when it use, so disable it when init
	 */
	अगर (rk_phy->uart_enabled)
		वापस clk_prepare_enable(rk_phy->clk);
	अन्यथा
		वापस rockchip_usb_phy_घातer(rk_phy, 1);

err_clk_prov:
	अगर (!rk_phy->uart_enabled)
		clk_unरेजिस्टर(rk_phy->clk480m);
err_clk:
	अगर (rk_phy->clk)
		clk_put(rk_phy->clk);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा rockchip_usb_phy_pdata rk3066a_pdata = अणु
	.phys = (काष्ठा rockchip_usb_phys[])अणु
		अणु .reg = 0x17c, .pll_name = "sclk_otgphy0_480m" पूर्ण,
		अणु .reg = 0x188, .pll_name = "sclk_otgphy1_480m" पूर्ण,
		अणु /* sentinel */ पूर्ण
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init rockchip_init_usb_uart_common(काष्ठा regmap *grf,
				स्थिर काष्ठा rockchip_usb_phy_pdata *pdata)
अणु
	पूर्णांक regoffs = pdata->phys[pdata->usb_uart_phy].reg;
	पूर्णांक ret;
	u32 val;

	/*
	 * COMMON_ON and DISABLE settings are described in the TRM,
	 * but were not present in the original code.
	 * Also disable the analog phy components to save घातer.
	 */
	val = HIWORD_UPDATE(UOC_CON0_COMMON_ON_N
				| UOC_CON0_DISABLE
				| UOC_CON0_SIDDQ,
			    UOC_CON0_COMMON_ON_N
				| UOC_CON0_DISABLE
				| UOC_CON0_SIDDQ);
	ret = regmap_ग_लिखो(grf, regoffs + UOC_CON0, val);
	अगर (ret)
		वापस ret;

	val = HIWORD_UPDATE(UOC_CON2_SOFT_CON_SEL,
			    UOC_CON2_SOFT_CON_SEL);
	ret = regmap_ग_लिखो(grf, regoffs + UOC_CON2, val);
	अगर (ret)
		वापस ret;

	val = HIWORD_UPDATE(UOC_CON3_UTMI_OPMODE_NODRIVING
				| UOC_CON3_UTMI_XCVRSEELCT_FSTRANSC
				| UOC_CON3_UTMI_TERMSEL_FULLSPEED,
			    UOC_CON3_UTMI_SUSPENDN
				| UOC_CON3_UTMI_OPMODE_MASK
				| UOC_CON3_UTMI_XCVRSEELCT_MASK
				| UOC_CON3_UTMI_TERMSEL_FULLSPEED);
	ret = regmap_ग_लिखो(grf, UOC_CON3, val);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

#घोषणा RK3188_UOC0_CON0				0x10c
#घोषणा RK3188_UOC0_CON0_BYPASSSEL			BIT(9)
#घोषणा RK3188_UOC0_CON0_BYPASSDMEN			BIT(8)

/*
 * Enable the bypass of uart2 data through the otg usb phy.
 * See description of rk3288-variant क्रम details.
 */
अटल पूर्णांक __init rk3188_init_usb_uart(काष्ठा regmap *grf,
				स्थिर काष्ठा rockchip_usb_phy_pdata *pdata)
अणु
	u32 val;
	पूर्णांक ret;

	ret = rockchip_init_usb_uart_common(grf, pdata);
	अगर (ret)
		वापस ret;

	val = HIWORD_UPDATE(RK3188_UOC0_CON0_BYPASSSEL
				| RK3188_UOC0_CON0_BYPASSDMEN,
			    RK3188_UOC0_CON0_BYPASSSEL
				| RK3188_UOC0_CON0_BYPASSDMEN);
	ret = regmap_ग_लिखो(grf, RK3188_UOC0_CON0, val);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rockchip_usb_phy_pdata rk3188_pdata = अणु
	.phys = (काष्ठा rockchip_usb_phys[])अणु
		अणु .reg = 0x10c, .pll_name = "sclk_otgphy0_480m" पूर्ण,
		अणु .reg = 0x11c, .pll_name = "sclk_otgphy1_480m" पूर्ण,
		अणु /* sentinel */ पूर्ण
	पूर्ण,
	.init_usb_uart = rk3188_init_usb_uart,
	.usb_uart_phy = 0,
पूर्ण;

#घोषणा RK3288_UOC0_CON3				0x32c
#घोषणा RK3288_UOC0_CON3_BYPASSDMEN			BIT(6)
#घोषणा RK3288_UOC0_CON3_BYPASSSEL			BIT(7)

/*
 * Enable the bypass of uart2 data through the otg usb phy.
 * Original description in the TRM.
 * 1. Disable the OTG block by setting OTGDISABLE0 to 1ै b1.
 * 2. Disable the pull-up resistance on the D+ line by setting
 *    OPMODE0[1:0] to 2ै b01.
 * 3. To ensure that the XO, Bias, and PLL blocks are घातered करोwn in Suspend
 *    mode, set COMMONONN to 1ै b1.
 * 4. Place the USB PHY in Suspend mode by setting SUSPENDM0 to 1ै b0.
 * 5. Set BYPASSSEL0 to 1ै b1.
 * 6. To transmit data, controls BYPASSDMEN0, and BYPASSDMDATA0.
 * To receive data, monitor FSVPLUS0.
 *
 * The actual code in the venकरोr kernel करोes some things dअगरferently.
 */
अटल पूर्णांक __init rk3288_init_usb_uart(काष्ठा regmap *grf,
				स्थिर काष्ठा rockchip_usb_phy_pdata *pdata)
अणु
	u32 val;
	पूर्णांक ret;

	ret = rockchip_init_usb_uart_common(grf, pdata);
	अगर (ret)
		वापस ret;

	val = HIWORD_UPDATE(RK3288_UOC0_CON3_BYPASSSEL
				| RK3288_UOC0_CON3_BYPASSDMEN,
			    RK3288_UOC0_CON3_BYPASSSEL
				| RK3288_UOC0_CON3_BYPASSDMEN);
	ret = regmap_ग_लिखो(grf, RK3288_UOC0_CON3, val);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rockchip_usb_phy_pdata rk3288_pdata = अणु
	.phys = (काष्ठा rockchip_usb_phys[])अणु
		अणु .reg = 0x320, .pll_name = "sclk_otgphy0_480m" पूर्ण,
		अणु .reg = 0x334, .pll_name = "sclk_otgphy1_480m" पूर्ण,
		अणु .reg = 0x348, .pll_name = "sclk_otgphy2_480m" पूर्ण,
		अणु /* sentinel */ पूर्ण
	पूर्ण,
	.init_usb_uart = rk3288_init_usb_uart,
	.usb_uart_phy = 0,
पूर्ण;

अटल पूर्णांक rockchip_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rockchip_usb_phy_base *phy_base;
	काष्ठा phy_provider *phy_provider;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *child;
	पूर्णांक err;

	phy_base = devm_kzalloc(dev, माप(*phy_base), GFP_KERNEL);
	अगर (!phy_base)
		वापस -ENOMEM;

	match = of_match_device(dev->driver->of_match_table, dev);
	अगर (!match || !match->data) अणु
		dev_err(dev, "missing phy data\n");
		वापस -EINVAL;
	पूर्ण

	phy_base->pdata = match->data;

	phy_base->dev = dev;
	phy_base->reg_base = ERR_PTR(-ENODEV);
	अगर (dev->parent && dev->parent->of_node)
		phy_base->reg_base = syscon_node_to_regmap(
						dev->parent->of_node);
	अगर (IS_ERR(phy_base->reg_base))
		phy_base->reg_base = syscon_regmap_lookup_by_phandle(
						dev->of_node, "rockchip,grf");
	अगर (IS_ERR(phy_base->reg_base)) अणु
		dev_err(&pdev->dev, "Missing rockchip,grf property\n");
		वापस PTR_ERR(phy_base->reg_base);
	पूर्ण

	क्रम_each_available_child_of_node(dev->of_node, child) अणु
		err = rockchip_usb_phy_init(phy_base, child);
		अगर (err) अणु
			of_node_put(child);
			वापस err;
		पूर्ण
	पूर्ण

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id rockchip_usb_phy_dt_ids[] = अणु
	अणु .compatible = "rockchip,rk3066a-usb-phy", .data = &rk3066a_pdata पूर्ण,
	अणु .compatible = "rockchip,rk3188-usb-phy", .data = &rk3188_pdata पूर्ण,
	अणु .compatible = "rockchip,rk3288-usb-phy", .data = &rk3288_pdata पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, rockchip_usb_phy_dt_ids);

अटल काष्ठा platक्रमm_driver rockchip_usb_driver = अणु
	.probe		= rockchip_usb_phy_probe,
	.driver		= अणु
		.name	= "rockchip-usb-phy",
		.of_match_table = rockchip_usb_phy_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rockchip_usb_driver);

#अगर_अघोषित MODULE
अटल पूर्णांक __init rockchip_init_usb_uart(व्योम)
अणु
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा rockchip_usb_phy_pdata *data;
	काष्ठा device_node *np;
	काष्ठा regmap *grf;
	पूर्णांक ret;

	अगर (!enable_usb_uart)
		वापस 0;

	np = of_find_matching_node_and_match(शून्य, rockchip_usb_phy_dt_ids,
					     &match);
	अगर (!np) अणु
		pr_err("%s: failed to find usbphy node\n", __func__);
		वापस -ENOTSUPP;
	पूर्ण

	pr_debug("%s: using settings for %s\n", __func__, match->compatible);
	data = match->data;

	अगर (!data->init_usb_uart) अणु
		pr_err("%s: usb-uart not available on %s\n",
		       __func__, match->compatible);
		वापस -ENOTSUPP;
	पूर्ण

	grf = ERR_PTR(-ENODEV);
	अगर (np->parent)
		grf = syscon_node_to_regmap(np->parent);
	अगर (IS_ERR(grf))
		grf = syscon_regmap_lookup_by_phandle(np, "rockchip,grf");
	अगर (IS_ERR(grf)) अणु
		pr_err("%s: Missing rockchip,grf property, %lu\n",
		       __func__, PTR_ERR(grf));
		वापस PTR_ERR(grf);
	पूर्ण

	ret = data->init_usb_uart(grf, data);
	अगर (ret) अणु
		pr_err("%s: could not init usb_uart, %d\n", __func__, ret);
		enable_usb_uart = 0;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
early_initcall(rockchip_init_usb_uart);

अटल पूर्णांक __init rockchip_usb_uart(अक्षर *buf)
अणु
	enable_usb_uart = true;
	वापस 0;
पूर्ण
early_param("rockchip.usb_uart", rockchip_usb_uart);
#पूर्ण_अगर

MODULE_AUTHOR("Yunzhi Li <lyz@rock-chips.com>");
MODULE_DESCRIPTION("Rockchip USB 2.0 PHY driver");
MODULE_LICENSE("GPL v2");
