<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2010 Samsung Electronics Co., Ltd.
//                     http://www.samsung.com/
//
// Based on S3C24XX setup क्रम i2c device

#समावेश <linux/kernel.h>
#समावेश <linux/gpपन.स>

काष्ठा platक्रमm_device; /* करोn't need the contents */

#समावेश <linux/platक्रमm_data/touchscreen-s3c2410.h>

#समावेश "gpio-cfg.h"
#समावेश "gpio-samsung.h"

/**
 * s3c24xx_ts_cfg_gpio - configure gpio क्रम s3c2410 प्रणालीs
 * @dev: Device to configure GPIO क्रम (ignored)
 *
 * Configure the GPIO क्रम the S3C2410 प्रणाली, where we have बाह्यal FETs
 * connected to the device (later प्रणालीs such as the S3C2440 पूर्णांकegrate
 * these पूर्णांकo the device).
 */
व्योम s3c24xx_ts_cfg_gpio(काष्ठा platक्रमm_device *dev)
अणु
	s3c_gpio_cfgpin_range(S3C2410_GPG(12), 4, S3C_GPIO_SFN(3));
पूर्ण
