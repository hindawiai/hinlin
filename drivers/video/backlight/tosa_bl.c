<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  LCD / Backlight control code क्रम Sharp SL-6000x (tosa)
 *
 *  Copyright (c) 2005		Dirk Opfer
 *  Copyright (c) 2007,2008	Dmitry Baryshkov
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/mach/sharpsl_param.h>

#समावेश "tosa_bl.h"

#घोषणा COMADJ_DEFAULT	97

#घोषणा DAC_CH1		0
#घोषणा DAC_CH2		1

काष्ठा tosa_bl_data अणु
	काष्ठा i2c_client *i2c;
	काष्ठा backlight_device *bl;
	काष्ठा gpio_desc *gpio;

	पूर्णांक comadj;
पूर्ण;

अटल व्योम tosa_bl_set_backlight(काष्ठा tosa_bl_data *data, पूर्णांक brightness)
अणु
	काष्ठा spi_device *spi = dev_get_platdata(&data->i2c->dev);

	i2c_smbus_ग_लिखो_byte_data(data->i2c, DAC_CH1, data->comadj);

	/* SetBacklightDuty */
	i2c_smbus_ग_लिखो_byte_data(data->i2c, DAC_CH2, (u8)(brightness & 0xff));

	/* SetBacklightVR */
	gpiod_set_value(data->gpio, brightness & 0x100);

	tosa_bl_enable(spi, brightness);
पूर्ण

अटल पूर्णांक tosa_bl_update_status(काष्ठा backlight_device *dev)
अणु
	काष्ठा backlight_properties *props = &dev->props;
	काष्ठा tosa_bl_data *data = bl_get_data(dev);
	पूर्णांक घातer = max(props->घातer, props->fb_blank);
	पूर्णांक brightness = props->brightness;

	अगर (घातer)
		brightness = 0;

	tosa_bl_set_backlight(data, brightness);

	वापस 0;
पूर्ण

अटल पूर्णांक tosa_bl_get_brightness(काष्ठा backlight_device *dev)
अणु
	काष्ठा backlight_properties *props = &dev->props;

	वापस props->brightness;
पूर्ण

अटल स्थिर काष्ठा backlight_ops bl_ops = अणु
	.get_brightness		= tosa_bl_get_brightness,
	.update_status		= tosa_bl_update_status,
पूर्ण;

अटल पूर्णांक tosa_bl_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा backlight_properties props;
	काष्ठा tosa_bl_data *data;
	पूर्णांक ret = 0;

	data = devm_kzalloc(&client->dev, माप(काष्ठा tosa_bl_data),
				GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->comadj = sharpsl_param.comadj == -1 ? COMADJ_DEFAULT : sharpsl_param.comadj;
	data->gpio = devm_gpiod_get(&client->dev, "backlight", GPIOD_OUT_LOW);
	ret = PTR_ERR_OR_ZERO(data->gpio);
	अगर (ret) अणु
		dev_dbg(&data->bl->dev, "Unable to request gpio!\n");
		वापस ret;
	पूर्ण

	i2c_set_clientdata(client, data);
	data->i2c = client;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = 512 - 1;
	data->bl = devm_backlight_device_रेजिस्टर(&client->dev, "tosa-bl",
						&client->dev, data, &bl_ops,
						&props);
	अगर (IS_ERR(data->bl)) अणु
		ret = PTR_ERR(data->bl);
		जाओ err_reg;
	पूर्ण

	data->bl->props.brightness = 69;
	data->bl->props.घातer = FB_BLANK_UNBLANK;

	backlight_update_status(data->bl);

	वापस 0;

err_reg:
	data->bl = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक tosa_bl_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tosa_bl_data *data = i2c_get_clientdata(client);

	data->bl = शून्य;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tosa_bl_suspend(काष्ठा device *dev)
अणु
	काष्ठा tosa_bl_data *data = dev_get_drvdata(dev);

	tosa_bl_set_backlight(data, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक tosa_bl_resume(काष्ठा device *dev)
अणु
	काष्ठा tosa_bl_data *data = dev_get_drvdata(dev);

	backlight_update_status(data->bl);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tosa_bl_pm_ops, tosa_bl_suspend, tosa_bl_resume);

अटल स्थिर काष्ठा i2c_device_id tosa_bl_id[] = अणु
	अणु "tosa-bl", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tosa_bl_id);

अटल काष्ठा i2c_driver tosa_bl_driver = अणु
	.driver = अणु
		.name		= "tosa-bl",
		.pm		= &tosa_bl_pm_ops,
	पूर्ण,
	.probe		= tosa_bl_probe,
	.हटाओ		= tosa_bl_हटाओ,
	.id_table	= tosa_bl_id,
पूर्ण;

module_i2c_driver(tosa_bl_driver);

MODULE_AUTHOR("Dmitry Baryshkov");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("LCD/Backlight control for Sharp SL-6000 PDA");

