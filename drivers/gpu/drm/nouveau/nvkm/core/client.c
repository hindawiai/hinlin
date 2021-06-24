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
#समावेश <core/client.h>
#समावेश <core/device.h>
#समावेश <core/notअगरy.h>
#समावेश <core/option.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/event.h>
#समावेश <nvअगर/अगर0000.h>
#समावेश <nvअगर/unpack.h>

अटल पूर्णांक
nvkm_uclient_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *argv, u32 argc,
		 काष्ठा nvkm_object **pobject)
अणु
	जोड़ अणु
		काष्ठा nvअगर_client_v0 v0;
	पूर्ण *args = argv;
	काष्ठा nvkm_client *client;
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unpack(ret, &argv, &argc, args->v0, 0, 0, false)))अणु
		args->v0.name[माप(args->v0.name) - 1] = 0;
		ret = nvkm_client_new(args->v0.name, args->v0.device, शून्य,
				      शून्य, oclass->client->ntfy, &client);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा
		वापस ret;

	client->object.client = oclass->client;
	client->object.handle = oclass->handle;
	client->object.route  = oclass->route;
	client->object.token  = oclass->token;
	client->object.object = oclass->object;
	client->debug = oclass->client->debug;
	*pobject = &client->object;
	वापस 0;
पूर्ण

स्थिर काष्ठा nvkm_sclass
nvkm_uclient_sclass = अणु
	.oclass = NVIF_CLASS_CLIENT,
	.minver = 0,
	.maxver = 0,
	.ctor = nvkm_uclient_new,
पूर्ण;

काष्ठा nvkm_client_notअगरy अणु
	काष्ठा nvkm_client *client;
	काष्ठा nvkm_notअगरy n;
	u8 version;
	u8 size;
	जोड़ अणु
		काष्ठा nvअगर_notअगरy_rep_v0 v0;
	पूर्ण rep;
पूर्ण;

अटल पूर्णांक
nvkm_client_notअगरy(काष्ठा nvkm_notअगरy *n)
अणु
	काष्ठा nvkm_client_notअगरy *notअगरy = container_of(n, typeof(*notअगरy), n);
	काष्ठा nvkm_client *client = notअगरy->client;
	वापस client->ntfy(&notअगरy->rep, notअगरy->size, n->data, n->size);
पूर्ण

पूर्णांक
nvkm_client_notअगरy_put(काष्ठा nvkm_client *client, पूर्णांक index)
अणु
	अगर (index < ARRAY_SIZE(client->notअगरy)) अणु
		अगर (client->notअगरy[index]) अणु
			nvkm_notअगरy_put(&client->notअगरy[index]->n);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOENT;
पूर्ण

पूर्णांक
nvkm_client_notअगरy_get(काष्ठा nvkm_client *client, पूर्णांक index)
अणु
	अगर (index < ARRAY_SIZE(client->notअगरy)) अणु
		अगर (client->notअगरy[index]) अणु
			nvkm_notअगरy_get(&client->notअगरy[index]->n);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOENT;
पूर्ण

पूर्णांक
nvkm_client_notअगरy_del(काष्ठा nvkm_client *client, पूर्णांक index)
अणु
	अगर (index < ARRAY_SIZE(client->notअगरy)) अणु
		अगर (client->notअगरy[index]) अणु
			nvkm_notअगरy_fini(&client->notअगरy[index]->n);
			kमुक्त(client->notअगरy[index]);
			client->notअगरy[index] = शून्य;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOENT;
पूर्ण

पूर्णांक
nvkm_client_notअगरy_new(काष्ठा nvkm_object *object,
		       काष्ठा nvkm_event *event, व्योम *data, u32 size)
अणु
	काष्ठा nvkm_client *client = object->client;
	काष्ठा nvkm_client_notअगरy *notअगरy;
	जोड़ अणु
		काष्ठा nvअगर_notअगरy_req_v0 v0;
	पूर्ण *req = data;
	u8  index, reply;
	पूर्णांक ret = -ENOSYS;

	क्रम (index = 0; index < ARRAY_SIZE(client->notअगरy); index++) अणु
		अगर (!client->notअगरy[index])
			अवरोध;
	पूर्ण

	अगर (index == ARRAY_SIZE(client->notअगरy))
		वापस -ENOSPC;

	notअगरy = kzalloc(माप(*notअगरy), GFP_KERNEL);
	अगर (!notअगरy)
		वापस -ENOMEM;

	nvअगर_ioctl(object, "notify new size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, req->v0, 0, 0, true))) अणु
		nvअगर_ioctl(object, "notify new vers %d reply %d route %02x "
				   "token %llx\n", req->v0.version,
			   req->v0.reply, req->v0.route, req->v0.token);
		notअगरy->version = req->v0.version;
		notअगरy->size = माप(notअगरy->rep.v0);
		notअगरy->rep.v0.version = req->v0.version;
		notअगरy->rep.v0.route = req->v0.route;
		notअगरy->rep.v0.token = req->v0.token;
		reply = req->v0.reply;
	पूर्ण

	अगर (ret == 0) अणु
		ret = nvkm_notअगरy_init(object, event, nvkm_client_notअगरy,
				       false, data, size, reply, &notअगरy->n);
		अगर (ret == 0) अणु
			client->notअगरy[index] = notअगरy;
			notअगरy->client = client;
			वापस index;
		पूर्ण
	पूर्ण

	kमुक्त(notअगरy);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func nvkm_client;
काष्ठा nvkm_client *
nvkm_client_search(काष्ठा nvkm_client *client, u64 handle)
अणु
	काष्ठा nvkm_object *object;

	object = nvkm_object_search(client, handle, &nvkm_client);
	अगर (IS_ERR(object))
		वापस (व्योम *)object;

	वापस nvkm_client(object);
पूर्ण

अटल पूर्णांक
nvkm_client_mthd_devlist(काष्ठा nvkm_client *client, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nvअगर_client_devlist_v0 v0;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(&client->object, "client devlist size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
		nvअगर_ioctl(&client->object, "client devlist vers %d count %d\n",
			   args->v0.version, args->v0.count);
		अगर (size == माप(args->v0.device[0]) * args->v0.count) अणु
			ret = nvkm_device_list(args->v0.device, args->v0.count);
			अगर (ret >= 0) अणु
				args->v0.count = ret;
				ret = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_client_mthd(काष्ठा nvkm_object *object, u32 mthd, व्योम *data, u32 size)
अणु
	काष्ठा nvkm_client *client = nvkm_client(object);
	चयन (mthd) अणु
	हाल NVIF_CLIENT_V0_DEVLIST:
		वापस nvkm_client_mthd_devlist(client, data, size);
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nvkm_client_child_new(स्थिर काष्ठा nvkm_oclass *oclass,
		      व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	वापस oclass->base.ctor(oclass, data, size, pobject);
पूर्ण

अटल पूर्णांक
nvkm_client_child_get(काष्ठा nvkm_object *object, पूर्णांक index,
		      काष्ठा nvkm_oclass *oclass)
अणु
	स्थिर काष्ठा nvkm_sclass *sclass;

	चयन (index) अणु
	हाल 0: sclass = &nvkm_uclient_sclass; अवरोध;
	हाल 1: sclass = &nvkm_udevice_sclass; अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	oclass->ctor = nvkm_client_child_new;
	oclass->base = *sclass;
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_client_fini(काष्ठा nvkm_object *object, bool suspend)
अणु
	काष्ठा nvkm_client *client = nvkm_client(object);
	स्थिर अक्षर *name[2] = अणु "fini", "suspend" पूर्ण;
	पूर्णांक i;
	nvअगर_debug(object, "%s notify\n", name[suspend]);
	क्रम (i = 0; i < ARRAY_SIZE(client->notअगरy); i++)
		nvkm_client_notअगरy_put(client, i);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_client_dtor(काष्ठा nvkm_object *object)
अणु
	काष्ठा nvkm_client *client = nvkm_client(object);
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(client->notअगरy); i++)
		nvkm_client_notअगरy_del(client, i);
	वापस client;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nvkm_client = अणु
	.dtor = nvkm_client_dtor,
	.fini = nvkm_client_fini,
	.mthd = nvkm_client_mthd,
	.sclass = nvkm_client_child_get,
पूर्ण;

पूर्णांक
nvkm_client_new(स्थिर अक्षर *name, u64 device, स्थिर अक्षर *cfg,
		स्थिर अक्षर *dbg,
		पूर्णांक (*ntfy)(स्थिर व्योम *, u32, स्थिर व्योम *, u32),
		काष्ठा nvkm_client **pclient)
अणु
	काष्ठा nvkm_oclass oclass = अणु .base = nvkm_uclient_sclass पूर्ण;
	काष्ठा nvkm_client *client;

	अगर (!(client = *pclient = kzalloc(माप(*client), GFP_KERNEL)))
		वापस -ENOMEM;
	oclass.client = client;

	nvkm_object_ctor(&nvkm_client, &oclass, &client->object);
	snम_लिखो(client->name, माप(client->name), "%s", name);
	client->device = device;
	client->debug = nvkm_dbgopt(dbg, "CLIENT");
	client->objroot = RB_ROOT;
	client->ntfy = ntfy;
	INIT_LIST_HEAD(&client->umem);
	spin_lock_init(&client->lock);
	वापस 0;
पूर्ण
