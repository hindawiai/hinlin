<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Onkey driver क्रम Actions Semi ATC260x PMICs.
 *
 * Copyright (c) 2020 Cristian Ciocaltea <cristian.ciocaltea@gmail.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/atc260x/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* <2s क्रम लघु press, >2s क्रम दीर्घ press */
#घोषणा KEY_PRESS_TIME_SEC	2

/* Driver पूर्णांकernals */
क्रमागत atc260x_onkey_reset_status अणु
	KEY_RESET_HW_DEFAULT,
	KEY_RESET_DISABLED,
	KEY_RESET_USER_SEL,
पूर्ण;

काष्ठा atc260x_onkey_params अणु
	u32 reg_पूर्णांक_ctl;
	u32 kdwn_state_bm;
	u32 दीर्घ_पूर्णांक_pnd_bm;
	u32 लघु_पूर्णांक_pnd_bm;
	u32 kdwn_पूर्णांक_pnd_bm;
	u32 press_पूर्णांक_en_bm;
	u32 kdwn_पूर्णांक_en_bm;
	u32 press_समय_bm;
	u32 reset_en_bm;
	u32 reset_समय_bm;
पूर्ण;

काष्ठा atc260x_onkey अणु
	काष्ठा atc260x *atc260x;
	स्थिर काष्ठा atc260x_onkey_params *params;
	काष्ठा input_dev *input_dev;
	काष्ठा delayed_work work;
	पूर्णांक irq;
पूर्ण;

अटल स्थिर काष्ठा atc260x_onkey_params atc2603c_onkey_params = अणु
	.reg_पूर्णांक_ctl		= ATC2603C_PMU_SYS_CTL2,
	.दीर्घ_पूर्णांक_pnd_bm	= ATC2603C_PMU_SYS_CTL2_ONOFF_LONG_PRESS,
	.लघु_पूर्णांक_pnd_bm	= ATC2603C_PMU_SYS_CTL2_ONOFF_SHORT_PRESS,
	.kdwn_पूर्णांक_pnd_bm	= ATC2603C_PMU_SYS_CTL2_ONOFF_PRESS_PD,
	.press_पूर्णांक_en_bm	= ATC2603C_PMU_SYS_CTL2_ONOFF_INT_EN,
	.kdwn_पूर्णांक_en_bm		= ATC2603C_PMU_SYS_CTL2_ONOFF_PRESS_INT_EN,
	.kdwn_state_bm		= ATC2603C_PMU_SYS_CTL2_ONOFF_PRESS,
	.press_समय_bm		= ATC2603C_PMU_SYS_CTL2_ONOFF_PRESS_TIME,
	.reset_en_bm		= ATC2603C_PMU_SYS_CTL2_ONOFF_PRESS_RESET_EN,
	.reset_समय_bm		= ATC2603C_PMU_SYS_CTL2_ONOFF_RESET_TIME_SEL,
पूर्ण;

अटल स्थिर काष्ठा atc260x_onkey_params atc2609a_onkey_params = अणु
	.reg_पूर्णांक_ctl		= ATC2609A_PMU_SYS_CTL2,
	.दीर्घ_पूर्णांक_pnd_bm	= ATC2609A_PMU_SYS_CTL2_ONOFF_LONG_PRESS,
	.लघु_पूर्णांक_pnd_bm	= ATC2609A_PMU_SYS_CTL2_ONOFF_SHORT_PRESS,
	.kdwn_पूर्णांक_pnd_bm	= ATC2609A_PMU_SYS_CTL2_ONOFF_PRESS_PD,
	.press_पूर्णांक_en_bm	= ATC2609A_PMU_SYS_CTL2_ONOFF_LSP_INT_EN,
	.kdwn_पूर्णांक_en_bm		= ATC2609A_PMU_SYS_CTL2_ONOFF_PRESS_INT_EN,
	.kdwn_state_bm		= ATC2609A_PMU_SYS_CTL2_ONOFF_PRESS,
	.press_समय_bm		= ATC2609A_PMU_SYS_CTL2_ONOFF_PRESS_TIME,
	.reset_en_bm		= ATC2609A_PMU_SYS_CTL2_ONOFF_RESET_EN,
	.reset_समय_bm		= ATC2609A_PMU_SYS_CTL2_ONOFF_RESET_TIME_SEL,
पूर्ण;

अटल पूर्णांक atc2603x_onkey_hw_init(काष्ठा atc260x_onkey *onkey,
				  क्रमागत atc260x_onkey_reset_status reset_status,
				  u32 reset_समय, u32 press_समय)
अणु
	u32 reg_bm, reg_val;

	reg_bm = onkey->params->दीर्घ_पूर्णांक_pnd_bm |
		 onkey->params->लघु_पूर्णांक_pnd_bm |
		 onkey->params->kdwn_पूर्णांक_pnd_bm |
		 onkey->params->press_पूर्णांक_en_bm |
		 onkey->params->kdwn_पूर्णांक_en_bm;

	reg_val = reg_bm | press_समय;
	reg_bm |= onkey->params->press_समय_bm;

	अगर (reset_status == KEY_RESET_DISABLED) अणु
		reg_bm |= onkey->params->reset_en_bm;
	पूर्ण अन्यथा अगर (reset_status == KEY_RESET_USER_SEL) अणु
		reg_bm |= onkey->params->reset_en_bm |
			  onkey->params->reset_समय_bm;
		reg_val |= onkey->params->reset_en_bm | reset_समय;
	पूर्ण

	वापस regmap_update_bits(onkey->atc260x->regmap,
				  onkey->params->reg_पूर्णांक_ctl, reg_bm, reg_val);
पूर्ण

अटल व्योम atc260x_onkey_query(काष्ठा atc260x_onkey *onkey)
अणु
	u32 reg_bits;
	पूर्णांक ret, key_करोwn;

	ret = regmap_पढ़ो(onkey->atc260x->regmap,
			  onkey->params->reg_पूर्णांक_ctl, &key_करोwn);
	अगर (ret) अणु
		key_करोwn = 1;
		dev_err(onkey->atc260x->dev,
			"Failed to read onkey status: %d\n", ret);
	पूर्ण अन्यथा अणु
		key_करोwn &= onkey->params->kdwn_state_bm;
	पूर्ण

	/*
	 * The hardware generates पूर्णांकerrupt only when the onkey pin is
	 * निश्चितed. Hence, the deनिश्चितion of the pin is simulated through
	 * work queue.
	 */
	अगर (key_करोwn) अणु
		schedule_delayed_work(&onkey->work, msecs_to_jअगरfies(200));
		वापस;
	पूर्ण

	/*
	 * The key-करोwn status bit is cleared when the On/Off button
	 * is released.
	 */
	input_report_key(onkey->input_dev, KEY_POWER, 0);
	input_sync(onkey->input_dev);

	reg_bits = onkey->params->दीर्घ_पूर्णांक_pnd_bm |
		   onkey->params->लघु_पूर्णांक_pnd_bm |
		   onkey->params->kdwn_पूर्णांक_pnd_bm |
		   onkey->params->press_पूर्णांक_en_bm |
		   onkey->params->kdwn_पूर्णांक_en_bm;

	/* Clear key press pending events and enable key press पूर्णांकerrupts. */
	regmap_update_bits(onkey->atc260x->regmap, onkey->params->reg_पूर्णांक_ctl,
			   reg_bits, reg_bits);
पूर्ण

अटल व्योम atc260x_onkey_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा atc260x_onkey *onkey = container_of(work, काष्ठा atc260x_onkey,
						   work.work);
	atc260x_onkey_query(onkey);
पूर्ण

अटल irqवापस_t atc260x_onkey_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा atc260x_onkey *onkey = data;
	पूर्णांक ret;

	/* Disable key press पूर्णांकerrupts. */
	ret = regmap_update_bits(onkey->atc260x->regmap,
				 onkey->params->reg_पूर्णांक_ctl,
				 onkey->params->press_पूर्णांक_en_bm |
				 onkey->params->kdwn_पूर्णांक_en_bm, 0);
	अगर (ret)
		dev_err(onkey->atc260x->dev,
			"Failed to disable interrupts: %d\n", ret);

	input_report_key(onkey->input_dev, KEY_POWER, 1);
	input_sync(onkey->input_dev);

	atc260x_onkey_query(onkey);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक atc260x_onkey_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा atc260x_onkey *onkey = input_get_drvdata(dev);

	enable_irq(onkey->irq);

	वापस 0;
पूर्ण

अटल व्योम atc260x_onkey_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा atc260x_onkey *onkey = input_get_drvdata(dev);

	disable_irq(onkey->irq);
	cancel_delayed_work_sync(&onkey->work);
पूर्ण

अटल पूर्णांक atc260x_onkey_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा atc260x *atc260x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा atc260x_onkey *onkey;
	काष्ठा input_dev *input_dev;
	क्रमागत atc260x_onkey_reset_status reset_status;
	u32 press_समय = KEY_PRESS_TIME_SEC, reset_समय = 0;
	पूर्णांक val, error;

	onkey = devm_kzalloc(&pdev->dev, माप(*onkey), GFP_KERNEL);
	अगर (!onkey)
		वापस -ENOMEM;

	error = device_property_पढ़ो_u32(pdev->dev.parent,
					 "reset-time-sec", &val);
	अगर (error) अणु
		reset_status = KEY_RESET_HW_DEFAULT;
	पूर्ण अन्यथा अगर (val) अणु
		अगर (val < 6 || val > 12) अणु
			dev_err(&pdev->dev, "reset-time-sec out of range\n");
			वापस -EINVAL;
		पूर्ण

		reset_status = KEY_RESET_USER_SEL;
		reset_समय = (val - 6) / 2;
	पूर्ण अन्यथा अणु
		reset_status = KEY_RESET_DISABLED;
		dev_dbg(&pdev->dev, "Disabled reset on long-press\n");
	पूर्ण

	चयन (atc260x->ic_type) अणु
	हाल ATC2603C:
		onkey->params = &atc2603c_onkey_params;
		press_समय = FIELD_PREP(ATC2603C_PMU_SYS_CTL2_ONOFF_PRESS_TIME,
					press_समय);
		reset_समय = FIELD_PREP(ATC2603C_PMU_SYS_CTL2_ONOFF_RESET_TIME_SEL,
					reset_समय);
		अवरोध;
	हाल ATC2609A:
		onkey->params = &atc2609a_onkey_params;
		press_समय = FIELD_PREP(ATC2609A_PMU_SYS_CTL2_ONOFF_PRESS_TIME,
					press_समय);
		reset_समय = FIELD_PREP(ATC2609A_PMU_SYS_CTL2_ONOFF_RESET_TIME_SEL,
					reset_समय);
		अवरोध;
	शेष:
		dev_err(&pdev->dev,
			"OnKey not supported for ATC260x PMIC type: %u\n",
			atc260x->ic_type);
		वापस -EINVAL;
	पूर्ण

	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!input_dev) अणु
		dev_err(&pdev->dev, "Failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	onkey->input_dev = input_dev;
	onkey->atc260x = atc260x;

	input_dev->name = "atc260x-onkey";
	input_dev->phys = "atc260x-onkey/input0";
	input_dev->खोलो = atc260x_onkey_खोलो;
	input_dev->बंद = atc260x_onkey_बंद;

	input_set_capability(input_dev, EV_KEY, KEY_POWER);
	input_set_drvdata(input_dev, onkey);

	INIT_DELAYED_WORK(&onkey->work, atc260x_onkey_work);

	onkey->irq = platक्रमm_get_irq(pdev, 0);
	अगर (onkey->irq < 0)
		वापस onkey->irq;

	error = devm_request_thपढ़ोed_irq(&pdev->dev, onkey->irq, शून्य,
					  atc260x_onkey_irq, IRQF_ONESHOT,
					  dev_name(&pdev->dev), onkey);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"Failed to register IRQ %d: %d\n", onkey->irq, error);
		वापस error;
	पूर्ण

	/* Keep IRQ disabled until atc260x_onkey_खोलो() is called. */
	disable_irq(onkey->irq);

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"Failed to register input device: %d\n", error);
		वापस error;
	पूर्ण

	error = atc2603x_onkey_hw_init(onkey, reset_status,
				       reset_समय, press_समय);
	अगर (error)
		वापस error;

	device_init_wakeup(&pdev->dev, true);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver atc260x_onkey_driver = अणु
	.probe	= atc260x_onkey_probe,
	.driver	= अणु
		.name = "atc260x-onkey",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(atc260x_onkey_driver);

MODULE_DESCRIPTION("Onkey driver for ATC260x PMICs");
MODULE_AUTHOR("Cristian Ciocaltea <cristian.ciocaltea@gmail.com>");
MODULE_LICENSE("GPL");
