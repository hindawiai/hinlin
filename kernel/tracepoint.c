<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2008-2014 Mathieu Desnoyers
 */
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/types.h>
#समावेश <linux/jhash.h>
#समावेश <linux/list.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/अटल_key.h>

बाह्य tracepoपूर्णांक_ptr_t __start___tracepoपूर्णांकs_ptrs[];
बाह्य tracepoपूर्णांक_ptr_t __stop___tracepoपूर्णांकs_ptrs[];

DEFINE_SRCU(tracepoपूर्णांक_srcu);
EXPORT_SYMBOL_GPL(tracepoपूर्णांक_srcu);

/* Set to 1 to enable tracepoपूर्णांक debug output */
अटल स्थिर पूर्णांक tracepoपूर्णांक_debug;

#अगर_घोषित CONFIG_MODULES
/*
 * Tracepoपूर्णांक module list mutex protects the local module list.
 */
अटल DEFINE_MUTEX(tracepoपूर्णांक_module_list_mutex);

/* Local list of काष्ठा tp_module */
अटल LIST_HEAD(tracepoपूर्णांक_module_list);
#पूर्ण_अगर /* CONFIG_MODULES */

/*
 * tracepoपूर्णांकs_mutex protects the builtin and module tracepoपूर्णांकs.
 * tracepoपूर्णांकs_mutex nests inside tracepoपूर्णांक_module_list_mutex.
 */
अटल DEFINE_MUTEX(tracepoपूर्णांकs_mutex);

अटल काष्ठा rcu_head *early_probes;
अटल bool ok_to_मुक्त_tracepoपूर्णांकs;

/*
 * Note about RCU :
 * It is used to delay the मुक्त of multiple probes array until a quiescent
 * state is reached.
 */
काष्ठा tp_probes अणु
	काष्ठा rcu_head rcu;
	काष्ठा tracepoपूर्णांक_func probes[];
पूर्ण;

/* Called in removal of a func but failed to allocate a new tp_funcs */
अटल व्योम tp_stub_func(व्योम)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम *allocate_probes(पूर्णांक count)
अणु
	काष्ठा tp_probes *p  = kदो_स्मृति(काष्ठा_size(p, probes, count),
				       GFP_KERNEL);
	वापस p == शून्य ? शून्य : p->probes;
पूर्ण

अटल व्योम srcu_मुक्त_old_probes(काष्ठा rcu_head *head)
अणु
	kमुक्त(container_of(head, काष्ठा tp_probes, rcu));
पूर्ण

अटल व्योम rcu_मुक्त_old_probes(काष्ठा rcu_head *head)
अणु
	call_srcu(&tracepoपूर्णांक_srcu, head, srcu_मुक्त_old_probes);
पूर्ण

अटल __init पूर्णांक release_early_probes(व्योम)
अणु
	काष्ठा rcu_head *पंचांगp;

	ok_to_मुक्त_tracepoपूर्णांकs = true;

	जबतक (early_probes) अणु
		पंचांगp = early_probes;
		early_probes = पंचांगp->next;
		call_rcu(पंचांगp, rcu_मुक्त_old_probes);
	पूर्ण

	वापस 0;
पूर्ण

/* SRCU is initialized at core_initcall */
postcore_initcall(release_early_probes);

अटल अंतरभूत व्योम release_probes(काष्ठा tracepoपूर्णांक_func *old)
अणु
	अगर (old) अणु
		काष्ठा tp_probes *tp_probes = container_of(old,
			काष्ठा tp_probes, probes[0]);

		/*
		 * We can't मुक्त probes अगर SRCU is not initialized yet.
		 * Postpone the मुक्तing till after SRCU is initialized.
		 */
		अगर (unlikely(!ok_to_मुक्त_tracepoपूर्णांकs)) अणु
			tp_probes->rcu.next = early_probes;
			early_probes = &tp_probes->rcu;
			वापस;
		पूर्ण

		/*
		 * Tracepoपूर्णांक probes are रक्षित by both sched RCU and SRCU,
		 * by calling the SRCU callback in the sched RCU callback we
		 * cover both हालs. So let us chain the SRCU and sched RCU
		 * callbacks to रुको क्रम both grace periods.
		 */
		call_rcu(&tp_probes->rcu, rcu_मुक्त_old_probes);
	पूर्ण
पूर्ण

अटल व्योम debug_prपूर्णांक_probes(काष्ठा tracepoपूर्णांक_func *funcs)
अणु
	पूर्णांक i;

	अगर (!tracepoपूर्णांक_debug || !funcs)
		वापस;

	क्रम (i = 0; funcs[i].func; i++)
		prपूर्णांकk(KERN_DEBUG "Probe %d : %p\n", i, funcs[i].func);
पूर्ण

अटल काष्ठा tracepoपूर्णांक_func *
func_add(काष्ठा tracepoपूर्णांक_func **funcs, काष्ठा tracepoपूर्णांक_func *tp_func,
	 पूर्णांक prio)
अणु
	काष्ठा tracepoपूर्णांक_func *old, *new;
	पूर्णांक iter_probes;	/* Iterate over old probe array. */
	पूर्णांक nr_probes = 0;	/* Counter क्रम probes */
	पूर्णांक pos = -1;		/* Insertion position पूर्णांकo new array */

	अगर (WARN_ON(!tp_func->func))
		वापस ERR_PTR(-EINVAL);

	debug_prपूर्णांक_probes(*funcs);
	old = *funcs;
	अगर (old) अणु
		/* (N -> N+1), (N != 0, 1) probes */
		क्रम (iter_probes = 0; old[iter_probes].func; iter_probes++) अणु
			अगर (old[iter_probes].func == tp_stub_func)
				जारी;	/* Skip stub functions. */
			अगर (old[iter_probes].func == tp_func->func &&
			    old[iter_probes].data == tp_func->data)
				वापस ERR_PTR(-EEXIST);
			nr_probes++;
		पूर्ण
	पूर्ण
	/* + 2 : one क्रम new probe, one क्रम शून्य func */
	new = allocate_probes(nr_probes + 2);
	अगर (new == शून्य)
		वापस ERR_PTR(-ENOMEM);
	अगर (old) अणु
		nr_probes = 0;
		क्रम (iter_probes = 0; old[iter_probes].func; iter_probes++) अणु
			अगर (old[iter_probes].func == tp_stub_func)
				जारी;
			/* Insert beक्रमe probes of lower priority */
			अगर (pos < 0 && old[iter_probes].prio < prio)
				pos = nr_probes++;
			new[nr_probes++] = old[iter_probes];
		पूर्ण
		अगर (pos < 0)
			pos = nr_probes++;
		/* nr_probes now poपूर्णांकs to the end of the new array */
	पूर्ण अन्यथा अणु
		pos = 0;
		nr_probes = 1; /* must poपूर्णांक at end of array */
	पूर्ण
	new[pos] = *tp_func;
	new[nr_probes].func = शून्य;
	*funcs = new;
	debug_prपूर्णांक_probes(*funcs);
	वापस old;
पूर्ण

अटल व्योम *func_हटाओ(काष्ठा tracepoपूर्णांक_func **funcs,
		काष्ठा tracepoपूर्णांक_func *tp_func)
अणु
	पूर्णांक nr_probes = 0, nr_del = 0, i;
	काष्ठा tracepoपूर्णांक_func *old, *new;

	old = *funcs;

	अगर (!old)
		वापस ERR_PTR(-ENOENT);

	debug_prपूर्णांक_probes(*funcs);
	/* (N -> M), (N > 1, M >= 0) probes */
	अगर (tp_func->func) अणु
		क्रम (nr_probes = 0; old[nr_probes].func; nr_probes++) अणु
			अगर ((old[nr_probes].func == tp_func->func &&
			     old[nr_probes].data == tp_func->data) ||
			    old[nr_probes].func == tp_stub_func)
				nr_del++;
		पूर्ण
	पूर्ण

	/*
	 * If probe is शून्य, then nr_probes = nr_del = 0, and then the
	 * entire entry will be हटाओd.
	 */
	अगर (nr_probes - nr_del == 0) अणु
		/* N -> 0, (N > 1) */
		*funcs = शून्य;
		debug_prपूर्णांक_probes(*funcs);
		वापस old;
	पूर्ण अन्यथा अणु
		पूर्णांक j = 0;
		/* N -> M, (N > 1, M > 0) */
		/* + 1 क्रम शून्य */
		new = allocate_probes(nr_probes - nr_del + 1);
		अगर (new) अणु
			क्रम (i = 0; old[i].func; i++) अणु
				अगर ((old[i].func != tp_func->func ||
				     old[i].data != tp_func->data) &&
				    old[i].func != tp_stub_func)
					new[j++] = old[i];
			पूर्ण
			new[nr_probes - nr_del].func = शून्य;
			*funcs = new;
		पूर्ण अन्यथा अणु
			/*
			 * Failed to allocate, replace the old function
			 * with calls to tp_stub_func.
			 */
			क्रम (i = 0; old[i].func; i++) अणु
				अगर (old[i].func == tp_func->func &&
				    old[i].data == tp_func->data)
					WRITE_ONCE(old[i].func, tp_stub_func);
			पूर्ण
			*funcs = old;
		पूर्ण
	पूर्ण
	debug_prपूर्णांक_probes(*funcs);
	वापस old;
पूर्ण

अटल व्योम tracepoपूर्णांक_update_call(काष्ठा tracepoपूर्णांक *tp, काष्ठा tracepoपूर्णांक_func *tp_funcs, bool sync)
अणु
	व्योम *func = tp->iterator;

	/* Synthetic events करो not have अटल call sites */
	अगर (!tp->अटल_call_key)
		वापस;

	अगर (!tp_funcs[1].func) अणु
		func = tp_funcs[0].func;
		/*
		 * If going from the iterator back to a single caller,
		 * we need to synchronize with __DO_TRACE to make sure
		 * that the data passed to the callback is the one that
		 * beदीर्घs to that callback.
		 */
		अगर (sync)
			tracepoपूर्णांक_synchronize_unरेजिस्टर();
	पूर्ण

	__अटल_call_update(tp->अटल_call_key, tp->अटल_call_tramp, func);
पूर्ण

/*
 * Add the probe function to a tracepoपूर्णांक.
 */
अटल पूर्णांक tracepoपूर्णांक_add_func(काष्ठा tracepoपूर्णांक *tp,
			       काष्ठा tracepoपूर्णांक_func *func, पूर्णांक prio)
अणु
	काष्ठा tracepoपूर्णांक_func *old, *tp_funcs;
	पूर्णांक ret;

	अगर (tp->regfunc && !अटल_key_enabled(&tp->key)) अणु
		ret = tp->regfunc();
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	tp_funcs = rcu_dereference_रक्षित(tp->funcs,
			lockdep_is_held(&tracepoपूर्णांकs_mutex));
	old = func_add(&tp_funcs, func, prio);
	अगर (IS_ERR(old)) अणु
		WARN_ON_ONCE(PTR_ERR(old) != -ENOMEM);
		वापस PTR_ERR(old);
	पूर्ण

	/*
	 * rcu_assign_poपूर्णांकer has as smp_store_release() which makes sure
	 * that the new probe callbacks array is consistent beक्रमe setting
	 * a poपूर्णांकer to it.  This array is referenced by __DO_TRACE from
	 * include/linux/tracepoपूर्णांक.h using rcu_dereference_sched().
	 */
	rcu_assign_poपूर्णांकer(tp->funcs, tp_funcs);
	tracepoपूर्णांक_update_call(tp, tp_funcs, false);
	अटल_key_enable(&tp->key);

	release_probes(old);
	वापस 0;
पूर्ण

/*
 * Remove a probe function from a tracepoपूर्णांक.
 * Note: only रुकोing an RCU period after setting elem->call to the empty
 * function insures that the original callback is not used anymore. This insured
 * by preempt_disable around the call site.
 */
अटल पूर्णांक tracepoपूर्णांक_हटाओ_func(काष्ठा tracepoपूर्णांक *tp,
		काष्ठा tracepoपूर्णांक_func *func)
अणु
	काष्ठा tracepoपूर्णांक_func *old, *tp_funcs;

	tp_funcs = rcu_dereference_रक्षित(tp->funcs,
			lockdep_is_held(&tracepoपूर्णांकs_mutex));
	old = func_हटाओ(&tp_funcs, func);
	अगर (WARN_ON_ONCE(IS_ERR(old)))
		वापस PTR_ERR(old);

	अगर (tp_funcs == old)
		/* Failed allocating new tp_funcs, replaced func with stub */
		वापस 0;

	अगर (!tp_funcs) अणु
		/* Removed last function */
		अगर (tp->unregfunc && अटल_key_enabled(&tp->key))
			tp->unregfunc();

		अटल_key_disable(&tp->key);
		rcu_assign_poपूर्णांकer(tp->funcs, tp_funcs);
	पूर्ण अन्यथा अणु
		rcu_assign_poपूर्णांकer(tp->funcs, tp_funcs);
		tracepoपूर्णांक_update_call(tp, tp_funcs,
				       tp_funcs[0].func != old[0].func);
	पूर्ण
	release_probes(old);
	वापस 0;
पूर्ण

/**
 * tracepoपूर्णांक_probe_रेजिस्टर_prio -  Connect a probe to a tracepoपूर्णांक with priority
 * @tp: tracepoपूर्णांक
 * @probe: probe handler
 * @data: tracepoपूर्णांक data
 * @prio: priority of this function over other रेजिस्टरed functions
 *
 * Returns 0 अगर ok, error value on error.
 * Note: अगर @tp is within a module, the caller is responsible क्रम
 * unरेजिस्टरing the probe beक्रमe the module is gone. This can be
 * perक्रमmed either with a tracepoपूर्णांक module going notअगरier, or from
 * within module निकास functions.
 */
पूर्णांक tracepoपूर्णांक_probe_रेजिस्टर_prio(काष्ठा tracepoपूर्णांक *tp, व्योम *probe,
				   व्योम *data, पूर्णांक prio)
अणु
	काष्ठा tracepoपूर्णांक_func tp_func;
	पूर्णांक ret;

	mutex_lock(&tracepoपूर्णांकs_mutex);
	tp_func.func = probe;
	tp_func.data = data;
	tp_func.prio = prio;
	ret = tracepoपूर्णांक_add_func(tp, &tp_func, prio);
	mutex_unlock(&tracepoपूर्णांकs_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tracepoपूर्णांक_probe_रेजिस्टर_prio);

/**
 * tracepoपूर्णांक_probe_रेजिस्टर -  Connect a probe to a tracepoपूर्णांक
 * @tp: tracepoपूर्णांक
 * @probe: probe handler
 * @data: tracepoपूर्णांक data
 *
 * Returns 0 अगर ok, error value on error.
 * Note: अगर @tp is within a module, the caller is responsible क्रम
 * unरेजिस्टरing the probe beक्रमe the module is gone. This can be
 * perक्रमmed either with a tracepoपूर्णांक module going notअगरier, or from
 * within module निकास functions.
 */
पूर्णांक tracepoपूर्णांक_probe_रेजिस्टर(काष्ठा tracepoपूर्णांक *tp, व्योम *probe, व्योम *data)
अणु
	वापस tracepoपूर्णांक_probe_रेजिस्टर_prio(tp, probe, data, TRACEPOINT_DEFAULT_PRIO);
पूर्ण
EXPORT_SYMBOL_GPL(tracepoपूर्णांक_probe_रेजिस्टर);

/**
 * tracepoपूर्णांक_probe_unरेजिस्टर -  Disconnect a probe from a tracepoपूर्णांक
 * @tp: tracepoपूर्णांक
 * @probe: probe function poपूर्णांकer
 * @data: tracepoपूर्णांक data
 *
 * Returns 0 अगर ok, error value on error.
 */
पूर्णांक tracepoपूर्णांक_probe_unरेजिस्टर(काष्ठा tracepoपूर्णांक *tp, व्योम *probe, व्योम *data)
अणु
	काष्ठा tracepoपूर्णांक_func tp_func;
	पूर्णांक ret;

	mutex_lock(&tracepoपूर्णांकs_mutex);
	tp_func.func = probe;
	tp_func.data = data;
	ret = tracepoपूर्णांक_हटाओ_func(tp, &tp_func);
	mutex_unlock(&tracepoपूर्णांकs_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tracepoपूर्णांक_probe_unरेजिस्टर);

अटल व्योम क्रम_each_tracepoपूर्णांक_range(
		tracepoपूर्णांक_ptr_t *begin, tracepoपूर्णांक_ptr_t *end,
		व्योम (*fct)(काष्ठा tracepoपूर्णांक *tp, व्योम *priv),
		व्योम *priv)
अणु
	tracepoपूर्णांक_ptr_t *iter;

	अगर (!begin)
		वापस;
	क्रम (iter = begin; iter < end; iter++)
		fct(tracepoपूर्णांक_ptr_deref(iter), priv);
पूर्ण

#अगर_घोषित CONFIG_MODULES
bool trace_module_has_bad_taपूर्णांक(काष्ठा module *mod)
अणु
	वापस mod->taपूर्णांकs & ~((1 << TAINT_OOT_MODULE) | (1 << TAINT_CRAP) |
			       (1 << TAINT_UNSIGNED_MODULE));
पूर्ण

अटल BLOCKING_NOTIFIER_HEAD(tracepoपूर्णांक_notअगरy_list);

/**
 * रेजिस्टर_tracepoपूर्णांक_notअगरier - रेजिस्टर tracepoपूर्णांक coming/going notअगरier
 * @nb: notअगरier block
 *
 * Notअगरiers रेजिस्टरed with this function are called on module
 * coming/going with the tracepoपूर्णांक_module_list_mutex held.
 * The notअगरier block callback should expect a "struct tp_module" data
 * poपूर्णांकer.
 */
पूर्णांक रेजिस्टर_tracepoपूर्णांक_module_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	काष्ठा tp_module *tp_mod;
	पूर्णांक ret;

	mutex_lock(&tracepoपूर्णांक_module_list_mutex);
	ret = blocking_notअगरier_chain_रेजिस्टर(&tracepoपूर्णांक_notअगरy_list, nb);
	अगर (ret)
		जाओ end;
	list_क्रम_each_entry(tp_mod, &tracepoपूर्णांक_module_list, list)
		(व्योम) nb->notअगरier_call(nb, MODULE_STATE_COMING, tp_mod);
end:
	mutex_unlock(&tracepoपूर्णांक_module_list_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_tracepoपूर्णांक_module_notअगरier);

/**
 * unरेजिस्टर_tracepoपूर्णांक_notअगरier - unरेजिस्टर tracepoपूर्णांक coming/going notअगरier
 * @nb: notअगरier block
 *
 * The notअगरier block callback should expect a "struct tp_module" data
 * poपूर्णांकer.
 */
पूर्णांक unरेजिस्टर_tracepoपूर्णांक_module_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	काष्ठा tp_module *tp_mod;
	पूर्णांक ret;

	mutex_lock(&tracepoपूर्णांक_module_list_mutex);
	ret = blocking_notअगरier_chain_unरेजिस्टर(&tracepoपूर्णांक_notअगरy_list, nb);
	अगर (ret)
		जाओ end;
	list_क्रम_each_entry(tp_mod, &tracepoपूर्णांक_module_list, list)
		(व्योम) nb->notअगरier_call(nb, MODULE_STATE_GOING, tp_mod);
end:
	mutex_unlock(&tracepoपूर्णांक_module_list_mutex);
	वापस ret;

पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_tracepoपूर्णांक_module_notअगरier);

/*
 * Ensure the tracer unरेजिस्टरed the module's probes beक्रमe the module
 * tearकरोwn is perक्रमmed. Prevents leaks of probe and data poपूर्णांकers.
 */
अटल व्योम tp_module_going_check_quiescent(काष्ठा tracepoपूर्णांक *tp, व्योम *priv)
अणु
	WARN_ON_ONCE(tp->funcs);
पूर्ण

अटल पूर्णांक tracepoपूर्णांक_module_coming(काष्ठा module *mod)
अणु
	काष्ठा tp_module *tp_mod;
	पूर्णांक ret = 0;

	अगर (!mod->num_tracepoपूर्णांकs)
		वापस 0;

	/*
	 * We skip modules that taपूर्णांक the kernel, especially those with dअगरferent
	 * module headers (क्रम क्रमced load), to make sure we करोn't cause a crash.
	 * Staging, out-of-tree, and अचिन्हित GPL modules are fine.
	 */
	अगर (trace_module_has_bad_taपूर्णांक(mod))
		वापस 0;
	mutex_lock(&tracepoपूर्णांक_module_list_mutex);
	tp_mod = kदो_स्मृति(माप(काष्ठा tp_module), GFP_KERNEL);
	अगर (!tp_mod) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण
	tp_mod->mod = mod;
	list_add_tail(&tp_mod->list, &tracepoपूर्णांक_module_list);
	blocking_notअगरier_call_chain(&tracepoपूर्णांक_notअगरy_list,
			MODULE_STATE_COMING, tp_mod);
end:
	mutex_unlock(&tracepoपूर्णांक_module_list_mutex);
	वापस ret;
पूर्ण

अटल व्योम tracepoपूर्णांक_module_going(काष्ठा module *mod)
अणु
	काष्ठा tp_module *tp_mod;

	अगर (!mod->num_tracepoपूर्णांकs)
		वापस;

	mutex_lock(&tracepoपूर्णांक_module_list_mutex);
	list_क्रम_each_entry(tp_mod, &tracepoपूर्णांक_module_list, list) अणु
		अगर (tp_mod->mod == mod) अणु
			blocking_notअगरier_call_chain(&tracepoपूर्णांक_notअगरy_list,
					MODULE_STATE_GOING, tp_mod);
			list_del(&tp_mod->list);
			kमुक्त(tp_mod);
			/*
			 * Called the going notअगरier beक्रमe checking क्रम
			 * quiescence.
			 */
			क्रम_each_tracepoपूर्णांक_range(mod->tracepoपूर्णांकs_ptrs,
				mod->tracepoपूर्णांकs_ptrs + mod->num_tracepoपूर्णांकs,
				tp_module_going_check_quiescent, शून्य);
			अवरोध;
		पूर्ण
	पूर्ण
	/*
	 * In the हाल of modules that were taपूर्णांकed at "coming", we'll simply
	 * walk through the list without finding it. We cannot use the "tainted"
	 * flag on "going", in हाल a module taपूर्णांकs the kernel only after being
	 * loaded.
	 */
	mutex_unlock(&tracepoपूर्णांक_module_list_mutex);
पूर्ण

अटल पूर्णांक tracepoपूर्णांक_module_notअगरy(काष्ठा notअगरier_block *self,
		अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा module *mod = data;
	पूर्णांक ret = 0;

	चयन (val) अणु
	हाल MODULE_STATE_COMING:
		ret = tracepoपूर्णांक_module_coming(mod);
		अवरोध;
	हाल MODULE_STATE_LIVE:
		अवरोध;
	हाल MODULE_STATE_GOING:
		tracepoपूर्णांक_module_going(mod);
		अवरोध;
	हाल MODULE_STATE_UNFORMED:
		अवरोध;
	पूर्ण
	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

अटल काष्ठा notअगरier_block tracepoपूर्णांक_module_nb = अणु
	.notअगरier_call = tracepoपूर्णांक_module_notअगरy,
	.priority = 0,
पूर्ण;

अटल __init पूर्णांक init_tracepoपूर्णांकs(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_module_notअगरier(&tracepoपूर्णांक_module_nb);
	अगर (ret)
		pr_warn("Failed to register tracepoint module enter notifier\n");

	वापस ret;
पूर्ण
__initcall(init_tracepoपूर्णांकs);
#पूर्ण_अगर /* CONFIG_MODULES */

/**
 * क्रम_each_kernel_tracepoपूर्णांक - iteration on all kernel tracepoपूर्णांकs
 * @fct: callback
 * @priv: निजी data
 */
व्योम क्रम_each_kernel_tracepoपूर्णांक(व्योम (*fct)(काष्ठा tracepoपूर्णांक *tp, व्योम *priv),
		व्योम *priv)
अणु
	क्रम_each_tracepoपूर्णांक_range(__start___tracepoपूर्णांकs_ptrs,
		__stop___tracepoपूर्णांकs_ptrs, fct, priv);
पूर्ण
EXPORT_SYMBOL_GPL(क्रम_each_kernel_tracepoपूर्णांक);

#अगर_घोषित CONFIG_HAVE_SYSCALL_TRACEPOINTS

/* NB: reg/unreg are called जबतक guarded with the tracepoपूर्णांकs_mutex */
अटल पूर्णांक sys_tracepoपूर्णांक_refcount;

पूर्णांक syscall_regfunc(व्योम)
अणु
	काष्ठा task_काष्ठा *p, *t;

	अगर (!sys_tracepoपूर्णांक_refcount) अणु
		पढ़ो_lock(&tasklist_lock);
		क्रम_each_process_thपढ़ो(p, t) अणु
			set_task_syscall_work(t, SYSCALL_TRACEPOINT);
		पूर्ण
		पढ़ो_unlock(&tasklist_lock);
	पूर्ण
	sys_tracepoपूर्णांक_refcount++;

	वापस 0;
पूर्ण

व्योम syscall_unregfunc(व्योम)
अणु
	काष्ठा task_काष्ठा *p, *t;

	sys_tracepoपूर्णांक_refcount--;
	अगर (!sys_tracepoपूर्णांक_refcount) अणु
		पढ़ो_lock(&tasklist_lock);
		क्रम_each_process_thपढ़ो(p, t) अणु
			clear_task_syscall_work(t, SYSCALL_TRACEPOINT);
		पूर्ण
		पढ़ो_unlock(&tasklist_lock);
	पूर्ण
पूर्ण
#पूर्ण_अगर
