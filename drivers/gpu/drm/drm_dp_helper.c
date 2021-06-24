<शैली गुरु>
/*
 * Copyright तऊ 2009 Keith Packard
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>

#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/drm_dp_mst_helper.h>

#समावेश "drm_crtc_helper_internal.h"

/**
 * DOC: dp helpers
 *
 * These functions contain some common logic and helpers at various असलtraction
 * levels to deal with Display Port sink devices and related things like DP aux
 * channel transfers, EDID पढ़ोing over DP aux channels, decoding certain DPCD
 * blocks, ...
 */

/* Helpers क्रम DP link training */
अटल u8 dp_link_status(स्थिर u8 link_status[DP_LINK_STATUS_SIZE], पूर्णांक r)
अणु
	वापस link_status[r - DP_LANE0_1_STATUS];
पूर्ण

अटल u8 dp_get_lane_status(स्थिर u8 link_status[DP_LINK_STATUS_SIZE],
			     पूर्णांक lane)
अणु
	पूर्णांक i = DP_LANE0_1_STATUS + (lane >> 1);
	पूर्णांक s = (lane & 1) * 4;
	u8 l = dp_link_status(link_status, i);

	वापस (l >> s) & 0xf;
पूर्ण

bool drm_dp_channel_eq_ok(स्थिर u8 link_status[DP_LINK_STATUS_SIZE],
			  पूर्णांक lane_count)
अणु
	u8 lane_align;
	u8 lane_status;
	पूर्णांक lane;

	lane_align = dp_link_status(link_status,
				    DP_LANE_ALIGN_STATUS_UPDATED);
	अगर ((lane_align & DP_INTERLANE_ALIGN_DONE) == 0)
		वापस false;
	क्रम (lane = 0; lane < lane_count; lane++) अणु
		lane_status = dp_get_lane_status(link_status, lane);
		अगर ((lane_status & DP_CHANNEL_EQ_BITS) != DP_CHANNEL_EQ_BITS)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_dp_channel_eq_ok);

bool drm_dp_घड़ी_recovery_ok(स्थिर u8 link_status[DP_LINK_STATUS_SIZE],
			      पूर्णांक lane_count)
अणु
	पूर्णांक lane;
	u8 lane_status;

	क्रम (lane = 0; lane < lane_count; lane++) अणु
		lane_status = dp_get_lane_status(link_status, lane);
		अगर ((lane_status & DP_LANE_CR_DONE) == 0)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_dp_घड़ी_recovery_ok);

u8 drm_dp_get_adjust_request_voltage(स्थिर u8 link_status[DP_LINK_STATUS_SIZE],
				     पूर्णांक lane)
अणु
	पूर्णांक i = DP_ADJUST_REQUEST_LANE0_1 + (lane >> 1);
	पूर्णांक s = ((lane & 1) ?
		 DP_ADJUST_VOLTAGE_SWING_LANE1_SHIFT :
		 DP_ADJUST_VOLTAGE_SWING_LANE0_SHIFT);
	u8 l = dp_link_status(link_status, i);

	वापस ((l >> s) & 0x3) << DP_TRAIN_VOLTAGE_SWING_SHIFT;
पूर्ण
EXPORT_SYMBOL(drm_dp_get_adjust_request_voltage);

u8 drm_dp_get_adjust_request_pre_emphasis(स्थिर u8 link_status[DP_LINK_STATUS_SIZE],
					  पूर्णांक lane)
अणु
	पूर्णांक i = DP_ADJUST_REQUEST_LANE0_1 + (lane >> 1);
	पूर्णांक s = ((lane & 1) ?
		 DP_ADJUST_PRE_EMPHASIS_LANE1_SHIFT :
		 DP_ADJUST_PRE_EMPHASIS_LANE0_SHIFT);
	u8 l = dp_link_status(link_status, i);

	वापस ((l >> s) & 0x3) << DP_TRAIN_PRE_EMPHASIS_SHIFT;
पूर्ण
EXPORT_SYMBOL(drm_dp_get_adjust_request_pre_emphasis);

u8 drm_dp_get_adjust_request_post_cursor(स्थिर u8 link_status[DP_LINK_STATUS_SIZE],
					 अचिन्हित पूर्णांक lane)
अणु
	अचिन्हित पूर्णांक offset = DP_ADJUST_REQUEST_POST_CURSOR2;
	u8 value = dp_link_status(link_status, offset);

	वापस (value >> (lane << 1)) & 0x3;
पूर्ण
EXPORT_SYMBOL(drm_dp_get_adjust_request_post_cursor);

व्योम drm_dp_link_train_घड़ी_recovery_delay(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	अचिन्हित दीर्घ rd_पूर्णांकerval = dpcd[DP_TRAINING_AUX_RD_INTERVAL] &
					 DP_TRAINING_AUX_RD_MASK;

	अगर (rd_पूर्णांकerval > 4)
		DRM_DEBUG_KMS("AUX interval %lu, out of range (max 4)\n",
			      rd_पूर्णांकerval);

	अगर (rd_पूर्णांकerval == 0 || dpcd[DP_DPCD_REV] >= DP_DPCD_REV_14)
		rd_पूर्णांकerval = 100;
	अन्यथा
		rd_पूर्णांकerval *= 4 * USEC_PER_MSEC;

	usleep_range(rd_पूर्णांकerval, rd_पूर्णांकerval * 2);
पूर्ण
EXPORT_SYMBOL(drm_dp_link_train_घड़ी_recovery_delay);

अटल व्योम __drm_dp_link_train_channel_eq_delay(अचिन्हित दीर्घ rd_पूर्णांकerval)
अणु
	अगर (rd_पूर्णांकerval > 4)
		DRM_DEBUG_KMS("AUX interval %lu, out of range (max 4)\n",
			      rd_पूर्णांकerval);

	अगर (rd_पूर्णांकerval == 0)
		rd_पूर्णांकerval = 400;
	अन्यथा
		rd_पूर्णांकerval *= 4 * USEC_PER_MSEC;

	usleep_range(rd_पूर्णांकerval, rd_पूर्णांकerval * 2);
पूर्ण

व्योम drm_dp_link_train_channel_eq_delay(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	__drm_dp_link_train_channel_eq_delay(dpcd[DP_TRAINING_AUX_RD_INTERVAL] &
					     DP_TRAINING_AUX_RD_MASK);
पूर्ण
EXPORT_SYMBOL(drm_dp_link_train_channel_eq_delay);

व्योम drm_dp_lttpr_link_train_घड़ी_recovery_delay(व्योम)
अणु
	usleep_range(100, 200);
पूर्ण
EXPORT_SYMBOL(drm_dp_lttpr_link_train_घड़ी_recovery_delay);

अटल u8 dp_lttpr_phy_cap(स्थिर u8 phy_cap[DP_LTTPR_PHY_CAP_SIZE], पूर्णांक r)
अणु
	वापस phy_cap[r - DP_TRAINING_AUX_RD_INTERVAL_PHY_REPEATER1];
पूर्ण

व्योम drm_dp_lttpr_link_train_channel_eq_delay(स्थिर u8 phy_cap[DP_LTTPR_PHY_CAP_SIZE])
अणु
	u8 पूर्णांकerval = dp_lttpr_phy_cap(phy_cap,
				       DP_TRAINING_AUX_RD_INTERVAL_PHY_REPEATER1) &
		      DP_TRAINING_AUX_RD_MASK;

	__drm_dp_link_train_channel_eq_delay(पूर्णांकerval);
पूर्ण
EXPORT_SYMBOL(drm_dp_lttpr_link_train_channel_eq_delay);

u8 drm_dp_link_rate_to_bw_code(पूर्णांक link_rate)
अणु
	/* Spec says link_bw = link_rate / 0.27Gbps */
	वापस link_rate / 27000;
पूर्ण
EXPORT_SYMBOL(drm_dp_link_rate_to_bw_code);

पूर्णांक drm_dp_bw_code_to_link_rate(u8 link_bw)
अणु
	/* Spec says link_rate = link_bw * 0.27Gbps */
	वापस link_bw * 27000;
पूर्ण
EXPORT_SYMBOL(drm_dp_bw_code_to_link_rate);

#घोषणा AUX_RETRY_INTERVAL 500 /* us */

अटल अंतरभूत व्योम
drm_dp_dump_access(स्थिर काष्ठा drm_dp_aux *aux,
		   u8 request, uपूर्णांक offset, व्योम *buffer, पूर्णांक ret)
अणु
	स्थिर अक्षर *arrow = request == DP_AUX_NATIVE_READ ? "->" : "<-";

	अगर (ret > 0)
		DRM_DEBUG_DP("%s: 0x%05x AUX %s (ret=%3d) %*ph\n",
			     aux->name, offset, arrow, ret, min(ret, 20), buffer);
	अन्यथा
		DRM_DEBUG_DP("%s: 0x%05x AUX %s (ret=%3d)\n",
			     aux->name, offset, arrow, ret);
पूर्ण

/**
 * DOC: dp helpers
 *
 * The DisplayPort AUX channel is an असलtraction to allow generic, driver-
 * independent access to AUX functionality. Drivers can take advantage of
 * this by filling in the fields of the drm_dp_aux काष्ठाure.
 *
 * Transactions are described using a hardware-independent drm_dp_aux_msg
 * काष्ठाure, which is passed पूर्णांकo a driver's .transfer() implementation.
 * Both native and I2C-over-AUX transactions are supported.
 */

अटल पूर्णांक drm_dp_dpcd_access(काष्ठा drm_dp_aux *aux, u8 request,
			      अचिन्हित पूर्णांक offset, व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा drm_dp_aux_msg msg;
	अचिन्हित पूर्णांक retry, native_reply;
	पूर्णांक err = 0, ret = 0;

	स_रखो(&msg, 0, माप(msg));
	msg.address = offset;
	msg.request = request;
	msg.buffer = buffer;
	msg.size = size;

	mutex_lock(&aux->hw_mutex);

	/*
	 * The specअगरication करोesn't give any recommendation on how often to
	 * retry native transactions. We used to retry 7 बार like क्रम
	 * aux i2c transactions but real world devices this wasn't
	 * sufficient, bump to 32 which makes Dell 4k monitors happier.
	 */
	क्रम (retry = 0; retry < 32; retry++) अणु
		अगर (ret != 0 && ret != -ETIMEDOUT) अणु
			usleep_range(AUX_RETRY_INTERVAL,
				     AUX_RETRY_INTERVAL + 100);
		पूर्ण

		ret = aux->transfer(aux, &msg);
		अगर (ret >= 0) अणु
			native_reply = msg.reply & DP_AUX_NATIVE_REPLY_MASK;
			अगर (native_reply == DP_AUX_NATIVE_REPLY_ACK) अणु
				अगर (ret == size)
					जाओ unlock;

				ret = -EPROTO;
			पूर्ण अन्यथा
				ret = -EIO;
		पूर्ण

		/*
		 * We want the error we वापस to be the error we received on
		 * the first transaction, since we may get a dअगरferent error the
		 * next समय we retry
		 */
		अगर (!err)
			err = ret;
	पूर्ण

	DRM_DEBUG_KMS("%s: Too many retries, giving up. First error: %d\n",
		      aux->name, err);
	ret = err;

unlock:
	mutex_unlock(&aux->hw_mutex);
	वापस ret;
पूर्ण

/**
 * drm_dp_dpcd_पढ़ो() - पढ़ो a series of bytes from the DPCD
 * @aux: DisplayPort AUX channel (SST or MST)
 * @offset: address of the (first) रेजिस्टर to पढ़ो
 * @buffer: buffer to store the रेजिस्टर values
 * @size: number of bytes in @buffer
 *
 * Returns the number of bytes transferred on success, or a negative error
 * code on failure. -EIO is वापसed अगर the request was NAKed by the sink or
 * अगर the retry count was exceeded. If not all bytes were transferred, this
 * function वापसs -EPROTO. Errors from the underlying AUX channel transfer
 * function, with the exception of -EBUSY (which causes the transaction to
 * be retried), are propagated to the caller.
 */
sमाप_प्रकार drm_dp_dpcd_पढ़ो(काष्ठा drm_dp_aux *aux, अचिन्हित पूर्णांक offset,
			 व्योम *buffer, माप_प्रकार size)
अणु
	पूर्णांक ret;

	/*
	 * HP ZR24w corrupts the first DPCD access after entering घातer save
	 * mode. Eg. on a पढ़ो, the entire buffer will be filled with the same
	 * byte. Do a throw away पढ़ो to aव्योम corrupting anything we care
	 * about. Afterwards things will work correctly until the monitor
	 * माला_लो woken up and subsequently re-enters घातer save mode.
	 *
	 * The user pressing any button on the monitor is enough to wake it
	 * up, so there is no particularly good place to करो the workaround.
	 * We just have to करो it beक्रमe any DPCD access and hope that the
	 * monitor करोesn't घातer करोwn exactly after the throw away पढ़ो.
	 */
	अगर (!aux->is_remote) अणु
		ret = drm_dp_dpcd_access(aux, DP_AUX_NATIVE_READ, DP_DPCD_REV,
					 buffer, 1);
		अगर (ret != 1)
			जाओ out;
	पूर्ण

	अगर (aux->is_remote)
		ret = drm_dp_mst_dpcd_पढ़ो(aux, offset, buffer, size);
	अन्यथा
		ret = drm_dp_dpcd_access(aux, DP_AUX_NATIVE_READ, offset,
					 buffer, size);

out:
	drm_dp_dump_access(aux, DP_AUX_NATIVE_READ, offset, buffer, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_dp_dpcd_पढ़ो);

/**
 * drm_dp_dpcd_ग_लिखो() - ग_लिखो a series of bytes to the DPCD
 * @aux: DisplayPort AUX channel (SST or MST)
 * @offset: address of the (first) रेजिस्टर to ग_लिखो
 * @buffer: buffer containing the values to ग_लिखो
 * @size: number of bytes in @buffer
 *
 * Returns the number of bytes transferred on success, or a negative error
 * code on failure. -EIO is वापसed अगर the request was NAKed by the sink or
 * अगर the retry count was exceeded. If not all bytes were transferred, this
 * function वापसs -EPROTO. Errors from the underlying AUX channel transfer
 * function, with the exception of -EBUSY (which causes the transaction to
 * be retried), are propagated to the caller.
 */
sमाप_प्रकार drm_dp_dpcd_ग_लिखो(काष्ठा drm_dp_aux *aux, अचिन्हित पूर्णांक offset,
			  व्योम *buffer, माप_प्रकार size)
अणु
	पूर्णांक ret;

	अगर (aux->is_remote)
		ret = drm_dp_mst_dpcd_ग_लिखो(aux, offset, buffer, size);
	अन्यथा
		ret = drm_dp_dpcd_access(aux, DP_AUX_NATIVE_WRITE, offset,
					 buffer, size);

	drm_dp_dump_access(aux, DP_AUX_NATIVE_WRITE, offset, buffer, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_dp_dpcd_ग_लिखो);

/**
 * drm_dp_dpcd_पढ़ो_link_status() - पढ़ो DPCD link status (bytes 0x202-0x207)
 * @aux: DisplayPort AUX channel
 * @status: buffer to store the link status in (must be at least 6 bytes)
 *
 * Returns the number of bytes transferred on success or a negative error
 * code on failure.
 */
पूर्णांक drm_dp_dpcd_पढ़ो_link_status(काष्ठा drm_dp_aux *aux,
				 u8 status[DP_LINK_STATUS_SIZE])
अणु
	वापस drm_dp_dpcd_पढ़ो(aux, DP_LANE0_1_STATUS, status,
				DP_LINK_STATUS_SIZE);
पूर्ण
EXPORT_SYMBOL(drm_dp_dpcd_पढ़ो_link_status);

/**
 * drm_dp_dpcd_पढ़ो_phy_link_status - get the link status inक्रमmation क्रम a DP PHY
 * @aux: DisplayPort AUX channel
 * @dp_phy: the DP PHY to get the link status क्रम
 * @link_status: buffer to वापस the status in
 *
 * Fetch the AUX DPCD रेजिस्टरs क्रम the DPRX or an LTTPR PHY link status. The
 * layout of the वापसed @link_status matches the DPCD रेजिस्टर layout of the
 * DPRX PHY link status.
 *
 * Returns 0 अगर the inक्रमmation was पढ़ो successfully or a negative error code
 * on failure.
 */
पूर्णांक drm_dp_dpcd_पढ़ो_phy_link_status(काष्ठा drm_dp_aux *aux,
				     क्रमागत drm_dp_phy dp_phy,
				     u8 link_status[DP_LINK_STATUS_SIZE])
अणु
	पूर्णांक ret;

	अगर (dp_phy == DP_PHY_DPRX) अणु
		ret = drm_dp_dpcd_पढ़ो(aux,
				       DP_LANE0_1_STATUS,
				       link_status,
				       DP_LINK_STATUS_SIZE);

		अगर (ret < 0)
			वापस ret;

		WARN_ON(ret != DP_LINK_STATUS_SIZE);

		वापस 0;
	पूर्ण

	ret = drm_dp_dpcd_पढ़ो(aux,
			       DP_LANE0_1_STATUS_PHY_REPEATER(dp_phy),
			       link_status,
			       DP_LINK_STATUS_SIZE - 1);

	अगर (ret < 0)
		वापस ret;

	WARN_ON(ret != DP_LINK_STATUS_SIZE - 1);

	/* Convert the LTTPR to the sink PHY link status layout */
	स_हटाओ(&link_status[DP_SINK_STATUS - DP_LANE0_1_STATUS + 1],
		&link_status[DP_SINK_STATUS - DP_LANE0_1_STATUS],
		DP_LINK_STATUS_SIZE - (DP_SINK_STATUS - DP_LANE0_1_STATUS) - 1);
	link_status[DP_SINK_STATUS - DP_LANE0_1_STATUS] = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_dpcd_पढ़ो_phy_link_status);

अटल bool is_edid_digital_input_dp(स्थिर काष्ठा edid *edid)
अणु
	वापस edid && edid->revision >= 4 &&
		edid->input & DRM_EDID_INPUT_DIGITAL &&
		(edid->input & DRM_EDID_DIGITAL_TYPE_MASK) == DRM_EDID_DIGITAL_TYPE_DP;
पूर्ण

/**
 * drm_dp_करोwnstream_is_type() - is the करोwnstream facing port of certain type?
 * @dpcd: DisplayPort configuration data
 * @port_cap: port capabilities
 * @type: port type to be checked. Can be:
 * 	  %DP_DS_PORT_TYPE_DP, %DP_DS_PORT_TYPE_VGA, %DP_DS_PORT_TYPE_DVI,
 * 	  %DP_DS_PORT_TYPE_HDMI, %DP_DS_PORT_TYPE_NON_EDID,
 *	  %DP_DS_PORT_TYPE_DP_DUALMODE or %DP_DS_PORT_TYPE_WIRELESS.
 *
 * Caveat: Only works with DPCD 1.1+ port caps.
 *
 * Returns: whether the करोwnstream facing port matches the type.
 */
bool drm_dp_करोwnstream_is_type(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
			       स्थिर u8 port_cap[4], u8 type)
अणु
	वापस drm_dp_is_branch(dpcd) &&
		dpcd[DP_DPCD_REV] >= 0x11 &&
		(port_cap[0] & DP_DS_PORT_TYPE_MASK) == type;
पूर्ण
EXPORT_SYMBOL(drm_dp_करोwnstream_is_type);

/**
 * drm_dp_करोwnstream_is_पंचांगds() - is the करोwnstream facing port TMDS?
 * @dpcd: DisplayPort configuration data
 * @port_cap: port capabilities
 * @edid: EDID
 *
 * Returns: whether the करोwnstream facing port is TMDS (HDMI/DVI).
 */
bool drm_dp_करोwnstream_is_पंचांगds(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
			       स्थिर u8 port_cap[4],
			       स्थिर काष्ठा edid *edid)
अणु
	अगर (dpcd[DP_DPCD_REV] < 0x11) अणु
		चयन (dpcd[DP_DOWNSTREAMPORT_PRESENT] & DP_DWN_STRM_PORT_TYPE_MASK) अणु
		हाल DP_DWN_STRM_PORT_TYPE_TMDS:
			वापस true;
		शेष:
			वापस false;
		पूर्ण
	पूर्ण

	चयन (port_cap[0] & DP_DS_PORT_TYPE_MASK) अणु
	हाल DP_DS_PORT_TYPE_DP_DUALMODE:
		अगर (is_edid_digital_input_dp(edid))
			वापस false;
		fallthrough;
	हाल DP_DS_PORT_TYPE_DVI:
	हाल DP_DS_PORT_TYPE_HDMI:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_dp_करोwnstream_is_पंचांगds);

/**
 * drm_dp_send_real_edid_checksum() - send back real edid checksum value
 * @aux: DisplayPort AUX channel
 * @real_edid_checksum: real edid checksum क्रम the last block
 *
 * Returns:
 * True on success
 */
bool drm_dp_send_real_edid_checksum(काष्ठा drm_dp_aux *aux,
				    u8 real_edid_checksum)
अणु
	u8 link_edid_पढ़ो = 0, स्वतः_test_req = 0, test_resp = 0;

	अगर (drm_dp_dpcd_पढ़ो(aux, DP_DEVICE_SERVICE_IRQ_VECTOR,
			     &स्वतः_test_req, 1) < 1) अणु
		DRM_ERROR("%s: DPCD failed read at register 0x%x\n",
			  aux->name, DP_DEVICE_SERVICE_IRQ_VECTOR);
		वापस false;
	पूर्ण
	स्वतः_test_req &= DP_AUTOMATED_TEST_REQUEST;

	अगर (drm_dp_dpcd_पढ़ो(aux, DP_TEST_REQUEST, &link_edid_पढ़ो, 1) < 1) अणु
		DRM_ERROR("%s: DPCD failed read at register 0x%x\n",
			  aux->name, DP_TEST_REQUEST);
		वापस false;
	पूर्ण
	link_edid_पढ़ो &= DP_TEST_LINK_EDID_READ;

	अगर (!स्वतः_test_req || !link_edid_पढ़ो) अणु
		DRM_DEBUG_KMS("%s: Source DUT does not support TEST_EDID_READ\n",
			      aux->name);
		वापस false;
	पूर्ण

	अगर (drm_dp_dpcd_ग_लिखो(aux, DP_DEVICE_SERVICE_IRQ_VECTOR,
			      &स्वतः_test_req, 1) < 1) अणु
		DRM_ERROR("%s: DPCD failed write at register 0x%x\n",
			  aux->name, DP_DEVICE_SERVICE_IRQ_VECTOR);
		वापस false;
	पूर्ण

	/* send back checksum क्रम the last edid extension block data */
	अगर (drm_dp_dpcd_ग_लिखो(aux, DP_TEST_EDID_CHECKSUM,
			      &real_edid_checksum, 1) < 1) अणु
		DRM_ERROR("%s: DPCD failed write at register 0x%x\n",
			  aux->name, DP_TEST_EDID_CHECKSUM);
		वापस false;
	पूर्ण

	test_resp |= DP_TEST_EDID_CHECKSUM_WRITE;
	अगर (drm_dp_dpcd_ग_लिखो(aux, DP_TEST_RESPONSE, &test_resp, 1) < 1) अणु
		DRM_ERROR("%s: DPCD failed write at register 0x%x\n",
			  aux->name, DP_TEST_RESPONSE);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_dp_send_real_edid_checksum);

अटल u8 drm_dp_करोwnstream_port_count(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	u8 port_count = dpcd[DP_DOWN_STREAM_PORT_COUNT] & DP_PORT_COUNT_MASK;

	अगर (dpcd[DP_DOWNSTREAMPORT_PRESENT] & DP_DETAILED_CAP_INFO_AVAILABLE && port_count > 4)
		port_count = 4;

	वापस port_count;
पूर्ण

अटल पूर्णांक drm_dp_पढ़ो_extended_dpcd_caps(काष्ठा drm_dp_aux *aux,
					  u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	u8 dpcd_ext[6];
	पूर्णांक ret;

	/*
	 * Prior to DP1.3 the bit represented by
	 * DP_EXTENDED_RECEIVER_CAP_FIELD_PRESENT was reserved.
	 * If it is set DP_DPCD_REV at 0000h could be at a value less than
	 * the true capability of the panel. The only way to check is to
	 * then compare 0000h and 2200h.
	 */
	अगर (!(dpcd[DP_TRAINING_AUX_RD_INTERVAL] &
	      DP_EXTENDED_RECEIVER_CAP_FIELD_PRESENT))
		वापस 0;

	ret = drm_dp_dpcd_पढ़ो(aux, DP_DP13_DPCD_REV, &dpcd_ext,
			       माप(dpcd_ext));
	अगर (ret < 0)
		वापस ret;
	अगर (ret != माप(dpcd_ext))
		वापस -EIO;

	अगर (dpcd[DP_DPCD_REV] > dpcd_ext[DP_DPCD_REV]) अणु
		DRM_DEBUG_KMS("%s: Extended DPCD rev less than base DPCD rev (%d > %d)\n",
			      aux->name, dpcd[DP_DPCD_REV],
			      dpcd_ext[DP_DPCD_REV]);
		वापस 0;
	पूर्ण

	अगर (!स_भेद(dpcd, dpcd_ext, माप(dpcd_ext)))
		वापस 0;

	DRM_DEBUG_KMS("%s: Base DPCD: %*ph\n",
		      aux->name, DP_RECEIVER_CAP_SIZE, dpcd);

	स_नकल(dpcd, dpcd_ext, माप(dpcd_ext));

	वापस 0;
पूर्ण

/**
 * drm_dp_पढ़ो_dpcd_caps() - पढ़ो DPCD caps and extended DPCD caps अगर
 * available
 * @aux: DisplayPort AUX channel
 * @dpcd: Buffer to store the resulting DPCD in
 *
 * Attempts to पढ़ो the base DPCD caps क्रम @aux. Additionally, this function
 * checks क्रम and पढ़ोs the extended DPRX caps (%DP_DP13_DPCD_REV) अगर
 * present.
 *
 * Returns: %0 अगर the DPCD was पढ़ो successfully, negative error code
 * otherwise.
 */
पूर्णांक drm_dp_पढ़ो_dpcd_caps(काष्ठा drm_dp_aux *aux,
			  u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ो(aux, DP_DPCD_REV, dpcd, DP_RECEIVER_CAP_SIZE);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != DP_RECEIVER_CAP_SIZE || dpcd[DP_DPCD_REV] == 0)
		वापस -EIO;

	ret = drm_dp_पढ़ो_extended_dpcd_caps(aux, dpcd);
	अगर (ret < 0)
		वापस ret;

	DRM_DEBUG_KMS("%s: DPCD: %*ph\n",
		      aux->name, DP_RECEIVER_CAP_SIZE, dpcd);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_dp_पढ़ो_dpcd_caps);

/**
 * drm_dp_पढ़ो_करोwnstream_info() - पढ़ो DPCD करोwnstream port info अगर available
 * @aux: DisplayPort AUX channel
 * @dpcd: A cached copy of the port's DPCD
 * @करोwnstream_ports: buffer to store the करोwnstream port info in
 *
 * See also:
 * drm_dp_करोwnstream_max_घड़ी()
 * drm_dp_करोwnstream_max_bpc()
 *
 * Returns: 0 अगर either the करोwnstream port info was पढ़ो successfully or
 * there was no करोwnstream info to पढ़ो, or a negative error code otherwise.
 */
पूर्णांक drm_dp_पढ़ो_करोwnstream_info(काष्ठा drm_dp_aux *aux,
				स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
				u8 करोwnstream_ports[DP_MAX_DOWNSTREAM_PORTS])
अणु
	पूर्णांक ret;
	u8 len;

	स_रखो(करोwnstream_ports, 0, DP_MAX_DOWNSTREAM_PORTS);

	/* No करोwnstream info to पढ़ो */
	अगर (!drm_dp_is_branch(dpcd) ||
	    dpcd[DP_DPCD_REV] < DP_DPCD_REV_10 ||
	    !(dpcd[DP_DOWNSTREAMPORT_PRESENT] & DP_DWN_STRM_PORT_PRESENT))
		वापस 0;

	len = drm_dp_करोwnstream_port_count(dpcd);
	अगर (dpcd[DP_DOWNSTREAMPORT_PRESENT] & DP_DETAILED_CAP_INFO_AVAILABLE)
		len *= 4;

	ret = drm_dp_dpcd_पढ़ो(aux, DP_DOWNSTREAM_PORT_0, करोwnstream_ports, len);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != len)
		वापस -EIO;

	DRM_DEBUG_KMS("%s: DPCD DFP: %*ph\n",
		      aux->name, len, करोwnstream_ports);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_पढ़ो_करोwnstream_info);

/**
 * drm_dp_करोwnstream_max_करोtघड़ी() - extract करोwnstream facing port max करोt घड़ी
 * @dpcd: DisplayPort configuration data
 * @port_cap: port capabilities
 *
 * Returns: Downstream facing port max करोt घड़ी in kHz on success,
 * or 0 अगर max घड़ी not defined
 */
पूर्णांक drm_dp_करोwnstream_max_करोtघड़ी(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
				   स्थिर u8 port_cap[4])
अणु
	अगर (!drm_dp_is_branch(dpcd))
		वापस 0;

	अगर (dpcd[DP_DPCD_REV] < 0x11)
		वापस 0;

	चयन (port_cap[0] & DP_DS_PORT_TYPE_MASK) अणु
	हाल DP_DS_PORT_TYPE_VGA:
		अगर ((dpcd[DP_DOWNSTREAMPORT_PRESENT] & DP_DETAILED_CAP_INFO_AVAILABLE) == 0)
			वापस 0;
		वापस port_cap[1] * 8000;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_dp_करोwnstream_max_करोtघड़ी);

/**
 * drm_dp_करोwnstream_max_पंचांगds_घड़ी() - extract करोwnstream facing port max TMDS घड़ी
 * @dpcd: DisplayPort configuration data
 * @port_cap: port capabilities
 * @edid: EDID
 *
 * Returns: HDMI/DVI करोwnstream facing port max TMDS घड़ी in kHz on success,
 * or 0 अगर max TMDS घड़ी not defined
 */
पूर्णांक drm_dp_करोwnstream_max_पंचांगds_घड़ी(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
				     स्थिर u8 port_cap[4],
				     स्थिर काष्ठा edid *edid)
अणु
	अगर (!drm_dp_is_branch(dpcd))
		वापस 0;

	अगर (dpcd[DP_DPCD_REV] < 0x11) अणु
		चयन (dpcd[DP_DOWNSTREAMPORT_PRESENT] & DP_DWN_STRM_PORT_TYPE_MASK) अणु
		हाल DP_DWN_STRM_PORT_TYPE_TMDS:
			वापस 165000;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	चयन (port_cap[0] & DP_DS_PORT_TYPE_MASK) अणु
	हाल DP_DS_PORT_TYPE_DP_DUALMODE:
		अगर (is_edid_digital_input_dp(edid))
			वापस 0;
		/*
		 * It's left up to the driver to check the
		 * DP dual mode adapter's max TMDS घड़ी.
		 *
		 * Unक्रमtunatley it looks like branch devices
		 * may not क्रमdward that the DP dual mode i2c
		 * access so we just usually get i2c nak :(
		 */
		fallthrough;
	हाल DP_DS_PORT_TYPE_HDMI:
		 /*
		  * We should perhaps assume 165 MHz when detailed cap
		  * info is not available. But looks like many typical
		  * branch devices fall पूर्णांकo that category and so we'd
		  * probably end up with users complaining that they can't
		  * get high resolution modes with their favorite करोngle.
		  *
		  * So let's limit to 300 MHz instead since DPCD 1.4
		  * HDMI 2.0 DFPs are required to have the detailed cap
		  * info. So it's more likely we're dealing with a HDMI 1.4
		  * compatible* device here.
		  */
		अगर ((dpcd[DP_DOWNSTREAMPORT_PRESENT] & DP_DETAILED_CAP_INFO_AVAILABLE) == 0)
			वापस 300000;
		वापस port_cap[1] * 2500;
	हाल DP_DS_PORT_TYPE_DVI:
		अगर ((dpcd[DP_DOWNSTREAMPORT_PRESENT] & DP_DETAILED_CAP_INFO_AVAILABLE) == 0)
			वापस 165000;
		/* FIXME what to करो about DVI dual link? */
		वापस port_cap[1] * 2500;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_dp_करोwnstream_max_पंचांगds_घड़ी);

/**
 * drm_dp_करोwnstream_min_पंचांगds_घड़ी() - extract करोwnstream facing port min TMDS घड़ी
 * @dpcd: DisplayPort configuration data
 * @port_cap: port capabilities
 * @edid: EDID
 *
 * Returns: HDMI/DVI करोwnstream facing port min TMDS घड़ी in kHz on success,
 * or 0 अगर max TMDS घड़ी not defined
 */
पूर्णांक drm_dp_करोwnstream_min_पंचांगds_घड़ी(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
				     स्थिर u8 port_cap[4],
				     स्थिर काष्ठा edid *edid)
अणु
	अगर (!drm_dp_is_branch(dpcd))
		वापस 0;

	अगर (dpcd[DP_DPCD_REV] < 0x11) अणु
		चयन (dpcd[DP_DOWNSTREAMPORT_PRESENT] & DP_DWN_STRM_PORT_TYPE_MASK) अणु
		हाल DP_DWN_STRM_PORT_TYPE_TMDS:
			वापस 25000;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	चयन (port_cap[0] & DP_DS_PORT_TYPE_MASK) अणु
	हाल DP_DS_PORT_TYPE_DP_DUALMODE:
		अगर (is_edid_digital_input_dp(edid))
			वापस 0;
		fallthrough;
	हाल DP_DS_PORT_TYPE_DVI:
	हाल DP_DS_PORT_TYPE_HDMI:
		/*
		 * Unclear whether the protocol converter could
		 * utilize pixel replication. Assume it won't.
		 */
		वापस 25000;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_dp_करोwnstream_min_पंचांगds_घड़ी);

/**
 * drm_dp_करोwnstream_max_bpc() - extract करोwnstream facing port max
 *                               bits per component
 * @dpcd: DisplayPort configuration data
 * @port_cap: करोwnstream facing port capabilities
 * @edid: EDID
 *
 * Returns: Max bpc on success or 0 अगर max bpc not defined
 */
पूर्णांक drm_dp_करोwnstream_max_bpc(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
			      स्थिर u8 port_cap[4],
			      स्थिर काष्ठा edid *edid)
अणु
	अगर (!drm_dp_is_branch(dpcd))
		वापस 0;

	अगर (dpcd[DP_DPCD_REV] < 0x11) अणु
		चयन (dpcd[DP_DOWNSTREAMPORT_PRESENT] & DP_DWN_STRM_PORT_TYPE_MASK) अणु
		हाल DP_DWN_STRM_PORT_TYPE_DP:
			वापस 0;
		शेष:
			वापस 8;
		पूर्ण
	पूर्ण

	चयन (port_cap[0] & DP_DS_PORT_TYPE_MASK) अणु
	हाल DP_DS_PORT_TYPE_DP:
		वापस 0;
	हाल DP_DS_PORT_TYPE_DP_DUALMODE:
		अगर (is_edid_digital_input_dp(edid))
			वापस 0;
		fallthrough;
	हाल DP_DS_PORT_TYPE_HDMI:
	हाल DP_DS_PORT_TYPE_DVI:
	हाल DP_DS_PORT_TYPE_VGA:
		अगर ((dpcd[DP_DOWNSTREAMPORT_PRESENT] & DP_DETAILED_CAP_INFO_AVAILABLE) == 0)
			वापस 8;

		चयन (port_cap[2] & DP_DS_MAX_BPC_MASK) अणु
		हाल DP_DS_8BPC:
			वापस 8;
		हाल DP_DS_10BPC:
			वापस 10;
		हाल DP_DS_12BPC:
			वापस 12;
		हाल DP_DS_16BPC:
			वापस 16;
		शेष:
			वापस 8;
		पूर्ण
		अवरोध;
	शेष:
		वापस 8;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_dp_करोwnstream_max_bpc);

/**
 * drm_dp_करोwnstream_420_passthrough() - determine करोwnstream facing port
 *                                       YCbCr 4:2:0 pass-through capability
 * @dpcd: DisplayPort configuration data
 * @port_cap: करोwnstream facing port capabilities
 *
 * Returns: whether the करोwnstream facing port can pass through YCbCr 4:2:0
 */
bool drm_dp_करोwnstream_420_passthrough(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
				       स्थिर u8 port_cap[4])
अणु
	अगर (!drm_dp_is_branch(dpcd))
		वापस false;

	अगर (dpcd[DP_DPCD_REV] < 0x13)
		वापस false;

	चयन (port_cap[0] & DP_DS_PORT_TYPE_MASK) अणु
	हाल DP_DS_PORT_TYPE_DP:
		वापस true;
	हाल DP_DS_PORT_TYPE_HDMI:
		अगर ((dpcd[DP_DOWNSTREAMPORT_PRESENT] & DP_DETAILED_CAP_INFO_AVAILABLE) == 0)
			वापस false;

		वापस port_cap[3] & DP_DS_HDMI_YCBCR420_PASS_THROUGH;
	शेष:
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_dp_करोwnstream_420_passthrough);

/**
 * drm_dp_करोwnstream_444_to_420_conversion() - determine करोwnstream facing port
 *                                             YCbCr 4:4:4->4:2:0 conversion capability
 * @dpcd: DisplayPort configuration data
 * @port_cap: करोwnstream facing port capabilities
 *
 * Returns: whether the करोwnstream facing port can convert YCbCr 4:4:4 to 4:2:0
 */
bool drm_dp_करोwnstream_444_to_420_conversion(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
					     स्थिर u8 port_cap[4])
अणु
	अगर (!drm_dp_is_branch(dpcd))
		वापस false;

	अगर (dpcd[DP_DPCD_REV] < 0x13)
		वापस false;

	चयन (port_cap[0] & DP_DS_PORT_TYPE_MASK) अणु
	हाल DP_DS_PORT_TYPE_HDMI:
		अगर ((dpcd[DP_DOWNSTREAMPORT_PRESENT] & DP_DETAILED_CAP_INFO_AVAILABLE) == 0)
			वापस false;

		वापस port_cap[3] & DP_DS_HDMI_YCBCR444_TO_420_CONV;
	शेष:
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_dp_करोwnstream_444_to_420_conversion);

/**
 * drm_dp_करोwnstream_rgb_to_ycbcr_conversion() - determine करोwnstream facing port
 *                                               RGB->YCbCr conversion capability
 * @dpcd: DisplayPort configuration data
 * @port_cap: करोwnstream facing port capabilities
 * @color_spc: Colorspace क्रम which conversion cap is sought
 *
 * Returns: whether the करोwnstream facing port can convert RGB->YCbCr क्रम a given
 * colorspace.
 */
bool drm_dp_करोwnstream_rgb_to_ycbcr_conversion(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
					       स्थिर u8 port_cap[4],
					       u8 color_spc)
अणु
	अगर (!drm_dp_is_branch(dpcd))
		वापस false;

	अगर (dpcd[DP_DPCD_REV] < 0x13)
		वापस false;

	चयन (port_cap[0] & DP_DS_PORT_TYPE_MASK) अणु
	हाल DP_DS_PORT_TYPE_HDMI:
		अगर ((dpcd[DP_DOWNSTREAMPORT_PRESENT] & DP_DETAILED_CAP_INFO_AVAILABLE) == 0)
			वापस false;

		वापस port_cap[3] & color_spc;
	शेष:
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_dp_करोwnstream_rgb_to_ycbcr_conversion);

/**
 * drm_dp_करोwnstream_mode() - वापस a mode क्रम करोwnstream facing port
 * @dev: DRM device
 * @dpcd: DisplayPort configuration data
 * @port_cap: port capabilities
 *
 * Provides a suitable mode क्रम करोwnstream facing ports without EDID.
 *
 * Returns: A new drm_display_mode on success or शून्य on failure
 */
काष्ठा drm_display_mode *
drm_dp_करोwnstream_mode(काष्ठा drm_device *dev,
		       स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
		       स्थिर u8 port_cap[4])

अणु
	u8 vic;

	अगर (!drm_dp_is_branch(dpcd))
		वापस शून्य;

	अगर (dpcd[DP_DPCD_REV] < 0x11)
		वापस शून्य;

	चयन (port_cap[0] & DP_DS_PORT_TYPE_MASK) अणु
	हाल DP_DS_PORT_TYPE_NON_EDID:
		चयन (port_cap[0] & DP_DS_NON_EDID_MASK) अणु
		हाल DP_DS_NON_EDID_720x480i_60:
			vic = 6;
			अवरोध;
		हाल DP_DS_NON_EDID_720x480i_50:
			vic = 21;
			अवरोध;
		हाल DP_DS_NON_EDID_1920x1080i_60:
			vic = 5;
			अवरोध;
		हाल DP_DS_NON_EDID_1920x1080i_50:
			vic = 20;
			अवरोध;
		हाल DP_DS_NON_EDID_1280x720_60:
			vic = 4;
			अवरोध;
		हाल DP_DS_NON_EDID_1280x720_50:
			vic = 19;
			अवरोध;
		शेष:
			वापस शून्य;
		पूर्ण
		वापस drm_display_mode_from_cea_vic(dev, vic);
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_dp_करोwnstream_mode);

/**
 * drm_dp_करोwnstream_id() - identअगरy branch device
 * @aux: DisplayPort AUX channel
 * @id: DisplayPort branch device id
 *
 * Returns branch device id on success or शून्य on failure
 */
पूर्णांक drm_dp_करोwnstream_id(काष्ठा drm_dp_aux *aux, अक्षर id[6])
अणु
	वापस drm_dp_dpcd_पढ़ो(aux, DP_BRANCH_ID, id, 6);
पूर्ण
EXPORT_SYMBOL(drm_dp_करोwnstream_id);

/**
 * drm_dp_करोwnstream_debug() - debug DP branch devices
 * @m: poपूर्णांकer क्रम debugfs file
 * @dpcd: DisplayPort configuration data
 * @port_cap: port capabilities
 * @edid: EDID
 * @aux: DisplayPort AUX channel
 *
 */
व्योम drm_dp_करोwnstream_debug(काष्ठा seq_file *m,
			     स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
			     स्थिर u8 port_cap[4],
			     स्थिर काष्ठा edid *edid,
			     काष्ठा drm_dp_aux *aux)
अणु
	bool detailed_cap_info = dpcd[DP_DOWNSTREAMPORT_PRESENT] &
				 DP_DETAILED_CAP_INFO_AVAILABLE;
	पूर्णांक clk;
	पूर्णांक bpc;
	अक्षर id[7];
	पूर्णांक len;
	uपूर्णांक8_t rev[2];
	पूर्णांक type = port_cap[0] & DP_DS_PORT_TYPE_MASK;
	bool branch_device = drm_dp_is_branch(dpcd);

	seq_म_लिखो(m, "\tDP branch device present: %s\n",
		   branch_device ? "yes" : "no");

	अगर (!branch_device)
		वापस;

	चयन (type) अणु
	हाल DP_DS_PORT_TYPE_DP:
		seq_माला_दो(m, "\t\tType: DisplayPort\n");
		अवरोध;
	हाल DP_DS_PORT_TYPE_VGA:
		seq_माला_दो(m, "\t\tType: VGA\n");
		अवरोध;
	हाल DP_DS_PORT_TYPE_DVI:
		seq_माला_दो(m, "\t\tType: DVI\n");
		अवरोध;
	हाल DP_DS_PORT_TYPE_HDMI:
		seq_माला_दो(m, "\t\tType: HDMI\n");
		अवरोध;
	हाल DP_DS_PORT_TYPE_NON_EDID:
		seq_माला_दो(m, "\t\tType: others without EDID support\n");
		अवरोध;
	हाल DP_DS_PORT_TYPE_DP_DUALMODE:
		seq_माला_दो(m, "\t\tType: DP++\n");
		अवरोध;
	हाल DP_DS_PORT_TYPE_WIRELESS:
		seq_माला_दो(m, "\t\tType: Wireless\n");
		अवरोध;
	शेष:
		seq_माला_दो(m, "\t\tType: N/A\n");
	पूर्ण

	स_रखो(id, 0, माप(id));
	drm_dp_करोwnstream_id(aux, id);
	seq_म_लिखो(m, "\t\tID: %s\n", id);

	len = drm_dp_dpcd_पढ़ो(aux, DP_BRANCH_HW_REV, &rev[0], 1);
	अगर (len > 0)
		seq_म_लिखो(m, "\t\tHW: %d.%d\n",
			   (rev[0] & 0xf0) >> 4, rev[0] & 0xf);

	len = drm_dp_dpcd_पढ़ो(aux, DP_BRANCH_SW_REV, rev, 2);
	अगर (len > 0)
		seq_म_लिखो(m, "\t\tSW: %d.%d\n", rev[0], rev[1]);

	अगर (detailed_cap_info) अणु
		clk = drm_dp_करोwnstream_max_करोtघड़ी(dpcd, port_cap);
		अगर (clk > 0)
			seq_म_लिखो(m, "\t\tMax dot clock: %d kHz\n", clk);

		clk = drm_dp_करोwnstream_max_पंचांगds_घड़ी(dpcd, port_cap, edid);
		अगर (clk > 0)
			seq_म_लिखो(m, "\t\tMax TMDS clock: %d kHz\n", clk);

		clk = drm_dp_करोwnstream_min_पंचांगds_घड़ी(dpcd, port_cap, edid);
		अगर (clk > 0)
			seq_म_लिखो(m, "\t\tMin TMDS clock: %d kHz\n", clk);

		bpc = drm_dp_करोwnstream_max_bpc(dpcd, port_cap, edid);

		अगर (bpc > 0)
			seq_म_लिखो(m, "\t\tMax bpc: %d\n", bpc);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_dp_करोwnstream_debug);

/**
 * drm_dp_subconnector_type() - get DP branch device type
 * @dpcd: DisplayPort configuration data
 * @port_cap: port capabilities
 */
क्रमागत drm_mode_subconnector
drm_dp_subconnector_type(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
			 स्थिर u8 port_cap[4])
अणु
	पूर्णांक type;
	अगर (!drm_dp_is_branch(dpcd))
		वापस DRM_MODE_SUBCONNECTOR_Native;
	/* DP 1.0 approach */
	अगर (dpcd[DP_DPCD_REV] == DP_DPCD_REV_10) अणु
		type = dpcd[DP_DOWNSTREAMPORT_PRESENT] &
		       DP_DWN_STRM_PORT_TYPE_MASK;

		चयन (type) अणु
		हाल DP_DWN_STRM_PORT_TYPE_TMDS:
			/* Can be HDMI or DVI-D, DVI-D is a safer option */
			वापस DRM_MODE_SUBCONNECTOR_DVID;
		हाल DP_DWN_STRM_PORT_TYPE_ANALOG:
			/* Can be VGA or DVI-A, VGA is more popular */
			वापस DRM_MODE_SUBCONNECTOR_VGA;
		हाल DP_DWN_STRM_PORT_TYPE_DP:
			वापस DRM_MODE_SUBCONNECTOR_DisplayPort;
		हाल DP_DWN_STRM_PORT_TYPE_OTHER:
		शेष:
			वापस DRM_MODE_SUBCONNECTOR_Unknown;
		पूर्ण
	पूर्ण
	type = port_cap[0] & DP_DS_PORT_TYPE_MASK;

	चयन (type) अणु
	हाल DP_DS_PORT_TYPE_DP:
	हाल DP_DS_PORT_TYPE_DP_DUALMODE:
		वापस DRM_MODE_SUBCONNECTOR_DisplayPort;
	हाल DP_DS_PORT_TYPE_VGA:
		वापस DRM_MODE_SUBCONNECTOR_VGA;
	हाल DP_DS_PORT_TYPE_DVI:
		वापस DRM_MODE_SUBCONNECTOR_DVID;
	हाल DP_DS_PORT_TYPE_HDMI:
		वापस DRM_MODE_SUBCONNECTOR_HDMIA;
	हाल DP_DS_PORT_TYPE_WIRELESS:
		वापस DRM_MODE_SUBCONNECTOR_Wireless;
	हाल DP_DS_PORT_TYPE_NON_EDID:
	शेष:
		वापस DRM_MODE_SUBCONNECTOR_Unknown;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_dp_subconnector_type);

/**
 * drm_dp_set_subconnector_property - set subconnector क्रम DP connector
 * @connector: connector to set property on
 * @status: connector status
 * @dpcd: DisplayPort configuration data
 * @port_cap: port capabilities
 *
 * Called by a driver on every detect event.
 */
व्योम drm_dp_set_subconnector_property(काष्ठा drm_connector *connector,
				      क्रमागत drm_connector_status status,
				      स्थिर u8 *dpcd,
				      स्थिर u8 port_cap[4])
अणु
	क्रमागत drm_mode_subconnector subconnector = DRM_MODE_SUBCONNECTOR_Unknown;

	अगर (status == connector_status_connected)
		subconnector = drm_dp_subconnector_type(dpcd, port_cap);
	drm_object_property_set_value(&connector->base,
			connector->dev->mode_config.dp_subconnector_property,
			subconnector);
पूर्ण
EXPORT_SYMBOL(drm_dp_set_subconnector_property);

/**
 * drm_dp_पढ़ो_sink_count_cap() - Check whether a given connector has a valid sink
 * count
 * @connector: The DRM connector to check
 * @dpcd: A cached copy of the connector's DPCD RX capabilities
 * @desc: A cached copy of the connector's DP descriptor
 *
 * See also: drm_dp_पढ़ो_sink_count()
 *
 * Returns: %True अगर the (e)DP connector has a valid sink count that should
 * be probed, %false otherwise.
 */
bool drm_dp_पढ़ो_sink_count_cap(काष्ठा drm_connector *connector,
				स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
				स्थिर काष्ठा drm_dp_desc *desc)
अणु
	/* Some eDP panels करोn't set a valid value क्रम the sink count */
	वापस connector->connector_type != DRM_MODE_CONNECTOR_eDP &&
		dpcd[DP_DPCD_REV] >= DP_DPCD_REV_11 &&
		dpcd[DP_DOWNSTREAMPORT_PRESENT] & DP_DWN_STRM_PORT_PRESENT &&
		!drm_dp_has_quirk(desc, DP_DPCD_QUIRK_NO_SINK_COUNT);
पूर्ण
EXPORT_SYMBOL(drm_dp_पढ़ो_sink_count_cap);

/**
 * drm_dp_पढ़ो_sink_count() - Retrieve the sink count क्रम a given sink
 * @aux: The DP AUX channel to use
 *
 * See also: drm_dp_पढ़ो_sink_count_cap()
 *
 * Returns: The current sink count reported by @aux, or a negative error code
 * otherwise.
 */
पूर्णांक drm_dp_पढ़ो_sink_count(काष्ठा drm_dp_aux *aux)
अणु
	u8 count;
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ोb(aux, DP_SINK_COUNT, &count);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != 1)
		वापस -EIO;

	वापस DP_GET_SINK_COUNT(count);
पूर्ण
EXPORT_SYMBOL(drm_dp_पढ़ो_sink_count);

/*
 * I2C-over-AUX implementation
 */

अटल u32 drm_dp_i2c_functionality(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL |
	       I2C_FUNC_SMBUS_READ_BLOCK_DATA |
	       I2C_FUNC_SMBUS_BLOCK_PROC_CALL |
	       I2C_FUNC_10BIT_ADDR;
पूर्ण

अटल व्योम drm_dp_i2c_msg_ग_लिखो_status_update(काष्ठा drm_dp_aux_msg *msg)
अणु
	/*
	 * In हाल of i2c defer or लघु i2c ack reply to a ग_लिखो,
	 * we need to चयन to WRITE_STATUS_UPDATE to drain the
	 * rest of the message
	 */
	अगर ((msg->request & ~DP_AUX_I2C_MOT) == DP_AUX_I2C_WRITE) अणु
		msg->request &= DP_AUX_I2C_MOT;
		msg->request |= DP_AUX_I2C_WRITE_STATUS_UPDATE;
	पूर्ण
पूर्ण

#घोषणा AUX_PRECHARGE_LEN 10 /* 10 to 16 */
#घोषणा AUX_SYNC_LEN (16 + 4) /* preamble + AUX_SYNC_END */
#घोषणा AUX_STOP_LEN 4
#घोषणा AUX_CMD_LEN 4
#घोषणा AUX_ADDRESS_LEN 20
#घोषणा AUX_REPLY_PAD_LEN 4
#घोषणा AUX_LENGTH_LEN 8

/*
 * Calculate the duration of the AUX request/reply in usec. Gives the
 * "best" हाल estimate, ie. successful जबतक as लघु as possible.
 */
अटल पूर्णांक drm_dp_aux_req_duration(स्थिर काष्ठा drm_dp_aux_msg *msg)
अणु
	पूर्णांक len = AUX_PRECHARGE_LEN + AUX_SYNC_LEN + AUX_STOP_LEN +
		AUX_CMD_LEN + AUX_ADDRESS_LEN + AUX_LENGTH_LEN;

	अगर ((msg->request & DP_AUX_I2C_READ) == 0)
		len += msg->size * 8;

	वापस len;
पूर्ण

अटल पूर्णांक drm_dp_aux_reply_duration(स्थिर काष्ठा drm_dp_aux_msg *msg)
अणु
	पूर्णांक len = AUX_PRECHARGE_LEN + AUX_SYNC_LEN + AUX_STOP_LEN +
		AUX_CMD_LEN + AUX_REPLY_PAD_LEN;

	/*
	 * For पढ़ो we expect what was asked. For ग_लिखोs there will
	 * be 0 or 1 data bytes. Assume 0 क्रम the "best" हाल.
	 */
	अगर (msg->request & DP_AUX_I2C_READ)
		len += msg->size * 8;

	वापस len;
पूर्ण

#घोषणा I2C_START_LEN 1
#घोषणा I2C_STOP_LEN 1
#घोषणा I2C_ADDR_LEN 9 /* ADDRESS + R/W + ACK/NACK */
#घोषणा I2C_DATA_LEN 9 /* DATA + ACK/NACK */

/*
 * Calculate the length of the i2c transfer in usec, assuming
 * the i2c bus speed is as specअगरied. Gives the the "worst"
 * हाल estimate, ie. successful जबतक as दीर्घ as possible.
 * Doesn't account the the "MOT" bit, and instead assumes each
 * message includes a START, ADDRESS and STOP. Neither करोes it
 * account क्रम additional अक्रमom variables such as घड़ी stretching.
 */
अटल पूर्णांक drm_dp_i2c_msg_duration(स्थिर काष्ठा drm_dp_aux_msg *msg,
				   पूर्णांक i2c_speed_khz)
अणु
	/* AUX bitrate is 1MHz, i2c bitrate as specअगरied */
	वापस DIV_ROUND_UP((I2C_START_LEN + I2C_ADDR_LEN +
			     msg->size * I2C_DATA_LEN +
			     I2C_STOP_LEN) * 1000, i2c_speed_khz);
पूर्ण

/*
 * Deterine how many retries should be attempted to successfully transfer
 * the specअगरied message, based on the estimated durations of the
 * i2c and AUX transfers.
 */
अटल पूर्णांक drm_dp_i2c_retry_count(स्थिर काष्ठा drm_dp_aux_msg *msg,
			      पूर्णांक i2c_speed_khz)
अणु
	पूर्णांक aux_समय_us = drm_dp_aux_req_duration(msg) +
		drm_dp_aux_reply_duration(msg);
	पूर्णांक i2c_समय_us = drm_dp_i2c_msg_duration(msg, i2c_speed_khz);

	वापस DIV_ROUND_UP(i2c_समय_us, aux_समय_us + AUX_RETRY_INTERVAL);
पूर्ण

/*
 * FIXME currently assumes 10 kHz as some real world devices seem
 * to require it. We should query/set the speed via DPCD अगर supported.
 */
अटल पूर्णांक dp_aux_i2c_speed_khz __पढ़ो_mostly = 10;
module_param_unsafe(dp_aux_i2c_speed_khz, पूर्णांक, 0644);
MODULE_PARM_DESC(dp_aux_i2c_speed_khz,
		 "Assumed speed of the i2c bus in kHz, (1-400, default 10)");

/*
 * Transfer a single I2C-over-AUX message and handle various error conditions,
 * retrying the transaction as appropriate.  It is assumed that the
 * &drm_dp_aux.transfer function करोes not modअगरy anything in the msg other than the
 * reply field.
 *
 * Returns bytes transferred on success, or a negative error code on failure.
 */
अटल पूर्णांक drm_dp_i2c_करो_msg(काष्ठा drm_dp_aux *aux, काष्ठा drm_dp_aux_msg *msg)
अणु
	अचिन्हित पूर्णांक retry, defer_i2c;
	पूर्णांक ret;
	/*
	 * DP1.2 sections 2.7.7.1.5.6.1 and 2.7.7.1.6.6.1: A DP Source device
	 * is required to retry at least seven बार upon receiving AUX_DEFER
	 * beक्रमe giving up the AUX transaction.
	 *
	 * We also try to account क्रम the i2c bus speed.
	 */
	पूर्णांक max_retries = max(7, drm_dp_i2c_retry_count(msg, dp_aux_i2c_speed_khz));

	क्रम (retry = 0, defer_i2c = 0; retry < (max_retries + defer_i2c); retry++) अणु
		ret = aux->transfer(aux, msg);
		अगर (ret < 0) अणु
			अगर (ret == -EBUSY)
				जारी;

			/*
			 * While समयouts can be errors, they're usually normal
			 * behavior (क्रम instance, when a driver tries to
			 * communicate with a non-existant DisplayPort device).
			 * Aव्योम spamming the kernel log with समयout errors.
			 */
			अगर (ret == -ETIMEDOUT)
				DRM_DEBUG_KMS_RATELIMITED("%s: transaction timed out\n",
							  aux->name);
			अन्यथा
				DRM_DEBUG_KMS("%s: transaction failed: %d\n",
					      aux->name, ret);
			वापस ret;
		पूर्ण


		चयन (msg->reply & DP_AUX_NATIVE_REPLY_MASK) अणु
		हाल DP_AUX_NATIVE_REPLY_ACK:
			/*
			 * For I2C-over-AUX transactions this isn't enough, we
			 * need to check क्रम the I2C ACK reply.
			 */
			अवरोध;

		हाल DP_AUX_NATIVE_REPLY_NACK:
			DRM_DEBUG_KMS("%s: native nack (result=%d, size=%zu)\n",
				      aux->name, ret, msg->size);
			वापस -EREMOTEIO;

		हाल DP_AUX_NATIVE_REPLY_DEFER:
			DRM_DEBUG_KMS("%s: native defer\n", aux->name);
			/*
			 * We could check क्रम I2C bit rate capabilities and अगर
			 * available adjust this पूर्णांकerval. We could also be
			 * more careful with DP-to-legacy adapters where a
			 * दीर्घ legacy cable may क्रमce very low I2C bit rates.
			 *
			 * For now just defer क्रम दीर्घ enough to hopefully be
			 * safe क्रम all use-हालs.
			 */
			usleep_range(AUX_RETRY_INTERVAL, AUX_RETRY_INTERVAL + 100);
			जारी;

		शेष:
			DRM_ERROR("%s: invalid native reply %#04x\n",
				  aux->name, msg->reply);
			वापस -EREMOTEIO;
		पूर्ण

		चयन (msg->reply & DP_AUX_I2C_REPLY_MASK) अणु
		हाल DP_AUX_I2C_REPLY_ACK:
			/*
			 * Both native ACK and I2C ACK replies received. We
			 * can assume the transfer was successful.
			 */
			अगर (ret != msg->size)
				drm_dp_i2c_msg_ग_लिखो_status_update(msg);
			वापस ret;

		हाल DP_AUX_I2C_REPLY_NACK:
			DRM_DEBUG_KMS("%s: I2C nack (result=%d, size=%zu)\n",
				      aux->name, ret, msg->size);
			aux->i2c_nack_count++;
			वापस -EREMOTEIO;

		हाल DP_AUX_I2C_REPLY_DEFER:
			DRM_DEBUG_KMS("%s: I2C defer\n", aux->name);
			/* DP Compliance Test 4.2.2.5 Requirement:
			 * Must have at least 7 retries क्रम I2C defers on the
			 * transaction to pass this test
			 */
			aux->i2c_defer_count++;
			अगर (defer_i2c < 7)
				defer_i2c++;
			usleep_range(AUX_RETRY_INTERVAL, AUX_RETRY_INTERVAL + 100);
			drm_dp_i2c_msg_ग_लिखो_status_update(msg);

			जारी;

		शेष:
			DRM_ERROR("%s: invalid I2C reply %#04x\n",
				  aux->name, msg->reply);
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण

	DRM_DEBUG_KMS("%s: Too many retries, giving up\n", aux->name);
	वापस -EREMOTEIO;
पूर्ण

अटल व्योम drm_dp_i2c_msg_set_request(काष्ठा drm_dp_aux_msg *msg,
				       स्थिर काष्ठा i2c_msg *i2c_msg)
अणु
	msg->request = (i2c_msg->flags & I2C_M_RD) ?
		DP_AUX_I2C_READ : DP_AUX_I2C_WRITE;
	अगर (!(i2c_msg->flags & I2C_M_STOP))
		msg->request |= DP_AUX_I2C_MOT;
पूर्ण

/*
 * Keep retrying drm_dp_i2c_करो_msg until all data has been transferred.
 *
 * Returns an error code on failure, or a recommended transfer size on success.
 */
अटल पूर्णांक drm_dp_i2c_drain_msg(काष्ठा drm_dp_aux *aux, काष्ठा drm_dp_aux_msg *orig_msg)
अणु
	पूर्णांक err, ret = orig_msg->size;
	काष्ठा drm_dp_aux_msg msg = *orig_msg;

	जबतक (msg.size > 0) अणु
		err = drm_dp_i2c_करो_msg(aux, &msg);
		अगर (err <= 0)
			वापस err == 0 ? -EPROTO : err;

		अगर (err < msg.size && err < ret) अणु
			DRM_DEBUG_KMS("%s: Partial I2C reply: requested %zu bytes got %d bytes\n",
				      aux->name, msg.size, err);
			ret = err;
		पूर्ण

		msg.size -= err;
		msg.buffer += err;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Bizlink deचिन्हित DP->DVI-D Dual Link adapters require the I2C over AUX
 * packets to be as large as possible. If not, the I2C transactions never
 * succeed. Hence the शेष is maximum.
 */
अटल पूर्णांक dp_aux_i2c_transfer_size __पढ़ो_mostly = DP_AUX_MAX_PAYLOAD_BYTES;
module_param_unsafe(dp_aux_i2c_transfer_size, पूर्णांक, 0644);
MODULE_PARM_DESC(dp_aux_i2c_transfer_size,
		 "Number of bytes to transfer in a single I2C over DP AUX CH message, (1-16, default 16)");

अटल पूर्णांक drm_dp_i2c_xfer(काष्ठा i2c_adapter *adapter, काष्ठा i2c_msg *msgs,
			   पूर्णांक num)
अणु
	काष्ठा drm_dp_aux *aux = adapter->algo_data;
	अचिन्हित पूर्णांक i, j;
	अचिन्हित transfer_size;
	काष्ठा drm_dp_aux_msg msg;
	पूर्णांक err = 0;

	dp_aux_i2c_transfer_size = clamp(dp_aux_i2c_transfer_size, 1, DP_AUX_MAX_PAYLOAD_BYTES);

	स_रखो(&msg, 0, माप(msg));

	क्रम (i = 0; i < num; i++) अणु
		msg.address = msgs[i].addr;
		drm_dp_i2c_msg_set_request(&msg, &msgs[i]);
		/* Send a bare address packet to start the transaction.
		 * Zero sized messages specअगरy an address only (bare
		 * address) transaction.
		 */
		msg.buffer = शून्य;
		msg.size = 0;
		err = drm_dp_i2c_करो_msg(aux, &msg);

		/*
		 * Reset msg.request in हाल in हाल it got
		 * changed पूर्णांकo a WRITE_STATUS_UPDATE.
		 */
		drm_dp_i2c_msg_set_request(&msg, &msgs[i]);

		अगर (err < 0)
			अवरोध;
		/* We want each transaction to be as large as possible, but
		 * we'll go to smaller sizes अगर the hardware gives us a
		 * लघु reply.
		 */
		transfer_size = dp_aux_i2c_transfer_size;
		क्रम (j = 0; j < msgs[i].len; j += msg.size) अणु
			msg.buffer = msgs[i].buf + j;
			msg.size = min(transfer_size, msgs[i].len - j);

			err = drm_dp_i2c_drain_msg(aux, &msg);

			/*
			 * Reset msg.request in हाल in हाल it got
			 * changed पूर्णांकo a WRITE_STATUS_UPDATE.
			 */
			drm_dp_i2c_msg_set_request(&msg, &msgs[i]);

			अगर (err < 0)
				अवरोध;
			transfer_size = err;
		पूर्ण
		अगर (err < 0)
			अवरोध;
	पूर्ण
	अगर (err >= 0)
		err = num;
	/* Send a bare address packet to बंद out the transaction.
	 * Zero sized messages specअगरy an address only (bare
	 * address) transaction.
	 */
	msg.request &= ~DP_AUX_I2C_MOT;
	msg.buffer = शून्य;
	msg.size = 0;
	(व्योम)drm_dp_i2c_करो_msg(aux, &msg);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm drm_dp_i2c_algo = अणु
	.functionality = drm_dp_i2c_functionality,
	.master_xfer = drm_dp_i2c_xfer,
पूर्ण;

अटल काष्ठा drm_dp_aux *i2c_to_aux(काष्ठा i2c_adapter *i2c)
अणु
	वापस container_of(i2c, काष्ठा drm_dp_aux, ddc);
पूर्ण

अटल व्योम lock_bus(काष्ठा i2c_adapter *i2c, अचिन्हित पूर्णांक flags)
अणु
	mutex_lock(&i2c_to_aux(i2c)->hw_mutex);
पूर्ण

अटल पूर्णांक trylock_bus(काष्ठा i2c_adapter *i2c, अचिन्हित पूर्णांक flags)
अणु
	वापस mutex_trylock(&i2c_to_aux(i2c)->hw_mutex);
पूर्ण

अटल व्योम unlock_bus(काष्ठा i2c_adapter *i2c, अचिन्हित पूर्णांक flags)
अणु
	mutex_unlock(&i2c_to_aux(i2c)->hw_mutex);
पूर्ण

अटल स्थिर काष्ठा i2c_lock_operations drm_dp_i2c_lock_ops = अणु
	.lock_bus = lock_bus,
	.trylock_bus = trylock_bus,
	.unlock_bus = unlock_bus,
पूर्ण;

अटल पूर्णांक drm_dp_aux_get_crc(काष्ठा drm_dp_aux *aux, u8 *crc)
अणु
	u8 buf, count;
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ोb(aux, DP_TEST_SINK, &buf);
	अगर (ret < 0)
		वापस ret;

	WARN_ON(!(buf & DP_TEST_SINK_START));

	ret = drm_dp_dpcd_पढ़ोb(aux, DP_TEST_SINK_MISC, &buf);
	अगर (ret < 0)
		वापस ret;

	count = buf & DP_TEST_COUNT_MASK;
	अगर (count == aux->crc_count)
		वापस -EAGAIN; /* No CRC yet */

	aux->crc_count = count;

	/*
	 * At DP_TEST_CRC_R_CR, there's 6 bytes containing CRC data, 2 bytes
	 * per component (RGB or CrYCb).
	 */
	ret = drm_dp_dpcd_पढ़ो(aux, DP_TEST_CRC_R_CR, crc, 6);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम drm_dp_aux_crc_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_dp_aux *aux = container_of(work, काष्ठा drm_dp_aux,
					      crc_work);
	काष्ठा drm_crtc *crtc;
	u8 crc_bytes[6];
	uपूर्णांक32_t crcs[3];
	पूर्णांक ret;

	अगर (WARN_ON(!aux->crtc))
		वापस;

	crtc = aux->crtc;
	जबतक (crtc->crc.खोलोed) अणु
		drm_crtc_रुको_one_vblank(crtc);
		अगर (!crtc->crc.खोलोed)
			अवरोध;

		ret = drm_dp_aux_get_crc(aux, crc_bytes);
		अगर (ret == -EAGAIN) अणु
			usleep_range(1000, 2000);
			ret = drm_dp_aux_get_crc(aux, crc_bytes);
		पूर्ण

		अगर (ret == -EAGAIN) अणु
			DRM_DEBUG_KMS("%s: Get CRC failed after retrying: %d\n",
				      aux->name, ret);
			जारी;
		पूर्ण अन्यथा अगर (ret) अणु
			DRM_DEBUG_KMS("%s: Failed to get a CRC: %d\n",
				      aux->name, ret);
			जारी;
		पूर्ण

		crcs[0] = crc_bytes[0] | crc_bytes[1] << 8;
		crcs[1] = crc_bytes[2] | crc_bytes[3] << 8;
		crcs[2] = crc_bytes[4] | crc_bytes[5] << 8;
		drm_crtc_add_crc_entry(crtc, false, 0, crcs);
	पूर्ण
पूर्ण

/**
 * drm_dp_remote_aux_init() - minimally initialise a remote aux channel
 * @aux: DisplayPort AUX channel
 *
 * Used क्रम remote aux channel in general. Merely initialize the crc work
 * काष्ठा.
 */
व्योम drm_dp_remote_aux_init(काष्ठा drm_dp_aux *aux)
अणु
	INIT_WORK(&aux->crc_work, drm_dp_aux_crc_work);
पूर्ण
EXPORT_SYMBOL(drm_dp_remote_aux_init);

/**
 * drm_dp_aux_init() - minimally initialise an aux channel
 * @aux: DisplayPort AUX channel
 *
 * If you need to use the drm_dp_aux's i2c adapter prior to रेजिस्टरing it
 * with the outside world, call drm_dp_aux_init() first. You must still
 * call drm_dp_aux_रेजिस्टर() once the connector has been रेजिस्टरed to
 * allow userspace access to the auxiliary DP channel.
 */
व्योम drm_dp_aux_init(काष्ठा drm_dp_aux *aux)
अणु
	mutex_init(&aux->hw_mutex);
	mutex_init(&aux->cec.lock);
	INIT_WORK(&aux->crc_work, drm_dp_aux_crc_work);

	aux->ddc.algo = &drm_dp_i2c_algo;
	aux->ddc.algo_data = aux;
	aux->ddc.retries = 3;

	aux->ddc.lock_ops = &drm_dp_i2c_lock_ops;
पूर्ण
EXPORT_SYMBOL(drm_dp_aux_init);

/**
 * drm_dp_aux_रेजिस्टर() - initialise and रेजिस्टर aux channel
 * @aux: DisplayPort AUX channel
 *
 * Automatically calls drm_dp_aux_init() अगर this hasn't been करोne yet.
 * This should only be called when the underlying &काष्ठा drm_connector is
 * initialiazed alपढ़ोy. Thereक्रमe the best place to call this is from
 * &drm_connector_funcs.late_रेजिस्टर. Not that drivers which करोn't follow this
 * will Oops when CONFIG_DRM_DP_AUX_CHARDEV is enabled.
 *
 * Drivers which need to use the aux channel beक्रमe that poपूर्णांक (e.g. at driver
 * load समय, beक्रमe drm_dev_रेजिस्टर() has been called) need to call
 * drm_dp_aux_init().
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक drm_dp_aux_रेजिस्टर(काष्ठा drm_dp_aux *aux)
अणु
	पूर्णांक ret;

	अगर (!aux->ddc.algo)
		drm_dp_aux_init(aux);

	aux->ddc.class = I2C_CLASS_DDC;
	aux->ddc.owner = THIS_MODULE;
	aux->ddc.dev.parent = aux->dev;

	strlcpy(aux->ddc.name, aux->name ? aux->name : dev_name(aux->dev),
		माप(aux->ddc.name));

	ret = drm_dp_aux_रेजिस्टर_devnode(aux);
	अगर (ret)
		वापस ret;

	ret = i2c_add_adapter(&aux->ddc);
	अगर (ret) अणु
		drm_dp_aux_unरेजिस्टर_devnode(aux);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_aux_रेजिस्टर);

/**
 * drm_dp_aux_unरेजिस्टर() - unरेजिस्टर an AUX adapter
 * @aux: DisplayPort AUX channel
 */
व्योम drm_dp_aux_unरेजिस्टर(काष्ठा drm_dp_aux *aux)
अणु
	drm_dp_aux_unरेजिस्टर_devnode(aux);
	i2c_del_adapter(&aux->ddc);
पूर्ण
EXPORT_SYMBOL(drm_dp_aux_unरेजिस्टर);

#घोषणा PSR_SETUP_TIME(x) [DP_PSR_SETUP_TIME_ ## x >> DP_PSR_SETUP_TIME_SHIFT] = (x)

/**
 * drm_dp_psr_setup_समय() - PSR setup in समय usec
 * @psr_cap: PSR capabilities from DPCD
 *
 * Returns:
 * PSR setup समय क्रम the panel in microseconds,  negative
 * error code on failure.
 */
पूर्णांक drm_dp_psr_setup_समय(स्थिर u8 psr_cap[EDP_PSR_RECEIVER_CAP_SIZE])
अणु
	अटल स्थिर u16 psr_setup_समय_us[] = अणु
		PSR_SETUP_TIME(330),
		PSR_SETUP_TIME(275),
		PSR_SETUP_TIME(220),
		PSR_SETUP_TIME(165),
		PSR_SETUP_TIME(110),
		PSR_SETUP_TIME(55),
		PSR_SETUP_TIME(0),
	पूर्ण;
	पूर्णांक i;

	i = (psr_cap[1] & DP_PSR_SETUP_TIME_MASK) >> DP_PSR_SETUP_TIME_SHIFT;
	अगर (i >= ARRAY_SIZE(psr_setup_समय_us))
		वापस -EINVAL;

	वापस psr_setup_समय_us[i];
पूर्ण
EXPORT_SYMBOL(drm_dp_psr_setup_समय);

#अघोषित PSR_SETUP_TIME

/**
 * drm_dp_start_crc() - start capture of frame CRCs
 * @aux: DisplayPort AUX channel
 * @crtc: CRTC displaying the frames whose CRCs are to be captured
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक drm_dp_start_crc(काष्ठा drm_dp_aux *aux, काष्ठा drm_crtc *crtc)
अणु
	u8 buf;
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ोb(aux, DP_TEST_SINK, &buf);
	अगर (ret < 0)
		वापस ret;

	ret = drm_dp_dpcd_ग_लिखोb(aux, DP_TEST_SINK, buf | DP_TEST_SINK_START);
	अगर (ret < 0)
		वापस ret;

	aux->crc_count = 0;
	aux->crtc = crtc;
	schedule_work(&aux->crc_work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_start_crc);

/**
 * drm_dp_stop_crc() - stop capture of frame CRCs
 * @aux: DisplayPort AUX channel
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक drm_dp_stop_crc(काष्ठा drm_dp_aux *aux)
अणु
	u8 buf;
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ोb(aux, DP_TEST_SINK, &buf);
	अगर (ret < 0)
		वापस ret;

	ret = drm_dp_dpcd_ग_लिखोb(aux, DP_TEST_SINK, buf & ~DP_TEST_SINK_START);
	अगर (ret < 0)
		वापस ret;

	flush_work(&aux->crc_work);
	aux->crtc = शून्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_stop_crc);

काष्ठा dpcd_quirk अणु
	u8 oui[3];
	u8 device_id[6];
	bool is_branch;
	u32 quirks;
पूर्ण;

#घोषणा OUI(first, second, third) अणु (first), (second), (third) पूर्ण
#घोषणा DEVICE_ID(first, second, third, fourth, fअगरth, sixth) \
	अणु (first), (second), (third), (fourth), (fअगरth), (sixth) पूर्ण

#घोषणा DEVICE_ID_ANY	DEVICE_ID(0, 0, 0, 0, 0, 0)

अटल स्थिर काष्ठा dpcd_quirk dpcd_quirk_list[] = अणु
	/* Analogix 7737 needs reduced M and N at HBR2 link rates */
	अणु OUI(0x00, 0x22, 0xb9), DEVICE_ID_ANY, true, BIT(DP_DPCD_QUIRK_CONSTANT_N) पूर्ण,
	/* LG LP140WF6-SPM1 eDP panel */
	अणु OUI(0x00, 0x22, 0xb9), DEVICE_ID('s', 'i', 'v', 'a', 'r', 'T'), false, BIT(DP_DPCD_QUIRK_CONSTANT_N) पूर्ण,
	/* Apple panels need some additional handling to support PSR */
	अणु OUI(0x00, 0x10, 0xfa), DEVICE_ID_ANY, false, BIT(DP_DPCD_QUIRK_NO_PSR) पूर्ण,
	/* CH7511 seems to leave SINK_COUNT zeroed */
	अणु OUI(0x00, 0x00, 0x00), DEVICE_ID('C', 'H', '7', '5', '1', '1'), false, BIT(DP_DPCD_QUIRK_NO_SINK_COUNT) पूर्ण,
	/* Synaptics DP1.4 MST hubs can support DSC without भव DPCD */
	अणु OUI(0x90, 0xCC, 0x24), DEVICE_ID_ANY, true, BIT(DP_DPCD_QUIRK_DSC_WITHOUT_VIRTUAL_DPCD) पूर्ण,
	/* Apple MacBookPro 2017 15 inch eDP Retina panel reports too low DP_MAX_LINK_RATE */
	अणु OUI(0x00, 0x10, 0xfa), DEVICE_ID(101, 68, 21, 101, 98, 97), false, BIT(DP_DPCD_QUIRK_CAN_DO_MAX_LINK_RATE_3_24_GBPS) पूर्ण,
पूर्ण;

#अघोषित OUI

/*
 * Get a bit mask of DPCD quirks क्रम the sink/branch device identअगरied by
 * ident. The quirk data is shared but it's up to the drivers to act on the
 * data.
 *
 * For now, only the OUI (first three bytes) is used, but this may be extended
 * to device identअगरication string and hardware/firmware revisions later.
 */
अटल u32
drm_dp_get_quirks(स्थिर काष्ठा drm_dp_dpcd_ident *ident, bool is_branch)
अणु
	स्थिर काष्ठा dpcd_quirk *quirk;
	u32 quirks = 0;
	पूर्णांक i;
	u8 any_device[] = DEVICE_ID_ANY;

	क्रम (i = 0; i < ARRAY_SIZE(dpcd_quirk_list); i++) अणु
		quirk = &dpcd_quirk_list[i];

		अगर (quirk->is_branch != is_branch)
			जारी;

		अगर (स_भेद(quirk->oui, ident->oui, माप(ident->oui)) != 0)
			जारी;

		अगर (स_भेद(quirk->device_id, any_device, माप(any_device)) != 0 &&
		    स_भेद(quirk->device_id, ident->device_id, माप(ident->device_id)) != 0)
			जारी;

		quirks |= quirk->quirks;
	पूर्ण

	वापस quirks;
पूर्ण

#अघोषित DEVICE_ID_ANY
#अघोषित DEVICE_ID

/**
 * drm_dp_पढ़ो_desc - पढ़ो sink/branch descriptor from DPCD
 * @aux: DisplayPort AUX channel
 * @desc: Device descriptor to fill from DPCD
 * @is_branch: true क्रम branch devices, false क्रम sink devices
 *
 * Read DPCD 0x400 (sink) or 0x500 (branch) पूर्णांकo @desc. Also debug log the
 * identअगरication.
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक drm_dp_पढ़ो_desc(काष्ठा drm_dp_aux *aux, काष्ठा drm_dp_desc *desc,
		     bool is_branch)
अणु
	काष्ठा drm_dp_dpcd_ident *ident = &desc->ident;
	अचिन्हित पूर्णांक offset = is_branch ? DP_BRANCH_OUI : DP_SINK_OUI;
	पूर्णांक ret, dev_id_len;

	ret = drm_dp_dpcd_पढ़ो(aux, offset, ident, माप(*ident));
	अगर (ret < 0)
		वापस ret;

	desc->quirks = drm_dp_get_quirks(ident, is_branch);

	dev_id_len = strnlen(ident->device_id, माप(ident->device_id));

	DRM_DEBUG_KMS("%s: DP %s: OUI %*phD dev-ID %*pE HW-rev %d.%d SW-rev %d.%d quirks 0x%04x\n",
		      aux->name, is_branch ? "branch" : "sink",
		      (पूर्णांक)माप(ident->oui), ident->oui,
		      dev_id_len, ident->device_id,
		      ident->hw_rev >> 4, ident->hw_rev & 0xf,
		      ident->sw_major_rev, ident->sw_minor_rev,
		      desc->quirks);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_पढ़ो_desc);

/**
 * drm_dp_dsc_sink_max_slice_count() - Get the max slice count
 * supported by the DSC sink.
 * @dsc_dpcd: DSC capabilities from DPCD
 * @is_edp: true अगर its eDP, false क्रम DP
 *
 * Read the slice capabilities DPCD रेजिस्टर from DSC sink to get
 * the maximum slice count supported. This is used to populate
 * the DSC parameters in the &काष्ठा drm_dsc_config by the driver.
 * Driver creates an infoframe using these parameters to populate
 * &काष्ठा drm_dsc_pps_infoframe. These are sent to the sink using DSC
 * infoframe using the helper function drm_dsc_pps_infoframe_pack()
 *
 * Returns:
 * Maximum slice count supported by DSC sink or 0 its invalid
 */
u8 drm_dp_dsc_sink_max_slice_count(स्थिर u8 dsc_dpcd[DP_DSC_RECEIVER_CAP_SIZE],
				   bool is_edp)
अणु
	u8 slice_cap1 = dsc_dpcd[DP_DSC_SLICE_CAP_1 - DP_DSC_SUPPORT];

	अगर (is_edp) अणु
		/* For eDP, रेजिस्टर DSC_SLICE_CAPABILITIES_1 gives slice count */
		अगर (slice_cap1 & DP_DSC_4_PER_DP_DSC_SINK)
			वापस 4;
		अगर (slice_cap1 & DP_DSC_2_PER_DP_DSC_SINK)
			वापस 2;
		अगर (slice_cap1 & DP_DSC_1_PER_DP_DSC_SINK)
			वापस 1;
	पूर्ण अन्यथा अणु
		/* For DP, use values from DSC_SLICE_CAP_1 and DSC_SLICE_CAP2 */
		u8 slice_cap2 = dsc_dpcd[DP_DSC_SLICE_CAP_2 - DP_DSC_SUPPORT];

		अगर (slice_cap2 & DP_DSC_24_PER_DP_DSC_SINK)
			वापस 24;
		अगर (slice_cap2 & DP_DSC_20_PER_DP_DSC_SINK)
			वापस 20;
		अगर (slice_cap2 & DP_DSC_16_PER_DP_DSC_SINK)
			वापस 16;
		अगर (slice_cap1 & DP_DSC_12_PER_DP_DSC_SINK)
			वापस 12;
		अगर (slice_cap1 & DP_DSC_10_PER_DP_DSC_SINK)
			वापस 10;
		अगर (slice_cap1 & DP_DSC_8_PER_DP_DSC_SINK)
			वापस 8;
		अगर (slice_cap1 & DP_DSC_6_PER_DP_DSC_SINK)
			वापस 6;
		अगर (slice_cap1 & DP_DSC_4_PER_DP_DSC_SINK)
			वापस 4;
		अगर (slice_cap1 & DP_DSC_2_PER_DP_DSC_SINK)
			वापस 2;
		अगर (slice_cap1 & DP_DSC_1_PER_DP_DSC_SINK)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_dsc_sink_max_slice_count);

/**
 * drm_dp_dsc_sink_line_buf_depth() - Get the line buffer depth in bits
 * @dsc_dpcd: DSC capabilities from DPCD
 *
 * Read the DSC DPCD रेजिस्टर to parse the line buffer depth in bits which is
 * number of bits of precision within the decoder line buffer supported by
 * the DSC sink. This is used to populate the DSC parameters in the
 * &काष्ठा drm_dsc_config by the driver.
 * Driver creates an infoframe using these parameters to populate
 * &काष्ठा drm_dsc_pps_infoframe. These are sent to the sink using DSC
 * infoframe using the helper function drm_dsc_pps_infoframe_pack()
 *
 * Returns:
 * Line buffer depth supported by DSC panel or 0 its invalid
 */
u8 drm_dp_dsc_sink_line_buf_depth(स्थिर u8 dsc_dpcd[DP_DSC_RECEIVER_CAP_SIZE])
अणु
	u8 line_buf_depth = dsc_dpcd[DP_DSC_LINE_BUF_BIT_DEPTH - DP_DSC_SUPPORT];

	चयन (line_buf_depth & DP_DSC_LINE_BUF_BIT_DEPTH_MASK) अणु
	हाल DP_DSC_LINE_BUF_BIT_DEPTH_9:
		वापस 9;
	हाल DP_DSC_LINE_BUF_BIT_DEPTH_10:
		वापस 10;
	हाल DP_DSC_LINE_BUF_BIT_DEPTH_11:
		वापस 11;
	हाल DP_DSC_LINE_BUF_BIT_DEPTH_12:
		वापस 12;
	हाल DP_DSC_LINE_BUF_BIT_DEPTH_13:
		वापस 13;
	हाल DP_DSC_LINE_BUF_BIT_DEPTH_14:
		वापस 14;
	हाल DP_DSC_LINE_BUF_BIT_DEPTH_15:
		वापस 15;
	हाल DP_DSC_LINE_BUF_BIT_DEPTH_16:
		वापस 16;
	हाल DP_DSC_LINE_BUF_BIT_DEPTH_8:
		वापस 8;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_dsc_sink_line_buf_depth);

/**
 * drm_dp_dsc_sink_supported_input_bpcs() - Get all the input bits per component
 * values supported by the DSC sink.
 * @dsc_dpcd: DSC capabilities from DPCD
 * @dsc_bpc: An array to be filled by this helper with supported
 *           input bpcs.
 *
 * Read the DSC DPCD from the sink device to parse the supported bits per
 * component values. This is used to populate the DSC parameters
 * in the &काष्ठा drm_dsc_config by the driver.
 * Driver creates an infoframe using these parameters to populate
 * &काष्ठा drm_dsc_pps_infoframe. These are sent to the sink using DSC
 * infoframe using the helper function drm_dsc_pps_infoframe_pack()
 *
 * Returns:
 * Number of input BPC values parsed from the DPCD
 */
पूर्णांक drm_dp_dsc_sink_supported_input_bpcs(स्थिर u8 dsc_dpcd[DP_DSC_RECEIVER_CAP_SIZE],
					 u8 dsc_bpc[3])
अणु
	पूर्णांक num_bpc = 0;
	u8 color_depth = dsc_dpcd[DP_DSC_DEC_COLOR_DEPTH_CAP - DP_DSC_SUPPORT];

	अगर (color_depth & DP_DSC_12_BPC)
		dsc_bpc[num_bpc++] = 12;
	अगर (color_depth & DP_DSC_10_BPC)
		dsc_bpc[num_bpc++] = 10;
	अगर (color_depth & DP_DSC_8_BPC)
		dsc_bpc[num_bpc++] = 8;

	वापस num_bpc;
पूर्ण
EXPORT_SYMBOL(drm_dp_dsc_sink_supported_input_bpcs);

/**
 * drm_dp_पढ़ो_lttpr_common_caps - पढ़ो the LTTPR common capabilities
 * @aux: DisplayPort AUX channel
 * @caps: buffer to वापस the capability info in
 *
 * Read capabilities common to all LTTPRs.
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक drm_dp_पढ़ो_lttpr_common_caps(काष्ठा drm_dp_aux *aux,
				  u8 caps[DP_LTTPR_COMMON_CAP_SIZE])
अणु
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ो(aux,
			       DP_LT_TUNABLE_PHY_REPEATER_FIELD_DATA_STRUCTURE_REV,
			       caps, DP_LTTPR_COMMON_CAP_SIZE);
	अगर (ret < 0)
		वापस ret;

	WARN_ON(ret != DP_LTTPR_COMMON_CAP_SIZE);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_पढ़ो_lttpr_common_caps);

/**
 * drm_dp_पढ़ो_lttpr_phy_caps - पढ़ो the capabilities क्रम a given LTTPR PHY
 * @aux: DisplayPort AUX channel
 * @dp_phy: LTTPR PHY to पढ़ो the capabilities क्रम
 * @caps: buffer to वापस the capability info in
 *
 * Read the capabilities क्रम the given LTTPR PHY.
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक drm_dp_पढ़ो_lttpr_phy_caps(काष्ठा drm_dp_aux *aux,
			       क्रमागत drm_dp_phy dp_phy,
			       u8 caps[DP_LTTPR_PHY_CAP_SIZE])
अणु
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ो(aux,
			       DP_TRAINING_AUX_RD_INTERVAL_PHY_REPEATER(dp_phy),
			       caps, DP_LTTPR_PHY_CAP_SIZE);
	अगर (ret < 0)
		वापस ret;

	WARN_ON(ret != DP_LTTPR_PHY_CAP_SIZE);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_पढ़ो_lttpr_phy_caps);

अटल u8 dp_lttpr_common_cap(स्थिर u8 caps[DP_LTTPR_COMMON_CAP_SIZE], पूर्णांक r)
अणु
	वापस caps[r - DP_LT_TUNABLE_PHY_REPEATER_FIELD_DATA_STRUCTURE_REV];
पूर्ण

/**
 * drm_dp_lttpr_count - get the number of detected LTTPRs
 * @caps: LTTPR common capabilities
 *
 * Get the number of detected LTTPRs from the LTTPR common capabilities info.
 *
 * Returns:
 *   -दुस्फल अगर more than supported number (8) of LTTPRs are detected
 *   -EINVAL अगर the DP_PHY_REPEATER_CNT रेजिस्टर contains an invalid value
 *   otherwise the number of detected LTTPRs
 */
पूर्णांक drm_dp_lttpr_count(स्थिर u8 caps[DP_LTTPR_COMMON_CAP_SIZE])
अणु
	u8 count = dp_lttpr_common_cap(caps, DP_PHY_REPEATER_CNT);

	चयन (hweight8(count)) अणु
	हाल 0:
		वापस 0;
	हाल 1:
		वापस 8 - ilog2(count);
	हाल 8:
		वापस -दुस्फल;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_dp_lttpr_count);

/**
 * drm_dp_lttpr_max_link_rate - get the maximum link rate supported by all LTTPRs
 * @caps: LTTPR common capabilities
 *
 * Returns the maximum link rate supported by all detected LTTPRs.
 */
पूर्णांक drm_dp_lttpr_max_link_rate(स्थिर u8 caps[DP_LTTPR_COMMON_CAP_SIZE])
अणु
	u8 rate = dp_lttpr_common_cap(caps, DP_MAX_LINK_RATE_PHY_REPEATER);

	वापस drm_dp_bw_code_to_link_rate(rate);
पूर्ण
EXPORT_SYMBOL(drm_dp_lttpr_max_link_rate);

/**
 * drm_dp_lttpr_max_lane_count - get the maximum lane count supported by all LTTPRs
 * @caps: LTTPR common capabilities
 *
 * Returns the maximum lane count supported by all detected LTTPRs.
 */
पूर्णांक drm_dp_lttpr_max_lane_count(स्थिर u8 caps[DP_LTTPR_COMMON_CAP_SIZE])
अणु
	u8 max_lanes = dp_lttpr_common_cap(caps, DP_MAX_LANE_COUNT_PHY_REPEATER);

	वापस max_lanes & DP_MAX_LANE_COUNT_MASK;
पूर्ण
EXPORT_SYMBOL(drm_dp_lttpr_max_lane_count);

/**
 * drm_dp_lttpr_voltage_swing_level_3_supported - check क्रम LTTPR vswing3 support
 * @caps: LTTPR PHY capabilities
 *
 * Returns true अगर the @caps क्रम an LTTPR TX PHY indicate support क्रम
 * voltage swing level 3.
 */
bool
drm_dp_lttpr_voltage_swing_level_3_supported(स्थिर u8 caps[DP_LTTPR_PHY_CAP_SIZE])
अणु
	u8 txcap = dp_lttpr_phy_cap(caps, DP_TRANSMITTER_CAPABILITY_PHY_REPEATER1);

	वापस txcap & DP_VOLTAGE_SWING_LEVEL_3_SUPPORTED;
पूर्ण
EXPORT_SYMBOL(drm_dp_lttpr_voltage_swing_level_3_supported);

/**
 * drm_dp_lttpr_pre_emphasis_level_3_supported - check क्रम LTTPR preemph3 support
 * @caps: LTTPR PHY capabilities
 *
 * Returns true अगर the @caps क्रम an LTTPR TX PHY indicate support क्रम
 * pre-emphasis level 3.
 */
bool
drm_dp_lttpr_pre_emphasis_level_3_supported(स्थिर u8 caps[DP_LTTPR_PHY_CAP_SIZE])
अणु
	u8 txcap = dp_lttpr_phy_cap(caps, DP_TRANSMITTER_CAPABILITY_PHY_REPEATER1);

	वापस txcap & DP_PRE_EMPHASIS_LEVEL_3_SUPPORTED;
पूर्ण
EXPORT_SYMBOL(drm_dp_lttpr_pre_emphasis_level_3_supported);

/**
 * drm_dp_get_phy_test_pattern() - get the requested pattern from the sink.
 * @aux: DisplayPort AUX channel
 * @data: DP phy compliance test parameters.
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक drm_dp_get_phy_test_pattern(काष्ठा drm_dp_aux *aux,
				काष्ठा drm_dp_phy_test_params *data)
अणु
	पूर्णांक err;
	u8 rate, lanes;

	err = drm_dp_dpcd_पढ़ोb(aux, DP_TEST_LINK_RATE, &rate);
	अगर (err < 0)
		वापस err;
	data->link_rate = drm_dp_bw_code_to_link_rate(rate);

	err = drm_dp_dpcd_पढ़ोb(aux, DP_TEST_LANE_COUNT, &lanes);
	अगर (err < 0)
		वापस err;
	data->num_lanes = lanes & DP_MAX_LANE_COUNT_MASK;

	अगर (lanes & DP_ENHANCED_FRAME_CAP)
		data->enhanced_frame_cap = true;

	err = drm_dp_dpcd_पढ़ोb(aux, DP_PHY_TEST_PATTERN, &data->phy_pattern);
	अगर (err < 0)
		वापस err;

	चयन (data->phy_pattern) अणु
	हाल DP_PHY_TEST_PATTERN_80BIT_CUSTOM:
		err = drm_dp_dpcd_पढ़ो(aux, DP_TEST_80BIT_CUSTOM_PATTERN_7_0,
				       &data->custom80, माप(data->custom80));
		अगर (err < 0)
			वापस err;

		अवरोध;
	हाल DP_PHY_TEST_PATTERN_CP2520:
		err = drm_dp_dpcd_पढ़ो(aux, DP_TEST_HBR2_SCRAMBLER_RESET,
				       &data->hbr2_reset,
				       माप(data->hbr2_reset));
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_get_phy_test_pattern);

/**
 * drm_dp_set_phy_test_pattern() - set the pattern to the sink.
 * @aux: DisplayPort AUX channel
 * @data: DP phy compliance test parameters.
 * @dp_rev: DP revision to use क्रम compliance testing
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक drm_dp_set_phy_test_pattern(काष्ठा drm_dp_aux *aux,
				काष्ठा drm_dp_phy_test_params *data, u8 dp_rev)
अणु
	पूर्णांक err, i;
	u8 link_config[2];
	u8 test_pattern;

	link_config[0] = drm_dp_link_rate_to_bw_code(data->link_rate);
	link_config[1] = data->num_lanes;
	अगर (data->enhanced_frame_cap)
		link_config[1] |= DP_LANE_COUNT_ENHANCED_FRAME_EN;
	err = drm_dp_dpcd_ग_लिखो(aux, DP_LINK_BW_SET, link_config, 2);
	अगर (err < 0)
		वापस err;

	test_pattern = data->phy_pattern;
	अगर (dp_rev < 0x12) अणु
		test_pattern = (test_pattern << 2) &
			       DP_LINK_QUAL_PATTERN_11_MASK;
		err = drm_dp_dpcd_ग_लिखोb(aux, DP_TRAINING_PATTERN_SET,
					 test_pattern);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < data->num_lanes; i++) अणु
			err = drm_dp_dpcd_ग_लिखोb(aux,
						 DP_LINK_QUAL_LANE0_SET + i,
						 test_pattern);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_set_phy_test_pattern);

अटल स्थिर अक्षर *dp_pixelक्रमmat_get_name(क्रमागत dp_pixelक्रमmat pixelक्रमmat)
अणु
	अगर (pixelक्रमmat < 0 || pixelक्रमmat > DP_PIXELFORMAT_RESERVED)
		वापस "Invalid";

	चयन (pixelक्रमmat) अणु
	हाल DP_PIXELFORMAT_RGB:
		वापस "RGB";
	हाल DP_PIXELFORMAT_YUV444:
		वापस "YUV444";
	हाल DP_PIXELFORMAT_YUV422:
		वापस "YUV422";
	हाल DP_PIXELFORMAT_YUV420:
		वापस "YUV420";
	हाल DP_PIXELFORMAT_Y_ONLY:
		वापस "Y_ONLY";
	हाल DP_PIXELFORMAT_RAW:
		वापस "RAW";
	शेष:
		वापस "Reserved";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *dp_colorimetry_get_name(क्रमागत dp_pixelक्रमmat pixelक्रमmat,
					   क्रमागत dp_colorimetry colorimetry)
अणु
	अगर (pixelक्रमmat < 0 || pixelक्रमmat > DP_PIXELFORMAT_RESERVED)
		वापस "Invalid";

	चयन (colorimetry) अणु
	हाल DP_COLORIMETRY_DEFAULT:
		चयन (pixelक्रमmat) अणु
		हाल DP_PIXELFORMAT_RGB:
			वापस "sRGB";
		हाल DP_PIXELFORMAT_YUV444:
		हाल DP_PIXELFORMAT_YUV422:
		हाल DP_PIXELFORMAT_YUV420:
			वापस "BT.601";
		हाल DP_PIXELFORMAT_Y_ONLY:
			वापस "DICOM PS3.14";
		हाल DP_PIXELFORMAT_RAW:
			वापस "Custom Color Profile";
		शेष:
			वापस "Reserved";
		पूर्ण
	हाल DP_COLORIMETRY_RGB_WIDE_FIXED: /* and DP_COLORIMETRY_BT709_YCC */
		चयन (pixelक्रमmat) अणु
		हाल DP_PIXELFORMAT_RGB:
			वापस "Wide Fixed";
		हाल DP_PIXELFORMAT_YUV444:
		हाल DP_PIXELFORMAT_YUV422:
		हाल DP_PIXELFORMAT_YUV420:
			वापस "BT.709";
		शेष:
			वापस "Reserved";
		पूर्ण
	हाल DP_COLORIMETRY_RGB_WIDE_FLOAT: /* and DP_COLORIMETRY_XVYCC_601 */
		चयन (pixelक्रमmat) अणु
		हाल DP_PIXELFORMAT_RGB:
			वापस "Wide Float";
		हाल DP_PIXELFORMAT_YUV444:
		हाल DP_PIXELFORMAT_YUV422:
		हाल DP_PIXELFORMAT_YUV420:
			वापस "xvYCC 601";
		शेष:
			वापस "Reserved";
		पूर्ण
	हाल DP_COLORIMETRY_OPRGB: /* and DP_COLORIMETRY_XVYCC_709 */
		चयन (pixelक्रमmat) अणु
		हाल DP_PIXELFORMAT_RGB:
			वापस "OpRGB";
		हाल DP_PIXELFORMAT_YUV444:
		हाल DP_PIXELFORMAT_YUV422:
		हाल DP_PIXELFORMAT_YUV420:
			वापस "xvYCC 709";
		शेष:
			वापस "Reserved";
		पूर्ण
	हाल DP_COLORIMETRY_DCI_P3_RGB: /* and DP_COLORIMETRY_SYCC_601 */
		चयन (pixelक्रमmat) अणु
		हाल DP_PIXELFORMAT_RGB:
			वापस "DCI-P3";
		हाल DP_PIXELFORMAT_YUV444:
		हाल DP_PIXELFORMAT_YUV422:
		हाल DP_PIXELFORMAT_YUV420:
			वापस "sYCC 601";
		शेष:
			वापस "Reserved";
		पूर्ण
	हाल DP_COLORIMETRY_RGB_CUSTOM: /* and DP_COLORIMETRY_OPYCC_601 */
		चयन (pixelक्रमmat) अणु
		हाल DP_PIXELFORMAT_RGB:
			वापस "Custom Profile";
		हाल DP_PIXELFORMAT_YUV444:
		हाल DP_PIXELFORMAT_YUV422:
		हाल DP_PIXELFORMAT_YUV420:
			वापस "OpYCC 601";
		शेष:
			वापस "Reserved";
		पूर्ण
	हाल DP_COLORIMETRY_BT2020_RGB: /* and DP_COLORIMETRY_BT2020_CYCC */
		चयन (pixelक्रमmat) अणु
		हाल DP_PIXELFORMAT_RGB:
			वापस "BT.2020 RGB";
		हाल DP_PIXELFORMAT_YUV444:
		हाल DP_PIXELFORMAT_YUV422:
		हाल DP_PIXELFORMAT_YUV420:
			वापस "BT.2020 CYCC";
		शेष:
			वापस "Reserved";
		पूर्ण
	हाल DP_COLORIMETRY_BT2020_YCC:
		चयन (pixelक्रमmat) अणु
		हाल DP_PIXELFORMAT_YUV444:
		हाल DP_PIXELFORMAT_YUV422:
		हाल DP_PIXELFORMAT_YUV420:
			वापस "BT.2020 YCC";
		शेष:
			वापस "Reserved";
		पूर्ण
	शेष:
		वापस "Invalid";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *dp_dynamic_range_get_name(क्रमागत dp_dynamic_range dynamic_range)
अणु
	चयन (dynamic_range) अणु
	हाल DP_DYNAMIC_RANGE_VESA:
		वापस "VESA range";
	हाल DP_DYNAMIC_RANGE_CTA:
		वापस "CTA range";
	शेष:
		वापस "Invalid";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *dp_content_type_get_name(क्रमागत dp_content_type content_type)
अणु
	चयन (content_type) अणु
	हाल DP_CONTENT_TYPE_NOT_DEFINED:
		वापस "Not defined";
	हाल DP_CONTENT_TYPE_GRAPHICS:
		वापस "Graphics";
	हाल DP_CONTENT_TYPE_PHOTO:
		वापस "Photo";
	हाल DP_CONTENT_TYPE_VIDEO:
		वापस "Video";
	हाल DP_CONTENT_TYPE_GAME:
		वापस "Game";
	शेष:
		वापस "Reserved";
	पूर्ण
पूर्ण

व्योम drm_dp_vsc_sdp_log(स्थिर अक्षर *level, काष्ठा device *dev,
			स्थिर काष्ठा drm_dp_vsc_sdp *vsc)
अणु
#घोषणा DP_SDP_LOG(fmt, ...) dev_prपूर्णांकk(level, dev, fmt, ##__VA_ARGS__)
	DP_SDP_LOG("DP SDP: %s, revision %u, length %u\n", "VSC",
		   vsc->revision, vsc->length);
	DP_SDP_LOG("    pixelformat: %s\n",
		   dp_pixelक्रमmat_get_name(vsc->pixelक्रमmat));
	DP_SDP_LOG("    colorimetry: %s\n",
		   dp_colorimetry_get_name(vsc->pixelक्रमmat, vsc->colorimetry));
	DP_SDP_LOG("    bpc: %u\n", vsc->bpc);
	DP_SDP_LOG("    dynamic range: %s\n",
		   dp_dynamic_range_get_name(vsc->dynamic_range));
	DP_SDP_LOG("    content type: %s\n",
		   dp_content_type_get_name(vsc->content_type));
#अघोषित DP_SDP_LOG
पूर्ण
EXPORT_SYMBOL(drm_dp_vsc_sdp_log);

/**
 * drm_dp_get_pcon_max_frl_bw() - maximum frl supported by PCON
 * @dpcd: DisplayPort configuration data
 * @port_cap: port capabilities
 *
 * Returns maximum frl bandwidth supported by PCON in GBPS,
 * वापसs 0 अगर not supported.
 */
पूर्णांक drm_dp_get_pcon_max_frl_bw(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
			       स्थिर u8 port_cap[4])
अणु
	पूर्णांक bw;
	u8 buf;

	buf = port_cap[2];
	bw = buf & DP_PCON_MAX_FRL_BW;

	चयन (bw) अणु
	हाल DP_PCON_MAX_9GBPS:
		वापस 9;
	हाल DP_PCON_MAX_18GBPS:
		वापस 18;
	हाल DP_PCON_MAX_24GBPS:
		वापस 24;
	हाल DP_PCON_MAX_32GBPS:
		वापस 32;
	हाल DP_PCON_MAX_40GBPS:
		वापस 40;
	हाल DP_PCON_MAX_48GBPS:
		वापस 48;
	हाल DP_PCON_MAX_0GBPS:
	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_get_pcon_max_frl_bw);

/**
 * drm_dp_pcon_frl_prepare() - Prepare PCON क्रम FRL.
 * @aux: DisplayPort AUX channel
 * @enable_frl_पढ़ोy_hpd: Configure DP_PCON_ENABLE_HPD_READY.
 *
 * Returns 0 अगर success, अन्यथा वापसs negative error code.
 */
पूर्णांक drm_dp_pcon_frl_prepare(काष्ठा drm_dp_aux *aux, bool enable_frl_पढ़ोy_hpd)
अणु
	पूर्णांक ret;
	u8 buf = DP_PCON_ENABLE_SOURCE_CTL_MODE |
		 DP_PCON_ENABLE_LINK_FRL_MODE;

	अगर (enable_frl_पढ़ोy_hpd)
		buf |= DP_PCON_ENABLE_HPD_READY;

	ret = drm_dp_dpcd_ग_लिखोb(aux, DP_PCON_HDMI_LINK_CONFIG_1, buf);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_dp_pcon_frl_prepare);

/**
 * drm_dp_pcon_is_frl_पढ़ोy() - Is PCON पढ़ोy क्रम FRL
 * @aux: DisplayPort AUX channel
 *
 * Returns true अगर success, अन्यथा वापसs false.
 */
bool drm_dp_pcon_is_frl_पढ़ोy(काष्ठा drm_dp_aux *aux)
अणु
	पूर्णांक ret;
	u8 buf;

	ret = drm_dp_dpcd_पढ़ोb(aux, DP_PCON_HDMI_TX_LINK_STATUS, &buf);
	अगर (ret < 0)
		वापस false;

	अगर (buf & DP_PCON_FRL_READY)
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL(drm_dp_pcon_is_frl_पढ़ोy);

/**
 * drm_dp_pcon_frl_configure_1() - Set HDMI LINK Configuration-Step1
 * @aux: DisplayPort AUX channel
 * @max_frl_gbps: maximum frl bw to be configured between PCON and HDMI sink
 * @frl_mode: FRL Training mode, it can be either Concurrent or Sequential.
 * In Concurrent Mode, the FRL link bring up can be करोne aदीर्घ with
 * DP Link training. In Sequential mode, the FRL link bring up is करोne prior to
 * the DP Link training.
 *
 * Returns 0 अगर success, अन्यथा वापसs negative error code.
 */

पूर्णांक drm_dp_pcon_frl_configure_1(काष्ठा drm_dp_aux *aux, पूर्णांक max_frl_gbps,
				u8 frl_mode)
अणु
	पूर्णांक ret;
	u8 buf;

	ret = drm_dp_dpcd_पढ़ोb(aux, DP_PCON_HDMI_LINK_CONFIG_1, &buf);
	अगर (ret < 0)
		वापस ret;

	अगर (frl_mode == DP_PCON_ENABLE_CONCURRENT_LINK)
		buf |= DP_PCON_ENABLE_CONCURRENT_LINK;
	अन्यथा
		buf &= ~DP_PCON_ENABLE_CONCURRENT_LINK;

	चयन (max_frl_gbps) अणु
	हाल 9:
		buf |=  DP_PCON_ENABLE_MAX_BW_9GBPS;
		अवरोध;
	हाल 18:
		buf |=  DP_PCON_ENABLE_MAX_BW_18GBPS;
		अवरोध;
	हाल 24:
		buf |=  DP_PCON_ENABLE_MAX_BW_24GBPS;
		अवरोध;
	हाल 32:
		buf |=  DP_PCON_ENABLE_MAX_BW_32GBPS;
		अवरोध;
	हाल 40:
		buf |=  DP_PCON_ENABLE_MAX_BW_40GBPS;
		अवरोध;
	हाल 48:
		buf |=  DP_PCON_ENABLE_MAX_BW_48GBPS;
		अवरोध;
	हाल 0:
		buf |=  DP_PCON_ENABLE_MAX_BW_0GBPS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = drm_dp_dpcd_ग_लिखोb(aux, DP_PCON_HDMI_LINK_CONFIG_1, buf);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_pcon_frl_configure_1);

/**
 * drm_dp_pcon_frl_configure_2() - Set HDMI Link configuration Step-2
 * @aux: DisplayPort AUX channel
 * @max_frl_mask : Max FRL BW to be tried by the PCON with HDMI Sink
 * @frl_type : FRL training type, can be Extended, or Normal.
 * In Normal FRL training, the PCON tries each frl bw from the max_frl_mask
 * starting from min, and stops when link training is successful. In Extended
 * FRL training, all frl bw selected in the mask are trained by the PCON.
 *
 * Returns 0 अगर success, अन्यथा वापसs negative error code.
 */
पूर्णांक drm_dp_pcon_frl_configure_2(काष्ठा drm_dp_aux *aux, पूर्णांक max_frl_mask,
				u8 frl_type)
अणु
	पूर्णांक ret;
	u8 buf = max_frl_mask;

	अगर (frl_type == DP_PCON_FRL_LINK_TRAIN_EXTENDED)
		buf |= DP_PCON_FRL_LINK_TRAIN_EXTENDED;
	अन्यथा
		buf &= ~DP_PCON_FRL_LINK_TRAIN_EXTENDED;

	ret = drm_dp_dpcd_ग_लिखोb(aux, DP_PCON_HDMI_LINK_CONFIG_2, buf);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_pcon_frl_configure_2);

/**
 * drm_dp_pcon_reset_frl_config() - Re-Set HDMI Link configuration.
 * @aux: DisplayPort AUX channel
 *
 * Returns 0 अगर success, अन्यथा वापसs negative error code.
 */
पूर्णांक drm_dp_pcon_reset_frl_config(काष्ठा drm_dp_aux *aux)
अणु
	पूर्णांक ret;

	ret = drm_dp_dpcd_ग_लिखोb(aux, DP_PCON_HDMI_LINK_CONFIG_1, 0x0);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_pcon_reset_frl_config);

/**
 * drm_dp_pcon_frl_enable() - Enable HDMI link through FRL
 * @aux: DisplayPort AUX channel
 *
 * Returns 0 अगर success, अन्यथा वापसs negative error code.
 */
पूर्णांक drm_dp_pcon_frl_enable(काष्ठा drm_dp_aux *aux)
अणु
	पूर्णांक ret;
	u8 buf = 0;

	ret = drm_dp_dpcd_पढ़ोb(aux, DP_PCON_HDMI_LINK_CONFIG_1, &buf);
	अगर (ret < 0)
		वापस ret;
	अगर (!(buf & DP_PCON_ENABLE_SOURCE_CTL_MODE)) अणु
		DRM_DEBUG_KMS("PCON in Autonomous mode, can't enable FRL\n");
		वापस -EINVAL;
	पूर्ण
	buf |= DP_PCON_ENABLE_HDMI_LINK;
	ret = drm_dp_dpcd_ग_लिखोb(aux, DP_PCON_HDMI_LINK_CONFIG_1, buf);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_pcon_frl_enable);

/**
 * drm_dp_pcon_hdmi_link_active() - check अगर the PCON HDMI LINK status is active.
 * @aux: DisplayPort AUX channel
 *
 * Returns true अगर link is active अन्यथा वापसs false.
 */
bool drm_dp_pcon_hdmi_link_active(काष्ठा drm_dp_aux *aux)
अणु
	u8 buf;
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ोb(aux, DP_PCON_HDMI_TX_LINK_STATUS, &buf);
	अगर (ret < 0)
		वापस false;

	वापस buf & DP_PCON_HDMI_TX_LINK_ACTIVE;
पूर्ण
EXPORT_SYMBOL(drm_dp_pcon_hdmi_link_active);

/**
 * drm_dp_pcon_hdmi_link_mode() - get the PCON HDMI LINK MODE
 * @aux: DisplayPort AUX channel
 * @frl_trained_mask: poपूर्णांकer to store biपंचांगask of the trained bw configuration.
 * Valid only अगर the MODE वापसed is FRL. For Normal Link training mode
 * only 1 of the bits will be set, but in हाल of Extended mode, more than
 * one bits can be set.
 *
 * Returns the link mode : TMDS or FRL on success, अन्यथा वापसs negative error
 * code.
 */
पूर्णांक drm_dp_pcon_hdmi_link_mode(काष्ठा drm_dp_aux *aux, u8 *frl_trained_mask)
अणु
	u8 buf;
	पूर्णांक mode;
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ोb(aux, DP_PCON_HDMI_POST_FRL_STATUS, &buf);
	अगर (ret < 0)
		वापस ret;

	mode = buf & DP_PCON_HDMI_LINK_MODE;

	अगर (frl_trained_mask && DP_PCON_HDMI_MODE_FRL == mode)
		*frl_trained_mask = (buf & DP_PCON_HDMI_FRL_TRAINED_BW) >> 1;

	वापस mode;
पूर्ण
EXPORT_SYMBOL(drm_dp_pcon_hdmi_link_mode);

/**
 * drm_dp_pcon_hdmi_frl_link_error_count() - prपूर्णांक the error count per lane
 * during link failure between PCON and HDMI sink
 * @aux: DisplayPort AUX channel
 * @connector: DRM connector
 * code.
 **/

व्योम drm_dp_pcon_hdmi_frl_link_error_count(काष्ठा drm_dp_aux *aux,
					   काष्ठा drm_connector *connector)
अणु
	u8 buf, error_count;
	पूर्णांक i, num_error;
	काष्ठा drm_hdmi_info *hdmi = &connector->display_info.hdmi;

	क्रम (i = 0; i < hdmi->max_lanes; i++) अणु
		अगर (drm_dp_dpcd_पढ़ोb(aux, DP_PCON_HDMI_ERROR_STATUS_LN0 + i, &buf) < 0)
			वापस;

		error_count = buf & DP_PCON_HDMI_ERROR_COUNT_MASK;
		चयन (error_count) अणु
		हाल DP_PCON_HDMI_ERROR_COUNT_HUNDRED_PLUS:
			num_error = 100;
			अवरोध;
		हाल DP_PCON_HDMI_ERROR_COUNT_TEN_PLUS:
			num_error = 10;
			अवरोध;
		हाल DP_PCON_HDMI_ERROR_COUNT_THREE_PLUS:
			num_error = 3;
			अवरोध;
		शेष:
			num_error = 0;
		पूर्ण

		DRM_ERROR("More than %d errors since the last read for lane %d", num_error, i);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_dp_pcon_hdmi_frl_link_error_count);

/*
 * drm_dp_pcon_enc_is_dsc_1_2 - Does PCON Encoder supports DSC 1.2
 * @pcon_dsc_dpcd: DSC capabilities of the PCON DSC Encoder
 *
 * Returns true is PCON encoder is DSC 1.2 अन्यथा वापसs false.
 */
bool drm_dp_pcon_enc_is_dsc_1_2(स्थिर u8 pcon_dsc_dpcd[DP_PCON_DSC_ENCODER_CAP_SIZE])
अणु
	u8 buf;
	u8 major_v, minor_v;

	buf = pcon_dsc_dpcd[DP_PCON_DSC_VERSION - DP_PCON_DSC_ENCODER];
	major_v = (buf & DP_PCON_DSC_MAJOR_MASK) >> DP_PCON_DSC_MAJOR_SHIFT;
	minor_v = (buf & DP_PCON_DSC_MINOR_MASK) >> DP_PCON_DSC_MINOR_SHIFT;

	अगर (major_v == 1 && minor_v == 2)
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL(drm_dp_pcon_enc_is_dsc_1_2);

/*
 * drm_dp_pcon_dsc_max_slices - Get max slices supported by PCON DSC Encoder
 * @pcon_dsc_dpcd: DSC capabilities of the PCON DSC Encoder
 *
 * Returns maximum no. of slices supported by the PCON DSC Encoder.
 */
पूर्णांक drm_dp_pcon_dsc_max_slices(स्थिर u8 pcon_dsc_dpcd[DP_PCON_DSC_ENCODER_CAP_SIZE])
अणु
	u8 slice_cap1, slice_cap2;

	slice_cap1 = pcon_dsc_dpcd[DP_PCON_DSC_SLICE_CAP_1 - DP_PCON_DSC_ENCODER];
	slice_cap2 = pcon_dsc_dpcd[DP_PCON_DSC_SLICE_CAP_2 - DP_PCON_DSC_ENCODER];

	अगर (slice_cap2 & DP_PCON_DSC_24_PER_DSC_ENC)
		वापस 24;
	अगर (slice_cap2 & DP_PCON_DSC_20_PER_DSC_ENC)
		वापस 20;
	अगर (slice_cap2 & DP_PCON_DSC_16_PER_DSC_ENC)
		वापस 16;
	अगर (slice_cap1 & DP_PCON_DSC_12_PER_DSC_ENC)
		वापस 12;
	अगर (slice_cap1 & DP_PCON_DSC_10_PER_DSC_ENC)
		वापस 10;
	अगर (slice_cap1 & DP_PCON_DSC_8_PER_DSC_ENC)
		वापस 8;
	अगर (slice_cap1 & DP_PCON_DSC_6_PER_DSC_ENC)
		वापस 6;
	अगर (slice_cap1 & DP_PCON_DSC_4_PER_DSC_ENC)
		वापस 4;
	अगर (slice_cap1 & DP_PCON_DSC_2_PER_DSC_ENC)
		वापस 2;
	अगर (slice_cap1 & DP_PCON_DSC_1_PER_DSC_ENC)
		वापस 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_pcon_dsc_max_slices);

/*
 * drm_dp_pcon_dsc_max_slice_width() - Get max slice width क्रम Pcon DSC encoder
 * @pcon_dsc_dpcd: DSC capabilities of the PCON DSC Encoder
 *
 * Returns maximum width of the slices in pixel width i.e. no. of pixels x 320.
 */
पूर्णांक drm_dp_pcon_dsc_max_slice_width(स्थिर u8 pcon_dsc_dpcd[DP_PCON_DSC_ENCODER_CAP_SIZE])
अणु
	u8 buf;

	buf = pcon_dsc_dpcd[DP_PCON_DSC_MAX_SLICE_WIDTH - DP_PCON_DSC_ENCODER];

	वापस buf * DP_DSC_SLICE_WIDTH_MULTIPLIER;
पूर्ण
EXPORT_SYMBOL(drm_dp_pcon_dsc_max_slice_width);

/*
 * drm_dp_pcon_dsc_bpp_incr() - Get bits per pixel increment क्रम PCON DSC encoder
 * @pcon_dsc_dpcd: DSC capabilities of the PCON DSC Encoder
 *
 * Returns the bpp precision supported by the PCON encoder.
 */
पूर्णांक drm_dp_pcon_dsc_bpp_incr(स्थिर u8 pcon_dsc_dpcd[DP_PCON_DSC_ENCODER_CAP_SIZE])
अणु
	u8 buf;

	buf = pcon_dsc_dpcd[DP_PCON_DSC_BPP_INCR - DP_PCON_DSC_ENCODER];

	चयन (buf & DP_PCON_DSC_BPP_INCR_MASK) अणु
	हाल DP_PCON_DSC_ONE_16TH_BPP:
		वापस 16;
	हाल DP_PCON_DSC_ONE_8TH_BPP:
		वापस 8;
	हाल DP_PCON_DSC_ONE_4TH_BPP:
		वापस 4;
	हाल DP_PCON_DSC_ONE_HALF_BPP:
		वापस 2;
	हाल DP_PCON_DSC_ONE_BPP:
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_pcon_dsc_bpp_incr);

अटल
पूर्णांक drm_dp_pcon_configure_dsc_enc(काष्ठा drm_dp_aux *aux, u8 pps_buf_config)
अणु
	u8 buf;
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ोb(aux, DP_PROTOCOL_CONVERTER_CONTROL_2, &buf);
	अगर (ret < 0)
		वापस ret;

	buf |= DP_PCON_ENABLE_DSC_ENCODER;

	अगर (pps_buf_config <= DP_PCON_ENC_PPS_OVERRIDE_EN_BUFFER) अणु
		buf &= ~DP_PCON_ENCODER_PPS_OVERRIDE_MASK;
		buf |= pps_buf_config << 2;
	पूर्ण

	ret = drm_dp_dpcd_ग_लिखोb(aux, DP_PROTOCOL_CONVERTER_CONTROL_2, buf);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/**
 * drm_dp_pcon_pps_शेष() - Let PCON fill the शेष pps parameters
 * क्रम DSC1.2 between PCON & HDMI2.1 sink
 * @aux: DisplayPort AUX channel
 *
 * Returns 0 on success, अन्यथा वापसs negative error code.
 */
पूर्णांक drm_dp_pcon_pps_शेष(काष्ठा drm_dp_aux *aux)
अणु
	पूर्णांक ret;

	ret = drm_dp_pcon_configure_dsc_enc(aux, DP_PCON_ENC_PPS_OVERRIDE_DISABLED);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_pcon_pps_शेष);

/**
 * drm_dp_pcon_pps_override_buf() - Configure PPS encoder override buffer क्रम
 * HDMI sink
 * @aux: DisplayPort AUX channel
 * @pps_buf: 128 bytes to be written पूर्णांकo PPS buffer क्रम HDMI sink by PCON.
 *
 * Returns 0 on success, अन्यथा वापसs negative error code.
 */
पूर्णांक drm_dp_pcon_pps_override_buf(काष्ठा drm_dp_aux *aux, u8 pps_buf[128])
अणु
	पूर्णांक ret;

	ret = drm_dp_dpcd_ग_लिखो(aux, DP_PCON_HDMI_PPS_OVERRIDE_BASE, &pps_buf, 128);
	अगर (ret < 0)
		वापस ret;

	ret = drm_dp_pcon_configure_dsc_enc(aux, DP_PCON_ENC_PPS_OVERRIDE_EN_BUFFER);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_pcon_pps_override_buf);

/*
 * drm_dp_pcon_pps_override_param() - Write PPS parameters to DSC encoder
 * override रेजिस्टरs
 * @aux: DisplayPort AUX channel
 * @pps_param: 3 Parameters (2 Bytes each) : Slice Width, Slice Height,
 * bits_per_pixel.
 *
 * Returns 0 on success, अन्यथा वापसs negative error code.
 */
पूर्णांक drm_dp_pcon_pps_override_param(काष्ठा drm_dp_aux *aux, u8 pps_param[6])
अणु
	पूर्णांक ret;

	ret = drm_dp_dpcd_ग_लिखो(aux, DP_PCON_HDMI_PPS_OVRD_SLICE_HEIGHT, &pps_param[0], 2);
	अगर (ret < 0)
		वापस ret;
	ret = drm_dp_dpcd_ग_लिखो(aux, DP_PCON_HDMI_PPS_OVRD_SLICE_WIDTH, &pps_param[2], 2);
	अगर (ret < 0)
		वापस ret;
	ret = drm_dp_dpcd_ग_लिखो(aux, DP_PCON_HDMI_PPS_OVRD_BPP, &pps_param[4], 2);
	अगर (ret < 0)
		वापस ret;

	ret = drm_dp_pcon_configure_dsc_enc(aux, DP_PCON_ENC_PPS_OVERRIDE_EN_BUFFER);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_pcon_pps_override_param);

/*
 * drm_dp_pcon_convert_rgb_to_ycbcr() - Configure the PCon to convert RGB to Ycbcr
 * @aux: displayPort AUX channel
 * @color_spc: Color-space/s क्रम which conversion is to be enabled, 0 क्रम disable.
 *
 * Returns 0 on success, अन्यथा वापसs negative error code.
 */
पूर्णांक drm_dp_pcon_convert_rgb_to_ycbcr(काष्ठा drm_dp_aux *aux, u8 color_spc)
अणु
	पूर्णांक ret;
	u8 buf;

	ret = drm_dp_dpcd_पढ़ोb(aux, DP_PROTOCOL_CONVERTER_CONTROL_2, &buf);
	अगर (ret < 0)
		वापस ret;

	अगर (color_spc & DP_CONVERSION_RGB_YCBCR_MASK)
		buf |= (color_spc & DP_CONVERSION_RGB_YCBCR_MASK);
	अन्यथा
		buf &= ~DP_CONVERSION_RGB_YCBCR_MASK;

	ret = drm_dp_dpcd_ग_लिखोb(aux, DP_PROTOCOL_CONVERTER_CONTROL_2, buf);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_pcon_convert_rgb_to_ycbcr);
