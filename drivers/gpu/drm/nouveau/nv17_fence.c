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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश "nouveau_drv.h"
#समावेश "nouveau_dma.h"
#समावेश "nv10_fence.h"

#समावेश <nvअगर/push006c.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl0002.h>

#समावेश <nvhw/class/cl176e.h>

पूर्णांक
nv17_fence_sync(काष्ठा nouveau_fence *fence,
		काष्ठा nouveau_channel *prev, काष्ठा nouveau_channel *chan)
अणु
	काष्ठा nouveau_cli *cli = (व्योम *)prev->user.client;
	काष्ठा nv10_fence_priv *priv = chan->drm->fence;
	काष्ठा nv10_fence_chan *fctx = chan->fence;
	काष्ठा nvअगर_push *ppush = prev->chan.push;
	काष्ठा nvअगर_push *npush = chan->chan.push;
	u32 value;
	पूर्णांक ret;

	अगर (!mutex_trylock(&cli->mutex))
		वापस -EBUSY;

	spin_lock(&priv->lock);
	value = priv->sequence;
	priv->sequence += 2;
	spin_unlock(&priv->lock);

	ret = PUSH_WAIT(ppush, 5);
	अगर (!ret) अणु
		PUSH_MTHD(ppush, NV176E, SET_CONTEXT_DMA_SEMAPHORE, fctx->sema.handle,
					 SEMAPHORE_OFFSET, 0,
					 SEMAPHORE_ACQUIRE, value + 0,
					 SEMAPHORE_RELEASE, value + 1);
		PUSH_KICK(ppush);
	पूर्ण

	अगर (!ret && !(ret = PUSH_WAIT(npush, 5))) अणु
		PUSH_MTHD(npush, NV176E, SET_CONTEXT_DMA_SEMAPHORE, fctx->sema.handle,
					 SEMAPHORE_OFFSET, 0,
					 SEMAPHORE_ACQUIRE, value + 1,
					 SEMAPHORE_RELEASE, value + 2);
		PUSH_KICK(npush);
	पूर्ण

	mutex_unlock(&cli->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक
nv17_fence_context_new(काष्ठा nouveau_channel *chan)
अणु
	काष्ठा nv10_fence_priv *priv = chan->drm->fence;
	काष्ठा nv10_fence_chan *fctx;
	काष्ठा tपंचांग_resource *reg = &priv->bo->bo.mem;
	u32 start = reg->start * PAGE_SIZE;
	u32 limit = start + priv->bo->bo.base.size - 1;
	पूर्णांक ret = 0;

	fctx = chan->fence = kzalloc(माप(*fctx), GFP_KERNEL);
	अगर (!fctx)
		वापस -ENOMEM;

	nouveau_fence_context_new(chan, &fctx->base);
	fctx->base.emit = nv10_fence_emit;
	fctx->base.पढ़ो = nv10_fence_पढ़ो;
	fctx->base.sync = nv17_fence_sync;

	ret = nvअगर_object_ctor(&chan->user, "fenceCtxDma", NvSema,
			       NV_DMA_FROM_MEMORY,
			       &(काष्ठा nv_dma_v0) अणु
					.target = NV_DMA_V0_TARGET_VRAM,
					.access = NV_DMA_V0_ACCESS_RDWR,
					.start = start,
					.limit = limit,
			       पूर्ण, माप(काष्ठा nv_dma_v0),
			       &fctx->sema);
	अगर (ret)
		nv10_fence_context_del(chan);
	वापस ret;
पूर्ण

व्योम
nv17_fence_resume(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nv10_fence_priv *priv = drm->fence;

	nouveau_bo_wr32(priv->bo, 0, priv->sequence);
पूर्ण

पूर्णांक
nv17_fence_create(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nv10_fence_priv *priv;
	पूर्णांक ret = 0;

	priv = drm->fence = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base.dtor = nv10_fence_destroy;
	priv->base.resume = nv17_fence_resume;
	priv->base.context_new = nv17_fence_context_new;
	priv->base.context_del = nv10_fence_context_del;
	spin_lock_init(&priv->lock);

	ret = nouveau_bo_new(&drm->client, 4096, 0x1000,
			     NOUVEAU_GEM_DOMAIN_VRAM,
			     0, 0x0000, शून्य, शून्य, &priv->bo);
	अगर (!ret) अणु
		ret = nouveau_bo_pin(priv->bo, NOUVEAU_GEM_DOMAIN_VRAM, false);
		अगर (!ret) अणु
			ret = nouveau_bo_map(priv->bo);
			अगर (ret)
				nouveau_bo_unpin(priv->bo);
		पूर्ण
		अगर (ret)
			nouveau_bo_ref(शून्य, &priv->bo);
	पूर्ण

	अगर (ret) अणु
		nv10_fence_destroy(drm);
		वापस ret;
	पूर्ण

	nouveau_bo_wr32(priv->bo, 0x000, 0x00000000);
	वापस ret;
पूर्ण
