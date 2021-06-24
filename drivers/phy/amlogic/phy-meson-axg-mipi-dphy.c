<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Meson AXG MIPI DPHY driver
 *
 * Copyright (C) 2018 Amlogic, Inc. All rights reserved
 * Copyright (C) 2020 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

/* [31] soft reset क्रम the phy.
 *		1: reset. 0: dessert the reset.
 * [30] घड़ी lane soft reset.
 * [29] data byte lane 3 soft reset.
 * [28] data byte lane 2 soft reset.
 * [27] data byte lane 1 soft reset.
 * [26] data byte lane 0 soft reset.
 * [25] mipi dsi pll घड़ी selection.
 *		1:  घड़ी from fixed 850Mhz घड़ी source. 0: from VID2 PLL.
 * [12] mipi HSbyteclk enable.
 * [11] mipi भागider clk selection.
 *		1: select the mipi DDRCLKHS from घड़ी भागider.
 *		0: from PLL घड़ी.
 * [10] mipi घड़ी भागider control.
 *		1: /4. 0: /2.
 * [9]  mipi भागider output enable.
 * [8]  mipi भागider counter enable.
 * [7]  PLL घड़ी enable.
 * [5]  LPDT data endian.
 *		1 = transfer the high bit first. 0 : transfer the low bit first.
 * [4]  HS data endian.
 * [3]  क्रमce data byte lane in stop mode.
 * [2]  क्रमce data byte lane 0 in receiver mode.
 * [1]  ग_लिखो 1 to sync the txclkesc input. the पूर्णांकernal logic have to
 *	use txclkesc to decide Txvalid and Txपढ़ोy.
 * [0]  enalbe the MIPI DPHY TxDDRClk.
 */
#घोषणा MIPI_DSI_PHY_CTRL				0x0

/* [31] clk lane tx_hs_en control selection.
 *		1: from रेजिस्टर. 0: use clk lane state machine.
 * [30] रेजिस्टर bit क्रम घड़ी lane tx_hs_en.
 * [29] clk lane tx_lp_en contrl selection.
 *		1: from रेजिस्टर. 0: from clk lane state machine.
 * [28] रेजिस्टर bit क्रम घड़ी lane tx_lp_en.
 * [27] chan0 tx_hs_en control selection.
 *		1: from रेजिस्टर. 0: from chan0 state machine.
 * [26] रेजिस्टर bit क्रम chan0 tx_hs_en.
 * [25] chan0 tx_lp_en control selection.
 *		1: from रेजिस्टर. 0: from chan0 state machine.
 * [24] रेजिस्टर bit from chan0 tx_lp_en.
 * [23] chan0 rx_lp_en control selection.
 *		1: from रेजिस्टर. 0: from chan0 state machine.
 * [22] रेजिस्टर bit from chan0 rx_lp_en.
 * [21] chan0 contention detection enable control selection.
 *		1: from रेजिस्टर. 0: from chan0 state machine.
 * [20] रेजिस्टर bit from chan0 contention dectection enable.
 * [19] chan1 tx_hs_en control selection.
 *		1: from रेजिस्टर. 0: from chan0 state machine.
 * [18] रेजिस्टर bit क्रम chan1 tx_hs_en.
 * [17] chan1 tx_lp_en control selection.
 *		1: from रेजिस्टर. 0: from chan0 state machine.
 * [16] रेजिस्टर bit from chan1 tx_lp_en.
 * [15] chan2 tx_hs_en control selection.
 *		1: from रेजिस्टर. 0: from chan0 state machine.
 * [14] रेजिस्टर bit क्रम chan2 tx_hs_en.
 * [13] chan2 tx_lp_en control selection.
 *		1: from रेजिस्टर. 0: from chan0 state machine.
 * [12] रेजिस्टर bit from chan2 tx_lp_en.
 * [11] chan3 tx_hs_en control selection.
 *		1: from रेजिस्टर. 0: from chan0 state machine.
 * [10] रेजिस्टर bit क्रम chan3 tx_hs_en.
 * [9]  chan3 tx_lp_en control selection.
 *		1: from रेजिस्टर. 0: from chan0 state machine.
 * [8]  रेजिस्टर bit from chan3 tx_lp_en.
 * [4]  clk chan घातer करोwn. this bit is also used as the घातer करोwn
 *	of the whole MIPI_DSI_PHY.
 * [3]  chan3 घातer करोwn.
 * [2]  chan2 घातer करोwn.
 * [1]  chan1 घातer करोwn.
 * [0]  chan0 घातer करोwn.
 */
#घोषणा MIPI_DSI_CHAN_CTRL				0x4

/* [24]   rx turn watch करोg triggered.
 * [23]   rx esc watchकरोg  triggered.
 * [22]   mbias पढ़ोy.
 * [21]   txclkesc  synced and पढ़ोy.
 * [20:17] clk lane state. अणुmbias_पढ़ोy, tx_stop, tx_ulps, tx_hs_activeपूर्ण
 * [16:13] chan3 stateअणु0, tx_stop, tx_ulps, tx_hs_activeपूर्ण
 * [12:9]  chan2 state.अणु0, tx_stop, tx_ulps, tx_hs_activeपूर्ण
 * [8:5]   chan1 state. अणु0, tx_stop, tx_ulps, tx_hs_activeपूर्ण
 * [4:0]   chan0 state. अणुTX_STOP, tx_ULPS, hs_active, direction, rxulpsescपूर्ण
 */
#घोषणा MIPI_DSI_CHAN_STS				0x8

/* [31:24] TCLK_PREPARE.
 * [23:16] TCLK_ZERO.
 * [15:8]  TCLK_POST.
 * [7:0]   TCLK_TRAIL.
 */
#घोषणा MIPI_DSI_CLK_TIM				0xc

/* [31:24] THS_PREPARE.
 * [23:16] THS_ZERO.
 * [15:8]  THS_TRAIL.
 * [7:0]   THS_EXIT.
 */
#घोषणा MIPI_DSI_HS_TIM					0x10

/* [31:24] tTA_GET.
 * [23:16] tTA_GO.
 * [15:8]  tTA_SURE.
 * [7:0]   tLPX.
 */
#घोषणा MIPI_DSI_LP_TIM					0x14

/* रुको समय to  MIPI DIS analog पढ़ोy. */
#घोषणा MIPI_DSI_ANA_UP_TIM				0x18

/* TINIT. */
#घोषणा MIPI_DSI_INIT_TIM				0x1c

/* TWAKEUP. */
#घोषणा MIPI_DSI_WAKEUP_TIM				0x20

/* when in RxULPS check state, after the the logic enable the analog,
 *	how दीर्घ we should रुको to check the lP state .
 */
#घोषणा MIPI_DSI_LPOK_TIM				0x24

/* Watchकरोg क्रम RX low घातer state no finished. */
#घोषणा MIPI_DSI_LP_WCHDOG				0x28

/* tMBIAS,  after send घातer up संकेतs to analog,
 *	how दीर्घ we should रुको क्रम analog घातered up.
 */
#घोषणा MIPI_DSI_ANA_CTRL				0x2c

/* [31:8]  reserved क्रम future.
 * [7:0]   tCLK_PRE.
 */
#घोषणा MIPI_DSI_CLK_TIM1				0x30

/* watchकरोg क्रम turn around रुकोing समय. */
#घोषणा MIPI_DSI_TURN_WCHDOG				0x34

/* When in RxULPS state, how frequency we should to check
 *	अगर the TX side out of ULPS state.
 */
#घोषणा MIPI_DSI_ULPS_CHECK				0x38
#घोषणा MIPI_DSI_TEST_CTRL0				0x3c
#घोषणा MIPI_DSI_TEST_CTRL1				0x40

काष्ठा phy_meson_axg_mipi_dphy_priv अणु
	काष्ठा device				*dev;
	काष्ठा regmap				*regmap;
	काष्ठा clk				*clk;
	काष्ठा reset_control			*reset;
	काष्ठा phy				*analog;
	काष्ठा phy_configure_opts_mipi_dphy	config;
पूर्ण;

अटल स्थिर काष्ठा regmap_config phy_meson_axg_mipi_dphy_regmap_conf = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = MIPI_DSI_TEST_CTRL1,
पूर्ण;

अटल पूर्णांक phy_meson_axg_mipi_dphy_init(काष्ठा phy *phy)
अणु
	काष्ठा phy_meson_axg_mipi_dphy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = phy_init(priv->analog);
	अगर (ret)
		वापस ret;

	ret = reset_control_reset(priv->reset);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक phy_meson_axg_mipi_dphy_configure(काष्ठा phy *phy,
					      जोड़ phy_configure_opts *opts)
अणु
	काष्ठा phy_meson_axg_mipi_dphy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = phy_mipi_dphy_config_validate(&opts->mipi_dphy);
	अगर (ret)
		वापस ret;

	ret = phy_configure(priv->analog, opts);
	अगर (ret)
		वापस ret;

	स_नकल(&priv->config, opts, माप(priv->config));

	वापस 0;
पूर्ण

अटल पूर्णांक phy_meson_axg_mipi_dphy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा phy_meson_axg_mipi_dphy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;
	अचिन्हित दीर्घ temp;

	ret = phy_घातer_on(priv->analog);
	अगर (ret)
		वापस ret;

	/* enable phy घड़ी */
	regmap_ग_लिखो(priv->regmap, MIPI_DSI_PHY_CTRL,  0x1);
	regmap_ग_लिखो(priv->regmap, MIPI_DSI_PHY_CTRL,
		     BIT(0) | /* enable the DSI PLL घड़ी . */
		     BIT(7) | /* enable pll घड़ी which connected to DDR घड़ी path */
		     BIT(8)); /* enable the घड़ी भागider counter */

	/* enable the भागider घड़ी out */
	regmap_update_bits(priv->regmap, MIPI_DSI_PHY_CTRL, BIT(9), BIT(9));

	/* enable the byte घड़ी generation. */
	regmap_update_bits(priv->regmap, MIPI_DSI_PHY_CTRL, BIT(12), BIT(12));
	regmap_update_bits(priv->regmap, MIPI_DSI_PHY_CTRL, BIT(31), BIT(31));
	regmap_update_bits(priv->regmap, MIPI_DSI_PHY_CTRL, BIT(31), 0);

	/* Calculate lanebyteclk period in ps */
	temp = (1000000 * 100) / (priv->config.hs_clk_rate / 1000);
	temp = temp * 8 * 10;

	regmap_ग_लिखो(priv->regmap, MIPI_DSI_CLK_TIM,
		     DIV_ROUND_UP(priv->config.clk_trail, temp) |
		     (DIV_ROUND_UP(priv->config.clk_post +
				   priv->config.hs_trail, temp) << 8) |
		     (DIV_ROUND_UP(priv->config.clk_zero, temp) << 16) |
		     (DIV_ROUND_UP(priv->config.clk_prepare, temp) << 24));
	regmap_ग_लिखो(priv->regmap, MIPI_DSI_CLK_TIM1,
		     DIV_ROUND_UP(priv->config.clk_pre, temp));

	regmap_ग_लिखो(priv->regmap, MIPI_DSI_HS_TIM,
		     DIV_ROUND_UP(priv->config.hs_निकास, temp) |
		     (DIV_ROUND_UP(priv->config.hs_trail, temp) << 8) |
		     (DIV_ROUND_UP(priv->config.hs_zero, temp) << 16) |
		     (DIV_ROUND_UP(priv->config.hs_prepare, temp) << 24));

	regmap_ग_लिखो(priv->regmap, MIPI_DSI_LP_TIM,
		     DIV_ROUND_UP(priv->config.lpx, temp) |
		     (DIV_ROUND_UP(priv->config.ta_sure, temp) << 8) |
		     (DIV_ROUND_UP(priv->config.ta_go, temp) << 16) |
		     (DIV_ROUND_UP(priv->config.ta_get, temp) << 24));

	regmap_ग_लिखो(priv->regmap, MIPI_DSI_ANA_UP_TIM, 0x0100);
	regmap_ग_लिखो(priv->regmap, MIPI_DSI_INIT_TIM,
		     DIV_ROUND_UP(priv->config.init * NSEC_PER_MSEC, temp));
	regmap_ग_लिखो(priv->regmap, MIPI_DSI_WAKEUP_TIM,
		     DIV_ROUND_UP(priv->config.wakeup * NSEC_PER_MSEC, temp));
	regmap_ग_लिखो(priv->regmap, MIPI_DSI_LPOK_TIM, 0x7C);
	regmap_ग_लिखो(priv->regmap, MIPI_DSI_ULPS_CHECK, 0x927C);
	regmap_ग_लिखो(priv->regmap, MIPI_DSI_LP_WCHDOG, 0x1000);
	regmap_ग_लिखो(priv->regmap, MIPI_DSI_TURN_WCHDOG, 0x1000);

	/* Powerup the analog circuit */
	चयन (priv->config.lanes) अणु
	हाल 1:
		regmap_ग_लिखो(priv->regmap, MIPI_DSI_CHAN_CTRL, 0xe);
		अवरोध;
	हाल 2:
		regmap_ग_लिखो(priv->regmap, MIPI_DSI_CHAN_CTRL, 0xc);
		अवरोध;
	हाल 3:
		regmap_ग_लिखो(priv->regmap, MIPI_DSI_CHAN_CTRL, 0x8);
		अवरोध;
	हाल 4:
	शेष:
		regmap_ग_लिखो(priv->regmap, MIPI_DSI_CHAN_CTRL, 0);
		अवरोध;
	पूर्ण

	/* Trigger a sync active क्रम esc_clk */
	regmap_update_bits(priv->regmap, MIPI_DSI_PHY_CTRL, BIT(1), BIT(1));

	वापस 0;
पूर्ण

अटल पूर्णांक phy_meson_axg_mipi_dphy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा phy_meson_axg_mipi_dphy_priv *priv = phy_get_drvdata(phy);

	regmap_ग_लिखो(priv->regmap, MIPI_DSI_CHAN_CTRL, 0xf);
	regmap_ग_लिखो(priv->regmap, MIPI_DSI_PHY_CTRL, BIT(31));

	phy_घातer_off(priv->analog);

	वापस 0;
पूर्ण

अटल पूर्णांक phy_meson_axg_mipi_dphy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा phy_meson_axg_mipi_dphy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = phy_निकास(priv->analog);
	अगर (ret)
		वापस ret;

	वापस reset_control_reset(priv->reset);
पूर्ण

अटल स्थिर काष्ठा phy_ops phy_meson_axg_mipi_dphy_ops = अणु
	.configure	= phy_meson_axg_mipi_dphy_configure,
	.init		= phy_meson_axg_mipi_dphy_init,
	.निकास		= phy_meson_axg_mipi_dphy_निकास,
	.घातer_on	= phy_meson_axg_mipi_dphy_घातer_on,
	.घातer_off	= phy_meson_axg_mipi_dphy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक phy_meson_axg_mipi_dphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_provider *phy_provider;
	काष्ठा resource *res;
	काष्ठा phy_meson_axg_mipi_dphy_priv *priv;
	काष्ठा phy *phy;
	व्योम __iomem *base;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	platक्रमm_set_drvdata(pdev, priv);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	priv->regmap = devm_regmap_init_mmio(dev, base,
					&phy_meson_axg_mipi_dphy_regmap_conf);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	priv->clk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	priv->reset = devm_reset_control_get(dev, "phy");
	अगर (IS_ERR(priv->reset))
		वापस PTR_ERR(priv->reset);

	priv->analog = devm_phy_get(dev, "analog");
	अगर (IS_ERR(priv->analog))
		वापस PTR_ERR(priv->analog);

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	ret = reset_control_deनिश्चित(priv->reset);
	अगर (ret)
		वापस ret;

	phy = devm_phy_create(dev, शून्य, &phy_meson_axg_mipi_dphy_ops);
	अगर (IS_ERR(phy)) अणु
		ret = PTR_ERR(phy);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to create PHY\n");

		वापस ret;
	पूर्ण

	phy_set_drvdata(phy, priv);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id phy_meson_axg_mipi_dphy_of_match[] = अणु
	अणु .compatible = "amlogic,axg-mipi-dphy", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, phy_meson_axg_mipi_dphy_of_match);

अटल काष्ठा platक्रमm_driver phy_meson_axg_mipi_dphy_driver = अणु
	.probe	= phy_meson_axg_mipi_dphy_probe,
	.driver	= अणु
		.name		= "phy-meson-axg-mipi-dphy",
		.of_match_table	= phy_meson_axg_mipi_dphy_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(phy_meson_axg_mipi_dphy_driver);

MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_DESCRIPTION("Meson AXG MIPI DPHY driver");
MODULE_LICENSE("GPL v2");
