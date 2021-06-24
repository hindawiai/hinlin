<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DRV2667 haptics driver family
 *
 * Author: Dan Murphy <dmurphy@ti.com>
 *
 * Copyright: (C) 2014 Texas Instruments, Inc.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/consumer.h>

/* Contol रेजिस्टरs */
#घोषणा DRV2667_STATUS	0x00
#घोषणा DRV2667_CTRL_1	0x01
#घोषणा DRV2667_CTRL_2	0x02
/* Waveक्रमm sequencer */
#घोषणा DRV2667_WV_SEQ_0	0x03
#घोषणा DRV2667_WV_SEQ_1	0x04
#घोषणा DRV2667_WV_SEQ_2	0x05
#घोषणा DRV2667_WV_SEQ_3	0x06
#घोषणा DRV2667_WV_SEQ_4	0x07
#घोषणा DRV2667_WV_SEQ_5	0x08
#घोषणा DRV2667_WV_SEQ_6	0x09
#घोषणा DRV2667_WV_SEQ_7	0x0A
#घोषणा DRV2667_FIFO		0x0B
#घोषणा DRV2667_PAGE		0xFF
#घोषणा DRV2667_MAX_REG		DRV2667_PAGE

#घोषणा DRV2667_PAGE_0		0x00
#घोषणा DRV2667_PAGE_1		0x01
#घोषणा DRV2667_PAGE_2		0x02
#घोषणा DRV2667_PAGE_3		0x03
#घोषणा DRV2667_PAGE_4		0x04
#घोषणा DRV2667_PAGE_5		0x05
#घोषणा DRV2667_PAGE_6		0x06
#घोषणा DRV2667_PAGE_7		0x07
#घोषणा DRV2667_PAGE_8		0x08

/* RAM fields */
#घोषणा DRV2667_RAM_HDR_SZ	0x0
/* RAM Header addresses */
#घोषणा DRV2667_RAM_START_HI	0x01
#घोषणा DRV2667_RAM_START_LO	0x02
#घोषणा DRV2667_RAM_STOP_HI		0x03
#घोषणा DRV2667_RAM_STOP_LO		0x04
#घोषणा DRV2667_RAM_REPEAT_CT	0x05
/* RAM data addresses */
#घोषणा DRV2667_RAM_AMP		0x06
#घोषणा DRV2667_RAM_FREQ	0x07
#घोषणा DRV2667_RAM_DURATION	0x08
#घोषणा DRV2667_RAM_ENVELOPE	0x09

/* Control 1 Register */
#घोषणा DRV2667_25_VPP_GAIN		0x00
#घोषणा DRV2667_50_VPP_GAIN		0x01
#घोषणा DRV2667_75_VPP_GAIN		0x02
#घोषणा DRV2667_100_VPP_GAIN	0x03
#घोषणा DRV2667_DIGITAL_IN		0xfc
#घोषणा DRV2667_ANALOG_IN		(1 << 2)

/* Control 2 Register */
#घोषणा DRV2667_GO			(1 << 0)
#घोषणा DRV2667_STANDBY		(1 << 6)
#घोषणा DRV2667_DEV_RST		(1 << 7)

/* RAM Envelope settings */
#घोषणा DRV2667_NO_ENV			0x00
#घोषणा DRV2667_32_MS_ENV		0x01
#घोषणा DRV2667_64_MS_ENV		0x02
#घोषणा DRV2667_96_MS_ENV		0x03
#घोषणा DRV2667_128_MS_ENV		0x04
#घोषणा DRV2667_160_MS_ENV		0x05
#घोषणा DRV2667_192_MS_ENV		0x06
#घोषणा DRV2667_224_MS_ENV		0x07
#घोषणा DRV2667_256_MS_ENV		0x08
#घोषणा DRV2667_512_MS_ENV		0x09
#घोषणा DRV2667_768_MS_ENV		0x0a
#घोषणा DRV2667_1024_MS_ENV		0x0b
#घोषणा DRV2667_1280_MS_ENV		0x0c
#घोषणा DRV2667_1536_MS_ENV		0x0d
#घोषणा DRV2667_1792_MS_ENV		0x0e
#घोषणा DRV2667_2048_MS_ENV		0x0f

/**
 * काष्ठा drv2667_data -
 * @input_dev: Poपूर्णांकer to the input device
 * @client: Poपूर्णांकer to the I2C client
 * @regmap: Register map of the device
 * @work: Work item used to off load the enable/disable of the vibration
 * @regulator: Poपूर्णांकer to the regulator क्रम the IC
 * @page: Page number
 * @magnitude: Magnitude of the vibration event
 * @frequency: Frequency of the vibration event
**/
काष्ठा drv2667_data अणु
	काष्ठा input_dev *input_dev;
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा work_काष्ठा work;
	काष्ठा regulator *regulator;
	u32 page;
	u32 magnitude;
	u32 frequency;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष drv2667_reg_defs[] = अणु
	अणु DRV2667_STATUS, 0x02 पूर्ण,
	अणु DRV2667_CTRL_1, 0x28 पूर्ण,
	अणु DRV2667_CTRL_2, 0x40 पूर्ण,
	अणु DRV2667_WV_SEQ_0, 0x00 पूर्ण,
	अणु DRV2667_WV_SEQ_1, 0x00 पूर्ण,
	अणु DRV2667_WV_SEQ_2, 0x00 पूर्ण,
	अणु DRV2667_WV_SEQ_3, 0x00 पूर्ण,
	अणु DRV2667_WV_SEQ_4, 0x00 पूर्ण,
	अणु DRV2667_WV_SEQ_5, 0x00 पूर्ण,
	अणु DRV2667_WV_SEQ_6, 0x00 पूर्ण,
	अणु DRV2667_WV_SEQ_7, 0x00 पूर्ण,
	अणु DRV2667_FIFO, 0x00 पूर्ण,
	अणु DRV2667_PAGE, 0x00 पूर्ण,
पूर्ण;

अटल पूर्णांक drv2667_set_waveक्रमm_freq(काष्ठा drv2667_data *haptics)
अणु
	अचिन्हित पूर्णांक पढ़ो_buf;
	पूर्णांक freq;
	पूर्णांक error;

	/* Per the data sheet:
	 * Sinusoid Frequency (Hz) = 7.8125 x Frequency
	 */
	freq = (haptics->frequency * 1000) / 78125;
	अगर (freq <= 0) अणु
		dev_err(&haptics->client->dev,
			"ERROR: Frequency calculated to %i\n", freq);
		वापस -EINVAL;
	पूर्ण

	error = regmap_पढ़ो(haptics->regmap, DRV2667_PAGE, &पढ़ो_buf);
	अगर (error) अणु
		dev_err(&haptics->client->dev,
			"Failed to read the page number: %d\n", error);
		वापस -EIO;
	पूर्ण

	अगर (पढ़ो_buf == DRV2667_PAGE_0 ||
		haptics->page != पढ़ो_buf) अणु
		error = regmap_ग_लिखो(haptics->regmap,
				DRV2667_PAGE, haptics->page);
		अगर (error) अणु
			dev_err(&haptics->client->dev,
				"Failed to set the page: %d\n", error);
			वापस -EIO;
		पूर्ण
	पूर्ण

	error = regmap_ग_लिखो(haptics->regmap, DRV2667_RAM_FREQ,	freq);
	अगर (error)
		dev_err(&haptics->client->dev,
				"Failed to set the frequency: %d\n", error);

	/* Reset back to original page */
	अगर (पढ़ो_buf == DRV2667_PAGE_0 ||
		haptics->page != पढ़ो_buf) अणु
		error = regmap_ग_लिखो(haptics->regmap, DRV2667_PAGE, पढ़ो_buf);
		अगर (error) अणु
			dev_err(&haptics->client->dev,
				"Failed to set the page: %d\n", error);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस error;
पूर्ण

अटल व्योम drv2667_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drv2667_data *haptics = container_of(work, काष्ठा drv2667_data, work);
	पूर्णांक error;

	अगर (haptics->magnitude) अणु
		error = regmap_ग_लिखो(haptics->regmap,
				DRV2667_PAGE, haptics->page);
		अगर (error) अणु
			dev_err(&haptics->client->dev,
				"Failed to set the page: %d\n", error);
			वापस;
		पूर्ण

		error = regmap_ग_लिखो(haptics->regmap, DRV2667_RAM_AMP,
				haptics->magnitude);
		अगर (error) अणु
			dev_err(&haptics->client->dev,
				"Failed to set the amplitude: %d\n", error);
			वापस;
		पूर्ण

		error = regmap_ग_लिखो(haptics->regmap,
				DRV2667_PAGE, DRV2667_PAGE_0);
		अगर (error) अणु
			dev_err(&haptics->client->dev,
				"Failed to set the page: %d\n", error);
			वापस;
		पूर्ण

		error = regmap_ग_लिखो(haptics->regmap,
				DRV2667_CTRL_2, DRV2667_GO);
		अगर (error) अणु
			dev_err(&haptics->client->dev,
				"Failed to set the GO bit: %d\n", error);
		पूर्ण
	पूर्ण अन्यथा अणु
		error = regmap_update_bits(haptics->regmap, DRV2667_CTRL_2,
				DRV2667_GO, 0);
		अगर (error) अणु
			dev_err(&haptics->client->dev,
				"Failed to unset the GO bit: %d\n", error);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक drv2667_haptics_play(काष्ठा input_dev *input, व्योम *data,
				काष्ठा ff_effect *effect)
अणु
	काष्ठा drv2667_data *haptics = input_get_drvdata(input);

	अगर (effect->u.rumble.strong_magnitude > 0)
		haptics->magnitude = effect->u.rumble.strong_magnitude;
	अन्यथा अगर (effect->u.rumble.weak_magnitude > 0)
		haptics->magnitude = effect->u.rumble.weak_magnitude;
	अन्यथा
		haptics->magnitude = 0;

	schedule_work(&haptics->work);

	वापस 0;
पूर्ण

अटल व्योम drv2667_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा drv2667_data *haptics = input_get_drvdata(input);
	पूर्णांक error;

	cancel_work_sync(&haptics->work);

	error = regmap_update_bits(haptics->regmap, DRV2667_CTRL_2,
				   DRV2667_STANDBY, DRV2667_STANDBY);
	अगर (error)
		dev_err(&haptics->client->dev,
			"Failed to enter standby mode: %d\n", error);
पूर्ण

अटल स्थिर काष्ठा reg_sequence drv2667_init_regs[] = अणु
	अणु DRV2667_CTRL_2, 0 पूर्ण,
	अणु DRV2667_CTRL_1, DRV2667_25_VPP_GAIN पूर्ण,
	अणु DRV2667_WV_SEQ_0, 1 पूर्ण,
	अणु DRV2667_WV_SEQ_1, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा reg_sequence drv2667_page1_init[] = अणु
	अणु DRV2667_RAM_HDR_SZ, 0x05 पूर्ण,
	अणु DRV2667_RAM_START_HI, 0x80 पूर्ण,
	अणु DRV2667_RAM_START_LO, 0x06 पूर्ण,
	अणु DRV2667_RAM_STOP_HI, 0x00 पूर्ण,
	अणु DRV2667_RAM_STOP_LO, 0x09 पूर्ण,
	अणु DRV2667_RAM_REPEAT_CT, 0 पूर्ण,
	अणु DRV2667_RAM_DURATION, 0x05 पूर्ण,
	अणु DRV2667_RAM_ENVELOPE, DRV2667_NO_ENV पूर्ण,
	अणु DRV2667_RAM_AMP, 0x60 पूर्ण,
पूर्ण;

अटल पूर्णांक drv2667_init(काष्ठा drv2667_data *haptics)
अणु
	पूर्णांक error;

	/* Set शेष haptic frequency to 195Hz on Page 1*/
	haptics->frequency = 195;
	haptics->page = DRV2667_PAGE_1;

	error = regmap_रेजिस्टर_patch(haptics->regmap,
				      drv2667_init_regs,
				      ARRAY_SIZE(drv2667_init_regs));
	अगर (error) अणु
		dev_err(&haptics->client->dev,
			"Failed to write init registers: %d\n",
			error);
		वापस error;
	पूर्ण

	error = regmap_ग_लिखो(haptics->regmap, DRV2667_PAGE, haptics->page);
	अगर (error) अणु
		dev_err(&haptics->client->dev, "Failed to set page: %d\n",
			error);
		जाओ error_out;
	पूर्ण

	error = drv2667_set_waveक्रमm_freq(haptics);
	अगर (error)
		जाओ error_page;

	error = regmap_रेजिस्टर_patch(haptics->regmap,
				      drv2667_page1_init,
				      ARRAY_SIZE(drv2667_page1_init));
	अगर (error) अणु
		dev_err(&haptics->client->dev,
			"Failed to write page registers: %d\n",
			error);
		वापस error;
	पूर्ण

	error = regmap_ग_लिखो(haptics->regmap, DRV2667_PAGE, DRV2667_PAGE_0);
	वापस error;

error_page:
	regmap_ग_लिखो(haptics->regmap, DRV2667_PAGE, DRV2667_PAGE_0);
error_out:
	वापस error;
पूर्ण

अटल स्थिर काष्ठा regmap_config drv2667_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = DRV2667_MAX_REG,
	.reg_शेषs = drv2667_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(drv2667_reg_defs),
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल पूर्णांक drv2667_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा drv2667_data *haptics;
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

	haptics->input_dev->name = "drv2667:haptics";
	haptics->input_dev->dev.parent = client->dev.parent;
	haptics->input_dev->बंद = drv2667_बंद;
	input_set_drvdata(haptics->input_dev, haptics);
	input_set_capability(haptics->input_dev, EV_FF, FF_RUMBLE);

	error = input_ff_create_memless(haptics->input_dev, शून्य,
					drv2667_haptics_play);
	अगर (error) अणु
		dev_err(&client->dev, "input_ff_create() failed: %d\n",
			error);
		वापस error;
	पूर्ण

	INIT_WORK(&haptics->work, drv2667_worker);

	haptics->client = client;
	i2c_set_clientdata(client, haptics);

	haptics->regmap = devm_regmap_init_i2c(client, &drv2667_regmap_config);
	अगर (IS_ERR(haptics->regmap)) अणु
		error = PTR_ERR(haptics->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			error);
		वापस error;
	पूर्ण

	error = drv2667_init(haptics);
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

अटल पूर्णांक __maybe_unused drv2667_suspend(काष्ठा device *dev)
अणु
	काष्ठा drv2667_data *haptics = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	mutex_lock(&haptics->input_dev->mutex);

	अगर (input_device_enabled(haptics->input_dev)) अणु
		ret = regmap_update_bits(haptics->regmap, DRV2667_CTRL_2,
					 DRV2667_STANDBY, DRV2667_STANDBY);
		अगर (ret) अणु
			dev_err(dev, "Failed to set standby mode\n");
			regulator_disable(haptics->regulator);
			जाओ out;
		पूर्ण

		ret = regulator_disable(haptics->regulator);
		अगर (ret) अणु
			dev_err(dev, "Failed to disable regulator\n");
			regmap_update_bits(haptics->regmap,
					   DRV2667_CTRL_2,
					   DRV2667_STANDBY, 0);
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&haptics->input_dev->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused drv2667_resume(काष्ठा device *dev)
अणु
	काष्ठा drv2667_data *haptics = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	mutex_lock(&haptics->input_dev->mutex);

	अगर (input_device_enabled(haptics->input_dev)) अणु
		ret = regulator_enable(haptics->regulator);
		अगर (ret) अणु
			dev_err(dev, "Failed to enable regulator\n");
			जाओ out;
		पूर्ण

		ret = regmap_update_bits(haptics->regmap, DRV2667_CTRL_2,
					 DRV2667_STANDBY, 0);
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

अटल SIMPLE_DEV_PM_OPS(drv2667_pm_ops, drv2667_suspend, drv2667_resume);

अटल स्थिर काष्ठा i2c_device_id drv2667_id[] = अणु
	अणु "drv2667", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, drv2667_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id drv2667_of_match[] = अणु
	अणु .compatible = "ti,drv2667", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, drv2667_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver drv2667_driver = अणु
	.probe		= drv2667_probe,
	.driver		= अणु
		.name	= "drv2667-haptics",
		.of_match_table = of_match_ptr(drv2667_of_match),
		.pm	= &drv2667_pm_ops,
	पूर्ण,
	.id_table = drv2667_id,
पूर्ण;
module_i2c_driver(drv2667_driver);

MODULE_DESCRIPTION("TI DRV2667 haptics driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
