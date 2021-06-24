<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP2xxx PRM module functions
 *
 * Copyright (C) 2010-2012 Texas Instruments, Inc.
 * Copyright (C) 2010 Nokia Corporation
 * Benoथऍt Cousson
 * Paul Walmsley
 * Rajendra Nayak <rnayak@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>

#समावेश "powerdomain.h"
#समावेश "clockdomain.h"
#समावेश "prm2xxx.h"
#समावेश "cm2xxx_3xxx.h"
#समावेश "prm-regbits-24xx.h"

/*
 * OMAP24xx PM_PWSTCTRL_*.POWERSTATE and PM_PWSTST_*.LASTSTATEENTERED bits -
 * these are reversed from the bits used on OMAP3+
 */
#घोषणा OMAP24XX_PWRDM_POWER_ON			0x0
#घोषणा OMAP24XX_PWRDM_POWER_RET		0x1
#घोषणा OMAP24XX_PWRDM_POWER_OFF		0x3

/*
 * omap2xxx_prm_reset_src_map - map from bits in the PRM_RSTST_WKUP
 *   hardware रेजिस्टर (which are specअगरic to the OMAP2xxx SoCs) to
 *   reset source ID bit shअगरts (which is an OMAP SoC-independent
 *   क्रमागतeration)
 */
अटल काष्ठा prm_reset_src_map omap2xxx_prm_reset_src_map[] = अणु
	अणु OMAP_GLOBALCOLD_RST_SHIFT, OMAP_GLOBAL_COLD_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP_GLOBALWARM_RST_SHIFT, OMAP_GLOBAL_WARM_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP24XX_SECU_VIOL_RST_SHIFT, OMAP_SECU_VIOL_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP24XX_MPU_WD_RST_SHIFT, OMAP_MPU_WD_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP24XX_SECU_WD_RST_SHIFT, OMAP_SECU_WD_RST_SRC_ID_SHIFT पूर्ण,
	अणु OMAP24XX_EXTWMPU_RST_SHIFT, OMAP_EXTWARM_RST_SRC_ID_SHIFT पूर्ण,
	अणु -1, -1 पूर्ण,
पूर्ण;

/**
 * omap2xxx_prm_पढ़ो_reset_sources - वापस the last SoC reset source
 *
 * Return a u32 representing the last reset sources of the SoC.  The
 * वापसed reset source bits are standardized across OMAP SoCs.
 */
अटल u32 omap2xxx_prm_पढ़ो_reset_sources(व्योम)
अणु
	काष्ठा prm_reset_src_map *p;
	u32 r = 0;
	u32 v;

	v = omap2_prm_पढ़ो_mod_reg(WKUP_MOD, OMAP2_RM_RSTST);

	p = omap2xxx_prm_reset_src_map;
	जबतक (p->reg_shअगरt >= 0 && p->std_shअगरt >= 0) अणु
		अगर (v & (1 << p->reg_shअगरt))
			r |= 1 << p->std_shअगरt;
		p++;
	पूर्ण

	वापस r;
पूर्ण

/**
 * omap2xxx_pwrst_to_common_pwrst - convert OMAP2xxx pwrst to common pwrst
 * @omap2xxx_pwrst: OMAP2xxx hardware घातer state to convert
 *
 * Return the common घातer state bits corresponding to the OMAP2xxx
 * hardware घातer state bits @omap2xxx_pwrst, or -EINVAL upon error.
 */
अटल पूर्णांक omap2xxx_pwrst_to_common_pwrst(u8 omap2xxx_pwrst)
अणु
	u8 pwrst;

	चयन (omap2xxx_pwrst) अणु
	हाल OMAP24XX_PWRDM_POWER_OFF:
		pwrst = PWRDM_POWER_OFF;
		अवरोध;
	हाल OMAP24XX_PWRDM_POWER_RET:
		pwrst = PWRDM_POWER_RET;
		अवरोध;
	हाल OMAP24XX_PWRDM_POWER_ON:
		pwrst = PWRDM_POWER_ON;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस pwrst;
पूर्ण

/**
 * omap2xxx_prm_dpll_reset - use DPLL reset to reboot the OMAP SoC
 *
 * Set the DPLL reset bit, which should reboot the SoC.  This is the
 * recommended way to restart the SoC.  No वापस value.
 */
अटल व्योम omap2xxx_prm_dpll_reset(व्योम)
अणु
	omap2_prm_set_mod_reg_bits(OMAP_RST_DPLL3_MASK, WKUP_MOD,
				   OMAP2_RM_RSTCTRL);
	/* OCP barrier */
	omap2_prm_पढ़ो_mod_reg(WKUP_MOD, OMAP2_RM_RSTCTRL);
पूर्ण

/**
 * omap2xxx_prm_clear_mod_irqs - clear wakeup status bits क्रम a module
 * @module: PRM module to clear wakeups from
 * @regs: रेजिस्टर offset to clear
 * @wkst_mask: wakeup status mask to clear
 *
 * Clears wakeup status bits क्रम a given module, so that the device can
 * re-enter idle.
 */
अटल पूर्णांक omap2xxx_prm_clear_mod_irqs(s16 module, u8 regs, u32 wkst_mask)
अणु
	u32 wkst;

	wkst = omap2_prm_पढ़ो_mod_reg(module, regs);
	wkst &= wkst_mask;
	omap2_prm_ग_लिखो_mod_reg(wkst, module, regs);
	वापस 0;
पूर्ण

पूर्णांक omap2xxx_clkdm_sleep(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	omap2_prm_set_mod_reg_bits(OMAP24XX_FORCESTATE_MASK,
				   clkdm->pwrdm.ptr->prcm_offs,
				   OMAP2_PM_PWSTCTRL);
	वापस 0;
पूर्ण

पूर्णांक omap2xxx_clkdm_wakeup(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	omap2_prm_clear_mod_reg_bits(OMAP24XX_FORCESTATE_MASK,
				     clkdm->pwrdm.ptr->prcm_offs,
				     OMAP2_PM_PWSTCTRL);
	वापस 0;
पूर्ण

अटल पूर्णांक omap2xxx_pwrdm_set_next_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 pwrst)
अणु
	u8 omap24xx_pwrst;

	चयन (pwrst) अणु
	हाल PWRDM_POWER_OFF:
		omap24xx_pwrst = OMAP24XX_PWRDM_POWER_OFF;
		अवरोध;
	हाल PWRDM_POWER_RET:
		omap24xx_pwrst = OMAP24XX_PWRDM_POWER_RET;
		अवरोध;
	हाल PWRDM_POWER_ON:
		omap24xx_pwrst = OMAP24XX_PWRDM_POWER_ON;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	omap2_prm_rmw_mod_reg_bits(OMAP_POWERSTATE_MASK,
				   (omap24xx_pwrst << OMAP_POWERSTATE_SHIFT),
				   pwrdm->prcm_offs, OMAP2_PM_PWSTCTRL);
	वापस 0;
पूर्ण

अटल पूर्णांक omap2xxx_pwrdm_पढ़ो_next_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	u8 omap2xxx_pwrst;

	omap2xxx_pwrst = omap2_prm_पढ़ो_mod_bits_shअगरt(pwrdm->prcm_offs,
						       OMAP2_PM_PWSTCTRL,
						       OMAP_POWERSTATE_MASK);

	वापस omap2xxx_pwrst_to_common_pwrst(omap2xxx_pwrst);
पूर्ण

अटल पूर्णांक omap2xxx_pwrdm_पढ़ो_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	u8 omap2xxx_pwrst;

	omap2xxx_pwrst = omap2_prm_पढ़ो_mod_bits_shअगरt(pwrdm->prcm_offs,
						       OMAP2_PM_PWSTST,
						       OMAP_POWERSTATEST_MASK);

	वापस omap2xxx_pwrst_to_common_pwrst(omap2xxx_pwrst);
पूर्ण

काष्ठा pwrdm_ops omap2_pwrdm_operations = अणु
	.pwrdm_set_next_pwrst	= omap2xxx_pwrdm_set_next_pwrst,
	.pwrdm_पढ़ो_next_pwrst	= omap2xxx_pwrdm_पढ़ो_next_pwrst,
	.pwrdm_पढ़ो_pwrst	= omap2xxx_pwrdm_पढ़ो_pwrst,
	.pwrdm_set_logic_retst	= omap2_pwrdm_set_logic_retst,
	.pwrdm_set_mem_onst	= omap2_pwrdm_set_mem_onst,
	.pwrdm_set_mem_retst	= omap2_pwrdm_set_mem_retst,
	.pwrdm_पढ़ो_mem_pwrst	= omap2_pwrdm_पढ़ो_mem_pwrst,
	.pwrdm_पढ़ो_mem_retst	= omap2_pwrdm_पढ़ो_mem_retst,
	.pwrdm_रुको_transition	= omap2_pwrdm_रुको_transition,
पूर्ण;

/*
 *
 */

अटल काष्ठा prm_ll_data omap2xxx_prm_ll_data = अणु
	.पढ़ो_reset_sources = &omap2xxx_prm_पढ़ो_reset_sources,
	.निश्चित_hardreset = &omap2_prm_निश्चित_hardreset,
	.deनिश्चित_hardreset = &omap2_prm_deनिश्चित_hardreset,
	.is_hardreset_निश्चितed = &omap2_prm_is_hardreset_निश्चितed,
	.reset_प्रणाली = &omap2xxx_prm_dpll_reset,
	.clear_mod_irqs = &omap2xxx_prm_clear_mod_irqs,
पूर्ण;

पूर्णांक __init omap2xxx_prm_init(स्थिर काष्ठा omap_prcm_init_data *data)
अणु
	वापस prm_रेजिस्टर(&omap2xxx_prm_ll_data);
पूर्ण

अटल व्योम __निकास omap2xxx_prm_निकास(व्योम)
अणु
	prm_unरेजिस्टर(&omap2xxx_prm_ll_data);
पूर्ण
__निकासcall(omap2xxx_prm_निकास);
