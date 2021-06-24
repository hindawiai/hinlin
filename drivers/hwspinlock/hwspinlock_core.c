<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hardware spinlock framework
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com
 *
 * Contact: Ohad Ben-Cohen <ohad@wizery.com>
 */

#घोषणा pr_fmt(fmt)    "%s: " fmt, __func__

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/hwspinlock.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>

#समावेश "hwspinlock_internal.h"

/* retry delay used in atomic context */
#घोषणा HWSPINLOCK_RETRY_DELAY_US	100

/* radix tree tags */
#घोषणा HWSPINLOCK_UNUSED	(0) /* tags an hwspinlock as unused */

/*
 * A radix tree is used to मुख्यtain the available hwspinlock instances.
 * The tree associates hwspinlock poपूर्णांकers with their पूर्णांकeger key id,
 * and provides easy-to-use API which makes the hwspinlock core code simple
 * and easy to पढ़ो.
 *
 * Radix trees are quick on lookups, and reasonably efficient in terms of
 * storage, especially with high density usages such as this framework
 * requires (a continuous range of पूर्णांकeger keys, beginning with zero, is
 * used as the ID's of the hwspinlock instances).
 *
 * The radix tree API supports tagging items in the tree, which this
 * framework uses to mark unused hwspinlock instances (see the
 * HWSPINLOCK_UNUSED tag above). As a result, the process of querying the
 * tree, looking क्रम an unused hwspinlock instance, is now reduced to a
 * single radix tree API call.
 */
अटल RADIX_TREE(hwspinlock_tree, GFP_KERNEL);

/*
 * Synchronization of access to the tree is achieved using this mutex,
 * as the radix-tree API requires that users provide all synchronisation.
 * A mutex is needed because we're using non-atomic radix tree allocations.
 */
अटल DEFINE_MUTEX(hwspinlock_tree_lock);


/**
 * __hwspin_trylock() - attempt to lock a specअगरic hwspinlock
 * @hwlock: an hwspinlock which we want to trylock
 * @mode: controls whether local पूर्णांकerrupts are disabled or not
 * @flags: a poपूर्णांकer where the caller's पूर्णांकerrupt state will be saved at (अगर
 *         requested)
 *
 * This function attempts to lock an hwspinlock, and will immediately
 * fail अगर the hwspinlock is alपढ़ोy taken.
 *
 * Caution: If the mode is HWLOCK_RAW, that means user must protect the routine
 * of getting hardware lock with mutex or spinlock. Since in some scenarios,
 * user need some समय-consuming or sleepable operations under the hardware
 * lock, they need one sleepable lock (like mutex) to protect the operations.
 *
 * If the mode is neither HWLOCK_IN_ATOMIC nor HWLOCK_RAW, upon a successful
 * वापस from this function, preemption (and possibly पूर्णांकerrupts) is disabled,
 * so the caller must not sleep, and is advised to release the hwspinlock as
 * soon as possible. This is required in order to minimize remote cores polling
 * on the hardware पूर्णांकerconnect.
 *
 * The user decides whether local पूर्णांकerrupts are disabled or not, and अगर yes,
 * whether he wants their previous state to be saved. It is up to the user
 * to choose the appropriate @mode of operation, exactly the same way users
 * should decide between spin_trylock, spin_trylock_irq and
 * spin_trylock_irqsave.
 *
 * Returns 0 अगर we successfully locked the hwspinlock or -EBUSY अगर
 * the hwspinlock was alपढ़ोy taken.
 * This function will never sleep.
 */
पूर्णांक __hwspin_trylock(काष्ठा hwspinlock *hwlock, पूर्णांक mode, अचिन्हित दीर्घ *flags)
अणु
	पूर्णांक ret;

	अगर (WARN_ON(!hwlock || (!flags && mode == HWLOCK_IRQSTATE)))
		वापस -EINVAL;

	/*
	 * This spin_lockअणु_irq, _irqsaveपूर्ण serves three purposes:
	 *
	 * 1. Disable preemption, in order to minimize the period of समय
	 *    in which the hwspinlock is taken. This is important in order
	 *    to minimize the possible polling on the hardware पूर्णांकerconnect
	 *    by a remote user of this lock.
	 * 2. Make the hwspinlock SMP-safe (so we can take it from
	 *    additional contexts on the local host).
	 * 3. Ensure that in_atomic/might_sleep checks catch potential
	 *    problems with hwspinlock usage (e.g. scheduler checks like
	 *    'scheduling while atomic' etc.)
	 */
	चयन (mode) अणु
	हाल HWLOCK_IRQSTATE:
		ret = spin_trylock_irqsave(&hwlock->lock, *flags);
		अवरोध;
	हाल HWLOCK_IRQ:
		ret = spin_trylock_irq(&hwlock->lock);
		अवरोध;
	हाल HWLOCK_RAW:
	हाल HWLOCK_IN_ATOMIC:
		ret = 1;
		अवरोध;
	शेष:
		ret = spin_trylock(&hwlock->lock);
		अवरोध;
	पूर्ण

	/* is lock alपढ़ोy taken by another context on the local cpu ? */
	अगर (!ret)
		वापस -EBUSY;

	/* try to take the hwspinlock device */
	ret = hwlock->bank->ops->trylock(hwlock);

	/* अगर hwlock is alपढ़ोy taken, unकरो spin_trylock_* and निकास */
	अगर (!ret) अणु
		चयन (mode) अणु
		हाल HWLOCK_IRQSTATE:
			spin_unlock_irqrestore(&hwlock->lock, *flags);
			अवरोध;
		हाल HWLOCK_IRQ:
			spin_unlock_irq(&hwlock->lock);
			अवरोध;
		हाल HWLOCK_RAW:
		हाल HWLOCK_IN_ATOMIC:
			/* Nothing to करो */
			अवरोध;
		शेष:
			spin_unlock(&hwlock->lock);
			अवरोध;
		पूर्ण

		वापस -EBUSY;
	पूर्ण

	/*
	 * We can be sure the other core's memory operations
	 * are observable to us only _after_ we successfully take
	 * the hwspinlock, and we must make sure that subsequent memory
	 * operations (both पढ़ोs and ग_लिखोs) will not be reordered beक्रमe
	 * we actually took the hwspinlock.
	 *
	 * Note: the implicit memory barrier of the spinlock above is too
	 * early, so we need this additional explicit memory barrier.
	 */
	mb();

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__hwspin_trylock);

/**
 * __hwspin_lock_समयout() - lock an hwspinlock with समयout limit
 * @hwlock: the hwspinlock to be locked
 * @समयout: समयout value in msecs
 * @mode: mode which controls whether local पूर्णांकerrupts are disabled or not
 * @flags: a poपूर्णांकer to where the caller's पूर्णांकerrupt state will be saved at (अगर
 *         requested)
 *
 * This function locks the given @hwlock. If the @hwlock
 * is alपढ़ोy taken, the function will busy loop रुकोing क्रम it to
 * be released, but give up after @समयout msecs have elapsed.
 *
 * Caution: If the mode is HWLOCK_RAW, that means user must protect the routine
 * of getting hardware lock with mutex or spinlock. Since in some scenarios,
 * user need some समय-consuming or sleepable operations under the hardware
 * lock, they need one sleepable lock (like mutex) to protect the operations.
 *
 * If the mode is HWLOCK_IN_ATOMIC (called from an atomic context) the समयout
 * is handled with busy-रुकोing delays, hence shall not exceed few msecs.
 *
 * If the mode is neither HWLOCK_IN_ATOMIC nor HWLOCK_RAW, upon a successful
 * वापस from this function, preemption (and possibly पूर्णांकerrupts) is disabled,
 * so the caller must not sleep, and is advised to release the hwspinlock as
 * soon as possible. This is required in order to minimize remote cores polling
 * on the hardware पूर्णांकerconnect.
 *
 * The user decides whether local पूर्णांकerrupts are disabled or not, and अगर yes,
 * whether he wants their previous state to be saved. It is up to the user
 * to choose the appropriate @mode of operation, exactly the same way users
 * should decide between spin_lock, spin_lock_irq and spin_lock_irqsave.
 *
 * Returns 0 when the @hwlock was successfully taken, and an appropriate
 * error code otherwise (most notably -ETIMEDOUT अगर the @hwlock is still
 * busy after @समयout msecs). The function will never sleep.
 */
पूर्णांक __hwspin_lock_समयout(काष्ठा hwspinlock *hwlock, अचिन्हित पूर्णांक to,
					पूर्णांक mode, अचिन्हित दीर्घ *flags)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ expire, atomic_delay = 0;

	expire = msecs_to_jअगरfies(to) + jअगरfies;

	क्रम (;;) अणु
		/* Try to take the hwspinlock */
		ret = __hwspin_trylock(hwlock, mode, flags);
		अगर (ret != -EBUSY)
			अवरोध;

		/*
		 * The lock is alपढ़ोy taken, let's check अगर the user wants
		 * us to try again
		 */
		अगर (mode == HWLOCK_IN_ATOMIC) अणु
			udelay(HWSPINLOCK_RETRY_DELAY_US);
			atomic_delay += HWSPINLOCK_RETRY_DELAY_US;
			अगर (atomic_delay > to * 1000)
				वापस -ETIMEDOUT;
		पूर्ण अन्यथा अणु
			अगर (समय_is_beक्रमe_eq_jअगरfies(expire))
				वापस -ETIMEDOUT;
		पूर्ण

		/*
		 * Allow platक्रमm-specअगरic relax handlers to prevent
		 * hogging the पूर्णांकerconnect (no sleeping, though)
		 */
		अगर (hwlock->bank->ops->relax)
			hwlock->bank->ops->relax(hwlock);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__hwspin_lock_समयout);

/**
 * __hwspin_unlock() - unlock a specअगरic hwspinlock
 * @hwlock: a previously-acquired hwspinlock which we want to unlock
 * @mode: controls whether local पूर्णांकerrupts needs to be restored or not
 * @flags: previous caller's पूर्णांकerrupt state to restore (अगर requested)
 *
 * This function will unlock a specअगरic hwspinlock, enable preemption and
 * (possibly) enable पूर्णांकerrupts or restore their previous state.
 * @hwlock must be alपढ़ोy locked beक्रमe calling this function: it is a bug
 * to call unlock on a @hwlock that is alपढ़ोy unlocked.
 *
 * The user decides whether local पूर्णांकerrupts should be enabled or not, and
 * अगर yes, whether he wants their previous state to be restored. It is up
 * to the user to choose the appropriate @mode of operation, exactly the
 * same way users decide between spin_unlock, spin_unlock_irq and
 * spin_unlock_irqrestore.
 *
 * The function will never sleep.
 */
व्योम __hwspin_unlock(काष्ठा hwspinlock *hwlock, पूर्णांक mode, अचिन्हित दीर्घ *flags)
अणु
	अगर (WARN_ON(!hwlock || (!flags && mode == HWLOCK_IRQSTATE)))
		वापस;

	/*
	 * We must make sure that memory operations (both पढ़ोs and ग_लिखोs),
	 * करोne beक्रमe unlocking the hwspinlock, will not be reordered
	 * after the lock is released.
	 *
	 * That's the purpose of this explicit memory barrier.
	 *
	 * Note: the memory barrier induced by the spin_unlock below is too
	 * late; the other core is going to access memory soon after it will
	 * take the hwspinlock, and by then we want to be sure our memory
	 * operations are alपढ़ोy observable.
	 */
	mb();

	hwlock->bank->ops->unlock(hwlock);

	/* Unकरो the spin_trylockअणु_irq, _irqsaveपूर्ण called जबतक locking */
	चयन (mode) अणु
	हाल HWLOCK_IRQSTATE:
		spin_unlock_irqrestore(&hwlock->lock, *flags);
		अवरोध;
	हाल HWLOCK_IRQ:
		spin_unlock_irq(&hwlock->lock);
		अवरोध;
	हाल HWLOCK_RAW:
	हाल HWLOCK_IN_ATOMIC:
		/* Nothing to करो */
		अवरोध;
	शेष:
		spin_unlock(&hwlock->lock);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__hwspin_unlock);

/**
 * of_hwspin_lock_simple_xlate - translate hwlock_spec to वापस a lock id
 * @bank: the hwspinlock device bank
 * @hwlock_spec: hwlock specअगरier as found in the device tree
 *
 * This is a simple translation function, suitable क्रम hwspinlock platक्रमm
 * drivers that only has a lock specअगरier length of 1.
 *
 * Returns a relative index of the lock within a specअगरied bank on success,
 * or -EINVAL on invalid specअगरier cell count.
 */
अटल अंतरभूत पूर्णांक
of_hwspin_lock_simple_xlate(स्थिर काष्ठा of_phandle_args *hwlock_spec)
अणु
	अगर (WARN_ON(hwlock_spec->args_count != 1))
		वापस -EINVAL;

	वापस hwlock_spec->args[0];
पूर्ण

/**
 * of_hwspin_lock_get_id() - get lock id क्रम an OF phandle-based specअगरic lock
 * @np: device node from which to request the specअगरic hwlock
 * @index: index of the hwlock in the list of values
 *
 * This function provides a means क्रम DT users of the hwspinlock module to
 * get the global lock id of a specअगरic hwspinlock using the phandle of the
 * hwspinlock device, so that it can be requested using the normal
 * hwspin_lock_request_specअगरic() API.
 *
 * Returns the global lock id number on success, -EPROBE_DEFER अगर the hwspinlock
 * device is not yet रेजिस्टरed, -EINVAL on invalid args specअगरier value or an
 * appropriate error as वापसed from the OF parsing of the DT client node.
 */
पूर्णांक of_hwspin_lock_get_id(काष्ठा device_node *np, पूर्णांक index)
अणु
	काष्ठा of_phandle_args args;
	काष्ठा hwspinlock *hwlock;
	काष्ठा radix_tree_iter iter;
	व्योम **slot;
	पूर्णांक id;
	पूर्णांक ret;

	ret = of_parse_phandle_with_args(np, "hwlocks", "#hwlock-cells", index,
					 &args);
	अगर (ret)
		वापस ret;

	अगर (!of_device_is_available(args.np)) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	/* Find the hwspinlock device: we need its base_id */
	ret = -EPROBE_DEFER;
	rcu_पढ़ो_lock();
	radix_tree_क्रम_each_slot(slot, &hwspinlock_tree, &iter, 0) अणु
		hwlock = radix_tree_deref_slot(slot);
		अगर (unlikely(!hwlock))
			जारी;
		अगर (radix_tree_deref_retry(hwlock)) अणु
			slot = radix_tree_iter_retry(&iter);
			जारी;
		पूर्ण

		अगर (hwlock->bank->dev->of_node == args.np) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (ret < 0)
		जाओ out;

	id = of_hwspin_lock_simple_xlate(&args);
	अगर (id < 0 || id >= hwlock->bank->num_locks) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	id += hwlock->bank->base_id;

out:
	of_node_put(args.np);
	वापस ret ? ret : id;
पूर्ण
EXPORT_SYMBOL_GPL(of_hwspin_lock_get_id);

/**
 * of_hwspin_lock_get_id_byname() - get lock id क्रम an specअगरied hwlock name
 * @np: device node from which to request the specअगरic hwlock
 * @name: hwlock name
 *
 * This function provides a means क्रम DT users of the hwspinlock module to
 * get the global lock id of a specअगरic hwspinlock using the specअगरied name of
 * the hwspinlock device, so that it can be requested using the normal
 * hwspin_lock_request_specअगरic() API.
 *
 * Returns the global lock id number on success, -EPROBE_DEFER अगर the hwspinlock
 * device is not yet रेजिस्टरed, -EINVAL on invalid args specअगरier value or an
 * appropriate error as वापसed from the OF parsing of the DT client node.
 */
पूर्णांक of_hwspin_lock_get_id_byname(काष्ठा device_node *np, स्थिर अक्षर *name)
अणु
	पूर्णांक index;

	अगर (!name)
		वापस -EINVAL;

	index = of_property_match_string(np, "hwlock-names", name);
	अगर (index < 0)
		वापस index;

	वापस of_hwspin_lock_get_id(np, index);
पूर्ण
EXPORT_SYMBOL_GPL(of_hwspin_lock_get_id_byname);

अटल पूर्णांक hwspin_lock_रेजिस्टर_single(काष्ठा hwspinlock *hwlock, पूर्णांक id)
अणु
	काष्ठा hwspinlock *पंचांगp;
	पूर्णांक ret;

	mutex_lock(&hwspinlock_tree_lock);

	ret = radix_tree_insert(&hwspinlock_tree, id, hwlock);
	अगर (ret) अणु
		अगर (ret == -EEXIST)
			pr_err("hwspinlock id %d already exists!\n", id);
		जाओ out;
	पूर्ण

	/* mark this hwspinlock as available */
	पंचांगp = radix_tree_tag_set(&hwspinlock_tree, id, HWSPINLOCK_UNUSED);

	/* self-sanity check which should never fail */
	WARN_ON(पंचांगp != hwlock);

out:
	mutex_unlock(&hwspinlock_tree_lock);
	वापस 0;
पूर्ण

अटल काष्ठा hwspinlock *hwspin_lock_unरेजिस्टर_single(अचिन्हित पूर्णांक id)
अणु
	काष्ठा hwspinlock *hwlock = शून्य;
	पूर्णांक ret;

	mutex_lock(&hwspinlock_tree_lock);

	/* make sure the hwspinlock is not in use (tag is set) */
	ret = radix_tree_tag_get(&hwspinlock_tree, id, HWSPINLOCK_UNUSED);
	अगर (ret == 0) अणु
		pr_err("hwspinlock %d still in use (or not present)\n", id);
		जाओ out;
	पूर्ण

	hwlock = radix_tree_delete(&hwspinlock_tree, id);
	अगर (!hwlock) अणु
		pr_err("failed to delete hwspinlock %d\n", id);
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&hwspinlock_tree_lock);
	वापस hwlock;
पूर्ण

/**
 * hwspin_lock_रेजिस्टर() - रेजिस्टर a new hw spinlock device
 * @bank: the hwspinlock device, which usually provides numerous hw locks
 * @dev: the backing device
 * @ops: hwspinlock handlers क्रम this device
 * @base_id: id of the first hardware spinlock in this bank
 * @num_locks: number of hwspinlocks provided by this device
 *
 * This function should be called from the underlying platक्रमm-specअगरic
 * implementation, to रेजिस्टर a new hwspinlock device instance.
 *
 * Should be called from a process context (might sleep)
 *
 * Returns 0 on success, or an appropriate error code on failure
 */
पूर्णांक hwspin_lock_रेजिस्टर(काष्ठा hwspinlock_device *bank, काष्ठा device *dev,
		स्थिर काष्ठा hwspinlock_ops *ops, पूर्णांक base_id, पूर्णांक num_locks)
अणु
	काष्ठा hwspinlock *hwlock;
	पूर्णांक ret = 0, i;

	अगर (!bank || !ops || !dev || !num_locks || !ops->trylock ||
							!ops->unlock) अणु
		pr_err("invalid parameters\n");
		वापस -EINVAL;
	पूर्ण

	bank->dev = dev;
	bank->ops = ops;
	bank->base_id = base_id;
	bank->num_locks = num_locks;

	क्रम (i = 0; i < num_locks; i++) अणु
		hwlock = &bank->lock[i];

		spin_lock_init(&hwlock->lock);
		hwlock->bank = bank;

		ret = hwspin_lock_रेजिस्टर_single(hwlock, base_id + i);
		अगर (ret)
			जाओ reg_failed;
	पूर्ण

	वापस 0;

reg_failed:
	जबतक (--i >= 0)
		hwspin_lock_unरेजिस्टर_single(base_id + i);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hwspin_lock_रेजिस्टर);

/**
 * hwspin_lock_unरेजिस्टर() - unरेजिस्टर an hw spinlock device
 * @bank: the hwspinlock device, which usually provides numerous hw locks
 *
 * This function should be called from the underlying platक्रमm-specअगरic
 * implementation, to unरेजिस्टर an existing (and unused) hwspinlock.
 *
 * Should be called from a process context (might sleep)
 *
 * Returns 0 on success, or an appropriate error code on failure
 */
पूर्णांक hwspin_lock_unरेजिस्टर(काष्ठा hwspinlock_device *bank)
अणु
	काष्ठा hwspinlock *hwlock, *पंचांगp;
	पूर्णांक i;

	क्रम (i = 0; i < bank->num_locks; i++) अणु
		hwlock = &bank->lock[i];

		पंचांगp = hwspin_lock_unरेजिस्टर_single(bank->base_id + i);
		अगर (!पंचांगp)
			वापस -EBUSY;

		/* self-sanity check that should never fail */
		WARN_ON(पंचांगp != hwlock);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hwspin_lock_unरेजिस्टर);

अटल व्योम devm_hwspin_lock_unreg(काष्ठा device *dev, व्योम *res)
अणु
	hwspin_lock_unरेजिस्टर(*(काष्ठा hwspinlock_device **)res);
पूर्ण

अटल पूर्णांक devm_hwspin_lock_device_match(काष्ठा device *dev, व्योम *res,
					 व्योम *data)
अणु
	काष्ठा hwspinlock_device **bank = res;

	अगर (WARN_ON(!bank || !*bank))
		वापस 0;

	वापस *bank == data;
पूर्ण

/**
 * devm_hwspin_lock_unरेजिस्टर() - unरेजिस्टर an hw spinlock device क्रम
 *				   a managed device
 * @dev: the backing device
 * @bank: the hwspinlock device, which usually provides numerous hw locks
 *
 * This function should be called from the underlying platक्रमm-specअगरic
 * implementation, to unरेजिस्टर an existing (and unused) hwspinlock.
 *
 * Should be called from a process context (might sleep)
 *
 * Returns 0 on success, or an appropriate error code on failure
 */
पूर्णांक devm_hwspin_lock_unरेजिस्टर(काष्ठा device *dev,
				काष्ठा hwspinlock_device *bank)
अणु
	पूर्णांक ret;

	ret = devres_release(dev, devm_hwspin_lock_unreg,
			     devm_hwspin_lock_device_match, bank);
	WARN_ON(ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_hwspin_lock_unरेजिस्टर);

/**
 * devm_hwspin_lock_रेजिस्टर() - रेजिस्टर a new hw spinlock device क्रम
 *				 a managed device
 * @dev: the backing device
 * @bank: the hwspinlock device, which usually provides numerous hw locks
 * @ops: hwspinlock handlers क्रम this device
 * @base_id: id of the first hardware spinlock in this bank
 * @num_locks: number of hwspinlocks provided by this device
 *
 * This function should be called from the underlying platक्रमm-specअगरic
 * implementation, to रेजिस्टर a new hwspinlock device instance.
 *
 * Should be called from a process context (might sleep)
 *
 * Returns 0 on success, or an appropriate error code on failure
 */
पूर्णांक devm_hwspin_lock_रेजिस्टर(काष्ठा device *dev,
			      काष्ठा hwspinlock_device *bank,
			      स्थिर काष्ठा hwspinlock_ops *ops,
			      पूर्णांक base_id, पूर्णांक num_locks)
अणु
	काष्ठा hwspinlock_device **ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_hwspin_lock_unreg, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	ret = hwspin_lock_रेजिस्टर(bank, dev, ops, base_id, num_locks);
	अगर (!ret) अणु
		*ptr = bank;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_hwspin_lock_रेजिस्टर);

/**
 * __hwspin_lock_request() - tag an hwspinlock as used and घातer it up
 *
 * This is an पूर्णांकernal function that prepares an hwspinlock instance
 * beक्रमe it is given to the user. The function assumes that
 * hwspinlock_tree_lock is taken.
 *
 * Returns 0 or positive to indicate success, and a negative value to
 * indicate an error (with the appropriate error code)
 */
अटल पूर्णांक __hwspin_lock_request(काष्ठा hwspinlock *hwlock)
अणु
	काष्ठा device *dev = hwlock->bank->dev;
	काष्ठा hwspinlock *पंचांगp;
	पूर्णांक ret;

	/* prevent underlying implementation from being हटाओd */
	अगर (!try_module_get(dev->driver->owner)) अणु
		dev_err(dev, "%s: can't get owner\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* notअगरy PM core that घातer is now needed */
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		dev_err(dev, "%s: can't power on device\n", __func__);
		pm_runसमय_put_noidle(dev);
		module_put(dev->driver->owner);
		वापस ret;
	पूर्ण

	ret = 0;

	/* mark hwspinlock as used, should not fail */
	पंचांगp = radix_tree_tag_clear(&hwspinlock_tree, hwlock_to_id(hwlock),
							HWSPINLOCK_UNUSED);

	/* self-sanity check that should never fail */
	WARN_ON(पंचांगp != hwlock);

	वापस ret;
पूर्ण

/**
 * hwspin_lock_get_id() - retrieve id number of a given hwspinlock
 * @hwlock: a valid hwspinlock instance
 *
 * Returns the id number of a given @hwlock, or -EINVAL अगर @hwlock is invalid.
 */
पूर्णांक hwspin_lock_get_id(काष्ठा hwspinlock *hwlock)
अणु
	अगर (!hwlock) अणु
		pr_err("invalid hwlock\n");
		वापस -EINVAL;
	पूर्ण

	वापस hwlock_to_id(hwlock);
पूर्ण
EXPORT_SYMBOL_GPL(hwspin_lock_get_id);

/**
 * hwspin_lock_request() - request an hwspinlock
 *
 * This function should be called by users of the hwspinlock device,
 * in order to dynamically assign them an unused hwspinlock.
 * Usually the user of this lock will then have to communicate the lock's id
 * to the remote core beक्रमe it can be used क्रम synchronization (to get the
 * id of a given hwlock, use hwspin_lock_get_id()).
 *
 * Should be called from a process context (might sleep)
 *
 * Returns the address of the asचिन्हित hwspinlock, or शून्य on error
 */
काष्ठा hwspinlock *hwspin_lock_request(व्योम)
अणु
	काष्ठा hwspinlock *hwlock;
	पूर्णांक ret;

	mutex_lock(&hwspinlock_tree_lock);

	/* look क्रम an unused lock */
	ret = radix_tree_gang_lookup_tag(&hwspinlock_tree, (व्योम **)&hwlock,
						0, 1, HWSPINLOCK_UNUSED);
	अगर (ret == 0) अणु
		pr_warn("a free hwspinlock is not available\n");
		hwlock = शून्य;
		जाओ out;
	पूर्ण

	/* sanity check that should never fail */
	WARN_ON(ret > 1);

	/* mark as used and घातer up */
	ret = __hwspin_lock_request(hwlock);
	अगर (ret < 0)
		hwlock = शून्य;

out:
	mutex_unlock(&hwspinlock_tree_lock);
	वापस hwlock;
पूर्ण
EXPORT_SYMBOL_GPL(hwspin_lock_request);

/**
 * hwspin_lock_request_specअगरic() - request क्रम a specअगरic hwspinlock
 * @id: index of the specअगरic hwspinlock that is requested
 *
 * This function should be called by users of the hwspinlock module,
 * in order to assign them a specअगरic hwspinlock.
 * Usually early board code will be calling this function in order to
 * reserve specअगरic hwspinlock ids क्रम predefined purposes.
 *
 * Should be called from a process context (might sleep)
 *
 * Returns the address of the asचिन्हित hwspinlock, or शून्य on error
 */
काष्ठा hwspinlock *hwspin_lock_request_specअगरic(अचिन्हित पूर्णांक id)
अणु
	काष्ठा hwspinlock *hwlock;
	पूर्णांक ret;

	mutex_lock(&hwspinlock_tree_lock);

	/* make sure this hwspinlock exists */
	hwlock = radix_tree_lookup(&hwspinlock_tree, id);
	अगर (!hwlock) अणु
		pr_warn("hwspinlock %u does not exist\n", id);
		जाओ out;
	पूर्ण

	/* sanity check (this shouldn't happen) */
	WARN_ON(hwlock_to_id(hwlock) != id);

	/* make sure this hwspinlock is unused */
	ret = radix_tree_tag_get(&hwspinlock_tree, id, HWSPINLOCK_UNUSED);
	अगर (ret == 0) अणु
		pr_warn("hwspinlock %u is already in use\n", id);
		hwlock = शून्य;
		जाओ out;
	पूर्ण

	/* mark as used and घातer up */
	ret = __hwspin_lock_request(hwlock);
	अगर (ret < 0)
		hwlock = शून्य;

out:
	mutex_unlock(&hwspinlock_tree_lock);
	वापस hwlock;
पूर्ण
EXPORT_SYMBOL_GPL(hwspin_lock_request_specअगरic);

/**
 * hwspin_lock_मुक्त() - मुक्त a specअगरic hwspinlock
 * @hwlock: the specअगरic hwspinlock to मुक्त
 *
 * This function mark @hwlock as मुक्त again.
 * Should only be called with an @hwlock that was retrieved from
 * an earlier call to hwspin_lock_requestअणु_specअगरicपूर्ण.
 *
 * Should be called from a process context (might sleep)
 *
 * Returns 0 on success, or an appropriate error code on failure
 */
पूर्णांक hwspin_lock_मुक्त(काष्ठा hwspinlock *hwlock)
अणु
	काष्ठा device *dev;
	काष्ठा hwspinlock *पंचांगp;
	पूर्णांक ret;

	अगर (!hwlock) अणु
		pr_err("invalid hwlock\n");
		वापस -EINVAL;
	पूर्ण

	dev = hwlock->bank->dev;
	mutex_lock(&hwspinlock_tree_lock);

	/* make sure the hwspinlock is used */
	ret = radix_tree_tag_get(&hwspinlock_tree, hwlock_to_id(hwlock),
							HWSPINLOCK_UNUSED);
	अगर (ret == 1) अणु
		dev_err(dev, "%s: hwlock is already free\n", __func__);
		dump_stack();
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* notअगरy the underlying device that घातer is not needed */
	pm_runसमय_put(dev);

	/* mark this hwspinlock as available */
	पंचांगp = radix_tree_tag_set(&hwspinlock_tree, hwlock_to_id(hwlock),
							HWSPINLOCK_UNUSED);

	/* sanity check (this shouldn't happen) */
	WARN_ON(पंचांगp != hwlock);

	module_put(dev->driver->owner);

out:
	mutex_unlock(&hwspinlock_tree_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hwspin_lock_मुक्त);

अटल पूर्णांक devm_hwspin_lock_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा hwspinlock **hwlock = res;

	अगर (WARN_ON(!hwlock || !*hwlock))
		वापस 0;

	वापस *hwlock == data;
पूर्ण

अटल व्योम devm_hwspin_lock_release(काष्ठा device *dev, व्योम *res)
अणु
	hwspin_lock_मुक्त(*(काष्ठा hwspinlock **)res);
पूर्ण

/**
 * devm_hwspin_lock_मुक्त() - मुक्त a specअगरic hwspinlock क्रम a managed device
 * @dev: the device to मुक्त the specअगरic hwspinlock
 * @hwlock: the specअगरic hwspinlock to मुक्त
 *
 * This function mark @hwlock as मुक्त again.
 * Should only be called with an @hwlock that was retrieved from
 * an earlier call to hwspin_lock_requestअणु_specअगरicपूर्ण.
 *
 * Should be called from a process context (might sleep)
 *
 * Returns 0 on success, or an appropriate error code on failure
 */
पूर्णांक devm_hwspin_lock_मुक्त(काष्ठा device *dev, काष्ठा hwspinlock *hwlock)
अणु
	पूर्णांक ret;

	ret = devres_release(dev, devm_hwspin_lock_release,
			     devm_hwspin_lock_match, hwlock);
	WARN_ON(ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_hwspin_lock_मुक्त);

/**
 * devm_hwspin_lock_request() - request an hwspinlock क्रम a managed device
 * @dev: the device to request an hwspinlock
 *
 * This function should be called by users of the hwspinlock device,
 * in order to dynamically assign them an unused hwspinlock.
 * Usually the user of this lock will then have to communicate the lock's id
 * to the remote core beक्रमe it can be used क्रम synchronization (to get the
 * id of a given hwlock, use hwspin_lock_get_id()).
 *
 * Should be called from a process context (might sleep)
 *
 * Returns the address of the asचिन्हित hwspinlock, or शून्य on error
 */
काष्ठा hwspinlock *devm_hwspin_lock_request(काष्ठा device *dev)
अणु
	काष्ठा hwspinlock **ptr, *hwlock;

	ptr = devres_alloc(devm_hwspin_lock_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस शून्य;

	hwlock = hwspin_lock_request();
	अगर (hwlock) अणु
		*ptr = hwlock;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस hwlock;
पूर्ण
EXPORT_SYMBOL_GPL(devm_hwspin_lock_request);

/**
 * devm_hwspin_lock_request_specअगरic() - request क्रम a specअगरic hwspinlock क्रम
 *					 a managed device
 * @dev: the device to request the specअगरic hwspinlock
 * @id: index of the specअगरic hwspinlock that is requested
 *
 * This function should be called by users of the hwspinlock module,
 * in order to assign them a specअगरic hwspinlock.
 * Usually early board code will be calling this function in order to
 * reserve specअगरic hwspinlock ids क्रम predefined purposes.
 *
 * Should be called from a process context (might sleep)
 *
 * Returns the address of the asचिन्हित hwspinlock, or शून्य on error
 */
काष्ठा hwspinlock *devm_hwspin_lock_request_specअगरic(काष्ठा device *dev,
						     अचिन्हित पूर्णांक id)
अणु
	काष्ठा hwspinlock **ptr, *hwlock;

	ptr = devres_alloc(devm_hwspin_lock_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस शून्य;

	hwlock = hwspin_lock_request_specअगरic(id);
	अगर (hwlock) अणु
		*ptr = hwlock;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस hwlock;
पूर्ण
EXPORT_SYMBOL_GPL(devm_hwspin_lock_request_specअगरic);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Hardware spinlock interface");
MODULE_AUTHOR("Ohad Ben-Cohen <ohad@wizery.com>");
