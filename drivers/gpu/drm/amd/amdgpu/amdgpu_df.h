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

#अगर_अघोषित __AMDGPU_DF_H__
#घोषणा __AMDGPU_DF_H__

काष्ठा amdgpu_df_hash_status अणु
	bool hash_64k;
	bool hash_2m;
	bool hash_1g;
पूर्ण;

काष्ठा amdgpu_df_funcs अणु
	व्योम (*sw_init)(काष्ठा amdgpu_device *adev);
	व्योम (*sw_fini)(काष्ठा amdgpu_device *adev);
	व्योम (*enable_broadcast_mode)(काष्ठा amdgpu_device *adev,
				      bool enable);
	u32 (*get_fb_channel_number)(काष्ठा amdgpu_device *adev);
	u32 (*get_hbm_channel_number)(काष्ठा amdgpu_device *adev);
	व्योम (*update_medium_grain_घड़ी_gating)(काष्ठा amdgpu_device *adev,
						 bool enable);
	व्योम (*get_घड़ीgating_state)(काष्ठा amdgpu_device *adev,
				      u32 *flags);
	व्योम (*enable_ecc_क्रमce_par_wr_rmw)(काष्ठा amdgpu_device *adev,
					    bool enable);
	पूर्णांक (*pmc_start)(काष्ठा amdgpu_device *adev, uपूर्णांक64_t config,
					 पूर्णांक counter_idx, पूर्णांक is_add);
	पूर्णांक (*pmc_stop)(काष्ठा amdgpu_device *adev, uपूर्णांक64_t config,
					 पूर्णांक counter_idx, पूर्णांक is_हटाओ);
	व्योम (*pmc_get_count)(काष्ठा amdgpu_device *adev, uपूर्णांक64_t config,
					 पूर्णांक counter_idx, uपूर्णांक64_t *count);
	uपूर्णांक64_t (*get_fica)(काष्ठा amdgpu_device *adev, uपूर्णांक32_t ficaa_val);
	व्योम (*set_fica)(काष्ठा amdgpu_device *adev, uपूर्णांक32_t ficaa_val,
			 uपूर्णांक32_t ficadl_val, uपूर्णांक32_t ficadh_val);
पूर्ण;

काष्ठा amdgpu_df अणु
	काष्ठा amdgpu_df_hash_status	hash_status;
	स्थिर काष्ठा amdgpu_df_funcs	*funcs;
पूर्ण;

#पूर्ण_अगर /* __AMDGPU_DF_H__ */
