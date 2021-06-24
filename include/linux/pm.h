<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  pm.h - Power management पूर्णांकerface
 *
 *  Copyright (C) 2000 Andrew Henroid
 */

#अगर_अघोषित _LINUX_PM_H
#घोषणा _LINUX_PM_H

#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/समयr.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/completion.h>

/*
 * Callbacks क्रम platक्रमm drivers to implement.
 */
बाह्य व्योम (*pm_घातer_off)(व्योम);
बाह्य व्योम (*pm_घातer_off_prepare)(व्योम);

काष्ठा device; /* we have a circular dep with device.h */
#अगर_घोषित CONFIG_VT_CONSOLE_SLEEP
बाह्य व्योम pm_vt_चयन_required(काष्ठा device *dev, bool required);
बाह्य व्योम pm_vt_चयन_unरेजिस्टर(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत व्योम pm_vt_चयन_required(काष्ठा device *dev, bool required)
अणु
पूर्ण
अटल अंतरभूत व्योम pm_vt_चयन_unरेजिस्टर(काष्ठा device *dev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_VT_CONSOLE_SLEEP */

/*
 * Device घातer management
 */


#अगर_घोषित CONFIG_PM
बाह्य स्थिर अक्षर घातer_group_name[];		/* = "power" */
#अन्यथा
#घोषणा घातer_group_name	शून्य
#पूर्ण_अगर

प्रकार काष्ठा pm_message अणु
	पूर्णांक event;
पूर्ण pm_message_t;

/**
 * काष्ठा dev_pm_ops - device PM callbacks.
 *
 * @prepare: The principal role of this callback is to prevent new children of
 *	the device from being रेजिस्टरed after it has वापसed (the driver's
 *	subप्रणाली and generally the rest of the kernel is supposed to prevent
 *	new calls to the probe method from being made too once @prepare() has
 *	succeeded).  If @prepare() detects a situation it cannot handle (e.g.
 *	registration of a child alपढ़ोy in progress), it may वापस -EAGAIN, so
 *	that the PM core can execute it once again (e.g. after a new child has
 *	been रेजिस्टरed) to recover from the race condition.
 *	This method is executed क्रम all kinds of suspend transitions and is
 *	followed by one of the suspend callbacks: @suspend(), @मुक्तze(), or
 *	@घातeroff().  If the transition is a suspend to memory or standby (that
 *	is, not related to hibernation), the वापस value of @prepare() may be
 *	used to indicate to the PM core to leave the device in runसमय suspend
 *	अगर applicable.  Namely, अगर @prepare() वापसs a positive number, the PM
 *	core will understand that as a declaration that the device appears to be
 *	runसमय-suspended and it may be left in that state during the entire
 *	transition and during the subsequent resume अगर all of its descendants
 *	are left in runसमय suspend too.  If that happens, @complete() will be
 *	executed directly after @prepare() and it must ensure the proper
 *	functioning of the device after the प्रणाली resume.
 *	The PM core executes subप्रणाली-level @prepare() क्रम all devices beक्रमe
 *	starting to invoke suspend callbacks क्रम any of them, so generally
 *	devices may be assumed to be functional or to respond to runसमय resume
 *	requests जबतक @prepare() is being executed.  However, device drivers
 *	may NOT assume anything about the availability of user space at that
 *	समय and it is NOT valid to request firmware from within @prepare()
 *	(it's too late to करो that).  It also is NOT valid to allocate
 *	substantial amounts of memory from @prepare() in the GFP_KERNEL mode.
 *	[To work around these limitations, drivers may रेजिस्टर suspend and
 *	hibernation notअगरiers to be executed beक्रमe the मुक्तzing of tasks.]
 *
 * @complete: Unकरो the changes made by @prepare().  This method is executed क्रम
 *	all kinds of resume transitions, following one of the resume callbacks:
 *	@resume(), @thaw(), @restore().  Also called अगर the state transition
 *	fails beक्रमe the driver's suspend callback: @suspend(), @मुक्तze() or
 *	@घातeroff(), can be executed (e.g. अगर the suspend callback fails क्रम one
 *	of the other devices that the PM core has unsuccessfully attempted to
 *	suspend earlier).
 *	The PM core executes subप्रणाली-level @complete() after it has executed
 *	the appropriate resume callbacks क्रम all devices.  If the corresponding
 *	@prepare() at the beginning of the suspend transition वापसed a
 *	positive number and the device was left in runसमय suspend (without
 *	executing any suspend and resume callbacks क्रम it), @complete() will be
 *	the only callback executed क्रम the device during resume.  In that हाल,
 *	@complete() must be prepared to करो whatever is necessary to ensure the
 *	proper functioning of the device after the प्रणाली resume.  To this end,
 *	@complete() can check the घातer.direct_complete flag of the device to
 *	learn whether (unset) or not (set) the previous suspend and resume
 *	callbacks have been executed क्रम it.
 *
 * @suspend: Executed beक्रमe putting the प्रणाली पूर्णांकo a sleep state in which the
 *	contents of मुख्य memory are preserved.  The exact action to perक्रमm
 *	depends on the device's subप्रणाली (PM करोमुख्य, device type, class or bus
 *	type), but generally the device must be quiescent after subप्रणाली-level
 *	@suspend() has वापसed, so that it करोesn't करो any I/O or DMA.
 *	Subप्रणाली-level @suspend() is executed क्रम all devices after invoking
 *	subप्रणाली-level @prepare() क्रम all of them.
 *
 * @suspend_late: Continue operations started by @suspend().  For a number of
 *	devices @suspend_late() may poपूर्णांक to the same callback routine as the
 *	runसमय suspend callback.
 *
 * @resume: Executed after waking the प्रणाली up from a sleep state in which the
 *	contents of मुख्य memory were preserved.  The exact action to perक्रमm
 *	depends on the device's subप्रणाली, but generally the driver is expected
 *	to start working again, responding to hardware events and software
 *	requests (the device itself may be left in a low-घातer state, रुकोing
 *	क्रम a runसमय resume to occur).  The state of the device at the समय its
 *	driver's @resume() callback is run depends on the platक्रमm and subप्रणाली
 *	the device beदीर्घs to.  On most platक्रमms, there are no restrictions on
 *	availability of resources like घड़ीs during @resume().
 *	Subप्रणाली-level @resume() is executed क्रम all devices after invoking
 *	subप्रणाली-level @resume_noirq() क्रम all of them.
 *
 * @resume_early: Prepare to execute @resume().  For a number of devices
 *	@resume_early() may poपूर्णांक to the same callback routine as the runसमय
 *	resume callback.
 *
 * @मुक्तze: Hibernation-specअगरic, executed beक्रमe creating a hibernation image.
 *	Analogous to @suspend(), but it should not enable the device to संकेत
 *	wakeup events or change its घातer state.  The majority of subप्रणालीs
 *	(with the notable exception of the PCI bus type) expect the driver-level
 *	@मुक्तze() to save the device settings in memory to be used by @restore()
 *	during the subsequent resume from hibernation.
 *	Subप्रणाली-level @मुक्तze() is executed क्रम all devices after invoking
 *	subप्रणाली-level @prepare() क्रम all of them.
 *
 * @मुक्तze_late: Continue operations started by @मुक्तze().  Analogous to
 *	@suspend_late(), but it should not enable the device to संकेत wakeup
 *	events or change its घातer state.
 *
 * @thaw: Hibernation-specअगरic, executed after creating a hibernation image OR
 *	अगर the creation of an image has failed.  Also executed after a failing
 *	attempt to restore the contents of मुख्य memory from such an image.
 *	Unकरो the changes made by the preceding @मुक्तze(), so the device can be
 *	operated in the same way as immediately beक्रमe the call to @मुक्तze().
 *	Subप्रणाली-level @thaw() is executed क्रम all devices after invoking
 *	subप्रणाली-level @thaw_noirq() क्रम all of them.  It also may be executed
 *	directly after @मुक्तze() in हाल of a transition error.
 *
 * @thaw_early: Prepare to execute @thaw().  Unकरो the changes made by the
 *	preceding @मुक्तze_late().
 *
 * @घातeroff: Hibernation-specअगरic, executed after saving a hibernation image.
 *	Analogous to @suspend(), but it need not save the device's settings in
 *	memory.
 *	Subप्रणाली-level @घातeroff() is executed क्रम all devices after invoking
 *	subप्रणाली-level @prepare() क्रम all of them.
 *
 * @घातeroff_late: Continue operations started by @घातeroff().  Analogous to
 *	@suspend_late(), but it need not save the device's settings in memory.
 *
 * @restore: Hibernation-specअगरic, executed after restoring the contents of मुख्य
 *	memory from a hibernation image, analogous to @resume().
 *
 * @restore_early: Prepare to execute @restore(), analogous to @resume_early().
 *
 * @suspend_noirq: Complete the actions started by @suspend().  Carry out any
 *	additional operations required क्रम suspending the device that might be
 *	racing with its driver's पूर्णांकerrupt handler, which is guaranteed not to
 *	run जबतक @suspend_noirq() is being executed.
 *	It generally is expected that the device will be in a low-घातer state
 *	(appropriate क्रम the target प्रणाली sleep state) after subप्रणाली-level
 *	@suspend_noirq() has वापसed successfully.  If the device can generate
 *	प्रणाली wakeup संकेतs and is enabled to wake up the प्रणाली, it should be
 *	configured to करो so at that समय.  However, depending on the platक्रमm
 *	and device's subप्रणाली, @suspend() or @suspend_late() may be allowed to
 *	put the device पूर्णांकo the low-घातer state and configure it to generate
 *	wakeup संकेतs, in which हाल it generally is not necessary to define
 *	@suspend_noirq().
 *
 * @resume_noirq: Prepare क्रम the execution of @resume() by carrying out any
 *	operations required क्रम resuming the device that might be racing with
 *	its driver's पूर्णांकerrupt handler, which is guaranteed not to run जबतक
 *	@resume_noirq() is being executed.
 *
 * @मुक्तze_noirq: Complete the actions started by @मुक्तze().  Carry out any
 *	additional operations required क्रम मुक्तzing the device that might be
 *	racing with its driver's पूर्णांकerrupt handler, which is guaranteed not to
 *	run जबतक @मुक्तze_noirq() is being executed.
 *	The घातer state of the device should not be changed by either @मुक्तze(),
 *	or @मुक्तze_late(), or @मुक्तze_noirq() and it should not be configured to
 *	संकेत प्रणाली wakeup by any of these callbacks.
 *
 * @thaw_noirq: Prepare क्रम the execution of @thaw() by carrying out any
 *	operations required क्रम thawing the device that might be racing with its
 *	driver's पूर्णांकerrupt handler, which is guaranteed not to run जबतक
 *	@thaw_noirq() is being executed.
 *
 * @घातeroff_noirq: Complete the actions started by @घातeroff().  Analogous to
 *	@suspend_noirq(), but it need not save the device's settings in memory.
 *
 * @restore_noirq: Prepare क्रम the execution of @restore() by carrying out any
 *	operations required क्रम thawing the device that might be racing with its
 *	driver's पूर्णांकerrupt handler, which is guaranteed not to run जबतक
 *	@restore_noirq() is being executed.  Analogous to @resume_noirq().
 *
 * @runसमय_suspend: Prepare the device क्रम a condition in which it won't be
 *	able to communicate with the CPU(s) and RAM due to घातer management.
 *	This need not mean that the device should be put पूर्णांकo a low-घातer state.
 *	For example, अगर the device is behind a link which is about to be turned
 *	off, the device may reमुख्य at full घातer.  If the device करोes go to low
 *	घातer and is capable of generating runसमय wakeup events, remote wakeup
 *	(i.e., a hardware mechanism allowing the device to request a change of
 *	its घातer state via an पूर्णांकerrupt) should be enabled क्रम it.
 *
 * @runसमय_resume: Put the device पूर्णांकo the fully active state in response to a
 *	wakeup event generated by hardware or at the request of software.  If
 *	necessary, put the device पूर्णांकo the full-घातer state and restore its
 *	रेजिस्टरs, so that it is fully operational.
 *
 * @runसमय_idle: Device appears to be inactive and it might be put पूर्णांकo a
 *	low-घातer state अगर all of the necessary conditions are satisfied.
 *	Check these conditions, and वापस 0 अगर it's appropriate to let the PM
 *	core queue a suspend request क्रम the device.
 *
 * Several device घातer state transitions are बाह्यally visible, affecting
 * the state of pending I/O queues and (क्रम drivers that touch hardware)
 * पूर्णांकerrupts, wakeups, DMA, and other hardware state.  There may also be
 * पूर्णांकernal transitions to various low-घातer modes which are transparent
 * to the rest of the driver stack (such as a driver that's ON gating off
 * घड़ीs which are not in active use).
 *
 * The बाह्यally visible transitions are handled with the help of callbacks
 * included in this काष्ठाure in such a way that, typically, two levels of
 * callbacks are involved.  First, the PM core executes callbacks provided by PM
 * करोमुख्यs, device types, classes and bus types.  They are the subप्रणाली-level
 * callbacks expected to execute callbacks provided by device drivers, although
 * they may choose not to करो that.  If the driver callbacks are executed, they
 * have to collaborate with the subप्रणाली-level callbacks to achieve the goals
 * appropriate क्रम the given प्रणाली transition, given transition phase and the
 * subप्रणाली the device beदीर्घs to.
 *
 * All of the above callbacks, except क्रम @complete(), वापस error codes.
 * However, the error codes वापसed by @resume(), @thaw(), @restore(),
 * @resume_noirq(), @thaw_noirq(), and @restore_noirq(), करो not cause the PM
 * core to पात the resume transition during which they are वापसed.  The
 * error codes वापसed in those हालs are only prपूर्णांकed to the प्रणाली logs क्रम
 * debugging purposes.  Still, it is recommended that drivers only वापस error
 * codes from their resume methods in हाल of an unrecoverable failure (i.e.
 * when the device being handled refuses to resume and becomes unusable) to
 * allow the PM core to be modअगरied in the future, so that it can aव्योम
 * attempting to handle devices that failed to resume and their children.
 *
 * It is allowed to unरेजिस्टर devices जबतक the above callbacks are being
 * executed.  However, a callback routine MUST NOT try to unरेजिस्टर the device
 * it was called क्रम, although it may unरेजिस्टर children of that device (क्रम
 * example, अगर it detects that a child was unplugged जबतक the प्रणाली was
 * asleep).
 *
 * There also are callbacks related to runसमय घातer management of devices.
 * Again, as a rule these callbacks are executed by the PM core क्रम subप्रणालीs
 * (PM करोमुख्यs, device types, classes and bus types) and the subप्रणाली-level
 * callbacks are expected to invoke the driver callbacks.  Moreover, the exact
 * actions to be perक्रमmed by a device driver's callbacks generally depend on
 * the platक्रमm and subप्रणाली the device beदीर्घs to.
 *
 * Refer to Documentation/घातer/runसमय_pm.rst क्रम more inक्रमmation about the
 * role of the @runसमय_suspend(), @runसमय_resume() and @runसमय_idle()
 * callbacks in device runसमय घातer management.
 */
काष्ठा dev_pm_ops अणु
	पूर्णांक (*prepare)(काष्ठा device *dev);
	व्योम (*complete)(काष्ठा device *dev);
	पूर्णांक (*suspend)(काष्ठा device *dev);
	पूर्णांक (*resume)(काष्ठा device *dev);
	पूर्णांक (*मुक्तze)(काष्ठा device *dev);
	पूर्णांक (*thaw)(काष्ठा device *dev);
	पूर्णांक (*घातeroff)(काष्ठा device *dev);
	पूर्णांक (*restore)(काष्ठा device *dev);
	पूर्णांक (*suspend_late)(काष्ठा device *dev);
	पूर्णांक (*resume_early)(काष्ठा device *dev);
	पूर्णांक (*मुक्तze_late)(काष्ठा device *dev);
	पूर्णांक (*thaw_early)(काष्ठा device *dev);
	पूर्णांक (*घातeroff_late)(काष्ठा device *dev);
	पूर्णांक (*restore_early)(काष्ठा device *dev);
	पूर्णांक (*suspend_noirq)(काष्ठा device *dev);
	पूर्णांक (*resume_noirq)(काष्ठा device *dev);
	पूर्णांक (*मुक्तze_noirq)(काष्ठा device *dev);
	पूर्णांक (*thaw_noirq)(काष्ठा device *dev);
	पूर्णांक (*घातeroff_noirq)(काष्ठा device *dev);
	पूर्णांक (*restore_noirq)(काष्ठा device *dev);
	पूर्णांक (*runसमय_suspend)(काष्ठा device *dev);
	पूर्णांक (*runसमय_resume)(काष्ठा device *dev);
	पूर्णांक (*runसमय_idle)(काष्ठा device *dev);
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
#घोषणा SET_SYSTEM_SLEEP_PM_OPS(suspend_fn, resume_fn) \
	.suspend = suspend_fn, \
	.resume = resume_fn, \
	.मुक्तze = suspend_fn, \
	.thaw = resume_fn, \
	.घातeroff = suspend_fn, \
	.restore = resume_fn,
#अन्यथा
#घोषणा SET_SYSTEM_SLEEP_PM_OPS(suspend_fn, resume_fn)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
#घोषणा SET_LATE_SYSTEM_SLEEP_PM_OPS(suspend_fn, resume_fn) \
	.suspend_late = suspend_fn, \
	.resume_early = resume_fn, \
	.मुक्तze_late = suspend_fn, \
	.thaw_early = resume_fn, \
	.घातeroff_late = suspend_fn, \
	.restore_early = resume_fn,
#अन्यथा
#घोषणा SET_LATE_SYSTEM_SLEEP_PM_OPS(suspend_fn, resume_fn)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
#घोषणा SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(suspend_fn, resume_fn) \
	.suspend_noirq = suspend_fn, \
	.resume_noirq = resume_fn, \
	.मुक्तze_noirq = suspend_fn, \
	.thaw_noirq = resume_fn, \
	.घातeroff_noirq = suspend_fn, \
	.restore_noirq = resume_fn,
#अन्यथा
#घोषणा SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(suspend_fn, resume_fn)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
#घोषणा SET_RUNTIME_PM_OPS(suspend_fn, resume_fn, idle_fn) \
	.runसमय_suspend = suspend_fn, \
	.runसमय_resume = resume_fn, \
	.runसमय_idle = idle_fn,
#अन्यथा
#घोषणा SET_RUNTIME_PM_OPS(suspend_fn, resume_fn, idle_fn)
#पूर्ण_अगर

/*
 * Use this अगर you want to use the same suspend and resume callbacks क्रम suspend
 * to RAM and hibernation.
 */
#घोषणा SIMPLE_DEV_PM_OPS(name, suspend_fn, resume_fn) \
स्थिर काष्ठा dev_pm_ops __maybe_unused name = अणु \
	SET_SYSTEM_SLEEP_PM_OPS(suspend_fn, resume_fn) \
पूर्ण

/*
 * Use this क्रम defining a set of PM operations to be used in all situations
 * (प्रणाली suspend, hibernation or runसमय PM).
 * NOTE: In general, प्रणाली suspend callbacks, .suspend() and .resume(), should
 * be dअगरferent from the corresponding runसमय PM callbacks, .runसमय_suspend(),
 * and .runसमय_resume(), because .runसमय_suspend() always works on an alपढ़ोy
 * quiescent device, जबतक .suspend() should assume that the device may be करोing
 * something when it is called (it should ensure that the device will be
 * quiescent after it has वापसed).  Thereक्रमe it's better to poपूर्णांक the "late"
 * suspend and "early" resume callback poपूर्णांकers, .suspend_late() and
 * .resume_early(), to the same routines as .runसमय_suspend() and
 * .runसमय_resume(), respectively (and analogously क्रम hibernation).
 */
#घोषणा UNIVERSAL_DEV_PM_OPS(name, suspend_fn, resume_fn, idle_fn) \
स्थिर काष्ठा dev_pm_ops __maybe_unused name = अणु \
	SET_SYSTEM_SLEEP_PM_OPS(suspend_fn, resume_fn) \
	SET_RUNTIME_PM_OPS(suspend_fn, resume_fn, idle_fn) \
पूर्ण

#अगर_घोषित CONFIG_PM
#घोषणा pm_ptr(_ptr) (_ptr)
#अन्यथा
#घोषणा pm_ptr(_ptr) शून्य
#पूर्ण_अगर

/*
 * PM_EVENT_ messages
 *
 * The following PM_EVENT_ messages are defined क्रम the पूर्णांकernal use of the PM
 * core, in order to provide a mechanism allowing the high level suspend and
 * hibernation code to convey the necessary inक्रमmation to the device PM core
 * code:
 *
 * ON		No transition.
 *
 * FREEZE	System is going to hibernate, call ->prepare() and ->मुक्तze()
 *		क्रम all devices.
 *
 * SUSPEND	System is going to suspend, call ->prepare() and ->suspend()
 *		क्रम all devices.
 *
 * HIBERNATE	Hibernation image has been saved, call ->prepare() and
 *		->घातeroff() क्रम all devices.
 *
 * QUIESCE	Contents of मुख्य memory are going to be restored from a (loaded)
 *		hibernation image, call ->prepare() and ->मुक्तze() क्रम all
 *		devices.
 *
 * RESUME	System is resuming, call ->resume() and ->complete() क्रम all
 *		devices.
 *
 * THAW		Hibernation image has been created, call ->thaw() and
 *		->complete() क्रम all devices.
 *
 * RESTORE	Contents of मुख्य memory have been restored from a hibernation
 *		image, call ->restore() and ->complete() क्रम all devices.
 *
 * RECOVER	Creation of a hibernation image or restoration of the मुख्य
 *		memory contents from a hibernation image has failed, call
 *		->thaw() and ->complete() क्रम all devices.
 *
 * The following PM_EVENT_ messages are defined क्रम पूर्णांकernal use by
 * kernel subप्रणालीs.  They are never issued by the PM core.
 *
 * USER_SUSPEND		Manual selective suspend was issued by userspace.
 *
 * USER_RESUME		Manual selective resume was issued by userspace.
 *
 * REMOTE_WAKEUP	Remote-wakeup request was received from the device.
 *
 * AUTO_SUSPEND		Automatic (device idle) runसमय suspend was
 *			initiated by the subप्रणाली.
 *
 * AUTO_RESUME		Automatic (device needed) runसमय resume was
 *			requested by a driver.
 */

#घोषणा PM_EVENT_INVALID	(-1)
#घोषणा PM_EVENT_ON		0x0000
#घोषणा PM_EVENT_FREEZE		0x0001
#घोषणा PM_EVENT_SUSPEND	0x0002
#घोषणा PM_EVENT_HIBERNATE	0x0004
#घोषणा PM_EVENT_QUIESCE	0x0008
#घोषणा PM_EVENT_RESUME		0x0010
#घोषणा PM_EVENT_THAW		0x0020
#घोषणा PM_EVENT_RESTORE	0x0040
#घोषणा PM_EVENT_RECOVER	0x0080
#घोषणा PM_EVENT_USER		0x0100
#घोषणा PM_EVENT_REMOTE		0x0200
#घोषणा PM_EVENT_AUTO		0x0400

#घोषणा PM_EVENT_SLEEP		(PM_EVENT_SUSPEND | PM_EVENT_HIBERNATE)
#घोषणा PM_EVENT_USER_SUSPEND	(PM_EVENT_USER | PM_EVENT_SUSPEND)
#घोषणा PM_EVENT_USER_RESUME	(PM_EVENT_USER | PM_EVENT_RESUME)
#घोषणा PM_EVENT_REMOTE_RESUME	(PM_EVENT_REMOTE | PM_EVENT_RESUME)
#घोषणा PM_EVENT_AUTO_SUSPEND	(PM_EVENT_AUTO | PM_EVENT_SUSPEND)
#घोषणा PM_EVENT_AUTO_RESUME	(PM_EVENT_AUTO | PM_EVENT_RESUME)

#घोषणा PMSG_INVALID	((काष्ठा pm_message)अणु .event = PM_EVENT_INVALID, पूर्ण)
#घोषणा PMSG_ON		((काष्ठा pm_message)अणु .event = PM_EVENT_ON, पूर्ण)
#घोषणा PMSG_FREEZE	((काष्ठा pm_message)अणु .event = PM_EVENT_FREEZE, पूर्ण)
#घोषणा PMSG_QUIESCE	((काष्ठा pm_message)अणु .event = PM_EVENT_QUIESCE, पूर्ण)
#घोषणा PMSG_SUSPEND	((काष्ठा pm_message)अणु .event = PM_EVENT_SUSPEND, पूर्ण)
#घोषणा PMSG_HIBERNATE	((काष्ठा pm_message)अणु .event = PM_EVENT_HIBERNATE, पूर्ण)
#घोषणा PMSG_RESUME	((काष्ठा pm_message)अणु .event = PM_EVENT_RESUME, पूर्ण)
#घोषणा PMSG_THAW	((काष्ठा pm_message)अणु .event = PM_EVENT_THAW, पूर्ण)
#घोषणा PMSG_RESTORE	((काष्ठा pm_message)अणु .event = PM_EVENT_RESTORE, पूर्ण)
#घोषणा PMSG_RECOVER	((काष्ठा pm_message)अणु .event = PM_EVENT_RECOVER, पूर्ण)
#घोषणा PMSG_USER_SUSPEND	((काष्ठा pm_message) \
					अणु .event = PM_EVENT_USER_SUSPEND, पूर्ण)
#घोषणा PMSG_USER_RESUME	((काष्ठा pm_message) \
					अणु .event = PM_EVENT_USER_RESUME, पूर्ण)
#घोषणा PMSG_REMOTE_RESUME	((काष्ठा pm_message) \
					अणु .event = PM_EVENT_REMOTE_RESUME, पूर्ण)
#घोषणा PMSG_AUTO_SUSPEND	((काष्ठा pm_message) \
					अणु .event = PM_EVENT_AUTO_SUSPEND, पूर्ण)
#घोषणा PMSG_AUTO_RESUME	((काष्ठा pm_message) \
					अणु .event = PM_EVENT_AUTO_RESUME, पूर्ण)

#घोषणा PMSG_IS_AUTO(msg)	(((msg).event & PM_EVENT_AUTO) != 0)

/*
 * Device run-समय घातer management status.
 *
 * These status labels are used पूर्णांकernally by the PM core to indicate the
 * current status of a device with respect to the PM core operations.  They करो
 * not reflect the actual घातer state of the device or its status as seen by the
 * driver.
 *
 * RPM_ACTIVE		Device is fully operational.  Indicates that the device
 *			bus type's ->runसमय_resume() callback has completed
 *			successfully.
 *
 * RPM_SUSPENDED	Device bus type's ->runसमय_suspend() callback has
 *			completed successfully.  The device is regarded as
 *			suspended.
 *
 * RPM_RESUMING		Device bus type's ->runसमय_resume() callback is being
 *			executed.
 *
 * RPM_SUSPENDING	Device bus type's ->runसमय_suspend() callback is being
 *			executed.
 */

क्रमागत rpm_status अणु
	RPM_ACTIVE = 0,
	RPM_RESUMING,
	RPM_SUSPENDED,
	RPM_SUSPENDING,
पूर्ण;

/*
 * Device run-समय घातer management request types.
 *
 * RPM_REQ_NONE		Do nothing.
 *
 * RPM_REQ_IDLE		Run the device bus type's ->runसमय_idle() callback
 *
 * RPM_REQ_SUSPEND	Run the device bus type's ->runसमय_suspend() callback
 *
 * RPM_REQ_AUTOSUSPEND	Same as RPM_REQ_SUSPEND, but not until the device has
 *			been inactive क्रम as दीर्घ as घातer.स्वतःsuspend_delay
 *
 * RPM_REQ_RESUME	Run the device bus type's ->runसमय_resume() callback
 */

क्रमागत rpm_request अणु
	RPM_REQ_NONE = 0,
	RPM_REQ_IDLE,
	RPM_REQ_SUSPEND,
	RPM_REQ_AUTOSUSPEND,
	RPM_REQ_RESUME,
पूर्ण;

काष्ठा wakeup_source;
काष्ठा wake_irq;
काष्ठा pm_करोमुख्य_data;

काष्ठा pm_subsys_data अणु
	spinlock_t lock;
	अचिन्हित पूर्णांक refcount;
#अगर_घोषित CONFIG_PM_CLK
	अचिन्हित पूर्णांक घड़ी_op_might_sleep;
	काष्ठा mutex घड़ी_mutex;
	काष्ठा list_head घड़ी_list;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PM_GENERIC_DOMAINS
	काष्ठा pm_करोमुख्य_data *करोमुख्य_data;
#पूर्ण_अगर
पूर्ण;

/*
 * Driver flags to control प्रणाली suspend/resume behavior.
 *
 * These flags can be set by device drivers at the probe समय.  They need not be
 * cleared by the drivers as the driver core will take care of that.
 *
 * NO_सूचीECT_COMPLETE: Do not apply direct-complete optimization to the device.
 * SMART_PREPARE: Take the driver ->prepare callback वापस value पूर्णांकo account.
 * SMART_SUSPEND: Aव्योम resuming the device from runसमय suspend.
 * MAY_SKIP_RESUME: Allow driver "noirq" and "early" callbacks to be skipped.
 *
 * See Documentation/driver-api/pm/devices.rst क्रम details.
 */
#घोषणा DPM_FLAG_NO_सूचीECT_COMPLETE	BIT(0)
#घोषणा DPM_FLAG_SMART_PREPARE		BIT(1)
#घोषणा DPM_FLAG_SMART_SUSPEND		BIT(2)
#घोषणा DPM_FLAG_MAY_SKIP_RESUME	BIT(3)

काष्ठा dev_pm_info अणु
	pm_message_t		घातer_state;
	अचिन्हित पूर्णांक		can_wakeup:1;
	अचिन्हित पूर्णांक		async_suspend:1;
	bool			in_dpm_list:1;	/* Owned by the PM core */
	bool			is_prepared:1;	/* Owned by the PM core */
	bool			is_suspended:1;	/* Ditto */
	bool			is_noirq_suspended:1;
	bool			is_late_suspended:1;
	bool			no_pm:1;
	bool			early_init:1;	/* Owned by the PM core */
	bool			direct_complete:1;	/* Owned by the PM core */
	u32			driver_flags;
	spinlock_t		lock;
#अगर_घोषित CONFIG_PM_SLEEP
	काष्ठा list_head	entry;
	काष्ठा completion	completion;
	काष्ठा wakeup_source	*wakeup;
	bool			wakeup_path:1;
	bool			syscore:1;
	bool			no_pm_callbacks:1;	/* Owned by the PM core */
	अचिन्हित पूर्णांक		must_resume:1;	/* Owned by the PM core */
	अचिन्हित पूर्णांक		may_skip_resume:1;	/* Set by subप्रणालीs */
#अन्यथा
	अचिन्हित पूर्णांक		should_wakeup:1;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PM
	काष्ठा hrसमयr		suspend_समयr;
	u64			समयr_expires;
	काष्ठा work_काष्ठा	work;
	रुको_queue_head_t	रुको_queue;
	काष्ठा wake_irq		*wakeirq;
	atomic_t		usage_count;
	atomic_t		child_count;
	अचिन्हित पूर्णांक		disable_depth:3;
	अचिन्हित पूर्णांक		idle_notअगरication:1;
	अचिन्हित पूर्णांक		request_pending:1;
	अचिन्हित पूर्णांक		deferred_resume:1;
	अचिन्हित पूर्णांक		needs_क्रमce_resume:1;
	अचिन्हित पूर्णांक		runसमय_स्वतः:1;
	bool			ignore_children:1;
	अचिन्हित पूर्णांक		no_callbacks:1;
	अचिन्हित पूर्णांक		irq_safe:1;
	अचिन्हित पूर्णांक		use_स्वतःsuspend:1;
	अचिन्हित पूर्णांक		समयr_स्वतःsuspends:1;
	अचिन्हित पूर्णांक		meदो_स्मृति_noio:1;
	अचिन्हित पूर्णांक		links_count;
	क्रमागत rpm_request	request;
	क्रमागत rpm_status		runसमय_status;
	पूर्णांक			runसमय_error;
	पूर्णांक			स्वतःsuspend_delay;
	u64			last_busy;
	u64			active_समय;
	u64			suspended_समय;
	u64			accounting_बारtamp;
#पूर्ण_अगर
	काष्ठा pm_subsys_data	*subsys_data;  /* Owned by the subप्रणाली. */
	व्योम (*set_latency_tolerance)(काष्ठा device *, s32);
	काष्ठा dev_pm_qos	*qos;
पूर्ण;

बाह्य पूर्णांक dev_pm_get_subsys_data(काष्ठा device *dev);
बाह्य व्योम dev_pm_put_subsys_data(काष्ठा device *dev);

/**
 * काष्ठा dev_pm_करोमुख्य - घातer management करोमुख्य representation.
 *
 * @ops: Power management operations associated with this करोमुख्य.
 * @start: Called when a user needs to start the device via the करोमुख्य.
 * @detach: Called when removing a device from the करोमुख्य.
 * @activate: Called beक्रमe executing probe routines क्रम bus types and drivers.
 * @sync: Called after successful driver probe.
 * @dismiss: Called after unsuccessful driver probe and after driver removal.
 *
 * Power करोमुख्यs provide callbacks that are executed during प्रणाली suspend,
 * hibernation, प्रणाली resume and during runसमय PM transitions instead of
 * subप्रणाली-level and driver-level callbacks.
 */
काष्ठा dev_pm_करोमुख्य अणु
	काष्ठा dev_pm_ops	ops;
	पूर्णांक (*start)(काष्ठा device *dev);
	व्योम (*detach)(काष्ठा device *dev, bool घातer_off);
	पूर्णांक (*activate)(काष्ठा device *dev);
	व्योम (*sync)(काष्ठा device *dev);
	व्योम (*dismiss)(काष्ठा device *dev);
पूर्ण;

/*
 * The PM_EVENT_ messages are also used by drivers implementing the legacy
 * suspend framework, based on the ->suspend() and ->resume() callbacks common
 * क्रम suspend and hibernation transitions, according to the rules below.
 */

/* Necessary, because several drivers use PM_EVENT_PRETHAW */
#घोषणा PM_EVENT_PRETHAW PM_EVENT_QUIESCE

/*
 * One transition is triggered by resume(), after a suspend() call; the
 * message is implicit:
 *
 * ON		Driver starts working again, responding to hardware events
 *		and software requests.  The hardware may have gone through
 *		a घातer-off reset, or it may have मुख्यtained state from the
 *		previous suspend() which the driver will rely on जबतक
 *		resuming.  On most platक्रमms, there are no restrictions on
 *		availability of resources like घड़ीs during resume().
 *
 * Other transitions are triggered by messages sent using suspend().  All
 * these transitions quiesce the driver, so that I/O queues are inactive.
 * That commonly entails turning off IRQs and DMA; there may be rules
 * about how to quiesce that are specअगरic to the bus or the device's type.
 * (For example, network drivers mark the link state.)  Other details may
 * dअगरfer according to the message:
 *
 * SUSPEND	Quiesce, enter a low घातer device state appropriate क्रम
 *		the upcoming प्रणाली state (such as PCI_D3hot), and enable
 *		wakeup events as appropriate.
 *
 * HIBERNATE	Enter a low घातer device state appropriate क्रम the hibernation
 *		state (eg. ACPI S4) and enable wakeup events as appropriate.
 *
 * FREEZE	Quiesce operations so that a consistent image can be saved;
 *		but करो NOT otherwise enter a low घातer device state, and करो
 *		NOT emit प्रणाली wakeup events.
 *
 * PRETHAW	Quiesce as अगर क्रम FREEZE; additionally, prepare क्रम restoring
 *		the प्रणाली from a snapshot taken after an earlier FREEZE.
 *		Some drivers will need to reset their hardware state instead
 *		of preserving it, to ensure that it's never mistaken क्रम the
 *		state which that earlier snapshot had set up.
 *
 * A minimally घातer-aware driver treats all messages as SUSPEND, fully
 * reinitializes its device during resume() -- whether or not it was reset
 * during the suspend/resume cycle -- and can't issue wakeup events.
 *
 * More घातer-aware drivers may also use low घातer states at runसमय as
 * well as during प्रणाली sleep states like PM_SUSPEND_STANDBY.  They may
 * be able to use wakeup events to निकास from runसमय low-घातer states,
 * or from प्रणाली low-घातer states such as standby or suspend-to-RAM.
 */

#अगर_घोषित CONFIG_PM_SLEEP
बाह्य व्योम device_pm_lock(व्योम);
बाह्य व्योम dpm_resume_start(pm_message_t state);
बाह्य व्योम dpm_resume_end(pm_message_t state);
बाह्य व्योम dpm_resume_noirq(pm_message_t state);
बाह्य व्योम dpm_resume_early(pm_message_t state);
बाह्य व्योम dpm_resume(pm_message_t state);
बाह्य व्योम dpm_complete(pm_message_t state);

बाह्य व्योम device_pm_unlock(व्योम);
बाह्य पूर्णांक dpm_suspend_end(pm_message_t state);
बाह्य पूर्णांक dpm_suspend_start(pm_message_t state);
बाह्य पूर्णांक dpm_suspend_noirq(pm_message_t state);
बाह्य पूर्णांक dpm_suspend_late(pm_message_t state);
बाह्य पूर्णांक dpm_suspend(pm_message_t state);
बाह्य पूर्णांक dpm_prepare(pm_message_t state);

बाह्य व्योम __suspend_report_result(स्थिर अक्षर *function, व्योम *fn, पूर्णांक ret);

#घोषणा suspend_report_result(fn, ret)					\
	करो अणु								\
		__suspend_report_result(__func__, fn, ret);		\
	पूर्ण जबतक (0)

बाह्य पूर्णांक device_pm_रुको_क्रम_dev(काष्ठा device *sub, काष्ठा device *dev);
बाह्य व्योम dpm_क्रम_each_dev(व्योम *data, व्योम (*fn)(काष्ठा device *, व्योम *));

बाह्य पूर्णांक pm_generic_prepare(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_suspend_late(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_suspend_noirq(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_suspend(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_resume_early(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_resume_noirq(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_resume(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_मुक्तze_noirq(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_मुक्तze_late(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_मुक्तze(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_thaw_noirq(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_thaw_early(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_thaw(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_restore_noirq(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_restore_early(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_restore(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_घातeroff_noirq(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_घातeroff_late(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_घातeroff(काष्ठा device *dev);
बाह्य व्योम pm_generic_complete(काष्ठा device *dev);

बाह्य bool dev_pm_skip_resume(काष्ठा device *dev);
बाह्य bool dev_pm_skip_suspend(काष्ठा device *dev);

#अन्यथा /* !CONFIG_PM_SLEEP */

#घोषणा device_pm_lock() करो अणुपूर्ण जबतक (0)
#घोषणा device_pm_unlock() करो अणुपूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक dpm_suspend_start(pm_message_t state)
अणु
	वापस 0;
पूर्ण

#घोषणा suspend_report_result(fn, ret)		करो अणुपूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक device_pm_रुको_क्रम_dev(काष्ठा device *a, काष्ठा device *b)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dpm_क्रम_each_dev(व्योम *data, व्योम (*fn)(काष्ठा device *, व्योम *))
अणु
पूर्ण

#घोषणा pm_generic_prepare		शून्य
#घोषणा pm_generic_suspend_late		शून्य
#घोषणा pm_generic_suspend_noirq	शून्य
#घोषणा pm_generic_suspend		शून्य
#घोषणा pm_generic_resume_early		शून्य
#घोषणा pm_generic_resume_noirq		शून्य
#घोषणा pm_generic_resume		शून्य
#घोषणा pm_generic_मुक्तze_noirq		शून्य
#घोषणा pm_generic_मुक्तze_late		शून्य
#घोषणा pm_generic_मुक्तze		शून्य
#घोषणा pm_generic_thaw_noirq		शून्य
#घोषणा pm_generic_thaw_early		शून्य
#घोषणा pm_generic_thaw			शून्य
#घोषणा pm_generic_restore_noirq	शून्य
#घोषणा pm_generic_restore_early	शून्य
#घोषणा pm_generic_restore		शून्य
#घोषणा pm_generic_घातeroff_noirq	शून्य
#घोषणा pm_generic_घातeroff_late	शून्य
#घोषणा pm_generic_घातeroff		शून्य
#घोषणा pm_generic_complete		शून्य
#पूर्ण_अगर /* !CONFIG_PM_SLEEP */

/* How to reorder dpm_list after device_move() */
क्रमागत dpm_order अणु
	DPM_ORDER_NONE,
	DPM_ORDER_DEV_AFTER_PARENT,
	DPM_ORDER_PARENT_BEFORE_DEV,
	DPM_ORDER_DEV_LAST,
पूर्ण;

#पूर्ण_अगर /* _LINUX_PM_H */
