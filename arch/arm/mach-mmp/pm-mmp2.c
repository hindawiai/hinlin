<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MMP2 Power Management Routines
 *
 * (C) Copyright 2012 Marvell International Ltd.
 * All Rights Reserved
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/समय.स>
#समावेश <linux/delay.h>
#समावेश <linux/suspend.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <linux/soc/mmp/cputype.h>
#समावेश "addr-map.h"
#समावेश "pm-mmp2.h"
#समावेश "regs-icu.h"
#समावेश "irqs.h"

पूर्णांक mmp2_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	अचिन्हित दीर्घ data = 0;
	पूर्णांक irq = d->irq;

	/* enable wakeup sources */
	चयन (irq) अणु
	हाल IRQ_MMP2_RTC:
	हाल IRQ_MMP2_RTC_ALARM:
		data = MPMU_WUCRM_PJ_WAKEUP(4) | MPMU_WUCRM_PJ_RTC_ALARM;
		अवरोध;
	हाल IRQ_MMP2_PMIC:
		data = MPMU_WUCRM_PJ_WAKEUP(7);
		अवरोध;
	हाल IRQ_MMP2_MMC2:
		/* mmc use WAKEUP2, same as GPIO wakeup source */
		data = MPMU_WUCRM_PJ_WAKEUP(2);
		अवरोध;
	पूर्ण
	अगर (on) अणु
		अगर (data) अणु
			data |= __raw_पढ़ोl(MPMU_WUCRM_PJ);
			__raw_ग_लिखोl(data, MPMU_WUCRM_PJ);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (data) अणु
			data = ~data & __raw_पढ़ोl(MPMU_WUCRM_PJ);
			__raw_ग_लिखोl(data, MPMU_WUCRM_PJ);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pm_scu_clk_disable(व्योम)
अणु
	अचिन्हित पूर्णांक val;

	/* बंद AXI fabric घड़ी gate */
	__raw_ग_लिखोl(0x0, CIU_REG(0x64));
	__raw_ग_लिखोl(0x0, CIU_REG(0x68));

	/* बंद MCB master घड़ी gate */
	val = __raw_पढ़ोl(CIU_REG(0x1c));
	val |= 0xf0;
	__raw_ग_लिखोl(val, CIU_REG(0x1c));

	वापस ;
पूर्ण

अटल व्योम pm_scu_clk_enable(व्योम)
अणु
	अचिन्हित पूर्णांक val;

	/* खोलो AXI fabric घड़ी gate */
	__raw_ग_लिखोl(0x03003003, CIU_REG(0x64));
	__raw_ग_लिखोl(0x00303030, CIU_REG(0x68));

	/* खोलो MCB master घड़ी gate */
	val = __raw_पढ़ोl(CIU_REG(0x1c));
	val &= ~(0xf0);
	__raw_ग_लिखोl(val, CIU_REG(0x1c));

	वापस ;
पूर्ण

अटल व्योम pm_mpmu_clk_disable(व्योम)
अणु
	/*
	 * disable घड़ीs in MPMU_CGR_PJ रेजिस्टर
	 * except घड़ी क्रम APMU_PLL1, APMU_PLL1_2 and AP_26M
	 */
	__raw_ग_लिखोl(0x0000a010, MPMU_CGR_PJ);
पूर्ण

अटल व्योम pm_mpmu_clk_enable(व्योम)
अणु
	अचिन्हित पूर्णांक val;

	__raw_ग_लिखोl(0xdffefffe, MPMU_CGR_PJ);
	val = __raw_पढ़ोl(MPMU_PLL2_CTRL1);
	val |= (1 << 29);
	__raw_ग_लिखोl(val, MPMU_PLL2_CTRL1);

	वापस ;
पूर्ण

व्योम mmp2_pm_enter_lowघातer_mode(पूर्णांक state)
अणु
	uपूर्णांक32_t idle_cfg, apcr;

	idle_cfg = __raw_पढ़ोl(APMU_PJ_IDLE_CFG);
	apcr = __raw_पढ़ोl(MPMU_PCR_PJ);
	apcr &= ~(MPMU_PCR_PJ_SLPEN | MPMU_PCR_PJ_DDRCORSD | MPMU_PCR_PJ_APBSD
		 | MPMU_PCR_PJ_AXISD | MPMU_PCR_PJ_VCTCXOSD | (1 << 13));
	idle_cfg &= ~APMU_PJ_IDLE_CFG_PJ_IDLE;

	चयन (state) अणु
	हाल POWER_MODE_SYS_SLEEP:
		apcr |= MPMU_PCR_PJ_SLPEN;		/* set the SLPEN bit */
		apcr |= MPMU_PCR_PJ_VCTCXOSD;		/* set VCTCXOSD */
		fallthrough;
	हाल POWER_MODE_CHIP_SLEEP:
		apcr |= MPMU_PCR_PJ_SLPEN;
		fallthrough;
	हाल POWER_MODE_APPS_SLEEP:
		apcr |= MPMU_PCR_PJ_APBSD;		/* set APBSD */
		fallthrough;
	हाल POWER_MODE_APPS_IDLE:
		apcr |= MPMU_PCR_PJ_AXISD;		/* set AXISDD bit */
		apcr |= MPMU_PCR_PJ_DDRCORSD;		/* set DDRCORSD bit */
		idle_cfg |= APMU_PJ_IDLE_CFG_PJ_PWRDWN;	/* PJ घातer करोwn */
		apcr |= MPMU_PCR_PJ_SPSD;
		fallthrough;
	हाल POWER_MODE_CORE_EXTIDLE:
		idle_cfg |= APMU_PJ_IDLE_CFG_PJ_IDLE;	/* set the IDLE bit */
		idle_cfg &= ~APMU_PJ_IDLE_CFG_ISO_MODE_CNTRL_MASK;
		idle_cfg |= APMU_PJ_IDLE_CFG_PWR_SW(3)
			| APMU_PJ_IDLE_CFG_L2_PWR_SW;
		अवरोध;
	हाल POWER_MODE_CORE_INTIDLE:
		apcr &= ~MPMU_PCR_PJ_SPSD;
		अवरोध;
	पूर्ण

	/* set reserve bits */
	apcr |= (1 << 30) | (1 << 25);

	/* finally ग_लिखो the रेजिस्टरs back */
	__raw_ग_लिखोl(idle_cfg, APMU_PJ_IDLE_CFG);
	__raw_ग_लिखोl(apcr, MPMU_PCR_PJ);	/* 0xfe086000 */
पूर्ण

अटल पूर्णांक mmp2_pm_enter(suspend_state_t state)
अणु
	पूर्णांक temp;

	temp = __raw_पढ़ोl(MMP2_ICU_INT4_MASK);
	अगर (temp & (1 << 1)) अणु
		prपूर्णांकk(KERN_ERR "%s: PMIC interrupt is handling\n", __func__);
		वापस -EAGAIN;
	पूर्ण

	temp = __raw_पढ़ोl(APMU_SRAM_PWR_DWN);
	temp |= ((1 << 19) | (1 << 18));
	__raw_ग_लिखोl(temp, APMU_SRAM_PWR_DWN);
	pm_mpmu_clk_disable();
	pm_scu_clk_disable();

	prपूर्णांकk(KERN_INFO "%s: before suspend\n", __func__);
	cpu_करो_idle();
	prपूर्णांकk(KERN_INFO "%s: after suspend\n", __func__);

	pm_mpmu_clk_enable();		/* enable घड़ीs in MPMU */
	pm_scu_clk_enable();		/* enable घड़ीs in SCU */

	वापस 0;
पूर्ण

/*
 * Called after processes are frozen, but beक्रमe we shut करोwn devices.
 */
अटल पूर्णांक mmp2_pm_prepare(व्योम)
अणु
	mmp2_pm_enter_lowघातer_mode(POWER_MODE_SYS_SLEEP);

	वापस 0;
पूर्ण

/*
 * Called after devices are re-setup, but beक्रमe processes are thawed.
 */
अटल व्योम mmp2_pm_finish(व्योम)
अणु
	mmp2_pm_enter_lowघातer_mode(POWER_MODE_CORE_INTIDLE);
पूर्ण

अटल पूर्णांक mmp2_pm_valid(suspend_state_t state)
अणु
	वापस ((state == PM_SUSPEND_STANDBY) || (state == PM_SUSPEND_MEM));
पूर्ण

/*
 * Set to PM_DISK_FIRMWARE so we can quickly veto suspend-to-disk.
 */
अटल स्थिर काष्ठा platक्रमm_suspend_ops mmp2_pm_ops = अणु
	.valid		= mmp2_pm_valid,
	.prepare	= mmp2_pm_prepare,
	.enter		= mmp2_pm_enter,
	.finish		= mmp2_pm_finish,
पूर्ण;

अटल पूर्णांक __init mmp2_pm_init(व्योम)
अणु
	uपूर्णांक32_t apcr;

	अगर (!cpu_is_mmp2())
		वापस -EIO;

	suspend_set_ops(&mmp2_pm_ops);

	/*
	 * Set bit 0, Slow घड़ी Select 32K घड़ी input instead of VCXO
	 * VCXO is chosen by शेष, which would be disabled in suspend
	 */
	__raw_ग_लिखोl(0x5, MPMU_SCCR);

	/*
	 * Clear bit 23 of CIU_CPU_CONF
	 * direct PJ4 to DDR access through Memory Controller slow queue
	 * fast queue has issue and cause lcd will flick
	 */
	__raw_ग_लिखोl(__raw_पढ़ोl(CIU_REG(0x8)) & ~(0x1 << 23), CIU_REG(0x8));

	/* Clear शेष low घातer control bit */
	apcr = __raw_पढ़ोl(MPMU_PCR_PJ);
	apcr &= ~(MPMU_PCR_PJ_SLPEN | MPMU_PCR_PJ_DDRCORSD
			| MPMU_PCR_PJ_APBSD | MPMU_PCR_PJ_AXISD | 1 << 13);
	__raw_ग_लिखोl(apcr, MPMU_PCR_PJ);

	वापस 0;
पूर्ण

late_initcall(mmp2_pm_init);
