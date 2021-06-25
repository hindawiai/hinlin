<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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
 * Authors: Ben Skeggs
 */
#समावेश "nouveau_drv.h"
#समावेश "nouveau_dma.h"
#समावेश "nouveau_fence.h"
#समावेश "nouveau_vmm.h"

#समावेश "nv50_display.h"

#समावेश <nvअगर/push206e.h>

#समावेश <nvhw/class/cl826f.h>

अटल पूर्णांक
nv84_fence_emit32(काष्ठा nouveau_channel *chan, u64 भव, u32 sequence)
अणु
	काष्ठा nvअगर_push *push = chan->chan.push;
	पूर्णांक ret = PUSH_WAIT(push, 8);
	अगर (ret == 0) अणु
		PUSH_MTHD(push, NV826F, SET_CONTEXT_DMA_SEMAPHORE, chan->vram.handle);

		PUSH_MTHD(push, NV826F, SEMAPHOREA,
			  NVVAL(NV826F, SEMAPHOREA, OFFSET_UPPER, upper_32_bits(भव)),

					SEMAPHOREB, lower_32_bits(भव),
					SEMAPHOREC, sequence,

					SEMAPHORED,
			  NVDEF(NV826F, SEMAPHORED, OPERATION, RELEASE),

					NON_STALLED_INTERRUPT, 0);
		PUSH_KICK(push);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
nv84_fence_sync32(काष्ठा nouveau_channel *chan, u64 भव, u32 sequence)
अणु
	काष्ठा nvअगर_push *push = chan->chan.push;
	पूर्णांक ret = PUSH_WAIT(push, 7);
	अगर (ret == 0) अणु
		PUSH_MTHD(push, NV826F, SET_CONTEXT_DMA_SEMAPHORE, chan->vram.handle);

		PUSH_MTHD(push, NV826F, SEMAPHOREA,
			  NVVAL(NV826F, SEMAPHOREA, OFFSET_UPPER, upper_32_bits(भव)),

					SEMAPHOREB, lower_32_bits(भव),
					SEMAPHOREC, sequence,

					SEMAPHORED,
			  NVDEF(NV826F, SEMAPHORED, OPERATION, ACQ_GEQ));
		PUSH_KICK(push);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
nv84_fence_emit(काष्ठा nouveau_fence *fence)
अणु
	काष्ठा nouveau_channel *chan = fence->channel;
	काष्ठा nv84_fence_chan *fctx = chan->fence;
	u64 addr = fctx->vma->addr + chan->chid * 16;

	वापस fctx->base.emit32(chan, addr, fence->base.seqno);
पूर्ण

अटल पूर्णांक
nv84_fence_sync(काष्ठा nouveau_fence *fence,
		काष्ठा nouveau_channel *prev, काष्ठा nouveau_channel *chan)
अणु
	काष्ठा nv84_fence_chan *fctx = chan->fence;
	u64 addr = fctx->vma->addr + prev->chid * 16;

	वापस fctx->base.sync32(chan, addr, fence->base.seqno);
पूर्ण

अटल u32
nv84_fence_पढ़ो(काष्ठा nouveau_channel *chan)
अणु
	काष्ठा nv84_fence_priv *priv = chan->drm->fence;
	वापस nouveau_bo_rd32(priv->bo, chan->chid * 16/4);
पूर्ण

अटल व्योम
nv84_fence_context_del(काष्ठा nouveau_channel *chan)
अणु
	काष्ठा nv84_fence_priv *priv = chan->drm->fence;
	काष्ठा nv84_fence_chan *fctx = chan->fence;

	nouveau_bo_wr32(priv->bo, chan->chid * 16 / 4, fctx->base.sequence);
	mutex_lock(&priv->mutex);
	nouveau_vma_del(&fctx->vma);
	mutex_unlock(&priv->mutex);
	nouveau_fence_context_del(&fctx->base);
	chan->fence = शून्य;
	nouveau_fence_context_मुक्त(&fctx->base);
पूर्ण

पूर्णांक
nv84_fence_context_new(काष्ठा nouveau_channel *chan)
अणु
	काष्ठा nv84_fence_priv *priv = chan->drm->fence;
	काष्ठा nv84_fence_chan *fctx;
	पूर्णांक ret;

	fctx = chan->fence = kzalloc(माप(*fctx), GFP_KERNEL);
	अगर (!fctx)
		वापस -ENOMEM;

	nouveau_fence_context_new(chan, &fctx->base);
	fctx->base.emit = nv84_fence_emit;
	fctx->base.sync = nv84_fence_sync;
	fctx->base.पढ़ो = nv84_fence_पढ़ो;
	fctx->base.emit32 = nv84_fence_emit32;
	fctx->base.sync32 = nv84_fence_sync32;
	fctx->base.sequence = nv84_fence_पढ़ो(chan);

	mutex_lock(&priv->mutex);
	ret = nouveau_vma_new(priv->bo, chan->vmm, &fctx->vma);
	mutex_unlock(&priv->mutex);

	अगर (ret)
		nv84_fence_context_del(chan);
	वापस ret;
पूर्ण

अटल bool
nv84_fence_suspend(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nv84_fence_priv *priv = drm->fence;
	पूर्णांक i;

	priv->suspend = vदो_स्मृति(array_size(माप(u32), drm->chan.nr));
	अगर (priv->suspend) अणु
		क्रम (i = 0; i < drm->chan.nr; i++)
			priv->suspend[i] = nouveau_bo_rd32(priv->bo, i*4);
	पूर्ण

	वापस priv->suspend != शून्य;
पूर्ण

अटल व्योम
nv84_fence_resume(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nv84_fence_priv *priv = drm->fence;
	पूर्णांक i;

	अगर (priv->suspend) अणु
		क्रम (i = 0; i < drm->chan.nr; i++)
			nouveau_bo_wr32(priv->bo, i*4, priv->suspend[i]);
		vमुक्त(priv->suspend);
		priv->suspend = शून्य;
	पूर्ण
पूर्ण

अटल व्योम
nv84_fence_destroy(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nv84_fence_priv *priv = drm->fence;
	nouveau_bo_unmap(priv->bo);
	अगर (priv->bo)
		nouveau_bo_unpin(priv->bo);
	nouveau_bo_ref(शून्य, &priv->bo);
	drm->fence = शून्य;
	kमुक्त(priv);
पूर्ण

पूर्णांक
nv84_fence_create(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nv84_fence_priv *priv;
	u32 करोमुख्य;
	पूर्णांक ret;

	priv = drm->fence = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base.dtor = nv84_fence_destroy;
	priv->base.suspend = nv84_fence_suspend;
	priv->base.resume = nv84_fence_resume;
	priv->base.context_new = nv84_fence_context_new;
	priv->base.context_del = nv84_fence_context_del;

	priv->base.uevent = true;

	mutex_init(&priv->mutex);

	/* Use VRAM अगर there is any ; otherwise fallback to प्रणाली memory */
	करोमुख्य = drm->client.device.info.ram_size != 0 ?
		NOUVEAU_GEM_DOMAIN_VRAM :
		 /*
		  * fences created in sysmem must be non-cached or we
		  * will lose CPU/GPU coherency!
		  */
		NOUVEAU_GEM_DOMAIN_GART | NOUVEAU_GEM_DOMAIN_COHERENT;
	ret = nouveau_bo_new(&drm->client, 16 * drm->chan.nr, 0,
			     करोमुख्य, 0, 0, शून्य, शून्य, &priv->bo);
	अगर (ret == 0) अणु
		ret = nouveau_bo_pin(priv->bo, करोमुख्य, false);
		अगर (ret == 0) अणु
			ret = nouveau_bo_map(priv->bo);
			अगर (ret)
				nouveau_bo_unpin(priv->bo);
		पूर्ण
		अगर (ret)
			nouveau_bo_ref(शून्य, &priv->bo);
	पूर्ण

	अगर (ret)
		nv84_fence_destroy(drm);
	वापस ret;
पूर्ण
