<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP2xxx/3xxx-common Power/Reset Management (PRM) रेजिस्टर definitions
 *
 * Copyright (C) 2007-2009, 2011-2012 Texas Instruments, Inc.
 * Copyright (C) 2008-2010 Nokia Corporation
 * Paul Walmsley
 *
 * The PRM hardware modules on the OMAP2/3 are quite similar to each
 * other.  The PRM on OMAP4 has a new रेजिस्टर layout, and is handled
 * in a separate file.
 */
#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_PRM2XXX_3XXX_H
#घोषणा __ARCH_ARM_MACH_OMAP2_PRM2XXX_3XXX_H

#समावेश "prcm-common.h"
#समावेश "prm.h"

/*
 * Module specअगरic PRM रेजिस्टर offsets from PRM_BASE + करोमुख्य offset
 *
 * Use prm_अणुपढ़ो,ग_लिखोपूर्ण_mod_reg() with these रेजिस्टरs.
 *
 * With a few exceptions, these are the रेजिस्टर names beginning with
 * अणुPM,RMपूर्ण_* on both OMAP2/3 SoC families..  (The exceptions are the
 * IRQSTATUS and IRQENABLE bits.)
 */

/* Register offsets appearing on both OMAP2 and OMAP3 */

#घोषणा OMAP2_RM_RSTCTRL				0x0050
#घोषणा OMAP2_RM_RSTTIME				0x0054
#घोषणा OMAP2_RM_RSTST					0x0058
#घोषणा OMAP2_PM_PWSTCTRL				0x00e0
#घोषणा OMAP2_PM_PWSTST					0x00e4

#घोषणा PM_WKEN						0x00a0
#घोषणा PM_WKEN1					PM_WKEN
#घोषणा PM_WKST						0x00b0
#घोषणा PM_WKST1					PM_WKST
#घोषणा PM_WKDEP					0x00c8
#घोषणा PM_EVGENCTRL					0x00d4
#घोषणा PM_EVGENONTIM					0x00d8
#घोषणा PM_EVGENOFFTIM					0x00dc


#अगर_अघोषित __ASSEMBLER__

#समावेश <linux/पन.स>
#समावेश "powerdomain.h"

/* Power/reset management करोमुख्य रेजिस्टर get/set */
अटल अंतरभूत u32 omap2_prm_पढ़ो_mod_reg(s16 module, u16 idx)
अणु
	वापस पढ़ोl_relaxed(prm_base.va + module + idx);
पूर्ण

अटल अंतरभूत व्योम omap2_prm_ग_लिखो_mod_reg(u32 val, s16 module, u16 idx)
अणु
	ग_लिखोl_relaxed(val, prm_base.va + module + idx);
पूर्ण

/* Read-modअगरy-ग_लिखो a रेजिस्टर in a PRM module. Caller must lock */
अटल अंतरभूत u32 omap2_prm_rmw_mod_reg_bits(u32 mask, u32 bits, s16 module,
					     s16 idx)
अणु
	u32 v;

	v = omap2_prm_पढ़ो_mod_reg(module, idx);
	v &= ~mask;
	v |= bits;
	omap2_prm_ग_लिखो_mod_reg(v, module, idx);

	वापस v;
पूर्ण

/* Read a PRM रेजिस्टर, AND it, and shअगरt the result करोwn to bit 0 */
अटल अंतरभूत u32 omap2_prm_पढ़ो_mod_bits_shअगरt(s16 करोमुख्य, s16 idx, u32 mask)
अणु
	u32 v;

	v = omap2_prm_पढ़ो_mod_reg(करोमुख्य, idx);
	v &= mask;
	v >>= __ffs(mask);

	वापस v;
पूर्ण

अटल अंतरभूत u32 omap2_prm_set_mod_reg_bits(u32 bits, s16 module, s16 idx)
अणु
	वापस omap2_prm_rmw_mod_reg_bits(bits, bits, module, idx);
पूर्ण

अटल अंतरभूत u32 omap2_prm_clear_mod_reg_bits(u32 bits, s16 module, s16 idx)
अणु
	वापस omap2_prm_rmw_mod_reg_bits(bits, 0x0, module, idx);
पूर्ण

/* These omap2_ PRM functions apply to both OMAP2 and 3 */
पूर्णांक omap2_prm_is_hardreset_निश्चितed(u8 shअगरt, u8 part, s16 prm_mod, u16 offset);
पूर्णांक omap2_prm_निश्चित_hardreset(u8 shअगरt, u8 part, s16 prm_mod,
			       u16 offset);
पूर्णांक omap2_prm_deनिश्चित_hardreset(u8 rst_shअगरt, u8 st_shअगरt, u8 part,
				 s16 prm_mod, u16 reset_offset,
				 u16 st_offset);

बाह्य पूर्णांक omap2_pwrdm_set_next_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 pwrst);
बाह्य पूर्णांक omap2_pwrdm_पढ़ो_next_pwrst(काष्ठा घातerकरोमुख्य *pwrdm);
बाह्य पूर्णांक omap2_pwrdm_पढ़ो_pwrst(काष्ठा घातerकरोमुख्य *pwrdm);
बाह्य पूर्णांक omap2_pwrdm_set_mem_onst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank,
				    u8 pwrst);
बाह्य पूर्णांक omap2_pwrdm_set_mem_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank,
				     u8 pwrst);
बाह्य पूर्णांक omap2_pwrdm_पढ़ो_mem_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank);
बाह्य पूर्णांक omap2_pwrdm_पढ़ो_mem_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank);
बाह्य पूर्णांक omap2_pwrdm_set_logic_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 pwrst);
बाह्य पूर्णांक omap2_pwrdm_रुको_transition(काष्ठा घातerकरोमुख्य *pwrdm);

बाह्य पूर्णांक omap2_clkdm_add_wkdep(काष्ठा घड़ीकरोमुख्य *clkdm1,
				 काष्ठा घड़ीकरोमुख्य *clkdm2);
बाह्य पूर्णांक omap2_clkdm_del_wkdep(काष्ठा घड़ीकरोमुख्य *clkdm1,
				 काष्ठा घड़ीकरोमुख्य *clkdm2);
बाह्य पूर्णांक omap2_clkdm_पढ़ो_wkdep(काष्ठा घड़ीकरोमुख्य *clkdm1,
				  काष्ठा घड़ीकरोमुख्य *clkdm2);
बाह्य पूर्णांक omap2_clkdm_clear_all_wkdeps(काष्ठा घड़ीकरोमुख्य *clkdm);

#पूर्ण_अगर /* __ASSEMBLER */

/*
 * Bits common to specअगरic रेजिस्टरs
 *
 * The 3430 रेजिस्टर and bit names are generally used,
 * since they tend to make more sense
 */

/* PM_EVGENONTIM_MPU */
/* Named PM_EVEGENONTIM_MPU on the 24XX */
#घोषणा OMAP_ONTIMEVAL_SHIFT				0
#घोषणा OMAP_ONTIMEVAL_MASK				(0xffffffff << 0)

/* PM_EVGENOFFTIM_MPU */
/* Named PM_EVEGENOFFTIM_MPU on the 24XX */
#घोषणा OMAP_OFFTIMEVAL_SHIFT				0
#घोषणा OMAP_OFFTIMEVAL_MASK				(0xffffffff << 0)

/* PRM_CLKSETUP and PRCM_VOLTSETUP */
/* Named PRCM_CLKSSETUP on the 24XX */
#घोषणा OMAP_SETUP_TIME_SHIFT				0
#घोषणा OMAP_SETUP_TIME_MASK				(0xffff << 0)

/* PRM_CLKSRC_CTRL */
/* Named PRCM_CLKSRC_CTRL on the 24XX */
#घोषणा OMAP_SYSCLKDIV_SHIFT				6
#घोषणा OMAP_SYSCLKDIV_MASK				(0x3 << 6)
#घोषणा OMAP_SYSCLKDIV_WIDTH				2
#घोषणा OMAP_AUTOEXTCLKMODE_SHIFT			3
#घोषणा OMAP_AUTOEXTCLKMODE_MASK			(0x3 << 3)
#घोषणा OMAP_SYSCLKSEL_SHIFT				0
#घोषणा OMAP_SYSCLKSEL_MASK				(0x3 << 0)

/* PM_EVGENCTRL_MPU */
#घोषणा OMAP_OFFLOADMODE_SHIFT				3
#घोषणा OMAP_OFFLOADMODE_MASK				(0x3 << 3)
#घोषणा OMAP_ONLOADMODE_SHIFT				1
#घोषणा OMAP_ONLOADMODE_MASK				(0x3 << 1)
#घोषणा OMAP_ENABLE_MASK				(1 << 0)

/* PRM_RSTTIME */
/* Named RM_RSTTIME_WKUP on the 24xx */
#घोषणा OMAP_RSTTIME2_SHIFT				8
#घोषणा OMAP_RSTTIME2_MASK				(0x1f << 8)
#घोषणा OMAP_RSTTIME1_SHIFT				0
#घोषणा OMAP_RSTTIME1_MASK				(0xff << 0)

/* PRM_RSTCTRL */
/* Named RM_RSTCTRL_WKUP on the 24xx */
/* 2420 calls RST_DPLL3 'RST_DPLL' */
#घोषणा OMAP_RST_DPLL3_MASK				(1 << 2)
#घोषणा OMAP_RST_GS_MASK				(1 << 1)


/*
 * Bits common to module-shared रेजिस्टरs
 *
 * Not all रेजिस्टरs of a particular type support all of these bits -
 * check TRM अगर you are unsure
 */

/*
 * 24XX: RM_RSTST_MPU and RM_RSTST_DSP - on 24XX, 'COREDOMAINWKUP_RST' is
 *	 called 'COREWKUP_RST'
 *
 * 3430: RM_RSTST_IVA2, RM_RSTST_MPU, RM_RSTST_GFX, RM_RSTST_DSS,
 *	 RM_RSTST_CAM, RM_RSTST_PER, RM_RSTST_NEON
 */
#घोषणा OMAP_CORगलत_तर्कAINWKUP_RST_MASK			(1 << 3)

/*
 * 24XX: RM_RSTST_MPU, RM_RSTST_GFX, RM_RSTST_DSP
 *
 * 2430: RM_RSTST_MDM
 *
 * 3430: RM_RSTST_CORE, RM_RSTST_EMU
 */
#घोषणा OMAP_DOMAINWKUP_RST_MASK			(1 << 2)

/*
 * 24XX: RM_RSTST_MPU, RM_RSTST_WKUP, RM_RSTST_DSP
 *	 On 24XX, 'GLOBALWARM_RST' is called 'GLOBALWMPU_RST'.
 *
 * 2430: RM_RSTST_MDM
 *
 * 3430: RM_RSTST_CORE, RM_RSTST_EMU
 */
#घोषणा OMAP_GLOBALWARM_RST_SHIFT			1
#घोषणा OMAP_GLOBALWARM_RST_MASK			(1 << 1)
#घोषणा OMAP_GLOBALCOLD_RST_SHIFT			0
#घोषणा OMAP_GLOBALCOLD_RST_MASK			(1 << 0)

/*
 * 24XX: PM_WKDEP_GFX, PM_WKDEP_MPU, PM_WKDEP_CORE, PM_WKDEP_DSP
 *	 2420 TRM someबार uses "EN_WAKEUP" instead of "EN_WKUP"
 *
 * 2430: PM_WKDEP_MDM
 *
 * 3430: PM_WKDEP_IVA2, PM_WKDEP_GFX, PM_WKDEP_DSS, PM_WKDEP_CAM,
 *	 PM_WKDEP_PER
 */
#घोषणा OMAP_EN_WKUP_SHIFT				4
#घोषणा OMAP_EN_WKUP_MASK				(1 << 4)

/*
 * 24XX: PM_PWSTCTRL_MPU, PM_PWSTCTRL_CORE, PM_PWSTCTRL_GFX,
 *	 PM_PWSTCTRL_DSP
 *
 * 2430: PM_PWSTCTRL_MDM
 *
 * 3430: PM_PWSTCTRL_IVA2, PM_PWSTCTRL_CORE, PM_PWSTCTRL_GFX,
 *	 PM_PWSTCTRL_DSS, PM_PWSTCTRL_CAM, PM_PWSTCTRL_PER,
 *	 PM_PWSTCTRL_NEON
 */
#घोषणा OMAP_LOGICRETSTATE_MASK				(1 << 2)


#पूर्ण_अगर
