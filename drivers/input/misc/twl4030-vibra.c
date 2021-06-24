<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * twl4030-vibra.c - TWL4030 Vibrator driver
 *
 * Copyright (C) 2008-2010 Nokia Corporation
 *
 * Written by Henrik Saari <henrik.saari@nokia.com>
 * Updates by Felipe Balbi <felipe.balbi@nokia.com>
 * Input by Jari Vanhala <ext-jari.vanhala@nokia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mfd/twl.h>
#समावेश <linux/mfd/twl4030-audपन.स>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>

/* MODULE ID2 */
#घोषणा LEDEN		0x00

/* ForceFeedback */
#घोषणा EFFECT_सूची_180_DEG	0x8000 /* range is 0 - 0xFFFF */

काष्ठा vibra_info अणु
	काष्ठा device		*dev;
	काष्ठा input_dev	*input_dev;

	काष्ठा work_काष्ठा	play_work;

	bool			enabled;
	पूर्णांक			speed;
	पूर्णांक			direction;

	bool			coexist;
पूर्ण;

अटल व्योम vibra_disable_leds(व्योम)
अणु
	u8 reg;

	/* Disable LEDA & LEDB, cannot be used with vibra (PWM) */
	twl_i2c_पढ़ो_u8(TWL4030_MODULE_LED, &reg, LEDEN);
	reg &= ~0x03;
	twl_i2c_ग_लिखो_u8(TWL4030_MODULE_LED, LEDEN, reg);
पूर्ण

/* Powers H-Bridge and enables audio clk */
अटल व्योम vibra_enable(काष्ठा vibra_info *info)
अणु
	u8 reg;

	twl4030_audio_enable_resource(TWL4030_AUDIO_RES_POWER);

	/* turn H-Bridge on */
	twl_i2c_पढ़ो_u8(TWL4030_MODULE_AUDIO_VOICE,
			&reg, TWL4030_REG_VIBRA_CTL);
	twl_i2c_ग_लिखो_u8(TWL4030_MODULE_AUDIO_VOICE,
			 (reg | TWL4030_VIBRA_EN), TWL4030_REG_VIBRA_CTL);

	twl4030_audio_enable_resource(TWL4030_AUDIO_RES_APLL);

	info->enabled = true;
पूर्ण

अटल व्योम vibra_disable(काष्ठा vibra_info *info)
अणु
	u8 reg;

	/* Power करोwn H-Bridge */
	twl_i2c_पढ़ो_u8(TWL4030_MODULE_AUDIO_VOICE,
			&reg, TWL4030_REG_VIBRA_CTL);
	twl_i2c_ग_लिखो_u8(TWL4030_MODULE_AUDIO_VOICE,
			 (reg & ~TWL4030_VIBRA_EN), TWL4030_REG_VIBRA_CTL);

	twl4030_audio_disable_resource(TWL4030_AUDIO_RES_APLL);
	twl4030_audio_disable_resource(TWL4030_AUDIO_RES_POWER);

	info->enabled = false;
पूर्ण

अटल व्योम vibra_play_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vibra_info *info = container_of(work,
			काष्ठा vibra_info, play_work);
	पूर्णांक dir;
	पूर्णांक pwm;
	u8 reg;

	dir = info->direction;
	pwm = info->speed;

	twl_i2c_पढ़ो_u8(TWL4030_MODULE_AUDIO_VOICE,
			&reg, TWL4030_REG_VIBRA_CTL);
	अगर (pwm && (!info->coexist || !(reg & TWL4030_VIBRA_SEL))) अणु

		अगर (!info->enabled)
			vibra_enable(info);

		/* set vibra rotation direction */
		twl_i2c_पढ़ो_u8(TWL4030_MODULE_AUDIO_VOICE,
				&reg, TWL4030_REG_VIBRA_CTL);
		reg = (dir) ? (reg | TWL4030_VIBRA_सूची) :
			(reg & ~TWL4030_VIBRA_सूची);
		twl_i2c_ग_लिखो_u8(TWL4030_MODULE_AUDIO_VOICE,
				 reg, TWL4030_REG_VIBRA_CTL);

		/* set PWM, 1 = max, 255 = min */
		twl_i2c_ग_लिखो_u8(TWL4030_MODULE_AUDIO_VOICE,
				 256 - pwm, TWL4030_REG_VIBRA_SET);
	पूर्ण अन्यथा अणु
		अगर (info->enabled)
			vibra_disable(info);
	पूर्ण
पूर्ण

/*** Input/ForceFeedback ***/

अटल पूर्णांक vibra_play(काष्ठा input_dev *input, व्योम *data,
		      काष्ठा ff_effect *effect)
अणु
	काष्ठा vibra_info *info = input_get_drvdata(input);

	info->speed = effect->u.rumble.strong_magnitude >> 8;
	अगर (!info->speed)
		info->speed = effect->u.rumble.weak_magnitude >> 9;
	info->direction = effect->direction < EFFECT_सूची_180_DEG ? 0 : 1;
	schedule_work(&info->play_work);
	वापस 0;
पूर्ण

अटल व्योम twl4030_vibra_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा vibra_info *info = input_get_drvdata(input);

	cancel_work_sync(&info->play_work);

	अगर (info->enabled)
		vibra_disable(info);
पूर्ण

/*** Module ***/
अटल पूर्णांक __maybe_unused twl4030_vibra_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा vibra_info *info = platक्रमm_get_drvdata(pdev);

	अगर (info->enabled)
		vibra_disable(info);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused twl4030_vibra_resume(काष्ठा device *dev)
अणु
	vibra_disable_leds();
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(twl4030_vibra_pm_ops,
			 twl4030_vibra_suspend, twl4030_vibra_resume);

अटल bool twl4030_vibra_check_coexist(काष्ठा twl4030_vibra_data *pdata,
			      काष्ठा device_node *parent)
अणु
	काष्ठा device_node *node;

	अगर (pdata && pdata->coexist)
		वापस true;

	node = of_get_child_by_name(parent, "codec");
	अगर (node) अणु
		of_node_put(node);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक twl4030_vibra_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl4030_vibra_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device_node *twl4030_core_node = pdev->dev.parent->of_node;
	काष्ठा vibra_info *info;
	पूर्णांक ret;

	अगर (!pdata && !twl4030_core_node) अणु
		dev_dbg(&pdev->dev, "platform_data not available\n");
		वापस -EINVAL;
	पूर्ण

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = &pdev->dev;
	info->coexist = twl4030_vibra_check_coexist(pdata, twl4030_core_node);
	INIT_WORK(&info->play_work, vibra_play_work);

	info->input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (info->input_dev == शून्य) अणु
		dev_err(&pdev->dev, "couldn't allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	input_set_drvdata(info->input_dev, info);

	info->input_dev->name = "twl4030:vibrator";
	info->input_dev->id.version = 1;
	info->input_dev->बंद = twl4030_vibra_बंद;
	__set_bit(FF_RUMBLE, info->input_dev->ffbit);

	ret = input_ff_create_memless(info->input_dev, शून्य, vibra_play);
	अगर (ret < 0) अणु
		dev_dbg(&pdev->dev, "couldn't register vibrator to FF\n");
		वापस ret;
	पूर्ण

	ret = input_रेजिस्टर_device(info->input_dev);
	अगर (ret < 0) अणु
		dev_dbg(&pdev->dev, "couldn't register input device\n");
		जाओ err_अगरf;
	पूर्ण

	vibra_disable_leds();

	platक्रमm_set_drvdata(pdev, info);
	वापस 0;

err_अगरf:
	input_ff_destroy(info->input_dev);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver twl4030_vibra_driver = अणु
	.probe		= twl4030_vibra_probe,
	.driver		= अणु
		.name	= "twl4030-vibra",
		.pm	= &twl4030_vibra_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(twl4030_vibra_driver);

MODULE_ALIAS("platform:twl4030-vibra");
MODULE_DESCRIPTION("TWL4030 Vibra driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nokia Corporation");
