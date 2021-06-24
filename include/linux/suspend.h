<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SUSPEND_H
#घोषणा _LINUX_SUSPEND_H

#समावेश <linux/swap.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/init.h>
#समावेश <linux/pm.h>
#समावेश <linux/mm.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <यंत्र/त्रुटिसं.स>

#अगर_घोषित CONFIG_VT
बाह्य व्योम pm_set_vt_चयन(पूर्णांक);
#अन्यथा
अटल अंतरभूत व्योम pm_set_vt_चयन(पूर्णांक करो_चयन)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_VT_CONSOLE_SLEEP
बाह्य व्योम pm_prepare_console(व्योम);
बाह्य व्योम pm_restore_console(व्योम);
#अन्यथा
अटल अंतरभूत व्योम pm_prepare_console(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम pm_restore_console(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

प्रकार पूर्णांक __bitwise suspend_state_t;

#घोषणा PM_SUSPEND_ON		((__क्रमce suspend_state_t) 0)
#घोषणा PM_SUSPEND_TO_IDLE	((__क्रमce suspend_state_t) 1)
#घोषणा PM_SUSPEND_STANDBY	((__क्रमce suspend_state_t) 2)
#घोषणा PM_SUSPEND_MEM		((__क्रमce suspend_state_t) 3)
#घोषणा PM_SUSPEND_MIN		PM_SUSPEND_TO_IDLE
#घोषणा PM_SUSPEND_MAX		((__क्रमce suspend_state_t) 4)

क्रमागत suspend_stat_step अणु
	SUSPEND_FREEZE = 1,
	SUSPEND_PREPARE,
	SUSPEND_SUSPEND,
	SUSPEND_SUSPEND_LATE,
	SUSPEND_SUSPEND_NOIRQ,
	SUSPEND_RESUME_NOIRQ,
	SUSPEND_RESUME_EARLY,
	SUSPEND_RESUME
पूर्ण;

काष्ठा suspend_stats अणु
	पूर्णांक	success;
	पूर्णांक	fail;
	पूर्णांक	failed_मुक्तze;
	पूर्णांक	failed_prepare;
	पूर्णांक	failed_suspend;
	पूर्णांक	failed_suspend_late;
	पूर्णांक	failed_suspend_noirq;
	पूर्णांक	failed_resume;
	पूर्णांक	failed_resume_early;
	पूर्णांक	failed_resume_noirq;
#घोषणा	REC_FAILED_NUM	2
	पूर्णांक	last_failed_dev;
	अक्षर	failed_devs[REC_FAILED_NUM][40];
	पूर्णांक	last_failed_त्रुटि_सं;
	पूर्णांक	त्रुटि_सं[REC_FAILED_NUM];
	पूर्णांक	last_failed_step;
	क्रमागत suspend_stat_step	failed_steps[REC_FAILED_NUM];
पूर्ण;

बाह्य काष्ठा suspend_stats suspend_stats;

अटल अंतरभूत व्योम dpm_save_failed_dev(स्थिर अक्षर *name)
अणु
	strlcpy(suspend_stats.failed_devs[suspend_stats.last_failed_dev],
		name,
		माप(suspend_stats.failed_devs[0]));
	suspend_stats.last_failed_dev++;
	suspend_stats.last_failed_dev %= REC_FAILED_NUM;
पूर्ण

अटल अंतरभूत व्योम dpm_save_failed_त्रुटि_सं(पूर्णांक err)
अणु
	suspend_stats.त्रुटि_सं[suspend_stats.last_failed_त्रुटि_सं] = err;
	suspend_stats.last_failed_त्रुटि_सं++;
	suspend_stats.last_failed_त्रुटि_सं %= REC_FAILED_NUM;
पूर्ण

अटल अंतरभूत व्योम dpm_save_failed_step(क्रमागत suspend_stat_step step)
अणु
	suspend_stats.failed_steps[suspend_stats.last_failed_step] = step;
	suspend_stats.last_failed_step++;
	suspend_stats.last_failed_step %= REC_FAILED_NUM;
पूर्ण

/**
 * काष्ठा platक्रमm_suspend_ops - Callbacks क्रम managing platक्रमm dependent
 *	प्रणाली sleep states.
 *
 * @valid: Callback to determine अगर given प्रणाली sleep state is supported by
 *	the platक्रमm.
 *	Valid (ie. supported) states are advertised in /sys/घातer/state.  Note
 *	that it still may be impossible to enter given प्रणाली sleep state अगर the
 *	conditions aren't right.
 *	There is the %suspend_valid_only_mem function available that can be
 *	asचिन्हित to this अगर the platक्रमm only supports mem sleep.
 *
 * @begin: Initialise a transition to given प्रणाली sleep state.
 *	@begin() is executed right prior to suspending devices.  The inक्रमmation
 *	conveyed to the platक्रमm code by @begin() should be disregarded by it as
 *	soon as @end() is executed.  If @begin() fails (ie. वापसs nonzero),
 *	@prepare(), @enter() and @finish() will not be called by the PM core.
 *	This callback is optional.  However, अगर it is implemented, the argument
 *	passed to @enter() is redundant and should be ignored.
 *
 * @prepare: Prepare the platक्रमm क्रम entering the प्रणाली sleep state indicated
 *	by @begin().
 *	@prepare() is called right after devices have been suspended (ie. the
 *	appropriate .suspend() method has been executed क्रम each device) and
 *	beक्रमe device drivers' late suspend callbacks are executed.  It वापसs
 *	0 on success or a negative error code otherwise, in which हाल the
 *	प्रणाली cannot enter the desired sleep state (@prepare_late(), @enter(),
 *	and @wake() will not be called in that हाल).
 *
 * @prepare_late: Finish preparing the platक्रमm क्रम entering the प्रणाली sleep
 *	state indicated by @begin().
 *	@prepare_late is called beक्रमe disabling nonboot CPUs and after
 *	device drivers' late suspend callbacks have been executed.  It वापसs
 *	0 on success or a negative error code otherwise, in which हाल the
 *	प्रणाली cannot enter the desired sleep state (@enter() will not be
 *	executed).
 *
 * @enter: Enter the प्रणाली sleep state indicated by @begin() or represented by
 *	the argument अगर @begin() is not implemented.
 *	This callback is mandatory.  It वापसs 0 on success or a negative
 *	error code otherwise, in which हाल the प्रणाली cannot enter the desired
 *	sleep state.
 *
 * @wake: Called when the प्रणाली has just left a sleep state, right after
 *	the nonboot CPUs have been enabled and beक्रमe device drivers' early
 *	resume callbacks are executed.
 *	This callback is optional, but should be implemented by the platक्रमms
 *	that implement @prepare_late().  If implemented, it is always called
 *	after @prepare_late and @enter(), even अगर one of them fails.
 *
 * @finish: Finish wake-up of the platक्रमm.
 *	@finish is called right prior to calling device drivers' regular suspend
 *	callbacks.
 *	This callback is optional, but should be implemented by the platक्रमms
 *	that implement @prepare().  If implemented, it is always called after
 *	@enter() and @wake(), even अगर any of them fails.  It is executed after
 *	a failing @prepare.
 *
 * @suspend_again: Returns whether the प्रणाली should suspend again (true) or
 *	not (false). If the platक्रमm wants to poll sensors or execute some
 *	code during suspended without invoking userspace and most of devices,
 *	suspend_again callback is the place assuming that periodic-wakeup or
 *	alarm-wakeup is alपढ़ोy setup. This allows to execute some codes जबतक
 *	being kept suspended in the view of userland and devices.
 *
 * @end: Called by the PM core right after resuming devices, to indicate to
 *	the platक्रमm that the प्रणाली has वापसed to the working state or
 *	the transition to the sleep state has been पातed.
 *	This callback is optional, but should be implemented by the platक्रमms
 *	that implement @begin().  Accordingly, platक्रमms implementing @begin()
 *	should also provide a @end() which cleans up transitions पातed beक्रमe
 *	@enter().
 *
 * @recover: Recover the platक्रमm from a suspend failure.
 *	Called by the PM core अगर the suspending of devices fails.
 *	This callback is optional and should only be implemented by platक्रमms
 *	which require special recovery actions in that situation.
 */
काष्ठा platक्रमm_suspend_ops अणु
	पूर्णांक (*valid)(suspend_state_t state);
	पूर्णांक (*begin)(suspend_state_t state);
	पूर्णांक (*prepare)(व्योम);
	पूर्णांक (*prepare_late)(व्योम);
	पूर्णांक (*enter)(suspend_state_t state);
	व्योम (*wake)(व्योम);
	व्योम (*finish)(व्योम);
	bool (*suspend_again)(व्योम);
	व्योम (*end)(व्योम);
	व्योम (*recover)(व्योम);
पूर्ण;

काष्ठा platक्रमm_s2idle_ops अणु
	पूर्णांक (*begin)(व्योम);
	पूर्णांक (*prepare)(व्योम);
	पूर्णांक (*prepare_late)(व्योम);
	bool (*wake)(व्योम);
	व्योम (*restore_early)(व्योम);
	व्योम (*restore)(व्योम);
	व्योम (*end)(व्योम);
पूर्ण;

#अगर_घोषित CONFIG_SUSPEND
बाह्य suspend_state_t mem_sleep_current;
बाह्य suspend_state_t mem_sleep_शेष;

/**
 * suspend_set_ops - set platक्रमm dependent suspend operations
 * @ops: The new suspend operations to set.
 */
बाह्य व्योम suspend_set_ops(स्थिर काष्ठा platक्रमm_suspend_ops *ops);
बाह्य पूर्णांक suspend_valid_only_mem(suspend_state_t state);

बाह्य अचिन्हित पूर्णांक pm_suspend_global_flags;

#घोषणा PM_SUSPEND_FLAG_FW_SUSPEND	BIT(0)
#घोषणा PM_SUSPEND_FLAG_FW_RESUME	BIT(1)
#घोषणा PM_SUSPEND_FLAG_NO_PLATFORM	BIT(2)

अटल अंतरभूत व्योम pm_suspend_clear_flags(व्योम)
अणु
	pm_suspend_global_flags = 0;
पूर्ण

अटल अंतरभूत व्योम pm_set_suspend_via_firmware(व्योम)
अणु
	pm_suspend_global_flags |= PM_SUSPEND_FLAG_FW_SUSPEND;
पूर्ण

अटल अंतरभूत व्योम pm_set_resume_via_firmware(व्योम)
अणु
	pm_suspend_global_flags |= PM_SUSPEND_FLAG_FW_RESUME;
पूर्ण

अटल अंतरभूत व्योम pm_set_suspend_no_platक्रमm(व्योम)
अणु
	pm_suspend_global_flags |= PM_SUSPEND_FLAG_NO_PLATFORM;
पूर्ण

/**
 * pm_suspend_via_firmware - Check अगर platक्रमm firmware will suspend the प्रणाली.
 *
 * To be called during प्रणाली-wide घातer management transitions to sleep states
 * or during the subsequent प्रणाली-wide transitions back to the working state.
 *
 * Return 'true' अगर the platक्रमm firmware is going to be invoked at the end of
 * the प्रणाली-wide घातer management transition (to a sleep state) in progress in
 * order to complete it, or अगर the platक्रमm firmware has been invoked in order
 * to complete the last (or preceding) transition of the प्रणाली to a sleep
 * state.
 *
 * This matters अगर the caller needs or wants to carry out some special actions
 * depending on whether or not control will be passed to the platक्रमm firmware
 * subsequently (क्रम example, the device may need to be reset beक्रमe letting the
 * platक्रमm firmware manipulate it, which is not necessary when the platक्रमm
 * firmware is not going to be invoked) or when such special actions may have
 * been carried out during the preceding transition of the प्रणाली to a sleep
 * state (as they may need to be taken पूर्णांकo account).
 */
अटल अंतरभूत bool pm_suspend_via_firmware(व्योम)
अणु
	वापस !!(pm_suspend_global_flags & PM_SUSPEND_FLAG_FW_SUSPEND);
पूर्ण

/**
 * pm_resume_via_firmware - Check अगर platक्रमm firmware has woken up the प्रणाली.
 *
 * To be called during प्रणाली-wide घातer management transitions from sleep
 * states.
 *
 * Return 'true' अगर the platक्रमm firmware has passed control to the kernel at
 * the beginning of the प्रणाली-wide घातer management transition in progress, so
 * the event that woke up the प्रणाली from sleep has been handled by the platक्रमm
 * firmware.
 */
अटल अंतरभूत bool pm_resume_via_firmware(व्योम)
अणु
	वापस !!(pm_suspend_global_flags & PM_SUSPEND_FLAG_FW_RESUME);
पूर्ण

/**
 * pm_suspend_no_platक्रमm - Check अगर platक्रमm may change device घातer states.
 *
 * To be called during प्रणाली-wide घातer management transitions to sleep states
 * or during the subsequent प्रणाली-wide transitions back to the working state.
 *
 * Return 'true' अगर the घातer states of devices reमुख्य under full control of the
 * kernel throughout the प्रणाली-wide suspend and resume cycle in progress (that
 * is, अगर a device is put पूर्णांकo a certain घातer state during suspend, it can be
 * expected to reमुख्य in that state during resume).
 */
अटल अंतरभूत bool pm_suspend_no_platक्रमm(व्योम)
अणु
	वापस !!(pm_suspend_global_flags & PM_SUSPEND_FLAG_NO_PLATFORM);
पूर्ण

/* Suspend-to-idle state machnine. */
क्रमागत s2idle_states अणु
	S2IDLE_STATE_NONE,      /* Not suspended/suspending. */
	S2IDLE_STATE_ENTER,     /* Enter suspend-to-idle. */
	S2IDLE_STATE_WAKE,      /* Wake up from suspend-to-idle. */
पूर्ण;

बाह्य क्रमागत s2idle_states __पढ़ो_mostly s2idle_state;

अटल अंतरभूत bool idle_should_enter_s2idle(व्योम)
अणु
	वापस unlikely(s2idle_state == S2IDLE_STATE_ENTER);
पूर्ण

बाह्य bool pm_suspend_शेष_s2idle(व्योम);
बाह्य व्योम __init pm_states_init(व्योम);
बाह्य व्योम s2idle_set_ops(स्थिर काष्ठा platक्रमm_s2idle_ops *ops);
बाह्य व्योम s2idle_wake(व्योम);

/**
 * arch_suspend_disable_irqs - disable IRQs क्रम suspend
 *
 * Disables IRQs (in the शेष हाल). This is a weak symbol in the common
 * code and thus allows architectures to override it अगर more needs to be
 * करोne. Not called क्रम suspend to disk.
 */
बाह्य व्योम arch_suspend_disable_irqs(व्योम);

/**
 * arch_suspend_enable_irqs - enable IRQs after suspend
 *
 * Enables IRQs (in the शेष हाल). This is a weak symbol in the common
 * code and thus allows architectures to override it अगर more needs to be
 * करोne. Not called क्रम suspend to disk.
 */
बाह्य व्योम arch_suspend_enable_irqs(व्योम);

बाह्य पूर्णांक pm_suspend(suspend_state_t state);
बाह्य bool sync_on_suspend_enabled;
#अन्यथा /* !CONFIG_SUSPEND */
#घोषणा suspend_valid_only_mem	शून्य

अटल अंतरभूत व्योम pm_suspend_clear_flags(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम pm_set_suspend_via_firmware(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम pm_set_resume_via_firmware(व्योम) अणुपूर्ण
अटल अंतरभूत bool pm_suspend_via_firmware(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool pm_resume_via_firmware(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool pm_suspend_no_platक्रमm(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool pm_suspend_शेष_s2idle(व्योम) अणु वापस false; पूर्ण

अटल अंतरभूत व्योम suspend_set_ops(स्थिर काष्ठा platक्रमm_suspend_ops *ops) अणुपूर्ण
अटल अंतरभूत पूर्णांक pm_suspend(suspend_state_t state) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत bool sync_on_suspend_enabled(व्योम) अणु वापस true; पूर्ण
अटल अंतरभूत bool idle_should_enter_s2idle(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम __init pm_states_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम s2idle_set_ops(स्थिर काष्ठा platक्रमm_s2idle_ops *ops) अणुपूर्ण
अटल अंतरभूत व्योम s2idle_wake(व्योम) अणुपूर्ण
#पूर्ण_अगर /* !CONFIG_SUSPEND */

/* काष्ठा pbe is used क्रम creating lists of pages that should be restored
 * atomically during the resume from disk, because the page frames they have
 * occupied beक्रमe the suspend are in use.
 */
काष्ठा pbe अणु
	व्योम *address;		/* address of the copy */
	व्योम *orig_address;	/* original address of a page */
	काष्ठा pbe *next;
पूर्ण;

/* mm/page_alloc.c */
बाह्य व्योम mark_मुक्त_pages(काष्ठा zone *zone);

/**
 * काष्ठा platक्रमm_hibernation_ops - hibernation platक्रमm support
 *
 * The methods in this काष्ठाure allow a platक्रमm to carry out special
 * operations required by it during a hibernation transition.
 *
 * All the methods below, except क्रम @recover(), must be implemented.
 *
 * @begin: Tell the platक्रमm driver that we're starting hibernation.
 *	Called right after shrinking memory and beक्रमe मुक्तzing devices.
 *
 * @end: Called by the PM core right after resuming devices, to indicate to
 *	the platक्रमm that the प्रणाली has वापसed to the working state.
 *
 * @pre_snapshot: Prepare the platक्रमm क्रम creating the hibernation image.
 *	Called right after devices have been frozen and beक्रमe the nonboot
 *	CPUs are disabled (runs with IRQs on).
 *
 * @finish: Restore the previous state of the platक्रमm after the hibernation
 *	image has been created *or* put the platक्रमm पूर्णांकo the normal operation
 *	mode after the hibernation (the same method is executed in both हालs).
 *	Called right after the nonboot CPUs have been enabled and beक्रमe
 *	thawing devices (runs with IRQs on).
 *
 * @prepare: Prepare the platक्रमm क्रम entering the low घातer state.
 *	Called right after the hibernation image has been saved and beक्रमe
 *	devices are prepared क्रम entering the low घातer state.
 *
 * @enter: Put the प्रणाली पूर्णांकo the low घातer state after the hibernation image
 *	has been saved to disk.
 *	Called after the nonboot CPUs have been disabled and all of the low
 *	level devices have been shut करोwn (runs with IRQs off).
 *
 * @leave: Perक्रमm the first stage of the cleanup after the प्रणाली sleep state
 *	indicated by @set_target() has been left.
 *	Called right after the control has been passed from the boot kernel to
 *	the image kernel, beक्रमe the nonboot CPUs are enabled and beक्रमe devices
 *	are resumed.  Executed with पूर्णांकerrupts disabled.
 *
 * @pre_restore: Prepare प्रणाली क्रम the restoration from a hibernation image.
 *	Called right after devices have been frozen and beक्रमe the nonboot
 *	CPUs are disabled (runs with IRQs on).
 *
 * @restore_cleanup: Clean up after a failing image restoration.
 *	Called right after the nonboot CPUs have been enabled and beक्रमe
 *	thawing devices (runs with IRQs on).
 *
 * @recover: Recover the platक्रमm from a failure to suspend devices.
 *	Called by the PM core अगर the suspending of devices during hibernation
 *	fails.  This callback is optional and should only be implemented by
 *	platक्रमms which require special recovery actions in that situation.
 */
काष्ठा platक्रमm_hibernation_ops अणु
	पूर्णांक (*begin)(pm_message_t stage);
	व्योम (*end)(व्योम);
	पूर्णांक (*pre_snapshot)(व्योम);
	व्योम (*finish)(व्योम);
	पूर्णांक (*prepare)(व्योम);
	पूर्णांक (*enter)(व्योम);
	व्योम (*leave)(व्योम);
	पूर्णांक (*pre_restore)(व्योम);
	व्योम (*restore_cleanup)(व्योम);
	व्योम (*recover)(व्योम);
पूर्ण;

#अगर_घोषित CONFIG_HIBERNATION
/* kernel/घातer/snapshot.c */
बाह्य व्योम __रेजिस्टर_nosave_region(अचिन्हित दीर्घ b, अचिन्हित दीर्घ e, पूर्णांक km);
अटल अंतरभूत व्योम __init रेजिस्टर_nosave_region(अचिन्हित दीर्घ b, अचिन्हित दीर्घ e)
अणु
	__रेजिस्टर_nosave_region(b, e, 0);
पूर्ण
अटल अंतरभूत व्योम __init रेजिस्टर_nosave_region_late(अचिन्हित दीर्घ b, अचिन्हित दीर्घ e)
अणु
	__रेजिस्टर_nosave_region(b, e, 1);
पूर्ण
बाह्य पूर्णांक swsusp_page_is_क्रमbidden(काष्ठा page *);
बाह्य व्योम swsusp_set_page_मुक्त(काष्ठा page *);
बाह्य व्योम swsusp_unset_page_मुक्त(काष्ठा page *);
बाह्य अचिन्हित दीर्घ get_safe_page(gfp_t gfp_mask);
बाह्य यंत्रlinkage पूर्णांक swsusp_arch_suspend(व्योम);
बाह्य यंत्रlinkage पूर्णांक swsusp_arch_resume(व्योम);

बाह्य व्योम hibernation_set_ops(स्थिर काष्ठा platक्रमm_hibernation_ops *ops);
बाह्य पूर्णांक hibernate(व्योम);
बाह्य bool प्रणाली_entering_hibernation(व्योम);
बाह्य bool hibernation_available(व्योम);
यंत्रlinkage पूर्णांक swsusp_save(व्योम);
बाह्य काष्ठा pbe *restore_pblist;
पूर्णांक pfn_is_nosave(अचिन्हित दीर्घ pfn);

पूर्णांक hibernate_quiet_exec(पूर्णांक (*func)(व्योम *data), व्योम *data);
#अन्यथा /* CONFIG_HIBERNATION */
अटल अंतरभूत व्योम रेजिस्टर_nosave_region(अचिन्हित दीर्घ b, अचिन्हित दीर्घ e) अणुपूर्ण
अटल अंतरभूत व्योम रेजिस्टर_nosave_region_late(अचिन्हित दीर्घ b, अचिन्हित दीर्घ e) अणुपूर्ण
अटल अंतरभूत पूर्णांक swsusp_page_is_क्रमbidden(काष्ठा page *p) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम swsusp_set_page_मुक्त(काष्ठा page *p) अणुपूर्ण
अटल अंतरभूत व्योम swsusp_unset_page_मुक्त(काष्ठा page *p) अणुपूर्ण

अटल अंतरभूत व्योम hibernation_set_ops(स्थिर काष्ठा platक्रमm_hibernation_ops *ops) अणुपूर्ण
अटल अंतरभूत पूर्णांक hibernate(व्योम) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत bool प्रणाली_entering_hibernation(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool hibernation_available(व्योम) अणु वापस false; पूर्ण

अटल अंतरभूत पूर्णांक hibernate_quiet_exec(पूर्णांक (*func)(व्योम *data), व्योम *data) अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर /* CONFIG_HIBERNATION */

#अगर_घोषित CONFIG_HIBERNATION_SNAPSHOT_DEV
पूर्णांक is_hibernate_resume_dev(dev_t dev);
#अन्यथा
अटल अंतरभूत पूर्णांक is_hibernate_resume_dev(dev_t dev) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/* Hibernation and suspend events */
#घोषणा PM_HIBERNATION_PREPARE	0x0001 /* Going to hibernate */
#घोषणा PM_POST_HIBERNATION	0x0002 /* Hibernation finished */
#घोषणा PM_SUSPEND_PREPARE	0x0003 /* Going to suspend the प्रणाली */
#घोषणा PM_POST_SUSPEND		0x0004 /* Suspend finished */
#घोषणा PM_RESTORE_PREPARE	0x0005 /* Going to restore a saved image */
#घोषणा PM_POST_RESTORE		0x0006 /* Restore failed */

बाह्य काष्ठा mutex प्रणाली_transition_mutex;

#अगर_घोषित CONFIG_PM_SLEEP
व्योम save_processor_state(व्योम);
व्योम restore_processor_state(व्योम);

/* kernel/घातer/मुख्य.c */
बाह्य पूर्णांक रेजिस्टर_pm_notअगरier(काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक unरेजिस्टर_pm_notअगरier(काष्ठा notअगरier_block *nb);
बाह्य व्योम ksys_sync_helper(व्योम);

#घोषणा pm_notअगरier(fn, pri) अणु				\
	अटल काष्ठा notअगरier_block fn##_nb =			\
		अणु .notअगरier_call = fn, .priority = pri पूर्ण;	\
	रेजिस्टर_pm_notअगरier(&fn##_nb);			\
पूर्ण

/* drivers/base/घातer/wakeup.c */
बाह्य bool events_check_enabled;
बाह्य अचिन्हित पूर्णांक pm_wakeup_irq;
बाह्य suspend_state_t pm_suspend_target_state;

बाह्य bool pm_wakeup_pending(व्योम);
बाह्य व्योम pm_प्रणाली_wakeup(व्योम);
बाह्य व्योम pm_प्रणाली_cancel_wakeup(व्योम);
बाह्य व्योम pm_wakeup_clear(bool reset);
बाह्य व्योम pm_प्रणाली_irq_wakeup(अचिन्हित पूर्णांक irq_number);
बाह्य bool pm_get_wakeup_count(अचिन्हित पूर्णांक *count, bool block);
बाह्य bool pm_save_wakeup_count(अचिन्हित पूर्णांक count);
बाह्य व्योम pm_wakep_स्वतःsleep_enabled(bool set);
बाह्य व्योम pm_prपूर्णांक_active_wakeup_sources(व्योम);

बाह्य व्योम lock_प्रणाली_sleep(व्योम);
बाह्य व्योम unlock_प्रणाली_sleep(व्योम);

#अन्यथा /* !CONFIG_PM_SLEEP */

अटल अंतरभूत पूर्णांक रेजिस्टर_pm_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक unरेजिस्टर_pm_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ksys_sync_helper(व्योम) अणुपूर्ण

#घोषणा pm_notअगरier(fn, pri)	करो अणु (व्योम)(fn); पूर्ण जबतक (0)

अटल अंतरभूत bool pm_wakeup_pending(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम pm_प्रणाली_wakeup(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम pm_wakeup_clear(bool reset) अणुपूर्ण
अटल अंतरभूत व्योम pm_प्रणाली_irq_wakeup(अचिन्हित पूर्णांक irq_number) अणुपूर्ण

अटल अंतरभूत व्योम lock_प्रणाली_sleep(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम unlock_प्रणाली_sleep(व्योम) अणुपूर्ण

#पूर्ण_अगर /* !CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM_SLEEP_DEBUG
बाह्य bool pm_prपूर्णांक_बार_enabled;
बाह्य bool pm_debug_messages_on;
बाह्य __म_लिखो(2, 3) व्योम __pm_pr_dbg(bool defer, स्थिर अक्षर *fmt, ...);
#अन्यथा
#घोषणा pm_prपूर्णांक_बार_enabled	(false)
#घोषणा pm_debug_messages_on	(false)

#समावेश <linux/prपूर्णांकk.h>

#घोषणा __pm_pr_dbg(defer, fmt, ...) \
	no_prपूर्णांकk(KERN_DEBUG fmt, ##__VA_ARGS__)
#पूर्ण_अगर

#घोषणा pm_pr_dbg(fmt, ...) \
	__pm_pr_dbg(false, fmt, ##__VA_ARGS__)

#घोषणा pm_deferred_pr_dbg(fmt, ...) \
	__pm_pr_dbg(true, fmt, ##__VA_ARGS__)

#अगर_घोषित CONFIG_PM_AUTOSLEEP

/* kernel/घातer/स्वतःsleep.c */
व्योम queue_up_suspend_work(व्योम);

#अन्यथा /* !CONFIG_PM_AUTOSLEEP */

अटल अंतरभूत व्योम queue_up_suspend_work(व्योम) अणुपूर्ण

#पूर्ण_अगर /* !CONFIG_PM_AUTOSLEEP */

#पूर्ण_अगर /* _LINUX_SUSPEND_H */
