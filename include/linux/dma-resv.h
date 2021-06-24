<शैली गुरु>
/*
 * Header file क्रम reservations क्रम dma-buf and tपंचांग
 *
 * Copyright(C) 2011 Linaro Limited. All rights reserved.
 * Copyright (C) 2012-2013 Canonical Ltd
 * Copyright (C) 2012 Texas Instruments
 *
 * Authors:
 * Rob Clark <robdclark@gmail.com>
 * Maarten Lankhorst <maarten.lankhorst@canonical.com>
 * Thomas Hellstrom <thellstrom-at-vmware-करोt-com>
 *
 * Based on bo.c which bears the following copyright notice,
 * but is dual licensed:
 *
 * Copyright (c) 2006-2009 VMware, Inc., Palo Alto, CA., USA
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#अगर_अघोषित _LINUX_RESERVATION_H
#घोषणा _LINUX_RESERVATION_H

#समावेश <linux/ww_mutex.h>
#समावेश <linux/dma-fence.h>
#समावेश <linux/slab.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/rcupdate.h>

बाह्य काष्ठा ww_class reservation_ww_class;

/**
 * काष्ठा dma_resv_list - a list of shared fences
 * @rcu: क्रम पूर्णांकernal use
 * @shared_count: table of shared fences
 * @shared_max: क्रम growing shared fence table
 * @shared: shared fence table
 */
काष्ठा dma_resv_list अणु
	काष्ठा rcu_head rcu;
	u32 shared_count, shared_max;
	काष्ठा dma_fence __rcu *shared[];
पूर्ण;

/**
 * काष्ठा dma_resv - a reservation object manages fences क्रम a buffer
 * @lock: update side lock
 * @seq: sequence count क्रम managing RCU पढ़ो-side synchronization
 * @fence_excl: the exclusive fence, अगर there is one currently
 * @fence: list of current shared fences
 */
काष्ठा dma_resv अणु
	काष्ठा ww_mutex lock;
	seqcount_ww_mutex_t seq;

	काष्ठा dma_fence __rcu *fence_excl;
	काष्ठा dma_resv_list __rcu *fence;
पूर्ण;

#घोषणा dma_resv_held(obj) lockdep_is_held(&(obj)->lock.base)
#घोषणा dma_resv_निश्चित_held(obj) lockdep_निश्चित_held(&(obj)->lock.base)

/**
 * dma_resv_get_list - get the reservation object's
 * shared fence list, with update-side lock held
 * @obj: the reservation object
 *
 * Returns the shared fence list.  Does NOT take references to
 * the fence.  The obj->lock must be held.
 */
अटल अंतरभूत काष्ठा dma_resv_list *dma_resv_get_list(काष्ठा dma_resv *obj)
अणु
	वापस rcu_dereference_रक्षित(obj->fence,
					 dma_resv_held(obj));
पूर्ण

/**
 * dma_resv_lock - lock the reservation object
 * @obj: the reservation object
 * @ctx: the locking context
 *
 * Locks the reservation object क्रम exclusive access and modअगरication. Note,
 * that the lock is only against other ग_लिखोrs, पढ़ोers will run concurrently
 * with a ग_लिखोr under RCU. The seqlock is used to notअगरy पढ़ोers अगर they
 * overlap with a ग_लिखोr.
 *
 * As the reservation object may be locked by multiple parties in an
 * undefined order, a #ww_acquire_ctx is passed to unwind अगर a cycle
 * is detected. See ww_mutex_lock() and ww_acquire_init(). A reservation
 * object may be locked by itself by passing शून्य as @ctx.
 */
अटल अंतरभूत पूर्णांक dma_resv_lock(काष्ठा dma_resv *obj,
				काष्ठा ww_acquire_ctx *ctx)
अणु
	वापस ww_mutex_lock(&obj->lock, ctx);
पूर्ण

/**
 * dma_resv_lock_पूर्णांकerruptible - lock the reservation object
 * @obj: the reservation object
 * @ctx: the locking context
 *
 * Locks the reservation object पूर्णांकerruptible क्रम exclusive access and
 * modअगरication. Note, that the lock is only against other ग_लिखोrs, पढ़ोers
 * will run concurrently with a ग_लिखोr under RCU. The seqlock is used to
 * notअगरy पढ़ोers अगर they overlap with a ग_लिखोr.
 *
 * As the reservation object may be locked by multiple parties in an
 * undefined order, a #ww_acquire_ctx is passed to unwind अगर a cycle
 * is detected. See ww_mutex_lock() and ww_acquire_init(). A reservation
 * object may be locked by itself by passing शून्य as @ctx.
 */
अटल अंतरभूत पूर्णांक dma_resv_lock_पूर्णांकerruptible(काष्ठा dma_resv *obj,
					      काष्ठा ww_acquire_ctx *ctx)
अणु
	वापस ww_mutex_lock_पूर्णांकerruptible(&obj->lock, ctx);
पूर्ण

/**
 * dma_resv_lock_slow - slowpath lock the reservation object
 * @obj: the reservation object
 * @ctx: the locking context
 *
 * Acquires the reservation object after a die हाल. This function
 * will sleep until the lock becomes available. See dma_resv_lock() as
 * well.
 */
अटल अंतरभूत व्योम dma_resv_lock_slow(काष्ठा dma_resv *obj,
				      काष्ठा ww_acquire_ctx *ctx)
अणु
	ww_mutex_lock_slow(&obj->lock, ctx);
पूर्ण

/**
 * dma_resv_lock_slow_पूर्णांकerruptible - slowpath lock the reservation
 * object, पूर्णांकerruptible
 * @obj: the reservation object
 * @ctx: the locking context
 *
 * Acquires the reservation object पूर्णांकerruptible after a die हाल. This function
 * will sleep until the lock becomes available. See
 * dma_resv_lock_पूर्णांकerruptible() as well.
 */
अटल अंतरभूत पूर्णांक dma_resv_lock_slow_पूर्णांकerruptible(काष्ठा dma_resv *obj,
						   काष्ठा ww_acquire_ctx *ctx)
अणु
	वापस ww_mutex_lock_slow_पूर्णांकerruptible(&obj->lock, ctx);
पूर्ण

/**
 * dma_resv_trylock - trylock the reservation object
 * @obj: the reservation object
 *
 * Tries to lock the reservation object क्रम exclusive access and modअगरication.
 * Note, that the lock is only against other ग_लिखोrs, पढ़ोers will run
 * concurrently with a ग_लिखोr under RCU. The seqlock is used to notअगरy पढ़ोers
 * अगर they overlap with a ग_लिखोr.
 *
 * Also note that since no context is provided, no deadlock protection is
 * possible.
 *
 * Returns true अगर the lock was acquired, false otherwise.
 */
अटल अंतरभूत bool __must_check dma_resv_trylock(काष्ठा dma_resv *obj)
अणु
	वापस ww_mutex_trylock(&obj->lock);
पूर्ण

/**
 * dma_resv_is_locked - is the reservation object locked
 * @obj: the reservation object
 *
 * Returns true अगर the mutex is locked, false अगर unlocked.
 */
अटल अंतरभूत bool dma_resv_is_locked(काष्ठा dma_resv *obj)
अणु
	वापस ww_mutex_is_locked(&obj->lock);
पूर्ण

/**
 * dma_resv_locking_ctx - वापसs the context used to lock the object
 * @obj: the reservation object
 *
 * Returns the context used to lock a reservation object or शून्य अगर no context
 * was used or the object is not locked at all.
 */
अटल अंतरभूत काष्ठा ww_acquire_ctx *dma_resv_locking_ctx(काष्ठा dma_resv *obj)
अणु
	वापस READ_ONCE(obj->lock.ctx);
पूर्ण

/**
 * dma_resv_unlock - unlock the reservation object
 * @obj: the reservation object
 *
 * Unlocks the reservation object following exclusive access.
 */
अटल अंतरभूत व्योम dma_resv_unlock(काष्ठा dma_resv *obj)
अणु
#अगर_घोषित CONFIG_DEBUG_MUTEXES
	/* Test shared fence slot reservation */
	अगर (rcu_access_poपूर्णांकer(obj->fence)) अणु
		काष्ठा dma_resv_list *fence = dma_resv_get_list(obj);

		fence->shared_max = fence->shared_count;
	पूर्ण
#पूर्ण_अगर
	ww_mutex_unlock(&obj->lock);
पूर्ण

/**
 * dma_resv_get_excl - get the reservation object's
 * exclusive fence, with update-side lock held
 * @obj: the reservation object
 *
 * Returns the exclusive fence (अगर any).  Does NOT take a
 * reference. Writers must hold obj->lock, पढ़ोers may only
 * hold a RCU पढ़ो side lock.
 *
 * RETURNS
 * The exclusive fence or शून्य
 */
अटल अंतरभूत काष्ठा dma_fence *
dma_resv_get_excl(काष्ठा dma_resv *obj)
अणु
	वापस rcu_dereference_रक्षित(obj->fence_excl,
					 dma_resv_held(obj));
पूर्ण

/**
 * dma_resv_get_excl_rcu - get the reservation object's
 * exclusive fence, without lock held.
 * @obj: the reservation object
 *
 * If there is an exclusive fence, this atomically increments it's
 * reference count and वापसs it.
 *
 * RETURNS
 * The exclusive fence or शून्य अगर none
 */
अटल अंतरभूत काष्ठा dma_fence *
dma_resv_get_excl_rcu(काष्ठा dma_resv *obj)
अणु
	काष्ठा dma_fence *fence;

	अगर (!rcu_access_poपूर्णांकer(obj->fence_excl))
		वापस शून्य;

	rcu_पढ़ो_lock();
	fence = dma_fence_get_rcu_safe(&obj->fence_excl);
	rcu_पढ़ो_unlock();

	वापस fence;
पूर्ण

व्योम dma_resv_init(काष्ठा dma_resv *obj);
व्योम dma_resv_fini(काष्ठा dma_resv *obj);
पूर्णांक dma_resv_reserve_shared(काष्ठा dma_resv *obj, अचिन्हित पूर्णांक num_fences);
व्योम dma_resv_add_shared_fence(काष्ठा dma_resv *obj, काष्ठा dma_fence *fence);

व्योम dma_resv_add_excl_fence(काष्ठा dma_resv *obj, काष्ठा dma_fence *fence);

पूर्णांक dma_resv_get_fences_rcu(काष्ठा dma_resv *obj,
			    काष्ठा dma_fence **pfence_excl,
			    अचिन्हित *pshared_count,
			    काष्ठा dma_fence ***pshared);

पूर्णांक dma_resv_copy_fences(काष्ठा dma_resv *dst, काष्ठा dma_resv *src);

दीर्घ dma_resv_रुको_समयout_rcu(काष्ठा dma_resv *obj, bool रुको_all, bool पूर्णांकr,
			       अचिन्हित दीर्घ समयout);

bool dma_resv_test_संकेतed_rcu(काष्ठा dma_resv *obj, bool test_all);

#पूर्ण_अगर /* _LINUX_RESERVATION_H */
