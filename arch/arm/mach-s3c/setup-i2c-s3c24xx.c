<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//
// S3C24XX Base setup क्रम i2c device

#समावेश <linux/kernel.h>
#समावेश <linux/gpपन.स>

काष्ठा platक्रमm_device;

#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>

#समावेश "gpio-cfg.h"
#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"

व्योम s3c_i2c0_cfg_gpio(काष्ठा platक्रमm_device *dev)
अणु
	s3c_gpio_cfgpin(S3C2410_GPE(15), S3C2410_GPE15_IICSDA);
	s3c_gpio_cfgpin(S3C2410_GPE(14), S3C2410_GPE14_IICSCL);
पूर्ण
