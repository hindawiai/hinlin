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

#अगर_अघोषित __VF_ERROR_H__
#घोषणा __VF_ERROR_H__

#घोषणा AMDGIM_ERROR_CODE_FLAGS_TO_MAILBOX(c,f)    (((c & 0xFFFF) << 16) | (f & 0xFFFF))
#घोषणा AMDGIM_ERROR_CODE(t,c)       (((t&0xF)<<12)|(c&0xFFF))

/* Please keep क्रमागत same as AMD GIM driver */
क्रमागत AMDGIM_ERROR_VF अणु
	AMDGIM_ERROR_VF_ATOMBIOS_INIT_FAIL = 0,
	AMDGIM_ERROR_VF_NO_VBIOS,
	AMDGIM_ERROR_VF_GPU_POST_ERROR,
	AMDGIM_ERROR_VF_ATOMBIOS_GET_CLOCK_FAIL,
	AMDGIM_ERROR_VF_FENCE_INIT_FAIL,

	AMDGIM_ERROR_VF_AMDGPU_INIT_FAIL,
	AMDGIM_ERROR_VF_IB_INIT_FAIL,
	AMDGIM_ERROR_VF_AMDGPU_LATE_INIT_FAIL,
	AMDGIM_ERROR_VF_ASIC_RESUME_FAIL,
	AMDGIM_ERROR_VF_GPU_RESET_FAIL,

	AMDGIM_ERROR_VF_TEST,
	AMDGIM_ERROR_VF_MAX
पूर्ण;

क्रमागत AMDGIM_ERROR_CATEGORY अणु
	AMDGIM_ERROR_CATEGORY_NON_USED = 0,
	AMDGIM_ERROR_CATEGORY_GIM,
	AMDGIM_ERROR_CATEGORY_PF,
	AMDGIM_ERROR_CATEGORY_VF,
	AMDGIM_ERROR_CATEGORY_VBIOS,
	AMDGIM_ERROR_CATEGORY_MONITOR,

	AMDGIM_ERROR_CATEGORY_MAX
पूर्ण;

व्योम amdgpu_vf_error_put(काष्ठा amdgpu_device *adev,
			 uपूर्णांक16_t sub_error_code,
			 uपूर्णांक16_t error_flags,
			 uपूर्णांक64_t error_data);
व्योम amdgpu_vf_error_trans_all (काष्ठा amdgpu_device *adev);

#पूर्ण_अगर /* __VF_ERROR_H__ */
