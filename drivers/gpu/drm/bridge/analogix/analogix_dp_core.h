<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Header file क्रम Analogix DP (Display Port) core पूर्णांकerface driver.
 *
 * Copyright (C) 2012 Samsung Electronics Co., Ltd.
 * Author: Jingoo Han <jg1.han@samsung.com>
 */

#अगर_अघोषित _ANALOGIX_DP_CORE_H
#घोषणा _ANALOGIX_DP_CORE_H

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_dp_helper.h>

#घोषणा DP_TIMEOUT_LOOP_COUNT 100
#घोषणा MAX_CR_LOOP 5
#घोषणा MAX_EQ_LOOP 5
#घोषणा MAX_PLL_LOCK_LOOP 5

/* Training takes 22ms अगर AUX channel comm fails. Use this as retry पूर्णांकerval */
#घोषणा DP_TIMEOUT_TRAINING_US			22000
#घोषणा DP_TIMEOUT_PSR_LOOP_MS			300

/* DP_MAX_LANE_COUNT */
#घोषणा DPCD_ENHANCED_FRAME_CAP(x)		(((x) >> 7) & 0x1)
#घोषणा DPCD_MAX_LANE_COUNT(x)			((x) & 0x1f)

/* DP_LANE_COUNT_SET */
#घोषणा DPCD_LANE_COUNT_SET(x)			((x) & 0x1f)

/* DP_TRAINING_LANE0_SET */
#घोषणा DPCD_PRE_EMPHASIS_SET(x)		(((x) & 0x3) << 3)
#घोषणा DPCD_PRE_EMPHASIS_GET(x)		(((x) >> 3) & 0x3)
#घोषणा DPCD_VOLTAGE_SWING_SET(x)		(((x) & 0x3) << 0)
#घोषणा DPCD_VOLTAGE_SWING_GET(x)		(((x) >> 0) & 0x3)

काष्ठा gpio_desc;

क्रमागत link_lane_count_type अणु
	LANE_COUNT1 = 1,
	LANE_COUNT2 = 2,
	LANE_COUNT4 = 4
पूर्ण;

क्रमागत link_training_state अणु
	START,
	CLOCK_RECOVERY,
	EQUALIZER_TRAINING,
	FINISHED,
	FAILED
पूर्ण;

क्रमागत voltage_swing_level अणु
	VOLTAGE_LEVEL_0,
	VOLTAGE_LEVEL_1,
	VOLTAGE_LEVEL_2,
	VOLTAGE_LEVEL_3,
पूर्ण;

क्रमागत pre_emphasis_level अणु
	PRE_EMPHASIS_LEVEL_0,
	PRE_EMPHASIS_LEVEL_1,
	PRE_EMPHASIS_LEVEL_2,
	PRE_EMPHASIS_LEVEL_3,
पूर्ण;

क्रमागत pattern_set अणु
	PRBS7,
	D10_2,
	TRAINING_PTN1,
	TRAINING_PTN2,
	DP_NONE
पूर्ण;

क्रमागत color_space अणु
	COLOR_RGB,
	COLOR_YCBCR422,
	COLOR_YCBCR444
पूर्ण;

क्रमागत color_depth अणु
	COLOR_6,
	COLOR_8,
	COLOR_10,
	COLOR_12
पूर्ण;

क्रमागत color_coefficient अणु
	COLOR_YCBCR601,
	COLOR_YCBCR709
पूर्ण;

क्रमागत dynamic_range अणु
	VESA,
	CEA
पूर्ण;

क्रमागत pll_status अणु
	PLL_UNLOCKED,
	PLL_LOCKED
पूर्ण;

क्रमागत घड़ी_recovery_m_value_type अणु
	CALCULATED_M,
	REGISTER_M
पूर्ण;

क्रमागत video_timing_recognition_type अणु
	VIDEO_TIMING_FROM_CAPTURE,
	VIDEO_TIMING_FROM_REGISTER
पूर्ण;

क्रमागत analog_घातer_block अणु
	AUX_BLOCK,
	CH0_BLOCK,
	CH1_BLOCK,
	CH2_BLOCK,
	CH3_BLOCK,
	ANALOG_TOTAL,
	POWER_ALL
पूर्ण;

क्रमागत dp_irq_type अणु
	DP_IRQ_TYPE_HP_CABLE_IN  = BIT(0),
	DP_IRQ_TYPE_HP_CABLE_OUT = BIT(1),
	DP_IRQ_TYPE_HP_CHANGE    = BIT(2),
	DP_IRQ_TYPE_UNKNOWN      = BIT(3),
पूर्ण;

काष्ठा video_info अणु
	अक्षर *name;

	bool h_sync_polarity;
	bool v_sync_polarity;
	bool पूर्णांकerlaced;

	क्रमागत color_space color_space;
	क्रमागत dynamic_range dynamic_range;
	क्रमागत color_coefficient ycbcr_coeff;
	क्रमागत color_depth color_depth;

	पूर्णांक max_link_rate;
	क्रमागत link_lane_count_type max_lane_count;
पूर्ण;

काष्ठा link_train अणु
	पूर्णांक eq_loop;
	पूर्णांक cr_loop[4];

	u8 link_rate;
	u8 lane_count;
	u8 training_lane[4];

	क्रमागत link_training_state lt_state;
पूर्ण;

काष्ठा analogix_dp_device अणु
	काष्ठा drm_encoder	*encoder;
	काष्ठा device		*dev;
	काष्ठा drm_device	*drm_dev;
	काष्ठा drm_connector	connector;
	काष्ठा drm_bridge	*bridge;
	काष्ठा drm_dp_aux       aux;
	काष्ठा clk		*घड़ी;
	अचिन्हित पूर्णांक		irq;
	व्योम __iomem		*reg_base;

	काष्ठा video_info	video_info;
	काष्ठा link_train	link_train;
	काष्ठा phy		*phy;
	पूर्णांक			dpms_mode;
	काष्ठा gpio_desc	*hpd_gpiod;
	bool                    क्रमce_hpd;
	bool			fast_train_enable;
	bool			psr_supported;

	काष्ठा mutex		panel_lock;
	bool			panel_is_modeset;

	काष्ठा analogix_dp_plat_data *plat_data;
पूर्ण;

/* analogix_dp_reg.c */
व्योम analogix_dp_enable_video_mute(काष्ठा analogix_dp_device *dp, bool enable);
व्योम analogix_dp_stop_video(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_lane_swap(काष्ठा analogix_dp_device *dp, bool enable);
व्योम analogix_dp_init_analog_param(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_init_पूर्णांकerrupt(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_reset(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_swreset(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_config_पूर्णांकerrupt(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_mute_hpd_पूर्णांकerrupt(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_unmute_hpd_पूर्णांकerrupt(काष्ठा analogix_dp_device *dp);
क्रमागत pll_status analogix_dp_get_pll_lock_status(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_set_pll_घातer_करोwn(काष्ठा analogix_dp_device *dp, bool enable);
व्योम analogix_dp_set_analog_घातer_करोwn(काष्ठा analogix_dp_device *dp,
				       क्रमागत analog_घातer_block block,
				       bool enable);
पूर्णांक analogix_dp_init_analog_func(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_init_hpd(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_क्रमce_hpd(काष्ठा analogix_dp_device *dp);
क्रमागत dp_irq_type analogix_dp_get_irq_type(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_clear_hotplug_पूर्णांकerrupts(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_reset_aux(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_init_aux(काष्ठा analogix_dp_device *dp);
पूर्णांक analogix_dp_get_plug_in_status(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_enable_sw_function(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_set_link_bandwidth(काष्ठा analogix_dp_device *dp, u32 bwtype);
व्योम analogix_dp_get_link_bandwidth(काष्ठा analogix_dp_device *dp, u32 *bwtype);
व्योम analogix_dp_set_lane_count(काष्ठा analogix_dp_device *dp, u32 count);
व्योम analogix_dp_get_lane_count(काष्ठा analogix_dp_device *dp, u32 *count);
व्योम analogix_dp_enable_enhanced_mode(काष्ठा analogix_dp_device *dp,
				      bool enable);
व्योम analogix_dp_set_training_pattern(काष्ठा analogix_dp_device *dp,
				      क्रमागत pattern_set pattern);
व्योम analogix_dp_set_lane0_pre_emphasis(काष्ठा analogix_dp_device *dp,
					u32 level);
व्योम analogix_dp_set_lane1_pre_emphasis(काष्ठा analogix_dp_device *dp,
					u32 level);
व्योम analogix_dp_set_lane2_pre_emphasis(काष्ठा analogix_dp_device *dp,
					u32 level);
व्योम analogix_dp_set_lane3_pre_emphasis(काष्ठा analogix_dp_device *dp,
					u32 level);
व्योम analogix_dp_set_lane0_link_training(काष्ठा analogix_dp_device *dp,
					 u32 training_lane);
व्योम analogix_dp_set_lane1_link_training(काष्ठा analogix_dp_device *dp,
					 u32 training_lane);
व्योम analogix_dp_set_lane2_link_training(काष्ठा analogix_dp_device *dp,
					 u32 training_lane);
व्योम analogix_dp_set_lane3_link_training(काष्ठा analogix_dp_device *dp,
					 u32 training_lane);
u32 analogix_dp_get_lane0_link_training(काष्ठा analogix_dp_device *dp);
u32 analogix_dp_get_lane1_link_training(काष्ठा analogix_dp_device *dp);
u32 analogix_dp_get_lane2_link_training(काष्ठा analogix_dp_device *dp);
u32 analogix_dp_get_lane3_link_training(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_reset_macro(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_init_video(काष्ठा analogix_dp_device *dp);

व्योम analogix_dp_set_video_color_क्रमmat(काष्ठा analogix_dp_device *dp);
पूर्णांक analogix_dp_is_slave_video_stream_घड़ी_on(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_set_video_cr_mn(काष्ठा analogix_dp_device *dp,
				 क्रमागत घड़ी_recovery_m_value_type type,
				 u32 m_value,
				 u32 n_value);
व्योम analogix_dp_set_video_timing_mode(काष्ठा analogix_dp_device *dp, u32 type);
व्योम analogix_dp_enable_video_master(काष्ठा analogix_dp_device *dp,
				     bool enable);
व्योम analogix_dp_start_video(काष्ठा analogix_dp_device *dp);
पूर्णांक analogix_dp_is_video_stream_on(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_config_video_slave_mode(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_enable_scrambling(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_disable_scrambling(काष्ठा analogix_dp_device *dp);
व्योम analogix_dp_enable_psr_crc(काष्ठा analogix_dp_device *dp);
पूर्णांक analogix_dp_send_psr_spd(काष्ठा analogix_dp_device *dp,
			     काष्ठा dp_sdp *vsc, bool blocking);
sमाप_प्रकार analogix_dp_transfer(काष्ठा analogix_dp_device *dp,
			     काष्ठा drm_dp_aux_msg *msg);

#पूर्ण_अगर /* _ANALOGIX_DP_CORE_H */
