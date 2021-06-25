<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Hardware spinlock खुला header
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com
 *
 * Contact: Ohad Ben-Cohen <ohad@wizery.com>
 */

#अगर_अघोषित __LINUX_HWSPINLOCK_H
#घोषणा __LINUX_HWSPINLOCK_H

#समावेश <linux/err.h>
#समावेश <linux/sched.h>

/* hwspinlock mode argument */
#घोषणा HWLOCK_IRQSTATE		0x01 /* Disable पूर्णांकerrupts, save state */
#घोषणा HWLOCK_IRQ		0x02 /* Disable पूर्णांकerrupts, करोn't save state */
#घोषणा HWLOCK_RAW		0x03
#घोषणा HWLOCK_IN_ATOMIC	0x04 /* Called जबतक in atomic context */

काष्ठा device;
काष्ठा device_node;
काष्ठा hwspinlock;
काष्ठा hwspinlock_device;
काष्ठा hwspinlock_ops;

/**
 * काष्ठा hwspinlock_pdata - platक्रमm data क्रम hwspinlock drivers
 * @base_id: base id क्रम this hwspinlock device
 *
 * hwspinlock devices provide प्रणाली-wide hardware locks that are used
 * by remote processors that have no other way to achieve synchronization.
 *
 * To achieve that, each physical lock must have a प्रणाली-wide id number
 * that is agreed upon, otherwise remote processors can't possibly assume
 * they're using the same hardware lock.
 *
 * Usually boards have a single hwspinlock device, which provides several
 * hwspinlocks, and in this हाल, they can be trivially numbered 0 to
 * (num-of-locks - 1).
 *
 * In हाल boards have several hwspinlocks devices, a dअगरferent base id
 * should be used क्रम each hwspinlock device (they can't all use 0 as
 * a starting id!).
 *
 * This platक्रमm data काष्ठाure should be used to provide the base id
 * क्रम each device (which is trivially 0 when only a single hwspinlock
 * device exists). It can be shared between dअगरferent platक्रमms, hence
 * its location.
 */
काष्ठा hwspinlock_pdata अणु
	पूर्णांक base_id;
पूर्ण;

#अगर_घोषित CONFIG_HWSPINLOCK

पूर्णांक hwspin_lock_रेजिस्टर(काष्ठा hwspinlock_device *bank, काष्ठा device *dev,
		स्थिर काष्ठा hwspinlock_ops *ops, पूर्णांक base_id, पूर्णांक num_locks);
पूर्णांक hwspin_lock_unरेजिस्टर(काष्ठा hwspinlock_device *bank);
काष्ठा hwspinlock *hwspin_lock_request(व्योम);
काष्ठा hwspinlock *hwspin_lock_request_specअगरic(अचिन्हित पूर्णांक id);
पूर्णांक hwspin_lock_मुक्त(काष्ठा hwspinlock *hwlock);
पूर्णांक of_hwspin_lock_get_id(काष्ठा device_node *np, पूर्णांक index);
पूर्णांक hwspin_lock_get_id(काष्ठा hwspinlock *hwlock);
पूर्णांक __hwspin_lock_समयout(काष्ठा hwspinlock *, अचिन्हित पूर्णांक, पूर्णांक,
							अचिन्हित दीर्घ *);
पूर्णांक __hwspin_trylock(काष्ठा hwspinlock *, पूर्णांक, अचिन्हित दीर्घ *);
व्योम __hwspin_unlock(काष्ठा hwspinlock *, पूर्णांक, अचिन्हित दीर्घ *);
पूर्णांक of_hwspin_lock_get_id_byname(काष्ठा device_node *np, स्थिर अक्षर *name);
पूर्णांक devm_hwspin_lock_मुक्त(काष्ठा device *dev, काष्ठा hwspinlock *hwlock);
काष्ठा hwspinlock *devm_hwspin_lock_request(काष्ठा device *dev);
काष्ठा hwspinlock *devm_hwspin_lock_request_specअगरic(काष्ठा device *dev,
						     अचिन्हित पूर्णांक id);
पूर्णांक devm_hwspin_lock_unरेजिस्टर(काष्ठा device *dev,
				काष्ठा hwspinlock_device *bank);
पूर्णांक devm_hwspin_lock_रेजिस्टर(काष्ठा device *dev,
			      काष्ठा hwspinlock_device *bank,
			      स्थिर काष्ठा hwspinlock_ops *ops,
			      पूर्णांक base_id, पूर्णांक num_locks);

#अन्यथा /* !CONFIG_HWSPINLOCK */

/*
 * We करोn't want these functions to fail अगर CONFIG_HWSPINLOCK is not
 * enabled. We prefer to silently succeed in this हाल, and let the
 * code path get compiled away. This way, अगर CONFIG_HWSPINLOCK is not
 * required on a given setup, users will still work.
 *
 * The only exception is hwspin_lock_रेजिस्टर/hwspin_lock_unरेजिस्टर, with which
 * we _करो_ want users to fail (no poपूर्णांक in रेजिस्टरing hwspinlock instances अगर
 * the framework is not available).
 *
 * Note: ERR_PTR(-ENODEV) will still be considered a success क्रम शून्य-checking
 * users. Others, which care, can still check this with IS_ERR.
 */
अटल अंतरभूत काष्ठा hwspinlock *hwspin_lock_request(व्योम)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा hwspinlock *hwspin_lock_request_specअगरic(अचिन्हित पूर्णांक id)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत पूर्णांक hwspin_lock_मुक्त(काष्ठा hwspinlock *hwlock)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक __hwspin_lock_समयout(काष्ठा hwspinlock *hwlock, अचिन्हित पूर्णांक to,
					पूर्णांक mode, अचिन्हित दीर्घ *flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक __hwspin_trylock(काष्ठा hwspinlock *hwlock, पूर्णांक mode, अचिन्हित दीर्घ *flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
व्योम __hwspin_unlock(काष्ठा hwspinlock *hwlock, पूर्णांक mode, अचिन्हित दीर्घ *flags)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक of_hwspin_lock_get_id(काष्ठा device_node *np, पूर्णांक index)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hwspin_lock_get_id(काष्ठा hwspinlock *hwlock)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक of_hwspin_lock_get_id_byname(काष्ठा device_node *np, स्थिर अक्षर *name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक devm_hwspin_lock_मुक्त(काष्ठा device *dev, काष्ठा hwspinlock *hwlock)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा hwspinlock *devm_hwspin_lock_request(काष्ठा device *dev)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत
काष्ठा hwspinlock *devm_hwspin_lock_request_specअगरic(काष्ठा device *dev,
						     अचिन्हित पूर्णांक id)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

#पूर्ण_अगर /* !CONFIG_HWSPINLOCK */

/**
 * hwspin_trylock_irqsave() - try to lock an hwspinlock, disable पूर्णांकerrupts
 * @hwlock: an hwspinlock which we want to trylock
 * @flags: a poपूर्णांकer to where the caller's पूर्णांकerrupt state will be saved at
 *
 * This function attempts to lock the underlying hwspinlock, and will
 * immediately fail अगर the hwspinlock is alपढ़ोy locked.
 *
 * Upon a successful वापस from this function, preemption and local
 * पूर्णांकerrupts are disabled (previous पूर्णांकerrupts state is saved at @flags),
 * so the caller must not sleep, and is advised to release the hwspinlock
 * as soon as possible.
 *
 * Returns 0 अगर we successfully locked the hwspinlock, -EBUSY अगर
 * the hwspinlock was alपढ़ोy taken, and -EINVAL अगर @hwlock is invalid.
 */
अटल अंतरभूत
पूर्णांक hwspin_trylock_irqsave(काष्ठा hwspinlock *hwlock, अचिन्हित दीर्घ *flags)
अणु
	वापस __hwspin_trylock(hwlock, HWLOCK_IRQSTATE, flags);
पूर्ण

/**
 * hwspin_trylock_irq() - try to lock an hwspinlock, disable पूर्णांकerrupts
 * @hwlock: an hwspinlock which we want to trylock
 *
 * This function attempts to lock the underlying hwspinlock, and will
 * immediately fail अगर the hwspinlock is alपढ़ोy locked.
 *
 * Upon a successful वापस from this function, preemption and local
 * पूर्णांकerrupts are disabled, so the caller must not sleep, and is advised
 * to release the hwspinlock as soon as possible.
 *
 * Returns 0 अगर we successfully locked the hwspinlock, -EBUSY अगर
 * the hwspinlock was alपढ़ोy taken, and -EINVAL अगर @hwlock is invalid.
 */
अटल अंतरभूत पूर्णांक hwspin_trylock_irq(काष्ठा hwspinlock *hwlock)
अणु
	वापस __hwspin_trylock(hwlock, HWLOCK_IRQ, शून्य);
पूर्ण

/**
 * hwspin_trylock_raw() - attempt to lock a specअगरic hwspinlock
 * @hwlock: an hwspinlock which we want to trylock
 *
 * This function attempts to lock an hwspinlock, and will immediately fail
 * अगर the hwspinlock is alपढ़ोy taken.
 *
 * Caution: User must protect the routine of getting hardware lock with mutex
 * or spinlock to aव्योम dead-lock, that will let user can करो some समय-consuming
 * or sleepable operations under the hardware lock.
 *
 * Returns 0 अगर we successfully locked the hwspinlock, -EBUSY अगर
 * the hwspinlock was alपढ़ोy taken, and -EINVAL अगर @hwlock is invalid.
 */
अटल अंतरभूत पूर्णांक hwspin_trylock_raw(काष्ठा hwspinlock *hwlock)
अणु
	वापस __hwspin_trylock(hwlock, HWLOCK_RAW, शून्य);
पूर्ण

/**
 * hwspin_trylock_in_atomic() - attempt to lock a specअगरic hwspinlock
 * @hwlock: an hwspinlock which we want to trylock
 *
 * This function attempts to lock an hwspinlock, and will immediately fail
 * अगर the hwspinlock is alपढ़ोy taken.
 *
 * This function shall be called only from an atomic context.
 *
 * Returns 0 अगर we successfully locked the hwspinlock, -EBUSY अगर
 * the hwspinlock was alपढ़ोy taken, and -EINVAL अगर @hwlock is invalid.
 */
अटल अंतरभूत पूर्णांक hwspin_trylock_in_atomic(काष्ठा hwspinlock *hwlock)
अणु
	वापस __hwspin_trylock(hwlock, HWLOCK_IN_ATOMIC, शून्य);
पूर्ण

/**
 * hwspin_trylock() - attempt to lock a specअगरic hwspinlock
 * @hwlock: an hwspinlock which we want to trylock
 *
 * This function attempts to lock an hwspinlock, and will immediately fail
 * अगर the hwspinlock is alपढ़ोy taken.
 *
 * Upon a successful वापस from this function, preemption is disabled,
 * so the caller must not sleep, and is advised to release the hwspinlock
 * as soon as possible. This is required in order to minimize remote cores
 * polling on the hardware पूर्णांकerconnect.
 *
 * Returns 0 अगर we successfully locked the hwspinlock, -EBUSY अगर
 * the hwspinlock was alपढ़ोy taken, and -EINVAL अगर @hwlock is invalid.
 */
अटल अंतरभूत पूर्णांक hwspin_trylock(काष्ठा hwspinlock *hwlock)
अणु
	वापस __hwspin_trylock(hwlock, 0, शून्य);
पूर्ण

/**
 * hwspin_lock_समयout_irqsave() - lock hwspinlock, with समयout, disable irqs
 * @hwlock: the hwspinlock to be locked
 * @to: समयout value in msecs
 * @flags: a poपूर्णांकer to where the caller's पूर्णांकerrupt state will be saved at
 *
 * This function locks the underlying @hwlock. If the @hwlock
 * is alपढ़ोy taken, the function will busy loop रुकोing क्रम it to
 * be released, but give up when @समयout msecs have elapsed.
 *
 * Upon a successful वापस from this function, preemption and local पूर्णांकerrupts
 * are disabled (plus previous पूर्णांकerrupt state is saved), so the caller must
 * not sleep, and is advised to release the hwspinlock as soon as possible.
 *
 * Returns 0 when the @hwlock was successfully taken, and an appropriate
 * error code otherwise (most notably an -ETIMEDOUT अगर the @hwlock is still
 * busy after @समयout msecs). The function will never sleep.
 */
अटल अंतरभूत पूर्णांक hwspin_lock_समयout_irqsave(काष्ठा hwspinlock *hwlock,
				अचिन्हित पूर्णांक to, अचिन्हित दीर्घ *flags)
अणु
	वापस __hwspin_lock_समयout(hwlock, to, HWLOCK_IRQSTATE, flags);
पूर्ण

/**
 * hwspin_lock_समयout_irq() - lock hwspinlock, with समयout, disable irqs
 * @hwlock: the hwspinlock to be locked
 * @to: समयout value in msecs
 *
 * This function locks the underlying @hwlock. If the @hwlock
 * is alपढ़ोy taken, the function will busy loop रुकोing क्रम it to
 * be released, but give up when @समयout msecs have elapsed.
 *
 * Upon a successful वापस from this function, preemption and local पूर्णांकerrupts
 * are disabled so the caller must not sleep, and is advised to release the
 * hwspinlock as soon as possible.
 *
 * Returns 0 when the @hwlock was successfully taken, and an appropriate
 * error code otherwise (most notably an -ETIMEDOUT अगर the @hwlock is still
 * busy after @समयout msecs). The function will never sleep.
 */
अटल अंतरभूत
पूर्णांक hwspin_lock_समयout_irq(काष्ठा hwspinlock *hwlock, अचिन्हित पूर्णांक to)
अणु
	वापस __hwspin_lock_समयout(hwlock, to, HWLOCK_IRQ, शून्य);
पूर्ण

/**
 * hwspin_lock_समयout_raw() - lock an hwspinlock with समयout limit
 * @hwlock: the hwspinlock to be locked
 * @to: समयout value in msecs
 *
 * This function locks the underlying @hwlock. If the @hwlock
 * is alपढ़ोy taken, the function will busy loop रुकोing क्रम it to
 * be released, but give up when @समयout msecs have elapsed.
 *
 * Caution: User must protect the routine of getting hardware lock with mutex
 * or spinlock to aव्योम dead-lock, that will let user can करो some समय-consuming
 * or sleepable operations under the hardware lock.
 *
 * Returns 0 when the @hwlock was successfully taken, and an appropriate
 * error code otherwise (most notably an -ETIMEDOUT अगर the @hwlock is still
 * busy after @समयout msecs). The function will never sleep.
 */
अटल अंतरभूत
पूर्णांक hwspin_lock_समयout_raw(काष्ठा hwspinlock *hwlock, अचिन्हित पूर्णांक to)
अणु
	वापस __hwspin_lock_समयout(hwlock, to, HWLOCK_RAW, शून्य);
पूर्ण

/**
 * hwspin_lock_समयout_in_atomic() - lock an hwspinlock with समयout limit
 * @hwlock: the hwspinlock to be locked
 * @to: समयout value in msecs
 *
 * This function locks the underlying @hwlock. If the @hwlock
 * is alपढ़ोy taken, the function will busy loop रुकोing क्रम it to
 * be released, but give up when @समयout msecs have elapsed.
 *
 * This function shall be called only from an atomic context and the समयout
 * value shall not exceed a few msecs.
 *
 * Returns 0 when the @hwlock was successfully taken, and an appropriate
 * error code otherwise (most notably an -ETIMEDOUT अगर the @hwlock is still
 * busy after @समयout msecs). The function will never sleep.
 */
अटल अंतरभूत
पूर्णांक hwspin_lock_समयout_in_atomic(काष्ठा hwspinlock *hwlock, अचिन्हित पूर्णांक to)
अणु
	वापस __hwspin_lock_समयout(hwlock, to, HWLOCK_IN_ATOMIC, शून्य);
पूर्ण

/**
 * hwspin_lock_समयout() - lock an hwspinlock with समयout limit
 * @hwlock: the hwspinlock to be locked
 * @to: समयout value in msecs
 *
 * This function locks the underlying @hwlock. If the @hwlock
 * is alपढ़ोy taken, the function will busy loop रुकोing क्रम it to
 * be released, but give up when @समयout msecs have elapsed.
 *
 * Upon a successful वापस from this function, preemption is disabled
 * so the caller must not sleep, and is advised to release the hwspinlock
 * as soon as possible.
 * This is required in order to minimize remote cores polling on the
 * hardware पूर्णांकerconnect.
 *
 * Returns 0 when the @hwlock was successfully taken, and an appropriate
 * error code otherwise (most notably an -ETIMEDOUT अगर the @hwlock is still
 * busy after @समयout msecs). The function will never sleep.
 */
अटल अंतरभूत
पूर्णांक hwspin_lock_समयout(काष्ठा hwspinlock *hwlock, अचिन्हित पूर्णांक to)
अणु
	वापस __hwspin_lock_समयout(hwlock, to, 0, शून्य);
पूर्ण

/**
 * hwspin_unlock_irqrestore() - unlock hwspinlock, restore irq state
 * @hwlock: a previously-acquired hwspinlock which we want to unlock
 * @flags: previous caller's पूर्णांकerrupt state to restore
 *
 * This function will unlock a specअगरic hwspinlock, enable preemption and
 * restore the previous state of the local पूर्णांकerrupts. It should be used
 * to unकरो, e.g., hwspin_trylock_irqsave().
 *
 * @hwlock must be alपढ़ोy locked beक्रमe calling this function: it is a bug
 * to call unlock on a @hwlock that is alपढ़ोy unlocked.
 */
अटल अंतरभूत व्योम hwspin_unlock_irqrestore(काष्ठा hwspinlock *hwlock,
							अचिन्हित दीर्घ *flags)
अणु
	__hwspin_unlock(hwlock, HWLOCK_IRQSTATE, flags);
पूर्ण

/**
 * hwspin_unlock_irq() - unlock hwspinlock, enable पूर्णांकerrupts
 * @hwlock: a previously-acquired hwspinlock which we want to unlock
 *
 * This function will unlock a specअगरic hwspinlock, enable preemption and
 * enable local पूर्णांकerrupts. Should be used to unकरो hwspin_lock_irq().
 *
 * @hwlock must be alपढ़ोy locked (e.g. by hwspin_trylock_irq()) beक्रमe
 * calling this function: it is a bug to call unlock on a @hwlock that is
 * alपढ़ोy unlocked.
 */
अटल अंतरभूत व्योम hwspin_unlock_irq(काष्ठा hwspinlock *hwlock)
अणु
	__hwspin_unlock(hwlock, HWLOCK_IRQ, शून्य);
पूर्ण

/**
 * hwspin_unlock_raw() - unlock hwspinlock
 * @hwlock: a previously-acquired hwspinlock which we want to unlock
 *
 * This function will unlock a specअगरic hwspinlock.
 *
 * @hwlock must be alपढ़ोy locked (e.g. by hwspin_trylock()) beक्रमe calling
 * this function: it is a bug to call unlock on a @hwlock that is alपढ़ोy
 * unlocked.
 */
अटल अंतरभूत व्योम hwspin_unlock_raw(काष्ठा hwspinlock *hwlock)
अणु
	__hwspin_unlock(hwlock, HWLOCK_RAW, शून्य);
पूर्ण

/**
 * hwspin_unlock_in_atomic() - unlock hwspinlock
 * @hwlock: a previously-acquired hwspinlock which we want to unlock
 *
 * This function will unlock a specअगरic hwspinlock.
 *
 * @hwlock must be alपढ़ोy locked (e.g. by hwspin_trylock()) beक्रमe calling
 * this function: it is a bug to call unlock on a @hwlock that is alपढ़ोy
 * unlocked.
 */
अटल अंतरभूत व्योम hwspin_unlock_in_atomic(काष्ठा hwspinlock *hwlock)
अणु
	__hwspin_unlock(hwlock, HWLOCK_IN_ATOMIC, शून्य);
पूर्ण

/**
 * hwspin_unlock() - unlock hwspinlock
 * @hwlock: a previously-acquired hwspinlock which we want to unlock
 *
 * This function will unlock a specअगरic hwspinlock and enable preemption
 * back.
 *
 * @hwlock must be alपढ़ोy locked (e.g. by hwspin_trylock()) beक्रमe calling
 * this function: it is a bug to call unlock on a @hwlock that is alपढ़ोy
 * unlocked.
 */
अटल अंतरभूत व्योम hwspin_unlock(काष्ठा hwspinlock *hwlock)
अणु
	__hwspin_unlock(hwlock, 0, शून्य);
पूर्ण

#पूर्ण_अगर /* __LINUX_HWSPINLOCK_H */
