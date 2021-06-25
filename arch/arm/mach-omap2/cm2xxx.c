<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP2xxx CM module functions
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

#समावेश "prm2xxx.h"
#समावेश "cm.h"
#समावेश "cm2xxx.h"
#समावेश "cm-regbits-24xx.h"
#समावेश "clockdomain.h"

/* CM_AUTOIDLE_PLL.AUTO_* bit values क्रम DPLLs */
#घोषणा DPLL_AUTOIDLE_DISABLE				0x0
#घोषणा OMAP2XXX_DPLL_AUTOIDLE_LOW_POWER_STOP		0x3

/* CM_AUTOIDLE_PLL.AUTO_* bit values क्रम APLLs (OMAP2xxx only) */
#घोषणा OMAP2XXX_APLL_AUTOIDLE_DISABLE			0x0
#घोषणा OMAP2XXX_APLL_AUTOIDLE_LOW_POWER_STOP		0x3

/* CM_IDLEST_PLL bit value offset क्रम APLLs (OMAP2xxx only) */
#घोषणा EN_APLL_LOCKED					3

अटल स्थिर u8 omap2xxx_cm_idlest_offs[] = अणु
	CM_IDLEST1, CM_IDLEST2, OMAP2430_CM_IDLEST3, OMAP24XX_CM_IDLEST4
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

अटल bool omap2xxx_cm_is_clkdm_in_hwsup(s16 module, u32 mask)
अणु
	u32 v;

	v = omap2_cm_पढ़ो_mod_reg(module, OMAP2_CM_CLKSTCTRL);
	v &= mask;
	v >>= __ffs(mask);

	वापस (v == OMAP24XX_CLKSTCTRL_ENABLE_AUTO) ? 1 : 0;
पूर्ण

अटल व्योम omap2xxx_cm_clkdm_enable_hwsup(s16 module, u32 mask)
अणु
	_ग_लिखो_clktrctrl(OMAP24XX_CLKSTCTRL_ENABLE_AUTO, module, mask);
पूर्ण

अटल व्योम omap2xxx_cm_clkdm_disable_hwsup(s16 module, u32 mask)
अणु
	_ग_लिखो_clktrctrl(OMAP24XX_CLKSTCTRL_DISABLE_AUTO, module, mask);
पूर्ण

/*
 * DPLL स्वतःidle control
 */

अटल व्योम _omap2xxx_set_dpll_स्वतःidle(u8 m)
अणु
	u32 v;

	v = omap2_cm_पढ़ो_mod_reg(PLL_MOD, CM_AUTOIDLE);
	v &= ~OMAP24XX_AUTO_DPLL_MASK;
	v |= m << OMAP24XX_AUTO_DPLL_SHIFT;
	omap2_cm_ग_लिखो_mod_reg(v, PLL_MOD, CM_AUTOIDLE);
पूर्ण

व्योम omap2xxx_cm_set_dpll_disable_स्वतःidle(व्योम)
अणु
	_omap2xxx_set_dpll_स्वतःidle(OMAP2XXX_DPLL_AUTOIDLE_LOW_POWER_STOP);
पूर्ण

व्योम omap2xxx_cm_set_dpll_स्वतः_low_घातer_stop(व्योम)
अणु
	_omap2xxx_set_dpll_स्वतःidle(DPLL_AUTOIDLE_DISABLE);
पूर्ण

/*
 * APLL control
 */

अटल व्योम _omap2xxx_set_apll_स्वतःidle(u8 m, u32 mask)
अणु
	u32 v;

	v = omap2_cm_पढ़ो_mod_reg(PLL_MOD, CM_AUTOIDLE);
	v &= ~mask;
	v |= m << __ffs(mask);
	omap2_cm_ग_लिखो_mod_reg(v, PLL_MOD, CM_AUTOIDLE);
पूर्ण

व्योम omap2xxx_cm_set_apll54_disable_स्वतःidle(व्योम)
अणु
	_omap2xxx_set_apll_स्वतःidle(OMAP2XXX_APLL_AUTOIDLE_LOW_POWER_STOP,
				    OMAP24XX_AUTO_54M_MASK);
पूर्ण

व्योम omap2xxx_cm_set_apll54_स्वतः_low_घातer_stop(व्योम)
अणु
	_omap2xxx_set_apll_स्वतःidle(OMAP2XXX_APLL_AUTOIDLE_DISABLE,
				    OMAP24XX_AUTO_54M_MASK);
पूर्ण

व्योम omap2xxx_cm_set_apll96_disable_स्वतःidle(व्योम)
अणु
	_omap2xxx_set_apll_स्वतःidle(OMAP2XXX_APLL_AUTOIDLE_LOW_POWER_STOP,
				    OMAP24XX_AUTO_96M_MASK);
पूर्ण

व्योम omap2xxx_cm_set_apll96_स्वतः_low_घातer_stop(व्योम)
अणु
	_omap2xxx_set_apll_स्वतःidle(OMAP2XXX_APLL_AUTOIDLE_DISABLE,
				    OMAP24XX_AUTO_96M_MASK);
पूर्ण

/* Enable an APLL अगर off */
अटल पूर्णांक _omap2xxx_apll_enable(u8 enable_bit, u8 status_bit)
अणु
	u32 v, m;

	m = EN_APLL_LOCKED << enable_bit;

	v = omap2_cm_पढ़ो_mod_reg(PLL_MOD, CM_CLKEN);
	अगर (v & m)
		वापस 0;   /* apll alपढ़ोy enabled */

	v |= m;
	omap2_cm_ग_लिखो_mod_reg(v, PLL_MOD, CM_CLKEN);

	omap2xxx_cm_रुको_module_पढ़ोy(0, PLL_MOD, 1, status_bit);

	/*
	 * REVISIT: Should we वापस an error code अगर
	 * omap2xxx_cm_रुको_module_पढ़ोy() fails?
	 */
	वापस 0;
पूर्ण

/* Stop APLL */
अटल व्योम _omap2xxx_apll_disable(u8 enable_bit)
अणु
	u32 v;

	v = omap2_cm_पढ़ो_mod_reg(PLL_MOD, CM_CLKEN);
	v &= ~(EN_APLL_LOCKED << enable_bit);
	omap2_cm_ग_लिखो_mod_reg(v, PLL_MOD, CM_CLKEN);
पूर्ण

/* Enable an APLL अगर off */
पूर्णांक omap2xxx_cm_apll54_enable(व्योम)
अणु
	वापस _omap2xxx_apll_enable(OMAP24XX_EN_54M_PLL_SHIFT,
				     OMAP24XX_ST_54M_APLL_SHIFT);
पूर्ण

/* Enable an APLL अगर off */
पूर्णांक omap2xxx_cm_apll96_enable(व्योम)
अणु
	वापस _omap2xxx_apll_enable(OMAP24XX_EN_96M_PLL_SHIFT,
				     OMAP24XX_ST_96M_APLL_SHIFT);
पूर्ण

/* Stop APLL */
व्योम omap2xxx_cm_apll54_disable(व्योम)
अणु
	_omap2xxx_apll_disable(OMAP24XX_EN_54M_PLL_SHIFT);
पूर्ण

/* Stop APLL */
व्योम omap2xxx_cm_apll96_disable(व्योम)
अणु
	_omap2xxx_apll_disable(OMAP24XX_EN_96M_PLL_SHIFT);
पूर्ण

/**
 * omap2xxx_cm_split_idlest_reg - split CM_IDLEST reg addr पूर्णांकo its components
 * @idlest_reg: CM_IDLEST* भव address
 * @prcm_inst: poपूर्णांकer to an s16 to वापस the PRCM instance offset
 * @idlest_reg_id: poपूर्णांकer to a u8 to वापस the CM_IDLESTx रेजिस्टर ID
 *
 * XXX This function is only needed until असलolute रेजिस्टर addresses are
 * हटाओd from the OMAP काष्ठा clk records.
 */
अटल पूर्णांक omap2xxx_cm_split_idlest_reg(काष्ठा clk_omap_reg *idlest_reg,
					s16 *prcm_inst,
					u8 *idlest_reg_id)
अणु
	अचिन्हित दीर्घ offs;
	u8 idlest_offs;
	पूर्णांक i;

	idlest_offs = idlest_reg->offset & 0xff;
	क्रम (i = 0; i < ARRAY_SIZE(omap2xxx_cm_idlest_offs); i++) अणु
		अगर (idlest_offs == omap2xxx_cm_idlest_offs[i]) अणु
			*idlest_reg_id = i + 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(omap2xxx_cm_idlest_offs))
		वापस -EINVAL;

	offs = idlest_reg->offset;
	offs &= 0xff00;
	*prcm_inst = offs;

	वापस 0;
पूर्ण

/*
 *
 */

/**
 * omap2xxx_cm_रुको_module_पढ़ोy - रुको क्रम a module to leave idle or standby
 * @part: PRCM partition, ignored क्रम OMAP2
 * @prcm_mod: PRCM module offset
 * @idlest_id: CM_IDLESTx रेजिस्टर ID (i.e., x = 1, 2, 3)
 * @idlest_shअगरt: shअगरt of the bit in the CM_IDLEST* रेजिस्टर to check
 *
 * Wait क्रम the PRCM to indicate that the module identअगरied by
 * (@prcm_mod, @idlest_id, @idlest_shअगरt) is घड़ीed.  Return 0 upon
 * success or -EBUSY अगर the module करोesn't enable in समय.
 */
पूर्णांक omap2xxx_cm_रुको_module_पढ़ोy(u8 part, s16 prcm_mod, u16 idlest_id,
				  u8 idlest_shअगरt)
अणु
	पूर्णांक ena = 0, i = 0;
	u8 cm_idlest_reg;
	u32 mask;

	अगर (!idlest_id || (idlest_id > ARRAY_SIZE(omap2xxx_cm_idlest_offs)))
		वापस -EINVAL;

	cm_idlest_reg = omap2xxx_cm_idlest_offs[idlest_id - 1];

	mask = 1 << idlest_shअगरt;
	ena = mask;

	omap_test_समयout(((omap2_cm_पढ़ो_mod_reg(prcm_mod, cm_idlest_reg) &
			    mask) == ena), MAX_MODULE_READY_TIME, i);

	वापस (i < MAX_MODULE_READY_TIME) ? 0 : -EBUSY;
पूर्ण

/* Clockकरोमुख्य low-level functions */

अटल व्योम omap2xxx_clkdm_allow_idle(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	omap2xxx_cm_clkdm_enable_hwsup(clkdm->pwrdm.ptr->prcm_offs,
				       clkdm->clktrctrl_mask);
पूर्ण

अटल व्योम omap2xxx_clkdm_deny_idle(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	omap2xxx_cm_clkdm_disable_hwsup(clkdm->pwrdm.ptr->prcm_offs,
					clkdm->clktrctrl_mask);
पूर्ण

अटल पूर्णांक omap2xxx_clkdm_clk_enable(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	bool hwsup = false;

	अगर (!clkdm->clktrctrl_mask)
		वापस 0;

	hwsup = omap2xxx_cm_is_clkdm_in_hwsup(clkdm->pwrdm.ptr->prcm_offs,
					      clkdm->clktrctrl_mask);
	अगर (!hwsup && clkdm->flags & CLKDM_CAN_FORCE_WAKEUP)
		omap2xxx_clkdm_wakeup(clkdm);

	वापस 0;
पूर्ण

अटल पूर्णांक omap2xxx_clkdm_clk_disable(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	bool hwsup = false;

	अगर (!clkdm->clktrctrl_mask)
		वापस 0;

	hwsup = omap2xxx_cm_is_clkdm_in_hwsup(clkdm->pwrdm.ptr->prcm_offs,
					      clkdm->clktrctrl_mask);

	अगर (!hwsup && clkdm->flags & CLKDM_CAN_FORCE_SLEEP)
		omap2xxx_clkdm_sleep(clkdm);

	वापस 0;
पूर्ण

काष्ठा clkdm_ops omap2_clkdm_operations = अणु
	.clkdm_add_wkdep	= omap2_clkdm_add_wkdep,
	.clkdm_del_wkdep	= omap2_clkdm_del_wkdep,
	.clkdm_पढ़ो_wkdep	= omap2_clkdm_पढ़ो_wkdep,
	.clkdm_clear_all_wkdeps	= omap2_clkdm_clear_all_wkdeps,
	.clkdm_sleep		= omap2xxx_clkdm_sleep,
	.clkdm_wakeup		= omap2xxx_clkdm_wakeup,
	.clkdm_allow_idle	= omap2xxx_clkdm_allow_idle,
	.clkdm_deny_idle	= omap2xxx_clkdm_deny_idle,
	.clkdm_clk_enable	= omap2xxx_clkdm_clk_enable,
	.clkdm_clk_disable	= omap2xxx_clkdm_clk_disable,
पूर्ण;

पूर्णांक omap2xxx_cm_fclks_active(व्योम)
अणु
	u32 f1, f2;

	f1 = omap2_cm_पढ़ो_mod_reg(CORE_MOD, CM_FCLKEN1);
	f2 = omap2_cm_पढ़ो_mod_reg(CORE_MOD, OMAP24XX_CM_FCLKEN2);

	वापस (f1 | f2) ? 1 : 0;
पूर्ण

पूर्णांक omap2xxx_cm_mpu_retention_allowed(व्योम)
अणु
	u32 l;

	/* Check क्रम MMC, UART2, UART1, McSPI2, McSPI1 and DSS1. */
	l = omap2_cm_पढ़ो_mod_reg(CORE_MOD, CM_FCLKEN1);
	अगर (l & (OMAP2420_EN_MMC_MASK | OMAP24XX_EN_UART2_MASK |
		 OMAP24XX_EN_UART1_MASK | OMAP24XX_EN_MCSPI2_MASK |
		 OMAP24XX_EN_MCSPI1_MASK | OMAP24XX_EN_DSS1_MASK))
		वापस 0;
	/* Check क्रम UART3. */
	l = omap2_cm_पढ़ो_mod_reg(CORE_MOD, OMAP24XX_CM_FCLKEN2);
	अगर (l & OMAP24XX_EN_UART3_MASK)
		वापस 0;

	वापस 1;
पूर्ण

u32 omap2xxx_cm_get_core_clk_src(व्योम)
अणु
	u32 v;

	v = omap2_cm_पढ़ो_mod_reg(PLL_MOD, CM_CLKSEL2);
	v &= OMAP24XX_CORE_CLK_SRC_MASK;

	वापस v;
पूर्ण

u32 omap2xxx_cm_get_core_pll_config(व्योम)
अणु
	वापस omap2_cm_पढ़ो_mod_reg(PLL_MOD, CM_CLKSEL2);
पूर्ण

व्योम omap2xxx_cm_set_mod_भागiders(u32 mpu, u32 dsp, u32 gfx, u32 core, u32 mdm)
अणु
	u32 पंचांगp;

	omap2_cm_ग_लिखो_mod_reg(mpu, MPU_MOD, CM_CLKSEL);
	omap2_cm_ग_लिखो_mod_reg(dsp, OMAP24XX_DSP_MOD, CM_CLKSEL);
	omap2_cm_ग_लिखो_mod_reg(gfx, GFX_MOD, CM_CLKSEL);
	पंचांगp = omap2_cm_पढ़ो_mod_reg(CORE_MOD, CM_CLKSEL1) &
		OMAP24XX_CLKSEL_DSS2_MASK;
	omap2_cm_ग_लिखो_mod_reg(core | पंचांगp, CORE_MOD, CM_CLKSEL1);
	अगर (mdm)
		omap2_cm_ग_लिखो_mod_reg(mdm, OMAP2430_MDM_MOD, CM_CLKSEL);
पूर्ण

/*
 *
 */

अटल स्थिर काष्ठा cm_ll_data omap2xxx_cm_ll_data = अणु
	.split_idlest_reg	= &omap2xxx_cm_split_idlest_reg,
	.रुको_module_पढ़ोy	= &omap2xxx_cm_रुको_module_पढ़ोy,
पूर्ण;

पूर्णांक __init omap2xxx_cm_init(स्थिर काष्ठा omap_prcm_init_data *data)
अणु
	वापस cm_रेजिस्टर(&omap2xxx_cm_ll_data);
पूर्ण

अटल व्योम __निकास omap2xxx_cm_निकास(व्योम)
अणु
	cm_unरेजिस्टर(&omap2xxx_cm_ll_data);
पूर्ण
__निकासcall(omap2xxx_cm_निकास);
