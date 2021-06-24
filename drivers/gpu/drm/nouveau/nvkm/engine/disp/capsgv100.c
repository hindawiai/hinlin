<शैली गुरु>
/*
 * Copyright 2020 Red Hat Inc.
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
 */
#घोषणा gv100_disp_caps(p) container_of((p), काष्ठा gv100_disp_caps, object)
#समावेश "rootnv50.h"

काष्ठा gv100_disp_caps अणु
	काष्ठा nvkm_object object;
	काष्ठा nv50_disp *disp;
पूर्ण;

अटल पूर्णांक
gv100_disp_caps_map(काष्ठा nvkm_object *object, व्योम *argv, u32 argc,
		    क्रमागत nvkm_object_map *type, u64 *addr, u64 *size)
अणु
	काष्ठा gv100_disp_caps *caps = gv100_disp_caps(object);
	काष्ठा nvkm_device *device = caps->disp->base.engine.subdev.device;
	*type = NVKM_OBJECT_MAP_IO;
	*addr = 0x640000 + device->func->resource_addr(device, 0);
	*size = 0x1000;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
gv100_disp_caps = अणु
	.map = gv100_disp_caps_map,
पूर्ण;

पूर्णांक
gv100_disp_caps_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
		    काष्ठा nv50_disp *disp, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा gv100_disp_caps *caps;

	अगर (!(caps = kzalloc(माप(*caps), GFP_KERNEL)))
		वापस -ENOMEM;
	*pobject = &caps->object;

	nvkm_object_ctor(&gv100_disp_caps, oclass, &caps->object);
	caps->disp = disp;
	वापस 0;
पूर्ण
