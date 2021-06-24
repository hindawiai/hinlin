<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Analogix DP (Display port) core रेजिस्टर पूर्णांकerface driver.
 *
 * Copyright (C) 2012 Samsung Electronics Co., Ltd.
 * Author: Jingoo Han <jg1.han@samsung.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>

#समावेश <drm/bridge/analogix_dp.h>

#समावेश "analogix_dp_core.h"
#समावेश "analogix_dp_reg.h"

#घोषणा COMMON_INT_MASK_1	0
#घोषणा COMMON_INT_MASK_2	0
#घोषणा COMMON_INT_MASK_3	0
#घोषणा COMMON_INT_MASK_4	(HOTPLUG_CHG | HPD_LOST | PLUG)
#घोषणा INT_STA_MASK		INT_HPD

व्योम analogix_dp_enable_video_mute(काष्ठा analogix_dp_device *dp, bool enable)
अणु
	u32 reg;

	अगर (enable) अणु
		reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_VIDEO_CTL_1);
		reg |= HDCP_VIDEO_MUTE;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_VIDEO_CTL_1);
	पूर्ण अन्यथा अणु
		reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_VIDEO_CTL_1);
		reg &= ~HDCP_VIDEO_MUTE;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_VIDEO_CTL_1);
	पूर्ण
पूर्ण

व्योम analogix_dp_stop_video(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_VIDEO_CTL_1);
	reg &= ~VIDEO_EN;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_VIDEO_CTL_1);
पूर्ण

व्योम analogix_dp_lane_swap(काष्ठा analogix_dp_device *dp, bool enable)
अणु
	u32 reg;

	अगर (enable)
		reg = LANE3_MAP_LOGIC_LANE_0 | LANE2_MAP_LOGIC_LANE_1 |
		      LANE1_MAP_LOGIC_LANE_2 | LANE0_MAP_LOGIC_LANE_3;
	अन्यथा
		reg = LANE3_MAP_LOGIC_LANE_3 | LANE2_MAP_LOGIC_LANE_2 |
		      LANE1_MAP_LOGIC_LANE_1 | LANE0_MAP_LOGIC_LANE_0;

	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_LANE_MAP);
पूर्ण

व्योम analogix_dp_init_analog_param(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	reg = TX_TERMINAL_CTRL_50_OHM;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_ANALOG_CTL_1);

	reg = SEL_24M | TX_DVDD_BIT_1_0625V;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_ANALOG_CTL_2);

	अगर (dp->plat_data && is_rockchip(dp->plat_data->dev_type)) अणु
		reg = REF_CLK_24M;
		अगर (dp->plat_data->dev_type == RK3288_DP)
			reg ^= REF_CLK_MASK;

		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_PLL_REG_1);
		ग_लिखोl(0x95, dp->reg_base + ANALOGIX_DP_PLL_REG_2);
		ग_लिखोl(0x40, dp->reg_base + ANALOGIX_DP_PLL_REG_3);
		ग_लिखोl(0x58, dp->reg_base + ANALOGIX_DP_PLL_REG_4);
		ग_लिखोl(0x22, dp->reg_base + ANALOGIX_DP_PLL_REG_5);
	पूर्ण

	reg = DRIVE_DVDD_BIT_1_0625V | VCO_BIT_600_MICRO;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_ANALOG_CTL_3);

	reg = PD_RING_OSC | AUX_TERMINAL_CTRL_50_OHM |
		TX_CUR1_2X | TX_CUR_16_MA;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_PLL_FILTER_CTL_1);

	reg = CH3_AMP_400_MV | CH2_AMP_400_MV |
		CH1_AMP_400_MV | CH0_AMP_400_MV;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_TX_AMP_TUNING_CTL);
पूर्ण

व्योम analogix_dp_init_पूर्णांकerrupt(काष्ठा analogix_dp_device *dp)
अणु
	/* Set पूर्णांकerrupt pin निश्चितion polarity as high */
	ग_लिखोl(INT_POL1 | INT_POL0, dp->reg_base + ANALOGIX_DP_INT_CTL);

	/* Clear pending regisers */
	ग_लिखोl(0xff, dp->reg_base + ANALOGIX_DP_COMMON_INT_STA_1);
	ग_लिखोl(0x4f, dp->reg_base + ANALOGIX_DP_COMMON_INT_STA_2);
	ग_लिखोl(0xe0, dp->reg_base + ANALOGIX_DP_COMMON_INT_STA_3);
	ग_लिखोl(0xe7, dp->reg_base + ANALOGIX_DP_COMMON_INT_STA_4);
	ग_लिखोl(0x63, dp->reg_base + ANALOGIX_DP_INT_STA);

	/* 0:mask,1: unmask */
	ग_लिखोl(0x00, dp->reg_base + ANALOGIX_DP_COMMON_INT_MASK_1);
	ग_लिखोl(0x00, dp->reg_base + ANALOGIX_DP_COMMON_INT_MASK_2);
	ग_लिखोl(0x00, dp->reg_base + ANALOGIX_DP_COMMON_INT_MASK_3);
	ग_लिखोl(0x00, dp->reg_base + ANALOGIX_DP_COMMON_INT_MASK_4);
	ग_लिखोl(0x00, dp->reg_base + ANALOGIX_DP_INT_STA_MASK);
पूर्ण

व्योम analogix_dp_reset(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	analogix_dp_stop_video(dp);
	analogix_dp_enable_video_mute(dp, 0);

	अगर (dp->plat_data && is_rockchip(dp->plat_data->dev_type))
		reg = RK_VID_CAP_FUNC_EN_N | RK_VID_FIFO_FUNC_EN_N |
			SW_FUNC_EN_N;
	अन्यथा
		reg = MASTER_VID_FUNC_EN_N | SLAVE_VID_FUNC_EN_N |
			AUD_FIFO_FUNC_EN_N | AUD_FUNC_EN_N |
			HDCP_FUNC_EN_N | SW_FUNC_EN_N;

	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_FUNC_EN_1);

	reg = SSC_FUNC_EN_N | AUX_FUNC_EN_N |
		SERDES_FIFO_FUNC_EN_N |
		LS_CLK_DOMAIN_FUNC_EN_N;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_FUNC_EN_2);

	usleep_range(20, 30);

	analogix_dp_lane_swap(dp, 0);

	ग_लिखोl(0x0, dp->reg_base + ANALOGIX_DP_SYS_CTL_1);
	ग_लिखोl(0x40, dp->reg_base + ANALOGIX_DP_SYS_CTL_2);
	ग_लिखोl(0x0, dp->reg_base + ANALOGIX_DP_SYS_CTL_3);
	ग_लिखोl(0x0, dp->reg_base + ANALOGIX_DP_SYS_CTL_4);

	ग_लिखोl(0x0, dp->reg_base + ANALOGIX_DP_PKT_SEND_CTL);
	ग_लिखोl(0x0, dp->reg_base + ANALOGIX_DP_HDCP_CTL);

	ग_लिखोl(0x5e, dp->reg_base + ANALOGIX_DP_HPD_DEGLITCH_L);
	ग_लिखोl(0x1a, dp->reg_base + ANALOGIX_DP_HPD_DEGLITCH_H);

	ग_लिखोl(0x10, dp->reg_base + ANALOGIX_DP_LINK_DEBUG_CTL);

	ग_लिखोl(0x0, dp->reg_base + ANALOGIX_DP_PHY_TEST);

	ग_लिखोl(0x0, dp->reg_base + ANALOGIX_DP_VIDEO_FIFO_THRD);
	ग_लिखोl(0x20, dp->reg_base + ANALOGIX_DP_AUDIO_MARGIN);

	ग_लिखोl(0x4, dp->reg_base + ANALOGIX_DP_M_VID_GEN_FILTER_TH);
	ग_लिखोl(0x2, dp->reg_base + ANALOGIX_DP_M_AUD_GEN_FILTER_TH);

	ग_लिखोl(0x00000101, dp->reg_base + ANALOGIX_DP_SOC_GENERAL_CTL);
पूर्ण

व्योम analogix_dp_swreset(काष्ठा analogix_dp_device *dp)
अणु
	ग_लिखोl(RESET_DP_TX, dp->reg_base + ANALOGIX_DP_TX_SW_RESET);
पूर्ण

व्योम analogix_dp_config_पूर्णांकerrupt(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	/* 0: mask, 1: unmask */
	reg = COMMON_INT_MASK_1;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_COMMON_INT_MASK_1);

	reg = COMMON_INT_MASK_2;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_COMMON_INT_MASK_2);

	reg = COMMON_INT_MASK_3;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_COMMON_INT_MASK_3);

	reg = COMMON_INT_MASK_4;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_COMMON_INT_MASK_4);

	reg = INT_STA_MASK;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_INT_STA_MASK);
पूर्ण

व्योम analogix_dp_mute_hpd_पूर्णांकerrupt(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	/* 0: mask, 1: unmask */
	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_COMMON_INT_MASK_4);
	reg &= ~COMMON_INT_MASK_4;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_COMMON_INT_MASK_4);

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_INT_STA_MASK);
	reg &= ~INT_STA_MASK;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_INT_STA_MASK);
पूर्ण

व्योम analogix_dp_unmute_hpd_पूर्णांकerrupt(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	/* 0: mask, 1: unmask */
	reg = COMMON_INT_MASK_4;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_COMMON_INT_MASK_4);

	reg = INT_STA_MASK;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_INT_STA_MASK);
पूर्ण

क्रमागत pll_status analogix_dp_get_pll_lock_status(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_DEBUG_CTL);
	अगर (reg & PLL_LOCK)
		वापस PLL_LOCKED;
	अन्यथा
		वापस PLL_UNLOCKED;
पूर्ण

व्योम analogix_dp_set_pll_घातer_करोwn(काष्ठा analogix_dp_device *dp, bool enable)
अणु
	u32 reg;
	u32 mask = DP_PLL_PD;
	u32 pd_addr = ANALOGIX_DP_PLL_CTL;

	अगर (dp->plat_data && is_rockchip(dp->plat_data->dev_type)) अणु
		pd_addr = ANALOGIX_DP_PD;
		mask = RK_PLL_PD;
	पूर्ण

	reg = पढ़ोl(dp->reg_base + pd_addr);
	अगर (enable)
		reg |= mask;
	अन्यथा
		reg &= ~mask;
	ग_लिखोl(reg, dp->reg_base + pd_addr);
पूर्ण

व्योम analogix_dp_set_analog_घातer_करोwn(काष्ठा analogix_dp_device *dp,
				       क्रमागत analog_घातer_block block,
				       bool enable)
अणु
	u32 reg;
	u32 phy_pd_addr = ANALOGIX_DP_PHY_PD;
	u32 mask;

	अगर (dp->plat_data && is_rockchip(dp->plat_data->dev_type))
		phy_pd_addr = ANALOGIX_DP_PD;

	चयन (block) अणु
	हाल AUX_BLOCK:
		अगर (dp->plat_data && is_rockchip(dp->plat_data->dev_type))
			mask = RK_AUX_PD;
		अन्यथा
			mask = AUX_PD;

		reg = पढ़ोl(dp->reg_base + phy_pd_addr);
		अगर (enable)
			reg |= mask;
		अन्यथा
			reg &= ~mask;
		ग_लिखोl(reg, dp->reg_base + phy_pd_addr);
		अवरोध;
	हाल CH0_BLOCK:
		mask = CH0_PD;
		reg = पढ़ोl(dp->reg_base + phy_pd_addr);

		अगर (enable)
			reg |= mask;
		अन्यथा
			reg &= ~mask;
		ग_लिखोl(reg, dp->reg_base + phy_pd_addr);
		अवरोध;
	हाल CH1_BLOCK:
		mask = CH1_PD;
		reg = पढ़ोl(dp->reg_base + phy_pd_addr);

		अगर (enable)
			reg |= mask;
		अन्यथा
			reg &= ~mask;
		ग_लिखोl(reg, dp->reg_base + phy_pd_addr);
		अवरोध;
	हाल CH2_BLOCK:
		mask = CH2_PD;
		reg = पढ़ोl(dp->reg_base + phy_pd_addr);

		अगर (enable)
			reg |= mask;
		अन्यथा
			reg &= ~mask;
		ग_लिखोl(reg, dp->reg_base + phy_pd_addr);
		अवरोध;
	हाल CH3_BLOCK:
		mask = CH3_PD;
		reg = पढ़ोl(dp->reg_base + phy_pd_addr);

		अगर (enable)
			reg |= mask;
		अन्यथा
			reg &= ~mask;
		ग_लिखोl(reg, dp->reg_base + phy_pd_addr);
		अवरोध;
	हाल ANALOG_TOTAL:
		/*
		 * There is no bit named DP_PHY_PD, so We used DP_INC_BG
		 * to घातer off everything instead of DP_PHY_PD in
		 * Rockchip
		 */
		अगर (dp->plat_data && is_rockchip(dp->plat_data->dev_type))
			mask = DP_INC_BG;
		अन्यथा
			mask = DP_PHY_PD;

		reg = पढ़ोl(dp->reg_base + phy_pd_addr);
		अगर (enable)
			reg |= mask;
		अन्यथा
			reg &= ~mask;

		ग_लिखोl(reg, dp->reg_base + phy_pd_addr);
		अगर (dp->plat_data && is_rockchip(dp->plat_data->dev_type))
			usleep_range(10, 15);
		अवरोध;
	हाल POWER_ALL:
		अगर (enable) अणु
			reg = DP_ALL_PD;
			ग_लिखोl(reg, dp->reg_base + phy_pd_addr);
		पूर्ण अन्यथा अणु
			reg = DP_ALL_PD;
			ग_लिखोl(reg, dp->reg_base + phy_pd_addr);
			usleep_range(10, 15);
			reg &= ~DP_INC_BG;
			ग_लिखोl(reg, dp->reg_base + phy_pd_addr);
			usleep_range(10, 15);

			ग_लिखोl(0x00, dp->reg_base + phy_pd_addr);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक analogix_dp_init_analog_func(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;
	पूर्णांक समयout_loop = 0;

	analogix_dp_set_analog_घातer_करोwn(dp, POWER_ALL, 0);

	reg = PLL_LOCK_CHG;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_COMMON_INT_STA_1);

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_DEBUG_CTL);
	reg &= ~(F_PLL_LOCK | PLL_LOCK_CTRL);
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_DEBUG_CTL);

	/* Power up PLL */
	अगर (analogix_dp_get_pll_lock_status(dp) == PLL_UNLOCKED) अणु
		analogix_dp_set_pll_घातer_करोwn(dp, 0);

		जबतक (analogix_dp_get_pll_lock_status(dp) == PLL_UNLOCKED) अणु
			समयout_loop++;
			अगर (DP_TIMEOUT_LOOP_COUNT < समयout_loop) अणु
				dev_err(dp->dev, "failed to get pll lock status\n");
				वापस -ETIMEDOUT;
			पूर्ण
			usleep_range(10, 20);
		पूर्ण
	पूर्ण

	/* Enable Serdes FIFO function and Link symbol घड़ी करोमुख्य module */
	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_FUNC_EN_2);
	reg &= ~(SERDES_FIFO_FUNC_EN_N | LS_CLK_DOMAIN_FUNC_EN_N
		| AUX_FUNC_EN_N);
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_FUNC_EN_2);
	वापस 0;
पूर्ण

व्योम analogix_dp_clear_hotplug_पूर्णांकerrupts(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	अगर (dp->hpd_gpiod)
		वापस;

	reg = HOTPLUG_CHG | HPD_LOST | PLUG;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_COMMON_INT_STA_4);

	reg = INT_HPD;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_INT_STA);
पूर्ण

व्योम analogix_dp_init_hpd(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	अगर (dp->hpd_gpiod)
		वापस;

	analogix_dp_clear_hotplug_पूर्णांकerrupts(dp);

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_SYS_CTL_3);
	reg &= ~(F_HPD | HPD_CTRL);
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_SYS_CTL_3);
पूर्ण

व्योम analogix_dp_क्रमce_hpd(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_SYS_CTL_3);
	reg = (F_HPD | HPD_CTRL);
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_SYS_CTL_3);
पूर्ण

क्रमागत dp_irq_type analogix_dp_get_irq_type(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	अगर (dp->hpd_gpiod) अणु
		reg = gpiod_get_value(dp->hpd_gpiod);
		अगर (reg)
			वापस DP_IRQ_TYPE_HP_CABLE_IN;
		अन्यथा
			वापस DP_IRQ_TYPE_HP_CABLE_OUT;
	पूर्ण अन्यथा अणु
		/* Parse hotplug पूर्णांकerrupt status रेजिस्टर */
		reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_COMMON_INT_STA_4);

		अगर (reg & PLUG)
			वापस DP_IRQ_TYPE_HP_CABLE_IN;

		अगर (reg & HPD_LOST)
			वापस DP_IRQ_TYPE_HP_CABLE_OUT;

		अगर (reg & HOTPLUG_CHG)
			वापस DP_IRQ_TYPE_HP_CHANGE;

		वापस DP_IRQ_TYPE_UNKNOWN;
	पूर्ण
पूर्ण

व्योम analogix_dp_reset_aux(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	/* Disable AUX channel module */
	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_FUNC_EN_2);
	reg |= AUX_FUNC_EN_N;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_FUNC_EN_2);
पूर्ण

व्योम analogix_dp_init_aux(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	/* Clear inerrupts related to AUX channel */
	reg = RPLY_RECEIV | AUX_ERR;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_INT_STA);

	analogix_dp_set_analog_घातer_करोwn(dp, AUX_BLOCK, true);
	usleep_range(10, 11);
	analogix_dp_set_analog_घातer_करोwn(dp, AUX_BLOCK, false);

	analogix_dp_reset_aux(dp);

	/* AUX_BIT_PERIOD_EXPECTED_DELAY करोesn't apply to Rockchip IP */
	अगर (dp->plat_data && is_rockchip(dp->plat_data->dev_type))
		reg = 0;
	अन्यथा
		reg = AUX_BIT_PERIOD_EXPECTED_DELAY(3);

	/* Disable AUX transaction H/W retry */
	reg |= AUX_HW_RETRY_COUNT_SEL(0) |
	       AUX_HW_RETRY_INTERVAL_600_MICROSECONDS;

	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_AUX_HW_RETRY_CTL);

	/* Receive AUX Channel DEFER commands equal to DEFFER_COUNT*64 */
	reg = DEFER_CTRL_EN | DEFER_COUNT(1);
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_AUX_CH_DEFER_CTL);

	/* Enable AUX channel module */
	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_FUNC_EN_2);
	reg &= ~AUX_FUNC_EN_N;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_FUNC_EN_2);
पूर्ण

पूर्णांक analogix_dp_get_plug_in_status(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	अगर (dp->hpd_gpiod) अणु
		अगर (gpiod_get_value(dp->hpd_gpiod))
			वापस 0;
	पूर्ण अन्यथा अणु
		reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_SYS_CTL_3);
		अगर (reg & HPD_STATUS)
			वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

व्योम analogix_dp_enable_sw_function(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_FUNC_EN_1);
	reg &= ~SW_FUNC_EN_N;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_FUNC_EN_1);
पूर्ण

व्योम analogix_dp_set_link_bandwidth(काष्ठा analogix_dp_device *dp, u32 bwtype)
अणु
	u32 reg;

	reg = bwtype;
	अगर ((bwtype == DP_LINK_BW_2_7) || (bwtype == DP_LINK_BW_1_62))
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_LINK_BW_SET);
पूर्ण

व्योम analogix_dp_get_link_bandwidth(काष्ठा analogix_dp_device *dp, u32 *bwtype)
अणु
	u32 reg;

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_LINK_BW_SET);
	*bwtype = reg;
पूर्ण

व्योम analogix_dp_set_lane_count(काष्ठा analogix_dp_device *dp, u32 count)
अणु
	u32 reg;

	reg = count;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_LANE_COUNT_SET);
पूर्ण

व्योम analogix_dp_get_lane_count(काष्ठा analogix_dp_device *dp, u32 *count)
अणु
	u32 reg;

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_LANE_COUNT_SET);
	*count = reg;
पूर्ण

व्योम analogix_dp_enable_enhanced_mode(काष्ठा analogix_dp_device *dp,
				      bool enable)
अणु
	u32 reg;

	अगर (enable) अणु
		reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_SYS_CTL_4);
		reg |= ENHANCED;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_SYS_CTL_4);
	पूर्ण अन्यथा अणु
		reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_SYS_CTL_4);
		reg &= ~ENHANCED;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_SYS_CTL_4);
	पूर्ण
पूर्ण

व्योम analogix_dp_set_training_pattern(काष्ठा analogix_dp_device *dp,
				      क्रमागत pattern_set pattern)
अणु
	u32 reg;

	चयन (pattern) अणु
	हाल PRBS7:
		reg = SCRAMBLING_ENABLE | LINK_QUAL_PATTERN_SET_PRBS7;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_TRAINING_PTN_SET);
		अवरोध;
	हाल D10_2:
		reg = SCRAMBLING_ENABLE | LINK_QUAL_PATTERN_SET_D10_2;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_TRAINING_PTN_SET);
		अवरोध;
	हाल TRAINING_PTN1:
		reg = SCRAMBLING_DISABLE | SW_TRAINING_PATTERN_SET_PTN1;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_TRAINING_PTN_SET);
		अवरोध;
	हाल TRAINING_PTN2:
		reg = SCRAMBLING_DISABLE | SW_TRAINING_PATTERN_SET_PTN2;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_TRAINING_PTN_SET);
		अवरोध;
	हाल DP_NONE:
		reg = SCRAMBLING_ENABLE |
			LINK_QUAL_PATTERN_SET_DISABLE |
			SW_TRAINING_PATTERN_SET_NORMAL;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_TRAINING_PTN_SET);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम analogix_dp_set_lane0_pre_emphasis(काष्ठा analogix_dp_device *dp,
					u32 level)
अणु
	u32 reg;

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_LN0_LINK_TRAINING_CTL);
	reg &= ~PRE_EMPHASIS_SET_MASK;
	reg |= level << PRE_EMPHASIS_SET_SHIFT;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_LN0_LINK_TRAINING_CTL);
पूर्ण

व्योम analogix_dp_set_lane1_pre_emphasis(काष्ठा analogix_dp_device *dp,
					u32 level)
अणु
	u32 reg;

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_LN1_LINK_TRAINING_CTL);
	reg &= ~PRE_EMPHASIS_SET_MASK;
	reg |= level << PRE_EMPHASIS_SET_SHIFT;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_LN1_LINK_TRAINING_CTL);
पूर्ण

व्योम analogix_dp_set_lane2_pre_emphasis(काष्ठा analogix_dp_device *dp,
					u32 level)
अणु
	u32 reg;

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_LN2_LINK_TRAINING_CTL);
	reg &= ~PRE_EMPHASIS_SET_MASK;
	reg |= level << PRE_EMPHASIS_SET_SHIFT;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_LN2_LINK_TRAINING_CTL);
पूर्ण

व्योम analogix_dp_set_lane3_pre_emphasis(काष्ठा analogix_dp_device *dp,
					u32 level)
अणु
	u32 reg;

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_LN3_LINK_TRAINING_CTL);
	reg &= ~PRE_EMPHASIS_SET_MASK;
	reg |= level << PRE_EMPHASIS_SET_SHIFT;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_LN3_LINK_TRAINING_CTL);
पूर्ण

व्योम analogix_dp_set_lane0_link_training(काष्ठा analogix_dp_device *dp,
					 u32 training_lane)
अणु
	u32 reg;

	reg = training_lane;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_LN0_LINK_TRAINING_CTL);
पूर्ण

व्योम analogix_dp_set_lane1_link_training(काष्ठा analogix_dp_device *dp,
					 u32 training_lane)
अणु
	u32 reg;

	reg = training_lane;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_LN1_LINK_TRAINING_CTL);
पूर्ण

व्योम analogix_dp_set_lane2_link_training(काष्ठा analogix_dp_device *dp,
					 u32 training_lane)
अणु
	u32 reg;

	reg = training_lane;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_LN2_LINK_TRAINING_CTL);
पूर्ण

व्योम analogix_dp_set_lane3_link_training(काष्ठा analogix_dp_device *dp,
					 u32 training_lane)
अणु
	u32 reg;

	reg = training_lane;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_LN3_LINK_TRAINING_CTL);
पूर्ण

u32 analogix_dp_get_lane0_link_training(काष्ठा analogix_dp_device *dp)
अणु
	वापस पढ़ोl(dp->reg_base + ANALOGIX_DP_LN0_LINK_TRAINING_CTL);
पूर्ण

u32 analogix_dp_get_lane1_link_training(काष्ठा analogix_dp_device *dp)
अणु
	वापस पढ़ोl(dp->reg_base + ANALOGIX_DP_LN1_LINK_TRAINING_CTL);
पूर्ण

u32 analogix_dp_get_lane2_link_training(काष्ठा analogix_dp_device *dp)
अणु
	वापस पढ़ोl(dp->reg_base + ANALOGIX_DP_LN2_LINK_TRAINING_CTL);
पूर्ण

u32 analogix_dp_get_lane3_link_training(काष्ठा analogix_dp_device *dp)
अणु
	वापस पढ़ोl(dp->reg_base + ANALOGIX_DP_LN3_LINK_TRAINING_CTL);
पूर्ण

व्योम analogix_dp_reset_macro(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_PHY_TEST);
	reg |= MACRO_RST;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_PHY_TEST);

	/* 10 us is the minimum reset समय. */
	usleep_range(10, 20);

	reg &= ~MACRO_RST;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_PHY_TEST);
पूर्ण

व्योम analogix_dp_init_video(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	reg = VSYNC_DET | VID_FORMAT_CHG | VID_CLK_CHG;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_COMMON_INT_STA_1);

	reg = 0x0;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_SYS_CTL_1);

	reg = CHA_CRI(4) | CHA_CTRL;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_SYS_CTL_2);

	reg = 0x0;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_SYS_CTL_3);

	reg = VID_HRES_TH(2) | VID_VRES_TH(0);
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_VIDEO_CTL_8);
पूर्ण

व्योम analogix_dp_set_video_color_क्रमmat(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	/* Configure the input color depth, color space, dynamic range */
	reg = (dp->video_info.dynamic_range << IN_D_RANGE_SHIFT) |
		(dp->video_info.color_depth << IN_BPC_SHIFT) |
		(dp->video_info.color_space << IN_COLOR_F_SHIFT);
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_VIDEO_CTL_2);

	/* Set Input Color YCbCr Coefficients to ITU601 or ITU709 */
	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_VIDEO_CTL_3);
	reg &= ~IN_YC_COEFFI_MASK;
	अगर (dp->video_info.ycbcr_coeff)
		reg |= IN_YC_COEFFI_ITU709;
	अन्यथा
		reg |= IN_YC_COEFFI_ITU601;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_VIDEO_CTL_3);
पूर्ण

पूर्णांक analogix_dp_is_slave_video_stream_घड़ी_on(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_SYS_CTL_1);
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_SYS_CTL_1);

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_SYS_CTL_1);

	अगर (!(reg & DET_STA)) अणु
		dev_dbg(dp->dev, "Input stream clock not detected.\n");
		वापस -EINVAL;
	पूर्ण

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_SYS_CTL_2);
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_SYS_CTL_2);

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_SYS_CTL_2);
	dev_dbg(dp->dev, "wait SYS_CTL_2.\n");

	अगर (reg & CHA_STA) अणु
		dev_dbg(dp->dev, "Input stream clk is changing\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम analogix_dp_set_video_cr_mn(काष्ठा analogix_dp_device *dp,
				 क्रमागत घड़ी_recovery_m_value_type type,
				 u32 m_value, u32 n_value)
अणु
	u32 reg;

	अगर (type == REGISTER_M) अणु
		reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_SYS_CTL_4);
		reg |= FIX_M_VID;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_SYS_CTL_4);
		reg = m_value & 0xff;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_M_VID_0);
		reg = (m_value >> 8) & 0xff;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_M_VID_1);
		reg = (m_value >> 16) & 0xff;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_M_VID_2);

		reg = n_value & 0xff;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_N_VID_0);
		reg = (n_value >> 8) & 0xff;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_N_VID_1);
		reg = (n_value >> 16) & 0xff;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_N_VID_2);
	पूर्ण अन्यथा  अणु
		reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_SYS_CTL_4);
		reg &= ~FIX_M_VID;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_SYS_CTL_4);

		ग_लिखोl(0x00, dp->reg_base + ANALOGIX_DP_N_VID_0);
		ग_लिखोl(0x80, dp->reg_base + ANALOGIX_DP_N_VID_1);
		ग_लिखोl(0x00, dp->reg_base + ANALOGIX_DP_N_VID_2);
	पूर्ण
पूर्ण

व्योम analogix_dp_set_video_timing_mode(काष्ठा analogix_dp_device *dp, u32 type)
अणु
	u32 reg;

	अगर (type == VIDEO_TIMING_FROM_CAPTURE) अणु
		reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_VIDEO_CTL_10);
		reg &= ~FORMAT_SEL;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_VIDEO_CTL_10);
	पूर्ण अन्यथा अणु
		reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_VIDEO_CTL_10);
		reg |= FORMAT_SEL;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_VIDEO_CTL_10);
	पूर्ण
पूर्ण

व्योम analogix_dp_enable_video_master(काष्ठा analogix_dp_device *dp, bool enable)
अणु
	u32 reg;

	अगर (enable) अणु
		reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_SOC_GENERAL_CTL);
		reg &= ~VIDEO_MODE_MASK;
		reg |= VIDEO_MASTER_MODE_EN | VIDEO_MODE_MASTER_MODE;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_SOC_GENERAL_CTL);
	पूर्ण अन्यथा अणु
		reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_SOC_GENERAL_CTL);
		reg &= ~VIDEO_MODE_MASK;
		reg |= VIDEO_MODE_SLAVE_MODE;
		ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_SOC_GENERAL_CTL);
	पूर्ण
पूर्ण

व्योम analogix_dp_start_video(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_VIDEO_CTL_1);
	reg |= VIDEO_EN;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_VIDEO_CTL_1);
पूर्ण

पूर्णांक analogix_dp_is_video_stream_on(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_SYS_CTL_3);
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_SYS_CTL_3);

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_SYS_CTL_3);
	अगर (!(reg & STRM_VALID)) अणु
		dev_dbg(dp->dev, "Input video stream is not detected.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम analogix_dp_config_video_slave_mode(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_FUNC_EN_1);
	अगर (dp->plat_data && is_rockchip(dp->plat_data->dev_type)) अणु
		reg &= ~(RK_VID_CAP_FUNC_EN_N | RK_VID_FIFO_FUNC_EN_N);
	पूर्ण अन्यथा अणु
		reg &= ~(MASTER_VID_FUNC_EN_N | SLAVE_VID_FUNC_EN_N);
		reg |= MASTER_VID_FUNC_EN_N;
	पूर्ण
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_FUNC_EN_1);

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_VIDEO_CTL_10);
	reg &= ~INTERACE_SCAN_CFG;
	reg |= (dp->video_info.पूर्णांकerlaced << 2);
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_VIDEO_CTL_10);

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_VIDEO_CTL_10);
	reg &= ~VSYNC_POLARITY_CFG;
	reg |= (dp->video_info.v_sync_polarity << 1);
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_VIDEO_CTL_10);

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_VIDEO_CTL_10);
	reg &= ~HSYNC_POLARITY_CFG;
	reg |= (dp->video_info.h_sync_polarity << 0);
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_VIDEO_CTL_10);

	reg = AUDIO_MODE_SPDIF_MODE | VIDEO_MODE_SLAVE_MODE;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_SOC_GENERAL_CTL);
पूर्ण

व्योम analogix_dp_enable_scrambling(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_TRAINING_PTN_SET);
	reg &= ~SCRAMBLING_DISABLE;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_TRAINING_PTN_SET);
पूर्ण

व्योम analogix_dp_disable_scrambling(काष्ठा analogix_dp_device *dp)
अणु
	u32 reg;

	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_TRAINING_PTN_SET);
	reg |= SCRAMBLING_DISABLE;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_TRAINING_PTN_SET);
पूर्ण

व्योम analogix_dp_enable_psr_crc(काष्ठा analogix_dp_device *dp)
अणु
	ग_लिखोl(PSR_VID_CRC_ENABLE, dp->reg_base + ANALOGIX_DP_CRC_CON);
पूर्ण

अटल sमाप_प्रकार analogix_dp_get_psr_status(काष्ठा analogix_dp_device *dp)
अणु
	sमाप_प्रकार val;
	u8 status;

	val = drm_dp_dpcd_पढ़ोb(&dp->aux, DP_PSR_STATUS, &status);
	अगर (val < 0) अणु
		dev_err(dp->dev, "PSR_STATUS read failed ret=%zd", val);
		वापस val;
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक analogix_dp_send_psr_spd(काष्ठा analogix_dp_device *dp,
			     काष्ठा dp_sdp *vsc, bool blocking)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	sमाप_प्रकार psr_status;

	/* करोn't send info frame */
	val = पढ़ोl(dp->reg_base + ANALOGIX_DP_PKT_SEND_CTL);
	val &= ~IF_EN;
	ग_लिखोl(val, dp->reg_base + ANALOGIX_DP_PKT_SEND_CTL);

	/* configure single frame update mode */
	ग_लिखोl(PSR_FRAME_UP_TYPE_BURST | PSR_CRC_SEL_HARDWARE,
	       dp->reg_base + ANALOGIX_DP_PSR_FRAME_UPDATE_CTRL);

	/* configure VSC HB0~HB3 */
	ग_लिखोl(vsc->sdp_header.HB0, dp->reg_base + ANALOGIX_DP_SPD_HB0);
	ग_लिखोl(vsc->sdp_header.HB1, dp->reg_base + ANALOGIX_DP_SPD_HB1);
	ग_लिखोl(vsc->sdp_header.HB2, dp->reg_base + ANALOGIX_DP_SPD_HB2);
	ग_लिखोl(vsc->sdp_header.HB3, dp->reg_base + ANALOGIX_DP_SPD_HB3);

	/* configure reused VSC PB0~PB3, magic number from venकरोr */
	ग_लिखोl(0x00, dp->reg_base + ANALOGIX_DP_SPD_PB0);
	ग_लिखोl(0x16, dp->reg_base + ANALOGIX_DP_SPD_PB1);
	ग_लिखोl(0xCE, dp->reg_base + ANALOGIX_DP_SPD_PB2);
	ग_लिखोl(0x5D, dp->reg_base + ANALOGIX_DP_SPD_PB3);

	/* configure DB0 / DB1 values */
	ग_लिखोl(vsc->db[0], dp->reg_base + ANALOGIX_DP_VSC_SHADOW_DB0);
	ग_लिखोl(vsc->db[1], dp->reg_base + ANALOGIX_DP_VSC_SHADOW_DB1);

	/* set reuse spd inक्रमframe */
	val = पढ़ोl(dp->reg_base + ANALOGIX_DP_VIDEO_CTL_3);
	val |= REUSE_SPD_EN;
	ग_लिखोl(val, dp->reg_base + ANALOGIX_DP_VIDEO_CTL_3);

	/* mark info frame update */
	val = पढ़ोl(dp->reg_base + ANALOGIX_DP_PKT_SEND_CTL);
	val = (val | IF_UP) & ~IF_EN;
	ग_लिखोl(val, dp->reg_base + ANALOGIX_DP_PKT_SEND_CTL);

	/* send info frame */
	val = पढ़ोl(dp->reg_base + ANALOGIX_DP_PKT_SEND_CTL);
	val |= IF_EN;
	ग_लिखोl(val, dp->reg_base + ANALOGIX_DP_PKT_SEND_CTL);

	अगर (!blocking)
		वापस 0;

	ret = पढ़ोx_poll_समयout(analogix_dp_get_psr_status, dp, psr_status,
		psr_status >= 0 &&
		((vsc->db[1] && psr_status == DP_PSR_SINK_ACTIVE_RFB) ||
		(!vsc->db[1] && psr_status == DP_PSR_SINK_INACTIVE)), 1500,
		DP_TIMEOUT_PSR_LOOP_MS * 1000);
	अगर (ret) अणु
		dev_warn(dp->dev, "Failed to apply PSR %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

sमाप_प्रकार analogix_dp_transfer(काष्ठा analogix_dp_device *dp,
			     काष्ठा drm_dp_aux_msg *msg)
अणु
	u32 reg;
	u32 status_reg;
	u8 *buffer = msg->buffer;
	अचिन्हित पूर्णांक i;
	पूर्णांक num_transferred = 0;
	पूर्णांक ret;

	/* Buffer size of AUX CH is 16 bytes */
	अगर (WARN_ON(msg->size > 16))
		वापस -E2BIG;

	/* Clear AUX CH data buffer */
	reg = BUF_CLR;
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_BUFFER_DATA_CTL);

	चयन (msg->request & ~DP_AUX_I2C_MOT) अणु
	हाल DP_AUX_I2C_WRITE:
		reg = AUX_TX_COMM_WRITE | AUX_TX_COMM_I2C_TRANSACTION;
		अगर (msg->request & DP_AUX_I2C_MOT)
			reg |= AUX_TX_COMM_MOT;
		अवरोध;

	हाल DP_AUX_I2C_READ:
		reg = AUX_TX_COMM_READ | AUX_TX_COMM_I2C_TRANSACTION;
		अगर (msg->request & DP_AUX_I2C_MOT)
			reg |= AUX_TX_COMM_MOT;
		अवरोध;

	हाल DP_AUX_NATIVE_WRITE:
		reg = AUX_TX_COMM_WRITE | AUX_TX_COMM_DP_TRANSACTION;
		अवरोध;

	हाल DP_AUX_NATIVE_READ:
		reg = AUX_TX_COMM_READ | AUX_TX_COMM_DP_TRANSACTION;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	reg |= AUX_LENGTH(msg->size);
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_AUX_CH_CTL_1);

	/* Select DPCD device address */
	reg = AUX_ADDR_7_0(msg->address);
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_AUX_ADDR_7_0);
	reg = AUX_ADDR_15_8(msg->address);
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_AUX_ADDR_15_8);
	reg = AUX_ADDR_19_16(msg->address);
	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_AUX_ADDR_19_16);

	अगर (!(msg->request & DP_AUX_I2C_READ)) अणु
		क्रम (i = 0; i < msg->size; i++) अणु
			reg = buffer[i];
			ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_BUF_DATA_0 +
			       4 * i);
			num_transferred++;
		पूर्ण
	पूर्ण

	/* Enable AUX CH operation */
	reg = AUX_EN;

	/* Zero-sized messages specअगरy address-only transactions. */
	अगर (msg->size < 1)
		reg |= ADDR_ONLY;

	ग_लिखोl(reg, dp->reg_base + ANALOGIX_DP_AUX_CH_CTL_2);

	ret = पढ़ोx_poll_समयout(पढ़ोl, dp->reg_base + ANALOGIX_DP_AUX_CH_CTL_2,
				 reg, !(reg & AUX_EN), 25, 500 * 1000);
	अगर (ret) अणु
		dev_err(dp->dev, "AUX CH enable timeout!\n");
		जाओ aux_error;
	पूर्ण

	/* TODO: Wait क्रम an पूर्णांकerrupt instead of looping? */
	/* Is AUX CH command reply received? */
	ret = पढ़ोx_poll_समयout(पढ़ोl, dp->reg_base + ANALOGIX_DP_INT_STA,
				 reg, reg & RPLY_RECEIV, 10, 20 * 1000);
	अगर (ret) अणु
		dev_err(dp->dev, "AUX CH cmd reply timeout!\n");
		जाओ aux_error;
	पूर्ण

	/* Clear पूर्णांकerrupt source क्रम AUX CH command reply */
	ग_लिखोl(RPLY_RECEIV, dp->reg_base + ANALOGIX_DP_INT_STA);

	/* Clear पूर्णांकerrupt source क्रम AUX CH access error */
	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_INT_STA);
	status_reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_AUX_CH_STA);
	अगर ((reg & AUX_ERR) || (status_reg & AUX_STATUS_MASK)) अणु
		ग_लिखोl(AUX_ERR, dp->reg_base + ANALOGIX_DP_INT_STA);

		dev_warn(dp->dev, "AUX CH error happened: %#x (%d)\n",
			 status_reg & AUX_STATUS_MASK, !!(reg & AUX_ERR));
		जाओ aux_error;
	पूर्ण

	अगर (msg->request & DP_AUX_I2C_READ) अणु
		क्रम (i = 0; i < msg->size; i++) अणु
			reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_BUF_DATA_0 +
				    4 * i);
			buffer[i] = (अचिन्हित अक्षर)reg;
			num_transferred++;
		पूर्ण
	पूर्ण

	/* Check अगर Rx sends defer */
	reg = पढ़ोl(dp->reg_base + ANALOGIX_DP_AUX_RX_COMM);
	अगर (reg == AUX_RX_COMM_AUX_DEFER)
		msg->reply = DP_AUX_NATIVE_REPLY_DEFER;
	अन्यथा अगर (reg == AUX_RX_COMM_I2C_DEFER)
		msg->reply = DP_AUX_I2C_REPLY_DEFER;
	अन्यथा अगर ((msg->request & ~DP_AUX_I2C_MOT) == DP_AUX_I2C_WRITE ||
		 (msg->request & ~DP_AUX_I2C_MOT) == DP_AUX_I2C_READ)
		msg->reply = DP_AUX_I2C_REPLY_ACK;
	अन्यथा अगर ((msg->request & ~DP_AUX_I2C_MOT) == DP_AUX_NATIVE_WRITE ||
		 (msg->request & ~DP_AUX_I2C_MOT) == DP_AUX_NATIVE_READ)
		msg->reply = DP_AUX_NATIVE_REPLY_ACK;

	वापस num_transferred > 0 ? num_transferred : -EBUSY;

aux_error:
	/* अगर aux err happen, reset aux */
	analogix_dp_init_aux(dp);

	वापस -EREMOTEIO;
पूर्ण
