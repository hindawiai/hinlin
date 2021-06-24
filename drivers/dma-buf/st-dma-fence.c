<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */

/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-fence.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "selftest.h"

अटल काष्ठा kmem_cache *slab_fences;

अटल काष्ठा mock_fence अणु
	काष्ठा dma_fence base;
	काष्ठा spinlock lock;
पूर्ण *to_mock_fence(काष्ठा dma_fence *f) अणु
	वापस container_of(f, काष्ठा mock_fence, base);
पूर्ण

अटल स्थिर अक्षर *mock_name(काष्ठा dma_fence *f)
अणु
	वापस "mock";
पूर्ण

अटल व्योम mock_fence_release(काष्ठा dma_fence *f)
अणु
	kmem_cache_मुक्त(slab_fences, to_mock_fence(f));
पूर्ण

काष्ठा रुको_cb अणु
	काष्ठा dma_fence_cb cb;
	काष्ठा task_काष्ठा *task;
पूर्ण;

अटल व्योम mock_wakeup(काष्ठा dma_fence *f, काष्ठा dma_fence_cb *cb)
अणु
	wake_up_process(container_of(cb, काष्ठा रुको_cb, cb)->task);
पूर्ण

अटल दीर्घ mock_रुको(काष्ठा dma_fence *f, bool पूर्णांकr, दीर्घ समयout)
अणु
	स्थिर पूर्णांक state = पूर्णांकr ? TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE;
	काष्ठा रुको_cb cb = अणु .task = current पूर्ण;

	अगर (dma_fence_add_callback(f, &cb.cb, mock_wakeup))
		वापस समयout;

	जबतक (समयout) अणु
		set_current_state(state);

		अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &f->flags))
			अवरोध;

		अगर (संकेत_pending_state(state, current))
			अवरोध;

		समयout = schedule_समयout(समयout);
	पूर्ण
	__set_current_state(TASK_RUNNING);

	अगर (!dma_fence_हटाओ_callback(f, &cb.cb))
		वापस समयout;

	अगर (संकेत_pending_state(state, current))
		वापस -ERESTARTSYS;

	वापस -ETIME;
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops mock_ops = अणु
	.get_driver_name = mock_name,
	.get_समयline_name = mock_name,
	.रुको = mock_रुको,
	.release = mock_fence_release,
पूर्ण;

अटल काष्ठा dma_fence *mock_fence(व्योम)
अणु
	काष्ठा mock_fence *f;

	f = kmem_cache_alloc(slab_fences, GFP_KERNEL);
	अगर (!f)
		वापस शून्य;

	spin_lock_init(&f->lock);
	dma_fence_init(&f->base, &mock_ops, &f->lock, 0, 0);

	वापस &f->base;
पूर्ण

अटल पूर्णांक sanitycheck(व्योम *arg)
अणु
	काष्ठा dma_fence *f;

	f = mock_fence();
	अगर (!f)
		वापस -ENOMEM;

	dma_fence_संकेत(f);
	dma_fence_put(f);

	वापस 0;
पूर्ण

अटल पूर्णांक test_संकेतing(व्योम *arg)
अणु
	काष्ठा dma_fence *f;
	पूर्णांक err = -EINVAL;

	f = mock_fence();
	अगर (!f)
		वापस -ENOMEM;

	अगर (dma_fence_is_संकेतed(f)) अणु
		pr_err("Fence unexpectedly signaled on creation\n");
		जाओ err_मुक्त;
	पूर्ण

	अगर (dma_fence_संकेत(f)) अणु
		pr_err("Fence reported being already signaled\n");
		जाओ err_मुक्त;
	पूर्ण

	अगर (!dma_fence_is_संकेतed(f)) अणु
		pr_err("Fence not reporting signaled\n");
		जाओ err_मुक्त;
	पूर्ण

	अगर (!dma_fence_संकेत(f)) अणु
		pr_err("Fence reported not being already signaled\n");
		जाओ err_मुक्त;
	पूर्ण

	err = 0;
err_मुक्त:
	dma_fence_put(f);
	वापस err;
पूर्ण

काष्ठा simple_cb अणु
	काष्ठा dma_fence_cb cb;
	bool seen;
पूर्ण;

अटल व्योम simple_callback(काष्ठा dma_fence *f, काष्ठा dma_fence_cb *cb)
अणु
	smp_store_mb(container_of(cb, काष्ठा simple_cb, cb)->seen, true);
पूर्ण

अटल पूर्णांक test_add_callback(व्योम *arg)
अणु
	काष्ठा simple_cb cb = अणुपूर्ण;
	काष्ठा dma_fence *f;
	पूर्णांक err = -EINVAL;

	f = mock_fence();
	अगर (!f)
		वापस -ENOMEM;

	अगर (dma_fence_add_callback(f, &cb.cb, simple_callback)) अणु
		pr_err("Failed to add callback, fence already signaled!\n");
		जाओ err_मुक्त;
	पूर्ण

	dma_fence_संकेत(f);
	अगर (!cb.seen) अणु
		pr_err("Callback failed!\n");
		जाओ err_मुक्त;
	पूर्ण

	err = 0;
err_मुक्त:
	dma_fence_put(f);
	वापस err;
पूर्ण

अटल पूर्णांक test_late_add_callback(व्योम *arg)
अणु
	काष्ठा simple_cb cb = अणुपूर्ण;
	काष्ठा dma_fence *f;
	पूर्णांक err = -EINVAL;

	f = mock_fence();
	अगर (!f)
		वापस -ENOMEM;

	dma_fence_संकेत(f);

	अगर (!dma_fence_add_callback(f, &cb.cb, simple_callback)) अणु
		pr_err("Added callback, but fence was already signaled!\n");
		जाओ err_मुक्त;
	पूर्ण

	dma_fence_संकेत(f);
	अगर (cb.seen) अणु
		pr_err("Callback called after failed attachment !\n");
		जाओ err_मुक्त;
	पूर्ण

	err = 0;
err_मुक्त:
	dma_fence_put(f);
	वापस err;
पूर्ण

अटल पूर्णांक test_rm_callback(व्योम *arg)
अणु
	काष्ठा simple_cb cb = अणुपूर्ण;
	काष्ठा dma_fence *f;
	पूर्णांक err = -EINVAL;

	f = mock_fence();
	अगर (!f)
		वापस -ENOMEM;

	अगर (dma_fence_add_callback(f, &cb.cb, simple_callback)) अणु
		pr_err("Failed to add callback, fence already signaled!\n");
		जाओ err_मुक्त;
	पूर्ण

	अगर (!dma_fence_हटाओ_callback(f, &cb.cb)) अणु
		pr_err("Failed to remove callback!\n");
		जाओ err_मुक्त;
	पूर्ण

	dma_fence_संकेत(f);
	अगर (cb.seen) अणु
		pr_err("Callback still signaled after removal!\n");
		जाओ err_मुक्त;
	पूर्ण

	err = 0;
err_मुक्त:
	dma_fence_put(f);
	वापस err;
पूर्ण

अटल पूर्णांक test_late_rm_callback(व्योम *arg)
अणु
	काष्ठा simple_cb cb = अणुपूर्ण;
	काष्ठा dma_fence *f;
	पूर्णांक err = -EINVAL;

	f = mock_fence();
	अगर (!f)
		वापस -ENOMEM;

	अगर (dma_fence_add_callback(f, &cb.cb, simple_callback)) अणु
		pr_err("Failed to add callback, fence already signaled!\n");
		जाओ err_मुक्त;
	पूर्ण

	dma_fence_संकेत(f);
	अगर (!cb.seen) अणु
		pr_err("Callback failed!\n");
		जाओ err_मुक्त;
	पूर्ण

	अगर (dma_fence_हटाओ_callback(f, &cb.cb)) अणु
		pr_err("Callback removal succeed after being executed!\n");
		जाओ err_मुक्त;
	पूर्ण

	err = 0;
err_मुक्त:
	dma_fence_put(f);
	वापस err;
पूर्ण

अटल पूर्णांक test_status(व्योम *arg)
अणु
	काष्ठा dma_fence *f;
	पूर्णांक err = -EINVAL;

	f = mock_fence();
	अगर (!f)
		वापस -ENOMEM;

	अगर (dma_fence_get_status(f)) अणु
		pr_err("Fence unexpectedly has signaled status on creation\n");
		जाओ err_मुक्त;
	पूर्ण

	dma_fence_संकेत(f);
	अगर (!dma_fence_get_status(f)) अणु
		pr_err("Fence not reporting signaled status\n");
		जाओ err_मुक्त;
	पूर्ण

	err = 0;
err_मुक्त:
	dma_fence_put(f);
	वापस err;
पूर्ण

अटल पूर्णांक test_error(व्योम *arg)
अणु
	काष्ठा dma_fence *f;
	पूर्णांक err = -EINVAL;

	f = mock_fence();
	अगर (!f)
		वापस -ENOMEM;

	dma_fence_set_error(f, -EIO);

	अगर (dma_fence_get_status(f)) अणु
		pr_err("Fence unexpectedly has error status before signal\n");
		जाओ err_मुक्त;
	पूर्ण

	dma_fence_संकेत(f);
	अगर (dma_fence_get_status(f) != -EIO) अणु
		pr_err("Fence not reporting error status, got %d\n",
		       dma_fence_get_status(f));
		जाओ err_मुक्त;
	पूर्ण

	err = 0;
err_मुक्त:
	dma_fence_put(f);
	वापस err;
पूर्ण

अटल पूर्णांक test_रुको(व्योम *arg)
अणु
	काष्ठा dma_fence *f;
	पूर्णांक err = -EINVAL;

	f = mock_fence();
	अगर (!f)
		वापस -ENOMEM;

	अगर (dma_fence_रुको_समयout(f, false, 0) != -ETIME) अणु
		pr_err("Wait reported complete before being signaled\n");
		जाओ err_मुक्त;
	पूर्ण

	dma_fence_संकेत(f);

	अगर (dma_fence_रुको_समयout(f, false, 0) != 0) अणु
		pr_err("Wait reported incomplete after being signaled\n");
		जाओ err_मुक्त;
	पूर्ण

	err = 0;
err_मुक्त:
	dma_fence_संकेत(f);
	dma_fence_put(f);
	वापस err;
पूर्ण

काष्ठा रुको_समयr अणु
	काष्ठा समयr_list समयr;
	काष्ठा dma_fence *f;
पूर्ण;

अटल व्योम रुको_समयr(काष्ठा समयr_list *समयr)
अणु
	काष्ठा रुको_समयr *wt = from_समयr(wt, समयr, समयr);

	dma_fence_संकेत(wt->f);
पूर्ण

अटल पूर्णांक test_रुको_समयout(व्योम *arg)
अणु
	काष्ठा रुको_समयr wt;
	पूर्णांक err = -EINVAL;

	समयr_setup_on_stack(&wt.समयr, रुको_समयr, 0);

	wt.f = mock_fence();
	अगर (!wt.f)
		वापस -ENOMEM;

	अगर (dma_fence_रुको_समयout(wt.f, false, 1) != -ETIME) अणु
		pr_err("Wait reported complete before being signaled\n");
		जाओ err_मुक्त;
	पूर्ण

	mod_समयr(&wt.समयr, jअगरfies + 1);

	अगर (dma_fence_रुको_समयout(wt.f, false, 2) == -ETIME) अणु
		अगर (समयr_pending(&wt.समयr)) अणु
			pr_notice("Timer did not fire within the jiffie!\n");
			err = 0; /* not our fault! */
		पूर्ण अन्यथा अणु
			pr_err("Wait reported incomplete after timeout\n");
		पूर्ण
		जाओ err_मुक्त;
	पूर्ण

	err = 0;
err_मुक्त:
	del_समयr_sync(&wt.समयr);
	destroy_समयr_on_stack(&wt.समयr);
	dma_fence_संकेत(wt.f);
	dma_fence_put(wt.f);
	वापस err;
पूर्ण

अटल पूर्णांक test_stub(व्योम *arg)
अणु
	काष्ठा dma_fence *f[64];
	पूर्णांक err = -EINVAL;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(f); i++) अणु
		f[i] = dma_fence_get_stub();
		अगर (!dma_fence_is_संकेतed(f[i])) अणु
			pr_err("Obtained unsignaled stub fence!\n");
			जाओ err;
		पूर्ण
	पूर्ण

	err = 0;
err:
	जबतक (i--)
		dma_fence_put(f[i]);
	वापस err;
पूर्ण

/* Now off to the races! */

काष्ठा race_thपढ़ो अणु
	काष्ठा dma_fence __rcu **fences;
	काष्ठा task_काष्ठा *task;
	bool beक्रमe;
	पूर्णांक id;
पूर्ण;

अटल व्योम __रुको_क्रम_callbacks(काष्ठा dma_fence *f)
अणु
	spin_lock_irq(f->lock);
	spin_unlock_irq(f->lock);
पूर्ण

अटल पूर्णांक thपढ़ो_संकेत_callback(व्योम *arg)
अणु
	स्थिर काष्ठा race_thपढ़ो *t = arg;
	अचिन्हित दीर्घ pass = 0;
	अचिन्हित दीर्घ miss = 0;
	पूर्णांक err = 0;

	जबतक (!err && !kthपढ़ो_should_stop()) अणु
		काष्ठा dma_fence *f1, *f2;
		काष्ठा simple_cb cb;

		f1 = mock_fence();
		अगर (!f1) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		rcu_assign_poपूर्णांकer(t->fences[t->id], f1);
		smp_wmb();

		rcu_पढ़ो_lock();
		करो अणु
			f2 = dma_fence_get_rcu_safe(&t->fences[!t->id]);
		पूर्ण जबतक (!f2 && !kthपढ़ो_should_stop());
		rcu_पढ़ो_unlock();

		अगर (t->beक्रमe)
			dma_fence_संकेत(f1);

		smp_store_mb(cb.seen, false);
		अगर (!f2 ||
		    dma_fence_add_callback(f2, &cb.cb, simple_callback)) अणु
			miss++;
			cb.seen = true;
		पूर्ण

		अगर (!t->beक्रमe)
			dma_fence_संकेत(f1);

		अगर (!cb.seen) अणु
			dma_fence_रुको(f2, false);
			__रुको_क्रम_callbacks(f2);
		पूर्ण

		अगर (!READ_ONCE(cb.seen)) अणु
			pr_err("Callback not seen on thread %d, pass %lu (%lu misses), signaling %s add_callback; fence signaled? %s\n",
			       t->id, pass, miss,
			       t->beक्रमe ? "before" : "after",
			       dma_fence_is_संकेतed(f2) ? "yes" : "no");
			err = -EINVAL;
		पूर्ण

		dma_fence_put(f2);

		rcu_assign_poपूर्णांकer(t->fences[t->id], शून्य);
		smp_wmb();

		dma_fence_put(f1);

		pass++;
	पूर्ण

	pr_info("%s[%d] completed %lu passes, %lu misses\n",
		__func__, t->id, pass, miss);
	वापस err;
पूर्ण

अटल पूर्णांक race_संकेत_callback(व्योम *arg)
अणु
	काष्ठा dma_fence __rcu *f[2] = अणुपूर्ण;
	पूर्णांक ret = 0;
	पूर्णांक pass;

	क्रम (pass = 0; !ret && pass <= 1; pass++) अणु
		काष्ठा race_thपढ़ो t[2];
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(t); i++) अणु
			t[i].fences = f;
			t[i].id = i;
			t[i].beक्रमe = pass;
			t[i].task = kthपढ़ो_run(thपढ़ो_संकेत_callback, &t[i],
						"dma-fence:%d", i);
			get_task_काष्ठा(t[i].task);
		पूर्ण

		msleep(50);

		क्रम (i = 0; i < ARRAY_SIZE(t); i++) अणु
			पूर्णांक err;

			err = kthपढ़ो_stop(t[i].task);
			अगर (err && !ret)
				ret = err;

			put_task_काष्ठा(t[i].task);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक dma_fence(व्योम)
अणु
	अटल स्थिर काष्ठा subtest tests[] = अणु
		SUBTEST(sanitycheck),
		SUBTEST(test_संकेतing),
		SUBTEST(test_add_callback),
		SUBTEST(test_late_add_callback),
		SUBTEST(test_rm_callback),
		SUBTEST(test_late_rm_callback),
		SUBTEST(test_status),
		SUBTEST(test_error),
		SUBTEST(test_रुको),
		SUBTEST(test_रुको_समयout),
		SUBTEST(test_stub),
		SUBTEST(race_संकेत_callback),
	पूर्ण;
	पूर्णांक ret;

	pr_info("sizeof(dma_fence)=%zu\n", माप(काष्ठा dma_fence));

	slab_fences = KMEM_CACHE(mock_fence,
				 SLAB_TYPESAFE_BY_RCU |
				 SLAB_HWCACHE_ALIGN);
	अगर (!slab_fences)
		वापस -ENOMEM;

	ret = subtests(tests, शून्य);

	kmem_cache_destroy(slab_fences);

	वापस ret;
पूर्ण
