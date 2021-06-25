<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2004-2006 Simtec Electronics
//   Ben Dooks <ben@simtec.co.uk>
//
// Samsung S3C2440 Mobile CPU support

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <यंत्र/irq.h>

#समावेश "devs.h"
#समावेश "cpu.h"
#समावेश "pm.h"

#समावेश "gpio-core.h"
#समावेश "gpio-cfg.h"
#समावेश "gpio-cfg-helpers.h"
#समावेश "gpio-samsung.h"

#समावेश "s3c24xx.h"

अटल काष्ठा device s3c2440_dev = अणु
	.bus		= &s3c2440_subsys,
पूर्ण;

पूर्णांक __init s3c2440_init(व्योम)
अणु
	prपूर्णांकk("S3C2440: Initialising architecture\n");

	/* change irq क्रम watchकरोg */

	s3c_device_wdt.resource[1].start = IRQ_S3C2440_WDT;
	s3c_device_wdt.resource[1].end   = IRQ_S3C2440_WDT;

	/* रेजिस्टर suspend/resume handlers */

#अगर_घोषित CONFIG_PM_SLEEP
	रेजिस्टर_syscore_ops(&s3c2410_pm_syscore_ops);
	रेजिस्टर_syscore_ops(&s3c24xx_irq_syscore_ops);
	रेजिस्टर_syscore_ops(&s3c244x_pm_syscore_ops);
#पूर्ण_अगर

	/* रेजिस्टर our प्रणाली device क्रम everything अन्यथा */

	वापस device_रेजिस्टर(&s3c2440_dev);
पूर्ण

व्योम __init s3c2440_map_io(व्योम)
अणु
	s3c244x_map_io();

	s3c24xx_gpiocfg_शेष.set_pull = s3c24xx_gpio_setpull_1up;
	s3c24xx_gpiocfg_शेष.get_pull = s3c24xx_gpio_getpull_1up;
पूर्ण
