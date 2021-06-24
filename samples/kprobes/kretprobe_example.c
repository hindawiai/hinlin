<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kretprobe_example.c
 *
 * Here's a sample kernel module showing the use of वापस probes to
 * report the वापस value and total समय taken क्रम probed function
 * to run.
 *
 * usage: insmod kretprobe_example.ko func=<func_name>
 *
 * If no func_name is specअगरied, kernel_clone is instrumented
 *
 * For more inक्रमmation on theory of operation of kretprobes, see
 * Documentation/trace/kprobes.rst
 *
 * Build and insert the kernel module as करोne in the kprobe example.
 * You will see the trace data in /var/log/messages and on the console
 * whenever the probed function वापसs. (Some messages may be suppressed
 * अगर syslogd is configured to eliminate duplicate messages.)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/सीमा.स>
#समावेश <linux/sched.h>

अटल अक्षर func_name[NAME_MAX] = "kernel_clone";
module_param_string(func, func_name, NAME_MAX, S_IRUGO);
MODULE_PARM_DESC(func, "Function to kretprobe; this module will report the"
			" function's execution time");

/* per-instance निजी data */
काष्ठा my_data अणु
	kसमय_प्रकार entry_stamp;
पूर्ण;

/* Here we use the entry_hanlder to बारtamp function entry */
अटल पूर्णांक entry_handler(काष्ठा kretprobe_instance *ri, काष्ठा pt_regs *regs)
अणु
	काष्ठा my_data *data;

	अगर (!current->mm)
		वापस 1;	/* Skip kernel thपढ़ोs */

	data = (काष्ठा my_data *)ri->data;
	data->entry_stamp = kसमय_get();
	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(entry_handler);

/*
 * Return-probe handler: Log the वापस value and duration. Duration may turn
 * out to be zero consistently, depending upon the granularity of समय
 * accounting on the platक्रमm.
 */
अटल पूर्णांक ret_handler(काष्ठा kretprobe_instance *ri, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ retval = regs_वापस_value(regs);
	काष्ठा my_data *data = (काष्ठा my_data *)ri->data;
	s64 delta;
	kसमय_प्रकार now;

	now = kसमय_get();
	delta = kसमय_प्रकारo_ns(kसमय_sub(now, data->entry_stamp));
	pr_info("%s returned %lu and took %lld ns to execute\n",
			func_name, retval, (दीर्घ दीर्घ)delta);
	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(ret_handler);

अटल काष्ठा kretprobe my_kretprobe = अणु
	.handler		= ret_handler,
	.entry_handler		= entry_handler,
	.data_size		= माप(काष्ठा my_data),
	/* Probe up to 20 instances concurrently. */
	.maxactive		= 20,
पूर्ण;

अटल पूर्णांक __init kretprobe_init(व्योम)
अणु
	पूर्णांक ret;

	my_kretprobe.kp.symbol_name = func_name;
	ret = रेजिस्टर_kretprobe(&my_kretprobe);
	अगर (ret < 0) अणु
		pr_err("register_kretprobe failed, returned %d\n", ret);
		वापस -1;
	पूर्ण
	pr_info("Planted return probe at %s: %p\n",
			my_kretprobe.kp.symbol_name, my_kretprobe.kp.addr);
	वापस 0;
पूर्ण

अटल व्योम __निकास kretprobe_निकास(व्योम)
अणु
	unरेजिस्टर_kretprobe(&my_kretprobe);
	pr_info("kretprobe at %p unregistered\n", my_kretprobe.kp.addr);

	/* nmissed > 0 suggests that maxactive was set too low. */
	pr_info("Missed probing %d instances of %s\n",
		my_kretprobe.nmissed, my_kretprobe.kp.symbol_name);
पूर्ण

module_init(kretprobe_init)
module_निकास(kretprobe_निकास)
MODULE_LICENSE("GPL");
