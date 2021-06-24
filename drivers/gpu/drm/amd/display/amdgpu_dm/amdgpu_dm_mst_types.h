<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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
 * Authors: AMD
 *
 */

#अगर_अघोषित __DAL_AMDGPU_DM_MST_TYPES_H__
#घोषणा __DAL_AMDGPU_DM_MST_TYPES_H__

काष्ठा amdgpu_display_manager;
काष्ठा amdgpu_dm_connector;

पूर्णांक dm_mst_get_pbn_भागider(काष्ठा dc_link *link);

व्योम amdgpu_dm_initialize_dp_connector(काष्ठा amdgpu_display_manager *dm,
				       काष्ठा amdgpu_dm_connector *aconnector,
				       पूर्णांक link_index);

व्योम
dm_dp_create_fake_mst_encoders(काष्ठा amdgpu_device *adev);

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
bool compute_mst_dsc_configs_क्रम_state(काष्ठा drm_atomic_state *state,
				       काष्ठा dc_state *dc_state);
#पूर्ण_अगर

#पूर्ण_अगर
