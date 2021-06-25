<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DRV2665 haptics driver family
 *
 * Author: Dan Murphy <dmurphy@ti.com>
 *
 * Copyright: (C) 2015 Texas Instruments, Inc.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/consumer.h>

/* Contol रेजिस्टरs */
#घोषणा DRV2665_STATUS	0x00
#घोषणा DRV2665_CTRL_1	0x01
#घोषणा DRV2665_CTRL_2	0x02
#घोषणा DRV2665_FIFO	0x0b

/* Status Register */
#घोषणा DRV2665_FIFO_FULL		BIT(0)
#घोषणा DRV2665_FIFO_EMPTY		BIT(1)

/* Control 1 Register */
#घोषणा DRV2665_25_VPP_GAIN		0x00
#घोषणा DRV2665_50_VPP_GAIN		0x01
#घोषणा DRV2665_75_VPP_GAIN		0x02
#घोषणा DRV2665_100_VPP_GAIN		0x03
#घोषणा DRV2665_DIGITAL_IN		0xfc
#घोषणा DRV2665_ANALOG_IN		BIT(2)

/* Control 2 Register */
#घोषणा DRV2665_BOOST_EN		BIT(1)
#घोषणा DRV2665_STANDBY			BIT(6)
#घोषणा DRV2665_DEV_RST			BIT(7)
#घोषणा DRV2665_5_MS_IDLE_TOUT		0x00
#घोषणा DRV2665_10_MS_IDLE_TOUT		0x04
#घोषणा DRV2665_15_MS_IDLE_TOUT		0x08
#घोषणा DRV2665_20_MS_IDLE_TOUT		0x0c

/**
 * काष्ठा drv2665_data -
 * @input_dev: Poपूर्णांकer to the input device
 * @client: Poपूर्णांकer to the I2C client
 * @regmap: Register map of the device
 * @work: Work item used to off load the enable/disable of the vibration
 * @regulator: Poपूर्णांकer to the regulator क्रम the IC
 */
काष्ठा drv2665_data अणु
	काष्ठा input_dev *input_dev;
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा work_काष्ठा work;
	काष्ठा regulator *regulator;
पूर्ण;

/* 8kHz Sine wave to stream to the FIFO */
अटल स्थिर u8 drv2665_sine_wave_क्रमm[] = अणु
	0x00, 0x10, 0x20, 0x2e, 0x3c, 0x48, 0x53, 0x5b, 0x61, 0x65, 0x66,
	0x65, 0x61, 0x5b, 0x53, 0x48, 0x3c, 0x2e, 0x20, 0x10,
	0x00, 0xf0, 0xe0, 0xd2, 0xc4, 0xb8, 0xad, 0xa5, 0x9f, 0x9b, 0x9a,
	0x9b, 0x9f, 0xa5, 0xad, 0xb8, 0xc4, 0xd2, 0xe0, 0xf0, 0x00,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष drv2665_reg_defs[] = अणु
	अणु DRV2665_STATUS, 0x02 पूर्ण,
	अणु DRV2665_CTRL_1, 0x28 पूर्ण,
	अणु DRV2665_CTRL_2, 0x40 पूर्ण,
	अणु DRV2665_FIFO, 0x00 पूर्ण,
पूर्ण;

अटल व्योम drv2665_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drv2665_data *haptics =
				container_of(work, काष्ठा drv2665_data, work);
	अचिन्हित पूर्णांक पढ़ो_buf;
	पूर्णांक error;

	error = regmap_पढ़ो(haptics->regmap, DRV2665_STATUS, &पढ़ो_buf);
	अगर (error) अणु
		dev_err(&haptics->client->dev,
			"Failed to read status: %d\n", error);
		वापस;
	पूर्ण

	अगर (पढ़ो_buf & DRV2665_FIFO_EMPTY) अणु
		error = regmap_bulk_ग_लिखो(haptics->regmap,
					  DRV2665_FIFO,
					  drv2665_sine_wave_क्रमm,
					  ARRAY_SIZE(drv2665_sine_wave_क्रमm));
		अगर (error) अणु
			dev_err(&haptics->client->dev,
				"Failed to write FIFO: %d\n", error);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक drv2665_haptics_play(काष्ठा input_dev *input, व्योम *data,
				काष्ठा ff_effect *effect)
अणु
	काष्ठा drv2665_data *haptics = input_get_drvdata(input);

	schedule_work(&haptics->work);

	वापस 0;
पूर्ण

अटल व्योम drv2665_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा drv2665_data *haptics = input_get_drvdata(input);
	पूर्णांक error;

	cancel_work_sync(&haptics->work);

	error = regmap_update_bits(haptics->regmap, DRV2665_CTRL_2,
				   DRV2665_STANDBY, DRV2665_STANDBY);
	अगर (error)
		dev_err(&haptics->client->dev,
			"Failed to enter standby mode: %d\n", error);
पूर्ण

अटल स्थिर काष्ठा reg_sequence drv2665_init_regs[] = अणु
	अणु DRV2665_CTRL_2, 0 | DRV2665_10_MS_IDLE_TOUT पूर्ण,
	अणु DRV2665_CTRL_1, DRV2665_25_VPP_GAIN पूर्ण,
पूर्ण;

अटल पूर्णांक drv2665_init(काष्ठा drv2665_data *haptics)
अणु
	पूर्णांक error;

	error = regmap_रेजिस्टर_patch(haptics->regmap,
				      drv2665_init_regs,
				      ARRAY_SIZE(drv2665_init_regs));
	अगर (error) अणु
		dev_err(&haptics->client->dev,
			"Failed to write init registers: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config drv2665_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = DRV2665_FIFO,
	.reg_शेषs = drv2665_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(drv2665_reg_defs),
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल पूर्णांक drv2665_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा drv2665_data *haptics;
	पूर्णांक error;

	haptics = devm_kzalloc(&client->dev, माप(*haptics), GFP_KERNEL);
	अगर (!haptics)
		वापस -ENOMEM;

	haptics->regulator = devm_regulator_get(&client->dev, "vbat");
	अगर (IS_ERR(haptics->regulator)) अणु
		error = PTR_ERR(haptics->regulator);
		dev_err(&client->dev,
			"unable to get regulator, error: %d\n", error);
		वापस error;
	पूर्ण

	haptics->input_dev = devm_input_allocate_device(&client->dev);
	अगर (!haptics->input_dev) अणु
		dev_err(&client->dev, "Failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	haptics->input_dev->name = "drv2665:haptics";
	haptics->input_dev->dev.parent = client->dev.parent;
	haptics->input_dev->बंद = drv2665_बंद;
	input_set_drvdata(haptics->input_dev, haptics);
	input_set_capability(haptics->input_dev, EV_FF, FF_RUMBLE);

	error = input_ff_create_memless(haptics->input_dev, शून्य,
					drv2665_haptics_play);
	अगर (error) अणु
		dev_err(&client->dev, "input_ff_create() failed: %d\n",
			error);
		वापस error;
	पूर्ण

	INIT_WORK(&haptics->work, drv2665_worker);

	haptics->client = client;
	i2c_set_clientdata(client, haptics);

	haptics->regmap = devm_regmap_init_i2c(client, &drv2665_regmap_config);
	अगर (IS_ERR(haptics->regmap)) अणु
		error = PTR_ERR(haptics->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			error);
		वापस error;
	पूर्ण

	error = drv2665_init(haptics);
	अगर (error) अणु
		dev_err(&client->dev, "Device init failed: %d\n", error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(haptics->input_dev);
	अगर (error) अणु
		dev_err(&client->dev, "couldn't register input device: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused drv2665_suspend(काष्ठा device *dev)
अणु
	काष्ठा drv2665_data *haptics = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	mutex_lock(&haptics->input_dev->mutex);

	अगर (input_device_enabled(haptics->input_dev)) अणु
		ret = regmap_update_bits(haptics->regmap, DRV2665_CTRL_2,
					 DRV2665_STANDBY, DRV2665_STANDBY);
		अगर (ret) अणु
			dev_err(dev, "Failed to set standby mode\n");
			regulator_disable(haptics->regulator);
			जाओ out;
		पूर्ण

		ret = regulator_disable(haptics->regulator);
		अगर (ret) अणु
			dev_err(dev, "Failed to disable regulator\n");
			regmap_update_bits(haptics->regmap,
					   DRV2665_CTRL_2,
					   DRV2665_STANDBY, 0);
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&haptics->input_dev->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused drv2665_resume(काष्ठा device *dev)
अणु
	काष्ठा drv2665_data *haptics = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	mutex_lock(&haptics->input_dev->mutex);

	अगर (input_device_enabled(haptics->input_dev)) अणु
		ret = regulator_enable(haptics->regulator);
		अगर (ret) अणु
			dev_err(dev, "Failed to enable regulator\n");
			जाओ out;
		पूर्ण

		ret = regmap_update_bits(haptics->regmap, DRV2665_CTRL_2,
					 DRV2665_STANDBY, 0);
		अगर (ret) अणु
			dev_err(dev, "Failed to unset standby mode\n");
			regulator_disable(haptics->regulator);
			जाओ out;
		पूर्ण

	पूर्ण

out:
	mutex_unlock(&haptics->input_dev->mutex);
	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(drv2665_pm_ops, drv2665_suspend, drv2665_resume);

अटल स्थिर काष्ठा i2c_device_id drv2665_id[] = अणु
	अणु "drv2665", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, drv2665_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id drv2665_of_match[] = अणु
	अणु .compatible = "ti,drv2665", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, drv2665_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver drv2665_driver = अणु
	.probe		= drv2665_probe,
	.driver		= अणु
		.name	= "drv2665-haptics",
		.of_match_table = of_match_ptr(drv2665_of_match),
		.pm	= &drv2665_pm_ops,
	पूर्ण,
	.id_table = drv2665_id,
पूर्ण;
module_i2c_driver(drv2665_driver);

MODULE_DESCRIPTION("TI DRV2665 haptics driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
