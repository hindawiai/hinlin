<शैली गुरु>
/*
 * AM33XX CM functions
 *
 * Copyright (C) 2011-2012 Texas Instruments Incorporated - https://www.ti.com/
 * Vaibhav Hiremath <hvaibhav@ti.com>
 *
 * Reference taken from from OMAP4 cminst44xx.c
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>

#समावेश "clockdomain.h"
#समावेश "cm.h"
#समावेश "cm33xx.h"
#समावेश "cm-regbits-34xx.h"
#समावेश "cm-regbits-33xx.h"
#समावेश "prm33xx.h"

/*
 * CLKCTRL_IDLEST_*: possible values क्रम the CM_*_CLKCTRL.IDLEST bitfield:
 *
 *   0x0 func:     Module is fully functional, including OCP
 *   0x1 trans:    Module is perक्रमming transition: wakeup, or sleep, or sleep
 *                 पातion
 *   0x2 idle:     Module is in Idle mode (only OCP part). It is functional अगर
 *                 using separate functional घड़ी
 *   0x3 disabled: Module is disabled and cannot be accessed
 *
 */
#घोषणा CLKCTRL_IDLEST_FUNCTIONAL		0x0
#घोषणा CLKCTRL_IDLEST_INTRANSITION		0x1
#घोषणा CLKCTRL_IDLEST_INTERFACE_IDLE		0x2
#घोषणा CLKCTRL_IDLEST_DISABLED			0x3

/* Private functions */

/* Read a रेजिस्टर in a CM instance */
अटल अंतरभूत u32 am33xx_cm_पढ़ो_reg(u16 inst, u16 idx)
अणु
	वापस पढ़ोl_relaxed(cm_base.va + inst + idx);
पूर्ण

/* Write पूर्णांकo a रेजिस्टर in a CM */
अटल अंतरभूत व्योम am33xx_cm_ग_लिखो_reg(u32 val, u16 inst, u16 idx)
अणु
	ग_लिखोl_relaxed(val, cm_base.va + inst + idx);
पूर्ण

/* Read-modअगरy-ग_लिखो a रेजिस्टर in CM */
अटल अंतरभूत u32 am33xx_cm_rmw_reg_bits(u32 mask, u32 bits, s16 inst, s16 idx)
अणु
	u32 v;

	v = am33xx_cm_पढ़ो_reg(inst, idx);
	v &= ~mask;
	v |= bits;
	am33xx_cm_ग_लिखो_reg(v, inst, idx);

	वापस v;
पूर्ण

अटल अंतरभूत u32 am33xx_cm_पढ़ो_reg_bits(u16 inst, s16 idx, u32 mask)
अणु
	u32 v;

	v = am33xx_cm_पढ़ो_reg(inst, idx);
	v &= mask;
	v >>= __ffs(mask);

	वापस v;
पूर्ण

/**
 * _clkctrl_idlest - पढ़ो a CM_*_CLKCTRL रेजिस्टर; mask & shअगरt IDLEST bitfield
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @clkctrl_offs: Module घड़ी control रेजिस्टर offset (*_CLKCTRL macro)
 *
 * Return the IDLEST bitfield of a CM_*_CLKCTRL रेजिस्टर, shअगरted करोwn to
 * bit 0.
 */
अटल u32 _clkctrl_idlest(u16 inst, u16 clkctrl_offs)
अणु
	u32 v = am33xx_cm_पढ़ो_reg(inst, clkctrl_offs);
	v &= AM33XX_IDLEST_MASK;
	v >>= AM33XX_IDLEST_SHIFT;
	वापस v;
पूर्ण

/**
 * _is_module_पढ़ोy - can module रेजिस्टरs be accessed without causing an पात?
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @clkctrl_offs: Module घड़ी control रेजिस्टर offset (*_CLKCTRL macro)
 *
 * Returns true अगर the module's CM_*_CLKCTRL.IDLEST bitfield is either
 * *FUNCTIONAL or *INTERFACE_IDLE; false otherwise.
 */
अटल bool _is_module_पढ़ोy(u16 inst, u16 clkctrl_offs)
अणु
	u32 v;

	v = _clkctrl_idlest(inst, clkctrl_offs);

	वापस (v == CLKCTRL_IDLEST_FUNCTIONAL ||
		v == CLKCTRL_IDLEST_INTERFACE_IDLE) ? true : false;
पूर्ण

/**
 * _clktrctrl_ग_लिखो - ग_लिखो @c to a CM_CLKSTCTRL.CLKTRCTRL रेजिस्टर bitfield
 * @c: CLKTRCTRL रेजिस्टर bitfield (LSB = bit 0, i.e., unshअगरted)
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @cकरोffs: Clockकरोमुख्य रेजिस्टर offset (*_CDOFFS macro)
 *
 * @c must be the unshअगरted value क्रम CLKTRCTRL - i.e., this function
 * will handle the shअगरt itself.
 */
अटल व्योम _clktrctrl_ग_लिखो(u8 c, u16 inst, u16 cकरोffs)
अणु
	u32 v;

	v = am33xx_cm_पढ़ो_reg(inst, cकरोffs);
	v &= ~AM33XX_CLKTRCTRL_MASK;
	v |= c << AM33XX_CLKTRCTRL_SHIFT;
	am33xx_cm_ग_लिखो_reg(v, inst, cकरोffs);
पूर्ण

/* Public functions */

/**
 * am33xx_cm_is_clkdm_in_hwsup - is a घड़ीकरोमुख्य in hwsup idle mode?
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @cकरोffs: Clockकरोमुख्य रेजिस्टर offset (*_CDOFFS macro)
 *
 * Returns true अगर the घड़ीकरोमुख्य referred to by (@inst, @cकरोffs)
 * is in hardware-supervised idle mode, or 0 otherwise.
 */
अटल bool am33xx_cm_is_clkdm_in_hwsup(u16 inst, u16 cकरोffs)
अणु
	u32 v;

	v = am33xx_cm_पढ़ो_reg(inst, cकरोffs);
	v &= AM33XX_CLKTRCTRL_MASK;
	v >>= AM33XX_CLKTRCTRL_SHIFT;

	वापस (v == OMAP34XX_CLKSTCTRL_ENABLE_AUTO) ? true : false;
पूर्ण

/**
 * am33xx_cm_clkdm_enable_hwsup - put a घड़ीकरोमुख्य in hwsup-idle mode
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @cकरोffs: Clockकरोमुख्य रेजिस्टर offset (*_CDOFFS macro)
 *
 * Put a घड़ीकरोमुख्य referred to by (@inst, @cकरोffs) पूर्णांकo
 * hardware-supervised idle mode.  No वापस value.
 */
अटल व्योम am33xx_cm_clkdm_enable_hwsup(u16 inst, u16 cकरोffs)
अणु
	_clktrctrl_ग_लिखो(OMAP34XX_CLKSTCTRL_ENABLE_AUTO, inst, cकरोffs);
पूर्ण

/**
 * am33xx_cm_clkdm_disable_hwsup - put a घड़ीकरोमुख्य in swsup-idle mode
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @cकरोffs: Clockकरोमुख्य रेजिस्टर offset (*_CDOFFS macro)
 *
 * Put a घड़ीकरोमुख्य referred to by (@inst, @cकरोffs) पूर्णांकo
 * software-supervised idle mode, i.e., controlled manually by the
 * Linux OMAP घड़ीकरोमुख्य code.  No वापस value.
 */
अटल व्योम am33xx_cm_clkdm_disable_hwsup(u16 inst, u16 cकरोffs)
अणु
	_clktrctrl_ग_लिखो(OMAP34XX_CLKSTCTRL_DISABLE_AUTO, inst, cकरोffs);
पूर्ण

/**
 * am33xx_cm_clkdm_क्रमce_sleep - try to put a घड़ीकरोमुख्य पूर्णांकo idle
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @cकरोffs: Clockकरोमुख्य रेजिस्टर offset (*_CDOFFS macro)
 *
 * Put a घड़ीकरोमुख्य referred to by (@inst, @cकरोffs) पूर्णांकo idle
 * No वापस value.
 */
अटल व्योम am33xx_cm_clkdm_क्रमce_sleep(u16 inst, u16 cकरोffs)
अणु
	_clktrctrl_ग_लिखो(OMAP34XX_CLKSTCTRL_FORCE_SLEEP, inst, cकरोffs);
पूर्ण

/**
 * am33xx_cm_clkdm_क्रमce_wakeup - try to take a घड़ीकरोमुख्य out of idle
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @cकरोffs: Clockकरोमुख्य रेजिस्टर offset (*_CDOFFS macro)
 *
 * Take a घड़ीकरोमुख्य referred to by (@inst, @cकरोffs) out of idle,
 * waking it up.  No वापस value.
 */
अटल व्योम am33xx_cm_clkdm_क्रमce_wakeup(u16 inst, u16 cकरोffs)
अणु
	_clktrctrl_ग_लिखो(OMAP34XX_CLKSTCTRL_FORCE_WAKEUP, inst, cकरोffs);
पूर्ण

/*
 *
 */

/**
 * am33xx_cm_रुको_module_पढ़ोy - रुको क्रम a module to be in 'func' state
 * @part: PRCM partition, ignored क्रम AM33xx
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @clkctrl_offs: Module घड़ी control रेजिस्टर offset (*_CLKCTRL macro)
 * @bit_shअगरt: bit shअगरt क्रम the रेजिस्टर, ignored क्रम AM33xx
 *
 * Wait क्रम the module IDLEST to be functional. If the idle state is in any
 * the non functional state (trans, idle or disabled), module and thus the
 * sysconfig cannot be accessed and will probably lead to an "imprecise
 * बाह्यal पात"
 */
अटल पूर्णांक am33xx_cm_रुको_module_पढ़ोy(u8 part, s16 inst, u16 clkctrl_offs,
				       u8 bit_shअगरt)
अणु
	पूर्णांक i = 0;

	omap_test_समयout(_is_module_पढ़ोy(inst, clkctrl_offs),
			  MAX_MODULE_READY_TIME, i);

	वापस (i < MAX_MODULE_READY_TIME) ? 0 : -EBUSY;
पूर्ण

/**
 * am33xx_cm_रुको_module_idle - रुको क्रम a module to be in 'disabled'
 * state
 * @part: CM partition, ignored क्रम AM33xx
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @clkctrl_offs: Module घड़ी control रेजिस्टर offset (*_CLKCTRL macro)
 * @bit_shअगरt: bit shअगरt क्रम the रेजिस्टर, ignored क्रम AM33xx
 *
 * Wait क्रम the module IDLEST to be disabled. Some PRCM transition,
 * like reset निश्चितion or parent घड़ी de-activation must रुको the
 * module to be fully disabled.
 */
अटल पूर्णांक am33xx_cm_रुको_module_idle(u8 part, s16 inst, u16 clkctrl_offs,
				      u8 bit_shअगरt)
अणु
	पूर्णांक i = 0;

	omap_test_समयout((_clkctrl_idlest(inst, clkctrl_offs) ==
				CLKCTRL_IDLEST_DISABLED),
				MAX_MODULE_READY_TIME, i);

	वापस (i < MAX_MODULE_READY_TIME) ? 0 : -EBUSY;
पूर्ण

/**
 * am33xx_cm_module_enable - Enable the modulemode inside CLKCTRL
 * @mode: Module mode (SW or HW)
 * @part: CM partition, ignored क्रम AM33xx
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @clkctrl_offs: Module घड़ी control रेजिस्टर offset (*_CLKCTRL macro)
 *
 * No वापस value.
 */
अटल व्योम am33xx_cm_module_enable(u8 mode, u8 part, u16 inst,
				    u16 clkctrl_offs)
अणु
	u32 v;

	v = am33xx_cm_पढ़ो_reg(inst, clkctrl_offs);
	v &= ~AM33XX_MODULEMODE_MASK;
	v |= mode << AM33XX_MODULEMODE_SHIFT;
	am33xx_cm_ग_लिखो_reg(v, inst, clkctrl_offs);
पूर्ण

/**
 * am33xx_cm_module_disable - Disable the module inside CLKCTRL
 * @part: CM partition, ignored क्रम AM33xx
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @clkctrl_offs: Module घड़ी control रेजिस्टर offset (*_CLKCTRL macro)
 *
 * No वापस value.
 */
अटल व्योम am33xx_cm_module_disable(u8 part, u16 inst, u16 clkctrl_offs)
अणु
	u32 v;

	v = am33xx_cm_पढ़ो_reg(inst, clkctrl_offs);
	v &= ~AM33XX_MODULEMODE_MASK;
	am33xx_cm_ग_लिखो_reg(v, inst, clkctrl_offs);
पूर्ण

/*
 * Clockकरोमुख्य low-level functions
 */

अटल पूर्णांक am33xx_clkdm_sleep(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	am33xx_cm_clkdm_क्रमce_sleep(clkdm->cm_inst, clkdm->clkdm_offs);
	वापस 0;
पूर्ण

अटल पूर्णांक am33xx_clkdm_wakeup(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	am33xx_cm_clkdm_क्रमce_wakeup(clkdm->cm_inst, clkdm->clkdm_offs);
	वापस 0;
पूर्ण

अटल व्योम am33xx_clkdm_allow_idle(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	am33xx_cm_clkdm_enable_hwsup(clkdm->cm_inst, clkdm->clkdm_offs);
पूर्ण

अटल व्योम am33xx_clkdm_deny_idle(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	am33xx_cm_clkdm_disable_hwsup(clkdm->cm_inst, clkdm->clkdm_offs);
पूर्ण

अटल पूर्णांक am33xx_clkdm_clk_enable(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	अगर (clkdm->flags & CLKDM_CAN_FORCE_WAKEUP)
		वापस am33xx_clkdm_wakeup(clkdm);

	वापस 0;
पूर्ण

अटल पूर्णांक am33xx_clkdm_clk_disable(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	bool hwsup = false;

	hwsup = am33xx_cm_is_clkdm_in_hwsup(clkdm->cm_inst, clkdm->clkdm_offs);

	अगर (!hwsup && (clkdm->flags & CLKDM_CAN_FORCE_SLEEP))
		am33xx_clkdm_sleep(clkdm);

	वापस 0;
पूर्ण

अटल u32 am33xx_cm_xlate_clkctrl(u8 part, u16 inst, u16 offset)
अणु
	वापस cm_base.pa + inst + offset;
पूर्ण

/**
 * am33xx_clkdm_save_context - Save the घड़ीकरोमुख्य transition context
 * @clkdm: The घड़ीकरोमुख्य poपूर्णांकer whose context needs to be saved
 *
 * Save the घड़ीकरोमुख्य transition context.
 */
अटल पूर्णांक am33xx_clkdm_save_context(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	clkdm->context = am33xx_cm_पढ़ो_reg_bits(clkdm->cm_inst,
						 clkdm->clkdm_offs,
						 AM33XX_CLKTRCTRL_MASK);

	वापस 0;
पूर्ण

/**
 * am33xx_restore_save_context - Restore the घड़ीकरोमुख्य transition context
 * @clkdm: The घड़ीकरोमुख्य poपूर्णांकer whose context needs to be restored
 *
 * Restore the घड़ीकरोमुख्य transition context.
 */
अटल पूर्णांक am33xx_clkdm_restore_context(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	चयन (clkdm->context) अणु
	हाल OMAP34XX_CLKSTCTRL_DISABLE_AUTO:
		am33xx_clkdm_deny_idle(clkdm);
		अवरोध;
	हाल OMAP34XX_CLKSTCTRL_FORCE_SLEEP:
		am33xx_clkdm_sleep(clkdm);
		अवरोध;
	हाल OMAP34XX_CLKSTCTRL_FORCE_WAKEUP:
		am33xx_clkdm_wakeup(clkdm);
		अवरोध;
	हाल OMAP34XX_CLKSTCTRL_ENABLE_AUTO:
		am33xx_clkdm_allow_idle(clkdm);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा clkdm_ops am33xx_clkdm_operations = अणु
	.clkdm_sleep		= am33xx_clkdm_sleep,
	.clkdm_wakeup		= am33xx_clkdm_wakeup,
	.clkdm_allow_idle	= am33xx_clkdm_allow_idle,
	.clkdm_deny_idle	= am33xx_clkdm_deny_idle,
	.clkdm_clk_enable	= am33xx_clkdm_clk_enable,
	.clkdm_clk_disable	= am33xx_clkdm_clk_disable,
	.clkdm_save_context	= am33xx_clkdm_save_context,
	.clkdm_restore_context	= am33xx_clkdm_restore_context,
पूर्ण;

अटल स्थिर काष्ठा cm_ll_data am33xx_cm_ll_data = अणु
	.रुको_module_पढ़ोy	= &am33xx_cm_रुको_module_पढ़ोy,
	.रुको_module_idle	= &am33xx_cm_रुको_module_idle,
	.module_enable		= &am33xx_cm_module_enable,
	.module_disable		= &am33xx_cm_module_disable,
	.xlate_clkctrl		= &am33xx_cm_xlate_clkctrl,
पूर्ण;

पूर्णांक __init am33xx_cm_init(स्थिर काष्ठा omap_prcm_init_data *data)
अणु
	वापस cm_रेजिस्टर(&am33xx_cm_ll_data);
पूर्ण

अटल व्योम __निकास am33xx_cm_निकास(व्योम)
अणु
	cm_unरेजिस्टर(&am33xx_cm_ll_data);
पूर्ण
__निकासcall(am33xx_cm_निकास);
