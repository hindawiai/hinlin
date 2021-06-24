<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

#घोषणा USB2_PHY_USB_PHY_UTMI_CTRL0		(0x3c)
#घोषणा SLEEPM					BIT(0)
#घोषणा OPMODE_MASK				GENMASK(4, 3)
#घोषणा OPMODE_NORMAL				(0x00)
#घोषणा OPMODE_NONDRIVING			BIT(3)
#घोषणा TERMSEL					BIT(5)

#घोषणा USB2_PHY_USB_PHY_UTMI_CTRL1		(0x40)
#घोषणा XCVRSEL					BIT(0)

#घोषणा USB2_PHY_USB_PHY_UTMI_CTRL5		(0x50)
#घोषणा POR					BIT(1)

#घोषणा USB2_PHY_USB_PHY_HS_PHY_CTRL_COMMON0	(0x54)
#घोषणा RETENABLEN				BIT(3)
#घोषणा FSEL_MASK				GENMASK(7, 5)
#घोषणा FSEL_DEFAULT				(0x3 << 4)

#घोषणा USB2_PHY_USB_PHY_HS_PHY_CTRL_COMMON1	(0x58)
#घोषणा VBUSVLDEXTSEL0				BIT(4)
#घोषणा PLLBTUNE				BIT(5)

#घोषणा USB2_PHY_USB_PHY_HS_PHY_CTRL_COMMON2	(0x5c)
#घोषणा VREGBYPASS				BIT(0)

#घोषणा USB2_PHY_USB_PHY_HS_PHY_CTRL1		(0x60)
#घोषणा VBUSVLDEXT0				BIT(0)

#घोषणा USB2_PHY_USB_PHY_HS_PHY_CTRL2		(0x64)
#घोषणा USB2_AUTO_RESUME			BIT(0)
#घोषणा USB2_SUSPEND_N				BIT(2)
#घोषणा USB2_SUSPEND_N_SEL			BIT(3)

#घोषणा USB2_PHY_USB_PHY_CFG0			(0x94)
#घोषणा UTMI_PHY_DATAPATH_CTRL_OVERRIDE_EN	BIT(0)
#घोषणा UTMI_PHY_CMN_CTRL_OVERRIDE_EN		BIT(1)

#घोषणा USB2_PHY_USB_PHY_REFCLK_CTRL		(0xa0)
#घोषणा REFCLK_SEL_MASK				GENMASK(1, 0)
#घोषणा REFCLK_SEL_DEFAULT			(0x2 << 0)

अटल स्थिर अक्षर * स्थिर qcom_snps_hsphy_vreg_names[] = अणु
	"vdda-pll", "vdda33", "vdda18",
पूर्ण;

#घोषणा SNPS_HS_NUM_VREGS		ARRAY_SIZE(qcom_snps_hsphy_vreg_names)

/**
 * काष्ठा qcom_snps_hsphy - snps hs phy attributes
 *
 * @phy: generic phy
 * @base: iomapped memory space क्रम snps hs phy
 *
 * @cfg_ahb_clk: AHB2PHY पूर्णांकerface घड़ी
 * @ref_clk: phy reference घड़ी
 * @अगरace_clk: phy पूर्णांकerface घड़ी
 * @phy_reset: phy reset control
 * @vregs: regulator supplies bulk data
 * @phy_initialized: अगर PHY has been initialized correctly
 * @mode: contains the current mode the PHY is in
 */
काष्ठा qcom_snps_hsphy अणु
	काष्ठा phy *phy;
	व्योम __iomem *base;

	काष्ठा clk *cfg_ahb_clk;
	काष्ठा clk *ref_clk;
	काष्ठा reset_control *phy_reset;
	काष्ठा regulator_bulk_data vregs[SNPS_HS_NUM_VREGS];

	bool phy_initialized;
	क्रमागत phy_mode mode;
पूर्ण;

अटल अंतरभूत व्योम qcom_snps_hsphy_ग_लिखो_mask(व्योम __iomem *base, u32 offset,
						u32 mask, u32 val)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(base + offset);
	reg &= ~mask;
	reg |= val & mask;
	ग_लिखोl_relaxed(reg, base + offset);

	/* Ensure above ग_लिखो is completed */
	पढ़ोl_relaxed(base + offset);
पूर्ण

अटल पूर्णांक qcom_snps_hsphy_suspend(काष्ठा qcom_snps_hsphy *hsphy)
अणु
	dev_dbg(&hsphy->phy->dev, "Suspend QCOM SNPS PHY\n");

	अगर (hsphy->mode == PHY_MODE_USB_HOST) अणु
		/* Enable स्वतः-resume to meet remote wakeup timing */
		qcom_snps_hsphy_ग_लिखो_mask(hsphy->base,
					   USB2_PHY_USB_PHY_HS_PHY_CTRL2,
					   USB2_AUTO_RESUME,
					   USB2_AUTO_RESUME);
		usleep_range(500, 1000);
		qcom_snps_hsphy_ग_लिखो_mask(hsphy->base,
					   USB2_PHY_USB_PHY_HS_PHY_CTRL2,
					   0, USB2_AUTO_RESUME);
	पूर्ण

	clk_disable_unprepare(hsphy->cfg_ahb_clk);
	वापस 0;
पूर्ण

अटल पूर्णांक qcom_snps_hsphy_resume(काष्ठा qcom_snps_hsphy *hsphy)
अणु
	पूर्णांक ret;

	dev_dbg(&hsphy->phy->dev, "Resume QCOM SNPS PHY, mode\n");

	ret = clk_prepare_enable(hsphy->cfg_ahb_clk);
	अगर (ret) अणु
		dev_err(&hsphy->phy->dev, "failed to enable cfg ahb clock\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused qcom_snps_hsphy_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा qcom_snps_hsphy *hsphy = dev_get_drvdata(dev);

	अगर (!hsphy->phy_initialized)
		वापस 0;

	qcom_snps_hsphy_suspend(hsphy);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused qcom_snps_hsphy_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा qcom_snps_hsphy *hsphy = dev_get_drvdata(dev);

	अगर (!hsphy->phy_initialized)
		वापस 0;

	qcom_snps_hsphy_resume(hsphy);
	वापस 0;
पूर्ण

अटल पूर्णांक qcom_snps_hsphy_set_mode(काष्ठा phy *phy, क्रमागत phy_mode mode,
				    पूर्णांक submode)
अणु
	काष्ठा qcom_snps_hsphy *hsphy = phy_get_drvdata(phy);

	hsphy->mode = mode;
	वापस 0;
पूर्ण

अटल पूर्णांक qcom_snps_hsphy_init(काष्ठा phy *phy)
अणु
	काष्ठा qcom_snps_hsphy *hsphy = phy_get_drvdata(phy);
	पूर्णांक ret;

	dev_vdbg(&phy->dev, "%s(): Initializing SNPS HS phy\n", __func__);

	ret = regulator_bulk_enable(ARRAY_SIZE(hsphy->vregs), hsphy->vregs);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(hsphy->cfg_ahb_clk);
	अगर (ret) अणु
		dev_err(&phy->dev, "failed to enable cfg ahb clock, %d\n", ret);
		जाओ घातeroff_phy;
	पूर्ण

	ret = reset_control_निश्चित(hsphy->phy_reset);
	अगर (ret) अणु
		dev_err(&phy->dev, "failed to assert phy_reset, %d\n", ret);
		जाओ disable_ahb_clk;
	पूर्ण

	usleep_range(100, 150);

	ret = reset_control_deनिश्चित(hsphy->phy_reset);
	अगर (ret) अणु
		dev_err(&phy->dev, "failed to de-assert phy_reset, %d\n", ret);
		जाओ disable_ahb_clk;
	पूर्ण

	qcom_snps_hsphy_ग_लिखो_mask(hsphy->base, USB2_PHY_USB_PHY_CFG0,
					UTMI_PHY_CMN_CTRL_OVERRIDE_EN,
					UTMI_PHY_CMN_CTRL_OVERRIDE_EN);
	qcom_snps_hsphy_ग_लिखो_mask(hsphy->base, USB2_PHY_USB_PHY_UTMI_CTRL5,
							POR, POR);
	qcom_snps_hsphy_ग_लिखो_mask(hsphy->base,
					USB2_PHY_USB_PHY_HS_PHY_CTRL_COMMON0,
					FSEL_MASK, 0);
	qcom_snps_hsphy_ग_लिखो_mask(hsphy->base,
					USB2_PHY_USB_PHY_HS_PHY_CTRL_COMMON1,
					PLLBTUNE, PLLBTUNE);
	qcom_snps_hsphy_ग_लिखो_mask(hsphy->base, USB2_PHY_USB_PHY_REFCLK_CTRL,
					REFCLK_SEL_DEFAULT, REFCLK_SEL_MASK);
	qcom_snps_hsphy_ग_लिखो_mask(hsphy->base,
					USB2_PHY_USB_PHY_HS_PHY_CTRL_COMMON1,
					VBUSVLDEXTSEL0, VBUSVLDEXTSEL0);
	qcom_snps_hsphy_ग_लिखो_mask(hsphy->base, USB2_PHY_USB_PHY_HS_PHY_CTRL1,
					VBUSVLDEXT0, VBUSVLDEXT0);

	qcom_snps_hsphy_ग_लिखो_mask(hsphy->base,
					USB2_PHY_USB_PHY_HS_PHY_CTRL_COMMON2,
					VREGBYPASS, VREGBYPASS);

	qcom_snps_hsphy_ग_लिखो_mask(hsphy->base, USB2_PHY_USB_PHY_HS_PHY_CTRL2,
					USB2_SUSPEND_N_SEL | USB2_SUSPEND_N,
					USB2_SUSPEND_N_SEL | USB2_SUSPEND_N);

	qcom_snps_hsphy_ग_लिखो_mask(hsphy->base, USB2_PHY_USB_PHY_UTMI_CTRL0,
					SLEEPM, SLEEPM);

	qcom_snps_hsphy_ग_लिखो_mask(hsphy->base, USB2_PHY_USB_PHY_UTMI_CTRL5,
					POR, 0);

	qcom_snps_hsphy_ग_लिखो_mask(hsphy->base, USB2_PHY_USB_PHY_HS_PHY_CTRL2,
					USB2_SUSPEND_N_SEL, 0);

	qcom_snps_hsphy_ग_लिखो_mask(hsphy->base, USB2_PHY_USB_PHY_CFG0,
					UTMI_PHY_CMN_CTRL_OVERRIDE_EN, 0);

	hsphy->phy_initialized = true;

	वापस 0;

disable_ahb_clk:
	clk_disable_unprepare(hsphy->cfg_ahb_clk);
घातeroff_phy:
	regulator_bulk_disable(ARRAY_SIZE(hsphy->vregs), hsphy->vregs);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_snps_hsphy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा qcom_snps_hsphy *hsphy = phy_get_drvdata(phy);

	reset_control_निश्चित(hsphy->phy_reset);
	clk_disable_unprepare(hsphy->cfg_ahb_clk);
	regulator_bulk_disable(ARRAY_SIZE(hsphy->vregs), hsphy->vregs);
	hsphy->phy_initialized = false;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops qcom_snps_hsphy_gen_ops = अणु
	.init		= qcom_snps_hsphy_init,
	.निकास		= qcom_snps_hsphy_निकास,
	.set_mode	= qcom_snps_hsphy_set_mode,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id qcom_snps_hsphy_of_match_table[] = अणु
	अणु .compatible	= "qcom,sm8150-usb-hs-phy", पूर्ण,
	अणु .compatible	= "qcom,usb-snps-hs-7nm-phy", पूर्ण,
	अणु .compatible	= "qcom,usb-snps-femto-v2-phy",	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_snps_hsphy_of_match_table);

अटल स्थिर काष्ठा dev_pm_ops qcom_snps_hsphy_pm_ops = अणु
	SET_RUNTIME_PM_OPS(qcom_snps_hsphy_runसमय_suspend,
			   qcom_snps_hsphy_runसमय_resume, शून्य)
पूर्ण;

अटल पूर्णांक qcom_snps_hsphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा qcom_snps_hsphy *hsphy;
	काष्ठा phy_provider *phy_provider;
	काष्ठा phy *generic_phy;
	पूर्णांक ret, i;
	पूर्णांक num;

	hsphy = devm_kzalloc(dev, माप(*hsphy), GFP_KERNEL);
	अगर (!hsphy)
		वापस -ENOMEM;

	hsphy->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hsphy->base))
		वापस PTR_ERR(hsphy->base);

	hsphy->ref_clk = devm_clk_get(dev, "ref");
	अगर (IS_ERR(hsphy->ref_clk)) अणु
		ret = PTR_ERR(hsphy->ref_clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get ref clk, %d\n", ret);
		वापस ret;
	पूर्ण

	hsphy->phy_reset = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(hsphy->phy_reset)) अणु
		dev_err(dev, "failed to get phy core reset\n");
		वापस PTR_ERR(hsphy->phy_reset);
	पूर्ण

	num = ARRAY_SIZE(hsphy->vregs);
	क्रम (i = 0; i < num; i++)
		hsphy->vregs[i].supply = qcom_snps_hsphy_vreg_names[i];

	ret = devm_regulator_bulk_get(dev, num, hsphy->vregs);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get regulator supplies: %d\n",
				ret);
		वापस ret;
	पूर्ण

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	/*
	 * Prevent runसमय pm from being ON by शेष. Users can enable
	 * it using घातer/control in sysfs.
	 */
	pm_runसमय_क्रमbid(dev);

	generic_phy = devm_phy_create(dev, शून्य, &qcom_snps_hsphy_gen_ops);
	अगर (IS_ERR(generic_phy)) अणु
		ret = PTR_ERR(generic_phy);
		dev_err(dev, "failed to create phy, %d\n", ret);
		वापस ret;
	पूर्ण
	hsphy->phy = generic_phy;

	dev_set_drvdata(dev, hsphy);
	phy_set_drvdata(generic_phy, hsphy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (!IS_ERR(phy_provider))
		dev_dbg(dev, "Registered Qcom-SNPS HS phy\n");
	अन्यथा
		pm_runसमय_disable(dev);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल काष्ठा platक्रमm_driver qcom_snps_hsphy_driver = अणु
	.probe		= qcom_snps_hsphy_probe,
	.driver = अणु
		.name	= "qcom-snps-hs-femto-v2-phy",
		.pm = &qcom_snps_hsphy_pm_ops,
		.of_match_table = qcom_snps_hsphy_of_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(qcom_snps_hsphy_driver);

MODULE_DESCRIPTION("Qualcomm SNPS FEMTO USB HS PHY V2 driver");
MODULE_LICENSE("GPL v2");
