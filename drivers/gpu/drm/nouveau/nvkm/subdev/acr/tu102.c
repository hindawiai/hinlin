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
#समावेश <subdev/gsp.h>
#समावेश <subdev/pmu.h>
#समावेश <engine/sec2.h>

#समावेश <nvfw/acr.h>

अटल पूर्णांक
tu102_acr_init(काष्ठा nvkm_acr *acr)
अणु
	पूर्णांक ret = nvkm_acr_hsf_boot(acr, "AHESASC");
	अगर (ret)
		वापस ret;

	वापस nvkm_acr_hsf_boot(acr, "ASB");
पूर्ण

अटल पूर्णांक
tu102_acr_wpr_build(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_lsf *rtos)
अणु
	काष्ठा nvkm_acr_lsfw *lsfw;
	u32 offset = 0;
	पूर्णांक ret;

	/*XXX: shared sub-WPR headers, fill terminator क्रम now. */
	nvkm_wo32(acr->wpr, 0x200, 0xffffffff);

	/* Fill per-LSF काष्ठाures. */
	list_क्रम_each_entry(lsfw, &acr->lsfw, head) अणु
		काष्ठा lsf_signature_v1 *sig = (व्योम *)lsfw->sig->data;
		काष्ठा wpr_header_v1 hdr = अणु
			.falcon_id = lsfw->id,
			.lsb_offset = lsfw->offset.lsb,
			.bootstrap_owner = NVKM_ACR_LSF_GSPLITE,
			.lazy_bootstrap = 1,
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

अटल पूर्णांक
tu102_acr_hsfw_boot(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_hsf *hsf)
अणु
	वापस gm200_acr_hsfw_boot(acr, hsf, 0, 0);
पूर्ण

अटल पूर्णांक
tu102_acr_hsfw_nofw(काष्ठा nvkm_acr *acr, स्थिर अक्षर *bl, स्थिर अक्षर *fw,
		    स्थिर अक्षर *name, पूर्णांक version,
		    स्थिर काष्ठा nvkm_acr_hsf_fwअगर *fwअगर)
अणु
	वापस 0;
पूर्ण

MODULE_FIRMWARE("nvidia/tu102/acr/unload_bl.bin");
MODULE_FIRMWARE("nvidia/tu102/acr/ucode_unload.bin");

MODULE_FIRMWARE("nvidia/tu104/acr/unload_bl.bin");
MODULE_FIRMWARE("nvidia/tu104/acr/ucode_unload.bin");

MODULE_FIRMWARE("nvidia/tu106/acr/unload_bl.bin");
MODULE_FIRMWARE("nvidia/tu106/acr/ucode_unload.bin");

MODULE_FIRMWARE("nvidia/tu116/acr/unload_bl.bin");
MODULE_FIRMWARE("nvidia/tu116/acr/ucode_unload.bin");

MODULE_FIRMWARE("nvidia/tu117/acr/unload_bl.bin");
MODULE_FIRMWARE("nvidia/tu117/acr/ucode_unload.bin");

अटल स्थिर काष्ठा nvkm_acr_hsf_fwअगर
tu102_acr_unload_fwअगर[] = अणु
	अणु  0, nvkm_acr_hsfw_load, &gp108_acr_unload_0 पूर्ण,
	अणु -1, tu102_acr_hsfw_nofw पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक
tu102_acr_asb_load(काष्ठा nvkm_acr *acr, काष्ठा nvkm_acr_hsfw *hsfw)
अणु
	वापस gm200_acr_hsfw_load(acr, hsfw, &acr->subdev.device->gsp->falcon);
पूर्ण

अटल स्थिर काष्ठा nvkm_acr_hsf_func
tu102_acr_asb_0 = अणु
	.load = tu102_acr_asb_load,
	.boot = tu102_acr_hsfw_boot,
	.bld = gp108_acr_hsfw_bld,
पूर्ण;

MODULE_FIRMWARE("nvidia/tu102/acr/ucode_asb.bin");
MODULE_FIRMWARE("nvidia/tu104/acr/ucode_asb.bin");
MODULE_FIRMWARE("nvidia/tu106/acr/ucode_asb.bin");
MODULE_FIRMWARE("nvidia/tu116/acr/ucode_asb.bin");
MODULE_FIRMWARE("nvidia/tu117/acr/ucode_asb.bin");

अटल स्थिर काष्ठा nvkm_acr_hsf_fwअगर
tu102_acr_asb_fwअगर[] = अणु
	अणु  0, nvkm_acr_hsfw_load, &tu102_acr_asb_0 पूर्ण,
	अणु -1, tu102_acr_hsfw_nofw पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_acr_hsf_func
tu102_acr_ahesasc_0 = अणु
	.load = gp102_acr_load_load,
	.boot = tu102_acr_hsfw_boot,
	.bld = gp108_acr_hsfw_bld,
पूर्ण;

MODULE_FIRMWARE("nvidia/tu102/acr/bl.bin");
MODULE_FIRMWARE("nvidia/tu102/acr/ucode_ahesasc.bin");

MODULE_FIRMWARE("nvidia/tu104/acr/bl.bin");
MODULE_FIRMWARE("nvidia/tu104/acr/ucode_ahesasc.bin");

MODULE_FIRMWARE("nvidia/tu106/acr/bl.bin");
MODULE_FIRMWARE("nvidia/tu106/acr/ucode_ahesasc.bin");

MODULE_FIRMWARE("nvidia/tu116/acr/bl.bin");
MODULE_FIRMWARE("nvidia/tu116/acr/ucode_ahesasc.bin");

MODULE_FIRMWARE("nvidia/tu117/acr/bl.bin");
MODULE_FIRMWARE("nvidia/tu117/acr/ucode_ahesasc.bin");

अटल स्थिर काष्ठा nvkm_acr_hsf_fwअगर
tu102_acr_ahesasc_fwअगर[] = अणु
	अणु  0, nvkm_acr_hsfw_load, &tu102_acr_ahesasc_0 पूर्ण,
	अणु -1, tu102_acr_hsfw_nofw पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_acr_func
tu102_acr = अणु
	.ahesasc = tu102_acr_ahesasc_fwअगर,
	.asb = tu102_acr_asb_fwअगर,
	.unload = tu102_acr_unload_fwअगर,
	.wpr_parse = gp102_acr_wpr_parse,
	.wpr_layout = gp102_acr_wpr_layout,
	.wpr_alloc = gp102_acr_wpr_alloc,
	.wpr_patch = gp102_acr_wpr_patch,
	.wpr_build = tu102_acr_wpr_build,
	.wpr_check = gm200_acr_wpr_check,
	.init = tu102_acr_init,
पूर्ण;

अटल पूर्णांक
tu102_acr_load(काष्ठा nvkm_acr *acr, पूर्णांक version,
	       स्थिर काष्ठा nvkm_acr_fwअगर *fwअगर)
अणु
	काष्ठा nvkm_subdev *subdev = &acr->subdev;
	स्थिर काष्ठा nvkm_acr_hsf_fwअगर *hsfwअगर;

	hsfwअगर = nvkm_firmware_load(subdev, fwअगर->func->ahesasc, "AcrAHESASC",
				    acr, "acr/bl", "acr/ucode_ahesasc",
				    "AHESASC");
	अगर (IS_ERR(hsfwअगर))
		वापस PTR_ERR(hsfwअगर);

	hsfwअगर = nvkm_firmware_load(subdev, fwअगर->func->asb, "AcrASB",
				    acr, "acr/bl", "acr/ucode_asb", "ASB");
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
tu102_acr_fwअगर[] = अणु
	अणु  0, tu102_acr_load, &tu102_acr पूर्ण,
	अणु -1, gm200_acr_nofw, &gm200_acr पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
tu102_acr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_acr **pacr)
अणु
	वापस nvkm_acr_new_(tu102_acr_fwअगर, device, type, inst, pacr);
पूर्ण
