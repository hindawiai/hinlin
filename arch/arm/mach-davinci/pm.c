<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DaVinci Power Management Routines
 *
 * Copyright (C) 2009 Texas Instruments, Inc. https://www.ti.com/
 */

#समावेश <linux/pm.h>
#समावेश <linux/suspend.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/पन.स>

#समावेश <mach/common.h>
#समावेश <mach/da8xx.h>
#समावेश <mach/mux.h>
#समावेश <mach/pm.h>

#समावेश "clock.h"
#समावेश "psc.h"
#समावेश "sram.h"

#घोषणा DA850_PLL1_BASE		0x01e1a000
#घोषणा DEEPSLEEP_SLEEPCOUNT_MASK	0xFFFF
#घोषणा DEEPSLEEP_SLEEPCOUNT		128

अटल व्योम (*davinci_sram_suspend) (काष्ठा davinci_pm_config *);
अटल काष्ठा davinci_pm_config pm_config = अणु
	.sleepcount = DEEPSLEEP_SLEEPCOUNT,
	.ddrpsc_num = DA8XX_LPSC1_EMIF3C,
पूर्ण;

अटल व्योम davinci_sram_push(व्योम *dest, व्योम *src, अचिन्हित पूर्णांक size)
अणु
	स_नकल(dest, src, size);
	flush_icache_range((अचिन्हित दीर्घ)dest, (अचिन्हित दीर्घ)(dest + size));
पूर्ण

अटल व्योम davinci_pm_suspend(व्योम)
अणु
	अचिन्हित val;

	अगर (pm_config.cpupll_reg_base != pm_config.ddrpll_reg_base) अणु

		/* Switch CPU PLL to bypass mode */
		val = __raw_पढ़ोl(pm_config.cpupll_reg_base + PLLCTL);
		val &= ~(PLLCTL_PLLENSRC | PLLCTL_PLLEN);
		__raw_ग_लिखोl(val, pm_config.cpupll_reg_base + PLLCTL);

		udelay(PLL_BYPASS_TIME);

		/* Powerकरोwn CPU PLL */
		val = __raw_पढ़ोl(pm_config.cpupll_reg_base + PLLCTL);
		val |= PLLCTL_PLLPWRDN;
		__raw_ग_लिखोl(val, pm_config.cpupll_reg_base + PLLCTL);
	पूर्ण

	/* Configure sleep count in deep sleep रेजिस्टर */
	val = __raw_पढ़ोl(pm_config.deepsleep_reg);
	val &= ~DEEPSLEEP_SLEEPCOUNT_MASK,
	val |= pm_config.sleepcount;
	__raw_ग_लिखोl(val, pm_config.deepsleep_reg);

	/* System goes to sleep in this call */
	davinci_sram_suspend(&pm_config);

	अगर (pm_config.cpupll_reg_base != pm_config.ddrpll_reg_base) अणु

		/* put CPU PLL in reset */
		val = __raw_पढ़ोl(pm_config.cpupll_reg_base + PLLCTL);
		val &= ~PLLCTL_PLLRST;
		__raw_ग_लिखोl(val, pm_config.cpupll_reg_base + PLLCTL);

		/* put CPU PLL in घातer करोwn */
		val = __raw_पढ़ोl(pm_config.cpupll_reg_base + PLLCTL);
		val &= ~PLLCTL_PLLPWRDN;
		__raw_ग_लिखोl(val, pm_config.cpupll_reg_base + PLLCTL);

		/* रुको क्रम CPU PLL reset */
		udelay(PLL_RESET_TIME);

		/* bring CPU PLL out of reset */
		val = __raw_पढ़ोl(pm_config.cpupll_reg_base + PLLCTL);
		val |= PLLCTL_PLLRST;
		__raw_ग_लिखोl(val, pm_config.cpupll_reg_base + PLLCTL);

		/* Wait क्रम CPU PLL to lock */
		udelay(PLL_LOCK_TIME);

		/* Remove CPU PLL from bypass mode */
		val = __raw_पढ़ोl(pm_config.cpupll_reg_base + PLLCTL);
		val &= ~PLLCTL_PLLENSRC;
		val |= PLLCTL_PLLEN;
		__raw_ग_लिखोl(val, pm_config.cpupll_reg_base + PLLCTL);
	पूर्ण
पूर्ण

अटल पूर्णांक davinci_pm_enter(suspend_state_t state)
अणु
	पूर्णांक ret = 0;

	चयन (state) अणु
	हाल PM_SUSPEND_MEM:
		davinci_pm_suspend();
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops davinci_pm_ops = अणु
	.enter		= davinci_pm_enter,
	.valid		= suspend_valid_only_mem,
पूर्ण;

पूर्णांक __init davinci_pm_init(व्योम)
अणु
	पूर्णांक ret;

	ret = davinci_cfg_reg(DA850_RTC_ALARM);
	अगर (ret)
		वापस ret;

	pm_config.ddr2_ctlr_base = da8xx_get_mem_ctlr();
	pm_config.deepsleep_reg = DA8XX_SYSCFG1_VIRT(DA8XX_DEEPSLEEP_REG);

	pm_config.cpupll_reg_base = ioremap(DA8XX_PLL0_BASE, SZ_4K);
	अगर (!pm_config.cpupll_reg_base)
		वापस -ENOMEM;

	pm_config.ddrpll_reg_base = ioremap(DA850_PLL1_BASE, SZ_4K);
	अगर (!pm_config.ddrpll_reg_base) अणु
		ret = -ENOMEM;
		जाओ no_ddrpll_mem;
	पूर्ण

	pm_config.ddrpsc_reg_base = ioremap(DA8XX_PSC1_BASE, SZ_4K);
	अगर (!pm_config.ddrpsc_reg_base) अणु
		ret = -ENOMEM;
		जाओ no_ddrpsc_mem;
	पूर्ण

	davinci_sram_suspend = sram_alloc(davinci_cpu_suspend_sz, शून्य);
	अगर (!davinci_sram_suspend) अणु
		pr_err("PM: cannot allocate SRAM memory\n");
		ret = -ENOMEM;
		जाओ no_sram_mem;
	पूर्ण

	davinci_sram_push(davinci_sram_suspend, davinci_cpu_suspend,
						davinci_cpu_suspend_sz);

	suspend_set_ops(&davinci_pm_ops);

	वापस 0;

no_sram_mem:
	iounmap(pm_config.ddrpsc_reg_base);
no_ddrpsc_mem:
	iounmap(pm_config.ddrpll_reg_base);
no_ddrpll_mem:
	iounmap(pm_config.cpupll_reg_base);
	वापस ret;
पूर्ण
