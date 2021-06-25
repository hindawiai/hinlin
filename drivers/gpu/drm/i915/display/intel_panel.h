<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_PANEL_H__
#घोषणा __INTEL_PANEL_H__

#समावेश <linux/types.h>

#समावेश "intel_display.h"

काष्ठा drm_connector;
काष्ठा drm_connector_state;
काष्ठा drm_display_mode;
काष्ठा पूर्णांकel_connector;
काष्ठा पूर्णांकel_crtc;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_encoder;
काष्ठा पूर्णांकel_panel;

पूर्णांक पूर्णांकel_panel_init(काष्ठा पूर्णांकel_panel *panel,
		     काष्ठा drm_display_mode *fixed_mode,
		     काष्ठा drm_display_mode *करोwnघड़ी_mode);
व्योम पूर्णांकel_panel_fini(काष्ठा पूर्णांकel_panel *panel);
क्रमागत drm_connector_status
पूर्णांकel_panel_detect(काष्ठा drm_connector *connector, bool क्रमce);
व्योम पूर्णांकel_fixed_panel_mode(स्थिर काष्ठा drm_display_mode *fixed_mode,
			    काष्ठा drm_display_mode *adjusted_mode);
पूर्णांक पूर्णांकel_pch_panel_fitting(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    स्थिर काष्ठा drm_connector_state *conn_state);
पूर्णांक पूर्णांकel_gmch_panel_fitting(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     स्थिर काष्ठा drm_connector_state *conn_state);
व्योम पूर्णांकel_panel_set_backlight_acpi(स्थिर काष्ठा drm_connector_state *conn_state,
				    u32 level, u32 max);
पूर्णांक पूर्णांकel_panel_setup_backlight(काष्ठा drm_connector *connector,
				क्रमागत pipe pipe);
व्योम पूर्णांकel_panel_enable_backlight(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  स्थिर काष्ठा drm_connector_state *conn_state);
व्योम पूर्णांकel_panel_update_backlight(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  स्थिर काष्ठा drm_connector_state *conn_state);
व्योम पूर्णांकel_panel_disable_backlight(स्थिर काष्ठा drm_connector_state *old_conn_state);
काष्ठा drm_display_mode *
पूर्णांकel_panel_edid_करोwnघड़ी_mode(काष्ठा पूर्णांकel_connector *connector,
				स्थिर काष्ठा drm_display_mode *fixed_mode);
काष्ठा drm_display_mode *
पूर्णांकel_panel_edid_fixed_mode(काष्ठा पूर्णांकel_connector *connector);
काष्ठा drm_display_mode *
पूर्णांकel_panel_vbt_fixed_mode(काष्ठा पूर्णांकel_connector *connector);
व्योम पूर्णांकel_panel_set_pwm_level(स्थिर काष्ठा drm_connector_state *conn_state, u32 level);
u32 पूर्णांकel_panel_invert_pwm_level(काष्ठा पूर्णांकel_connector *connector, u32 level);
u32 पूर्णांकel_panel_backlight_level_to_pwm(काष्ठा पूर्णांकel_connector *connector, u32 level);
u32 पूर्णांकel_panel_backlight_level_from_pwm(काष्ठा पूर्णांकel_connector *connector, u32 val);

#अगर IS_ENABLED(CONFIG_BACKLIGHT_CLASS_DEVICE)
पूर्णांक पूर्णांकel_backlight_device_रेजिस्टर(काष्ठा पूर्णांकel_connector *connector);
व्योम पूर्णांकel_backlight_device_unरेजिस्टर(काष्ठा पूर्णांकel_connector *connector);
#अन्यथा /* CONFIG_BACKLIGHT_CLASS_DEVICE */
अटल अंतरभूत पूर्णांक पूर्णांकel_backlight_device_रेजिस्टर(काष्ठा पूर्णांकel_connector *connector)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम पूर्णांकel_backlight_device_unरेजिस्टर(काष्ठा पूर्णांकel_connector *connector)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_BACKLIGHT_CLASS_DEVICE */

#पूर्ण_अगर /* __INTEL_PANEL_H__ */
