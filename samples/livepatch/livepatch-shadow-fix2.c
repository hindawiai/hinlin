<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Joe Lawrence <joe.lawrence@redhat.com>
 */

/*
 * livepatch-shaकरोw-fix2.c - Shaकरोw variables, livepatch demo
 *
 * Purpose
 * -------
 *
 * Adds functionality to livepatch-shaकरोw-mod's in-flight data
 * काष्ठाures through a shaकरोw variable.  The livepatch patches a
 * routine that periodically inspects data काष्ठाures, incrementing a
 * per-data-काष्ठाure counter, creating the counter अगर needed.
 *
 *
 * Usage
 * -----
 *
 * This module is not पूर्णांकended to be standalone.  See the "Usage"
 * section of livepatch-shaकरोw-mod.c.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/livepatch.h>
#समावेश <linux/slab.h>

/* Shaकरोw variable क्रमागतs */
#घोषणा SV_LEAK		1
#घोषणा SV_COUNTER	2

काष्ठा dummy अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ jअगरfies_expire;
पूर्ण;

अटल bool livepatch_fix2_dummy_check(काष्ठा dummy *d, अचिन्हित दीर्घ jअगरfies)
अणु
	पूर्णांक *shaकरोw_count;

	/*
	 * Patch: handle in-flight dummy काष्ठाures, अगर they करो not
	 * alपढ़ोy have a SV_COUNTER shaकरोw variable, then attach a
	 * new one.
	 */
	shaकरोw_count = klp_shaकरोw_get_or_alloc(d, SV_COUNTER,
				माप(*shaकरोw_count), GFP_NOWAIT,
				शून्य, शून्य);
	अगर (shaकरोw_count)
		*shaकरोw_count += 1;

	वापस समय_after(jअगरfies, d->jअगरfies_expire);
पूर्ण

अटल व्योम livepatch_fix2_dummy_leak_dtor(व्योम *obj, व्योम *shaकरोw_data)
अणु
	व्योम *d = obj;
	पूर्णांक **shaकरोw_leak = shaकरोw_data;

	kमुक्त(*shaकरोw_leak);
	pr_info("%s: dummy @ %p, prevented leak @ %p\n",
			 __func__, d, *shaकरोw_leak);
पूर्ण

अटल व्योम livepatch_fix2_dummy_मुक्त(काष्ठा dummy *d)
अणु
	पूर्णांक **shaकरोw_leak;
	पूर्णांक *shaकरोw_count;

	/* Patch: copy the memory leak patch from the fix1 module. */
	shaकरोw_leak = klp_shaकरोw_get(d, SV_LEAK);
	अगर (shaकरोw_leak)
		klp_shaकरोw_मुक्त(d, SV_LEAK, livepatch_fix2_dummy_leak_dtor);
	अन्यथा
		pr_info("%s: dummy @ %p leaked!\n", __func__, d);

	/*
	 * Patch: fetch the SV_COUNTER shaकरोw variable and display
	 * the final count.  Detach the shaकरोw variable.
	 */
	shaकरोw_count = klp_shaकरोw_get(d, SV_COUNTER);
	अगर (shaकरोw_count) अणु
		pr_info("%s: dummy @ %p, check counter = %d\n",
			__func__, d, *shaकरोw_count);
		klp_shaकरोw_मुक्त(d, SV_COUNTER, शून्य);
	पूर्ण

	kमुक्त(d);
पूर्ण

अटल काष्ठा klp_func funcs[] = अणु
	अणु
		.old_name = "dummy_check",
		.new_func = livepatch_fix2_dummy_check,
	पूर्ण,
	अणु
		.old_name = "dummy_free",
		.new_func = livepatch_fix2_dummy_मुक्त,
	पूर्ण, अणु पूर्ण
पूर्ण;

अटल काष्ठा klp_object objs[] = अणु
	अणु
		.name = "livepatch_shadow_mod",
		.funcs = funcs,
	पूर्ण, अणु पूर्ण
पूर्ण;

अटल काष्ठा klp_patch patch = अणु
	.mod = THIS_MODULE,
	.objs = objs,
पूर्ण;

अटल पूर्णांक livepatch_shaकरोw_fix2_init(व्योम)
अणु
	वापस klp_enable_patch(&patch);
पूर्ण

अटल व्योम livepatch_shaकरोw_fix2_निकास(व्योम)
अणु
	/* Cleanup any existing SV_COUNTER shaकरोw variables */
	klp_shaकरोw_मुक्त_all(SV_COUNTER, शून्य);
पूर्ण

module_init(livepatch_shaकरोw_fix2_init);
module_निकास(livepatch_shaकरोw_fix2_निकास);
MODULE_LICENSE("GPL");
MODULE_INFO(livepatch, "Y");
