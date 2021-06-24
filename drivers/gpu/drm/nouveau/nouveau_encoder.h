<शैली गुरु>
/*
 * Copyright (C) 2008 Maarten Maathuis.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __NOUVEAU_ENCODER_H__
#घोषणा __NOUVEAU_ENCODER_H__

#समावेश <subdev/bios/dcb.h>

#समावेश <drm/drm_encoder_slave.h>
#समावेश <drm/drm_dp_mst_helper.h>
#समावेश "dispnv04/disp.h"
काष्ठा nv50_head_atom;
काष्ठा nouveau_connector;

#घोषणा NV_DPMS_CLEARED 0x80

काष्ठा nvkm_i2c_port;

काष्ठा nouveau_encoder अणु
	काष्ठा drm_encoder_slave base;

	काष्ठा dcb_output *dcb;
	पूर्णांक or;
	पूर्णांक link;

	काष्ठा i2c_adapter *i2c;
	काष्ठा nvkm_i2c_aux *aux;

	/* dअगरferent to drm_encoder.crtc, this reflects what's
	 * actually programmed on the hw, not the proposed crtc */
	काष्ठा drm_crtc *crtc;
	u32 ctrl;

	/* Protected by nouveau_drm.audio.lock */
	काष्ठा अणु
		bool enabled;
		काष्ठा drm_connector *connector;
	पूर्ण audio;

	काष्ठा drm_display_mode mode;
	पूर्णांक last_dpms;

	काष्ठा nv04_output_reg restore;

	जोड़ अणु
		काष्ठा अणु
			काष्ठा nv50_msपंचांग *msपंचांग;
			पूर्णांक link_nr;
			पूर्णांक link_bw;

			/* Protects DP state that needs to be accessed outside
			 * connector reprobing contexts
			 */
			काष्ठा mutex hpd_irq_lock;

			u8 dpcd[DP_RECEIVER_CAP_SIZE];
			u8 करोwnstream_ports[DP_MAX_DOWNSTREAM_PORTS];
			काष्ठा drm_dp_desc desc;

			u8 sink_count;
		पूर्ण dp;
	पूर्ण;

	काष्ठा अणु
		bool dp_पूर्णांकerlace : 1;
	पूर्ण caps;

	व्योम (*enc_save)(काष्ठा drm_encoder *encoder);
	व्योम (*enc_restore)(काष्ठा drm_encoder *encoder);
	व्योम (*update)(काष्ठा nouveau_encoder *, u8 head,
		       काष्ठा nv50_head_atom *, u8 proto, u8 depth);
पूर्ण;

काष्ठा nv50_msपंचांग अणु
	काष्ठा nouveau_encoder *outp;

	काष्ठा drm_dp_mst_topology_mgr mgr;

	/* Protected under nouveau_encoder->dp.hpd_irq_lock */
	bool can_mst;
	bool is_mst;
	bool suspended;

	bool modअगरied;
	bool disabled;
	पूर्णांक links;
पूर्ण;

काष्ठा nouveau_encoder *
find_encoder(काष्ठा drm_connector *connector, पूर्णांक type);

अटल अंतरभूत काष्ठा nouveau_encoder *nouveau_encoder(काष्ठा drm_encoder *enc)
अणु
	काष्ठा drm_encoder_slave *slave = to_encoder_slave(enc);

	वापस container_of(slave, काष्ठा nouveau_encoder, base);
पूर्ण

अटल अंतरभूत काष्ठा drm_encoder *to_drm_encoder(काष्ठा nouveau_encoder *enc)
अणु
	वापस &enc->base.base;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा drm_encoder_slave_funcs *
get_slave_funcs(काष्ठा drm_encoder *enc)
अणु
	वापस to_encoder_slave(enc)->slave_funcs;
पूर्ण

/* nouveau_dp.c */
क्रमागत nouveau_dp_status अणु
	NOUVEAU_DP_NONE,
	NOUVEAU_DP_SST,
	NOUVEAU_DP_MST,
पूर्ण;

पूर्णांक nouveau_dp_detect(काष्ठा nouveau_connector *, काष्ठा nouveau_encoder *);
व्योम nouveau_dp_irq(काष्ठा nouveau_drm *drm,
		    काष्ठा nouveau_connector *nv_connector);
क्रमागत drm_mode_status nv50_dp_mode_valid(काष्ठा drm_connector *,
					काष्ठा nouveau_encoder *,
					स्थिर काष्ठा drm_display_mode *,
					अचिन्हित *घड़ी);

काष्ठा nouveau_connector *
nv50_outp_get_new_connector(काष्ठा drm_atomic_state *state, काष्ठा nouveau_encoder *outp);
काष्ठा nouveau_connector *
nv50_outp_get_old_connector(काष्ठा drm_atomic_state *state, काष्ठा nouveau_encoder *outp);

पूर्णांक nv50_msपंचांग_detect(काष्ठा nouveau_encoder *encoder);
व्योम nv50_msपंचांग_हटाओ(काष्ठा nv50_msपंचांग *msपंचांग);
bool nv50_msपंचांग_service(काष्ठा nouveau_drm *drm,
		       काष्ठा nouveau_connector *nv_connector,
		       काष्ठा nv50_msपंचांग *msपंचांग);
#पूर्ण_अगर /* __NOUVEAU_ENCODER_H__ */
