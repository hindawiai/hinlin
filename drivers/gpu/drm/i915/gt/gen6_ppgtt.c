<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <linux/log2.h>

#समावेश "gen6_ppgtt.h"
#समावेश "i915_scatterlist.h"
#समावेश "i915_trace.h"
#समावेश "i915_vgpu.h"
#समावेश "intel_gt.h"

/* Write pde (index) from the page directory @pd to the page table @pt */
अटल व्योम gen6_ग_लिखो_pde(स्थिर काष्ठा gen6_ppgtt *ppgtt,
			   स्थिर अचिन्हित पूर्णांक pde,
			   स्थिर काष्ठा i915_page_table *pt)
अणु
	dma_addr_t addr = pt ? px_dma(pt) : px_dma(ppgtt->base.vm.scratch[1]);

	/* Caller needs to make sure the ग_लिखो completes अगर necessary */
	ioग_लिखो32(GEN6_PDE_ADDR_ENCODE(addr) | GEN6_PDE_VALID,
		  ppgtt->pd_addr + pde);
पूर्ण

व्योम gen7_ppgtt_enable(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	u32 ecochk;

	पूर्णांकel_uncore_rmw(uncore, GAC_ECO_BITS, 0, ECOBITS_PPGTT_CACHE64B);

	ecochk = पूर्णांकel_uncore_पढ़ो(uncore, GAM_ECOCHK);
	अगर (IS_HASWELL(i915)) अणु
		ecochk |= ECOCHK_PPGTT_WB_HSW;
	पूर्ण अन्यथा अणु
		ecochk |= ECOCHK_PPGTT_LLC_IVB;
		ecochk &= ~ECOCHK_PPGTT_GFDT_IVB;
	पूर्ण
	पूर्णांकel_uncore_ग_लिखो(uncore, GAM_ECOCHK, ecochk);
पूर्ण

व्योम gen6_ppgtt_enable(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;

	पूर्णांकel_uncore_rmw(uncore,
			 GAC_ECO_BITS,
			 0,
			 ECOBITS_SNB_BIT | ECOBITS_PPGTT_CACHE64B);

	पूर्णांकel_uncore_rmw(uncore,
			 GAB_CTL,
			 0,
			 GAB_CTL_CONT_AFTER_PAGEFAULT);

	पूर्णांकel_uncore_rmw(uncore,
			 GAM_ECOCHK,
			 0,
			 ECOCHK_SNB_BIT | ECOCHK_PPGTT_CACHE64B);

	अगर (HAS_PPGTT(uncore->i915)) /* may be disabled क्रम VT-d */
		पूर्णांकel_uncore_ग_लिखो(uncore,
				   GFX_MODE,
				   _MASKED_BIT_ENABLE(GFX_PPGTT_ENABLE));
पूर्ण

/* PPGTT support क्रम Sandybdrige/Gen6 and later */
अटल व्योम gen6_ppgtt_clear_range(काष्ठा i915_address_space *vm,
				   u64 start, u64 length)
अणु
	काष्ठा gen6_ppgtt * स्थिर ppgtt = to_gen6_ppgtt(i915_vm_to_ppgtt(vm));
	स्थिर अचिन्हित पूर्णांक first_entry = start / I915_GTT_PAGE_SIZE;
	स्थिर gen6_pte_t scratch_pte = vm->scratch[0]->encode;
	अचिन्हित पूर्णांक pde = first_entry / GEN6_PTES;
	अचिन्हित पूर्णांक pte = first_entry % GEN6_PTES;
	अचिन्हित पूर्णांक num_entries = length / I915_GTT_PAGE_SIZE;

	जबतक (num_entries) अणु
		काष्ठा i915_page_table * स्थिर pt =
			i915_pt_entry(ppgtt->base.pd, pde++);
		स्थिर अचिन्हित पूर्णांक count = min(num_entries, GEN6_PTES - pte);
		gen6_pte_t *vaddr;

		num_entries -= count;

		GEM_BUG_ON(count > atomic_पढ़ो(&pt->used));
		अगर (!atomic_sub_वापस(count, &pt->used))
			ppgtt->scan_क्रम_unused_pt = true;

		/*
		 * Note that the hw करोesn't support removing PDE on the fly
		 * (they are cached inside the context with no means to
		 * invalidate the cache), so we can only reset the PTE
		 * entries back to scratch.
		 */

		vaddr = kmap_atomic_px(pt);
		स_रखो32(vaddr + pte, scratch_pte, count);
		kunmap_atomic(vaddr);

		pte = 0;
	पूर्ण
पूर्ण

अटल व्योम gen6_ppgtt_insert_entries(काष्ठा i915_address_space *vm,
				      काष्ठा i915_vma *vma,
				      क्रमागत i915_cache_level cache_level,
				      u32 flags)
अणु
	काष्ठा i915_ppgtt *ppgtt = i915_vm_to_ppgtt(vm);
	काष्ठा i915_page_directory * स्थिर pd = ppgtt->pd;
	अचिन्हित पूर्णांक first_entry = vma->node.start / I915_GTT_PAGE_SIZE;
	अचिन्हित पूर्णांक act_pt = first_entry / GEN6_PTES;
	अचिन्हित पूर्णांक act_pte = first_entry % GEN6_PTES;
	स्थिर u32 pte_encode = vm->pte_encode(0, cache_level, flags);
	काष्ठा sgt_dma iter = sgt_dma(vma);
	gen6_pte_t *vaddr;

	GEM_BUG_ON(!pd->entry[act_pt]);

	vaddr = kmap_atomic_px(i915_pt_entry(pd, act_pt));
	करो अणु
		GEM_BUG_ON(sg_dma_len(iter.sg) < I915_GTT_PAGE_SIZE);
		vaddr[act_pte] = pte_encode | GEN6_PTE_ADDR_ENCODE(iter.dma);

		iter.dma += I915_GTT_PAGE_SIZE;
		अगर (iter.dma == iter.max) अणु
			iter.sg = __sg_next(iter.sg);
			अगर (!iter.sg || sg_dma_len(iter.sg) == 0)
				अवरोध;

			iter.dma = sg_dma_address(iter.sg);
			iter.max = iter.dma + sg_dma_len(iter.sg);
		पूर्ण

		अगर (++act_pte == GEN6_PTES) अणु
			kunmap_atomic(vaddr);
			vaddr = kmap_atomic_px(i915_pt_entry(pd, ++act_pt));
			act_pte = 0;
		पूर्ण
	पूर्ण जबतक (1);
	kunmap_atomic(vaddr);

	vma->page_sizes.gtt = I915_GTT_PAGE_SIZE;
पूर्ण

अटल व्योम gen6_flush_pd(काष्ठा gen6_ppgtt *ppgtt, u64 start, u64 end)
अणु
	काष्ठा i915_page_directory * स्थिर pd = ppgtt->base.pd;
	काष्ठा i915_page_table *pt;
	अचिन्हित पूर्णांक pde;

	start = round_करोwn(start, SZ_64K);
	end = round_up(end, SZ_64K) - start;

	mutex_lock(&ppgtt->flush);

	gen6_क्रम_each_pde(pt, pd, start, end, pde)
		gen6_ग_लिखो_pde(ppgtt, pde, pt);

	mb();
	ioपढ़ो32(ppgtt->pd_addr + pde - 1);
	gen6_ggtt_invalidate(ppgtt->base.vm.gt->ggtt);
	mb();

	mutex_unlock(&ppgtt->flush);
पूर्ण

अटल व्योम gen6_alloc_va_range(काष्ठा i915_address_space *vm,
				काष्ठा i915_vm_pt_stash *stash,
				u64 start, u64 length)
अणु
	काष्ठा gen6_ppgtt *ppgtt = to_gen6_ppgtt(i915_vm_to_ppgtt(vm));
	काष्ठा i915_page_directory * स्थिर pd = ppgtt->base.pd;
	काष्ठा i915_page_table *pt;
	bool flush = false;
	u64 from = start;
	अचिन्हित पूर्णांक pde;

	spin_lock(&pd->lock);
	gen6_क्रम_each_pde(pt, pd, start, length, pde) अणु
		स्थिर अचिन्हित पूर्णांक count = gen6_pte_count(start, length);

		अगर (!pt) अणु
			spin_unlock(&pd->lock);

			pt = stash->pt[0];
			__i915_gem_object_pin_pages(pt->base);
			i915_gem_object_make_unshrinkable(pt->base);

			fill32_px(pt, vm->scratch[0]->encode);

			spin_lock(&pd->lock);
			अगर (!pd->entry[pde]) अणु
				stash->pt[0] = pt->stash;
				atomic_set(&pt->used, 0);
				pd->entry[pde] = pt;
			पूर्ण अन्यथा अणु
				pt = pd->entry[pde];
			पूर्ण

			flush = true;
		पूर्ण

		atomic_add(count, &pt->used);
	पूर्ण
	spin_unlock(&pd->lock);

	अगर (flush && i915_vma_is_bound(ppgtt->vma, I915_VMA_GLOBAL_BIND)) अणु
		पूर्णांकel_wakeref_t wakeref;

		with_पूर्णांकel_runसमय_pm(&vm->i915->runसमय_pm, wakeref)
			gen6_flush_pd(ppgtt, from, start);
	पूर्ण
पूर्ण

अटल पूर्णांक gen6_ppgtt_init_scratch(काष्ठा gen6_ppgtt *ppgtt)
अणु
	काष्ठा i915_address_space * स्थिर vm = &ppgtt->base.vm;
	पूर्णांक ret;

	ret = setup_scratch_page(vm);
	अगर (ret)
		वापस ret;

	vm->scratch[0]->encode =
		vm->pte_encode(px_dma(vm->scratch[0]),
			       I915_CACHE_NONE, PTE_READ_ONLY);

	vm->scratch[1] = vm->alloc_pt_dma(vm, I915_GTT_PAGE_SIZE_4K);
	अगर (IS_ERR(vm->scratch[1])) अणु
		ret = PTR_ERR(vm->scratch[1]);
		जाओ err_scratch0;
	पूर्ण

	ret = pin_pt_dma(vm, vm->scratch[1]);
	अगर (ret)
		जाओ err_scratch1;

	fill32_px(vm->scratch[1], vm->scratch[0]->encode);

	वापस 0;

err_scratch1:
	i915_gem_object_put(vm->scratch[1]);
err_scratch0:
	i915_gem_object_put(vm->scratch[0]);
	वापस ret;
पूर्ण

अटल व्योम gen6_ppgtt_मुक्त_pd(काष्ठा gen6_ppgtt *ppgtt)
अणु
	काष्ठा i915_page_directory * स्थिर pd = ppgtt->base.pd;
	काष्ठा i915_page_table *pt;
	u32 pde;

	gen6_क्रम_all_pdes(pt, pd, pde)
		अगर (pt)
			मुक्त_pt(&ppgtt->base.vm, pt);
पूर्ण

अटल व्योम gen6_ppgtt_cleanup(काष्ठा i915_address_space *vm)
अणु
	काष्ठा gen6_ppgtt *ppgtt = to_gen6_ppgtt(i915_vm_to_ppgtt(vm));

	__i915_vma_put(ppgtt->vma);

	gen6_ppgtt_मुक्त_pd(ppgtt);
	मुक्त_scratch(vm);

	mutex_destroy(&ppgtt->flush);
	mutex_destroy(&ppgtt->pin_mutex);

	मुक्त_pd(&ppgtt->base.vm, ppgtt->base.pd);
पूर्ण

अटल पूर्णांक pd_vma_set_pages(काष्ठा i915_vma *vma)
अणु
	vma->pages = ERR_PTR(-ENODEV);
	वापस 0;
पूर्ण

अटल व्योम pd_vma_clear_pages(काष्ठा i915_vma *vma)
अणु
	GEM_BUG_ON(!vma->pages);

	vma->pages = शून्य;
पूर्ण

अटल व्योम pd_vma_bind(काष्ठा i915_address_space *vm,
			काष्ठा i915_vm_pt_stash *stash,
			काष्ठा i915_vma *vma,
			क्रमागत i915_cache_level cache_level,
			u32 unused)
अणु
	काष्ठा i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	काष्ठा gen6_ppgtt *ppgtt = vma->निजी;
	u32 ggtt_offset = i915_ggtt_offset(vma) / I915_GTT_PAGE_SIZE;

	ppgtt->pp_dir = ggtt_offset * माप(gen6_pte_t) << 10;
	ppgtt->pd_addr = (gen6_pte_t __iomem *)ggtt->gsm + ggtt_offset;

	gen6_flush_pd(ppgtt, 0, ppgtt->base.vm.total);
पूर्ण

अटल व्योम pd_vma_unbind(काष्ठा i915_address_space *vm, काष्ठा i915_vma *vma)
अणु
	काष्ठा gen6_ppgtt *ppgtt = vma->निजी;
	काष्ठा i915_page_directory * स्थिर pd = ppgtt->base.pd;
	काष्ठा i915_page_table *pt;
	अचिन्हित पूर्णांक pde;

	अगर (!ppgtt->scan_क्रम_unused_pt)
		वापस;

	/* Free all no दीर्घer used page tables */
	gen6_क्रम_all_pdes(pt, ppgtt->base.pd, pde) अणु
		अगर (!pt || atomic_पढ़ो(&pt->used))
			जारी;

		मुक्त_pt(&ppgtt->base.vm, pt);
		pd->entry[pde] = शून्य;
	पूर्ण

	ppgtt->scan_क्रम_unused_pt = false;
पूर्ण

अटल स्थिर काष्ठा i915_vma_ops pd_vma_ops = अणु
	.set_pages = pd_vma_set_pages,
	.clear_pages = pd_vma_clear_pages,
	.bind_vma = pd_vma_bind,
	.unbind_vma = pd_vma_unbind,
पूर्ण;

अटल काष्ठा i915_vma *pd_vma_create(काष्ठा gen6_ppgtt *ppgtt, पूर्णांक size)
अणु
	काष्ठा i915_ggtt *ggtt = ppgtt->base.vm.gt->ggtt;
	काष्ठा i915_vma *vma;

	GEM_BUG_ON(!IS_ALIGNED(size, I915_GTT_PAGE_SIZE));
	GEM_BUG_ON(size > ggtt->vm.total);

	vma = i915_vma_alloc();
	अगर (!vma)
		वापस ERR_PTR(-ENOMEM);

	i915_active_init(&vma->active, शून्य, शून्य);

	kref_init(&vma->ref);
	mutex_init(&vma->pages_mutex);
	vma->vm = i915_vm_get(&ggtt->vm);
	vma->ops = &pd_vma_ops;
	vma->निजी = ppgtt;

	vma->size = size;
	vma->fence_size = size;
	atomic_set(&vma->flags, I915_VMA_GGTT);
	vma->ggtt_view.type = I915_GGTT_VIEW_ROTATED; /* prevent fencing */

	INIT_LIST_HEAD(&vma->obj_link);
	INIT_LIST_HEAD(&vma->बंदd_link);

	वापस vma;
पूर्ण

पूर्णांक gen6_ppgtt_pin(काष्ठा i915_ppgtt *base, काष्ठा i915_gem_ww_ctx *ww)
अणु
	काष्ठा gen6_ppgtt *ppgtt = to_gen6_ppgtt(base);
	पूर्णांक err;

	GEM_BUG_ON(!atomic_पढ़ो(&ppgtt->base.vm.खोलो));

	/*
	 * Workaround the limited maximum vma->pin_count and the aliasing_ppgtt
	 * which will be pinned पूर्णांकo every active context.
	 * (When vma->pin_count becomes atomic, I expect we will naturally
	 * need a larger, unpacked, type and समाप्त this redundancy.)
	 */
	अगर (atomic_add_unless(&ppgtt->pin_count, 1, 0))
		वापस 0;

	अगर (mutex_lock_पूर्णांकerruptible(&ppgtt->pin_mutex))
		वापस -EINTR;

	/*
	 * PPGTT PDEs reside in the GGTT and consists of 512 entries. The
	 * allocator works in address space sizes, so it's multiplied by page
	 * size. We allocate at the top of the GTT to aव्योम fragmentation.
	 */
	err = 0;
	अगर (!atomic_पढ़ो(&ppgtt->pin_count))
		err = i915_ggtt_pin(ppgtt->vma, ww, GEN6_PD_ALIGN, PIN_HIGH);
	अगर (!err)
		atomic_inc(&ppgtt->pin_count);
	mutex_unlock(&ppgtt->pin_mutex);

	वापस err;
पूर्ण

व्योम gen6_ppgtt_unpin(काष्ठा i915_ppgtt *base)
अणु
	काष्ठा gen6_ppgtt *ppgtt = to_gen6_ppgtt(base);

	GEM_BUG_ON(!atomic_पढ़ो(&ppgtt->pin_count));
	अगर (atomic_dec_and_test(&ppgtt->pin_count))
		i915_vma_unpin(ppgtt->vma);
पूर्ण

व्योम gen6_ppgtt_unpin_all(काष्ठा i915_ppgtt *base)
अणु
	काष्ठा gen6_ppgtt *ppgtt = to_gen6_ppgtt(base);

	अगर (!atomic_पढ़ो(&ppgtt->pin_count))
		वापस;

	i915_vma_unpin(ppgtt->vma);
	atomic_set(&ppgtt->pin_count, 0);
पूर्ण

काष्ठा i915_ppgtt *gen6_ppgtt_create(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा i915_ggtt * स्थिर ggtt = gt->ggtt;
	काष्ठा gen6_ppgtt *ppgtt;
	पूर्णांक err;

	ppgtt = kzalloc(माप(*ppgtt), GFP_KERNEL);
	अगर (!ppgtt)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&ppgtt->flush);
	mutex_init(&ppgtt->pin_mutex);

	ppgtt_init(&ppgtt->base, gt);
	ppgtt->base.vm.pd_shअगरt = ilog2(SZ_4K * SZ_4K / माप(gen6_pte_t));
	ppgtt->base.vm.top = 1;

	ppgtt->base.vm.bind_async_flags = I915_VMA_LOCAL_BIND;
	ppgtt->base.vm.allocate_va_range = gen6_alloc_va_range;
	ppgtt->base.vm.clear_range = gen6_ppgtt_clear_range;
	ppgtt->base.vm.insert_entries = gen6_ppgtt_insert_entries;
	ppgtt->base.vm.cleanup = gen6_ppgtt_cleanup;

	ppgtt->base.vm.alloc_pt_dma = alloc_pt_dma;
	ppgtt->base.vm.pte_encode = ggtt->vm.pte_encode;

	ppgtt->base.pd = __alloc_pd(I915_PDES);
	अगर (!ppgtt->base.pd) अणु
		err = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	err = gen6_ppgtt_init_scratch(ppgtt);
	अगर (err)
		जाओ err_pd;

	ppgtt->vma = pd_vma_create(ppgtt, GEN6_PD_SIZE);
	अगर (IS_ERR(ppgtt->vma)) अणु
		err = PTR_ERR(ppgtt->vma);
		जाओ err_scratch;
	पूर्ण

	वापस &ppgtt->base;

err_scratch:
	मुक्त_scratch(&ppgtt->base.vm);
err_pd:
	मुक्त_pd(&ppgtt->base.vm, ppgtt->base.pd);
err_मुक्त:
	mutex_destroy(&ppgtt->pin_mutex);
	kमुक्त(ppgtt);
	वापस ERR_PTR(err);
पूर्ण
