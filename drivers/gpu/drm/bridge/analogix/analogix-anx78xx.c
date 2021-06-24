<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2016, Analogix Semiconductor.
 *
 * Based on anx7808 driver obtained from chromeos with copyright:
 * Copyright(c) 2013, Google Inc.
 */
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/types.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "analogix-anx78xx.h"

#घोषणा I2C_NUM_ADDRESSES	5
#घोषणा I2C_IDX_TX_P0		0
#घोषणा I2C_IDX_TX_P1		1
#घोषणा I2C_IDX_TX_P2		2
#घोषणा I2C_IDX_RX_P0		3
#घोषणा I2C_IDX_RX_P1		4

#घोषणा XTAL_CLK		270 /* 27M */

अटल स्थिर u8 anx7808_i2c_addresses[] = अणु
	[I2C_IDX_TX_P0] = 0x78,
	[I2C_IDX_TX_P1] = 0x7a,
	[I2C_IDX_TX_P2] = 0x72,
	[I2C_IDX_RX_P0] = 0x7e,
	[I2C_IDX_RX_P1] = 0x80,
पूर्ण;

अटल स्थिर u8 anx781x_i2c_addresses[] = अणु
	[I2C_IDX_TX_P0] = 0x70,
	[I2C_IDX_TX_P1] = 0x7a,
	[I2C_IDX_TX_P2] = 0x72,
	[I2C_IDX_RX_P0] = 0x7e,
	[I2C_IDX_RX_P1] = 0x80,
पूर्ण;

काष्ठा anx78xx_platक्रमm_data अणु
	काष्ठा regulator *dvdd10;
	काष्ठा gpio_desc *gpiod_hpd;
	काष्ठा gpio_desc *gpiod_pd;
	काष्ठा gpio_desc *gpiod_reset;

	पूर्णांक hpd_irq;
	पूर्णांक पूर्णांकp_irq;
पूर्ण;

काष्ठा anx78xx अणु
	काष्ठा drm_dp_aux aux;
	काष्ठा drm_bridge bridge;
	काष्ठा i2c_client *client;
	काष्ठा edid *edid;
	काष्ठा drm_connector connector;
	काष्ठा anx78xx_platक्रमm_data pdata;
	काष्ठा mutex lock;

	/*
	 * I2C Slave addresses of ANX7814 are mapped as TX_P0, TX_P1, TX_P2,
	 * RX_P0 and RX_P1.
	 */
	काष्ठा i2c_client *i2c_dummy[I2C_NUM_ADDRESSES];
	काष्ठा regmap *map[I2C_NUM_ADDRESSES];

	u16 chipid;
	u8 dpcd[DP_RECEIVER_CAP_SIZE];

	bool घातered;
पूर्ण;

अटल अंतरभूत काष्ठा anx78xx *connector_to_anx78xx(काष्ठा drm_connector *c)
अणु
	वापस container_of(c, काष्ठा anx78xx, connector);
पूर्ण

अटल अंतरभूत काष्ठा anx78xx *bridge_to_anx78xx(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा anx78xx, bridge);
पूर्ण

अटल पूर्णांक anx78xx_set_bits(काष्ठा regmap *map, u8 reg, u8 mask)
अणु
	वापस regmap_update_bits(map, reg, mask, mask);
पूर्ण

अटल पूर्णांक anx78xx_clear_bits(काष्ठा regmap *map, u8 reg, u8 mask)
अणु
	वापस regmap_update_bits(map, reg, mask, 0);
पूर्ण

अटल sमाप_प्रकार anx78xx_aux_transfer(काष्ठा drm_dp_aux *aux,
				    काष्ठा drm_dp_aux_msg *msg)
अणु
	काष्ठा anx78xx *anx78xx = container_of(aux, काष्ठा anx78xx, aux);
	वापस anx_dp_aux_transfer(anx78xx->map[I2C_IDX_TX_P0], msg);
पूर्ण

अटल पूर्णांक anx78xx_set_hpd(काष्ठा anx78xx *anx78xx)
अणु
	पूर्णांक err;

	err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_RX_P0],
				 SP_TMDS_CTRL_BASE + 7, SP_PD_RT);
	अगर (err)
		वापस err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P2], SP_VID_CTRL3_REG,
			       SP_HPD_OUT);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक anx78xx_clear_hpd(काष्ठा anx78xx *anx78xx)
अणु
	पूर्णांक err;

	err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_TX_P2], SP_VID_CTRL3_REG,
				 SP_HPD_OUT);
	अगर (err)
		वापस err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_RX_P0],
			       SP_TMDS_CTRL_BASE + 7, SP_PD_RT);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reg_sequence पंचांगds_phy_initialization[] = अणु
	अणु SP_TMDS_CTRL_BASE +  1, 0x90 पूर्ण,
	अणु SP_TMDS_CTRL_BASE +  2, 0xa9 पूर्ण,
	अणु SP_TMDS_CTRL_BASE +  6, 0x92 पूर्ण,
	अणु SP_TMDS_CTRL_BASE +  7, 0x80 पूर्ण,
	अणु SP_TMDS_CTRL_BASE + 20, 0xf2 पूर्ण,
	अणु SP_TMDS_CTRL_BASE + 22, 0xc4 पूर्ण,
	अणु SP_TMDS_CTRL_BASE + 23, 0x18 पूर्ण,
पूर्ण;

अटल पूर्णांक anx78xx_rx_initialization(काष्ठा anx78xx *anx78xx)
अणु
	पूर्णांक err;

	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_RX_P0], SP_HDMI_MUTE_CTRL_REG,
			   SP_AUD_MUTE | SP_VID_MUTE);
	अगर (err)
		वापस err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_RX_P0], SP_CHIP_CTRL_REG,
			       SP_MAN_HDMI5V_DET | SP_PLLLOCK_CKDT_EN |
			       SP_DIGITAL_CKDT_EN);
	अगर (err)
		वापस err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_RX_P0],
			       SP_SOFTWARE_RESET1_REG, SP_HDCP_MAN_RST |
			       SP_SW_MAN_RST | SP_TMDS_RST | SP_VIDEO_RST);
	अगर (err)
		वापस err;

	err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_RX_P0],
				 SP_SOFTWARE_RESET1_REG, SP_HDCP_MAN_RST |
				 SP_SW_MAN_RST | SP_TMDS_RST | SP_VIDEO_RST);
	अगर (err)
		वापस err;

	/* Sync detect change, GP set mute */
	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_RX_P0],
			       SP_AUD_EXCEPTION_ENABLE_BASE + 1, BIT(5) |
			       BIT(6));
	अगर (err)
		वापस err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_RX_P0],
			       SP_AUD_EXCEPTION_ENABLE_BASE + 3,
			       SP_AEC_EN21);
	अगर (err)
		वापस err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_RX_P0], SP_AUDVID_CTRL_REG,
			       SP_AVC_EN | SP_AAC_OE | SP_AAC_EN);
	अगर (err)
		वापस err;

	err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_RX_P0],
				 SP_SYSTEM_POWER_DOWN1_REG, SP_PWDN_CTRL);
	अगर (err)
		वापस err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_RX_P0],
			       SP_VID_DATA_RANGE_CTRL_REG, SP_R2Y_INPUT_LIMIT);
	अगर (err)
		वापस err;

	/* Enable DDC stretch */
	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P0],
			   SP_DP_EXTRA_I2C_DEV_ADDR_REG, SP_I2C_EXTRA_ADDR);
	अगर (err)
		वापस err;

	/* TMDS phy initialization */
	err = regmap_multi_reg_ग_लिखो(anx78xx->map[I2C_IDX_RX_P0],
				     पंचांगds_phy_initialization,
				     ARRAY_SIZE(पंचांगds_phy_initialization));
	अगर (err)
		वापस err;

	err = anx78xx_clear_hpd(anx78xx);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल स्थिर u8 dp_tx_output_precise_tune_bits[20] = अणु
	0x01, 0x03, 0x07, 0x7f, 0x71, 0x6b, 0x7f,
	0x73, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00,
	0x0c, 0x42, 0x1e, 0x3e, 0x72, 0x7e,
पूर्ण;

अटल पूर्णांक anx78xx_link_phy_initialization(काष्ठा anx78xx *anx78xx)
अणु
	पूर्णांक err;

	/*
	 * REVISIT : It is writing to a RESERVED bits in Analog Control 0
	 * रेजिस्टर.
	 */
	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P2], SP_ANALOG_CTRL0_REG,
			   0x02);
	अगर (err)
		वापस err;

	/*
	 * Write DP TX output emphasis precise tune bits.
	 */
	err = regmap_bulk_ग_लिखो(anx78xx->map[I2C_IDX_TX_P1],
				SP_DP_TX_LT_CTRL0_REG,
				dp_tx_output_precise_tune_bits,
				ARRAY_SIZE(dp_tx_output_precise_tune_bits));

	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक anx78xx_xtal_clk_sel(काष्ठा anx78xx *anx78xx)
अणु
	अचिन्हित पूर्णांक value;
	पूर्णांक err;

	err = regmap_update_bits(anx78xx->map[I2C_IDX_TX_P2],
				 SP_ANALOG_DEBUG2_REG,
				 SP_XTAL_FRQ | SP_FORCE_SW_OFF_BYPASS,
				 SP_XTAL_FRQ_27M);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P0], SP_DP_AUX_CH_CTRL3_REG,
			   XTAL_CLK & SP_WAIT_COUNTER_7_0_MASK);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P0], SP_DP_AUX_CH_CTRL4_REG,
			   ((XTAL_CLK & 0xff00) >> 2) | (XTAL_CLK / 10));
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P0],
			   SP_I2C_GEN_10US_TIMER0_REG, XTAL_CLK & 0xff);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P0],
			   SP_I2C_GEN_10US_TIMER1_REG,
			   (XTAL_CLK & 0xff00) >> 8);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P0], SP_AUX_MISC_CTRL_REG,
			   XTAL_CLK / 10 - 1);
	अगर (err)
		वापस err;

	err = regmap_पढ़ो(anx78xx->map[I2C_IDX_RX_P0],
			  SP_HDMI_US_TIMER_CTRL_REG,
			  &value);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_RX_P0],
			   SP_HDMI_US_TIMER_CTRL_REG,
			   (value & SP_MS_TIMER_MARGIN_10_8_MASK) |
			   ((((XTAL_CLK / 10) >> 1) - 2) << 3));
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reg_sequence otp_key_protect[] = अणु
	अणु SP_OTP_KEY_PROTECT1_REG, SP_OTP_PSW1 पूर्ण,
	अणु SP_OTP_KEY_PROTECT2_REG, SP_OTP_PSW2 पूर्ण,
	अणु SP_OTP_KEY_PROTECT3_REG, SP_OTP_PSW3 पूर्ण,
पूर्ण;

अटल पूर्णांक anx78xx_tx_initialization(काष्ठा anx78xx *anx78xx)
अणु
	पूर्णांक err;

	/* Set terminal resistor to 50 ohm */
	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P0], SP_DP_AUX_CH_CTRL2_REG,
			   0x30);
	अगर (err)
		वापस err;

	/* Enable aux द्विगुन dअगरf output */
	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_DP_AUX_CH_CTRL2_REG, 0x08);
	अगर (err)
		वापस err;

	err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_TX_P0],
				 SP_DP_HDCP_CTRL_REG, SP_AUTO_EN |
				 SP_AUTO_START);
	अगर (err)
		वापस err;

	err = regmap_multi_reg_ग_लिखो(anx78xx->map[I2C_IDX_TX_P0],
				     otp_key_protect,
				     ARRAY_SIZE(otp_key_protect));
	अगर (err)
		वापस err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_HDCP_KEY_COMMAND_REG, SP_DISABLE_SYNC_HDCP);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P2], SP_VID_CTRL8_REG,
			   SP_VID_VRES_TH);
	अगर (err)
		वापस err;

	/*
	 * DP HDCP स्वतः authentication रुको समयr (when करोwnstream starts to
	 * auth, DP side will रुको क्रम this period then करो auth स्वतःmatically)
	 */
	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P0], SP_HDCP_AUTO_TIMER_REG,
			   0x00);
	अगर (err)
		वापस err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_DP_HDCP_CTRL_REG, SP_LINK_POLLING);
	अगर (err)
		वापस err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_DP_LINK_DEBUG_CTRL_REG, SP_M_VID_DEBUG);
	अगर (err)
		वापस err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P2],
			       SP_ANALOG_DEBUG2_REG, SP_POWERON_TIME_1P5MS);
	अगर (err)
		वापस err;

	err = anx78xx_xtal_clk_sel(anx78xx);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P0], SP_AUX_DEFER_CTRL_REG,
			   SP_DEFER_CTRL_EN | 0x0c);
	अगर (err)
		वापस err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_DP_POLLING_CTRL_REG,
			       SP_AUTO_POLLING_DISABLE);
	अगर (err)
		वापस err;

	/*
	 * Short the link पूर्णांकegrity check समयr to speed up bstatus
	 * polling क्रम HDCP CTS item 1A-07
	 */
	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P0],
			   SP_HDCP_LINK_CHECK_TIMER_REG, 0x1d);
	अगर (err)
		वापस err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_DP_MISC_CTRL_REG, SP_EQ_TRAINING_LOOP);
	अगर (err)
		वापस err;

	/* Power करोwn the मुख्य link by शेष */
	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_DP_ANALOG_POWER_DOWN_REG, SP_CH0_PD);
	अगर (err)
		वापस err;

	err = anx78xx_link_phy_initialization(anx78xx);
	अगर (err)
		वापस err;

	/* Gen m_clk with करोwnspपढ़ोing */
	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_DP_M_CALCULATION_CTRL_REG, SP_M_GEN_CLK_SEL);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक anx78xx_enable_पूर्णांकerrupts(काष्ठा anx78xx *anx78xx)
अणु
	पूर्णांक err;

	/*
	 * BIT0: INT pin निश्चितion polarity: 1 = निश्चित high
	 * BIT1: INT pin output type: 0 = push/pull
	 */
	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P2], SP_INT_CTRL_REG, 0x01);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P2],
			   SP_COMMON_INT_MASK4_REG, SP_HPD_LOST | SP_HPD_PLUG);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P2], SP_DP_INT_MASK1_REG,
			   SP_TRAINING_FINISH);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_RX_P0], SP_INT_MASK1_REG,
			   SP_CKDT_CHG | SP_SCDT_CHG);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम anx78xx_घातeron(काष्ठा anx78xx *anx78xx)
अणु
	काष्ठा anx78xx_platक्रमm_data *pdata = &anx78xx->pdata;
	पूर्णांक err;

	अगर (WARN_ON(anx78xx->घातered))
		वापस;

	अगर (pdata->dvdd10) अणु
		err = regulator_enable(pdata->dvdd10);
		अगर (err) अणु
			DRM_ERROR("Failed to enable DVDD10 regulator: %d\n",
				  err);
			वापस;
		पूर्ण

		usleep_range(1000, 2000);
	पूर्ण

	gpiod_set_value_cansleep(pdata->gpiod_reset, 1);
	usleep_range(1000, 2000);

	gpiod_set_value_cansleep(pdata->gpiod_pd, 0);
	usleep_range(1000, 2000);

	gpiod_set_value_cansleep(pdata->gpiod_reset, 0);

	/* Power on रेजिस्टरs module */
	anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P2], SP_POWERDOWN_CTRL_REG,
			 SP_HDCP_PD | SP_AUDIO_PD | SP_VIDEO_PD | SP_LINK_PD);
	anx78xx_clear_bits(anx78xx->map[I2C_IDX_TX_P2], SP_POWERDOWN_CTRL_REG,
			   SP_REGISTER_PD | SP_TOTAL_PD);

	anx78xx->घातered = true;
पूर्ण

अटल व्योम anx78xx_घातeroff(काष्ठा anx78xx *anx78xx)
अणु
	काष्ठा anx78xx_platक्रमm_data *pdata = &anx78xx->pdata;
	पूर्णांक err;

	अगर (WARN_ON(!anx78xx->घातered))
		वापस;

	gpiod_set_value_cansleep(pdata->gpiod_reset, 1);
	usleep_range(1000, 2000);

	gpiod_set_value_cansleep(pdata->gpiod_pd, 1);
	usleep_range(1000, 2000);

	अगर (pdata->dvdd10) अणु
		err = regulator_disable(pdata->dvdd10);
		अगर (err) अणु
			DRM_ERROR("Failed to disable DVDD10 regulator: %d\n",
				  err);
			वापस;
		पूर्ण

		usleep_range(1000, 2000);
	पूर्ण

	anx78xx->घातered = false;
पूर्ण

अटल पूर्णांक anx78xx_start(काष्ठा anx78xx *anx78xx)
अणु
	पूर्णांक err;

	/* Power on all modules */
	err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_TX_P2],
				 SP_POWERDOWN_CTRL_REG,
				 SP_HDCP_PD | SP_AUDIO_PD | SP_VIDEO_PD |
				 SP_LINK_PD);

	err = anx78xx_enable_पूर्णांकerrupts(anx78xx);
	अगर (err) अणु
		DRM_ERROR("Failed to enable interrupts: %d\n", err);
		जाओ err_घातeroff;
	पूर्ण

	err = anx78xx_rx_initialization(anx78xx);
	अगर (err) अणु
		DRM_ERROR("Failed receiver initialization: %d\n", err);
		जाओ err_घातeroff;
	पूर्ण

	err = anx78xx_tx_initialization(anx78xx);
	अगर (err) अणु
		DRM_ERROR("Failed transmitter initialization: %d\n", err);
		जाओ err_घातeroff;
	पूर्ण

	/*
	 * This delay seems to help keep the hardware in a good state. Without
	 * it, there are बार where it fails silently.
	 */
	usleep_range(10000, 15000);

	वापस 0;

err_घातeroff:
	DRM_ERROR("Failed SlimPort transmitter initialization: %d\n", err);
	anx78xx_घातeroff(anx78xx);

	वापस err;
पूर्ण

अटल पूर्णांक anx78xx_init_pdata(काष्ठा anx78xx *anx78xx)
अणु
	काष्ठा anx78xx_platक्रमm_data *pdata = &anx78xx->pdata;
	काष्ठा device *dev = &anx78xx->client->dev;

	/* 1.0V digital core घातer regulator  */
	pdata->dvdd10 = devm_regulator_get(dev, "dvdd10");
	अगर (IS_ERR(pdata->dvdd10)) अणु
		अगर (PTR_ERR(pdata->dvdd10) != -EPROBE_DEFER)
			DRM_ERROR("DVDD10 regulator not found\n");

		वापस PTR_ERR(pdata->dvdd10);
	पूर्ण

	/* GPIO क्रम HPD */
	pdata->gpiod_hpd = devm_gpiod_get(dev, "hpd", GPIOD_IN);
	अगर (IS_ERR(pdata->gpiod_hpd))
		वापस PTR_ERR(pdata->gpiod_hpd);

	/* GPIO क्रम chip घातer करोwn */
	pdata->gpiod_pd = devm_gpiod_get(dev, "pd", GPIOD_OUT_HIGH);
	अगर (IS_ERR(pdata->gpiod_pd))
		वापस PTR_ERR(pdata->gpiod_pd);

	/* GPIO क्रम chip reset */
	pdata->gpiod_reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);

	वापस PTR_ERR_OR_ZERO(pdata->gpiod_reset);
पूर्ण

अटल पूर्णांक anx78xx_dp_link_training(काष्ठा anx78xx *anx78xx)
अणु
	u8 dp_bw, dpcd[2];
	पूर्णांक err;

	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_RX_P0], SP_HDMI_MUTE_CTRL_REG,
			   0x0);
	अगर (err)
		वापस err;

	err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_TX_P2],
				 SP_POWERDOWN_CTRL_REG,
				 SP_TOTAL_PD);
	अगर (err)
		वापस err;

	err = drm_dp_dpcd_पढ़ोb(&anx78xx->aux, DP_MAX_LINK_RATE, &dp_bw);
	अगर (err < 0)
		वापस err;

	चयन (dp_bw) अणु
	हाल DP_LINK_BW_1_62:
	हाल DP_LINK_BW_2_7:
	हाल DP_LINK_BW_5_4:
		अवरोध;

	शेष:
		DRM_DEBUG_KMS("DP bandwidth (%#02x) not supported\n", dp_bw);
		वापस -EINVAL;
	पूर्ण

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P2], SP_VID_CTRL1_REG,
			       SP_VIDEO_MUTE);
	अगर (err)
		वापस err;

	err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_TX_P2],
				 SP_VID_CTRL1_REG, SP_VIDEO_EN);
	अगर (err)
		वापस err;

	/* Get DPCD info */
	err = drm_dp_dpcd_पढ़ो(&anx78xx->aux, DP_DPCD_REV,
			       &anx78xx->dpcd, DP_RECEIVER_CAP_SIZE);
	अगर (err < 0) अणु
		DRM_ERROR("Failed to read DPCD: %d\n", err);
		वापस err;
	पूर्ण

	/* Clear channel x SERDES घातer करोwn */
	err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_TX_P0],
				 SP_DP_ANALOG_POWER_DOWN_REG, SP_CH0_PD);
	अगर (err)
		वापस err;

	/*
	 * Power up the sink (DP_SET_POWER रेजिस्टर is only available on DPCD
	 * v1.1 and later).
	 */
	अगर (anx78xx->dpcd[DP_DPCD_REV] >= 0x11) अणु
		err = drm_dp_dpcd_पढ़ोb(&anx78xx->aux, DP_SET_POWER, &dpcd[0]);
		अगर (err < 0) अणु
			DRM_ERROR("Failed to read DP_SET_POWER register: %d\n",
				  err);
			वापस err;
		पूर्ण

		dpcd[0] &= ~DP_SET_POWER_MASK;
		dpcd[0] |= DP_SET_POWER_D0;

		err = drm_dp_dpcd_ग_लिखोb(&anx78xx->aux, DP_SET_POWER, dpcd[0]);
		अगर (err < 0) अणु
			DRM_ERROR("Failed to power up DisplayPort link: %d\n",
				  err);
			वापस err;
		पूर्ण

		/*
		 * According to the DP 1.1 specअगरication, a "Sink Device must
		 * निकास the घातer saving state within 1 ms" (Section 2.5.3.1,
		 * Table 5-52, "Sink Control Field" (रेजिस्टर 0x600).
		 */
		usleep_range(1000, 2000);
	पूर्ण

	/* Possibly enable करोwnspपढ़ो on the sink */
	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P0],
			   SP_DP_DOWNSPREAD_CTRL1_REG, 0);
	अगर (err)
		वापस err;

	अगर (anx78xx->dpcd[DP_MAX_DOWNSPREAD] & DP_MAX_DOWNSPREAD_0_5) अणु
		DRM_DEBUG("Enable downspread on the sink\n");
		/* 4000PPM */
		err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P0],
				   SP_DP_DOWNSPREAD_CTRL1_REG, 8);
		अगर (err)
			वापस err;

		err = drm_dp_dpcd_ग_लिखोb(&anx78xx->aux, DP_DOWNSPREAD_CTRL,
					 DP_SPREAD_AMP_0_5);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अणु
		err = drm_dp_dpcd_ग_लिखोb(&anx78xx->aux, DP_DOWNSPREAD_CTRL, 0);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* Set the lane count and the link rate on the sink */
	अगर (drm_dp_enhanced_frame_cap(anx78xx->dpcd))
		err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
				       SP_DP_SYSTEM_CTRL_BASE + 4,
				       SP_ENHANCED_MODE);
	अन्यथा
		err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_TX_P0],
					 SP_DP_SYSTEM_CTRL_BASE + 4,
					 SP_ENHANCED_MODE);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P0],
			   SP_DP_MAIN_LINK_BW_SET_REG,
			   anx78xx->dpcd[DP_MAX_LINK_RATE]);
	अगर (err)
		वापस err;

	dpcd[1] = drm_dp_max_lane_count(anx78xx->dpcd);

	अगर (drm_dp_enhanced_frame_cap(anx78xx->dpcd))
		dpcd[1] |= DP_LANE_COUNT_ENHANCED_FRAME_EN;

	err = drm_dp_dpcd_ग_लिखो(&anx78xx->aux, DP_LINK_BW_SET, dpcd,
				माप(dpcd));
	अगर (err < 0) अणु
		DRM_ERROR("Failed to configure link: %d\n", err);
		वापस err;
	पूर्ण

	/* Start training on the source */
	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P0], SP_DP_LT_CTRL_REG,
			   SP_LT_EN);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक anx78xx_config_dp_output(काष्ठा anx78xx *anx78xx)
अणु
	पूर्णांक err;

	err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_TX_P2], SP_VID_CTRL1_REG,
				 SP_VIDEO_MUTE);
	अगर (err)
		वापस err;

	/* Enable DP output */
	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P2], SP_VID_CTRL1_REG,
			       SP_VIDEO_EN);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक anx78xx_send_video_infoframe(काष्ठा anx78xx *anx78xx,
					काष्ठा hdmi_avi_infoframe *frame)
अणु
	u8 buffer[HDMI_INFOFRAME_HEADER_SIZE + HDMI_AVI_INFOFRAME_SIZE];
	पूर्णांक err;

	err = hdmi_avi_infoframe_pack(frame, buffer, माप(buffer));
	अगर (err < 0) अणु
		DRM_ERROR("Failed to pack AVI infoframe: %d\n", err);
		वापस err;
	पूर्ण

	err = anx78xx_clear_bits(anx78xx->map[I2C_IDX_TX_P0],
				 SP_PACKET_SEND_CTRL_REG, SP_AVI_IF_EN);
	अगर (err)
		वापस err;

	err = regmap_bulk_ग_लिखो(anx78xx->map[I2C_IDX_TX_P2],
				SP_INFOFRAME_AVI_DB1_REG, buffer,
				frame->length);
	अगर (err)
		वापस err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_PACKET_SEND_CTRL_REG, SP_AVI_IF_UD);
	अगर (err)
		वापस err;

	err = anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P0],
			       SP_PACKET_SEND_CTRL_REG, SP_AVI_IF_EN);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक anx78xx_get_करोwnstream_info(काष्ठा anx78xx *anx78xx)
अणु
	u8 value;
	पूर्णांक err;

	err = drm_dp_dpcd_पढ़ोb(&anx78xx->aux, DP_SINK_COUNT, &value);
	अगर (err < 0) अणु
		DRM_ERROR("Get sink count failed %d\n", err);
		वापस err;
	पूर्ण

	अगर (!DP_GET_SINK_COUNT(value)) अणु
		DRM_ERROR("Downstream disconnected\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक anx78xx_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा anx78xx *anx78xx = connector_to_anx78xx(connector);
	पूर्णांक err, num_modes = 0;

	अगर (WARN_ON(!anx78xx->घातered))
		वापस 0;

	अगर (anx78xx->edid)
		वापस drm_add_edid_modes(connector, anx78xx->edid);

	mutex_lock(&anx78xx->lock);

	err = anx78xx_get_करोwnstream_info(anx78xx);
	अगर (err) अणु
		DRM_ERROR("Failed to get downstream info: %d\n", err);
		जाओ unlock;
	पूर्ण

	anx78xx->edid = drm_get_edid(connector, &anx78xx->aux.ddc);
	अगर (!anx78xx->edid) अणु
		DRM_ERROR("Failed to read EDID\n");
		जाओ unlock;
	पूर्ण

	err = drm_connector_update_edid_property(connector,
						 anx78xx->edid);
	अगर (err) अणु
		DRM_ERROR("Failed to update EDID property: %d\n", err);
		जाओ unlock;
	पूर्ण

	num_modes = drm_add_edid_modes(connector, anx78xx->edid);

unlock:
	mutex_unlock(&anx78xx->lock);

	वापस num_modes;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs anx78xx_connector_helper_funcs = अणु
	.get_modes = anx78xx_get_modes,
पूर्ण;

अटल क्रमागत drm_connector_status anx78xx_detect(काष्ठा drm_connector *connector,
						bool क्रमce)
अणु
	काष्ठा anx78xx *anx78xx = connector_to_anx78xx(connector);

	अगर (!gpiod_get_value(anx78xx->pdata.gpiod_hpd))
		वापस connector_status_disconnected;

	वापस connector_status_connected;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs anx78xx_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.detect = anx78xx_detect,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक anx78xx_bridge_attach(काष्ठा drm_bridge *bridge,
				 क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा anx78xx *anx78xx = bridge_to_anx78xx(bridge);
	पूर्णांक err;

	अगर (flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR) अणु
		DRM_ERROR("Fix bridge driver to make connector optional!");
		वापस -EINVAL;
	पूर्ण

	अगर (!bridge->encoder) अणु
		DRM_ERROR("Parent encoder object not found");
		वापस -ENODEV;
	पूर्ण

	/* Register aux channel */
	anx78xx->aux.name = "DP-AUX";
	anx78xx->aux.dev = &anx78xx->client->dev;
	anx78xx->aux.transfer = anx78xx_aux_transfer;

	err = drm_dp_aux_रेजिस्टर(&anx78xx->aux);
	अगर (err < 0) अणु
		DRM_ERROR("Failed to register aux channel: %d\n", err);
		वापस err;
	पूर्ण

	err = drm_connector_init(bridge->dev, &anx78xx->connector,
				 &anx78xx_connector_funcs,
				 DRM_MODE_CONNECTOR_DisplayPort);
	अगर (err) अणु
		DRM_ERROR("Failed to initialize connector: %d\n", err);
		जाओ aux_unरेजिस्टर;
	पूर्ण

	drm_connector_helper_add(&anx78xx->connector,
				 &anx78xx_connector_helper_funcs);

	anx78xx->connector.polled = DRM_CONNECTOR_POLL_HPD;

	err = drm_connector_attach_encoder(&anx78xx->connector,
					   bridge->encoder);
	अगर (err) अणु
		DRM_ERROR("Failed to link up connector to encoder: %d\n", err);
		जाओ connector_cleanup;
	पूर्ण

	err = drm_connector_रेजिस्टर(&anx78xx->connector);
	अगर (err) अणु
		DRM_ERROR("Failed to register connector: %d\n", err);
		जाओ connector_cleanup;
	पूर्ण

	वापस 0;
connector_cleanup:
	drm_connector_cleanup(&anx78xx->connector);
aux_unरेजिस्टर:
	drm_dp_aux_unरेजिस्टर(&anx78xx->aux);
	वापस err;
पूर्ण

अटल व्योम anx78xx_bridge_detach(काष्ठा drm_bridge *bridge)
अणु
	drm_dp_aux_unरेजिस्टर(&bridge_to_anx78xx(bridge)->aux);
पूर्ण

अटल क्रमागत drm_mode_status
anx78xx_bridge_mode_valid(काष्ठा drm_bridge *bridge,
			  स्थिर काष्ठा drm_display_info *info,
			  स्थिर काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		वापस MODE_NO_INTERLACE;

	/* Max 1200p at 5.4 Ghz, one lane */
	अगर (mode->घड़ी > 154000)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल व्योम anx78xx_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा anx78xx *anx78xx = bridge_to_anx78xx(bridge);

	/* Power off all modules except configuration रेजिस्टरs access */
	anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P2], SP_POWERDOWN_CTRL_REG,
			 SP_HDCP_PD | SP_AUDIO_PD | SP_VIDEO_PD | SP_LINK_PD);
पूर्ण

अटल व्योम anx78xx_bridge_mode_set(काष्ठा drm_bridge *bridge,
				स्थिर काष्ठा drm_display_mode *mode,
				स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा anx78xx *anx78xx = bridge_to_anx78xx(bridge);
	काष्ठा hdmi_avi_infoframe frame;
	पूर्णांक err;

	अगर (WARN_ON(!anx78xx->घातered))
		वापस;

	mutex_lock(&anx78xx->lock);

	err = drm_hdmi_avi_infoframe_from_display_mode(&frame,
						       &anx78xx->connector,
						       adjusted_mode);
	अगर (err) अणु
		DRM_ERROR("Failed to setup AVI infoframe: %d\n", err);
		जाओ unlock;
	पूर्ण

	err = anx78xx_send_video_infoframe(anx78xx, &frame);
	अगर (err)
		DRM_ERROR("Failed to send AVI infoframe: %d\n", err);

unlock:
	mutex_unlock(&anx78xx->lock);
पूर्ण

अटल व्योम anx78xx_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा anx78xx *anx78xx = bridge_to_anx78xx(bridge);
	पूर्णांक err;

	err = anx78xx_start(anx78xx);
	अगर (err) अणु
		DRM_ERROR("Failed to initialize: %d\n", err);
		वापस;
	पूर्ण

	err = anx78xx_set_hpd(anx78xx);
	अगर (err)
		DRM_ERROR("Failed to set HPD: %d\n", err);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs anx78xx_bridge_funcs = अणु
	.attach = anx78xx_bridge_attach,
	.detach = anx78xx_bridge_detach,
	.mode_valid = anx78xx_bridge_mode_valid,
	.disable = anx78xx_bridge_disable,
	.mode_set = anx78xx_bridge_mode_set,
	.enable = anx78xx_bridge_enable,
पूर्ण;

अटल irqवापस_t anx78xx_hpd_thपढ़ोed_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा anx78xx *anx78xx = data;
	पूर्णांक err;

	अगर (anx78xx->घातered)
		वापस IRQ_HANDLED;

	mutex_lock(&anx78xx->lock);

	/* Cable is pulled, घातer on the chip */
	anx78xx_घातeron(anx78xx);

	err = anx78xx_enable_पूर्णांकerrupts(anx78xx);
	अगर (err)
		DRM_ERROR("Failed to enable interrupts: %d\n", err);

	mutex_unlock(&anx78xx->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक anx78xx_handle_dp_पूर्णांक_1(काष्ठा anx78xx *anx78xx, u8 irq)
अणु
	पूर्णांक err;

	DRM_DEBUG_KMS("Handle DP interrupt 1: %02x\n", irq);

	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P2], SP_DP_INT_STATUS1_REG,
			   irq);
	अगर (err)
		वापस err;

	अगर (irq & SP_TRAINING_FINISH) अणु
		DRM_DEBUG_KMS("IRQ: hardware link training finished\n");
		err = anx78xx_config_dp_output(anx78xx);
	पूर्ण

	वापस err;
पूर्ण

अटल bool anx78xx_handle_common_पूर्णांक_4(काष्ठा anx78xx *anx78xx, u8 irq)
अणु
	bool event = false;
	पूर्णांक err;

	DRM_DEBUG_KMS("Handle common interrupt 4: %02x\n", irq);

	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_TX_P2],
			   SP_COMMON_INT_STATUS4_REG, irq);
	अगर (err) अणु
		DRM_ERROR("Failed to write SP_COMMON_INT_STATUS4 %d\n", err);
		वापस event;
	पूर्ण

	अगर (irq & SP_HPD_LOST) अणु
		DRM_DEBUG_KMS("IRQ: Hot plug detect - cable is pulled out\n");
		event = true;
		anx78xx_घातeroff(anx78xx);
		/* Free cached EDID */
		kमुक्त(anx78xx->edid);
		anx78xx->edid = शून्य;
	पूर्ण अन्यथा अगर (irq & SP_HPD_PLUG) अणु
		DRM_DEBUG_KMS("IRQ: Hot plug detect - cable plug\n");
		event = true;
	पूर्ण

	वापस event;
पूर्ण

अटल व्योम anx78xx_handle_hdmi_पूर्णांक_1(काष्ठा anx78xx *anx78xx, u8 irq)
अणु
	अचिन्हित पूर्णांक value;
	पूर्णांक err;

	DRM_DEBUG_KMS("Handle HDMI interrupt 1: %02x\n", irq);

	err = regmap_ग_लिखो(anx78xx->map[I2C_IDX_RX_P0], SP_INT_STATUS1_REG,
			   irq);
	अगर (err) अणु
		DRM_ERROR("Write HDMI int 1 failed: %d\n", err);
		वापस;
	पूर्ण

	अगर ((irq & SP_CKDT_CHG) || (irq & SP_SCDT_CHG)) अणु
		DRM_DEBUG_KMS("IRQ: HDMI input detected\n");

		err = regmap_पढ़ो(anx78xx->map[I2C_IDX_RX_P0],
				  SP_SYSTEM_STATUS_REG, &value);
		अगर (err) अणु
			DRM_ERROR("Read system status reg failed: %d\n", err);
			वापस;
		पूर्ण

		अगर (!(value & SP_TMDS_CLOCK_DET)) अणु
			DRM_DEBUG_KMS("IRQ: *** Waiting for HDMI clock ***\n");
			वापस;
		पूर्ण

		अगर (!(value & SP_TMDS_DE_DET)) अणु
			DRM_DEBUG_KMS("IRQ: *** Waiting for HDMI signal ***\n");
			वापस;
		पूर्ण

		err = anx78xx_dp_link_training(anx78xx);
		अगर (err)
			DRM_ERROR("Failed to start link training: %d\n", err);
	पूर्ण
पूर्ण

अटल irqवापस_t anx78xx_पूर्णांकp_thपढ़ोed_handler(पूर्णांक unused, व्योम *data)
अणु
	काष्ठा anx78xx *anx78xx = data;
	bool event = false;
	अचिन्हित पूर्णांक irq;
	पूर्णांक err;

	mutex_lock(&anx78xx->lock);

	err = regmap_पढ़ो(anx78xx->map[I2C_IDX_TX_P2], SP_DP_INT_STATUS1_REG,
			  &irq);
	अगर (err) अणु
		DRM_ERROR("Failed to read DP interrupt 1 status: %d\n", err);
		जाओ unlock;
	पूर्ण

	अगर (irq)
		anx78xx_handle_dp_पूर्णांक_1(anx78xx, irq);

	err = regmap_पढ़ो(anx78xx->map[I2C_IDX_TX_P2],
			  SP_COMMON_INT_STATUS4_REG, &irq);
	अगर (err) अणु
		DRM_ERROR("Failed to read common interrupt 4 status: %d\n",
			  err);
		जाओ unlock;
	पूर्ण

	अगर (irq)
		event = anx78xx_handle_common_पूर्णांक_4(anx78xx, irq);

	/* Make sure we are still घातered after handle HPD events */
	अगर (!anx78xx->घातered)
		जाओ unlock;

	err = regmap_पढ़ो(anx78xx->map[I2C_IDX_RX_P0], SP_INT_STATUS1_REG,
			  &irq);
	अगर (err) अणु
		DRM_ERROR("Failed to read HDMI int 1 status: %d\n", err);
		जाओ unlock;
	पूर्ण

	अगर (irq)
		anx78xx_handle_hdmi_पूर्णांक_1(anx78xx, irq);

unlock:
	mutex_unlock(&anx78xx->lock);

	अगर (event)
		drm_helper_hpd_irq_event(anx78xx->connector.dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम unरेजिस्टर_i2c_dummy_clients(काष्ठा anx78xx *anx78xx)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(anx78xx->i2c_dummy); i++)
		i2c_unरेजिस्टर_device(anx78xx->i2c_dummy[i]);
पूर्ण

अटल स्थिर काष्ठा regmap_config anx78xx_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल स्थिर u16 anx78xx_chipid_list[] = अणु
	0x7808,
	0x7812,
	0x7814,
	0x7818,
पूर्ण;

अटल पूर्णांक anx78xx_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा anx78xx *anx78xx;
	काष्ठा anx78xx_platक्रमm_data *pdata;
	अचिन्हित पूर्णांक i, idl, idh, version;
	स्थिर u8 *i2c_addresses;
	bool found = false;
	पूर्णांक err;

	anx78xx = devm_kzalloc(&client->dev, माप(*anx78xx), GFP_KERNEL);
	अगर (!anx78xx)
		वापस -ENOMEM;

	pdata = &anx78xx->pdata;

	mutex_init(&anx78xx->lock);

#अगर IS_ENABLED(CONFIG_OF)
	anx78xx->bridge.of_node = client->dev.of_node;
#पूर्ण_अगर

	anx78xx->client = client;
	i2c_set_clientdata(client, anx78xx);

	err = anx78xx_init_pdata(anx78xx);
	अगर (err) अणु
		अगर (err != -EPROBE_DEFER)
			DRM_ERROR("Failed to initialize pdata: %d\n", err);

		वापस err;
	पूर्ण

	pdata->hpd_irq = gpiod_to_irq(pdata->gpiod_hpd);
	अगर (pdata->hpd_irq < 0) अणु
		DRM_ERROR("Failed to get HPD IRQ: %d\n", pdata->hpd_irq);
		वापस -ENODEV;
	पूर्ण

	pdata->पूर्णांकp_irq = client->irq;
	अगर (!pdata->पूर्णांकp_irq) अणु
		DRM_ERROR("Failed to get CABLE_DET and INTP IRQ\n");
		वापस -ENODEV;
	पूर्ण

	/* Map slave addresses of ANX7814 */
	i2c_addresses = device_get_match_data(&client->dev);
	क्रम (i = 0; i < I2C_NUM_ADDRESSES; i++) अणु
		काष्ठा i2c_client *i2c_dummy;

		i2c_dummy = i2c_new_dummy_device(client->adapter,
						 i2c_addresses[i] >> 1);
		अगर (IS_ERR(i2c_dummy)) अणु
			err = PTR_ERR(i2c_dummy);
			DRM_ERROR("Failed to reserve I2C bus %02x: %d\n",
				  i2c_addresses[i], err);
			जाओ err_unरेजिस्टर_i2c;
		पूर्ण

		anx78xx->i2c_dummy[i] = i2c_dummy;
		anx78xx->map[i] = devm_regmap_init_i2c(anx78xx->i2c_dummy[i],
						       &anx78xx_regmap_config);
		अगर (IS_ERR(anx78xx->map[i])) अणु
			err = PTR_ERR(anx78xx->map[i]);
			DRM_ERROR("Failed regmap initialization %02x\n",
				  i2c_addresses[i]);
			जाओ err_unरेजिस्टर_i2c;
		पूर्ण
	पूर्ण

	/* Look क्रम supported chip ID */
	anx78xx_घातeron(anx78xx);

	err = regmap_पढ़ो(anx78xx->map[I2C_IDX_TX_P2], SP_DEVICE_IDL_REG,
			  &idl);
	अगर (err)
		जाओ err_घातeroff;

	err = regmap_पढ़ो(anx78xx->map[I2C_IDX_TX_P2], SP_DEVICE_IDH_REG,
			  &idh);
	अगर (err)
		जाओ err_घातeroff;

	anx78xx->chipid = (u8)idl | ((u8)idh << 8);

	err = regmap_पढ़ो(anx78xx->map[I2C_IDX_TX_P2], SP_DEVICE_VERSION_REG,
			  &version);
	अगर (err)
		जाओ err_घातeroff;

	क्रम (i = 0; i < ARRAY_SIZE(anx78xx_chipid_list); i++) अणु
		अगर (anx78xx->chipid == anx78xx_chipid_list[i]) अणु
			DRM_INFO("Found ANX%x (ver. %d) SlimPort Transmitter\n",
				 anx78xx->chipid, version);
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		DRM_ERROR("ANX%x (ver. %d) not supported by this driver\n",
			  anx78xx->chipid, version);
		err = -ENODEV;
		जाओ err_घातeroff;
	पूर्ण

	err = devm_request_thपढ़ोed_irq(&client->dev, pdata->hpd_irq, शून्य,
					anx78xx_hpd_thपढ़ोed_handler,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					"anx78xx-hpd", anx78xx);
	अगर (err) अणु
		DRM_ERROR("Failed to request CABLE_DET threaded IRQ: %d\n",
			  err);
		जाओ err_घातeroff;
	पूर्ण

	err = devm_request_thपढ़ोed_irq(&client->dev, pdata->पूर्णांकp_irq, शून्य,
					anx78xx_पूर्णांकp_thपढ़ोed_handler,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					"anx78xx-intp", anx78xx);
	अगर (err) अणु
		DRM_ERROR("Failed to request INTP threaded IRQ: %d\n", err);
		जाओ err_घातeroff;
	पूर्ण

	anx78xx->bridge.funcs = &anx78xx_bridge_funcs;

	drm_bridge_add(&anx78xx->bridge);

	/* If cable is pulled out, just घातeroff and रुको क्रम HPD event */
	अगर (!gpiod_get_value(anx78xx->pdata.gpiod_hpd))
		anx78xx_घातeroff(anx78xx);

	वापस 0;

err_घातeroff:
	anx78xx_घातeroff(anx78xx);

err_unरेजिस्टर_i2c:
	unरेजिस्टर_i2c_dummy_clients(anx78xx);
	वापस err;
पूर्ण

अटल पूर्णांक anx78xx_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा anx78xx *anx78xx = i2c_get_clientdata(client);

	drm_bridge_हटाओ(&anx78xx->bridge);

	unरेजिस्टर_i2c_dummy_clients(anx78xx);

	kमुक्त(anx78xx->edid);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id anx78xx_id[] = अणु
	अणु "anx7814", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, anx78xx_id);

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id anx78xx_match_table[] = अणु
	अणु .compatible = "analogix,anx7808", .data = anx7808_i2c_addresses पूर्ण,
	अणु .compatible = "analogix,anx7812", .data = anx781x_i2c_addresses पूर्ण,
	अणु .compatible = "analogix,anx7814", .data = anx781x_i2c_addresses पूर्ण,
	अणु .compatible = "analogix,anx7818", .data = anx781x_i2c_addresses पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, anx78xx_match_table);
#पूर्ण_अगर

अटल काष्ठा i2c_driver anx78xx_driver = अणु
	.driver = अणु
		   .name = "anx7814",
		   .of_match_table = of_match_ptr(anx78xx_match_table),
		  पूर्ण,
	.probe = anx78xx_i2c_probe,
	.हटाओ = anx78xx_i2c_हटाओ,
	.id_table = anx78xx_id,
पूर्ण;
module_i2c_driver(anx78xx_driver);

MODULE_DESCRIPTION("ANX78xx SlimPort Transmitter driver");
MODULE_AUTHOR("Enric Balletbo i Serra <enric.balletbo@collabora.com>");
MODULE_LICENSE("GPL v2");
