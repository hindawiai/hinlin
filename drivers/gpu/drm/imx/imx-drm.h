<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _IMX_DRM_H_
#घोषणा _IMX_DRM_H_

काष्ठा device_node;
काष्ठा drm_crtc;
काष्ठा drm_connector;
काष्ठा drm_device;
काष्ठा drm_display_mode;
काष्ठा drm_encoder;
काष्ठा drm_framebuffer;
काष्ठा drm_plane;
काष्ठा platक्रमm_device;

काष्ठा imx_crtc_state अणु
	काष्ठा drm_crtc_state			base;
	u32					bus_क्रमmat;
	u32					bus_flags;
	पूर्णांक					di_hsync_pin;
	पूर्णांक					di_vsync_pin;
पूर्ण;

अटल अंतरभूत काष्ठा imx_crtc_state *to_imx_crtc_state(काष्ठा drm_crtc_state *s)
अणु
	वापस container_of(s, काष्ठा imx_crtc_state, base);
पूर्ण
पूर्णांक imx_drm_init_drm(काष्ठा platक्रमm_device *pdev,
		पूर्णांक preferred_bpp);
पूर्णांक imx_drm_निकास_drm(व्योम);

बाह्य काष्ठा platक्रमm_driver ipu_drm_driver;

व्योम imx_drm_mode_config_init(काष्ठा drm_device *drm);

काष्ठा drm_gem_cma_object *imx_drm_fb_get_obj(काष्ठा drm_framebuffer *fb);

पूर्णांक imx_drm_encoder_parse_of(काष्ठा drm_device *drm,
	काष्ठा drm_encoder *encoder, काष्ठा device_node *np);

व्योम imx_drm_connector_destroy(काष्ठा drm_connector *connector);

पूर्णांक ipu_planes_assign_pre(काष्ठा drm_device *dev,
			  काष्ठा drm_atomic_state *state);

#पूर्ण_अगर /* _IMX_DRM_H_ */
