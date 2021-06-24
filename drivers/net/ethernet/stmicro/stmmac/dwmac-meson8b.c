<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Amlogic Meson8b, Meson8m2 and GXBB DWMAC glue layer
 *
 * Copyright (C) 2016 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_net.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sपंचांगmac.h>

#समावेश "stmmac_platform.h"

#घोषणा PRG_ETH0			0x0

#घोषणा PRG_ETH0_RGMII_MODE		BIT(0)

#घोषणा PRG_ETH0_EXT_PHY_MODE_MASK	GENMASK(2, 0)
#घोषणा PRG_ETH0_EXT_RGMII_MODE		1
#घोषणा PRG_ETH0_EXT_RMII_MODE		4

/* mux to choose between fclk_भाग2 (bit unset) and mpll2 (bit set) */
#घोषणा PRG_ETH0_CLK_M250_SEL_MASK	GENMASK(4, 4)

/* TX घड़ी delay in ns = "8ns / 4 * tx_dly_val" (where 8ns are exactly one
 * cycle of the 125MHz RGMII TX घड़ी):
 * 0ns = 0x0, 2ns = 0x1, 4ns = 0x2, 6ns = 0x3
 */
#घोषणा PRG_ETH0_TXDLY_MASK		GENMASK(6, 5)

/* भागider क्रम the result of m250_sel */
#घोषणा PRG_ETH0_CLK_M250_DIV_SHIFT	7
#घोषणा PRG_ETH0_CLK_M250_DIV_WIDTH	3

#घोषणा PRG_ETH0_RGMII_TX_CLK_EN	10

#घोषणा PRG_ETH0_INVERTED_RMII_CLK	BIT(11)
#घोषणा PRG_ETH0_TX_AND_PHY_REF_CLK	BIT(12)

/* Bypass (= 0, the संकेत from the GPIO input directly connects to the
 * पूर्णांकernal sampling) or enable (= 1) the पूर्णांकernal logic क्रम RXEN and RXD[3:0]
 * timing tuning.
 */
#घोषणा PRG_ETH0_ADJ_ENABLE		BIT(13)
/* Controls whether the RXEN and RXD[3:0] संकेतs should be aligned with the
 * input RX rising/falling edge and sent to the Ethernet पूर्णांकernals. This sets
 * the स्वतःmatically delay and skew स्वतःmatically (पूर्णांकernally).
 */
#घोषणा PRG_ETH0_ADJ_SETUP		BIT(14)
/* An पूर्णांकernal counter based on the "timing-adjustment" घड़ी. The counter is
 * cleared on both, the falling and rising edge of the RX_CLK. This selects the
 * delay (= the counter value) when to start sampling RXEN and RXD[3:0].
 */
#घोषणा PRG_ETH0_ADJ_DELAY		GENMASK(19, 15)
/* Adjusts the skew between each bit of RXEN and RXD[3:0]. If a संकेत has a
 * large input delay, the bit क्रम that संकेत (RXEN = bit 0, RXD[3] = bit 1,
 * ...) can be configured to be 1 to compensate क्रम a delay of about 1ns.
 */
#घोषणा PRG_ETH0_ADJ_SKEW		GENMASK(24, 20)

#घोषणा PRG_ETH1			0x4

/* Defined क्रम adding a delay to the input RX_CLK क्रम better timing.
 * Each step is 200ps. These bits are used with बाह्यal RGMII PHYs
 * because RGMII RX only has the small winकरोw. cfg_rxclk_dly can
 * adjust the winकरोw between RX_CLK and RX_DATA and improve the stability
 * of "rx data valid".
 */
#घोषणा PRG_ETH1_CFG_RXCLK_DLY		GENMASK(19, 16)

काष्ठा meson8b_dwmac;

काष्ठा meson8b_dwmac_data अणु
	पूर्णांक (*set_phy_mode)(काष्ठा meson8b_dwmac *dwmac);
	bool has_prg_eth1_rgmii_rx_delay;
पूर्ण;

काष्ठा meson8b_dwmac अणु
	काष्ठा device			*dev;
	व्योम __iomem			*regs;

	स्थिर काष्ठा meson8b_dwmac_data	*data;
	phy_पूर्णांकerface_t			phy_mode;
	काष्ठा clk			*rgmii_tx_clk;
	u32				tx_delay_ns;
	u32				rx_delay_ps;
	काष्ठा clk			*timing_adj_clk;
पूर्ण;

काष्ठा meson8b_dwmac_clk_configs अणु
	काष्ठा clk_mux		m250_mux;
	काष्ठा clk_भागider	m250_भाग;
	काष्ठा clk_fixed_factor	fixed_भाग2;
	काष्ठा clk_gate		rgmii_tx_en;
पूर्ण;

अटल व्योम meson8b_dwmac_mask_bits(काष्ठा meson8b_dwmac *dwmac, u32 reg,
				    u32 mask, u32 value)
अणु
	u32 data;

	data = पढ़ोl(dwmac->regs + reg);
	data &= ~mask;
	data |= (value & mask);

	ग_लिखोl(data, dwmac->regs + reg);
पूर्ण

अटल काष्ठा clk *meson8b_dwmac_रेजिस्टर_clk(काष्ठा meson8b_dwmac *dwmac,
					      स्थिर अक्षर *name_suffix,
					      स्थिर काष्ठा clk_parent_data *parents,
					      पूर्णांक num_parents,
					      स्थिर काष्ठा clk_ops *ops,
					      काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_init_data init = अणु पूर्ण;
	अक्षर clk_name[32];

	snम_लिखो(clk_name, माप(clk_name), "%s#%s", dev_name(dwmac->dev),
		 name_suffix);

	init.name = clk_name;
	init.ops = ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_data = parents;
	init.num_parents = num_parents;

	hw->init = &init;

	वापस devm_clk_रेजिस्टर(dwmac->dev, hw);
पूर्ण

अटल पूर्णांक meson8b_init_rgmii_tx_clk(काष्ठा meson8b_dwmac *dwmac)
अणु
	काष्ठा clk *clk;
	काष्ठा device *dev = dwmac->dev;
	अटल स्थिर काष्ठा clk_parent_data mux_parents[] = अणु
		अणु .fw_name = "clkin0", पूर्ण,
		अणु .index = -1, पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा clk_भाग_प्रकारable भाग_प्रकारable[] = अणु
		अणु .भाग = 2, .val = 2, पूर्ण,
		अणु .भाग = 3, .val = 3, पूर्ण,
		अणु .भाग = 4, .val = 4, पूर्ण,
		अणु .भाग = 5, .val = 5, पूर्ण,
		अणु .भाग = 6, .val = 6, पूर्ण,
		अणु .भाग = 7, .val = 7, पूर्ण,
		अणु /* end of array */ पूर्ण
	पूर्ण;
	काष्ठा meson8b_dwmac_clk_configs *clk_configs;
	काष्ठा clk_parent_data parent_data = अणु पूर्ण;

	clk_configs = devm_kzalloc(dev, माप(*clk_configs), GFP_KERNEL);
	अगर (!clk_configs)
		वापस -ENOMEM;

	clk_configs->m250_mux.reg = dwmac->regs + PRG_ETH0;
	clk_configs->m250_mux.shअगरt = __ffs(PRG_ETH0_CLK_M250_SEL_MASK);
	clk_configs->m250_mux.mask = PRG_ETH0_CLK_M250_SEL_MASK >>
				     clk_configs->m250_mux.shअगरt;
	clk = meson8b_dwmac_रेजिस्टर_clk(dwmac, "m250_sel", mux_parents,
					 ARRAY_SIZE(mux_parents), &clk_mux_ops,
					 &clk_configs->m250_mux.hw);
	अगर (WARN_ON(IS_ERR(clk)))
		वापस PTR_ERR(clk);

	parent_data.hw = &clk_configs->m250_mux.hw;
	clk_configs->m250_भाग.reg = dwmac->regs + PRG_ETH0;
	clk_configs->m250_भाग.shअगरt = PRG_ETH0_CLK_M250_DIV_SHIFT;
	clk_configs->m250_भाग.width = PRG_ETH0_CLK_M250_DIV_WIDTH;
	clk_configs->m250_भाग.table = भाग_प्रकारable;
	clk_configs->m250_भाग.flags = CLK_DIVIDER_ALLOW_ZERO |
				      CLK_DIVIDER_ROUND_CLOSEST;
	clk = meson8b_dwmac_रेजिस्टर_clk(dwmac, "m250_div", &parent_data, 1,
					 &clk_भागider_ops,
					 &clk_configs->m250_भाग.hw);
	अगर (WARN_ON(IS_ERR(clk)))
		वापस PTR_ERR(clk);

	parent_data.hw = &clk_configs->m250_भाग.hw;
	clk_configs->fixed_भाग2.mult = 1;
	clk_configs->fixed_भाग2.भाग = 2;
	clk = meson8b_dwmac_रेजिस्टर_clk(dwmac, "fixed_div2", &parent_data, 1,
					 &clk_fixed_factor_ops,
					 &clk_configs->fixed_भाग2.hw);
	अगर (WARN_ON(IS_ERR(clk)))
		वापस PTR_ERR(clk);

	parent_data.hw = &clk_configs->fixed_भाग2.hw;
	clk_configs->rgmii_tx_en.reg = dwmac->regs + PRG_ETH0;
	clk_configs->rgmii_tx_en.bit_idx = PRG_ETH0_RGMII_TX_CLK_EN;
	clk = meson8b_dwmac_रेजिस्टर_clk(dwmac, "rgmii_tx_en", &parent_data, 1,
					 &clk_gate_ops,
					 &clk_configs->rgmii_tx_en.hw);
	अगर (WARN_ON(IS_ERR(clk)))
		वापस PTR_ERR(clk);

	dwmac->rgmii_tx_clk = clk;

	वापस 0;
पूर्ण

अटल पूर्णांक meson8b_set_phy_mode(काष्ठा meson8b_dwmac *dwmac)
अणु
	चयन (dwmac->phy_mode) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		/* enable RGMII mode */
		meson8b_dwmac_mask_bits(dwmac, PRG_ETH0,
					PRG_ETH0_RGMII_MODE,
					PRG_ETH0_RGMII_MODE);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		/* disable RGMII mode -> enables RMII mode */
		meson8b_dwmac_mask_bits(dwmac, PRG_ETH0,
					PRG_ETH0_RGMII_MODE, 0);
		अवरोध;
	शेष:
		dev_err(dwmac->dev, "fail to set phy-mode %s\n",
			phy_modes(dwmac->phy_mode));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक meson_axg_set_phy_mode(काष्ठा meson8b_dwmac *dwmac)
अणु
	चयन (dwmac->phy_mode) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		/* enable RGMII mode */
		meson8b_dwmac_mask_bits(dwmac, PRG_ETH0,
					PRG_ETH0_EXT_PHY_MODE_MASK,
					PRG_ETH0_EXT_RGMII_MODE);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		/* disable RGMII mode -> enables RMII mode */
		meson8b_dwmac_mask_bits(dwmac, PRG_ETH0,
					PRG_ETH0_EXT_PHY_MODE_MASK,
					PRG_ETH0_EXT_RMII_MODE);
		अवरोध;
	शेष:
		dev_err(dwmac->dev, "fail to set phy-mode %s\n",
			phy_modes(dwmac->phy_mode));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक meson8b_devm_clk_prepare_enable(काष्ठा meson8b_dwmac *dwmac,
					   काष्ठा clk *clk)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(clk);
	अगर (ret)
		वापस ret;

	devm_add_action_or_reset(dwmac->dev,
				 (व्योम(*)(व्योम *))clk_disable_unprepare,
				 dwmac->rgmii_tx_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक meson8b_init_rgmii_delays(काष्ठा meson8b_dwmac *dwmac)
अणु
	u32 tx_dly_config, rx_adj_config, cfg_rxclk_dly, delay_config;
	पूर्णांक ret;

	rx_adj_config = 0;
	cfg_rxclk_dly = 0;
	tx_dly_config = FIELD_PREP(PRG_ETH0_TXDLY_MASK,
				   dwmac->tx_delay_ns >> 1);

	अगर (dwmac->data->has_prg_eth1_rgmii_rx_delay)
		cfg_rxclk_dly = FIELD_PREP(PRG_ETH1_CFG_RXCLK_DLY,
					   dwmac->rx_delay_ps / 200);
	अन्यथा अगर (dwmac->rx_delay_ps == 2000)
		rx_adj_config = PRG_ETH0_ADJ_ENABLE | PRG_ETH0_ADJ_SETUP;

	चयन (dwmac->phy_mode) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
		delay_config = tx_dly_config | rx_adj_config;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
		delay_config = tx_dly_config;
		cfg_rxclk_dly = 0;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		delay_config = rx_adj_config;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RMII:
		delay_config = 0;
		cfg_rxclk_dly = 0;
		अवरोध;
	शेष:
		dev_err(dwmac->dev, "unsupported phy-mode %s\n",
			phy_modes(dwmac->phy_mode));
		वापस -EINVAL;
	पूर्ण

	अगर (delay_config & PRG_ETH0_ADJ_ENABLE) अणु
		अगर (!dwmac->timing_adj_clk) अणु
			dev_err(dwmac->dev,
				"The timing-adjustment clock is mandatory for the RX delay re-timing\n");
			वापस -EINVAL;
		पूर्ण

		/* The timing adjusपंचांगent logic is driven by a separate घड़ी */
		ret = meson8b_devm_clk_prepare_enable(dwmac,
						      dwmac->timing_adj_clk);
		अगर (ret) अणु
			dev_err(dwmac->dev,
				"Failed to enable the timing-adjustment clock\n");
			वापस ret;
		पूर्ण
	पूर्ण

	meson8b_dwmac_mask_bits(dwmac, PRG_ETH0, PRG_ETH0_TXDLY_MASK |
				PRG_ETH0_ADJ_ENABLE | PRG_ETH0_ADJ_SETUP |
				PRG_ETH0_ADJ_DELAY | PRG_ETH0_ADJ_SKEW,
				delay_config);

	meson8b_dwmac_mask_bits(dwmac, PRG_ETH1, PRG_ETH1_CFG_RXCLK_DLY,
				cfg_rxclk_dly);

	वापस 0;
पूर्ण

अटल पूर्णांक meson8b_init_prg_eth(काष्ठा meson8b_dwmac *dwmac)
अणु
	पूर्णांक ret;

	अगर (phy_पूर्णांकerface_mode_is_rgmii(dwmac->phy_mode)) अणु
		/* only relevant क्रम RMII mode -> disable in RGMII mode */
		meson8b_dwmac_mask_bits(dwmac, PRG_ETH0,
					PRG_ETH0_INVERTED_RMII_CLK, 0);

		/* Configure the 125MHz RGMII TX घड़ी, the IP block changes
		 * the output स्वतःmatically (= without us having to configure
		 * a रेजिस्टर) based on the line-speed (125MHz क्रम Gbit speeds,
		 * 25MHz क्रम 100Mbit/s and 2.5MHz क्रम 10Mbit/s).
		 */
		ret = clk_set_rate(dwmac->rgmii_tx_clk, 125 * 1000 * 1000);
		अगर (ret) अणु
			dev_err(dwmac->dev,
				"failed to set RGMII TX clock\n");
			वापस ret;
		पूर्ण

		ret = meson8b_devm_clk_prepare_enable(dwmac,
						      dwmac->rgmii_tx_clk);
		अगर (ret) अणु
			dev_err(dwmac->dev,
				"failed to enable the RGMII TX clock\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* invert पूर्णांकernal clk_rmii_i to generate 25/2.5 tx_rx_clk */
		meson8b_dwmac_mask_bits(dwmac, PRG_ETH0,
					PRG_ETH0_INVERTED_RMII_CLK,
					PRG_ETH0_INVERTED_RMII_CLK);
	पूर्ण

	/* enable TX_CLK and PHY_REF_CLK generator */
	meson8b_dwmac_mask_bits(dwmac, PRG_ETH0, PRG_ETH0_TX_AND_PHY_REF_CLK,
				PRG_ETH0_TX_AND_PHY_REF_CLK);

	वापस 0;
पूर्ण

अटल पूर्णांक meson8b_dwmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	काष्ठा meson8b_dwmac *dwmac;
	पूर्णांक ret;

	ret = sपंचांगmac_get_platक्रमm_resources(pdev, &sपंचांगmac_res);
	अगर (ret)
		वापस ret;

	plat_dat = sपंचांगmac_probe_config_dt(pdev, sपंचांगmac_res.mac);
	अगर (IS_ERR(plat_dat))
		वापस PTR_ERR(plat_dat);

	dwmac = devm_kzalloc(&pdev->dev, माप(*dwmac), GFP_KERNEL);
	अगर (!dwmac) अणु
		ret = -ENOMEM;
		जाओ err_हटाओ_config_dt;
	पूर्ण

	dwmac->data = (स्थिर काष्ठा meson8b_dwmac_data *)
		of_device_get_match_data(&pdev->dev);
	अगर (!dwmac->data) अणु
		ret = -EINVAL;
		जाओ err_हटाओ_config_dt;
	पूर्ण
	dwmac->regs = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(dwmac->regs)) अणु
		ret = PTR_ERR(dwmac->regs);
		जाओ err_हटाओ_config_dt;
	पूर्ण

	dwmac->dev = &pdev->dev;
	ret = of_get_phy_mode(pdev->dev.of_node, &dwmac->phy_mode);
	अगर (ret) अणु
		dev_err(&pdev->dev, "missing phy-mode property\n");
		जाओ err_हटाओ_config_dt;
	पूर्ण

	/* use 2ns as fallback since this value was previously hardcoded */
	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "amlogic,tx-delay-ns",
				 &dwmac->tx_delay_ns))
		dwmac->tx_delay_ns = 2;

	/* RX delay शेषs to 0ps since this is what many boards use */
	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "rx-internal-delay-ps",
				 &dwmac->rx_delay_ps)) अणु
		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node,
					  "amlogic,rx-delay-ns",
					  &dwmac->rx_delay_ps))
			/* convert ns to ps */
			dwmac->rx_delay_ps *= 1000;
	पूर्ण

	अगर (dwmac->data->has_prg_eth1_rgmii_rx_delay) अणु
		अगर (dwmac->rx_delay_ps > 3000 || dwmac->rx_delay_ps % 200) अणु
			dev_err(dwmac->dev,
				"The RGMII RX delay range is 0..3000ps in 200ps steps");
			ret = -EINVAL;
			जाओ err_हटाओ_config_dt;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dwmac->rx_delay_ps != 0 && dwmac->rx_delay_ps != 2000) अणु
			dev_err(dwmac->dev,
				"The only allowed RGMII RX delays values are: 0ps, 2000ps");
			ret = -EINVAL;
			जाओ err_हटाओ_config_dt;
		पूर्ण
	पूर्ण

	dwmac->timing_adj_clk = devm_clk_get_optional(dwmac->dev,
						      "timing-adjustment");
	अगर (IS_ERR(dwmac->timing_adj_clk)) अणु
		ret = PTR_ERR(dwmac->timing_adj_clk);
		जाओ err_हटाओ_config_dt;
	पूर्ण

	ret = meson8b_init_rgmii_delays(dwmac);
	अगर (ret)
		जाओ err_हटाओ_config_dt;

	ret = meson8b_init_rgmii_tx_clk(dwmac);
	अगर (ret)
		जाओ err_हटाओ_config_dt;

	ret = dwmac->data->set_phy_mode(dwmac);
	अगर (ret)
		जाओ err_हटाओ_config_dt;

	ret = meson8b_init_prg_eth(dwmac);
	अगर (ret)
		जाओ err_हटाओ_config_dt;

	plat_dat->bsp_priv = dwmac;

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret)
		जाओ err_हटाओ_config_dt;

	वापस 0;

err_हटाओ_config_dt:
	sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा meson8b_dwmac_data meson8b_dwmac_data = अणु
	.set_phy_mode = meson8b_set_phy_mode,
	.has_prg_eth1_rgmii_rx_delay = false,
पूर्ण;

अटल स्थिर काष्ठा meson8b_dwmac_data meson_axg_dwmac_data = अणु
	.set_phy_mode = meson_axg_set_phy_mode,
	.has_prg_eth1_rgmii_rx_delay = false,
पूर्ण;

अटल स्थिर काष्ठा meson8b_dwmac_data meson_g12a_dwmac_data = अणु
	.set_phy_mode = meson_axg_set_phy_mode,
	.has_prg_eth1_rgmii_rx_delay = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson8b_dwmac_match[] = अणु
	अणु
		.compatible = "amlogic,meson8b-dwmac",
		.data = &meson8b_dwmac_data,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson8m2-dwmac",
		.data = &meson8b_dwmac_data,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-gxbb-dwmac",
		.data = &meson8b_dwmac_data,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-axg-dwmac",
		.data = &meson_axg_dwmac_data,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-g12a-dwmac",
		.data = &meson_g12a_dwmac_data,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson8b_dwmac_match);

अटल काष्ठा platक्रमm_driver meson8b_dwmac_driver = अणु
	.probe  = meson8b_dwmac_probe,
	.हटाओ = sपंचांगmac_pltfr_हटाओ,
	.driver = अणु
		.name           = "meson8b-dwmac",
		.pm		= &sपंचांगmac_pltfr_pm_ops,
		.of_match_table = meson8b_dwmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(meson8b_dwmac_driver);

MODULE_AUTHOR("Martin Blumenstingl <martin.blumenstingl@googlemail.com>");
MODULE_DESCRIPTION("Amlogic Meson8b, Meson8m2 and GXBB DWMAC glue layer");
MODULE_LICENSE("GPL v2");
