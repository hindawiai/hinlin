<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
 * Author: Huang Rui
 *
 */

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_psp.h"
#समावेश "amdgpu_ucode.h"
#समावेश "soc15_common.h"
#समावेश "psp_v10_0.h"

#समावेश "mp/mp_10_0_offset.h"
#समावेश "gc/gc_9_1_offset.h"
#समावेश "sdma0/sdma0_4_1_offset.h"

MODULE_FIRMWARE("amdgpu/raven_asd.bin");
MODULE_FIRMWARE("amdgpu/picasso_asd.bin");
MODULE_FIRMWARE("amdgpu/raven2_asd.bin");
MODULE_FIRMWARE("amdgpu/picasso_ta.bin");
MODULE_FIRMWARE("amdgpu/raven2_ta.bin");
MODULE_FIRMWARE("amdgpu/raven_ta.bin");

अटल पूर्णांक psp_v10_0_init_microcode(काष्ठा psp_context *psp)
अणु
	काष्ठा amdgpu_device *adev = psp->adev;
	स्थिर अक्षर *chip_name;
	अक्षर fw_name[30];
	पूर्णांक err = 0;
	स्थिर काष्ठा ta_firmware_header_v1_0 *ta_hdr;
	DRM_DEBUG("\n");

	चयन (adev->asic_type) अणु
	हाल CHIP_RAVEN:
		अगर (adev->apu_flags & AMD_APU_IS_RAVEN2)
			chip_name = "raven2";
		अन्यथा अगर (adev->apu_flags & AMD_APU_IS_PICASSO)
			chip_name = "picasso";
		अन्यथा
			chip_name = "raven";
		अवरोध;
	शेष: BUG();
	पूर्ण

	err = psp_init_asd_microcode(psp, chip_name);
	अगर (err)
		जाओ out;

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_ta.bin", chip_name);
	err = request_firmware(&adev->psp.ta_fw, fw_name, adev->dev);
	अगर (err) अणु
		release_firmware(adev->psp.ta_fw);
		adev->psp.ta_fw = शून्य;
		dev_info(adev->dev,
			 "psp v10.0: Failed to load firmware \"%s\"\n",
			 fw_name);
	पूर्ण अन्यथा अणु
		err = amdgpu_ucode_validate(adev->psp.ta_fw);
		अगर (err)
			जाओ out2;

		ta_hdr = (स्थिर काष्ठा ta_firmware_header_v1_0 *)
				 adev->psp.ta_fw->data;
		adev->psp.ta_hdcp_ucode_version =
			le32_to_cpu(ta_hdr->ta_hdcp_ucode_version);
		adev->psp.ta_hdcp_ucode_size =
			le32_to_cpu(ta_hdr->ta_hdcp_size_bytes);
		adev->psp.ta_hdcp_start_addr =
			(uपूर्णांक8_t *)ta_hdr +
			le32_to_cpu(ta_hdr->header.ucode_array_offset_bytes);

		adev->psp.ta_dपंचांग_ucode_version =
			le32_to_cpu(ta_hdr->ta_dपंचांग_ucode_version);
		adev->psp.ta_dपंचांग_ucode_size =
			le32_to_cpu(ta_hdr->ta_dपंचांग_size_bytes);
		adev->psp.ta_dपंचांग_start_addr =
			(uपूर्णांक8_t *)adev->psp.ta_hdcp_start_addr +
			le32_to_cpu(ta_hdr->ta_dपंचांग_offset_bytes);

		adev->psp.ta_securedisplay_ucode_version =
			le32_to_cpu(ta_hdr->ta_securedisplay_ucode_version);
		adev->psp.ta_securedisplay_ucode_size =
			le32_to_cpu(ta_hdr->ta_securedisplay_size_bytes);
		adev->psp.ta_securedisplay_start_addr =
			(uपूर्णांक8_t *)adev->psp.ta_hdcp_start_addr +
			le32_to_cpu(ta_hdr->ta_securedisplay_offset_bytes);

		adev->psp.ta_fw_version = le32_to_cpu(ta_hdr->header.ucode_version);
	पूर्ण

	वापस 0;

out2:
	release_firmware(adev->psp.ta_fw);
	adev->psp.ta_fw = शून्य;
out:
	अगर (err) अणु
		dev_err(adev->dev,
			"psp v10.0: Failed to load firmware \"%s\"\n",
			fw_name);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक psp_v10_0_ring_init(काष्ठा psp_context *psp,
			       क्रमागत psp_ring_type ring_type)
अणु
	पूर्णांक ret = 0;
	काष्ठा psp_ring *ring;
	काष्ठा amdgpu_device *adev = psp->adev;

	ring = &psp->km_ring;

	ring->ring_type = ring_type;

	/* allocate 4k Page of Local Frame Buffer memory क्रम ring */
	ring->ring_size = 0x1000;
	ret = amdgpu_bo_create_kernel(adev, ring->ring_size, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &adev->firmware.rbuf,
				      &ring->ring_mem_mc_addr,
				      (व्योम **)&ring->ring_mem);
	अगर (ret) अणु
		ring->ring_size = 0;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक psp_v10_0_ring_create(काष्ठा psp_context *psp,
				 क्रमागत psp_ring_type ring_type)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक psp_ring_reg = 0;
	काष्ठा psp_ring *ring = &psp->km_ring;
	काष्ठा amdgpu_device *adev = psp->adev;

	/* Write low address of the ring to C2PMSG_69 */
	psp_ring_reg = lower_32_bits(ring->ring_mem_mc_addr);
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_69, psp_ring_reg);
	/* Write high address of the ring to C2PMSG_70 */
	psp_ring_reg = upper_32_bits(ring->ring_mem_mc_addr);
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_70, psp_ring_reg);
	/* Write size of ring to C2PMSG_71 */
	psp_ring_reg = ring->ring_size;
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_71, psp_ring_reg);
	/* Write the ring initialization command to C2PMSG_64 */
	psp_ring_reg = ring_type;
	psp_ring_reg = psp_ring_reg << 16;
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_64, psp_ring_reg);

	/* There might be handshake issue with hardware which needs delay */
	mdelay(20);

	/* Wait क्रम response flag (bit 31) in C2PMSG_64 */
	ret = psp_रुको_क्रम(psp, SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
			   0x80000000, 0x8000FFFF, false);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_v10_0_ring_stop(काष्ठा psp_context *psp,
			       क्रमागत psp_ring_type ring_type)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक psp_ring_reg = 0;
	काष्ठा amdgpu_device *adev = psp->adev;

	/* Write the ring destroy command to C2PMSG_64 */
	psp_ring_reg = 3 << 16;
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_64, psp_ring_reg);

	/* There might be handshake issue with hardware which needs delay */
	mdelay(20);

	/* Wait क्रम response flag (bit 31) in C2PMSG_64 */
	ret = psp_रुको_क्रम(psp, SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
			   0x80000000, 0x80000000, false);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_v10_0_ring_destroy(काष्ठा psp_context *psp,
				  क्रमागत psp_ring_type ring_type)
अणु
	पूर्णांक ret = 0;
	काष्ठा psp_ring *ring = &psp->km_ring;
	काष्ठा amdgpu_device *adev = psp->adev;

	ret = psp_v10_0_ring_stop(psp, ring_type);
	अगर (ret)
		DRM_ERROR("Fail to stop psp ring\n");

	amdgpu_bo_मुक्त_kernel(&adev->firmware.rbuf,
			      &ring->ring_mem_mc_addr,
			      (व्योम **)&ring->ring_mem);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_v10_0_mode1_reset(काष्ठा psp_context *psp)
अणु
	DRM_INFO("psp mode 1 reset not supported now! \n");
	वापस -EINVAL;
पूर्ण

अटल uपूर्णांक32_t psp_v10_0_ring_get_wptr(काष्ठा psp_context *psp)
अणु
	काष्ठा amdgpu_device *adev = psp->adev;

	वापस RREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_67);
पूर्ण

अटल व्योम psp_v10_0_ring_set_wptr(काष्ठा psp_context *psp, uपूर्णांक32_t value)
अणु
	काष्ठा amdgpu_device *adev = psp->adev;

	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_67, value);
पूर्ण

अटल स्थिर काष्ठा psp_funcs psp_v10_0_funcs = अणु
	.init_microcode = psp_v10_0_init_microcode,
	.ring_init = psp_v10_0_ring_init,
	.ring_create = psp_v10_0_ring_create,
	.ring_stop = psp_v10_0_ring_stop,
	.ring_destroy = psp_v10_0_ring_destroy,
	.mode1_reset = psp_v10_0_mode1_reset,
	.ring_get_wptr = psp_v10_0_ring_get_wptr,
	.ring_set_wptr = psp_v10_0_ring_set_wptr,
पूर्ण;

व्योम psp_v10_0_set_psp_funcs(काष्ठा psp_context *psp)
अणु
	psp->funcs = &psp_v10_0_funcs;
पूर्ण
