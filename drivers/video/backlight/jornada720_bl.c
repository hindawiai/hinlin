<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Backlight driver क्रम HP Jornada 700 series (710/720/728)
 * Copyright (C) 2006-2009 Kristoffer Ericson <kristoffer.ericson@gmail.com>
 */

#समावेश <linux/backlight.h>
#समावेश <linux/device.h>
#समावेश <linux/fb.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <mach/jornada720.h>
#समावेश <mach/hardware.h>

#समावेश <video/s1d13xxxfb.h>

#घोषणा BL_MAX_BRIGHT	255
#घोषणा BL_DEF_BRIGHT	25

अटल पूर्णांक jornada_bl_get_brightness(काष्ठा backlight_device *bd)
अणु
	पूर्णांक ret;

	/* check अगर backlight is on */
	अगर (!(PPSR & PPC_LDD1))
		वापस 0;

	jornada_ssp_start();

	/* cmd should वापस txdummy */
	ret = jornada_ssp_byte(GETBRIGHTNESS);

	अगर (jornada_ssp_byte(GETBRIGHTNESS) != TXDUMMY) अणु
		dev_err(&bd->dev, "get brightness timeout\n");
		jornada_ssp_end();
		वापस -ETIMEDOUT;
	पूर्ण

	/* exchange txdummy क्रम value */
	ret = jornada_ssp_byte(TXDUMMY);

	jornada_ssp_end();

	वापस BL_MAX_BRIGHT - ret;
पूर्ण

अटल पूर्णांक jornada_bl_update_status(काष्ठा backlight_device *bd)
अणु
	पूर्णांक ret = 0;

	jornada_ssp_start();

	/* If backlight is off then really turn it off */
	अगर (backlight_is_blank(bd)) अणु
		ret = jornada_ssp_byte(BRIGHTNESSOFF);
		अगर (ret != TXDUMMY) अणु
			dev_info(&bd->dev, "brightness off timeout\n");
			/* turn off backlight */
			PPSR &= ~PPC_LDD1;
			PPDR |= PPC_LDD1;
			ret = -ETIMEDOUT;
		पूर्ण
	पूर्ण अन्यथा  /* turn on backlight */
		PPSR |= PPC_LDD1;

	/* send command to our mcu */
	अगर (jornada_ssp_byte(SETBRIGHTNESS) != TXDUMMY) अणु
		dev_info(&bd->dev, "failed to set brightness\n");
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	/*
	 * at this poपूर्णांक we expect that the mcu has accepted
	 * our command and is रुकोing क्रम our new value
	 * please note that maximum brightness is 255,
	 * but due to physical layout it is equal to 0, so we simply
	 * invert the value (MAX VALUE - NEW VALUE).
	 */
	अगर (jornada_ssp_byte(BL_MAX_BRIGHT - bd->props.brightness)
		!= TXDUMMY) अणु
		dev_err(&bd->dev, "set brightness failed\n");
		ret = -ETIMEDOUT;
	पूर्ण

	/*
	 * If infact we get an TXDUMMY as output we are happy and करोnt
	 * make any further comments about it
	 */
out:
	jornada_ssp_end();

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा backlight_ops jornada_bl_ops = अणु
	.get_brightness = jornada_bl_get_brightness,
	.update_status = jornada_bl_update_status,
	.options = BL_CORE_SUSPENDRESUME,
पूर्ण;

अटल पूर्णांक jornada_bl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा backlight_properties props;
	पूर्णांक ret;
	काष्ठा backlight_device *bd;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = BL_MAX_BRIGHT;

	bd = devm_backlight_device_रेजिस्टर(&pdev->dev, S1D_DEVICENAME,
					&pdev->dev, शून्य, &jornada_bl_ops,
					&props);
	अगर (IS_ERR(bd)) अणु
		ret = PTR_ERR(bd);
		dev_err(&pdev->dev, "failed to register device, err=%x\n", ret);
		वापस ret;
	पूर्ण

	bd->props.घातer = FB_BLANK_UNBLANK;
	bd->props.brightness = BL_DEF_BRIGHT;
	/*
	 * note. make sure max brightness is set otherwise
	 * you will get seemingly non-related errors when
	 * trying to change brightness
	 */
	jornada_bl_update_status(bd);

	platक्रमm_set_drvdata(pdev, bd);
	dev_info(&pdev->dev, "HP Jornada 700 series backlight driver\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver jornada_bl_driver = अणु
	.probe		= jornada_bl_probe,
	.driver	= अणु
		.name	= "jornada_bl",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(jornada_bl_driver);

MODULE_AUTHOR("Kristoffer Ericson <kristoffer.ericson>");
MODULE_DESCRIPTION("HP Jornada 710/720/728 Backlight driver");
MODULE_LICENSE("GPL");
