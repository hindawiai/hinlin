<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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
#समावेश "amdgpu.h"
#समावेश "soc15.h"

#समावेश "soc15_common.h"
#समावेश "vega10_ip_offset.h"

पूर्णांक vega10_reg_base_init(काष्ठा amdgpu_device *adev)
अणु
	/* HW has more IP blocks,  only initialized the blocke beend by our driver  */
	uपूर्णांक32_t i;
	क्रम (i = 0 ; i < MAX_INSTANCE ; ++i) अणु
		adev->reg_offset[GC_HWIP][i] = (uपूर्णांक32_t *)(&(GC_BASE.instance[i]));
		adev->reg_offset[HDP_HWIP][i] = (uपूर्णांक32_t *)(&(HDP_BASE.instance[i]));
		adev->reg_offset[MMHUB_HWIP][i] = (uपूर्णांक32_t *)(&(MMHUB_BASE.instance[i]));
		adev->reg_offset[ATHUB_HWIP][i] = (uपूर्णांक32_t *)(&(ATHUB_BASE.instance[i]));
		adev->reg_offset[NBIO_HWIP][i] = (uपूर्णांक32_t *)(&(NBIO_BASE.instance[i]));
		adev->reg_offset[MP0_HWIP][i] = (uपूर्णांक32_t *)(&(MP0_BASE.instance[i]));
		adev->reg_offset[MP1_HWIP][i] = (uपूर्णांक32_t *)(&(MP1_BASE.instance[i]));
		adev->reg_offset[UVD_HWIP][i] = (uपूर्णांक32_t *)(&(UVD_BASE.instance[i]));
		adev->reg_offset[VCE_HWIP][i] = (uपूर्णांक32_t *)(&(VCE_BASE.instance[i]));
		adev->reg_offset[VCN_HWIP][i] = (uपूर्णांक32_t *)(&(VCN_BASE.instance[i]));
		adev->reg_offset[DF_HWIP][i] = (uपूर्णांक32_t *)(&(DF_BASE.instance[i]));
		adev->reg_offset[DCE_HWIP][i] = (uपूर्णांक32_t *)(&(DCE_BASE.instance[i]));
		adev->reg_offset[OSSSYS_HWIP][i] = (uपूर्णांक32_t *)(&(OSSSYS_BASE.instance[i]));
		adev->reg_offset[SDMA0_HWIP][i] = (uपूर्णांक32_t *)(&(SDMA0_BASE.instance[i]));
		adev->reg_offset[SDMA1_HWIP][i] = (uपूर्णांक32_t *)(&(SDMA1_BASE.instance[i]));
		adev->reg_offset[SMUIO_HWIP][i] = (uपूर्णांक32_t *)(&(SMUIO_BASE.instance[i]));
		adev->reg_offset[PWR_HWIP][i] = (uपूर्णांक32_t *)(&(PWR_BASE.instance[i]));
		adev->reg_offset[NBIF_HWIP][i] = (uपूर्णांक32_t *)(&(NBIF_BASE.instance[i]));
		adev->reg_offset[THM_HWIP][i] = (uपूर्णांक32_t *)(&(THM_BASE.instance[i]));
		adev->reg_offset[CLK_HWIP][i] = (uपूर्णांक32_t *)(&(CLK_BASE.instance[i]));
	पूर्ण
	वापस 0;
पूर्ण

व्योम vega10_करोorbell_index_init(काष्ठा amdgpu_device *adev)
अणु
	adev->करोorbell_index.kiq = AMDGPU_DOORBELL64_KIQ;
	adev->करोorbell_index.mec_ring0 = AMDGPU_DOORBELL64_MEC_RING0;
	adev->करोorbell_index.mec_ring1 = AMDGPU_DOORBELL64_MEC_RING1;
	adev->करोorbell_index.mec_ring2 = AMDGPU_DOORBELL64_MEC_RING2;
	adev->करोorbell_index.mec_ring3 = AMDGPU_DOORBELL64_MEC_RING3;
	adev->करोorbell_index.mec_ring4 = AMDGPU_DOORBELL64_MEC_RING4;
	adev->करोorbell_index.mec_ring5 = AMDGPU_DOORBELL64_MEC_RING5;
	adev->करोorbell_index.mec_ring6 = AMDGPU_DOORBELL64_MEC_RING6;
	adev->करोorbell_index.mec_ring7 = AMDGPU_DOORBELL64_MEC_RING7;
	adev->करोorbell_index.userqueue_start = AMDGPU_DOORBELL64_USERQUEUE_START;
	adev->करोorbell_index.userqueue_end = AMDGPU_DOORBELL64_USERQUEUE_END;
	adev->करोorbell_index.gfx_ring0 = AMDGPU_DOORBELL64_GFX_RING0;
	adev->करोorbell_index.sdma_engine[0] = AMDGPU_DOORBELL64_sDMA_ENGINE0;
	adev->करोorbell_index.sdma_engine[1] = AMDGPU_DOORBELL64_sDMA_ENGINE1;
	adev->करोorbell_index.ih = AMDGPU_DOORBELL64_IH;
	adev->करोorbell_index.uvd_vce.uvd_ring0_1 = AMDGPU_DOORBELL64_UVD_RING0_1;
	adev->करोorbell_index.uvd_vce.uvd_ring2_3 = AMDGPU_DOORBELL64_UVD_RING2_3;
	adev->करोorbell_index.uvd_vce.uvd_ring4_5 = AMDGPU_DOORBELL64_UVD_RING4_5;
	adev->करोorbell_index.uvd_vce.uvd_ring6_7 = AMDGPU_DOORBELL64_UVD_RING6_7;
	adev->करोorbell_index.uvd_vce.vce_ring0_1 = AMDGPU_DOORBELL64_VCE_RING0_1;
	adev->करोorbell_index.uvd_vce.vce_ring2_3 = AMDGPU_DOORBELL64_VCE_RING2_3;
	adev->करोorbell_index.uvd_vce.vce_ring4_5 = AMDGPU_DOORBELL64_VCE_RING4_5;
	adev->करोorbell_index.uvd_vce.vce_ring6_7 = AMDGPU_DOORBELL64_VCE_RING6_7;
	adev->करोorbell_index.vcn.vcn_ring0_1 = AMDGPU_DOORBELL64_VCN0_1;
	adev->करोorbell_index.vcn.vcn_ring2_3 = AMDGPU_DOORBELL64_VCN2_3;
	adev->करोorbell_index.vcn.vcn_ring4_5 = AMDGPU_DOORBELL64_VCN4_5;
	adev->करोorbell_index.vcn.vcn_ring6_7 = AMDGPU_DOORBELL64_VCN6_7;

	adev->करोorbell_index.first_non_cp = AMDGPU_DOORBELL64_FIRST_NON_CP;
	adev->करोorbell_index.last_non_cp = AMDGPU_DOORBELL64_LAST_NON_CP;

	/* In unit of dword करोorbell */
	adev->करोorbell_index.max_assignment = AMDGPU_DOORBELL64_MAX_ASSIGNMENT << 1;
	adev->करोorbell_index.sdma_करोorbell_range = 4;
पूर्ण

