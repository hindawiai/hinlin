<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
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
 *
 *
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_dp_dual_mode_helper.h>
#समावेश <drm/drm_edid.h>

#समावेश "intel_display_types.h"
#समावेश "intel_dp.h"
#समावेश "intel_lspcon.h"
#समावेश "intel_hdmi.h"

/* LSPCON OUI Venकरोr ID(signatures) */
#घोषणा LSPCON_VENDOR_PARADE_OUI 0x001CF8
#घोषणा LSPCON_VENDOR_MCA_OUI 0x0060AD

#घोषणा DPCD_MCA_LSPCON_HDR_STATUS	0x70003
#घोषणा DPCD_PARADE_LSPCON_HDR_STATUS	0x00511

/* AUX addresses to ग_लिखो MCA AVI IF */
#घोषणा LSPCON_MCA_AVI_IF_WRITE_OFFSET 0x5C0
#घोषणा LSPCON_MCA_AVI_IF_CTRL 0x5DF
#घोषणा  LSPCON_MCA_AVI_IF_KICKOFF (1 << 0)
#घोषणा  LSPCON_MCA_AVI_IF_HANDLED (1 << 1)

/* AUX addresses to ग_लिखो Parade AVI IF */
#घोषणा LSPCON_PARADE_AVI_IF_WRITE_OFFSET 0x516
#घोषणा LSPCON_PARADE_AVI_IF_CTRL 0x51E
#घोषणा  LSPCON_PARADE_AVI_IF_KICKOFF (1 << 7)
#घोषणा LSPCON_PARADE_AVI_IF_DATA_SIZE 32

अटल काष्ठा पूर्णांकel_dp *lspcon_to_पूर्णांकel_dp(काष्ठा पूर्णांकel_lspcon *lspcon)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port =
		container_of(lspcon, काष्ठा पूर्णांकel_digital_port, lspcon);

	वापस &dig_port->dp;
पूर्ण

अटल स्थिर अक्षर *lspcon_mode_name(क्रमागत drm_lspcon_mode mode)
अणु
	चयन (mode) अणु
	हाल DRM_LSPCON_MODE_PCON:
		वापस "PCON";
	हाल DRM_LSPCON_MODE_LS:
		वापस "LS";
	हाल DRM_LSPCON_MODE_INVALID:
		वापस "INVALID";
	शेष:
		MISSING_CASE(mode);
		वापस "INVALID";
	पूर्ण
पूर्ण

अटल bool lspcon_detect_venकरोr(काष्ठा पूर्णांकel_lspcon *lspcon)
अणु
	काष्ठा पूर्णांकel_dp *dp = lspcon_to_पूर्णांकel_dp(lspcon);
	काष्ठा drm_dp_dpcd_ident *ident;
	u32 venकरोr_oui;

	अगर (drm_dp_पढ़ो_desc(&dp->aux, &dp->desc, drm_dp_is_branch(dp->dpcd))) अणु
		DRM_ERROR("Can't read description\n");
		वापस false;
	पूर्ण

	ident = &dp->desc.ident;
	venकरोr_oui = (ident->oui[0] << 16) | (ident->oui[1] << 8) |
		      ident->oui[2];

	चयन (venकरोr_oui) अणु
	हाल LSPCON_VENDOR_MCA_OUI:
		lspcon->venकरोr = LSPCON_VENDOR_MCA;
		DRM_DEBUG_KMS("Vendor: Mega Chips\n");
		अवरोध;

	हाल LSPCON_VENDOR_PARADE_OUI:
		lspcon->venकरोr = LSPCON_VENDOR_PARADE;
		DRM_DEBUG_KMS("Vendor: Parade Tech\n");
		अवरोध;

	शेष:
		DRM_ERROR("Invalid/Unknown vendor OUI\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल u32 get_hdr_status_reg(काष्ठा पूर्णांकel_lspcon *lspcon)
अणु
	अगर (lspcon->venकरोr == LSPCON_VENDOR_MCA)
		वापस DPCD_MCA_LSPCON_HDR_STATUS;
	अन्यथा
		वापस DPCD_PARADE_LSPCON_HDR_STATUS;
पूर्ण

व्योम lspcon_detect_hdr_capability(काष्ठा पूर्णांकel_lspcon *lspcon)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port =
		container_of(lspcon, काष्ठा पूर्णांकel_digital_port, lspcon);
	काष्ठा drm_device *dev = dig_port->base.base.dev;
	काष्ठा पूर्णांकel_dp *dp = lspcon_to_पूर्णांकel_dp(lspcon);
	u8 hdr_caps;
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ो(&dp->aux, get_hdr_status_reg(lspcon),
			       &hdr_caps, 1);

	अगर (ret < 0) अणु
		drm_dbg_kms(dev, "HDR capability detection failed\n");
		lspcon->hdr_supported = false;
	पूर्ण अन्यथा अगर (hdr_caps & 0x1) अणु
		drm_dbg_kms(dev, "LSPCON capable of HDR\n");
		lspcon->hdr_supported = true;
	पूर्ण
पूर्ण

अटल क्रमागत drm_lspcon_mode lspcon_get_current_mode(काष्ठा पूर्णांकel_lspcon *lspcon)
अणु
	क्रमागत drm_lspcon_mode current_mode;
	काष्ठा i2c_adapter *adapter = &lspcon_to_पूर्णांकel_dp(lspcon)->aux.ddc;

	अगर (drm_lspcon_get_mode(adapter, &current_mode)) अणु
		DRM_DEBUG_KMS("Error reading LSPCON mode\n");
		वापस DRM_LSPCON_MODE_INVALID;
	पूर्ण
	वापस current_mode;
पूर्ण

अटल क्रमागत drm_lspcon_mode lspcon_रुको_mode(काष्ठा पूर्णांकel_lspcon *lspcon,
					     क्रमागत drm_lspcon_mode mode)
अणु
	क्रमागत drm_lspcon_mode current_mode;

	current_mode = lspcon_get_current_mode(lspcon);
	अगर (current_mode == mode)
		जाओ out;

	DRM_DEBUG_KMS("Waiting for LSPCON mode %s to settle\n",
		      lspcon_mode_name(mode));

	रुको_क्रम((current_mode = lspcon_get_current_mode(lspcon)) == mode, 400);
	अगर (current_mode != mode)
		DRM_ERROR("LSPCON mode hasn't settled\n");

out:
	DRM_DEBUG_KMS("Current LSPCON mode %s\n",
		      lspcon_mode_name(current_mode));

	वापस current_mode;
पूर्ण

अटल पूर्णांक lspcon_change_mode(काष्ठा पूर्णांकel_lspcon *lspcon,
			      क्रमागत drm_lspcon_mode mode)
अणु
	पूर्णांक err;
	क्रमागत drm_lspcon_mode current_mode;
	काष्ठा i2c_adapter *adapter = &lspcon_to_पूर्णांकel_dp(lspcon)->aux.ddc;

	err = drm_lspcon_get_mode(adapter, &current_mode);
	अगर (err) अणु
		DRM_ERROR("Error reading LSPCON mode\n");
		वापस err;
	पूर्ण

	अगर (current_mode == mode) अणु
		DRM_DEBUG_KMS("Current mode = desired LSPCON mode\n");
		वापस 0;
	पूर्ण

	err = drm_lspcon_set_mode(adapter, mode);
	अगर (err < 0) अणु
		DRM_ERROR("LSPCON mode change failed\n");
		वापस err;
	पूर्ण

	lspcon->mode = mode;
	DRM_DEBUG_KMS("LSPCON mode changed done\n");
	वापस 0;
पूर्ण

अटल bool lspcon_wake_native_aux_ch(काष्ठा पूर्णांकel_lspcon *lspcon)
अणु
	u8 rev;

	अगर (drm_dp_dpcd_पढ़ोb(&lspcon_to_पूर्णांकel_dp(lspcon)->aux, DP_DPCD_REV,
			      &rev) != 1) अणु
		DRM_DEBUG_KMS("Native AUX CH down\n");
		वापस false;
	पूर्ण

	DRM_DEBUG_KMS("Native AUX CH up, DPCD version: %d.%d\n",
		      rev >> 4, rev & 0xf);

	वापस true;
पूर्ण

अटल bool lspcon_probe(काष्ठा पूर्णांकel_lspcon *lspcon)
अणु
	पूर्णांक retry;
	क्रमागत drm_dp_dual_mode_type adaptor_type;
	काष्ठा i2c_adapter *adapter = &lspcon_to_पूर्णांकel_dp(lspcon)->aux.ddc;
	क्रमागत drm_lspcon_mode expected_mode;

	expected_mode = lspcon_wake_native_aux_ch(lspcon) ?
			DRM_LSPCON_MODE_PCON : DRM_LSPCON_MODE_LS;

	/* Lets probe the adaptor and check its type */
	क्रम (retry = 0; retry < 6; retry++) अणु
		अगर (retry)
			usleep_range(500, 1000);

		adaptor_type = drm_dp_dual_mode_detect(adapter);
		अगर (adaptor_type == DRM_DP_DUAL_MODE_LSPCON)
			अवरोध;
	पूर्ण

	अगर (adaptor_type != DRM_DP_DUAL_MODE_LSPCON) अणु
		DRM_DEBUG_KMS("No LSPCON detected, found %s\n",
			       drm_dp_get_dual_mode_type_name(adaptor_type));
		वापस false;
	पूर्ण

	/* Yay ... got a LSPCON device */
	DRM_DEBUG_KMS("LSPCON detected\n");
	lspcon->mode = lspcon_रुको_mode(lspcon, expected_mode);

	/*
	 * In the SW state machine, lets Put LSPCON in PCON mode only.
	 * In this way, it will work with both HDMI 1.4 sinks as well as HDMI
	 * 2.0 sinks.
	 */
	अगर (lspcon->mode != DRM_LSPCON_MODE_PCON) अणु
		अगर (lspcon_change_mode(lspcon, DRM_LSPCON_MODE_PCON) < 0) अणु
			DRM_ERROR("LSPCON mode change to PCON failed\n");
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम lspcon_resume_in_pcon_wa(काष्ठा पूर्णांकel_lspcon *lspcon)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = lspcon_to_पूर्णांकel_dp(lspcon);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	अचिन्हित दीर्घ start = jअगरfies;

	जबतक (1) अणु
		अगर (पूर्णांकel_digital_port_connected(&dig_port->base)) अणु
			DRM_DEBUG_KMS("LSPCON recovering in PCON mode after %u ms\n",
				      jअगरfies_to_msecs(jअगरfies - start));
			वापस;
		पूर्ण

		अगर (समय_after(jअगरfies, start + msecs_to_jअगरfies(1000)))
			अवरोध;

		usleep_range(10000, 15000);
	पूर्ण

	DRM_DEBUG_KMS("LSPCON DP descriptor mismatch after resume\n");
पूर्ण

अटल bool lspcon_parade_fw_पढ़ोy(काष्ठा drm_dp_aux *aux)
अणु
	u8 avi_अगर_ctrl;
	u8 retry;
	sमाप_प्रकार ret;

	/* Check अगर LSPCON FW is पढ़ोy क्रम data */
	क्रम (retry = 0; retry < 5; retry++) अणु
		अगर (retry)
			usleep_range(200, 300);

		ret = drm_dp_dpcd_पढ़ो(aux, LSPCON_PARADE_AVI_IF_CTRL,
				       &avi_अगर_ctrl, 1);
		अगर (ret < 0) अणु
			DRM_ERROR("Failed to read AVI IF control\n");
			वापस false;
		पूर्ण

		अगर ((avi_अगर_ctrl & LSPCON_PARADE_AVI_IF_KICKOFF) == 0)
			वापस true;
	पूर्ण

	DRM_ERROR("Parade FW not ready to accept AVI IF\n");
	वापस false;
पूर्ण

अटल bool _lspcon_parade_ग_लिखो_infoframe_blocks(काष्ठा drm_dp_aux *aux,
						  u8 *avi_buf)
अणु
	u8 avi_अगर_ctrl;
	u8 block_count = 0;
	u8 *data;
	u16 reg;
	sमाप_प्रकार ret;

	जबतक (block_count < 4) अणु
		अगर (!lspcon_parade_fw_पढ़ोy(aux)) अणु
			DRM_DEBUG_KMS("LSPCON FW not ready, block %d\n",
				      block_count);
			वापस false;
		पूर्ण

		reg = LSPCON_PARADE_AVI_IF_WRITE_OFFSET;
		data = avi_buf + block_count * 8;
		ret = drm_dp_dpcd_ग_लिखो(aux, reg, data, 8);
		अगर (ret < 0) अणु
			DRM_ERROR("Failed to write AVI IF block %d\n",
				  block_count);
			वापस false;
		पूर्ण

		/*
		 * Once a block of data is written, we have to inक्रमm the FW
		 * about this by writing पूर्णांकo avi infoframe control रेजिस्टर:
		 * - set the kickoff bit[7] to 1
		 * - ग_लिखो the block no. to bits[1:0]
		 */
		reg = LSPCON_PARADE_AVI_IF_CTRL;
		avi_अगर_ctrl = LSPCON_PARADE_AVI_IF_KICKOFF | block_count;
		ret = drm_dp_dpcd_ग_लिखो(aux, reg, &avi_अगर_ctrl, 1);
		अगर (ret < 0) अणु
			DRM_ERROR("Failed to update (0x%x), block %d\n",
				  reg, block_count);
			वापस false;
		पूर्ण

		block_count++;
	पूर्ण

	DRM_DEBUG_KMS("Wrote AVI IF blocks successfully\n");
	वापस true;
पूर्ण

अटल bool _lspcon_ग_लिखो_avi_infoframe_parade(काष्ठा drm_dp_aux *aux,
					       स्थिर u8 *frame,
					       sमाप_प्रकार len)
अणु
	u8 avi_अगर[LSPCON_PARADE_AVI_IF_DATA_SIZE] = अणु1, पूर्ण;

	/*
	 * Parade's frames contains 32 bytes of data, भागided
	 * पूर्णांकo 4 frames:
	 *	Token byte (first byte of first frame, must be non-zero)
	 *	HB0 to HB2	 from AVI IF (3 bytes header)
	 *	PB0 to PB27 from AVI IF (28 bytes data)
	 * So it should look like this
	 *	first block: | <token> <HB0-HB2> <DB0-DB3> |
	 *	next 3 blocks: |<DB4-DB11>|<DB12-DB19>|<DB20-DB28>|
	 */

	अगर (len > LSPCON_PARADE_AVI_IF_DATA_SIZE - 1) अणु
		DRM_ERROR("Invalid length of infoframes\n");
		वापस false;
	पूर्ण

	स_नकल(&avi_अगर[1], frame, len);

	अगर (!_lspcon_parade_ग_लिखो_infoframe_blocks(aux, avi_अगर)) अणु
		DRM_DEBUG_KMS("Failed to write infoframe blocks\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool _lspcon_ग_लिखो_avi_infoframe_mca(काष्ठा drm_dp_aux *aux,
					    स्थिर u8 *buffer, sमाप_प्रकार len)
अणु
	पूर्णांक ret;
	u32 val = 0;
	u32 retry;
	u16 reg;
	स्थिर u8 *data = buffer;

	reg = LSPCON_MCA_AVI_IF_WRITE_OFFSET;
	जबतक (val < len) अणु
		/* DPCD ग_लिखो क्रम AVI IF can fail on a slow FW day, so retry */
		क्रम (retry = 0; retry < 5; retry++) अणु
			ret = drm_dp_dpcd_ग_लिखो(aux, reg, (व्योम *)data, 1);
			अगर (ret == 1) अणु
				अवरोध;
			पूर्ण अन्यथा अगर (retry < 4) अणु
				mdelay(50);
				जारी;
			पूर्ण अन्यथा अणु
				DRM_ERROR("DPCD write failed at:0x%x\n", reg);
				वापस false;
			पूर्ण
		पूर्ण
		val++; reg++; data++;
	पूर्ण

	val = 0;
	reg = LSPCON_MCA_AVI_IF_CTRL;
	ret = drm_dp_dpcd_पढ़ो(aux, reg, &val, 1);
	अगर (ret < 0) अणु
		DRM_ERROR("DPCD read failed, address 0x%x\n", reg);
		वापस false;
	पूर्ण

	/* Indicate LSPCON chip about infoframe, clear bit 1 and set bit 0 */
	val &= ~LSPCON_MCA_AVI_IF_HANDLED;
	val |= LSPCON_MCA_AVI_IF_KICKOFF;

	ret = drm_dp_dpcd_ग_लिखो(aux, reg, &val, 1);
	अगर (ret < 0) अणु
		DRM_ERROR("DPCD read failed, address 0x%x\n", reg);
		वापस false;
	पूर्ण

	val = 0;
	ret = drm_dp_dpcd_पढ़ो(aux, reg, &val, 1);
	अगर (ret < 0) अणु
		DRM_ERROR("DPCD read failed, address 0x%x\n", reg);
		वापस false;
	पूर्ण

	अगर (val == LSPCON_MCA_AVI_IF_HANDLED)
		DRM_DEBUG_KMS("AVI IF handled by FW\n");

	वापस true;
पूर्ण

व्योम lspcon_ग_लिखो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    अचिन्हित पूर्णांक type,
			    स्थिर व्योम *frame, sमाप_प्रकार len)
अणु
	bool ret = true;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	काष्ठा पूर्णांकel_lspcon *lspcon = enc_to_पूर्णांकel_lspcon(encoder);

	चयन (type) अणु
	हाल HDMI_INFOFRAME_TYPE_AVI:
		अगर (lspcon->venकरोr == LSPCON_VENDOR_MCA)
			ret = _lspcon_ग_लिखो_avi_infoframe_mca(&पूर्णांकel_dp->aux,
							      frame, len);
		अन्यथा
			ret = _lspcon_ग_लिखो_avi_infoframe_parade(&पूर्णांकel_dp->aux,
								 frame, len);
		अवरोध;
	हाल HDMI_PACKET_TYPE_GAMUT_METADATA:
		drm_dbg_kms(encoder->base.dev, "Update HDR metadata for lspcon\n");
		/* It uses the legacy hsw implementation क्रम the same */
		hsw_ग_लिखो_infoframe(encoder, crtc_state, type, frame, len);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (!ret) अणु
		DRM_ERROR("Failed to write infoframes\n");
		वापस;
	पूर्ण
पूर्ण

व्योम lspcon_पढ़ो_infoframe(काष्ठा पूर्णांकel_encoder *encoder,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   अचिन्हित पूर्णांक type,
			   व्योम *frame, sमाप_प्रकार len)
अणु
	/* FIXME implement क्रम AVI Infoframe as well */
	अगर (type == HDMI_PACKET_TYPE_GAMUT_METADATA)
		hsw_पढ़ो_infoframe(encoder, crtc_state, type,
				   frame, len);
पूर्ण

व्योम lspcon_set_infoframes(काष्ठा पूर्णांकel_encoder *encoder,
			   bool enable,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	sमाप_प्रकार ret;
	जोड़ hdmi_infoframe frame;
	u8 buf[VIDEO_DIP_DATA_SIZE];
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा पूर्णांकel_lspcon *lspcon = &dig_port->lspcon;
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;

	अगर (!lspcon->active) अणु
		DRM_ERROR("Writing infoframes while LSPCON disabled ?\n");
		वापस;
	पूर्ण

	/* FIXME precompute infoframes */

	ret = drm_hdmi_avi_infoframe_from_display_mode(&frame.avi,
						       conn_state->connector,
						       adjusted_mode);
	अगर (ret < 0) अणु
		DRM_ERROR("couldn't fill AVI infoframe\n");
		वापस;
	पूर्ण

	/*
	 * Currently there is no पूर्णांकerface defined to
	 * check user preference between RGB/YCBCR444
	 * or YCBCR420. So the only possible हाल क्रम
	 * YCBCR444 usage is driving YCBCR420 output
	 * with LSPCON, when pipe is configured क्रम
	 * YCBCR444 output and LSPCON takes care of
	 * करोwnsampling it.
	 */
	अगर (crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR444)
		frame.avi.colorspace = HDMI_COLORSPACE_YUV420;
	अन्यथा
		frame.avi.colorspace = HDMI_COLORSPACE_RGB;

	/* Set the Colorspace as per the HDMI spec */
	drm_hdmi_avi_infoframe_colorspace(&frame.avi, conn_state);

	/* nonsense combination */
	drm_WARN_ON(encoder->base.dev, crtc_state->limited_color_range &&
		    crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB);

	अगर (crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_RGB) अणु
		drm_hdmi_avi_infoframe_quant_range(&frame.avi,
						   conn_state->connector,
						   adjusted_mode,
						   crtc_state->limited_color_range ?
						   HDMI_QUANTIZATION_RANGE_LIMITED :
						   HDMI_QUANTIZATION_RANGE_FULL);
	पूर्ण अन्यथा अणु
		frame.avi.quantization_range = HDMI_QUANTIZATION_RANGE_DEFAULT;
		frame.avi.ycc_quantization_range = HDMI_YCC_QUANTIZATION_RANGE_LIMITED;
	पूर्ण

	drm_hdmi_avi_infoframe_content_type(&frame.avi, conn_state);

	ret = hdmi_infoframe_pack(&frame, buf, माप(buf));
	अगर (ret < 0) अणु
		DRM_ERROR("Failed to pack AVI IF\n");
		वापस;
	पूर्ण

	dig_port->ग_लिखो_infoframe(encoder, crtc_state, HDMI_INFOFRAME_TYPE_AVI,
				  buf, ret);
पूर्ण

अटल bool _lspcon_पढ़ो_avi_infoframe_enabled_mca(काष्ठा drm_dp_aux *aux)
अणु
	पूर्णांक ret;
	u32 val = 0;
	u16 reg = LSPCON_MCA_AVI_IF_CTRL;

	ret = drm_dp_dpcd_पढ़ो(aux, reg, &val, 1);
	अगर (ret < 0) अणु
		DRM_ERROR("DPCD read failed, address 0x%x\n", reg);
		वापस false;
	पूर्ण

	वापस val & LSPCON_MCA_AVI_IF_KICKOFF;
पूर्ण

अटल bool _lspcon_पढ़ो_avi_infoframe_enabled_parade(काष्ठा drm_dp_aux *aux)
अणु
	पूर्णांक ret;
	u32 val = 0;
	u16 reg = LSPCON_PARADE_AVI_IF_CTRL;

	ret = drm_dp_dpcd_पढ़ो(aux, reg, &val, 1);
	अगर (ret < 0) अणु
		DRM_ERROR("DPCD read failed, address 0x%x\n", reg);
		वापस false;
	पूर्ण

	वापस val & LSPCON_PARADE_AVI_IF_KICKOFF;
पूर्ण

u32 lspcon_infoframes_enabled(काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	काष्ठा पूर्णांकel_lspcon *lspcon = enc_to_पूर्णांकel_lspcon(encoder);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	bool infoframes_enabled;
	u32 val = 0;
	u32 mask, पंचांगp;

	अगर (lspcon->venकरोr == LSPCON_VENDOR_MCA)
		infoframes_enabled = _lspcon_पढ़ो_avi_infoframe_enabled_mca(&पूर्णांकel_dp->aux);
	अन्यथा
		infoframes_enabled = _lspcon_पढ़ो_avi_infoframe_enabled_parade(&पूर्णांकel_dp->aux);

	अगर (infoframes_enabled)
		val |= पूर्णांकel_hdmi_infoframe_enable(HDMI_INFOFRAME_TYPE_AVI);

	अगर (lspcon->hdr_supported) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
				    HSW_TVIDEO_DIP_CTL(pipe_config->cpu_transcoder));
		mask = VIDEO_DIP_ENABLE_GMP_HSW;

		अगर (पंचांगp & mask)
			val |= पूर्णांकel_hdmi_infoframe_enable(HDMI_PACKET_TYPE_GAMUT_METADATA);
	पूर्ण

	वापस val;
पूर्ण

व्योम lspcon_रुको_pcon_mode(काष्ठा पूर्णांकel_lspcon *lspcon)
अणु
	lspcon_रुको_mode(lspcon, DRM_LSPCON_MODE_PCON);
पूर्ण

bool lspcon_init(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा पूर्णांकel_dp *dp = &dig_port->dp;
	काष्ठा पूर्णांकel_lspcon *lspcon = &dig_port->lspcon;
	काष्ठा drm_connector *connector = &dp->attached_connector->base;

	lspcon->active = false;
	lspcon->mode = DRM_LSPCON_MODE_INVALID;

	अगर (!lspcon_probe(lspcon)) अणु
		DRM_ERROR("Failed to probe lspcon\n");
		वापस false;
	पूर्ण

	अगर (drm_dp_पढ़ो_dpcd_caps(&dp->aux, dp->dpcd) != 0) अणु
		DRM_ERROR("LSPCON DPCD read failed\n");
		वापस false;
	पूर्ण

	अगर (!lspcon_detect_venकरोr(lspcon)) अणु
		DRM_ERROR("LSPCON vendor detection failed\n");
		वापस false;
	पूर्ण

	connector->ycbcr_420_allowed = true;
	lspcon->active = true;
	DRM_DEBUG_KMS("Success: LSPCON init\n");
	वापस true;
पूर्ण

u32 पूर्णांकel_lspcon_infoframes_enabled(काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);

	वापस dig_port->infoframes_enabled(encoder, pipe_config);
पूर्ण

व्योम lspcon_resume(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा पूर्णांकel_lspcon *lspcon = &dig_port->lspcon;
	काष्ठा drm_device *dev = dig_port->base.base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत drm_lspcon_mode expected_mode;

	अगर (!पूर्णांकel_bios_is_lspcon_present(dev_priv, dig_port->base.port))
		वापस;

	अगर (!lspcon->active) अणु
		अगर (!lspcon_init(dig_port)) अणु
			DRM_ERROR("LSPCON init failed on port %c\n",
				  port_name(dig_port->base.port));
			वापस;
		पूर्ण
	पूर्ण

	अगर (lspcon_wake_native_aux_ch(lspcon)) अणु
		expected_mode = DRM_LSPCON_MODE_PCON;
		lspcon_resume_in_pcon_wa(lspcon);
	पूर्ण अन्यथा अणु
		expected_mode = DRM_LSPCON_MODE_LS;
	पूर्ण

	अगर (lspcon_रुको_mode(lspcon, expected_mode) == DRM_LSPCON_MODE_PCON)
		वापस;

	अगर (lspcon_change_mode(lspcon, DRM_LSPCON_MODE_PCON))
		DRM_ERROR("LSPCON resume failed\n");
	अन्यथा
		DRM_DEBUG_KMS("LSPCON resume success\n");
पूर्ण
