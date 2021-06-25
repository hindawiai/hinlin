<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2008 Simtec Electronics
 *      Ben Dooks <ben@simtec.co.uk>
 *      http://armlinux.simtec.co.uk/
 *
 * S3C24xx - PM core support क्रम arch/arm/plat-s3c/pm.c
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>

#समावेश "regs-clock.h"
#समावेश "regs-irq-s3c24xx.h"
#समावेश <mach/irqs.h>

अटल अंतरभूत व्योम s3c_pm_debug_init_uart(व्योम)
अणु
#अगर_घोषित CONFIG_SAMSUNG_PM_DEBUG
	अचिन्हित दीर्घ पंचांगp = __raw_पढ़ोl(S3C2410_CLKCON);

	/* re-start uart घड़ीs */
	पंचांगp |= S3C2410_CLKCON_UART0;
	पंचांगp |= S3C2410_CLKCON_UART1;
	पंचांगp |= S3C2410_CLKCON_UART2;

	__raw_ग_लिखोl(पंचांगp, S3C2410_CLKCON);
	udelay(10);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम s3c_pm_arch_prepare_irqs(व्योम)
अणु
	__raw_ग_लिखोl(s3c_irqwake_पूर्णांकmask, S3C2410_INTMSK);
	__raw_ग_लिखोl(s3c_irqwake_eपूर्णांकmask, S3C2410_EINTMASK);

	/* ack any outstanding बाह्यal पूर्णांकerrupts beक्रमe we go to sleep */

	__raw_ग_लिखोl(__raw_पढ़ोl(S3C2410_EINTPEND), S3C2410_EINTPEND);
	__raw_ग_लिखोl(__raw_पढ़ोl(S3C2410_INTPND), S3C2410_INTPND);
	__raw_ग_लिखोl(__raw_पढ़ोl(S3C2410_SRCPND), S3C2410_SRCPND);

पूर्ण

अटल अंतरभूत व्योम s3c_pm_arch_stop_घड़ीs(व्योम)
अणु
	__raw_ग_लिखोl(0x00, S3C2410_CLKCON);  /* turn off घड़ीs over sleep */
पूर्ण

/* s3c2410_pm_show_resume_irqs
 *
 * prपूर्णांक any IRQs निश्चितed at resume समय (ie, we woke from)
*/
अटल अंतरभूत व्योम s3c_pm_show_resume_irqs(पूर्णांक start, अचिन्हित दीर्घ which,
					   अचिन्हित दीर्घ mask)
अणु
	पूर्णांक i;

	which &= ~mask;

	क्रम (i = 0; i <= 31; i++) अणु
		अगर (which & (1L<<i)) अणु
			S3C_PMDBG("IRQ %d asserted at resume\n", start+i);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम s3c_pm_arch_show_resume_irqs(व्योम)
अणु
	S3C_PMDBG("post sleep: IRQs 0x%08x, 0x%08x\n",
		  __raw_पढ़ोl(S3C2410_SRCPND),
		  __raw_पढ़ोl(S3C2410_EINTPEND));

	s3c_pm_show_resume_irqs(IRQ_EINT0, __raw_पढ़ोl(S3C2410_SRCPND),
				s3c_irqwake_पूर्णांकmask);

	s3c_pm_show_resume_irqs(IRQ_EINT4-4, __raw_पढ़ोl(S3C2410_EINTPEND),
				s3c_irqwake_eपूर्णांकmask);
पूर्ण

अटल अंतरभूत व्योम s3c_pm_restored_gpios(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम samsung_pm_saved_gpios(व्योम) अणु पूर्ण

/* state क्रम IRQs over sleep */

/* शेष is to allow क्रम EINT0..EINT15, and IRQ_RTC as wakeup sources
 *
 * set bit to 1 in allow bitfield to enable the wakeup settings on it
*/
#अगर_घोषित CONFIG_PM_SLEEP
#घोषणा s3c_irqwake_पूर्णांकallow	(1L << 30 | 0xfL)
#घोषणा s3c_irqwake_eपूर्णांकallow	(0x0000fff0L)
#अन्यथा
#घोषणा s3c_irqwake_eपूर्णांकallow 0
#घोषणा s3c_irqwake_पूर्णांकallow  0
#पूर्ण_अगर
