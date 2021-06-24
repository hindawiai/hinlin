<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP घातerकरोमुख्य control
 *
 * Copyright (C) 2007-2008, 2011 Texas Instruments, Inc.
 * Copyright (C) 2007-2011 Nokia Corporation
 *
 * Written by Paul Walmsley
 * Added OMAP4 specअगरic support by Abhijit Pagare <abhijitpagare@ti.com>
 * State counting code by Tero Kristo <tero.kristo@nokia.com>
 */
#अघोषित DEBUG

#समावेश <linux/cpu_pm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <trace/events/घातer.h>

#समावेश "cm2xxx_3xxx.h"
#समावेश "prcm44xx.h"
#समावेश "cm44xx.h"
#समावेश "prm2xxx_3xxx.h"
#समावेश "prm44xx.h"

#समावेश <यंत्र/cpu.h>

#समावेश "powerdomain.h"
#समावेश "clockdomain.h"
#समावेश "voltage.h"

#समावेश "soc.h"
#समावेश "pm.h"

#घोषणा PWRDM_TRACE_STATES_FLAG	(1<<31)

व्योम pwrdms_save_context(व्योम);
व्योम pwrdms_restore_context(व्योम);

क्रमागत अणु
	PWRDM_STATE_NOW = 0,
	PWRDM_STATE_PREV,
पूर्ण;

/*
 * Types of sleep_चयन used पूर्णांकernally in omap_set_pwrdm_state()
 * and its associated अटल functions
 *
 * XXX Better करोcumentation is needed here
 */
#घोषणा ALREADYACTIVE_SWITCH		0
#घोषणा FORCEWAKEUP_SWITCH		1
#घोषणा LOWPOWERSTATE_SWITCH		2

/* pwrdm_list contains all रेजिस्टरed काष्ठा घातerकरोमुख्यs */
अटल LIST_HEAD(pwrdm_list);

अटल काष्ठा pwrdm_ops *arch_pwrdm;

/* Private functions */

अटल काष्ठा घातerकरोमुख्य *_pwrdm_lookup(स्थिर अक्षर *name)
अणु
	काष्ठा घातerकरोमुख्य *pwrdm, *temp_pwrdm;

	pwrdm = शून्य;

	list_क्रम_each_entry(temp_pwrdm, &pwrdm_list, node) अणु
		अगर (!म_भेद(name, temp_pwrdm->name)) अणु
			pwrdm = temp_pwrdm;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस pwrdm;
पूर्ण

/**
 * _pwrdm_रेजिस्टर - रेजिस्टर a घातerकरोमुख्य
 * @pwrdm: काष्ठा घातerकरोमुख्य * to रेजिस्टर
 *
 * Adds a घातerकरोमुख्य to the पूर्णांकernal घातerकरोमुख्य list.  Returns
 * -EINVAL अगर given a null poपूर्णांकer, -EEXIST अगर a घातerकरोमुख्य is
 * alपढ़ोy रेजिस्टरed by the provided name, or 0 upon success.
 */
अटल पूर्णांक _pwrdm_रेजिस्टर(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक i;
	काष्ठा voltageकरोमुख्य *voltdm;

	अगर (!pwrdm || !pwrdm->name)
		वापस -EINVAL;

	अगर (cpu_is_omap44xx() &&
	    pwrdm->prcm_partition == OMAP4430_INVALID_PRCM_PARTITION) अणु
		pr_err("powerdomain: %s: missing OMAP4 PRCM partition ID\n",
		       pwrdm->name);
		वापस -EINVAL;
	पूर्ण

	अगर (_pwrdm_lookup(pwrdm->name))
		वापस -EEXIST;

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_has_voltdm)
		अगर (!arch_pwrdm->pwrdm_has_voltdm())
			जाओ skip_voltdm;

	voltdm = voltdm_lookup(pwrdm->voltdm.name);
	अगर (!voltdm) अणु
		pr_err("powerdomain: %s: voltagedomain %s does not exist\n",
		       pwrdm->name, pwrdm->voltdm.name);
		वापस -EINVAL;
	पूर्ण
	pwrdm->voltdm.ptr = voltdm;
	INIT_LIST_HEAD(&pwrdm->voltdm_node);
skip_voltdm:
	spin_lock_init(&pwrdm->_lock);

	list_add(&pwrdm->node, &pwrdm_list);

	/* Initialize the घातerकरोमुख्य's state counter */
	क्रम (i = 0; i < PWRDM_MAX_PWRSTS; i++)
		pwrdm->state_counter[i] = 0;

	pwrdm->ret_logic_off_counter = 0;
	क्रम (i = 0; i < pwrdm->banks; i++)
		pwrdm->ret_mem_off_counter[i] = 0;

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_रुको_transition)
		arch_pwrdm->pwrdm_रुको_transition(pwrdm);
	pwrdm->state = pwrdm_पढ़ो_pwrst(pwrdm);
	pwrdm->state_counter[pwrdm->state] = 1;

	pr_debug("powerdomain: registered %s\n", pwrdm->name);

	वापस 0;
पूर्ण

अटल व्योम _update_logic_membank_counters(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक i;
	u8 prev_logic_pwrst, prev_mem_pwrst;

	prev_logic_pwrst = pwrdm_पढ़ो_prev_logic_pwrst(pwrdm);
	अगर ((pwrdm->pwrsts_logic_ret == PWRSTS_OFF_RET) &&
	    (prev_logic_pwrst == PWRDM_POWER_OFF))
		pwrdm->ret_logic_off_counter++;

	क्रम (i = 0; i < pwrdm->banks; i++) अणु
		prev_mem_pwrst = pwrdm_पढ़ो_prev_mem_pwrst(pwrdm, i);

		अगर ((pwrdm->pwrsts_mem_ret[i] == PWRSTS_OFF_RET) &&
		    (prev_mem_pwrst == PWRDM_POWER_OFF))
			pwrdm->ret_mem_off_counter[i]++;
	पूर्ण
पूर्ण

अटल पूर्णांक _pwrdm_state_चयन(काष्ठा घातerकरोमुख्य *pwrdm, पूर्णांक flag)
अणु

	पूर्णांक prev, next, state, trace_state = 0;

	अगर (pwrdm == शून्य)
		वापस -EINVAL;

	state = pwrdm_पढ़ो_pwrst(pwrdm);

	चयन (flag) अणु
	हाल PWRDM_STATE_NOW:
		prev = pwrdm->state;
		अवरोध;
	हाल PWRDM_STATE_PREV:
		prev = pwrdm_पढ़ो_prev_pwrst(pwrdm);
		अगर (pwrdm->state != prev)
			pwrdm->state_counter[prev]++;
		अगर (prev == PWRDM_POWER_RET)
			_update_logic_membank_counters(pwrdm);
		/*
		 * If the घातer करोमुख्य did not hit the desired state,
		 * generate a trace event with both the desired and hit states
		 */
		next = pwrdm_पढ़ो_next_pwrst(pwrdm);
		अगर (next != prev) अणु
			trace_state = (PWRDM_TRACE_STATES_FLAG |
				       ((next & OMAP_POWERSTATE_MASK) << 8) |
				       ((prev & OMAP_POWERSTATE_MASK) << 0));
			trace_घातer_करोमुख्य_target_rcuidle(pwrdm->name,
							  trace_state,
							  raw_smp_processor_id());
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (state != prev)
		pwrdm->state_counter[state]++;

	pm_dbg_update_समय(pwrdm, prev);

	pwrdm->state = state;

	वापस 0;
पूर्ण

अटल पूर्णांक _pwrdm_pre_transition_cb(काष्ठा घातerकरोमुख्य *pwrdm, व्योम *unused)
अणु
	pwrdm_clear_all_prev_pwrst(pwrdm);
	_pwrdm_state_चयन(pwrdm, PWRDM_STATE_NOW);
	वापस 0;
पूर्ण

अटल पूर्णांक _pwrdm_post_transition_cb(काष्ठा घातerकरोमुख्य *pwrdm, व्योम *unused)
अणु
	_pwrdm_state_चयन(pwrdm, PWRDM_STATE_PREV);
	वापस 0;
पूर्ण

/**
 * _pwrdm_save_clkdm_state_and_activate - prepare क्रम घातer state change
 * @pwrdm: काष्ठा घातerकरोमुख्य * to operate on
 * @curr_pwrst: current घातer state of @pwrdm
 * @pwrst: घातer state to चयन to
 *
 * Determine whether the घातerकरोमुख्य needs to be turned on beक्रमe
 * attempting to चयन घातer states.  Called by
 * omap_set_pwrdm_state().  NOTE that अगर the घातerकरोमुख्य contains
 * multiple घड़ीकरोमुख्यs, this code assumes that the first घड़ीकरोमुख्य
 * supports software-supervised wakeup mode - potentially a problem.
 * Returns the घातer state चयन mode currently in use (see the
 * "Types of sleep_switch" comment above).
 */
अटल u8 _pwrdm_save_clkdm_state_and_activate(काष्ठा घातerकरोमुख्य *pwrdm,
					       u8 curr_pwrst, u8 pwrst)
अणु
	u8 sleep_चयन;

	अगर (curr_pwrst < PWRDM_POWER_ON) अणु
		अगर (curr_pwrst > pwrst &&
		    pwrdm->flags & PWRDM_HAS_LOWPOWERSTATECHANGE &&
		    arch_pwrdm->pwrdm_set_lowpwrstchange) अणु
			sleep_चयन = LOWPOWERSTATE_SWITCH;
		पूर्ण अन्यथा अणु
			clkdm_deny_idle_nolock(pwrdm->pwrdm_clkdms[0]);
			sleep_चयन = FORCEWAKEUP_SWITCH;
		पूर्ण
	पूर्ण अन्यथा अणु
		sleep_चयन = ALREADYACTIVE_SWITCH;
	पूर्ण

	वापस sleep_चयन;
पूर्ण

/**
 * _pwrdm_restore_clkdm_state - restore the clkdm hwsup state after pwrst change
 * @pwrdm: काष्ठा घातerकरोमुख्य * to operate on
 * @sleep_चयन: वापस value from _pwrdm_save_clkdm_state_and_activate()
 *
 * Restore the घड़ीकरोमुख्य state perturbed by
 * _pwrdm_save_clkdm_state_and_activate(), and call the घातer state
 * bookkeeping code.  Called by omap_set_pwrdm_state().  NOTE that अगर
 * the घातerकरोमुख्य contains multiple घड़ीकरोमुख्यs, this assumes that
 * the first associated घड़ीकरोमुख्य supports either
 * hardware-supervised idle control in the रेजिस्टर, or
 * software-supervised sleep.  No वापस value.
 */
अटल व्योम _pwrdm_restore_clkdm_state(काष्ठा घातerकरोमुख्य *pwrdm,
				       u8 sleep_चयन)
अणु
	चयन (sleep_चयन) अणु
	हाल FORCEWAKEUP_SWITCH:
		clkdm_allow_idle_nolock(pwrdm->pwrdm_clkdms[0]);
		अवरोध;
	हाल LOWPOWERSTATE_SWITCH:
		अगर (pwrdm->flags & PWRDM_HAS_LOWPOWERSTATECHANGE &&
		    arch_pwrdm->pwrdm_set_lowpwrstchange)
			arch_pwrdm->pwrdm_set_lowpwrstchange(pwrdm);
		pwrdm_state_चयन_nolock(pwrdm);
		अवरोध;
	पूर्ण
पूर्ण

/* Public functions */

/**
 * pwrdm_रेजिस्टर_platक्रमm_funcs - रेजिस्टर घातerकरोमुख्य implementation fns
 * @po: func poपूर्णांकers क्रम arch specअगरic implementations
 *
 * Register the list of function poपूर्णांकers used to implement the
 * घातerकरोमुख्य functions on dअगरferent OMAP SoCs.  Should be called
 * beक्रमe any other pwrdm_रेजिस्टर*() function.  Returns -EINVAL अगर
 * @po is null, -EEXIST अगर platक्रमm functions have alपढ़ोy been
 * रेजिस्टरed, or 0 upon success.
 */
पूर्णांक pwrdm_रेजिस्टर_platक्रमm_funcs(काष्ठा pwrdm_ops *po)
अणु
	अगर (!po)
		वापस -EINVAL;

	अगर (arch_pwrdm)
		वापस -EEXIST;

	arch_pwrdm = po;

	वापस 0;
पूर्ण

/**
 * pwrdm_रेजिस्टर_pwrdms - रेजिस्टर SoC घातerकरोमुख्यs
 * @ps: poपूर्णांकer to an array of काष्ठा घातerकरोमुख्य to रेजिस्टर
 *
 * Register the घातerकरोमुख्यs available on a particular OMAP SoC.  Must
 * be called after pwrdm_रेजिस्टर_platक्रमm_funcs().  May be called
 * multiple बार.  Returns -EACCES अगर called beक्रमe
 * pwrdm_रेजिस्टर_platक्रमm_funcs(); -EINVAL अगर the argument @ps is
 * null; or 0 upon success.
 */
पूर्णांक pwrdm_रेजिस्टर_pwrdms(काष्ठा घातerकरोमुख्य **ps)
अणु
	काष्ठा घातerकरोमुख्य **p = शून्य;

	अगर (!arch_pwrdm)
		वापस -EEXIST;

	अगर (!ps)
		वापस -EINVAL;

	क्रम (p = ps; *p; p++)
		_pwrdm_रेजिस्टर(*p);

	वापस 0;
पूर्ण

अटल पूर्णांक cpu_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ cmd, व्योम *v)
अणु
	चयन (cmd) अणु
	हाल CPU_CLUSTER_PM_ENTER:
		अगर (enable_off_mode)
			pwrdms_save_context();
		अवरोध;
	हाल CPU_CLUSTER_PM_EXIT:
		अगर (enable_off_mode)
			pwrdms_restore_context();
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

/**
 * pwrdm_complete_init - set up the घातerकरोमुख्य layer
 *
 * Do whatever is necessary to initialize रेजिस्टरed घातerकरोमुख्यs and
 * घातerकरोमुख्य code.  Currently, this programs the next घातer state
 * क्रम each घातerकरोमुख्य to ON.  This prevents घातerकरोमुख्यs from
 * unexpectedly losing context or entering high wakeup latency modes
 * with non-घातer-management-enabled kernels.  Must be called after
 * pwrdm_रेजिस्टर_pwrdms().  Returns -EACCES अगर called beक्रमe
 * pwrdm_रेजिस्टर_pwrdms(), or 0 upon success.
 */
पूर्णांक pwrdm_complete_init(व्योम)
अणु
	काष्ठा घातerकरोमुख्य *temp_p;
	अटल काष्ठा notअगरier_block nb;

	अगर (list_empty(&pwrdm_list))
		वापस -EACCES;

	list_क्रम_each_entry(temp_p, &pwrdm_list, node)
		pwrdm_set_next_pwrst(temp_p, PWRDM_POWER_ON);

	/* Only AM43XX can lose pwrdm context during rtc-ddr suspend */
	अगर (soc_is_am43xx()) अणु
		nb.notअगरier_call = cpu_notअगरier;
		cpu_pm_रेजिस्टर_notअगरier(&nb);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pwrdm_lock - acquire a Linux spinlock on a घातerकरोमुख्य
 * @pwrdm: काष्ठा घातerकरोमुख्य * to lock
 *
 * Acquire the घातerकरोमुख्य spinlock on @pwrdm.  No वापस value.
 */
व्योम pwrdm_lock(काष्ठा घातerकरोमुख्य *pwrdm)
	__acquires(&pwrdm->_lock)
अणु
	spin_lock_irqsave(&pwrdm->_lock, pwrdm->_lock_flags);
पूर्ण

/**
 * pwrdm_unlock - release a Linux spinlock on a घातerकरोमुख्य
 * @pwrdm: काष्ठा घातerकरोमुख्य * to unlock
 *
 * Release the घातerकरोमुख्य spinlock on @pwrdm.  No वापस value.
 */
व्योम pwrdm_unlock(काष्ठा घातerकरोमुख्य *pwrdm)
	__releases(&pwrdm->_lock)
अणु
	spin_unlock_irqrestore(&pwrdm->_lock, pwrdm->_lock_flags);
पूर्ण

/**
 * pwrdm_lookup - look up a घातerकरोमुख्य by name, वापस a poपूर्णांकer
 * @name: name of घातerकरोमुख्य
 *
 * Find a रेजिस्टरed घातerकरोमुख्य by its name @name.  Returns a poपूर्णांकer
 * to the काष्ठा घातerकरोमुख्य अगर found, or शून्य otherwise.
 */
काष्ठा घातerकरोमुख्य *pwrdm_lookup(स्थिर अक्षर *name)
अणु
	काष्ठा घातerकरोमुख्य *pwrdm;

	अगर (!name)
		वापस शून्य;

	pwrdm = _pwrdm_lookup(name);

	वापस pwrdm;
पूर्ण

/**
 * pwrdm_क्रम_each - call function on each रेजिस्टरed घड़ीकरोमुख्य
 * @fn: callback function *
 *
 * Call the supplied function @fn क्रम each रेजिस्टरed घातerकरोमुख्य.
 * The callback function @fn can वापस anything but 0 to bail out
 * early from the iterator.  Returns the last वापस value of the
 * callback function, which should be 0 क्रम success or anything अन्यथा
 * to indicate failure; or -EINVAL अगर the function poपूर्णांकer is null.
 */
पूर्णांक pwrdm_क्रम_each(पूर्णांक (*fn)(काष्ठा घातerकरोमुख्य *pwrdm, व्योम *user),
		   व्योम *user)
अणु
	काष्ठा घातerकरोमुख्य *temp_pwrdm;
	पूर्णांक ret = 0;

	अगर (!fn)
		वापस -EINVAL;

	list_क्रम_each_entry(temp_pwrdm, &pwrdm_list, node) अणु
		ret = (*fn)(temp_pwrdm, user);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * pwrdm_add_clkdm - add a घड़ीकरोमुख्य to a घातerकरोमुख्य
 * @pwrdm: काष्ठा घातerकरोमुख्य * to add the घड़ीकरोमुख्य to
 * @clkdm: काष्ठा घड़ीकरोमुख्य * to associate with a घातerकरोमुख्य
 *
 * Associate the घड़ीकरोमुख्य @clkdm with a घातerकरोमुख्य @pwrdm.  This
 * enables the use of pwrdm_क्रम_each_clkdm().  Returns -EINVAL अगर
 * presented with invalid poपूर्णांकers; -ENOMEM अगर memory could not be allocated;
 * or 0 upon success.
 */
पूर्णांक pwrdm_add_clkdm(काष्ठा घातerकरोमुख्य *pwrdm, काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	पूर्णांक i;
	पूर्णांक ret = -EINVAL;

	अगर (!pwrdm || !clkdm)
		वापस -EINVAL;

	pr_debug("powerdomain: %s: associating clockdomain %s\n",
		 pwrdm->name, clkdm->name);

	क्रम (i = 0; i < PWRDM_MAX_CLKDMS; i++) अणु
		अगर (!pwrdm->pwrdm_clkdms[i])
			अवरोध;
#अगर_घोषित DEBUG
		अगर (pwrdm->pwrdm_clkdms[i] == clkdm) अणु
			ret = -EINVAL;
			जाओ pac_निकास;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	अगर (i == PWRDM_MAX_CLKDMS) अणु
		pr_debug("powerdomain: %s: increase PWRDM_MAX_CLKDMS for clkdm %s\n",
			 pwrdm->name, clkdm->name);
		WARN_ON(1);
		ret = -ENOMEM;
		जाओ pac_निकास;
	पूर्ण

	pwrdm->pwrdm_clkdms[i] = clkdm;

	ret = 0;

pac_निकास:
	वापस ret;
पूर्ण

/**
 * pwrdm_get_mem_bank_count - get number of memory banks in this घातerकरोमुख्य
 * @pwrdm: काष्ठा घातerकरोमुख्य *
 *
 * Return the number of controllable memory banks in घातerकरोमुख्य @pwrdm,
 * starting with 1.  Returns -EINVAL अगर the घातerकरोमुख्य poपूर्णांकer is null.
 */
पूर्णांक pwrdm_get_mem_bank_count(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	अगर (!pwrdm)
		वापस -EINVAL;

	वापस pwrdm->banks;
पूर्ण

/**
 * pwrdm_set_next_pwrst - set next घातerकरोमुख्य घातer state
 * @pwrdm: काष्ठा घातerकरोमुख्य * to set
 * @pwrst: one of the PWRDM_POWER_* macros
 *
 * Set the घातerकरोमुख्य @pwrdm's next घातer state to @pwrst.  The घातerकरोमुख्य
 * may not enter this state immediately अगर the preconditions क्रम this state
 * have not been satisfied.  Returns -EINVAL अगर the घातerकरोमुख्य poपूर्णांकer is
 * null or अगर the घातer state is invalid क्रम the घातerकरोmin, or वापसs 0
 * upon success.
 */
पूर्णांक pwrdm_set_next_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 pwrst)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!pwrdm)
		वापस -EINVAL;

	अगर (!(pwrdm->pwrsts & (1 << pwrst)))
		वापस -EINVAL;

	pr_debug("powerdomain: %s: setting next powerstate to %0x\n",
		 pwrdm->name, pwrst);

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_set_next_pwrst) अणु
		/* Trace the pwrdm desired target state */
		trace_घातer_करोमुख्य_target_rcuidle(pwrdm->name, pwrst,
						  raw_smp_processor_id());
		/* Program the pwrdm desired target state */
		ret = arch_pwrdm->pwrdm_set_next_pwrst(pwrdm, pwrst);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * pwrdm_पढ़ो_next_pwrst - get next घातerकरोमुख्य घातer state
 * @pwrdm: काष्ठा घातerकरोमुख्य * to get घातer state
 *
 * Return the घातerकरोमुख्य @pwrdm's next घातer state.  Returns -EINVAL
 * अगर the घातerकरोमुख्य poपूर्णांकer is null or वापसs the next घातer state
 * upon success.
 */
पूर्णांक pwrdm_पढ़ो_next_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!pwrdm)
		वापस -EINVAL;

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_पढ़ो_next_pwrst)
		ret = arch_pwrdm->pwrdm_पढ़ो_next_pwrst(pwrdm);

	वापस ret;
पूर्ण

/**
 * pwrdm_पढ़ो_pwrst - get current घातerकरोमुख्य घातer state
 * @pwrdm: काष्ठा घातerकरोमुख्य * to get घातer state
 *
 * Return the घातerकरोमुख्य @pwrdm's current घातer state.	Returns -EINVAL
 * अगर the घातerकरोमुख्य poपूर्णांकer is null or वापसs the current घातer state
 * upon success. Note that अगर the घातer करोमुख्य only supports the ON state
 * then just वापस ON as the current state.
 */
पूर्णांक pwrdm_पढ़ो_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!pwrdm)
		वापस -EINVAL;

	अगर (pwrdm->pwrsts == PWRSTS_ON)
		वापस PWRDM_POWER_ON;

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_पढ़ो_pwrst)
		ret = arch_pwrdm->pwrdm_पढ़ो_pwrst(pwrdm);

	वापस ret;
पूर्ण

/**
 * pwrdm_पढ़ो_prev_pwrst - get previous घातerकरोमुख्य घातer state
 * @pwrdm: काष्ठा घातerकरोमुख्य * to get previous घातer state
 *
 * Return the घातerकरोमुख्य @pwrdm's previous घातer state.  Returns -EINVAL
 * अगर the घातerकरोमुख्य poपूर्णांकer is null or वापसs the previous घातer state
 * upon success.
 */
पूर्णांक pwrdm_पढ़ो_prev_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!pwrdm)
		वापस -EINVAL;

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_पढ़ो_prev_pwrst)
		ret = arch_pwrdm->pwrdm_पढ़ो_prev_pwrst(pwrdm);

	वापस ret;
पूर्ण

/**
 * pwrdm_set_logic_retst - set घातerकरोमुख्य logic घातer state upon retention
 * @pwrdm: काष्ठा घातerकरोमुख्य * to set
 * @pwrst: one of the PWRDM_POWER_* macros
 *
 * Set the next घातer state @pwrst that the logic portion of the
 * घातerकरोमुख्य @pwrdm will enter when the घातerकरोमुख्य enters retention.
 * This will be either RETENTION or OFF, अगर supported.  Returns
 * -EINVAL अगर the घातerकरोमुख्य poपूर्णांकer is null or the target घातer
 * state is not not supported, or वापसs 0 upon success.
 */
पूर्णांक pwrdm_set_logic_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 pwrst)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!pwrdm)
		वापस -EINVAL;

	अगर (!(pwrdm->pwrsts_logic_ret & (1 << pwrst)))
		वापस -EINVAL;

	pr_debug("powerdomain: %s: setting next logic powerstate to %0x\n",
		 pwrdm->name, pwrst);

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_set_logic_retst)
		ret = arch_pwrdm->pwrdm_set_logic_retst(pwrdm, pwrst);

	वापस ret;
पूर्ण

/**
 * pwrdm_set_mem_onst - set memory घातer state जबतक घातerकरोमुख्य ON
 * @pwrdm: काष्ठा घातerकरोमुख्य * to set
 * @bank: memory bank number to set (0-3)
 * @pwrst: one of the PWRDM_POWER_* macros
 *
 * Set the next घातer state @pwrst that memory bank @bank of the
 * घातerकरोमुख्य @pwrdm will enter when the घातerकरोमुख्य enters the ON
 * state.  @bank will be a number from 0 to 3, and represents dअगरferent
 * types of memory, depending on the घातerकरोमुख्य.  Returns -EINVAL अगर
 * the घातerकरोमुख्य poपूर्णांकer is null or the target घातer state is not
 * not supported क्रम this memory bank, -EEXIST अगर the target memory
 * bank करोes not exist or is not controllable, or वापसs 0 upon
 * success.
 */
पूर्णांक pwrdm_set_mem_onst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank, u8 pwrst)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!pwrdm)
		वापस -EINVAL;

	अगर (pwrdm->banks < (bank + 1))
		वापस -EEXIST;

	अगर (!(pwrdm->pwrsts_mem_on[bank] & (1 << pwrst)))
		वापस -EINVAL;

	pr_debug("powerdomain: %s: setting next memory powerstate for bank %0x while pwrdm-ON to %0x\n",
		 pwrdm->name, bank, pwrst);

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_set_mem_onst)
		ret = arch_pwrdm->pwrdm_set_mem_onst(pwrdm, bank, pwrst);

	वापस ret;
पूर्ण

/**
 * pwrdm_set_mem_retst - set memory घातer state जबतक घातerकरोमुख्य in RET
 * @pwrdm: काष्ठा घातerकरोमुख्य * to set
 * @bank: memory bank number to set (0-3)
 * @pwrst: one of the PWRDM_POWER_* macros
 *
 * Set the next घातer state @pwrst that memory bank @bank of the
 * घातerकरोमुख्य @pwrdm will enter when the घातerकरोमुख्य enters the
 * RETENTION state.  Bank will be a number from 0 to 3, and represents
 * dअगरferent types of memory, depending on the घातerकरोमुख्य.  @pwrst
 * will be either RETENTION or OFF, अगर supported.  Returns -EINVAL अगर
 * the घातerकरोमुख्य poपूर्णांकer is null or the target घातer state is not
 * not supported क्रम this memory bank, -EEXIST अगर the target memory
 * bank करोes not exist or is not controllable, or वापसs 0 upon
 * success.
 */
पूर्णांक pwrdm_set_mem_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank, u8 pwrst)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!pwrdm)
		वापस -EINVAL;

	अगर (pwrdm->banks < (bank + 1))
		वापस -EEXIST;

	अगर (!(pwrdm->pwrsts_mem_ret[bank] & (1 << pwrst)))
		वापस -EINVAL;

	pr_debug("powerdomain: %s: setting next memory powerstate for bank %0x while pwrdm-RET to %0x\n",
		 pwrdm->name, bank, pwrst);

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_set_mem_retst)
		ret = arch_pwrdm->pwrdm_set_mem_retst(pwrdm, bank, pwrst);

	वापस ret;
पूर्ण

/**
 * pwrdm_पढ़ो_logic_pwrst - get current घातerकरोमुख्य logic retention घातer state
 * @pwrdm: काष्ठा घातerकरोमुख्य * to get current logic retention घातer state
 *
 * Return the घातer state that the logic portion of घातerकरोमुख्य @pwrdm
 * will enter when the घातerकरोमुख्य enters retention.  Returns -EINVAL
 * अगर the घातerकरोमुख्य poपूर्णांकer is null or वापसs the logic retention
 * घातer state upon success.
 */
पूर्णांक pwrdm_पढ़ो_logic_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!pwrdm)
		वापस -EINVAL;

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_पढ़ो_logic_pwrst)
		ret = arch_pwrdm->pwrdm_पढ़ो_logic_pwrst(pwrdm);

	वापस ret;
पूर्ण

/**
 * pwrdm_पढ़ो_prev_logic_pwrst - get previous घातerकरोमुख्य logic घातer state
 * @pwrdm: काष्ठा घातerकरोमुख्य * to get previous logic घातer state
 *
 * Return the घातerकरोमुख्य @pwrdm's previous logic घातer state.  Returns
 * -EINVAL अगर the घातerकरोमुख्य poपूर्णांकer is null or वापसs the previous
 * logic घातer state upon success.
 */
पूर्णांक pwrdm_पढ़ो_prev_logic_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!pwrdm)
		वापस -EINVAL;

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_पढ़ो_prev_logic_pwrst)
		ret = arch_pwrdm->pwrdm_पढ़ो_prev_logic_pwrst(pwrdm);

	वापस ret;
पूर्ण

/**
 * pwrdm_पढ़ो_logic_retst - get next घातerकरोमुख्य logic घातer state
 * @pwrdm: काष्ठा घातerकरोमुख्य * to get next logic घातer state
 *
 * Return the घातerकरोमुख्य pwrdm's logic घातer state.  Returns -EINVAL
 * अगर the घातerकरोमुख्य poपूर्णांकer is null or वापसs the next logic
 * घातer state upon success.
 */
पूर्णांक pwrdm_पढ़ो_logic_retst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!pwrdm)
		वापस -EINVAL;

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_पढ़ो_logic_retst)
		ret = arch_pwrdm->pwrdm_पढ़ो_logic_retst(pwrdm);

	वापस ret;
पूर्ण

/**
 * pwrdm_पढ़ो_mem_pwrst - get current memory bank घातer state
 * @pwrdm: काष्ठा घातerकरोमुख्य * to get current memory bank घातer state
 * @bank: memory bank number (0-3)
 *
 * Return the घातerकरोमुख्य @pwrdm's current memory घातer state क्रम bank
 * @bank.  Returns -EINVAL अगर the घातerकरोमुख्य poपूर्णांकer is null, -EEXIST अगर
 * the target memory bank करोes not exist or is not controllable, or
 * वापसs the current memory घातer state upon success.
 */
पूर्णांक pwrdm_पढ़ो_mem_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!pwrdm)
		वापस ret;

	अगर (pwrdm->banks < (bank + 1))
		वापस ret;

	अगर (pwrdm->flags & PWRDM_HAS_MPU_QUIRK)
		bank = 1;

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_पढ़ो_mem_pwrst)
		ret = arch_pwrdm->pwrdm_पढ़ो_mem_pwrst(pwrdm, bank);

	वापस ret;
पूर्ण

/**
 * pwrdm_पढ़ो_prev_mem_pwrst - get previous memory bank घातer state
 * @pwrdm: काष्ठा घातerकरोमुख्य * to get previous memory bank घातer state
 * @bank: memory bank number (0-3)
 *
 * Return the घातerकरोमुख्य @pwrdm's previous memory घातer state क्रम
 * bank @bank.  Returns -EINVAL अगर the घातerकरोमुख्य poपूर्णांकer is null,
 * -EEXIST अगर the target memory bank करोes not exist or is not
 * controllable, or वापसs the previous memory घातer state upon
 * success.
 */
पूर्णांक pwrdm_पढ़ो_prev_mem_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!pwrdm)
		वापस ret;

	अगर (pwrdm->banks < (bank + 1))
		वापस ret;

	अगर (pwrdm->flags & PWRDM_HAS_MPU_QUIRK)
		bank = 1;

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_पढ़ो_prev_mem_pwrst)
		ret = arch_pwrdm->pwrdm_पढ़ो_prev_mem_pwrst(pwrdm, bank);

	वापस ret;
पूर्ण

/**
 * pwrdm_पढ़ो_mem_retst - get next memory bank घातer state
 * @pwrdm: काष्ठा घातerकरोमुख्य * to get mext memory bank घातer state
 * @bank: memory bank number (0-3)
 *
 * Return the घातerकरोमुख्य pwrdm's next memory घातer state क्रम bank
 * x.  Returns -EINVAL अगर the घातerकरोमुख्य poपूर्णांकer is null, -EEXIST अगर
 * the target memory bank करोes not exist or is not controllable, or
 * वापसs the next memory घातer state upon success.
 */
पूर्णांक pwrdm_पढ़ो_mem_retst(काष्ठा घातerकरोमुख्य *pwrdm, u8 bank)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!pwrdm)
		वापस ret;

	अगर (pwrdm->banks < (bank + 1))
		वापस ret;

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_पढ़ो_mem_retst)
		ret = arch_pwrdm->pwrdm_पढ़ो_mem_retst(pwrdm, bank);

	वापस ret;
पूर्ण

/**
 * pwrdm_clear_all_prev_pwrst - clear previous घातerstate रेजिस्टर क्रम a pwrdm
 * @pwrdm: काष्ठा घातerकरोमुख्य * to clear
 *
 * Clear the घातerकरोमुख्य's previous घातer state रेजिस्टर @pwrdm.
 * Clears the entire रेजिस्टर, including logic and memory bank
 * previous घातer states.  Returns -EINVAL अगर the घातerकरोमुख्य poपूर्णांकer
 * is null, or वापसs 0 upon success.
 */
पूर्णांक pwrdm_clear_all_prev_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!pwrdm)
		वापस ret;

	/*
	 * XXX should get the घातerकरोमुख्य's current state here;
	 * warn & fail अगर it is not ON.
	 */

	pr_debug("powerdomain: %s: clearing previous power state reg\n",
		 pwrdm->name);

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_clear_all_prev_pwrst)
		ret = arch_pwrdm->pwrdm_clear_all_prev_pwrst(pwrdm);

	वापस ret;
पूर्ण

/**
 * pwrdm_enable_hdwr_sar - enable स्वतःmatic hardware SAR क्रम a pwrdm
 * @pwrdm: काष्ठा घातerकरोमुख्य *
 *
 * Enable स्वतःmatic context save-and-restore upon घातer state change
 * क्रम some devices in the घातerकरोमुख्य @pwrdm.  Warning: this only
 * affects a subset of devices in a घातerकरोमुख्य; check the TRM
 * बंदly.  Returns -EINVAL अगर the घातerकरोमुख्य poपूर्णांकer is null or अगर
 * the घातerकरोमुख्य करोes not support स्वतःmatic save-and-restore, or
 * वापसs 0 upon success.
 */
पूर्णांक pwrdm_enable_hdwr_sar(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!pwrdm)
		वापस ret;

	अगर (!(pwrdm->flags & PWRDM_HAS_HDWR_SAR))
		वापस ret;

	pr_debug("powerdomain: %s: setting SAVEANDRESTORE bit\n", pwrdm->name);

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_enable_hdwr_sar)
		ret = arch_pwrdm->pwrdm_enable_hdwr_sar(pwrdm);

	वापस ret;
पूर्ण

/**
 * pwrdm_disable_hdwr_sar - disable स्वतःmatic hardware SAR क्रम a pwrdm
 * @pwrdm: काष्ठा घातerकरोमुख्य *
 *
 * Disable स्वतःmatic context save-and-restore upon घातer state change
 * क्रम some devices in the घातerकरोमुख्य @pwrdm.  Warning: this only
 * affects a subset of devices in a घातerकरोमुख्य; check the TRM
 * बंदly.  Returns -EINVAL अगर the घातerकरोमुख्य poपूर्णांकer is null or अगर
 * the घातerकरोमुख्य करोes not support स्वतःmatic save-and-restore, or
 * वापसs 0 upon success.
 */
पूर्णांक pwrdm_disable_hdwr_sar(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (!pwrdm)
		वापस ret;

	अगर (!(pwrdm->flags & PWRDM_HAS_HDWR_SAR))
		वापस ret;

	pr_debug("powerdomain: %s: clearing SAVEANDRESTORE bit\n", pwrdm->name);

	अगर (arch_pwrdm && arch_pwrdm->pwrdm_disable_hdwr_sar)
		ret = arch_pwrdm->pwrdm_disable_hdwr_sar(pwrdm);

	वापस ret;
पूर्ण

/**
 * pwrdm_has_hdwr_sar - test whether घातerकरोमुख्य supports hardware SAR
 * @pwrdm: काष्ठा घातerकरोमुख्य *
 *
 * Returns 1 अगर घातerकरोमुख्य @pwrdm supports hardware save-and-restore
 * क्रम some devices, or 0 अगर it करोes not.
 */
bool pwrdm_has_hdwr_sar(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	वापस (pwrdm && pwrdm->flags & PWRDM_HAS_HDWR_SAR) ? 1 : 0;
पूर्ण

पूर्णांक pwrdm_state_चयन_nolock(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक ret;

	अगर (!pwrdm || !arch_pwrdm)
		वापस -EINVAL;

	ret = arch_pwrdm->pwrdm_रुको_transition(pwrdm);
	अगर (!ret)
		ret = _pwrdm_state_चयन(pwrdm, PWRDM_STATE_NOW);

	वापस ret;
पूर्ण

पूर्णांक __deprecated pwrdm_state_चयन(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक ret;

	pwrdm_lock(pwrdm);
	ret = pwrdm_state_चयन_nolock(pwrdm);
	pwrdm_unlock(pwrdm);

	वापस ret;
पूर्ण

पूर्णांक pwrdm_pre_transition(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	अगर (pwrdm)
		_pwrdm_pre_transition_cb(pwrdm, शून्य);
	अन्यथा
		pwrdm_क्रम_each(_pwrdm_pre_transition_cb, शून्य);

	वापस 0;
पूर्ण

पूर्णांक pwrdm_post_transition(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	अगर (pwrdm)
		_pwrdm_post_transition_cb(pwrdm, शून्य);
	अन्यथा
		pwrdm_क्रम_each(_pwrdm_post_transition_cb, शून्य);

	वापस 0;
पूर्ण

/**
 * pwrdm_get_valid_lp_state() - Find best match deep घातer state
 * @pwrdm:	घातer करोमुख्य क्रम which we want to find best match
 * @is_logic_state: Are we looking क्रम logic state match here? Should
 *		    be one of PWRDM_xxx macro values
 * @req_state:	requested घातer state
 *
 * Returns: बंदst match क्रम requested घातer state. शेष fallback
 * is RET क्रम logic state and ON क्रम घातer state.
 *
 * This करोes a search from the घातer करोमुख्य data looking क्रम the
 * बंदst valid घातer करोमुख्य state that the hardware can achieve.
 * PRCM definitions क्रम PWRSTCTRL allows us to program whatever
 * configuration we'd like, and PRCM will actually attempt such
 * a transition, however अगर the घातerकरोमुख्य करोes not actually support it,
 * we endup with a hung प्रणाली. The valid घातer करोमुख्य states are alपढ़ोy
 * available in our घातerकरोमुख्य data files. So this function tries to करो
 * the following:
 * a) find अगर we have an exact match to the request - no issues.
 * b) अन्यथा find अगर a deeper घातer state is possible.
 * c) failing which, it tries to find बंदst higher घातer state क्रम the
 * request.
 */
u8 pwrdm_get_valid_lp_state(काष्ठा घातerकरोमुख्य *pwrdm,
			    bool is_logic_state, u8 req_state)
अणु
	u8 pwrdm_states = is_logic_state ? pwrdm->pwrsts_logic_ret :
			pwrdm->pwrsts;
	/* For logic, ret is highest and others, ON is highest */
	u8 शेष_pwrst = is_logic_state ? PWRDM_POWER_RET : PWRDM_POWER_ON;
	u8 new_pwrst;
	bool found;

	/* If it is alपढ़ोy supported, nothing to search */
	अगर (pwrdm_states & BIT(req_state))
		वापस req_state;

	अगर (!req_state)
		जाओ up_search;

	/*
	 * So, we करोnt have a exact match
	 * Can we get a deeper घातer state match?
	 */
	new_pwrst = req_state - 1;
	found = true;
	जबतक (!(pwrdm_states & BIT(new_pwrst))) अणु
		/* No match even at OFF? Not available */
		अगर (new_pwrst == PWRDM_POWER_OFF) अणु
			found = false;
			अवरोध;
		पूर्ण
		new_pwrst--;
	पूर्ण

	अगर (found)
		जाओ करोne;

up_search:
	/* OK, no deeper ones, can we get a higher match? */
	new_pwrst = req_state + 1;
	जबतक (!(pwrdm_states & BIT(new_pwrst))) अणु
		अगर (new_pwrst > PWRDM_POWER_ON) अणु
			WARN(1, "powerdomain: %s: Fix max powerstate to ON\n",
			     pwrdm->name);
			वापस PWRDM_POWER_ON;
		पूर्ण

		अगर (new_pwrst == शेष_pwrst)
			अवरोध;
		new_pwrst++;
	पूर्ण
करोne:
	वापस new_pwrst;
पूर्ण

/**
 * omap_set_pwrdm_state - change a घातerकरोमुख्य's current घातer state
 * @pwrdm: काष्ठा घातerकरोमुख्य * to change the घातer state of
 * @pwrst: घातer state to change to
 *
 * Change the current hardware घातer state of the घातerकरोमुख्य
 * represented by @pwrdm to the घातer state represented by @pwrst.
 * Returns -EINVAL अगर @pwrdm is null or invalid or अगर the
 * घातerकरोमुख्य's current घातer state could not be पढ़ो, or वापसs 0
 * upon success or अगर @pwrdm करोes not support @pwrst or any
 * lower-घातer state.  XXX Should not वापस 0 अगर the @pwrdm करोes not
 * support @pwrst or any lower-घातer state: this should be an error.
 */
पूर्णांक omap_set_pwrdm_state(काष्ठा घातerकरोमुख्य *pwrdm, u8 pwrst)
अणु
	u8 next_pwrst, sleep_चयन;
	पूर्णांक curr_pwrst;
	पूर्णांक ret = 0;

	अगर (!pwrdm || IS_ERR(pwrdm))
		वापस -EINVAL;

	जबतक (!(pwrdm->pwrsts & (1 << pwrst))) अणु
		अगर (pwrst == PWRDM_POWER_OFF)
			वापस ret;
		pwrst--;
	पूर्ण

	pwrdm_lock(pwrdm);

	curr_pwrst = pwrdm_पढ़ो_pwrst(pwrdm);
	अगर (curr_pwrst < 0) अणु
		ret = -EINVAL;
		जाओ osps_out;
	पूर्ण

	next_pwrst = pwrdm_पढ़ो_next_pwrst(pwrdm);
	अगर (curr_pwrst == pwrst && next_pwrst == pwrst)
		जाओ osps_out;

	sleep_चयन = _pwrdm_save_clkdm_state_and_activate(pwrdm, curr_pwrst,
							    pwrst);

	ret = pwrdm_set_next_pwrst(pwrdm, pwrst);
	अगर (ret)
		pr_err("%s: unable to set power state of powerdomain: %s\n",
		       __func__, pwrdm->name);

	_pwrdm_restore_clkdm_state(pwrdm, sleep_चयन);

osps_out:
	pwrdm_unlock(pwrdm);

	वापस ret;
पूर्ण

/**
 * pwrdm_get_context_loss_count - get घातerकरोमुख्य's context loss count
 * @pwrdm: काष्ठा घातerकरोमुख्य * to रुको क्रम
 *
 * Context loss count is the sum of घातerकरोमुख्य off-mode counter, the
 * logic off counter and the per-bank memory off counter.  Returns negative
 * (and WARNs) upon error, otherwise, वापसs the context loss count.
 */
पूर्णांक pwrdm_get_context_loss_count(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक i, count;

	अगर (!pwrdm) अणु
		WARN(1, "powerdomain: %s: pwrdm is null\n", __func__);
		वापस -ENODEV;
	पूर्ण

	count = pwrdm->state_counter[PWRDM_POWER_OFF];
	count += pwrdm->ret_logic_off_counter;

	क्रम (i = 0; i < pwrdm->banks; i++)
		count += pwrdm->ret_mem_off_counter[i];

	/*
	 * Context loss count has to be a non-negative value. Clear the sign
	 * bit to get a value range from 0 to पूर्णांक_उच्च.
	 */
	count &= पूर्णांक_उच्च;

	pr_debug("powerdomain: %s: context loss count = %d\n",
		 pwrdm->name, count);

	वापस count;
पूर्ण

/**
 * pwrdm_can_ever_lose_context - can this घातerकरोमुख्य ever lose context?
 * @pwrdm: काष्ठा घातerकरोमुख्य *
 *
 * Given a काष्ठा घातerकरोमुख्य * @pwrdm, वापसs 1 अगर the घातerकरोमुख्य
 * can lose either memory or logic context or अगर @pwrdm is invalid, or
 * वापसs 0 otherwise.  This function is not concerned with how the
 * घातerकरोमुख्य रेजिस्टरs are programmed (i.e., to go off or not); it's
 * concerned with whether it's ever possible क्रम this घातerकरोमुख्य to
 * go off जबतक some other part of the chip is active.  This function
 * assumes that every घातerकरोमुख्य can go to either ON or INACTIVE.
 */
bool pwrdm_can_ever_lose_context(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	पूर्णांक i;

	अगर (!pwrdm) अणु
		pr_debug("powerdomain: %s: invalid powerdomain pointer\n",
			 __func__);
		वापस true;
	पूर्ण

	अगर (pwrdm->pwrsts & PWRSTS_OFF)
		वापस true;

	अगर (pwrdm->pwrsts & PWRSTS_RET) अणु
		अगर (pwrdm->pwrsts_logic_ret & PWRSTS_OFF)
			वापस true;

		क्रम (i = 0; i < pwrdm->banks; i++)
			अगर (pwrdm->pwrsts_mem_ret[i] & PWRSTS_OFF)
				वापस true;
	पूर्ण

	क्रम (i = 0; i < pwrdm->banks; i++)
		अगर (pwrdm->pwrsts_mem_on[i] & PWRSTS_OFF)
			वापस true;

	वापस false;
पूर्ण

/**
 * pwrdm_save_context - save घातerकरोमुख्य रेजिस्टरs
 *
 * Register state is going to be lost due to a suspend or hibernate
 * event. Save the घातerकरोमुख्य रेजिस्टरs.
 */
अटल पूर्णांक pwrdm_save_context(काष्ठा घातerकरोमुख्य *pwrdm, व्योम *unused)
अणु
	अगर (arch_pwrdm && arch_pwrdm->pwrdm_save_context)
		arch_pwrdm->pwrdm_save_context(pwrdm);
	वापस 0;
पूर्ण

/**
 * pwrdm_save_context - restore घातerकरोमुख्य रेजिस्टरs
 *
 * Restore घातerकरोमुख्य control रेजिस्टरs after a suspend or resume
 * event.
 */
अटल पूर्णांक pwrdm_restore_context(काष्ठा घातerकरोमुख्य *pwrdm, व्योम *unused)
अणु
	अगर (arch_pwrdm && arch_pwrdm->pwrdm_restore_context)
		arch_pwrdm->pwrdm_restore_context(pwrdm);
	वापस 0;
पूर्ण

अटल पूर्णांक pwrdm_lost_घातer(काष्ठा घातerकरोमुख्य *pwrdm, व्योम *unused)
अणु
	पूर्णांक state;

	/*
	 * Power has been lost across all घातerकरोमुख्यs, increment the
	 * counter.
	 */

	state = pwrdm_पढ़ो_pwrst(pwrdm);
	अगर (state != PWRDM_POWER_OFF) अणु
		pwrdm->state_counter[state]++;
		pwrdm->state_counter[PWRDM_POWER_OFF]++;
	पूर्ण
	pwrdm->state = state;

	वापस 0;
पूर्ण

व्योम pwrdms_save_context(व्योम)
अणु
	pwrdm_क्रम_each(pwrdm_save_context, शून्य);
पूर्ण

व्योम pwrdms_restore_context(व्योम)
अणु
	pwrdm_क्रम_each(pwrdm_restore_context, शून्य);
पूर्ण

व्योम pwrdms_lost_घातer(व्योम)
अणु
	pwrdm_क्रम_each(pwrdm_lost_घातer, शून्य);
पूर्ण
