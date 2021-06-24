<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 Chris Zhong <zyw@rock-chips.com>
 * Copyright (C) 2016 ROCKCHIP, Inc.
 */

#अगर_अघोषित _CDN_DP_CORE_H
#घोषणा _CDN_DP_CORE_H

#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "rockchip_drm_drv.h"

#घोषणा MAX_PHY		2

क्रमागत audio_क्रमmat अणु
	AFMT_I2S = 0,
	AFMT_SPDIF = 1,
	AFMT_UNUSED,
पूर्ण;

काष्ठा audio_info अणु
	क्रमागत audio_क्रमmat क्रमmat;
	पूर्णांक sample_rate;
	पूर्णांक channels;
	पूर्णांक sample_width;
पूर्ण;

क्रमागत vic_pxl_encoding_क्रमmat अणु
	PXL_RGB = 0x1,
	YCBCR_4_4_4 = 0x2,
	YCBCR_4_2_2 = 0x4,
	YCBCR_4_2_0 = 0x8,
	Y_ONLY = 0x10,
पूर्ण;

काष्ठा video_info अणु
	bool h_sync_polarity;
	bool v_sync_polarity;
	bool पूर्णांकerlaced;
	पूर्णांक color_depth;
	क्रमागत vic_pxl_encoding_क्रमmat color_fmt;
पूर्ण;

काष्ठा cdn_firmware_header अणु
	u32 size_bytes; /* size of the entire header+image(s) in bytes */
	u32 header_size; /* size of just the header in bytes */
	u32 iram_size; /* size of iram */
	u32 dram_size; /* size of dram */
पूर्ण;

काष्ठा cdn_dp_port अणु
	काष्ठा cdn_dp_device *dp;
	काष्ठा notअगरier_block event_nb;
	काष्ठा extcon_dev *extcon;
	काष्ठा phy *phy;
	u8 lanes;
	bool phy_enabled;
	u8 id;
पूर्ण;

काष्ठा cdn_dp_device अणु
	काष्ठा device *dev;
	काष्ठा drm_device *drm_dev;
	काष्ठा drm_connector connector;
	काष्ठा drm_encoder encoder;
	काष्ठा drm_display_mode mode;
	काष्ठा platक्रमm_device *audio_pdev;
	काष्ठा work_काष्ठा event_work;
	काष्ठा edid *edid;

	काष्ठा mutex lock;
	bool connected;
	bool active;
	bool suspended;

	स्थिर काष्ठा firmware *fw;	/* cdn dp firmware */
	अचिन्हित पूर्णांक fw_version;	/* cdn fw version */
	bool fw_loaded;

	व्योम __iomem *regs;
	काष्ठा regmap *grf;
	काष्ठा clk *core_clk;
	काष्ठा clk *pclk;
	काष्ठा clk *spdअगर_clk;
	काष्ठा clk *grf_clk;
	काष्ठा reset_control *spdअगर_rst;
	काष्ठा reset_control *dptx_rst;
	काष्ठा reset_control *apb_rst;
	काष्ठा reset_control *core_rst;
	काष्ठा audio_info audio_info;
	काष्ठा video_info video_info;
	काष्ठा cdn_dp_port *port[MAX_PHY];
	u8 ports;
	u8 max_lanes;
	अचिन्हित पूर्णांक max_rate;
	u8 lanes;
	पूर्णांक active_port;

	u8 dpcd[DP_RECEIVER_CAP_SIZE];
	bool sink_has_audio;
पूर्ण;
#पूर्ण_अगर  /* _CDN_DP_CORE_H */
