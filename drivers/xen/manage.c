<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Handle बाह्य requests क्रम shutकरोwn, reboot and sysrq
 */

#घोषणा pr_fmt(fmt) "xen:" KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/reboot.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/export.h>

#समावेश <xen/xen.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/events.h>
#समावेश <xen/hvc-console.h>
#समावेश <xen/page.h>
#समावेश <xen/xen-ops.h>

#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/xen/hypervisor.h>

क्रमागत shutकरोwn_state अणु
	SHUTDOWN_INVALID = -1,
	SHUTDOWN_POWEROFF = 0,
	SHUTDOWN_SUSPEND = 2,
	/* Code 3 is SHUTDOWN_CRASH, which we करोn't use because the करोमुख्य can only
	   report a crash, not be inकाष्ठाed to crash!
	   HALT is the same as POWEROFF, as far as we're concerned.  The tools use
	   the distinction when we वापस the reason code to them.  */
	 SHUTDOWN_HALT = 4,
पूर्ण;

/* Ignore multiple shutकरोwn requests. */
अटल क्रमागत shutकरोwn_state shutting_करोwn = SHUTDOWN_INVALID;

काष्ठा suspend_info अणु
	पूर्णांक cancelled;
पूर्ण;

अटल RAW_NOTIFIER_HEAD(xen_resume_notअगरier);

व्योम xen_resume_notअगरier_रेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	raw_notअगरier_chain_रेजिस्टर(&xen_resume_notअगरier, nb);
पूर्ण
EXPORT_SYMBOL_GPL(xen_resume_notअगरier_रेजिस्टर);

व्योम xen_resume_notअगरier_unरेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	raw_notअगरier_chain_unरेजिस्टर(&xen_resume_notअगरier, nb);
पूर्ण
EXPORT_SYMBOL_GPL(xen_resume_notअगरier_unरेजिस्टर);

#अगर_घोषित CONFIG_HIBERNATE_CALLBACKS
अटल पूर्णांक xen_suspend(व्योम *data)
अणु
	काष्ठा suspend_info *si = data;
	पूर्णांक err;

	BUG_ON(!irqs_disabled());

	err = syscore_suspend();
	अगर (err) अणु
		pr_err("%s: system core suspend failed: %d\n", __func__, err);
		वापस err;
	पूर्ण

	gnttab_suspend();
	xen_manage_runstate_समय(-1);
	xen_arch_pre_suspend();

	si->cancelled = HYPERVISOR_suspend(xen_pv_करोमुख्य()
                                           ? virt_to_gfn(xen_start_info)
                                           : 0);

	xen_arch_post_suspend(si->cancelled);
	xen_manage_runstate_समय(si->cancelled ? 1 : 0);
	gnttab_resume();

	अगर (!si->cancelled) अणु
		xen_irq_resume();
		xen_समयr_resume();
	पूर्ण

	syscore_resume();

	वापस 0;
पूर्ण

अटल व्योम करो_suspend(व्योम)
अणु
	पूर्णांक err;
	काष्ठा suspend_info si;

	shutting_करोwn = SHUTDOWN_SUSPEND;

	err = मुक्तze_processes();
	अगर (err) अणु
		pr_err("%s: freeze processes failed %d\n", __func__, err);
		जाओ out;
	पूर्ण

	err = मुक्तze_kernel_thपढ़ोs();
	अगर (err) अणु
		pr_err("%s: freeze kernel threads failed %d\n", __func__, err);
		जाओ out_thaw;
	पूर्ण

	err = dpm_suspend_start(PMSG_FREEZE);
	अगर (err) अणु
		pr_err("%s: dpm_suspend_start %d\n", __func__, err);
		जाओ out_thaw;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "suspending xenstore...\n");
	xs_suspend();

	err = dpm_suspend_end(PMSG_FREEZE);
	अगर (err) अणु
		pr_err("dpm_suspend_end failed: %d\n", err);
		si.cancelled = 0;
		जाओ out_resume;
	पूर्ण

	xen_arch_suspend();

	si.cancelled = 1;

	err = stop_machine(xen_suspend, &si, cpumask_of(0));

	/* Resume console as early as possible. */
	अगर (!si.cancelled)
		xen_console_resume();

	raw_notअगरier_call_chain(&xen_resume_notअगरier, 0, शून्य);

	dpm_resume_start(si.cancelled ? PMSG_THAW : PMSG_RESTORE);

	अगर (err) अणु
		pr_err("failed to start xen_suspend: %d\n", err);
		si.cancelled = 1;
	पूर्ण

	xen_arch_resume();

out_resume:
	अगर (!si.cancelled)
		xs_resume();
	अन्यथा
		xs_suspend_cancel();

	dpm_resume_end(si.cancelled ? PMSG_THAW : PMSG_RESTORE);

out_thaw:
	thaw_processes();
out:
	shutting_करोwn = SHUTDOWN_INVALID;
पूर्ण
#पूर्ण_अगर	/* CONFIG_HIBERNATE_CALLBACKS */

काष्ठा shutकरोwn_handler अणु
#घोषणा SHUTDOWN_CMD_SIZE 11
	स्थिर अक्षर command[SHUTDOWN_CMD_SIZE];
	bool flag;
	व्योम (*cb)(व्योम);
पूर्ण;

अटल पूर्णांक घातeroff_nb(काष्ठा notअगरier_block *cb, अचिन्हित दीर्घ code, व्योम *unused)
अणु
	चयन (code) अणु
	हाल SYS_DOWN:
	हाल SYS_HALT:
	हाल SYS_POWER_OFF:
		shutting_करोwn = SHUTDOWN_POWEROFF;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण
अटल व्योम करो_घातeroff(व्योम)
अणु
	चयन (प्रणाली_state) अणु
	हाल SYSTEM_BOOTING:
	हाल SYSTEM_SCHEDULING:
		orderly_घातeroff(true);
		अवरोध;
	हाल SYSTEM_RUNNING:
		orderly_घातeroff(false);
		अवरोध;
	शेष:
		/* Don't करो it when we are halting/rebooting. */
		pr_info("Ignoring Xen toolstack shutdown.\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम करो_reboot(व्योम)
अणु
	shutting_करोwn = SHUTDOWN_POWEROFF; /* ? */
	ctrl_alt_del();
पूर्ण

अटल काष्ठा shutकरोwn_handler shutकरोwn_handlers[] = अणु
	अणु "poweroff",	true,	करो_घातeroff पूर्ण,
	अणु "halt",	false,	करो_घातeroff पूर्ण,
	अणु "reboot",	true,	करो_reboot   पूर्ण,
#अगर_घोषित CONFIG_HIBERNATE_CALLBACKS
	अणु "suspend",	true,	करो_suspend  पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल व्योम shutकरोwn_handler(काष्ठा xenbus_watch *watch,
			     स्थिर अक्षर *path, स्थिर अक्षर *token)
अणु
	अक्षर *str;
	काष्ठा xenbus_transaction xbt;
	पूर्णांक err;
	पूर्णांक idx;

	अगर (shutting_करोwn != SHUTDOWN_INVALID)
		वापस;

 again:
	err = xenbus_transaction_start(&xbt);
	अगर (err)
		वापस;

	str = (अक्षर *)xenbus_पढ़ो(xbt, "control", "shutdown", शून्य);
	/* Ignore पढ़ो errors and empty पढ़ोs. */
	अगर (XENBUS_IS_ERR_READ(str)) अणु
		xenbus_transaction_end(xbt, 1);
		वापस;
	पूर्ण

	क्रम (idx = 0; idx < ARRAY_SIZE(shutकरोwn_handlers); idx++) अणु
		अगर (म_भेद(str, shutकरोwn_handlers[idx].command) == 0)
			अवरोध;
	पूर्ण

	/* Only acknowledge commands which we are prepared to handle. */
	अगर (idx < ARRAY_SIZE(shutकरोwn_handlers))
		xenbus_ग_लिखो(xbt, "control", "shutdown", "");

	err = xenbus_transaction_end(xbt, 0);
	अगर (err == -EAGAIN) अणु
		kमुक्त(str);
		जाओ again;
	पूर्ण

	अगर (idx < ARRAY_SIZE(shutकरोwn_handlers)) अणु
		shutकरोwn_handlers[idx].cb();
	पूर्ण अन्यथा अणु
		pr_info("Ignoring shutdown request: %s\n", str);
		shutting_करोwn = SHUTDOWN_INVALID;
	पूर्ण

	kमुक्त(str);
पूर्ण

#अगर_घोषित CONFIG_MAGIC_SYSRQ
अटल व्योम sysrq_handler(काष्ठा xenbus_watch *watch, स्थिर अक्षर *path,
			  स्थिर अक्षर *token)
अणु
	अक्षर sysrq_key = '\0';
	काष्ठा xenbus_transaction xbt;
	पूर्णांक err;

 again:
	err = xenbus_transaction_start(&xbt);
	अगर (err)
		वापस;
	err = xenbus_म_पूछो(xbt, "control", "sysrq", "%c", &sysrq_key);
	अगर (err < 0) अणु
		/*
		 * The Xenstore watch fires directly after रेजिस्टरing it and
		 * after a suspend/resume cycle. So ENOENT is no error but
		 * might happen in those हालs. दुस्फल is observed when we get
		 * an empty value (''), this happens when we acknowledge the
		 * request by writing '\0' below.
		 */
		अगर (err != -ENOENT && err != -दुस्फल)
			pr_err("Error %d reading sysrq code in control/sysrq\n",
			       err);
		xenbus_transaction_end(xbt, 1);
		वापस;
	पूर्ण

	अगर (sysrq_key != '\0') अणु
		err = xenbus_म_लिखो(xbt, "control", "sysrq", "%c", '\0');
		अगर (err) अणु
			pr_err("%s: Error %d writing sysrq in control/sysrq\n",
			       __func__, err);
			xenbus_transaction_end(xbt, 1);
			वापस;
		पूर्ण
	पूर्ण

	err = xenbus_transaction_end(xbt, 0);
	अगर (err == -EAGAIN)
		जाओ again;

	अगर (sysrq_key != '\0')
		handle_sysrq(sysrq_key);
पूर्ण

अटल काष्ठा xenbus_watch sysrq_watch = अणु
	.node = "control/sysrq",
	.callback = sysrq_handler
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा xenbus_watch shutकरोwn_watch = अणु
	.node = "control/shutdown",
	.callback = shutकरोwn_handler
पूर्ण;

अटल काष्ठा notअगरier_block xen_reboot_nb = अणु
	.notअगरier_call = घातeroff_nb,
पूर्ण;

अटल पूर्णांक setup_shutकरोwn_watcher(व्योम)
अणु
	पूर्णांक err;
	पूर्णांक idx;
#घोषणा FEATURE_PATH_SIZE (SHUTDOWN_CMD_SIZE + माप("feature-"))
	अक्षर node[FEATURE_PATH_SIZE];

	err = रेजिस्टर_xenbus_watch(&shutकरोwn_watch);
	अगर (err) अणु
		pr_err("Failed to set shutdown watcher\n");
		वापस err;
	पूर्ण


#अगर_घोषित CONFIG_MAGIC_SYSRQ
	err = रेजिस्टर_xenbus_watch(&sysrq_watch);
	अगर (err) अणु
		pr_err("Failed to set sysrq watcher\n");
		वापस err;
	पूर्ण
#पूर्ण_अगर

	क्रम (idx = 0; idx < ARRAY_SIZE(shutकरोwn_handlers); idx++) अणु
		अगर (!shutकरोwn_handlers[idx].flag)
			जारी;
		snम_लिखो(node, FEATURE_PATH_SIZE, "feature-%s",
			 shutकरोwn_handlers[idx].command);
		err = xenbus_म_लिखो(XBT_NIL, "control", node, "%u", 1);
		अगर (err) अणु
			pr_err("%s: Error %d writing %s\n", __func__,
				err, node);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक shutकरोwn_event(काष्ठा notअगरier_block *notअगरier,
			  अचिन्हित दीर्घ event,
			  व्योम *data)
अणु
	setup_shutकरोwn_watcher();
	वापस NOTIFY_DONE;
पूर्ण

पूर्णांक xen_setup_shutकरोwn_event(व्योम)
अणु
	अटल काष्ठा notअगरier_block xenstore_notअगरier = अणु
		.notअगरier_call = shutकरोwn_event
	पूर्ण;

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;
	रेजिस्टर_xenstore_notअगरier(&xenstore_notअगरier);
	रेजिस्टर_reboot_notअगरier(&xen_reboot_nb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xen_setup_shutकरोwn_event);

subsys_initcall(xen_setup_shutकरोwn_event);
