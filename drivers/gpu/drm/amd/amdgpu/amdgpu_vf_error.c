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
#समावेश "amdgpu_vf_error.h"
#समावेश "mxgpu_ai.h"

व्योम amdgpu_vf_error_put(काष्ठा amdgpu_device *adev,
			 uपूर्णांक16_t sub_error_code,
			 uपूर्णांक16_t error_flags,
			 uपूर्णांक64_t error_data)
अणु
	पूर्णांक index;
	uपूर्णांक16_t error_code;

	अगर (!amdgpu_sriov_vf(adev))
		वापस;

	error_code = AMDGIM_ERROR_CODE(AMDGIM_ERROR_CATEGORY_VF, sub_error_code);

	mutex_lock(&adev->virt.vf_errors.lock);
	index = adev->virt.vf_errors.ग_लिखो_count % AMDGPU_VF_ERROR_ENTRY_SIZE;
	adev->virt.vf_errors.code [index] = error_code;
	adev->virt.vf_errors.flags [index] = error_flags;
	adev->virt.vf_errors.data [index] = error_data;
	adev->virt.vf_errors.ग_लिखो_count ++;
	mutex_unlock(&adev->virt.vf_errors.lock);
पूर्ण


व्योम amdgpu_vf_error_trans_all(काष्ठा amdgpu_device *adev)
अणु
	/* u32 pf2vf_flags = 0; */
	u32 data1, data2, data3;
	पूर्णांक index;

	अगर ((शून्य == adev) || (!amdgpu_sriov_vf(adev)) ||
	    (!adev->virt.ops) || (!adev->virt.ops->trans_msg)) अणु
		वापस;
	पूर्ण
/*
	TODO: Enable these code when pv2vf_info is merged
	AMDGPU_FW_VRAM_PF2VF_READ (adev, feature_flags, &pf2vf_flags);
	अगर (!(pf2vf_flags & AMDGIM_FEATURE_ERROR_LOG_COLLECT)) अणु
		वापस;
	पूर्ण
*/

	mutex_lock(&adev->virt.vf_errors.lock);
	/* The errors are overlay of array, correct पढ़ो_count as full. */
	अगर (adev->virt.vf_errors.ग_लिखो_count - adev->virt.vf_errors.पढ़ो_count > AMDGPU_VF_ERROR_ENTRY_SIZE) अणु
		adev->virt.vf_errors.पढ़ो_count = adev->virt.vf_errors.ग_लिखो_count - AMDGPU_VF_ERROR_ENTRY_SIZE;
	पूर्ण

	जबतक (adev->virt.vf_errors.पढ़ो_count < adev->virt.vf_errors.ग_लिखो_count) अणु
		index =adev->virt.vf_errors.पढ़ो_count % AMDGPU_VF_ERROR_ENTRY_SIZE;
		data1 = AMDGIM_ERROR_CODE_FLAGS_TO_MAILBOX(adev->virt.vf_errors.code[index],
							   adev->virt.vf_errors.flags[index]);
		data2 = adev->virt.vf_errors.data[index] & 0xFFFFFFFF;
		data3 = (adev->virt.vf_errors.data[index] >> 32) & 0xFFFFFFFF;

		adev->virt.ops->trans_msg(adev, IDH_LOG_VF_ERROR, data1, data2, data3);
		adev->virt.vf_errors.पढ़ो_count ++;
	पूर्ण
	mutex_unlock(&adev->virt.vf_errors.lock);
पूर्ण
