<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Copyright (c) 2004 Simtec Electronics
 * Ben Dooks <ben@simtec.co.uk>
 *
 * Header file क्रम s3c2410 standard platक्रमm devices
 */

#अगर_अघोषित __PLAT_DEVS_H
#घोषणा __PLAT_DEVS_H __खाता__

#समावेश <linux/platक्रमm_device.h>

काष्ठा s3c24xx_uart_resources अणु
	काष्ठा resource		*resources;
	अचिन्हित दीर्घ		 nr_resources;
पूर्ण;

बाह्य काष्ठा s3c24xx_uart_resources s3c2410_uart_resources[];
बाह्य काष्ठा s3c24xx_uart_resources s3c64xx_uart_resources[];

बाह्य काष्ठा platक्रमm_device *s3c24xx_uart_devs[];
बाह्य काष्ठा platक्रमm_device *s3c24xx_uart_src[];

बाह्य काष्ठा platक्रमm_device s3c64xx_device_ac97;
बाह्य काष्ठा platक्रमm_device s3c64xx_device_iis0;
बाह्य काष्ठा platक्रमm_device s3c64xx_device_iis1;
बाह्य काष्ठा platक्रमm_device s3c64xx_device_iisv4;
बाह्य काष्ठा platक्रमm_device s3c64xx_device_onenand1;
बाह्य काष्ठा platक्रमm_device s3c64xx_device_pcm0;
बाह्य काष्ठा platक्रमm_device s3c64xx_device_pcm1;
बाह्य काष्ठा platक्रमm_device s3c64xx_device_spi0;
बाह्य काष्ठा platक्रमm_device s3c64xx_device_spi1;
बाह्य काष्ठा platक्रमm_device s3c64xx_device_spi2;

बाह्य काष्ठा platक्रमm_device s3c_device_adc;
बाह्य काष्ठा platक्रमm_device s3c_device_cfcon;
बाह्य काष्ठा platक्रमm_device s3c_device_fb;
बाह्य काष्ठा platक्रमm_device s3c_device_hwmon;
बाह्य काष्ठा platक्रमm_device s3c_device_hsmmc0;
बाह्य काष्ठा platक्रमm_device s3c_device_hsmmc1;
बाह्य काष्ठा platक्रमm_device s3c_device_hsmmc2;
बाह्य काष्ठा platक्रमm_device s3c_device_hsmmc3;
बाह्य काष्ठा platक्रमm_device s3c_device_i2c0;
बाह्य काष्ठा platक्रमm_device s3c_device_i2c1;
बाह्य काष्ठा platक्रमm_device s3c_device_i2c2;
बाह्य काष्ठा platक्रमm_device s3c_device_i2c3;
बाह्य काष्ठा platक्रमm_device s3c_device_i2c4;
बाह्य काष्ठा platक्रमm_device s3c_device_i2c5;
बाह्य काष्ठा platक्रमm_device s3c_device_i2c6;
बाह्य काष्ठा platक्रमm_device s3c_device_i2c7;
बाह्य काष्ठा platक्रमm_device s3c_device_iis;
बाह्य काष्ठा platक्रमm_device s3c_device_lcd;
बाह्य काष्ठा platक्रमm_device s3c_device_nand;
बाह्य काष्ठा platक्रमm_device s3c_device_ohci;
बाह्य काष्ठा platक्रमm_device s3c_device_onenand;
बाह्य काष्ठा platक्रमm_device s3c_device_rtc;
बाह्य काष्ठा platक्रमm_device s3c_device_sdi;
बाह्य काष्ठा platक्रमm_device s3c_device_spi0;
बाह्य काष्ठा platक्रमm_device s3c_device_spi1;
बाह्य काष्ठा platक्रमm_device s3c_device_ts;
बाह्य काष्ठा platक्रमm_device s3c_device_समयr[];
बाह्य काष्ठा platक्रमm_device s3c_device_usbgadget;
बाह्य काष्ठा platक्रमm_device s3c_device_usb_hsotg;
बाह्य काष्ठा platक्रमm_device s3c_device_usb_hsudc;
बाह्य काष्ठा platक्रमm_device s3c_device_wdt;

बाह्य काष्ठा platक्रमm_device samsung_asoc_idma;
बाह्य काष्ठा platक्रमm_device samsung_device_keypad;
बाह्य काष्ठा platक्रमm_device samsung_device_pwm;

/* s3c2440 specअगरic devices */

#अगर_घोषित CONFIG_CPU_S3C2440

बाह्य काष्ठा platक्रमm_device s3c_device_camअगर;
बाह्य काष्ठा platक्रमm_device s3c_device_ac97;

#पूर्ण_अगर

/**
 * s3c_set_platdata() - helper क्रम setting platक्रमm data
 * @pd: The शेष platक्रमm data क्रम this device.
 * @pdsize: The size of the platक्रमm data.
 * @pdev: Poपूर्णांकer to the device to fill in.
 *
 * This helper replaces a number of calls that copy and then set the
 * platक्रमm data of the device.
 */
बाह्य व्योम *s3c_set_platdata(व्योम *pd, माप_प्रकार pdsize,
			      काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर /* __PLAT_DEVS_H */
