<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Joe Lawrence <joe.lawrence@redhat.com>
 */

/*
 * livepatch-shaकरोw-fix1.c - Shaकरोw variables, livepatch demo
 *
 * Purpose
 * -------
 *
 * Fixes the memory leak पूर्णांकroduced in livepatch-shaकरोw-mod through the
 * use of a shaकरोw variable.  This fix demonstrates the "extending" of
 * लघु-lived data काष्ठाures by patching its allocation and release
 * functions.
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

/* Allocate new dummies every second */
#घोषणा ALLOC_PERIOD	1
/* Check क्रम expired dummies after a few new ones have been allocated */
#घोषणा CLEANUP_PERIOD	(3 * ALLOC_PERIOD)
/* Dummies expire after a few cleanup instances */
#घोषणा EXPIRE_PERIOD	(4 * CLEANUP_PERIOD)

काष्ठा dummy अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ jअगरfies_expire;
पूर्ण;

/*
 * The स्थिरructor makes more sense together with klp_shaकरोw_get_or_alloc().
 * In this example, it would be safe to assign the poपूर्णांकer also to the shaकरोw
 * variable वापसed by klp_shaकरोw_alloc().  But we wanted to show the more
 * complicated use of the API.
 */
अटल पूर्णांक shaकरोw_leak_ctor(व्योम *obj, व्योम *shaकरोw_data, व्योम *ctor_data)
अणु
	पूर्णांक **shaकरोw_leak = shaकरोw_data;
	पूर्णांक **leak = ctor_data;

	अगर (!ctor_data)
		वापस -EINVAL;

	*shaकरोw_leak = *leak;
	वापस 0;
पूर्ण

अटल काष्ठा dummy *livepatch_fix1_dummy_alloc(व्योम)
अणु
	काष्ठा dummy *d;
	पूर्णांक *leak;
	पूर्णांक **shaकरोw_leak;

	d = kzalloc(माप(*d), GFP_KERNEL);
	अगर (!d)
		वापस शून्य;

	d->jअगरfies_expire = jअगरfies +
		msecs_to_jअगरfies(1000 * EXPIRE_PERIOD);

	/*
	 * Patch: save the extra memory location पूर्णांकo a SV_LEAK shaकरोw
	 * variable.  A patched dummy_मुक्त routine can later fetch this
	 * poपूर्णांकer to handle resource release.
	 */
	leak = kzalloc(माप(*leak), GFP_KERNEL);
	अगर (!leak)
		जाओ err_leak;

	shaकरोw_leak = klp_shaकरोw_alloc(d, SV_LEAK, माप(leak), GFP_KERNEL,
				       shaकरोw_leak_ctor, &leak);
	अगर (!shaकरोw_leak) अणु
		pr_err("%s: failed to allocate shadow variable for the leaking pointer: dummy @ %p, leak @ %p\n",
		       __func__, d, leak);
		जाओ err_shaकरोw;
	पूर्ण

	pr_info("%s: dummy @ %p, expires @ %lx\n",
		__func__, d, d->jअगरfies_expire);

	वापस d;

err_shaकरोw:
	kमुक्त(leak);
err_leak:
	kमुक्त(d);
	वापस शून्य;
पूर्ण

अटल व्योम livepatch_fix1_dummy_leak_dtor(व्योम *obj, व्योम *shaकरोw_data)
अणु
	व्योम *d = obj;
	पूर्णांक **shaकरोw_leak = shaकरोw_data;

	kमुक्त(*shaकरोw_leak);
	pr_info("%s: dummy @ %p, prevented leak @ %p\n",
			 __func__, d, *shaकरोw_leak);
पूर्ण

अटल व्योम livepatch_fix1_dummy_मुक्त(काष्ठा dummy *d)
अणु
	पूर्णांक **shaकरोw_leak;

	/*
	 * Patch: fetch the saved SV_LEAK shaकरोw variable, detach and
	 * मुक्त it.  Note: handle हालs where this shaकरोw variable करोes
	 * not exist (ie, dummy काष्ठाures allocated beक्रमe this livepatch
	 * was loaded.)
	 */
	shaकरोw_leak = klp_shaकरोw_get(d, SV_LEAK);
	अगर (shaकरोw_leak)
		klp_shaकरोw_मुक्त(d, SV_LEAK, livepatch_fix1_dummy_leak_dtor);
	अन्यथा
		pr_info("%s: dummy @ %p leaked!\n", __func__, d);

	kमुक्त(d);
पूर्ण

अटल काष्ठा klp_func funcs[] = अणु
	अणु
		.old_name = "dummy_alloc",
		.new_func = livepatch_fix1_dummy_alloc,
	पूर्ण,
	अणु
		.old_name = "dummy_free",
		.new_func = livepatch_fix1_dummy_मुक्त,
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

अटल पूर्णांक livepatch_shaकरोw_fix1_init(व्योम)
अणु
	वापस klp_enable_patch(&patch);
पूर्ण

अटल व्योम livepatch_shaकरोw_fix1_निकास(व्योम)
अणु
	/* Cleanup any existing SV_LEAK shaकरोw variables */
	klp_shaकरोw_मुक्त_all(SV_LEAK, livepatch_fix1_dummy_leak_dtor);
पूर्ण

module_init(livepatch_shaकरोw_fix1_init);
module_निकास(livepatch_shaकरोw_fix1_निकास);
MODULE_LICENSE("GPL");
MODULE_INFO(livepatch, "Y");
