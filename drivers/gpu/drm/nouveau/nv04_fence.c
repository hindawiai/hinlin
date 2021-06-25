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

#समावेश <nvअगर/अगर0004.h>
#समावेश <nvअगर/push006c.h>

काष्ठा nv04_fence_chan अणु
	काष्ठा nouveau_fence_chan base;
पूर्ण;

काष्ठा nv04_fence_priv अणु
	काष्ठा nouveau_fence_priv base;
पूर्ण;

अटल पूर्णांक
nv04_fence_emit(काष्ठा nouveau_fence *fence)
अणु
	काष्ठा nvअगर_push *push = fence->channel->chan.push;
	पूर्णांक ret = PUSH_WAIT(push, 2);
	अगर (ret == 0) अणु
		PUSH_NVSQ(push, NV_SW, 0x0150, fence->base.seqno);
		PUSH_KICK(push);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
nv04_fence_sync(काष्ठा nouveau_fence *fence,
		काष्ठा nouveau_channel *prev, काष्ठा nouveau_channel *chan)
अणु
	वापस -ENODEV;
पूर्ण

अटल u32
nv04_fence_पढ़ो(काष्ठा nouveau_channel *chan)
अणु
	काष्ठा nv04_nvsw_get_ref_v0 args = अणुपूर्ण;
	WARN_ON(nvअगर_object_mthd(&chan->nvsw, NV04_NVSW_GET_REF,
				 &args, माप(args)));
	वापस args.ref;
पूर्ण

अटल व्योम
nv04_fence_context_del(काष्ठा nouveau_channel *chan)
अणु
	काष्ठा nv04_fence_chan *fctx = chan->fence;
	nouveau_fence_context_del(&fctx->base);
	chan->fence = शून्य;
	nouveau_fence_context_मुक्त(&fctx->base);
पूर्ण

अटल पूर्णांक
nv04_fence_context_new(काष्ठा nouveau_channel *chan)
अणु
	काष्ठा nv04_fence_chan *fctx = kzalloc(माप(*fctx), GFP_KERNEL);
	अगर (fctx) अणु
		nouveau_fence_context_new(chan, &fctx->base);
		fctx->base.emit = nv04_fence_emit;
		fctx->base.sync = nv04_fence_sync;
		fctx->base.पढ़ो = nv04_fence_पढ़ो;
		chan->fence = fctx;
		वापस 0;
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल व्योम
nv04_fence_destroy(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nv04_fence_priv *priv = drm->fence;
	drm->fence = शून्य;
	kमुक्त(priv);
पूर्ण

पूर्णांक
nv04_fence_create(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nv04_fence_priv *priv;

	priv = drm->fence = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base.dtor = nv04_fence_destroy;
	priv->base.context_new = nv04_fence_context_new;
	priv->base.context_del = nv04_fence_context_del;
	वापस 0;
पूर्ण
