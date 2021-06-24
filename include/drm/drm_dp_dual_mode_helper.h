<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
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
 */

#अगर_अघोषित DRM_DP_DUAL_MODE_HELPER_H
#घोषणा DRM_DP_DUAL_MODE_HELPER_H

#समावेश <linux/types.h>

/*
 * Optional क्रम type 1 DVI adaptors
 * Mandatory क्रम type 1 HDMI and type 2 adaptors
 */
#घोषणा DP_DUAL_MODE_HDMI_ID 0x00 /* 00-0f */
#घोषणा  DP_DUAL_MODE_HDMI_ID_LEN 16
/*
 * Optional क्रम type 1 adaptors
 * Mandatory क्रम type 2 adaptors
 */
#घोषणा DP_DUAL_MODE_ADAPTOR_ID 0x10
#घोषणा  DP_DUAL_MODE_REV_MASK 0x07
#घोषणा  DP_DUAL_MODE_REV_TYPE2 0x00
#घोषणा  DP_DUAL_MODE_TYPE_MASK 0xf0
#घोषणा  DP_DUAL_MODE_TYPE_TYPE2 0xa0
/* This field is marked reserved in dual mode spec, used in LSPCON */
#घोषणा  DP_DUAL_MODE_TYPE_HAS_DPCD 0x08
#घोषणा DP_DUAL_MODE_IEEE_OUI 0x11 /* 11-13*/
#घोषणा  DP_DUAL_IEEE_OUI_LEN 3
#घोषणा DP_DUAL_DEVICE_ID 0x14 /* 14-19 */
#घोषणा  DP_DUAL_DEVICE_ID_LEN 6
#घोषणा DP_DUAL_MODE_HARDWARE_REV 0x1a
#घोषणा DP_DUAL_MODE_FIRMWARE_MAJOR_REV 0x1b
#घोषणा DP_DUAL_MODE_FIRMWARE_MINOR_REV 0x1c
#घोषणा DP_DUAL_MODE_MAX_TMDS_CLOCK 0x1d
#घोषणा DP_DUAL_MODE_I2C_SPEED_CAP 0x1e
#घोषणा DP_DUAL_MODE_TMDS_OEN 0x20
#घोषणा  DP_DUAL_MODE_TMDS_DISABLE 0x01
#घोषणा DP_DUAL_MODE_HDMI_PIN_CTRL 0x21
#घोषणा  DP_DUAL_MODE_CEC_ENABLE 0x01
#घोषणा DP_DUAL_MODE_I2C_SPEED_CTRL 0x22

/* LSPCON specअगरic रेजिस्टरs, defined by MCA */
#घोषणा DP_DUAL_MODE_LSPCON_MODE_CHANGE		0x40
#घोषणा DP_DUAL_MODE_LSPCON_CURRENT_MODE		0x41
#घोषणा  DP_DUAL_MODE_LSPCON_MODE_PCON			0x1

काष्ठा i2c_adapter;

sमाप_प्रकार drm_dp_dual_mode_पढ़ो(काष्ठा i2c_adapter *adapter,
			      u8 offset, व्योम *buffer, माप_प्रकार size);
sमाप_प्रकार drm_dp_dual_mode_ग_लिखो(काष्ठा i2c_adapter *adapter,
			       u8 offset, स्थिर व्योम *buffer, माप_प्रकार size);

/**
 * क्रमागत drm_lspcon_mode
 * @DRM_LSPCON_MODE_INVALID: No LSPCON.
 * @DRM_LSPCON_MODE_LS: Level shअगरter mode of LSPCON
 *	which drives DP++ to HDMI 1.4 conversion.
 * @DRM_LSPCON_MODE_PCON: Protocol converter mode of LSPCON
 *	which drives DP++ to HDMI 2.0 active conversion.
 */
क्रमागत drm_lspcon_mode अणु
	DRM_LSPCON_MODE_INVALID,
	DRM_LSPCON_MODE_LS,
	DRM_LSPCON_MODE_PCON,
पूर्ण;

/**
 * क्रमागत drm_dp_dual_mode_type - Type of the DP dual mode adaptor
 * @DRM_DP_DUAL_MODE_NONE: No DP dual mode adaptor
 * @DRM_DP_DUAL_MODE_UNKNOWN: Could be either none or type 1 DVI adaptor
 * @DRM_DP_DUAL_MODE_TYPE1_DVI: Type 1 DVI adaptor
 * @DRM_DP_DUAL_MODE_TYPE1_HDMI: Type 1 HDMI adaptor
 * @DRM_DP_DUAL_MODE_TYPE2_DVI: Type 2 DVI adaptor
 * @DRM_DP_DUAL_MODE_TYPE2_HDMI: Type 2 HDMI adaptor
 * @DRM_DP_DUAL_MODE_LSPCON: Level shअगरter / protocol converter
 */
क्रमागत drm_dp_dual_mode_type अणु
	DRM_DP_DUAL_MODE_NONE,
	DRM_DP_DUAL_MODE_UNKNOWN,
	DRM_DP_DUAL_MODE_TYPE1_DVI,
	DRM_DP_DUAL_MODE_TYPE1_HDMI,
	DRM_DP_DUAL_MODE_TYPE2_DVI,
	DRM_DP_DUAL_MODE_TYPE2_HDMI,
	DRM_DP_DUAL_MODE_LSPCON,
पूर्ण;

क्रमागत drm_dp_dual_mode_type drm_dp_dual_mode_detect(काष्ठा i2c_adapter *adapter);
पूर्णांक drm_dp_dual_mode_max_पंचांगds_घड़ी(क्रमागत drm_dp_dual_mode_type type,
				    काष्ठा i2c_adapter *adapter);
पूर्णांक drm_dp_dual_mode_get_पंचांगds_output(क्रमागत drm_dp_dual_mode_type type,
				     काष्ठा i2c_adapter *adapter, bool *enabled);
पूर्णांक drm_dp_dual_mode_set_पंचांगds_output(क्रमागत drm_dp_dual_mode_type type,
				     काष्ठा i2c_adapter *adapter, bool enable);
स्थिर अक्षर *drm_dp_get_dual_mode_type_name(क्रमागत drm_dp_dual_mode_type type);

पूर्णांक drm_lspcon_get_mode(काष्ठा i2c_adapter *adapter,
			क्रमागत drm_lspcon_mode *current_mode);
पूर्णांक drm_lspcon_set_mode(काष्ठा i2c_adapter *adapter,
			क्रमागत drm_lspcon_mode reqd_mode);
#पूर्ण_अगर
