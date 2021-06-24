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

#समावेश "uvd/uvd_7_0_offset.h"
#समावेश "gc/gc_9_0_offset.h"
#समावेश "gc/gc_9_0_sh_mask.h"
#समावेश "sdma0/sdma0_4_0_offset.h"
#समावेश "sdma1/sdma1_4_0_offset.h"
#समावेश "nbio/nbio_7_0_default.h"
#समावेश "nbio/nbio_7_0_offset.h"
#समावेश "nbio/nbio_7_0_sh_mask.h"
#समावेश "nbio/nbio_7_0_smn.h"
#समावेश "mp/mp_9_0_offset.h"

#समावेश "soc15.h"
#समावेश "soc15_common.h"
#समावेश "gfx_v9_0.h"
#समावेश "gmc_v9_0.h"
#समावेश "gfxhub_v1_0.h"
#समावेश "mmhub_v1_0.h"
#समावेश "df_v1_7.h"
#समावेश "df_v3_6.h"
#समावेश "nbio_v6_1.h"
#समावेश "nbio_v7_0.h"
#समावेश "nbio_v7_4.h"
#समावेश "hdp_v4_0.h"
#समावेश "vega10_ih.h"
#समावेश "vega20_ih.h"
#समावेश "navi10_ih.h"
#समावेश "sdma_v4_0.h"
#समावेश "uvd_v7_0.h"
#समावेश "vce_v4_0.h"
#समावेश "vcn_v1_0.h"
#समावेश "vcn_v2_0.h"
#समावेश "jpeg_v2_0.h"
#समावेश "vcn_v2_5.h"
#समावेश "jpeg_v2_5.h"
#समावेश "smuio_v9_0.h"
#समावेश "smuio_v11_0.h"
#समावेश "smuio_v13_0.h"
#समावेश "dce_virtual.h"
#समावेश "mxgpu_ai.h"
#समावेश "amdgpu_ras.h"
#समावेश "amdgpu_xgmi.h"
#समावेश <uapi/linux/kfd_ioctl.h>

#घोषणा mmMP0_MISC_CGTT_CTRL0                                                                   0x01b9
#घोषणा mmMP0_MISC_CGTT_CTRL0_BASE_IDX                                                          0
#घोषणा mmMP0_MISC_LIGHT_SLEEP_CTRL                                                             0x01ba
#घोषणा mmMP0_MISC_LIGHT_SLEEP_CTRL_BASE_IDX                                                    0

/* Vega, Raven, Arcturus */
अटल स्थिर काष्ठा amdgpu_video_codec_info vega_video_codecs_encode_array[] =
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

अटल स्थिर काष्ठा amdgpu_video_codecs vega_video_codecs_encode =
अणु
	.codec_count = ARRAY_SIZE(vega_video_codecs_encode_array),
	.codec_array = vega_video_codecs_encode_array,
पूर्ण;

/* Vega */
अटल स्थिर काष्ठा amdgpu_video_codec_info vega_video_codecs_decode_array[] =
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
		.max_width = 4096,
		.max_height = 4096,
		.max_pixels_per_frame = 4096 * 4096,
		.max_level = 186,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_JPEG,
		.max_width = 4096,
		.max_height = 4096,
		.max_pixels_per_frame = 4096 * 4096,
		.max_level = 0,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_video_codecs vega_video_codecs_decode =
अणु
	.codec_count = ARRAY_SIZE(vega_video_codecs_decode_array),
	.codec_array = vega_video_codecs_decode_array,
पूर्ण;

/* Raven */
अटल स्थिर काष्ठा amdgpu_video_codec_info rv_video_codecs_decode_array[] =
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
		.max_width = 4096,
		.max_height = 4096,
		.max_pixels_per_frame = 4096 * 4096,
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
		.max_width = 4096,
		.max_height = 4096,
		.max_pixels_per_frame = 4096 * 4096,
		.max_level = 0,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_video_codecs rv_video_codecs_decode =
अणु
	.codec_count = ARRAY_SIZE(rv_video_codecs_decode_array),
	.codec_array = rv_video_codecs_decode_array,
पूर्ण;

/* Renoir, Arcturus */
अटल स्थिर काष्ठा amdgpu_video_codec_info rn_video_codecs_decode_array[] =
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
		.max_pixels_per_frame = 4096 * 4096,
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
		.max_pixels_per_frame = 4096 * 4096,
		.max_level = 0,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_video_codecs rn_video_codecs_decode =
अणु
	.codec_count = ARRAY_SIZE(rn_video_codecs_decode_array),
	.codec_array = rn_video_codecs_decode_array,
पूर्ण;

अटल पूर्णांक soc15_query_video_codecs(काष्ठा amdgpu_device *adev, bool encode,
				    स्थिर काष्ठा amdgpu_video_codecs **codecs)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA20:
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA12:
		अगर (encode)
			*codecs = &vega_video_codecs_encode;
		अन्यथा
			*codecs = &vega_video_codecs_decode;
		वापस 0;
	हाल CHIP_RAVEN:
		अगर (encode)
			*codecs = &vega_video_codecs_encode;
		अन्यथा
			*codecs = &rv_video_codecs_decode;
		वापस 0;
	हाल CHIP_ARCTURUS:
	हाल CHIP_ALDEBARAN:
	हाल CHIP_RENOIR:
		अगर (encode)
			*codecs = &vega_video_codecs_encode;
		अन्यथा
			*codecs = &rn_video_codecs_decode;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * Indirect रेजिस्टरs accessor
 */
अटल u32 soc15_pcie_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ address, data;
	address = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	वापस amdgpu_device_indirect_rreg(adev, address, data, reg);
पूर्ण

अटल व्योम soc15_pcie_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ address, data;

	address = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	amdgpu_device_indirect_wreg(adev, address, data, reg, v);
पूर्ण

अटल u64 soc15_pcie_rreg64(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ address, data;
	address = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	वापस amdgpu_device_indirect_rreg64(adev, address, data, reg);
पूर्ण

अटल व्योम soc15_pcie_wreg64(काष्ठा amdgpu_device *adev, u32 reg, u64 v)
अणु
	अचिन्हित दीर्घ address, data;

	address = adev->nbio.funcs->get_pcie_index_offset(adev);
	data = adev->nbio.funcs->get_pcie_data_offset(adev);

	amdgpu_device_indirect_wreg64(adev, address, data, reg, v);
पूर्ण

अटल u32 soc15_uvd_ctx_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags, address, data;
	u32 r;

	address = SOC15_REG_OFFSET(UVD, 0, mmUVD_CTX_INDEX);
	data = SOC15_REG_OFFSET(UVD, 0, mmUVD_CTX_DATA);

	spin_lock_irqsave(&adev->uvd_ctx_idx_lock, flags);
	WREG32(address, ((reg) & 0x1ff));
	r = RREG32(data);
	spin_unlock_irqrestore(&adev->uvd_ctx_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम soc15_uvd_ctx_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags, address, data;

	address = SOC15_REG_OFFSET(UVD, 0, mmUVD_CTX_INDEX);
	data = SOC15_REG_OFFSET(UVD, 0, mmUVD_CTX_DATA);

	spin_lock_irqsave(&adev->uvd_ctx_idx_lock, flags);
	WREG32(address, ((reg) & 0x1ff));
	WREG32(data, (v));
	spin_unlock_irqrestore(&adev->uvd_ctx_idx_lock, flags);
पूर्ण

अटल u32 soc15_didt_rreg(काष्ठा amdgpu_device *adev, u32 reg)
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

अटल व्योम soc15_didt_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags, address, data;

	address = SOC15_REG_OFFSET(GC, 0, mmDIDT_IND_INDEX);
	data = SOC15_REG_OFFSET(GC, 0, mmDIDT_IND_DATA);

	spin_lock_irqsave(&adev->didt_idx_lock, flags);
	WREG32(address, (reg));
	WREG32(data, (v));
	spin_unlock_irqrestore(&adev->didt_idx_lock, flags);
पूर्ण

अटल u32 soc15_gc_cac_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->gc_cac_idx_lock, flags);
	WREG32_SOC15(GC, 0, mmGC_CAC_IND_INDEX, (reg));
	r = RREG32_SOC15(GC, 0, mmGC_CAC_IND_DATA);
	spin_unlock_irqrestore(&adev->gc_cac_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम soc15_gc_cac_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->gc_cac_idx_lock, flags);
	WREG32_SOC15(GC, 0, mmGC_CAC_IND_INDEX, (reg));
	WREG32_SOC15(GC, 0, mmGC_CAC_IND_DATA, (v));
	spin_unlock_irqrestore(&adev->gc_cac_idx_lock, flags);
पूर्ण

अटल u32 soc15_se_cac_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->se_cac_idx_lock, flags);
	WREG32_SOC15(GC, 0, mmSE_CAC_IND_INDEX, (reg));
	r = RREG32_SOC15(GC, 0, mmSE_CAC_IND_DATA);
	spin_unlock_irqrestore(&adev->se_cac_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम soc15_se_cac_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->se_cac_idx_lock, flags);
	WREG32_SOC15(GC, 0, mmSE_CAC_IND_INDEX, (reg));
	WREG32_SOC15(GC, 0, mmSE_CAC_IND_DATA, (v));
	spin_unlock_irqrestore(&adev->se_cac_idx_lock, flags);
पूर्ण

अटल u32 soc15_get_config_memsize(काष्ठा amdgpu_device *adev)
अणु
	वापस adev->nbio.funcs->get_memsize(adev);
पूर्ण

अटल u32 soc15_get_xclk(काष्ठा amdgpu_device *adev)
अणु
	u32 reference_घड़ी = adev->घड़ी.spll.reference_freq;

	अगर (adev->asic_type == CHIP_RENOIR)
		वापस 10000;
	अगर (adev->asic_type == CHIP_RAVEN)
		वापस reference_घड़ी / 4;

	वापस reference_घड़ी;
पूर्ण


व्योम soc15_grbm_select(काष्ठा amdgpu_device *adev,
		     u32 me, u32 pipe, u32 queue, u32 vmid)
अणु
	u32 grbm_gfx_cntl = 0;
	grbm_gfx_cntl = REG_SET_FIELD(grbm_gfx_cntl, GRBM_GFX_CNTL, PIPEID, pipe);
	grbm_gfx_cntl = REG_SET_FIELD(grbm_gfx_cntl, GRBM_GFX_CNTL, MEID, me);
	grbm_gfx_cntl = REG_SET_FIELD(grbm_gfx_cntl, GRBM_GFX_CNTL, VMID, vmid);
	grbm_gfx_cntl = REG_SET_FIELD(grbm_gfx_cntl, GRBM_GFX_CNTL, QUEUEID, queue);

	WREG32_SOC15_RLC_SHADOW(GC, 0, mmGRBM_GFX_CNTL, grbm_gfx_cntl);
पूर्ण

अटल व्योम soc15_vga_set_state(काष्ठा amdgpu_device *adev, bool state)
अणु
	/* toकरो */
पूर्ण

अटल bool soc15_पढ़ो_disabled_bios(काष्ठा amdgpu_device *adev)
अणु
	/* toकरो */
	वापस false;
पूर्ण

अटल bool soc15_पढ़ो_bios_from_rom(काष्ठा amdgpu_device *adev,
				     u8 *bios, u32 length_bytes)
अणु
	u32 *dw_ptr;
	u32 i, length_dw;
	uपूर्णांक32_t rom_index_offset;
	uपूर्णांक32_t rom_data_offset;

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

अटल काष्ठा soc15_allowed_रेजिस्टर_entry soc15_allowed_पढ़ो_रेजिस्टरs[] = अणु
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
	अणु SOC15_REG_ENTRY(GC, 0, mmDB_DEBUG2)पूर्ण,
पूर्ण;

अटल uपूर्णांक32_t soc15_पढ़ो_indexed_रेजिस्टर(काष्ठा amdgpu_device *adev, u32 se_num,
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

अटल uपूर्णांक32_t soc15_get_रेजिस्टर_value(काष्ठा amdgpu_device *adev,
					 bool indexed, u32 se_num,
					 u32 sh_num, u32 reg_offset)
अणु
	अगर (indexed) अणु
		वापस soc15_पढ़ो_indexed_रेजिस्टर(adev, se_num, sh_num, reg_offset);
	पूर्ण अन्यथा अणु
		अगर (reg_offset == SOC15_REG_OFFSET(GC, 0, mmGB_ADDR_CONFIG))
			वापस adev->gfx.config.gb_addr_config;
		अन्यथा अगर (reg_offset == SOC15_REG_OFFSET(GC, 0, mmDB_DEBUG2))
			वापस adev->gfx.config.db_debug2;
		वापस RREG32(reg_offset);
	पूर्ण
पूर्ण

अटल पूर्णांक soc15_पढ़ो_रेजिस्टर(काष्ठा amdgpu_device *adev, u32 se_num,
			    u32 sh_num, u32 reg_offset, u32 *value)
अणु
	uपूर्णांक32_t i;
	काष्ठा soc15_allowed_रेजिस्टर_entry  *en;

	*value = 0;
	क्रम (i = 0; i < ARRAY_SIZE(soc15_allowed_पढ़ो_रेजिस्टरs); i++) अणु
		en = &soc15_allowed_पढ़ो_रेजिस्टरs[i];
		अगर (adev->reg_offset[en->hwip][en->inst] &&
			reg_offset != (adev->reg_offset[en->hwip][en->inst][en->seg]
					+ en->reg_offset))
			जारी;

		*value = soc15_get_रेजिस्टर_value(adev,
						  soc15_allowed_पढ़ो_रेजिस्टरs[i].grbm_indexed,
						  se_num, sh_num, reg_offset);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण


/**
 * soc15_program_रेजिस्टर_sequence - program an array of रेजिस्टरs.
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @regs: poपूर्णांकer to the रेजिस्टर array
 * @array_size: size of the रेजिस्टर array
 *
 * Programs an array or रेजिस्टरs with and and or masks.
 * This is a helper क्रम setting golden रेजिस्टरs.
 */

व्योम soc15_program_रेजिस्टर_sequence(काष्ठा amdgpu_device *adev,
					     स्थिर काष्ठा soc15_reg_golden *regs,
					     स्थिर u32 array_size)
अणु
	स्थिर काष्ठा soc15_reg_golden *entry;
	u32 पंचांगp, reg;
	पूर्णांक i;

	क्रम (i = 0; i < array_size; ++i) अणु
		entry = &regs[i];
		reg =  adev->reg_offset[entry->hwip][entry->instance][entry->segment] + entry->reg;

		अगर (entry->and_mask == 0xffffffff) अणु
			पंचांगp = entry->or_mask;
		पूर्ण अन्यथा अणु
			पंचांगp = RREG32(reg);
			पंचांगp &= ~(entry->and_mask);
			पंचांगp |= (entry->or_mask & entry->and_mask);
		पूर्ण

		अगर (reg == SOC15_REG_OFFSET(GC, 0, mmPA_SC_BINNER_EVENT_CNTL_3) ||
			reg == SOC15_REG_OFFSET(GC, 0, mmPA_SC_ENHANCE) ||
			reg == SOC15_REG_OFFSET(GC, 0, mmPA_SC_ENHANCE_1) ||
			reg == SOC15_REG_OFFSET(GC, 0, mmSH_MEM_CONFIG))
			WREG32_RLC(reg, पंचांगp);
		अन्यथा
			WREG32(reg, पंचांगp);

	पूर्ण

पूर्ण

अटल पूर्णांक soc15_asic_baco_reset(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *ras = amdgpu_ras_get_context(adev);
	पूर्णांक ret = 0;

	/* aव्योम NBIF got stuck when करो RAS recovery in BACO reset */
	अगर (ras && ras->supported)
		adev->nbio.funcs->enable_करोorbell_पूर्णांकerrupt(adev, false);

	ret = amdgpu_dpm_baco_reset(adev);
	अगर (ret)
		वापस ret;

	/* re-enable करोorbell पूर्णांकerrupt after BACO निकास */
	अगर (ras && ras->supported)
		adev->nbio.funcs->enable_करोorbell_पूर्णांकerrupt(adev, true);

	वापस 0;
पूर्ण

अटल क्रमागत amd_reset_method
soc15_asic_reset_method(काष्ठा amdgpu_device *adev)
अणु
	bool baco_reset = false;
	bool connected_to_cpu = false;
	काष्ठा amdgpu_ras *ras = amdgpu_ras_get_context(adev);

        अगर (adev->gmc.xgmi.supported && adev->gmc.xgmi.connected_to_cpu)
                connected_to_cpu = true;

	अगर (amdgpu_reset_method == AMD_RESET_METHOD_MODE1 ||
	    amdgpu_reset_method == AMD_RESET_METHOD_MODE2 ||
	    amdgpu_reset_method == AMD_RESET_METHOD_BACO ||
	    amdgpu_reset_method == AMD_RESET_METHOD_PCI) अणु
		/* If connected to cpu, driver only support mode2 */
                अगर (connected_to_cpu)
                        वापस AMD_RESET_METHOD_MODE2;
                वापस amdgpu_reset_method;
        पूर्ण

	अगर (amdgpu_reset_method != -1)
		dev_warn(adev->dev, "Specified reset method:%d isn't supported, using AUTO instead.\n",
				  amdgpu_reset_method);

	चयन (adev->asic_type) अणु
	हाल CHIP_RAVEN:
	हाल CHIP_RENOIR:
		वापस AMD_RESET_METHOD_MODE2;
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA12:
	हाल CHIP_ARCTURUS:
		baco_reset = amdgpu_dpm_is_baco_supported(adev);
		अवरोध;
	हाल CHIP_VEGA20:
		अगर (adev->psp.sos_fw_version >= 0x80067)
			baco_reset = amdgpu_dpm_is_baco_supported(adev);

		/*
		 * 1. PMFW version > 0x284300: all हालs use baco
		 * 2. PMFW version <= 0x284300: only sGPU w/o RAS use baco
		 */
		अगर ((ras && ras->supported) && adev->pm.fw_version <= 0x283400)
			baco_reset = false;
		अवरोध;
	हाल CHIP_ALDEBARAN:
		 /*
		 * 1.connected to cpu: driver issue mode2 reset
		 * 2.discret gpu: driver issue mode1 reset
		 */
		अगर (connected_to_cpu)
			वापस AMD_RESET_METHOD_MODE2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (baco_reset)
		वापस AMD_RESET_METHOD_BACO;
	अन्यथा
		वापस AMD_RESET_METHOD_MODE1;
पूर्ण

अटल पूर्णांक soc15_asic_reset(काष्ठा amdgpu_device *adev)
अणु
	/* original raven करोesn't have full asic reset */
	अगर ((adev->apu_flags & AMD_APU_IS_RAVEN) &&
	    !(adev->apu_flags & AMD_APU_IS_RAVEN2))
		वापस 0;

	चयन (soc15_asic_reset_method(adev)) अणु
	हाल AMD_RESET_METHOD_PCI:
		dev_info(adev->dev, "PCI reset\n");
		वापस amdgpu_device_pci_reset(adev);
	हाल AMD_RESET_METHOD_BACO:
		dev_info(adev->dev, "BACO reset\n");
		वापस soc15_asic_baco_reset(adev);
	हाल AMD_RESET_METHOD_MODE2:
		dev_info(adev->dev, "MODE2 reset\n");
		वापस amdgpu_dpm_mode2_reset(adev);
	शेष:
		dev_info(adev->dev, "MODE1 reset\n");
		वापस amdgpu_device_mode1_reset(adev);
	पूर्ण
पूर्ण

अटल bool soc15_supports_baco(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA12:
	हाल CHIP_ARCTURUS:
		वापस amdgpu_dpm_is_baco_supported(adev);
	हाल CHIP_VEGA20:
		अगर (adev->psp.sos_fw_version >= 0x80067)
			वापस amdgpu_dpm_is_baco_supported(adev);
		वापस false;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*अटल पूर्णांक soc15_set_uvd_घड़ी(काष्ठा amdgpu_device *adev, u32 घड़ी,
			u32 cntl_reg, u32 status_reg)
अणु
	वापस 0;
पूर्ण*/

अटल पूर्णांक soc15_set_uvd_घड़ीs(काष्ठा amdgpu_device *adev, u32 vclk, u32 dclk)
अणु
	/*पूर्णांक r;

	r = soc15_set_uvd_घड़ी(adev, vclk, ixCG_VCLK_CNTL, ixCG_VCLK_STATUS);
	अगर (r)
		वापस r;

	r = soc15_set_uvd_घड़ी(adev, dclk, ixCG_DCLK_CNTL, ixCG_DCLK_STATUS);
	*/
	वापस 0;
पूर्ण

अटल पूर्णांक soc15_set_vce_घड़ीs(काष्ठा amdgpu_device *adev, u32 evclk, u32 ecclk)
अणु
	/* toकरो */

	वापस 0;
पूर्ण

अटल व्योम soc15_pcie_gen3_enable(काष्ठा amdgpu_device *adev)
अणु
	अगर (pci_is_root_bus(adev->pdev->bus))
		वापस;

	अगर (amdgpu_pcie_gen2 == 0)
		वापस;

	अगर (adev->flags & AMD_IS_APU)
		वापस;

	अगर (!(adev->pm.pcie_gen_mask & (CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2 |
					CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3)))
		वापस;

	/* toकरो */
पूर्ण

अटल व्योम soc15_program_aspm(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_aspm != 1)
		वापस;

	अगर (!(adev->flags & AMD_IS_APU) &&
	    (adev->nbio.funcs->program_aspm))
		adev->nbio.funcs->program_aspm(adev);
पूर्ण

अटल व्योम soc15_enable_करोorbell_aperture(काष्ठा amdgpu_device *adev,
					   bool enable)
अणु
	adev->nbio.funcs->enable_करोorbell_aperture(adev, enable);
	adev->nbio.funcs->enable_करोorbell_selfring_aperture(adev, enable);
पूर्ण

अटल स्थिर काष्ठा amdgpu_ip_block_version vega10_common_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_COMMON,
	.major = 2,
	.minor = 0,
	.rev = 0,
	.funcs = &soc15_common_ip_funcs,
पूर्ण;

अटल uपूर्णांक32_t soc15_get_rev_id(काष्ठा amdgpu_device *adev)
अणु
	वापस adev->nbio.funcs->get_rev_id(adev);
पूर्ण

अटल व्योम soc15_reg_base_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	/* Set IP रेजिस्टर base beक्रमe any HW रेजिस्टर access */
	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA12:
	हाल CHIP_RAVEN:
		vega10_reg_base_init(adev);
		अवरोध;
	हाल CHIP_RENOIR:
		/* It's safe to करो ip discovery here क्रम Renior,
		 * it करोesn't support SRIOV. */
		अगर (amdgpu_discovery) अणु
			r = amdgpu_discovery_reg_base_init(adev);
			अगर (r == 0)
				अवरोध;
			DRM_WARN("failed to init reg base from ip discovery table, "
				 "fallback to legacy init method\n");
		पूर्ण
		vega10_reg_base_init(adev);
		अवरोध;
	हाल CHIP_VEGA20:
		vega20_reg_base_init(adev);
		अवरोध;
	हाल CHIP_ARCTURUS:
		arct_reg_base_init(adev);
		अवरोध;
	हाल CHIP_ALDEBARAN:
		aldebaran_reg_base_init(adev);
		अवरोध;
	शेष:
		DRM_ERROR("Unsupported asic type: %d!\n", adev->asic_type);
		अवरोध;
	पूर्ण
पूर्ण

व्योम soc15_set_virt_ops(काष्ठा amdgpu_device *adev)
अणु
	adev->virt.ops = &xgpu_ai_virt_ops;

	/* init soc15 reg base early enough so we can
	 * request request full access क्रम sriov beक्रमe
	 * set_ip_blocks. */
	soc15_reg_base_init(adev);
पूर्ण

पूर्णांक soc15_set_ip_blocks(काष्ठा amdgpu_device *adev)
अणु
	/* क्रम bare metal हाल */
	अगर (!amdgpu_sriov_vf(adev))
		soc15_reg_base_init(adev);

	अगर (adev->flags & AMD_IS_APU) अणु
		adev->nbio.funcs = &nbio_v7_0_funcs;
		adev->nbपन.सdp_flush_reg = &nbio_v7_0_hdp_flush_reg;
	पूर्ण अन्यथा अगर (adev->asic_type == CHIP_VEGA20 ||
		   adev->asic_type == CHIP_ARCTURUS ||
		   adev->asic_type == CHIP_ALDEBARAN) अणु
		adev->nbio.funcs = &nbio_v7_4_funcs;
		adev->nbपन.सdp_flush_reg = &nbio_v7_4_hdp_flush_reg;
	पूर्ण अन्यथा अणु
		adev->nbio.funcs = &nbio_v6_1_funcs;
		adev->nbपन.सdp_flush_reg = &nbio_v6_1_hdp_flush_reg;
	पूर्ण
	adev->hdp.funcs = &hdp_v4_0_funcs;

	अगर (adev->asic_type == CHIP_VEGA20 ||
	    adev->asic_type == CHIP_ARCTURUS ||
	    adev->asic_type == CHIP_ALDEBARAN)
		adev->df.funcs = &df_v3_6_funcs;
	अन्यथा
		adev->df.funcs = &df_v1_7_funcs;

	अगर (adev->asic_type == CHIP_VEGA20 ||
	    adev->asic_type == CHIP_ARCTURUS)
		adev->smuio.funcs = &smuio_v11_0_funcs;
	अन्यथा अगर (adev->asic_type == CHIP_ALDEBARAN)
		adev->smuio.funcs = &smuio_v13_0_funcs;
	अन्यथा
		adev->smuio.funcs = &smuio_v9_0_funcs;

	adev->rev_id = soc15_get_rev_id(adev);

	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA12:
	हाल CHIP_VEGA20:
		amdgpu_device_ip_block_add(adev, &vega10_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v9_0_ip_block);

		/* For Vega10 SR-IOV, PSP need to be initialized beक्रमe IH */
		अगर (amdgpu_sriov_vf(adev)) अणु
			अगर (likely(adev->firmware.load_type == AMDGPU_FW_LOAD_PSP)) अणु
				अगर (adev->asic_type == CHIP_VEGA20)
					amdgpu_device_ip_block_add(adev, &psp_v11_0_ip_block);
				अन्यथा
					amdgpu_device_ip_block_add(adev, &psp_v3_1_ip_block);
			पूर्ण
			अगर (adev->asic_type == CHIP_VEGA20)
				amdgpu_device_ip_block_add(adev, &vega20_ih_ip_block);
			अन्यथा
				amdgpu_device_ip_block_add(adev, &vega10_ih_ip_block);
		पूर्ण अन्यथा अणु
			अगर (adev->asic_type == CHIP_VEGA20)
				amdgpu_device_ip_block_add(adev, &vega20_ih_ip_block);
			अन्यथा
				amdgpu_device_ip_block_add(adev, &vega10_ih_ip_block);
			अगर (likely(adev->firmware.load_type == AMDGPU_FW_LOAD_PSP)) अणु
				अगर (adev->asic_type == CHIP_VEGA20)
					amdgpu_device_ip_block_add(adev, &psp_v11_0_ip_block);
				अन्यथा
					amdgpu_device_ip_block_add(adev, &psp_v3_1_ip_block);
			पूर्ण
		पूर्ण
		amdgpu_device_ip_block_add(adev, &gfx_v9_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v4_0_ip_block);
		अगर (is_support_sw_smu(adev)) अणु
			अगर (!amdgpu_sriov_vf(adev))
				amdgpu_device_ip_block_add(adev, &smu_v11_0_ip_block);
		पूर्ण अन्यथा अणु
			amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		पूर्ण
		अगर (adev->enable_भव_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		अगर (!(adev->asic_type == CHIP_VEGA20 && amdgpu_sriov_vf(adev))) अणु
			amdgpu_device_ip_block_add(adev, &uvd_v7_0_ip_block);
			amdgpu_device_ip_block_add(adev, &vce_v4_0_ip_block);
		पूर्ण
		अवरोध;
	हाल CHIP_RAVEN:
		amdgpu_device_ip_block_add(adev, &vega10_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v9_0_ip_block);
		amdgpu_device_ip_block_add(adev, &vega10_ih_ip_block);
		अगर (likely(adev->firmware.load_type == AMDGPU_FW_LOAD_PSP))
			amdgpu_device_ip_block_add(adev, &psp_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v9_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v4_0_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		अगर (adev->enable_भव_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		amdgpu_device_ip_block_add(adev, &vcn_v1_0_ip_block);
		अवरोध;
	हाल CHIP_ARCTURUS:
		amdgpu_device_ip_block_add(adev, &vega10_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v9_0_ip_block);

		अगर (amdgpu_sriov_vf(adev)) अणु
			अगर (likely(adev->firmware.load_type == AMDGPU_FW_LOAD_PSP))
				amdgpu_device_ip_block_add(adev, &psp_v11_0_ip_block);
			amdgpu_device_ip_block_add(adev, &vega20_ih_ip_block);
		पूर्ण अन्यथा अणु
			amdgpu_device_ip_block_add(adev, &vega20_ih_ip_block);
			अगर (likely(adev->firmware.load_type == AMDGPU_FW_LOAD_PSP))
				amdgpu_device_ip_block_add(adev, &psp_v11_0_ip_block);
		पूर्ण

		अगर (adev->enable_भव_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v9_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v4_0_ip_block);
		amdgpu_device_ip_block_add(adev, &smu_v11_0_ip_block);

		अगर (amdgpu_sriov_vf(adev)) अणु
			अगर (likely(adev->firmware.load_type == AMDGPU_FW_LOAD_PSP))
				amdgpu_device_ip_block_add(adev, &vcn_v2_5_ip_block);
		पूर्ण अन्यथा अणु
			amdgpu_device_ip_block_add(adev, &vcn_v2_5_ip_block);
		पूर्ण
		अगर (!amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &jpeg_v2_5_ip_block);
		अवरोध;
	हाल CHIP_RENOIR:
		amdgpu_device_ip_block_add(adev, &vega10_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v9_0_ip_block);
		amdgpu_device_ip_block_add(adev, &vega10_ih_ip_block);
		अगर (likely(adev->firmware.load_type == AMDGPU_FW_LOAD_PSP))
			amdgpu_device_ip_block_add(adev, &psp_v12_0_ip_block);
		amdgpu_device_ip_block_add(adev, &smu_v12_0_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v9_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v4_0_ip_block);
		अगर (adev->enable_भव_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
                अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		amdgpu_device_ip_block_add(adev, &vcn_v2_0_ip_block);
		amdgpu_device_ip_block_add(adev, &jpeg_v2_0_ip_block);
		अवरोध;
	हाल CHIP_ALDEBARAN:
		amdgpu_device_ip_block_add(adev, &vega10_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v9_0_ip_block);

		अगर (amdgpu_sriov_vf(adev)) अणु
			अगर (likely(adev->firmware.load_type == AMDGPU_FW_LOAD_PSP))
				amdgpu_device_ip_block_add(adev, &psp_v13_0_ip_block);
			amdgpu_device_ip_block_add(adev, &vega20_ih_ip_block);
		पूर्ण अन्यथा अणु
			amdgpu_device_ip_block_add(adev, &vega20_ih_ip_block);
			अगर (likely(adev->firmware.load_type == AMDGPU_FW_LOAD_PSP))
				amdgpu_device_ip_block_add(adev, &psp_v13_0_ip_block);
		पूर्ण

		amdgpu_device_ip_block_add(adev, &gfx_v9_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v4_0_ip_block);

		amdgpu_device_ip_block_add(adev, &smu_v13_0_ip_block);
		amdgpu_device_ip_block_add(adev, &vcn_v2_6_ip_block);
		amdgpu_device_ip_block_add(adev, &jpeg_v2_6_ip_block);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool soc15_need_full_reset(काष्ठा amdgpu_device *adev)
अणु
	/* change this when we implement soft reset */
	वापस true;
पूर्ण

अटल व्योम soc15_get_pcie_usage(काष्ठा amdgpu_device *adev, uपूर्णांक64_t *count0,
				 uपूर्णांक64_t *count1)
अणु
	uपूर्णांक32_t perfctr = 0;
	uपूर्णांक64_t cnt0_of, cnt1_of;
	पूर्णांक पंचांगp;

	/* This reports 0 on APUs, so वापस to aव्योम writing/पढ़ोing रेजिस्टरs
	 * that may or may not be dअगरferent from their GPU counterparts
	 */
	अगर (adev->flags & AMD_IS_APU)
		वापस;

	/* Set the 2 events that we wish to watch, defined above */
	/* Reg 40 is # received msgs */
	/* Reg 104 is # of posted requests sent */
	perfctr = REG_SET_FIELD(perfctr, PCIE_PERF_CNTL_TXCLK, EVENT0_SEL, 40);
	perfctr = REG_SET_FIELD(perfctr, PCIE_PERF_CNTL_TXCLK, EVENT1_SEL, 104);

	/* Write to enable desired perf counters */
	WREG32_PCIE(smnPCIE_PERF_CNTL_TXCLK, perfctr);
	/* Zero out and enable the perf counters
	 * Write 0x5:
	 * Bit 0 = Start all counters(1)
	 * Bit 2 = Global counter reset enable(1)
	 */
	WREG32_PCIE(smnPCIE_PERF_COUNT_CNTL, 0x00000005);

	msleep(1000);

	/* Load the shaकरोw and disable the perf counters
	 * Write 0x2:
	 * Bit 0 = Stop counters(0)
	 * Bit 1 = Load the shaकरोw counters(1)
	 */
	WREG32_PCIE(smnPCIE_PERF_COUNT_CNTL, 0x00000002);

	/* Read रेजिस्टर values to get any >32bit overflow */
	पंचांगp = RREG32_PCIE(smnPCIE_PERF_CNTL_TXCLK);
	cnt0_of = REG_GET_FIELD(पंचांगp, PCIE_PERF_CNTL_TXCLK, COUNTER0_UPPER);
	cnt1_of = REG_GET_FIELD(पंचांगp, PCIE_PERF_CNTL_TXCLK, COUNTER1_UPPER);

	/* Get the values and add the overflow */
	*count0 = RREG32_PCIE(smnPCIE_PERF_COUNT0_TXCLK) | (cnt0_of << 32);
	*count1 = RREG32_PCIE(smnPCIE_PERF_COUNT1_TXCLK) | (cnt1_of << 32);
पूर्ण

अटल व्योम vega20_get_pcie_usage(काष्ठा amdgpu_device *adev, uपूर्णांक64_t *count0,
				 uपूर्णांक64_t *count1)
अणु
	uपूर्णांक32_t perfctr = 0;
	uपूर्णांक64_t cnt0_of, cnt1_of;
	पूर्णांक पंचांगp;

	/* This reports 0 on APUs, so वापस to aव्योम writing/पढ़ोing रेजिस्टरs
	 * that may or may not be dअगरferent from their GPU counterparts
	 */
	अगर (adev->flags & AMD_IS_APU)
		वापस;

	/* Set the 2 events that we wish to watch, defined above */
	/* Reg 40 is # received msgs */
	/* Reg 108 is # of posted requests sent on VG20 */
	perfctr = REG_SET_FIELD(perfctr, PCIE_PERF_CNTL_TXCLK3,
				EVENT0_SEL, 40);
	perfctr = REG_SET_FIELD(perfctr, PCIE_PERF_CNTL_TXCLK3,
				EVENT1_SEL, 108);

	/* Write to enable desired perf counters */
	WREG32_PCIE(smnPCIE_PERF_CNTL_TXCLK3, perfctr);
	/* Zero out and enable the perf counters
	 * Write 0x5:
	 * Bit 0 = Start all counters(1)
	 * Bit 2 = Global counter reset enable(1)
	 */
	WREG32_PCIE(smnPCIE_PERF_COUNT_CNTL, 0x00000005);

	msleep(1000);

	/* Load the shaकरोw and disable the perf counters
	 * Write 0x2:
	 * Bit 0 = Stop counters(0)
	 * Bit 1 = Load the shaकरोw counters(1)
	 */
	WREG32_PCIE(smnPCIE_PERF_COUNT_CNTL, 0x00000002);

	/* Read रेजिस्टर values to get any >32bit overflow */
	पंचांगp = RREG32_PCIE(smnPCIE_PERF_CNTL_TXCLK3);
	cnt0_of = REG_GET_FIELD(पंचांगp, PCIE_PERF_CNTL_TXCLK3, COUNTER0_UPPER);
	cnt1_of = REG_GET_FIELD(पंचांगp, PCIE_PERF_CNTL_TXCLK3, COUNTER1_UPPER);

	/* Get the values and add the overflow */
	*count0 = RREG32_PCIE(smnPCIE_PERF_COUNT0_TXCLK3) | (cnt0_of << 32);
	*count1 = RREG32_PCIE(smnPCIE_PERF_COUNT1_TXCLK3) | (cnt1_of << 32);
पूर्ण

अटल bool soc15_need_reset_on_init(काष्ठा amdgpu_device *adev)
अणु
	u32 sol_reg;

	/* Just वापस false क्रम soc15 GPUs.  Reset करोes not seem to
	 * be necessary.
	 */
	अगर (!amdgpu_passthrough(adev))
		वापस false;

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

अटल uपूर्णांक64_t soc15_get_pcie_replay_count(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t nak_r, nak_g;

	/* Get the number of NAKs received and generated */
	nak_r = RREG32_PCIE(smnPCIE_RX_NUM_NAK);
	nak_g = RREG32_PCIE(smnPCIE_RX_NUM_NAK_GENERATED);

	/* Add the total number of NAKs, i.e the number of replays */
	वापस (nak_r + nak_g);
पूर्ण

अटल व्योम soc15_pre_asic_init(काष्ठा amdgpu_device *adev)
अणु
	gmc_v9_0_restore_रेजिस्टरs(adev);
पूर्ण

अटल स्थिर काष्ठा amdgpu_asic_funcs soc15_asic_funcs =
अणु
	.पढ़ो_disabled_bios = &soc15_पढ़ो_disabled_bios,
	.पढ़ो_bios_from_rom = &soc15_पढ़ो_bios_from_rom,
	.पढ़ो_रेजिस्टर = &soc15_पढ़ो_रेजिस्टर,
	.reset = &soc15_asic_reset,
	.reset_method = &soc15_asic_reset_method,
	.set_vga_state = &soc15_vga_set_state,
	.get_xclk = &soc15_get_xclk,
	.set_uvd_घड़ीs = &soc15_set_uvd_घड़ीs,
	.set_vce_घड़ीs = &soc15_set_vce_घड़ीs,
	.get_config_memsize = &soc15_get_config_memsize,
	.need_full_reset = &soc15_need_full_reset,
	.init_करोorbell_index = &vega10_करोorbell_index_init,
	.get_pcie_usage = &soc15_get_pcie_usage,
	.need_reset_on_init = &soc15_need_reset_on_init,
	.get_pcie_replay_count = &soc15_get_pcie_replay_count,
	.supports_baco = &soc15_supports_baco,
	.pre_asic_init = &soc15_pre_asic_init,
	.query_video_codecs = &soc15_query_video_codecs,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_asic_funcs vega20_asic_funcs =
अणु
	.पढ़ो_disabled_bios = &soc15_पढ़ो_disabled_bios,
	.पढ़ो_bios_from_rom = &soc15_पढ़ो_bios_from_rom,
	.पढ़ो_रेजिस्टर = &soc15_पढ़ो_रेजिस्टर,
	.reset = &soc15_asic_reset,
	.reset_method = &soc15_asic_reset_method,
	.set_vga_state = &soc15_vga_set_state,
	.get_xclk = &soc15_get_xclk,
	.set_uvd_घड़ीs = &soc15_set_uvd_घड़ीs,
	.set_vce_घड़ीs = &soc15_set_vce_घड़ीs,
	.get_config_memsize = &soc15_get_config_memsize,
	.need_full_reset = &soc15_need_full_reset,
	.init_करोorbell_index = &vega20_करोorbell_index_init,
	.get_pcie_usage = &vega20_get_pcie_usage,
	.need_reset_on_init = &soc15_need_reset_on_init,
	.get_pcie_replay_count = &soc15_get_pcie_replay_count,
	.supports_baco = &soc15_supports_baco,
	.pre_asic_init = &soc15_pre_asic_init,
	.query_video_codecs = &soc15_query_video_codecs,
पूर्ण;

अटल पूर्णांक soc15_common_early_init(व्योम *handle)
अणु
#घोषणा MMIO_REG_HOLE_OFFSET (0x80000 - PAGE_SIZE)
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->rmmio_remap.reg_offset = MMIO_REG_HOLE_OFFSET;
	adev->rmmio_remap.bus_addr = adev->rmmio_base + MMIO_REG_HOLE_OFFSET;
	adev->smc_rreg = शून्य;
	adev->smc_wreg = शून्य;
	adev->pcie_rreg = &soc15_pcie_rreg;
	adev->pcie_wreg = &soc15_pcie_wreg;
	adev->pcie_rreg64 = &soc15_pcie_rreg64;
	adev->pcie_wreg64 = &soc15_pcie_wreg64;
	adev->uvd_ctx_rreg = &soc15_uvd_ctx_rreg;
	adev->uvd_ctx_wreg = &soc15_uvd_ctx_wreg;
	adev->didt_rreg = &soc15_didt_rreg;
	adev->didt_wreg = &soc15_didt_wreg;
	adev->gc_cac_rreg = &soc15_gc_cac_rreg;
	adev->gc_cac_wreg = &soc15_gc_cac_wreg;
	adev->se_cac_rreg = &soc15_se_cac_rreg;
	adev->se_cac_wreg = &soc15_se_cac_wreg;


	adev->बाह्यal_rev_id = 0xFF;
	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA10:
		adev->asic_funcs = &soc15_asic_funcs;
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			AMD_CG_SUPPORT_GFX_RLC_LS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_GFX_3D_CGCG |
			AMD_CG_SUPPORT_GFX_3D_CGLS |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_BIF_MGCG |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_DRM_MGCG |
			AMD_CG_SUPPORT_DRM_LS |
			AMD_CG_SUPPORT_ROM_MGCG |
			AMD_CG_SUPPORT_DF_MGCG |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_MC_LS;
		adev->pg_flags = 0;
		adev->बाह्यal_rev_id = 0x1;
		अवरोध;
	हाल CHIP_VEGA12:
		adev->asic_funcs = &soc15_asic_funcs;
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_3D_CGCG |
			AMD_CG_SUPPORT_GFX_3D_CGLS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_BIF_MGCG |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_HDP_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_ROM_MGCG |
			AMD_CG_SUPPORT_VCE_MGCG |
			AMD_CG_SUPPORT_UVD_MGCG;
		adev->pg_flags = 0;
		adev->बाह्यal_rev_id = adev->rev_id + 0x14;
		अवरोध;
	हाल CHIP_VEGA20:
		adev->asic_funcs = &vega20_asic_funcs;
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_3D_CGCG |
			AMD_CG_SUPPORT_GFX_3D_CGLS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_BIF_MGCG |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_HDP_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_ROM_MGCG |
			AMD_CG_SUPPORT_VCE_MGCG |
			AMD_CG_SUPPORT_UVD_MGCG;
		adev->pg_flags = 0;
		adev->बाह्यal_rev_id = adev->rev_id + 0x28;
		अवरोध;
	हाल CHIP_RAVEN:
		adev->asic_funcs = &soc15_asic_funcs;
		अगर (adev->pdev->device == 0x15dd)
			adev->apu_flags |= AMD_APU_IS_RAVEN;
		अगर (adev->pdev->device == 0x15d8)
			adev->apu_flags |= AMD_APU_IS_PICASSO;
		अगर (adev->rev_id >= 0x8)
			adev->apu_flags |= AMD_APU_IS_RAVEN2;

		अगर (adev->apu_flags & AMD_APU_IS_RAVEN2)
			adev->बाह्यal_rev_id = adev->rev_id + 0x79;
		अन्यथा अगर (adev->apu_flags & AMD_APU_IS_PICASSO)
			adev->बाह्यal_rev_id = adev->rev_id + 0x41;
		अन्यथा अगर (adev->rev_id == 1)
			adev->बाह्यal_rev_id = adev->rev_id + 0x20;
		अन्यथा
			adev->बाह्यal_rev_id = adev->rev_id + 0x01;

		अगर (adev->apu_flags & AMD_APU_IS_RAVEN2) अणु
			adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
				AMD_CG_SUPPORT_GFX_MGLS |
				AMD_CG_SUPPORT_GFX_CP_LS |
				AMD_CG_SUPPORT_GFX_3D_CGCG |
				AMD_CG_SUPPORT_GFX_3D_CGLS |
				AMD_CG_SUPPORT_GFX_CGCG |
				AMD_CG_SUPPORT_GFX_CGLS |
				AMD_CG_SUPPORT_BIF_LS |
				AMD_CG_SUPPORT_HDP_LS |
				AMD_CG_SUPPORT_MC_MGCG |
				AMD_CG_SUPPORT_MC_LS |
				AMD_CG_SUPPORT_SDMA_MGCG |
				AMD_CG_SUPPORT_SDMA_LS |
				AMD_CG_SUPPORT_VCN_MGCG;

			adev->pg_flags = AMD_PG_SUPPORT_SDMA | AMD_PG_SUPPORT_VCN;
		पूर्ण अन्यथा अगर (adev->apu_flags & AMD_APU_IS_PICASSO) अणु
			adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
				AMD_CG_SUPPORT_GFX_MGLS |
				AMD_CG_SUPPORT_GFX_CP_LS |
				AMD_CG_SUPPORT_GFX_3D_CGLS |
				AMD_CG_SUPPORT_GFX_CGCG |
				AMD_CG_SUPPORT_GFX_CGLS |
				AMD_CG_SUPPORT_BIF_LS |
				AMD_CG_SUPPORT_HDP_LS |
				AMD_CG_SUPPORT_MC_MGCG |
				AMD_CG_SUPPORT_MC_LS |
				AMD_CG_SUPPORT_SDMA_MGCG |
				AMD_CG_SUPPORT_SDMA_LS |
				AMD_CG_SUPPORT_VCN_MGCG;

			adev->pg_flags = AMD_PG_SUPPORT_SDMA |
				AMD_PG_SUPPORT_MMHUB |
				AMD_PG_SUPPORT_VCN;
		पूर्ण अन्यथा अणु
			adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
				AMD_CG_SUPPORT_GFX_MGLS |
				AMD_CG_SUPPORT_GFX_RLC_LS |
				AMD_CG_SUPPORT_GFX_CP_LS |
				AMD_CG_SUPPORT_GFX_3D_CGLS |
				AMD_CG_SUPPORT_GFX_CGCG |
				AMD_CG_SUPPORT_GFX_CGLS |
				AMD_CG_SUPPORT_BIF_MGCG |
				AMD_CG_SUPPORT_BIF_LS |
				AMD_CG_SUPPORT_HDP_MGCG |
				AMD_CG_SUPPORT_HDP_LS |
				AMD_CG_SUPPORT_DRM_MGCG |
				AMD_CG_SUPPORT_DRM_LS |
				AMD_CG_SUPPORT_MC_MGCG |
				AMD_CG_SUPPORT_MC_LS |
				AMD_CG_SUPPORT_SDMA_MGCG |
				AMD_CG_SUPPORT_SDMA_LS |
				AMD_CG_SUPPORT_VCN_MGCG;

			adev->pg_flags = AMD_PG_SUPPORT_SDMA | AMD_PG_SUPPORT_VCN;
		पूर्ण
		अवरोध;
	हाल CHIP_ARCTURUS:
		adev->asic_funcs = &vega20_asic_funcs;
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_HDP_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_IH_CG |
			AMD_CG_SUPPORT_VCN_MGCG |
			AMD_CG_SUPPORT_JPEG_MGCG;
		adev->pg_flags = AMD_PG_SUPPORT_VCN | AMD_PG_SUPPORT_VCN_DPG;
		adev->बाह्यal_rev_id = adev->rev_id + 0x32;
		अवरोध;
	हाल CHIP_RENOIR:
		adev->asic_funcs = &soc15_asic_funcs;
		अगर ((adev->pdev->device == 0x1636) ||
		    (adev->pdev->device == 0x164c))
			adev->apu_flags |= AMD_APU_IS_RENOIR;
		अन्यथा
			adev->apu_flags |= AMD_APU_IS_GREEN_SARDINE;

		अगर (adev->apu_flags & AMD_APU_IS_RENOIR)
			adev->बाह्यal_rev_id = adev->rev_id + 0x91;
		अन्यथा
			adev->बाह्यal_rev_id = adev->rev_id + 0xa1;
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
				 AMD_CG_SUPPORT_GFX_MGLS |
				 AMD_CG_SUPPORT_GFX_3D_CGCG |
				 AMD_CG_SUPPORT_GFX_3D_CGLS |
				 AMD_CG_SUPPORT_GFX_CGCG |
				 AMD_CG_SUPPORT_GFX_CGLS |
				 AMD_CG_SUPPORT_GFX_CP_LS |
				 AMD_CG_SUPPORT_MC_MGCG |
				 AMD_CG_SUPPORT_MC_LS |
				 AMD_CG_SUPPORT_SDMA_MGCG |
				 AMD_CG_SUPPORT_SDMA_LS |
				 AMD_CG_SUPPORT_BIF_LS |
				 AMD_CG_SUPPORT_HDP_LS |
				 AMD_CG_SUPPORT_VCN_MGCG |
				 AMD_CG_SUPPORT_JPEG_MGCG |
				 AMD_CG_SUPPORT_IH_CG |
				 AMD_CG_SUPPORT_ATHUB_LS |
				 AMD_CG_SUPPORT_ATHUB_MGCG |
				 AMD_CG_SUPPORT_DF_MGCG;
		adev->pg_flags = AMD_PG_SUPPORT_SDMA |
				 AMD_PG_SUPPORT_VCN |
				 AMD_PG_SUPPORT_JPEG |
				 AMD_PG_SUPPORT_VCN_DPG;
		अवरोध;
	हाल CHIP_ALDEBARAN:
		adev->asic_funcs = &vega20_asic_funcs;
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_IH_CG |
			AMD_CG_SUPPORT_VCN_MGCG | AMD_CG_SUPPORT_JPEG_MGCG;
		adev->pg_flags = AMD_PG_SUPPORT_VCN_DPG;
		adev->बाह्यal_rev_id = adev->rev_id + 0x3c;
		अवरोध;
	शेष:
		/* FIXME: not supported yet */
		वापस -EINVAL;
	पूर्ण

	अगर (amdgpu_sriov_vf(adev)) अणु
		amdgpu_virt_init_setting(adev);
		xgpu_ai_mailbox_set_irq_funcs(adev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक soc15_common_late_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r = 0;

	अगर (amdgpu_sriov_vf(adev))
		xgpu_ai_mailbox_get_irq(adev);

	अगर (adev->hdp.funcs->reset_ras_error_count)
		adev->hdp.funcs->reset_ras_error_count(adev);

	अगर (adev->nbio.ras_funcs &&
	    adev->nbio.ras_funcs->ras_late_init)
		r = adev->nbio.ras_funcs->ras_late_init(adev);

	वापस r;
पूर्ण

अटल पूर्णांक soc15_common_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev))
		xgpu_ai_mailbox_add_irq_id(adev);

	adev->df.funcs->sw_init(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक soc15_common_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (adev->nbio.ras_funcs &&
	    adev->nbio.ras_funcs->ras_fini)
		adev->nbio.ras_funcs->ras_fini(adev);
	adev->df.funcs->sw_fini(adev);
	वापस 0;
पूर्ण

अटल व्योम soc15_करोorbell_range_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;
	काष्ठा amdgpu_ring *ring;

	/* sdma/ih करोorbell range are programed by hypervisor */
	अगर (!amdgpu_sriov_vf(adev)) अणु
		क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
			ring = &adev->sdma.instance[i].ring;
			adev->nbio.funcs->sdma_करोorbell_range(adev, i,
				ring->use_करोorbell, ring->करोorbell_index,
				adev->करोorbell_index.sdma_करोorbell_range);
		पूर्ण

		adev->nbio.funcs->ih_करोorbell_range(adev, adev->irq.ih.use_करोorbell,
						adev->irq.ih.करोorbell_index);
	पूर्ण
पूर्ण

अटल पूर्णांक soc15_common_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* enable pcie gen2/3 link */
	soc15_pcie_gen3_enable(adev);
	/* enable aspm */
	soc15_program_aspm(adev);
	/* setup nbio रेजिस्टरs */
	adev->nbio.funcs->init_रेजिस्टरs(adev);
	/* remap HDP रेजिस्टरs to a hole in mmio space,
	 * क्रम the purpose of expose those रेजिस्टरs
	 * to process space
	 */
	अगर (adev->nbio.funcs->remap_hdp_रेजिस्टरs)
		adev->nbio.funcs->remap_hdp_रेजिस्टरs(adev);

	/* enable the करोorbell aperture */
	soc15_enable_करोorbell_aperture(adev, true);
	/* HW करोorbell routing policy: करोorbell writing not
	 * in SDMA/IH/MM/ACV range will be routed to CP. So
	 * we need to init SDMA/IH/MM/ACV करोorbell range prior
	 * to CP ip block init and ring test.
	 */
	soc15_करोorbell_range_init(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक soc15_common_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* disable the करोorbell aperture */
	soc15_enable_करोorbell_aperture(adev, false);
	अगर (amdgpu_sriov_vf(adev))
		xgpu_ai_mailbox_put_irq(adev);

	अगर (adev->nbio.ras_अगर &&
	    amdgpu_ras_is_supported(adev, adev->nbio.ras_अगर->block)) अणु
		अगर (adev->nbio.ras_funcs &&
		    adev->nbio.ras_funcs->init_ras_controller_पूर्णांकerrupt)
			amdgpu_irq_put(adev, &adev->nbio.ras_controller_irq, 0);
		अगर (adev->nbio.ras_funcs &&
		    adev->nbio.ras_funcs->init_ras_err_event_athub_पूर्णांकerrupt)
			amdgpu_irq_put(adev, &adev->nbio.ras_err_event_athub_irq, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक soc15_common_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस soc15_common_hw_fini(adev);
पूर्ण

अटल पूर्णांक soc15_common_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस soc15_common_hw_init(adev);
पूर्ण

अटल bool soc15_common_is_idle(व्योम *handle)
अणु
	वापस true;
पूर्ण

अटल पूर्णांक soc15_common_रुको_क्रम_idle(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक soc15_common_soft_reset(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल व्योम soc15_update_drm_घड़ी_gating(काष्ठा amdgpu_device *adev, bool enable)
अणु
	uपूर्णांक32_t def, data;

	def = data = RREG32(SOC15_REG_OFFSET(MP0, 0, mmMP0_MISC_CGTT_CTRL0));

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_DRM_MGCG))
		data &= ~(0x01000000 |
			  0x02000000 |
			  0x04000000 |
			  0x08000000 |
			  0x10000000 |
			  0x20000000 |
			  0x40000000 |
			  0x80000000);
	अन्यथा
		data |= (0x01000000 |
			 0x02000000 |
			 0x04000000 |
			 0x08000000 |
			 0x10000000 |
			 0x20000000 |
			 0x40000000 |
			 0x80000000);

	अगर (def != data)
		WREG32(SOC15_REG_OFFSET(MP0, 0, mmMP0_MISC_CGTT_CTRL0), data);
पूर्ण

अटल व्योम soc15_update_drm_light_sleep(काष्ठा amdgpu_device *adev, bool enable)
अणु
	uपूर्णांक32_t def, data;

	def = data = RREG32(SOC15_REG_OFFSET(MP0, 0, mmMP0_MISC_LIGHT_SLEEP_CTRL));

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_DRM_LS))
		data |= 1;
	अन्यथा
		data &= ~1;

	अगर (def != data)
		WREG32(SOC15_REG_OFFSET(MP0, 0, mmMP0_MISC_LIGHT_SLEEP_CTRL), data);
पूर्ण

अटल पूर्णांक soc15_common_set_घड़ीgating_state(व्योम *handle,
					    क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA12:
	हाल CHIP_VEGA20:
		adev->nbio.funcs->update_medium_grain_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		adev->nbio.funcs->update_medium_grain_light_sleep(adev,
				state == AMD_CG_STATE_GATE);
		adev->hdp.funcs->update_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		soc15_update_drm_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		soc15_update_drm_light_sleep(adev,
				state == AMD_CG_STATE_GATE);
		adev->smuio.funcs->update_rom_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		adev->df.funcs->update_medium_grain_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		अवरोध;
	हाल CHIP_RAVEN:
	हाल CHIP_RENOIR:
		adev->nbio.funcs->update_medium_grain_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		adev->nbio.funcs->update_medium_grain_light_sleep(adev,
				state == AMD_CG_STATE_GATE);
		adev->hdp.funcs->update_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		soc15_update_drm_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		soc15_update_drm_light_sleep(adev,
				state == AMD_CG_STATE_GATE);
		अवरोध;
	हाल CHIP_ARCTURUS:
	हाल CHIP_ALDEBARAN:
		adev->hdp.funcs->update_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम soc15_common_get_घड़ीgating_state(व्योम *handle, u32 *flags)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक data;

	अगर (amdgpu_sriov_vf(adev))
		*flags = 0;

	adev->nbio.funcs->get_घड़ीgating_state(adev, flags);

	adev->hdp.funcs->get_घड़ी_gating_state(adev, flags);

	अगर (adev->asic_type != CHIP_ALDEBARAN) अणु

		/* AMD_CG_SUPPORT_DRM_MGCG */
		data = RREG32(SOC15_REG_OFFSET(MP0, 0, mmMP0_MISC_CGTT_CTRL0));
		अगर (!(data & 0x01000000))
			*flags |= AMD_CG_SUPPORT_DRM_MGCG;

		/* AMD_CG_SUPPORT_DRM_LS */
		data = RREG32(SOC15_REG_OFFSET(MP0, 0, mmMP0_MISC_LIGHT_SLEEP_CTRL));
		अगर (data & 0x1)
			*flags |= AMD_CG_SUPPORT_DRM_LS;
	पूर्ण

	/* AMD_CG_SUPPORT_ROM_MGCG */
	adev->smuio.funcs->get_घड़ी_gating_state(adev, flags);

	adev->df.funcs->get_घड़ीgating_state(adev, flags);
पूर्ण

अटल पूर्णांक soc15_common_set_घातergating_state(व्योम *handle,
					    क्रमागत amd_घातergating_state state)
अणु
	/* toकरो */
	वापस 0;
पूर्ण

स्थिर काष्ठा amd_ip_funcs soc15_common_ip_funcs = अणु
	.name = "soc15_common",
	.early_init = soc15_common_early_init,
	.late_init = soc15_common_late_init,
	.sw_init = soc15_common_sw_init,
	.sw_fini = soc15_common_sw_fini,
	.hw_init = soc15_common_hw_init,
	.hw_fini = soc15_common_hw_fini,
	.suspend = soc15_common_suspend,
	.resume = soc15_common_resume,
	.is_idle = soc15_common_is_idle,
	.रुको_क्रम_idle = soc15_common_रुको_क्रम_idle,
	.soft_reset = soc15_common_soft_reset,
	.set_घड़ीgating_state = soc15_common_set_घड़ीgating_state,
	.set_घातergating_state = soc15_common_set_घातergating_state,
	.get_घड़ीgating_state= soc15_common_get_घड़ीgating_state,
पूर्ण;
