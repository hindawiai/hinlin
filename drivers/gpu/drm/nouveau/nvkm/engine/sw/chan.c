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
#समावेश "chan.h"

#समावेश <core/notअगरy.h>
#समावेश <engine/fअगरo.h>

#समावेश <nvअगर/event.h>
#समावेश <nvअगर/unpack.h>

bool
nvkm_sw_chan_mthd(काष्ठा nvkm_sw_chan *chan, पूर्णांक subc, u32 mthd, u32 data)
अणु
	चयन (mthd) अणु
	हाल 0x0000:
		वापस true;
	हाल 0x0500:
		nvkm_event_send(&chan->event, 1, 0, शून्य, 0);
		वापस true;
	शेष:
		अगर (chan->func->mthd)
			वापस chan->func->mthd(chan, subc, mthd, data);
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक
nvkm_sw_chan_event_ctor(काष्ठा nvkm_object *object, व्योम *data, u32 size,
			काष्ठा nvkm_notअगरy *notअगरy)
अणु
	जोड़ अणु
		काष्ठा nvअगर_notअगरy_uevent_req none;
	पूर्ण *req = data;
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unvers(ret, &data, &size, req->none))) अणु
		notअगरy->size  = माप(काष्ठा nvअगर_notअगरy_uevent_rep);
		notअगरy->types = 1;
		notअगरy->index = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_event_func
nvkm_sw_chan_event = अणु
	.ctor = nvkm_sw_chan_event_ctor,
पूर्ण;

अटल व्योम *
nvkm_sw_chan_dtor(काष्ठा nvkm_object *object)
अणु
	काष्ठा nvkm_sw_chan *chan = nvkm_sw_chan(object);
	काष्ठा nvkm_sw *sw = chan->sw;
	अचिन्हित दीर्घ flags;
	व्योम *data = chan;

	अगर (chan->func->dtor)
		data = chan->func->dtor(chan);
	nvkm_event_fini(&chan->event);

	spin_lock_irqsave(&sw->engine.lock, flags);
	list_del(&chan->head);
	spin_unlock_irqrestore(&sw->engine.lock, flags);
	वापस data;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nvkm_sw_chan = अणु
	.dtor = nvkm_sw_chan_dtor,
पूर्ण;

पूर्णांक
nvkm_sw_chan_ctor(स्थिर काष्ठा nvkm_sw_chan_func *func, काष्ठा nvkm_sw *sw,
		  काष्ठा nvkm_fअगरo_chan *fअगरo, स्थिर काष्ठा nvkm_oclass *oclass,
		  काष्ठा nvkm_sw_chan *chan)
अणु
	अचिन्हित दीर्घ flags;

	nvkm_object_ctor(&nvkm_sw_chan, oclass, &chan->object);
	chan->func = func;
	chan->sw = sw;
	chan->fअगरo = fअगरo;
	spin_lock_irqsave(&sw->engine.lock, flags);
	list_add(&chan->head, &sw->chan);
	spin_unlock_irqrestore(&sw->engine.lock, flags);

	वापस nvkm_event_init(&nvkm_sw_chan_event, 1, 1, &chan->event);
पूर्ण
