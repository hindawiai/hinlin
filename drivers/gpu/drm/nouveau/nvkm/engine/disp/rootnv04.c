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
#घोषणा nv04_disp_root(p) container_of((p), काष्ठा nv04_disp_root, object)
#समावेश "priv.h"
#समावेश "head.h"

#समावेश <core/client.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl0046.h>
#समावेश <nvअगर/unpack.h>

काष्ठा nv04_disp_root अणु
	काष्ठा nvkm_object object;
	काष्ठा nvkm_disp *disp;
पूर्ण;

अटल पूर्णांक
nv04_disp_mthd(काष्ठा nvkm_object *object, u32 mthd, व्योम *data, u32 size)
अणु
	काष्ठा nv04_disp_root *root = nv04_disp_root(object);
	जोड़ अणु
		काष्ठा nv04_disp_mthd_v0 v0;
	पूर्ण *args = data;
	काष्ठा nvkm_head *head;
	पूर्णांक id, ret = -ENOSYS;

	nvअगर_ioctl(object, "disp mthd size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
		nvअगर_ioctl(object, "disp mthd vers %d mthd %02x head %d\n",
			   args->v0.version, args->v0.method, args->v0.head);
		mthd = args->v0.method;
		id   = args->v0.head;
	पूर्ण अन्यथा
		वापस ret;

	अगर (!(head = nvkm_head_find(root->disp, id)))
		वापस -ENXIO;

	चयन (mthd) अणु
	हाल NV04_DISP_SCANOUTPOS:
		वापस nvkm_head_mthd_scanoutpos(object, head, data, size);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nv04_disp_root = अणु
	.mthd = nv04_disp_mthd,
	.ntfy = nvkm_disp_ntfy,
पूर्ण;

अटल पूर्णांक
nv04_disp_root_new(काष्ठा nvkm_disp *disp, स्थिर काष्ठा nvkm_oclass *oclass,
		   व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nv04_disp_root *root;

	अगर (!(root = kzalloc(माप(*root), GFP_KERNEL)))
		वापस -ENOMEM;
	root->disp = disp;
	*pobject = &root->object;

	nvkm_object_ctor(&nv04_disp_root, oclass, &root->object);
	वापस 0;
पूर्ण

स्थिर काष्ठा nvkm_disp_oclass
nv04_disp_root_oclass = अणु
	.base.oclass = NV04_DISP,
	.base.minver = -1,
	.base.maxver = -1,
	.ctor = nv04_disp_root_new,
पूर्ण;
