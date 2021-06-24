<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/video/backlight/aat2870_bl.c
 *
 * Copyright (c) 2011, NVIDIA Corporation.
 * Author: Jin Park <jinyoungp@nvidia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>
#समावेश <linux/mfd/aat2870.h>

काष्ठा aat2870_bl_driver_data अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा backlight_device *bd;

	पूर्णांक channels;
	पूर्णांक max_current;
	पूर्णांक brightness; /* current brightness */
पूर्ण;

अटल अंतरभूत पूर्णांक aat2870_brightness(काष्ठा aat2870_bl_driver_data *aat2870_bl,
				     पूर्णांक brightness)
अणु
	काष्ठा backlight_device *bd = aat2870_bl->bd;
	पूर्णांक val;

	val = brightness * (aat2870_bl->max_current - 1);
	val /= bd->props.max_brightness;

	वापस val;
पूर्ण

अटल अंतरभूत पूर्णांक aat2870_bl_enable(काष्ठा aat2870_bl_driver_data *aat2870_bl)
अणु
	काष्ठा aat2870_data *aat2870
			= dev_get_drvdata(aat2870_bl->pdev->dev.parent);

	वापस aat2870->ग_लिखो(aat2870, AAT2870_BL_CH_EN,
			      (u8)aat2870_bl->channels);
पूर्ण

अटल अंतरभूत पूर्णांक aat2870_bl_disable(काष्ठा aat2870_bl_driver_data *aat2870_bl)
अणु
	काष्ठा aat2870_data *aat2870
			= dev_get_drvdata(aat2870_bl->pdev->dev.parent);

	वापस aat2870->ग_लिखो(aat2870, AAT2870_BL_CH_EN, 0x0);
पूर्ण

अटल पूर्णांक aat2870_bl_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा aat2870_bl_driver_data *aat2870_bl = bl_get_data(bd);
	काष्ठा aat2870_data *aat2870 =
			dev_get_drvdata(aat2870_bl->pdev->dev.parent);
	पूर्णांक brightness = bd->props.brightness;
	पूर्णांक ret;

	अगर ((brightness < 0) || (bd->props.max_brightness < brightness)) अणु
		dev_err(&bd->dev, "invalid brightness, %d\n", brightness);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&bd->dev, "brightness=%d, power=%d, state=%d\n",
		 bd->props.brightness, bd->props.घातer, bd->props.state);

	अगर ((bd->props.घातer != FB_BLANK_UNBLANK) ||
			(bd->props.state & BL_CORE_FBBLANK) ||
			(bd->props.state & BL_CORE_SUSPENDED))
		brightness = 0;

	ret = aat2870->ग_लिखो(aat2870, AAT2870_BLM,
			     (u8)aat2870_brightness(aat2870_bl, brightness));
	अगर (ret < 0)
		वापस ret;

	अगर (brightness == 0) अणु
		ret = aat2870_bl_disable(aat2870_bl);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (aat2870_bl->brightness == 0) अणु
		ret = aat2870_bl_enable(aat2870_bl);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	aat2870_bl->brightness = brightness;

	वापस 0;
पूर्ण

अटल पूर्णांक aat2870_bl_check_fb(काष्ठा backlight_device *bd, काष्ठा fb_info *fi)
अणु
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा backlight_ops aat2870_bl_ops = अणु
	.options = BL_CORE_SUSPENDRESUME,
	.update_status = aat2870_bl_update_status,
	.check_fb = aat2870_bl_check_fb,
पूर्ण;

अटल पूर्णांक aat2870_bl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aat2870_bl_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा aat2870_bl_driver_data *aat2870_bl;
	काष्ठा backlight_device *bd;
	काष्ठा backlight_properties props;
	पूर्णांक ret = 0;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "No platform data\n");
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	अगर (pdev->id != AAT2870_ID_BL) अणु
		dev_err(&pdev->dev, "Invalid device ID, %d\n", pdev->id);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	aat2870_bl = devm_kzalloc(&pdev->dev,
				  माप(काष्ठा aat2870_bl_driver_data),
				  GFP_KERNEL);
	अगर (!aat2870_bl) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));

	props.type = BACKLIGHT_RAW;
	bd = devm_backlight_device_रेजिस्टर(&pdev->dev, "aat2870-backlight",
					&pdev->dev, aat2870_bl, &aat2870_bl_ops,
					&props);
	अगर (IS_ERR(bd)) अणु
		dev_err(&pdev->dev,
			"Failed allocate memory for backlight device\n");
		ret = PTR_ERR(bd);
		जाओ out;
	पूर्ण

	aat2870_bl->pdev = pdev;
	platक्रमm_set_drvdata(pdev, aat2870_bl);

	aat2870_bl->bd = bd;

	अगर (pdata->channels > 0)
		aat2870_bl->channels = pdata->channels;
	अन्यथा
		aat2870_bl->channels = AAT2870_BL_CH_ALL;

	अगर (pdata->max_current > 0)
		aat2870_bl->max_current = pdata->max_current;
	अन्यथा
		aat2870_bl->max_current = AAT2870_CURRENT_27_9;

	अगर (pdata->max_brightness > 0)
		bd->props.max_brightness = pdata->max_brightness;
	अन्यथा
		bd->props.max_brightness = 255;

	aat2870_bl->brightness = 0;
	bd->props.घातer = FB_BLANK_UNBLANK;
	bd->props.brightness = bd->props.max_brightness;

	ret = aat2870_bl_update_status(bd);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to initialize\n");
		वापस ret;
	पूर्ण

	वापस 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक aat2870_bl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aat2870_bl_driver_data *aat2870_bl = platक्रमm_get_drvdata(pdev);
	काष्ठा backlight_device *bd = aat2870_bl->bd;

	bd->props.घातer = FB_BLANK_POWERDOWN;
	bd->props.brightness = 0;
	backlight_update_status(bd);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aat2870_bl_driver = अणु
	.driver = अणु
		.name	= "aat2870-backlight",
	पूर्ण,
	.probe		= aat2870_bl_probe,
	.हटाओ		= aat2870_bl_हटाओ,
पूर्ण;

अटल पूर्णांक __init aat2870_bl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&aat2870_bl_driver);
पूर्ण
subsys_initcall(aat2870_bl_init);

अटल व्योम __निकास aat2870_bl_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&aat2870_bl_driver);
पूर्ण
module_निकास(aat2870_bl_निकास);

MODULE_DESCRIPTION("AnalogicTech AAT2870 Backlight");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jin Park <jinyoungp@nvidia.com>");
