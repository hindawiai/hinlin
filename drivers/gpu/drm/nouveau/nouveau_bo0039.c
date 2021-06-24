<शैली गुरु>
/*
 * Copyright 2007 Dave Airlied
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
/*
 * Authors: Dave Airlied <airlied@linux.ie>
 *	    Ben Skeggs   <darktama@iinet.net.au>
 *	    Jeremy Kolb  <jkolb@bअक्रमeis.edu>
 */
#समावेश "nouveau_bo.h"
#समावेश "nouveau_dma.h"
#समावेश "nouveau_drv.h"

#समावेश <nvअगर/push006c.h>

#समावेश <nvhw/class/cl0039.h>

अटल अंतरभूत uपूर्णांक32_t
nouveau_bo_mem_ctxdma(काष्ठा tपंचांग_buffer_object *bo,
		      काष्ठा nouveau_channel *chan, काष्ठा tपंचांग_resource *reg)
अणु
	अगर (reg->mem_type == TTM_PL_TT)
		वापस NvDmaTT;
	वापस chan->vram.handle;
पूर्ण

पूर्णांक
nv04_bo_move_m2mf(काष्ठा nouveau_channel *chan, काष्ठा tपंचांग_buffer_object *bo,
		  काष्ठा tपंचांग_resource *old_reg, काष्ठा tपंचांग_resource *new_reg)
अणु
	काष्ठा nvअगर_push *push = chan->chan.push;
	u32 src_ctxdma = nouveau_bo_mem_ctxdma(bo, chan, old_reg);
	u32 src_offset = old_reg->start << PAGE_SHIFT;
	u32 dst_ctxdma = nouveau_bo_mem_ctxdma(bo, chan, new_reg);
	u32 dst_offset = new_reg->start << PAGE_SHIFT;
	u32 page_count = new_reg->num_pages;
	पूर्णांक ret;

	ret = PUSH_WAIT(push, 3);
	अगर (ret)
		वापस ret;

	PUSH_MTHD(push, NV039, SET_CONTEXT_DMA_BUFFER_IN, src_ctxdma,
			       SET_CONTEXT_DMA_BUFFER_OUT, dst_ctxdma);

	page_count = new_reg->num_pages;
	जबतक (page_count) अणु
		पूर्णांक line_count = (page_count > 2047) ? 2047 : page_count;

		ret = PUSH_WAIT(push, 11);
		अगर (ret)
			वापस ret;

		PUSH_MTHD(push, NV039, OFFSET_IN, src_offset,
				       OFFSET_OUT, dst_offset,
				       PITCH_IN, PAGE_SIZE,
				       PITCH_OUT, PAGE_SIZE,
				       LINE_LENGTH_IN, PAGE_SIZE,
				       LINE_COUNT, line_count,

				       FORMAT,
			  NVVAL(NV039, FORMAT, IN, 1) |
			  NVVAL(NV039, FORMAT, OUT, 1),

				       BUFFER_NOTIFY, NV039_BUFFER_NOTIFY_WRITE_ONLY);

		PUSH_MTHD(push, NV039, NO_OPERATION, 0x00000000);

		page_count -= line_count;
		src_offset += (PAGE_SIZE * line_count);
		dst_offset += (PAGE_SIZE * line_count);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nv04_bo_move_init(काष्ठा nouveau_channel *chan, u32 handle)
अणु
	काष्ठा nvअगर_push *push = chan->chan.push;
	पूर्णांक ret;

	ret = PUSH_WAIT(push, 4);
	अगर (ret)
		वापस ret;

	PUSH_MTHD(push, NV039, SET_OBJECT, handle);
	PUSH_MTHD(push, NV039, SET_CONTEXT_DMA_NOTIFIES, chan->drm->ntfy.handle);
	वापस 0;
पूर्ण
