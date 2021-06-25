<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/**
 * PCIe SERDES driver क्रम AM654x SoC
 *
 * Copyright (C) 2018 - 2019 Texas Instruments Incorporated - http://www.ti.com/
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <dt-bindings/phy/phy.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mux/consumer.h>
#समावेश <linux/of_address.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#घोषणा CMU_R004		0x4
#घोषणा CMU_R060		0x60
#घोषणा CMU_R07C		0x7c
#घोषणा CMU_R088		0x88
#घोषणा CMU_R0D0		0xd0
#घोषणा CMU_R0E8		0xe8

#घोषणा LANE_R048		0x248
#घोषणा LANE_R058		0x258
#घोषणा LANE_R06c		0x26c
#घोषणा LANE_R070		0x270
#घोषणा LANE_R070		0x270
#घोषणा LANE_R19C		0x39c

#घोषणा COMLANE_R004		0xa04
#घोषणा COMLANE_R138		0xb38
#घोषणा VERSION_VAL		0x70

#घोषणा COMLANE_R190		0xb90
#घोषणा COMLANE_R194		0xb94

#घोषणा COMRXEQ_R004		0x1404
#घोषणा COMRXEQ_R008		0x1408
#घोषणा COMRXEQ_R00C		0x140c
#घोषणा COMRXEQ_R014		0x1414
#घोषणा COMRXEQ_R018		0x1418
#घोषणा COMRXEQ_R01C		0x141c
#घोषणा COMRXEQ_R04C		0x144c
#घोषणा COMRXEQ_R088		0x1488
#घोषणा COMRXEQ_R094		0x1494
#घोषणा COMRXEQ_R098		0x1498

#घोषणा SERDES_CTRL		0x1fd0

#घोषणा WIZ_LANEXCTL_STS	0x1fe0
#घोषणा TX0_DISABLE_STATE	0x4
#घोषणा TX0_SLEEP_STATE		0x5
#घोषणा TX0_SNOOZE_STATE	0x6
#घोषणा TX0_ENABLE_STATE	0x7

#घोषणा RX0_DISABLE_STATE	0x4
#घोषणा RX0_SLEEP_STATE		0x5
#घोषणा RX0_SNOOZE_STATE	0x6
#घोषणा RX0_ENABLE_STATE	0x7

#घोषणा WIZ_PLL_CTRL		0x1ff4
#घोषणा PLL_DISABLE_STATE	0x4
#घोषणा PLL_SLEEP_STATE		0x5
#घोषणा PLL_SNOOZE_STATE	0x6
#घोषणा PLL_ENABLE_STATE	0x7

#घोषणा PLL_LOCK_TIME		100000	/* in microseconds */
#घोषणा SLEEP_TIME		100	/* in microseconds */

#घोषणा LANE_USB3		0x0
#घोषणा LANE_PCIE0_LANE0	0x1

#घोषणा LANE_PCIE1_LANE0	0x0
#घोषणा LANE_PCIE0_LANE1	0x1

#घोषणा SERDES_NUM_CLOCKS	3

#घोषणा AM654_SERDES_CTRL_CLKSEL_MASK	GENMASK(7, 4)
#घोषणा AM654_SERDES_CTRL_CLKSEL_SHIFT	4

काष्ठा serdes_am654_clk_mux अणु
	काष्ठा clk_hw	hw;
	काष्ठा regmap	*regmap;
	अचिन्हित पूर्णांक	reg;
	पूर्णांक		clk_id;
	काष्ठा clk_init_data clk_data;
पूर्ण;

#घोषणा to_serdes_am654_clk_mux(_hw)	\
		container_of(_hw, काष्ठा serdes_am654_clk_mux, hw)

अटल स्थिर काष्ठा regmap_config serdes_am654_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.fast_io = true,
	.max_रेजिस्टर = 0x1ffc,
पूर्ण;

क्रमागत serdes_am654_fields अणु
	/* CMU PLL Control */
	CMU_PLL_CTRL,

	LANE_PLL_CTRL_RXEQ_RXIDLE,

	/* CMU VCO bias current and VREG setting */
	AHB_PMA_CM_VCO_VBIAS_VREG,
	AHB_PMA_CM_VCO_BIAS_VREG,

	AHB_PMA_CM_SR,
	AHB_SSC_GEN_Z_O_20_13,

	/* AHB PMA Lane Configuration */
	AHB_PMA_LN_AGC_THSEL_VREGH,

	/* AGC and Signal detect threshold क्रम Gen3 */
	AHB_PMA_LN_GEN3_AGC_SD_THSEL,

	AHB_PMA_LN_RX_SELR_GEN3,
	AHB_PMA_LN_TX_DRV,

	/* CMU Master Reset */
	CMU_MASTER_CDN,

	/* P2S ring buffer initial startup poपूर्णांकer dअगरference */
	P2S_RBUF_PTR_DIFF,

	CONFIG_VERSION,

	/* Lane 1 Master Reset */
	L1_MASTER_CDN,

	/* CMU OK Status */
	CMU_OK_I_0,

	/* Mid-speed initial calibration control */
	COMRXEQ_MS_INIT_CTRL_7_0,

	/* High-speed initial calibration control */
	COMRXEQ_HS_INIT_CAL_7_0,

	/* Mid-speed recalibration control */
	COMRXEQ_MS_RECAL_CTRL_7_0,

	/* High-speed recalibration control */
	COMRXEQ_HS_RECAL_CTRL_7_0,

	/* ATT configuration */
	COMRXEQ_CSR_ATT_CONFIG,

	/* Edge based boost adaptation winकरोw length */
	COMRXEQ_CSR_EBSTADAPT_WIN_LEN,

	/* COMRXEQ control 3 & 4 */
	COMRXEQ_CTRL_3_4,

	/* COMRXEQ control 14, 15 and 16*/
	COMRXEQ_CTRL_14_15_16,

	/* Threshold क्रम errors in pattern data  */
	COMRXEQ_CSR_DLEV_ERR_THRESH,

	/* COMRXEQ control 25 */
	COMRXEQ_CTRL_25,

	/* Mid-speed rate change calibration control */
	CSR_RXEQ_RATE_CHANGE_CAL_RUN_RATE2_O,

	/* High-speed rate change calibration control */
	COMRXEQ_HS_RCHANGE_CTRL_7_0,

	/* Serdes reset */
	POR_EN,

	/* Tx Enable Value */
	TX0_ENABLE,

	/* Rx Enable Value */
	RX0_ENABLE,

	/* PLL Enable Value */
	PLL_ENABLE,

	/* PLL पढ़ोy क्रम use */
	PLL_OK,

	/* sentinel */
	MAX_FIELDS

पूर्ण;

अटल स्थिर काष्ठा reg_field serdes_am654_reg_fields[] = अणु
	[CMU_PLL_CTRL]			= REG_FIELD(CMU_R004, 8, 15),
	[AHB_PMA_CM_VCO_VBIAS_VREG]	= REG_FIELD(CMU_R060, 8, 15),
	[CMU_MASTER_CDN]		= REG_FIELD(CMU_R07C, 24, 31),
	[AHB_PMA_CM_VCO_BIAS_VREG]	= REG_FIELD(CMU_R088, 24, 31),
	[AHB_PMA_CM_SR]			= REG_FIELD(CMU_R0D0, 24, 31),
	[AHB_SSC_GEN_Z_O_20_13]		= REG_FIELD(CMU_R0E8, 8, 15),
	[LANE_PLL_CTRL_RXEQ_RXIDLE]	= REG_FIELD(LANE_R048, 8, 15),
	[AHB_PMA_LN_AGC_THSEL_VREGH]	= REG_FIELD(LANE_R058, 16, 23),
	[AHB_PMA_LN_GEN3_AGC_SD_THSEL]	= REG_FIELD(LANE_R06c, 0, 7),
	[AHB_PMA_LN_RX_SELR_GEN3]	= REG_FIELD(LANE_R070, 16, 23),
	[AHB_PMA_LN_TX_DRV]		= REG_FIELD(LANE_R19C, 16, 23),
	[P2S_RBUF_PTR_DIFF]		= REG_FIELD(COMLANE_R004, 0, 7),
	[CONFIG_VERSION]		= REG_FIELD(COMLANE_R138, 16, 23),
	[L1_MASTER_CDN]			= REG_FIELD(COMLANE_R190, 8, 15),
	[CMU_OK_I_0]			= REG_FIELD(COMLANE_R194, 19, 19),
	[COMRXEQ_MS_INIT_CTRL_7_0]	= REG_FIELD(COMRXEQ_R004, 24, 31),
	[COMRXEQ_HS_INIT_CAL_7_0]	= REG_FIELD(COMRXEQ_R008, 0, 7),
	[COMRXEQ_MS_RECAL_CTRL_7_0]	= REG_FIELD(COMRXEQ_R00C, 8, 15),
	[COMRXEQ_HS_RECAL_CTRL_7_0]	= REG_FIELD(COMRXEQ_R00C, 16, 23),
	[COMRXEQ_CSR_ATT_CONFIG]	= REG_FIELD(COMRXEQ_R014, 16, 23),
	[COMRXEQ_CSR_EBSTADAPT_WIN_LEN]	= REG_FIELD(COMRXEQ_R018, 16, 23),
	[COMRXEQ_CTRL_3_4]		= REG_FIELD(COMRXEQ_R01C, 8, 15),
	[COMRXEQ_CTRL_14_15_16]		= REG_FIELD(COMRXEQ_R04C, 0, 7),
	[COMRXEQ_CSR_DLEV_ERR_THRESH]	= REG_FIELD(COMRXEQ_R088, 16, 23),
	[COMRXEQ_CTRL_25]		= REG_FIELD(COMRXEQ_R094, 24, 31),
	[CSR_RXEQ_RATE_CHANGE_CAL_RUN_RATE2_O] = REG_FIELD(COMRXEQ_R098, 8, 15),
	[COMRXEQ_HS_RCHANGE_CTRL_7_0]	= REG_FIELD(COMRXEQ_R098, 16, 23),
	[POR_EN]			= REG_FIELD(SERDES_CTRL, 29, 29),
	[TX0_ENABLE]			= REG_FIELD(WIZ_LANEXCTL_STS, 29, 31),
	[RX0_ENABLE]			= REG_FIELD(WIZ_LANEXCTL_STS, 13, 15),
	[PLL_ENABLE]			= REG_FIELD(WIZ_PLL_CTRL, 29, 31),
	[PLL_OK]			= REG_FIELD(WIZ_PLL_CTRL, 28, 28),
पूर्ण;

काष्ठा serdes_am654 अणु
	काष्ठा regmap		*regmap;
	काष्ठा regmap_field	*fields[MAX_FIELDS];

	काष्ठा device		*dev;
	काष्ठा mux_control	*control;
	bool			busy;
	u32			type;
	काष्ठा device_node	*of_node;
	काष्ठा clk_onecell_data	clk_data;
	काष्ठा clk		*clks[SERDES_NUM_CLOCKS];
पूर्ण;

अटल पूर्णांक serdes_am654_enable_pll(काष्ठा serdes_am654 *phy)
अणु
	पूर्णांक ret;
	u32 val;

	ret = regmap_field_ग_लिखो(phy->fields[PLL_ENABLE], PLL_ENABLE_STATE);
	अगर (ret)
		वापस ret;

	वापस regmap_field_पढ़ो_poll_समयout(phy->fields[PLL_OK], val, val,
					      1000, PLL_LOCK_TIME);
पूर्ण

अटल व्योम serdes_am654_disable_pll(काष्ठा serdes_am654 *phy)
अणु
	काष्ठा device *dev = phy->dev;
	पूर्णांक ret;

	ret = regmap_field_ग_लिखो(phy->fields[PLL_ENABLE], PLL_DISABLE_STATE);
	अगर (ret)
		dev_err(dev, "Failed to disable PLL\n");
पूर्ण

अटल पूर्णांक serdes_am654_enable_txrx(काष्ठा serdes_am654 *phy)
अणु
	पूर्णांक ret = 0;

	/* Enable TX */
	ret |= regmap_field_ग_लिखो(phy->fields[TX0_ENABLE], TX0_ENABLE_STATE);

	/* Enable RX */
	ret |= regmap_field_ग_लिखो(phy->fields[RX0_ENABLE], RX0_ENABLE_STATE);

	अगर (ret)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक serdes_am654_disable_txrx(काष्ठा serdes_am654 *phy)
अणु
	पूर्णांक ret = 0;

	/* Disable TX */
	ret |= regmap_field_ग_लिखो(phy->fields[TX0_ENABLE], TX0_DISABLE_STATE);

	/* Disable RX */
	ret |= regmap_field_ग_लिखो(phy->fields[RX0_ENABLE], RX0_DISABLE_STATE);

	अगर (ret)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक serdes_am654_घातer_on(काष्ठा phy *x)
अणु
	काष्ठा serdes_am654 *phy = phy_get_drvdata(x);
	काष्ठा device *dev = phy->dev;
	पूर्णांक ret;
	u32 val;

	ret = serdes_am654_enable_pll(phy);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable PLL\n");
		वापस ret;
	पूर्ण

	ret = serdes_am654_enable_txrx(phy);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable TX RX\n");
		वापस ret;
	पूर्ण

	वापस regmap_field_पढ़ो_poll_समयout(phy->fields[CMU_OK_I_0], val,
					      val, SLEEP_TIME, PLL_LOCK_TIME);
पूर्ण

अटल पूर्णांक serdes_am654_घातer_off(काष्ठा phy *x)
अणु
	काष्ठा serdes_am654 *phy = phy_get_drvdata(x);

	serdes_am654_disable_txrx(phy);
	serdes_am654_disable_pll(phy);

	वापस 0;
पूर्ण

#घोषणा SERDES_AM654_CFG(offset, a, b, val) \
	regmap_update_bits(phy->regmap, (offset),\
			   GENMASK((a), (b)), (val) << (b))

अटल पूर्णांक serdes_am654_usb3_init(काष्ठा serdes_am654 *phy)
अणु
	SERDES_AM654_CFG(0x0000, 31, 24, 0x17);
	SERDES_AM654_CFG(0x0004, 15, 8, 0x02);
	SERDES_AM654_CFG(0x0004, 7, 0, 0x0e);
	SERDES_AM654_CFG(0x0008, 23, 16, 0x2e);
	SERDES_AM654_CFG(0x0008, 31, 24, 0x2e);
	SERDES_AM654_CFG(0x0060, 7, 0, 0x4b);
	SERDES_AM654_CFG(0x0060, 15, 8, 0x98);
	SERDES_AM654_CFG(0x0060, 23, 16, 0x60);
	SERDES_AM654_CFG(0x00d0, 31, 24, 0x45);
	SERDES_AM654_CFG(0x00e8, 15, 8, 0x0e);
	SERDES_AM654_CFG(0x0220, 7, 0, 0x34);
	SERDES_AM654_CFG(0x0220, 15, 8, 0x34);
	SERDES_AM654_CFG(0x0220, 31, 24, 0x37);
	SERDES_AM654_CFG(0x0224, 7, 0, 0x37);
	SERDES_AM654_CFG(0x0224, 15, 8, 0x37);
	SERDES_AM654_CFG(0x0228, 23, 16, 0x37);
	SERDES_AM654_CFG(0x0228, 31, 24, 0x37);
	SERDES_AM654_CFG(0x022c, 7, 0, 0x37);
	SERDES_AM654_CFG(0x022c, 15, 8, 0x37);
	SERDES_AM654_CFG(0x0230, 15, 8, 0x2a);
	SERDES_AM654_CFG(0x0230, 23, 16, 0x2a);
	SERDES_AM654_CFG(0x0240, 23, 16, 0x10);
	SERDES_AM654_CFG(0x0240, 31, 24, 0x34);
	SERDES_AM654_CFG(0x0244, 7, 0, 0x40);
	SERDES_AM654_CFG(0x0244, 23, 16, 0x34);
	SERDES_AM654_CFG(0x0248, 15, 8, 0x0d);
	SERDES_AM654_CFG(0x0258, 15, 8, 0x16);
	SERDES_AM654_CFG(0x0258, 23, 16, 0x84);
	SERDES_AM654_CFG(0x0258, 31, 24, 0xf2);
	SERDES_AM654_CFG(0x025c, 7, 0, 0x21);
	SERDES_AM654_CFG(0x0260, 7, 0, 0x27);
	SERDES_AM654_CFG(0x0260, 15, 8, 0x04);
	SERDES_AM654_CFG(0x0268, 15, 8, 0x04);
	SERDES_AM654_CFG(0x0288, 15, 8, 0x2c);
	SERDES_AM654_CFG(0x0330, 31, 24, 0xa0);
	SERDES_AM654_CFG(0x0338, 23, 16, 0x03);
	SERDES_AM654_CFG(0x0338, 31, 24, 0x00);
	SERDES_AM654_CFG(0x033c, 7, 0, 0x00);
	SERDES_AM654_CFG(0x0344, 31, 24, 0x18);
	SERDES_AM654_CFG(0x034c, 7, 0, 0x18);
	SERDES_AM654_CFG(0x039c, 23, 16, 0x3b);
	SERDES_AM654_CFG(0x0a04, 7, 0, 0x03);
	SERDES_AM654_CFG(0x0a14, 31, 24, 0x3c);
	SERDES_AM654_CFG(0x0a18, 15, 8, 0x3c);
	SERDES_AM654_CFG(0x0a38, 7, 0, 0x3e);
	SERDES_AM654_CFG(0x0a38, 15, 8, 0x3e);
	SERDES_AM654_CFG(0x0ae0, 7, 0, 0x07);
	SERDES_AM654_CFG(0x0b6c, 23, 16, 0xcd);
	SERDES_AM654_CFG(0x0b6c, 31, 24, 0x04);
	SERDES_AM654_CFG(0x0b98, 23, 16, 0x03);
	SERDES_AM654_CFG(0x1400, 7, 0, 0x3f);
	SERDES_AM654_CFG(0x1404, 23, 16, 0x6f);
	SERDES_AM654_CFG(0x1404, 31, 24, 0x6f);
	SERDES_AM654_CFG(0x140c, 7, 0, 0x6f);
	SERDES_AM654_CFG(0x140c, 15, 8, 0x6f);
	SERDES_AM654_CFG(0x1410, 15, 8, 0x27);
	SERDES_AM654_CFG(0x1414, 7, 0, 0x0c);
	SERDES_AM654_CFG(0x1414, 23, 16, 0x07);
	SERDES_AM654_CFG(0x1418, 23, 16, 0x40);
	SERDES_AM654_CFG(0x141c, 7, 0, 0x00);
	SERDES_AM654_CFG(0x141c, 15, 8, 0x1f);
	SERDES_AM654_CFG(0x1428, 31, 24, 0x08);
	SERDES_AM654_CFG(0x1434, 31, 24, 0x00);
	SERDES_AM654_CFG(0x1444, 7, 0, 0x94);
	SERDES_AM654_CFG(0x1460, 31, 24, 0x7f);
	SERDES_AM654_CFG(0x1464, 7, 0, 0x43);
	SERDES_AM654_CFG(0x1464, 23, 16, 0x6f);
	SERDES_AM654_CFG(0x1464, 31, 24, 0x43);
	SERDES_AM654_CFG(0x1484, 23, 16, 0x8f);
	SERDES_AM654_CFG(0x1498, 7, 0, 0x4f);
	SERDES_AM654_CFG(0x1498, 23, 16, 0x4f);
	SERDES_AM654_CFG(0x007c, 31, 24, 0x0d);
	SERDES_AM654_CFG(0x0b90, 15, 8, 0x0f);

	वापस 0;
पूर्ण

अटल पूर्णांक serdes_am654_pcie_init(काष्ठा serdes_am654 *phy)
अणु
	पूर्णांक ret = 0;

	ret |= regmap_field_ग_लिखो(phy->fields[CMU_PLL_CTRL], 0x2);
	ret |= regmap_field_ग_लिखो(phy->fields[AHB_PMA_CM_VCO_VBIAS_VREG], 0x98);
	ret |= regmap_field_ग_लिखो(phy->fields[AHB_PMA_CM_VCO_BIAS_VREG], 0x98);
	ret |= regmap_field_ग_लिखो(phy->fields[AHB_PMA_CM_SR], 0x45);
	ret |= regmap_field_ग_लिखो(phy->fields[AHB_SSC_GEN_Z_O_20_13], 0xe);
	ret |= regmap_field_ग_लिखो(phy->fields[LANE_PLL_CTRL_RXEQ_RXIDLE], 0x5);
	ret |= regmap_field_ग_लिखो(phy->fields[AHB_PMA_LN_AGC_THSEL_VREGH], 0x83);
	ret |= regmap_field_ग_लिखो(phy->fields[AHB_PMA_LN_GEN3_AGC_SD_THSEL], 0x83);
	ret |= regmap_field_ग_लिखो(phy->fields[AHB_PMA_LN_RX_SELR_GEN3],	0x81);
	ret |= regmap_field_ग_लिखो(phy->fields[AHB_PMA_LN_TX_DRV], 0x3b);
	ret |= regmap_field_ग_लिखो(phy->fields[P2S_RBUF_PTR_DIFF], 0x3);
	ret |= regmap_field_ग_लिखो(phy->fields[CONFIG_VERSION], VERSION_VAL);
	ret |= regmap_field_ग_लिखो(phy->fields[COMRXEQ_MS_INIT_CTRL_7_0], 0xf);
	ret |= regmap_field_ग_लिखो(phy->fields[COMRXEQ_HS_INIT_CAL_7_0], 0x4f);
	ret |= regmap_field_ग_लिखो(phy->fields[COMRXEQ_MS_RECAL_CTRL_7_0], 0xf);
	ret |= regmap_field_ग_लिखो(phy->fields[COMRXEQ_HS_RECAL_CTRL_7_0], 0x4f);
	ret |= regmap_field_ग_लिखो(phy->fields[COMRXEQ_CSR_ATT_CONFIG], 0x7);
	ret |= regmap_field_ग_लिखो(phy->fields[COMRXEQ_CSR_EBSTADAPT_WIN_LEN], 0x7f);
	ret |= regmap_field_ग_लिखो(phy->fields[COMRXEQ_CTRL_3_4], 0xf);
	ret |= regmap_field_ग_लिखो(phy->fields[COMRXEQ_CTRL_14_15_16], 0x9a);
	ret |= regmap_field_ग_लिखो(phy->fields[COMRXEQ_CSR_DLEV_ERR_THRESH], 0x32);
	ret |= regmap_field_ग_लिखो(phy->fields[COMRXEQ_CTRL_25], 0x80);
	ret |= regmap_field_ग_लिखो(phy->fields[CSR_RXEQ_RATE_CHANGE_CAL_RUN_RATE2_O], 0xf);
	ret |= regmap_field_ग_लिखो(phy->fields[COMRXEQ_HS_RCHANGE_CTRL_7_0], 0x4f);
	ret |= regmap_field_ग_लिखो(phy->fields[CMU_MASTER_CDN], 0x1);
	ret |= regmap_field_ग_लिखो(phy->fields[L1_MASTER_CDN], 0x2);

	अगर (ret)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक serdes_am654_init(काष्ठा phy *x)
अणु
	काष्ठा serdes_am654 *phy = phy_get_drvdata(x);

	चयन (phy->type) अणु
	हाल PHY_TYPE_PCIE:
		वापस serdes_am654_pcie_init(phy);
	हाल PHY_TYPE_USB3:
		वापस serdes_am654_usb3_init(phy);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक serdes_am654_reset(काष्ठा phy *x)
अणु
	काष्ठा serdes_am654 *phy = phy_get_drvdata(x);
	पूर्णांक ret = 0;

	serdes_am654_disable_pll(phy);
	serdes_am654_disable_txrx(phy);

	ret |= regmap_field_ग_लिखो(phy->fields[POR_EN], 0x1);

	mdelay(1);

	ret |= regmap_field_ग_लिखो(phy->fields[POR_EN], 0x0);

	अगर (ret)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम serdes_am654_release(काष्ठा phy *x)
अणु
	काष्ठा serdes_am654 *phy = phy_get_drvdata(x);

	phy->type = PHY_NONE;
	phy->busy = false;
	mux_control_deselect(phy->control);
पूर्ण

अटल काष्ठा phy *serdes_am654_xlate(काष्ठा device *dev,
				      काष्ठा of_phandle_args *args)
अणु
	काष्ठा serdes_am654 *am654_phy;
	काष्ठा phy *phy;
	पूर्णांक ret;

	phy = of_phy_simple_xlate(dev, args);
	अगर (IS_ERR(phy))
		वापस phy;

	am654_phy = phy_get_drvdata(phy);
	अगर (am654_phy->busy)
		वापस ERR_PTR(-EBUSY);

	ret = mux_control_select(am654_phy->control, args->args[1]);
	अगर (ret) अणु
		dev_err(dev, "Failed to select SERDES Lane Function\n");
		वापस ERR_PTR(ret);
	पूर्ण

	am654_phy->busy = true;
	am654_phy->type = args->args[0];

	वापस phy;
पूर्ण

अटल स्थिर काष्ठा phy_ops ops = अणु
	.reset		= serdes_am654_reset,
	.init		= serdes_am654_init,
	.घातer_on	= serdes_am654_घातer_on,
	.घातer_off	= serdes_am654_घातer_off,
	.release	= serdes_am654_release,
	.owner		= THIS_MODULE,
पूर्ण;

#घोषणा SERDES_NUM_MUX_COMBINATIONS 16

#घोषणा LICLK 0
#घोषणा EXT_REFCLK 1
#घोषणा RICLK 2

अटल स्थिर पूर्णांक
serdes_am654_mux_table[SERDES_NUM_MUX_COMBINATIONS][SERDES_NUM_CLOCKS] = अणु
	/*
	 * Each combination maps to one of
	 * "Figure 12-1986. SerDes Reference Clock Distribution"
	 * in TRM.
	 */
	 /* Parent of CMU refclk, Left output, Right output
	  * either of EXT_REFCLK, LICLK, RICLK
	  */
	अणु EXT_REFCLK, EXT_REFCLK, EXT_REFCLK पूर्ण,	/* 0000 */
	अणु RICLK, EXT_REFCLK, EXT_REFCLK पूर्ण,	/* 0001 */
	अणु EXT_REFCLK, RICLK, LICLK पूर्ण,		/* 0010 */
	अणु RICLK, RICLK, EXT_REFCLK पूर्ण,		/* 0011 */
	अणु LICLK, EXT_REFCLK, EXT_REFCLK पूर्ण,	/* 0100 */
	अणु EXT_REFCLK, EXT_REFCLK, EXT_REFCLK पूर्ण,	/* 0101 */
	अणु LICLK, RICLK, LICLK पूर्ण,		/* 0110 */
	अणु EXT_REFCLK, RICLK, LICLK पूर्ण,		/* 0111 */
	अणु EXT_REFCLK, EXT_REFCLK, LICLK पूर्ण,	/* 1000 */
	अणु RICLK, EXT_REFCLK, LICLK पूर्ण,		/* 1001 */
	अणु EXT_REFCLK, RICLK, EXT_REFCLK पूर्ण,	/* 1010 */
	अणु RICLK, RICLK, EXT_REFCLK पूर्ण,		/* 1011 */
	अणु LICLK, EXT_REFCLK, LICLK पूर्ण,		/* 1100 */
	अणु EXT_REFCLK, EXT_REFCLK, LICLK पूर्ण,	/* 1101 */
	अणु LICLK, RICLK, EXT_REFCLK पूर्ण,		/* 1110 */
	अणु EXT_REFCLK, RICLK, EXT_REFCLK पूर्ण,	/* 1111 */
पूर्ण;

अटल u8 serdes_am654_clk_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा serdes_am654_clk_mux *mux = to_serdes_am654_clk_mux(hw);
	काष्ठा regmap *regmap = mux->regmap;
	अचिन्हित पूर्णांक reg = mux->reg;
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(regmap, reg, &val);
	val &= AM654_SERDES_CTRL_CLKSEL_MASK;
	val >>= AM654_SERDES_CTRL_CLKSEL_SHIFT;

	वापस serdes_am654_mux_table[val][mux->clk_id];
पूर्ण

अटल पूर्णांक serdes_am654_clk_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा serdes_am654_clk_mux *mux = to_serdes_am654_clk_mux(hw);
	काष्ठा regmap *regmap = mux->regmap;
	स्थिर अक्षर *name = clk_hw_get_name(hw);
	अचिन्हित पूर्णांक reg = mux->reg;
	पूर्णांक clk_id = mux->clk_id;
	पूर्णांक parents[SERDES_NUM_CLOCKS];
	स्थिर पूर्णांक *p;
	u32 val;
	पूर्णांक found, i;
	पूर्णांक ret;

	/* get existing setting */
	regmap_पढ़ो(regmap, reg, &val);
	val &= AM654_SERDES_CTRL_CLKSEL_MASK;
	val >>= AM654_SERDES_CTRL_CLKSEL_SHIFT;

	क्रम (i = 0; i < SERDES_NUM_CLOCKS; i++)
		parents[i] = serdes_am654_mux_table[val][i];

	/* change parent of this घड़ी. others left पूर्णांकact */
	parents[clk_id] = index;

	/* Find the match */
	क्रम (val = 0; val < SERDES_NUM_MUX_COMBINATIONS; val++) अणु
		p = serdes_am654_mux_table[val];
		found = 1;
		क्रम (i = 0; i < SERDES_NUM_CLOCKS; i++) अणु
			अगर (parents[i] != p[i]) अणु
				found = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (found)
			अवरोध;
	पूर्ण

	अगर (!found) अणु
		/*
		 * This can never happen, unless we missed
		 * a valid combination in serdes_am654_mux_table.
		 */
		WARN(1, "Failed to find the parent of %s clock\n", name);
		वापस -EINVAL;
	पूर्ण

	val <<= AM654_SERDES_CTRL_CLKSEL_SHIFT;
	ret = regmap_update_bits(regmap, reg, AM654_SERDES_CTRL_CLKSEL_MASK,
				 val);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops serdes_am654_clk_mux_ops = अणु
	.set_parent = serdes_am654_clk_mux_set_parent,
	.get_parent = serdes_am654_clk_mux_get_parent,
पूर्ण;

अटल पूर्णांक serdes_am654_clk_रेजिस्टर(काष्ठा serdes_am654 *am654_phy,
				     स्थिर अक्षर *घड़ी_name, पूर्णांक घड़ी_num)
अणु
	काष्ठा device_node *node = am654_phy->of_node;
	काष्ठा device *dev = am654_phy->dev;
	काष्ठा serdes_am654_clk_mux *mux;
	काष्ठा device_node *regmap_node;
	स्थिर अक्षर **parent_names;
	काष्ठा clk_init_data *init;
	अचिन्हित पूर्णांक num_parents;
	काष्ठा regmap *regmap;
	स्थिर __be32 *addr;
	अचिन्हित पूर्णांक reg;
	काष्ठा clk *clk;
	पूर्णांक ret = 0;

	mux = devm_kzalloc(dev, माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस -ENOMEM;

	init = &mux->clk_data;

	regmap_node = of_parse_phandle(node, "ti,serdes-clk", 0);
	अगर (!regmap_node) अणु
		dev_err(dev, "Fail to get serdes-clk node\n");
		ret = -ENODEV;
		जाओ out_put_node;
	पूर्ण

	regmap = syscon_node_to_regmap(regmap_node->parent);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "Fail to get Syscon regmap\n");
		ret = PTR_ERR(regmap);
		जाओ out_put_node;
	पूर्ण

	num_parents = of_clk_get_parent_count(node);
	अगर (num_parents < 2) अणु
		dev_err(dev, "SERDES clock must have parents\n");
		ret = -EINVAL;
		जाओ out_put_node;
	पूर्ण

	parent_names = devm_kzalloc(dev, (माप(अक्षर *) * num_parents),
				    GFP_KERNEL);
	अगर (!parent_names) अणु
		ret = -ENOMEM;
		जाओ out_put_node;
	पूर्ण

	of_clk_parent_fill(node, parent_names, num_parents);

	addr = of_get_address(regmap_node, 0, शून्य, शून्य);
	अगर (!addr) अणु
		ret = -EINVAL;
		जाओ out_put_node;
	पूर्ण

	reg = be32_to_cpu(*addr);

	init->ops = &serdes_am654_clk_mux_ops;
	init->flags = CLK_SET_RATE_NO_REPARENT;
	init->parent_names = parent_names;
	init->num_parents = num_parents;
	init->name = घड़ी_name;

	mux->regmap = regmap;
	mux->reg = reg;
	mux->clk_id = घड़ी_num;
	mux->hw.init = init;

	clk = devm_clk_रेजिस्टर(dev, &mux->hw);
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		जाओ out_put_node;
	पूर्ण

	am654_phy->clks[घड़ी_num] = clk;

out_put_node:
	of_node_put(regmap_node);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id serdes_am654_id_table[] = अणु
	अणु
		.compatible = "ti,phy-am654-serdes",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, serdes_am654_id_table);

अटल पूर्णांक serdes_am654_regfield_init(काष्ठा serdes_am654 *am654_phy)
अणु
	काष्ठा regmap *regmap = am654_phy->regmap;
	काष्ठा device *dev = am654_phy->dev;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_FIELDS; i++) अणु
		am654_phy->fields[i] = devm_regmap_field_alloc(dev,
							       regmap,
							       serdes_am654_reg_fields[i]);
		अगर (IS_ERR(am654_phy->fields[i])) अणु
			dev_err(dev, "Unable to allocate regmap field %d\n", i);
			वापस PTR_ERR(am654_phy->fields[i]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक serdes_am654_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा serdes_am654 *am654_phy;
	काष्ठा mux_control *control;
	स्थिर अक्षर *घड़ी_name;
	काष्ठा regmap *regmap;
	व्योम __iomem *base;
	काष्ठा phy *phy;
	पूर्णांक ret;
	पूर्णांक i;

	am654_phy = devm_kzalloc(dev, माप(*am654_phy), GFP_KERNEL);
	अगर (!am654_phy)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio(dev, base, &serdes_am654_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "Failed to initialize regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	control = devm_mux_control_get(dev, शून्य);
	अगर (IS_ERR(control))
		वापस PTR_ERR(control);

	am654_phy->dev = dev;
	am654_phy->of_node = node;
	am654_phy->regmap = regmap;
	am654_phy->control = control;
	am654_phy->type = PHY_NONE;

	ret = serdes_am654_regfield_init(am654_phy);
	अगर (ret) अणु
		dev_err(dev, "Failed to initialize regfields\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, am654_phy);

	क्रम (i = 0; i < SERDES_NUM_CLOCKS; i++) अणु
		ret = of_property_पढ़ो_string_index(node, "clock-output-names",
						    i, &घड़ी_name);
		अगर (ret) अणु
			dev_err(dev, "Failed to get clock name\n");
			वापस ret;
		पूर्ण

		ret = serdes_am654_clk_रेजिस्टर(am654_phy, घड़ी_name, i);
		अगर (ret) अणु
			dev_err(dev, "Failed to initialize clock %s\n",
				घड़ी_name);
			वापस ret;
		पूर्ण
	पूर्ण

	clk_data = &am654_phy->clk_data;
	clk_data->clks = am654_phy->clks;
	clk_data->clk_num = SERDES_NUM_CLOCKS;
	ret = of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
	अगर (ret)
		वापस ret;

	pm_runसमय_enable(dev);

	phy = devm_phy_create(dev, शून्य, &ops);
	अगर (IS_ERR(phy)) अणु
		ret = PTR_ERR(phy);
		जाओ clk_err;
	पूर्ण

	phy_set_drvdata(phy, am654_phy);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, serdes_am654_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		ret = PTR_ERR(phy_provider);
		जाओ clk_err;
	पूर्ण

	वापस 0;

clk_err:
	of_clk_del_provider(node);

	वापस ret;
पूर्ण

अटल पूर्णांक serdes_am654_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा serdes_am654 *am654_phy = platक्रमm_get_drvdata(pdev);
	काष्ठा device_node *node = am654_phy->of_node;

	pm_runसमय_disable(&pdev->dev);
	of_clk_del_provider(node);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver serdes_am654_driver = अणु
	.probe		= serdes_am654_probe,
	.हटाओ		= serdes_am654_हटाओ,
	.driver		= अणु
		.name	= "phy-am654",
		.of_match_table = serdes_am654_id_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(serdes_am654_driver);

MODULE_AUTHOR("Texas Instruments Inc.");
MODULE_DESCRIPTION("TI AM654x SERDES driver");
MODULE_LICENSE("GPL v2");
