<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
//	originally from arch/arm/plat-s3c24xx/devs.c
//
// Copyright (c) 2004 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//
// Base S3C24XX platक्रमm device definitions

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "devs.h"

/* uart devices */

अटल काष्ठा platक्रमm_device s3c24xx_uart_device0 = अणु
	.id		= 0,
पूर्ण;

अटल काष्ठा platक्रमm_device s3c24xx_uart_device1 = अणु
	.id		= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device s3c24xx_uart_device2 = अणु
	.id		= 2,
पूर्ण;

अटल काष्ठा platक्रमm_device s3c24xx_uart_device3 = अणु
	.id		= 3,
पूर्ण;

काष्ठा platक्रमm_device *s3c24xx_uart_src[4] = अणु
	&s3c24xx_uart_device0,
	&s3c24xx_uart_device1,
	&s3c24xx_uart_device2,
	&s3c24xx_uart_device3,
पूर्ण;

काष्ठा platक्रमm_device *s3c24xx_uart_devs[4] = अणु
पूर्ण;
