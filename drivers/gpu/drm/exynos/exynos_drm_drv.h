<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* exynos_drm_drv.h
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 * Authors:
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *	Seung-Woo Kim <sw0312.kim@samsung.com>
 */

#अगर_अघोषित _EXYNOS_DRM_DRV_H_
#घोषणा _EXYNOS_DRM_DRV_H_

#समावेश <linux/module.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_plane.h>

#घोषणा MAX_CRTC	3
#घोषणा MAX_PLANE	5
#घोषणा MAX_FB_BUFFER	4

#घोषणा DEFAULT_WIN	0

काष्ठा drm_crtc_state;
काष्ठा drm_display_mode;

#घोषणा to_exynos_crtc(x)	container_of(x, काष्ठा exynos_drm_crtc, base)
#घोषणा to_exynos_plane(x)	container_of(x, काष्ठा exynos_drm_plane, base)

/* this क्रमागतerates display type. */
क्रमागत exynos_drm_output_type अणु
	EXYNOS_DISPLAY_TYPE_NONE,
	/* RGB or CPU Interface. */
	EXYNOS_DISPLAY_TYPE_LCD,
	/* HDMI Interface. */
	EXYNOS_DISPLAY_TYPE_HDMI,
	/* Virtual Display Interface. */
	EXYNOS_DISPLAY_TYPE_VIDI,
पूर्ण;

काष्ठा exynos_drm_rect अणु
	अचिन्हित पूर्णांक x, y;
	अचिन्हित पूर्णांक w, h;
पूर्ण;

/*
 * Exynos drm plane state काष्ठाure.
 *
 * @base: plane_state object (contains drm_framebuffer poपूर्णांकer)
 * @src: rectangle of the source image data to be displayed (clipped to
 *       visible part).
 * @crtc: rectangle of the target image position on hardware screen
 *       (clipped to visible part).
 * @h_ratio: horizontal scaling ratio, 16.16 fixed poपूर्णांक
 * @v_ratio: vertical scaling ratio, 16.16 fixed poपूर्णांक
 *
 * this काष्ठाure consists plane state data that will be applied to hardware
 * specअगरic overlay info.
 */

काष्ठा exynos_drm_plane_state अणु
	काष्ठा drm_plane_state base;
	काष्ठा exynos_drm_rect crtc;
	काष्ठा exynos_drm_rect src;
	अचिन्हित पूर्णांक h_ratio;
	अचिन्हित पूर्णांक v_ratio;
पूर्ण;

अटल अंतरभूत काष्ठा exynos_drm_plane_state *
to_exynos_plane_state(काष्ठा drm_plane_state *state)
अणु
	वापस container_of(state, काष्ठा exynos_drm_plane_state, base);
पूर्ण

/*
 * Exynos drm common overlay काष्ठाure.
 *
 * @base: plane object
 * @index: hardware index of the overlay layer
 *
 * this काष्ठाure is common to exynos SoC and its contents would be copied
 * to hardware specअगरic overlay info.
 */

काष्ठा exynos_drm_plane अणु
	काष्ठा drm_plane base;
	स्थिर काष्ठा exynos_drm_plane_config *config;
	अचिन्हित पूर्णांक index;
पूर्ण;

#घोषणा EXYNOS_DRM_PLANE_CAP_DOUBLE	(1 << 0)
#घोषणा EXYNOS_DRM_PLANE_CAP_SCALE	(1 << 1)
#घोषणा EXYNOS_DRM_PLANE_CAP_ZPOS	(1 << 2)
#घोषणा EXYNOS_DRM_PLANE_CAP_TILE	(1 << 3)
#घोषणा EXYNOS_DRM_PLANE_CAP_PIX_BLEND	(1 << 4)
#घोषणा EXYNOS_DRM_PLANE_CAP_WIN_BLEND	(1 << 5)

/*
 * Exynos DRM plane configuration काष्ठाure.
 *
 * @zpos: initial z-position of the plane.
 * @type: type of the plane (primary, cursor or overlay).
 * @pixel_क्रमmats: supported pixel क्रमmats.
 * @num_pixel_क्रमmats: number of elements in 'pixel_formats'.
 * @capabilities: supported features (see EXYNOS_DRM_PLANE_CAP_*)
 */

काष्ठा exynos_drm_plane_config अणु
	अचिन्हित पूर्णांक zpos;
	क्रमागत drm_plane_type type;
	स्थिर uपूर्णांक32_t *pixel_क्रमmats;
	अचिन्हित पूर्णांक num_pixel_क्रमmats;
	अचिन्हित पूर्णांक capabilities;
पूर्ण;

/*
 * Exynos drm crtc ops
 *
 * @atomic_enable: enable the device
 * @atomic_disable: disable the device
 * @enable_vblank: specअगरic driver callback क्रम enabling vblank पूर्णांकerrupt.
 * @disable_vblank: specअगरic driver callback क्रम disabling vblank पूर्णांकerrupt.
 * @mode_valid: specअगरic driver callback क्रम mode validation
 * @atomic_check: validate state
 * @atomic_begin: prepare device to receive an update
 * @atomic_flush: mark the end of device update
 * @update_plane: apply hardware specअगरic overlay data to रेजिस्टरs.
 * @disable_plane: disable hardware specअगरic overlay.
 * @te_handler: trigger to transfer video image at the tearing effect
 *	synchronization संकेत अगर there is a page flip request.
 */
काष्ठा exynos_drm_crtc;
काष्ठा exynos_drm_crtc_ops अणु
	व्योम (*atomic_enable)(काष्ठा exynos_drm_crtc *crtc);
	व्योम (*atomic_disable)(काष्ठा exynos_drm_crtc *crtc);
	पूर्णांक (*enable_vblank)(काष्ठा exynos_drm_crtc *crtc);
	व्योम (*disable_vblank)(काष्ठा exynos_drm_crtc *crtc);
	क्रमागत drm_mode_status (*mode_valid)(काष्ठा exynos_drm_crtc *crtc,
		स्थिर काष्ठा drm_display_mode *mode);
	bool (*mode_fixup)(काष्ठा exynos_drm_crtc *crtc,
			   स्थिर काष्ठा drm_display_mode *mode,
			   काष्ठा drm_display_mode *adjusted_mode);
	पूर्णांक (*atomic_check)(काष्ठा exynos_drm_crtc *crtc,
			    काष्ठा drm_crtc_state *state);
	व्योम (*atomic_begin)(काष्ठा exynos_drm_crtc *crtc);
	व्योम (*update_plane)(काष्ठा exynos_drm_crtc *crtc,
			     काष्ठा exynos_drm_plane *plane);
	व्योम (*disable_plane)(काष्ठा exynos_drm_crtc *crtc,
			      काष्ठा exynos_drm_plane *plane);
	व्योम (*atomic_flush)(काष्ठा exynos_drm_crtc *crtc);
	व्योम (*te_handler)(काष्ठा exynos_drm_crtc *crtc);
पूर्ण;

काष्ठा exynos_drm_clk अणु
	व्योम (*enable)(काष्ठा exynos_drm_clk *clk, bool enable);
पूर्ण;

/*
 * Exynos specअगरic crtc काष्ठाure.
 *
 * @base: crtc object.
 * @type: one of EXYNOS_DISPLAY_TYPE_LCD and HDMI.
 * @ops: poपूर्णांकer to callbacks क्रम exynos drm specअगरic functionality
 * @ctx: A poपूर्णांकer to the crtc's implementation specअगरic context
 * @pipe_clk: A poपूर्णांकer to the crtc's pipeline घड़ी.
 */
काष्ठा exynos_drm_crtc अणु
	काष्ठा drm_crtc			base;
	क्रमागत exynos_drm_output_type	type;
	स्थिर काष्ठा exynos_drm_crtc_ops	*ops;
	व्योम				*ctx;
	काष्ठा exynos_drm_clk		*pipe_clk;
	bool				i80_mode : 1;
पूर्ण;

अटल अंतरभूत व्योम exynos_drm_pipe_clk_enable(काष्ठा exynos_drm_crtc *crtc,
					      bool enable)
अणु
	अगर (crtc->pipe_clk)
		crtc->pipe_clk->enable(crtc->pipe_clk, enable);
पूर्ण

काष्ठा drm_exynos_file_निजी अणु
	/* क्रम g2d api */
	काष्ठा list_head	inuse_cmdlist;
	काष्ठा list_head	event_list;
	काष्ठा list_head	userptr_list;
पूर्ण;

/*
 * Exynos drm निजी काष्ठाure.
 *
 * @pending: the crtcs that have pending updates to finish
 * @lock: protect access to @pending
 * @रुको: रुको an atomic commit to finish
 */
काष्ठा exynos_drm_निजी अणु
	काष्ठा drm_fb_helper *fb_helper;

	काष्ठा device *g2d_dev;
	काष्ठा device *dma_dev;
	व्योम *mapping;

	/* क्रम atomic commit */
	u32			pending;
	spinlock_t		lock;
	रुको_queue_head_t	रुको;
पूर्ण;

अटल अंतरभूत काष्ठा device *to_dma_dev(काष्ठा drm_device *dev)
अणु
	काष्ठा exynos_drm_निजी *priv = dev->dev_निजी;

	वापस priv->dma_dev;
पूर्ण

अटल अंतरभूत bool is_drm_iommu_supported(काष्ठा drm_device *drm_dev)
अणु
	काष्ठा exynos_drm_निजी *priv = drm_dev->dev_निजी;

	वापस priv->mapping ? true : false;
पूर्ण

पूर्णांक exynos_drm_रेजिस्टर_dma(काष्ठा drm_device *drm, काष्ठा device *dev,
			    व्योम **dma_priv);
व्योम exynos_drm_unरेजिस्टर_dma(काष्ठा drm_device *drm, काष्ठा device *dev,
			       व्योम **dma_priv);
व्योम exynos_drm_cleanup_dma(काष्ठा drm_device *drm);

#अगर_घोषित CONFIG_DRM_EXYNOS_DPI
काष्ठा drm_encoder *exynos_dpi_probe(काष्ठा device *dev);
पूर्णांक exynos_dpi_हटाओ(काष्ठा drm_encoder *encoder);
पूर्णांक exynos_dpi_bind(काष्ठा drm_device *dev, काष्ठा drm_encoder *encoder);
#अन्यथा
अटल अंतरभूत काष्ठा drm_encoder *
exynos_dpi_probe(काष्ठा device *dev) अणु वापस शून्य; पूर्ण
अटल अंतरभूत पूर्णांक exynos_dpi_हटाओ(काष्ठा drm_encoder *encoder)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक exynos_dpi_bind(काष्ठा drm_device *dev,
				  काष्ठा drm_encoder *encoder)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DRM_EXYNOS_FIMC
पूर्णांक exynos_drm_check_fimc_device(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक exynos_drm_check_fimc_device(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक exynos_atomic_commit(काष्ठा drm_device *dev, काष्ठा drm_atomic_state *state,
			 bool nonblock);


बाह्य काष्ठा platक्रमm_driver fimd_driver;
बाह्य काष्ठा platक्रमm_driver exynos5433_decon_driver;
बाह्य काष्ठा platक्रमm_driver decon_driver;
बाह्य काष्ठा platक्रमm_driver dp_driver;
बाह्य काष्ठा platक्रमm_driver dsi_driver;
बाह्य काष्ठा platक्रमm_driver mixer_driver;
बाह्य काष्ठा platक्रमm_driver hdmi_driver;
बाह्य काष्ठा platक्रमm_driver vidi_driver;
बाह्य काष्ठा platक्रमm_driver g2d_driver;
बाह्य काष्ठा platक्रमm_driver fimc_driver;
बाह्य काष्ठा platक्रमm_driver rotator_driver;
बाह्य काष्ठा platक्रमm_driver scaler_driver;
बाह्य काष्ठा platक्रमm_driver gsc_driver;
बाह्य काष्ठा platक्रमm_driver mic_driver;
#पूर्ण_अगर
