<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_HDMI_H__
#घोषणा __INTEL_HDMI_H__

#समावेश <linux/hdmi.h>
#समावेश <linux/types.h>

#समावेश "i915_reg.h"

काष्ठा drm_connector;
काष्ठा drm_encoder;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_connector;
काष्ठा पूर्णांकel_digital_port;
काष्ठा पूर्णांकel_encoder;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_hdmi;
काष्ठा drm_connector_state;
जोड़ hdmi_infoframe;
क्रमागत port;

व्योम पूर्णांकel_hdmi_init_connector(काष्ठा पूर्णांकel_digital_port *dig_port,
			       काष्ठा पूर्णांकel_connector *पूर्णांकel_connector);
पूर्णांक पूर्णांकel_hdmi_compute_config(काष्ठा पूर्णांकel_encoder *encoder,
			      काष्ठा पूर्णांकel_crtc_state *pipe_config,
			      काष्ठा drm_connector_state *conn_state);
bool पूर्णांकel_hdmi_handle_sink_scrambling(काष्ठा पूर्णांकel_encoder *encoder,
				       काष्ठा drm_connector *connector,
				       bool high_पंचांगds_घड़ी_ratio,
				       bool scrambling);
व्योम पूर्णांकel_dp_dual_mode_set_पंचांगds_output(काष्ठा पूर्णांकel_hdmi *hdmi, bool enable);
व्योम पूर्णांकel_infoframe_init(काष्ठा पूर्णांकel_digital_port *dig_port);
u32 पूर्णांकel_hdmi_infoframes_enabled(काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
u32 पूर्णांकel_hdmi_infoframe_enable(अचिन्हित पूर्णांक type);
व्योम पूर्णांकel_hdmi_पढ़ो_gcp_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
				   काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_पढ़ो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
			  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			  क्रमागत hdmi_infoframe_type type,
			  जोड़ hdmi_infoframe *frame);
bool पूर्णांकel_hdmi_limited_color_range(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    स्थिर काष्ठा drm_connector_state *conn_state);
bool पूर्णांकel_hdmi_deep_color_possible(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state, पूर्णांक bpc,
				    bool has_hdmi_sink, bool ycbcr420_output);
पूर्णांक पूर्णांकel_hdmi_dsc_get_bpp(पूर्णांक src_fractional_bpp, पूर्णांक slice_width,
			   पूर्णांक num_slices, पूर्णांक output_क्रमmat, bool hdmi_all_bpp,
			   पूर्णांक hdmi_max_chunk_bytes);
पूर्णांक पूर्णांकel_hdmi_dsc_get_num_slices(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  पूर्णांक src_max_slices, पूर्णांक src_max_slice_width,
				  पूर्णांक hdmi_max_slices, पूर्णांक hdmi_throughput);
पूर्णांक पूर्णांकel_hdmi_dsc_get_slice_height(पूर्णांक vactive);

#पूर्ण_अगर /* __INTEL_HDMI_H__ */
