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

#समावेश <subdev/mmu.h>

#समावेश <nvfw/flcn.h>

व्योम
gp108_acr_hsfw_bld(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_hsf *hsf)
अणु
	काष्ठा flcn_bl_dmem_desc_v2 hsdesc = अणु
		.ctx_dma = FALCON_DMAIDX_VIRT,
		.code_dma_base = hsf->vma->addr,
		.non_sec_code_off = hsf->non_sec_addr,
		.non_sec_code_size = hsf->non_sec_size,
		.sec_code_off = hsf->sec_addr,
		.sec_code_size = hsf->sec_size,
		.code_entry_poपूर्णांक = 0,
		.data_dma_base = hsf->vma->addr + hsf->data_addr,
		.data_size = hsf->data_size,
		.argc = 0,
		.argv = 0,
	पूर्ण;

	flcn_bl_dmem_desc_v2_dump(&acr->subdev, &hsdesc);

	nvkm_falcon_load_dmem(hsf->falcon, &hsdesc, 0, माप(hsdesc), 0);
पूर्ण

स्थिर काष्ठा nvkm_acr_hsf_func
gp108_acr_unload_0 = अणु
	.load = gm200_acr_unload_load,
	.boot = gm200_acr_unload_boot,
	.bld = gp108_acr_hsfw_bld,
पूर्ण;

MODULE_FIRMWARE("nvidia/gp108/acr/unload_bl.bin");
MODULE_FIRMWARE("nvidia/gp108/acr/ucode_unload.bin");

MODULE_FIRMWARE("nvidia/gv100/acr/unload_bl.bin");
MODULE_FIRMWARE("nvidia/gv100/acr/ucode_unload.bin");

अटल स्थिर काष्ठा nvkm_acr_hsf_fwअगर
gp108_acr_unload_fwअगर[] = अणु
	अणु 0, nvkm_acr_hsfw_load, &gp108_acr_unload_0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_acr_hsf_func
gp108_acr_load_0 = अणु
	.load = gp102_acr_load_load,
	.boot = gm200_acr_load_boot,
	.bld = gp108_acr_hsfw_bld,
पूर्ण;

MODULE_FIRMWARE("nvidia/gp108/acr/bl.bin");
MODULE_FIRMWARE("nvidia/gp108/acr/ucode_load.bin");

MODULE_FIRMWARE("nvidia/gv100/acr/bl.bin");
MODULE_FIRMWARE("nvidia/gv100/acr/ucode_load.bin");

अटल स्थिर काष्ठा nvkm_acr_hsf_fwअगर
gp108_acr_load_fwअगर[] = अणु
	अणु 0, nvkm_acr_hsfw_load, &gp108_acr_load_0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_acr_func
gp108_acr = अणु
	.load = gp108_acr_load_fwअगर,
	.unload = gp108_acr_unload_fwअगर,
	.wpr_parse = gp102_acr_wpr_parse,
	.wpr_layout = gp102_acr_wpr_layout,
	.wpr_alloc = gp102_acr_wpr_alloc,
	.wpr_build = gp102_acr_wpr_build,
	.wpr_patch = gp102_acr_wpr_patch,
	.wpr_check = gm200_acr_wpr_check,
	.init = gm200_acr_init,
पूर्ण;

अटल स्थिर काष्ठा nvkm_acr_fwअगर
gp108_acr_fwअगर[] = अणु
	अणु  0, gp102_acr_load, &gp108_acr पूर्ण,
	अणु -1, gm200_acr_nofw, &gm200_acr पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gp108_acr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_acr **pacr)
अणु
	वापस nvkm_acr_new_(gp108_acr_fwअगर, device, type, inst, pacr);
पूर्ण
