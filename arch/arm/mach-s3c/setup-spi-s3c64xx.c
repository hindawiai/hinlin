<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2011 Samsung Electronics Ltd.
//		http://www.samsung.com/

#समावेश <linux/gpपन.स>
#समावेश <linux/platक्रमm_data/spi-s3c64xx.h>
#समावेश "gpio-cfg.h"
#समावेश "gpio-samsung.h"

#अगर_घोषित CONFIG_S3C64XX_DEV_SPI0
पूर्णांक s3c64xx_spi0_cfg_gpio(व्योम)
अणु
	s3c_gpio_cfgall_range(S3C64XX_GPC(0), 3,
				S3C_GPIO_SFN(2), S3C_GPIO_PULL_UP);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_S3C64XX_DEV_SPI1
पूर्णांक s3c64xx_spi1_cfg_gpio(व्योम)
अणु
	s3c_gpio_cfgall_range(S3C64XX_GPC(4), 3,
				S3C_GPIO_SFN(2), S3C_GPIO_PULL_UP);
	वापस 0;
पूर्ण
#पूर्ण_अगर
