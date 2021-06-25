<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __AMDGPU_DMA_BUF_H__
#घोषणा __AMDGPU_DMA_BUF_H__

#समावेश <drm/drm_gem.h>

काष्ठा dma_buf *amdgpu_gem_prime_export(काष्ठा drm_gem_object *gobj,
					पूर्णांक flags);
काष्ठा drm_gem_object *amdgpu_gem_prime_import(काष्ठा drm_device *dev,
					    काष्ठा dma_buf *dma_buf);
bool amdgpu_dmabuf_is_xgmi_accessible(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_bo *bo);
पूर्णांक amdgpu_gem_prime_mmap(काष्ठा drm_gem_object *obj,
			  काष्ठा vm_area_काष्ठा *vma);

बाह्य स्थिर काष्ठा dma_buf_ops amdgpu_dmabuf_ops;

#पूर्ण_अगर
