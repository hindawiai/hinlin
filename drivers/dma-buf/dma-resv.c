<शैली गुरु>
/*
 * Copyright (C) 2012-2014 Canonical Ltd (Maarten Lankhorst)
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
 *
 **************************************************************************/
/*
 * Authors: Thomas Hellstrom <thellstrom-at-vmware-करोt-com>
 */

#समावेश <linux/dma-resv.h>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/mmu_notअगरier.h>

/**
 * DOC: Reservation Object Overview
 *
 * The reservation object provides a mechanism to manage shared and
 * exclusive fences associated with a buffer.  A reservation object
 * can have attached one exclusive fence (normally associated with
 * ग_लिखो operations) or N shared fences (पढ़ो operations).  The RCU
 * mechanism is used to protect पढ़ो access to fences from locked
 * ग_लिखो-side updates.
 */

DEFINE_WD_CLASS(reservation_ww_class);
EXPORT_SYMBOL(reservation_ww_class);

/**
 * dma_resv_list_alloc - allocate fence list
 * @shared_max: number of fences we need space क्रम
 *
 * Allocate a new dma_resv_list and make sure to correctly initialize
 * shared_max.
 */
अटल काष्ठा dma_resv_list *dma_resv_list_alloc(अचिन्हित पूर्णांक shared_max)
अणु
	काष्ठा dma_resv_list *list;

	list = kदो_स्मृति(काष्ठा_size(list, shared, shared_max), GFP_KERNEL);
	अगर (!list)
		वापस शून्य;

	list->shared_max = (ksize(list) - दुरत्व(typeof(*list), shared)) /
		माप(*list->shared);

	वापस list;
पूर्ण

/**
 * dma_resv_list_मुक्त - मुक्त fence list
 * @list: list to मुक्त
 *
 * Free a dma_resv_list and make sure to drop all references.
 */
अटल व्योम dma_resv_list_मुक्त(काष्ठा dma_resv_list *list)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!list)
		वापस;

	क्रम (i = 0; i < list->shared_count; ++i)
		dma_fence_put(rcu_dereference_रक्षित(list->shared[i], true));

	kमुक्त_rcu(list, rcu);
पूर्ण

#अगर IS_ENABLED(CONFIG_LOCKDEP)
अटल पूर्णांक __init dma_resv_lockdep(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = mm_alloc();
	काष्ठा ww_acquire_ctx ctx;
	काष्ठा dma_resv obj;
	काष्ठा address_space mapping;
	पूर्णांक ret;

	अगर (!mm)
		वापस -ENOMEM;

	dma_resv_init(&obj);
	address_space_init_once(&mapping);

	mmap_पढ़ो_lock(mm);
	ww_acquire_init(&ctx, &reservation_ww_class);
	ret = dma_resv_lock(&obj, &ctx);
	अगर (ret == -EDEADLK)
		dma_resv_lock_slow(&obj, &ctx);
	fs_reclaim_acquire(GFP_KERNEL);
	/* क्रम unmap_mapping_range on trylocked buffer objects in shrinkers */
	i_mmap_lock_ग_लिखो(&mapping);
	i_mmap_unlock_ग_लिखो(&mapping);
#अगर_घोषित CONFIG_MMU_NOTIFIER
	lock_map_acquire(&__mmu_notअगरier_invalidate_range_start_map);
	__dma_fence_might_रुको();
	lock_map_release(&__mmu_notअगरier_invalidate_range_start_map);
#अन्यथा
	__dma_fence_might_रुको();
#पूर्ण_अगर
	fs_reclaim_release(GFP_KERNEL);
	ww_mutex_unlock(&obj.lock);
	ww_acquire_fini(&ctx);
	mmap_पढ़ो_unlock(mm);
	
	mmput(mm);

	वापस 0;
पूर्ण
subsys_initcall(dma_resv_lockdep);
#पूर्ण_अगर

/**
 * dma_resv_init - initialize a reservation object
 * @obj: the reservation object
 */
व्योम dma_resv_init(काष्ठा dma_resv *obj)
अणु
	ww_mutex_init(&obj->lock, &reservation_ww_class);
	seqcount_ww_mutex_init(&obj->seq, &obj->lock);

	RCU_INIT_POINTER(obj->fence, शून्य);
	RCU_INIT_POINTER(obj->fence_excl, शून्य);
पूर्ण
EXPORT_SYMBOL(dma_resv_init);

/**
 * dma_resv_fini - destroys a reservation object
 * @obj: the reservation object
 */
व्योम dma_resv_fini(काष्ठा dma_resv *obj)
अणु
	काष्ठा dma_resv_list *fobj;
	काष्ठा dma_fence *excl;

	/*
	 * This object should be dead and all references must have
	 * been released to it, so no need to be रक्षित with rcu.
	 */
	excl = rcu_dereference_रक्षित(obj->fence_excl, 1);
	अगर (excl)
		dma_fence_put(excl);

	fobj = rcu_dereference_रक्षित(obj->fence, 1);
	dma_resv_list_मुक्त(fobj);
	ww_mutex_destroy(&obj->lock);
पूर्ण
EXPORT_SYMBOL(dma_resv_fini);

/**
 * dma_resv_reserve_shared - Reserve space to add shared fences to
 * a dma_resv.
 * @obj: reservation object
 * @num_fences: number of fences we want to add
 *
 * Should be called beक्रमe dma_resv_add_shared_fence().  Must
 * be called with obj->lock held.
 *
 * RETURNS
 * Zero क्रम success, or -त्रुटि_सं
 */
पूर्णांक dma_resv_reserve_shared(काष्ठा dma_resv *obj, अचिन्हित पूर्णांक num_fences)
अणु
	काष्ठा dma_resv_list *old, *new;
	अचिन्हित पूर्णांक i, j, k, max;

	dma_resv_निश्चित_held(obj);

	old = dma_resv_get_list(obj);

	अगर (old && old->shared_max) अणु
		अगर ((old->shared_count + num_fences) <= old->shared_max)
			वापस 0;
		अन्यथा
			max = max(old->shared_count + num_fences,
				  old->shared_max * 2);
	पूर्ण अन्यथा अणु
		max = max(4ul, roundup_घात_of_two(num_fences));
	पूर्ण

	new = dma_resv_list_alloc(max);
	अगर (!new)
		वापस -ENOMEM;

	/*
	 * no need to bump fence refcounts, rcu_पढ़ो access
	 * requires the use of kref_get_unless_zero, and the
	 * references from the old काष्ठा are carried over to
	 * the new.
	 */
	क्रम (i = 0, j = 0, k = max; i < (old ? old->shared_count : 0); ++i) अणु
		काष्ठा dma_fence *fence;

		fence = rcu_dereference_रक्षित(old->shared[i],
						  dma_resv_held(obj));
		अगर (dma_fence_is_संकेतed(fence))
			RCU_INIT_POINTER(new->shared[--k], fence);
		अन्यथा
			RCU_INIT_POINTER(new->shared[j++], fence);
	पूर्ण
	new->shared_count = j;

	/*
	 * We are not changing the effective set of fences here so can
	 * merely update the poपूर्णांकer to the new array; both existing
	 * पढ़ोers and new पढ़ोers will see exactly the same set of
	 * active (unसंकेतed) shared fences. Inभागidual fences and the
	 * old array are रक्षित by RCU and so will not vanish under
	 * the gaze of the rcu_पढ़ो_lock() पढ़ोers.
	 */
	rcu_assign_poपूर्णांकer(obj->fence, new);

	अगर (!old)
		वापस 0;

	/* Drop the references to the संकेतed fences */
	क्रम (i = k; i < max; ++i) अणु
		काष्ठा dma_fence *fence;

		fence = rcu_dereference_रक्षित(new->shared[i],
						  dma_resv_held(obj));
		dma_fence_put(fence);
	पूर्ण
	kमुक्त_rcu(old, rcu);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dma_resv_reserve_shared);

/**
 * dma_resv_add_shared_fence - Add a fence to a shared slot
 * @obj: the reservation object
 * @fence: the shared fence to add
 *
 * Add a fence to a shared slot, obj->lock must be held, and
 * dma_resv_reserve_shared() has been called.
 */
व्योम dma_resv_add_shared_fence(काष्ठा dma_resv *obj, काष्ठा dma_fence *fence)
अणु
	काष्ठा dma_resv_list *fobj;
	काष्ठा dma_fence *old;
	अचिन्हित पूर्णांक i, count;

	dma_fence_get(fence);

	dma_resv_निश्चित_held(obj);

	fobj = dma_resv_get_list(obj);
	count = fobj->shared_count;

	ग_लिखो_seqcount_begin(&obj->seq);

	क्रम (i = 0; i < count; ++i) अणु

		old = rcu_dereference_रक्षित(fobj->shared[i],
						dma_resv_held(obj));
		अगर (old->context == fence->context ||
		    dma_fence_is_संकेतed(old))
			जाओ replace;
	पूर्ण

	BUG_ON(fobj->shared_count >= fobj->shared_max);
	old = शून्य;
	count++;

replace:
	RCU_INIT_POINTER(fobj->shared[i], fence);
	/* poपूर्णांकer update must be visible beक्रमe we extend the shared_count */
	smp_store_mb(fobj->shared_count, count);

	ग_लिखो_seqcount_end(&obj->seq);
	dma_fence_put(old);
पूर्ण
EXPORT_SYMBOL(dma_resv_add_shared_fence);

/**
 * dma_resv_add_excl_fence - Add an exclusive fence.
 * @obj: the reservation object
 * @fence: the shared fence to add
 *
 * Add a fence to the exclusive slot.  The obj->lock must be held.
 */
व्योम dma_resv_add_excl_fence(काष्ठा dma_resv *obj, काष्ठा dma_fence *fence)
अणु
	काष्ठा dma_fence *old_fence = dma_resv_get_excl(obj);
	काष्ठा dma_resv_list *old;
	u32 i = 0;

	dma_resv_निश्चित_held(obj);

	old = dma_resv_get_list(obj);
	अगर (old)
		i = old->shared_count;

	अगर (fence)
		dma_fence_get(fence);

	ग_लिखो_seqcount_begin(&obj->seq);
	/* ग_लिखो_seqcount_begin provides the necessary memory barrier */
	RCU_INIT_POINTER(obj->fence_excl, fence);
	अगर (old)
		old->shared_count = 0;
	ग_लिखो_seqcount_end(&obj->seq);

	/* inplace update, no shared fences */
	जबतक (i--)
		dma_fence_put(rcu_dereference_रक्षित(old->shared[i],
						dma_resv_held(obj)));

	dma_fence_put(old_fence);
पूर्ण
EXPORT_SYMBOL(dma_resv_add_excl_fence);

/**
* dma_resv_copy_fences - Copy all fences from src to dst.
* @dst: the destination reservation object
* @src: the source reservation object
*
* Copy all fences from src to dst. dst-lock must be held.
*/
पूर्णांक dma_resv_copy_fences(काष्ठा dma_resv *dst, काष्ठा dma_resv *src)
अणु
	काष्ठा dma_resv_list *src_list, *dst_list;
	काष्ठा dma_fence *old, *new;
	अचिन्हित i;

	dma_resv_निश्चित_held(dst);

	rcu_पढ़ो_lock();
	src_list = rcu_dereference(src->fence);

retry:
	अगर (src_list) अणु
		अचिन्हित shared_count = src_list->shared_count;

		rcu_पढ़ो_unlock();

		dst_list = dma_resv_list_alloc(shared_count);
		अगर (!dst_list)
			वापस -ENOMEM;

		rcu_पढ़ो_lock();
		src_list = rcu_dereference(src->fence);
		अगर (!src_list || src_list->shared_count > shared_count) अणु
			kमुक्त(dst_list);
			जाओ retry;
		पूर्ण

		dst_list->shared_count = 0;
		क्रम (i = 0; i < src_list->shared_count; ++i) अणु
			काष्ठा dma_fence *fence;

			fence = rcu_dereference(src_list->shared[i]);
			अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT,
				     &fence->flags))
				जारी;

			अगर (!dma_fence_get_rcu(fence)) अणु
				dma_resv_list_मुक्त(dst_list);
				src_list = rcu_dereference(src->fence);
				जाओ retry;
			पूर्ण

			अगर (dma_fence_is_संकेतed(fence)) अणु
				dma_fence_put(fence);
				जारी;
			पूर्ण

			rcu_assign_poपूर्णांकer(dst_list->shared[dst_list->shared_count++], fence);
		पूर्ण
	पूर्ण अन्यथा अणु
		dst_list = शून्य;
	पूर्ण

	new = dma_fence_get_rcu_safe(&src->fence_excl);
	rcu_पढ़ो_unlock();

	src_list = dma_resv_get_list(dst);
	old = dma_resv_get_excl(dst);

	ग_लिखो_seqcount_begin(&dst->seq);
	/* ग_लिखो_seqcount_begin provides the necessary memory barrier */
	RCU_INIT_POINTER(dst->fence_excl, new);
	RCU_INIT_POINTER(dst->fence, dst_list);
	ग_लिखो_seqcount_end(&dst->seq);

	dma_resv_list_मुक्त(src_list);
	dma_fence_put(old);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dma_resv_copy_fences);

/**
 * dma_resv_get_fences_rcu - Get an object's shared and exclusive
 * fences without update side lock held
 * @obj: the reservation object
 * @pfence_excl: the वापसed exclusive fence (or शून्य)
 * @pshared_count: the number of shared fences वापसed
 * @pshared: the array of shared fence ptrs वापसed (array is kपुनः_स्मृति'd to
 * the required size, and must be मुक्तd by caller)
 *
 * Retrieve all fences from the reservation object. If the poपूर्णांकer क्रम the
 * exclusive fence is not specअगरied the fence is put पूर्णांकo the array of the
 * shared fences as well. Returns either zero or -ENOMEM.
 */
पूर्णांक dma_resv_get_fences_rcu(काष्ठा dma_resv *obj,
			    काष्ठा dma_fence **pfence_excl,
			    अचिन्हित *pshared_count,
			    काष्ठा dma_fence ***pshared)
अणु
	काष्ठा dma_fence **shared = शून्य;
	काष्ठा dma_fence *fence_excl;
	अचिन्हित पूर्णांक shared_count;
	पूर्णांक ret = 1;

	करो अणु
		काष्ठा dma_resv_list *fobj;
		अचिन्हित पूर्णांक i, seq;
		माप_प्रकार sz = 0;

		shared_count = i = 0;

		rcu_पढ़ो_lock();
		seq = पढ़ो_seqcount_begin(&obj->seq);

		fence_excl = rcu_dereference(obj->fence_excl);
		अगर (fence_excl && !dma_fence_get_rcu(fence_excl))
			जाओ unlock;

		fobj = rcu_dereference(obj->fence);
		अगर (fobj)
			sz += माप(*shared) * fobj->shared_max;

		अगर (!pfence_excl && fence_excl)
			sz += माप(*shared);

		अगर (sz) अणु
			काष्ठा dma_fence **nshared;

			nshared = kपुनः_स्मृति(shared, sz,
					   GFP_NOWAIT | __GFP_NOWARN);
			अगर (!nshared) अणु
				rcu_पढ़ो_unlock();

				dma_fence_put(fence_excl);
				fence_excl = शून्य;

				nshared = kपुनः_स्मृति(shared, sz, GFP_KERNEL);
				अगर (nshared) अणु
					shared = nshared;
					जारी;
				पूर्ण

				ret = -ENOMEM;
				अवरोध;
			पूर्ण
			shared = nshared;
			shared_count = fobj ? fobj->shared_count : 0;
			क्रम (i = 0; i < shared_count; ++i) अणु
				shared[i] = rcu_dereference(fobj->shared[i]);
				अगर (!dma_fence_get_rcu(shared[i]))
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (i != shared_count || पढ़ो_seqcount_retry(&obj->seq, seq)) अणु
			जबतक (i--)
				dma_fence_put(shared[i]);
			dma_fence_put(fence_excl);
			जाओ unlock;
		पूर्ण

		ret = 0;
unlock:
		rcu_पढ़ो_unlock();
	पूर्ण जबतक (ret);

	अगर (pfence_excl)
		*pfence_excl = fence_excl;
	अन्यथा अगर (fence_excl)
		shared[shared_count++] = fence_excl;

	अगर (!shared_count) अणु
		kमुक्त(shared);
		shared = शून्य;
	पूर्ण

	*pshared_count = shared_count;
	*pshared = shared;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dma_resv_get_fences_rcu);

/**
 * dma_resv_रुको_समयout_rcu - Wait on reservation's objects
 * shared and/or exclusive fences.
 * @obj: the reservation object
 * @रुको_all: अगर true, रुको on all fences, अन्यथा रुको on just exclusive fence
 * @पूर्णांकr: अगर true, करो पूर्णांकerruptible रुको
 * @समयout: समयout value in jअगरfies or zero to वापस immediately
 *
 * RETURNS
 * Returns -ERESTARTSYS अगर पूर्णांकerrupted, 0 अगर the रुको समयd out, or
 * greater than zer on success.
 */
दीर्घ dma_resv_रुको_समयout_rcu(काष्ठा dma_resv *obj,
			       bool रुको_all, bool पूर्णांकr,
			       अचिन्हित दीर्घ समयout)
अणु
	काष्ठा dma_fence *fence;
	अचिन्हित seq, shared_count;
	दीर्घ ret = समयout ? समयout : 1;
	पूर्णांक i;

retry:
	shared_count = 0;
	seq = पढ़ो_seqcount_begin(&obj->seq);
	rcu_पढ़ो_lock();
	i = -1;

	fence = rcu_dereference(obj->fence_excl);
	अगर (fence && !test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags)) अणु
		अगर (!dma_fence_get_rcu(fence))
			जाओ unlock_retry;

		अगर (dma_fence_is_संकेतed(fence)) अणु
			dma_fence_put(fence);
			fence = शून्य;
		पूर्ण

	पूर्ण अन्यथा अणु
		fence = शून्य;
	पूर्ण

	अगर (रुको_all) अणु
		काष्ठा dma_resv_list *fobj = rcu_dereference(obj->fence);

		अगर (fobj)
			shared_count = fobj->shared_count;

		क्रम (i = 0; !fence && i < shared_count; ++i) अणु
			काष्ठा dma_fence *lfence = rcu_dereference(fobj->shared[i]);

			अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT,
				     &lfence->flags))
				जारी;

			अगर (!dma_fence_get_rcu(lfence))
				जाओ unlock_retry;

			अगर (dma_fence_is_संकेतed(lfence)) अणु
				dma_fence_put(lfence);
				जारी;
			पूर्ण

			fence = lfence;
			अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	अगर (fence) अणु
		अगर (पढ़ो_seqcount_retry(&obj->seq, seq)) अणु
			dma_fence_put(fence);
			जाओ retry;
		पूर्ण

		ret = dma_fence_रुको_समयout(fence, पूर्णांकr, ret);
		dma_fence_put(fence);
		अगर (ret > 0 && रुको_all && (i + 1 < shared_count))
			जाओ retry;
	पूर्ण
	वापस ret;

unlock_retry:
	rcu_पढ़ो_unlock();
	जाओ retry;
पूर्ण
EXPORT_SYMBOL_GPL(dma_resv_रुको_समयout_rcu);


अटल अंतरभूत पूर्णांक dma_resv_test_संकेतed_single(काष्ठा dma_fence *passed_fence)
अणु
	काष्ठा dma_fence *fence, *lfence = passed_fence;
	पूर्णांक ret = 1;

	अगर (!test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &lfence->flags)) अणु
		fence = dma_fence_get_rcu(lfence);
		अगर (!fence)
			वापस -1;

		ret = !!dma_fence_is_संकेतed(fence);
		dma_fence_put(fence);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * dma_resv_test_संकेतed_rcu - Test अगर a reservation object's
 * fences have been संकेतed.
 * @obj: the reservation object
 * @test_all: अगर true, test all fences, otherwise only test the exclusive
 * fence
 *
 * RETURNS
 * true अगर all fences संकेतed, अन्यथा false
 */
bool dma_resv_test_संकेतed_rcu(काष्ठा dma_resv *obj, bool test_all)
अणु
	अचिन्हित seq, shared_count;
	पूर्णांक ret;

	rcu_पढ़ो_lock();
retry:
	ret = true;
	shared_count = 0;
	seq = पढ़ो_seqcount_begin(&obj->seq);

	अगर (test_all) अणु
		अचिन्हित i;

		काष्ठा dma_resv_list *fobj = rcu_dereference(obj->fence);

		अगर (fobj)
			shared_count = fobj->shared_count;

		क्रम (i = 0; i < shared_count; ++i) अणु
			काष्ठा dma_fence *fence = rcu_dereference(fobj->shared[i]);

			ret = dma_resv_test_संकेतed_single(fence);
			अगर (ret < 0)
				जाओ retry;
			अन्यथा अगर (!ret)
				अवरोध;
		पूर्ण

		अगर (पढ़ो_seqcount_retry(&obj->seq, seq))
			जाओ retry;
	पूर्ण

	अगर (!shared_count) अणु
		काष्ठा dma_fence *fence_excl = rcu_dereference(obj->fence_excl);

		अगर (fence_excl) अणु
			ret = dma_resv_test_संकेतed_single(fence_excl);
			अगर (ret < 0)
				जाओ retry;

			अगर (पढ़ो_seqcount_retry(&obj->seq, seq))
				जाओ retry;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dma_resv_test_संकेतed_rcu);
