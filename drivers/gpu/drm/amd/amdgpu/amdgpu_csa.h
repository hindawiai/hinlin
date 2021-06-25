<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
 * Author: Monk.liu@amd.com
 */

#अगर_अघोषित AMDGPU_CSA_MANAGER_H
#घोषणा AMDGPU_CSA_MANAGER_H

#घोषणा AMDGPU_CSA_SIZE		(128 * 1024)

uपूर्णांक32_t amdgpu_get_total_csa_size(काष्ठा amdgpu_device *adev);
uपूर्णांक64_t amdgpu_csa_vaddr(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_allocate_अटल_csa(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_bo **bo,
				u32 करोमुख्य, uपूर्णांक32_t size);
पूर्णांक amdgpu_map_अटल_csa(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_vm *vm,
			  काष्ठा amdgpu_bo *bo, काष्ठा amdgpu_bo_va **bo_va,
			  uपूर्णांक64_t csa_addr, uपूर्णांक32_t size);
व्योम amdgpu_मुक्त_अटल_csa(काष्ठा amdgpu_bo **bo);

#पूर्ण_अगर
