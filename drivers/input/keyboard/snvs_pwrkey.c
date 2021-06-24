<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Driver क्रम the IMX SNVS ON/OFF Power Key
// Copyright (C) 2015 Freescale Semiconductor, Inc. All Rights Reserved.

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#घोषणा SNVS_HPVIDR1_REG	0xF8
#घोषणा SNVS_LPSR_REG		0x4C	/* LP Status Register */
#घोषणा SNVS_LPCR_REG		0x38	/* LP Control Register */
#घोषणा SNVS_HPSR_REG		0x14
#घोषणा SNVS_HPSR_BTN		BIT(6)
#घोषणा SNVS_LPSR_SPO		BIT(18)
#घोषणा SNVS_LPCR_DEP_EN	BIT(5)

#घोषणा DEBOUNCE_TIME		30
#घोषणा REPEAT_INTERVAL		60

काष्ठा pwrkey_drv_data अणु
	काष्ठा regmap *snvs;
	पूर्णांक irq;
	पूर्णांक keycode;
	पूर्णांक keystate;  /* 1:pressed */
	पूर्णांक wakeup;
	काष्ठा समयr_list check_समयr;
	काष्ठा input_dev *input;
	u8 minor_rev;
पूर्ण;

अटल व्योम imx_imx_snvs_check_क्रम_events(काष्ठा समयr_list *t)
अणु
	काष्ठा pwrkey_drv_data *pdata = from_समयr(pdata, t, check_समयr);
	काष्ठा input_dev *input = pdata->input;
	u32 state;

	regmap_पढ़ो(pdata->snvs, SNVS_HPSR_REG, &state);
	state = state & SNVS_HPSR_BTN ? 1 : 0;

	/* only report new event अगर status changed */
	अगर (state ^ pdata->keystate) अणु
		pdata->keystate = state;
		input_event(input, EV_KEY, pdata->keycode, state);
		input_sync(input);
		pm_relax(pdata->input->dev.parent);
	पूर्ण

	/* repeat check अगर pressed दीर्घ */
	अगर (state) अणु
		mod_समयr(&pdata->check_समयr,
			  jअगरfies + msecs_to_jअगरfies(REPEAT_INTERVAL));
	पूर्ण
पूर्ण

अटल irqवापस_t imx_snvs_pwrkey_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा platक्रमm_device *pdev = dev_id;
	काष्ठा pwrkey_drv_data *pdata = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input = pdata->input;
	u32 lp_status;

	pm_wakeup_event(input->dev.parent, 0);

	regmap_पढ़ो(pdata->snvs, SNVS_LPSR_REG, &lp_status);
	अगर (lp_status & SNVS_LPSR_SPO) अणु
		अगर (pdata->minor_rev == 0) अणु
			/*
			 * The first generation i.MX6 SoCs only sends an
			 * पूर्णांकerrupt on button release. To mimic घातer-key
			 * usage, we'll prepend a press event.
			 */
			input_report_key(input, pdata->keycode, 1);
			input_sync(input);
			input_report_key(input, pdata->keycode, 0);
			input_sync(input);
			pm_relax(input->dev.parent);
		पूर्ण अन्यथा अणु
			mod_समयr(&pdata->check_समयr,
			          jअगरfies + msecs_to_jअगरfies(DEBOUNCE_TIME));
		पूर्ण
	पूर्ण

	/* clear SPO status */
	regmap_ग_लिखो(pdata->snvs, SNVS_LPSR_REG, SNVS_LPSR_SPO);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम imx_snvs_pwrkey_act(व्योम *pdata)
अणु
	काष्ठा pwrkey_drv_data *pd = pdata;

	del_समयr_sync(&pd->check_समयr);
पूर्ण

अटल पूर्णांक imx_snvs_pwrkey_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pwrkey_drv_data *pdata;
	काष्ठा input_dev *input;
	काष्ठा device_node *np;
	पूर्णांक error;
	u32 vid;

	/* Get SNVS रेजिस्टर Page */
	np = pdev->dev.of_node;
	अगर (!np)
		वापस -ENODEV;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	pdata->snvs = syscon_regmap_lookup_by_phandle(np, "regmap");
	अगर (IS_ERR(pdata->snvs)) अणु
		dev_err(&pdev->dev, "Can't get snvs syscon\n");
		वापस PTR_ERR(pdata->snvs);
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "linux,keycode", &pdata->keycode)) अणु
		pdata->keycode = KEY_POWER;
		dev_warn(&pdev->dev, "KEY_POWER without setting in dts\n");
	पूर्ण

	pdata->wakeup = of_property_पढ़ो_bool(np, "wakeup-source");

	pdata->irq = platक्रमm_get_irq(pdev, 0);
	अगर (pdata->irq < 0)
		वापस -EINVAL;

	regmap_पढ़ो(pdata->snvs, SNVS_HPVIDR1_REG, &vid);
	pdata->minor_rev = vid & 0xff;

	regmap_update_bits(pdata->snvs, SNVS_LPCR_REG, SNVS_LPCR_DEP_EN, SNVS_LPCR_DEP_EN);

	/* clear the unexpected पूर्णांकerrupt beक्रमe driver पढ़ोy */
	regmap_ग_लिखो(pdata->snvs, SNVS_LPSR_REG, SNVS_LPSR_SPO);

	समयr_setup(&pdata->check_समयr, imx_imx_snvs_check_क्रम_events, 0);

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input) अणु
		dev_err(&pdev->dev, "failed to allocate the input device\n");
		वापस -ENOMEM;
	पूर्ण

	input->name = pdev->name;
	input->phys = "snvs-pwrkey/input0";
	input->id.bustype = BUS_HOST;

	input_set_capability(input, EV_KEY, pdata->keycode);

	/* input customer action to cancel release समयr */
	error = devm_add_action(&pdev->dev, imx_snvs_pwrkey_act, pdata);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to register remove action\n");
		वापस error;
	पूर्ण

	pdata->input = input;
	platक्रमm_set_drvdata(pdev, pdata);

	error = devm_request_irq(&pdev->dev, pdata->irq,
			       imx_snvs_pwrkey_पूर्णांकerrupt,
			       0, pdev->name, pdev);

	अगर (error) अणु
		dev_err(&pdev->dev, "interrupt not available.\n");
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(input);
	अगर (error < 0) अणु
		dev_err(&pdev->dev, "failed to register input device\n");
		वापस error;
	पूर्ण

	device_init_wakeup(&pdev->dev, pdata->wakeup);
	error = dev_pm_set_wake_irq(&pdev->dev, pdata->irq);
	अगर (error)
		dev_err(&pdev->dev, "irq wake enable failed.\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_snvs_pwrkey_ids[] = अणु
	अणु .compatible = "fsl,sec-v4.0-pwrkey" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_snvs_pwrkey_ids);

अटल काष्ठा platक्रमm_driver imx_snvs_pwrkey_driver = अणु
	.driver = अणु
		.name = "snvs_pwrkey",
		.of_match_table = imx_snvs_pwrkey_ids,
	पूर्ण,
	.probe = imx_snvs_pwrkey_probe,
पूर्ण;
module_platक्रमm_driver(imx_snvs_pwrkey_driver);

MODULE_AUTHOR("Freescale Semiconductor");
MODULE_DESCRIPTION("i.MX snvs power key Driver");
MODULE_LICENSE("GPL");
