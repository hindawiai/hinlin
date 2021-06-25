<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2008 Openmoko, Inc.
// Copyright 2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinux.simtec.co.uk/
//
// S3C64XX CPU PM support.

#समावेश <linux/init.h>
#समावेश <linux/suspend.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/pm_करोमुख्य.h>

#समावेश "map.h"
#समावेश <mach/irqs.h>

#समावेश "cpu.h"
#समावेश "devs.h"
#समावेश "pm.h"
#समावेश "wakeup-mask.h"

#समावेश "regs-gpio.h"
#समावेश "regs-clock.h"
#समावेश "gpio-samsung.h"

#समावेश "regs-gpio-memport-s3c64xx.h"
#समावेश "regs-modem-s3c64xx.h"
#समावेश "regs-sys-s3c64xx.h"
#समावेश "regs-syscon-power-s3c64xx.h"

काष्ठा s3c64xx_pm_करोमुख्य अणु
	अक्षर *स्थिर name;
	u32 ena;
	u32 pwr_stat;
	काष्ठा generic_pm_करोमुख्य pd;
पूर्ण;

अटल पूर्णांक s3c64xx_pd_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा s3c64xx_pm_करोमुख्य *pd;
	u32 val;

	pd = container_of(करोमुख्य, काष्ठा s3c64xx_pm_करोमुख्य, pd);

	val = __raw_पढ़ोl(S3C64XX_NORMAL_CFG);
	val &= ~(pd->ena);
	__raw_ग_लिखोl(val, S3C64XX_NORMAL_CFG);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c64xx_pd_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा s3c64xx_pm_करोमुख्य *pd;
	u32 val;
	दीर्घ retry = 1000000L;

	pd = container_of(करोमुख्य, काष्ठा s3c64xx_pm_करोमुख्य, pd);

	val = __raw_पढ़ोl(S3C64XX_NORMAL_CFG);
	val |= pd->ena;
	__raw_ग_लिखोl(val, S3C64XX_NORMAL_CFG);

	/* Not all करोमुख्यs provide घातer status पढ़ोback */
	अगर (pd->pwr_stat) अणु
		करो अणु
			cpu_relax();
			अगर (__raw_पढ़ोl(S3C64XX_BLK_PWR_STAT) & pd->pwr_stat)
				अवरोध;
		पूर्ण जबतक (retry--);

		अगर (!retry) अणु
			pr_err("Failed to start domain %s\n", pd->name);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा s3c64xx_pm_करोमुख्य s3c64xx_pm_irom = अणु
	.name = "IROM",
	.ena = S3C64XX_NORMALCFG_IROM_ON,
	.pd = अणु
		.घातer_off = s3c64xx_pd_off,
		.घातer_on = s3c64xx_pd_on,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c64xx_pm_करोमुख्य s3c64xx_pm_eपंचांग = अणु
	.name = "ETM",
	.ena = S3C64XX_NORMALCFG_DOMAIN_ETM_ON,
	.pwr_stat = S3C64XX_BLKPWRSTAT_ETM,
	.pd = अणु
		.घातer_off = s3c64xx_pd_off,
		.घातer_on = s3c64xx_pd_on,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c64xx_pm_करोमुख्य s3c64xx_pm_s = अणु
	.name = "S",
	.ena = S3C64XX_NORMALCFG_DOMAIN_S_ON,
	.pwr_stat = S3C64XX_BLKPWRSTAT_S,
	.pd = अणु
		.घातer_off = s3c64xx_pd_off,
		.घातer_on = s3c64xx_pd_on,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c64xx_pm_करोमुख्य s3c64xx_pm_f = अणु
	.name = "F",
	.ena = S3C64XX_NORMALCFG_DOMAIN_F_ON,
	.pwr_stat = S3C64XX_BLKPWRSTAT_F,
	.pd = अणु
		.घातer_off = s3c64xx_pd_off,
		.घातer_on = s3c64xx_pd_on,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c64xx_pm_करोमुख्य s3c64xx_pm_p = अणु
	.name = "P",
	.ena = S3C64XX_NORMALCFG_DOMAIN_P_ON,
	.pwr_stat = S3C64XX_BLKPWRSTAT_P,
	.pd = अणु
		.घातer_off = s3c64xx_pd_off,
		.घातer_on = s3c64xx_pd_on,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c64xx_pm_करोमुख्य s3c64xx_pm_i = अणु
	.name = "I",
	.ena = S3C64XX_NORMALCFG_DOMAIN_I_ON,
	.pwr_stat = S3C64XX_BLKPWRSTAT_I,
	.pd = अणु
		.घातer_off = s3c64xx_pd_off,
		.घातer_on = s3c64xx_pd_on,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c64xx_pm_करोमुख्य s3c64xx_pm_g = अणु
	.name = "G",
	.ena = S3C64XX_NORMALCFG_DOMAIN_G_ON,
	.pd = अणु
		.घातer_off = s3c64xx_pd_off,
		.घातer_on = s3c64xx_pd_on,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c64xx_pm_करोमुख्य s3c64xx_pm_v = अणु
	.name = "V",
	.ena = S3C64XX_NORMALCFG_DOMAIN_V_ON,
	.pwr_stat = S3C64XX_BLKPWRSTAT_V,
	.pd = अणु
		.घातer_off = s3c64xx_pd_off,
		.घातer_on = s3c64xx_pd_on,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c64xx_pm_करोमुख्य *s3c64xx_always_on_pm_करोमुख्यs[] = अणु
	&s3c64xx_pm_irom,
पूर्ण;

अटल काष्ठा s3c64xx_pm_करोमुख्य *s3c64xx_pm_करोमुख्यs[] = अणु
	&s3c64xx_pm_eपंचांग,
	&s3c64xx_pm_g,
	&s3c64xx_pm_v,
	&s3c64xx_pm_i,
	&s3c64xx_pm_p,
	&s3c64xx_pm_s,
	&s3c64xx_pm_f,
पूर्ण;

#अगर_घोषित CONFIG_S3C_PM_DEBUG_LED_SMDK
व्योम s3c_pm_debug_smdkled(u32 set, u32 clear)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	local_irq_save(flags);
	क्रम (i = 0; i < 4; i++) अणु
		अगर (clear & (1 << i))
			gpio_set_value(S3C64XX_GPN(12 + i), 0);
		अगर (set & (1 << i))
			gpio_set_value(S3C64XX_GPN(12 + i), 1);
	पूर्ण
	local_irq_restore(flags);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल काष्ठा sleep_save core_save[] = अणु
	SAVE_ITEM(S3C64XX_MEM0DRVCON),
	SAVE_ITEM(S3C64XX_MEM1DRVCON),
पूर्ण;

अटल काष्ठा sleep_save misc_save[] = अणु
	SAVE_ITEM(S3C64XX_AHB_CON0),
	SAVE_ITEM(S3C64XX_AHB_CON1),
	SAVE_ITEM(S3C64XX_AHB_CON2),
	
	SAVE_ITEM(S3C64XX_SPCON),

	SAVE_ITEM(S3C64XX_MEM0CONSTOP),
	SAVE_ITEM(S3C64XX_MEM1CONSTOP),
	SAVE_ITEM(S3C64XX_MEM0CONSLP0),
	SAVE_ITEM(S3C64XX_MEM0CONSLP1),
	SAVE_ITEM(S3C64XX_MEM1CONSLP),

	SAVE_ITEM(S3C64XX_SDMA_SEL),
	SAVE_ITEM(S3C64XX_MODEM_MIFPCON),

	SAVE_ITEM(S3C64XX_NORMAL_CFG),
पूर्ण;

व्योम s3c_pm_configure_extपूर्णांक(व्योम)
अणु
	__raw_ग_लिखोl(s3c_irqwake_eपूर्णांकmask, S3C64XX_EINT_MASK);
पूर्ण

व्योम s3c_pm_restore_core(व्योम)
अणु
	__raw_ग_लिखोl(0, S3C64XX_EINT_MASK);

	s3c_pm_debug_smdkled(1 << 2, 0);

	s3c_pm_करो_restore_core(core_save, ARRAY_SIZE(core_save));
	s3c_pm_करो_restore(misc_save, ARRAY_SIZE(misc_save));
पूर्ण

व्योम s3c_pm_save_core(व्योम)
अणु
	s3c_pm_करो_save(misc_save, ARRAY_SIZE(misc_save));
	s3c_pm_करो_save(core_save, ARRAY_SIZE(core_save));
पूर्ण
#पूर्ण_अगर

/* since both s3c6400 and s3c6410 share the same sleep pm calls, we
 * put the per-cpu code in here until any new cpu comes aदीर्घ and changes
 * this.
 */

अटल पूर्णांक s3c64xx_cpu_suspend(अचिन्हित दीर्घ arg)
अणु
	अचिन्हित दीर्घ पंचांगp;

	/* set our standby method to sleep */

	पंचांगp = __raw_पढ़ोl(S3C64XX_PWR_CFG);
	पंचांगp &= ~S3C64XX_PWRCFG_CFG_WFI_MASK;
	पंचांगp |= S3C64XX_PWRCFG_CFG_WFI_SLEEP;
	__raw_ग_लिखोl(पंचांगp, S3C64XX_PWR_CFG);

	/* clear any old wakeup */

	__raw_ग_लिखोl(__raw_पढ़ोl(S3C64XX_WAKEUP_STAT),
		     S3C64XX_WAKEUP_STAT);

	/* set the LED state to 0110 over sleep */
	s3c_pm_debug_smdkled(3 << 1, 0xf);

	/* issue the standby संकेत पूर्णांकo the pm unit. Note, we
	 * issue a ग_लिखो-buffer drain just in हाल */

	पंचांगp = 0;

	यंत्र("b 1f\n\t"
	    ".align 5\n\t"
	    "1:\n\t"
	    "mcr p15, 0, %0, c7, c10, 5\n\t"
	    "mcr p15, 0, %0, c7, c10, 4\n\t"
	    "mcr p15, 0, %0, c7, c0, 4" :: "r" (पंचांगp));

	/* we should never get past here */

	pr_info("Failed to suspend the system\n");
	वापस 1; /* Aborting suspend */
पूर्ण

/* mapping of पूर्णांकerrupts to parts of the wakeup mask */
अटल स्थिर काष्ठा samsung_wakeup_mask wake_irqs[] = अणु
	अणु .irq = IRQ_RTC_ALARM,	.bit = S3C64XX_PWRCFG_RTC_ALARM_DISABLE, पूर्ण,
	अणु .irq = IRQ_RTC_TIC,	.bit = S3C64XX_PWRCFG_RTC_TICK_DISABLE, पूर्ण,
	अणु .irq = IRQ_PENDN,	.bit = S3C64XX_PWRCFG_TS_DISABLE, पूर्ण,
	अणु .irq = IRQ_HSMMC0,	.bit = S3C64XX_PWRCFG_MMC0_DISABLE, पूर्ण,
	अणु .irq = IRQ_HSMMC1,	.bit = S3C64XX_PWRCFG_MMC1_DISABLE, पूर्ण,
	अणु .irq = IRQ_HSMMC2,	.bit = S3C64XX_PWRCFG_MMC2_DISABLE, पूर्ण,
	अणु .irq = NO_WAKEUP_IRQ,	.bit = S3C64XX_PWRCFG_BATF_DISABLEपूर्ण,
	अणु .irq = NO_WAKEUP_IRQ,	.bit = S3C64XX_PWRCFG_MSM_DISABLE पूर्ण,
	अणु .irq = NO_WAKEUP_IRQ,	.bit = S3C64XX_PWRCFG_HSI_DISABLE पूर्ण,
	अणु .irq = NO_WAKEUP_IRQ,	.bit = S3C64XX_PWRCFG_MSM_DISABLE पूर्ण,
पूर्ण;

अटल व्योम s3c64xx_pm_prepare(व्योम)
अणु
	samsung_sync_wakemask(S3C64XX_PWR_CFG,
			      wake_irqs, ARRAY_SIZE(wake_irqs));

	/* store address of resume. */
	__raw_ग_लिखोl(__pa_symbol(s3c_cpu_resume), S3C64XX_INFORM0);

	/* ensure previous wakeup state is cleared beक्रमe sleeping */
	__raw_ग_लिखोl(__raw_पढ़ोl(S3C64XX_WAKEUP_STAT), S3C64XX_WAKEUP_STAT);
पूर्ण

#अगर_घोषित CONFIG_SAMSUNG_PM_DEBUG
व्योम s3c_pm_arch_update_uart(व्योम __iomem *regs, काष्ठा pm_uart_save *save)
अणु
	u32 ucon;
	u32 ucon_clk
	u32 save_clk;
	u32 new_ucon;
	u32 delta;

	अगर (!soc_is_s3c64xx())
		वापस;

	ucon = __raw_पढ़ोl(regs + S3C2410_UCON);
	ucon_clk = ucon & S3C6400_UCON_CLKMASK;
	sav_clk = save->ucon & S3C6400_UCON_CLKMASK;

	/* S3C64XX UART blocks only support level पूर्णांकerrupts, so ensure that
	 * when we restore unused UART blocks we क्रमce the level पूर्णांकerrupt
	 * settigs. */
	save->ucon |= S3C2410_UCON_TXILEVEL | S3C2410_UCON_RXILEVEL;

	/* We have a स्थिरraपूर्णांक on changing the घड़ी type of the UART
	 * between UCLKx and PCLK, so ensure that when we restore UCON
	 * that the CLK field is correctly modअगरied अगर the bootloader
	 * has changed anything.
	 */
	अगर (ucon_clk != save_clk) अणु
		new_ucon = save->ucon;
		delta = ucon_clk ^ save_clk;

		/* change from UCLKx => wrong PCLK,
		 * either UCLK can be tested क्रम by a bit-test
		 * with UCLK0 */
		अगर (ucon_clk & S3C6400_UCON_UCLK0 &&
		    !(save_clk & S3C6400_UCON_UCLK0) &&
		    delta & S3C6400_UCON_PCLK2) अणु
			new_ucon &= ~S3C6400_UCON_UCLK0;
		पूर्ण अन्यथा अगर (delta == S3C6400_UCON_PCLK2) अणु
			/* as an precaution, करोn't change from
			 * PCLK2 => PCLK or vice-versa */
			new_ucon ^= S3C6400_UCON_PCLK2;
		पूर्ण

		S3C_PMDBG("ucon change %04x => %04x (save=%04x)\n",
			  ucon, new_ucon, save->ucon);
		save->ucon = new_ucon;
	पूर्ण
पूर्ण
#पूर्ण_अगर

पूर्णांक __init s3c64xx_pm_init(व्योम)
अणु
	पूर्णांक i;

	s3c_pm_init();

	क्रम (i = 0; i < ARRAY_SIZE(s3c64xx_always_on_pm_करोमुख्यs); i++)
		pm_genpd_init(&s3c64xx_always_on_pm_करोमुख्यs[i]->pd,
			      &pm_करोमुख्य_always_on_gov, false);

	क्रम (i = 0; i < ARRAY_SIZE(s3c64xx_pm_करोमुख्यs); i++)
		pm_genpd_init(&s3c64xx_pm_करोमुख्यs[i]->pd, शून्य, false);

#अगर_घोषित CONFIG_S3C_DEV_FB
	अगर (dev_get_platdata(&s3c_device_fb.dev))
		pm_genpd_add_device(&s3c64xx_pm_f.pd, &s3c_device_fb.dev);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल __init पूर्णांक s3c64xx_pm_initcall(व्योम)
अणु
	अगर (!soc_is_s3c64xx())
		वापस 0;

	pm_cpu_prep = s3c64xx_pm_prepare;
	pm_cpu_sleep = s3c64xx_cpu_suspend;

#अगर_घोषित CONFIG_S3C_PM_DEBUG_LED_SMDK
	gpio_request(S3C64XX_GPN(12), "DEBUG_LED0");
	gpio_request(S3C64XX_GPN(13), "DEBUG_LED1");
	gpio_request(S3C64XX_GPN(14), "DEBUG_LED2");
	gpio_request(S3C64XX_GPN(15), "DEBUG_LED3");
	gpio_direction_output(S3C64XX_GPN(12), 0);
	gpio_direction_output(S3C64XX_GPN(13), 0);
	gpio_direction_output(S3C64XX_GPN(14), 0);
	gpio_direction_output(S3C64XX_GPN(15), 0);
#पूर्ण_अगर

	वापस 0;
पूर्ण
arch_initcall(s3c64xx_pm_initcall);
