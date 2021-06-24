<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2017 Rockchip Electronics Co. Ltd.
 *
 * Author: Zheng Yang <zhengyang@rock-chips.com>
 *         Heiko Stuebner <heiko@sntech.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/slab.h>

#घोषणा UPDATE(x, h, l)		(((x) << (l)) & GENMASK((h), (l)))

/* REG: 0x00 */
#घोषणा RK3228_PRE_PLL_REFCLK_SEL_PCLK			BIT(0)
/* REG: 0x01 */
#घोषणा RK3228_BYPASS_RXSENSE_EN			BIT(2)
#घोषणा RK3228_BYPASS_PWRON_EN				BIT(1)
#घोषणा RK3228_BYPASS_PLLPD_EN				BIT(0)
/* REG: 0x02 */
#घोषणा RK3228_BYPASS_PDATA_EN				BIT(4)
#घोषणा RK3228_PDATAEN_DISABLE				BIT(0)
/* REG: 0x03 */
#घोषणा RK3228_BYPASS_AUTO_TERM_RES_CAL			BIT(7)
#घोषणा RK3228_AUTO_TERM_RES_CAL_SPEED_14_8(x)		UPDATE(x, 6, 0)
/* REG: 0x04 */
#घोषणा RK3228_AUTO_TERM_RES_CAL_SPEED_7_0(x)		UPDATE(x, 7, 0)
/* REG: 0xaa */
#घोषणा RK3228_POST_PLL_CTRL_MANUAL			BIT(0)
/* REG: 0xe0 */
#घोषणा RK3228_POST_PLL_POWER_DOWN			BIT(5)
#घोषणा RK3228_PRE_PLL_POWER_DOWN			BIT(4)
#घोषणा RK3228_RXSENSE_CLK_CH_ENABLE			BIT(3)
#घोषणा RK3228_RXSENSE_DATA_CH2_ENABLE			BIT(2)
#घोषणा RK3228_RXSENSE_DATA_CH1_ENABLE			BIT(1)
#घोषणा RK3228_RXSENSE_DATA_CH0_ENABLE			BIT(0)
/* REG: 0xe1 */
#घोषणा RK3228_BANDGAP_ENABLE				BIT(4)
#घोषणा RK3228_TMDS_DRIVER_ENABLE			GENMASK(3, 0)
/* REG: 0xe2 */
#घोषणा RK3228_PRE_PLL_FB_DIV_8_MASK			BIT(7)
#घोषणा RK3228_PRE_PLL_FB_DIV_8(x)			UPDATE((x) >> 8, 7, 7)
#घोषणा RK3228_PCLK_VCO_DIV_5_MASK			BIT(5)
#घोषणा RK3228_PCLK_VCO_DIV_5(x)			UPDATE(x, 5, 5)
#घोषणा RK3228_PRE_PLL_PRE_DIV_MASK			GENMASK(4, 0)
#घोषणा RK3228_PRE_PLL_PRE_DIV(x)			UPDATE(x, 4, 0)
/* REG: 0xe3 */
#घोषणा RK3228_PRE_PLL_FB_DIV_7_0(x)			UPDATE(x, 7, 0)
/* REG: 0xe4 */
#घोषणा RK3228_PRE_PLL_PCLK_DIV_B_MASK			GENMASK(6, 5)
#घोषणा RK3228_PRE_PLL_PCLK_DIV_B_SHIFT			5
#घोषणा RK3228_PRE_PLL_PCLK_DIV_B(x)			UPDATE(x, 6, 5)
#घोषणा RK3228_PRE_PLL_PCLK_DIV_A_MASK			GENMASK(4, 0)
#घोषणा RK3228_PRE_PLL_PCLK_DIV_A(x)			UPDATE(x, 4, 0)
/* REG: 0xe5 */
#घोषणा RK3228_PRE_PLL_PCLK_DIV_C_MASK			GENMASK(6, 5)
#घोषणा RK3228_PRE_PLL_PCLK_DIV_C(x)			UPDATE(x, 6, 5)
#घोषणा RK3228_PRE_PLL_PCLK_DIV_D_MASK			GENMASK(4, 0)
#घोषणा RK3228_PRE_PLL_PCLK_DIV_D(x)			UPDATE(x, 4, 0)
/* REG: 0xe6 */
#घोषणा RK3228_PRE_PLL_TMDSCLK_DIV_C_MASK		GENMASK(5, 4)
#घोषणा RK3228_PRE_PLL_TMDSCLK_DIV_C(x)			UPDATE(x, 5, 4)
#घोषणा RK3228_PRE_PLL_TMDSCLK_DIV_A_MASK		GENMASK(3, 2)
#घोषणा RK3228_PRE_PLL_TMDSCLK_DIV_A(x)			UPDATE(x, 3, 2)
#घोषणा RK3228_PRE_PLL_TMDSCLK_DIV_B_MASK		GENMASK(1, 0)
#घोषणा RK3228_PRE_PLL_TMDSCLK_DIV_B(x)			UPDATE(x, 1, 0)
/* REG: 0xe8 */
#घोषणा RK3228_PRE_PLL_LOCK_STATUS			BIT(0)
/* REG: 0xe9 */
#घोषणा RK3228_POST_PLL_POST_DIV_ENABLE			UPDATE(3, 7, 6)
#घोषणा RK3228_POST_PLL_PRE_DIV_MASK			GENMASK(4, 0)
#घोषणा RK3228_POST_PLL_PRE_DIV(x)			UPDATE(x, 4, 0)
/* REG: 0xea */
#घोषणा RK3228_POST_PLL_FB_DIV_7_0(x)			UPDATE(x, 7, 0)
/* REG: 0xeb */
#घोषणा RK3228_POST_PLL_FB_DIV_8_MASK			BIT(7)
#घोषणा RK3228_POST_PLL_FB_DIV_8(x)			UPDATE((x) >> 8, 7, 7)
#घोषणा RK3228_POST_PLL_POST_DIV_MASK			GENMASK(5, 4)
#घोषणा RK3228_POST_PLL_POST_DIV(x)			UPDATE(x, 5, 4)
#घोषणा RK3228_POST_PLL_LOCK_STATUS			BIT(0)
/* REG: 0xee */
#घोषणा RK3228_TMDS_CH_TA_ENABLE			GENMASK(7, 4)
/* REG: 0xef */
#घोषणा RK3228_TMDS_CLK_CH_TA(x)			UPDATE(x, 7, 6)
#घोषणा RK3228_TMDS_DATA_CH2_TA(x)			UPDATE(x, 5, 4)
#घोषणा RK3228_TMDS_DATA_CH1_TA(x)			UPDATE(x, 3, 2)
#घोषणा RK3228_TMDS_DATA_CH0_TA(x)			UPDATE(x, 1, 0)
/* REG: 0xf0 */
#घोषणा RK3228_TMDS_DATA_CH2_PRE_EMPHASIS_MASK		GENMASK(5, 4)
#घोषणा RK3228_TMDS_DATA_CH2_PRE_EMPHASIS(x)		UPDATE(x, 5, 4)
#घोषणा RK3228_TMDS_DATA_CH1_PRE_EMPHASIS_MASK		GENMASK(3, 2)
#घोषणा RK3228_TMDS_DATA_CH1_PRE_EMPHASIS(x)		UPDATE(x, 3, 2)
#घोषणा RK3228_TMDS_DATA_CH0_PRE_EMPHASIS_MASK		GENMASK(1, 0)
#घोषणा RK3228_TMDS_DATA_CH0_PRE_EMPHASIS(x)		UPDATE(x, 1, 0)
/* REG: 0xf1 */
#घोषणा RK3228_TMDS_CLK_CH_OUTPUT_SWING(x)		UPDATE(x, 7, 4)
#घोषणा RK3228_TMDS_DATA_CH2_OUTPUT_SWING(x)		UPDATE(x, 3, 0)
/* REG: 0xf2 */
#घोषणा RK3228_TMDS_DATA_CH1_OUTPUT_SWING(x)		UPDATE(x, 7, 4)
#घोषणा RK3228_TMDS_DATA_CH0_OUTPUT_SWING(x)		UPDATE(x, 3, 0)

/* REG: 0x01 */
#घोषणा RK3328_BYPASS_RXSENSE_EN			BIT(2)
#घोषणा RK3328_BYPASS_POWERON_EN			BIT(1)
#घोषणा RK3328_BYPASS_PLLPD_EN				BIT(0)
/* REG: 0x02 */
#घोषणा RK3328_INT_POL_HIGH				BIT(7)
#घोषणा RK3328_BYPASS_PDATA_EN				BIT(4)
#घोषणा RK3328_PDATA_EN					BIT(0)
/* REG:0x05 */
#घोषणा RK3328_INT_TMDS_CLK(x)				UPDATE(x, 7, 4)
#घोषणा RK3328_INT_TMDS_D2(x)				UPDATE(x, 3, 0)
/* REG:0x07 */
#घोषणा RK3328_INT_TMDS_D1(x)				UPDATE(x, 7, 4)
#घोषणा RK3328_INT_TMDS_D0(x)				UPDATE(x, 3, 0)
/* क्रम all RK3328_INT_TMDS_*, ESD_DET as defined in 0xc8-0xcb */
#घोषणा RK3328_INT_AGND_LOW_PULSE_LOCKED		BIT(3)
#घोषणा RK3328_INT_RXSENSE_LOW_PULSE_LOCKED		BIT(2)
#घोषणा RK3328_INT_VSS_AGND_ESD_DET			BIT(1)
#घोषणा RK3328_INT_AGND_VSS_ESD_DET			BIT(0)
/* REG: 0xa0 */
#घोषणा RK3328_PCLK_VCO_DIV_5_MASK			BIT(1)
#घोषणा RK3328_PCLK_VCO_DIV_5(x)			UPDATE(x, 1, 1)
#घोषणा RK3328_PRE_PLL_POWER_DOWN			BIT(0)
/* REG: 0xa1 */
#घोषणा RK3328_PRE_PLL_PRE_DIV_MASK			GENMASK(5, 0)
#घोषणा RK3328_PRE_PLL_PRE_DIV(x)			UPDATE(x, 5, 0)
/* REG: 0xa2 */
/* unset means center spपढ़ो */
#घोषणा RK3328_SPREAD_SPECTRUM_MOD_DOWN			BIT(7)
#घोषणा RK3328_SPREAD_SPECTRUM_MOD_DISABLE		BIT(6)
#घोषणा RK3328_PRE_PLL_FRAC_DIV_DISABLE			UPDATE(3, 5, 4)
#घोषणा RK3328_PRE_PLL_FB_DIV_11_8_MASK			GENMASK(3, 0)
#घोषणा RK3328_PRE_PLL_FB_DIV_11_8(x)			UPDATE((x) >> 8, 3, 0)
/* REG: 0xa3 */
#घोषणा RK3328_PRE_PLL_FB_DIV_7_0(x)			UPDATE(x, 7, 0)
/* REG: 0xa4*/
#घोषणा RK3328_PRE_PLL_TMDSCLK_DIV_C_MASK		GENMASK(1, 0)
#घोषणा RK3328_PRE_PLL_TMDSCLK_DIV_C(x)			UPDATE(x, 1, 0)
#घोषणा RK3328_PRE_PLL_TMDSCLK_DIV_B_MASK		GENMASK(3, 2)
#घोषणा RK3328_PRE_PLL_TMDSCLK_DIV_B(x)			UPDATE(x, 3, 2)
#घोषणा RK3328_PRE_PLL_TMDSCLK_DIV_A_MASK		GENMASK(5, 4)
#घोषणा RK3328_PRE_PLL_TMDSCLK_DIV_A(x)			UPDATE(x, 5, 4)
/* REG: 0xa5 */
#घोषणा RK3328_PRE_PLL_PCLK_DIV_B_SHIFT			5
#घोषणा RK3328_PRE_PLL_PCLK_DIV_B_MASK			GENMASK(6, 5)
#घोषणा RK3328_PRE_PLL_PCLK_DIV_B(x)			UPDATE(x, 6, 5)
#घोषणा RK3328_PRE_PLL_PCLK_DIV_A_MASK			GENMASK(4, 0)
#घोषणा RK3328_PRE_PLL_PCLK_DIV_A(x)			UPDATE(x, 4, 0)
/* REG: 0xa6 */
#घोषणा RK3328_PRE_PLL_PCLK_DIV_C_SHIFT			5
#घोषणा RK3328_PRE_PLL_PCLK_DIV_C_MASK			GENMASK(6, 5)
#घोषणा RK3328_PRE_PLL_PCLK_DIV_C(x)			UPDATE(x, 6, 5)
#घोषणा RK3328_PRE_PLL_PCLK_DIV_D_MASK			GENMASK(4, 0)
#घोषणा RK3328_PRE_PLL_PCLK_DIV_D(x)			UPDATE(x, 4, 0)
/* REG: 0xa9 */
#घोषणा RK3328_PRE_PLL_LOCK_STATUS			BIT(0)
/* REG: 0xaa */
#घोषणा RK3328_POST_PLL_POST_DIV_ENABLE			GENMASK(3, 2)
#घोषणा RK3328_POST_PLL_REFCLK_SEL_TMDS			BIT(1)
#घोषणा RK3328_POST_PLL_POWER_DOWN			BIT(0)
/* REG:0xab */
#घोषणा RK3328_POST_PLL_FB_DIV_8(x)			UPDATE((x) >> 8, 7, 7)
#घोषणा RK3328_POST_PLL_PRE_DIV(x)			UPDATE(x, 4, 0)
/* REG: 0xac */
#घोषणा RK3328_POST_PLL_FB_DIV_7_0(x)			UPDATE(x, 7, 0)
/* REG: 0xad */
#घोषणा RK3328_POST_PLL_POST_DIV_MASK			GENMASK(1, 0)
#घोषणा RK3328_POST_PLL_POST_DIV_2			0x0
#घोषणा RK3328_POST_PLL_POST_DIV_4			0x1
#घोषणा RK3328_POST_PLL_POST_DIV_8			0x3
/* REG: 0xaf */
#घोषणा RK3328_POST_PLL_LOCK_STATUS			BIT(0)
/* REG: 0xb0 */
#घोषणा RK3328_BANDGAP_ENABLE				BIT(2)
/* REG: 0xb2 */
#घोषणा RK3328_TMDS_CLK_DRIVER_EN			BIT(3)
#घोषणा RK3328_TMDS_D2_DRIVER_EN			BIT(2)
#घोषणा RK3328_TMDS_D1_DRIVER_EN			BIT(1)
#घोषणा RK3328_TMDS_D0_DRIVER_EN			BIT(0)
#घोषणा RK3328_TMDS_DRIVER_ENABLE		(RK3328_TMDS_CLK_DRIVER_EN | \
						RK3328_TMDS_D2_DRIVER_EN | \
						RK3328_TMDS_D1_DRIVER_EN | \
						RK3328_TMDS_D0_DRIVER_EN)
/* REG:0xc5 */
#घोषणा RK3328_BYPASS_TERM_RESISTOR_CALIB		BIT(7)
#घोषणा RK3328_TERM_RESISTOR_CALIB_SPEED_14_8(x)	UPDATE((x) >> 8, 6, 0)
/* REG:0xc6 */
#घोषणा RK3328_TERM_RESISTOR_CALIB_SPEED_7_0(x)		UPDATE(x, 7, 0)
/* REG:0xc7 */
#घोषणा RK3328_TERM_RESISTOR_50				UPDATE(0, 2, 1)
#घोषणा RK3328_TERM_RESISTOR_62_5			UPDATE(1, 2, 1)
#घोषणा RK3328_TERM_RESISTOR_75				UPDATE(2, 2, 1)
#घोषणा RK3328_TERM_RESISTOR_100			UPDATE(3, 2, 1)
/* REG 0xc8 - 0xcb */
#घोषणा RK3328_ESD_DETECT_MASK				GENMASK(7, 6)
#घोषणा RK3328_ESD_DETECT_340MV				(0x0 << 6)
#घोषणा RK3328_ESD_DETECT_280MV				(0x1 << 6)
#घोषणा RK3328_ESD_DETECT_260MV				(0x2 << 6)
#घोषणा RK3328_ESD_DETECT_240MV				(0x3 << 6)
/* resistors can be used in parallel */
#घोषणा RK3328_TMDS_TERM_RESIST_MASK			GENMASK(5, 0)
#घोषणा RK3328_TMDS_TERM_RESIST_75			BIT(5)
#घोषणा RK3328_TMDS_TERM_RESIST_150			BIT(4)
#घोषणा RK3328_TMDS_TERM_RESIST_300			BIT(3)
#घोषणा RK3328_TMDS_TERM_RESIST_600			BIT(2)
#घोषणा RK3328_TMDS_TERM_RESIST_1000			BIT(1)
#घोषणा RK3328_TMDS_TERM_RESIST_2000			BIT(0)
/* REG: 0xd1 */
#घोषणा RK3328_PRE_PLL_FRAC_DIV_23_16(x)		UPDATE((x) >> 16, 7, 0)
/* REG: 0xd2 */
#घोषणा RK3328_PRE_PLL_FRAC_DIV_15_8(x)			UPDATE((x) >> 8, 7, 0)
/* REG: 0xd3 */
#घोषणा RK3328_PRE_PLL_FRAC_DIV_7_0(x)			UPDATE(x, 7, 0)

काष्ठा inno_hdmi_phy_drv_data;

काष्ठा inno_hdmi_phy अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	पूर्णांक irq;

	काष्ठा phy *phy;
	काष्ठा clk *sysclk;
	काष्ठा clk *refoclk;
	काष्ठा clk *refpclk;

	/* platक्रमm data */
	स्थिर काष्ठा inno_hdmi_phy_drv_data *plat_data;
	पूर्णांक chip_version;

	/* clk provider */
	काष्ठा clk_hw hw;
	काष्ठा clk *phyclk;
	अचिन्हित दीर्घ pixघड़ी;
पूर्ण;

काष्ठा pre_pll_config अणु
	अचिन्हित दीर्घ pixघड़ी;
	अचिन्हित दीर्घ पंचांगdsघड़ी;
	u8 preभाग;
	u16 fbभाग;
	u8 पंचांगds_भाग_a;
	u8 पंचांगds_भाग_b;
	u8 पंचांगds_भाग_c;
	u8 pclk_भाग_a;
	u8 pclk_भाग_b;
	u8 pclk_भाग_c;
	u8 pclk_भाग_d;
	u8 vco_भाग_5_en;
	u32 fracभाग;
पूर्ण;

काष्ठा post_pll_config अणु
	अचिन्हित दीर्घ पंचांगdsघड़ी;
	u8 preभाग;
	u16 fbभाग;
	u8 postभाग;
	u8 version;
पूर्ण;

काष्ठा phy_config अणु
	अचिन्हित दीर्घ	पंचांगdsघड़ी;
	u8		regs[14];
पूर्ण;

काष्ठा inno_hdmi_phy_ops अणु
	पूर्णांक (*init)(काष्ठा inno_hdmi_phy *inno);
	पूर्णांक (*घातer_on)(काष्ठा inno_hdmi_phy *inno,
			स्थिर काष्ठा post_pll_config *cfg,
			स्थिर काष्ठा phy_config *phy_cfg);
	व्योम (*घातer_off)(काष्ठा inno_hdmi_phy *inno);
पूर्ण;

काष्ठा inno_hdmi_phy_drv_data अणु
	स्थिर काष्ठा inno_hdmi_phy_ops	*ops;
	स्थिर काष्ठा clk_ops		*clk_ops;
	स्थिर काष्ठा phy_config		*phy_cfg_table;
पूर्ण;

अटल स्थिर काष्ठा pre_pll_config pre_pll_cfg_table[] = अणु
	अणु 27000000,  27000000, 1,  90, 3, 2, 2, 10, 3, 3, 4, 0, 0पूर्ण,
	अणु 27000000,  33750000, 1,  90, 1, 3, 3, 10, 3, 3, 4, 0, 0पूर्ण,
	अणु 40000000,  40000000, 1,  80, 2, 2, 2, 12, 2, 2, 2, 0, 0पूर्ण,
	अणु 59341000,  59341000, 1,  98, 3, 1, 2,  1, 3, 3, 4, 0, 0xE6AE6Bपूर्ण,
	अणु 59400000,  59400000, 1,  99, 3, 1, 1,  1, 3, 3, 4, 0, 0पूर्ण,
	अणु 59341000,  74176250, 1,  98, 0, 3, 3,  1, 3, 3, 4, 0, 0xE6AE6Bपूर्ण,
	अणु 59400000,  74250000, 1,  99, 1, 2, 2,  1, 3, 3, 4, 0, 0पूर्ण,
	अणु 74176000,  74176000, 1,  98, 1, 2, 2,  1, 2, 3, 4, 0, 0xE6AE6Bपूर्ण,
	अणु 74250000,  74250000, 1,  99, 1, 2, 2,  1, 2, 3, 4, 0, 0पूर्ण,
	अणु 74176000,  92720000, 4, 494, 1, 2, 2,  1, 3, 3, 4, 0, 0x816817पूर्ण,
	अणु 74250000,  92812500, 4, 495, 1, 2, 2,  1, 3, 3, 4, 0, 0पूर्ण,
	अणु148352000, 148352000, 1,  98, 1, 1, 1,  1, 2, 2, 2, 0, 0xE6AE6Bपूर्ण,
	अणु148500000, 148500000, 1,  99, 1, 1, 1,  1, 2, 2, 2, 0, 0पूर्ण,
	अणु148352000, 185440000, 4, 494, 0, 2, 2,  1, 3, 2, 2, 0, 0x816817पूर्ण,
	अणु148500000, 185625000, 4, 495, 0, 2, 2,  1, 3, 2, 2, 0, 0पूर्ण,
	अणु296703000, 296703000, 1,  98, 0, 1, 1,  1, 0, 2, 2, 0, 0xE6AE6Bपूर्ण,
	अणु297000000, 297000000, 1,  99, 0, 1, 1,  1, 0, 2, 2, 0, 0पूर्ण,
	अणु296703000, 370878750, 4, 494, 1, 2, 0,  1, 3, 1, 1, 0, 0x816817पूर्ण,
	अणु297000000, 371250000, 4, 495, 1, 2, 0,  1, 3, 1, 1, 0, 0पूर्ण,
	अणु593407000, 296703500, 1,  98, 0, 1, 1,  1, 0, 2, 1, 0, 0xE6AE6Bपूर्ण,
	अणु594000000, 297000000, 1,  99, 0, 1, 1,  1, 0, 2, 1, 0, 0पूर्ण,
	अणु593407000, 370879375, 4, 494, 1, 2, 0,  1, 3, 1, 1, 1, 0x816817पूर्ण,
	अणु594000000, 371250000, 4, 495, 1, 2, 0,  1, 3, 1, 1, 1, 0पूर्ण,
	अणु593407000, 593407000, 1,  98, 0, 2, 0,  1, 0, 1, 1, 0, 0xE6AE6Bपूर्ण,
	अणु594000000, 594000000, 1,  99, 0, 2, 0,  1, 0, 1, 1, 0, 0पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा post_pll_config post_pll_cfg_table[] = अणु
	अणु33750000,  1, 40, 8, 1पूर्ण,
	अणु33750000,  1, 80, 8, 2पूर्ण,
	अणु74250000,  1, 40, 8, 1पूर्ण,
	अणु74250000, 18, 80, 8, 2पूर्ण,
	अणु148500000, 2, 40, 4, 3पूर्ण,
	अणु297000000, 4, 40, 2, 3पूर्ण,
	अणु594000000, 8, 40, 1, 3पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

/* phy tuning values क्रम an unकरोcumented set of रेजिस्टरs */
अटल स्थिर काष्ठा phy_config rk3228_phy_cfg[] = अणु
	अणु	165000000, अणु
			0xaa, 0x00, 0x44, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00,
		पूर्ण,
	पूर्ण, अणु
		340000000, अणु
			0xaa, 0x15, 0x6a, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00,
		पूर्ण,
	पूर्ण, अणु
		594000000, अणु
			0xaa, 0x15, 0x7a, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00,
		पूर्ण,
	पूर्ण, अणु /* sentinel */ पूर्ण,
पूर्ण;

/* phy tuning values क्रम an unकरोcumented set of रेजिस्टरs */
अटल स्थिर काष्ठा phy_config rk3328_phy_cfg[] = अणु
	अणु	165000000, अणु
			0x07, 0x0a, 0x0a, 0x0a, 0x00, 0x00, 0x08, 0x08, 0x08,
			0x00, 0xac, 0xcc, 0xcc, 0xcc,
		पूर्ण,
	पूर्ण, अणु
		340000000, अणु
			0x0b, 0x0d, 0x0d, 0x0d, 0x07, 0x15, 0x08, 0x08, 0x08,
			0x3f, 0xac, 0xcc, 0xcd, 0xdd,
		पूर्ण,
	पूर्ण, अणु
		594000000, अणु
			0x10, 0x1a, 0x1a, 0x1a, 0x07, 0x15, 0x08, 0x08, 0x08,
			0x00, 0xac, 0xcc, 0xcc, 0xcc,
		पूर्ण,
	पूर्ण, अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा inno_hdmi_phy *to_inno_hdmi_phy(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा inno_hdmi_phy, hw);
पूर्ण

/*
 * The रेजिस्टर description of the IP block करोes not use any distinct names
 * but instead the databook simply numbers the रेजिस्टरs in one-increments.
 * As the रेजिस्टरs are obviously 32bit sized, the inno_* functions
 * translate the databook रेजिस्टर names to the actual रेजिस्टरs addresses.
 */
अटल अंतरभूत व्योम inno_ग_लिखो(काष्ठा inno_hdmi_phy *inno, u32 reg, u8 val)
अणु
	regmap_ग_लिखो(inno->regmap, reg * 4, val);
पूर्ण

अटल अंतरभूत u8 inno_पढ़ो(काष्ठा inno_hdmi_phy *inno, u32 reg)
अणु
	u32 val;

	regmap_पढ़ो(inno->regmap, reg * 4, &val);

	वापस val;
पूर्ण

अटल अंतरभूत व्योम inno_update_bits(काष्ठा inno_hdmi_phy *inno, u8 reg,
				    u8 mask, u8 val)
अणु
	regmap_update_bits(inno->regmap, reg * 4, mask, val);
पूर्ण

#घोषणा inno_poll(inno, reg, val, cond, sleep_us, समयout_us) \
	regmap_पढ़ो_poll_समयout((inno)->regmap, (reg) * 4, val, cond, \
				 sleep_us, समयout_us)

अटल अचिन्हित दीर्घ inno_hdmi_phy_get_पंचांगdsclk(काष्ठा inno_hdmi_phy *inno,
					       अचिन्हित दीर्घ rate)
अणु
	पूर्णांक bus_width = phy_get_bus_width(inno->phy);

	चयन (bus_width) अणु
	हाल 4:
	हाल 5:
	हाल 6:
	हाल 10:
	हाल 12:
	हाल 16:
		वापस (u64)rate * bus_width / 8;
	शेष:
		वापस rate;
	पूर्ण
पूर्ण

अटल irqवापस_t inno_hdmi_phy_rk3328_hardirq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा inno_hdmi_phy *inno = dev_id;
	पूर्णांक पूर्णांकr_stat1, पूर्णांकr_stat2, पूर्णांकr_stat3;

	पूर्णांकr_stat1 = inno_पढ़ो(inno, 0x04);
	पूर्णांकr_stat2 = inno_पढ़ो(inno, 0x06);
	पूर्णांकr_stat3 = inno_पढ़ो(inno, 0x08);

	अगर (पूर्णांकr_stat1)
		inno_ग_लिखो(inno, 0x04, पूर्णांकr_stat1);
	अगर (पूर्णांकr_stat2)
		inno_ग_लिखो(inno, 0x06, पूर्णांकr_stat2);
	अगर (पूर्णांकr_stat3)
		inno_ग_लिखो(inno, 0x08, पूर्णांकr_stat3);

	अगर (पूर्णांकr_stat1 || पूर्णांकr_stat2 || पूर्णांकr_stat3)
		वापस IRQ_WAKE_THREAD;

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t inno_hdmi_phy_rk3328_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा inno_hdmi_phy *inno = dev_id;

	inno_update_bits(inno, 0x02, RK3328_PDATA_EN, 0);
	usleep_range(10, 20);
	inno_update_bits(inno, 0x02, RK3328_PDATA_EN, RK3328_PDATA_EN);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक inno_hdmi_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा inno_hdmi_phy *inno = phy_get_drvdata(phy);
	स्थिर काष्ठा post_pll_config *cfg = post_pll_cfg_table;
	स्थिर काष्ठा phy_config *phy_cfg = inno->plat_data->phy_cfg_table;
	अचिन्हित दीर्घ पंचांगdsघड़ी = inno_hdmi_phy_get_पंचांगdsclk(inno,
							    inno->pixघड़ी);
	पूर्णांक ret;

	अगर (!पंचांगdsघड़ी) अणु
		dev_err(inno->dev, "TMDS clock is zero!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!inno->plat_data->ops->घातer_on)
		वापस -EINVAL;

	क्रम (; cfg->पंचांगdsघड़ी != 0; cfg++)
		अगर (पंचांगdsघड़ी <= cfg->पंचांगdsघड़ी &&
		    cfg->version & inno->chip_version)
			अवरोध;

	क्रम (; phy_cfg->पंचांगdsघड़ी != 0; phy_cfg++)
		अगर (पंचांगdsघड़ी <= phy_cfg->पंचांगdsघड़ी)
			अवरोध;

	अगर (cfg->पंचांगdsघड़ी == 0 || phy_cfg->पंचांगdsघड़ी == 0)
		वापस -EINVAL;

	dev_dbg(inno->dev, "Inno HDMI PHY Power On\n");

	ret = clk_prepare_enable(inno->phyclk);
	अगर (ret)
		वापस ret;

	ret = inno->plat_data->ops->घातer_on(inno, cfg, phy_cfg);
	अगर (ret) अणु
		clk_disable_unprepare(inno->phyclk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inno_hdmi_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा inno_hdmi_phy *inno = phy_get_drvdata(phy);

	अगर (!inno->plat_data->ops->घातer_off)
		वापस -EINVAL;

	inno->plat_data->ops->घातer_off(inno);

	clk_disable_unprepare(inno->phyclk);

	dev_dbg(inno->dev, "Inno HDMI PHY Power Off\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops inno_hdmi_phy_ops = अणु
	.owner = THIS_MODULE,
	.घातer_on = inno_hdmi_phy_घातer_on,
	.घातer_off = inno_hdmi_phy_घातer_off,
पूर्ण;

अटल स्थिर
काष्ठा pre_pll_config *inno_hdmi_phy_get_pre_pll_cfg(काष्ठा inno_hdmi_phy *inno,
						     अचिन्हित दीर्घ rate)
अणु
	स्थिर काष्ठा pre_pll_config *cfg = pre_pll_cfg_table;
	अचिन्हित दीर्घ पंचांगdsघड़ी = inno_hdmi_phy_get_पंचांगdsclk(inno, rate);

	क्रम (; cfg->pixघड़ी != 0; cfg++)
		अगर (cfg->pixघड़ी == rate && cfg->पंचांगdsघड़ी == पंचांगdsघड़ी)
			अवरोध;

	अगर (cfg->pixघड़ी == 0)
		वापस ERR_PTR(-EINVAL);

	वापस cfg;
पूर्ण

अटल पूर्णांक inno_hdmi_phy_rk3228_clk_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);
	u8 status;

	status = inno_पढ़ो(inno, 0xe0) & RK3228_PRE_PLL_POWER_DOWN;
	वापस status ? 0 : 1;
पूर्ण

अटल पूर्णांक inno_hdmi_phy_rk3228_clk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);

	inno_update_bits(inno, 0xe0, RK3228_PRE_PLL_POWER_DOWN, 0);
	वापस 0;
पूर्ण

अटल व्योम inno_hdmi_phy_rk3228_clk_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);

	inno_update_bits(inno, 0xe0, RK3228_PRE_PLL_POWER_DOWN,
			 RK3228_PRE_PLL_POWER_DOWN);
पूर्ण

अटल
अचिन्हित दीर्घ inno_hdmi_phy_rk3228_clk_recalc_rate(काष्ठा clk_hw *hw,
						   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);
	u8 nd, no_a, no_b, no_d;
	u64 vco;
	u16 nf;

	nd = inno_पढ़ो(inno, 0xe2) & RK3228_PRE_PLL_PRE_DIV_MASK;
	nf = (inno_पढ़ो(inno, 0xe2) & RK3228_PRE_PLL_FB_DIV_8_MASK) << 1;
	nf |= inno_पढ़ो(inno, 0xe3);
	vco = parent_rate * nf;

	अगर (inno_पढ़ो(inno, 0xe2) & RK3228_PCLK_VCO_DIV_5_MASK) अणु
		करो_भाग(vco, nd * 5);
	पूर्ण अन्यथा अणु
		no_a = inno_पढ़ो(inno, 0xe4) & RK3228_PRE_PLL_PCLK_DIV_A_MASK;
		अगर (!no_a)
			no_a = 1;
		no_b = inno_पढ़ो(inno, 0xe4) & RK3228_PRE_PLL_PCLK_DIV_B_MASK;
		no_b >>= RK3228_PRE_PLL_PCLK_DIV_B_SHIFT;
		no_b += 2;
		no_d = inno_पढ़ो(inno, 0xe5) & RK3228_PRE_PLL_PCLK_DIV_D_MASK;

		करो_भाग(vco, (nd * (no_a == 1 ? no_b : no_a) * no_d * 2));
	पूर्ण

	inno->pixघड़ी = vco;

	dev_dbg(inno->dev, "%s rate %lu\n", __func__, inno->pixघड़ी);

	वापस vco;
पूर्ण

अटल दीर्घ inno_hdmi_phy_rk3228_clk_round_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ rate,
						अचिन्हित दीर्घ *parent_rate)
अणु
	स्थिर काष्ठा pre_pll_config *cfg = pre_pll_cfg_table;

	rate = (rate / 1000) * 1000;

	क्रम (; cfg->pixघड़ी != 0; cfg++)
		अगर (cfg->pixघड़ी == rate && !cfg->fracभाग)
			अवरोध;

	अगर (cfg->pixघड़ी == 0)
		वापस -EINVAL;

	वापस cfg->pixघड़ी;
पूर्ण

अटल पूर्णांक inno_hdmi_phy_rk3228_clk_set_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ rate,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);
	स्थिर काष्ठा pre_pll_config *cfg = pre_pll_cfg_table;
	अचिन्हित दीर्घ पंचांगdsघड़ी = inno_hdmi_phy_get_पंचांगdsclk(inno, rate);
	u32 v;
	पूर्णांक ret;

	dev_dbg(inno->dev, "%s rate %lu tmdsclk %lu\n",
		__func__, rate, पंचांगdsघड़ी);

	cfg = inno_hdmi_phy_get_pre_pll_cfg(inno, rate);
	अगर (IS_ERR(cfg))
		वापस PTR_ERR(cfg);

	/* Power करोwn PRE-PLL */
	inno_update_bits(inno, 0xe0, RK3228_PRE_PLL_POWER_DOWN,
			 RK3228_PRE_PLL_POWER_DOWN);

	inno_update_bits(inno, 0xe2, RK3228_PRE_PLL_FB_DIV_8_MASK |
			 RK3228_PCLK_VCO_DIV_5_MASK |
			 RK3228_PRE_PLL_PRE_DIV_MASK,
			 RK3228_PRE_PLL_FB_DIV_8(cfg->fbभाग) |
			 RK3228_PCLK_VCO_DIV_5(cfg->vco_भाग_5_en) |
			 RK3228_PRE_PLL_PRE_DIV(cfg->preभाग));
	inno_ग_लिखो(inno, 0xe3, RK3228_PRE_PLL_FB_DIV_7_0(cfg->fbभाग));
	inno_update_bits(inno, 0xe4, RK3228_PRE_PLL_PCLK_DIV_B_MASK |
			 RK3228_PRE_PLL_PCLK_DIV_A_MASK,
			 RK3228_PRE_PLL_PCLK_DIV_B(cfg->pclk_भाग_b) |
			 RK3228_PRE_PLL_PCLK_DIV_A(cfg->pclk_भाग_a));
	inno_update_bits(inno, 0xe5, RK3228_PRE_PLL_PCLK_DIV_C_MASK |
			 RK3228_PRE_PLL_PCLK_DIV_D_MASK,
			 RK3228_PRE_PLL_PCLK_DIV_C(cfg->pclk_भाग_c) |
			 RK3228_PRE_PLL_PCLK_DIV_D(cfg->pclk_भाग_d));
	inno_update_bits(inno, 0xe6, RK3228_PRE_PLL_TMDSCLK_DIV_C_MASK |
			 RK3228_PRE_PLL_TMDSCLK_DIV_A_MASK |
			 RK3228_PRE_PLL_TMDSCLK_DIV_B_MASK,
			 RK3228_PRE_PLL_TMDSCLK_DIV_C(cfg->पंचांगds_भाग_c) |
			 RK3228_PRE_PLL_TMDSCLK_DIV_A(cfg->पंचांगds_भाग_a) |
			 RK3228_PRE_PLL_TMDSCLK_DIV_B(cfg->पंचांगds_भाग_b));

	/* Power up PRE-PLL */
	inno_update_bits(inno, 0xe0, RK3228_PRE_PLL_POWER_DOWN, 0);

	/* Wait क्रम Pre-PLL lock */
	ret = inno_poll(inno, 0xe8, v, v & RK3228_PRE_PLL_LOCK_STATUS,
			100, 100000);
	अगर (ret) अणु
		dev_err(inno->dev, "Pre-PLL locking failed\n");
		वापस ret;
	पूर्ण

	inno->pixघड़ी = rate;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops inno_hdmi_phy_rk3228_clk_ops = अणु
	.prepare = inno_hdmi_phy_rk3228_clk_prepare,
	.unprepare = inno_hdmi_phy_rk3228_clk_unprepare,
	.is_prepared = inno_hdmi_phy_rk3228_clk_is_prepared,
	.recalc_rate = inno_hdmi_phy_rk3228_clk_recalc_rate,
	.round_rate = inno_hdmi_phy_rk3228_clk_round_rate,
	.set_rate = inno_hdmi_phy_rk3228_clk_set_rate,
पूर्ण;

अटल पूर्णांक inno_hdmi_phy_rk3328_clk_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);
	u8 status;

	status = inno_पढ़ो(inno, 0xa0) & RK3328_PRE_PLL_POWER_DOWN;
	वापस status ? 0 : 1;
पूर्ण

अटल पूर्णांक inno_hdmi_phy_rk3328_clk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);

	inno_update_bits(inno, 0xa0, RK3328_PRE_PLL_POWER_DOWN, 0);
	वापस 0;
पूर्ण

अटल व्योम inno_hdmi_phy_rk3328_clk_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);

	inno_update_bits(inno, 0xa0, RK3328_PRE_PLL_POWER_DOWN,
			 RK3328_PRE_PLL_POWER_DOWN);
पूर्ण

अटल
अचिन्हित दीर्घ inno_hdmi_phy_rk3328_clk_recalc_rate(काष्ठा clk_hw *hw,
						   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);
	अचिन्हित दीर्घ frac;
	u8 nd, no_a, no_b, no_c, no_d;
	u64 vco;
	u16 nf;

	nd = inno_पढ़ो(inno, 0xa1) & RK3328_PRE_PLL_PRE_DIV_MASK;
	nf = ((inno_पढ़ो(inno, 0xa2) & RK3328_PRE_PLL_FB_DIV_11_8_MASK) << 8);
	nf |= inno_पढ़ो(inno, 0xa3);
	vco = parent_rate * nf;

	अगर (!(inno_पढ़ो(inno, 0xa2) & RK3328_PRE_PLL_FRAC_DIV_DISABLE)) अणु
		frac = inno_पढ़ो(inno, 0xd3) |
		       (inno_पढ़ो(inno, 0xd2) << 8) |
		       (inno_पढ़ो(inno, 0xd1) << 16);
		vco += DIV_ROUND_CLOSEST(parent_rate * frac, (1 << 24));
	पूर्ण

	अगर (inno_पढ़ो(inno, 0xa0) & RK3328_PCLK_VCO_DIV_5_MASK) अणु
		करो_भाग(vco, nd * 5);
	पूर्ण अन्यथा अणु
		no_a = inno_पढ़ो(inno, 0xa5) & RK3328_PRE_PLL_PCLK_DIV_A_MASK;
		no_b = inno_पढ़ो(inno, 0xa5) & RK3328_PRE_PLL_PCLK_DIV_B_MASK;
		no_b >>= RK3328_PRE_PLL_PCLK_DIV_B_SHIFT;
		no_b += 2;
		no_c = inno_पढ़ो(inno, 0xa6) & RK3328_PRE_PLL_PCLK_DIV_C_MASK;
		no_c >>= RK3328_PRE_PLL_PCLK_DIV_C_SHIFT;
		no_c = 1 << no_c;
		no_d = inno_पढ़ो(inno, 0xa6) & RK3328_PRE_PLL_PCLK_DIV_D_MASK;

		करो_भाग(vco, (nd * (no_a == 1 ? no_b : no_a) * no_d * 2));
	पूर्ण

	inno->pixघड़ी = vco;
	dev_dbg(inno->dev, "%s rate %lu\n", __func__, inno->pixघड़ी);

	वापस vco;
पूर्ण

अटल दीर्घ inno_hdmi_phy_rk3328_clk_round_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ rate,
						अचिन्हित दीर्घ *parent_rate)
अणु
	स्थिर काष्ठा pre_pll_config *cfg = pre_pll_cfg_table;

	rate = (rate / 1000) * 1000;

	क्रम (; cfg->pixघड़ी != 0; cfg++)
		अगर (cfg->pixघड़ी == rate)
			अवरोध;

	अगर (cfg->pixघड़ी == 0)
		वापस -EINVAL;

	वापस cfg->pixघड़ी;
पूर्ण

अटल पूर्णांक inno_hdmi_phy_rk3328_clk_set_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ rate,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा inno_hdmi_phy *inno = to_inno_hdmi_phy(hw);
	स्थिर काष्ठा pre_pll_config *cfg = pre_pll_cfg_table;
	अचिन्हित दीर्घ पंचांगdsघड़ी = inno_hdmi_phy_get_पंचांगdsclk(inno, rate);
	u32 val;
	पूर्णांक ret;

	dev_dbg(inno->dev, "%s rate %lu tmdsclk %lu\n",
		__func__, rate, पंचांगdsघड़ी);

	cfg = inno_hdmi_phy_get_pre_pll_cfg(inno, rate);
	अगर (IS_ERR(cfg))
		वापस PTR_ERR(cfg);

	inno_update_bits(inno, 0xa0, RK3328_PRE_PLL_POWER_DOWN,
			 RK3328_PRE_PLL_POWER_DOWN);

	/* Configure pre-pll */
	inno_update_bits(inno, 0xa0, RK3228_PCLK_VCO_DIV_5_MASK,
			 RK3228_PCLK_VCO_DIV_5(cfg->vco_भाग_5_en));
	inno_ग_लिखो(inno, 0xa1, RK3328_PRE_PLL_PRE_DIV(cfg->preभाग));

	val = RK3328_SPREAD_SPECTRUM_MOD_DISABLE;
	अगर (!cfg->fracभाग)
		val |= RK3328_PRE_PLL_FRAC_DIV_DISABLE;
	inno_ग_लिखो(inno, 0xa2, RK3328_PRE_PLL_FB_DIV_11_8(cfg->fbभाग) | val);
	inno_ग_लिखो(inno, 0xa3, RK3328_PRE_PLL_FB_DIV_7_0(cfg->fbभाग));
	inno_ग_लिखो(inno, 0xa5, RK3328_PRE_PLL_PCLK_DIV_A(cfg->pclk_भाग_a) |
		   RK3328_PRE_PLL_PCLK_DIV_B(cfg->pclk_भाग_b));
	inno_ग_लिखो(inno, 0xa6, RK3328_PRE_PLL_PCLK_DIV_C(cfg->pclk_भाग_c) |
		   RK3328_PRE_PLL_PCLK_DIV_D(cfg->pclk_भाग_d));
	inno_ग_लिखो(inno, 0xa4, RK3328_PRE_PLL_TMDSCLK_DIV_C(cfg->पंचांगds_भाग_c) |
		   RK3328_PRE_PLL_TMDSCLK_DIV_A(cfg->पंचांगds_भाग_a) |
		   RK3328_PRE_PLL_TMDSCLK_DIV_B(cfg->पंचांगds_भाग_b));
	inno_ग_लिखो(inno, 0xd3, RK3328_PRE_PLL_FRAC_DIV_7_0(cfg->fracभाग));
	inno_ग_लिखो(inno, 0xd2, RK3328_PRE_PLL_FRAC_DIV_15_8(cfg->fracभाग));
	inno_ग_लिखो(inno, 0xd1, RK3328_PRE_PLL_FRAC_DIV_23_16(cfg->fracभाग));

	inno_update_bits(inno, 0xa0, RK3328_PRE_PLL_POWER_DOWN, 0);

	/* Wait क्रम Pre-PLL lock */
	ret = inno_poll(inno, 0xa9, val, val & RK3328_PRE_PLL_LOCK_STATUS,
			1000, 10000);
	अगर (ret) अणु
		dev_err(inno->dev, "Pre-PLL locking failed\n");
		वापस ret;
	पूर्ण

	inno->pixघड़ी = rate;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops inno_hdmi_phy_rk3328_clk_ops = अणु
	.prepare = inno_hdmi_phy_rk3328_clk_prepare,
	.unprepare = inno_hdmi_phy_rk3328_clk_unprepare,
	.is_prepared = inno_hdmi_phy_rk3328_clk_is_prepared,
	.recalc_rate = inno_hdmi_phy_rk3328_clk_recalc_rate,
	.round_rate = inno_hdmi_phy_rk3328_clk_round_rate,
	.set_rate = inno_hdmi_phy_rk3328_clk_set_rate,
पूर्ण;

अटल पूर्णांक inno_hdmi_phy_clk_रेजिस्टर(काष्ठा inno_hdmi_phy *inno)
अणु
	काष्ठा device *dev = inno->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *parent_name;
	पूर्णांक ret;

	parent_name = __clk_get_name(inno->refoclk);

	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.flags = 0;
	init.name = "pin_hd20_pclk";
	init.ops = inno->plat_data->clk_ops;

	/* optional override of the घड़ी name */
	of_property_पढ़ो_string(np, "clock-output-names", &init.name);

	inno->hw.init = &init;

	inno->phyclk = devm_clk_रेजिस्टर(dev, &inno->hw);
	अगर (IS_ERR(inno->phyclk)) अणु
		ret = PTR_ERR(inno->phyclk);
		dev_err(dev, "failed to register clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = of_clk_add_provider(np, of_clk_src_simple_get, inno->phyclk);
	अगर (ret) अणु
		dev_err(dev, "failed to register clock provider: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inno_hdmi_phy_rk3228_init(काष्ठा inno_hdmi_phy *inno)
अणु
	/*
	 * Use phy पूर्णांकernal रेजिस्टर control
	 * rxsense/घातeron/pllpd/pdataen संकेत.
	 */
	inno_ग_लिखो(inno, 0x01, RK3228_BYPASS_RXSENSE_EN |
		   RK3228_BYPASS_PWRON_EN |
		   RK3228_BYPASS_PLLPD_EN);
	inno_update_bits(inno, 0x02, RK3228_BYPASS_PDATA_EN,
			 RK3228_BYPASS_PDATA_EN);

	/* manual घातer करोwn post-PLL */
	inno_update_bits(inno, 0xaa, RK3228_POST_PLL_CTRL_MANUAL,
			 RK3228_POST_PLL_CTRL_MANUAL);

	inno->chip_version = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक
inno_hdmi_phy_rk3228_घातer_on(काष्ठा inno_hdmi_phy *inno,
			      स्थिर काष्ठा post_pll_config *cfg,
			      स्थिर काष्ठा phy_config *phy_cfg)
अणु
	पूर्णांक ret;
	u32 v;

	inno_update_bits(inno, 0x02, RK3228_PDATAEN_DISABLE,
			 RK3228_PDATAEN_DISABLE);
	inno_update_bits(inno, 0xe0, RK3228_PRE_PLL_POWER_DOWN |
			 RK3228_POST_PLL_POWER_DOWN,
			 RK3228_PRE_PLL_POWER_DOWN |
			 RK3228_POST_PLL_POWER_DOWN);

	/* Post-PLL update */
	inno_update_bits(inno, 0xe9, RK3228_POST_PLL_PRE_DIV_MASK,
			 RK3228_POST_PLL_PRE_DIV(cfg->preभाग));
	inno_update_bits(inno, 0xeb, RK3228_POST_PLL_FB_DIV_8_MASK,
			 RK3228_POST_PLL_FB_DIV_8(cfg->fbभाग));
	inno_ग_लिखो(inno, 0xea, RK3228_POST_PLL_FB_DIV_7_0(cfg->fbभाग));

	अगर (cfg->postभाग == 1) अणु
		inno_update_bits(inno, 0xe9, RK3228_POST_PLL_POST_DIV_ENABLE,
				 0);
	पूर्ण अन्यथा अणु
		पूर्णांक भाग = cfg->postभाग / 2 - 1;

		inno_update_bits(inno, 0xe9, RK3228_POST_PLL_POST_DIV_ENABLE,
				 RK3228_POST_PLL_POST_DIV_ENABLE);
		inno_update_bits(inno, 0xeb, RK3228_POST_PLL_POST_DIV_MASK,
				 RK3228_POST_PLL_POST_DIV(भाग));
	पूर्ण

	क्रम (v = 0; v < 4; v++)
		inno_ग_लिखो(inno, 0xef + v, phy_cfg->regs[v]);

	inno_update_bits(inno, 0xe0, RK3228_PRE_PLL_POWER_DOWN |
			 RK3228_POST_PLL_POWER_DOWN, 0);
	inno_update_bits(inno, 0xe1, RK3228_BANDGAP_ENABLE,
			 RK3228_BANDGAP_ENABLE);
	inno_update_bits(inno, 0xe1, RK3228_TMDS_DRIVER_ENABLE,
			 RK3228_TMDS_DRIVER_ENABLE);

	/* Wait क्रम post PLL lock */
	ret = inno_poll(inno, 0xeb, v, v & RK3228_POST_PLL_LOCK_STATUS,
			100, 100000);
	अगर (ret) अणु
		dev_err(inno->dev, "Post-PLL locking failed\n");
		वापस ret;
	पूर्ण

	अगर (cfg->पंचांगdsघड़ी > 340000000)
		msleep(100);

	inno_update_bits(inno, 0x02, RK3228_PDATAEN_DISABLE, 0);
	वापस 0;
पूर्ण

अटल व्योम inno_hdmi_phy_rk3228_घातer_off(काष्ठा inno_hdmi_phy *inno)
अणु
	inno_update_bits(inno, 0xe1, RK3228_TMDS_DRIVER_ENABLE, 0);
	inno_update_bits(inno, 0xe1, RK3228_BANDGAP_ENABLE, 0);
	inno_update_bits(inno, 0xe0, RK3228_POST_PLL_POWER_DOWN,
			 RK3228_POST_PLL_POWER_DOWN);
पूर्ण

अटल स्थिर काष्ठा inno_hdmi_phy_ops rk3228_hdmi_phy_ops = अणु
	.init = inno_hdmi_phy_rk3228_init,
	.घातer_on = inno_hdmi_phy_rk3228_घातer_on,
	.घातer_off = inno_hdmi_phy_rk3228_घातer_off,
पूर्ण;

अटल पूर्णांक inno_hdmi_phy_rk3328_init(काष्ठा inno_hdmi_phy *inno)
अणु
	काष्ठा nvmem_cell *cell;
	अचिन्हित अक्षर *efuse_buf;
	माप_प्रकार len;

	/*
	 * Use phy पूर्णांकernal रेजिस्टर control
	 * rxsense/घातeron/pllpd/pdataen संकेत.
	 */
	inno_ग_लिखो(inno, 0x01, RK3328_BYPASS_RXSENSE_EN |
		   RK3328_BYPASS_POWERON_EN |
		   RK3328_BYPASS_PLLPD_EN);
	inno_ग_लिखो(inno, 0x02, RK3328_INT_POL_HIGH | RK3328_BYPASS_PDATA_EN |
		   RK3328_PDATA_EN);

	/* Disable phy irq */
	inno_ग_लिखो(inno, 0x05, 0);
	inno_ग_लिखो(inno, 0x07, 0);

	/* try to पढ़ो the chip-version */
	inno->chip_version = 1;
	cell = nvmem_cell_get(inno->dev, "cpu-version");
	अगर (IS_ERR(cell)) अणु
		अगर (PTR_ERR(cell) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		वापस 0;
	पूर्ण

	efuse_buf = nvmem_cell_पढ़ो(cell, &len);
	nvmem_cell_put(cell);

	अगर (IS_ERR(efuse_buf))
		वापस 0;
	अगर (len == 1)
		inno->chip_version = efuse_buf[0] + 1;
	kमुक्त(efuse_buf);

	वापस 0;
पूर्ण

अटल पूर्णांक
inno_hdmi_phy_rk3328_घातer_on(काष्ठा inno_hdmi_phy *inno,
			      स्थिर काष्ठा post_pll_config *cfg,
			      स्थिर काष्ठा phy_config *phy_cfg)
अणु
	पूर्णांक ret;
	u32 v;

	inno_update_bits(inno, 0x02, RK3328_PDATA_EN, 0);
	inno_update_bits(inno, 0xaa, RK3328_POST_PLL_POWER_DOWN,
			 RK3328_POST_PLL_POWER_DOWN);

	inno_ग_लिखो(inno, 0xac, RK3328_POST_PLL_FB_DIV_7_0(cfg->fbभाग));
	अगर (cfg->postभाग == 1) अणु
		inno_ग_लिखो(inno, 0xaa, RK3328_POST_PLL_REFCLK_SEL_TMDS);
		inno_ग_लिखो(inno, 0xab, RK3328_POST_PLL_FB_DIV_8(cfg->fbभाग) |
			   RK3328_POST_PLL_PRE_DIV(cfg->preभाग));
	पूर्ण अन्यथा अणु
		v = (cfg->postभाग / 2) - 1;
		v &= RK3328_POST_PLL_POST_DIV_MASK;
		inno_ग_लिखो(inno, 0xad, v);
		inno_ग_लिखो(inno, 0xab, RK3328_POST_PLL_FB_DIV_8(cfg->fbभाग) |
			   RK3328_POST_PLL_PRE_DIV(cfg->preभाग));
		inno_ग_लिखो(inno, 0xaa, RK3328_POST_PLL_POST_DIV_ENABLE |
			   RK3328_POST_PLL_REFCLK_SEL_TMDS);
	पूर्ण

	क्रम (v = 0; v < 14; v++)
		inno_ग_लिखो(inno, 0xb5 + v, phy_cfg->regs[v]);

	/* set ESD detection threshold क्रम TMDS CLK, D2, D1 and D0 */
	क्रम (v = 0; v < 4; v++)
		inno_update_bits(inno, 0xc8 + v, RK3328_ESD_DETECT_MASK,
				 RK3328_ESD_DETECT_340MV);

	अगर (phy_cfg->पंचांगdsघड़ी > 340000000) अणु
		/* Set termination resistor to 100ohm */
		v = clk_get_rate(inno->sysclk) / 100000;
		inno_ग_लिखो(inno, 0xc5, RK3328_TERM_RESISTOR_CALIB_SPEED_14_8(v)
			   | RK3328_BYPASS_TERM_RESISTOR_CALIB);
		inno_ग_लिखो(inno, 0xc6, RK3328_TERM_RESISTOR_CALIB_SPEED_7_0(v));
		inno_ग_लिखो(inno, 0xc7, RK3328_TERM_RESISTOR_100);
		inno_update_bits(inno, 0xc5,
				 RK3328_BYPASS_TERM_RESISTOR_CALIB, 0);
	पूर्ण अन्यथा अणु
		inno_ग_लिखो(inno, 0xc5, RK3328_BYPASS_TERM_RESISTOR_CALIB);

		/* clk termination resistor is 50ohm (parallel resistors) */
		अगर (phy_cfg->पंचांगdsघड़ी > 165000000)
			inno_update_bits(inno, 0xc8,
					 RK3328_TMDS_TERM_RESIST_MASK,
					 RK3328_TMDS_TERM_RESIST_75 |
					 RK3328_TMDS_TERM_RESIST_150);

		/* data termination resistor क्रम D2, D1 and D0 is 150ohm */
		क्रम (v = 0; v < 3; v++)
			inno_update_bits(inno, 0xc9 + v,
					 RK3328_TMDS_TERM_RESIST_MASK,
					 RK3328_TMDS_TERM_RESIST_150);
	पूर्ण

	inno_update_bits(inno, 0xaa, RK3328_POST_PLL_POWER_DOWN, 0);
	inno_update_bits(inno, 0xb0, RK3328_BANDGAP_ENABLE,
			 RK3328_BANDGAP_ENABLE);
	inno_update_bits(inno, 0xb2, RK3328_TMDS_DRIVER_ENABLE,
			 RK3328_TMDS_DRIVER_ENABLE);

	/* Wait क्रम post PLL lock */
	ret = inno_poll(inno, 0xaf, v, v & RK3328_POST_PLL_LOCK_STATUS,
			1000, 10000);
	अगर (ret) अणु
		dev_err(inno->dev, "Post-PLL locking failed\n");
		वापस ret;
	पूर्ण

	अगर (phy_cfg->पंचांगdsघड़ी > 340000000)
		msleep(100);

	inno_update_bits(inno, 0x02, RK3328_PDATA_EN, RK3328_PDATA_EN);

	/* Enable PHY IRQ */
	inno_ग_लिखो(inno, 0x05, RK3328_INT_TMDS_CLK(RK3328_INT_VSS_AGND_ESD_DET)
		   | RK3328_INT_TMDS_D2(RK3328_INT_VSS_AGND_ESD_DET));
	inno_ग_लिखो(inno, 0x07, RK3328_INT_TMDS_D1(RK3328_INT_VSS_AGND_ESD_DET)
		   | RK3328_INT_TMDS_D0(RK3328_INT_VSS_AGND_ESD_DET));
	वापस 0;
पूर्ण

अटल व्योम inno_hdmi_phy_rk3328_घातer_off(काष्ठा inno_hdmi_phy *inno)
अणु
	inno_update_bits(inno, 0xb2, RK3328_TMDS_DRIVER_ENABLE, 0);
	inno_update_bits(inno, 0xb0, RK3328_BANDGAP_ENABLE, 0);
	inno_update_bits(inno, 0xaa, RK3328_POST_PLL_POWER_DOWN,
			 RK3328_POST_PLL_POWER_DOWN);

	/* Disable PHY IRQ */
	inno_ग_लिखो(inno, 0x05, 0);
	inno_ग_लिखो(inno, 0x07, 0);
पूर्ण

अटल स्थिर काष्ठा inno_hdmi_phy_ops rk3328_hdmi_phy_ops = अणु
	.init = inno_hdmi_phy_rk3328_init,
	.घातer_on = inno_hdmi_phy_rk3328_घातer_on,
	.घातer_off = inno_hdmi_phy_rk3328_घातer_off,
पूर्ण;

अटल स्थिर काष्ठा inno_hdmi_phy_drv_data rk3228_hdmi_phy_drv_data = अणु
	.ops = &rk3228_hdmi_phy_ops,
	.clk_ops = &inno_hdmi_phy_rk3228_clk_ops,
	.phy_cfg_table = rk3228_phy_cfg,
पूर्ण;

अटल स्थिर काष्ठा inno_hdmi_phy_drv_data rk3328_hdmi_phy_drv_data = अणु
	.ops = &rk3328_hdmi_phy_ops,
	.clk_ops = &inno_hdmi_phy_rk3328_clk_ops,
	.phy_cfg_table = rk3328_phy_cfg,
पूर्ण;

अटल स्थिर काष्ठा regmap_config inno_hdmi_phy_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = 0x400,
पूर्ण;

अटल व्योम inno_hdmi_phy_action(व्योम *data)
अणु
	काष्ठा inno_hdmi_phy *inno = data;

	clk_disable_unprepare(inno->refpclk);
	clk_disable_unprepare(inno->sysclk);
पूर्ण

अटल पूर्णांक inno_hdmi_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा inno_hdmi_phy *inno;
	काष्ठा phy_provider *phy_provider;
	व्योम __iomem *regs;
	पूर्णांक ret;

	inno = devm_kzalloc(&pdev->dev, माप(*inno), GFP_KERNEL);
	अगर (!inno)
		वापस -ENOMEM;

	inno->dev = &pdev->dev;

	inno->plat_data = of_device_get_match_data(inno->dev);
	अगर (!inno->plat_data || !inno->plat_data->ops)
		वापस -EINVAL;

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	inno->sysclk = devm_clk_get(inno->dev, "sysclk");
	अगर (IS_ERR(inno->sysclk)) अणु
		ret = PTR_ERR(inno->sysclk);
		dev_err(inno->dev, "failed to get sysclk: %d\n", ret);
		वापस ret;
	पूर्ण

	inno->refpclk = devm_clk_get(inno->dev, "refpclk");
	अगर (IS_ERR(inno->refpclk)) अणु
		ret = PTR_ERR(inno->refpclk);
		dev_err(inno->dev, "failed to get ref clock: %d\n", ret);
		वापस ret;
	पूर्ण

	inno->refoclk = devm_clk_get(inno->dev, "refoclk");
	अगर (IS_ERR(inno->refoclk)) अणु
		ret = PTR_ERR(inno->refoclk);
		dev_err(inno->dev, "failed to get oscillator-ref clock: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(inno->sysclk);
	अगर (ret) अणु
		dev_err(inno->dev, "Cannot enable inno phy sysclk: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Refpclk needs to be on, on at least the rk3328 क्रम still
	 * unknown reasons.
	 */
	ret = clk_prepare_enable(inno->refpclk);
	अगर (ret) अणु
		dev_err(inno->dev, "failed to enable refpclk\n");
		clk_disable_unprepare(inno->sysclk);
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(inno->dev, inno_hdmi_phy_action,
				       inno);
	अगर (ret)
		वापस ret;

	inno->regmap = devm_regmap_init_mmio(inno->dev, regs,
					     &inno_hdmi_phy_regmap_config);
	अगर (IS_ERR(inno->regmap))
		वापस PTR_ERR(inno->regmap);

	/* only the newer rk3328 hdmiphy has an पूर्णांकerrupt */
	inno->irq = platक्रमm_get_irq(pdev, 0);
	अगर (inno->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(inno->dev, inno->irq,
						inno_hdmi_phy_rk3328_hardirq,
						inno_hdmi_phy_rk3328_irq,
						IRQF_SHARED,
						dev_name(inno->dev), inno);
		अगर (ret)
			वापस ret;
	पूर्ण

	inno->phy = devm_phy_create(inno->dev, शून्य, &inno_hdmi_phy_ops);
	अगर (IS_ERR(inno->phy)) अणु
		dev_err(inno->dev, "failed to create HDMI PHY\n");
		वापस PTR_ERR(inno->phy);
	पूर्ण

	phy_set_drvdata(inno->phy, inno);
	phy_set_bus_width(inno->phy, 8);

	अगर (inno->plat_data->ops->init) अणु
		ret = inno->plat_data->ops->init(inno);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = inno_hdmi_phy_clk_रेजिस्टर(inno);
	अगर (ret)
		वापस ret;

	phy_provider = devm_of_phy_provider_रेजिस्टर(inno->dev,
						     of_phy_simple_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल पूर्णांक inno_hdmi_phy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	of_clk_del_provider(pdev->dev.of_node);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id inno_hdmi_phy_of_match[] = अणु
	अणु
		.compatible = "rockchip,rk3228-hdmi-phy",
		.data = &rk3228_hdmi_phy_drv_data
	पूर्ण, अणु
		.compatible = "rockchip,rk3328-hdmi-phy",
		.data = &rk3328_hdmi_phy_drv_data
	पूर्ण, अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, inno_hdmi_phy_of_match);

अटल काष्ठा platक्रमm_driver inno_hdmi_phy_driver = अणु
	.probe  = inno_hdmi_phy_probe,
	.हटाओ = inno_hdmi_phy_हटाओ,
	.driver = अणु
		.name = "inno-hdmi-phy",
		.of_match_table = inno_hdmi_phy_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(inno_hdmi_phy_driver);

MODULE_AUTHOR("Zheng Yang <zhengyang@rock-chips.com>");
MODULE_DESCRIPTION("Innosilion HDMI 2.0 Transmitter PHY Driver");
MODULE_LICENSE("GPL v2");
