<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2020 Texas Instruments Incorporated - https://www.ti.com
 *  Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <video/mipi_display.h>
#समावेश <video/videomode.h>

/* Global (16-bit addressable) */
#घोषणा TC358768_CHIPID			0x0000
#घोषणा TC358768_SYSCTL			0x0002
#घोषणा TC358768_CONFCTL		0x0004
#घोषणा TC358768_VSDLY			0x0006
#घोषणा TC358768_DATAFMT		0x0008
#घोषणा TC358768_GPIOEN			0x000E
#घोषणा TC358768_GPIOसूची		0x0010
#घोषणा TC358768_GPIOIN			0x0012
#घोषणा TC358768_GPIOOUT		0x0014
#घोषणा TC358768_PLLCTL0		0x0016
#घोषणा TC358768_PLLCTL1		0x0018
#घोषणा TC358768_CMDBYTE		0x0022
#घोषणा TC358768_PP_MISC		0x0032
#घोषणा TC358768_DSITX_DT		0x0050
#घोषणा TC358768_FIFOSTATUS		0x00F8

/* Debug (16-bit addressable) */
#घोषणा TC358768_VBUFCTRL		0x00E0
#घोषणा TC358768_DBG_WIDTH		0x00E2
#घोषणा TC358768_DBG_VBLANK		0x00E4
#घोषणा TC358768_DBG_DATA		0x00E8

/* TX PHY (32-bit addressable) */
#घोषणा TC358768_CLW_DPHYCONTTX		0x0100
#घोषणा TC358768_D0W_DPHYCONTTX		0x0104
#घोषणा TC358768_D1W_DPHYCONTTX		0x0108
#घोषणा TC358768_D2W_DPHYCONTTX		0x010C
#घोषणा TC358768_D3W_DPHYCONTTX		0x0110
#घोषणा TC358768_CLW_CNTRL		0x0140
#घोषणा TC358768_D0W_CNTRL		0x0144
#घोषणा TC358768_D1W_CNTRL		0x0148
#घोषणा TC358768_D2W_CNTRL		0x014C
#घोषणा TC358768_D3W_CNTRL		0x0150

/* TX PPI (32-bit addressable) */
#घोषणा TC358768_STARTCNTRL		0x0204
#घोषणा TC358768_DSITXSTATUS		0x0208
#घोषणा TC358768_LINEINITCNT		0x0210
#घोषणा TC358768_LPTXTIMECNT		0x0214
#घोषणा TC358768_TCLK_HEADERCNT		0x0218
#घोषणा TC358768_TCLK_TRAILCNT		0x021C
#घोषणा TC358768_THS_HEADERCNT		0x0220
#घोषणा TC358768_TWAKEUP		0x0224
#घोषणा TC358768_TCLK_POSTCNT		0x0228
#घोषणा TC358768_THS_TRAILCNT		0x022C
#घोषणा TC358768_HSTXVREGCNT		0x0230
#घोषणा TC358768_HSTXVREGEN		0x0234
#घोषणा TC358768_TXOPTIONCNTRL		0x0238
#घोषणा TC358768_BTACNTRL1		0x023C

/* TX CTRL (32-bit addressable) */
#घोषणा TC358768_DSI_CONTROL		0x040C
#घोषणा TC358768_DSI_STATUS		0x0410
#घोषणा TC358768_DSI_INT		0x0414
#घोषणा TC358768_DSI_INT_ENA		0x0418
#घोषणा TC358768_DSICMD_RDFIFO		0x0430
#घोषणा TC358768_DSI_ACKERR		0x0434
#घोषणा TC358768_DSI_ACKERR_INTENA	0x0438
#घोषणा TC358768_DSI_ACKERR_HALT	0x043c
#घोषणा TC358768_DSI_RXERR		0x0440
#घोषणा TC358768_DSI_RXERR_INTENA	0x0444
#घोषणा TC358768_DSI_RXERR_HALT		0x0448
#घोषणा TC358768_DSI_ERR		0x044C
#घोषणा TC358768_DSI_ERR_INTENA		0x0450
#घोषणा TC358768_DSI_ERR_HALT		0x0454
#घोषणा TC358768_DSI_CONFW		0x0500
#घोषणा TC358768_DSI_LPCMD		0x0500
#घोषणा TC358768_DSI_RESET		0x0504
#घोषणा TC358768_DSI_INT_CLR		0x050C
#घोषणा TC358768_DSI_START		0x0518

/* DSITX CTRL (16-bit addressable) */
#घोषणा TC358768_DSICMD_TX		0x0600
#घोषणा TC358768_DSICMD_TYPE		0x0602
#घोषणा TC358768_DSICMD_WC		0x0604
#घोषणा TC358768_DSICMD_WD0		0x0610
#घोषणा TC358768_DSICMD_WD1		0x0612
#घोषणा TC358768_DSICMD_WD2		0x0614
#घोषणा TC358768_DSICMD_WD3		0x0616
#घोषणा TC358768_DSI_EVENT		0x0620
#घोषणा TC358768_DSI_VSW		0x0622
#घोषणा TC358768_DSI_VBPR		0x0624
#घोषणा TC358768_DSI_VACT		0x0626
#घोषणा TC358768_DSI_HSW		0x0628
#घोषणा TC358768_DSI_HBPR		0x062A
#घोषणा TC358768_DSI_HACT		0x062C

/* TC358768_DSI_CONTROL (0x040C) रेजिस्टर */
#घोषणा TC358768_DSI_CONTROL_DIS_MODE	BIT(15)
#घोषणा TC358768_DSI_CONTROL_TXMD	BIT(7)
#घोषणा TC358768_DSI_CONTROL_HSCKMD	BIT(5)
#घोषणा TC358768_DSI_CONTROL_EOTDIS	BIT(0)

/* TC358768_DSI_CONFW (0x0500) रेजिस्टर */
#घोषणा TC358768_DSI_CONFW_MODE_SET	(5 << 29)
#घोषणा TC358768_DSI_CONFW_MODE_CLR	(6 << 29)
#घोषणा TC358768_DSI_CONFW_ADDR_DSI_CONTROL	(0x3 << 24)

अटल स्थिर अक्षर * स्थिर tc358768_supplies[] = अणु
	"vddc", "vddmipi", "vddio"
पूर्ण;

काष्ठा tc358768_dsi_output अणु
	काष्ठा mipi_dsi_device *dev;
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *bridge;
पूर्ण;

काष्ठा tc358768_priv अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(tc358768_supplies)];
	काष्ठा clk *refclk;
	पूर्णांक enabled;
	पूर्णांक error;

	काष्ठा mipi_dsi_host dsi_host;
	काष्ठा drm_bridge bridge;
	काष्ठा tc358768_dsi_output output;

	u32 pd_lines; /* number of Parallel Port Input Data Lines */
	u32 dsi_lanes; /* number of DSI Lanes */

	/* Parameters क्रम PLL programming */
	u32 fbd;	/* PLL feedback भागider */
	u32 prd;	/* PLL input भागider */
	u32 frs;	/* PLL Freqency range क्रम HSCK (post भागider) */

	u32 dsiclk;	/* pll_clk / 2 */
पूर्ण;

अटल अंतरभूत काष्ठा tc358768_priv *dsi_host_to_tc358768(काष्ठा mipi_dsi_host
							 *host)
अणु
	वापस container_of(host, काष्ठा tc358768_priv, dsi_host);
पूर्ण

अटल अंतरभूत काष्ठा tc358768_priv *bridge_to_tc358768(काष्ठा drm_bridge
						       *bridge)
अणु
	वापस container_of(bridge, काष्ठा tc358768_priv, bridge);
पूर्ण

अटल पूर्णांक tc358768_clear_error(काष्ठा tc358768_priv *priv)
अणु
	पूर्णांक ret = priv->error;

	priv->error = 0;
	वापस ret;
पूर्ण

अटल व्योम tc358768_ग_लिखो(काष्ठा tc358768_priv *priv, u32 reg, u32 val)
अणु
	/* work around https://gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */
	पूर्णांक पंचांगpval = val;
	माप_प्रकार count = 2;

	अगर (priv->error)
		वापस;

	/* 16-bit रेजिस्टर? */
	अगर (reg < 0x100 || reg >= 0x600)
		count = 1;

	priv->error = regmap_bulk_ग_लिखो(priv->regmap, reg, &पंचांगpval, count);
पूर्ण

अटल व्योम tc358768_पढ़ो(काष्ठा tc358768_priv *priv, u32 reg, u32 *val)
अणु
	माप_प्रकार count = 2;

	अगर (priv->error)
		वापस;

	/* 16-bit रेजिस्टर? */
	अगर (reg < 0x100 || reg >= 0x600) अणु
		*val = 0;
		count = 1;
	पूर्ण

	priv->error = regmap_bulk_पढ़ो(priv->regmap, reg, val, count);
पूर्ण

अटल व्योम tc358768_update_bits(काष्ठा tc358768_priv *priv, u32 reg, u32 mask,
				 u32 val)
अणु
	u32 पंचांगp, orig;

	tc358768_पढ़ो(priv, reg, &orig);
	पंचांगp = orig & ~mask;
	पंचांगp |= val & mask;
	अगर (पंचांगp != orig)
		tc358768_ग_लिखो(priv, reg, पंचांगp);
पूर्ण

अटल पूर्णांक tc358768_sw_reset(काष्ठा tc358768_priv *priv)
अणु
	/* Assert Reset */
	tc358768_ग_लिखो(priv, TC358768_SYSCTL, 1);
	/* Release Reset, Exit Sleep */
	tc358768_ग_लिखो(priv, TC358768_SYSCTL, 0);

	वापस tc358768_clear_error(priv);
पूर्ण

अटल व्योम tc358768_hw_enable(काष्ठा tc358768_priv *priv)
अणु
	पूर्णांक ret;

	अगर (priv->enabled)
		वापस;

	ret = regulator_bulk_enable(ARRAY_SIZE(priv->supplies), priv->supplies);
	अगर (ret < 0)
		dev_err(priv->dev, "error enabling regulators (%d)\n", ret);

	अगर (priv->reset_gpio)
		usleep_range(200, 300);

	/*
	 * The RESX is active low (GPIO_ACTIVE_LOW).
	 * DEASSERT (value = 0) the reset_gpio to enable the chip
	 */
	gpiod_set_value_cansleep(priv->reset_gpio, 0);

	/* रुको क्रम encoder घड़ीs to stabilize */
	usleep_range(1000, 2000);

	priv->enabled = true;
पूर्ण

अटल व्योम tc358768_hw_disable(काष्ठा tc358768_priv *priv)
अणु
	पूर्णांक ret;

	अगर (!priv->enabled)
		वापस;

	/*
	 * The RESX is active low (GPIO_ACTIVE_LOW).
	 * ASSERT (value = 1) the reset_gpio to disable the chip
	 */
	gpiod_set_value_cansleep(priv->reset_gpio, 1);

	ret = regulator_bulk_disable(ARRAY_SIZE(priv->supplies),
				     priv->supplies);
	अगर (ret < 0)
		dev_err(priv->dev, "error disabling regulators (%d)\n", ret);

	priv->enabled = false;
पूर्ण

अटल u32 tc358768_pll_to_pclk(काष्ठा tc358768_priv *priv, u32 pll_clk)
अणु
	वापस (u32)भाग_u64((u64)pll_clk * priv->dsi_lanes, priv->pd_lines);
पूर्ण

अटल u32 tc358768_pclk_to_pll(काष्ठा tc358768_priv *priv, u32 pclk)
अणु
	वापस (u32)भाग_u64((u64)pclk * priv->pd_lines, priv->dsi_lanes);
पूर्ण

अटल पूर्णांक tc358768_calc_pll(काष्ठा tc358768_priv *priv,
			     स्थिर काष्ठा drm_display_mode *mode,
			     bool verअगरy_only)
अणु
	स्थिर u32 frs_limits[] = अणु
		1000000000,
		500000000,
		250000000,
		125000000,
		62500000
	पूर्ण;
	अचिन्हित दीर्घ refclk;
	u32 prd, target_pll, i, max_pll, min_pll;
	u32 frs, best_dअगरf, best_pll, best_prd, best_fbd;

	target_pll = tc358768_pclk_to_pll(priv, mode->घड़ी * 1000);

	/* pll_clk = RefClk * [(FBD + 1)/ (PRD + 1)] * [1 / (2^FRS)] */

	क्रम (i = 0; i < ARRAY_SIZE(frs_limits); i++)
		अगर (target_pll >= frs_limits[i])
			अवरोध;

	अगर (i == ARRAY_SIZE(frs_limits) || i == 0)
		वापस -EINVAL;

	frs = i - 1;
	max_pll = frs_limits[i - 1];
	min_pll = frs_limits[i];

	refclk = clk_get_rate(priv->refclk);

	best_dअगरf = अच_पूर्णांक_उच्च;
	best_pll = 0;
	best_prd = 0;
	best_fbd = 0;

	क्रम (prd = 0; prd < 16; ++prd) अणु
		u32 भागisor = (prd + 1) * (1 << frs);
		u32 fbd;

		क्रम (fbd = 0; fbd < 512; ++fbd) अणु
			u32 pll, dअगरf;

			pll = (u32)भाग_u64((u64)refclk * (fbd + 1), भागisor);

			अगर (pll >= max_pll || pll < min_pll)
				जारी;

			dअगरf = max(pll, target_pll) - min(pll, target_pll);

			अगर (dअगरf < best_dअगरf) अणु
				best_dअगरf = dअगरf;
				best_pll = pll;
				best_prd = prd;
				best_fbd = fbd;

				अगर (best_dअगरf == 0)
					जाओ found;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (best_dअगरf == अच_पूर्णांक_उच्च) अणु
		dev_err(priv->dev, "could not find suitable PLL setup\n");
		वापस -EINVAL;
	पूर्ण

found:
	अगर (verअगरy_only)
		वापस 0;

	priv->fbd = best_fbd;
	priv->prd = best_prd;
	priv->frs = frs;
	priv->dsiclk = best_pll / 2;

	वापस 0;
पूर्ण

अटल पूर्णांक tc358768_dsi_host_attach(काष्ठा mipi_dsi_host *host,
				    काष्ठा mipi_dsi_device *dev)
अणु
	काष्ठा tc358768_priv *priv = dsi_host_to_tc358768(host);
	काष्ठा drm_bridge *bridge;
	काष्ठा drm_panel *panel;
	काष्ठा device_node *ep;
	पूर्णांक ret;

	अगर (dev->lanes > 4) अणु
		dev_err(priv->dev, "unsupported number of data lanes(%u)\n",
			dev->lanes);
		वापस -EINVAL;
	पूर्ण

	/*
	 * tc358768 supports both Video and Pulse mode, but the driver only
	 * implements Video (event) mode currently
	 */
	अगर (!(dev->mode_flags & MIPI_DSI_MODE_VIDEO)) अणु
		dev_err(priv->dev, "Only MIPI_DSI_MODE_VIDEO is supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	/*
	 * tc358768 supports RGB888, RGB666, RGB666_PACKED and RGB565, but only
	 * RGB888 is verअगरied.
	 */
	अगर (dev->क्रमmat != MIPI_DSI_FMT_RGB888) अणु
		dev_warn(priv->dev, "Only MIPI_DSI_FMT_RGB888 tested!\n");
		वापस -ENOTSUPP;
	पूर्ण

	ret = drm_of_find_panel_or_bridge(host->dev->of_node, 1, 0, &panel,
					  &bridge);
	अगर (ret)
		वापस ret;

	अगर (panel) अणु
		bridge = drm_panel_bridge_add_typed(panel,
						    DRM_MODE_CONNECTOR_DSI);
		अगर (IS_ERR(bridge))
			वापस PTR_ERR(bridge);
	पूर्ण

	priv->output.dev = dev;
	priv->output.bridge = bridge;
	priv->output.panel = panel;

	priv->dsi_lanes = dev->lanes;

	/* get input ep (port0/endpoपूर्णांक0) */
	ret = -EINVAL;
	ep = of_graph_get_endpoपूर्णांक_by_regs(host->dev->of_node, 0, 0);
	अगर (ep) अणु
		ret = of_property_पढ़ो_u32(ep, "data-lines", &priv->pd_lines);

		of_node_put(ep);
	पूर्ण

	अगर (ret)
		priv->pd_lines = mipi_dsi_pixel_क्रमmat_to_bpp(dev->क्रमmat);

	drm_bridge_add(&priv->bridge);

	वापस 0;
पूर्ण

अटल पूर्णांक tc358768_dsi_host_detach(काष्ठा mipi_dsi_host *host,
				    काष्ठा mipi_dsi_device *dev)
अणु
	काष्ठा tc358768_priv *priv = dsi_host_to_tc358768(host);

	drm_bridge_हटाओ(&priv->bridge);
	अगर (priv->output.panel)
		drm_panel_bridge_हटाओ(priv->output.bridge);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार tc358768_dsi_host_transfer(काष्ठा mipi_dsi_host *host,
					  स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा tc358768_priv *priv = dsi_host_to_tc358768(host);
	काष्ठा mipi_dsi_packet packet;
	पूर्णांक ret;

	अगर (!priv->enabled) अणु
		dev_err(priv->dev, "Bridge is not enabled\n");
		वापस -ENODEV;
	पूर्ण

	अगर (msg->rx_len) अणु
		dev_warn(priv->dev, "MIPI rx is not supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (msg->tx_len > 8) अणु
		dev_warn(priv->dev, "Maximum 8 byte MIPI tx is supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	ret = mipi_dsi_create_packet(&packet, msg);
	अगर (ret)
		वापस ret;

	अगर (mipi_dsi_packet_क्रमmat_is_लघु(msg->type)) अणु
		tc358768_ग_लिखो(priv, TC358768_DSICMD_TYPE,
			       (0x10 << 8) | (packet.header[0] & 0x3f));
		tc358768_ग_लिखो(priv, TC358768_DSICMD_WC, 0);
		tc358768_ग_लिखो(priv, TC358768_DSICMD_WD0,
			       (packet.header[2] << 8) | packet.header[1]);
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		tc358768_ग_लिखो(priv, TC358768_DSICMD_TYPE,
			       (0x40 << 8) | (packet.header[0] & 0x3f));
		tc358768_ग_लिखो(priv, TC358768_DSICMD_WC, packet.payload_length);
		क्रम (i = 0; i < packet.payload_length; i += 2) अणु
			u16 val = packet.payload[i];

			अगर (i + 1 < packet.payload_length)
				val |= packet.payload[i + 1] << 8;

			tc358768_ग_लिखो(priv, TC358768_DSICMD_WD0 + i, val);
		पूर्ण
	पूर्ण

	/* start transfer */
	tc358768_ग_लिखो(priv, TC358768_DSICMD_TX, 1);

	ret = tc358768_clear_error(priv);
	अगर (ret)
		dev_warn(priv->dev, "Software disable failed: %d\n", ret);
	अन्यथा
		ret = packet.size;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mipi_dsi_host_ops tc358768_dsi_host_ops = अणु
	.attach = tc358768_dsi_host_attach,
	.detach = tc358768_dsi_host_detach,
	.transfer = tc358768_dsi_host_transfer,
पूर्ण;

अटल पूर्णांक tc358768_bridge_attach(काष्ठा drm_bridge *bridge,
				  क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा tc358768_priv *priv = bridge_to_tc358768(bridge);

	अगर (!drm_core_check_feature(bridge->dev, DRIVER_ATOMIC)) अणु
		dev_err(priv->dev, "needs atomic updates support\n");
		वापस -ENOTSUPP;
	पूर्ण

	वापस drm_bridge_attach(bridge->encoder, priv->output.bridge, bridge,
				 flags);
पूर्ण

अटल क्रमागत drm_mode_status
tc358768_bridge_mode_valid(काष्ठा drm_bridge *bridge,
			   स्थिर काष्ठा drm_display_info *info,
			   स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा tc358768_priv *priv = bridge_to_tc358768(bridge);

	अगर (tc358768_calc_pll(priv, mode, true))
		वापस MODE_CLOCK_RANGE;

	वापस MODE_OK;
पूर्ण

अटल व्योम tc358768_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tc358768_priv *priv = bridge_to_tc358768(bridge);
	पूर्णांक ret;

	/* set FrmStop */
	tc358768_update_bits(priv, TC358768_PP_MISC, BIT(15), BIT(15));

	/* रुको at least क्रम one frame */
	msleep(50);

	/* clear PP_en */
	tc358768_update_bits(priv, TC358768_CONFCTL, BIT(6), 0);

	/* set RstPtr */
	tc358768_update_bits(priv, TC358768_PP_MISC, BIT(14), BIT(14));

	ret = tc358768_clear_error(priv);
	अगर (ret)
		dev_warn(priv->dev, "Software disable failed: %d\n", ret);
पूर्ण

अटल व्योम tc358768_bridge_post_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tc358768_priv *priv = bridge_to_tc358768(bridge);

	tc358768_hw_disable(priv);
पूर्ण

अटल पूर्णांक tc358768_setup_pll(काष्ठा tc358768_priv *priv,
			      स्थिर काष्ठा drm_display_mode *mode)
अणु
	u32 fbd, prd, frs;
	पूर्णांक ret;

	ret = tc358768_calc_pll(priv, mode, false);
	अगर (ret) अणु
		dev_err(priv->dev, "PLL calculation failed: %d\n", ret);
		वापस ret;
	पूर्ण

	fbd = priv->fbd;
	prd = priv->prd;
	frs = priv->frs;

	dev_dbg(priv->dev, "PLL: refclk %lu, fbd %u, prd %u, frs %u\n",
		clk_get_rate(priv->refclk), fbd, prd, frs);
	dev_dbg(priv->dev, "PLL: pll_clk: %u, DSIClk %u, DSIByteClk %u\n",
		priv->dsiclk * 2, priv->dsiclk, priv->dsiclk / 4);
	dev_dbg(priv->dev, "PLL: pclk %u (panel: %u)\n",
		tc358768_pll_to_pclk(priv, priv->dsiclk * 2),
		mode->घड़ी * 1000);

	/* PRD[15:12] FBD[8:0] */
	tc358768_ग_लिखो(priv, TC358768_PLLCTL0, (prd << 12) | fbd);

	/* FRS[11:10] LBWS[9:8] CKEN[4] RESETB[1] EN[0] */
	tc358768_ग_लिखो(priv, TC358768_PLLCTL1,
		       (frs << 10) | (0x2 << 8) | BIT(1) | BIT(0));

	/* रुको क्रम lock */
	usleep_range(1000, 2000);

	/* FRS[11:10] LBWS[9:8] CKEN[4] PLL_CKEN[4] RESETB[1] EN[0] */
	tc358768_ग_लिखो(priv, TC358768_PLLCTL1,
		       (frs << 10) | (0x2 << 8) | BIT(4) | BIT(1) | BIT(0));

	वापस tc358768_clear_error(priv);
पूर्ण

#घोषणा TC358768_PRECISION	1000
अटल u32 tc358768_ns_to_cnt(u32 ns, u32 period_nsk)
अणु
	वापस (ns * TC358768_PRECISION + period_nsk) / period_nsk;
पूर्ण

अटल u32 tc358768_to_ns(u32 nsk)
अणु
	वापस (nsk / TC358768_PRECISION);
पूर्ण

अटल व्योम tc358768_bridge_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tc358768_priv *priv = bridge_to_tc358768(bridge);
	काष्ठा mipi_dsi_device *dsi_dev = priv->output.dev;
	u32 val, val2, lptxcnt, hact, data_type;
	स्थिर काष्ठा drm_display_mode *mode;
	u32 dsibclk_nsk, dsiclk_nsk, ui_nsk, phy_delay_nsk;
	u32 dsiclk, dsibclk;
	पूर्णांक ret, i;

	tc358768_hw_enable(priv);

	ret = tc358768_sw_reset(priv);
	अगर (ret) अणु
		dev_err(priv->dev, "Software reset failed: %d\n", ret);
		tc358768_hw_disable(priv);
		वापस;
	पूर्ण

	mode = &bridge->encoder->crtc->state->adjusted_mode;
	ret = tc358768_setup_pll(priv, mode);
	अगर (ret) अणु
		dev_err(priv->dev, "PLL setup failed: %d\n", ret);
		tc358768_hw_disable(priv);
		वापस;
	पूर्ण

	dsiclk = priv->dsiclk;
	dsibclk = dsiclk / 4;

	/* Data Format Control Register */
	val = BIT(2) | BIT(1) | BIT(0); /* rdswap_en | dsitx_en | txdt_en */
	चयन (dsi_dev->क्रमmat) अणु
	हाल MIPI_DSI_FMT_RGB888:
		val |= (0x3 << 4);
		hact = mode->hdisplay * 3;
		data_type = MIPI_DSI_PACKED_PIXEL_STREAM_24;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666:
		val |= (0x4 << 4);
		hact = mode->hdisplay * 3;
		data_type = MIPI_DSI_PACKED_PIXEL_STREAM_18;
		अवरोध;

	हाल MIPI_DSI_FMT_RGB666_PACKED:
		val |= (0x4 << 4) | BIT(3);
		hact = mode->hdisplay * 18 / 8;
		data_type = MIPI_DSI_PIXEL_STREAM_3BYTE_18;
		अवरोध;

	हाल MIPI_DSI_FMT_RGB565:
		val |= (0x5 << 4);
		hact = mode->hdisplay * 2;
		data_type = MIPI_DSI_PACKED_PIXEL_STREAM_16;
		अवरोध;
	शेष:
		dev_err(priv->dev, "Invalid data format (%u)\n",
			dsi_dev->क्रमmat);
		tc358768_hw_disable(priv);
		वापस;
	पूर्ण

	/* VSDly[9:0] */
	tc358768_ग_लिखो(priv, TC358768_VSDLY, 1);

	tc358768_ग_लिखो(priv, TC358768_DATAFMT, val);
	tc358768_ग_लिखो(priv, TC358768_DSITX_DT, data_type);

	/* Enable D-PHY (HiZ->LP11) */
	tc358768_ग_लिखो(priv, TC358768_CLW_CNTRL, 0x0000);
	/* Enable lanes */
	क्रम (i = 0; i < dsi_dev->lanes; i++)
		tc358768_ग_लिखो(priv, TC358768_D0W_CNTRL + i * 4, 0x0000);

	/* DSI Timings */
	dsibclk_nsk = (u32)भाग_u64((u64)1000000000 * TC358768_PRECISION,
				  dsibclk);
	dsiclk_nsk = (u32)भाग_u64((u64)1000000000 * TC358768_PRECISION, dsiclk);
	ui_nsk = dsiclk_nsk / 2;
	phy_delay_nsk = dsibclk_nsk + 2 * dsiclk_nsk;
	dev_dbg(priv->dev, "dsiclk_nsk: %u\n", dsiclk_nsk);
	dev_dbg(priv->dev, "ui_nsk: %u\n", ui_nsk);
	dev_dbg(priv->dev, "dsibclk_nsk: %u\n", dsibclk_nsk);
	dev_dbg(priv->dev, "phy_delay_nsk: %u\n", phy_delay_nsk);

	/* LP11 > 100us क्रम D-PHY Rx Init */
	val = tc358768_ns_to_cnt(100 * 1000, dsibclk_nsk) - 1;
	dev_dbg(priv->dev, "LINEINITCNT: 0x%x\n", val);
	tc358768_ग_लिखो(priv, TC358768_LINEINITCNT, val);

	/* LPTimeCnt > 50ns */
	val = tc358768_ns_to_cnt(50, dsibclk_nsk) - 1;
	lptxcnt = val;
	dev_dbg(priv->dev, "LPTXTIMECNT: 0x%x\n", val);
	tc358768_ग_लिखो(priv, TC358768_LPTXTIMECNT, val);

	/* 38ns < TCLK_PREPARE < 95ns */
	val = tc358768_ns_to_cnt(65, dsibclk_nsk) - 1;
	/* TCLK_PREPARE > 300ns */
	val2 = tc358768_ns_to_cnt(300 + tc358768_to_ns(3 * ui_nsk),
				  dsibclk_nsk);
	val |= (val2 - tc358768_to_ns(phy_delay_nsk - dsibclk_nsk)) << 8;
	dev_dbg(priv->dev, "TCLK_HEADERCNT: 0x%x\n", val);
	tc358768_ग_लिखो(priv, TC358768_TCLK_HEADERCNT, val);

	/* TCLK_TRAIL > 60ns + 3*UI */
	val = 60 + tc358768_to_ns(3 * ui_nsk);
	val = tc358768_ns_to_cnt(val, dsibclk_nsk) - 5;
	dev_dbg(priv->dev, "TCLK_TRAILCNT: 0x%x\n", val);
	tc358768_ग_लिखो(priv, TC358768_TCLK_TRAILCNT, val);

	/* 40ns + 4*UI < THS_PREPARE < 85ns + 6*UI */
	val = 50 + tc358768_to_ns(4 * ui_nsk);
	val = tc358768_ns_to_cnt(val, dsibclk_nsk) - 1;
	/* THS_ZERO > 145ns + 10*UI */
	val2 = tc358768_ns_to_cnt(145 - tc358768_to_ns(ui_nsk), dsibclk_nsk);
	val |= (val2 - tc358768_to_ns(phy_delay_nsk)) << 8;
	dev_dbg(priv->dev, "THS_HEADERCNT: 0x%x\n", val);
	tc358768_ग_लिखो(priv, TC358768_THS_HEADERCNT, val);

	/* TWAKEUP > 1ms in lptxcnt steps */
	val = tc358768_ns_to_cnt(1020000, dsibclk_nsk);
	val = val / (lptxcnt + 1) - 1;
	dev_dbg(priv->dev, "TWAKEUP: 0x%x\n", val);
	tc358768_ग_लिखो(priv, TC358768_TWAKEUP, val);

	/* TCLK_POSTCNT > 60ns + 52*UI */
	val = tc358768_ns_to_cnt(60 + tc358768_to_ns(52 * ui_nsk),
				 dsibclk_nsk) - 3;
	dev_dbg(priv->dev, "TCLK_POSTCNT: 0x%x\n", val);
	tc358768_ग_लिखो(priv, TC358768_TCLK_POSTCNT, val);

	/* 60ns + 4*UI < THS_PREPARE < 105ns + 12*UI */
	val = tc358768_ns_to_cnt(60 + tc358768_to_ns(15 * ui_nsk),
				 dsibclk_nsk) - 5;
	dev_dbg(priv->dev, "THS_TRAILCNT: 0x%x\n", val);
	tc358768_ग_लिखो(priv, TC358768_THS_TRAILCNT, val);

	val = BIT(0);
	क्रम (i = 0; i < dsi_dev->lanes; i++)
		val |= BIT(i + 1);
	tc358768_ग_लिखो(priv, TC358768_HSTXVREGEN, val);

	अगर (!(dsi_dev->mode_flags & MIPI_DSI_CLOCK_NON_CONTINUOUS))
		tc358768_ग_लिखो(priv, TC358768_TXOPTIONCNTRL, 0x1);

	/* TXTAGOCNT[26:16] RXTASURECNT[10:0] */
	val = tc358768_to_ns((lptxcnt + 1) * dsibclk_nsk * 4);
	val = tc358768_ns_to_cnt(val, dsibclk_nsk) - 1;
	val2 = tc358768_ns_to_cnt(tc358768_to_ns((lptxcnt + 1) * dsibclk_nsk),
				  dsibclk_nsk) - 2;
	val |= val2 << 16;
	dev_dbg(priv->dev, "BTACNTRL1: 0x%x\n", val);
	tc358768_ग_लिखो(priv, TC358768_BTACNTRL1, val);

	/* START[0] */
	tc358768_ग_लिखो(priv, TC358768_STARTCNTRL, 1);

	/* Set event mode */
	tc358768_ग_लिखो(priv, TC358768_DSI_EVENT, 1);

	/* vsw (+ vbp) */
	tc358768_ग_लिखो(priv, TC358768_DSI_VSW,
		       mode->vtotal - mode->vsync_start);
	/* vbp (not used in event mode) */
	tc358768_ग_लिखो(priv, TC358768_DSI_VBPR, 0);
	/* vact */
	tc358768_ग_लिखो(priv, TC358768_DSI_VACT, mode->vdisplay);

	/* (hsw + hbp) * byteclk * ndl / pclk */
	val = (u32)भाग_u64((mode->htotal - mode->hsync_start) *
			   ((u64)priv->dsiclk / 4) * priv->dsi_lanes,
			   mode->घड़ी * 1000);
	tc358768_ग_लिखो(priv, TC358768_DSI_HSW, val);
	/* hbp (not used in event mode) */
	tc358768_ग_लिखो(priv, TC358768_DSI_HBPR, 0);
	/* hact (bytes) */
	tc358768_ग_लिखो(priv, TC358768_DSI_HACT, hact);

	/* VSYNC polarity */
	अगर (!(mode->flags & DRM_MODE_FLAG_NVSYNC))
		tc358768_update_bits(priv, TC358768_CONFCTL, BIT(5), BIT(5));
	/* HSYNC polarity */
	अगर (mode->flags & DRM_MODE_FLAG_PHSYNC)
		tc358768_update_bits(priv, TC358768_PP_MISC, BIT(0), BIT(0));

	/* Start DSI Tx */
	tc358768_ग_लिखो(priv, TC358768_DSI_START, 0x1);

	/* Configure DSI_Control रेजिस्टर */
	val = TC358768_DSI_CONFW_MODE_CLR | TC358768_DSI_CONFW_ADDR_DSI_CONTROL;
	val |= TC358768_DSI_CONTROL_TXMD | TC358768_DSI_CONTROL_HSCKMD |
	       0x3 << 1 | TC358768_DSI_CONTROL_EOTDIS;
	tc358768_ग_लिखो(priv, TC358768_DSI_CONFW, val);

	val = TC358768_DSI_CONFW_MODE_SET | TC358768_DSI_CONFW_ADDR_DSI_CONTROL;
	val |= (dsi_dev->lanes - 1) << 1;

	अगर (!(dsi_dev->mode_flags & MIPI_DSI_MODE_LPM))
		val |= TC358768_DSI_CONTROL_TXMD;

	अगर (!(dsi_dev->mode_flags & MIPI_DSI_CLOCK_NON_CONTINUOUS))
		val |= TC358768_DSI_CONTROL_HSCKMD;

	अगर (dsi_dev->mode_flags & MIPI_DSI_MODE_EOT_PACKET)
		val |= TC358768_DSI_CONTROL_EOTDIS;

	tc358768_ग_लिखो(priv, TC358768_DSI_CONFW, val);

	val = TC358768_DSI_CONFW_MODE_CLR | TC358768_DSI_CONFW_ADDR_DSI_CONTROL;
	val |= TC358768_DSI_CONTROL_DIS_MODE; /* DSI mode */
	tc358768_ग_लिखो(priv, TC358768_DSI_CONFW, val);

	ret = tc358768_clear_error(priv);
	अगर (ret) अणु
		dev_err(priv->dev, "Bridge pre_enable failed: %d\n", ret);
		tc358768_bridge_disable(bridge);
		tc358768_bridge_post_disable(bridge);
	पूर्ण
पूर्ण

अटल व्योम tc358768_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tc358768_priv *priv = bridge_to_tc358768(bridge);
	पूर्णांक ret;

	अगर (!priv->enabled) अणु
		dev_err(priv->dev, "Bridge is not enabled\n");
		वापस;
	पूर्ण

	/* clear FrmStop and RstPtr */
	tc358768_update_bits(priv, TC358768_PP_MISC, 0x3 << 14, 0);

	/* set PP_en */
	tc358768_update_bits(priv, TC358768_CONFCTL, BIT(6), BIT(6));

	ret = tc358768_clear_error(priv);
	अगर (ret) अणु
		dev_err(priv->dev, "Bridge enable failed: %d\n", ret);
		tc358768_bridge_disable(bridge);
		tc358768_bridge_post_disable(bridge);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs tc358768_bridge_funcs = अणु
	.attach = tc358768_bridge_attach,
	.mode_valid = tc358768_bridge_mode_valid,
	.pre_enable = tc358768_bridge_pre_enable,
	.enable = tc358768_bridge_enable,
	.disable = tc358768_bridge_disable,
	.post_disable = tc358768_bridge_post_disable,
पूर्ण;

अटल स्थिर काष्ठा drm_bridge_timings शेष_tc358768_timings = अणु
	.input_bus_flags = DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE
		 | DRM_BUS_FLAG_SYNC_SAMPLE_NEGEDGE
		 | DRM_BUS_FLAG_DE_HIGH,
पूर्ण;

अटल bool tc358768_is_reserved_reg(अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x114 ... 0x13f:
	हाल 0x200:
	हाल 0x20c:
	हाल 0x400 ... 0x408:
	हाल 0x41c ... 0x42f:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool tc358768_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (tc358768_is_reserved_reg(reg))
		वापस false;

	चयन (reg) अणु
	हाल TC358768_CHIPID:
	हाल TC358768_FIFOSTATUS:
	हाल TC358768_DSITXSTATUS ... (TC358768_DSITXSTATUS + 2):
	हाल TC358768_DSI_CONTROL ... (TC358768_DSI_INT_ENA + 2):
	हाल TC358768_DSICMD_RDFIFO ... (TC358768_DSI_ERR_HALT + 2):
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool tc358768_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (tc358768_is_reserved_reg(reg))
		वापस false;

	चयन (reg) अणु
	हाल TC358768_STARTCNTRL:
	हाल TC358768_DSI_CONFW ... (TC358768_DSI_CONFW + 2):
	हाल TC358768_DSI_INT_CLR ... (TC358768_DSI_INT_CLR + 2):
	हाल TC358768_DSI_START ... (TC358768_DSI_START + 2):
	हाल TC358768_DBG_DATA:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config tc358768_regmap_config = अणु
	.name = "tc358768",
	.reg_bits = 16,
	.val_bits = 16,
	.max_रेजिस्टर = TC358768_DSI_HACT,
	.cache_type = REGCACHE_NONE,
	.ग_लिखोable_reg = tc358768_ग_लिखोable_reg,
	.पढ़ोable_reg = tc358768_पढ़ोable_reg,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian = REGMAP_ENDIAN_BIG,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id tc358768_i2c_ids[] = अणु
	अणु "tc358768", 0 पूर्ण,
	अणु "tc358778", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tc358768_i2c_ids);

अटल स्थिर काष्ठा of_device_id tc358768_of_ids[] = अणु
	अणु .compatible = "toshiba,tc358768", पूर्ण,
	अणु .compatible = "toshiba,tc358778", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tc358768_of_ids);

अटल पूर्णांक tc358768_get_regulators(काष्ठा tc358768_priv *priv)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(priv->supplies); ++i)
		priv->supplies[i].supply = tc358768_supplies[i];

	ret = devm_regulator_bulk_get(priv->dev, ARRAY_SIZE(priv->supplies),
				      priv->supplies);
	अगर (ret < 0)
		dev_err(priv->dev, "failed to get regulators: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक tc358768_i2c_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tc358768_priv *priv;
	काष्ठा device *dev = &client->dev;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	अगर (!np)
		वापस -ENODEV;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	dev_set_drvdata(dev, priv);
	priv->dev = dev;

	ret = tc358768_get_regulators(priv);
	अगर (ret)
		वापस ret;

	priv->refclk = devm_clk_get(dev, "refclk");
	अगर (IS_ERR(priv->refclk))
		वापस PTR_ERR(priv->refclk);

	/*
	 * RESX is low active, to disable tc358768 initially (keep in reset)
	 * the gpio line must be LOW. This is the ASSERTED state of
	 * GPIO_ACTIVE_LOW (GPIOD_OUT_HIGH == ASSERTED).
	 */
	priv->reset_gpio  = devm_gpiod_get_optional(dev, "reset",
						    GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->reset_gpio))
		वापस PTR_ERR(priv->reset_gpio);

	priv->regmap = devm_regmap_init_i2c(client, &tc358768_regmap_config);
	अगर (IS_ERR(priv->regmap)) अणु
		dev_err(dev, "Failed to init regmap\n");
		वापस PTR_ERR(priv->regmap);
	पूर्ण

	priv->dsi_host.dev = dev;
	priv->dsi_host.ops = &tc358768_dsi_host_ops;

	priv->bridge.funcs = &tc358768_bridge_funcs;
	priv->bridge.timings = &शेष_tc358768_timings;
	priv->bridge.of_node = np;

	i2c_set_clientdata(client, priv);

	वापस mipi_dsi_host_रेजिस्टर(&priv->dsi_host);
पूर्ण

अटल पूर्णांक tc358768_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tc358768_priv *priv = i2c_get_clientdata(client);

	mipi_dsi_host_unरेजिस्टर(&priv->dsi_host);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver tc358768_driver = अणु
	.driver = अणु
		.name = "tc358768",
		.of_match_table = tc358768_of_ids,
	पूर्ण,
	.id_table = tc358768_i2c_ids,
	.probe = tc358768_i2c_probe,
	.हटाओ	= tc358768_i2c_हटाओ,
पूर्ण;
module_i2c_driver(tc358768_driver);

MODULE_AUTHOR("Peter Ujfalusi <peter.ujfalusi@ti.com>");
MODULE_DESCRIPTION("TC358768AXBG/TC358778XBG DSI bridge");
MODULE_LICENSE("GPL v2");
