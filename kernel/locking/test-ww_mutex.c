<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Module-based API test facility क्रम ww_mutexes
 */

#समावेश <linux/kernel.h>

#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/ww_mutex.h>

अटल DEFINE_WD_CLASS(ww_class);
काष्ठा workqueue_काष्ठा *wq;

काष्ठा test_mutex अणु
	काष्ठा work_काष्ठा work;
	काष्ठा ww_mutex mutex;
	काष्ठा completion पढ़ोy, go, करोne;
	अचिन्हित पूर्णांक flags;
पूर्ण;

#घोषणा TEST_MTX_SPIN BIT(0)
#घोषणा TEST_MTX_TRY BIT(1)
#घोषणा TEST_MTX_CTX BIT(2)
#घोषणा __TEST_MTX_LAST BIT(3)

अटल व्योम test_mutex_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा test_mutex *mtx = container_of(work, typeof(*mtx), work);

	complete(&mtx->पढ़ोy);
	रुको_क्रम_completion(&mtx->go);

	अगर (mtx->flags & TEST_MTX_TRY) अणु
		जबतक (!ww_mutex_trylock(&mtx->mutex))
			cond_resched();
	पूर्ण अन्यथा अणु
		ww_mutex_lock(&mtx->mutex, शून्य);
	पूर्ण
	complete(&mtx->करोne);
	ww_mutex_unlock(&mtx->mutex);
पूर्ण

अटल पूर्णांक __test_mutex(अचिन्हित पूर्णांक flags)
अणु
#घोषणा TIMEOUT (HZ / 16)
	काष्ठा test_mutex mtx;
	काष्ठा ww_acquire_ctx ctx;
	पूर्णांक ret;

	ww_mutex_init(&mtx.mutex, &ww_class);
	ww_acquire_init(&ctx, &ww_class);

	INIT_WORK_ONSTACK(&mtx.work, test_mutex_work);
	init_completion(&mtx.पढ़ोy);
	init_completion(&mtx.go);
	init_completion(&mtx.करोne);
	mtx.flags = flags;

	schedule_work(&mtx.work);

	रुको_क्रम_completion(&mtx.पढ़ोy);
	ww_mutex_lock(&mtx.mutex, (flags & TEST_MTX_CTX) ? &ctx : शून्य);
	complete(&mtx.go);
	अगर (flags & TEST_MTX_SPIN) अणु
		अचिन्हित दीर्घ समयout = jअगरfies + TIMEOUT;

		ret = 0;
		करो अणु
			अगर (completion_करोne(&mtx.करोne)) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			cond_resched();
		पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));
	पूर्ण अन्यथा अणु
		ret = रुको_क्रम_completion_समयout(&mtx.करोne, TIMEOUT);
	पूर्ण
	ww_mutex_unlock(&mtx.mutex);
	ww_acquire_fini(&ctx);

	अगर (ret) अणु
		pr_err("%s(flags=%x): mutual exclusion failure\n",
		       __func__, flags);
		ret = -EINVAL;
	पूर्ण

	flush_work(&mtx.work);
	destroy_work_on_stack(&mtx.work);
	वापस ret;
#अघोषित TIMEOUT
पूर्ण

अटल पूर्णांक test_mutex(व्योम)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < __TEST_MTX_LAST; i++) अणु
		ret = __test_mutex(i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक test_aa(व्योम)
अणु
	काष्ठा ww_mutex mutex;
	काष्ठा ww_acquire_ctx ctx;
	पूर्णांक ret;

	ww_mutex_init(&mutex, &ww_class);
	ww_acquire_init(&ctx, &ww_class);

	ww_mutex_lock(&mutex, &ctx);

	अगर (ww_mutex_trylock(&mutex))  अणु
		pr_err("%s: trylocked itself!\n", __func__);
		ww_mutex_unlock(&mutex);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = ww_mutex_lock(&mutex, &ctx);
	अगर (ret != -EALREADY) अणु
		pr_err("%s: missed deadlock for recursing, ret=%d\n",
		       __func__, ret);
		अगर (!ret)
			ww_mutex_unlock(&mutex);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = 0;
out:
	ww_mutex_unlock(&mutex);
	ww_acquire_fini(&ctx);
	वापस ret;
पूर्ण

काष्ठा test_abba अणु
	काष्ठा work_काष्ठा work;
	काष्ठा ww_mutex a_mutex;
	काष्ठा ww_mutex b_mutex;
	काष्ठा completion a_पढ़ोy;
	काष्ठा completion b_पढ़ोy;
	bool resolve;
	पूर्णांक result;
पूर्ण;

अटल व्योम test_abba_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा test_abba *abba = container_of(work, typeof(*abba), work);
	काष्ठा ww_acquire_ctx ctx;
	पूर्णांक err;

	ww_acquire_init(&ctx, &ww_class);
	ww_mutex_lock(&abba->b_mutex, &ctx);

	complete(&abba->b_पढ़ोy);
	रुको_क्रम_completion(&abba->a_पढ़ोy);

	err = ww_mutex_lock(&abba->a_mutex, &ctx);
	अगर (abba->resolve && err == -EDEADLK) अणु
		ww_mutex_unlock(&abba->b_mutex);
		ww_mutex_lock_slow(&abba->a_mutex, &ctx);
		err = ww_mutex_lock(&abba->b_mutex, &ctx);
	पूर्ण

	अगर (!err)
		ww_mutex_unlock(&abba->a_mutex);
	ww_mutex_unlock(&abba->b_mutex);
	ww_acquire_fini(&ctx);

	abba->result = err;
पूर्ण

अटल पूर्णांक test_abba(bool resolve)
अणु
	काष्ठा test_abba abba;
	काष्ठा ww_acquire_ctx ctx;
	पूर्णांक err, ret;

	ww_mutex_init(&abba.a_mutex, &ww_class);
	ww_mutex_init(&abba.b_mutex, &ww_class);
	INIT_WORK_ONSTACK(&abba.work, test_abba_work);
	init_completion(&abba.a_पढ़ोy);
	init_completion(&abba.b_पढ़ोy);
	abba.resolve = resolve;

	schedule_work(&abba.work);

	ww_acquire_init(&ctx, &ww_class);
	ww_mutex_lock(&abba.a_mutex, &ctx);

	complete(&abba.a_पढ़ोy);
	रुको_क्रम_completion(&abba.b_पढ़ोy);

	err = ww_mutex_lock(&abba.b_mutex, &ctx);
	अगर (resolve && err == -EDEADLK) अणु
		ww_mutex_unlock(&abba.a_mutex);
		ww_mutex_lock_slow(&abba.b_mutex, &ctx);
		err = ww_mutex_lock(&abba.a_mutex, &ctx);
	पूर्ण

	अगर (!err)
		ww_mutex_unlock(&abba.b_mutex);
	ww_mutex_unlock(&abba.a_mutex);
	ww_acquire_fini(&ctx);

	flush_work(&abba.work);
	destroy_work_on_stack(&abba.work);

	ret = 0;
	अगर (resolve) अणु
		अगर (err || abba.result) अणु
			pr_err("%s: failed to resolve ABBA deadlock, A err=%d, B err=%d\n",
			       __func__, err, abba.result);
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (err != -EDEADLK && abba.result != -EDEADLK) अणु
			pr_err("%s: missed ABBA deadlock, A err=%d, B err=%d\n",
			       __func__, err, abba.result);
			ret = -EINVAL;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

काष्ठा test_cycle अणु
	काष्ठा work_काष्ठा work;
	काष्ठा ww_mutex a_mutex;
	काष्ठा ww_mutex *b_mutex;
	काष्ठा completion *a_संकेत;
	काष्ठा completion b_संकेत;
	पूर्णांक result;
पूर्ण;

अटल व्योम test_cycle_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा test_cycle *cycle = container_of(work, typeof(*cycle), work);
	काष्ठा ww_acquire_ctx ctx;
	पूर्णांक err, erra = 0;

	ww_acquire_init(&ctx, &ww_class);
	ww_mutex_lock(&cycle->a_mutex, &ctx);

	complete(cycle->a_संकेत);
	रुको_क्रम_completion(&cycle->b_संकेत);

	err = ww_mutex_lock(cycle->b_mutex, &ctx);
	अगर (err == -EDEADLK) अणु
		err = 0;
		ww_mutex_unlock(&cycle->a_mutex);
		ww_mutex_lock_slow(cycle->b_mutex, &ctx);
		erra = ww_mutex_lock(&cycle->a_mutex, &ctx);
	पूर्ण

	अगर (!err)
		ww_mutex_unlock(cycle->b_mutex);
	अगर (!erra)
		ww_mutex_unlock(&cycle->a_mutex);
	ww_acquire_fini(&ctx);

	cycle->result = err ?: erra;
पूर्ण

अटल पूर्णांक __test_cycle(अचिन्हित पूर्णांक nthपढ़ोs)
अणु
	काष्ठा test_cycle *cycles;
	अचिन्हित पूर्णांक n, last = nthपढ़ोs - 1;
	पूर्णांक ret;

	cycles = kदो_स्मृति_array(nthपढ़ोs, माप(*cycles), GFP_KERNEL);
	अगर (!cycles)
		वापस -ENOMEM;

	क्रम (n = 0; n < nthपढ़ोs; n++) अणु
		काष्ठा test_cycle *cycle = &cycles[n];

		ww_mutex_init(&cycle->a_mutex, &ww_class);
		अगर (n == last)
			cycle->b_mutex = &cycles[0].a_mutex;
		अन्यथा
			cycle->b_mutex = &cycles[n + 1].a_mutex;

		अगर (n == 0)
			cycle->a_संकेत = &cycles[last].b_संकेत;
		अन्यथा
			cycle->a_संकेत = &cycles[n - 1].b_संकेत;
		init_completion(&cycle->b_संकेत);

		INIT_WORK(&cycle->work, test_cycle_work);
		cycle->result = 0;
	पूर्ण

	क्रम (n = 0; n < nthपढ़ोs; n++)
		queue_work(wq, &cycles[n].work);

	flush_workqueue(wq);

	ret = 0;
	क्रम (n = 0; n < nthपढ़ोs; n++) अणु
		काष्ठा test_cycle *cycle = &cycles[n];

		अगर (!cycle->result)
			जारी;

		pr_err("cyclic deadlock not resolved, ret[%d/%d] = %d\n",
		       n, nthपढ़ोs, cycle->result);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	क्रम (n = 0; n < nthपढ़ोs; n++)
		ww_mutex_destroy(&cycles[n].a_mutex);
	kमुक्त(cycles);
	वापस ret;
पूर्ण

अटल पूर्णांक test_cycle(अचिन्हित पूर्णांक ncpus)
अणु
	अचिन्हित पूर्णांक n;
	पूर्णांक ret;

	क्रम (n = 2; n <= ncpus + 1; n++) अणु
		ret = __test_cycle(n);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा stress अणु
	काष्ठा work_काष्ठा work;
	काष्ठा ww_mutex *locks;
	अचिन्हित दीर्घ समयout;
	पूर्णांक nlocks;
पूर्ण;

अटल पूर्णांक *get_अक्रमom_order(पूर्णांक count)
अणु
	पूर्णांक *order;
	पूर्णांक n, r, पंचांगp;

	order = kदो_स्मृति_array(count, माप(*order), GFP_KERNEL);
	अगर (!order)
		वापस order;

	क्रम (n = 0; n < count; n++)
		order[n] = n;

	क्रम (n = count - 1; n > 1; n--) अणु
		r = get_अक्रमom_पूर्णांक() % (n + 1);
		अगर (r != n) अणु
			पंचांगp = order[n];
			order[n] = order[r];
			order[r] = पंचांगp;
		पूर्ण
	पूर्ण

	वापस order;
पूर्ण

अटल व्योम dummy_load(काष्ठा stress *stress)
अणु
	usleep_range(1000, 2000);
पूर्ण

अटल व्योम stress_inorder_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा stress *stress = container_of(work, typeof(*stress), work);
	स्थिर पूर्णांक nlocks = stress->nlocks;
	काष्ठा ww_mutex *locks = stress->locks;
	काष्ठा ww_acquire_ctx ctx;
	पूर्णांक *order;

	order = get_अक्रमom_order(nlocks);
	अगर (!order)
		वापस;

	करो अणु
		पूर्णांक contended = -1;
		पूर्णांक n, err;

		ww_acquire_init(&ctx, &ww_class);
retry:
		err = 0;
		क्रम (n = 0; n < nlocks; n++) अणु
			अगर (n == contended)
				जारी;

			err = ww_mutex_lock(&locks[order[n]], &ctx);
			अगर (err < 0)
				अवरोध;
		पूर्ण
		अगर (!err)
			dummy_load(stress);

		अगर (contended > n)
			ww_mutex_unlock(&locks[order[contended]]);
		contended = n;
		जबतक (n--)
			ww_mutex_unlock(&locks[order[n]]);

		अगर (err == -EDEADLK) अणु
			ww_mutex_lock_slow(&locks[order[contended]], &ctx);
			जाओ retry;
		पूर्ण

		अगर (err) अणु
			pr_err_once("stress (%s) failed with %d\n",
				    __func__, err);
			अवरोध;
		पूर्ण

		ww_acquire_fini(&ctx);
	पूर्ण जबतक (!समय_after(jअगरfies, stress->समयout));

	kमुक्त(order);
	kमुक्त(stress);
पूर्ण

काष्ठा reorder_lock अणु
	काष्ठा list_head link;
	काष्ठा ww_mutex *lock;
पूर्ण;

अटल व्योम stress_reorder_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा stress *stress = container_of(work, typeof(*stress), work);
	LIST_HEAD(locks);
	काष्ठा ww_acquire_ctx ctx;
	काष्ठा reorder_lock *ll, *ln;
	पूर्णांक *order;
	पूर्णांक n, err;

	order = get_अक्रमom_order(stress->nlocks);
	अगर (!order)
		वापस;

	क्रम (n = 0; n < stress->nlocks; n++) अणु
		ll = kदो_स्मृति(माप(*ll), GFP_KERNEL);
		अगर (!ll)
			जाओ out;

		ll->lock = &stress->locks[order[n]];
		list_add(&ll->link, &locks);
	पूर्ण
	kमुक्त(order);
	order = शून्य;

	करो अणु
		ww_acquire_init(&ctx, &ww_class);

		list_क्रम_each_entry(ll, &locks, link) अणु
			err = ww_mutex_lock(ll->lock, &ctx);
			अगर (!err)
				जारी;

			ln = ll;
			list_क्रम_each_entry_जारी_reverse(ln, &locks, link)
				ww_mutex_unlock(ln->lock);

			अगर (err != -EDEADLK) अणु
				pr_err_once("stress (%s) failed with %d\n",
					    __func__, err);
				अवरोध;
			पूर्ण

			ww_mutex_lock_slow(ll->lock, &ctx);
			list_move(&ll->link, &locks); /* restarts iteration */
		पूर्ण

		dummy_load(stress);
		list_क्रम_each_entry(ll, &locks, link)
			ww_mutex_unlock(ll->lock);

		ww_acquire_fini(&ctx);
	पूर्ण जबतक (!समय_after(jअगरfies, stress->समयout));

out:
	list_क्रम_each_entry_safe(ll, ln, &locks, link)
		kमुक्त(ll);
	kमुक्त(order);
	kमुक्त(stress);
पूर्ण

अटल व्योम stress_one_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा stress *stress = container_of(work, typeof(*stress), work);
	स्थिर पूर्णांक nlocks = stress->nlocks;
	काष्ठा ww_mutex *lock = stress->locks + (get_अक्रमom_पूर्णांक() % nlocks);
	पूर्णांक err;

	करो अणु
		err = ww_mutex_lock(lock, शून्य);
		अगर (!err) अणु
			dummy_load(stress);
			ww_mutex_unlock(lock);
		पूर्ण अन्यथा अणु
			pr_err_once("stress (%s) failed with %d\n",
				    __func__, err);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (!समय_after(jअगरfies, stress->समयout));

	kमुक्त(stress);
पूर्ण

#घोषणा STRESS_INORDER BIT(0)
#घोषणा STRESS_REORDER BIT(1)
#घोषणा STRESS_ONE BIT(2)
#घोषणा STRESS_ALL (STRESS_INORDER | STRESS_REORDER | STRESS_ONE)

अटल पूर्णांक stress(पूर्णांक nlocks, पूर्णांक nthपढ़ोs, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ww_mutex *locks;
	पूर्णांक n;

	locks = kदो_स्मृति_array(nlocks, माप(*locks), GFP_KERNEL);
	अगर (!locks)
		वापस -ENOMEM;

	क्रम (n = 0; n < nlocks; n++)
		ww_mutex_init(&locks[n], &ww_class);

	क्रम (n = 0; nthपढ़ोs; n++) अणु
		काष्ठा stress *stress;
		व्योम (*fn)(काष्ठा work_काष्ठा *work);

		fn = शून्य;
		चयन (n & 3) अणु
		हाल 0:
			अगर (flags & STRESS_INORDER)
				fn = stress_inorder_work;
			अवरोध;
		हाल 1:
			अगर (flags & STRESS_REORDER)
				fn = stress_reorder_work;
			अवरोध;
		हाल 2:
			अगर (flags & STRESS_ONE)
				fn = stress_one_work;
			अवरोध;
		पूर्ण

		अगर (!fn)
			जारी;

		stress = kदो_स्मृति(माप(*stress), GFP_KERNEL);
		अगर (!stress)
			अवरोध;

		INIT_WORK(&stress->work, fn);
		stress->locks = locks;
		stress->nlocks = nlocks;
		stress->समयout = jअगरfies + 2*HZ;

		queue_work(wq, &stress->work);
		nthपढ़ोs--;
	पूर्ण

	flush_workqueue(wq);

	क्रम (n = 0; n < nlocks; n++)
		ww_mutex_destroy(&locks[n]);
	kमुक्त(locks);

	वापस 0;
पूर्ण

अटल पूर्णांक __init test_ww_mutex_init(व्योम)
अणु
	पूर्णांक ncpus = num_online_cpus();
	पूर्णांक ret;

	wq = alloc_workqueue("test-ww_mutex", WQ_UNBOUND, 0);
	अगर (!wq)
		वापस -ENOMEM;

	ret = test_mutex();
	अगर (ret)
		वापस ret;

	ret = test_aa();
	अगर (ret)
		वापस ret;

	ret = test_abba(false);
	अगर (ret)
		वापस ret;

	ret = test_abba(true);
	अगर (ret)
		वापस ret;

	ret = test_cycle(ncpus);
	अगर (ret)
		वापस ret;

	ret = stress(16, 2*ncpus, STRESS_INORDER);
	अगर (ret)
		वापस ret;

	ret = stress(16, 2*ncpus, STRESS_REORDER);
	अगर (ret)
		वापस ret;

	ret = stress(4095, hweight32(STRESS_ALL)*ncpus, STRESS_ALL);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम __निकास test_ww_mutex_निकास(व्योम)
अणु
	destroy_workqueue(wq);
पूर्ण

module_init(test_ww_mutex_init);
module_निकास(test_ww_mutex_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Intel Corporation");
