<शैली गुरु>
/*
 * Default घड़ी type
 *
 * Copyright (C) 2005-2008, 2015 Texas Instruments, Inc.
 * Copyright (C) 2004-2010 Nokia Corporation
 *
 * Contacts:
 * Riअक्षरd Woodruff <r-woodruff2@ti.com>
 * Paul Walmsley
 * Tero Kristo <t-kristo@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk/ti.h>
#समावेश <linux/delay.h>

#समावेश "clock.h"

/*
 * MAX_MODULE_ENABLE_WAIT: maximum of number of microseconds to रुको
 * क्रम a module to indicate that it is no दीर्घer in idle
 */
#घोषणा MAX_MODULE_ENABLE_WAIT		100000

/*
 * CM module रेजिस्टर offsets, used क्रम calculating the companion
 * रेजिस्टर addresses.
 */
#घोषणा CM_FCLKEN			0x0000
#घोषणा CM_ICLKEN			0x0010

/**
 * _रुको_idlest_generic - रुको क्रम a module to leave the idle state
 * @clk: module घड़ी to रुको क्रम (needed क्रम रेजिस्टर offsets)
 * @reg: भव address of module IDLEST रेजिस्टर
 * @mask: value to mask against to determine अगर the module is active
 * @idlest: idle state indicator (0 or 1) क्रम the घड़ी
 * @name: name of the घड़ी (क्रम prपूर्णांकk)
 *
 * Wait क्रम a module to leave idle, where its idle-status रेजिस्टर is
 * not inside the CM module.  Returns 1 अगर the module left idle
 * promptly, or 0 अगर the module did not leave idle beक्रमe the समयout
 * elapsed.  XXX Deprecated - should be moved पूर्णांकo drivers क्रम the
 * inभागidual IP block that the IDLEST रेजिस्टर exists in.
 */
अटल पूर्णांक _रुको_idlest_generic(काष्ठा clk_hw_omap *clk,
				काष्ठा clk_omap_reg *reg,
				u32 mask, u8 idlest, स्थिर अक्षर *name)
अणु
	पूर्णांक i = 0, ena = 0;

	ena = (idlest) ? 0 : mask;

	/* Wait until module enters enabled state */
	क्रम (i = 0; i < MAX_MODULE_ENABLE_WAIT; i++) अणु
		अगर ((ti_clk_ll_ops->clk_पढ़ोl(reg) & mask) == ena)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i < MAX_MODULE_ENABLE_WAIT)
		pr_debug("omap clock: module associated with clock %s ready after %d loops\n",
			 name, i);
	अन्यथा
		pr_err("omap clock: module associated with clock %s didn't enable in %d tries\n",
		       name, MAX_MODULE_ENABLE_WAIT);

	वापस (i < MAX_MODULE_ENABLE_WAIT) ? 1 : 0;
पूर्ण

/**
 * _omap2_module_रुको_पढ़ोy - रुको क्रम an OMAP module to leave IDLE
 * @clk: काष्ठा clk * beदीर्घing to the module
 *
 * If the necessary घड़ीs क्रम the OMAP hardware IP block that
 * corresponds to घड़ी @clk are enabled, then रुको क्रम the module to
 * indicate पढ़ोiness (i.e., to leave IDLE).  This code करोes not
 * beदीर्घ in the घड़ी code and will be moved in the medium term to
 * module-dependent code.  No वापस value.
 */
अटल व्योम _omap2_module_रुको_पढ़ोy(काष्ठा clk_hw_omap *clk)
अणु
	काष्ठा clk_omap_reg companion_reg, idlest_reg;
	u8 other_bit, idlest_bit, idlest_val, idlest_reg_id;
	s16 prcm_mod;
	पूर्णांक r;

	/* Not all modules have multiple घड़ीs that their IDLEST depends on */
	अगर (clk->ops->find_companion) अणु
		clk->ops->find_companion(clk, &companion_reg, &other_bit);
		अगर (!(ti_clk_ll_ops->clk_पढ़ोl(&companion_reg) &
		      (1 << other_bit)))
			वापस;
	पूर्ण

	clk->ops->find_idlest(clk, &idlest_reg, &idlest_bit, &idlest_val);
	r = ti_clk_ll_ops->cm_split_idlest_reg(&idlest_reg, &prcm_mod,
					       &idlest_reg_id);
	अगर (r) अणु
		/* IDLEST रेजिस्टर not in the CM module */
		_रुको_idlest_generic(clk, &idlest_reg, (1 << idlest_bit),
				     idlest_val, clk_hw_get_name(&clk->hw));
	पूर्ण अन्यथा अणु
		ti_clk_ll_ops->cm_रुको_module_पढ़ोy(0, prcm_mod, idlest_reg_id,
						    idlest_bit);
	पूर्ण
पूर्ण

/**
 * omap2_clk_dflt_find_companion - find companion घड़ी to @clk
 * @clk: काष्ठा clk * to find the companion घड़ी of
 * @other_reg: व्योम __iomem ** to वापस the companion घड़ी CM_*CLKEN va in
 * @other_bit: u8 ** to वापस the companion घड़ी bit shअगरt in
 *
 * Note: We करोn't need special code here क्रम INVERT_ENABLE क्रम the
 * समय being since INVERT_ENABLE only applies to घड़ीs enabled by
 * CM_CLKEN_PLL
 *
 * Convert CM_ICLKEN* <-> CM_FCLKEN*.  This conversion assumes it's
 * just a matter of XORing the bits.
 *
 * Some घड़ीs करोn't have companion घड़ीs.  For example, modules with
 * only an पूर्णांकerface घड़ी (such as MAILBOXES) करोn't have a companion
 * घड़ी.  Right now, this code relies on the hardware exporting a bit
 * in the correct companion रेजिस्टर that indicates that the
 * nonexistent 'companion clock' is active.  Future patches will
 * associate this type of code with per-module data काष्ठाures to
 * aव्योम this issue, and हटाओ the casts.  No वापस value.
 */
व्योम omap2_clk_dflt_find_companion(काष्ठा clk_hw_omap *clk,
				   काष्ठा clk_omap_reg *other_reg,
				   u8 *other_bit)
अणु
	स_नकल(other_reg, &clk->enable_reg, माप(*other_reg));

	/*
	 * Convert CM_ICLKEN* <-> CM_FCLKEN*.  This conversion assumes
	 * it's just a matter of XORing the bits.
	 */
	other_reg->offset ^= (CM_FCLKEN ^ CM_ICLKEN);

	*other_bit = clk->enable_bit;
पूर्ण

/**
 * omap2_clk_dflt_find_idlest - find CM_IDLEST reg va, bit shअगरt क्रम @clk
 * @clk: काष्ठा clk * to find IDLEST info क्रम
 * @idlest_reg: व्योम __iomem ** to वापस the CM_IDLEST va in
 * @idlest_bit: u8 * to वापस the CM_IDLEST bit shअगरt in
 * @idlest_val: u8 * to वापस the idle status indicator
 *
 * Return the CM_IDLEST रेजिस्टर address and bit shअगरt corresponding
 * to the module that "owns" this घड़ी.  This शेष code assumes
 * that the CM_IDLEST bit shअगरt is the CM_*CLKEN bit shअगरt, and that
 * the IDLEST रेजिस्टर address ID corresponds to the CM_*CLKEN
 * रेजिस्टर address ID (e.g., that CM_FCLKEN2 corresponds to
 * CM_IDLEST2).  This is not true क्रम all modules.  No वापस value.
 */
व्योम omap2_clk_dflt_find_idlest(काष्ठा clk_hw_omap *clk,
				काष्ठा clk_omap_reg *idlest_reg, u8 *idlest_bit,
				u8 *idlest_val)
अणु
	स_नकल(idlest_reg, &clk->enable_reg, माप(*idlest_reg));

	idlest_reg->offset &= ~0xf0;
	idlest_reg->offset |= 0x20;

	*idlest_bit = clk->enable_bit;

	/*
	 * 24xx uses 0 to indicate not पढ़ोy, and 1 to indicate पढ़ोy.
	 * 34xx reverses this, just to keep us on our toes
	 * AM35xx uses both, depending on the module.
	 */
	*idlest_val = ti_clk_get_features()->cm_idlest_val;
पूर्ण

/**
 * omap2_dflt_clk_enable - enable a घड़ी in the hardware
 * @hw: काष्ठा clk_hw * of the घड़ी to enable
 *
 * Enable the घड़ी @hw in the hardware.  We first call पूर्णांकo the OMAP
 * घड़ीकरोमुख्य code to "enable" the corresponding घड़ीकरोमुख्य अगर this
 * is the first enabled user of the घड़ीकरोमुख्य.  Then program the
 * hardware to enable the घड़ी.  Then रुको क्रम the IP block that uses
 * this घड़ी to leave idle (अगर applicable).  Returns the error value
 * from clkdm_clk_enable() अगर it terminated with an error, or -EINVAL
 * अगर @hw has a null घड़ी enable_reg, or zero upon success.
 */
पूर्णांक omap2_dflt_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk;
	u32 v;
	पूर्णांक ret = 0;
	bool clkdm_control;

	अगर (ti_clk_get_features()->flags & TI_CLK_DISABLE_CLKDM_CONTROL)
		clkdm_control = false;
	अन्यथा
		clkdm_control = true;

	clk = to_clk_hw_omap(hw);

	अगर (clkdm_control && clk->clkdm) अणु
		ret = ti_clk_ll_ops->clkdm_clk_enable(clk->clkdm, hw->clk);
		अगर (ret) अणु
			WARN(1,
			     "%s: could not enable %s's clockdomain %s: %d\n",
			     __func__, clk_hw_get_name(hw),
			     clk->clkdm_name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* FIXME should not have INVERT_ENABLE bit here */
	v = ti_clk_ll_ops->clk_पढ़ोl(&clk->enable_reg);
	अगर (clk->flags & INVERT_ENABLE)
		v &= ~(1 << clk->enable_bit);
	अन्यथा
		v |= (1 << clk->enable_bit);
	ti_clk_ll_ops->clk_ग_लिखोl(v, &clk->enable_reg);
	v = ti_clk_ll_ops->clk_पढ़ोl(&clk->enable_reg); /* OCP barrier */

	अगर (clk->ops && clk->ops->find_idlest)
		_omap2_module_रुको_पढ़ोy(clk);

	वापस 0;
पूर्ण

/**
 * omap2_dflt_clk_disable - disable a घड़ी in the hardware
 * @hw: काष्ठा clk_hw * of the घड़ी to disable
 *
 * Disable the घड़ी @hw in the hardware, and call पूर्णांकo the OMAP
 * घड़ीकरोमुख्य code to "disable" the corresponding घड़ीकरोमुख्य अगर all
 * घड़ीs/hwmods in that घड़ीकरोमुख्य are now disabled.  No वापस
 * value.
 */
व्योम omap2_dflt_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk;
	u32 v;

	clk = to_clk_hw_omap(hw);

	v = ti_clk_ll_ops->clk_पढ़ोl(&clk->enable_reg);
	अगर (clk->flags & INVERT_ENABLE)
		v |= (1 << clk->enable_bit);
	अन्यथा
		v &= ~(1 << clk->enable_bit);
	ti_clk_ll_ops->clk_ग_लिखोl(v, &clk->enable_reg);
	/* No OCP barrier needed here since it is a disable operation */

	अगर (!(ti_clk_get_features()->flags & TI_CLK_DISABLE_CLKDM_CONTROL) &&
	    clk->clkdm)
		ti_clk_ll_ops->clkdm_clk_disable(clk->clkdm, hw->clk);
पूर्ण

/**
 * omap2_dflt_clk_is_enabled - is घड़ी enabled in the hardware?
 * @hw: काष्ठा clk_hw * to check
 *
 * Return 1 अगर the घड़ी represented by @hw is enabled in the
 * hardware, or 0 otherwise.  Intended क्रम use in the काष्ठा
 * clk_ops.is_enabled function poपूर्णांकer.
 */
पूर्णांक omap2_dflt_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	u32 v;

	v = ti_clk_ll_ops->clk_पढ़ोl(&clk->enable_reg);

	अगर (clk->flags & INVERT_ENABLE)
		v ^= BIT(clk->enable_bit);

	v &= BIT(clk->enable_bit);

	वापस v ? 1 : 0;
पूर्ण

स्थिर काष्ठा clk_hw_omap_ops clkhwops_रुको = अणु
	.find_idlest	= omap2_clk_dflt_find_idlest,
	.find_companion	= omap2_clk_dflt_find_companion,
पूर्ण;
