<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/shmobile/pm.c
 *
 * Power management support code क्रम SuperH Mobile
 *
 *  Copyright (C) 2009 Magnus Damm
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/suspend.h>
#समावेश <यंत्र/suspend.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/bl_bit.h>

/*
 * Notअगरier lists क्रम pre/post sleep notअगरication
 */
ATOMIC_NOTIFIER_HEAD(sh_mobile_pre_sleep_notअगरier_list);
ATOMIC_NOTIFIER_HEAD(sh_mobile_post_sleep_notअगरier_list);

/*
 * Sleep modes available on SuperH Mobile:
 *
 * Sleep mode is just plain "sleep" inकाष्ठाion
 * Sleep Self-Refresh mode is above plus RAM put in Self-Refresh
 * Standby Self-Refresh mode is above plus stopped घड़ीs
 */
#घोषणा SUSP_MODE_SLEEP		(SUSP_SH_SLEEP)
#घोषणा SUSP_MODE_SLEEP_SF	(SUSP_SH_SLEEP | SUSP_SH_SF)
#घोषणा SUSP_MODE_STANDBY_SF	(SUSP_SH_STANDBY | SUSP_SH_SF)
#घोषणा SUSP_MODE_RSTANDBY_SF \
	(SUSP_SH_RSTANDBY | SUSP_SH_MMU | SUSP_SH_REGS | SUSP_SH_SF)
 /*
  * U-standby mode is unsupported since it needs bootloader hacks
  */

#अगर_घोषित CONFIG_CPU_SUBTYPE_SH7724
#घोषणा RAM_BASE 0xfd800000 /* RSMEM */
#अन्यथा
#घोषणा RAM_BASE 0xe5200000 /* ILRAM */
#पूर्ण_अगर

व्योम sh_mobile_call_standby(अचिन्हित दीर्घ mode)
अणु
	व्योम *onchip_mem = (व्योम *)RAM_BASE;
	काष्ठा sh_sleep_data *sdp = onchip_mem;
	व्योम (*standby_onchip_mem)(अचिन्हित दीर्घ, अचिन्हित दीर्घ);

	/* code located directly after data काष्ठाure */
	standby_onchip_mem = (व्योम *)(sdp + 1);

	atomic_notअगरier_call_chain(&sh_mobile_pre_sleep_notअगरier_list,
				   mode, शून्य);

	/* flush the caches अगर MMU flag is set */
	अगर (mode & SUSP_SH_MMU)
		flush_cache_all();

	/* Let assembly snippet in on-chip memory handle the rest */
	standby_onchip_mem(mode, RAM_BASE);

	atomic_notअगरier_call_chain(&sh_mobile_post_sleep_notअगरier_list,
				   mode, शून्य);
पूर्ण

बाह्य अक्षर sh_mobile_sleep_enter_start;
बाह्य अक्षर sh_mobile_sleep_enter_end;

बाह्य अक्षर sh_mobile_sleep_resume_start;
बाह्य अक्षर sh_mobile_sleep_resume_end;

अचिन्हित दीर्घ sh_mobile_sleep_supported = SUSP_SH_SLEEP;

व्योम sh_mobile_रेजिस्टर_self_refresh(अचिन्हित दीर्घ flags,
				     व्योम *pre_start, व्योम *pre_end,
				     व्योम *post_start, व्योम *post_end)
अणु
	व्योम *onchip_mem = (व्योम *)RAM_BASE;
	व्योम *vp;
	काष्ठा sh_sleep_data *sdp;
	पूर्णांक n;

	/* part 0: data area */
	sdp = onchip_mem;
	sdp->addr.stbcr = 0xa4150020; /* STBCR */
	sdp->addr.bar = 0xa4150040; /* BAR */
	sdp->addr.pteh = 0xff000000; /* PTEH */
	sdp->addr.ptel = 0xff000004; /* PTEL */
	sdp->addr.ttb = 0xff000008; /* TTB */
	sdp->addr.tea = 0xff00000c; /* TEA */
	sdp->addr.mmucr = 0xff000010; /* MMUCR */
	sdp->addr.ptea = 0xff000034; /* PTEA */
	sdp->addr.pascr = 0xff000070; /* PASCR */
	sdp->addr.irmcr = 0xff000078; /* IRMCR */
	sdp->addr.ccr = 0xff00001c; /* CCR */
	sdp->addr.ramcr = 0xff000074; /* RAMCR */
	vp = sdp + 1;

	/* part 1: common code to enter sleep mode */
	n = &sh_mobile_sleep_enter_end - &sh_mobile_sleep_enter_start;
	स_नकल(vp, &sh_mobile_sleep_enter_start, n);
	vp += roundup(n, 4);

	/* part 2: board specअगरic code to enter self-refresh mode */
	n = pre_end - pre_start;
	स_नकल(vp, pre_start, n);
	sdp->sf_pre = (अचिन्हित दीर्घ)vp;
	vp += roundup(n, 4);

	/* part 3: board specअगरic code to resume from self-refresh mode */
	n = post_end - post_start;
	स_नकल(vp, post_start, n);
	sdp->sf_post = (अचिन्हित दीर्घ)vp;
	vp += roundup(n, 4);

	/* part 4: common code to resume from sleep mode */
	WARN_ON(vp > (onchip_mem + 0x600));
	vp = onchip_mem + 0x600; /* located at पूर्णांकerrupt vector */
	n = &sh_mobile_sleep_resume_end - &sh_mobile_sleep_resume_start;
	स_नकल(vp, &sh_mobile_sleep_resume_start, n);
	sdp->resume = (अचिन्हित दीर्घ)vp;

	sh_mobile_sleep_supported |= flags;
पूर्ण

अटल पूर्णांक sh_pm_enter(suspend_state_t state)
अणु
	अगर (!(sh_mobile_sleep_supported & SUSP_MODE_STANDBY_SF))
		वापस -ENXIO;

	local_irq_disable();
	set_bl_bit();
	sh_mobile_call_standby(SUSP_MODE_STANDBY_SF);
	local_irq_disable();
	clear_bl_bit();
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops sh_pm_ops = अणु
	.enter          = sh_pm_enter,
	.valid          = suspend_valid_only_mem,
पूर्ण;

अटल पूर्णांक __init sh_pm_init(व्योम)
अणु
	suspend_set_ops(&sh_pm_ops);
	वापस sh_mobile_setup_cpuidle();
पूर्ण

late_initcall(sh_pm_init);
