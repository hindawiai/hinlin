<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2010-2011, Code Aurora Forum. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/log2.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#घोषणा PON_CNTL_1 0x1C
#घोषणा PON_CNTL_PULL_UP BIT(7)
#घोषणा PON_CNTL_TRIG_DELAY_MASK (0x7)
#घोषणा PON_CNTL_1_PULL_UP_EN			0xe0
#घोषणा PON_CNTL_1_USB_PWR_EN			0x10
#घोषणा PON_CNTL_1_WD_EN_RESET			0x08

#घोषणा PM8058_SLEEP_CTRL			0x02b
#घोषणा PM8921_SLEEP_CTRL			0x10a

#घोषणा SLEEP_CTRL_SMPL_EN_RESET		0x04

/* Regulator master enable addresses */
#घोषणा REG_PM8058_VREG_EN_MSM			0x018
#घोषणा REG_PM8058_VREG_EN_GRP_5_4		0x1c8

/* Regulator control रेजिस्टरs क्रम shutकरोwn/reset */
#घोषणा PM8058_S0_CTRL				0x004
#घोषणा PM8058_S1_CTRL				0x005
#घोषणा PM8058_S3_CTRL				0x111
#घोषणा PM8058_L21_CTRL				0x120
#घोषणा PM8058_L22_CTRL				0x121

#घोषणा PM8058_REGULATOR_ENABLE_MASK		0x80
#घोषणा PM8058_REGULATOR_ENABLE			0x80
#घोषणा PM8058_REGULATOR_DISABLE		0x00
#घोषणा PM8058_REGULATOR_PULL_DOWN_MASK		0x40
#घोषणा PM8058_REGULATOR_PULL_DOWN_EN		0x40

/* Buck CTRL रेजिस्टर */
#घोषणा PM8058_SMPS_LEGACY_VREF_SEL		0x20
#घोषणा PM8058_SMPS_LEGACY_VPROG_MASK		0x1f
#घोषणा PM8058_SMPS_ADVANCED_BAND_MASK		0xC0
#घोषणा PM8058_SMPS_ADVANCED_BAND_SHIFT		6
#घोषणा PM8058_SMPS_ADVANCED_VPROG_MASK		0x3f

/* Buck TEST2 रेजिस्टरs क्रम shutकरोwn/reset */
#घोषणा PM8058_S0_TEST2				0x084
#घोषणा PM8058_S1_TEST2				0x085
#घोषणा PM8058_S3_TEST2				0x11a

#घोषणा PM8058_REGULATOR_BANK_WRITE		0x80
#घोषणा PM8058_REGULATOR_BANK_MASK		0x70
#घोषणा PM8058_REGULATOR_BANK_SHIFT		4
#घोषणा PM8058_REGULATOR_BANK_SEL(n)	((n) << PM8058_REGULATOR_BANK_SHIFT)

/* Buck TEST2 रेजिस्टर bank 1 */
#घोषणा PM8058_SMPS_LEGACY_VLOW_SEL		0x01

/* Buck TEST2 रेजिस्टर bank 7 */
#घोषणा PM8058_SMPS_ADVANCED_MODE_MASK		0x02
#घोषणा PM8058_SMPS_ADVANCED_MODE		0x02
#घोषणा PM8058_SMPS_LEGACY_MODE			0x00

/**
 * काष्ठा pmic8xxx_pwrkey - pmic8xxx pwrkey inक्रमmation
 * @key_press_irq: key press irq number
 * @regmap: device regmap
 * @shutकरोwn_fn: shutकरोwn configuration function
 */
काष्ठा pmic8xxx_pwrkey अणु
	पूर्णांक key_press_irq;
	काष्ठा regmap *regmap;
	पूर्णांक (*shutकरोwn_fn)(काष्ठा pmic8xxx_pwrkey *, bool);
पूर्ण;

अटल irqवापस_t pwrkey_press_irq(पूर्णांक irq, व्योम *_pwr)
अणु
	काष्ठा input_dev *pwr = _pwr;

	input_report_key(pwr, KEY_POWER, 1);
	input_sync(pwr);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t pwrkey_release_irq(पूर्णांक irq, व्योम *_pwr)
अणु
	काष्ठा input_dev *pwr = _pwr;

	input_report_key(pwr, KEY_POWER, 0);
	input_sync(pwr);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __maybe_unused pmic8xxx_pwrkey_suspend(काष्ठा device *dev)
अणु
	काष्ठा pmic8xxx_pwrkey *pwrkey = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(pwrkey->key_press_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pmic8xxx_pwrkey_resume(काष्ठा device *dev)
अणु
	काष्ठा pmic8xxx_pwrkey *pwrkey = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(pwrkey->key_press_irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pm8xxx_pwr_key_pm_ops,
		pmic8xxx_pwrkey_suspend, pmic8xxx_pwrkey_resume);

अटल व्योम pmic8xxx_pwrkey_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pmic8xxx_pwrkey *pwrkey = platक्रमm_get_drvdata(pdev);
	पूर्णांक error;
	u8 mask, val;
	bool reset = प्रणाली_state == SYSTEM_RESTART;

	अगर (pwrkey->shutकरोwn_fn) अणु
		error = pwrkey->shutकरोwn_fn(pwrkey, reset);
		अगर (error)
			वापस;
	पूर्ण

	/*
	 * Select action to perक्रमm (reset or shutकरोwn) when PS_HOLD goes low.
	 * Also ensure that KPD, CBL0, and CBL1 pull ups are enabled and that
	 * USB अक्षरging is enabled.
	 */
	mask = PON_CNTL_1_PULL_UP_EN | PON_CNTL_1_USB_PWR_EN;
	mask |= PON_CNTL_1_WD_EN_RESET;
	val = mask;
	अगर (!reset)
		val &= ~PON_CNTL_1_WD_EN_RESET;

	regmap_update_bits(pwrkey->regmap, PON_CNTL_1, mask, val);
पूर्ण

/*
 * Set an SMPS regulator to be disabled in its CTRL रेजिस्टर, but enabled
 * in the master enable रेजिस्टर.  Also set it's pull करोwn enable bit.
 * Take care to make sure that the output voltage करोesn't change अगर चयनing
 * from advanced mode to legacy mode.
 */
अटल पूर्णांक pm8058_disable_smps_locally_set_pull_करोwn(काष्ठा regmap *regmap,
	u16 ctrl_addr, u16 test2_addr, u16 master_enable_addr,
	u8 master_enable_bit)
अणु
	पूर्णांक error;
	u8 vref_sel, vlow_sel, band, vprog, bank;
	अचिन्हित पूर्णांक reg;

	bank = PM8058_REGULATOR_BANK_SEL(7);
	error = regmap_ग_लिखो(regmap, test2_addr, bank);
	अगर (error)
		वापस error;

	error = regmap_पढ़ो(regmap, test2_addr, &reg);
	अगर (error)
		वापस error;

	reg &= PM8058_SMPS_ADVANCED_MODE_MASK;
	/* Check अगर in advanced mode. */
	अगर (reg == PM8058_SMPS_ADVANCED_MODE) अणु
		/* Determine current output voltage. */
		error = regmap_पढ़ो(regmap, ctrl_addr, &reg);
		अगर (error)
			वापस error;

		band = reg & PM8058_SMPS_ADVANCED_BAND_MASK;
		band >>= PM8058_SMPS_ADVANCED_BAND_SHIFT;
		चयन (band) अणु
		हाल 3:
			vref_sel = 0;
			vlow_sel = 0;
			अवरोध;
		हाल 2:
			vref_sel = PM8058_SMPS_LEGACY_VREF_SEL;
			vlow_sel = 0;
			अवरोध;
		हाल 1:
			vref_sel = PM8058_SMPS_LEGACY_VREF_SEL;
			vlow_sel = PM8058_SMPS_LEGACY_VLOW_SEL;
			अवरोध;
		शेष:
			pr_err("%s: regulator already disabled\n", __func__);
			वापस -EPERM;
		पूर्ण
		vprog = reg & PM8058_SMPS_ADVANCED_VPROG_MASK;
		/* Round up अगर fine step is in use. */
		vprog = (vprog + 1) >> 1;
		अगर (vprog > PM8058_SMPS_LEGACY_VPROG_MASK)
			vprog = PM8058_SMPS_LEGACY_VPROG_MASK;

		/* Set VLOW_SEL bit. */
		bank = PM8058_REGULATOR_BANK_SEL(1);
		error = regmap_ग_लिखो(regmap, test2_addr, bank);
		अगर (error)
			वापस error;

		error = regmap_update_bits(regmap, test2_addr,
			PM8058_REGULATOR_BANK_WRITE | PM8058_REGULATOR_BANK_MASK
				| PM8058_SMPS_LEGACY_VLOW_SEL,
			PM8058_REGULATOR_BANK_WRITE |
			PM8058_REGULATOR_BANK_SEL(1) | vlow_sel);
		अगर (error)
			वापस error;

		/* Switch to legacy mode */
		bank = PM8058_REGULATOR_BANK_SEL(7);
		error = regmap_ग_लिखो(regmap, test2_addr, bank);
		अगर (error)
			वापस error;

		error = regmap_update_bits(regmap, test2_addr,
				PM8058_REGULATOR_BANK_WRITE |
				PM8058_REGULATOR_BANK_MASK |
				PM8058_SMPS_ADVANCED_MODE_MASK,
				PM8058_REGULATOR_BANK_WRITE |
				PM8058_REGULATOR_BANK_SEL(7) |
				PM8058_SMPS_LEGACY_MODE);
		अगर (error)
			वापस error;

		/* Enable locally, enable pull करोwn, keep voltage the same. */
		error = regmap_update_bits(regmap, ctrl_addr,
			PM8058_REGULATOR_ENABLE_MASK |
			PM8058_REGULATOR_PULL_DOWN_MASK |
			PM8058_SMPS_LEGACY_VREF_SEL |
			PM8058_SMPS_LEGACY_VPROG_MASK,
			PM8058_REGULATOR_ENABLE | PM8058_REGULATOR_PULL_DOWN_EN
				| vref_sel | vprog);
		अगर (error)
			वापस error;
	पूर्ण

	/* Enable in master control रेजिस्टर. */
	error = regmap_update_bits(regmap, master_enable_addr,
			master_enable_bit, master_enable_bit);
	अगर (error)
		वापस error;

	/* Disable locally and enable pull करोwn. */
	वापस regmap_update_bits(regmap, ctrl_addr,
		PM8058_REGULATOR_ENABLE_MASK | PM8058_REGULATOR_PULL_DOWN_MASK,
		PM8058_REGULATOR_DISABLE | PM8058_REGULATOR_PULL_DOWN_EN);
पूर्ण

अटल पूर्णांक pm8058_disable_lकरो_locally_set_pull_करोwn(काष्ठा regmap *regmap,
		u16 ctrl_addr, u16 master_enable_addr, u8 master_enable_bit)
अणु
	पूर्णांक error;

	/* Enable LDO in master control रेजिस्टर. */
	error = regmap_update_bits(regmap, master_enable_addr,
			master_enable_bit, master_enable_bit);
	अगर (error)
		वापस error;

	/* Disable LDO in CTRL रेजिस्टर and set pull करोwn */
	वापस regmap_update_bits(regmap, ctrl_addr,
		PM8058_REGULATOR_ENABLE_MASK | PM8058_REGULATOR_PULL_DOWN_MASK,
		PM8058_REGULATOR_DISABLE | PM8058_REGULATOR_PULL_DOWN_EN);
पूर्ण

अटल पूर्णांक pm8058_pwrkey_shutकरोwn(काष्ठा pmic8xxx_pwrkey *pwrkey, bool reset)
अणु
	पूर्णांक error;
	काष्ठा regmap *regmap = pwrkey->regmap;
	u8 mask, val;

	/* When shutting करोwn, enable active pullकरोwns on important rails. */
	अगर (!reset) अणु
		/* Disable SMPS's 0,1,3 locally and set pullकरोwn enable bits. */
		pm8058_disable_smps_locally_set_pull_करोwn(regmap,
			PM8058_S0_CTRL, PM8058_S0_TEST2,
			REG_PM8058_VREG_EN_MSM, BIT(7));
		pm8058_disable_smps_locally_set_pull_करोwn(regmap,
			PM8058_S1_CTRL, PM8058_S1_TEST2,
			REG_PM8058_VREG_EN_MSM, BIT(6));
		pm8058_disable_smps_locally_set_pull_करोwn(regmap,
			PM8058_S3_CTRL, PM8058_S3_TEST2,
			REG_PM8058_VREG_EN_GRP_5_4, BIT(7) | BIT(4));
		/* Disable LDO 21 locally and set pullकरोwn enable bit. */
		pm8058_disable_lकरो_locally_set_pull_करोwn(regmap,
			PM8058_L21_CTRL, REG_PM8058_VREG_EN_GRP_5_4,
			BIT(1));
	पूर्ण

	/*
	 * Fix-up: Set regulator LDO22 to 1.225 V in high घातer mode. Leave its
	 * pull-करोwn state पूर्णांकact. This ensures a safe shutकरोwn.
	 */
	error = regmap_update_bits(regmap, PM8058_L22_CTRL, 0xbf, 0x93);
	अगर (error)
		वापस error;

	/* Enable SMPL अगर resetting is desired */
	mask = SLEEP_CTRL_SMPL_EN_RESET;
	val = 0;
	अगर (reset)
		val = mask;
	वापस regmap_update_bits(regmap, PM8058_SLEEP_CTRL, mask, val);
पूर्ण

अटल पूर्णांक pm8921_pwrkey_shutकरोwn(काष्ठा pmic8xxx_pwrkey *pwrkey, bool reset)
अणु
	काष्ठा regmap *regmap = pwrkey->regmap;
	u8 mask = SLEEP_CTRL_SMPL_EN_RESET;
	u8 val = 0;

	/* Enable SMPL अगर resetting is desired */
	अगर (reset)
		val = mask;
	वापस regmap_update_bits(regmap, PM8921_SLEEP_CTRL, mask, val);
पूर्ण

अटल पूर्णांक pmic8xxx_pwrkey_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा input_dev *pwr;
	पूर्णांक key_release_irq = platक्रमm_get_irq(pdev, 0);
	पूर्णांक key_press_irq = platक्रमm_get_irq(pdev, 1);
	पूर्णांक err;
	अचिन्हित पूर्णांक delay;
	अचिन्हित पूर्णांक pon_cntl;
	काष्ठा regmap *regmap;
	काष्ठा pmic8xxx_pwrkey *pwrkey;
	u32 kpd_delay;
	bool pull_up;

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "debounce", &kpd_delay))
		kpd_delay = 15625;

	/* Valid range of pwr key trigger delay is 1/64 sec to 2 seconds. */
	अगर (kpd_delay > USEC_PER_SEC * 2 || kpd_delay < USEC_PER_SEC / 64) अणु
		dev_err(&pdev->dev, "invalid power key trigger delay\n");
		वापस -EINVAL;
	पूर्ण

	pull_up = of_property_पढ़ो_bool(pdev->dev.of_node, "pull-up");

	regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!regmap) अणु
		dev_err(&pdev->dev, "failed to locate regmap for the device\n");
		वापस -ENODEV;
	पूर्ण

	pwrkey = devm_kzalloc(&pdev->dev, माप(*pwrkey), GFP_KERNEL);
	अगर (!pwrkey)
		वापस -ENOMEM;

	pwrkey->shutकरोwn_fn = of_device_get_match_data(&pdev->dev);
	pwrkey->regmap = regmap;
	pwrkey->key_press_irq = key_press_irq;

	pwr = devm_input_allocate_device(&pdev->dev);
	अगर (!pwr) अणु
		dev_dbg(&pdev->dev, "Can't allocate power button\n");
		वापस -ENOMEM;
	पूर्ण

	input_set_capability(pwr, EV_KEY, KEY_POWER);

	pwr->name = "pmic8xxx_pwrkey";
	pwr->phys = "pmic8xxx_pwrkey/input0";

	delay = (kpd_delay << 6) / USEC_PER_SEC;
	delay = ilog2(delay);

	err = regmap_पढ़ो(regmap, PON_CNTL_1, &pon_cntl);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed reading PON_CNTL_1 err=%d\n", err);
		वापस err;
	पूर्ण

	pon_cntl &= ~PON_CNTL_TRIG_DELAY_MASK;
	pon_cntl |= (delay & PON_CNTL_TRIG_DELAY_MASK);
	अगर (pull_up)
		pon_cntl |= PON_CNTL_PULL_UP;
	अन्यथा
		pon_cntl &= ~PON_CNTL_PULL_UP;

	err = regmap_ग_लिखो(regmap, PON_CNTL_1, pon_cntl);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed writing PON_CNTL_1 err=%d\n", err);
		वापस err;
	पूर्ण

	err = devm_request_irq(&pdev->dev, key_press_irq, pwrkey_press_irq,
			       IRQF_TRIGGER_RISING,
			       "pmic8xxx_pwrkey_press", pwr);
	अगर (err) अणु
		dev_err(&pdev->dev, "Can't get %d IRQ for pwrkey: %d\n",
			key_press_irq, err);
		वापस err;
	पूर्ण

	err = devm_request_irq(&pdev->dev, key_release_irq, pwrkey_release_irq,
			       IRQF_TRIGGER_RISING,
			       "pmic8xxx_pwrkey_release", pwr);
	अगर (err) अणु
		dev_err(&pdev->dev, "Can't get %d IRQ for pwrkey: %d\n",
			key_release_irq, err);
		वापस err;
	पूर्ण

	err = input_रेजिस्टर_device(pwr);
	अगर (err) अणु
		dev_err(&pdev->dev, "Can't register power key: %d\n", err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pwrkey);
	device_init_wakeup(&pdev->dev, 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pm8xxx_pwr_key_id_table[] = अणु
	अणु .compatible = "qcom,pm8058-pwrkey", .data = &pm8058_pwrkey_shutकरोwn पूर्ण,
	अणु .compatible = "qcom,pm8921-pwrkey", .data = &pm8921_pwrkey_shutकरोwn पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pm8xxx_pwr_key_id_table);

अटल काष्ठा platक्रमm_driver pmic8xxx_pwrkey_driver = अणु
	.probe		= pmic8xxx_pwrkey_probe,
	.shutकरोwn	= pmic8xxx_pwrkey_shutकरोwn,
	.driver		= अणु
		.name	= "pm8xxx-pwrkey",
		.pm	= &pm8xxx_pwr_key_pm_ops,
		.of_match_table = pm8xxx_pwr_key_id_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(pmic8xxx_pwrkey_driver);

MODULE_ALIAS("platform:pmic8xxx_pwrkey");
MODULE_DESCRIPTION("PMIC8XXX Power Key driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Trilok Soni <tsoni@codeaurora.org>");
