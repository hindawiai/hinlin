<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __AMDGPU_CTX_H__
#घोषणा __AMDGPU_CTX_H__

#समावेश "amdgpu_ring.h"

काष्ठा drm_device;
काष्ठा drm_file;
काष्ठा amdgpu_fpriv;

#घोषणा AMDGPU_MAX_ENTITY_NUM 4

काष्ठा amdgpu_ctx_entity अणु
	uपूर्णांक64_t		sequence;
	काष्ठा drm_sched_entity	entity;
	काष्ठा dma_fence	*fences[];
पूर्ण;

काष्ठा amdgpu_ctx अणु
	काष्ठा kref			refcount;
	काष्ठा amdgpu_device		*adev;
	अचिन्हित			reset_counter;
	अचिन्हित			reset_counter_query;
	uपूर्णांक32_t			vram_lost_counter;
	spinlock_t			ring_lock;
	काष्ठा amdgpu_ctx_entity	*entities[AMDGPU_HW_IP_NUM][AMDGPU_MAX_ENTITY_NUM];
	bool				preamble_presented;
	क्रमागत drm_sched_priority		init_priority;
	क्रमागत drm_sched_priority		override_priority;
	काष्ठा mutex			lock;
	atomic_t			guilty;
	अचिन्हित दीर्घ			ras_counter_ce;
	अचिन्हित दीर्घ			ras_counter_ue;
पूर्ण;

काष्ठा amdgpu_ctx_mgr अणु
	काष्ठा amdgpu_device	*adev;
	काष्ठा mutex		lock;
	/* रक्षित by lock */
	काष्ठा idr		ctx_handles;
पूर्ण;

बाह्य स्थिर अचिन्हित पूर्णांक amdgpu_ctx_num_entities[AMDGPU_HW_IP_NUM];

काष्ठा amdgpu_ctx *amdgpu_ctx_get(काष्ठा amdgpu_fpriv *fpriv, uपूर्णांक32_t id);
पूर्णांक amdgpu_ctx_put(काष्ठा amdgpu_ctx *ctx);

पूर्णांक amdgpu_ctx_get_entity(काष्ठा amdgpu_ctx *ctx, u32 hw_ip, u32 instance,
			  u32 ring, काष्ठा drm_sched_entity **entity);
व्योम amdgpu_ctx_add_fence(काष्ठा amdgpu_ctx *ctx,
			  काष्ठा drm_sched_entity *entity,
			  काष्ठा dma_fence *fence, uपूर्णांक64_t *seq);
काष्ठा dma_fence *amdgpu_ctx_get_fence(काष्ठा amdgpu_ctx *ctx,
				       काष्ठा drm_sched_entity *entity,
				       uपूर्णांक64_t seq);
व्योम amdgpu_ctx_priority_override(काष्ठा amdgpu_ctx *ctx,
				  क्रमागत drm_sched_priority priority);

पूर्णांक amdgpu_ctx_ioctl(काष्ठा drm_device *dev, व्योम *data,
		     काष्ठा drm_file *filp);

पूर्णांक amdgpu_ctx_रुको_prev_fence(काष्ठा amdgpu_ctx *ctx,
			       काष्ठा drm_sched_entity *entity);

व्योम amdgpu_ctx_mgr_init(काष्ठा amdgpu_ctx_mgr *mgr);
व्योम amdgpu_ctx_mgr_entity_fini(काष्ठा amdgpu_ctx_mgr *mgr);
दीर्घ amdgpu_ctx_mgr_entity_flush(काष्ठा amdgpu_ctx_mgr *mgr, दीर्घ समयout);
व्योम amdgpu_ctx_mgr_fini(काष्ठा amdgpu_ctx_mgr *mgr);

#पूर्ण_अगर
