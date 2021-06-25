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
#घोषणा nv04_sw_chan(p) container_of((p), काष्ठा nv04_sw_chan, base)
#समावेश "priv.h"
#समावेश "chan.h"
#समावेश "nvsw.h"

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/अगर0004.h>
#समावेश <nvअगर/ioctl.h>
#समावेश <nvअगर/unpack.h>

काष्ठा nv04_sw_chan अणु
	काष्ठा nvkm_sw_chan base;
	atomic_t ref;
पूर्ण;

/*******************************************************************************
 * software object classes
 ******************************************************************************/

अटल पूर्णांक
nv04_nvsw_mthd_get_ref(काष्ठा nvkm_nvsw *nvsw, व्योम *data, u32 size)
अणु
	काष्ठा nv04_sw_chan *chan = nv04_sw_chan(nvsw->chan);
	जोड़ अणु
		काष्ठा nv04_nvsw_get_ref_v0 v0;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		args->v0.ref = atomic_पढ़ो(&chan->ref);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
nv04_nvsw_mthd(काष्ठा nvkm_nvsw *nvsw, u32 mthd, व्योम *data, u32 size)
अणु
	चयन (mthd) अणु
	हाल NV04_NVSW_GET_REF:
		वापस nv04_nvsw_mthd_get_ref(nvsw, data, size);
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा nvkm_nvsw_func
nv04_nvsw = अणु
	.mthd = nv04_nvsw_mthd,
पूर्ण;

अटल पूर्णांक
nv04_nvsw_new(काष्ठा nvkm_sw_chan *chan, स्थिर काष्ठा nvkm_oclass *oclass,
	      व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	वापस nvkm_nvsw_new_(&nv04_nvsw, chan, oclass, data, size, pobject);
पूर्ण

/*******************************************************************************
 * software context
 ******************************************************************************/

अटल bool
nv04_sw_chan_mthd(काष्ठा nvkm_sw_chan *base, पूर्णांक subc, u32 mthd, u32 data)
अणु
	काष्ठा nv04_sw_chan *chan = nv04_sw_chan(base);

	चयन (mthd) अणु
	हाल 0x0150:
		atomic_set(&chan->ref, data);
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा nvkm_sw_chan_func
nv04_sw_chan = अणु
	.mthd = nv04_sw_chan_mthd,
पूर्ण;

अटल पूर्णांक
nv04_sw_chan_new(काष्ठा nvkm_sw *sw, काष्ठा nvkm_fअगरo_chan *fअगरo,
		 स्थिर काष्ठा nvkm_oclass *oclass, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nv04_sw_chan *chan;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	atomic_set(&chan->ref, 0);
	*pobject = &chan->base.object;

	वापस nvkm_sw_chan_ctor(&nv04_sw_chan, sw, fअगरo, oclass, &chan->base);
पूर्ण

/*******************************************************************************
 * software engine/subdev functions
 ******************************************************************************/

अटल स्थिर काष्ठा nvkm_sw_func
nv04_sw = अणु
	.chan_new = nv04_sw_chan_new,
	.sclass = अणु
		अणु nv04_nvsw_new, अणु -1, -1, NVIF_CLASS_SW_NV04 पूर्ण पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv04_sw_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_sw **psw)
अणु
	वापस nvkm_sw_new_(&nv04_sw, device, type, inst, psw);
पूर्ण
