<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP2/3/4 घातerकरोमुख्य control
 *
 * Copyright (C) 2007-2008, 2010 Texas Instruments, Inc.
 * Copyright (C) 2007-2011 Nokia Corporation
 *
 * Paul Walmsley
 *
 * XXX This should be moved to the mach-omap2/ directory at the earliest
 * opportunity.
 */

#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_POWERDOMAIN_H
#घोषणा __ARCH_ARM_MACH_OMAP2_POWERDOMAIN_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>

/* Powerकरोमुख्य basic घातer states */
#घोषणा PWRDM_POWER_OFF		0x0
#घोषणा PWRDM_POWER_RET		0x1
#घोषणा PWRDM_POWER_INACTIVE	0x2
#घोषणा PWRDM_POWER_ON		0x3

#घोषणा PWRDM_MAX_PWRSTS	4

/* Powerकरोमुख्य allowable state bitfields */
#घोषणा PWRSTS_ON		(1 << PWRDM_POWER_ON)
#घोषणा PWRSTS_INACTIVE		(1 << PWRDM_POWER_INACTIVE)
#घोषणा PWRSTS_RET		(1 << PWRDM_POWER_RET)
#घोषणा PWRSTS_OFF		(1 << PWRDM_POWER_OFF)

#घोषणा PWRSTS_OFF_ON		(PWRSTS_OFF | PWRSTS_ON)
#घोषणा PWRSTS_OFF_RET		(PWRSTS_OFF | PWRSTS_RET)
#घोषणा PWRSTS_RET_ON		(PWRSTS_RET | PWRSTS_ON)
#घोषणा PWRSTS_OFF_RET_ON	(PWRSTS_OFF_RET | PWRSTS_ON)
#घोषणा PWRSTS_INA_ON		(PWRSTS_INACTIVE | PWRSTS_ON)


/*
 * Powerकरोमुख्य flags (काष्ठा घातerकरोमुख्य.flags)
 *
 * PWRDM_HAS_HDWR_SAR - घातerकरोमुख्य has hardware save-and-restore support
 *
 * PWRDM_HAS_MPU_QUIRK - MPU pwr करोमुख्य has MEM bank 0 bits in MEM
 * bank 1 position. This is true क्रम OMAP3430
 *
 * PWRDM_HAS_LOWPOWERSTATECHANGE - can transition from a sleep state
 * to a lower sleep state without waking up the घातerकरोमुख्य
 */
#घोषणा PWRDM_HAS_HDWR_SAR		BIT(0)
#घोषणा PWRDM_HAS_MPU_QUIRK		BIT(1)
#घोषणा PWRDM_HAS_LOWPOWERSTATECHANGE	BIT(2)

/*
 * Number of memory banks that are घातer-controllable.	On OMAP4430, the
 * maximum is 5.
 */
#घोषणा PWRDM_MAX_MEM_BANKS	5

/*
 * Maximum number of घड़ीकरोमुख्यs that can be associated with a घातerकरोमुख्य.
 * PER घातerकरोमुख्य on AM33XX is the worst हाल
 */
#घोषणा PWRDM_MAX_CLKDMS	11

/* XXX A completely arbitrary number. What is reasonable here? */
#घोषणा PWRDM_TRANSITION_BAILOUT 100000

काष्ठा घड़ीकरोमुख्य;
काष्ठा घातerकरोमुख्य;
काष्ठा voltageकरोमुख्य;

/**
 * काष्ठा घातerकरोमुख्य - OMAP घातerकरोमुख्य
 * @name: Powerकरोमुख्य name
 * @voltdm: voltageकरोमुख्य containing this घातerकरोमुख्य
 * @prcm_offs: the address offset from CM_BASE/PRM_BASE
 * @prcm_partition: (OMAP4 only) the PRCM partition ID containing @prcm_offs
 * @pwrsts: Possible घातerकरोमुख्य घातer states
 * @pwrsts_logic_ret: Possible logic घातer states when pwrdm in RETENTION
 * @flags: Powerकरोमुख्य flags
 * @banks: Number of software-controllable memory banks in this घातerकरोमुख्य
 * @pwrsts_mem_ret: Possible memory bank pwrstates when pwrdm in RETENTION
 * @pwrsts_mem_on: Possible memory bank pwrstates when pwrdm in ON
 * @pwrdm_clkdms: Clockकरोमुख्यs in this घातerकरोमुख्य
 * @node: list_head linking all घातerकरोमुख्यs
 * @voltdm_node: list_head linking all घातerकरोमुख्यs in a voltageकरोमुख्य
 * @pwrstctrl_offs: (AM33XX only) XXX_PWRSTCTRL reg offset from prcm_offs
 * @pwrstst_offs: (AM33XX only) XXX_PWRSTST reg offset from prcm_offs
 * @logicretstate_mask: (AM33XX only) mask क्रम logic retention bitfield
 *	in @pwrstctrl_offs
 * @mem_on_mask: (AM33XX only) mask क्रम mem on bitfield in @pwrstctrl_offs
 * @mem_ret_mask: (AM33XX only) mask क्रम mem ret bitfield in @pwrstctrl_offs
 * @mem_pwrst_mask: (AM33XX only) mask क्रम mem state bitfield in @pwrstst_offs
 * @mem_retst_mask: (AM33XX only) mask क्रम mem retention state bitfield
 *	in @pwrstctrl_offs
 * @state:
 * @state_counter:
 * @समयr:
 * @state_समयr:
 * @_lock: spinlock used to serialize घातerकरोमुख्य and some घड़ीकरोमुख्य ops
 * @_lock_flags: stored flags when @_lock is taken
 *
 * @prcm_partition possible values are defined in mach-omap2/prcm44xx.h.
 */
काष्ठा घातerकरोमुख्य अणु
	स्थिर अक्षर *name;
	जोड़ अणु
		स्थिर अक्षर *name;
		काष्ठा voltageकरोमुख्य *ptr;
	पूर्ण voltdm;
	स्थिर s16 prcm_offs;
	स्थिर u8 pwrsts;
	स्थिर u8 pwrsts_logic_ret;
	स्थिर u8 flags;
	स्थिर u8 banks;
	स्थिर u8 pwrsts_mem_ret[PWRDM_MAX_MEM_BANKS];
	स्थिर u8 pwrsts_mem_on[PWRDM_MAX_MEM_BANKS];
	स्थिर u8 prcm_partition;
	काष्ठा घड़ीकरोमुख्य *pwrdm_clkdms[PWRDM_MAX_CLKDMS];
	काष्ठा list_head node;
	काष्ठा list_head voltdm_node;
	पूर्णांक state;
	अचिन्हित state_counter[PWRDM_MAX_PWRSTS];
	अचिन्हित ret_logic_off_counter;
	अचिन्हित ret_mem_off_counter[PWRDM_MAX_MEM_BANKS];
	spinlock_t _lock;
	अचिन्हित दीर्घ _lock_flags;
	स्थिर u8 pwrstctrl_offs;
	स्थिर u8 pwrstst_offs;
	स्थिर u32 logicretstate_mask;
	स्थिर u32 mem_on_mask[PWRDM_MAX_MEM_BANKS];
	स्थिर u32 mem_ret_mask[PWRDM_MAX_MEM_BANKS];
	स्थिर u32 mem_pwrst_mask[PWRDM_MAX_MEM_BANKS];
	स्थिर u32 mem_retst_mask[PWRDM_MAX_MEM_BANKS];

#अगर_घोषित CONFIG_PM_DEBUG
	s64 समयr;
	s64 state_समयr[PWRDM_MAX_PWRSTS];
#पूर्ण_अगर
	u32 context;
पूर्ण;

/**
 * काष्ठा pwrdm_ops - Arch specअगरic function implementations
 * @pwrdm_set_next_pwrst: Set the target घातer state क्रम a pd
 * @pwrdm_पढ़ो_next_pwrst: Read the target घातer state set क्रम a pd
 * @pwrdm_पढ़ो_pwrst: Read the current घातer state of a pd
 * @pwrdm_पढ़ो_prev_pwrst: Read the prev घातer state entered by the pd
 * @pwrdm_set_logic_retst: Set the logic state in RET क्रम a pd
 * @pwrdm_set_mem_onst: Set the Memory state in ON क्रम a pd
 * @pwrdm_set_mem_retst: Set the Memory state in RET क्रम a pd
 * @pwrdm_पढ़ो_logic_pwrst: Read the current logic state of a pd
 * @pwrdm_पढ़ो_prev_logic_pwrst: Read the previous logic state entered by a pd
 * @pwrdm_पढ़ो_logic_retst: Read the logic state in RET क्रम a pd
 * @pwrdm_पढ़ो_mem_pwrst: Read the current memory state of a pd
 * @pwrdm_पढ़ो_prev_mem_pwrst: Read the previous memory state entered by a pd
 * @pwrdm_पढ़ो_mem_retst: Read the memory state in RET क्रम a pd
 * @pwrdm_clear_all_prev_pwrst: Clear all previous घातer states logged क्रम a pd
 * @pwrdm_enable_hdwr_sar: Enable Hardware Save-Restore feature क्रम the pd
 * @pwrdm_disable_hdwr_sar: Disable Hardware Save-Restore feature क्रम a pd
 * @pwrdm_set_lowpwrstchange: Enable pd transitions from a shallow to deep sleep
 * @pwrdm_रुको_transition: Wait क्रम a pd state transition to complete
 * @pwrdm_has_voltdm: Check अगर a voltdm association is needed
 *
 * Regarding @pwrdm_set_lowpwrstchange: On the OMAP2 and 3-family
 * chips, a घातerकरोमुख्य's घातer state is not allowed to directly
 * transition from one low-घातer state (e.g., CSWR) to another
 * low-घातer state (e.g., OFF) without first waking up the
 * घातerकरोमुख्य.  This wastes energy.  So OMAP4 chips support the
 * ability to transition a घातerकरोमुख्य घातer state directly from one
 * low-घातer state to another.  The function poपूर्णांकed to by
 * @pwrdm_set_lowpwrstchange is पूर्णांकended to configure the OMAP4
 * hardware घातerकरोमुख्य state machine to enable this feature.
 */
काष्ठा pwrdm_ops अणु
	पूर्णांक	(*pwrdm_set_next_pwrst)(काष्ठा घातerकरोमुख्य *pwrdm, u8 pwrst);
	पूर्णांक	(*pwrdm_पढ़ो_next_pwrst)(काष्ठा घातerकरोमुख्य *pwrdm);
	पूर्णांक	(*pwrdm_पढ़ो_pwrst)(काष्ठा घातerकरोमुख्य *pwrdm);
	पूर्णांक	(*pwrdm_पढ़ो_prev_pwrst)(काष्ठा घातerकरोमुख्य *pwrdm);
	पूर्णांक	(*pwrdm_set_logic_retst)(काष्ठा घातerकरोमुख्य *pwrdm, u8 pwrst);
	पूर्णांक	(*pwrdm_set_mem_onst)(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank, u8 pwrst);
	पूर्णांक	(*pwrdm_set_mem_retst)(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank, u8 pwrst);
	पूर्णांक	(*pwrdm_पढ़ो_logic_pwrst)(काष्ठा घातerकरोमुख्य *pwrdm);
	पूर्णांक	(*pwrdm_पढ़ो_prev_logic_pwrst)(काष्ठा घातerकरोमुख्य *pwrdm);
	पूर्णांक	(*pwrdm_पढ़ो_logic_retst)(काष्ठा घातerकरोमुख्य *pwrdm);
	पूर्णांक	(*pwrdm_पढ़ो_mem_pwrst)(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank);
	पूर्णांक	(*pwrdm_पढ़ो_prev_mem_pwrst)(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank);
	पूर्णांक	(*pwrdm_पढ़ो_mem_retst)(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank);
	पूर्णांक	(*pwrdm_clear_all_prev_pwrst)(काष्ठा घातerकरोमुख्य *pwrdm);
	पूर्णांक	(*pwrdm_enable_hdwr_sar)(काष्ठा घातerकरोमुख्य *pwrdm);
	पूर्णांक	(*pwrdm_disable_hdwr_sar)(काष्ठा घातerकरोमुख्य *pwrdm);
	पूर्णांक	(*pwrdm_set_lowpwrstchange)(काष्ठा घातerकरोमुख्य *pwrdm);
	पूर्णांक	(*pwrdm_रुको_transition)(काष्ठा घातerकरोमुख्य *pwrdm);
	पूर्णांक	(*pwrdm_has_voltdm)(व्योम);
	व्योम	(*pwrdm_save_context)(काष्ठा घातerकरोमुख्य *pwrdm);
	व्योम	(*pwrdm_restore_context)(काष्ठा घातerकरोमुख्य *pwrdm);
पूर्ण;

पूर्णांक pwrdm_रेजिस्टर_platक्रमm_funcs(काष्ठा pwrdm_ops *custom_funcs);
पूर्णांक pwrdm_रेजिस्टर_pwrdms(काष्ठा घातerकरोमुख्य **pwrdm_list);
पूर्णांक pwrdm_complete_init(व्योम);

काष्ठा घातerकरोमुख्य *pwrdm_lookup(स्थिर अक्षर *name);

पूर्णांक pwrdm_क्रम_each(पूर्णांक (*fn)(काष्ठा घातerकरोमुख्य *pwrdm, व्योम *user),
			व्योम *user);
पूर्णांक pwrdm_क्रम_each_nolock(पूर्णांक (*fn)(काष्ठा घातerकरोमुख्य *pwrdm, व्योम *user),
			व्योम *user);

पूर्णांक pwrdm_add_clkdm(काष्ठा घातerकरोमुख्य *pwrdm, काष्ठा घड़ीकरोमुख्य *clkdm);

पूर्णांक pwrdm_get_mem_bank_count(काष्ठा घातerकरोमुख्य *pwrdm);

u8 pwrdm_get_valid_lp_state(काष्ठा घातerकरोमुख्य *pwrdm,
			    bool is_logic_state, u8 req_state);

पूर्णांक pwrdm_set_next_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 pwrst);
पूर्णांक pwrdm_पढ़ो_next_pwrst(काष्ठा घातerकरोमुख्य *pwrdm);
पूर्णांक pwrdm_पढ़ो_pwrst(काष्ठा घातerकरोमुख्य *pwrdm);
पूर्णांक pwrdm_पढ़ो_prev_pwrst(काष्ठा घातerकरोमुख्य *pwrdm);
पूर्णांक pwrdm_clear_all_prev_pwrst(काष्ठा घातerकरोमुख्य *pwrdm);

पूर्णांक pwrdm_set_logic_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 pwrst);
पूर्णांक pwrdm_set_mem_onst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank, u8 pwrst);
पूर्णांक pwrdm_set_mem_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank, u8 pwrst);

पूर्णांक pwrdm_पढ़ो_logic_pwrst(काष्ठा घातerकरोमुख्य *pwrdm);
पूर्णांक pwrdm_पढ़ो_prev_logic_pwrst(काष्ठा घातerकरोमुख्य *pwrdm);
पूर्णांक pwrdm_पढ़ो_logic_retst(काष्ठा घातerकरोमुख्य *pwrdm);
पूर्णांक pwrdm_पढ़ो_mem_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank);
पूर्णांक pwrdm_पढ़ो_prev_mem_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank);
पूर्णांक pwrdm_पढ़ो_mem_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank);

पूर्णांक pwrdm_enable_hdwr_sar(काष्ठा घातerकरोमुख्य *pwrdm);
पूर्णांक pwrdm_disable_hdwr_sar(काष्ठा घातerकरोमुख्य *pwrdm);
bool pwrdm_has_hdwr_sar(काष्ठा घातerकरोमुख्य *pwrdm);

पूर्णांक pwrdm_state_चयन_nolock(काष्ठा घातerकरोमुख्य *pwrdm);
पूर्णांक pwrdm_state_चयन(काष्ठा घातerकरोमुख्य *pwrdm);
पूर्णांक pwrdm_pre_transition(काष्ठा घातerकरोमुख्य *pwrdm);
पूर्णांक pwrdm_post_transition(काष्ठा घातerकरोमुख्य *pwrdm);
पूर्णांक pwrdm_get_context_loss_count(काष्ठा घातerकरोमुख्य *pwrdm);
bool pwrdm_can_ever_lose_context(काष्ठा घातerकरोमुख्य *pwrdm);

बाह्य पूर्णांक omap_set_pwrdm_state(काष्ठा घातerकरोमुख्य *pwrdm, u8 state);

बाह्य व्योम omap242x_घातerकरोमुख्यs_init(व्योम);
बाह्य व्योम omap243x_घातerकरोमुख्यs_init(व्योम);
बाह्य व्योम omap3xxx_घातerकरोमुख्यs_init(व्योम);
बाह्य व्योम am33xx_घातerकरोमुख्यs_init(व्योम);
बाह्य व्योम omap44xx_घातerकरोमुख्यs_init(व्योम);
बाह्य व्योम omap54xx_घातerकरोमुख्यs_init(व्योम);
बाह्य व्योम dra7xx_घातerकरोमुख्यs_init(व्योम);
व्योम am43xx_घातerकरोमुख्यs_init(व्योम);

बाह्य काष्ठा pwrdm_ops omap2_pwrdm_operations;
बाह्य काष्ठा pwrdm_ops omap3_pwrdm_operations;
बाह्य काष्ठा pwrdm_ops am33xx_pwrdm_operations;
बाह्य काष्ठा pwrdm_ops omap4_pwrdm_operations;

/* Common Internal functions used across OMAP rev's */
बाह्य u32 omap2_pwrdm_get_mem_bank_onstate_mask(u8 bank);
बाह्य u32 omap2_pwrdm_get_mem_bank_retst_mask(u8 bank);
बाह्य u32 omap2_pwrdm_get_mem_bank_stst_mask(u8 bank);

बाह्य काष्ठा घातerकरोमुख्य wkup_omap2_pwrdm;
बाह्य काष्ठा घातerकरोमुख्य gfx_omap2_pwrdm;

बाह्य व्योम pwrdm_lock(काष्ठा घातerकरोमुख्य *pwrdm);
बाह्य व्योम pwrdm_unlock(काष्ठा घातerकरोमुख्य *pwrdm);

बाह्य व्योम pwrdms_save_context(व्योम);
बाह्य व्योम pwrdms_restore_context(व्योम);

बाह्य व्योम pwrdms_lost_घातer(व्योम);
#पूर्ण_अगर
