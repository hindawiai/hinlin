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
#समावेश <core/notअगरy.h>
#समावेश <core/event.h>

अटल अंतरभूत व्योम
nvkm_notअगरy_put_locked(काष्ठा nvkm_notअगरy *notअगरy)
अणु
	अगर (notअगरy->block++ == 0)
		nvkm_event_put(notअगरy->event, notअगरy->types, notअगरy->index);
पूर्ण

व्योम
nvkm_notअगरy_put(काष्ठा nvkm_notअगरy *notअगरy)
अणु
	काष्ठा nvkm_event *event = notअगरy->event;
	अचिन्हित दीर्घ flags;
	अगर (likely(event) &&
	    test_and_clear_bit(NVKM_NOTIFY_USER, &notअगरy->flags)) अणु
		spin_lock_irqsave(&event->refs_lock, flags);
		nvkm_notअगरy_put_locked(notअगरy);
		spin_unlock_irqrestore(&event->refs_lock, flags);
		अगर (test_bit(NVKM_NOTIFY_WORK, &notअगरy->flags))
			flush_work(&notअगरy->work);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
nvkm_notअगरy_get_locked(काष्ठा nvkm_notअगरy *notअगरy)
अणु
	अगर (--notअगरy->block == 0)
		nvkm_event_get(notअगरy->event, notअगरy->types, notअगरy->index);
पूर्ण

व्योम
nvkm_notअगरy_get(काष्ठा nvkm_notअगरy *notअगरy)
अणु
	काष्ठा nvkm_event *event = notअगरy->event;
	अचिन्हित दीर्घ flags;
	अगर (likely(event) &&
	    !test_and_set_bit(NVKM_NOTIFY_USER, &notअगरy->flags)) अणु
		spin_lock_irqsave(&event->refs_lock, flags);
		nvkm_notअगरy_get_locked(notअगरy);
		spin_unlock_irqrestore(&event->refs_lock, flags);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
nvkm_notअगरy_func(काष्ठा nvkm_notअगरy *notअगरy)
अणु
	काष्ठा nvkm_event *event = notअगरy->event;
	पूर्णांक ret = notअगरy->func(notअगरy);
	अचिन्हित दीर्घ flags;
	अगर ((ret == NVKM_NOTIFY_KEEP) ||
	    !test_and_clear_bit(NVKM_NOTIFY_USER, &notअगरy->flags)) अणु
		spin_lock_irqsave(&event->refs_lock, flags);
		nvkm_notअगरy_get_locked(notअगरy);
		spin_unlock_irqrestore(&event->refs_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम
nvkm_notअगरy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvkm_notअगरy *notअगरy = container_of(work, typeof(*notअगरy), work);
	nvkm_notअगरy_func(notअगरy);
पूर्ण

व्योम
nvkm_notअगरy_send(काष्ठा nvkm_notअगरy *notअगरy, व्योम *data, u32 size)
अणु
	काष्ठा nvkm_event *event = notअगरy->event;
	अचिन्हित दीर्घ flags;

	निश्चित_spin_locked(&event->list_lock);
	BUG_ON(size != notअगरy->size);

	spin_lock_irqsave(&event->refs_lock, flags);
	अगर (notअगरy->block) अणु
		spin_unlock_irqrestore(&event->refs_lock, flags);
		वापस;
	पूर्ण
	nvkm_notअगरy_put_locked(notअगरy);
	spin_unlock_irqrestore(&event->refs_lock, flags);

	अगर (test_bit(NVKM_NOTIFY_WORK, &notअगरy->flags)) अणु
		स_नकल((व्योम *)notअगरy->data, data, size);
		schedule_work(&notअगरy->work);
	पूर्ण अन्यथा अणु
		notअगरy->data = data;
		nvkm_notअगरy_func(notअगरy);
		notअगरy->data = शून्य;
	पूर्ण
पूर्ण

व्योम
nvkm_notअगरy_fini(काष्ठा nvkm_notअगरy *notअगरy)
अणु
	अचिन्हित दीर्घ flags;
	अगर (notअगरy->event) अणु
		nvkm_notअगरy_put(notअगरy);
		spin_lock_irqsave(&notअगरy->event->list_lock, flags);
		list_del(&notअगरy->head);
		spin_unlock_irqrestore(&notअगरy->event->list_lock, flags);
		kमुक्त((व्योम *)notअगरy->data);
		notअगरy->event = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nvkm_notअगरy_init(काष्ठा nvkm_object *object, काष्ठा nvkm_event *event,
		 पूर्णांक (*func)(काष्ठा nvkm_notअगरy *), bool work,
		 व्योम *data, u32 size, u32 reply,
		 काष्ठा nvkm_notअगरy *notअगरy)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -ENODEV;
	अगर ((notअगरy->event = event), event->refs) अणु
		ret = event->func->ctor(object, data, size, notअगरy);
		अगर (ret == 0 && (ret = -EINVAL, notअगरy->size == reply)) अणु
			notअगरy->flags = 0;
			notअगरy->block = 1;
			notअगरy->func = func;
			notअगरy->data = शून्य;
			अगर (ret = 0, work) अणु
				INIT_WORK(&notअगरy->work, nvkm_notअगरy_work);
				set_bit(NVKM_NOTIFY_WORK, &notअगरy->flags);
				notअगरy->data = kदो_स्मृति(reply, GFP_KERNEL);
				अगर (!notअगरy->data)
					ret = -ENOMEM;
			पूर्ण
		पूर्ण
		अगर (ret == 0) अणु
			spin_lock_irqsave(&event->list_lock, flags);
			list_add_tail(&notअगरy->head, &event->list);
			spin_unlock_irqrestore(&event->list_lock, flags);
		पूर्ण
	पूर्ण
	अगर (ret)
		notअगरy->event = शून्य;
	वापस ret;
पूर्ण
