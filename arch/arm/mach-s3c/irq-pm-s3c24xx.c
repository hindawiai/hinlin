<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2003-2004 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinux.simtec.co.uk/
//
// S3C24XX - IRQ PM code

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/पन.स>

#समावेश "cpu.h"
#समावेश "pm.h"
#समावेश <mach/map-base.h>
#समावेश "map-s3c.h"

#समावेश "regs-irq.h"
#समावेश "regs-gpio.h"
#समावेश "pm-core.h"

#समावेश <यंत्र/irq.h>

पूर्णांक s3c_irq_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक state)
अणु
	अचिन्हित दीर्घ irqbit = 1 << data->hwirq;

	अगर (!(s3c_irqwake_पूर्णांकallow & irqbit))
		वापस -ENOENT;

	pr_info("wake %s for hwirq %lu\n",
		state ? "enabled" : "disabled", data->hwirq);

	अगर (!state)
		s3c_irqwake_पूर्णांकmask |= irqbit;
	अन्यथा
		s3c_irqwake_पूर्णांकmask &= ~irqbit;

	वापस 0;
पूर्ण

अटल काष्ठा sleep_save irq_save[] = अणु
	SAVE_ITEM(S3C2410_INTMSK),
	SAVE_ITEM(S3C2410_INTSUBMSK),
पूर्ण;

/* the extपूर्णांक values move between the s3c2410/s3c2440 and the s3c2412
 * so we use an array to hold them, and to calculate the address of
 * the रेजिस्टर at run-समय
*/

अटल अचिन्हित दीर्घ save_extपूर्णांक[3];
अटल अचिन्हित दीर्घ save_eपूर्णांकflt[4];
अटल अचिन्हित दीर्घ save_eपूर्णांकmask;

अटल पूर्णांक s3c24xx_irq_suspend(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(save_extपूर्णांक); i++)
		save_extपूर्णांक[i] = __raw_पढ़ोl(S3C24XX_EXTINT0 + (i*4));

	क्रम (i = 0; i < ARRAY_SIZE(save_eपूर्णांकflt); i++)
		save_eपूर्णांकflt[i] = __raw_पढ़ोl(S3C24XX_EINFLT0 + (i*4));

	s3c_pm_करो_save(irq_save, ARRAY_SIZE(irq_save));
	save_eपूर्णांकmask = __raw_पढ़ोl(S3C24XX_EINTMASK);

	वापस 0;
पूर्ण

अटल व्योम s3c24xx_irq_resume(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(save_extपूर्णांक); i++)
		__raw_ग_लिखोl(save_extपूर्णांक[i], S3C24XX_EXTINT0 + (i*4));

	क्रम (i = 0; i < ARRAY_SIZE(save_eपूर्णांकflt); i++)
		__raw_ग_लिखोl(save_eपूर्णांकflt[i], S3C24XX_EINFLT0 + (i*4));

	s3c_pm_करो_restore(irq_save, ARRAY_SIZE(irq_save));
	__raw_ग_लिखोl(save_eपूर्णांकmask, S3C24XX_EINTMASK);
पूर्ण

काष्ठा syscore_ops s3c24xx_irq_syscore_ops = अणु
	.suspend	= s3c24xx_irq_suspend,
	.resume		= s3c24xx_irq_resume,
पूर्ण;

#अगर_घोषित CONFIG_CPU_S3C2416
अटल काष्ठा sleep_save s3c2416_irq_save[] = अणु
	SAVE_ITEM(S3C2416_INTMSK2),
पूर्ण;

अटल पूर्णांक s3c2416_irq_suspend(व्योम)
अणु
	s3c_pm_करो_save(s3c2416_irq_save, ARRAY_SIZE(s3c2416_irq_save));

	वापस 0;
पूर्ण

अटल व्योम s3c2416_irq_resume(व्योम)
अणु
	s3c_pm_करो_restore(s3c2416_irq_save, ARRAY_SIZE(s3c2416_irq_save));
पूर्ण

काष्ठा syscore_ops s3c2416_irq_syscore_ops = अणु
	.suspend	= s3c2416_irq_suspend,
	.resume		= s3c2416_irq_resume,
पूर्ण;
#पूर्ण_अगर
