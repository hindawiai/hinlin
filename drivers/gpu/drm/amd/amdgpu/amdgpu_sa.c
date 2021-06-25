<शैली गुरु>
/*
 * Copyright 2011 Red Hat Inc.
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 */
/*
 * Authors:
 *    Jerome Glisse <glisse@मुक्तdesktop.org>
 */
/* Algorithm:
 *
 * We store the last allocated bo in "hole", we always try to allocate
 * after the last allocated bo. Principle is that in a linear GPU ring
 * progression was is after last is the oldest bo we allocated and thus
 * the first one that should no दीर्घer be in use by the GPU.
 *
 * If it's not the हाल we skip over the bo after last to the बंदst
 * करोne bo अगर such one exist. If none exist and we are not asked to
 * block we report failure to allocate.
 *
 * If we are asked to block we रुको on all the oldest fence of all
 * rings. We just रुको क्रम any of those fence to complete.
 */

#समावेश "amdgpu.h"

अटल व्योम amdgpu_sa_bo_हटाओ_locked(काष्ठा amdgpu_sa_bo *sa_bo);
अटल व्योम amdgpu_sa_bo_try_मुक्त(काष्ठा amdgpu_sa_manager *sa_manager);

पूर्णांक amdgpu_sa_bo_manager_init(काष्ठा amdgpu_device *adev,
			      काष्ठा amdgpu_sa_manager *sa_manager,
			      अचिन्हित size, u32 align, u32 करोमुख्य)
अणु
	पूर्णांक i, r;

	init_रुकोqueue_head(&sa_manager->wq);
	sa_manager->bo = शून्य;
	sa_manager->size = size;
	sa_manager->करोमुख्य = करोमुख्य;
	sa_manager->align = align;
	sa_manager->hole = &sa_manager->olist;
	INIT_LIST_HEAD(&sa_manager->olist);
	क्रम (i = 0; i < AMDGPU_SA_NUM_FENCE_LISTS; ++i)
		INIT_LIST_HEAD(&sa_manager->flist[i]);

	r = amdgpu_bo_create_kernel(adev, size, align, करोमुख्य, &sa_manager->bo,
				&sa_manager->gpu_addr, &sa_manager->cpu_ptr);
	अगर (r) अणु
		dev_err(adev->dev, "(%d) failed to allocate bo for manager\n", r);
		वापस r;
	पूर्ण

	स_रखो(sa_manager->cpu_ptr, 0, sa_manager->size);
	वापस r;
पूर्ण

व्योम amdgpu_sa_bo_manager_fini(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_sa_manager *sa_manager)
अणु
	काष्ठा amdgpu_sa_bo *sa_bo, *पंचांगp;

	अगर (sa_manager->bo == शून्य) अणु
		dev_err(adev->dev, "no bo for sa manager\n");
		वापस;
	पूर्ण

	अगर (!list_empty(&sa_manager->olist)) अणु
		sa_manager->hole = &sa_manager->olist,
		amdgpu_sa_bo_try_मुक्त(sa_manager);
		अगर (!list_empty(&sa_manager->olist)) अणु
			dev_err(adev->dev, "sa_manager is not empty, clearing anyway\n");
		पूर्ण
	पूर्ण
	list_क्रम_each_entry_safe(sa_bo, पंचांगp, &sa_manager->olist, olist) अणु
		amdgpu_sa_bo_हटाओ_locked(sa_bo);
	पूर्ण

	amdgpu_bo_मुक्त_kernel(&sa_manager->bo, &sa_manager->gpu_addr, &sa_manager->cpu_ptr);
	sa_manager->size = 0;
पूर्ण

अटल व्योम amdgpu_sa_bo_हटाओ_locked(काष्ठा amdgpu_sa_bo *sa_bo)
अणु
	काष्ठा amdgpu_sa_manager *sa_manager = sa_bo->manager;
	अगर (sa_manager->hole == &sa_bo->olist) अणु
		sa_manager->hole = sa_bo->olist.prev;
	पूर्ण
	list_del_init(&sa_bo->olist);
	list_del_init(&sa_bo->flist);
	dma_fence_put(sa_bo->fence);
	kमुक्त(sa_bo);
पूर्ण

अटल व्योम amdgpu_sa_bo_try_मुक्त(काष्ठा amdgpu_sa_manager *sa_manager)
अणु
	काष्ठा amdgpu_sa_bo *sa_bo, *पंचांगp;

	अगर (sa_manager->hole->next == &sa_manager->olist)
		वापस;

	sa_bo = list_entry(sa_manager->hole->next, काष्ठा amdgpu_sa_bo, olist);
	list_क्रम_each_entry_safe_from(sa_bo, पंचांगp, &sa_manager->olist, olist) अणु
		अगर (sa_bo->fence == शून्य ||
		    !dma_fence_is_संकेतed(sa_bo->fence)) अणु
			वापस;
		पूर्ण
		amdgpu_sa_bo_हटाओ_locked(sa_bo);
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित amdgpu_sa_bo_hole_soffset(काष्ठा amdgpu_sa_manager *sa_manager)
अणु
	काष्ठा list_head *hole = sa_manager->hole;

	अगर (hole != &sa_manager->olist) अणु
		वापस list_entry(hole, काष्ठा amdgpu_sa_bo, olist)->eoffset;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित amdgpu_sa_bo_hole_eoffset(काष्ठा amdgpu_sa_manager *sa_manager)
अणु
	काष्ठा list_head *hole = sa_manager->hole;

	अगर (hole->next != &sa_manager->olist) अणु
		वापस list_entry(hole->next, काष्ठा amdgpu_sa_bo, olist)->soffset;
	पूर्ण
	वापस sa_manager->size;
पूर्ण

अटल bool amdgpu_sa_bo_try_alloc(काष्ठा amdgpu_sa_manager *sa_manager,
				   काष्ठा amdgpu_sa_bo *sa_bo,
				   अचिन्हित size, अचिन्हित align)
अणु
	अचिन्हित soffset, eoffset, wasted;

	soffset = amdgpu_sa_bo_hole_soffset(sa_manager);
	eoffset = amdgpu_sa_bo_hole_eoffset(sa_manager);
	wasted = (align - (soffset % align)) % align;

	अगर ((eoffset - soffset) >= (size + wasted)) अणु
		soffset += wasted;

		sa_bo->manager = sa_manager;
		sa_bo->soffset = soffset;
		sa_bo->eoffset = soffset + size;
		list_add(&sa_bo->olist, sa_manager->hole);
		INIT_LIST_HEAD(&sa_bo->flist);
		sa_manager->hole = &sa_bo->olist;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * amdgpu_sa_event - Check अगर we can stop रुकोing
 *
 * @sa_manager: poपूर्णांकer to the sa_manager
 * @size: number of bytes we want to allocate
 * @align: alignment we need to match
 *
 * Check अगर either there is a fence we can रुको क्रम or
 * enough मुक्त memory to satisfy the allocation directly
 */
अटल bool amdgpu_sa_event(काष्ठा amdgpu_sa_manager *sa_manager,
			    अचिन्हित size, अचिन्हित align)
अणु
	अचिन्हित soffset, eoffset, wasted;
	पूर्णांक i;

	क्रम (i = 0; i < AMDGPU_SA_NUM_FENCE_LISTS; ++i)
		अगर (!list_empty(&sa_manager->flist[i]))
			वापस true;

	soffset = amdgpu_sa_bo_hole_soffset(sa_manager);
	eoffset = amdgpu_sa_bo_hole_eoffset(sa_manager);
	wasted = (align - (soffset % align)) % align;

	अगर ((eoffset - soffset) >= (size + wasted)) अणु
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool amdgpu_sa_bo_next_hole(काष्ठा amdgpu_sa_manager *sa_manager,
				   काष्ठा dma_fence **fences,
				   अचिन्हित *tries)
अणु
	काष्ठा amdgpu_sa_bo *best_bo = शून्य;
	अचिन्हित i, soffset, best, पंचांगp;

	/* अगर hole poपूर्णांकs to the end of the buffer */
	अगर (sa_manager->hole->next == &sa_manager->olist) अणु
		/* try again with its beginning */
		sa_manager->hole = &sa_manager->olist;
		वापस true;
	पूर्ण

	soffset = amdgpu_sa_bo_hole_soffset(sa_manager);
	/* to handle wrap around we add sa_manager->size */
	best = sa_manager->size * 2;
	/* go over all fence list and try to find the बंदst sa_bo
	 * of the current last
	 */
	क्रम (i = 0; i < AMDGPU_SA_NUM_FENCE_LISTS; ++i) अणु
		काष्ठा amdgpu_sa_bo *sa_bo;

		fences[i] = शून्य;

		अगर (list_empty(&sa_manager->flist[i]))
			जारी;

		sa_bo = list_first_entry(&sa_manager->flist[i],
					 काष्ठा amdgpu_sa_bo, flist);

		अगर (!dma_fence_is_संकेतed(sa_bo->fence)) अणु
			fences[i] = sa_bo->fence;
			जारी;
		पूर्ण

		/* limit the number of tries each ring माला_लो */
		अगर (tries[i] > 2) अणु
			जारी;
		पूर्ण

		पंचांगp = sa_bo->soffset;
		अगर (पंचांगp < soffset) अणु
			/* wrap around, pretend it's after */
			पंचांगp += sa_manager->size;
		पूर्ण
		पंचांगp -= soffset;
		अगर (पंचांगp < best) अणु
			/* this sa bo is the बंदst one */
			best = पंचांगp;
			best_bo = sa_bo;
		पूर्ण
	पूर्ण

	अगर (best_bo) अणु
		uपूर्णांक32_t idx = best_bo->fence->context;

		idx %= AMDGPU_SA_NUM_FENCE_LISTS;
		++tries[idx];
		sa_manager->hole = best_bo->olist.prev;

		/* we knew that this one is संकेतed,
		   so it's save to remote it */
		amdgpu_sa_bo_हटाओ_locked(best_bo);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक amdgpu_sa_bo_new(काष्ठा amdgpu_sa_manager *sa_manager,
		     काष्ठा amdgpu_sa_bo **sa_bo,
		     अचिन्हित size, अचिन्हित align)
अणु
	काष्ठा dma_fence *fences[AMDGPU_SA_NUM_FENCE_LISTS];
	अचिन्हित tries[AMDGPU_SA_NUM_FENCE_LISTS];
	अचिन्हित count;
	पूर्णांक i, r;
	चिन्हित दीर्घ t;

	अगर (WARN_ON_ONCE(align > sa_manager->align))
		वापस -EINVAL;

	अगर (WARN_ON_ONCE(size > sa_manager->size))
		वापस -EINVAL;

	*sa_bo = kदो_स्मृति(माप(काष्ठा amdgpu_sa_bo), GFP_KERNEL);
	अगर (!(*sa_bo))
		वापस -ENOMEM;
	(*sa_bo)->manager = sa_manager;
	(*sa_bo)->fence = शून्य;
	INIT_LIST_HEAD(&(*sa_bo)->olist);
	INIT_LIST_HEAD(&(*sa_bo)->flist);

	spin_lock(&sa_manager->wq.lock);
	करो अणु
		क्रम (i = 0; i < AMDGPU_SA_NUM_FENCE_LISTS; ++i)
			tries[i] = 0;

		करो अणु
			amdgpu_sa_bo_try_मुक्त(sa_manager);

			अगर (amdgpu_sa_bo_try_alloc(sa_manager, *sa_bo,
						   size, align)) अणु
				spin_unlock(&sa_manager->wq.lock);
				वापस 0;
			पूर्ण

			/* see अगर we can skip over some allocations */
		पूर्ण जबतक (amdgpu_sa_bo_next_hole(sa_manager, fences, tries));

		क्रम (i = 0, count = 0; i < AMDGPU_SA_NUM_FENCE_LISTS; ++i)
			अगर (fences[i])
				fences[count++] = dma_fence_get(fences[i]);

		अगर (count) अणु
			spin_unlock(&sa_manager->wq.lock);
			t = dma_fence_रुको_any_समयout(fences, count, false,
						       MAX_SCHEDULE_TIMEOUT,
						       शून्य);
			क्रम (i = 0; i < count; ++i)
				dma_fence_put(fences[i]);

			r = (t > 0) ? 0 : t;
			spin_lock(&sa_manager->wq.lock);
		पूर्ण अन्यथा अणु
			/* अगर we have nothing to रुको क्रम block */
			r = रुको_event_पूर्णांकerruptible_locked(
				sa_manager->wq,
				amdgpu_sa_event(sa_manager, size, align)
			);
		पूर्ण

	पूर्ण जबतक (!r);

	spin_unlock(&sa_manager->wq.lock);
	kमुक्त(*sa_bo);
	*sa_bo = शून्य;
	वापस r;
पूर्ण

व्योम amdgpu_sa_bo_मुक्त(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_sa_bo **sa_bo,
		       काष्ठा dma_fence *fence)
अणु
	काष्ठा amdgpu_sa_manager *sa_manager;

	अगर (sa_bo == शून्य || *sa_bo == शून्य) अणु
		वापस;
	पूर्ण

	sa_manager = (*sa_bo)->manager;
	spin_lock(&sa_manager->wq.lock);
	अगर (fence && !dma_fence_is_संकेतed(fence)) अणु
		uपूर्णांक32_t idx;

		(*sa_bo)->fence = dma_fence_get(fence);
		idx = fence->context % AMDGPU_SA_NUM_FENCE_LISTS;
		list_add_tail(&(*sa_bo)->flist, &sa_manager->flist[idx]);
	पूर्ण अन्यथा अणु
		amdgpu_sa_bo_हटाओ_locked(*sa_bo);
	पूर्ण
	wake_up_all_locked(&sa_manager->wq);
	spin_unlock(&sa_manager->wq.lock);
	*sa_bo = शून्य;
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)

व्योम amdgpu_sa_bo_dump_debug_info(काष्ठा amdgpu_sa_manager *sa_manager,
				  काष्ठा seq_file *m)
अणु
	काष्ठा amdgpu_sa_bo *i;

	spin_lock(&sa_manager->wq.lock);
	list_क्रम_each_entry(i, &sa_manager->olist, olist) अणु
		uपूर्णांक64_t soffset = i->soffset + sa_manager->gpu_addr;
		uपूर्णांक64_t eoffset = i->eoffset + sa_manager->gpu_addr;
		अगर (&i->olist == sa_manager->hole) अणु
			seq_म_लिखो(m, ">");
		पूर्ण अन्यथा अणु
			seq_म_लिखो(m, " ");
		पूर्ण
		seq_म_लिखो(m, "[0x%010llx 0x%010llx] size %8lld",
			   soffset, eoffset, eoffset - soffset);

		अगर (i->fence)
			seq_म_लिखो(m, " protected by 0x%016llx on context %llu",
				   i->fence->seqno, i->fence->context);

		seq_म_लिखो(m, "\n");
	पूर्ण
	spin_unlock(&sa_manager->wq.lock);
पूर्ण
#पूर्ण_अगर
