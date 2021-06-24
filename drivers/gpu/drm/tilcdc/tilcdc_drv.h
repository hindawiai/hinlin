<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Texas Instruments
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित __TILCDC_DRV_H__
#घोषणा __TILCDC_DRV_H__

#समावेश <linux/cpufreq.h>
#समावेश <linux/irqवापस.h>

#समावेश <drm/drm_prपूर्णांक.h>

काष्ठा clk;
काष्ठा workqueue_काष्ठा;

काष्ठा drm_connector;
काष्ठा drm_connector_helper_funcs;
काष्ठा drm_crtc;
काष्ठा drm_device;
काष्ठा drm_display_mode;
काष्ठा drm_encoder;
काष्ठा drm_framebuffer;
काष्ठा drm_minor;
काष्ठा drm_pending_vblank_event;
काष्ठा drm_plane;

/* Defaulting to pixel घड़ी defined on AM335x */
#घोषणा TILCDC_DEFAULT_MAX_PIXELCLOCK  126000
/* Maximum display width क्रम LCDC V1 */
#घोषणा TILCDC_DEFAULT_MAX_WIDTH_V1  1024
/* ... and क्रम LCDC V2 found on AM335x: */
#घोषणा TILCDC_DEFAULT_MAX_WIDTH_V2  2048
/*
 * This may need some tweaking, but want to allow at least 1280x1024@60
 * with optimized DDR & EMIF settings tweaked 1920x1080@24 appears to
 * be supportable
 */
#घोषणा TILCDC_DEFAULT_MAX_BANDWIDTH  (1280*1024*60)


काष्ठा tilcdc_drm_निजी अणु
	व्योम __iomem *mmio;

	काष्ठा clk *clk;         /* functional घड़ी */
	पूर्णांक rev;                 /* IP revision */

	/* करोn't attempt resolutions w/ higher W * H * Hz: */
	uपूर्णांक32_t max_bandwidth;
	/*
	 * Pixel Clock will be restricted to some value as
	 * defined in the device datasheet measured in KHz
	 */
	uपूर्णांक32_t max_pixelघड़ी;
	/*
	 * Max allowable width is limited on a per device basis
	 * measured in pixels
	 */
	uपूर्णांक32_t max_width;

	/* Supported pixel क्रमmats */
	स्थिर uपूर्णांक32_t *pixelक्रमmats;
	uपूर्णांक32_t num_pixelक्रमmats;

#अगर_घोषित CONFIG_CPU_FREQ
	काष्ठा notअगरier_block freq_transition;
#पूर्ण_अगर

	काष्ठा workqueue_काष्ठा *wq;

	काष्ठा drm_crtc *crtc;

	अचिन्हित पूर्णांक num_encoders;
	काष्ठा drm_encoder *encoders[8];

	अचिन्हित पूर्णांक num_connectors;
	काष्ठा drm_connector *connectors[8];

	काष्ठा drm_encoder *बाह्यal_encoder;
	काष्ठा drm_connector *बाह्यal_connector;

	bool is_रेजिस्टरed;
	bool is_componentized;
पूर्ण;

/* Sub-module क्रम display.  Since we करोn't know at compile समय what panels
 * or display adapter(s) might be present (क्रम ex, off chip dvi/tfp410,
 * hdmi encoder, various lcd panels), the connector/encoder(s) are split पूर्णांकo
 * separate drivers.  If they are probed and found to be present, they
 * रेजिस्टर themselves with tilcdc_रेजिस्टर_module().
 */
काष्ठा tilcdc_module;

काष्ठा tilcdc_module_ops अणु
	/* create appropriate encoders/connectors: */
	पूर्णांक (*modeset_init)(काष्ठा tilcdc_module *mod, काष्ठा drm_device *dev);
#अगर_घोषित CONFIG_DEBUG_FS
	/* create debugfs nodes (can be शून्य): */
	पूर्णांक (*debugfs_init)(काष्ठा tilcdc_module *mod, काष्ठा drm_minor *minor);
#पूर्ण_अगर
पूर्ण;

काष्ठा tilcdc_module अणु
	स्थिर अक्षर *name;
	काष्ठा list_head list;
	स्थिर काष्ठा tilcdc_module_ops *funcs;
पूर्ण;

व्योम tilcdc_module_init(काष्ठा tilcdc_module *mod, स्थिर अक्षर *name,
		स्थिर काष्ठा tilcdc_module_ops *funcs);
व्योम tilcdc_module_cleanup(काष्ठा tilcdc_module *mod);

/* Panel config that needs to be set in the crtc, but is not coming from
 * the mode timings.  The display module is expected to call
 * tilcdc_crtc_set_panel_info() to set this during modeset.
 */
काष्ठा tilcdc_panel_info अणु

	/* AC Bias Pin Frequency */
	uपूर्णांक32_t ac_bias;

	/* AC Bias Pin Transitions per Interrupt */
	uपूर्णांक32_t ac_bias_पूर्णांकrpt;

	/* DMA burst size */
	uपूर्णांक32_t dma_burst_sz;

	/* Bits per pixel */
	uपूर्णांक32_t bpp;

	/* FIFO DMA Request Delay */
	uपूर्णांक32_t fdd;

	/* TFT Alternative Signal Mapping (Only क्रम active) */
	bool tft_alt_mode;

	/* Invert pixel घड़ी */
	bool invert_pxl_clk;

	/* Horizontal and Vertical Sync Edge: 0=rising 1=falling */
	uपूर्णांक32_t sync_edge;

	/* Horizontal and Vertical Sync: Control: 0=ignore */
	uपूर्णांक32_t sync_ctrl;

	/* Raster Data Order Select: 1=Most-to-least 0=Least-to-most */
	uपूर्णांक32_t raster_order;

	/* DMA FIFO threshold */
	uपूर्णांक32_t fअगरo_th;
पूर्ण;

#घोषणा DBG(fmt, ...) DRM_DEBUG(fmt"\n", ##__VA_ARGS__)

पूर्णांक tilcdc_crtc_create(काष्ठा drm_device *dev);
irqवापस_t tilcdc_crtc_irq(काष्ठा drm_crtc *crtc);
व्योम tilcdc_crtc_update_clk(काष्ठा drm_crtc *crtc);
व्योम tilcdc_crtc_set_panel_info(काष्ठा drm_crtc *crtc,
		स्थिर काष्ठा tilcdc_panel_info *info);
व्योम tilcdc_crtc_set_simulate_vesa_sync(काष्ठा drm_crtc *crtc,
					bool simulate_vesa_sync);
व्योम tilcdc_crtc_shutकरोwn(काष्ठा drm_crtc *crtc);
पूर्णांक tilcdc_crtc_update_fb(काष्ठा drm_crtc *crtc,
		काष्ठा drm_framebuffer *fb,
		काष्ठा drm_pending_vblank_event *event);

पूर्णांक tilcdc_plane_init(काष्ठा drm_device *dev, काष्ठा drm_plane *plane);

#पूर्ण_अगर /* __TILCDC_DRV_H__ */
