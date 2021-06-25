<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Based on the same principle as kgdboe using the NETPOLL api, this
 * driver uses a console polling api to implement a gdb serial पूर्णांकeface
 * which is multiplexed on a console port.
 *
 * Maपूर्णांकainer: Jason Wessel <jason.wessel@windriver.com>
 *
 * 2007-2008 (c) Jason Wessel - Wind River Systems, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kgdb.h>
#समावेश <linux/kdb.h>
#समावेश <linux/tty.h>
#समावेश <linux/console.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_core.h>

#घोषणा MAX_CONFIG_LEN		40

अटल काष्ठा kgdb_io		kgdboc_io_ops;

/* -1 = init not run yet, 0 = unconfigured, 1 = configured. */
अटल पूर्णांक configured		= -1;
अटल DEFINE_MUTEX(config_mutex);

अटल अक्षर config[MAX_CONFIG_LEN];
अटल काष्ठा kparam_string kps = अणु
	.string			= config,
	.maxlen			= MAX_CONFIG_LEN,
पूर्ण;

अटल पूर्णांक kgdboc_use_kms;  /* 1 अगर we use kernel mode चयनing */
अटल काष्ठा tty_driver	*kgdb_tty_driver;
अटल पूर्णांक			kgdb_tty_line;

अटल काष्ठा platक्रमm_device *kgdboc_pdev;

#अगर IS_BUILTIN(CONFIG_KGDB_SERIAL_CONSOLE)
अटल काष्ठा kgdb_io		kgdboc_earlycon_io_ops;
अटल पूर्णांक                      (*earlycon_orig_निकास)(काष्ठा console *con);
#पूर्ण_अगर /* IS_BUILTIN(CONFIG_KGDB_SERIAL_CONSOLE) */

#अगर_घोषित CONFIG_KDB_KEYBOARD
अटल पूर्णांक kgdboc_reset_connect(काष्ठा input_handler *handler,
				काष्ठा input_dev *dev,
				स्थिर काष्ठा input_device_id *id)
अणु
	input_reset_device(dev);

	/* Return an error - we करो not want to bind, just to reset */
	वापस -ENODEV;
पूर्ण

अटल व्योम kgdboc_reset_disconnect(काष्ठा input_handle *handle)
अणु
	/* We करो not expect anyone to actually bind to us */
	BUG();
पूर्ण

अटल स्थिर काष्ठा input_device_id kgdboc_reset_ids[] = अणु
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT,
		.evbit = अणु BIT_MASK(EV_KEY) पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा input_handler kgdboc_reset_handler = अणु
	.connect	= kgdboc_reset_connect,
	.disconnect	= kgdboc_reset_disconnect,
	.name		= "kgdboc_reset",
	.id_table	= kgdboc_reset_ids,
पूर्ण;

अटल DEFINE_MUTEX(kgdboc_reset_mutex);

अटल व्योम kgdboc_restore_input_helper(काष्ठा work_काष्ठा *dummy)
अणु
	/*
	 * We need to take a mutex to prevent several instances of
	 * this work running on dअगरferent CPUs so they करोn't try
	 * to रेजिस्टर again alपढ़ोy रेजिस्टरed handler.
	 */
	mutex_lock(&kgdboc_reset_mutex);

	अगर (input_रेजिस्टर_handler(&kgdboc_reset_handler) == 0)
		input_unरेजिस्टर_handler(&kgdboc_reset_handler);

	mutex_unlock(&kgdboc_reset_mutex);
पूर्ण

अटल DECLARE_WORK(kgdboc_restore_input_work, kgdboc_restore_input_helper);

अटल व्योम kgdboc_restore_input(व्योम)
अणु
	अगर (likely(प्रणाली_state == SYSTEM_RUNNING))
		schedule_work(&kgdboc_restore_input_work);
पूर्ण

अटल पूर्णांक kgdboc_रेजिस्टर_kbd(अक्षर **cptr)
अणु
	अगर (म_भेदन(*cptr, "kbd", 3) == 0 ||
		म_भेदन(*cptr, "kdb", 3) == 0) अणु
		अगर (kdb_poll_idx < KDB_POLL_FUNC_MAX) अणु
			kdb_poll_funcs[kdb_poll_idx] = kdb_get_kbd_अक्षर;
			kdb_poll_idx++;
			अगर (cptr[0][3] == ',')
				*cptr += 4;
			अन्यथा
				वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम kgdboc_unरेजिस्टर_kbd(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < kdb_poll_idx; i++) अणु
		अगर (kdb_poll_funcs[i] == kdb_get_kbd_अक्षर) अणु
			kdb_poll_idx--;
			kdb_poll_funcs[i] = kdb_poll_funcs[kdb_poll_idx];
			kdb_poll_funcs[kdb_poll_idx] = शून्य;
			i--;
		पूर्ण
	पूर्ण
	flush_work(&kgdboc_restore_input_work);
पूर्ण
#अन्यथा /* ! CONFIG_KDB_KEYBOARD */
#घोषणा kgdboc_रेजिस्टर_kbd(x) 0
#घोषणा kgdboc_unरेजिस्टर_kbd()
#घोषणा kgdboc_restore_input()
#पूर्ण_अगर /* ! CONFIG_KDB_KEYBOARD */

#अगर IS_BUILTIN(CONFIG_KGDB_SERIAL_CONSOLE)
अटल व्योम cleanup_earlycon(व्योम)
अणु
	अगर (kgdboc_earlycon_io_ops.cons)
		kgdb_unरेजिस्टर_io_module(&kgdboc_earlycon_io_ops);
पूर्ण
#अन्यथा /* !IS_BUILTIN(CONFIG_KGDB_SERIAL_CONSOLE) */
अटल अंतरभूत व्योम cleanup_earlycon(व्योम) अणु पूर्ण
#पूर्ण_अगर /* !IS_BUILTIN(CONFIG_KGDB_SERIAL_CONSOLE) */

अटल व्योम cleanup_kgdboc(व्योम)
अणु
	cleanup_earlycon();

	अगर (configured != 1)
		वापस;

	अगर (kgdb_unरेजिस्टर_nmi_console())
		वापस;
	kgdboc_unरेजिस्टर_kbd();
	kgdb_unरेजिस्टर_io_module(&kgdboc_io_ops);
पूर्ण

अटल पूर्णांक configure_kgdboc(व्योम)
अणु
	काष्ठा tty_driver *p;
	पूर्णांक tty_line = 0;
	पूर्णांक err = -ENODEV;
	अक्षर *cptr = config;
	काष्ठा console *cons;

	अगर (!म_माप(config) || है_खाली(config[0])) अणु
		err = 0;
		जाओ noconfig;
	पूर्ण

	kgdboc_io_ops.cons = शून्य;
	kgdb_tty_driver = शून्य;

	kgdboc_use_kms = 0;
	अगर (म_भेदन(cptr, "kms,", 4) == 0) अणु
		cptr += 4;
		kgdboc_use_kms = 1;
	पूर्ण

	अगर (kgdboc_रेजिस्टर_kbd(&cptr))
		जाओ करो_रेजिस्टर;

	p = tty_find_polling_driver(cptr, &tty_line);
	अगर (!p)
		जाओ noconfig;

	क्रम_each_console(cons) अणु
		पूर्णांक idx;
		अगर (cons->device && cons->device(cons, &idx) == p &&
		    idx == tty_line) अणु
			kgdboc_io_ops.cons = cons;
			अवरोध;
		पूर्ण
	पूर्ण

	kgdb_tty_driver = p;
	kgdb_tty_line = tty_line;

करो_रेजिस्टर:
	err = kgdb_रेजिस्टर_io_module(&kgdboc_io_ops);
	अगर (err)
		जाओ noconfig;

	err = kgdb_रेजिस्टर_nmi_console();
	अगर (err)
		जाओ nmi_con_failed;

	configured = 1;

	वापस 0;

nmi_con_failed:
	kgdb_unरेजिस्टर_io_module(&kgdboc_io_ops);
noconfig:
	kgdboc_unरेजिस्टर_kbd();
	configured = 0;

	वापस err;
पूर्ण

अटल पूर्णांक kgdboc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&config_mutex);
	अगर (configured != 1) अणु
		ret = configure_kgdboc();

		/* Convert "no device" to "defer" so we'll keep trying */
		अगर (ret == -ENODEV)
			ret = -EPROBE_DEFER;
	पूर्ण
	mutex_unlock(&config_mutex);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver kgdboc_platक्रमm_driver = अणु
	.probe = kgdboc_probe,
	.driver = अणु
		.name = "kgdboc",
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init init_kgdboc(व्योम)
अणु
	पूर्णांक ret;

	/*
	 * kgdboc is a little bit of an odd "platform_driver".  It can be
	 * up and running दीर्घ beक्रमe the platक्रमm_driver object is
	 * created and thus करोesn't actually store anything in it.  There's
	 * only one instance of kgdb so anything is stored as global state.
	 * The platक्रमm_driver is only created so that we can leverage the
	 * kernel's mechanisms (like -EPROBE_DEFER) to call us when our
	 * underlying tty is पढ़ोy.  Here we init our platक्रमm driver and
	 * then create the single kgdboc instance.
	 */
	ret = platक्रमm_driver_रेजिस्टर(&kgdboc_platक्रमm_driver);
	अगर (ret)
		वापस ret;

	kgdboc_pdev = platक्रमm_device_alloc("kgdboc", PLATFORM_DEVID_NONE);
	अगर (!kgdboc_pdev) अणु
		ret = -ENOMEM;
		जाओ err_did_रेजिस्टर;
	पूर्ण

	ret = platक्रमm_device_add(kgdboc_pdev);
	अगर (!ret)
		वापस 0;

	platक्रमm_device_put(kgdboc_pdev);

err_did_रेजिस्टर:
	platक्रमm_driver_unरेजिस्टर(&kgdboc_platक्रमm_driver);
	वापस ret;
पूर्ण

अटल व्योम निकास_kgdboc(व्योम)
अणु
	mutex_lock(&config_mutex);
	cleanup_kgdboc();
	mutex_unlock(&config_mutex);

	platक्रमm_device_unरेजिस्टर(kgdboc_pdev);
	platक्रमm_driver_unरेजिस्टर(&kgdboc_platक्रमm_driver);
पूर्ण

अटल पूर्णांक kgdboc_get_अक्षर(व्योम)
अणु
	अगर (!kgdb_tty_driver)
		वापस -1;
	वापस kgdb_tty_driver->ops->poll_get_अक्षर(kgdb_tty_driver,
						kgdb_tty_line);
पूर्ण

अटल व्योम kgdboc_put_अक्षर(u8 chr)
अणु
	अगर (!kgdb_tty_driver)
		वापस;
	kgdb_tty_driver->ops->poll_put_अक्षर(kgdb_tty_driver,
					kgdb_tty_line, chr);
पूर्ण

अटल पूर्णांक param_set_kgdboc_var(स्थिर अक्षर *kmessage,
				स्थिर काष्ठा kernel_param *kp)
अणु
	माप_प्रकार len = म_माप(kmessage);
	पूर्णांक ret = 0;

	अगर (len >= MAX_CONFIG_LEN) अणु
		pr_err("config string too long\n");
		वापस -ENOSPC;
	पूर्ण

	अगर (kgdb_connected) अणु
		pr_err("Cannot reconfigure while KGDB is connected.\n");
		वापस -EBUSY;
	पूर्ण

	mutex_lock(&config_mutex);

	म_नकल(config, kmessage);
	/* Chop out \न अक्षर as a result of echo */
	अगर (len && config[len - 1] == '\n')
		config[len - 1] = '\0';

	अगर (configured == 1)
		cleanup_kgdboc();

	/*
	 * Configure with the new params as दीर्घ as init alपढ़ोy ran.
	 * Note that we can get called beक्रमe init अगर someone loads us
	 * with "modprobe kgdboc kgdboc=..." or अगर they happen to use the
	 * the odd syntax of "kgdboc.kgdboc=..." on the kernel command.
	 */
	अगर (configured >= 0)
		ret = configure_kgdboc();

	/*
	 * If we couldn't configure then clear out the config.  Note that
	 * specअगरying an invalid config on the kernel command line vs.
	 * through sysfs have slightly dअगरferent behaviors.  If we fail
	 * to configure what was specअगरied on the kernel command line
	 * we'll leave it in the 'config' and वापस -EPROBE_DEFER from
	 * our probe.  When specअगरied through sysfs userspace is
	 * responsible क्रम loading the tty driver beक्रमe setting up.
	 */
	अगर (ret)
		config[0] = '\0';

	mutex_unlock(&config_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक dbg_restore_graphics;

अटल व्योम kgdboc_pre_exp_handler(व्योम)
अणु
	अगर (!dbg_restore_graphics && kgdboc_use_kms) अणु
		dbg_restore_graphics = 1;
		con_debug_enter(vc_cons[fg_console].d);
	पूर्ण
	/* Increment the module count when the debugger is active */
	अगर (!kgdb_connected)
		try_module_get(THIS_MODULE);
पूर्ण

अटल व्योम kgdboc_post_exp_handler(व्योम)
अणु
	/* decrement the module count when the debugger detaches */
	अगर (!kgdb_connected)
		module_put(THIS_MODULE);
	अगर (kgdboc_use_kms && dbg_restore_graphics) अणु
		dbg_restore_graphics = 0;
		con_debug_leave();
	पूर्ण
	kgdboc_restore_input();
पूर्ण

अटल काष्ठा kgdb_io kgdboc_io_ops = अणु
	.name			= "kgdboc",
	.पढ़ो_अक्षर		= kgdboc_get_अक्षर,
	.ग_लिखो_अक्षर		= kgdboc_put_अक्षर,
	.pre_exception		= kgdboc_pre_exp_handler,
	.post_exception		= kgdboc_post_exp_handler,
पूर्ण;

#अगर IS_BUILTIN(CONFIG_KGDB_SERIAL_CONSOLE)
अटल पूर्णांक kgdboc_option_setup(अक्षर *opt)
अणु
	अगर (!opt) अणु
		pr_err("config string not provided\n");
		वापस -EINVAL;
	पूर्ण

	अगर (म_माप(opt) >= MAX_CONFIG_LEN) अणु
		pr_err("config string too long\n");
		वापस -ENOSPC;
	पूर्ण
	म_नकल(config, opt);

	वापस 0;
पूर्ण

__setup("kgdboc=", kgdboc_option_setup);


/* This is only available अगर kgdboc is a built in क्रम early debugging */
अटल पूर्णांक __init kgdboc_early_init(अक्षर *opt)
अणु
	kgdboc_option_setup(opt);
	configure_kgdboc();
	वापस 0;
पूर्ण

early_param("ekgdboc", kgdboc_early_init);

अटल पूर्णांक kgdboc_earlycon_get_अक्षर(व्योम)
अणु
	अक्षर c;

	अगर (!kgdboc_earlycon_io_ops.cons->पढ़ो(kgdboc_earlycon_io_ops.cons,
					       &c, 1))
		वापस NO_POLL_CHAR;

	वापस c;
पूर्ण

अटल व्योम kgdboc_earlycon_put_अक्षर(u8 chr)
अणु
	kgdboc_earlycon_io_ops.cons->ग_लिखो(kgdboc_earlycon_io_ops.cons, &chr,
					   1);
पूर्ण

अटल व्योम kgdboc_earlycon_pre_exp_handler(व्योम)
अणु
	काष्ठा console *con;
	अटल bool alपढ़ोy_warned;

	अगर (alपढ़ोy_warned)
		वापस;

	/*
	 * When the first normal console comes up the kernel will take all
	 * the boot consoles out of the list.  Really, we should stop using
	 * the boot console when it करोes that but until a TTY is रेजिस्टरed
	 * we have no other choice so we keep using it.  Since not all
	 * serial drivers might be OK with this, prपूर्णांक a warning once per
	 * boot अगर we detect this हाल.
	 */
	क्रम_each_console(con)
		अगर (con == kgdboc_earlycon_io_ops.cons)
			वापस;

	alपढ़ोy_warned = true;
	pr_warn("kgdboc_earlycon is still using bootconsole\n");
पूर्ण

अटल पूर्णांक kgdboc_earlycon_deferred_निकास(काष्ठा console *con)
अणु
	/*
	 * If we get here it means the boot console is going away but we
	 * करोn't yet have a suitable replacement.  Don't pass through to
	 * the original निकास routine.  We'll call it later in our deinit()
	 * function.  For now, restore the original निकास() function poपूर्णांकer
	 * as a sentinal that we've hit this poपूर्णांक.
	 */
	con->निकास = earlycon_orig_निकास;

	वापस 0;
पूर्ण

अटल व्योम kgdboc_earlycon_deinit(व्योम)
अणु
	अगर (!kgdboc_earlycon_io_ops.cons)
		वापस;

	अगर (kgdboc_earlycon_io_ops.cons->निकास == kgdboc_earlycon_deferred_निकास)
		/*
		 * kgdboc_earlycon is निकासing but original boot console निकास
		 * was never called (AKA kgdboc_earlycon_deferred_निकास()
		 * didn't ever run).  Unकरो our trap.
		 */
		kgdboc_earlycon_io_ops.cons->निकास = earlycon_orig_निकास;
	अन्यथा अगर (kgdboc_earlycon_io_ops.cons->निकास)
		/*
		 * We skipped calling the निकास() routine so we could try to
		 * keep using the boot console even after it went away.  We're
		 * finally करोne so call the function now.
		 */
		kgdboc_earlycon_io_ops.cons->निकास(kgdboc_earlycon_io_ops.cons);

	kgdboc_earlycon_io_ops.cons = शून्य;
पूर्ण

अटल काष्ठा kgdb_io kgdboc_earlycon_io_ops = अणु
	.name			= "kgdboc_earlycon",
	.पढ़ो_अक्षर		= kgdboc_earlycon_get_अक्षर,
	.ग_लिखो_अक्षर		= kgdboc_earlycon_put_अक्षर,
	.pre_exception		= kgdboc_earlycon_pre_exp_handler,
	.deinit			= kgdboc_earlycon_deinit,
पूर्ण;

#घोषणा MAX_CONSOLE_NAME_LEN (माप((काष्ठा console *) 0)->name)
अटल अक्षर kgdboc_earlycon_param[MAX_CONSOLE_NAME_LEN] __initdata;
अटल bool kgdboc_earlycon_late_enable __initdata;

अटल पूर्णांक __init kgdboc_earlycon_init(अक्षर *opt)
अणु
	काष्ठा console *con;

	kdb_init(KDB_INIT_EARLY);

	/*
	 * Look क्रम a matching console, or अगर the name was left blank just
	 * pick the first one we find.
	 */
	console_lock();
	क्रम_each_console(con) अणु
		अगर (con->ग_लिखो && con->पढ़ो &&
		    (con->flags & (CON_BOOT | CON_ENABLED)) &&
		    (!opt || !opt[0] || म_भेद(con->name, opt) == 0))
			अवरोध;
	पूर्ण

	अगर (!con) अणु
		/*
		 * Both earlycon and kgdboc_earlycon are initialized during
		 * early parameter parsing. We cannot guarantee earlycon माला_लो
		 * in first and, in any हाल, on ACPI प्रणालीs earlycon may
		 * defer its own initialization (usually to somewhere within
		 * setup_arch() ). To cope with either of these situations
		 * we can defer our own initialization to a little later in
		 * the boot.
		 */
		अगर (!kgdboc_earlycon_late_enable) अणु
			pr_info("No suitable earlycon yet, will try later\n");
			अगर (opt)
				strscpy(kgdboc_earlycon_param, opt,
					माप(kgdboc_earlycon_param));
			kgdboc_earlycon_late_enable = true;
		पूर्ण अन्यथा अणु
			pr_info("Couldn't find kgdb earlycon\n");
		पूर्ण
		जाओ unlock;
	पूर्ण

	kgdboc_earlycon_io_ops.cons = con;
	pr_info("Going to register kgdb with earlycon '%s'\n", con->name);
	अगर (kgdb_रेजिस्टर_io_module(&kgdboc_earlycon_io_ops) != 0) अणु
		kgdboc_earlycon_io_ops.cons = शून्य;
		pr_info("Failed to register kgdb with earlycon\n");
	पूर्ण अन्यथा अणु
		/* Trap निकास so we can keep earlycon दीर्घer अगर needed. */
		earlycon_orig_निकास = con->निकास;
		con->निकास = kgdboc_earlycon_deferred_निकास;
	पूर्ण

unlock:
	console_unlock();

	/* Non-zero means malक्रमmed option so we always वापस zero */
	वापस 0;
पूर्ण

early_param("kgdboc_earlycon", kgdboc_earlycon_init);

/*
 * This is only पूर्णांकended क्रम the late aकरोption of an early console.
 *
 * It is not a reliable way to aकरोpt regular consoles because we can not
 * control what order console initcalls are made and, in any हाल, many
 * regular consoles are रेजिस्टरed much later in the boot process than
 * the console initcalls!
 */
अटल पूर्णांक __init kgdboc_earlycon_late_init(व्योम)
अणु
	अगर (kgdboc_earlycon_late_enable)
		kgdboc_earlycon_init(kgdboc_earlycon_param);
	वापस 0;
पूर्ण
console_initcall(kgdboc_earlycon_late_init);

#पूर्ण_अगर /* IS_BUILTIN(CONFIG_KGDB_SERIAL_CONSOLE) */

module_init(init_kgdboc);
module_निकास(निकास_kgdboc);
module_param_call(kgdboc, param_set_kgdboc_var, param_get_string, &kps, 0644);
MODULE_PARM_DESC(kgdboc, "<serial_device>[,baud]");
MODULE_DESCRIPTION("KGDB Console TTY Driver");
MODULE_LICENSE("GPL");
