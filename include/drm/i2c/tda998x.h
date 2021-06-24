<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __DRM_I2C_TDA998X_H__
#घोषणा __DRM_I2C_TDA998X_H__

#समावेश <linux/hdmi.h>
#समावेश <dt-bindings/display/tda998x.h>

क्रमागत अणु
	AFMT_UNUSED =	0,
	AFMT_SPDIF =	TDA998x_SPDIF,
	AFMT_I2S =	TDA998x_I2S,
पूर्ण;

काष्ठा tda998x_audio_params अणु
	u8 config;
	u8 क्रमmat;
	अचिन्हित sample_width;
	अचिन्हित sample_rate;
	काष्ठा hdmi_audio_infoframe cea;
	u8 status[5];
पूर्ण;

काष्ठा tda998x_encoder_params अणु
	u8 swap_b:3;
	u8 mirr_b:1;
	u8 swap_a:3;
	u8 mirr_a:1;
	u8 swap_d:3;
	u8 mirr_d:1;
	u8 swap_c:3;
	u8 mirr_c:1;
	u8 swap_f:3;
	u8 mirr_f:1;
	u8 swap_e:3;
	u8 mirr_e:1;

	काष्ठा tda998x_audio_params audio_params;
पूर्ण;

#पूर्ण_अगर
