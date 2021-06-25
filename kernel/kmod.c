<शैली गुरु>
/*
 * kmod - the kernel module loader
 */
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/unistd.h>
#समावेश <linux/kmod.h>
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>
#समावेश <linux/cred.h>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/security.h>
#समावेश <linux/mount.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/resource.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/suspend.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/async.h>
#समावेश <linux/uaccess.h>

#समावेश <trace/events/module.h>

/*
 * Assuming:
 *
 * thपढ़ोs = भाग64_u64((u64) totalram_pages * (u64) PAGE_SIZE,
 *		       (u64) THREAD_SIZE * 8UL);
 *
 * If you need less than 50 thपढ़ोs would mean we're dealing with प्रणालीs
 * smaller than 3200 pages. This assumes you are capable of having ~13M memory,
 * and this would only be an upper limit, after which the OOM समाप्तer would take
 * effect. Systems like these are very unlikely अगर modules are enabled.
 */
#घोषणा MAX_KMOD_CONCURRENT 50
अटल atomic_t kmod_concurrent_max = ATOMIC_INIT(MAX_KMOD_CONCURRENT);
अटल DECLARE_WAIT_QUEUE_HEAD(kmod_wq);

/*
 * This is a restriction on having *all* MAX_KMOD_CONCURRENT thपढ़ोs
 * running at the same समय without वापसing. When this happens we
 * believe you've somehow ended up with a recursive module dependency
 * creating a loop.
 *
 * We have no option but to fail.
 *
 * Userspace should proactively try to detect and prevent these.
 */
#घोषणा MAX_KMOD_ALL_BUSY_TIMEOUT 5

/*
	modprobe_path is set via /proc/sys.
*/
अक्षर modprobe_path[KMOD_PATH_LEN] = CONFIG_MODPROBE_PATH;

अटल व्योम मुक्त_modprobe_argv(काष्ठा subprocess_info *info)
अणु
	kमुक्त(info->argv[3]); /* check call_modprobe() */
	kमुक्त(info->argv);
पूर्ण

अटल पूर्णांक call_modprobe(अक्षर *module_name, पूर्णांक रुको)
अणु
	काष्ठा subprocess_info *info;
	अटल अक्षर *envp[] = अणु
		"HOME=/",
		"TERM=linux",
		"PATH=/sbin:/usr/sbin:/bin:/usr/bin",
		शून्य
	पूर्ण;

	अक्षर **argv = kदो_स्मृति(माप(अक्षर *[5]), GFP_KERNEL);
	अगर (!argv)
		जाओ out;

	module_name = kstrdup(module_name, GFP_KERNEL);
	अगर (!module_name)
		जाओ मुक्त_argv;

	argv[0] = modprobe_path;
	argv[1] = "-q";
	argv[2] = "--";
	argv[3] = module_name;	/* check मुक्त_modprobe_argv() */
	argv[4] = शून्य;

	info = call_usermodehelper_setup(modprobe_path, argv, envp, GFP_KERNEL,
					 शून्य, मुक्त_modprobe_argv, शून्य);
	अगर (!info)
		जाओ मुक्त_module_name;

	वापस call_usermodehelper_exec(info, रुको | UMH_KILLABLE);

मुक्त_module_name:
	kमुक्त(module_name);
मुक्त_argv:
	kमुक्त(argv);
out:
	वापस -ENOMEM;
पूर्ण

/**
 * __request_module - try to load a kernel module
 * @रुको: रुको (or not) क्रम the operation to complete
 * @fmt: म_लिखो style क्रमmat string क्रम the name of the module
 * @...: arguments as specअगरied in the क्रमmat string
 *
 * Load a module using the user mode module loader. The function वापसs
 * zero on success or a negative त्रुटि_सं code or positive निकास code from
 * "modprobe" on failure. Note that a successful module load करोes not mean
 * the module did not then unload and निकास on an error of its own. Callers
 * must check that the service they requested is now available not blindly
 * invoke it.
 *
 * If module स्वतः-loading support is disabled then this function
 * simply वापसs -ENOENT.
 */
पूर्णांक __request_module(bool रुको, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर module_name[MODULE_NAME_LEN];
	पूर्णांक ret;

	/*
	 * We करोn't allow synchronous module loading from async.  Module
	 * init may invoke async_synchronize_full() which will end up
	 * रुकोing क्रम this task which alपढ़ोy is रुकोing क्रम the module
	 * loading to complete, leading to a deadlock.
	 */
	WARN_ON_ONCE(रुको && current_is_async());

	अगर (!modprobe_path[0])
		वापस -ENOENT;

	बहु_शुरू(args, fmt);
	ret = vsnम_लिखो(module_name, MODULE_NAME_LEN, fmt, args);
	बहु_पूर्ण(args);
	अगर (ret >= MODULE_NAME_LEN)
		वापस -ENAMETOOLONG;

	ret = security_kernel_module_request(module_name);
	अगर (ret)
		वापस ret;

	अगर (atomic_dec_अगर_positive(&kmod_concurrent_max) < 0) अणु
		pr_warn_ratelimited("request_module: kmod_concurrent_max (%u) close to 0 (max_modprobes: %u), for module %s, throttling...",
				    atomic_पढ़ो(&kmod_concurrent_max),
				    MAX_KMOD_CONCURRENT, module_name);
		ret = रुको_event_समाप्तable_समयout(kmod_wq,
						  atomic_dec_अगर_positive(&kmod_concurrent_max) >= 0,
						  MAX_KMOD_ALL_BUSY_TIMEOUT * HZ);
		अगर (!ret) अणु
			pr_warn_ratelimited("request_module: modprobe %s cannot be processed, kmod busy with %d threads for more than %d seconds now",
					    module_name, MAX_KMOD_CONCURRENT, MAX_KMOD_ALL_BUSY_TIMEOUT);
			वापस -ETIME;
		पूर्ण अन्यथा अगर (ret == -ERESTARTSYS) अणु
			pr_warn_ratelimited("request_module: sigkill sent for modprobe %s, giving up", module_name);
			वापस ret;
		पूर्ण
	पूर्ण

	trace_module_request(module_name, रुको, _RET_IP_);

	ret = call_modprobe(module_name, रुको ? UMH_WAIT_PROC : UMH_WAIT_EXEC);

	atomic_inc(&kmod_concurrent_max);
	wake_up(&kmod_wq);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(__request_module);
