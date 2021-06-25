<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// HS-SPI device setup क्रम S3C2443/S3C2416
//
// Copyright (C) 2011 Samsung Electronics Ltd.
//		http://www.samsung.com/

#समावेश <linux/gpपन.स>
#समावेश <linux/platक्रमm_device.h>

#समावेश "gpio-cfg.h"

#समावेश "hardware-s3c24xx.h"
#समावेश "regs-gpio.h"

#अगर_घोषित CONFIG_S3C64XX_DEV_SPI0
पूर्णांक s3c64xx_spi0_cfg_gpio(व्योम)
अणु
	/* enable hsspi bit in misccr */
	s3c2410_modअगरy_misccr(S3C2416_MISCCR_HSSPI_EN2, 1);

	s3c_gpio_cfgall_range(S3C2410_GPE(11), 3,
			      S3C_GPIO_SFN(2), S3C_GPIO_PULL_UP);

	वापस 0;
पूर्ण
#पूर्ण_अगर
