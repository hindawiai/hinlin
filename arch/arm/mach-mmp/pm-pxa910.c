<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PXA910 Power Management Routines
 *
 * (C) Copyright 2009 Marvell International Ltd.
 * All Rights Reserved
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/समय.स>
#समावेश <linux/delay.h>
#समावेश <linux/suspend.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/outercache.h>

#समावेश <linux/soc/mmp/cputype.h>
#समावेश "addr-map.h"
#समावेश "pm-pxa910.h"
#समावेश "regs-icu.h"
#समावेश "irqs.h"

पूर्णांक pxa910_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	uपूर्णांक32_t awucrm = 0, apcr = 0;
	पूर्णांक irq = data->irq;

	/* setting wakeup sources */
	चयन (irq) अणु
	/* wakeup line 2 */
	हाल IRQ_PXA910_AP_GPIO:
		awucrm = MPMU_AWUCRM_WAKEUP(2);
		apcr |= MPMU_APCR_SLPWP2;
		अवरोध;
	/* wakeup line 3 */
	हाल IRQ_PXA910_KEYPAD:
		awucrm = MPMU_AWUCRM_WAKEUP(3) | MPMU_AWUCRM_KEYPRESS;
		apcr |= MPMU_APCR_SLPWP3;
		अवरोध;
	हाल IRQ_PXA910_ROTARY:
		awucrm = MPMU_AWUCRM_WAKEUP(3) | MPMU_AWUCRM_NEWROTARY;
		apcr |= MPMU_APCR_SLPWP3;
		अवरोध;
	हाल IRQ_PXA910_TRACKBALL:
		awucrm = MPMU_AWUCRM_WAKEUP(3) | MPMU_AWUCRM_TRACKBALL;
		apcr |= MPMU_APCR_SLPWP3;
		अवरोध;
	/* wakeup line 4 */
	हाल IRQ_PXA910_AP1_TIMER1:
		awucrm = MPMU_AWUCRM_WAKEUP(4) | MPMU_AWUCRM_AP1_TIMER_1;
		apcr |= MPMU_APCR_SLPWP4;
		अवरोध;
	हाल IRQ_PXA910_AP1_TIMER2:
		awucrm = MPMU_AWUCRM_WAKEUP(4) | MPMU_AWUCRM_AP1_TIMER_2;
		apcr |= MPMU_APCR_SLPWP4;
		अवरोध;
	हाल IRQ_PXA910_AP1_TIMER3:
		awucrm = MPMU_AWUCRM_WAKEUP(4) | MPMU_AWUCRM_AP1_TIMER_3;
		apcr |= MPMU_APCR_SLPWP4;
		अवरोध;
	हाल IRQ_PXA910_AP2_TIMER1:
		awucrm = MPMU_AWUCRM_WAKEUP(4) | MPMU_AWUCRM_AP2_TIMER_1;
		apcr |= MPMU_APCR_SLPWP4;
		अवरोध;
	हाल IRQ_PXA910_AP2_TIMER2:
		awucrm = MPMU_AWUCRM_WAKEUP(4) | MPMU_AWUCRM_AP2_TIMER_2;
		apcr |= MPMU_APCR_SLPWP4;
		अवरोध;
	हाल IRQ_PXA910_AP2_TIMER3:
		awucrm = MPMU_AWUCRM_WAKEUP(4) | MPMU_AWUCRM_AP2_TIMER_3;
		apcr |= MPMU_APCR_SLPWP4;
		अवरोध;
	हाल IRQ_PXA910_RTC_ALARM:
		awucrm = MPMU_AWUCRM_WAKEUP(4) | MPMU_AWUCRM_RTC_ALARM;
		apcr |= MPMU_APCR_SLPWP4;
		अवरोध;
	/* wakeup line 5 */
	हाल IRQ_PXA910_USB1:
	हाल IRQ_PXA910_USB2:
		awucrm = MPMU_AWUCRM_WAKEUP(5);
		apcr |= MPMU_APCR_SLPWP5;
		अवरोध;
	/* wakeup line 6 */
	हाल IRQ_PXA910_MMC:
		awucrm = MPMU_AWUCRM_WAKEUP(6)
			| MPMU_AWUCRM_SDH1
			| MPMU_AWUCRM_SDH2;
		apcr |= MPMU_APCR_SLPWP6;
		अवरोध;
	/* wakeup line 7 */
	हाल IRQ_PXA910_PMIC_INT:
		awucrm = MPMU_AWUCRM_WAKEUP(7);
		apcr |= MPMU_APCR_SLPWP7;
		अवरोध;
	शेष:
		अगर (irq >= IRQ_GPIO_START && irq < IRQ_BOARD_START) अणु
			awucrm = MPMU_AWUCRM_WAKEUP(2);
			apcr |= MPMU_APCR_SLPWP2;
		पूर्ण अन्यथा अणु
			/* FIXME: This should वापस a proper error code ! */
			prपूर्णांकk(KERN_ERR "Error: no defined wake up source irq: %d\n",
				irq);
		पूर्ण
	पूर्ण

	अगर (on) अणु
		अगर (awucrm) अणु
			awucrm |= __raw_पढ़ोl(MPMU_AWUCRM);
			__raw_ग_लिखोl(awucrm, MPMU_AWUCRM);
		पूर्ण
		अगर (apcr) अणु
			apcr = ~apcr & __raw_पढ़ोl(MPMU_APCR);
			__raw_ग_लिखोl(apcr, MPMU_APCR);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (awucrm) अणु
			awucrm = ~awucrm & __raw_पढ़ोl(MPMU_AWUCRM);
			__raw_ग_लिखोl(awucrm, MPMU_AWUCRM);
		पूर्ण
		अगर (apcr) अणु
			apcr |= __raw_पढ़ोl(MPMU_APCR);
			__raw_ग_लिखोl(apcr, MPMU_APCR);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम pxa910_pm_enter_lowघातer_mode(पूर्णांक state)
अणु
	uपूर्णांक32_t idle_cfg, apcr;

	idle_cfg = __raw_पढ़ोl(APMU_MOH_IDLE_CFG);
	apcr = __raw_पढ़ोl(MPMU_APCR);

	apcr &= ~(MPMU_APCR_DDRCORSD | MPMU_APCR_APBSD | MPMU_APCR_AXISD
		| MPMU_APCR_VCTCXOSD | MPMU_APCR_STBYEN);
	idle_cfg &= ~(APMU_MOH_IDLE_CFG_MOH_IDLE
		| APMU_MOH_IDLE_CFG_MOH_PWRDWN);

	चयन (state) अणु
	हाल POWER_MODE_UDR:
		/* only shutकरोwn APB in UDR */
		apcr |= MPMU_APCR_STBYEN | MPMU_APCR_APBSD;
		fallthrough;
	हाल POWER_MODE_SYS_SLEEP:
		apcr |= MPMU_APCR_SLPEN;		/* set the SLPEN bit */
		apcr |= MPMU_APCR_VCTCXOSD;		/* set VCTCXOSD */
		fallthrough;
	हाल POWER_MODE_APPS_SLEEP:
		apcr |= MPMU_APCR_DDRCORSD;		/* set DDRCORSD */
		fallthrough;
	हाल POWER_MODE_APPS_IDLE:
		apcr |= MPMU_APCR_AXISD;		/* set AXISDD bit */
		fallthrough;
	हाल POWER_MODE_CORE_EXTIDLE:
		idle_cfg |= APMU_MOH_IDLE_CFG_MOH_IDLE;
		idle_cfg |= APMU_MOH_IDLE_CFG_MOH_PWRDWN;
		idle_cfg |= APMU_MOH_IDLE_CFG_MOH_PWR_SW(3)
			| APMU_MOH_IDLE_CFG_MOH_L2_PWR_SW(3);
		fallthrough;
	हाल POWER_MODE_CORE_INTIDLE:
		अवरोध;
	पूर्ण

	/* program the memory controller hardware sleep type and स्वतः wakeup */
	idle_cfg |= APMU_MOH_IDLE_CFG_MOH_DIS_MC_SW_REQ;
	idle_cfg |= APMU_MOH_IDLE_CFG_MOH_MC_WAKE_EN;
	__raw_ग_लिखोl(0x0, APMU_MC_HW_SLP_TYPE);		/* स्वतः refresh */

	/* set DSPSD, DTCMSD, BBSD, MSASLPEN */
	apcr |= MPMU_APCR_DSPSD | MPMU_APCR_DTCMSD | MPMU_APCR_BBSD
		| MPMU_APCR_MSASLPEN;

	/*always set SLEPEN bit मुख्यly क्रम MSA*/
	apcr |= MPMU_APCR_SLPEN;

	/* finally ग_लिखो the रेजिस्टरs back */
	__raw_ग_लिखोl(idle_cfg, APMU_MOH_IDLE_CFG);
	__raw_ग_लिखोl(apcr, MPMU_APCR);

पूर्ण

अटल पूर्णांक pxa910_pm_enter(suspend_state_t state)
अणु
	अचिन्हित पूर्णांक idle_cfg, reg = 0;

	/*pmic thपढ़ो not completed,निकास;otherwise प्रणाली can't be waked up*/
	reg = __raw_पढ़ोl(ICU_INT_CONF(IRQ_PXA910_PMIC_INT));
	अगर ((reg & 0x3) == 0)
		वापस -EAGAIN;

	idle_cfg = __raw_पढ़ोl(APMU_MOH_IDLE_CFG);
	idle_cfg |= APMU_MOH_IDLE_CFG_MOH_PWRDWN
		| APMU_MOH_IDLE_CFG_MOH_SRAM_PWRDWN;
	__raw_ग_लिखोl(idle_cfg, APMU_MOH_IDLE_CFG);

	/* disable L2 */
	outer_disable();
	/* रुको क्रम l2 idle */
	जबतक (!(पढ़ोl(CIU_REG(0x8)) & (1 << 16)))
		udelay(1);

	cpu_करो_idle();

	/* enable L2 */
	outer_resume();
	/* रुको क्रम l2 idle */
	जबतक (!(पढ़ोl(CIU_REG(0x8)) & (1 << 16)))
		udelay(1);

	idle_cfg = __raw_पढ़ोl(APMU_MOH_IDLE_CFG);
	idle_cfg &= ~(APMU_MOH_IDLE_CFG_MOH_PWRDWN
		| APMU_MOH_IDLE_CFG_MOH_SRAM_PWRDWN);
	__raw_ग_लिखोl(idle_cfg, APMU_MOH_IDLE_CFG);

	वापस 0;
पूर्ण

/*
 * Called after processes are frozen, but beक्रमe we shut करोwn devices.
 */
अटल पूर्णांक pxa910_pm_prepare(व्योम)
अणु
	pxa910_pm_enter_lowघातer_mode(POWER_MODE_UDR);
	वापस 0;
पूर्ण

/*
 * Called after devices are re-setup, but beक्रमe processes are thawed.
 */
अटल व्योम pxa910_pm_finish(व्योम)
अणु
	pxa910_pm_enter_lowघातer_mode(POWER_MODE_CORE_INTIDLE);
पूर्ण

अटल पूर्णांक pxa910_pm_valid(suspend_state_t state)
अणु
	वापस ((state == PM_SUSPEND_STANDBY) || (state == PM_SUSPEND_MEM));
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops pxa910_pm_ops = अणु
	.valid		= pxa910_pm_valid,
	.prepare	= pxa910_pm_prepare,
	.enter		= pxa910_pm_enter,
	.finish		= pxa910_pm_finish,
पूर्ण;

अटल पूर्णांक __init pxa910_pm_init(व्योम)
अणु
	uपूर्णांक32_t awucrm = 0;

	अगर (!cpu_is_pxa910())
		वापस -EIO;

	suspend_set_ops(&pxa910_pm_ops);

	/* Set the following bits क्रम MMP3 playback with VCTXO on */
	__raw_ग_लिखोl(__raw_पढ़ोl(APMU_SQU_CLK_GATE_CTRL) | (1 << 30),
		APMU_SQU_CLK_GATE_CTRL);
	__raw_ग_लिखोl(__raw_पढ़ोl(MPMU_FCCR) | (1 << 28), MPMU_FCCR);

	awucrm |= MPMU_AWUCRM_AP_ASYNC_INT | MPMU_AWUCRM_AP_FULL_IDLE;
	__raw_ग_लिखोl(awucrm, MPMU_AWUCRM);

	वापस 0;
पूर्ण

late_initcall(pxa910_pm_init);
