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
#समावेश <core/ioctl.h>
#समावेश <core/client.h>
#समावेश <core/engine.h>

#समावेश <nvअगर/unpack.h>
#समावेश <nvअगर/ioctl.h>

अटल पूर्णांक
nvkm_ioctl_nop(काष्ठा nvkm_client *client,
	       काष्ठा nvkm_object *object, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_ioctl_nop_v0 v0;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(object, "nop size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(object, "nop vers %lld\n", args->v0.version);
		args->v0.version = NVIF_VERSION_LATEST;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_ioctl_sclass(काष्ठा nvkm_client *client,
		  काष्ठा nvkm_object *object, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_ioctl_sclass_v0 v0;
	पूर्ण *args = data;
	काष्ठा nvkm_oclass oclass = अणु .client = client पूर्ण;
	पूर्णांक ret = -ENOSYS, i = 0;

	nvअगर_ioctl(object, "sclass size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
		nvअगर_ioctl(object, "sclass vers %d count %d\n",
			   args->v0.version, args->v0.count);
		अगर (size != args->v0.count * माप(args->v0.oclass[0]))
			वापस -EINVAL;

		जबतक (object->func->sclass &&
		       object->func->sclass(object, i, &oclass) >= 0) अणु
			अगर (i < args->v0.count) अणु
				args->v0.oclass[i].oclass = oclass.base.oclass;
				args->v0.oclass[i].minver = oclass.base.minver;
				args->v0.oclass[i].maxver = oclass.base.maxver;
			पूर्ण
			i++;
		पूर्ण

		args->v0.count = i;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_ioctl_new(काष्ठा nvkm_client *client,
	       काष्ठा nvkm_object *parent, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_ioctl_new_v0 v0;
	पूर्ण *args = data;
	काष्ठा nvkm_object *object = शून्य;
	काष्ठा nvkm_oclass oclass;
	पूर्णांक ret = -ENOSYS, i = 0;

	nvअगर_ioctl(parent, "new size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
		nvअगर_ioctl(parent, "new vers %d handle %08x class %08x "
				   "route %02x token %llx object %016llx\n",
			   args->v0.version, args->v0.handle, args->v0.oclass,
			   args->v0.route, args->v0.token, args->v0.object);
	पूर्ण अन्यथा
		वापस ret;

	अगर (!parent->func->sclass) अणु
		nvअगर_ioctl(parent, "cannot have children\n");
		वापस -EINVAL;
	पूर्ण

	करो अणु
		स_रखो(&oclass, 0x00, माप(oclass));
		oclass.handle = args->v0.handle;
		oclass.route  = args->v0.route;
		oclass.token  = args->v0.token;
		oclass.object = args->v0.object;
		oclass.client = client;
		oclass.parent = parent;
		ret = parent->func->sclass(parent, i++, &oclass);
		अगर (ret)
			वापस ret;
	पूर्ण जबतक (oclass.base.oclass != args->v0.oclass);

	अगर (oclass.engine) अणु
		oclass.engine = nvkm_engine_ref(oclass.engine);
		अगर (IS_ERR(oclass.engine))
			वापस PTR_ERR(oclass.engine);
	पूर्ण

	ret = oclass.ctor(&oclass, data, size, &object);
	nvkm_engine_unref(&oclass.engine);
	अगर (ret == 0) अणु
		ret = nvkm_object_init(object);
		अगर (ret == 0) अणु
			list_add(&object->head, &parent->tree);
			अगर (nvkm_object_insert(object)) अणु
				client->data = object;
				वापस 0;
			पूर्ण
			ret = -EEXIST;
		पूर्ण
		nvkm_object_fini(object, false);
	पूर्ण

	nvkm_object_del(&object);
	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_ioctl_del(काष्ठा nvkm_client *client,
	       काष्ठा nvkm_object *object, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_ioctl_del none;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(object, "delete size %d\n", size);
	अगर (!(ret = nvअगर_unvers(ret, &data, &size, args->none))) अणु
		nvअगर_ioctl(object, "delete\n");
		nvkm_object_fini(object, false);
		nvkm_object_del(&object);
	पूर्ण

	वापस ret ? ret : 1;
पूर्ण

अटल पूर्णांक
nvkm_ioctl_mthd(काष्ठा nvkm_client *client,
		काष्ठा nvkm_object *object, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_ioctl_mthd_v0 v0;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(object, "mthd size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
		nvअगर_ioctl(object, "mthd vers %d mthd %02x\n",
			   args->v0.version, args->v0.method);
		ret = nvkm_object_mthd(object, args->v0.method, data, size);
	पूर्ण

	वापस ret;
पूर्ण


अटल पूर्णांक
nvkm_ioctl_rd(काष्ठा nvkm_client *client,
	      काष्ठा nvkm_object *object, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_ioctl_rd_v0 v0;
	पूर्ण *args = data;
	जोड़ अणु
		u8  b08;
		u16 b16;
		u32 b32;
	पूर्ण v;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(object, "rd size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(object, "rd vers %d size %d addr %016llx\n",
			   args->v0.version, args->v0.size, args->v0.addr);
		चयन (args->v0.size) अणु
		हाल 1:
			ret = nvkm_object_rd08(object, args->v0.addr, &v.b08);
			args->v0.data = v.b08;
			अवरोध;
		हाल 2:
			ret = nvkm_object_rd16(object, args->v0.addr, &v.b16);
			args->v0.data = v.b16;
			अवरोध;
		हाल 4:
			ret = nvkm_object_rd32(object, args->v0.addr, &v.b32);
			args->v0.data = v.b32;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_ioctl_wr(काष्ठा nvkm_client *client,
	      काष्ठा nvkm_object *object, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_ioctl_wr_v0 v0;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(object, "wr size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(object,
			   "wr vers %d size %d addr %016llx data %08x\n",
			   args->v0.version, args->v0.size, args->v0.addr,
			   args->v0.data);
	पूर्ण अन्यथा
		वापस ret;

	चयन (args->v0.size) अणु
	हाल 1: वापस nvkm_object_wr08(object, args->v0.addr, args->v0.data);
	हाल 2: वापस nvkm_object_wr16(object, args->v0.addr, args->v0.data);
	हाल 4: वापस nvkm_object_wr32(object, args->v0.addr, args->v0.data);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nvkm_ioctl_map(काष्ठा nvkm_client *client,
	       काष्ठा nvkm_object *object, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_ioctl_map_v0 v0;
	पूर्ण *args = data;
	क्रमागत nvkm_object_map type;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(object, "map size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
		nvअगर_ioctl(object, "map vers %d\n", args->v0.version);
		ret = nvkm_object_map(object, data, size, &type,
				      &args->v0.handle,
				      &args->v0.length);
		अगर (type == NVKM_OBJECT_MAP_IO)
			args->v0.type = NVIF_IOCTL_MAP_V0_IO;
		अन्यथा
			args->v0.type = NVIF_IOCTL_MAP_V0_VA;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_ioctl_unmap(काष्ठा nvkm_client *client,
		 काष्ठा nvkm_object *object, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_ioctl_unmap none;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(object, "unmap size %d\n", size);
	अगर (!(ret = nvअगर_unvers(ret, &data, &size, args->none))) अणु
		nvअगर_ioctl(object, "unmap\n");
		ret = nvkm_object_unmap(object);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_ioctl_ntfy_new(काष्ठा nvkm_client *client,
		    काष्ठा nvkm_object *object, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_ioctl_ntfy_new_v0 v0;
	पूर्ण *args = data;
	काष्ठा nvkm_event *event;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(object, "ntfy new size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
		nvअगर_ioctl(object, "ntfy new vers %d event %02x\n",
			   args->v0.version, args->v0.event);
		ret = nvkm_object_ntfy(object, args->v0.event, &event);
		अगर (ret == 0) अणु
			ret = nvkm_client_notअगरy_new(object, event, data, size);
			अगर (ret >= 0) अणु
				args->v0.index = ret;
				ret = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_ioctl_ntfy_del(काष्ठा nvkm_client *client,
		    काष्ठा nvkm_object *object, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_ioctl_ntfy_del_v0 v0;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(object, "ntfy del size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(object, "ntfy del vers %d index %d\n",
			   args->v0.version, args->v0.index);
		ret = nvkm_client_notअगरy_del(client, args->v0.index);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_ioctl_ntfy_get(काष्ठा nvkm_client *client,
		    काष्ठा nvkm_object *object, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_ioctl_ntfy_get_v0 v0;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(object, "ntfy get size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(object, "ntfy get vers %d index %d\n",
			   args->v0.version, args->v0.index);
		ret = nvkm_client_notअगरy_get(client, args->v0.index);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_ioctl_ntfy_put(काष्ठा nvkm_client *client,
		    काष्ठा nvkm_object *object, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_ioctl_ntfy_put_v0 v0;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(object, "ntfy put size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(object, "ntfy put vers %d index %d\n",
			   args->v0.version, args->v0.index);
		ret = nvkm_client_notअगरy_put(client, args->v0.index);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा अणु
	पूर्णांक version;
	पूर्णांक (*func)(काष्ठा nvkm_client *, काष्ठा nvkm_object *, व्योम *, u32);
पूर्ण
nvkm_ioctl_v0[] = अणु
	अणु 0x00, nvkm_ioctl_nop पूर्ण,
	अणु 0x00, nvkm_ioctl_sclass पूर्ण,
	अणु 0x00, nvkm_ioctl_new पूर्ण,
	अणु 0x00, nvkm_ioctl_del पूर्ण,
	अणु 0x00, nvkm_ioctl_mthd पूर्ण,
	अणु 0x00, nvkm_ioctl_rd पूर्ण,
	अणु 0x00, nvkm_ioctl_wr पूर्ण,
	अणु 0x00, nvkm_ioctl_map पूर्ण,
	अणु 0x00, nvkm_ioctl_unmap पूर्ण,
	अणु 0x00, nvkm_ioctl_ntfy_new पूर्ण,
	अणु 0x00, nvkm_ioctl_ntfy_del पूर्ण,
	अणु 0x00, nvkm_ioctl_ntfy_get पूर्ण,
	अणु 0x00, nvkm_ioctl_ntfy_put पूर्ण,
पूर्ण;

अटल पूर्णांक
nvkm_ioctl_path(काष्ठा nvkm_client *client, u64 handle, u32 type,
		व्योम *data, u32 size, u8 owner, u8 *route, u64 *token)
अणु
	काष्ठा nvkm_object *object;
	पूर्णांक ret;

	object = nvkm_object_search(client, handle, शून्य);
	अगर (IS_ERR(object)) अणु
		nvअगर_ioctl(&client->object, "object not found\n");
		वापस PTR_ERR(object);
	पूर्ण

	अगर (owner != NVIF_IOCTL_V0_OWNER_ANY && owner != object->route) अणु
		nvअगर_ioctl(&client->object, "route != owner\n");
		वापस -EACCES;
	पूर्ण
	*route = object->route;
	*token = object->token;

	अगर (ret = -EINVAL, type < ARRAY_SIZE(nvkm_ioctl_v0)) अणु
		अगर (nvkm_ioctl_v0[type].version == 0)
			ret = nvkm_ioctl_v0[type].func(client, object, data, size);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
nvkm_ioctl(काष्ठा nvkm_client *client, bool supervisor,
	   व्योम *data, u32 size, व्योम **hack)
अणु
	काष्ठा nvkm_object *object = &client->object;
	जोड़ अणु
		काष्ठा nvअगर_ioctl_v0 v0;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	client->super = supervisor;
	nvअगर_ioctl(object, "size %d\n", size);

	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
		nvअगर_ioctl(object,
			   "vers %d type %02x object %016llx owner %02x\n",
			   args->v0.version, args->v0.type, args->v0.object,
			   args->v0.owner);
		ret = nvkm_ioctl_path(client, args->v0.object, args->v0.type,
				      data, size, args->v0.owner,
				      &args->v0.route, &args->v0.token);
	पूर्ण

	अगर (ret != 1) अणु
		nvअगर_ioctl(object, "return %d\n", ret);
		अगर (hack) अणु
			*hack = client->data;
			client->data = शून्य;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
