<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2009-2010, Lars-Peter Clausen <lars@metafoo.de>
 *      PCF50633 backlight device driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/backlight.h>
#समावेश <linux/fb.h>

#समावेश <linux/mfd/pcf50633/core.h>
#समावेश <linux/mfd/pcf50633/backlight.h>

काष्ठा pcf50633_bl अणु
	काष्ठा pcf50633 *pcf;
	काष्ठा backlight_device *bl;

	अचिन्हित पूर्णांक brightness;
	अचिन्हित पूर्णांक brightness_limit;
पूर्ण;

/*
 * pcf50633_bl_set_brightness_limit
 *
 * Update the brightness limit क्रम the pc50633 backlight. The actual brightness
 * will not go above the limit. This is useful to limit घातer drain क्रम example
 * on low battery.
 *
 * @dev: Poपूर्णांकer to a pcf50633 device
 * @limit: The brightness limit. Valid values are 0-63
 */
पूर्णांक pcf50633_bl_set_brightness_limit(काष्ठा pcf50633 *pcf, अचिन्हित पूर्णांक limit)
अणु
	काष्ठा pcf50633_bl *pcf_bl = platक्रमm_get_drvdata(pcf->bl_pdev);

	अगर (!pcf_bl)
		वापस -ENODEV;

	pcf_bl->brightness_limit = limit & 0x3f;
	backlight_update_status(pcf_bl->bl);

	वापस 0;
पूर्ण

अटल पूर्णांक pcf50633_bl_update_status(काष्ठा backlight_device *bl)
अणु
	काष्ठा pcf50633_bl *pcf_bl = bl_get_data(bl);
	अचिन्हित पूर्णांक new_brightness;


	अगर (bl->props.state & (BL_CORE_SUSPENDED | BL_CORE_FBBLANK) ||
		bl->props.घातer != FB_BLANK_UNBLANK)
		new_brightness = 0;
	अन्यथा अगर (bl->props.brightness < pcf_bl->brightness_limit)
		new_brightness = bl->props.brightness;
	अन्यथा
		new_brightness = pcf_bl->brightness_limit;


	अगर (pcf_bl->brightness == new_brightness)
		वापस 0;

	अगर (new_brightness) अणु
		pcf50633_reg_ग_लिखो(pcf_bl->pcf, PCF50633_REG_LEDOUT,
					new_brightness);
		अगर (!pcf_bl->brightness)
			pcf50633_reg_ग_लिखो(pcf_bl->pcf, PCF50633_REG_LEDENA, 1);
	पूर्ण अन्यथा अणु
		pcf50633_reg_ग_लिखो(pcf_bl->pcf, PCF50633_REG_LEDENA, 0);
	पूर्ण

	pcf_bl->brightness = new_brightness;

	वापस 0;
पूर्ण

अटल पूर्णांक pcf50633_bl_get_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा pcf50633_bl *pcf_bl = bl_get_data(bl);

	वापस pcf_bl->brightness;
पूर्ण

अटल स्थिर काष्ठा backlight_ops pcf50633_bl_ops = अणु
	.get_brightness = pcf50633_bl_get_brightness,
	.update_status	= pcf50633_bl_update_status,
	.options	= BL_CORE_SUSPENDRESUME,
पूर्ण;

अटल पूर्णांक pcf50633_bl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pcf50633_bl *pcf_bl;
	काष्ठा device *parent = pdev->dev.parent;
	काष्ठा pcf50633_platक्रमm_data *pcf50633_data = dev_get_platdata(parent);
	काष्ठा pcf50633_bl_platक्रमm_data *pdata = pcf50633_data->backlight_data;
	काष्ठा backlight_properties bl_props;

	pcf_bl = devm_kzalloc(&pdev->dev, माप(*pcf_bl), GFP_KERNEL);
	अगर (!pcf_bl)
		वापस -ENOMEM;

	स_रखो(&bl_props, 0, माप(bl_props));
	bl_props.type = BACKLIGHT_RAW;
	bl_props.max_brightness = 0x3f;
	bl_props.घातer = FB_BLANK_UNBLANK;

	अगर (pdata) अणु
		bl_props.brightness = pdata->शेष_brightness;
		pcf_bl->brightness_limit = pdata->शेष_brightness_limit;
	पूर्ण अन्यथा अणु
		bl_props.brightness = 0x3f;
		pcf_bl->brightness_limit = 0x3f;
	पूर्ण

	pcf_bl->pcf = dev_to_pcf50633(pdev->dev.parent);

	pcf_bl->bl = devm_backlight_device_रेजिस्टर(&pdev->dev, pdev->name,
						&pdev->dev, pcf_bl,
						&pcf50633_bl_ops, &bl_props);

	अगर (IS_ERR(pcf_bl->bl))
		वापस PTR_ERR(pcf_bl->bl);

	platक्रमm_set_drvdata(pdev, pcf_bl);

	pcf50633_reg_ग_लिखो(pcf_bl->pcf, PCF50633_REG_LEDDIM, pdata->ramp_समय);

	/*
	 * Should be dअगरferent from bl_props.brightness, so we करो not निकास
	 * update_status early the first समय it's called
	 */
	pcf_bl->brightness = pcf_bl->bl->props.brightness + 1;

	backlight_update_status(pcf_bl->bl);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pcf50633_bl_driver = अणु
	.probe =	pcf50633_bl_probe,
	.driver = अणु
		.name = "pcf50633-backlight",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pcf50633_bl_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("PCF50633 backlight driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pcf50633-backlight");
