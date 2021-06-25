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

#समावेश <nvhw/class/cl006e.h>

पूर्णांक
nv10_fence_emit(काष्ठा nouveau_fence *fence)
अणु
	काष्ठा nvअगर_push *push = fence->channel->chan.push;
	पूर्णांक ret = PUSH_WAIT(push, 2);
	अगर (ret == 0) अणु
		PUSH_MTHD(push, NV06E, SET_REFERENCE, fence->base.seqno);
		PUSH_KICK(push);
	पूर्ण
	वापस ret;
पूर्ण


अटल पूर्णांक
nv10_fence_sync(काष्ठा nouveau_fence *fence,
		काष्ठा nouveau_channel *prev, काष्ठा nouveau_channel *chan)
अणु
	वापस -ENODEV;
पूर्ण

u32
nv10_fence_पढ़ो(काष्ठा nouveau_channel *chan)
अणु
	वापस NVIF_RD32(&chan->user, NV06E, REFERENCE);
पूर्ण

व्योम
nv10_fence_context_del(काष्ठा nouveau_channel *chan)
अणु
	काष्ठा nv10_fence_chan *fctx = chan->fence;
	nouveau_fence_context_del(&fctx->base);
	nvअगर_object_dtor(&fctx->sema);
	chan->fence = शून्य;
	nouveau_fence_context_मुक्त(&fctx->base);
पूर्ण

अटल पूर्णांक
nv10_fence_context_new(काष्ठा nouveau_channel *chan)
अणु
	काष्ठा nv10_fence_chan *fctx;

	fctx = chan->fence = kzalloc(माप(*fctx), GFP_KERNEL);
	अगर (!fctx)
		वापस -ENOMEM;

	nouveau_fence_context_new(chan, &fctx->base);
	fctx->base.emit = nv10_fence_emit;
	fctx->base.पढ़ो = nv10_fence_पढ़ो;
	fctx->base.sync = nv10_fence_sync;
	वापस 0;
पूर्ण

व्योम
nv10_fence_destroy(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nv10_fence_priv *priv = drm->fence;
	nouveau_bo_unmap(priv->bo);
	अगर (priv->bo)
		nouveau_bo_unpin(priv->bo);
	nouveau_bo_ref(शून्य, &priv->bo);
	drm->fence = शून्य;
	kमुक्त(priv);
पूर्ण

पूर्णांक
nv10_fence_create(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nv10_fence_priv *priv;

	priv = drm->fence = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base.dtor = nv10_fence_destroy;
	priv->base.context_new = nv10_fence_context_new;
	priv->base.context_del = nv10_fence_context_del;
	spin_lock_init(&priv->lock);
	वापस 0;
पूर्ण
