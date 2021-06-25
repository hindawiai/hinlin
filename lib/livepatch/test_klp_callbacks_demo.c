<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Joe Lawrence <joe.lawrence@redhat.com>

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/livepatch.h>

अटल पूर्णांक pre_patch_ret;
module_param(pre_patch_ret, पूर्णांक, 0644);
MODULE_PARM_DESC(pre_patch_ret, "pre_patch_ret (default=0)");

अटल स्थिर अक्षर *स्थिर module_state[] = अणु
	[MODULE_STATE_LIVE]	= "[MODULE_STATE_LIVE] Normal state",
	[MODULE_STATE_COMING]	= "[MODULE_STATE_COMING] Full formed, running module_init",
	[MODULE_STATE_GOING]	= "[MODULE_STATE_GOING] Going away",
	[MODULE_STATE_UNFORMED]	= "[MODULE_STATE_UNFORMED] Still setting it up",
पूर्ण;

अटल व्योम callback_info(स्थिर अक्षर *callback, काष्ठा klp_object *obj)
अणु
	अगर (obj->mod)
		pr_info("%s: %s -> %s\n", callback, obj->mod->name,
			module_state[obj->mod->state]);
	अन्यथा
		pr_info("%s: vmlinux\n", callback);
पूर्ण

/* Executed on object patching (ie, patch enablement) */
अटल पूर्णांक pre_patch_callback(काष्ठा klp_object *obj)
अणु
	callback_info(__func__, obj);
	वापस pre_patch_ret;
पूर्ण

/* Executed on object unpatching (ie, patch disablement) */
अटल व्योम post_patch_callback(काष्ठा klp_object *obj)
अणु
	callback_info(__func__, obj);
पूर्ण

/* Executed on object unpatching (ie, patch disablement) */
अटल व्योम pre_unpatch_callback(काष्ठा klp_object *obj)
अणु
	callback_info(__func__, obj);
पूर्ण

/* Executed on object unpatching (ie, patch disablement) */
अटल व्योम post_unpatch_callback(काष्ठा klp_object *obj)
अणु
	callback_info(__func__, obj);
पूर्ण

अटल व्योम patched_work_func(काष्ठा work_काष्ठा *work)
अणु
	pr_info("%s\n", __func__);
पूर्ण

अटल काष्ठा klp_func no_funcs[] = अणु
	अणुपूर्ण
पूर्ण;

अटल काष्ठा klp_func busymod_funcs[] = अणु
	अणु
		.old_name = "busymod_work_func",
		.new_func = patched_work_func,
	पूर्ण, अणुपूर्ण
पूर्ण;

अटल काष्ठा klp_object objs[] = अणु
	अणु
		.name = शून्य,	/* vmlinux */
		.funcs = no_funcs,
		.callbacks = अणु
			.pre_patch = pre_patch_callback,
			.post_patch = post_patch_callback,
			.pre_unpatch = pre_unpatch_callback,
			.post_unpatch = post_unpatch_callback,
		पूर्ण,
	पूर्ण,	अणु
		.name = "test_klp_callbacks_mod",
		.funcs = no_funcs,
		.callbacks = अणु
			.pre_patch = pre_patch_callback,
			.post_patch = post_patch_callback,
			.pre_unpatch = pre_unpatch_callback,
			.post_unpatch = post_unpatch_callback,
		पूर्ण,
	पूर्ण,	अणु
		.name = "test_klp_callbacks_busy",
		.funcs = busymod_funcs,
		.callbacks = अणु
			.pre_patch = pre_patch_callback,
			.post_patch = post_patch_callback,
			.pre_unpatch = pre_unpatch_callback,
			.post_unpatch = post_unpatch_callback,
		पूर्ण,
	पूर्ण, अणु पूर्ण
पूर्ण;

अटल काष्ठा klp_patch patch = अणु
	.mod = THIS_MODULE,
	.objs = objs,
पूर्ण;

अटल पूर्णांक test_klp_callbacks_demo_init(व्योम)
अणु
	वापस klp_enable_patch(&patch);
पूर्ण

अटल व्योम test_klp_callbacks_demo_निकास(व्योम)
अणु
पूर्ण

module_init(test_klp_callbacks_demo_init);
module_निकास(test_klp_callbacks_demo_निकास);
MODULE_LICENSE("GPL");
MODULE_INFO(livepatch, "Y");
MODULE_AUTHOR("Joe Lawrence <joe.lawrence@redhat.com>");
MODULE_DESCRIPTION("Livepatch test: livepatch demo");
