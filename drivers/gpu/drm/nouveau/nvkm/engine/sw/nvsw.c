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
#समावेश "nvsw.h"
#समावेश "chan.h"

#समावेश <nvअगर/अगर0004.h>

अटल पूर्णांक
nvkm_nvsw_mthd_(काष्ठा nvkm_object *object, u32 mthd, व्योम *data, u32 size)
अणु
	काष्ठा nvkm_nvsw *nvsw = nvkm_nvsw(object);
	अगर (nvsw->func->mthd)
		वापस nvsw->func->mthd(nvsw, mthd, data, size);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक
nvkm_nvsw_ntfy_(काष्ठा nvkm_object *object, u32 mthd,
		काष्ठा nvkm_event **pevent)
अणु
	काष्ठा nvkm_nvsw *nvsw = nvkm_nvsw(object);
	चयन (mthd) अणु
	हाल NV04_NVSW_NTFY_UEVENT:
		*pevent = &nvsw->chan->event;
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nvkm_nvsw_ = अणु
	.mthd = nvkm_nvsw_mthd_,
	.ntfy = nvkm_nvsw_ntfy_,
पूर्ण;

पूर्णांक
nvkm_nvsw_new_(स्थिर काष्ठा nvkm_nvsw_func *func, काष्ठा nvkm_sw_chan *chan,
	       स्थिर काष्ठा nvkm_oclass *oclass, व्योम *data, u32 size,
	       काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_nvsw *nvsw;

	अगर (!(nvsw = kzalloc(माप(*nvsw), GFP_KERNEL)))
		वापस -ENOMEM;
	*pobject = &nvsw->object;

	nvkm_object_ctor(&nvkm_nvsw_, oclass, &nvsw->object);
	nvsw->func = func;
	nvsw->chan = chan;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_nvsw_func
nvkm_nvsw = अणु
पूर्ण;

पूर्णांक
nvkm_nvsw_new(काष्ठा nvkm_sw_chan *chan, स्थिर काष्ठा nvkm_oclass *oclass,
	      व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	वापस nvkm_nvsw_new_(&nvkm_nvsw, chan, oclass, data, size, pobject);
पूर्ण
