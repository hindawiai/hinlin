<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
//
// Copyright (c) Arnaud Patard <arnaud.patard@rtp-net.org>
//
//	    S3C2410 bluetooth "driver"

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/leds.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/rfसमाप्त.h>

#समावेश "gpio-cfg.h"
#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"

#समावेश "h1940.h"

#घोषणा DRV_NAME "h1940-bt"

/* Bluetooth control */
अटल व्योम h1940bt_enable(पूर्णांक on)
अणु
	अगर (on) अणु
		/* Power on the chip */
		gpio_set_value(H1940_LATCH_BLUETOOTH_POWER, 1);
		/* Reset the chip */
		mdelay(10);

		gpio_set_value(S3C2410_GPH(1), 1);
		mdelay(10);
		gpio_set_value(S3C2410_GPH(1), 0);

		h1940_led_blink_set(शून्य, GPIO_LED_BLINK, शून्य, शून्य);
	पूर्ण
	अन्यथा अणु
		gpio_set_value(S3C2410_GPH(1), 1);
		mdelay(10);
		gpio_set_value(S3C2410_GPH(1), 0);
		mdelay(10);
		gpio_set_value(H1940_LATCH_BLUETOOTH_POWER, 0);

		h1940_led_blink_set(शून्य, GPIO_LED_NO_BLINK_LOW, शून्य, शून्य);
	पूर्ण
पूर्ण

अटल पूर्णांक h1940bt_set_block(व्योम *data, bool blocked)
अणु
	h1940bt_enable(!blocked);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops h1940bt_rfसमाप्त_ops = अणु
	.set_block = h1940bt_set_block,
पूर्ण;

अटल पूर्णांक h1940bt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rfसमाप्त *rfk;
	पूर्णांक ret = 0;

	ret = gpio_request(S3C2410_GPH(1), dev_name(&pdev->dev));
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not get GPH1\n");
		वापस ret;
	पूर्ण

	ret = gpio_request(H1940_LATCH_BLUETOOTH_POWER, dev_name(&pdev->dev));
	अगर (ret) अणु
		gpio_मुक्त(S3C2410_GPH(1));
		dev_err(&pdev->dev, "could not get BT_POWER\n");
		वापस ret;
	पूर्ण

	/* Configures BT serial port GPIOs */
	s3c_gpio_cfgpin(S3C2410_GPH(0), S3C2410_GPH0_nCTS0);
	s3c_gpio_setpull(S3C2410_GPH(0), S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(S3C2410_GPH(1), S3C2410_GPIO_OUTPUT);
	s3c_gpio_setpull(S3C2410_GPH(1), S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(S3C2410_GPH(2), S3C2410_GPH2_TXD0);
	s3c_gpio_setpull(S3C2410_GPH(2), S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(S3C2410_GPH(3), S3C2410_GPH3_RXD0);
	s3c_gpio_setpull(S3C2410_GPH(3), S3C_GPIO_PULL_NONE);

	rfk = rfसमाप्त_alloc(DRV_NAME, &pdev->dev, RFKILL_TYPE_BLUETOOTH,
			&h1940bt_rfसमाप्त_ops, शून्य);
	अगर (!rfk) अणु
		ret = -ENOMEM;
		जाओ err_rfk_alloc;
	पूर्ण

	ret = rfसमाप्त_रेजिस्टर(rfk);
	अगर (ret)
		जाओ err_rfसमाप्त;

	platक्रमm_set_drvdata(pdev, rfk);

	वापस 0;

err_rfसमाप्त:
	rfसमाप्त_destroy(rfk);
err_rfk_alloc:
	वापस ret;
पूर्ण

अटल पूर्णांक h1940bt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rfसमाप्त *rfk = platक्रमm_get_drvdata(pdev);

	platक्रमm_set_drvdata(pdev, शून्य);
	gpio_मुक्त(S3C2410_GPH(1));

	अगर (rfk) अणु
		rfसमाप्त_unरेजिस्टर(rfk);
		rfसमाप्त_destroy(rfk);
	पूर्ण
	rfk = शून्य;

	h1940bt_enable(0);

	वापस 0;
पूर्ण


अटल काष्ठा platक्रमm_driver h1940bt_driver = अणु
	.driver		= अणु
		.name	= DRV_NAME,
	पूर्ण,
	.probe		= h1940bt_probe,
	.हटाओ		= h1940bt_हटाओ,
पूर्ण;

module_platक्रमm_driver(h1940bt_driver);

MODULE_AUTHOR("Arnaud Patard <arnaud.patard@rtp-net.org>");
MODULE_DESCRIPTION("Driver for the iPAQ H1940 bluetooth chip");
MODULE_LICENSE("GPL");
