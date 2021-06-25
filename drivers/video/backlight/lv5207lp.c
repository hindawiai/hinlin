<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sanyo LV5207LP LED Driver
 *
 * Copyright (C) 2013 Ideas on board SPRL
 *
 * Contact: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/backlight.h>
#समावेश <linux/err.h>
#समावेश <linux/fb.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/lv5207lp.h>
#समावेश <linux/slab.h>

#घोषणा LV5207LP_CTRL1			0x00
#घोषणा LV5207LP_CPSW			(1 << 7)
#घोषणा LV5207LP_SCTEN			(1 << 6)
#घोषणा LV5207LP_C10			(1 << 5)
#घोषणा LV5207LP_CKSW			(1 << 4)
#घोषणा LV5207LP_RSW			(1 << 3)
#घोषणा LV5207LP_GSW			(1 << 2)
#घोषणा LV5207LP_BSW			(1 << 1)
#घोषणा LV5207LP_CTRL2			0x01
#घोषणा LV5207LP_MSW			(1 << 7)
#घोषणा LV5207LP_MLED4			(1 << 6)
#घोषणा LV5207LP_RED			0x02
#घोषणा LV5207LP_GREEN			0x03
#घोषणा LV5207LP_BLUE			0x04

#घोषणा LV5207LP_MAX_BRIGHTNESS		32

काष्ठा lv5207lp अणु
	काष्ठा i2c_client *client;
	काष्ठा backlight_device *backlight;
	काष्ठा lv5207lp_platक्रमm_data *pdata;
पूर्ण;

अटल पूर्णांक lv5207lp_ग_लिखो(काष्ठा lv5207lp *lv, u8 reg, u8 data)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(lv->client, reg, data);
पूर्ण

अटल पूर्णांक lv5207lp_backlight_update_status(काष्ठा backlight_device *backlight)
अणु
	काष्ठा lv5207lp *lv = bl_get_data(backlight);
	पूर्णांक brightness = backlight_get_brightness(backlight);

	अगर (brightness) अणु
		lv5207lp_ग_लिखो(lv, LV5207LP_CTRL1,
			       LV5207LP_CPSW | LV5207LP_C10 | LV5207LP_CKSW);
		lv5207lp_ग_लिखो(lv, LV5207LP_CTRL2,
			       LV5207LP_MSW | LV5207LP_MLED4 |
			       (brightness - 1));
	पूर्ण अन्यथा अणु
		lv5207lp_ग_लिखो(lv, LV5207LP_CTRL1, 0);
		lv5207lp_ग_लिखो(lv, LV5207LP_CTRL2, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lv5207lp_backlight_check_fb(काष्ठा backlight_device *backlight,
				       काष्ठा fb_info *info)
अणु
	काष्ठा lv5207lp *lv = bl_get_data(backlight);

	वापस lv->pdata->fbdev == शून्य || lv->pdata->fbdev == info->dev;
पूर्ण

अटल स्थिर काष्ठा backlight_ops lv5207lp_backlight_ops = अणु
	.options	= BL_CORE_SUSPENDRESUME,
	.update_status	= lv5207lp_backlight_update_status,
	.check_fb	= lv5207lp_backlight_check_fb,
पूर्ण;

अटल पूर्णांक lv5207lp_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lv5207lp_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा backlight_device *backlight;
	काष्ठा backlight_properties props;
	काष्ठा lv5207lp *lv;

	अगर (pdata == शून्य) अणु
		dev_err(&client->dev, "No platform data supplied\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_warn(&client->dev,
			 "I2C adapter doesn't support I2C_FUNC_SMBUS_BYTE\n");
		वापस -EIO;
	पूर्ण

	lv = devm_kzalloc(&client->dev, माप(*lv), GFP_KERNEL);
	अगर (!lv)
		वापस -ENOMEM;

	lv->client = client;
	lv->pdata = pdata;

	स_रखो(&props, 0, माप(props));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = min_t(अचिन्हित पूर्णांक, pdata->max_value,
				     LV5207LP_MAX_BRIGHTNESS);
	props.brightness = clamp_t(अचिन्हित पूर्णांक, pdata->def_value, 0,
				   props.max_brightness);

	backlight = devm_backlight_device_रेजिस्टर(&client->dev,
				dev_name(&client->dev), &lv->client->dev,
				lv, &lv5207lp_backlight_ops, &props);
	अगर (IS_ERR(backlight)) अणु
		dev_err(&client->dev, "failed to register backlight\n");
		वापस PTR_ERR(backlight);
	पूर्ण

	backlight_update_status(backlight);
	i2c_set_clientdata(client, backlight);

	वापस 0;
पूर्ण

अटल पूर्णांक lv5207lp_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा backlight_device *backlight = i2c_get_clientdata(client);

	backlight->props.brightness = 0;
	backlight_update_status(backlight);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lv5207lp_ids[] = अणु
	अणु "lv5207lp", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lv5207lp_ids);

अटल काष्ठा i2c_driver lv5207lp_driver = अणु
	.driver = अणु
		.name = "lv5207lp",
	पूर्ण,
	.probe = lv5207lp_probe,
	.हटाओ = lv5207lp_हटाओ,
	.id_table = lv5207lp_ids,
पूर्ण;

module_i2c_driver(lv5207lp_driver);

MODULE_DESCRIPTION("Sanyo LV5207LP Backlight Driver");
MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_LICENSE("GPL");
