<शैली गुरु>
/*
 * Copyright 2014 Martin Peres
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
 * Authors: Martin Peres
 */
#समावेश "priv.h"

अटल u32
gf100_fuse_पढ़ो(काष्ठा nvkm_fuse *fuse, u32 addr)
अणु
	काष्ठा nvkm_device *device = fuse->subdev.device;
	अचिन्हित दीर्घ flags;
	u32 fuse_enable, unk, val;

	/* racy अगर another part of nvkm start writing to these regs */
	spin_lock_irqsave(&fuse->lock, flags);
	fuse_enable = nvkm_mask(device, 0x022400, 0x800, 0x800);
	unk = nvkm_mask(device, 0x021000, 0x1, 0x1);
	val = nvkm_rd32(device, 0x021100 + addr);
	nvkm_wr32(device, 0x021000, unk);
	nvkm_wr32(device, 0x022400, fuse_enable);
	spin_unlock_irqrestore(&fuse->lock, flags);
	वापस val;
पूर्ण

अटल स्थिर काष्ठा nvkm_fuse_func
gf100_fuse = अणु
	.पढ़ो = gf100_fuse_पढ़ो,
पूर्ण;

पूर्णांक
gf100_fuse_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_fuse **pfuse)
अणु
	वापस nvkm_fuse_new_(&gf100_fuse, device, type, inst, pfuse);
पूर्ण
