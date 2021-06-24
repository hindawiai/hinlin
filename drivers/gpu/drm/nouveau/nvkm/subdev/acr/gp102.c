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
#समावेश <engine/sec2.h>

#समावेश <nvfw/acr.h>
#समावेश <nvfw/flcn.h>

व्योम
gp102_acr_wpr_patch(काष्ठा nvkm_acr *acr, s64 adjust)
अणु
	काष्ठा wpr_header_v1 hdr;
	काष्ठा lsb_header_v1 lsb;
	काष्ठा nvkm_acr_lsfw *lsfw;
	u32 offset = 0;

	करो अणु
		nvkm_robj(acr->wpr, offset, &hdr, माप(hdr));
		wpr_header_v1_dump(&acr->subdev, &hdr);

		list_क्रम_each_entry(lsfw, &acr->lsfw, head) अणु
			अगर (lsfw->id != hdr.falcon_id)
				जारी;

			nvkm_robj(acr->wpr, hdr.lsb_offset, &lsb, माप(lsb));
			lsb_header_v1_dump(&acr->subdev, &lsb);

			lsfw->func->bld_patch(acr, lsb.tail.bl_data_off, adjust);
			अवरोध;
		पूर्ण

		offset += माप(hdr);
	पूर्ण जबतक (hdr.falcon_id != WPR_HEADER_V1_FALCON_ID_INVALID);
पूर्ण

पूर्णांक
gp102_acr_wpr_build_lsb(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_lsfw *lsfw)
अणु
	काष्ठा lsb_header_v1 hdr;

	अगर (WARN_ON(lsfw->sig->size != माप(hdr.signature)))
		वापस -EINVAL;

	स_नकल(&hdr.signature, lsfw->sig->data, lsfw->sig->size);
	gm200_acr_wpr_build_lsb_tail(lsfw, &hdr.tail);

	nvkm_wobj(acr->wpr, lsfw->offset.lsb, &hdr, माप(hdr));
	वापस 0;
पूर्ण

पूर्णांक
gp102_acr_wpr_build(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_lsf *rtos)
अणु
	काष्ठा nvkm_acr_lsfw *lsfw;
	u32 offset = 0;
	पूर्णांक ret;

	/* Fill per-LSF काष्ठाures. */
	list_क्रम_each_entry(lsfw, &acr->lsfw, head) अणु
		काष्ठा lsf_signature_v1 *sig = (व्योम *)lsfw->sig->data;
		काष्ठा wpr_header_v1 hdr = अणु
			.falcon_id = lsfw->id,
			.lsb_offset = lsfw->offset.lsb,
			.bootstrap_owner = NVKM_ACR_LSF_SEC2,
			.lazy_bootstrap = rtos && lsfw->id != rtos->id,
			.bin_version = sig->version,
			.status = WPR_HEADER_V1_STATUS_COPY,
		पूर्ण;

		/* Write WPR header. */
		nvkm_wobj(acr->wpr, offset, &hdr, माप(hdr));
		offset += माप(hdr);

		/* Write LSB header. */
		ret = gp102_acr_wpr_build_lsb(acr, lsfw);
		अगर (ret)
			वापस ret;

		/* Write ucode image. */
		nvkm_wobj(acr->wpr, lsfw->offset.img,
				    lsfw->img.data,
				    lsfw->img.size);

		/* Write bootloader data. */
		lsfw->func->bld_ग_लिखो(acr, lsfw->offset.bld, lsfw);
	पूर्ण

	/* Finalise WPR. */
	nvkm_wo32(acr->wpr, offset, WPR_HEADER_V1_FALCON_ID_INVALID);
	वापस 0;
पूर्ण

पूर्णांक
gp102_acr_wpr_alloc(काष्ठा nvkm_acr *acr, u32 wpr_size)
अणु
	पूर्णांक ret = nvkm_memory_new(acr->subdev.device, NVKM_MEM_TARGET_INST,
				  ALIGN(wpr_size, 0x40000) << 1, 0x40000, true,
				  &acr->wpr);
	अगर (ret)
		वापस ret;

	acr->shaकरोw_start = nvkm_memory_addr(acr->wpr);
	acr->wpr_start = acr->shaकरोw_start + (nvkm_memory_size(acr->wpr) >> 1);
	acr->wpr_end = acr->wpr_start + (nvkm_memory_size(acr->wpr) >> 1);
	वापस 0;
पूर्ण

u32
gp102_acr_wpr_layout(काष्ठा nvkm_acr *acr)
अणु
	काष्ठा nvkm_acr_lsfw *lsfw;
	u32 wpr = 0;

	wpr += 11 /* MAX_LSF */ * माप(काष्ठा wpr_header_v1);
	wpr  = ALIGN(wpr, 256);

	wpr += 0x100; /* Shared sub-WPR headers. */

	list_क्रम_each_entry(lsfw, &acr->lsfw, head) अणु
		wpr  = ALIGN(wpr, 256);
		lsfw->offset.lsb = wpr;
		wpr += माप(काष्ठा lsb_header_v1);

		wpr  = ALIGN(wpr, 4096);
		lsfw->offset.img = wpr;
		wpr += lsfw->img.size;

		wpr  = ALIGN(wpr, 256);
		lsfw->offset.bld = wpr;
		lsfw->bl_data_size = ALIGN(lsfw->func->bld_size, 256);
		wpr += lsfw->bl_data_size;
	पूर्ण

	वापस wpr;
पूर्ण

पूर्णांक
gp102_acr_wpr_parse(काष्ठा nvkm_acr *acr)
अणु
	स्थिर काष्ठा wpr_header_v1 *hdr = (व्योम *)acr->wpr_fw->data;

	जबतक (hdr->falcon_id != WPR_HEADER_V1_FALCON_ID_INVALID) अणु
		wpr_header_v1_dump(&acr->subdev, hdr);
		अगर (!nvkm_acr_lsfw_add(शून्य, acr, शून्य, (hdr++)->falcon_id))
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

MODULE_FIRMWARE("nvidia/gp102/acr/unload_bl.bin");
MODULE_FIRMWARE("nvidia/gp102/acr/ucode_unload.bin");

MODULE_FIRMWARE("nvidia/gp104/acr/unload_bl.bin");
MODULE_FIRMWARE("nvidia/gp104/acr/ucode_unload.bin");

MODULE_FIRMWARE("nvidia/gp106/acr/unload_bl.bin");
MODULE_FIRMWARE("nvidia/gp106/acr/ucode_unload.bin");

MODULE_FIRMWARE("nvidia/gp107/acr/unload_bl.bin");
MODULE_FIRMWARE("nvidia/gp107/acr/ucode_unload.bin");

अटल स्थिर काष्ठा nvkm_acr_hsf_fwअगर
gp102_acr_unload_fwअगर[] = अणु
	अणु 0, nvkm_acr_hsfw_load, &gm200_acr_unload_0 पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gp102_acr_load_load(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_hsfw *hsfw)
अणु
	काष्ठा flcn_acr_desc_v1 *desc = (व्योम *)&hsfw->image[hsfw->data_addr];

	desc->wpr_region_id = 1;
	desc->regions.no_regions = 2;
	desc->regions.region_props[0].start_addr = acr->wpr_start >> 8;
	desc->regions.region_props[0].end_addr = acr->wpr_end >> 8;
	desc->regions.region_props[0].region_id = 1;
	desc->regions.region_props[0].पढ़ो_mask = 0xf;
	desc->regions.region_props[0].ग_लिखो_mask = 0xc;
	desc->regions.region_props[0].client_mask = 0x2;
	desc->regions.region_props[0].shaकरोw_mem_start_addr =
		acr->shaकरोw_start >> 8;
	flcn_acr_desc_v1_dump(&acr->subdev, desc);

	वापस gm200_acr_hsfw_load(acr, hsfw,
				  &acr->subdev.device->sec2->falcon);
पूर्ण

अटल स्थिर काष्ठा nvkm_acr_hsf_func
gp102_acr_load_0 = अणु
	.load = gp102_acr_load_load,
	.boot = gm200_acr_load_boot,
	.bld = gm200_acr_hsfw_bld,
पूर्ण;

MODULE_FIRMWARE("nvidia/gp102/acr/bl.bin");
MODULE_FIRMWARE("nvidia/gp102/acr/ucode_load.bin");

MODULE_FIRMWARE("nvidia/gp104/acr/bl.bin");
MODULE_FIRMWARE("nvidia/gp104/acr/ucode_load.bin");

MODULE_FIRMWARE("nvidia/gp106/acr/bl.bin");
MODULE_FIRMWARE("nvidia/gp106/acr/ucode_load.bin");

MODULE_FIRMWARE("nvidia/gp107/acr/bl.bin");
MODULE_FIRMWARE("nvidia/gp107/acr/ucode_load.bin");

अटल स्थिर काष्ठा nvkm_acr_hsf_fwअगर
gp102_acr_load_fwअगर[] = अणु
	अणु 0, nvkm_acr_hsfw_load, &gp102_acr_load_0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_acr_func
gp102_acr = अणु
	.load = gp102_acr_load_fwअगर,
	.unload = gp102_acr_unload_fwअगर,
	.wpr_parse = gp102_acr_wpr_parse,
	.wpr_layout = gp102_acr_wpr_layout,
	.wpr_alloc = gp102_acr_wpr_alloc,
	.wpr_build = gp102_acr_wpr_build,
	.wpr_patch = gp102_acr_wpr_patch,
	.wpr_check = gm200_acr_wpr_check,
	.init = gm200_acr_init,
पूर्ण;

पूर्णांक
gp102_acr_load(काष्ठा nvkm_acr *acr, पूर्णांक ver, स्थिर काष्ठा nvkm_acr_fwअगर *fwअगर)
अणु
	काष्ठा nvkm_subdev *subdev = &acr->subdev;
	स्थिर काष्ठा nvkm_acr_hsf_fwअगर *hsfwअगर;

	hsfwअगर = nvkm_firmware_load(subdev, fwअगर->func->load, "AcrLoad",
				    acr, "acr/bl", "acr/ucode_load", "load");
	अगर (IS_ERR(hsfwअगर))
		वापस PTR_ERR(hsfwअगर);

	hsfwअगर = nvkm_firmware_load(subdev, fwअगर->func->unload, "AcrUnload",
				    acr, "acr/unload_bl", "acr/ucode_unload",
				    "unload");
	अगर (IS_ERR(hsfwअगर))
		वापस PTR_ERR(hsfwअगर);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_acr_fwअगर
gp102_acr_fwअगर[] = अणु
	अणु  0, gp102_acr_load, &gp102_acr पूर्ण,
	अणु -1, gm200_acr_nofw, &gm200_acr पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gp102_acr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_acr **pacr)
अणु
	वापस nvkm_acr_new_(gp102_acr_fwअगर, device, type, inst, pacr);
पूर्ण
