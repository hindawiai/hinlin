<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP2/3 घड़ीकरोमुख्य framework functions
 *
 * Copyright (C) 2008, 2012 Texas Instruments, Inc.
 * Copyright (C) 2008-2011 Nokia Corporation
 *
 * Paul Walmsley
 */

#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_CLOCKDOMAIN_H
#घोषणा __ARCH_ARM_MACH_OMAP2_CLOCKDOMAIN_H

#समावेश <linux/init.h>

#समावेश "powerdomain.h"
#समावेश "clock.h"

/*
 * Clockकरोमुख्य flags
 *
 * XXX Document CLKDM_CAN_* flags
 *
 * CLKDM_NO_AUTODEPS: Prevent "autodeps" from being added/हटाओd from this
 *     घड़ीकरोमुख्य.  (Currently, this applies to OMAP3 घड़ीकरोमुख्यs only.)
 * CLKDM_ACTIVE_WITH_MPU: The PRCM guarantees that this घड़ीकरोमुख्य is
 *     active whenever the MPU is active.  True क्रम पूर्णांकerconnects and
 *     the WKUP घड़ीकरोमुख्यs.
 * CLKDM_MISSING_IDLE_REPORTING: The idle status of the IP blocks and
 *     घड़ीs inside this घड़ीकरोमुख्य are not taken पूर्णांकo account by
 *     the PRCM when determining whether the घड़ीकरोमुख्य is idle.
 *     Without this flag, अगर the घड़ीकरोमुख्य is set to
 *     hardware-supervised idle mode, the PRCM may transition the
 *     enclosing घातerकरोमुख्य to a low घातer state, even when devices
 *     inside the घड़ीकरोमुख्य and घातerकरोमुख्य are in use.  (An example
 *     of such a घड़ीकरोमुख्य is the EMU घड़ीकरोमुख्य on OMAP3/4.)  If
 *     this flag is set, and the घड़ीकरोमुख्य करोes not support the
 *     क्रमce-sleep mode, then the HW_AUTO mode will be used to put the
 *     घड़ीकरोमुख्य to sleep.  Similarly, अगर the घड़ीकरोमुख्य supports
 *     the क्रमce-wakeup mode, then it will be used whenever a घड़ी or
 *     IP block inside the घड़ीकरोमुख्य is active, rather than the
 *     HW_AUTO mode.
 */
#घोषणा CLKDM_CAN_FORCE_SLEEP			(1 << 0)
#घोषणा CLKDM_CAN_FORCE_WAKEUP			(1 << 1)
#घोषणा CLKDM_CAN_ENABLE_AUTO			(1 << 2)
#घोषणा CLKDM_CAN_DISABLE_AUTO			(1 << 3)
#घोषणा CLKDM_NO_AUTODEPS			(1 << 4)
#घोषणा CLKDM_ACTIVE_WITH_MPU			(1 << 5)
#घोषणा CLKDM_MISSING_IDLE_REPORTING		(1 << 6)

#घोषणा CLKDM_CAN_HWSUP		(CLKDM_CAN_ENABLE_AUTO | CLKDM_CAN_DISABLE_AUTO)
#घोषणा CLKDM_CAN_SWSUP		(CLKDM_CAN_FORCE_SLEEP | CLKDM_CAN_FORCE_WAKEUP)
#घोषणा CLKDM_CAN_HWSUP_SWSUP	(CLKDM_CAN_SWSUP | CLKDM_CAN_HWSUP)

/**
 * काष्ठा clkdm_स्वतःdep - clkdm deps to add when entering/निकासing hwsup mode
 * @clkdm: घड़ीकरोमुख्य to add wkdep+sleepdep on - set name member only
 *
 * A घड़ीकरोमुख्य that should have wkdeps and sleepdeps added when a
 * घड़ीकरोमुख्य should stay active in hwsup mode; and conversely,
 * हटाओd when the घड़ीकरोमुख्य should be allowed to go inactive in
 * hwsup mode.
 *
 * Autodeps are deprecated and should be हटाओd after
 * omap_hwmod-based fine-grained module idle control is added.
 */
काष्ठा clkdm_स्वतःdep अणु
	जोड़ अणु
		स्थिर अक्षर *name;
		काष्ठा घड़ीकरोमुख्य *ptr;
	पूर्ण clkdm;
पूर्ण;

/**
 * काष्ठा clkdm_dep - encode dependencies between घड़ीकरोमुख्यs
 * @clkdm_name: घड़ीकरोमुख्य name
 * @clkdm: poपूर्णांकer to the काष्ठा घड़ीकरोमुख्य of @clkdm_name
 * @wkdep_usecount: Number of wakeup dependencies causing this clkdm to wake
 * @sleepdep_usecount: Number of sleep deps that could prevent clkdm from idle
 *
 * Statically defined.  @clkdm is resolved from @clkdm_name at runसमय and
 * should not be pre-initialized.
 *
 * XXX Should also include hardware (fixed) dependencies.
 */
काष्ठा clkdm_dep अणु
	स्थिर अक्षर *clkdm_name;
	काष्ठा घड़ीकरोमुख्य *clkdm;
	s16 wkdep_usecount;
	s16 sleepdep_usecount;
पूर्ण;

/* Possible flags क्रम काष्ठा घड़ीकरोमुख्य._flags */
#घोषणा _CLKDM_FLAG_HWSUP_ENABLED		BIT(0)

काष्ठा omap_hwmod;

/**
 * काष्ठा घड़ीकरोमुख्य - OMAP घड़ीकरोमुख्य
 * @name: घड़ीकरोमुख्य name
 * @pwrdm: घातerकरोमुख्य containing this घड़ीकरोमुख्य
 * @clktrctrl_reg: CLKSTCTRL reg क्रम the given घड़ी करोमुख्य
 * @clktrctrl_mask: CLKTRCTRL/AUTOSTATE field mask in CM_CLKSTCTRL reg
 * @flags: Clockकरोमुख्य capability flags
 * @_flags: Flags क्रम use only by पूर्णांकernal घड़ीकरोमुख्य code
 * @dep_bit: Bit shअगरt of this घड़ीकरोमुख्य's PM_WKDEP/CM_SLEEPDEP bit
 * @prcm_partition: (OMAP4 only) PRCM partition ID क्रम this clkdm's रेजिस्टरs
 * @cm_inst: (OMAP4 only) CM instance रेजिस्टर offset
 * @clkdm_offs: (OMAP4 only) CM घड़ीकरोमुख्य रेजिस्टर offset
 * @wkdep_srcs: Clockकरोमुख्यs that can be told to wake this घातerकरोमुख्य up
 * @sleepdep_srcs: Clockकरोमुख्यs that can be told to keep this clkdm from inact
 * @usecount: Usecount tracking
 * @क्रमcewake_count: Usecount क्रम क्रमcing the करोमुख्य active
 * @node: list_head to link all घड़ीकरोमुख्यs together
 *
 * @prcm_partition should be a macro from mach-omap2/prcm44xx.h (OMAP4 only)
 * @cm_inst should be a macro ending in _INST from the OMAP4 CM instance
 *     definitions (OMAP4 only)
 * @clkdm_offs should be a macro ending in _CDOFFS from the OMAP4 CM instance
 *     definitions (OMAP4 only)
 */
काष्ठा घड़ीकरोमुख्य अणु
	स्थिर अक्षर *name;
	जोड़ अणु
		स्थिर अक्षर *name;
		काष्ठा घातerकरोमुख्य *ptr;
	पूर्ण pwrdm;
	स्थिर u16 clktrctrl_mask;
	स्थिर u8 flags;
	u8 _flags;
	स्थिर u8 dep_bit;
	स्थिर u8 prcm_partition;
	स्थिर u16 cm_inst;
	स्थिर u16 clkdm_offs;
	काष्ठा clkdm_dep *wkdep_srcs;
	काष्ठा clkdm_dep *sleepdep_srcs;
	पूर्णांक usecount;
	पूर्णांक क्रमcewake_count;
	काष्ठा list_head node;
	u32 context;
पूर्ण;

/**
 * काष्ठा clkdm_ops - Arch specअगरic function implementations
 * @clkdm_add_wkdep: Add a wakeup dependency between clk करोमुख्यs
 * @clkdm_del_wkdep: Delete a wakeup dependency between clk करोमुख्यs
 * @clkdm_पढ़ो_wkdep: Read wakeup dependency state between clk करोमुख्यs
 * @clkdm_clear_all_wkdeps: Remove all wakeup dependencies from the clk करोमुख्य
 * @clkdm_add_sleepdep: Add a sleep dependency between clk करोमुख्यs
 * @clkdm_del_sleepdep: Delete a sleep dependency between clk करोमुख्यs
 * @clkdm_पढ़ो_sleepdep: Read sleep dependency state between clk करोमुख्यs
 * @clkdm_clear_all_sleepdeps: Remove all sleep dependencies from the clk करोमुख्य
 * @clkdm_sleep: Force a घड़ीकरोमुख्य to sleep
 * @clkdm_wakeup: Force a घड़ीकरोमुख्य to wakeup
 * @clkdm_allow_idle: Enable hw supervised idle transitions क्रम घड़ी करोमुख्य
 * @clkdm_deny_idle: Disable hw supervised idle transitions क्रम घड़ी करोमुख्य
 * @clkdm_clk_enable: Put the clkdm in right state क्रम a घड़ी enable
 * @clkdm_clk_disable: Put the clkdm in right state क्रम a घड़ी disable
 * @clkdm_save_context: Save the current clkdm context
 * @clkdm_restore_context: Restore the clkdm context
 */
काष्ठा clkdm_ops अणु
	पूर्णांक	(*clkdm_add_wkdep)(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2);
	पूर्णांक	(*clkdm_del_wkdep)(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2);
	पूर्णांक	(*clkdm_पढ़ो_wkdep)(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2);
	पूर्णांक	(*clkdm_clear_all_wkdeps)(काष्ठा घड़ीकरोमुख्य *clkdm);
	पूर्णांक	(*clkdm_add_sleepdep)(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2);
	पूर्णांक	(*clkdm_del_sleepdep)(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2);
	पूर्णांक	(*clkdm_पढ़ो_sleepdep)(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2);
	पूर्णांक	(*clkdm_clear_all_sleepdeps)(काष्ठा घड़ीकरोमुख्य *clkdm);
	पूर्णांक	(*clkdm_sleep)(काष्ठा घड़ीकरोमुख्य *clkdm);
	पूर्णांक	(*clkdm_wakeup)(काष्ठा घड़ीकरोमुख्य *clkdm);
	व्योम	(*clkdm_allow_idle)(काष्ठा घड़ीकरोमुख्य *clkdm);
	व्योम	(*clkdm_deny_idle)(काष्ठा घड़ीकरोमुख्य *clkdm);
	पूर्णांक	(*clkdm_clk_enable)(काष्ठा घड़ीकरोमुख्य *clkdm);
	पूर्णांक	(*clkdm_clk_disable)(काष्ठा घड़ीकरोमुख्य *clkdm);
	पूर्णांक	(*clkdm_save_context)(काष्ठा घड़ीकरोमुख्य *clkdm);
	पूर्णांक	(*clkdm_restore_context)(काष्ठा घड़ीकरोमुख्य *clkdm);
पूर्ण;

पूर्णांक clkdm_रेजिस्टर_platक्रमm_funcs(काष्ठा clkdm_ops *co);
पूर्णांक clkdm_रेजिस्टर_स्वतःdeps(काष्ठा clkdm_स्वतःdep *ia);
पूर्णांक clkdm_रेजिस्टर_clkdms(काष्ठा घड़ीकरोमुख्य **c);
पूर्णांक clkdm_complete_init(व्योम);

काष्ठा घड़ीकरोमुख्य *clkdm_lookup(स्थिर अक्षर *name);

पूर्णांक clkdm_क्रम_each(पूर्णांक (*fn)(काष्ठा घड़ीकरोमुख्य *clkdm, व्योम *user),
			व्योम *user);
काष्ठा घातerकरोमुख्य *clkdm_get_pwrdm(काष्ठा घड़ीकरोमुख्य *clkdm);

पूर्णांक clkdm_add_wkdep(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2);
पूर्णांक clkdm_del_wkdep(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2);
पूर्णांक clkdm_पढ़ो_wkdep(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2);
पूर्णांक clkdm_clear_all_wkdeps(काष्ठा घड़ीकरोमुख्य *clkdm);
पूर्णांक clkdm_add_sleepdep(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2);
पूर्णांक clkdm_del_sleepdep(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2);
पूर्णांक clkdm_पढ़ो_sleepdep(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2);
पूर्णांक clkdm_clear_all_sleepdeps(काष्ठा घड़ीकरोमुख्य *clkdm);

व्योम clkdm_allow_idle_nolock(काष्ठा घड़ीकरोमुख्य *clkdm);
व्योम clkdm_allow_idle(काष्ठा घड़ीकरोमुख्य *clkdm);
व्योम clkdm_deny_idle_nolock(काष्ठा घड़ीकरोमुख्य *clkdm);
व्योम clkdm_deny_idle(काष्ठा घड़ीकरोमुख्य *clkdm);
bool clkdm_in_hwsup(काष्ठा घड़ीकरोमुख्य *clkdm);
bool clkdm_missing_idle_reporting(काष्ठा घड़ीकरोमुख्य *clkdm);

पूर्णांक clkdm_wakeup_nolock(काष्ठा घड़ीकरोमुख्य *clkdm);
पूर्णांक clkdm_wakeup(काष्ठा घड़ीकरोमुख्य *clkdm);
पूर्णांक clkdm_sleep_nolock(काष्ठा घड़ीकरोमुख्य *clkdm);
पूर्णांक clkdm_sleep(काष्ठा घड़ीकरोमुख्य *clkdm);

पूर्णांक clkdm_clk_enable(काष्ठा घड़ीकरोमुख्य *clkdm, काष्ठा clk *clk);
पूर्णांक clkdm_clk_disable(काष्ठा घड़ीकरोमुख्य *clkdm, काष्ठा clk *clk);
पूर्णांक clkdm_hwmod_enable(काष्ठा घड़ीकरोमुख्य *clkdm, काष्ठा omap_hwmod *oh);
पूर्णांक clkdm_hwmod_disable(काष्ठा घड़ीकरोमुख्य *clkdm, काष्ठा omap_hwmod *oh);

व्योम clkdm_save_context(व्योम);
व्योम clkdm_restore_context(व्योम);

बाह्य व्योम __init omap242x_घड़ीकरोमुख्यs_init(व्योम);
बाह्य व्योम __init omap243x_घड़ीकरोमुख्यs_init(व्योम);
बाह्य व्योम __init omap3xxx_घड़ीकरोमुख्यs_init(व्योम);
बाह्य व्योम __init am33xx_घड़ीकरोमुख्यs_init(व्योम);
बाह्य व्योम __init ti814x_घड़ीकरोमुख्यs_init(व्योम);
बाह्य व्योम __init ti816x_घड़ीकरोमुख्यs_init(व्योम);
बाह्य व्योम __init omap44xx_घड़ीकरोमुख्यs_init(व्योम);
बाह्य व्योम __init omap54xx_घड़ीकरोमुख्यs_init(व्योम);
बाह्य व्योम __init dra7xx_घड़ीकरोमुख्यs_init(व्योम);
व्योम am43xx_घड़ीकरोमुख्यs_init(व्योम);

बाह्य व्योम clkdm_add_स्वतःdeps(काष्ठा घड़ीकरोमुख्य *clkdm);
बाह्य व्योम clkdm_del_स्वतःdeps(काष्ठा घड़ीकरोमुख्य *clkdm);

बाह्य काष्ठा clkdm_ops omap2_clkdm_operations;
बाह्य काष्ठा clkdm_ops omap3_clkdm_operations;
बाह्य काष्ठा clkdm_ops omap4_clkdm_operations;
बाह्य काष्ठा clkdm_ops am33xx_clkdm_operations;
बाह्य काष्ठा clkdm_ops am43xx_clkdm_operations;

बाह्य काष्ठा clkdm_dep gfx_24xx_wkdeps[];
बाह्य काष्ठा clkdm_dep dsp_24xx_wkdeps[];
बाह्य काष्ठा घड़ीकरोमुख्य wkup_common_clkdm;

#पूर्ण_अगर
