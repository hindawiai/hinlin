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
gm107_fuse_पढ़ो(काष्ठा nvkm_fuse *fuse, u32 addr)
अणु
	काष्ठा nvkm_device *device = fuse->subdev.device;
	वापस nvkm_rd32(device, 0x021100 + addr);
पूर्ण

अटल स्थिर काष्ठा nvkm_fuse_func
gm107_fuse = अणु
	.पढ़ो = gm107_fuse_पढ़ो,
पूर्ण;

पूर्णांक
gm107_fuse_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_fuse **pfuse)
अणु
	वापस nvkm_fuse_new_(&gm107_fuse, device, type, inst, pfuse);
पूर्ण
