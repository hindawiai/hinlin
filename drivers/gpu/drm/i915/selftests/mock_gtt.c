<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#समावेश "mock_gtt.h"

अटल व्योम mock_insert_page(काष्ठा i915_address_space *vm,
			     dma_addr_t addr,
			     u64 offset,
			     क्रमागत i915_cache_level level,
			     u32 flags)
अणु
पूर्ण

अटल व्योम mock_insert_entries(काष्ठा i915_address_space *vm,
				काष्ठा i915_vma *vma,
				क्रमागत i915_cache_level level, u32 flags)
अणु
पूर्ण

अटल व्योम mock_bind_ppgtt(काष्ठा i915_address_space *vm,
			    काष्ठा i915_vm_pt_stash *stash,
			    काष्ठा i915_vma *vma,
			    क्रमागत i915_cache_level cache_level,
			    u32 flags)
अणु
	GEM_BUG_ON(flags & I915_VMA_GLOBAL_BIND);
	set_bit(I915_VMA_LOCAL_BIND_BIT, __i915_vma_flags(vma));
पूर्ण

अटल व्योम mock_unbind_ppgtt(काष्ठा i915_address_space *vm,
			      काष्ठा i915_vma *vma)
अणु
पूर्ण

अटल व्योम mock_cleanup(काष्ठा i915_address_space *vm)
अणु
पूर्ण

अटल व्योम mock_clear_range(काष्ठा i915_address_space *vm,
			     u64 start, u64 length)
अणु
पूर्ण

काष्ठा i915_ppgtt *mock_ppgtt(काष्ठा drm_i915_निजी *i915, स्थिर अक्षर *name)
अणु
	काष्ठा i915_ppgtt *ppgtt;

	ppgtt = kzalloc(माप(*ppgtt), GFP_KERNEL);
	अगर (!ppgtt)
		वापस शून्य;

	ppgtt->vm.gt = &i915->gt;
	ppgtt->vm.i915 = i915;
	ppgtt->vm.total = round_करोwn(U64_MAX, PAGE_SIZE);
	ppgtt->vm.file = ERR_PTR(-ENODEV);
	ppgtt->vm.dma = i915->drm.dev;

	i915_address_space_init(&ppgtt->vm, VM_CLASS_PPGTT);

	ppgtt->vm.alloc_pt_dma = alloc_pt_dma;

	ppgtt->vm.clear_range = mock_clear_range;
	ppgtt->vm.insert_page = mock_insert_page;
	ppgtt->vm.insert_entries = mock_insert_entries;
	ppgtt->vm.cleanup = mock_cleanup;

	ppgtt->vm.vma_ops.bind_vma    = mock_bind_ppgtt;
	ppgtt->vm.vma_ops.unbind_vma  = mock_unbind_ppgtt;
	ppgtt->vm.vma_ops.set_pages   = ppgtt_set_pages;
	ppgtt->vm.vma_ops.clear_pages = clear_pages;

	वापस ppgtt;
पूर्ण

अटल व्योम mock_bind_ggtt(काष्ठा i915_address_space *vm,
			   काष्ठा i915_vm_pt_stash *stash,
			   काष्ठा i915_vma *vma,
			   क्रमागत i915_cache_level cache_level,
			   u32 flags)
अणु
पूर्ण

अटल व्योम mock_unbind_ggtt(काष्ठा i915_address_space *vm,
			     काष्ठा i915_vma *vma)
अणु
पूर्ण

व्योम mock_init_ggtt(काष्ठा drm_i915_निजी *i915, काष्ठा i915_ggtt *ggtt)
अणु
	स_रखो(ggtt, 0, माप(*ggtt));

	ggtt->vm.gt = &i915->gt;
	ggtt->vm.i915 = i915;
	ggtt->vm.is_ggtt = true;

	ggtt->gmadr = (काष्ठा resource) DEFINE_RES_MEM(0, 2048 * PAGE_SIZE);
	ggtt->mappable_end = resource_size(&ggtt->gmadr);
	ggtt->vm.total = 4096 * PAGE_SIZE;

	ggtt->vm.alloc_pt_dma = alloc_pt_dma;

	ggtt->vm.clear_range = mock_clear_range;
	ggtt->vm.insert_page = mock_insert_page;
	ggtt->vm.insert_entries = mock_insert_entries;
	ggtt->vm.cleanup = mock_cleanup;

	ggtt->vm.vma_ops.bind_vma    = mock_bind_ggtt;
	ggtt->vm.vma_ops.unbind_vma  = mock_unbind_ggtt;
	ggtt->vm.vma_ops.set_pages   = ggtt_set_pages;
	ggtt->vm.vma_ops.clear_pages = clear_pages;

	i915_address_space_init(&ggtt->vm, VM_CLASS_GGTT);
	i915->gt.ggtt = ggtt;
पूर्ण

व्योम mock_fini_ggtt(काष्ठा i915_ggtt *ggtt)
अणु
	i915_address_space_fini(&ggtt->vm);
पूर्ण
