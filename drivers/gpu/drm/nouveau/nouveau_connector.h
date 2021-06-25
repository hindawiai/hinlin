<शैली गुरु>
/*
 * Copyright (C) 2008 Maarten Maathuis.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __NOUVEAU_CONNECTOR_H__
#घोषणा __NOUVEAU_CONNECTOR_H__

#समावेश <nvअगर/notअगरy.h>

#समावेश <nvhw/class/cl507d.h>
#समावेश <nvhw/class/cl907d.h>
#समावेश <nvhw/drf.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_util.h>

#समावेश "nouveau_crtc.h"
#समावेश "nouveau_encoder.h"

काष्ठा nvkm_i2c_port;
काष्ठा dcb_output;

#अगर_घोषित CONFIG_DRM_NOUVEAU_BACKLIGHT
काष्ठा nouveau_backlight;
#पूर्ण_अगर

#घोषणा nouveau_conn_atom(p)                                                   \
	container_of((p), काष्ठा nouveau_conn_atom, state)

काष्ठा nouveau_conn_atom अणु
	काष्ठा drm_connector_state state;

	काष्ठा अणु
		/* The क्रमागत values specअगरically defined here match nv50/gf119
		 * hw values, and the code relies on this.
		 */
		क्रमागत अणु
			DITHERING_MODE_OFF =
				NVDEF(NV507D, HEAD_SET_DITHER_CONTROL, ENABLE, DISABLE),
			DITHERING_MODE_ON =
				NVDEF(NV507D, HEAD_SET_DITHER_CONTROL, ENABLE, ENABLE),
			DITHERING_MODE_DYNAMIC2X2 = DITHERING_MODE_ON |
				NVDEF(NV507D, HEAD_SET_DITHER_CONTROL, MODE, DYNAMIC_2X2),
			DITHERING_MODE_STATIC2X2 = DITHERING_MODE_ON |
				NVDEF(NV507D, HEAD_SET_DITHER_CONTROL, MODE, STATIC_2X2),
			DITHERING_MODE_TEMPORAL = DITHERING_MODE_ON |
				NVDEF(NV907D, HEAD_SET_DITHER_CONTROL, MODE, TEMPORAL),
			DITHERING_MODE_AUTO
		पूर्ण mode;
		क्रमागत अणु
			DITHERING_DEPTH_6BPC =
				NVDEF(NV507D, HEAD_SET_DITHER_CONTROL, BITS, DITHER_TO_6_BITS),
			DITHERING_DEPTH_8BPC =
				NVDEF(NV507D, HEAD_SET_DITHER_CONTROL, BITS, DITHER_TO_8_BITS),
			DITHERING_DEPTH_AUTO
		पूर्ण depth;
	पूर्ण dither;

	काष्ठा अणु
		पूर्णांक mode;	/* DRM_MODE_SCALE_* */
		काष्ठा अणु
			क्रमागत अणु
				UNDERSCAN_OFF,
				UNDERSCAN_ON,
				UNDERSCAN_AUTO,
			पूर्ण mode;
			u32 hborder;
			u32 vborder;
		पूर्ण underscan;
		bool full;
	पूर्ण scaler;

	काष्ठा अणु
		पूर्णांक color_vibrance;
		पूर्णांक vibrant_hue;
	पूर्ण procamp;

	जोड़ अणु
		काष्ठा अणु
			bool dither:1;
			bool scaler:1;
			bool procamp:1;
		पूर्ण;
		u8 mask;
	पूर्ण set;
पूर्ण;

काष्ठा nouveau_connector अणु
	काष्ठा drm_connector base;
	क्रमागत dcb_connector_type type;
	u8 index;
	u8 *dcb;

	काष्ठा nvअगर_notअगरy hpd;

	काष्ठा drm_dp_aux aux;

	पूर्णांक dithering_mode;
	पूर्णांक scaling_mode;

	काष्ठा nouveau_encoder *detected_encoder;
	काष्ठा edid *edid;
	काष्ठा drm_display_mode *native_mode;
#अगर_घोषित CONFIG_DRM_NOUVEAU_BACKLIGHT
	काष्ठा nouveau_backlight *backlight;
#पूर्ण_अगर
	/*
	 * Our connector property code expects a nouveau_conn_atom काष्ठा
	 * even on pre-nv50 where we करो not support atomic. This embedded
	 * version माला_लो used in the non atomic modeset हाल.
	 */
	काष्ठा nouveau_conn_atom properties_state;
पूर्ण;

अटल अंतरभूत काष्ठा nouveau_connector *nouveau_connector(
						काष्ठा drm_connector *con)
अणु
	वापस container_of(con, काष्ठा nouveau_connector, base);
पूर्ण

अटल अंतरभूत bool
nouveau_connector_is_mst(काष्ठा drm_connector *connector)
अणु
	स्थिर काष्ठा nouveau_encoder *nv_encoder;
	स्थिर काष्ठा drm_encoder *encoder;

	अगर (connector->connector_type != DRM_MODE_CONNECTOR_DisplayPort)
		वापस false;

	nv_encoder = find_encoder(connector, DCB_OUTPUT_ANY);
	अगर (!nv_encoder)
		वापस false;

	encoder = &nv_encoder->base.base;
	वापस encoder->encoder_type == DRM_MODE_ENCODER_DPMST;
पूर्ण

#घोषणा nouveau_क्रम_each_non_mst_connector_iter(connector, iter) \
	drm_क्रम_each_connector_iter(connector, iter) \
		क्रम_each_अगर(!nouveau_connector_is_mst(connector))

अटल अंतरभूत काष्ठा nouveau_connector *
nouveau_crtc_connector_get(काष्ठा nouveau_crtc *nv_crtc)
अणु
	काष्ठा drm_device *dev = nv_crtc->base.dev;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा nouveau_connector *nv_connector = शून्य;
	काष्ठा drm_crtc *crtc = to_drm_crtc(nv_crtc);

	drm_connector_list_iter_begin(dev, &conn_iter);
	nouveau_क्रम_each_non_mst_connector_iter(connector, &conn_iter) अणु
		अगर (connector->encoder && connector->encoder->crtc == crtc) अणु
			nv_connector = nouveau_connector(connector);
			अवरोध;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	वापस nv_connector;
पूर्ण

काष्ठा drm_connector *
nouveau_connector_create(काष्ठा drm_device *, स्थिर काष्ठा dcb_output *);
व्योम nouveau_connector_hpd(काष्ठा drm_connector *connector);

बाह्य पूर्णांक nouveau_tv_disable;
बाह्य पूर्णांक nouveau_ignorelid;
बाह्य पूर्णांक nouveau_duallink;
बाह्य पूर्णांक nouveau_hdmimhz;

व्योम nouveau_conn_attach_properties(काष्ठा drm_connector *);
व्योम nouveau_conn_reset(काष्ठा drm_connector *);
काष्ठा drm_connector_state *
nouveau_conn_atomic_duplicate_state(काष्ठा drm_connector *);
व्योम nouveau_conn_atomic_destroy_state(काष्ठा drm_connector *,
				       काष्ठा drm_connector_state *);
पूर्णांक nouveau_conn_atomic_set_property(काष्ठा drm_connector *,
				     काष्ठा drm_connector_state *,
				     काष्ठा drm_property *, u64);
पूर्णांक nouveau_conn_atomic_get_property(काष्ठा drm_connector *,
				     स्थिर काष्ठा drm_connector_state *,
				     काष्ठा drm_property *, u64 *);
काष्ठा drm_display_mode *nouveau_conn_native_mode(काष्ठा drm_connector *);
क्रमागत drm_mode_status
nouveau_conn_mode_घड़ी_valid(स्थिर काष्ठा drm_display_mode *,
			      स्थिर अचिन्हित min_घड़ी,
			      स्थिर अचिन्हित max_घड़ी,
			      अचिन्हित *घड़ी);

#अगर_घोषित CONFIG_DRM_NOUVEAU_BACKLIGHT
बाह्य पूर्णांक nouveau_backlight_init(काष्ठा drm_connector *);
बाह्य व्योम nouveau_backlight_fini(काष्ठा drm_connector *);
बाह्य व्योम nouveau_backlight_ctor(व्योम);
बाह्य व्योम nouveau_backlight_dtor(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक
nouveau_backlight_init(काष्ठा drm_connector *connector)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
nouveau_backlight_fini(काष्ठा drm_connector *connector) अणु
पूर्ण

अटल अंतरभूत व्योम
nouveau_backlight_ctor(व्योम) अणु
पूर्ण

अटल अंतरभूत व्योम
nouveau_backlight_dtor(व्योम) अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __NOUVEAU_CONNECTOR_H__ */
