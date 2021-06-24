<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Joe Lawrence <joe.lawrence@redhat.com>
 */

/*
 * livepatch-callbacks-demo.c - (un)patching callbacks livepatch demo
 *
 *
 * Purpose
 * -------
 *
 * Demonstration of रेजिस्टरing livepatch (un)patching callbacks.
 *
 *
 * Usage
 * -----
 *
 * Step 1 - load the simple module
 *
 *   insmod samples/livepatch/livepatch-callbacks-mod.ko
 *
 *
 * Step 2 - load the demonstration livepatch (with callbacks)
 *
 *   insmod samples/livepatch/livepatch-callbacks-demo.ko
 *
 *
 * Step 3 - cleanup
 *
 *   echo 0 > /sys/kernel/livepatch/livepatch_callbacks_demo/enabled
 *   rmmod livepatch_callbacks_demo
 *   rmmod livepatch_callbacks_mod
 *
 * Watch dmesg output to see livepatch enablement, callback execution
 * and patching operations क्रम both vmlinux and module tarमाला_लो.
 *
 * NOTE: swap the insmod order of livepatch-callbacks-mod.ko and
 *       livepatch-callbacks-demo.ko to observe what happens when a
 *       target module is loaded after a livepatch with callbacks.
 *
 * NOTE: 'pre_patch_ret' is a module parameter that sets the pre-patch
 *       callback वापस status.  Try setting up a non-zero status
 *       such as -19 (-ENODEV):
 *
 *       # Load demo livepatch, vmlinux is patched
 *       insmod samples/livepatch/livepatch-callbacks-demo.ko
 *
 *       # Setup next pre-patch callback to वापस -ENODEV
 *       echo -19 > /sys/module/livepatch_callbacks_demo/parameters/pre_patch_ret
 *
 *       # Module loader refuses to load the target module
 *       insmod samples/livepatch/livepatch-callbacks-mod.ko
 *       insmod: ERROR: could not insert module samples/livepatch/livepatch-callbacks-mod.ko: No such device
 *
 * NOTE: There is a second target module,
 *       livepatch-callbacks-busymod.ko, available क्रम experimenting
 *       with livepatch (un)patch callbacks.  This module contains
 *       a 'sleep_secs' parameter that parks the module on one of the
 *       functions that the livepatch demo module wants to patch.
 *       Modअगरying this value and tweaking the order of module loads can
 *       effectively demonstrate stalled patch transitions:
 *
 *       # Load a target module, let it park on 'busymod_work_func' क्रम
 *       # thirty seconds
 *       insmod samples/livepatch/livepatch-callbacks-busymod.ko sleep_secs=30
 *
 *       # Meanजबतक load the livepatch
 *       insmod samples/livepatch/livepatch-callbacks-demo.ko
 *
 *       # ... then load and unload another target module जबतक the
 *       # transition is in progress
 *       insmod samples/livepatch/livepatch-callbacks-mod.ko
 *       rmmod samples/livepatch/livepatch-callbacks-mod.ko
 *
 *       # Finally cleanup
 *       echo 0 > /sys/kernel/livepatch/livepatch_callbacks_demo/enabled
 *       rmmod samples/livepatch/livepatch-callbacks-demo.ko
 */

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
	अणु पूर्ण
पूर्ण;

अटल काष्ठा klp_func busymod_funcs[] = अणु
	अणु
		.old_name = "busymod_work_func",
		.new_func = patched_work_func,
	पूर्ण, अणु पूर्ण
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
		.name = "livepatch_callbacks_mod",
		.funcs = no_funcs,
		.callbacks = अणु
			.pre_patch = pre_patch_callback,
			.post_patch = post_patch_callback,
			.pre_unpatch = pre_unpatch_callback,
			.post_unpatch = post_unpatch_callback,
		पूर्ण,
	पूर्ण,	अणु
		.name = "livepatch_callbacks_busymod",
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

अटल पूर्णांक livepatch_callbacks_demo_init(व्योम)
अणु
	वापस klp_enable_patch(&patch);
पूर्ण

अटल व्योम livepatch_callbacks_demo_निकास(व्योम)
अणु
पूर्ण

module_init(livepatch_callbacks_demo_init);
module_निकास(livepatch_callbacks_demo_निकास);
MODULE_LICENSE("GPL");
MODULE_INFO(livepatch, "Y");
