<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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
#समावेश "changk104.h"
#समावेश "cgrp.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>

#समावेश <nvअगर/clc36f.h>
#समावेश <nvअगर/unpack.h>

अटल u32
tu102_fअगरo_gpfअगरo_submit_token(काष्ठा nvkm_fअगरo_chan *base)
अणु
	काष्ठा gk104_fअगरo_chan *chan = gk104_fअगरo_chan(base);
	वापस (chan->runl << 16) | chan->base.chid;
पूर्ण

अटल स्थिर काष्ठा nvkm_fअगरo_chan_func
tu102_fअगरo_gpfअगरo = अणु
	.dtor = gk104_fअगरo_gpfअगरo_dtor,
	.init = gk104_fअगरo_gpfअगरo_init,
	.fini = gk104_fअगरo_gpfअगरo_fini,
	.ntfy = gf100_fअगरo_chan_ntfy,
	.engine_ctor = gk104_fअगरo_gpfअगरo_engine_ctor,
	.engine_dtor = gk104_fअगरo_gpfअगरo_engine_dtor,
	.engine_init = gv100_fअगरo_gpfअगरo_engine_init,
	.engine_fini = gv100_fअगरo_gpfअगरo_engine_fini,
	.submit_token = tu102_fअगरo_gpfअगरo_submit_token,
पूर्ण;

पूर्णांक
tu102_fअगरo_gpfअगरo_new(काष्ठा gk104_fअगरo *fअगरo, स्थिर काष्ठा nvkm_oclass *oclass,
		      व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_object *parent = oclass->parent;
	जोड़ अणु
		काष्ठा volta_channel_gpfअगरo_a_v0 v0;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(parent, "create channel gpfifo size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(parent, "create channel gpfifo vers %d vmm %llx "
				   "ioffset %016llx ilength %08x "
				   "runlist %016llx priv %d\n",
			   args->v0.version, args->v0.vmm, args->v0.ioffset,
			   args->v0.ilength, args->v0.runlist, args->v0.priv);
		अगर (args->v0.priv && !oclass->client->super)
			वापस -EINVAL;
		वापस gv100_fअगरo_gpfअगरo_new_(&tu102_fअगरo_gpfअगरo, fअगरo,
					      &args->v0.runlist,
					      &args->v0.chid,
					       args->v0.vmm,
					       args->v0.ioffset,
					       args->v0.ilength,
					      &args->v0.inst,
					       args->v0.priv,
					      &args->v0.token,
					      oclass, pobject);
	पूर्ण

	वापस ret;
पूर्ण
