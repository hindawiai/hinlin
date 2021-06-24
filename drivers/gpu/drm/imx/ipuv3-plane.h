<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __IPUV3_PLANE_H__
#घोषणा __IPUV3_PLANE_H__

#समावेश <drm/drm_crtc.h> /* drm_plane */

काष्ठा drm_plane;
काष्ठा drm_device;
काष्ठा ipu_soc;
काष्ठा drm_crtc;
काष्ठा drm_framebuffer;

काष्ठा ipuv3_channel;
काष्ठा dmfc_channel;
काष्ठा ipu_dp;

काष्ठा ipu_plane अणु
	काष्ठा drm_plane	base;

	काष्ठा ipu_soc		*ipu;
	काष्ठा ipuv3_channel	*ipu_ch;
	काष्ठा ipuv3_channel	*alpha_ch;
	काष्ठा dmfc_channel	*dmfc;
	काष्ठा ipu_dp		*dp;

	पूर्णांक			dma;
	पूर्णांक			dp_flow;

	bool			disabling;
पूर्ण;

काष्ठा ipu_plane *ipu_plane_init(काष्ठा drm_device *dev, काष्ठा ipu_soc *ipu,
				 पूर्णांक dma, पूर्णांक dp, अचिन्हित पूर्णांक possible_crtcs,
				 क्रमागत drm_plane_type type);

/* Init IDMAC, DMFC, DP */
पूर्णांक ipu_plane_mode_set(काष्ठा ipu_plane *plane, काष्ठा drm_crtc *crtc,
		       काष्ठा drm_display_mode *mode,
		       काष्ठा drm_framebuffer *fb, पूर्णांक crtc_x, पूर्णांक crtc_y,
		       अचिन्हित पूर्णांक crtc_w, अचिन्हित पूर्णांक crtc_h,
		       uपूर्णांक32_t src_x, uपूर्णांक32_t src_y, uपूर्णांक32_t src_w,
		       uपूर्णांक32_t src_h, bool पूर्णांकerlaced);

पूर्णांक ipu_plane_irq(काष्ठा ipu_plane *plane);

व्योम ipu_plane_disable(काष्ठा ipu_plane *ipu_plane, bool disable_dp_channel);
व्योम ipu_plane_disable_deferred(काष्ठा drm_plane *plane);
bool ipu_plane_atomic_update_pending(काष्ठा drm_plane *plane);

#पूर्ण_अगर
