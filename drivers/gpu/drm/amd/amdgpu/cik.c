<शैली गुरु>
/*
 * Copyright 2012 Advanced Micro Devices, Inc.
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
 * Authors: Alex Deucher
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
#समावेश "cikd.h"
#समावेश "atom.h"
#समावेश "amd_pcie.h"

#समावेश "cik.h"
#समावेश "gmc_v7_0.h"
#समावेश "cik_ih.h"
#समावेश "dce_v8_0.h"
#समावेश "gfx_v7_0.h"
#समावेश "cik_sdma.h"
#समावेश "uvd_v4_2.h"
#समावेश "vce_v2_0.h"
#समावेश "cik_dpm.h"

#समावेश "uvd/uvd_4_2_d.h"

#समावेश "smu/smu_7_0_1_d.h"
#समावेश "smu/smu_7_0_1_sh_mask.h"

#समावेश "dce/dce_8_0_d.h"
#समावेश "dce/dce_8_0_sh_mask.h"

#समावेश "bif/bif_4_1_d.h"
#समावेश "bif/bif_4_1_sh_mask.h"

#समावेश "gca/gfx_7_2_d.h"
#समावेश "gca/gfx_7_2_enum.h"
#समावेश "gca/gfx_7_2_sh_mask.h"

#समावेश "gmc/gmc_7_1_d.h"
#समावेश "gmc/gmc_7_1_sh_mask.h"

#समावेश "oss/oss_2_0_d.h"
#समावेश "oss/oss_2_0_sh_mask.h"

#समावेश "amdgpu_dm.h"
#समावेश "amdgpu_amdkfd.h"
#समावेश "dce_virtual.h"

अटल स्थिर काष्ठा amdgpu_video_codec_info cik_video_codecs_encode_array[] =
अणु
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC,
		.max_width = 2048,
		.max_height = 1152,
		.max_pixels_per_frame = 2048 * 1152,
		.max_level = 0,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_video_codecs cik_video_codecs_encode =
अणु
	.codec_count = ARRAY_SIZE(cik_video_codecs_encode_array),
	.codec_array = cik_video_codecs_encode_array,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_video_codec_info cik_video_codecs_decode_array[] =
अणु
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG2,
		.max_width = 2048,
		.max_height = 1152,
		.max_pixels_per_frame = 2048 * 1152,
		.max_level = 3,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4,
		.max_width = 2048,
		.max_height = 1152,
		.max_pixels_per_frame = 2048 * 1152,
		.max_level = 5,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC,
		.max_width = 2048,
		.max_height = 1152,
		.max_pixels_per_frame = 2048 * 1152,
		.max_level = 41,
	पूर्ण,
	अणु
		.codec_type = AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VC1,
		.max_width = 2048,
		.max_height = 1152,
		.max_pixels_per_frame = 2048 * 1152,
		.max_level = 4,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_video_codecs cik_video_codecs_decode =
अणु
	.codec_count = ARRAY_SIZE(cik_video_codecs_decode_array),
	.codec_array = cik_video_codecs_decode_array,
पूर्ण;

अटल पूर्णांक cik_query_video_codecs(काष्ठा amdgpu_device *adev, bool encode,
				  स्थिर काष्ठा amdgpu_video_codecs **codecs)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_BONAIRE:
	हाल CHIP_HAWAII:
	हाल CHIP_KAVERI:
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
		अगर (encode)
			*codecs = &cik_video_codecs_encode;
		अन्यथा
			*codecs = &cik_video_codecs_decode;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * Indirect रेजिस्टरs accessor
 */
अटल u32 cik_pcie_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(mmPCIE_INDEX, reg);
	(व्योम)RREG32(mmPCIE_INDEX);
	r = RREG32(mmPCIE_DATA);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम cik_pcie_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->pcie_idx_lock, flags);
	WREG32(mmPCIE_INDEX, reg);
	(व्योम)RREG32(mmPCIE_INDEX);
	WREG32(mmPCIE_DATA, v);
	(व्योम)RREG32(mmPCIE_DATA);
	spin_unlock_irqrestore(&adev->pcie_idx_lock, flags);
पूर्ण

अटल u32 cik_smc_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->smc_idx_lock, flags);
	WREG32(mmSMC_IND_INDEX_0, (reg));
	r = RREG32(mmSMC_IND_DATA_0);
	spin_unlock_irqrestore(&adev->smc_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम cik_smc_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->smc_idx_lock, flags);
	WREG32(mmSMC_IND_INDEX_0, (reg));
	WREG32(mmSMC_IND_DATA_0, (v));
	spin_unlock_irqrestore(&adev->smc_idx_lock, flags);
पूर्ण

अटल u32 cik_uvd_ctx_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->uvd_ctx_idx_lock, flags);
	WREG32(mmUVD_CTX_INDEX, ((reg) & 0x1ff));
	r = RREG32(mmUVD_CTX_DATA);
	spin_unlock_irqrestore(&adev->uvd_ctx_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम cik_uvd_ctx_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->uvd_ctx_idx_lock, flags);
	WREG32(mmUVD_CTX_INDEX, ((reg) & 0x1ff));
	WREG32(mmUVD_CTX_DATA, (v));
	spin_unlock_irqrestore(&adev->uvd_ctx_idx_lock, flags);
पूर्ण

अटल u32 cik_didt_rreg(काष्ठा amdgpu_device *adev, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 r;

	spin_lock_irqsave(&adev->didt_idx_lock, flags);
	WREG32(mmDIDT_IND_INDEX, (reg));
	r = RREG32(mmDIDT_IND_DATA);
	spin_unlock_irqrestore(&adev->didt_idx_lock, flags);
	वापस r;
पूर्ण

अटल व्योम cik_didt_wreg(काष्ठा amdgpu_device *adev, u32 reg, u32 v)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adev->didt_idx_lock, flags);
	WREG32(mmDIDT_IND_INDEX, (reg));
	WREG32(mmDIDT_IND_DATA, (v));
	spin_unlock_irqrestore(&adev->didt_idx_lock, flags);
पूर्ण

अटल स्थिर u32 bonaire_golden_spm_रेजिस्टरs[] =
अणु
	0xc200, 0xe0ffffff, 0xe0000000
पूर्ण;

अटल स्थिर u32 bonaire_golden_common_रेजिस्टरs[] =
अणु
	0x31dc, 0xffffffff, 0x00000800,
	0x31dd, 0xffffffff, 0x00000800,
	0x31e6, 0xffffffff, 0x00007fbf,
	0x31e7, 0xffffffff, 0x00007faf
पूर्ण;

अटल स्थिर u32 bonaire_golden_रेजिस्टरs[] =
अणु
	0xcd5, 0x00000333, 0x00000333,
	0xcd4, 0x000c0fc0, 0x00040200,
	0x2684, 0x00010000, 0x00058208,
	0xf000, 0xffff1fff, 0x00140000,
	0xf080, 0xfdfc0fff, 0x00000100,
	0xf08d, 0x40000000, 0x40000200,
	0x260c, 0xffffffff, 0x00000000,
	0x260d, 0xf00fffff, 0x00000400,
	0x260e, 0x0002021c, 0x00020200,
	0x31e, 0x00000080, 0x00000000,
	0x16ec, 0x000000f0, 0x00000070,
	0x16f0, 0xf0311fff, 0x80300000,
	0x263e, 0x73773777, 0x12010001,
	0xd43, 0x00810000, 0x408af000,
	0x1c0c, 0x31000111, 0x00000011,
	0xbd2, 0x73773777, 0x12010001,
	0x883, 0x00007fb6, 0x0021a1b1,
	0x884, 0x00007fb6, 0x002021b1,
	0x860, 0x00007fb6, 0x00002191,
	0x886, 0x00007fb6, 0x002121b1,
	0x887, 0x00007fb6, 0x002021b1,
	0x877, 0x00007fb6, 0x00002191,
	0x878, 0x00007fb6, 0x00002191,
	0xd8a, 0x0000003f, 0x0000000a,
	0xd8b, 0x0000003f, 0x0000000a,
	0xab9, 0x00073ffe, 0x000022a2,
	0x903, 0x000007ff, 0x00000000,
	0x2285, 0xf000003f, 0x00000007,
	0x22fc, 0x00002001, 0x00000001,
	0x22c9, 0xffffffff, 0x00ffffff,
	0xc281, 0x0000ff0f, 0x00000000,
	0xa293, 0x07ffffff, 0x06000000,
	0x136, 0x00000fff, 0x00000100,
	0xf9e, 0x00000001, 0x00000002,
	0x2440, 0x03000000, 0x0362c688,
	0x2300, 0x000000ff, 0x00000001,
	0x390, 0x00001fff, 0x00001fff,
	0x2418, 0x0000007f, 0x00000020,
	0x2542, 0x00010000, 0x00010000,
	0x2b05, 0x000003ff, 0x000000f3,
	0x2b03, 0xffffffff, 0x00001032
पूर्ण;

अटल स्थिर u32 bonaire_mgcg_cgcg_init[] =
अणु
	0x3108, 0xffffffff, 0xfffffffc,
	0xc200, 0xffffffff, 0xe0000000,
	0xf0a8, 0xffffffff, 0x00000100,
	0xf082, 0xffffffff, 0x00000100,
	0xf0b0, 0xffffffff, 0xc0000100,
	0xf0b2, 0xffffffff, 0xc0000100,
	0xf0b1, 0xffffffff, 0xc0000100,
	0x1579, 0xffffffff, 0x00600100,
	0xf0a0, 0xffffffff, 0x00000100,
	0xf085, 0xffffffff, 0x06000100,
	0xf088, 0xffffffff, 0x00000100,
	0xf086, 0xffffffff, 0x06000100,
	0xf081, 0xffffffff, 0x00000100,
	0xf0b8, 0xffffffff, 0x00000100,
	0xf089, 0xffffffff, 0x00000100,
	0xf080, 0xffffffff, 0x00000100,
	0xf08c, 0xffffffff, 0x00000100,
	0xf08d, 0xffffffff, 0x00000100,
	0xf094, 0xffffffff, 0x00000100,
	0xf095, 0xffffffff, 0x00000100,
	0xf096, 0xffffffff, 0x00000100,
	0xf097, 0xffffffff, 0x00000100,
	0xf098, 0xffffffff, 0x00000100,
	0xf09f, 0xffffffff, 0x00000100,
	0xf09e, 0xffffffff, 0x00000100,
	0xf084, 0xffffffff, 0x06000100,
	0xf0a4, 0xffffffff, 0x00000100,
	0xf09d, 0xffffffff, 0x00000100,
	0xf0ad, 0xffffffff, 0x00000100,
	0xf0ac, 0xffffffff, 0x00000100,
	0xf09c, 0xffffffff, 0x00000100,
	0xc200, 0xffffffff, 0xe0000000,
	0xf008, 0xffffffff, 0x00010000,
	0xf009, 0xffffffff, 0x00030002,
	0xf00a, 0xffffffff, 0x00040007,
	0xf00b, 0xffffffff, 0x00060005,
	0xf00c, 0xffffffff, 0x00090008,
	0xf00d, 0xffffffff, 0x00010000,
	0xf00e, 0xffffffff, 0x00030002,
	0xf00f, 0xffffffff, 0x00040007,
	0xf010, 0xffffffff, 0x00060005,
	0xf011, 0xffffffff, 0x00090008,
	0xf012, 0xffffffff, 0x00010000,
	0xf013, 0xffffffff, 0x00030002,
	0xf014, 0xffffffff, 0x00040007,
	0xf015, 0xffffffff, 0x00060005,
	0xf016, 0xffffffff, 0x00090008,
	0xf017, 0xffffffff, 0x00010000,
	0xf018, 0xffffffff, 0x00030002,
	0xf019, 0xffffffff, 0x00040007,
	0xf01a, 0xffffffff, 0x00060005,
	0xf01b, 0xffffffff, 0x00090008,
	0xf01c, 0xffffffff, 0x00010000,
	0xf01d, 0xffffffff, 0x00030002,
	0xf01e, 0xffffffff, 0x00040007,
	0xf01f, 0xffffffff, 0x00060005,
	0xf020, 0xffffffff, 0x00090008,
	0xf021, 0xffffffff, 0x00010000,
	0xf022, 0xffffffff, 0x00030002,
	0xf023, 0xffffffff, 0x00040007,
	0xf024, 0xffffffff, 0x00060005,
	0xf025, 0xffffffff, 0x00090008,
	0xf026, 0xffffffff, 0x00010000,
	0xf027, 0xffffffff, 0x00030002,
	0xf028, 0xffffffff, 0x00040007,
	0xf029, 0xffffffff, 0x00060005,
	0xf02a, 0xffffffff, 0x00090008,
	0xf000, 0xffffffff, 0x96e00200,
	0x21c2, 0xffffffff, 0x00900100,
	0x3109, 0xffffffff, 0x0020003f,
	0xe, 0xffffffff, 0x0140001c,
	0xf, 0x000f0000, 0x000f0000,
	0x88, 0xffffffff, 0xc060000c,
	0x89, 0xc0000fff, 0x00000100,
	0x3e4, 0xffffffff, 0x00000100,
	0x3e6, 0x00000101, 0x00000000,
	0x82a, 0xffffffff, 0x00000104,
	0x1579, 0xff000fff, 0x00000100,
	0xc33, 0xc0000fff, 0x00000104,
	0x3079, 0x00000001, 0x00000001,
	0x3403, 0xff000ff0, 0x00000100,
	0x3603, 0xff000ff0, 0x00000100
पूर्ण;

अटल स्थिर u32 spectre_golden_spm_रेजिस्टरs[] =
अणु
	0xc200, 0xe0ffffff, 0xe0000000
पूर्ण;

अटल स्थिर u32 spectre_golden_common_रेजिस्टरs[] =
अणु
	0x31dc, 0xffffffff, 0x00000800,
	0x31dd, 0xffffffff, 0x00000800,
	0x31e6, 0xffffffff, 0x00007fbf,
	0x31e7, 0xffffffff, 0x00007faf
पूर्ण;

अटल स्थिर u32 spectre_golden_रेजिस्टरs[] =
अणु
	0xf000, 0xffff1fff, 0x96940200,
	0xf003, 0xffff0001, 0xff000000,
	0xf080, 0xfffc0fff, 0x00000100,
	0x1bb6, 0x00010101, 0x00010000,
	0x260d, 0xf00fffff, 0x00000400,
	0x260e, 0xfffffffc, 0x00020200,
	0x16ec, 0x000000f0, 0x00000070,
	0x16f0, 0xf0311fff, 0x80300000,
	0x263e, 0x73773777, 0x12010001,
	0x26df, 0x00ff0000, 0x00fc0000,
	0xbd2, 0x73773777, 0x12010001,
	0x2285, 0xf000003f, 0x00000007,
	0x22c9, 0xffffffff, 0x00ffffff,
	0xa0d4, 0x3f3f3fff, 0x00000082,
	0xa0d5, 0x0000003f, 0x00000000,
	0xf9e, 0x00000001, 0x00000002,
	0x244f, 0xffff03df, 0x00000004,
	0x31da, 0x00000008, 0x00000008,
	0x2300, 0x000008ff, 0x00000800,
	0x2542, 0x00010000, 0x00010000,
	0x2b03, 0xffffffff, 0x54763210,
	0x853e, 0x01ff01ff, 0x00000002,
	0x8526, 0x007ff800, 0x00200000,
	0x8057, 0xffffffff, 0x00000f40,
	0xc24d, 0xffffffff, 0x00000001
पूर्ण;

अटल स्थिर u32 spectre_mgcg_cgcg_init[] =
अणु
	0x3108, 0xffffffff, 0xfffffffc,
	0xc200, 0xffffffff, 0xe0000000,
	0xf0a8, 0xffffffff, 0x00000100,
	0xf082, 0xffffffff, 0x00000100,
	0xf0b0, 0xffffffff, 0x00000100,
	0xf0b2, 0xffffffff, 0x00000100,
	0xf0b1, 0xffffffff, 0x00000100,
	0x1579, 0xffffffff, 0x00600100,
	0xf0a0, 0xffffffff, 0x00000100,
	0xf085, 0xffffffff, 0x06000100,
	0xf088, 0xffffffff, 0x00000100,
	0xf086, 0xffffffff, 0x06000100,
	0xf081, 0xffffffff, 0x00000100,
	0xf0b8, 0xffffffff, 0x00000100,
	0xf089, 0xffffffff, 0x00000100,
	0xf080, 0xffffffff, 0x00000100,
	0xf08c, 0xffffffff, 0x00000100,
	0xf08d, 0xffffffff, 0x00000100,
	0xf094, 0xffffffff, 0x00000100,
	0xf095, 0xffffffff, 0x00000100,
	0xf096, 0xffffffff, 0x00000100,
	0xf097, 0xffffffff, 0x00000100,
	0xf098, 0xffffffff, 0x00000100,
	0xf09f, 0xffffffff, 0x00000100,
	0xf09e, 0xffffffff, 0x00000100,
	0xf084, 0xffffffff, 0x06000100,
	0xf0a4, 0xffffffff, 0x00000100,
	0xf09d, 0xffffffff, 0x00000100,
	0xf0ad, 0xffffffff, 0x00000100,
	0xf0ac, 0xffffffff, 0x00000100,
	0xf09c, 0xffffffff, 0x00000100,
	0xc200, 0xffffffff, 0xe0000000,
	0xf008, 0xffffffff, 0x00010000,
	0xf009, 0xffffffff, 0x00030002,
	0xf00a, 0xffffffff, 0x00040007,
	0xf00b, 0xffffffff, 0x00060005,
	0xf00c, 0xffffffff, 0x00090008,
	0xf00d, 0xffffffff, 0x00010000,
	0xf00e, 0xffffffff, 0x00030002,
	0xf00f, 0xffffffff, 0x00040007,
	0xf010, 0xffffffff, 0x00060005,
	0xf011, 0xffffffff, 0x00090008,
	0xf012, 0xffffffff, 0x00010000,
	0xf013, 0xffffffff, 0x00030002,
	0xf014, 0xffffffff, 0x00040007,
	0xf015, 0xffffffff, 0x00060005,
	0xf016, 0xffffffff, 0x00090008,
	0xf017, 0xffffffff, 0x00010000,
	0xf018, 0xffffffff, 0x00030002,
	0xf019, 0xffffffff, 0x00040007,
	0xf01a, 0xffffffff, 0x00060005,
	0xf01b, 0xffffffff, 0x00090008,
	0xf01c, 0xffffffff, 0x00010000,
	0xf01d, 0xffffffff, 0x00030002,
	0xf01e, 0xffffffff, 0x00040007,
	0xf01f, 0xffffffff, 0x00060005,
	0xf020, 0xffffffff, 0x00090008,
	0xf021, 0xffffffff, 0x00010000,
	0xf022, 0xffffffff, 0x00030002,
	0xf023, 0xffffffff, 0x00040007,
	0xf024, 0xffffffff, 0x00060005,
	0xf025, 0xffffffff, 0x00090008,
	0xf026, 0xffffffff, 0x00010000,
	0xf027, 0xffffffff, 0x00030002,
	0xf028, 0xffffffff, 0x00040007,
	0xf029, 0xffffffff, 0x00060005,
	0xf02a, 0xffffffff, 0x00090008,
	0xf02b, 0xffffffff, 0x00010000,
	0xf02c, 0xffffffff, 0x00030002,
	0xf02d, 0xffffffff, 0x00040007,
	0xf02e, 0xffffffff, 0x00060005,
	0xf02f, 0xffffffff, 0x00090008,
	0xf000, 0xffffffff, 0x96e00200,
	0x21c2, 0xffffffff, 0x00900100,
	0x3109, 0xffffffff, 0x0020003f,
	0xe, 0xffffffff, 0x0140001c,
	0xf, 0x000f0000, 0x000f0000,
	0x88, 0xffffffff, 0xc060000c,
	0x89, 0xc0000fff, 0x00000100,
	0x3e4, 0xffffffff, 0x00000100,
	0x3e6, 0x00000101, 0x00000000,
	0x82a, 0xffffffff, 0x00000104,
	0x1579, 0xff000fff, 0x00000100,
	0xc33, 0xc0000fff, 0x00000104,
	0x3079, 0x00000001, 0x00000001,
	0x3403, 0xff000ff0, 0x00000100,
	0x3603, 0xff000ff0, 0x00000100
पूर्ण;

अटल स्थिर u32 kalindi_golden_spm_रेजिस्टरs[] =
अणु
	0xc200, 0xe0ffffff, 0xe0000000
पूर्ण;

अटल स्थिर u32 kalindi_golden_common_रेजिस्टरs[] =
अणु
	0x31dc, 0xffffffff, 0x00000800,
	0x31dd, 0xffffffff, 0x00000800,
	0x31e6, 0xffffffff, 0x00007fbf,
	0x31e7, 0xffffffff, 0x00007faf
पूर्ण;

अटल स्थिर u32 kalindi_golden_रेजिस्टरs[] =
अणु
	0xf000, 0xffffdfff, 0x6e944040,
	0x1579, 0xff607fff, 0xfc000100,
	0xf088, 0xff000fff, 0x00000100,
	0xf089, 0xff000fff, 0x00000100,
	0xf080, 0xfffc0fff, 0x00000100,
	0x1bb6, 0x00010101, 0x00010000,
	0x260c, 0xffffffff, 0x00000000,
	0x260d, 0xf00fffff, 0x00000400,
	0x16ec, 0x000000f0, 0x00000070,
	0x16f0, 0xf0311fff, 0x80300000,
	0x263e, 0x73773777, 0x12010001,
	0x263f, 0xffffffff, 0x00000010,
	0x26df, 0x00ff0000, 0x00fc0000,
	0x200c, 0x00001f0f, 0x0000100a,
	0xbd2, 0x73773777, 0x12010001,
	0x902, 0x000fffff, 0x000c007f,
	0x2285, 0xf000003f, 0x00000007,
	0x22c9, 0x3fff3fff, 0x00ffcfff,
	0xc281, 0x0000ff0f, 0x00000000,
	0xa293, 0x07ffffff, 0x06000000,
	0x136, 0x00000fff, 0x00000100,
	0xf9e, 0x00000001, 0x00000002,
	0x31da, 0x00000008, 0x00000008,
	0x2300, 0x000000ff, 0x00000003,
	0x853e, 0x01ff01ff, 0x00000002,
	0x8526, 0x007ff800, 0x00200000,
	0x8057, 0xffffffff, 0x00000f40,
	0x2231, 0x001f3ae3, 0x00000082,
	0x2235, 0x0000001f, 0x00000010,
	0xc24d, 0xffffffff, 0x00000000
पूर्ण;

अटल स्थिर u32 kalindi_mgcg_cgcg_init[] =
अणु
	0x3108, 0xffffffff, 0xfffffffc,
	0xc200, 0xffffffff, 0xe0000000,
	0xf0a8, 0xffffffff, 0x00000100,
	0xf082, 0xffffffff, 0x00000100,
	0xf0b0, 0xffffffff, 0x00000100,
	0xf0b2, 0xffffffff, 0x00000100,
	0xf0b1, 0xffffffff, 0x00000100,
	0x1579, 0xffffffff, 0x00600100,
	0xf0a0, 0xffffffff, 0x00000100,
	0xf085, 0xffffffff, 0x06000100,
	0xf088, 0xffffffff, 0x00000100,
	0xf086, 0xffffffff, 0x06000100,
	0xf081, 0xffffffff, 0x00000100,
	0xf0b8, 0xffffffff, 0x00000100,
	0xf089, 0xffffffff, 0x00000100,
	0xf080, 0xffffffff, 0x00000100,
	0xf08c, 0xffffffff, 0x00000100,
	0xf08d, 0xffffffff, 0x00000100,
	0xf094, 0xffffffff, 0x00000100,
	0xf095, 0xffffffff, 0x00000100,
	0xf096, 0xffffffff, 0x00000100,
	0xf097, 0xffffffff, 0x00000100,
	0xf098, 0xffffffff, 0x00000100,
	0xf09f, 0xffffffff, 0x00000100,
	0xf09e, 0xffffffff, 0x00000100,
	0xf084, 0xffffffff, 0x06000100,
	0xf0a4, 0xffffffff, 0x00000100,
	0xf09d, 0xffffffff, 0x00000100,
	0xf0ad, 0xffffffff, 0x00000100,
	0xf0ac, 0xffffffff, 0x00000100,
	0xf09c, 0xffffffff, 0x00000100,
	0xc200, 0xffffffff, 0xe0000000,
	0xf008, 0xffffffff, 0x00010000,
	0xf009, 0xffffffff, 0x00030002,
	0xf00a, 0xffffffff, 0x00040007,
	0xf00b, 0xffffffff, 0x00060005,
	0xf00c, 0xffffffff, 0x00090008,
	0xf00d, 0xffffffff, 0x00010000,
	0xf00e, 0xffffffff, 0x00030002,
	0xf00f, 0xffffffff, 0x00040007,
	0xf010, 0xffffffff, 0x00060005,
	0xf011, 0xffffffff, 0x00090008,
	0xf000, 0xffffffff, 0x96e00200,
	0x21c2, 0xffffffff, 0x00900100,
	0x3109, 0xffffffff, 0x0020003f,
	0xe, 0xffffffff, 0x0140001c,
	0xf, 0x000f0000, 0x000f0000,
	0x88, 0xffffffff, 0xc060000c,
	0x89, 0xc0000fff, 0x00000100,
	0x82a, 0xffffffff, 0x00000104,
	0x1579, 0xff000fff, 0x00000100,
	0xc33, 0xc0000fff, 0x00000104,
	0x3079, 0x00000001, 0x00000001,
	0x3403, 0xff000ff0, 0x00000100,
	0x3603, 0xff000ff0, 0x00000100
पूर्ण;

अटल स्थिर u32 hawaii_golden_spm_रेजिस्टरs[] =
अणु
	0xc200, 0xe0ffffff, 0xe0000000
पूर्ण;

अटल स्थिर u32 hawaii_golden_common_रेजिस्टरs[] =
अणु
	0xc200, 0xffffffff, 0xe0000000,
	0xa0d4, 0xffffffff, 0x3a00161a,
	0xa0d5, 0xffffffff, 0x0000002e,
	0x2684, 0xffffffff, 0x00018208,
	0x263e, 0xffffffff, 0x12011003
पूर्ण;

अटल स्थिर u32 hawaii_golden_रेजिस्टरs[] =
अणु
	0xcd5, 0x00000333, 0x00000333,
	0x2684, 0x00010000, 0x00058208,
	0x260c, 0xffffffff, 0x00000000,
	0x260d, 0xf00fffff, 0x00000400,
	0x260e, 0x0002021c, 0x00020200,
	0x31e, 0x00000080, 0x00000000,
	0x16ec, 0x000000f0, 0x00000070,
	0x16f0, 0xf0311fff, 0x80300000,
	0xd43, 0x00810000, 0x408af000,
	0x1c0c, 0x31000111, 0x00000011,
	0xbd2, 0x73773777, 0x12010001,
	0x848, 0x0000007f, 0x0000001b,
	0x877, 0x00007fb6, 0x00002191,
	0xd8a, 0x0000003f, 0x0000000a,
	0xd8b, 0x0000003f, 0x0000000a,
	0xab9, 0x00073ffe, 0x000022a2,
	0x903, 0x000007ff, 0x00000000,
	0x22fc, 0x00002001, 0x00000001,
	0x22c9, 0xffffffff, 0x00ffffff,
	0xc281, 0x0000ff0f, 0x00000000,
	0xa293, 0x07ffffff, 0x06000000,
	0xf9e, 0x00000001, 0x00000002,
	0x31da, 0x00000008, 0x00000008,
	0x31dc, 0x00000f00, 0x00000800,
	0x31dd, 0x00000f00, 0x00000800,
	0x31e6, 0x00ffffff, 0x00ff7fbf,
	0x31e7, 0x00ffffff, 0x00ff7faf,
	0x2300, 0x000000ff, 0x00000800,
	0x390, 0x00001fff, 0x00001fff,
	0x2418, 0x0000007f, 0x00000020,
	0x2542, 0x00010000, 0x00010000,
	0x2b80, 0x00100000, 0x000ff07c,
	0x2b05, 0x000003ff, 0x0000000f,
	0x2b04, 0xffffffff, 0x7564fdec,
	0x2b03, 0xffffffff, 0x3120b9a8,
	0x2b02, 0x20000000, 0x0f9c0000
पूर्ण;

अटल स्थिर u32 hawaii_mgcg_cgcg_init[] =
अणु
	0x3108, 0xffffffff, 0xfffffffd,
	0xc200, 0xffffffff, 0xe0000000,
	0xf0a8, 0xffffffff, 0x00000100,
	0xf082, 0xffffffff, 0x00000100,
	0xf0b0, 0xffffffff, 0x00000100,
	0xf0b2, 0xffffffff, 0x00000100,
	0xf0b1, 0xffffffff, 0x00000100,
	0x1579, 0xffffffff, 0x00200100,
	0xf0a0, 0xffffffff, 0x00000100,
	0xf085, 0xffffffff, 0x06000100,
	0xf088, 0xffffffff, 0x00000100,
	0xf086, 0xffffffff, 0x06000100,
	0xf081, 0xffffffff, 0x00000100,
	0xf0b8, 0xffffffff, 0x00000100,
	0xf089, 0xffffffff, 0x00000100,
	0xf080, 0xffffffff, 0x00000100,
	0xf08c, 0xffffffff, 0x00000100,
	0xf08d, 0xffffffff, 0x00000100,
	0xf094, 0xffffffff, 0x00000100,
	0xf095, 0xffffffff, 0x00000100,
	0xf096, 0xffffffff, 0x00000100,
	0xf097, 0xffffffff, 0x00000100,
	0xf098, 0xffffffff, 0x00000100,
	0xf09f, 0xffffffff, 0x00000100,
	0xf09e, 0xffffffff, 0x00000100,
	0xf084, 0xffffffff, 0x06000100,
	0xf0a4, 0xffffffff, 0x00000100,
	0xf09d, 0xffffffff, 0x00000100,
	0xf0ad, 0xffffffff, 0x00000100,
	0xf0ac, 0xffffffff, 0x00000100,
	0xf09c, 0xffffffff, 0x00000100,
	0xc200, 0xffffffff, 0xe0000000,
	0xf008, 0xffffffff, 0x00010000,
	0xf009, 0xffffffff, 0x00030002,
	0xf00a, 0xffffffff, 0x00040007,
	0xf00b, 0xffffffff, 0x00060005,
	0xf00c, 0xffffffff, 0x00090008,
	0xf00d, 0xffffffff, 0x00010000,
	0xf00e, 0xffffffff, 0x00030002,
	0xf00f, 0xffffffff, 0x00040007,
	0xf010, 0xffffffff, 0x00060005,
	0xf011, 0xffffffff, 0x00090008,
	0xf012, 0xffffffff, 0x00010000,
	0xf013, 0xffffffff, 0x00030002,
	0xf014, 0xffffffff, 0x00040007,
	0xf015, 0xffffffff, 0x00060005,
	0xf016, 0xffffffff, 0x00090008,
	0xf017, 0xffffffff, 0x00010000,
	0xf018, 0xffffffff, 0x00030002,
	0xf019, 0xffffffff, 0x00040007,
	0xf01a, 0xffffffff, 0x00060005,
	0xf01b, 0xffffffff, 0x00090008,
	0xf01c, 0xffffffff, 0x00010000,
	0xf01d, 0xffffffff, 0x00030002,
	0xf01e, 0xffffffff, 0x00040007,
	0xf01f, 0xffffffff, 0x00060005,
	0xf020, 0xffffffff, 0x00090008,
	0xf021, 0xffffffff, 0x00010000,
	0xf022, 0xffffffff, 0x00030002,
	0xf023, 0xffffffff, 0x00040007,
	0xf024, 0xffffffff, 0x00060005,
	0xf025, 0xffffffff, 0x00090008,
	0xf026, 0xffffffff, 0x00010000,
	0xf027, 0xffffffff, 0x00030002,
	0xf028, 0xffffffff, 0x00040007,
	0xf029, 0xffffffff, 0x00060005,
	0xf02a, 0xffffffff, 0x00090008,
	0xf02b, 0xffffffff, 0x00010000,
	0xf02c, 0xffffffff, 0x00030002,
	0xf02d, 0xffffffff, 0x00040007,
	0xf02e, 0xffffffff, 0x00060005,
	0xf02f, 0xffffffff, 0x00090008,
	0xf030, 0xffffffff, 0x00010000,
	0xf031, 0xffffffff, 0x00030002,
	0xf032, 0xffffffff, 0x00040007,
	0xf033, 0xffffffff, 0x00060005,
	0xf034, 0xffffffff, 0x00090008,
	0xf035, 0xffffffff, 0x00010000,
	0xf036, 0xffffffff, 0x00030002,
	0xf037, 0xffffffff, 0x00040007,
	0xf038, 0xffffffff, 0x00060005,
	0xf039, 0xffffffff, 0x00090008,
	0xf03a, 0xffffffff, 0x00010000,
	0xf03b, 0xffffffff, 0x00030002,
	0xf03c, 0xffffffff, 0x00040007,
	0xf03d, 0xffffffff, 0x00060005,
	0xf03e, 0xffffffff, 0x00090008,
	0x30c6, 0xffffffff, 0x00020200,
	0xcd4, 0xffffffff, 0x00000200,
	0x570, 0xffffffff, 0x00000400,
	0x157a, 0xffffffff, 0x00000000,
	0xbd4, 0xffffffff, 0x00000902,
	0xf000, 0xffffffff, 0x96940200,
	0x21c2, 0xffffffff, 0x00900100,
	0x3109, 0xffffffff, 0x0020003f,
	0xe, 0xffffffff, 0x0140001c,
	0xf, 0x000f0000, 0x000f0000,
	0x88, 0xffffffff, 0xc060000c,
	0x89, 0xc0000fff, 0x00000100,
	0x3e4, 0xffffffff, 0x00000100,
	0x3e6, 0x00000101, 0x00000000,
	0x82a, 0xffffffff, 0x00000104,
	0x1579, 0xff000fff, 0x00000100,
	0xc33, 0xc0000fff, 0x00000104,
	0x3079, 0x00000001, 0x00000001,
	0x3403, 0xff000ff0, 0x00000100,
	0x3603, 0xff000ff0, 0x00000100
पूर्ण;

अटल स्थिर u32 godavari_golden_रेजिस्टरs[] =
अणु
	0x1579, 0xff607fff, 0xfc000100,
	0x1bb6, 0x00010101, 0x00010000,
	0x260c, 0xffffffff, 0x00000000,
	0x260c0, 0xf00fffff, 0x00000400,
	0x184c, 0xffffffff, 0x00010000,
	0x16ec, 0x000000f0, 0x00000070,
	0x16f0, 0xf0311fff, 0x80300000,
	0x263e, 0x73773777, 0x12010001,
	0x263f, 0xffffffff, 0x00000010,
	0x200c, 0x00001f0f, 0x0000100a,
	0xbd2, 0x73773777, 0x12010001,
	0x902, 0x000fffff, 0x000c007f,
	0x2285, 0xf000003f, 0x00000007,
	0x22c9, 0xffffffff, 0x00ff0fff,
	0xc281, 0x0000ff0f, 0x00000000,
	0xa293, 0x07ffffff, 0x06000000,
	0x136, 0x00000fff, 0x00000100,
	0x3405, 0x00010000, 0x00810001,
	0x3605, 0x00010000, 0x00810001,
	0xf9e, 0x00000001, 0x00000002,
	0x31da, 0x00000008, 0x00000008,
	0x31dc, 0x00000f00, 0x00000800,
	0x31dd, 0x00000f00, 0x00000800,
	0x31e6, 0x00ffffff, 0x00ff7fbf,
	0x31e7, 0x00ffffff, 0x00ff7faf,
	0x2300, 0x000000ff, 0x00000001,
	0x853e, 0x01ff01ff, 0x00000002,
	0x8526, 0x007ff800, 0x00200000,
	0x8057, 0xffffffff, 0x00000f40,
	0x2231, 0x001f3ae3, 0x00000082,
	0x2235, 0x0000001f, 0x00000010,
	0xc24d, 0xffffffff, 0x00000000
पूर्ण;

अटल व्योम cik_init_golden_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	/* Some of the रेजिस्टरs might be dependent on GRBM_GFX_INDEX */
	mutex_lock(&adev->grbm_idx_mutex);

	चयन (adev->asic_type) अणु
	हाल CHIP_BONAIRE:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							bonaire_mgcg_cgcg_init,
							ARRAY_SIZE(bonaire_mgcg_cgcg_init));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							bonaire_golden_रेजिस्टरs,
							ARRAY_SIZE(bonaire_golden_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							bonaire_golden_common_रेजिस्टरs,
							ARRAY_SIZE(bonaire_golden_common_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							bonaire_golden_spm_रेजिस्टरs,
							ARRAY_SIZE(bonaire_golden_spm_रेजिस्टरs));
		अवरोध;
	हाल CHIP_KABINI:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							kalindi_mgcg_cgcg_init,
							ARRAY_SIZE(kalindi_mgcg_cgcg_init));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							kalindi_golden_रेजिस्टरs,
							ARRAY_SIZE(kalindi_golden_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							kalindi_golden_common_रेजिस्टरs,
							ARRAY_SIZE(kalindi_golden_common_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							kalindi_golden_spm_रेजिस्टरs,
							ARRAY_SIZE(kalindi_golden_spm_रेजिस्टरs));
		अवरोध;
	हाल CHIP_MULLINS:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							kalindi_mgcg_cgcg_init,
							ARRAY_SIZE(kalindi_mgcg_cgcg_init));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							godavari_golden_रेजिस्टरs,
							ARRAY_SIZE(godavari_golden_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							kalindi_golden_common_रेजिस्टरs,
							ARRAY_SIZE(kalindi_golden_common_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							kalindi_golden_spm_रेजिस्टरs,
							ARRAY_SIZE(kalindi_golden_spm_रेजिस्टरs));
		अवरोध;
	हाल CHIP_KAVERI:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							spectre_mgcg_cgcg_init,
							ARRAY_SIZE(spectre_mgcg_cgcg_init));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							spectre_golden_रेजिस्टरs,
							ARRAY_SIZE(spectre_golden_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							spectre_golden_common_रेजिस्टरs,
							ARRAY_SIZE(spectre_golden_common_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							spectre_golden_spm_रेजिस्टरs,
							ARRAY_SIZE(spectre_golden_spm_रेजिस्टरs));
		अवरोध;
	हाल CHIP_HAWAII:
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							hawaii_mgcg_cgcg_init,
							ARRAY_SIZE(hawaii_mgcg_cgcg_init));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							hawaii_golden_रेजिस्टरs,
							ARRAY_SIZE(hawaii_golden_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							hawaii_golden_common_रेजिस्टरs,
							ARRAY_SIZE(hawaii_golden_common_रेजिस्टरs));
		amdgpu_device_program_रेजिस्टर_sequence(adev,
							hawaii_golden_spm_रेजिस्टरs,
							ARRAY_SIZE(hawaii_golden_spm_रेजिस्टरs));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&adev->grbm_idx_mutex);
पूर्ण

/**
 * cik_get_xclk - get the xclk
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Returns the reference घड़ी used by the gfx engine
 * (CIK).
 */
अटल u32 cik_get_xclk(काष्ठा amdgpu_device *adev)
अणु
	u32 reference_घड़ी = adev->घड़ी.spll.reference_freq;

	अगर (adev->flags & AMD_IS_APU) अणु
		अगर (RREG32_SMC(ixGENERAL_PWRMGT) & GENERAL_PWRMGT__GPU_COUNTER_CLK_MASK)
			वापस reference_घड़ी / 2;
	पूर्ण अन्यथा अणु
		अगर (RREG32_SMC(ixCG_CLKPIN_CNTL) & CG_CLKPIN_CNTL__XTALIN_DIVIDE_MASK)
			वापस reference_घड़ी / 4;
	पूर्ण
	वापस reference_घड़ी;
पूर्ण

/**
 * cik_srbm_select - select specअगरic रेजिस्टर instances
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
व्योम cik_srbm_select(काष्ठा amdgpu_device *adev,
		     u32 me, u32 pipe, u32 queue, u32 vmid)
अणु
	u32 srbm_gfx_cntl =
		(((pipe << SRBM_GFX_CNTL__PIPEID__SHIFT) & SRBM_GFX_CNTL__PIPEID_MASK)|
		((me << SRBM_GFX_CNTL__MEID__SHIFT) & SRBM_GFX_CNTL__MEID_MASK)|
		((vmid << SRBM_GFX_CNTL__VMID__SHIFT) & SRBM_GFX_CNTL__VMID_MASK)|
		((queue << SRBM_GFX_CNTL__QUEUEID__SHIFT) & SRBM_GFX_CNTL__QUEUEID_MASK));
	WREG32(mmSRBM_GFX_CNTL, srbm_gfx_cntl);
पूर्ण

अटल व्योम cik_vga_set_state(काष्ठा amdgpu_device *adev, bool state)
अणु
	uपूर्णांक32_t पंचांगp;

	पंचांगp = RREG32(mmCONFIG_CNTL);
	अगर (!state)
		पंचांगp |= CONFIG_CNTL__VGA_DIS_MASK;
	अन्यथा
		पंचांगp &= ~CONFIG_CNTL__VGA_DIS_MASK;
	WREG32(mmCONFIG_CNTL, पंचांगp);
पूर्ण

अटल bool cik_पढ़ो_disabled_bios(काष्ठा amdgpu_device *adev)
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
		       (d2vga_control & ~(D1VGA_CONTROL__D1VGA_MODE_ENABLE_MASK |
					  D1VGA_CONTROL__D1VGA_TIMING_SELECT_MASK)));
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

अटल bool cik_पढ़ो_bios_from_rom(काष्ठा amdgpu_device *adev,
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
	WREG32(mmSMC_IND_INDEX_0, ixROM_INDEX);
	WREG32(mmSMC_IND_DATA_0, 0);
	/* set index to data क्रम continous पढ़ो */
	WREG32(mmSMC_IND_INDEX_0, ixROM_DATA);
	क्रम (i = 0; i < length_dw; i++)
		dw_ptr[i] = RREG32(mmSMC_IND_DATA_0);
	spin_unlock_irqrestore(&adev->smc_idx_lock, flags);

	वापस true;
पूर्ण

अटल स्थिर काष्ठा amdgpu_allowed_रेजिस्टर_entry cik_allowed_पढ़ो_रेजिस्टरs[] = अणु
	अणुmmGRBM_STATUSपूर्ण,
	अणुmmGRBM_STATUS2पूर्ण,
	अणुmmGRBM_STATUS_SE0पूर्ण,
	अणुmmGRBM_STATUS_SE1पूर्ण,
	अणुmmGRBM_STATUS_SE2पूर्ण,
	अणुmmGRBM_STATUS_SE3पूर्ण,
	अणुmmSRBM_STATUSपूर्ण,
	अणुmmSRBM_STATUS2पूर्ण,
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


अटल uपूर्णांक32_t cik_get_रेजिस्टर_value(काष्ठा amdgpu_device *adev,
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

अटल पूर्णांक cik_पढ़ो_रेजिस्टर(काष्ठा amdgpu_device *adev, u32 se_num,
			     u32 sh_num, u32 reg_offset, u32 *value)
अणु
	uपूर्णांक32_t i;

	*value = 0;
	क्रम (i = 0; i < ARRAY_SIZE(cik_allowed_पढ़ो_रेजिस्टरs); i++) अणु
		bool indexed = cik_allowed_पढ़ो_रेजिस्टरs[i].grbm_indexed;

		अगर (reg_offset != cik_allowed_पढ़ो_रेजिस्टरs[i].reg_offset)
			जारी;

		*value = cik_get_रेजिस्टर_value(adev, indexed, se_num, sh_num,
						reg_offset);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

काष्ठा kv_reset_save_regs अणु
	u32 gmcon_reng_execute;
	u32 gmcon_misc;
	u32 gmcon_misc3;
पूर्ण;

अटल व्योम kv_save_regs_क्रम_reset(काष्ठा amdgpu_device *adev,
				   काष्ठा kv_reset_save_regs *save)
अणु
	save->gmcon_reng_execute = RREG32(mmGMCON_RENG_EXECUTE);
	save->gmcon_misc = RREG32(mmGMCON_MISC);
	save->gmcon_misc3 = RREG32(mmGMCON_MISC3);

	WREG32(mmGMCON_RENG_EXECUTE, save->gmcon_reng_execute &
		~GMCON_RENG_EXECUTE__RENG_EXECUTE_ON_PWR_UP_MASK);
	WREG32(mmGMCON_MISC, save->gmcon_misc &
		~(GMCON_MISC__RENG_EXECUTE_ON_REG_UPDATE_MASK |
			GMCON_MISC__STCTRL_STUTTER_EN_MASK));
पूर्ण

अटल व्योम kv_restore_regs_क्रम_reset(काष्ठा amdgpu_device *adev,
				      काष्ठा kv_reset_save_regs *save)
अणु
	पूर्णांक i;

	WREG32(mmGMCON_PGFSM_WRITE, 0);
	WREG32(mmGMCON_PGFSM_CONFIG, 0x200010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(mmGMCON_PGFSM_WRITE, 0);

	WREG32(mmGMCON_PGFSM_WRITE, 0);
	WREG32(mmGMCON_PGFSM_CONFIG, 0x300010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(mmGMCON_PGFSM_WRITE, 0);

	WREG32(mmGMCON_PGFSM_WRITE, 0x210000);
	WREG32(mmGMCON_PGFSM_CONFIG, 0xa00010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(mmGMCON_PGFSM_WRITE, 0);

	WREG32(mmGMCON_PGFSM_WRITE, 0x21003);
	WREG32(mmGMCON_PGFSM_CONFIG, 0xb00010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(mmGMCON_PGFSM_WRITE, 0);

	WREG32(mmGMCON_PGFSM_WRITE, 0x2b00);
	WREG32(mmGMCON_PGFSM_CONFIG, 0xc00010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(mmGMCON_PGFSM_WRITE, 0);

	WREG32(mmGMCON_PGFSM_WRITE, 0);
	WREG32(mmGMCON_PGFSM_CONFIG, 0xd00010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(mmGMCON_PGFSM_WRITE, 0);

	WREG32(mmGMCON_PGFSM_WRITE, 0x420000);
	WREG32(mmGMCON_PGFSM_CONFIG, 0x100010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(mmGMCON_PGFSM_WRITE, 0);

	WREG32(mmGMCON_PGFSM_WRITE, 0x120202);
	WREG32(mmGMCON_PGFSM_CONFIG, 0x500010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(mmGMCON_PGFSM_WRITE, 0);

	WREG32(mmGMCON_PGFSM_WRITE, 0x3e3e36);
	WREG32(mmGMCON_PGFSM_CONFIG, 0x600010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(mmGMCON_PGFSM_WRITE, 0);

	WREG32(mmGMCON_PGFSM_WRITE, 0x373f3e);
	WREG32(mmGMCON_PGFSM_CONFIG, 0x700010ff);

	क्रम (i = 0; i < 5; i++)
		WREG32(mmGMCON_PGFSM_WRITE, 0);

	WREG32(mmGMCON_PGFSM_WRITE, 0x3e1332);
	WREG32(mmGMCON_PGFSM_CONFIG, 0xe00010ff);

	WREG32(mmGMCON_MISC3, save->gmcon_misc3);
	WREG32(mmGMCON_MISC, save->gmcon_misc);
	WREG32(mmGMCON_RENG_EXECUTE, save->gmcon_reng_execute);
पूर्ण

/**
 * cik_asic_pci_config_reset - soft reset GPU
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Use PCI Config method to reset the GPU.
 *
 * Returns 0 क्रम success.
 */
अटल पूर्णांक cik_asic_pci_config_reset(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा kv_reset_save_regs kv_save = अणु 0 पूर्ण;
	u32 i;
	पूर्णांक r = -EINVAL;

	amdgpu_atombios_scratch_regs_engine_hung(adev, true);

	अगर (adev->flags & AMD_IS_APU)
		kv_save_regs_क्रम_reset(adev, &kv_save);

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

	/* करोes asic init need to be run first??? */
	अगर (adev->flags & AMD_IS_APU)
		kv_restore_regs_क्रम_reset(adev, &kv_save);

	amdgpu_atombios_scratch_regs_engine_hung(adev, false);

	वापस r;
पूर्ण

अटल bool cik_asic_supports_baco(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_BONAIRE:
	हाल CHIP_HAWAII:
		वापस amdgpu_dpm_is_baco_supported(adev);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल क्रमागत amd_reset_method
cik_asic_reset_method(काष्ठा amdgpu_device *adev)
अणु
	bool baco_reset;

	अगर (amdgpu_reset_method == AMD_RESET_METHOD_LEGACY ||
	    amdgpu_reset_method == AMD_RESET_METHOD_BACO)
		वापस amdgpu_reset_method;

	अगर (amdgpu_reset_method != -1)
		dev_warn(adev->dev, "Specified reset:%d isn't supported, using AUTO instead.\n",
				  amdgpu_reset_method);

	चयन (adev->asic_type) अणु
	हाल CHIP_BONAIRE:
	हाल CHIP_HAWAII:
		baco_reset = cik_asic_supports_baco(adev);
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
 * cik_asic_reset - soft reset GPU
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Look up which blocks are hung and attempt
 * to reset them.
 * Returns 0 क्रम success.
 */
अटल पूर्णांक cik_asic_reset(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (cik_asic_reset_method(adev) == AMD_RESET_METHOD_BACO) अणु
		dev_info(adev->dev, "BACO reset\n");
		r = amdgpu_dpm_baco_reset(adev);
	पूर्ण अन्यथा अणु
		dev_info(adev->dev, "PCI CONFIG reset\n");
		r = cik_asic_pci_config_reset(adev);
	पूर्ण

	वापस r;
पूर्ण

अटल u32 cik_get_config_memsize(काष्ठा amdgpu_device *adev)
अणु
	वापस RREG32(mmCONFIG_MEMSIZE);
पूर्ण

अटल पूर्णांक cik_set_uvd_घड़ी(काष्ठा amdgpu_device *adev, u32 घड़ी,
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
	पंचांगp &= ~(CG_DCLK_CNTL__DCLK_सूची_CNTL_EN_MASK |
		CG_DCLK_CNTL__DCLK_DIVIDER_MASK);
	पंचांगp |= भागiders.post_भागider;
	WREG32_SMC(cntl_reg, पंचांगp);

	क्रम (i = 0; i < 100; i++) अणु
		अगर (RREG32_SMC(status_reg) & CG_DCLK_STATUS__DCLK_STATUS_MASK)
			अवरोध;
		mdelay(10);
	पूर्ण
	अगर (i == 100)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक cik_set_uvd_घड़ीs(काष्ठा amdgpu_device *adev, u32 vclk, u32 dclk)
अणु
	पूर्णांक r = 0;

	r = cik_set_uvd_घड़ी(adev, vclk, ixCG_VCLK_CNTL, ixCG_VCLK_STATUS);
	अगर (r)
		वापस r;

	r = cik_set_uvd_घड़ी(adev, dclk, ixCG_DCLK_CNTL, ixCG_DCLK_STATUS);
	वापस r;
पूर्ण

अटल पूर्णांक cik_set_vce_घड़ीs(काष्ठा amdgpu_device *adev, u32 evclk, u32 ecclk)
अणु
	पूर्णांक r, i;
	काष्ठा atom_घड़ी_भागiders भागiders;
	u32 पंचांगp;

	r = amdgpu_atombios_get_घड़ी_भागiders(adev,
					       COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
					       ecclk, false, &भागiders);
	अगर (r)
		वापस r;

	क्रम (i = 0; i < 100; i++) अणु
		अगर (RREG32_SMC(ixCG_ECLK_STATUS) & CG_ECLK_STATUS__ECLK_STATUS_MASK)
			अवरोध;
		mdelay(10);
	पूर्ण
	अगर (i == 100)
		वापस -ETIMEDOUT;

	पंचांगp = RREG32_SMC(ixCG_ECLK_CNTL);
	पंचांगp &= ~(CG_ECLK_CNTL__ECLK_सूची_CNTL_EN_MASK |
		CG_ECLK_CNTL__ECLK_DIVIDER_MASK);
	पंचांगp |= भागiders.post_भागider;
	WREG32_SMC(ixCG_ECLK_CNTL, पंचांगp);

	क्रम (i = 0; i < 100; i++) अणु
		अगर (RREG32_SMC(ixCG_ECLK_STATUS) & CG_ECLK_STATUS__ECLK_STATUS_MASK)
			अवरोध;
		mdelay(10);
	पूर्ण
	अगर (i == 100)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल व्योम cik_pcie_gen3_enable(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा pci_dev *root = adev->pdev->bus->self;
	u32 speed_cntl, current_data_rate;
	पूर्णांक i;
	u16 पंचांगp16;

	अगर (pci_is_root_bus(adev->pdev->bus))
		वापस;

	अगर (amdgpu_pcie_gen2 == 0)
		वापस;

	अगर (adev->flags & AMD_IS_APU)
		वापस;

	अगर (!(adev->pm.pcie_gen_mask & (CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2 |
					CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3)))
		वापस;

	speed_cntl = RREG32_PCIE(ixPCIE_LC_SPEED_CNTL);
	current_data_rate = (speed_cntl & PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE_MASK) >>
		PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE__SHIFT;
	अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3) अणु
		अगर (current_data_rate == 2) अणु
			DRM_INFO("PCIE gen 3 link speeds already enabled\n");
			वापस;
		पूर्ण
		DRM_INFO("enabling PCIE gen 3 link speeds, disable with amdgpu.pcie_gen2=0\n");
	पूर्ण अन्यथा अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2) अणु
		अगर (current_data_rate == 1) अणु
			DRM_INFO("PCIE gen 2 link speeds already enabled\n");
			वापस;
		पूर्ण
		DRM_INFO("enabling PCIE gen 2 link speeds, disable with amdgpu.pcie_gen2=0\n");
	पूर्ण

	अगर (!pci_is_pcie(root) || !pci_is_pcie(adev->pdev))
		वापस;

	अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3) अणु
		/* re-try equalization अगर gen3 is not alपढ़ोy enabled */
		अगर (current_data_rate != 2) अणु
			u16 bridge_cfg, gpu_cfg;
			u16 bridge_cfg2, gpu_cfg2;
			u32 max_lw, current_lw, पंचांगp;

			pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL,
						  &bridge_cfg);
			pcie_capability_पढ़ो_word(adev->pdev, PCI_EXP_LNKCTL,
						  &gpu_cfg);

			पंचांगp16 = bridge_cfg | PCI_EXP_LNKCTL_HAWD;
			pcie_capability_ग_लिखो_word(root, PCI_EXP_LNKCTL, पंचांगp16);

			पंचांगp16 = gpu_cfg | PCI_EXP_LNKCTL_HAWD;
			pcie_capability_ग_लिखो_word(adev->pdev, PCI_EXP_LNKCTL,
						   पंचांगp16);

			पंचांगp = RREG32_PCIE(ixPCIE_LC_STATUS1);
			max_lw = (पंचांगp & PCIE_LC_STATUS1__LC_DETECTED_LINK_WIDTH_MASK) >>
				PCIE_LC_STATUS1__LC_DETECTED_LINK_WIDTH__SHIFT;
			current_lw = (पंचांगp & PCIE_LC_STATUS1__LC_OPERATING_LINK_WIDTH_MASK)
				>> PCIE_LC_STATUS1__LC_OPERATING_LINK_WIDTH__SHIFT;

			अगर (current_lw < max_lw) अणु
				पंचांगp = RREG32_PCIE(ixPCIE_LC_LINK_WIDTH_CNTL);
				अगर (पंचांगp & PCIE_LC_LINK_WIDTH_CNTL__LC_RENEGOTIATION_SUPPORT_MASK) अणु
					पंचांगp &= ~(PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_MASK |
						PCIE_LC_LINK_WIDTH_CNTL__LC_UPCONFIGURE_DIS_MASK);
					पंचांगp |= (max_lw <<
						PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH__SHIFT);
					पंचांगp |= PCIE_LC_LINK_WIDTH_CNTL__LC_UPCONFIGURE_SUPPORT_MASK |
					PCIE_LC_LINK_WIDTH_CNTL__LC_RENEGOTIATE_EN_MASK |
					PCIE_LC_LINK_WIDTH_CNTL__LC_RECONFIG_NOW_MASK;
					WREG32_PCIE(ixPCIE_LC_LINK_WIDTH_CNTL, पंचांगp);
				पूर्ण
			पूर्ण

			क्रम (i = 0; i < 10; i++) अणु
				/* check status */
				pcie_capability_पढ़ो_word(adev->pdev,
							  PCI_EXP_DEVSTA,
							  &पंचांगp16);
				अगर (पंचांगp16 & PCI_EXP_DEVSTA_TRPND)
					अवरोध;

				pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL,
							  &bridge_cfg);
				pcie_capability_पढ़ो_word(adev->pdev,
							  PCI_EXP_LNKCTL,
							  &gpu_cfg);

				pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL2,
							  &bridge_cfg2);
				pcie_capability_पढ़ो_word(adev->pdev,
							  PCI_EXP_LNKCTL2,
							  &gpu_cfg2);

				पंचांगp = RREG32_PCIE(ixPCIE_LC_CNTL4);
				पंचांगp |= PCIE_LC_CNTL4__LC_SET_QUIESCE_MASK;
				WREG32_PCIE(ixPCIE_LC_CNTL4, पंचांगp);

				पंचांगp = RREG32_PCIE(ixPCIE_LC_CNTL4);
				पंचांगp |= PCIE_LC_CNTL4__LC_REDO_EQ_MASK;
				WREG32_PCIE(ixPCIE_LC_CNTL4, पंचांगp);

				msleep(100);

				/* linkctl */
				pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL,
							  &पंचांगp16);
				पंचांगp16 &= ~PCI_EXP_LNKCTL_HAWD;
				पंचांगp16 |= (bridge_cfg & PCI_EXP_LNKCTL_HAWD);
				pcie_capability_ग_लिखो_word(root, PCI_EXP_LNKCTL,
							   पंचांगp16);

				pcie_capability_पढ़ो_word(adev->pdev,
							  PCI_EXP_LNKCTL,
							  &पंचांगp16);
				पंचांगp16 &= ~PCI_EXP_LNKCTL_HAWD;
				पंचांगp16 |= (gpu_cfg & PCI_EXP_LNKCTL_HAWD);
				pcie_capability_ग_लिखो_word(adev->pdev,
							   PCI_EXP_LNKCTL,
							   पंचांगp16);

				/* linkctl2 */
				pcie_capability_पढ़ो_word(root, PCI_EXP_LNKCTL2,
							  &पंचांगp16);
				पंचांगp16 &= ~(PCI_EXP_LNKCTL2_ENTER_COMP |
					   PCI_EXP_LNKCTL2_TX_MARGIN);
				पंचांगp16 |= (bridge_cfg2 &
					  (PCI_EXP_LNKCTL2_ENTER_COMP |
					   PCI_EXP_LNKCTL2_TX_MARGIN));
				pcie_capability_ग_लिखो_word(root,
							   PCI_EXP_LNKCTL2,
							   पंचांगp16);

				pcie_capability_पढ़ो_word(adev->pdev,
							  PCI_EXP_LNKCTL2,
							  &पंचांगp16);
				पंचांगp16 &= ~(PCI_EXP_LNKCTL2_ENTER_COMP |
					   PCI_EXP_LNKCTL2_TX_MARGIN);
				पंचांगp16 |= (gpu_cfg2 &
					  (PCI_EXP_LNKCTL2_ENTER_COMP |
					   PCI_EXP_LNKCTL2_TX_MARGIN));
				pcie_capability_ग_लिखो_word(adev->pdev,
							   PCI_EXP_LNKCTL2,
							   पंचांगp16);

				पंचांगp = RREG32_PCIE(ixPCIE_LC_CNTL4);
				पंचांगp &= ~PCIE_LC_CNTL4__LC_SET_QUIESCE_MASK;
				WREG32_PCIE(ixPCIE_LC_CNTL4, पंचांगp);
			पूर्ण
		पूर्ण
	पूर्ण

	/* set the link speed */
	speed_cntl |= PCIE_LC_SPEED_CNTL__LC_FORCE_EN_SW_SPEED_CHANGE_MASK |
		PCIE_LC_SPEED_CNTL__LC_FORCE_DIS_HW_SPEED_CHANGE_MASK;
	speed_cntl &= ~PCIE_LC_SPEED_CNTL__LC_FORCE_DIS_SW_SPEED_CHANGE_MASK;
	WREG32_PCIE(ixPCIE_LC_SPEED_CNTL, speed_cntl);

	pcie_capability_पढ़ो_word(adev->pdev, PCI_EXP_LNKCTL2, &पंचांगp16);
	पंचांगp16 &= ~PCI_EXP_LNKCTL2_TLS;

	अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3)
		पंचांगp16 |= PCI_EXP_LNKCTL2_TLS_8_0GT; /* gen3 */
	अन्यथा अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2)
		पंचांगp16 |= PCI_EXP_LNKCTL2_TLS_5_0GT; /* gen2 */
	अन्यथा
		पंचांगp16 |= PCI_EXP_LNKCTL2_TLS_2_5GT; /* gen1 */
	pcie_capability_ग_लिखो_word(adev->pdev, PCI_EXP_LNKCTL2, पंचांगp16);

	speed_cntl = RREG32_PCIE(ixPCIE_LC_SPEED_CNTL);
	speed_cntl |= PCIE_LC_SPEED_CNTL__LC_INITIATE_LINK_SPEED_CHANGE_MASK;
	WREG32_PCIE(ixPCIE_LC_SPEED_CNTL, speed_cntl);

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		speed_cntl = RREG32_PCIE(ixPCIE_LC_SPEED_CNTL);
		अगर ((speed_cntl & PCIE_LC_SPEED_CNTL__LC_INITIATE_LINK_SPEED_CHANGE_MASK) == 0)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम cik_program_aspm(काष्ठा amdgpu_device *adev)
अणु
	u32 data, orig;
	bool disable_l0s = false, disable_l1 = false, disable_plloff_in_l1 = false;
	bool disable_clkreq = false;

	अगर (amdgpu_aspm == 0)
		वापस;

	अगर (pci_is_root_bus(adev->pdev->bus))
		वापस;

	/* XXX द्विगुन check APUs */
	अगर (adev->flags & AMD_IS_APU)
		वापस;

	orig = data = RREG32_PCIE(ixPCIE_LC_N_FTS_CNTL);
	data &= ~PCIE_LC_N_FTS_CNTL__LC_XMIT_N_FTS_MASK;
	data |= (0x24 << PCIE_LC_N_FTS_CNTL__LC_XMIT_N_FTS__SHIFT) |
		PCIE_LC_N_FTS_CNTL__LC_XMIT_N_FTS_OVERRIDE_EN_MASK;
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

	orig = data = RREG32_PCIE(ixPCIE_LC_CNTL);
	data &= ~(PCIE_LC_CNTL__LC_L0S_INACTIVITY_MASK |
		PCIE_LC_CNTL__LC_L1_INACTIVITY_MASK);
	data |= PCIE_LC_CNTL__LC_PMI_TO_L1_DIS_MASK;
	अगर (!disable_l0s)
		data |= (7 << PCIE_LC_CNTL__LC_L0S_INACTIVITY__SHIFT);

	अगर (!disable_l1) अणु
		data |= (7 << PCIE_LC_CNTL__LC_L1_INACTIVITY__SHIFT);
		data &= ~PCIE_LC_CNTL__LC_PMI_TO_L1_DIS_MASK;
		अगर (orig != data)
			WREG32_PCIE(ixPCIE_LC_CNTL, data);

		अगर (!disable_plloff_in_l1) अणु
			bool clk_req_support;

			orig = data = RREG32_PCIE(ixPB0_PIF_PWRDOWN_0);
			data &= ~(PB0_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_OFF_0_MASK |
				PB0_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= (7 << PB0_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_OFF_0__SHIFT) |
				(7 << PB0_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_TXS2_0__SHIFT);
			अगर (orig != data)
				WREG32_PCIE(ixPB0_PIF_PWRDOWN_0, data);

			orig = data = RREG32_PCIE(ixPB0_PIF_PWRDOWN_1);
			data &= ~(PB0_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_OFF_1_MASK |
				PB0_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= (7 << PB0_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_OFF_1__SHIFT) |
				(7 << PB0_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_TXS2_1__SHIFT);
			अगर (orig != data)
				WREG32_PCIE(ixPB0_PIF_PWRDOWN_1, data);

			orig = data = RREG32_PCIE(ixPB1_PIF_PWRDOWN_0);
			data &= ~(PB1_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_OFF_0_MASK |
				PB1_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= (7 << PB1_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_OFF_0__SHIFT) |
				(7 << PB1_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_TXS2_0__SHIFT);
			अगर (orig != data)
				WREG32_PCIE(ixPB1_PIF_PWRDOWN_0, data);

			orig = data = RREG32_PCIE(ixPB1_PIF_PWRDOWN_1);
			data &= ~(PB1_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_OFF_1_MASK |
				PB1_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= (7 << PB1_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_OFF_1__SHIFT) |
				(7 << PB1_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_TXS2_1__SHIFT);
			अगर (orig != data)
				WREG32_PCIE(ixPB1_PIF_PWRDOWN_1, data);

			orig = data = RREG32_PCIE(ixPCIE_LC_LINK_WIDTH_CNTL);
			data &= ~PCIE_LC_LINK_WIDTH_CNTL__LC_DYN_LANES_PWR_STATE_MASK;
			data |= ~(3 << PCIE_LC_LINK_WIDTH_CNTL__LC_DYN_LANES_PWR_STATE__SHIFT);
			अगर (orig != data)
				WREG32_PCIE(ixPCIE_LC_LINK_WIDTH_CNTL, data);

			अगर (!disable_clkreq) अणु
				काष्ठा pci_dev *root = adev->pdev->bus->self;
				u32 lnkcap;

				clk_req_support = false;
				pcie_capability_पढ़ो_dword(root, PCI_EXP_LNKCAP, &lnkcap);
				अगर (lnkcap & PCI_EXP_LNKCAP_CLKPM)
					clk_req_support = true;
			पूर्ण अन्यथा अणु
				clk_req_support = false;
			पूर्ण

			अगर (clk_req_support) अणु
				orig = data = RREG32_PCIE(ixPCIE_LC_CNTL2);
				data |= PCIE_LC_CNTL2__LC_ALLOW_PDWN_IN_L1_MASK |
					PCIE_LC_CNTL2__LC_ALLOW_PDWN_IN_L23_MASK;
				अगर (orig != data)
					WREG32_PCIE(ixPCIE_LC_CNTL2, data);

				orig = data = RREG32_SMC(ixTHM_CLK_CNTL);
				data &= ~(THM_CLK_CNTL__CMON_CLK_SEL_MASK |
					THM_CLK_CNTL__TMON_CLK_SEL_MASK);
				data |= (1 << THM_CLK_CNTL__CMON_CLK_SEL__SHIFT) |
					(1 << THM_CLK_CNTL__TMON_CLK_SEL__SHIFT);
				अगर (orig != data)
					WREG32_SMC(ixTHM_CLK_CNTL, data);

				orig = data = RREG32_SMC(ixMISC_CLK_CTRL);
				data &= ~(MISC_CLK_CTRL__DEEP_SLEEP_CLK_SEL_MASK |
					MISC_CLK_CTRL__ZCLK_SEL_MASK);
				data |= (1 << MISC_CLK_CTRL__DEEP_SLEEP_CLK_SEL__SHIFT) |
					(1 << MISC_CLK_CTRL__ZCLK_SEL__SHIFT);
				अगर (orig != data)
					WREG32_SMC(ixMISC_CLK_CTRL, data);

				orig = data = RREG32_SMC(ixCG_CLKPIN_CNTL);
				data &= ~CG_CLKPIN_CNTL__BCLK_AS_XCLK_MASK;
				अगर (orig != data)
					WREG32_SMC(ixCG_CLKPIN_CNTL, data);

				orig = data = RREG32_SMC(ixCG_CLKPIN_CNTL_2);
				data &= ~CG_CLKPIN_CNTL_2__FORCE_BIF_REFCLK_EN_MASK;
				अगर (orig != data)
					WREG32_SMC(ixCG_CLKPIN_CNTL_2, data);

				orig = data = RREG32_SMC(ixMPLL_BYPASSCLK_SEL);
				data &= ~MPLL_BYPASSCLK_SEL__MPLL_CLKOUT_SEL_MASK;
				data |= (4 << MPLL_BYPASSCLK_SEL__MPLL_CLKOUT_SEL__SHIFT);
				अगर (orig != data)
					WREG32_SMC(ixMPLL_BYPASSCLK_SEL, data);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (orig != data)
			WREG32_PCIE(ixPCIE_LC_CNTL, data);
	पूर्ण

	orig = data = RREG32_PCIE(ixPCIE_CNTL2);
	data |= PCIE_CNTL2__SLV_MEM_LS_EN_MASK |
		PCIE_CNTL2__MST_MEM_LS_EN_MASK |
		PCIE_CNTL2__REPLAY_MEM_LS_EN_MASK;
	अगर (orig != data)
		WREG32_PCIE(ixPCIE_CNTL2, data);

	अगर (!disable_l0s) अणु
		data = RREG32_PCIE(ixPCIE_LC_N_FTS_CNTL);
		अगर ((data & PCIE_LC_N_FTS_CNTL__LC_N_FTS_MASK) ==
				PCIE_LC_N_FTS_CNTL__LC_N_FTS_MASK) अणु
			data = RREG32_PCIE(ixPCIE_LC_STATUS1);
			अगर ((data & PCIE_LC_STATUS1__LC_REVERSE_XMIT_MASK) &&
			(data & PCIE_LC_STATUS1__LC_REVERSE_RCVR_MASK)) अणु
				orig = data = RREG32_PCIE(ixPCIE_LC_CNTL);
				data &= ~PCIE_LC_CNTL__LC_L0S_INACTIVITY_MASK;
				अगर (orig != data)
					WREG32_PCIE(ixPCIE_LC_CNTL, data);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल uपूर्णांक32_t cik_get_rev_id(काष्ठा amdgpu_device *adev)
अणु
	वापस (RREG32(mmCC_DRM_ID_STRAPS) & CC_DRM_ID_STRAPS__ATI_REV_ID_MASK)
		>> CC_DRM_ID_STRAPS__ATI_REV_ID__SHIFT;
पूर्ण

अटल व्योम cik_flush_hdp(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ring *ring)
अणु
	अगर (!ring || !ring->funcs->emit_wreg) अणु
		WREG32(mmHDP_MEM_COHERENCY_FLUSH_CNTL, 1);
		RREG32(mmHDP_MEM_COHERENCY_FLUSH_CNTL);
	पूर्ण अन्यथा अणु
		amdgpu_ring_emit_wreg(ring, mmHDP_MEM_COHERENCY_FLUSH_CNTL, 1);
	पूर्ण
पूर्ण

अटल व्योम cik_invalidate_hdp(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_ring *ring)
अणु
	अगर (!ring || !ring->funcs->emit_wreg) अणु
		WREG32(mmHDP_DEBUG0, 1);
		RREG32(mmHDP_DEBUG0);
	पूर्ण अन्यथा अणु
		amdgpu_ring_emit_wreg(ring, mmHDP_DEBUG0, 1);
	पूर्ण
पूर्ण

अटल bool cik_need_full_reset(काष्ठा amdgpu_device *adev)
अणु
	/* change this when we support soft reset */
	वापस true;
पूर्ण

अटल व्योम cik_get_pcie_usage(काष्ठा amdgpu_device *adev, uपूर्णांक64_t *count0,
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

अटल bool cik_need_reset_on_init(काष्ठा amdgpu_device *adev)
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

अटल uपूर्णांक64_t cik_get_pcie_replay_count(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t nak_r, nak_g;

	/* Get the number of NAKs received and generated */
	nak_r = RREG32_PCIE(ixPCIE_RX_NUM_NAK);
	nak_g = RREG32_PCIE(ixPCIE_RX_NUM_NAK_GENERATED);

	/* Add the total number of NAKs, i.e the number of replays */
	वापस (nak_r + nak_g);
पूर्ण

अटल व्योम cik_pre_asic_init(काष्ठा amdgpu_device *adev)
अणु
पूर्ण

अटल स्थिर काष्ठा amdgpu_asic_funcs cik_asic_funcs =
अणु
	.पढ़ो_disabled_bios = &cik_पढ़ो_disabled_bios,
	.पढ़ो_bios_from_rom = &cik_पढ़ो_bios_from_rom,
	.पढ़ो_रेजिस्टर = &cik_पढ़ो_रेजिस्टर,
	.reset = &cik_asic_reset,
	.reset_method = &cik_asic_reset_method,
	.set_vga_state = &cik_vga_set_state,
	.get_xclk = &cik_get_xclk,
	.set_uvd_घड़ीs = &cik_set_uvd_घड़ीs,
	.set_vce_घड़ीs = &cik_set_vce_घड़ीs,
	.get_config_memsize = &cik_get_config_memsize,
	.flush_hdp = &cik_flush_hdp,
	.invalidate_hdp = &cik_invalidate_hdp,
	.need_full_reset = &cik_need_full_reset,
	.init_करोorbell_index = &legacy_करोorbell_index_init,
	.get_pcie_usage = &cik_get_pcie_usage,
	.need_reset_on_init = &cik_need_reset_on_init,
	.get_pcie_replay_count = &cik_get_pcie_replay_count,
	.supports_baco = &cik_asic_supports_baco,
	.pre_asic_init = &cik_pre_asic_init,
	.query_video_codecs = &cik_query_video_codecs,
पूर्ण;

अटल पूर्णांक cik_common_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->smc_rreg = &cik_smc_rreg;
	adev->smc_wreg = &cik_smc_wreg;
	adev->pcie_rreg = &cik_pcie_rreg;
	adev->pcie_wreg = &cik_pcie_wreg;
	adev->uvd_ctx_rreg = &cik_uvd_ctx_rreg;
	adev->uvd_ctx_wreg = &cik_uvd_ctx_wreg;
	adev->didt_rreg = &cik_didt_rreg;
	adev->didt_wreg = &cik_didt_wreg;

	adev->asic_funcs = &cik_asic_funcs;

	adev->rev_id = cik_get_rev_id(adev);
	adev->बाह्यal_rev_id = 0xFF;
	चयन (adev->asic_type) अणु
	हाल CHIP_BONAIRE:
		adev->cg_flags =
			AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			/*AMD_CG_SUPPORT_GFX_CGCG |*/
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_CGTS |
			AMD_CG_SUPPORT_GFX_CGTS_LS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_VCE_MGCG |
			AMD_CG_SUPPORT_UVD_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_HDP_MGCG;
		adev->pg_flags = 0;
		adev->बाह्यal_rev_id = adev->rev_id + 0x14;
		अवरोध;
	हाल CHIP_HAWAII:
		adev->cg_flags =
			AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			/*AMD_CG_SUPPORT_GFX_CGCG |*/
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_CGTS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_MC_LS |
			AMD_CG_SUPPORT_MC_MGCG |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_VCE_MGCG |
			AMD_CG_SUPPORT_UVD_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_HDP_MGCG;
		adev->pg_flags = 0;
		adev->बाह्यal_rev_id = 0x28;
		अवरोध;
	हाल CHIP_KAVERI:
		adev->cg_flags =
			AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			/*AMD_CG_SUPPORT_GFX_CGCG |*/
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_CGTS |
			AMD_CG_SUPPORT_GFX_CGTS_LS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_VCE_MGCG |
			AMD_CG_SUPPORT_UVD_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_HDP_MGCG;
		adev->pg_flags =
			/*AMD_PG_SUPPORT_GFX_PG |
			  AMD_PG_SUPPORT_GFX_SMG |
			  AMD_PG_SUPPORT_GFX_DMG |*/
			AMD_PG_SUPPORT_UVD |
			AMD_PG_SUPPORT_VCE |
			/*  AMD_PG_SUPPORT_CP |
			  AMD_PG_SUPPORT_GDS |
			  AMD_PG_SUPPORT_RLC_SMU_HS |
			  AMD_PG_SUPPORT_ACP |
			  AMD_PG_SUPPORT_SAMU |*/
			0;
		अगर (adev->pdev->device == 0x1312 ||
			adev->pdev->device == 0x1316 ||
			adev->pdev->device == 0x1317)
			adev->बाह्यal_rev_id = 0x41;
		अन्यथा
			adev->बाह्यal_rev_id = 0x1;
		अवरोध;
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
		adev->cg_flags =
			AMD_CG_SUPPORT_GFX_MGCG |
			AMD_CG_SUPPORT_GFX_MGLS |
			/*AMD_CG_SUPPORT_GFX_CGCG |*/
			AMD_CG_SUPPORT_GFX_CGLS |
			AMD_CG_SUPPORT_GFX_CGTS |
			AMD_CG_SUPPORT_GFX_CGTS_LS |
			AMD_CG_SUPPORT_GFX_CP_LS |
			AMD_CG_SUPPORT_SDMA_MGCG |
			AMD_CG_SUPPORT_SDMA_LS |
			AMD_CG_SUPPORT_BIF_LS |
			AMD_CG_SUPPORT_VCE_MGCG |
			AMD_CG_SUPPORT_UVD_MGCG |
			AMD_CG_SUPPORT_HDP_LS |
			AMD_CG_SUPPORT_HDP_MGCG;
		adev->pg_flags =
			/*AMD_PG_SUPPORT_GFX_PG |
			  AMD_PG_SUPPORT_GFX_SMG | */
			AMD_PG_SUPPORT_UVD |
			/*AMD_PG_SUPPORT_VCE |
			  AMD_PG_SUPPORT_CP |
			  AMD_PG_SUPPORT_GDS |
			  AMD_PG_SUPPORT_RLC_SMU_HS |
			  AMD_PG_SUPPORT_SAMU |*/
			0;
		अगर (adev->asic_type == CHIP_KABINI) अणु
			अगर (adev->rev_id == 0)
				adev->बाह्यal_rev_id = 0x81;
			अन्यथा अगर (adev->rev_id == 1)
				adev->बाह्यal_rev_id = 0x82;
			अन्यथा अगर (adev->rev_id == 2)
				adev->बाह्यal_rev_id = 0x85;
		पूर्ण अन्यथा
			adev->बाह्यal_rev_id = adev->rev_id + 0xa1;
		अवरोध;
	शेष:
		/* FIXME: not supported yet */
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cik_common_sw_init(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक cik_common_sw_fini(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक cik_common_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* move the golden regs per IP block */
	cik_init_golden_रेजिस्टरs(adev);
	/* enable pcie gen2/3 link */
	cik_pcie_gen3_enable(adev);
	/* enable aspm */
	cik_program_aspm(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक cik_common_hw_fini(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक cik_common_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस cik_common_hw_fini(adev);
पूर्ण

अटल पूर्णांक cik_common_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस cik_common_hw_init(adev);
पूर्ण

अटल bool cik_common_is_idle(व्योम *handle)
अणु
	वापस true;
पूर्ण

अटल पूर्णांक cik_common_रुको_क्रम_idle(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक cik_common_soft_reset(व्योम *handle)
अणु
	/* XXX hard reset?? */
	वापस 0;
पूर्ण

अटल पूर्णांक cik_common_set_घड़ीgating_state(व्योम *handle,
					    क्रमागत amd_घड़ीgating_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक cik_common_set_घातergating_state(व्योम *handle,
					    क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs cik_common_ip_funcs = अणु
	.name = "cik_common",
	.early_init = cik_common_early_init,
	.late_init = शून्य,
	.sw_init = cik_common_sw_init,
	.sw_fini = cik_common_sw_fini,
	.hw_init = cik_common_hw_init,
	.hw_fini = cik_common_hw_fini,
	.suspend = cik_common_suspend,
	.resume = cik_common_resume,
	.is_idle = cik_common_is_idle,
	.रुको_क्रम_idle = cik_common_रुको_क्रम_idle,
	.soft_reset = cik_common_soft_reset,
	.set_घड़ीgating_state = cik_common_set_घड़ीgating_state,
	.set_घातergating_state = cik_common_set_घातergating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ip_block_version cik_common_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_COMMON,
	.major = 1,
	.minor = 0,
	.rev = 0,
	.funcs = &cik_common_ip_funcs,
पूर्ण;

पूर्णांक cik_set_ip_blocks(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_BONAIRE:
		amdgpu_device_ip_block_add(adev, &cik_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v7_0_ip_block);
		amdgpu_device_ip_block_add(adev, &cik_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v7_2_ip_block);
		amdgpu_device_ip_block_add(adev, &cik_sdma_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		अगर (adev->enable_भव_display)
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		अन्यथा
			amdgpu_device_ip_block_add(adev, &dce_v8_2_ip_block);
		amdgpu_device_ip_block_add(adev, &uvd_v4_2_ip_block);
		amdgpu_device_ip_block_add(adev, &vce_v2_0_ip_block);
		अवरोध;
	हाल CHIP_HAWAII:
		amdgpu_device_ip_block_add(adev, &cik_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v7_0_ip_block);
		amdgpu_device_ip_block_add(adev, &cik_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v7_3_ip_block);
		amdgpu_device_ip_block_add(adev, &cik_sdma_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		अगर (adev->enable_भव_display)
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		अन्यथा
			amdgpu_device_ip_block_add(adev, &dce_v8_5_ip_block);
		amdgpu_device_ip_block_add(adev, &uvd_v4_2_ip_block);
		amdgpu_device_ip_block_add(adev, &vce_v2_0_ip_block);
		अवरोध;
	हाल CHIP_KAVERI:
		amdgpu_device_ip_block_add(adev, &cik_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v7_0_ip_block);
		amdgpu_device_ip_block_add(adev, &cik_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v7_1_ip_block);
		amdgpu_device_ip_block_add(adev, &cik_sdma_ip_block);
		amdgpu_device_ip_block_add(adev, &kv_smu_ip_block);
		अगर (adev->enable_भव_display)
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		अन्यथा
			amdgpu_device_ip_block_add(adev, &dce_v8_1_ip_block);

		amdgpu_device_ip_block_add(adev, &uvd_v4_2_ip_block);
		amdgpu_device_ip_block_add(adev, &vce_v2_0_ip_block);
		अवरोध;
	हाल CHIP_KABINI:
	हाल CHIP_MULLINS:
		amdgpu_device_ip_block_add(adev, &cik_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v7_0_ip_block);
		amdgpu_device_ip_block_add(adev, &cik_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v7_2_ip_block);
		amdgpu_device_ip_block_add(adev, &cik_sdma_ip_block);
		amdgpu_device_ip_block_add(adev, &kv_smu_ip_block);
		अगर (adev->enable_भव_display)
			amdgpu_device_ip_block_add(adev, &dce_भव_ip_block);
#अगर defined(CONFIG_DRM_AMD_DC)
		अन्यथा अगर (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#पूर्ण_अगर
		अन्यथा
			amdgpu_device_ip_block_add(adev, &dce_v8_3_ip_block);
		amdgpu_device_ip_block_add(adev, &uvd_v4_2_ip_block);
		amdgpu_device_ip_block_add(adev, &vce_v2_0_ip_block);
		अवरोध;
	शेष:
		/* FIXME: not supported yet */
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
