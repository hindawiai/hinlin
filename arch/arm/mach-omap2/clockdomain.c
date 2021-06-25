<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP2/3/4 घड़ीकरोमुख्य framework functions
 *
 * Copyright (C) 2008-2011 Texas Instruments, Inc.
 * Copyright (C) 2008-2011 Nokia Corporation
 *
 * Written by Paul Walmsley and Jouni Hथघgander
 * Added OMAP4 specअगरic support by Abhijit Pagare <abhijitpagare@ti.com>
 */
#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/err.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/cpu_pm.h>

#समावेश <linux/पन.स>

#समावेश <linux/bitops.h>

#समावेश "soc.h"
#समावेश "clock.h"
#समावेश "clockdomain.h"
#समावेश "pm.h"

/* clkdm_list contains all रेजिस्टरed काष्ठा घड़ीकरोमुख्यs */
अटल LIST_HEAD(clkdm_list);

/* array of घड़ीकरोमुख्य deps to be added/हटाओd when clkdm in hwsup mode */
अटल काष्ठा clkdm_स्वतःdep *स्वतःdeps;

अटल काष्ठा clkdm_ops *arch_clkdm;
व्योम clkdm_save_context(व्योम);
व्योम clkdm_restore_context(व्योम);

/* Private functions */

अटल काष्ठा घड़ीकरोमुख्य *_clkdm_lookup(स्थिर अक्षर *name)
अणु
	काष्ठा घड़ीकरोमुख्य *clkdm, *temp_clkdm;

	अगर (!name)
		वापस शून्य;

	clkdm = शून्य;

	list_क्रम_each_entry(temp_clkdm, &clkdm_list, node) अणु
		अगर (!म_भेद(name, temp_clkdm->name)) अणु
			clkdm = temp_clkdm;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस clkdm;
पूर्ण

/**
 * _clkdm_रेजिस्टर - रेजिस्टर a घड़ीकरोमुख्य
 * @clkdm: काष्ठा घड़ीकरोमुख्य * to रेजिस्टर
 *
 * Adds a घड़ीकरोमुख्य to the पूर्णांकernal घड़ीकरोमुख्य list.
 * Returns -EINVAL अगर given a null poपूर्णांकer, -EEXIST अगर a घड़ीकरोमुख्य is
 * alपढ़ोy रेजिस्टरed by the provided name, or 0 upon success.
 */
अटल पूर्णांक _clkdm_रेजिस्टर(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	काष्ठा घातerकरोमुख्य *pwrdm;

	अगर (!clkdm || !clkdm->name)
		वापस -EINVAL;

	pwrdm = pwrdm_lookup(clkdm->pwrdm.name);
	अगर (!pwrdm) अणु
		pr_err("clockdomain: %s: powerdomain %s does not exist\n",
			clkdm->name, clkdm->pwrdm.name);
		वापस -EINVAL;
	पूर्ण
	clkdm->pwrdm.ptr = pwrdm;

	/* Verअगरy that the घड़ीकरोमुख्य is not alपढ़ोy रेजिस्टरed */
	अगर (_clkdm_lookup(clkdm->name))
		वापस -EEXIST;

	list_add(&clkdm->node, &clkdm_list);

	pwrdm_add_clkdm(pwrdm, clkdm);

	pr_debug("clockdomain: registered %s\n", clkdm->name);

	वापस 0;
पूर्ण

/* _clkdm_deps_lookup - look up the specअगरied घड़ीकरोमुख्य in a clkdm list */
अटल काष्ठा clkdm_dep *_clkdm_deps_lookup(काष्ठा घड़ीकरोमुख्य *clkdm,
					    काष्ठा clkdm_dep *deps)
अणु
	काष्ठा clkdm_dep *cd;

	अगर (!clkdm || !deps)
		वापस ERR_PTR(-EINVAL);

	क्रम (cd = deps; cd->clkdm_name; cd++) अणु
		अगर (!cd->clkdm && cd->clkdm_name)
			cd->clkdm = _clkdm_lookup(cd->clkdm_name);

		अगर (cd->clkdm == clkdm)
			अवरोध;
	पूर्ण

	अगर (!cd->clkdm_name)
		वापस ERR_PTR(-ENOENT);

	वापस cd;
पूर्ण

/**
 * _स्वतःdep_lookup - resolve स्वतःdep clkdm names to clkdm poपूर्णांकers; store
 * @स्वतःdep: काष्ठा clkdm_स्वतःdep * to resolve
 *
 * Resolve स्वतःdep घड़ीकरोमुख्य names to घड़ीकरोमुख्य poपूर्णांकers via
 * clkdm_lookup() and store the poपूर्णांकers in the स्वतःdep काष्ठाure.  An
 * "autodep" is a घड़ीकरोमुख्य sleep/wakeup dependency that is
 * स्वतःmatically added and हटाओd whenever घड़ीs in the associated
 * घड़ीकरोमुख्य are enabled or disabled (respectively) when the
 * घड़ीकरोमुख्य is in hardware-supervised mode.	Meant to be called
 * once at घड़ीकरोमुख्य layer initialization, since these should reमुख्य
 * fixed क्रम a particular architecture.  No वापस value.
 *
 * XXX स्वतःdeps are deprecated and should be हटाओd at the earliest
 * opportunity
 */
अटल व्योम _स्वतःdep_lookup(काष्ठा clkdm_स्वतःdep *स्वतःdep)
अणु
	काष्ठा घड़ीकरोमुख्य *clkdm;

	अगर (!स्वतःdep)
		वापस;

	clkdm = clkdm_lookup(स्वतःdep->clkdm.name);
	अगर (!clkdm) अणु
		pr_err("clockdomain: autodeps: clockdomain %s does not exist\n",
			 स्वतःdep->clkdm.name);
		clkdm = ERR_PTR(-ENOENT);
	पूर्ण
	स्वतःdep->clkdm.ptr = clkdm;
पूर्ण

/**
 * _resolve_clkdm_deps() - resolve clkdm_names in @clkdm_deps to clkdms
 * @clkdm: घड़ीकरोमुख्य that we are resolving dependencies क्रम
 * @clkdm_deps: ptr to array of काष्ठा clkdm_deps to resolve
 *
 * Iterates through @clkdm_deps, looking up the काष्ठा घड़ीकरोमुख्य named by
 * clkdm_name and storing the घड़ीकरोमुख्य poपूर्णांकer in the काष्ठा clkdm_dep.
 * No वापस value.
 */
अटल व्योम _resolve_clkdm_deps(काष्ठा घड़ीकरोमुख्य *clkdm,
				काष्ठा clkdm_dep *clkdm_deps)
अणु
	काष्ठा clkdm_dep *cd;

	क्रम (cd = clkdm_deps; cd && cd->clkdm_name; cd++) अणु
		अगर (cd->clkdm)
			जारी;
		cd->clkdm = _clkdm_lookup(cd->clkdm_name);

		WARN(!cd->clkdm, "clockdomain: %s: could not find clkdm %s while resolving dependencies - should never happen",
		     clkdm->name, cd->clkdm_name);
	पूर्ण
पूर्ण

/**
 * _clkdm_add_wkdep - add a wakeup dependency from clkdm2 to clkdm1 (lockless)
 * @clkdm1: wake this काष्ठा घड़ीकरोमुख्य * up (dependent)
 * @clkdm2: when this काष्ठा घड़ीकरोमुख्य * wakes up (source)
 *
 * When the घड़ीकरोमुख्य represented by @clkdm2 wakes up, wake up
 * @clkdm1. Implemented in hardware on the OMAP, this feature is
 * deचिन्हित to reduce wakeup latency of the dependent घड़ीकरोमुख्य @clkdm1.
 * Returns -EINVAL अगर presented with invalid घड़ीकरोमुख्य poपूर्णांकers,
 * -ENOENT अगर @clkdm2 cannot wake up clkdm1 in hardware, or 0 upon
 * success.
 */
अटल पूर्णांक _clkdm_add_wkdep(काष्ठा घड़ीकरोमुख्य *clkdm1,
			    काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	काष्ठा clkdm_dep *cd;
	पूर्णांक ret = 0;

	अगर (!clkdm1 || !clkdm2)
		वापस -EINVAL;

	cd = _clkdm_deps_lookup(clkdm2, clkdm1->wkdep_srcs);
	अगर (IS_ERR(cd))
		ret = PTR_ERR(cd);

	अगर (!arch_clkdm || !arch_clkdm->clkdm_add_wkdep)
		ret = -EINVAL;

	अगर (ret) अणु
		pr_debug("clockdomain: hardware cannot set/clear wake up of %s when %s wakes up\n",
			 clkdm1->name, clkdm2->name);
		वापस ret;
	पूर्ण

	cd->wkdep_usecount++;
	अगर (cd->wkdep_usecount == 1) अणु
		pr_debug("clockdomain: hardware will wake up %s when %s wakes up\n",
			 clkdm1->name, clkdm2->name);

		ret = arch_clkdm->clkdm_add_wkdep(clkdm1, clkdm2);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * _clkdm_del_wkdep - हटाओ a wakeup dep from clkdm2 to clkdm1 (lockless)
 * @clkdm1: wake this काष्ठा घड़ीकरोमुख्य * up (dependent)
 * @clkdm2: when this काष्ठा घड़ीकरोमुख्य * wakes up (source)
 *
 * Remove a wakeup dependency causing @clkdm1 to wake up when @clkdm2
 * wakes up.  Returns -EINVAL अगर presented with invalid घड़ीकरोमुख्य
 * poपूर्णांकers, -ENOENT अगर @clkdm2 cannot wake up clkdm1 in hardware, or
 * 0 upon success.
 */
अटल पूर्णांक _clkdm_del_wkdep(काष्ठा घड़ीकरोमुख्य *clkdm1,
			    काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	काष्ठा clkdm_dep *cd;
	पूर्णांक ret = 0;

	अगर (!clkdm1 || !clkdm2)
		वापस -EINVAL;

	cd = _clkdm_deps_lookup(clkdm2, clkdm1->wkdep_srcs);
	अगर (IS_ERR(cd))
		ret = PTR_ERR(cd);

	अगर (!arch_clkdm || !arch_clkdm->clkdm_del_wkdep)
		ret = -EINVAL;

	अगर (ret) अणु
		pr_debug("clockdomain: hardware cannot set/clear wake up of %s when %s wakes up\n",
			 clkdm1->name, clkdm2->name);
		वापस ret;
	पूर्ण

	cd->wkdep_usecount--;
	अगर (cd->wkdep_usecount == 0) अणु
		pr_debug("clockdomain: hardware will no longer wake up %s after %s wakes up\n",
			 clkdm1->name, clkdm2->name);

		ret = arch_clkdm->clkdm_del_wkdep(clkdm1, clkdm2);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * _clkdm_add_sleepdep - add a sleep dependency from clkdm2 to clkdm1 (lockless)
 * @clkdm1: prevent this काष्ठा घड़ीकरोमुख्य * from sleeping (dependent)
 * @clkdm2: when this काष्ठा घड़ीकरोमुख्य * is active (source)
 *
 * Prevent @clkdm1 from स्वतःmatically going inactive (and then to
 * retention or off) अगर @clkdm2 is active.  Returns -EINVAL अगर
 * presented with invalid घड़ीकरोमुख्य poपूर्णांकers or called on a machine
 * that करोes not support software-configurable hardware sleep
 * dependencies, -ENOENT अगर the specअगरied dependency cannot be set in
 * hardware, or 0 upon success.
 */
अटल पूर्णांक _clkdm_add_sleepdep(काष्ठा घड़ीकरोमुख्य *clkdm1,
			       काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	काष्ठा clkdm_dep *cd;
	पूर्णांक ret = 0;

	अगर (!clkdm1 || !clkdm2)
		वापस -EINVAL;

	cd = _clkdm_deps_lookup(clkdm2, clkdm1->sleepdep_srcs);
	अगर (IS_ERR(cd))
		ret = PTR_ERR(cd);

	अगर (!arch_clkdm || !arch_clkdm->clkdm_add_sleepdep)
		ret = -EINVAL;

	अगर (ret) अणु
		pr_debug("clockdomain: hardware cannot set/clear sleep dependency affecting %s from %s\n",
			 clkdm1->name, clkdm2->name);
		वापस ret;
	पूर्ण

	cd->sleepdep_usecount++;
	अगर (cd->sleepdep_usecount == 1) अणु
		pr_debug("clockdomain: will prevent %s from sleeping if %s is active\n",
			 clkdm1->name, clkdm2->name);

		ret = arch_clkdm->clkdm_add_sleepdep(clkdm1, clkdm2);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * _clkdm_del_sleepdep - हटाओ a sleep dep from clkdm2 to clkdm1 (lockless)
 * @clkdm1: prevent this काष्ठा घड़ीकरोमुख्य * from sleeping (dependent)
 * @clkdm2: when this काष्ठा घड़ीकरोमुख्य * is active (source)
 *
 * Allow @clkdm1 to स्वतःmatically go inactive (and then to retention or
 * off), independent of the activity state of @clkdm2.  Returns -EINVAL
 * अगर presented with invalid घड़ीकरोमुख्य poपूर्णांकers or called on a machine
 * that करोes not support software-configurable hardware sleep dependencies,
 * -ENOENT अगर the specअगरied dependency cannot be cleared in hardware, or
 * 0 upon success.
 */
अटल पूर्णांक _clkdm_del_sleepdep(काष्ठा घड़ीकरोमुख्य *clkdm1,
			       काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	काष्ठा clkdm_dep *cd;
	पूर्णांक ret = 0;

	अगर (!clkdm1 || !clkdm2)
		वापस -EINVAL;

	cd = _clkdm_deps_lookup(clkdm2, clkdm1->sleepdep_srcs);
	अगर (IS_ERR(cd))
		ret = PTR_ERR(cd);

	अगर (!arch_clkdm || !arch_clkdm->clkdm_del_sleepdep)
		ret = -EINVAL;

	अगर (ret) अणु
		pr_debug("clockdomain: hardware cannot set/clear sleep dependency affecting %s from %s\n",
			 clkdm1->name, clkdm2->name);
		वापस ret;
	पूर्ण

	cd->sleepdep_usecount--;
	अगर (cd->sleepdep_usecount == 0) अणु
		pr_debug("clockdomain: will no longer prevent %s from sleeping if %s is active\n",
			 clkdm1->name, clkdm2->name);

		ret = arch_clkdm->clkdm_del_sleepdep(clkdm1, clkdm2);
	पूर्ण

	वापस ret;
पूर्ण

/* Public functions */

/**
 * clkdm_रेजिस्टर_platक्रमm_funcs - रेजिस्टर घड़ीकरोमुख्य implementation fns
 * @co: func poपूर्णांकers क्रम arch specअगरic implementations
 *
 * Register the list of function poपूर्णांकers used to implement the
 * घड़ीकरोमुख्य functions on dअगरferent OMAP SoCs.  Should be called
 * beक्रमe any other clkdm_रेजिस्टर*() function.  Returns -EINVAL अगर
 * @co is null, -EEXIST अगर platक्रमm functions have alपढ़ोy been
 * रेजिस्टरed, or 0 upon success.
 */
पूर्णांक clkdm_रेजिस्टर_platक्रमm_funcs(काष्ठा clkdm_ops *co)
अणु
	अगर (!co)
		वापस -EINVAL;

	अगर (arch_clkdm)
		वापस -EEXIST;

	arch_clkdm = co;

	वापस 0;
पूर्ण;

/**
 * clkdm_रेजिस्टर_clkdms - रेजिस्टर SoC घड़ीकरोमुख्यs
 * @cs: poपूर्णांकer to an array of काष्ठा घड़ीकरोमुख्य to रेजिस्टर
 *
 * Register the घड़ीकरोमुख्यs available on a particular OMAP SoC.  Must
 * be called after clkdm_रेजिस्टर_platक्रमm_funcs().  May be called
 * multiple बार.  Returns -EACCES अगर called beक्रमe
 * clkdm_रेजिस्टर_platक्रमm_funcs(); -EINVAL अगर the argument @cs is
 * null; or 0 upon success.
 */
पूर्णांक clkdm_रेजिस्टर_clkdms(काष्ठा घड़ीकरोमुख्य **cs)
अणु
	काष्ठा घड़ीकरोमुख्य **c = शून्य;

	अगर (!arch_clkdm)
		वापस -EACCES;

	अगर (!cs)
		वापस -EINVAL;

	क्रम (c = cs; *c; c++)
		_clkdm_रेजिस्टर(*c);

	वापस 0;
पूर्ण

/**
 * clkdm_रेजिस्टर_स्वतःdeps - रेजिस्टर स्वतःdeps (अगर required)
 * @ia: poपूर्णांकer to a अटल array of काष्ठा clkdm_स्वतःdep to रेजिस्टर
 *
 * Register घड़ीकरोमुख्य "automatic dependencies."  These are
 * घड़ीकरोमुख्य wakeup and sleep dependencies that are स्वतःmatically
 * added whenever the first घड़ी inside a घड़ीकरोमुख्य is enabled, and
 * हटाओd whenever the last घड़ी inside a घड़ीकरोमुख्य is disabled.
 * These are currently only used on OMAP3 devices, and are deprecated,
 * since they waste energy.  However, until the OMAP2/3 IP block
 * enable/disable sequence can be converted to match the OMAP4
 * sequence, they are needed.
 *
 * Must be called only after all of the SoC घड़ीकरोमुख्यs are
 * रेजिस्टरed, since the function will resolve स्वतःdep घड़ीकरोमुख्य
 * names पूर्णांकo घड़ीकरोमुख्य poपूर्णांकers.
 *
 * The काष्ठा clkdm_स्वतःdep @ia array must be अटल, as this function
 * करोes not copy the array elements.
 *
 * Returns -EACCES अगर called beक्रमe any घड़ीकरोमुख्यs have been
 * रेजिस्टरed, -EINVAL अगर called with a null @ia argument, -EEXIST अगर
 * स्वतःdeps have alपढ़ोy been रेजिस्टरed, or 0 upon success.
 */
पूर्णांक clkdm_रेजिस्टर_स्वतःdeps(काष्ठा clkdm_स्वतःdep *ia)
अणु
	काष्ठा clkdm_स्वतःdep *a = शून्य;

	अगर (list_empty(&clkdm_list))
		वापस -EACCES;

	अगर (!ia)
		वापस -EINVAL;

	अगर (स्वतःdeps)
		वापस -EEXIST;

	स्वतःdeps = ia;
	क्रम (a = स्वतःdeps; a->clkdm.ptr; a++)
		_स्वतःdep_lookup(a);

	वापस 0;
पूर्ण

अटल पूर्णांक cpu_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ cmd, व्योम *v)
अणु
	चयन (cmd) अणु
	हाल CPU_CLUSTER_PM_ENTER:
		अगर (enable_off_mode)
			clkdm_save_context();
		अवरोध;
	हाल CPU_CLUSTER_PM_EXIT:
		अगर (enable_off_mode)
			clkdm_restore_context();
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

/**
 * clkdm_complete_init - set up the घड़ीकरोमुख्य layer
 *
 * Put all घड़ीकरोमुख्यs पूर्णांकo software-supervised mode; PM code should
 * later enable hardware-supervised mode as appropriate.  Must be
 * called after clkdm_रेजिस्टर_clkdms().  Returns -EACCES अगर called
 * beक्रमe clkdm_रेजिस्टर_clkdms(), or 0 upon success.
 */
पूर्णांक clkdm_complete_init(व्योम)
अणु
	काष्ठा घड़ीकरोमुख्य *clkdm;
	अटल काष्ठा notअगरier_block nb;

	अगर (list_empty(&clkdm_list))
		वापस -EACCES;

	list_क्रम_each_entry(clkdm, &clkdm_list, node) अणु
		clkdm_deny_idle(clkdm);

		_resolve_clkdm_deps(clkdm, clkdm->wkdep_srcs);
		clkdm_clear_all_wkdeps(clkdm);

		_resolve_clkdm_deps(clkdm, clkdm->sleepdep_srcs);
		clkdm_clear_all_sleepdeps(clkdm);
	पूर्ण

	/* Only AM43XX can lose clkdm context during rtc-ddr suspend */
	अगर (soc_is_am43xx()) अणु
		nb.notअगरier_call = cpu_notअगरier;
		cpu_pm_रेजिस्टर_notअगरier(&nb);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * clkdm_lookup - look up a घड़ीकरोमुख्य by name, वापस a poपूर्णांकer
 * @name: name of घड़ीकरोमुख्य
 *
 * Find a रेजिस्टरed घड़ीकरोमुख्य by its name @name.  Returns a poपूर्णांकer
 * to the काष्ठा घड़ीकरोमुख्य अगर found, or शून्य otherwise.
 */
काष्ठा घड़ीकरोमुख्य *clkdm_lookup(स्थिर अक्षर *name)
अणु
	काष्ठा घड़ीकरोमुख्य *clkdm, *temp_clkdm;

	अगर (!name)
		वापस शून्य;

	clkdm = शून्य;

	list_क्रम_each_entry(temp_clkdm, &clkdm_list, node) अणु
		अगर (!म_भेद(name, temp_clkdm->name)) अणु
			clkdm = temp_clkdm;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस clkdm;
पूर्ण

/**
 * clkdm_क्रम_each - call function on each रेजिस्टरed घड़ीकरोमुख्य
 * @fn: callback function *
 *
 * Call the supplied function @fn क्रम each रेजिस्टरed घड़ीकरोमुख्य.
 * The callback function @fn can वापस anything but 0 to bail
 * out early from the iterator.  The callback function is called with
 * the clkdm_mutex held, so no घड़ीकरोमुख्य काष्ठाure manipulation
 * functions should be called from the callback, although hardware
 * घड़ीकरोमुख्य control functions are fine.  Returns the last वापस
 * value of the callback function, which should be 0 क्रम success or
 * anything अन्यथा to indicate failure; or -EINVAL अगर the function poपूर्णांकer
 * is null.
 */
पूर्णांक clkdm_क्रम_each(पूर्णांक (*fn)(काष्ठा घड़ीकरोमुख्य *clkdm, व्योम *user),
			व्योम *user)
अणु
	काष्ठा घड़ीकरोमुख्य *clkdm;
	पूर्णांक ret = 0;

	अगर (!fn)
		वापस -EINVAL;

	list_क्रम_each_entry(clkdm, &clkdm_list, node) अणु
		ret = (*fn)(clkdm, user);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण


/**
 * clkdm_get_pwrdm - वापस a ptr to the pwrdm that this clkdm resides in
 * @clkdm: काष्ठा घड़ीकरोमुख्य *
 *
 * Return a poपूर्णांकer to the काष्ठा घातerकरोमुख्य that the specअगरied घड़ीकरोमुख्य
 * @clkdm exists in, or वापसs शून्य अगर @clkdm is शून्य.
 */
काष्ठा घातerकरोमुख्य *clkdm_get_pwrdm(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	अगर (!clkdm)
		वापस शून्य;

	वापस clkdm->pwrdm.ptr;
पूर्ण


/* Hardware घड़ीकरोमुख्य control */

/**
 * clkdm_add_wkdep - add a wakeup dependency from clkdm2 to clkdm1
 * @clkdm1: wake this काष्ठा घड़ीकरोमुख्य * up (dependent)
 * @clkdm2: when this काष्ठा घड़ीकरोमुख्य * wakes up (source)
 *
 * When the घड़ीकरोमुख्य represented by @clkdm2 wakes up, wake up
 * @clkdm1. Implemented in hardware on the OMAP, this feature is
 * deचिन्हित to reduce wakeup latency of the dependent घड़ीकरोमुख्य @clkdm1.
 * Returns -EINVAL अगर presented with invalid घड़ीकरोमुख्य poपूर्णांकers,
 * -ENOENT अगर @clkdm2 cannot wake up clkdm1 in hardware, or 0 upon
 * success.
 */
पूर्णांक clkdm_add_wkdep(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	काष्ठा clkdm_dep *cd;
	पूर्णांक ret;

	अगर (!clkdm1 || !clkdm2)
		वापस -EINVAL;

	cd = _clkdm_deps_lookup(clkdm2, clkdm1->wkdep_srcs);
	अगर (IS_ERR(cd))
		वापस PTR_ERR(cd);

	pwrdm_lock(cd->clkdm->pwrdm.ptr);
	ret = _clkdm_add_wkdep(clkdm1, clkdm2);
	pwrdm_unlock(cd->clkdm->pwrdm.ptr);

	वापस ret;
पूर्ण

/**
 * clkdm_del_wkdep - हटाओ a wakeup dependency from clkdm2 to clkdm1
 * @clkdm1: wake this काष्ठा घड़ीकरोमुख्य * up (dependent)
 * @clkdm2: when this काष्ठा घड़ीकरोमुख्य * wakes up (source)
 *
 * Remove a wakeup dependency causing @clkdm1 to wake up when @clkdm2
 * wakes up.  Returns -EINVAL अगर presented with invalid घड़ीकरोमुख्य
 * poपूर्णांकers, -ENOENT अगर @clkdm2 cannot wake up clkdm1 in hardware, or
 * 0 upon success.
 */
पूर्णांक clkdm_del_wkdep(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	काष्ठा clkdm_dep *cd;
	पूर्णांक ret;

	अगर (!clkdm1 || !clkdm2)
		वापस -EINVAL;

	cd = _clkdm_deps_lookup(clkdm2, clkdm1->wkdep_srcs);
	अगर (IS_ERR(cd))
		वापस PTR_ERR(cd);

	pwrdm_lock(cd->clkdm->pwrdm.ptr);
	ret = _clkdm_del_wkdep(clkdm1, clkdm2);
	pwrdm_unlock(cd->clkdm->pwrdm.ptr);

	वापस ret;
पूर्ण

/**
 * clkdm_पढ़ो_wkdep - पढ़ो wakeup dependency state from clkdm2 to clkdm1
 * @clkdm1: wake this काष्ठा घड़ीकरोमुख्य * up (dependent)
 * @clkdm2: when this काष्ठा घड़ीकरोमुख्य * wakes up (source)
 *
 * Return 1 अगर a hardware wakeup dependency exists wherein @clkdm1 will be
 * awoken when @clkdm2 wakes up; 0 अगर dependency is not set; -EINVAL
 * अगर either घड़ीकरोमुख्य poपूर्णांकer is invalid; or -ENOENT अगर the hardware
 * is incapable.
 *
 * REVISIT: Currently this function only represents software-controllable
 * wakeup dependencies.  Wakeup dependencies fixed in hardware are not
 * yet handled here.
 */
पूर्णांक clkdm_पढ़ो_wkdep(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	काष्ठा clkdm_dep *cd;
	पूर्णांक ret = 0;

	अगर (!clkdm1 || !clkdm2)
		वापस -EINVAL;

	cd = _clkdm_deps_lookup(clkdm2, clkdm1->wkdep_srcs);
	अगर (IS_ERR(cd))
		ret = PTR_ERR(cd);

	अगर (!arch_clkdm || !arch_clkdm->clkdm_पढ़ो_wkdep)
		ret = -EINVAL;

	अगर (ret) अणु
		pr_debug("clockdomain: hardware cannot set/clear wake up of %s when %s wakes up\n",
			 clkdm1->name, clkdm2->name);
		वापस ret;
	पूर्ण

	/* XXX It's faster to वापस the wkdep_usecount */
	वापस arch_clkdm->clkdm_पढ़ो_wkdep(clkdm1, clkdm2);
पूर्ण

/**
 * clkdm_clear_all_wkdeps - हटाओ all wakeup dependencies from target clkdm
 * @clkdm: काष्ठा घड़ीकरोमुख्य * to हटाओ all wakeup dependencies from
 *
 * Remove all पूर्णांकer-घड़ीकरोमुख्य wakeup dependencies that could cause
 * @clkdm to wake.  Intended to be used during boot to initialize the
 * PRCM to a known state, after all घड़ीकरोमुख्यs are put पूर्णांकo swsup idle
 * and woken up.  Returns -EINVAL अगर @clkdm poपूर्णांकer is invalid, or
 * 0 upon success.
 */
पूर्णांक clkdm_clear_all_wkdeps(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	अगर (!clkdm)
		वापस -EINVAL;

	अगर (!arch_clkdm || !arch_clkdm->clkdm_clear_all_wkdeps)
		वापस -EINVAL;

	वापस arch_clkdm->clkdm_clear_all_wkdeps(clkdm);
पूर्ण

/**
 * clkdm_add_sleepdep - add a sleep dependency from clkdm2 to clkdm1
 * @clkdm1: prevent this काष्ठा घड़ीकरोमुख्य * from sleeping (dependent)
 * @clkdm2: when this काष्ठा घड़ीकरोमुख्य * is active (source)
 *
 * Prevent @clkdm1 from स्वतःmatically going inactive (and then to
 * retention or off) अगर @clkdm2 is active.  Returns -EINVAL अगर
 * presented with invalid घड़ीकरोमुख्य poपूर्णांकers or called on a machine
 * that करोes not support software-configurable hardware sleep
 * dependencies, -ENOENT अगर the specअगरied dependency cannot be set in
 * hardware, or 0 upon success.
 */
पूर्णांक clkdm_add_sleepdep(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	काष्ठा clkdm_dep *cd;
	पूर्णांक ret;

	अगर (!clkdm1 || !clkdm2)
		वापस -EINVAL;

	cd = _clkdm_deps_lookup(clkdm2, clkdm1->wkdep_srcs);
	अगर (IS_ERR(cd))
		वापस PTR_ERR(cd);

	pwrdm_lock(cd->clkdm->pwrdm.ptr);
	ret = _clkdm_add_sleepdep(clkdm1, clkdm2);
	pwrdm_unlock(cd->clkdm->pwrdm.ptr);

	वापस ret;
पूर्ण

/**
 * clkdm_del_sleepdep - हटाओ a sleep dependency from clkdm2 to clkdm1
 * @clkdm1: prevent this काष्ठा घड़ीकरोमुख्य * from sleeping (dependent)
 * @clkdm2: when this काष्ठा घड़ीकरोमुख्य * is active (source)
 *
 * Allow @clkdm1 to स्वतःmatically go inactive (and then to retention or
 * off), independent of the activity state of @clkdm2.  Returns -EINVAL
 * अगर presented with invalid घड़ीकरोमुख्य poपूर्णांकers or called on a machine
 * that करोes not support software-configurable hardware sleep dependencies,
 * -ENOENT अगर the specअगरied dependency cannot be cleared in hardware, or
 * 0 upon success.
 */
पूर्णांक clkdm_del_sleepdep(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	काष्ठा clkdm_dep *cd;
	पूर्णांक ret;

	अगर (!clkdm1 || !clkdm2)
		वापस -EINVAL;

	cd = _clkdm_deps_lookup(clkdm2, clkdm1->wkdep_srcs);
	अगर (IS_ERR(cd))
		वापस PTR_ERR(cd);

	pwrdm_lock(cd->clkdm->pwrdm.ptr);
	ret = _clkdm_del_sleepdep(clkdm1, clkdm2);
	pwrdm_unlock(cd->clkdm->pwrdm.ptr);

	वापस ret;
पूर्ण

/**
 * clkdm_पढ़ो_sleepdep - पढ़ो sleep dependency state from clkdm2 to clkdm1
 * @clkdm1: prevent this काष्ठा घड़ीकरोमुख्य * from sleeping (dependent)
 * @clkdm2: when this काष्ठा घड़ीकरोमुख्य * is active (source)
 *
 * Return 1 अगर a hardware sleep dependency exists wherein @clkdm1 will
 * not be allowed to स्वतःmatically go inactive अगर @clkdm2 is active;
 * 0 अगर @clkdm1's स्वतःmatic घातer state inactivity transition is independent
 * of @clkdm2's; -EINVAL अगर either घड़ीकरोमुख्य poपूर्णांकer is invalid or called
 * on a machine that करोes not support software-configurable hardware sleep
 * dependencies; or -ENOENT अगर the hardware is incapable.
 *
 * REVISIT: Currently this function only represents software-controllable
 * sleep dependencies.	Sleep dependencies fixed in hardware are not
 * yet handled here.
 */
पूर्णांक clkdm_पढ़ो_sleepdep(काष्ठा घड़ीकरोमुख्य *clkdm1, काष्ठा घड़ीकरोमुख्य *clkdm2)
अणु
	काष्ठा clkdm_dep *cd;
	पूर्णांक ret = 0;

	अगर (!clkdm1 || !clkdm2)
		वापस -EINVAL;

	cd = _clkdm_deps_lookup(clkdm2, clkdm1->sleepdep_srcs);
	अगर (IS_ERR(cd))
		ret = PTR_ERR(cd);

	अगर (!arch_clkdm || !arch_clkdm->clkdm_पढ़ो_sleepdep)
		ret = -EINVAL;

	अगर (ret) अणु
		pr_debug("clockdomain: hardware cannot set/clear sleep dependency affecting %s from %s\n",
			 clkdm1->name, clkdm2->name);
		वापस ret;
	पूर्ण

	/* XXX It's faster to वापस the sleepdep_usecount */
	वापस arch_clkdm->clkdm_पढ़ो_sleepdep(clkdm1, clkdm2);
पूर्ण

/**
 * clkdm_clear_all_sleepdeps - हटाओ all sleep dependencies from target clkdm
 * @clkdm: काष्ठा घड़ीकरोमुख्य * to हटाओ all sleep dependencies from
 *
 * Remove all पूर्णांकer-घड़ीकरोमुख्य sleep dependencies that could prevent
 * @clkdm from idling.  Intended to be used during boot to initialize the
 * PRCM to a known state, after all घड़ीकरोमुख्यs are put पूर्णांकo swsup idle
 * and woken up.  Returns -EINVAL अगर @clkdm poपूर्णांकer is invalid, or
 * 0 upon success.
 */
पूर्णांक clkdm_clear_all_sleepdeps(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	अगर (!clkdm)
		वापस -EINVAL;

	अगर (!arch_clkdm || !arch_clkdm->clkdm_clear_all_sleepdeps)
		वापस -EINVAL;

	वापस arch_clkdm->clkdm_clear_all_sleepdeps(clkdm);
पूर्ण

/**
 * clkdm_sleep_nolock - क्रमce घड़ीकरोमुख्य sleep transition (lockless)
 * @clkdm: काष्ठा घड़ीकरोमुख्य *
 *
 * Inकाष्ठा the CM to क्रमce a sleep transition on the specअगरied
 * घड़ीकरोमुख्य @clkdm.  Only क्रम use by the घातerकरोमुख्य code.  Returns
 * -EINVAL अगर @clkdm is शून्य or अगर घड़ीकरोमुख्य करोes not support
 * software-initiated sleep; 0 upon success.
 */
पूर्णांक clkdm_sleep_nolock(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	पूर्णांक ret;

	अगर (!clkdm)
		वापस -EINVAL;

	अगर (!(clkdm->flags & CLKDM_CAN_FORCE_SLEEP)) अणु
		pr_debug("clockdomain: %s does not support forcing sleep via software\n",
			 clkdm->name);
		वापस -EINVAL;
	पूर्ण

	अगर (!arch_clkdm || !arch_clkdm->clkdm_sleep)
		वापस -EINVAL;

	pr_debug("clockdomain: forcing sleep on %s\n", clkdm->name);

	clkdm->_flags &= ~_CLKDM_FLAG_HWSUP_ENABLED;
	ret = arch_clkdm->clkdm_sleep(clkdm);
	ret |= pwrdm_state_चयन_nolock(clkdm->pwrdm.ptr);

	वापस ret;
पूर्ण

/**
 * clkdm_sleep - क्रमce घड़ीकरोमुख्य sleep transition
 * @clkdm: काष्ठा घड़ीकरोमुख्य *
 *
 * Inकाष्ठा the CM to क्रमce a sleep transition on the specअगरied
 * घड़ीकरोमुख्य @clkdm.  Returns -EINVAL अगर @clkdm is शून्य or अगर
 * घड़ीकरोमुख्य करोes not support software-initiated sleep; 0 upon
 * success.
 */
पूर्णांक clkdm_sleep(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	पूर्णांक ret;

	pwrdm_lock(clkdm->pwrdm.ptr);
	ret = clkdm_sleep_nolock(clkdm);
	pwrdm_unlock(clkdm->pwrdm.ptr);

	वापस ret;
पूर्ण

/**
 * clkdm_wakeup_nolock - क्रमce घड़ीकरोमुख्य wakeup transition (lockless)
 * @clkdm: काष्ठा घड़ीकरोमुख्य *
 *
 * Inकाष्ठा the CM to क्रमce a wakeup transition on the specअगरied
 * घड़ीकरोमुख्य @clkdm.  Only क्रम use by the घातerकरोमुख्य code.  Returns
 * -EINVAL अगर @clkdm is शून्य or अगर the घड़ीकरोमुख्य करोes not support
 * software-controlled wakeup; 0 upon success.
 */
पूर्णांक clkdm_wakeup_nolock(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	पूर्णांक ret;

	अगर (!clkdm)
		वापस -EINVAL;

	अगर (!(clkdm->flags & CLKDM_CAN_FORCE_WAKEUP)) अणु
		pr_debug("clockdomain: %s does not support forcing wakeup via software\n",
			 clkdm->name);
		वापस -EINVAL;
	पूर्ण

	अगर (!arch_clkdm || !arch_clkdm->clkdm_wakeup)
		वापस -EINVAL;

	pr_debug("clockdomain: forcing wakeup on %s\n", clkdm->name);

	clkdm->_flags &= ~_CLKDM_FLAG_HWSUP_ENABLED;
	ret = arch_clkdm->clkdm_wakeup(clkdm);
	ret |= pwrdm_state_चयन_nolock(clkdm->pwrdm.ptr);

	वापस ret;
पूर्ण

/**
 * clkdm_wakeup - क्रमce घड़ीकरोमुख्य wakeup transition
 * @clkdm: काष्ठा घड़ीकरोमुख्य *
 *
 * Inकाष्ठा the CM to क्रमce a wakeup transition on the specअगरied
 * घड़ीकरोमुख्य @clkdm.  Returns -EINVAL अगर @clkdm is शून्य or अगर the
 * घड़ीकरोमुख्य करोes not support software-controlled wakeup; 0 upon
 * success.
 */
पूर्णांक clkdm_wakeup(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	पूर्णांक ret;

	pwrdm_lock(clkdm->pwrdm.ptr);
	ret = clkdm_wakeup_nolock(clkdm);
	pwrdm_unlock(clkdm->pwrdm.ptr);

	वापस ret;
पूर्ण

/**
 * clkdm_allow_idle_nolock - enable hwsup idle transitions क्रम clkdm
 * @clkdm: काष्ठा घड़ीकरोमुख्य *
 *
 * Allow the hardware to स्वतःmatically चयन the घड़ीकरोमुख्य @clkdm
 * पूर्णांकo active or idle states, as needed by करोwnstream घड़ीs.  If the
 * घड़ीकरोमुख्य has any करोwnstream घड़ीs enabled in the घड़ी
 * framework, wkdep/sleepdep स्वतःdependencies are added; this is so
 * device drivers can पढ़ो and ग_लिखो to the device.  Only क्रम use by
 * the घातerकरोमुख्य code.  No वापस value.
 */
व्योम clkdm_allow_idle_nolock(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	अगर (!clkdm)
		वापस;

	अगर (!WARN_ON(!clkdm->क्रमcewake_count))
		clkdm->क्रमcewake_count--;

	अगर (clkdm->क्रमcewake_count)
		वापस;

	अगर (!clkdm->usecount && (clkdm->flags & CLKDM_CAN_FORCE_SLEEP))
		clkdm_sleep_nolock(clkdm);

	अगर (!(clkdm->flags & CLKDM_CAN_ENABLE_AUTO))
		वापस;

	अगर (clkdm->flags & CLKDM_MISSING_IDLE_REPORTING)
		वापस;

	अगर (!arch_clkdm || !arch_clkdm->clkdm_allow_idle)
		वापस;

	pr_debug("clockdomain: enabling automatic idle transitions for %s\n",
		 clkdm->name);

	clkdm->_flags |= _CLKDM_FLAG_HWSUP_ENABLED;
	arch_clkdm->clkdm_allow_idle(clkdm);
	pwrdm_state_चयन_nolock(clkdm->pwrdm.ptr);
पूर्ण

/**
 * clkdm_allow_idle - enable hwsup idle transitions क्रम clkdm
 * @clkdm: काष्ठा घड़ीकरोमुख्य *
 *
 * Allow the hardware to स्वतःmatically चयन the घड़ीकरोमुख्य @clkdm पूर्णांकo
 * active or idle states, as needed by करोwnstream घड़ीs.  If the
 * घड़ीकरोमुख्य has any करोwnstream घड़ीs enabled in the घड़ी
 * framework, wkdep/sleepdep स्वतःdependencies are added; this is so
 * device drivers can पढ़ो and ग_लिखो to the device.  No वापस value.
 */
व्योम clkdm_allow_idle(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	pwrdm_lock(clkdm->pwrdm.ptr);
	clkdm_allow_idle_nolock(clkdm);
	pwrdm_unlock(clkdm->pwrdm.ptr);
पूर्ण

/**
 * clkdm_deny_idle - disable hwsup idle transitions क्रम clkdm
 * @clkdm: काष्ठा घड़ीकरोमुख्य *
 *
 * Prevent the hardware from स्वतःmatically चयनing the घड़ीकरोमुख्य
 * @clkdm पूर्णांकo inactive or idle states.  If the घड़ीकरोमुख्य has
 * करोwnstream घड़ीs enabled in the घड़ी framework, wkdep/sleepdep
 * स्वतःdependencies are हटाओd.  Only क्रम use by the घातerकरोमुख्य
 * code.  No वापस value.
 */
व्योम clkdm_deny_idle_nolock(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	अगर (!clkdm)
		वापस;

	अगर (clkdm->क्रमcewake_count++)
		वापस;

	अगर (clkdm->flags & CLKDM_CAN_FORCE_WAKEUP)
		clkdm_wakeup_nolock(clkdm);

	अगर (!(clkdm->flags & CLKDM_CAN_DISABLE_AUTO))
		वापस;

	अगर (clkdm->flags & CLKDM_MISSING_IDLE_REPORTING)
		वापस;

	अगर (!arch_clkdm || !arch_clkdm->clkdm_deny_idle)
		वापस;

	pr_debug("clockdomain: disabling automatic idle transitions for %s\n",
		 clkdm->name);

	clkdm->_flags &= ~_CLKDM_FLAG_HWSUP_ENABLED;
	arch_clkdm->clkdm_deny_idle(clkdm);
	pwrdm_state_चयन_nolock(clkdm->pwrdm.ptr);
पूर्ण

/**
 * clkdm_deny_idle - disable hwsup idle transitions क्रम clkdm
 * @clkdm: काष्ठा घड़ीकरोमुख्य *
 *
 * Prevent the hardware from स्वतःmatically चयनing the घड़ीकरोमुख्य
 * @clkdm पूर्णांकo inactive or idle states.  If the घड़ीकरोमुख्य has
 * करोwnstream घड़ीs enabled in the घड़ी framework, wkdep/sleepdep
 * स्वतःdependencies are हटाओd.  No वापस value.
 */
व्योम clkdm_deny_idle(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	pwrdm_lock(clkdm->pwrdm.ptr);
	clkdm_deny_idle_nolock(clkdm);
	pwrdm_unlock(clkdm->pwrdm.ptr);
पूर्ण

/**
 * clkdm_in_hwsup - is घड़ीकरोमुख्य @clkdm have hardware-supervised idle enabled?
 * @clkdm: काष्ठा घड़ीकरोमुख्य *
 *
 * Returns true अगर घड़ीकरोमुख्य @clkdm currently has
 * hardware-supervised idle enabled, or false अगर it करोes not or अगर
 * @clkdm is शून्य.  It is only valid to call this function after
 * clkdm_init() has been called.  This function करोes not actually पढ़ो
 * bits from the hardware; it instead tests an in-memory flag that is
 * changed whenever the घड़ीकरोमुख्य code changes the स्वतः-idle mode.
 */
bool clkdm_in_hwsup(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	bool ret;

	अगर (!clkdm)
		वापस false;

	ret = (clkdm->_flags & _CLKDM_FLAG_HWSUP_ENABLED) ? true : false;

	वापस ret;
पूर्ण

/**
 * clkdm_missing_idle_reporting - can @clkdm enter स्वतःidle even अगर in use?
 * @clkdm: काष्ठा घड़ीकरोमुख्य *
 *
 * Returns true अगर घड़ीकरोमुख्य @clkdm has the
 * CLKDM_MISSING_IDLE_REPORTING flag set, or false अगर not or @clkdm is
 * null.  More inक्रमmation is available in the करोcumentation क्रम the
 * CLKDM_MISSING_IDLE_REPORTING macro.
 */
bool clkdm_missing_idle_reporting(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	अगर (!clkdm)
		वापस false;

	वापस (clkdm->flags & CLKDM_MISSING_IDLE_REPORTING) ? true : false;
पूर्ण

/* Public स्वतःdep handling functions (deprecated) */

/**
 * clkdm_add_स्वतःdeps - add स्वतः sleepdeps/wkdeps to clkdm upon घड़ी enable
 * @clkdm: काष्ठा घड़ीकरोमुख्य *
 *
 * Add the "autodep" sleep & wakeup dependencies to घड़ीकरोमुख्य 'clkdm'
 * in hardware-supervised mode.  Meant to be called from घड़ी framework
 * when a घड़ी inside घड़ीकरोमुख्य 'clkdm' is enabled.	No वापस value.
 *
 * XXX स्वतःdeps are deprecated and should be हटाओd at the earliest
 * opportunity
 */
व्योम clkdm_add_स्वतःdeps(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	काष्ठा clkdm_स्वतःdep *स्वतःdep;

	अगर (!स्वतःdeps || clkdm->flags & CLKDM_NO_AUTODEPS)
		वापस;

	क्रम (स्वतःdep = स्वतःdeps; स्वतःdep->clkdm.ptr; स्वतःdep++) अणु
		अगर (IS_ERR(स्वतःdep->clkdm.ptr))
			जारी;

		pr_debug("clockdomain: %s: adding %s sleepdep/wkdep\n",
			 clkdm->name, स्वतःdep->clkdm.ptr->name);

		_clkdm_add_sleepdep(clkdm, स्वतःdep->clkdm.ptr);
		_clkdm_add_wkdep(clkdm, स्वतःdep->clkdm.ptr);
	पूर्ण
पूर्ण

/**
 * clkdm_del_स्वतःdeps - हटाओ स्वतः sleepdeps/wkdeps from clkdm
 * @clkdm: काष्ठा घड़ीकरोमुख्य *
 *
 * Remove the "autodep" sleep & wakeup dependencies from घड़ीकरोमुख्य 'clkdm'
 * in hardware-supervised mode.  Meant to be called from घड़ी framework
 * when a घड़ी inside घड़ीकरोमुख्य 'clkdm' is disabled.  No वापस value.
 *
 * XXX स्वतःdeps are deprecated and should be हटाओd at the earliest
 * opportunity
 */
व्योम clkdm_del_स्वतःdeps(काष्ठा घड़ीकरोमुख्य *clkdm)
अणु
	काष्ठा clkdm_स्वतःdep *स्वतःdep;

	अगर (!स्वतःdeps || clkdm->flags & CLKDM_NO_AUTODEPS)
		वापस;

	क्रम (स्वतःdep = स्वतःdeps; स्वतःdep->clkdm.ptr; स्वतःdep++) अणु
		अगर (IS_ERR(स्वतःdep->clkdm.ptr))
			जारी;

		pr_debug("clockdomain: %s: removing %s sleepdep/wkdep\n",
			 clkdm->name, स्वतःdep->clkdm.ptr->name);

		_clkdm_del_sleepdep(clkdm, स्वतःdep->clkdm.ptr);
		_clkdm_del_wkdep(clkdm, स्वतःdep->clkdm.ptr);
	पूर्ण
पूर्ण

/* Clockकरोमुख्य-to-घड़ी/hwmod framework पूर्णांकerface code */

/**
 * clkdm_clk_enable - add an enabled करोwnstream घड़ी to this clkdm
 * @clkdm: काष्ठा घड़ीकरोमुख्य *
 * @clk: काष्ठा clk * of the enabled करोwnstream घड़ी
 *
 * Increment the usecount of the घड़ीकरोमुख्य @clkdm and ensure that it
 * is awake beक्रमe @clk is enabled.  Intended to be called by
 * clk_enable() code.  If the घड़ीकरोमुख्य is in software-supervised
 * idle mode, क्रमce the घड़ीकरोमुख्य to wake.  If the घड़ीकरोमुख्य is in
 * hardware-supervised idle mode, add clkdm-pwrdm स्वतःdependencies, to
 * ensure that devices in the घड़ीकरोमुख्य can be पढ़ो from/written to
 * by on-chip processors.  Returns -EINVAL अगर passed null poपूर्णांकers;
 * वापसs 0 upon success or अगर the घड़ीकरोमुख्य is in hwsup idle mode.
 */
पूर्णांक clkdm_clk_enable(काष्ठा घड़ीकरोमुख्य *clkdm, काष्ठा clk *unused)
अणु
	अगर (!clkdm || !arch_clkdm || !arch_clkdm->clkdm_clk_enable)
		वापस -EINVAL;

	pwrdm_lock(clkdm->pwrdm.ptr);

	/*
	 * For arch's with no स्वतःdeps, clkcm_clk_enable
	 * should be called क्रम every घड़ी instance or hwmod that is
	 * enabled, so the clkdm can be क्रमce woken up.
	 */
	clkdm->usecount++;
	अगर (clkdm->usecount > 1 && स्वतःdeps) अणु
		pwrdm_unlock(clkdm->pwrdm.ptr);
		वापस 0;
	पूर्ण

	arch_clkdm->clkdm_clk_enable(clkdm);
	pwrdm_state_चयन_nolock(clkdm->pwrdm.ptr);
	pwrdm_unlock(clkdm->pwrdm.ptr);

	pr_debug("clockdomain: %s: enabled\n", clkdm->name);

	वापस 0;
पूर्ण

/**
 * clkdm_clk_disable - हटाओ an enabled करोwnstream घड़ी from this clkdm
 * @clkdm: काष्ठा घड़ीकरोमुख्य *
 * @clk: काष्ठा clk * of the disabled करोwnstream घड़ी
 *
 * Decrement the usecount of this घड़ीकरोमुख्य @clkdm when @clk is
 * disabled.  Intended to be called by clk_disable() code.  If the
 * घड़ीकरोमुख्य usecount goes to 0, put the घड़ीकरोमुख्य to sleep
 * (software-supervised mode) or हटाओ the clkdm स्वतःdependencies
 * (hardware-supervised mode).  Returns -EINVAL अगर passed null
 * poपूर्णांकers; -दुस्फल अगर the @clkdm usecount underflows; or वापसs 0
 * upon success or अगर the घड़ीकरोमुख्य is in hwsup idle mode.
 */
पूर्णांक clkdm_clk_disable(काष्ठा घड़ीकरोमुख्य *clkdm, काष्ठा clk *clk)
अणु
	अगर (!clkdm || !arch_clkdm || !arch_clkdm->clkdm_clk_disable)
		वापस -EINVAL;

	pwrdm_lock(clkdm->pwrdm.ptr);

	/* corner हाल: disabling unused घड़ीs */
	अगर (clk && (__clk_get_enable_count(clk) == 0) && clkdm->usecount == 0)
		जाओ ccd_निकास;

	अगर (clkdm->usecount == 0) अणु
		pwrdm_unlock(clkdm->pwrdm.ptr);
		WARN_ON(1); /* underflow */
		वापस -दुस्फल;
	पूर्ण

	clkdm->usecount--;
	अगर (clkdm->usecount > 0) अणु
		pwrdm_unlock(clkdm->pwrdm.ptr);
		वापस 0;
	पूर्ण

	arch_clkdm->clkdm_clk_disable(clkdm);
	pwrdm_state_चयन_nolock(clkdm->pwrdm.ptr);

	pr_debug("clockdomain: %s: disabled\n", clkdm->name);

ccd_निकास:
	pwrdm_unlock(clkdm->pwrdm.ptr);

	वापस 0;
पूर्ण

/**
 * clkdm_hwmod_enable - add an enabled करोwnstream hwmod to this clkdm
 * @clkdm: काष्ठा घड़ीकरोमुख्य *
 * @oh: काष्ठा omap_hwmod * of the enabled करोwnstream hwmod
 *
 * Increment the usecount of the घड़ीकरोमुख्य @clkdm and ensure that it
 * is awake beक्रमe @oh is enabled. Intended to be called by
 * module_enable() code.
 * If the घड़ीकरोमुख्य is in software-supervised idle mode, क्रमce the
 * घड़ीकरोमुख्य to wake.  If the घड़ीकरोमुख्य is in hardware-supervised idle
 * mode, add clkdm-pwrdm स्वतःdependencies, to ensure that devices in the
 * घड़ीकरोमुख्य can be पढ़ो from/written to by on-chip processors.
 * Returns -EINVAL अगर passed null poपूर्णांकers;
 * वापसs 0 upon success or अगर the घड़ीकरोमुख्य is in hwsup idle mode.
 */
पूर्णांक clkdm_hwmod_enable(काष्ठा घड़ीकरोमुख्य *clkdm, काष्ठा omap_hwmod *oh)
अणु
	/* The clkdm attribute करोes not exist yet prior OMAP4 */
	अगर (cpu_is_omap24xx() || cpu_is_omap34xx())
		वापस 0;

	/*
	 * XXX Reग_लिखो this code to मुख्यtain a list of enabled
	 * करोwnstream hwmods क्रम debugging purposes?
	 */

	अगर (!oh)
		वापस -EINVAL;

	वापस clkdm_clk_enable(clkdm, शून्य);
पूर्ण

/**
 * clkdm_hwmod_disable - हटाओ an enabled करोwnstream hwmod from this clkdm
 * @clkdm: काष्ठा घड़ीकरोमुख्य *
 * @oh: काष्ठा omap_hwmod * of the disabled करोwnstream hwmod
 *
 * Decrement the usecount of this घड़ीकरोमुख्य @clkdm when @oh is
 * disabled. Intended to be called by module_disable() code.
 * If the घड़ीकरोमुख्य usecount goes to 0, put the घड़ीकरोमुख्य to sleep
 * (software-supervised mode) or हटाओ the clkdm स्वतःdependencies
 * (hardware-supervised mode).
 * Returns -EINVAL अगर passed null poपूर्णांकers; -दुस्फल अगर the @clkdm usecount
 * underflows; or वापसs 0 upon success or अगर the घड़ीकरोमुख्य is in hwsup
 * idle mode.
 */
पूर्णांक clkdm_hwmod_disable(काष्ठा घड़ीकरोमुख्य *clkdm, काष्ठा omap_hwmod *oh)
अणु
	/* The clkdm attribute करोes not exist yet prior OMAP4 */
	अगर (cpu_is_omap24xx() || cpu_is_omap34xx())
		वापस 0;

	अगर (!oh)
		वापस -EINVAL;

	वापस clkdm_clk_disable(clkdm, शून्य);
पूर्ण

/**
 * _clkdm_save_context - save the context क्रम the control of this clkdm
 *
 * Due to a suspend or hibernation operation, the state of the रेजिस्टरs
 * controlling this clkdm will be lost, save their context.
 */
अटल पूर्णांक _clkdm_save_context(काष्ठा घड़ीकरोमुख्य *clkdm, व्योम *unused)
अणु
	अगर (!arch_clkdm || !arch_clkdm->clkdm_save_context)
		वापस -EINVAL;

	वापस arch_clkdm->clkdm_save_context(clkdm);
पूर्ण

/**
 * _clkdm_restore_context - restore context क्रम control of this clkdm
 *
 * Restore the रेजिस्टर values क्रम this घड़ीकरोमुख्य.
 */
अटल पूर्णांक _clkdm_restore_context(काष्ठा घड़ीकरोमुख्य *clkdm, व्योम *unused)
अणु
	अगर (!arch_clkdm || !arch_clkdm->clkdm_restore_context)
		वापस -EINVAL;

	वापस arch_clkdm->clkdm_restore_context(clkdm);
पूर्ण

/**
 * clkdm_save_context - Saves the context क्रम each रेजिस्टरed clkdm
 *
 * Save the context क्रम each रेजिस्टरed घड़ीकरोमुख्य.
 */
व्योम clkdm_save_context(व्योम)
अणु
	clkdm_क्रम_each(_clkdm_save_context, शून्य);
पूर्ण

/**
 * clkdm_restore_context - Restores the context क्रम each रेजिस्टरed clkdm
 *
 * Restore the context क्रम each रेजिस्टरed घड़ीकरोमुख्य.
 */
व्योम clkdm_restore_context(व्योम)
अणु
	clkdm_क्रम_each(_clkdm_restore_context, शून्य);
पूर्ण
