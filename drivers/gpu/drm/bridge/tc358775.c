<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * TC358775 DSI to LVDS bridge driver
 *
 * Copyright (C) 2020 SMART Wireless Computing
 * Author: Vinay Simha BN <simhavcs@gmail.com>
 *
 */
/* #घोषणा DEBUG */
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/unaligned.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_probe_helper.h>

#घोषणा FLD_VAL(val, start, end) FIELD_PREP(GENMASK(start, end), val)

/* Registers */

/* DSI D-PHY Layer Registers */
#घोषणा D0W_DPHYCONTTX  0x0004  /* Data Lane 0 DPHY Tx Control */
#घोषणा CLW_DPHYCONTRX  0x0020  /* Clock Lane DPHY Rx Control */
#घोषणा D0W_DPHYCONTRX  0x0024  /* Data Lane 0 DPHY Rx Control */
#घोषणा D1W_DPHYCONTRX  0x0028  /* Data Lane 1 DPHY Rx Control */
#घोषणा D2W_DPHYCONTRX  0x002C  /* Data Lane 2 DPHY Rx Control */
#घोषणा D3W_DPHYCONTRX  0x0030  /* Data Lane 3 DPHY Rx Control */
#घोषणा COM_DPHYCONTRX  0x0038  /* DPHY Rx Common Control */
#घोषणा CLW_CNTRL       0x0040  /* Clock Lane Control */
#घोषणा D0W_CNTRL       0x0044  /* Data Lane 0 Control */
#घोषणा D1W_CNTRL       0x0048  /* Data Lane 1 Control */
#घोषणा D2W_CNTRL       0x004C  /* Data Lane 2 Control */
#घोषणा D3W_CNTRL       0x0050  /* Data Lane 3 Control */
#घोषणा DFTMODE_CNTRL   0x0054  /* DFT Mode Control */

/* DSI PPI Layer Registers */
#घोषणा PPI_STARTPPI    0x0104  /* START control bit of PPI-TX function. */
#घोषणा PPI_START_FUNCTION      1

#घोषणा PPI_BUSYPPI     0x0108
#घोषणा PPI_LINEINITCNT 0x0110  /* Line Initialization Wait Counter  */
#घोषणा PPI_LPTXTIMECNT 0x0114
#घोषणा PPI_LANEENABLE  0x0134  /* Enables each lane at the PPI layer. */
#घोषणा PPI_TX_RX_TA    0x013C  /* DSI Bus Turn Around timing parameters */

/* Analog समयr function enable */
#घोषणा PPI_CLS_ATMR    0x0140  /* Delay क्रम Clock Lane in LPRX  */
#घोषणा PPI_D0S_ATMR    0x0144  /* Delay क्रम Data Lane 0 in LPRX */
#घोषणा PPI_D1S_ATMR    0x0148  /* Delay क्रम Data Lane 1 in LPRX */
#घोषणा PPI_D2S_ATMR    0x014C  /* Delay क्रम Data Lane 2 in LPRX */
#घोषणा PPI_D3S_ATMR    0x0150  /* Delay क्रम Data Lane 3 in LPRX */

#घोषणा PPI_D0S_CLRSIPOCOUNT    0x0164  /* For lane 0 */
#घोषणा PPI_D1S_CLRSIPOCOUNT    0x0168  /* For lane 1 */
#घोषणा PPI_D2S_CLRSIPOCOUNT    0x016C  /* For lane 2 */
#घोषणा PPI_D3S_CLRSIPOCOUNT    0x0170  /* For lane 3 */

#घोषणा CLS_PRE         0x0180  /* Digital Counter inside of PHY IO */
#घोषणा D0S_PRE         0x0184  /* Digital Counter inside of PHY IO */
#घोषणा D1S_PRE         0x0188  /* Digital Counter inside of PHY IO */
#घोषणा D2S_PRE         0x018C  /* Digital Counter inside of PHY IO */
#घोषणा D3S_PRE         0x0190  /* Digital Counter inside of PHY IO */
#घोषणा CLS_PREP        0x01A0  /* Digital Counter inside of PHY IO */
#घोषणा D0S_PREP        0x01A4  /* Digital Counter inside of PHY IO */
#घोषणा D1S_PREP        0x01A8  /* Digital Counter inside of PHY IO */
#घोषणा D2S_PREP        0x01AC  /* Digital Counter inside of PHY IO */
#घोषणा D3S_PREP        0x01B0  /* Digital Counter inside of PHY IO */
#घोषणा CLS_ZERO        0x01C0  /* Digital Counter inside of PHY IO */
#घोषणा D0S_ZERO        0x01C4  /* Digital Counter inside of PHY IO */
#घोषणा D1S_ZERO        0x01C8  /* Digital Counter inside of PHY IO */
#घोषणा D2S_ZERO        0x01CC  /* Digital Counter inside of PHY IO */
#घोषणा D3S_ZERO        0x01D0  /* Digital Counter inside of PHY IO */

#घोषणा PPI_CLRFLG      0x01E0  /* PRE Counters has reached set values */
#घोषणा PPI_CLRSIPO     0x01E4  /* Clear SIPO values, Slave mode use only. */
#घोषणा HSTIMEOUT       0x01F0  /* HS Rx Time Out Counter */
#घोषणा HSTIMEOUTENABLE 0x01F4  /* Enable HS Rx Time Out Counter */
#घोषणा DSI_STARTDSI    0x0204  /* START control bit of DSI-TX function */
#घोषणा DSI_RX_START	1

#घोषणा DSI_BUSYDSI     0x0208
#घोषणा DSI_LANEENABLE  0x0210  /* Enables each lane at the Protocol layer. */
#घोषणा DSI_LANESTATUS0 0x0214  /* Displays lane is in HS RX mode. */
#घोषणा DSI_LANESTATUS1 0x0218  /* Displays lane is in ULPS or STOP state */

#घोषणा DSI_INTSTATUS   0x0220  /* Interrupt Status */
#घोषणा DSI_INTMASK     0x0224  /* Interrupt Mask */
#घोषणा DSI_INTCLR      0x0228  /* Interrupt Clear */
#घोषणा DSI_LPTXTO      0x0230  /* Low Power Tx Time Out Counter */

#घोषणा DSIERRCNT       0x0300  /* DSI Error Count */
#घोषणा APLCTRL         0x0400  /* Application Layer Control */
#घोषणा RDPKTLN         0x0404  /* Command Read Packet Length */

#घोषणा VPCTRL          0x0450  /* Video Path Control */
#घोषणा HTIM1           0x0454  /* Horizontal Timing Control 1 */
#घोषणा HTIM2           0x0458  /* Horizontal Timing Control 2 */
#घोषणा VTIM1           0x045C  /* Vertical Timing Control 1 */
#घोषणा VTIM2           0x0460  /* Vertical Timing Control 2 */
#घोषणा VFUEN           0x0464  /* Video Frame Timing Update Enable */
#घोषणा VFUEN_EN	BIT(0)  /* Upload Enable */

/* Mux Input Select क्रम LVDS LINK Input */
#घोषणा LV_MX0003        0x0480  /* Bit 0 to 3 */
#घोषणा LV_MX0407        0x0484  /* Bit 4 to 7 */
#घोषणा LV_MX0811        0x0488  /* Bit 8 to 11 */
#घोषणा LV_MX1215        0x048C  /* Bit 12 to 15 */
#घोषणा LV_MX1619        0x0490  /* Bit 16 to 19 */
#घोषणा LV_MX2023        0x0494  /* Bit 20 to 23 */
#घोषणा LV_MX2427        0x0498  /* Bit 24 to 27 */
#घोषणा LV_MX(b0, b1, b2, b3)	(FLD_VAL(b0, 4, 0) | FLD_VAL(b1, 12, 8) | \
				FLD_VAL(b2, 20, 16) | FLD_VAL(b3, 28, 24))

/* Input bit numbers used in mux रेजिस्टरs */
क्रमागत अणु
	LVI_R0,
	LVI_R1,
	LVI_R2,
	LVI_R3,
	LVI_R4,
	LVI_R5,
	LVI_R6,
	LVI_R7,
	LVI_G0,
	LVI_G1,
	LVI_G2,
	LVI_G3,
	LVI_G4,
	LVI_G5,
	LVI_G6,
	LVI_G7,
	LVI_B0,
	LVI_B1,
	LVI_B2,
	LVI_B3,
	LVI_B4,
	LVI_B5,
	LVI_B6,
	LVI_B7,
	LVI_HS,
	LVI_VS,
	LVI_DE,
	LVI_L0
पूर्ण;

#घोषणा LVCFG           0x049C  /* LVDS Configuration  */
#घोषणा LVPHY0          0x04A0  /* LVDS PHY 0 */
#घोषणा LV_PHY0_RST(v)          FLD_VAL(v, 22, 22) /* PHY reset */
#घोषणा LV_PHY0_IS(v)           FLD_VAL(v, 15, 14)
#घोषणा LV_PHY0_ND(v)           FLD_VAL(v, 4, 0) /* Frequency range select */
#घोषणा LV_PHY0_PRBS_ON(v)      FLD_VAL(v, 20, 16) /* Clock/Data Flag pins */

#घोषणा LVPHY1          0x04A4  /* LVDS PHY 1 */
#घोषणा SYSSTAT         0x0500  /* System Status  */
#घोषणा SYSRST          0x0504  /* System Reset  */

#घोषणा SYS_RST_I2CS	BIT(0) /* Reset I2C-Slave controller */
#घोषणा SYS_RST_I2CM	BIT(1) /* Reset I2C-Master controller */
#घोषणा SYS_RST_LCD	BIT(2) /* Reset LCD controller */
#घोषणा SYS_RST_BM	BIT(3) /* Reset Bus Management controller */
#घोषणा SYS_RST_DSIRX	BIT(4) /* Reset DSI-RX and App controller */
#घोषणा SYS_RST_REG	BIT(5) /* Reset Register module */

/* GPIO Registers */
#घोषणा GPIOC           0x0520  /* GPIO Control  */
#घोषणा GPIOO           0x0524  /* GPIO Output  */
#घोषणा GPIOI           0x0528  /* GPIO Input  */

/* I2C Registers */
#घोषणा I2CTIMCTRL      0x0540  /* I2C IF Timing and Enable Control */
#घोषणा I2CMADDR        0x0544  /* I2C Master Addressing */
#घोषणा WDATAQ          0x0548  /* Write Data Queue */
#घोषणा RDATAQ          0x054C  /* Read Data Queue */

/* Chip ID and Revision ID Register */
#घोषणा IDREG           0x0580

#घोषणा LPX_PERIOD		4
#घोषणा TTA_GET			0x40000
#घोषणा TTA_SURE		6
#घोषणा SINGLE_LINK		1
#घोषणा DUAL_LINK		2

#घोषणा TC358775XBG_ID  0x00007500

/* Debug Registers */
#घोषणा DEBUG00         0x05A0  /* Debug */
#घोषणा DEBUG01         0x05A4  /* LVDS Data */

#घोषणा DSI_CLEN_BIT		BIT(0)
#घोषणा DIVIDE_BY_3		3 /* PCLK=DCLK/3 */
#घोषणा DIVIDE_BY_6		6 /* PCLK=DCLK/6 */
#घोषणा LVCFG_LVEN_BIT		BIT(0)

#घोषणा L0EN BIT(1)

#घोषणा TC358775_VPCTRL_VSDELAY__MASK	0x3FF00000
#घोषणा TC358775_VPCTRL_VSDELAY__SHIFT	20
अटल अंतरभूत u32 TC358775_VPCTRL_VSDELAY(uपूर्णांक32_t val)
अणु
	वापस ((val) << TC358775_VPCTRL_VSDELAY__SHIFT) &
			TC358775_VPCTRL_VSDELAY__MASK;
पूर्ण

#घोषणा TC358775_VPCTRL_OPXLFMT__MASK	0x00000100
#घोषणा TC358775_VPCTRL_OPXLFMT__SHIFT	8
अटल अंतरभूत u32 TC358775_VPCTRL_OPXLFMT(uपूर्णांक32_t val)
अणु
	वापस ((val) << TC358775_VPCTRL_OPXLFMT__SHIFT) &
			TC358775_VPCTRL_OPXLFMT__MASK;
पूर्ण

#घोषणा TC358775_VPCTRL_MSF__MASK	0x00000001
#घोषणा TC358775_VPCTRL_MSF__SHIFT	0
अटल अंतरभूत u32 TC358775_VPCTRL_MSF(uपूर्णांक32_t val)
अणु
	वापस ((val) << TC358775_VPCTRL_MSF__SHIFT) &
			TC358775_VPCTRL_MSF__MASK;
पूर्ण

#घोषणा TC358775_LVCFG_PCLKDIV__MASK	0x000000f0
#घोषणा TC358775_LVCFG_PCLKDIV__SHIFT	4
अटल अंतरभूत u32 TC358775_LVCFG_PCLKDIV(uपूर्णांक32_t val)
अणु
	वापस ((val) << TC358775_LVCFG_PCLKDIV__SHIFT) &
			TC358775_LVCFG_PCLKDIV__MASK;
पूर्ण

#घोषणा TC358775_LVCFG_LVDLINK__MASK                         0x00000002
#घोषणा TC358775_LVCFG_LVDLINK__SHIFT                        0
अटल अंतरभूत u32 TC358775_LVCFG_LVDLINK(uपूर्णांक32_t val)
अणु
	वापस ((val) << TC358775_LVCFG_LVDLINK__SHIFT) &
			TC358775_LVCFG_LVDLINK__MASK;
पूर्ण

क्रमागत tc358775_ports अणु
	TC358775_DSI_IN,
	TC358775_LVDS_OUT0,
	TC358775_LVDS_OUT1,
पूर्ण;

काष्ठा tc_data अणु
	काष्ठा i2c_client	*i2c;
	काष्ठा device		*dev;

	काष्ठा drm_bridge	bridge;
	काष्ठा drm_bridge	*panel_bridge;

	काष्ठा device_node *host_node;
	काष्ठा mipi_dsi_device *dsi;
	u8 num_dsi_lanes;

	काष्ठा regulator	*vdd;
	काष्ठा regulator	*vddio;
	काष्ठा gpio_desc	*reset_gpio;
	काष्ठा gpio_desc	*stby_gpio;
	u8			lvds_link; /* single-link or dual-link */
	u8			bpc;
पूर्ण;

अटल अंतरभूत काष्ठा tc_data *bridge_to_tc(काष्ठा drm_bridge *b)
अणु
	वापस container_of(b, काष्ठा tc_data, bridge);
पूर्ण

अटल व्योम tc_bridge_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tc_data *tc = bridge_to_tc(bridge);
	काष्ठा device *dev = &tc->dsi->dev;
	पूर्णांक ret;

	ret = regulator_enable(tc->vddio);
	अगर (ret < 0)
		dev_err(dev, "regulator vddio enable failed, %d\n", ret);
	usleep_range(10000, 11000);

	ret = regulator_enable(tc->vdd);
	अगर (ret < 0)
		dev_err(dev, "regulator vdd enable failed, %d\n", ret);
	usleep_range(10000, 11000);

	gpiod_set_value(tc->stby_gpio, 0);
	usleep_range(10000, 11000);

	gpiod_set_value(tc->reset_gpio, 0);
	usleep_range(10, 20);
पूर्ण

अटल व्योम tc_bridge_post_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tc_data *tc = bridge_to_tc(bridge);
	काष्ठा device *dev = &tc->dsi->dev;
	पूर्णांक ret;

	gpiod_set_value(tc->reset_gpio, 1);
	usleep_range(10, 20);

	gpiod_set_value(tc->stby_gpio, 1);
	usleep_range(10000, 11000);

	ret = regulator_disable(tc->vdd);
	अगर (ret < 0)
		dev_err(dev, "regulator vdd disable failed, %d\n", ret);
	usleep_range(10000, 11000);

	ret = regulator_disable(tc->vddio);
	अगर (ret < 0)
		dev_err(dev, "regulator vddio disable failed, %d\n", ret);
	usleep_range(10000, 11000);
पूर्ण

अटल व्योम d2l_पढ़ो(काष्ठा i2c_client *i2c, u16 addr, u32 *val)
अणु
	पूर्णांक ret;
	u8 buf_addr[2];

	put_unaligned_be16(addr, buf_addr);
	ret = i2c_master_send(i2c, buf_addr, माप(buf_addr));
	अगर (ret < 0)
		जाओ fail;

	ret = i2c_master_recv(i2c, (u8 *)val, माप(*val));
	अगर (ret < 0)
		जाओ fail;

	pr_debug("d2l: I2C : addr:%04x value:%08x\n", addr, *val);

fail:
	dev_err(&i2c->dev, "Error %d reading from subaddress 0x%x\n",
		ret, addr);
पूर्ण

अटल व्योम d2l_ग_लिखो(काष्ठा i2c_client *i2c, u16 addr, u32 val)
अणु
	u8 data[6];
	पूर्णांक ret;

	put_unaligned_be16(addr, data);
	put_unaligned_le32(val, data + 2);

	ret = i2c_master_send(i2c, data, ARRAY_SIZE(data));
	अगर (ret < 0)
		dev_err(&i2c->dev, "Error %d writing to subaddress 0x%x\n",
			ret, addr);
पूर्ण

/* helper function to access bus_क्रमmats */
अटल काष्ठा drm_connector *get_connector(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_connector *connector;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head)
		अगर (connector->encoder == encoder)
			वापस connector;

	वापस शून्य;
पूर्ण

अटल व्योम tc_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tc_data *tc = bridge_to_tc(bridge);
	u32 hback_porch, hsync_len, hfront_porch, hactive, hसमय1, hसमय2;
	u32 vback_porch, vsync_len, vfront_porch, vactive, vसमय1, vसमय2;
	u32 val = 0;
	u16 dsiclk, clkभाग, byteclk, t1, t2, t3, vsdelay;
	काष्ठा drm_display_mode *mode;
	काष्ठा drm_connector *connector = get_connector(bridge->encoder);

	mode = &bridge->encoder->crtc->state->adjusted_mode;

	hback_porch = mode->htotal - mode->hsync_end;
	hsync_len  = mode->hsync_end - mode->hsync_start;
	vback_porch = mode->vtotal - mode->vsync_end;
	vsync_len  = mode->vsync_end - mode->vsync_start;

	hसमय1 = (hback_porch << 16) + hsync_len;
	vसमय1 = (vback_porch << 16) + vsync_len;

	hfront_porch = mode->hsync_start - mode->hdisplay;
	hactive = mode->hdisplay;
	vfront_porch = mode->vsync_start - mode->vdisplay;
	vactive = mode->vdisplay;

	hसमय2 = (hfront_porch << 16) + hactive;
	vसमय2 = (vfront_porch << 16) + vactive;

	d2l_पढ़ो(tc->i2c, IDREG, &val);

	dev_info(tc->dev, "DSI2LVDS Chip ID.%02x Revision ID. %02x **\n",
		 (val >> 8) & 0xFF, val & 0xFF);

	d2l_ग_लिखो(tc->i2c, SYSRST, SYS_RST_REG | SYS_RST_DSIRX | SYS_RST_BM |
		  SYS_RST_LCD | SYS_RST_I2CM | SYS_RST_I2CS);
	usleep_range(30000, 40000);

	d2l_ग_लिखो(tc->i2c, PPI_TX_RX_TA, TTA_GET | TTA_SURE);
	d2l_ग_लिखो(tc->i2c, PPI_LPTXTIMECNT, LPX_PERIOD);
	d2l_ग_लिखो(tc->i2c, PPI_D0S_CLRSIPOCOUNT, 3);
	d2l_ग_लिखो(tc->i2c, PPI_D1S_CLRSIPOCOUNT, 3);
	d2l_ग_लिखो(tc->i2c, PPI_D2S_CLRSIPOCOUNT, 3);
	d2l_ग_लिखो(tc->i2c, PPI_D3S_CLRSIPOCOUNT, 3);

	val = ((L0EN << tc->num_dsi_lanes) - L0EN) | DSI_CLEN_BIT;
	d2l_ग_लिखो(tc->i2c, PPI_LANEENABLE, val);
	d2l_ग_लिखो(tc->i2c, DSI_LANEENABLE, val);

	d2l_ग_लिखो(tc->i2c, PPI_STARTPPI, PPI_START_FUNCTION);
	d2l_ग_लिखो(tc->i2c, DSI_STARTDSI, DSI_RX_START);

	अगर (tc->bpc == 8)
		val = TC358775_VPCTRL_OPXLFMT(1);
	अन्यथा /* bpc = 6; */
		val = TC358775_VPCTRL_MSF(1);

	dsiclk = mode->crtc_घड़ी * 3 * tc->bpc / tc->num_dsi_lanes / 1000;
	clkभाग = dsiclk / DIVIDE_BY_3 * tc->lvds_link;
	byteclk = dsiclk / 4;
	t1 = hactive * (tc->bpc * 3 / 8) / tc->num_dsi_lanes;
	t2 = ((100000 / clkभाग)) * (hactive + hback_porch + hsync_len + hfront_porch) / 1000;
	t3 = ((t2 * byteclk) / 100) - (hactive * (tc->bpc * 3 / 8) /
		tc->num_dsi_lanes);

	vsdelay = (clkभाग * (t1 + t3) / byteclk) - hback_porch - hsync_len - hactive;

	val |= TC358775_VPCTRL_VSDELAY(vsdelay);
	d2l_ग_लिखो(tc->i2c, VPCTRL, val);

	d2l_ग_लिखो(tc->i2c, HTIM1, hसमय1);
	d2l_ग_लिखो(tc->i2c, VTIM1, vसमय1);
	d2l_ग_लिखो(tc->i2c, HTIM2, hसमय2);
	d2l_ग_लिखो(tc->i2c, VTIM2, vसमय2);

	d2l_ग_लिखो(tc->i2c, VFUEN, VFUEN_EN);
	d2l_ग_लिखो(tc->i2c, SYSRST, SYS_RST_LCD);
	d2l_ग_लिखो(tc->i2c, LVPHY0, LV_PHY0_PRBS_ON(4) | LV_PHY0_ND(6));

	dev_dbg(tc->dev, "bus_formats %04x bpc %d\n",
		connector->display_info.bus_क्रमmats[0],
		tc->bpc);
	/*
	 * Default hardware रेजिस्टर settings of tc358775 configured
	 * with MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA jeida-24 क्रमmat
	 */
	अगर (connector->display_info.bus_क्रमmats[0] ==
		MEDIA_BUS_FMT_RGB888_1X7X4_SPWG) अणु
		/* VESA-24 */
		d2l_ग_लिखो(tc->i2c, LV_MX0003, LV_MX(LVI_R0, LVI_R1, LVI_R2, LVI_R3));
		d2l_ग_लिखो(tc->i2c, LV_MX0407, LV_MX(LVI_R4, LVI_R7, LVI_R5, LVI_G0));
		d2l_ग_लिखो(tc->i2c, LV_MX0811, LV_MX(LVI_G1, LVI_G2, LVI_G6, LVI_G7));
		d2l_ग_लिखो(tc->i2c, LV_MX1215, LV_MX(LVI_G3, LVI_G4, LVI_G5, LVI_B0));
		d2l_ग_लिखो(tc->i2c, LV_MX1619, LV_MX(LVI_B6, LVI_B7, LVI_B1, LVI_B2));
		d2l_ग_लिखो(tc->i2c, LV_MX2023, LV_MX(LVI_B3, LVI_B4, LVI_B5, LVI_L0));
		d2l_ग_लिखो(tc->i2c, LV_MX2427, LV_MX(LVI_HS, LVI_VS, LVI_DE, LVI_R6));
	पूर्ण अन्यथा अणु /*  MEDIA_BUS_FMT_RGB666_1X7X3_SPWG - JEIDA-18 */
		d2l_ग_लिखो(tc->i2c, LV_MX0003, LV_MX(LVI_R0, LVI_R1, LVI_R2, LVI_R3));
		d2l_ग_लिखो(tc->i2c, LV_MX0407, LV_MX(LVI_R4, LVI_L0, LVI_R5, LVI_G0));
		d2l_ग_लिखो(tc->i2c, LV_MX0811, LV_MX(LVI_G1, LVI_G2, LVI_L0, LVI_L0));
		d2l_ग_लिखो(tc->i2c, LV_MX1215, LV_MX(LVI_G3, LVI_G4, LVI_G5, LVI_B0));
		d2l_ग_लिखो(tc->i2c, LV_MX1619, LV_MX(LVI_L0, LVI_L0, LVI_B1, LVI_B2));
		d2l_ग_लिखो(tc->i2c, LV_MX2023, LV_MX(LVI_B3, LVI_B4, LVI_B5, LVI_L0));
		d2l_ग_लिखो(tc->i2c, LV_MX2427, LV_MX(LVI_HS, LVI_VS, LVI_DE, LVI_L0));
	पूर्ण

	d2l_ग_लिखो(tc->i2c, VFUEN, VFUEN_EN);

	val = LVCFG_LVEN_BIT;
	अगर (tc->lvds_link == DUAL_LINK) अणु
		val |= TC358775_LVCFG_LVDLINK(1);
		val |= TC358775_LVCFG_PCLKDIV(DIVIDE_BY_6);
	पूर्ण अन्यथा अणु
		val |= TC358775_LVCFG_PCLKDIV(DIVIDE_BY_3);
	पूर्ण
	d2l_ग_लिखो(tc->i2c, LVCFG, val);
पूर्ण

अटल क्रमागत drm_mode_status
tc_mode_valid(काष्ठा drm_bridge *bridge,
	      स्थिर काष्ठा drm_display_info *info,
	      स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा tc_data *tc = bridge_to_tc(bridge);

	/*
	 * Maximum pixel घड़ी speed 135MHz क्रम single-link
	 * 270MHz क्रम dual-link
	 */
	अगर ((mode->घड़ी > 135000 && tc->lvds_link == SINGLE_LINK) ||
	    (mode->घड़ी > 270000 && tc->lvds_link == DUAL_LINK))
		वापस MODE_CLOCK_HIGH;

	चयन (info->bus_क्रमmats[0]) अणु
	हाल MEDIA_BUS_FMT_RGB888_1X7X4_SPWG:
	हाल MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA:
		/* RGB888 */
		tc->bpc = 8;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB666_1X7X3_SPWG:
		/* RGB666 */
		tc->bpc = 6;
		अवरोध;
	शेष:
		dev_warn(tc->dev,
			 "unsupported LVDS bus format 0x%04x\n",
			 info->bus_क्रमmats[0]);
		वापस MODE_NOMODE;
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल पूर्णांक tc358775_parse_dt(काष्ठा device_node *np, काष्ठा tc_data *tc)
अणु
	काष्ठा device_node *endpoपूर्णांक;
	काष्ठा device_node *parent;
	काष्ठा device_node *remote;
	काष्ठा property *prop;
	पूर्णांक len = 0;

	/*
	 * To get the data-lanes of dsi, we need to access the dsi0_out of port1
	 *  of dsi0 endpoपूर्णांक from bridge port0 of d2l_in
	 */
	endpoपूर्णांक = of_graph_get_endpoपूर्णांक_by_regs(tc->dev->of_node,
						 TC358775_DSI_IN, -1);
	अगर (endpoपूर्णांक) अणु
		/* dsi0_out node */
		parent = of_graph_get_remote_port_parent(endpoपूर्णांक);
		of_node_put(endpoपूर्णांक);
		अगर (parent) अणु
			/* dsi0 port 1 */
			endpoपूर्णांक = of_graph_get_endpoपूर्णांक_by_regs(parent, 1, -1);
			of_node_put(parent);
			अगर (endpoपूर्णांक) अणु
				prop = of_find_property(endpoपूर्णांक, "data-lanes",
							&len);
				of_node_put(endpoपूर्णांक);
				अगर (!prop) अणु
					dev_err(tc->dev,
						"failed to find data lane\n");
					वापस -EPROBE_DEFER;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	tc->num_dsi_lanes = len / माप(u32);

	अगर (tc->num_dsi_lanes < 1 || tc->num_dsi_lanes > 4)
		वापस -EINVAL;

	tc->host_node = of_graph_get_remote_node(np, 0, 0);
	अगर (!tc->host_node)
		वापस -ENODEV;

	of_node_put(tc->host_node);

	tc->lvds_link = SINGLE_LINK;
	endpoपूर्णांक = of_graph_get_endpoपूर्णांक_by_regs(tc->dev->of_node,
						 TC358775_LVDS_OUT1, -1);
	अगर (endpoपूर्णांक) अणु
		remote = of_graph_get_remote_port_parent(endpoपूर्णांक);
		of_node_put(endpoपूर्णांक);

		अगर (remote) अणु
			अगर (of_device_is_available(remote))
				tc->lvds_link = DUAL_LINK;
			of_node_put(remote);
		पूर्ण
	पूर्ण

	dev_dbg(tc->dev, "no.of dsi lanes: %d\n", tc->num_dsi_lanes);
	dev_dbg(tc->dev, "operating in %d-link mode\n",	tc->lvds_link);

	वापस 0;
पूर्ण

अटल पूर्णांक tc_bridge_attach(काष्ठा drm_bridge *bridge,
			    क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा tc_data *tc = bridge_to_tc(bridge);
	काष्ठा device *dev = &tc->i2c->dev;
	काष्ठा mipi_dsi_host *host;
	काष्ठा mipi_dsi_device *dsi;
	पूर्णांक ret;

	स्थिर काष्ठा mipi_dsi_device_info info = अणु .type = "tc358775",
							.channel = 0,
							.node = शून्य,
						पूर्ण;

	host = of_find_mipi_dsi_host_by_node(tc->host_node);
	अगर (!host) अणु
		dev_err(dev, "failed to find dsi host\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	dsi = mipi_dsi_device_रेजिस्टर_full(host, &info);
	अगर (IS_ERR(dsi)) अणु
		dev_err(dev, "failed to create dsi device\n");
		ret = PTR_ERR(dsi);
		जाओ err_dsi_device;
	पूर्ण

	tc->dsi = dsi;

	dsi->lanes = tc->num_dsi_lanes;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO;

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to attach dsi to host\n");
		जाओ err_dsi_attach;
	पूर्ण

	/* Attach the panel-bridge to the dsi bridge */
	वापस drm_bridge_attach(bridge->encoder, tc->panel_bridge,
				 &tc->bridge, flags);
err_dsi_attach:
	mipi_dsi_device_unरेजिस्टर(dsi);
err_dsi_device:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs tc_bridge_funcs = अणु
	.attach = tc_bridge_attach,
	.pre_enable = tc_bridge_pre_enable,
	.enable = tc_bridge_enable,
	.mode_valid = tc_mode_valid,
	.post_disable = tc_bridge_post_disable,
पूर्ण;

अटल पूर्णांक tc_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा drm_panel *panel;
	काष्ठा tc_data *tc;
	पूर्णांक ret;

	tc = devm_kzalloc(dev, माप(*tc), GFP_KERNEL);
	अगर (!tc)
		वापस -ENOMEM;

	tc->dev = dev;
	tc->i2c = client;

	ret = drm_of_find_panel_or_bridge(dev->of_node, TC358775_LVDS_OUT0,
					  0, &panel, शून्य);
	अगर (ret < 0)
		वापस ret;
	अगर (!panel)
		वापस -ENODEV;

	tc->panel_bridge = devm_drm_panel_bridge_add(dev, panel);
	अगर (IS_ERR(tc->panel_bridge))
		वापस PTR_ERR(tc->panel_bridge);

	ret = tc358775_parse_dt(dev->of_node, tc);
	अगर (ret)
		वापस ret;

	tc->vddio = devm_regulator_get(dev, "vddio-supply");
	अगर (IS_ERR(tc->vddio)) अणु
		ret = PTR_ERR(tc->vddio);
		dev_err(dev, "vddio-supply not found\n");
		वापस ret;
	पूर्ण

	tc->vdd = devm_regulator_get(dev, "vdd-supply");
	अगर (IS_ERR(tc->vdd)) अणु
		ret = PTR_ERR(tc->vdd);
		dev_err(dev, "vdd-supply not found\n");
		वापस ret;
	पूर्ण

	tc->stby_gpio = devm_gpiod_get(dev, "stby", GPIOD_OUT_HIGH);
	अगर (IS_ERR(tc->stby_gpio)) अणु
		ret = PTR_ERR(tc->stby_gpio);
		dev_err(dev, "cannot get stby-gpio %d\n", ret);
		वापस ret;
	पूर्ण

	tc->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(tc->reset_gpio)) अणु
		ret = PTR_ERR(tc->reset_gpio);
		dev_err(dev, "cannot get reset-gpios %d\n", ret);
		वापस ret;
	पूर्ण

	tc->bridge.funcs = &tc_bridge_funcs;
	tc->bridge.of_node = dev->of_node;
	drm_bridge_add(&tc->bridge);

	i2c_set_clientdata(client, tc);

	वापस 0;
पूर्ण

अटल पूर्णांक tc_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tc_data *tc = i2c_get_clientdata(client);

	drm_bridge_हटाओ(&tc->bridge);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tc358775_i2c_ids[] = अणु
	अणु "tc358775", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tc358775_i2c_ids);

अटल स्थिर काष्ठा of_device_id tc358775_of_ids[] = अणु
	अणु .compatible = "toshiba,tc358775", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tc358775_of_ids);

अटल काष्ठा i2c_driver tc358775_driver = अणु
	.driver = अणु
		.name = "tc358775",
		.of_match_table = tc358775_of_ids,
	पूर्ण,
	.id_table = tc358775_i2c_ids,
	.probe = tc_probe,
	.हटाओ	= tc_हटाओ,
पूर्ण;
module_i2c_driver(tc358775_driver);

MODULE_AUTHOR("Vinay Simha BN <simhavcs@gmail.com>");
MODULE_DESCRIPTION("TC358775 DSI/LVDS bridge driver");
MODULE_LICENSE("GPL v2");
