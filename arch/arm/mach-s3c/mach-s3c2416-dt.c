<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Samsung's S3C2416 flattened device tree enabled machine
//
// Copyright (c) 2012 Heiko Stuebner <heiko@sntech.de>
//
// based on mach-exynos/mach-exynos4-dt.c
//
// Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
//		http://www.samsung.com
// Copyright (c) 2010-2011 Linaro Ltd.
//		www.linaro.org

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/serial_s3c.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश "map.h"

#समावेश "cpu.h"
#समावेश "pm.h"

#समावेश "s3c24xx.h"

अटल व्योम __init s3c2416_dt_map_io(व्योम)
अणु
	s3c24xx_init_io(शून्य, 0);
पूर्ण

अटल व्योम __init s3c2416_dt_machine_init(व्योम)
अणु
	s3c_pm_init();
पूर्ण

अटल स्थिर अक्षर *स्थिर s3c2416_dt_compat[] __initस्थिर = अणु
	"samsung,s3c2416",
	"samsung,s3c2450",
	शून्य
पूर्ण;

DT_MACHINE_START(S3C2416_DT, "Samsung S3C2416 (Flattened Device Tree)")
	/* Maपूर्णांकainer: Heiko Stuebner <heiko@sntech.de> */
	.dt_compat	= s3c2416_dt_compat,
	.map_io		= s3c2416_dt_map_io,
	.init_irq	= irqchip_init,
	.init_machine	= s3c2416_dt_machine_init,
MACHINE_END
