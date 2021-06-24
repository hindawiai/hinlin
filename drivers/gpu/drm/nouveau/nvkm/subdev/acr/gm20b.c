<शैली गुरु>
/*
 * Copyright 2019 Red Hat Inc.
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
#समावेश "priv.h"

#समावेश <core/firmware.h>
#समावेश <core/memory.h>
#समावेश <subdev/mmu.h>
#समावेश <subdev/pmu.h>

#समावेश <nvfw/acr.h>
#समावेश <nvfw/flcn.h>

पूर्णांक
gm20b_acr_wpr_alloc(काष्ठा nvkm_acr *acr, u32 wpr_size)
अणु
	काष्ठा nvkm_subdev *subdev = &acr->subdev;

	acr->func->wpr_check(acr, &acr->wpr_start, &acr->wpr_end);

	अगर ((acr->wpr_end - acr->wpr_start) < wpr_size) अणु
		nvkm_error(subdev, "WPR image too big for WPR!\n");
		वापस -ENOSPC;
	पूर्ण

	वापस nvkm_memory_new(subdev->device, NVKM_MEM_TARGET_INST,
			       wpr_size, 0, true, &acr->wpr);
पूर्ण

अटल व्योम
gm20b_acr_load_bld(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_hsf *hsf)
अणु
	काष्ठा flcn_bl_dmem_desc hsdesc = अणु
		.ctx_dma = FALCON_DMAIDX_VIRT,
		.code_dma_base = hsf->vma->addr >> 8,
		.non_sec_code_off = hsf->non_sec_addr,
		.non_sec_code_size = hsf->non_sec_size,
		.sec_code_off = hsf->sec_addr,
		.sec_code_size = hsf->sec_size,
		.code_entry_poपूर्णांक = 0,
		.data_dma_base = (hsf->vma->addr + hsf->data_addr) >> 8,
		.data_size = hsf->data_size,
	पूर्ण;

	flcn_bl_dmem_desc_dump(&acr->subdev, &hsdesc);

	nvkm_falcon_load_dmem(hsf->falcon, &hsdesc, 0, माप(hsdesc), 0);
पूर्ण

अटल पूर्णांक
gm20b_acr_load_load(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_hsfw *hsfw)
अणु
	काष्ठा flcn_acr_desc *desc = (व्योम *)&hsfw->image[hsfw->data_addr];

	desc->ucode_blob_base = nvkm_memory_addr(acr->wpr);
	desc->ucode_blob_size = nvkm_memory_size(acr->wpr);
	flcn_acr_desc_dump(&acr->subdev, desc);

	वापस gm200_acr_hsfw_load(acr, hsfw, &acr->subdev.device->pmu->falcon);
पूर्ण

स्थिर काष्ठा nvkm_acr_hsf_func
gm20b_acr_load_0 = अणु
	.load = gm20b_acr_load_load,
	.boot = gm200_acr_load_boot,
	.bld = gm20b_acr_load_bld,
पूर्ण;

#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_210_SOC)
MODULE_FIRMWARE("nvidia/gm20b/acr/bl.bin");
MODULE_FIRMWARE("nvidia/gm20b/acr/ucode_load.bin");
#पूर्ण_अगर

अटल स्थिर काष्ठा nvkm_acr_hsf_fwअगर
gm20b_acr_load_fwअगर[] = अणु
	अणु 0, nvkm_acr_hsfw_load, &gm20b_acr_load_0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_acr_func
gm20b_acr = अणु
	.load = gm20b_acr_load_fwअगर,
	.wpr_parse = gm200_acr_wpr_parse,
	.wpr_layout = gm200_acr_wpr_layout,
	.wpr_alloc = gm20b_acr_wpr_alloc,
	.wpr_build = gm200_acr_wpr_build,
	.wpr_patch = gm200_acr_wpr_patch,
	.wpr_check = gm200_acr_wpr_check,
	.init = gm200_acr_init,
पूर्ण;

पूर्णांक
gm20b_acr_load(काष्ठा nvkm_acr *acr, पूर्णांक ver, स्थिर काष्ठा nvkm_acr_fwअगर *fwअगर)
अणु
	काष्ठा nvkm_subdev *subdev = &acr->subdev;
	स्थिर काष्ठा nvkm_acr_hsf_fwअगर *hsfwअगर;

	hsfwअगर = nvkm_firmware_load(subdev, fwअगर->func->load, "AcrLoad",
				    acr, "acr/bl", "acr/ucode_load", "load");
	अगर (IS_ERR(hsfwअगर))
		वापस PTR_ERR(hsfwअगर);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_acr_fwअगर
gm20b_acr_fwअगर[] = अणु
	अणु  0, gm20b_acr_load, &gm20b_acr पूर्ण,
	अणु -1, gm200_acr_nofw, &gm200_acr पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gm20b_acr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_acr **pacr)
अणु
	वापस nvkm_acr_new_(gm20b_acr_fwअगर, device, type, inst, pacr);
पूर्ण
