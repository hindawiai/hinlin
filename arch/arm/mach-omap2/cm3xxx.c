<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP3xxx CM module functions
 *
 * Copyright (C) 2009 Nokia Corporation
 * Copyright (C) 2008-2010, 2012 Texas Instruments, Inc.
 * Paul Walmsley
 * Rajendra Nayak <rnayak@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>

#समावेश "prm2xxx_3xxx.h"
#समावेश "cm.h"
#समावेश "cm3xxx.h"
#समावेश "cm-regbits-34xx.h"
#समावेश "clockdomain.h"

अटल स्थिर u8 omap3xxx_cm_idlest_offs[] = अणु
	CM_IDLEST1, CM_IDLEST2, OMAP2430_CM_IDLEST3
पूर्ण;

/*
 *
 */

अटल व्योम _ग_लिखो_clktrctrl(u8 c, s16 module, u32 mask)
अणु
	u32 v;

	v = omap2_cm_पढ़ो_mod_reg(module, OMAP2_CM_CLKSTCTRL);
	v &= ~mask;
	v |= c << __ffs(mask);
	omap2_cm_ग_लिखो_mod_reg(v, module, OMAP2_CM_CLKSTCTRL);
पूर्ण

अटल bool omap3xxx_cm_is_clkdm_in_hwsup(s16 module, u32 mask)
अणु
	u32 v;

	v = omap2_cm_पढ़ो_mod_reg(module, OMAP2_CM_CLKSTCTRL);
	v &= mask;
	v >>= __ffs(mask);

	वापस (v == OMAP34XX_CLKSTCTRL_ENABLE_AUTO) ? 1 : 0;
पूर्ण

अटल व्योम omap3xxx_cm_clkdm_enable_hwsup(s16 module, u32 mask)
अणु
	_ग_लिखो_clktrctrl(OMAP34XX_CLKSTCTRL_ENABLE_AUTO, module, mask);
पूर्ण

अटल व्योम omap3xxx_cm_clkdm_disable_hwsup(s16 module, u32 mask)
अणु
	_ग_लिखो_clktrctrl(OMAP34XX_CLKSTCTRL_DISABLE_AUTO, module, mask);
पूर्ण

अटल व्योम omap3xxx_cm_clkdm_क्रमce_sleep(s16 module, u32 mask)
अणु
	_ग_लिखो_clktrctrl(OMAP34XX_CLKSTCTRL_FORCE_SLEEP, module, mask);
पूर्ण

अटल व्योम omap3xxx_cm_clkdm_क्रमce_wakeup(s16 module, u32 mask)
अणु
	_ग_लिखो_clktrctrl(OMAP34XX_CLKSTCTRL_FORCE_WAKEUP, module, mask);
पूर्ण

/*
 *
 */

/**
 * omap3xxx_cm_रुको_module_पढ़ोy - रुको क्रम a module to leave idle or standby
 * @part: PRCM partition, ignored क्रम OMAP3
 * @prcm_mod: PRCM module offset
 * @idlest_id: CM_IDLESTx रेजिस्टर ID (i.e., x = 1, 2, 3)
 * @idlest_shअगरt: shअगरt of the bit in the CM_IDLEST* रेजिस्टर to check
 *
 * Wait क्रम the PRCM to indicate that the module identअगरied by
 * (@prcm_mod, @idlest_id, @idlest_shअगरt) is घड़ीed.  Return 0 upon
 * success or -EBUSY अगर the module करोesn't enable in समय.
 */
अटल पूर्णांक omap3xxx_cm_रुको_module_पढ़ोy(u8 part, s16 prcm_mod, u16 idlest_id,
					 u8 idlest_shअगरt)
अणु
	पूर्णांक ena = 0, i = 0;
	u8 cm_idlest_reg;
	u32 mask;

	अगर (!idlest_id || (idlest_id > ARRAY_SIZE(omap3xxx_cm_idlest_offs)))
		वापस -EINVAL;

	cm_idlest_reg = omap3xxx_cm_idlest_offs[idlest_id - 1];

	mask = 1 << idlest_shअगरt;
	ena = 0;

	omap_test_समयout(((omap2_cm_पढ़ो_mod_reg(prcm_mod, cm_idlest_reg) &
			    mask) == ena), MAX_MODULE_READY_TIME, i);

	वापस (i < MAX_MODULE_READY_TIME) ? 0 : -EBUSY;
पूर्ण

/**
 * omap3xxx_cm_split_idlest_reg - split CM_IDLEST reg addr पूर्णांकo its components
 * @idlest_reg: CM_IDLEST* भव address
 * @prcm_inst: poपूर्णांकer to an s16 to वापस the PRCM instance offset
 * @idlest_reg_id: poपूर्णांकer to a u8 to वापस the CM_IDLESTx रेजिस्टर ID
 *
 * XXX This function is only needed until असलolute रेजिस्टर addresses are
 * हटाओd from the OMAP काष्ठा clk records.
 */
अटल पूर्णांक omap3xxx_cm_split_idlest_reg(काष्ठा clk_omap_reg *idlest_reg,
					s16 *prcm_inst,
					u8 *idlest_reg_id)
अणु
	अचिन्हित दीर्घ offs;
	u8 idlest_offs;
	पूर्णांक i;

	idlest_offs = idlest_reg->offset & 0xff;
	क्रम (i = 0; i < ARRAY_SIZE(omap3xxx_cm_idlest_offs); i++) अणु
		अगर (idlest_offs == omap3xxx_cm_idlest_offs[i]) अणु
			*idlest_reg_id = i + 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(omap3xxx_cm_idlest_offs))
		वापस -EINVAL;

	offs = idlest_reg->offset;
	offs &= 0xff00;
	*prcm_inst = offs;

	वापस 0;
पूर्ण

/* Clockकरोमुख्य low-level operations */

अटल पूर्णांक omap3xxx_clkdm_add_sleepdep(काष्ठा घड़ीकरोमुख्य *clkdm1,
				       काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	omap2_cm_set_mod_reg_bits((1 << clkdm2->dep_bit),
				  clkdm1->pwrdm.ptr->prcm_offs,
				  OMAP3430_CM_SLEEPDEP);
	वापस 0;
पूर्ण

अटल पूर्णांक omap3xxx_clkdm_del_sleepdep(काष्ठा घड़ीकरोमुख्य *clkdm1,
				       काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	omap2_cm_clear_mod_reg_bits((1 << clkdm2->dep_bit),
				    clkdm1->pwrdm.ptr->prcm_offs,
				    OMAP3430_CM_SLEEPDEP);
	वापस 0;
पूर्ण

अटल पूर्णांक omap3xxx_clkdm_पढ़ो_sleepdep(काष्ठा घड़ीकरोमुख्य *clkdm1,
					काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	वापस omap2_cm_पढ़ो_mod_bits_shअगरt(clkdm1->pwrdm.ptr->prcm_offs,
					    OMAP3430_CM_SLEEPDEP,
					    (1 << clkdm2->dep_bit));
पूर्ण

अटल पूर्णांक omap3xxx_clkdm_clear_all_sleepdeps(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	काष्ठा clkdm_dep *cd;
	u32 mask = 0;

	क्रम (cd = clkdm->sleepdep_srcs; cd && cd->clkdm_name; cd++) अणु
		अगर (!cd->clkdm)
			जारी; /* only happens अगर data is erroneous */

		mask |= 1 << cd->clkdm->dep_bit;
		cd->sleepdep_usecount = 0;
	पूर्ण
	omap2_cm_clear_mod_reg_bits(mask, clkdm->pwrdm.ptr->prcm_offs,
				    OMAP3430_CM_SLEEPDEP);
	वापस 0;
पूर्ण

अटल पूर्णांक omap3xxx_clkdm_sleep(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	omap3xxx_cm_clkdm_क्रमce_sleep(clkdm->pwrdm.ptr->prcm_offs,
				      clkdm->clktrctrl_mask);
	वापस 0;
पूर्ण

अटल पूर्णांक omap3xxx_clkdm_wakeup(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	omap3xxx_cm_clkdm_क्रमce_wakeup(clkdm->pwrdm.ptr->prcm_offs,
				       clkdm->clktrctrl_mask);
	वापस 0;
पूर्ण

अटल व्योम omap3xxx_clkdm_allow_idle(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	अगर (clkdm->usecount > 0)
		clkdm_add_स्वतःdeps(clkdm);

	omap3xxx_cm_clkdm_enable_hwsup(clkdm->pwrdm.ptr->prcm_offs,
				       clkdm->clktrctrl_mask);
पूर्ण

अटल व्योम omap3xxx_clkdm_deny_idle(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	omap3xxx_cm_clkdm_disable_hwsup(clkdm->pwrdm.ptr->prcm_offs,
					clkdm->clktrctrl_mask);

	अगर (clkdm->usecount > 0)
		clkdm_del_स्वतःdeps(clkdm);
पूर्ण

अटल पूर्णांक omap3xxx_clkdm_clk_enable(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	bool hwsup = false;

	अगर (!clkdm->clktrctrl_mask)
		वापस 0;

	/*
	 * The CLKDM_MISSING_IDLE_REPORTING flag करोcumentation has
	 * more details on the unpleasant problem this is working
	 * around
	 */
	अगर ((clkdm->flags & CLKDM_MISSING_IDLE_REPORTING) &&
	    (clkdm->flags & CLKDM_CAN_FORCE_WAKEUP)) अणु
		omap3xxx_clkdm_wakeup(clkdm);
		वापस 0;
	पूर्ण

	hwsup = omap3xxx_cm_is_clkdm_in_hwsup(clkdm->pwrdm.ptr->prcm_offs,
					      clkdm->clktrctrl_mask);

	अगर (hwsup) अणु
		/* Disable HW transitions when we are changing deps */
		omap3xxx_cm_clkdm_disable_hwsup(clkdm->pwrdm.ptr->prcm_offs,
						clkdm->clktrctrl_mask);
		clkdm_add_स्वतःdeps(clkdm);
		omap3xxx_cm_clkdm_enable_hwsup(clkdm->pwrdm.ptr->prcm_offs,
					       clkdm->clktrctrl_mask);
	पूर्ण अन्यथा अणु
		अगर (clkdm->flags & CLKDM_CAN_FORCE_WAKEUP)
			omap3xxx_clkdm_wakeup(clkdm);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap3xxx_clkdm_clk_disable(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	bool hwsup = false;

	अगर (!clkdm->clktrctrl_mask)
		वापस 0;

	/*
	 * The CLKDM_MISSING_IDLE_REPORTING flag करोcumentation has
	 * more details on the unpleasant problem this is working
	 * around
	 */
	अगर (clkdm->flags & CLKDM_MISSING_IDLE_REPORTING &&
	    !(clkdm->flags & CLKDM_CAN_FORCE_SLEEP)) अणु
		omap3xxx_cm_clkdm_enable_hwsup(clkdm->pwrdm.ptr->prcm_offs,
					       clkdm->clktrctrl_mask);
		वापस 0;
	पूर्ण

	hwsup = omap3xxx_cm_is_clkdm_in_hwsup(clkdm->pwrdm.ptr->prcm_offs,
					      clkdm->clktrctrl_mask);

	अगर (hwsup) अणु
		/* Disable HW transitions when we are changing deps */
		omap3xxx_cm_clkdm_disable_hwsup(clkdm->pwrdm.ptr->prcm_offs,
						clkdm->clktrctrl_mask);
		clkdm_del_स्वतःdeps(clkdm);
		omap3xxx_cm_clkdm_enable_hwsup(clkdm->pwrdm.ptr->prcm_offs,
					       clkdm->clktrctrl_mask);
	पूर्ण अन्यथा अणु
		अगर (clkdm->flags & CLKDM_CAN_FORCE_SLEEP)
			omap3xxx_clkdm_sleep(clkdm);
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा clkdm_ops omap3_clkdm_operations = अणु
	.clkdm_add_wkdep	= omap2_clkdm_add_wkdep,
	.clkdm_del_wkdep	= omap2_clkdm_del_wkdep,
	.clkdm_पढ़ो_wkdep	= omap2_clkdm_पढ़ो_wkdep,
	.clkdm_clear_all_wkdeps	= omap2_clkdm_clear_all_wkdeps,
	.clkdm_add_sleepdep	= omap3xxx_clkdm_add_sleepdep,
	.clkdm_del_sleepdep	= omap3xxx_clkdm_del_sleepdep,
	.clkdm_पढ़ो_sleepdep	= omap3xxx_clkdm_पढ़ो_sleepdep,
	.clkdm_clear_all_sleepdeps	= omap3xxx_clkdm_clear_all_sleepdeps,
	.clkdm_sleep		= omap3xxx_clkdm_sleep,
	.clkdm_wakeup		= omap3xxx_clkdm_wakeup,
	.clkdm_allow_idle	= omap3xxx_clkdm_allow_idle,
	.clkdm_deny_idle	= omap3xxx_clkdm_deny_idle,
	.clkdm_clk_enable	= omap3xxx_clkdm_clk_enable,
	.clkdm_clk_disable	= omap3xxx_clkdm_clk_disable,
पूर्ण;

/*
 * Context save/restore code - OMAP3 only
 */
काष्ठा omap3_cm_regs अणु
	u32 iva2_cm_clksel1;
	u32 iva2_cm_clksel2;
	u32 cm_sysconfig;
	u32 sgx_cm_clksel;
	u32 dss_cm_clksel;
	u32 cam_cm_clksel;
	u32 per_cm_clksel;
	u32 emu_cm_clksel;
	u32 emu_cm_clkstctrl;
	u32 pll_cm_स्वतःidle;
	u32 pll_cm_स्वतःidle2;
	u32 pll_cm_clksel4;
	u32 pll_cm_clksel5;
	u32 pll_cm_clken2;
	u32 cm_polctrl;
	u32 iva2_cm_fclken;
	u32 iva2_cm_clken_pll;
	u32 core_cm_fclken1;
	u32 core_cm_fclken3;
	u32 sgx_cm_fclken;
	u32 wkup_cm_fclken;
	u32 dss_cm_fclken;
	u32 cam_cm_fclken;
	u32 per_cm_fclken;
	u32 usbhost_cm_fclken;
	u32 core_cm_iclken1;
	u32 core_cm_iclken2;
	u32 core_cm_iclken3;
	u32 sgx_cm_iclken;
	u32 wkup_cm_iclken;
	u32 dss_cm_iclken;
	u32 cam_cm_iclken;
	u32 per_cm_iclken;
	u32 usbhost_cm_iclken;
	u32 iva2_cm_स्वतःidle2;
	u32 mpu_cm_स्वतःidle2;
	u32 iva2_cm_clkstctrl;
	u32 mpu_cm_clkstctrl;
	u32 core_cm_clkstctrl;
	u32 sgx_cm_clkstctrl;
	u32 dss_cm_clkstctrl;
	u32 cam_cm_clkstctrl;
	u32 per_cm_clkstctrl;
	u32 neon_cm_clkstctrl;
	u32 usbhost_cm_clkstctrl;
	u32 core_cm_स्वतःidle1;
	u32 core_cm_स्वतःidle2;
	u32 core_cm_स्वतःidle3;
	u32 wkup_cm_स्वतःidle;
	u32 dss_cm_स्वतःidle;
	u32 cam_cm_स्वतःidle;
	u32 per_cm_स्वतःidle;
	u32 usbhost_cm_स्वतःidle;
	u32 sgx_cm_sleepdep;
	u32 dss_cm_sleepdep;
	u32 cam_cm_sleepdep;
	u32 per_cm_sleepdep;
	u32 usbhost_cm_sleepdep;
	u32 cm_clkout_ctrl;
पूर्ण;

अटल काष्ठा omap3_cm_regs cm_context;

व्योम omap3_cm_save_context(व्योम)
अणु
	cm_context.iva2_cm_clksel1 =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_IVA2_MOD, CM_CLKSEL1);
	cm_context.iva2_cm_clksel2 =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_IVA2_MOD, CM_CLKSEL2);
	cm_context.cm_sysconfig =
		omap2_cm_पढ़ो_mod_reg(OCP_MOD, OMAP3430_CM_SYSCONFIG);
	cm_context.sgx_cm_clksel =
		omap2_cm_पढ़ो_mod_reg(OMAP3430ES2_SGX_MOD, CM_CLKSEL);
	cm_context.dss_cm_clksel =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_DSS_MOD, CM_CLKSEL);
	cm_context.cam_cm_clksel =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_CAM_MOD, CM_CLKSEL);
	cm_context.per_cm_clksel =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_PER_MOD, CM_CLKSEL);
	cm_context.emu_cm_clksel =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_EMU_MOD, CM_CLKSEL1);
	cm_context.emu_cm_clkstctrl =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_EMU_MOD, OMAP2_CM_CLKSTCTRL);
	/*
	 * As per erratum i671, ROM code करोes not respect the PER DPLL
	 * programming scheme अगर CM_AUTOIDLE_PLL.AUTO_PERIPH_DPLL == 1.
	 * In this हाल, even though this रेजिस्टर has been saved in
	 * scratchpad contents, we need to restore AUTO_PERIPH_DPLL
	 * by ourselves. So, we need to save it anyway.
	 */
	cm_context.pll_cm_स्वतःidle =
		omap2_cm_पढ़ो_mod_reg(PLL_MOD, CM_AUTOIDLE);
	cm_context.pll_cm_स्वतःidle2 =
		omap2_cm_पढ़ो_mod_reg(PLL_MOD, CM_AUTOIDLE2);
	cm_context.pll_cm_clksel4 =
		omap2_cm_पढ़ो_mod_reg(PLL_MOD, OMAP3430ES2_CM_CLKSEL4);
	cm_context.pll_cm_clksel5 =
		omap2_cm_पढ़ो_mod_reg(PLL_MOD, OMAP3430ES2_CM_CLKSEL5);
	cm_context.pll_cm_clken2 =
		omap2_cm_पढ़ो_mod_reg(PLL_MOD, OMAP3430ES2_CM_CLKEN2);
	cm_context.cm_polctrl =
		omap2_cm_पढ़ो_mod_reg(OCP_MOD, OMAP3430_CM_POLCTRL);
	cm_context.iva2_cm_fclken =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_IVA2_MOD, CM_FCLKEN);
	cm_context.iva2_cm_clken_pll =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_IVA2_MOD, OMAP3430_CM_CLKEN_PLL);
	cm_context.core_cm_fclken1 =
		omap2_cm_पढ़ो_mod_reg(CORE_MOD, CM_FCLKEN1);
	cm_context.core_cm_fclken3 =
		omap2_cm_पढ़ो_mod_reg(CORE_MOD, OMAP3430ES2_CM_FCLKEN3);
	cm_context.sgx_cm_fclken =
		omap2_cm_पढ़ो_mod_reg(OMAP3430ES2_SGX_MOD, CM_FCLKEN);
	cm_context.wkup_cm_fclken =
		omap2_cm_पढ़ो_mod_reg(WKUP_MOD, CM_FCLKEN);
	cm_context.dss_cm_fclken =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_DSS_MOD, CM_FCLKEN);
	cm_context.cam_cm_fclken =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_CAM_MOD, CM_FCLKEN);
	cm_context.per_cm_fclken =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_PER_MOD, CM_FCLKEN);
	cm_context.usbhost_cm_fclken =
		omap2_cm_पढ़ो_mod_reg(OMAP3430ES2_USBHOST_MOD, CM_FCLKEN);
	cm_context.core_cm_iclken1 =
		omap2_cm_पढ़ो_mod_reg(CORE_MOD, CM_ICLKEN1);
	cm_context.core_cm_iclken2 =
		omap2_cm_पढ़ो_mod_reg(CORE_MOD, CM_ICLKEN2);
	cm_context.core_cm_iclken3 =
		omap2_cm_पढ़ो_mod_reg(CORE_MOD, CM_ICLKEN3);
	cm_context.sgx_cm_iclken =
		omap2_cm_पढ़ो_mod_reg(OMAP3430ES2_SGX_MOD, CM_ICLKEN);
	cm_context.wkup_cm_iclken =
		omap2_cm_पढ़ो_mod_reg(WKUP_MOD, CM_ICLKEN);
	cm_context.dss_cm_iclken =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_DSS_MOD, CM_ICLKEN);
	cm_context.cam_cm_iclken =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_CAM_MOD, CM_ICLKEN);
	cm_context.per_cm_iclken =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_PER_MOD, CM_ICLKEN);
	cm_context.usbhost_cm_iclken =
		omap2_cm_पढ़ो_mod_reg(OMAP3430ES2_USBHOST_MOD, CM_ICLKEN);
	cm_context.iva2_cm_स्वतःidle2 =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_IVA2_MOD, CM_AUTOIDLE2);
	cm_context.mpu_cm_स्वतःidle2 =
		omap2_cm_पढ़ो_mod_reg(MPU_MOD, CM_AUTOIDLE2);
	cm_context.iva2_cm_clkstctrl =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_IVA2_MOD, OMAP2_CM_CLKSTCTRL);
	cm_context.mpu_cm_clkstctrl =
		omap2_cm_पढ़ो_mod_reg(MPU_MOD, OMAP2_CM_CLKSTCTRL);
	cm_context.core_cm_clkstctrl =
		omap2_cm_पढ़ो_mod_reg(CORE_MOD, OMAP2_CM_CLKSTCTRL);
	cm_context.sgx_cm_clkstctrl =
		omap2_cm_पढ़ो_mod_reg(OMAP3430ES2_SGX_MOD, OMAP2_CM_CLKSTCTRL);
	cm_context.dss_cm_clkstctrl =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_DSS_MOD, OMAP2_CM_CLKSTCTRL);
	cm_context.cam_cm_clkstctrl =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_CAM_MOD, OMAP2_CM_CLKSTCTRL);
	cm_context.per_cm_clkstctrl =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_PER_MOD, OMAP2_CM_CLKSTCTRL);
	cm_context.neon_cm_clkstctrl =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_NEON_MOD, OMAP2_CM_CLKSTCTRL);
	cm_context.usbhost_cm_clkstctrl =
		omap2_cm_पढ़ो_mod_reg(OMAP3430ES2_USBHOST_MOD,
				      OMAP2_CM_CLKSTCTRL);
	cm_context.core_cm_स्वतःidle1 =
		omap2_cm_पढ़ो_mod_reg(CORE_MOD, CM_AUTOIDLE1);
	cm_context.core_cm_स्वतःidle2 =
		omap2_cm_पढ़ो_mod_reg(CORE_MOD, CM_AUTOIDLE2);
	cm_context.core_cm_स्वतःidle3 =
		omap2_cm_पढ़ो_mod_reg(CORE_MOD, CM_AUTOIDLE3);
	cm_context.wkup_cm_स्वतःidle =
		omap2_cm_पढ़ो_mod_reg(WKUP_MOD, CM_AUTOIDLE);
	cm_context.dss_cm_स्वतःidle =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_DSS_MOD, CM_AUTOIDLE);
	cm_context.cam_cm_स्वतःidle =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_CAM_MOD, CM_AUTOIDLE);
	cm_context.per_cm_स्वतःidle =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_PER_MOD, CM_AUTOIDLE);
	cm_context.usbhost_cm_स्वतःidle =
		omap2_cm_पढ़ो_mod_reg(OMAP3430ES2_USBHOST_MOD, CM_AUTOIDLE);
	cm_context.sgx_cm_sleepdep =
		omap2_cm_पढ़ो_mod_reg(OMAP3430ES2_SGX_MOD,
				      OMAP3430_CM_SLEEPDEP);
	cm_context.dss_cm_sleepdep =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_DSS_MOD, OMAP3430_CM_SLEEPDEP);
	cm_context.cam_cm_sleepdep =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_CAM_MOD, OMAP3430_CM_SLEEPDEP);
	cm_context.per_cm_sleepdep =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_PER_MOD, OMAP3430_CM_SLEEPDEP);
	cm_context.usbhost_cm_sleepdep =
		omap2_cm_पढ़ो_mod_reg(OMAP3430ES2_USBHOST_MOD,
				      OMAP3430_CM_SLEEPDEP);
	cm_context.cm_clkout_ctrl =
		omap2_cm_पढ़ो_mod_reg(OMAP3430_CCR_MOD,
				      OMAP3_CM_CLKOUT_CTRL_OFFSET);
पूर्ण

व्योम omap3_cm_restore_context(व्योम)
अणु
	omap2_cm_ग_लिखो_mod_reg(cm_context.iva2_cm_clksel1, OMAP3430_IVA2_MOD,
			       CM_CLKSEL1);
	omap2_cm_ग_लिखो_mod_reg(cm_context.iva2_cm_clksel2, OMAP3430_IVA2_MOD,
			       CM_CLKSEL2);
	omap2_cm_ग_लिखो_mod_reg(cm_context.cm_sysconfig, OCP_MOD,
			       OMAP3430_CM_SYSCONFIG);
	omap2_cm_ग_लिखो_mod_reg(cm_context.sgx_cm_clksel, OMAP3430ES2_SGX_MOD,
			       CM_CLKSEL);
	omap2_cm_ग_लिखो_mod_reg(cm_context.dss_cm_clksel, OMAP3430_DSS_MOD,
			       CM_CLKSEL);
	omap2_cm_ग_लिखो_mod_reg(cm_context.cam_cm_clksel, OMAP3430_CAM_MOD,
			       CM_CLKSEL);
	omap2_cm_ग_लिखो_mod_reg(cm_context.per_cm_clksel, OMAP3430_PER_MOD,
			       CM_CLKSEL);
	omap2_cm_ग_लिखो_mod_reg(cm_context.emu_cm_clksel, OMAP3430_EMU_MOD,
			       CM_CLKSEL1);
	omap2_cm_ग_लिखो_mod_reg(cm_context.emu_cm_clkstctrl, OMAP3430_EMU_MOD,
			       OMAP2_CM_CLKSTCTRL);
	/*
	 * As per erratum i671, ROM code करोes not respect the PER DPLL
	 * programming scheme अगर CM_AUTOIDLE_PLL.AUTO_PERIPH_DPLL == 1.
	 * In this हाल, we need to restore AUTO_PERIPH_DPLL by ourselves.
	 */
	omap2_cm_ग_लिखो_mod_reg(cm_context.pll_cm_स्वतःidle, PLL_MOD,
			       CM_AUTOIDLE);
	omap2_cm_ग_लिखो_mod_reg(cm_context.pll_cm_स्वतःidle2, PLL_MOD,
			       CM_AUTOIDLE2);
	omap2_cm_ग_लिखो_mod_reg(cm_context.pll_cm_clksel4, PLL_MOD,
			       OMAP3430ES2_CM_CLKSEL4);
	omap2_cm_ग_लिखो_mod_reg(cm_context.pll_cm_clksel5, PLL_MOD,
			       OMAP3430ES2_CM_CLKSEL5);
	omap2_cm_ग_लिखो_mod_reg(cm_context.pll_cm_clken2, PLL_MOD,
			       OMAP3430ES2_CM_CLKEN2);
	omap2_cm_ग_लिखो_mod_reg(cm_context.cm_polctrl, OCP_MOD,
			       OMAP3430_CM_POLCTRL);
	omap2_cm_ग_लिखो_mod_reg(cm_context.iva2_cm_fclken, OMAP3430_IVA2_MOD,
			       CM_FCLKEN);
	omap2_cm_ग_लिखो_mod_reg(cm_context.iva2_cm_clken_pll, OMAP3430_IVA2_MOD,
			       OMAP3430_CM_CLKEN_PLL);
	omap2_cm_ग_लिखो_mod_reg(cm_context.core_cm_fclken1, CORE_MOD,
			       CM_FCLKEN1);
	omap2_cm_ग_लिखो_mod_reg(cm_context.core_cm_fclken3, CORE_MOD,
			       OMAP3430ES2_CM_FCLKEN3);
	omap2_cm_ग_लिखो_mod_reg(cm_context.sgx_cm_fclken, OMAP3430ES2_SGX_MOD,
			       CM_FCLKEN);
	omap2_cm_ग_लिखो_mod_reg(cm_context.wkup_cm_fclken, WKUP_MOD, CM_FCLKEN);
	omap2_cm_ग_लिखो_mod_reg(cm_context.dss_cm_fclken, OMAP3430_DSS_MOD,
			       CM_FCLKEN);
	omap2_cm_ग_लिखो_mod_reg(cm_context.cam_cm_fclken, OMAP3430_CAM_MOD,
			       CM_FCLKEN);
	omap2_cm_ग_लिखो_mod_reg(cm_context.per_cm_fclken, OMAP3430_PER_MOD,
			       CM_FCLKEN);
	omap2_cm_ग_लिखो_mod_reg(cm_context.usbhost_cm_fclken,
			       OMAP3430ES2_USBHOST_MOD, CM_FCLKEN);
	omap2_cm_ग_लिखो_mod_reg(cm_context.core_cm_iclken1, CORE_MOD,
			       CM_ICLKEN1);
	omap2_cm_ग_लिखो_mod_reg(cm_context.core_cm_iclken2, CORE_MOD,
			       CM_ICLKEN2);
	omap2_cm_ग_लिखो_mod_reg(cm_context.core_cm_iclken3, CORE_MOD,
			       CM_ICLKEN3);
	omap2_cm_ग_लिखो_mod_reg(cm_context.sgx_cm_iclken, OMAP3430ES2_SGX_MOD,
			       CM_ICLKEN);
	omap2_cm_ग_लिखो_mod_reg(cm_context.wkup_cm_iclken, WKUP_MOD, CM_ICLKEN);
	omap2_cm_ग_लिखो_mod_reg(cm_context.dss_cm_iclken, OMAP3430_DSS_MOD,
			       CM_ICLKEN);
	omap2_cm_ग_लिखो_mod_reg(cm_context.cam_cm_iclken, OMAP3430_CAM_MOD,
			       CM_ICLKEN);
	omap2_cm_ग_लिखो_mod_reg(cm_context.per_cm_iclken, OMAP3430_PER_MOD,
			       CM_ICLKEN);
	omap2_cm_ग_लिखो_mod_reg(cm_context.usbhost_cm_iclken,
			       OMAP3430ES2_USBHOST_MOD, CM_ICLKEN);
	omap2_cm_ग_लिखो_mod_reg(cm_context.iva2_cm_स्वतःidle2, OMAP3430_IVA2_MOD,
			       CM_AUTOIDLE2);
	omap2_cm_ग_लिखो_mod_reg(cm_context.mpu_cm_स्वतःidle2, MPU_MOD,
			       CM_AUTOIDLE2);
	omap2_cm_ग_लिखो_mod_reg(cm_context.iva2_cm_clkstctrl, OMAP3430_IVA2_MOD,
			       OMAP2_CM_CLKSTCTRL);
	omap2_cm_ग_लिखो_mod_reg(cm_context.mpu_cm_clkstctrl, MPU_MOD,
			       OMAP2_CM_CLKSTCTRL);
	omap2_cm_ग_लिखो_mod_reg(cm_context.core_cm_clkstctrl, CORE_MOD,
			       OMAP2_CM_CLKSTCTRL);
	omap2_cm_ग_लिखो_mod_reg(cm_context.sgx_cm_clkstctrl, OMAP3430ES2_SGX_MOD,
			       OMAP2_CM_CLKSTCTRL);
	omap2_cm_ग_लिखो_mod_reg(cm_context.dss_cm_clkstctrl, OMAP3430_DSS_MOD,
			       OMAP2_CM_CLKSTCTRL);
	omap2_cm_ग_लिखो_mod_reg(cm_context.cam_cm_clkstctrl, OMAP3430_CAM_MOD,
			       OMAP2_CM_CLKSTCTRL);
	omap2_cm_ग_लिखो_mod_reg(cm_context.per_cm_clkstctrl, OMAP3430_PER_MOD,
			       OMAP2_CM_CLKSTCTRL);
	omap2_cm_ग_लिखो_mod_reg(cm_context.neon_cm_clkstctrl, OMAP3430_NEON_MOD,
			       OMAP2_CM_CLKSTCTRL);
	omap2_cm_ग_लिखो_mod_reg(cm_context.usbhost_cm_clkstctrl,
			       OMAP3430ES2_USBHOST_MOD, OMAP2_CM_CLKSTCTRL);
	omap2_cm_ग_लिखो_mod_reg(cm_context.core_cm_स्वतःidle1, CORE_MOD,
			       CM_AUTOIDLE1);
	omap2_cm_ग_लिखो_mod_reg(cm_context.core_cm_स्वतःidle2, CORE_MOD,
			       CM_AUTOIDLE2);
	omap2_cm_ग_लिखो_mod_reg(cm_context.core_cm_स्वतःidle3, CORE_MOD,
			       CM_AUTOIDLE3);
	omap2_cm_ग_लिखो_mod_reg(cm_context.wkup_cm_स्वतःidle, WKUP_MOD,
			       CM_AUTOIDLE);
	omap2_cm_ग_लिखो_mod_reg(cm_context.dss_cm_स्वतःidle, OMAP3430_DSS_MOD,
			       CM_AUTOIDLE);
	omap2_cm_ग_लिखो_mod_reg(cm_context.cam_cm_स्वतःidle, OMAP3430_CAM_MOD,
			       CM_AUTOIDLE);
	omap2_cm_ग_लिखो_mod_reg(cm_context.per_cm_स्वतःidle, OMAP3430_PER_MOD,
			       CM_AUTOIDLE);
	omap2_cm_ग_लिखो_mod_reg(cm_context.usbhost_cm_स्वतःidle,
			       OMAP3430ES2_USBHOST_MOD, CM_AUTOIDLE);
	omap2_cm_ग_लिखो_mod_reg(cm_context.sgx_cm_sleepdep, OMAP3430ES2_SGX_MOD,
			       OMAP3430_CM_SLEEPDEP);
	omap2_cm_ग_लिखो_mod_reg(cm_context.dss_cm_sleepdep, OMAP3430_DSS_MOD,
			       OMAP3430_CM_SLEEPDEP);
	omap2_cm_ग_लिखो_mod_reg(cm_context.cam_cm_sleepdep, OMAP3430_CAM_MOD,
			       OMAP3430_CM_SLEEPDEP);
	omap2_cm_ग_लिखो_mod_reg(cm_context.per_cm_sleepdep, OMAP3430_PER_MOD,
			       OMAP3430_CM_SLEEPDEP);
	omap2_cm_ग_लिखो_mod_reg(cm_context.usbhost_cm_sleepdep,
			       OMAP3430ES2_USBHOST_MOD, OMAP3430_CM_SLEEPDEP);
	omap2_cm_ग_लिखो_mod_reg(cm_context.cm_clkout_ctrl, OMAP3430_CCR_MOD,
			       OMAP3_CM_CLKOUT_CTRL_OFFSET);
पूर्ण

व्योम omap3_cm_save_scratchpad_contents(u32 *ptr)
अणु
	*ptr++ = omap2_cm_पढ़ो_mod_reg(CORE_MOD, CM_CLKSEL);
	*ptr++ = omap2_cm_पढ़ो_mod_reg(WKUP_MOD, CM_CLKSEL);
	*ptr++ = omap2_cm_पढ़ो_mod_reg(PLL_MOD, CM_CLKEN);

	/*
	 * As per erratum i671, ROM code करोes not respect the PER DPLL
	 * programming scheme अगर CM_AUTOIDLE_PLL..AUTO_PERIPH_DPLL == 1.
	 * Then,  in any हाल, clear these bits to aव्योम extra latencies.
	 */
	*ptr++ = omap2_cm_पढ़ो_mod_reg(PLL_MOD, CM_AUTOIDLE) &
		~OMAP3430_AUTO_PERIPH_DPLL_MASK;
	*ptr++ = omap2_cm_पढ़ो_mod_reg(PLL_MOD, OMAP3430_CM_CLKSEL1_PLL);
	*ptr++ = omap2_cm_पढ़ो_mod_reg(PLL_MOD, OMAP3430_CM_CLKSEL2_PLL);
	*ptr++ = omap2_cm_पढ़ो_mod_reg(PLL_MOD, OMAP3430_CM_CLKSEL3);
	*ptr++ = omap2_cm_पढ़ो_mod_reg(MPU_MOD, OMAP3430_CM_CLKEN_PLL);
	*ptr++ = omap2_cm_पढ़ो_mod_reg(MPU_MOD, OMAP3430_CM_AUTOIDLE_PLL);
	*ptr++ = omap2_cm_पढ़ो_mod_reg(MPU_MOD, OMAP3430_CM_CLKSEL1_PLL);
	*ptr++ = omap2_cm_पढ़ो_mod_reg(MPU_MOD, OMAP3430_CM_CLKSEL2_PLL);
पूर्ण

/*
 *
 */

अटल स्थिर काष्ठा cm_ll_data omap3xxx_cm_ll_data = अणु
	.split_idlest_reg	= &omap3xxx_cm_split_idlest_reg,
	.रुको_module_पढ़ोy	= &omap3xxx_cm_रुको_module_पढ़ोy,
पूर्ण;

पूर्णांक __init omap3xxx_cm_init(स्थिर काष्ठा omap_prcm_init_data *data)
अणु
	omap2_clk_legacy_provider_init(TI_CLKM_CM, cm_base.va +
				       OMAP3430_IVA2_MOD);
	वापस cm_रेजिस्टर(&omap3xxx_cm_ll_data);
पूर्ण

अटल व्योम __निकास omap3xxx_cm_निकास(व्योम)
अणु
	cm_unरेजिस्टर(&omap3xxx_cm_ll_data);
पूर्ण
__निकासcall(omap3xxx_cm_निकास);
