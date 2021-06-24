<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Broadcom
 * Copyright (c) 2014 The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश "vc4_hdmi.h"
#समावेश "vc4_regs.h"
#समावेश "vc4_hdmi_regs.h"

#घोषणा VC4_HDMI_TX_PHY_RESET_CTL_PLL_RESETB	BIT(5)
#घोषणा VC4_HDMI_TX_PHY_RESET_CTL_PLLDIV_RESETB	BIT(4)
#घोषणा VC4_HDMI_TX_PHY_RESET_CTL_TX_CK_RESET	BIT(3)
#घोषणा VC4_HDMI_TX_PHY_RESET_CTL_TX_2_RESET	BIT(2)
#घोषणा VC4_HDMI_TX_PHY_RESET_CTL_TX_1_RESET	BIT(1)
#घोषणा VC4_HDMI_TX_PHY_RESET_CTL_TX_0_RESET	BIT(0)

#घोषणा VC4_HDMI_TX_PHY_POWERDOWN_CTL_RNDGEN_PWRDN	BIT(4)

#घोषणा VC4_HDMI_TX_PHY_CTL_0_PREEMP_2_PREEMP_SHIFT	29
#घोषणा VC4_HDMI_TX_PHY_CTL_0_PREEMP_2_PREEMP_MASK	VC4_MASK(31, 29)
#घोषणा VC4_HDMI_TX_PHY_CTL_0_PREEMP_2_MAINDRV_SHIFT	24
#घोषणा VC4_HDMI_TX_PHY_CTL_0_PREEMP_2_MAINDRV_MASK	VC4_MASK(28, 24)
#घोषणा VC4_HDMI_TX_PHY_CTL_0_PREEMP_1_PREEMP_SHIFT	21
#घोषणा VC4_HDMI_TX_PHY_CTL_0_PREEMP_1_PREEMP_MASK	VC4_MASK(23, 21)
#घोषणा VC4_HDMI_TX_PHY_CTL_0_PREEMP_1_MAINDRV_SHIFT	16
#घोषणा VC4_HDMI_TX_PHY_CTL_0_PREEMP_1_MAINDRV_MASK	VC4_MASK(20, 16)
#घोषणा VC4_HDMI_TX_PHY_CTL_0_PREEMP_0_PREEMP_SHIFT	13
#घोषणा VC4_HDMI_TX_PHY_CTL_0_PREEMP_0_PREEMP_MASK	VC4_MASK(15, 13)
#घोषणा VC4_HDMI_TX_PHY_CTL_0_PREEMP_0_MAINDRV_SHIFT	8
#घोषणा VC4_HDMI_TX_PHY_CTL_0_PREEMP_0_MAINDRV_MASK	VC4_MASK(12, 8)
#घोषणा VC4_HDMI_TX_PHY_CTL_0_PREEMP_CK_PREEMP_SHIFT	5
#घोषणा VC4_HDMI_TX_PHY_CTL_0_PREEMP_CK_PREEMP_MASK	VC4_MASK(7, 5)
#घोषणा VC4_HDMI_TX_PHY_CTL_0_PREEMP_CK_MAINDRV_SHIFT	0
#घोषणा VC4_HDMI_TX_PHY_CTL_0_PREEMP_CK_MAINDRV_MASK	VC4_MASK(4, 0)

#घोषणा VC4_HDMI_TX_PHY_CTL_1_RES_SEL_DATA2_SHIFT	15
#घोषणा VC4_HDMI_TX_PHY_CTL_1_RES_SEL_DATA2_MASK	VC4_MASK(19, 15)
#घोषणा VC4_HDMI_TX_PHY_CTL_1_RES_SEL_DATA1_SHIFT	10
#घोषणा VC4_HDMI_TX_PHY_CTL_1_RES_SEL_DATA1_MASK	VC4_MASK(14, 10)
#घोषणा VC4_HDMI_TX_PHY_CTL_1_RES_SEL_DATA0_SHIFT	5
#घोषणा VC4_HDMI_TX_PHY_CTL_1_RES_SEL_DATA0_MASK	VC4_MASK(9, 5)
#घोषणा VC4_HDMI_TX_PHY_CTL_1_RES_SEL_CK_SHIFT		0
#घोषणा VC4_HDMI_TX_PHY_CTL_1_RES_SEL_CK_MASK		VC4_MASK(4, 0)

#घोषणा VC4_HDMI_TX_PHY_CTL_2_VCO_GAIN_SHIFT		16
#घोषणा VC4_HDMI_TX_PHY_CTL_2_VCO_GAIN_MASK		VC4_MASK(19, 16)
#घोषणा VC4_HDMI_TX_PHY_CTL_2_TERM_RES_SELDATA2_SHIFT	12
#घोषणा VC4_HDMI_TX_PHY_CTL_2_TERM_RES_SELDATA2_MASK	VC4_MASK(15, 12)
#घोषणा VC4_HDMI_TX_PHY_CTL_2_TERM_RES_SELDATA1_SHIFT	8
#घोषणा VC4_HDMI_TX_PHY_CTL_2_TERM_RES_SELDATA1_MASK	VC4_MASK(11, 8)
#घोषणा VC4_HDMI_TX_PHY_CTL_2_TERM_RES_SELDATA0_SHIFT	4
#घोषणा VC4_HDMI_TX_PHY_CTL_2_TERM_RES_SELDATA0_MASK	VC4_MASK(7, 4)
#घोषणा VC4_HDMI_TX_PHY_CTL_2_TERM_RES_SELCK_SHIFT	0
#घोषणा VC4_HDMI_TX_PHY_CTL_2_TERM_RES_SELCK_MASK	VC4_MASK(3, 0)

#घोषणा VC4_HDMI_TX_PHY_CTL_3_RP_SHIFT			17
#घोषणा VC4_HDMI_TX_PHY_CTL_3_RP_MASK			VC4_MASK(19, 17)
#घोषणा VC4_HDMI_TX_PHY_CTL_3_RZ_SHIFT			12
#घोषणा VC4_HDMI_TX_PHY_CTL_3_RZ_MASK			VC4_MASK(16, 12)
#घोषणा VC4_HDMI_TX_PHY_CTL_3_CP1_SHIFT			10
#घोषणा VC4_HDMI_TX_PHY_CTL_3_CP1_MASK			VC4_MASK(11, 10)
#घोषणा VC4_HDMI_TX_PHY_CTL_3_CP_SHIFT			8
#घोषणा VC4_HDMI_TX_PHY_CTL_3_CP_MASK			VC4_MASK(9, 8)
#घोषणा VC4_HDMI_TX_PHY_CTL_3_CZ_SHIFT			6
#घोषणा VC4_HDMI_TX_PHY_CTL_3_CZ_MASK			VC4_MASK(7, 6)
#घोषणा VC4_HDMI_TX_PHY_CTL_3_ICP_SHIFT			0
#घोषणा VC4_HDMI_TX_PHY_CTL_3_ICP_MASK			VC4_MASK(5, 0)

#घोषणा VC4_HDMI_TX_PHY_PLL_CTL_0_MASH11_MODE		BIT(13)
#घोषणा VC4_HDMI_TX_PHY_PLL_CTL_0_VC_RANGE_EN		BIT(12)
#घोषणा VC4_HDMI_TX_PHY_PLL_CTL_0_EMULATE_VC_LOW	BIT(11)
#घोषणा VC4_HDMI_TX_PHY_PLL_CTL_0_EMULATE_VC_HIGH	BIT(10)
#घोषणा VC4_HDMI_TX_PHY_PLL_CTL_0_VCO_SEL_SHIFT		9
#घोषणा VC4_HDMI_TX_PHY_PLL_CTL_0_VCO_SEL_MASK		VC4_MASK(9, 9)
#घोषणा VC4_HDMI_TX_PHY_PLL_CTL_0_VCO_FB_DIV2		BIT(8)
#घोषणा VC4_HDMI_TX_PHY_PLL_CTL_0_VCO_POST_DIV2		BIT(7)
#घोषणा VC4_HDMI_TX_PHY_PLL_CTL_0_VCO_CONT_EN		BIT(6)
#घोषणा VC4_HDMI_TX_PHY_PLL_CTL_0_ENA_VCO_CLK		BIT(5)

#घोषणा VC4_HDMI_TX_PHY_PLL_CTL_1_CPP_SHIFT			16
#घोषणा VC4_HDMI_TX_PHY_PLL_CTL_1_CPP_MASK			VC4_MASK(27, 16)
#घोषणा VC4_HDMI_TX_PHY_PLL_CTL_1_FREQ_DOUBLER_DELAY_SHIFT	14
#घोषणा VC4_HDMI_TX_PHY_PLL_CTL_1_FREQ_DOUBLER_DELAY_MASK	VC4_MASK(15, 14)
#घोषणा VC4_HDMI_TX_PHY_PLL_CTL_1_FREQ_DOUBLER_ENABLE		BIT(13)
#घोषणा VC4_HDMI_TX_PHY_PLL_CTL_1_POST_RST_SEL_SHIFT		11
#घोषणा VC4_HDMI_TX_PHY_PLL_CTL_1_POST_RST_SEL_MASK		VC4_MASK(12, 11)

#घोषणा VC4_HDMI_TX_PHY_CLK_DIV_VCO_SHIFT		8
#घोषणा VC4_HDMI_TX_PHY_CLK_DIV_VCO_MASK		VC4_MASK(15, 8)

#घोषणा VC4_HDMI_TX_PHY_PLL_CFG_PDIV_SHIFT		0
#घोषणा VC4_HDMI_TX_PHY_PLL_CFG_PDIV_MASK		VC4_MASK(3, 0)

#घोषणा VC4_HDMI_TX_PHY_CHANNEL_SWAP_TXCK_OUT_SEL_MASK	VC4_MASK(13, 12)
#घोषणा VC4_HDMI_TX_PHY_CHANNEL_SWAP_TXCK_OUT_SEL_SHIFT	12
#घोषणा VC4_HDMI_TX_PHY_CHANNEL_SWAP_TX2_OUT_SEL_MASK	VC4_MASK(9, 8)
#घोषणा VC4_HDMI_TX_PHY_CHANNEL_SWAP_TX2_OUT_SEL_SHIFT	8
#घोषणा VC4_HDMI_TX_PHY_CHANNEL_SWAP_TX1_OUT_SEL_MASK	VC4_MASK(5, 4)
#घोषणा VC4_HDMI_TX_PHY_CHANNEL_SWAP_TX1_OUT_SEL_SHIFT	4
#घोषणा VC4_HDMI_TX_PHY_CHANNEL_SWAP_TX0_OUT_SEL_MASK	VC4_MASK(1, 0)
#घोषणा VC4_HDMI_TX_PHY_CHANNEL_SWAP_TX0_OUT_SEL_SHIFT	0

#घोषणा VC4_HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_1_MIN_LIMIT_MASK		VC4_MASK(27, 0)
#घोषणा VC4_HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_1_MIN_LIMIT_SHIFT	0

#घोषणा VC4_HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_2_MAX_LIMIT_MASK		VC4_MASK(27, 0)
#घोषणा VC4_HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_2_MAX_LIMIT_SHIFT	0

#घोषणा VC4_HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_4_STABLE_THRESHOLD_MASK	VC4_MASK(31, 16)
#घोषणा VC4_HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_4_STABLE_THRESHOLD_SHIFT	16
#घोषणा VC4_HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_4_HOLD_THRESHOLD_MASK	VC4_MASK(15, 0)
#घोषणा VC4_HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_4_HOLD_THRESHOLD_SHIFT	0

#घोषणा VC4_HDMI_RM_CONTROL_EN_FREEZE_COUNTERS		BIT(19)
#घोषणा VC4_HDMI_RM_CONTROL_EN_LOAD_INTEGRATOR		BIT(17)
#घोषणा VC4_HDMI_RM_CONTROL_FREE_RUN			BIT(4)

#घोषणा VC4_HDMI_RM_OFFSET_ONLY				BIT(31)
#घोषणा VC4_HDMI_RM_OFFSET_OFFSET_SHIFT			0
#घोषणा VC4_HDMI_RM_OFFSET_OFFSET_MASK			VC4_MASK(30, 0)

#घोषणा VC4_HDMI_RM_FORMAT_SHIFT_SHIFT			24
#घोषणा VC4_HDMI_RM_FORMAT_SHIFT_MASK			VC4_MASK(25, 24)

#घोषणा OSCILLATOR_FREQUENCY	54000000

व्योम vc4_hdmi_phy_init(काष्ठा vc4_hdmi *vc4_hdmi,
		       काष्ठा vc4_hdmi_connector_state *conn_state)
अणु
	/* PHY should be in reset, like
	 * vc4_hdmi_encoder_disable() करोes.
	 */

	HDMI_WRITE(HDMI_TX_PHY_RESET_CTL, 0xf << 16);
	HDMI_WRITE(HDMI_TX_PHY_RESET_CTL, 0);
पूर्ण

व्योम vc4_hdmi_phy_disable(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	HDMI_WRITE(HDMI_TX_PHY_RESET_CTL, 0xf << 16);
पूर्ण

व्योम vc4_hdmi_phy_rng_enable(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	HDMI_WRITE(HDMI_TX_PHY_CTL_0,
		   HDMI_READ(HDMI_TX_PHY_CTL_0) &
		   ~VC4_HDMI_TX_PHY_RNG_PWRDN);
पूर्ण

व्योम vc4_hdmi_phy_rng_disable(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	HDMI_WRITE(HDMI_TX_PHY_CTL_0,
		   HDMI_READ(HDMI_TX_PHY_CTL_0) |
		   VC4_HDMI_TX_PHY_RNG_PWRDN);
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ
phy_get_vco_freq(अचिन्हित दीर्घ दीर्घ घड़ी, u8 *vco_sel, u8 *vco_भाग)
अणु
	अचिन्हित दीर्घ दीर्घ vco_freq = घड़ी;
	अचिन्हित पूर्णांक _vco_भाग = 0;
	अचिन्हित पूर्णांक _vco_sel = 0;

	जबतक (vco_freq < 3000000000ULL) अणु
		_vco_भाग++;
		vco_freq = घड़ी * _vco_भाग * 10;
	पूर्ण

	अगर (vco_freq > 4500000000ULL)
		_vco_sel = 1;

	*vco_sel = _vco_sel;
	*vco_भाग = _vco_भाग;

	वापस vco_freq;
पूर्ण

अटल u8 phy_get_cp_current(अचिन्हित दीर्घ vco_freq)
अणु
	अगर (vco_freq < 3700000000ULL)
		वापस 0x1c;

	वापस 0x18;
पूर्ण

अटल u32 phy_get_rm_offset(अचिन्हित दीर्घ दीर्घ vco_freq)
अणु
	अचिन्हित दीर्घ दीर्घ fref = OSCILLATOR_FREQUENCY;
	u64 offset = 0;

	/* RM offset is stored as 9.22 क्रमmat */
	offset = vco_freq * 2;
	offset = offset << 22;
	करो_भाग(offset, fref);
	offset >>= 2;

	वापस offset;
पूर्ण

अटल u8 phy_get_vco_gain(अचिन्हित दीर्घ दीर्घ vco_freq)
अणु
	अगर (vco_freq < 3350000000ULL)
		वापस 0xf;

	अगर (vco_freq < 3700000000ULL)
		वापस 0xc;

	अगर (vco_freq < 4050000000ULL)
		वापस 0x6;

	अगर (vco_freq < 4800000000ULL)
		वापस 0x5;

	अगर (vco_freq < 5200000000ULL)
		वापस 0x7;

	वापस 0x2;
पूर्ण

काष्ठा phy_lane_settings अणु
	काष्ठा अणु
		u8 preemphasis;
		u8 मुख्य_driver;
	पूर्ण amplitude;

	u8 res_sel_data;
	u8 term_res_sel_data;
पूर्ण;

काष्ठा phy_settings अणु
	अचिन्हित दीर्घ दीर्घ min_rate;
	अचिन्हित दीर्घ दीर्घ max_rate;
	काष्ठा phy_lane_settings channel[3];
	काष्ठा phy_lane_settings घड़ी;
पूर्ण;

अटल स्थिर काष्ठा phy_settings vc5_hdmi_phy_settings[] = अणु
	अणु
		0, 50000000,
		अणु
			अणुअणु0x0, 0x0Aपूर्ण, 0x12, 0x0पूर्ण,
			अणुअणु0x0, 0x0Aपूर्ण, 0x12, 0x0पूर्ण,
			अणुअणु0x0, 0x0Aपूर्ण, 0x12, 0x0पूर्ण
		पूर्ण,
		अणुअणु0x0, 0x0Aपूर्ण, 0x18, 0x0पूर्ण,
	पूर्ण,
	अणु
		50000001, 75000000,
		अणु
			अणुअणु0x0, 0x09पूर्ण, 0x12, 0x0पूर्ण,
			अणुअणु0x0, 0x09पूर्ण, 0x12, 0x0पूर्ण,
			अणुअणु0x0, 0x09पूर्ण, 0x12, 0x0पूर्ण
		पूर्ण,
		अणुअणु0x0, 0x0Cपूर्ण, 0x18, 0x3पूर्ण,
	पूर्ण,
	अणु
		75000001,   165000000,
		अणु
			अणुअणु0x0, 0x09पूर्ण, 0x12, 0x0पूर्ण,
			अणुअणु0x0, 0x09पूर्ण, 0x12, 0x0पूर्ण,
			अणुअणु0x0, 0x09पूर्ण, 0x12, 0x0पूर्ण
		पूर्ण,
		अणुअणु0x0, 0x0Cपूर्ण, 0x18, 0x3पूर्ण,
	पूर्ण,
	अणु
		165000001,  250000000,
		अणु
			अणुअणु0x0, 0x0Fपूर्ण, 0x12, 0x1पूर्ण,
			अणुअणु0x0, 0x0Fपूर्ण, 0x12, 0x1पूर्ण,
			अणुअणु0x0, 0x0Fपूर्ण, 0x12, 0x1पूर्ण
		पूर्ण,
		अणुअणु0x0, 0x0Cपूर्ण, 0x18, 0x3पूर्ण,
	पूर्ण,
	अणु
		250000001,  340000000,
		अणु
			अणुअणु0x2, 0x0Dपूर्ण, 0x12, 0x1पूर्ण,
			अणुअणु0x2, 0x0Dपूर्ण, 0x12, 0x1पूर्ण,
			अणुअणु0x2, 0x0Dपूर्ण, 0x12, 0x1पूर्ण
		पूर्ण,
		अणुअणु0x0, 0x0Cपूर्ण, 0x18, 0xFपूर्ण,
	पूर्ण,
	अणु
		340000001,  450000000,
		अणु
			अणुअणु0x0, 0x1Bपूर्ण, 0x12, 0xFपूर्ण,
			अणुअणु0x0, 0x1Bपूर्ण, 0x12, 0xFपूर्ण,
			अणुअणु0x0, 0x1Bपूर्ण, 0x12, 0xFपूर्ण
		पूर्ण,
		अणुअणु0x0, 0x0Aपूर्ण, 0x12, 0xFपूर्ण,
	पूर्ण,
	अणु
		450000001,  600000000,
		अणु
			अणुअणु0x0, 0x1Cपूर्ण, 0x12, 0xFपूर्ण,
			अणुअणु0x0, 0x1Cपूर्ण, 0x12, 0xFपूर्ण,
			अणुअणु0x0, 0x1Cपूर्ण, 0x12, 0xFपूर्ण
		पूर्ण,
		अणुअणु0x0, 0x0Bपूर्ण, 0x13, 0xFपूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा phy_settings *phy_get_settings(अचिन्हित दीर्घ दीर्घ पंचांगds_rate)
अणु
	अचिन्हित पूर्णांक count = ARRAY_SIZE(vc5_hdmi_phy_settings);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		स्थिर काष्ठा phy_settings *s = &vc5_hdmi_phy_settings[i];

		अगर (पंचांगds_rate >= s->min_rate && पंचांगds_rate <= s->max_rate)
			वापस s;
	पूर्ण

	/*
	 * If the pixel घड़ी exceeds our max setting, try the max
	 * setting anyway.
	 */
	वापस &vc5_hdmi_phy_settings[count - 1];
पूर्ण

अटल स्थिर काष्ठा phy_lane_settings *
phy_get_channel_settings(क्रमागत vc4_hdmi_phy_channel chan,
			 अचिन्हित दीर्घ दीर्घ पंचांगds_rate)
अणु
	स्थिर काष्ठा phy_settings *settings = phy_get_settings(पंचांगds_rate);

	अगर (chan == PHY_LANE_CK)
		वापस &settings->घड़ी;

	वापस &settings->channel[chan];
पूर्ण

अटल व्योम vc5_hdmi_reset_phy(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	HDMI_WRITE(HDMI_TX_PHY_RESET_CTL, 0x0f);
	HDMI_WRITE(HDMI_TX_PHY_POWERDOWN_CTL, BIT(10));
पूर्ण

व्योम vc5_hdmi_phy_init(काष्ठा vc4_hdmi *vc4_hdmi,
		       काष्ठा vc4_hdmi_connector_state *conn_state)
अणु
	स्थिर काष्ठा phy_lane_settings *chan0_settings, *chan1_settings, *chan2_settings, *घड़ी_settings;
	स्थिर काष्ठा vc4_hdmi_variant *variant = vc4_hdmi->variant;
	अचिन्हित दीर्घ दीर्घ pixel_freq = conn_state->pixel_rate;
	अचिन्हित दीर्घ दीर्घ vco_freq;
	अचिन्हित अक्षर word_sel;
	u8 vco_sel, vco_भाग;

	vco_freq = phy_get_vco_freq(pixel_freq, &vco_sel, &vco_भाग);

	vc5_hdmi_reset_phy(vc4_hdmi);

	HDMI_WRITE(HDMI_TX_PHY_POWERDOWN_CTL,
		   VC4_HDMI_TX_PHY_POWERDOWN_CTL_RNDGEN_PWRDN);

	HDMI_WRITE(HDMI_TX_PHY_RESET_CTL,
		   HDMI_READ(HDMI_TX_PHY_RESET_CTL) &
		   ~VC4_HDMI_TX_PHY_RESET_CTL_TX_0_RESET &
		   ~VC4_HDMI_TX_PHY_RESET_CTL_TX_1_RESET &
		   ~VC4_HDMI_TX_PHY_RESET_CTL_TX_2_RESET &
		   ~VC4_HDMI_TX_PHY_RESET_CTL_TX_CK_RESET);

	HDMI_WRITE(HDMI_RM_CONTROL,
		   HDMI_READ(HDMI_RM_CONTROL) |
		   VC4_HDMI_RM_CONTROL_EN_FREEZE_COUNTERS |
		   VC4_HDMI_RM_CONTROL_EN_LOAD_INTEGRATOR |
		   VC4_HDMI_RM_CONTROL_FREE_RUN);

	HDMI_WRITE(HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_1,
		   (HDMI_READ(HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_1) &
		    ~VC4_HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_1_MIN_LIMIT_MASK) |
		   VC4_SET_FIELD(0, VC4_HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_1_MIN_LIMIT));

	HDMI_WRITE(HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_2,
		   (HDMI_READ(HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_2) &
		    ~VC4_HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_2_MAX_LIMIT_MASK) |
		   VC4_SET_FIELD(0, VC4_HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_2_MAX_LIMIT));

	HDMI_WRITE(HDMI_RM_OFFSET,
		   VC4_SET_FIELD(phy_get_rm_offset(vco_freq),
				 VC4_HDMI_RM_OFFSET_OFFSET) |
		   VC4_HDMI_RM_OFFSET_ONLY);

	HDMI_WRITE(HDMI_TX_PHY_CLK_DIV,
		   VC4_SET_FIELD(vco_भाग, VC4_HDMI_TX_PHY_CLK_DIV_VCO));

	HDMI_WRITE(HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_4,
		   VC4_SET_FIELD(0xe147, VC4_HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_4_HOLD_THRESHOLD) |
		   VC4_SET_FIELD(0xe14, VC4_HDMI_TX_PHY_PLL_CALIBRATION_CONFIG_4_STABLE_THRESHOLD));

	HDMI_WRITE(HDMI_TX_PHY_PLL_CTL_0,
		   VC4_HDMI_TX_PHY_PLL_CTL_0_ENA_VCO_CLK |
		   VC4_HDMI_TX_PHY_PLL_CTL_0_VCO_CONT_EN |
		   VC4_HDMI_TX_PHY_PLL_CTL_0_MASH11_MODE |
		   VC4_SET_FIELD(vco_sel, VC4_HDMI_TX_PHY_PLL_CTL_0_VCO_SEL));

	HDMI_WRITE(HDMI_TX_PHY_PLL_CTL_1,
		   HDMI_READ(HDMI_TX_PHY_PLL_CTL_1) |
		   VC4_HDMI_TX_PHY_PLL_CTL_1_FREQ_DOUBLER_ENABLE |
		   VC4_SET_FIELD(3, VC4_HDMI_TX_PHY_PLL_CTL_1_POST_RST_SEL) |
		   VC4_SET_FIELD(1, VC4_HDMI_TX_PHY_PLL_CTL_1_FREQ_DOUBLER_DELAY) |
		   VC4_SET_FIELD(0x8a, VC4_HDMI_TX_PHY_PLL_CTL_1_CPP));

	HDMI_WRITE(HDMI_RM_FORMAT,
		   HDMI_READ(HDMI_RM_FORMAT) |
		   VC4_SET_FIELD(2, VC4_HDMI_RM_FORMAT_SHIFT));

	HDMI_WRITE(HDMI_TX_PHY_PLL_CFG,
		   HDMI_READ(HDMI_TX_PHY_PLL_CFG) |
		   VC4_SET_FIELD(1, VC4_HDMI_TX_PHY_PLL_CFG_PDIV));

	अगर (pixel_freq >= 340000000)
		word_sel = 3;
	अन्यथा
		word_sel = 0;
	HDMI_WRITE(HDMI_TX_PHY_TMDS_CLK_WORD_SEL, word_sel);

	HDMI_WRITE(HDMI_TX_PHY_CTL_3,
		   VC4_SET_FIELD(phy_get_cp_current(vco_freq),
				 VC4_HDMI_TX_PHY_CTL_3_ICP) |
		   VC4_SET_FIELD(1, VC4_HDMI_TX_PHY_CTL_3_CP) |
		   VC4_SET_FIELD(1, VC4_HDMI_TX_PHY_CTL_3_CP1) |
		   VC4_SET_FIELD(3, VC4_HDMI_TX_PHY_CTL_3_CZ) |
		   VC4_SET_FIELD(4, VC4_HDMI_TX_PHY_CTL_3_RP) |
		   VC4_SET_FIELD(6, VC4_HDMI_TX_PHY_CTL_3_RZ));

	chan0_settings =
		phy_get_channel_settings(variant->phy_lane_mapping[PHY_LANE_0],
					 pixel_freq);
	chan1_settings =
		phy_get_channel_settings(variant->phy_lane_mapping[PHY_LANE_1],
					 pixel_freq);
	chan2_settings =
		phy_get_channel_settings(variant->phy_lane_mapping[PHY_LANE_2],
					 pixel_freq);
	घड़ी_settings =
		phy_get_channel_settings(variant->phy_lane_mapping[PHY_LANE_CK],
					 pixel_freq);

	HDMI_WRITE(HDMI_TX_PHY_CTL_0,
		   VC4_SET_FIELD(chan0_settings->amplitude.preemphasis,
				 VC4_HDMI_TX_PHY_CTL_0_PREEMP_0_PREEMP) |
		   VC4_SET_FIELD(chan0_settings->amplitude.मुख्य_driver,
				 VC4_HDMI_TX_PHY_CTL_0_PREEMP_0_MAINDRV) |
		   VC4_SET_FIELD(chan1_settings->amplitude.preemphasis,
				 VC4_HDMI_TX_PHY_CTL_0_PREEMP_1_PREEMP) |
		   VC4_SET_FIELD(chan1_settings->amplitude.मुख्य_driver,
				 VC4_HDMI_TX_PHY_CTL_0_PREEMP_1_MAINDRV) |
		   VC4_SET_FIELD(chan2_settings->amplitude.preemphasis,
				 VC4_HDMI_TX_PHY_CTL_0_PREEMP_2_PREEMP) |
		   VC4_SET_FIELD(chan2_settings->amplitude.मुख्य_driver,
				 VC4_HDMI_TX_PHY_CTL_0_PREEMP_2_MAINDRV) |
		   VC4_SET_FIELD(घड़ी_settings->amplitude.preemphasis,
				 VC4_HDMI_TX_PHY_CTL_0_PREEMP_CK_PREEMP) |
		   VC4_SET_FIELD(घड़ी_settings->amplitude.मुख्य_driver,
				 VC4_HDMI_TX_PHY_CTL_0_PREEMP_CK_MAINDRV));

	HDMI_WRITE(HDMI_TX_PHY_CTL_1,
		   HDMI_READ(HDMI_TX_PHY_CTL_1) |
		   VC4_SET_FIELD(chan0_settings->res_sel_data,
				 VC4_HDMI_TX_PHY_CTL_1_RES_SEL_DATA0) |
		   VC4_SET_FIELD(chan1_settings->res_sel_data,
				 VC4_HDMI_TX_PHY_CTL_1_RES_SEL_DATA1) |
		   VC4_SET_FIELD(chan2_settings->res_sel_data,
				 VC4_HDMI_TX_PHY_CTL_1_RES_SEL_DATA2) |
		   VC4_SET_FIELD(घड़ी_settings->res_sel_data,
				 VC4_HDMI_TX_PHY_CTL_1_RES_SEL_CK));

	HDMI_WRITE(HDMI_TX_PHY_CTL_2,
		   VC4_SET_FIELD(chan0_settings->term_res_sel_data,
				 VC4_HDMI_TX_PHY_CTL_2_TERM_RES_SELDATA0) |
		   VC4_SET_FIELD(chan1_settings->term_res_sel_data,
				 VC4_HDMI_TX_PHY_CTL_2_TERM_RES_SELDATA1) |
		   VC4_SET_FIELD(chan2_settings->term_res_sel_data,
				 VC4_HDMI_TX_PHY_CTL_2_TERM_RES_SELDATA2) |
		   VC4_SET_FIELD(घड़ी_settings->term_res_sel_data,
				 VC4_HDMI_TX_PHY_CTL_2_TERM_RES_SELCK) |
		   VC4_SET_FIELD(phy_get_vco_gain(vco_freq),
				 VC4_HDMI_TX_PHY_CTL_2_VCO_GAIN));

	HDMI_WRITE(HDMI_TX_PHY_CHANNEL_SWAP,
		   VC4_SET_FIELD(variant->phy_lane_mapping[PHY_LANE_0],
				 VC4_HDMI_TX_PHY_CHANNEL_SWAP_TX0_OUT_SEL) |
		   VC4_SET_FIELD(variant->phy_lane_mapping[PHY_LANE_1],
				 VC4_HDMI_TX_PHY_CHANNEL_SWAP_TX1_OUT_SEL) |
		   VC4_SET_FIELD(variant->phy_lane_mapping[PHY_LANE_2],
				 VC4_HDMI_TX_PHY_CHANNEL_SWAP_TX2_OUT_SEL) |
		   VC4_SET_FIELD(variant->phy_lane_mapping[PHY_LANE_CK],
				 VC4_HDMI_TX_PHY_CHANNEL_SWAP_TXCK_OUT_SEL));

	HDMI_WRITE(HDMI_TX_PHY_RESET_CTL,
		   HDMI_READ(HDMI_TX_PHY_RESET_CTL) &
		   ~(VC4_HDMI_TX_PHY_RESET_CTL_PLL_RESETB |
		     VC4_HDMI_TX_PHY_RESET_CTL_PLLDIV_RESETB));

	HDMI_WRITE(HDMI_TX_PHY_RESET_CTL,
		   HDMI_READ(HDMI_TX_PHY_RESET_CTL) |
		   VC4_HDMI_TX_PHY_RESET_CTL_PLL_RESETB |
		   VC4_HDMI_TX_PHY_RESET_CTL_PLLDIV_RESETB);
पूर्ण

व्योम vc5_hdmi_phy_disable(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	vc5_hdmi_reset_phy(vc4_hdmi);
पूर्ण

व्योम vc5_hdmi_phy_rng_enable(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	HDMI_WRITE(HDMI_TX_PHY_POWERDOWN_CTL,
		   HDMI_READ(HDMI_TX_PHY_POWERDOWN_CTL) &
		   ~VC4_HDMI_TX_PHY_POWERDOWN_CTL_RNDGEN_PWRDN);
पूर्ण

व्योम vc5_hdmi_phy_rng_disable(काष्ठा vc4_hdmi *vc4_hdmi)
अणु
	HDMI_WRITE(HDMI_TX_PHY_POWERDOWN_CTL,
		   HDMI_READ(HDMI_TX_PHY_POWERDOWN_CTL) |
		   VC4_HDMI_TX_PHY_POWERDOWN_CTL_RNDGEN_PWRDN);
पूर्ण
