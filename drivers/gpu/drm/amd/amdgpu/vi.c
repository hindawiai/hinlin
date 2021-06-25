<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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

#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <drm/amdgpu_drm.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_atombios.h"
#समावेश "amdgpu_ih.h"
#समावेश "amdgpu_uvd.h"
#समावेश "amdgpu_vce.h"
#समावेश "amdgpu_ucode.h"
#समावेश "atom.h"
#समावेश "amd_pcie.h"

#समावेश "gmc/gmc_8_1_d.h"
#समावेश "gmc/gmc_8_1_sh_mask.h"

#समावेश "oss/oss_3_0_d.h"
#समावेश "oss/oss_3_0_sh_mask.h"

#समावेश "bif/bif_5_0_d.h"
#समावेश "bif/bif_5_0_sh_mask.h"

#समावेश "gca/gfx_8_0_d.h"
#समावेश "gca/gfx_8_0_sh_mask.h"

#समावेश "smu/smu_7_1_1_d.h"
#समावेश "smu/smu_7_1_1_sh_mask.h"

#समावेश "uvd/uvd_5_0_d.h"
#समावेश "uvd/uvd_5_0_sh_mask.h"

#समावेश "vce/vce_3_0_d.h"
#समावेश "vce/vce_3_0_sh_mask.h"

#समावेश "dce/dce_10_0_d.h"
#समावेश "dce/dce_10_0_sh_mask.h"

#समावेश "vid.h"
#समावेश "vi.h"
#समावेश "gmc_v8_0.h"
#समावेश "gmc_v7_0.h"
#समावेश "gfx_v8_0.h"
#समावेश "sdma_v2_4.h"
#समावेश "sdma_v3_0.h"
#समावेश "dce_v10_0.h"
#समावेश "dce_v11_0.h"
#समावेश "iceland_ih.h"
#समावेश "tonga_ih.h"
#समावेश "cz_ih.h"
#समावेश "uvd_v5_0.h"
#समावेश "uvd_v6_0.h"
#समावेश "vce_v3_0.h"
#अगर defined(CONFIG_DRM_AMD_ACP)
#समावेश "amdgpu_acp.h"
#पूर्ण_अगर
#समावेश "dce_virtual.h"
#समावेश "mxgpu_vi.h"
#समावेश "amdgpu_dm.h"

#घोषणा ixPCIE_LC_L1_PM_SUBSTATE	0x100100C6
#घोषणा PCIE_LC_L1_PM_SUBSTATE__LC_L1_SUBSTATES_OVERRIDE_EN_MASK	0x00000001L
#घोषणा PCIE_LC_L1_PM_SUBSTATE__LC_PCI_PM_L1_2_OVERRIDE_MASK	0x00000002L
#घोषणा PCIE_LC_L1_PM_SUBSTATE__LC_PCI_PM_L1_1_OVERRIDE_MASK	0x00000004L
#घोषणा PCIE_LC_L1_PM_SUBSTATE__LC_ASPM_L1_2_OVERRIDE_MASK		0x00000008L
#घोषणा PCIE_LC_L1_PM_SUBSTATE__LC_ASPM_L1_1_OVERRIDE_MASK		0x00000010L
#घोषणा ixPCIE_L1_PM_SUB_CNTL	0x378
#घोषणा PCIE_L1_PM_SUB_CNTL__ASPM_L1_2_EN_MASK	0x00000004L
#घोषणा PCIE_L1_PM_SUB_CNTL__ASPM_L1_1_EN_MASK	0x00000008L
#घोषणा PCIE_L1_PM_SUB_CNTL__PCI_PM_L1_2_EN_MASK	0x00000001L
#घोषणा PCIE_L1_PM_SUB_CNTL__PCI_PM_L1_1_EN_MASK	0x00000002L
#घोषणा PCIE_LC_CNTL6__LC_L1_POWERDOWN_MASK		0x00200000L
#घोषणा LINK_CAP	0x64
#घोषणा PCIE_LINK_CAP__CLOCK_POWER_MANAGEMENT_MASK	0x00040000L
#घोषणा ixCPM_CONTROL	0x1400118
#घोषणा ixPCIE_LC_CNTL7	0x100100BC
#घोषणा PCIE_LC_CNTL7__LC_L1_SIDEBAND_CLKREQ_PDWN_EN_MASK	0x00000400L
#घोषणा PCIE_LC_CNTL__LC_L0S_INACTIVITY_DEFAULT	0x00000007
#घोषणा PCIE_LC_CNTL__LC_L1_INACTIVITY_DEFAULT	0x00000009
#घोषणा CPM_CONTROL__CLKREQb_UNGATE_TXCLK_ENABLE_MASK	0x01000000L
#घोषणा PCIE_L1_PM_SUB_CNTL	0x378
#घोषणा ASIC_IS_P22(asic_type, rid)	((asic_type >= CHIP_POLARIS10) && \
									(asic_type <= CHIP_POLARIS12) && \
									(rid >= 0x6E))
/* Topaz */
अटल स्थिर काष्ठा amdgpu_video_codecs topaz_video_codecs_encode =
अणु
	.codec_count = 0,
	.codec_array = शून्य,
पूर्ण;

/* Tonga, CZ, ST, Fiji */
अटल स्थिर काष्ठा amdgpu_video_codec_info tonga_video_codecs_encode_array[] =
अणु
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC,
		.max_width = 4096,
		.max_height = 2304,
		.max_pixels_per_frame = 4096 * 2304,
		.max_level = 0,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_video_codecs tonga_video_codecs_encode =
अणु
	.codec_count = ARRAY_SIZE(tonga_video_codecs_encode_array),
	.codec_array = tonga_video_codecs_encode_array,
पूर्ण;

/* Polaris */
अटल स्थिर काष्ठा amdgpu_video_codec_info polaris_video_codecs_encode_array[] =
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

अटल स्थिर काष्ठा amdgpu_video_codecs polaris_video_codecs_encode =
अणु
	.codec_count = ARRAY_SIZE(polaris_video_codecs_encode_array),
	.codec_array = polaris_video_codecs_encode_array,
पूर्ण;

/* Topaz */
अटल स्थिर काष्ठा amdgpu_video_codecs topaz_video_codecs_decode =
अणु
	.codec_count = 0,
	.codec_array = शून्य,
पूर्ण;

/* Tonga */
अटल स्थिर काष्ठा amdgpu_video_codec_info tonga_video_codecs_decode_array[] =
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
पूर्ण;

अटल स्थिर काष्ठा amdgpu_video_codecs tonga_video_codecs_decode =
अणु
	.codec_count = ARRAY_SIZE(tonga_video_codecs_decode_array),
	.codec_array = tonga_video_codecs_decode_array,
पूर्ण;

/* CZ, ST, Fiji, Polaris */
अटल स्थिर काष्ठा amdgpu_video_codec_info cz_video_codecs_decode_array[] =
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

अटल स्थिर काष्ठा amdgpu_video_codecs cz_video_codecs_decode =
अणु
	.codec_count = ARRAY_SIZE(cz_video_codecs_decode_array),
	.codec_array = cz_video_codecs_decode_array,
पूर्ण;

अटल पूर्णांक vi_query_video_codecs(काष्ठा amdgpu_device *adev, bool encode,
				 स्थिर काष्ठा amdgpu_video_codecs **codecs)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_TOPAZ:
		अगर (encode)
			*codecs = &topaz_video_codecs_encode;
		अन्यथा
			*codecs = &topaz_video_codecs_decode;
		वापस 0;
	हाल CHIP_TONGA:
		अगर (encode)
			*codecs = &tonga_video_codecs_encode;
		अन्यथा
			*codecs = &tonga_video_codecs_decode;
		वापस 0;
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
		अगर (encode)
			*codecs = &polaris_video_codecs_encode;
		अन्यथा
			*codecs = &cz_video_codecs_decode;
		वापस 0;
	हाल CHIP_FIJI:
	हाल CHIP_CARRIZO:
	हाल CHIP_STONEY:
		अगर (encode)
			*codecs = &tonga_video_codecs_encode;
		अन्यथा
			*codecs = &cz_video_codecs_decode;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * Indirect रेजिस्टरs accessor
 */
अटल u32 vi_pcie_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32_NO_KIQ(mmPCIE_INDEX, reg);
	(व्योम)RREG32_NO_KIQ(mmPCIE_INDEX);
	r = RREG32_NO_KIQ(mmPCIE_DATA);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम vi_pcie_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32_NO_KIQ(mmPCIE_INDEX, reg);
	(व्योम)RREG32_NO_KIQ(mmPCIE_INDEX);
	WREG32_NO_KIQ(mmPCIE_DATA, v);
	(व्योम)RREG32_NO_KIQ(mmPCIE_DATA);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
पूर्ण

अटल u32 vi_smc_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->smc_idx_lock, flags);
	WREG32_NO_KIQ(mmSMC_IND_INDEX_11, (reg));
	r = RREG32_NO_KIQ(mmSMC_IND_DATA_11);
	spin_unlock_irqrestore(&adev->smc_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम vi_smc_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->smc_idx_lock, flags);
	WREG32_NO_KIQ(mmSMC_IND_INDEX_11, (reg));
	WREG32_NO_KIQ(mmSMC_IND_DATA_11, (v));
	spin_unlock_irqrestore(&adev->smc_idx_lock, flags);
पूर्ण

/* smu_8_0_d.h */
#घोषणा mmMP0PUB_IND_INDEX                                                      0x180
#घोषणा mmMP0PUB_IND_DATA                                                       0x181

अटल u32 cz_smc_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->smc_idx_lock, flags);
	WREG32(mmMP0PUB_IND_INDEX, (reg));
	r = RREG32(mmMP0PUB_IND_DATA);
	spin_unlock_irqrestore(&adev->smc_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम cz_smc_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->smc_idx_lock, flags);
	WREG32(mmMP0PUB_IND_INDEX, (reg));
	WREG32(mmMP0PUB_IND_DATA, (v));
	spin_unlock_irqrestore(&adev->smc_idx_lock, flags);
पूर्ण

अटल u32 vi_uvd_ctx_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->uvd_ctx_idx_lock, flags);
	WREG32(mmUVD_CTX_INDEX, ((reg) & 0x1ff));
	r = RREG32(mmUVD_CTX_DATA);
	spin_unlock_irqrestore(&adev->uvd_ctx_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम vi_uvd_ctx_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->uvd_ctx_idx_lock, flags);
	WREG32(mmUVD_CTX_INDEX, ((reg) & 0x1ff));
	WREG32(mmUVD_CTX_DATA, (v));
	spin_unlock_irqrestore(&adev->uvd_ctx_idx_lock, flags);
पूर्ण

अटल u32 vi_didt_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->didt_idx_lock, flags);
	WREG32(mmDIDT_IND_INDEX, (reg));
	r = RREG32(mmDIDT_IND_DATA);
	spin_unlock_irqrestore(&adev->didt_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम vi_didt_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->didt_idx_lock, flags);
	WREG32(mmDIDT_IND_INDEX, (reg));
	WREG32(mmDIDT_IND_DATA, (v));
	spin_unlock_irqrestore(&adev->didt_idx_lock, flags);
पूर्ण

अटल u32 vi_gc_cac_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->gc_cac_idx_lock, flags);
	WREG32(mmGC_CAC_IND_INDEX, (reg));
	r = RREG32(mmGC_CAC_IND_DATA);
	spin_unlock_irqrestore(&adev->gc_cac_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम vi_gc_cac_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->gc_cac_idx_lock, flags);
	WREG32(mmGC_CAC_IND_INDEX, (reg));
	WREG32(mmGC_CAC_IND_DATA, (v));
	spin_unlock_irqrestore(&adev->gc_cac_idx_lock, flags);
पूर्ण


अटल स्थिर u32 tonga_mgcg_cgcg_init[] =
अणु
	mmCGTT_DRM_CLK_CTRL0, 0xffffffff, 0x00600100,
	mmPCIE_INDEX, 0xffffffff, 0x0140001c,
	mmPCIE_DATA, 0x000f0000, 0x00000000,
	mmSMC_IND_INDEX_4, 0xffffffff, 0xC060000C,
	mmSMC_IND_DATA_4, 0xc0000fff, 0x00000100,
	mmCGTT_DRM_CLK_CTRL0, 0xff000fff, 0x00000100,
	mmHDP_XDP_CGTT_BLK_CTRL, 0xc0000fff, 0x00000104,
पूर्ण;

अटल स्थिर u32 fiji_mgcg_cgcg_init[] =
अणु
	mmCGTT_DRM_CLK_CTRL0, 0xffffffff, 0x00600100,
	mmPCIE_INDEX, 0xffffffff, 0x0140001c,
	mmPCIE_DATA, 0x000f0000, 0x00000000,
	mmSMC_IND_INDEX_4, 0xffffffff, 0xC060000C,
	mmSMC_IND_DATA_4, 0xc0000fff, 0x00000100,
	mmCGTT_DRM_CLK_CTRL0, 0xff000fff, 0x00000100,
	mmHDP_XDP_CGTT_BLK_CTRL, 0xc0000fff, 0x00000104,
पूर्ण;

अटल स्थिर u32 iceland_mgcg_cgcg_init[] =
अणु
	mmPCIE_INDEX, 0xffffffff, ixPCIE_CNTL2,
	mmPCIE_DATA, 0x000f0000, 0x00000000,
	mmSMC_IND_INDEX_4, 0xffffffff, ixCGTT_ROM_CLK_CTRL0,
	mmSMC_IND_DATA_4, 0xc0000fff, 0x00000100,
	mmHDP_XDP_CGTT_BLK_CTRL, 0xc0000fff, 0x00000104,
पूर्ण;

अटल स्थिर u32 cz_mgcg_cgcg_init[] =
अणु
	mmCGTT_DRM_CLK_CTRL0, 0xffffffff, 0x00600100,
	mmPCIE_INDEX, 0xffffffff, 0x0140001c,
	mmPCIE_DATA, 0x000f0000, 0x00000000,
	mmCGTT_DRM_CLK_CTRL0, 0xff000fff, 0x00000100,
	mmHDP_XDP_CGTT_BLK_CTRL, 0xc0000fff, 0x00000104,
पूर्ण;

अटल स्थिर u32 stoney_mgcg_cgcg_init[] =
अणु
	mmCGTT_DRM_CLK_CTRL0, 0xffffffff, 0x00000100,
	mmHDP_XDP_CGTT_BLK_CTRL, 0xffffffff, 0x00000104,
	mmHDP_HOST_PATH_CNTL, 0xffffffff, 0x0f000027,
पूर्ण;

अटल व्योम vi_init_golden_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	/* Some of the रेजिस्टरs might be dependent on GRBM_GFX_INDEX */
	mutex_lock(&adev->grbm_idx_mutex);

	अगर (amdgpu_sriov_vf(adev)) अणु
		xgpu_vi_init_golden_रेजिस्टरs(adev);
		mutex_unlock(&adev->grbm_idx_mutex);
		वापस;
	पूर्ण

	चयन (adev->asic_type) अणु
	हाल CHIP_TOPAZ:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							iceland_mgcg_cgcg_init,
							ARRAY_SIZE(iceland_mgcg_cgcg_init));
		अवरोध;
	हाल CHIP_FIJI:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							fiji_mgcg_cgcg_init,
							ARRAY_SIZE(fiji_mgcg_cgcg_init));
		अवरोध;
	हाल CHIP_TONGA:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							tonga_mgcg_cgcg_init,
							ARRAY_SIZE(tonga_mgcg_cgcg_init));
		अवरोध;
	हाल CHIP_CARRIZO:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							cz_mgcg_cgcg_init,
							ARRAY_SIZE(cz_mgcg_cgcg_init));
		अवरोध;
	हाल CHIP_STONEY:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							stoney_mgcg_cgcg_init,
							ARRAY_SIZE(stoney_mgcg_cgcg_init));
		अवरोध;
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&adev->grbm_idx_mutex);
पूर्ण

/**
 * vi_get_xclk - get the xclk
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Returns the reference घड़ी used by the gfx engine
 * (VI).
 */
अटल u32 vi_get_xclk(काष्ठा amdgpu_device *adev)
अणु
	u32 reference_घड़ी = adev->घड़ी.spll.reference_freq;
	u32 पंचांगp;

	अगर (adev->flags & AMD_IS_APU)
		वापस reference_घड़ी;

	पंचांगp = RREG32_SMC(ixCG_CLKPIN_CNTL_2);
	अगर (REG_GET_FIELD(पंचांगp, CG_CLKPIN_CNTL_2, MUX_TCLK_TO_XCLK))
		वापस 1000;

	पंचांगp = RREG32_SMC(ixCG_CLKPIN_CNTL);
	अगर (REG_GET_FIELD(पंचांगp, CG_CLKPIN_CNTL, XTALIN_DIVIDE))
		वापस reference_घड़ी / 4;

	वापस reference_घड़ी;
पूर्ण

/**
 * vi_srbm_select - select specअगरic रेजिस्टर instances
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @me: selected ME (micro engine)
 * @pipe: pipe
 * @queue: queue
 * @vmid: VMID
 *
 * Switches the currently active रेजिस्टरs instances.  Some
 * रेजिस्टरs are instanced per VMID, others are instanced per
 * me/pipe/queue combination.
 */
व्योम vi_srbm_select(काष्ठा amdgpu_device *adev,
		     u32 me, u32 pipe, u32 queue, u32 vmid)
अणु
	u32 srbm_gfx_cntl = 0;
	srbm_gfx_cntl = REG_SET_FIELD(srbm_gfx_cntl, SRBM_GFX_CNTL, PIPEID, pipe);
	srbm_gfx_cntl = REG_SET_FIELD(srbm_gfx_cntl, SRBM_GFX_CNTL, MEID, me);
	srbm_gfx_cntl = REG_SET_FIELD(srbm_gfx_cntl, SRBM_GFX_CNTL, VMID, vmid);
	srbm_gfx_cntl = REG_SET_FIELD(srbm_gfx_cntl, SRBM_GFX_CNTL, QUEUEID, queue);
	WREG32(mmSRBM_GFX_CNTL, srbm_gfx_cntl);
पूर्ण

अटल व्योम vi_vga_set_state(काष्ठा amdgpu_device *adev, bool state)
अणु
	/* toकरो */
पूर्ण

अटल bool vi_पढ़ो_disabled_bios(काष्ठा amdgpu_device *adev)
अणु
	u32 bus_cntl;
	u32 d1vga_control = 0;
	u32 d2vga_control = 0;
	u32 vga_render_control = 0;
	u32 rom_cntl;
	bool r;

	bus_cntl = RREG32(mmBUS_CNTL);
	अगर (adev->mode_info.num_crtc) अणु
		d1vga_control = RREG32(mmD1VGA_CONTROL);
		d2vga_control = RREG32(mmD2VGA_CONTROL);
		vga_render_control = RREG32(mmVGA_RENDER_CONTROL);
	पूर्ण
	rom_cntl = RREG32_SMC(ixROM_CNTL);

	/* enable the rom */
	WREG32(mmBUS_CNTL, (bus_cntl & ~BUS_CNTL__BIOS_ROM_DIS_MASK));
	अगर (adev->mode_info.num_crtc) अणु
		/* Disable VGA mode */
		WREG32(mmD1VGA_CONTROL,
		       (d1vga_control & ~(D1VGA_CONTROL__D1VGA_MODE_ENABLE_MASK |
					  D1VGA_CONTROL__D1VGA_TIMING_SELECT_MASK)));
		WREG32(mmD2VGA_CONTROL,
		       (d2vga_control & ~(D2VGA_CONTROL__D2VGA_MODE_ENABLE_MASK |
					  D2VGA_CONTROL__D2VGA_TIMING_SELECT_MASK)));
		WREG32(mmVGA_RENDER_CONTROL,
		       (vga_render_control & ~VGA_RENDER_CONTROL__VGA_VSTATUS_CNTL_MASK));
	पूर्ण
	WREG32_SMC(ixROM_CNTL, rom_cntl | ROM_CNTL__SCK_OVERWRITE_MASK);

	r = amdgpu_पढ़ो_bios(adev);

	/* restore regs */
	WREG32(mmBUS_CNTL, bus_cntl);
	अगर (adev->mode_info.num_crtc) अणु
		WREG32(mmD1VGA_CONTROL, d1vga_control);
		WREG32(mmD2VGA_CONTROL, d2vga_control);
		WREG32(mmVGA_RENDER_CONTROL, vga_render_control);
	पूर्ण
	WREG32_SMC(ixROM_CNTL, rom_cntl);
	वापस r;
पूर्ण

अटल bool vi_पढ़ो_bios_from_rom(काष्ठा amdgpu_device *adev,
				  u8 *bios, u32 length_bytes)
अणु
	u32 *dw_ptr;
	अचिन्हित दीर्घ flags;
	u32 i, length_dw;

	अगर (bios == शून्य)
		वापस false;
	अगर (length_bytes == 0)
		वापस false;
	/* APU vbios image is part of sbios image */
	अगर (adev->flags & AMD_IS_APU)
		वापस false;

	dw_ptr = (u32 *)bios;
	length_dw = ALIGN(length_bytes, 4) / 4;
	/* take the smc lock since we are using the smc index */
	spin_lock_irqsave(&adev->smc_idx_lock, flags);
	/* set rom index to 0 */
	WREG32(mmSMC_IND_INDEX_11, ixROM_INDEX);
	WREG32(mmSMC_IND_DATA_11, 0);
	/* set index to data क्रम continous पढ़ो */
	WREG32(mmSMC_IND_INDEX_11, ixROM_DATA);
	क्रम (i = 0; i < length_dw; i++)
		dw_ptr[i] = RREG32(mmSMC_IND_DATA_11);
	spin_unlock_irqrestore(&adev->smc_idx_lock, flags);

	वापस true;
पूर्ण

अटल स्थिर काष्ठा amdgpu_allowed_रेजिस्टर_entry vi_allowed_पढ़ो_रेजिस्टरs[] = अणु
	अणुmmGRBM_STATUSपूर्ण,
	अणुmmGRBM_STATUS2पूर्ण,
	अणुmmGRBM_STATUS_SE0पूर्ण,
	अणुmmGRBM_STATUS_SE1पूर्ण,
	अणुmmGRBM_STATUS_SE2पूर्ण,
	अणुmmGRBM_STATUS_SE3पूर्ण,
	अणुmmSRBM_STATUSपूर्ण,
	अणुmmSRBM_STATUS2पूर्ण,
	अणुmmSRBM_STATUS3पूर्ण,
	अणुmmSDMA0_STATUS_REG + SDMA0_REGISTER_OFFSETपूर्ण,
	अणुmmSDMA0_STATUS_REG + SDMA1_REGISTER_OFFSETपूर्ण,
	अणुmmCP_STATपूर्ण,
	अणुmmCP_STALLED_STAT1पूर्ण,
	अणुmmCP_STALLED_STAT2पूर्ण,
	अणुmmCP_STALLED_STAT3पूर्ण,
	अणुmmCP_CPF_BUSY_STATपूर्ण,
	अणुmmCP_CPF_STALLED_STAT1पूर्ण,
	अणुmmCP_CPF_STATUSपूर्ण,
	अणुmmCP_CPC_BUSY_STATपूर्ण,
	अणुmmCP_CPC_STALLED_STAT1पूर्ण,
	अणुmmCP_CPC_STATUSपूर्ण,
	अणुmmGB_ADDR_CONFIGपूर्ण,
	अणुmmMC_ARB_RAMCFGपूर्ण,
	अणुmmGB_TILE_MODE0पूर्ण,
	अणुmmGB_TILE_MODE1पूर्ण,
	अणुmmGB_TILE_MODE2पूर्ण,
	अणुmmGB_TILE_MODE3पूर्ण,
	अणुmmGB_TILE_MODE4पूर्ण,
	अणुmmGB_TILE_MODE5पूर्ण,
	अणुmmGB_TILE_MODE6पूर्ण,
	अणुmmGB_TILE_MODE7पूर्ण,
	अणुmmGB_TILE_MODE8पूर्ण,
	अणुmmGB_TILE_MODE9पूर्ण,
	अणुmmGB_TILE_MODE10पूर्ण,
	अणुmmGB_TILE_MODE11पूर्ण,
	अणुmmGB_TILE_MODE12पूर्ण,
	अणुmmGB_TILE_MODE13पूर्ण,
	अणुmmGB_TILE_MODE14पूर्ण,
	अणुmmGB_TILE_MODE15पूर्ण,
	अणुmmGB_TILE_MODE16पूर्ण,
	अणुmmGB_TILE_MODE17पूर्ण,
	अणुmmGB_TILE_MODE18पूर्ण,
	अणुmmGB_TILE_MODE19पूर्ण,
	अणुmmGB_TILE_MODE20पूर्ण,
	अणुmmGB_TILE_MODE21पूर्ण,
	अणुmmGB_TILE_MODE22पूर्ण,
	अणुmmGB_TILE_MODE23पूर्ण,
	अणुmmGB_TILE_MODE24पूर्ण,
	अणुmmGB_TILE_MODE25पूर्ण,
	अणुmmGB_TILE_MODE26पूर्ण,
	अणुmmGB_TILE_MODE27पूर्ण,
	अणुmmGB_TILE_MODE28पूर्ण,
	अणुmmGB_TILE_MODE29पूर्ण,
	अणुmmGB_TILE_MODE30पूर्ण,
	अणुmmGB_TILE_MODE31पूर्ण,
	अणुmmGB_MACROTILE_MODE0पूर्ण,
	अणुmmGB_MACROTILE_MODE1पूर्ण,
	अणुmmGB_MACROTILE_MODE2पूर्ण,
	अणुmmGB_MACROTILE_MODE3पूर्ण,
	अणुmmGB_MACROTILE_MODE4पूर्ण,
	अणुmmGB_MACROTILE_MODE5पूर्ण,
	अणुmmGB_MACROTILE_MODE6पूर्ण,
	अणुmmGB_MACROTILE_MODE7पूर्ण,
	अणुmmGB_MACROTILE_MODE8पूर्ण,
	अणुmmGB_MACROTILE_MODE9पूर्ण,
	अणुmmGB_MACROTILE_MODE10पूर्ण,
	अणुmmGB_MACROTILE_MODE11पूर्ण,
	अणुmmGB_MACROTILE_MODE12पूर्ण,
	अणुmmGB_MACROTILE_MODE13पूर्ण,
	अणुmmGB_MACROTILE_MODE14पूर्ण,
	अणुmmGB_MACROTILE_MODE15पूर्ण,
	अणुmmCC_RB_BACKEND_DISABLE, trueपूर्ण,
	अणुmmGC_USER_RB_BACKEND_DISABLE, trueपूर्ण,
	अणुmmGB_BACKEND_MAP, falseपूर्ण,
	अणुmmPA_SC_RASTER_CONFIG, trueपूर्ण,
	अणुmmPA_SC_RASTER_CONFIG_1, trueपूर्ण,
पूर्ण;

अटल uपूर्णांक32_t vi_get_रेजिस्टर_value(काष्ठा amdgpu_device *adev,
				      bool indexed, u32 se_num,
				      u32 sh_num, u32 reg_offset)
अणु
	अगर (indexed) अणु
		uपूर्णांक32_t val;
		अचिन्हित se_idx = (se_num == 0xffffffff) ? 0 : se_num;
		अचिन्हित sh_idx = (sh_num == 0xffffffff) ? 0 : sh_num;

		चयन (reg_offset) अणु
		हाल mmCC_RB_BACKEND_DISABLE:
			वापस adev->gfx.config.rb_config[se_idx][sh_idx].rb_backend_disable;
		हाल mmGC_USER_RB_BACKEND_DISABLE:
			वापस adev->gfx.config.rb_config[se_idx][sh_idx].user_rb_backend_disable;
		हाल mmPA_SC_RASTER_CONFIG:
			वापस adev->gfx.config.rb_config[se_idx][sh_idx].raster_config;
		हाल mmPA_SC_RASTER_CONFIG_1:
			वापस adev->gfx.config.rb_config[se_idx][sh_idx].raster_config_1;
		पूर्ण

		mutex_lock(&adev->grbm_idx_mutex);
		अगर (se_num != 0xffffffff || sh_num != 0xffffffff)
			amdgpu_gfx_select_se_sh(adev, se_num, sh_num, 0xffffffff);

		val = RREG32(reg_offset);

		अगर (se_num != 0xffffffff || sh_num != 0xffffffff)
			amdgpu_gfx_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
		mutex_unlock(&adev->grbm_idx_mutex);
		वापस val;
	पूर्ण अन्यथा अणु
		अचिन्हित idx;

		चयन (reg_offset) अणु
		हाल mmGB_ADDR_CONFIG:
			वापस adev->gfx.config.gb_addr_config;
		हाल mmMC_ARB_RAMCFG:
			वापस adev->gfx.config.mc_arb_ramcfg;
		हाल mmGB_TILE_MODE0:
		हाल mmGB_TILE_MODE1:
		हाल mmGB_TILE_MODE2:
		हाल mmGB_TILE_MODE3:
		हाल mmGB_TILE_MODE4:
		हाल mmGB_TILE_MODE5:
		हाल mmGB_TILE_MODE6:
		हाल mmGB_TILE_MODE7:
		हाल mmGB_TILE_MODE8:
		हाल mmGB_TILE_MODE9:
		हाल mmGB_TILE_MODE10:
		हाल mmGB_TILE_MODE11:
		हाल mmGB_TILE_MODE12:
		हाल mmGB_TILE_MODE13:
		हाल mmGB_TILE_MODE14:
		हाल mmGB_TILE_MODE15:
		हाल mmGB_TILE_MODE16:
		हाल mmGB_TILE_MODE17:
		हाल mmGB_TILE_MODE18:
		हाल mmGB_TILE_MODE19:
		हाल mmGB_TILE_MODE20:
		हाल mmGB_TILE_MODE21:
		हाल mmGB_TILE_MODE22:
		हाल mmGB_TILE_MODE23:
		हाल mmGB_TILE_MODE24:
		हाल mmGB_TILE_MODE25:
		हाल mmGB_TILE_MODE26:
		हाल mmGB_TILE_MODE27:
		हाल mmGB_TILE_MODE28:
		हाल mmGB_TILE_MODE29:
		हाल mmGB_TILE_MODE30:
		हाल mmGB_TILE_MODE31:
			idx = (reg_offset - mmGB_TILE_MODE0);
			वापस adev->gfx.config.tile_mode_array[idx];
		हाल mmGB_MACROTILE_MODE0:
		हाल mmGB_MACROTILE_MODE1:
		हाल mmGB_MACROTILE_MODE2:
		हाल mmGB_MACROTILE_MODE3:
		हाल mmGB_MACROTILE_MODE4:
		हाल mmGB_MACROTILE_MODE5:
		हाल mmGB_MACROTILE_MODE6:
		हाल mmGB_MACROTILE_MODE7:
		हाल mmGB_MACROTILE_MODE8:
		हाल mmGB_MACROTILE_MODE9:
		हाल mmGB_MACROTILE_MODE10:
		हाल mmGB_MACROTILE_MODE11:
		हाल mmGB_MACROTILE_MODE12:
		हाल mmGB_MACROTILE_MODE13:
		हाल mmGB_MACROTILE_MODE14:
		हाल mmGB_MACROTILE_MODE15:
			idx = (reg_offset - mmGB_MACROTILE_MODE0);
			वापस adev->gfx.config.macrotile_mode_array[idx];
		शेष:
			वापस RREG32(reg_offset);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक vi_पढ़ो_रेजिस्टर(काष्ठा amdgpu_device *adev, u32 se_num,
			    u32 sh_num, u32 reg_offset, u32 *value)
अणु
	uपूर्णांक32_t i;

	*value = 0;
	क्रम (i = 0; i < ARRAY_SIZE(vi_allowed_पढ़ो_रेजिस्टरs); i++) अणु
		bool indexed = vi_allowed_पढ़ो_रेजिस्टरs[i].grbm_indexed;

		अगर (reg_offset != vi_allowed_पढ़ो_रेजिस्टरs[i].reg_offset)
			जारी;

		*value = vi_get_रेजिस्टर_value(adev, indexed, se_num, sh_num,
					       reg_offset);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/**
 * vi_asic_pci_config_reset - soft reset GPU
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Use PCI Config method to reset the GPU.
 *
 * Returns 0 क्रम success.
 */
अटल पूर्णांक vi_asic_pci_config_reset(काष्ठा amdgpu_device *adev)
अणु
	u32 i;
	पूर्णांक r = -EINVAL;

	amdgpu_atombios_scratch_regs_engine_hung(adev, true);

	/* disable BM */
	pci_clear_master(adev->pdev);
	/* reset */
	amdgpu_device_pci_config_reset(adev);

	udelay(100);

	/* रुको क्रम asic to come out of reset */
	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (RREG32(mmCONFIG_MEMSIZE) != 0xffffffff) अणु
			/* enable BM */
			pci_set_master(adev->pdev);
			adev->has_hw_reset = true;
			r = 0;
			अवरोध;
		पूर्ण
		udelay(1);
	पूर्ण

	amdgpu_atombios_scratch_regs_engine_hung(adev, false);

	वापस r;
पूर्ण

अटल bool vi_asic_supports_baco(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_FIJI:
	हाल CHIP_TONGA:
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_TOPAZ:
		वापस amdgpu_dpm_is_baco_supported(adev);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल क्रमागत amd_reset_method
vi_asic_reset_method(काष्ठा amdgpu_device *adev)
अणु
	bool baco_reset;

	अगर (amdgpu_reset_method == AMD_RESET_METHOD_LEGACY ||
	    amdgpu_reset_method == AMD_RESET_METHOD_BACO)
		वापस amdgpu_reset_method;

	अगर (amdgpu_reset_method != -1)
		dev_warn(adev->dev, "Specified reset method:%d isn't supported, using AUTO instead.\n",
				  amdgpu_reset_method);

	चयन (adev->asic_type) अणु
	हाल CHIP_FIJI:
	हाल CHIP_TONGA:
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_TOPAZ:
		baco_reset = amdgpu_dpm_is_baco_supported(adev);
		अवरोध;
	शेष:
		baco_reset = false;
		अवरोध;
	पूर्ण

	अगर (baco_reset)
		वापस AMD_RESET_METHOD_BACO;
	अन्यथा
		वापस AMD_RESET_METHOD_LEGACY;
पूर्ण

/**
 * vi_asic_reset - soft reset GPU
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Look up which blocks are hung and attempt
 * to reset them.
 * Returns 0 क्रम success.
 */
अटल पूर्णांक vi_asic_reset(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (vi_asic_reset_method(adev) == AMD_RESET_METHOD_BACO) अणु
		dev_info(adev->dev, "BACO reset\n");
		r = amdgpu_dpm_baco_reset(adev);
	पूर्ण अन्यथा अणु
		dev_info(adev->dev, "PCI CONFIG reset\n");
		r = vi_asic_pci_config_reset(adev);
	पूर्ण

	वापस r;
पूर्ण

अटल u32 vi_get_config_memsize(काष्ठा amdgpu_device *adev)
अणु
	वापस RREG32(mmCONFIG_MEMSIZE);
पूर्ण

अटल पूर्णांक vi_set_uvd_घड़ी(काष्ठा amdgpu_device *adev, u32 घड़ी,
			u32 cntl_reg, u32 status_reg)
अणु
	पूर्णांक r, i;
	काष्ठा atom_घड़ी_भागiders भागiders;
	uपूर्णांक32_t पंचांगp;

	r = amdgpu_atombios_get_घड़ी_भागiders(adev,
					       COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
					       घड़ी, false, &भागiders);
	अगर (r)
		वापस r;

	पंचांगp = RREG32_SMC(cntl_reg);

	अगर (adev->flags & AMD_IS_APU)
		पंचांगp &= ~CG_DCLK_CNTL__DCLK_DIVIDER_MASK;
	अन्यथा
		पंचांगp &= ~(CG_DCLK_CNTL__DCLK_सूची_CNTL_EN_MASK |
				CG_DCLK_CNTL__DCLK_DIVIDER_MASK);
	पंचांगp |= भागiders.post_भागider;
	WREG32_SMC(cntl_reg, पंचांगp);

	क्रम (i = 0; i < 100; i++) अणु
		पंचांगp = RREG32_SMC(status_reg);
		अगर (adev->flags & AMD_IS_APU) अणु
			अगर (पंचांगp & 0x10000)
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (पंचांगp & CG_DCLK_STATUS__DCLK_STATUS_MASK)
				अवरोध;
		पूर्ण
		mdelay(10);
	पूर्ण
	अगर (i == 100)
		वापस -ETIMEDOUT;
	वापस 0;
पूर्ण

#घोषणा ixGNB_CLK1_DFS_CNTL 0xD82200F0
#घोषणा ixGNB_CLK1_STATUS   0xD822010C
#घोषणा ixGNB_CLK2_DFS_CNTL 0xD8220110
#घोषणा ixGNB_CLK2_STATUS   0xD822012C
#घोषणा ixGNB_CLK3_DFS_CNTL 0xD8220130
#घोषणा ixGNB_CLK3_STATUS   0xD822014C

अटल पूर्णांक vi_set_uvd_घड़ीs(काष्ठा amdgpu_device *adev, u32 vclk, u32 dclk)
अणु
	पूर्णांक r;

	अगर (adev->flags & AMD_IS_APU) अणु
		r = vi_set_uvd_घड़ी(adev, vclk, ixGNB_CLK2_DFS_CNTL, ixGNB_CLK2_STATUS);
		अगर (r)
			वापस r;

		r = vi_set_uvd_घड़ी(adev, dclk, ixGNB_CLK1_DFS_CNTL, ixGNB_CLK1_STATUS);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अणु
		r = vi_set_uvd_घड़ी(adev, vclk, ixCG_VCLK_CNTL, ixCG_VCLK_STATUS);
		अगर (r)
			वापस r;

		r = vi_set_uvd_घड़ी(adev, dclk, ixCG_DCLK_CNTL, ixCG_DCLK_STATUS);
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vi_set_vce_घड़ीs(काष्ठा amdgpu_device *adev, u32 evclk, u32 ecclk)
अणु
	पूर्णांक r, i;
	काष्ठा atom_घड़ी_भागiders भागiders;
	u32 पंचांगp;
	u32 reg_ctrl;
	u32 reg_status;
	u32 status_mask;
	u32 reg_mask;

	अगर (adev->flags & AMD_IS_APU) अणु
		reg_ctrl = ixGNB_CLK3_DFS_CNTL;
		reg_status = ixGNB_CLK3_STATUS;
		status_mask = 0x00010000;
		reg_mask = CG_ECLK_CNTL__ECLK_DIVIDER_MASK;
	पूर्ण अन्यथा अणु
		reg_ctrl = ixCG_ECLK_CNTL;
		reg_status = ixCG_ECLK_STATUS;
		status_mask = CG_ECLK_STATUS__ECLK_STATUS_MASK;
		reg_mask = CG_ECLK_CNTL__ECLK_सूची_CNTL_EN_MASK | CG_ECLK_CNTL__ECLK_DIVIDER_MASK;
	पूर्ण

	r = amdgpu_atombios_get_घड़ी_भागiders(adev,
					       COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
					       ecclk, false, &भागiders);
	अगर (r)
		वापस r;

	क्रम (i = 0; i < 100; i++) अणु
		अगर (RREG32_SMC(reg_status) & status_mask)
			अवरोध;
		mdelay(10);
	पूर्ण

	अगर (i == 100)
		वापस -ETIMEDOUT;

	पंचांगp = RREG32_SMC(reg_ctrl);
	पंचांगp &= ~reg_mask;
	पंचांगp |= भागiders.post_भागider;
	WREG32_SMC(reg_ctrl, पंचांगp);

	क्रम (i = 0; i < 100; i++) अणु
		अगर (RREG32_SMC(reg_status) & status_mask)
			अवरोध;
		mdelay(10);
	पूर्ण

	अगर (i == 100)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल व्योम vi_pcie_gen3_enable(काष्ठा amdgpu_device *adev)
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

अटल व्योम vi_enable_aspm(काष्ठा amdgpu_device *adev)
अणु
	u32 data, orig;

	orig = data = RREG32_PCIE(ixPCIE_LC_CNTL);
	data |= PCIE_LC_CNTL__LC_L0S_INACTIVITY_DEFAULT <<
			PCIE_LC_CNTL__LC_L0S_INACTIVITY__SHIFT;
	data |= PCIE_LC_CNTL__LC_L1_INACTIVITY_DEFAULT <<
			PCIE_LC_CNTL__LC_L1_INACTIVITY__SHIFT;
	data &= ~PCIE_LC_CNTL__LC_PMI_TO_L1_DIS_MASK;
	data |= PCIE_LC_CNTL__LC_DELAY_L1_EXIT_MASK;
	अगर (orig != data)
		WREG32_PCIE(ixPCIE_LC_CNTL, data);
पूर्ण

अटल व्योम vi_program_aspm(काष्ठा amdgpu_device *adev)
अणु
	u32 data, data1, orig;
	bool bL1SS = false;
	bool bClkReqSupport = true;

	अगर (amdgpu_aspm != 1)
		वापस;

	अगर (adev->flags & AMD_IS_APU ||
	    adev->asic_type < CHIP_POLARIS10)
		वापस;

	orig = data = RREG32_PCIE(ixPCIE_LC_CNTL);
	data &= ~PCIE_LC_CNTL__LC_L1_INACTIVITY_MASK;
	data &= ~PCIE_LC_CNTL__LC_L0S_INACTIVITY_MASK;
	data |= PCIE_LC_CNTL__LC_PMI_TO_L1_DIS_MASK;
	अगर (orig != data)
		WREG32_PCIE(ixPCIE_LC_CNTL, data);

	orig = data = RREG32_PCIE(ixPCIE_LC_N_FTS_CNTL);
	data &= ~PCIE_LC_N_FTS_CNTL__LC_XMIT_N_FTS_MASK;
	data |= 0x0024 << PCIE_LC_N_FTS_CNTL__LC_XMIT_N_FTS__SHIFT;
	data |= PCIE_LC_N_FTS_CNTL__LC_XMIT_N_FTS_OVERRIDE_EN_MASK;
	अगर (orig != data)
		WREG32_PCIE(ixPCIE_LC_N_FTS_CNTL, data);

	orig = data = RREG32_PCIE(ixPCIE_LC_CNTL3);
	data |= PCIE_LC_CNTL3__LC_GO_TO_RECOVERY_MASK;
	अगर (orig != data)
		WREG32_PCIE(ixPCIE_LC_CNTL3, data);

	orig = data = RREG32_PCIE(ixPCIE_P_CNTL);
	data |= PCIE_P_CNTL__P_IGNORE_EDB_ERR_MASK;
	अगर (orig != data)
		WREG32_PCIE(ixPCIE_P_CNTL, data);

	data = RREG32_PCIE(ixPCIE_LC_L1_PM_SUBSTATE);
	pci_पढ़ो_config_dword(adev->pdev, PCIE_L1_PM_SUB_CNTL, &data1);
	अगर (data & PCIE_LC_L1_PM_SUBSTATE__LC_L1_SUBSTATES_OVERRIDE_EN_MASK &&
	    (data & (PCIE_LC_L1_PM_SUBSTATE__LC_PCI_PM_L1_2_OVERRIDE_MASK |
		    PCIE_LC_L1_PM_SUBSTATE__LC_PCI_PM_L1_1_OVERRIDE_MASK |
			PCIE_LC_L1_PM_SUBSTATE__LC_ASPM_L1_2_OVERRIDE_MASK |
			PCIE_LC_L1_PM_SUBSTATE__LC_ASPM_L1_1_OVERRIDE_MASK))) अणु
		bL1SS = true;
	पूर्ण अन्यथा अगर (data1 & (PCIE_L1_PM_SUB_CNTL__ASPM_L1_2_EN_MASK |
	    PCIE_L1_PM_SUB_CNTL__ASPM_L1_1_EN_MASK |
	    PCIE_L1_PM_SUB_CNTL__PCI_PM_L1_2_EN_MASK |
	    PCIE_L1_PM_SUB_CNTL__PCI_PM_L1_1_EN_MASK)) अणु
		bL1SS = true;
	पूर्ण

	orig = data = RREG32_PCIE(ixPCIE_LC_CNTL6);
	data |= PCIE_LC_CNTL6__LC_L1_POWERDOWN_MASK;
	अगर (orig != data)
		WREG32_PCIE(ixPCIE_LC_CNTL6, data);

	orig = data = RREG32_PCIE(ixPCIE_LC_LINK_WIDTH_CNTL);
	data |= PCIE_LC_LINK_WIDTH_CNTL__LC_DYN_LANES_PWR_STATE_MASK;
	अगर (orig != data)
		WREG32_PCIE(ixPCIE_LC_LINK_WIDTH_CNTL, data);

	pci_पढ़ो_config_dword(adev->pdev, LINK_CAP, &data);
	अगर (!(data & PCIE_LINK_CAP__CLOCK_POWER_MANAGEMENT_MASK))
		bClkReqSupport = false;

	अगर (bClkReqSupport) अणु
		orig = data = RREG32_SMC(ixTHM_CLK_CNTL);
		data &= ~(THM_CLK_CNTL__CMON_CLK_SEL_MASK | THM_CLK_CNTL__TMON_CLK_SEL_MASK);
		data |= (1 << THM_CLK_CNTL__CMON_CLK_SEL__SHIFT) |
				(1 << THM_CLK_CNTL__TMON_CLK_SEL__SHIFT);
		अगर (orig != data)
			WREG32_SMC(ixTHM_CLK_CNTL, data);

		orig = data = RREG32_SMC(ixMISC_CLK_CTRL);
		data &= ~(MISC_CLK_CTRL__DEEP_SLEEP_CLK_SEL_MASK |
			MISC_CLK_CTRL__ZCLK_SEL_MASK | MISC_CLK_CTRL__DFT_SMS_PG_CLK_SEL_MASK);
		data |= (1 << MISC_CLK_CTRL__DEEP_SLEEP_CLK_SEL__SHIFT) |
				(1 << MISC_CLK_CTRL__ZCLK_SEL__SHIFT);
		data |= (0x20 << MISC_CLK_CTRL__DFT_SMS_PG_CLK_SEL__SHIFT);
		अगर (orig != data)
			WREG32_SMC(ixMISC_CLK_CTRL, data);

		orig = data = RREG32_SMC(ixCG_CLKPIN_CNTL);
		data |= CG_CLKPIN_CNTL__XTALIN_DIVIDE_MASK;
		अगर (orig != data)
			WREG32_SMC(ixCG_CLKPIN_CNTL, data);

		orig = data = RREG32_SMC(ixCG_CLKPIN_CNTL_2);
		data |= CG_CLKPIN_CNTL_2__ENABLE_XCLK_MASK;
		अगर (orig != data)
			WREG32_SMC(ixCG_CLKPIN_CNTL, data);

		orig = data = RREG32_SMC(ixMPLL_BYPASSCLK_SEL);
		data &= ~MPLL_BYPASSCLK_SEL__MPLL_CLKOUT_SEL_MASK;
		data |= (4 << MPLL_BYPASSCLK_SEL__MPLL_CLKOUT_SEL__SHIFT);
		अगर (orig != data)
			WREG32_SMC(ixMPLL_BYPASSCLK_SEL, data);

		orig = data = RREG32_PCIE(ixCPM_CONTROL);
		data |= (CPM_CONTROL__REFCLK_XSTCLK_ENABLE_MASK |
				CPM_CONTROL__CLKREQb_UNGATE_TXCLK_ENABLE_MASK);
		अगर (orig != data)
			WREG32_PCIE(ixCPM_CONTROL, data);

		orig = data = RREG32_PCIE(ixPCIE_CONFIG_CNTL);
		data &= ~PCIE_CONFIG_CNTL__DYN_CLK_LATENCY_MASK;
		data |= (0xE << PCIE_CONFIG_CNTL__DYN_CLK_LATENCY__SHIFT);
		अगर (orig != data)
			WREG32_PCIE(ixPCIE_CONFIG_CNTL, data);

		orig = data = RREG32(mmBIF_CLK_CTRL);
		data |= BIF_CLK_CTRL__BIF_XSTCLK_READY_MASK;
		अगर (orig != data)
			WREG32(mmBIF_CLK_CTRL, data);

		orig = data = RREG32_PCIE(ixPCIE_LC_CNTL7);
		data |= PCIE_LC_CNTL7__LC_L1_SIDEBAND_CLKREQ_PDWN_EN_MASK;
		अगर (orig != data)
			WREG32_PCIE(ixPCIE_LC_CNTL7, data);

		orig = data = RREG32_PCIE(ixPCIE_HW_DEBUG);
		data |= PCIE_HW_DEBUG__HW_01_DEBUG_MASK;
		अगर (orig != data)
			WREG32_PCIE(ixPCIE_HW_DEBUG, data);

		orig = data = RREG32_PCIE(ixPCIE_LC_CNTL2);
		data |= PCIE_LC_CNTL2__LC_ALLOW_PDWN_IN_L23_MASK;
		data |= PCIE_LC_CNTL2__LC_ALLOW_PDWN_IN_L1_MASK;
		अगर (bL1SS)
			data &= ~PCIE_LC_CNTL2__LC_ALLOW_PDWN_IN_L1_MASK;
		अगर (orig != data)
			WREG32_PCIE(ixPCIE_LC_CNTL2, data);

	पूर्ण

	vi_enable_aspm(adev);

	data = RREG32_PCIE(ixPCIE_LC_N_FTS_CNTL);
	data1 = RREG32_PCIE(ixPCIE_LC_STATUS1);
	अगर (((data & PCIE_LC_N_FTS_CNTL__LC_N_FTS_MASK) == PCIE_LC_N_FTS_CNTL__LC_N_FTS_MASK) &&
	    data1 & PCIE_LC_STATUS1__LC_REVERSE_XMIT_MASK &&
	    data1 & PCIE_LC_STATUS1__LC_REVERSE_RCVR_MASK) अणु
		orig = data = RREG32_PCIE(ixPCIE_LC_CNTL);
		data &= ~PCIE_LC_CNTL__LC_L0S_INACTIVITY_MASK;
		अगर (orig != data)
			WREG32_PCIE(ixPCIE_LC_CNTL, data);
	पूर्ण

	अगर ((adev->asic_type == CHIP_POLARIS12 &&
	    !(ASICID_IS_P23(adev->pdev->device, adev->pdev->revision))) ||
	    ASIC_IS_P22(adev->asic_type, adev->बाह्यal_rev_id)) अणु
		orig = data = RREG32_PCIE(ixPCIE_LC_TRAINING_CNTL);
		data &= ~PCIE_LC_TRAINING_CNTL__LC_DISABLE_TRAINING_BIT_ARCH_MASK;
		अगर (orig != data)
			WREG32_PCIE(ixPCIE_LC_TRAINING_CNTL, data);
	पूर्ण
पूर्ण

अटल व्योम vi_enable_करोorbell_aperture(काष्ठा amdgpu_device *adev,
					bool enable)
अणु
	u32 पंचांगp;

	/* not necessary on CZ */
	अगर (adev->flags & AMD_IS_APU)
		वापस;

	पंचांगp = RREG32(mmBIF_DOORBELL_APER_EN);
	अगर (enable)
		पंचांगp = REG_SET_FIELD(पंचांगp, BIF_DOORBELL_APER_EN, BIF_DOORBELL_APER_EN, 1);
	अन्यथा
		पंचांगp = REG_SET_FIELD(पंचांगp, BIF_DOORBELL_APER_EN, BIF_DOORBELL_APER_EN, 0);

	WREG32(mmBIF_DOORBELL_APER_EN, पंचांगp);
पूर्ण

#घोषणा ATI_REV_ID_FUSE_MACRO__ADDRESS      0xC0014044
#घोषणा ATI_REV_ID_FUSE_MACRO__SHIFT        9
#घोषणा ATI_REV_ID_FUSE_MACRO__MASK         0x00001E00

अटल uपूर्णांक32_t vi_get_rev_id(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->flags & AMD_IS_APU)
		वापस (RREG32_SMC(ATI_REV_ID_FUSE_MACRO__ADDRESS) & ATI_REV_ID_FUSE_MACRO__MASK)
			>> ATI_REV_ID_FUSE_MACRO__SHIFT;
	अन्यथा
		वापस (RREG32(mmPCIE_EFUSE4) & PCIE_EFUSE4__STRAP_BIF_ATI_REV_ID_MASK)
			>> PCIE_EFUSE4__STRAP_BIF_ATI_REV_ID__SHIFT;
पूर्ण

अटल व्योम vi_flush_hdp(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ring *ring)
अणु
	अगर (!ring || !ring->funcs->emit_wreg) अणु
		WREG32(mmHDP_MEM_COHERENCY_FLUSH_CNTL, 1);
		RREG32(mmHDP_MEM_COHERENCY_FLUSH_CNTL);
	पूर्ण अन्यथा अणु
		amdgpu_ring_emit_wreg(ring, mmHDP_MEM_COHERENCY_FLUSH_CNTL, 1);
	पूर्ण
पूर्ण

अटल व्योम vi_invalidate_hdp(काष्ठा amdgpu_device *adev,
			      काष्ठा amdgpu_ring *ring)
अणु
	अगर (!ring || !ring->funcs->emit_wreg) अणु
		WREG32(mmHDP_DEBUG0, 1);
		RREG32(mmHDP_DEBUG0);
	पूर्ण अन्यथा अणु
		amdgpu_ring_emit_wreg(ring, mmHDP_DEBUG0, 1);
	पूर्ण
पूर्ण

अटल bool vi_need_full_reset(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_CARRIZO:
	हाल CHIP_STONEY:
		/* CZ has hang issues with full reset at the moment */
		वापस false;
	हाल CHIP_FIJI:
	हाल CHIP_TONGA:
		/* XXX: soft reset should work on fiji and tonga */
		वापस true;
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_TOPAZ:
	शेष:
		/* change this when we support soft reset */
		वापस true;
	पूर्ण
पूर्ण

अटल व्योम vi_get_pcie_usage(काष्ठा amdgpu_device *adev, uपूर्णांक64_t *count0,
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
	/* Reg 40 is # received msgs, Reg 104 is # of posted requests sent */
	perfctr = REG_SET_FIELD(perfctr, PCIE_PERF_CNTL_TXCLK, EVENT0_SEL, 40);
	perfctr = REG_SET_FIELD(perfctr, PCIE_PERF_CNTL_TXCLK, EVENT1_SEL, 104);

	/* Write to enable desired perf counters */
	WREG32_PCIE(ixPCIE_PERF_CNTL_TXCLK, perfctr);
	/* Zero out and enable the perf counters
	 * Write 0x5:
	 * Bit 0 = Start all counters(1)
	 * Bit 2 = Global counter reset enable(1)
	 */
	WREG32_PCIE(ixPCIE_PERF_COUNT_CNTL, 0x00000005);

	msleep(1000);

	/* Load the shaकरोw and disable the perf counters
	 * Write 0x2:
	 * Bit 0 = Stop counters(0)
	 * Bit 1 = Load the shaकरोw counters(1)
	 */
	WREG32_PCIE(ixPCIE_PERF_COUNT_CNTL, 0x00000002);

	/* Read रेजिस्टर values to get any >32bit overflow */
	पंचांगp = RREG32_PCIE(ixPCIE_PERF_CNTL_TXCLK);
	cnt0_of = REG_GET_FIELD(पंचांगp, PCIE_PERF_CNTL_TXCLK, COUNTER0_UPPER);
	cnt1_of = REG_GET_FIELD(पंचांगp, PCIE_PERF_CNTL_TXCLK, COUNTER1_UPPER);

	/* Get the values and add the overflow */
	*count0 = RREG32_PCIE(ixPCIE_PERF_COUNT0_TXCLK) | (cnt0_of << 32);
	*count1 = RREG32_PCIE(ixPCIE_PERF_COUNT1_TXCLK) | (cnt1_of << 32);
पूर्ण

अटल uपूर्णांक64_t vi_get_pcie_replay_count(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t nak_r, nak_g;

	/* Get the number of NAKs received and generated */
	nak_r = RREG32_PCIE(ixPCIE_RX_NUM_NAK);
	nak_g = RREG32_PCIE(ixPCIE_RX_NUM_NAK_GENERATED);

	/* Add the total number of NAKs, i.e the number of replays */
	वापस (nak_r + nak_g);
पूर्ण

अटल bool vi_need_reset_on_init(काष्ठा amdgpu_device *adev)
अणु
	u32 घड़ी_cntl, pc;

	अगर (adev->flags & AMD_IS_APU)
		वापस false;

	/* check अगर the SMC is alपढ़ोy running */
	घड़ी_cntl = RREG32_SMC(ixSMC_SYSCON_CLOCK_CNTL_0);
	pc = RREG32_SMC(ixSMC_PC_C);
	अगर ((0 == REG_GET_FIELD(घड़ी_cntl, SMC_SYSCON_CLOCK_CNTL_0, ck_disable)) &&
	    (0x20100 <= pc))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम vi_pre_asic_init(काष्ठा amdgpu_device *adev)
अणु
पूर्ण

अटल स्थिर काष्ठा amdgpu_asic_funcs vi_asic_funcs =
अणु
	.पढ़ो_disabled_bios = &vi_पढ़ो_disabled_bios,
	.पढ़ो_bios_from_rom = &vi_पढ़ो_bios_from_rom,
	.पढ़ो_रेजिस्टर = &vi_पढ़ो_रेजिस्टर,
	.reset = &vi_asic_reset,
	.reset_method = &vi_asic_reset_method,
	.set_vga_state = &vi_vga_set_state,
	.get_xclk = &vi_get_xclk,
	.set_uvd_घड़ीs = &vi_set_uvd_घड़ीs,
	.set_vce_घड़ीs = &vi_set_vce_घड़ीs,
	.get_config_memsize = &vi_get_config_memsize,
	.flush_hdp = &vi_flush_hdp,
	.invalidate_hdp = &vi_invalidate_hdp,
	.need_full_reset = &vi_need_full_reset,
	.init_करोorbell_index = &legacy_करोorbell_index_init,
	.get_pcie_usage = &vi_get_pcie_usage,
	.need_reset_on_init = &vi_need_reset_on_init,
	.get_pcie_replay_count = &vi_get_pcie_replay_count,
	.supports_baco = &vi_asic_supports_baco,
	.pre_asic_init = &vi_pre_asic_init,
	.query_video_codecs = &vi_query_video_codecs,
पूर्ण;

#घोषणा CZ_REV_BRISTOL(rev)	 \
	((rev >= 0xC8 && rev <= 0xCE) || (rev >= 0xE1 && rev <= 0xE6))

अटल पूर्णांक vi_common_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (adev->flags & AMD_IS_APU) अणु
		adev->smc_rreg = &cz_smc_rreg;
		adev->smc_wreg = &cz_smc_wreg;
	पूर्ण अन्यथा अणु
		adev->smc_rreg = &vi_smc_rreg;
		adev->smc_wreg = &vi_smc_wreg;
	पूर्ण
	adev->pcie_rreg = &vi_pcie_rreg;
	adev->pcie_wreg = &vi_pcie_wreg;
	adev->uvd_ctx_rreg = &vi_uvd_ctx_rreg;
	adev->uvd_ctx_wreg = &vi_uvd_ctx_wreg;
	adev->didt_rreg = &vi_didt_rreg;
	adev->didt_wreg = &vi_didt_wreg;
	adev->gc_cac_rreg = &vi_gc_cac_rreg;
	adev->gc_cac_wreg = &vi_gc_cac_wreg;

	adev->asic_funcs = &vi_asic_funcs;

	adev->rev_id = vi_get_rev_id(adev);
	adev->बाह्यal_rev_id = 0xFF;
	चयन (adev->asic_type) अणु
	हाल CHIP_TOPAZ:
		adev->cg_flags = 0;
		adev->pg_flags = 0;
		adev->बाह्यal_rev_id = 0x1;
		अवरोध;
	हाल CHIP_FIJI:
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			AMD_CG_SUPPORT_GFX_RLC_LS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_GFX_CGTS |
			AMD_CG_SUPPORT_GFX_CGTS_LS |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_HDP_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_ROM_MGCG |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_UVD_MGCG;
		adev->pg_flags = 0;
		adev->बाह्यal_rev_id = adev->rev_id + 0x3c;
		अवरोध;
	हाल CHIP_TONGA:
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_HDP_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_ROM_MGCG |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_DRM_LS |
			AMD_CG_SUPPORT_UVD_MGCG;
		adev->pg_flags = 0;
		adev->बाह्यal_rev_id = adev->rev_id + 0x14;
		अवरोध;
	हाल CHIP_POLARIS11:
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_RLC_LS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_3D_CGCG |
			AMD_CG_SUPPORT_GFX_3D_CGLS |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_BIF_MGCG |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_HDP_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_ROM_MGCG |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_DRM_LS |
			AMD_CG_SUPPORT_UVD_MGCG |
			AMD_CG_SUPPORT_VCE_MGCG;
		adev->pg_flags = 0;
		adev->बाह्यal_rev_id = adev->rev_id + 0x5A;
		अवरोध;
	हाल CHIP_POLARIS10:
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_RLC_LS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_3D_CGCG |
			AMD_CG_SUPPORT_GFX_3D_CGLS |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_BIF_MGCG |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_HDP_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_ROM_MGCG |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_DRM_LS |
			AMD_CG_SUPPORT_UVD_MGCG |
			AMD_CG_SUPPORT_VCE_MGCG;
		adev->pg_flags = 0;
		adev->बाह्यal_rev_id = adev->rev_id + 0x50;
		अवरोध;
	हाल CHIP_POLARIS12:
		adev->cg_flags = AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_RLC_LS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_3D_CGCG |
			AMD_CG_SUPPORT_GFX_3D_CGLS |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_BIF_MGCG |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_HDP_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_ROM_MGCG |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_DRM_LS |
			AMD_CG_SUPPORT_UVD_MGCG |
			AMD_CG_SUPPORT_VCE_MGCG;
		adev->pg_flags = 0;
		adev->बाह्यal_rev_id = adev->rev_id + 0x64;
		अवरोध;
	हाल CHIP_VEGAM:
		adev->cg_flags = 0;
			/*AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_RLC_LS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_3D_CGCG |
			AMD_CG_SUPPORT_GFX_3D_CGLS |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_BIF_MGCG |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_HDP_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_ROM_MGCG |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_DRM_LS |
			AMD_CG_SUPPORT_UVD_MGCG |
			AMD_CG_SUPPORT_VCE_MGCG;*/
		adev->pg_flags = 0;
		adev->बाह्यal_rev_id = adev->rev_id + 0x6E;
		अवरोध;
	हाल CHIP_CARRIZO:
		adev->cg_flags = AMD_CG_SUPPORT_UVD_MGCG |
			AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			AMD_CG_SUPPORT_GFX_RLC_LS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_GFX_CGTS |
			AMD_CG_SUPPORT_GFX_CGTS_LS |
			AMD_CG_SUPPORT_GFX_CGCG |
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_HDP_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_VCE_MGCG;
		/* rev0 hardware requires workarounds to support PG */
		adev->pg_flags = 0;
		अगर (adev->rev_id != 0x00 || CZ_REV_BRISTOL(adev->pdev->revision)) अणु
			adev->pg_flags |= AMD_PG_SUPPORT_GFX_SMG |
				AMD_PG_SUPPORT_GFX_PIPELINE |
				AMD_PG_SUPPORT_CP |
				AMD_PG_SUPPORT_UVD |
				AMD_PG_SUPPORT_VCE;
		पूर्ण
		adev->बाह्यal_rev_id = adev->rev_id + 0x1;
		अवरोध;
	हाल CHIP_STONEY:
		adev->cg_flags = AMD_CG_SUPPORT_UVD_MGCG |
			AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			AMD_CG_SUPPORT_GFX_RLC_LS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_GFX_CGTS |
			AMD_CG_SUPPORT_GFX_CGTS_LS |
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_HDP_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_VCE_MGCG;
		adev->pg_flags = AMD_PG_SUPPORT_GFX_PG |
			AMD_PG_SUPPORT_GFX_SMG |
			AMD_PG_SUPPORT_GFX_PIPELINE |
			AMD_PG_SUPPORT_CP |
			AMD_PG_SUPPORT_UVD |
			AMD_PG_SUPPORT_VCE;
		adev->बाह्यal_rev_id = adev->rev_id + 0x61;
		अवरोध;
	शेष:
		/* FIXME: not supported yet */
		वापस -EINVAL;
	पूर्ण

	अगर (amdgpu_sriov_vf(adev)) अणु
		amdgpu_virt_init_setting(adev);
		xgpu_vi_mailbox_set_irq_funcs(adev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vi_common_late_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev))
		xgpu_vi_mailbox_get_irq(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक vi_common_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev))
		xgpu_vi_mailbox_add_irq_id(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक vi_common_sw_fini(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vi_common_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* move the golden regs per IP block */
	vi_init_golden_रेजिस्टरs(adev);
	/* enable pcie gen2/3 link */
	vi_pcie_gen3_enable(adev);
	/* enable aspm */
	vi_program_aspm(adev);
	/* enable the करोorbell aperture */
	vi_enable_करोorbell_aperture(adev, true);

	वापस 0;
पूर्ण

अटल पूर्णांक vi_common_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* enable the करोorbell aperture */
	vi_enable_करोorbell_aperture(adev, false);

	अगर (amdgpu_sriov_vf(adev))
		xgpu_vi_mailbox_put_irq(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक vi_common_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस vi_common_hw_fini(adev);
पूर्ण

अटल पूर्णांक vi_common_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस vi_common_hw_init(adev);
पूर्ण

अटल bool vi_common_is_idle(व्योम *handle)
अणु
	वापस true;
पूर्ण

अटल पूर्णांक vi_common_रुको_क्रम_idle(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vi_common_soft_reset(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल व्योम vi_update_bअगर_medium_grain_light_sleep(काष्ठा amdgpu_device *adev,
						   bool enable)
अणु
	uपूर्णांक32_t temp, data;

	temp = data = RREG32_PCIE(ixPCIE_CNTL2);

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_BIF_LS))
		data |= PCIE_CNTL2__SLV_MEM_LS_EN_MASK |
				PCIE_CNTL2__MST_MEM_LS_EN_MASK |
				PCIE_CNTL2__REPLAY_MEM_LS_EN_MASK;
	अन्यथा
		data &= ~(PCIE_CNTL2__SLV_MEM_LS_EN_MASK |
				PCIE_CNTL2__MST_MEM_LS_EN_MASK |
				PCIE_CNTL2__REPLAY_MEM_LS_EN_MASK);

	अगर (temp != data)
		WREG32_PCIE(ixPCIE_CNTL2, data);
पूर्ण

अटल व्योम vi_update_hdp_medium_grain_घड़ी_gating(काष्ठा amdgpu_device *adev,
						    bool enable)
अणु
	uपूर्णांक32_t temp, data;

	temp = data = RREG32(mmHDP_HOST_PATH_CNTL);

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_HDP_MGCG))
		data &= ~HDP_HOST_PATH_CNTL__CLOCK_GATING_DIS_MASK;
	अन्यथा
		data |= HDP_HOST_PATH_CNTL__CLOCK_GATING_DIS_MASK;

	अगर (temp != data)
		WREG32(mmHDP_HOST_PATH_CNTL, data);
पूर्ण

अटल व्योम vi_update_hdp_light_sleep(काष्ठा amdgpu_device *adev,
				      bool enable)
अणु
	uपूर्णांक32_t temp, data;

	temp = data = RREG32(mmHDP_MEM_POWER_LS);

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_HDP_LS))
		data |= HDP_MEM_POWER_LS__LS_ENABLE_MASK;
	अन्यथा
		data &= ~HDP_MEM_POWER_LS__LS_ENABLE_MASK;

	अगर (temp != data)
		WREG32(mmHDP_MEM_POWER_LS, data);
पूर्ण

अटल व्योम vi_update_drm_light_sleep(काष्ठा amdgpu_device *adev,
				      bool enable)
अणु
	uपूर्णांक32_t temp, data;

	temp = data = RREG32(0x157a);

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_DRM_LS))
		data |= 1;
	अन्यथा
		data &= ~1;

	अगर (temp != data)
		WREG32(0x157a, data);
पूर्ण


अटल व्योम vi_update_rom_medium_grain_घड़ी_gating(काष्ठा amdgpu_device *adev,
						    bool enable)
अणु
	uपूर्णांक32_t temp, data;

	temp = data = RREG32_SMC(ixCGTT_ROM_CLK_CTRL0);

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_ROM_MGCG))
		data &= ~(CGTT_ROM_CLK_CTRL0__SOFT_OVERRIDE0_MASK |
				CGTT_ROM_CLK_CTRL0__SOFT_OVERRIDE1_MASK);
	अन्यथा
		data |= CGTT_ROM_CLK_CTRL0__SOFT_OVERRIDE0_MASK |
				CGTT_ROM_CLK_CTRL0__SOFT_OVERRIDE1_MASK;

	अगर (temp != data)
		WREG32_SMC(ixCGTT_ROM_CLK_CTRL0, data);
पूर्ण

अटल पूर्णांक vi_common_set_घड़ीgating_state_by_smu(व्योम *handle,
					   क्रमागत amd_घड़ीgating_state state)
अणु
	uपूर्णांक32_t msg_id, pp_state = 0;
	uपूर्णांक32_t pp_support_state = 0;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (adev->cg_flags & (AMD_CG_SUPPORT_MC_LS | AMD_CG_SUPPORT_MC_MGCG)) अणु
		अगर (adev->cg_flags & AMD_CG_SUPPORT_MC_LS) अणु
			pp_support_state = PP_STATE_SUPPORT_LS;
			pp_state = PP_STATE_LS;
		पूर्ण
		अगर (adev->cg_flags & AMD_CG_SUPPORT_MC_MGCG) अणु
			pp_support_state |= PP_STATE_SUPPORT_CG;
			pp_state |= PP_STATE_CG;
		पूर्ण
		अगर (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		msg_id = PP_CG_MSG_ID(PP_GROUP_SYS,
			       PP_BLOCK_SYS_MC,
			       pp_support_state,
			       pp_state);
		amdgpu_dpm_set_घड़ीgating_by_smu(adev, msg_id);
	पूर्ण

	अगर (adev->cg_flags & (AMD_CG_SUPPORT_SDMA_LS | AMD_CG_SUPPORT_SDMA_MGCG)) अणु
		अगर (adev->cg_flags & AMD_CG_SUPPORT_SDMA_LS) अणु
			pp_support_state = PP_STATE_SUPPORT_LS;
			pp_state = PP_STATE_LS;
		पूर्ण
		अगर (adev->cg_flags & AMD_CG_SUPPORT_SDMA_MGCG) अणु
			pp_support_state |= PP_STATE_SUPPORT_CG;
			pp_state |= PP_STATE_CG;
		पूर्ण
		अगर (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		msg_id = PP_CG_MSG_ID(PP_GROUP_SYS,
			       PP_BLOCK_SYS_SDMA,
			       pp_support_state,
			       pp_state);
		amdgpu_dpm_set_घड़ीgating_by_smu(adev, msg_id);
	पूर्ण

	अगर (adev->cg_flags & (AMD_CG_SUPPORT_HDP_LS | AMD_CG_SUPPORT_HDP_MGCG)) अणु
		अगर (adev->cg_flags & AMD_CG_SUPPORT_HDP_LS) अणु
			pp_support_state = PP_STATE_SUPPORT_LS;
			pp_state = PP_STATE_LS;
		पूर्ण
		अगर (adev->cg_flags & AMD_CG_SUPPORT_HDP_MGCG) अणु
			pp_support_state |= PP_STATE_SUPPORT_CG;
			pp_state |= PP_STATE_CG;
		पूर्ण
		अगर (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		msg_id = PP_CG_MSG_ID(PP_GROUP_SYS,
			       PP_BLOCK_SYS_HDP,
			       pp_support_state,
			       pp_state);
		amdgpu_dpm_set_घड़ीgating_by_smu(adev, msg_id);
	पूर्ण


	अगर (adev->cg_flags & AMD_CG_SUPPORT_BIF_LS) अणु
		अगर (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		अन्यथा
			pp_state = PP_STATE_LS;

		msg_id = PP_CG_MSG_ID(PP_GROUP_SYS,
			       PP_BLOCK_SYS_BIF,
			       PP_STATE_SUPPORT_LS,
			        pp_state);
		amdgpu_dpm_set_घड़ीgating_by_smu(adev, msg_id);
	पूर्ण
	अगर (adev->cg_flags & AMD_CG_SUPPORT_BIF_MGCG) अणु
		अगर (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		अन्यथा
			pp_state = PP_STATE_CG;

		msg_id = PP_CG_MSG_ID(PP_GROUP_SYS,
			       PP_BLOCK_SYS_BIF,
			       PP_STATE_SUPPORT_CG,
			       pp_state);
		amdgpu_dpm_set_घड़ीgating_by_smu(adev, msg_id);
	पूर्ण

	अगर (adev->cg_flags & AMD_CG_SUPPORT_DRM_LS) अणु

		अगर (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		अन्यथा
			pp_state = PP_STATE_LS;

		msg_id = PP_CG_MSG_ID(PP_GROUP_SYS,
			       PP_BLOCK_SYS_DRM,
			       PP_STATE_SUPPORT_LS,
			       pp_state);
		amdgpu_dpm_set_घड़ीgating_by_smu(adev, msg_id);
	पूर्ण

	अगर (adev->cg_flags & AMD_CG_SUPPORT_ROM_MGCG) अणु

		अगर (state == AMD_CG_STATE_UNGATE)
			pp_state = 0;
		अन्यथा
			pp_state = PP_STATE_CG;

		msg_id = PP_CG_MSG_ID(PP_GROUP_SYS,
			       PP_BLOCK_SYS_ROM,
			       PP_STATE_SUPPORT_CG,
			       pp_state);
		amdgpu_dpm_set_घड़ीgating_by_smu(adev, msg_id);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vi_common_set_घड़ीgating_state(व्योम *handle,
					   क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_FIJI:
		vi_update_bअगर_medium_grain_light_sleep(adev,
				state == AMD_CG_STATE_GATE);
		vi_update_hdp_medium_grain_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		vi_update_hdp_light_sleep(adev,
				state == AMD_CG_STATE_GATE);
		vi_update_rom_medium_grain_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		अवरोध;
	हाल CHIP_CARRIZO:
	हाल CHIP_STONEY:
		vi_update_bअगर_medium_grain_light_sleep(adev,
				state == AMD_CG_STATE_GATE);
		vi_update_hdp_medium_grain_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		vi_update_hdp_light_sleep(adev,
				state == AMD_CG_STATE_GATE);
		vi_update_drm_light_sleep(adev,
				state == AMD_CG_STATE_GATE);
		अवरोध;
	हाल CHIP_TONGA:
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
		vi_common_set_घड़ीgating_state_by_smu(adev, state);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vi_common_set_घातergating_state(व्योम *handle,
					    क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल व्योम vi_common_get_घड़ीgating_state(व्योम *handle, u32 *flags)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक data;

	अगर (amdgpu_sriov_vf(adev))
		*flags = 0;

	/* AMD_CG_SUPPORT_BIF_LS */
	data = RREG32_PCIE(ixPCIE_CNTL2);
	अगर (data & PCIE_CNTL2__SLV_MEM_LS_EN_MASK)
		*flags |= AMD_CG_SUPPORT_BIF_LS;

	/* AMD_CG_SUPPORT_HDP_LS */
	data = RREG32(mmHDP_MEM_POWER_LS);
	अगर (data & HDP_MEM_POWER_LS__LS_ENABLE_MASK)
		*flags |= AMD_CG_SUPPORT_HDP_LS;

	/* AMD_CG_SUPPORT_HDP_MGCG */
	data = RREG32(mmHDP_HOST_PATH_CNTL);
	अगर (!(data & HDP_HOST_PATH_CNTL__CLOCK_GATING_DIS_MASK))
		*flags |= AMD_CG_SUPPORT_HDP_MGCG;

	/* AMD_CG_SUPPORT_ROM_MGCG */
	data = RREG32_SMC(ixCGTT_ROM_CLK_CTRL0);
	अगर (!(data & CGTT_ROM_CLK_CTRL0__SOFT_OVERRIDE0_MASK))
		*flags |= AMD_CG_SUPPORT_ROM_MGCG;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs vi_common_ip_funcs = अणु
	.name = "vi_common",
	.early_init = vi_common_early_init,
	.late_init = vi_common_late_init,
	.sw_init = vi_common_sw_init,
	.sw_fini = vi_common_sw_fini,
	.hw_init = vi_common_hw_init,
	.hw_fini = vi_common_hw_fini,
	.suspend = vi_common_suspend,
	.resume = vi_common_resume,
	.is_idle = vi_common_is_idle,
	.रुको_क्रम_idle = vi_common_रुको_क्रम_idle,
	.soft_reset = vi_common_soft_reset,
	.set_घड़ीgating_state = vi_common_set_घड़ीgating_state,
	.set_घातergating_state = vi_common_set_घातergating_state,
	.get_घड़ीgating_state = vi_common_get_घड़ीgating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ip_block_version vi_common_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_COMMON,
	.major = 1,
	.minor = 0,
	.rev = 0,
	.funcs = &vi_common_ip_funcs,
पूर्ण;

व्योम vi_set_virt_ops(काष्ठा amdgpu_device *adev)
अणु
	adev->virt.ops = &xgpu_vi_virt_ops;
पूर्ण

पूर्णांक vi_set_ip_blocks(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_TOPAZ:
		/* topaz has no DCE, UVD, VCE */
		amdgpu_device_ip_block_add(adev, &vi_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v7_4_ip_block);
		amdgpu_device_ip_block_add(adev, &iceland_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v8_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v2_4_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		अगर (adev->enable_भव_display)
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
		अवरोध;
	हाल CHIP_FIJI:
		amdgpu_device_ip_block_add(adev, &vi_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v8_5_ip_block);
		amdgpu_device_ip_block_add(adev, &tonga_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v8_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v3_0_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		अगर (adev->enable_भव_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		अन्यथा
			amdgpu_device_ip_block_add(adev, &dce_v10_1_ip_block);
		अगर (!amdgpu_sriov_vf(adev)) अणु
			amdgpu_device_ip_block_add(adev, &uvd_v6_0_ip_block);
			amdgpu_device_ip_block_add(adev, &vce_v3_0_ip_block);
		पूर्ण
		अवरोध;
	हाल CHIP_TONGA:
		amdgpu_device_ip_block_add(adev, &vi_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v8_0_ip_block);
		amdgpu_device_ip_block_add(adev, &tonga_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v8_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v3_0_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		अगर (adev->enable_भव_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		अन्यथा
			amdgpu_device_ip_block_add(adev, &dce_v10_0_ip_block);
		अगर (!amdgpu_sriov_vf(adev)) अणु
			amdgpu_device_ip_block_add(adev, &uvd_v5_0_ip_block);
			amdgpu_device_ip_block_add(adev, &vce_v3_0_ip_block);
		पूर्ण
		अवरोध;
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
		amdgpu_device_ip_block_add(adev, &vi_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v8_1_ip_block);
		amdgpu_device_ip_block_add(adev, &tonga_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v8_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v3_1_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		अगर (adev->enable_भव_display)
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		अन्यथा
			amdgpu_device_ip_block_add(adev, &dce_v11_2_ip_block);
		amdgpu_device_ip_block_add(adev, &uvd_v6_3_ip_block);
		amdgpu_device_ip_block_add(adev, &vce_v3_4_ip_block);
		अवरोध;
	हाल CHIP_CARRIZO:
		amdgpu_device_ip_block_add(adev, &vi_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v8_0_ip_block);
		amdgpu_device_ip_block_add(adev, &cz_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v8_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v3_0_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		अगर (adev->enable_भव_display)
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		अन्यथा
			amdgpu_device_ip_block_add(adev, &dce_v11_0_ip_block);
		amdgpu_device_ip_block_add(adev, &uvd_v6_0_ip_block);
		amdgpu_device_ip_block_add(adev, &vce_v3_1_ip_block);
#अगर defined(CONFIG_DRM_AMD_ACP)
		amdgpu_device_ip_block_add(adev, &acp_ip_block);
#पूर्ण_अगर
		अवरोध;
	हाल CHIP_STONEY:
		amdgpu_device_ip_block_add(adev, &vi_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v8_0_ip_block);
		amdgpu_device_ip_block_add(adev, &cz_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v8_1_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v3_0_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		अगर (adev->enable_भव_display)
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		अन्यथा
			amdgpu_device_ip_block_add(adev, &dce_v11_0_ip_block);
		amdgpu_device_ip_block_add(adev, &uvd_v6_2_ip_block);
		amdgpu_device_ip_block_add(adev, &vce_v3_4_ip_block);
#अगर defined(CONFIG_DRM_AMD_ACP)
		amdgpu_device_ip_block_add(adev, &acp_ip_block);
#पूर्ण_अगर
		अवरोध;
	शेष:
		/* FIXME: not supported yet */
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम legacy_करोorbell_index_init(काष्ठा amdgpu_device *adev)
अणु
	adev->करोorbell_index.kiq = AMDGPU_DOORBELL_KIQ;
	adev->करोorbell_index.mec_ring0 = AMDGPU_DOORBELL_MEC_RING0;
	adev->करोorbell_index.mec_ring1 = AMDGPU_DOORBELL_MEC_RING1;
	adev->करोorbell_index.mec_ring2 = AMDGPU_DOORBELL_MEC_RING2;
	adev->करोorbell_index.mec_ring3 = AMDGPU_DOORBELL_MEC_RING3;
	adev->करोorbell_index.mec_ring4 = AMDGPU_DOORBELL_MEC_RING4;
	adev->करोorbell_index.mec_ring5 = AMDGPU_DOORBELL_MEC_RING5;
	adev->करोorbell_index.mec_ring6 = AMDGPU_DOORBELL_MEC_RING6;
	adev->करोorbell_index.mec_ring7 = AMDGPU_DOORBELL_MEC_RING7;
	adev->करोorbell_index.gfx_ring0 = AMDGPU_DOORBELL_GFX_RING0;
	adev->करोorbell_index.sdma_engine[0] = AMDGPU_DOORBELL_sDMA_ENGINE0;
	adev->करोorbell_index.sdma_engine[1] = AMDGPU_DOORBELL_sDMA_ENGINE1;
	adev->करोorbell_index.ih = AMDGPU_DOORBELL_IH;
	adev->करोorbell_index.max_assignment = AMDGPU_DOORBELL_MAX_ASSIGNMENT;
पूर्ण
