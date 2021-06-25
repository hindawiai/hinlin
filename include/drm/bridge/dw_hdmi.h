<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित __DW_HDMI__
#घोषणा __DW_HDMI__

#समावेश <sound/hdmi-codec.h>

काष्ठा drm_display_info;
काष्ठा drm_display_mode;
काष्ठा drm_encoder;
काष्ठा dw_hdmi;
काष्ठा platक्रमm_device;

/**
 * DOC: Supported input क्रमmats and encodings
 *
 * Depending on the Hardware configuration of the Controller IP, it supports
 * a subset of the following input क्रमmats and encodings on its पूर्णांकernal
 * 48bit bus.
 *
 * +----------------------+----------------------------------+------------------------------+
 * | Format Name          | Format Code                      | Encodings                    |
 * +----------------------+----------------------------------+------------------------------+
 * | RGB 4:4:4 8bit       | ``MEDIA_BUS_FMT_RGB888_1X24``    | ``V4L2_YCBCR_ENC_DEFAULT``   |
 * +----------------------+----------------------------------+------------------------------+
 * | RGB 4:4:4 10bits     | ``MEDIA_BUS_FMT_RGB101010_1X30`` | ``V4L2_YCBCR_ENC_DEFAULT``   |
 * +----------------------+----------------------------------+------------------------------+
 * | RGB 4:4:4 12bits     | ``MEDIA_BUS_FMT_RGB121212_1X36`` | ``V4L2_YCBCR_ENC_DEFAULT``   |
 * +----------------------+----------------------------------+------------------------------+
 * | RGB 4:4:4 16bits     | ``MEDIA_BUS_FMT_RGB161616_1X48`` | ``V4L2_YCBCR_ENC_DEFAULT``   |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCr 4:4:4 8bit     | ``MEDIA_BUS_FMT_YUV8_1X24``      | ``V4L2_YCBCR_ENC_601``       |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_709``    |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_XV601``  |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_XV709``  |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCr 4:4:4 10bits   | ``MEDIA_BUS_FMT_YUV10_1X30``     | ``V4L2_YCBCR_ENC_601``       |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_709``    |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_XV601``  |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_XV709``  |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCr 4:4:4 12bits   | ``MEDIA_BUS_FMT_YUV12_1X36``     | ``V4L2_YCBCR_ENC_601``       |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_709``    |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_XV601``  |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_XV709``  |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCr 4:4:4 16bits   | ``MEDIA_BUS_FMT_YUV16_1X48``     | ``V4L2_YCBCR_ENC_601``       |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_709``    |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_XV601``  |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_XV709``  |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCr 4:2:2 8bit     | ``MEDIA_BUS_FMT_UYVY8_1X16``     | ``V4L2_YCBCR_ENC_601``       |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_709``    |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCr 4:2:2 10bits   | ``MEDIA_BUS_FMT_UYVY10_1X20``    | ``V4L2_YCBCR_ENC_601``       |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_709``    |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCr 4:2:2 12bits   | ``MEDIA_BUS_FMT_UYVY12_1X24``    | ``V4L2_YCBCR_ENC_601``       |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_709``    |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCr 4:2:0 8bit     | ``MEDIA_BUS_FMT_UYYVYY8_0_5X24`` | ``V4L2_YCBCR_ENC_601``       |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_709``    |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCr 4:2:0 10bits   | ``MEDIA_BUS_FMT_UYYVYY10_0_5X30``| ``V4L2_YCBCR_ENC_601``       |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_709``    |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCr 4:2:0 12bits   | ``MEDIA_BUS_FMT_UYYVYY12_0_5X36``| ``V4L2_YCBCR_ENC_601``       |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_709``    |
 * +----------------------+----------------------------------+------------------------------+
 * | YCbCr 4:2:0 16bits   | ``MEDIA_BUS_FMT_UYYVYY16_0_5X48``| ``V4L2_YCBCR_ENC_601``       |
 * |                      |                                  | or ``V4L2_YCBCR_ENC_709``    |
 * +----------------------+----------------------------------+------------------------------+
 */

क्रमागत अणु
	DW_HDMI_RES_8,
	DW_HDMI_RES_10,
	DW_HDMI_RES_12,
	DW_HDMI_RES_MAX,
पूर्ण;

क्रमागत dw_hdmi_phy_type अणु
	DW_HDMI_PHY_DWC_HDMI_TX_PHY = 0x00,
	DW_HDMI_PHY_DWC_MHL_PHY_HEAC = 0xb2,
	DW_HDMI_PHY_DWC_MHL_PHY = 0xc2,
	DW_HDMI_PHY_DWC_HDMI_3D_TX_PHY_HEAC = 0xe2,
	DW_HDMI_PHY_DWC_HDMI_3D_TX_PHY = 0xf2,
	DW_HDMI_PHY_DWC_HDMI20_TX_PHY = 0xf3,
	DW_HDMI_PHY_VENDOR_PHY = 0xfe,
पूर्ण;

काष्ठा dw_hdmi_mpll_config अणु
	अचिन्हित दीर्घ mpixelघड़ी;
	काष्ठा अणु
		u16 cpce;
		u16 gmp;
	पूर्ण res[DW_HDMI_RES_MAX];
पूर्ण;

काष्ठा dw_hdmi_curr_ctrl अणु
	अचिन्हित दीर्घ mpixelघड़ी;
	u16 curr[DW_HDMI_RES_MAX];
पूर्ण;

काष्ठा dw_hdmi_phy_config अणु
	अचिन्हित दीर्घ mpixelघड़ी;
	u16 sym_ctr;    /*घड़ी symbol and transmitter control*/
	u16 term;       /*transmission termination value*/
	u16 vlev_ctr;   /* voltage level control */
पूर्ण;

काष्ठा dw_hdmi_phy_ops अणु
	पूर्णांक (*init)(काष्ठा dw_hdmi *hdmi, व्योम *data,
		    स्थिर काष्ठा drm_display_info *display,
		    स्थिर काष्ठा drm_display_mode *mode);
	व्योम (*disable)(काष्ठा dw_hdmi *hdmi, व्योम *data);
	क्रमागत drm_connector_status (*पढ़ो_hpd)(काष्ठा dw_hdmi *hdmi, व्योम *data);
	व्योम (*update_hpd)(काष्ठा dw_hdmi *hdmi, व्योम *data,
			   bool क्रमce, bool disabled, bool rxsense);
	व्योम (*setup_hpd)(काष्ठा dw_hdmi *hdmi, व्योम *data);
पूर्ण;

काष्ठा dw_hdmi_plat_data अणु
	काष्ठा regmap *regm;

	अचिन्हित दीर्घ input_bus_encoding;
	bool use_drm_infoframe;
	bool ycbcr_420_allowed;

	/*
	 * Private data passed to all the .mode_valid() and .configure_phy()
	 * callback functions.
	 */
	व्योम *priv_data;

	/* Platक्रमm-specअगरic mode validation (optional). */
	क्रमागत drm_mode_status (*mode_valid)(काष्ठा dw_hdmi *hdmi, व्योम *data,
					   स्थिर काष्ठा drm_display_info *info,
					   स्थिर काष्ठा drm_display_mode *mode);

	/* Venकरोr PHY support */
	स्थिर काष्ठा dw_hdmi_phy_ops *phy_ops;
	स्थिर अक्षर *phy_name;
	व्योम *phy_data;
	अचिन्हित पूर्णांक phy_क्रमce_venकरोr;

	/* Synopsys PHY support */
	स्थिर काष्ठा dw_hdmi_mpll_config *mpll_cfg;
	स्थिर काष्ठा dw_hdmi_curr_ctrl *cur_ctr;
	स्थिर काष्ठा dw_hdmi_phy_config *phy_config;
	पूर्णांक (*configure_phy)(काष्ठा dw_hdmi *hdmi, व्योम *data,
			     अचिन्हित दीर्घ mpixelघड़ी);
पूर्ण;

काष्ठा dw_hdmi *dw_hdmi_probe(काष्ठा platक्रमm_device *pdev,
			      स्थिर काष्ठा dw_hdmi_plat_data *plat_data);
व्योम dw_hdmi_हटाओ(काष्ठा dw_hdmi *hdmi);
व्योम dw_hdmi_unbind(काष्ठा dw_hdmi *hdmi);
काष्ठा dw_hdmi *dw_hdmi_bind(काष्ठा platक्रमm_device *pdev,
			     काष्ठा drm_encoder *encoder,
			     स्थिर काष्ठा dw_hdmi_plat_data *plat_data);

व्योम dw_hdmi_resume(काष्ठा dw_hdmi *hdmi);

व्योम dw_hdmi_setup_rx_sense(काष्ठा dw_hdmi *hdmi, bool hpd, bool rx_sense);

पूर्णांक dw_hdmi_set_plugged_cb(काष्ठा dw_hdmi *hdmi, hdmi_codec_plugged_cb fn,
			   काष्ठा device *codec_dev);
व्योम dw_hdmi_set_sample_rate(काष्ठा dw_hdmi *hdmi, अचिन्हित पूर्णांक rate);
व्योम dw_hdmi_set_channel_count(काष्ठा dw_hdmi *hdmi, अचिन्हित पूर्णांक cnt);
व्योम dw_hdmi_set_channel_status(काष्ठा dw_hdmi *hdmi, u8 *channel_status);
व्योम dw_hdmi_set_channel_allocation(काष्ठा dw_hdmi *hdmi, अचिन्हित पूर्णांक ca);
व्योम dw_hdmi_audio_enable(काष्ठा dw_hdmi *hdmi);
व्योम dw_hdmi_audio_disable(काष्ठा dw_hdmi *hdmi);
व्योम dw_hdmi_set_high_पंचांगds_घड़ी_ratio(काष्ठा dw_hdmi *hdmi,
				       स्थिर काष्ठा drm_display_info *display);

/* PHY configuration */
व्योम dw_hdmi_phy_i2c_set_addr(काष्ठा dw_hdmi *hdmi, u8 address);
व्योम dw_hdmi_phy_i2c_ग_लिखो(काष्ठा dw_hdmi *hdmi, अचिन्हित लघु data,
			   अचिन्हित अक्षर addr);

व्योम dw_hdmi_phy_gen2_pddq(काष्ठा dw_hdmi *hdmi, u8 enable);
व्योम dw_hdmi_phy_gen2_txpwron(काष्ठा dw_hdmi *hdmi, u8 enable);
व्योम dw_hdmi_phy_reset(काष्ठा dw_hdmi *hdmi);

क्रमागत drm_connector_status dw_hdmi_phy_पढ़ो_hpd(काष्ठा dw_hdmi *hdmi,
					       व्योम *data);
व्योम dw_hdmi_phy_update_hpd(काष्ठा dw_hdmi *hdmi, व्योम *data,
			    bool क्रमce, bool disabled, bool rxsense);
व्योम dw_hdmi_phy_setup_hpd(काष्ठा dw_hdmi *hdmi, व्योम *data);

#पूर्ण_अगर /* __IMX_HDMI_H__ */
