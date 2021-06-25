<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author:
 *      Chris Zhong <zyw@rock-chips.com>
 *      Nickey Yang <nickey.yang@rock-chips.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/math64.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/bridge/dw_mipi_dsi.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "rockchip_drm_drv.h"
#समावेश "rockchip_drm_vop.h"

#घोषणा DSI_PHY_RSTZ			0xa0
#घोषणा PHY_DISFORCEPLL			0
#घोषणा PHY_ENFORCEPLL			BIT(3)
#घोषणा PHY_DISABLECLK			0
#घोषणा PHY_ENABLECLK			BIT(2)
#घोषणा PHY_RSTZ			0
#घोषणा PHY_UNRSTZ			BIT(1)
#घोषणा PHY_SHUTDOWNZ			0
#घोषणा PHY_UNSHUTDOWNZ			BIT(0)

#घोषणा DSI_PHY_IF_CFG			0xa4
#घोषणा N_LANES(n)			((((n) - 1) & 0x3) << 0)
#घोषणा PHY_STOP_WAIT_TIME(cycle)	(((cycle) & 0xff) << 8)

#घोषणा DSI_PHY_STATUS			0xb0
#घोषणा LOCK				BIT(0)
#घोषणा STOP_STATE_CLK_LANE		BIT(2)

#घोषणा DSI_PHY_TST_CTRL0		0xb4
#घोषणा PHY_TESTCLK			BIT(1)
#घोषणा PHY_UNTESTCLK			0
#घोषणा PHY_TESTCLR			BIT(0)
#घोषणा PHY_UNTESTCLR			0

#घोषणा DSI_PHY_TST_CTRL1		0xb8
#घोषणा PHY_TESTEN			BIT(16)
#घोषणा PHY_UNTESTEN			0
#घोषणा PHY_TESTDOUT(n)			(((n) & 0xff) << 8)
#घोषणा PHY_TESTDIN(n)			(((n) & 0xff) << 0)

#घोषणा DSI_INT_ST0			0xbc
#घोषणा DSI_INT_ST1			0xc0
#घोषणा DSI_INT_MSK0			0xc4
#घोषणा DSI_INT_MSK1			0xc8

#घोषणा PHY_STATUS_TIMEOUT_US		10000
#घोषणा CMD_PKT_STATUS_TIMEOUT_US	20000

#घोषणा BYPASS_VCO_RANGE	BIT(7)
#घोषणा VCO_RANGE_CON_SEL(val)	(((val) & 0x7) << 3)
#घोषणा VCO_IN_CAP_CON_DEFAULT	(0x0 << 1)
#घोषणा VCO_IN_CAP_CON_LOW	(0x1 << 1)
#घोषणा VCO_IN_CAP_CON_HIGH	(0x2 << 1)
#घोषणा REF_BIAS_CUR_SEL	BIT(0)

#घोषणा CP_CURRENT_3UA	0x1
#घोषणा CP_CURRENT_4_5UA	0x2
#घोषणा CP_CURRENT_7_5UA	0x6
#घोषणा CP_CURRENT_6UA	0x9
#घोषणा CP_CURRENT_12UA	0xb
#घोषणा CP_CURRENT_SEL(val)	((val) & 0xf)
#घोषणा CP_PROGRAM_EN		BIT(7)

#घोषणा LPF_RESISTORS_15_5KOHM	0x1
#घोषणा LPF_RESISTORS_13KOHM	0x2
#घोषणा LPF_RESISTORS_11_5KOHM	0x4
#घोषणा LPF_RESISTORS_10_5KOHM	0x8
#घोषणा LPF_RESISTORS_8KOHM	0x10
#घोषणा LPF_PROGRAM_EN		BIT(6)
#घोषणा LPF_RESISTORS_SEL(val)	((val) & 0x3f)

#घोषणा HSFREQRANGE_SEL(val)	(((val) & 0x3f) << 1)

#घोषणा INPUT_DIVIDER(val)	(((val) - 1) & 0x7f)
#घोषणा LOW_PROGRAM_EN		0
#घोषणा HIGH_PROGRAM_EN		BIT(7)
#घोषणा LOOP_DIV_LOW_SEL(val)	(((val) - 1) & 0x1f)
#घोषणा LOOP_DIV_HIGH_SEL(val)	((((val) - 1) >> 5) & 0xf)
#घोषणा PLL_LOOP_DIV_EN		BIT(5)
#घोषणा PLL_INPUT_DIV_EN	BIT(4)

#घोषणा POWER_CONTROL		BIT(6)
#घोषणा INTERNAL_REG_CURRENT	BIT(3)
#घोषणा BIAS_BLOCK_ON		BIT(2)
#घोषणा BANDGAP_ON		BIT(0)

#घोषणा TER_RESISTOR_HIGH	BIT(7)
#घोषणा	TER_RESISTOR_LOW	0
#घोषणा LEVEL_SHIFTERS_ON	BIT(6)
#घोषणा TER_CAL_DONE		BIT(5)
#घोषणा SETRD_MAX		(0x7 << 2)
#घोषणा POWER_MANAGE		BIT(1)
#घोषणा TER_RESISTORS_ON	BIT(0)

#घोषणा BIASEXTR_SEL(val)	((val) & 0x7)
#घोषणा BANDGAP_SEL(val)	((val) & 0x7)
#घोषणा TLP_PROGRAM_EN		BIT(7)
#घोषणा THS_PRE_PROGRAM_EN	BIT(7)
#घोषणा THS_ZERO_PROGRAM_EN	BIT(6)

#घोषणा PLL_BIAS_CUR_SEL_CAP_VCO_CONTROL		0x10
#घोषणा PLL_CP_CONTROL_PLL_LOCK_BYPASS			0x11
#घोषणा PLL_LPF_AND_CP_CONTROL				0x12
#घोषणा PLL_INPUT_DIVIDER_RATIO				0x17
#घोषणा PLL_LOOP_DIVIDER_RATIO				0x18
#घोषणा PLL_INPUT_AND_LOOP_DIVIDER_RATIOS_CONTROL	0x19
#घोषणा BANDGAP_AND_BIAS_CONTROL			0x20
#घोषणा TERMINATION_RESISTER_CONTROL			0x21
#घोषणा AFE_BIAS_BANDGAP_ANALOG_PROGRAMMABILITY		0x22
#घोषणा HS_RX_CONTROL_OF_LANE_0				0x44
#घोषणा HS_TX_CLOCK_LANE_REQUEST_STATE_TIME_CONTROL	0x60
#घोषणा HS_TX_CLOCK_LANE_PREPARE_STATE_TIME_CONTROL	0x61
#घोषणा HS_TX_CLOCK_LANE_HS_ZERO_STATE_TIME_CONTROL	0x62
#घोषणा HS_TX_CLOCK_LANE_TRAIL_STATE_TIME_CONTROL	0x63
#घोषणा HS_TX_CLOCK_LANE_EXIT_STATE_TIME_CONTROL	0x64
#घोषणा HS_TX_CLOCK_LANE_POST_TIME_CONTROL		0x65
#घोषणा HS_TX_DATA_LANE_REQUEST_STATE_TIME_CONTROL	0x70
#घोषणा HS_TX_DATA_LANE_PREPARE_STATE_TIME_CONTROL	0x71
#घोषणा HS_TX_DATA_LANE_HS_ZERO_STATE_TIME_CONTROL	0x72
#घोषणा HS_TX_DATA_LANE_TRAIL_STATE_TIME_CONTROL	0x73
#घोषणा HS_TX_DATA_LANE_EXIT_STATE_TIME_CONTROL		0x74

#घोषणा DW_MIPI_NEEDS_PHY_CFG_CLK	BIT(0)
#घोषणा DW_MIPI_NEEDS_GRF_CLK		BIT(1)

#घोषणा PX30_GRF_PD_VO_CON1		0x0438
#घोषणा PX30_DSI_FORCETXSTOPMODE	(0xf << 7)
#घोषणा PX30_DSI_FORCERXMODE		BIT(6)
#घोषणा PX30_DSI_TURNDISABLE		BIT(5)
#घोषणा PX30_DSI_LCDC_SEL		BIT(0)

#घोषणा RK3288_GRF_SOC_CON6		0x025c
#घोषणा RK3288_DSI0_LCDC_SEL		BIT(6)
#घोषणा RK3288_DSI1_LCDC_SEL		BIT(9)

#घोषणा RK3399_GRF_SOC_CON20		0x6250
#घोषणा RK3399_DSI0_LCDC_SEL		BIT(0)
#घोषणा RK3399_DSI1_LCDC_SEL		BIT(4)

#घोषणा RK3399_GRF_SOC_CON22		0x6258
#घोषणा RK3399_DSI0_TURNREQUEST		(0xf << 12)
#घोषणा RK3399_DSI0_TURNDISABLE		(0xf << 8)
#घोषणा RK3399_DSI0_FORCETXSTOPMODE	(0xf << 4)
#घोषणा RK3399_DSI0_FORCERXMODE		(0xf << 0)

#घोषणा RK3399_GRF_SOC_CON23		0x625c
#घोषणा RK3399_DSI1_TURNDISABLE		(0xf << 12)
#घोषणा RK3399_DSI1_FORCETXSTOPMODE	(0xf << 8)
#घोषणा RK3399_DSI1_FORCERXMODE		(0xf << 4)
#घोषणा RK3399_DSI1_ENABLE		(0xf << 0)

#घोषणा RK3399_GRF_SOC_CON24		0x6260
#घोषणा RK3399_TXRX_MASTERSLAVEZ	BIT(7)
#घोषणा RK3399_TXRX_ENABLECLK		BIT(6)
#घोषणा RK3399_TXRX_BASEसूची		BIT(5)

#घोषणा HIWORD_UPDATE(val, mask)	(val | (mask) << 16)

#घोषणा to_dsi(nm)	container_of(nm, काष्ठा dw_mipi_dsi_rockchip, nm)

क्रमागत अणु
	BANDGAP_97_07,
	BANDGAP_98_05,
	BANDGAP_99_02,
	BANDGAP_100_00,
	BANDGAP_93_17,
	BANDGAP_94_15,
	BANDGAP_95_12,
	BANDGAP_96_10,
पूर्ण;

क्रमागत अणु
	BIASEXTR_87_1,
	BIASEXTR_91_5,
	BIASEXTR_95_9,
	BIASEXTR_100,
	BIASEXTR_105_94,
	BIASEXTR_111_88,
	BIASEXTR_118_8,
	BIASEXTR_127_7,
पूर्ण;

काष्ठा rockchip_dw_dsi_chip_data अणु
	u32 reg;

	u32 lcdsel_grf_reg;
	u32 lcdsel_big;
	u32 lcdsel_lit;

	u32 enable_grf_reg;
	u32 enable;

	u32 lanecfg1_grf_reg;
	u32 lanecfg1;
	u32 lanecfg2_grf_reg;
	u32 lanecfg2;

	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक max_data_lanes;
पूर्ण;

काष्ठा dw_mipi_dsi_rockchip अणु
	काष्ठा device *dev;
	काष्ठा drm_encoder encoder;
	व्योम __iomem *base;

	काष्ठा regmap *grf_regmap;
	काष्ठा clk *pllref_clk;
	काष्ठा clk *grf_clk;
	काष्ठा clk *phy_cfg_clk;

	/* dual-channel */
	bool is_slave;
	काष्ठा dw_mipi_dsi_rockchip *slave;

	/* optional बाह्यal dphy */
	काष्ठा phy *phy;
	जोड़ phy_configure_opts phy_opts;

	अचिन्हित पूर्णांक lane_mbps; /* per lane */
	u16 input_भाग;
	u16 feedback_भाग;
	u32 क्रमmat;

	काष्ठा dw_mipi_dsi *dmd;
	स्थिर काष्ठा rockchip_dw_dsi_chip_data *cdata;
	काष्ठा dw_mipi_dsi_plat_data pdata;
	पूर्णांक devcnt;
पूर्ण;

काष्ठा dphy_pll_parameter_map अणु
	अचिन्हित पूर्णांक max_mbps;
	u8 hsfreqrange;
	u8 icpctrl;
	u8 lpfctrl;
पूर्ण;

/* The table is based on 27MHz DPHY pll reference घड़ी. */
अटल स्थिर काष्ठा dphy_pll_parameter_map dppa_map[] = अणु
	अणु  89, 0x00, CP_CURRENT_3UA, LPF_RESISTORS_13KOHM पूर्ण,
	अणु  99, 0x10, CP_CURRENT_3UA, LPF_RESISTORS_13KOHM पूर्ण,
	अणु 109, 0x20, CP_CURRENT_3UA, LPF_RESISTORS_13KOHM पूर्ण,
	अणु 129, 0x01, CP_CURRENT_3UA, LPF_RESISTORS_15_5KOHM पूर्ण,
	अणु 139, 0x11, CP_CURRENT_3UA, LPF_RESISTORS_15_5KOHM पूर्ण,
	अणु 149, 0x21, CP_CURRENT_3UA, LPF_RESISTORS_15_5KOHM पूर्ण,
	अणु 169, 0x02, CP_CURRENT_6UA, LPF_RESISTORS_13KOHM पूर्ण,
	अणु 179, 0x12, CP_CURRENT_6UA, LPF_RESISTORS_13KOHM पूर्ण,
	अणु 199, 0x22, CP_CURRENT_6UA, LPF_RESISTORS_13KOHM पूर्ण,
	अणु 219, 0x03, CP_CURRENT_4_5UA, LPF_RESISTORS_13KOHM पूर्ण,
	अणु 239, 0x13, CP_CURRENT_4_5UA, LPF_RESISTORS_13KOHM पूर्ण,
	अणु 249, 0x23, CP_CURRENT_4_5UA, LPF_RESISTORS_13KOHM पूर्ण,
	अणु 269, 0x04, CP_CURRENT_6UA, LPF_RESISTORS_11_5KOHM पूर्ण,
	अणु 299, 0x14, CP_CURRENT_6UA, LPF_RESISTORS_11_5KOHM पूर्ण,
	अणु 329, 0x05, CP_CURRENT_3UA, LPF_RESISTORS_15_5KOHM पूर्ण,
	अणु 359, 0x15, CP_CURRENT_3UA, LPF_RESISTORS_15_5KOHM पूर्ण,
	अणु 399, 0x25, CP_CURRENT_3UA, LPF_RESISTORS_15_5KOHM पूर्ण,
	अणु 449, 0x06, CP_CURRENT_7_5UA, LPF_RESISTORS_11_5KOHM पूर्ण,
	अणु 499, 0x16, CP_CURRENT_7_5UA, LPF_RESISTORS_11_5KOHM पूर्ण,
	अणु 549, 0x07, CP_CURRENT_7_5UA, LPF_RESISTORS_10_5KOHM पूर्ण,
	अणु 599, 0x17, CP_CURRENT_7_5UA, LPF_RESISTORS_10_5KOHM पूर्ण,
	अणु 649, 0x08, CP_CURRENT_7_5UA, LPF_RESISTORS_11_5KOHM पूर्ण,
	अणु 699, 0x18, CP_CURRENT_7_5UA, LPF_RESISTORS_11_5KOHM पूर्ण,
	अणु 749, 0x09, CP_CURRENT_7_5UA, LPF_RESISTORS_11_5KOHM पूर्ण,
	अणु 799, 0x19, CP_CURRENT_7_5UA, LPF_RESISTORS_11_5KOHM पूर्ण,
	अणु 849, 0x29, CP_CURRENT_7_5UA, LPF_RESISTORS_11_5KOHM पूर्ण,
	अणु 899, 0x39, CP_CURRENT_7_5UA, LPF_RESISTORS_11_5KOHM पूर्ण,
	अणु 949, 0x0a, CP_CURRENT_12UA, LPF_RESISTORS_8KOHM पूर्ण,
	अणु 999, 0x1a, CP_CURRENT_12UA, LPF_RESISTORS_8KOHM पूर्ण,
	अणु1049, 0x2a, CP_CURRENT_12UA, LPF_RESISTORS_8KOHM पूर्ण,
	अणु1099, 0x3a, CP_CURRENT_12UA, LPF_RESISTORS_8KOHM पूर्ण,
	अणु1149, 0x0b, CP_CURRENT_12UA, LPF_RESISTORS_10_5KOHM पूर्ण,
	अणु1199, 0x1b, CP_CURRENT_12UA, LPF_RESISTORS_10_5KOHM पूर्ण,
	अणु1249, 0x2b, CP_CURRENT_12UA, LPF_RESISTORS_10_5KOHM पूर्ण,
	अणु1299, 0x3b, CP_CURRENT_12UA, LPF_RESISTORS_10_5KOHM पूर्ण,
	अणु1349, 0x0c, CP_CURRENT_12UA, LPF_RESISTORS_10_5KOHM पूर्ण,
	अणु1399, 0x1c, CP_CURRENT_12UA, LPF_RESISTORS_10_5KOHM पूर्ण,
	अणु1449, 0x2c, CP_CURRENT_12UA, LPF_RESISTORS_10_5KOHM पूर्ण,
	अणु1500, 0x3c, CP_CURRENT_12UA, LPF_RESISTORS_10_5KOHM पूर्ण
पूर्ण;

अटल पूर्णांक max_mbps_to_parameter(अचिन्हित पूर्णांक max_mbps)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dppa_map); i++)
		अगर (dppa_map[i].max_mbps >= max_mbps)
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम dsi_ग_लिखो(काष्ठा dw_mipi_dsi_rockchip *dsi, u32 reg, u32 val)
अणु
	ग_लिखोl(val, dsi->base + reg);
पूर्ण

अटल अंतरभूत u32 dsi_पढ़ो(काष्ठा dw_mipi_dsi_rockchip *dsi, u32 reg)
अणु
	वापस पढ़ोl(dsi->base + reg);
पूर्ण

अटल अंतरभूत व्योम dsi_set(काष्ठा dw_mipi_dsi_rockchip *dsi, u32 reg, u32 mask)
अणु
	dsi_ग_लिखो(dsi, reg, dsi_पढ़ो(dsi, reg) | mask);
पूर्ण

अटल अंतरभूत व्योम dsi_update_bits(काष्ठा dw_mipi_dsi_rockchip *dsi, u32 reg,
				   u32 mask, u32 val)
अणु
	dsi_ग_लिखो(dsi, reg, (dsi_पढ़ो(dsi, reg) & ~mask) | val);
पूर्ण

अटल व्योम dw_mipi_dsi_phy_ग_लिखो(काष्ठा dw_mipi_dsi_rockchip *dsi,
				  u8 test_code,
				  u8 test_data)
अणु
	/*
	 * With the falling edge on TESTCLK, the TESTDIN[7:0] संकेत content
	 * is latched पूर्णांकernally as the current test code. Test data is
	 * programmed पूर्णांकernally by rising edge on TESTCLK.
	 */
	dsi_ग_लिखो(dsi, DSI_PHY_TST_CTRL0, PHY_TESTCLK | PHY_UNTESTCLR);

	dsi_ग_लिखो(dsi, DSI_PHY_TST_CTRL1, PHY_TESTEN | PHY_TESTDOUT(0) |
					  PHY_TESTDIN(test_code));

	dsi_ग_लिखो(dsi, DSI_PHY_TST_CTRL0, PHY_UNTESTCLK | PHY_UNTESTCLR);

	dsi_ग_लिखो(dsi, DSI_PHY_TST_CTRL1, PHY_UNTESTEN | PHY_TESTDOUT(0) |
					  PHY_TESTDIN(test_data));

	dsi_ग_लिखो(dsi, DSI_PHY_TST_CTRL0, PHY_TESTCLK | PHY_UNTESTCLR);
पूर्ण

/*
 * ns2bc - Nanoseconds to byte घड़ी cycles
 */
अटल अंतरभूत अचिन्हित पूर्णांक ns2bc(काष्ठा dw_mipi_dsi_rockchip *dsi, पूर्णांक ns)
अणु
	वापस DIV_ROUND_UP(ns * dsi->lane_mbps / 8, 1000);
पूर्ण

/*
 * ns2ui - Nanoseconds to UI समय periods
 */
अटल अंतरभूत अचिन्हित पूर्णांक ns2ui(काष्ठा dw_mipi_dsi_rockchip *dsi, पूर्णांक ns)
अणु
	वापस DIV_ROUND_UP(ns * dsi->lane_mbps, 1000);
पूर्ण

अटल पूर्णांक dw_mipi_dsi_phy_init(व्योम *priv_data)
अणु
	काष्ठा dw_mipi_dsi_rockchip *dsi = priv_data;
	पूर्णांक ret, i, vco;

	अगर (dsi->phy)
		वापस 0;

	/*
	 * Get vco from frequency(lane_mbps)
	 * vco	frequency table
	 * 000 - between   80 and  200 MHz
	 * 001 - between  200 and  300 MHz
	 * 010 - between  300 and  500 MHz
	 * 011 - between  500 and  700 MHz
	 * 100 - between  700 and  900 MHz
	 * 101 - between  900 and 1100 MHz
	 * 110 - between 1100 and 1300 MHz
	 * 111 - between 1300 and 1500 MHz
	 */
	vco = (dsi->lane_mbps < 200) ? 0 : (dsi->lane_mbps + 100) / 200;

	i = max_mbps_to_parameter(dsi->lane_mbps);
	अगर (i < 0) अणु
		DRM_DEV_ERROR(dsi->dev,
			      "failed to get parameter for %dmbps clock\n",
			      dsi->lane_mbps);
		वापस i;
	पूर्ण

	ret = clk_prepare_enable(dsi->phy_cfg_clk);
	अगर (ret) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to enable phy_cfg_clk\n");
		वापस ret;
	पूर्ण

	dw_mipi_dsi_phy_ग_लिखो(dsi, PLL_BIAS_CUR_SEL_CAP_VCO_CONTROL,
			      BYPASS_VCO_RANGE |
			      VCO_RANGE_CON_SEL(vco) |
			      VCO_IN_CAP_CON_LOW |
			      REF_BIAS_CUR_SEL);

	dw_mipi_dsi_phy_ग_लिखो(dsi, PLL_CP_CONTROL_PLL_LOCK_BYPASS,
			      CP_CURRENT_SEL(dppa_map[i].icpctrl));
	dw_mipi_dsi_phy_ग_लिखो(dsi, PLL_LPF_AND_CP_CONTROL,
			      CP_PROGRAM_EN | LPF_PROGRAM_EN |
			      LPF_RESISTORS_SEL(dppa_map[i].lpfctrl));

	dw_mipi_dsi_phy_ग_लिखो(dsi, HS_RX_CONTROL_OF_LANE_0,
			      HSFREQRANGE_SEL(dppa_map[i].hsfreqrange));

	dw_mipi_dsi_phy_ग_लिखो(dsi, PLL_INPUT_DIVIDER_RATIO,
			      INPUT_DIVIDER(dsi->input_भाग));
	dw_mipi_dsi_phy_ग_लिखो(dsi, PLL_LOOP_DIVIDER_RATIO,
			      LOOP_DIV_LOW_SEL(dsi->feedback_भाग) |
			      LOW_PROGRAM_EN);
	/*
	 * We need set PLL_INPUT_AND_LOOP_DIVIDER_RATIOS_CONTROL immediately
	 * to make the configured LSB effective according to IP simulation
	 * and lab test results.
	 * Only in this way can we get correct mipi phy pll frequency.
	 */
	dw_mipi_dsi_phy_ग_लिखो(dsi, PLL_INPUT_AND_LOOP_DIVIDER_RATIOS_CONTROL,
			      PLL_LOOP_DIV_EN | PLL_INPUT_DIV_EN);
	dw_mipi_dsi_phy_ग_लिखो(dsi, PLL_LOOP_DIVIDER_RATIO,
			      LOOP_DIV_HIGH_SEL(dsi->feedback_भाग) |
			      HIGH_PROGRAM_EN);
	dw_mipi_dsi_phy_ग_लिखो(dsi, PLL_INPUT_AND_LOOP_DIVIDER_RATIOS_CONTROL,
			      PLL_LOOP_DIV_EN | PLL_INPUT_DIV_EN);

	dw_mipi_dsi_phy_ग_लिखो(dsi, AFE_BIAS_BANDGAP_ANALOG_PROGRAMMABILITY,
			      LOW_PROGRAM_EN | BIASEXTR_SEL(BIASEXTR_127_7));
	dw_mipi_dsi_phy_ग_लिखो(dsi, AFE_BIAS_BANDGAP_ANALOG_PROGRAMMABILITY,
			      HIGH_PROGRAM_EN | BANDGAP_SEL(BANDGAP_96_10));

	dw_mipi_dsi_phy_ग_लिखो(dsi, BANDGAP_AND_BIAS_CONTROL,
			      POWER_CONTROL | INTERNAL_REG_CURRENT |
			      BIAS_BLOCK_ON | BANDGAP_ON);

	dw_mipi_dsi_phy_ग_लिखो(dsi, TERMINATION_RESISTER_CONTROL,
			      TER_RESISTOR_LOW | TER_CAL_DONE |
			      SETRD_MAX | TER_RESISTORS_ON);
	dw_mipi_dsi_phy_ग_लिखो(dsi, TERMINATION_RESISTER_CONTROL,
			      TER_RESISTOR_HIGH | LEVEL_SHIFTERS_ON |
			      SETRD_MAX | POWER_MANAGE |
			      TER_RESISTORS_ON);

	dw_mipi_dsi_phy_ग_लिखो(dsi, HS_TX_CLOCK_LANE_REQUEST_STATE_TIME_CONTROL,
			      TLP_PROGRAM_EN | ns2bc(dsi, 500));
	dw_mipi_dsi_phy_ग_लिखो(dsi, HS_TX_CLOCK_LANE_PREPARE_STATE_TIME_CONTROL,
			      THS_PRE_PROGRAM_EN | ns2ui(dsi, 40));
	dw_mipi_dsi_phy_ग_लिखो(dsi, HS_TX_CLOCK_LANE_HS_ZERO_STATE_TIME_CONTROL,
			      THS_ZERO_PROGRAM_EN | ns2bc(dsi, 300));
	dw_mipi_dsi_phy_ग_लिखो(dsi, HS_TX_CLOCK_LANE_TRAIL_STATE_TIME_CONTROL,
			      THS_PRE_PROGRAM_EN | ns2ui(dsi, 100));
	dw_mipi_dsi_phy_ग_लिखो(dsi, HS_TX_CLOCK_LANE_EXIT_STATE_TIME_CONTROL,
			      BIT(5) | ns2bc(dsi, 100));
	dw_mipi_dsi_phy_ग_लिखो(dsi, HS_TX_CLOCK_LANE_POST_TIME_CONTROL,
			      BIT(5) | (ns2bc(dsi, 60) + 7));

	dw_mipi_dsi_phy_ग_लिखो(dsi, HS_TX_DATA_LANE_REQUEST_STATE_TIME_CONTROL,
			      TLP_PROGRAM_EN | ns2bc(dsi, 500));
	dw_mipi_dsi_phy_ग_लिखो(dsi, HS_TX_DATA_LANE_PREPARE_STATE_TIME_CONTROL,
			      THS_PRE_PROGRAM_EN | (ns2ui(dsi, 50) + 20));
	dw_mipi_dsi_phy_ग_लिखो(dsi, HS_TX_DATA_LANE_HS_ZERO_STATE_TIME_CONTROL,
			      THS_ZERO_PROGRAM_EN | (ns2bc(dsi, 140) + 2));
	dw_mipi_dsi_phy_ग_लिखो(dsi, HS_TX_DATA_LANE_TRAIL_STATE_TIME_CONTROL,
			      THS_PRE_PROGRAM_EN | (ns2ui(dsi, 60) + 8));
	dw_mipi_dsi_phy_ग_लिखो(dsi, HS_TX_DATA_LANE_EXIT_STATE_TIME_CONTROL,
			      BIT(5) | ns2bc(dsi, 100));

	clk_disable_unprepare(dsi->phy_cfg_clk);

	वापस ret;
पूर्ण

अटल व्योम dw_mipi_dsi_phy_घातer_on(व्योम *priv_data)
अणु
	काष्ठा dw_mipi_dsi_rockchip *dsi = priv_data;
	पूर्णांक ret;

	ret = phy_set_mode(dsi->phy, PHY_MODE_MIPI_DPHY);
	अगर (ret) अणु
		DRM_DEV_ERROR(dsi->dev, "failed to set phy mode: %d\n", ret);
		वापस;
	पूर्ण

	phy_configure(dsi->phy, &dsi->phy_opts);
	phy_घातer_on(dsi->phy);
पूर्ण

अटल व्योम dw_mipi_dsi_phy_घातer_off(व्योम *priv_data)
अणु
	काष्ठा dw_mipi_dsi_rockchip *dsi = priv_data;

	phy_घातer_off(dsi->phy);
पूर्ण

अटल पूर्णांक
dw_mipi_dsi_get_lane_mbps(व्योम *priv_data, स्थिर काष्ठा drm_display_mode *mode,
			  अचिन्हित दीर्घ mode_flags, u32 lanes, u32 क्रमmat,
			  अचिन्हित पूर्णांक *lane_mbps)
अणु
	काष्ठा dw_mipi_dsi_rockchip *dsi = priv_data;
	पूर्णांक bpp;
	अचिन्हित दीर्घ mpclk, पंचांगp;
	अचिन्हित पूर्णांक target_mbps = 1000;
	अचिन्हित पूर्णांक max_mbps = dppa_map[ARRAY_SIZE(dppa_map) - 1].max_mbps;
	अचिन्हित दीर्घ best_freq = 0;
	अचिन्हित दीर्घ fvco_min, fvco_max, fin, fout;
	अचिन्हित पूर्णांक min_preभाग, max_preभाग;
	अचिन्हित पूर्णांक _preभाग, best_preभाग;
	अचिन्हित दीर्घ _fbभाग, best_fbभाग;
	अचिन्हित दीर्घ min_delta = अच_दीर्घ_उच्च;

	dsi->क्रमmat = क्रमmat;
	bpp = mipi_dsi_pixel_क्रमmat_to_bpp(dsi->क्रमmat);
	अगर (bpp < 0) अणु
		DRM_DEV_ERROR(dsi->dev,
			      "failed to get bpp for pixel format %d\n",
			      dsi->क्रमmat);
		वापस bpp;
	पूर्ण

	mpclk = DIV_ROUND_UP(mode->घड़ी, MSEC_PER_SEC);
	अगर (mpclk) अणु
		/* take 1 / 0.8, since mbps must big than bandwidth of RGB */
		पंचांगp = mpclk * (bpp / lanes) * 10 / 8;
		अगर (पंचांगp < max_mbps)
			target_mbps = पंचांगp;
		अन्यथा
			DRM_DEV_ERROR(dsi->dev,
				      "DPHY clock frequency is out of range\n");
	पूर्ण

	/* क्रम बाह्यal phy only a the mipi_dphy_config is necessary */
	अगर (dsi->phy) अणु
		phy_mipi_dphy_get_शेष_config(mode->घड़ी * 1000 * 10 / 8,
						 bpp, lanes,
						 &dsi->phy_opts.mipi_dphy);
		dsi->lane_mbps = target_mbps;
		*lane_mbps = dsi->lane_mbps;

		वापस 0;
	पूर्ण

	fin = clk_get_rate(dsi->pllref_clk);
	fout = target_mbps * USEC_PER_SEC;

	/* स्थिरraपूर्णांक: 5Mhz <= Fref / N <= 40MHz */
	min_preभाग = DIV_ROUND_UP(fin, 40 * USEC_PER_SEC);
	max_preभाग = fin / (5 * USEC_PER_SEC);

	/* स्थिरraपूर्णांक: 80MHz <= Fvco <= 1500Mhz */
	fvco_min = 80 * USEC_PER_SEC;
	fvco_max = 1500 * USEC_PER_SEC;

	क्रम (_preभाग = min_preभाग; _preभाग <= max_preभाग; _preभाग++) अणु
		u64 पंचांगp;
		u32 delta;
		/* Fvco = Fref * M / N */
		पंचांगp = (u64)fout * _preभाग;
		करो_भाग(पंचांगp, fin);
		_fbभाग = पंचांगp;
		/*
		 * Due to the use of a "by 2 pre-scaler," the range of the
		 * feedback multiplication value M is limited to even भागision
		 * numbers, and m must be greater than 6, not bigger than 512.
		 */
		अगर (_fbभाग < 6 || _fbभाग > 512)
			जारी;

		_fbभाग += _fbभाग % 2;

		पंचांगp = (u64)_fbभाग * fin;
		करो_भाग(पंचांगp, _preभाग);
		अगर (पंचांगp < fvco_min || पंचांगp > fvco_max)
			जारी;

		delta = असल(fout - पंचांगp);
		अगर (delta < min_delta) अणु
			best_preभाग = _preभाग;
			best_fbभाग = _fbभाग;
			min_delta = delta;
			best_freq = पंचांगp;
		पूर्ण
	पूर्ण

	अगर (best_freq) अणु
		dsi->lane_mbps = DIV_ROUND_UP(best_freq, USEC_PER_SEC);
		*lane_mbps = dsi->lane_mbps;
		dsi->input_भाग = best_preभाग;
		dsi->feedback_भाग = best_fbभाग;
	पूर्ण अन्यथा अणु
		DRM_DEV_ERROR(dsi->dev, "Can not find best_freq for DPHY\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा hstt अणु
	अचिन्हित पूर्णांक maxfreq;
	काष्ठा dw_mipi_dsi_dphy_timing timing;
पूर्ण;

#घोषणा HSTT(_maxfreq, _c_lp2hs, _c_hs2lp, _d_lp2hs, _d_hs2lp)	\
अणु					\
	.maxfreq = _maxfreq,		\
	.timing = अणु			\
		.clk_lp2hs = _c_lp2hs,	\
		.clk_hs2lp = _c_hs2lp,	\
		.data_lp2hs = _d_lp2hs,	\
		.data_hs2lp = _d_hs2lp,	\
	पूर्ण				\
पूर्ण

/* Table A-3 High-Speed Transition Times */
काष्ठा hstt hstt_table[] = अणु
	HSTT(  90,  32, 20,  26, 13),
	HSTT( 100,  35, 23,  28, 14),
	HSTT( 110,  32, 22,  26, 13),
	HSTT( 130,  31, 20,  27, 13),
	HSTT( 140,  33, 22,  26, 14),
	HSTT( 150,  33, 21,  26, 14),
	HSTT( 170,  32, 20,  27, 13),
	HSTT( 180,  36, 23,  30, 15),
	HSTT( 200,  40, 22,  33, 15),
	HSTT( 220,  40, 22,  33, 15),
	HSTT( 240,  44, 24,  36, 16),
	HSTT( 250,  48, 24,  38, 17),
	HSTT( 270,  48, 24,  38, 17),
	HSTT( 300,  50, 27,  41, 18),
	HSTT( 330,  56, 28,  45, 18),
	HSTT( 360,  59, 28,  48, 19),
	HSTT( 400,  61, 30,  50, 20),
	HSTT( 450,  67, 31,  55, 21),
	HSTT( 500,  73, 31,  59, 22),
	HSTT( 550,  79, 36,  63, 24),
	HSTT( 600,  83, 37,  68, 25),
	HSTT( 650,  90, 38,  73, 27),
	HSTT( 700,  95, 40,  77, 28),
	HSTT( 750, 102, 40,  84, 28),
	HSTT( 800, 106, 42,  87, 30),
	HSTT( 850, 113, 44,  93, 31),
	HSTT( 900, 118, 47,  98, 32),
	HSTT( 950, 124, 47, 102, 34),
	HSTT(1000, 130, 49, 107, 35),
	HSTT(1050, 135, 51, 111, 37),
	HSTT(1100, 139, 51, 114, 38),
	HSTT(1150, 146, 54, 120, 40),
	HSTT(1200, 153, 57, 125, 41),
	HSTT(1250, 158, 58, 130, 42),
	HSTT(1300, 163, 58, 135, 44),
	HSTT(1350, 168, 60, 140, 45),
	HSTT(1400, 172, 64, 144, 47),
	HSTT(1450, 176, 65, 148, 48),
	HSTT(1500, 181, 66, 153, 50)
पूर्ण;

अटल पूर्णांक
dw_mipi_dsi_phy_get_timing(व्योम *priv_data, अचिन्हित पूर्णांक lane_mbps,
			   काष्ठा dw_mipi_dsi_dphy_timing *timing)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hstt_table); i++)
		अगर (lane_mbps < hstt_table[i].maxfreq)
			अवरोध;

	अगर (i == ARRAY_SIZE(hstt_table))
		i--;

	*timing = hstt_table[i].timing;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_mipi_dsi_phy_ops dw_mipi_dsi_rockchip_phy_ops = अणु
	.init = dw_mipi_dsi_phy_init,
	.घातer_on = dw_mipi_dsi_phy_घातer_on,
	.घातer_off = dw_mipi_dsi_phy_घातer_off,
	.get_lane_mbps = dw_mipi_dsi_get_lane_mbps,
	.get_timing = dw_mipi_dsi_phy_get_timing,
पूर्ण;

अटल व्योम dw_mipi_dsi_rockchip_config(काष्ठा dw_mipi_dsi_rockchip *dsi,
					पूर्णांक mux)
अणु
	अगर (dsi->cdata->lcdsel_grf_reg)
		regmap_ग_लिखो(dsi->grf_regmap, dsi->cdata->lcdsel_grf_reg,
			mux ? dsi->cdata->lcdsel_lit : dsi->cdata->lcdsel_big);

	अगर (dsi->cdata->lanecfg1_grf_reg)
		regmap_ग_लिखो(dsi->grf_regmap, dsi->cdata->lanecfg1_grf_reg,
					      dsi->cdata->lanecfg1);

	अगर (dsi->cdata->lanecfg2_grf_reg)
		regmap_ग_लिखो(dsi->grf_regmap, dsi->cdata->lanecfg2_grf_reg,
					      dsi->cdata->lanecfg2);

	अगर (dsi->cdata->enable_grf_reg)
		regmap_ग_लिखो(dsi->grf_regmap, dsi->cdata->enable_grf_reg,
					      dsi->cdata->enable);
पूर्ण

अटल पूर्णांक
dw_mipi_dsi_encoder_atomic_check(काष्ठा drm_encoder *encoder,
				 काष्ठा drm_crtc_state *crtc_state,
				 काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा rockchip_crtc_state *s = to_rockchip_crtc_state(crtc_state);
	काष्ठा dw_mipi_dsi_rockchip *dsi = to_dsi(encoder);

	चयन (dsi->क्रमmat) अणु
	हाल MIPI_DSI_FMT_RGB888:
		s->output_mode = ROCKCHIP_OUT_MODE_P888;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666:
		s->output_mode = ROCKCHIP_OUT_MODE_P666;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB565:
		s->output_mode = ROCKCHIP_OUT_MODE_P565;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	s->output_type = DRM_MODE_CONNECTOR_DSI;
	अगर (dsi->slave)
		s->output_flags = ROCKCHIP_OUTPUT_DSI_DUAL;

	वापस 0;
पूर्ण

अटल व्योम dw_mipi_dsi_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा dw_mipi_dsi_rockchip *dsi = to_dsi(encoder);
	पूर्णांक ret, mux;

	mux = drm_of_encoder_active_endpoपूर्णांक_id(dsi->dev->of_node,
						&dsi->encoder);
	अगर (mux < 0)
		वापस;

	pm_runसमय_get_sync(dsi->dev);
	अगर (dsi->slave)
		pm_runसमय_get_sync(dsi->slave->dev);

	/*
	 * For the RK3399, the clk of grf must be enabled beक्रमe writing grf
	 * रेजिस्टर. And क्रम RK3288 or other soc, this grf_clk must be शून्य,
	 * the clk_prepare_enable वापस true directly.
	 */
	ret = clk_prepare_enable(dsi->grf_clk);
	अगर (ret) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to enable grf_clk: %d\n", ret);
		वापस;
	पूर्ण

	dw_mipi_dsi_rockchip_config(dsi, mux);
	अगर (dsi->slave)
		dw_mipi_dsi_rockchip_config(dsi->slave, mux);

	clk_disable_unprepare(dsi->grf_clk);
पूर्ण

अटल व्योम dw_mipi_dsi_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा dw_mipi_dsi_rockchip *dsi = to_dsi(encoder);

	अगर (dsi->slave)
		pm_runसमय_put(dsi->slave->dev);
	pm_runसमय_put(dsi->dev);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs
dw_mipi_dsi_encoder_helper_funcs = अणु
	.atomic_check = dw_mipi_dsi_encoder_atomic_check,
	.enable = dw_mipi_dsi_encoder_enable,
	.disable = dw_mipi_dsi_encoder_disable,
पूर्ण;

अटल पूर्णांक rockchip_dsi_drm_create_encoder(काष्ठा dw_mipi_dsi_rockchip *dsi,
					   काष्ठा drm_device *drm_dev)
अणु
	काष्ठा drm_encoder *encoder = &dsi->encoder;
	पूर्णांक ret;

	encoder->possible_crtcs = drm_of_find_possible_crtcs(drm_dev,
							     dsi->dev->of_node);

	ret = drm_simple_encoder_init(drm_dev, encoder, DRM_MODE_ENCODER_DSI);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize encoder with drm\n");
		वापस ret;
	पूर्ण

	drm_encoder_helper_add(encoder, &dw_mipi_dsi_encoder_helper_funcs);

	वापस 0;
पूर्ण

अटल काष्ठा device
*dw_mipi_dsi_rockchip_find_second(काष्ठा dw_mipi_dsi_rockchip *dsi)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *node = शून्य, *local;

	match = of_match_device(dsi->dev->driver->of_match_table, dsi->dev);

	local = of_graph_get_remote_node(dsi->dev->of_node, 1, 0);
	अगर (!local)
		वापस शून्य;

	जबतक ((node = of_find_compatible_node(node, शून्य,
					       match->compatible))) अणु
		काष्ठा device_node *remote;

		/* found ourself */
		अगर (node == dsi->dev->of_node)
			जारी;

		remote = of_graph_get_remote_node(node, 1, 0);
		अगर (!remote)
			जारी;

		/* same display device in port1-ep0 क्रम both */
		अगर (remote == local) अणु
			काष्ठा dw_mipi_dsi_rockchip *dsi2;
			काष्ठा platक्रमm_device *pdev;

			pdev = of_find_device_by_node(node);

			/*
			 * we have found the second, so will either वापस it
			 * or वापस with an error. In any हाल won't need the
			 * nodes anymore nor जारी the loop.
			 */
			of_node_put(remote);
			of_node_put(node);
			of_node_put(local);

			अगर (!pdev)
				वापस ERR_PTR(-EPROBE_DEFER);

			dsi2 = platक्रमm_get_drvdata(pdev);
			अगर (!dsi2) अणु
				platक्रमm_device_put(pdev);
				वापस ERR_PTR(-EPROBE_DEFER);
			पूर्ण

			वापस &pdev->dev;
		पूर्ण

		of_node_put(remote);
	पूर्ण

	of_node_put(local);

	वापस शून्य;
पूर्ण

अटल पूर्णांक dw_mipi_dsi_rockchip_bind(काष्ठा device *dev,
				     काष्ठा device *master,
				     व्योम *data)
अणु
	काष्ठा dw_mipi_dsi_rockchip *dsi = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा device *second;
	bool master1, master2;
	पूर्णांक ret;

	second = dw_mipi_dsi_rockchip_find_second(dsi);
	अगर (IS_ERR(second))
		वापस PTR_ERR(second);

	अगर (second) अणु
		master1 = of_property_पढ़ो_bool(dsi->dev->of_node,
						"clock-master");
		master2 = of_property_पढ़ो_bool(second->of_node,
						"clock-master");

		अगर (master1 && master2) अणु
			DRM_DEV_ERROR(dsi->dev, "only one clock-master allowed\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!master1 && !master2) अणु
			DRM_DEV_ERROR(dsi->dev, "no clock-master defined\n");
			वापस -EINVAL;
		पूर्ण

		/* we are the slave in dual-DSI */
		अगर (!master1) अणु
			dsi->is_slave = true;
			वापस 0;
		पूर्ण

		dsi->slave = dev_get_drvdata(second);
		अगर (!dsi->slave) अणु
			DRM_DEV_ERROR(dev, "could not get slaves data\n");
			वापस -ENODEV;
		पूर्ण

		dsi->slave->is_slave = true;
		dw_mipi_dsi_set_slave(dsi->dmd, dsi->slave->dmd);
		put_device(second);
	पूर्ण

	ret = clk_prepare_enable(dsi->pllref_clk);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "Failed to enable pllref_clk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = rockchip_dsi_drm_create_encoder(dsi, drm_dev);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "Failed to create drm encoder\n");
		वापस ret;
	पूर्ण

	ret = dw_mipi_dsi_bind(dsi->dmd, &dsi->encoder);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "Failed to bind: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dw_mipi_dsi_rockchip_unbind(काष्ठा device *dev,
					काष्ठा device *master,
					व्योम *data)
अणु
	काष्ठा dw_mipi_dsi_rockchip *dsi = dev_get_drvdata(dev);

	अगर (dsi->is_slave)
		वापस;

	dw_mipi_dsi_unbind(dsi->dmd);

	clk_disable_unprepare(dsi->pllref_clk);
पूर्ण

अटल स्थिर काष्ठा component_ops dw_mipi_dsi_rockchip_ops = अणु
	.bind	= dw_mipi_dsi_rockchip_bind,
	.unbind	= dw_mipi_dsi_rockchip_unbind,
पूर्ण;

अटल पूर्णांक dw_mipi_dsi_rockchip_host_attach(व्योम *priv_data,
					    काष्ठा mipi_dsi_device *device)
अणु
	काष्ठा dw_mipi_dsi_rockchip *dsi = priv_data;
	काष्ठा device *second;
	पूर्णांक ret;

	ret = component_add(dsi->dev, &dw_mipi_dsi_rockchip_ops);
	अगर (ret) अणु
		DRM_DEV_ERROR(dsi->dev, "Failed to register component: %d\n",
					ret);
		वापस ret;
	पूर्ण

	second = dw_mipi_dsi_rockchip_find_second(dsi);
	अगर (IS_ERR(second))
		वापस PTR_ERR(second);
	अगर (second) अणु
		ret = component_add(second, &dw_mipi_dsi_rockchip_ops);
		अगर (ret) अणु
			DRM_DEV_ERROR(second,
				      "Failed to register component: %d\n",
				      ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dw_mipi_dsi_rockchip_host_detach(व्योम *priv_data,
					    काष्ठा mipi_dsi_device *device)
अणु
	काष्ठा dw_mipi_dsi_rockchip *dsi = priv_data;
	काष्ठा device *second;

	second = dw_mipi_dsi_rockchip_find_second(dsi);
	अगर (second && !IS_ERR(second))
		component_del(second, &dw_mipi_dsi_rockchip_ops);

	component_del(dsi->dev, &dw_mipi_dsi_rockchip_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_mipi_dsi_host_ops dw_mipi_dsi_rockchip_host_ops = अणु
	.attach = dw_mipi_dsi_rockchip_host_attach,
	.detach = dw_mipi_dsi_rockchip_host_detach,
पूर्ण;

अटल पूर्णांक dw_mipi_dsi_rockchip_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा dw_mipi_dsi_rockchip *dsi;
	काष्ठा resource *res;
	स्थिर काष्ठा rockchip_dw_dsi_chip_data *cdata =
				of_device_get_match_data(dev);
	पूर्णांक ret, i;

	dsi = devm_kzalloc(dev, माप(*dsi), GFP_KERNEL);
	अगर (!dsi)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dsi->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(dsi->base)) अणु
		DRM_DEV_ERROR(dev, "Unable to get dsi registers\n");
		वापस PTR_ERR(dsi->base);
	पूर्ण

	i = 0;
	जबतक (cdata[i].reg) अणु
		अगर (cdata[i].reg == res->start) अणु
			dsi->cdata = &cdata[i];
			अवरोध;
		पूर्ण

		i++;
	पूर्ण

	अगर (!dsi->cdata) अणु
		DRM_DEV_ERROR(dev, "no dsi-config for %s node\n", np->name);
		वापस -EINVAL;
	पूर्ण

	/* try to get a possible बाह्यal dphy */
	dsi->phy = devm_phy_optional_get(dev, "dphy");
	अगर (IS_ERR(dsi->phy)) अणु
		ret = PTR_ERR(dsi->phy);
		DRM_DEV_ERROR(dev, "failed to get mipi dphy: %d\n", ret);
		वापस ret;
	पूर्ण

	dsi->pllref_clk = devm_clk_get(dev, "ref");
	अगर (IS_ERR(dsi->pllref_clk)) अणु
		अगर (dsi->phy) अणु
			/*
			 * अगर बाह्यal phy is present, pll will be
			 * generated there.
			 */
			dsi->pllref_clk = शून्य;
		पूर्ण अन्यथा अणु
			ret = PTR_ERR(dsi->pllref_clk);
			DRM_DEV_ERROR(dev,
				      "Unable to get pll reference clock: %d\n",
				      ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (dsi->cdata->flags & DW_MIPI_NEEDS_PHY_CFG_CLK) अणु
		dsi->phy_cfg_clk = devm_clk_get(dev, "phy_cfg");
		अगर (IS_ERR(dsi->phy_cfg_clk)) अणु
			ret = PTR_ERR(dsi->phy_cfg_clk);
			DRM_DEV_ERROR(dev,
				      "Unable to get phy_cfg_clk: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (dsi->cdata->flags & DW_MIPI_NEEDS_GRF_CLK) अणु
		dsi->grf_clk = devm_clk_get(dev, "grf");
		अगर (IS_ERR(dsi->grf_clk)) अणु
			ret = PTR_ERR(dsi->grf_clk);
			DRM_DEV_ERROR(dev, "Unable to get grf_clk: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	dsi->grf_regmap = syscon_regmap_lookup_by_phandle(np, "rockchip,grf");
	अगर (IS_ERR(dsi->grf_regmap)) अणु
		DRM_DEV_ERROR(dev, "Unable to get rockchip,grf\n");
		वापस PTR_ERR(dsi->grf_regmap);
	पूर्ण

	dsi->dev = dev;
	dsi->pdata.base = dsi->base;
	dsi->pdata.max_data_lanes = dsi->cdata->max_data_lanes;
	dsi->pdata.phy_ops = &dw_mipi_dsi_rockchip_phy_ops;
	dsi->pdata.host_ops = &dw_mipi_dsi_rockchip_host_ops;
	dsi->pdata.priv_data = dsi;
	platक्रमm_set_drvdata(pdev, dsi);

	dsi->dmd = dw_mipi_dsi_probe(pdev, &dsi->pdata);
	अगर (IS_ERR(dsi->dmd)) अणु
		ret = PTR_ERR(dsi->dmd);
		अगर (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev,
				      "Failed to probe dw_mipi_dsi: %d\n", ret);
		जाओ err_clkdisable;
	पूर्ण

	वापस 0;

err_clkdisable:
	clk_disable_unprepare(dsi->pllref_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक dw_mipi_dsi_rockchip_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_mipi_dsi_rockchip *dsi = platक्रमm_get_drvdata(pdev);

	अगर (dsi->devcnt == 0)
		component_del(dsi->dev, &dw_mipi_dsi_rockchip_ops);

	dw_mipi_dsi_हटाओ(dsi->dmd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rockchip_dw_dsi_chip_data px30_chip_data[] = अणु
	अणु
		.reg = 0xff450000,
		.lcdsel_grf_reg = PX30_GRF_PD_VO_CON1,
		.lcdsel_big = HIWORD_UPDATE(0, PX30_DSI_LCDC_SEL),
		.lcdsel_lit = HIWORD_UPDATE(PX30_DSI_LCDC_SEL,
					    PX30_DSI_LCDC_SEL),

		.lanecfg1_grf_reg = PX30_GRF_PD_VO_CON1,
		.lanecfg1 = HIWORD_UPDATE(0, PX30_DSI_TURNDISABLE |
					     PX30_DSI_FORCERXMODE |
					     PX30_DSI_FORCETXSTOPMODE),

		.max_data_lanes = 4,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rockchip_dw_dsi_chip_data rk3288_chip_data[] = अणु
	अणु
		.reg = 0xff960000,
		.lcdsel_grf_reg = RK3288_GRF_SOC_CON6,
		.lcdsel_big = HIWORD_UPDATE(0, RK3288_DSI0_LCDC_SEL),
		.lcdsel_lit = HIWORD_UPDATE(RK3288_DSI0_LCDC_SEL, RK3288_DSI0_LCDC_SEL),

		.max_data_lanes = 4,
	पूर्ण,
	अणु
		.reg = 0xff964000,
		.lcdsel_grf_reg = RK3288_GRF_SOC_CON6,
		.lcdsel_big = HIWORD_UPDATE(0, RK3288_DSI1_LCDC_SEL),
		.lcdsel_lit = HIWORD_UPDATE(RK3288_DSI1_LCDC_SEL, RK3288_DSI1_LCDC_SEL),

		.max_data_lanes = 4,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rockchip_dw_dsi_chip_data rk3399_chip_data[] = अणु
	अणु
		.reg = 0xff960000,
		.lcdsel_grf_reg = RK3399_GRF_SOC_CON20,
		.lcdsel_big = HIWORD_UPDATE(0, RK3399_DSI0_LCDC_SEL),
		.lcdsel_lit = HIWORD_UPDATE(RK3399_DSI0_LCDC_SEL,
					    RK3399_DSI0_LCDC_SEL),

		.lanecfg1_grf_reg = RK3399_GRF_SOC_CON22,
		.lanecfg1 = HIWORD_UPDATE(0, RK3399_DSI0_TURNREQUEST |
					     RK3399_DSI0_TURNDISABLE |
					     RK3399_DSI0_FORCETXSTOPMODE |
					     RK3399_DSI0_FORCERXMODE),

		.flags = DW_MIPI_NEEDS_PHY_CFG_CLK | DW_MIPI_NEEDS_GRF_CLK,
		.max_data_lanes = 4,
	पूर्ण,
	अणु
		.reg = 0xff968000,
		.lcdsel_grf_reg = RK3399_GRF_SOC_CON20,
		.lcdsel_big = HIWORD_UPDATE(0, RK3399_DSI1_LCDC_SEL),
		.lcdsel_lit = HIWORD_UPDATE(RK3399_DSI1_LCDC_SEL,
					    RK3399_DSI1_LCDC_SEL),

		.lanecfg1_grf_reg = RK3399_GRF_SOC_CON23,
		.lanecfg1 = HIWORD_UPDATE(0, RK3399_DSI1_TURNDISABLE |
					     RK3399_DSI1_FORCETXSTOPMODE |
					     RK3399_DSI1_FORCERXMODE |
					     RK3399_DSI1_ENABLE),

		.lanecfg2_grf_reg = RK3399_GRF_SOC_CON24,
		.lanecfg2 = HIWORD_UPDATE(RK3399_TXRX_MASTERSLAVEZ |
					  RK3399_TXRX_ENABLECLK,
					  RK3399_TXRX_MASTERSLAVEZ |
					  RK3399_TXRX_ENABLECLK |
					  RK3399_TXRX_BASEसूची),

		.enable_grf_reg = RK3399_GRF_SOC_CON23,
		.enable = HIWORD_UPDATE(RK3399_DSI1_ENABLE, RK3399_DSI1_ENABLE),

		.flags = DW_MIPI_NEEDS_PHY_CFG_CLK | DW_MIPI_NEEDS_GRF_CLK,
		.max_data_lanes = 4,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id dw_mipi_dsi_rockchip_dt_ids[] = अणु
	अणु
	 .compatible = "rockchip,px30-mipi-dsi",
	 .data = &px30_chip_data,
	पूर्ण, अणु
	 .compatible = "rockchip,rk3288-mipi-dsi",
	 .data = &rk3288_chip_data,
	पूर्ण, अणु
	 .compatible = "rockchip,rk3399-mipi-dsi",
	 .data = &rk3399_chip_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dw_mipi_dsi_rockchip_dt_ids);

काष्ठा platक्रमm_driver dw_mipi_dsi_rockchip_driver = अणु
	.probe		= dw_mipi_dsi_rockchip_probe,
	.हटाओ		= dw_mipi_dsi_rockchip_हटाओ,
	.driver		= अणु
		.of_match_table = dw_mipi_dsi_rockchip_dt_ids,
		.name	= "dw-mipi-dsi-rockchip",
	पूर्ण,
पूर्ण;
