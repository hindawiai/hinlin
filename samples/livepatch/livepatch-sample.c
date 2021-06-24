<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * livepatch-sample.c - Kernel Live Patching Sample Module
 *
 * Copyright (C) 2014 Seth Jennings <sjenning@redhat.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/livepatch.h>

/*
 * This (dumb) live patch overrides the function that prपूर्णांकs the
 * kernel boot cmdline when /proc/cmdline is पढ़ो.
 *
 * Example:
 *
 * $ cat /proc/cmdline
 * <your cmdline>
 *
 * $ insmod livepatch-sample.ko
 * $ cat /proc/cmdline
 * this has been live patched
 *
 * $ echo 0 > /sys/kernel/livepatch/livepatch_sample/enabled
 * $ cat /proc/cmdline
 * <your cmdline>
 */

#समावेश <linux/seq_file.h>
अटल पूर्णांक livepatch_cmdline_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "%s\n", "this has been live patched");
	वापस 0;
पूर्ण

अटल काष्ठा klp_func funcs[] = अणु
	अणु
		.old_name = "cmdline_proc_show",
		.new_func = livepatch_cmdline_proc_show,
	पूर्ण, अणु पूर्ण
पूर्ण;

अटल काष्ठा klp_object objs[] = अणु
	अणु
		/* name being शून्य means vmlinux */
		.funcs = funcs,
	पूर्ण, अणु पूर्ण
पूर्ण;

अटल काष्ठा klp_patch patch = अणु
	.mod = THIS_MODULE,
	.objs = objs,
पूर्ण;

अटल पूर्णांक livepatch_init(व्योम)
अणु
	वापस klp_enable_patch(&patch);
पूर्ण

अटल व्योम livepatch_निकास(व्योम)
अणु
पूर्ण

module_init(livepatch_init);
module_निकास(livepatch_निकास);
MODULE_LICENSE("GPL");
MODULE_INFO(livepatch, "Y");
