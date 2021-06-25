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

#समावेश <core/falcon.h>
#समावेश <core/firmware.h>
#समावेश <core/memory.h>
#समावेश <subdev/mc.h>
#समावेश <subdev/mmu.h>
#समावेश <subdev/pmu.h>
#समावेश <subdev/समयr.h>

#समावेश <nvfw/acr.h>
#समावेश <nvfw/flcn.h>

स्थिर काष्ठा nvkm_acr_func
gm200_acr = अणु
पूर्ण;

पूर्णांक
gm200_acr_nofw(काष्ठा nvkm_acr *acr, पूर्णांक ver, स्थिर काष्ठा nvkm_acr_fwअगर *fwअगर)
अणु
	nvkm_warn(&acr->subdev, "firmware unavailable\n");
	वापस 0;
पूर्ण

पूर्णांक
gm200_acr_init(काष्ठा nvkm_acr *acr)
अणु
	वापस nvkm_acr_hsf_boot(acr, "load");
पूर्ण

व्योम
gm200_acr_wpr_check(काष्ठा nvkm_acr *acr, u64 *start, u64 *limit)
अणु
	काष्ठा nvkm_device *device = acr->subdev.device;

	nvkm_wr32(device, 0x100cd4, 2);
	*start = (u64)(nvkm_rd32(device, 0x100cd4) & 0xffffff00) << 8;
	nvkm_wr32(device, 0x100cd4, 3);
	*limit = (u64)(nvkm_rd32(device, 0x100cd4) & 0xffffff00) << 8;
	*limit = *limit + 0x20000;
पूर्ण

व्योम
gm200_acr_wpr_patch(काष्ठा nvkm_acr *acr, s64 adjust)
अणु
	काष्ठा nvkm_subdev *subdev = &acr->subdev;
	काष्ठा wpr_header hdr;
	काष्ठा lsb_header lsb;
	काष्ठा nvkm_acr_lsf *lsfw;
	u32 offset = 0;

	करो अणु
		nvkm_robj(acr->wpr, offset, &hdr, माप(hdr));
		wpr_header_dump(subdev, &hdr);

		list_क्रम_each_entry(lsfw, &acr->lsfw, head) अणु
			अगर (lsfw->id != hdr.falcon_id)
				जारी;

			nvkm_robj(acr->wpr, hdr.lsb_offset, &lsb, माप(lsb));
			lsb_header_dump(subdev, &lsb);

			lsfw->func->bld_patch(acr, lsb.tail.bl_data_off, adjust);
			अवरोध;
		पूर्ण
		offset += माप(hdr);
	पूर्ण जबतक (hdr.falcon_id != WPR_HEADER_V0_FALCON_ID_INVALID);
पूर्ण

व्योम
gm200_acr_wpr_build_lsb_tail(काष्ठा nvkm_acr_lsfw *lsfw,
			     काष्ठा lsb_header_tail *hdr)
अणु
	hdr->ucode_off = lsfw->offset.img;
	hdr->ucode_size = lsfw->ucode_size;
	hdr->data_size = lsfw->data_size;
	hdr->bl_code_size = lsfw->bootloader_size;
	hdr->bl_imem_off = lsfw->bootloader_imem_offset;
	hdr->bl_data_off = lsfw->offset.bld;
	hdr->bl_data_size = lsfw->bl_data_size;
	hdr->app_code_off = lsfw->app_start_offset +
			   lsfw->app_resident_code_offset;
	hdr->app_code_size = lsfw->app_resident_code_size;
	hdr->app_data_off = lsfw->app_start_offset +
			   lsfw->app_resident_data_offset;
	hdr->app_data_size = lsfw->app_resident_data_size;
	hdr->flags = lsfw->func->flags;
पूर्ण

अटल पूर्णांक
gm200_acr_wpr_build_lsb(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_lsfw *lsfw)
अणु
	काष्ठा lsb_header hdr;

	अगर (WARN_ON(lsfw->sig->size != माप(hdr.signature)))
		वापस -EINVAL;

	स_नकल(&hdr.signature, lsfw->sig->data, lsfw->sig->size);
	gm200_acr_wpr_build_lsb_tail(lsfw, &hdr.tail);

	nvkm_wobj(acr->wpr, lsfw->offset.lsb, &hdr, माप(hdr));
	वापस 0;
पूर्ण

पूर्णांक
gm200_acr_wpr_build(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_lsf *rtos)
अणु
	काष्ठा nvkm_acr_lsfw *lsfw;
	u32 offset = 0;
	पूर्णांक ret;

	/* Fill per-LSF काष्ठाures. */
	list_क्रम_each_entry(lsfw, &acr->lsfw, head) अणु
		काष्ठा wpr_header hdr = अणु
			.falcon_id = lsfw->id,
			.lsb_offset = lsfw->offset.lsb,
			.bootstrap_owner = NVKM_ACR_LSF_PMU,
			.lazy_bootstrap = rtos && lsfw->id != rtos->id,
			.status = WPR_HEADER_V0_STATUS_COPY,
		पूर्ण;

		/* Write WPR header. */
		nvkm_wobj(acr->wpr, offset, &hdr, माप(hdr));
		offset += माप(hdr);

		/* Write LSB header. */
		ret = gm200_acr_wpr_build_lsb(acr, lsfw);
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
	nvkm_wo32(acr->wpr, offset, WPR_HEADER_V0_FALCON_ID_INVALID);
	वापस 0;
पूर्ण

अटल पूर्णांक
gm200_acr_wpr_alloc(काष्ठा nvkm_acr *acr, u32 wpr_size)
अणु
	पूर्णांक ret = nvkm_memory_new(acr->subdev.device, NVKM_MEM_TARGET_INST,
				  ALIGN(wpr_size, 0x40000), 0x40000, true,
				  &acr->wpr);
	अगर (ret)
		वापस ret;

	acr->wpr_start = nvkm_memory_addr(acr->wpr);
	acr->wpr_end = acr->wpr_start + nvkm_memory_size(acr->wpr);
	वापस 0;
पूर्ण

u32
gm200_acr_wpr_layout(काष्ठा nvkm_acr *acr)
अणु
	काष्ठा nvkm_acr_lsfw *lsfw;
	u32 wpr = 0;

	wpr += 11 /* MAX_LSF */ * माप(काष्ठा wpr_header);

	list_क्रम_each_entry(lsfw, &acr->lsfw, head) अणु
		wpr  = ALIGN(wpr, 256);
		lsfw->offset.lsb = wpr;
		wpr += माप(काष्ठा lsb_header);

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
gm200_acr_wpr_parse(काष्ठा nvkm_acr *acr)
अणु
	स्थिर काष्ठा wpr_header *hdr = (व्योम *)acr->wpr_fw->data;

	जबतक (hdr->falcon_id != WPR_HEADER_V0_FALCON_ID_INVALID) अणु
		wpr_header_dump(&acr->subdev, hdr);
		अगर (!nvkm_acr_lsfw_add(शून्य, acr, शून्य, (hdr++)->falcon_id))
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम
gm200_acr_hsfw_bld(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_hsf *hsf)
अणु
	काष्ठा flcn_bl_dmem_desc_v1 hsdesc = अणु
		.ctx_dma = FALCON_DMAIDX_VIRT,
		.code_dma_base = hsf->vma->addr,
		.non_sec_code_off = hsf->non_sec_addr,
		.non_sec_code_size = hsf->non_sec_size,
		.sec_code_off = hsf->sec_addr,
		.sec_code_size = hsf->sec_size,
		.code_entry_poपूर्णांक = 0,
		.data_dma_base = hsf->vma->addr + hsf->data_addr,
		.data_size = hsf->data_size,
	पूर्ण;

	flcn_bl_dmem_desc_v1_dump(&acr->subdev, &hsdesc);

	nvkm_falcon_load_dmem(hsf->falcon, &hsdesc, 0, माप(hsdesc), 0);
पूर्ण

पूर्णांक
gm200_acr_hsfw_boot(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_hsf *hsf,
		    u32 पूर्णांकr_clear, u32 mbox0_ok)
अणु
	काष्ठा nvkm_subdev *subdev = &acr->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_falcon *falcon = hsf->falcon;
	u32 mbox0, mbox1;
	पूर्णांक ret;

	/* Reset falcon. */
	nvkm_falcon_reset(falcon);
	nvkm_falcon_bind_context(falcon, acr->inst);

	/* Load bootloader पूर्णांकo IMEM. */
	nvkm_falcon_load_imem(falcon, hsf->imem,
				      falcon->code.limit - hsf->imem_size,
				      hsf->imem_size,
				      hsf->imem_tag,
				      0, false);

	/* Load bootloader data पूर्णांकo DMEM. */
	hsf->func->bld(acr, hsf);

	/* Boot the falcon. */
	nvkm_mc_पूर्णांकr_mask(device, falcon->owner->type, falcon->owner->inst, false);

	nvkm_falcon_wr32(falcon, 0x040, 0xdeada5a5);
	nvkm_falcon_set_start_addr(falcon, hsf->imem_tag << 8);
	nvkm_falcon_start(falcon);
	ret = nvkm_falcon_रुको_क्रम_halt(falcon, 100);
	अगर (ret)
		वापस ret;

	/* Check क्रम successful completion. */
	mbox0 = nvkm_falcon_rd32(falcon, 0x040);
	mbox1 = nvkm_falcon_rd32(falcon, 0x044);
	nvkm_debug(subdev, "mailbox %08x %08x\n", mbox0, mbox1);
	अगर (mbox0 && mbox0 != mbox0_ok)
		वापस -EIO;

	nvkm_falcon_clear_पूर्णांकerrupt(falcon, पूर्णांकr_clear);
	nvkm_mc_पूर्णांकr_mask(device, falcon->owner->type, falcon->owner->inst, true);
	वापस ret;
पूर्ण

पूर्णांक
gm200_acr_hsfw_load(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_hsfw *hsfw,
		    काष्ठा nvkm_falcon *falcon)
अणु
	काष्ठा nvkm_subdev *subdev = &acr->subdev;
	काष्ठा nvkm_acr_hsf *hsf;
	पूर्णांक ret;

	/* Patch the appropriate signature (production/debug) पूर्णांकo the FW
	 * image, as determined by the mode the falcon is in.
	 */
	ret = nvkm_falcon_get(falcon, subdev);
	अगर (ret)
		वापस ret;

	अगर (hsfw->sig.patch_loc) अणु
		अगर (!falcon->debug) अणु
			nvkm_debug(subdev, "patching production signature\n");
			स_नकल(hsfw->image + hsfw->sig.patch_loc,
			       hsfw->sig.prod.data,
			       hsfw->sig.prod.size);
		पूर्ण अन्यथा अणु
			nvkm_debug(subdev, "patching debug signature\n");
			स_नकल(hsfw->image + hsfw->sig.patch_loc,
			       hsfw->sig.dbg.data,
			       hsfw->sig.dbg.size);
		पूर्ण
	पूर्ण

	nvkm_falcon_put(falcon, subdev);

	अगर (!(hsf = kzalloc(माप(*hsf), GFP_KERNEL)))
		वापस -ENOMEM;
	hsf->func = hsfw->func;
	hsf->name = hsfw->name;
	list_add_tail(&hsf->head, &acr->hsf);

	hsf->imem_size = hsfw->imem_size;
	hsf->imem_tag = hsfw->imem_tag;
	hsf->imem = kmemdup(hsfw->imem, hsfw->imem_size, GFP_KERNEL);
	अगर (!hsf->imem)
		वापस -ENOMEM;

	hsf->non_sec_addr = hsfw->non_sec_addr;
	hsf->non_sec_size = hsfw->non_sec_size;
	hsf->sec_addr = hsfw->sec_addr;
	hsf->sec_size = hsfw->sec_size;
	hsf->data_addr = hsfw->data_addr;
	hsf->data_size = hsfw->data_size;

	/* Make the FW image accessible to the HS bootloader. */
	ret = nvkm_memory_new(subdev->device, NVKM_MEM_TARGET_INST,
			      hsfw->image_size, 0x1000, false, &hsf->ucode);
	अगर (ret)
		वापस ret;

	nvkm_kmap(hsf->ucode);
	nvkm_wobj(hsf->ucode, 0, hsfw->image, hsfw->image_size);
	nvkm_करोne(hsf->ucode);

	ret = nvkm_vmm_get(acr->vmm, 12, nvkm_memory_size(hsf->ucode),
			   &hsf->vma);
	अगर (ret)
		वापस ret;

	ret = nvkm_memory_map(hsf->ucode, 0, acr->vmm, hsf->vma, शून्य, 0);
	अगर (ret)
		वापस ret;

	hsf->falcon = falcon;
	वापस 0;
पूर्ण

पूर्णांक
gm200_acr_unload_boot(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_hsf *hsf)
अणु
	वापस gm200_acr_hsfw_boot(acr, hsf, 0, 0x1d);
पूर्ण

पूर्णांक
gm200_acr_unload_load(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_hsfw *hsfw)
अणु
	वापस gm200_acr_hsfw_load(acr, hsfw, &acr->subdev.device->pmu->falcon);
पूर्ण

स्थिर काष्ठा nvkm_acr_hsf_func
gm200_acr_unload_0 = अणु
	.load = gm200_acr_unload_load,
	.boot = gm200_acr_unload_boot,
	.bld = gm200_acr_hsfw_bld,
पूर्ण;

MODULE_FIRMWARE("nvidia/gm200/acr/ucode_unload.bin");
MODULE_FIRMWARE("nvidia/gm204/acr/ucode_unload.bin");
MODULE_FIRMWARE("nvidia/gm206/acr/ucode_unload.bin");
MODULE_FIRMWARE("nvidia/gp100/acr/ucode_unload.bin");

अटल स्थिर काष्ठा nvkm_acr_hsf_fwअगर
gm200_acr_unload_fwअगर[] = अणु
	अणु 0, nvkm_acr_hsfw_load, &gm200_acr_unload_0 पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gm200_acr_load_boot(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_hsf *hsf)
अणु
	वापस gm200_acr_hsfw_boot(acr, hsf, 0x10, 0);
पूर्ण

अटल पूर्णांक
gm200_acr_load_load(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_hsfw *hsfw)
अणु
	काष्ठा flcn_acr_desc *desc = (व्योम *)&hsfw->image[hsfw->data_addr];

	desc->wpr_region_id = 1;
	desc->regions.no_regions = 2;
	desc->regions.region_props[0].start_addr = acr->wpr_start >> 8;
	desc->regions.region_props[0].end_addr = acr->wpr_end >> 8;
	desc->regions.region_props[0].region_id = 1;
	desc->regions.region_props[0].पढ़ो_mask = 0xf;
	desc->regions.region_props[0].ग_लिखो_mask = 0xc;
	desc->regions.region_props[0].client_mask = 0x2;
	flcn_acr_desc_dump(&acr->subdev, desc);

	वापस gm200_acr_hsfw_load(acr, hsfw, &acr->subdev.device->pmu->falcon);
पूर्ण

अटल स्थिर काष्ठा nvkm_acr_hsf_func
gm200_acr_load_0 = अणु
	.load = gm200_acr_load_load,
	.boot = gm200_acr_load_boot,
	.bld = gm200_acr_hsfw_bld,
पूर्ण;

MODULE_FIRMWARE("nvidia/gm200/acr/bl.bin");
MODULE_FIRMWARE("nvidia/gm200/acr/ucode_load.bin");

MODULE_FIRMWARE("nvidia/gm204/acr/bl.bin");
MODULE_FIRMWARE("nvidia/gm204/acr/ucode_load.bin");

MODULE_FIRMWARE("nvidia/gm206/acr/bl.bin");
MODULE_FIRMWARE("nvidia/gm206/acr/ucode_load.bin");

MODULE_FIRMWARE("nvidia/gp100/acr/bl.bin");
MODULE_FIRMWARE("nvidia/gp100/acr/ucode_load.bin");

अटल स्थिर काष्ठा nvkm_acr_hsf_fwअगर
gm200_acr_load_fwअगर[] = अणु
	अणु 0, nvkm_acr_hsfw_load, &gm200_acr_load_0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_acr_func
gm200_acr_0 = अणु
	.load = gm200_acr_load_fwअगर,
	.unload = gm200_acr_unload_fwअगर,
	.wpr_parse = gm200_acr_wpr_parse,
	.wpr_layout = gm200_acr_wpr_layout,
	.wpr_alloc = gm200_acr_wpr_alloc,
	.wpr_build = gm200_acr_wpr_build,
	.wpr_patch = gm200_acr_wpr_patch,
	.wpr_check = gm200_acr_wpr_check,
	.init = gm200_acr_init,
	.bootstrap_falcons = BIT_ULL(NVKM_ACR_LSF_FECS) |
			     BIT_ULL(NVKM_ACR_LSF_GPCCS),
पूर्ण;

अटल पूर्णांक
gm200_acr_load(काष्ठा nvkm_acr *acr, पूर्णांक ver, स्थिर काष्ठा nvkm_acr_fwअगर *fwअगर)
अणु
	काष्ठा nvkm_subdev *subdev = &acr->subdev;
	स्थिर काष्ठा nvkm_acr_hsf_fwअगर *hsfwअगर;

	hsfwअगर = nvkm_firmware_load(subdev, fwअगर->func->load, "AcrLoad",
				    acr, "acr/bl", "acr/ucode_load", "load");
	अगर (IS_ERR(hsfwअगर))
		वापस PTR_ERR(hsfwअगर);

	hsfwअगर = nvkm_firmware_load(subdev, fwअगर->func->unload, "AcrUnload",
				    acr, "acr/bl", "acr/ucode_unload",
				    "unload");
	अगर (IS_ERR(hsfwअगर))
		वापस PTR_ERR(hsfwअगर);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_acr_fwअगर
gm200_acr_fwअगर[] = अणु
	अणु  0, gm200_acr_load, &gm200_acr_0 पूर्ण,
	अणु -1, gm200_acr_nofw, &gm200_acr पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gm200_acr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_acr **pacr)
अणु
	वापस nvkm_acr_new_(gm200_acr_fwअगर, device, type, inst, pacr);
पूर्ण
