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

#समावेश "nv50_display.h"

#समावेश <nvअगर/push906f.h>

#समावेश <nvhw/class/cl906f.h>

अटल पूर्णांक
nvc0_fence_emit32(काष्ठा nouveau_channel *chan, u64 भव, u32 sequence)
अणु
	काष्ठा nvअगर_push *push = chan->chan.push;
	पूर्णांक ret = PUSH_WAIT(push, 6);
	अगर (ret == 0) अणु
		PUSH_MTHD(push, NV906F, SEMAPHOREA,
			  NVVAL(NV906F, SEMAPHOREA, OFFSET_UPPER, upper_32_bits(भव)),

					SEMAPHOREB, lower_32_bits(भव),
					SEMAPHOREC, sequence,

					SEMAPHORED,
			  NVDEF(NV906F, SEMAPHORED, OPERATION, RELEASE) |
			  NVDEF(NV906F, SEMAPHORED, RELEASE_WFI, EN) |
			  NVDEF(NV906F, SEMAPHORED, RELEASE_SIZE, 16BYTE),

					NON_STALL_INTERRUPT, 0);
		PUSH_KICK(push);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
nvc0_fence_sync32(काष्ठा nouveau_channel *chan, u64 भव, u32 sequence)
अणु
	काष्ठा nvअगर_push *push = chan->chan.push;
	पूर्णांक ret = PUSH_WAIT(push, 5);
	अगर (ret == 0) अणु
		PUSH_MTHD(push, NV906F, SEMAPHOREA,
			  NVVAL(NV906F, SEMAPHOREA, OFFSET_UPPER, upper_32_bits(भव)),

					SEMAPHOREB, lower_32_bits(भव),
					SEMAPHOREC, sequence,

					SEMAPHORED,
			  NVDEF(NV906F, SEMAPHORED, OPERATION, ACQ_GEQ) |
			  NVDEF(NV906F, SEMAPHORED, ACQUIRE_SWITCH, ENABLED));
		PUSH_KICK(push);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
nvc0_fence_context_new(काष्ठा nouveau_channel *chan)
अणु
	पूर्णांक ret = nv84_fence_context_new(chan);
	अगर (ret == 0) अणु
		काष्ठा nv84_fence_chan *fctx = chan->fence;
		fctx->base.emit32 = nvc0_fence_emit32;
		fctx->base.sync32 = nvc0_fence_sync32;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक
nvc0_fence_create(काष्ठा nouveau_drm *drm)
अणु
	पूर्णांक ret = nv84_fence_create(drm);
	अगर (ret == 0) अणु
		काष्ठा nv84_fence_priv *priv = drm->fence;
		priv->base.context_new = nvc0_fence_context_new;
	पूर्ण
	वापस ret;
पूर्ण
