<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NOUVEAU_DISPLAY_H__
#घोषणा __NOUVEAU_DISPLAY_H__

#समावेश "nouveau_drv.h"

#समावेश <nvअगर/disp.h>

#समावेश <drm/drm_framebuffer.h>

पूर्णांक
nouveau_framebuffer_new(काष्ठा drm_device *dev,
			स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			काष्ठा drm_gem_object *gem,
			काष्ठा drm_framebuffer **pfb);

काष्ठा nouveau_display अणु
	व्योम *priv;
	व्योम (*dtor)(काष्ठा drm_device *);
	पूर्णांक  (*init)(काष्ठा drm_device *, bool resume, bool runसमय);
	व्योम (*fini)(काष्ठा drm_device *, bool suspend, bool runसमय);

	काष्ठा nvअगर_disp disp;

	काष्ठा drm_property *dithering_mode;
	काष्ठा drm_property *dithering_depth;
	काष्ठा drm_property *underscan_property;
	काष्ठा drm_property *underscan_hborder_property;
	काष्ठा drm_property *underscan_vborder_property;
	/* not really hue and saturation: */
	काष्ठा drm_property *vibrant_hue_property;
	काष्ठा drm_property *color_vibrance_property;

	काष्ठा drm_atomic_state *suspend;

	स्थिर u64 *क्रमmat_modअगरiers;
पूर्ण;

अटल अंतरभूत काष्ठा nouveau_display *
nouveau_display(काष्ठा drm_device *dev)
अणु
	वापस nouveau_drm(dev)->display;
पूर्ण

पूर्णांक  nouveau_display_create(काष्ठा drm_device *dev);
व्योम nouveau_display_destroy(काष्ठा drm_device *dev);
पूर्णांक  nouveau_display_init(काष्ठा drm_device *dev, bool resume, bool runसमय);
व्योम nouveau_display_hpd_resume(काष्ठा drm_device *dev);
व्योम nouveau_display_fini(काष्ठा drm_device *dev, bool suspend, bool runसमय);
पूर्णांक  nouveau_display_suspend(काष्ठा drm_device *dev, bool runसमय);
व्योम nouveau_display_resume(काष्ठा drm_device *dev, bool runसमय);
पूर्णांक  nouveau_display_vblank_enable(काष्ठा drm_crtc *crtc);
व्योम nouveau_display_vblank_disable(काष्ठा drm_crtc *crtc);
bool nouveau_display_scanoutpos(काष्ठा drm_crtc *crtc,
				bool in_vblank_irq, पूर्णांक *vpos, पूर्णांक *hpos,
				kसमय_प्रकार *sसमय, kसमय_प्रकार *eसमय,
				स्थिर काष्ठा drm_display_mode *mode);

पूर्णांक  nouveau_display_dumb_create(काष्ठा drm_file *, काष्ठा drm_device *,
				 काष्ठा drm_mode_create_dumb *args);
पूर्णांक  nouveau_display_dumb_map_offset(काष्ठा drm_file *, काष्ठा drm_device *,
				     u32 handle, u64 *offset);

व्योम nouveau_hdmi_mode_set(काष्ठा drm_encoder *, काष्ठा drm_display_mode *);

व्योम
nouveau_framebuffer_get_layout(काष्ठा drm_framebuffer *fb, uपूर्णांक32_t *tile_mode,
			       uपूर्णांक8_t *kind);

काष्ठा drm_framebuffer *
nouveau_user_framebuffer_create(काष्ठा drm_device *, काष्ठा drm_file *,
				स्थिर काष्ठा drm_mode_fb_cmd2 *);
#पूर्ण_अगर
