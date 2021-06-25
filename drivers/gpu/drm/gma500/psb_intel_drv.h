<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2009-2011, Intel Corporation.
 */

#अगर_अघोषित __INTEL_DRV_H__
#घोषणा __INTEL_DRV_H__

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>
#समावेश "gma_display.h"

/*
 * Display related stuff
 */

/* maximum connectors per crtcs in the mode set */
#घोषणा INTELFB_CONN_LIMIT 4

/* Intel Pipe Clone Bit */
#घोषणा INTEL_HDMIB_CLONE_BIT 1
#घोषणा INTEL_HDMIC_CLONE_BIT 2
#घोषणा INTEL_HDMID_CLONE_BIT 3
#घोषणा INTEL_HDMIE_CLONE_BIT 4
#घोषणा INTEL_HDMIF_CLONE_BIT 5
#घोषणा INTEL_SDVO_NON_TV_CLONE_BIT 6
#घोषणा INTEL_SDVO_TV_CLONE_BIT 7
#घोषणा INTEL_SDVO_LVDS_CLONE_BIT 8
#घोषणा INTEL_ANALOG_CLONE_BIT 9
#घोषणा INTEL_TV_CLONE_BIT 10
#घोषणा INTEL_DP_B_CLONE_BIT 11
#घोषणा INTEL_DP_C_CLONE_BIT 12
#घोषणा INTEL_DP_D_CLONE_BIT 13
#घोषणा INTEL_LVDS_CLONE_BIT 14
#घोषणा INTEL_DVO_TMDS_CLONE_BIT 15
#घोषणा INTEL_DVO_LVDS_CLONE_BIT 16
#घोषणा INTEL_EDP_CLONE_BIT 17

/* these are outमाला_दो from the chip - पूर्णांकegrated only
 * बाह्यal chips are via DVO or SDVO output */
#घोषणा INTEL_OUTPUT_UNUSED 0
#घोषणा INTEL_OUTPUT_ANALOG 1
#घोषणा INTEL_OUTPUT_DVO 2
#घोषणा INTEL_OUTPUT_SDVO 3
#घोषणा INTEL_OUTPUT_LVDS 4
#घोषणा INTEL_OUTPUT_TVOUT 5
#घोषणा INTEL_OUTPUT_HDMI 6
#घोषणा INTEL_OUTPUT_MIPI 7
#घोषणा INTEL_OUTPUT_MIPI2 8
#घोषणा INTEL_OUTPUT_DISPLAYPORT 9
#घोषणा INTEL_OUTPUT_EDP 10

/*
 * Hold inक्रमmation useally put on the device driver निजीs here,
 * since it needs to be shared across multiple of devices drivers निजीs.
 */
काष्ठा psb_पूर्णांकel_mode_device अणु

	/*
	 * Abstracted memory manager operations
	 */
	 माप_प्रकार(*bo_offset) (काष्ठा drm_device *dev, व्योम *bo);

	/*
	 * LVDS info
	 */
	पूर्णांक backlight_duty_cycle;	/* restore backlight to this value */
	bool panel_wants_dither;
	काष्ठा drm_display_mode *panel_fixed_mode;
	काष्ठा drm_display_mode *panel_fixed_mode2;
	काष्ठा drm_display_mode *vbt_mode;	/* अगर any */

	uपूर्णांक32_t saveBLC_PWM_CTL;
पूर्ण;

काष्ठा psb_पूर्णांकel_i2c_chan अणु
	/* क्रम getting at dev. निजी (mmio etc.) */
	काष्ठा drm_device *drm_dev;
	u32 reg;		/* GPIO reg */
	काष्ठा i2c_adapter adapter;
	काष्ठा i2c_algo_bit_data algo;
	u8 slave_addr;
पूर्ण;

काष्ठा gma_encoder अणु
	काष्ठा drm_encoder base;
	पूर्णांक type;
	bool needs_tv_घड़ी;
	व्योम (*hot_plug)(काष्ठा gma_encoder *);
	पूर्णांक crtc_mask;
	पूर्णांक clone_mask;
	u32 ddi_select;	/* Channel info */
#घोषणा DDI0_SELECT	0x01
#घोषणा DDI1_SELECT	0x02
#घोषणा DP_MASK		0x8000
#घोषणा DDI_MASK	0x03
	व्योम *dev_priv; /* For sdvo_priv, lvds_priv, etc... */

	/* FIXME: Either make SDVO and LVDS store it's i2c here or give CDV it's
	   own set of output निजीs */
	काष्ठा psb_पूर्णांकel_i2c_chan *i2c_bus;
	काष्ठा psb_पूर्णांकel_i2c_chan *ddc_bus;
पूर्ण;

काष्ठा gma_connector अणु
	काष्ठा drm_connector base;
	काष्ठा gma_encoder *encoder;

	व्योम (*save)(काष्ठा drm_connector *connector);
	व्योम (*restore)(काष्ठा drm_connector *connector);
पूर्ण;

काष्ठा psb_पूर्णांकel_crtc_state अणु
	uपूर्णांक32_t saveDSPCNTR;
	uपूर्णांक32_t savePIPECONF;
	uपूर्णांक32_t savePIPESRC;
	uपूर्णांक32_t saveDPLL;
	uपूर्णांक32_t saveFP0;
	uपूर्णांक32_t saveFP1;
	uपूर्णांक32_t saveHTOTAL;
	uपूर्णांक32_t saveHBLANK;
	uपूर्णांक32_t saveHSYNC;
	uपूर्णांक32_t saveVTOTAL;
	uपूर्णांक32_t saveVBLANK;
	uपूर्णांक32_t saveVSYNC;
	uपूर्णांक32_t saveDSPSTRIDE;
	uपूर्णांक32_t saveDSPSIZE;
	uपूर्णांक32_t saveDSPPOS;
	uपूर्णांक32_t saveDSPBASE;
	uपूर्णांक32_t savePalette[256];
पूर्ण;

काष्ठा gma_crtc अणु
	काष्ठा drm_crtc base;
	पूर्णांक pipe;
	पूर्णांक plane;
	uपूर्णांक32_t cursor_addr;
	काष्ठा gtt_range *cursor_gt;
	u8 lut_adj[256];
	काष्ठा psb_पूर्णांकel_framebuffer *fbdev_fb;
	/* a mode_set क्रम fbdev users on this crtc */
	काष्ठा drm_mode_set mode_set;

	/* GEM object that holds our cursor */
	काष्ठा drm_gem_object *cursor_obj;

	काष्ठा drm_display_mode saved_mode;
	काष्ठा drm_display_mode saved_adjusted_mode;

	काष्ठा psb_पूर्णांकel_mode_device *mode_dev;

	/*crtc mode setting flags*/
	u32 mode_flags;

	bool active;

	/* Saved Crtc HW states */
	काष्ठा psb_पूर्णांकel_crtc_state *crtc_state;

	स्थिर काष्ठा gma_घड़ी_funcs *घड़ी_funcs;

	काष्ठा drm_pending_vblank_event *page_flip_event;
पूर्ण;

#घोषणा to_gma_crtc(x)	\
		container_of(x, काष्ठा gma_crtc, base)
#घोषणा to_gma_connector(x) \
		container_of(x, काष्ठा gma_connector, base)
#घोषणा to_gma_encoder(x)	\
		container_of(x, काष्ठा gma_encoder, base)
#घोषणा to_psb_पूर्णांकel_framebuffer(x)	\
		container_of(x, काष्ठा psb_पूर्णांकel_framebuffer, base)

काष्ठा psb_पूर्णांकel_i2c_chan *psb_पूर्णांकel_i2c_create(काष्ठा drm_device *dev,
					स्थिर u32 reg, स्थिर अक्षर *name);
व्योम psb_पूर्णांकel_i2c_destroy(काष्ठा psb_पूर्णांकel_i2c_chan *chan);
पूर्णांक psb_पूर्णांकel_ddc_get_modes(काष्ठा drm_connector *connector,
			    काष्ठा i2c_adapter *adapter);
बाह्य bool psb_पूर्णांकel_ddc_probe(काष्ठा i2c_adapter *adapter);

बाह्य व्योम psb_पूर्णांकel_crtc_init(काष्ठा drm_device *dev, पूर्णांक pipe,
			    काष्ठा psb_पूर्णांकel_mode_device *mode_dev);
बाह्य व्योम psb_पूर्णांकel_crt_init(काष्ठा drm_device *dev);
बाह्य bool psb_पूर्णांकel_sdvo_init(काष्ठा drm_device *dev, पूर्णांक output_device);
बाह्य व्योम psb_पूर्णांकel_dvo_init(काष्ठा drm_device *dev);
बाह्य व्योम psb_पूर्णांकel_tv_init(काष्ठा drm_device *dev);
बाह्य व्योम psb_पूर्णांकel_lvds_init(काष्ठा drm_device *dev,
			    काष्ठा psb_पूर्णांकel_mode_device *mode_dev);
बाह्य व्योम psb_पूर्णांकel_lvds_set_brightness(काष्ठा drm_device *dev, पूर्णांक level);
बाह्य व्योम oaktrail_lvds_init(काष्ठा drm_device *dev,
			   काष्ठा psb_पूर्णांकel_mode_device *mode_dev);
बाह्य व्योम oaktrail_रुको_क्रम_INTR_PKT_SENT(काष्ठा drm_device *dev);
बाह्य व्योम oaktrail_dsi_init(काष्ठा drm_device *dev,
			   काष्ठा psb_पूर्णांकel_mode_device *mode_dev);
बाह्य व्योम oaktrail_lvds_i2c_init(काष्ठा drm_encoder *encoder);
बाह्य व्योम mid_dsi_init(काष्ठा drm_device *dev,
		    काष्ठा psb_पूर्णांकel_mode_device *mode_dev, पूर्णांक dsi_num);

बाह्य काष्ठा drm_encoder *gma_best_encoder(काष्ठा drm_connector *connector);
बाह्य व्योम gma_connector_attach_encoder(काष्ठा gma_connector *connector,
					 काष्ठा gma_encoder *encoder);

अटल अंतरभूत काष्ठा gma_encoder *gma_attached_encoder(
						काष्ठा drm_connector *connector)
अणु
	वापस to_gma_connector(connector)->encoder;
पूर्ण

बाह्य काष्ठा drm_display_mode *psb_पूर्णांकel_crtc_mode_get(काष्ठा drm_device *dev,
						    काष्ठा drm_crtc *crtc);
बाह्य काष्ठा drm_crtc *psb_पूर्णांकel_get_crtc_from_pipe(काष्ठा drm_device *dev,
						 पूर्णांक pipe);
बाह्य काष्ठा drm_connector *psb_पूर्णांकel_sdvo_find(काष्ठा drm_device *dev,
					     पूर्णांक sdvoB);
बाह्य पूर्णांक psb_पूर्णांकel_sdvo_supports_hotplug(काष्ठा drm_connector *connector);
बाह्य व्योम psb_पूर्णांकel_sdvo_set_hotplug(काष्ठा drm_connector *connector,
				   पूर्णांक enable);
बाह्य पूर्णांक पूर्णांकelfb_probe(काष्ठा drm_device *dev);
बाह्य पूर्णांक पूर्णांकelfb_हटाओ(काष्ठा drm_device *dev,
			  काष्ठा drm_framebuffer *fb);
बाह्य bool psb_पूर्णांकel_lvds_mode_fixup(काष्ठा drm_encoder *encoder,
				      स्थिर काष्ठा drm_display_mode *mode,
				      काष्ठा drm_display_mode *adjusted_mode);
बाह्य क्रमागत drm_mode_status psb_पूर्णांकel_lvds_mode_valid(काष्ठा drm_connector *connector,
				     काष्ठा drm_display_mode *mode);
बाह्य पूर्णांक psb_पूर्णांकel_lvds_set_property(काष्ठा drm_connector *connector,
					काष्ठा drm_property *property,
					uपूर्णांक64_t value);
बाह्य व्योम psb_पूर्णांकel_lvds_destroy(काष्ठा drm_connector *connector);

/* पूर्णांकel_gmbus.c */
बाह्य व्योम gma_पूर्णांकel_i2c_reset(काष्ठा drm_device *dev);
बाह्य पूर्णांक gma_पूर्णांकel_setup_gmbus(काष्ठा drm_device *dev);
बाह्य व्योम gma_पूर्णांकel_gmbus_set_speed(काष्ठा i2c_adapter *adapter, पूर्णांक speed);
बाह्य व्योम gma_पूर्णांकel_gmbus_क्रमce_bit(काष्ठा i2c_adapter *adapter, bool क्रमce_bit);
बाह्य व्योम gma_पूर्णांकel_tearकरोwn_gmbus(काष्ठा drm_device *dev);

/* DP support */
बाह्य व्योम cdv_पूर्णांकel_dp_init(काष्ठा drm_device *dev, काष्ठा psb_पूर्णांकel_mode_device *mode_dev, पूर्णांक output_reg);
बाह्य व्योम cdv_पूर्णांकel_dp_set_m_n(काष्ठा drm_crtc *crtc,
					काष्ठा drm_display_mode *mode,
					काष्ठा drm_display_mode *adjusted_mode);

बाह्य व्योम psb_पूर्णांकel_attach_क्रमce_audio_property(काष्ठा drm_connector *connector);
बाह्य व्योम psb_पूर्णांकel_attach_broadcast_rgb_property(काष्ठा drm_connector *connector);

बाह्य पूर्णांक cdv_sb_पढ़ो(काष्ठा drm_device *dev, u32 reg, u32 *val);
बाह्य पूर्णांक cdv_sb_ग_लिखो(काष्ठा drm_device *dev, u32 reg, u32 val);
बाह्य व्योम cdv_sb_reset(काष्ठा drm_device *dev);

बाह्य व्योम cdv_पूर्णांकel_attach_क्रमce_audio_property(काष्ठा drm_connector *connector);
बाह्य व्योम cdv_पूर्णांकel_attach_broadcast_rgb_property(काष्ठा drm_connector *connector);

#पूर्ण_अगर				/* __INTEL_DRV_H__ */
