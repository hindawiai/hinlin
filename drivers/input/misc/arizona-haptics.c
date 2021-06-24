<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Arizona haptics driver
 *
 * Copyright 2012 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>

#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>

#समावेश <linux/mfd/arizona/core.h>
#समावेश <linux/mfd/arizona/pdata.h>
#समावेश <linux/mfd/arizona/रेजिस्टरs.h>

काष्ठा arizona_haptics अणु
	काष्ठा arizona *arizona;
	काष्ठा input_dev *input_dev;
	काष्ठा work_काष्ठा work;

	काष्ठा mutex mutex;
	u8 पूर्णांकensity;
पूर्ण;

अटल व्योम arizona_haptics_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा arizona_haptics *haptics = container_of(work,
						       काष्ठा arizona_haptics,
						       work);
	काष्ठा arizona *arizona = haptics->arizona;
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(arizona->dapm);
	पूर्णांक ret;

	अगर (!haptics->arizona->dapm) अणु
		dev_err(arizona->dev, "No DAPM context\n");
		वापस;
	पूर्ण

	अगर (haptics->पूर्णांकensity) अणु
		ret = regmap_update_bits(arizona->regmap,
					 ARIZONA_HAPTICS_PHASE_2_INTENSITY,
					 ARIZONA_PHASE2_INTENSITY_MASK,
					 haptics->पूर्णांकensity);
		अगर (ret != 0) अणु
			dev_err(arizona->dev, "Failed to set intensity: %d\n",
				ret);
			वापस;
		पूर्ण

		/* This enable sequence will be a noop अगर alपढ़ोy enabled */
		ret = regmap_update_bits(arizona->regmap,
					 ARIZONA_HAPTICS_CONTROL_1,
					 ARIZONA_HAP_CTRL_MASK,
					 1 << ARIZONA_HAP_CTRL_SHIFT);
		अगर (ret != 0) अणु
			dev_err(arizona->dev, "Failed to start haptics: %d\n",
				ret);
			वापस;
		पूर्ण

		ret = snd_soc_component_enable_pin(component, "HAPTICS");
		अगर (ret != 0) अणु
			dev_err(arizona->dev, "Failed to start HAPTICS: %d\n",
				ret);
			वापस;
		पूर्ण

		ret = snd_soc_dapm_sync(arizona->dapm);
		अगर (ret != 0) अणु
			dev_err(arizona->dev, "Failed to sync DAPM: %d\n",
				ret);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* This disable sequence will be a noop अगर alपढ़ोy enabled */
		ret = snd_soc_component_disable_pin(component, "HAPTICS");
		अगर (ret != 0) अणु
			dev_err(arizona->dev, "Failed to disable HAPTICS: %d\n",
				ret);
			वापस;
		पूर्ण

		ret = snd_soc_dapm_sync(arizona->dapm);
		अगर (ret != 0) अणु
			dev_err(arizona->dev, "Failed to sync DAPM: %d\n",
				ret);
			वापस;
		पूर्ण

		ret = regmap_update_bits(arizona->regmap,
					 ARIZONA_HAPTICS_CONTROL_1,
					 ARIZONA_HAP_CTRL_MASK, 0);
		अगर (ret != 0) अणु
			dev_err(arizona->dev, "Failed to stop haptics: %d\n",
				ret);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक arizona_haptics_play(काष्ठा input_dev *input, व्योम *data,
				काष्ठा ff_effect *effect)
अणु
	काष्ठा arizona_haptics *haptics = input_get_drvdata(input);
	काष्ठा arizona *arizona = haptics->arizona;

	अगर (!arizona->dapm) अणु
		dev_err(arizona->dev, "No DAPM context\n");
		वापस -EBUSY;
	पूर्ण

	अगर (effect->u.rumble.strong_magnitude) अणु
		/* Scale the magnitude पूर्णांकo the range the device supports */
		अगर (arizona->pdata.hap_act) अणु
			haptics->पूर्णांकensity =
				effect->u.rumble.strong_magnitude >> 9;
			अगर (effect->direction < 0x8000)
				haptics->पूर्णांकensity += 0x7f;
		पूर्ण अन्यथा अणु
			haptics->पूर्णांकensity =
				effect->u.rumble.strong_magnitude >> 8;
		पूर्ण
	पूर्ण अन्यथा अणु
		haptics->पूर्णांकensity = 0;
	पूर्ण

	schedule_work(&haptics->work);

	वापस 0;
पूर्ण

अटल व्योम arizona_haptics_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा arizona_haptics *haptics = input_get_drvdata(input);
	काष्ठा snd_soc_component *component;

	cancel_work_sync(&haptics->work);

	अगर (haptics->arizona->dapm) अणु
		component = snd_soc_dapm_to_component(haptics->arizona->dapm);
		snd_soc_component_disable_pin(component, "HAPTICS");
	पूर्ण
पूर्ण

अटल पूर्णांक arizona_haptics_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arizona *arizona = dev_get_drvdata(pdev->dev.parent);
	काष्ठा arizona_haptics *haptics;
	पूर्णांक ret;

	haptics = devm_kzalloc(&pdev->dev, माप(*haptics), GFP_KERNEL);
	अगर (!haptics)
		वापस -ENOMEM;

	haptics->arizona = arizona;

	ret = regmap_update_bits(arizona->regmap, ARIZONA_HAPTICS_CONTROL_1,
				 ARIZONA_HAP_ACT, arizona->pdata.hap_act);
	अगर (ret != 0) अणु
		dev_err(arizona->dev, "Failed to set haptics actuator: %d\n",
			ret);
		वापस ret;
	पूर्ण

	INIT_WORK(&haptics->work, arizona_haptics_work);

	haptics->input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!haptics->input_dev) अणु
		dev_err(arizona->dev, "Failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	input_set_drvdata(haptics->input_dev, haptics);

	haptics->input_dev->name = "arizona:haptics";
	haptics->input_dev->बंद = arizona_haptics_बंद;
	__set_bit(FF_RUMBLE, haptics->input_dev->ffbit);

	ret = input_ff_create_memless(haptics->input_dev, शून्य,
				      arizona_haptics_play);
	अगर (ret < 0) अणु
		dev_err(arizona->dev, "input_ff_create_memless() failed: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = input_रेजिस्टर_device(haptics->input_dev);
	अगर (ret < 0) अणु
		dev_err(arizona->dev, "couldn't register input device: %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver arizona_haptics_driver = अणु
	.probe		= arizona_haptics_probe,
	.driver		= अणु
		.name	= "arizona-haptics",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(arizona_haptics_driver);

MODULE_ALIAS("platform:arizona-haptics");
MODULE_DESCRIPTION("Arizona haptics driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
