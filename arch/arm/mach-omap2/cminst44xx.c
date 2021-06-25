<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP4 CM instance functions
 *
 * Copyright (C) 2009 Nokia Corporation
 * Copyright (C) 2008-2011 Texas Instruments, Inc.
 * Paul Walmsley
 * Rajendra Nayak <rnayak@ti.com>
 *
 * This is needed since CM instances can be in the PRM, PRCM_MPU, CM1,
 * or CM2 hardware modules.  For example, the EMU_CM CM instance is in
 * the PRM hardware module.  What a mess...
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>

#समावेश "clockdomain.h"
#समावेश "cm.h"
#समावेश "cm1_44xx.h"
#समावेश "cm2_44xx.h"
#समावेश "cm44xx.h"
#समावेश "cm-regbits-34xx.h"
#समावेश "prcm44xx.h"
#समावेश "prm44xx.h"
#समावेश "prcm_mpu44xx.h"
#समावेश "prcm-common.h"

#घोषणा OMAP4430_IDLEST_SHIFT		16
#घोषणा OMAP4430_IDLEST_MASK		(0x3 << 16)
#घोषणा OMAP4430_CLKTRCTRL_SHIFT	0
#घोषणा OMAP4430_CLKTRCTRL_MASK		(0x3 << 0)
#घोषणा OMAP4430_MODULEMODE_SHIFT	0
#घोषणा OMAP4430_MODULEMODE_MASK	(0x3 << 0)

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

अटल काष्ठा omap_करोमुख्य_base _cm_bases[OMAP4_MAX_PRCM_PARTITIONS];

/**
 * omap_cm_base_init - Populates the cm partitions
 *
 * Populates the base addresses of the _cm_bases
 * array used क्रम पढ़ो/ग_लिखो of cm module रेजिस्टरs.
 */
अटल व्योम omap_cm_base_init(व्योम)
अणु
	स_नकल(&_cm_bases[OMAP4430_PRM_PARTITION], &prm_base, माप(prm_base));
	स_नकल(&_cm_bases[OMAP4430_CM1_PARTITION], &cm_base, माप(cm_base));
	स_नकल(&_cm_bases[OMAP4430_CM2_PARTITION], &cm2_base, माप(cm2_base));
	स_नकल(&_cm_bases[OMAP4430_PRCM_MPU_PARTITION], &prcm_mpu_base,
	       माप(prcm_mpu_base));
पूर्ण

/* Private functions */

अटल u32 omap4_cminst_पढ़ो_inst_reg(u8 part, u16 inst, u16 idx);

/**
 * _clkctrl_idlest - पढ़ो a CM_*_CLKCTRL रेजिस्टर; mask & shअगरt IDLEST bitfield
 * @part: PRCM partition ID that the CM_CLKCTRL रेजिस्टर exists in
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @clkctrl_offs: Module घड़ी control रेजिस्टर offset (*_CLKCTRL macro)
 *
 * Return the IDLEST bitfield of a CM_*_CLKCTRL रेजिस्टर, shअगरted करोwn to
 * bit 0.
 */
अटल u32 _clkctrl_idlest(u8 part, u16 inst, u16 clkctrl_offs)
अणु
	u32 v = omap4_cminst_पढ़ो_inst_reg(part, inst, clkctrl_offs);
	v &= OMAP4430_IDLEST_MASK;
	v >>= OMAP4430_IDLEST_SHIFT;
	वापस v;
पूर्ण

/**
 * _is_module_पढ़ोy - can module रेजिस्टरs be accessed without causing an पात?
 * @part: PRCM partition ID that the CM_CLKCTRL रेजिस्टर exists in
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @clkctrl_offs: Module घड़ी control रेजिस्टर offset (*_CLKCTRL macro)
 *
 * Returns true अगर the module's CM_*_CLKCTRL.IDLEST bitfield is either
 * *FUNCTIONAL or *INTERFACE_IDLE; false otherwise.
 */
अटल bool _is_module_पढ़ोy(u8 part, u16 inst, u16 clkctrl_offs)
अणु
	u32 v;

	v = _clkctrl_idlest(part, inst, clkctrl_offs);

	वापस (v == CLKCTRL_IDLEST_FUNCTIONAL ||
		v == CLKCTRL_IDLEST_INTERFACE_IDLE) ? true : false;
पूर्ण

/* Read a रेजिस्टर in a CM instance */
अटल u32 omap4_cminst_पढ़ो_inst_reg(u8 part, u16 inst, u16 idx)
अणु
	BUG_ON(part >= OMAP4_MAX_PRCM_PARTITIONS ||
	       part == OMAP4430_INVALID_PRCM_PARTITION ||
	       !_cm_bases[part].va);
	वापस पढ़ोl_relaxed(_cm_bases[part].va + inst + idx);
पूर्ण

/* Write पूर्णांकo a रेजिस्टर in a CM instance */
अटल व्योम omap4_cminst_ग_लिखो_inst_reg(u32 val, u8 part, u16 inst, u16 idx)
अणु
	BUG_ON(part >= OMAP4_MAX_PRCM_PARTITIONS ||
	       part == OMAP4430_INVALID_PRCM_PARTITION ||
	       !_cm_bases[part].va);
	ग_लिखोl_relaxed(val, _cm_bases[part].va + inst + idx);
पूर्ण

/* Read-modअगरy-ग_लिखो a रेजिस्टर in CM1. Caller must lock */
अटल u32 omap4_cminst_rmw_inst_reg_bits(u32 mask, u32 bits, u8 part, u16 inst,
					  s16 idx)
अणु
	u32 v;

	v = omap4_cminst_पढ़ो_inst_reg(part, inst, idx);
	v &= ~mask;
	v |= bits;
	omap4_cminst_ग_लिखो_inst_reg(v, part, inst, idx);

	वापस v;
पूर्ण

अटल u32 omap4_cminst_set_inst_reg_bits(u32 bits, u8 part, u16 inst, s16 idx)
अणु
	वापस omap4_cminst_rmw_inst_reg_bits(bits, bits, part, inst, idx);
पूर्ण

अटल u32 omap4_cminst_clear_inst_reg_bits(u32 bits, u8 part, u16 inst,
					    s16 idx)
अणु
	वापस omap4_cminst_rmw_inst_reg_bits(bits, 0x0, part, inst, idx);
पूर्ण

अटल u32 omap4_cminst_पढ़ो_inst_reg_bits(u8 part, u16 inst, s16 idx, u32 mask)
अणु
	u32 v;

	v = omap4_cminst_पढ़ो_inst_reg(part, inst, idx);
	v &= mask;
	v >>= __ffs(mask);

	वापस v;
पूर्ण

/*
 *
 */

/**
 * _clktrctrl_ग_लिखो - ग_लिखो @c to a CM_CLKSTCTRL.CLKTRCTRL रेजिस्टर bitfield
 * @c: CLKTRCTRL रेजिस्टर bitfield (LSB = bit 0, i.e., unshअगरted)
 * @part: PRCM partition ID that the CM_CLKSTCTRL रेजिस्टर exists in
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @cकरोffs: Clockकरोमुख्य रेजिस्टर offset (*_CDOFFS macro)
 *
 * @c must be the unshअगरted value क्रम CLKTRCTRL - i.e., this function
 * will handle the shअगरt itself.
 */
अटल व्योम _clktrctrl_ग_लिखो(u8 c, u8 part, u16 inst, u16 cकरोffs)
अणु
	u32 v;

	v = omap4_cminst_पढ़ो_inst_reg(part, inst, cकरोffs + OMAP4_CM_CLKSTCTRL);
	v &= ~OMAP4430_CLKTRCTRL_MASK;
	v |= c << OMAP4430_CLKTRCTRL_SHIFT;
	omap4_cminst_ग_लिखो_inst_reg(v, part, inst, cकरोffs + OMAP4_CM_CLKSTCTRL);
पूर्ण

/**
 * omap4_cminst_is_clkdm_in_hwsup - is a घड़ीकरोमुख्य in hwsup idle mode?
 * @part: PRCM partition ID that the CM_CLKSTCTRL रेजिस्टर exists in
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @cकरोffs: Clockकरोमुख्य रेजिस्टर offset (*_CDOFFS macro)
 *
 * Returns true अगर the घड़ीकरोमुख्य referred to by (@part, @inst, @cकरोffs)
 * is in hardware-supervised idle mode, or 0 otherwise.
 */
अटल bool omap4_cminst_is_clkdm_in_hwsup(u8 part, u16 inst, u16 cकरोffs)
अणु
	u32 v;

	v = omap4_cminst_पढ़ो_inst_reg(part, inst, cकरोffs + OMAP4_CM_CLKSTCTRL);
	v &= OMAP4430_CLKTRCTRL_MASK;
	v >>= OMAP4430_CLKTRCTRL_SHIFT;

	वापस (v == OMAP34XX_CLKSTCTRL_ENABLE_AUTO) ? true : false;
पूर्ण

/**
 * omap4_cminst_clkdm_enable_hwsup - put a घड़ीकरोमुख्य in hwsup-idle mode
 * @part: PRCM partition ID that the घड़ीकरोमुख्य रेजिस्टरs exist in
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @cकरोffs: Clockकरोमुख्य रेजिस्टर offset (*_CDOFFS macro)
 *
 * Put a घड़ीकरोमुख्य referred to by (@part, @inst, @cकरोffs) पूर्णांकo
 * hardware-supervised idle mode.  No वापस value.
 */
अटल व्योम omap4_cminst_clkdm_enable_hwsup(u8 part, u16 inst, u16 cकरोffs)
अणु
	_clktrctrl_ग_लिखो(OMAP34XX_CLKSTCTRL_ENABLE_AUTO, part, inst, cकरोffs);
पूर्ण

/**
 * omap4_cminst_clkdm_disable_hwsup - put a घड़ीकरोमुख्य in swsup-idle mode
 * @part: PRCM partition ID that the घड़ीकरोमुख्य रेजिस्टरs exist in
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @cकरोffs: Clockकरोमुख्य रेजिस्टर offset (*_CDOFFS macro)
 *
 * Put a घड़ीकरोमुख्य referred to by (@part, @inst, @cकरोffs) पूर्णांकo
 * software-supervised idle mode, i.e., controlled manually by the
 * Linux OMAP घड़ीकरोमुख्य code.  No वापस value.
 */
अटल व्योम omap4_cminst_clkdm_disable_hwsup(u8 part, u16 inst, u16 cकरोffs)
अणु
	_clktrctrl_ग_लिखो(OMAP34XX_CLKSTCTRL_DISABLE_AUTO, part, inst, cकरोffs);
पूर्ण

/**
 * omap4_cminst_clkdm_क्रमce_sleep - try to take a घड़ीकरोमुख्य out of idle
 * @part: PRCM partition ID that the घड़ीकरोमुख्य रेजिस्टरs exist in
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @cकरोffs: Clockकरोमुख्य रेजिस्टर offset (*_CDOFFS macro)
 *
 * Take a घड़ीकरोमुख्य referred to by (@part, @inst, @cकरोffs) out of idle,
 * waking it up.  No वापस value.
 */
अटल व्योम omap4_cminst_clkdm_क्रमce_wakeup(u8 part, u16 inst, u16 cकरोffs)
अणु
	_clktrctrl_ग_लिखो(OMAP34XX_CLKSTCTRL_FORCE_WAKEUP, part, inst, cकरोffs);
पूर्ण

/*
 *
 */

अटल व्योम omap4_cminst_clkdm_क्रमce_sleep(u8 part, u16 inst, u16 cकरोffs)
अणु
	_clktrctrl_ग_लिखो(OMAP34XX_CLKSTCTRL_FORCE_SLEEP, part, inst, cकरोffs);
पूर्ण

/**
 * omap4_cminst_रुको_module_पढ़ोy - रुको क्रम a module to be in 'func' state
 * @part: PRCM partition ID that the CM_CLKCTRL रेजिस्टर exists in
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @clkctrl_offs: Module घड़ी control रेजिस्टर offset (*_CLKCTRL macro)
 * @bit_shअगरt: bit shअगरt क्रम the रेजिस्टर, ignored क्रम OMAP4+
 *
 * Wait क्रम the module IDLEST to be functional. If the idle state is in any
 * the non functional state (trans, idle or disabled), module and thus the
 * sysconfig cannot be accessed and will probably lead to an "imprecise
 * बाह्यal पात"
 */
अटल पूर्णांक omap4_cminst_रुको_module_पढ़ोy(u8 part, s16 inst, u16 clkctrl_offs,
					  u8 bit_shअगरt)
अणु
	पूर्णांक i = 0;

	omap_test_समयout(_is_module_पढ़ोy(part, inst, clkctrl_offs),
			  MAX_MODULE_READY_TIME, i);

	वापस (i < MAX_MODULE_READY_TIME) ? 0 : -EBUSY;
पूर्ण

/**
 * omap4_cminst_रुको_module_idle - रुको क्रम a module to be in 'disabled'
 * state
 * @part: PRCM partition ID that the CM_CLKCTRL रेजिस्टर exists in
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @clkctrl_offs: Module घड़ी control रेजिस्टर offset (*_CLKCTRL macro)
 * @bit_shअगरt: Bit shअगरt क्रम the रेजिस्टर, ignored क्रम OMAP4+
 *
 * Wait क्रम the module IDLEST to be disabled. Some PRCM transition,
 * like reset निश्चितion or parent घड़ी de-activation must रुको the
 * module to be fully disabled.
 */
अटल पूर्णांक omap4_cminst_रुको_module_idle(u8 part, s16 inst, u16 clkctrl_offs,
					 u8 bit_shअगरt)
अणु
	पूर्णांक i = 0;

	omap_test_समयout((_clkctrl_idlest(part, inst, clkctrl_offs) ==
			   CLKCTRL_IDLEST_DISABLED),
			  MAX_MODULE_DISABLE_TIME, i);

	वापस (i < MAX_MODULE_DISABLE_TIME) ? 0 : -EBUSY;
पूर्ण

/**
 * omap4_cminst_module_enable - Enable the modulemode inside CLKCTRL
 * @mode: Module mode (SW or HW)
 * @part: PRCM partition ID that the CM_CLKCTRL रेजिस्टर exists in
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @clkctrl_offs: Module घड़ी control रेजिस्टर offset (*_CLKCTRL macro)
 *
 * No वापस value.
 */
अटल व्योम omap4_cminst_module_enable(u8 mode, u8 part, u16 inst,
				       u16 clkctrl_offs)
अणु
	u32 v;

	v = omap4_cminst_पढ़ो_inst_reg(part, inst, clkctrl_offs);
	v &= ~OMAP4430_MODULEMODE_MASK;
	v |= mode << OMAP4430_MODULEMODE_SHIFT;
	omap4_cminst_ग_लिखो_inst_reg(v, part, inst, clkctrl_offs);
पूर्ण

/**
 * omap4_cminst_module_disable - Disable the module inside CLKCTRL
 * @part: PRCM partition ID that the CM_CLKCTRL रेजिस्टर exists in
 * @inst: CM instance रेजिस्टर offset (*_INST macro)
 * @clkctrl_offs: Module घड़ी control रेजिस्टर offset (*_CLKCTRL macro)
 *
 * No वापस value.
 */
अटल व्योम omap4_cminst_module_disable(u8 part, u16 inst, u16 clkctrl_offs)
अणु
	u32 v;

	v = omap4_cminst_पढ़ो_inst_reg(part, inst, clkctrl_offs);
	v &= ~OMAP4430_MODULEMODE_MASK;
	omap4_cminst_ग_लिखो_inst_reg(v, part, inst, clkctrl_offs);
पूर्ण

/*
 * Clockकरोमुख्य low-level functions
 */

अटल पूर्णांक omap4_clkdm_add_wkup_sleep_dep(काष्ठा घड़ीकरोमुख्य *clkdm1,
					काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	omap4_cminst_set_inst_reg_bits((1 << clkdm2->dep_bit),
				       clkdm1->prcm_partition,
				       clkdm1->cm_inst, clkdm1->clkdm_offs +
				       OMAP4_CM_STATICDEP);
	वापस 0;
पूर्ण

अटल पूर्णांक omap4_clkdm_del_wkup_sleep_dep(काष्ठा घड़ीकरोमुख्य *clkdm1,
					काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	omap4_cminst_clear_inst_reg_bits((1 << clkdm2->dep_bit),
					 clkdm1->prcm_partition,
					 clkdm1->cm_inst, clkdm1->clkdm_offs +
					 OMAP4_CM_STATICDEP);
	वापस 0;
पूर्ण

अटल पूर्णांक omap4_clkdm_पढ़ो_wkup_sleep_dep(काष्ठा घड़ीकरोमुख्य *clkdm1,
					काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	वापस omap4_cminst_पढ़ो_inst_reg_bits(clkdm1->prcm_partition,
					       clkdm1->cm_inst,
					       clkdm1->clkdm_offs +
					       OMAP4_CM_STATICDEP,
					       (1 << clkdm2->dep_bit));
पूर्ण

अटल पूर्णांक omap4_clkdm_clear_all_wkup_sleep_deps(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	काष्ठा clkdm_dep *cd;
	u32 mask = 0;

	अगर (!clkdm->prcm_partition)
		वापस 0;

	क्रम (cd = clkdm->wkdep_srcs; cd && cd->clkdm_name; cd++) अणु
		अगर (!cd->clkdm)
			जारी; /* only happens अगर data is erroneous */

		mask |= 1 << cd->clkdm->dep_bit;
		cd->wkdep_usecount = 0;
	पूर्ण

	omap4_cminst_clear_inst_reg_bits(mask, clkdm->prcm_partition,
					 clkdm->cm_inst, clkdm->clkdm_offs +
					 OMAP4_CM_STATICDEP);
	वापस 0;
पूर्ण

अटल पूर्णांक omap4_clkdm_sleep(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	अगर (clkdm->flags & CLKDM_CAN_HWSUP)
		omap4_cminst_clkdm_enable_hwsup(clkdm->prcm_partition,
						clkdm->cm_inst,
						clkdm->clkdm_offs);
	अन्यथा अगर (clkdm->flags & CLKDM_CAN_FORCE_SLEEP)
		omap4_cminst_clkdm_क्रमce_sleep(clkdm->prcm_partition,
					       clkdm->cm_inst,
					       clkdm->clkdm_offs);
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक omap4_clkdm_wakeup(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	omap4_cminst_clkdm_क्रमce_wakeup(clkdm->prcm_partition,
					clkdm->cm_inst, clkdm->clkdm_offs);
	वापस 0;
पूर्ण

अटल व्योम omap4_clkdm_allow_idle(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	omap4_cminst_clkdm_enable_hwsup(clkdm->prcm_partition,
					clkdm->cm_inst, clkdm->clkdm_offs);
पूर्ण

अटल व्योम omap4_clkdm_deny_idle(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	अगर (clkdm->flags & CLKDM_CAN_FORCE_WAKEUP)
		omap4_clkdm_wakeup(clkdm);
	अन्यथा
		omap4_cminst_clkdm_disable_hwsup(clkdm->prcm_partition,
						 clkdm->cm_inst,
						 clkdm->clkdm_offs);
पूर्ण

अटल पूर्णांक omap4_clkdm_clk_enable(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	अगर (clkdm->flags & CLKDM_CAN_FORCE_WAKEUP)
		वापस omap4_clkdm_wakeup(clkdm);

	वापस 0;
पूर्ण

अटल पूर्णांक omap4_clkdm_clk_disable(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	bool hwsup = false;

	अगर (!clkdm->prcm_partition)
		वापस 0;

	/*
	 * The CLKDM_MISSING_IDLE_REPORTING flag करोcumentation has
	 * more details on the unpleasant problem this is working
	 * around
	 */
	अगर (clkdm->flags & CLKDM_MISSING_IDLE_REPORTING &&
	    !(clkdm->flags & CLKDM_CAN_FORCE_SLEEP)) अणु
		omap4_clkdm_allow_idle(clkdm);
		वापस 0;
	पूर्ण

	hwsup = omap4_cminst_is_clkdm_in_hwsup(clkdm->prcm_partition,
					clkdm->cm_inst, clkdm->clkdm_offs);

	अगर (!hwsup && (clkdm->flags & CLKDM_CAN_FORCE_SLEEP))
		omap4_clkdm_sleep(clkdm);

	वापस 0;
पूर्ण

अटल u32 omap4_cminst_xlate_clkctrl(u8 part, u16 inst, u16 offset)
अणु
	वापस _cm_bases[part].pa + inst + offset;
पूर्ण

/**
 * omap4_clkdm_save_context - Save the घड़ीकरोमुख्य modulemode context
 * @clkdm: The घड़ीकरोमुख्य poपूर्णांकer whose context needs to be saved
 *
 * Save the घड़ीकरोमुख्य modulemode context.
 */
अटल पूर्णांक omap4_clkdm_save_context(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	clkdm->context = omap4_cminst_पढ़ो_inst_reg(clkdm->prcm_partition,
						    clkdm->cm_inst,
						    clkdm->clkdm_offs +
						    OMAP4_CM_CLKSTCTRL);
	clkdm->context &= OMAP4430_MODULEMODE_MASK;
	वापस 0;
पूर्ण

/**
 * omap4_clkdm_restore_context - Restore the घड़ीकरोमुख्य modulemode context
 * @clkdm: The घड़ीकरोमुख्य poपूर्णांकer whose context needs to be restored
 *
 * Restore the घड़ीकरोमुख्य modulemode context.
 */
अटल पूर्णांक omap4_clkdm_restore_context(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	चयन (clkdm->context) अणु
	हाल OMAP34XX_CLKSTCTRL_DISABLE_AUTO:
		omap4_clkdm_deny_idle(clkdm);
		अवरोध;
	हाल OMAP34XX_CLKSTCTRL_FORCE_SLEEP:
		omap4_clkdm_sleep(clkdm);
		अवरोध;
	हाल OMAP34XX_CLKSTCTRL_FORCE_WAKEUP:
		omap4_clkdm_wakeup(clkdm);
		अवरोध;
	हाल OMAP34XX_CLKSTCTRL_ENABLE_AUTO:
		omap4_clkdm_allow_idle(clkdm);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा clkdm_ops omap4_clkdm_operations = अणु
	.clkdm_add_wkdep	= omap4_clkdm_add_wkup_sleep_dep,
	.clkdm_del_wkdep	= omap4_clkdm_del_wkup_sleep_dep,
	.clkdm_पढ़ो_wkdep	= omap4_clkdm_पढ़ो_wkup_sleep_dep,
	.clkdm_clear_all_wkdeps	= omap4_clkdm_clear_all_wkup_sleep_deps,
	.clkdm_add_sleepdep	= omap4_clkdm_add_wkup_sleep_dep,
	.clkdm_del_sleepdep	= omap4_clkdm_del_wkup_sleep_dep,
	.clkdm_पढ़ो_sleepdep	= omap4_clkdm_पढ़ो_wkup_sleep_dep,
	.clkdm_clear_all_sleepdeps	= omap4_clkdm_clear_all_wkup_sleep_deps,
	.clkdm_sleep		= omap4_clkdm_sleep,
	.clkdm_wakeup		= omap4_clkdm_wakeup,
	.clkdm_allow_idle	= omap4_clkdm_allow_idle,
	.clkdm_deny_idle	= omap4_clkdm_deny_idle,
	.clkdm_clk_enable	= omap4_clkdm_clk_enable,
	.clkdm_clk_disable	= omap4_clkdm_clk_disable,
	.clkdm_save_context	= omap4_clkdm_save_context,
	.clkdm_restore_context	= omap4_clkdm_restore_context,
पूर्ण;

काष्ठा clkdm_ops am43xx_clkdm_operations = अणु
	.clkdm_sleep		= omap4_clkdm_sleep,
	.clkdm_wakeup		= omap4_clkdm_wakeup,
	.clkdm_allow_idle	= omap4_clkdm_allow_idle,
	.clkdm_deny_idle	= omap4_clkdm_deny_idle,
	.clkdm_clk_enable	= omap4_clkdm_clk_enable,
	.clkdm_clk_disable	= omap4_clkdm_clk_disable,
पूर्ण;

अटल स्थिर काष्ठा cm_ll_data omap4xxx_cm_ll_data = अणु
	.रुको_module_पढ़ोy	= &omap4_cminst_रुको_module_पढ़ोy,
	.रुको_module_idle	= &omap4_cminst_रुको_module_idle,
	.module_enable		= &omap4_cminst_module_enable,
	.module_disable		= &omap4_cminst_module_disable,
	.xlate_clkctrl		= &omap4_cminst_xlate_clkctrl,
पूर्ण;

पूर्णांक __init omap4_cm_init(स्थिर काष्ठा omap_prcm_init_data *data)
अणु
	omap_cm_base_init();

	वापस cm_रेजिस्टर(&omap4xxx_cm_ll_data);
पूर्ण

अटल व्योम __निकास omap4_cm_निकास(व्योम)
अणु
	cm_unरेजिस्टर(&omap4xxx_cm_ll_data);
पूर्ण
__निकासcall(omap4_cm_निकास);
