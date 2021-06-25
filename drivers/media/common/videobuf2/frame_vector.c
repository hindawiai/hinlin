<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sched.h>

#समावेश <media/frame_vector.h>

/**
 * get_vaddr_frames() - map भव addresses to pfns
 * @start:	starting user address
 * @nr_frames:	number of pages / pfns from start to map
 * @vec:	काष्ठाure which receives pages / pfns of the addresses mapped.
 *		It should have space क्रम at least nr_frames entries.
 *
 * This function maps भव addresses from @start and fills @vec काष्ठाure
 * with page frame numbers or page poपूर्णांकers to corresponding pages (choice
 * depends on the type of the vma underlying the भव address). If @start
 * beदीर्घs to a normal vma, the function grअसल reference to each of the pages
 * to pin them in memory. If @start beदीर्घs to VM_IO | VM_PFNMAP vma, we करोn't
 * touch page काष्ठाures and the caller must make sure pfns aren't reused क्रम
 * anything अन्यथा जबतक he is using them.
 *
 * The function वापसs number of pages mapped which may be less than
 * @nr_frames. In particular we stop mapping अगर there are more vmas of
 * dअगरferent type underlying the specअगरied range of भव addresses.
 * When the function isn't able to map a single page, it वापसs error.
 *
 * This function takes care of grabbing mmap_lock as necessary.
 */
पूर्णांक get_vaddr_frames(अचिन्हित दीर्घ start, अचिन्हित पूर्णांक nr_frames,
		     काष्ठा frame_vector *vec)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक ret = 0;
	पूर्णांक err;

	अगर (nr_frames == 0)
		वापस 0;

	अगर (WARN_ON_ONCE(nr_frames > vec->nr_allocated))
		nr_frames = vec->nr_allocated;

	start = untagged_addr(start);

	ret = pin_user_pages_fast(start, nr_frames,
				  FOLL_FORCE | FOLL_WRITE | FOLL_LONGTERM,
				  (काष्ठा page **)(vec->ptrs));
	अगर (ret > 0) अणु
		vec->got_ref = true;
		vec->is_pfns = false;
		जाओ out_unlocked;
	पूर्ण

	mmap_पढ़ो_lock(mm);
	vec->got_ref = false;
	vec->is_pfns = true;
	ret = 0;
	करो अणु
		अचिन्हित दीर्घ *nums = frame_vector_pfns(vec);

		vma = find_vma_पूर्णांकersection(mm, start, start + 1);
		अगर (!vma)
			अवरोध;

		जबतक (ret < nr_frames && start + PAGE_SIZE <= vma->vm_end) अणु
			err = follow_pfn(vma, start, &nums[ret]);
			अगर (err) अणु
				अगर (ret == 0)
					ret = err;
				जाओ out;
			पूर्ण
			start += PAGE_SIZE;
			ret++;
		पूर्ण
		/* Bail out अगर VMA करोesn't completely cover the tail page. */
		अगर (start < vma->vm_end)
			अवरोध;
	पूर्ण जबतक (ret < nr_frames);
out:
	mmap_पढ़ो_unlock(mm);
out_unlocked:
	अगर (!ret)
		ret = -EFAULT;
	अगर (ret > 0)
		vec->nr_frames = ret;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(get_vaddr_frames);

/**
 * put_vaddr_frames() - drop references to pages अगर get_vaddr_frames() acquired
 *			them
 * @vec:	frame vector to put
 *
 * Drop references to pages अगर get_vaddr_frames() acquired them. We also
 * invalidate the frame vector so that it is prepared क्रम the next call पूर्णांकo
 * get_vaddr_frames().
 */
व्योम put_vaddr_frames(काष्ठा frame_vector *vec)
अणु
	काष्ठा page **pages;

	अगर (!vec->got_ref)
		जाओ out;
	pages = frame_vector_pages(vec);
	/*
	 * frame_vector_pages() might needed to करो a conversion when
	 * get_vaddr_frames() got pages but vec was later converted to pfns.
	 * But it shouldn't really fail to convert pfns back...
	 */
	अगर (WARN_ON(IS_ERR(pages)))
		जाओ out;

	unpin_user_pages(pages, vec->nr_frames);
	vec->got_ref = false;
out:
	vec->nr_frames = 0;
पूर्ण
EXPORT_SYMBOL(put_vaddr_frames);

/**
 * frame_vector_to_pages - convert frame vector to contain page poपूर्णांकers
 * @vec:	frame vector to convert
 *
 * Convert @vec to contain array of page poपूर्णांकers.  If the conversion is
 * successful, वापस 0. Otherwise वापस an error. Note that we करो not grab
 * page references क्रम the page काष्ठाures.
 */
पूर्णांक frame_vector_to_pages(काष्ठा frame_vector *vec)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ *nums;
	काष्ठा page **pages;

	अगर (!vec->is_pfns)
		वापस 0;
	nums = frame_vector_pfns(vec);
	क्रम (i = 0; i < vec->nr_frames; i++)
		अगर (!pfn_valid(nums[i]))
			वापस -EINVAL;
	pages = (काष्ठा page **)nums;
	क्रम (i = 0; i < vec->nr_frames; i++)
		pages[i] = pfn_to_page(nums[i]);
	vec->is_pfns = false;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(frame_vector_to_pages);

/**
 * frame_vector_to_pfns - convert frame vector to contain pfns
 * @vec:	frame vector to convert
 *
 * Convert @vec to contain array of pfns.
 */
व्योम frame_vector_to_pfns(काष्ठा frame_vector *vec)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ *nums;
	काष्ठा page **pages;

	अगर (vec->is_pfns)
		वापस;
	pages = (काष्ठा page **)(vec->ptrs);
	nums = (अचिन्हित दीर्घ *)pages;
	क्रम (i = 0; i < vec->nr_frames; i++)
		nums[i] = page_to_pfn(pages[i]);
	vec->is_pfns = true;
पूर्ण
EXPORT_SYMBOL(frame_vector_to_pfns);

/**
 * frame_vector_create() - allocate & initialize काष्ठाure क्रम pinned pfns
 * @nr_frames:	number of pfns slots we should reserve
 *
 * Allocate and initialize काष्ठा pinned_pfns to be able to hold @nr_pfns
 * pfns.
 */
काष्ठा frame_vector *frame_vector_create(अचिन्हित पूर्णांक nr_frames)
अणु
	काष्ठा frame_vector *vec;
	पूर्णांक size = माप(काष्ठा frame_vector) + माप(व्योम *) * nr_frames;

	अगर (WARN_ON_ONCE(nr_frames == 0))
		वापस शून्य;
	/*
	 * This is असलurdly high. It's here just to aव्योम strange effects when
	 * arithmetics overflows.
	 */
	अगर (WARN_ON_ONCE(nr_frames > पूर्णांक_उच्च / माप(व्योम *) / 2))
		वापस शून्य;
	/*
	 * Aव्योम higher order allocations, use vदो_स्मृति instead. It should
	 * be rare anyway.
	 */
	vec = kvदो_स्मृति(size, GFP_KERNEL);
	अगर (!vec)
		वापस शून्य;
	vec->nr_allocated = nr_frames;
	vec->nr_frames = 0;
	वापस vec;
पूर्ण
EXPORT_SYMBOL(frame_vector_create);

/**
 * frame_vector_destroy() - मुक्त memory allocated to carry frame vector
 * @vec:	Frame vector to मुक्त
 *
 * Free काष्ठाure allocated by frame_vector_create() to carry frames.
 */
व्योम frame_vector_destroy(काष्ठा frame_vector *vec)
अणु
	/* Make sure put_vaddr_frames() got called properly... */
	VM_BUG_ON(vec->nr_frames > 0);
	kvमुक्त(vec);
पूर्ण
EXPORT_SYMBOL(frame_vector_destroy);
