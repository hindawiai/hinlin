<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2008 Openmoko, Inc.
// Copyright 2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinux.simtec.co.uk/
//
// Base S3C64XX UART resource and device definitions

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश "map.h"
#समावेश <mach/irqs.h>

#समावेश "devs.h"

/* Serial port registrations */

/* 64xx uarts are बंदr together */

अटल काष्ठा resource s3c64xx_uart0_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_UART0, SZ_256),
	[1] = DEFINE_RES_IRQ(IRQ_UART0),
पूर्ण;

अटल काष्ठा resource s3c64xx_uart1_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_UART1, SZ_256),
	[1] = DEFINE_RES_IRQ(IRQ_UART1),
पूर्ण;

अटल काष्ठा resource s3c6xx_uart2_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_UART2, SZ_256),
	[1] = DEFINE_RES_IRQ(IRQ_UART2),
पूर्ण;

अटल काष्ठा resource s3c64xx_uart3_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C_PA_UART3, SZ_256),
	[1] = DEFINE_RES_IRQ(IRQ_UART3),
पूर्ण;


काष्ठा s3c24xx_uart_resources s3c64xx_uart_resources[] __initdata = अणु
	[0] = अणु
		.resources	= s3c64xx_uart0_resource,
		.nr_resources	= ARRAY_SIZE(s3c64xx_uart0_resource),
	पूर्ण,
	[1] = अणु
		.resources	= s3c64xx_uart1_resource,
		.nr_resources	= ARRAY_SIZE(s3c64xx_uart1_resource),
	पूर्ण,
	[2] = अणु
		.resources	= s3c6xx_uart2_resource,
		.nr_resources	= ARRAY_SIZE(s3c6xx_uart2_resource),
	पूर्ण,
	[3] = अणु
		.resources	= s3c64xx_uart3_resource,
		.nr_resources	= ARRAY_SIZE(s3c64xx_uart3_resource),
	पूर्ण,
पूर्ण;
