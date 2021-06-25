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

#समावेश <nvअगर/client.h>
#समावेश <nvअगर/driver.h>
#समावेश <nvअगर/notअगरy.h>
#समावेश <nvअगर/object.h>
#समावेश <nvअगर/ioctl.h>
#समावेश <nvअगर/event.h>

अटल अंतरभूत पूर्णांक
nvअगर_notअगरy_put_(काष्ठा nvअगर_notअगरy *notअगरy)
अणु
	काष्ठा nvअगर_object *object = notअगरy->object;
	काष्ठा अणु
		काष्ठा nvअगर_ioctl_v0 ioctl;
		काष्ठा nvअगर_ioctl_ntfy_put_v0 ntfy;
	पूर्ण args = अणु
		.ioctl.type = NVIF_IOCTL_V0_NTFY_PUT,
		.ntfy.index = notअगरy->index,
	पूर्ण;

	अगर (atomic_inc_वापस(&notअगरy->अ_दोnt) != 1)
		वापस 0;

	वापस nvअगर_object_ioctl(object, &args, माप(args), शून्य);
पूर्ण

पूर्णांक
nvअगर_notअगरy_put(काष्ठा nvअगर_notअगरy *notअगरy)
अणु
	अगर (likely(notअगरy->object) &&
	    test_and_clear_bit(NVIF_NOTIFY_USER, &notअगरy->flags)) अणु
		पूर्णांक ret = nvअगर_notअगरy_put_(notअगरy);
		अगर (test_bit(NVIF_NOTIFY_WORK, &notअगरy->flags))
			flush_work(&notअगरy->work);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
nvअगर_notअगरy_get_(काष्ठा nvअगर_notअगरy *notअगरy)
अणु
	काष्ठा nvअगर_object *object = notअगरy->object;
	काष्ठा अणु
		काष्ठा nvअगर_ioctl_v0 ioctl;
		काष्ठा nvअगर_ioctl_ntfy_get_v0 ntfy;
	पूर्ण args = अणु
		.ioctl.type = NVIF_IOCTL_V0_NTFY_GET,
		.ntfy.index = notअगरy->index,
	पूर्ण;

	अगर (atomic_dec_वापस(&notअगरy->अ_दोnt) != 0)
		वापस 0;

	वापस nvअगर_object_ioctl(object, &args, माप(args), शून्य);
पूर्ण

पूर्णांक
nvअगर_notअगरy_get(काष्ठा nvअगर_notअगरy *notअगरy)
अणु
	अगर (likely(notअगरy->object) &&
	    !test_and_set_bit(NVIF_NOTIFY_USER, &notअगरy->flags))
		वापस nvअगर_notअगरy_get_(notअगरy);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
nvअगर_notअगरy_func(काष्ठा nvअगर_notअगरy *notअगरy, bool keep)
अणु
	पूर्णांक ret = notअगरy->func(notअगरy);
	अगर (ret == NVIF_NOTIFY_KEEP ||
	    !test_and_clear_bit(NVIF_NOTIFY_USER, &notअगरy->flags)) अणु
		अगर (!keep)
			atomic_dec(&notअगरy->अ_दोnt);
		अन्यथा
			nvअगर_notअगरy_get_(notअगरy);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम
nvअगर_notअगरy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvअगर_notअगरy *notअगरy = container_of(work, typeof(*notअगरy), work);
	nvअगर_notअगरy_func(notअगरy, true);
पूर्ण

पूर्णांक
nvअगर_notअगरy(स्थिर व्योम *header, u32 length, स्थिर व्योम *data, u32 size)
अणु
	काष्ठा nvअगर_notअगरy *notअगरy = शून्य;
	स्थिर जोड़ अणु
		काष्ठा nvअगर_notअगरy_rep_v0 v0;
	पूर्ण *args = header;
	पूर्णांक ret = NVIF_NOTIFY_DROP;

	अगर (length == माप(args->v0) && args->v0.version == 0) अणु
		अगर (WARN_ON(args->v0.route))
			वापस NVIF_NOTIFY_DROP;
		notअगरy = (व्योम *)(अचिन्हित दीर्घ)args->v0.token;
	पूर्ण

	अगर (!WARN_ON(notअगरy == शून्य)) अणु
		काष्ठा nvअगर_client *client = notअगरy->object->client;
		अगर (!WARN_ON(notअगरy->size != size)) अणु
			atomic_inc(&notअगरy->अ_दोnt);
			अगर (test_bit(NVIF_NOTIFY_WORK, &notअगरy->flags)) अणु
				स_नकल((व्योम *)notअगरy->data, data, size);
				schedule_work(&notअगरy->work);
				वापस NVIF_NOTIFY_DROP;
			पूर्ण
			notअगरy->data = data;
			ret = nvअगर_notअगरy_func(notअगरy, client->driver->keep);
			notअगरy->data = शून्य;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
nvअगर_notअगरy_dtor(काष्ठा nvअगर_notअगरy *notअगरy)
अणु
	काष्ठा nvअगर_object *object = notअगरy->object;
	काष्ठा अणु
		काष्ठा nvअगर_ioctl_v0 ioctl;
		काष्ठा nvअगर_ioctl_ntfy_del_v0 ntfy;
	पूर्ण args = अणु
		.ioctl.type = NVIF_IOCTL_V0_NTFY_DEL,
		.ntfy.index = notअगरy->index,
	पूर्ण;
	पूर्णांक ret = nvअगर_notअगरy_put(notअगरy);
	अगर (ret >= 0 && object) अणु
		ret = nvअगर_object_ioctl(object, &args, माप(args), शून्य);
		notअगरy->object = शून्य;
		kमुक्त((व्योम *)notअगरy->data);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक
nvअगर_notअगरy_ctor(काष्ठा nvअगर_object *object, स्थिर अक्षर *name,
		 पूर्णांक (*func)(काष्ठा nvअगर_notअगरy *), bool work, u8 event,
		 व्योम *data, u32 size, u32 reply, काष्ठा nvअगर_notअगरy *notअगरy)
अणु
	काष्ठा अणु
		काष्ठा nvअगर_ioctl_v0 ioctl;
		काष्ठा nvअगर_ioctl_ntfy_new_v0 ntfy;
		काष्ठा nvअगर_notअगरy_req_v0 req;
	पूर्ण *args;
	पूर्णांक ret = -ENOMEM;

	notअगरy->object = object;
	notअगरy->name = name ? name : "nvifNotify";
	notअगरy->flags = 0;
	atomic_set(&notअगरy->अ_दोnt, 1);
	notअगरy->func = func;
	notअगरy->data = शून्य;
	notअगरy->size = reply;
	अगर (work) अणु
		INIT_WORK(&notअगरy->work, nvअगर_notअगरy_work);
		set_bit(NVIF_NOTIFY_WORK, &notअगरy->flags);
		notअगरy->data = kदो_स्मृति(notअगरy->size, GFP_KERNEL);
		अगर (!notअगरy->data)
			जाओ करोne;
	पूर्ण

	अगर (!(args = kदो_स्मृति(माप(*args) + size, GFP_KERNEL)))
		जाओ करोne;
	args->ioctl.version = 0;
	args->ioctl.type = NVIF_IOCTL_V0_NTFY_NEW;
	args->ntfy.version = 0;
	args->ntfy.event = event;
	args->req.version = 0;
	args->req.reply = notअगरy->size;
	args->req.route = 0;
	args->req.token = (अचिन्हित दीर्घ)(व्योम *)notअगरy;

	स_नकल(args->req.data, data, size);
	ret = nvअगर_object_ioctl(object, args, माप(*args) + size, शून्य);
	notअगरy->index = args->ntfy.index;
	kमुक्त(args);
करोne:
	अगर (ret)
		nvअगर_notअगरy_dtor(notअगरy);
	वापस ret;
पूर्ण
