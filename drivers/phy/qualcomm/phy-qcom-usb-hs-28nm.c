<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2009-2018, Linux Foundation. All rights reserved.
 * Copyright (c) 2018-2020, Linaro Limited
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

/* PHY रेजिस्टर and bit definitions */
#घोषणा PHY_CTRL_COMMON0		0x078
#घोषणा SIDDQ				BIT(2)
#घोषणा PHY_IRQ_CMD			0x0d0
#घोषणा PHY_INTR_MASK0			0x0d4
#घोषणा PHY_INTR_CLEAR0			0x0dc
#घोषणा DPDM_MASK			0x1e
#घोषणा DP_1_0				BIT(4)
#घोषणा DP_0_1				BIT(3)
#घोषणा DM_1_0				BIT(2)
#घोषणा DM_0_1				BIT(1)

क्रमागत hsphy_voltage अणु
	VOL_NONE,
	VOL_MIN,
	VOL_MAX,
	VOL_NUM,
पूर्ण;

क्रमागत hsphy_vreg अणु
	VDD,
	VDDA_1P8,
	VDDA_3P3,
	VREG_NUM,
पूर्ण;

काष्ठा hsphy_init_seq अणु
	पूर्णांक offset;
	पूर्णांक val;
	पूर्णांक delay;
पूर्ण;

काष्ठा hsphy_data अणु
	स्थिर काष्ठा hsphy_init_seq *init_seq;
	अचिन्हित पूर्णांक init_seq_num;
पूर्ण;

काष्ठा hsphy_priv अणु
	व्योम __iomem *base;
	काष्ठा clk_bulk_data *clks;
	पूर्णांक num_clks;
	काष्ठा reset_control *phy_reset;
	काष्ठा reset_control *por_reset;
	काष्ठा regulator_bulk_data vregs[VREG_NUM];
	स्थिर काष्ठा hsphy_data *data;
	क्रमागत phy_mode mode;
पूर्ण;

अटल पूर्णांक qcom_snps_hsphy_set_mode(काष्ठा phy *phy, क्रमागत phy_mode mode,
				    पूर्णांक submode)
अणु
	काष्ठा hsphy_priv *priv = phy_get_drvdata(phy);

	priv->mode = PHY_MODE_INVALID;

	अगर (mode > 0)
		priv->mode = mode;

	वापस 0;
पूर्ण

अटल व्योम qcom_snps_hsphy_enable_hv_पूर्णांकerrupts(काष्ठा hsphy_priv *priv)
अणु
	u32 val;

	/* Clear any existing पूर्णांकerrupts beक्रमe enabling the पूर्णांकerrupts */
	val = पढ़ोb(priv->base + PHY_INTR_CLEAR0);
	val |= DPDM_MASK;
	ग_लिखोb(val, priv->base + PHY_INTR_CLEAR0);

	ग_लिखोb(0x0, priv->base + PHY_IRQ_CMD);
	usleep_range(200, 220);
	ग_लिखोb(0x1, priv->base + PHY_IRQ_CMD);

	/* Make sure the पूर्णांकerrupts are cleared */
	usleep_range(200, 220);

	val = पढ़ोb(priv->base + PHY_INTR_MASK0);
	चयन (priv->mode) अणु
	हाल PHY_MODE_USB_HOST_HS:
	हाल PHY_MODE_USB_HOST_FS:
	हाल PHY_MODE_USB_DEVICE_HS:
	हाल PHY_MODE_USB_DEVICE_FS:
		val |= DP_1_0 | DM_0_1;
		अवरोध;
	हाल PHY_MODE_USB_HOST_LS:
	हाल PHY_MODE_USB_DEVICE_LS:
		val |= DP_0_1 | DM_1_0;
		अवरोध;
	शेष:
		/* No device connected */
		val |= DP_0_1 | DM_0_1;
		अवरोध;
	पूर्ण
	ग_लिखोb(val, priv->base + PHY_INTR_MASK0);
पूर्ण

अटल व्योम qcom_snps_hsphy_disable_hv_पूर्णांकerrupts(काष्ठा hsphy_priv *priv)
अणु
	u32 val;

	val = पढ़ोb(priv->base + PHY_INTR_MASK0);
	val &= ~DPDM_MASK;
	ग_लिखोb(val, priv->base + PHY_INTR_MASK0);

	/* Clear any pending पूर्णांकerrupts */
	val = पढ़ोb(priv->base + PHY_INTR_CLEAR0);
	val |= DPDM_MASK;
	ग_लिखोb(val, priv->base + PHY_INTR_CLEAR0);

	ग_लिखोb(0x0, priv->base + PHY_IRQ_CMD);
	usleep_range(200, 220);

	ग_लिखोb(0x1, priv->base + PHY_IRQ_CMD);
	usleep_range(200, 220);
पूर्ण

अटल व्योम qcom_snps_hsphy_enter_retention(काष्ठा hsphy_priv *priv)
अणु
	u32 val;

	val = पढ़ोb(priv->base + PHY_CTRL_COMMON0);
	val |= SIDDQ;
	ग_लिखोb(val, priv->base + PHY_CTRL_COMMON0);
पूर्ण

अटल व्योम qcom_snps_hsphy_निकास_retention(काष्ठा hsphy_priv *priv)
अणु
	u32 val;

	val = पढ़ोb(priv->base + PHY_CTRL_COMMON0);
	val &= ~SIDDQ;
	ग_लिखोb(val, priv->base + PHY_CTRL_COMMON0);
पूर्ण

अटल पूर्णांक qcom_snps_hsphy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा hsphy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = regulator_bulk_enable(VREG_NUM, priv->vregs);
	अगर (ret)
		वापस ret;

	qcom_snps_hsphy_disable_hv_पूर्णांकerrupts(priv);
	qcom_snps_hsphy_निकास_retention(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_snps_hsphy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा hsphy_priv *priv = phy_get_drvdata(phy);

	qcom_snps_hsphy_enter_retention(priv);
	qcom_snps_hsphy_enable_hv_पूर्णांकerrupts(priv);
	regulator_bulk_disable(VREG_NUM, priv->vregs);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_snps_hsphy_reset(काष्ठा hsphy_priv *priv)
अणु
	पूर्णांक ret;

	ret = reset_control_निश्चित(priv->phy_reset);
	अगर (ret)
		वापस ret;

	usleep_range(10, 15);

	ret = reset_control_deनिश्चित(priv->phy_reset);
	अगर (ret)
		वापस ret;

	usleep_range(80, 100);

	वापस 0;
पूर्ण

अटल व्योम qcom_snps_hsphy_init_sequence(काष्ठा hsphy_priv *priv)
अणु
	स्थिर काष्ठा hsphy_data *data = priv->data;
	स्थिर काष्ठा hsphy_init_seq *seq;
	पूर्णांक i;

	/* Device match data is optional. */
	अगर (!data)
		वापस;

	seq = data->init_seq;

	क्रम (i = 0; i < data->init_seq_num; i++, seq++) अणु
		ग_लिखोb(seq->val, priv->base + seq->offset);
		अगर (seq->delay)
			usleep_range(seq->delay, seq->delay + 10);
	पूर्ण
पूर्ण

अटल पूर्णांक qcom_snps_hsphy_por_reset(काष्ठा hsphy_priv *priv)
अणु
	पूर्णांक ret;

	ret = reset_control_निश्चित(priv->por_reset);
	अगर (ret)
		वापस ret;

	/*
	 * The Femto PHY is POR reset in the following scenarios.
	 *
	 * 1. After overriding the parameter रेजिस्टरs.
	 * 2. Low घातer mode निकास from PHY retention.
	 *
	 * Ensure that SIDDQ is cleared beक्रमe bringing the PHY
	 * out of reset.
	 */
	qcom_snps_hsphy_निकास_retention(priv);

	/*
	 * As per databook, 10 usec delay is required between
	 * PHY POR निश्चित and de-निश्चित.
	 */
	usleep_range(10, 20);
	ret = reset_control_deनिश्चित(priv->por_reset);
	अगर (ret)
		वापस ret;

	/*
	 * As per databook, it takes 75 usec क्रम PHY to stabilize
	 * after the reset.
	 */
	usleep_range(80, 100);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_snps_hsphy_init(काष्ठा phy *phy)
अणु
	काष्ठा hsphy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = clk_bulk_prepare_enable(priv->num_clks, priv->clks);
	अगर (ret)
		वापस ret;

	ret = qcom_snps_hsphy_reset(priv);
	अगर (ret)
		जाओ disable_घड़ीs;

	qcom_snps_hsphy_init_sequence(priv);

	ret = qcom_snps_hsphy_por_reset(priv);
	अगर (ret)
		जाओ disable_घड़ीs;

	वापस 0;

disable_घड़ीs:
	clk_bulk_disable_unprepare(priv->num_clks, priv->clks);
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_snps_hsphy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा hsphy_priv *priv = phy_get_drvdata(phy);

	clk_bulk_disable_unprepare(priv->num_clks, priv->clks);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops qcom_snps_hsphy_ops = अणु
	.init = qcom_snps_hsphy_init,
	.निकास = qcom_snps_hsphy_निकास,
	.घातer_on = qcom_snps_hsphy_घातer_on,
	.घातer_off = qcom_snps_hsphy_घातer_off,
	.set_mode = qcom_snps_hsphy_set_mode,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर अक्षर * स्थिर qcom_snps_hsphy_clks[] = अणु
	"ref",
	"ahb",
	"sleep",
पूर्ण;

अटल पूर्णांक qcom_snps_hsphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_provider *provider;
	काष्ठा hsphy_priv *priv;
	काष्ठा phy *phy;
	पूर्णांक ret;
	पूर्णांक i;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	priv->num_clks = ARRAY_SIZE(qcom_snps_hsphy_clks);
	priv->clks = devm_kसुस्मृति(dev, priv->num_clks, माप(*priv->clks),
				  GFP_KERNEL);
	अगर (!priv->clks)
		वापस -ENOMEM;

	क्रम (i = 0; i < priv->num_clks; i++)
		priv->clks[i].id = qcom_snps_hsphy_clks[i];

	ret = devm_clk_bulk_get(dev, priv->num_clks, priv->clks);
	अगर (ret)
		वापस ret;

	priv->phy_reset = devm_reset_control_get_exclusive(dev, "phy");
	अगर (IS_ERR(priv->phy_reset))
		वापस PTR_ERR(priv->phy_reset);

	priv->por_reset = devm_reset_control_get_exclusive(dev, "por");
	अगर (IS_ERR(priv->por_reset))
		वापस PTR_ERR(priv->por_reset);

	priv->vregs[VDD].supply = "vdd";
	priv->vregs[VDDA_1P8].supply = "vdda1p8";
	priv->vregs[VDDA_3P3].supply = "vdda3p3";

	ret = devm_regulator_bulk_get(dev, VREG_NUM, priv->vregs);
	अगर (ret)
		वापस ret;

	/* Get device match data */
	priv->data = device_get_match_data(dev);

	phy = devm_phy_create(dev, dev->of_node, &qcom_snps_hsphy_ops);
	अगर (IS_ERR(phy))
		वापस PTR_ERR(phy);

	phy_set_drvdata(phy, priv);

	provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(provider))
		वापस PTR_ERR(provider);

	ret = regulator_set_load(priv->vregs[VDDA_1P8].consumer, 19000);
	अगर (ret < 0)
		वापस ret;

	ret = regulator_set_load(priv->vregs[VDDA_3P3].consumer, 16000);
	अगर (ret < 0)
		जाओ unset_1p8_load;

	वापस 0;

unset_1p8_load:
	regulator_set_load(priv->vregs[VDDA_1P8].consumer, 0);

	वापस ret;
पूर्ण

/*
 * The macro is used to define an initialization sequence.  Each tuple
 * is meant to program 'value' into phy register at 'offset' with 'delay'
 * in us followed.
 */
#घोषणा HSPHY_INIT_CFG(o, v, d)	अणु .offset = o, .val = v, .delay = d, पूर्ण

अटल स्थिर काष्ठा hsphy_init_seq init_seq_femtophy[] = अणु
	HSPHY_INIT_CFG(0xc0, 0x01, 0),
	HSPHY_INIT_CFG(0xe8, 0x0d, 0),
	HSPHY_INIT_CFG(0x74, 0x12, 0),
	HSPHY_INIT_CFG(0x98, 0x63, 0),
	HSPHY_INIT_CFG(0x9c, 0x03, 0),
	HSPHY_INIT_CFG(0xa0, 0x1d, 0),
	HSPHY_INIT_CFG(0xa4, 0x03, 0),
	HSPHY_INIT_CFG(0x8c, 0x23, 0),
	HSPHY_INIT_CFG(0x78, 0x08, 0),
	HSPHY_INIT_CFG(0x7c, 0xdc, 0),
	HSPHY_INIT_CFG(0x90, 0xe0, 20),
	HSPHY_INIT_CFG(0x74, 0x10, 0),
	HSPHY_INIT_CFG(0x90, 0x60, 0),
पूर्ण;

अटल स्थिर काष्ठा hsphy_init_seq init_seq_mdm9607[] = अणु
	HSPHY_INIT_CFG(0x80, 0x44, 0),
	HSPHY_INIT_CFG(0x81, 0x38, 0),
	HSPHY_INIT_CFG(0x82, 0x24, 0),
	HSPHY_INIT_CFG(0x83, 0x13, 0),
पूर्ण;

अटल स्थिर काष्ठा hsphy_data hsphy_data_femtophy = अणु
	.init_seq = init_seq_femtophy,
	.init_seq_num = ARRAY_SIZE(init_seq_femtophy),
पूर्ण;

अटल स्थिर काष्ठा hsphy_data hsphy_data_mdm9607 = अणु
	.init_seq = init_seq_mdm9607,
	.init_seq_num = ARRAY_SIZE(init_seq_mdm9607),
पूर्ण;

अटल स्थिर काष्ठा of_device_id qcom_snps_hsphy_match[] = अणु
	अणु .compatible = "qcom,usb-hs-28nm-femtophy", .data = &hsphy_data_femtophy, पूर्ण,
	अणु .compatible = "qcom,usb-hs-28nm-mdm9607", .data = &hsphy_data_mdm9607, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_snps_hsphy_match);

अटल काष्ठा platक्रमm_driver qcom_snps_hsphy_driver = अणु
	.probe = qcom_snps_hsphy_probe,
	.driver	= अणु
		.name = "qcom,usb-hs-28nm-phy",
		.of_match_table = qcom_snps_hsphy_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_snps_hsphy_driver);

MODULE_DESCRIPTION("Qualcomm 28nm Hi-Speed USB PHY driver");
MODULE_LICENSE("GPL v2");
