<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/**
 * DOC: dwmac-rk.c - Rockchip RK3288 DWMAC specअगरic glue layer
 *
 * Copyright (C) 2014 Chen-Zhi (Roger Chen)
 *
 * Chen-Zhi (Roger Chen)  <roger.chen@rock-chips.com>
 */

#समावेश <linux/sपंचांगmac.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/phy.h>
#समावेश <linux/of_net.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "stmmac_platform.h"

काष्ठा rk_priv_data;
काष्ठा rk_gmac_ops अणु
	व्योम (*set_to_rgmii)(काष्ठा rk_priv_data *bsp_priv,
			     पूर्णांक tx_delay, पूर्णांक rx_delay);
	व्योम (*set_to_rmii)(काष्ठा rk_priv_data *bsp_priv);
	व्योम (*set_rgmii_speed)(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed);
	व्योम (*set_rmii_speed)(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed);
	व्योम (*पूर्णांकegrated_phy_घातerup)(काष्ठा rk_priv_data *bsp_priv);
पूर्ण;

काष्ठा rk_priv_data अणु
	काष्ठा platक्रमm_device *pdev;
	phy_पूर्णांकerface_t phy_अगरace;
	काष्ठा regulator *regulator;
	bool suspended;
	स्थिर काष्ठा rk_gmac_ops *ops;

	bool clk_enabled;
	bool घड़ी_input;
	bool पूर्णांकegrated_phy;

	काष्ठा clk *clk_mac;
	काष्ठा clk *gmac_clkin;
	काष्ठा clk *mac_clk_rx;
	काष्ठा clk *mac_clk_tx;
	काष्ठा clk *clk_mac_ref;
	काष्ठा clk *clk_mac_refout;
	काष्ठा clk *clk_mac_speed;
	काष्ठा clk *aclk_mac;
	काष्ठा clk *pclk_mac;
	काष्ठा clk *clk_phy;

	काष्ठा reset_control *phy_reset;

	पूर्णांक tx_delay;
	पूर्णांक rx_delay;

	काष्ठा regmap *grf;
पूर्ण;

#घोषणा HIWORD_UPDATE(val, mask, shअगरt) \
		((val) << (shअगरt) | (mask) << ((shअगरt) + 16))

#घोषणा GRF_BIT(nr)	(BIT(nr) | BIT(nr+16))
#घोषणा GRF_CLR_BIT(nr)	(BIT(nr+16))

#घोषणा DELAY_ENABLE(soc, tx, rx) \
	(((tx) ? soc##_GMAC_TXCLK_DLY_ENABLE : soc##_GMAC_TXCLK_DLY_DISABLE) | \
	 ((rx) ? soc##_GMAC_RXCLK_DLY_ENABLE : soc##_GMAC_RXCLK_DLY_DISABLE))

#घोषणा PX30_GRF_GMAC_CON1		0x0904

/* PX30_GRF_GMAC_CON1 */
#घोषणा PX30_GMAC_PHY_INTF_SEL_RMII	(GRF_CLR_BIT(4) | GRF_CLR_BIT(5) | \
					 GRF_BIT(6))
#घोषणा PX30_GMAC_SPEED_10M		GRF_CLR_BIT(2)
#घोषणा PX30_GMAC_SPEED_100M		GRF_BIT(2)

अटल व्योम px30_set_to_rmii(काष्ठा rk_priv_data *bsp_priv)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "%s: Missing rockchip,grf property\n", __func__);
		वापस;
	पूर्ण

	regmap_ग_लिखो(bsp_priv->grf, PX30_GRF_GMAC_CON1,
		     PX30_GMAC_PHY_INTF_SEL_RMII);
पूर्ण

अटल व्योम px30_set_rmii_speed(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;
	पूर्णांक ret;

	अगर (IS_ERR(bsp_priv->clk_mac_speed)) अणु
		dev_err(dev, "%s: Missing clk_mac_speed clock\n", __func__);
		वापस;
	पूर्ण

	अगर (speed == 10) अणु
		regmap_ग_लिखो(bsp_priv->grf, PX30_GRF_GMAC_CON1,
			     PX30_GMAC_SPEED_10M);

		ret = clk_set_rate(bsp_priv->clk_mac_speed, 2500000);
		अगर (ret)
			dev_err(dev, "%s: set clk_mac_speed rate 2500000 failed: %d\n",
				__func__, ret);
	पूर्ण अन्यथा अगर (speed == 100) अणु
		regmap_ग_लिखो(bsp_priv->grf, PX30_GRF_GMAC_CON1,
			     PX30_GMAC_SPEED_100M);

		ret = clk_set_rate(bsp_priv->clk_mac_speed, 25000000);
		अगर (ret)
			dev_err(dev, "%s: set clk_mac_speed rate 25000000 failed: %d\n",
				__func__, ret);

	पूर्ण अन्यथा अणु
		dev_err(dev, "unknown speed value for RMII! speed=%d", speed);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rk_gmac_ops px30_ops = अणु
	.set_to_rmii = px30_set_to_rmii,
	.set_rmii_speed = px30_set_rmii_speed,
पूर्ण;

#घोषणा RK3128_GRF_MAC_CON0	0x0168
#घोषणा RK3128_GRF_MAC_CON1	0x016c

/* RK3128_GRF_MAC_CON0 */
#घोषणा RK3128_GMAC_TXCLK_DLY_ENABLE   GRF_BIT(14)
#घोषणा RK3128_GMAC_TXCLK_DLY_DISABLE  GRF_CLR_BIT(14)
#घोषणा RK3128_GMAC_RXCLK_DLY_ENABLE   GRF_BIT(15)
#घोषणा RK3128_GMAC_RXCLK_DLY_DISABLE  GRF_CLR_BIT(15)
#घोषणा RK3128_GMAC_CLK_RX_DL_CFG(val) HIWORD_UPDATE(val, 0x7F, 7)
#घोषणा RK3128_GMAC_CLK_TX_DL_CFG(val) HIWORD_UPDATE(val, 0x7F, 0)

/* RK3128_GRF_MAC_CON1 */
#घोषणा RK3128_GMAC_PHY_INTF_SEL_RGMII	\
		(GRF_BIT(6) | GRF_CLR_BIT(7) | GRF_CLR_BIT(8))
#घोषणा RK3128_GMAC_PHY_INTF_SEL_RMII	\
		(GRF_CLR_BIT(6) | GRF_CLR_BIT(7) | GRF_BIT(8))
#घोषणा RK3128_GMAC_FLOW_CTRL          GRF_BIT(9)
#घोषणा RK3128_GMAC_FLOW_CTRL_CLR      GRF_CLR_BIT(9)
#घोषणा RK3128_GMAC_SPEED_10M          GRF_CLR_BIT(10)
#घोषणा RK3128_GMAC_SPEED_100M         GRF_BIT(10)
#घोषणा RK3128_GMAC_RMII_CLK_25M       GRF_BIT(11)
#घोषणा RK3128_GMAC_RMII_CLK_2_5M      GRF_CLR_BIT(11)
#घोषणा RK3128_GMAC_CLK_125M           (GRF_CLR_BIT(12) | GRF_CLR_BIT(13))
#घोषणा RK3128_GMAC_CLK_25M            (GRF_BIT(12) | GRF_BIT(13))
#घोषणा RK3128_GMAC_CLK_2_5M           (GRF_CLR_BIT(12) | GRF_BIT(13))
#घोषणा RK3128_GMAC_RMII_MODE          GRF_BIT(14)
#घोषणा RK3128_GMAC_RMII_MODE_CLR      GRF_CLR_BIT(14)

अटल व्योम rk3128_set_to_rgmii(काष्ठा rk_priv_data *bsp_priv,
				पूर्णांक tx_delay, पूर्णांक rx_delay)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "Missing rockchip,grf property\n");
		वापस;
	पूर्ण

	regmap_ग_लिखो(bsp_priv->grf, RK3128_GRF_MAC_CON1,
		     RK3128_GMAC_PHY_INTF_SEL_RGMII |
		     RK3128_GMAC_RMII_MODE_CLR);
	regmap_ग_लिखो(bsp_priv->grf, RK3128_GRF_MAC_CON0,
		     DELAY_ENABLE(RK3128, tx_delay, rx_delay) |
		     RK3128_GMAC_CLK_RX_DL_CFG(rx_delay) |
		     RK3128_GMAC_CLK_TX_DL_CFG(tx_delay));
पूर्ण

अटल व्योम rk3128_set_to_rmii(काष्ठा rk_priv_data *bsp_priv)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "Missing rockchip,grf property\n");
		वापस;
	पूर्ण

	regmap_ग_लिखो(bsp_priv->grf, RK3128_GRF_MAC_CON1,
		     RK3128_GMAC_PHY_INTF_SEL_RMII | RK3128_GMAC_RMII_MODE);
पूर्ण

अटल व्योम rk3128_set_rgmii_speed(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "Missing rockchip,grf property\n");
		वापस;
	पूर्ण

	अगर (speed == 10)
		regmap_ग_लिखो(bsp_priv->grf, RK3128_GRF_MAC_CON1,
			     RK3128_GMAC_CLK_2_5M);
	अन्यथा अगर (speed == 100)
		regmap_ग_लिखो(bsp_priv->grf, RK3128_GRF_MAC_CON1,
			     RK3128_GMAC_CLK_25M);
	अन्यथा अगर (speed == 1000)
		regmap_ग_लिखो(bsp_priv->grf, RK3128_GRF_MAC_CON1,
			     RK3128_GMAC_CLK_125M);
	अन्यथा
		dev_err(dev, "unknown speed value for RGMII! speed=%d", speed);
पूर्ण

अटल व्योम rk3128_set_rmii_speed(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "Missing rockchip,grf property\n");
		वापस;
	पूर्ण

	अगर (speed == 10) अणु
		regmap_ग_लिखो(bsp_priv->grf, RK3128_GRF_MAC_CON1,
			     RK3128_GMAC_RMII_CLK_2_5M |
			     RK3128_GMAC_SPEED_10M);
	पूर्ण अन्यथा अगर (speed == 100) अणु
		regmap_ग_लिखो(bsp_priv->grf, RK3128_GRF_MAC_CON1,
			     RK3128_GMAC_RMII_CLK_25M |
			     RK3128_GMAC_SPEED_100M);
	पूर्ण अन्यथा अणु
		dev_err(dev, "unknown speed value for RMII! speed=%d", speed);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rk_gmac_ops rk3128_ops = अणु
	.set_to_rgmii = rk3128_set_to_rgmii,
	.set_to_rmii = rk3128_set_to_rmii,
	.set_rgmii_speed = rk3128_set_rgmii_speed,
	.set_rmii_speed = rk3128_set_rmii_speed,
पूर्ण;

#घोषणा RK3228_GRF_MAC_CON0	0x0900
#घोषणा RK3228_GRF_MAC_CON1	0x0904

#घोषणा RK3228_GRF_CON_MUX	0x50

/* RK3228_GRF_MAC_CON0 */
#घोषणा RK3228_GMAC_CLK_RX_DL_CFG(val)	HIWORD_UPDATE(val, 0x7F, 7)
#घोषणा RK3228_GMAC_CLK_TX_DL_CFG(val)	HIWORD_UPDATE(val, 0x7F, 0)

/* RK3228_GRF_MAC_CON1 */
#घोषणा RK3228_GMAC_PHY_INTF_SEL_RGMII	\
		(GRF_BIT(4) | GRF_CLR_BIT(5) | GRF_CLR_BIT(6))
#घोषणा RK3228_GMAC_PHY_INTF_SEL_RMII	\
		(GRF_CLR_BIT(4) | GRF_CLR_BIT(5) | GRF_BIT(6))
#घोषणा RK3228_GMAC_FLOW_CTRL		GRF_BIT(3)
#घोषणा RK3228_GMAC_FLOW_CTRL_CLR	GRF_CLR_BIT(3)
#घोषणा RK3228_GMAC_SPEED_10M		GRF_CLR_BIT(2)
#घोषणा RK3228_GMAC_SPEED_100M		GRF_BIT(2)
#घोषणा RK3228_GMAC_RMII_CLK_25M	GRF_BIT(7)
#घोषणा RK3228_GMAC_RMII_CLK_2_5M	GRF_CLR_BIT(7)
#घोषणा RK3228_GMAC_CLK_125M		(GRF_CLR_BIT(8) | GRF_CLR_BIT(9))
#घोषणा RK3228_GMAC_CLK_25M		(GRF_BIT(8) | GRF_BIT(9))
#घोषणा RK3228_GMAC_CLK_2_5M		(GRF_CLR_BIT(8) | GRF_BIT(9))
#घोषणा RK3228_GMAC_RMII_MODE		GRF_BIT(10)
#घोषणा RK3228_GMAC_RMII_MODE_CLR	GRF_CLR_BIT(10)
#घोषणा RK3228_GMAC_TXCLK_DLY_ENABLE	GRF_BIT(0)
#घोषणा RK3228_GMAC_TXCLK_DLY_DISABLE	GRF_CLR_BIT(0)
#घोषणा RK3228_GMAC_RXCLK_DLY_ENABLE	GRF_BIT(1)
#घोषणा RK3228_GMAC_RXCLK_DLY_DISABLE	GRF_CLR_BIT(1)

/* RK3228_GRF_COM_MUX */
#घोषणा RK3228_GRF_CON_MUX_GMAC_INTEGRATED_PHY	GRF_BIT(15)

अटल व्योम rk3228_set_to_rgmii(काष्ठा rk_priv_data *bsp_priv,
				पूर्णांक tx_delay, पूर्णांक rx_delay)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "Missing rockchip,grf property\n");
		वापस;
	पूर्ण

	regmap_ग_लिखो(bsp_priv->grf, RK3228_GRF_MAC_CON1,
		     RK3228_GMAC_PHY_INTF_SEL_RGMII |
		     RK3228_GMAC_RMII_MODE_CLR |
		     DELAY_ENABLE(RK3228, tx_delay, rx_delay));

	regmap_ग_लिखो(bsp_priv->grf, RK3228_GRF_MAC_CON0,
		     RK3228_GMAC_CLK_RX_DL_CFG(rx_delay) |
		     RK3228_GMAC_CLK_TX_DL_CFG(tx_delay));
पूर्ण

अटल व्योम rk3228_set_to_rmii(काष्ठा rk_priv_data *bsp_priv)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "Missing rockchip,grf property\n");
		वापस;
	पूर्ण

	regmap_ग_लिखो(bsp_priv->grf, RK3228_GRF_MAC_CON1,
		     RK3228_GMAC_PHY_INTF_SEL_RMII |
		     RK3228_GMAC_RMII_MODE);

	/* set MAC to RMII mode */
	regmap_ग_लिखो(bsp_priv->grf, RK3228_GRF_MAC_CON1, GRF_BIT(11));
पूर्ण

अटल व्योम rk3228_set_rgmii_speed(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "Missing rockchip,grf property\n");
		वापस;
	पूर्ण

	अगर (speed == 10)
		regmap_ग_लिखो(bsp_priv->grf, RK3228_GRF_MAC_CON1,
			     RK3228_GMAC_CLK_2_5M);
	अन्यथा अगर (speed == 100)
		regmap_ग_लिखो(bsp_priv->grf, RK3228_GRF_MAC_CON1,
			     RK3228_GMAC_CLK_25M);
	अन्यथा अगर (speed == 1000)
		regmap_ग_लिखो(bsp_priv->grf, RK3228_GRF_MAC_CON1,
			     RK3228_GMAC_CLK_125M);
	अन्यथा
		dev_err(dev, "unknown speed value for RGMII! speed=%d", speed);
पूर्ण

अटल व्योम rk3228_set_rmii_speed(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "Missing rockchip,grf property\n");
		वापस;
	पूर्ण

	अगर (speed == 10)
		regmap_ग_लिखो(bsp_priv->grf, RK3228_GRF_MAC_CON1,
			     RK3228_GMAC_RMII_CLK_2_5M |
			     RK3228_GMAC_SPEED_10M);
	अन्यथा अगर (speed == 100)
		regmap_ग_लिखो(bsp_priv->grf, RK3228_GRF_MAC_CON1,
			     RK3228_GMAC_RMII_CLK_25M |
			     RK3228_GMAC_SPEED_100M);
	अन्यथा
		dev_err(dev, "unknown speed value for RMII! speed=%d", speed);
पूर्ण

अटल व्योम rk3228_पूर्णांकegrated_phy_घातerup(काष्ठा rk_priv_data *priv)
अणु
	regmap_ग_लिखो(priv->grf, RK3228_GRF_CON_MUX,
		     RK3228_GRF_CON_MUX_GMAC_INTEGRATED_PHY);
पूर्ण

अटल स्थिर काष्ठा rk_gmac_ops rk3228_ops = अणु
	.set_to_rgmii = rk3228_set_to_rgmii,
	.set_to_rmii = rk3228_set_to_rmii,
	.set_rgmii_speed = rk3228_set_rgmii_speed,
	.set_rmii_speed = rk3228_set_rmii_speed,
	.पूर्णांकegrated_phy_घातerup =  rk3228_पूर्णांकegrated_phy_घातerup,
पूर्ण;

#घोषणा RK3288_GRF_SOC_CON1	0x0248
#घोषणा RK3288_GRF_SOC_CON3	0x0250

/*RK3288_GRF_SOC_CON1*/
#घोषणा RK3288_GMAC_PHY_INTF_SEL_RGMII	(GRF_BIT(6) | GRF_CLR_BIT(7) | \
					 GRF_CLR_BIT(8))
#घोषणा RK3288_GMAC_PHY_INTF_SEL_RMII	(GRF_CLR_BIT(6) | GRF_CLR_BIT(7) | \
					 GRF_BIT(8))
#घोषणा RK3288_GMAC_FLOW_CTRL		GRF_BIT(9)
#घोषणा RK3288_GMAC_FLOW_CTRL_CLR	GRF_CLR_BIT(9)
#घोषणा RK3288_GMAC_SPEED_10M		GRF_CLR_BIT(10)
#घोषणा RK3288_GMAC_SPEED_100M		GRF_BIT(10)
#घोषणा RK3288_GMAC_RMII_CLK_25M	GRF_BIT(11)
#घोषणा RK3288_GMAC_RMII_CLK_2_5M	GRF_CLR_BIT(11)
#घोषणा RK3288_GMAC_CLK_125M		(GRF_CLR_BIT(12) | GRF_CLR_BIT(13))
#घोषणा RK3288_GMAC_CLK_25M		(GRF_BIT(12) | GRF_BIT(13))
#घोषणा RK3288_GMAC_CLK_2_5M		(GRF_CLR_BIT(12) | GRF_BIT(13))
#घोषणा RK3288_GMAC_RMII_MODE		GRF_BIT(14)
#घोषणा RK3288_GMAC_RMII_MODE_CLR	GRF_CLR_BIT(14)

/*RK3288_GRF_SOC_CON3*/
#घोषणा RK3288_GMAC_TXCLK_DLY_ENABLE	GRF_BIT(14)
#घोषणा RK3288_GMAC_TXCLK_DLY_DISABLE	GRF_CLR_BIT(14)
#घोषणा RK3288_GMAC_RXCLK_DLY_ENABLE	GRF_BIT(15)
#घोषणा RK3288_GMAC_RXCLK_DLY_DISABLE	GRF_CLR_BIT(15)
#घोषणा RK3288_GMAC_CLK_RX_DL_CFG(val)	HIWORD_UPDATE(val, 0x7F, 7)
#घोषणा RK3288_GMAC_CLK_TX_DL_CFG(val)	HIWORD_UPDATE(val, 0x7F, 0)

अटल व्योम rk3288_set_to_rgmii(काष्ठा rk_priv_data *bsp_priv,
				पूर्णांक tx_delay, पूर्णांक rx_delay)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "Missing rockchip,grf property\n");
		वापस;
	पूर्ण

	regmap_ग_लिखो(bsp_priv->grf, RK3288_GRF_SOC_CON1,
		     RK3288_GMAC_PHY_INTF_SEL_RGMII |
		     RK3288_GMAC_RMII_MODE_CLR);
	regmap_ग_लिखो(bsp_priv->grf, RK3288_GRF_SOC_CON3,
		     DELAY_ENABLE(RK3288, tx_delay, rx_delay) |
		     RK3288_GMAC_CLK_RX_DL_CFG(rx_delay) |
		     RK3288_GMAC_CLK_TX_DL_CFG(tx_delay));
पूर्ण

अटल व्योम rk3288_set_to_rmii(काष्ठा rk_priv_data *bsp_priv)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "Missing rockchip,grf property\n");
		वापस;
	पूर्ण

	regmap_ग_लिखो(bsp_priv->grf, RK3288_GRF_SOC_CON1,
		     RK3288_GMAC_PHY_INTF_SEL_RMII | RK3288_GMAC_RMII_MODE);
पूर्ण

अटल व्योम rk3288_set_rgmii_speed(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "Missing rockchip,grf property\n");
		वापस;
	पूर्ण

	अगर (speed == 10)
		regmap_ग_लिखो(bsp_priv->grf, RK3288_GRF_SOC_CON1,
			     RK3288_GMAC_CLK_2_5M);
	अन्यथा अगर (speed == 100)
		regmap_ग_लिखो(bsp_priv->grf, RK3288_GRF_SOC_CON1,
			     RK3288_GMAC_CLK_25M);
	अन्यथा अगर (speed == 1000)
		regmap_ग_लिखो(bsp_priv->grf, RK3288_GRF_SOC_CON1,
			     RK3288_GMAC_CLK_125M);
	अन्यथा
		dev_err(dev, "unknown speed value for RGMII! speed=%d", speed);
पूर्ण

अटल व्योम rk3288_set_rmii_speed(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "Missing rockchip,grf property\n");
		वापस;
	पूर्ण

	अगर (speed == 10) अणु
		regmap_ग_लिखो(bsp_priv->grf, RK3288_GRF_SOC_CON1,
			     RK3288_GMAC_RMII_CLK_2_5M |
			     RK3288_GMAC_SPEED_10M);
	पूर्ण अन्यथा अगर (speed == 100) अणु
		regmap_ग_लिखो(bsp_priv->grf, RK3288_GRF_SOC_CON1,
			     RK3288_GMAC_RMII_CLK_25M |
			     RK3288_GMAC_SPEED_100M);
	पूर्ण अन्यथा अणु
		dev_err(dev, "unknown speed value for RMII! speed=%d", speed);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rk_gmac_ops rk3288_ops = अणु
	.set_to_rgmii = rk3288_set_to_rgmii,
	.set_to_rmii = rk3288_set_to_rmii,
	.set_rgmii_speed = rk3288_set_rgmii_speed,
	.set_rmii_speed = rk3288_set_rmii_speed,
पूर्ण;

#घोषणा RK3328_GRF_MAC_CON0	0x0900
#घोषणा RK3328_GRF_MAC_CON1	0x0904
#घोषणा RK3328_GRF_MAC_CON2	0x0908
#घोषणा RK3328_GRF_MACPHY_CON1	0xb04

/* RK3328_GRF_MAC_CON0 */
#घोषणा RK3328_GMAC_CLK_RX_DL_CFG(val)	HIWORD_UPDATE(val, 0x7F, 7)
#घोषणा RK3328_GMAC_CLK_TX_DL_CFG(val)	HIWORD_UPDATE(val, 0x7F, 0)

/* RK3328_GRF_MAC_CON1 */
#घोषणा RK3328_GMAC_PHY_INTF_SEL_RGMII	\
		(GRF_BIT(4) | GRF_CLR_BIT(5) | GRF_CLR_BIT(6))
#घोषणा RK3328_GMAC_PHY_INTF_SEL_RMII	\
		(GRF_CLR_BIT(4) | GRF_CLR_BIT(5) | GRF_BIT(6))
#घोषणा RK3328_GMAC_FLOW_CTRL		GRF_BIT(3)
#घोषणा RK3328_GMAC_FLOW_CTRL_CLR	GRF_CLR_BIT(3)
#घोषणा RK3328_GMAC_SPEED_10M		GRF_CLR_BIT(2)
#घोषणा RK3328_GMAC_SPEED_100M		GRF_BIT(2)
#घोषणा RK3328_GMAC_RMII_CLK_25M	GRF_BIT(7)
#घोषणा RK3328_GMAC_RMII_CLK_2_5M	GRF_CLR_BIT(7)
#घोषणा RK3328_GMAC_CLK_125M		(GRF_CLR_BIT(11) | GRF_CLR_BIT(12))
#घोषणा RK3328_GMAC_CLK_25M		(GRF_BIT(11) | GRF_BIT(12))
#घोषणा RK3328_GMAC_CLK_2_5M		(GRF_CLR_BIT(11) | GRF_BIT(12))
#घोषणा RK3328_GMAC_RMII_MODE		GRF_BIT(9)
#घोषणा RK3328_GMAC_RMII_MODE_CLR	GRF_CLR_BIT(9)
#घोषणा RK3328_GMAC_TXCLK_DLY_ENABLE	GRF_BIT(0)
#घोषणा RK3328_GMAC_TXCLK_DLY_DISABLE	GRF_CLR_BIT(0)
#घोषणा RK3328_GMAC_RXCLK_DLY_ENABLE	GRF_BIT(1)
#घोषणा RK3328_GMAC_RXCLK_DLY_DISABLE	GRF_CLR_BIT(0)

/* RK3328_GRF_MACPHY_CON1 */
#घोषणा RK3328_MACPHY_RMII_MODE		GRF_BIT(9)

अटल व्योम rk3328_set_to_rgmii(काष्ठा rk_priv_data *bsp_priv,
				पूर्णांक tx_delay, पूर्णांक rx_delay)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "Missing rockchip,grf property\n");
		वापस;
	पूर्ण

	regmap_ग_लिखो(bsp_priv->grf, RK3328_GRF_MAC_CON1,
		     RK3328_GMAC_PHY_INTF_SEL_RGMII |
		     RK3328_GMAC_RMII_MODE_CLR |
		     RK3328_GMAC_RXCLK_DLY_ENABLE |
		     RK3328_GMAC_TXCLK_DLY_ENABLE);

	regmap_ग_लिखो(bsp_priv->grf, RK3328_GRF_MAC_CON0,
		     RK3328_GMAC_CLK_RX_DL_CFG(rx_delay) |
		     RK3328_GMAC_CLK_TX_DL_CFG(tx_delay));
पूर्ण

अटल व्योम rk3328_set_to_rmii(काष्ठा rk_priv_data *bsp_priv)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;
	अचिन्हित पूर्णांक reg;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "Missing rockchip,grf property\n");
		वापस;
	पूर्ण

	reg = bsp_priv->पूर्णांकegrated_phy ? RK3328_GRF_MAC_CON2 :
		  RK3328_GRF_MAC_CON1;

	regmap_ग_लिखो(bsp_priv->grf, reg,
		     RK3328_GMAC_PHY_INTF_SEL_RMII |
		     RK3328_GMAC_RMII_MODE);
पूर्ण

अटल व्योम rk3328_set_rgmii_speed(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "Missing rockchip,grf property\n");
		वापस;
	पूर्ण

	अगर (speed == 10)
		regmap_ग_लिखो(bsp_priv->grf, RK3328_GRF_MAC_CON1,
			     RK3328_GMAC_CLK_2_5M);
	अन्यथा अगर (speed == 100)
		regmap_ग_लिखो(bsp_priv->grf, RK3328_GRF_MAC_CON1,
			     RK3328_GMAC_CLK_25M);
	अन्यथा अगर (speed == 1000)
		regmap_ग_लिखो(bsp_priv->grf, RK3328_GRF_MAC_CON1,
			     RK3328_GMAC_CLK_125M);
	अन्यथा
		dev_err(dev, "unknown speed value for RGMII! speed=%d", speed);
पूर्ण

अटल व्योम rk3328_set_rmii_speed(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;
	अचिन्हित पूर्णांक reg;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "Missing rockchip,grf property\n");
		वापस;
	पूर्ण

	reg = bsp_priv->पूर्णांकegrated_phy ? RK3328_GRF_MAC_CON2 :
		  RK3328_GRF_MAC_CON1;

	अगर (speed == 10)
		regmap_ग_लिखो(bsp_priv->grf, reg,
			     RK3328_GMAC_RMII_CLK_2_5M |
			     RK3328_GMAC_SPEED_10M);
	अन्यथा अगर (speed == 100)
		regmap_ग_लिखो(bsp_priv->grf, reg,
			     RK3328_GMAC_RMII_CLK_25M |
			     RK3328_GMAC_SPEED_100M);
	अन्यथा
		dev_err(dev, "unknown speed value for RMII! speed=%d", speed);
पूर्ण

अटल व्योम rk3328_पूर्णांकegrated_phy_घातerup(काष्ठा rk_priv_data *priv)
अणु
	regmap_ग_लिखो(priv->grf, RK3328_GRF_MACPHY_CON1,
		     RK3328_MACPHY_RMII_MODE);
पूर्ण

अटल स्थिर काष्ठा rk_gmac_ops rk3328_ops = अणु
	.set_to_rgmii = rk3328_set_to_rgmii,
	.set_to_rmii = rk3328_set_to_rmii,
	.set_rgmii_speed = rk3328_set_rgmii_speed,
	.set_rmii_speed = rk3328_set_rmii_speed,
	.पूर्णांकegrated_phy_घातerup =  rk3328_पूर्णांकegrated_phy_घातerup,
पूर्ण;

#घोषणा RK3366_GRF_SOC_CON6	0x0418
#घोषणा RK3366_GRF_SOC_CON7	0x041c

/* RK3366_GRF_SOC_CON6 */
#घोषणा RK3366_GMAC_PHY_INTF_SEL_RGMII	(GRF_BIT(9) | GRF_CLR_BIT(10) | \
					 GRF_CLR_BIT(11))
#घोषणा RK3366_GMAC_PHY_INTF_SEL_RMII	(GRF_CLR_BIT(9) | GRF_CLR_BIT(10) | \
					 GRF_BIT(11))
#घोषणा RK3366_GMAC_FLOW_CTRL		GRF_BIT(8)
#घोषणा RK3366_GMAC_FLOW_CTRL_CLR	GRF_CLR_BIT(8)
#घोषणा RK3366_GMAC_SPEED_10M		GRF_CLR_BIT(7)
#घोषणा RK3366_GMAC_SPEED_100M		GRF_BIT(7)
#घोषणा RK3366_GMAC_RMII_CLK_25M	GRF_BIT(3)
#घोषणा RK3366_GMAC_RMII_CLK_2_5M	GRF_CLR_BIT(3)
#घोषणा RK3366_GMAC_CLK_125M		(GRF_CLR_BIT(4) | GRF_CLR_BIT(5))
#घोषणा RK3366_GMAC_CLK_25M		(GRF_BIT(4) | GRF_BIT(5))
#घोषणा RK3366_GMAC_CLK_2_5M		(GRF_CLR_BIT(4) | GRF_BIT(5))
#घोषणा RK3366_GMAC_RMII_MODE		GRF_BIT(6)
#घोषणा RK3366_GMAC_RMII_MODE_CLR	GRF_CLR_BIT(6)

/* RK3366_GRF_SOC_CON7 */
#घोषणा RK3366_GMAC_TXCLK_DLY_ENABLE	GRF_BIT(7)
#घोषणा RK3366_GMAC_TXCLK_DLY_DISABLE	GRF_CLR_BIT(7)
#घोषणा RK3366_GMAC_RXCLK_DLY_ENABLE	GRF_BIT(15)
#घोषणा RK3366_GMAC_RXCLK_DLY_DISABLE	GRF_CLR_BIT(15)
#घोषणा RK3366_GMAC_CLK_RX_DL_CFG(val)	HIWORD_UPDATE(val, 0x7F, 8)
#घोषणा RK3366_GMAC_CLK_TX_DL_CFG(val)	HIWORD_UPDATE(val, 0x7F, 0)

अटल व्योम rk3366_set_to_rgmii(काष्ठा rk_priv_data *bsp_priv,
				पूर्णांक tx_delay, पूर्णांक rx_delay)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "%s: Missing rockchip,grf property\n", __func__);
		वापस;
	पूर्ण

	regmap_ग_लिखो(bsp_priv->grf, RK3366_GRF_SOC_CON6,
		     RK3366_GMAC_PHY_INTF_SEL_RGMII |
		     RK3366_GMAC_RMII_MODE_CLR);
	regmap_ग_लिखो(bsp_priv->grf, RK3366_GRF_SOC_CON7,
		     DELAY_ENABLE(RK3366, tx_delay, rx_delay) |
		     RK3366_GMAC_CLK_RX_DL_CFG(rx_delay) |
		     RK3366_GMAC_CLK_TX_DL_CFG(tx_delay));
पूर्ण

अटल व्योम rk3366_set_to_rmii(काष्ठा rk_priv_data *bsp_priv)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "%s: Missing rockchip,grf property\n", __func__);
		वापस;
	पूर्ण

	regmap_ग_लिखो(bsp_priv->grf, RK3366_GRF_SOC_CON6,
		     RK3366_GMAC_PHY_INTF_SEL_RMII | RK3366_GMAC_RMII_MODE);
पूर्ण

अटल व्योम rk3366_set_rgmii_speed(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "%s: Missing rockchip,grf property\n", __func__);
		वापस;
	पूर्ण

	अगर (speed == 10)
		regmap_ग_लिखो(bsp_priv->grf, RK3366_GRF_SOC_CON6,
			     RK3366_GMAC_CLK_2_5M);
	अन्यथा अगर (speed == 100)
		regmap_ग_लिखो(bsp_priv->grf, RK3366_GRF_SOC_CON6,
			     RK3366_GMAC_CLK_25M);
	अन्यथा अगर (speed == 1000)
		regmap_ग_लिखो(bsp_priv->grf, RK3366_GRF_SOC_CON6,
			     RK3366_GMAC_CLK_125M);
	अन्यथा
		dev_err(dev, "unknown speed value for RGMII! speed=%d", speed);
पूर्ण

अटल व्योम rk3366_set_rmii_speed(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "%s: Missing rockchip,grf property\n", __func__);
		वापस;
	पूर्ण

	अगर (speed == 10) अणु
		regmap_ग_लिखो(bsp_priv->grf, RK3366_GRF_SOC_CON6,
			     RK3366_GMAC_RMII_CLK_2_5M |
			     RK3366_GMAC_SPEED_10M);
	पूर्ण अन्यथा अगर (speed == 100) अणु
		regmap_ग_लिखो(bsp_priv->grf, RK3366_GRF_SOC_CON6,
			     RK3366_GMAC_RMII_CLK_25M |
			     RK3366_GMAC_SPEED_100M);
	पूर्ण अन्यथा अणु
		dev_err(dev, "unknown speed value for RMII! speed=%d", speed);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rk_gmac_ops rk3366_ops = अणु
	.set_to_rgmii = rk3366_set_to_rgmii,
	.set_to_rmii = rk3366_set_to_rmii,
	.set_rgmii_speed = rk3366_set_rgmii_speed,
	.set_rmii_speed = rk3366_set_rmii_speed,
पूर्ण;

#घोषणा RK3368_GRF_SOC_CON15	0x043c
#घोषणा RK3368_GRF_SOC_CON16	0x0440

/* RK3368_GRF_SOC_CON15 */
#घोषणा RK3368_GMAC_PHY_INTF_SEL_RGMII	(GRF_BIT(9) | GRF_CLR_BIT(10) | \
					 GRF_CLR_BIT(11))
#घोषणा RK3368_GMAC_PHY_INTF_SEL_RMII	(GRF_CLR_BIT(9) | GRF_CLR_BIT(10) | \
					 GRF_BIT(11))
#घोषणा RK3368_GMAC_FLOW_CTRL		GRF_BIT(8)
#घोषणा RK3368_GMAC_FLOW_CTRL_CLR	GRF_CLR_BIT(8)
#घोषणा RK3368_GMAC_SPEED_10M		GRF_CLR_BIT(7)
#घोषणा RK3368_GMAC_SPEED_100M		GRF_BIT(7)
#घोषणा RK3368_GMAC_RMII_CLK_25M	GRF_BIT(3)
#घोषणा RK3368_GMAC_RMII_CLK_2_5M	GRF_CLR_BIT(3)
#घोषणा RK3368_GMAC_CLK_125M		(GRF_CLR_BIT(4) | GRF_CLR_BIT(5))
#घोषणा RK3368_GMAC_CLK_25M		(GRF_BIT(4) | GRF_BIT(5))
#घोषणा RK3368_GMAC_CLK_2_5M		(GRF_CLR_BIT(4) | GRF_BIT(5))
#घोषणा RK3368_GMAC_RMII_MODE		GRF_BIT(6)
#घोषणा RK3368_GMAC_RMII_MODE_CLR	GRF_CLR_BIT(6)

/* RK3368_GRF_SOC_CON16 */
#घोषणा RK3368_GMAC_TXCLK_DLY_ENABLE	GRF_BIT(7)
#घोषणा RK3368_GMAC_TXCLK_DLY_DISABLE	GRF_CLR_BIT(7)
#घोषणा RK3368_GMAC_RXCLK_DLY_ENABLE	GRF_BIT(15)
#घोषणा RK3368_GMAC_RXCLK_DLY_DISABLE	GRF_CLR_BIT(15)
#घोषणा RK3368_GMAC_CLK_RX_DL_CFG(val)	HIWORD_UPDATE(val, 0x7F, 8)
#घोषणा RK3368_GMAC_CLK_TX_DL_CFG(val)	HIWORD_UPDATE(val, 0x7F, 0)

अटल व्योम rk3368_set_to_rgmii(काष्ठा rk_priv_data *bsp_priv,
				पूर्णांक tx_delay, पूर्णांक rx_delay)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "%s: Missing rockchip,grf property\n", __func__);
		वापस;
	पूर्ण

	regmap_ग_लिखो(bsp_priv->grf, RK3368_GRF_SOC_CON15,
		     RK3368_GMAC_PHY_INTF_SEL_RGMII |
		     RK3368_GMAC_RMII_MODE_CLR);
	regmap_ग_लिखो(bsp_priv->grf, RK3368_GRF_SOC_CON16,
		     DELAY_ENABLE(RK3368, tx_delay, rx_delay) |
		     RK3368_GMAC_CLK_RX_DL_CFG(rx_delay) |
		     RK3368_GMAC_CLK_TX_DL_CFG(tx_delay));
पूर्ण

अटल व्योम rk3368_set_to_rmii(काष्ठा rk_priv_data *bsp_priv)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "%s: Missing rockchip,grf property\n", __func__);
		वापस;
	पूर्ण

	regmap_ग_लिखो(bsp_priv->grf, RK3368_GRF_SOC_CON15,
		     RK3368_GMAC_PHY_INTF_SEL_RMII | RK3368_GMAC_RMII_MODE);
पूर्ण

अटल व्योम rk3368_set_rgmii_speed(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "%s: Missing rockchip,grf property\n", __func__);
		वापस;
	पूर्ण

	अगर (speed == 10)
		regmap_ग_लिखो(bsp_priv->grf, RK3368_GRF_SOC_CON15,
			     RK3368_GMAC_CLK_2_5M);
	अन्यथा अगर (speed == 100)
		regmap_ग_लिखो(bsp_priv->grf, RK3368_GRF_SOC_CON15,
			     RK3368_GMAC_CLK_25M);
	अन्यथा अगर (speed == 1000)
		regmap_ग_लिखो(bsp_priv->grf, RK3368_GRF_SOC_CON15,
			     RK3368_GMAC_CLK_125M);
	अन्यथा
		dev_err(dev, "unknown speed value for RGMII! speed=%d", speed);
पूर्ण

अटल व्योम rk3368_set_rmii_speed(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "%s: Missing rockchip,grf property\n", __func__);
		वापस;
	पूर्ण

	अगर (speed == 10) अणु
		regmap_ग_लिखो(bsp_priv->grf, RK3368_GRF_SOC_CON15,
			     RK3368_GMAC_RMII_CLK_2_5M |
			     RK3368_GMAC_SPEED_10M);
	पूर्ण अन्यथा अगर (speed == 100) अणु
		regmap_ग_लिखो(bsp_priv->grf, RK3368_GRF_SOC_CON15,
			     RK3368_GMAC_RMII_CLK_25M |
			     RK3368_GMAC_SPEED_100M);
	पूर्ण अन्यथा अणु
		dev_err(dev, "unknown speed value for RMII! speed=%d", speed);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rk_gmac_ops rk3368_ops = अणु
	.set_to_rgmii = rk3368_set_to_rgmii,
	.set_to_rmii = rk3368_set_to_rmii,
	.set_rgmii_speed = rk3368_set_rgmii_speed,
	.set_rmii_speed = rk3368_set_rmii_speed,
पूर्ण;

#घोषणा RK3399_GRF_SOC_CON5	0xc214
#घोषणा RK3399_GRF_SOC_CON6	0xc218

/* RK3399_GRF_SOC_CON5 */
#घोषणा RK3399_GMAC_PHY_INTF_SEL_RGMII	(GRF_BIT(9) | GRF_CLR_BIT(10) | \
					 GRF_CLR_BIT(11))
#घोषणा RK3399_GMAC_PHY_INTF_SEL_RMII	(GRF_CLR_BIT(9) | GRF_CLR_BIT(10) | \
					 GRF_BIT(11))
#घोषणा RK3399_GMAC_FLOW_CTRL		GRF_BIT(8)
#घोषणा RK3399_GMAC_FLOW_CTRL_CLR	GRF_CLR_BIT(8)
#घोषणा RK3399_GMAC_SPEED_10M		GRF_CLR_BIT(7)
#घोषणा RK3399_GMAC_SPEED_100M		GRF_BIT(7)
#घोषणा RK3399_GMAC_RMII_CLK_25M	GRF_BIT(3)
#घोषणा RK3399_GMAC_RMII_CLK_2_5M	GRF_CLR_BIT(3)
#घोषणा RK3399_GMAC_CLK_125M		(GRF_CLR_BIT(4) | GRF_CLR_BIT(5))
#घोषणा RK3399_GMAC_CLK_25M		(GRF_BIT(4) | GRF_BIT(5))
#घोषणा RK3399_GMAC_CLK_2_5M		(GRF_CLR_BIT(4) | GRF_BIT(5))
#घोषणा RK3399_GMAC_RMII_MODE		GRF_BIT(6)
#घोषणा RK3399_GMAC_RMII_MODE_CLR	GRF_CLR_BIT(6)

/* RK3399_GRF_SOC_CON6 */
#घोषणा RK3399_GMAC_TXCLK_DLY_ENABLE	GRF_BIT(7)
#घोषणा RK3399_GMAC_TXCLK_DLY_DISABLE	GRF_CLR_BIT(7)
#घोषणा RK3399_GMAC_RXCLK_DLY_ENABLE	GRF_BIT(15)
#घोषणा RK3399_GMAC_RXCLK_DLY_DISABLE	GRF_CLR_BIT(15)
#घोषणा RK3399_GMAC_CLK_RX_DL_CFG(val)	HIWORD_UPDATE(val, 0x7F, 8)
#घोषणा RK3399_GMAC_CLK_TX_DL_CFG(val)	HIWORD_UPDATE(val, 0x7F, 0)

अटल व्योम rk3399_set_to_rgmii(काष्ठा rk_priv_data *bsp_priv,
				पूर्णांक tx_delay, पूर्णांक rx_delay)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "%s: Missing rockchip,grf property\n", __func__);
		वापस;
	पूर्ण

	regmap_ग_लिखो(bsp_priv->grf, RK3399_GRF_SOC_CON5,
		     RK3399_GMAC_PHY_INTF_SEL_RGMII |
		     RK3399_GMAC_RMII_MODE_CLR);
	regmap_ग_लिखो(bsp_priv->grf, RK3399_GRF_SOC_CON6,
		     DELAY_ENABLE(RK3399, tx_delay, rx_delay) |
		     RK3399_GMAC_CLK_RX_DL_CFG(rx_delay) |
		     RK3399_GMAC_CLK_TX_DL_CFG(tx_delay));
पूर्ण

अटल व्योम rk3399_set_to_rmii(काष्ठा rk_priv_data *bsp_priv)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "%s: Missing rockchip,grf property\n", __func__);
		वापस;
	पूर्ण

	regmap_ग_लिखो(bsp_priv->grf, RK3399_GRF_SOC_CON5,
		     RK3399_GMAC_PHY_INTF_SEL_RMII | RK3399_GMAC_RMII_MODE);
पूर्ण

अटल व्योम rk3399_set_rgmii_speed(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "%s: Missing rockchip,grf property\n", __func__);
		वापस;
	पूर्ण

	अगर (speed == 10)
		regmap_ग_लिखो(bsp_priv->grf, RK3399_GRF_SOC_CON5,
			     RK3399_GMAC_CLK_2_5M);
	अन्यथा अगर (speed == 100)
		regmap_ग_लिखो(bsp_priv->grf, RK3399_GRF_SOC_CON5,
			     RK3399_GMAC_CLK_25M);
	अन्यथा अगर (speed == 1000)
		regmap_ग_लिखो(bsp_priv->grf, RK3399_GRF_SOC_CON5,
			     RK3399_GMAC_CLK_125M);
	अन्यथा
		dev_err(dev, "unknown speed value for RGMII! speed=%d", speed);
पूर्ण

अटल व्योम rk3399_set_rmii_speed(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "%s: Missing rockchip,grf property\n", __func__);
		वापस;
	पूर्ण

	अगर (speed == 10) अणु
		regmap_ग_लिखो(bsp_priv->grf, RK3399_GRF_SOC_CON5,
			     RK3399_GMAC_RMII_CLK_2_5M |
			     RK3399_GMAC_SPEED_10M);
	पूर्ण अन्यथा अगर (speed == 100) अणु
		regmap_ग_लिखो(bsp_priv->grf, RK3399_GRF_SOC_CON5,
			     RK3399_GMAC_RMII_CLK_25M |
			     RK3399_GMAC_SPEED_100M);
	पूर्ण अन्यथा अणु
		dev_err(dev, "unknown speed value for RMII! speed=%d", speed);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rk_gmac_ops rk3399_ops = अणु
	.set_to_rgmii = rk3399_set_to_rgmii,
	.set_to_rmii = rk3399_set_to_rmii,
	.set_rgmii_speed = rk3399_set_rgmii_speed,
	.set_rmii_speed = rk3399_set_rmii_speed,
पूर्ण;

#घोषणा RV1108_GRF_GMAC_CON0		0X0900

/* RV1108_GRF_GMAC_CON0 */
#घोषणा RV1108_GMAC_PHY_INTF_SEL_RMII	(GRF_CLR_BIT(4) | GRF_CLR_BIT(5) | \
					GRF_BIT(6))
#घोषणा RV1108_GMAC_FLOW_CTRL		GRF_BIT(3)
#घोषणा RV1108_GMAC_FLOW_CTRL_CLR	GRF_CLR_BIT(3)
#घोषणा RV1108_GMAC_SPEED_10M		GRF_CLR_BIT(2)
#घोषणा RV1108_GMAC_SPEED_100M		GRF_BIT(2)
#घोषणा RV1108_GMAC_RMII_CLK_25M	GRF_BIT(7)
#घोषणा RV1108_GMAC_RMII_CLK_2_5M	GRF_CLR_BIT(7)

अटल व्योम rv1108_set_to_rmii(काष्ठा rk_priv_data *bsp_priv)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "%s: Missing rockchip,grf property\n", __func__);
		वापस;
	पूर्ण

	regmap_ग_लिखो(bsp_priv->grf, RV1108_GRF_GMAC_CON0,
		     RV1108_GMAC_PHY_INTF_SEL_RMII);
पूर्ण

अटल व्योम rv1108_set_rmii_speed(काष्ठा rk_priv_data *bsp_priv, पूर्णांक speed)
अणु
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (IS_ERR(bsp_priv->grf)) अणु
		dev_err(dev, "%s: Missing rockchip,grf property\n", __func__);
		वापस;
	पूर्ण

	अगर (speed == 10) अणु
		regmap_ग_लिखो(bsp_priv->grf, RV1108_GRF_GMAC_CON0,
			     RV1108_GMAC_RMII_CLK_2_5M |
			     RV1108_GMAC_SPEED_10M);
	पूर्ण अन्यथा अगर (speed == 100) अणु
		regmap_ग_लिखो(bsp_priv->grf, RV1108_GRF_GMAC_CON0,
			     RV1108_GMAC_RMII_CLK_25M |
			     RV1108_GMAC_SPEED_100M);
	पूर्ण अन्यथा अणु
		dev_err(dev, "unknown speed value for RMII! speed=%d", speed);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rk_gmac_ops rv1108_ops = अणु
	.set_to_rmii = rv1108_set_to_rmii,
	.set_rmii_speed = rv1108_set_rmii_speed,
पूर्ण;

#घोषणा RK_GRF_MACPHY_CON0		0xb00
#घोषणा RK_GRF_MACPHY_CON1		0xb04
#घोषणा RK_GRF_MACPHY_CON2		0xb08
#घोषणा RK_GRF_MACPHY_CON3		0xb0c

#घोषणा RK_MACPHY_ENABLE		GRF_BIT(0)
#घोषणा RK_MACPHY_DISABLE		GRF_CLR_BIT(0)
#घोषणा RK_MACPHY_CFG_CLK_50M		GRF_BIT(14)
#घोषणा RK_GMAC2PHY_RMII_MODE		(GRF_BIT(6) | GRF_CLR_BIT(7))
#घोषणा RK_GRF_CON2_MACPHY_ID		HIWORD_UPDATE(0x1234, 0xffff, 0)
#घोषणा RK_GRF_CON3_MACPHY_ID		HIWORD_UPDATE(0x35, 0x3f, 0)

अटल व्योम rk_gmac_पूर्णांकegrated_phy_घातerup(काष्ठा rk_priv_data *priv)
अणु
	अगर (priv->ops->पूर्णांकegrated_phy_घातerup)
		priv->ops->पूर्णांकegrated_phy_घातerup(priv);

	regmap_ग_लिखो(priv->grf, RK_GRF_MACPHY_CON0, RK_MACPHY_CFG_CLK_50M);
	regmap_ग_लिखो(priv->grf, RK_GRF_MACPHY_CON0, RK_GMAC2PHY_RMII_MODE);

	regmap_ग_लिखो(priv->grf, RK_GRF_MACPHY_CON2, RK_GRF_CON2_MACPHY_ID);
	regmap_ग_लिखो(priv->grf, RK_GRF_MACPHY_CON3, RK_GRF_CON3_MACPHY_ID);

	अगर (priv->phy_reset) अणु
		/* PHY needs to be disabled beक्रमe trying to reset it */
		regmap_ग_लिखो(priv->grf, RK_GRF_MACPHY_CON0, RK_MACPHY_DISABLE);
		अगर (priv->phy_reset)
			reset_control_निश्चित(priv->phy_reset);
		usleep_range(10, 20);
		अगर (priv->phy_reset)
			reset_control_deनिश्चित(priv->phy_reset);
		usleep_range(10, 20);
		regmap_ग_लिखो(priv->grf, RK_GRF_MACPHY_CON0, RK_MACPHY_ENABLE);
		msleep(30);
	पूर्ण
पूर्ण

अटल व्योम rk_gmac_पूर्णांकegrated_phy_घातerकरोwn(काष्ठा rk_priv_data *priv)
अणु
	regmap_ग_लिखो(priv->grf, RK_GRF_MACPHY_CON0, RK_MACPHY_DISABLE);
	अगर (priv->phy_reset)
		reset_control_निश्चित(priv->phy_reset);
पूर्ण

अटल पूर्णांक rk_gmac_clk_init(काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	काष्ठा rk_priv_data *bsp_priv = plat->bsp_priv;
	काष्ठा device *dev = &bsp_priv->pdev->dev;
	पूर्णांक ret;

	bsp_priv->clk_enabled = false;

	bsp_priv->mac_clk_rx = devm_clk_get(dev, "mac_clk_rx");
	अगर (IS_ERR(bsp_priv->mac_clk_rx))
		dev_err(dev, "cannot get clock %s\n",
			"mac_clk_rx");

	bsp_priv->mac_clk_tx = devm_clk_get(dev, "mac_clk_tx");
	अगर (IS_ERR(bsp_priv->mac_clk_tx))
		dev_err(dev, "cannot get clock %s\n",
			"mac_clk_tx");

	bsp_priv->aclk_mac = devm_clk_get(dev, "aclk_mac");
	अगर (IS_ERR(bsp_priv->aclk_mac))
		dev_err(dev, "cannot get clock %s\n",
			"aclk_mac");

	bsp_priv->pclk_mac = devm_clk_get(dev, "pclk_mac");
	अगर (IS_ERR(bsp_priv->pclk_mac))
		dev_err(dev, "cannot get clock %s\n",
			"pclk_mac");

	bsp_priv->clk_mac = devm_clk_get(dev, "stmmaceth");
	अगर (IS_ERR(bsp_priv->clk_mac))
		dev_err(dev, "cannot get clock %s\n",
			"stmmaceth");

	अगर (bsp_priv->phy_अगरace == PHY_INTERFACE_MODE_RMII) अणु
		bsp_priv->clk_mac_ref = devm_clk_get(dev, "clk_mac_ref");
		अगर (IS_ERR(bsp_priv->clk_mac_ref))
			dev_err(dev, "cannot get clock %s\n",
				"clk_mac_ref");

		अगर (!bsp_priv->घड़ी_input) अणु
			bsp_priv->clk_mac_refout =
				devm_clk_get(dev, "clk_mac_refout");
			अगर (IS_ERR(bsp_priv->clk_mac_refout))
				dev_err(dev, "cannot get clock %s\n",
					"clk_mac_refout");
		पूर्ण
	पूर्ण

	bsp_priv->clk_mac_speed = devm_clk_get(dev, "clk_mac_speed");
	अगर (IS_ERR(bsp_priv->clk_mac_speed))
		dev_err(dev, "cannot get clock %s\n", "clk_mac_speed");

	अगर (bsp_priv->घड़ी_input) अणु
		dev_info(dev, "clock input from PHY\n");
	पूर्ण अन्यथा अणु
		अगर (bsp_priv->phy_अगरace == PHY_INTERFACE_MODE_RMII)
			clk_set_rate(bsp_priv->clk_mac, 50000000);
	पूर्ण

	अगर (plat->phy_node && bsp_priv->पूर्णांकegrated_phy) अणु
		bsp_priv->clk_phy = of_clk_get(plat->phy_node, 0);
		अगर (IS_ERR(bsp_priv->clk_phy)) अणु
			ret = PTR_ERR(bsp_priv->clk_phy);
			dev_err(dev, "Cannot get PHY clock: %d\n", ret);
			वापस -EINVAL;
		पूर्ण
		clk_set_rate(bsp_priv->clk_phy, 50000000);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gmac_clk_enable(काष्ठा rk_priv_data *bsp_priv, bool enable)
अणु
	पूर्णांक phy_अगरace = bsp_priv->phy_अगरace;

	अगर (enable) अणु
		अगर (!bsp_priv->clk_enabled) अणु
			अगर (phy_अगरace == PHY_INTERFACE_MODE_RMII) अणु
				अगर (!IS_ERR(bsp_priv->mac_clk_rx))
					clk_prepare_enable(
						bsp_priv->mac_clk_rx);

				अगर (!IS_ERR(bsp_priv->clk_mac_ref))
					clk_prepare_enable(
						bsp_priv->clk_mac_ref);

				अगर (!IS_ERR(bsp_priv->clk_mac_refout))
					clk_prepare_enable(
						bsp_priv->clk_mac_refout);
			पूर्ण

			अगर (!IS_ERR(bsp_priv->clk_phy))
				clk_prepare_enable(bsp_priv->clk_phy);

			अगर (!IS_ERR(bsp_priv->aclk_mac))
				clk_prepare_enable(bsp_priv->aclk_mac);

			अगर (!IS_ERR(bsp_priv->pclk_mac))
				clk_prepare_enable(bsp_priv->pclk_mac);

			अगर (!IS_ERR(bsp_priv->mac_clk_tx))
				clk_prepare_enable(bsp_priv->mac_clk_tx);

			अगर (!IS_ERR(bsp_priv->clk_mac_speed))
				clk_prepare_enable(bsp_priv->clk_mac_speed);

			/**
			 * अगर (!IS_ERR(bsp_priv->clk_mac))
			 *	clk_prepare_enable(bsp_priv->clk_mac);
			 */
			mdelay(5);
			bsp_priv->clk_enabled = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (bsp_priv->clk_enabled) अणु
			अगर (phy_अगरace == PHY_INTERFACE_MODE_RMII) अणु
				clk_disable_unprepare(bsp_priv->mac_clk_rx);

				clk_disable_unprepare(bsp_priv->clk_mac_ref);

				clk_disable_unprepare(bsp_priv->clk_mac_refout);
			पूर्ण

			clk_disable_unprepare(bsp_priv->clk_phy);

			clk_disable_unprepare(bsp_priv->aclk_mac);

			clk_disable_unprepare(bsp_priv->pclk_mac);

			clk_disable_unprepare(bsp_priv->mac_clk_tx);

			clk_disable_unprepare(bsp_priv->clk_mac_speed);
			/**
			 * अगर (!IS_ERR(bsp_priv->clk_mac))
			 *	clk_disable_unprepare(bsp_priv->clk_mac);
			 */
			bsp_priv->clk_enabled = false;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक phy_घातer_on(काष्ठा rk_priv_data *bsp_priv, bool enable)
अणु
	काष्ठा regulator *lकरो = bsp_priv->regulator;
	पूर्णांक ret;
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	अगर (!lकरो)
		वापस 0;

	अगर (enable) अणु
		ret = regulator_enable(lकरो);
		अगर (ret)
			dev_err(dev, "fail to enable phy-supply\n");
	पूर्ण अन्यथा अणु
		ret = regulator_disable(lकरो);
		अगर (ret)
			dev_err(dev, "fail to disable phy-supply\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा rk_priv_data *rk_gmac_setup(काष्ठा platक्रमm_device *pdev,
					  काष्ठा plat_sपंचांगmacenet_data *plat,
					  स्थिर काष्ठा rk_gmac_ops *ops)
अणु
	काष्ठा rk_priv_data *bsp_priv;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;
	स्थिर अक्षर *strings = शून्य;
	पूर्णांक value;

	bsp_priv = devm_kzalloc(dev, माप(*bsp_priv), GFP_KERNEL);
	अगर (!bsp_priv)
		वापस ERR_PTR(-ENOMEM);

	of_get_phy_mode(dev->of_node, &bsp_priv->phy_अगरace);
	bsp_priv->ops = ops;

	bsp_priv->regulator = devm_regulator_get_optional(dev, "phy");
	अगर (IS_ERR(bsp_priv->regulator)) अणु
		अगर (PTR_ERR(bsp_priv->regulator) == -EPROBE_DEFER) अणु
			dev_err(dev, "phy regulator is not available yet, deferred probing\n");
			वापस ERR_PTR(-EPROBE_DEFER);
		पूर्ण
		dev_err(dev, "no regulator found\n");
		bsp_priv->regulator = शून्य;
	पूर्ण

	ret = of_property_पढ़ो_string(dev->of_node, "clock_in_out", &strings);
	अगर (ret) अणु
		dev_err(dev, "Can not read property: clock_in_out.\n");
		bsp_priv->घड़ी_input = true;
	पूर्ण अन्यथा अणु
		dev_info(dev, "clock input or output? (%s).\n",
			 strings);
		अगर (!म_भेद(strings, "input"))
			bsp_priv->घड़ी_input = true;
		अन्यथा
			bsp_priv->घड़ी_input = false;
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "tx_delay", &value);
	अगर (ret) अणु
		bsp_priv->tx_delay = 0x30;
		dev_err(dev, "Can not read property: tx_delay.");
		dev_err(dev, "set tx_delay to 0x%x\n",
			bsp_priv->tx_delay);
	पूर्ण अन्यथा अणु
		dev_info(dev, "TX delay(0x%x).\n", value);
		bsp_priv->tx_delay = value;
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "rx_delay", &value);
	अगर (ret) अणु
		bsp_priv->rx_delay = 0x10;
		dev_err(dev, "Can not read property: rx_delay.");
		dev_err(dev, "set rx_delay to 0x%x\n",
			bsp_priv->rx_delay);
	पूर्ण अन्यथा अणु
		dev_info(dev, "RX delay(0x%x).\n", value);
		bsp_priv->rx_delay = value;
	पूर्ण

	bsp_priv->grf = syscon_regmap_lookup_by_phandle(dev->of_node,
							"rockchip,grf");

	अगर (plat->phy_node) अणु
		bsp_priv->पूर्णांकegrated_phy = of_property_पढ़ो_bool(plat->phy_node,
								 "phy-is-integrated");
		अगर (bsp_priv->पूर्णांकegrated_phy) अणु
			bsp_priv->phy_reset = of_reset_control_get(plat->phy_node, शून्य);
			अगर (IS_ERR(bsp_priv->phy_reset)) अणु
				dev_err(&pdev->dev, "No PHY reset control found.\n");
				bsp_priv->phy_reset = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
	dev_info(dev, "integrated PHY? (%s).\n",
		 bsp_priv->पूर्णांकegrated_phy ? "yes" : "no");

	bsp_priv->pdev = pdev;

	वापस bsp_priv;
पूर्ण

अटल पूर्णांक rk_gmac_घातerup(काष्ठा rk_priv_data *bsp_priv)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	ret = gmac_clk_enable(bsp_priv, true);
	अगर (ret)
		वापस ret;

	/*rmii or rgmii*/
	चयन (bsp_priv->phy_अगरace) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
		dev_info(dev, "init for RGMII\n");
		bsp_priv->ops->set_to_rgmii(bsp_priv, bsp_priv->tx_delay,
					    bsp_priv->rx_delay);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_ID:
		dev_info(dev, "init for RGMII_ID\n");
		bsp_priv->ops->set_to_rgmii(bsp_priv, 0, 0);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
		dev_info(dev, "init for RGMII_RXID\n");
		bsp_priv->ops->set_to_rgmii(bsp_priv, bsp_priv->tx_delay, 0);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		dev_info(dev, "init for RGMII_TXID\n");
		bsp_priv->ops->set_to_rgmii(bsp_priv, 0, bsp_priv->rx_delay);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		dev_info(dev, "init for RMII\n");
		bsp_priv->ops->set_to_rmii(bsp_priv);
		अवरोध;
	शेष:
		dev_err(dev, "NO interface defined!\n");
	पूर्ण

	ret = phy_घातer_on(bsp_priv, true);
	अगर (ret) अणु
		gmac_clk_enable(bsp_priv, false);
		वापस ret;
	पूर्ण

	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	अगर (bsp_priv->पूर्णांकegrated_phy)
		rk_gmac_पूर्णांकegrated_phy_घातerup(bsp_priv);

	वापस 0;
पूर्ण

अटल व्योम rk_gmac_घातerकरोwn(काष्ठा rk_priv_data *gmac)
अणु
	काष्ठा device *dev = &gmac->pdev->dev;

	अगर (gmac->पूर्णांकegrated_phy)
		rk_gmac_पूर्णांकegrated_phy_घातerकरोwn(gmac);

	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);

	phy_घातer_on(gmac, false);
	gmac_clk_enable(gmac, false);
पूर्ण

अटल व्योम rk_fix_speed(व्योम *priv, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा rk_priv_data *bsp_priv = priv;
	काष्ठा device *dev = &bsp_priv->pdev->dev;

	चयन (bsp_priv->phy_अगरace) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		bsp_priv->ops->set_rgmii_speed(bsp_priv, speed);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		bsp_priv->ops->set_rmii_speed(bsp_priv, speed);
		अवरोध;
	शेष:
		dev_err(dev, "unsupported interface %d", bsp_priv->phy_अगरace);
	पूर्ण
पूर्ण

अटल पूर्णांक rk_gmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	स्थिर काष्ठा rk_gmac_ops *data;
	पूर्णांक ret;

	data = of_device_get_match_data(&pdev->dev);
	अगर (!data) अणु
		dev_err(&pdev->dev, "no of match data provided\n");
		वापस -EINVAL;
	पूर्ण

	ret = sपंचांगmac_get_platक्रमm_resources(pdev, &sपंचांगmac_res);
	अगर (ret)
		वापस ret;

	plat_dat = sपंचांगmac_probe_config_dt(pdev, sपंचांगmac_res.mac);
	अगर (IS_ERR(plat_dat))
		वापस PTR_ERR(plat_dat);

	plat_dat->has_gmac = true;
	plat_dat->fix_mac_speed = rk_fix_speed;

	plat_dat->bsp_priv = rk_gmac_setup(pdev, plat_dat, data);
	अगर (IS_ERR(plat_dat->bsp_priv)) अणु
		ret = PTR_ERR(plat_dat->bsp_priv);
		जाओ err_हटाओ_config_dt;
	पूर्ण

	ret = rk_gmac_clk_init(plat_dat);
	अगर (ret)
		जाओ err_हटाओ_config_dt;

	ret = rk_gmac_घातerup(plat_dat->bsp_priv);
	अगर (ret)
		जाओ err_हटाओ_config_dt;

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret)
		जाओ err_gmac_घातerकरोwn;

	वापस 0;

err_gmac_घातerकरोwn:
	rk_gmac_घातerकरोwn(plat_dat->bsp_priv);
err_हटाओ_config_dt:
	sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);

	वापस ret;
पूर्ण

अटल पूर्णांक rk_gmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rk_priv_data *bsp_priv = get_sपंचांगmac_bsp_priv(&pdev->dev);
	पूर्णांक ret = sपंचांगmac_dvr_हटाओ(&pdev->dev);

	rk_gmac_घातerकरोwn(bsp_priv);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rk_gmac_suspend(काष्ठा device *dev)
अणु
	काष्ठा rk_priv_data *bsp_priv = get_sपंचांगmac_bsp_priv(dev);
	पूर्णांक ret = sपंचांगmac_suspend(dev);

	/* Keep the PHY up अगर we use Wake-on-Lan. */
	अगर (!device_may_wakeup(dev)) अणु
		rk_gmac_घातerकरोwn(bsp_priv);
		bsp_priv->suspended = true;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rk_gmac_resume(काष्ठा device *dev)
अणु
	काष्ठा rk_priv_data *bsp_priv = get_sपंचांगmac_bsp_priv(dev);

	/* The PHY was up क्रम Wake-on-Lan. */
	अगर (bsp_priv->suspended) अणु
		rk_gmac_घातerup(bsp_priv);
		bsp_priv->suspended = false;
	पूर्ण

	वापस sपंचांगmac_resume(dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(rk_gmac_pm_ops, rk_gmac_suspend, rk_gmac_resume);

अटल स्थिर काष्ठा of_device_id rk_gmac_dwmac_match[] = अणु
	अणु .compatible = "rockchip,px30-gmac",	.data = &px30_ops   पूर्ण,
	अणु .compatible = "rockchip,rk3128-gmac", .data = &rk3128_ops पूर्ण,
	अणु .compatible = "rockchip,rk3228-gmac", .data = &rk3228_ops पूर्ण,
	अणु .compatible = "rockchip,rk3288-gmac", .data = &rk3288_ops पूर्ण,
	अणु .compatible = "rockchip,rk3328-gmac", .data = &rk3328_ops पूर्ण,
	अणु .compatible = "rockchip,rk3366-gmac", .data = &rk3366_ops पूर्ण,
	अणु .compatible = "rockchip,rk3368-gmac", .data = &rk3368_ops पूर्ण,
	अणु .compatible = "rockchip,rk3399-gmac", .data = &rk3399_ops पूर्ण,
	अणु .compatible = "rockchip,rv1108-gmac", .data = &rv1108_ops पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rk_gmac_dwmac_match);

अटल काष्ठा platक्रमm_driver rk_gmac_dwmac_driver = अणु
	.probe  = rk_gmac_probe,
	.हटाओ = rk_gmac_हटाओ,
	.driver = अणु
		.name           = "rk_gmac-dwmac",
		.pm		= &rk_gmac_pm_ops,
		.of_match_table = rk_gmac_dwmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rk_gmac_dwmac_driver);

MODULE_AUTHOR("Chen-Zhi (Roger Chen) <roger.chen@rock-chips.com>");
MODULE_DESCRIPTION("Rockchip RK3288 DWMAC specific glue layer");
MODULE_LICENSE("GPL");
