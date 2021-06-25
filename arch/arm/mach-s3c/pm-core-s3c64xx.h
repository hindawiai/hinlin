<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *      Ben Dooks <ben@simtec.co.uk>
 *      http://armlinux.simtec.co.uk/
 *
 * S3C64XX - PM core support क्रम arch/arm/plat-s3c/pm.c
 */

#अगर_अघोषित __MACH_S3C64XX_PM_CORE_H
#घोषणा __MACH_S3C64XX_PM_CORE_H __खाता__

#समावेश <linux/serial_s3c.h>
#समावेश <linux/delay.h>

#समावेश "regs-gpio.h"
#समावेश "regs-clock.h"
#समावेश "map.h"

अटल अंतरभूत व्योम s3c_pm_debug_init_uart(व्योम)
अणु
#अगर_घोषित CONFIG_SAMSUNG_PM_DEBUG
	u32 पंचांगp = __raw_पढ़ोl(S3C_PCLK_GATE);

	/* As a note, since the S3C64XX UARTs generally have multiple
	 * घड़ी sources, we simply enable PCLK at the moment and hope
	 * that the resume settings क्रम the UART are suitable क्रम the
	 * use with PCLK.
	 */

	पंचांगp |= S3C_CLKCON_PCLK_UART0;
	पंचांगp |= S3C_CLKCON_PCLK_UART1;
	पंचांगp |= S3C_CLKCON_PCLK_UART2;
	पंचांगp |= S3C_CLKCON_PCLK_UART3;

	__raw_ग_लिखोl(पंचांगp, S3C_PCLK_GATE);
	udelay(10);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम s3c_pm_arch_prepare_irqs(व्योम)
अणु
	/* VIC should have alपढ़ोy been taken care of */

	/* clear any pending EINT0 पूर्णांकerrupts */
	__raw_ग_लिखोl(__raw_पढ़ोl(S3C64XX_EINT0PEND), S3C64XX_EINT0PEND);
पूर्ण

अटल अंतरभूत व्योम s3c_pm_arch_stop_घड़ीs(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम s3c_pm_arch_show_resume_irqs(व्योम)
अणु
पूर्ण

/* make these defines, we currently करो not have any need to change
 * the IRQ wake controls depending on the CPU we are running on */
#अगर_घोषित CONFIG_PM_SLEEP
#घोषणा s3c_irqwake_eपूर्णांकallow	((1 << 28) - 1)
#घोषणा s3c_irqwake_पूर्णांकallow	(~0)
#अन्यथा
#घोषणा s3c_irqwake_eपूर्णांकallow 0
#घोषणा s3c_irqwake_पूर्णांकallow  0
#पूर्ण_अगर

अटल अंतरभूत व्योम s3c_pm_restored_gpios(व्योम)
अणु
	/* ensure sleep mode has been cleared from the प्रणाली */

	__raw_ग_लिखोl(0, S3C64XX_SLPEN);
पूर्ण

अटल अंतरभूत व्योम samsung_pm_saved_gpios(व्योम)
अणु
	/* turn on the sleep mode and keep it there, as it seems that during
	 * suspend the xCON रेजिस्टरs get re-set and thus you can end up with
	 * problems between going to sleep and resuming.
	 */

	__raw_ग_लिखोl(S3C64XX_SLPEN_USE_xSLP, S3C64XX_SLPEN);
पूर्ण
#पूर्ण_अगर /* __MACH_S3C64XX_PM_CORE_H */
