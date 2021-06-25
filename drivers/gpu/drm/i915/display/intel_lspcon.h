<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_LSPCON_H__
#घोषणा __INTEL_LSPCON_H__

#समावेश <linux/types.h>

काष्ठा drm_connector;
काष्ठा drm_connector_state;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_digital_port;
काष्ठा पूर्णांकel_encoder;
काष्ठा पूर्णांकel_lspcon;

bool lspcon_init(काष्ठा पूर्णांकel_digital_port *dig_port);
व्योम lspcon_detect_hdr_capability(काष्ठा पूर्णांकel_lspcon *lspcon);
व्योम lspcon_resume(काष्ठा पूर्णांकel_digital_port *dig_port);
व्योम lspcon_रुको_pcon_mode(काष्ठा पूर्णांकel_lspcon *lspcon);
व्योम lspcon_ग_लिखो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    अचिन्हित पूर्णांक type,
			    स्थिर व्योम *buf, sमाप_प्रकार len);
व्योम lspcon_पढ़ो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   अचिन्हित पूर्णांक type,
			   व्योम *frame, sमाप_प्रकार len);
व्योम lspcon_set_infoframes(काष्ठा पूर्णांकel_encoder *encoder,
			   bool enable,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   स्थिर काष्ठा drm_connector_state *conn_state);
u32 lspcon_infoframes_enabled(काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config);
u32 पूर्णांकel_lspcon_infoframes_enabled(काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config);
व्योम hsw_ग_लिखो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
			 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			 अचिन्हित पूर्णांक type,
			 स्थिर व्योम *frame, sमाप_प्रकार len);
व्योम hsw_पढ़ो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			अचिन्हित पूर्णांक type,
			व्योम *frame, sमाप_प्रकार len);

#पूर्ण_अगर /* __INTEL_LSPCON_H__ */
