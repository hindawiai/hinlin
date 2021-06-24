<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2016 Linaro Ltd.
 * Copyright 2016 ZTE Corporation.
 */

#अगर_अघोषित __ZX_VOU_H__
#घोषणा __ZX_VOU_H__

#घोषणा VOU_CRTC_MASK		0x3

/* VOU output पूर्णांकerfaces */
क्रमागत vou_inf_id अणु
	VOU_HDMI	= 0,
	VOU_RGB_LCD	= 1,
	VOU_TV_ENC	= 2,
	VOU_MIPI_DSI	= 3,
	VOU_LVDS	= 4,
	VOU_VGA		= 5,
पूर्ण;

क्रमागत vou_inf_hdmi_audio अणु
	VOU_HDMI_AUD_SPDIF	= BIT(0),
	VOU_HDMI_AUD_I2S	= BIT(1),
	VOU_HDMI_AUD_DSD	= BIT(2),
	VOU_HDMI_AUD_HBR	= BIT(3),
	VOU_HDMI_AUD_PARALLEL	= BIT(4),
पूर्ण;

व्योम vou_inf_hdmi_audio_sel(काष्ठा drm_crtc *crtc,
			    क्रमागत vou_inf_hdmi_audio aud);
व्योम vou_inf_enable(क्रमागत vou_inf_id id, काष्ठा drm_crtc *crtc);
व्योम vou_inf_disable(क्रमागत vou_inf_id id, काष्ठा drm_crtc *crtc);

क्रमागत vou_भाग_id अणु
	VOU_DIV_VGA,
	VOU_DIV_PIC,
	VOU_DIV_TVENC,
	VOU_DIV_HDMI_PNX,
	VOU_DIV_HDMI,
	VOU_DIV_INF,
	VOU_DIV_LAYER,
पूर्ण;

क्रमागत vou_भाग_val अणु
	VOU_DIV_1 = 0,
	VOU_DIV_2 = 1,
	VOU_DIV_4 = 3,
	VOU_DIV_8 = 7,
पूर्ण;

काष्ठा vou_भाग_config अणु
	क्रमागत vou_भाग_id id;
	क्रमागत vou_भाग_val val;
पूर्ण;

व्योम zx_vou_config_भागiders(काष्ठा drm_crtc *crtc,
			    काष्ठा vou_भाग_config *configs, पूर्णांक num);

व्योम zx_vou_layer_enable(काष्ठा drm_plane *plane);
व्योम zx_vou_layer_disable(काष्ठा drm_plane *plane,
			  काष्ठा drm_plane_state *old_state);

#पूर्ण_अगर /* __ZX_VOU_H__ */
