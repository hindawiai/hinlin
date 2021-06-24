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
#समावेश "channv50.h"

#समावेश <core/client.h>
#समावेश <core/ramht.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl826f.h>
#समावेश <nvअगर/unpack.h>

अटल पूर्णांक
g84_fअगरo_gpfअगरo_new(काष्ठा nvkm_fअगरo *base, स्थिर काष्ठा nvkm_oclass *oclass,
		    व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_object *parent = oclass->parent;
	जोड़ अणु
		काष्ठा g82_channel_gpfअगरo_v0 v0;
	पूर्ण *args = data;
	काष्ठा nv50_fअगरo *fअगरo = nv50_fअगरo(base);
	काष्ठा nv50_fअगरo_chan *chan;
	u64 ioffset, ilength;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(parent, "create channel gpfifo size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(parent, "create channel gpfifo vers %d vmm %llx "
				   "pushbuf %llx ioffset %016llx "
				   "ilength %08x\n",
			   args->v0.version, args->v0.vmm, args->v0.pushbuf,
			   args->v0.ioffset, args->v0.ilength);
		अगर (!args->v0.pushbuf)
			वापस -EINVAL;
	पूर्ण अन्यथा
		वापस ret;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	*pobject = &chan->base.object;

	ret = g84_fअगरo_chan_ctor(fअगरo, args->v0.vmm, args->v0.pushbuf,
				 oclass, chan);
	अगर (ret)
		वापस ret;

	args->v0.chid = chan->base.chid;
	ioffset = args->v0.ioffset;
	ilength = order_base_2(args->v0.ilength / 8);

	nvkm_kmap(chan->ramfc);
	nvkm_wo32(chan->ramfc, 0x3c, 0x403f6078);
	nvkm_wo32(chan->ramfc, 0x44, 0x01003fff);
	nvkm_wo32(chan->ramfc, 0x48, chan->base.push->node->offset >> 4);
	nvkm_wo32(chan->ramfc, 0x50, lower_32_bits(ioffset));
	nvkm_wo32(chan->ramfc, 0x54, upper_32_bits(ioffset) | (ilength << 16));
	nvkm_wo32(chan->ramfc, 0x60, 0x7fffffff);
	nvkm_wo32(chan->ramfc, 0x78, 0x00000000);
	nvkm_wo32(chan->ramfc, 0x7c, 0x30000001);
	nvkm_wo32(chan->ramfc, 0x80, ((chan->ramht->bits - 9) << 27) |
				     (4 << 24) /* SEARCH_FULL */ |
				     (chan->ramht->gpuobj->node->offset >> 4));
	nvkm_wo32(chan->ramfc, 0x88, chan->cache->addr >> 10);
	nvkm_wo32(chan->ramfc, 0x98, chan->base.inst->addr >> 12);
	nvkm_करोne(chan->ramfc);
	वापस 0;
पूर्ण

स्थिर काष्ठा nvkm_fअगरo_chan_oclass
g84_fअगरo_gpfअगरo_oclass = अणु
	.base.oclass = G82_CHANNEL_GPFIFO,
	.base.minver = 0,
	.base.maxver = 0,
	.ctor = g84_fअगरo_gpfअगरo_new,
पूर्ण;
