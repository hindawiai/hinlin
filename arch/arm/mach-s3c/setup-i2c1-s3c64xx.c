<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2008 Openmoko, Inc.
// Copyright 2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinux.simtec.co.uk/
//
// Base S3C64XX I2C bus 1 gpio configuration

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/gpपन.स>

काष्ठा platक्रमm_device; /* करोn't need the contents */

#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश "gpio-cfg.h"
#समावेश "gpio-samsung.h"

व्योम s3c_i2c1_cfg_gpio(काष्ठा platक्रमm_device *dev)
अणु
	s3c_gpio_cfgall_range(S3C64XX_GPB(2), 2,
			      S3C_GPIO_SFN(6), S3C_GPIO_PULL_UP);
पूर्ण
