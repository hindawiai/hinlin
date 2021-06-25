<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Salvo PHY is a 28nm PHY, it is a legacy PHY, and only
 * क्रम USB3 and USB2.
 *
 * Copyright (c) 2019-2020 NXP
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>

/* PHY रेजिस्टर definition */
#घोषणा PHY_PMA_CMN_CTRL1			0xC800
#घोषणा TB_ADDR_CMN_DIAG_HSCLK_SEL		0x01e0
#घोषणा TB_ADDR_CMN_PLL0_VCOCAL_INIT_TMR	0x0084
#घोषणा TB_ADDR_CMN_PLL0_VCOCAL_ITER_TMR	0x0085
#घोषणा TB_ADDR_CMN_PLL0_INTDIV	                0x0094
#घोषणा TB_ADDR_CMN_PLL0_FRACDIV		0x0095
#घोषणा TB_ADDR_CMN_PLL0_HIGH_THR		0x0096
#घोषणा TB_ADDR_CMN_PLL0_SS_CTRL1		0x0098
#घोषणा TB_ADDR_CMN_PLL0_SS_CTRL2		0x0099
#घोषणा TB_ADDR_CMN_PLL0_DSM_DIAG		0x0097
#घोषणा TB_ADDR_CMN_DIAG_PLL0_OVRD		0x01c2
#घोषणा TB_ADDR_CMN_DIAG_PLL0_FBH_OVRD		0x01c0
#घोषणा TB_ADDR_CMN_DIAG_PLL0_FBL_OVRD		0x01c1
#घोषणा TB_ADDR_CMN_DIAG_PLL0_V2I_TUNE          0x01C5
#घोषणा TB_ADDR_CMN_DIAG_PLL0_CP_TUNE           0x01C6
#घोषणा TB_ADDR_CMN_DIAG_PLL0_LF_PROG           0x01C7
#घोषणा TB_ADDR_CMN_DIAG_PLL0_TEST_MODE		0x01c4
#घोषणा TB_ADDR_CMN_PSM_CLK_CTRL		0x0061
#घोषणा TB_ADDR_XCVR_DIAG_RX_LANE_CAL_RST_TMR	0x40ea
#घोषणा TB_ADDR_XCVR_PSM_RCTRL	                0x4001
#घोषणा TB_ADDR_TX_PSC_A0		        0x4100
#घोषणा TB_ADDR_TX_PSC_A1		        0x4101
#घोषणा TB_ADDR_TX_PSC_A2		        0x4102
#घोषणा TB_ADDR_TX_PSC_A3		        0x4103
#घोषणा TB_ADDR_TX_DIAG_ECTRL_OVRD		0x41f5
#घोषणा TB_ADDR_TX_PSC_CAL		        0x4106
#घोषणा TB_ADDR_TX_PSC_RDY		        0x4107
#घोषणा TB_ADDR_RX_PSC_A0	                0x8000
#घोषणा TB_ADDR_RX_PSC_A1	                0x8001
#घोषणा TB_ADDR_RX_PSC_A2	                0x8002
#घोषणा TB_ADDR_RX_PSC_A3	                0x8003
#घोषणा TB_ADDR_RX_PSC_CAL	                0x8006
#घोषणा TB_ADDR_RX_PSC_RDY	                0x8007
#घोषणा TB_ADDR_TX_TXCC_MGNLS_MULT_000		0x4058
#घोषणा TB_ADDR_TX_DIAG_BGREF_PREDRV_DELAY	0x41e7
#घोषणा TB_ADDR_RX_SLC_CU_ITER_TMR		0x80e3
#घोषणा TB_ADDR_RX_SIGDET_HL_FILT_TMR		0x8090
#घोषणा TB_ADDR_RX_SAMP_DAC_CTRL		0x8058
#घोषणा TB_ADDR_RX_DIAG_SIGDET_TUNE		0x81dc
#घोषणा TB_ADDR_RX_DIAG_LFPSDET_TUNE2		0x81df
#घोषणा TB_ADDR_RX_DIAG_BS_TM	                0x81f5
#घोषणा TB_ADDR_RX_DIAG_DFE_CTRL1		0x81d3
#घोषणा TB_ADDR_RX_DIAG_ILL_IQE_TRIM4		0x81c7
#घोषणा TB_ADDR_RX_DIAG_ILL_E_TRIM0		0x81c2
#घोषणा TB_ADDR_RX_DIAG_ILL_IQ_TRIM0		0x81c1
#घोषणा TB_ADDR_RX_DIAG_ILL_IQE_TRIM6		0x81c9
#घोषणा TB_ADDR_RX_DIAG_RXFE_TM3		0x81f8
#घोषणा TB_ADDR_RX_DIAG_RXFE_TM4		0x81f9
#घोषणा TB_ADDR_RX_DIAG_LFPSDET_TUNE		0x81dd
#घोषणा TB_ADDR_RX_DIAG_DFE_CTRL3		0x81d5
#घोषणा TB_ADDR_RX_DIAG_SC2C_DELAY		0x81e1
#घोषणा TB_ADDR_RX_REE_VGA_GAIN_NODFE		0x81bf
#घोषणा TB_ADDR_XCVR_PSM_CAL_TMR		0x4002
#घोषणा TB_ADDR_XCVR_PSM_A0BYP_TMR		0x4004
#घोषणा TB_ADDR_XCVR_PSM_A0IN_TMR		0x4003
#घोषणा TB_ADDR_XCVR_PSM_A1IN_TMR		0x4005
#घोषणा TB_ADDR_XCVR_PSM_A2IN_TMR		0x4006
#घोषणा TB_ADDR_XCVR_PSM_A3IN_TMR		0x4007
#घोषणा TB_ADDR_XCVR_PSM_A4IN_TMR		0x4008
#घोषणा TB_ADDR_XCVR_PSM_A5IN_TMR		0x4009
#घोषणा TB_ADDR_XCVR_PSM_A0OUT_TMR		0x400a
#घोषणा TB_ADDR_XCVR_PSM_A1OUT_TMR		0x400b
#घोषणा TB_ADDR_XCVR_PSM_A2OUT_TMR		0x400c
#घोषणा TB_ADDR_XCVR_PSM_A3OUT_TMR		0x400d
#घोषणा TB_ADDR_XCVR_PSM_A4OUT_TMR		0x400e
#घोषणा TB_ADDR_XCVR_PSM_A5OUT_TMR		0x400f
#घोषणा TB_ADDR_TX_RCVDET_EN_TMR	        0x4122
#घोषणा TB_ADDR_TX_RCVDET_ST_TMR	        0x4123
#घोषणा TB_ADDR_XCVR_DIAG_LANE_FCM_EN_MGN_TMR	0x40f2
#घोषणा TB_ADDR_TX_RCVDETSC_CTRL	        0x4124

/* TB_ADDR_TX_RCVDETSC_CTRL */
#घोषणा RXDET_IN_P3_32KHZ			BIT(0)

काष्ठा cdns_reg_pairs अणु
	u16 val;
	u32 off;
पूर्ण;

काष्ठा cdns_salvo_data अणु
	u8 reg_offset_shअगरt;
	स्थिर काष्ठा cdns_reg_pairs *init_sequence_val;
	u8 init_sequence_length;
पूर्ण;

काष्ठा cdns_salvo_phy अणु
	काष्ठा phy *phy;
	काष्ठा clk *clk;
	व्योम __iomem *base;
	काष्ठा cdns_salvo_data *data;
पूर्ण;

अटल स्थिर काष्ठा of_device_id cdns_salvo_phy_of_match[];
अटल u16 cdns_salvo_पढ़ो(काष्ठा cdns_salvo_phy *salvo_phy, u32 reg)
अणु
	वापस (u16)पढ़ोl(salvo_phy->base +
		reg * (1 << salvo_phy->data->reg_offset_shअगरt));
पूर्ण

अटल व्योम cdns_salvo_ग_लिखो(काष्ठा cdns_salvo_phy *salvo_phy,
			     u32 reg, u16 val)
अणु
	ग_लिखोl(val, salvo_phy->base +
		reg * (1 << salvo_phy->data->reg_offset_shअगरt));
पूर्ण

/*
 * Below bringup sequence pair are from Cadence PHY's User Guide
 * and NXP platक्रमm tuning results.
 */
अटल स्थिर काष्ठा cdns_reg_pairs cdns_nxp_sequence_pair[] = अणु
	अणु0x0830, PHY_PMA_CMN_CTRL1पूर्ण,
	अणु0x0010, TB_ADDR_CMN_DIAG_HSCLK_SELपूर्ण,
	अणु0x00f0, TB_ADDR_CMN_PLL0_VCOCAL_INIT_TMRपूर्ण,
	अणु0x0018, TB_ADDR_CMN_PLL0_VCOCAL_ITER_TMRपूर्ण,
	अणु0x00d0, TB_ADDR_CMN_PLL0_INTDIVपूर्ण,
	अणु0x4aaa, TB_ADDR_CMN_PLL0_FRACDIVपूर्ण,
	अणु0x0034, TB_ADDR_CMN_PLL0_HIGH_THRपूर्ण,
	अणु0x01ee, TB_ADDR_CMN_PLL0_SS_CTRL1पूर्ण,
	अणु0x7f03, TB_ADDR_CMN_PLL0_SS_CTRL2पूर्ण,
	अणु0x0020, TB_ADDR_CMN_PLL0_DSM_DIAGपूर्ण,
	अणु0x0000, TB_ADDR_CMN_DIAG_PLL0_OVRDपूर्ण,
	अणु0x0000, TB_ADDR_CMN_DIAG_PLL0_FBH_OVRDपूर्ण,
	अणु0x0000, TB_ADDR_CMN_DIAG_PLL0_FBL_OVRDपूर्ण,
	अणु0x0007, TB_ADDR_CMN_DIAG_PLL0_V2I_TUNEपूर्ण,
	अणु0x0027, TB_ADDR_CMN_DIAG_PLL0_CP_TUNEपूर्ण,
	अणु0x0008, TB_ADDR_CMN_DIAG_PLL0_LF_PROGपूर्ण,
	अणु0x0022, TB_ADDR_CMN_DIAG_PLL0_TEST_MODEपूर्ण,
	अणु0x000a, TB_ADDR_CMN_PSM_CLK_CTRLपूर्ण,
	अणु0x0139, TB_ADDR_XCVR_DIAG_RX_LANE_CAL_RST_TMRपूर्ण,
	अणु0xbefc, TB_ADDR_XCVR_PSM_RCTRLपूर्ण,

	अणु0x7799, TB_ADDR_TX_PSC_A0पूर्ण,
	अणु0x7798, TB_ADDR_TX_PSC_A1पूर्ण,
	अणु0x509b, TB_ADDR_TX_PSC_A2पूर्ण,
	अणु0x0003, TB_ADDR_TX_DIAG_ECTRL_OVRDपूर्ण,
	अणु0x509b, TB_ADDR_TX_PSC_A3पूर्ण,
	अणु0x2090, TB_ADDR_TX_PSC_CALपूर्ण,
	अणु0x2090, TB_ADDR_TX_PSC_RDYपूर्ण,

	अणु0xA6FD, TB_ADDR_RX_PSC_A0पूर्ण,
	अणु0xA6FD, TB_ADDR_RX_PSC_A1पूर्ण,
	अणु0xA410, TB_ADDR_RX_PSC_A2पूर्ण,
	अणु0x2410, TB_ADDR_RX_PSC_A3पूर्ण,

	अणु0x23FF, TB_ADDR_RX_PSC_CALपूर्ण,
	अणु0x2010, TB_ADDR_RX_PSC_RDYपूर्ण,

	अणु0x0020, TB_ADDR_TX_TXCC_MGNLS_MULT_000पूर्ण,
	अणु0x00ff, TB_ADDR_TX_DIAG_BGREF_PREDRV_DELAYपूर्ण,
	अणु0x0002, TB_ADDR_RX_SLC_CU_ITER_TMRपूर्ण,
	अणु0x0013, TB_ADDR_RX_SIGDET_HL_FILT_TMRपूर्ण,
	अणु0x0000, TB_ADDR_RX_SAMP_DAC_CTRLपूर्ण,
	अणु0x1004, TB_ADDR_RX_DIAG_SIGDET_TUNEपूर्ण,
	अणु0x4041, TB_ADDR_RX_DIAG_LFPSDET_TUNE2पूर्ण,
	अणु0x0480, TB_ADDR_RX_DIAG_BS_TMपूर्ण,
	अणु0x8006, TB_ADDR_RX_DIAG_DFE_CTRL1पूर्ण,
	अणु0x003f, TB_ADDR_RX_DIAG_ILL_IQE_TRIM4पूर्ण,
	अणु0x543f, TB_ADDR_RX_DIAG_ILL_E_TRIM0पूर्ण,
	अणु0x543f, TB_ADDR_RX_DIAG_ILL_IQ_TRIM0पूर्ण,
	अणु0x0000, TB_ADDR_RX_DIAG_ILL_IQE_TRIM6पूर्ण,
	अणु0x8000, TB_ADDR_RX_DIAG_RXFE_TM3पूर्ण,
	अणु0x0003, TB_ADDR_RX_DIAG_RXFE_TM4पूर्ण,
	अणु0x2408, TB_ADDR_RX_DIAG_LFPSDET_TUNEपूर्ण,
	अणु0x05ca, TB_ADDR_RX_DIAG_DFE_CTRL3पूर्ण,
	अणु0x0258, TB_ADDR_RX_DIAG_SC2C_DELAYपूर्ण,
	अणु0x1fff, TB_ADDR_RX_REE_VGA_GAIN_NODFEपूर्ण,

	अणु0x02c6, TB_ADDR_XCVR_PSM_CAL_TMRपूर्ण,
	अणु0x0002, TB_ADDR_XCVR_PSM_A0BYP_TMRपूर्ण,
	अणु0x02c6, TB_ADDR_XCVR_PSM_A0IN_TMRपूर्ण,
	अणु0x0010, TB_ADDR_XCVR_PSM_A1IN_TMRपूर्ण,
	अणु0x0010, TB_ADDR_XCVR_PSM_A2IN_TMRपूर्ण,
	अणु0x0010, TB_ADDR_XCVR_PSM_A3IN_TMRपूर्ण,
	अणु0x0010, TB_ADDR_XCVR_PSM_A4IN_TMRपूर्ण,
	अणु0x0010, TB_ADDR_XCVR_PSM_A5IN_TMRपूर्ण,

	अणु0x0002, TB_ADDR_XCVR_PSM_A0OUT_TMRपूर्ण,
	अणु0x0002, TB_ADDR_XCVR_PSM_A1OUT_TMRपूर्ण,
	अणु0x0002, TB_ADDR_XCVR_PSM_A2OUT_TMRपूर्ण,
	अणु0x0002, TB_ADDR_XCVR_PSM_A3OUT_TMRपूर्ण,
	अणु0x0002, TB_ADDR_XCVR_PSM_A4OUT_TMRपूर्ण,
	अणु0x0002, TB_ADDR_XCVR_PSM_A5OUT_TMRपूर्ण,
	/* Change rx detect parameter */
	अणु0x0960, TB_ADDR_TX_RCVDET_EN_TMRपूर्ण,
	अणु0x01e0, TB_ADDR_TX_RCVDET_ST_TMRपूर्ण,
	अणु0x0090, TB_ADDR_XCVR_DIAG_LANE_FCM_EN_MGN_TMRपूर्ण,
पूर्ण;

अटल पूर्णांक cdns_salvo_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा cdns_salvo_phy *salvo_phy = phy_get_drvdata(phy);
	काष्ठा cdns_salvo_data *data = salvo_phy->data;
	पूर्णांक ret, i;
	u16 value;

	ret = clk_prepare_enable(salvo_phy->clk);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < data->init_sequence_length; i++) अणु
		स्थिर काष्ठा cdns_reg_pairs *reg_pair = data->init_sequence_val + i;

		cdns_salvo_ग_लिखो(salvo_phy, reg_pair->off, reg_pair->val);
	पूर्ण

	/* RXDET_IN_P3_32KHZ, Receiver detect slow घड़ी enable */
	value = cdns_salvo_पढ़ो(salvo_phy, TB_ADDR_TX_RCVDETSC_CTRL);
	value |= RXDET_IN_P3_32KHZ;
	cdns_salvo_ग_लिखो(salvo_phy, TB_ADDR_TX_RCVDETSC_CTRL,
			 RXDET_IN_P3_32KHZ);

	udelay(10);

	clk_disable_unprepare(salvo_phy->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक cdns_salvo_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा cdns_salvo_phy *salvo_phy = phy_get_drvdata(phy);

	वापस clk_prepare_enable(salvo_phy->clk);
पूर्ण

अटल पूर्णांक cdns_salvo_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा cdns_salvo_phy *salvo_phy = phy_get_drvdata(phy);

	clk_disable_unprepare(salvo_phy->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops cdns_salvo_phy_ops = अणु
	.init		= cdns_salvo_phy_init,
	.घातer_on	= cdns_salvo_phy_घातer_on,
	.घातer_off	= cdns_salvo_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक cdns_salvo_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cdns_salvo_phy *salvo_phy;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा cdns_salvo_data *data;

	match = of_match_device(cdns_salvo_phy_of_match, dev);
	अगर (!match)
		वापस -EINVAL;

	data = (काष्ठा cdns_salvo_data *)match->data;
	salvo_phy = devm_kzalloc(dev, माप(*salvo_phy), GFP_KERNEL);
	अगर (!salvo_phy)
		वापस -ENOMEM;

	salvo_phy->data = data;
	salvo_phy->clk = devm_clk_get_optional(dev, "salvo_phy_clk");
	अगर (IS_ERR(salvo_phy->clk))
		वापस PTR_ERR(salvo_phy->clk);

	salvo_phy->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(salvo_phy->base))
		वापस PTR_ERR(salvo_phy->base);

	salvo_phy->phy = devm_phy_create(dev, शून्य, &cdns_salvo_phy_ops);
	अगर (IS_ERR(salvo_phy->phy))
		वापस PTR_ERR(salvo_phy->phy);

	phy_set_drvdata(salvo_phy->phy, salvo_phy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा cdns_salvo_data cdns_nxp_salvo_data = अणु
	2,
	cdns_nxp_sequence_pair,
	ARRAY_SIZE(cdns_nxp_sequence_pair),
पूर्ण;

अटल स्थिर काष्ठा of_device_id cdns_salvo_phy_of_match[] = अणु
	अणु
		.compatible = "nxp,salvo-phy",
		.data = &cdns_nxp_salvo_data,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cdns_salvo_phy_of_match);

अटल काष्ठा platक्रमm_driver cdns_salvo_phy_driver = अणु
	.probe	= cdns_salvo_phy_probe,
	.driver = अणु
		.name	= "cdns-salvo-phy",
		.of_match_table	= cdns_salvo_phy_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(cdns_salvo_phy_driver);

MODULE_AUTHOR("Peter Chen <peter.chen@nxp.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Cadence SALVO PHY Driver");
