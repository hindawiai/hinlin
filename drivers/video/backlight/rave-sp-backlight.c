<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

/*
 * LCD Backlight driver क्रम RAVE SP
 *
 * Copyright (C) 2018 Zodiac Inflight Innovations
 *
 */

#समावेश <linux/backlight.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/rave-sp.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा	RAVE_SP_BACKLIGHT_LCD_EN	BIT(7)

अटल पूर्णांक rave_sp_backlight_update_status(काष्ठा backlight_device *bd)
अणु
	स्थिर काष्ठा backlight_properties *p = &bd->props;
	स्थिर u8 पूर्णांकensity =
		(p->घातer == FB_BLANK_UNBLANK) ? p->brightness : 0;
	काष्ठा rave_sp *sp = dev_get_drvdata(&bd->dev);
	u8 cmd[] = अणु
		[0] = RAVE_SP_CMD_SET_BACKLIGHT,
		[1] = 0,
		[2] = पूर्णांकensity ? RAVE_SP_BACKLIGHT_LCD_EN | पूर्णांकensity : 0,
		[3] = 0,
		[4] = 0,
	पूर्ण;

	वापस rave_sp_exec(sp, cmd, माप(cmd), शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा backlight_ops rave_sp_backlight_ops = अणु
	.options	= BL_CORE_SUSPENDRESUME,
	.update_status	= rave_sp_backlight_update_status,
पूर्ण;

अटल काष्ठा backlight_properties rave_sp_backlight_props = अणु
	.type		= BACKLIGHT_PLATFORM,
	.max_brightness = 100,
	.brightness	= 50,
पूर्ण;

अटल पूर्णांक rave_sp_backlight_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा backlight_device *bd;

	bd = devm_backlight_device_रेजिस्टर(dev, pdev->name, dev,
					    dev_get_drvdata(dev->parent),
					    &rave_sp_backlight_ops,
					    &rave_sp_backlight_props);
	अगर (IS_ERR(bd))
		वापस PTR_ERR(bd);

	/*
	 * If there is a phandle poपूर्णांकing to the device node we can
	 * assume that another device will manage the status changes.
	 * If not we make sure the backlight is in a consistent state.
	 */
	अगर (!dev->of_node->phandle)
		backlight_update_status(bd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rave_sp_backlight_of_match[] = अणु
	अणु .compatible = "zii,rave-sp-backlight" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver rave_sp_backlight_driver = अणु
	.probe = rave_sp_backlight_probe,
	.driver	= अणु
		.name = KBUILD_MODNAME,
		.of_match_table = rave_sp_backlight_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rave_sp_backlight_driver);

MODULE_DEVICE_TABLE(of, rave_sp_backlight_of_match);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrey Vostrikov <andrey.vostrikov@cogentembedded.com>");
MODULE_AUTHOR("Nikita Yushchenko <nikita.yoush@cogentembedded.com>");
MODULE_AUTHOR("Andrey Smirnov <andrew.smirnov@gmail.com>");
MODULE_DESCRIPTION("RAVE SP Backlight driver");
