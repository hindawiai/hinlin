<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <linux/slab.h>

#समावेश "gem/i915_gem_lmem.h"

#समावेश "i915_trace.h"
#समावेश "intel_gtt.h"
#समावेश "gen6_ppgtt.h"
#समावेश "gen8_ppgtt.h"

काष्ठा i915_page_table *alloc_pt(काष्ठा i915_address_space *vm)
अणु
	काष्ठा i915_page_table *pt;

	pt = kदो_स्मृति(माप(*pt), I915_GFP_ALLOW_FAIL);
	अगर (unlikely(!pt))
		वापस ERR_PTR(-ENOMEM);

	pt->base = vm->alloc_pt_dma(vm, I915_GTT_PAGE_SIZE_4K);
	अगर (IS_ERR(pt->base)) अणु
		kमुक्त(pt);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	atomic_set(&pt->used, 0);
	वापस pt;
पूर्ण

काष्ठा i915_page_directory *__alloc_pd(पूर्णांक count)
अणु
	काष्ठा i915_page_directory *pd;

	pd = kzalloc(माप(*pd), I915_GFP_ALLOW_FAIL);
	अगर (unlikely(!pd))
		वापस शून्य;

	pd->entry = kसुस्मृति(count, माप(*pd->entry), I915_GFP_ALLOW_FAIL);
	अगर (unlikely(!pd->entry)) अणु
		kमुक्त(pd);
		वापस शून्य;
	पूर्ण

	spin_lock_init(&pd->lock);
	वापस pd;
पूर्ण

काष्ठा i915_page_directory *alloc_pd(काष्ठा i915_address_space *vm)
अणु
	काष्ठा i915_page_directory *pd;

	pd = __alloc_pd(I915_PDES);
	अगर (unlikely(!pd))
		वापस ERR_PTR(-ENOMEM);

	pd->pt.base = vm->alloc_pt_dma(vm, I915_GTT_PAGE_SIZE_4K);
	अगर (IS_ERR(pd->pt.base)) अणु
		kमुक्त(pd->entry);
		kमुक्त(pd);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस pd;
पूर्ण

व्योम मुक्त_px(काष्ठा i915_address_space *vm, काष्ठा i915_page_table *pt, पूर्णांक lvl)
अणु
	BUILD_BUG_ON(दुरत्व(काष्ठा i915_page_directory, pt));

	अगर (lvl) अणु
		काष्ठा i915_page_directory *pd =
			container_of(pt, typeof(*pd), pt);
		kमुक्त(pd->entry);
	पूर्ण

	अगर (pt->base)
		i915_gem_object_put(pt->base);

	kमुक्त(pt);
पूर्ण

अटल व्योम
ग_लिखो_dma_entry(काष्ठा drm_i915_gem_object * स्थिर pdma,
		स्थिर अचिन्हित लघु idx,
		स्थिर u64 encoded_entry)
अणु
	u64 * स्थिर vaddr = kmap_atomic(__px_page(pdma));

	vaddr[idx] = encoded_entry;
	clflush_cache_range(&vaddr[idx], माप(u64));
	kunmap_atomic(vaddr);
पूर्ण

व्योम
__set_pd_entry(काष्ठा i915_page_directory * स्थिर pd,
	       स्थिर अचिन्हित लघु idx,
	       काष्ठा i915_page_table * स्थिर to,
	       u64 (*encode)(स्थिर dma_addr_t, स्थिर क्रमागत i915_cache_level))
अणु
	/* Each thपढ़ो pre-pins the pd, and we may have a thपढ़ो per pde. */
	GEM_BUG_ON(atomic_पढ़ो(px_used(pd)) > NALLOC * I915_PDES);

	atomic_inc(px_used(pd));
	pd->entry[idx] = to;
	ग_लिखो_dma_entry(px_base(pd), idx, encode(px_dma(to), I915_CACHE_LLC));
पूर्ण

व्योम
clear_pd_entry(काष्ठा i915_page_directory * स्थिर pd,
	       स्थिर अचिन्हित लघु idx,
	       स्थिर काष्ठा drm_i915_gem_object * स्थिर scratch)
अणु
	GEM_BUG_ON(atomic_पढ़ो(px_used(pd)) == 0);

	ग_लिखो_dma_entry(px_base(pd), idx, scratch->encode);
	pd->entry[idx] = शून्य;
	atomic_dec(px_used(pd));
पूर्ण

bool
release_pd_entry(काष्ठा i915_page_directory * स्थिर pd,
		 स्थिर अचिन्हित लघु idx,
		 काष्ठा i915_page_table * स्थिर pt,
		 स्थिर काष्ठा drm_i915_gem_object * स्थिर scratch)
अणु
	bool मुक्त = false;

	अगर (atomic_add_unless(&pt->used, -1, 1))
		वापस false;

	spin_lock(&pd->lock);
	अगर (atomic_dec_and_test(&pt->used)) अणु
		clear_pd_entry(pd, idx, scratch);
		मुक्त = true;
	पूर्ण
	spin_unlock(&pd->lock);

	वापस मुक्त;
पूर्ण

पूर्णांक i915_ppgtt_init_hw(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;

	gtt_ग_लिखो_workarounds(gt);

	अगर (IS_GEN(i915, 6))
		gen6_ppgtt_enable(gt);
	अन्यथा अगर (IS_GEN(i915, 7))
		gen7_ppgtt_enable(gt);

	वापस 0;
पूर्ण

अटल काष्ठा i915_ppgtt *
__ppgtt_create(काष्ठा पूर्णांकel_gt *gt)
अणु
	अगर (INTEL_GEN(gt->i915) < 8)
		वापस gen6_ppgtt_create(gt);
	अन्यथा
		वापस gen8_ppgtt_create(gt);
पूर्ण

काष्ठा i915_ppgtt *i915_ppgtt_create(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा i915_ppgtt *ppgtt;

	ppgtt = __ppgtt_create(gt);
	अगर (IS_ERR(ppgtt))
		वापस ppgtt;

	trace_i915_ppgtt_create(&ppgtt->vm);

	वापस ppgtt;
पूर्ण

व्योम ppgtt_bind_vma(काष्ठा i915_address_space *vm,
		    काष्ठा i915_vm_pt_stash *stash,
		    काष्ठा i915_vma *vma,
		    क्रमागत i915_cache_level cache_level,
		    u32 flags)
अणु
	u32 pte_flags;

	अगर (!test_bit(I915_VMA_ALLOC_BIT, __i915_vma_flags(vma))) अणु
		vm->allocate_va_range(vm, stash, vma->node.start, vma->size);
		set_bit(I915_VMA_ALLOC_BIT, __i915_vma_flags(vma));
	पूर्ण

	/* Applicable to VLV, and gen8+ */
	pte_flags = 0;
	अगर (i915_gem_object_is_पढ़ोonly(vma->obj))
		pte_flags |= PTE_READ_ONLY;
	अगर (i915_gem_object_is_lmem(vma->obj))
		pte_flags |= PTE_LM;

	vm->insert_entries(vm, vma, cache_level, pte_flags);
	wmb();
पूर्ण

व्योम ppgtt_unbind_vma(काष्ठा i915_address_space *vm, काष्ठा i915_vma *vma)
अणु
	अगर (test_and_clear_bit(I915_VMA_ALLOC_BIT, __i915_vma_flags(vma)))
		vm->clear_range(vm, vma->node.start, vma->size);
पूर्ण

अटल अचिन्हित दीर्घ pd_count(u64 size, पूर्णांक shअगरt)
अणु
	/* Beware later misalignment */
	वापस (size + 2 * (BIT_ULL(shअगरt) - 1)) >> shअगरt;
पूर्ण

पूर्णांक i915_vm_alloc_pt_stash(काष्ठा i915_address_space *vm,
			   काष्ठा i915_vm_pt_stash *stash,
			   u64 size)
अणु
	अचिन्हित दीर्घ count;
	पूर्णांक shअगरt, n;

	shअगरt = vm->pd_shअगरt;
	अगर (!shअगरt)
		वापस 0;

	count = pd_count(size, shअगरt);
	जबतक (count--) अणु
		काष्ठा i915_page_table *pt;

		pt = alloc_pt(vm);
		अगर (IS_ERR(pt)) अणु
			i915_vm_मुक्त_pt_stash(vm, stash);
			वापस PTR_ERR(pt);
		पूर्ण

		pt->stash = stash->pt[0];
		stash->pt[0] = pt;
	पूर्ण

	क्रम (n = 1; n < vm->top; n++) अणु
		shअगरt += ilog2(I915_PDES); /* Each PD holds 512 entries */
		count = pd_count(size, shअगरt);
		जबतक (count--) अणु
			काष्ठा i915_page_directory *pd;

			pd = alloc_pd(vm);
			अगर (IS_ERR(pd)) अणु
				i915_vm_मुक्त_pt_stash(vm, stash);
				वापस PTR_ERR(pd);
			पूर्ण

			pd->pt.stash = stash->pt[1];
			stash->pt[1] = &pd->pt;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक i915_vm_pin_pt_stash(काष्ठा i915_address_space *vm,
			 काष्ठा i915_vm_pt_stash *stash)
अणु
	काष्ठा i915_page_table *pt;
	पूर्णांक n, err;

	क्रम (n = 0; n < ARRAY_SIZE(stash->pt); n++) अणु
		क्रम (pt = stash->pt[n]; pt; pt = pt->stash) अणु
			err = pin_pt_dma_locked(vm, pt->base);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम i915_vm_मुक्त_pt_stash(काष्ठा i915_address_space *vm,
			   काष्ठा i915_vm_pt_stash *stash)
अणु
	काष्ठा i915_page_table *pt;
	पूर्णांक n;

	क्रम (n = 0; n < ARRAY_SIZE(stash->pt); n++) अणु
		जबतक ((pt = stash->pt[n])) अणु
			stash->pt[n] = pt->stash;
			मुक्त_px(vm, pt, n);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक ppgtt_set_pages(काष्ठा i915_vma *vma)
अणु
	GEM_BUG_ON(vma->pages);

	vma->pages = vma->obj->mm.pages;
	vma->page_sizes = vma->obj->mm.page_sizes;

	वापस 0;
पूर्ण

व्योम ppgtt_init(काष्ठा i915_ppgtt *ppgtt, काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;

	ppgtt->vm.gt = gt;
	ppgtt->vm.i915 = i915;
	ppgtt->vm.dma = i915->drm.dev;
	ppgtt->vm.total = BIT_ULL(INTEL_INFO(i915)->ppgtt_size);

	dma_resv_init(&ppgtt->vm.resv);
	i915_address_space_init(&ppgtt->vm, VM_CLASS_PPGTT);

	ppgtt->vm.vma_ops.bind_vma    = ppgtt_bind_vma;
	ppgtt->vm.vma_ops.unbind_vma  = ppgtt_unbind_vma;
	ppgtt->vm.vma_ops.set_pages   = ppgtt_set_pages;
	ppgtt->vm.vma_ops.clear_pages = clear_pages;
पूर्ण
