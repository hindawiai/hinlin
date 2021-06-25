<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <linux/log2.h>

#समावेश "gem/i915_gem_lmem.h"

#समावेश "gen8_ppgtt.h"
#समावेश "i915_scatterlist.h"
#समावेश "i915_trace.h"
#समावेश "i915_pvinfo.h"
#समावेश "i915_vgpu.h"
#समावेश "intel_gt.h"
#समावेश "intel_gtt.h"

अटल u64 gen8_pde_encode(स्थिर dma_addr_t addr,
			   स्थिर क्रमागत i915_cache_level level)
अणु
	u64 pde = addr | _PAGE_PRESENT | _PAGE_RW;

	अगर (level != I915_CACHE_NONE)
		pde |= PPAT_CACHED_PDE;
	अन्यथा
		pde |= PPAT_UNCACHED;

	वापस pde;
पूर्ण

अटल u64 gen8_pte_encode(dma_addr_t addr,
			   क्रमागत i915_cache_level level,
			   u32 flags)
अणु
	gen8_pte_t pte = addr | _PAGE_PRESENT | _PAGE_RW;

	अगर (unlikely(flags & PTE_READ_ONLY))
		pte &= ~_PAGE_RW;

	अगर (flags & PTE_LM)
		pte |= GEN12_PPGTT_PTE_LM;

	चयन (level) अणु
	हाल I915_CACHE_NONE:
		pte |= PPAT_UNCACHED;
		अवरोध;
	हाल I915_CACHE_WT:
		pte |= PPAT_DISPLAY_ELLC;
		अवरोध;
	शेष:
		pte |= PPAT_CACHED;
		अवरोध;
	पूर्ण

	वापस pte;
पूर्ण

अटल व्योम gen8_ppgtt_notअगरy_vgt(काष्ठा i915_ppgtt *ppgtt, bool create)
अणु
	काष्ठा drm_i915_निजी *i915 = ppgtt->vm.i915;
	काष्ठा पूर्णांकel_uncore *uncore = ppgtt->vm.gt->uncore;
	क्रमागत vgt_g2v_type msg;
	पूर्णांक i;

	अगर (create)
		atomic_inc(px_used(ppgtt->pd)); /* never हटाओ */
	अन्यथा
		atomic_dec(px_used(ppgtt->pd));

	mutex_lock(&i915->vgpu.lock);

	अगर (i915_vm_is_4lvl(&ppgtt->vm)) अणु
		स्थिर u64 daddr = px_dma(ppgtt->pd);

		पूर्णांकel_uncore_ग_लिखो(uncore,
				   vgtअगर_reg(pdp[0].lo), lower_32_bits(daddr));
		पूर्णांकel_uncore_ग_लिखो(uncore,
				   vgtअगर_reg(pdp[0].hi), upper_32_bits(daddr));

		msg = create ?
			VGT_G2V_PPGTT_L4_PAGE_TABLE_CREATE :
			VGT_G2V_PPGTT_L4_PAGE_TABLE_DESTROY;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < GEN8_3LVL_PDPES; i++) अणु
			स्थिर u64 daddr = i915_page_dir_dma_addr(ppgtt, i);

			पूर्णांकel_uncore_ग_लिखो(uncore,
					   vgtअगर_reg(pdp[i].lo),
					   lower_32_bits(daddr));
			पूर्णांकel_uncore_ग_लिखो(uncore,
					   vgtअगर_reg(pdp[i].hi),
					   upper_32_bits(daddr));
		पूर्ण

		msg = create ?
			VGT_G2V_PPGTT_L3_PAGE_TABLE_CREATE :
			VGT_G2V_PPGTT_L3_PAGE_TABLE_DESTROY;
	पूर्ण

	/* g2v_notअगरy atomically (via hv trap) consumes the message packet. */
	पूर्णांकel_uncore_ग_लिखो(uncore, vgtअगर_reg(g2v_notअगरy), msg);

	mutex_unlock(&i915->vgpu.lock);
पूर्ण

/* Index shअगरts पूर्णांकo the pagetable are offset by GEN8_PTE_SHIFT [12] */
#घोषणा GEN8_PAGE_SIZE (SZ_4K) /* page and page-directory sizes are the same */
#घोषणा GEN8_PTE_SHIFT (ilog2(GEN8_PAGE_SIZE))
#घोषणा GEN8_PDES (GEN8_PAGE_SIZE / माप(u64))
#घोषणा gen8_pd_shअगरt(lvl) ((lvl) * ilog2(GEN8_PDES))
#घोषणा gen8_pd_index(i, lvl) i915_pde_index((i), gen8_pd_shअगरt(lvl))
#घोषणा __gen8_pte_shअगरt(lvl) (GEN8_PTE_SHIFT + gen8_pd_shअगरt(lvl))
#घोषणा __gen8_pte_index(a, lvl) i915_pde_index((a), __gen8_pte_shअगरt(lvl))

#घोषणा as_pd(x) container_of((x), typeof(काष्ठा i915_page_directory), pt)

अटल अचिन्हित पूर्णांक
gen8_pd_range(u64 start, u64 end, पूर्णांक lvl, अचिन्हित पूर्णांक *idx)
अणु
	स्थिर पूर्णांक shअगरt = gen8_pd_shअगरt(lvl);
	स्थिर u64 mask = ~0ull << gen8_pd_shअगरt(lvl + 1);

	GEM_BUG_ON(start >= end);
	end += ~mask >> gen8_pd_shअगरt(1);

	*idx = i915_pde_index(start, shअगरt);
	अगर ((start ^ end) & mask)
		वापस GEN8_PDES - *idx;
	अन्यथा
		वापस i915_pde_index(end, shअगरt) - *idx;
पूर्ण

अटल bool gen8_pd_contains(u64 start, u64 end, पूर्णांक lvl)
अणु
	स्थिर u64 mask = ~0ull << gen8_pd_shअगरt(lvl + 1);

	GEM_BUG_ON(start >= end);
	वापस (start ^ end) & mask && (start & ~mask) == 0;
पूर्ण

अटल अचिन्हित पूर्णांक gen8_pt_count(u64 start, u64 end)
अणु
	GEM_BUG_ON(start >= end);
	अगर ((start ^ end) >> gen8_pd_shअगरt(1))
		वापस GEN8_PDES - (start & (GEN8_PDES - 1));
	अन्यथा
		वापस end - start;
पूर्ण

अटल अचिन्हित पूर्णांक gen8_pd_top_count(स्थिर काष्ठा i915_address_space *vm)
अणु
	अचिन्हित पूर्णांक shअगरt = __gen8_pte_shअगरt(vm->top);

	वापस (vm->total + (1ull << shअगरt) - 1) >> shअगरt;
पूर्ण

अटल काष्ठा i915_page_directory *
gen8_pdp_क्रम_page_index(काष्ठा i915_address_space * स्थिर vm, स्थिर u64 idx)
अणु
	काष्ठा i915_ppgtt * स्थिर ppgtt = i915_vm_to_ppgtt(vm);

	अगर (vm->top == 2)
		वापस ppgtt->pd;
	अन्यथा
		वापस i915_pd_entry(ppgtt->pd, gen8_pd_index(idx, vm->top));
पूर्ण

अटल काष्ठा i915_page_directory *
gen8_pdp_क्रम_page_address(काष्ठा i915_address_space * स्थिर vm, स्थिर u64 addr)
अणु
	वापस gen8_pdp_क्रम_page_index(vm, addr >> GEN8_PTE_SHIFT);
पूर्ण

अटल व्योम __gen8_ppgtt_cleanup(काष्ठा i915_address_space *vm,
				 काष्ठा i915_page_directory *pd,
				 पूर्णांक count, पूर्णांक lvl)
अणु
	अगर (lvl) अणु
		व्योम **pde = pd->entry;

		करो अणु
			अगर (!*pde)
				जारी;

			__gen8_ppgtt_cleanup(vm, *pde, GEN8_PDES, lvl - 1);
		पूर्ण जबतक (pde++, --count);
	पूर्ण

	मुक्त_px(vm, &pd->pt, lvl);
पूर्ण

अटल व्योम gen8_ppgtt_cleanup(काष्ठा i915_address_space *vm)
अणु
	काष्ठा i915_ppgtt *ppgtt = i915_vm_to_ppgtt(vm);

	अगर (पूर्णांकel_vgpu_active(vm->i915))
		gen8_ppgtt_notअगरy_vgt(ppgtt, false);

	__gen8_ppgtt_cleanup(vm, ppgtt->pd, gen8_pd_top_count(vm), vm->top);
	मुक्त_scratch(vm);
पूर्ण

अटल u64 __gen8_ppgtt_clear(काष्ठा i915_address_space * स्थिर vm,
			      काष्ठा i915_page_directory * स्थिर pd,
			      u64 start, स्थिर u64 end, पूर्णांक lvl)
अणु
	स्थिर काष्ठा drm_i915_gem_object * स्थिर scratch = vm->scratch[lvl];
	अचिन्हित पूर्णांक idx, len;

	GEM_BUG_ON(end > vm->total >> GEN8_PTE_SHIFT);

	len = gen8_pd_range(start, end, lvl--, &idx);
	DBG("%s(%p):{ lvl:%d, start:%llx, end:%llx, idx:%d, len:%d, used:%d }\n",
	    __func__, vm, lvl + 1, start, end,
	    idx, len, atomic_पढ़ो(px_used(pd)));
	GEM_BUG_ON(!len || len >= atomic_पढ़ो(px_used(pd)));

	करो अणु
		काष्ठा i915_page_table *pt = pd->entry[idx];

		अगर (atomic_fetch_inc(&pt->used) >> gen8_pd_shअगरt(1) &&
		    gen8_pd_contains(start, end, lvl)) अणु
			DBG("%s(%p):{ lvl:%d, idx:%d, start:%llx, end:%llx } removing pd\n",
			    __func__, vm, lvl + 1, idx, start, end);
			clear_pd_entry(pd, idx, scratch);
			__gen8_ppgtt_cleanup(vm, as_pd(pt), I915_PDES, lvl);
			start += (u64)I915_PDES << gen8_pd_shअगरt(lvl);
			जारी;
		पूर्ण

		अगर (lvl) अणु
			start = __gen8_ppgtt_clear(vm, as_pd(pt),
						   start, end, lvl);
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक count;
			u64 *vaddr;

			count = gen8_pt_count(start, end);
			DBG("%s(%p):{ lvl:%d, start:%llx, end:%llx, idx:%d, len:%d, used:%d } removing pte\n",
			    __func__, vm, lvl, start, end,
			    gen8_pd_index(start, 0), count,
			    atomic_पढ़ो(&pt->used));
			GEM_BUG_ON(!count || count >= atomic_पढ़ो(&pt->used));

			vaddr = kmap_atomic_px(pt);
			स_रखो64(vaddr + gen8_pd_index(start, 0),
				 vm->scratch[0]->encode,
				 count);
			kunmap_atomic(vaddr);

			atomic_sub(count, &pt->used);
			start += count;
		पूर्ण

		अगर (release_pd_entry(pd, idx, pt, scratch))
			मुक्त_px(vm, pt, lvl);
	पूर्ण जबतक (idx++, --len);

	वापस start;
पूर्ण

अटल व्योम gen8_ppgtt_clear(काष्ठा i915_address_space *vm,
			     u64 start, u64 length)
अणु
	GEM_BUG_ON(!IS_ALIGNED(start, BIT_ULL(GEN8_PTE_SHIFT)));
	GEM_BUG_ON(!IS_ALIGNED(length, BIT_ULL(GEN8_PTE_SHIFT)));
	GEM_BUG_ON(range_overflows(start, length, vm->total));

	start >>= GEN8_PTE_SHIFT;
	length >>= GEN8_PTE_SHIFT;
	GEM_BUG_ON(length == 0);

	__gen8_ppgtt_clear(vm, i915_vm_to_ppgtt(vm)->pd,
			   start, start + length, vm->top);
पूर्ण

अटल व्योम __gen8_ppgtt_alloc(काष्ठा i915_address_space * स्थिर vm,
			       काष्ठा i915_vm_pt_stash *stash,
			       काष्ठा i915_page_directory * स्थिर pd,
			       u64 * स्थिर start, स्थिर u64 end, पूर्णांक lvl)
अणु
	अचिन्हित पूर्णांक idx, len;

	GEM_BUG_ON(end > vm->total >> GEN8_PTE_SHIFT);

	len = gen8_pd_range(*start, end, lvl--, &idx);
	DBG("%s(%p):{ lvl:%d, start:%llx, end:%llx, idx:%d, len:%d, used:%d }\n",
	    __func__, vm, lvl + 1, *start, end,
	    idx, len, atomic_पढ़ो(px_used(pd)));
	GEM_BUG_ON(!len || (idx + len - 1) >> gen8_pd_shअगरt(1));

	spin_lock(&pd->lock);
	GEM_BUG_ON(!atomic_पढ़ो(px_used(pd))); /* Must be pinned! */
	करो अणु
		काष्ठा i915_page_table *pt = pd->entry[idx];

		अगर (!pt) अणु
			spin_unlock(&pd->lock);

			DBG("%s(%p):{ lvl:%d, idx:%d } allocating new tree\n",
			    __func__, vm, lvl + 1, idx);

			pt = stash->pt[!!lvl];
			__i915_gem_object_pin_pages(pt->base);
			i915_gem_object_make_unshrinkable(pt->base);

			अगर (lvl ||
			    gen8_pt_count(*start, end) < I915_PDES ||
			    पूर्णांकel_vgpu_active(vm->i915))
				fill_px(pt, vm->scratch[lvl]->encode);

			spin_lock(&pd->lock);
			अगर (likely(!pd->entry[idx])) अणु
				stash->pt[!!lvl] = pt->stash;
				atomic_set(&pt->used, 0);
				set_pd_entry(pd, idx, pt);
			पूर्ण अन्यथा अणु
				pt = pd->entry[idx];
			पूर्ण
		पूर्ण

		अगर (lvl) अणु
			atomic_inc(&pt->used);
			spin_unlock(&pd->lock);

			__gen8_ppgtt_alloc(vm, stash,
					   as_pd(pt), start, end, lvl);

			spin_lock(&pd->lock);
			atomic_dec(&pt->used);
			GEM_BUG_ON(!atomic_पढ़ो(&pt->used));
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक count = gen8_pt_count(*start, end);

			DBG("%s(%p):{ lvl:%d, start:%llx, end:%llx, idx:%d, len:%d, used:%d } inserting pte\n",
			    __func__, vm, lvl, *start, end,
			    gen8_pd_index(*start, 0), count,
			    atomic_पढ़ो(&pt->used));

			atomic_add(count, &pt->used);
			/* All other pdes may be simultaneously हटाओd */
			GEM_BUG_ON(atomic_पढ़ो(&pt->used) > NALLOC * I915_PDES);
			*start += count;
		पूर्ण
	पूर्ण जबतक (idx++, --len);
	spin_unlock(&pd->lock);
पूर्ण

अटल व्योम gen8_ppgtt_alloc(काष्ठा i915_address_space *vm,
			     काष्ठा i915_vm_pt_stash *stash,
			     u64 start, u64 length)
अणु
	GEM_BUG_ON(!IS_ALIGNED(start, BIT_ULL(GEN8_PTE_SHIFT)));
	GEM_BUG_ON(!IS_ALIGNED(length, BIT_ULL(GEN8_PTE_SHIFT)));
	GEM_BUG_ON(range_overflows(start, length, vm->total));

	start >>= GEN8_PTE_SHIFT;
	length >>= GEN8_PTE_SHIFT;
	GEM_BUG_ON(length == 0);

	__gen8_ppgtt_alloc(vm, stash, i915_vm_to_ppgtt(vm)->pd,
			   &start, start + length, vm->top);
पूर्ण

अटल __always_अंतरभूत u64
gen8_ppgtt_insert_pte(काष्ठा i915_ppgtt *ppgtt,
		      काष्ठा i915_page_directory *pdp,
		      काष्ठा sgt_dma *iter,
		      u64 idx,
		      क्रमागत i915_cache_level cache_level,
		      u32 flags)
अणु
	काष्ठा i915_page_directory *pd;
	स्थिर gen8_pte_t pte_encode = gen8_pte_encode(0, cache_level, flags);
	gen8_pte_t *vaddr;

	pd = i915_pd_entry(pdp, gen8_pd_index(idx, 2));
	vaddr = kmap_atomic_px(i915_pt_entry(pd, gen8_pd_index(idx, 1)));
	करो अणु
		GEM_BUG_ON(sg_dma_len(iter->sg) < I915_GTT_PAGE_SIZE);
		vaddr[gen8_pd_index(idx, 0)] = pte_encode | iter->dma;

		iter->dma += I915_GTT_PAGE_SIZE;
		अगर (iter->dma >= iter->max) अणु
			iter->sg = __sg_next(iter->sg);
			अगर (!iter->sg || sg_dma_len(iter->sg) == 0) अणु
				idx = 0;
				अवरोध;
			पूर्ण

			iter->dma = sg_dma_address(iter->sg);
			iter->max = iter->dma + sg_dma_len(iter->sg);
		पूर्ण

		अगर (gen8_pd_index(++idx, 0) == 0) अणु
			अगर (gen8_pd_index(idx, 1) == 0) अणु
				/* Limited by sg length क्रम 3lvl */
				अगर (gen8_pd_index(idx, 2) == 0)
					अवरोध;

				pd = pdp->entry[gen8_pd_index(idx, 2)];
			पूर्ण

			clflush_cache_range(vaddr, PAGE_SIZE);
			kunmap_atomic(vaddr);
			vaddr = kmap_atomic_px(i915_pt_entry(pd, gen8_pd_index(idx, 1)));
		पूर्ण
	पूर्ण जबतक (1);
	clflush_cache_range(vaddr, PAGE_SIZE);
	kunmap_atomic(vaddr);

	वापस idx;
पूर्ण

अटल व्योम gen8_ppgtt_insert_huge(काष्ठा i915_vma *vma,
				   काष्ठा sgt_dma *iter,
				   क्रमागत i915_cache_level cache_level,
				   u32 flags)
अणु
	स्थिर gen8_pte_t pte_encode = gen8_pte_encode(0, cache_level, flags);
	अचिन्हित पूर्णांक rem = sg_dma_len(iter->sg);
	u64 start = vma->node.start;

	GEM_BUG_ON(!i915_vm_is_4lvl(vma->vm));

	करो अणु
		काष्ठा i915_page_directory * स्थिर pdp =
			gen8_pdp_क्रम_page_address(vma->vm, start);
		काष्ठा i915_page_directory * स्थिर pd =
			i915_pd_entry(pdp, __gen8_pte_index(start, 2));
		gen8_pte_t encode = pte_encode;
		अचिन्हित पूर्णांक maybe_64K = -1;
		अचिन्हित पूर्णांक page_size;
		gen8_pte_t *vaddr;
		u16 index;

		अगर (vma->page_sizes.sg & I915_GTT_PAGE_SIZE_2M &&
		    IS_ALIGNED(iter->dma, I915_GTT_PAGE_SIZE_2M) &&
		    rem >= I915_GTT_PAGE_SIZE_2M &&
		    !__gen8_pte_index(start, 0)) अणु
			index = __gen8_pte_index(start, 1);
			encode |= GEN8_PDE_PS_2M;
			page_size = I915_GTT_PAGE_SIZE_2M;

			vaddr = kmap_atomic_px(pd);
		पूर्ण अन्यथा अणु
			काष्ठा i915_page_table *pt =
				i915_pt_entry(pd, __gen8_pte_index(start, 1));

			index = __gen8_pte_index(start, 0);
			page_size = I915_GTT_PAGE_SIZE;

			अगर (!index &&
			    vma->page_sizes.sg & I915_GTT_PAGE_SIZE_64K &&
			    IS_ALIGNED(iter->dma, I915_GTT_PAGE_SIZE_64K) &&
			    (IS_ALIGNED(rem, I915_GTT_PAGE_SIZE_64K) ||
			     rem >= (I915_PDES - index) * I915_GTT_PAGE_SIZE))
				maybe_64K = __gen8_pte_index(start, 1);

			vaddr = kmap_atomic_px(pt);
		पूर्ण

		करो अणु
			GEM_BUG_ON(sg_dma_len(iter->sg) < page_size);
			vaddr[index++] = encode | iter->dma;

			start += page_size;
			iter->dma += page_size;
			rem -= page_size;
			अगर (iter->dma >= iter->max) अणु
				iter->sg = __sg_next(iter->sg);
				अगर (!iter->sg)
					अवरोध;

				rem = sg_dma_len(iter->sg);
				अगर (!rem)
					अवरोध;

				iter->dma = sg_dma_address(iter->sg);
				iter->max = iter->dma + rem;

				अगर (maybe_64K != -1 && index < I915_PDES &&
				    !(IS_ALIGNED(iter->dma, I915_GTT_PAGE_SIZE_64K) &&
				      (IS_ALIGNED(rem, I915_GTT_PAGE_SIZE_64K) ||
				       rem >= (I915_PDES - index) * I915_GTT_PAGE_SIZE)))
					maybe_64K = -1;

				अगर (unlikely(!IS_ALIGNED(iter->dma, page_size)))
					अवरोध;
			पूर्ण
		पूर्ण जबतक (rem >= page_size && index < I915_PDES);

		clflush_cache_range(vaddr, PAGE_SIZE);
		kunmap_atomic(vaddr);

		/*
		 * Is it safe to mark the 2M block as 64K? -- Either we have
		 * filled whole page-table with 64K entries, or filled part of
		 * it and have reached the end of the sg table and we have
		 * enough padding.
		 */
		अगर (maybe_64K != -1 &&
		    (index == I915_PDES ||
		     (i915_vm_has_scratch_64K(vma->vm) &&
		      !iter->sg && IS_ALIGNED(vma->node.start +
					      vma->node.size,
					      I915_GTT_PAGE_SIZE_2M)))) अणु
			vaddr = kmap_atomic_px(pd);
			vaddr[maybe_64K] |= GEN8_PDE_IPS_64K;
			kunmap_atomic(vaddr);
			page_size = I915_GTT_PAGE_SIZE_64K;

			/*
			 * We ग_लिखो all 4K page entries, even when using 64K
			 * pages. In order to verअगरy that the HW isn't cheating
			 * by using the 4K PTE instead of the 64K PTE, we want
			 * to हटाओ all the surplus entries. If the HW skipped
			 * the 64K PTE, it will पढ़ो/ग_लिखो पूर्णांकo the scratch page
			 * instead - which we detect as missing results during
			 * selftests.
			 */
			अगर (I915_SELFTEST_ONLY(vma->vm->scrub_64K)) अणु
				u16 i;

				encode = vma->vm->scratch[0]->encode;
				vaddr = kmap_atomic_px(i915_pt_entry(pd, maybe_64K));

				क्रम (i = 1; i < index; i += 16)
					स_रखो64(vaddr + i, encode, 15);

				kunmap_atomic(vaddr);
			पूर्ण
		पूर्ण

		vma->page_sizes.gtt |= page_size;
	पूर्ण जबतक (iter->sg && sg_dma_len(iter->sg));
पूर्ण

अटल व्योम gen8_ppgtt_insert(काष्ठा i915_address_space *vm,
			      काष्ठा i915_vma *vma,
			      क्रमागत i915_cache_level cache_level,
			      u32 flags)
अणु
	काष्ठा i915_ppgtt * स्थिर ppgtt = i915_vm_to_ppgtt(vm);
	काष्ठा sgt_dma iter = sgt_dma(vma);

	अगर (vma->page_sizes.sg > I915_GTT_PAGE_SIZE) अणु
		gen8_ppgtt_insert_huge(vma, &iter, cache_level, flags);
	पूर्ण अन्यथा  अणु
		u64 idx = vma->node.start >> GEN8_PTE_SHIFT;

		करो अणु
			काष्ठा i915_page_directory * स्थिर pdp =
				gen8_pdp_क्रम_page_index(vm, idx);

			idx = gen8_ppgtt_insert_pte(ppgtt, pdp, &iter, idx,
						    cache_level, flags);
		पूर्ण जबतक (idx);

		vma->page_sizes.gtt = I915_GTT_PAGE_SIZE;
	पूर्ण
पूर्ण

अटल पूर्णांक gen8_init_scratch(काष्ठा i915_address_space *vm)
अणु
	u32 pte_flags;
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * If everybody agrees to not to ग_लिखो पूर्णांकo the scratch page,
	 * we can reuse it क्रम all vm, keeping contexts and processes separate.
	 */
	अगर (vm->has_पढ़ो_only && vm->gt->vm && !i915_is_ggtt(vm->gt->vm)) अणु
		काष्ठा i915_address_space *clone = vm->gt->vm;

		GEM_BUG_ON(!clone->has_पढ़ो_only);

		vm->scratch_order = clone->scratch_order;
		क्रम (i = 0; i <= vm->top; i++)
			vm->scratch[i] = i915_gem_object_get(clone->scratch[i]);

		वापस 0;
	पूर्ण

	ret = setup_scratch_page(vm);
	अगर (ret)
		वापस ret;

	pte_flags = vm->has_पढ़ो_only;
	अगर (i915_gem_object_is_lmem(vm->scratch[0]))
		pte_flags |= PTE_LM;

	vm->scratch[0]->encode =
		gen8_pte_encode(px_dma(vm->scratch[0]),
				I915_CACHE_LLC, pte_flags);

	क्रम (i = 1; i <= vm->top; i++) अणु
		काष्ठा drm_i915_gem_object *obj;

		obj = vm->alloc_pt_dma(vm, I915_GTT_PAGE_SIZE_4K);
		अगर (IS_ERR(obj))
			जाओ मुक्त_scratch;

		ret = pin_pt_dma(vm, obj);
		अगर (ret) अणु
			i915_gem_object_put(obj);
			जाओ मुक्त_scratch;
		पूर्ण

		fill_px(obj, vm->scratch[i - 1]->encode);
		obj->encode = gen8_pde_encode(px_dma(obj), I915_CACHE_LLC);

		vm->scratch[i] = obj;
	पूर्ण

	वापस 0;

मुक्त_scratch:
	जबतक (i--)
		i915_gem_object_put(vm->scratch[i]);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक gen8_pपुनः_स्मृतिate_top_level_pdp(काष्ठा i915_ppgtt *ppgtt)
अणु
	काष्ठा i915_address_space *vm = &ppgtt->vm;
	काष्ठा i915_page_directory *pd = ppgtt->pd;
	अचिन्हित पूर्णांक idx;

	GEM_BUG_ON(vm->top != 2);
	GEM_BUG_ON(gen8_pd_top_count(vm) != GEN8_3LVL_PDPES);

	क्रम (idx = 0; idx < GEN8_3LVL_PDPES; idx++) अणु
		काष्ठा i915_page_directory *pde;
		पूर्णांक err;

		pde = alloc_pd(vm);
		अगर (IS_ERR(pde))
			वापस PTR_ERR(pde);

		err = pin_pt_dma(vm, pde->pt.base);
		अगर (err) अणु
			मुक्त_pd(vm, pde);
			वापस err;
		पूर्ण

		fill_px(pde, vm->scratch[1]->encode);
		set_pd_entry(pd, idx, pde);
		atomic_inc(px_used(pde)); /* keep pinned */
	पूर्ण
	wmb();

	वापस 0;
पूर्ण

अटल काष्ठा i915_page_directory *
gen8_alloc_top_pd(काष्ठा i915_address_space *vm)
अणु
	स्थिर अचिन्हित पूर्णांक count = gen8_pd_top_count(vm);
	काष्ठा i915_page_directory *pd;
	पूर्णांक err;

	GEM_BUG_ON(count > I915_PDES);

	pd = __alloc_pd(count);
	अगर (unlikely(!pd))
		वापस ERR_PTR(-ENOMEM);

	pd->pt.base = vm->alloc_pt_dma(vm, I915_GTT_PAGE_SIZE_4K);
	अगर (IS_ERR(pd->pt.base)) अणु
		err = PTR_ERR(pd->pt.base);
		pd->pt.base = शून्य;
		जाओ err_pd;
	पूर्ण

	err = pin_pt_dma(vm, pd->pt.base);
	अगर (err)
		जाओ err_pd;

	fill_page_dma(px_base(pd), vm->scratch[vm->top]->encode, count);
	atomic_inc(px_used(pd)); /* mark as pinned */
	वापस pd;

err_pd:
	मुक्त_pd(vm, pd);
	वापस ERR_PTR(err);
पूर्ण

/*
 * GEN8 legacy ppgtt programming is accomplished through a max 4 PDP रेजिस्टरs
 * with a net effect resembling a 2-level page table in normal x86 terms. Each
 * PDP represents 1GB of memory 4 * 512 * 512 * 4096 = 4GB legacy 32b address
 * space.
 *
 */
काष्ठा i915_ppgtt *gen8_ppgtt_create(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा i915_ppgtt *ppgtt;
	पूर्णांक err;

	ppgtt = kzalloc(माप(*ppgtt), GFP_KERNEL);
	अगर (!ppgtt)
		वापस ERR_PTR(-ENOMEM);

	ppgtt_init(ppgtt, gt);
	ppgtt->vm.top = i915_vm_is_4lvl(&ppgtt->vm) ? 3 : 2;
	ppgtt->vm.pd_shअगरt = ilog2(SZ_4K * SZ_4K / माप(gen8_pte_t));

	/*
	 * From bdw, there is hw support क्रम पढ़ो-only pages in the PPGTT.
	 *
	 * Gen11 has HSDES#:1807136187 unresolved. Disable ro support
	 * क्रम now.
	 *
	 * Gen12 has inherited the same पढ़ो-only fault issue from gen11.
	 */
	ppgtt->vm.has_पढ़ो_only = !IS_GEN_RANGE(gt->i915, 11, 12);

	ppgtt->vm.alloc_pt_dma = alloc_pt_dma;

	err = gen8_init_scratch(&ppgtt->vm);
	अगर (err)
		जाओ err_मुक्त;

	ppgtt->pd = gen8_alloc_top_pd(&ppgtt->vm);
	अगर (IS_ERR(ppgtt->pd)) अणु
		err = PTR_ERR(ppgtt->pd);
		जाओ err_मुक्त_scratch;
	पूर्ण

	अगर (!i915_vm_is_4lvl(&ppgtt->vm)) अणु
		err = gen8_pपुनः_स्मृतिate_top_level_pdp(ppgtt);
		अगर (err)
			जाओ err_मुक्त_pd;
	पूर्ण

	ppgtt->vm.bind_async_flags = I915_VMA_LOCAL_BIND;
	ppgtt->vm.insert_entries = gen8_ppgtt_insert;
	ppgtt->vm.allocate_va_range = gen8_ppgtt_alloc;
	ppgtt->vm.clear_range = gen8_ppgtt_clear;

	ppgtt->vm.pte_encode = gen8_pte_encode;

	अगर (पूर्णांकel_vgpu_active(gt->i915))
		gen8_ppgtt_notअगरy_vgt(ppgtt, true);

	ppgtt->vm.cleanup = gen8_ppgtt_cleanup;

	वापस ppgtt;

err_मुक्त_pd:
	__gen8_ppgtt_cleanup(&ppgtt->vm, ppgtt->pd,
			     gen8_pd_top_count(&ppgtt->vm), ppgtt->vm.top);
err_मुक्त_scratch:
	मुक्त_scratch(&ppgtt->vm);
err_मुक्त:
	kमुक्त(ppgtt);
	वापस ERR_PTR(err);
पूर्ण
