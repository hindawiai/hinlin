<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2004-2005 Simtec Electronics
//	http://armlinux.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>
//
// S3C2442 core and lock support

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mutex.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/irq.h>

#समावेश "regs-clock.h"

#समावेश "cpu.h"
#समावेश "pm.h"

#समावेश "gpio-core.h"
#समावेश "gpio-cfg.h"
#समावेश "gpio-cfg-helpers.h"
#समावेश "gpio-samsung.h"

#समावेश "s3c24xx.h"

अटल काष्ठा device s3c2442_dev = अणु
	.bus		= &s3c2442_subsys,
पूर्ण;

पूर्णांक __init s3c2442_init(व्योम)
अणु
	prपूर्णांकk("S3C2442: Initialising architecture\n");

#अगर_घोषित CONFIG_PM_SLEEP
	रेजिस्टर_syscore_ops(&s3c2410_pm_syscore_ops);
	रेजिस्टर_syscore_ops(&s3c24xx_irq_syscore_ops);
	रेजिस्टर_syscore_ops(&s3c244x_pm_syscore_ops);
#पूर्ण_अगर

	वापस device_रेजिस्टर(&s3c2442_dev);
पूर्ण

व्योम __init s3c2442_map_io(व्योम)
अणु
	s3c244x_map_io();

	s3c24xx_gpiocfg_शेष.set_pull = s3c24xx_gpio_setpull_1करोwn;
	s3c24xx_gpiocfg_शेष.get_pull = s3c24xx_gpio_getpull_1करोwn;
पूर्ण
