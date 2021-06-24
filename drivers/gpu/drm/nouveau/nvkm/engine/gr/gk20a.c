<शैली गुरु>
/*
 * Copyright (c) 2014-2015, NVIDIA CORPORATION. All rights reserved.
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#समावेश "gf100.h"
#समावेश "ctxgf100.h"

#समावेश <core/firmware.h>
#समावेश <subdev/समयr.h>

#समावेश <nvअगर/class.h>

काष्ठा gk20a_fw_av
अणु
	u32 addr;
	u32 data;
पूर्ण;

अटल पूर्णांक
gk20a_gr_av_to_init(काष्ठा gf100_gr *gr, स्थिर अक्षर *path, स्थिर अक्षर *name,
		    पूर्णांक ver, काष्ठा gf100_gr_pack **ppack)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_blob blob;
	काष्ठा gf100_gr_init *init;
	काष्ठा gf100_gr_pack *pack;
	पूर्णांक nent;
	पूर्णांक ret;
	पूर्णांक i;

	ret = nvkm_firmware_load_blob(subdev, path, name, ver, &blob);
	अगर (ret)
		वापस ret;

	nent = (blob.size / माप(काष्ठा gk20a_fw_av));
	pack = vzalloc((माप(*pack) * 2) + (माप(*init) * (nent + 1)));
	अगर (!pack) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण

	init = (व्योम *)(pack + 2);
	pack[0].init = init;

	क्रम (i = 0; i < nent; i++) अणु
		काष्ठा gf100_gr_init *ent = &init[i];
		काष्ठा gk20a_fw_av *av = &((काष्ठा gk20a_fw_av *)blob.data)[i];

		ent->addr = av->addr;
		ent->data = av->data;
		ent->count = 1;
		ent->pitch = 1;
	पूर्ण

	*ppack = pack;

end:
	nvkm_blob_dtor(&blob);
	वापस ret;
पूर्ण

काष्ठा gk20a_fw_aiv
अणु
	u32 addr;
	u32 index;
	u32 data;
पूर्ण;

अटल पूर्णांक
gk20a_gr_aiv_to_init(काष्ठा gf100_gr *gr, स्थिर अक्षर *path, स्थिर अक्षर *name,
		     पूर्णांक ver, काष्ठा gf100_gr_pack **ppack)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_blob blob;
	काष्ठा gf100_gr_init *init;
	काष्ठा gf100_gr_pack *pack;
	पूर्णांक nent;
	पूर्णांक ret;
	पूर्णांक i;

	ret = nvkm_firmware_load_blob(subdev, path, name, ver, &blob);
	अगर (ret)
		वापस ret;

	nent = (blob.size / माप(काष्ठा gk20a_fw_aiv));
	pack = vzalloc((माप(*pack) * 2) + (माप(*init) * (nent + 1)));
	अगर (!pack) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण

	init = (व्योम *)(pack + 2);
	pack[0].init = init;

	क्रम (i = 0; i < nent; i++) अणु
		काष्ठा gf100_gr_init *ent = &init[i];
		काष्ठा gk20a_fw_aiv *av = &((काष्ठा gk20a_fw_aiv *)blob.data)[i];

		ent->addr = av->addr;
		ent->data = av->data;
		ent->count = 1;
		ent->pitch = 1;
	पूर्ण

	*ppack = pack;

end:
	nvkm_blob_dtor(&blob);
	वापस ret;
पूर्ण

अटल पूर्णांक
gk20a_gr_av_to_method(काष्ठा gf100_gr *gr, स्थिर अक्षर *path, स्थिर अक्षर *name,
		      पूर्णांक ver, काष्ठा gf100_gr_pack **ppack)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_blob blob;
	काष्ठा gf100_gr_init *init;
	काष्ठा gf100_gr_pack *pack;
	/* We करोn't suppose we will initialize more than 16 classes here... */
	अटल स्थिर अचिन्हित पूर्णांक max_classes = 16;
	u32 classidx = 0, prevclass = 0;
	पूर्णांक nent;
	पूर्णांक ret;
	पूर्णांक i;

	ret = nvkm_firmware_load_blob(subdev, path, name, ver, &blob);
	अगर (ret)
		वापस ret;

	nent = (blob.size / माप(काष्ठा gk20a_fw_av));

	pack = vzalloc((माप(*pack) * (max_classes + 1)) +
		       (माप(*init) * (nent + max_classes + 1)));
	अगर (!pack) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण

	init = (व्योम *)(pack + max_classes + 1);

	क्रम (i = 0; i < nent; i++, init++) अणु
		काष्ठा gk20a_fw_av *av = &((काष्ठा gk20a_fw_av *)blob.data)[i];
		u32 class = av->addr & 0xffff;
		u32 addr = (av->addr & 0xffff0000) >> 14;

		अगर (prevclass != class) अणु
			अगर (prevclass) /* Add terminator to the method list. */
				init++;
			pack[classidx].init = init;
			pack[classidx].type = class;
			prevclass = class;
			अगर (++classidx >= max_classes) अणु
				vमुक्त(pack);
				ret = -ENOSPC;
				जाओ end;
			पूर्ण
		पूर्ण

		init->addr = addr;
		init->data = av->data;
		init->count = 1;
		init->pitch = 1;
	पूर्ण

	*ppack = pack;

end:
	nvkm_blob_dtor(&blob);
	वापस ret;
पूर्ण

अटल पूर्णांक
gk20a_gr_रुको_mem_scrubbing(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;

	अगर (nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x40910c) & 0x00000006))
			अवरोध;
	) < 0) अणु
		nvkm_error(subdev, "FECS mem scrubbing timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x41a10c) & 0x00000006))
			अवरोध;
	) < 0) अणु
		nvkm_error(subdev, "GPCCS mem scrubbing timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
gk20a_gr_set_hww_esr_report_mask(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	nvkm_wr32(device, 0x419e44, 0x1ffffe);
	nvkm_wr32(device, 0x419e4c, 0x7f);
पूर्ण

पूर्णांक
gk20a_gr_init(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	पूर्णांक ret;

	/* Clear SCC RAM */
	nvkm_wr32(device, 0x40802c, 0x1);

	gf100_gr_mmio(gr, gr->sw_nonctx);

	ret = gk20a_gr_रुको_mem_scrubbing(gr);
	अगर (ret)
		वापस ret;

	ret = gf100_gr_रुको_idle(gr);
	अगर (ret)
		वापस ret;

	/* MMU debug buffer */
	अगर (gr->func->init_gpc_mmu)
		gr->func->init_gpc_mmu(gr);

	/* Set the PE as stream master */
	nvkm_mask(device, 0x503018, 0x1, 0x1);

	/* Zcull init */
	gr->func->init_zcull(gr);

	gr->func->init_rop_active_fbps(gr);

	/* Enable FIFO access */
	nvkm_wr32(device, 0x400500, 0x00010001);

	/* Enable पूर्णांकerrupts */
	nvkm_wr32(device, 0x400100, 0xffffffff);
	nvkm_wr32(device, 0x40013c, 0xffffffff);

	/* Enable FECS error पूर्णांकerrupts */
	nvkm_wr32(device, 0x409c24, 0x000f0000);

	/* Enable hardware warning exceptions */
	nvkm_wr32(device, 0x404000, 0xc0000000);
	nvkm_wr32(device, 0x404600, 0xc0000000);

	अगर (gr->func->set_hww_esr_report_mask)
		gr->func->set_hww_esr_report_mask(gr);

	/* Enable TPC exceptions per GPC */
	nvkm_wr32(device, 0x419d0c, 0x2);
	nvkm_wr32(device, 0x41ac94, (((1 << gr->tpc_total) - 1) & 0xff) << 16);

	/* Reset and enable all exceptions */
	nvkm_wr32(device, 0x400108, 0xffffffff);
	nvkm_wr32(device, 0x400138, 0xffffffff);
	nvkm_wr32(device, 0x400118, 0xffffffff);
	nvkm_wr32(device, 0x400130, 0xffffffff);
	nvkm_wr32(device, 0x40011c, 0xffffffff);
	nvkm_wr32(device, 0x400134, 0xffffffff);

	gf100_gr_zbc_init(gr);

	वापस gf100_gr_init_ctxctl(gr);
पूर्ण

अटल स्थिर काष्ठा gf100_gr_func
gk20a_gr = अणु
	.oneinit_tiles = gf100_gr_oneinit_tiles,
	.oneinit_sm_id = gf100_gr_oneinit_sm_id,
	.init = gk20a_gr_init,
	.init_zcull = gf117_gr_init_zcull,
	.init_rop_active_fbps = gk104_gr_init_rop_active_fbps,
	.trap_mp = gf100_gr_trap_mp,
	.set_hww_esr_report_mask = gk20a_gr_set_hww_esr_report_mask,
	.rops = gf100_gr_rops,
	.ppc_nr = 1,
	.grctx = &gk20a_grctx,
	.zbc = &gf100_gr_zbc,
	.sclass = अणु
		अणु -1, -1, FERMI_TWOD_A पूर्ण,
		अणु -1, -1, KEPLER_INLINE_TO_MEMORY_A पूर्ण,
		अणु -1, -1, KEPLER_C, &gf100_fermi पूर्ण,
		अणु -1, -1, KEPLER_COMPUTE_A पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
gk20a_gr_load_sw(काष्ठा gf100_gr *gr, स्थिर अक्षर *path, पूर्णांक ver)
अणु
	अगर (gk20a_gr_av_to_init(gr, path, "sw_nonctx", ver, &gr->sw_nonctx) ||
	    gk20a_gr_aiv_to_init(gr, path, "sw_ctx", ver, &gr->sw_ctx) ||
	    gk20a_gr_av_to_init(gr, path, "sw_bundle_init", ver, &gr->bundle) ||
	    gk20a_gr_av_to_method(gr, path, "sw_method_init", ver, &gr->method))
		वापस -ENOENT;

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_124_SOC) || IS_ENABLED(CONFIG_ARCH_TEGRA_132_SOC)
MODULE_FIRMWARE("nvidia/gk20a/fecs_data.bin");
MODULE_FIRMWARE("nvidia/gk20a/fecs_inst.bin");
MODULE_FIRMWARE("nvidia/gk20a/gpccs_data.bin");
MODULE_FIRMWARE("nvidia/gk20a/gpccs_inst.bin");
MODULE_FIRMWARE("nvidia/gk20a/sw_bundle_init.bin");
MODULE_FIRMWARE("nvidia/gk20a/sw_ctx.bin");
MODULE_FIRMWARE("nvidia/gk20a/sw_method_init.bin");
MODULE_FIRMWARE("nvidia/gk20a/sw_nonctx.bin");
#पूर्ण_अगर

अटल पूर्णांक
gk20a_gr_load(काष्ठा gf100_gr *gr, पूर्णांक ver, स्थिर काष्ठा gf100_gr_fwअगर *fwअगर)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;

	अगर (nvkm_firmware_load_blob(subdev, "", "fecs_inst", ver,
				    &gr->fecs.inst) ||
	    nvkm_firmware_load_blob(subdev, "", "fecs_data", ver,
				    &gr->fecs.data) ||
	    nvkm_firmware_load_blob(subdev, "", "gpccs_inst", ver,
				    &gr->gpccs.inst) ||
	    nvkm_firmware_load_blob(subdev, "", "gpccs_data", ver,
				    &gr->gpccs.data))
		वापस -ENOENT;

	gr->firmware = true;

	वापस gk20a_gr_load_sw(gr, "", ver);
पूर्ण

अटल स्थिर काष्ठा gf100_gr_fwअगर
gk20a_gr_fwअगर[] = अणु
	अणु 0, gk20a_gr_load, &gk20a_gr पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gk20a_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस gf100_gr_new_(gk20a_gr_fwअगर, device, type, inst, pgr);
पूर्ण
