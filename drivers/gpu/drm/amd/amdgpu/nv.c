<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
 */
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश <drm/amdgpu_drm.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_atombios.h"
#समावेश "amdgpu_ih.h"
#समावेश "amdgpu_uvd.h"
#समावेश "amdgpu_vce.h"
#समावेश "amdgpu_ucode.h"
#समावेश "amdgpu_psp.h"
#समावेश "atom.h"
#समावेश "amd_pcie.h"

#समावेश "gc/gc_10_1_0_offset.h"
#समावेश "gc/gc_10_1_0_sh_mask.h"
#समावेश "mp/mp_11_0_offset.h"

#समावेश "soc15.h"
#समावेश "soc15_common.h"
#समावेश "gmc_v10_0.h"
#समावेश "gfxhub_v2_0.h"
#समावेश "mmhub_v2_0.h"
#समावेश "nbio_v2_3.h"
#समावेश "nbio_v7_2.h"
#समावेश "hdp_v5_0.h"
#समावेश "nv.h"
#समावेश "navi10_ih.h"
#समावेश "gfx_v10_0.h"
#समावेश "sdma_v5_0.h"
#समावेश "sdma_v5_2.h"
#समावेश "vcn_v2_0.h"
#समावेश "jpeg_v2_0.h"
#समावेश "vcn_v3_0.h"
#समावेश "jpeg_v3_0.h"
#समावेश "dce_virtual.h"
#समावेश "mes_v10_1.h"
#समावेश "mxgpu_nv.h"
#समावेश "smuio_v11_0.h"
#समावेश "smuio_v11_0_6.h"

अटल स्थिर काष्ठा amd_ip_funcs nv_common_ip_funcs;

/* Navi */
अटल स्थिर काष्ठा amdgpu_video_codec_info nv_video_codecs_encode_array[] =
अणु
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC,
		.max_width = 4096,
		.max_height = 2304,
		.max_pixels_per_frame = 4096 * 2304,
		.max_level = 0,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC,
		.max_width = 4096,
		.max_height = 2304,
		.max_pixels_per_frame = 4096 * 2304,
		.max_level = 0,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_video_codecs nv_video_codecs_encode =
अणु
	.codec_count = ARRAY_SIZE(nv_video_codecs_encode_array),
	.codec_array = nv_video_codecs_encode_array,
पूर्ण;

/* Navi1x */
अटल स्थिर काष्ठा amdgpu_video_codec_info nv_video_codecs_decode_array[] =
अणु
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG2,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixels_per_frame = 4096 * 4096,
		.max_level = 3,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixels_per_frame = 4096 * 4096,
		.max_level = 5,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixels_per_frame = 4096 * 4096,
		.max_level = 52,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VC1,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixels_per_frame = 4096 * 4096,
		.max_level = 4,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC,
		.max_width = 8192,
		.max_height = 4352,
		.max_pixels_per_frame = 8192 * 4352,
		.max_level = 186,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_JPEG,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixels_per_frame = 4096 * 4096,
		.max_level = 0,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VP9,
		.max_width = 8192,
		.max_height = 4352,
		.max_pixels_per_frame = 8192 * 4352,
		.max_level = 0,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_video_codecs nv_video_codecs_decode =
अणु
	.codec_count = ARRAY_SIZE(nv_video_codecs_decode_array),
	.codec_array = nv_video_codecs_decode_array,
पूर्ण;

/* Sienna Cichlid */
अटल स्थिर काष्ठा amdgpu_video_codec_info sc_video_codecs_decode_array[] =
अणु
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG2,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixels_per_frame = 4096 * 4096,
		.max_level = 3,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixels_per_frame = 4096 * 4096,
		.max_level = 5,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixels_per_frame = 4096 * 4096,
		.max_level = 52,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VC1,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixels_per_frame = 4096 * 4096,
		.max_level = 4,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC,
		.max_width = 8192,
		.max_height = 4352,
		.max_pixels_per_frame = 8192 * 4352,
		.max_level = 186,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_JPEG,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixels_per_frame = 4096 * 4096,
		.max_level = 0,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VP9,
		.max_width = 8192,
		.max_height = 4352,
		.max_pixels_per_frame = 8192 * 4352,
		.max_level = 0,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_AV1,
		.max_width = 8192,
		.max_height = 4352,
		.max_pixels_per_frame = 8192 * 4352,
		.max_level = 0,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_video_codecs sc_video_codecs_decode =
अणु
	.codec_count = ARRAY_SIZE(sc_video_codecs_decode_array),
	.codec_array = sc_video_codecs_decode_array,
पूर्ण;

अटल पूर्णांक nv_query_video_codecs(काष्ठा amdgpu_device *adev, bool encode,
				 स्थिर काष्ठा amdgpu_video_codecs **codecs)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_DIMGREY_CAVEFISH:
	हाल CHIP_VANGOGH:
		अगर (encode)
			*codecs = &nv_video_codecs_encode;
		अन्यथा
			*codecs = &sc_video_codecs_decode;
		वापस 0;
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
	हाल CHIP_NAVI12:
		अगर (encode)
			*codecs = &nv_video_codecs_encode;
		अन्यथा
			*codecs = &nv_video_codecs_decode;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * Indirect रेजिस्टरs accessor
 */
अटल u32 nv_pcie_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ address, data;
	address = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	वापस amdgpu_device_indirect_rreg(adev, address, data, reg);
पूर्ण

अटल व्योम nv_pcie_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ address, data;

	address = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	amdgpu_device_indirect_wreg(adev, address, data, reg, v);
पूर्ण

अटल u64 nv_pcie_rreg64(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ address, data;
	address = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	वापस amdgpu_device_indirect_rreg64(adev, address, data, reg);
पूर्ण

अटल u32 nv_pcie_port_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags, address, data;
	u32 r;
	address = adev->nbio.funcs->get_pcie_port_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_port_data_offset(adev);

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(address, reg * 4);
	(व्योम)RREG32(address);
	r = RREG32(data);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम nv_pcie_wreg64(काष्ठा amdgpu_device *adev, u32 reg, u64 v)
अणु
	अचिन्हित दीर्घ address, data;

	address = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	amdgpu_device_indirect_wreg64(adev, address, data, reg, v);
पूर्ण

अटल व्योम nv_pcie_port_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags, address, data;

	address = adev->nbio.funcs->get_pcie_port_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_port_data_offset(adev);

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(address, reg * 4);
	(व्योम)RREG32(address);
	WREG32(data, v);
	(व्योम)RREG32(data);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
पूर्ण

अटल u32 nv_didt_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags, address, data;
	u32 r;

	address = SOC15_REG_OFFSET(GC, 0, mmDIDT_IND_INDEX);
	data = SOC15_REG_OFFSET(GC, 0, mmDIDT_IND_DATA);

	spin_lock_irqsave(&adev->didt_idx_lock, flags);
	WREG32(address, (reg));
	r = RREG32(data);
	spin_unlock_irqrestore(&adev->didt_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम nv_didt_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags, address, data;

	address = SOC15_REG_OFFSET(GC, 0, mmDIDT_IND_INDEX);
	data = SOC15_REG_OFFSET(GC, 0, mmDIDT_IND_DATA);

	spin_lock_irqsave(&adev->didt_idx_lock, flags);
	WREG32(address, (reg));
	WREG32(data, (v));
	spin_unlock_irqrestore(&adev->didt_idx_lock, flags);
पूर्ण

अटल u32 nv_get_config_memsize(काष्ठा amdgpu_device *adev)
अणु
	वापस adev->nbio.funcs->get_memsize(adev);
पूर्ण

अटल u32 nv_get_xclk(काष्ठा amdgpu_device *adev)
अणु
	वापस adev->घड़ी.spll.reference_freq;
पूर्ण


व्योम nv_grbm_select(काष्ठा amdgpu_device *adev,
		     u32 me, u32 pipe, u32 queue, u32 vmid)
अणु
	u32 grbm_gfx_cntl = 0;
	grbm_gfx_cntl = REG_SET_FIELD(grbm_gfx_cntl, GRBM_GFX_CNTL, PIPEID, pipe);
	grbm_gfx_cntl = REG_SET_FIELD(grbm_gfx_cntl, GRBM_GFX_CNTL, MEID, me);
	grbm_gfx_cntl = REG_SET_FIELD(grbm_gfx_cntl, GRBM_GFX_CNTL, VMID, vmid);
	grbm_gfx_cntl = REG_SET_FIELD(grbm_gfx_cntl, GRBM_GFX_CNTL, QUEUEID, queue);

	WREG32(SOC15_REG_OFFSET(GC, 0, mmGRBM_GFX_CNTL), grbm_gfx_cntl);
पूर्ण

अटल व्योम nv_vga_set_state(काष्ठा amdgpu_device *adev, bool state)
अणु
	/* toकरो */
पूर्ण

अटल bool nv_पढ़ो_disabled_bios(काष्ठा amdgpu_device *adev)
अणु
	/* toकरो */
	वापस false;
पूर्ण

अटल bool nv_पढ़ो_bios_from_rom(काष्ठा amdgpu_device *adev,
				  u8 *bios, u32 length_bytes)
अणु
	u32 *dw_ptr;
	u32 i, length_dw;
	u32 rom_index_offset, rom_data_offset;

	अगर (bios == शून्य)
		वापस false;
	अगर (length_bytes == 0)
		वापस false;
	/* APU vbios image is part of sbios image */
	अगर (adev->flags & AMD_IS_APU)
		वापस false;

	dw_ptr = (u32 *)bios;
	length_dw = ALIGN(length_bytes, 4) / 4;

	rom_index_offset =
		adev->smuio.funcs->get_rom_index_offset(adev);
	rom_data_offset =
		adev->smuio.funcs->get_rom_data_offset(adev);

	/* set rom index to 0 */
	WREG32(rom_index_offset, 0);
	/* पढ़ो out the rom data */
	क्रम (i = 0; i < length_dw; i++)
		dw_ptr[i] = RREG32(rom_data_offset);

	वापस true;
पूर्ण

अटल काष्ठा soc15_allowed_रेजिस्टर_entry nv_allowed_पढ़ो_रेजिस्टरs[] = अणु
	अणु SOC15_REG_ENTRY(GC, 0, mmGRBM_STATUS)पूर्ण,
	अणु SOC15_REG_ENTRY(GC, 0, mmGRBM_STATUS2)पूर्ण,
	अणु SOC15_REG_ENTRY(GC, 0, mmGRBM_STATUS_SE0)पूर्ण,
	अणु SOC15_REG_ENTRY(GC, 0, mmGRBM_STATUS_SE1)पूर्ण,
	अणु SOC15_REG_ENTRY(GC, 0, mmGRBM_STATUS_SE2)पूर्ण,
	अणु SOC15_REG_ENTRY(GC, 0, mmGRBM_STATUS_SE3)पूर्ण,
	अणु SOC15_REG_ENTRY(SDMA0, 0, mmSDMA0_STATUS_REG)पूर्ण,
	अणु SOC15_REG_ENTRY(SDMA1, 0, mmSDMA1_STATUS_REG)पूर्ण,
	अणु SOC15_REG_ENTRY(GC, 0, mmCP_STAT)पूर्ण,
	अणु SOC15_REG_ENTRY(GC, 0, mmCP_STALLED_STAT1)पूर्ण,
	अणु SOC15_REG_ENTRY(GC, 0, mmCP_STALLED_STAT2)पूर्ण,
	अणु SOC15_REG_ENTRY(GC, 0, mmCP_STALLED_STAT3)पूर्ण,
	अणु SOC15_REG_ENTRY(GC, 0, mmCP_CPF_BUSY_STAT)पूर्ण,
	अणु SOC15_REG_ENTRY(GC, 0, mmCP_CPF_STALLED_STAT1)पूर्ण,
	अणु SOC15_REG_ENTRY(GC, 0, mmCP_CPF_STATUS)पूर्ण,
	अणु SOC15_REG_ENTRY(GC, 0, mmCP_CPC_BUSY_STAT)पूर्ण,
	अणु SOC15_REG_ENTRY(GC, 0, mmCP_CPC_STALLED_STAT1)पूर्ण,
	अणु SOC15_REG_ENTRY(GC, 0, mmCP_CPC_STATUS)पूर्ण,
	अणु SOC15_REG_ENTRY(GC, 0, mmGB_ADDR_CONFIG)पूर्ण,
पूर्ण;

अटल uपूर्णांक32_t nv_पढ़ो_indexed_रेजिस्टर(काष्ठा amdgpu_device *adev, u32 se_num,
					 u32 sh_num, u32 reg_offset)
अणु
	uपूर्णांक32_t val;

	mutex_lock(&adev->grbm_idx_mutex);
	अगर (se_num != 0xffffffff || sh_num != 0xffffffff)
		amdgpu_gfx_select_se_sh(adev, se_num, sh_num, 0xffffffff);

	val = RREG32(reg_offset);

	अगर (se_num != 0xffffffff || sh_num != 0xffffffff)
		amdgpu_gfx_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
	mutex_unlock(&adev->grbm_idx_mutex);
	वापस val;
पूर्ण

अटल uपूर्णांक32_t nv_get_रेजिस्टर_value(काष्ठा amdgpu_device *adev,
				      bool indexed, u32 se_num,
				      u32 sh_num, u32 reg_offset)
अणु
	अगर (indexed) अणु
		वापस nv_पढ़ो_indexed_रेजिस्टर(adev, se_num, sh_num, reg_offset);
	पूर्ण अन्यथा अणु
		अगर (reg_offset == SOC15_REG_OFFSET(GC, 0, mmGB_ADDR_CONFIG))
			वापस adev->gfx.config.gb_addr_config;
		वापस RREG32(reg_offset);
	पूर्ण
पूर्ण

अटल पूर्णांक nv_पढ़ो_रेजिस्टर(काष्ठा amdgpu_device *adev, u32 se_num,
			    u32 sh_num, u32 reg_offset, u32 *value)
अणु
	uपूर्णांक32_t i;
	काष्ठा soc15_allowed_रेजिस्टर_entry  *en;

	*value = 0;
	क्रम (i = 0; i < ARRAY_SIZE(nv_allowed_पढ़ो_रेजिस्टरs); i++) अणु
		en = &nv_allowed_पढ़ो_रेजिस्टरs[i];
		अगर ((i == 7 && (adev->sdma.num_instances == 1)) || /* some asics करोn't have SDMA1 */
		    reg_offset !=
		    (adev->reg_offset[en->hwip][en->inst][en->seg] + en->reg_offset))
			जारी;

		*value = nv_get_रेजिस्टर_value(adev,
					       nv_allowed_पढ़ो_रेजिस्टरs[i].grbm_indexed,
					       se_num, sh_num, reg_offset);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक nv_asic_mode2_reset(काष्ठा amdgpu_device *adev)
अणु
	u32 i;
	पूर्णांक ret = 0;

	amdgpu_atombios_scratch_regs_engine_hung(adev, true);

	/* disable BM */
	pci_clear_master(adev->pdev);

	amdgpu_device_cache_pci_state(adev->pdev);

	ret = amdgpu_dpm_mode2_reset(adev);
	अगर (ret)
		dev_err(adev->dev, "GPU mode2 reset failed\n");

	amdgpu_device_load_pci_state(adev->pdev);

	/* रुको क्रम asic to come out of reset */
	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		u32 memsize = adev->nbio.funcs->get_memsize(adev);

		अगर (memsize != 0xffffffff)
			अवरोध;
		udelay(1);
	पूर्ण

	amdgpu_atombios_scratch_regs_engine_hung(adev, false);

	वापस ret;
पूर्ण

अटल क्रमागत amd_reset_method
nv_asic_reset_method(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_reset_method == AMD_RESET_METHOD_MODE1 ||
	    amdgpu_reset_method == AMD_RESET_METHOD_MODE2 ||
	    amdgpu_reset_method == AMD_RESET_METHOD_BACO ||
	    amdgpu_reset_method == AMD_RESET_METHOD_PCI)
		वापस amdgpu_reset_method;

	अगर (amdgpu_reset_method != -1)
		dev_warn(adev->dev, "Specified reset method:%d isn't supported, using AUTO instead.\n",
				  amdgpu_reset_method);

	चयन (adev->asic_type) अणु
	हाल CHIP_VANGOGH:
		वापस AMD_RESET_METHOD_MODE2;
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_DIMGREY_CAVEFISH:
		वापस AMD_RESET_METHOD_MODE1;
	शेष:
		अगर (amdgpu_dpm_is_baco_supported(adev))
			वापस AMD_RESET_METHOD_BACO;
		अन्यथा
			वापस AMD_RESET_METHOD_MODE1;
	पूर्ण
पूर्ण

अटल पूर्णांक nv_asic_reset(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret = 0;

	चयन (nv_asic_reset_method(adev)) अणु
	हाल AMD_RESET_METHOD_PCI:
		dev_info(adev->dev, "PCI reset\n");
		ret = amdgpu_device_pci_reset(adev);
		अवरोध;
	हाल AMD_RESET_METHOD_BACO:
		dev_info(adev->dev, "BACO reset\n");
		ret = amdgpu_dpm_baco_reset(adev);
		अवरोध;
	हाल AMD_RESET_METHOD_MODE2:
		dev_info(adev->dev, "MODE2 reset\n");
		ret = nv_asic_mode2_reset(adev);
		अवरोध;
	शेष:
		dev_info(adev->dev, "MODE1 reset\n");
		ret = amdgpu_device_mode1_reset(adev);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक nv_set_uvd_घड़ीs(काष्ठा amdgpu_device *adev, u32 vclk, u32 dclk)
अणु
	/* toकरो */
	वापस 0;
पूर्ण

अटल पूर्णांक nv_set_vce_घड़ीs(काष्ठा amdgpu_device *adev, u32 evclk, u32 ecclk)
अणु
	/* toकरो */
	वापस 0;
पूर्ण

अटल व्योम nv_pcie_gen3_enable(काष्ठा amdgpu_device *adev)
अणु
	अगर (pci_is_root_bus(adev->pdev->bus))
		वापस;

	अगर (amdgpu_pcie_gen2 == 0)
		वापस;

	अगर (!(adev->pm.pcie_gen_mask & (CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2 |
					CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3)))
		वापस;

	/* toकरो */
पूर्ण

अटल व्योम nv_program_aspm(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_aspm != 1)
		वापस;

	अगर (!(adev->flags & AMD_IS_APU) &&
	    (adev->nbio.funcs->program_aspm))
		adev->nbio.funcs->program_aspm(adev);

पूर्ण

अटल व्योम nv_enable_करोorbell_aperture(काष्ठा amdgpu_device *adev,
					bool enable)
अणु
	adev->nbio.funcs->enable_करोorbell_aperture(adev, enable);
	adev->nbio.funcs->enable_करोorbell_selfring_aperture(adev, enable);
पूर्ण

अटल स्थिर काष्ठा amdgpu_ip_block_version nv_common_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_COMMON,
	.major = 1,
	.minor = 0,
	.rev = 0,
	.funcs = &nv_common_ip_funcs,
पूर्ण;

अटल bool nv_is_headless_sku(काष्ठा pci_dev *pdev)
अणु
	अगर ((pdev->device == 0x731E &&
	    (pdev->revision == 0xC6 || pdev->revision == 0xC7)) ||
	    (pdev->device == 0x7340 && pdev->revision == 0xC9)  ||
	    (pdev->device == 0x7360 && pdev->revision == 0xC7))
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक nv_reg_base_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (amdgpu_discovery) अणु
		r = amdgpu_discovery_reg_base_init(adev);
		अगर (r) अणु
			DRM_WARN("failed to init reg base from ip discovery table, "
					"fallback to legacy init method\n");
			जाओ legacy_init;
		पूर्ण

		amdgpu_discovery_harvest_ip(adev);
		अगर (nv_is_headless_sku(adev->pdev)) अणु
			adev->harvest_ip_mask |= AMD_HARVEST_IP_VCN_MASK;
			adev->harvest_ip_mask |= AMD_HARVEST_IP_JPEG_MASK;
		पूर्ण

		वापस 0;
	पूर्ण

legacy_init:
	चयन (adev->asic_type) अणु
	हाल CHIP_NAVI10:
		navi10_reg_base_init(adev);
		अवरोध;
	हाल CHIP_NAVI14:
		navi14_reg_base_init(adev);
		अवरोध;
	हाल CHIP_NAVI12:
		navi12_reg_base_init(adev);
		अवरोध;
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
		sienna_cichlid_reg_base_init(adev);
		अवरोध;
	हाल CHIP_VANGOGH:
		vangogh_reg_base_init(adev);
		अवरोध;
	हाल CHIP_DIMGREY_CAVEFISH:
		dimgrey_cavefish_reg_base_init(adev);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम nv_set_virt_ops(काष्ठा amdgpu_device *adev)
अणु
	adev->virt.ops = &xgpu_nv_virt_ops;
पूर्ण

पूर्णांक nv_set_ip_blocks(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (adev->flags & AMD_IS_APU) अणु
		adev->nbio.funcs = &nbio_v7_2_funcs;
		adev->nbपन.सdp_flush_reg = &nbio_v7_2_hdp_flush_reg;
	पूर्ण अन्यथा अणु
		adev->nbio.funcs = &nbio_v2_3_funcs;
		adev->nbपन.सdp_flush_reg = &nbio_v2_3_hdp_flush_reg;
	पूर्ण
	adev->hdp.funcs = &hdp_v5_0_funcs;

	अगर (adev->asic_type >= CHIP_SIENNA_CICHLID)
		adev->smuio.funcs = &smuio_v11_0_6_funcs;
	अन्यथा
		adev->smuio.funcs = &smuio_v11_0_funcs;

	अगर (adev->asic_type == CHIP_SIENNA_CICHLID)
		adev->gmc.xgmi.supported = true;

	/* Set IP रेजिस्टर base beक्रमe any HW रेजिस्टर access */
	r = nv_reg_base_init(adev);
	अगर (r)
		वापस r;

	चयन (adev->asic_type) अणु
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
		amdgpu_device_ip_block_add(adev, &nv_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &navi10_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &psp_v11_0_ip_block);
		अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP &&
		    !amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &smu_v11_0_ip_block);
		अगर (adev->enable_भव_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		amdgpu_device_ip_block_add(adev, &gfx_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v5_0_ip_block);
		अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_सूचीECT &&
		    !amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &smu_v11_0_ip_block);
		amdgpu_device_ip_block_add(adev, &vcn_v2_0_ip_block);
		amdgpu_device_ip_block_add(adev, &jpeg_v2_0_ip_block);
		अगर (adev->enable_mes)
			amdgpu_device_ip_block_add(adev, &mes_v10_1_ip_block);
		अवरोध;
	हाल CHIP_NAVI12:
		amdgpu_device_ip_block_add(adev, &nv_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &navi10_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &psp_v11_0_ip_block);
		अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP)
			amdgpu_device_ip_block_add(adev, &smu_v11_0_ip_block);
		अगर (adev->enable_भव_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		amdgpu_device_ip_block_add(adev, &gfx_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v5_0_ip_block);
		अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_सूचीECT &&
		    !amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &smu_v11_0_ip_block);
		amdgpu_device_ip_block_add(adev, &vcn_v2_0_ip_block);
		अगर (!amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &jpeg_v2_0_ip_block);
		अवरोध;
	हाल CHIP_SIENNA_CICHLID:
		amdgpu_device_ip_block_add(adev, &nv_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &navi10_ih_ip_block);
		अगर (likely(adev->firmware.load_type == AMDGPU_FW_LOAD_PSP))
			amdgpu_device_ip_block_add(adev, &psp_v11_0_ip_block);
		अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP &&
		    is_support_sw_smu(adev))
			amdgpu_device_ip_block_add(adev, &smu_v11_0_ip_block);
		अगर (adev->enable_भव_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		amdgpu_device_ip_block_add(adev, &gfx_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v5_2_ip_block);
		amdgpu_device_ip_block_add(adev, &vcn_v3_0_ip_block);
		अगर (!amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &jpeg_v3_0_ip_block);
		अगर (adev->enable_mes)
			amdgpu_device_ip_block_add(adev, &mes_v10_1_ip_block);
		अवरोध;
	हाल CHIP_NAVY_FLOUNDER:
		amdgpu_device_ip_block_add(adev, &nv_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &navi10_ih_ip_block);
		अगर (likely(adev->firmware.load_type == AMDGPU_FW_LOAD_PSP))
			amdgpu_device_ip_block_add(adev, &psp_v11_0_ip_block);
		अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP &&
		    is_support_sw_smu(adev))
			amdgpu_device_ip_block_add(adev, &smu_v11_0_ip_block);
		अगर (adev->enable_भव_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		amdgpu_device_ip_block_add(adev, &gfx_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v5_2_ip_block);
		amdgpu_device_ip_block_add(adev, &vcn_v3_0_ip_block);
		amdgpu_device_ip_block_add(adev, &jpeg_v3_0_ip_block);
		अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_सूचीECT &&
		    is_support_sw_smu(adev))
			amdgpu_device_ip_block_add(adev, &smu_v11_0_ip_block);
		अवरोध;
	हाल CHIP_VANGOGH:
		amdgpu_device_ip_block_add(adev, &nv_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &navi10_ih_ip_block);
		अगर (likely(adev->firmware.load_type == AMDGPU_FW_LOAD_PSP))
			amdgpu_device_ip_block_add(adev, &psp_v11_0_ip_block);
		amdgpu_device_ip_block_add(adev, &smu_v11_0_ip_block);
		अगर (adev->enable_भव_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		amdgpu_device_ip_block_add(adev, &gfx_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v5_2_ip_block);
		amdgpu_device_ip_block_add(adev, &vcn_v3_0_ip_block);
		amdgpu_device_ip_block_add(adev, &jpeg_v3_0_ip_block);
		अवरोध;
	हाल CHIP_DIMGREY_CAVEFISH:
		amdgpu_device_ip_block_add(adev, &nv_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &navi10_ih_ip_block);
		अगर (likely(adev->firmware.load_type == AMDGPU_FW_LOAD_PSP))
			amdgpu_device_ip_block_add(adev, &psp_v11_0_ip_block);
		अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP &&
		    is_support_sw_smu(adev))
			amdgpu_device_ip_block_add(adev, &smu_v11_0_ip_block);
		अगर (adev->enable_भव_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
                अन्यथा अगर (amdgpu_device_has_dc_support(adev))
                        amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		amdgpu_device_ip_block_add(adev, &gfx_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v5_2_ip_block);
		amdgpu_device_ip_block_add(adev, &vcn_v3_0_ip_block);
		amdgpu_device_ip_block_add(adev, &jpeg_v3_0_ip_block);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t nv_get_rev_id(काष्ठा amdgpu_device *adev)
अणु
	वापस adev->nbio.funcs->get_rev_id(adev);
पूर्ण

अटल bool nv_need_full_reset(काष्ठा amdgpu_device *adev)
अणु
	वापस true;
पूर्ण

अटल bool nv_need_reset_on_init(काष्ठा amdgpu_device *adev)
अणु
	u32 sol_reg;

	अगर (adev->flags & AMD_IS_APU)
		वापस false;

	/* Check sOS sign of lअगरe रेजिस्टर to confirm sys driver and sOS
	 * are alपढ़ोy been loaded.
	 */
	sol_reg = RREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_81);
	अगर (sol_reg)
		वापस true;

	वापस false;
पूर्ण

अटल uपूर्णांक64_t nv_get_pcie_replay_count(काष्ठा amdgpu_device *adev)
अणु

	/* TODO
	 * dummy implement क्रम pcie_replay_count sysfs पूर्णांकerface
	 * */

	वापस 0;
पूर्ण

अटल व्योम nv_init_करोorbell_index(काष्ठा amdgpu_device *adev)
अणु
	adev->करोorbell_index.kiq = AMDGPU_NAVI10_DOORBELL_KIQ;
	adev->करोorbell_index.mec_ring0 = AMDGPU_NAVI10_DOORBELL_MEC_RING0;
	adev->करोorbell_index.mec_ring1 = AMDGPU_NAVI10_DOORBELL_MEC_RING1;
	adev->करोorbell_index.mec_ring2 = AMDGPU_NAVI10_DOORBELL_MEC_RING2;
	adev->करोorbell_index.mec_ring3 = AMDGPU_NAVI10_DOORBELL_MEC_RING3;
	adev->करोorbell_index.mec_ring4 = AMDGPU_NAVI10_DOORBELL_MEC_RING4;
	adev->करोorbell_index.mec_ring5 = AMDGPU_NAVI10_DOORBELL_MEC_RING5;
	adev->करोorbell_index.mec_ring6 = AMDGPU_NAVI10_DOORBELL_MEC_RING6;
	adev->करोorbell_index.mec_ring7 = AMDGPU_NAVI10_DOORBELL_MEC_RING7;
	adev->करोorbell_index.userqueue_start = AMDGPU_NAVI10_DOORBELL_USERQUEUE_START;
	adev->करोorbell_index.userqueue_end = AMDGPU_NAVI10_DOORBELL_USERQUEUE_END;
	adev->करोorbell_index.gfx_ring0 = AMDGPU_NAVI10_DOORBELL_GFX_RING0;
	adev->करोorbell_index.gfx_ring1 = AMDGPU_NAVI10_DOORBELL_GFX_RING1;
	adev->करोorbell_index.mes_ring = AMDGPU_NAVI10_DOORBELL_MES_RING;
	adev->करोorbell_index.sdma_engine[0] = AMDGPU_NAVI10_DOORBELL_sDMA_ENGINE0;
	adev->करोorbell_index.sdma_engine[1] = AMDGPU_NAVI10_DOORBELL_sDMA_ENGINE1;
	adev->करोorbell_index.sdma_engine[2] = AMDGPU_NAVI10_DOORBELL_sDMA_ENGINE2;
	adev->करोorbell_index.sdma_engine[3] = AMDGPU_NAVI10_DOORBELL_sDMA_ENGINE3;
	adev->करोorbell_index.ih = AMDGPU_NAVI10_DOORBELL_IH;
	adev->करोorbell_index.vcn.vcn_ring0_1 = AMDGPU_NAVI10_DOORBELL64_VCN0_1;
	adev->करोorbell_index.vcn.vcn_ring2_3 = AMDGPU_NAVI10_DOORBELL64_VCN2_3;
	adev->करोorbell_index.vcn.vcn_ring4_5 = AMDGPU_NAVI10_DOORBELL64_VCN4_5;
	adev->करोorbell_index.vcn.vcn_ring6_7 = AMDGPU_NAVI10_DOORBELL64_VCN6_7;
	adev->करोorbell_index.first_non_cp = AMDGPU_NAVI10_DOORBELL64_FIRST_NON_CP;
	adev->करोorbell_index.last_non_cp = AMDGPU_NAVI10_DOORBELL64_LAST_NON_CP;

	adev->करोorbell_index.max_assignment = AMDGPU_NAVI10_DOORBELL_MAX_ASSIGNMENT << 1;
	adev->करोorbell_index.sdma_करोorbell_range = 20;
पूर्ण

अटल व्योम nv_pre_asic_init(काष्ठा amdgpu_device *adev)
अणु
पूर्ण

अटल पूर्णांक nv_update_umd_stable_pstate(काष्ठा amdgpu_device *adev,
				       bool enter)
अणु
	अगर (enter)
		amdgpu_gfx_rlc_enter_safe_mode(adev);
	अन्यथा
		amdgpu_gfx_rlc_निकास_safe_mode(adev);

	अगर (adev->gfx.funcs->update_perfmon_mgcg)
		adev->gfx.funcs->update_perfmon_mgcg(adev, !enter);

	अगर (!(adev->flags & AMD_IS_APU) &&
	    (adev->nbio.funcs->enable_aspm))
		adev->nbio.funcs->enable_aspm(adev, !enter);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amdgpu_asic_funcs nv_asic_funcs =
अणु
	.पढ़ो_disabled_bios = &nv_पढ़ो_disabled_bios,
	.पढ़ो_bios_from_rom = &nv_पढ़ो_bios_from_rom,
	.पढ़ो_रेजिस्टर = &nv_पढ़ो_रेजिस्टर,
	.reset = &nv_asic_reset,
	.reset_method = &nv_asic_reset_method,
	.set_vga_state = &nv_vga_set_state,
	.get_xclk = &nv_get_xclk,
	.set_uvd_घड़ीs = &nv_set_uvd_घड़ीs,
	.set_vce_घड़ीs = &nv_set_vce_घड़ीs,
	.get_config_memsize = &nv_get_config_memsize,
	.init_करोorbell_index = &nv_init_करोorbell_index,
	.need_full_reset = &nv_need_full_reset,
	.need_reset_on_init = &nv_need_reset_on_init,
	.get_pcie_replay_count = &nv_get_pcie_replay_count,
	.supports_baco = &amdgpu_dpm_is_baco_supported,
	.pre_asic_init = &nv_pre_asic_init,
	.update_umd_stable_pstate = &nv_update_umd_stable_pstate,
	.query_video_codecs = &nv_query_video_codecs,
पूर्ण;

अटल पूर्णांक nv_common_early_init(व्योम *handle)
अणु
#घोषणा MMIO_REG_HOLE_OFFSET (0x80000 - PAGE_SIZE)
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->rmmio_remap.reg_offset = MMIO_REG_HOLE_OFFSET;
	adev->rmmio_remap.bus_addr = adev->rmmio_base + MMIO_REG_HOLE_OFFSET;
	adev->smc_rreg = शून्य;
	adev->smc_wreg = शून्य;
	adev->pcie_rreg = &nv_pcie_rreg;
	adev->pcie_wreg = &nv_pcie_wreg;
	adev->pcie_rreg64 = &nv_pcie_rreg64;
	adev->pcie_wreg64 = &nv_pcie_wreg64;
	adev->pciep_rreg = &nv_pcie_port_rreg;
	adev->pciep_wreg = &nv_pcie_port_wreg;

	/* TODO: will add them during VCN v2 implementation */
	adev->uvd_ctx_rreg = शून्य;
	adev->uvd_ctx_wreg = शून्य;

	adev->didt_rreg = &nv_didt_rreg;
	adev->didt_wreg = &nv_didt_wreg;

	adev->asic_funcs = &nv_asic_funcs;

	adev->rev_id = nv_get_rev_id(adev);
	adev->बाह्यal_rev_id = 0xff;
	चयन (adev->asic_type) अणु
	हाल CHIP_NAVI10:
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_IH_CG |
			AMD_CG_SUPPORT_HDP_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_ATHUB_MGCG |
			AMD_CG_SUPPORT_ATHUB_LS |
			AMD_CG_SUPPORT_VCN_MGCG |
			AMD_CG_SUPPORT_JPEG_MGCG |
			AMD_CG_SUPPORT_BIF_MGCG |
			AMD_CG_SUPPORT_BIF_LS;
		adev->pg_flags = AMD_PG_SUPPORT_VCN |
			AMD_PG_SUPPORT_VCN_DPG |
			AMD_PG_SUPPORT_JPEG |
			AMD_PG_SUPPORT_ATHUB;
		adev->बाह्यal_rev_id = adev->rev_id + 0x1;
		अवरोध;
	हाल CHIP_NAVI14:
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_IH_CG |
			AMD_CG_SUPPORT_HDP_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_ATHUB_MGCG |
			AMD_CG_SUPPORT_ATHUB_LS |
			AMD_CG_SUPPORT_VCN_MGCG |
			AMD_CG_SUPPORT_JPEG_MGCG |
			AMD_CG_SUPPORT_BIF_MGCG |
			AMD_CG_SUPPORT_BIF_LS;
		adev->pg_flags = AMD_PG_SUPPORT_VCN |
			AMD_PG_SUPPORT_JPEG |
			AMD_PG_SUPPORT_VCN_DPG;
		adev->बाह्यal_rev_id = adev->rev_id + 20;
		अवरोध;
	हाल CHIP_NAVI12:
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_GFX_RLC_LS |
			AMD_CG_SUPPORT_IH_CG |
			AMD_CG_SUPPORT_HDP_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_ATHUB_MGCG |
			AMD_CG_SUPPORT_ATHUB_LS |
			AMD_CG_SUPPORT_VCN_MGCG |
			AMD_CG_SUPPORT_JPEG_MGCG;
		adev->pg_flags = AMD_PG_SUPPORT_VCN |
			AMD_PG_SUPPORT_VCN_DPG |
			AMD_PG_SUPPORT_JPEG |
			AMD_PG_SUPPORT_ATHUB;
		/* guest vm माला_लो 0xffffffff when पढ़ोing RCC_DEV0_EPF0_STRAP0,
		 * as a consequence, the rev_id and बाह्यal_rev_id are wrong.
		 * workaround it by hardcoding rev_id to 0 (शेष value).
		 */
		अगर (amdgpu_sriov_vf(adev))
			adev->rev_id = 0;
		adev->बाह्यal_rev_id = adev->rev_id + 0xa;
		अवरोध;
	हाल CHIP_SIENNA_CICHLID:
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_GFX_3D_CGCG |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_VCN_MGCG |
			AMD_CG_SUPPORT_JPEG_MGCG |
			AMD_CG_SUPPORT_HDP_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_IH_CG |
			AMD_CG_SUPPORT_MC_LS;
		adev->pg_flags = AMD_PG_SUPPORT_VCN |
			AMD_PG_SUPPORT_VCN_DPG |
			AMD_PG_SUPPORT_JPEG |
			AMD_PG_SUPPORT_ATHUB |
			AMD_PG_SUPPORT_MMHUB;
		अगर (amdgpu_sriov_vf(adev)) अणु
			/* hypervisor control CG and PG enablement */
			adev->cg_flags = 0;
			adev->pg_flags = 0;
		पूर्ण
		adev->बाह्यal_rev_id = adev->rev_id + 0x28;
		अवरोध;
	हाल CHIP_NAVY_FLOUNDER:
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_GFX_3D_CGCG |
			AMD_CG_SUPPORT_VCN_MGCG |
			AMD_CG_SUPPORT_JPEG_MGCG |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_HDP_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_IH_CG;
		adev->pg_flags = AMD_PG_SUPPORT_VCN |
			AMD_PG_SUPPORT_VCN_DPG |
			AMD_PG_SUPPORT_JPEG |
			AMD_PG_SUPPORT_ATHUB |
			AMD_PG_SUPPORT_MMHUB;
		adev->बाह्यal_rev_id = adev->rev_id + 0x32;
		अवरोध;

	हाल CHIP_VANGOGH:
		adev->apu_flags |= AMD_APU_IS_VANGOGH;
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_GFX_RLC_LS |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_3D_CGCG |
			AMD_CG_SUPPORT_GFX_3D_CGLS |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_GFX_FGCG |
			AMD_CG_SUPPORT_VCN_MGCG |
			AMD_CG_SUPPORT_JPEG_MGCG;
		adev->pg_flags = AMD_PG_SUPPORT_GFX_PG |
			AMD_PG_SUPPORT_VCN |
			AMD_PG_SUPPORT_VCN_DPG |
			AMD_PG_SUPPORT_JPEG;
		अगर (adev->apu_flags & AMD_APU_IS_VANGOGH)
			adev->बाह्यal_rev_id = adev->rev_id + 0x01;
		अवरोध;
	हाल CHIP_DIMGREY_CAVEFISH:
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_GFX_3D_CGCG |
			AMD_CG_SUPPORT_VCN_MGCG |
			AMD_CG_SUPPORT_JPEG_MGCG |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_HDP_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_IH_CG;
		adev->pg_flags = AMD_PG_SUPPORT_VCN |
			AMD_PG_SUPPORT_VCN_DPG |
			AMD_PG_SUPPORT_JPEG |
			AMD_PG_SUPPORT_ATHUB |
			AMD_PG_SUPPORT_MMHUB;
		adev->बाह्यal_rev_id = adev->rev_id + 0x3c;
		अवरोध;
	शेष:
		/* FIXME: not supported yet */
		वापस -EINVAL;
	पूर्ण

	अगर (adev->harvest_ip_mask & AMD_HARVEST_IP_VCN_MASK)
		adev->pg_flags &= ~(AMD_PG_SUPPORT_VCN |
				    AMD_PG_SUPPORT_VCN_DPG |
				    AMD_PG_SUPPORT_JPEG);

	अगर (amdgpu_sriov_vf(adev)) अणु
		amdgpu_virt_init_setting(adev);
		xgpu_nv_mailbox_set_irq_funcs(adev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nv_common_late_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev))
		xgpu_nv_mailbox_get_irq(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक nv_common_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev))
		xgpu_nv_mailbox_add_irq_id(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक nv_common_sw_fini(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक nv_common_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* enable pcie gen2/3 link */
	nv_pcie_gen3_enable(adev);
	/* enable aspm */
	nv_program_aspm(adev);
	/* setup nbio रेजिस्टरs */
	adev->nbio.funcs->init_रेजिस्टरs(adev);
	/* remap HDP रेजिस्टरs to a hole in mmio space,
	 * क्रम the purpose of expose those रेजिस्टरs
	 * to process space
	 */
	अगर (adev->nbio.funcs->remap_hdp_रेजिस्टरs)
		adev->nbio.funcs->remap_hdp_रेजिस्टरs(adev);
	/* enable the करोorbell aperture */
	nv_enable_करोorbell_aperture(adev, true);

	वापस 0;
पूर्ण

अटल पूर्णांक nv_common_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* disable the करोorbell aperture */
	nv_enable_करोorbell_aperture(adev, false);

	वापस 0;
पूर्ण

अटल पूर्णांक nv_common_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस nv_common_hw_fini(adev);
पूर्ण

अटल पूर्णांक nv_common_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस nv_common_hw_init(adev);
पूर्ण

अटल bool nv_common_is_idle(व्योम *handle)
अणु
	वापस true;
पूर्ण

अटल पूर्णांक nv_common_रुको_क्रम_idle(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक nv_common_soft_reset(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक nv_common_set_घड़ीgating_state(व्योम *handle,
					   क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
	हाल CHIP_NAVI12:
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_DIMGREY_CAVEFISH:
		adev->nbio.funcs->update_medium_grain_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		adev->nbio.funcs->update_medium_grain_light_sleep(adev,
				state == AMD_CG_STATE_GATE);
		adev->hdp.funcs->update_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		adev->smuio.funcs->update_rom_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nv_common_set_घातergating_state(व्योम *handle,
					   क्रमागत amd_घातergating_state state)
अणु
	/* TODO */
	वापस 0;
पूर्ण

अटल व्योम nv_common_get_घड़ीgating_state(व्योम *handle, u32 *flags)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev))
		*flags = 0;

	adev->nbio.funcs->get_घड़ीgating_state(adev, flags);

	adev->hdp.funcs->get_घड़ी_gating_state(adev, flags);

	adev->smuio.funcs->get_घड़ी_gating_state(adev, flags);

	वापस;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs nv_common_ip_funcs = अणु
	.name = "nv_common",
	.early_init = nv_common_early_init,
	.late_init = nv_common_late_init,
	.sw_init = nv_common_sw_init,
	.sw_fini = nv_common_sw_fini,
	.hw_init = nv_common_hw_init,
	.hw_fini = nv_common_hw_fini,
	.suspend = nv_common_suspend,
	.resume = nv_common_resume,
	.is_idle = nv_common_is_idle,
	.रुको_क्रम_idle = nv_common_रुको_क्रम_idle,
	.soft_reset = nv_common_soft_reset,
	.set_घड़ीgating_state = nv_common_set_घड़ीgating_state,
	.set_घातergating_state = nv_common_set_घातergating_state,
	.get_घड़ीgating_state = nv_common_get_घड़ीgating_state,
पूर्ण;
