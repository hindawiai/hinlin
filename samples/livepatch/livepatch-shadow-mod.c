<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Joe Lawrence <joe.lawrence@redhat.com>
 */

/*
 * livepatch-shaकरोw-mod.c - Shaकरोw variables, buggy module demo
 *
 * Purpose
 * -------
 *
 * As a demonstration of livepatch shaकरोw variable API, this module
 * पूर्णांकroduces memory leak behavior that livepatch modules
 * livepatch-shaकरोw-fix1.ko and livepatch-shaकरोw-fix2.ko correct and
 * enhance.
 *
 * WARNING - even though the livepatch-shaकरोw-fix modules patch the
 * memory leak, please load these modules at your own risk -- some
 * amount of memory may leaked beक्रमe the bug is patched.
 *
 *
 * Usage
 * -----
 *
 * Step 1 - Load the buggy demonstration module:
 *
 *   insmod samples/livepatch/livepatch-shaकरोw-mod.ko
 *
 * Watch dmesg output क्रम a few moments to see new dummy being allocated
 * and a periodic cleanup check.  (Note: a small amount of memory is
 * being leaked.)
 *
 *
 * Step 2 - Load livepatch fix1:
 *
 *   insmod samples/livepatch/livepatch-shaकरोw-fix1.ko
 *
 * Continue watching dmesg and note that now livepatch_fix1_dummy_मुक्त()
 * and livepatch_fix1_dummy_alloc() are logging messages about leaked
 * memory and eventually leaks prevented.
 *
 *
 * Step 3 - Load livepatch fix2 (on top of fix1):
 *
 *   insmod samples/livepatch/livepatch-shaकरोw-fix2.ko
 *
 * This module extends functionality through shaकरोw variables, as a new
 * "check" counter is added to the dummy काष्ठाure.  Periodic dmesg
 * messages will log these as dummies are cleaned up.
 *
 *
 * Step 4 - Cleanup
 *
 * Unwind the demonstration by disabling the livepatch fix modules, then
 * removing them and the demo module:
 *
 *   echo 0 > /sys/kernel/livepatch/livepatch_shaकरोw_fix2/enabled
 *   echo 0 > /sys/kernel/livepatch/livepatch_shaकरोw_fix1/enabled
 *   rmmod livepatch-shaकरोw-fix2
 *   rmmod livepatch-shaकरोw-fix1
 *   rmmod livepatch-shaकरोw-mod
 */


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/workqueue.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joe Lawrence <joe.lawrence@redhat.com>");
MODULE_DESCRIPTION("Buggy module for shadow variable demo");

/* Allocate new dummies every second */
#घोषणा ALLOC_PERIOD	1
/* Check क्रम expired dummies after a few new ones have been allocated */
#घोषणा CLEANUP_PERIOD	(3 * ALLOC_PERIOD)
/* Dummies expire after a few cleanup instances */
#घोषणा EXPIRE_PERIOD	(4 * CLEANUP_PERIOD)

/*
 * Keep a list of all the dummies so we can clean up any residual ones
 * on module निकास
 */
अटल LIST_HEAD(dummy_list);
अटल DEFINE_MUTEX(dummy_list_mutex);

काष्ठा dummy अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ jअगरfies_expire;
पूर्ण;

अटल __used noअंतरभूत काष्ठा dummy *dummy_alloc(व्योम)
अणु
	काष्ठा dummy *d;
	पूर्णांक *leak;

	d = kzalloc(माप(*d), GFP_KERNEL);
	अगर (!d)
		वापस शून्य;

	d->jअगरfies_expire = jअगरfies +
		msecs_to_jअगरfies(1000 * EXPIRE_PERIOD);

	/* Oops, क्रमgot to save leak! */
	leak = kzalloc(माप(*leak), GFP_KERNEL);
	अगर (!leak) अणु
		kमुक्त(d);
		वापस शून्य;
	पूर्ण

	pr_info("%s: dummy @ %p, expires @ %lx\n",
		__func__, d, d->jअगरfies_expire);

	वापस d;
पूर्ण

अटल __used noअंतरभूत व्योम dummy_मुक्त(काष्ठा dummy *d)
अणु
	pr_info("%s: dummy @ %p, expired = %lx\n",
		__func__, d, d->jअगरfies_expire);

	kमुक्त(d);
पूर्ण

अटल __used noअंतरभूत bool dummy_check(काष्ठा dummy *d,
					   अचिन्हित दीर्घ jअगरfies)
अणु
	वापस समय_after(jअगरfies, d->jअगरfies_expire);
पूर्ण

/*
 * alloc_work_func: allocates new dummy काष्ठाures, allocates additional
 *                  memory, aptly named "leak", but करोesn't keep
 *                  permanent record of it.
 */

अटल व्योम alloc_work_func(काष्ठा work_काष्ठा *work);
अटल DECLARE_DELAYED_WORK(alloc_dwork, alloc_work_func);

अटल व्योम alloc_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dummy *d;

	d = dummy_alloc();
	अगर (!d)
		वापस;

	mutex_lock(&dummy_list_mutex);
	list_add(&d->list, &dummy_list);
	mutex_unlock(&dummy_list_mutex);

	schedule_delayed_work(&alloc_dwork,
		msecs_to_jअगरfies(1000 * ALLOC_PERIOD));
पूर्ण

/*
 * cleanup_work_func: मुक्तs dummy काष्ठाures.  Without knownledge of
 *                    "leak", it leaks the additional memory that
 *                    alloc_work_func created.
 */

अटल व्योम cleanup_work_func(काष्ठा work_काष्ठा *work);
अटल DECLARE_DELAYED_WORK(cleanup_dwork, cleanup_work_func);

अटल व्योम cleanup_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dummy *d, *पंचांगp;
	अचिन्हित दीर्घ j;

	j = jअगरfies;
	pr_info("%s: jiffies = %lx\n", __func__, j);

	mutex_lock(&dummy_list_mutex);
	list_क्रम_each_entry_safe(d, पंचांगp, &dummy_list, list) अणु

		/* Kick out and मुक्त any expired dummies */
		अगर (dummy_check(d, j)) अणु
			list_del(&d->list);
			dummy_मुक्त(d);
		पूर्ण
	पूर्ण
	mutex_unlock(&dummy_list_mutex);

	schedule_delayed_work(&cleanup_dwork,
		msecs_to_jअगरfies(1000 * CLEANUP_PERIOD));
पूर्ण

अटल पूर्णांक livepatch_shaकरोw_mod_init(व्योम)
अणु
	schedule_delayed_work(&alloc_dwork,
		msecs_to_jअगरfies(1000 * ALLOC_PERIOD));
	schedule_delayed_work(&cleanup_dwork,
		msecs_to_jअगरfies(1000 * CLEANUP_PERIOD));

	वापस 0;
पूर्ण

अटल व्योम livepatch_shaकरोw_mod_निकास(व्योम)
अणु
	काष्ठा dummy *d, *पंचांगp;

	/* Wait क्रम any dummies at work */
	cancel_delayed_work_sync(&alloc_dwork);
	cancel_delayed_work_sync(&cleanup_dwork);

	/* Cleanup residual dummies */
	list_क्रम_each_entry_safe(d, पंचांगp, &dummy_list, list) अणु
		list_del(&d->list);
		dummy_मुक्त(d);
	पूर्ण
पूर्ण

module_init(livepatch_shaकरोw_mod_init);
module_निकास(livepatch_shaकरोw_mod_निकास);
