<शैली गुरु>
/*
 * Copyright 2013-2014 Red Hat Inc.
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
#समावेश <core/event.h>
#समावेश <core/notअगरy.h>

व्योम
nvkm_event_put(काष्ठा nvkm_event *event, u32 types, पूर्णांक index)
अणु
	निश्चित_spin_locked(&event->refs_lock);
	जबतक (types) अणु
		पूर्णांक type = __ffs(types); types &= ~(1 << type);
		अगर (--event->refs[index * event->types_nr + type] == 0) अणु
			अगर (event->func->fini)
				event->func->fini(event, 1 << type, index);
		पूर्ण
	पूर्ण
पूर्ण

व्योम
nvkm_event_get(काष्ठा nvkm_event *event, u32 types, पूर्णांक index)
अणु
	निश्चित_spin_locked(&event->refs_lock);
	जबतक (types) अणु
		पूर्णांक type = __ffs(types); types &= ~(1 << type);
		अगर (++event->refs[index * event->types_nr + type] == 1) अणु
			अगर (event->func->init)
				event->func->init(event, 1 << type, index);
		पूर्ण
	पूर्ण
पूर्ण

व्योम
nvkm_event_send(काष्ठा nvkm_event *event, u32 types, पूर्णांक index,
		व्योम *data, u32 size)
अणु
	काष्ठा nvkm_notअगरy *notअगरy;
	अचिन्हित दीर्घ flags;

	अगर (!event->refs || WARN_ON(index >= event->index_nr))
		वापस;

	spin_lock_irqsave(&event->list_lock, flags);
	list_क्रम_each_entry(notअगरy, &event->list, head) अणु
		अगर (notअगरy->index == index && (notअगरy->types & types)) अणु
			अगर (event->func->send) अणु
				event->func->send(data, size, notअगरy);
				जारी;
			पूर्ण
			nvkm_notअगरy_send(notअगरy, data, size);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&event->list_lock, flags);
पूर्ण

व्योम
nvkm_event_fini(काष्ठा nvkm_event *event)
अणु
	अगर (event->refs) अणु
		kमुक्त(event->refs);
		event->refs = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nvkm_event_init(स्थिर काष्ठा nvkm_event_func *func, पूर्णांक types_nr, पूर्णांक index_nr,
		काष्ठा nvkm_event *event)
अणु
	event->refs = kzalloc(array3_size(index_nr, types_nr,
					  माप(*event->refs)),
			      GFP_KERNEL);
	अगर (!event->refs)
		वापस -ENOMEM;

	event->func = func;
	event->types_nr = types_nr;
	event->index_nr = index_nr;
	spin_lock_init(&event->refs_lock);
	spin_lock_init(&event->list_lock);
	INIT_LIST_HEAD(&event->list);
	वापस 0;
पूर्ण
