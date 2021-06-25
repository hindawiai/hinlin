<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright (C) 2017 Google, Inc.
 * Copyright _ 2017-2019, Intel Corporation.
 *
 * Authors:
 * Sean Paul <seanpaul@chromium.org>
 * Ramalingam C <ramalingam.c@पूर्णांकel.com>
 */

#समावेश <linux/component.h>
#समावेश <linux/i2c.h>
#समावेश <linux/अक्रमom.h>

#समावेश <drm/drm_hdcp.h>
#समावेश <drm/i915_component.h>

#समावेश "i915_drv.h"
#समावेश "i915_reg.h"
#समावेश "intel_display_power.h"
#समावेश "intel_display_types.h"
#समावेश "intel_hdcp.h"
#समावेश "intel_sideband.h"
#समावेश "intel_connector.h"

#घोषणा KEY_LOAD_TRIES	5
#घोषणा HDCP2_LC_RETRY_CNT			3

अटल पूर्णांक पूर्णांकel_conn_to_vcpi(काष्ठा पूर्णांकel_connector *connector)
अणु
	/* For HDMI this is क्रमced to be 0x0. For DP SST also this is 0x0. */
	वापस connector->port	? connector->port->vcpi.vcpi : 0;
पूर्ण

अटल bool
पूर्णांकel_streams_type1_capable(काष्ठा पूर्णांकel_connector *connector)
अणु
	स्थिर काष्ठा पूर्णांकel_hdcp_shim *shim = connector->hdcp.shim;
	bool capable = false;

	अगर (!shim)
		वापस capable;

	अगर (shim->streams_type1_capable)
		shim->streams_type1_capable(connector, &capable);

	वापस capable;
पूर्ण

/*
 * पूर्णांकel_hdcp_required_content_stream selects the most highest common possible HDCP
 * content_type क्रम all streams in DP MST topology because security f/w करोesn't
 * have any provision to mark content_type क्रम each stream separately, it marks
 * all available streams with the content_type proivided at the समय of port
 * authentication. This may prohibit the userspace to use type1 content on
 * HDCP 2.2 capable sink because of other sink are not capable of HDCP 2.2 in
 * DP MST topology. Though it is not compulsory, security fw should change its
 * policy to mark dअगरferent content_types क्रम dअगरferent streams.
 */
अटल पूर्णांक
पूर्णांकel_hdcp_required_content_stream(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा पूर्णांकel_digital_port *conn_dig_port;
	काष्ठा पूर्णांकel_connector *connector;
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	काष्ठा hdcp_port_data *data = &dig_port->hdcp_port_data;
	bool enक्रमce_type0 = false;
	पूर्णांक k;

	data->k = 0;

	अगर (dig_port->hdcp_auth_status)
		वापस 0;

	drm_connector_list_iter_begin(&i915->drm, &conn_iter);
	क्रम_each_पूर्णांकel_connector_iter(connector, &conn_iter) अणु
		अगर (connector->base.status == connector_status_disconnected)
			जारी;

		अगर (!पूर्णांकel_encoder_is_mst(पूर्णांकel_attached_encoder(connector)))
			जारी;

		conn_dig_port = पूर्णांकel_attached_dig_port(connector);
		अगर (conn_dig_port != dig_port)
			जारी;

		अगर (!enक्रमce_type0 && !पूर्णांकel_streams_type1_capable(connector))
			enक्रमce_type0 = true;

		data->streams[data->k].stream_id = पूर्णांकel_conn_to_vcpi(connector);
		data->k++;

		/* अगर there is only one active stream */
		अगर (dig_port->dp.active_mst_links <= 1)
			अवरोध;
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	अगर (drm_WARN_ON(&i915->drm, data->k > INTEL_NUM_PIPES(i915) || data->k == 0))
		वापस -EINVAL;

	/*
	 * Apply common protection level across all streams in DP MST Topology.
	 * Use highest supported content type क्रम all streams in DP MST Topology.
	 */
	क्रम (k = 0; k < data->k; k++)
		data->streams[k].stream_type =
			enक्रमce_type0 ? DRM_MODE_HDCP_CONTENT_TYPE0 : DRM_MODE_HDCP_CONTENT_TYPE1;

	वापस 0;
पूर्ण

अटल
bool पूर्णांकel_hdcp_is_ksv_valid(u8 *ksv)
अणु
	पूर्णांक i, ones = 0;
	/* KSV has 20 1's and 20 0's */
	क्रम (i = 0; i < DRM_HDCP_KSV_LEN; i++)
		ones += hweight8(ksv[i]);
	अगर (ones != 20)
		वापस false;

	वापस true;
पूर्ण

अटल
पूर्णांक पूर्णांकel_hdcp_पढ़ो_valid_bksv(काष्ठा पूर्णांकel_digital_port *dig_port,
			       स्थिर काष्ठा पूर्णांकel_hdcp_shim *shim, u8 *bksv)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	पूर्णांक ret, i, tries = 2;

	/* HDCP spec states that we must retry the bksv अगर it is invalid */
	क्रम (i = 0; i < tries; i++) अणु
		ret = shim->पढ़ो_bksv(dig_port, bksv);
		अगर (ret)
			वापस ret;
		अगर (पूर्णांकel_hdcp_is_ksv_valid(bksv))
			अवरोध;
	पूर्ण
	अगर (i == tries) अणु
		drm_dbg_kms(&i915->drm, "Bksv is invalid\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/* Is HDCP1.4 capable on Platक्रमm and Sink */
bool पूर्णांकel_hdcp_capable(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	स्थिर काष्ठा पूर्णांकel_hdcp_shim *shim = connector->hdcp.shim;
	bool capable = false;
	u8 bksv[5];

	अगर (!shim)
		वापस capable;

	अगर (shim->hdcp_capable) अणु
		shim->hdcp_capable(dig_port, &capable);
	पूर्ण अन्यथा अणु
		अगर (!पूर्णांकel_hdcp_पढ़ो_valid_bksv(dig_port, shim, bksv))
			capable = true;
	पूर्ण

	वापस capable;
पूर्ण

/* Is HDCP2.2 capable on Platक्रमm and Sink */
bool पूर्णांकel_hdcp2_capable(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	bool capable = false;

	/* I915 support क्रम HDCP2.2 */
	अगर (!hdcp->hdcp2_supported)
		वापस false;

	/* MEI पूर्णांकerface is solid */
	mutex_lock(&dev_priv->hdcp_comp_mutex);
	अगर (!dev_priv->hdcp_comp_added ||  !dev_priv->hdcp_master) अणु
		mutex_unlock(&dev_priv->hdcp_comp_mutex);
		वापस false;
	पूर्ण
	mutex_unlock(&dev_priv->hdcp_comp_mutex);

	/* Sink's capability क्रम HDCP2.2 */
	hdcp->shim->hdcp_2_2_capable(dig_port, &capable);

	वापस capable;
पूर्ण

अटल bool पूर्णांकel_hdcp_in_use(काष्ठा drm_i915_निजी *dev_priv,
			      क्रमागत transcoder cpu_transcoder, क्रमागत port port)
अणु
	वापस पूर्णांकel_de_पढ़ो(dev_priv,
	                     HDCP_STATUS(dev_priv, cpu_transcoder, port)) &
	       HDCP_STATUS_ENC;
पूर्ण

अटल bool पूर्णांकel_hdcp2_in_use(काष्ठा drm_i915_निजी *dev_priv,
			       क्रमागत transcoder cpu_transcoder, क्रमागत port port)
अणु
	वापस पूर्णांकel_de_पढ़ो(dev_priv,
	                     HDCP2_STATUS(dev_priv, cpu_transcoder, port)) &
	       LINK_ENCRYPTION_STATUS;
पूर्ण

अटल पूर्णांक पूर्णांकel_hdcp_poll_ksv_fअगरo(काष्ठा पूर्णांकel_digital_port *dig_port,
				    स्थिर काष्ठा पूर्णांकel_hdcp_shim *shim)
अणु
	पूर्णांक ret, पढ़ो_ret;
	bool ksv_पढ़ोy;

	/* Poll क्रम ksv list पढ़ोy (spec says max समय allowed is 5s) */
	ret = __रुको_क्रम(पढ़ो_ret = shim->पढ़ो_ksv_पढ़ोy(dig_port,
							 &ksv_पढ़ोy),
			 पढ़ो_ret || ksv_पढ़ोy, 5 * 1000 * 1000, 1000,
			 100 * 1000);
	अगर (ret)
		वापस ret;
	अगर (पढ़ो_ret)
		वापस पढ़ो_ret;
	अगर (!ksv_पढ़ोy)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल bool hdcp_key_loadable(काष्ठा drm_i915_निजी *dev_priv)
अणु
	क्रमागत i915_घातer_well_id id;
	पूर्णांकel_wakeref_t wakeref;
	bool enabled = false;

	/*
	 * On HSW and BDW, Display HW loads the Key as soon as Display resumes.
	 * On all BXT+, SW can load the keys only when the PW#1 is turned on.
	 */
	अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		id = HSW_DISP_PW_GLOBAL;
	अन्यथा
		id = SKL_DISP_PW_1;

	/* PG1 (घातer well #1) needs to be enabled */
	with_पूर्णांकel_runसमय_pm(&dev_priv->runसमय_pm, wakeref)
		enabled = पूर्णांकel_display_घातer_well_is_enabled(dev_priv, id);

	/*
	 * Another req क्रम hdcp key loadability is enabled state of pll क्रम
	 * cdclk. Without active crtc we wont land here. So we are assuming that
	 * cdclk is alपढ़ोy on.
	 */

	वापस enabled;
पूर्ण

अटल व्योम पूर्णांकel_hdcp_clear_keys(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_KEY_CONF, HDCP_CLEAR_KEYS_TRIGGER);
	पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_KEY_STATUS,
		       HDCP_KEY_LOAD_DONE | HDCP_KEY_LOAD_STATUS | HDCP_FUSE_IN_PROGRESS | HDCP_FUSE_ERROR | HDCP_FUSE_DONE);
पूर्ण

अटल पूर्णांक पूर्णांकel_hdcp_load_keys(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक ret;
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, HDCP_KEY_STATUS);
	अगर ((val & HDCP_KEY_LOAD_DONE) && (val & HDCP_KEY_LOAD_STATUS))
		वापस 0;

	/*
	 * On HSW and BDW HW loads the HDCP1.4 Key when Display comes
	 * out of reset. So अगर Key is not alपढ़ोy loaded, its an error state.
	 */
	अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		अगर (!(पूर्णांकel_de_पढ़ो(dev_priv, HDCP_KEY_STATUS) & HDCP_KEY_LOAD_DONE))
			वापस -ENXIO;

	/*
	 * Initiate loading the HDCP key from fuses.
	 *
	 * BXT+ platक्रमms, HDCP key needs to be loaded by SW. Only Gen 9
	 * platक्रमms except BXT and GLK, dअगरfer in the key load trigger process
	 * from other platक्रमms. So GEN9_BC uses the GT Driver Mailbox i/f.
	 */
	अगर (IS_GEN9_BC(dev_priv)) अणु
		ret = sandybridge_pcode_ग_लिखो(dev_priv,
					      SKL_PCODE_LOAD_HDCP_KEYS, 1);
		अगर (ret) अणु
			drm_err(&dev_priv->drm,
				"Failed to initiate HDCP key load (%d)\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_KEY_CONF, HDCP_KEY_LOAD_TRIGGER);
	पूर्ण

	/* Wait क्रम the keys to load (500us) */
	ret = __पूर्णांकel_रुको_क्रम_रेजिस्टर(&dev_priv->uncore, HDCP_KEY_STATUS,
					HDCP_KEY_LOAD_DONE, HDCP_KEY_LOAD_DONE,
					10, 1, &val);
	अगर (ret)
		वापस ret;
	अन्यथा अगर (!(val & HDCP_KEY_LOAD_STATUS))
		वापस -ENXIO;

	/* Send Aksv over to PCH display क्रम use in authentication */
	पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_KEY_CONF, HDCP_AKSV_SEND_TRIGGER);

	वापस 0;
पूर्ण

/* Returns updated SHA-1 index */
अटल पूर्णांक पूर्णांकel_ग_लिखो_sha_text(काष्ठा drm_i915_निजी *dev_priv, u32 sha_text)
अणु
	पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_SHA_TEXT, sha_text);
	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, HDCP_REP_CTL, HDCP_SHA1_READY, 1)) अणु
		drm_err(&dev_priv->drm, "Timed out waiting for SHA1 ready\n");
		वापस -ETIMEDOUT;
	पूर्ण
	वापस 0;
पूर्ण

अटल
u32 पूर्णांकel_hdcp_get_repeater_ctl(काष्ठा drm_i915_निजी *dev_priv,
				क्रमागत transcoder cpu_transcoder, क्रमागत port port)
अणु
	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		चयन (cpu_transcoder) अणु
		हाल TRANSCODER_A:
			वापस HDCP_TRANSA_REP_PRESENT |
			       HDCP_TRANSA_SHA1_M0;
		हाल TRANSCODER_B:
			वापस HDCP_TRANSB_REP_PRESENT |
			       HDCP_TRANSB_SHA1_M0;
		हाल TRANSCODER_C:
			वापस HDCP_TRANSC_REP_PRESENT |
			       HDCP_TRANSC_SHA1_M0;
		हाल TRANSCODER_D:
			वापस HDCP_TRANSD_REP_PRESENT |
			       HDCP_TRANSD_SHA1_M0;
		शेष:
			drm_err(&dev_priv->drm, "Unknown transcoder %d\n",
				cpu_transcoder);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	चयन (port) अणु
	हाल PORT_A:
		वापस HDCP_DDIA_REP_PRESENT | HDCP_DDIA_SHA1_M0;
	हाल PORT_B:
		वापस HDCP_DDIB_REP_PRESENT | HDCP_DDIB_SHA1_M0;
	हाल PORT_C:
		वापस HDCP_DDIC_REP_PRESENT | HDCP_DDIC_SHA1_M0;
	हाल PORT_D:
		वापस HDCP_DDID_REP_PRESENT | HDCP_DDID_SHA1_M0;
	हाल PORT_E:
		वापस HDCP_DDIE_REP_PRESENT | HDCP_DDIE_SHA1_M0;
	शेष:
		drm_err(&dev_priv->drm, "Unknown port %d\n", port);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल
पूर्णांक पूर्णांकel_hdcp_validate_v_prime(काष्ठा पूर्णांकel_connector *connector,
				स्थिर काष्ठा पूर्णांकel_hdcp_shim *shim,
				u8 *ksv_fअगरo, u8 num_करोwnstream, u8 *bstatus)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	क्रमागत transcoder cpu_transcoder = connector->hdcp.cpu_transcoder;
	क्रमागत port port = dig_port->base.port;
	u32 vprime, sha_text, sha_leftovers, rep_ctl;
	पूर्णांक ret, i, j, sha_idx;

	/* Process V' values from the receiver */
	क्रम (i = 0; i < DRM_HDCP_V_PRIME_NUM_PARTS; i++) अणु
		ret = shim->पढ़ो_v_prime_part(dig_port, i, &vprime);
		अगर (ret)
			वापस ret;
		पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_SHA_V_PRIME(i), vprime);
	पूर्ण

	/*
	 * We need to ग_लिखो the concatenation of all device KSVs, BINFO (DP) ||
	 * BSTATUS (HDMI), and M0 (which is added via HDCP_REP_CTL). This byte
	 * stream is written via the HDCP_SHA_TEXT रेजिस्टर in 32-bit
	 * increments. Every 64 bytes, we need to ग_लिखो HDCP_REP_CTL again. This
	 * index will keep track of our progress through the 64 bytes as well as
	 * helping us work the 40-bit KSVs through our 32-bit रेजिस्टर.
	 *
	 * NOTE: data passed via HDCP_SHA_TEXT should be big-endian
	 */
	sha_idx = 0;
	sha_text = 0;
	sha_leftovers = 0;
	rep_ctl = पूर्णांकel_hdcp_get_repeater_ctl(dev_priv, cpu_transcoder, port);
	पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL, rep_ctl | HDCP_SHA1_TEXT_32);
	क्रम (i = 0; i < num_करोwnstream; i++) अणु
		अचिन्हित पूर्णांक sha_empty;
		u8 *ksv = &ksv_fअगरo[i * DRM_HDCP_KSV_LEN];

		/* Fill up the empty slots in sha_text and ग_लिखो it out */
		sha_empty = माप(sha_text) - sha_leftovers;
		क्रम (j = 0; j < sha_empty; j++) अणु
			u8 off = ((माप(sha_text) - j - 1 - sha_leftovers) * 8);
			sha_text |= ksv[j] << off;
		पूर्ण

		ret = पूर्णांकel_ग_लिखो_sha_text(dev_priv, sha_text);
		अगर (ret < 0)
			वापस ret;

		/* Programming guide ग_लिखोs this every 64 bytes */
		sha_idx += माप(sha_text);
		अगर (!(sha_idx % 64))
			पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL,
				       rep_ctl | HDCP_SHA1_TEXT_32);

		/* Store the leftover bytes from the ksv in sha_text */
		sha_leftovers = DRM_HDCP_KSV_LEN - sha_empty;
		sha_text = 0;
		क्रम (j = 0; j < sha_leftovers; j++)
			sha_text |= ksv[sha_empty + j] <<
					((माप(sha_text) - j - 1) * 8);

		/*
		 * If we still have room in sha_text क्रम more data, जारी.
		 * Otherwise, ग_लिखो it out immediately.
		 */
		अगर (माप(sha_text) > sha_leftovers)
			जारी;

		ret = पूर्णांकel_ग_लिखो_sha_text(dev_priv, sha_text);
		अगर (ret < 0)
			वापस ret;
		sha_leftovers = 0;
		sha_text = 0;
		sha_idx += माप(sha_text);
	पूर्ण

	/*
	 * We need to ग_लिखो BINFO/BSTATUS, and M0 now. Depending on how many
	 * bytes are leftover from the last ksv, we might be able to fit them
	 * all in sha_text (first 2 हालs), or we might need to split them up
	 * पूर्णांकo 2 ग_लिखोs (last 2 हालs).
	 */
	अगर (sha_leftovers == 0) अणु
		/* Write 16 bits of text, 16 bits of M0 */
		पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL,
			       rep_ctl | HDCP_SHA1_TEXT_16);
		ret = पूर्णांकel_ग_लिखो_sha_text(dev_priv,
					   bstatus[0] << 8 | bstatus[1]);
		अगर (ret < 0)
			वापस ret;
		sha_idx += माप(sha_text);

		/* Write 32 bits of M0 */
		पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL,
			       rep_ctl | HDCP_SHA1_TEXT_0);
		ret = पूर्णांकel_ग_लिखो_sha_text(dev_priv, 0);
		अगर (ret < 0)
			वापस ret;
		sha_idx += माप(sha_text);

		/* Write 16 bits of M0 */
		पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL,
			       rep_ctl | HDCP_SHA1_TEXT_16);
		ret = पूर्णांकel_ग_लिखो_sha_text(dev_priv, 0);
		अगर (ret < 0)
			वापस ret;
		sha_idx += माप(sha_text);

	पूर्ण अन्यथा अगर (sha_leftovers == 1) अणु
		/* Write 24 bits of text, 8 bits of M0 */
		पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL,
			       rep_ctl | HDCP_SHA1_TEXT_24);
		sha_text |= bstatus[0] << 16 | bstatus[1] << 8;
		/* Only 24-bits of data, must be in the LSB */
		sha_text = (sha_text & 0xffffff00) >> 8;
		ret = पूर्णांकel_ग_लिखो_sha_text(dev_priv, sha_text);
		अगर (ret < 0)
			वापस ret;
		sha_idx += माप(sha_text);

		/* Write 32 bits of M0 */
		पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL,
			       rep_ctl | HDCP_SHA1_TEXT_0);
		ret = पूर्णांकel_ग_लिखो_sha_text(dev_priv, 0);
		अगर (ret < 0)
			वापस ret;
		sha_idx += माप(sha_text);

		/* Write 24 bits of M0 */
		पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL,
			       rep_ctl | HDCP_SHA1_TEXT_8);
		ret = पूर्णांकel_ग_लिखो_sha_text(dev_priv, 0);
		अगर (ret < 0)
			वापस ret;
		sha_idx += माप(sha_text);

	पूर्ण अन्यथा अगर (sha_leftovers == 2) अणु
		/* Write 32 bits of text */
		पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL,
			       rep_ctl | HDCP_SHA1_TEXT_32);
		sha_text |= bstatus[0] << 8 | bstatus[1];
		ret = पूर्णांकel_ग_लिखो_sha_text(dev_priv, sha_text);
		अगर (ret < 0)
			वापस ret;
		sha_idx += माप(sha_text);

		/* Write 64 bits of M0 */
		पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL,
			       rep_ctl | HDCP_SHA1_TEXT_0);
		क्रम (i = 0; i < 2; i++) अणु
			ret = पूर्णांकel_ग_लिखो_sha_text(dev_priv, 0);
			अगर (ret < 0)
				वापस ret;
			sha_idx += माप(sha_text);
		पूर्ण

		/*
		 * Terminate the SHA-1 stream by hand. For the other leftover
		 * हालs this is appended by the hardware.
		 */
		पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL,
			       rep_ctl | HDCP_SHA1_TEXT_32);
		sha_text = DRM_HDCP_SHA1_TERMINATOR << 24;
		ret = पूर्णांकel_ग_लिखो_sha_text(dev_priv, sha_text);
		अगर (ret < 0)
			वापस ret;
		sha_idx += माप(sha_text);
	पूर्ण अन्यथा अगर (sha_leftovers == 3) अणु
		/* Write 32 bits of text (filled from LSB) */
		पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL,
			       rep_ctl | HDCP_SHA1_TEXT_32);
		sha_text |= bstatus[0];
		ret = पूर्णांकel_ग_लिखो_sha_text(dev_priv, sha_text);
		अगर (ret < 0)
			वापस ret;
		sha_idx += माप(sha_text);

		/* Write 8 bits of text (filled from LSB), 24 bits of M0 */
		पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL,
			       rep_ctl | HDCP_SHA1_TEXT_8);
		ret = पूर्णांकel_ग_लिखो_sha_text(dev_priv, bstatus[1]);
		अगर (ret < 0)
			वापस ret;
		sha_idx += माप(sha_text);

		/* Write 32 bits of M0 */
		पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL,
			       rep_ctl | HDCP_SHA1_TEXT_0);
		ret = पूर्णांकel_ग_लिखो_sha_text(dev_priv, 0);
		अगर (ret < 0)
			वापस ret;
		sha_idx += माप(sha_text);

		/* Write 8 bits of M0 */
		पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL,
			       rep_ctl | HDCP_SHA1_TEXT_24);
		ret = पूर्णांकel_ग_लिखो_sha_text(dev_priv, 0);
		अगर (ret < 0)
			वापस ret;
		sha_idx += माप(sha_text);
	पूर्ण अन्यथा अणु
		drm_dbg_kms(&dev_priv->drm, "Invalid number of leftovers %d\n",
			    sha_leftovers);
		वापस -EINVAL;
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL, rep_ctl | HDCP_SHA1_TEXT_32);
	/* Fill up to 64-4 bytes with zeros (leave the last ग_लिखो क्रम length) */
	जबतक ((sha_idx % 64) < (64 - माप(sha_text))) अणु
		ret = पूर्णांकel_ग_लिखो_sha_text(dev_priv, 0);
		अगर (ret < 0)
			वापस ret;
		sha_idx += माप(sha_text);
	पूर्ण

	/*
	 * Last ग_लिखो माला_लो the length of the concatenation in bits. That is:
	 *  - 5 bytes per device
	 *  - 10 bytes क्रम BINFO/BSTATUS(2), M0(8)
	 */
	sha_text = (num_करोwnstream * 5 + 10) * 8;
	ret = पूर्णांकel_ग_लिखो_sha_text(dev_priv, sha_text);
	अगर (ret < 0)
		वापस ret;

	/* Tell the HW we're करोne with the hash and रुको क्रम it to ACK */
	पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL,
		       rep_ctl | HDCP_SHA1_COMPLETE_HASH);
	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, HDCP_REP_CTL,
				  HDCP_SHA1_COMPLETE, 1)) अणु
		drm_err(&dev_priv->drm, "Timed out waiting for SHA1 complete\n");
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (!(पूर्णांकel_de_पढ़ो(dev_priv, HDCP_REP_CTL) & HDCP_SHA1_V_MATCH)) अणु
		drm_dbg_kms(&dev_priv->drm, "SHA-1 mismatch, HDCP failed\n");
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

/* Implements Part 2 of the HDCP authorization procedure */
अटल
पूर्णांक पूर्णांकel_hdcp_auth_करोwnstream(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	स्थिर काष्ठा पूर्णांकel_hdcp_shim *shim = connector->hdcp.shim;
	u8 bstatus[2], num_करोwnstream, *ksv_fअगरo;
	पूर्णांक ret, i, tries = 3;

	ret = पूर्णांकel_hdcp_poll_ksv_fअगरo(dig_port, shim);
	अगर (ret) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "KSV list failed to become ready (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = shim->पढ़ो_bstatus(dig_port, bstatus);
	अगर (ret)
		वापस ret;

	अगर (DRM_HDCP_MAX_DEVICE_EXCEEDED(bstatus[0]) ||
	    DRM_HDCP_MAX_CASCADE_EXCEEDED(bstatus[1])) अणु
		drm_dbg_kms(&dev_priv->drm, "Max Topology Limit Exceeded\n");
		वापस -EPERM;
	पूर्ण

	/*
	 * When repeater reports 0 device count, HDCP1.4 spec allows disabling
	 * the HDCP encryption. That implies that repeater can't have its own
	 * display. As there is no consumption of encrypted content in the
	 * repeater with 0 करोwnstream devices, we are failing the
	 * authentication.
	 */
	num_करोwnstream = DRM_HDCP_NUM_DOWNSTREAM(bstatus[0]);
	अगर (num_करोwnstream == 0) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Repeater with zero downstream devices\n");
		वापस -EINVAL;
	पूर्ण

	ksv_fअगरo = kसुस्मृति(DRM_HDCP_KSV_LEN, num_करोwnstream, GFP_KERNEL);
	अगर (!ksv_fअगरo) अणु
		drm_dbg_kms(&dev_priv->drm, "Out of mem: ksv_fifo\n");
		वापस -ENOMEM;
	पूर्ण

	ret = shim->पढ़ो_ksv_fअगरo(dig_port, num_करोwnstream, ksv_fअगरo);
	अगर (ret)
		जाओ err;

	अगर (drm_hdcp_check_ksvs_revoked(&dev_priv->drm, ksv_fअगरo,
					num_करोwnstream) > 0) अणु
		drm_err(&dev_priv->drm, "Revoked Ksv(s) in ksv_fifo\n");
		ret = -EPERM;
		जाओ err;
	पूर्ण

	/*
	 * When V prime mismatches, DP Spec mandates re-पढ़ो of
	 * V prime atleast twice.
	 */
	क्रम (i = 0; i < tries; i++) अणु
		ret = पूर्णांकel_hdcp_validate_v_prime(connector, shim,
						  ksv_fअगरo, num_करोwnstream,
						  bstatus);
		अगर (!ret)
			अवरोध;
	पूर्ण

	अगर (i == tries) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "V Prime validation failed.(%d)\n", ret);
		जाओ err;
	पूर्ण

	drm_dbg_kms(&dev_priv->drm, "HDCP is enabled (%d downstream devices)\n",
		    num_करोwnstream);
	ret = 0;
err:
	kमुक्त(ksv_fअगरo);
	वापस ret;
पूर्ण

/* Implements Part 1 of the HDCP authorization procedure */
अटल पूर्णांक पूर्णांकel_hdcp_auth(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	स्थिर काष्ठा पूर्णांकel_hdcp_shim *shim = hdcp->shim;
	क्रमागत transcoder cpu_transcoder = connector->hdcp.cpu_transcoder;
	क्रमागत port port = dig_port->base.port;
	अचिन्हित दीर्घ r0_prime_gen_start;
	पूर्णांक ret, i, tries = 2;
	जोड़ अणु
		u32 reg[2];
		u8 shim[DRM_HDCP_AN_LEN];
	पूर्ण an;
	जोड़ अणु
		u32 reg[2];
		u8 shim[DRM_HDCP_KSV_LEN];
	पूर्ण bksv;
	जोड़ अणु
		u32 reg;
		u8 shim[DRM_HDCP_RI_LEN];
	पूर्ण ri;
	bool repeater_present, hdcp_capable;

	/*
	 * Detects whether the display is HDCP capable. Although we check क्रम
	 * valid Bksv below, the HDCP over DP spec requires that we check
	 * whether the display supports HDCP beक्रमe we ग_लिखो An. For HDMI
	 * displays, this is not necessary.
	 */
	अगर (shim->hdcp_capable) अणु
		ret = shim->hdcp_capable(dig_port, &hdcp_capable);
		अगर (ret)
			वापस ret;
		अगर (!hdcp_capable) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "Panel is not HDCP capable\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Initialize An with 2 अक्रमom values and acquire it */
	क्रम (i = 0; i < 2; i++)
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       HDCP_ANINIT(dev_priv, cpu_transcoder, port),
			       get_अक्रमom_u32());
	पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_CONF(dev_priv, cpu_transcoder, port),
		       HDCP_CONF_CAPTURE_AN);

	/* Wait क्रम An to be acquired */
	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv,
				  HDCP_STATUS(dev_priv, cpu_transcoder, port),
				  HDCP_STATUS_AN_READY, 1)) अणु
		drm_err(&dev_priv->drm, "Timed out waiting for An\n");
		वापस -ETIMEDOUT;
	पूर्ण

	an.reg[0] = पूर्णांकel_de_पढ़ो(dev_priv,
				  HDCP_ANLO(dev_priv, cpu_transcoder, port));
	an.reg[1] = पूर्णांकel_de_पढ़ो(dev_priv,
				  HDCP_ANHI(dev_priv, cpu_transcoder, port));
	ret = shim->ग_लिखो_an_aksv(dig_port, an.shim);
	अगर (ret)
		वापस ret;

	r0_prime_gen_start = jअगरfies;

	स_रखो(&bksv, 0, माप(bksv));

	ret = पूर्णांकel_hdcp_पढ़ो_valid_bksv(dig_port, shim, bksv.shim);
	अगर (ret < 0)
		वापस ret;

	अगर (drm_hdcp_check_ksvs_revoked(&dev_priv->drm, bksv.shim, 1) > 0) अणु
		drm_err(&dev_priv->drm, "BKSV is revoked\n");
		वापस -EPERM;
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_BKSVLO(dev_priv, cpu_transcoder, port),
		       bksv.reg[0]);
	पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_BKSVHI(dev_priv, cpu_transcoder, port),
		       bksv.reg[1]);

	ret = shim->repeater_present(dig_port, &repeater_present);
	अगर (ret)
		वापस ret;
	अगर (repeater_present)
		पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL,
			       पूर्णांकel_hdcp_get_repeater_ctl(dev_priv, cpu_transcoder, port));

	ret = shim->toggle_संकेतling(dig_port, cpu_transcoder, true);
	अगर (ret)
		वापस ret;

	पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_CONF(dev_priv, cpu_transcoder, port),
		       HDCP_CONF_AUTH_AND_ENC);

	/* Wait क्रम R0 पढ़ोy */
	अगर (रुको_क्रम(पूर्णांकel_de_पढ़ो(dev_priv, HDCP_STATUS(dev_priv, cpu_transcoder, port)) &
		     (HDCP_STATUS_R0_READY | HDCP_STATUS_ENC), 1)) अणु
		drm_err(&dev_priv->drm, "Timed out waiting for R0 ready\n");
		वापस -ETIMEDOUT;
	पूर्ण

	/*
	 * Wait क्रम R0' to become available. The spec says 100ms from Aksv, but
	 * some monitors can take दीर्घer than this. We'll set the समयout at
	 * 300ms just to be sure.
	 *
	 * On DP, there's an R0_READY bit available but no such bit
	 * exists on HDMI. Since the upper-bound is the same, we'll just करो
	 * the stupid thing instead of polling on one and not the other.
	 */
	रुको_reमुख्यing_ms_from_jअगरfies(r0_prime_gen_start, 300);

	tries = 3;

	/*
	 * DP HDCP Spec mandates the two more reattempt to पढ़ो R0, inहाल
	 * of R0 mismatch.
	 */
	क्रम (i = 0; i < tries; i++) अणु
		ri.reg = 0;
		ret = shim->पढ़ो_ri_prime(dig_port, ri.shim);
		अगर (ret)
			वापस ret;
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       HDCP_RPRIME(dev_priv, cpu_transcoder, port),
			       ri.reg);

		/* Wait क्रम Ri prime match */
		अगर (!रुको_क्रम(पूर्णांकel_de_पढ़ो(dev_priv, HDCP_STATUS(dev_priv, cpu_transcoder, port)) &
			      (HDCP_STATUS_RI_MATCH | HDCP_STATUS_ENC), 1))
			अवरोध;
	पूर्ण

	अगर (i == tries) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Timed out waiting for Ri prime match (%x)\n",
			    पूर्णांकel_de_पढ़ो(dev_priv, HDCP_STATUS(dev_priv,
					  cpu_transcoder, port)));
		वापस -ETIMEDOUT;
	पूर्ण

	/* Wait क्रम encryption confirmation */
	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv,
				  HDCP_STATUS(dev_priv, cpu_transcoder, port),
				  HDCP_STATUS_ENC,
				  HDCP_ENCRYPT_STATUS_CHANGE_TIMEOUT_MS)) अणु
		drm_err(&dev_priv->drm, "Timed out waiting for encryption\n");
		वापस -ETIMEDOUT;
	पूर्ण

	/* DP MST Auth Part 1 Step 2.a and Step 2.b */
	अगर (shim->stream_encryption) अणु
		ret = shim->stream_encryption(connector, true);
		अगर (ret) अणु
			drm_err(&dev_priv->drm, "[%s:%d] Failed to enable HDCP 1.4 stream enc\n",
				connector->base.name, connector->base.base.id);
			वापस ret;
		पूर्ण
		drm_dbg_kms(&dev_priv->drm, "HDCP 1.4 transcoder: %s stream encrypted\n",
			    transcoder_name(hdcp->stream_transcoder));
	पूर्ण

	अगर (repeater_present)
		वापस पूर्णांकel_hdcp_auth_करोwnstream(connector);

	drm_dbg_kms(&dev_priv->drm, "HDCP is enabled (no repeater present)\n");
	वापस 0;
पूर्ण

अटल पूर्णांक _पूर्णांकel_hdcp_disable(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	क्रमागत port port = dig_port->base.port;
	क्रमागत transcoder cpu_transcoder = hdcp->cpu_transcoder;
	u32 repeater_ctl;
	पूर्णांक ret;

	drm_dbg_kms(&dev_priv->drm, "[%s:%d] HDCP is being disabled...\n",
		    connector->base.name, connector->base.base.id);

	अगर (hdcp->shim->stream_encryption) अणु
		ret = hdcp->shim->stream_encryption(connector, false);
		अगर (ret) अणु
			drm_err(&dev_priv->drm, "[%s:%d] Failed to disable HDCP 1.4 stream enc\n",
				connector->base.name, connector->base.base.id);
			वापस ret;
		पूर्ण
		drm_dbg_kms(&dev_priv->drm, "HDCP 1.4 transcoder: %s stream encryption disabled\n",
			    transcoder_name(hdcp->stream_transcoder));
		/*
		 * If there are other connectors on this port using HDCP,
		 * करोn't disable it until it disabled HDCP encryption क्रम
		 * all connectors in MST topology.
		 */
		अगर (dig_port->num_hdcp_streams > 0)
			वापस 0;
	पूर्ण

	hdcp->hdcp_encrypted = false;
	पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_CONF(dev_priv, cpu_transcoder, port), 0);
	अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv,
				    HDCP_STATUS(dev_priv, cpu_transcoder, port),
				    ~0, HDCP_ENCRYPT_STATUS_CHANGE_TIMEOUT_MS)) अणु
		drm_err(&dev_priv->drm,
			"Failed to disable HDCP, timeout clearing status\n");
		वापस -ETIMEDOUT;
	पूर्ण

	repeater_ctl = पूर्णांकel_hdcp_get_repeater_ctl(dev_priv, cpu_transcoder,
						   port);
	पूर्णांकel_de_ग_लिखो(dev_priv, HDCP_REP_CTL,
		       पूर्णांकel_de_पढ़ो(dev_priv, HDCP_REP_CTL) & ~repeater_ctl);

	ret = hdcp->shim->toggle_संकेतling(dig_port, cpu_transcoder, false);
	अगर (ret) अणु
		drm_err(&dev_priv->drm, "Failed to disable HDCP signalling\n");
		वापस ret;
	पूर्ण

	drm_dbg_kms(&dev_priv->drm, "HDCP is disabled\n");
	वापस 0;
पूर्ण

अटल पूर्णांक _पूर्णांकel_hdcp_enable(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	पूर्णांक i, ret, tries = 3;

	drm_dbg_kms(&dev_priv->drm, "[%s:%d] HDCP is being enabled...\n",
		    connector->base.name, connector->base.base.id);

	अगर (!hdcp_key_loadable(dev_priv)) अणु
		drm_err(&dev_priv->drm, "HDCP key Load is not possible\n");
		वापस -ENXIO;
	पूर्ण

	क्रम (i = 0; i < KEY_LOAD_TRIES; i++) अणु
		ret = पूर्णांकel_hdcp_load_keys(dev_priv);
		अगर (!ret)
			अवरोध;
		पूर्णांकel_hdcp_clear_keys(dev_priv);
	पूर्ण
	अगर (ret) अणु
		drm_err(&dev_priv->drm, "Could not load HDCP keys, (%d)\n",
			ret);
		वापस ret;
	पूर्ण

	/* Inहाल of authentication failures, HDCP spec expects reauth. */
	क्रम (i = 0; i < tries; i++) अणु
		ret = पूर्णांकel_hdcp_auth(connector);
		अगर (!ret) अणु
			hdcp->hdcp_encrypted = true;
			वापस 0;
		पूर्ण

		drm_dbg_kms(&dev_priv->drm, "HDCP Auth failure (%d)\n", ret);

		/* Ensuring HDCP encryption and संकेतling are stopped. */
		_पूर्णांकel_hdcp_disable(connector);
	पूर्ण

	drm_dbg_kms(&dev_priv->drm,
		    "HDCP authentication failed (%d tries/%d)\n", tries, ret);
	वापस ret;
पूर्ण

अटल काष्ठा पूर्णांकel_connector *पूर्णांकel_hdcp_to_connector(काष्ठा पूर्णांकel_hdcp *hdcp)
अणु
	वापस container_of(hdcp, काष्ठा पूर्णांकel_connector, hdcp);
पूर्ण

अटल व्योम पूर्णांकel_hdcp_update_value(काष्ठा पूर्णांकel_connector *connector,
				    u64 value, bool update_property)
अणु
	काष्ठा drm_device *dev = connector->base.dev;
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;

	drm_WARN_ON(connector->base.dev, !mutex_is_locked(&hdcp->mutex));

	अगर (hdcp->value == value)
		वापस;

	drm_WARN_ON(dev, !mutex_is_locked(&dig_port->hdcp_mutex));

	अगर (hdcp->value == DRM_MODE_CONTENT_PROTECTION_ENABLED) अणु
		अगर (!drm_WARN_ON(dev, dig_port->num_hdcp_streams == 0))
			dig_port->num_hdcp_streams--;
	पूर्ण अन्यथा अगर (value == DRM_MODE_CONTENT_PROTECTION_ENABLED) अणु
		dig_port->num_hdcp_streams++;
	पूर्ण

	hdcp->value = value;
	अगर (update_property) अणु
		drm_connector_get(&connector->base);
		schedule_work(&hdcp->prop_work);
	पूर्ण
पूर्ण

/* Implements Part 3 of the HDCP authorization procedure */
अटल पूर्णांक पूर्णांकel_hdcp_check_link(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	क्रमागत port port = dig_port->base.port;
	क्रमागत transcoder cpu_transcoder;
	पूर्णांक ret = 0;

	mutex_lock(&hdcp->mutex);
	mutex_lock(&dig_port->hdcp_mutex);

	cpu_transcoder = hdcp->cpu_transcoder;

	/* Check_link valid only when HDCP1.4 is enabled */
	अगर (hdcp->value != DRM_MODE_CONTENT_PROTECTION_ENABLED ||
	    !hdcp->hdcp_encrypted) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (drm_WARN_ON(&dev_priv->drm,
			!पूर्णांकel_hdcp_in_use(dev_priv, cpu_transcoder, port))) अणु
		drm_err(&dev_priv->drm,
			"%s:%d HDCP link stopped encryption,%x\n",
			connector->base.name, connector->base.base.id,
			पूर्णांकel_de_पढ़ो(dev_priv, HDCP_STATUS(dev_priv, cpu_transcoder, port)));
		ret = -ENXIO;
		पूर्णांकel_hdcp_update_value(connector,
					DRM_MODE_CONTENT_PROTECTION_DESIRED,
					true);
		जाओ out;
	पूर्ण

	अगर (hdcp->shim->check_link(dig_port, connector)) अणु
		अगर (hdcp->value != DRM_MODE_CONTENT_PROTECTION_UNDESIRED) अणु
			पूर्णांकel_hdcp_update_value(connector,
				DRM_MODE_CONTENT_PROTECTION_ENABLED, true);
		पूर्ण
		जाओ out;
	पूर्ण

	drm_dbg_kms(&dev_priv->drm,
		    "[%s:%d] HDCP link failed, retrying authentication\n",
		    connector->base.name, connector->base.base.id);

	ret = _पूर्णांकel_hdcp_disable(connector);
	अगर (ret) अणु
		drm_err(&dev_priv->drm, "Failed to disable hdcp (%d)\n", ret);
		पूर्णांकel_hdcp_update_value(connector,
					DRM_MODE_CONTENT_PROTECTION_DESIRED,
					true);
		जाओ out;
	पूर्ण

	ret = _पूर्णांकel_hdcp_enable(connector);
	अगर (ret) अणु
		drm_err(&dev_priv->drm, "Failed to enable hdcp (%d)\n", ret);
		पूर्णांकel_hdcp_update_value(connector,
					DRM_MODE_CONTENT_PROTECTION_DESIRED,
					true);
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&dig_port->hdcp_mutex);
	mutex_unlock(&hdcp->mutex);
	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_hdcp_prop_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांकel_hdcp *hdcp = container_of(work, काष्ठा पूर्णांकel_hdcp,
					       prop_work);
	काष्ठा पूर्णांकel_connector *connector = पूर्णांकel_hdcp_to_connector(hdcp);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);

	drm_modeset_lock(&dev_priv->drm.mode_config.connection_mutex, शून्य);
	mutex_lock(&hdcp->mutex);

	/*
	 * This worker is only used to flip between ENABLED/DESIRED. Either of
	 * those to UNDESIRED is handled by core. If value == UNDESIRED,
	 * we're running just after hdcp has been disabled, so just निकास
	 */
	अगर (hdcp->value != DRM_MODE_CONTENT_PROTECTION_UNDESIRED)
		drm_hdcp_update_content_protection(&connector->base,
						   hdcp->value);

	mutex_unlock(&hdcp->mutex);
	drm_modeset_unlock(&dev_priv->drm.mode_config.connection_mutex);

	drm_connector_put(&connector->base);
पूर्ण

bool is_hdcp_supported(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port)
अणु
	वापस INTEL_INFO(dev_priv)->display.has_hdcp &&
			(DISPLAY_VER(dev_priv) >= 12 || port < PORT_E);
पूर्ण

अटल पूर्णांक
hdcp2_prepare_ake_init(काष्ठा पूर्णांकel_connector *connector,
		       काष्ठा hdcp2_ake_init *ake_data)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा hdcp_port_data *data = &dig_port->hdcp_port_data;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा i915_hdcp_comp_master *comp;
	पूर्णांक ret;

	mutex_lock(&dev_priv->hdcp_comp_mutex);
	comp = dev_priv->hdcp_master;

	अगर (!comp || !comp->ops) अणु
		mutex_unlock(&dev_priv->hdcp_comp_mutex);
		वापस -EINVAL;
	पूर्ण

	ret = comp->ops->initiate_hdcp2_session(comp->mei_dev, data, ake_data);
	अगर (ret)
		drm_dbg_kms(&dev_priv->drm, "Prepare_ake_init failed. %d\n",
			    ret);
	mutex_unlock(&dev_priv->hdcp_comp_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
hdcp2_verअगरy_rx_cert_prepare_km(काष्ठा पूर्णांकel_connector *connector,
				काष्ठा hdcp2_ake_send_cert *rx_cert,
				bool *paired,
				काष्ठा hdcp2_ake_no_stored_km *ek_pub_km,
				माप_प्रकार *msg_sz)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा hdcp_port_data *data = &dig_port->hdcp_port_data;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा i915_hdcp_comp_master *comp;
	पूर्णांक ret;

	mutex_lock(&dev_priv->hdcp_comp_mutex);
	comp = dev_priv->hdcp_master;

	अगर (!comp || !comp->ops) अणु
		mutex_unlock(&dev_priv->hdcp_comp_mutex);
		वापस -EINVAL;
	पूर्ण

	ret = comp->ops->verअगरy_receiver_cert_prepare_km(comp->mei_dev, data,
							 rx_cert, paired,
							 ek_pub_km, msg_sz);
	अगर (ret < 0)
		drm_dbg_kms(&dev_priv->drm, "Verify rx_cert failed. %d\n",
			    ret);
	mutex_unlock(&dev_priv->hdcp_comp_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक hdcp2_verअगरy_hprime(काष्ठा पूर्णांकel_connector *connector,
			       काष्ठा hdcp2_ake_send_hprime *rx_hprime)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा hdcp_port_data *data = &dig_port->hdcp_port_data;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा i915_hdcp_comp_master *comp;
	पूर्णांक ret;

	mutex_lock(&dev_priv->hdcp_comp_mutex);
	comp = dev_priv->hdcp_master;

	अगर (!comp || !comp->ops) अणु
		mutex_unlock(&dev_priv->hdcp_comp_mutex);
		वापस -EINVAL;
	पूर्ण

	ret = comp->ops->verअगरy_hprime(comp->mei_dev, data, rx_hprime);
	अगर (ret < 0)
		drm_dbg_kms(&dev_priv->drm, "Verify hprime failed. %d\n", ret);
	mutex_unlock(&dev_priv->hdcp_comp_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
hdcp2_store_pairing_info(काष्ठा पूर्णांकel_connector *connector,
			 काष्ठा hdcp2_ake_send_pairing_info *pairing_info)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा hdcp_port_data *data = &dig_port->hdcp_port_data;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा i915_hdcp_comp_master *comp;
	पूर्णांक ret;

	mutex_lock(&dev_priv->hdcp_comp_mutex);
	comp = dev_priv->hdcp_master;

	अगर (!comp || !comp->ops) अणु
		mutex_unlock(&dev_priv->hdcp_comp_mutex);
		वापस -EINVAL;
	पूर्ण

	ret = comp->ops->store_pairing_info(comp->mei_dev, data, pairing_info);
	अगर (ret < 0)
		drm_dbg_kms(&dev_priv->drm, "Store pairing info failed. %d\n",
			    ret);
	mutex_unlock(&dev_priv->hdcp_comp_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
hdcp2_prepare_lc_init(काष्ठा पूर्णांकel_connector *connector,
		      काष्ठा hdcp2_lc_init *lc_init)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा hdcp_port_data *data = &dig_port->hdcp_port_data;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा i915_hdcp_comp_master *comp;
	पूर्णांक ret;

	mutex_lock(&dev_priv->hdcp_comp_mutex);
	comp = dev_priv->hdcp_master;

	अगर (!comp || !comp->ops) अणु
		mutex_unlock(&dev_priv->hdcp_comp_mutex);
		वापस -EINVAL;
	पूर्ण

	ret = comp->ops->initiate_locality_check(comp->mei_dev, data, lc_init);
	अगर (ret < 0)
		drm_dbg_kms(&dev_priv->drm, "Prepare lc_init failed. %d\n",
			    ret);
	mutex_unlock(&dev_priv->hdcp_comp_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
hdcp2_verअगरy_lprime(काष्ठा पूर्णांकel_connector *connector,
		    काष्ठा hdcp2_lc_send_lprime *rx_lprime)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा hdcp_port_data *data = &dig_port->hdcp_port_data;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा i915_hdcp_comp_master *comp;
	पूर्णांक ret;

	mutex_lock(&dev_priv->hdcp_comp_mutex);
	comp = dev_priv->hdcp_master;

	अगर (!comp || !comp->ops) अणु
		mutex_unlock(&dev_priv->hdcp_comp_mutex);
		वापस -EINVAL;
	पूर्ण

	ret = comp->ops->verअगरy_lprime(comp->mei_dev, data, rx_lprime);
	अगर (ret < 0)
		drm_dbg_kms(&dev_priv->drm, "Verify L_Prime failed. %d\n",
			    ret);
	mutex_unlock(&dev_priv->hdcp_comp_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक hdcp2_prepare_skey(काष्ठा पूर्णांकel_connector *connector,
			      काष्ठा hdcp2_ske_send_eks *ske_data)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा hdcp_port_data *data = &dig_port->hdcp_port_data;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा i915_hdcp_comp_master *comp;
	पूर्णांक ret;

	mutex_lock(&dev_priv->hdcp_comp_mutex);
	comp = dev_priv->hdcp_master;

	अगर (!comp || !comp->ops) अणु
		mutex_unlock(&dev_priv->hdcp_comp_mutex);
		वापस -EINVAL;
	पूर्ण

	ret = comp->ops->get_session_key(comp->mei_dev, data, ske_data);
	अगर (ret < 0)
		drm_dbg_kms(&dev_priv->drm, "Get session key failed. %d\n",
			    ret);
	mutex_unlock(&dev_priv->hdcp_comp_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
hdcp2_verअगरy_rep_topology_prepare_ack(काष्ठा पूर्णांकel_connector *connector,
				      काष्ठा hdcp2_rep_send_receiverid_list
								*rep_topology,
				      काष्ठा hdcp2_rep_send_ack *rep_send_ack)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा hdcp_port_data *data = &dig_port->hdcp_port_data;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा i915_hdcp_comp_master *comp;
	पूर्णांक ret;

	mutex_lock(&dev_priv->hdcp_comp_mutex);
	comp = dev_priv->hdcp_master;

	अगर (!comp || !comp->ops) अणु
		mutex_unlock(&dev_priv->hdcp_comp_mutex);
		वापस -EINVAL;
	पूर्ण

	ret = comp->ops->repeater_check_flow_prepare_ack(comp->mei_dev, data,
							 rep_topology,
							 rep_send_ack);
	अगर (ret < 0)
		drm_dbg_kms(&dev_priv->drm,
			    "Verify rep topology failed. %d\n", ret);
	mutex_unlock(&dev_priv->hdcp_comp_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
hdcp2_verअगरy_mprime(काष्ठा पूर्णांकel_connector *connector,
		    काष्ठा hdcp2_rep_stream_पढ़ोy *stream_पढ़ोy)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा hdcp_port_data *data = &dig_port->hdcp_port_data;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा i915_hdcp_comp_master *comp;
	पूर्णांक ret;

	mutex_lock(&dev_priv->hdcp_comp_mutex);
	comp = dev_priv->hdcp_master;

	अगर (!comp || !comp->ops) अणु
		mutex_unlock(&dev_priv->hdcp_comp_mutex);
		वापस -EINVAL;
	पूर्ण

	ret = comp->ops->verअगरy_mprime(comp->mei_dev, data, stream_पढ़ोy);
	अगर (ret < 0)
		drm_dbg_kms(&dev_priv->drm, "Verify mprime failed. %d\n", ret);
	mutex_unlock(&dev_priv->hdcp_comp_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक hdcp2_authenticate_port(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा hdcp_port_data *data = &dig_port->hdcp_port_data;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा i915_hdcp_comp_master *comp;
	पूर्णांक ret;

	mutex_lock(&dev_priv->hdcp_comp_mutex);
	comp = dev_priv->hdcp_master;

	अगर (!comp || !comp->ops) अणु
		mutex_unlock(&dev_priv->hdcp_comp_mutex);
		वापस -EINVAL;
	पूर्ण

	ret = comp->ops->enable_hdcp_authentication(comp->mei_dev, data);
	अगर (ret < 0)
		drm_dbg_kms(&dev_priv->drm, "Enable hdcp auth failed. %d\n",
			    ret);
	mutex_unlock(&dev_priv->hdcp_comp_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक hdcp2_बंद_mei_session(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा i915_hdcp_comp_master *comp;
	पूर्णांक ret;

	mutex_lock(&dev_priv->hdcp_comp_mutex);
	comp = dev_priv->hdcp_master;

	अगर (!comp || !comp->ops) अणु
		mutex_unlock(&dev_priv->hdcp_comp_mutex);
		वापस -EINVAL;
	पूर्ण

	ret = comp->ops->बंद_hdcp_session(comp->mei_dev,
					     &dig_port->hdcp_port_data);
	mutex_unlock(&dev_priv->hdcp_comp_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक hdcp2_deauthenticate_port(काष्ठा पूर्णांकel_connector *connector)
अणु
	वापस hdcp2_बंद_mei_session(connector);
पूर्ण

/* Authentication flow starts from here */
अटल पूर्णांक hdcp2_authentication_key_exchange(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	जोड़ अणु
		काष्ठा hdcp2_ake_init ake_init;
		काष्ठा hdcp2_ake_send_cert send_cert;
		काष्ठा hdcp2_ake_no_stored_km no_stored_km;
		काष्ठा hdcp2_ake_send_hprime send_hprime;
		काष्ठा hdcp2_ake_send_pairing_info pairing_info;
	पूर्ण msgs;
	स्थिर काष्ठा पूर्णांकel_hdcp_shim *shim = hdcp->shim;
	माप_प्रकार size;
	पूर्णांक ret;

	/* Init क्रम seq_num */
	hdcp->seq_num_v = 0;
	hdcp->seq_num_m = 0;

	ret = hdcp2_prepare_ake_init(connector, &msgs.ake_init);
	अगर (ret < 0)
		वापस ret;

	ret = shim->ग_लिखो_2_2_msg(dig_port, &msgs.ake_init,
				  माप(msgs.ake_init));
	अगर (ret < 0)
		वापस ret;

	ret = shim->पढ़ो_2_2_msg(dig_port, HDCP_2_2_AKE_SEND_CERT,
				 &msgs.send_cert, माप(msgs.send_cert));
	अगर (ret < 0)
		वापस ret;

	अगर (msgs.send_cert.rx_caps[0] != HDCP_2_2_RX_CAPS_VERSION_VAL) अणु
		drm_dbg_kms(&dev_priv->drm, "cert.rx_caps dont claim HDCP2.2\n");
		वापस -EINVAL;
	पूर्ण

	hdcp->is_repeater = HDCP_2_2_RX_REPEATER(msgs.send_cert.rx_caps[2]);

	अगर (drm_hdcp_check_ksvs_revoked(&dev_priv->drm,
					msgs.send_cert.cert_rx.receiver_id,
					1) > 0) अणु
		drm_err(&dev_priv->drm, "Receiver ID is revoked\n");
		वापस -EPERM;
	पूर्ण

	/*
	 * Here msgs.no_stored_km will hold msgs corresponding to the km
	 * stored also.
	 */
	ret = hdcp2_verअगरy_rx_cert_prepare_km(connector, &msgs.send_cert,
					      &hdcp->is_paired,
					      &msgs.no_stored_km, &size);
	अगर (ret < 0)
		वापस ret;

	ret = shim->ग_लिखो_2_2_msg(dig_port, &msgs.no_stored_km, size);
	अगर (ret < 0)
		वापस ret;

	ret = shim->पढ़ो_2_2_msg(dig_port, HDCP_2_2_AKE_SEND_HPRIME,
				 &msgs.send_hprime, माप(msgs.send_hprime));
	अगर (ret < 0)
		वापस ret;

	ret = hdcp2_verअगरy_hprime(connector, &msgs.send_hprime);
	अगर (ret < 0)
		वापस ret;

	अगर (!hdcp->is_paired) अणु
		/* Pairing is required */
		ret = shim->पढ़ो_2_2_msg(dig_port,
					 HDCP_2_2_AKE_SEND_PAIRING_INFO,
					 &msgs.pairing_info,
					 माप(msgs.pairing_info));
		अगर (ret < 0)
			वापस ret;

		ret = hdcp2_store_pairing_info(connector, &msgs.pairing_info);
		अगर (ret < 0)
			वापस ret;
		hdcp->is_paired = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hdcp2_locality_check(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	जोड़ अणु
		काष्ठा hdcp2_lc_init lc_init;
		काष्ठा hdcp2_lc_send_lprime send_lprime;
	पूर्ण msgs;
	स्थिर काष्ठा पूर्णांकel_hdcp_shim *shim = hdcp->shim;
	पूर्णांक tries = HDCP2_LC_RETRY_CNT, ret, i;

	क्रम (i = 0; i < tries; i++) अणु
		ret = hdcp2_prepare_lc_init(connector, &msgs.lc_init);
		अगर (ret < 0)
			जारी;

		ret = shim->ग_लिखो_2_2_msg(dig_port, &msgs.lc_init,
				      माप(msgs.lc_init));
		अगर (ret < 0)
			जारी;

		ret = shim->पढ़ो_2_2_msg(dig_port,
					 HDCP_2_2_LC_SEND_LPRIME,
					 &msgs.send_lprime,
					 माप(msgs.send_lprime));
		अगर (ret < 0)
			जारी;

		ret = hdcp2_verअगरy_lprime(connector, &msgs.send_lprime);
		अगर (!ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hdcp2_session_key_exchange(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	काष्ठा hdcp2_ske_send_eks send_eks;
	पूर्णांक ret;

	ret = hdcp2_prepare_skey(connector, &send_eks);
	अगर (ret < 0)
		वापस ret;

	ret = hdcp->shim->ग_लिखो_2_2_msg(dig_port, &send_eks,
					माप(send_eks));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल
पूर्णांक _hdcp2_propagate_stream_management_info(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा hdcp_port_data *data = &dig_port->hdcp_port_data;
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	जोड़ अणु
		काष्ठा hdcp2_rep_stream_manage stream_manage;
		काष्ठा hdcp2_rep_stream_पढ़ोy stream_पढ़ोy;
	पूर्ण msgs;
	स्थिर काष्ठा पूर्णांकel_hdcp_shim *shim = hdcp->shim;
	पूर्णांक ret, streams_size_delta, i;

	अगर (connector->hdcp.seq_num_m > HDCP_2_2_SEQ_NUM_MAX)
		वापस -दुस्फल;

	/* Prepare RepeaterAuth_Stream_Manage msg */
	msgs.stream_manage.msg_id = HDCP_2_2_REP_STREAM_MANAGE;
	drm_hdcp_cpu_to_be24(msgs.stream_manage.seq_num_m, hdcp->seq_num_m);

	msgs.stream_manage.k = cpu_to_be16(data->k);

	क्रम (i = 0; i < data->k; i++) अणु
		msgs.stream_manage.streams[i].stream_id = data->streams[i].stream_id;
		msgs.stream_manage.streams[i].stream_type = data->streams[i].stream_type;
	पूर्ण

	streams_size_delta = (HDCP_2_2_MAX_CONTENT_STREAMS_CNT - data->k) *
				माप(काष्ठा hdcp2_streamid_type);
	/* Send it to Repeater */
	ret = shim->ग_लिखो_2_2_msg(dig_port, &msgs.stream_manage,
				  माप(msgs.stream_manage) - streams_size_delta);
	अगर (ret < 0)
		जाओ out;

	ret = shim->पढ़ो_2_2_msg(dig_port, HDCP_2_2_REP_STREAM_READY,
				 &msgs.stream_पढ़ोy, माप(msgs.stream_पढ़ोy));
	अगर (ret < 0)
		जाओ out;

	data->seq_num_m = hdcp->seq_num_m;

	ret = hdcp2_verअगरy_mprime(connector, &msgs.stream_पढ़ोy);

out:
	hdcp->seq_num_m++;

	वापस ret;
पूर्ण

अटल
पूर्णांक hdcp2_authenticate_repeater_topology(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	जोड़ अणु
		काष्ठा hdcp2_rep_send_receiverid_list recvid_list;
		काष्ठा hdcp2_rep_send_ack rep_ack;
	पूर्ण msgs;
	स्थिर काष्ठा पूर्णांकel_hdcp_shim *shim = hdcp->shim;
	u32 seq_num_v, device_cnt;
	u8 *rx_info;
	पूर्णांक ret;

	ret = shim->पढ़ो_2_2_msg(dig_port, HDCP_2_2_REP_SEND_RECVID_LIST,
				 &msgs.recvid_list, माप(msgs.recvid_list));
	अगर (ret < 0)
		वापस ret;

	rx_info = msgs.recvid_list.rx_info;

	अगर (HDCP_2_2_MAX_CASCADE_EXCEEDED(rx_info[1]) ||
	    HDCP_2_2_MAX_DEVS_EXCEEDED(rx_info[1])) अणु
		drm_dbg_kms(&dev_priv->drm, "Topology Max Size Exceeded\n");
		वापस -EINVAL;
	पूर्ण

	/* Converting and Storing the seq_num_v to local variable as DWORD */
	seq_num_v =
		drm_hdcp_be24_to_cpu((स्थिर u8 *)msgs.recvid_list.seq_num_v);

	अगर (!hdcp->hdcp2_encrypted && seq_num_v) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Non zero Seq_num_v at first RecvId_List msg\n");
		वापस -EINVAL;
	पूर्ण

	अगर (seq_num_v < hdcp->seq_num_v) अणु
		/* Roll over of the seq_num_v from repeater. Reauthenticate. */
		drm_dbg_kms(&dev_priv->drm, "Seq_num_v roll over.\n");
		वापस -EINVAL;
	पूर्ण

	device_cnt = (HDCP_2_2_DEV_COUNT_HI(rx_info[0]) << 4 |
		      HDCP_2_2_DEV_COUNT_LO(rx_info[1]));
	अगर (drm_hdcp_check_ksvs_revoked(&dev_priv->drm,
					msgs.recvid_list.receiver_ids,
					device_cnt) > 0) अणु
		drm_err(&dev_priv->drm, "Revoked receiver ID(s) is in list\n");
		वापस -EPERM;
	पूर्ण

	ret = hdcp2_verअगरy_rep_topology_prepare_ack(connector,
						    &msgs.recvid_list,
						    &msgs.rep_ack);
	अगर (ret < 0)
		वापस ret;

	hdcp->seq_num_v = seq_num_v;
	ret = shim->ग_लिखो_2_2_msg(dig_port, &msgs.rep_ack,
				  माप(msgs.rep_ack));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक hdcp2_authenticate_sink(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	स्थिर काष्ठा पूर्णांकel_hdcp_shim *shim = hdcp->shim;
	पूर्णांक ret;

	ret = hdcp2_authentication_key_exchange(connector);
	अगर (ret < 0) अणु
		drm_dbg_kms(&i915->drm, "AKE Failed. Err : %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hdcp2_locality_check(connector);
	अगर (ret < 0) अणु
		drm_dbg_kms(&i915->drm,
			    "Locality Check failed. Err : %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hdcp2_session_key_exchange(connector);
	अगर (ret < 0) अणु
		drm_dbg_kms(&i915->drm, "SKE Failed. Err : %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (shim->config_stream_type) अणु
		ret = shim->config_stream_type(dig_port,
					       hdcp->is_repeater,
					       hdcp->content_type);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (hdcp->is_repeater) अणु
		ret = hdcp2_authenticate_repeater_topology(connector);
		अगर (ret < 0) अणु
			drm_dbg_kms(&i915->drm,
				    "Repeater Auth Failed. Err: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hdcp2_enable_stream_encryption(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा hdcp_port_data *data = &dig_port->hdcp_port_data;
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	क्रमागत transcoder cpu_transcoder = hdcp->cpu_transcoder;
	क्रमागत port port = dig_port->base.port;
	पूर्णांक ret = 0;

	अगर (!(पूर्णांकel_de_पढ़ो(dev_priv, HDCP2_STATUS(dev_priv, cpu_transcoder, port)) &
			    LINK_ENCRYPTION_STATUS)) अणु
		drm_err(&dev_priv->drm, "[%s:%d] HDCP 2.2 Link is not encrypted\n",
			connector->base.name, connector->base.base.id);
		ret = -EPERM;
		जाओ link_recover;
	पूर्ण

	अगर (hdcp->shim->stream_2_2_encryption) अणु
		ret = hdcp->shim->stream_2_2_encryption(connector, true);
		अगर (ret) अणु
			drm_err(&dev_priv->drm, "[%s:%d] Failed to enable HDCP 2.2 stream enc\n",
				connector->base.name, connector->base.base.id);
			वापस ret;
		पूर्ण
		drm_dbg_kms(&dev_priv->drm, "HDCP 2.2 transcoder: %s stream encrypted\n",
			    transcoder_name(hdcp->stream_transcoder));
	पूर्ण

	वापस 0;

link_recover:
	अगर (hdcp2_deauthenticate_port(connector) < 0)
		drm_dbg_kms(&dev_priv->drm, "Port deauth failed.\n");

	dig_port->hdcp_auth_status = false;
	data->k = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक hdcp2_enable_encryption(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	क्रमागत port port = dig_port->base.port;
	क्रमागत transcoder cpu_transcoder = hdcp->cpu_transcoder;
	पूर्णांक ret;

	drm_WARN_ON(&dev_priv->drm,
		    पूर्णांकel_de_पढ़ो(dev_priv, HDCP2_STATUS(dev_priv, cpu_transcoder, port)) &
		    LINK_ENCRYPTION_STATUS);
	अगर (hdcp->shim->toggle_संकेतling) अणु
		ret = hdcp->shim->toggle_संकेतling(dig_port, cpu_transcoder,
						    true);
		अगर (ret) अणु
			drm_err(&dev_priv->drm,
				"Failed to enable HDCP signalling. %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (पूर्णांकel_de_पढ़ो(dev_priv, HDCP2_STATUS(dev_priv, cpu_transcoder, port)) &
	    LINK_AUTH_STATUS) अणु
		/* Link is Authenticated. Now set क्रम Encryption */
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       HDCP2_CTL(dev_priv, cpu_transcoder, port),
			       पूर्णांकel_de_पढ़ो(dev_priv, HDCP2_CTL(dev_priv, cpu_transcoder, port)) | CTL_LINK_ENCRYPTION_REQ);
	पूर्ण

	ret = पूर्णांकel_de_रुको_क्रम_set(dev_priv,
				    HDCP2_STATUS(dev_priv, cpu_transcoder,
						 port),
				    LINK_ENCRYPTION_STATUS,
				    HDCP_ENCRYPT_STATUS_CHANGE_TIMEOUT_MS);
	dig_port->hdcp_auth_status = true;

	वापस ret;
पूर्ण

अटल पूर्णांक hdcp2_disable_encryption(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	क्रमागत port port = dig_port->base.port;
	क्रमागत transcoder cpu_transcoder = hdcp->cpu_transcoder;
	पूर्णांक ret;

	drm_WARN_ON(&dev_priv->drm, !(पूर्णांकel_de_पढ़ो(dev_priv, HDCP2_STATUS(dev_priv, cpu_transcoder, port)) &
				      LINK_ENCRYPTION_STATUS));

	पूर्णांकel_de_ग_लिखो(dev_priv, HDCP2_CTL(dev_priv, cpu_transcoder, port),
		       पूर्णांकel_de_पढ़ो(dev_priv, HDCP2_CTL(dev_priv, cpu_transcoder, port)) & ~CTL_LINK_ENCRYPTION_REQ);

	ret = पूर्णांकel_de_रुको_क्रम_clear(dev_priv,
				      HDCP2_STATUS(dev_priv, cpu_transcoder,
						   port),
				      LINK_ENCRYPTION_STATUS,
				      HDCP_ENCRYPT_STATUS_CHANGE_TIMEOUT_MS);
	अगर (ret == -ETIMEDOUT)
		drm_dbg_kms(&dev_priv->drm, "Disable Encryption Timedout");

	अगर (hdcp->shim->toggle_संकेतling) अणु
		ret = hdcp->shim->toggle_संकेतling(dig_port, cpu_transcoder,
						    false);
		अगर (ret) अणु
			drm_err(&dev_priv->drm,
				"Failed to disable HDCP signalling. %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
hdcp2_propagate_stream_management_info(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	पूर्णांक i, tries = 3, ret;

	अगर (!connector->hdcp.is_repeater)
		वापस 0;

	क्रम (i = 0; i < tries; i++) अणु
		ret = _hdcp2_propagate_stream_management_info(connector);
		अगर (!ret)
			अवरोध;

		/* Lets restart the auth inहाल of seq_num_m roll over */
		अगर (connector->hdcp.seq_num_m > HDCP_2_2_SEQ_NUM_MAX) अणु
			drm_dbg_kms(&i915->drm,
				    "seq_num_m roll over.(%d)\n", ret);
			अवरोध;
		पूर्ण

		drm_dbg_kms(&i915->drm,
			    "HDCP2 stream management %d of %d Failed.(%d)\n",
			    i + 1, tries, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hdcp2_authenticate_and_encrypt(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	पूर्णांक ret = 0, i, tries = 3;

	क्रम (i = 0; i < tries && !dig_port->hdcp_auth_status; i++) अणु
		ret = hdcp2_authenticate_sink(connector);
		अगर (!ret) अणु
			ret = hdcp2_propagate_stream_management_info(connector);
			अगर (ret) अणु
				drm_dbg_kms(&i915->drm,
					    "Stream management failed.(%d)\n",
					    ret);
				अवरोध;
			पूर्ण

			ret = hdcp2_authenticate_port(connector);
			अगर (!ret)
				अवरोध;
			drm_dbg_kms(&i915->drm, "HDCP2 port auth failed.(%d)\n",
				    ret);
		पूर्ण

		/* Clearing the mei hdcp session */
		drm_dbg_kms(&i915->drm, "HDCP2.2 Auth %d of %d Failed.(%d)\n",
			    i + 1, tries, ret);
		अगर (hdcp2_deauthenticate_port(connector) < 0)
			drm_dbg_kms(&i915->drm, "Port deauth failed.\n");
	पूर्ण

	अगर (!ret && !dig_port->hdcp_auth_status) अणु
		/*
		 * Ensuring the required 200mSec min समय पूर्णांकerval between
		 * Session Key Exchange and encryption.
		 */
		msleep(HDCP_2_2_DELAY_BEFORE_ENCRYPTION_EN);
		ret = hdcp2_enable_encryption(connector);
		अगर (ret < 0) अणु
			drm_dbg_kms(&i915->drm,
				    "Encryption Enable Failed.(%d)\n", ret);
			अगर (hdcp2_deauthenticate_port(connector) < 0)
				drm_dbg_kms(&i915->drm, "Port deauth failed.\n");
		पूर्ण
	पूर्ण

	अगर (!ret)
		ret = hdcp2_enable_stream_encryption(connector);

	वापस ret;
पूर्ण

अटल पूर्णांक _पूर्णांकel_hdcp2_enable(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	काष्ठा hdcp_port_data *data = &dig_port->hdcp_port_data;
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	पूर्णांक ret;

	drm_dbg_kms(&i915->drm, "[%s:%d] HDCP2.2 is being enabled. Type: %d\n",
		    connector->base.name, connector->base.base.id,
		    hdcp->content_type);

	/* Stream which requires encryption */
	अगर (!पूर्णांकel_encoder_is_mst(पूर्णांकel_attached_encoder(connector))) अणु
		data->k = 1;
		data->streams[0].stream_type = hdcp->content_type;
	पूर्ण अन्यथा अणु
		ret = पूर्णांकel_hdcp_required_content_stream(dig_port);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = hdcp2_authenticate_and_encrypt(connector);
	अगर (ret) अणु
		drm_dbg_kms(&i915->drm, "HDCP2 Type%d  Enabling Failed. (%d)\n",
			    hdcp->content_type, ret);
		वापस ret;
	पूर्ण

	drm_dbg_kms(&i915->drm, "[%s:%d] HDCP2.2 is enabled. Type %d\n",
		    connector->base.name, connector->base.base.id,
		    hdcp->content_type);

	hdcp->hdcp2_encrypted = true;
	वापस 0;
पूर्ण

अटल पूर्णांक
_पूर्णांकel_hdcp2_disable(काष्ठा पूर्णांकel_connector *connector, bool hdcp2_link_recovery)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	काष्ठा hdcp_port_data *data = &dig_port->hdcp_port_data;
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	पूर्णांक ret;

	drm_dbg_kms(&i915->drm, "[%s:%d] HDCP2.2 is being Disabled\n",
		    connector->base.name, connector->base.base.id);

	अगर (hdcp->shim->stream_2_2_encryption) अणु
		ret = hdcp->shim->stream_2_2_encryption(connector, false);
		अगर (ret) अणु
			drm_err(&i915->drm, "[%s:%d] Failed to disable HDCP 2.2 stream enc\n",
				connector->base.name, connector->base.base.id);
			वापस ret;
		पूर्ण
		drm_dbg_kms(&i915->drm, "HDCP 2.2 transcoder: %s stream encryption disabled\n",
			    transcoder_name(hdcp->stream_transcoder));

		अगर (dig_port->num_hdcp_streams > 0 && !hdcp2_link_recovery)
			वापस 0;
	पूर्ण

	ret = hdcp2_disable_encryption(connector);

	अगर (hdcp2_deauthenticate_port(connector) < 0)
		drm_dbg_kms(&i915->drm, "Port deauth failed.\n");

	connector->hdcp.hdcp2_encrypted = false;
	dig_port->hdcp_auth_status = false;
	data->k = 0;

	वापस ret;
पूर्ण

/* Implements the Link Integrity Check क्रम HDCP2.2 */
अटल पूर्णांक पूर्णांकel_hdcp2_check_link(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	क्रमागत port port = dig_port->base.port;
	क्रमागत transcoder cpu_transcoder;
	पूर्णांक ret = 0;

	mutex_lock(&hdcp->mutex);
	mutex_lock(&dig_port->hdcp_mutex);
	cpu_transcoder = hdcp->cpu_transcoder;

	/* hdcp2_check_link is expected only when HDCP2.2 is Enabled */
	अगर (hdcp->value != DRM_MODE_CONTENT_PROTECTION_ENABLED ||
	    !hdcp->hdcp2_encrypted) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (drm_WARN_ON(&dev_priv->drm,
			!पूर्णांकel_hdcp2_in_use(dev_priv, cpu_transcoder, port))) अणु
		drm_err(&dev_priv->drm,
			"HDCP2.2 link stopped the encryption, %x\n",
			पूर्णांकel_de_पढ़ो(dev_priv, HDCP2_STATUS(dev_priv, cpu_transcoder, port)));
		ret = -ENXIO;
		_पूर्णांकel_hdcp2_disable(connector, true);
		पूर्णांकel_hdcp_update_value(connector,
					DRM_MODE_CONTENT_PROTECTION_DESIRED,
					true);
		जाओ out;
	पूर्ण

	ret = hdcp->shim->check_2_2_link(dig_port, connector);
	अगर (ret == HDCP_LINK_PROTECTED) अणु
		अगर (hdcp->value != DRM_MODE_CONTENT_PROTECTION_UNDESIRED) अणु
			पूर्णांकel_hdcp_update_value(connector,
					DRM_MODE_CONTENT_PROTECTION_ENABLED,
					true);
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (ret == HDCP_TOPOLOGY_CHANGE) अणु
		अगर (hdcp->value == DRM_MODE_CONTENT_PROTECTION_UNDESIRED)
			जाओ out;

		drm_dbg_kms(&dev_priv->drm,
			    "HDCP2.2 Downstream topology change\n");
		ret = hdcp2_authenticate_repeater_topology(connector);
		अगर (!ret) अणु
			पूर्णांकel_hdcp_update_value(connector,
					DRM_MODE_CONTENT_PROTECTION_ENABLED,
					true);
			जाओ out;
		पूर्ण
		drm_dbg_kms(&dev_priv->drm,
			    "[%s:%d] Repeater topology auth failed.(%d)\n",
			    connector->base.name, connector->base.base.id,
			    ret);
	पूर्ण अन्यथा अणु
		drm_dbg_kms(&dev_priv->drm,
			    "[%s:%d] HDCP2.2 link failed, retrying auth\n",
			    connector->base.name, connector->base.base.id);
	पूर्ण

	ret = _पूर्णांकel_hdcp2_disable(connector, true);
	अगर (ret) अणु
		drm_err(&dev_priv->drm,
			"[%s:%d] Failed to disable hdcp2.2 (%d)\n",
			connector->base.name, connector->base.base.id, ret);
		पूर्णांकel_hdcp_update_value(connector,
				DRM_MODE_CONTENT_PROTECTION_DESIRED, true);
		जाओ out;
	पूर्ण

	ret = _पूर्णांकel_hdcp2_enable(connector);
	अगर (ret) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "[%s:%d] Failed to enable hdcp2.2 (%d)\n",
			    connector->base.name, connector->base.base.id,
			    ret);
		पूर्णांकel_hdcp_update_value(connector,
					DRM_MODE_CONTENT_PROTECTION_DESIRED,
					true);
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&dig_port->hdcp_mutex);
	mutex_unlock(&hdcp->mutex);
	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_hdcp_check_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांकel_hdcp *hdcp = container_of(to_delayed_work(work),
					       काष्ठा पूर्णांकel_hdcp,
					       check_work);
	काष्ठा पूर्णांकel_connector *connector = पूर्णांकel_hdcp_to_connector(hdcp);

	अगर (drm_connector_is_unरेजिस्टरed(&connector->base))
		वापस;

	अगर (!पूर्णांकel_hdcp2_check_link(connector))
		schedule_delayed_work(&hdcp->check_work,
				      DRM_HDCP2_CHECK_PERIOD_MS);
	अन्यथा अगर (!पूर्णांकel_hdcp_check_link(connector))
		schedule_delayed_work(&hdcp->check_work,
				      DRM_HDCP_CHECK_PERIOD_MS);
पूर्ण

अटल पूर्णांक i915_hdcp_component_bind(काष्ठा device *i915_kdev,
				    काष्ठा device *mei_kdev, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_to_i915(i915_kdev);

	drm_dbg(&dev_priv->drm, "I915 HDCP comp bind\n");
	mutex_lock(&dev_priv->hdcp_comp_mutex);
	dev_priv->hdcp_master = (काष्ठा i915_hdcp_comp_master *)data;
	dev_priv->hdcp_master->mei_dev = mei_kdev;
	mutex_unlock(&dev_priv->hdcp_comp_mutex);

	वापस 0;
पूर्ण

अटल व्योम i915_hdcp_component_unbind(काष्ठा device *i915_kdev,
				       काष्ठा device *mei_kdev, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *dev_priv = kdev_to_i915(i915_kdev);

	drm_dbg(&dev_priv->drm, "I915 HDCP comp unbind\n");
	mutex_lock(&dev_priv->hdcp_comp_mutex);
	dev_priv->hdcp_master = शून्य;
	mutex_unlock(&dev_priv->hdcp_comp_mutex);
पूर्ण

अटल स्थिर काष्ठा component_ops i915_hdcp_component_ops = अणु
	.bind   = i915_hdcp_component_bind,
	.unbind = i915_hdcp_component_unbind,
पूर्ण;

अटल क्रमागत mei_fw_ddi पूर्णांकel_get_mei_fw_ddi_index(क्रमागत port port)
अणु
	चयन (port) अणु
	हाल PORT_A:
		वापस MEI_DDI_A;
	हाल PORT_B ... PORT_F:
		वापस (क्रमागत mei_fw_ddi)port;
	शेष:
		वापस MEI_DDI_INVALID_PORT;
	पूर्ण
पूर्ण

अटल क्रमागत mei_fw_tc पूर्णांकel_get_mei_fw_tc(क्रमागत transcoder cpu_transcoder)
अणु
	चयन (cpu_transcoder) अणु
	हाल TRANSCODER_A ... TRANSCODER_D:
		वापस (क्रमागत mei_fw_tc)(cpu_transcoder | 0x10);
	शेष: /* eDP, DSI TRANSCODERS are non HDCP capable */
		वापस MEI_INVALID_TRANSCODER;
	पूर्ण
पूर्ण

अटल पूर्णांक initialize_hdcp_port_data(काष्ठा पूर्णांकel_connector *connector,
				     काष्ठा पूर्णांकel_digital_port *dig_port,
				     स्थिर काष्ठा पूर्णांकel_hdcp_shim *shim)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा hdcp_port_data *data = &dig_port->hdcp_port_data;
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	क्रमागत port port = dig_port->base.port;

	अगर (DISPLAY_VER(dev_priv) < 12)
		data->fw_ddi = पूर्णांकel_get_mei_fw_ddi_index(port);
	अन्यथा
		/*
		 * As per ME FW API expectation, क्रम GEN 12+, fw_ddi is filled
		 * with zero(INVALID PORT index).
		 */
		data->fw_ddi = MEI_DDI_INVALID_PORT;

	/*
	 * As associated transcoder is set and modअगरied at modeset, here fw_tc
	 * is initialized to zero (invalid transcoder index). This will be
	 * retained क्रम <Gen12 क्रमever.
	 */
	data->fw_tc = MEI_INVALID_TRANSCODER;

	data->port_type = (u8)HDCP_PORT_TYPE_INTEGRATED;
	data->protocol = (u8)shim->protocol;

	अगर (!data->streams)
		data->streams = kसुस्मृति(INTEL_NUM_PIPES(dev_priv),
					माप(काष्ठा hdcp2_streamid_type),
					GFP_KERNEL);
	अगर (!data->streams) अणु
		drm_err(&dev_priv->drm, "Out of Memory\n");
		वापस -ENOMEM;
	पूर्ण
	/* For SST */
	data->streams[0].stream_id = 0;
	data->streams[0].stream_type = hdcp->content_type;

	वापस 0;
पूर्ण

अटल bool is_hdcp2_supported(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (!IS_ENABLED(CONFIG_INTEL_MEI_HDCP))
		वापस false;

	वापस (DISPLAY_VER(dev_priv) >= 10 ||
		IS_KABYLAKE(dev_priv) ||
		IS_COFFEELAKE(dev_priv) ||
		IS_COMETLAKE(dev_priv));
पूर्ण

व्योम पूर्णांकel_hdcp_component_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक ret;

	अगर (!is_hdcp2_supported(dev_priv))
		वापस;

	mutex_lock(&dev_priv->hdcp_comp_mutex);
	drm_WARN_ON(&dev_priv->drm, dev_priv->hdcp_comp_added);

	dev_priv->hdcp_comp_added = true;
	mutex_unlock(&dev_priv->hdcp_comp_mutex);
	ret = component_add_typed(dev_priv->drm.dev, &i915_hdcp_component_ops,
				  I915_COMPONENT_HDCP);
	अगर (ret < 0) अणु
		drm_dbg_kms(&dev_priv->drm, "Failed at component add(%d)\n",
			    ret);
		mutex_lock(&dev_priv->hdcp_comp_mutex);
		dev_priv->hdcp_comp_added = false;
		mutex_unlock(&dev_priv->hdcp_comp_mutex);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_hdcp2_init(काष्ठा पूर्णांकel_connector *connector,
			     काष्ठा पूर्णांकel_digital_port *dig_port,
			     स्थिर काष्ठा पूर्णांकel_hdcp_shim *shim)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	पूर्णांक ret;

	ret = initialize_hdcp_port_data(connector, dig_port, shim);
	अगर (ret) अणु
		drm_dbg_kms(&i915->drm, "Mei hdcp data init failed\n");
		वापस;
	पूर्ण

	hdcp->hdcp2_supported = true;
पूर्ण

पूर्णांक पूर्णांकel_hdcp_init(काष्ठा पूर्णांकel_connector *connector,
		    काष्ठा पूर्णांकel_digital_port *dig_port,
		    स्थिर काष्ठा पूर्णांकel_hdcp_shim *shim)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	पूर्णांक ret;

	अगर (!shim)
		वापस -EINVAL;

	अगर (is_hdcp2_supported(dev_priv))
		पूर्णांकel_hdcp2_init(connector, dig_port, shim);

	ret =
	drm_connector_attach_content_protection_property(&connector->base,
							 hdcp->hdcp2_supported);
	अगर (ret) अणु
		hdcp->hdcp2_supported = false;
		kमुक्त(dig_port->hdcp_port_data.streams);
		वापस ret;
	पूर्ण

	hdcp->shim = shim;
	mutex_init(&hdcp->mutex);
	INIT_DELAYED_WORK(&hdcp->check_work, पूर्णांकel_hdcp_check_work);
	INIT_WORK(&hdcp->prop_work, पूर्णांकel_hdcp_prop_work);
	init_रुकोqueue_head(&hdcp->cp_irq_queue);

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_hdcp_enable(काष्ठा पूर्णांकel_connector *connector,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config, u8 content_type)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	अचिन्हित दीर्घ check_link_पूर्णांकerval = DRM_HDCP_CHECK_PERIOD_MS;
	पूर्णांक ret = -EINVAL;

	अगर (!hdcp->shim)
		वापस -ENOENT;

	अगर (!connector->encoder) अणु
		drm_err(&dev_priv->drm, "[%s:%d] encoder is not initialized\n",
			connector->base.name, connector->base.base.id);
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&hdcp->mutex);
	mutex_lock(&dig_port->hdcp_mutex);
	drm_WARN_ON(&dev_priv->drm,
		    hdcp->value == DRM_MODE_CONTENT_PROTECTION_ENABLED);
	hdcp->content_type = content_type;

	अगर (पूर्णांकel_crtc_has_type(pipe_config, INTEL_OUTPUT_DP_MST)) अणु
		hdcp->cpu_transcoder = pipe_config->mst_master_transcoder;
		hdcp->stream_transcoder = pipe_config->cpu_transcoder;
	पूर्ण अन्यथा अणु
		hdcp->cpu_transcoder = pipe_config->cpu_transcoder;
		hdcp->stream_transcoder = INVALID_TRANSCODER;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 12)
		dig_port->hdcp_port_data.fw_tc = पूर्णांकel_get_mei_fw_tc(hdcp->cpu_transcoder);

	/*
	 * Considering that HDCP2.2 is more secure than HDCP1.4, If the setup
	 * is capable of HDCP2.2, it is preferred to use HDCP2.2.
	 */
	अगर (पूर्णांकel_hdcp2_capable(connector)) अणु
		ret = _पूर्णांकel_hdcp2_enable(connector);
		अगर (!ret)
			check_link_पूर्णांकerval = DRM_HDCP2_CHECK_PERIOD_MS;
	पूर्ण

	/*
	 * When HDCP2.2 fails and Content Type is not Type1, HDCP1.4 will
	 * be attempted.
	 */
	अगर (ret && पूर्णांकel_hdcp_capable(connector) &&
	    hdcp->content_type != DRM_MODE_HDCP_CONTENT_TYPE1) अणु
		ret = _पूर्णांकel_hdcp_enable(connector);
	पूर्ण

	अगर (!ret) अणु
		schedule_delayed_work(&hdcp->check_work, check_link_पूर्णांकerval);
		पूर्णांकel_hdcp_update_value(connector,
					DRM_MODE_CONTENT_PROTECTION_ENABLED,
					true);
	पूर्ण

	mutex_unlock(&dig_port->hdcp_mutex);
	mutex_unlock(&hdcp->mutex);
	वापस ret;
पूर्ण

पूर्णांक पूर्णांकel_hdcp_disable(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	पूर्णांक ret = 0;

	अगर (!hdcp->shim)
		वापस -ENOENT;

	mutex_lock(&hdcp->mutex);
	mutex_lock(&dig_port->hdcp_mutex);

	अगर (hdcp->value == DRM_MODE_CONTENT_PROTECTION_UNDESIRED)
		जाओ out;

	पूर्णांकel_hdcp_update_value(connector,
				DRM_MODE_CONTENT_PROTECTION_UNDESIRED, false);
	अगर (hdcp->hdcp2_encrypted)
		ret = _पूर्णांकel_hdcp2_disable(connector, false);
	अन्यथा अगर (hdcp->hdcp_encrypted)
		ret = _पूर्णांकel_hdcp_disable(connector);

out:
	mutex_unlock(&dig_port->hdcp_mutex);
	mutex_unlock(&hdcp->mutex);
	cancel_delayed_work_sync(&hdcp->check_work);
	वापस ret;
पूर्ण

व्योम पूर्णांकel_hdcp_update_pipe(काष्ठा पूर्णांकel_atomic_state *state,
			    काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_connector *connector =
				to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	bool content_protection_type_changed, desired_and_not_enabled = false;

	अगर (!connector->hdcp.shim)
		वापस;

	content_protection_type_changed =
		(conn_state->hdcp_content_type != hdcp->content_type &&
		 conn_state->content_protection !=
		 DRM_MODE_CONTENT_PROTECTION_UNDESIRED);

	/*
	 * During the HDCP encryption session अगर Type change is requested,
	 * disable the HDCP and reenable it with new TYPE value.
	 */
	अगर (conn_state->content_protection ==
	    DRM_MODE_CONTENT_PROTECTION_UNDESIRED ||
	    content_protection_type_changed)
		पूर्णांकel_hdcp_disable(connector);

	/*
	 * Mark the hdcp state as DESIRED after the hdcp disable of type
	 * change procedure.
	 */
	अगर (content_protection_type_changed) अणु
		mutex_lock(&hdcp->mutex);
		hdcp->value = DRM_MODE_CONTENT_PROTECTION_DESIRED;
		drm_connector_get(&connector->base);
		schedule_work(&hdcp->prop_work);
		mutex_unlock(&hdcp->mutex);
	पूर्ण

	अगर (conn_state->content_protection ==
	    DRM_MODE_CONTENT_PROTECTION_DESIRED) अणु
		mutex_lock(&hdcp->mutex);
		/* Aव्योम enabling hdcp, अगर it alपढ़ोy ENABLED */
		desired_and_not_enabled =
			hdcp->value != DRM_MODE_CONTENT_PROTECTION_ENABLED;
		mutex_unlock(&hdcp->mutex);
		/*
		 * If HDCP alपढ़ोy ENABLED and CP property is DESIRED, schedule
		 * prop_work to update correct CP property to user space.
		 */
		अगर (!desired_and_not_enabled && !content_protection_type_changed) अणु
			drm_connector_get(&connector->base);
			schedule_work(&hdcp->prop_work);
		पूर्ण
	पूर्ण

	अगर (desired_and_not_enabled || content_protection_type_changed)
		पूर्णांकel_hdcp_enable(connector,
				  crtc_state,
				  (u8)conn_state->hdcp_content_type);
पूर्ण

व्योम पूर्णांकel_hdcp_component_fini(काष्ठा drm_i915_निजी *dev_priv)
अणु
	mutex_lock(&dev_priv->hdcp_comp_mutex);
	अगर (!dev_priv->hdcp_comp_added) अणु
		mutex_unlock(&dev_priv->hdcp_comp_mutex);
		वापस;
	पूर्ण

	dev_priv->hdcp_comp_added = false;
	mutex_unlock(&dev_priv->hdcp_comp_mutex);

	component_del(dev_priv->drm.dev, &i915_hdcp_component_ops);
पूर्ण

व्योम पूर्णांकel_hdcp_cleanup(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;

	अगर (!hdcp->shim)
		वापस;

	/*
	 * If the connector is रेजिस्टरed, it's possible userspace could kick
	 * off another HDCP enable, which would re-spawn the workers.
	 */
	drm_WARN_ON(connector->base.dev,
		connector->base.registration_state == DRM_CONNECTOR_REGISTERED);

	/*
	 * Now that the connector is not रेजिस्टरed, check_work won't be run,
	 * but cancel any outstanding instances of it
	 */
	cancel_delayed_work_sync(&hdcp->check_work);

	/*
	 * We करोn't cancel prop_work in the same way as check_work since it
	 * requires connection_mutex which could be held जबतक calling this
	 * function. Instead, we rely on the connector references grabbed beक्रमe
	 * scheduling prop_work to ensure the connector is alive when prop_work
	 * is run. So अगर we're in the destroy path (which is where this
	 * function should be called), we're "guaranteed" that prop_work is not
	 * active (tl;dr This Should Never Happen).
	 */
	drm_WARN_ON(connector->base.dev, work_pending(&hdcp->prop_work));

	mutex_lock(&hdcp->mutex);
	hdcp->shim = शून्य;
	mutex_unlock(&hdcp->mutex);
पूर्ण

व्योम पूर्णांकel_hdcp_atomic_check(काष्ठा drm_connector *connector,
			     काष्ठा drm_connector_state *old_state,
			     काष्ठा drm_connector_state *new_state)
अणु
	u64 old_cp = old_state->content_protection;
	u64 new_cp = new_state->content_protection;
	काष्ठा drm_crtc_state *crtc_state;

	अगर (!new_state->crtc) अणु
		/*
		 * If the connector is being disabled with CP enabled, mark it
		 * desired so it's re-enabled when the connector is brought back
		 */
		अगर (old_cp == DRM_MODE_CONTENT_PROTECTION_ENABLED)
			new_state->content_protection =
				DRM_MODE_CONTENT_PROTECTION_DESIRED;
		वापस;
	पूर्ण

	crtc_state = drm_atomic_get_new_crtc_state(new_state->state,
						   new_state->crtc);
	/*
	 * Fix the HDCP uapi content protection state in हाल of modeset.
	 * FIXME: As per HDCP content protection property uapi करोc, an uevent()
	 * need to be sent अगर there is transition from ENABLED->DESIRED.
	 */
	अगर (drm_atomic_crtc_needs_modeset(crtc_state) &&
	    (old_cp == DRM_MODE_CONTENT_PROTECTION_ENABLED &&
	    new_cp != DRM_MODE_CONTENT_PROTECTION_UNDESIRED))
		new_state->content_protection =
			DRM_MODE_CONTENT_PROTECTION_DESIRED;

	/*
	 * Nothing to करो अगर the state didn't change, or HDCP was activated since
	 * the last commit. And also no change in hdcp content type.
	 */
	अगर (old_cp == new_cp ||
	    (old_cp == DRM_MODE_CONTENT_PROTECTION_DESIRED &&
	     new_cp == DRM_MODE_CONTENT_PROTECTION_ENABLED)) अणु
		अगर (old_state->hdcp_content_type ==
				new_state->hdcp_content_type)
			वापस;
	पूर्ण

	crtc_state->mode_changed = true;
पूर्ण

/* Handles the CP_IRQ उठाओd from the DP HDCP sink */
व्योम पूर्णांकel_hdcp_handle_cp_irq(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;

	अगर (!hdcp->shim)
		वापस;

	atomic_inc(&connector->hdcp.cp_irq_count);
	wake_up_all(&connector->hdcp.cp_irq_queue);

	schedule_delayed_work(&hdcp->check_work, 0);
पूर्ण
