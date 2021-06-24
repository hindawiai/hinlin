<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * seqno-fence, using a dma-buf to synchronize fencing
 *
 * Copyright (C) 2012 Texas Instruments
 * Copyright (C) 2012 Canonical Ltd
 * Authors:
 *   Rob Clark <robdclark@gmail.com>
 *   Maarten Lankhorst <maarten.lankhorst@canonical.com>
 */

#अगर_अघोषित __LINUX_SEQNO_FENCE_H
#घोषणा __LINUX_SEQNO_FENCE_H

#समावेश <linux/dma-fence.h>
#समावेश <linux/dma-buf.h>

क्रमागत seqno_fence_condition अणु
	SEQNO_FENCE_WAIT_GEQUAL,
	SEQNO_FENCE_WAIT_NONZERO
पूर्ण;

काष्ठा seqno_fence अणु
	काष्ठा dma_fence base;

	स्थिर काष्ठा dma_fence_ops *ops;
	काष्ठा dma_buf *sync_buf;
	uपूर्णांक32_t seqno_ofs;
	क्रमागत seqno_fence_condition condition;
पूर्ण;

बाह्य स्थिर काष्ठा dma_fence_ops seqno_fence_ops;

/**
 * to_seqno_fence - cast a fence to a seqno_fence
 * @fence: fence to cast to a seqno_fence
 *
 * Returns शून्य अगर the fence is not a seqno_fence,
 * or the seqno_fence otherwise.
 */
अटल अंतरभूत काष्ठा seqno_fence *
to_seqno_fence(काष्ठा dma_fence *fence)
अणु
	अगर (fence->ops != &seqno_fence_ops)
		वापस शून्य;
	वापस container_of(fence, काष्ठा seqno_fence, base);
पूर्ण

/**
 * seqno_fence_init - initialize a seqno fence
 * @fence: seqno_fence to initialize
 * @lock: poपूर्णांकer to spinlock to use क्रम fence
 * @sync_buf: buffer containing the memory location to संकेत on
 * @context: the execution context this fence is a part of
 * @seqno_ofs: the offset within @sync_buf
 * @seqno: the sequence # to संकेत on
 * @cond: fence रुको condition
 * @ops: the fence_ops क्रम operations on this seqno fence
 *
 * This function initializes a काष्ठा seqno_fence with passed parameters,
 * and takes a reference on sync_buf which is released on fence deकाष्ठाion.
 *
 * A seqno_fence is a dma_fence which can complete in software when
 * enable_संकेतing is called, but it also completes when
 * (s32)((sync_buf)[seqno_ofs] - seqno) >= 0 is true
 *
 * The seqno_fence will take a refcount on the sync_buf until it's
 * destroyed, but actual lअगरeसमय of sync_buf may be दीर्घer अगर one of the
 * callers take a reference to it.
 *
 * Certain hardware have inकाष्ठाions to insert this type of रुको condition
 * in the command stream, so no पूर्णांकervention from software would be needed.
 * This type of fence can be destroyed beक्रमe completed, however a reference
 * on the sync_buf dma-buf can be taken. It is encouraged to re-use the same
 * dma-buf क्रम sync_buf, since mapping or unmapping the sync_buf to the
 * device's vm can be expensive.
 *
 * It is recommended क्रम creators of seqno_fence to call dma_fence_संकेत()
 * beक्रमe deकाष्ठाion. This will prevent possible issues from wraparound at
 * समय of issue vs समय of check, since users can check dma_fence_is_संकेतed()
 * beक्रमe submitting inकाष्ठाions क्रम the hardware to रुको on the fence.
 * However, when ops.enable_संकेतing is not called, it करोesn't have to be
 * करोne as soon as possible, just beक्रमe there's any real danger of seqno
 * wraparound.
 */
अटल अंतरभूत व्योम
seqno_fence_init(काष्ठा seqno_fence *fence, spinlock_t *lock,
		 काष्ठा dma_buf *sync_buf,  uपूर्णांक32_t context,
		 uपूर्णांक32_t seqno_ofs, uपूर्णांक32_t seqno,
		 क्रमागत seqno_fence_condition cond,
		 स्थिर काष्ठा dma_fence_ops *ops)
अणु
	BUG_ON(!fence || !sync_buf || !ops);
	BUG_ON(!ops->रुको || !ops->enable_संकेतing ||
	       !ops->get_driver_name || !ops->get_समयline_name);

	/*
	 * ops is used in dma_fence_init क्रम get_driver_name, so needs to be
	 * initialized first
	 */
	fence->ops = ops;
	dma_fence_init(&fence->base, &seqno_fence_ops, lock, context, seqno);
	get_dma_buf(sync_buf);
	fence->sync_buf = sync_buf;
	fence->seqno_ofs = seqno_ofs;
	fence->condition = cond;
पूर्ण

#पूर्ण_अगर /* __LINUX_SEQNO_FENCE_H */
