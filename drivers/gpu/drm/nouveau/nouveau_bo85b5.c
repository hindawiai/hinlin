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
#समावेश "nouveau_mem.h"

#समावेश <nvअगर/push206e.h>

/*XXX: Fixup class to be compatible with NVIDIA's, which will allow sharing
 *     code with KeplerDmaCopyA.
 */

पूर्णांक
nva3_bo_move_copy(काष्ठा nouveau_channel *chan, काष्ठा tपंचांग_buffer_object *bo,
		  काष्ठा tपंचांग_resource *old_reg, काष्ठा tपंचांग_resource *new_reg)
अणु
	काष्ठा nouveau_mem *mem = nouveau_mem(old_reg);
	काष्ठा nvअगर_push *push = chan->chan.push;
	u64 src_offset = mem->vma[0].addr;
	u64 dst_offset = mem->vma[1].addr;
	u32 page_count = new_reg->num_pages;
	पूर्णांक ret;

	page_count = new_reg->num_pages;
	जबतक (page_count) अणु
		पूर्णांक line_count = (page_count > 8191) ? 8191 : page_count;

		ret = PUSH_WAIT(push, 11);
		अगर (ret)
			वापस ret;

		PUSH_NVSQ(push, NV85B5, 0x030c, upper_32_bits(src_offset),
					0x0310, lower_32_bits(src_offset),
					0x0314, upper_32_bits(dst_offset),
					0x0318, lower_32_bits(dst_offset),
					0x031c, PAGE_SIZE,
					0x0320, PAGE_SIZE,
					0x0324, PAGE_SIZE,
					0x0328, line_count);
		PUSH_NVSQ(push, NV85B5, 0x0300, 0x00000110);

		page_count -= line_count;
		src_offset += (PAGE_SIZE * line_count);
		dst_offset += (PAGE_SIZE * line_count);
	पूर्ण

	वापस 0;
पूर्ण
