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
#अगर_अघोषित __AMDGPU_IDS_H__
#घोषणा __AMDGPU_IDS_H__

#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/dma-fence.h>

#समावेश "amdgpu_sync.h"

/* maximum number of VMIDs */
#घोषणा AMDGPU_NUM_VMID	16

काष्ठा amdgpu_device;
काष्ठा amdgpu_vm;
काष्ठा amdgpu_ring;
काष्ठा amdgpu_sync;
काष्ठा amdgpu_job;

काष्ठा amdgpu_vmid अणु
	काष्ठा list_head	list;
	काष्ठा amdgpu_sync	active;
	काष्ठा dma_fence	*last_flush;
	uपूर्णांक64_t		owner;

	uपूर्णांक64_t		pd_gpu_addr;
	/* last flushed PD/PT update */
	काष्ठा dma_fence	*flushed_updates;

	uपूर्णांक32_t                current_gpu_reset_count;

	uपूर्णांक32_t		gds_base;
	uपूर्णांक32_t		gds_size;
	uपूर्णांक32_t		gws_base;
	uपूर्णांक32_t		gws_size;
	uपूर्णांक32_t		oa_base;
	uपूर्णांक32_t		oa_size;

	अचिन्हित		pasid;
	काष्ठा dma_fence	*pasid_mapping;
पूर्ण;

काष्ठा amdgpu_vmid_mgr अणु
	काष्ठा mutex		lock;
	अचिन्हित		num_ids;
	काष्ठा list_head	ids_lru;
	काष्ठा amdgpu_vmid	ids[AMDGPU_NUM_VMID];
	atomic_t		reserved_vmid_num;
पूर्ण;

पूर्णांक amdgpu_pasid_alloc(अचिन्हित पूर्णांक bits);
व्योम amdgpu_pasid_मुक्त(u32 pasid);
व्योम amdgpu_pasid_मुक्त_delayed(काष्ठा dma_resv *resv,
			       u32 pasid);

bool amdgpu_vmid_had_gpu_reset(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_vmid *id);
पूर्णांक amdgpu_vmid_alloc_reserved(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_vm *vm,
			       अचिन्हित vmhub);
व्योम amdgpu_vmid_मुक्त_reserved(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_vm *vm,
			       अचिन्हित vmhub);
पूर्णांक amdgpu_vmid_grab(काष्ठा amdgpu_vm *vm, काष्ठा amdgpu_ring *ring,
		     काष्ठा amdgpu_sync *sync, काष्ठा dma_fence *fence,
		     काष्ठा amdgpu_job *job);
व्योम amdgpu_vmid_reset(काष्ठा amdgpu_device *adev, अचिन्हित vmhub,
		       अचिन्हित vmid);
व्योम amdgpu_vmid_reset_all(काष्ठा amdgpu_device *adev);

व्योम amdgpu_vmid_mgr_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_vmid_mgr_fini(काष्ठा amdgpu_device *adev);

#पूर्ण_अगर
