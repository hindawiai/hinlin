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
#समावेश "gf100.h"
#समावेश "ctxgf100.h"
#समावेश "fuc/os.h"

#समावेश <core/client.h>
#समावेश <core/firmware.h>
#समावेश <core/option.h>
#समावेश <subdev/acr.h>
#समावेश <subdev/fb.h>
#समावेश <subdev/mc.h>
#समावेश <subdev/pmu.h>
#समावेश <subdev/therm.h>
#समावेश <subdev/समयr.h>
#समावेश <engine/fअगरo.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl9097.h>
#समावेश <nvअगर/अगर900d.h>
#समावेश <nvअगर/unpack.h>

/*******************************************************************************
 * Zero Bandwidth Clear
 ******************************************************************************/

अटल व्योम
gf100_gr_zbc_clear_color(काष्ठा gf100_gr *gr, पूर्णांक zbc)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	अगर (gr->zbc_color[zbc].क्रमmat) अणु
		nvkm_wr32(device, 0x405804, gr->zbc_color[zbc].ds[0]);
		nvkm_wr32(device, 0x405808, gr->zbc_color[zbc].ds[1]);
		nvkm_wr32(device, 0x40580c, gr->zbc_color[zbc].ds[2]);
		nvkm_wr32(device, 0x405810, gr->zbc_color[zbc].ds[3]);
	पूर्ण
	nvkm_wr32(device, 0x405814, gr->zbc_color[zbc].क्रमmat);
	nvkm_wr32(device, 0x405820, zbc);
	nvkm_wr32(device, 0x405824, 0x00000004); /* TRIGGER | WRITE | COLOR */
पूर्ण

अटल पूर्णांक
gf100_gr_zbc_color_get(काष्ठा gf100_gr *gr, पूर्णांक क्रमmat,
		       स्थिर u32 ds[4], स्थिर u32 l2[4])
अणु
	काष्ठा nvkm_ltc *ltc = gr->base.engine.subdev.device->ltc;
	पूर्णांक zbc = -ENOSPC, i;

	क्रम (i = ltc->zbc_min; i <= ltc->zbc_max; i++) अणु
		अगर (gr->zbc_color[i].क्रमmat) अणु
			अगर (gr->zbc_color[i].क्रमmat != क्रमmat)
				जारी;
			अगर (स_भेद(gr->zbc_color[i].ds, ds, माप(
				   gr->zbc_color[i].ds)))
				जारी;
			अगर (स_भेद(gr->zbc_color[i].l2, l2, माप(
				   gr->zbc_color[i].l2))) अणु
				WARN_ON(1);
				वापस -EINVAL;
			पूर्ण
			वापस i;
		पूर्ण अन्यथा अणु
			zbc = (zbc < 0) ? i : zbc;
		पूर्ण
	पूर्ण

	अगर (zbc < 0)
		वापस zbc;

	स_नकल(gr->zbc_color[zbc].ds, ds, माप(gr->zbc_color[zbc].ds));
	स_नकल(gr->zbc_color[zbc].l2, l2, माप(gr->zbc_color[zbc].l2));
	gr->zbc_color[zbc].क्रमmat = क्रमmat;
	nvkm_ltc_zbc_color_get(ltc, zbc, l2);
	gr->func->zbc->clear_color(gr, zbc);
	वापस zbc;
पूर्ण

अटल व्योम
gf100_gr_zbc_clear_depth(काष्ठा gf100_gr *gr, पूर्णांक zbc)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	अगर (gr->zbc_depth[zbc].क्रमmat)
		nvkm_wr32(device, 0x405818, gr->zbc_depth[zbc].ds);
	nvkm_wr32(device, 0x40581c, gr->zbc_depth[zbc].क्रमmat);
	nvkm_wr32(device, 0x405820, zbc);
	nvkm_wr32(device, 0x405824, 0x00000005); /* TRIGGER | WRITE | DEPTH */
पूर्ण

अटल पूर्णांक
gf100_gr_zbc_depth_get(काष्ठा gf100_gr *gr, पूर्णांक क्रमmat,
		       स्थिर u32 ds, स्थिर u32 l2)
अणु
	काष्ठा nvkm_ltc *ltc = gr->base.engine.subdev.device->ltc;
	पूर्णांक zbc = -ENOSPC, i;

	क्रम (i = ltc->zbc_min; i <= ltc->zbc_max; i++) अणु
		अगर (gr->zbc_depth[i].क्रमmat) अणु
			अगर (gr->zbc_depth[i].क्रमmat != क्रमmat)
				जारी;
			अगर (gr->zbc_depth[i].ds != ds)
				जारी;
			अगर (gr->zbc_depth[i].l2 != l2) अणु
				WARN_ON(1);
				वापस -EINVAL;
			पूर्ण
			वापस i;
		पूर्ण अन्यथा अणु
			zbc = (zbc < 0) ? i : zbc;
		पूर्ण
	पूर्ण

	अगर (zbc < 0)
		वापस zbc;

	gr->zbc_depth[zbc].क्रमmat = क्रमmat;
	gr->zbc_depth[zbc].ds = ds;
	gr->zbc_depth[zbc].l2 = l2;
	nvkm_ltc_zbc_depth_get(ltc, zbc, l2);
	gr->func->zbc->clear_depth(gr, zbc);
	वापस zbc;
पूर्ण

स्थिर काष्ठा gf100_gr_func_zbc
gf100_gr_zbc = अणु
	.clear_color = gf100_gr_zbc_clear_color,
	.clear_depth = gf100_gr_zbc_clear_depth,
पूर्ण;

/*******************************************************************************
 * Graphics object classes
 ******************************************************************************/
#घोषणा gf100_gr_object(p) container_of((p), काष्ठा gf100_gr_object, object)

काष्ठा gf100_gr_object अणु
	काष्ठा nvkm_object object;
	काष्ठा gf100_gr_chan *chan;
पूर्ण;

अटल पूर्णांक
gf100_fermi_mthd_zbc_color(काष्ठा nvkm_object *object, व्योम *data, u32 size)
अणु
	काष्ठा gf100_gr *gr = gf100_gr(nvkm_gr(object->engine));
	जोड़ अणु
		काष्ठा fermi_a_zbc_color_v0 v0;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		चयन (args->v0.क्रमmat) अणु
		हाल FERMI_A_ZBC_COLOR_V0_FMT_ZERO:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_UNORM_ONE:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_RF32_GF32_BF32_AF32:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_R16_G16_B16_A16:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_RN16_GN16_BN16_AN16:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_RS16_GS16_BS16_AS16:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_RU16_GU16_BU16_AU16:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_RF16_GF16_BF16_AF16:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_A8R8G8B8:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_A8RL8GL8BL8:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_A2B10G10R10:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_AU2BU10GU10RU10:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_A8B8G8R8:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_A8BL8GL8RL8:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_AN8BN8GN8RN8:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_AS8BS8GS8RS8:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_AU8BU8GU8RU8:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_A2R10G10B10:
		हाल FERMI_A_ZBC_COLOR_V0_FMT_BF10GF11RF11:
			ret = gf100_gr_zbc_color_get(gr, args->v0.क्रमmat,
							   args->v0.ds,
							   args->v0.l2);
			अगर (ret >= 0) अणु
				args->v0.index = ret;
				वापस 0;
			पूर्ण
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
gf100_fermi_mthd_zbc_depth(काष्ठा nvkm_object *object, व्योम *data, u32 size)
अणु
	काष्ठा gf100_gr *gr = gf100_gr(nvkm_gr(object->engine));
	जोड़ अणु
		काष्ठा fermi_a_zbc_depth_v0 v0;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		चयन (args->v0.क्रमmat) अणु
		हाल FERMI_A_ZBC_DEPTH_V0_FMT_FP32:
			ret = gf100_gr_zbc_depth_get(gr, args->v0.क्रमmat,
							   args->v0.ds,
							   args->v0.l2);
			वापस (ret >= 0) ? 0 : -ENOSPC;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
gf100_fermi_mthd(काष्ठा nvkm_object *object, u32 mthd, व्योम *data, u32 size)
अणु
	nvअगर_ioctl(object, "fermi mthd %08x\n", mthd);
	चयन (mthd) अणु
	हाल FERMI_A_ZBC_COLOR:
		वापस gf100_fermi_mthd_zbc_color(object, data, size);
	हाल FERMI_A_ZBC_DEPTH:
		वापस gf100_fermi_mthd_zbc_depth(object, data, size);
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

स्थिर काष्ठा nvkm_object_func
gf100_fermi = अणु
	.mthd = gf100_fermi_mthd,
पूर्ण;

अटल व्योम
gf100_gr_mthd_set_shader_exceptions(काष्ठा nvkm_device *device, u32 data)
अणु
	nvkm_wr32(device, 0x419e44, data ? 0xffffffff : 0x00000000);
	nvkm_wr32(device, 0x419e4c, data ? 0xffffffff : 0x00000000);
पूर्ण

अटल bool
gf100_gr_mthd_sw(काष्ठा nvkm_device *device, u16 class, u32 mthd, u32 data)
अणु
	चयन (class & 0x00ff) अणु
	हाल 0x97:
	हाल 0xc0:
		चयन (mthd) अणु
		हाल 0x1528:
			gf100_gr_mthd_set_shader_exceptions(device, data);
			वापस true;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
gf100_gr_object_func = अणु
पूर्ण;

अटल पूर्णांक
gf100_gr_object_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *data, u32 size,
		    काष्ठा nvkm_object **pobject)
अणु
	काष्ठा gf100_gr_chan *chan = gf100_gr_chan(oclass->parent);
	काष्ठा gf100_gr_object *object;

	अगर (!(object = kzalloc(माप(*object), GFP_KERNEL)))
		वापस -ENOMEM;
	*pobject = &object->object;

	nvkm_object_ctor(oclass->base.func ? oclass->base.func :
			 &gf100_gr_object_func, oclass, &object->object);
	object->chan = chan;
	वापस 0;
पूर्ण

अटल पूर्णांक
gf100_gr_object_get(काष्ठा nvkm_gr *base, पूर्णांक index, काष्ठा nvkm_sclass *sclass)
अणु
	काष्ठा gf100_gr *gr = gf100_gr(base);
	पूर्णांक c = 0;

	जबतक (gr->func->sclass[c].oclass) अणु
		अगर (c++ == index) अणु
			*sclass = gr->func->sclass[index];
			sclass->ctor = gf100_gr_object_new;
			वापस index;
		पूर्ण
	पूर्ण

	वापस c;
पूर्ण

/*******************************************************************************
 * PGRAPH context
 ******************************************************************************/

अटल पूर्णांक
gf100_gr_chan_bind(काष्ठा nvkm_object *object, काष्ठा nvkm_gpuobj *parent,
		   पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	काष्ठा gf100_gr_chan *chan = gf100_gr_chan(object);
	काष्ठा gf100_gr *gr = chan->gr;
	पूर्णांक ret, i;

	ret = nvkm_gpuobj_new(gr->base.engine.subdev.device, gr->size,
			      align, false, parent, pgpuobj);
	अगर (ret)
		वापस ret;

	nvkm_kmap(*pgpuobj);
	क्रम (i = 0; i < gr->size; i += 4)
		nvkm_wo32(*pgpuobj, i, gr->data[i / 4]);

	अगर (!gr->firmware) अणु
		nvkm_wo32(*pgpuobj, 0x00, chan->mmio_nr / 2);
		nvkm_wo32(*pgpuobj, 0x04, chan->mmio_vma->addr >> 8);
	पूर्ण अन्यथा अणु
		nvkm_wo32(*pgpuobj, 0xf4, 0);
		nvkm_wo32(*pgpuobj, 0xf8, 0);
		nvkm_wo32(*pgpuobj, 0x10, chan->mmio_nr / 2);
		nvkm_wo32(*pgpuobj, 0x14, lower_32_bits(chan->mmio_vma->addr));
		nvkm_wo32(*pgpuobj, 0x18, upper_32_bits(chan->mmio_vma->addr));
		nvkm_wo32(*pgpuobj, 0x1c, 1);
		nvkm_wo32(*pgpuobj, 0x20, 0);
		nvkm_wo32(*pgpuobj, 0x28, 0);
		nvkm_wo32(*pgpuobj, 0x2c, 0);
	पूर्ण
	nvkm_करोne(*pgpuobj);
	वापस 0;
पूर्ण

अटल व्योम *
gf100_gr_chan_dtor(काष्ठा nvkm_object *object)
अणु
	काष्ठा gf100_gr_chan *chan = gf100_gr_chan(object);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(chan->data); i++) अणु
		nvkm_vmm_put(chan->vmm, &chan->data[i].vma);
		nvkm_memory_unref(&chan->data[i].mem);
	पूर्ण

	nvkm_vmm_put(chan->vmm, &chan->mmio_vma);
	nvkm_memory_unref(&chan->mmio);
	nvkm_vmm_unref(&chan->vmm);
	वापस chan;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
gf100_gr_chan = अणु
	.dtor = gf100_gr_chan_dtor,
	.bind = gf100_gr_chan_bind,
पूर्ण;

अटल पूर्णांक
gf100_gr_chan_new(काष्ठा nvkm_gr *base, काष्ठा nvkm_fअगरo_chan *fअगरoch,
		  स्थिर काष्ठा nvkm_oclass *oclass,
		  काष्ठा nvkm_object **pobject)
अणु
	काष्ठा gf100_gr *gr = gf100_gr(base);
	काष्ठा gf100_gr_data *data = gr->mmio_data;
	काष्ठा gf100_gr_mmio *mmio = gr->mmio_list;
	काष्ठा gf100_gr_chan *chan;
	काष्ठा gf100_vmm_map_v0 args = अणु .priv = 1 पूर्ण;
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	पूर्णांक ret, i;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(&gf100_gr_chan, oclass, &chan->object);
	chan->gr = gr;
	chan->vmm = nvkm_vmm_ref(fअगरoch->vmm);
	*pobject = &chan->object;

	/* allocate memory क्रम a "mmio list" buffer that's used by the HUB
	 * fuc to modअगरy some per-context रेजिस्टर settings on first load
	 * of the context.
	 */
	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 0x1000, 0x100,
			      false, &chan->mmio);
	अगर (ret)
		वापस ret;

	ret = nvkm_vmm_get(fअगरoch->vmm, 12, 0x1000, &chan->mmio_vma);
	अगर (ret)
		वापस ret;

	ret = nvkm_memory_map(chan->mmio, 0, fअगरoch->vmm,
			      chan->mmio_vma, &args, माप(args));
	अगर (ret)
		वापस ret;

	/* allocate buffers referenced by mmio list */
	क्रम (i = 0; data->size && i < ARRAY_SIZE(gr->mmio_data); i++) अणु
		ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST,
				      data->size, data->align, false,
				      &chan->data[i].mem);
		अगर (ret)
			वापस ret;

		ret = nvkm_vmm_get(fअगरoch->vmm, 12,
				   nvkm_memory_size(chan->data[i].mem),
				   &chan->data[i].vma);
		अगर (ret)
			वापस ret;

		args.priv = data->priv;

		ret = nvkm_memory_map(chan->data[i].mem, 0, chan->vmm,
				      chan->data[i].vma, &args, माप(args));
		अगर (ret)
			वापस ret;

		data++;
	पूर्ण

	/* finally, fill in the mmio list and poपूर्णांक the context at it */
	nvkm_kmap(chan->mmio);
	क्रम (i = 0; mmio->addr && i < ARRAY_SIZE(gr->mmio_list); i++) अणु
		u32 addr = mmio->addr;
		u32 data = mmio->data;

		अगर (mmio->buffer >= 0) अणु
			u64 info = chan->data[mmio->buffer].vma->addr;
			data |= info >> mmio->shअगरt;
		पूर्ण

		nvkm_wo32(chan->mmio, chan->mmio_nr++ * 4, addr);
		nvkm_wo32(chan->mmio, chan->mmio_nr++ * 4, data);
		mmio++;
	पूर्ण
	nvkm_करोne(chan->mmio);
	वापस 0;
पूर्ण

/*******************************************************************************
 * PGRAPH रेजिस्टर lists
 ******************************************************************************/

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_मुख्य_0[] = अणु
	अणु 0x400080,   1, 0x04, 0x003083c2 पूर्ण,
	अणु 0x400088,   1, 0x04, 0x00006fe7 पूर्ण,
	अणु 0x40008c,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x400090,   1, 0x04, 0x00000030 पूर्ण,
	अणु 0x40013c,   1, 0x04, 0x013901f7 पूर्ण,
	अणु 0x400140,   1, 0x04, 0x00000100 पूर्ण,
	अणु 0x400144,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x400148,   1, 0x04, 0x00000110 पूर्ण,
	अणु 0x400138,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x400130,   2, 0x04, 0x00000000 पूर्ण,
	अणु 0x400124,   1, 0x04, 0x00000002 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_fe_0[] = अणु
	अणु 0x40415c,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x404170,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_pri_0[] = अणु
	अणु 0x404488,   2, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_rstr2d_0[] = अणु
	अणु 0x407808,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_pd_0[] = अणु
	अणु 0x406024,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_ds_0[] = अणु
	अणु 0x405844,   1, 0x04, 0x00ffffff पूर्ण,
	अणु 0x405850,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x405908,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_scc_0[] = अणु
	अणु 0x40803c,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_prop_0[] = अणु
	अणु 0x4184a0,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_gpc_unk_0[] = अणु
	अणु 0x418604,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x418680,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x418714,   1, 0x04, 0x80000000 पूर्ण,
	अणु 0x418384,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_setup_0[] = अणु
	अणु 0x418814,   3, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_crstr_0[] = अणु
	अणु 0x418b04,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_setup_1[] = अणु
	अणु 0x4188c8,   1, 0x04, 0x80000000 पूर्ण,
	अणु 0x4188cc,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x4188d0,   1, 0x04, 0x00010000 पूर्ण,
	अणु 0x4188d4,   1, 0x04, 0x00000001 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_zcull_0[] = अणु
	अणु 0x418910,   1, 0x04, 0x00010001 पूर्ण,
	अणु 0x418914,   1, 0x04, 0x00000301 पूर्ण,
	अणु 0x418918,   1, 0x04, 0x00800000 पूर्ण,
	अणु 0x418980,   1, 0x04, 0x77777770 पूर्ण,
	अणु 0x418984,   3, 0x04, 0x77777777 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_gpm_0[] = अणु
	अणु 0x418c04,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x418c88,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_gpc_unk_1[] = अणु
	अणु 0x418d00,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x418f08,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x418e00,   1, 0x04, 0x00000050 पूर्ण,
	अणु 0x418e08,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_gcc_0[] = अणु
	अणु 0x41900c,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x419018,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_tpccs_0[] = अणु
	अणु 0x419d08,   2, 0x04, 0x00000000 पूर्ण,
	अणु 0x419d10,   1, 0x04, 0x00000014 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_tex_0[] = अणु
	अणु 0x419ab0,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x419ab8,   1, 0x04, 0x000000e7 पूर्ण,
	अणु 0x419abc,   2, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_pe_0[] = अणु
	अणु 0x41980c,   3, 0x04, 0x00000000 पूर्ण,
	अणु 0x419844,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x41984c,   1, 0x04, 0x00005bc5 पूर्ण,
	अणु 0x419850,   4, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_l1c_0[] = अणु
	अणु 0x419c98,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x419ca8,   1, 0x04, 0x80000000 पूर्ण,
	अणु 0x419cb4,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x419cb8,   1, 0x04, 0x00008bf4 पूर्ण,
	अणु 0x419cbc,   1, 0x04, 0x28137606 पूर्ण,
	अणु 0x419cc0,   2, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_wwdx_0[] = अणु
	अणु 0x419bd4,   1, 0x04, 0x00800000 पूर्ण,
	अणु 0x419bdc,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_tpccs_1[] = अणु
	अणु 0x419d2c,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_mpc_0[] = अणु
	अणु 0x419c0c,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_init
gf100_gr_init_sm_0[] = अणु
	अणु 0x419e00,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x419ea0,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x419ea4,   1, 0x04, 0x00000100 पूर्ण,
	अणु 0x419ea8,   1, 0x04, 0x00001100 पूर्ण,
	अणु 0x419eac,   1, 0x04, 0x11100702 पूर्ण,
	अणु 0x419eb0,   1, 0x04, 0x00000003 पूर्ण,
	अणु 0x419eb4,   4, 0x04, 0x00000000 पूर्ण,
	अणु 0x419ec8,   1, 0x04, 0x06060618 पूर्ण,
	अणु 0x419ed0,   1, 0x04, 0x0eff0e38 पूर्ण,
	अणु 0x419ed4,   1, 0x04, 0x011104f1 पूर्ण,
	अणु 0x419edc,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x419f00,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x419f2c,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_be_0[] = अणु
	अणु 0x40880c,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x408910,   9, 0x04, 0x00000000 पूर्ण,
	अणु 0x408950,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x408954,   1, 0x04, 0x0000ffff पूर्ण,
	अणु 0x408984,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x408988,   1, 0x04, 0x08040201 पूर्ण,
	अणु 0x40898c,   1, 0x04, 0x80402010 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_fe_1[] = अणु
	अणु 0x4040f0,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf100_gr_init_pe_1[] = अणु
	अणु 0x419880,   1, 0x04, 0x00000002 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_pack
gf100_gr_pack_mmio[] = अणु
	अणु gf100_gr_init_मुख्य_0 पूर्ण,
	अणु gf100_gr_init_fe_0 पूर्ण,
	अणु gf100_gr_init_pri_0 पूर्ण,
	अणु gf100_gr_init_rstr2d_0 पूर्ण,
	अणु gf100_gr_init_pd_0 पूर्ण,
	अणु gf100_gr_init_ds_0 पूर्ण,
	अणु gf100_gr_init_scc_0 पूर्ण,
	अणु gf100_gr_init_prop_0 पूर्ण,
	अणु gf100_gr_init_gpc_unk_0 पूर्ण,
	अणु gf100_gr_init_setup_0 पूर्ण,
	अणु gf100_gr_init_crstr_0 पूर्ण,
	अणु gf100_gr_init_setup_1 पूर्ण,
	अणु gf100_gr_init_zcull_0 पूर्ण,
	अणु gf100_gr_init_gpm_0 पूर्ण,
	अणु gf100_gr_init_gpc_unk_1 पूर्ण,
	अणु gf100_gr_init_gcc_0 पूर्ण,
	अणु gf100_gr_init_tpccs_0 पूर्ण,
	अणु gf100_gr_init_tex_0 पूर्ण,
	अणु gf100_gr_init_pe_0 पूर्ण,
	अणु gf100_gr_init_l1c_0 पूर्ण,
	अणु gf100_gr_init_wwdx_0 पूर्ण,
	अणु gf100_gr_init_tpccs_1 पूर्ण,
	अणु gf100_gr_init_mpc_0 पूर्ण,
	अणु gf100_gr_init_sm_0 पूर्ण,
	अणु gf100_gr_init_be_0 पूर्ण,
	अणु gf100_gr_init_fe_1 पूर्ण,
	अणु gf100_gr_init_pe_1 पूर्ण,
	अणुपूर्ण
पूर्ण;

/*******************************************************************************
 * PGRAPH engine/subdev functions
 ******************************************************************************/

अटल u32
gf100_gr_ctxsw_inst(काष्ठा nvkm_gr *gr)
अणु
	वापस nvkm_rd32(gr->engine.subdev.device, 0x409b00);
पूर्ण

अटल पूर्णांक
gf100_gr_fecs_ctrl_ctxsw(काष्ठा gf100_gr *gr, u32 mthd)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;

	nvkm_wr32(device, 0x409804, 0xffffffff);
	nvkm_wr32(device, 0x409840, 0xffffffff);
	nvkm_wr32(device, 0x409500, 0xffffffff);
	nvkm_wr32(device, 0x409504, mthd);
	nvkm_msec(device, 2000,
		u32 stat = nvkm_rd32(device, 0x409804);
		अगर (stat == 0x00000002)
			वापस -EIO;
		अगर (stat == 0x00000001)
			वापस 0;
	);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक
gf100_gr_fecs_start_ctxsw(काष्ठा nvkm_gr *base)
अणु
	काष्ठा gf100_gr *gr = gf100_gr(base);
	पूर्णांक ret = 0;

	mutex_lock(&gr->fecs.mutex);
	अगर (!--gr->fecs.disable) अणु
		अगर (WARN_ON(ret = gf100_gr_fecs_ctrl_ctxsw(gr, 0x39)))
			gr->fecs.disable++;
	पूर्ण
	mutex_unlock(&gr->fecs.mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक
gf100_gr_fecs_stop_ctxsw(काष्ठा nvkm_gr *base)
अणु
	काष्ठा gf100_gr *gr = gf100_gr(base);
	पूर्णांक ret = 0;

	mutex_lock(&gr->fecs.mutex);
	अगर (!gr->fecs.disable++) अणु
		अगर (WARN_ON(ret = gf100_gr_fecs_ctrl_ctxsw(gr, 0x38)))
			gr->fecs.disable--;
	पूर्ण
	mutex_unlock(&gr->fecs.mutex);
	वापस ret;
पूर्ण

पूर्णांक
gf100_gr_fecs_bind_poपूर्णांकer(काष्ठा gf100_gr *gr, u32 inst)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;

	nvkm_wr32(device, 0x409840, 0x00000030);
	nvkm_wr32(device, 0x409500, inst);
	nvkm_wr32(device, 0x409504, 0x00000003);
	nvkm_msec(device, 2000,
		u32 stat = nvkm_rd32(device, 0x409800);
		अगर (stat & 0x00000020)
			वापस -EIO;
		अगर (stat & 0x00000010)
			वापस 0;
	);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक
gf100_gr_fecs_set_reglist_भव_address(काष्ठा gf100_gr *gr, u64 addr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;

	nvkm_wr32(device, 0x409810, addr >> 8);
	nvkm_wr32(device, 0x409800, 0x00000000);
	nvkm_wr32(device, 0x409500, 0x00000001);
	nvkm_wr32(device, 0x409504, 0x00000032);
	nvkm_msec(device, 2000,
		अगर (nvkm_rd32(device, 0x409800) == 0x00000001)
			वापस 0;
	);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक
gf100_gr_fecs_set_reglist_bind_instance(काष्ठा gf100_gr *gr, u32 inst)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;

	nvkm_wr32(device, 0x409810, inst);
	nvkm_wr32(device, 0x409800, 0x00000000);
	nvkm_wr32(device, 0x409500, 0x00000001);
	nvkm_wr32(device, 0x409504, 0x00000031);
	nvkm_msec(device, 2000,
		अगर (nvkm_rd32(device, 0x409800) == 0x00000001)
			वापस 0;
	);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक
gf100_gr_fecs_discover_reglist_image_size(काष्ठा gf100_gr *gr, u32 *psize)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;

	nvkm_wr32(device, 0x409800, 0x00000000);
	nvkm_wr32(device, 0x409500, 0x00000001);
	nvkm_wr32(device, 0x409504, 0x00000030);
	nvkm_msec(device, 2000,
		अगर ((*psize = nvkm_rd32(device, 0x409800)))
			वापस 0;
	);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक
gf100_gr_fecs_elpg_bind(काष्ठा gf100_gr *gr)
अणु
	u32 size;
	पूर्णांक ret;

	ret = gf100_gr_fecs_discover_reglist_image_size(gr, &size);
	अगर (ret)
		वापस ret;

	/*XXX: We need to allocate + map the above पूर्णांकo PMU's inst block,
	 *     which which means we probably need a proper PMU beक्रमe we
	 *     even bother.
	 */

	ret = gf100_gr_fecs_set_reglist_bind_instance(gr, 0);
	अगर (ret)
		वापस ret;

	वापस gf100_gr_fecs_set_reglist_भव_address(gr, 0);
पूर्ण

अटल पूर्णांक
gf100_gr_fecs_discover_pm_image_size(काष्ठा gf100_gr *gr, u32 *psize)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;

	nvkm_wr32(device, 0x409840, 0xffffffff);
	nvkm_wr32(device, 0x409500, 0x00000000);
	nvkm_wr32(device, 0x409504, 0x00000025);
	nvkm_msec(device, 2000,
		अगर ((*psize = nvkm_rd32(device, 0x409800)))
			वापस 0;
	);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक
gf100_gr_fecs_discover_zcull_image_size(काष्ठा gf100_gr *gr, u32 *psize)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;

	nvkm_wr32(device, 0x409840, 0xffffffff);
	nvkm_wr32(device, 0x409500, 0x00000000);
	nvkm_wr32(device, 0x409504, 0x00000016);
	nvkm_msec(device, 2000,
		अगर ((*psize = nvkm_rd32(device, 0x409800)))
			वापस 0;
	);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक
gf100_gr_fecs_discover_image_size(काष्ठा gf100_gr *gr, u32 *psize)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;

	nvkm_wr32(device, 0x409840, 0xffffffff);
	nvkm_wr32(device, 0x409500, 0x00000000);
	nvkm_wr32(device, 0x409504, 0x00000010);
	nvkm_msec(device, 2000,
		अगर ((*psize = nvkm_rd32(device, 0x409800)))
			वापस 0;
	);

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम
gf100_gr_fecs_set_watchकरोg_समयout(काष्ठा gf100_gr *gr, u32 समयout)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;

	nvkm_wr32(device, 0x409840, 0xffffffff);
	nvkm_wr32(device, 0x409500, समयout);
	nvkm_wr32(device, 0x409504, 0x00000021);
पूर्ण

अटल bool
gf100_gr_chsw_load(काष्ठा nvkm_gr *base)
अणु
	काष्ठा gf100_gr *gr = gf100_gr(base);
	अगर (!gr->firmware) अणु
		u32 trace = nvkm_rd32(gr->base.engine.subdev.device, 0x40981c);
		अगर (trace & 0x00000040)
			वापस true;
	पूर्ण अन्यथा अणु
		u32 mthd = nvkm_rd32(gr->base.engine.subdev.device, 0x409808);
		अगर (mthd & 0x00080000)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक
gf100_gr_rops(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	वापस (nvkm_rd32(device, 0x409604) & 0x001f0000) >> 16;
पूर्ण

व्योम
gf100_gr_zbc_init(काष्ठा gf100_gr *gr)
अणु
	स्थिर u32  zero[] = अणु 0x00000000, 0x00000000, 0x00000000, 0x00000000,
			      0x00000000, 0x00000000, 0x00000000, 0x00000000 पूर्ण;
	स्थिर u32   one[] = अणु 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000,
			      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff पूर्ण;
	स्थिर u32 f32_0[] = अणु 0x00000000, 0x00000000, 0x00000000, 0x00000000,
			      0x00000000, 0x00000000, 0x00000000, 0x00000000 पूर्ण;
	स्थिर u32 f32_1[] = अणु 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000,
			      0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000 पूर्ण;
	काष्ठा nvkm_ltc *ltc = gr->base.engine.subdev.device->ltc;
	पूर्णांक index, c = ltc->zbc_min, d = ltc->zbc_min, s = ltc->zbc_min;

	अगर (!gr->zbc_color[0].क्रमmat) अणु
		gf100_gr_zbc_color_get(gr, 1,  & zero[0],   &zero[4]); c++;
		gf100_gr_zbc_color_get(gr, 2,  &  one[0],    &one[4]); c++;
		gf100_gr_zbc_color_get(gr, 4,  &f32_0[0],  &f32_0[4]); c++;
		gf100_gr_zbc_color_get(gr, 4,  &f32_1[0],  &f32_1[4]); c++;
		gf100_gr_zbc_depth_get(gr, 1, 0x00000000, 0x00000000); d++;
		gf100_gr_zbc_depth_get(gr, 1, 0x3f800000, 0x3f800000); d++;
		अगर (gr->func->zbc->stencil_get) अणु
			gr->func->zbc->stencil_get(gr, 1, 0x00, 0x00); s++;
			gr->func->zbc->stencil_get(gr, 1, 0x01, 0x01); s++;
			gr->func->zbc->stencil_get(gr, 1, 0xff, 0xff); s++;
		पूर्ण
	पूर्ण

	क्रम (index = c; index <= ltc->zbc_max; index++)
		gr->func->zbc->clear_color(gr, index);
	क्रम (index = d; index <= ltc->zbc_max; index++)
		gr->func->zbc->clear_depth(gr, index);

	अगर (gr->func->zbc->clear_stencil) अणु
		क्रम (index = s; index <= ltc->zbc_max; index++)
			gr->func->zbc->clear_stencil(gr, index);
	पूर्ण
पूर्ण

/**
 * Wait until GR goes idle. GR is considered idle अगर it is disabled by the
 * MC (0x200) रेजिस्टर, or GR is not busy and a context चयन is not in
 * progress.
 */
पूर्णांक
gf100_gr_रुको_idle(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	अचिन्हित दीर्घ end_jअगरfies = jअगरfies + msecs_to_jअगरfies(2000);
	bool gr_enabled, ctxsw_active, gr_busy;

	करो अणु
		/*
		 * required to make sure FIFO_ENGINE_STATUS (0x2640) is
		 * up-to-date
		 */
		nvkm_rd32(device, 0x400700);

		gr_enabled = nvkm_rd32(device, 0x200) & 0x1000;
		ctxsw_active = nvkm_rd32(device, 0x2640) & 0x8000;
		gr_busy = nvkm_rd32(device, 0x40060c) & 0x1;

		अगर (!gr_enabled || (!gr_busy && !ctxsw_active))
			वापस 0;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_jअगरfies));

	nvkm_error(subdev,
		   "wait for idle timeout (en: %d, ctxsw: %d, busy: %d)\n",
		   gr_enabled, ctxsw_active, gr_busy);
	वापस -EAGAIN;
पूर्ण

व्योम
gf100_gr_mmio(काष्ठा gf100_gr *gr, स्थिर काष्ठा gf100_gr_pack *p)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	स्थिर काष्ठा gf100_gr_pack *pack;
	स्थिर काष्ठा gf100_gr_init *init;

	pack_क्रम_each_init(init, pack, p) अणु
		u32 next = init->addr + init->count * init->pitch;
		u32 addr = init->addr;
		जबतक (addr < next) अणु
			nvkm_wr32(device, addr, init->data);
			addr += init->pitch;
		पूर्ण
	पूर्ण
पूर्ण

व्योम
gf100_gr_icmd(काष्ठा gf100_gr *gr, स्थिर काष्ठा gf100_gr_pack *p)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	स्थिर काष्ठा gf100_gr_pack *pack;
	स्थिर काष्ठा gf100_gr_init *init;
	u32 data = 0;

	nvkm_wr32(device, 0x400208, 0x80000000);

	pack_क्रम_each_init(init, pack, p) अणु
		u32 next = init->addr + init->count * init->pitch;
		u32 addr = init->addr;

		अगर ((pack == p && init == p->init) || data != init->data) अणु
			nvkm_wr32(device, 0x400204, init->data);
			data = init->data;
		पूर्ण

		जबतक (addr < next) अणु
			nvkm_wr32(device, 0x400200, addr);
			/**
			 * Wait क्रम GR to go idle after submitting a
			 * GO_IDLE bundle
			 */
			अगर ((addr & 0xffff) == 0xe100)
				gf100_gr_रुको_idle(gr);
			nvkm_msec(device, 2000,
				अगर (!(nvkm_rd32(device, 0x400700) & 0x00000004))
					अवरोध;
			);
			addr += init->pitch;
		पूर्ण
	पूर्ण

	nvkm_wr32(device, 0x400208, 0x00000000);
पूर्ण

व्योम
gf100_gr_mthd(काष्ठा gf100_gr *gr, स्थिर काष्ठा gf100_gr_pack *p)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	स्थिर काष्ठा gf100_gr_pack *pack;
	स्थिर काष्ठा gf100_gr_init *init;
	u32 data = 0;

	pack_क्रम_each_init(init, pack, p) अणु
		u32 ctrl = 0x80000000 | pack->type;
		u32 next = init->addr + init->count * init->pitch;
		u32 addr = init->addr;

		अगर ((pack == p && init == p->init) || data != init->data) अणु
			nvkm_wr32(device, 0x40448c, init->data);
			data = init->data;
		पूर्ण

		जबतक (addr < next) अणु
			nvkm_wr32(device, 0x404488, ctrl | (addr << 14));
			addr += init->pitch;
		पूर्ण
	पूर्ण
पूर्ण

u64
gf100_gr_units(काष्ठा nvkm_gr *base)
अणु
	काष्ठा gf100_gr *gr = gf100_gr(base);
	u64 cfg;

	cfg  = (u32)gr->gpc_nr;
	cfg |= (u32)gr->tpc_total << 8;
	cfg |= (u64)gr->rop_nr << 32;

	वापस cfg;
पूर्ण

अटल स्थिर काष्ठा nvkm_bitfield gf100_dispatch_error[] = अणु
	अणु 0x00000001, "INJECTED_BUNDLE_ERROR" पूर्ण,
	अणु 0x00000002, "CLASS_SUBCH_MISMATCH" पूर्ण,
	अणु 0x00000004, "SUBCHSW_DURING_NOTIFY" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield gf100_m2mf_error[] = अणु
	अणु 0x00000001, "PUSH_TOO_MUCH_DATA" पूर्ण,
	अणु 0x00000002, "PUSH_NOT_ENOUGH_DATA" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield gf100_unk6_error[] = अणु
	अणु 0x00000001, "TEMP_TOO_SMALL" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield gf100_ccache_error[] = अणु
	अणु 0x00000001, "INTR" पूर्ण,
	अणु 0x00000002, "LDCONST_OOB" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield gf100_macro_error[] = अणु
	अणु 0x00000001, "TOO_FEW_PARAMS" पूर्ण,
	अणु 0x00000002, "TOO_MANY_PARAMS" पूर्ण,
	अणु 0x00000004, "ILLEGAL_OPCODE" पूर्ण,
	अणु 0x00000008, "DOUBLE_BRANCH" पूर्ण,
	अणु 0x00000010, "WATCHDOG" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield gk104_sked_error[] = अणु
	अणु 0x00000040, "CTA_RESUME" पूर्ण,
	अणु 0x00000080, "CONSTANT_BUFFER_SIZE" पूर्ण,
	अणु 0x00000200, "LOCAL_MEMORY_SIZE_POS" पूर्ण,
	अणु 0x00000400, "LOCAL_MEMORY_SIZE_NEG" पूर्ण,
	अणु 0x00000800, "WARP_CSTACK_SIZE" पूर्ण,
	अणु 0x00001000, "TOTAL_TEMP_SIZE" पूर्ण,
	अणु 0x00002000, "REGISTER_COUNT" पूर्ण,
	अणु 0x00040000, "TOTAL_THREADS" पूर्ण,
	अणु 0x00100000, "PROGRAM_OFFSET" पूर्ण,
	अणु 0x00200000, "SHARED_MEMORY_SIZE" पूर्ण,
	अणु 0x00800000, "CTA_THREAD_DIMENSION_ZERO" पूर्ण,
	अणु 0x01000000, "MEMORY_WINDOW_OVERLAP" पूर्ण,
	अणु 0x02000000, "SHARED_CONFIG_TOO_SMALL" पूर्ण,
	अणु 0x04000000, "TOTAL_REGISTER_COUNT" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_bitfield gf100_gpc_rop_error[] = अणु
	अणु 0x00000002, "RT_PITCH_OVERRUN" पूर्ण,
	अणु 0x00000010, "RT_WIDTH_OVERRUN" पूर्ण,
	अणु 0x00000020, "RT_HEIGHT_OVERRUN" पूर्ण,
	अणु 0x00000080, "ZETA_STORAGE_TYPE_MISMATCH" पूर्ण,
	अणु 0x00000100, "RT_STORAGE_TYPE_MISMATCH" पूर्ण,
	अणु 0x00000400, "RT_LINEAR_MISMATCH" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
gf100_gr_trap_gpc_rop(काष्ठा gf100_gr *gr, पूर्णांक gpc)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	अक्षर error[128];
	u32 trap[4];

	trap[0] = nvkm_rd32(device, GPC_UNIT(gpc, 0x0420)) & 0x3fffffff;
	trap[1] = nvkm_rd32(device, GPC_UNIT(gpc, 0x0434));
	trap[2] = nvkm_rd32(device, GPC_UNIT(gpc, 0x0438));
	trap[3] = nvkm_rd32(device, GPC_UNIT(gpc, 0x043c));

	nvkm_snprपूर्णांकbf(error, माप(error), gf100_gpc_rop_error, trap[0]);

	nvkm_error(subdev, "GPC%d/PROP trap: %08x [%s] x = %u, y = %u, "
			   "format = %x, storage type = %x\n",
		   gpc, trap[0], error, trap[1] & 0xffff, trap[1] >> 16,
		   (trap[2] >> 8) & 0x3f, trap[3] & 0xff);
	nvkm_wr32(device, GPC_UNIT(gpc, 0x0420), 0xc0000000);
पूर्ण

स्थिर काष्ठा nvkm_क्रमागत gf100_mp_warp_error[] = अणु
	अणु 0x01, "STACK_ERROR" पूर्ण,
	अणु 0x02, "API_STACK_ERROR" पूर्ण,
	अणु 0x03, "RET_EMPTY_STACK_ERROR" पूर्ण,
	अणु 0x04, "PC_WRAP" पूर्ण,
	अणु 0x05, "MISALIGNED_PC" पूर्ण,
	अणु 0x06, "PC_OVERFLOW" पूर्ण,
	अणु 0x07, "MISALIGNED_IMMC_ADDR" पूर्ण,
	अणु 0x08, "MISALIGNED_REG" पूर्ण,
	अणु 0x09, "ILLEGAL_INSTR_ENCODING" पूर्ण,
	अणु 0x0a, "ILLEGAL_SPH_INSTR_COMBO" पूर्ण,
	अणु 0x0b, "ILLEGAL_INSTR_PARAM" पूर्ण,
	अणु 0x0c, "INVALID_CONST_ADDR" पूर्ण,
	अणु 0x0d, "OOR_REG" पूर्ण,
	अणु 0x0e, "OOR_ADDR" पूर्ण,
	अणु 0x0f, "MISALIGNED_ADDR" पूर्ण,
	अणु 0x10, "INVALID_ADDR_SPACE" पूर्ण,
	अणु 0x11, "ILLEGAL_INSTR_PARAM2" पूर्ण,
	अणु 0x12, "INVALID_CONST_ADDR_LDC" पूर्ण,
	अणु 0x13, "GEOMETRY_SM_ERROR" पूर्ण,
	अणु 0x14, "DIVERGENT" पूर्ण,
	अणु 0x15, "WARP_EXIT" पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_bitfield gf100_mp_global_error[] = अणु
	अणु 0x00000001, "SM_TO_SM_FAULT" पूर्ण,
	अणु 0x00000002, "L1_ERROR" पूर्ण,
	अणु 0x00000004, "MULTIPLE_WARP_ERRORS" पूर्ण,
	अणु 0x00000008, "PHYSICAL_STACK_OVERFLOW" पूर्ण,
	अणु 0x00000010, "BPT_INT" पूर्ण,
	अणु 0x00000020, "BPT_PAUSE" पूर्ण,
	अणु 0x00000040, "SINGLE_STEP_COMPLETE" पूर्ण,
	अणु 0x20000000, "ECC_SEC_ERROR" पूर्ण,
	अणु 0x40000000, "ECC_DED_ERROR" पूर्ण,
	अणु 0x80000000, "TIMEOUT" पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम
gf100_gr_trap_mp(काष्ठा gf100_gr *gr, पूर्णांक gpc, पूर्णांक tpc)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 werr = nvkm_rd32(device, TPC_UNIT(gpc, tpc, 0x648));
	u32 gerr = nvkm_rd32(device, TPC_UNIT(gpc, tpc, 0x650));
	स्थिर काष्ठा nvkm_क्रमागत *warp;
	अक्षर glob[128];

	nvkm_snprपूर्णांकbf(glob, माप(glob), gf100_mp_global_error, gerr);
	warp = nvkm_क्रमागत_find(gf100_mp_warp_error, werr & 0xffff);

	nvkm_error(subdev, "GPC%i/TPC%i/MP trap: "
			   "global %08x [%s] warp %04x [%s]\n",
		   gpc, tpc, gerr, glob, werr, warp ? warp->name : "");

	nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x648), 0x00000000);
	nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x650), gerr);
पूर्ण

अटल व्योम
gf100_gr_trap_tpc(काष्ठा gf100_gr *gr, पूर्णांक gpc, पूर्णांक tpc)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, TPC_UNIT(gpc, tpc, 0x0508));

	अगर (stat & 0x00000001) अणु
		u32 trap = nvkm_rd32(device, TPC_UNIT(gpc, tpc, 0x0224));
		nvkm_error(subdev, "GPC%d/TPC%d/TEX: %08x\n", gpc, tpc, trap);
		nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x0224), 0xc0000000);
		stat &= ~0x00000001;
	पूर्ण

	अगर (stat & 0x00000002) अणु
		gr->func->trap_mp(gr, gpc, tpc);
		stat &= ~0x00000002;
	पूर्ण

	अगर (stat & 0x00000004) अणु
		u32 trap = nvkm_rd32(device, TPC_UNIT(gpc, tpc, 0x0084));
		nvkm_error(subdev, "GPC%d/TPC%d/POLY: %08x\n", gpc, tpc, trap);
		nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x0084), 0xc0000000);
		stat &= ~0x00000004;
	पूर्ण

	अगर (stat & 0x00000008) अणु
		u32 trap = nvkm_rd32(device, TPC_UNIT(gpc, tpc, 0x048c));
		nvkm_error(subdev, "GPC%d/TPC%d/L1C: %08x\n", gpc, tpc, trap);
		nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x048c), 0xc0000000);
		stat &= ~0x00000008;
	पूर्ण

	अगर (stat & 0x00000010) अणु
		u32 trap = nvkm_rd32(device, TPC_UNIT(gpc, tpc, 0x0430));
		nvkm_error(subdev, "GPC%d/TPC%d/MPC: %08x\n", gpc, tpc, trap);
		nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x0430), 0xc0000000);
		stat &= ~0x00000010;
	पूर्ण

	अगर (stat) अणु
		nvkm_error(subdev, "GPC%d/TPC%d/%08x: unknown\n", gpc, tpc, stat);
	पूर्ण
पूर्ण

अटल व्योम
gf100_gr_trap_gpc(काष्ठा gf100_gr *gr, पूर्णांक gpc)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, GPC_UNIT(gpc, 0x2c90));
	पूर्णांक tpc;

	अगर (stat & 0x00000001) अणु
		gf100_gr_trap_gpc_rop(gr, gpc);
		stat &= ~0x00000001;
	पूर्ण

	अगर (stat & 0x00000002) अणु
		u32 trap = nvkm_rd32(device, GPC_UNIT(gpc, 0x0900));
		nvkm_error(subdev, "GPC%d/ZCULL: %08x\n", gpc, trap);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0900), 0xc0000000);
		stat &= ~0x00000002;
	पूर्ण

	अगर (stat & 0x00000004) अणु
		u32 trap = nvkm_rd32(device, GPC_UNIT(gpc, 0x1028));
		nvkm_error(subdev, "GPC%d/CCACHE: %08x\n", gpc, trap);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x1028), 0xc0000000);
		stat &= ~0x00000004;
	पूर्ण

	अगर (stat & 0x00000008) अणु
		u32 trap = nvkm_rd32(device, GPC_UNIT(gpc, 0x0824));
		nvkm_error(subdev, "GPC%d/ESETUP: %08x\n", gpc, trap);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0824), 0xc0000000);
		stat &= ~0x00000009;
	पूर्ण

	क्रम (tpc = 0; tpc < gr->tpc_nr[gpc]; tpc++) अणु
		u32 mask = 0x00010000 << tpc;
		अगर (stat & mask) अणु
			gf100_gr_trap_tpc(gr, gpc, tpc);
			nvkm_wr32(device, GPC_UNIT(gpc, 0x2c90), mask);
			stat &= ~mask;
		पूर्ण
	पूर्ण

	अगर (stat) अणु
		nvkm_error(subdev, "GPC%d/%08x: unknown\n", gpc, stat);
	पूर्ण
पूर्ण

अटल व्योम
gf100_gr_trap_पूर्णांकr(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	अक्षर error[128];
	u32 trap = nvkm_rd32(device, 0x400108);
	पूर्णांक rop, gpc;

	अगर (trap & 0x00000001) अणु
		u32 stat = nvkm_rd32(device, 0x404000);

		nvkm_snprपूर्णांकbf(error, माप(error), gf100_dispatch_error,
			       stat & 0x3fffffff);
		nvkm_error(subdev, "DISPATCH %08x [%s]\n", stat, error);
		nvkm_wr32(device, 0x404000, 0xc0000000);
		nvkm_wr32(device, 0x400108, 0x00000001);
		trap &= ~0x00000001;
	पूर्ण

	अगर (trap & 0x00000002) अणु
		u32 stat = nvkm_rd32(device, 0x404600);

		nvkm_snprपूर्णांकbf(error, माप(error), gf100_m2mf_error,
			       stat & 0x3fffffff);
		nvkm_error(subdev, "M2MF %08x [%s]\n", stat, error);

		nvkm_wr32(device, 0x404600, 0xc0000000);
		nvkm_wr32(device, 0x400108, 0x00000002);
		trap &= ~0x00000002;
	पूर्ण

	अगर (trap & 0x00000008) अणु
		u32 stat = nvkm_rd32(device, 0x408030);

		nvkm_snprपूर्णांकbf(error, माप(error), gf100_ccache_error,
			       stat & 0x3fffffff);
		nvkm_error(subdev, "CCACHE %08x [%s]\n", stat, error);
		nvkm_wr32(device, 0x408030, 0xc0000000);
		nvkm_wr32(device, 0x400108, 0x00000008);
		trap &= ~0x00000008;
	पूर्ण

	अगर (trap & 0x00000010) अणु
		u32 stat = nvkm_rd32(device, 0x405840);
		nvkm_error(subdev, "SHADER %08x, sph: 0x%06x, stage: 0x%02x\n",
			   stat, stat & 0xffffff, (stat >> 24) & 0x3f);
		nvkm_wr32(device, 0x405840, 0xc0000000);
		nvkm_wr32(device, 0x400108, 0x00000010);
		trap &= ~0x00000010;
	पूर्ण

	अगर (trap & 0x00000040) अणु
		u32 stat = nvkm_rd32(device, 0x40601c);

		nvkm_snprपूर्णांकbf(error, माप(error), gf100_unk6_error,
			       stat & 0x3fffffff);
		nvkm_error(subdev, "UNK6 %08x [%s]\n", stat, error);

		nvkm_wr32(device, 0x40601c, 0xc0000000);
		nvkm_wr32(device, 0x400108, 0x00000040);
		trap &= ~0x00000040;
	पूर्ण

	अगर (trap & 0x00000080) अणु
		u32 stat = nvkm_rd32(device, 0x404490);
		u32 pc = nvkm_rd32(device, 0x404494);
		u32 op = nvkm_rd32(device, 0x40449c);

		nvkm_snprपूर्णांकbf(error, माप(error), gf100_macro_error,
			       stat & 0x1fffffff);
		nvkm_error(subdev, "MACRO %08x [%s], pc: 0x%03x%s, op: 0x%08x\n",
			   stat, error, pc & 0x7ff,
			   (pc & 0x10000000) ? "" : " (invalid)",
			   op);

		nvkm_wr32(device, 0x404490, 0xc0000000);
		nvkm_wr32(device, 0x400108, 0x00000080);
		trap &= ~0x00000080;
	पूर्ण

	अगर (trap & 0x00000100) अणु
		u32 stat = nvkm_rd32(device, 0x407020) & 0x3fffffff;

		nvkm_snprपूर्णांकbf(error, माप(error), gk104_sked_error, stat);
		nvkm_error(subdev, "SKED: %08x [%s]\n", stat, error);

		अगर (stat)
			nvkm_wr32(device, 0x407020, 0x40000000);
		nvkm_wr32(device, 0x400108, 0x00000100);
		trap &= ~0x00000100;
	पूर्ण

	अगर (trap & 0x01000000) अणु
		u32 stat = nvkm_rd32(device, 0x400118);
		क्रम (gpc = 0; stat && gpc < gr->gpc_nr; gpc++) अणु
			u32 mask = 0x00000001 << gpc;
			अगर (stat & mask) अणु
				gf100_gr_trap_gpc(gr, gpc);
				nvkm_wr32(device, 0x400118, mask);
				stat &= ~mask;
			पूर्ण
		पूर्ण
		nvkm_wr32(device, 0x400108, 0x01000000);
		trap &= ~0x01000000;
	पूर्ण

	अगर (trap & 0x02000000) अणु
		क्रम (rop = 0; rop < gr->rop_nr; rop++) अणु
			u32 statz = nvkm_rd32(device, ROP_UNIT(rop, 0x070));
			u32 statc = nvkm_rd32(device, ROP_UNIT(rop, 0x144));
			nvkm_error(subdev, "ROP%d %08x %08x\n",
				 rop, statz, statc);
			nvkm_wr32(device, ROP_UNIT(rop, 0x070), 0xc0000000);
			nvkm_wr32(device, ROP_UNIT(rop, 0x144), 0xc0000000);
		पूर्ण
		nvkm_wr32(device, 0x400108, 0x02000000);
		trap &= ~0x02000000;
	पूर्ण

	अगर (trap) अणु
		nvkm_error(subdev, "TRAP UNHANDLED %08x\n", trap);
		nvkm_wr32(device, 0x400108, trap);
	पूर्ण
पूर्ण

अटल व्योम
gf100_gr_ctxctl_debug_unit(काष्ठा gf100_gr *gr, u32 base)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	nvkm_error(subdev, "%06x - done %08x\n", base,
		   nvkm_rd32(device, base + 0x400));
	nvkm_error(subdev, "%06x - stat %08x %08x %08x %08x\n", base,
		   nvkm_rd32(device, base + 0x800),
		   nvkm_rd32(device, base + 0x804),
		   nvkm_rd32(device, base + 0x808),
		   nvkm_rd32(device, base + 0x80c));
	nvkm_error(subdev, "%06x - stat %08x %08x %08x %08x\n", base,
		   nvkm_rd32(device, base + 0x810),
		   nvkm_rd32(device, base + 0x814),
		   nvkm_rd32(device, base + 0x818),
		   nvkm_rd32(device, base + 0x81c));
पूर्ण

व्योम
gf100_gr_ctxctl_debug(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	u32 gpcnr = nvkm_rd32(device, 0x409604) & 0xffff;
	u32 gpc;

	gf100_gr_ctxctl_debug_unit(gr, 0x409000);
	क्रम (gpc = 0; gpc < gpcnr; gpc++)
		gf100_gr_ctxctl_debug_unit(gr, 0x502000 + (gpc * 0x8000));
पूर्ण

अटल व्योम
gf100_gr_ctxctl_isr(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x409c18);

	अगर (!gr->firmware && (stat & 0x00000001)) अणु
		u32 code = nvkm_rd32(device, 0x409814);
		अगर (code == E_BAD_FWMTHD) अणु
			u32 class = nvkm_rd32(device, 0x409808);
			u32  addr = nvkm_rd32(device, 0x40980c);
			u32  subc = (addr & 0x00070000) >> 16;
			u32  mthd = (addr & 0x00003ffc);
			u32  data = nvkm_rd32(device, 0x409810);

			nvkm_error(subdev, "FECS MTHD subc %d class %04x "
					   "mthd %04x data %08x\n",
				   subc, class, mthd, data);
		पूर्ण अन्यथा अणु
			nvkm_error(subdev, "FECS ucode error %d\n", code);
		पूर्ण
		nvkm_wr32(device, 0x409c20, 0x00000001);
		stat &= ~0x00000001;
	पूर्ण

	अगर (!gr->firmware && (stat & 0x00080000)) अणु
		nvkm_error(subdev, "FECS watchdog timeout\n");
		gf100_gr_ctxctl_debug(gr);
		nvkm_wr32(device, 0x409c20, 0x00080000);
		stat &= ~0x00080000;
	पूर्ण

	अगर (stat) अणु
		nvkm_error(subdev, "FECS %08x\n", stat);
		gf100_gr_ctxctl_debug(gr);
		nvkm_wr32(device, 0x409c20, stat);
	पूर्ण
पूर्ण

अटल व्योम
gf100_gr_पूर्णांकr(काष्ठा nvkm_gr *base)
अणु
	काष्ठा gf100_gr *gr = gf100_gr(base);
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_fअगरo_chan *chan;
	अचिन्हित दीर्घ flags;
	u64 inst = nvkm_rd32(device, 0x409b00) & 0x0fffffff;
	u32 stat = nvkm_rd32(device, 0x400100);
	u32 addr = nvkm_rd32(device, 0x400704);
	u32 mthd = (addr & 0x00003ffc);
	u32 subc = (addr & 0x00070000) >> 16;
	u32 data = nvkm_rd32(device, 0x400708);
	u32 code = nvkm_rd32(device, 0x400110);
	u32 class;
	स्थिर अक्षर *name = "unknown";
	पूर्णांक chid = -1;

	chan = nvkm_fअगरo_chan_inst(device->fअगरo, (u64)inst << 12, &flags);
	अगर (chan) अणु
		name = chan->object.client->name;
		chid = chan->chid;
	पूर्ण

	अगर (device->card_type < NV_E0 || subc < 4)
		class = nvkm_rd32(device, 0x404200 + (subc * 4));
	अन्यथा
		class = 0x0000;

	अगर (stat & 0x00000001) अणु
		/*
		 * notअगरier पूर्णांकerrupt, only needed क्रम cyclestats
		 * can be safely ignored
		 */
		nvkm_wr32(device, 0x400100, 0x00000001);
		stat &= ~0x00000001;
	पूर्ण

	अगर (stat & 0x00000010) अणु
		अगर (!gf100_gr_mthd_sw(device, class, mthd, data)) अणु
			nvkm_error(subdev, "ILLEGAL_MTHD ch %d [%010llx %s] "
				   "subc %d class %04x mthd %04x data %08x\n",
				   chid, inst << 12, name, subc,
				   class, mthd, data);
		पूर्ण
		nvkm_wr32(device, 0x400100, 0x00000010);
		stat &= ~0x00000010;
	पूर्ण

	अगर (stat & 0x00000020) अणु
		nvkm_error(subdev, "ILLEGAL_CLASS ch %d [%010llx %s] "
			   "subc %d class %04x mthd %04x data %08x\n",
			   chid, inst << 12, name, subc, class, mthd, data);
		nvkm_wr32(device, 0x400100, 0x00000020);
		stat &= ~0x00000020;
	पूर्ण

	अगर (stat & 0x00100000) अणु
		स्थिर काष्ठा nvkm_क्रमागत *en =
			nvkm_क्रमागत_find(nv50_data_error_names, code);
		nvkm_error(subdev, "DATA_ERROR %08x [%s] ch %d [%010llx %s] "
				   "subc %d class %04x mthd %04x data %08x\n",
			   code, en ? en->name : "", chid, inst << 12,
			   name, subc, class, mthd, data);
		nvkm_wr32(device, 0x400100, 0x00100000);
		stat &= ~0x00100000;
	पूर्ण

	अगर (stat & 0x00200000) अणु
		nvkm_error(subdev, "TRAP ch %d [%010llx %s]\n",
			   chid, inst << 12, name);
		gf100_gr_trap_पूर्णांकr(gr);
		nvkm_wr32(device, 0x400100, 0x00200000);
		stat &= ~0x00200000;
	पूर्ण

	अगर (stat & 0x00080000) अणु
		gf100_gr_ctxctl_isr(gr);
		nvkm_wr32(device, 0x400100, 0x00080000);
		stat &= ~0x00080000;
	पूर्ण

	अगर (stat) अणु
		nvkm_error(subdev, "intr %08x\n", stat);
		nvkm_wr32(device, 0x400100, stat);
	पूर्ण

	nvkm_wr32(device, 0x400500, 0x00010001);
	nvkm_fअगरo_chan_put(device->fअगरo, flags, &chan);
पूर्ण

अटल व्योम
gf100_gr_init_fw(काष्ठा nvkm_falcon *falcon,
		 काष्ठा nvkm_blob *code, काष्ठा nvkm_blob *data)
अणु
	nvkm_falcon_load_dmem(falcon, data->data, 0x0, data->size, 0);
	nvkm_falcon_load_imem(falcon, code->data, 0x0, code->size, 0, 0, false);
पूर्ण

अटल व्योम
gf100_gr_init_csdata(काष्ठा gf100_gr *gr,
		     स्थिर काष्ठा gf100_gr_pack *pack,
		     u32 falcon, u32 starstar, u32 base)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	स्थिर काष्ठा gf100_gr_pack *iter;
	स्थिर काष्ठा gf100_gr_init *init;
	u32 addr = ~0, prev = ~0, xfer = 0;
	u32 star, temp;

	nvkm_wr32(device, falcon + 0x01c0, 0x02000000 + starstar);
	star = nvkm_rd32(device, falcon + 0x01c4);
	temp = nvkm_rd32(device, falcon + 0x01c4);
	अगर (temp > star)
		star = temp;
	nvkm_wr32(device, falcon + 0x01c0, 0x01000000 + star);

	pack_क्रम_each_init(init, iter, pack) अणु
		u32 head = init->addr - base;
		u32 tail = head + init->count * init->pitch;
		जबतक (head < tail) अणु
			अगर (head != prev + 4 || xfer >= 32) अणु
				अगर (xfer) अणु
					u32 data = ((--xfer << 26) | addr);
					nvkm_wr32(device, falcon + 0x01c4, data);
					star += 4;
				पूर्ण
				addr = head;
				xfer = 0;
			पूर्ण
			prev = head;
			xfer = xfer + 1;
			head = head + init->pitch;
		पूर्ण
	पूर्ण

	nvkm_wr32(device, falcon + 0x01c4, (--xfer << 26) | addr);
	nvkm_wr32(device, falcon + 0x01c0, 0x01000004 + starstar);
	nvkm_wr32(device, falcon + 0x01c4, star + 4);
पूर्ण

/* Initialize context from an बाह्यal (secure or not) firmware */
अटल पूर्णांक
gf100_gr_init_ctxctl_ext(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 lsf_mask = 0;
	पूर्णांक ret;

	/* load fuc microcode */
	nvkm_mc_unk260(device, 0);

	/* securely-managed falcons must be reset using secure boot */

	अगर (!nvkm_acr_managed_falcon(device, NVKM_ACR_LSF_FECS)) अणु
		gf100_gr_init_fw(&gr->fecs.falcon, &gr->fecs.inst,
						   &gr->fecs.data);
	पूर्ण अन्यथा अणु
		lsf_mask |= BIT(NVKM_ACR_LSF_FECS);
	पूर्ण

	अगर (!nvkm_acr_managed_falcon(device, NVKM_ACR_LSF_GPCCS)) अणु
		gf100_gr_init_fw(&gr->gpccs.falcon, &gr->gpccs.inst,
						    &gr->gpccs.data);
	पूर्ण अन्यथा अणु
		lsf_mask |= BIT(NVKM_ACR_LSF_GPCCS);
	पूर्ण

	अगर (lsf_mask) अणु
		ret = nvkm_acr_bootstrap_falcons(device, lsf_mask);
		अगर (ret)
			वापस ret;
	पूर्ण

	nvkm_mc_unk260(device, 1);

	/* start both of them running */
	nvkm_wr32(device, 0x409840, 0xffffffff);
	nvkm_wr32(device, 0x41a10c, 0x00000000);
	nvkm_wr32(device, 0x40910c, 0x00000000);

	nvkm_falcon_start(&gr->gpccs.falcon);
	nvkm_falcon_start(&gr->fecs.falcon);

	अगर (nvkm_msec(device, 2000,
		अगर (nvkm_rd32(device, 0x409800) & 0x00000001)
			अवरोध;
	) < 0)
		वापस -EBUSY;

	gf100_gr_fecs_set_watchकरोg_समयout(gr, 0x7fffffff);

	/* Determine how much memory is required to store मुख्य context image. */
	ret = gf100_gr_fecs_discover_image_size(gr, &gr->size);
	अगर (ret)
		वापस ret;

	/* Determine how much memory is required to store ZCULL image. */
	ret = gf100_gr_fecs_discover_zcull_image_size(gr, &gr->size_zcull);
	अगर (ret)
		वापस ret;

	/* Determine how much memory is required to store PerfMon image. */
	ret = gf100_gr_fecs_discover_pm_image_size(gr, &gr->size_pm);
	अगर (ret)
		वापस ret;

	/*XXX: We (likely) require PMU support to even bother with this.
	 *
	 *     Also, it seems like not all GPUs support ELPG.  Traces I
	 *     have here show RM enabling it on Kepler/Turing, but none
	 *     of the GPUs between those.  NVGPU decides this by PCIID.
	 */
	अगर (0) अणु
		ret = gf100_gr_fecs_elpg_bind(gr);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Generate golden context image. */
	अगर (gr->data == शून्य) अणु
		पूर्णांक ret = gf100_grctx_generate(gr);
		अगर (ret) अणु
			nvkm_error(subdev, "failed to construct context\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
gf100_gr_init_ctxctl_पूर्णांक(काष्ठा gf100_gr *gr)
अणु
	स्थिर काष्ठा gf100_grctx_func *grctx = gr->func->grctx;
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;

	अगर (!gr->func->fecs.ucode) अणु
		वापस -ENOSYS;
	पूर्ण

	/* load HUB microcode */
	nvkm_mc_unk260(device, 0);
	nvkm_falcon_load_dmem(&gr->fecs.falcon,
			      gr->func->fecs.ucode->data.data, 0x0,
			      gr->func->fecs.ucode->data.size, 0);
	nvkm_falcon_load_imem(&gr->fecs.falcon,
			      gr->func->fecs.ucode->code.data, 0x0,
			      gr->func->fecs.ucode->code.size, 0, 0, false);

	/* load GPC microcode */
	nvkm_falcon_load_dmem(&gr->gpccs.falcon,
			      gr->func->gpccs.ucode->data.data, 0x0,
			      gr->func->gpccs.ucode->data.size, 0);
	nvkm_falcon_load_imem(&gr->gpccs.falcon,
			      gr->func->gpccs.ucode->code.data, 0x0,
			      gr->func->gpccs.ucode->code.size, 0, 0, false);
	nvkm_mc_unk260(device, 1);

	/* load रेजिस्टर lists */
	gf100_gr_init_csdata(gr, grctx->hub, 0x409000, 0x000, 0x000000);
	gf100_gr_init_csdata(gr, grctx->gpc_0, 0x41a000, 0x000, 0x418000);
	gf100_gr_init_csdata(gr, grctx->gpc_1, 0x41a000, 0x000, 0x418000);
	gf100_gr_init_csdata(gr, grctx->tpc, 0x41a000, 0x004, 0x419800);
	gf100_gr_init_csdata(gr, grctx->ppc, 0x41a000, 0x008, 0x41be00);

	/* start HUB ucode running, it'll init the GPCs */
	nvkm_wr32(device, 0x40910c, 0x00000000);
	nvkm_wr32(device, 0x409100, 0x00000002);
	अगर (nvkm_msec(device, 2000,
		अगर (nvkm_rd32(device, 0x409800) & 0x80000000)
			अवरोध;
	) < 0) अणु
		gf100_gr_ctxctl_debug(gr);
		वापस -EBUSY;
	पूर्ण

	gr->size = nvkm_rd32(device, 0x409804);
	अगर (gr->data == शून्य) अणु
		पूर्णांक ret = gf100_grctx_generate(gr);
		अगर (ret) अणु
			nvkm_error(subdev, "failed to construct context\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
gf100_gr_init_ctxctl(काष्ठा gf100_gr *gr)
अणु
	पूर्णांक ret;

	अगर (gr->firmware)
		ret = gf100_gr_init_ctxctl_ext(gr);
	अन्यथा
		ret = gf100_gr_init_ctxctl_पूर्णांक(gr);

	वापस ret;
पूर्ण

व्योम
gf100_gr_oneinit_sm_id(काष्ठा gf100_gr *gr)
अणु
	पूर्णांक tpc, gpc;
	क्रम (tpc = 0; tpc < gr->tpc_max; tpc++) अणु
		क्रम (gpc = 0; gpc < gr->gpc_nr; gpc++) अणु
			अगर (tpc < gr->tpc_nr[gpc]) अणु
				gr->sm[gr->sm_nr].gpc = gpc;
				gr->sm[gr->sm_nr].tpc = tpc;
				gr->sm_nr++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम
gf100_gr_oneinit_tiles(काष्ठा gf100_gr *gr)
अणु
	अटल स्थिर u8 primes[] = अणु
		3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61
	पूर्ण;
	पूर्णांक init_frac[GPC_MAX], init_err[GPC_MAX], run_err[GPC_MAX], i, j;
	u32 mul_factor, comm_denom;
	u8  gpc_map[GPC_MAX];
	bool sorted;

	चयन (gr->tpc_total) अणु
	हाल 15: gr->screen_tile_row_offset = 0x06; अवरोध;
	हाल 14: gr->screen_tile_row_offset = 0x05; अवरोध;
	हाल 13: gr->screen_tile_row_offset = 0x02; अवरोध;
	हाल 11: gr->screen_tile_row_offset = 0x07; अवरोध;
	हाल 10: gr->screen_tile_row_offset = 0x06; अवरोध;
	हाल  7:
	हाल  5: gr->screen_tile_row_offset = 0x01; अवरोध;
	हाल  3: gr->screen_tile_row_offset = 0x02; अवरोध;
	हाल  2:
	हाल  1: gr->screen_tile_row_offset = 0x01; अवरोध;
	शेष: gr->screen_tile_row_offset = 0x03;
		क्रम (i = 0; i < ARRAY_SIZE(primes); i++) अणु
			अगर (gr->tpc_total % primes[i]) अणु
				gr->screen_tile_row_offset = primes[i];
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	/* Sort GPCs by TPC count, highest-to-lowest. */
	क्रम (i = 0; i < gr->gpc_nr; i++)
		gpc_map[i] = i;
	sorted = false;

	जबतक (!sorted) अणु
		क्रम (sorted = true, i = 0; i < gr->gpc_nr - 1; i++) अणु
			अगर (gr->tpc_nr[gpc_map[i + 1]] >
			    gr->tpc_nr[gpc_map[i + 0]]) अणु
				u8 swap = gpc_map[i];
				gpc_map[i + 0] = gpc_map[i + 1];
				gpc_map[i + 1] = swap;
				sorted = false;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Determine tile->GPC mapping */
	mul_factor = gr->gpc_nr * gr->tpc_max;
	अगर (mul_factor & 1)
		mul_factor = 2;
	अन्यथा
		mul_factor = 1;

	comm_denom = gr->gpc_nr * gr->tpc_max * mul_factor;

	क्रम (i = 0; i < gr->gpc_nr; i++) अणु
		init_frac[i] = gr->tpc_nr[gpc_map[i]] * gr->gpc_nr * mul_factor;
		 init_err[i] = i * gr->tpc_max * mul_factor - comm_denom/2;
		  run_err[i] = init_frac[i] + init_err[i];
	पूर्ण

	क्रम (i = 0; i < gr->tpc_total;) अणु
		क्रम (j = 0; j < gr->gpc_nr; j++) अणु
			अगर ((run_err[j] * 2) >= comm_denom) अणु
				gr->tile[i++] = gpc_map[j];
				run_err[j] += init_frac[j] - comm_denom;
			पूर्ण अन्यथा अणु
				run_err[j] += init_frac[j];
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
gf100_gr_oneinit(काष्ठा nvkm_gr *base)
अणु
	काष्ठा gf100_gr *gr = gf100_gr(base);
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	पूर्णांक i, j;

	nvkm_pmu_pgob(device->pmu, false);

	gr->rop_nr = gr->func->rops(gr);
	gr->gpc_nr = nvkm_rd32(device, 0x409604) & 0x0000001f;
	क्रम (i = 0; i < gr->gpc_nr; i++) अणु
		gr->tpc_nr[i]  = nvkm_rd32(device, GPC_UNIT(i, 0x2608));
		gr->tpc_max = max(gr->tpc_max, gr->tpc_nr[i]);
		gr->tpc_total += gr->tpc_nr[i];
		gr->ppc_nr[i]  = gr->func->ppc_nr;
		क्रम (j = 0; j < gr->ppc_nr[i]; j++) अणु
			gr->ppc_tpc_mask[i][j] =
				nvkm_rd32(device, GPC_UNIT(i, 0x0c30 + (j * 4)));
			अगर (gr->ppc_tpc_mask[i][j] == 0)
				जारी;
			gr->ppc_mask[i] |= (1 << j);
			gr->ppc_tpc_nr[i][j] = hweight8(gr->ppc_tpc_mask[i][j]);
			अगर (gr->ppc_tpc_min == 0 ||
			    gr->ppc_tpc_min > gr->ppc_tpc_nr[i][j])
				gr->ppc_tpc_min = gr->ppc_tpc_nr[i][j];
			अगर (gr->ppc_tpc_max < gr->ppc_tpc_nr[i][j])
				gr->ppc_tpc_max = gr->ppc_tpc_nr[i][j];
		पूर्ण
	पूर्ण

	स_रखो(gr->tile, 0xff, माप(gr->tile));
	gr->func->oneinit_tiles(gr);
	gr->func->oneinit_sm_id(gr);
	वापस 0;
पूर्ण

अटल पूर्णांक
gf100_gr_init_(काष्ठा nvkm_gr *base)
अणु
	काष्ठा gf100_gr *gr = gf100_gr(base);
	काष्ठा nvkm_subdev *subdev = &base->engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	bool reset = device->chipset == 0x137 || device->chipset == 0x138;
	u32 ret;

	/* On certain GP107/GP108 boards, we trigger a weird issue where
	 * GR will stop responding to PRI accesses after we've asked the
	 * SEC2 RTOS to boot the GR falcons.  This happens with far more
	 * frequency when cold-booting a board (ie. वापसing from D3).
	 *
	 * The root cause क्रम this is not known and has proven dअगरficult
	 * to isolate, with many avenues being dead-ends.
	 *
	 * A workaround was discovered by Karol, whereby putting GR पूर्णांकo
	 * reset क्रम an extended period right beक्रमe initialisation
	 * prevents the problem from occuring.
	 *
	 * XXX: As RM करोes not require any such workaround, this is more
	 *      of a hack than a true fix.
	 */
	reset = nvkm_boolopt(device->cfgopt, "NvGrResetWar", reset);
	अगर (reset) अणु
		nvkm_mask(device, 0x000200, 0x00001000, 0x00000000);
		nvkm_rd32(device, 0x000200);
		msleep(50);
		nvkm_mask(device, 0x000200, 0x00001000, 0x00001000);
		nvkm_rd32(device, 0x000200);
	पूर्ण

	nvkm_pmu_pgob(gr->base.engine.subdev.device->pmu, false);

	ret = nvkm_falcon_get(&gr->fecs.falcon, subdev);
	अगर (ret)
		वापस ret;

	ret = nvkm_falcon_get(&gr->gpccs.falcon, subdev);
	अगर (ret)
		वापस ret;

	वापस gr->func->init(gr);
पूर्ण

अटल पूर्णांक
gf100_gr_fini(काष्ठा nvkm_gr *base, bool suspend)
अणु
	काष्ठा gf100_gr *gr = gf100_gr(base);
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	nvkm_falcon_put(&gr->gpccs.falcon, subdev);
	nvkm_falcon_put(&gr->fecs.falcon, subdev);
	वापस 0;
पूर्ण

अटल व्योम *
gf100_gr_dtor(काष्ठा nvkm_gr *base)
अणु
	काष्ठा gf100_gr *gr = gf100_gr(base);

	kमुक्त(gr->data);

	nvkm_falcon_dtor(&gr->gpccs.falcon);
	nvkm_falcon_dtor(&gr->fecs.falcon);

	nvkm_blob_dtor(&gr->fecs.inst);
	nvkm_blob_dtor(&gr->fecs.data);
	nvkm_blob_dtor(&gr->gpccs.inst);
	nvkm_blob_dtor(&gr->gpccs.data);

	vमुक्त(gr->bundle);
	vमुक्त(gr->method);
	vमुक्त(gr->sw_ctx);
	vमुक्त(gr->sw_nonctx);

	वापस gr;
पूर्ण

अटल स्थिर काष्ठा nvkm_gr_func
gf100_gr_ = अणु
	.dtor = gf100_gr_dtor,
	.oneinit = gf100_gr_oneinit,
	.init = gf100_gr_init_,
	.fini = gf100_gr_fini,
	.पूर्णांकr = gf100_gr_पूर्णांकr,
	.units = gf100_gr_units,
	.chan_new = gf100_gr_chan_new,
	.object_get = gf100_gr_object_get,
	.chsw_load = gf100_gr_chsw_load,
	.ctxsw.छोड़ो = gf100_gr_fecs_stop_ctxsw,
	.ctxsw.resume = gf100_gr_fecs_start_ctxsw,
	.ctxsw.inst = gf100_gr_ctxsw_inst,
पूर्ण;

अटल स्थिर काष्ठा nvkm_falcon_func
gf100_gr_flcn = अणु
	.fbअगर = 0x600,
	.load_imem = nvkm_falcon_v1_load_imem,
	.load_dmem = nvkm_falcon_v1_load_dmem,
	.पढ़ो_dmem = nvkm_falcon_v1_पढ़ो_dmem,
	.bind_context = nvkm_falcon_v1_bind_context,
	.रुको_क्रम_halt = nvkm_falcon_v1_रुको_क्रम_halt,
	.clear_पूर्णांकerrupt = nvkm_falcon_v1_clear_पूर्णांकerrupt,
	.set_start_addr = nvkm_falcon_v1_set_start_addr,
	.start = nvkm_falcon_v1_start,
	.enable = nvkm_falcon_v1_enable,
	.disable = nvkm_falcon_v1_disable,
पूर्ण;

पूर्णांक
gf100_gr_new_(स्थिर काष्ठा gf100_gr_fwअगर *fwअगर, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	काष्ठा gf100_gr *gr;
	पूर्णांक ret;

	अगर (!(gr = kzalloc(माप(*gr), GFP_KERNEL)))
		वापस -ENOMEM;
	*pgr = &gr->base;

	ret = nvkm_gr_ctor(&gf100_gr_, device, type, inst, true, &gr->base);
	अगर (ret)
		वापस ret;

	fwअगर = nvkm_firmware_load(&gr->base.engine.subdev, fwअगर, "Gr", gr);
	अगर (IS_ERR(fwअगर))
		वापस PTR_ERR(fwअगर);

	gr->func = fwअगर->func;

	ret = nvkm_falcon_ctor(&gf100_gr_flcn, &gr->base.engine.subdev,
			       "fecs", 0x409000, &gr->fecs.falcon);
	अगर (ret)
		वापस ret;

	mutex_init(&gr->fecs.mutex);

	ret = nvkm_falcon_ctor(&gf100_gr_flcn, &gr->base.engine.subdev,
			       "gpccs", 0x41a000, &gr->gpccs.falcon);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

व्योम
gf100_gr_init_num_tpc_per_gpc(काष्ठा gf100_gr *gr, bool pd, bool ds)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	पूर्णांक gpc, i, j;
	u32 data;

	क्रम (gpc = 0, i = 0; i < 4; i++) अणु
		क्रम (data = 0, j = 0; j < 8 && gpc < gr->gpc_nr; j++, gpc++)
			data |= gr->tpc_nr[gpc] << (j * 4);
		अगर (pd)
			nvkm_wr32(device, 0x406028 + (i * 4), data);
		अगर (ds)
			nvkm_wr32(device, 0x405870 + (i * 4), data);
	पूर्ण
पूर्ण

व्योम
gf100_gr_init_400054(काष्ठा gf100_gr *gr)
अणु
	nvkm_wr32(gr->base.engine.subdev.device, 0x400054, 0x34ce3464);
पूर्ण

व्योम
gf100_gr_init_shader_exceptions(काष्ठा gf100_gr *gr, पूर्णांक gpc, पूर्णांक tpc)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x644), 0x001ffffe);
	nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x64c), 0x0000000f);
पूर्ण

व्योम
gf100_gr_init_tex_hww_esr(काष्ठा gf100_gr *gr, पूर्णांक gpc, पूर्णांक tpc)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x224), 0xc0000000);
पूर्ण

व्योम
gf100_gr_init_419eb4(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	nvkm_mask(device, 0x419eb4, 0x00001000, 0x00001000);
पूर्ण

व्योम
gf100_gr_init_419cc0(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	पूर्णांक gpc, tpc;

	nvkm_mask(device, 0x419cc0, 0x00000008, 0x00000008);

	क्रम (gpc = 0; gpc < gr->gpc_nr; gpc++) अणु
		क्रम (tpc = 0; tpc < gr->tpc_nr[gpc]; tpc++)
			nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x48c), 0xc0000000);
	पूर्ण
पूर्ण

व्योम
gf100_gr_init_40601c(काष्ठा gf100_gr *gr)
अणु
	nvkm_wr32(gr->base.engine.subdev.device, 0x40601c, 0xc0000000);
पूर्ण

व्योम
gf100_gr_init_fecs_exceptions(काष्ठा gf100_gr *gr)
अणु
	स्थिर u32 data = gr->firmware ? 0x000e0000 : 0x000e0001;
	nvkm_wr32(gr->base.engine.subdev.device, 0x409c24, data);
पूर्ण

व्योम
gf100_gr_init_gpc_mmu(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	काष्ठा nvkm_fb *fb = device->fb;

	nvkm_wr32(device, 0x418880, nvkm_rd32(device, 0x100c80) & 0x00000001);
	nvkm_wr32(device, 0x4188a4, 0x03000000);
	nvkm_wr32(device, 0x418888, 0x00000000);
	nvkm_wr32(device, 0x41888c, 0x00000000);
	nvkm_wr32(device, 0x418890, 0x00000000);
	nvkm_wr32(device, 0x418894, 0x00000000);
	nvkm_wr32(device, 0x4188b4, nvkm_memory_addr(fb->mmu_wr) >> 8);
	nvkm_wr32(device, 0x4188b8, nvkm_memory_addr(fb->mmu_rd) >> 8);
पूर्ण

व्योम
gf100_gr_init_num_active_ltcs(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	nvkm_wr32(device, GPC_BCAST(0x08ac), nvkm_rd32(device, 0x100800));
पूर्ण

व्योम
gf100_gr_init_zcull(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	स्थिर u32 magicgpc918 = DIV_ROUND_UP(0x00800000, gr->tpc_total);
	स्थिर u8 tile_nr = ALIGN(gr->tpc_total, 32);
	u8 bank[GPC_MAX] = अणुपूर्ण, gpc, i, j;
	u32 data;

	क्रम (i = 0; i < tile_nr; i += 8) अणु
		क्रम (data = 0, j = 0; j < 8 && i + j < gr->tpc_total; j++) अणु
			data |= bank[gr->tile[i + j]] << (j * 4);
			bank[gr->tile[i + j]]++;
		पूर्ण
		nvkm_wr32(device, GPC_BCAST(0x0980 + ((i / 8) * 4)), data);
	पूर्ण

	क्रम (gpc = 0; gpc < gr->gpc_nr; gpc++) अणु
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0914),
			  gr->screen_tile_row_offset << 8 | gr->tpc_nr[gpc]);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0910), 0x00040000 |
							 gr->tpc_total);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0918), magicgpc918);
	पूर्ण

	nvkm_wr32(device, GPC_BCAST(0x1bd4), magicgpc918);
पूर्ण

व्योम
gf100_gr_init_vsc_stream_master(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	nvkm_mask(device, TPC_UNIT(0, 0, 0x05c), 0x00000001, 0x00000001);
पूर्ण

पूर्णांक
gf100_gr_init(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	पूर्णांक gpc, tpc, rop;

	अगर (gr->func->init_419bd8)
		gr->func->init_419bd8(gr);

	gr->func->init_gpc_mmu(gr);

	अगर (gr->sw_nonctx)
		gf100_gr_mmio(gr, gr->sw_nonctx);
	अन्यथा
		gf100_gr_mmio(gr, gr->func->mmio);

	gf100_gr_रुको_idle(gr);

	अगर (gr->func->init_r405a14)
		gr->func->init_r405a14(gr);

	अगर (gr->func->clkgate_pack)
		nvkm_therm_clkgate_init(device->therm, gr->func->clkgate_pack);

	अगर (gr->func->init_bios)
		gr->func->init_bios(gr);

	gr->func->init_vsc_stream_master(gr);
	gr->func->init_zcull(gr);
	gr->func->init_num_active_ltcs(gr);
	अगर (gr->func->init_rop_active_fbps)
		gr->func->init_rop_active_fbps(gr);
	अगर (gr->func->init_bios_2)
		gr->func->init_bios_2(gr);
	अगर (gr->func->init_swdx_pes_mask)
		gr->func->init_swdx_pes_mask(gr);
	अगर (gr->func->init_fs)
		gr->func->init_fs(gr);

	nvkm_wr32(device, 0x400500, 0x00010001);

	nvkm_wr32(device, 0x400100, 0xffffffff);
	nvkm_wr32(device, 0x40013c, 0xffffffff);
	nvkm_wr32(device, 0x400124, 0x00000002);

	gr->func->init_fecs_exceptions(gr);
	अगर (gr->func->init_ds_hww_esr_2)
		gr->func->init_ds_hww_esr_2(gr);

	nvkm_wr32(device, 0x404000, 0xc0000000);
	nvkm_wr32(device, 0x404600, 0xc0000000);
	nvkm_wr32(device, 0x408030, 0xc0000000);

	अगर (gr->func->init_40601c)
		gr->func->init_40601c(gr);

	nvkm_wr32(device, 0x406018, 0xc0000000);
	nvkm_wr32(device, 0x404490, 0xc0000000);

	अगर (gr->func->init_sked_hww_esr)
		gr->func->init_sked_hww_esr(gr);

	nvkm_wr32(device, 0x405840, 0xc0000000);
	nvkm_wr32(device, 0x405844, 0x00ffffff);

	अगर (gr->func->init_419cc0)
		gr->func->init_419cc0(gr);
	अगर (gr->func->init_419eb4)
		gr->func->init_419eb4(gr);
	अगर (gr->func->init_419c9c)
		gr->func->init_419c9c(gr);

	अगर (gr->func->init_ppc_exceptions)
		gr->func->init_ppc_exceptions(gr);

	क्रम (gpc = 0; gpc < gr->gpc_nr; gpc++) अणु
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0420), 0xc0000000);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0900), 0xc0000000);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x1028), 0xc0000000);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0824), 0xc0000000);
		क्रम (tpc = 0; tpc < gr->tpc_nr[gpc]; tpc++) अणु
			nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x508), 0xffffffff);
			nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x50c), 0xffffffff);
			अगर (gr->func->init_tex_hww_esr)
				gr->func->init_tex_hww_esr(gr, gpc, tpc);
			nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x084), 0xc0000000);
			अगर (gr->func->init_504430)
				gr->func->init_504430(gr, gpc, tpc);
			gr->func->init_shader_exceptions(gr, gpc, tpc);
		पूर्ण
		nvkm_wr32(device, GPC_UNIT(gpc, 0x2c90), 0xffffffff);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x2c94), 0xffffffff);
	पूर्ण

	क्रम (rop = 0; rop < gr->rop_nr; rop++) अणु
		nvkm_wr32(device, ROP_UNIT(rop, 0x144), 0x40000000);
		nvkm_wr32(device, ROP_UNIT(rop, 0x070), 0x40000000);
		nvkm_wr32(device, ROP_UNIT(rop, 0x204), 0xffffffff);
		nvkm_wr32(device, ROP_UNIT(rop, 0x208), 0xffffffff);
	पूर्ण

	nvkm_wr32(device, 0x400108, 0xffffffff);
	nvkm_wr32(device, 0x400138, 0xffffffff);
	nvkm_wr32(device, 0x400118, 0xffffffff);
	nvkm_wr32(device, 0x400130, 0xffffffff);
	nvkm_wr32(device, 0x40011c, 0xffffffff);
	nvkm_wr32(device, 0x400134, 0xffffffff);

	अगर (gr->func->init_400054)
		gr->func->init_400054(gr);

	gf100_gr_zbc_init(gr);

	अगर (gr->func->init_4188a4)
		gr->func->init_4188a4(gr);

	वापस gf100_gr_init_ctxctl(gr);
पूर्ण

#समावेश "fuc/hubgf100.fuc3.h"

काष्ठा gf100_gr_ucode
gf100_gr_fecs_ucode = अणु
	.code.data = gf100_grhub_code,
	.code.size = माप(gf100_grhub_code),
	.data.data = gf100_grhub_data,
	.data.size = माप(gf100_grhub_data),
पूर्ण;

#समावेश "fuc/gpcgf100.fuc3.h"

काष्ठा gf100_gr_ucode
gf100_gr_gpccs_ucode = अणु
	.code.data = gf100_grgpc_code,
	.code.size = माप(gf100_grgpc_code),
	.data.data = gf100_grgpc_data,
	.data.size = माप(gf100_grgpc_data),
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_func
gf100_gr = अणु
	.oneinit_tiles = gf100_gr_oneinit_tiles,
	.oneinit_sm_id = gf100_gr_oneinit_sm_id,
	.init = gf100_gr_init,
	.init_gpc_mmu = gf100_gr_init_gpc_mmu,
	.init_vsc_stream_master = gf100_gr_init_vsc_stream_master,
	.init_zcull = gf100_gr_init_zcull,
	.init_num_active_ltcs = gf100_gr_init_num_active_ltcs,
	.init_fecs_exceptions = gf100_gr_init_fecs_exceptions,
	.init_40601c = gf100_gr_init_40601c,
	.init_419cc0 = gf100_gr_init_419cc0,
	.init_419eb4 = gf100_gr_init_419eb4,
	.init_tex_hww_esr = gf100_gr_init_tex_hww_esr,
	.init_shader_exceptions = gf100_gr_init_shader_exceptions,
	.init_400054 = gf100_gr_init_400054,
	.trap_mp = gf100_gr_trap_mp,
	.mmio = gf100_gr_pack_mmio,
	.fecs.ucode = &gf100_gr_fecs_ucode,
	.gpccs.ucode = &gf100_gr_gpccs_ucode,
	.rops = gf100_gr_rops,
	.grctx = &gf100_grctx,
	.zbc = &gf100_gr_zbc,
	.sclass = अणु
		अणु -1, -1, FERMI_TWOD_A पूर्ण,
		अणु -1, -1, FERMI_MEMORY_TO_MEMORY_FORMAT_A पूर्ण,
		अणु -1, -1, FERMI_A, &gf100_fermi पूर्ण,
		अणु -1, -1, FERMI_COMPUTE_A पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
gf100_gr_nofw(काष्ठा gf100_gr *gr, पूर्णांक ver, स्थिर काष्ठा gf100_gr_fwअगर *fwअगर)
अणु
	gr->firmware = false;
	वापस 0;
पूर्ण

अटल पूर्णांक
gf100_gr_load_fw(काष्ठा gf100_gr *gr, स्थिर अक्षर *name,
		 काष्ठा nvkm_blob *blob)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर काष्ठा firmware *fw;
	अक्षर f[32];
	पूर्णांक ret;

	snम_लिखो(f, माप(f), "nouveau/nv%02x_%s", device->chipset, name);
	ret = request_firmware(&fw, f, device->dev);
	अगर (ret) अणु
		snम_लिखो(f, माप(f), "nouveau/%s", name);
		ret = request_firmware(&fw, f, device->dev);
		अगर (ret) अणु
			nvkm_error(subdev, "failed to load %s\n", name);
			वापस ret;
		पूर्ण
	पूर्ण

	blob->size = fw->size;
	blob->data = kmemdup(fw->data, blob->size, GFP_KERNEL);
	release_firmware(fw);
	वापस (blob->data != शून्य) ? 0 : -ENOMEM;
पूर्ण

पूर्णांक
gf100_gr_load(काष्ठा gf100_gr *gr, पूर्णांक ver, स्थिर काष्ठा gf100_gr_fwअगर *fwअगर)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;

	अगर (!nvkm_boolopt(device->cfgopt, "NvGrUseFW", false))
		वापस -EINVAL;

	अगर (gf100_gr_load_fw(gr, "fuc409c", &gr->fecs.inst) ||
	    gf100_gr_load_fw(gr, "fuc409d", &gr->fecs.data) ||
	    gf100_gr_load_fw(gr, "fuc41ac", &gr->gpccs.inst) ||
	    gf100_gr_load_fw(gr, "fuc41ad", &gr->gpccs.data))
		वापस -ENOENT;

	gr->firmware = true;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा gf100_gr_fwअगर
gf100_gr_fwअगर[] = अणु
	अणु -1, gf100_gr_load, &gf100_gr पूर्ण,
	अणु -1, gf100_gr_nofw, &gf100_gr पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gf100_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस gf100_gr_new_(gf100_gr_fwअगर, device, type, inst, pgr);
पूर्ण
