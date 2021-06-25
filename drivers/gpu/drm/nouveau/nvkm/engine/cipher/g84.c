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
#समावेश <engine/cipher.h>
#समावेश <engine/fअगरo.h>

#समावेश <core/client.h>
#समावेश <core/क्रमागत.h>
#समावेश <core/gpuobj.h>

#समावेश <nvअगर/class.h>

अटल पूर्णांक
g84_cipher_oclass_bind(काष्ठा nvkm_object *object, काष्ठा nvkm_gpuobj *parent,
		       पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	पूर्णांक ret = nvkm_gpuobj_new(object->engine->subdev.device, 16,
				  align, false, parent, pgpuobj);
	अगर (ret == 0) अणु
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, object->oclass);
		nvkm_wo32(*pgpuobj, 0x04, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x08, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x0c, 0x00000000);
		nvkm_करोne(*pgpuobj);
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
g84_cipher_oclass_func = अणु
	.bind = g84_cipher_oclass_bind,
पूर्ण;

अटल पूर्णांक
g84_cipher_cclass_bind(काष्ठा nvkm_object *object, काष्ठा nvkm_gpuobj *parent,
		       पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	वापस nvkm_gpuobj_new(object->engine->subdev.device, 256,
			       align, true, parent, pgpuobj);

पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
g84_cipher_cclass = अणु
	.bind = g84_cipher_cclass_bind,
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield
g84_cipher_पूर्णांकr_mask[] = अणु
	अणु 0x00000001, "INVALID_STATE" पूर्ण,
	अणु 0x00000002, "ILLEGAL_MTHD" पूर्ण,
	अणु 0x00000004, "ILLEGAL_CLASS" पूर्ण,
	अणु 0x00000080, "QUERY" पूर्ण,
	अणु 0x00000100, "FAULT" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
g84_cipher_पूर्णांकr(काष्ठा nvkm_engine *cipher)
अणु
	काष्ठा nvkm_subdev *subdev = &cipher->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_fअगरo *fअगरo = device->fअगरo;
	काष्ठा nvkm_fअगरo_chan *chan;
	u32 stat = nvkm_rd32(device, 0x102130);
	u32 mthd = nvkm_rd32(device, 0x102190);
	u32 data = nvkm_rd32(device, 0x102194);
	u32 inst = nvkm_rd32(device, 0x102188) & 0x7fffffff;
	अचिन्हित दीर्घ flags;
	अक्षर msg[128];

	chan = nvkm_fअगरo_chan_inst(fअगरo, (u64)inst << 12, &flags);
	अगर (stat) अणु
		nvkm_snprपूर्णांकbf(msg, माप(msg), g84_cipher_पूर्णांकr_mask, stat);
		nvkm_error(subdev,  "%08x [%s] ch %d [%010llx %s] "
				    "mthd %04x data %08x\n", stat, msg,
			   chan ? chan->chid : -1, (u64)inst << 12,
			   chan ? chan->object.client->name : "unknown",
			   mthd, data);
	पूर्ण
	nvkm_fअगरo_chan_put(fअगरo, flags, &chan);

	nvkm_wr32(device, 0x102130, stat);
	nvkm_wr32(device, 0x10200c, 0x10);
पूर्ण

अटल पूर्णांक
g84_cipher_init(काष्ठा nvkm_engine *cipher)
अणु
	काष्ठा nvkm_device *device = cipher->subdev.device;
	nvkm_wr32(device, 0x102130, 0xffffffff);
	nvkm_wr32(device, 0x102140, 0xffffffbf);
	nvkm_wr32(device, 0x10200c, 0x00000010);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_engine_func
g84_cipher = अणु
	.init = g84_cipher_init,
	.पूर्णांकr = g84_cipher_पूर्णांकr,
	.cclass = &g84_cipher_cclass,
	.sclass = अणु
		अणु -1, -1, NV74_CIPHER, &g84_cipher_oclass_func पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
g84_cipher_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_engine **pengine)
अणु
	वापस nvkm_engine_new_(&g84_cipher, device, type, inst, true, pengine);
पूर्ण
