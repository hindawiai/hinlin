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

u32
nvkm_fuse_पढ़ो(काष्ठा nvkm_fuse *fuse, u32 addr)
अणु
	वापस fuse->func->पढ़ो(fuse, addr);
पूर्ण

अटल व्योम *
nvkm_fuse_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	वापस nvkm_fuse(subdev);
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_fuse = अणु
	.dtor = nvkm_fuse_dtor,
पूर्ण;

पूर्णांक
nvkm_fuse_new_(स्थिर काष्ठा nvkm_fuse_func *func, काष्ठा nvkm_device *device,
	       क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fuse **pfuse)
अणु
	काष्ठा nvkm_fuse *fuse;
	अगर (!(fuse = *pfuse = kzalloc(माप(*fuse), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_subdev_ctor(&nvkm_fuse, device, type, inst, &fuse->subdev);
	fuse->func = func;
	spin_lock_init(&fuse->lock);
	वापस 0;
पूर्ण
