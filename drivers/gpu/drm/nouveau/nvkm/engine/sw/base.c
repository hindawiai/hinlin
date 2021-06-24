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
#समावेश "priv.h"
#समावेश "chan.h"

#समावेश <engine/fअगरo.h>

bool
nvkm_sw_mthd(काष्ठा nvkm_sw *sw, पूर्णांक chid, पूर्णांक subc, u32 mthd, u32 data)
अणु
	काष्ठा nvkm_sw_chan *chan;
	bool handled = false;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sw->engine.lock, flags);
	list_क्रम_each_entry(chan, &sw->chan, head) अणु
		अगर (chan->fअगरo->chid == chid) अणु
			handled = nvkm_sw_chan_mthd(chan, subc, mthd, data);
			list_del(&chan->head);
			list_add(&chan->head, &sw->chan);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&sw->engine.lock, flags);
	वापस handled;
पूर्ण

अटल पूर्णांक
nvkm_sw_oclass_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *data, u32 size,
		   काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_sw_chan *chan = nvkm_sw_chan(oclass->parent);
	स्थिर काष्ठा nvkm_sw_chan_sclass *sclass = oclass->engn;
	वापस sclass->ctor(chan, oclass, data, size, pobject);
पूर्ण

अटल पूर्णांक
nvkm_sw_oclass_get(काष्ठा nvkm_oclass *oclass, पूर्णांक index)
अणु
	काष्ठा nvkm_sw *sw = nvkm_sw(oclass->engine);
	पूर्णांक c = 0;

	जबतक (sw->func->sclass[c].ctor) अणु
		अगर (c++ == index) अणु
			oclass->engn = &sw->func->sclass[index];
			oclass->base =  sw->func->sclass[index].base;
			oclass->base.ctor = nvkm_sw_oclass_new;
			वापस index;
		पूर्ण
	पूर्ण

	वापस c;
पूर्ण

अटल पूर्णांक
nvkm_sw_cclass_get(काष्ठा nvkm_fअगरo_chan *fअगरoch,
		   स्थिर काष्ठा nvkm_oclass *oclass,
		   काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_sw *sw = nvkm_sw(oclass->engine);
	वापस sw->func->chan_new(sw, fअगरoch, oclass, pobject);
पूर्ण

अटल व्योम *
nvkm_sw_dtor(काष्ठा nvkm_engine *engine)
अणु
	वापस nvkm_sw(engine);
पूर्ण

अटल स्थिर काष्ठा nvkm_engine_func
nvkm_sw = अणु
	.dtor = nvkm_sw_dtor,
	.fअगरo.cclass = nvkm_sw_cclass_get,
	.fअगरo.sclass = nvkm_sw_oclass_get,
पूर्ण;

पूर्णांक
nvkm_sw_new_(स्थिर काष्ठा nvkm_sw_func *func, काष्ठा nvkm_device *device,
	     क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_sw **psw)
अणु
	काष्ठा nvkm_sw *sw;

	अगर (!(sw = *psw = kzalloc(माप(*sw), GFP_KERNEL)))
		वापस -ENOMEM;
	INIT_LIST_HEAD(&sw->chan);
	sw->func = func;

	वापस nvkm_engine_ctor(&nvkm_sw, device, type, inst, true, &sw->engine);
पूर्ण
