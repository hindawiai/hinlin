<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <linux/slab.h> /* fault-inject.h is not standalone! */

#समावेश <linux/fault-inject.h>

#समावेश "i915_trace.h"
#समावेश "intel_gt.h"
#समावेश "intel_gtt.h"

काष्ठा drm_i915_gem_object *alloc_pt_dma(काष्ठा i915_address_space *vm, पूर्णांक sz)
अणु
	काष्ठा drm_i915_gem_object *obj;

	अगर (I915_SELFTEST_ONLY(should_fail(&vm->fault_attr, 1)))
		i915_gem_shrink_all(vm->i915);

	obj = i915_gem_object_create_पूर्णांकernal(vm->i915, sz);
	/* ensure all dma objects have the same reservation class */
	अगर (!IS_ERR(obj))
		obj->base.resv = &vm->resv;
	वापस obj;
पूर्ण

पूर्णांक pin_pt_dma(काष्ठा i915_address_space *vm, काष्ठा drm_i915_gem_object *obj)
अणु
	पूर्णांक err;

	i915_gem_object_lock(obj, शून्य);
	err = i915_gem_object_pin_pages(obj);
	i915_gem_object_unlock(obj);
	अगर (err)
		वापस err;

	i915_gem_object_make_unshrinkable(obj);
	वापस 0;
पूर्ण

पूर्णांक pin_pt_dma_locked(काष्ठा i915_address_space *vm, काष्ठा drm_i915_gem_object *obj)
अणु
	पूर्णांक err;

	err = i915_gem_object_pin_pages(obj);
	अगर (err)
		वापस err;

	i915_gem_object_make_unshrinkable(obj);
	वापस 0;
पूर्ण

व्योम __i915_vm_बंद(काष्ठा i915_address_space *vm)
अणु
	काष्ठा i915_vma *vma, *vn;

	अगर (!atomic_dec_and_mutex_lock(&vm->खोलो, &vm->mutex))
		वापस;

	list_क्रम_each_entry_safe(vma, vn, &vm->bound_list, vm_link) अणु
		काष्ठा drm_i915_gem_object *obj = vma->obj;

		/* Keep the obj (and hence the vma) alive as _we_ destroy it */
		अगर (!kref_get_unless_zero(&obj->base.refcount))
			जारी;

		atomic_and(~I915_VMA_PIN_MASK, &vma->flags);
		WARN_ON(__i915_vma_unbind(vma));
		__i915_vma_put(vma);

		i915_gem_object_put(obj);
	पूर्ण
	GEM_BUG_ON(!list_empty(&vm->bound_list));

	mutex_unlock(&vm->mutex);
पूर्ण

/* lock the vm पूर्णांकo the current ww, अगर we lock one, we lock all */
पूर्णांक i915_vm_lock_objects(काष्ठा i915_address_space *vm,
			 काष्ठा i915_gem_ww_ctx *ww)
अणु
	अगर (vm->scratch[0]->base.resv == &vm->resv) अणु
		वापस i915_gem_object_lock(vm->scratch[0], ww);
	पूर्ण अन्यथा अणु
		काष्ठा i915_ppgtt *ppgtt = i915_vm_to_ppgtt(vm);

		/* We borrowed the scratch page from ggtt, take the top level object */
		वापस i915_gem_object_lock(ppgtt->pd->pt.base, ww);
	पूर्ण
पूर्ण

व्योम i915_address_space_fini(काष्ठा i915_address_space *vm)
अणु
	drm_mm_takeकरोwn(&vm->mm);
	mutex_destroy(&vm->mutex);
पूर्ण

अटल व्योम __i915_vm_release(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा i915_address_space *vm =
		container_of(work, काष्ठा i915_address_space, rcu.work);

	vm->cleanup(vm);
	i915_address_space_fini(vm);
	dma_resv_fini(&vm->resv);

	kमुक्त(vm);
पूर्ण

व्योम i915_vm_release(काष्ठा kref *kref)
अणु
	काष्ठा i915_address_space *vm =
		container_of(kref, काष्ठा i915_address_space, ref);

	GEM_BUG_ON(i915_is_ggtt(vm));
	trace_i915_ppgtt_release(vm);

	queue_rcu_work(vm->i915->wq, &vm->rcu);
पूर्ण

व्योम i915_address_space_init(काष्ठा i915_address_space *vm, पूर्णांक subclass)
अणु
	kref_init(&vm->ref);
	INIT_RCU_WORK(&vm->rcu, __i915_vm_release);
	atomic_set(&vm->खोलो, 1);

	/*
	 * The vm->mutex must be reclaim safe (क्रम use in the shrinker).
	 * Do a dummy acquire now under fs_reclaim so that any allocation
	 * attempt holding the lock is immediately reported by lockdep.
	 */
	mutex_init(&vm->mutex);
	lockdep_set_subclass(&vm->mutex, subclass);
	i915_gem_shrinker_taपूर्णांकs_mutex(vm->i915, &vm->mutex);
	dma_resv_init(&vm->resv);

	GEM_BUG_ON(!vm->total);
	drm_mm_init(&vm->mm, 0, vm->total);
	vm->mm.head_node.color = I915_COLOR_UNEVICTABLE;

	INIT_LIST_HEAD(&vm->bound_list);
पूर्ण

व्योम clear_pages(काष्ठा i915_vma *vma)
अणु
	GEM_BUG_ON(!vma->pages);

	अगर (vma->pages != vma->obj->mm.pages) अणु
		sg_मुक्त_table(vma->pages);
		kमुक्त(vma->pages);
	पूर्ण
	vma->pages = शून्य;

	स_रखो(&vma->page_sizes, 0, माप(vma->page_sizes));
पूर्ण

dma_addr_t __px_dma(काष्ठा drm_i915_gem_object *p)
अणु
	GEM_BUG_ON(!i915_gem_object_has_pages(p));
	वापस sg_dma_address(p->mm.pages->sgl);
पूर्ण

काष्ठा page *__px_page(काष्ठा drm_i915_gem_object *p)
अणु
	GEM_BUG_ON(!i915_gem_object_has_pages(p));
	वापस sg_page(p->mm.pages->sgl);
पूर्ण

व्योम
fill_page_dma(काष्ठा drm_i915_gem_object *p, स्थिर u64 val, अचिन्हित पूर्णांक count)
अणु
	काष्ठा page *page = __px_page(p);
	व्योम *vaddr;

	vaddr = kmap(page);
	स_रखो64(vaddr, val, count);
	clflush_cache_range(vaddr, PAGE_SIZE);
	kunmap(page);
पूर्ण

अटल व्योम poison_scratch_page(काष्ठा drm_i915_gem_object *scratch)
अणु
	काष्ठा sgt_iter sgt;
	काष्ठा page *page;
	u8 val;

	val = 0;
	अगर (IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
		val = POISON_FREE;

	क्रम_each_sgt_page(page, sgt, scratch->mm.pages) अणु
		व्योम *vaddr;

		vaddr = kmap(page);
		स_रखो(vaddr, val, PAGE_SIZE);
		kunmap(page);
	पूर्ण
पूर्ण

पूर्णांक setup_scratch_page(काष्ठा i915_address_space *vm)
अणु
	अचिन्हित दीर्घ size;

	/*
	 * In order to utilize 64K pages क्रम an object with a size < 2M, we will
	 * need to support a 64K scratch page, given that every 16th entry क्रम a
	 * page-table operating in 64K mode must poपूर्णांक to a properly aligned 64K
	 * region, including any PTEs which happen to poपूर्णांक to scratch.
	 *
	 * This is only relevant क्रम the 48b PPGTT where we support
	 * huge-gtt-pages, see also i915_vma_insert(). However, as we share the
	 * scratch (पढ़ो-only) between all vm, we create one 64k scratch page
	 * क्रम all.
	 */
	size = I915_GTT_PAGE_SIZE_4K;
	अगर (i915_vm_is_4lvl(vm) &&
	    HAS_PAGE_SIZES(vm->i915, I915_GTT_PAGE_SIZE_64K))
		size = I915_GTT_PAGE_SIZE_64K;

	करो अणु
		काष्ठा drm_i915_gem_object *obj;

		obj = vm->alloc_pt_dma(vm, size);
		अगर (IS_ERR(obj))
			जाओ skip;

		अगर (pin_pt_dma(vm, obj))
			जाओ skip_obj;

		/* We need a single contiguous page क्रम our scratch */
		अगर (obj->mm.page_sizes.sg < size)
			जाओ skip_obj;

		/* And it needs to be correspondingly aligned */
		अगर (__px_dma(obj) & (size - 1))
			जाओ skip_obj;

		/*
		 * Use a non-zero scratch page क्रम debugging.
		 *
		 * We want a value that should be reasonably obvious
		 * to spot in the error state, जबतक also causing a GPU hang
		 * अगर executed. We prefer using a clear page in production, so
		 * should it ever be accidentally used, the effect should be
		 * fairly benign.
		 */
		poison_scratch_page(obj);

		vm->scratch[0] = obj;
		vm->scratch_order = get_order(size);
		वापस 0;

skip_obj:
		i915_gem_object_put(obj);
skip:
		अगर (size == I915_GTT_PAGE_SIZE_4K)
			वापस -ENOMEM;

		size = I915_GTT_PAGE_SIZE_4K;
	पूर्ण जबतक (1);
पूर्ण

व्योम मुक्त_scratch(काष्ठा i915_address_space *vm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= vm->top; i++)
		i915_gem_object_put(vm->scratch[i]);
पूर्ण

व्योम gtt_ग_लिखो_workarounds(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;

	/*
	 * This function is क्रम gtt related workarounds. This function is
	 * called on driver load and after a GPU reset, so you can place
	 * workarounds here even अगर they get overwritten by GPU reset.
	 */
	/* WaIncreaseDefaultTLBEntries:chv,bdw,skl,bxt,kbl,glk,cfl,cnl,icl */
	अगर (IS_BROADWELL(i915))
		पूर्णांकel_uncore_ग_लिखो(uncore,
				   GEN8_L3_LRA_1_GPGPU,
				   GEN8_L3_LRA_1_GPGPU_DEFAULT_VALUE_BDW);
	अन्यथा अगर (IS_CHERRYVIEW(i915))
		पूर्णांकel_uncore_ग_लिखो(uncore,
				   GEN8_L3_LRA_1_GPGPU,
				   GEN8_L3_LRA_1_GPGPU_DEFAULT_VALUE_CHV);
	अन्यथा अगर (IS_GEN9_LP(i915))
		पूर्णांकel_uncore_ग_लिखो(uncore,
				   GEN8_L3_LRA_1_GPGPU,
				   GEN9_L3_LRA_1_GPGPU_DEFAULT_VALUE_BXT);
	अन्यथा अगर (INTEL_GEN(i915) >= 9 && INTEL_GEN(i915) <= 11)
		पूर्णांकel_uncore_ग_लिखो(uncore,
				   GEN8_L3_LRA_1_GPGPU,
				   GEN9_L3_LRA_1_GPGPU_DEFAULT_VALUE_SKL);

	/*
	 * To support 64K PTEs we need to first enable the use of the
	 * Intermediate-Page-Size(IPS) bit of the PDE field via some magical
	 * mmio, otherwise the page-walker will simply ignore the IPS bit. This
	 * shouldn't be needed after GEN10.
	 *
	 * 64K pages were first पूर्णांकroduced from BDW+, although technically they
	 * only *work* from gen9+. For pre-BDW we instead have the option क्रम
	 * 32K pages, but we करोn't currently have any support क्रम it in our
	 * driver.
	 */
	अगर (HAS_PAGE_SIZES(i915, I915_GTT_PAGE_SIZE_64K) &&
	    INTEL_GEN(i915) <= 10)
		पूर्णांकel_uncore_rmw(uncore,
				 GEN8_GAMW_ECO_DEV_RW_IA,
				 0,
				 GAMW_ECO_ENABLE_64K_IPS_FIELD);

	अगर (IS_GEN_RANGE(i915, 8, 11)) अणु
		bool can_use_gtt_cache = true;

		/*
		 * According to the BSpec अगर we use 2M/1G pages then we also
		 * need to disable the GTT cache. At least on BDW we can see
		 * visual corruption when using 2M pages, and not disabling the
		 * GTT cache.
		 */
		अगर (HAS_PAGE_SIZES(i915, I915_GTT_PAGE_SIZE_2M))
			can_use_gtt_cache = false;

		/* WaGttCachingOffByDefault */
		पूर्णांकel_uncore_ग_लिखो(uncore,
				   HSW_GTT_CACHE_EN,
				   can_use_gtt_cache ? GTT_CACHE_EN_ALL : 0);
		drm_WARN_ON_ONCE(&i915->drm, can_use_gtt_cache &&
				 पूर्णांकel_uncore_पढ़ो(uncore,
						   HSW_GTT_CACHE_EN) == 0);
	पूर्ण
पूर्ण

अटल व्योम tgl_setup_निजी_ppat(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	/* TGL करोesn't support LLC or AGE settings */
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN12_PAT_INDEX(0), GEN8_PPAT_WB);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN12_PAT_INDEX(1), GEN8_PPAT_WC);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN12_PAT_INDEX(2), GEN8_PPAT_WT);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN12_PAT_INDEX(3), GEN8_PPAT_UC);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN12_PAT_INDEX(4), GEN8_PPAT_WB);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN12_PAT_INDEX(5), GEN8_PPAT_WB);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN12_PAT_INDEX(6), GEN8_PPAT_WB);
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN12_PAT_INDEX(7), GEN8_PPAT_WB);
पूर्ण

अटल व्योम cnl_setup_निजी_ppat(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	पूर्णांकel_uncore_ग_लिखो(uncore,
			   GEN10_PAT_INDEX(0),
			   GEN8_PPAT_WB | GEN8_PPAT_LLC);
	पूर्णांकel_uncore_ग_लिखो(uncore,
			   GEN10_PAT_INDEX(1),
			   GEN8_PPAT_WC | GEN8_PPAT_LLCELLC);
	पूर्णांकel_uncore_ग_लिखो(uncore,
			   GEN10_PAT_INDEX(2),
			   GEN8_PPAT_WB | GEN8_PPAT_ELLC_OVERRIDE);
	पूर्णांकel_uncore_ग_लिखो(uncore,
			   GEN10_PAT_INDEX(3),
			   GEN8_PPAT_UC);
	पूर्णांकel_uncore_ग_लिखो(uncore,
			   GEN10_PAT_INDEX(4),
			   GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(0));
	पूर्णांकel_uncore_ग_लिखो(uncore,
			   GEN10_PAT_INDEX(5),
			   GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(1));
	पूर्णांकel_uncore_ग_लिखो(uncore,
			   GEN10_PAT_INDEX(6),
			   GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(2));
	पूर्णांकel_uncore_ग_लिखो(uncore,
			   GEN10_PAT_INDEX(7),
			   GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(3));
पूर्ण

/*
 * The GGTT and PPGTT need a निजी PPAT setup in order to handle cacheability
 * bits. When using advanced contexts each context stores its own PAT, but
 * writing this data shouldn't be harmful even in those हालs.
 */
अटल व्योम bdw_setup_निजी_ppat(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	काष्ठा drm_i915_निजी *i915 = uncore->i915;
	u64 pat;

	pat = GEN8_PPAT(0, GEN8_PPAT_WB | GEN8_PPAT_LLC) |	/* क्रम normal objects, no eLLC */
	      GEN8_PPAT(1, GEN8_PPAT_WC | GEN8_PPAT_LLCELLC) |	/* क्रम something poपूर्णांकing to ptes? */
	      GEN8_PPAT(3, GEN8_PPAT_UC) |			/* Uncached objects, mostly क्रम scanout */
	      GEN8_PPAT(4, GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(0)) |
	      GEN8_PPAT(5, GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(1)) |
	      GEN8_PPAT(6, GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(2)) |
	      GEN8_PPAT(7, GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(3));

	/* क्रम scanout with eLLC */
	अगर (INTEL_GEN(i915) >= 9)
		pat |= GEN8_PPAT(2, GEN8_PPAT_WB | GEN8_PPAT_ELLC_OVERRIDE);
	अन्यथा
		pat |= GEN8_PPAT(2, GEN8_PPAT_WT | GEN8_PPAT_LLCELLC);

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN8_PRIVATE_PAT_LO, lower_32_bits(pat));
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN8_PRIVATE_PAT_HI, upper_32_bits(pat));
पूर्ण

अटल व्योम chv_setup_निजी_ppat(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	u64 pat;

	/*
	 * Map WB on BDW to snooped on CHV.
	 *
	 * Only the snoop bit has meaning क्रम CHV, the rest is
	 * ignored.
	 *
	 * The hardware will never snoop क्रम certain types of accesses:
	 * - CPU GTT (GMADR->GGTT->no snoop->memory)
	 * - PPGTT page tables
	 * - some other special cycles
	 *
	 * As with BDW, we also need to consider the following क्रम GT accesses:
	 * "For GGTT, there is NO pat_sel[2:0] from the entry,
	 * so RTL will always use the value corresponding to
	 * pat_sel = 000".
	 * Which means we must set the snoop bit in PAT entry 0
	 * in order to keep the global status page working.
	 */

	pat = GEN8_PPAT(0, CHV_PPAT_SNOOP) |
	      GEN8_PPAT(1, 0) |
	      GEN8_PPAT(2, 0) |
	      GEN8_PPAT(3, 0) |
	      GEN8_PPAT(4, CHV_PPAT_SNOOP) |
	      GEN8_PPAT(5, CHV_PPAT_SNOOP) |
	      GEN8_PPAT(6, CHV_PPAT_SNOOP) |
	      GEN8_PPAT(7, CHV_PPAT_SNOOP);

	पूर्णांकel_uncore_ग_लिखो(uncore, GEN8_PRIVATE_PAT_LO, lower_32_bits(pat));
	पूर्णांकel_uncore_ग_लिखो(uncore, GEN8_PRIVATE_PAT_HI, upper_32_bits(pat));
पूर्ण

व्योम setup_निजी_pat(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	काष्ठा drm_i915_निजी *i915 = uncore->i915;

	GEM_BUG_ON(INTEL_GEN(i915) < 8);

	अगर (INTEL_GEN(i915) >= 12)
		tgl_setup_निजी_ppat(uncore);
	अन्यथा अगर (INTEL_GEN(i915) >= 10)
		cnl_setup_निजी_ppat(uncore);
	अन्यथा अगर (IS_CHERRYVIEW(i915) || IS_GEN9_LP(i915))
		chv_setup_निजी_ppat(uncore);
	अन्यथा
		bdw_setup_निजी_ppat(uncore);
पूर्ण

काष्ठा i915_vma *
__vm_create_scratch_क्रम_पढ़ो(काष्ठा i915_address_space *vm, अचिन्हित दीर्घ size)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;

	obj = i915_gem_object_create_पूर्णांकernal(vm->i915, PAGE_ALIGN(size));
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	i915_gem_object_set_cache_coherency(obj, I915_CACHING_CACHED);

	vma = i915_vma_instance(obj, vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		i915_gem_object_put(obj);
		वापस vma;
	पूर्ण

	वापस vma;
पूर्ण

काष्ठा i915_vma *
__vm_create_scratch_क्रम_पढ़ो_pinned(काष्ठा i915_address_space *vm, अचिन्हित दीर्घ size)
अणु
	काष्ठा i915_vma *vma;
	पूर्णांक err;

	vma = __vm_create_scratch_क्रम_पढ़ो(vm, size);
	अगर (IS_ERR(vma))
		वापस vma;

	err = i915_vma_pin(vma, 0, 0,
			   i915_vma_is_ggtt(vma) ? PIN_GLOBAL : PIN_USER);
	अगर (err) अणु
		i915_vma_put(vma);
		वापस ERR_PTR(err);
	पूर्ण

	वापस vma;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/mock_gtt.c"
#पूर्ण_अगर
