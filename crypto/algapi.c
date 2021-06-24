<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API क्रम algorithms (i.e., low-level API).
 *
 * Copyright (c) 2006 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <crypto/algapi.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fips.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश "internal.h"

अटल LIST_HEAD(crypto_ढाँचा_list);

अटल अंतरभूत व्योम crypto_check_module_sig(काष्ठा module *mod)
अणु
	अगर (fips_enabled && mod && !module_sig_ok(mod))
		panic("Module %s signature verification failed in FIPS mode\n",
		      module_name(mod));
पूर्ण

अटल पूर्णांक crypto_check_alg(काष्ठा crypto_alg *alg)
अणु
	crypto_check_module_sig(alg->cra_module);

	अगर (!alg->cra_name[0] || !alg->cra_driver_name[0])
		वापस -EINVAL;

	अगर (alg->cra_alignmask & (alg->cra_alignmask + 1))
		वापस -EINVAL;

	/* General maximums क्रम all algs. */
	अगर (alg->cra_alignmask > MAX_ALGAPI_ALIGNMASK)
		वापस -EINVAL;

	अगर (alg->cra_blocksize > MAX_ALGAPI_BLOCKSIZE)
		वापस -EINVAL;

	/* Lower maximums क्रम specअगरic alg types. */
	अगर (!alg->cra_type && (alg->cra_flags & CRYPTO_ALG_TYPE_MASK) ==
			       CRYPTO_ALG_TYPE_CIPHER) अणु
		अगर (alg->cra_alignmask > MAX_CIPHER_ALIGNMASK)
			वापस -EINVAL;

		अगर (alg->cra_blocksize > MAX_CIPHER_BLOCKSIZE)
			वापस -EINVAL;
	पूर्ण

	अगर (alg->cra_priority < 0)
		वापस -EINVAL;

	refcount_set(&alg->cra_refcnt, 1);

	वापस 0;
पूर्ण

अटल व्योम crypto_मुक्त_instance(काष्ठा crypto_instance *inst)
अणु
	inst->alg.cra_type->मुक्त(inst);
पूर्ण

अटल व्योम crypto_destroy_instance(काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_instance *inst = (व्योम *)alg;
	काष्ठा crypto_ढाँचा *पंचांगpl = inst->पंचांगpl;

	crypto_मुक्त_instance(inst);
	crypto_पंचांगpl_put(पंचांगpl);
पूर्ण

/*
 * This function adds a spawn to the list secondary_spawns which
 * will be used at the end of crypto_हटाओ_spawns to unरेजिस्टर
 * instances, unless the spawn happens to be one that is depended
 * on by the new algorithm (nalg in crypto_हटाओ_spawns).
 *
 * This function is also responsible क्रम resurrecting any algorithms
 * in the dependency chain of nalg by unsetting n->dead.
 */
अटल काष्ठा list_head *crypto_more_spawns(काष्ठा crypto_alg *alg,
					    काष्ठा list_head *stack,
					    काष्ठा list_head *top,
					    काष्ठा list_head *secondary_spawns)
अणु
	काष्ठा crypto_spawn *spawn, *n;

	spawn = list_first_entry_or_null(stack, काष्ठा crypto_spawn, list);
	अगर (!spawn)
		वापस शून्य;

	n = list_prev_entry(spawn, list);
	list_move(&spawn->list, secondary_spawns);

	अगर (list_is_last(&n->list, stack))
		वापस top;

	n = list_next_entry(n, list);
	अगर (!spawn->dead)
		n->dead = false;

	वापस &n->inst->alg.cra_users;
पूर्ण

अटल व्योम crypto_हटाओ_instance(काष्ठा crypto_instance *inst,
				   काष्ठा list_head *list)
अणु
	काष्ठा crypto_ढाँचा *पंचांगpl = inst->पंचांगpl;

	अगर (crypto_is_dead(&inst->alg))
		वापस;

	inst->alg.cra_flags |= CRYPTO_ALG_DEAD;

	अगर (!पंचांगpl || !crypto_पंचांगpl_get(पंचांगpl))
		वापस;

	list_move(&inst->alg.cra_list, list);
	hlist_del(&inst->list);
	inst->alg.cra_destroy = crypto_destroy_instance;

	BUG_ON(!list_empty(&inst->alg.cra_users));
पूर्ण

/*
 * Given an algorithm alg, हटाओ all algorithms that depend on it
 * through spawns.  If nalg is not null, then exempt any algorithms
 * that is depended on by nalg.  This is useful when nalg itself
 * depends on alg.
 */
व्योम crypto_हटाओ_spawns(काष्ठा crypto_alg *alg, काष्ठा list_head *list,
			  काष्ठा crypto_alg *nalg)
अणु
	u32 new_type = (nalg ?: alg)->cra_flags;
	काष्ठा crypto_spawn *spawn, *n;
	LIST_HEAD(secondary_spawns);
	काष्ठा list_head *spawns;
	LIST_HEAD(stack);
	LIST_HEAD(top);

	spawns = &alg->cra_users;
	list_क्रम_each_entry_safe(spawn, n, spawns, list) अणु
		अगर ((spawn->alg->cra_flags ^ new_type) & spawn->mask)
			जारी;

		list_move(&spawn->list, &top);
	पूर्ण

	/*
	 * Perक्रमm a depth-first walk starting from alg through
	 * the cra_users tree.  The list stack records the path
	 * from alg to the current spawn.
	 */
	spawns = &top;
	करो अणु
		जबतक (!list_empty(spawns)) अणु
			काष्ठा crypto_instance *inst;

			spawn = list_first_entry(spawns, काष्ठा crypto_spawn,
						 list);
			inst = spawn->inst;

			list_move(&spawn->list, &stack);
			spawn->dead = !spawn->रेजिस्टरed || &inst->alg != nalg;

			अगर (!spawn->रेजिस्टरed)
				अवरोध;

			BUG_ON(&inst->alg == alg);

			अगर (&inst->alg == nalg)
				अवरोध;

			spawns = &inst->alg.cra_users;

			/*
			 * Even अगर spawn->रेजिस्टरed is true, the
			 * instance itself may still be unरेजिस्टरed.
			 * This is because it may have failed during
			 * registration.  Thereक्रमe we still need to
			 * make the following test.
			 *
			 * We may encounter an unरेजिस्टरed instance here, since
			 * an instance's spawns are set up prior to the instance
			 * being रेजिस्टरed.  An unरेजिस्टरed instance will have
			 * शून्य ->cra_users.next, since ->cra_users isn't
			 * properly initialized until registration.  But an
			 * unरेजिस्टरed instance cannot have any users, so treat
			 * it the same as ->cra_users being empty.
			 */
			अगर (spawns->next == शून्य)
				अवरोध;
		पूर्ण
	पूर्ण जबतक ((spawns = crypto_more_spawns(alg, &stack, &top,
					      &secondary_spawns)));

	/*
	 * Remove all instances that are marked as dead.  Also
	 * complete the resurrection of the others by moving them
	 * back to the cra_users list.
	 */
	list_क्रम_each_entry_safe(spawn, n, &secondary_spawns, list) अणु
		अगर (!spawn->dead)
			list_move(&spawn->list, &spawn->alg->cra_users);
		अन्यथा अगर (spawn->रेजिस्टरed)
			crypto_हटाओ_instance(spawn->inst, list);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(crypto_हटाओ_spawns);

अटल काष्ठा crypto_larval *__crypto_रेजिस्टर_alg(काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_alg *q;
	काष्ठा crypto_larval *larval;
	पूर्णांक ret = -EAGAIN;

	अगर (crypto_is_dead(alg))
		जाओ err;

	INIT_LIST_HEAD(&alg->cra_users);

	/* No cheating! */
	alg->cra_flags &= ~CRYPTO_ALG_TESTED;

	ret = -EEXIST;

	list_क्रम_each_entry(q, &crypto_alg_list, cra_list) अणु
		अगर (q == alg)
			जाओ err;

		अगर (crypto_is_moribund(q))
			जारी;

		अगर (crypto_is_larval(q)) अणु
			अगर (!म_भेद(alg->cra_driver_name, q->cra_driver_name))
				जाओ err;
			जारी;
		पूर्ण

		अगर (!म_भेद(q->cra_driver_name, alg->cra_name) ||
		    !म_भेद(q->cra_name, alg->cra_driver_name))
			जाओ err;
	पूर्ण

	larval = crypto_larval_alloc(alg->cra_name,
				     alg->cra_flags | CRYPTO_ALG_TESTED, 0);
	अगर (IS_ERR(larval))
		जाओ out;

	ret = -ENOENT;
	larval->adult = crypto_mod_get(alg);
	अगर (!larval->adult)
		जाओ मुक्त_larval;

	refcount_set(&larval->alg.cra_refcnt, 1);
	स_नकल(larval->alg.cra_driver_name, alg->cra_driver_name,
	       CRYPTO_MAX_ALG_NAME);
	larval->alg.cra_priority = alg->cra_priority;

	list_add(&alg->cra_list, &crypto_alg_list);
	list_add(&larval->alg.cra_list, &crypto_alg_list);

	crypto_stats_init(alg);

out:
	वापस larval;

मुक्त_larval:
	kमुक्त(larval);
err:
	larval = ERR_PTR(ret);
	जाओ out;
पूर्ण

व्योम crypto_alg_tested(स्थिर अक्षर *name, पूर्णांक err)
अणु
	काष्ठा crypto_larval *test;
	काष्ठा crypto_alg *alg;
	काष्ठा crypto_alg *q;
	LIST_HEAD(list);
	bool best;

	करोwn_ग_लिखो(&crypto_alg_sem);
	list_क्रम_each_entry(q, &crypto_alg_list, cra_list) अणु
		अगर (crypto_is_moribund(q) || !crypto_is_larval(q))
			जारी;

		test = (काष्ठा crypto_larval *)q;

		अगर (!म_भेद(q->cra_driver_name, name))
			जाओ found;
	पूर्ण

	pr_err("alg: Unexpected test result for %s: %d\n", name, err);
	जाओ unlock;

found:
	q->cra_flags |= CRYPTO_ALG_DEAD;
	alg = test->adult;
	अगर (err || list_empty(&alg->cra_list))
		जाओ complete;

	alg->cra_flags |= CRYPTO_ALG_TESTED;

	/* Only satisfy larval रुकोers अगर we are the best. */
	best = true;
	list_क्रम_each_entry(q, &crypto_alg_list, cra_list) अणु
		अगर (crypto_is_moribund(q) || !crypto_is_larval(q))
			जारी;

		अगर (म_भेद(alg->cra_name, q->cra_name))
			जारी;

		अगर (q->cra_priority > alg->cra_priority) अणु
			best = false;
			अवरोध;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(q, &crypto_alg_list, cra_list) अणु
		अगर (q == alg)
			जारी;

		अगर (crypto_is_moribund(q))
			जारी;

		अगर (crypto_is_larval(q)) अणु
			काष्ठा crypto_larval *larval = (व्योम *)q;

			/*
			 * Check to see अगर either our generic name or
			 * specअगरic name can satisfy the name requested
			 * by the larval entry q.
			 */
			अगर (म_भेद(alg->cra_name, q->cra_name) &&
			    म_भेद(alg->cra_driver_name, q->cra_name))
				जारी;

			अगर (larval->adult)
				जारी;
			अगर ((q->cra_flags ^ alg->cra_flags) & larval->mask)
				जारी;

			अगर (best && crypto_mod_get(alg))
				larval->adult = alg;
			अन्यथा
				larval->adult = ERR_PTR(-EAGAIN);

			जारी;
		पूर्ण

		अगर (म_भेद(alg->cra_name, q->cra_name))
			जारी;

		अगर (म_भेद(alg->cra_driver_name, q->cra_driver_name) &&
		    q->cra_priority > alg->cra_priority)
			जारी;

		crypto_हटाओ_spawns(q, &list, alg);
	पूर्ण

complete:
	complete_all(&test->completion);

unlock:
	up_ग_लिखो(&crypto_alg_sem);

	crypto_हटाओ_final(&list);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_alg_tested);

व्योम crypto_हटाओ_final(काष्ठा list_head *list)
अणु
	काष्ठा crypto_alg *alg;
	काष्ठा crypto_alg *n;

	list_क्रम_each_entry_safe(alg, n, list, cra_list) अणु
		list_del_init(&alg->cra_list);
		crypto_alg_put(alg);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(crypto_हटाओ_final);

अटल व्योम crypto_रुको_क्रम_test(काष्ठा crypto_larval *larval)
अणु
	पूर्णांक err;

	err = crypto_probing_notअगरy(CRYPTO_MSG_ALG_REGISTER, larval->adult);
	अगर (err != NOTIFY_STOP) अणु
		अगर (WARN_ON(err != NOTIFY_DONE))
			जाओ out;
		crypto_alg_tested(larval->alg.cra_driver_name, 0);
	पूर्ण

	err = रुको_क्रम_completion_समाप्तable(&larval->completion);
	WARN_ON(err);
	अगर (!err)
		crypto_notअगरy(CRYPTO_MSG_ALG_LOADED, larval);

out:
	crypto_larval_समाप्त(&larval->alg);
पूर्ण

पूर्णांक crypto_रेजिस्टर_alg(काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_larval *larval;
	पूर्णांक err;

	alg->cra_flags &= ~CRYPTO_ALG_DEAD;
	err = crypto_check_alg(alg);
	अगर (err)
		वापस err;

	करोwn_ग_लिखो(&crypto_alg_sem);
	larval = __crypto_रेजिस्टर_alg(alg);
	up_ग_लिखो(&crypto_alg_sem);

	अगर (IS_ERR(larval))
		वापस PTR_ERR(larval);

	crypto_रुको_क्रम_test(larval);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_alg);

अटल पूर्णांक crypto_हटाओ_alg(काष्ठा crypto_alg *alg, काष्ठा list_head *list)
अणु
	अगर (unlikely(list_empty(&alg->cra_list)))
		वापस -ENOENT;

	alg->cra_flags |= CRYPTO_ALG_DEAD;

	list_del_init(&alg->cra_list);
	crypto_हटाओ_spawns(alg, list, शून्य);

	वापस 0;
पूर्ण

व्योम crypto_unरेजिस्टर_alg(काष्ठा crypto_alg *alg)
अणु
	पूर्णांक ret;
	LIST_HEAD(list);

	करोwn_ग_लिखो(&crypto_alg_sem);
	ret = crypto_हटाओ_alg(alg, &list);
	up_ग_लिखो(&crypto_alg_sem);

	अगर (WARN(ret, "Algorithm %s is not registered", alg->cra_driver_name))
		वापस;

	BUG_ON(refcount_पढ़ो(&alg->cra_refcnt) != 1);
	अगर (alg->cra_destroy)
		alg->cra_destroy(alg);

	crypto_हटाओ_final(&list);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_alg);

पूर्णांक crypto_रेजिस्टर_algs(काष्ठा crypto_alg *algs, पूर्णांक count)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < count; i++) अणु
		ret = crypto_रेजिस्टर_alg(&algs[i]);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	क्रम (--i; i >= 0; --i)
		crypto_unरेजिस्टर_alg(&algs[i]);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_algs);

व्योम crypto_unरेजिस्टर_algs(काष्ठा crypto_alg *algs, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		crypto_unरेजिस्टर_alg(&algs[i]);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_algs);

पूर्णांक crypto_रेजिस्टर_ढाँचा(काष्ठा crypto_ढाँचा *पंचांगpl)
अणु
	काष्ठा crypto_ढाँचा *q;
	पूर्णांक err = -EEXIST;

	करोwn_ग_लिखो(&crypto_alg_sem);

	crypto_check_module_sig(पंचांगpl->module);

	list_क्रम_each_entry(q, &crypto_ढाँचा_list, list) अणु
		अगर (q == पंचांगpl)
			जाओ out;
	पूर्ण

	list_add(&पंचांगpl->list, &crypto_ढाँचा_list);
	err = 0;
out:
	up_ग_लिखो(&crypto_alg_sem);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_ढाँचा);

पूर्णांक crypto_रेजिस्टर_ढाँचाs(काष्ठा crypto_ढाँचा *पंचांगpls, पूर्णांक count)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < count; i++) अणु
		err = crypto_रेजिस्टर_ढाँचा(&पंचांगpls[i]);
		अगर (err)
			जाओ out;
	पूर्ण
	वापस 0;

out:
	क्रम (--i; i >= 0; --i)
		crypto_unरेजिस्टर_ढाँचा(&पंचांगpls[i]);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_ढाँचाs);

व्योम crypto_unरेजिस्टर_ढाँचा(काष्ठा crypto_ढाँचा *पंचांगpl)
अणु
	काष्ठा crypto_instance *inst;
	काष्ठा hlist_node *n;
	काष्ठा hlist_head *list;
	LIST_HEAD(users);

	करोwn_ग_लिखो(&crypto_alg_sem);

	BUG_ON(list_empty(&पंचांगpl->list));
	list_del_init(&पंचांगpl->list);

	list = &पंचांगpl->instances;
	hlist_क्रम_each_entry(inst, list, list) अणु
		पूर्णांक err = crypto_हटाओ_alg(&inst->alg, &users);

		BUG_ON(err);
	पूर्ण

	up_ग_लिखो(&crypto_alg_sem);

	hlist_क्रम_each_entry_safe(inst, n, list, list) अणु
		BUG_ON(refcount_पढ़ो(&inst->alg.cra_refcnt) != 1);
		crypto_मुक्त_instance(inst);
	पूर्ण
	crypto_हटाओ_final(&users);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_ढाँचा);

व्योम crypto_unरेजिस्टर_ढाँचाs(काष्ठा crypto_ढाँचा *पंचांगpls, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = count - 1; i >= 0; --i)
		crypto_unरेजिस्टर_ढाँचा(&पंचांगpls[i]);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_ढाँचाs);

अटल काष्ठा crypto_ढाँचा *__crypto_lookup_ढाँचा(स्थिर अक्षर *name)
अणु
	काष्ठा crypto_ढाँचा *q, *पंचांगpl = शून्य;

	करोwn_पढ़ो(&crypto_alg_sem);
	list_क्रम_each_entry(q, &crypto_ढाँचा_list, list) अणु
		अगर (म_भेद(q->name, name))
			जारी;
		अगर (unlikely(!crypto_पंचांगpl_get(q)))
			जारी;

		पंचांगpl = q;
		अवरोध;
	पूर्ण
	up_पढ़ो(&crypto_alg_sem);

	वापस पंचांगpl;
पूर्ण

काष्ठा crypto_ढाँचा *crypto_lookup_ढाँचा(स्थिर अक्षर *name)
अणु
	वापस try_then_request_module(__crypto_lookup_ढाँचा(name),
				       "crypto-%s", name);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_lookup_ढाँचा);

पूर्णांक crypto_रेजिस्टर_instance(काष्ठा crypto_ढाँचा *पंचांगpl,
			     काष्ठा crypto_instance *inst)
अणु
	काष्ठा crypto_larval *larval;
	काष्ठा crypto_spawn *spawn;
	पूर्णांक err;

	err = crypto_check_alg(&inst->alg);
	अगर (err)
		वापस err;

	inst->alg.cra_module = पंचांगpl->module;
	inst->alg.cra_flags |= CRYPTO_ALG_INSTANCE;

	करोwn_ग_लिखो(&crypto_alg_sem);

	larval = ERR_PTR(-EAGAIN);
	क्रम (spawn = inst->spawns; spawn;) अणु
		काष्ठा crypto_spawn *next;

		अगर (spawn->dead)
			जाओ unlock;

		next = spawn->next;
		spawn->inst = inst;
		spawn->रेजिस्टरed = true;

		crypto_mod_put(spawn->alg);

		spawn = next;
	पूर्ण

	larval = __crypto_रेजिस्टर_alg(&inst->alg);
	अगर (IS_ERR(larval))
		जाओ unlock;

	hlist_add_head(&inst->list, &पंचांगpl->instances);
	inst->पंचांगpl = पंचांगpl;

unlock:
	up_ग_लिखो(&crypto_alg_sem);

	err = PTR_ERR(larval);
	अगर (IS_ERR(larval))
		जाओ err;

	crypto_रुको_क्रम_test(larval);
	err = 0;

err:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_instance);

व्योम crypto_unरेजिस्टर_instance(काष्ठा crypto_instance *inst)
अणु
	LIST_HEAD(list);

	करोwn_ग_लिखो(&crypto_alg_sem);

	crypto_हटाओ_spawns(&inst->alg, &list, शून्य);
	crypto_हटाओ_instance(inst, &list);

	up_ग_लिखो(&crypto_alg_sem);

	crypto_हटाओ_final(&list);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_instance);

पूर्णांक crypto_grab_spawn(काष्ठा crypto_spawn *spawn, काष्ठा crypto_instance *inst,
		      स्थिर अक्षर *name, u32 type, u32 mask)
अणु
	काष्ठा crypto_alg *alg;
	पूर्णांक err = -EAGAIN;

	अगर (WARN_ON_ONCE(inst == शून्य))
		वापस -EINVAL;

	/* Allow the result of crypto_attr_alg_name() to be passed directly */
	अगर (IS_ERR(name))
		वापस PTR_ERR(name);

	alg = crypto_find_alg(name, spawn->frontend, type, mask);
	अगर (IS_ERR(alg))
		वापस PTR_ERR(alg);

	करोwn_ग_लिखो(&crypto_alg_sem);
	अगर (!crypto_is_moribund(alg)) अणु
		list_add(&spawn->list, &alg->cra_users);
		spawn->alg = alg;
		spawn->mask = mask;
		spawn->next = inst->spawns;
		inst->spawns = spawn;
		inst->alg.cra_flags |=
			(alg->cra_flags & CRYPTO_ALG_INHERITED_FLAGS);
		err = 0;
	पूर्ण
	up_ग_लिखो(&crypto_alg_sem);
	अगर (err)
		crypto_mod_put(alg);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_grab_spawn);

व्योम crypto_drop_spawn(काष्ठा crypto_spawn *spawn)
अणु
	अगर (!spawn->alg) /* not yet initialized? */
		वापस;

	करोwn_ग_लिखो(&crypto_alg_sem);
	अगर (!spawn->dead)
		list_del(&spawn->list);
	up_ग_लिखो(&crypto_alg_sem);

	अगर (!spawn->रेजिस्टरed)
		crypto_mod_put(spawn->alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_drop_spawn);

अटल काष्ठा crypto_alg *crypto_spawn_alg(काष्ठा crypto_spawn *spawn)
अणु
	काष्ठा crypto_alg *alg = ERR_PTR(-EAGAIN);
	काष्ठा crypto_alg *target;
	bool shoot = false;

	करोwn_पढ़ो(&crypto_alg_sem);
	अगर (!spawn->dead) अणु
		alg = spawn->alg;
		अगर (!crypto_mod_get(alg)) अणु
			target = crypto_alg_get(alg);
			shoot = true;
			alg = ERR_PTR(-EAGAIN);
		पूर्ण
	पूर्ण
	up_पढ़ो(&crypto_alg_sem);

	अगर (shoot) अणु
		crypto_shoot_alg(target);
		crypto_alg_put(target);
	पूर्ण

	वापस alg;
पूर्ण

काष्ठा crypto_tfm *crypto_spawn_tfm(काष्ठा crypto_spawn *spawn, u32 type,
				    u32 mask)
अणु
	काष्ठा crypto_alg *alg;
	काष्ठा crypto_tfm *tfm;

	alg = crypto_spawn_alg(spawn);
	अगर (IS_ERR(alg))
		वापस ERR_CAST(alg);

	tfm = ERR_PTR(-EINVAL);
	अगर (unlikely((alg->cra_flags ^ type) & mask))
		जाओ out_put_alg;

	tfm = __crypto_alloc_tfm(alg, type, mask);
	अगर (IS_ERR(tfm))
		जाओ out_put_alg;

	वापस tfm;

out_put_alg:
	crypto_mod_put(alg);
	वापस tfm;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_spawn_tfm);

व्योम *crypto_spawn_tfm2(काष्ठा crypto_spawn *spawn)
अणु
	काष्ठा crypto_alg *alg;
	काष्ठा crypto_tfm *tfm;

	alg = crypto_spawn_alg(spawn);
	अगर (IS_ERR(alg))
		वापस ERR_CAST(alg);

	tfm = crypto_create_tfm(alg, spawn->frontend);
	अगर (IS_ERR(tfm))
		जाओ out_put_alg;

	वापस tfm;

out_put_alg:
	crypto_mod_put(alg);
	वापस tfm;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_spawn_tfm2);

पूर्णांक crypto_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&crypto_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_notअगरier);

पूर्णांक crypto_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&crypto_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_notअगरier);

काष्ठा crypto_attr_type *crypto_get_attr_type(काष्ठा rtattr **tb)
अणु
	काष्ठा rtattr *rta = tb[0];
	काष्ठा crypto_attr_type *algt;

	अगर (!rta)
		वापस ERR_PTR(-ENOENT);
	अगर (RTA_PAYLOAD(rta) < माप(*algt))
		वापस ERR_PTR(-EINVAL);
	अगर (rta->rta_type != CRYPTOA_TYPE)
		वापस ERR_PTR(-EINVAL);

	algt = RTA_DATA(rta);

	वापस algt;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_get_attr_type);

/**
 * crypto_check_attr_type() - check algorithm type and compute inherited mask
 * @tb: the ढाँचा parameters
 * @type: the algorithm type the ढाँचा would be instantiated as
 * @mask_ret: (output) the mask that should be passed to crypto_grab_*()
 *	      to restrict the flags of any inner algorithms
 *
 * Validate that the algorithm type the user requested is compatible with the
 * one the ढाँचा would actually be instantiated as.  E.g., अगर the user is
 * करोing crypto_alloc_shash("cbc(aes)", ...), this would वापस an error because
 * the "cbc" ढाँचा creates an "skcipher" algorithm, not an "shash" algorithm.
 *
 * Also compute the mask to use to restrict the flags of any inner algorithms.
 *
 * Return: 0 on success; -त्रुटि_सं on failure
 */
पूर्णांक crypto_check_attr_type(काष्ठा rtattr **tb, u32 type, u32 *mask_ret)
अणु
	काष्ठा crypto_attr_type *algt;

	algt = crypto_get_attr_type(tb);
	अगर (IS_ERR(algt))
		वापस PTR_ERR(algt);

	अगर ((algt->type ^ type) & algt->mask)
		वापस -EINVAL;

	*mask_ret = crypto_algt_inherited_mask(algt);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_check_attr_type);

स्थिर अक्षर *crypto_attr_alg_name(काष्ठा rtattr *rta)
अणु
	काष्ठा crypto_attr_alg *alga;

	अगर (!rta)
		वापस ERR_PTR(-ENOENT);
	अगर (RTA_PAYLOAD(rta) < माप(*alga))
		वापस ERR_PTR(-EINVAL);
	अगर (rta->rta_type != CRYPTOA_ALG)
		वापस ERR_PTR(-EINVAL);

	alga = RTA_DATA(rta);
	alga->name[CRYPTO_MAX_ALG_NAME - 1] = 0;

	वापस alga->name;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_attr_alg_name);

पूर्णांक crypto_attr_u32(काष्ठा rtattr *rta, u32 *num)
अणु
	काष्ठा crypto_attr_u32 *nu32;

	अगर (!rta)
		वापस -ENOENT;
	अगर (RTA_PAYLOAD(rta) < माप(*nu32))
		वापस -EINVAL;
	अगर (rta->rta_type != CRYPTOA_U32)
		वापस -EINVAL;

	nu32 = RTA_DATA(rta);
	*num = nu32->num;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_attr_u32);

पूर्णांक crypto_inst_setname(काष्ठा crypto_instance *inst, स्थिर अक्षर *name,
			काष्ठा crypto_alg *alg)
अणु
	अगर (snम_लिखो(inst->alg.cra_name, CRYPTO_MAX_ALG_NAME, "%s(%s)", name,
		     alg->cra_name) >= CRYPTO_MAX_ALG_NAME)
		वापस -ENAMETOOLONG;

	अगर (snम_लिखो(inst->alg.cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s(%s)",
		     name, alg->cra_driver_name) >= CRYPTO_MAX_ALG_NAME)
		वापस -ENAMETOOLONG;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_inst_setname);

व्योम crypto_init_queue(काष्ठा crypto_queue *queue, अचिन्हित पूर्णांक max_qlen)
अणु
	INIT_LIST_HEAD(&queue->list);
	queue->backlog = &queue->list;
	queue->qlen = 0;
	queue->max_qlen = max_qlen;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_init_queue);

पूर्णांक crypto_enqueue_request(काष्ठा crypto_queue *queue,
			   काष्ठा crypto_async_request *request)
अणु
	पूर्णांक err = -EINPROGRESS;

	अगर (unlikely(queue->qlen >= queue->max_qlen)) अणु
		अगर (!(request->flags & CRYPTO_TFM_REQ_MAY_BACKLOG)) अणु
			err = -ENOSPC;
			जाओ out;
		पूर्ण
		err = -EBUSY;
		अगर (queue->backlog == &queue->list)
			queue->backlog = &request->list;
	पूर्ण

	queue->qlen++;
	list_add_tail(&request->list, &queue->list);

out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_enqueue_request);

व्योम crypto_enqueue_request_head(काष्ठा crypto_queue *queue,
				 काष्ठा crypto_async_request *request)
अणु
	queue->qlen++;
	list_add(&request->list, &queue->list);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_enqueue_request_head);

काष्ठा crypto_async_request *crypto_dequeue_request(काष्ठा crypto_queue *queue)
अणु
	काष्ठा list_head *request;

	अगर (unlikely(!queue->qlen))
		वापस शून्य;

	queue->qlen--;

	अगर (queue->backlog != &queue->list)
		queue->backlog = queue->backlog->next;

	request = queue->list.next;
	list_del(request);

	वापस list_entry(request, काष्ठा crypto_async_request, list);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_dequeue_request);

अटल अंतरभूत व्योम crypto_inc_byte(u8 *a, अचिन्हित पूर्णांक size)
अणु
	u8 *b = (a + size);
	u8 c;

	क्रम (; size; size--) अणु
		c = *--b + 1;
		*b = c;
		अगर (c)
			अवरोध;
	पूर्ण
पूर्ण

व्योम crypto_inc(u8 *a, अचिन्हित पूर्णांक size)
अणु
	__be32 *b = (__be32 *)(a + size);
	u32 c;

	अगर (IS_ENABLED(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) ||
	    IS_ALIGNED((अचिन्हित दीर्घ)b, __alignof__(*b)))
		क्रम (; size >= 4; size -= 4) अणु
			c = be32_to_cpu(*--b) + 1;
			*b = cpu_to_be32(c);
			अगर (likely(c))
				वापस;
		पूर्ण

	crypto_inc_byte(a, size);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_inc);

व्योम __crypto_xor(u8 *dst, स्थिर u8 *src1, स्थिर u8 *src2, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक relalign = 0;

	अगर (!IS_ENABLED(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)) अणु
		पूर्णांक size = माप(अचिन्हित दीर्घ);
		पूर्णांक d = (((अचिन्हित दीर्घ)dst ^ (अचिन्हित दीर्घ)src1) |
			 ((अचिन्हित दीर्घ)dst ^ (अचिन्हित दीर्घ)src2)) &
			(size - 1);

		relalign = d ? 1 << __ffs(d) : size;

		/*
		 * If we care about alignment, process as many bytes as
		 * needed to advance dst and src to values whose alignments
		 * equal their relative alignment. This will allow us to
		 * process the reमुख्यder of the input using optimal strides.
		 */
		जबतक (((अचिन्हित दीर्घ)dst & (relalign - 1)) && len > 0) अणु
			*dst++ = *src1++ ^ *src2++;
			len--;
		पूर्ण
	पूर्ण

	जबतक (IS_ENABLED(CONFIG_64BIT) && len >= 8 && !(relalign & 7)) अणु
		*(u64 *)dst = *(u64 *)src1 ^  *(u64 *)src2;
		dst += 8;
		src1 += 8;
		src2 += 8;
		len -= 8;
	पूर्ण

	जबतक (len >= 4 && !(relalign & 3)) अणु
		*(u32 *)dst = *(u32 *)src1 ^ *(u32 *)src2;
		dst += 4;
		src1 += 4;
		src2 += 4;
		len -= 4;
	पूर्ण

	जबतक (len >= 2 && !(relalign & 1)) अणु
		*(u16 *)dst = *(u16 *)src1 ^ *(u16 *)src2;
		dst += 2;
		src1 += 2;
		src2 += 2;
		len -= 2;
	पूर्ण

	जबतक (len--)
		*dst++ = *src1++ ^ *src2++;
पूर्ण
EXPORT_SYMBOL_GPL(__crypto_xor);

अचिन्हित पूर्णांक crypto_alg_extsize(काष्ठा crypto_alg *alg)
अणु
	वापस alg->cra_ctxsize +
	       (alg->cra_alignmask & ~(crypto_tfm_ctx_alignment() - 1));
पूर्ण
EXPORT_SYMBOL_GPL(crypto_alg_extsize);

पूर्णांक crypto_type_has_alg(स्थिर अक्षर *name, स्थिर काष्ठा crypto_type *frontend,
			u32 type, u32 mask)
अणु
	पूर्णांक ret = 0;
	काष्ठा crypto_alg *alg = crypto_find_alg(name, frontend, type, mask);

	अगर (!IS_ERR(alg)) अणु
		crypto_mod_put(alg);
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_type_has_alg);

#अगर_घोषित CONFIG_CRYPTO_STATS
व्योम crypto_stats_init(काष्ठा crypto_alg *alg)
अणु
	स_रखो(&alg->stats, 0, माप(alg->stats));
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_init);

व्योम crypto_stats_get(काष्ठा crypto_alg *alg)
अणु
	crypto_alg_get(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_get);

व्योम crypto_stats_aead_encrypt(अचिन्हित पूर्णांक cryptlen, काष्ठा crypto_alg *alg,
			       पूर्णांक ret)
अणु
	अगर (ret && ret != -EINPROGRESS && ret != -EBUSY) अणु
		atomic64_inc(&alg->stats.aead.err_cnt);
	पूर्ण अन्यथा अणु
		atomic64_inc(&alg->stats.aead.encrypt_cnt);
		atomic64_add(cryptlen, &alg->stats.aead.encrypt_tlen);
	पूर्ण
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_aead_encrypt);

व्योम crypto_stats_aead_decrypt(अचिन्हित पूर्णांक cryptlen, काष्ठा crypto_alg *alg,
			       पूर्णांक ret)
अणु
	अगर (ret && ret != -EINPROGRESS && ret != -EBUSY) अणु
		atomic64_inc(&alg->stats.aead.err_cnt);
	पूर्ण अन्यथा अणु
		atomic64_inc(&alg->stats.aead.decrypt_cnt);
		atomic64_add(cryptlen, &alg->stats.aead.decrypt_tlen);
	पूर्ण
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_aead_decrypt);

व्योम crypto_stats_akcipher_encrypt(अचिन्हित पूर्णांक src_len, पूर्णांक ret,
				   काष्ठा crypto_alg *alg)
अणु
	अगर (ret && ret != -EINPROGRESS && ret != -EBUSY) अणु
		atomic64_inc(&alg->stats.akcipher.err_cnt);
	पूर्ण अन्यथा अणु
		atomic64_inc(&alg->stats.akcipher.encrypt_cnt);
		atomic64_add(src_len, &alg->stats.akcipher.encrypt_tlen);
	पूर्ण
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_akcipher_encrypt);

व्योम crypto_stats_akcipher_decrypt(अचिन्हित पूर्णांक src_len, पूर्णांक ret,
				   काष्ठा crypto_alg *alg)
अणु
	अगर (ret && ret != -EINPROGRESS && ret != -EBUSY) अणु
		atomic64_inc(&alg->stats.akcipher.err_cnt);
	पूर्ण अन्यथा अणु
		atomic64_inc(&alg->stats.akcipher.decrypt_cnt);
		atomic64_add(src_len, &alg->stats.akcipher.decrypt_tlen);
	पूर्ण
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_akcipher_decrypt);

व्योम crypto_stats_akcipher_sign(पूर्णांक ret, काष्ठा crypto_alg *alg)
अणु
	अगर (ret && ret != -EINPROGRESS && ret != -EBUSY)
		atomic64_inc(&alg->stats.akcipher.err_cnt);
	अन्यथा
		atomic64_inc(&alg->stats.akcipher.sign_cnt);
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_akcipher_sign);

व्योम crypto_stats_akcipher_verअगरy(पूर्णांक ret, काष्ठा crypto_alg *alg)
अणु
	अगर (ret && ret != -EINPROGRESS && ret != -EBUSY)
		atomic64_inc(&alg->stats.akcipher.err_cnt);
	अन्यथा
		atomic64_inc(&alg->stats.akcipher.verअगरy_cnt);
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_akcipher_verअगरy);

व्योम crypto_stats_compress(अचिन्हित पूर्णांक slen, पूर्णांक ret, काष्ठा crypto_alg *alg)
अणु
	अगर (ret && ret != -EINPROGRESS && ret != -EBUSY) अणु
		atomic64_inc(&alg->stats.compress.err_cnt);
	पूर्ण अन्यथा अणु
		atomic64_inc(&alg->stats.compress.compress_cnt);
		atomic64_add(slen, &alg->stats.compress.compress_tlen);
	पूर्ण
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_compress);

व्योम crypto_stats_decompress(अचिन्हित पूर्णांक slen, पूर्णांक ret, काष्ठा crypto_alg *alg)
अणु
	अगर (ret && ret != -EINPROGRESS && ret != -EBUSY) अणु
		atomic64_inc(&alg->stats.compress.err_cnt);
	पूर्ण अन्यथा अणु
		atomic64_inc(&alg->stats.compress.decompress_cnt);
		atomic64_add(slen, &alg->stats.compress.decompress_tlen);
	पूर्ण
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_decompress);

व्योम crypto_stats_ahash_update(अचिन्हित पूर्णांक nbytes, पूर्णांक ret,
			       काष्ठा crypto_alg *alg)
अणु
	अगर (ret && ret != -EINPROGRESS && ret != -EBUSY)
		atomic64_inc(&alg->stats.hash.err_cnt);
	अन्यथा
		atomic64_add(nbytes, &alg->stats.hash.hash_tlen);
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_ahash_update);

व्योम crypto_stats_ahash_final(अचिन्हित पूर्णांक nbytes, पूर्णांक ret,
			      काष्ठा crypto_alg *alg)
अणु
	अगर (ret && ret != -EINPROGRESS && ret != -EBUSY) अणु
		atomic64_inc(&alg->stats.hash.err_cnt);
	पूर्ण अन्यथा अणु
		atomic64_inc(&alg->stats.hash.hash_cnt);
		atomic64_add(nbytes, &alg->stats.hash.hash_tlen);
	पूर्ण
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_ahash_final);

व्योम crypto_stats_kpp_set_secret(काष्ठा crypto_alg *alg, पूर्णांक ret)
अणु
	अगर (ret)
		atomic64_inc(&alg->stats.kpp.err_cnt);
	अन्यथा
		atomic64_inc(&alg->stats.kpp.setsecret_cnt);
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_kpp_set_secret);

व्योम crypto_stats_kpp_generate_खुला_key(काष्ठा crypto_alg *alg, पूर्णांक ret)
अणु
	अगर (ret)
		atomic64_inc(&alg->stats.kpp.err_cnt);
	अन्यथा
		atomic64_inc(&alg->stats.kpp.generate_खुला_key_cnt);
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_kpp_generate_खुला_key);

व्योम crypto_stats_kpp_compute_shared_secret(काष्ठा crypto_alg *alg, पूर्णांक ret)
अणु
	अगर (ret)
		atomic64_inc(&alg->stats.kpp.err_cnt);
	अन्यथा
		atomic64_inc(&alg->stats.kpp.compute_shared_secret_cnt);
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_kpp_compute_shared_secret);

व्योम crypto_stats_rng_seed(काष्ठा crypto_alg *alg, पूर्णांक ret)
अणु
	अगर (ret && ret != -EINPROGRESS && ret != -EBUSY)
		atomic64_inc(&alg->stats.rng.err_cnt);
	अन्यथा
		atomic64_inc(&alg->stats.rng.seed_cnt);
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_rng_seed);

व्योम crypto_stats_rng_generate(काष्ठा crypto_alg *alg, अचिन्हित पूर्णांक dlen,
			       पूर्णांक ret)
अणु
	अगर (ret && ret != -EINPROGRESS && ret != -EBUSY) अणु
		atomic64_inc(&alg->stats.rng.err_cnt);
	पूर्ण अन्यथा अणु
		atomic64_inc(&alg->stats.rng.generate_cnt);
		atomic64_add(dlen, &alg->stats.rng.generate_tlen);
	पूर्ण
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_rng_generate);

व्योम crypto_stats_skcipher_encrypt(अचिन्हित पूर्णांक cryptlen, पूर्णांक ret,
				   काष्ठा crypto_alg *alg)
अणु
	अगर (ret && ret != -EINPROGRESS && ret != -EBUSY) अणु
		atomic64_inc(&alg->stats.cipher.err_cnt);
	पूर्ण अन्यथा अणु
		atomic64_inc(&alg->stats.cipher.encrypt_cnt);
		atomic64_add(cryptlen, &alg->stats.cipher.encrypt_tlen);
	पूर्ण
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_skcipher_encrypt);

व्योम crypto_stats_skcipher_decrypt(अचिन्हित पूर्णांक cryptlen, पूर्णांक ret,
				   काष्ठा crypto_alg *alg)
अणु
	अगर (ret && ret != -EINPROGRESS && ret != -EBUSY) अणु
		atomic64_inc(&alg->stats.cipher.err_cnt);
	पूर्ण अन्यथा अणु
		atomic64_inc(&alg->stats.cipher.decrypt_cnt);
		atomic64_add(cryptlen, &alg->stats.cipher.decrypt_tlen);
	पूर्ण
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_stats_skcipher_decrypt);
#पूर्ण_अगर

अटल पूर्णांक __init crypto_algapi_init(व्योम)
अणु
	crypto_init_proc();
	वापस 0;
पूर्ण

अटल व्योम __निकास crypto_algapi_निकास(व्योम)
अणु
	crypto_निकास_proc();
पूर्ण

module_init(crypto_algapi_init);
module_निकास(crypto_algapi_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Cryptographic algorithms API");
