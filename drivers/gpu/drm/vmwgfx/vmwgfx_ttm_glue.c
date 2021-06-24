<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2009-2011 VMware, Inc., Palo Alto, CA., USA
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

#समावेश "vmwgfx_drv.h"

पूर्णांक vmw_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	अटल स्थिर काष्ठा vm_operations_काष्ठा vmw_vm_ops = अणु
		.pfn_mkग_लिखो = vmw_bo_vm_mkग_लिखो,
		.page_mkग_लिखो = vmw_bo_vm_mkग_लिखो,
		.fault = vmw_bo_vm_fault,
		.खोलो = tपंचांग_bo_vm_खोलो,
		.बंद = tपंचांग_bo_vm_बंद,
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
		.huge_fault = vmw_bo_vm_huge_fault,
#पूर्ण_अगर
	पूर्ण;
	काष्ठा drm_file *file_priv = filp->निजी_data;
	काष्ठा vmw_निजी *dev_priv = vmw_priv(file_priv->minor->dev);
	पूर्णांक ret = tपंचांग_bo_mmap(filp, vma, &dev_priv->bdev);

	अगर (ret)
		वापस ret;

	vma->vm_ops = &vmw_vm_ops;

	/* Use VM_PFNMAP rather than VM_MIXEDMAP अगर not a COW mapping */
	अगर (!is_cow_mapping(vma->vm_flags))
		vma->vm_flags = (vma->vm_flags & ~VM_MIXEDMAP) | VM_PFNMAP;

	वापस 0;
पूर्ण

/* काष्ठा vmw_validation_mem callback */
अटल पूर्णांक vmw_vmt_reserve(काष्ठा vmw_validation_mem *m, माप_प्रकार size)
अणु
	अटल काष्ठा tपंचांग_operation_ctx ctx = अणु.पूर्णांकerruptible = false,
					       .no_रुको_gpu = falseपूर्ण;
	काष्ठा vmw_निजी *dev_priv = container_of(m, काष्ठा vmw_निजी, vvm);

	वापस tपंचांग_mem_global_alloc(vmw_mem_glob(dev_priv), size, &ctx);
पूर्ण

/* काष्ठा vmw_validation_mem callback */
अटल व्योम vmw_vmt_unreserve(काष्ठा vmw_validation_mem *m, माप_प्रकार size)
अणु
	काष्ठा vmw_निजी *dev_priv = container_of(m, काष्ठा vmw_निजी, vvm);

	वापस tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv), size);
पूर्ण

/**
 * vmw_validation_mem_init_tपंचांग - Interface the validation memory tracker
 * to tपंचांग.
 * @dev_priv: Poपूर्णांकer to काष्ठा vmw_निजी. The reason we choose a vmw निजी
 * rather than a काष्ठा vmw_validation_mem is to make sure assumption in the
 * callbacks that काष्ठा vmw_निजी derives from काष्ठा vmw_validation_mem
 * holds true.
 * @gran: The recommended allocation granularity
 */
व्योम vmw_validation_mem_init_tपंचांग(काष्ठा vmw_निजी *dev_priv, माप_प्रकार gran)
अणु
	काष्ठा vmw_validation_mem *vvm = &dev_priv->vvm;

	vvm->reserve_mem = vmw_vmt_reserve;
	vvm->unreserve_mem = vmw_vmt_unreserve;
	vvm->gran = gran;
पूर्ण
