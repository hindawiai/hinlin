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

#अगर_अघोषित __ATOMBIOS_DP_H__
#घोषणा __ATOMBIOS_DP_H__

व्योम amdgpu_atombios_dp_aux_init(काष्ठा amdgpu_connector *amdgpu_connector);
u8 amdgpu_atombios_dp_get_sinktype(काष्ठा amdgpu_connector *amdgpu_connector);
पूर्णांक amdgpu_atombios_dp_get_dpcd(काष्ठा amdgpu_connector *amdgpu_connector);
पूर्णांक amdgpu_atombios_dp_get_panel_mode(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_connector *connector);
व्योम amdgpu_atombios_dp_set_link_config(काष्ठा drm_connector *connector,
				 स्थिर काष्ठा drm_display_mode *mode);
पूर्णांक amdgpu_atombios_dp_mode_valid_helper(काष्ठा drm_connector *connector,
				  काष्ठा drm_display_mode *mode);
bool amdgpu_atombios_dp_needs_link_train(काष्ठा amdgpu_connector *amdgpu_connector);
व्योम amdgpu_atombios_dp_set_rx_घातer_state(काष्ठा drm_connector *connector,
				    u8 घातer_state);
व्योम amdgpu_atombios_dp_link_train(काष्ठा drm_encoder *encoder,
			    काष्ठा drm_connector *connector);

#पूर्ण_अगर
