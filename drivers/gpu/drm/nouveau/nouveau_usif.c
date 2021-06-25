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

#समावेश "nouveau_drv.h"
#समावेश "nouveau_usif.h"
#समावेश "nouveau_abi16.h"

#समावेश <nvअगर/notअगरy.h>
#समावेश <nvअगर/unpack.h>
#समावेश <nvअगर/client.h>
#समावेश <nvअगर/event.h>
#समावेश <nvअगर/ioctl.h>

काष्ठा usअगर_notअगरy_p अणु
	काष्ठा drm_pending_event base;
	काष्ठा अणु
		काष्ठा drm_event base;
		u8 data[];
	पूर्ण e;
पूर्ण;

काष्ठा usअगर_notअगरy अणु
	काष्ठा list_head head;
	atomic_t enabled;
	u32 handle;
	u16 reply;
	u8  route;
	u64 token;
	काष्ठा usअगर_notअगरy_p *p;
पूर्ण;

अटल अंतरभूत काष्ठा usअगर_notअगरy *
usअगर_notअगरy_find(काष्ठा drm_file *filp, u32 handle)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(filp);
	काष्ठा usअगर_notअगरy *ntfy;
	list_क्रम_each_entry(ntfy, &cli->notअगरys, head) अणु
		अगर (ntfy->handle == handle)
			वापस ntfy;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
usअगर_notअगरy_dtor(काष्ठा usअगर_notअगरy *ntfy)
अणु
	list_del(&ntfy->head);
	kमुक्त(ntfy);
पूर्ण

पूर्णांक
usअगर_notअगरy(स्थिर व्योम *header, u32 length, स्थिर व्योम *data, u32 size)
अणु
	काष्ठा usअगर_notअगरy *ntfy = शून्य;
	स्थिर जोड़ अणु
		काष्ठा nvअगर_notअगरy_rep_v0 v0;
	पूर्ण *rep = header;
	काष्ठा drm_device *dev;
	काष्ठा drm_file *filp;
	अचिन्हित दीर्घ flags;

	अगर (length == माप(rep->v0) && rep->v0.version == 0) अणु
		अगर (WARN_ON(!(ntfy = (व्योम *)(अचिन्हित दीर्घ)rep->v0.token)))
			वापस NVIF_NOTIFY_DROP;
		BUG_ON(rep->v0.route != NVDRM_NOTIFY_USIF);
	पूर्ण अन्यथा
	अगर (WARN_ON(1))
		वापस NVIF_NOTIFY_DROP;

	अगर (WARN_ON(!ntfy->p || ntfy->reply != (length + size)))
		वापस NVIF_NOTIFY_DROP;
	filp = ntfy->p->base.file_priv;
	dev = filp->minor->dev;

	स_नकल(&ntfy->p->e.data[0], header, length);
	स_नकल(&ntfy->p->e.data[length], data, size);
	चयन (rep->v0.version) अणु
	हाल 0: अणु
		काष्ठा nvअगर_notअगरy_rep_v0 *rep = (व्योम *)ntfy->p->e.data;
		rep->route = ntfy->route;
		rep->token = ntfy->token;
	पूर्ण
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&dev->event_lock, flags);
	अगर (!WARN_ON(filp->event_space < ntfy->p->e.base.length)) अणु
		list_add_tail(&ntfy->p->base.link, &filp->event_list);
		filp->event_space -= ntfy->p->e.base.length;
	पूर्ण
	wake_up_पूर्णांकerruptible(&filp->event_रुको);
	spin_unlock_irqrestore(&dev->event_lock, flags);
	atomic_set(&ntfy->enabled, 0);
	वापस NVIF_NOTIFY_DROP;
पूर्ण

अटल पूर्णांक
usअगर_notअगरy_new(काष्ठा drm_file *f, व्योम *data, u32 size, व्योम *argv, u32 argc)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(f);
	काष्ठा nvअगर_client *client = &cli->base;
	जोड़ अणु
		काष्ठा nvअगर_ioctl_ntfy_new_v0 v0;
	पूर्ण *args = data;
	जोड़ अणु
		काष्ठा nvअगर_notअगरy_req_v0 v0;
	पूर्ण *req;
	काष्ठा usअगर_notअगरy *ntfy;
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
		अगर (usअगर_notअगरy_find(f, args->v0.index))
			वापस -EEXIST;
	पूर्ण अन्यथा
		वापस ret;
	req = data;
	ret = -ENOSYS;

	अगर (!(ntfy = kदो_स्मृति(माप(*ntfy), GFP_KERNEL)))
		वापस -ENOMEM;
	atomic_set(&ntfy->enabled, 0);

	अगर (!(ret = nvअगर_unpack(ret, &data, &size, req->v0, 0, 0, true))) अणु
		ntfy->reply = माप(काष्ठा nvअगर_notअगरy_rep_v0) + req->v0.reply;
		ntfy->route = req->v0.route;
		ntfy->token = req->v0.token;
		req->v0.route = NVDRM_NOTIFY_USIF;
		req->v0.token = (अचिन्हित दीर्घ)(व्योम *)ntfy;
		ret = nvअगर_client_ioctl(client, argv, argc);
		req->v0.token = ntfy->token;
		req->v0.route = ntfy->route;
		ntfy->handle = args->v0.index;
	पूर्ण

	अगर (ret == 0)
		list_add(&ntfy->head, &cli->notअगरys);
	अगर (ret)
		kमुक्त(ntfy);
	वापस ret;
पूर्ण

अटल पूर्णांक
usअगर_notअगरy_del(काष्ठा drm_file *f, व्योम *data, u32 size, व्योम *argv, u32 argc)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(f);
	काष्ठा nvअगर_client *client = &cli->base;
	जोड़ अणु
		काष्ठा nvअगर_ioctl_ntfy_del_v0 v0;
	पूर्ण *args = data;
	काष्ठा usअगर_notअगरy *ntfy;
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
		अगर (!(ntfy = usअगर_notअगरy_find(f, args->v0.index)))
			वापस -ENOENT;
	पूर्ण अन्यथा
		वापस ret;

	ret = nvअगर_client_ioctl(client, argv, argc);
	अगर (ret == 0)
		usअगर_notअगरy_dtor(ntfy);
	वापस ret;
पूर्ण

अटल पूर्णांक
usअगर_notअगरy_get(काष्ठा drm_file *f, व्योम *data, u32 size, व्योम *argv, u32 argc)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(f);
	काष्ठा nvअगर_client *client = &cli->base;
	जोड़ अणु
		काष्ठा nvअगर_ioctl_ntfy_del_v0 v0;
	पूर्ण *args = data;
	काष्ठा usअगर_notअगरy *ntfy;
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
		अगर (!(ntfy = usअगर_notअगरy_find(f, args->v0.index)))
			वापस -ENOENT;
	पूर्ण अन्यथा
		वापस ret;

	अगर (atomic_xchg(&ntfy->enabled, 1))
		वापस 0;

	ntfy->p = kदो_स्मृति(माप(*ntfy->p) + ntfy->reply, GFP_KERNEL);
	अगर (ret = -ENOMEM, !ntfy->p)
		जाओ करोne;
	ntfy->p->base.event = &ntfy->p->e.base;
	ntfy->p->base.file_priv = f;
	ntfy->p->e.base.type = DRM_NOUVEAU_EVENT_NVIF;
	ntfy->p->e.base.length = माप(ntfy->p->e.base) + ntfy->reply;

	ret = nvअगर_client_ioctl(client, argv, argc);
करोne:
	अगर (ret) अणु
		atomic_set(&ntfy->enabled, 0);
		kमुक्त(ntfy->p);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
usअगर_notअगरy_put(काष्ठा drm_file *f, व्योम *data, u32 size, व्योम *argv, u32 argc)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(f);
	काष्ठा nvअगर_client *client = &cli->base;
	जोड़ अणु
		काष्ठा nvअगर_ioctl_ntfy_put_v0 v0;
	पूर्ण *args = data;
	काष्ठा usअगर_notअगरy *ntfy;
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
		अगर (!(ntfy = usअगर_notअगरy_find(f, args->v0.index)))
			वापस -ENOENT;
	पूर्ण अन्यथा
		वापस ret;

	ret = nvअगर_client_ioctl(client, argv, argc);
	अगर (ret == 0 && atomic_xchg(&ntfy->enabled, 0))
		kमुक्त(ntfy->p);
	वापस ret;
पूर्ण

काष्ठा usअगर_object अणु
	काष्ठा list_head head;
	काष्ठा list_head ntfy;
	u8  route;
	u64 token;
पूर्ण;

अटल व्योम
usअगर_object_dtor(काष्ठा usअगर_object *object)
अणु
	list_del(&object->head);
	kमुक्त(object);
पूर्ण

अटल पूर्णांक
usअगर_object_new(काष्ठा drm_file *f, व्योम *data, u32 size, व्योम *argv, u32 argc)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(f);
	काष्ठा nvअगर_client *client = &cli->base;
	जोड़ अणु
		काष्ठा nvअगर_ioctl_new_v0 v0;
	पूर्ण *args = data;
	काष्ठा usअगर_object *object;
	पूर्णांक ret = -ENOSYS;

	अगर (!(object = kदो_स्मृति(माप(*object), GFP_KERNEL)))
		वापस -ENOMEM;
	list_add(&object->head, &cli->objects);

	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
		object->route = args->v0.route;
		object->token = args->v0.token;
		args->v0.route = NVDRM_OBJECT_USIF;
		args->v0.token = (अचिन्हित दीर्घ)(व्योम *)object;
		ret = nvअगर_client_ioctl(client, argv, argc);
		args->v0.token = object->token;
		args->v0.route = object->route;
	पूर्ण

	अगर (ret)
		usअगर_object_dtor(object);
	वापस ret;
पूर्ण

पूर्णांक
usअगर_ioctl(काष्ठा drm_file *filp, व्योम __user *user, u32 argc)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(filp);
	काष्ठा nvअगर_client *client = &cli->base;
	व्योम *data = kदो_स्मृति(argc, GFP_KERNEL);
	u32   size = argc;
	जोड़ अणु
		काष्ठा nvअगर_ioctl_v0 v0;
	पूर्ण *argv = data;
	काष्ठा usअगर_object *object;
	u8 owner;
	पूर्णांक ret;

	अगर (ret = -ENOMEM, !argv)
		जाओ करोne;
	अगर (ret = -EFAULT, copy_from_user(argv, user, size))
		जाओ करोne;

	अगर (!(ret = nvअगर_unpack(-ENOSYS, &data, &size, argv->v0, 0, 0, true))) अणु
		/* block access to objects not created via this पूर्णांकerface */
		owner = argv->v0.owner;
		अगर (argv->v0.object == 0ULL &&
		    argv->v0.type != NVIF_IOCTL_V0_DEL)
			argv->v0.owner = NVDRM_OBJECT_ANY; /* except client */
		अन्यथा
			argv->v0.owner = NVDRM_OBJECT_USIF;
	पूर्ण अन्यथा
		जाओ करोne;

	/* USIF slightly abuses some वापस-only ioctl members in order
	 * to provide पूर्णांकeroperability with the older ABI16 objects
	 */
	mutex_lock(&cli->mutex);
	अगर (argv->v0.route) अणु
		अगर (ret = -EINVAL, argv->v0.route == 0xff)
			ret = nouveau_abi16_usअगर(filp, argv, argc);
		अगर (ret) अणु
			mutex_unlock(&cli->mutex);
			जाओ करोne;
		पूर्ण
	पूर्ण

	चयन (argv->v0.type) अणु
	हाल NVIF_IOCTL_V0_NEW:
		ret = usअगर_object_new(filp, data, size, argv, argc);
		अवरोध;
	हाल NVIF_IOCTL_V0_NTFY_NEW:
		ret = usअगर_notअगरy_new(filp, data, size, argv, argc);
		अवरोध;
	हाल NVIF_IOCTL_V0_NTFY_DEL:
		ret = usअगर_notअगरy_del(filp, data, size, argv, argc);
		अवरोध;
	हाल NVIF_IOCTL_V0_NTFY_GET:
		ret = usअगर_notअगरy_get(filp, data, size, argv, argc);
		अवरोध;
	हाल NVIF_IOCTL_V0_NTFY_PUT:
		ret = usअगर_notअगरy_put(filp, data, size, argv, argc);
		अवरोध;
	शेष:
		ret = nvअगर_client_ioctl(client, argv, argc);
		अवरोध;
	पूर्ण
	अगर (argv->v0.route == NVDRM_OBJECT_USIF) अणु
		object = (व्योम *)(अचिन्हित दीर्घ)argv->v0.token;
		argv->v0.route = object->route;
		argv->v0.token = object->token;
		अगर (ret == 0 && argv->v0.type == NVIF_IOCTL_V0_DEL) अणु
			list_del(&object->head);
			kमुक्त(object);
		पूर्ण
	पूर्ण अन्यथा अणु
		argv->v0.route = NVIF_IOCTL_V0_ROUTE_HIDDEN;
		argv->v0.token = 0;
	पूर्ण
	argv->v0.owner = owner;
	mutex_unlock(&cli->mutex);

	अगर (copy_to_user(user, argv, argc))
		ret = -EFAULT;
करोne:
	kमुक्त(argv);
	वापस ret;
पूर्ण

व्योम
usअगर_client_fini(काष्ठा nouveau_cli *cli)
अणु
	काष्ठा usअगर_object *object, *otemp;
	काष्ठा usअगर_notअगरy *notअगरy, *ntemp;

	list_क्रम_each_entry_safe(notअगरy, ntemp, &cli->notअगरys, head) अणु
		usअगर_notअगरy_dtor(notअगरy);
	पूर्ण

	list_क्रम_each_entry_safe(object, otemp, &cli->objects, head) अणु
		usअगर_object_dtor(object);
	पूर्ण
पूर्ण

व्योम
usअगर_client_init(काष्ठा nouveau_cli *cli)
अणु
	INIT_LIST_HEAD(&cli->objects);
	INIT_LIST_HEAD(&cli->notअगरys);
पूर्ण
