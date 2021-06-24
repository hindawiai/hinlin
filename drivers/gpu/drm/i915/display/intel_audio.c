<शैली गुरु>
/*
 * Copyright तऊ 2014 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/component.h>
#समावेश <linux/kernel.h>

#समावेश <drm/drm_edid.h>
#समावेश <drm/i915_component.h>

#समावेश "i915_drv.h"
#समावेश "intel_atomic.h"
#समावेश "intel_audio.h"
#समावेश "intel_cdclk.h"
#समावेश "intel_display_types.h"
#समावेश "intel_lpe_audio.h"

/**
 * DOC: High Definition Audio over HDMI and Display Port
 *
 * The graphics and audio drivers together support High Definition Audio over
 * HDMI and Display Port. The audio programming sequences are भागided पूर्णांकo audio
 * codec and controller enable and disable sequences. The graphics driver
 * handles the audio codec sequences, जबतक the audio driver handles the audio
 * controller sequences.
 *
 * The disable sequences must be perक्रमmed beक्रमe disabling the transcoder or
 * port. The enable sequences may only be perक्रमmed after enabling the
 * transcoder and port, and after completed link training. Thereक्रमe the audio
 * enable/disable sequences are part of the modeset sequence.
 *
 * The codec and controller sequences could be करोne either parallel or serial,
 * but generally the ELDV/PD change in the codec sequence indicates to the audio
 * driver that the controller sequence should start. Indeed, most of the
 * co-operation between the graphics and audio drivers is handled via audio
 * related रेजिस्टरs. (The notable exception is the घातer management, not
 * covered here.)
 *
 * The काष्ठा &i915_audio_component is used to पूर्णांकeract between the graphics
 * and audio drivers. The काष्ठा &i915_audio_component_ops @ops in it is
 * defined in graphics driver and called in audio driver. The
 * काष्ठा &i915_audio_component_audio_ops @audio_ops is called from i915 driver.
 */

/* DP N/M table */
#घोषणा LC_810M	810000
#घोषणा LC_540M	540000
#घोषणा LC_270M	270000
#घोषणा LC_162M	162000

काष्ठा dp_aud_n_m अणु
	पूर्णांक sample_rate;
	पूर्णांक घड़ी;
	u16 m;
	u16 n;
पूर्ण;

काष्ठा hdmi_aud_ncts अणु
	पूर्णांक sample_rate;
	पूर्णांक घड़ी;
	पूर्णांक n;
	पूर्णांक cts;
पूर्ण;

/* Values according to DP 1.4 Table 2-104 */
अटल स्थिर काष्ठा dp_aud_n_m dp_aud_n_m[] = अणु
	अणु 32000, LC_162M, 1024, 10125 पूर्ण,
	अणु 44100, LC_162M, 784, 5625 पूर्ण,
	अणु 48000, LC_162M, 512, 3375 पूर्ण,
	अणु 64000, LC_162M, 2048, 10125 पूर्ण,
	अणु 88200, LC_162M, 1568, 5625 पूर्ण,
	अणु 96000, LC_162M, 1024, 3375 पूर्ण,
	अणु 128000, LC_162M, 4096, 10125 पूर्ण,
	अणु 176400, LC_162M, 3136, 5625 पूर्ण,
	अणु 192000, LC_162M, 2048, 3375 पूर्ण,
	अणु 32000, LC_270M, 1024, 16875 पूर्ण,
	अणु 44100, LC_270M, 784, 9375 पूर्ण,
	अणु 48000, LC_270M, 512, 5625 पूर्ण,
	अणु 64000, LC_270M, 2048, 16875 पूर्ण,
	अणु 88200, LC_270M, 1568, 9375 पूर्ण,
	अणु 96000, LC_270M, 1024, 5625 पूर्ण,
	अणु 128000, LC_270M, 4096, 16875 पूर्ण,
	अणु 176400, LC_270M, 3136, 9375 पूर्ण,
	अणु 192000, LC_270M, 2048, 5625 पूर्ण,
	अणु 32000, LC_540M, 1024, 33750 पूर्ण,
	अणु 44100, LC_540M, 784, 18750 पूर्ण,
	अणु 48000, LC_540M, 512, 11250 पूर्ण,
	अणु 64000, LC_540M, 2048, 33750 पूर्ण,
	अणु 88200, LC_540M, 1568, 18750 पूर्ण,
	अणु 96000, LC_540M, 1024, 11250 पूर्ण,
	अणु 128000, LC_540M, 4096, 33750 पूर्ण,
	अणु 176400, LC_540M, 3136, 18750 पूर्ण,
	अणु 192000, LC_540M, 2048, 11250 पूर्ण,
	अणु 32000, LC_810M, 1024, 50625 पूर्ण,
	अणु 44100, LC_810M, 784, 28125 पूर्ण,
	अणु 48000, LC_810M, 512, 16875 पूर्ण,
	अणु 64000, LC_810M, 2048, 50625 पूर्ण,
	अणु 88200, LC_810M, 1568, 28125 पूर्ण,
	अणु 96000, LC_810M, 1024, 16875 पूर्ण,
	अणु 128000, LC_810M, 4096, 50625 पूर्ण,
	अणु 176400, LC_810M, 3136, 28125 पूर्ण,
	अणु 192000, LC_810M, 2048, 16875 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dp_aud_n_m *
audio_config_dp_get_n_m(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state, पूर्णांक rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dp_aud_n_m); i++) अणु
		अगर (rate == dp_aud_n_m[i].sample_rate &&
		    crtc_state->port_घड़ी == dp_aud_n_m[i].घड़ी)
			वापस &dp_aud_n_m[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा अणु
	पूर्णांक घड़ी;
	u32 config;
पूर्ण hdmi_audio_घड़ी[] = अणु
	अणु 25175, AUD_CONFIG_PIXEL_CLOCK_HDMI_25175 पूर्ण,
	अणु 25200, AUD_CONFIG_PIXEL_CLOCK_HDMI_25200 पूर्ण, /* शेष per bspec */
	अणु 27000, AUD_CONFIG_PIXEL_CLOCK_HDMI_27000 पूर्ण,
	अणु 27027, AUD_CONFIG_PIXEL_CLOCK_HDMI_27027 पूर्ण,
	अणु 54000, AUD_CONFIG_PIXEL_CLOCK_HDMI_54000 पूर्ण,
	अणु 54054, AUD_CONFIG_PIXEL_CLOCK_HDMI_54054 पूर्ण,
	अणु 74176, AUD_CONFIG_PIXEL_CLOCK_HDMI_74176 पूर्ण,
	अणु 74250, AUD_CONFIG_PIXEL_CLOCK_HDMI_74250 पूर्ण,
	अणु 148352, AUD_CONFIG_PIXEL_CLOCK_HDMI_148352 पूर्ण,
	अणु 148500, AUD_CONFIG_PIXEL_CLOCK_HDMI_148500 पूर्ण,
	अणु 296703, AUD_CONFIG_PIXEL_CLOCK_HDMI_296703 पूर्ण,
	अणु 297000, AUD_CONFIG_PIXEL_CLOCK_HDMI_297000 पूर्ण,
	अणु 593407, AUD_CONFIG_PIXEL_CLOCK_HDMI_593407 पूर्ण,
	अणु 594000, AUD_CONFIG_PIXEL_CLOCK_HDMI_594000 पूर्ण,
पूर्ण;

/* HDMI N/CTS table */
#घोषणा TMDS_297M 297000
#घोषणा TMDS_296M 296703
#घोषणा TMDS_594M 594000
#घोषणा TMDS_593M 593407

अटल स्थिर काष्ठा hdmi_aud_ncts hdmi_aud_ncts_24bpp[] = अणु
	अणु 32000, TMDS_296M, 5824, 421875 पूर्ण,
	अणु 32000, TMDS_297M, 3072, 222750 पूर्ण,
	अणु 32000, TMDS_593M, 5824, 843750 पूर्ण,
	अणु 32000, TMDS_594M, 3072, 445500 पूर्ण,
	अणु 44100, TMDS_296M, 4459, 234375 पूर्ण,
	अणु 44100, TMDS_297M, 4704, 247500 पूर्ण,
	अणु 44100, TMDS_593M, 8918, 937500 पूर्ण,
	अणु 44100, TMDS_594M, 9408, 990000 पूर्ण,
	अणु 88200, TMDS_296M, 8918, 234375 पूर्ण,
	अणु 88200, TMDS_297M, 9408, 247500 पूर्ण,
	अणु 88200, TMDS_593M, 17836, 937500 पूर्ण,
	अणु 88200, TMDS_594M, 18816, 990000 पूर्ण,
	अणु 176400, TMDS_296M, 17836, 234375 पूर्ण,
	अणु 176400, TMDS_297M, 18816, 247500 पूर्ण,
	अणु 176400, TMDS_593M, 35672, 937500 पूर्ण,
	अणु 176400, TMDS_594M, 37632, 990000 पूर्ण,
	अणु 48000, TMDS_296M, 5824, 281250 पूर्ण,
	अणु 48000, TMDS_297M, 5120, 247500 पूर्ण,
	अणु 48000, TMDS_593M, 5824, 562500 पूर्ण,
	अणु 48000, TMDS_594M, 6144, 594000 पूर्ण,
	अणु 96000, TMDS_296M, 11648, 281250 पूर्ण,
	अणु 96000, TMDS_297M, 10240, 247500 पूर्ण,
	अणु 96000, TMDS_593M, 11648, 562500 पूर्ण,
	अणु 96000, TMDS_594M, 12288, 594000 पूर्ण,
	अणु 192000, TMDS_296M, 23296, 281250 पूर्ण,
	अणु 192000, TMDS_297M, 20480, 247500 पूर्ण,
	अणु 192000, TMDS_593M, 23296, 562500 पूर्ण,
	अणु 192000, TMDS_594M, 24576, 594000 पूर्ण,
पूर्ण;

/* Appendix C - N & CTS values क्रम deep color from HDMI 2.0 spec*/
/* HDMI N/CTS table क्रम 10 bit deep color(30 bpp)*/
#घोषणा TMDS_371M 371250
#घोषणा TMDS_370M 370878

अटल स्थिर काष्ठा hdmi_aud_ncts hdmi_aud_ncts_30bpp[] = अणु
	अणु 32000, TMDS_370M, 5824, 527344 पूर्ण,
	अणु 32000, TMDS_371M, 6144, 556875 पूर्ण,
	अणु 44100, TMDS_370M, 8918, 585938 पूर्ण,
	अणु 44100, TMDS_371M, 4704, 309375 पूर्ण,
	अणु 88200, TMDS_370M, 17836, 585938 पूर्ण,
	अणु 88200, TMDS_371M, 9408, 309375 पूर्ण,
	अणु 176400, TMDS_370M, 35672, 585938 पूर्ण,
	अणु 176400, TMDS_371M, 18816, 309375 पूर्ण,
	अणु 48000, TMDS_370M, 11648, 703125 पूर्ण,
	अणु 48000, TMDS_371M, 5120, 309375 पूर्ण,
	अणु 96000, TMDS_370M, 23296, 703125 पूर्ण,
	अणु 96000, TMDS_371M, 10240, 309375 पूर्ण,
	अणु 192000, TMDS_370M, 46592, 703125 पूर्ण,
	अणु 192000, TMDS_371M, 20480, 309375 पूर्ण,
पूर्ण;

/* HDMI N/CTS table क्रम 12 bit deep color(36 bpp)*/
#घोषणा TMDS_445_5M 445500
#घोषणा TMDS_445M 445054

अटल स्थिर काष्ठा hdmi_aud_ncts hdmi_aud_ncts_36bpp[] = अणु
	अणु 32000, TMDS_445M, 5824, 632813 पूर्ण,
	अणु 32000, TMDS_445_5M, 4096, 445500 पूर्ण,
	अणु 44100, TMDS_445M, 8918, 703125 पूर्ण,
	अणु 44100, TMDS_445_5M, 4704, 371250 पूर्ण,
	अणु 88200, TMDS_445M, 17836, 703125 पूर्ण,
	अणु 88200, TMDS_445_5M, 9408, 371250 पूर्ण,
	अणु 176400, TMDS_445M, 35672, 703125 पूर्ण,
	अणु 176400, TMDS_445_5M, 18816, 371250 पूर्ण,
	अणु 48000, TMDS_445M, 5824, 421875 पूर्ण,
	अणु 48000, TMDS_445_5M, 5120, 371250 पूर्ण,
	अणु 96000, TMDS_445M, 11648, 421875 पूर्ण,
	अणु 96000, TMDS_445_5M, 10240, 371250 पूर्ण,
	अणु 192000, TMDS_445M, 23296, 421875 पूर्ण,
	अणु 192000, TMDS_445_5M, 20480, 371250 पूर्ण,
पूर्ण;

/* get AUD_CONFIG_PIXEL_CLOCK_HDMI_* value क्रम mode */
अटल u32 audio_config_hdmi_pixel_घड़ी(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hdmi_audio_घड़ी); i++) अणु
		अगर (adjusted_mode->crtc_घड़ी == hdmi_audio_घड़ी[i].घड़ी)
			अवरोध;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) < 12 && adjusted_mode->crtc_घड़ी > 148500)
		i = ARRAY_SIZE(hdmi_audio_घड़ी);

	अगर (i == ARRAY_SIZE(hdmi_audio_घड़ी)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "HDMI audio pixel clock setting for %d not found, falling back to defaults\n",
			    adjusted_mode->crtc_घड़ी);
		i = 1;
	पूर्ण

	drm_dbg_kms(&dev_priv->drm,
		    "Configuring HDMI audio for pixel clock %d (0x%08x)\n",
		    hdmi_audio_घड़ी[i].घड़ी,
		    hdmi_audio_घड़ी[i].config);

	वापस hdmi_audio_घड़ी[i].config;
पूर्ण

अटल पूर्णांक audio_config_hdmi_get_n(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				   पूर्णांक rate)
अणु
	स्थिर काष्ठा hdmi_aud_ncts *hdmi_ncts_table;
	पूर्णांक i, size;

	अगर (crtc_state->pipe_bpp == 36) अणु
		hdmi_ncts_table = hdmi_aud_ncts_36bpp;
		size = ARRAY_SIZE(hdmi_aud_ncts_36bpp);
	पूर्ण अन्यथा अगर (crtc_state->pipe_bpp == 30) अणु
		hdmi_ncts_table = hdmi_aud_ncts_30bpp;
		size = ARRAY_SIZE(hdmi_aud_ncts_30bpp);
	पूर्ण अन्यथा अणु
		hdmi_ncts_table = hdmi_aud_ncts_24bpp;
		size = ARRAY_SIZE(hdmi_aud_ncts_24bpp);
	पूर्ण

	क्रम (i = 0; i < size; i++) अणु
		अगर (rate == hdmi_ncts_table[i].sample_rate &&
		    crtc_state->port_घड़ी == hdmi_ncts_table[i].घड़ी) अणु
			वापस hdmi_ncts_table[i].n;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल bool पूर्णांकel_eld_uptodate(काष्ठा drm_connector *connector,
			       i915_reg_t reg_eldv, u32 bits_eldv,
			       i915_reg_t reg_elda, u32 bits_elda,
			       i915_reg_t reg_edid)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);
	स्थिर u8 *eld = connector->eld;
	u32 पंचांगp;
	पूर्णांक i;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, reg_eldv);
	पंचांगp &= bits_eldv;

	अगर (!पंचांगp)
		वापस false;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, reg_elda);
	पंचांगp &= ~bits_elda;
	पूर्णांकel_de_ग_लिखो(dev_priv, reg_elda, पंचांगp);

	क्रम (i = 0; i < drm_eld_size(eld) / 4; i++)
		अगर (पूर्णांकel_de_पढ़ो(dev_priv, reg_edid) != *((स्थिर u32 *)eld + i))
			वापस false;

	वापस true;
पूर्ण

अटल व्योम g4x_audio_codec_disable(काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				    स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 eldv, पंचांगp;

	drm_dbg_kms(&dev_priv->drm, "Disable audio codec\n");

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, G4X_AUD_VID_DID);
	अगर (पंचांगp == INTEL_AUDIO_DEVBLC || पंचांगp == INTEL_AUDIO_DEVCL)
		eldv = G4X_ELDV_DEVCL_DEVBLC;
	अन्यथा
		eldv = G4X_ELDV_DEVCTG;

	/* Invalidate ELD */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, G4X_AUD_CNTL_ST);
	पंचांगp &= ~eldv;
	पूर्णांकel_de_ग_लिखो(dev_priv, G4X_AUD_CNTL_ST, पंचांगp);
पूर्ण

अटल व्योम g4x_audio_codec_enable(काष्ठा पूर्णांकel_encoder *encoder,
				   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				   स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा drm_connector *connector = conn_state->connector;
	स्थिर u8 *eld = connector->eld;
	u32 eldv;
	u32 पंचांगp;
	पूर्णांक len, i;

	drm_dbg_kms(&dev_priv->drm, "Enable audio codec, %u bytes ELD\n",
		    drm_eld_size(eld));

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, G4X_AUD_VID_DID);
	अगर (पंचांगp == INTEL_AUDIO_DEVBLC || पंचांगp == INTEL_AUDIO_DEVCL)
		eldv = G4X_ELDV_DEVCL_DEVBLC;
	अन्यथा
		eldv = G4X_ELDV_DEVCTG;

	अगर (पूर्णांकel_eld_uptodate(connector,
			       G4X_AUD_CNTL_ST, eldv,
			       G4X_AUD_CNTL_ST, G4X_ELD_ADDR_MASK,
			       G4X_HDMIW_HDMIEDID))
		वापस;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, G4X_AUD_CNTL_ST);
	पंचांगp &= ~(eldv | G4X_ELD_ADDR_MASK);
	len = (पंचांगp >> 9) & 0x1f;		/* ELD buffer size */
	पूर्णांकel_de_ग_लिखो(dev_priv, G4X_AUD_CNTL_ST, पंचांगp);

	len = min(drm_eld_size(eld) / 4, len);
	drm_dbg(&dev_priv->drm, "ELD size %d\n", len);
	क्रम (i = 0; i < len; i++)
		पूर्णांकel_de_ग_लिखो(dev_priv, G4X_HDMIW_HDMIEDID,
			       *((स्थिर u32 *)eld + i));

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, G4X_AUD_CNTL_ST);
	पंचांगp |= eldv;
	पूर्णांकel_de_ग_लिखो(dev_priv, G4X_AUD_CNTL_ST, पंचांगp);
पूर्ण

अटल व्योम
hsw_dp_audio_config_update(काष्ठा पूर्णांकel_encoder *encoder,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा i915_audio_component *acomp = dev_priv->audio_component;
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	क्रमागत port port = encoder->port;
	स्थिर काष्ठा dp_aud_n_m *nm;
	पूर्णांक rate;
	u32 पंचांगp;

	rate = acomp ? acomp->aud_sample_rate[port] : 0;
	nm = audio_config_dp_get_n_m(crtc_state, rate);
	अगर (nm)
		drm_dbg_kms(&dev_priv->drm, "using Maud %u, Naud %u\n", nm->m,
			    nm->n);
	अन्यथा
		drm_dbg_kms(&dev_priv->drm, "using automatic Maud, Naud\n");

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, HSW_AUD_CFG(cpu_transcoder));
	पंचांगp &= ~AUD_CONFIG_N_VALUE_INDEX;
	पंचांगp &= ~AUD_CONFIG_PIXEL_CLOCK_HDMI_MASK;
	पंचांगp &= ~AUD_CONFIG_N_PROG_ENABLE;
	पंचांगp |= AUD_CONFIG_N_VALUE_INDEX;

	अगर (nm) अणु
		पंचांगp &= ~AUD_CONFIG_N_MASK;
		पंचांगp |= AUD_CONFIG_N(nm->n);
		पंचांगp |= AUD_CONFIG_N_PROG_ENABLE;
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, HSW_AUD_CFG(cpu_transcoder), पंचांगp);

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, HSW_AUD_M_CTS_ENABLE(cpu_transcoder));
	पंचांगp &= ~AUD_CONFIG_M_MASK;
	पंचांगp &= ~AUD_M_CTS_M_VALUE_INDEX;
	पंचांगp &= ~AUD_M_CTS_M_PROG_ENABLE;

	अगर (nm) अणु
		पंचांगp |= nm->m;
		पंचांगp |= AUD_M_CTS_M_VALUE_INDEX;
		पंचांगp |= AUD_M_CTS_M_PROG_ENABLE;
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, HSW_AUD_M_CTS_ENABLE(cpu_transcoder), पंचांगp);
पूर्ण

अटल व्योम
hsw_hdmi_audio_config_update(काष्ठा पूर्णांकel_encoder *encoder,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा i915_audio_component *acomp = dev_priv->audio_component;
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	क्रमागत port port = encoder->port;
	पूर्णांक n, rate;
	u32 पंचांगp;

	rate = acomp ? acomp->aud_sample_rate[port] : 0;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, HSW_AUD_CFG(cpu_transcoder));
	पंचांगp &= ~AUD_CONFIG_N_VALUE_INDEX;
	पंचांगp &= ~AUD_CONFIG_PIXEL_CLOCK_HDMI_MASK;
	पंचांगp &= ~AUD_CONFIG_N_PROG_ENABLE;
	पंचांगp |= audio_config_hdmi_pixel_घड़ी(crtc_state);

	n = audio_config_hdmi_get_n(crtc_state, rate);
	अगर (n != 0) अणु
		drm_dbg_kms(&dev_priv->drm, "using N %d\n", n);

		पंचांगp &= ~AUD_CONFIG_N_MASK;
		पंचांगp |= AUD_CONFIG_N(n);
		पंचांगp |= AUD_CONFIG_N_PROG_ENABLE;
	पूर्ण अन्यथा अणु
		drm_dbg_kms(&dev_priv->drm, "using automatic N\n");
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, HSW_AUD_CFG(cpu_transcoder), पंचांगp);

	/*
	 * Let's disable "Enable CTS or M Prog bit"
	 * and let HW calculate the value
	 */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, HSW_AUD_M_CTS_ENABLE(cpu_transcoder));
	पंचांगp &= ~AUD_M_CTS_M_PROG_ENABLE;
	पंचांगp &= ~AUD_M_CTS_M_VALUE_INDEX;
	पूर्णांकel_de_ग_लिखो(dev_priv, HSW_AUD_M_CTS_ENABLE(cpu_transcoder), पंचांगp);
पूर्ण

अटल व्योम
hsw_audio_config_update(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (पूर्णांकel_crtc_has_dp_encoder(crtc_state))
		hsw_dp_audio_config_update(encoder, crtc_state);
	अन्यथा
		hsw_hdmi_audio_config_update(encoder, crtc_state);
पूर्ण

अटल व्योम hsw_audio_codec_disable(काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				    स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत transcoder cpu_transcoder = old_crtc_state->cpu_transcoder;
	u32 पंचांगp;

	drm_dbg_kms(&dev_priv->drm, "Disable audio codec on transcoder %s\n",
		    transcoder_name(cpu_transcoder));

	mutex_lock(&dev_priv->av_mutex);

	/* Disable बारtamps */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, HSW_AUD_CFG(cpu_transcoder));
	पंचांगp &= ~AUD_CONFIG_N_VALUE_INDEX;
	पंचांगp |= AUD_CONFIG_N_PROG_ENABLE;
	पंचांगp &= ~AUD_CONFIG_UPPER_N_MASK;
	पंचांगp &= ~AUD_CONFIG_LOWER_N_MASK;
	अगर (पूर्णांकel_crtc_has_dp_encoder(old_crtc_state))
		पंचांगp |= AUD_CONFIG_N_VALUE_INDEX;
	पूर्णांकel_de_ग_लिखो(dev_priv, HSW_AUD_CFG(cpu_transcoder), पंचांगp);

	/* Invalidate ELD */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, HSW_AUD_PIN_ELD_CP_VLD);
	पंचांगp &= ~AUDIO_ELD_VALID(cpu_transcoder);
	पंचांगp &= ~AUDIO_OUTPUT_ENABLE(cpu_transcoder);
	पूर्णांकel_de_ग_लिखो(dev_priv, HSW_AUD_PIN_ELD_CP_VLD, पंचांगp);

	mutex_unlock(&dev_priv->av_mutex);
पूर्ण

अटल अचिन्हित पूर्णांक calc_hblank_early_prog(काष्ठा पूर्णांकel_encoder *encoder,
					   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	अचिन्हित पूर्णांक link_clks_available, link_clks_required;
	अचिन्हित पूर्णांक tu_data, tu_line, link_clks_active;
	अचिन्हित पूर्णांक h_active, h_total, hblank_delta, pixel_clk;
	अचिन्हित पूर्णांक fec_coeff, cdclk, vdsc_bpp;
	अचिन्हित पूर्णांक link_clk, lanes;
	अचिन्हित पूर्णांक hblank_rise;

	h_active = crtc_state->hw.adjusted_mode.crtc_hdisplay;
	h_total = crtc_state->hw.adjusted_mode.crtc_htotal;
	pixel_clk = crtc_state->hw.adjusted_mode.crtc_घड़ी;
	vdsc_bpp = crtc_state->dsc.compressed_bpp;
	cdclk = i915->cdclk.hw.cdclk;
	/* fec= 0.972261, using rounding multiplier of 1000000 */
	fec_coeff = 972261;
	link_clk = crtc_state->port_घड़ी;
	lanes = crtc_state->lane_count;

	drm_dbg_kms(&i915->drm, "h_active = %u link_clk = %u :"
		    "lanes = %u vdsc_bpp = %u cdclk = %u\n",
		    h_active, link_clk, lanes, vdsc_bpp, cdclk);

	अगर (WARN_ON(!link_clk || !pixel_clk || !lanes || !vdsc_bpp || !cdclk))
		वापस 0;

	link_clks_available = (h_total - h_active) * link_clk / pixel_clk - 28;
	link_clks_required = DIV_ROUND_UP(192000 * h_total, 1000 * pixel_clk) * (48 / lanes + 2);

	अगर (link_clks_available > link_clks_required)
		hblank_delta = 32;
	अन्यथा
		hblank_delta = DIV64_U64_ROUND_UP(mul_u32_u32(5 * (link_clk + cdclk), pixel_clk),
						  mul_u32_u32(link_clk, cdclk));

	tu_data = भाग64_u64(mul_u32_u32(pixel_clk * vdsc_bpp * 8, 1000000),
			    mul_u32_u32(link_clk * lanes, fec_coeff));
	tu_line = भाग64_u64(h_active * mul_u32_u32(link_clk, fec_coeff),
			    mul_u32_u32(64 * pixel_clk, 1000000));
	link_clks_active  = (tu_line - 1) * 64 + tu_data;

	hblank_rise = (link_clks_active + 6 * DIV_ROUND_UP(link_clks_active, 250) + 4) * pixel_clk / link_clk;

	वापस h_active - hblank_rise + hblank_delta;
पूर्ण

अटल अचिन्हित पूर्णांक calc_samples_room(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अचिन्हित पूर्णांक h_active, h_total, pixel_clk;
	अचिन्हित पूर्णांक link_clk, lanes;

	h_active = crtc_state->hw.adjusted_mode.hdisplay;
	h_total = crtc_state->hw.adjusted_mode.htotal;
	pixel_clk = crtc_state->hw.adjusted_mode.घड़ी;
	link_clk = crtc_state->port_घड़ी;
	lanes = crtc_state->lane_count;

	वापस ((h_total - h_active) * link_clk - 12 * pixel_clk) /
		(pixel_clk * (48 / lanes + 2));
पूर्ण

अटल व्योम enable_audio_dsc_wa(काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	क्रमागत pipe pipe = crtc->pipe;
	अचिन्हित पूर्णांक hblank_early_prog, samples_room;
	अचिन्हित पूर्णांक val;

	अगर (DISPLAY_VER(i915) < 11)
		वापस;

	val = पूर्णांकel_de_पढ़ो(i915, AUD_CONFIG_BE);

	अगर (IS_DISPLAY_VER(i915, 11))
		val |= HBLANK_EARLY_ENABLE_ICL(pipe);
	अन्यथा अगर (DISPLAY_VER(i915) >= 12)
		val |= HBLANK_EARLY_ENABLE_TGL(pipe);

	अगर (crtc_state->dsc.compression_enable &&
	    (crtc_state->hw.adjusted_mode.hdisplay >= 3840 &&
	    crtc_state->hw.adjusted_mode.vdisplay >= 2160)) अणु
		/* Get hblank early enable value required */
		hblank_early_prog = calc_hblank_early_prog(encoder, crtc_state);
		अगर (hblank_early_prog < 32) अणु
			val &= ~HBLANK_START_COUNT_MASK(pipe);
			val |= HBLANK_START_COUNT(pipe, HBLANK_START_COUNT_32);
		पूर्ण अन्यथा अगर (hblank_early_prog < 64) अणु
			val &= ~HBLANK_START_COUNT_MASK(pipe);
			val |= HBLANK_START_COUNT(pipe, HBLANK_START_COUNT_64);
		पूर्ण अन्यथा अगर (hblank_early_prog < 96) अणु
			val &= ~HBLANK_START_COUNT_MASK(pipe);
			val |= HBLANK_START_COUNT(pipe, HBLANK_START_COUNT_96);
		पूर्ण अन्यथा अणु
			val &= ~HBLANK_START_COUNT_MASK(pipe);
			val |= HBLANK_START_COUNT(pipe, HBLANK_START_COUNT_128);
		पूर्ण

		/* Get samples room value required */
		samples_room = calc_samples_room(crtc_state);
		अगर (samples_room < 3) अणु
			val &= ~NUMBER_SAMPLES_PER_LINE_MASK(pipe);
			val |= NUMBER_SAMPLES_PER_LINE(pipe, samples_room);
		पूर्ण अन्यथा अणु
			/* Program 0 i.e "All Samples available in buffer" */
			val &= ~NUMBER_SAMPLES_PER_LINE_MASK(pipe);
			val |= NUMBER_SAMPLES_PER_LINE(pipe, 0x0);
		पूर्ण
	पूर्ण

	पूर्णांकel_de_ग_लिखो(i915, AUD_CONFIG_BE, val);
पूर्ण

#अघोषित ROUNDING_FACTOR

अटल व्योम hsw_audio_codec_enable(काष्ठा पूर्णांकel_encoder *encoder,
				   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				   स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा drm_connector *connector = conn_state->connector;
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	स्थिर u8 *eld = connector->eld;
	u32 पंचांगp;
	पूर्णांक len, i;

	drm_dbg_kms(&dev_priv->drm,
		    "Enable audio codec on transcoder %s, %u bytes ELD\n",
		     transcoder_name(cpu_transcoder), drm_eld_size(eld));

	mutex_lock(&dev_priv->av_mutex);

	/* Enable Audio WA क्रम 4k DSC useहालs */
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DP))
		enable_audio_dsc_wa(encoder, crtc_state);

	/* Enable audio presence detect, invalidate ELD */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, HSW_AUD_PIN_ELD_CP_VLD);
	पंचांगp |= AUDIO_OUTPUT_ENABLE(cpu_transcoder);
	पंचांगp &= ~AUDIO_ELD_VALID(cpu_transcoder);
	पूर्णांकel_de_ग_लिखो(dev_priv, HSW_AUD_PIN_ELD_CP_VLD, पंचांगp);

	/*
	 * FIXME: We're supposed to रुको क्रम vblank here, but we have vblanks
	 * disabled during the mode set. The proper fix would be to push the
	 * rest of the setup पूर्णांकo a vblank work item, queued here, but the
	 * infraकाष्ठाure is not there yet.
	 */

	/* Reset ELD ग_लिखो address */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, HSW_AUD_DIP_ELD_CTRL(cpu_transcoder));
	पंचांगp &= ~IBX_ELD_ADDRESS_MASK;
	पूर्णांकel_de_ग_लिखो(dev_priv, HSW_AUD_DIP_ELD_CTRL(cpu_transcoder), पंचांगp);

	/* Up to 84 bytes of hw ELD buffer */
	len = min(drm_eld_size(eld), 84);
	क्रम (i = 0; i < len / 4; i++)
		पूर्णांकel_de_ग_लिखो(dev_priv, HSW_AUD_EDID_DATA(cpu_transcoder),
			       *((स्थिर u32 *)eld + i));

	/* ELD valid */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, HSW_AUD_PIN_ELD_CP_VLD);
	पंचांगp |= AUDIO_ELD_VALID(cpu_transcoder);
	पूर्णांकel_de_ग_लिखो(dev_priv, HSW_AUD_PIN_ELD_CP_VLD, पंचांगp);

	/* Enable बारtamps */
	hsw_audio_config_update(encoder, crtc_state);

	mutex_unlock(&dev_priv->av_mutex);
पूर्ण

अटल व्योम ilk_audio_codec_disable(काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				    स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(old_crtc_state->uapi.crtc);
	क्रमागत pipe pipe = crtc->pipe;
	क्रमागत port port = encoder->port;
	u32 पंचांगp, eldv;
	i915_reg_t aud_config, aud_cntrl_st2;

	drm_dbg_kms(&dev_priv->drm,
		    "Disable audio codec on [ENCODER:%d:%s], pipe %c\n",
		     encoder->base.base.id, encoder->base.name,
		     pipe_name(pipe));

	अगर (drm_WARN_ON(&dev_priv->drm, port == PORT_A))
		वापस;

	अगर (HAS_PCH_IBX(dev_priv)) अणु
		aud_config = IBX_AUD_CFG(pipe);
		aud_cntrl_st2 = IBX_AUD_CNTL_ST2;
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		aud_config = VLV_AUD_CFG(pipe);
		aud_cntrl_st2 = VLV_AUD_CNTL_ST2;
	पूर्ण अन्यथा अणु
		aud_config = CPT_AUD_CFG(pipe);
		aud_cntrl_st2 = CPT_AUD_CNTRL_ST2;
	पूर्ण

	/* Disable बारtamps */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, aud_config);
	पंचांगp &= ~AUD_CONFIG_N_VALUE_INDEX;
	पंचांगp |= AUD_CONFIG_N_PROG_ENABLE;
	पंचांगp &= ~AUD_CONFIG_UPPER_N_MASK;
	पंचांगp &= ~AUD_CONFIG_LOWER_N_MASK;
	अगर (पूर्णांकel_crtc_has_dp_encoder(old_crtc_state))
		पंचांगp |= AUD_CONFIG_N_VALUE_INDEX;
	पूर्णांकel_de_ग_लिखो(dev_priv, aud_config, पंचांगp);

	eldv = IBX_ELD_VALID(port);

	/* Invalidate ELD */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, aud_cntrl_st2);
	पंचांगp &= ~eldv;
	पूर्णांकel_de_ग_लिखो(dev_priv, aud_cntrl_st2, पंचांगp);
पूर्ण

अटल व्योम ilk_audio_codec_enable(काष्ठा पूर्णांकel_encoder *encoder,
				   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				   स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_connector *connector = conn_state->connector;
	क्रमागत pipe pipe = crtc->pipe;
	क्रमागत port port = encoder->port;
	स्थिर u8 *eld = connector->eld;
	u32 पंचांगp, eldv;
	पूर्णांक len, i;
	i915_reg_t hdmiw_hdmiedid, aud_config, aud_cntl_st, aud_cntrl_st2;

	drm_dbg_kms(&dev_priv->drm,
		    "Enable audio codec on [ENCODER:%d:%s], pipe %c, %u bytes ELD\n",
		    encoder->base.base.id, encoder->base.name,
		    pipe_name(pipe), drm_eld_size(eld));

	अगर (drm_WARN_ON(&dev_priv->drm, port == PORT_A))
		वापस;

	/*
	 * FIXME: We're supposed to रुको क्रम vblank here, but we have vblanks
	 * disabled during the mode set. The proper fix would be to push the
	 * rest of the setup पूर्णांकo a vblank work item, queued here, but the
	 * infraकाष्ठाure is not there yet.
	 */

	अगर (HAS_PCH_IBX(dev_priv)) अणु
		hdmiw_hdmiedid = IBX_HDMIW_HDMIEDID(pipe);
		aud_config = IBX_AUD_CFG(pipe);
		aud_cntl_st = IBX_AUD_CNTL_ST(pipe);
		aud_cntrl_st2 = IBX_AUD_CNTL_ST2;
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(dev_priv) ||
		   IS_CHERRYVIEW(dev_priv)) अणु
		hdmiw_hdmiedid = VLV_HDMIW_HDMIEDID(pipe);
		aud_config = VLV_AUD_CFG(pipe);
		aud_cntl_st = VLV_AUD_CNTL_ST(pipe);
		aud_cntrl_st2 = VLV_AUD_CNTL_ST2;
	पूर्ण अन्यथा अणु
		hdmiw_hdmiedid = CPT_HDMIW_HDMIEDID(pipe);
		aud_config = CPT_AUD_CFG(pipe);
		aud_cntl_st = CPT_AUD_CNTL_ST(pipe);
		aud_cntrl_st2 = CPT_AUD_CNTRL_ST2;
	पूर्ण

	eldv = IBX_ELD_VALID(port);

	/* Invalidate ELD */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, aud_cntrl_st2);
	पंचांगp &= ~eldv;
	पूर्णांकel_de_ग_लिखो(dev_priv, aud_cntrl_st2, पंचांगp);

	/* Reset ELD ग_लिखो address */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, aud_cntl_st);
	पंचांगp &= ~IBX_ELD_ADDRESS_MASK;
	पूर्णांकel_de_ग_लिखो(dev_priv, aud_cntl_st, पंचांगp);

	/* Up to 84 bytes of hw ELD buffer */
	len = min(drm_eld_size(eld), 84);
	क्रम (i = 0; i < len / 4; i++)
		पूर्णांकel_de_ग_लिखो(dev_priv, hdmiw_hdmiedid,
			       *((स्थिर u32 *)eld + i));

	/* ELD valid */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, aud_cntrl_st2);
	पंचांगp |= eldv;
	पूर्णांकel_de_ग_लिखो(dev_priv, aud_cntrl_st2, पंचांगp);

	/* Enable बारtamps */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, aud_config);
	पंचांगp &= ~AUD_CONFIG_N_VALUE_INDEX;
	पंचांगp &= ~AUD_CONFIG_N_PROG_ENABLE;
	पंचांगp &= ~AUD_CONFIG_PIXEL_CLOCK_HDMI_MASK;
	अगर (पूर्णांकel_crtc_has_dp_encoder(crtc_state))
		पंचांगp |= AUD_CONFIG_N_VALUE_INDEX;
	अन्यथा
		पंचांगp |= audio_config_hdmi_pixel_घड़ी(crtc_state);
	पूर्णांकel_de_ग_लिखो(dev_priv, aud_config, पंचांगp);
पूर्ण

/**
 * पूर्णांकel_audio_codec_enable - Enable the audio codec क्रम HD audio
 * @encoder: encoder on which to enable audio
 * @crtc_state: poपूर्णांकer to the current crtc state.
 * @conn_state: poपूर्णांकer to the current connector state.
 *
 * The enable sequences may only be perक्रमmed after enabling the transcoder and
 * port, and after completed link training.
 */
व्योम पूर्णांकel_audio_codec_enable(काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा i915_audio_component *acomp = dev_priv->audio_component;
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_connector *connector = conn_state->connector;
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;
	क्रमागत port port = encoder->port;
	क्रमागत pipe pipe = crtc->pipe;

	/* FIXME precompute the ELD in .compute_config() */
	अगर (!connector->eld[0])
		drm_dbg_kms(&dev_priv->drm,
			    "Bogus ELD on [CONNECTOR:%d:%s]\n",
			    connector->base.id, connector->name);

	drm_dbg(&dev_priv->drm, "ELD on [CONNECTOR:%d:%s], [ENCODER:%d:%s]\n",
		connector->base.id,
		connector->name,
		encoder->base.base.id,
		encoder->base.name);

	connector->eld[6] = drm_av_sync_delay(connector, adjusted_mode) / 2;

	अगर (dev_priv->display.audio_codec_enable)
		dev_priv->display.audio_codec_enable(encoder,
						     crtc_state,
						     conn_state);

	mutex_lock(&dev_priv->av_mutex);
	encoder->audio_connector = connector;

	/* referred in audio callbacks */
	dev_priv->av_enc_map[pipe] = encoder;
	mutex_unlock(&dev_priv->av_mutex);

	अगर (acomp && acomp->base.audio_ops &&
	    acomp->base.audio_ops->pin_eld_notअगरy) अणु
		/* audio drivers expect pipe = -1 to indicate Non-MST हालs */
		अगर (!पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DP_MST))
			pipe = -1;
		acomp->base.audio_ops->pin_eld_notअगरy(acomp->base.audio_ops->audio_ptr,
						 (पूर्णांक) port, (पूर्णांक) pipe);
	पूर्ण

	पूर्णांकel_lpe_audio_notअगरy(dev_priv, pipe, port, connector->eld,
			       crtc_state->port_घड़ी,
			       पूर्णांकel_crtc_has_dp_encoder(crtc_state));
पूर्ण

/**
 * पूर्णांकel_audio_codec_disable - Disable the audio codec क्रम HD audio
 * @encoder: encoder on which to disable audio
 * @old_crtc_state: poपूर्णांकer to the old crtc state.
 * @old_conn_state: poपूर्णांकer to the old connector state.
 *
 * The disable sequences must be perक्रमmed beक्रमe disabling the transcoder or
 * port.
 */
व्योम पूर्णांकel_audio_codec_disable(काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			       स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा i915_audio_component *acomp = dev_priv->audio_component;
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(old_crtc_state->uapi.crtc);
	क्रमागत port port = encoder->port;
	क्रमागत pipe pipe = crtc->pipe;

	अगर (dev_priv->display.audio_codec_disable)
		dev_priv->display.audio_codec_disable(encoder,
						      old_crtc_state,
						      old_conn_state);

	mutex_lock(&dev_priv->av_mutex);
	encoder->audio_connector = शून्य;
	dev_priv->av_enc_map[pipe] = शून्य;
	mutex_unlock(&dev_priv->av_mutex);

	अगर (acomp && acomp->base.audio_ops &&
	    acomp->base.audio_ops->pin_eld_notअगरy) अणु
		/* audio drivers expect pipe = -1 to indicate Non-MST हालs */
		अगर (!पूर्णांकel_crtc_has_type(old_crtc_state, INTEL_OUTPUT_DP_MST))
			pipe = -1;
		acomp->base.audio_ops->pin_eld_notअगरy(acomp->base.audio_ops->audio_ptr,
						 (पूर्णांक) port, (पूर्णांक) pipe);
	पूर्ण

	पूर्णांकel_lpe_audio_notअगरy(dev_priv, pipe, port, शून्य, 0, false);
पूर्ण

/**
 * पूर्णांकel_init_audio_hooks - Set up chip specअगरic audio hooks
 * @dev_priv: device निजी
 */
व्योम पूर्णांकel_init_audio_hooks(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (IS_G4X(dev_priv)) अणु
		dev_priv->display.audio_codec_enable = g4x_audio_codec_enable;
		dev_priv->display.audio_codec_disable = g4x_audio_codec_disable;
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		dev_priv->display.audio_codec_enable = ilk_audio_codec_enable;
		dev_priv->display.audio_codec_disable = ilk_audio_codec_disable;
	पूर्ण अन्यथा अगर (IS_HASWELL(dev_priv) || DISPLAY_VER(dev_priv) >= 8) अणु
		dev_priv->display.audio_codec_enable = hsw_audio_codec_enable;
		dev_priv->display.audio_codec_disable = hsw_audio_codec_disable;
	पूर्ण अन्यथा अगर (HAS_PCH_SPLIT(dev_priv)) अणु
		dev_priv->display.audio_codec_enable = ilk_audio_codec_enable;
		dev_priv->display.audio_codec_disable = ilk_audio_codec_disable;
	पूर्ण
पूर्ण

अटल पूर्णांक glk_क्रमce_audio_cdclk_commit(काष्ठा पूर्णांकel_atomic_state *state,
					काष्ठा पूर्णांकel_crtc *crtc,
					bool enable)
अणु
	काष्ठा पूर्णांकel_cdclk_state *cdclk_state;
	पूर्णांक ret;

	/* need to hold at least one crtc lock क्रम the global state */
	ret = drm_modeset_lock(&crtc->base.mutex, state->base.acquire_ctx);
	अगर (ret)
		वापस ret;

	cdclk_state = पूर्णांकel_atomic_get_cdclk_state(state);
	अगर (IS_ERR(cdclk_state))
		वापस PTR_ERR(cdclk_state);

	cdclk_state->क्रमce_min_cdclk = enable ? 2 * 96000 : 0;

	वापस drm_atomic_commit(&state->base);
पूर्ण

अटल व्योम glk_क्रमce_audio_cdclk(काष्ठा drm_i915_निजी *dev_priv,
				  bool enable)
अणु
	काष्ठा drm_modeset_acquire_ctx ctx;
	काष्ठा drm_atomic_state *state;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक ret;

	crtc = पूर्णांकel_get_first_crtc(dev_priv);
	अगर (!crtc)
		वापस;

	drm_modeset_acquire_init(&ctx, 0);
	state = drm_atomic_state_alloc(&dev_priv->drm);
	अगर (drm_WARN_ON(&dev_priv->drm, !state))
		वापस;

	state->acquire_ctx = &ctx;

retry:
	ret = glk_क्रमce_audio_cdclk_commit(to_पूर्णांकel_atomic_state(state), crtc,
					   enable);
	अगर (ret == -EDEADLK) अणु
		drm_atomic_state_clear(state);
		drm_modeset_backoff(&ctx);
		जाओ retry;
	पूर्ण

	drm_WARN_ON(&dev_priv->drm, ret);

	drm_atomic_state_put(state);

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);
पूर्ण

अटल अचिन्हित दीर्घ i915_audio_component_get_घातer(काष्ठा device *kdev)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_to_i915(kdev);
	पूर्णांकel_wakeref_t ret;

	/* Catch potential impedance mismatches beक्रमe they occur! */
	BUILD_BUG_ON(माप(पूर्णांकel_wakeref_t) > माप(अचिन्हित दीर्घ));

	ret = पूर्णांकel_display_घातer_get(dev_priv, POWER_DOMAIN_AUDIO);

	अगर (dev_priv->audio_घातer_refcount++ == 0) अणु
		अगर (DISPLAY_VER(dev_priv) >= 9) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, AUD_FREQ_CNTRL,
				       dev_priv->audio_freq_cntrl);
			drm_dbg_kms(&dev_priv->drm,
				    "restored AUD_FREQ_CNTRL to 0x%x\n",
				    dev_priv->audio_freq_cntrl);
		पूर्ण

		/* Force CDCLK to 2*BCLK as दीर्घ as we need audio घातered. */
		अगर (IS_GEMINILAKE(dev_priv))
			glk_क्रमce_audio_cdclk(dev_priv, true);

		अगर (DISPLAY_VER(dev_priv) >= 10)
			पूर्णांकel_de_ग_लिखो(dev_priv, AUD_PIN_BUF_CTL,
				       (पूर्णांकel_de_पढ़ो(dev_priv, AUD_PIN_BUF_CTL) | AUD_PIN_BUF_ENABLE));
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम i915_audio_component_put_घातer(काष्ठा device *kdev,
					   अचिन्हित दीर्घ cookie)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_to_i915(kdev);

	/* Stop क्रमcing CDCLK to 2*BCLK अगर no need क्रम audio to be घातered. */
	अगर (--dev_priv->audio_घातer_refcount == 0)
		अगर (IS_GEMINILAKE(dev_priv))
			glk_क्रमce_audio_cdclk(dev_priv, false);

	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_AUDIO, cookie);
पूर्ण

अटल व्योम i915_audio_component_codec_wake_override(काष्ठा device *kdev,
						     bool enable)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_to_i915(kdev);
	अचिन्हित दीर्घ cookie;
	u32 पंचांगp;

	अगर (DISPLAY_VER(dev_priv) < 9)
		वापस;

	cookie = i915_audio_component_get_घातer(kdev);

	/*
	 * Enable/disable generating the codec wake संकेत, overriding the
	 * पूर्णांकernal logic to generate the codec wake to controller.
	 */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, HSW_AUD_CHICKENBIT);
	पंचांगp &= ~SKL_AUD_CODEC_WAKE_SIGNAL;
	पूर्णांकel_de_ग_लिखो(dev_priv, HSW_AUD_CHICKENBIT, पंचांगp);
	usleep_range(1000, 1500);

	अगर (enable) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, HSW_AUD_CHICKENBIT);
		पंचांगp |= SKL_AUD_CODEC_WAKE_SIGNAL;
		पूर्णांकel_de_ग_लिखो(dev_priv, HSW_AUD_CHICKENBIT, पंचांगp);
		usleep_range(1000, 1500);
	पूर्ण

	i915_audio_component_put_घातer(kdev, cookie);
पूर्ण

/* Get CDCLK in kHz  */
अटल पूर्णांक i915_audio_component_get_cdclk_freq(काष्ठा device *kdev)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_to_i915(kdev);

	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, !HAS_DDI(dev_priv)))
		वापस -ENODEV;

	वापस dev_priv->cdclk.hw.cdclk;
पूर्ण

/*
 * get the पूर्णांकel_encoder according to the parameter port and pipe
 * पूर्णांकel_encoder is saved by the index of pipe
 * MST & (pipe >= 0): वापस the av_enc_map[pipe],
 *   when port is matched
 * MST & (pipe < 0): this is invalid
 * Non-MST & (pipe >= 0): only pipe = 0 (the first device entry)
 *   will get the right पूर्णांकel_encoder with port matched
 * Non-MST & (pipe < 0): get the right पूर्णांकel_encoder with port matched
 */
अटल काष्ठा पूर्णांकel_encoder *get_saved_enc(काष्ठा drm_i915_निजी *dev_priv,
					       पूर्णांक port, पूर्णांक pipe)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;

	/* MST */
	अगर (pipe >= 0) अणु
		अगर (drm_WARN_ON(&dev_priv->drm,
				pipe >= ARRAY_SIZE(dev_priv->av_enc_map)))
			वापस शून्य;

		encoder = dev_priv->av_enc_map[pipe];
		/*
		 * when bootup, audio driver may not know it is
		 * MST or not. So it will poll all the port & pipe
		 * combinations
		 */
		अगर (encoder != शून्य && encoder->port == port &&
		    encoder->type == INTEL_OUTPUT_DP_MST)
			वापस encoder;
	पूर्ण

	/* Non-MST */
	अगर (pipe > 0)
		वापस शून्य;

	क्रम_each_pipe(dev_priv, pipe) अणु
		encoder = dev_priv->av_enc_map[pipe];
		अगर (encoder == शून्य)
			जारी;

		अगर (encoder->type == INTEL_OUTPUT_DP_MST)
			जारी;

		अगर (port == encoder->port)
			वापस encoder;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक i915_audio_component_sync_audio_rate(काष्ठा device *kdev, पूर्णांक port,
						पूर्णांक pipe, पूर्णांक rate)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_to_i915(kdev);
	काष्ठा i915_audio_component *acomp = dev_priv->audio_component;
	काष्ठा पूर्णांकel_encoder *encoder;
	काष्ठा पूर्णांकel_crtc *crtc;
	अचिन्हित दीर्घ cookie;
	पूर्णांक err = 0;

	अगर (!HAS_DDI(dev_priv))
		वापस 0;

	cookie = i915_audio_component_get_घातer(kdev);
	mutex_lock(&dev_priv->av_mutex);

	/* 1. get the pipe */
	encoder = get_saved_enc(dev_priv, port, pipe);
	अगर (!encoder || !encoder->base.crtc) अणु
		drm_dbg_kms(&dev_priv->drm, "Not valid for port %c\n",
			    port_name(port));
		err = -ENODEV;
		जाओ unlock;
	पूर्ण

	crtc = to_पूर्णांकel_crtc(encoder->base.crtc);

	/* port must be valid now, otherwise the pipe will be invalid */
	acomp->aud_sample_rate[port] = rate;

	hsw_audio_config_update(encoder, crtc->config);

 unlock:
	mutex_unlock(&dev_priv->av_mutex);
	i915_audio_component_put_घातer(kdev, cookie);
	वापस err;
पूर्ण

अटल पूर्णांक i915_audio_component_get_eld(काष्ठा device *kdev, पूर्णांक port,
					पूर्णांक pipe, bool *enabled,
					अचिन्हित अक्षर *buf, पूर्णांक max_bytes)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_to_i915(kdev);
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder;
	स्थिर u8 *eld;
	पूर्णांक ret = -EINVAL;

	mutex_lock(&dev_priv->av_mutex);

	पूर्णांकel_encoder = get_saved_enc(dev_priv, port, pipe);
	अगर (!पूर्णांकel_encoder) अणु
		drm_dbg_kms(&dev_priv->drm, "Not valid for port %c\n",
			    port_name(port));
		mutex_unlock(&dev_priv->av_mutex);
		वापस ret;
	पूर्ण

	ret = 0;
	*enabled = पूर्णांकel_encoder->audio_connector != शून्य;
	अगर (*enabled) अणु
		eld = पूर्णांकel_encoder->audio_connector->eld;
		ret = drm_eld_size(eld);
		स_नकल(buf, eld, min(max_bytes, ret));
	पूर्ण

	mutex_unlock(&dev_priv->av_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_audio_component_ops i915_audio_component_ops = अणु
	.owner		= THIS_MODULE,
	.get_घातer	= i915_audio_component_get_घातer,
	.put_घातer	= i915_audio_component_put_घातer,
	.codec_wake_override = i915_audio_component_codec_wake_override,
	.get_cdclk_freq	= i915_audio_component_get_cdclk_freq,
	.sync_audio_rate = i915_audio_component_sync_audio_rate,
	.get_eld	= i915_audio_component_get_eld,
पूर्ण;

अटल पूर्णांक i915_audio_component_bind(काष्ठा device *i915_kdev,
				     काष्ठा device *hda_kdev, व्योम *data)
अणु
	काष्ठा i915_audio_component *acomp = data;
	काष्ठा drm_i915_निजी *dev_priv = kdev_to_i915(i915_kdev);
	पूर्णांक i;

	अगर (drm_WARN_ON(&dev_priv->drm, acomp->base.ops || acomp->base.dev))
		वापस -EEXIST;

	अगर (drm_WARN_ON(&dev_priv->drm,
			!device_link_add(hda_kdev, i915_kdev,
					 DL_FLAG_STATELESS)))
		वापस -ENOMEM;

	drm_modeset_lock_all(&dev_priv->drm);
	acomp->base.ops = &i915_audio_component_ops;
	acomp->base.dev = i915_kdev;
	BUILD_BUG_ON(MAX_PORTS != I915_MAX_PORTS);
	क्रम (i = 0; i < ARRAY_SIZE(acomp->aud_sample_rate); i++)
		acomp->aud_sample_rate[i] = 0;
	dev_priv->audio_component = acomp;
	drm_modeset_unlock_all(&dev_priv->drm);

	वापस 0;
पूर्ण

अटल व्योम i915_audio_component_unbind(काष्ठा device *i915_kdev,
					काष्ठा device *hda_kdev, व्योम *data)
अणु
	काष्ठा i915_audio_component *acomp = data;
	काष्ठा drm_i915_निजी *dev_priv = kdev_to_i915(i915_kdev);

	drm_modeset_lock_all(&dev_priv->drm);
	acomp->base.ops = शून्य;
	acomp->base.dev = शून्य;
	dev_priv->audio_component = शून्य;
	drm_modeset_unlock_all(&dev_priv->drm);

	device_link_हटाओ(hda_kdev, i915_kdev);

	अगर (dev_priv->audio_घातer_refcount)
		drm_err(&dev_priv->drm, "audio power refcount %d after unbind\n",
			dev_priv->audio_घातer_refcount);
पूर्ण

अटल स्थिर काष्ठा component_ops i915_audio_component_bind_ops = अणु
	.bind	= i915_audio_component_bind,
	.unbind	= i915_audio_component_unbind,
पूर्ण;

#घोषणा AUD_FREQ_TMODE_SHIFT	14
#घोषणा AUD_FREQ_4T		0
#घोषणा AUD_FREQ_8T		(2 << AUD_FREQ_TMODE_SHIFT)
#घोषणा AUD_FREQ_PULLCLKS(x)	(((x) & 0x3) << 11)
#घोषणा AUD_FREQ_BCLK_96M	BIT(4)

#घोषणा AUD_FREQ_GEN12          (AUD_FREQ_8T | AUD_FREQ_PULLCLKS(0) | AUD_FREQ_BCLK_96M)
#घोषणा AUD_FREQ_TGL_BROKEN     (AUD_FREQ_8T | AUD_FREQ_PULLCLKS(2) | AUD_FREQ_BCLK_96M)

/**
 * i915_audio_component_init - initialize and रेजिस्टर the audio component
 * @dev_priv: i915 device instance
 *
 * This will रेजिस्टर with the component framework a child component which
 * will bind dynamically to the snd_hda_पूर्णांकel driver's corresponding master
 * component when the latter is रेजिस्टरed. During binding the child
 * initializes an instance of काष्ठा i915_audio_component which it receives
 * from the master. The master can then start to use the पूर्णांकerface defined by
 * this काष्ठा. Each side can अवरोध the binding at any poपूर्णांक by deरेजिस्टरing
 * its own component after which each side's component unbind callback is
 * called.
 *
 * We ignore any error during registration and जारी with reduced
 * functionality (i.e. without HDMI audio).
 */
अटल व्योम i915_audio_component_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 aud_freq, aud_freq_init;
	पूर्णांक ret;

	ret = component_add_typed(dev_priv->drm.dev,
				  &i915_audio_component_bind_ops,
				  I915_COMPONENT_AUDIO);
	अगर (ret < 0) अणु
		drm_err(&dev_priv->drm,
			"failed to add audio component (%d)\n", ret);
		/* जारी with reduced functionality */
		वापस;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 9) अणु
		aud_freq_init = पूर्णांकel_de_पढ़ो(dev_priv, AUD_FREQ_CNTRL);

		अगर (INTEL_GEN(dev_priv) >= 12)
			aud_freq = AUD_FREQ_GEN12;
		अन्यथा
			aud_freq = aud_freq_init;

		/* use BIOS provided value क्रम TGL unless it is a known bad value */
		अगर (IS_TIGERLAKE(dev_priv) && aud_freq_init != AUD_FREQ_TGL_BROKEN)
			aud_freq = aud_freq_init;

		drm_dbg_kms(&dev_priv->drm, "use AUD_FREQ_CNTRL of 0x%x (init value 0x%x)\n",
			    aud_freq, aud_freq_init);

		dev_priv->audio_freq_cntrl = aud_freq;
	पूर्ण

	dev_priv->audio_component_रेजिस्टरed = true;
पूर्ण

/**
 * i915_audio_component_cleanup - deरेजिस्टर the audio component
 * @dev_priv: i915 device instance
 *
 * Deरेजिस्टरs the audio component, अवरोधing any existing binding to the
 * corresponding snd_hda_पूर्णांकel driver's master component.
 */
अटल व्योम i915_audio_component_cleanup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (!dev_priv->audio_component_रेजिस्टरed)
		वापस;

	component_del(dev_priv->drm.dev, &i915_audio_component_bind_ops);
	dev_priv->audio_component_रेजिस्टरed = false;
पूर्ण

/**
 * पूर्णांकel_audio_init() - Initialize the audio driver either using
 * component framework or using lpe audio bridge
 * @dev_priv: the i915 drm device निजी data
 *
 */
व्योम पूर्णांकel_audio_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (पूर्णांकel_lpe_audio_init(dev_priv) < 0)
		i915_audio_component_init(dev_priv);
पूर्ण

/**
 * पूर्णांकel_audio_deinit() - deinitialize the audio driver
 * @dev_priv: the i915 drm device निजी data
 *
 */
व्योम पूर्णांकel_audio_deinit(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर ((dev_priv)->lpe_audio.platdev != शून्य)
		पूर्णांकel_lpe_audio_tearकरोwn(dev_priv);
	अन्यथा
		i915_audio_component_cleanup(dev_priv);
पूर्ण
