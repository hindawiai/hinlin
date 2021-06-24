<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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
#समावेश "nv.h"

#समावेश "soc15_common.h"
#समावेश "navi14_ip_offset.h"

पूर्णांक navi14_reg_base_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0 ; i < MAX_INSTANCE ; ++i) अणु
		adev->reg_offset[GC_HWIP][i] = (uपूर्णांक32_t *)(&(GC_BASE.instance[i]));
		adev->reg_offset[HDP_HWIP][i] = (uपूर्णांक32_t *)(&(HDP_BASE.instance[i]));
		adev->reg_offset[MMHUB_HWIP][i] = (uपूर्णांक32_t *)(&(MMHUB_BASE.instance[i]));
		adev->reg_offset[ATHUB_HWIP][i] = (uपूर्णांक32_t *)(&(ATHUB_BASE.instance[i]));
		adev->reg_offset[NBIO_HWIP][i] = (uपूर्णांक32_t *)(&(NBIF0_BASE.instance[i]));
		adev->reg_offset[MP0_HWIP][i] = (uपूर्णांक32_t *)(&(MP0_BASE.instance[i]));
		adev->reg_offset[MP1_HWIP][i] = (uपूर्णांक32_t *)(&(MP1_BASE.instance[i]));
		adev->reg_offset[VCN_HWIP][i] = (uपूर्णांक32_t *)(&(UVD0_BASE.instance[i]));
		adev->reg_offset[DF_HWIP][i] = (uपूर्णांक32_t *)(&(DF_BASE.instance[i]));
		adev->reg_offset[DCE_HWIP][i] = (uपूर्णांक32_t *)(&(DMU_BASE.instance[i]));
		adev->reg_offset[OSSSYS_HWIP][i] = (uपूर्णांक32_t *)(&(OSSSYS_BASE.instance[i]));
		adev->reg_offset[SDMA0_HWIP][i] = (uपूर्णांक32_t *)(&(GC_BASE.instance[i]));
		adev->reg_offset[SDMA1_HWIP][i] = (uपूर्णांक32_t *)(&(GC_BASE.instance[i]));
		adev->reg_offset[SMUIO_HWIP][i] = (uपूर्णांक32_t *)(&(SMUIO_BASE.instance[i]));
		adev->reg_offset[THM_HWIP][i] = (uपूर्णांक32_t *)(&(THM_BASE.instance[i]));
		adev->reg_offset[CLK_HWIP][i] = (uपूर्णांक32_t *)(&(CLK_BASE.instance[i]));
	पूर्ण

	वापस 0;
पूर्ण
