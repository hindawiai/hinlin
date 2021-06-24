<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kernel/घातer/hibernate.c - Hibernation (a.k.a suspend-to-disk) support.
 *
 * Copyright (c) 2003 Patrick Mochel
 * Copyright (c) 2003 Open Source Development Lab
 * Copyright (c) 2004 Pavel Machek <pavel@ucw.cz>
 * Copyright (c) 2009 Rafael J. Wysocki, Novell Inc.
 * Copyright (C) 2012 Bojan Smojver <bojan@rexursive.com>
 */

#घोषणा pr_fmt(fmt) "PM: hibernation: " fmt

#समावेश <linux/export.h>
#समावेश <linux/suspend.h>
#समावेश <linux/reboot.h>
#समावेश <linux/माला.स>
#समावेश <linux/device.h>
#समावेश <linux/async.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/pm.h>
#समावेश <linux/nmi.h>
#समावेश <linux/console.h>
#समावेश <linux/cpu.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/gfp.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/genhd.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/security.h>
#समावेश <trace/events/घातer.h>

#समावेश "power.h"


अटल पूर्णांक nocompress;
अटल पूर्णांक noresume;
अटल पूर्णांक nohibernate;
अटल पूर्णांक resume_रुको;
अटल अचिन्हित पूर्णांक resume_delay;
अटल अक्षर resume_file[256] = CONFIG_PM_STD_PARTITION;
dev_t swsusp_resume_device;
sector_t swsusp_resume_block;
__visible पूर्णांक in_suspend __nosavedata;

क्रमागत अणु
	HIBERNATION_INVALID,
	HIBERNATION_PLATFORM,
	HIBERNATION_SHUTDOWN,
	HIBERNATION_REBOOT,
#अगर_घोषित CONFIG_SUSPEND
	HIBERNATION_SUSPEND,
#पूर्ण_अगर
	HIBERNATION_TEST_RESUME,
	/* keep last */
	__HIBERNATION_AFTER_LAST
पूर्ण;
#घोषणा HIBERNATION_MAX (__HIBERNATION_AFTER_LAST-1)
#घोषणा HIBERNATION_FIRST (HIBERNATION_INVALID + 1)

अटल पूर्णांक hibernation_mode = HIBERNATION_SHUTDOWN;

bool मुक्तzer_test_करोne;

अटल स्थिर काष्ठा platक्रमm_hibernation_ops *hibernation_ops;

अटल atomic_t hibernate_atomic = ATOMIC_INIT(1);

bool hibernate_acquire(व्योम)
अणु
	वापस atomic_add_unless(&hibernate_atomic, -1, 0);
पूर्ण

व्योम hibernate_release(व्योम)
अणु
	atomic_inc(&hibernate_atomic);
पूर्ण

bool hibernation_available(व्योम)
अणु
	वापस nohibernate == 0 && !security_locked_करोwn(LOCKDOWN_HIBERNATION);
पूर्ण

/**
 * hibernation_set_ops - Set the global hibernate operations.
 * @ops: Hibernation operations to use in subsequent hibernation transitions.
 */
व्योम hibernation_set_ops(स्थिर काष्ठा platक्रमm_hibernation_ops *ops)
अणु
	अगर (ops && !(ops->begin && ops->end &&  ops->pre_snapshot
	    && ops->prepare && ops->finish && ops->enter && ops->pre_restore
	    && ops->restore_cleanup && ops->leave)) अणु
		WARN_ON(1);
		वापस;
	पूर्ण
	lock_प्रणाली_sleep();
	hibernation_ops = ops;
	अगर (ops)
		hibernation_mode = HIBERNATION_PLATFORM;
	अन्यथा अगर (hibernation_mode == HIBERNATION_PLATFORM)
		hibernation_mode = HIBERNATION_SHUTDOWN;

	unlock_प्रणाली_sleep();
पूर्ण
EXPORT_SYMBOL_GPL(hibernation_set_ops);

अटल bool entering_platक्रमm_hibernation;

bool प्रणाली_entering_hibernation(व्योम)
अणु
	वापस entering_platक्रमm_hibernation;
पूर्ण
EXPORT_SYMBOL(प्रणाली_entering_hibernation);

#अगर_घोषित CONFIG_PM_DEBUG
अटल व्योम hibernation_debug_sleep(व्योम)
अणु
	pr_info("debug: Waiting for 5 seconds.\n");
	mdelay(5000);
पूर्ण

अटल पूर्णांक hibernation_test(पूर्णांक level)
अणु
	अगर (pm_test_level == level) अणु
		hibernation_debug_sleep();
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा /* !CONFIG_PM_DEBUG */
अटल पूर्णांक hibernation_test(पूर्णांक level) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* !CONFIG_PM_DEBUG */

/**
 * platक्रमm_begin - Call platक्रमm to start hibernation.
 * @platक्रमm_mode: Whether or not to use the platक्रमm driver.
 */
अटल पूर्णांक platक्रमm_begin(पूर्णांक platक्रमm_mode)
अणु
	वापस (platक्रमm_mode && hibernation_ops) ?
		hibernation_ops->begin(PMSG_FREEZE) : 0;
पूर्ण

/**
 * platक्रमm_end - Call platक्रमm to finish transition to the working state.
 * @platक्रमm_mode: Whether or not to use the platक्रमm driver.
 */
अटल व्योम platक्रमm_end(पूर्णांक platक्रमm_mode)
अणु
	अगर (platक्रमm_mode && hibernation_ops)
		hibernation_ops->end();
पूर्ण

/**
 * platक्रमm_pre_snapshot - Call platक्रमm to prepare the machine क्रम hibernation.
 * @platक्रमm_mode: Whether or not to use the platक्रमm driver.
 *
 * Use the platक्रमm driver to prepare the प्रणाली क्रम creating a hibernate image,
 * अगर so configured, and वापस an error code अगर that fails.
 */

अटल पूर्णांक platक्रमm_pre_snapshot(पूर्णांक platक्रमm_mode)
अणु
	वापस (platक्रमm_mode && hibernation_ops) ?
		hibernation_ops->pre_snapshot() : 0;
पूर्ण

/**
 * platक्रमm_leave - Call platक्रमm to prepare a transition to the working state.
 * @platक्रमm_mode: Whether or not to use the platक्रमm driver.
 *
 * Use the platक्रमm driver prepare to prepare the machine क्रम चयनing to the
 * normal mode of operation.
 *
 * This routine is called on one CPU with पूर्णांकerrupts disabled.
 */
अटल व्योम platक्रमm_leave(पूर्णांक platक्रमm_mode)
अणु
	अगर (platक्रमm_mode && hibernation_ops)
		hibernation_ops->leave();
पूर्ण

/**
 * platक्रमm_finish - Call platक्रमm to चयन the प्रणाली to the working state.
 * @platक्रमm_mode: Whether or not to use the platक्रमm driver.
 *
 * Use the platक्रमm driver to चयन the machine to the normal mode of
 * operation.
 *
 * This routine must be called after platक्रमm_prepare().
 */
अटल व्योम platक्रमm_finish(पूर्णांक platक्रमm_mode)
अणु
	अगर (platक्रमm_mode && hibernation_ops)
		hibernation_ops->finish();
पूर्ण

/**
 * platक्रमm_pre_restore - Prepare क्रम hibernate image restoration.
 * @platक्रमm_mode: Whether or not to use the platक्रमm driver.
 *
 * Use the platक्रमm driver to prepare the प्रणाली क्रम resume from a hibernation
 * image.
 *
 * If the restore fails after this function has been called,
 * platक्रमm_restore_cleanup() must be called.
 */
अटल पूर्णांक platक्रमm_pre_restore(पूर्णांक platक्रमm_mode)
अणु
	वापस (platक्रमm_mode && hibernation_ops) ?
		hibernation_ops->pre_restore() : 0;
पूर्ण

/**
 * platक्रमm_restore_cleanup - Switch to the working state after failing restore.
 * @platक्रमm_mode: Whether or not to use the platक्रमm driver.
 *
 * Use the platक्रमm driver to चयन the प्रणाली to the normal mode of operation
 * after a failing restore.
 *
 * If platक्रमm_pre_restore() has been called beक्रमe the failing restore, this
 * function must be called too, regardless of the result of
 * platक्रमm_pre_restore().
 */
अटल व्योम platक्रमm_restore_cleanup(पूर्णांक platक्रमm_mode)
अणु
	अगर (platक्रमm_mode && hibernation_ops)
		hibernation_ops->restore_cleanup();
पूर्ण

/**
 * platक्रमm_recover - Recover from a failure to suspend devices.
 * @platक्रमm_mode: Whether or not to use the platक्रमm driver.
 */
अटल व्योम platक्रमm_recover(पूर्णांक platक्रमm_mode)
अणु
	अगर (platक्रमm_mode && hibernation_ops && hibernation_ops->recover)
		hibernation_ops->recover();
पूर्ण

/**
 * swsusp_show_speed - Prपूर्णांक समय elapsed between two events during hibernation.
 * @start: Starting event.
 * @stop: Final event.
 * @nr_pages: Number of memory pages processed between @start and @stop.
 * @msg: Additional diagnostic message to prपूर्णांक.
 */
व्योम swsusp_show_speed(kसमय_प्रकार start, kसमय_प्रकार stop,
		      अचिन्हित nr_pages, अक्षर *msg)
अणु
	kसमय_प्रकार dअगरf;
	u64 elapsed_centisecs64;
	अचिन्हित पूर्णांक centisecs;
	अचिन्हित पूर्णांक k;
	अचिन्हित पूर्णांक kps;

	dअगरf = kसमय_sub(stop, start);
	elapsed_centisecs64 = kसमय_भागns(dअगरf, 10*NSEC_PER_MSEC);
	centisecs = elapsed_centisecs64;
	अगर (centisecs == 0)
		centisecs = 1;	/* aव्योम भाग-by-zero */
	k = nr_pages * (PAGE_SIZE / 1024);
	kps = (k * 100) / centisecs;
	pr_info("%s %u kbytes in %u.%02u seconds (%u.%02u MB/s)\n",
		msg, k, centisecs / 100, centisecs % 100, kps / 1000,
		(kps % 1000) / 10);
पूर्ण

__weak पूर्णांक arch_resume_nosmt(व्योम)
अणु
	वापस 0;
पूर्ण

/**
 * create_image - Create a hibernation image.
 * @platक्रमm_mode: Whether or not to use the platक्रमm driver.
 *
 * Execute device drivers' "late" and "noirq" मुक्तze callbacks, create a
 * hibernation image and run the drivers' "noirq" and "early" thaw callbacks.
 *
 * Control reappears in this routine after the subsequent restore.
 */
अटल पूर्णांक create_image(पूर्णांक platक्रमm_mode)
अणु
	पूर्णांक error;

	error = dpm_suspend_end(PMSG_FREEZE);
	अगर (error) अणु
		pr_err("Some devices failed to power down, aborting\n");
		वापस error;
	पूर्ण

	error = platक्रमm_pre_snapshot(platक्रमm_mode);
	अगर (error || hibernation_test(TEST_PLATFORM))
		जाओ Platक्रमm_finish;

	error = suspend_disable_secondary_cpus();
	अगर (error || hibernation_test(TEST_CPUS))
		जाओ Enable_cpus;

	local_irq_disable();

	प्रणाली_state = SYSTEM_SUSPEND;

	error = syscore_suspend();
	अगर (error) अणु
		pr_err("Some system devices failed to power down, aborting\n");
		जाओ Enable_irqs;
	पूर्ण

	अगर (hibernation_test(TEST_CORE) || pm_wakeup_pending())
		जाओ Power_up;

	in_suspend = 1;
	save_processor_state();
	trace_suspend_resume(TPS("machine_suspend"), PM_EVENT_HIBERNATE, true);
	error = swsusp_arch_suspend();
	/* Restore control flow magically appears here */
	restore_processor_state();
	trace_suspend_resume(TPS("machine_suspend"), PM_EVENT_HIBERNATE, false);
	अगर (error)
		pr_err("Error %d creating image\n", error);

	अगर (!in_suspend) अणु
		events_check_enabled = false;
		clear_or_poison_मुक्त_pages();
	पूर्ण

	platक्रमm_leave(platक्रमm_mode);

 Power_up:
	syscore_resume();

 Enable_irqs:
	प्रणाली_state = SYSTEM_RUNNING;
	local_irq_enable();

 Enable_cpus:
	suspend_enable_secondary_cpus();

	/* Allow architectures to करो nosmt-specअगरic post-resume dances */
	अगर (!in_suspend)
		error = arch_resume_nosmt();

 Platक्रमm_finish:
	platक्रमm_finish(platक्रमm_mode);

	dpm_resume_start(in_suspend ?
		(error ? PMSG_RECOVER : PMSG_THAW) : PMSG_RESTORE);

	वापस error;
पूर्ण

/**
 * hibernation_snapshot - Quiesce devices and create a hibernation image.
 * @platक्रमm_mode: If set, use platक्रमm driver to prepare क्रम the transition.
 *
 * This routine must be called with प्रणाली_transition_mutex held.
 */
पूर्णांक hibernation_snapshot(पूर्णांक platक्रमm_mode)
अणु
	pm_message_t msg;
	पूर्णांक error;

	pm_suspend_clear_flags();
	error = platक्रमm_begin(platक्रमm_mode);
	अगर (error)
		जाओ Close;

	/* Pपुनः_स्मृतिate image memory beक्रमe shutting करोwn devices. */
	error = hibernate_pपुनः_स्मृतिate_memory();
	अगर (error)
		जाओ Close;

	error = मुक्तze_kernel_thपढ़ोs();
	अगर (error)
		जाओ Cleanup;

	अगर (hibernation_test(TEST_FREEZER)) अणु

		/*
		 * Indicate to the caller that we are वापसing due to a
		 * successful मुक्तzer test.
		 */
		मुक्तzer_test_करोne = true;
		जाओ Thaw;
	पूर्ण

	error = dpm_prepare(PMSG_FREEZE);
	अगर (error) अणु
		dpm_complete(PMSG_RECOVER);
		जाओ Thaw;
	पूर्ण

	suspend_console();
	pm_restrict_gfp_mask();

	error = dpm_suspend(PMSG_FREEZE);

	अगर (error || hibernation_test(TEST_DEVICES))
		platक्रमm_recover(platक्रमm_mode);
	अन्यथा
		error = create_image(platक्रमm_mode);

	/*
	 * In the हाल that we call create_image() above, the control
	 * वापसs here (1) after the image has been created or the
	 * image creation has failed and (2) after a successful restore.
	 */

	/* We may need to release the pपुनः_स्मृतिated image pages here. */
	अगर (error || !in_suspend)
		swsusp_मुक्त();

	msg = in_suspend ? (error ? PMSG_RECOVER : PMSG_THAW) : PMSG_RESTORE;
	dpm_resume(msg);

	अगर (error || !in_suspend)
		pm_restore_gfp_mask();

	resume_console();
	dpm_complete(msg);

 Close:
	platक्रमm_end(platक्रमm_mode);
	वापस error;

 Thaw:
	thaw_kernel_thपढ़ोs();
 Cleanup:
	swsusp_मुक्त();
	जाओ Close;
पूर्ण

पूर्णांक __weak hibernate_resume_nonboot_cpu_disable(व्योम)
अणु
	वापस suspend_disable_secondary_cpus();
पूर्ण

/**
 * resume_target_kernel - Restore प्रणाली state from a hibernation image.
 * @platक्रमm_mode: Whether or not to use the platक्रमm driver.
 *
 * Execute device drivers' "noirq" and "late" मुक्तze callbacks, restore the
 * contents of highmem that have not been restored yet from the image and run
 * the low-level code that will restore the reमुख्यing contents of memory and
 * चयन to the just restored target kernel.
 */
अटल पूर्णांक resume_target_kernel(bool platक्रमm_mode)
अणु
	पूर्णांक error;

	error = dpm_suspend_end(PMSG_QUIESCE);
	अगर (error) अणु
		pr_err("Some devices failed to power down, aborting resume\n");
		वापस error;
	पूर्ण

	error = platक्रमm_pre_restore(platक्रमm_mode);
	अगर (error)
		जाओ Cleanup;

	error = hibernate_resume_nonboot_cpu_disable();
	अगर (error)
		जाओ Enable_cpus;

	local_irq_disable();
	प्रणाली_state = SYSTEM_SUSPEND;

	error = syscore_suspend();
	अगर (error)
		जाओ Enable_irqs;

	save_processor_state();
	error = restore_highmem();
	अगर (!error) अणु
		error = swsusp_arch_resume();
		/*
		 * The code below is only ever reached in हाल of a failure.
		 * Otherwise, execution जारीs at the place where
		 * swsusp_arch_suspend() was called.
		 */
		BUG_ON(!error);
		/*
		 * This call to restore_highmem() reverts the changes made by
		 * the previous one.
		 */
		restore_highmem();
	पूर्ण
	/*
	 * The only reason why swsusp_arch_resume() can fail is memory being
	 * very tight, so we have to मुक्त it as soon as we can to aव्योम
	 * subsequent failures.
	 */
	swsusp_मुक्त();
	restore_processor_state();
	touch_softlockup_watchकरोg();

	syscore_resume();

 Enable_irqs:
	प्रणाली_state = SYSTEM_RUNNING;
	local_irq_enable();

 Enable_cpus:
	suspend_enable_secondary_cpus();

 Cleanup:
	platक्रमm_restore_cleanup(platक्रमm_mode);

	dpm_resume_start(PMSG_RECOVER);

	वापस error;
पूर्ण

/**
 * hibernation_restore - Quiesce devices and restore from a hibernation image.
 * @platक्रमm_mode: If set, use platक्रमm driver to prepare क्रम the transition.
 *
 * This routine must be called with प्रणाली_transition_mutex held.  If it is
 * successful, control reappears in the restored target kernel in
 * hibernation_snapshot().
 */
पूर्णांक hibernation_restore(पूर्णांक platक्रमm_mode)
अणु
	पूर्णांक error;

	pm_prepare_console();
	suspend_console();
	pm_restrict_gfp_mask();
	error = dpm_suspend_start(PMSG_QUIESCE);
	अगर (!error) अणु
		error = resume_target_kernel(platक्रमm_mode);
		/*
		 * The above should either succeed and jump to the new kernel,
		 * or वापस with an error. Otherwise things are just
		 * undefined, so let's be paranoid.
		 */
		BUG_ON(!error);
	पूर्ण
	dpm_resume_end(PMSG_RECOVER);
	pm_restore_gfp_mask();
	resume_console();
	pm_restore_console();
	वापस error;
पूर्ण

/**
 * hibernation_platक्रमm_enter - Power off the प्रणाली using the platक्रमm driver.
 */
पूर्णांक hibernation_platक्रमm_enter(व्योम)
अणु
	पूर्णांक error;

	अगर (!hibernation_ops)
		वापस -ENOSYS;

	/*
	 * We have cancelled the घातer transition by running
	 * hibernation_ops->finish() beक्रमe saving the image, so we should let
	 * the firmware know that we're going to enter the sleep state after all
	 */
	error = hibernation_ops->begin(PMSG_HIBERNATE);
	अगर (error)
		जाओ Close;

	entering_platक्रमm_hibernation = true;
	suspend_console();
	error = dpm_suspend_start(PMSG_HIBERNATE);
	अगर (error) अणु
		अगर (hibernation_ops->recover)
			hibernation_ops->recover();
		जाओ Resume_devices;
	पूर्ण

	error = dpm_suspend_end(PMSG_HIBERNATE);
	अगर (error)
		जाओ Resume_devices;

	error = hibernation_ops->prepare();
	अगर (error)
		जाओ Platक्रमm_finish;

	error = suspend_disable_secondary_cpus();
	अगर (error)
		जाओ Enable_cpus;

	local_irq_disable();
	प्रणाली_state = SYSTEM_SUSPEND;
	syscore_suspend();
	अगर (pm_wakeup_pending()) अणु
		error = -EAGAIN;
		जाओ Power_up;
	पूर्ण

	hibernation_ops->enter();
	/* We should never get here */
	जबतक (1);

 Power_up:
	syscore_resume();
	प्रणाली_state = SYSTEM_RUNNING;
	local_irq_enable();

 Enable_cpus:
	suspend_enable_secondary_cpus();

 Platक्रमm_finish:
	hibernation_ops->finish();

	dpm_resume_start(PMSG_RESTORE);

 Resume_devices:
	entering_platक्रमm_hibernation = false;
	dpm_resume_end(PMSG_RESTORE);
	resume_console();

 Close:
	hibernation_ops->end();

	वापस error;
पूर्ण

/**
 * घातer_करोwn - Shut the machine करोwn क्रम hibernation.
 *
 * Use the platक्रमm driver, अगर configured, to put the प्रणाली पूर्णांकo the sleep
 * state corresponding to hibernation, or try to घातer it off or reboot,
 * depending on the value of hibernation_mode.
 */
अटल व्योम घातer_करोwn(व्योम)
अणु
#अगर_घोषित CONFIG_SUSPEND
	पूर्णांक error;

	अगर (hibernation_mode == HIBERNATION_SUSPEND) अणु
		error = suspend_devices_and_enter(PM_SUSPEND_MEM);
		अगर (error) अणु
			hibernation_mode = hibernation_ops ?
						HIBERNATION_PLATFORM :
						HIBERNATION_SHUTDOWN;
		पूर्ण अन्यथा अणु
			/* Restore swap signature. */
			error = swsusp_unmark();
			अगर (error)
				pr_err("Swap will be unusable! Try swapon -a.\n");

			वापस;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	चयन (hibernation_mode) अणु
	हाल HIBERNATION_REBOOT:
		kernel_restart(शून्य);
		अवरोध;
	हाल HIBERNATION_PLATFORM:
		hibernation_platक्रमm_enter();
		fallthrough;
	हाल HIBERNATION_SHUTDOWN:
		अगर (pm_घातer_off)
			kernel_घातer_off();
		अवरोध;
	पूर्ण
	kernel_halt();
	/*
	 * Valid image is on the disk, अगर we जारी we risk serious data
	 * corruption after resume.
	 */
	pr_crit("Power down manually\n");
	जबतक (1)
		cpu_relax();
पूर्ण

अटल पूर्णांक load_image_and_restore(व्योम)
अणु
	पूर्णांक error;
	अचिन्हित पूर्णांक flags;

	pm_pr_dbg("Loading hibernation image.\n");

	lock_device_hotplug();
	error = create_basic_memory_biपंचांगaps();
	अगर (error)
		जाओ Unlock;

	error = swsusp_पढ़ो(&flags);
	swsusp_बंद(FMODE_READ);
	अगर (!error)
		error = hibernation_restore(flags & SF_PLATFORM_MODE);

	pr_err("Failed to load image, recovering.\n");
	swsusp_मुक्त();
	मुक्त_basic_memory_biपंचांगaps();
 Unlock:
	unlock_device_hotplug();

	वापस error;
पूर्ण

/**
 * hibernate - Carry out प्रणाली hibernation, including saving the image.
 */
पूर्णांक hibernate(व्योम)
अणु
	bool snapshot_test = false;
	पूर्णांक error;

	अगर (!hibernation_available()) अणु
		pm_pr_dbg("Hibernation not available.\n");
		वापस -EPERM;
	पूर्ण

	lock_प्रणाली_sleep();
	/* The snapshot device should not be खोलोed जबतक we're running */
	अगर (!hibernate_acquire()) अणु
		error = -EBUSY;
		जाओ Unlock;
	पूर्ण

	pr_info("hibernation entry\n");
	pm_prepare_console();
	error = pm_notअगरier_call_chain_robust(PM_HIBERNATION_PREPARE, PM_POST_HIBERNATION);
	अगर (error)
		जाओ Restore;

	ksys_sync_helper();

	error = मुक्तze_processes();
	अगर (error)
		जाओ Exit;

	lock_device_hotplug();
	/* Allocate memory management काष्ठाures */
	error = create_basic_memory_biपंचांगaps();
	अगर (error)
		जाओ Thaw;

	error = hibernation_snapshot(hibernation_mode == HIBERNATION_PLATFORM);
	अगर (error || मुक्तzer_test_करोne)
		जाओ Free_biपंचांगaps;

	अगर (in_suspend) अणु
		अचिन्हित पूर्णांक flags = 0;

		अगर (hibernation_mode == HIBERNATION_PLATFORM)
			flags |= SF_PLATFORM_MODE;
		अगर (nocompress)
			flags |= SF_NOCOMPRESS_MODE;
		अन्यथा
		        flags |= SF_CRC32_MODE;

		pm_pr_dbg("Writing hibernation image.\n");
		error = swsusp_ग_लिखो(flags);
		swsusp_मुक्त();
		अगर (!error) अणु
			अगर (hibernation_mode == HIBERNATION_TEST_RESUME)
				snapshot_test = true;
			अन्यथा
				घातer_करोwn();
		पूर्ण
		in_suspend = 0;
		pm_restore_gfp_mask();
	पूर्ण अन्यथा अणु
		pm_pr_dbg("Hibernation image restored successfully.\n");
	पूर्ण

 Free_biपंचांगaps:
	मुक्त_basic_memory_biपंचांगaps();
 Thaw:
	unlock_device_hotplug();
	अगर (snapshot_test) अणु
		pm_pr_dbg("Checking hibernation image\n");
		error = swsusp_check();
		अगर (!error)
			error = load_image_and_restore();
	पूर्ण
	thaw_processes();

	/* Don't bother checking whether मुक्तzer_test_करोne is true */
	मुक्तzer_test_करोne = false;
 Exit:
	pm_notअगरier_call_chain(PM_POST_HIBERNATION);
 Restore:
	pm_restore_console();
	hibernate_release();
 Unlock:
	unlock_प्रणाली_sleep();
	pr_info("hibernation exit\n");

	वापस error;
पूर्ण

/**
 * hibernate_quiet_exec - Execute a function with all devices frozen.
 * @func: Function to execute.
 * @data: Data poपूर्णांकer to pass to @func.
 *
 * Return the @func वापस value or an error code अगर it cannot be executed.
 */
पूर्णांक hibernate_quiet_exec(पूर्णांक (*func)(व्योम *data), व्योम *data)
अणु
	पूर्णांक error;

	lock_प्रणाली_sleep();

	अगर (!hibernate_acquire()) अणु
		error = -EBUSY;
		जाओ unlock;
	पूर्ण

	pm_prepare_console();

	error = pm_notअगरier_call_chain_robust(PM_HIBERNATION_PREPARE, PM_POST_HIBERNATION);
	अगर (error)
		जाओ restore;

	error = मुक्तze_processes();
	अगर (error)
		जाओ निकास;

	lock_device_hotplug();

	pm_suspend_clear_flags();

	error = platक्रमm_begin(true);
	अगर (error)
		जाओ thaw;

	error = मुक्तze_kernel_thपढ़ोs();
	अगर (error)
		जाओ thaw;

	error = dpm_prepare(PMSG_FREEZE);
	अगर (error)
		जाओ dpm_complete;

	suspend_console();

	error = dpm_suspend(PMSG_FREEZE);
	अगर (error)
		जाओ dpm_resume;

	error = dpm_suspend_end(PMSG_FREEZE);
	अगर (error)
		जाओ dpm_resume;

	error = platक्रमm_pre_snapshot(true);
	अगर (error)
		जाओ skip;

	error = func(data);

skip:
	platक्रमm_finish(true);

	dpm_resume_start(PMSG_THAW);

dpm_resume:
	dpm_resume(PMSG_THAW);

	resume_console();

dpm_complete:
	dpm_complete(PMSG_THAW);

	thaw_kernel_thपढ़ोs();

thaw:
	platक्रमm_end(true);

	unlock_device_hotplug();

	thaw_processes();

निकास:
	pm_notअगरier_call_chain(PM_POST_HIBERNATION);

restore:
	pm_restore_console();

	hibernate_release();

unlock:
	unlock_प्रणाली_sleep();

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(hibernate_quiet_exec);

/**
 * software_resume - Resume from a saved hibernation image.
 *
 * This routine is called as a late initcall, when all devices have been
 * discovered and initialized alपढ़ोy.
 *
 * The image पढ़ोing code is called to see अगर there is a hibernation image
 * available क्रम पढ़ोing.  If that is the हाल, devices are quiesced and the
 * contents of memory is restored from the saved image.
 *
 * If this is successful, control reappears in the restored target kernel in
 * hibernation_snapshot() which वापसs to hibernate().  Otherwise, the routine
 * attempts to recover gracefully and make the kernel वापस to the normal mode
 * of operation.
 */
अटल पूर्णांक software_resume(व्योम)
अणु
	पूर्णांक error;

	/*
	 * If the user said "noresume".. bail out early.
	 */
	अगर (noresume || !hibernation_available())
		वापस 0;

	/*
	 * name_to_dev_t() below takes a sysfs buffer mutex when sysfs
	 * is configured पूर्णांकo the kernel. Since the regular hibernate
	 * trigger path is via sysfs which takes a buffer mutex beक्रमe
	 * calling hibernate functions (which take प्रणाली_transition_mutex)
	 * this can cause lockdep to complain about a possible ABBA deadlock
	 * which cannot happen since we're in the boot code here and
	 * sysfs can't be invoked yet. Thereक्रमe, we use a subclass
	 * here to aव्योम lockdep complaining.
	 */
	mutex_lock_nested(&प्रणाली_transition_mutex, SINGLE_DEPTH_NESTING);

	अगर (swsusp_resume_device)
		जाओ Check_image;

	अगर (!म_माप(resume_file)) अणु
		error = -ENOENT;
		जाओ Unlock;
	पूर्ण

	pm_pr_dbg("Checking hibernation image partition %s\n", resume_file);

	अगर (resume_delay) अणु
		pr_info("Waiting %dsec before reading resume device ...\n",
			resume_delay);
		ssleep(resume_delay);
	पूर्ण

	/* Check अगर the device is there */
	swsusp_resume_device = name_to_dev_t(resume_file);
	अगर (!swsusp_resume_device) अणु
		/*
		 * Some device discovery might still be in progress; we need
		 * to रुको क्रम this to finish.
		 */
		रुको_क्रम_device_probe();

		अगर (resume_रुको) अणु
			जबतक ((swsusp_resume_device = name_to_dev_t(resume_file)) == 0)
				msleep(10);
			async_synchronize_full();
		पूर्ण

		swsusp_resume_device = name_to_dev_t(resume_file);
		अगर (!swsusp_resume_device) अणु
			error = -ENODEV;
			जाओ Unlock;
		पूर्ण
	पूर्ण

 Check_image:
	pm_pr_dbg("Hibernation image partition %d:%d present\n",
		MAJOR(swsusp_resume_device), MINOR(swsusp_resume_device));

	pm_pr_dbg("Looking for hibernation image.\n");
	error = swsusp_check();
	अगर (error)
		जाओ Unlock;

	/* The snapshot device should not be खोलोed जबतक we're running */
	अगर (!hibernate_acquire()) अणु
		error = -EBUSY;
		swsusp_बंद(FMODE_READ);
		जाओ Unlock;
	पूर्ण

	pr_info("resume from hibernation\n");
	pm_prepare_console();
	error = pm_notअगरier_call_chain_robust(PM_RESTORE_PREPARE, PM_POST_RESTORE);
	अगर (error)
		जाओ Restore;

	pm_pr_dbg("Preparing processes for hibernation restore.\n");
	error = मुक्तze_processes();
	अगर (error)
		जाओ Close_Finish;

	error = मुक्तze_kernel_thपढ़ोs();
	अगर (error) अणु
		thaw_processes();
		जाओ Close_Finish;
	पूर्ण

	error = load_image_and_restore();
	thaw_processes();
 Finish:
	pm_notअगरier_call_chain(PM_POST_RESTORE);
 Restore:
	pm_restore_console();
	pr_info("resume failed (%d)\n", error);
	hibernate_release();
	/* For success हाल, the suspend path will release the lock */
 Unlock:
	mutex_unlock(&प्रणाली_transition_mutex);
	pm_pr_dbg("Hibernation image not present or could not be loaded.\n");
	वापस error;
 Close_Finish:
	swsusp_बंद(FMODE_READ);
	जाओ Finish;
पूर्ण

late_initcall_sync(software_resume);


अटल स्थिर अक्षर * स्थिर hibernation_modes[] = अणु
	[HIBERNATION_PLATFORM]	= "platform",
	[HIBERNATION_SHUTDOWN]	= "shutdown",
	[HIBERNATION_REBOOT]	= "reboot",
#अगर_घोषित CONFIG_SUSPEND
	[HIBERNATION_SUSPEND]	= "suspend",
#पूर्ण_अगर
	[HIBERNATION_TEST_RESUME]	= "test_resume",
पूर्ण;

/*
 * /sys/घातer/disk - Control hibernation mode.
 *
 * Hibernation can be handled in several ways.  There are a few dअगरferent ways
 * to put the प्रणाली पूर्णांकo the sleep state: using the platक्रमm driver (e.g. ACPI
 * or other hibernation_ops), घातering it off or rebooting it (क्रम testing
 * mostly).
 *
 * The sysfs file /sys/घातer/disk provides an पूर्णांकerface क्रम selecting the
 * hibernation mode to use.  Reading from this file causes the available modes
 * to be prपूर्णांकed.  There are 3 modes that can be supported:
 *
 *	'platform'
 *	'shutdown'
 *	'reboot'
 *
 * If a platक्रमm hibernation driver is in use, 'platform' will be supported
 * and will be used by शेष.  Otherwise, 'shutdown' will be used by शेष.
 * The selected option (i.e. the one corresponding to the current value of
 * hibernation_mode) is enबंदd by a square bracket.
 *
 * To select a given hibernation mode it is necessary to ग_लिखो the mode's
 * string representation (as वापसed by पढ़ोing from /sys/घातer/disk) back
 * पूर्णांकo /sys/घातer/disk.
 */

अटल sमाप_प्रकार disk_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			 अक्षर *buf)
अणु
	पूर्णांक i;
	अक्षर *start = buf;

	अगर (!hibernation_available())
		वापस प्र_लिखो(buf, "[disabled]\n");

	क्रम (i = HIBERNATION_FIRST; i <= HIBERNATION_MAX; i++) अणु
		अगर (!hibernation_modes[i])
			जारी;
		चयन (i) अणु
		हाल HIBERNATION_SHUTDOWN:
		हाल HIBERNATION_REBOOT:
#अगर_घोषित CONFIG_SUSPEND
		हाल HIBERNATION_SUSPEND:
#पूर्ण_अगर
		हाल HIBERNATION_TEST_RESUME:
			अवरोध;
		हाल HIBERNATION_PLATFORM:
			अगर (hibernation_ops)
				अवरोध;
			/* not a valid mode, जारी with loop */
			जारी;
		पूर्ण
		अगर (i == hibernation_mode)
			buf += प्र_लिखो(buf, "[%s] ", hibernation_modes[i]);
		अन्यथा
			buf += प्र_लिखो(buf, "%s ", hibernation_modes[i]);
	पूर्ण
	buf += प्र_लिखो(buf, "\n");
	वापस buf-start;
पूर्ण

अटल sमाप_प्रकार disk_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	पूर्णांक error = 0;
	पूर्णांक i;
	पूर्णांक len;
	अक्षर *p;
	पूर्णांक mode = HIBERNATION_INVALID;

	अगर (!hibernation_available())
		वापस -EPERM;

	p = स_प्रथम(buf, '\n', n);
	len = p ? p - buf : n;

	lock_प्रणाली_sleep();
	क्रम (i = HIBERNATION_FIRST; i <= HIBERNATION_MAX; i++) अणु
		अगर (len == म_माप(hibernation_modes[i])
		    && !म_भेदन(buf, hibernation_modes[i], len)) अणु
			mode = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (mode != HIBERNATION_INVALID) अणु
		चयन (mode) अणु
		हाल HIBERNATION_SHUTDOWN:
		हाल HIBERNATION_REBOOT:
#अगर_घोषित CONFIG_SUSPEND
		हाल HIBERNATION_SUSPEND:
#पूर्ण_अगर
		हाल HIBERNATION_TEST_RESUME:
			hibernation_mode = mode;
			अवरोध;
		हाल HIBERNATION_PLATFORM:
			अगर (hibernation_ops)
				hibernation_mode = mode;
			अन्यथा
				error = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा
		error = -EINVAL;

	अगर (!error)
		pm_pr_dbg("Hibernation mode set to '%s'\n",
			       hibernation_modes[mode]);
	unlock_प्रणाली_sleep();
	वापस error ? error : n;
पूर्ण

घातer_attr(disk);

अटल sमाप_प्रकार resume_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			   अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d:%d\n", MAJOR(swsusp_resume_device),
		       MINOR(swsusp_resume_device));
पूर्ण

अटल sमाप_प्रकार resume_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	dev_t res;
	पूर्णांक len = n;
	अक्षर *name;

	अगर (len && buf[len-1] == '\n')
		len--;
	name = kstrndup(buf, len, GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;

	res = name_to_dev_t(name);
	kमुक्त(name);
	अगर (!res)
		वापस -EINVAL;

	lock_प्रणाली_sleep();
	swsusp_resume_device = res;
	unlock_प्रणाली_sleep();
	pm_pr_dbg("Configured hibernation resume from disk to %u\n",
		  swsusp_resume_device);
	noresume = 0;
	software_resume();
	वापस n;
पूर्ण

घातer_attr(resume);

अटल sमाप_प्रकार resume_offset_show(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n", (अचिन्हित दीर्घ दीर्घ)swsusp_resume_block);
पूर्ण

अटल sमाप_प्रकार resume_offset_store(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr, स्थिर अक्षर *buf,
				   माप_प्रकार n)
अणु
	अचिन्हित दीर्घ दीर्घ offset;
	पूर्णांक rc;

	rc = kम_से_अदीर्घl(buf, 0, &offset);
	अगर (rc)
		वापस rc;
	swsusp_resume_block = offset;

	वापस n;
पूर्ण

घातer_attr(resume_offset);

अटल sमाप_प्रकार image_size_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			       अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%lu\n", image_size);
पूर्ण

अटल sमाप_प्रकार image_size_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	अचिन्हित दीर्घ size;

	अगर (माला_पूछो(buf, "%lu", &size) == 1) अणु
		image_size = size;
		वापस n;
	पूर्ण

	वापस -EINVAL;
पूर्ण

घातer_attr(image_size);

अटल sमाप_प्रकार reserved_size_show(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%lu\n", reserved_size);
पूर्ण

अटल sमाप_प्रकार reserved_size_store(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	अचिन्हित दीर्घ size;

	अगर (माला_पूछो(buf, "%lu", &size) == 1) अणु
		reserved_size = size;
		वापस n;
	पूर्ण

	वापस -EINVAL;
पूर्ण

घातer_attr(reserved_size);

अटल काष्ठा attribute *g[] = अणु
	&disk_attr.attr,
	&resume_offset_attr.attr,
	&resume_attr.attr,
	&image_size_attr.attr,
	&reserved_size_attr.attr,
	शून्य,
पूर्ण;


अटल स्थिर काष्ठा attribute_group attr_group = अणु
	.attrs = g,
पूर्ण;


अटल पूर्णांक __init pm_disk_init(व्योम)
अणु
	वापस sysfs_create_group(घातer_kobj, &attr_group);
पूर्ण

core_initcall(pm_disk_init);


अटल पूर्णांक __init resume_setup(अक्षर *str)
अणु
	अगर (noresume)
		वापस 1;

	म_नकलन(resume_file, str, 255);
	वापस 1;
पूर्ण

अटल पूर्णांक __init resume_offset_setup(अक्षर *str)
अणु
	अचिन्हित दीर्घ दीर्घ offset;

	अगर (noresume)
		वापस 1;

	अगर (माला_पूछो(str, "%llu", &offset) == 1)
		swsusp_resume_block = offset;

	वापस 1;
पूर्ण

अटल पूर्णांक __init hibernate_setup(अक्षर *str)
अणु
	अगर (!म_भेदन(str, "noresume", 8)) अणु
		noresume = 1;
	पूर्ण अन्यथा अगर (!म_भेदन(str, "nocompress", 10)) अणु
		nocompress = 1;
	पूर्ण अन्यथा अगर (!म_भेदन(str, "no", 2)) अणु
		noresume = 1;
		nohibernate = 1;
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_STRICT_KERNEL_RWX)
		   && !म_भेदन(str, "protect_image", 13)) अणु
		enable_restore_image_protection();
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक __init noresume_setup(अक्षर *str)
अणु
	noresume = 1;
	वापस 1;
पूर्ण

अटल पूर्णांक __init resumeरुको_setup(अक्षर *str)
अणु
	resume_रुको = 1;
	वापस 1;
पूर्ण

अटल पूर्णांक __init resumedelay_setup(अक्षर *str)
अणु
	पूर्णांक rc = kstrtouपूर्णांक(str, 0, &resume_delay);

	अगर (rc)
		वापस rc;
	वापस 1;
पूर्ण

अटल पूर्णांक __init nohibernate_setup(अक्षर *str)
अणु
	noresume = 1;
	nohibernate = 1;
	वापस 1;
पूर्ण

__setup("noresume", noresume_setup);
__setup("resume_offset=", resume_offset_setup);
__setup("resume=", resume_setup);
__setup("hibernate=", hibernate_setup);
__setup("resumewait", resumeरुको_setup);
__setup("resumedelay=", resumedelay_setup);
__setup("nohibernate", nohibernate_setup);
