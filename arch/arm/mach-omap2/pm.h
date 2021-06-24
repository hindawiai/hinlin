<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP2/3 Power Management Routines
 *
 * Copyright (C) 2008 Nokia Corporation
 * Jouni Hogander
 */
#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_PM_H
#घोषणा __ARCH_ARM_MACH_OMAP2_PM_H

#समावेश <linux/err.h>

#समावेश "powerdomain.h"

#अगर_घोषित CONFIG_CPU_IDLE
बाह्य पूर्णांक __init omap3_idle_init(व्योम);
बाह्य पूर्णांक __init omap4_idle_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक omap3_idle_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक omap4_idle_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

बाह्य व्योम *omap3_secure_ram_storage;
बाह्य व्योम omap3_pm_off_mode_enable(पूर्णांक);
बाह्य व्योम omap_sram_idle(व्योम);
बाह्य पूर्णांक omap_pm_clkdms_setup(काष्ठा घड़ीकरोमुख्य *clkdm, व्योम *unused);

#अगर defined(CONFIG_PM_OPP)
बाह्य पूर्णांक omap3_opp_init(व्योम);
बाह्य पूर्णांक omap4_opp_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक omap3_opp_init(व्योम)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक omap4_opp_init(व्योम)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक omap3_pm_get_suspend_state(काष्ठा घातerकरोमुख्य *pwrdm);
बाह्य पूर्णांक omap3_pm_set_suspend_state(काष्ठा घातerकरोमुख्य *pwrdm, पूर्णांक state);

बाह्य u32 enable_off_mode;

#अगर defined(CONFIG_PM_DEBUG) && defined(CONFIG_DEBUG_FS)
बाह्य व्योम pm_dbg_update_समय(काष्ठा घातerकरोमुख्य *pwrdm, पूर्णांक prev);
#अन्यथा
#घोषणा pm_dbg_update_समय(pwrdm, prev) करो अणुपूर्ण जबतक (0);
#पूर्ण_अगर /* CONFIG_PM_DEBUG */

/* 24xx */
बाह्य व्योम omap24xx_idle_loop_suspend(व्योम);
बाह्य अचिन्हित पूर्णांक omap24xx_idle_loop_suspend_sz;

बाह्य व्योम omap24xx_cpu_suspend(u32 dll_ctrl, व्योम __iomem *sdrc_dlla_ctrl,
					व्योम __iomem *sdrc_घातer);
बाह्य अचिन्हित पूर्णांक omap24xx_cpu_suspend_sz;

/* 3xxx */
बाह्य व्योम omap34xx_cpu_suspend(पूर्णांक save_state);

/* omap3_करो_wfi function poपूर्णांकer and size, क्रम copy to SRAM */
बाह्य व्योम omap3_करो_wfi(व्योम);
बाह्य अचिन्हित पूर्णांक omap3_करो_wfi_sz;
/* ... and its poपूर्णांकer from SRAM after copy */
बाह्य व्योम (*omap3_करो_wfi_sram)(व्योम);

बाह्य काष्ठा am33xx_pm_sram_addr am33xx_pm_sram;
बाह्य काष्ठा am33xx_pm_sram_addr am43xx_pm_sram;

बाह्य व्योम omap3_save_scratchpad_contents(व्योम);

#घोषणा PM_RTA_ERRATUM_i608		(1 << 0)
#घोषणा PM_SDRC_WAKEUP_ERRATUM_i583	(1 << 1)
#घोषणा PM_PER_MEMORIES_ERRATUM_i582	(1 << 2)

#अगर defined(CONFIG_PM) && defined(CONFIG_ARCH_OMAP3)
बाह्य u16 pm34xx_errata;
#घोषणा IS_PM34XX_ERRATUM(id)		(pm34xx_errata & (id))
बाह्य व्योम enable_omap3630_toggle_l2_on_restore(व्योम);
#अन्यथा
#घोषणा IS_PM34XX_ERRATUM(id)		0
अटल अंतरभूत व्योम enable_omap3630_toggle_l2_on_restore(व्योम) अणु पूर्ण
#पूर्ण_अगर		/* defined(CONFIG_PM) && defined(CONFIG_ARCH_OMAP3) */

#घोषणा PM_OMAP4_ROM_SMP_BOOT_ERRATUM_GICD	(1 << 0)
#घोषणा PM_OMAP4_CPU_OSWR_DISABLE		(1 << 1)

#अगर defined(CONFIG_PM) && (defined(CONFIG_ARCH_OMAP4) ||\
	   defined(CONFIG_SOC_OMAP5) || defined(CONFIG_SOC_DRA7XX))
बाह्य u16 pm44xx_errata;
#घोषणा IS_PM44XX_ERRATUM(id)		(pm44xx_errata & (id))
#अन्यथा
#घोषणा IS_PM44XX_ERRATUM(id)		0
#पूर्ण_अगर

#घोषणा OMAP4_VP_CONFIG_ERROROFFSET	0x00
#घोषणा OMAP4_VP_VSTEPMIN_VSTEPMIN	0x01
#घोषणा OMAP4_VP_VSTEPMAX_VSTEPMAX	0x04
#घोषणा OMAP4_VP_VLIMITTO_TIMEOUT_US	200

#अगर_घोषित CONFIG_POWER_AVS_OMAP
बाह्य पूर्णांक omap_devinit_smartreflex(व्योम);
बाह्य व्योम omap_enable_smartreflex_on_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक omap_devinit_smartreflex(व्योम)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम omap_enable_smartreflex_on_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_TWL4030_CORE
बाह्य पूर्णांक omap3_twl_init(व्योम);
बाह्य पूर्णांक omap4_twl_init(व्योम);
बाह्य पूर्णांक omap3_twl_set_sr_bit(bool enable);
#अन्यथा
अटल अंतरभूत पूर्णांक omap3_twl_init(व्योम)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक omap4_twl_init(व्योम)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_MFD_CPCAP)
बाह्य पूर्णांक omap4_cpcap_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक omap4_cpcap_init(व्योम)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
बाह्य व्योम omap_pm_setup_oscillator(u32 tstart, u32 tshut);
बाह्य व्योम omap_pm_get_oscillator(u32 *tstart, u32 *tshut);
बाह्य व्योम omap_pm_setup_sr_i2c_pcb_length(u32 mm);
#अन्यथा
अटल अंतरभूत व्योम omap_pm_setup_oscillator(u32 tstart, u32 tshut) अणु पूर्ण
अटल अंतरभूत व्योम omap_pm_get_oscillator(u32 *tstart, u32 *tshut) अणु *tstart = *tshut = 0; पूर्ण
अटल अंतरभूत व्योम omap_pm_setup_sr_i2c_pcb_length(u32 mm) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SUSPEND
व्योम omap_common_suspend_init(व्योम *pm_suspend);
#अन्यथा
अटल अंतरभूत व्योम omap_common_suspend_init(व्योम *pm_suspend)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SUSPEND */
#पूर्ण_अगर
