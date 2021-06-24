<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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
#समावेश "user.h"

अटल पूर्णांक
tu102_fअगरo_user_map(काष्ठा nvkm_object *object, व्योम *argv, u32 argc,
		    क्रमागत nvkm_object_map *type, u64 *addr, u64 *size)
अणु
	काष्ठा nvkm_device *device = object->engine->subdev.device;
	*addr = 0xbb0000 + device->func->resource_addr(device, 0);
	*size = 0x010000;
	*type = NVKM_OBJECT_MAP_IO;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
tu102_fअगरo_user = अणु
	.map = tu102_fअगरo_user_map,
पूर्ण;

पूर्णांक
tu102_fअगरo_user_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
		    काष्ठा nvkm_object **pobject)
अणु
	वापस nvkm_object_new_(&tu102_fअगरo_user, oclass, argv, argc, pobject);
पूर्ण
