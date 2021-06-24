<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/kernel/reboot.c
 *
 *  Copyright (C) 2013  Linus Torvalds
 */

#घोषणा pr_fmt(fmt)	"reboot: " fmt

#समावेश <linux/प्रकार.स>
#समावेश <linux/export.h>
#समावेश <linux/kexec.h>
#समावेश <linux/kmod.h>
#समावेश <linux/kmsg_dump.h>
#समावेश <linux/reboot.h>
#समावेश <linux/suspend.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/uaccess.h>

/*
 * this indicates whether you can reboot with ctrl-alt-del: the शेष is yes
 */

पूर्णांक C_A_D = 1;
काष्ठा pid *cad_pid;
EXPORT_SYMBOL(cad_pid);

#अगर defined(CONFIG_ARM)
#घोषणा DEFAULT_REBOOT_MODE		= REBOOT_HARD
#अन्यथा
#घोषणा DEFAULT_REBOOT_MODE
#पूर्ण_अगर
क्रमागत reboot_mode reboot_mode DEFAULT_REBOOT_MODE;
क्रमागत reboot_mode panic_reboot_mode = REBOOT_UNDEFINED;

/*
 * This variable is used निजीly to keep track of whether or not
 * reboot_type is still set to its शेष value (i.e., reboot= hasn't
 * been set on the command line).  This is needed so that we can
 * suppress DMI scanning क्रम reboot quirks.  Without it, it's
 * impossible to override a faulty reboot quirk without recompiling.
 */
पूर्णांक reboot_शेष = 1;
पूर्णांक reboot_cpu;
क्रमागत reboot_type reboot_type = BOOT_ACPI;
पूर्णांक reboot_क्रमce;

/*
 * If set, this is used क्रम preparing the प्रणाली to घातer off.
 */

व्योम (*pm_घातer_off_prepare)(व्योम);
EXPORT_SYMBOL_GPL(pm_घातer_off_prepare);

/**
 *	emergency_restart - reboot the प्रणाली
 *
 *	Without shutting करोwn any hardware or taking any locks
 *	reboot the प्रणाली.  This is called when we know we are in
 *	trouble so this is our best efक्रमt to reboot.  This is
 *	safe to call in पूर्णांकerrupt context.
 */
व्योम emergency_restart(व्योम)
अणु
	kmsg_dump(KMSG_DUMP_EMERG);
	machine_emergency_restart();
पूर्ण
EXPORT_SYMBOL_GPL(emergency_restart);

व्योम kernel_restart_prepare(अक्षर *cmd)
अणु
	blocking_notअगरier_call_chain(&reboot_notअगरier_list, SYS_RESTART, cmd);
	प्रणाली_state = SYSTEM_RESTART;
	usermodehelper_disable();
	device_shutकरोwn();
पूर्ण

/**
 *	रेजिस्टर_reboot_notअगरier - Register function to be called at reboot समय
 *	@nb: Info about notअगरier function to be called
 *
 *	Registers a function with the list of functions
 *	to be called at reboot समय.
 *
 *	Currently always वापसs zero, as blocking_notअगरier_chain_रेजिस्टर()
 *	always वापसs zero.
 */
पूर्णांक रेजिस्टर_reboot_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&reboot_notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_reboot_notअगरier);

/**
 *	unरेजिस्टर_reboot_notअगरier - Unरेजिस्टर previously रेजिस्टरed reboot notअगरier
 *	@nb: Hook to be unरेजिस्टरed
 *
 *	Unरेजिस्टरs a previously रेजिस्टरed reboot
 *	notअगरier function.
 *
 *	Returns zero on success, or %-ENOENT on failure.
 */
पूर्णांक unरेजिस्टर_reboot_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&reboot_notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_reboot_notअगरier);

अटल व्योम devm_unरेजिस्टर_reboot_notअगरier(काष्ठा device *dev, व्योम *res)
अणु
	WARN_ON(unरेजिस्टर_reboot_notअगरier(*(काष्ठा notअगरier_block **)res));
पूर्ण

पूर्णांक devm_रेजिस्टर_reboot_notअगरier(काष्ठा device *dev, काष्ठा notअगरier_block *nb)
अणु
	काष्ठा notअगरier_block **rcnb;
	पूर्णांक ret;

	rcnb = devres_alloc(devm_unरेजिस्टर_reboot_notअगरier,
			    माप(*rcnb), GFP_KERNEL);
	अगर (!rcnb)
		वापस -ENOMEM;

	ret = रेजिस्टर_reboot_notअगरier(nb);
	अगर (!ret) अणु
		*rcnb = nb;
		devres_add(dev, rcnb);
	पूर्ण अन्यथा अणु
		devres_मुक्त(rcnb);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(devm_रेजिस्टर_reboot_notअगरier);

/*
 *	Notअगरier list क्रम kernel code which wants to be called
 *	to restart the प्रणाली.
 */
अटल ATOMIC_NOTIFIER_HEAD(restart_handler_list);

/**
 *	रेजिस्टर_restart_handler - Register function to be called to reset
 *				   the प्रणाली
 *	@nb: Info about handler function to be called
 *	@nb->priority:	Handler priority. Handlers should follow the
 *			following guidelines क्रम setting priorities.
 *			0:	Restart handler of last resort,
 *				with limited restart capabilities
 *			128:	Default restart handler; use अगर no other
 *				restart handler is expected to be available,
 *				and/or अगर restart functionality is
 *				sufficient to restart the entire प्रणाली
 *			255:	Highest priority restart handler, will
 *				preempt all other restart handlers
 *
 *	Registers a function with code to be called to restart the
 *	प्रणाली.
 *
 *	Registered functions will be called from machine_restart as last
 *	step of the restart sequence (अगर the architecture specअगरic
 *	machine_restart function calls करो_kernel_restart - see below
 *	क्रम details).
 *	Registered functions are expected to restart the प्रणाली immediately.
 *	If more than one function is रेजिस्टरed, the restart handler priority
 *	selects which function will be called first.
 *
 *	Restart handlers are expected to be रेजिस्टरed from non-architecture
 *	code, typically from drivers. A typical use हाल would be a प्रणाली
 *	where restart functionality is provided through a watchकरोg. Multiple
 *	restart handlers may exist; क्रम example, one restart handler might
 *	restart the entire प्रणाली, जबतक another only restarts the CPU.
 *	In such हालs, the restart handler which only restarts part of the
 *	hardware is expected to रेजिस्टर with low priority to ensure that
 *	it only runs अगर no other means to restart the प्रणाली is available.
 *
 *	Currently always वापसs zero, as atomic_notअगरier_chain_रेजिस्टर()
 *	always वापसs zero.
 */
पूर्णांक रेजिस्टर_restart_handler(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&restart_handler_list, nb);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_restart_handler);

/**
 *	unरेजिस्टर_restart_handler - Unरेजिस्टर previously रेजिस्टरed
 *				     restart handler
 *	@nb: Hook to be unरेजिस्टरed
 *
 *	Unरेजिस्टरs a previously रेजिस्टरed restart handler function.
 *
 *	Returns zero on success, or %-ENOENT on failure.
 */
पूर्णांक unरेजिस्टर_restart_handler(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_unरेजिस्टर(&restart_handler_list, nb);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_restart_handler);

/**
 *	करो_kernel_restart - Execute kernel restart handler call chain
 *
 *	Calls functions रेजिस्टरed with रेजिस्टर_restart_handler.
 *
 *	Expected to be called from machine_restart as last step of the restart
 *	sequence.
 *
 *	Restarts the प्रणाली immediately अगर a restart handler function has been
 *	रेजिस्टरed. Otherwise करोes nothing.
 */
व्योम करो_kernel_restart(अक्षर *cmd)
अणु
	atomic_notअगरier_call_chain(&restart_handler_list, reboot_mode, cmd);
पूर्ण

व्योम migrate_to_reboot_cpu(व्योम)
अणु
	/* The boot cpu is always logical cpu 0 */
	पूर्णांक cpu = reboot_cpu;

	cpu_hotplug_disable();

	/* Make certain the cpu I'm about to reboot on is online */
	अगर (!cpu_online(cpu))
		cpu = cpumask_first(cpu_online_mask);

	/* Prevent races with other tasks migrating this task */
	current->flags |= PF_NO_SETAFFINITY;

	/* Make certain I only run on the appropriate processor */
	set_cpus_allowed_ptr(current, cpumask_of(cpu));
पूर्ण

/**
 *	kernel_restart - reboot the प्रणाली
 *	@cmd: poपूर्णांकer to buffer containing command to execute क्रम restart
 *		or %शून्य
 *
 *	Shutकरोwn everything and perक्रमm a clean reboot.
 *	This is not safe to call in पूर्णांकerrupt context.
 */
व्योम kernel_restart(अक्षर *cmd)
अणु
	kernel_restart_prepare(cmd);
	migrate_to_reboot_cpu();
	syscore_shutकरोwn();
	अगर (!cmd)
		pr_emerg("Restarting system\n");
	अन्यथा
		pr_emerg("Restarting system with command '%s'\n", cmd);
	kmsg_dump(KMSG_DUMP_SHUTDOWN);
	machine_restart(cmd);
पूर्ण
EXPORT_SYMBOL_GPL(kernel_restart);

अटल व्योम kernel_shutकरोwn_prepare(क्रमागत प्रणाली_states state)
अणु
	blocking_notअगरier_call_chain(&reboot_notअगरier_list,
		(state == SYSTEM_HALT) ? SYS_HALT : SYS_POWER_OFF, शून्य);
	प्रणाली_state = state;
	usermodehelper_disable();
	device_shutकरोwn();
पूर्ण
/**
 *	kernel_halt - halt the प्रणाली
 *
 *	Shutकरोwn everything and perक्रमm a clean प्रणाली halt.
 */
व्योम kernel_halt(व्योम)
अणु
	kernel_shutकरोwn_prepare(SYSTEM_HALT);
	migrate_to_reboot_cpu();
	syscore_shutकरोwn();
	pr_emerg("System halted\n");
	kmsg_dump(KMSG_DUMP_SHUTDOWN);
	machine_halt();
पूर्ण
EXPORT_SYMBOL_GPL(kernel_halt);

/**
 *	kernel_घातer_off - घातer_off the प्रणाली
 *
 *	Shutकरोwn everything and perक्रमm a clean प्रणाली घातer_off.
 */
व्योम kernel_घातer_off(व्योम)
अणु
	kernel_shutकरोwn_prepare(SYSTEM_POWER_OFF);
	अगर (pm_घातer_off_prepare)
		pm_घातer_off_prepare();
	migrate_to_reboot_cpu();
	syscore_shutकरोwn();
	pr_emerg("Power down\n");
	kmsg_dump(KMSG_DUMP_SHUTDOWN);
	machine_घातer_off();
पूर्ण
EXPORT_SYMBOL_GPL(kernel_घातer_off);

DEFINE_MUTEX(प्रणाली_transition_mutex);

/*
 * Reboot प्रणाली call: क्रम obvious reasons only root may call it,
 * and even root needs to set up some magic numbers in the रेजिस्टरs
 * so that some mistake won't make this reboot the whole machine.
 * You can also set the meaning of the ctrl-alt-del-key here.
 *
 * reboot करोesn't sync: करो that yourself beक्रमe calling this.
 */
SYSCALL_DEFINE4(reboot, पूर्णांक, magic1, पूर्णांक, magic2, अचिन्हित पूर्णांक, cmd,
		व्योम __user *, arg)
अणु
	काष्ठा pid_namespace *pid_ns = task_active_pid_ns(current);
	अक्षर buffer[256];
	पूर्णांक ret = 0;

	/* We only trust the superuser with rebooting the प्रणाली. */
	अगर (!ns_capable(pid_ns->user_ns, CAP_SYS_BOOT))
		वापस -EPERM;

	/* For safety, we require "magic" arguments. */
	अगर (magic1 != LINUX_REBOOT_MAGIC1 ||
			(magic2 != LINUX_REBOOT_MAGIC2 &&
			magic2 != LINUX_REBOOT_MAGIC2A &&
			magic2 != LINUX_REBOOT_MAGIC2B &&
			magic2 != LINUX_REBOOT_MAGIC2C))
		वापस -EINVAL;

	/*
	 * If pid namespaces are enabled and the current task is in a child
	 * pid_namespace, the command is handled by reboot_pid_ns() which will
	 * call करो_निकास().
	 */
	ret = reboot_pid_ns(pid_ns, cmd);
	अगर (ret)
		वापस ret;

	/* Instead of trying to make the घातer_off code look like
	 * halt when pm_घातer_off is not set करो it the easy way.
	 */
	अगर ((cmd == LINUX_REBOOT_CMD_POWER_OFF) && !pm_घातer_off)
		cmd = LINUX_REBOOT_CMD_HALT;

	mutex_lock(&प्रणाली_transition_mutex);
	चयन (cmd) अणु
	हाल LINUX_REBOOT_CMD_RESTART:
		kernel_restart(शून्य);
		अवरोध;

	हाल LINUX_REBOOT_CMD_CAD_ON:
		C_A_D = 1;
		अवरोध;

	हाल LINUX_REBOOT_CMD_CAD_OFF:
		C_A_D = 0;
		अवरोध;

	हाल LINUX_REBOOT_CMD_HALT:
		kernel_halt();
		करो_निकास(0);
		panic("cannot halt");

	हाल LINUX_REBOOT_CMD_POWER_OFF:
		kernel_घातer_off();
		करो_निकास(0);
		अवरोध;

	हाल LINUX_REBOOT_CMD_RESTART2:
		ret = म_नकलन_from_user(&buffer[0], arg, माप(buffer) - 1);
		अगर (ret < 0) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		buffer[माप(buffer) - 1] = '\0';

		kernel_restart(buffer);
		अवरोध;

#अगर_घोषित CONFIG_KEXEC_CORE
	हाल LINUX_REBOOT_CMD_KEXEC:
		ret = kernel_kexec();
		अवरोध;
#पूर्ण_अगर

#अगर_घोषित CONFIG_HIBERNATION
	हाल LINUX_REBOOT_CMD_SW_SUSPEND:
		ret = hibernate();
		अवरोध;
#पूर्ण_अगर

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	mutex_unlock(&प्रणाली_transition_mutex);
	वापस ret;
पूर्ण

अटल व्योम deferred_cad(काष्ठा work_काष्ठा *dummy)
अणु
	kernel_restart(शून्य);
पूर्ण

/*
 * This function माला_लो called by ctrl-alt-del - ie the keyboard पूर्णांकerrupt.
 * As it's called within an पूर्णांकerrupt, it may NOT sync: the only choice
 * is whether to reboot at once, or just ignore the ctrl-alt-del.
 */
व्योम ctrl_alt_del(व्योम)
अणु
	अटल DECLARE_WORK(cad_work, deferred_cad);

	अगर (C_A_D)
		schedule_work(&cad_work);
	अन्यथा
		समाप्त_cad_pid(संक_विघ्न, 1);
पूर्ण

अक्षर घातeroff_cmd[POWEROFF_CMD_PATH_LEN] = "/sbin/poweroff";
अटल स्थिर अक्षर reboot_cmd[] = "/sbin/reboot";

अटल पूर्णांक run_cmd(स्थिर अक्षर *cmd)
अणु
	अक्षर **argv;
	अटल अक्षर *envp[] = अणु
		"HOME=/",
		"PATH=/sbin:/bin:/usr/sbin:/usr/bin",
		शून्य
	पूर्ण;
	पूर्णांक ret;
	argv = argv_split(GFP_KERNEL, cmd, शून्य);
	अगर (argv) अणु
		ret = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
		argv_मुक्त(argv);
	पूर्ण अन्यथा अणु
		ret = -ENOMEM;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __orderly_reboot(व्योम)
अणु
	पूर्णांक ret;

	ret = run_cmd(reboot_cmd);

	अगर (ret) अणु
		pr_warn("Failed to start orderly reboot: forcing the issue\n");
		emergency_sync();
		kernel_restart(शून्य);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __orderly_घातeroff(bool क्रमce)
अणु
	पूर्णांक ret;

	ret = run_cmd(घातeroff_cmd);

	अगर (ret && क्रमce) अणु
		pr_warn("Failed to start orderly shutdown: forcing the issue\n");

		/*
		 * I guess this should try to kick off some daemon to sync and
		 * घातeroff asap.  Or not even bother syncing अगर we're करोing an
		 * emergency shutकरोwn?
		 */
		emergency_sync();
		kernel_घातer_off();
	पूर्ण

	वापस ret;
पूर्ण

अटल bool घातeroff_क्रमce;

अटल व्योम घातeroff_work_func(काष्ठा work_काष्ठा *work)
अणु
	__orderly_घातeroff(घातeroff_क्रमce);
पूर्ण

अटल DECLARE_WORK(घातeroff_work, घातeroff_work_func);

/**
 * orderly_घातeroff - Trigger an orderly प्रणाली घातeroff
 * @क्रमce: क्रमce घातeroff अगर command execution fails
 *
 * This may be called from any context to trigger a प्रणाली shutकरोwn.
 * If the orderly shutकरोwn fails, it will क्रमce an immediate shutकरोwn.
 */
व्योम orderly_घातeroff(bool क्रमce)
अणु
	अगर (क्रमce) /* करो not override the pending "true" */
		घातeroff_क्रमce = true;
	schedule_work(&घातeroff_work);
पूर्ण
EXPORT_SYMBOL_GPL(orderly_घातeroff);

अटल व्योम reboot_work_func(काष्ठा work_काष्ठा *work)
अणु
	__orderly_reboot();
पूर्ण

अटल DECLARE_WORK(reboot_work, reboot_work_func);

/**
 * orderly_reboot - Trigger an orderly प्रणाली reboot
 *
 * This may be called from any context to trigger a प्रणाली reboot.
 * If the orderly reboot fails, it will क्रमce an immediate reboot.
 */
व्योम orderly_reboot(व्योम)
अणु
	schedule_work(&reboot_work);
पूर्ण
EXPORT_SYMBOL_GPL(orderly_reboot);

अटल पूर्णांक __init reboot_setup(अक्षर *str)
अणु
	क्रम (;;) अणु
		क्रमागत reboot_mode *mode;

		/*
		 * Having anything passed on the command line via
		 * reboot= will cause us to disable DMI checking
		 * below.
		 */
		reboot_शेष = 0;

		अगर (!म_भेदन(str, "panic_", 6)) अणु
			mode = &panic_reboot_mode;
			str += 6;
		पूर्ण अन्यथा अणु
			mode = &reboot_mode;
		पूर्ण

		चयन (*str) अणु
		हाल 'w':
			*mode = REBOOT_WARM;
			अवरोध;

		हाल 'c':
			*mode = REBOOT_COLD;
			अवरोध;

		हाल 'h':
			*mode = REBOOT_HARD;
			अवरोध;

		हाल 's':
			/*
			 * reboot_cpu is s[mp]#### with #### being the processor
			 * to be used क्रम rebooting. Skip 's' or 'smp' prefix.
			 */
			str += str[1] == 'm' && str[2] == 'p' ? 3 : 1;

			अगर (है_अंक(str[0])) अणु
				पूर्णांक cpu = simple_म_से_अदीर्घ(str, शून्य, 0);

				अगर (cpu >= num_possible_cpus()) अणु
					pr_err("Ignoring the CPU number in reboot= option. "
					"CPU %d exceeds possible cpu number %d\n",
					cpu, num_possible_cpus());
					अवरोध;
				पूर्ण
				reboot_cpu = cpu;
			पूर्ण अन्यथा
				*mode = REBOOT_SOFT;
			अवरोध;

		हाल 'g':
			*mode = REBOOT_GPIO;
			अवरोध;

		हाल 'b':
		हाल 'a':
		हाल 'k':
		हाल 't':
		हाल 'e':
		हाल 'p':
			reboot_type = *str;
			अवरोध;

		हाल 'f':
			reboot_क्रमce = 1;
			अवरोध;
		पूर्ण

		str = म_अक्षर(str, ',');
		अगर (str)
			str++;
		अन्यथा
			अवरोध;
	पूर्ण
	वापस 1;
पूर्ण
__setup("reboot=", reboot_setup);

#अगर_घोषित CONFIG_SYSFS

#घोषणा REBOOT_COLD_STR		"cold"
#घोषणा REBOOT_WARM_STR		"warm"
#घोषणा REBOOT_HARD_STR		"hard"
#घोषणा REBOOT_SOFT_STR		"soft"
#घोषणा REBOOT_GPIO_STR		"gpio"
#घोषणा REBOOT_UNDEFINED_STR	"undefined"

#घोषणा BOOT_TRIPLE_STR		"triple"
#घोषणा BOOT_KBD_STR		"kbd"
#घोषणा BOOT_BIOS_STR		"bios"
#घोषणा BOOT_ACPI_STR		"acpi"
#घोषणा BOOT_EFI_STR		"efi"
#घोषणा BOOT_PCI_STR		"pci"

अटल sमाप_प्रकार mode_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	स्थिर अक्षर *val;

	चयन (reboot_mode) अणु
	हाल REBOOT_COLD:
		val = REBOOT_COLD_STR;
		अवरोध;
	हाल REBOOT_WARM:
		val = REBOOT_WARM_STR;
		अवरोध;
	हाल REBOOT_HARD:
		val = REBOOT_HARD_STR;
		अवरोध;
	हाल REBOOT_SOFT:
		val = REBOOT_SOFT_STR;
		अवरोध;
	हाल REBOOT_GPIO:
		val = REBOOT_GPIO_STR;
		अवरोध;
	शेष:
		val = REBOOT_UNDEFINED_STR;
	पूर्ण

	वापस प्र_लिखो(buf, "%s\n", val);
पूर्ण
अटल sमाप_प्रकार mode_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (!capable(CAP_SYS_BOOT))
		वापस -EPERM;

	अगर (!म_भेदन(buf, REBOOT_COLD_STR, म_माप(REBOOT_COLD_STR)))
		reboot_mode = REBOOT_COLD;
	अन्यथा अगर (!म_भेदन(buf, REBOOT_WARM_STR, म_माप(REBOOT_WARM_STR)))
		reboot_mode = REBOOT_WARM;
	अन्यथा अगर (!म_भेदन(buf, REBOOT_HARD_STR, म_माप(REBOOT_HARD_STR)))
		reboot_mode = REBOOT_HARD;
	अन्यथा अगर (!म_भेदन(buf, REBOOT_SOFT_STR, म_माप(REBOOT_SOFT_STR)))
		reboot_mode = REBOOT_SOFT;
	अन्यथा अगर (!म_भेदन(buf, REBOOT_GPIO_STR, म_माप(REBOOT_GPIO_STR)))
		reboot_mode = REBOOT_GPIO;
	अन्यथा
		वापस -EINVAL;

	reboot_शेष = 0;

	वापस count;
पूर्ण
अटल काष्ठा kobj_attribute reboot_mode_attr = __ATTR_RW(mode);

#अगर_घोषित CONFIG_X86
अटल sमाप_प्रकार क्रमce_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", reboot_क्रमce);
पूर्ण
अटल sमाप_प्रकार क्रमce_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	bool res;

	अगर (!capable(CAP_SYS_BOOT))
		वापस -EPERM;

	अगर (kstrtobool(buf, &res))
		वापस -EINVAL;

	reboot_शेष = 0;
	reboot_क्रमce = res;

	वापस count;
पूर्ण
अटल काष्ठा kobj_attribute reboot_क्रमce_attr = __ATTR_RW(क्रमce);

अटल sमाप_प्रकार type_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	स्थिर अक्षर *val;

	चयन (reboot_type) अणु
	हाल BOOT_TRIPLE:
		val = BOOT_TRIPLE_STR;
		अवरोध;
	हाल BOOT_KBD:
		val = BOOT_KBD_STR;
		अवरोध;
	हाल BOOT_BIOS:
		val = BOOT_BIOS_STR;
		अवरोध;
	हाल BOOT_ACPI:
		val = BOOT_ACPI_STR;
		अवरोध;
	हाल BOOT_EFI:
		val = BOOT_EFI_STR;
		अवरोध;
	हाल BOOT_CF9_FORCE:
		val = BOOT_PCI_STR;
		अवरोध;
	शेष:
		val = REBOOT_UNDEFINED_STR;
	पूर्ण

	वापस प्र_लिखो(buf, "%s\n", val);
पूर्ण
अटल sमाप_प्रकार type_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (!capable(CAP_SYS_BOOT))
		वापस -EPERM;

	अगर (!म_भेदन(buf, BOOT_TRIPLE_STR, म_माप(BOOT_TRIPLE_STR)))
		reboot_type = BOOT_TRIPLE;
	अन्यथा अगर (!म_भेदन(buf, BOOT_KBD_STR, म_माप(BOOT_KBD_STR)))
		reboot_type = BOOT_KBD;
	अन्यथा अगर (!म_भेदन(buf, BOOT_BIOS_STR, म_माप(BOOT_BIOS_STR)))
		reboot_type = BOOT_BIOS;
	अन्यथा अगर (!म_भेदन(buf, BOOT_ACPI_STR, म_माप(BOOT_ACPI_STR)))
		reboot_type = BOOT_ACPI;
	अन्यथा अगर (!म_भेदन(buf, BOOT_EFI_STR, म_माप(BOOT_EFI_STR)))
		reboot_type = BOOT_EFI;
	अन्यथा अगर (!म_भेदन(buf, BOOT_PCI_STR, म_माप(BOOT_PCI_STR)))
		reboot_type = BOOT_CF9_FORCE;
	अन्यथा
		वापस -EINVAL;

	reboot_शेष = 0;

	वापस count;
पूर्ण
अटल काष्ठा kobj_attribute reboot_type_attr = __ATTR_RW(type);
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
अटल sमाप_प्रकार cpu_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", reboot_cpu);
पूर्ण
अटल sमाप_प्रकार cpu_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक cpunum;
	पूर्णांक rc;

	अगर (!capable(CAP_SYS_BOOT))
		वापस -EPERM;

	rc = kstrtouपूर्णांक(buf, 0, &cpunum);

	अगर (rc)
		वापस rc;

	अगर (cpunum >= num_possible_cpus())
		वापस -दुस्फल;

	reboot_शेष = 0;
	reboot_cpu = cpunum;

	वापस count;
पूर्ण
अटल काष्ठा kobj_attribute reboot_cpu_attr = __ATTR_RW(cpu);
#पूर्ण_अगर

अटल काष्ठा attribute *reboot_attrs[] = अणु
	&reboot_mode_attr.attr,
#अगर_घोषित CONFIG_X86
	&reboot_क्रमce_attr.attr,
	&reboot_type_attr.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMP
	&reboot_cpu_attr.attr,
#पूर्ण_अगर
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group reboot_attr_group = अणु
	.attrs = reboot_attrs,
पूर्ण;

अटल पूर्णांक __init reboot_ksysfs_init(व्योम)
अणु
	काष्ठा kobject *reboot_kobj;
	पूर्णांक ret;

	reboot_kobj = kobject_create_and_add("reboot", kernel_kobj);
	अगर (!reboot_kobj)
		वापस -ENOMEM;

	ret = sysfs_create_group(reboot_kobj, &reboot_attr_group);
	अगर (ret) अणु
		kobject_put(reboot_kobj);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
late_initcall(reboot_ksysfs_init);

#पूर्ण_अगर
