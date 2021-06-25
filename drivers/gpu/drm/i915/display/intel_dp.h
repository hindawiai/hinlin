<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_DP_H__
#घोषणा __INTEL_DP_H__

#समावेश <linux/types.h>

#समावेश "i915_reg.h"

क्रमागत पूर्णांकel_output_क्रमmat;
क्रमागत pipe;
क्रमागत port;
काष्ठा drm_connector_state;
काष्ठा drm_encoder;
काष्ठा drm_i915_निजी;
काष्ठा drm_modeset_acquire_ctx;
काष्ठा drm_dp_vsc_sdp;
काष्ठा पूर्णांकel_atomic_state;
काष्ठा पूर्णांकel_connector;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_digital_port;
काष्ठा पूर्णांकel_dp;
काष्ठा पूर्णांकel_encoder;

काष्ठा link_config_limits अणु
	पूर्णांक min_घड़ी, max_घड़ी;
	पूर्णांक min_lane_count, max_lane_count;
	पूर्णांक min_bpp, max_bpp;
पूर्ण;

व्योम पूर्णांकel_dp_adjust_compliance_config(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				       काष्ठा पूर्णांकel_crtc_state *pipe_config,
				       काष्ठा link_config_limits *limits);
bool पूर्णांकel_dp_limited_color_range(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  स्थिर काष्ठा drm_connector_state *conn_state);
पूर्णांक पूर्णांकel_dp_min_bpp(क्रमागत पूर्णांकel_output_क्रमmat output_क्रमmat);
bool पूर्णांकel_dp_init_connector(काष्ठा पूर्णांकel_digital_port *dig_port,
			     काष्ठा पूर्णांकel_connector *पूर्णांकel_connector);
व्योम पूर्णांकel_dp_set_link_params(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			      पूर्णांक link_rate, पूर्णांक lane_count);
पूर्णांक पूर्णांकel_dp_get_link_train_fallback_values(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					    पूर्णांक link_rate, u8 lane_count);
पूर्णांक पूर्णांकel_dp_retrain_link(काष्ठा पूर्णांकel_encoder *encoder,
			  काष्ठा drm_modeset_acquire_ctx *ctx);
व्योम पूर्णांकel_dp_set_घातer(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, u8 mode);
व्योम पूर्णांकel_dp_configure_protocol_converter(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_dp_sink_set_decompression_state(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					   bool enable);
व्योम पूर्णांकel_dp_encoder_suspend(काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder);
व्योम पूर्णांकel_dp_encoder_shutकरोwn(काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder);
व्योम पूर्णांकel_dp_encoder_flush_work(काष्ठा drm_encoder *encoder);
पूर्णांक पूर्णांकel_dp_compute_config(काष्ठा पूर्णांकel_encoder *encoder,
			    काष्ठा पूर्णांकel_crtc_state *pipe_config,
			    काष्ठा drm_connector_state *conn_state);
bool पूर्णांकel_dp_is_edp(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
bool पूर्णांकel_dp_is_port_edp(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port);
क्रमागत irqवापस पूर्णांकel_dp_hpd_pulse(काष्ठा पूर्णांकel_digital_port *dig_port,
				  bool दीर्घ_hpd);
व्योम पूर्णांकel_edp_backlight_on(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    स्थिर काष्ठा drm_connector_state *conn_state);
व्योम पूर्णांकel_edp_backlight_off(स्थिर काष्ठा drm_connector_state *conn_state);
व्योम पूर्णांकel_dp_mst_suspend(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_dp_mst_resume(काष्ठा drm_i915_निजी *dev_priv);
पूर्णांक पूर्णांकel_dp_max_link_rate(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
पूर्णांक पूर्णांकel_dp_max_lane_count(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
पूर्णांक पूर्णांकel_dp_rate_select(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, पूर्णांक rate);

व्योम पूर्णांकel_edp_drrs_enable(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_edp_drrs_disable(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_edp_drrs_update(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_edp_drrs_invalidate(काष्ठा drm_i915_निजी *dev_priv,
			       अचिन्हित पूर्णांक frontbuffer_bits);
व्योम पूर्णांकel_edp_drrs_flush(काष्ठा drm_i915_निजी *dev_priv,
			  अचिन्हित पूर्णांक frontbuffer_bits);

व्योम पूर्णांकel_dp_compute_rate(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, पूर्णांक port_घड़ी,
			   u8 *link_bw, u8 *rate_select);
bool पूर्णांकel_dp_source_supports_hbr2(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
bool पूर्णांकel_dp_source_supports_hbr3(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);

bool पूर्णांकel_dp_get_colorimetry_status(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
पूर्णांक पूर्णांकel_dp_link_required(पूर्णांक pixel_घड़ी, पूर्णांक bpp);
पूर्णांक पूर्णांकel_dp_max_data_rate(पूर्णांक max_link_घड़ी, पूर्णांक max_lanes);
bool पूर्णांकel_dp_can_bigjoiner(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
bool पूर्णांकel_dp_needs_vsc_sdp(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    स्थिर काष्ठा drm_connector_state *conn_state);
व्योम पूर्णांकel_dp_compute_psr_vsc_sdp(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  स्थिर काष्ठा drm_connector_state *conn_state,
				  काष्ठा drm_dp_vsc_sdp *vsc);
व्योम पूर्णांकel_ग_लिखो_dp_vsc_sdp(काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    काष्ठा drm_dp_vsc_sdp *vsc);
व्योम पूर्णांकel_dp_set_infoframes(काष्ठा पूर्णांकel_encoder *encoder, bool enable,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     स्थिर काष्ठा drm_connector_state *conn_state);
व्योम पूर्णांकel_पढ़ो_dp_sdp(काष्ठा पूर्णांकel_encoder *encoder,
		       काष्ठा पूर्णांकel_crtc_state *crtc_state,
		       अचिन्हित पूर्णांक type);
bool पूर्णांकel_digital_port_connected(काष्ठा पूर्णांकel_encoder *encoder);

अटल अंतरभूत अचिन्हित पूर्णांक पूर्णांकel_dp_unused_lane_mask(पूर्णांक lane_count)
अणु
	वापस ~((1 << lane_count) - 1) & 0xf;
पूर्ण

u32 पूर्णांकel_dp_mode_to_fec_घड़ी(u32 mode_घड़ी);

व्योम पूर्णांकel_ddi_update_pipe(काष्ठा पूर्णांकel_atomic_state *state,
			   काष्ठा पूर्णांकel_encoder *encoder,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   स्थिर काष्ठा drm_connector_state *conn_state);

पूर्णांक पूर्णांकel_dp_init_hdcp(काष्ठा पूर्णांकel_digital_port *dig_port,
		       काष्ठा पूर्णांकel_connector *पूर्णांकel_connector);

bool पूर्णांकel_dp_initial_fastset_check(काष्ठा पूर्णांकel_encoder *encoder,
				    काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_dp_sync_state(काष्ठा पूर्णांकel_encoder *encoder,
			 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);

व्योम पूर्णांकel_dp_check_frl_training(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
व्योम पूर्णांकel_dp_pcon_dsc_configure(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_dp_phy_test(काष्ठा पूर्णांकel_encoder *encoder);

#पूर्ण_अगर /* __INTEL_DP_H__ */
