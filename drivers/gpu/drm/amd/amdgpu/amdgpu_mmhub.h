<शैली गुरु>
/*
 * Copyright (C) 2019  Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#अगर_अघोषित __AMDGPU_MMHUB_H__
#घोषणा __AMDGPU_MMHUB_H__

काष्ठा amdgpu_mmhub_ras_funcs अणु
	पूर्णांक (*ras_late_init)(काष्ठा amdgpu_device *adev);
	व्योम (*ras_fini)(काष्ठा amdgpu_device *adev);
	व्योम (*query_ras_error_count)(काष्ठा amdgpu_device *adev,
				      व्योम *ras_error_status);
	व्योम (*query_ras_error_status)(काष्ठा amdgpu_device *adev);
	व्योम (*reset_ras_error_count)(काष्ठा amdgpu_device *adev);
पूर्ण;

काष्ठा amdgpu_mmhub_funcs अणु
	u64 (*get_fb_location)(काष्ठा amdgpu_device *adev);
	व्योम (*init)(काष्ठा amdgpu_device *adev);
	पूर्णांक (*gart_enable)(काष्ठा amdgpu_device *adev);
	व्योम (*set_fault_enable_शेष)(काष्ठा amdgpu_device *adev,
			bool value);
	व्योम (*gart_disable)(काष्ठा amdgpu_device *adev);
	पूर्णांक (*set_घड़ीgating)(काष्ठा amdgpu_device *adev,
			       क्रमागत amd_घड़ीgating_state state);
	व्योम (*get_घड़ीgating)(काष्ठा amdgpu_device *adev, u32 *flags);
	व्योम (*setup_vm_pt_regs)(काष्ठा amdgpu_device *adev, uपूर्णांक32_t vmid,
				uपूर्णांक64_t page_table_base);
	व्योम (*update_घातer_gating)(काष्ठा amdgpu_device *adev,
                                bool enable);
पूर्ण;

काष्ठा amdgpu_mmhub अणु
	काष्ठा ras_common_अगर *ras_अगर;
	स्थिर काष्ठा amdgpu_mmhub_funcs *funcs;
	स्थिर काष्ठा amdgpu_mmhub_ras_funcs *ras_funcs;
पूर्ण;

पूर्णांक amdgpu_mmhub_ras_late_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_mmhub_ras_fini(काष्ठा amdgpu_device *adev);
#पूर्ण_अगर

