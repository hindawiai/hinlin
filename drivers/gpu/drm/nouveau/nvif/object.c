<शैली गुरु>
/*
 * Copyright 2014 Red Hat Inc.
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

#समावेश <nvअगर/object.h>
#समावेश <nvअगर/client.h>
#समावेश <nvअगर/driver.h>
#समावेश <nvअगर/ioctl.h>

पूर्णांक
nvअगर_object_ioctl(काष्ठा nvअगर_object *object, व्योम *data, u32 size, व्योम **hack)
अणु
	काष्ठा nvअगर_client *client = object->client;
	जोड़ अणु
		काष्ठा nvअगर_ioctl_v0 v0;
	पूर्ण *args = data;

	अगर (size >= माप(*args) && args->v0.version == 0) अणु
		अगर (object != &client->object)
			args->v0.object = nvअगर_handle(object);
		अन्यथा
			args->v0.object = 0;
		args->v0.owner = NVIF_IOCTL_V0_OWNER_ANY;
	पूर्ण अन्यथा
		वापस -ENOSYS;

	वापस client->driver->ioctl(client->object.priv, client->super,
				     data, size, hack);
पूर्ण

व्योम
nvअगर_object_sclass_put(काष्ठा nvअगर_sclass **psclass)
अणु
	kमुक्त(*psclass);
	*psclass = शून्य;
पूर्ण

पूर्णांक
nvअगर_object_sclass_get(काष्ठा nvअगर_object *object, काष्ठा nvअगर_sclass **psclass)
अणु
	काष्ठा अणु
		काष्ठा nvअगर_ioctl_v0 ioctl;
		काष्ठा nvअगर_ioctl_sclass_v0 sclass;
	पूर्ण *args = शून्य;
	पूर्णांक ret, cnt = 0, i;
	u32 size;

	जबतक (1) अणु
		size = माप(*args) + cnt * माप(args->sclass.oclass[0]);
		अगर (!(args = kदो_स्मृति(size, GFP_KERNEL)))
			वापस -ENOMEM;
		args->ioctl.version = 0;
		args->ioctl.type = NVIF_IOCTL_V0_SCLASS;
		args->sclass.version = 0;
		args->sclass.count = cnt;

		ret = nvअगर_object_ioctl(object, args, size, शून्य);
		अगर (ret == 0 && args->sclass.count <= cnt)
			अवरोध;
		cnt = args->sclass.count;
		kमुक्त(args);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	*psclass = kसुस्मृति(args->sclass.count, माप(**psclass), GFP_KERNEL);
	अगर (*psclass) अणु
		क्रम (i = 0; i < args->sclass.count; i++) अणु
			(*psclass)[i].oclass = args->sclass.oclass[i].oclass;
			(*psclass)[i].minver = args->sclass.oclass[i].minver;
			(*psclass)[i].maxver = args->sclass.oclass[i].maxver;
		पूर्ण
		ret = args->sclass.count;
	पूर्ण अन्यथा अणु
		ret = -ENOMEM;
	पूर्ण

	kमुक्त(args);
	वापस ret;
पूर्ण

u32
nvअगर_object_rd(काष्ठा nvअगर_object *object, पूर्णांक size, u64 addr)
अणु
	काष्ठा अणु
		काष्ठा nvअगर_ioctl_v0 ioctl;
		काष्ठा nvअगर_ioctl_rd_v0 rd;
	पूर्ण args = अणु
		.ioctl.type = NVIF_IOCTL_V0_RD,
		.rd.size = size,
		.rd.addr = addr,
	पूर्ण;
	पूर्णांक ret = nvअगर_object_ioctl(object, &args, माप(args), शून्य);
	अगर (ret) अणु
		/*XXX: warn? */
		वापस 0;
	पूर्ण
	वापस args.rd.data;
पूर्ण

व्योम
nvअगर_object_wr(काष्ठा nvअगर_object *object, पूर्णांक size, u64 addr, u32 data)
अणु
	काष्ठा अणु
		काष्ठा nvअगर_ioctl_v0 ioctl;
		काष्ठा nvअगर_ioctl_wr_v0 wr;
	पूर्ण args = अणु
		.ioctl.type = NVIF_IOCTL_V0_WR,
		.wr.size = size,
		.wr.addr = addr,
		.wr.data = data,
	पूर्ण;
	पूर्णांक ret = nvअगर_object_ioctl(object, &args, माप(args), शून्य);
	अगर (ret) अणु
		/*XXX: warn? */
	पूर्ण
पूर्ण

पूर्णांक
nvअगर_object_mthd(काष्ठा nvअगर_object *object, u32 mthd, व्योम *data, u32 size)
अणु
	काष्ठा अणु
		काष्ठा nvअगर_ioctl_v0 ioctl;
		काष्ठा nvअगर_ioctl_mthd_v0 mthd;
	पूर्ण *args;
	u8 stack[128];
	पूर्णांक ret;

	अगर (माप(*args) + size > माप(stack)) अणु
		अगर (!(args = kदो_स्मृति(माप(*args) + size, GFP_KERNEL)))
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		args = (व्योम *)stack;
	पूर्ण
	args->ioctl.version = 0;
	args->ioctl.type = NVIF_IOCTL_V0_MTHD;
	args->mthd.version = 0;
	args->mthd.method = mthd;

	स_नकल(args->mthd.data, data, size);
	ret = nvअगर_object_ioctl(object, args, माप(*args) + size, शून्य);
	स_नकल(data, args->mthd.data, size);
	अगर (args != (व्योम *)stack)
		kमुक्त(args);
	वापस ret;
पूर्ण

व्योम
nvअगर_object_unmap_handle(काष्ठा nvअगर_object *object)
अणु
	काष्ठा अणु
		काष्ठा nvअगर_ioctl_v0 ioctl;
		काष्ठा nvअगर_ioctl_unmap unmap;
	पूर्ण args = अणु
		.ioctl.type = NVIF_IOCTL_V0_UNMAP,
	पूर्ण;

	nvअगर_object_ioctl(object, &args, माप(args), शून्य);
पूर्ण

पूर्णांक
nvअगर_object_map_handle(काष्ठा nvअगर_object *object, व्योम *argv, u32 argc,
		       u64 *handle, u64 *length)
अणु
	काष्ठा अणु
		काष्ठा nvअगर_ioctl_v0 ioctl;
		काष्ठा nvअगर_ioctl_map_v0 map;
	पूर्ण *args;
	u32 argn = माप(*args) + argc;
	पूर्णांक ret, maptype;

	अगर (!(args = kzalloc(argn, GFP_KERNEL)))
		वापस -ENOMEM;
	args->ioctl.type = NVIF_IOCTL_V0_MAP;
	स_नकल(args->map.data, argv, argc);

	ret = nvअगर_object_ioctl(object, args, argn, शून्य);
	*handle = args->map.handle;
	*length = args->map.length;
	maptype = args->map.type;
	kमुक्त(args);
	वापस ret ? ret : (maptype == NVIF_IOCTL_MAP_V0_IO);
पूर्ण

व्योम
nvअगर_object_unmap(काष्ठा nvअगर_object *object)
अणु
	काष्ठा nvअगर_client *client = object->client;
	अगर (object->map.ptr) अणु
		अगर (object->map.size) अणु
			client->driver->unmap(client, object->map.ptr,
						      object->map.size);
			object->map.size = 0;
		पूर्ण
		object->map.ptr = शून्य;
		nvअगर_object_unmap_handle(object);
	पूर्ण
पूर्ण

पूर्णांक
nvअगर_object_map(काष्ठा nvअगर_object *object, व्योम *argv, u32 argc)
अणु
	काष्ठा nvअगर_client *client = object->client;
	u64 handle, length;
	पूर्णांक ret = nvअगर_object_map_handle(object, argv, argc, &handle, &length);
	अगर (ret >= 0) अणु
		अगर (ret) अणु
			object->map.ptr = client->driver->map(client,
							      handle,
							      length);
			अगर (ret = -ENOMEM, object->map.ptr) अणु
				object->map.size = length;
				वापस 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			object->map.ptr = (व्योम *)(अचिन्हित दीर्घ)handle;
			वापस 0;
		पूर्ण
		nvअगर_object_unmap_handle(object);
	पूर्ण
	वापस ret;
पूर्ण

व्योम
nvअगर_object_dtor(काष्ठा nvअगर_object *object)
अणु
	काष्ठा अणु
		काष्ठा nvअगर_ioctl_v0 ioctl;
		काष्ठा nvअगर_ioctl_del del;
	पूर्ण args = अणु
		.ioctl.type = NVIF_IOCTL_V0_DEL,
	पूर्ण;

	अगर (!object->client)
		वापस;

	nvअगर_object_unmap(object);
	nvअगर_object_ioctl(object, &args, माप(args), शून्य);
	object->client = शून्य;
पूर्ण

पूर्णांक
nvअगर_object_ctor(काष्ठा nvअगर_object *parent, स्थिर अक्षर *name, u32 handle,
		 s32 oclass, व्योम *data, u32 size, काष्ठा nvअगर_object *object)
अणु
	काष्ठा अणु
		काष्ठा nvअगर_ioctl_v0 ioctl;
		काष्ठा nvअगर_ioctl_new_v0 new;
	पूर्ण *args;
	पूर्णांक ret = 0;

	object->client = शून्य;
	object->name = name ? name : "nvifObject";
	object->handle = handle;
	object->oclass = oclass;
	object->map.ptr = शून्य;
	object->map.size = 0;

	अगर (parent) अणु
		अगर (!(args = kदो_स्मृति(माप(*args) + size, GFP_KERNEL))) अणु
			nvअगर_object_dtor(object);
			वापस -ENOMEM;
		पूर्ण

		object->parent = parent->parent;

		args->ioctl.version = 0;
		args->ioctl.type = NVIF_IOCTL_V0_NEW;
		args->new.version = 0;
		args->new.route = parent->client->route;
		args->new.token = nvअगर_handle(object);
		args->new.object = nvअगर_handle(object);
		args->new.handle = handle;
		args->new.oclass = oclass;

		स_नकल(args->new.data, data, size);
		ret = nvअगर_object_ioctl(parent, args, माप(*args) + size,
					&object->priv);
		स_नकल(data, args->new.data, size);
		kमुक्त(args);
		अगर (ret == 0)
			object->client = parent->client;
	पूर्ण

	अगर (ret)
		nvअगर_object_dtor(object);
	वापस ret;
पूर्ण
