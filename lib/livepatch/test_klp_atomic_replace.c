<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Joe Lawrence <joe.lawrence@redhat.com>

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/livepatch.h>

अटल पूर्णांक replace;
module_param(replace, पूर्णांक, 0644);
MODULE_PARM_DESC(replace, "replace (default=0)");

#समावेश <linux/seq_file.h>
अटल पूर्णांक livepatch_meminfo_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "%s: %s\n", THIS_MODULE->name,
		   "this has been live patched");
	वापस 0;
पूर्ण

अटल काष्ठा klp_func funcs[] = अणु
	अणु
		.old_name = "meminfo_proc_show",
		.new_func = livepatch_meminfo_proc_show,
	पूर्ण, अणुपूर्ण
पूर्ण;

अटल काष्ठा klp_object objs[] = अणु
	अणु
		/* name being शून्य means vmlinux */
		.funcs = funcs,
	पूर्ण, अणुपूर्ण
पूर्ण;

अटल काष्ठा klp_patch patch = अणु
	.mod = THIS_MODULE,
	.objs = objs,
	/* set .replace in the init function below क्रम demo purposes */
पूर्ण;

अटल पूर्णांक test_klp_atomic_replace_init(व्योम)
अणु
	patch.replace = replace;
	वापस klp_enable_patch(&patch);
पूर्ण

अटल व्योम test_klp_atomic_replace_निकास(व्योम)
अणु
पूर्ण

module_init(test_klp_atomic_replace_init);
module_निकास(test_klp_atomic_replace_निकास);
MODULE_LICENSE("GPL");
MODULE_INFO(livepatch, "Y");
MODULE_AUTHOR("Joe Lawrence <joe.lawrence@redhat.com>");
MODULE_DESCRIPTION("Livepatch test: atomic replace");
