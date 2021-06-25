<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright (C) 2020 Google, Inc.
 *
 * Authors:
 * Sean Paul <seanpaul@chromium.org>
 */

#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_dp_mst_helper.h>
#समावेश <drm/drm_hdcp.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "intel_display_types.h"
#समावेश "intel_ddi.h"
#समावेश "intel_dp.h"
#समावेश "intel_hdcp.h"

अटल अचिन्हित पूर्णांक transcoder_to_stream_enc_status(क्रमागत transcoder cpu_transcoder)
अणु
	u32 stream_enc_mask;

	चयन (cpu_transcoder) अणु
	हाल TRANSCODER_A:
		stream_enc_mask = HDCP_STATUS_STREAM_A_ENC;
		अवरोध;
	हाल TRANSCODER_B:
		stream_enc_mask = HDCP_STATUS_STREAM_B_ENC;
		अवरोध;
	हाल TRANSCODER_C:
		stream_enc_mask = HDCP_STATUS_STREAM_C_ENC;
		अवरोध;
	हाल TRANSCODER_D:
		stream_enc_mask = HDCP_STATUS_STREAM_D_ENC;
		अवरोध;
	शेष:
		stream_enc_mask = 0;
	पूर्ण

	वापस stream_enc_mask;
पूर्ण

अटल व्योम पूर्णांकel_dp_hdcp_रुको_क्रम_cp_irq(काष्ठा पूर्णांकel_hdcp *hdcp, पूर्णांक समयout)
अणु
	दीर्घ ret;

#घोषणा C (hdcp->cp_irq_count_cached != atomic_पढ़ो(&hdcp->cp_irq_count))
	ret = रुको_event_पूर्णांकerruptible_समयout(hdcp->cp_irq_queue, C,
					       msecs_to_jअगरfies(समयout));

	अगर (!ret)
		DRM_DEBUG_KMS("Timedout at waiting for CP_IRQ\n");
पूर्ण

अटल
पूर्णांक पूर्णांकel_dp_hdcp_ग_लिखो_an_aksv(काष्ठा पूर्णांकel_digital_port *dig_port,
				u8 *an)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	u8 aksv[DRM_HDCP_KSV_LEN] = अणुपूर्ण;
	sमाप_प्रकार dpcd_ret;

	/* Output An first, that's easy */
	dpcd_ret = drm_dp_dpcd_ग_लिखो(&dig_port->dp.aux, DP_AUX_HDCP_AN,
				     an, DRM_HDCP_AN_LEN);
	अगर (dpcd_ret != DRM_HDCP_AN_LEN) अणु
		drm_dbg_kms(&i915->drm,
			    "Failed to write An over DP/AUX (%zd)\n",
			    dpcd_ret);
		वापस dpcd_ret >= 0 ? -EIO : dpcd_ret;
	पूर्ण

	/*
	 * Since Aksv is Oh-So-Secret, we can't access it in software. So we
	 * send an empty buffer of the correct length through the DP helpers. On
	 * the other side, in the transfer hook, we'll generate a flag based on
	 * the destination address which will tickle the hardware to output the
	 * Aksv on our behalf after the header is sent.
	 */
	dpcd_ret = drm_dp_dpcd_ग_लिखो(&dig_port->dp.aux, DP_AUX_HDCP_AKSV,
				     aksv, DRM_HDCP_KSV_LEN);
	अगर (dpcd_ret != DRM_HDCP_KSV_LEN) अणु
		drm_dbg_kms(&i915->drm,
			    "Failed to write Aksv over DP/AUX (%zd)\n",
			    dpcd_ret);
		वापस dpcd_ret >= 0 ? -EIO : dpcd_ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_hdcp_पढ़ो_bksv(काष्ठा पूर्णांकel_digital_port *dig_port,
				   u8 *bksv)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	sमाप_प्रकार ret;

	ret = drm_dp_dpcd_पढ़ो(&dig_port->dp.aux, DP_AUX_HDCP_BKSV, bksv,
			       DRM_HDCP_KSV_LEN);
	अगर (ret != DRM_HDCP_KSV_LEN) अणु
		drm_dbg_kms(&i915->drm,
			    "Read Bksv from DP/AUX failed (%zd)\n", ret);
		वापस ret >= 0 ? -EIO : ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_hdcp_पढ़ो_bstatus(काष्ठा पूर्णांकel_digital_port *dig_port,
				      u8 *bstatus)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	sमाप_प्रकार ret;

	/*
	 * For some reason the HDMI and DP HDCP specs call this रेजिस्टर
	 * definition by dअगरferent names. In the HDMI spec, it's called BSTATUS,
	 * but in DP it's called BINFO.
	 */
	ret = drm_dp_dpcd_पढ़ो(&dig_port->dp.aux, DP_AUX_HDCP_BINFO,
			       bstatus, DRM_HDCP_BSTATUS_LEN);
	अगर (ret != DRM_HDCP_BSTATUS_LEN) अणु
		drm_dbg_kms(&i915->drm,
			    "Read bstatus from DP/AUX failed (%zd)\n", ret);
		वापस ret >= 0 ? -EIO : ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल
पूर्णांक पूर्णांकel_dp_hdcp_पढ़ो_bcaps(काष्ठा पूर्णांकel_digital_port *dig_port,
			     u8 *bcaps)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	sमाप_प्रकार ret;

	ret = drm_dp_dpcd_पढ़ो(&dig_port->dp.aux, DP_AUX_HDCP_BCAPS,
			       bcaps, 1);
	अगर (ret != 1) अणु
		drm_dbg_kms(&i915->drm,
			    "Read bcaps from DP/AUX failed (%zd)\n", ret);
		वापस ret >= 0 ? -EIO : ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल
पूर्णांक पूर्णांकel_dp_hdcp_repeater_present(काष्ठा पूर्णांकel_digital_port *dig_port,
				   bool *repeater_present)
अणु
	sमाप_प्रकार ret;
	u8 bcaps;

	ret = पूर्णांकel_dp_hdcp_पढ़ो_bcaps(dig_port, &bcaps);
	अगर (ret)
		वापस ret;

	*repeater_present = bcaps & DP_BCAPS_REPEATER_PRESENT;
	वापस 0;
पूर्ण

अटल
पूर्णांक पूर्णांकel_dp_hdcp_पढ़ो_ri_prime(काष्ठा पूर्णांकel_digital_port *dig_port,
				u8 *ri_prime)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	sमाप_प्रकार ret;

	ret = drm_dp_dpcd_पढ़ो(&dig_port->dp.aux, DP_AUX_HDCP_RI_PRIME,
			       ri_prime, DRM_HDCP_RI_LEN);
	अगर (ret != DRM_HDCP_RI_LEN) अणु
		drm_dbg_kms(&i915->drm, "Read Ri' from DP/AUX failed (%zd)\n",
			    ret);
		वापस ret >= 0 ? -EIO : ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल
पूर्णांक पूर्णांकel_dp_hdcp_पढ़ो_ksv_पढ़ोy(काष्ठा पूर्णांकel_digital_port *dig_port,
				 bool *ksv_पढ़ोy)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	sमाप_प्रकार ret;
	u8 bstatus;

	ret = drm_dp_dpcd_पढ़ो(&dig_port->dp.aux, DP_AUX_HDCP_BSTATUS,
			       &bstatus, 1);
	अगर (ret != 1) अणु
		drm_dbg_kms(&i915->drm,
			    "Read bstatus from DP/AUX failed (%zd)\n", ret);
		वापस ret >= 0 ? -EIO : ret;
	पूर्ण
	*ksv_पढ़ोy = bstatus & DP_BSTATUS_READY;
	वापस 0;
पूर्ण

अटल
पूर्णांक पूर्णांकel_dp_hdcp_पढ़ो_ksv_fअगरo(काष्ठा पूर्णांकel_digital_port *dig_port,
				पूर्णांक num_करोwnstream, u8 *ksv_fअगरo)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	sमाप_प्रकार ret;
	पूर्णांक i;

	/* KSV list is पढ़ो via 15 byte winकरोw (3 entries @ 5 bytes each) */
	क्रम (i = 0; i < num_करोwnstream; i += 3) अणु
		माप_प्रकार len = min(num_करोwnstream - i, 3) * DRM_HDCP_KSV_LEN;
		ret = drm_dp_dpcd_पढ़ो(&dig_port->dp.aux,
				       DP_AUX_HDCP_KSV_FIFO,
				       ksv_fअगरo + i * DRM_HDCP_KSV_LEN,
				       len);
		अगर (ret != len) अणु
			drm_dbg_kms(&i915->drm,
				    "Read ksv[%d] from DP/AUX failed (%zd)\n",
				    i, ret);
			वापस ret >= 0 ? -EIO : ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल
पूर्णांक पूर्णांकel_dp_hdcp_पढ़ो_v_prime_part(काष्ठा पूर्णांकel_digital_port *dig_port,
				    पूर्णांक i, u32 *part)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	sमाप_प्रकार ret;

	अगर (i >= DRM_HDCP_V_PRIME_NUM_PARTS)
		वापस -EINVAL;

	ret = drm_dp_dpcd_पढ़ो(&dig_port->dp.aux,
			       DP_AUX_HDCP_V_PRIME(i), part,
			       DRM_HDCP_V_PRIME_PART_LEN);
	अगर (ret != DRM_HDCP_V_PRIME_PART_LEN) अणु
		drm_dbg_kms(&i915->drm,
			    "Read v'[%d] from DP/AUX failed (%zd)\n", i, ret);
		वापस ret >= 0 ? -EIO : ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल
पूर्णांक पूर्णांकel_dp_hdcp_toggle_संकेतling(काष्ठा पूर्णांकel_digital_port *dig_port,
				    क्रमागत transcoder cpu_transcoder,
				    bool enable)
अणु
	/* Not used क्रम single stream DisplayPort setups */
	वापस 0;
पूर्ण

अटल
bool पूर्णांकel_dp_hdcp_check_link(काष्ठा पूर्णांकel_digital_port *dig_port,
			      काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	sमाप_प्रकार ret;
	u8 bstatus;

	ret = drm_dp_dpcd_पढ़ो(&dig_port->dp.aux, DP_AUX_HDCP_BSTATUS,
			       &bstatus, 1);
	अगर (ret != 1) अणु
		drm_dbg_kms(&i915->drm,
			    "Read bstatus from DP/AUX failed (%zd)\n", ret);
		वापस false;
	पूर्ण

	वापस !(bstatus & (DP_BSTATUS_LINK_FAILURE | DP_BSTATUS_REAUTH_REQ));
पूर्ण

अटल
पूर्णांक पूर्णांकel_dp_hdcp_capable(काष्ठा पूर्णांकel_digital_port *dig_port,
			  bool *hdcp_capable)
अणु
	sमाप_प्रकार ret;
	u8 bcaps;

	ret = पूर्णांकel_dp_hdcp_पढ़ो_bcaps(dig_port, &bcaps);
	अगर (ret)
		वापस ret;

	*hdcp_capable = bcaps & DP_BCAPS_HDCP_CAPABLE;
	वापस 0;
पूर्ण

काष्ठा hdcp2_dp_errata_stream_type अणु
	u8	msg_id;
	u8	stream_type;
पूर्ण __packed;

काष्ठा hdcp2_dp_msg_data अणु
	u8 msg_id;
	u32 offset;
	bool msg_detectable;
	u32 समयout;
	u32 समयout2; /* Added क्रम non_paired situation */
	/* Timeout to पढ़ो entire msg */
	u32 msg_पढ़ो_समयout;
पूर्ण;

अटल स्थिर काष्ठा hdcp2_dp_msg_data hdcp2_dp_msg_data[] = अणु
	अणु HDCP_2_2_AKE_INIT, DP_HDCP_2_2_AKE_INIT_OFFSET, false, 0, 0, 0पूर्ण,
	अणु HDCP_2_2_AKE_SEND_CERT, DP_HDCP_2_2_AKE_SEND_CERT_OFFSET,
	  false, HDCP_2_2_CERT_TIMEOUT_MS, 0, HDCP_2_2_DP_CERT_READ_TIMEOUT_MSपूर्ण,
	अणु HDCP_2_2_AKE_NO_STORED_KM, DP_HDCP_2_2_AKE_NO_STORED_KM_OFFSET,
	  false, 0, 0, 0 पूर्ण,
	अणु HDCP_2_2_AKE_STORED_KM, DP_HDCP_2_2_AKE_STORED_KM_OFFSET,
	  false, 0, 0, 0 पूर्ण,
	अणु HDCP_2_2_AKE_SEND_HPRIME, DP_HDCP_2_2_AKE_SEND_HPRIME_OFFSET,
	  true, HDCP_2_2_HPRIME_PAIRED_TIMEOUT_MS,
	  HDCP_2_2_HPRIME_NO_PAIRED_TIMEOUT_MS, HDCP_2_2_DP_HPRIME_READ_TIMEOUT_MSपूर्ण,
	अणु HDCP_2_2_AKE_SEND_PAIRING_INFO,
	  DP_HDCP_2_2_AKE_SEND_PAIRING_INFO_OFFSET, true,
	  HDCP_2_2_PAIRING_TIMEOUT_MS, 0, HDCP_2_2_DP_PAIRING_READ_TIMEOUT_MS पूर्ण,
	अणु HDCP_2_2_LC_INIT, DP_HDCP_2_2_LC_INIT_OFFSET, false, 0, 0, 0 पूर्ण,
	अणु HDCP_2_2_LC_SEND_LPRIME, DP_HDCP_2_2_LC_SEND_LPRIME_OFFSET,
	  false, HDCP_2_2_DP_LPRIME_TIMEOUT_MS, 0, 0 पूर्ण,
	अणु HDCP_2_2_SKE_SEND_EKS, DP_HDCP_2_2_SKE_SEND_EKS_OFFSET, false,
	  0, 0, 0 पूर्ण,
	अणु HDCP_2_2_REP_SEND_RECVID_LIST,
	  DP_HDCP_2_2_REP_SEND_RECVID_LIST_OFFSET, true,
	  HDCP_2_2_RECVID_LIST_TIMEOUT_MS, 0, 0 पूर्ण,
	अणु HDCP_2_2_REP_SEND_ACK, DP_HDCP_2_2_REP_SEND_ACK_OFFSET, false,
	  0, 0, 0 पूर्ण,
	अणु HDCP_2_2_REP_STREAM_MANAGE,
	  DP_HDCP_2_2_REP_STREAM_MANAGE_OFFSET, false,
	  0, 0, 0पूर्ण,
	अणु HDCP_2_2_REP_STREAM_READY, DP_HDCP_2_2_REP_STREAM_READY_OFFSET,
	  false, HDCP_2_2_STREAM_READY_TIMEOUT_MS, 0, 0 पूर्ण,
/* local define to shovel this through the ग_लिखो_2_2 पूर्णांकerface */
#घोषणा HDCP_2_2_ERRATA_DP_STREAM_TYPE	50
	अणु HDCP_2_2_ERRATA_DP_STREAM_TYPE,
	  DP_HDCP_2_2_REG_STREAM_TYPE_OFFSET, false,
	  0, 0 पूर्ण,
पूर्ण;

अटल पूर्णांक
पूर्णांकel_dp_hdcp2_पढ़ो_rx_status(काष्ठा पूर्णांकel_digital_port *dig_port,
			      u8 *rx_status)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	sमाप_प्रकार ret;

	ret = drm_dp_dpcd_पढ़ो(&dig_port->dp.aux,
			       DP_HDCP_2_2_REG_RXSTATUS_OFFSET, rx_status,
			       HDCP_2_2_DP_RXSTATUS_LEN);
	अगर (ret != HDCP_2_2_DP_RXSTATUS_LEN) अणु
		drm_dbg_kms(&i915->drm,
			    "Read bstatus from DP/AUX failed (%zd)\n", ret);
		वापस ret >= 0 ? -EIO : ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल
पूर्णांक hdcp2_detect_msg_availability(काष्ठा पूर्णांकel_digital_port *dig_port,
				  u8 msg_id, bool *msg_पढ़ोy)
अणु
	u8 rx_status;
	पूर्णांक ret;

	*msg_पढ़ोy = false;
	ret = पूर्णांकel_dp_hdcp2_पढ़ो_rx_status(dig_port, &rx_status);
	अगर (ret < 0)
		वापस ret;

	चयन (msg_id) अणु
	हाल HDCP_2_2_AKE_SEND_HPRIME:
		अगर (HDCP_2_2_DP_RXSTATUS_H_PRIME(rx_status))
			*msg_पढ़ोy = true;
		अवरोध;
	हाल HDCP_2_2_AKE_SEND_PAIRING_INFO:
		अगर (HDCP_2_2_DP_RXSTATUS_PAIRING(rx_status))
			*msg_पढ़ोy = true;
		अवरोध;
	हाल HDCP_2_2_REP_SEND_RECVID_LIST:
		अगर (HDCP_2_2_DP_RXSTATUS_READY(rx_status))
			*msg_पढ़ोy = true;
		अवरोध;
	शेष:
		DRM_ERROR("Unidentified msg_id: %d\n", msg_id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
पूर्णांकel_dp_hdcp2_रुको_क्रम_msg(काष्ठा पूर्णांकel_digital_port *dig_port,
			    स्थिर काष्ठा hdcp2_dp_msg_data *hdcp2_msg_data)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	काष्ठा पूर्णांकel_dp *dp = &dig_port->dp;
	काष्ठा पूर्णांकel_hdcp *hdcp = &dp->attached_connector->hdcp;
	u8 msg_id = hdcp2_msg_data->msg_id;
	पूर्णांक ret, समयout;
	bool msg_पढ़ोy = false;

	अगर (msg_id == HDCP_2_2_AKE_SEND_HPRIME && !hdcp->is_paired)
		समयout = hdcp2_msg_data->समयout2;
	अन्यथा
		समयout = hdcp2_msg_data->समयout;

	/*
	 * There is no way to detect the CERT, LPRIME and STREAM_READY
	 * availability. So Wait क्रम समयout and पढ़ो the msg.
	 */
	अगर (!hdcp2_msg_data->msg_detectable) अणु
		mdelay(समयout);
		ret = 0;
	पूर्ण अन्यथा अणु
		/*
		 * As we want to check the msg availability at समयout, Ignoring
		 * the समयout at रुको क्रम CP_IRQ.
		 */
		पूर्णांकel_dp_hdcp_रुको_क्रम_cp_irq(hdcp, समयout);
		ret = hdcp2_detect_msg_availability(dig_port,
						    msg_id, &msg_पढ़ोy);
		अगर (!msg_पढ़ोy)
			ret = -ETIMEDOUT;
	पूर्ण

	अगर (ret)
		drm_dbg_kms(&i915->drm,
			    "msg_id %d, ret %d, timeout(mSec): %d\n",
			    hdcp2_msg_data->msg_id, ret, समयout);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hdcp2_dp_msg_data *get_hdcp2_dp_msg_data(u8 msg_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hdcp2_dp_msg_data); i++)
		अगर (hdcp2_dp_msg_data[i].msg_id == msg_id)
			वापस &hdcp2_dp_msg_data[i];

	वापस शून्य;
पूर्ण

अटल
पूर्णांक पूर्णांकel_dp_hdcp2_ग_लिखो_msg(काष्ठा पूर्णांकel_digital_port *dig_port,
			     व्योम *buf, माप_प्रकार size)
अणु
	काष्ठा पूर्णांकel_dp *dp = &dig_port->dp;
	काष्ठा पूर्णांकel_hdcp *hdcp = &dp->attached_connector->hdcp;
	अचिन्हित पूर्णांक offset;
	u8 *byte = buf;
	sमाप_प्रकार ret, bytes_to_ग_लिखो, len;
	स्थिर काष्ठा hdcp2_dp_msg_data *hdcp2_msg_data;

	hdcp2_msg_data = get_hdcp2_dp_msg_data(*byte);
	अगर (!hdcp2_msg_data)
		वापस -EINVAL;

	offset = hdcp2_msg_data->offset;

	/* No msg_id in DP HDCP2.2 msgs */
	bytes_to_ग_लिखो = size - 1;
	byte++;

	hdcp->cp_irq_count_cached = atomic_पढ़ो(&hdcp->cp_irq_count);

	जबतक (bytes_to_ग_लिखो) अणु
		len = bytes_to_ग_लिखो > DP_AUX_MAX_PAYLOAD_BYTES ?
				DP_AUX_MAX_PAYLOAD_BYTES : bytes_to_ग_लिखो;

		ret = drm_dp_dpcd_ग_लिखो(&dig_port->dp.aux,
					offset, (व्योम *)byte, len);
		अगर (ret < 0)
			वापस ret;

		bytes_to_ग_लिखो -= ret;
		byte += ret;
		offset += ret;
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक
get_rxinfo_hdcp_1_dev_करोwnstream(काष्ठा पूर्णांकel_digital_port *dig_port, bool *hdcp_1_x)
अणु
	u8 rx_info[HDCP_2_2_RXINFO_LEN];
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ो(&dig_port->dp.aux,
			       DP_HDCP_2_2_REG_RXINFO_OFFSET,
			       (व्योम *)rx_info, HDCP_2_2_RXINFO_LEN);

	अगर (ret != HDCP_2_2_RXINFO_LEN)
		वापस ret >= 0 ? -EIO : ret;

	*hdcp_1_x = HDCP_2_2_HDCP1_DEVICE_CONNECTED(rx_info[1]) ? true : false;
	वापस 0;
पूर्ण

अटल
sमाप_प्रकार get_receiver_id_list_size(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	u8 rx_info[HDCP_2_2_RXINFO_LEN];
	u32 dev_cnt;
	sमाप_प्रकार ret;

	ret = drm_dp_dpcd_पढ़ो(&dig_port->dp.aux,
			       DP_HDCP_2_2_REG_RXINFO_OFFSET,
			       (व्योम *)rx_info, HDCP_2_2_RXINFO_LEN);
	अगर (ret != HDCP_2_2_RXINFO_LEN)
		वापस ret >= 0 ? -EIO : ret;

	dev_cnt = (HDCP_2_2_DEV_COUNT_HI(rx_info[0]) << 4 |
		   HDCP_2_2_DEV_COUNT_LO(rx_info[1]));

	अगर (dev_cnt > HDCP_2_2_MAX_DEVICE_COUNT)
		dev_cnt = HDCP_2_2_MAX_DEVICE_COUNT;

	ret = माप(काष्ठा hdcp2_rep_send_receiverid_list) -
		HDCP_2_2_RECEIVER_IDS_MAX_LEN +
		(dev_cnt * HDCP_2_2_RECEIVER_ID_LEN);

	वापस ret;
पूर्ण

अटल
पूर्णांक पूर्णांकel_dp_hdcp2_पढ़ो_msg(काष्ठा पूर्णांकel_digital_port *dig_port,
			    u8 msg_id, व्योम *buf, माप_प्रकार size)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	अचिन्हित पूर्णांक offset;
	u8 *byte = buf;
	sमाप_प्रकार ret, bytes_to_recv, len;
	स्थिर काष्ठा hdcp2_dp_msg_data *hdcp2_msg_data;
	kसमय_प्रकार msg_end;
	bool msg_expired;

	hdcp2_msg_data = get_hdcp2_dp_msg_data(msg_id);
	अगर (!hdcp2_msg_data)
		वापस -EINVAL;
	offset = hdcp2_msg_data->offset;

	ret = पूर्णांकel_dp_hdcp2_रुको_क्रम_msg(dig_port, hdcp2_msg_data);
	अगर (ret < 0)
		वापस ret;

	अगर (msg_id == HDCP_2_2_REP_SEND_RECVID_LIST) अणु
		ret = get_receiver_id_list_size(dig_port);
		अगर (ret < 0)
			वापस ret;

		size = ret;
	पूर्ण
	bytes_to_recv = size - 1;

	/* DP adaptation msgs has no msg_id */
	byte++;

	जबतक (bytes_to_recv) अणु
		len = bytes_to_recv > DP_AUX_MAX_PAYLOAD_BYTES ?
		      DP_AUX_MAX_PAYLOAD_BYTES : bytes_to_recv;

		/* Entire msg पढ़ो समयout since initiate of msg पढ़ो */
		अगर (bytes_to_recv == size - 1 && hdcp2_msg_data->msg_पढ़ो_समयout > 0)
			msg_end = kसमय_add_ms(kसमय_get_raw(),
					       hdcp2_msg_data->msg_पढ़ो_समयout);

		ret = drm_dp_dpcd_पढ़ो(&dig_port->dp.aux, offset,
				       (व्योम *)byte, len);
		अगर (ret < 0) अणु
			drm_dbg_kms(&i915->drm, "msg_id %d, ret %zd\n",
				    msg_id, ret);
			वापस ret;
		पूर्ण

		bytes_to_recv -= ret;
		byte += ret;
		offset += ret;
	पूर्ण

	अगर (hdcp2_msg_data->msg_पढ़ो_समयout > 0) अणु
		msg_expired = kसमय_after(kसमय_get_raw(), msg_end);
		अगर (msg_expired) अणु
			drm_dbg_kms(&i915->drm, "msg_id %d, entire msg read timeout(mSec): %d\n",
				    msg_id, hdcp2_msg_data->msg_पढ़ो_समयout);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	byte = buf;
	*byte = msg_id;

	वापस size;
पूर्ण

अटल
पूर्णांक पूर्णांकel_dp_hdcp2_config_stream_type(काष्ठा पूर्णांकel_digital_port *dig_port,
				      bool is_repeater, u8 content_type)
अणु
	पूर्णांक ret;
	काष्ठा hdcp2_dp_errata_stream_type stream_type_msg;

	अगर (is_repeater)
		वापस 0;

	/*
	 * Errata क्रम DP: As Stream type is used क्रम encryption, Receiver
	 * should be communicated with stream type क्रम the decryption of the
	 * content.
	 * Repeater will be communicated with stream type as a part of it's
	 * auth later in समय.
	 */
	stream_type_msg.msg_id = HDCP_2_2_ERRATA_DP_STREAM_TYPE;
	stream_type_msg.stream_type = content_type;

	ret =  पूर्णांकel_dp_hdcp2_ग_लिखो_msg(dig_port, &stream_type_msg,
					माप(stream_type_msg));

	वापस ret < 0 ? ret : 0;

पूर्ण

अटल
पूर्णांक पूर्णांकel_dp_hdcp2_check_link(काष्ठा पूर्णांकel_digital_port *dig_port,
			      काष्ठा पूर्णांकel_connector *connector)
अणु
	u8 rx_status;
	पूर्णांक ret;

	ret = पूर्णांकel_dp_hdcp2_पढ़ो_rx_status(dig_port, &rx_status);
	अगर (ret)
		वापस ret;

	अगर (HDCP_2_2_DP_RXSTATUS_REAUTH_REQ(rx_status))
		ret = HDCP_REAUTH_REQUEST;
	अन्यथा अगर (HDCP_2_2_DP_RXSTATUS_LINK_FAILED(rx_status))
		ret = HDCP_LINK_INTEGRITY_FAILURE;
	अन्यथा अगर (HDCP_2_2_DP_RXSTATUS_READY(rx_status))
		ret = HDCP_TOPOLOGY_CHANGE;

	वापस ret;
पूर्ण

अटल
पूर्णांक पूर्णांकel_dp_hdcp2_capable(काष्ठा पूर्णांकel_digital_port *dig_port,
			   bool *capable)
अणु
	u8 rx_caps[3];
	पूर्णांक ret;

	*capable = false;
	ret = drm_dp_dpcd_पढ़ो(&dig_port->dp.aux,
			       DP_HDCP_2_2_REG_RX_CAPS_OFFSET,
			       rx_caps, HDCP_2_2_RXCAPS_LEN);
	अगर (ret != HDCP_2_2_RXCAPS_LEN)
		वापस ret >= 0 ? -EIO : ret;

	अगर (rx_caps[0] == HDCP_2_2_RX_CAPS_VERSION_VAL &&
	    HDCP_2_2_DP_HDCP_CAPABLE(rx_caps[2]))
		*capable = true;

	वापस 0;
पूर्ण

अटल
पूर्णांक पूर्णांकel_dp_mst_streams_type1_capable(काष्ठा पूर्णांकel_connector *connector,
				       bool *capable)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	पूर्णांक ret;
	bool hdcp_1_x;

	ret = get_rxinfo_hdcp_1_dev_करोwnstream(dig_port, &hdcp_1_x);
	अगर (ret) अणु
		drm_dbg_kms(&i915->drm,
			    "[%s:%d] failed to read RxInfo ret=%d\n",
			    connector->base.name, connector->base.base.id, ret);
		वापस ret;
	पूर्ण

	*capable = !hdcp_1_x;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_hdcp_shim पूर्णांकel_dp_hdcp_shim = अणु
	.ग_लिखो_an_aksv = पूर्णांकel_dp_hdcp_ग_लिखो_an_aksv,
	.पढ़ो_bksv = पूर्णांकel_dp_hdcp_पढ़ो_bksv,
	.पढ़ो_bstatus = पूर्णांकel_dp_hdcp_पढ़ो_bstatus,
	.repeater_present = पूर्णांकel_dp_hdcp_repeater_present,
	.पढ़ो_ri_prime = पूर्णांकel_dp_hdcp_पढ़ो_ri_prime,
	.पढ़ो_ksv_पढ़ोy = पूर्णांकel_dp_hdcp_पढ़ो_ksv_पढ़ोy,
	.पढ़ो_ksv_fअगरo = पूर्णांकel_dp_hdcp_पढ़ो_ksv_fअगरo,
	.पढ़ो_v_prime_part = पूर्णांकel_dp_hdcp_पढ़ो_v_prime_part,
	.toggle_संकेतling = पूर्णांकel_dp_hdcp_toggle_संकेतling,
	.check_link = पूर्णांकel_dp_hdcp_check_link,
	.hdcp_capable = पूर्णांकel_dp_hdcp_capable,
	.ग_लिखो_2_2_msg = पूर्णांकel_dp_hdcp2_ग_लिखो_msg,
	.पढ़ो_2_2_msg = पूर्णांकel_dp_hdcp2_पढ़ो_msg,
	.config_stream_type = पूर्णांकel_dp_hdcp2_config_stream_type,
	.check_2_2_link = पूर्णांकel_dp_hdcp2_check_link,
	.hdcp_2_2_capable = पूर्णांकel_dp_hdcp2_capable,
	.protocol = HDCP_PROTOCOL_DP,
पूर्ण;

अटल पूर्णांक
पूर्णांकel_dp_mst_toggle_hdcp_stream_select(काष्ठा पूर्णांकel_connector *connector,
				       bool enable)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	पूर्णांक ret;

	ret = पूर्णांकel_ddi_toggle_hdcp_bits(&dig_port->base,
					 hdcp->stream_transcoder, enable,
					 TRANS_DDI_HDCP_SELECT);
	अगर (ret)
		drm_err(&i915->drm, "%s HDCP stream select failed (%d)\n",
			enable ? "Enable" : "Disable", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक
पूर्णांकel_dp_mst_hdcp_stream_encryption(काष्ठा पूर्णांकel_connector *connector,
				    bool enable)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	क्रमागत port port = dig_port->base.port;
	क्रमागत transcoder cpu_transcoder = hdcp->stream_transcoder;
	u32 stream_enc_status;
	पूर्णांक ret;

	ret = पूर्णांकel_dp_mst_toggle_hdcp_stream_select(connector, enable);
	अगर (ret)
		वापस ret;

	stream_enc_status =  transcoder_to_stream_enc_status(cpu_transcoder);
	अगर (!stream_enc_status)
		वापस -EINVAL;

	/* Wait क्रम encryption confirmation */
	अगर (पूर्णांकel_de_रुको_क्रम_रेजिस्टर(i915,
				       HDCP_STATUS(i915, cpu_transcoder, port),
				       stream_enc_status,
				       enable ? stream_enc_status : 0,
				       HDCP_ENCRYPT_STATUS_CHANGE_TIMEOUT_MS)) अणु
		drm_err(&i915->drm, "Timed out waiting for transcoder: %s stream encryption %s\n",
			transcoder_name(cpu_transcoder), enable ? "enabled" : "disabled");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
पूर्णांकel_dp_mst_hdcp2_stream_encryption(काष्ठा पूर्णांकel_connector *connector,
				     bool enable)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_attached_dig_port(connector);
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	काष्ठा hdcp_port_data *data = &dig_port->hdcp_port_data;
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	क्रमागत transcoder cpu_transcoder = hdcp->stream_transcoder;
	क्रमागत pipe pipe = (क्रमागत pipe)cpu_transcoder;
	क्रमागत port port = dig_port->base.port;
	पूर्णांक ret;

	drm_WARN_ON(&i915->drm, enable &&
		    !!(पूर्णांकel_de_पढ़ो(i915, HDCP2_AUTH_STREAM(i915, cpu_transcoder, port))
		    & AUTH_STREAM_TYPE) != data->streams[0].stream_type);

	ret = पूर्णांकel_dp_mst_toggle_hdcp_stream_select(connector, enable);
	अगर (ret)
		वापस ret;

	/* Wait क्रम encryption confirmation */
	अगर (पूर्णांकel_de_रुको_क्रम_रेजिस्टर(i915,
				       HDCP2_STREAM_STATUS(i915, cpu_transcoder, pipe),
				       STREAM_ENCRYPTION_STATUS,
				       enable ? STREAM_ENCRYPTION_STATUS : 0,
				       HDCP_ENCRYPT_STATUS_CHANGE_TIMEOUT_MS)) अणु
		drm_err(&i915->drm, "Timed out waiting for transcoder: %s stream encryption %s\n",
			transcoder_name(cpu_transcoder), enable ? "enabled" : "disabled");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल
पूर्णांक पूर्णांकel_dp_mst_hdcp2_check_link(काष्ठा पूर्णांकel_digital_port *dig_port,
				  काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_hdcp *hdcp = &connector->hdcp;
	पूर्णांक ret;

	/*
	 * We करो need to करो the Link Check only क्रम the connector involved with
	 * HDCP port authentication and encryption.
	 * We can re-use the hdcp->is_repeater flag to know that the connector
	 * involved with HDCP port authentication and encryption.
	 */
	अगर (hdcp->is_repeater) अणु
		ret = पूर्णांकel_dp_hdcp2_check_link(dig_port, connector);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_hdcp_shim पूर्णांकel_dp_mst_hdcp_shim = अणु
	.ग_लिखो_an_aksv = पूर्णांकel_dp_hdcp_ग_लिखो_an_aksv,
	.पढ़ो_bksv = पूर्णांकel_dp_hdcp_पढ़ो_bksv,
	.पढ़ो_bstatus = पूर्णांकel_dp_hdcp_पढ़ो_bstatus,
	.repeater_present = पूर्णांकel_dp_hdcp_repeater_present,
	.पढ़ो_ri_prime = पूर्णांकel_dp_hdcp_पढ़ो_ri_prime,
	.पढ़ो_ksv_पढ़ोy = पूर्णांकel_dp_hdcp_पढ़ो_ksv_पढ़ोy,
	.पढ़ो_ksv_fअगरo = पूर्णांकel_dp_hdcp_पढ़ो_ksv_fअगरo,
	.पढ़ो_v_prime_part = पूर्णांकel_dp_hdcp_पढ़ो_v_prime_part,
	.toggle_संकेतling = पूर्णांकel_dp_hdcp_toggle_संकेतling,
	.stream_encryption = पूर्णांकel_dp_mst_hdcp_stream_encryption,
	.check_link = पूर्णांकel_dp_hdcp_check_link,
	.hdcp_capable = पूर्णांकel_dp_hdcp_capable,
	.ग_लिखो_2_2_msg = पूर्णांकel_dp_hdcp2_ग_लिखो_msg,
	.पढ़ो_2_2_msg = पूर्णांकel_dp_hdcp2_पढ़ो_msg,
	.config_stream_type = पूर्णांकel_dp_hdcp2_config_stream_type,
	.stream_2_2_encryption = पूर्णांकel_dp_mst_hdcp2_stream_encryption,
	.check_2_2_link = पूर्णांकel_dp_mst_hdcp2_check_link,
	.hdcp_2_2_capable = पूर्णांकel_dp_hdcp2_capable,
	.streams_type1_capable = पूर्णांकel_dp_mst_streams_type1_capable,
	.protocol = HDCP_PROTOCOL_DP,
पूर्ण;

पूर्णांक पूर्णांकel_dp_init_hdcp(काष्ठा पूर्णांकel_digital_port *dig_port,
		       काष्ठा पूर्णांकel_connector *पूर्णांकel_connector)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_connector->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder = &dig_port->base;
	क्रमागत port port = पूर्णांकel_encoder->port;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &dig_port->dp;

	अगर (!is_hdcp_supported(dev_priv, port))
		वापस 0;

	अगर (पूर्णांकel_connector->mst_port)
		वापस पूर्णांकel_hdcp_init(पूर्णांकel_connector, dig_port,
				       &पूर्णांकel_dp_mst_hdcp_shim);
	अन्यथा अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस पूर्णांकel_hdcp_init(पूर्णांकel_connector, dig_port,
				       &पूर्णांकel_dp_hdcp_shim);

	वापस 0;
पूर्ण
