<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित __MSM_RINGBUFFER_H__
#घोषणा __MSM_RINGBUFFER_H__

#समावेश "msm_drv.h"

#घोषणा rbmemptr(ring, member)  \
	((ring)->memptrs_iova + दुरत्व(काष्ठा msm_rbmemptrs, member))

#घोषणा rbmemptr_stats(ring, index, member) \
	(rbmemptr((ring), stats) + \
	 ((index) * माप(काष्ठा msm_gpu_submit_stats)) + \
	 दुरत्व(काष्ठा msm_gpu_submit_stats, member))

काष्ठा msm_gpu_submit_stats अणु
	u64 cpcycles_start;
	u64 cpcycles_end;
	u64 alwayson_start;
	u64 alwayson_end;
पूर्ण;

#घोषणा MSM_GPU_SUBMIT_STATS_COUNT 64

काष्ठा msm_rbmemptrs अणु
	अस्थिर uपूर्णांक32_t rptr;
	अस्थिर uपूर्णांक32_t fence;

	अस्थिर काष्ठा msm_gpu_submit_stats stats[MSM_GPU_SUBMIT_STATS_COUNT];
	अस्थिर u64 ttbr0;
पूर्ण;

काष्ठा msm_ringbuffer अणु
	काष्ठा msm_gpu *gpu;
	पूर्णांक id;
	काष्ठा drm_gem_object *bo;
	uपूर्णांक32_t *start, *end, *cur, *next;

	/*
	 * List of in-flight submits on this ring.  Protected by submit_lock.
	 */
	काष्ठा list_head submits;
	spinlock_t submit_lock;

	uपूर्णांक64_t iova;
	uपूर्णांक32_t seqno;
	uपूर्णांक32_t hangcheck_fence;
	काष्ठा msm_rbmemptrs *memptrs;
	uपूर्णांक64_t memptrs_iova;
	काष्ठा msm_fence_context *fctx;

	/*
	 * preempt_lock protects preemption and serializes wptr updates against
	 * preemption.  Can be aquired from irq context.
	 */
	spinlock_t preempt_lock;
पूर्ण;

काष्ठा msm_ringbuffer *msm_ringbuffer_new(काष्ठा msm_gpu *gpu, पूर्णांक id,
		व्योम *memptrs, uपूर्णांक64_t memptrs_iova);
व्योम msm_ringbuffer_destroy(काष्ठा msm_ringbuffer *ring);

/* ringbuffer helpers (the parts that are same क्रम a3xx/a2xx/z180..) */

अटल अंतरभूत व्योम
OUT_RING(काष्ठा msm_ringbuffer *ring, uपूर्णांक32_t data)
अणु
	/*
	 * ring->next poपूर्णांकs to the current command being written - it won't be
	 * committed as ring->cur until the flush
	 */
	अगर (ring->next == ring->end)
		ring->next = ring->start;
	*(ring->next++) = data;
पूर्ण

#पूर्ण_अगर /* __MSM_RINGBUFFER_H__ */
