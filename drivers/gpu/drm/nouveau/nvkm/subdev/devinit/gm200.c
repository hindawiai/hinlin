<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
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
#समावेश "nv50.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/bit.h>
#समावेश <subdev/bios/pmu.h>
#समावेश <subdev/समयr.h>

अटल व्योम
pmu_code(काष्ठा nv50_devinit *init, u32 pmu, u32 img, u32 len, bool sec)
अणु
	काष्ठा nvkm_device *device = init->base.subdev.device;
	काष्ठा nvkm_bios *bios = device->bios;
	पूर्णांक i;

	nvkm_wr32(device, 0x10a180, 0x01000000 | (sec ? 0x10000000 : 0) | pmu);
	क्रम (i = 0; i < len; i += 4) अणु
		अगर ((i & 0xff) == 0)
			nvkm_wr32(device, 0x10a188, (pmu + i) >> 8);
		nvkm_wr32(device, 0x10a184, nvbios_rd32(bios, img + i));
	पूर्ण

	जबतक (i & 0xff) अणु
		nvkm_wr32(device, 0x10a184, 0x00000000);
		i += 4;
	पूर्ण
पूर्ण

अटल व्योम
pmu_data(काष्ठा nv50_devinit *init, u32 pmu, u32 img, u32 len)
अणु
	काष्ठा nvkm_device *device = init->base.subdev.device;
	काष्ठा nvkm_bios *bios = device->bios;
	पूर्णांक i;

	nvkm_wr32(device, 0x10a1c0, 0x01000000 | pmu);
	क्रम (i = 0; i < len; i += 4)
		nvkm_wr32(device, 0x10a1c4, nvbios_rd32(bios, img + i));
पूर्ण

अटल u32
pmu_args(काष्ठा nv50_devinit *init, u32 argp, u32 argi)
अणु
	काष्ठा nvkm_device *device = init->base.subdev.device;
	nvkm_wr32(device, 0x10a1c0, argp);
	nvkm_wr32(device, 0x10a1c0, nvkm_rd32(device, 0x10a1c4) + argi);
	वापस nvkm_rd32(device, 0x10a1c4);
पूर्ण

अटल व्योम
pmu_exec(काष्ठा nv50_devinit *init, u32 init_addr)
अणु
	काष्ठा nvkm_device *device = init->base.subdev.device;
	nvkm_wr32(device, 0x10a104, init_addr);
	nvkm_wr32(device, 0x10a10c, 0x00000000);
	nvkm_wr32(device, 0x10a100, 0x00000002);
पूर्ण

अटल पूर्णांक
pmu_load(काष्ठा nv50_devinit *init, u8 type, bool post,
	 u32 *init_addr_pmu, u32 *args_addr_pmu)
अणु
	काष्ठा nvkm_subdev *subdev = &init->base.subdev;
	काष्ठा nvkm_bios *bios = subdev->device->bios;
	काष्ठा nvbios_pmuR pmu;

	अगर (!nvbios_pmuRm(bios, type, &pmu))
		वापस -EINVAL;

	अगर (!post)
		वापस 0;

	pmu_code(init, pmu.boot_addr_pmu, pmu.boot_addr, pmu.boot_size, false);
	pmu_code(init, pmu.code_addr_pmu, pmu.code_addr, pmu.code_size, true);
	pmu_data(init, pmu.data_addr_pmu, pmu.data_addr, pmu.data_size);

	अगर (init_addr_pmu) अणु
		*init_addr_pmu = pmu.init_addr_pmu;
		*args_addr_pmu = pmu.args_addr_pmu;
		वापस 0;
	पूर्ण

	वापस pmu_exec(init, pmu.init_addr_pmu), 0;
पूर्ण

व्योम
gm200_devinit_preos(काष्ठा nv50_devinit *init, bool post)
अणु
	/* Optional: Execute PRE_OS application on PMU, which should at
	 * least take care of fans until a full PMU has been loaded.
	 */
	pmu_load(init, 0x01, post, शून्य, शून्य);
पूर्ण

पूर्णांक
gm200_devinit_post(काष्ठा nvkm_devinit *base, bool post)
अणु
	काष्ठा nv50_devinit *init = nv50_devinit(base);
	काष्ठा nvkm_subdev *subdev = &init->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_bios *bios = device->bios;
	काष्ठा bit_entry bit_I;
	u32 exec, args;
	पूर्णांक ret;

	अगर (bit_entry(bios, 'I', &bit_I) || bit_I.version != 1 ||
					    bit_I.length < 0x1c) अणु
		nvkm_error(subdev, "VBIOS PMU init data not found\n");
		वापस -EINVAL;
	पूर्ण

	/* Upload DEVINIT application from VBIOS onto PMU. */
	ret = pmu_load(init, 0x04, post, &exec, &args);
	अगर (ret) अणु
		nvkm_error(subdev, "VBIOS PMU/DEVINIT not found\n");
		वापस ret;
	पूर्ण

	/* Upload tables required by opcodes in boot scripts. */
	अगर (post) अणु
		u32 pmu = pmu_args(init, args + 0x08, 0x08);
		u32 img = nvbios_rd16(bios, bit_I.offset + 0x14);
		u32 len = nvbios_rd16(bios, bit_I.offset + 0x16);
		pmu_data(init, pmu, img, len);
	पूर्ण

	/* Upload boot scripts. */
	अगर (post) अणु
		u32 pmu = pmu_args(init, args + 0x08, 0x10);
		u32 img = nvbios_rd16(bios, bit_I.offset + 0x18);
		u32 len = nvbios_rd16(bios, bit_I.offset + 0x1a);
		pmu_data(init, pmu, img, len);
	पूर्ण

	/* Execute DEVINIT. */
	अगर (post) अणु
		nvkm_wr32(device, 0x10a040, 0x00005000);
		pmu_exec(init, exec);
		अगर (nvkm_msec(device, 2000,
			अगर (nvkm_rd32(device, 0x10a040) & 0x00002000)
				अवरोध;
		) < 0)
			वापस -ETIMEDOUT;
	पूर्ण

	gm200_devinit_preos(init, post);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_devinit_func
gm200_devinit = अणु
	.preinit = gf100_devinit_preinit,
	.init = nv50_devinit_init,
	.post = gm200_devinit_post,
	.pll_set = gf100_devinit_pll_set,
	.disable = gm107_devinit_disable,
पूर्ण;

पूर्णांक
gm200_devinit_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		  काष्ठा nvkm_devinit **pinit)
अणु
	वापस nv50_devinit_new_(&gm200_devinit, device, type, inst, pinit);
पूर्ण
