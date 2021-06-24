<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Hardware spinlocks पूर्णांकernal header
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com
 *
 * Contact: Ohad Ben-Cohen <ohad@wizery.com>
 */

#अगर_अघोषित __HWSPINLOCK_HWSPINLOCK_H
#घोषणा __HWSPINLOCK_HWSPINLOCK_H

#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>

काष्ठा hwspinlock_device;

/**
 * काष्ठा hwspinlock_ops - platक्रमm-specअगरic hwspinlock handlers
 *
 * @trylock: make a single attempt to take the lock. वापसs 0 on
 *	     failure and true on success. may _not_ sleep.
 * @unlock:  release the lock. always succeed. may _not_ sleep.
 * @relax:   optional, platक्रमm-specअगरic relax handler, called by hwspinlock
 *	     core जबतक spinning on a lock, between two successive
 *	     invocations of @trylock. may _not_ sleep.
 */
काष्ठा hwspinlock_ops अणु
	पूर्णांक (*trylock)(काष्ठा hwspinlock *lock);
	व्योम (*unlock)(काष्ठा hwspinlock *lock);
	व्योम (*relax)(काष्ठा hwspinlock *lock);
पूर्ण;

/**
 * काष्ठा hwspinlock - this काष्ठा represents a single hwspinlock instance
 * @bank: the hwspinlock_device काष्ठाure which owns this lock
 * @lock: initialized and used by hwspinlock core
 * @priv: निजी data, owned by the underlying platक्रमm-specअगरic hwspinlock drv
 */
काष्ठा hwspinlock अणु
	काष्ठा hwspinlock_device *bank;
	spinlock_t lock;
	व्योम *priv;
पूर्ण;

/**
 * काष्ठा hwspinlock_device - a device which usually spans numerous hwspinlocks
 * @dev: underlying device, will be used to invoke runसमय PM api
 * @ops: platक्रमm-specअगरic hwspinlock handlers
 * @base_id: id index of the first lock in this device
 * @num_locks: number of locks in this device
 * @lock: dynamically allocated array of 'struct hwspinlock'
 */
काष्ठा hwspinlock_device अणु
	काष्ठा device *dev;
	स्थिर काष्ठा hwspinlock_ops *ops;
	पूर्णांक base_id;
	पूर्णांक num_locks;
	काष्ठा hwspinlock lock[];
पूर्ण;

अटल अंतरभूत पूर्णांक hwlock_to_id(काष्ठा hwspinlock *hwlock)
अणु
	पूर्णांक local_id = hwlock - &hwlock->bank->lock[0];

	वापस hwlock->bank->base_id + local_id;
पूर्ण

#पूर्ण_अगर /* __HWSPINLOCK_HWSPINLOCK_H */
