<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Pengutronix
 * Uwe Kleine-Koenig <u.kleine-koenig@pengutronix.de>
 */
#समावेश <linux/err.h>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

/**
 * gpio_led_रेजिस्टर_device - रेजिस्टर a gpio-led device
 * @pdata: the platक्रमm data used क्रम the new device
 *
 * Makes a copy of pdata and pdata->leds and रेजिस्टरs a new leds-gpio device
 * with the result. This allows to have pdata and pdata-leds in .init.rodata
 * and so saves some bytes compared to a अटल काष्ठा platक्रमm_device with
 * अटल platक्रमm data.
 *
 * Returns the रेजिस्टरed device or an error poपूर्णांकer.
 */
काष्ठा platक्रमm_device *__init gpio_led_रेजिस्टर_device(
		पूर्णांक id, स्थिर काष्ठा gpio_led_platक्रमm_data *pdata)
अणु
	काष्ठा platक्रमm_device *ret;
	काष्ठा gpio_led_platक्रमm_data _pdata = *pdata;

	अगर (!pdata->num_leds)
		वापस ERR_PTR(-EINVAL);

	_pdata.leds = kmemdup(pdata->leds,
			pdata->num_leds * माप(*pdata->leds), GFP_KERNEL);
	अगर (!_pdata.leds)
		वापस ERR_PTR(-ENOMEM);

	ret = platक्रमm_device_रेजिस्टर_resndata(शून्य, "leds-gpio", id,
			शून्य, 0, &_pdata, माप(_pdata));
	अगर (IS_ERR(ret))
		kमुक्त(_pdata.leds);

	वापस ret;
पूर्ण
