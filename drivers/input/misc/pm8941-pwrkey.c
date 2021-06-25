<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010-2011, Code Aurora Forum. All rights reserved.
 * Copyright (c) 2014, Sony Mobile Communications Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>

#घोषणा PON_REV2			0x01

#घोषणा PON_RT_STS			0x10
#घोषणा  PON_KPDPWR_N_SET		BIT(0)
#घोषणा  PON_RESIN_N_SET		BIT(1)

#घोषणा PON_PS_HOLD_RST_CTL		0x5a
#घोषणा PON_PS_HOLD_RST_CTL2		0x5b
#घोषणा  PON_PS_HOLD_ENABLE		BIT(7)
#घोषणा  PON_PS_HOLD_TYPE_MASK		0x0f
#घोषणा  PON_PS_HOLD_TYPE_SHUTDOWN	4
#घोषणा  PON_PS_HOLD_TYPE_HARD_RESET	7

#घोषणा PON_PULL_CTL			0x70
#घोषणा  PON_KPDPWR_PULL_UP		BIT(1)
#घोषणा  PON_RESIN_PULL_UP		BIT(0)

#घोषणा PON_DBC_CTL			0x71
#घोषणा  PON_DBC_DELAY_MASK		0x7

काष्ठा pm8941_data अणु
	अचिन्हित पूर्णांक pull_up_bit;
	अचिन्हित पूर्णांक status_bit;
पूर्ण;

काष्ठा pm8941_pwrkey अणु
	काष्ठा device *dev;
	पूर्णांक irq;
	u32 baseaddr;
	काष्ठा regmap *regmap;
	काष्ठा input_dev *input;

	अचिन्हित पूर्णांक revision;
	काष्ठा notअगरier_block reboot_notअगरier;

	u32 code;
	स्थिर काष्ठा pm8941_data *data;
पूर्ण;

अटल पूर्णांक pm8941_reboot_notअगरy(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ code, व्योम *unused)
अणु
	काष्ठा pm8941_pwrkey *pwrkey = container_of(nb, काष्ठा pm8941_pwrkey,
						    reboot_notअगरier);
	अचिन्हित पूर्णांक enable_reg;
	अचिन्हित पूर्णांक reset_type;
	पूर्णांक error;

	/* PMICs with revision 0 have the enable bit in same रेजिस्टर as ctrl */
	अगर (pwrkey->revision == 0)
		enable_reg = PON_PS_HOLD_RST_CTL;
	अन्यथा
		enable_reg = PON_PS_HOLD_RST_CTL2;

	error = regmap_update_bits(pwrkey->regmap,
				   pwrkey->baseaddr + enable_reg,
				   PON_PS_HOLD_ENABLE,
				   0);
	अगर (error)
		dev_err(pwrkey->dev,
			"unable to clear ps hold reset enable: %d\n",
			error);

	/*
	 * Updates of PON_PS_HOLD_ENABLE requires 3 sleep cycles between
	 * ग_लिखोs.
	 */
	usleep_range(100, 1000);

	चयन (code) अणु
	हाल SYS_HALT:
	हाल SYS_POWER_OFF:
		reset_type = PON_PS_HOLD_TYPE_SHUTDOWN;
		अवरोध;
	हाल SYS_RESTART:
	शेष:
		reset_type = PON_PS_HOLD_TYPE_HARD_RESET;
		अवरोध;
	पूर्ण

	error = regmap_update_bits(pwrkey->regmap,
				   pwrkey->baseaddr + PON_PS_HOLD_RST_CTL,
				   PON_PS_HOLD_TYPE_MASK,
				   reset_type);
	अगर (error)
		dev_err(pwrkey->dev, "unable to set ps hold reset type: %d\n",
			error);

	error = regmap_update_bits(pwrkey->regmap,
				   pwrkey->baseaddr + enable_reg,
				   PON_PS_HOLD_ENABLE,
				   PON_PS_HOLD_ENABLE);
	अगर (error)
		dev_err(pwrkey->dev, "unable to re-set enable: %d\n", error);

	वापस NOTIFY_DONE;
पूर्ण

अटल irqवापस_t pm8941_pwrkey_irq(पूर्णांक irq, व्योम *_data)
अणु
	काष्ठा pm8941_pwrkey *pwrkey = _data;
	अचिन्हित पूर्णांक sts;
	पूर्णांक error;

	error = regmap_पढ़ो(pwrkey->regmap,
			    pwrkey->baseaddr + PON_RT_STS, &sts);
	अगर (error)
		वापस IRQ_HANDLED;

	input_report_key(pwrkey->input, pwrkey->code,
			 sts & pwrkey->data->status_bit);
	input_sync(pwrkey->input);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __maybe_unused pm8941_pwrkey_suspend(काष्ठा device *dev)
अणु
	काष्ठा pm8941_pwrkey *pwrkey = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(pwrkey->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pm8941_pwrkey_resume(काष्ठा device *dev)
अणु
	काष्ठा pm8941_pwrkey *pwrkey = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(pwrkey->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pm8941_pwr_key_pm_ops,
			 pm8941_pwrkey_suspend, pm8941_pwrkey_resume);

अटल पूर्णांक pm8941_pwrkey_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm8941_pwrkey *pwrkey;
	bool pull_up;
	काष्ठा device *parent;
	u32 req_delay;
	पूर्णांक error;

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "debounce", &req_delay))
		req_delay = 15625;

	अगर (req_delay > 2000000 || req_delay == 0) अणु
		dev_err(&pdev->dev, "invalid debounce time: %u\n", req_delay);
		वापस -EINVAL;
	पूर्ण

	pull_up = of_property_पढ़ो_bool(pdev->dev.of_node, "bias-pull-up");

	pwrkey = devm_kzalloc(&pdev->dev, माप(*pwrkey), GFP_KERNEL);
	अगर (!pwrkey)
		वापस -ENOMEM;

	pwrkey->dev = &pdev->dev;
	pwrkey->data = of_device_get_match_data(&pdev->dev);

	parent = pdev->dev.parent;
	pwrkey->regmap = dev_get_regmap(parent, शून्य);
	अगर (!pwrkey->regmap) अणु
		/*
		 * We failed to get regmap क्रम parent. Let's see अगर we are
		 * a child of pon node and पढ़ो regmap and reg from its
		 * parent.
		 */
		pwrkey->regmap = dev_get_regmap(parent->parent, शून्य);
		अगर (!pwrkey->regmap) अणु
			dev_err(&pdev->dev, "failed to locate regmap\n");
			वापस -ENODEV;
		पूर्ण

		error = of_property_पढ़ो_u32(parent->of_node,
					     "reg", &pwrkey->baseaddr);
	पूर्ण अन्यथा अणु
		error = of_property_पढ़ो_u32(pdev->dev.of_node, "reg",
					     &pwrkey->baseaddr);
	पूर्ण
	अगर (error)
		वापस error;

	pwrkey->irq = platक्रमm_get_irq(pdev, 0);
	अगर (pwrkey->irq < 0)
		वापस pwrkey->irq;

	error = regmap_पढ़ो(pwrkey->regmap, pwrkey->baseaddr + PON_REV2,
			    &pwrkey->revision);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to set debounce: %d\n", error);
		वापस error;
	पूर्ण

	error = of_property_पढ़ो_u32(pdev->dev.of_node, "linux,code",
				     &pwrkey->code);
	अगर (error) अणु
		dev_dbg(&pdev->dev,
			"no linux,code assuming power (%d)\n", error);
		pwrkey->code = KEY_POWER;
	पूर्ण

	pwrkey->input = devm_input_allocate_device(&pdev->dev);
	अगर (!pwrkey->input) अणु
		dev_dbg(&pdev->dev, "unable to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	input_set_capability(pwrkey->input, EV_KEY, pwrkey->code);

	pwrkey->input->name = "pm8941_pwrkey";
	pwrkey->input->phys = "pm8941_pwrkey/input0";

	req_delay = (req_delay << 6) / USEC_PER_SEC;
	req_delay = ilog2(req_delay);

	error = regmap_update_bits(pwrkey->regmap,
				   pwrkey->baseaddr + PON_DBC_CTL,
				   PON_DBC_DELAY_MASK,
				   req_delay);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to set debounce: %d\n", error);
		वापस error;
	पूर्ण

	error = regmap_update_bits(pwrkey->regmap,
				   pwrkey->baseaddr + PON_PULL_CTL,
				   pwrkey->data->pull_up_bit,
				   pull_up ? pwrkey->data->pull_up_bit : 0);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to set pull: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(&pdev->dev, pwrkey->irq,
					  शून्य, pm8941_pwrkey_irq,
					  IRQF_ONESHOT,
					  "pm8941_pwrkey", pwrkey);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed requesting IRQ: %d\n", error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(pwrkey->input);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to register input device: %d\n",
			error);
		वापस error;
	पूर्ण

	pwrkey->reboot_notअगरier.notअगरier_call = pm8941_reboot_notअगरy,
	error = रेजिस्टर_reboot_notअगरier(&pwrkey->reboot_notअगरier);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to register reboot notifier: %d\n",
			error);
		वापस error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pwrkey);
	device_init_wakeup(&pdev->dev, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक pm8941_pwrkey_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm8941_pwrkey *pwrkey = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_reboot_notअगरier(&pwrkey->reboot_notअगरier);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pm8941_data pwrkey_data = अणु
	.pull_up_bit = PON_KPDPWR_PULL_UP,
	.status_bit = PON_KPDPWR_N_SET,
पूर्ण;

अटल स्थिर काष्ठा pm8941_data resin_data = अणु
	.pull_up_bit = PON_RESIN_PULL_UP,
	.status_bit = PON_RESIN_N_SET,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pm8941_pwr_key_id_table[] = अणु
	अणु .compatible = "qcom,pm8941-pwrkey", .data = &pwrkey_data पूर्ण,
	अणु .compatible = "qcom,pm8941-resin", .data = &resin_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pm8941_pwr_key_id_table);

अटल काष्ठा platक्रमm_driver pm8941_pwrkey_driver = अणु
	.probe = pm8941_pwrkey_probe,
	.हटाओ = pm8941_pwrkey_हटाओ,
	.driver = अणु
		.name = "pm8941-pwrkey",
		.pm = &pm8941_pwr_key_pm_ops,
		.of_match_table = of_match_ptr(pm8941_pwr_key_id_table),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(pm8941_pwrkey_driver);

MODULE_DESCRIPTION("PM8941 Power Key driver");
MODULE_LICENSE("GPL v2");
