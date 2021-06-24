<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

/*
 * Video Encoders
 * - ENCI : Interlace Video Encoder
 * - ENCI_DVI : Interlace Video Encoder क्रम DVI/HDMI
 * - ENCP : Progressive Video Encoder
 */

#अगर_अघोषित __MESON_VENC_H
#घोषणा __MESON_VENC_H

काष्ठा drm_display_mode;

क्रमागत अणु
	MESON_VENC_MODE_NONE = 0,
	MESON_VENC_MODE_CVBS_PAL,
	MESON_VENC_MODE_CVBS_NTSC,
	MESON_VENC_MODE_HDMI,
पूर्ण;

काष्ठा meson_cvbs_enci_mode अणु
	अचिन्हित पूर्णांक mode_tag;
	अचिन्हित पूर्णांक hso_begin; /* HSO begin position */
	अचिन्हित पूर्णांक hso_end; /* HSO end position */
	अचिन्हित पूर्णांक vso_even; /* VSO even line */
	अचिन्हित पूर्णांक vso_odd; /* VSO odd line */
	अचिन्हित पूर्णांक macv_max_amp; /* Macrovision max amplitude */
	अचिन्हित पूर्णांक video_prog_mode;
	अचिन्हित पूर्णांक video_mode;
	अचिन्हित पूर्णांक sch_adjust;
	अचिन्हित पूर्णांक yc_delay;
	अचिन्हित पूर्णांक pixel_start;
	अचिन्हित पूर्णांक pixel_end;
	अचिन्हित पूर्णांक top_field_line_start;
	अचिन्हित पूर्णांक top_field_line_end;
	अचिन्हित पूर्णांक bottom_field_line_start;
	अचिन्हित पूर्णांक bottom_field_line_end;
	अचिन्हित पूर्णांक video_saturation;
	अचिन्हित पूर्णांक video_contrast;
	अचिन्हित पूर्णांक video_brightness;
	अचिन्हित पूर्णांक video_hue;
	अचिन्हित पूर्णांक analog_sync_adj;
पूर्ण;

/* HDMI Clock parameters */
क्रमागत drm_mode_status
meson_venc_hdmi_supported_mode(स्थिर काष्ठा drm_display_mode *mode);
bool meson_venc_hdmi_supported_vic(पूर्णांक vic);
bool meson_venc_hdmi_venc_repeat(पूर्णांक vic);

/* CVBS Timings and Parameters */
बाह्य काष्ठा meson_cvbs_enci_mode meson_cvbs_enci_pal;
बाह्य काष्ठा meson_cvbs_enci_mode meson_cvbs_enci_ntsc;

व्योम meson_venci_cvbs_mode_set(काष्ठा meson_drm *priv,
			       काष्ठा meson_cvbs_enci_mode *mode);
व्योम meson_venc_hdmi_mode_set(काष्ठा meson_drm *priv, पूर्णांक vic,
			      अचिन्हित पूर्णांक ycrcb_map,
			      bool yuv420_mode,
			      स्थिर काष्ठा drm_display_mode *mode);
अचिन्हित पूर्णांक meson_venci_get_field(काष्ठा meson_drm *priv);

व्योम meson_venc_enable_vsync(काष्ठा meson_drm *priv);
व्योम meson_venc_disable_vsync(काष्ठा meson_drm *priv);

व्योम meson_venc_init(काष्ठा meson_drm *priv);

#पूर्ण_अगर /* __MESON_VENC_H */
