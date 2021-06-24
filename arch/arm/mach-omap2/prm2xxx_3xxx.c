<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP2/3 PRM module functions
 *
 * Copyright (C) 2010-2011 Texas Instruments, Inc.
 * Copyright (C) 2010 Nokia Corporation
 * Benoथऍt Cousson
 * Paul Walmsley
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>

#समावेश "powerdomain.h"
#समावेश "prm2xxx_3xxx.h"
#समावेश "prm-regbits-24xx.h"
#समावेश "clockdomain.h"

/**
 * omap2_prm_is_hardreset_निश्चितed - पढ़ो the HW reset line state of
 * submodules contained in the hwmod module
 * @shअगरt: रेजिस्टर bit shअगरt corresponding to the reset line to check
 * @part: PRM partition, ignored क्रम OMAP2
 * @prm_mod: PRM submodule base (e.g. CORE_MOD)
 * @offset: रेजिस्टर offset, ignored क्रम OMAP2
 *
 * Returns 1 अगर the (sub)module hardreset line is currently निश्चितed,
 * 0 अगर the (sub)module hardreset line is not currently निश्चितed, or
 * -EINVAL अगर called जबतक running on a non-OMAP2/3 chip.
 */
पूर्णांक omap2_prm_is_hardreset_निश्चितed(u8 shअगरt, u8 part, s16 prm_mod, u16 offset)
अणु
	वापस omap2_prm_पढ़ो_mod_bits_shअगरt(prm_mod, OMAP2_RM_RSTCTRL,
				       (1 << shअगरt));
पूर्ण

/**
 * omap2_prm_निश्चित_hardreset - निश्चित the HW reset line of a submodule
 * @shअगरt: रेजिस्टर bit shअगरt corresponding to the reset line to निश्चित
 * @part: PRM partition, ignored क्रम OMAP2
 * @prm_mod: PRM submodule base (e.g. CORE_MOD)
 * @offset: रेजिस्टर offset, ignored क्रम OMAP2
 *
 * Some IPs like dsp or iva contain processors that require an HW
 * reset line to be निश्चितed / deनिश्चितed in order to fully enable the
 * IP.  These modules may have multiple hard-reset lines that reset
 * dअगरferent 'submodules' inside the IP block.  This function will
 * place the submodule पूर्णांकo reset.  Returns 0 upon success or -EINVAL
 * upon an argument error.
 */
पूर्णांक omap2_prm_निश्चित_hardreset(u8 shअगरt, u8 part, s16 prm_mod, u16 offset)
अणु
	u32 mask;

	mask = 1 << shअगरt;
	omap2_prm_rmw_mod_reg_bits(mask, mask, prm_mod, OMAP2_RM_RSTCTRL);

	वापस 0;
पूर्ण

/**
 * omap2_prm_deनिश्चित_hardreset - deनिश्चित a submodule hardreset line and रुको
 * @prm_mod: PRM submodule base (e.g. CORE_MOD)
 * @rst_shअगरt: रेजिस्टर bit shअगरt corresponding to the reset line to deनिश्चित
 * @st_shअगरt: रेजिस्टर bit shअगरt क्रम the status of the deनिश्चितed submodule
 * @part: PRM partition, not used क्रम OMAP2
 * @prm_mod: PRM submodule base (e.g. CORE_MOD)
 * @rst_offset: reset रेजिस्टर offset, not used क्रम OMAP2
 * @st_offset: reset status रेजिस्टर offset, not used क्रम OMAP2
 *
 * Some IPs like dsp or iva contain processors that require an HW
 * reset line to be निश्चितed / deनिश्चितed in order to fully enable the
 * IP.  These modules may have multiple hard-reset lines that reset
 * dअगरferent 'submodules' inside the IP block.  This function will
 * take the submodule out of reset and रुको until the PRCM indicates
 * that the reset has completed beक्रमe वापसing.  Returns 0 upon success or
 * -EINVAL upon an argument error, -EEXIST अगर the submodule was alपढ़ोy out
 * of reset, or -EBUSY अगर the submodule did not निकास reset promptly.
 */
पूर्णांक omap2_prm_deनिश्चित_hardreset(u8 rst_shअगरt, u8 st_shअगरt, u8 part,
				 s16 prm_mod, u16 rst_offset, u16 st_offset)
अणु
	u32 rst, st;
	पूर्णांक c;

	rst = 1 << rst_shअगरt;
	st = 1 << st_shअगरt;

	/* Check the current status to aव्योम de-निश्चितing the line twice */
	अगर (omap2_prm_पढ़ो_mod_bits_shअगरt(prm_mod, OMAP2_RM_RSTCTRL, rst) == 0)
		वापस -EEXIST;

	/* Clear the reset status by writing 1 to the status bit */
	omap2_prm_rmw_mod_reg_bits(0xffffffff, st, prm_mod, OMAP2_RM_RSTST);
	/* de-निश्चित the reset control line */
	omap2_prm_rmw_mod_reg_bits(rst, 0, prm_mod, OMAP2_RM_RSTCTRL);
	/* रुको the status to be set */
	omap_test_समयout(omap2_prm_पढ़ो_mod_bits_shअगरt(prm_mod, OMAP2_RM_RSTST,
						  st),
			  MAX_MODULE_HARDRESET_WAIT, c);

	वापस (c == MAX_MODULE_HARDRESET_WAIT) ? -EBUSY : 0;
पूर्ण


/* Powerकरोमुख्य low-level functions */

/* Common functions across OMAP2 and OMAP3 */
पूर्णांक omap2_pwrdm_set_mem_onst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank,
								u8 pwrst)
अणु
	u32 m;

	m = omap2_pwrdm_get_mem_bank_onstate_mask(bank);

	omap2_prm_rmw_mod_reg_bits(m, (pwrst << __ffs(m)), pwrdm->prcm_offs,
				   OMAP2_PM_PWSTCTRL);

	वापस 0;
पूर्ण

पूर्णांक omap2_pwrdm_set_mem_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank,
								u8 pwrst)
अणु
	u32 m;

	m = omap2_pwrdm_get_mem_bank_retst_mask(bank);

	omap2_prm_rmw_mod_reg_bits(m, (pwrst << __ffs(m)), pwrdm->prcm_offs,
				   OMAP2_PM_PWSTCTRL);

	वापस 0;
पूर्ण

पूर्णांक omap2_pwrdm_पढ़ो_mem_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank)
अणु
	u32 m;

	m = omap2_pwrdm_get_mem_bank_stst_mask(bank);

	वापस omap2_prm_पढ़ो_mod_bits_shअगरt(pwrdm->prcm_offs, OMAP2_PM_PWSTST,
					     m);
पूर्ण

पूर्णांक omap2_pwrdm_पढ़ो_mem_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank)
अणु
	u32 m;

	m = omap2_pwrdm_get_mem_bank_retst_mask(bank);

	वापस omap2_prm_पढ़ो_mod_bits_shअगरt(pwrdm->prcm_offs,
					     OMAP2_PM_PWSTCTRL, m);
पूर्ण

पूर्णांक omap2_pwrdm_set_logic_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 pwrst)
अणु
	u32 v;

	v = pwrst << __ffs(OMAP_LOGICRETSTATE_MASK);
	omap2_prm_rmw_mod_reg_bits(OMAP_LOGICRETSTATE_MASK, v, pwrdm->prcm_offs,
				   OMAP2_PM_PWSTCTRL);

	वापस 0;
पूर्ण

पूर्णांक omap2_pwrdm_रुको_transition(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	u32 c = 0;

	/*
	 * REVISIT: pwrdm_रुको_transition() may be better implemented
	 * via a callback and a periodic समयr check -- how दीर्घ करो we expect
	 * घातerकरोमुख्य transitions to take?
	 */

	/* XXX Is this udelay() value meaningful? */
	जबतक ((omap2_prm_पढ़ो_mod_reg(pwrdm->prcm_offs, OMAP2_PM_PWSTST) &
		OMAP_INTRANSITION_MASK) &&
		(c++ < PWRDM_TRANSITION_BAILOUT))
			udelay(1);

	अगर (c > PWRDM_TRANSITION_BAILOUT) अणु
		pr_err("powerdomain: %s: waited too long to complete transition\n",
		       pwrdm->name);
		वापस -EAGAIN;
	पूर्ण

	pr_debug("powerdomain: completed transition in %d loops\n", c);

	वापस 0;
पूर्ण

पूर्णांक omap2_clkdm_add_wkdep(काष्ठा घड़ीकरोमुख्य *clkdm1,
			  काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	omap2_prm_set_mod_reg_bits((1 << clkdm2->dep_bit),
				   clkdm1->pwrdm.ptr->prcm_offs, PM_WKDEP);
	वापस 0;
पूर्ण

पूर्णांक omap2_clkdm_del_wkdep(काष्ठा घड़ीकरोमुख्य *clkdm1,
			  काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	omap2_prm_clear_mod_reg_bits((1 << clkdm2->dep_bit),
				     clkdm1->pwrdm.ptr->prcm_offs, PM_WKDEP);
	वापस 0;
पूर्ण

पूर्णांक omap2_clkdm_पढ़ो_wkdep(काष्ठा घड़ीकरोमुख्य *clkdm1,
			   काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	वापस omap2_prm_पढ़ो_mod_bits_shअगरt(clkdm1->pwrdm.ptr->prcm_offs,
					     PM_WKDEP, (1 << clkdm2->dep_bit));
पूर्ण

/* XXX Caller must hold the clkdm's घातerकरोमुख्य lock */
पूर्णांक omap2_clkdm_clear_all_wkdeps(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	काष्ठा clkdm_dep *cd;
	u32 mask = 0;

	क्रम (cd = clkdm->wkdep_srcs; cd && cd->clkdm_name; cd++) अणु
		अगर (!cd->clkdm)
			जारी; /* only happens अगर data is erroneous */

		/* PRM accesses are slow, so minimize them */
		mask |= 1 << cd->clkdm->dep_bit;
		cd->wkdep_usecount = 0;
	पूर्ण

	omap2_prm_clear_mod_reg_bits(mask, clkdm->pwrdm.ptr->prcm_offs,
				     PM_WKDEP);
	वापस 0;
पूर्ण

