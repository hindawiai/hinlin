<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2008 Openmoko, Inc.
// Copyright 2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinux.simtec.co.uk/
//
// Base S3C64XX setup inक्रमmation क्रम 24bpp LCD framebuffer

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fb.h>
#समावेश <linux/gpपन.स>

#समावेश "fb.h"
#समावेश "gpio-cfg.h"
#समावेश "gpio-samsung.h"

व्योम s3c64xx_fb_gpio_setup_24bpp(व्योम)
अणु
	s3c_gpio_cfgrange_nopull(S3C64XX_GPI(0), 16, S3C_GPIO_SFN(2));
	s3c_gpio_cfgrange_nopull(S3C64XX_GPJ(0), 12, S3C_GPIO_SFN(2));
पूर्ण
