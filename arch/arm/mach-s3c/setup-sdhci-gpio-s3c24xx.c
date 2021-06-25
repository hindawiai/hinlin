<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2010 Promwad Innovation Company
//	Yauhen Kharuzhy <yauhen.kharuzhy@promwad.com>
//
// S3C2416 - Helper functions क्रम setting up SDHCI device(s) GPIO (HSMMC)
//
// Based on mach-s3c64xx/setup-sdhci-gpio.c

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>

#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"
#समावेश "gpio-cfg.h"
#समावेश "sdhci.h"

व्योम s3c2416_setup_sdhci0_cfg_gpio(काष्ठा platक्रमm_device *dev, पूर्णांक width)
अणु
	s3c_gpio_cfgrange_nopull(S3C2410_GPE(5), 2 + width, S3C_GPIO_SFN(2));
पूर्ण

व्योम s3c2416_setup_sdhci1_cfg_gpio(काष्ठा platक्रमm_device *dev, पूर्णांक width)
अणु
	s3c_gpio_cfgrange_nopull(S3C2410_GPL(0), width, S3C_GPIO_SFN(2));
	s3c_gpio_cfgrange_nopull(S3C2410_GPL(8), 2, S3C_GPIO_SFN(2));
पूर्ण
