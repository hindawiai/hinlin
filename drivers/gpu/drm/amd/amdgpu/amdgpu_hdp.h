<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __AMDGPU_HDP_H__
#घोषणा __AMDGPU_HDP_H__

काष्ठा amdgpu_hdp_funcs अणु
	व्योम (*flush_hdp)(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ring *ring);
	व्योम (*invalidate_hdp)(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_ring *ring);
	व्योम (*reset_ras_error_count)(काष्ठा amdgpu_device *adev);
	व्योम (*update_घड़ी_gating)(काष्ठा amdgpu_device *adev, bool enable);
	व्योम (*get_घड़ी_gating_state)(काष्ठा amdgpu_device *adev, u32 *flags);
	व्योम (*init_रेजिस्टरs)(काष्ठा amdgpu_device *adev);
पूर्ण;

काष्ठा amdgpu_hdp अणु
	स्थिर काष्ठा amdgpu_hdp_funcs		*funcs;
पूर्ण;

#पूर्ण_अगर /* __AMDGPU_HDP_H__ */
