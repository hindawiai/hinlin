<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ROHM Semiconductor BD6107 LED Driver
 *
 * Copyright (C) 2013 Ideas on board SPRL
 *
 * Contact: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/fb.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/bd6107.h>
#समावेश <linux/slab.h>

#घोषणा BD6107_PSCNT1				0x00
#घोषणा BD6107_PSCNT1_PSCNTREG2			(1 << 2)
#घोषणा BD6107_PSCNT1_PSCNTREG1			(1 << 0)
#घोषणा BD6107_REGVSET				0x02
#घोषणा BD6107_REGVSET_REG1VSET_2_85V		(1 << 2)
#घोषणा BD6107_REGVSET_REG1VSET_2_80V		(0 << 2)
#घोषणा BD6107_LEDCNT1				0x03
#घोषणा BD6107_LEDCNT1_LEDONOFF2		(1 << 1)
#घोषणा BD6107_LEDCNT1_LEDONOFF1		(1 << 0)
#घोषणा BD6107_PORTSEL				0x04
#घोषणा BD6107_PORTSEL_LEDM(n)			(1 << (n))
#घोषणा BD6107_RGB1CNT1				0x05
#घोषणा BD6107_RGB1CNT2				0x06
#घोषणा BD6107_RGB1CNT3				0x07
#घोषणा BD6107_RGB1CNT4				0x08
#घोषणा BD6107_RGB1CNT5				0x09
#घोषणा BD6107_RGB1FLM				0x0a
#घोषणा BD6107_RGB2CNT1				0x0b
#घोषणा BD6107_RGB2CNT2				0x0c
#घोषणा BD6107_RGB2CNT3				0x0d
#घोषणा BD6107_RGB2CNT4				0x0e
#घोषणा BD6107_RGB2CNT5				0x0f
#घोषणा BD6107_RGB2FLM				0x10
#घोषणा BD6107_PSCONT3				0x11
#घोषणा BD6107_SMMONCNT				0x12
#घोषणा BD6107_DCDCCNT				0x13
#घोषणा BD6107_IOSEL				0x14
#घोषणा BD6107_OUT1				0x15
#घोषणा BD6107_OUT2				0x16
#घोषणा BD6107_MASK1				0x17
#घोषणा BD6107_MASK2				0x18
#घोषणा BD6107_FACTOR1				0x19
#घोषणा BD6107_FACTOR2				0x1a
#घोषणा BD6107_CLRFACT1				0x1b
#घोषणा BD6107_CLRFACT2				0x1c
#घोषणा BD6107_STATE1				0x1d
#घोषणा BD6107_LSIVER				0x1e
#घोषणा BD6107_GRPSEL				0x1f
#घोषणा BD6107_LEDCNT2				0x20
#घोषणा BD6107_LEDCNT3				0x21
#घोषणा BD6107_MCURRENT				0x22
#घोषणा BD6107_MAINCNT1				0x23
#घोषणा BD6107_MAINCNT2				0x24
#घोषणा BD6107_SLOPECNT				0x25
#घोषणा BD6107_MSLOPE				0x26
#घोषणा BD6107_RGBSLOPE				0x27
#घोषणा BD6107_TEST				0x29
#घोषणा BD6107_SFTRST				0x2a
#घोषणा BD6107_SFTRSTGD				0x2b

काष्ठा bd6107 अणु
	काष्ठा i2c_client *client;
	काष्ठा backlight_device *backlight;
	काष्ठा bd6107_platक्रमm_data *pdata;
	काष्ठा gpio_desc *reset;
पूर्ण;

अटल पूर्णांक bd6107_ग_लिखो(काष्ठा bd6107 *bd, u8 reg, u8 data)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(bd->client, reg, data);
पूर्ण

अटल पूर्णांक bd6107_backlight_update_status(काष्ठा backlight_device *backlight)
अणु
	काष्ठा bd6107 *bd = bl_get_data(backlight);
	पूर्णांक brightness = backlight_get_brightness(backlight);

	अगर (brightness) अणु
		bd6107_ग_लिखो(bd, BD6107_PORTSEL, BD6107_PORTSEL_LEDM(2) |
			     BD6107_PORTSEL_LEDM(1) | BD6107_PORTSEL_LEDM(0));
		bd6107_ग_लिखो(bd, BD6107_MAINCNT1, brightness);
		bd6107_ग_लिखो(bd, BD6107_LEDCNT1, BD6107_LEDCNT1_LEDONOFF1);
	पूर्ण अन्यथा अणु
		/* Assert the reset line (gpiolib will handle active low) */
		gpiod_set_value(bd->reset, 1);
		msleep(24);
		gpiod_set_value(bd->reset, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bd6107_backlight_check_fb(काष्ठा backlight_device *backlight,
				       काष्ठा fb_info *info)
अणु
	काष्ठा bd6107 *bd = bl_get_data(backlight);

	वापस bd->pdata->fbdev == शून्य || bd->pdata->fbdev == info->dev;
पूर्ण

अटल स्थिर काष्ठा backlight_ops bd6107_backlight_ops = अणु
	.options	= BL_CORE_SUSPENDRESUME,
	.update_status	= bd6107_backlight_update_status,
	.check_fb	= bd6107_backlight_check_fb,
पूर्ण;

अटल पूर्णांक bd6107_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा bd6107_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा backlight_device *backlight;
	काष्ठा backlight_properties props;
	काष्ठा bd6107 *bd;
	पूर्णांक ret;

	अगर (pdata == शून्य) अणु
		dev_err(&client->dev, "No platform data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_warn(&client->dev,
			 "I2C adapter doesn't support I2C_FUNC_SMBUS_BYTE\n");
		वापस -EIO;
	पूर्ण

	bd = devm_kzalloc(&client->dev, माप(*bd), GFP_KERNEL);
	अगर (!bd)
		वापस -ENOMEM;

	bd->client = client;
	bd->pdata = pdata;

	/*
	 * Request the reset GPIO line with GPIOD_OUT_HIGH meaning निश्चितed,
	 * so in the machine descriptor table (or other hardware description),
	 * the line should be flagged as active low so this will निश्चित
	 * the reset.
	 */
	bd->reset = devm_gpiod_get(&client->dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(bd->reset)) अणु
		dev_err(&client->dev, "unable to request reset GPIO\n");
		ret = PTR_ERR(bd->reset);
		वापस ret;
	पूर्ण

	स_रखो(&props, 0, माप(props));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = 128;
	props.brightness = clamp_t(अचिन्हित पूर्णांक, pdata->def_value, 0,
				   props.max_brightness);

	backlight = devm_backlight_device_रेजिस्टर(&client->dev,
					      dev_name(&client->dev),
					      &bd->client->dev, bd,
					      &bd6107_backlight_ops, &props);
	अगर (IS_ERR(backlight)) अणु
		dev_err(&client->dev, "failed to register backlight\n");
		वापस PTR_ERR(backlight);
	पूर्ण

	backlight_update_status(backlight);
	i2c_set_clientdata(client, backlight);

	वापस 0;
पूर्ण

अटल पूर्णांक bd6107_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा backlight_device *backlight = i2c_get_clientdata(client);

	backlight->props.brightness = 0;
	backlight_update_status(backlight);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id bd6107_ids[] = अणु
	अणु "bd6107", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bd6107_ids);

अटल काष्ठा i2c_driver bd6107_driver = अणु
	.driver = अणु
		.name = "bd6107",
	पूर्ण,
	.probe = bd6107_probe,
	.हटाओ = bd6107_हटाओ,
	.id_table = bd6107_ids,
पूर्ण;

module_i2c_driver(bd6107_driver);

MODULE_DESCRIPTION("Rohm BD6107 Backlight Driver");
MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_LICENSE("GPL");
