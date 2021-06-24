<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2017-2020, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DP_CATALOG_H_
#घोषणा _DP_CATALOG_H_

#समावेश <drm/drm_modes.h>

#समावेश "dp_parser.h"

/* पूर्णांकerrupts */
#घोषणा DP_INTR_HPD		BIT(0)
#घोषणा DP_INTR_AUX_I2C_DONE	BIT(3)
#घोषणा DP_INTR_WRONG_ADDR	BIT(6)
#घोषणा DP_INTR_TIMEOUT		BIT(9)
#घोषणा DP_INTR_NACK_DEFER	BIT(12)
#घोषणा DP_INTR_WRONG_DATA_CNT	BIT(15)
#घोषणा DP_INTR_I2C_NACK	BIT(18)
#घोषणा DP_INTR_I2C_DEFER	BIT(21)
#घोषणा DP_INTR_PLL_UNLOCKED	BIT(24)
#घोषणा DP_INTR_AUX_ERROR	BIT(27)

#घोषणा DP_INTR_READY_FOR_VIDEO		BIT(0)
#घोषणा DP_INTR_IDLE_PATTERN_SENT	BIT(3)
#घोषणा DP_INTR_FRAME_END		BIT(6)
#घोषणा DP_INTR_CRC_UPDATED		BIT(9)

#घोषणा DP_AUX_CFG_MAX_VALUE_CNT 3

/* PHY AUX config रेजिस्टरs */
क्रमागत dp_phy_aux_config_type अणु
	PHY_AUX_CFG0,
	PHY_AUX_CFG1,
	PHY_AUX_CFG2,
	PHY_AUX_CFG3,
	PHY_AUX_CFG4,
	PHY_AUX_CFG5,
	PHY_AUX_CFG6,
	PHY_AUX_CFG7,
	PHY_AUX_CFG8,
	PHY_AUX_CFG9,
	PHY_AUX_CFG_MAX,
पूर्ण;

क्रमागत dp_catalog_audio_sdp_type अणु
	DP_AUDIO_SDP_STREAM,
	DP_AUDIO_SDP_TIMESTAMP,
	DP_AUDIO_SDP_INFOFRAME,
	DP_AUDIO_SDP_COPYMANAGEMENT,
	DP_AUDIO_SDP_ISRC,
	DP_AUDIO_SDP_MAX,
पूर्ण;

क्रमागत dp_catalog_audio_header_type अणु
	DP_AUDIO_SDP_HEADER_1,
	DP_AUDIO_SDP_HEADER_2,
	DP_AUDIO_SDP_HEADER_3,
	DP_AUDIO_SDP_HEADER_MAX,
पूर्ण;

काष्ठा dp_catalog अणु
	u32 aux_data;
	u32 total;
	u32 sync_start;
	u32 width_blanking;
	u32 dp_active;
	क्रमागत dp_catalog_audio_sdp_type sdp_type;
	क्रमागत dp_catalog_audio_header_type sdp_header;
	u32 audio_data;
पूर्ण;

/* AUX APIs */
u32 dp_catalog_aux_पढ़ो_data(काष्ठा dp_catalog *dp_catalog);
पूर्णांक dp_catalog_aux_ग_लिखो_data(काष्ठा dp_catalog *dp_catalog);
पूर्णांक dp_catalog_aux_ग_लिखो_trans(काष्ठा dp_catalog *dp_catalog);
पूर्णांक dp_catalog_aux_clear_trans(काष्ठा dp_catalog *dp_catalog, bool पढ़ो);
पूर्णांक dp_catalog_aux_clear_hw_पूर्णांकerrupts(काष्ठा dp_catalog *dp_catalog);
व्योम dp_catalog_aux_reset(काष्ठा dp_catalog *dp_catalog);
व्योम dp_catalog_aux_enable(काष्ठा dp_catalog *dp_catalog, bool enable);
व्योम dp_catalog_aux_update_cfg(काष्ठा dp_catalog *dp_catalog);
पूर्णांक dp_catalog_aux_get_irq(काष्ठा dp_catalog *dp_catalog);

/* DP Controller APIs */
व्योम dp_catalog_ctrl_state_ctrl(काष्ठा dp_catalog *dp_catalog, u32 state);
व्योम dp_catalog_ctrl_config_ctrl(काष्ठा dp_catalog *dp_catalog, u32 config);
व्योम dp_catalog_ctrl_lane_mapping(काष्ठा dp_catalog *dp_catalog);
व्योम dp_catalog_ctrl_मुख्यlink_ctrl(काष्ठा dp_catalog *dp_catalog, bool enable);
व्योम dp_catalog_ctrl_config_misc(काष्ठा dp_catalog *dp_catalog, u32 cc, u32 tb);
व्योम dp_catalog_ctrl_config_msa(काष्ठा dp_catalog *dp_catalog, u32 rate,
				u32 stream_rate_khz, bool fixed_nvid);
पूर्णांक dp_catalog_ctrl_set_pattern(काष्ठा dp_catalog *dp_catalog, u32 pattern);
व्योम dp_catalog_ctrl_reset(काष्ठा dp_catalog *dp_catalog);
bool dp_catalog_ctrl_मुख्यlink_पढ़ोy(काष्ठा dp_catalog *dp_catalog);
व्योम dp_catalog_ctrl_enable_irq(काष्ठा dp_catalog *dp_catalog, bool enable);
व्योम dp_catalog_hpd_config_पूर्णांकr(काष्ठा dp_catalog *dp_catalog,
			u32 पूर्णांकr_mask, bool en);
व्योम dp_catalog_ctrl_hpd_config(काष्ठा dp_catalog *dp_catalog);
u32 dp_catalog_link_is_connected(काष्ठा dp_catalog *dp_catalog);
u32 dp_catalog_hpd_get_पूर्णांकr_status(काष्ठा dp_catalog *dp_catalog);
व्योम dp_catalog_ctrl_phy_reset(काष्ठा dp_catalog *dp_catalog);
पूर्णांक dp_catalog_ctrl_update_vx_px(काष्ठा dp_catalog *dp_catalog, u8 v_level,
				u8 p_level);
पूर्णांक dp_catalog_ctrl_get_पूर्णांकerrupt(काष्ठा dp_catalog *dp_catalog);
व्योम dp_catalog_ctrl_update_transfer_unit(काष्ठा dp_catalog *dp_catalog,
				u32 dp_tu, u32 valid_boundary,
				u32 valid_boundary2);
व्योम dp_catalog_ctrl_send_phy_pattern(काष्ठा dp_catalog *dp_catalog,
				u32 pattern);
u32 dp_catalog_ctrl_पढ़ो_phy_pattern(काष्ठा dp_catalog *dp_catalog);

/* DP Panel APIs */
पूर्णांक dp_catalog_panel_timing_cfg(काष्ठा dp_catalog *dp_catalog);
व्योम dp_catalog_dump_regs(काष्ठा dp_catalog *dp_catalog);
व्योम dp_catalog_panel_tpg_enable(काष्ठा dp_catalog *dp_catalog,
				काष्ठा drm_display_mode *drm_mode);
व्योम dp_catalog_panel_tpg_disable(काष्ठा dp_catalog *dp_catalog);

काष्ठा dp_catalog *dp_catalog_get(काष्ठा device *dev, काष्ठा dp_io *io);

/* DP Audio APIs */
व्योम dp_catalog_audio_get_header(काष्ठा dp_catalog *catalog);
व्योम dp_catalog_audio_set_header(काष्ठा dp_catalog *catalog);
व्योम dp_catalog_audio_config_acr(काष्ठा dp_catalog *catalog);
व्योम dp_catalog_audio_enable(काष्ठा dp_catalog *catalog);
व्योम dp_catalog_audio_enable(काष्ठा dp_catalog *catalog);
व्योम dp_catalog_audio_config_sdp(काष्ठा dp_catalog *catalog);
व्योम dp_catalog_audio_init(काष्ठा dp_catalog *catalog);
व्योम dp_catalog_audio_sfe_level(काष्ठा dp_catalog *catalog);

#पूर्ण_अगर /* _DP_CATALOG_H_ */
