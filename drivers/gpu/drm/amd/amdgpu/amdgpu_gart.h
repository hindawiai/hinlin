<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __AMDGPU_GART_H__
#घोषणा __AMDGPU_GART_H__

#समावेश <linux/types.h>

/*
 * GART काष्ठाures, functions & helpers
 */
काष्ठा amdgpu_device;
काष्ठा amdgpu_bo;

#घोषणा AMDGPU_GPU_PAGE_SIZE 4096
#घोषणा AMDGPU_GPU_PAGE_MASK (AMDGPU_GPU_PAGE_SIZE - 1)
#घोषणा AMDGPU_GPU_PAGE_SHIFT 12
#घोषणा AMDGPU_GPU_PAGE_ALIGN(a) (((a) + AMDGPU_GPU_PAGE_MASK) & ~AMDGPU_GPU_PAGE_MASK)

#घोषणा AMDGPU_GPU_PAGES_IN_CPU_PAGE (PAGE_SIZE / AMDGPU_GPU_PAGE_SIZE)

काष्ठा amdgpu_gart अणु
	काष्ठा amdgpu_bo		*bo;
	/* CPU kmapped address of gart table */
	व्योम				*ptr;
	अचिन्हित			num_gpu_pages;
	अचिन्हित			num_cpu_pages;
	अचिन्हित			table_size;
	bool				पढ़ोy;

	/* Asic शेष pte flags */
	uपूर्णांक64_t			gart_pte_flags;
पूर्ण;

पूर्णांक amdgpu_gart_table_vram_alloc(काष्ठा amdgpu_device *adev);
व्योम amdgpu_gart_table_vram_मुक्त(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_gart_table_vram_pin(काष्ठा amdgpu_device *adev);
व्योम amdgpu_gart_table_vram_unpin(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_gart_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_gart_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_gart_unbind(काष्ठा amdgpu_device *adev, uपूर्णांक64_t offset,
		       पूर्णांक pages);
पूर्णांक amdgpu_gart_map(काष्ठा amdgpu_device *adev, uपूर्णांक64_t offset,
		    पूर्णांक pages, dma_addr_t *dma_addr, uपूर्णांक64_t flags,
		    व्योम *dst);
पूर्णांक amdgpu_gart_bind(काष्ठा amdgpu_device *adev, uपूर्णांक64_t offset,
		     पूर्णांक pages, काष्ठा page **pagelist,
		     dma_addr_t *dma_addr, uपूर्णांक64_t flags);

#पूर्ण_अगर
