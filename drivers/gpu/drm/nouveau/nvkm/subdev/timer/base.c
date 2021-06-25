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
#समावेश "priv.h"

s64
nvkm_समयr_रुको_test(काष्ठा nvkm_समयr_रुको *रुको)
अणु
	काष्ठा nvkm_subdev *subdev = &रुको->पंचांगr->subdev;
	u64 समय = nvkm_समयr_पढ़ो(रुको->पंचांगr);

	अगर (रुको->पढ़ोs == 0) अणु
		रुको->समय0 = समय;
		रुको->समय1 = समय;
	पूर्ण

	अगर (रुको->समय1 == समय) अणु
		अगर (रुको->पढ़ोs++ == 16) अणु
			nvkm_fatal(subdev, "stalled at %016llx\n", समय);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण अन्यथा अणु
		रुको->समय1 = समय;
		रुको->पढ़ोs = 1;
	पूर्ण

	अगर (रुको->समय1 - रुको->समय0 > रुको->limit)
		वापस -ETIMEDOUT;

	वापस रुको->समय1 - रुको->समय0;
पूर्ण

व्योम
nvkm_समयr_रुको_init(काष्ठा nvkm_device *device, u64 nsec,
		     काष्ठा nvkm_समयr_रुको *रुको)
अणु
	रुको->पंचांगr = device->समयr;
	रुको->limit = nsec;
	रुको->पढ़ोs = 0;
पूर्ण

u64
nvkm_समयr_पढ़ो(काष्ठा nvkm_समयr *पंचांगr)
अणु
	वापस पंचांगr->func->पढ़ो(पंचांगr);
पूर्ण

व्योम
nvkm_समयr_alarm_trigger(काष्ठा nvkm_समयr *पंचांगr)
अणु
	काष्ठा nvkm_alarm *alarm, *atemp;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(exec);

	/* Process pending alarms. */
	spin_lock_irqsave(&पंचांगr->lock, flags);
	list_क्रम_each_entry_safe(alarm, atemp, &पंचांगr->alarms, head) अणु
		/* Have we hit the earliest alarm that hasn't gone off? */
		अगर (alarm->बारtamp > nvkm_समयr_पढ़ो(पंचांगr)) अणु
			/* Schedule it.  If we didn't race, we're करोne. */
			पंचांगr->func->alarm_init(पंचांगr, alarm->बारtamp);
			अगर (alarm->बारtamp > nvkm_समयr_पढ़ो(पंचांगr))
				अवरोध;
		पूर्ण

		/* Move to completed list.  We'll drop the lock beक्रमe
		 * executing the callback so it can reschedule itself.
		 */
		list_del_init(&alarm->head);
		list_add(&alarm->exec, &exec);
	पूर्ण

	/* Shut करोwn पूर्णांकerrupt अगर no more pending alarms. */
	अगर (list_empty(&पंचांगr->alarms))
		पंचांगr->func->alarm_fini(पंचांगr);
	spin_unlock_irqrestore(&पंचांगr->lock, flags);

	/* Execute completed callbacks. */
	list_क्रम_each_entry_safe(alarm, atemp, &exec, exec) अणु
		list_del(&alarm->exec);
		alarm->func(alarm);
	पूर्ण
पूर्ण

व्योम
nvkm_समयr_alarm(काष्ठा nvkm_समयr *पंचांगr, u32 nsec, काष्ठा nvkm_alarm *alarm)
अणु
	काष्ठा nvkm_alarm *list;
	अचिन्हित दीर्घ flags;

	/* Remove alarm from pending list.
	 *
	 * This both protects against the corruption of the list,
	 * and implements alarm rescheduling/cancellation.
	 */
	spin_lock_irqsave(&पंचांगr->lock, flags);
	list_del_init(&alarm->head);

	अगर (nsec) अणु
		/* Insert पूर्णांकo pending list, ordered earliest to latest. */
		alarm->बारtamp = nvkm_समयr_पढ़ो(पंचांगr) + nsec;
		list_क्रम_each_entry(list, &पंचांगr->alarms, head) अणु
			अगर (list->बारtamp > alarm->बारtamp)
				अवरोध;
		पूर्ण

		list_add_tail(&alarm->head, &list->head);

		/* Update HW अगर this is now the earliest alarm. */
		list = list_first_entry(&पंचांगr->alarms, typeof(*list), head);
		अगर (list == alarm) अणु
			पंचांगr->func->alarm_init(पंचांगr, alarm->बारtamp);
			/* This shouldn't happen if callers aren't stupid.
			 *
			 * Worst हाल scenario is that it'll take roughly
			 * 4 seconds क्रम the next alarm to trigger.
			 */
			WARN_ON(alarm->बारtamp <= nvkm_समयr_पढ़ो(पंचांगr));
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&पंचांगr->lock, flags);
पूर्ण

अटल व्योम
nvkm_समयr_पूर्णांकr(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_समयr *पंचांगr = nvkm_समयr(subdev);
	पंचांगr->func->पूर्णांकr(पंचांगr);
पूर्ण

अटल पूर्णांक
nvkm_समयr_fini(काष्ठा nvkm_subdev *subdev, bool suspend)
अणु
	काष्ठा nvkm_समयr *पंचांगr = nvkm_समयr(subdev);
	पंचांगr->func->alarm_fini(पंचांगr);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_समयr_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_समयr *पंचांगr = nvkm_समयr(subdev);
	अगर (पंचांगr->func->init)
		पंचांगr->func->init(पंचांगr);
	पंचांगr->func->समय(पंचांगr, kसमय_प्रकारo_ns(kसमय_get()));
	nvkm_समयr_alarm_trigger(पंचांगr);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_समयr_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	वापस nvkm_समयr(subdev);
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_समयr = अणु
	.dtor = nvkm_समयr_dtor,
	.init = nvkm_समयr_init,
	.fini = nvkm_समयr_fini,
	.पूर्णांकr = nvkm_समयr_पूर्णांकr,
पूर्ण;

पूर्णांक
nvkm_समयr_new_(स्थिर काष्ठा nvkm_समयr_func *func, काष्ठा nvkm_device *device,
		क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_समयr **pपंचांगr)
अणु
	काष्ठा nvkm_समयr *पंचांगr;

	अगर (!(पंचांगr = *pपंचांगr = kzalloc(माप(*पंचांगr), GFP_KERNEL)))
		वापस -ENOMEM;

	nvkm_subdev_ctor(&nvkm_समयr, device, type, inst, &पंचांगr->subdev);
	पंचांगr->func = func;
	INIT_LIST_HEAD(&पंचांगr->alarms);
	spin_lock_init(&पंचांगr->lock);
	वापस 0;
पूर्ण
