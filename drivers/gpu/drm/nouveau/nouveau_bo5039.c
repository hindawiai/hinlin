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
#समावेश "nouveau_mem.h"

#समावेश <nvअगर/push206e.h>

#समावेश <nvhw/class/cl5039.h>

पूर्णांक
nv50_bo_move_m2mf(काष्ठा nouveau_channel *chan, काष्ठा tपंचांग_buffer_object *bo,
		  काष्ठा tपंचांग_resource *old_reg, काष्ठा tपंचांग_resource *new_reg)
अणु
	काष्ठा nouveau_mem *mem = nouveau_mem(old_reg);
	काष्ठा nvअगर_push *push = chan->chan.push;
	u64 length = (new_reg->num_pages << PAGE_SHIFT);
	u64 src_offset = mem->vma[0].addr;
	u64 dst_offset = mem->vma[1].addr;
	पूर्णांक src_tiled = !!mem->kind;
	पूर्णांक dst_tiled = !!nouveau_mem(new_reg)->kind;
	पूर्णांक ret;

	जबतक (length) अणु
		u32 amount, stride, height;

		ret = PUSH_WAIT(push, 18 + 6 * (src_tiled + dst_tiled));
		अगर (ret)
			वापस ret;

		amount  = min(length, (u64)(4 * 1024 * 1024));
		stride  = 16 * 4;
		height  = amount / stride;

		अगर (src_tiled) अणु
			PUSH_MTHD(push, NV5039, SET_SRC_MEMORY_LAYOUT,
				  NVDEF(NV5039, SET_SRC_MEMORY_LAYOUT, V, BLOCKLINEAR),

						SET_SRC_BLOCK_SIZE,
				  NVDEF(NV5039, SET_SRC_BLOCK_SIZE, WIDTH, ONE_GOB) |
				  NVDEF(NV5039, SET_SRC_BLOCK_SIZE, HEIGHT, ONE_GOB) |
				  NVDEF(NV5039, SET_SRC_BLOCK_SIZE, DEPTH, ONE_GOB),

						SET_SRC_WIDTH, stride,
						SET_SRC_HEIGHT, height,
						SET_SRC_DEPTH, 1,
						SET_SRC_LAYER, 0,

						SET_SRC_ORIGIN,
				  NVVAL(NV5039, SET_SRC_ORIGIN, X, 0) |
				  NVVAL(NV5039, SET_SRC_ORIGIN, Y, 0));
		पूर्ण अन्यथा अणु
			PUSH_MTHD(push, NV5039, SET_SRC_MEMORY_LAYOUT,
				  NVDEF(NV5039, SET_SRC_MEMORY_LAYOUT, V, PITCH));
		पूर्ण

		अगर (dst_tiled) अणु
			PUSH_MTHD(push, NV5039, SET_DST_MEMORY_LAYOUT,
				  NVDEF(NV5039, SET_DST_MEMORY_LAYOUT, V, BLOCKLINEAR),

						SET_DST_BLOCK_SIZE,
				  NVDEF(NV5039, SET_DST_BLOCK_SIZE, WIDTH, ONE_GOB) |
				  NVDEF(NV5039, SET_DST_BLOCK_SIZE, HEIGHT, ONE_GOB) |
				  NVDEF(NV5039, SET_DST_BLOCK_SIZE, DEPTH, ONE_GOB),

						SET_DST_WIDTH, stride,
						SET_DST_HEIGHT, height,
						SET_DST_DEPTH, 1,
						SET_DST_LAYER, 0,

						SET_DST_ORIGIN,
				  NVVAL(NV5039, SET_DST_ORIGIN, X, 0) |
				  NVVAL(NV5039, SET_DST_ORIGIN, Y, 0));
		पूर्ण अन्यथा अणु
			PUSH_MTHD(push, NV5039, SET_DST_MEMORY_LAYOUT,
				  NVDEF(NV5039, SET_DST_MEMORY_LAYOUT, V, PITCH));
		पूर्ण

		PUSH_MTHD(push, NV5039, OFFSET_IN_UPPER,
			  NVVAL(NV5039, OFFSET_IN_UPPER, VALUE, upper_32_bits(src_offset)),

					OFFSET_OUT_UPPER,
			  NVVAL(NV5039, OFFSET_OUT_UPPER, VALUE, upper_32_bits(dst_offset)));

		PUSH_MTHD(push, NV5039, OFFSET_IN, lower_32_bits(src_offset),
					OFFSET_OUT, lower_32_bits(dst_offset),
					PITCH_IN, stride,
					PITCH_OUT, stride,
					LINE_LENGTH_IN, stride,
					LINE_COUNT, height,

					FORMAT,
			  NVDEF(NV5039, FORMAT, IN, ONE) |
			  NVDEF(NV5039, FORMAT, OUT, ONE),

					BUFFER_NOTIFY,
			  NVDEF(NV5039, BUFFER_NOTIFY, TYPE, WRITE_ONLY));

		PUSH_MTHD(push, NV5039, NO_OPERATION, 0x00000000);

		length -= amount;
		src_offset += amount;
		dst_offset += amount;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nv50_bo_move_init(काष्ठा nouveau_channel *chan, u32 handle)
अणु
	काष्ठा nvअगर_push *push = chan->chan.push;
	पूर्णांक ret;

	ret = PUSH_WAIT(push, 6);
	अगर (ret)
		वापस ret;

	PUSH_MTHD(push, NV5039, SET_OBJECT, handle);
	PUSH_MTHD(push, NV5039, SET_CONTEXT_DMA_NOTIFY, chan->drm->ntfy.handle,
				SET_CONTEXT_DMA_BUFFER_IN, chan->vram.handle,
				SET_CONTEXT_DMA_BUFFER_OUT, chan->vram.handle);
	वापस 0;
पूर्ण
