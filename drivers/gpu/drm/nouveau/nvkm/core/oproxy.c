<शैली गुरु>
/*
 * Copyright 2015 Red Hat Inc.
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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश <core/oproxy.h>

अटल पूर्णांक
nvkm_oproxy_mthd(काष्ठा nvkm_object *object, u32 mthd, व्योम *data, u32 size)
अणु
	वापस nvkm_object_mthd(nvkm_oproxy(object)->object, mthd, data, size);
पूर्ण

अटल पूर्णांक
nvkm_oproxy_ntfy(काष्ठा nvkm_object *object, u32 mthd,
		 काष्ठा nvkm_event **pevent)
अणु
	वापस nvkm_object_ntfy(nvkm_oproxy(object)->object, mthd, pevent);
पूर्ण

अटल पूर्णांक
nvkm_oproxy_map(काष्ठा nvkm_object *object, व्योम *argv, u32 argc,
		क्रमागत nvkm_object_map *type, u64 *addr, u64 *size)
अणु
	काष्ठा nvkm_oproxy *oproxy = nvkm_oproxy(object);
	वापस nvkm_object_map(oproxy->object, argv, argc, type, addr, size);
पूर्ण

अटल पूर्णांक
nvkm_oproxy_unmap(काष्ठा nvkm_object *object)
अणु
	वापस nvkm_object_unmap(nvkm_oproxy(object)->object);
पूर्ण

अटल पूर्णांक
nvkm_oproxy_rd08(काष्ठा nvkm_object *object, u64 addr, u8 *data)
अणु
	वापस nvkm_object_rd08(nvkm_oproxy(object)->object, addr, data);
पूर्ण

अटल पूर्णांक
nvkm_oproxy_rd16(काष्ठा nvkm_object *object, u64 addr, u16 *data)
अणु
	वापस nvkm_object_rd16(nvkm_oproxy(object)->object, addr, data);
पूर्ण

अटल पूर्णांक
nvkm_oproxy_rd32(काष्ठा nvkm_object *object, u64 addr, u32 *data)
अणु
	वापस nvkm_object_rd32(nvkm_oproxy(object)->object, addr, data);
पूर्ण

अटल पूर्णांक
nvkm_oproxy_wr08(काष्ठा nvkm_object *object, u64 addr, u8 data)
अणु
	वापस nvkm_object_wr08(nvkm_oproxy(object)->object, addr, data);
पूर्ण

अटल पूर्णांक
nvkm_oproxy_wr16(काष्ठा nvkm_object *object, u64 addr, u16 data)
अणु
	वापस nvkm_object_wr16(nvkm_oproxy(object)->object, addr, data);
पूर्ण

अटल पूर्णांक
nvkm_oproxy_wr32(काष्ठा nvkm_object *object, u64 addr, u32 data)
अणु
	वापस nvkm_object_wr32(nvkm_oproxy(object)->object, addr, data);
पूर्ण

अटल पूर्णांक
nvkm_oproxy_bind(काष्ठा nvkm_object *object, काष्ठा nvkm_gpuobj *parent,
		 पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	वापस nvkm_object_bind(nvkm_oproxy(object)->object,
				parent, align, pgpuobj);
पूर्ण

अटल पूर्णांक
nvkm_oproxy_sclass(काष्ठा nvkm_object *object, पूर्णांक index,
		   काष्ठा nvkm_oclass *oclass)
अणु
	काष्ठा nvkm_oproxy *oproxy = nvkm_oproxy(object);
	oclass->parent = oproxy->object;
	अगर (!oproxy->object->func->sclass)
		वापस -ENODEV;
	वापस oproxy->object->func->sclass(oproxy->object, index, oclass);
पूर्ण

अटल पूर्णांक
nvkm_oproxy_fini(काष्ठा nvkm_object *object, bool suspend)
अणु
	काष्ठा nvkm_oproxy *oproxy = nvkm_oproxy(object);
	पूर्णांक ret;

	अगर (oproxy->func->fini[0]) अणु
		ret = oproxy->func->fini[0](oproxy, suspend);
		अगर (ret && suspend)
			वापस ret;
	पूर्ण

	अगर (oproxy->object->func->fini) अणु
		ret = oproxy->object->func->fini(oproxy->object, suspend);
		अगर (ret && suspend)
			वापस ret;
	पूर्ण

	अगर (oproxy->func->fini[1]) अणु
		ret = oproxy->func->fini[1](oproxy, suspend);
		अगर (ret && suspend)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_oproxy_init(काष्ठा nvkm_object *object)
अणु
	काष्ठा nvkm_oproxy *oproxy = nvkm_oproxy(object);
	पूर्णांक ret;

	अगर (oproxy->func->init[0]) अणु
		ret = oproxy->func->init[0](oproxy);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (oproxy->object->func->init) अणु
		ret = oproxy->object->func->init(oproxy->object);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (oproxy->func->init[1]) अणु
		ret = oproxy->func->init[1](oproxy);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम *
nvkm_oproxy_dtor(काष्ठा nvkm_object *object)
अणु
	काष्ठा nvkm_oproxy *oproxy = nvkm_oproxy(object);
	अगर (oproxy->func->dtor[0])
		oproxy->func->dtor[0](oproxy);
	nvkm_object_del(&oproxy->object);
	अगर (oproxy->func->dtor[1])
		oproxy->func->dtor[1](oproxy);
	वापस oproxy;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nvkm_oproxy_func = अणु
	.dtor = nvkm_oproxy_dtor,
	.init = nvkm_oproxy_init,
	.fini = nvkm_oproxy_fini,
	.mthd = nvkm_oproxy_mthd,
	.ntfy = nvkm_oproxy_ntfy,
	.map = nvkm_oproxy_map,
	.unmap = nvkm_oproxy_unmap,
	.rd08 = nvkm_oproxy_rd08,
	.rd16 = nvkm_oproxy_rd16,
	.rd32 = nvkm_oproxy_rd32,
	.wr08 = nvkm_oproxy_wr08,
	.wr16 = nvkm_oproxy_wr16,
	.wr32 = nvkm_oproxy_wr32,
	.bind = nvkm_oproxy_bind,
	.sclass = nvkm_oproxy_sclass,
पूर्ण;

व्योम
nvkm_oproxy_ctor(स्थिर काष्ठा nvkm_oproxy_func *func,
		 स्थिर काष्ठा nvkm_oclass *oclass, काष्ठा nvkm_oproxy *oproxy)
अणु
	nvkm_object_ctor(&nvkm_oproxy_func, oclass, &oproxy->base);
	oproxy->func = func;
पूर्ण

पूर्णांक
nvkm_oproxy_new_(स्थिर काष्ठा nvkm_oproxy_func *func,
		 स्थिर काष्ठा nvkm_oclass *oclass, काष्ठा nvkm_oproxy **poproxy)
अणु
	अगर (!(*poproxy = kzalloc(माप(**poproxy), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_oproxy_ctor(func, oclass, *poproxy);
	वापस 0;
पूर्ण
