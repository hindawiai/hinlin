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

#समावेश <engine/fअगरo.h>

u32
nvkm_gr_ctxsw_inst(काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_gr *gr = device->gr;
	अगर (gr && gr->func->ctxsw.inst)
		वापस gr->func->ctxsw.inst(gr);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_gr_ctxsw_resume(काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_gr *gr = device->gr;
	अगर (gr && gr->func->ctxsw.resume)
		वापस gr->func->ctxsw.resume(gr);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_gr_ctxsw_छोड़ो(काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_gr *gr = device->gr;
	अगर (gr && gr->func->ctxsw.छोड़ो)
		वापस gr->func->ctxsw.छोड़ो(gr);
	वापस 0;
पूर्ण

अटल bool
nvkm_gr_chsw_load(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_gr *gr = nvkm_gr(engine);
	अगर (gr->func->chsw_load)
		वापस gr->func->chsw_load(gr);
	वापस false;
पूर्ण

अटल व्योम
nvkm_gr_tile(काष्ठा nvkm_engine *engine, पूर्णांक region, काष्ठा nvkm_fb_tile *tile)
अणु
	काष्ठा nvkm_gr *gr = nvkm_gr(engine);
	अगर (gr->func->tile)
		gr->func->tile(gr, region, tile);
पूर्ण

u64
nvkm_gr_units(काष्ठा nvkm_gr *gr)
अणु
	अगर (gr->func->units)
		वापस gr->func->units(gr);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_gr_tlb_flush(काष्ठा nvkm_gr *gr)
अणु
	अगर (gr->func->tlb_flush)
		वापस gr->func->tlb_flush(gr);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक
nvkm_gr_oclass_get(काष्ठा nvkm_oclass *oclass, पूर्णांक index)
अणु
	काष्ठा nvkm_gr *gr = nvkm_gr(oclass->engine);
	पूर्णांक c = 0;

	अगर (gr->func->object_get) अणु
		पूर्णांक ret = gr->func->object_get(gr, index, &oclass->base);
		अगर (oclass->base.oclass)
			वापस index;
		वापस ret;
	पूर्ण

	जबतक (gr->func->sclass[c].oclass) अणु
		अगर (c++ == index) अणु
			oclass->base = gr->func->sclass[index];
			वापस index;
		पूर्ण
	पूर्ण

	वापस c;
पूर्ण

अटल पूर्णांक
nvkm_gr_cclass_new(काष्ठा nvkm_fअगरo_chan *chan,
		   स्थिर काष्ठा nvkm_oclass *oclass,
		   काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_gr *gr = nvkm_gr(oclass->engine);
	अगर (gr->func->chan_new)
		वापस gr->func->chan_new(gr, chan, oclass, pobject);
	वापस 0;
पूर्ण

अटल व्योम
nvkm_gr_पूर्णांकr(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_gr *gr = nvkm_gr(engine);
	gr->func->पूर्णांकr(gr);
पूर्ण

अटल पूर्णांक
nvkm_gr_oneinit(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_gr *gr = nvkm_gr(engine);
	अगर (gr->func->oneinit)
		वापस gr->func->oneinit(gr);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_gr_init(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_gr *gr = nvkm_gr(engine);
	वापस gr->func->init(gr);
पूर्ण

अटल पूर्णांक
nvkm_gr_fini(काष्ठा nvkm_engine *engine, bool suspend)
अणु
	काष्ठा nvkm_gr *gr = nvkm_gr(engine);
	अगर (gr->func->fini)
		वापस gr->func->fini(gr, suspend);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_gr_dtor(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_gr *gr = nvkm_gr(engine);
	अगर (gr->func->dtor)
		वापस gr->func->dtor(gr);
	वापस gr;
पूर्ण

अटल स्थिर काष्ठा nvkm_engine_func
nvkm_gr = अणु
	.dtor = nvkm_gr_dtor,
	.oneinit = nvkm_gr_oneinit,
	.init = nvkm_gr_init,
	.fini = nvkm_gr_fini,
	.पूर्णांकr = nvkm_gr_पूर्णांकr,
	.tile = nvkm_gr_tile,
	.chsw_load = nvkm_gr_chsw_load,
	.fअगरo.cclass = nvkm_gr_cclass_new,
	.fअगरo.sclass = nvkm_gr_oclass_get,
पूर्ण;

पूर्णांक
nvkm_gr_ctor(स्थिर काष्ठा nvkm_gr_func *func, काष्ठा nvkm_device *device,
	     क्रमागत nvkm_subdev_type type, पूर्णांक inst, bool enable, काष्ठा nvkm_gr *gr)
अणु
	gr->func = func;
	वापस nvkm_engine_ctor(&nvkm_gr, device, type, inst, enable, &gr->engine);
पूर्ण
