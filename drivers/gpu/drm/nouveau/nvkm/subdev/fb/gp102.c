<शैली गुरु>
/*
 * Copyright 2016 Red Hat Inc.
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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश "gf100.h"
#समावेश "ram.h"

#समावेश <core/firmware.h>
#समावेश <core/memory.h>
#समावेश <nvfw/fw.h>
#समावेश <nvfw/hs.h>
#समावेश <engine/nvdec.h>

पूर्णांक
gp102_fb_vpr_scrub(काष्ठा nvkm_fb *fb)
अणु
	काष्ठा nvkm_subdev *subdev = &fb->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_falcon *falcon = &device->nvdec[0]->falcon;
	काष्ठा nvkm_blob *blob = &fb->vpr_scrubber;
	स्थिर काष्ठा nvfw_bin_hdr *hsbin_hdr;
	स्थिर काष्ठा nvfw_hs_header *fw_hdr;
	स्थिर काष्ठा nvfw_hs_load_header *lhdr;
	व्योम *scrub_data;
	u32 patch_loc, patch_sig;
	पूर्णांक ret;

	nvkm_falcon_get(falcon, subdev);

	hsbin_hdr = nvfw_bin_hdr(subdev, blob->data);
	fw_hdr = nvfw_hs_header(subdev, blob->data + hsbin_hdr->header_offset);
	lhdr = nvfw_hs_load_header(subdev, blob->data + fw_hdr->hdr_offset);
	scrub_data = blob->data + hsbin_hdr->data_offset;

	patch_loc = *(u32 *)(blob->data + fw_hdr->patch_loc);
	patch_sig = *(u32 *)(blob->data + fw_hdr->patch_sig);
	अगर (falcon->debug) अणु
		स_नकल(scrub_data + patch_loc,
		       blob->data + fw_hdr->sig_dbg_offset + patch_sig,
		       fw_hdr->sig_dbg_size);
	पूर्ण अन्यथा अणु
		स_नकल(scrub_data + patch_loc,
		       blob->data + fw_hdr->sig_prod_offset + patch_sig,
		       fw_hdr->sig_prod_size);
	पूर्ण

	nvkm_falcon_reset(falcon);
	nvkm_falcon_bind_context(falcon, शून्य);

	nvkm_falcon_load_imem(falcon, scrub_data, lhdr->non_sec_code_off,
			      lhdr->non_sec_code_size,
			      lhdr->non_sec_code_off >> 8, 0, false);
	nvkm_falcon_load_imem(falcon, scrub_data + lhdr->apps[0],
			      ALIGN(lhdr->apps[0], 0x100),
			      lhdr->apps[1],
			      lhdr->apps[0] >> 8, 0, true);
	nvkm_falcon_load_dmem(falcon, scrub_data + lhdr->data_dma_base, 0,
			      lhdr->data_size, 0);

	nvkm_falcon_set_start_addr(falcon, 0x0);
	nvkm_falcon_start(falcon);

	ret = nvkm_falcon_रुको_क्रम_halt(falcon, 500);
	अगर (ret < 0) अणु
		ret = -ETIMEDOUT;
		जाओ end;
	पूर्ण

	/* put nvdec in clean state - without reset it will reमुख्य in HS mode */
	nvkm_falcon_reset(falcon);
end:
	nvkm_falcon_put(falcon, subdev);
	वापस ret;
पूर्ण

bool
gp102_fb_vpr_scrub_required(काष्ठा nvkm_fb *fb)
अणु
	काष्ठा nvkm_device *device = fb->subdev.device;
	nvkm_wr32(device, 0x100cd0, 0x2);
	वापस (nvkm_rd32(device, 0x100cd0) & 0x00000010) != 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_fb_func
gp102_fb = अणु
	.dtor = gf100_fb_dtor,
	.oneinit = gf100_fb_oneinit,
	.init = gp100_fb_init,
	.init_remapper = gp100_fb_init_remapper,
	.init_page = gm200_fb_init_page,
	.vpr.scrub_required = gp102_fb_vpr_scrub_required,
	.vpr.scrub = gp102_fb_vpr_scrub,
	.ram_new = gp100_ram_new,
पूर्ण;

पूर्णांक
gp102_fb_new_(स्थिर काष्ठा nvkm_fb_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fb **pfb)
अणु
	पूर्णांक ret = gf100_fb_new_(func, device, type, inst, pfb);
	अगर (ret)
		वापस ret;

	nvkm_firmware_load_blob(&(*pfb)->subdev, "nvdec/scrubber", "", 0,
				&(*pfb)->vpr_scrubber);
	वापस 0;
पूर्ण

पूर्णांक
gp102_fb_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fb **pfb)
अणु
	वापस gp102_fb_new_(&gp102_fb, device, type, inst, pfb);
पूर्ण

MODULE_FIRMWARE("nvidia/gp102/nvdec/scrubber.bin");
MODULE_FIRMWARE("nvidia/gp104/nvdec/scrubber.bin");
MODULE_FIRMWARE("nvidia/gp106/nvdec/scrubber.bin");
MODULE_FIRMWARE("nvidia/gp107/nvdec/scrubber.bin");
MODULE_FIRMWARE("nvidia/gp108/nvdec/scrubber.bin");
