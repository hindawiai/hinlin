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

#अगर_अघोषित __ATOMBIOS_ENCODER_H__
#घोषणा __ATOMBIOS_ENCODER_H__

u8
amdgpu_atombios_encoder_get_backlight_level_from_reg(काष्ठा amdgpu_device *adev);
व्योम
amdgpu_atombios_encoder_set_backlight_level_to_reg(काष्ठा amdgpu_device *adev,
						   u8 backlight_level);
u8
amdgpu_atombios_encoder_get_backlight_level(काष्ठा amdgpu_encoder *amdgpu_encoder);
व्योम
amdgpu_atombios_encoder_set_backlight_level(काष्ठा amdgpu_encoder *amdgpu_encoder,
				     u8 level);
व्योम amdgpu_atombios_encoder_init_backlight(काष्ठा amdgpu_encoder *amdgpu_encoder,
				     काष्ठा drm_connector *drm_connector);
व्योम
amdgpu_atombios_encoder_fini_backlight(काष्ठा amdgpu_encoder *amdgpu_encoder);
bool amdgpu_atombios_encoder_is_digital(काष्ठा drm_encoder *encoder);
bool amdgpu_atombios_encoder_mode_fixup(काष्ठा drm_encoder *encoder,
				 स्थिर काष्ठा drm_display_mode *mode,
				 काष्ठा drm_display_mode *adjusted_mode);
पूर्णांक amdgpu_atombios_encoder_get_encoder_mode(काष्ठा drm_encoder *encoder);
व्योम
amdgpu_atombios_encoder_setup_dig_encoder(काष्ठा drm_encoder *encoder,
				   पूर्णांक action, पूर्णांक panel_mode);
व्योम
amdgpu_atombios_encoder_setup_dig_transmitter(काष्ठा drm_encoder *encoder, पूर्णांक action,
				       uपूर्णांक8_t lane_num, uपूर्णांक8_t lane_set);
bool
amdgpu_atombios_encoder_set_edp_panel_घातer(काष्ठा drm_connector *connector,
				     पूर्णांक action);
व्योम
amdgpu_atombios_encoder_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode);
व्योम
amdgpu_atombios_encoder_set_crtc_source(काष्ठा drm_encoder *encoder);
व्योम
amdgpu_atombios_encoder_init_dig(काष्ठा amdgpu_device *adev);
क्रमागत drm_connector_status
amdgpu_atombios_encoder_dac_detect(काष्ठा drm_encoder *encoder,
			    काष्ठा drm_connector *connector);
क्रमागत drm_connector_status
amdgpu_atombios_encoder_dig_detect(काष्ठा drm_encoder *encoder,
			    काष्ठा drm_connector *connector);
व्योम
amdgpu_atombios_encoder_setup_ext_encoder_ddc(काष्ठा drm_encoder *encoder);
व्योम
amdgpu_atombios_encoder_set_bios_scratch_regs(काष्ठा drm_connector *connector,
				       काष्ठा drm_encoder *encoder,
				       bool connected);
काष्ठा amdgpu_encoder_atom_dig *
amdgpu_atombios_encoder_get_lcd_info(काष्ठा amdgpu_encoder *encoder);
काष्ठा amdgpu_encoder_atom_dig *
amdgpu_atombios_encoder_get_dig_info(काष्ठा amdgpu_encoder *amdgpu_encoder);

#पूर्ण_अगर
