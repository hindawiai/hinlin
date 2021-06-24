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
 * Authors: Christian Kथघnig
 */
#अगर_अघोषित __AMDGPU_SYNC_H__
#घोषणा __AMDGPU_SYNC_H__

#समावेश <linux/hashtable.h>

काष्ठा dma_fence;
काष्ठा dma_resv;
काष्ठा amdgpu_device;
काष्ठा amdgpu_ring;

क्रमागत amdgpu_sync_mode अणु
	AMDGPU_SYNC_ALWAYS,
	AMDGPU_SYNC_NE_OWNER,
	AMDGPU_SYNC_EQ_OWNER,
	AMDGPU_SYNC_EXPLICIT
पूर्ण;

/*
 * Container क्रम fences used to sync command submissions.
 */
काष्ठा amdgpu_sync अणु
	DECLARE_HASHTABLE(fences, 4);
	काष्ठा dma_fence	*last_vm_update;
पूर्ण;

व्योम amdgpu_sync_create(काष्ठा amdgpu_sync *sync);
पूर्णांक amdgpu_sync_fence(काष्ठा amdgpu_sync *sync, काष्ठा dma_fence *f);
पूर्णांक amdgpu_sync_vm_fence(काष्ठा amdgpu_sync *sync, काष्ठा dma_fence *fence);
पूर्णांक amdgpu_sync_resv(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_sync *sync,
		     काष्ठा dma_resv *resv, क्रमागत amdgpu_sync_mode mode,
		     व्योम *owner);
काष्ठा dma_fence *amdgpu_sync_peek_fence(काष्ठा amdgpu_sync *sync,
				     काष्ठा amdgpu_ring *ring);
काष्ठा dma_fence *amdgpu_sync_get_fence(काष्ठा amdgpu_sync *sync);
पूर्णांक amdgpu_sync_clone(काष्ठा amdgpu_sync *source, काष्ठा amdgpu_sync *clone);
पूर्णांक amdgpu_sync_रुको(काष्ठा amdgpu_sync *sync, bool पूर्णांकr);
व्योम amdgpu_sync_मुक्त(काष्ठा amdgpu_sync *sync);
पूर्णांक amdgpu_sync_init(व्योम);
व्योम amdgpu_sync_fini(व्योम);

#पूर्ण_अगर
