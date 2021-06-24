<शैली गुरु>
/*
 * Copyright तऊ 2014 Red Hat
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

#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/iopoll.h>

#अगर IS_ENABLED(CONFIG_DRM_DEBUG_DP_MST_TOPOLOGY_REFS)
#समावेश <linux/stacktrace.h>
#समावेश <linux/sort.h>
#समावेश <linux/समयkeeping.h>
#समावेश <linux/math64.h>
#पूर्ण_अगर

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_dp_mst_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "drm_crtc_helper_internal.h"
#समावेश "drm_dp_mst_topology_internal.h"

/**
 * DOC: dp mst helper
 *
 * These functions contain parts of the DisplayPort 1.2a MultiStream Transport
 * protocol. The helpers contain a topology manager and bandwidth manager.
 * The helpers encapsulate the sending and received of sideband msgs.
 */
काष्ठा drm_dp_pending_up_req अणु
	काष्ठा drm_dp_sideband_msg_hdr hdr;
	काष्ठा drm_dp_sideband_msg_req_body msg;
	काष्ठा list_head next;
पूर्ण;

अटल bool dump_dp_payload_table(काष्ठा drm_dp_mst_topology_mgr *mgr,
				  अक्षर *buf);

अटल व्योम drm_dp_mst_topology_put_port(काष्ठा drm_dp_mst_port *port);

अटल पूर्णांक drm_dp_dpcd_ग_लिखो_payload(काष्ठा drm_dp_mst_topology_mgr *mgr,
				     पूर्णांक id,
				     काष्ठा drm_dp_payload *payload);

अटल पूर्णांक drm_dp_send_dpcd_पढ़ो(काष्ठा drm_dp_mst_topology_mgr *mgr,
				 काष्ठा drm_dp_mst_port *port,
				 पूर्णांक offset, पूर्णांक size, u8 *bytes);
अटल पूर्णांक drm_dp_send_dpcd_ग_लिखो(काष्ठा drm_dp_mst_topology_mgr *mgr,
				  काष्ठा drm_dp_mst_port *port,
				  पूर्णांक offset, पूर्णांक size, u8 *bytes);

अटल पूर्णांक drm_dp_send_link_address(काष्ठा drm_dp_mst_topology_mgr *mgr,
				    काष्ठा drm_dp_mst_branch *mstb);

अटल व्योम
drm_dp_send_clear_payload_id_table(काष्ठा drm_dp_mst_topology_mgr *mgr,
				   काष्ठा drm_dp_mst_branch *mstb);

अटल पूर्णांक drm_dp_send_क्रमागत_path_resources(काष्ठा drm_dp_mst_topology_mgr *mgr,
					   काष्ठा drm_dp_mst_branch *mstb,
					   काष्ठा drm_dp_mst_port *port);
अटल bool drm_dp_validate_guid(काष्ठा drm_dp_mst_topology_mgr *mgr,
				 u8 *guid);

अटल पूर्णांक drm_dp_mst_रेजिस्टर_i2c_bus(काष्ठा drm_dp_mst_port *port);
अटल व्योम drm_dp_mst_unरेजिस्टर_i2c_bus(काष्ठा drm_dp_mst_port *port);
अटल व्योम drm_dp_mst_kick_tx(काष्ठा drm_dp_mst_topology_mgr *mgr);

#घोषणा DBG_PREFIX "[dp_mst]"

#घोषणा DP_STR(x) [DP_ ## x] = #x

अटल स्थिर अक्षर *drm_dp_mst_req_type_str(u8 req_type)
अणु
	अटल स्थिर अक्षर * स्थिर req_type_str[] = अणु
		DP_STR(GET_MSG_TRANSACTION_VERSION),
		DP_STR(LINK_ADDRESS),
		DP_STR(CONNECTION_STATUS_NOTIFY),
		DP_STR(ENUM_PATH_RESOURCES),
		DP_STR(ALLOCATE_PAYLOAD),
		DP_STR(QUERY_PAYLOAD),
		DP_STR(RESOURCE_STATUS_NOTIFY),
		DP_STR(CLEAR_PAYLOAD_ID_TABLE),
		DP_STR(REMOTE_DPCD_READ),
		DP_STR(REMOTE_DPCD_WRITE),
		DP_STR(REMOTE_I2C_READ),
		DP_STR(REMOTE_I2C_WRITE),
		DP_STR(POWER_UP_PHY),
		DP_STR(POWER_DOWN_PHY),
		DP_STR(SINK_EVENT_NOTIFY),
		DP_STR(QUERY_STREAM_ENC_STATUS),
	पूर्ण;

	अगर (req_type >= ARRAY_SIZE(req_type_str) ||
	    !req_type_str[req_type])
		वापस "unknown";

	वापस req_type_str[req_type];
पूर्ण

#अघोषित DP_STR
#घोषणा DP_STR(x) [DP_NAK_ ## x] = #x

अटल स्थिर अक्षर *drm_dp_mst_nak_reason_str(u8 nak_reason)
अणु
	अटल स्थिर अक्षर * स्थिर nak_reason_str[] = अणु
		DP_STR(WRITE_FAILURE),
		DP_STR(INVALID_READ),
		DP_STR(CRC_FAILURE),
		DP_STR(BAD_PARAM),
		DP_STR(DEFER),
		DP_STR(LINK_FAILURE),
		DP_STR(NO_RESOURCES),
		DP_STR(DPCD_FAIL),
		DP_STR(I2C_NAK),
		DP_STR(ALLOCATE_FAIL),
	पूर्ण;

	अगर (nak_reason >= ARRAY_SIZE(nak_reason_str) ||
	    !nak_reason_str[nak_reason])
		वापस "unknown";

	वापस nak_reason_str[nak_reason];
पूर्ण

#अघोषित DP_STR
#घोषणा DP_STR(x) [DRM_DP_SIDEBAND_TX_ ## x] = #x

अटल स्थिर अक्षर *drm_dp_mst_sideband_tx_state_str(पूर्णांक state)
अणु
	अटल स्थिर अक्षर * स्थिर sideband_reason_str[] = अणु
		DP_STR(QUEUED),
		DP_STR(START_SEND),
		DP_STR(SENT),
		DP_STR(RX),
		DP_STR(TIMEOUT),
	पूर्ण;

	अगर (state >= ARRAY_SIZE(sideband_reason_str) ||
	    !sideband_reason_str[state])
		वापस "unknown";

	वापस sideband_reason_str[state];
पूर्ण

अटल पूर्णांक
drm_dp_mst_rad_to_str(स्थिर u8 rad[8], u8 lct, अक्षर *out, माप_प्रकार len)
अणु
	पूर्णांक i;
	u8 unpacked_rad[16];

	क्रम (i = 0; i < lct; i++) अणु
		अगर (i % 2)
			unpacked_rad[i] = rad[i / 2] >> 4;
		अन्यथा
			unpacked_rad[i] = rad[i / 2] & BIT_MASK(4);
	पूर्ण

	/* TODO: Eventually add something to prपूर्णांकk so we can क्रमmat the rad
	 * like this: 1.2.3
	 */
	वापस snम_लिखो(out, len, "%*phC", lct, unpacked_rad);
पूर्ण

/* sideband msg handling */
अटल u8 drm_dp_msg_header_crc4(स्थिर uपूर्णांक8_t *data, माप_प्रकार num_nibbles)
अणु
	u8 biपंचांगask = 0x80;
	u8 bitshअगरt = 7;
	u8 array_index = 0;
	पूर्णांक number_of_bits = num_nibbles * 4;
	u8 reमुख्यder = 0;

	जबतक (number_of_bits != 0) अणु
		number_of_bits--;
		reमुख्यder <<= 1;
		reमुख्यder |= (data[array_index] & biपंचांगask) >> bitshअगरt;
		biपंचांगask >>= 1;
		bitshअगरt--;
		अगर (biपंचांगask == 0) अणु
			biपंचांगask = 0x80;
			bitshअगरt = 7;
			array_index++;
		पूर्ण
		अगर ((reमुख्यder & 0x10) == 0x10)
			reमुख्यder ^= 0x13;
	पूर्ण

	number_of_bits = 4;
	जबतक (number_of_bits != 0) अणु
		number_of_bits--;
		reमुख्यder <<= 1;
		अगर ((reमुख्यder & 0x10) != 0)
			reमुख्यder ^= 0x13;
	पूर्ण

	वापस reमुख्यder;
पूर्ण

अटल u8 drm_dp_msg_data_crc4(स्थिर uपूर्णांक8_t *data, u8 number_of_bytes)
अणु
	u8 biपंचांगask = 0x80;
	u8 bitshअगरt = 7;
	u8 array_index = 0;
	पूर्णांक number_of_bits = number_of_bytes * 8;
	u16 reमुख्यder = 0;

	जबतक (number_of_bits != 0) अणु
		number_of_bits--;
		reमुख्यder <<= 1;
		reमुख्यder |= (data[array_index] & biपंचांगask) >> bitshअगरt;
		biपंचांगask >>= 1;
		bitshअगरt--;
		अगर (biपंचांगask == 0) अणु
			biपंचांगask = 0x80;
			bitshअगरt = 7;
			array_index++;
		पूर्ण
		अगर ((reमुख्यder & 0x100) == 0x100)
			reमुख्यder ^= 0xd5;
	पूर्ण

	number_of_bits = 8;
	जबतक (number_of_bits != 0) अणु
		number_of_bits--;
		reमुख्यder <<= 1;
		अगर ((reमुख्यder & 0x100) != 0)
			reमुख्यder ^= 0xd5;
	पूर्ण

	वापस reमुख्यder & 0xff;
पूर्ण
अटल अंतरभूत u8 drm_dp_calc_sb_hdr_size(काष्ठा drm_dp_sideband_msg_hdr *hdr)
अणु
	u8 size = 3;

	size += (hdr->lct / 2);
	वापस size;
पूर्ण

अटल व्योम drm_dp_encode_sideband_msg_hdr(काष्ठा drm_dp_sideband_msg_hdr *hdr,
					   u8 *buf, पूर्णांक *len)
अणु
	पूर्णांक idx = 0;
	पूर्णांक i;
	u8 crc4;

	buf[idx++] = ((hdr->lct & 0xf) << 4) | (hdr->lcr & 0xf);
	क्रम (i = 0; i < (hdr->lct / 2); i++)
		buf[idx++] = hdr->rad[i];
	buf[idx++] = (hdr->broadcast << 7) | (hdr->path_msg << 6) |
		(hdr->msg_len & 0x3f);
	buf[idx++] = (hdr->somt << 7) | (hdr->eomt << 6) | (hdr->seqno << 4);

	crc4 = drm_dp_msg_header_crc4(buf, (idx * 2) - 1);
	buf[idx - 1] |= (crc4 & 0xf);

	*len = idx;
पूर्ण

अटल bool drm_dp_decode_sideband_msg_hdr(काष्ठा drm_dp_sideband_msg_hdr *hdr,
					   u8 *buf, पूर्णांक buflen, u8 *hdrlen)
अणु
	u8 crc4;
	u8 len;
	पूर्णांक i;
	u8 idx;

	अगर (buf[0] == 0)
		वापस false;
	len = 3;
	len += ((buf[0] & 0xf0) >> 4) / 2;
	अगर (len > buflen)
		वापस false;
	crc4 = drm_dp_msg_header_crc4(buf, (len * 2) - 1);

	अगर ((crc4 & 0xf) != (buf[len - 1] & 0xf)) अणु
		DRM_DEBUG_KMS("crc4 mismatch 0x%x 0x%x\n", crc4, buf[len - 1]);
		वापस false;
	पूर्ण

	hdr->lct = (buf[0] & 0xf0) >> 4;
	hdr->lcr = (buf[0] & 0xf);
	idx = 1;
	क्रम (i = 0; i < (hdr->lct / 2); i++)
		hdr->rad[i] = buf[idx++];
	hdr->broadcast = (buf[idx] >> 7) & 0x1;
	hdr->path_msg = (buf[idx] >> 6) & 0x1;
	hdr->msg_len = buf[idx] & 0x3f;
	idx++;
	hdr->somt = (buf[idx] >> 7) & 0x1;
	hdr->eomt = (buf[idx] >> 6) & 0x1;
	hdr->seqno = (buf[idx] >> 4) & 0x1;
	idx++;
	*hdrlen = idx;
	वापस true;
पूर्ण

व्योम
drm_dp_encode_sideband_req(स्थिर काष्ठा drm_dp_sideband_msg_req_body *req,
			   काष्ठा drm_dp_sideband_msg_tx *raw)
अणु
	पूर्णांक idx = 0;
	पूर्णांक i;
	u8 *buf = raw->msg;

	buf[idx++] = req->req_type & 0x7f;

	चयन (req->req_type) अणु
	हाल DP_ENUM_PATH_RESOURCES:
	हाल DP_POWER_DOWN_PHY:
	हाल DP_POWER_UP_PHY:
		buf[idx] = (req->u.port_num.port_number & 0xf) << 4;
		idx++;
		अवरोध;
	हाल DP_ALLOCATE_PAYLOAD:
		buf[idx] = (req->u.allocate_payload.port_number & 0xf) << 4 |
			(req->u.allocate_payload.number_sdp_streams & 0xf);
		idx++;
		buf[idx] = (req->u.allocate_payload.vcpi & 0x7f);
		idx++;
		buf[idx] = (req->u.allocate_payload.pbn >> 8);
		idx++;
		buf[idx] = (req->u.allocate_payload.pbn & 0xff);
		idx++;
		क्रम (i = 0; i < req->u.allocate_payload.number_sdp_streams / 2; i++) अणु
			buf[idx] = ((req->u.allocate_payload.sdp_stream_sink[i * 2] & 0xf) << 4) |
				(req->u.allocate_payload.sdp_stream_sink[i * 2 + 1] & 0xf);
			idx++;
		पूर्ण
		अगर (req->u.allocate_payload.number_sdp_streams & 1) अणु
			i = req->u.allocate_payload.number_sdp_streams - 1;
			buf[idx] = (req->u.allocate_payload.sdp_stream_sink[i] & 0xf) << 4;
			idx++;
		पूर्ण
		अवरोध;
	हाल DP_QUERY_PAYLOAD:
		buf[idx] = (req->u.query_payload.port_number & 0xf) << 4;
		idx++;
		buf[idx] = (req->u.query_payload.vcpi & 0x7f);
		idx++;
		अवरोध;
	हाल DP_REMOTE_DPCD_READ:
		buf[idx] = (req->u.dpcd_पढ़ो.port_number & 0xf) << 4;
		buf[idx] |= ((req->u.dpcd_पढ़ो.dpcd_address & 0xf0000) >> 16) & 0xf;
		idx++;
		buf[idx] = (req->u.dpcd_पढ़ो.dpcd_address & 0xff00) >> 8;
		idx++;
		buf[idx] = (req->u.dpcd_पढ़ो.dpcd_address & 0xff);
		idx++;
		buf[idx] = (req->u.dpcd_पढ़ो.num_bytes);
		idx++;
		अवरोध;

	हाल DP_REMOTE_DPCD_WRITE:
		buf[idx] = (req->u.dpcd_ग_लिखो.port_number & 0xf) << 4;
		buf[idx] |= ((req->u.dpcd_ग_लिखो.dpcd_address & 0xf0000) >> 16) & 0xf;
		idx++;
		buf[idx] = (req->u.dpcd_ग_लिखो.dpcd_address & 0xff00) >> 8;
		idx++;
		buf[idx] = (req->u.dpcd_ग_लिखो.dpcd_address & 0xff);
		idx++;
		buf[idx] = (req->u.dpcd_ग_लिखो.num_bytes);
		idx++;
		स_नकल(&buf[idx], req->u.dpcd_ग_लिखो.bytes, req->u.dpcd_ग_लिखो.num_bytes);
		idx += req->u.dpcd_ग_लिखो.num_bytes;
		अवरोध;
	हाल DP_REMOTE_I2C_READ:
		buf[idx] = (req->u.i2c_पढ़ो.port_number & 0xf) << 4;
		buf[idx] |= (req->u.i2c_पढ़ो.num_transactions & 0x3);
		idx++;
		क्रम (i = 0; i < (req->u.i2c_पढ़ो.num_transactions & 0x3); i++) अणु
			buf[idx] = req->u.i2c_पढ़ो.transactions[i].i2c_dev_id & 0x7f;
			idx++;
			buf[idx] = req->u.i2c_पढ़ो.transactions[i].num_bytes;
			idx++;
			स_नकल(&buf[idx], req->u.i2c_पढ़ो.transactions[i].bytes, req->u.i2c_पढ़ो.transactions[i].num_bytes);
			idx += req->u.i2c_पढ़ो.transactions[i].num_bytes;

			buf[idx] = (req->u.i2c_पढ़ो.transactions[i].no_stop_bit & 0x1) << 4;
			buf[idx] |= (req->u.i2c_पढ़ो.transactions[i].i2c_transaction_delay & 0xf);
			idx++;
		पूर्ण
		buf[idx] = (req->u.i2c_पढ़ो.पढ़ो_i2c_device_id) & 0x7f;
		idx++;
		buf[idx] = (req->u.i2c_पढ़ो.num_bytes_पढ़ो);
		idx++;
		अवरोध;

	हाल DP_REMOTE_I2C_WRITE:
		buf[idx] = (req->u.i2c_ग_लिखो.port_number & 0xf) << 4;
		idx++;
		buf[idx] = (req->u.i2c_ग_लिखो.ग_लिखो_i2c_device_id) & 0x7f;
		idx++;
		buf[idx] = (req->u.i2c_ग_लिखो.num_bytes);
		idx++;
		स_नकल(&buf[idx], req->u.i2c_ग_लिखो.bytes, req->u.i2c_ग_लिखो.num_bytes);
		idx += req->u.i2c_ग_लिखो.num_bytes;
		अवरोध;
	हाल DP_QUERY_STREAM_ENC_STATUS: अणु
		स्थिर काष्ठा drm_dp_query_stream_enc_status *msg;

		msg = &req->u.enc_status;
		buf[idx] = msg->stream_id;
		idx++;
		स_नकल(&buf[idx], msg->client_id, माप(msg->client_id));
		idx += माप(msg->client_id);
		buf[idx] = 0;
		buf[idx] |= FIELD_PREP(GENMASK(1, 0), msg->stream_event);
		buf[idx] |= msg->valid_stream_event ? BIT(2) : 0;
		buf[idx] |= FIELD_PREP(GENMASK(4, 3), msg->stream_behavior);
		buf[idx] |= msg->valid_stream_behavior ? BIT(5) : 0;
		idx++;
		पूर्ण
		अवरोध;
	पूर्ण
	raw->cur_len = idx;
पूर्ण
EXPORT_SYMBOL_FOR_TESTS_ONLY(drm_dp_encode_sideband_req);

/* Decode a sideband request we've encoded, मुख्यly used क्रम debugging */
पूर्णांक
drm_dp_decode_sideband_req(स्थिर काष्ठा drm_dp_sideband_msg_tx *raw,
			   काष्ठा drm_dp_sideband_msg_req_body *req)
अणु
	स्थिर u8 *buf = raw->msg;
	पूर्णांक i, idx = 0;

	req->req_type = buf[idx++] & 0x7f;
	चयन (req->req_type) अणु
	हाल DP_ENUM_PATH_RESOURCES:
	हाल DP_POWER_DOWN_PHY:
	हाल DP_POWER_UP_PHY:
		req->u.port_num.port_number = (buf[idx] >> 4) & 0xf;
		अवरोध;
	हाल DP_ALLOCATE_PAYLOAD:
		अणु
			काष्ठा drm_dp_allocate_payload *a =
				&req->u.allocate_payload;

			a->number_sdp_streams = buf[idx] & 0xf;
			a->port_number = (buf[idx] >> 4) & 0xf;

			WARN_ON(buf[++idx] & 0x80);
			a->vcpi = buf[idx] & 0x7f;

			a->pbn = buf[++idx] << 8;
			a->pbn |= buf[++idx];

			idx++;
			क्रम (i = 0; i < a->number_sdp_streams; i++) अणु
				a->sdp_stream_sink[i] =
					(buf[idx + (i / 2)] >> ((i % 2) ? 0 : 4)) & 0xf;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल DP_QUERY_PAYLOAD:
		req->u.query_payload.port_number = (buf[idx] >> 4) & 0xf;
		WARN_ON(buf[++idx] & 0x80);
		req->u.query_payload.vcpi = buf[idx] & 0x7f;
		अवरोध;
	हाल DP_REMOTE_DPCD_READ:
		अणु
			काष्ठा drm_dp_remote_dpcd_पढ़ो *r = &req->u.dpcd_पढ़ो;

			r->port_number = (buf[idx] >> 4) & 0xf;

			r->dpcd_address = (buf[idx] << 16) & 0xf0000;
			r->dpcd_address |= (buf[++idx] << 8) & 0xff00;
			r->dpcd_address |= buf[++idx] & 0xff;

			r->num_bytes = buf[++idx];
		पूर्ण
		अवरोध;
	हाल DP_REMOTE_DPCD_WRITE:
		अणु
			काष्ठा drm_dp_remote_dpcd_ग_लिखो *w =
				&req->u.dpcd_ग_लिखो;

			w->port_number = (buf[idx] >> 4) & 0xf;

			w->dpcd_address = (buf[idx] << 16) & 0xf0000;
			w->dpcd_address |= (buf[++idx] << 8) & 0xff00;
			w->dpcd_address |= buf[++idx] & 0xff;

			w->num_bytes = buf[++idx];

			w->bytes = kmemdup(&buf[++idx], w->num_bytes,
					   GFP_KERNEL);
			अगर (!w->bytes)
				वापस -ENOMEM;
		पूर्ण
		अवरोध;
	हाल DP_REMOTE_I2C_READ:
		अणु
			काष्ठा drm_dp_remote_i2c_पढ़ो *r = &req->u.i2c_पढ़ो;
			काष्ठा drm_dp_remote_i2c_पढ़ो_tx *tx;
			bool failed = false;

			r->num_transactions = buf[idx] & 0x3;
			r->port_number = (buf[idx] >> 4) & 0xf;
			क्रम (i = 0; i < r->num_transactions; i++) अणु
				tx = &r->transactions[i];

				tx->i2c_dev_id = buf[++idx] & 0x7f;
				tx->num_bytes = buf[++idx];
				tx->bytes = kmemdup(&buf[++idx],
						    tx->num_bytes,
						    GFP_KERNEL);
				अगर (!tx->bytes) अणु
					failed = true;
					अवरोध;
				पूर्ण
				idx += tx->num_bytes;
				tx->no_stop_bit = (buf[idx] >> 5) & 0x1;
				tx->i2c_transaction_delay = buf[idx] & 0xf;
			पूर्ण

			अगर (failed) अणु
				क्रम (i = 0; i < r->num_transactions; i++) अणु
					tx = &r->transactions[i];
					kमुक्त(tx->bytes);
				पूर्ण
				वापस -ENOMEM;
			पूर्ण

			r->पढ़ो_i2c_device_id = buf[++idx] & 0x7f;
			r->num_bytes_पढ़ो = buf[++idx];
		पूर्ण
		अवरोध;
	हाल DP_REMOTE_I2C_WRITE:
		अणु
			काष्ठा drm_dp_remote_i2c_ग_लिखो *w = &req->u.i2c_ग_लिखो;

			w->port_number = (buf[idx] >> 4) & 0xf;
			w->ग_लिखो_i2c_device_id = buf[++idx] & 0x7f;
			w->num_bytes = buf[++idx];
			w->bytes = kmemdup(&buf[++idx], w->num_bytes,
					   GFP_KERNEL);
			अगर (!w->bytes)
				वापस -ENOMEM;
		पूर्ण
		अवरोध;
	हाल DP_QUERY_STREAM_ENC_STATUS:
		req->u.enc_status.stream_id = buf[idx++];
		क्रम (i = 0; i < माप(req->u.enc_status.client_id); i++)
			req->u.enc_status.client_id[i] = buf[idx++];

		req->u.enc_status.stream_event = FIELD_GET(GENMASK(1, 0),
							   buf[idx]);
		req->u.enc_status.valid_stream_event = FIELD_GET(BIT(2),
								 buf[idx]);
		req->u.enc_status.stream_behavior = FIELD_GET(GENMASK(4, 3),
							      buf[idx]);
		req->u.enc_status.valid_stream_behavior = FIELD_GET(BIT(5),
								    buf[idx]);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_FOR_TESTS_ONLY(drm_dp_decode_sideband_req);

व्योम
drm_dp_dump_sideband_msg_req_body(स्थिर काष्ठा drm_dp_sideband_msg_req_body *req,
				  पूर्णांक indent, काष्ठा drm_prपूर्णांकer *prपूर्णांकer)
अणु
	पूर्णांक i;

#घोषणा P(f, ...) drm_म_लिखो_indent(prपूर्णांकer, indent, f, ##__VA_ARGS__)
	अगर (req->req_type == DP_LINK_ADDRESS) अणु
		/* No contents to prपूर्णांक */
		P("type=%s\n", drm_dp_mst_req_type_str(req->req_type));
		वापस;
	पूर्ण

	P("type=%s contents:\n", drm_dp_mst_req_type_str(req->req_type));
	indent++;

	चयन (req->req_type) अणु
	हाल DP_ENUM_PATH_RESOURCES:
	हाल DP_POWER_DOWN_PHY:
	हाल DP_POWER_UP_PHY:
		P("port=%d\n", req->u.port_num.port_number);
		अवरोध;
	हाल DP_ALLOCATE_PAYLOAD:
		P("port=%d vcpi=%d pbn=%d sdp_streams=%d %*ph\n",
		  req->u.allocate_payload.port_number,
		  req->u.allocate_payload.vcpi, req->u.allocate_payload.pbn,
		  req->u.allocate_payload.number_sdp_streams,
		  req->u.allocate_payload.number_sdp_streams,
		  req->u.allocate_payload.sdp_stream_sink);
		अवरोध;
	हाल DP_QUERY_PAYLOAD:
		P("port=%d vcpi=%d\n",
		  req->u.query_payload.port_number,
		  req->u.query_payload.vcpi);
		अवरोध;
	हाल DP_REMOTE_DPCD_READ:
		P("port=%d dpcd_addr=%05x len=%d\n",
		  req->u.dpcd_पढ़ो.port_number, req->u.dpcd_पढ़ो.dpcd_address,
		  req->u.dpcd_पढ़ो.num_bytes);
		अवरोध;
	हाल DP_REMOTE_DPCD_WRITE:
		P("port=%d addr=%05x len=%d: %*ph\n",
		  req->u.dpcd_ग_लिखो.port_number,
		  req->u.dpcd_ग_लिखो.dpcd_address,
		  req->u.dpcd_ग_लिखो.num_bytes, req->u.dpcd_ग_लिखो.num_bytes,
		  req->u.dpcd_ग_लिखो.bytes);
		अवरोध;
	हाल DP_REMOTE_I2C_READ:
		P("port=%d num_tx=%d id=%d size=%d:\n",
		  req->u.i2c_पढ़ो.port_number,
		  req->u.i2c_पढ़ो.num_transactions,
		  req->u.i2c_पढ़ो.पढ़ो_i2c_device_id,
		  req->u.i2c_पढ़ो.num_bytes_पढ़ो);

		indent++;
		क्रम (i = 0; i < req->u.i2c_पढ़ो.num_transactions; i++) अणु
			स्थिर काष्ठा drm_dp_remote_i2c_पढ़ो_tx *rtx =
				&req->u.i2c_पढ़ो.transactions[i];

			P("%d: id=%03d size=%03d no_stop_bit=%d tx_delay=%03d: %*ph\n",
			  i, rtx->i2c_dev_id, rtx->num_bytes,
			  rtx->no_stop_bit, rtx->i2c_transaction_delay,
			  rtx->num_bytes, rtx->bytes);
		पूर्ण
		अवरोध;
	हाल DP_REMOTE_I2C_WRITE:
		P("port=%d id=%d size=%d: %*ph\n",
		  req->u.i2c_ग_लिखो.port_number,
		  req->u.i2c_ग_लिखो.ग_लिखो_i2c_device_id,
		  req->u.i2c_ग_लिखो.num_bytes, req->u.i2c_ग_लिखो.num_bytes,
		  req->u.i2c_ग_लिखो.bytes);
		अवरोध;
	हाल DP_QUERY_STREAM_ENC_STATUS:
		P("stream_id=%u client_id=%*ph stream_event=%x "
		  "valid_event=%d stream_behavior=%x valid_behavior=%d",
		  req->u.enc_status.stream_id,
		  (पूर्णांक)ARRAY_SIZE(req->u.enc_status.client_id),
		  req->u.enc_status.client_id, req->u.enc_status.stream_event,
		  req->u.enc_status.valid_stream_event,
		  req->u.enc_status.stream_behavior,
		  req->u.enc_status.valid_stream_behavior);
		अवरोध;
	शेष:
		P("???\n");
		अवरोध;
	पूर्ण
#अघोषित P
पूर्ण
EXPORT_SYMBOL_FOR_TESTS_ONLY(drm_dp_dump_sideband_msg_req_body);

अटल अंतरभूत व्योम
drm_dp_mst_dump_sideband_msg_tx(काष्ठा drm_prपूर्णांकer *p,
				स्थिर काष्ठा drm_dp_sideband_msg_tx *txmsg)
अणु
	काष्ठा drm_dp_sideband_msg_req_body req;
	अक्षर buf[64];
	पूर्णांक ret;
	पूर्णांक i;

	drm_dp_mst_rad_to_str(txmsg->dst->rad, txmsg->dst->lct, buf,
			      माप(buf));
	drm_म_लिखो(p, "txmsg cur_offset=%x cur_len=%x seqno=%x state=%s path_msg=%d dst=%s\n",
		   txmsg->cur_offset, txmsg->cur_len, txmsg->seqno,
		   drm_dp_mst_sideband_tx_state_str(txmsg->state),
		   txmsg->path_msg, buf);

	ret = drm_dp_decode_sideband_req(txmsg, &req);
	अगर (ret) अणु
		drm_म_लिखो(p, "<failed to decode sideband req: %d>\n", ret);
		वापस;
	पूर्ण
	drm_dp_dump_sideband_msg_req_body(&req, 1, p);

	चयन (req.req_type) अणु
	हाल DP_REMOTE_DPCD_WRITE:
		kमुक्त(req.u.dpcd_ग_लिखो.bytes);
		अवरोध;
	हाल DP_REMOTE_I2C_READ:
		क्रम (i = 0; i < req.u.i2c_पढ़ो.num_transactions; i++)
			kमुक्त(req.u.i2c_पढ़ो.transactions[i].bytes);
		अवरोध;
	हाल DP_REMOTE_I2C_WRITE:
		kमुक्त(req.u.i2c_ग_लिखो.bytes);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम drm_dp_crc_sideband_chunk_req(u8 *msg, u8 len)
अणु
	u8 crc4;

	crc4 = drm_dp_msg_data_crc4(msg, len);
	msg[len] = crc4;
पूर्ण

अटल व्योम drm_dp_encode_sideband_reply(काष्ठा drm_dp_sideband_msg_reply_body *rep,
					 काष्ठा drm_dp_sideband_msg_tx *raw)
अणु
	पूर्णांक idx = 0;
	u8 *buf = raw->msg;

	buf[idx++] = (rep->reply_type & 0x1) << 7 | (rep->req_type & 0x7f);

	raw->cur_len = idx;
पूर्ण

अटल पूर्णांक drm_dp_sideband_msg_set_header(काष्ठा drm_dp_sideband_msg_rx *msg,
					  काष्ठा drm_dp_sideband_msg_hdr *hdr,
					  u8 hdrlen)
अणु
	/*
	 * ignore out-of-order messages or messages that are part of a
	 * failed transaction
	 */
	अगर (!hdr->somt && !msg->have_somt)
		वापस false;

	/* get length contained in this portion */
	msg->curchunk_idx = 0;
	msg->curchunk_len = hdr->msg_len;
	msg->curchunk_hdrlen = hdrlen;

	/* we have alपढ़ोy gotten an somt - करोn't bother parsing */
	अगर (hdr->somt && msg->have_somt)
		वापस false;

	अगर (hdr->somt) अणु
		स_नकल(&msg->initial_hdr, hdr,
		       माप(काष्ठा drm_dp_sideband_msg_hdr));
		msg->have_somt = true;
	पूर्ण
	अगर (hdr->eomt)
		msg->have_eomt = true;

	वापस true;
पूर्ण

/* this adds a chunk of msg to the builder to get the final msg */
अटल bool drm_dp_sideband_append_payload(काष्ठा drm_dp_sideband_msg_rx *msg,
					   u8 *replybuf, u8 replybuflen)
अणु
	u8 crc4;

	स_नकल(&msg->chunk[msg->curchunk_idx], replybuf, replybuflen);
	msg->curchunk_idx += replybuflen;

	अगर (msg->curchunk_idx >= msg->curchunk_len) अणु
		/* करो CRC */
		crc4 = drm_dp_msg_data_crc4(msg->chunk, msg->curchunk_len - 1);
		अगर (crc4 != msg->chunk[msg->curchunk_len - 1])
			prपूर्णांक_hex_dump(KERN_DEBUG, "wrong crc",
				       DUMP_PREFIX_NONE, 16, 1,
				       msg->chunk,  msg->curchunk_len, false);
		/* copy chunk पूर्णांकo bigger msg */
		स_नकल(&msg->msg[msg->curlen], msg->chunk, msg->curchunk_len - 1);
		msg->curlen += msg->curchunk_len - 1;
	पूर्ण
	वापस true;
पूर्ण

अटल bool drm_dp_sideband_parse_link_address(काष्ठा drm_dp_sideband_msg_rx *raw,
					       काष्ठा drm_dp_sideband_msg_reply_body *repmsg)
अणु
	पूर्णांक idx = 1;
	पूर्णांक i;

	स_नकल(repmsg->u.link_addr.guid, &raw->msg[idx], 16);
	idx += 16;
	repmsg->u.link_addr.nports = raw->msg[idx] & 0xf;
	idx++;
	अगर (idx > raw->curlen)
		जाओ fail_len;
	क्रम (i = 0; i < repmsg->u.link_addr.nports; i++) अणु
		अगर (raw->msg[idx] & 0x80)
			repmsg->u.link_addr.ports[i].input_port = 1;

		repmsg->u.link_addr.ports[i].peer_device_type = (raw->msg[idx] >> 4) & 0x7;
		repmsg->u.link_addr.ports[i].port_number = (raw->msg[idx] & 0xf);

		idx++;
		अगर (idx > raw->curlen)
			जाओ fail_len;
		repmsg->u.link_addr.ports[i].mcs = (raw->msg[idx] >> 7) & 0x1;
		repmsg->u.link_addr.ports[i].ddps = (raw->msg[idx] >> 6) & 0x1;
		अगर (repmsg->u.link_addr.ports[i].input_port == 0)
			repmsg->u.link_addr.ports[i].legacy_device_plug_status = (raw->msg[idx] >> 5) & 0x1;
		idx++;
		अगर (idx > raw->curlen)
			जाओ fail_len;
		अगर (repmsg->u.link_addr.ports[i].input_port == 0) अणु
			repmsg->u.link_addr.ports[i].dpcd_revision = (raw->msg[idx]);
			idx++;
			अगर (idx > raw->curlen)
				जाओ fail_len;
			स_नकल(repmsg->u.link_addr.ports[i].peer_guid, &raw->msg[idx], 16);
			idx += 16;
			अगर (idx > raw->curlen)
				जाओ fail_len;
			repmsg->u.link_addr.ports[i].num_sdp_streams = (raw->msg[idx] >> 4) & 0xf;
			repmsg->u.link_addr.ports[i].num_sdp_stream_sinks = (raw->msg[idx] & 0xf);
			idx++;

		पूर्ण
		अगर (idx > raw->curlen)
			जाओ fail_len;
	पूर्ण

	वापस true;
fail_len:
	DRM_DEBUG_KMS("link address reply parse length fail %d %d\n", idx, raw->curlen);
	वापस false;
पूर्ण

अटल bool drm_dp_sideband_parse_remote_dpcd_पढ़ो(काष्ठा drm_dp_sideband_msg_rx *raw,
						   काष्ठा drm_dp_sideband_msg_reply_body *repmsg)
अणु
	पूर्णांक idx = 1;

	repmsg->u.remote_dpcd_पढ़ो_ack.port_number = raw->msg[idx] & 0xf;
	idx++;
	अगर (idx > raw->curlen)
		जाओ fail_len;
	repmsg->u.remote_dpcd_पढ़ो_ack.num_bytes = raw->msg[idx];
	idx++;
	अगर (idx > raw->curlen)
		जाओ fail_len;

	स_नकल(repmsg->u.remote_dpcd_पढ़ो_ack.bytes, &raw->msg[idx], repmsg->u.remote_dpcd_पढ़ो_ack.num_bytes);
	वापस true;
fail_len:
	DRM_DEBUG_KMS("link address reply parse length fail %d %d\n", idx, raw->curlen);
	वापस false;
पूर्ण

अटल bool drm_dp_sideband_parse_remote_dpcd_ग_लिखो(काष्ठा drm_dp_sideband_msg_rx *raw,
						      काष्ठा drm_dp_sideband_msg_reply_body *repmsg)
अणु
	पूर्णांक idx = 1;

	repmsg->u.remote_dpcd_ग_लिखो_ack.port_number = raw->msg[idx] & 0xf;
	idx++;
	अगर (idx > raw->curlen)
		जाओ fail_len;
	वापस true;
fail_len:
	DRM_DEBUG_KMS("parse length fail %d %d\n", idx, raw->curlen);
	वापस false;
पूर्ण

अटल bool drm_dp_sideband_parse_remote_i2c_पढ़ो_ack(काष्ठा drm_dp_sideband_msg_rx *raw,
						      काष्ठा drm_dp_sideband_msg_reply_body *repmsg)
अणु
	पूर्णांक idx = 1;

	repmsg->u.remote_i2c_पढ़ो_ack.port_number = (raw->msg[idx] & 0xf);
	idx++;
	अगर (idx > raw->curlen)
		जाओ fail_len;
	repmsg->u.remote_i2c_पढ़ो_ack.num_bytes = raw->msg[idx];
	idx++;
	/* TODO check */
	स_नकल(repmsg->u.remote_i2c_पढ़ो_ack.bytes, &raw->msg[idx], repmsg->u.remote_i2c_पढ़ो_ack.num_bytes);
	वापस true;
fail_len:
	DRM_DEBUG_KMS("remote i2c reply parse length fail %d %d\n", idx, raw->curlen);
	वापस false;
पूर्ण

अटल bool drm_dp_sideband_parse_क्रमागत_path_resources_ack(काष्ठा drm_dp_sideband_msg_rx *raw,
							  काष्ठा drm_dp_sideband_msg_reply_body *repmsg)
अणु
	पूर्णांक idx = 1;

	repmsg->u.path_resources.port_number = (raw->msg[idx] >> 4) & 0xf;
	repmsg->u.path_resources.fec_capable = raw->msg[idx] & 0x1;
	idx++;
	अगर (idx > raw->curlen)
		जाओ fail_len;
	repmsg->u.path_resources.full_payload_bw_number = (raw->msg[idx] << 8) | (raw->msg[idx+1]);
	idx += 2;
	अगर (idx > raw->curlen)
		जाओ fail_len;
	repmsg->u.path_resources.avail_payload_bw_number = (raw->msg[idx] << 8) | (raw->msg[idx+1]);
	idx += 2;
	अगर (idx > raw->curlen)
		जाओ fail_len;
	वापस true;
fail_len:
	DRM_DEBUG_KMS("enum resource parse length fail %d %d\n", idx, raw->curlen);
	वापस false;
पूर्ण

अटल bool drm_dp_sideband_parse_allocate_payload_ack(काष्ठा drm_dp_sideband_msg_rx *raw,
							  काष्ठा drm_dp_sideband_msg_reply_body *repmsg)
अणु
	पूर्णांक idx = 1;

	repmsg->u.allocate_payload.port_number = (raw->msg[idx] >> 4) & 0xf;
	idx++;
	अगर (idx > raw->curlen)
		जाओ fail_len;
	repmsg->u.allocate_payload.vcpi = raw->msg[idx];
	idx++;
	अगर (idx > raw->curlen)
		जाओ fail_len;
	repmsg->u.allocate_payload.allocated_pbn = (raw->msg[idx] << 8) | (raw->msg[idx+1]);
	idx += 2;
	अगर (idx > raw->curlen)
		जाओ fail_len;
	वापस true;
fail_len:
	DRM_DEBUG_KMS("allocate payload parse length fail %d %d\n", idx, raw->curlen);
	वापस false;
पूर्ण

अटल bool drm_dp_sideband_parse_query_payload_ack(काष्ठा drm_dp_sideband_msg_rx *raw,
						    काष्ठा drm_dp_sideband_msg_reply_body *repmsg)
अणु
	पूर्णांक idx = 1;

	repmsg->u.query_payload.port_number = (raw->msg[idx] >> 4) & 0xf;
	idx++;
	अगर (idx > raw->curlen)
		जाओ fail_len;
	repmsg->u.query_payload.allocated_pbn = (raw->msg[idx] << 8) | (raw->msg[idx + 1]);
	idx += 2;
	अगर (idx > raw->curlen)
		जाओ fail_len;
	वापस true;
fail_len:
	DRM_DEBUG_KMS("query payload parse length fail %d %d\n", idx, raw->curlen);
	वापस false;
पूर्ण

अटल bool drm_dp_sideband_parse_घातer_upकरोwn_phy_ack(काष्ठा drm_dp_sideband_msg_rx *raw,
						       काष्ठा drm_dp_sideband_msg_reply_body *repmsg)
अणु
	पूर्णांक idx = 1;

	repmsg->u.port_number.port_number = (raw->msg[idx] >> 4) & 0xf;
	idx++;
	अगर (idx > raw->curlen) अणु
		DRM_DEBUG_KMS("power up/down phy parse length fail %d %d\n",
			      idx, raw->curlen);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool
drm_dp_sideband_parse_query_stream_enc_status(
				काष्ठा drm_dp_sideband_msg_rx *raw,
				काष्ठा drm_dp_sideband_msg_reply_body *repmsg)
अणु
	काष्ठा drm_dp_query_stream_enc_status_ack_reply *reply;

	reply = &repmsg->u.enc_status;

	reply->stream_id = raw->msg[3];

	reply->reply_चिन्हित = raw->msg[2] & BIT(0);

	/*
	 * NOTE: It's my impression from पढ़ोing the spec that the below parsing
	 * is correct. However I noticed जबतक testing with an HDCP 1.4 display
	 * through an HDCP 2.2 hub that only bit 3 was set. In that हाल, I
	 * would expect both bits to be set. So keep the parsing following the
	 * spec, but beware reality might not match the spec (at least क्रम some
	 * configurations).
	 */
	reply->hdcp_1x_device_present = raw->msg[2] & BIT(4);
	reply->hdcp_2x_device_present = raw->msg[2] & BIT(3);

	reply->query_capable_device_present = raw->msg[2] & BIT(5);
	reply->legacy_device_present = raw->msg[2] & BIT(6);
	reply->unauthorizable_device_present = raw->msg[2] & BIT(7);

	reply->auth_completed = !!(raw->msg[1] & BIT(3));
	reply->encryption_enabled = !!(raw->msg[1] & BIT(4));
	reply->repeater_present = !!(raw->msg[1] & BIT(5));
	reply->state = (raw->msg[1] & GENMASK(7, 6)) >> 6;

	वापस true;
पूर्ण

अटल bool drm_dp_sideband_parse_reply(काष्ठा drm_dp_sideband_msg_rx *raw,
					काष्ठा drm_dp_sideband_msg_reply_body *msg)
अणु
	स_रखो(msg, 0, माप(*msg));
	msg->reply_type = (raw->msg[0] & 0x80) >> 7;
	msg->req_type = (raw->msg[0] & 0x7f);

	अगर (msg->reply_type == DP_SIDEBAND_REPLY_NAK) अणु
		स_नकल(msg->u.nak.guid, &raw->msg[1], 16);
		msg->u.nak.reason = raw->msg[17];
		msg->u.nak.nak_data = raw->msg[18];
		वापस false;
	पूर्ण

	चयन (msg->req_type) अणु
	हाल DP_LINK_ADDRESS:
		वापस drm_dp_sideband_parse_link_address(raw, msg);
	हाल DP_QUERY_PAYLOAD:
		वापस drm_dp_sideband_parse_query_payload_ack(raw, msg);
	हाल DP_REMOTE_DPCD_READ:
		वापस drm_dp_sideband_parse_remote_dpcd_पढ़ो(raw, msg);
	हाल DP_REMOTE_DPCD_WRITE:
		वापस drm_dp_sideband_parse_remote_dpcd_ग_लिखो(raw, msg);
	हाल DP_REMOTE_I2C_READ:
		वापस drm_dp_sideband_parse_remote_i2c_पढ़ो_ack(raw, msg);
	हाल DP_REMOTE_I2C_WRITE:
		वापस true; /* since there's nothing to parse */
	हाल DP_ENUM_PATH_RESOURCES:
		वापस drm_dp_sideband_parse_क्रमागत_path_resources_ack(raw, msg);
	हाल DP_ALLOCATE_PAYLOAD:
		वापस drm_dp_sideband_parse_allocate_payload_ack(raw, msg);
	हाल DP_POWER_DOWN_PHY:
	हाल DP_POWER_UP_PHY:
		वापस drm_dp_sideband_parse_घातer_upकरोwn_phy_ack(raw, msg);
	हाल DP_CLEAR_PAYLOAD_ID_TABLE:
		वापस true; /* since there's nothing to parse */
	हाल DP_QUERY_STREAM_ENC_STATUS:
		वापस drm_dp_sideband_parse_query_stream_enc_status(raw, msg);
	शेष:
		DRM_ERROR("Got unknown reply 0x%02x (%s)\n", msg->req_type,
			  drm_dp_mst_req_type_str(msg->req_type));
		वापस false;
	पूर्ण
पूर्ण

अटल bool drm_dp_sideband_parse_connection_status_notअगरy(काष्ठा drm_dp_sideband_msg_rx *raw,
							   काष्ठा drm_dp_sideband_msg_req_body *msg)
अणु
	पूर्णांक idx = 1;

	msg->u.conn_stat.port_number = (raw->msg[idx] & 0xf0) >> 4;
	idx++;
	अगर (idx > raw->curlen)
		जाओ fail_len;

	स_नकल(msg->u.conn_stat.guid, &raw->msg[idx], 16);
	idx += 16;
	अगर (idx > raw->curlen)
		जाओ fail_len;

	msg->u.conn_stat.legacy_device_plug_status = (raw->msg[idx] >> 6) & 0x1;
	msg->u.conn_stat.displayport_device_plug_status = (raw->msg[idx] >> 5) & 0x1;
	msg->u.conn_stat.message_capability_status = (raw->msg[idx] >> 4) & 0x1;
	msg->u.conn_stat.input_port = (raw->msg[idx] >> 3) & 0x1;
	msg->u.conn_stat.peer_device_type = (raw->msg[idx] & 0x7);
	idx++;
	वापस true;
fail_len:
	DRM_DEBUG_KMS("connection status reply parse length fail %d %d\n", idx, raw->curlen);
	वापस false;
पूर्ण

अटल bool drm_dp_sideband_parse_resource_status_notअगरy(काष्ठा drm_dp_sideband_msg_rx *raw,
							   काष्ठा drm_dp_sideband_msg_req_body *msg)
अणु
	पूर्णांक idx = 1;

	msg->u.resource_stat.port_number = (raw->msg[idx] & 0xf0) >> 4;
	idx++;
	अगर (idx > raw->curlen)
		जाओ fail_len;

	स_नकल(msg->u.resource_stat.guid, &raw->msg[idx], 16);
	idx += 16;
	अगर (idx > raw->curlen)
		जाओ fail_len;

	msg->u.resource_stat.available_pbn = (raw->msg[idx] << 8) | (raw->msg[idx + 1]);
	idx++;
	वापस true;
fail_len:
	DRM_DEBUG_KMS("resource status reply parse length fail %d %d\n", idx, raw->curlen);
	वापस false;
पूर्ण

अटल bool drm_dp_sideband_parse_req(काष्ठा drm_dp_sideband_msg_rx *raw,
				      काष्ठा drm_dp_sideband_msg_req_body *msg)
अणु
	स_रखो(msg, 0, माप(*msg));
	msg->req_type = (raw->msg[0] & 0x7f);

	चयन (msg->req_type) अणु
	हाल DP_CONNECTION_STATUS_NOTIFY:
		वापस drm_dp_sideband_parse_connection_status_notअगरy(raw, msg);
	हाल DP_RESOURCE_STATUS_NOTIFY:
		वापस drm_dp_sideband_parse_resource_status_notअगरy(raw, msg);
	शेष:
		DRM_ERROR("Got unknown request 0x%02x (%s)\n", msg->req_type,
			  drm_dp_mst_req_type_str(msg->req_type));
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम build_dpcd_ग_लिखो(काष्ठा drm_dp_sideband_msg_tx *msg,
			     u8 port_num, u32 offset, u8 num_bytes, u8 *bytes)
अणु
	काष्ठा drm_dp_sideband_msg_req_body req;

	req.req_type = DP_REMOTE_DPCD_WRITE;
	req.u.dpcd_ग_लिखो.port_number = port_num;
	req.u.dpcd_ग_लिखो.dpcd_address = offset;
	req.u.dpcd_ग_लिखो.num_bytes = num_bytes;
	req.u.dpcd_ग_लिखो.bytes = bytes;
	drm_dp_encode_sideband_req(&req, msg);
पूर्ण

अटल व्योम build_link_address(काष्ठा drm_dp_sideband_msg_tx *msg)
अणु
	काष्ठा drm_dp_sideband_msg_req_body req;

	req.req_type = DP_LINK_ADDRESS;
	drm_dp_encode_sideband_req(&req, msg);
पूर्ण

अटल व्योम build_clear_payload_id_table(काष्ठा drm_dp_sideband_msg_tx *msg)
अणु
	काष्ठा drm_dp_sideband_msg_req_body req;

	req.req_type = DP_CLEAR_PAYLOAD_ID_TABLE;
	drm_dp_encode_sideband_req(&req, msg);
	msg->path_msg = true;
पूर्ण

अटल पूर्णांक build_क्रमागत_path_resources(काष्ठा drm_dp_sideband_msg_tx *msg,
				     पूर्णांक port_num)
अणु
	काष्ठा drm_dp_sideband_msg_req_body req;

	req.req_type = DP_ENUM_PATH_RESOURCES;
	req.u.port_num.port_number = port_num;
	drm_dp_encode_sideband_req(&req, msg);
	msg->path_msg = true;
	वापस 0;
पूर्ण

अटल व्योम build_allocate_payload(काष्ठा drm_dp_sideband_msg_tx *msg,
				   पूर्णांक port_num,
				   u8 vcpi, uपूर्णांक16_t pbn,
				   u8 number_sdp_streams,
				   u8 *sdp_stream_sink)
अणु
	काष्ठा drm_dp_sideband_msg_req_body req;

	स_रखो(&req, 0, माप(req));
	req.req_type = DP_ALLOCATE_PAYLOAD;
	req.u.allocate_payload.port_number = port_num;
	req.u.allocate_payload.vcpi = vcpi;
	req.u.allocate_payload.pbn = pbn;
	req.u.allocate_payload.number_sdp_streams = number_sdp_streams;
	स_नकल(req.u.allocate_payload.sdp_stream_sink, sdp_stream_sink,
		   number_sdp_streams);
	drm_dp_encode_sideband_req(&req, msg);
	msg->path_msg = true;
पूर्ण

अटल व्योम build_घातer_upकरोwn_phy(काष्ठा drm_dp_sideband_msg_tx *msg,
				   पूर्णांक port_num, bool घातer_up)
अणु
	काष्ठा drm_dp_sideband_msg_req_body req;

	अगर (घातer_up)
		req.req_type = DP_POWER_UP_PHY;
	अन्यथा
		req.req_type = DP_POWER_DOWN_PHY;

	req.u.port_num.port_number = port_num;
	drm_dp_encode_sideband_req(&req, msg);
	msg->path_msg = true;
पूर्ण

अटल पूर्णांक
build_query_stream_enc_status(काष्ठा drm_dp_sideband_msg_tx *msg, u8 stream_id,
			      u8 *q_id)
अणु
	काष्ठा drm_dp_sideband_msg_req_body req;

	req.req_type = DP_QUERY_STREAM_ENC_STATUS;
	req.u.enc_status.stream_id = stream_id;
	स_नकल(req.u.enc_status.client_id, q_id,
	       माप(req.u.enc_status.client_id));
	req.u.enc_status.stream_event = 0;
	req.u.enc_status.valid_stream_event = false;
	req.u.enc_status.stream_behavior = 0;
	req.u.enc_status.valid_stream_behavior = false;

	drm_dp_encode_sideband_req(&req, msg);
	वापस 0;
पूर्ण

अटल पूर्णांक drm_dp_mst_assign_payload_id(काष्ठा drm_dp_mst_topology_mgr *mgr,
					काष्ठा drm_dp_vcpi *vcpi)
अणु
	पूर्णांक ret, vcpi_ret;

	mutex_lock(&mgr->payload_lock);
	ret = find_first_zero_bit(&mgr->payload_mask, mgr->max_payloads + 1);
	अगर (ret > mgr->max_payloads) अणु
		ret = -EINVAL;
		DRM_DEBUG_KMS("out of payload ids %d\n", ret);
		जाओ out_unlock;
	पूर्ण

	vcpi_ret = find_first_zero_bit(&mgr->vcpi_mask, mgr->max_payloads + 1);
	अगर (vcpi_ret > mgr->max_payloads) अणु
		ret = -EINVAL;
		DRM_DEBUG_KMS("out of vcpi ids %d\n", ret);
		जाओ out_unlock;
	पूर्ण

	set_bit(ret, &mgr->payload_mask);
	set_bit(vcpi_ret, &mgr->vcpi_mask);
	vcpi->vcpi = vcpi_ret + 1;
	mgr->proposed_vcpis[ret - 1] = vcpi;
out_unlock:
	mutex_unlock(&mgr->payload_lock);
	वापस ret;
पूर्ण

अटल व्योम drm_dp_mst_put_payload_id(काष्ठा drm_dp_mst_topology_mgr *mgr,
				      पूर्णांक vcpi)
अणु
	पूर्णांक i;

	अगर (vcpi == 0)
		वापस;

	mutex_lock(&mgr->payload_lock);
	DRM_DEBUG_KMS("putting payload %d\n", vcpi);
	clear_bit(vcpi - 1, &mgr->vcpi_mask);

	क्रम (i = 0; i < mgr->max_payloads; i++) अणु
		अगर (mgr->proposed_vcpis[i] &&
		    mgr->proposed_vcpis[i]->vcpi == vcpi) अणु
			mgr->proposed_vcpis[i] = शून्य;
			clear_bit(i + 1, &mgr->payload_mask);
		पूर्ण
	पूर्ण
	mutex_unlock(&mgr->payload_lock);
पूर्ण

अटल bool check_txmsg_state(काष्ठा drm_dp_mst_topology_mgr *mgr,
			      काष्ठा drm_dp_sideband_msg_tx *txmsg)
अणु
	अचिन्हित पूर्णांक state;

	/*
	 * All updates to txmsg->state are रक्षित by mgr->qlock, and the two
	 * हालs we check here are terminal states. For those the barriers
	 * provided by the wake_up/रुको_event pair are enough.
	 */
	state = READ_ONCE(txmsg->state);
	वापस (state == DRM_DP_SIDEBAND_TX_RX ||
		state == DRM_DP_SIDEBAND_TX_TIMEOUT);
पूर्ण

अटल पूर्णांक drm_dp_mst_रुको_tx_reply(काष्ठा drm_dp_mst_branch *mstb,
				    काष्ठा drm_dp_sideband_msg_tx *txmsg)
अणु
	काष्ठा drm_dp_mst_topology_mgr *mgr = mstb->mgr;
	अचिन्हित दीर्घ रुको_समयout = msecs_to_jअगरfies(4000);
	अचिन्हित दीर्घ रुको_expires = jअगरfies + रुको_समयout;
	पूर्णांक ret;

	क्रम (;;) अणु
		/*
		 * If the driver provides a way क्रम this, change to
		 * poll-रुकोing क्रम the MST reply पूर्णांकerrupt अगर we didn't receive
		 * it क्रम 50 msec. This would cater क्रम हालs where the HPD
		 * pulse संकेत got lost somewhere, even though the sink उठाओd
		 * the corresponding MST पूर्णांकerrupt correctly. One example is the
		 * Club 3D CAC-1557 TypeC -> DP adapter which क्रम some reason
		 * filters out लघु pulses with a duration less than ~540 usec.
		 *
		 * The poll period is 50 msec to aव्योम missing an पूर्णांकerrupt
		 * after the sink has cleared it (after a 110msec समयout
		 * since it उठाओd the पूर्णांकerrupt).
		 */
		ret = रुको_event_समयout(mgr->tx_रुकोq,
					 check_txmsg_state(mgr, txmsg),
					 mgr->cbs->poll_hpd_irq ?
						msecs_to_jअगरfies(50) :
						रुको_समयout);

		अगर (ret || !mgr->cbs->poll_hpd_irq ||
		    समय_after(jअगरfies, रुको_expires))
			अवरोध;

		mgr->cbs->poll_hpd_irq(mgr);
	पूर्ण

	mutex_lock(&mgr->qlock);
	अगर (ret > 0) अणु
		अगर (txmsg->state == DRM_DP_SIDEBAND_TX_TIMEOUT) अणु
			ret = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		DRM_DEBUG_KMS("timedout msg send %p %d %d\n", txmsg, txmsg->state, txmsg->seqno);

		/* dump some state */
		ret = -EIO;

		/* हटाओ from q */
		अगर (txmsg->state == DRM_DP_SIDEBAND_TX_QUEUED ||
		    txmsg->state == DRM_DP_SIDEBAND_TX_START_SEND ||
		    txmsg->state == DRM_DP_SIDEBAND_TX_SENT)
			list_del(&txmsg->next);
	पूर्ण
out:
	अगर (unlikely(ret == -EIO) && drm_debug_enabled(DRM_UT_DP)) अणु
		काष्ठा drm_prपूर्णांकer p = drm_debug_prपूर्णांकer(DBG_PREFIX);

		drm_dp_mst_dump_sideband_msg_tx(&p, txmsg);
	पूर्ण
	mutex_unlock(&mgr->qlock);

	drm_dp_mst_kick_tx(mgr);
	वापस ret;
पूर्ण

अटल काष्ठा drm_dp_mst_branch *drm_dp_add_mst_branch_device(u8 lct, u8 *rad)
अणु
	काष्ठा drm_dp_mst_branch *mstb;

	mstb = kzalloc(माप(*mstb), GFP_KERNEL);
	अगर (!mstb)
		वापस शून्य;

	mstb->lct = lct;
	अगर (lct > 1)
		स_नकल(mstb->rad, rad, lct / 2);
	INIT_LIST_HEAD(&mstb->ports);
	kref_init(&mstb->topology_kref);
	kref_init(&mstb->दो_स्मृति_kref);
	वापस mstb;
पूर्ण

अटल व्योम drm_dp_मुक्त_mst_branch_device(काष्ठा kref *kref)
अणु
	काष्ठा drm_dp_mst_branch *mstb =
		container_of(kref, काष्ठा drm_dp_mst_branch, दो_स्मृति_kref);

	अगर (mstb->port_parent)
		drm_dp_mst_put_port_दो_स्मृति(mstb->port_parent);

	kमुक्त(mstb);
पूर्ण

/**
 * DOC: Branch device and port refcounting
 *
 * Topology refcount overview
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * The refcounting schemes क्रम &काष्ठा drm_dp_mst_branch and &काष्ठा
 * drm_dp_mst_port are somewhat unusual. Both ports and branch devices have
 * two dअगरferent kinds of refcounts: topology refcounts, and दो_स्मृति refcounts.
 *
 * Topology refcounts are not exposed to drivers, and are handled पूर्णांकernally
 * by the DP MST helpers. The helpers use them in order to prevent the
 * in-memory topology state from being changed in the middle of critical
 * operations like changing the पूर्णांकernal state of payload allocations. This
 * means each branch and port will be considered to be connected to the rest
 * of the topology until its topology refcount reaches zero. Additionally,
 * क्रम ports this means that their associated &काष्ठा drm_connector will stay
 * रेजिस्टरed with userspace until the port's refcount reaches 0.
 *
 * Malloc refcount overview
 * ~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Malloc references are used to keep a &काष्ठा drm_dp_mst_port or &काष्ठा
 * drm_dp_mst_branch allocated even after all of its topology references have
 * been dropped, so that the driver or MST helpers can safely access each
 * branch's last known state beक्रमe it was disconnected from the topology.
 * When the दो_स्मृति refcount of a port or branch reaches 0, the memory
 * allocation containing the &काष्ठा drm_dp_mst_branch or &काष्ठा
 * drm_dp_mst_port respectively will be मुक्तd.
 *
 * For &काष्ठा drm_dp_mst_branch, दो_स्मृति refcounts are not currently exposed
 * to drivers. As of writing this करोcumentation, there are no drivers that
 * have a useहाल क्रम accessing &काष्ठा drm_dp_mst_branch outside of the MST
 * helpers. Exposing this API to drivers in a race-मुक्त manner would take more
 * tweaking of the refcounting scheme, however patches are welcome provided
 * there is a legitimate driver useहाल क्रम this.
 *
 * Refcount relationships in a topology
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Let's take a look at why the relationship between topology and दो_स्मृति
 * refcounts is deचिन्हित the way it is.
 *
 * .. kernel-figure:: dp-mst/topology-figure-1.करोt
 *
 *    An example of topology and दो_स्मृति refs in a DP MST topology with two
 *    active payloads. Topology refcount increments are indicated by solid
 *    lines, and दो_स्मृति refcount increments are indicated by dashed lines.
 *    Each starts from the branch which incremented the refcount, and ends at
 *    the branch to which the refcount beदीर्घs to, i.e. the arrow poपूर्णांकs the
 *    same way as the C poपूर्णांकers used to reference a काष्ठाure.
 *
 * As you can see in the above figure, every branch increments the topology
 * refcount of its children, and increments the दो_स्मृति refcount of its
 * parent. Additionally, every payload increments the दो_स्मृति refcount of its
 * asचिन्हित port by 1.
 *
 * So, what would happen अगर MSTB #3 from the above figure was unplugged from
 * the प्रणाली, but the driver hadn't yet हटाओd payload #2 from port #3? The
 * topology would start to look like the figure below.
 *
 * .. kernel-figure:: dp-mst/topology-figure-2.करोt
 *
 *    Ports and branch devices which have been released from memory are
 *    colored grey, and references which have been हटाओd are colored red.
 *
 * Whenever a port or branch device's topology refcount reaches zero, it will
 * decrement the topology refcounts of all its children, the दो_स्मृति refcount
 * of its parent, and finally its own दो_स्मृति refcount. For MSTB #4 and port
 * #4, this means they both have been disconnected from the topology and मुक्तd
 * from memory. But, because payload #2 is still holding a reference to port
 * #3, port #3 is हटाओd from the topology but its &काष्ठा drm_dp_mst_port
 * is still accessible from memory. This also means port #3 has not yet
 * decremented the दो_स्मृति refcount of MSTB #3, so its &काष्ठा
 * drm_dp_mst_branch will also stay allocated in memory until port #3's
 * दो_स्मृति refcount reaches 0.
 *
 * This relationship is necessary because in order to release payload #2, we
 * need to be able to figure out the last relative of port #3 that's still
 * connected to the topology. In this हाल, we would travel up the topology as
 * shown below.
 *
 * .. kernel-figure:: dp-mst/topology-figure-3.करोt
 *
 * And finally, हटाओ payload #2 by communicating with port #2 through
 * sideband transactions.
 */

/**
 * drm_dp_mst_get_mstb_दो_स्मृति() - Increment the दो_स्मृति refcount of a branch
 * device
 * @mstb: The &काष्ठा drm_dp_mst_branch to increment the दो_स्मृति refcount of
 *
 * Increments &drm_dp_mst_branch.दो_स्मृति_kref. When
 * &drm_dp_mst_branch.दो_स्मृति_kref reaches 0, the memory allocation क्रम @mstb
 * will be released and @mstb may no दीर्घer be used.
 *
 * See also: drm_dp_mst_put_mstb_दो_स्मृति()
 */
अटल व्योम
drm_dp_mst_get_mstb_दो_स्मृति(काष्ठा drm_dp_mst_branch *mstb)
अणु
	kref_get(&mstb->दो_स्मृति_kref);
	DRM_DEBUG("mstb %p (%d)\n", mstb, kref_पढ़ो(&mstb->दो_स्मृति_kref));
पूर्ण

/**
 * drm_dp_mst_put_mstb_दो_स्मृति() - Decrement the दो_स्मृति refcount of a branch
 * device
 * @mstb: The &काष्ठा drm_dp_mst_branch to decrement the दो_स्मृति refcount of
 *
 * Decrements &drm_dp_mst_branch.दो_स्मृति_kref. When
 * &drm_dp_mst_branch.दो_स्मृति_kref reaches 0, the memory allocation क्रम @mstb
 * will be released and @mstb may no दीर्घer be used.
 *
 * See also: drm_dp_mst_get_mstb_दो_स्मृति()
 */
अटल व्योम
drm_dp_mst_put_mstb_दो_स्मृति(काष्ठा drm_dp_mst_branch *mstb)
अणु
	DRM_DEBUG("mstb %p (%d)\n", mstb, kref_पढ़ो(&mstb->दो_स्मृति_kref) - 1);
	kref_put(&mstb->दो_स्मृति_kref, drm_dp_मुक्त_mst_branch_device);
पूर्ण

अटल व्योम drm_dp_मुक्त_mst_port(काष्ठा kref *kref)
अणु
	काष्ठा drm_dp_mst_port *port =
		container_of(kref, काष्ठा drm_dp_mst_port, दो_स्मृति_kref);

	drm_dp_mst_put_mstb_दो_स्मृति(port->parent);
	kमुक्त(port);
पूर्ण

/**
 * drm_dp_mst_get_port_दो_स्मृति() - Increment the दो_स्मृति refcount of an MST port
 * @port: The &काष्ठा drm_dp_mst_port to increment the दो_स्मृति refcount of
 *
 * Increments &drm_dp_mst_port.दो_स्मृति_kref. When &drm_dp_mst_port.दो_स्मृति_kref
 * reaches 0, the memory allocation क्रम @port will be released and @port may
 * no दीर्घer be used.
 *
 * Because @port could potentially be मुक्तd at any समय by the DP MST helpers
 * अगर &drm_dp_mst_port.दो_स्मृति_kref reaches 0, including during a call to this
 * function, drivers that which to make use of &काष्ठा drm_dp_mst_port should
 * ensure that they grab at least one मुख्य दो_स्मृति reference to their MST ports
 * in &drm_dp_mst_topology_cbs.add_connector. This callback is called beक्रमe
 * there is any chance क्रम &drm_dp_mst_port.दो_स्मृति_kref to reach 0.
 *
 * See also: drm_dp_mst_put_port_दो_स्मृति()
 */
व्योम
drm_dp_mst_get_port_दो_स्मृति(काष्ठा drm_dp_mst_port *port)
अणु
	kref_get(&port->दो_स्मृति_kref);
	DRM_DEBUG("port %p (%d)\n", port, kref_पढ़ो(&port->दो_स्मृति_kref));
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_get_port_दो_स्मृति);

/**
 * drm_dp_mst_put_port_दो_स्मृति() - Decrement the दो_स्मृति refcount of an MST port
 * @port: The &काष्ठा drm_dp_mst_port to decrement the दो_स्मृति refcount of
 *
 * Decrements &drm_dp_mst_port.दो_स्मृति_kref. When &drm_dp_mst_port.दो_स्मृति_kref
 * reaches 0, the memory allocation क्रम @port will be released and @port may
 * no दीर्घer be used.
 *
 * See also: drm_dp_mst_get_port_दो_स्मृति()
 */
व्योम
drm_dp_mst_put_port_दो_स्मृति(काष्ठा drm_dp_mst_port *port)
अणु
	DRM_DEBUG("port %p (%d)\n", port, kref_पढ़ो(&port->दो_स्मृति_kref) - 1);
	kref_put(&port->दो_स्मृति_kref, drm_dp_मुक्त_mst_port);
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_put_port_दो_स्मृति);

#अगर IS_ENABLED(CONFIG_DRM_DEBUG_DP_MST_TOPOLOGY_REFS)

#घोषणा STACK_DEPTH 8

अटल noअंतरभूत व्योम
__topology_ref_save(काष्ठा drm_dp_mst_topology_mgr *mgr,
		    काष्ठा drm_dp_mst_topology_ref_history *history,
		    क्रमागत drm_dp_mst_topology_ref_type type)
अणु
	काष्ठा drm_dp_mst_topology_ref_entry *entry = शून्य;
	depot_stack_handle_t backtrace;
	uदीर्घ stack_entries[STACK_DEPTH];
	uपूर्णांक n;
	पूर्णांक i;

	n = stack_trace_save(stack_entries, ARRAY_SIZE(stack_entries), 1);
	backtrace = stack_depot_save(stack_entries, n, GFP_KERNEL);
	अगर (!backtrace)
		वापस;

	/* Try to find an existing entry क्रम this backtrace */
	क्रम (i = 0; i < history->len; i++) अणु
		अगर (history->entries[i].backtrace == backtrace) अणु
			entry = &history->entries[i];
			अवरोध;
		पूर्ण
	पूर्ण

	/* Otherwise add one */
	अगर (!entry) अणु
		काष्ठा drm_dp_mst_topology_ref_entry *new;
		पूर्णांक new_len = history->len + 1;

		new = kपुनः_स्मृति(history->entries, माप(*new) * new_len,
			       GFP_KERNEL);
		अगर (!new)
			वापस;

		entry = &new[history->len];
		history->len = new_len;
		history->entries = new;

		entry->backtrace = backtrace;
		entry->type = type;
		entry->count = 0;
	पूर्ण
	entry->count++;
	entry->ts_nsec = kसमय_get_ns();
पूर्ण

अटल पूर्णांक
topology_ref_history_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा drm_dp_mst_topology_ref_entry *entry_a = a, *entry_b = b;

	अगर (entry_a->ts_nsec > entry_b->ts_nsec)
		वापस 1;
	अन्यथा अगर (entry_a->ts_nsec < entry_b->ts_nsec)
		वापस -1;
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *
topology_ref_type_to_str(क्रमागत drm_dp_mst_topology_ref_type type)
अणु
	अगर (type == DRM_DP_MST_TOPOLOGY_REF_GET)
		वापस "get";
	अन्यथा
		वापस "put";
पूर्ण

अटल व्योम
__dump_topology_ref_history(काष्ठा drm_dp_mst_topology_ref_history *history,
			    व्योम *ptr, स्थिर अक्षर *type_str)
अणु
	काष्ठा drm_prपूर्णांकer p = drm_debug_prपूर्णांकer(DBG_PREFIX);
	अक्षर *buf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	पूर्णांक i;

	अगर (!buf)
		वापस;

	अगर (!history->len)
		जाओ out;

	/* First, sort the list so that it goes from oldest to newest
	 * reference entry
	 */
	sort(history->entries, history->len, माप(*history->entries),
	     topology_ref_history_cmp, शून्य);

	drm_म_लिखो(&p, "%s (%p) topology count reached 0, dumping history:\n",
		   type_str, ptr);

	क्रम (i = 0; i < history->len; i++) अणु
		स्थिर काष्ठा drm_dp_mst_topology_ref_entry *entry =
			&history->entries[i];
		uदीर्घ *entries;
		uपूर्णांक nr_entries;
		u64 ts_nsec = entry->ts_nsec;
		u32 rem_nsec = करो_भाग(ts_nsec, 1000000000);

		nr_entries = stack_depot_fetch(entry->backtrace, &entries);
		stack_trace_snprपूर्णांक(buf, PAGE_SIZE, entries, nr_entries, 4);

		drm_म_लिखो(&p, "  %d %ss (last at %5llu.%06u):\n%s",
			   entry->count,
			   topology_ref_type_to_str(entry->type),
			   ts_nsec, rem_nsec / 1000, buf);
	पूर्ण

	/* Now मुक्त the history, since this is the only समय we expose it */
	kमुक्त(history->entries);
out:
	kमुक्त(buf);
पूर्ण

अटल __always_अंतरभूत व्योम
drm_dp_mst_dump_mstb_topology_history(काष्ठा drm_dp_mst_branch *mstb)
अणु
	__dump_topology_ref_history(&mstb->topology_ref_history, mstb,
				    "MSTB");
पूर्ण

अटल __always_अंतरभूत व्योम
drm_dp_mst_dump_port_topology_history(काष्ठा drm_dp_mst_port *port)
अणु
	__dump_topology_ref_history(&port->topology_ref_history, port,
				    "Port");
पूर्ण

अटल __always_अंतरभूत व्योम
save_mstb_topology_ref(काष्ठा drm_dp_mst_branch *mstb,
		       क्रमागत drm_dp_mst_topology_ref_type type)
अणु
	__topology_ref_save(mstb->mgr, &mstb->topology_ref_history, type);
पूर्ण

अटल __always_अंतरभूत व्योम
save_port_topology_ref(काष्ठा drm_dp_mst_port *port,
		       क्रमागत drm_dp_mst_topology_ref_type type)
अणु
	__topology_ref_save(port->mgr, &port->topology_ref_history, type);
पूर्ण

अटल अंतरभूत व्योम
topology_ref_history_lock(काष्ठा drm_dp_mst_topology_mgr *mgr)
अणु
	mutex_lock(&mgr->topology_ref_history_lock);
पूर्ण

अटल अंतरभूत व्योम
topology_ref_history_unlock(काष्ठा drm_dp_mst_topology_mgr *mgr)
अणु
	mutex_unlock(&mgr->topology_ref_history_lock);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
topology_ref_history_lock(काष्ठा drm_dp_mst_topology_mgr *mgr) अणुपूर्ण
अटल अंतरभूत व्योम
topology_ref_history_unlock(काष्ठा drm_dp_mst_topology_mgr *mgr) अणुपूर्ण
अटल अंतरभूत व्योम
drm_dp_mst_dump_mstb_topology_history(काष्ठा drm_dp_mst_branch *mstb) अणुपूर्ण
अटल अंतरभूत व्योम
drm_dp_mst_dump_port_topology_history(काष्ठा drm_dp_mst_port *port) अणुपूर्ण
#घोषणा save_mstb_topology_ref(mstb, type)
#घोषणा save_port_topology_ref(port, type)
#पूर्ण_अगर

अटल व्योम drm_dp_destroy_mst_branch_device(काष्ठा kref *kref)
अणु
	काष्ठा drm_dp_mst_branch *mstb =
		container_of(kref, काष्ठा drm_dp_mst_branch, topology_kref);
	काष्ठा drm_dp_mst_topology_mgr *mgr = mstb->mgr;

	drm_dp_mst_dump_mstb_topology_history(mstb);

	INIT_LIST_HEAD(&mstb->destroy_next);

	/*
	 * This can get called under mgr->mutex, so we need to perक्रमm the
	 * actual deकाष्ठाion of the mstb in another worker
	 */
	mutex_lock(&mgr->delayed_destroy_lock);
	list_add(&mstb->destroy_next, &mgr->destroy_branch_device_list);
	mutex_unlock(&mgr->delayed_destroy_lock);
	queue_work(mgr->delayed_destroy_wq, &mgr->delayed_destroy_work);
पूर्ण

/**
 * drm_dp_mst_topology_try_get_mstb() - Increment the topology refcount of a
 * branch device unless it's zero
 * @mstb: &काष्ठा drm_dp_mst_branch to increment the topology refcount of
 *
 * Attempts to grab a topology reference to @mstb, अगर it hasn't yet been
 * हटाओd from the topology (e.g. &drm_dp_mst_branch.topology_kref has
 * reached 0). Holding a topology reference implies that a दो_स्मृति reference
 * will be held to @mstb as दीर्घ as the user holds the topology reference.
 *
 * Care should be taken to ensure that the user has at least one दो_स्मृति
 * reference to @mstb. If you alपढ़ोy have a topology reference to @mstb, you
 * should use drm_dp_mst_topology_get_mstb() instead.
 *
 * See also:
 * drm_dp_mst_topology_get_mstb()
 * drm_dp_mst_topology_put_mstb()
 *
 * Returns:
 * * 1: A topology reference was grabbed successfully
 * * 0: @port is no दीर्घer in the topology, no reference was grabbed
 */
अटल पूर्णांक __must_check
drm_dp_mst_topology_try_get_mstb(काष्ठा drm_dp_mst_branch *mstb)
अणु
	पूर्णांक ret;

	topology_ref_history_lock(mstb->mgr);
	ret = kref_get_unless_zero(&mstb->topology_kref);
	अगर (ret) अणु
		DRM_DEBUG("mstb %p (%d)\n",
			  mstb, kref_पढ़ो(&mstb->topology_kref));
		save_mstb_topology_ref(mstb, DRM_DP_MST_TOPOLOGY_REF_GET);
	पूर्ण

	topology_ref_history_unlock(mstb->mgr);

	वापस ret;
पूर्ण

/**
 * drm_dp_mst_topology_get_mstb() - Increment the topology refcount of a
 * branch device
 * @mstb: The &काष्ठा drm_dp_mst_branch to increment the topology refcount of
 *
 * Increments &drm_dp_mst_branch.topology_refcount without checking whether or
 * not it's alपढ़ोy reached 0. This is only valid to use in scenarios where
 * you are alपढ़ोy guaranteed to have at least one active topology reference
 * to @mstb. Otherwise, drm_dp_mst_topology_try_get_mstb() must be used.
 *
 * See also:
 * drm_dp_mst_topology_try_get_mstb()
 * drm_dp_mst_topology_put_mstb()
 */
अटल व्योम drm_dp_mst_topology_get_mstb(काष्ठा drm_dp_mst_branch *mstb)
अणु
	topology_ref_history_lock(mstb->mgr);

	save_mstb_topology_ref(mstb, DRM_DP_MST_TOPOLOGY_REF_GET);
	WARN_ON(kref_पढ़ो(&mstb->topology_kref) == 0);
	kref_get(&mstb->topology_kref);
	DRM_DEBUG("mstb %p (%d)\n", mstb, kref_पढ़ो(&mstb->topology_kref));

	topology_ref_history_unlock(mstb->mgr);
पूर्ण

/**
 * drm_dp_mst_topology_put_mstb() - release a topology reference to a branch
 * device
 * @mstb: The &काष्ठा drm_dp_mst_branch to release the topology reference from
 *
 * Releases a topology reference from @mstb by decrementing
 * &drm_dp_mst_branch.topology_kref.
 *
 * See also:
 * drm_dp_mst_topology_try_get_mstb()
 * drm_dp_mst_topology_get_mstb()
 */
अटल व्योम
drm_dp_mst_topology_put_mstb(काष्ठा drm_dp_mst_branch *mstb)
अणु
	topology_ref_history_lock(mstb->mgr);

	DRM_DEBUG("mstb %p (%d)\n",
		  mstb, kref_पढ़ो(&mstb->topology_kref) - 1);
	save_mstb_topology_ref(mstb, DRM_DP_MST_TOPOLOGY_REF_PUT);

	topology_ref_history_unlock(mstb->mgr);
	kref_put(&mstb->topology_kref, drm_dp_destroy_mst_branch_device);
पूर्ण

अटल व्योम drm_dp_destroy_port(काष्ठा kref *kref)
अणु
	काष्ठा drm_dp_mst_port *port =
		container_of(kref, काष्ठा drm_dp_mst_port, topology_kref);
	काष्ठा drm_dp_mst_topology_mgr *mgr = port->mgr;

	drm_dp_mst_dump_port_topology_history(port);

	/* There's nothing that needs locking to destroy an input port yet */
	अगर (port->input) अणु
		drm_dp_mst_put_port_दो_स्मृति(port);
		वापस;
	पूर्ण

	kमुक्त(port->cached_edid);

	/*
	 * we can't destroy the connector here, as we might be holding the
	 * mode_config.mutex from an EDID retrieval
	 */
	mutex_lock(&mgr->delayed_destroy_lock);
	list_add(&port->next, &mgr->destroy_port_list);
	mutex_unlock(&mgr->delayed_destroy_lock);
	queue_work(mgr->delayed_destroy_wq, &mgr->delayed_destroy_work);
पूर्ण

/**
 * drm_dp_mst_topology_try_get_port() - Increment the topology refcount of a
 * port unless it's zero
 * @port: &काष्ठा drm_dp_mst_port to increment the topology refcount of
 *
 * Attempts to grab a topology reference to @port, अगर it hasn't yet been
 * हटाओd from the topology (e.g. &drm_dp_mst_port.topology_kref has reached
 * 0). Holding a topology reference implies that a दो_स्मृति reference will be
 * held to @port as दीर्घ as the user holds the topology reference.
 *
 * Care should be taken to ensure that the user has at least one दो_स्मृति
 * reference to @port. If you alपढ़ोy have a topology reference to @port, you
 * should use drm_dp_mst_topology_get_port() instead.
 *
 * See also:
 * drm_dp_mst_topology_get_port()
 * drm_dp_mst_topology_put_port()
 *
 * Returns:
 * * 1: A topology reference was grabbed successfully
 * * 0: @port is no दीर्घer in the topology, no reference was grabbed
 */
अटल पूर्णांक __must_check
drm_dp_mst_topology_try_get_port(काष्ठा drm_dp_mst_port *port)
अणु
	पूर्णांक ret;

	topology_ref_history_lock(port->mgr);
	ret = kref_get_unless_zero(&port->topology_kref);
	अगर (ret) अणु
		DRM_DEBUG("port %p (%d)\n",
			  port, kref_पढ़ो(&port->topology_kref));
		save_port_topology_ref(port, DRM_DP_MST_TOPOLOGY_REF_GET);
	पूर्ण

	topology_ref_history_unlock(port->mgr);
	वापस ret;
पूर्ण

/**
 * drm_dp_mst_topology_get_port() - Increment the topology refcount of a port
 * @port: The &काष्ठा drm_dp_mst_port to increment the topology refcount of
 *
 * Increments &drm_dp_mst_port.topology_refcount without checking whether or
 * not it's alपढ़ोy reached 0. This is only valid to use in scenarios where
 * you are alपढ़ोy guaranteed to have at least one active topology reference
 * to @port. Otherwise, drm_dp_mst_topology_try_get_port() must be used.
 *
 * See also:
 * drm_dp_mst_topology_try_get_port()
 * drm_dp_mst_topology_put_port()
 */
अटल व्योम drm_dp_mst_topology_get_port(काष्ठा drm_dp_mst_port *port)
अणु
	topology_ref_history_lock(port->mgr);

	WARN_ON(kref_पढ़ो(&port->topology_kref) == 0);
	kref_get(&port->topology_kref);
	DRM_DEBUG("port %p (%d)\n", port, kref_पढ़ो(&port->topology_kref));
	save_port_topology_ref(port, DRM_DP_MST_TOPOLOGY_REF_GET);

	topology_ref_history_unlock(port->mgr);
पूर्ण

/**
 * drm_dp_mst_topology_put_port() - release a topology reference to a port
 * @port: The &काष्ठा drm_dp_mst_port to release the topology reference from
 *
 * Releases a topology reference from @port by decrementing
 * &drm_dp_mst_port.topology_kref.
 *
 * See also:
 * drm_dp_mst_topology_try_get_port()
 * drm_dp_mst_topology_get_port()
 */
अटल व्योम drm_dp_mst_topology_put_port(काष्ठा drm_dp_mst_port *port)
अणु
	topology_ref_history_lock(port->mgr);

	DRM_DEBUG("port %p (%d)\n",
		  port, kref_पढ़ो(&port->topology_kref) - 1);
	save_port_topology_ref(port, DRM_DP_MST_TOPOLOGY_REF_PUT);

	topology_ref_history_unlock(port->mgr);
	kref_put(&port->topology_kref, drm_dp_destroy_port);
पूर्ण

अटल काष्ठा drm_dp_mst_branch *
drm_dp_mst_topology_get_mstb_validated_locked(काष्ठा drm_dp_mst_branch *mstb,
					      काष्ठा drm_dp_mst_branch *to_find)
अणु
	काष्ठा drm_dp_mst_port *port;
	काष्ठा drm_dp_mst_branch *rmstb;

	अगर (to_find == mstb)
		वापस mstb;

	list_क्रम_each_entry(port, &mstb->ports, next) अणु
		अगर (port->mstb) अणु
			rmstb = drm_dp_mst_topology_get_mstb_validated_locked(
			    port->mstb, to_find);
			अगर (rmstb)
				वापस rmstb;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा drm_dp_mst_branch *
drm_dp_mst_topology_get_mstb_validated(काष्ठा drm_dp_mst_topology_mgr *mgr,
				       काष्ठा drm_dp_mst_branch *mstb)
अणु
	काष्ठा drm_dp_mst_branch *rmstb = शून्य;

	mutex_lock(&mgr->lock);
	अगर (mgr->mst_primary) अणु
		rmstb = drm_dp_mst_topology_get_mstb_validated_locked(
		    mgr->mst_primary, mstb);

		अगर (rmstb && !drm_dp_mst_topology_try_get_mstb(rmstb))
			rmstb = शून्य;
	पूर्ण
	mutex_unlock(&mgr->lock);
	वापस rmstb;
पूर्ण

अटल काष्ठा drm_dp_mst_port *
drm_dp_mst_topology_get_port_validated_locked(काष्ठा drm_dp_mst_branch *mstb,
					      काष्ठा drm_dp_mst_port *to_find)
अणु
	काष्ठा drm_dp_mst_port *port, *mport;

	list_क्रम_each_entry(port, &mstb->ports, next) अणु
		अगर (port == to_find)
			वापस port;

		अगर (port->mstb) अणु
			mport = drm_dp_mst_topology_get_port_validated_locked(
			    port->mstb, to_find);
			अगर (mport)
				वापस mport;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा drm_dp_mst_port *
drm_dp_mst_topology_get_port_validated(काष्ठा drm_dp_mst_topology_mgr *mgr,
				       काष्ठा drm_dp_mst_port *port)
अणु
	काष्ठा drm_dp_mst_port *rport = शून्य;

	mutex_lock(&mgr->lock);
	अगर (mgr->mst_primary) अणु
		rport = drm_dp_mst_topology_get_port_validated_locked(
		    mgr->mst_primary, port);

		अगर (rport && !drm_dp_mst_topology_try_get_port(rport))
			rport = शून्य;
	पूर्ण
	mutex_unlock(&mgr->lock);
	वापस rport;
पूर्ण

अटल काष्ठा drm_dp_mst_port *drm_dp_get_port(काष्ठा drm_dp_mst_branch *mstb, u8 port_num)
अणु
	काष्ठा drm_dp_mst_port *port;
	पूर्णांक ret;

	list_क्रम_each_entry(port, &mstb->ports, next) अणु
		अगर (port->port_num == port_num) अणु
			ret = drm_dp_mst_topology_try_get_port(port);
			वापस ret ? port : शून्य;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * calculate a new RAD क्रम this MST branch device
 * अगर parent has an LCT of 2 then it has 1 nibble of RAD,
 * अगर parent has an LCT of 3 then it has 2 nibbles of RAD,
 */
अटल u8 drm_dp_calculate_rad(काष्ठा drm_dp_mst_port *port,
				 u8 *rad)
अणु
	पूर्णांक parent_lct = port->parent->lct;
	पूर्णांक shअगरt = 4;
	पूर्णांक idx = (parent_lct - 1) / 2;

	अगर (parent_lct > 1) अणु
		स_नकल(rad, port->parent->rad, idx + 1);
		shअगरt = (parent_lct % 2) ? 4 : 0;
	पूर्ण अन्यथा
		rad[0] = 0;

	rad[idx] |= port->port_num << shअगरt;
	वापस parent_lct + 1;
पूर्ण

अटल bool drm_dp_mst_is_end_device(u8 pdt, bool mcs)
अणु
	चयन (pdt) अणु
	हाल DP_PEER_DEVICE_DP_LEGACY_CONV:
	हाल DP_PEER_DEVICE_SST_SINK:
		वापस true;
	हाल DP_PEER_DEVICE_MST_BRANCHING:
		/* For sst branch device */
		अगर (!mcs)
			वापस true;

		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक
drm_dp_port_set_pdt(काष्ठा drm_dp_mst_port *port, u8 new_pdt,
		    bool new_mcs)
अणु
	काष्ठा drm_dp_mst_topology_mgr *mgr = port->mgr;
	काष्ठा drm_dp_mst_branch *mstb;
	u8 rad[8], lct;
	पूर्णांक ret = 0;

	अगर (port->pdt == new_pdt && port->mcs == new_mcs)
		वापस 0;

	/* Tearकरोwn the old pdt, अगर there is one */
	अगर (port->pdt != DP_PEER_DEVICE_NONE) अणु
		अगर (drm_dp_mst_is_end_device(port->pdt, port->mcs)) अणु
			/*
			 * If the new PDT would also have an i2c bus,
			 * करोn't bother with reरेजिस्टरing it
			 */
			अगर (new_pdt != DP_PEER_DEVICE_NONE &&
			    drm_dp_mst_is_end_device(new_pdt, new_mcs)) अणु
				port->pdt = new_pdt;
				port->mcs = new_mcs;
				वापस 0;
			पूर्ण

			/* हटाओ i2c over sideband */
			drm_dp_mst_unरेजिस्टर_i2c_bus(port);
		पूर्ण अन्यथा अणु
			mutex_lock(&mgr->lock);
			drm_dp_mst_topology_put_mstb(port->mstb);
			port->mstb = शून्य;
			mutex_unlock(&mgr->lock);
		पूर्ण
	पूर्ण

	port->pdt = new_pdt;
	port->mcs = new_mcs;

	अगर (port->pdt != DP_PEER_DEVICE_NONE) अणु
		अगर (drm_dp_mst_is_end_device(port->pdt, port->mcs)) अणु
			/* add i2c over sideband */
			ret = drm_dp_mst_रेजिस्टर_i2c_bus(port);
		पूर्ण अन्यथा अणु
			lct = drm_dp_calculate_rad(port, rad);
			mstb = drm_dp_add_mst_branch_device(lct, rad);
			अगर (!mstb) अणु
				ret = -ENOMEM;
				DRM_ERROR("Failed to create MSTB for port %p",
					  port);
				जाओ out;
			पूर्ण

			mutex_lock(&mgr->lock);
			port->mstb = mstb;
			mstb->mgr = port->mgr;
			mstb->port_parent = port;

			/*
			 * Make sure this port's memory allocation stays
			 * around until its child MSTB releases it
			 */
			drm_dp_mst_get_port_दो_स्मृति(port);
			mutex_unlock(&mgr->lock);

			/* And make sure we send a link address क्रम this */
			ret = 1;
		पूर्ण
	पूर्ण

out:
	अगर (ret < 0)
		port->pdt = DP_PEER_DEVICE_NONE;
	वापस ret;
पूर्ण

/**
 * drm_dp_mst_dpcd_पढ़ो() - पढ़ो a series of bytes from the DPCD via sideband
 * @aux: Fake sideband AUX CH
 * @offset: address of the (first) रेजिस्टर to पढ़ो
 * @buffer: buffer to store the रेजिस्टर values
 * @size: number of bytes in @buffer
 *
 * Perक्रमms the same functionality क्रम remote devices via
 * sideband messaging as drm_dp_dpcd_पढ़ो() करोes क्रम local
 * devices via actual AUX CH.
 *
 * Return: Number of bytes पढ़ो, or negative error code on failure.
 */
sमाप_प्रकार drm_dp_mst_dpcd_पढ़ो(काष्ठा drm_dp_aux *aux,
			     अचिन्हित पूर्णांक offset, व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा drm_dp_mst_port *port = container_of(aux, काष्ठा drm_dp_mst_port,
						    aux);

	वापस drm_dp_send_dpcd_पढ़ो(port->mgr, port,
				     offset, size, buffer);
पूर्ण

/**
 * drm_dp_mst_dpcd_ग_लिखो() - ग_लिखो a series of bytes to the DPCD via sideband
 * @aux: Fake sideband AUX CH
 * @offset: address of the (first) रेजिस्टर to ग_लिखो
 * @buffer: buffer containing the values to ग_लिखो
 * @size: number of bytes in @buffer
 *
 * Perक्रमms the same functionality क्रम remote devices via
 * sideband messaging as drm_dp_dpcd_ग_लिखो() करोes क्रम local
 * devices via actual AUX CH.
 *
 * Return: number of bytes written on success, negative error code on failure.
 */
sमाप_प्रकार drm_dp_mst_dpcd_ग_लिखो(काष्ठा drm_dp_aux *aux,
			      अचिन्हित पूर्णांक offset, व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा drm_dp_mst_port *port = container_of(aux, काष्ठा drm_dp_mst_port,
						    aux);

	वापस drm_dp_send_dpcd_ग_लिखो(port->mgr, port,
				      offset, size, buffer);
पूर्ण

अटल पूर्णांक drm_dp_check_mstb_guid(काष्ठा drm_dp_mst_branch *mstb, u8 *guid)
अणु
	पूर्णांक ret = 0;

	स_नकल(mstb->guid, guid, 16);

	अगर (!drm_dp_validate_guid(mstb->mgr, mstb->guid)) अणु
		अगर (mstb->port_parent) अणु
			ret = drm_dp_send_dpcd_ग_लिखो(mstb->mgr,
						     mstb->port_parent,
						     DP_GUID, 16, mstb->guid);
		पूर्ण अन्यथा अणु
			ret = drm_dp_dpcd_ग_लिखो(mstb->mgr->aux,
						DP_GUID, mstb->guid, 16);
		पूर्ण
	पूर्ण

	अगर (ret < 16 && ret > 0)
		वापस -EPROTO;

	वापस ret == 16 ? 0 : ret;
पूर्ण

अटल व्योम build_mst_prop_path(स्थिर काष्ठा drm_dp_mst_branch *mstb,
				पूर्णांक pnum,
				अक्षर *proppath,
				माप_प्रकार proppath_size)
अणु
	पूर्णांक i;
	अक्षर temp[8];

	snम_लिखो(proppath, proppath_size, "mst:%d", mstb->mgr->conn_base_id);
	क्रम (i = 0; i < (mstb->lct - 1); i++) अणु
		पूर्णांक shअगरt = (i % 2) ? 0 : 4;
		पूर्णांक port_num = (mstb->rad[i / 2] >> shअगरt) & 0xf;

		snम_लिखो(temp, माप(temp), "-%d", port_num);
		strlcat(proppath, temp, proppath_size);
	पूर्ण
	snम_लिखो(temp, माप(temp), "-%d", pnum);
	strlcat(proppath, temp, proppath_size);
पूर्ण

/**
 * drm_dp_mst_connector_late_रेजिस्टर() - Late MST connector registration
 * @connector: The MST connector
 * @port: The MST port क्रम this connector
 *
 * Helper to रेजिस्टर the remote aux device क्रम this MST port. Drivers should
 * call this from their mst connector's late_रेजिस्टर hook to enable MST aux
 * devices.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक drm_dp_mst_connector_late_रेजिस्टर(काष्ठा drm_connector *connector,
				       काष्ठा drm_dp_mst_port *port)
अणु
	DRM_DEBUG_KMS("registering %s remote bus for %s\n",
		      port->aux.name, connector->kdev->kobj.name);

	port->aux.dev = connector->kdev;
	वापस drm_dp_aux_रेजिस्टर_devnode(&port->aux);
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_connector_late_रेजिस्टर);

/**
 * drm_dp_mst_connector_early_unरेजिस्टर() - Early MST connector unregistration
 * @connector: The MST connector
 * @port: The MST port क्रम this connector
 *
 * Helper to unरेजिस्टर the remote aux device क्रम this MST port, रेजिस्टरed by
 * drm_dp_mst_connector_late_रेजिस्टर(). Drivers should call this from their mst
 * connector's early_unरेजिस्टर hook.
 */
व्योम drm_dp_mst_connector_early_unरेजिस्टर(काष्ठा drm_connector *connector,
					   काष्ठा drm_dp_mst_port *port)
अणु
	DRM_DEBUG_KMS("unregistering %s remote bus for %s\n",
		      port->aux.name, connector->kdev->kobj.name);
	drm_dp_aux_unरेजिस्टर_devnode(&port->aux);
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_connector_early_unरेजिस्टर);

अटल व्योम
drm_dp_mst_port_add_connector(काष्ठा drm_dp_mst_branch *mstb,
			      काष्ठा drm_dp_mst_port *port)
अणु
	काष्ठा drm_dp_mst_topology_mgr *mgr = port->mgr;
	अक्षर proppath[255];
	पूर्णांक ret;

	build_mst_prop_path(mstb, port->port_num, proppath, माप(proppath));
	port->connector = mgr->cbs->add_connector(mgr, port, proppath);
	अगर (!port->connector) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	अगर (port->pdt != DP_PEER_DEVICE_NONE &&
	    drm_dp_mst_is_end_device(port->pdt, port->mcs) &&
	    port->port_num >= DP_MST_LOGICAL_PORT_0)
		port->cached_edid = drm_get_edid(port->connector,
						 &port->aux.ddc);

	drm_connector_रेजिस्टर(port->connector);
	वापस;

error:
	DRM_ERROR("Failed to create connector for port %p: %d\n", port, ret);
पूर्ण

/*
 * Drop a topology reference, and unlink the port from the in-memory topology
 * layout
 */
अटल व्योम
drm_dp_mst_topology_unlink_port(काष्ठा drm_dp_mst_topology_mgr *mgr,
				काष्ठा drm_dp_mst_port *port)
अणु
	mutex_lock(&mgr->lock);
	port->parent->num_ports--;
	list_del(&port->next);
	mutex_unlock(&mgr->lock);
	drm_dp_mst_topology_put_port(port);
पूर्ण

अटल काष्ठा drm_dp_mst_port *
drm_dp_mst_add_port(काष्ठा drm_device *dev,
		    काष्ठा drm_dp_mst_topology_mgr *mgr,
		    काष्ठा drm_dp_mst_branch *mstb, u8 port_number)
अणु
	काष्ठा drm_dp_mst_port *port = kzalloc(माप(*port), GFP_KERNEL);

	अगर (!port)
		वापस शून्य;

	kref_init(&port->topology_kref);
	kref_init(&port->दो_स्मृति_kref);
	port->parent = mstb;
	port->port_num = port_number;
	port->mgr = mgr;
	port->aux.name = "DPMST";
	port->aux.dev = dev->dev;
	port->aux.is_remote = true;

	/* initialize the MST करोwnstream port's AUX crc work queue */
	drm_dp_remote_aux_init(&port->aux);

	/*
	 * Make sure the memory allocation क्रम our parent branch stays
	 * around until our own memory allocation is released
	 */
	drm_dp_mst_get_mstb_दो_स्मृति(mstb);

	वापस port;
पूर्ण

अटल पूर्णांक
drm_dp_mst_handle_link_address_port(काष्ठा drm_dp_mst_branch *mstb,
				    काष्ठा drm_device *dev,
				    काष्ठा drm_dp_link_addr_reply_port *port_msg)
अणु
	काष्ठा drm_dp_mst_topology_mgr *mgr = mstb->mgr;
	काष्ठा drm_dp_mst_port *port;
	पूर्णांक old_ddps = 0, ret;
	u8 new_pdt = DP_PEER_DEVICE_NONE;
	bool new_mcs = 0;
	bool created = false, send_link_addr = false, changed = false;

	port = drm_dp_get_port(mstb, port_msg->port_number);
	अगर (!port) अणु
		port = drm_dp_mst_add_port(dev, mgr, mstb,
					   port_msg->port_number);
		अगर (!port)
			वापस -ENOMEM;
		created = true;
		changed = true;
	पूर्ण अन्यथा अगर (!port->input && port_msg->input_port && port->connector) अणु
		/* Since port->connector can't be changed here, we create a
		 * new port अगर input_port changes from 0 to 1
		 */
		drm_dp_mst_topology_unlink_port(mgr, port);
		drm_dp_mst_topology_put_port(port);
		port = drm_dp_mst_add_port(dev, mgr, mstb,
					   port_msg->port_number);
		अगर (!port)
			वापस -ENOMEM;
		changed = true;
		created = true;
	पूर्ण अन्यथा अगर (port->input && !port_msg->input_port) अणु
		changed = true;
	पूर्ण अन्यथा अगर (port->connector) अणु
		/* We're updating a port that's exposed to userspace, so करो it
		 * under lock
		 */
		drm_modeset_lock(&mgr->base.lock, शून्य);

		old_ddps = port->ddps;
		changed = port->ddps != port_msg->ddps ||
			(port->ddps &&
			 (port->ldps != port_msg->legacy_device_plug_status ||
			  port->dpcd_rev != port_msg->dpcd_revision ||
			  port->mcs != port_msg->mcs ||
			  port->pdt != port_msg->peer_device_type ||
			  port->num_sdp_stream_sinks !=
			  port_msg->num_sdp_stream_sinks));
	पूर्ण

	port->input = port_msg->input_port;
	अगर (!port->input)
		new_pdt = port_msg->peer_device_type;
	new_mcs = port_msg->mcs;
	port->ddps = port_msg->ddps;
	port->ldps = port_msg->legacy_device_plug_status;
	port->dpcd_rev = port_msg->dpcd_revision;
	port->num_sdp_streams = port_msg->num_sdp_streams;
	port->num_sdp_stream_sinks = port_msg->num_sdp_stream_sinks;

	/* manage mstb port lists with mgr lock - take a reference
	   क्रम this list */
	अगर (created) अणु
		mutex_lock(&mgr->lock);
		drm_dp_mst_topology_get_port(port);
		list_add(&port->next, &mstb->ports);
		mstb->num_ports++;
		mutex_unlock(&mgr->lock);
	पूर्ण

	/*
	 * Reprobe PBN caps on both hotplug, and when re-probing the link
	 * क्रम our parent mstb
	 */
	अगर (old_ddps != port->ddps || !created) अणु
		अगर (port->ddps && !port->input) अणु
			ret = drm_dp_send_क्रमागत_path_resources(mgr, mstb,
							      port);
			अगर (ret == 1)
				changed = true;
		पूर्ण अन्यथा अणु
			port->full_pbn = 0;
		पूर्ण
	पूर्ण

	ret = drm_dp_port_set_pdt(port, new_pdt, new_mcs);
	अगर (ret == 1) अणु
		send_link_addr = true;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		DRM_ERROR("Failed to change PDT on port %p: %d\n",
			  port, ret);
		जाओ fail;
	पूर्ण

	/*
	 * If this port wasn't just created, then we're reprobing because
	 * we're coming out of suspend. In this हाल, always resend the link
	 * address अगर there's an MSTB on this port
	 */
	अगर (!created && port->pdt == DP_PEER_DEVICE_MST_BRANCHING &&
	    port->mcs)
		send_link_addr = true;

	अगर (port->connector)
		drm_modeset_unlock(&mgr->base.lock);
	अन्यथा अगर (!port->input)
		drm_dp_mst_port_add_connector(mstb, port);

	अगर (send_link_addr && port->mstb) अणु
		ret = drm_dp_send_link_address(mgr, port->mstb);
		अगर (ret == 1) /* MSTB below us changed */
			changed = true;
		अन्यथा अगर (ret < 0)
			जाओ fail_put;
	पूर्ण

	/* put reference to this port */
	drm_dp_mst_topology_put_port(port);
	वापस changed;

fail:
	drm_dp_mst_topology_unlink_port(mgr, port);
	अगर (port->connector)
		drm_modeset_unlock(&mgr->base.lock);
fail_put:
	drm_dp_mst_topology_put_port(port);
	वापस ret;
पूर्ण

अटल व्योम
drm_dp_mst_handle_conn_stat(काष्ठा drm_dp_mst_branch *mstb,
			    काष्ठा drm_dp_connection_status_notअगरy *conn_stat)
अणु
	काष्ठा drm_dp_mst_topology_mgr *mgr = mstb->mgr;
	काष्ठा drm_dp_mst_port *port;
	पूर्णांक old_ddps, old_input, ret, i;
	u8 new_pdt;
	bool new_mcs;
	bool करोwork = false, create_connector = false;

	port = drm_dp_get_port(mstb, conn_stat->port_number);
	अगर (!port)
		वापस;

	अगर (port->connector) अणु
		अगर (!port->input && conn_stat->input_port) अणु
			/*
			 * We can't हटाओ a connector from an alपढ़ोy exposed
			 * port, so just throw the port out and make sure we
			 * reprobe the link address of it's parent MSTB
			 */
			drm_dp_mst_topology_unlink_port(mgr, port);
			mstb->link_address_sent = false;
			करोwork = true;
			जाओ out;
		पूर्ण

		/* Locking is only needed अगर the port's exposed to userspace */
		drm_modeset_lock(&mgr->base.lock, शून्य);
	पूर्ण अन्यथा अगर (port->input && !conn_stat->input_port) अणु
		create_connector = true;
		/* Reprobe link address so we get num_sdp_streams */
		mstb->link_address_sent = false;
		करोwork = true;
	पूर्ण

	old_ddps = port->ddps;
	old_input = port->input;
	port->input = conn_stat->input_port;
	port->ldps = conn_stat->legacy_device_plug_status;
	port->ddps = conn_stat->displayport_device_plug_status;

	अगर (old_ddps != port->ddps) अणु
		अगर (port->ddps && !port->input)
			drm_dp_send_क्रमागत_path_resources(mgr, mstb, port);
		अन्यथा
			port->full_pbn = 0;
	पूर्ण

	new_pdt = port->input ? DP_PEER_DEVICE_NONE : conn_stat->peer_device_type;
	new_mcs = conn_stat->message_capability_status;
	ret = drm_dp_port_set_pdt(port, new_pdt, new_mcs);
	अगर (ret == 1) अणु
		करोwork = true;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		DRM_ERROR("Failed to change PDT for port %p: %d\n",
			  port, ret);
		करोwork = false;
	पूर्ण

	अगर (!old_input && old_ddps != port->ddps && !port->ddps) अणु
		क्रम (i = 0; i < mgr->max_payloads; i++) अणु
			काष्ठा drm_dp_vcpi *vcpi = mgr->proposed_vcpis[i];
			काष्ठा drm_dp_mst_port *port_validated;

			अगर (!vcpi)
				जारी;

			port_validated =
				container_of(vcpi, काष्ठा drm_dp_mst_port, vcpi);
			port_validated =
				drm_dp_mst_topology_get_port_validated(mgr, port_validated);
			अगर (!port_validated) अणु
				mutex_lock(&mgr->payload_lock);
				vcpi->num_slots = 0;
				mutex_unlock(&mgr->payload_lock);
			पूर्ण अन्यथा अणु
				drm_dp_mst_topology_put_port(port_validated);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (port->connector)
		drm_modeset_unlock(&mgr->base.lock);
	अन्यथा अगर (create_connector)
		drm_dp_mst_port_add_connector(mstb, port);

out:
	drm_dp_mst_topology_put_port(port);
	अगर (करोwork)
		queue_work(प्रणाली_दीर्घ_wq, &mstb->mgr->work);
पूर्ण

अटल काष्ठा drm_dp_mst_branch *drm_dp_get_mst_branch_device(काष्ठा drm_dp_mst_topology_mgr *mgr,
							       u8 lct, u8 *rad)
अणु
	काष्ठा drm_dp_mst_branch *mstb;
	काष्ठा drm_dp_mst_port *port;
	पूर्णांक i, ret;
	/* find the port by iterating करोwn */

	mutex_lock(&mgr->lock);
	mstb = mgr->mst_primary;

	अगर (!mstb)
		जाओ out;

	क्रम (i = 0; i < lct - 1; i++) अणु
		पूर्णांक shअगरt = (i % 2) ? 0 : 4;
		पूर्णांक port_num = (rad[i / 2] >> shअगरt) & 0xf;

		list_क्रम_each_entry(port, &mstb->ports, next) अणु
			अगर (port->port_num == port_num) अणु
				mstb = port->mstb;
				अगर (!mstb) अणु
					DRM_ERROR("failed to lookup MSTB with lct %d, rad %02x\n", lct, rad[0]);
					जाओ out;
				पूर्ण

				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	ret = drm_dp_mst_topology_try_get_mstb(mstb);
	अगर (!ret)
		mstb = शून्य;
out:
	mutex_unlock(&mgr->lock);
	वापस mstb;
पूर्ण

अटल काष्ठा drm_dp_mst_branch *get_mst_branch_device_by_guid_helper(
	काष्ठा drm_dp_mst_branch *mstb,
	स्थिर uपूर्णांक8_t *guid)
अणु
	काष्ठा drm_dp_mst_branch *found_mstb;
	काष्ठा drm_dp_mst_port *port;

	अगर (स_भेद(mstb->guid, guid, 16) == 0)
		वापस mstb;


	list_क्रम_each_entry(port, &mstb->ports, next) अणु
		अगर (!port->mstb)
			जारी;

		found_mstb = get_mst_branch_device_by_guid_helper(port->mstb, guid);

		अगर (found_mstb)
			वापस found_mstb;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा drm_dp_mst_branch *
drm_dp_get_mst_branch_device_by_guid(काष्ठा drm_dp_mst_topology_mgr *mgr,
				     स्थिर uपूर्णांक8_t *guid)
अणु
	काष्ठा drm_dp_mst_branch *mstb;
	पूर्णांक ret;

	/* find the port by iterating करोwn */
	mutex_lock(&mgr->lock);

	mstb = get_mst_branch_device_by_guid_helper(mgr->mst_primary, guid);
	अगर (mstb) अणु
		ret = drm_dp_mst_topology_try_get_mstb(mstb);
		अगर (!ret)
			mstb = शून्य;
	पूर्ण

	mutex_unlock(&mgr->lock);
	वापस mstb;
पूर्ण

अटल पूर्णांक drm_dp_check_and_send_link_address(काष्ठा drm_dp_mst_topology_mgr *mgr,
					       काष्ठा drm_dp_mst_branch *mstb)
अणु
	काष्ठा drm_dp_mst_port *port;
	पूर्णांक ret;
	bool changed = false;

	अगर (!mstb->link_address_sent) अणु
		ret = drm_dp_send_link_address(mgr, mstb);
		अगर (ret == 1)
			changed = true;
		अन्यथा अगर (ret < 0)
			वापस ret;
	पूर्ण

	list_क्रम_each_entry(port, &mstb->ports, next) अणु
		काष्ठा drm_dp_mst_branch *mstb_child = शून्य;

		अगर (port->input || !port->ddps)
			जारी;

		अगर (port->mstb)
			mstb_child = drm_dp_mst_topology_get_mstb_validated(
			    mgr, port->mstb);

		अगर (mstb_child) अणु
			ret = drm_dp_check_and_send_link_address(mgr,
								 mstb_child);
			drm_dp_mst_topology_put_mstb(mstb_child);
			अगर (ret == 1)
				changed = true;
			अन्यथा अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस changed;
पूर्ण

अटल व्योम drm_dp_mst_link_probe_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_dp_mst_topology_mgr *mgr =
		container_of(work, काष्ठा drm_dp_mst_topology_mgr, work);
	काष्ठा drm_device *dev = mgr->dev;
	काष्ठा drm_dp_mst_branch *mstb;
	पूर्णांक ret;
	bool clear_payload_id_table;

	mutex_lock(&mgr->probe_lock);

	mutex_lock(&mgr->lock);
	clear_payload_id_table = !mgr->payload_id_table_cleared;
	mgr->payload_id_table_cleared = true;

	mstb = mgr->mst_primary;
	अगर (mstb) अणु
		ret = drm_dp_mst_topology_try_get_mstb(mstb);
		अगर (!ret)
			mstb = शून्य;
	पूर्ण
	mutex_unlock(&mgr->lock);
	अगर (!mstb) अणु
		mutex_unlock(&mgr->probe_lock);
		वापस;
	पूर्ण

	/*
	 * Certain branch devices seem to incorrectly report an available_pbn
	 * of 0 on करोwnstream sinks, even after clearing the
	 * DP_PAYLOAD_ALLOCATE_* रेजिस्टरs in
	 * drm_dp_mst_topology_mgr_set_mst(). Namely, the CableMatters USB-C
	 * 2x DP hub. Sending a CLEAR_PAYLOAD_ID_TABLE message seems to make
	 * things work again.
	 */
	अगर (clear_payload_id_table) अणु
		DRM_DEBUG_KMS("Clearing payload ID table\n");
		drm_dp_send_clear_payload_id_table(mgr, mstb);
	पूर्ण

	ret = drm_dp_check_and_send_link_address(mgr, mstb);
	drm_dp_mst_topology_put_mstb(mstb);

	mutex_unlock(&mgr->probe_lock);
	अगर (ret > 0)
		drm_kms_helper_hotplug_event(dev);
पूर्ण

अटल bool drm_dp_validate_guid(काष्ठा drm_dp_mst_topology_mgr *mgr,
				 u8 *guid)
अणु
	u64 salt;

	अगर (स_प्रथम_inv(guid, 0, 16))
		वापस true;

	salt = get_jअगरfies_64();

	स_नकल(&guid[0], &salt, माप(u64));
	स_नकल(&guid[8], &salt, माप(u64));

	वापस false;
पूर्ण

अटल व्योम build_dpcd_पढ़ो(काष्ठा drm_dp_sideband_msg_tx *msg,
			    u8 port_num, u32 offset, u8 num_bytes)
अणु
	काष्ठा drm_dp_sideband_msg_req_body req;

	req.req_type = DP_REMOTE_DPCD_READ;
	req.u.dpcd_पढ़ो.port_number = port_num;
	req.u.dpcd_पढ़ो.dpcd_address = offset;
	req.u.dpcd_पढ़ो.num_bytes = num_bytes;
	drm_dp_encode_sideband_req(&req, msg);
पूर्ण

अटल पूर्णांक drm_dp_send_sideband_msg(काष्ठा drm_dp_mst_topology_mgr *mgr,
				    bool up, u8 *msg, पूर्णांक len)
अणु
	पूर्णांक ret;
	पूर्णांक regbase = up ? DP_SIDEBAND_MSG_UP_REP_BASE : DP_SIDEBAND_MSG_DOWN_REQ_BASE;
	पूर्णांक tosend, total, offset;
	पूर्णांक retries = 0;

retry:
	total = len;
	offset = 0;
	करो अणु
		tosend = min3(mgr->max_dpcd_transaction_bytes, 16, total);

		ret = drm_dp_dpcd_ग_लिखो(mgr->aux, regbase + offset,
					&msg[offset],
					tosend);
		अगर (ret != tosend) अणु
			अगर (ret == -EIO && retries < 5) अणु
				retries++;
				जाओ retry;
			पूर्ण
			DRM_DEBUG_KMS("failed to dpcd write %d %d\n", tosend, ret);

			वापस -EIO;
		पूर्ण
		offset += tosend;
		total -= tosend;
	पूर्ण जबतक (total > 0);
	वापस 0;
पूर्ण

अटल पूर्णांक set_hdr_from_dst_qlock(काष्ठा drm_dp_sideband_msg_hdr *hdr,
				  काष्ठा drm_dp_sideband_msg_tx *txmsg)
अणु
	काष्ठा drm_dp_mst_branch *mstb = txmsg->dst;
	u8 req_type;

	req_type = txmsg->msg[0] & 0x7f;
	अगर (req_type == DP_CONNECTION_STATUS_NOTIFY ||
		req_type == DP_RESOURCE_STATUS_NOTIFY ||
		req_type == DP_CLEAR_PAYLOAD_ID_TABLE)
		hdr->broadcast = 1;
	अन्यथा
		hdr->broadcast = 0;
	hdr->path_msg = txmsg->path_msg;
	अगर (hdr->broadcast) अणु
		hdr->lct = 1;
		hdr->lcr = 6;
	पूर्ण अन्यथा अणु
		hdr->lct = mstb->lct;
		hdr->lcr = mstb->lct - 1;
	पूर्ण

	स_नकल(hdr->rad, mstb->rad, hdr->lct / 2);

	वापस 0;
पूर्ण
/*
 * process a single block of the next message in the sideband queue
 */
अटल पूर्णांक process_single_tx_qlock(काष्ठा drm_dp_mst_topology_mgr *mgr,
				   काष्ठा drm_dp_sideband_msg_tx *txmsg,
				   bool up)
अणु
	u8 chunk[48];
	काष्ठा drm_dp_sideband_msg_hdr hdr;
	पूर्णांक len, space, idx, tosend;
	पूर्णांक ret;

	अगर (txmsg->state == DRM_DP_SIDEBAND_TX_SENT)
		वापस 0;

	स_रखो(&hdr, 0, माप(काष्ठा drm_dp_sideband_msg_hdr));

	अगर (txmsg->state == DRM_DP_SIDEBAND_TX_QUEUED)
		txmsg->state = DRM_DP_SIDEBAND_TX_START_SEND;

	/* make hdr from dst mst */
	ret = set_hdr_from_dst_qlock(&hdr, txmsg);
	अगर (ret < 0)
		वापस ret;

	/* amount left to send in this message */
	len = txmsg->cur_len - txmsg->cur_offset;

	/* 48 - sideband msg size - 1 byte क्रम data CRC, x header bytes */
	space = 48 - 1 - drm_dp_calc_sb_hdr_size(&hdr);

	tosend = min(len, space);
	अगर (len == txmsg->cur_len)
		hdr.somt = 1;
	अगर (space >= len)
		hdr.eomt = 1;


	hdr.msg_len = tosend + 1;
	drm_dp_encode_sideband_msg_hdr(&hdr, chunk, &idx);
	स_नकल(&chunk[idx], &txmsg->msg[txmsg->cur_offset], tosend);
	/* add crc at end */
	drm_dp_crc_sideband_chunk_req(&chunk[idx], tosend);
	idx += tosend + 1;

	ret = drm_dp_send_sideband_msg(mgr, up, chunk, idx);
	अगर (unlikely(ret) && drm_debug_enabled(DRM_UT_DP)) अणु
		काष्ठा drm_prपूर्णांकer p = drm_debug_prपूर्णांकer(DBG_PREFIX);

		drm_म_लिखो(&p, "sideband msg failed to send\n");
		drm_dp_mst_dump_sideband_msg_tx(&p, txmsg);
		वापस ret;
	पूर्ण

	txmsg->cur_offset += tosend;
	अगर (txmsg->cur_offset == txmsg->cur_len) अणु
		txmsg->state = DRM_DP_SIDEBAND_TX_SENT;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम process_single_करोwn_tx_qlock(काष्ठा drm_dp_mst_topology_mgr *mgr)
अणु
	काष्ठा drm_dp_sideband_msg_tx *txmsg;
	पूर्णांक ret;

	WARN_ON(!mutex_is_locked(&mgr->qlock));

	/* स्थिरruct a chunk from the first msg in the tx_msg queue */
	अगर (list_empty(&mgr->tx_msg_करोwnq))
		वापस;

	txmsg = list_first_entry(&mgr->tx_msg_करोwnq,
				 काष्ठा drm_dp_sideband_msg_tx, next);
	ret = process_single_tx_qlock(mgr, txmsg, false);
	अगर (ret < 0) अणु
		DRM_DEBUG_KMS("failed to send msg in q %d\n", ret);
		list_del(&txmsg->next);
		txmsg->state = DRM_DP_SIDEBAND_TX_TIMEOUT;
		wake_up_all(&mgr->tx_रुकोq);
	पूर्ण
पूर्ण

अटल व्योम drm_dp_queue_करोwn_tx(काष्ठा drm_dp_mst_topology_mgr *mgr,
				 काष्ठा drm_dp_sideband_msg_tx *txmsg)
अणु
	mutex_lock(&mgr->qlock);
	list_add_tail(&txmsg->next, &mgr->tx_msg_करोwnq);

	अगर (drm_debug_enabled(DRM_UT_DP)) अणु
		काष्ठा drm_prपूर्णांकer p = drm_debug_prपूर्णांकer(DBG_PREFIX);

		drm_dp_mst_dump_sideband_msg_tx(&p, txmsg);
	पूर्ण

	अगर (list_is_singular(&mgr->tx_msg_करोwnq))
		process_single_करोwn_tx_qlock(mgr);
	mutex_unlock(&mgr->qlock);
पूर्ण

अटल व्योम
drm_dp_dump_link_address(काष्ठा drm_dp_link_address_ack_reply *reply)
अणु
	काष्ठा drm_dp_link_addr_reply_port *port_reply;
	पूर्णांक i;

	क्रम (i = 0; i < reply->nports; i++) अणु
		port_reply = &reply->ports[i];
		DRM_DEBUG_KMS("port %d: input %d, pdt: %d, pn: %d, dpcd_rev: %02x, mcs: %d, ddps: %d, ldps %d, sdp %d/%d\n",
			      i,
			      port_reply->input_port,
			      port_reply->peer_device_type,
			      port_reply->port_number,
			      port_reply->dpcd_revision,
			      port_reply->mcs,
			      port_reply->ddps,
			      port_reply->legacy_device_plug_status,
			      port_reply->num_sdp_streams,
			      port_reply->num_sdp_stream_sinks);
	पूर्ण
पूर्ण

अटल पूर्णांक drm_dp_send_link_address(काष्ठा drm_dp_mst_topology_mgr *mgr,
				     काष्ठा drm_dp_mst_branch *mstb)
अणु
	काष्ठा drm_dp_sideband_msg_tx *txmsg;
	काष्ठा drm_dp_link_address_ack_reply *reply;
	काष्ठा drm_dp_mst_port *port, *पंचांगp;
	पूर्णांक i, ret, port_mask = 0;
	bool changed = false;

	txmsg = kzalloc(माप(*txmsg), GFP_KERNEL);
	अगर (!txmsg)
		वापस -ENOMEM;

	txmsg->dst = mstb;
	build_link_address(txmsg);

	mstb->link_address_sent = true;
	drm_dp_queue_करोwn_tx(mgr, txmsg);

	/* FIXME: Actually करो some real error handling here */
	ret = drm_dp_mst_रुको_tx_reply(mstb, txmsg);
	अगर (ret <= 0) अणु
		DRM_ERROR("Sending link address failed with %d\n", ret);
		जाओ out;
	पूर्ण
	अगर (txmsg->reply.reply_type == DP_SIDEBAND_REPLY_NAK) अणु
		DRM_ERROR("link address NAK received\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	reply = &txmsg->reply.u.link_addr;
	DRM_DEBUG_KMS("link address reply: %d\n", reply->nports);
	drm_dp_dump_link_address(reply);

	ret = drm_dp_check_mstb_guid(mstb, reply->guid);
	अगर (ret) अणु
		अक्षर buf[64];

		drm_dp_mst_rad_to_str(mstb->rad, mstb->lct, buf, माप(buf));
		DRM_ERROR("GUID check on %s failed: %d\n",
			  buf, ret);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < reply->nports; i++) अणु
		port_mask |= BIT(reply->ports[i].port_number);
		ret = drm_dp_mst_handle_link_address_port(mstb, mgr->dev,
							  &reply->ports[i]);
		अगर (ret == 1)
			changed = true;
		अन्यथा अगर (ret < 0)
			जाओ out;
	पूर्ण

	/* Prune any ports that are currently a part of mstb in our in-memory
	 * topology, but were not seen in this link address. Usually this
	 * means that they were हटाओd जबतक the topology was out of sync,
	 * e.g. during suspend/resume
	 */
	mutex_lock(&mgr->lock);
	list_क्रम_each_entry_safe(port, पंचांगp, &mstb->ports, next) अणु
		अगर (port_mask & BIT(port->port_num))
			जारी;

		DRM_DEBUG_KMS("port %d was not in link address, removing\n",
			      port->port_num);
		list_del(&port->next);
		drm_dp_mst_topology_put_port(port);
		changed = true;
	पूर्ण
	mutex_unlock(&mgr->lock);

out:
	अगर (ret <= 0)
		mstb->link_address_sent = false;
	kमुक्त(txmsg);
	वापस ret < 0 ? ret : changed;
पूर्ण

अटल व्योम
drm_dp_send_clear_payload_id_table(काष्ठा drm_dp_mst_topology_mgr *mgr,
				   काष्ठा drm_dp_mst_branch *mstb)
अणु
	काष्ठा drm_dp_sideband_msg_tx *txmsg;
	पूर्णांक ret;

	txmsg = kzalloc(माप(*txmsg), GFP_KERNEL);
	अगर (!txmsg)
		वापस;

	txmsg->dst = mstb;
	build_clear_payload_id_table(txmsg);

	drm_dp_queue_करोwn_tx(mgr, txmsg);

	ret = drm_dp_mst_रुको_tx_reply(mstb, txmsg);
	अगर (ret > 0 && txmsg->reply.reply_type == DP_SIDEBAND_REPLY_NAK)
		DRM_DEBUG_KMS("clear payload table id nak received\n");

	kमुक्त(txmsg);
पूर्ण

अटल पूर्णांक
drm_dp_send_क्रमागत_path_resources(काष्ठा drm_dp_mst_topology_mgr *mgr,
				काष्ठा drm_dp_mst_branch *mstb,
				काष्ठा drm_dp_mst_port *port)
अणु
	काष्ठा drm_dp_क्रमागत_path_resources_ack_reply *path_res;
	काष्ठा drm_dp_sideband_msg_tx *txmsg;
	पूर्णांक ret;

	txmsg = kzalloc(माप(*txmsg), GFP_KERNEL);
	अगर (!txmsg)
		वापस -ENOMEM;

	txmsg->dst = mstb;
	build_क्रमागत_path_resources(txmsg, port->port_num);

	drm_dp_queue_करोwn_tx(mgr, txmsg);

	ret = drm_dp_mst_रुको_tx_reply(mstb, txmsg);
	अगर (ret > 0) अणु
		ret = 0;
		path_res = &txmsg->reply.u.path_resources;

		अगर (txmsg->reply.reply_type == DP_SIDEBAND_REPLY_NAK) अणु
			DRM_DEBUG_KMS("enum path resources nak received\n");
		पूर्ण अन्यथा अणु
			अगर (port->port_num != path_res->port_number)
				DRM_ERROR("got incorrect port in response\n");

			DRM_DEBUG_KMS("enum path resources %d: %d %d\n",
				      path_res->port_number,
				      path_res->full_payload_bw_number,
				      path_res->avail_payload_bw_number);

			/*
			 * If something changed, make sure we send a
			 * hotplug
			 */
			अगर (port->full_pbn != path_res->full_payload_bw_number ||
			    port->fec_capable != path_res->fec_capable)
				ret = 1;

			port->full_pbn = path_res->full_payload_bw_number;
			port->fec_capable = path_res->fec_capable;
		पूर्ण
	पूर्ण

	kमुक्त(txmsg);
	वापस ret;
पूर्ण

अटल काष्ठा drm_dp_mst_port *drm_dp_get_last_connected_port_to_mstb(काष्ठा drm_dp_mst_branch *mstb)
अणु
	अगर (!mstb->port_parent)
		वापस शून्य;

	अगर (mstb->port_parent->mstb != mstb)
		वापस mstb->port_parent;

	वापस drm_dp_get_last_connected_port_to_mstb(mstb->port_parent->parent);
पूर्ण

/*
 * Searches upwards in the topology starting from mstb to try to find the
 * बंदst available parent of mstb that's still connected to the rest of the
 * topology. This can be used in order to perक्रमm operations like releasing
 * payloads, where the branch device which owned the payload may no दीर्घer be
 * around and thus would require that the payload on the last living relative
 * be मुक्तd instead.
 */
अटल काष्ठा drm_dp_mst_branch *
drm_dp_get_last_connected_port_and_mstb(काष्ठा drm_dp_mst_topology_mgr *mgr,
					काष्ठा drm_dp_mst_branch *mstb,
					पूर्णांक *port_num)
अणु
	काष्ठा drm_dp_mst_branch *rmstb = शून्य;
	काष्ठा drm_dp_mst_port *found_port;

	mutex_lock(&mgr->lock);
	अगर (!mgr->mst_primary)
		जाओ out;

	करो अणु
		found_port = drm_dp_get_last_connected_port_to_mstb(mstb);
		अगर (!found_port)
			अवरोध;

		अगर (drm_dp_mst_topology_try_get_mstb(found_port->parent)) अणु
			rmstb = found_port->parent;
			*port_num = found_port->port_num;
		पूर्ण अन्यथा अणु
			/* Search again, starting from this parent */
			mstb = found_port->parent;
		पूर्ण
	पूर्ण जबतक (!rmstb);
out:
	mutex_unlock(&mgr->lock);
	वापस rmstb;
पूर्ण

अटल पूर्णांक drm_dp_payload_send_msg(काष्ठा drm_dp_mst_topology_mgr *mgr,
				   काष्ठा drm_dp_mst_port *port,
				   पूर्णांक id,
				   पूर्णांक pbn)
अणु
	काष्ठा drm_dp_sideband_msg_tx *txmsg;
	काष्ठा drm_dp_mst_branch *mstb;
	पूर्णांक ret, port_num;
	u8 sinks[DRM_DP_MAX_SDP_STREAMS];
	पूर्णांक i;

	port_num = port->port_num;
	mstb = drm_dp_mst_topology_get_mstb_validated(mgr, port->parent);
	अगर (!mstb) अणु
		mstb = drm_dp_get_last_connected_port_and_mstb(mgr,
							       port->parent,
							       &port_num);

		अगर (!mstb)
			वापस -EINVAL;
	पूर्ण

	txmsg = kzalloc(माप(*txmsg), GFP_KERNEL);
	अगर (!txmsg) अणु
		ret = -ENOMEM;
		जाओ fail_put;
	पूर्ण

	क्रम (i = 0; i < port->num_sdp_streams; i++)
		sinks[i] = i;

	txmsg->dst = mstb;
	build_allocate_payload(txmsg, port_num,
			       id,
			       pbn, port->num_sdp_streams, sinks);

	drm_dp_queue_करोwn_tx(mgr, txmsg);

	/*
	 * FIXME: there is a small chance that between getting the last
	 * connected mstb and sending the payload message, the last connected
	 * mstb could also be हटाओd from the topology. In the future, this
	 * needs to be fixed by restarting the
	 * drm_dp_get_last_connected_port_and_mstb() search in the event of a
	 * समयout अगर the topology is still connected to the प्रणाली.
	 */
	ret = drm_dp_mst_रुको_tx_reply(mstb, txmsg);
	अगर (ret > 0) अणु
		अगर (txmsg->reply.reply_type == DP_SIDEBAND_REPLY_NAK)
			ret = -EINVAL;
		अन्यथा
			ret = 0;
	पूर्ण
	kमुक्त(txmsg);
fail_put:
	drm_dp_mst_topology_put_mstb(mstb);
	वापस ret;
पूर्ण

पूर्णांक drm_dp_send_घातer_upकरोwn_phy(काष्ठा drm_dp_mst_topology_mgr *mgr,
				 काष्ठा drm_dp_mst_port *port, bool घातer_up)
अणु
	काष्ठा drm_dp_sideband_msg_tx *txmsg;
	पूर्णांक ret;

	port = drm_dp_mst_topology_get_port_validated(mgr, port);
	अगर (!port)
		वापस -EINVAL;

	txmsg = kzalloc(माप(*txmsg), GFP_KERNEL);
	अगर (!txmsg) अणु
		drm_dp_mst_topology_put_port(port);
		वापस -ENOMEM;
	पूर्ण

	txmsg->dst = port->parent;
	build_घातer_upकरोwn_phy(txmsg, port->port_num, घातer_up);
	drm_dp_queue_करोwn_tx(mgr, txmsg);

	ret = drm_dp_mst_रुको_tx_reply(port->parent, txmsg);
	अगर (ret > 0) अणु
		अगर (txmsg->reply.reply_type == DP_SIDEBAND_REPLY_NAK)
			ret = -EINVAL;
		अन्यथा
			ret = 0;
	पूर्ण
	kमुक्त(txmsg);
	drm_dp_mst_topology_put_port(port);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_dp_send_घातer_upकरोwn_phy);

पूर्णांक drm_dp_send_query_stream_enc_status(काष्ठा drm_dp_mst_topology_mgr *mgr,
		काष्ठा drm_dp_mst_port *port,
		काष्ठा drm_dp_query_stream_enc_status_ack_reply *status)
अणु
	काष्ठा drm_dp_sideband_msg_tx *txmsg;
	u8 nonce[7];
	पूर्णांक ret;

	txmsg = kzalloc(माप(*txmsg), GFP_KERNEL);
	अगर (!txmsg)
		वापस -ENOMEM;

	port = drm_dp_mst_topology_get_port_validated(mgr, port);
	अगर (!port) अणु
		ret = -EINVAL;
		जाओ out_get_port;
	पूर्ण

	get_अक्रमom_bytes(nonce, माप(nonce));

	/*
	 * "Source device tarमाला_लो the QUERY_STREAM_ENCRYPTION_STATUS message
	 *  transaction at the MST Branch device directly connected to the
	 *  Source"
	 */
	txmsg->dst = mgr->mst_primary;

	build_query_stream_enc_status(txmsg, port->vcpi.vcpi, nonce);

	drm_dp_queue_करोwn_tx(mgr, txmsg);

	ret = drm_dp_mst_रुको_tx_reply(mgr->mst_primary, txmsg);
	अगर (ret < 0) अणु
		जाओ out;
	पूर्ण अन्यथा अगर (txmsg->reply.reply_type == DP_SIDEBAND_REPLY_NAK) अणु
		drm_dbg_kms(mgr->dev, "query encryption status nak received\n");
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	ret = 0;
	स_नकल(status, &txmsg->reply.u.enc_status, माप(*status));

out:
	drm_dp_mst_topology_put_port(port);
out_get_port:
	kमुक्त(txmsg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_dp_send_query_stream_enc_status);

अटल पूर्णांक drm_dp_create_payload_step1(काष्ठा drm_dp_mst_topology_mgr *mgr,
				       पूर्णांक id,
				       काष्ठा drm_dp_payload *payload)
अणु
	पूर्णांक ret;

	ret = drm_dp_dpcd_ग_लिखो_payload(mgr, id, payload);
	अगर (ret < 0) अणु
		payload->payload_state = 0;
		वापस ret;
	पूर्ण
	payload->payload_state = DP_PAYLOAD_LOCAL;
	वापस 0;
पूर्ण

अटल पूर्णांक drm_dp_create_payload_step2(काष्ठा drm_dp_mst_topology_mgr *mgr,
				       काष्ठा drm_dp_mst_port *port,
				       पूर्णांक id,
				       काष्ठा drm_dp_payload *payload)
अणु
	पूर्णांक ret;

	ret = drm_dp_payload_send_msg(mgr, port, id, port->vcpi.pbn);
	अगर (ret < 0)
		वापस ret;
	payload->payload_state = DP_PAYLOAD_REMOTE;
	वापस ret;
पूर्ण

अटल पूर्णांक drm_dp_destroy_payload_step1(काष्ठा drm_dp_mst_topology_mgr *mgr,
					काष्ठा drm_dp_mst_port *port,
					पूर्णांक id,
					काष्ठा drm_dp_payload *payload)
अणु
	DRM_DEBUG_KMS("\n");
	/* it's okay क्रम these to fail */
	अगर (port) अणु
		drm_dp_payload_send_msg(mgr, port, id, 0);
	पूर्ण

	drm_dp_dpcd_ग_लिखो_payload(mgr, id, payload);
	payload->payload_state = DP_PAYLOAD_DELETE_LOCAL;
	वापस 0;
पूर्ण

अटल पूर्णांक drm_dp_destroy_payload_step2(काष्ठा drm_dp_mst_topology_mgr *mgr,
					पूर्णांक id,
					काष्ठा drm_dp_payload *payload)
अणु
	payload->payload_state = 0;
	वापस 0;
पूर्ण

/**
 * drm_dp_update_payload_part1() - Execute payload update part 1
 * @mgr: manager to use.
 *
 * This iterates over all proposed भव channels, and tries to
 * allocate space in the link क्रम them. For 0->slots transitions,
 * this step just ग_लिखोs the VCPI to the MST device. For slots->0
 * transitions, this ग_लिखोs the updated VCPIs and हटाओs the
 * remote VC payloads.
 *
 * after calling this the driver should generate ACT and payload
 * packets.
 */
पूर्णांक drm_dp_update_payload_part1(काष्ठा drm_dp_mst_topology_mgr *mgr)
अणु
	काष्ठा drm_dp_payload req_payload;
	काष्ठा drm_dp_mst_port *port;
	पूर्णांक i, j;
	पूर्णांक cur_slots = 1;

	mutex_lock(&mgr->payload_lock);
	क्रम (i = 0; i < mgr->max_payloads; i++) अणु
		काष्ठा drm_dp_vcpi *vcpi = mgr->proposed_vcpis[i];
		काष्ठा drm_dp_payload *payload = &mgr->payloads[i];
		bool put_port = false;

		/* solve the current payloads - compare to the hw ones
		   - update the hw view */
		req_payload.start_slot = cur_slots;
		अगर (vcpi) अणु
			port = container_of(vcpi, काष्ठा drm_dp_mst_port,
					    vcpi);

			/* Validated ports करोn't matter if we're releasing
			 * VCPI
			 */
			अगर (vcpi->num_slots) अणु
				port = drm_dp_mst_topology_get_port_validated(
				    mgr, port);
				अगर (!port) अणु
					mutex_unlock(&mgr->payload_lock);
					वापस -EINVAL;
				पूर्ण
				put_port = true;
			पूर्ण

			req_payload.num_slots = vcpi->num_slots;
			req_payload.vcpi = vcpi->vcpi;
		पूर्ण अन्यथा अणु
			port = शून्य;
			req_payload.num_slots = 0;
		पूर्ण

		payload->start_slot = req_payload.start_slot;
		/* work out what is required to happen with this payload */
		अगर (payload->num_slots != req_payload.num_slots) अणु

			/* need to push an update क्रम this payload */
			अगर (req_payload.num_slots) अणु
				drm_dp_create_payload_step1(mgr, vcpi->vcpi,
							    &req_payload);
				payload->num_slots = req_payload.num_slots;
				payload->vcpi = req_payload.vcpi;

			पूर्ण अन्यथा अगर (payload->num_slots) अणु
				payload->num_slots = 0;
				drm_dp_destroy_payload_step1(mgr, port,
							     payload->vcpi,
							     payload);
				req_payload.payload_state =
					payload->payload_state;
				payload->start_slot = 0;
			पूर्ण
			payload->payload_state = req_payload.payload_state;
		पूर्ण
		cur_slots += req_payload.num_slots;

		अगर (put_port)
			drm_dp_mst_topology_put_port(port);
	पूर्ण

	क्रम (i = 0; i < mgr->max_payloads; /* करो nothing */) अणु
		अगर (mgr->payloads[i].payload_state != DP_PAYLOAD_DELETE_LOCAL) अणु
			i++;
			जारी;
		पूर्ण

		DRM_DEBUG_KMS("removing payload %d\n", i);
		क्रम (j = i; j < mgr->max_payloads - 1; j++) अणु
			mgr->payloads[j] = mgr->payloads[j + 1];
			mgr->proposed_vcpis[j] = mgr->proposed_vcpis[j + 1];

			अगर (mgr->proposed_vcpis[j] &&
			    mgr->proposed_vcpis[j]->num_slots) अणु
				set_bit(j + 1, &mgr->payload_mask);
			पूर्ण अन्यथा अणु
				clear_bit(j + 1, &mgr->payload_mask);
			पूर्ण
		पूर्ण

		स_रखो(&mgr->payloads[mgr->max_payloads - 1], 0,
		       माप(काष्ठा drm_dp_payload));
		mgr->proposed_vcpis[mgr->max_payloads - 1] = शून्य;
		clear_bit(mgr->max_payloads, &mgr->payload_mask);
	पूर्ण
	mutex_unlock(&mgr->payload_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_update_payload_part1);

/**
 * drm_dp_update_payload_part2() - Execute payload update part 2
 * @mgr: manager to use.
 *
 * This iterates over all proposed भव channels, and tries to
 * allocate space in the link क्रम them. For 0->slots transitions,
 * this step ग_लिखोs the remote VC payload commands. For slots->0
 * this just resets some पूर्णांकernal state.
 */
पूर्णांक drm_dp_update_payload_part2(काष्ठा drm_dp_mst_topology_mgr *mgr)
अणु
	काष्ठा drm_dp_mst_port *port;
	पूर्णांक i;
	पूर्णांक ret = 0;

	mutex_lock(&mgr->payload_lock);
	क्रम (i = 0; i < mgr->max_payloads; i++) अणु

		अगर (!mgr->proposed_vcpis[i])
			जारी;

		port = container_of(mgr->proposed_vcpis[i], काष्ठा drm_dp_mst_port, vcpi);

		DRM_DEBUG_KMS("payload %d %d\n", i, mgr->payloads[i].payload_state);
		अगर (mgr->payloads[i].payload_state == DP_PAYLOAD_LOCAL) अणु
			ret = drm_dp_create_payload_step2(mgr, port, mgr->proposed_vcpis[i]->vcpi, &mgr->payloads[i]);
		पूर्ण अन्यथा अगर (mgr->payloads[i].payload_state == DP_PAYLOAD_DELETE_LOCAL) अणु
			ret = drm_dp_destroy_payload_step2(mgr, mgr->proposed_vcpis[i]->vcpi, &mgr->payloads[i]);
		पूर्ण
		अगर (ret) अणु
			mutex_unlock(&mgr->payload_lock);
			वापस ret;
		पूर्ण
	पूर्ण
	mutex_unlock(&mgr->payload_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_update_payload_part2);

अटल पूर्णांक drm_dp_send_dpcd_पढ़ो(काष्ठा drm_dp_mst_topology_mgr *mgr,
				 काष्ठा drm_dp_mst_port *port,
				 पूर्णांक offset, पूर्णांक size, u8 *bytes)
अणु
	पूर्णांक ret = 0;
	काष्ठा drm_dp_sideband_msg_tx *txmsg;
	काष्ठा drm_dp_mst_branch *mstb;

	mstb = drm_dp_mst_topology_get_mstb_validated(mgr, port->parent);
	अगर (!mstb)
		वापस -EINVAL;

	txmsg = kzalloc(माप(*txmsg), GFP_KERNEL);
	अगर (!txmsg) अणु
		ret = -ENOMEM;
		जाओ fail_put;
	पूर्ण

	build_dpcd_पढ़ो(txmsg, port->port_num, offset, size);
	txmsg->dst = port->parent;

	drm_dp_queue_करोwn_tx(mgr, txmsg);

	ret = drm_dp_mst_रुको_tx_reply(mstb, txmsg);
	अगर (ret < 0)
		जाओ fail_मुक्त;

	/* DPCD पढ़ो should never be NACKed */
	अगर (txmsg->reply.reply_type == 1) अणु
		DRM_ERROR("mstb %p port %d: DPCD read on addr 0x%x for %d bytes NAKed\n",
			  mstb, port->port_num, offset, size);
		ret = -EIO;
		जाओ fail_मुक्त;
	पूर्ण

	अगर (txmsg->reply.u.remote_dpcd_पढ़ो_ack.num_bytes != size) अणु
		ret = -EPROTO;
		जाओ fail_मुक्त;
	पूर्ण

	ret = min_t(माप_प्रकार, txmsg->reply.u.remote_dpcd_पढ़ो_ack.num_bytes,
		    size);
	स_नकल(bytes, txmsg->reply.u.remote_dpcd_पढ़ो_ack.bytes, ret);

fail_मुक्त:
	kमुक्त(txmsg);
fail_put:
	drm_dp_mst_topology_put_mstb(mstb);

	वापस ret;
पूर्ण

अटल पूर्णांक drm_dp_send_dpcd_ग_लिखो(काष्ठा drm_dp_mst_topology_mgr *mgr,
				  काष्ठा drm_dp_mst_port *port,
				  पूर्णांक offset, पूर्णांक size, u8 *bytes)
अणु
	पूर्णांक ret;
	काष्ठा drm_dp_sideband_msg_tx *txmsg;
	काष्ठा drm_dp_mst_branch *mstb;

	mstb = drm_dp_mst_topology_get_mstb_validated(mgr, port->parent);
	अगर (!mstb)
		वापस -EINVAL;

	txmsg = kzalloc(माप(*txmsg), GFP_KERNEL);
	अगर (!txmsg) अणु
		ret = -ENOMEM;
		जाओ fail_put;
	पूर्ण

	build_dpcd_ग_लिखो(txmsg, port->port_num, offset, size, bytes);
	txmsg->dst = mstb;

	drm_dp_queue_करोwn_tx(mgr, txmsg);

	ret = drm_dp_mst_रुको_tx_reply(mstb, txmsg);
	अगर (ret > 0) अणु
		अगर (txmsg->reply.reply_type == DP_SIDEBAND_REPLY_NAK)
			ret = -EIO;
		अन्यथा
			ret = size;
	पूर्ण

	kमुक्त(txmsg);
fail_put:
	drm_dp_mst_topology_put_mstb(mstb);
	वापस ret;
पूर्ण

अटल पूर्णांक drm_dp_encode_up_ack_reply(काष्ठा drm_dp_sideband_msg_tx *msg, u8 req_type)
अणु
	काष्ठा drm_dp_sideband_msg_reply_body reply;

	reply.reply_type = DP_SIDEBAND_REPLY_ACK;
	reply.req_type = req_type;
	drm_dp_encode_sideband_reply(&reply, msg);
	वापस 0;
पूर्ण

अटल पूर्णांक drm_dp_send_up_ack_reply(काष्ठा drm_dp_mst_topology_mgr *mgr,
				    काष्ठा drm_dp_mst_branch *mstb,
				    पूर्णांक req_type, bool broadcast)
अणु
	काष्ठा drm_dp_sideband_msg_tx *txmsg;

	txmsg = kzalloc(माप(*txmsg), GFP_KERNEL);
	अगर (!txmsg)
		वापस -ENOMEM;

	txmsg->dst = mstb;
	drm_dp_encode_up_ack_reply(txmsg, req_type);

	mutex_lock(&mgr->qlock);
	/* स्थिरruct a chunk from the first msg in the tx_msg queue */
	process_single_tx_qlock(mgr, txmsg, true);
	mutex_unlock(&mgr->qlock);

	kमुक्त(txmsg);
	वापस 0;
पूर्ण

/**
 * drm_dp_get_vc_payload_bw - get the VC payload BW क्रम an MST link
 * @link_rate: link rate in 10kbits/s units
 * @link_lane_count: lane count
 *
 * Calculate the total bandwidth of a MultiStream Transport link. The वापसed
 * value is in units of PBNs/(बारlots/1 MTP). This value can be used to
 * convert the number of PBNs required क्रम a given stream to the number of
 * बारlots this stream requires in each MTP.
 */
पूर्णांक drm_dp_get_vc_payload_bw(पूर्णांक link_rate, पूर्णांक link_lane_count)
अणु
	अगर (link_rate == 0 || link_lane_count == 0)
		DRM_DEBUG_KMS("invalid link rate/lane count: (%d / %d)\n",
			      link_rate, link_lane_count);

	/* See DP v2.0 2.6.4.2, VCPayload_Bandwidth_क्रम_OneTimeSlotPer_MTP_Allocation */
	वापस link_rate * link_lane_count / 54000;
पूर्ण
EXPORT_SYMBOL(drm_dp_get_vc_payload_bw);

/**
 * drm_dp_पढ़ो_mst_cap() - check whether or not a sink supports MST
 * @aux: The DP AUX channel to use
 * @dpcd: A cached copy of the DPCD capabilities क्रम this sink
 *
 * Returns: %True अगर the sink supports MST, %false otherwise
 */
bool drm_dp_पढ़ो_mst_cap(काष्ठा drm_dp_aux *aux,
			 स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	u8 msपंचांग_cap;

	अगर (dpcd[DP_DPCD_REV] < DP_DPCD_REV_12)
		वापस false;

	अगर (drm_dp_dpcd_पढ़ोb(aux, DP_MSTM_CAP, &msपंचांग_cap) != 1)
		वापस false;

	वापस msपंचांग_cap & DP_MST_CAP;
पूर्ण
EXPORT_SYMBOL(drm_dp_पढ़ो_mst_cap);

/**
 * drm_dp_mst_topology_mgr_set_mst() - Set the MST state क्रम a topology manager
 * @mgr: manager to set state क्रम
 * @mst_state: true to enable MST on this connector - false to disable.
 *
 * This is called by the driver when it detects an MST capable device plugged
 * पूर्णांकo a DP MST capable port, or when a DP MST capable device is unplugged.
 */
पूर्णांक drm_dp_mst_topology_mgr_set_mst(काष्ठा drm_dp_mst_topology_mgr *mgr, bool mst_state)
अणु
	पूर्णांक ret = 0;
	काष्ठा drm_dp_mst_branch *mstb = शून्य;

	mutex_lock(&mgr->payload_lock);
	mutex_lock(&mgr->lock);
	अगर (mst_state == mgr->mst_state)
		जाओ out_unlock;

	mgr->mst_state = mst_state;
	/* set the device पूर्णांकo MST mode */
	अगर (mst_state) अणु
		काष्ठा drm_dp_payload reset_pay;

		WARN_ON(mgr->mst_primary);

		/* get dpcd info */
		ret = drm_dp_dpcd_पढ़ो(mgr->aux, DP_DPCD_REV, mgr->dpcd, DP_RECEIVER_CAP_SIZE);
		अगर (ret != DP_RECEIVER_CAP_SIZE) अणु
			DRM_DEBUG_KMS("failed to read DPCD\n");
			जाओ out_unlock;
		पूर्ण

		mgr->pbn_भाग = drm_dp_get_vc_payload_bw(drm_dp_bw_code_to_link_rate(mgr->dpcd[1]),
							mgr->dpcd[2] & DP_MAX_LANE_COUNT_MASK);
		अगर (mgr->pbn_भाग == 0) अणु
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		/* add initial branch device at LCT 1 */
		mstb = drm_dp_add_mst_branch_device(1, शून्य);
		अगर (mstb == शून्य) अणु
			ret = -ENOMEM;
			जाओ out_unlock;
		पूर्ण
		mstb->mgr = mgr;

		/* give this the मुख्य reference */
		mgr->mst_primary = mstb;
		drm_dp_mst_topology_get_mstb(mgr->mst_primary);

		ret = drm_dp_dpcd_ग_लिखोb(mgr->aux, DP_MSTM_CTRL,
					 DP_MST_EN |
					 DP_UP_REQ_EN |
					 DP_UPSTREAM_IS_SRC);
		अगर (ret < 0)
			जाओ out_unlock;

		reset_pay.start_slot = 0;
		reset_pay.num_slots = 0x3f;
		drm_dp_dpcd_ग_लिखो_payload(mgr, 0, &reset_pay);

		queue_work(प्रणाली_दीर्घ_wq, &mgr->work);

		ret = 0;
	पूर्ण अन्यथा अणु
		/* disable MST on the device */
		mstb = mgr->mst_primary;
		mgr->mst_primary = शून्य;
		/* this can fail अगर the device is gone */
		drm_dp_dpcd_ग_लिखोb(mgr->aux, DP_MSTM_CTRL, 0);
		ret = 0;
		स_रखो(mgr->payloads, 0,
		       mgr->max_payloads * माप(mgr->payloads[0]));
		स_रखो(mgr->proposed_vcpis, 0,
		       mgr->max_payloads * माप(mgr->proposed_vcpis[0]));
		mgr->payload_mask = 0;
		set_bit(0, &mgr->payload_mask);
		mgr->vcpi_mask = 0;
		mgr->payload_id_table_cleared = false;
	पूर्ण

out_unlock:
	mutex_unlock(&mgr->lock);
	mutex_unlock(&mgr->payload_lock);
	अगर (mstb)
		drm_dp_mst_topology_put_mstb(mstb);
	वापस ret;

पूर्ण
EXPORT_SYMBOL(drm_dp_mst_topology_mgr_set_mst);

अटल व्योम
drm_dp_mst_topology_mgr_invalidate_mstb(काष्ठा drm_dp_mst_branch *mstb)
अणु
	काष्ठा drm_dp_mst_port *port;

	/* The link address will need to be re-sent on resume */
	mstb->link_address_sent = false;

	list_क्रम_each_entry(port, &mstb->ports, next)
		अगर (port->mstb)
			drm_dp_mst_topology_mgr_invalidate_mstb(port->mstb);
पूर्ण

/**
 * drm_dp_mst_topology_mgr_suspend() - suspend the MST manager
 * @mgr: manager to suspend
 *
 * This function tells the MST device that we can't handle UP messages
 * anymore. This should stop it from sending any since we are suspended.
 */
व्योम drm_dp_mst_topology_mgr_suspend(काष्ठा drm_dp_mst_topology_mgr *mgr)
अणु
	mutex_lock(&mgr->lock);
	drm_dp_dpcd_ग_लिखोb(mgr->aux, DP_MSTM_CTRL,
			   DP_MST_EN | DP_UPSTREAM_IS_SRC);
	mutex_unlock(&mgr->lock);
	flush_work(&mgr->up_req_work);
	flush_work(&mgr->work);
	flush_work(&mgr->delayed_destroy_work);

	mutex_lock(&mgr->lock);
	अगर (mgr->mst_state && mgr->mst_primary)
		drm_dp_mst_topology_mgr_invalidate_mstb(mgr->mst_primary);
	mutex_unlock(&mgr->lock);
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_topology_mgr_suspend);

/**
 * drm_dp_mst_topology_mgr_resume() - resume the MST manager
 * @mgr: manager to resume
 * @sync: whether or not to perक्रमm topology reprobing synchronously
 *
 * This will fetch DPCD and see अगर the device is still there,
 * अगर it is, it will reग_लिखो the MSTM control bits, and वापस.
 *
 * If the device fails this वापसs -1, and the driver should करो
 * a full MST reprobe, in हाल we were unकरोcked.
 *
 * During प्रणाली resume (where it is assumed that the driver will be calling
 * drm_atomic_helper_resume()) this function should be called beक्रमehand with
 * @sync set to true. In contexts like runसमय resume where the driver is not
 * expected to be calling drm_atomic_helper_resume(), this function should be
 * called with @sync set to false in order to aव्योम deadlocking.
 *
 * Returns: -1 अगर the MST topology was हटाओd जबतक we were suspended, 0
 * otherwise.
 */
पूर्णांक drm_dp_mst_topology_mgr_resume(काष्ठा drm_dp_mst_topology_mgr *mgr,
				   bool sync)
अणु
	पूर्णांक ret;
	u8 guid[16];

	mutex_lock(&mgr->lock);
	अगर (!mgr->mst_primary)
		जाओ out_fail;

	ret = drm_dp_dpcd_पढ़ो(mgr->aux, DP_DPCD_REV, mgr->dpcd,
			       DP_RECEIVER_CAP_SIZE);
	अगर (ret != DP_RECEIVER_CAP_SIZE) अणु
		DRM_DEBUG_KMS("dpcd read failed - undocked during suspend?\n");
		जाओ out_fail;
	पूर्ण

	ret = drm_dp_dpcd_ग_लिखोb(mgr->aux, DP_MSTM_CTRL,
				 DP_MST_EN |
				 DP_UP_REQ_EN |
				 DP_UPSTREAM_IS_SRC);
	अगर (ret < 0) अणु
		DRM_DEBUG_KMS("mst write failed - undocked during suspend?\n");
		जाओ out_fail;
	पूर्ण

	/* Some hubs क्रमget their guids after they resume */
	ret = drm_dp_dpcd_पढ़ो(mgr->aux, DP_GUID, guid, 16);
	अगर (ret != 16) अणु
		DRM_DEBUG_KMS("dpcd read failed - undocked during suspend?\n");
		जाओ out_fail;
	पूर्ण

	ret = drm_dp_check_mstb_guid(mgr->mst_primary, guid);
	अगर (ret) अणु
		DRM_DEBUG_KMS("check mstb failed - undocked during suspend?\n");
		जाओ out_fail;
	पूर्ण

	/*
	 * For the final step of resuming the topology, we need to bring the
	 * state of our in-memory topology back पूर्णांकo sync with reality. So,
	 * restart the probing process as अगर we're probing a new hub
	 */
	queue_work(प्रणाली_दीर्घ_wq, &mgr->work);
	mutex_unlock(&mgr->lock);

	अगर (sync) अणु
		DRM_DEBUG_KMS("Waiting for link probe work to finish re-syncing topology...\n");
		flush_work(&mgr->work);
	पूर्ण

	वापस 0;

out_fail:
	mutex_unlock(&mgr->lock);
	वापस -1;
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_topology_mgr_resume);

अटल bool
drm_dp_get_one_sb_msg(काष्ठा drm_dp_mst_topology_mgr *mgr, bool up,
		      काष्ठा drm_dp_mst_branch **mstb)
अणु
	पूर्णांक len;
	u8 replyblock[32];
	पूर्णांक replylen, curreply;
	पूर्णांक ret;
	u8 hdrlen;
	काष्ठा drm_dp_sideband_msg_hdr hdr;
	काष्ठा drm_dp_sideband_msg_rx *msg =
		up ? &mgr->up_req_recv : &mgr->करोwn_rep_recv;
	पूर्णांक basereg = up ? DP_SIDEBAND_MSG_UP_REQ_BASE :
			   DP_SIDEBAND_MSG_DOWN_REP_BASE;

	अगर (!up)
		*mstb = शून्य;

	len = min(mgr->max_dpcd_transaction_bytes, 16);
	ret = drm_dp_dpcd_पढ़ो(mgr->aux, basereg, replyblock, len);
	अगर (ret != len) अणु
		DRM_DEBUG_KMS("failed to read DPCD down rep %d %d\n", len, ret);
		वापस false;
	पूर्ण

	ret = drm_dp_decode_sideband_msg_hdr(&hdr, replyblock, len, &hdrlen);
	अगर (ret == false) अणु
		prपूर्णांक_hex_dump(KERN_DEBUG, "failed hdr", DUMP_PREFIX_NONE, 16,
			       1, replyblock, len, false);
		DRM_DEBUG_KMS("ERROR: failed header\n");
		वापस false;
	पूर्ण

	अगर (!up) अणु
		/* Caller is responsible क्रम giving back this reference */
		*mstb = drm_dp_get_mst_branch_device(mgr, hdr.lct, hdr.rad);
		अगर (!*mstb) अणु
			DRM_DEBUG_KMS("Got MST reply from unknown device %d\n",
				      hdr.lct);
			वापस false;
		पूर्ण
	पूर्ण

	अगर (!drm_dp_sideband_msg_set_header(msg, &hdr, hdrlen)) अणु
		DRM_DEBUG_KMS("sideband msg set header failed %d\n",
			      replyblock[0]);
		वापस false;
	पूर्ण

	replylen = min(msg->curchunk_len, (u8)(len - hdrlen));
	ret = drm_dp_sideband_append_payload(msg, replyblock + hdrlen, replylen);
	अगर (!ret) अणु
		DRM_DEBUG_KMS("sideband msg build failed %d\n", replyblock[0]);
		वापस false;
	पूर्ण

	replylen = msg->curchunk_len + msg->curchunk_hdrlen - len;
	curreply = len;
	जबतक (replylen > 0) अणु
		len = min3(replylen, mgr->max_dpcd_transaction_bytes, 16);
		ret = drm_dp_dpcd_पढ़ो(mgr->aux, basereg + curreply,
				    replyblock, len);
		अगर (ret != len) अणु
			DRM_DEBUG_KMS("failed to read a chunk (len %d, ret %d)\n",
				      len, ret);
			वापस false;
		पूर्ण

		ret = drm_dp_sideband_append_payload(msg, replyblock, len);
		अगर (!ret) अणु
			DRM_DEBUG_KMS("failed to build sideband msg\n");
			वापस false;
		पूर्ण

		curreply += len;
		replylen -= len;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक drm_dp_mst_handle_करोwn_rep(काष्ठा drm_dp_mst_topology_mgr *mgr)
अणु
	काष्ठा drm_dp_sideband_msg_tx *txmsg;
	काष्ठा drm_dp_mst_branch *mstb = शून्य;
	काष्ठा drm_dp_sideband_msg_rx *msg = &mgr->करोwn_rep_recv;

	अगर (!drm_dp_get_one_sb_msg(mgr, false, &mstb))
		जाओ out;

	/* Multi-packet message transmission, करोn't clear the reply */
	अगर (!msg->have_eomt)
		जाओ out;

	/* find the message */
	mutex_lock(&mgr->qlock);
	txmsg = list_first_entry_or_null(&mgr->tx_msg_करोwnq,
					 काष्ठा drm_dp_sideband_msg_tx, next);
	mutex_unlock(&mgr->qlock);

	/* Were we actually expecting a response, and from this mstb? */
	अगर (!txmsg || txmsg->dst != mstb) अणु
		काष्ठा drm_dp_sideband_msg_hdr *hdr;

		hdr = &msg->initial_hdr;
		DRM_DEBUG_KMS("Got MST reply with no msg %p %d %d %02x %02x\n",
			      mstb, hdr->seqno, hdr->lct, hdr->rad[0],
			      msg->msg[0]);
		जाओ out_clear_reply;
	पूर्ण

	drm_dp_sideband_parse_reply(msg, &txmsg->reply);

	अगर (txmsg->reply.reply_type == DP_SIDEBAND_REPLY_NAK) अणु
		DRM_DEBUG_KMS("Got NAK reply: req 0x%02x (%s), reason 0x%02x (%s), nak data 0x%02x\n",
			      txmsg->reply.req_type,
			      drm_dp_mst_req_type_str(txmsg->reply.req_type),
			      txmsg->reply.u.nak.reason,
			      drm_dp_mst_nak_reason_str(txmsg->reply.u.nak.reason),
			      txmsg->reply.u.nak.nak_data);
	पूर्ण

	स_रखो(msg, 0, माप(काष्ठा drm_dp_sideband_msg_rx));
	drm_dp_mst_topology_put_mstb(mstb);

	mutex_lock(&mgr->qlock);
	txmsg->state = DRM_DP_SIDEBAND_TX_RX;
	list_del(&txmsg->next);
	mutex_unlock(&mgr->qlock);

	wake_up_all(&mgr->tx_रुकोq);

	वापस 0;

out_clear_reply:
	स_रखो(msg, 0, माप(काष्ठा drm_dp_sideband_msg_rx));
out:
	अगर (mstb)
		drm_dp_mst_topology_put_mstb(mstb);

	वापस 0;
पूर्ण

अटल अंतरभूत bool
drm_dp_mst_process_up_req(काष्ठा drm_dp_mst_topology_mgr *mgr,
			  काष्ठा drm_dp_pending_up_req *up_req)
अणु
	काष्ठा drm_dp_mst_branch *mstb = शून्य;
	काष्ठा drm_dp_sideband_msg_req_body *msg = &up_req->msg;
	काष्ठा drm_dp_sideband_msg_hdr *hdr = &up_req->hdr;
	bool hotplug = false;

	अगर (hdr->broadcast) अणु
		स्थिर u8 *guid = शून्य;

		अगर (msg->req_type == DP_CONNECTION_STATUS_NOTIFY)
			guid = msg->u.conn_stat.guid;
		अन्यथा अगर (msg->req_type == DP_RESOURCE_STATUS_NOTIFY)
			guid = msg->u.resource_stat.guid;

		अगर (guid)
			mstb = drm_dp_get_mst_branch_device_by_guid(mgr, guid);
	पूर्ण अन्यथा अणु
		mstb = drm_dp_get_mst_branch_device(mgr, hdr->lct, hdr->rad);
	पूर्ण

	अगर (!mstb) अणु
		DRM_DEBUG_KMS("Got MST reply from unknown device %d\n",
			      hdr->lct);
		वापस false;
	पूर्ण

	/* TODO: Add missing handler क्रम DP_RESOURCE_STATUS_NOTIFY events */
	अगर (msg->req_type == DP_CONNECTION_STATUS_NOTIFY) अणु
		drm_dp_mst_handle_conn_stat(mstb, &msg->u.conn_stat);
		hotplug = true;
	पूर्ण

	drm_dp_mst_topology_put_mstb(mstb);
	वापस hotplug;
पूर्ण

अटल व्योम drm_dp_mst_up_req_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_dp_mst_topology_mgr *mgr =
		container_of(work, काष्ठा drm_dp_mst_topology_mgr,
			     up_req_work);
	काष्ठा drm_dp_pending_up_req *up_req;
	bool send_hotplug = false;

	mutex_lock(&mgr->probe_lock);
	जबतक (true) अणु
		mutex_lock(&mgr->up_req_lock);
		up_req = list_first_entry_or_null(&mgr->up_req_list,
						  काष्ठा drm_dp_pending_up_req,
						  next);
		अगर (up_req)
			list_del(&up_req->next);
		mutex_unlock(&mgr->up_req_lock);

		अगर (!up_req)
			अवरोध;

		send_hotplug |= drm_dp_mst_process_up_req(mgr, up_req);
		kमुक्त(up_req);
	पूर्ण
	mutex_unlock(&mgr->probe_lock);

	अगर (send_hotplug)
		drm_kms_helper_hotplug_event(mgr->dev);
पूर्ण

अटल पूर्णांक drm_dp_mst_handle_up_req(काष्ठा drm_dp_mst_topology_mgr *mgr)
अणु
	काष्ठा drm_dp_pending_up_req *up_req;

	अगर (!drm_dp_get_one_sb_msg(mgr, true, शून्य))
		जाओ out;

	अगर (!mgr->up_req_recv.have_eomt)
		वापस 0;

	up_req = kzalloc(माप(*up_req), GFP_KERNEL);
	अगर (!up_req)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&up_req->next);

	drm_dp_sideband_parse_req(&mgr->up_req_recv, &up_req->msg);

	अगर (up_req->msg.req_type != DP_CONNECTION_STATUS_NOTIFY &&
	    up_req->msg.req_type != DP_RESOURCE_STATUS_NOTIFY) अणु
		DRM_DEBUG_KMS("Received unknown up req type, ignoring: %x\n",
			      up_req->msg.req_type);
		kमुक्त(up_req);
		जाओ out;
	पूर्ण

	drm_dp_send_up_ack_reply(mgr, mgr->mst_primary, up_req->msg.req_type,
				 false);

	अगर (up_req->msg.req_type == DP_CONNECTION_STATUS_NOTIFY) अणु
		स्थिर काष्ठा drm_dp_connection_status_notअगरy *conn_stat =
			&up_req->msg.u.conn_stat;

		DRM_DEBUG_KMS("Got CSN: pn: %d ldps:%d ddps: %d mcs: %d ip: %d pdt: %d\n",
			      conn_stat->port_number,
			      conn_stat->legacy_device_plug_status,
			      conn_stat->displayport_device_plug_status,
			      conn_stat->message_capability_status,
			      conn_stat->input_port,
			      conn_stat->peer_device_type);
	पूर्ण अन्यथा अगर (up_req->msg.req_type == DP_RESOURCE_STATUS_NOTIFY) अणु
		स्थिर काष्ठा drm_dp_resource_status_notअगरy *res_stat =
			&up_req->msg.u.resource_stat;

		DRM_DEBUG_KMS("Got RSN: pn: %d avail_pbn %d\n",
			      res_stat->port_number,
			      res_stat->available_pbn);
	पूर्ण

	up_req->hdr = mgr->up_req_recv.initial_hdr;
	mutex_lock(&mgr->up_req_lock);
	list_add_tail(&up_req->next, &mgr->up_req_list);
	mutex_unlock(&mgr->up_req_lock);
	queue_work(प्रणाली_दीर्घ_wq, &mgr->up_req_work);

out:
	स_रखो(&mgr->up_req_recv, 0, माप(काष्ठा drm_dp_sideband_msg_rx));
	वापस 0;
पूर्ण

/**
 * drm_dp_mst_hpd_irq() - MST hotplug IRQ notअगरy
 * @mgr: manager to notअगरy irq क्रम.
 * @esi: 4 bytes from SINK_COUNT_ESI
 * @handled: whether the hpd पूर्णांकerrupt was consumed or not
 *
 * This should be called from the driver when it detects a लघु IRQ,
 * aदीर्घ with the value of the DEVICE_SERVICE_IRQ_VECTOR_ESI0. The
 * topology manager will process the sideband messages received as a result
 * of this.
 */
पूर्णांक drm_dp_mst_hpd_irq(काष्ठा drm_dp_mst_topology_mgr *mgr, u8 *esi, bool *handled)
अणु
	पूर्णांक ret = 0;
	पूर्णांक sc;
	*handled = false;
	sc = esi[0] & 0x3f;

	अगर (sc != mgr->sink_count) अणु
		mgr->sink_count = sc;
		*handled = true;
	पूर्ण

	अगर (esi[1] & DP_DOWN_REP_MSG_RDY) अणु
		ret = drm_dp_mst_handle_करोwn_rep(mgr);
		*handled = true;
	पूर्ण

	अगर (esi[1] & DP_UP_REQ_MSG_RDY) अणु
		ret |= drm_dp_mst_handle_up_req(mgr);
		*handled = true;
	पूर्ण

	drm_dp_mst_kick_tx(mgr);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_hpd_irq);

/**
 * drm_dp_mst_detect_port() - get connection status क्रम an MST port
 * @connector: DRM connector क्रम this port
 * @ctx: The acquisition context to use क्रम grabbing locks
 * @mgr: manager क्रम this port
 * @port: poपूर्णांकer to a port
 *
 * This वापसs the current connection state क्रम a port.
 */
पूर्णांक
drm_dp_mst_detect_port(काष्ठा drm_connector *connector,
		       काष्ठा drm_modeset_acquire_ctx *ctx,
		       काष्ठा drm_dp_mst_topology_mgr *mgr,
		       काष्ठा drm_dp_mst_port *port)
अणु
	पूर्णांक ret;

	/* we need to search क्रम the port in the mgr in हाल it's gone */
	port = drm_dp_mst_topology_get_port_validated(mgr, port);
	अगर (!port)
		वापस connector_status_disconnected;

	ret = drm_modeset_lock(&mgr->base.lock, ctx);
	अगर (ret)
		जाओ out;

	ret = connector_status_disconnected;

	अगर (!port->ddps)
		जाओ out;

	चयन (port->pdt) अणु
	हाल DP_PEER_DEVICE_NONE:
		अवरोध;
	हाल DP_PEER_DEVICE_MST_BRANCHING:
		अगर (!port->mcs)
			ret = connector_status_connected;
		अवरोध;

	हाल DP_PEER_DEVICE_SST_SINK:
		ret = connector_status_connected;
		/* क्रम logical ports - cache the EDID */
		अगर (port->port_num >= DP_MST_LOGICAL_PORT_0 && !port->cached_edid)
			port->cached_edid = drm_get_edid(connector, &port->aux.ddc);
		अवरोध;
	हाल DP_PEER_DEVICE_DP_LEGACY_CONV:
		अगर (port->ldps)
			ret = connector_status_connected;
		अवरोध;
	पूर्ण
out:
	drm_dp_mst_topology_put_port(port);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_detect_port);

/**
 * drm_dp_mst_get_edid() - get EDID क्रम an MST port
 * @connector: toplevel connector to get EDID क्रम
 * @mgr: manager क्रम this port
 * @port: unverअगरied poपूर्णांकer to a port.
 *
 * This वापसs an EDID क्रम the port connected to a connector,
 * It validates the poपूर्णांकer still exists so the caller करोesn't require a
 * reference.
 */
काष्ठा edid *drm_dp_mst_get_edid(काष्ठा drm_connector *connector, काष्ठा drm_dp_mst_topology_mgr *mgr, काष्ठा drm_dp_mst_port *port)
अणु
	काष्ठा edid *edid = शून्य;

	/* we need to search क्रम the port in the mgr in हाल it's gone */
	port = drm_dp_mst_topology_get_port_validated(mgr, port);
	अगर (!port)
		वापस शून्य;

	अगर (port->cached_edid)
		edid = drm_edid_duplicate(port->cached_edid);
	अन्यथा अणु
		edid = drm_get_edid(connector, &port->aux.ddc);
	पूर्ण
	port->has_audio = drm_detect_monitor_audio(edid);
	drm_dp_mst_topology_put_port(port);
	वापस edid;
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_get_edid);

/**
 * drm_dp_find_vcpi_slots() - Find VCPI slots क्रम this PBN value
 * @mgr: manager to use
 * @pbn: payload bandwidth to convert पूर्णांकo slots.
 *
 * Calculate the number of VCPI slots that will be required क्रम the given PBN
 * value. This function is deprecated, and should not be used in atomic
 * drivers.
 *
 * RETURNS:
 * The total slots required क्रम this port, or error.
 */
पूर्णांक drm_dp_find_vcpi_slots(काष्ठा drm_dp_mst_topology_mgr *mgr,
			   पूर्णांक pbn)
अणु
	पूर्णांक num_slots;

	num_slots = DIV_ROUND_UP(pbn, mgr->pbn_भाग);

	/* max. समय slots - one slot क्रम MTP header */
	अगर (num_slots > 63)
		वापस -ENOSPC;
	वापस num_slots;
पूर्ण
EXPORT_SYMBOL(drm_dp_find_vcpi_slots);

अटल पूर्णांक drm_dp_init_vcpi(काष्ठा drm_dp_mst_topology_mgr *mgr,
			    काष्ठा drm_dp_vcpi *vcpi, पूर्णांक pbn, पूर्णांक slots)
अणु
	पूर्णांक ret;

	/* max. समय slots - one slot क्रम MTP header */
	अगर (slots > 63)
		वापस -ENOSPC;

	vcpi->pbn = pbn;
	vcpi->aligned_pbn = slots * mgr->pbn_भाग;
	vcpi->num_slots = slots;

	ret = drm_dp_mst_assign_payload_id(mgr, vcpi);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

/**
 * drm_dp_atomic_find_vcpi_slots() - Find and add VCPI slots to the state
 * @state: global atomic state
 * @mgr: MST topology manager क्रम the port
 * @port: port to find vcpi slots क्रम
 * @pbn: bandwidth required क्रम the mode in PBN
 * @pbn_भाग: भागider क्रम DSC mode that takes FEC पूर्णांकo account
 *
 * Allocates VCPI slots to @port, replacing any previous VCPI allocations it
 * may have had. Any atomic drivers which support MST must call this function
 * in their &drm_encoder_helper_funcs.atomic_check() callback to change the
 * current VCPI allocation क्रम the new state, but only when
 * &drm_crtc_state.mode_changed or &drm_crtc_state.connectors_changed is set
 * to ensure compatibility with userspace applications that still use the
 * legacy modesetting UAPI.
 *
 * Allocations set by this function are not checked against the bandwidth
 * restraपूर्णांकs of @mgr until the driver calls drm_dp_mst_atomic_check().
 *
 * Additionally, it is OK to call this function multiple बार on the same
 * @port as needed. It is not OK however, to call this function and
 * drm_dp_atomic_release_vcpi_slots() in the same atomic check phase.
 *
 * See also:
 * drm_dp_atomic_release_vcpi_slots()
 * drm_dp_mst_atomic_check()
 *
 * Returns:
 * Total slots in the atomic state asचिन्हित क्रम this port, or a negative error
 * code अगर the port no दीर्घer exists
 */
पूर्णांक drm_dp_atomic_find_vcpi_slots(काष्ठा drm_atomic_state *state,
				  काष्ठा drm_dp_mst_topology_mgr *mgr,
				  काष्ठा drm_dp_mst_port *port, पूर्णांक pbn,
				  पूर्णांक pbn_भाग)
अणु
	काष्ठा drm_dp_mst_topology_state *topology_state;
	काष्ठा drm_dp_vcpi_allocation *pos, *vcpi = शून्य;
	पूर्णांक prev_slots, prev_bw, req_slots;

	topology_state = drm_atomic_get_mst_topology_state(state, mgr);
	अगर (IS_ERR(topology_state))
		वापस PTR_ERR(topology_state);

	/* Find the current allocation क्रम this port, अगर any */
	list_क्रम_each_entry(pos, &topology_state->vcpis, next) अणु
		अगर (pos->port == port) अणु
			vcpi = pos;
			prev_slots = vcpi->vcpi;
			prev_bw = vcpi->pbn;

			/*
			 * This should never happen, unless the driver tries
			 * releasing and allocating the same VCPI allocation,
			 * which is an error
			 */
			अगर (WARN_ON(!prev_slots)) अणु
				DRM_ERROR("cannot allocate and release VCPI on [MST PORT:%p] in the same state\n",
					  port);
				वापस -EINVAL;
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!vcpi) अणु
		prev_slots = 0;
		prev_bw = 0;
	पूर्ण

	अगर (pbn_भाग <= 0)
		pbn_भाग = mgr->pbn_भाग;

	req_slots = DIV_ROUND_UP(pbn, pbn_भाग);

	DRM_DEBUG_ATOMIC("[CONNECTOR:%d:%s] [MST PORT:%p] VCPI %d -> %d\n",
			 port->connector->base.id, port->connector->name,
			 port, prev_slots, req_slots);
	DRM_DEBUG_ATOMIC("[CONNECTOR:%d:%s] [MST PORT:%p] PBN %d -> %d\n",
			 port->connector->base.id, port->connector->name,
			 port, prev_bw, pbn);

	/* Add the new allocation to the state */
	अगर (!vcpi) अणु
		vcpi = kzalloc(माप(*vcpi), GFP_KERNEL);
		अगर (!vcpi)
			वापस -ENOMEM;

		drm_dp_mst_get_port_दो_स्मृति(port);
		vcpi->port = port;
		list_add(&vcpi->next, &topology_state->vcpis);
	पूर्ण
	vcpi->vcpi = req_slots;
	vcpi->pbn = pbn;

	वापस req_slots;
पूर्ण
EXPORT_SYMBOL(drm_dp_atomic_find_vcpi_slots);

/**
 * drm_dp_atomic_release_vcpi_slots() - Release allocated vcpi slots
 * @state: global atomic state
 * @mgr: MST topology manager क्रम the port
 * @port: The port to release the VCPI slots from
 *
 * Releases any VCPI slots that have been allocated to a port in the atomic
 * state. Any atomic drivers which support MST must call this function in
 * their &drm_connector_helper_funcs.atomic_check() callback when the
 * connector will no दीर्घer have VCPI allocated (e.g. because its CRTC was
 * हटाओd) when it had VCPI allocated in the previous atomic state.
 *
 * It is OK to call this even अगर @port has been हटाओd from the प्रणाली.
 * Additionally, it is OK to call this function multiple बार on the same
 * @port as needed. It is not OK however, to call this function and
 * drm_dp_atomic_find_vcpi_slots() on the same @port in a single atomic check
 * phase.
 *
 * See also:
 * drm_dp_atomic_find_vcpi_slots()
 * drm_dp_mst_atomic_check()
 *
 * Returns:
 * 0 अगर all slots क्रम this port were added back to
 * &drm_dp_mst_topology_state.avail_slots or negative error code
 */
पूर्णांक drm_dp_atomic_release_vcpi_slots(काष्ठा drm_atomic_state *state,
				     काष्ठा drm_dp_mst_topology_mgr *mgr,
				     काष्ठा drm_dp_mst_port *port)
अणु
	काष्ठा drm_dp_mst_topology_state *topology_state;
	काष्ठा drm_dp_vcpi_allocation *pos;
	bool found = false;

	topology_state = drm_atomic_get_mst_topology_state(state, mgr);
	अगर (IS_ERR(topology_state))
		वापस PTR_ERR(topology_state);

	list_क्रम_each_entry(pos, &topology_state->vcpis, next) अणु
		अगर (pos->port == port) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (WARN_ON(!found)) अणु
		DRM_ERROR("no VCPI for [MST PORT:%p] found in mst state %p\n",
			  port, &topology_state->base);
		वापस -EINVAL;
	पूर्ण

	DRM_DEBUG_ATOMIC("[MST PORT:%p] VCPI %d -> 0\n", port, pos->vcpi);
	अगर (pos->vcpi) अणु
		drm_dp_mst_put_port_दो_स्मृति(port);
		pos->vcpi = 0;
		pos->pbn = 0;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_atomic_release_vcpi_slots);

/**
 * drm_dp_mst_allocate_vcpi() - Allocate a भव channel
 * @mgr: manager क्रम this port
 * @port: port to allocate a भव channel क्रम.
 * @pbn: payload bandwidth number to request
 * @slots: वापसed number of slots क्रम this PBN.
 */
bool drm_dp_mst_allocate_vcpi(काष्ठा drm_dp_mst_topology_mgr *mgr,
			      काष्ठा drm_dp_mst_port *port, पूर्णांक pbn, पूर्णांक slots)
अणु
	पूर्णांक ret;

	अगर (slots < 0)
		वापस false;

	port = drm_dp_mst_topology_get_port_validated(mgr, port);
	अगर (!port)
		वापस false;

	अगर (port->vcpi.vcpi > 0) अणु
		DRM_DEBUG_KMS("payload: vcpi %d already allocated for pbn %d - requested pbn %d\n",
			      port->vcpi.vcpi, port->vcpi.pbn, pbn);
		अगर (pbn == port->vcpi.pbn) अणु
			drm_dp_mst_topology_put_port(port);
			वापस true;
		पूर्ण
	पूर्ण

	ret = drm_dp_init_vcpi(mgr, &port->vcpi, pbn, slots);
	अगर (ret) अणु
		DRM_DEBUG_KMS("failed to init vcpi slots=%d max=63 ret=%d\n",
			      DIV_ROUND_UP(pbn, mgr->pbn_भाग), ret);
		drm_dp_mst_topology_put_port(port);
		जाओ out;
	पूर्ण
	DRM_DEBUG_KMS("initing vcpi for pbn=%d slots=%d\n",
		      pbn, port->vcpi.num_slots);

	/* Keep port allocated until its payload has been हटाओd */
	drm_dp_mst_get_port_दो_स्मृति(port);
	drm_dp_mst_topology_put_port(port);
	वापस true;
out:
	वापस false;
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_allocate_vcpi);

पूर्णांक drm_dp_mst_get_vcpi_slots(काष्ठा drm_dp_mst_topology_mgr *mgr, काष्ठा drm_dp_mst_port *port)
अणु
	पूर्णांक slots = 0;

	port = drm_dp_mst_topology_get_port_validated(mgr, port);
	अगर (!port)
		वापस slots;

	slots = port->vcpi.num_slots;
	drm_dp_mst_topology_put_port(port);
	वापस slots;
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_get_vcpi_slots);

/**
 * drm_dp_mst_reset_vcpi_slots() - Reset number of slots to 0 क्रम VCPI
 * @mgr: manager क्रम this port
 * @port: unverअगरied poपूर्णांकer to a port.
 *
 * This just resets the number of slots क्रम the ports VCPI क्रम later programming.
 */
व्योम drm_dp_mst_reset_vcpi_slots(काष्ठा drm_dp_mst_topology_mgr *mgr, काष्ठा drm_dp_mst_port *port)
अणु
	/*
	 * A port with VCPI will reमुख्य allocated until its VCPI is
	 * released, no verअगरied ref needed
	 */

	port->vcpi.num_slots = 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_reset_vcpi_slots);

/**
 * drm_dp_mst_deallocate_vcpi() - deallocate a VCPI
 * @mgr: manager क्रम this port
 * @port: port to deallocate vcpi क्रम
 *
 * This can be called unconditionally, regardless of whether
 * drm_dp_mst_allocate_vcpi() succeeded or not.
 */
व्योम drm_dp_mst_deallocate_vcpi(काष्ठा drm_dp_mst_topology_mgr *mgr,
				काष्ठा drm_dp_mst_port *port)
अणु
	अगर (!port->vcpi.vcpi)
		वापस;

	drm_dp_mst_put_payload_id(mgr, port->vcpi.vcpi);
	port->vcpi.num_slots = 0;
	port->vcpi.pbn = 0;
	port->vcpi.aligned_pbn = 0;
	port->vcpi.vcpi = 0;
	drm_dp_mst_put_port_दो_स्मृति(port);
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_deallocate_vcpi);

अटल पूर्णांक drm_dp_dpcd_ग_लिखो_payload(काष्ठा drm_dp_mst_topology_mgr *mgr,
				     पूर्णांक id, काष्ठा drm_dp_payload *payload)
अणु
	u8 payload_alloc[3], status;
	पूर्णांक ret;
	पूर्णांक retries = 0;

	drm_dp_dpcd_ग_लिखोb(mgr->aux, DP_PAYLOAD_TABLE_UPDATE_STATUS,
			   DP_PAYLOAD_TABLE_UPDATED);

	payload_alloc[0] = id;
	payload_alloc[1] = payload->start_slot;
	payload_alloc[2] = payload->num_slots;

	ret = drm_dp_dpcd_ग_लिखो(mgr->aux, DP_PAYLOAD_ALLOCATE_SET, payload_alloc, 3);
	अगर (ret != 3) अणु
		DRM_DEBUG_KMS("failed to write payload allocation %d\n", ret);
		जाओ fail;
	पूर्ण

retry:
	ret = drm_dp_dpcd_पढ़ोb(mgr->aux, DP_PAYLOAD_TABLE_UPDATE_STATUS, &status);
	अगर (ret < 0) अणु
		DRM_DEBUG_KMS("failed to read payload table status %d\n", ret);
		जाओ fail;
	पूर्ण

	अगर (!(status & DP_PAYLOAD_TABLE_UPDATED)) अणु
		retries++;
		अगर (retries < 20) अणु
			usleep_range(10000, 20000);
			जाओ retry;
		पूर्ण
		DRM_DEBUG_KMS("status not set after read payload table status %d\n", status);
		ret = -EINVAL;
		जाओ fail;
	पूर्ण
	ret = 0;
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक करो_get_act_status(काष्ठा drm_dp_aux *aux)
अणु
	पूर्णांक ret;
	u8 status;

	ret = drm_dp_dpcd_पढ़ोb(aux, DP_PAYLOAD_TABLE_UPDATE_STATUS, &status);
	अगर (ret < 0)
		वापस ret;

	वापस status;
पूर्ण

/**
 * drm_dp_check_act_status() - Polls क्रम ACT handled status.
 * @mgr: manager to use
 *
 * Tries रुकोing क्रम the MST hub to finish updating it's payload table by
 * polling क्रम the ACT handled bit क्रम up to 3 seconds (yes-some hubs really
 * take that दीर्घ).
 *
 * Returns:
 * 0 अगर the ACT was handled in समय, negative error code on failure.
 */
पूर्णांक drm_dp_check_act_status(काष्ठा drm_dp_mst_topology_mgr *mgr)
अणु
	/*
	 * There करोesn't seem to be any recommended retry count or समयout in
	 * the MST specअगरication. Since some hubs have been observed to take
	 * over 1 second to update their payload allocations under certain
	 * conditions, we use a rather large समयout value.
	 */
	स्थिर पूर्णांक समयout_ms = 3000;
	पूर्णांक ret, status;

	ret = पढ़ोx_poll_समयout(करो_get_act_status, mgr->aux, status,
				 status & DP_PAYLOAD_ACT_HANDLED || status < 0,
				 200, समयout_ms * USEC_PER_MSEC);
	अगर (ret < 0 && status >= 0) अणु
		DRM_ERROR("Failed to get ACT after %dms, last status: %02x\n",
			  समयout_ms, status);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (status < 0) अणु
		/*
		 * Failure here isn't unexpected - the hub may have
		 * just been unplugged
		 */
		DRM_DEBUG_KMS("Failed to read payload table status: %d\n",
			      status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_check_act_status);

/**
 * drm_dp_calc_pbn_mode() - Calculate the PBN क्रम a mode.
 * @घड़ी: करोt घड़ी क्रम the mode
 * @bpp: bpp क्रम the mode.
 * @dsc: DSC mode. If true, bpp has units of 1/16 of a bit per pixel
 *
 * This uses the क्रमmula in the spec to calculate the PBN value क्रम a mode.
 */
पूर्णांक drm_dp_calc_pbn_mode(पूर्णांक घड़ी, पूर्णांक bpp, bool dsc)
अणु
	/*
	 * margin 5300ppm + 300ppm ~ 0.6% as per spec, factor is 1.006
	 * The unit of 54/64Mbytes/sec is an arbitrary unit chosen based on
	 * common multiplier to render an पूर्णांकeger PBN क्रम all link rate/lane
	 * counts combinations
	 * calculate
	 * peak_kbps *= (1006/1000)
	 * peak_kbps *= (64/54)
	 * peak_kbps *= 8    convert to bytes
	 *
	 * If the bpp is in units of 1/16, further भागide by 16. Put this
	 * factor in the numerator rather than the denominator to aव्योम
	 * पूर्णांकeger overflow
	 */

	अगर (dsc)
		वापस DIV_ROUND_UP_ULL(mul_u32_u32(घड़ी * (bpp / 16), 64 * 1006),
					8 * 54 * 1000 * 1000);

	वापस DIV_ROUND_UP_ULL(mul_u32_u32(घड़ी * bpp, 64 * 1006),
				8 * 54 * 1000 * 1000);
पूर्ण
EXPORT_SYMBOL(drm_dp_calc_pbn_mode);

/* we want to kick the TX after we've ack the up/करोwn IRQs. */
अटल व्योम drm_dp_mst_kick_tx(काष्ठा drm_dp_mst_topology_mgr *mgr)
अणु
	queue_work(प्रणाली_दीर्घ_wq, &mgr->tx_work);
पूर्ण

/*
 * Helper function क्रम parsing DP device types पूर्णांकo convenient strings
 * क्रम use with dp_mst_topology
 */
अटल स्थिर अक्षर *pdt_to_string(u8 pdt)
अणु
	चयन (pdt) अणु
	हाल DP_PEER_DEVICE_NONE:
		वापस "NONE";
	हाल DP_PEER_DEVICE_SOURCE_OR_SST:
		वापस "SOURCE OR SST";
	हाल DP_PEER_DEVICE_MST_BRANCHING:
		वापस "MST BRANCHING";
	हाल DP_PEER_DEVICE_SST_SINK:
		वापस "SST SINK";
	हाल DP_PEER_DEVICE_DP_LEGACY_CONV:
		वापस "DP LEGACY CONV";
	शेष:
		वापस "ERR";
	पूर्ण
पूर्ण

अटल व्योम drm_dp_mst_dump_mstb(काष्ठा seq_file *m,
				 काष्ठा drm_dp_mst_branch *mstb)
अणु
	काष्ठा drm_dp_mst_port *port;
	पूर्णांक tअसल = mstb->lct;
	अक्षर prefix[10];
	पूर्णांक i;

	क्रम (i = 0; i < tअसल; i++)
		prefix[i] = '\t';
	prefix[i] = '\0';

	seq_म_लिखो(m, "%smstb - [%p]: num_ports: %d\n", prefix, mstb, mstb->num_ports);
	list_क्रम_each_entry(port, &mstb->ports, next) अणु
		seq_म_लिखो(m, "%sport %d - [%p] (%s - %s): ddps: %d, ldps: %d, sdp: %d/%d, fec: %s, conn: %p\n", 
			   prefix,
			   port->port_num,
			   port,
			   port->input ? "input" : "output",
			   pdt_to_string(port->pdt),
			   port->ddps,
			   port->ldps,
			   port->num_sdp_streams,
			   port->num_sdp_stream_sinks,
			   port->fec_capable ? "true" : "false",
			   port->connector);
		अगर (port->mstb)
			drm_dp_mst_dump_mstb(m, port->mstb);
	पूर्ण
पूर्ण

#घोषणा DP_PAYLOAD_TABLE_SIZE		64

अटल bool dump_dp_payload_table(काष्ठा drm_dp_mst_topology_mgr *mgr,
				  अक्षर *buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DP_PAYLOAD_TABLE_SIZE; i += 16) अणु
		अगर (drm_dp_dpcd_पढ़ो(mgr->aux,
				     DP_PAYLOAD_TABLE_UPDATE_STATUS + i,
				     &buf[i], 16) != 16)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम fetch_monitor_name(काष्ठा drm_dp_mst_topology_mgr *mgr,
			       काष्ठा drm_dp_mst_port *port, अक्षर *name,
			       पूर्णांक namelen)
अणु
	काष्ठा edid *mst_edid;

	mst_edid = drm_dp_mst_get_edid(port->connector, mgr, port);
	drm_edid_get_monitor_name(mst_edid, name, namelen);
पूर्ण

/**
 * drm_dp_mst_dump_topology(): dump topology to seq file.
 * @m: seq_file to dump output to
 * @mgr: manager to dump current topology क्रम.
 *
 * helper to dump MST topology to a seq file क्रम debugfs.
 */
व्योम drm_dp_mst_dump_topology(काष्ठा seq_file *m,
			      काष्ठा drm_dp_mst_topology_mgr *mgr)
अणु
	पूर्णांक i;
	काष्ठा drm_dp_mst_port *port;

	mutex_lock(&mgr->lock);
	अगर (mgr->mst_primary)
		drm_dp_mst_dump_mstb(m, mgr->mst_primary);

	/* dump VCPIs */
	mutex_unlock(&mgr->lock);

	mutex_lock(&mgr->payload_lock);
	seq_म_लिखो(m, "\n*** VCPI Info ***\n");
	seq_म_लिखो(m, "payload_mask: %lx, vcpi_mask: %lx, max_payloads: %d\n", mgr->payload_mask, mgr->vcpi_mask, mgr->max_payloads);

	seq_म_लिखो(m, "\n|   idx   |  port # |  vcp_id | # slots |     sink name     |\n");
	क्रम (i = 0; i < mgr->max_payloads; i++) अणु
		अगर (mgr->proposed_vcpis[i]) अणु
			अक्षर name[14];

			port = container_of(mgr->proposed_vcpis[i], काष्ठा drm_dp_mst_port, vcpi);
			fetch_monitor_name(mgr, port, name, माप(name));
			seq_म_लिखो(m, "%10d%10d%10d%10d%20s\n",
				   i,
				   port->port_num,
				   port->vcpi.vcpi,
				   port->vcpi.num_slots,
				   (*name != 0) ? name : "Unknown");
		पूर्ण अन्यथा
			seq_म_लिखो(m, "%6d - Unused\n", i);
	पूर्ण
	seq_म_लिखो(m, "\n*** Payload Info ***\n");
	seq_म_लिखो(m, "|   idx   |  state  |  start slot  | # slots |\n");
	क्रम (i = 0; i < mgr->max_payloads; i++) अणु
		seq_म_लिखो(m, "%10d%10d%15d%10d\n",
			   i,
			   mgr->payloads[i].payload_state,
			   mgr->payloads[i].start_slot,
			   mgr->payloads[i].num_slots);
	पूर्ण
	mutex_unlock(&mgr->payload_lock);

	seq_म_लिखो(m, "\n*** DPCD Info ***\n");
	mutex_lock(&mgr->lock);
	अगर (mgr->mst_primary) अणु
		u8 buf[DP_PAYLOAD_TABLE_SIZE];
		पूर्णांक ret;

		ret = drm_dp_dpcd_पढ़ो(mgr->aux, DP_DPCD_REV, buf, DP_RECEIVER_CAP_SIZE);
		अगर (ret) अणु
			seq_म_लिखो(m, "dpcd read failed\n");
			जाओ out;
		पूर्ण
		seq_म_लिखो(m, "dpcd: %*ph\n", DP_RECEIVER_CAP_SIZE, buf);

		ret = drm_dp_dpcd_पढ़ो(mgr->aux, DP_FAUX_CAP, buf, 2);
		अगर (ret) अणु
			seq_म_लिखो(m, "faux/mst read failed\n");
			जाओ out;
		पूर्ण
		seq_म_लिखो(m, "faux/mst: %*ph\n", 2, buf);

		ret = drm_dp_dpcd_पढ़ो(mgr->aux, DP_MSTM_CTRL, buf, 1);
		अगर (ret) अणु
			seq_म_लिखो(m, "mst ctrl read failed\n");
			जाओ out;
		पूर्ण
		seq_म_लिखो(m, "mst ctrl: %*ph\n", 1, buf);

		/* dump the standard OUI branch header */
		ret = drm_dp_dpcd_पढ़ो(mgr->aux, DP_BRANCH_OUI, buf, DP_BRANCH_OUI_HEADER_SIZE);
		अगर (ret) अणु
			seq_म_लिखो(m, "branch oui read failed\n");
			जाओ out;
		पूर्ण
		seq_म_लिखो(m, "branch oui: %*phN devid: ", 3, buf);

		क्रम (i = 0x3; i < 0x8 && buf[i]; i++)
			seq_म_लिखो(m, "%c", buf[i]);
		seq_म_लिखो(m, " revision: hw: %x.%x sw: %x.%x\n",
			   buf[0x9] >> 4, buf[0x9] & 0xf, buf[0xa], buf[0xb]);
		अगर (dump_dp_payload_table(mgr, buf))
			seq_म_लिखो(m, "payload table: %*ph\n", DP_PAYLOAD_TABLE_SIZE, buf);
	पूर्ण

out:
	mutex_unlock(&mgr->lock);

पूर्ण
EXPORT_SYMBOL(drm_dp_mst_dump_topology);

अटल व्योम drm_dp_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_dp_mst_topology_mgr *mgr = container_of(work, काष्ठा drm_dp_mst_topology_mgr, tx_work);

	mutex_lock(&mgr->qlock);
	अगर (!list_empty(&mgr->tx_msg_करोwnq))
		process_single_करोwn_tx_qlock(mgr);
	mutex_unlock(&mgr->qlock);
पूर्ण

अटल अंतरभूत व्योम
drm_dp_delayed_destroy_port(काष्ठा drm_dp_mst_port *port)
अणु
	drm_dp_port_set_pdt(port, DP_PEER_DEVICE_NONE, port->mcs);

	अगर (port->connector) अणु
		drm_connector_unरेजिस्टर(port->connector);
		drm_connector_put(port->connector);
	पूर्ण

	drm_dp_mst_put_port_दो_स्मृति(port);
पूर्ण

अटल अंतरभूत व्योम
drm_dp_delayed_destroy_mstb(काष्ठा drm_dp_mst_branch *mstb)
अणु
	काष्ठा drm_dp_mst_topology_mgr *mgr = mstb->mgr;
	काष्ठा drm_dp_mst_port *port, *port_पंचांगp;
	काष्ठा drm_dp_sideband_msg_tx *txmsg, *txmsg_पंचांगp;
	bool wake_tx = false;

	mutex_lock(&mgr->lock);
	list_क्रम_each_entry_safe(port, port_पंचांगp, &mstb->ports, next) अणु
		list_del(&port->next);
		drm_dp_mst_topology_put_port(port);
	पूर्ण
	mutex_unlock(&mgr->lock);

	/* drop any tx slot msg */
	mutex_lock(&mstb->mgr->qlock);
	list_क्रम_each_entry_safe(txmsg, txmsg_पंचांगp, &mgr->tx_msg_करोwnq, next) अणु
		अगर (txmsg->dst != mstb)
			जारी;

		txmsg->state = DRM_DP_SIDEBAND_TX_TIMEOUT;
		list_del(&txmsg->next);
		wake_tx = true;
	पूर्ण
	mutex_unlock(&mstb->mgr->qlock);

	अगर (wake_tx)
		wake_up_all(&mstb->mgr->tx_रुकोq);

	drm_dp_mst_put_mstb_दो_स्मृति(mstb);
पूर्ण

अटल व्योम drm_dp_delayed_destroy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_dp_mst_topology_mgr *mgr =
		container_of(work, काष्ठा drm_dp_mst_topology_mgr,
			     delayed_destroy_work);
	bool send_hotplug = false, go_again;

	/*
	 * Not a regular list traverse as we have to drop the destroy
	 * connector lock beक्रमe destroying the mstb/port, to aव्योम AB->BA
	 * ordering between this lock and the config mutex.
	 */
	करो अणु
		go_again = false;

		क्रम (;;) अणु
			काष्ठा drm_dp_mst_branch *mstb;

			mutex_lock(&mgr->delayed_destroy_lock);
			mstb = list_first_entry_or_null(&mgr->destroy_branch_device_list,
							काष्ठा drm_dp_mst_branch,
							destroy_next);
			अगर (mstb)
				list_del(&mstb->destroy_next);
			mutex_unlock(&mgr->delayed_destroy_lock);

			अगर (!mstb)
				अवरोध;

			drm_dp_delayed_destroy_mstb(mstb);
			go_again = true;
		पूर्ण

		क्रम (;;) अणु
			काष्ठा drm_dp_mst_port *port;

			mutex_lock(&mgr->delayed_destroy_lock);
			port = list_first_entry_or_null(&mgr->destroy_port_list,
							काष्ठा drm_dp_mst_port,
							next);
			अगर (port)
				list_del(&port->next);
			mutex_unlock(&mgr->delayed_destroy_lock);

			अगर (!port)
				अवरोध;

			drm_dp_delayed_destroy_port(port);
			send_hotplug = true;
			go_again = true;
		पूर्ण
	पूर्ण जबतक (go_again);

	अगर (send_hotplug)
		drm_kms_helper_hotplug_event(mgr->dev);
पूर्ण

अटल काष्ठा drm_निजी_state *
drm_dp_mst_duplicate_state(काष्ठा drm_निजी_obj *obj)
अणु
	काष्ठा drm_dp_mst_topology_state *state, *old_state =
		to_dp_mst_topology_state(obj->state);
	काष्ठा drm_dp_vcpi_allocation *pos, *vcpi;

	state = kmemdup(old_state, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_निजी_obj_duplicate_state(obj, &state->base);

	INIT_LIST_HEAD(&state->vcpis);

	list_क्रम_each_entry(pos, &old_state->vcpis, next) अणु
		/* Prune leftover मुक्तd VCPI allocations */
		अगर (!pos->vcpi)
			जारी;

		vcpi = kmemdup(pos, माप(*vcpi), GFP_KERNEL);
		अगर (!vcpi)
			जाओ fail;

		drm_dp_mst_get_port_दो_स्मृति(vcpi->port);
		list_add(&vcpi->next, &state->vcpis);
	पूर्ण

	वापस &state->base;

fail:
	list_क्रम_each_entry_safe(pos, vcpi, &state->vcpis, next) अणु
		drm_dp_mst_put_port_दो_स्मृति(pos->port);
		kमुक्त(pos);
	पूर्ण
	kमुक्त(state);

	वापस शून्य;
पूर्ण

अटल व्योम drm_dp_mst_destroy_state(काष्ठा drm_निजी_obj *obj,
				     काष्ठा drm_निजी_state *state)
अणु
	काष्ठा drm_dp_mst_topology_state *mst_state =
		to_dp_mst_topology_state(state);
	काष्ठा drm_dp_vcpi_allocation *pos, *पंचांगp;

	list_क्रम_each_entry_safe(pos, पंचांगp, &mst_state->vcpis, next) अणु
		/* We only keep references to ports with non-zero VCPIs */
		अगर (pos->vcpi)
			drm_dp_mst_put_port_दो_स्मृति(pos->port);
		kमुक्त(pos);
	पूर्ण

	kमुक्त(mst_state);
पूर्ण

अटल bool drm_dp_mst_port_करोwnstream_of_branch(काष्ठा drm_dp_mst_port *port,
						 काष्ठा drm_dp_mst_branch *branch)
अणु
	जबतक (port->parent) अणु
		अगर (port->parent == branch)
			वापस true;

		अगर (port->parent->port_parent)
			port = port->parent->port_parent;
		अन्यथा
			अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक
drm_dp_mst_atomic_check_port_bw_limit(काष्ठा drm_dp_mst_port *port,
				      काष्ठा drm_dp_mst_topology_state *state);

अटल पूर्णांक
drm_dp_mst_atomic_check_mstb_bw_limit(काष्ठा drm_dp_mst_branch *mstb,
				      काष्ठा drm_dp_mst_topology_state *state)
अणु
	काष्ठा drm_dp_vcpi_allocation *vcpi;
	काष्ठा drm_dp_mst_port *port;
	पूर्णांक pbn_used = 0, ret;
	bool found = false;

	/* Check that we have at least one port in our state that's करोwnstream
	 * of this branch, otherwise we can skip this branch
	 */
	list_क्रम_each_entry(vcpi, &state->vcpis, next) अणु
		अगर (!vcpi->pbn ||
		    !drm_dp_mst_port_करोwnstream_of_branch(vcpi->port, mstb))
			जारी;

		found = true;
		अवरोध;
	पूर्ण
	अगर (!found)
		वापस 0;

	अगर (mstb->port_parent)
		DRM_DEBUG_ATOMIC("[MSTB:%p] [MST PORT:%p] Checking bandwidth limits on [MSTB:%p]\n",
				 mstb->port_parent->parent, mstb->port_parent,
				 mstb);
	अन्यथा
		DRM_DEBUG_ATOMIC("[MSTB:%p] Checking bandwidth limits\n",
				 mstb);

	list_क्रम_each_entry(port, &mstb->ports, next) अणु
		ret = drm_dp_mst_atomic_check_port_bw_limit(port, state);
		अगर (ret < 0)
			वापस ret;

		pbn_used += ret;
	पूर्ण

	वापस pbn_used;
पूर्ण

अटल पूर्णांक
drm_dp_mst_atomic_check_port_bw_limit(काष्ठा drm_dp_mst_port *port,
				      काष्ठा drm_dp_mst_topology_state *state)
अणु
	काष्ठा drm_dp_vcpi_allocation *vcpi;
	पूर्णांक pbn_used = 0;

	अगर (port->pdt == DP_PEER_DEVICE_NONE)
		वापस 0;

	अगर (drm_dp_mst_is_end_device(port->pdt, port->mcs)) अणु
		bool found = false;

		list_क्रम_each_entry(vcpi, &state->vcpis, next) अणु
			अगर (vcpi->port != port)
				जारी;
			अगर (!vcpi->pbn)
				वापस 0;

			found = true;
			अवरोध;
		पूर्ण
		अगर (!found)
			वापस 0;

		/*
		 * This could happen अगर the sink deनिश्चितed its HPD line, but
		 * the branch device still reports it as attached (PDT != NONE).
		 */
		अगर (!port->full_pbn) अणु
			drm_dbg_atomic(port->mgr->dev,
				       "[MSTB:%p] [MST PORT:%p] no BW available for the port\n",
				       port->parent, port);
			वापस -EINVAL;
		पूर्ण

		pbn_used = vcpi->pbn;
	पूर्ण अन्यथा अणु
		pbn_used = drm_dp_mst_atomic_check_mstb_bw_limit(port->mstb,
								 state);
		अगर (pbn_used <= 0)
			वापस pbn_used;
	पूर्ण

	अगर (pbn_used > port->full_pbn) अणु
		DRM_DEBUG_ATOMIC("[MSTB:%p] [MST PORT:%p] required PBN of %d exceeds port limit of %d\n",
				 port->parent, port, pbn_used,
				 port->full_pbn);
		वापस -ENOSPC;
	पूर्ण

	DRM_DEBUG_ATOMIC("[MSTB:%p] [MST PORT:%p] uses %d out of %d PBN\n",
			 port->parent, port, pbn_used, port->full_pbn);

	वापस pbn_used;
पूर्ण

अटल अंतरभूत पूर्णांक
drm_dp_mst_atomic_check_vcpi_alloc_limit(काष्ठा drm_dp_mst_topology_mgr *mgr,
					 काष्ठा drm_dp_mst_topology_state *mst_state)
अणु
	काष्ठा drm_dp_vcpi_allocation *vcpi;
	पूर्णांक avail_slots = 63, payload_count = 0;

	list_क्रम_each_entry(vcpi, &mst_state->vcpis, next) अणु
		/* Releasing VCPI is always OK-even अगर the port is gone */
		अगर (!vcpi->vcpi) अणु
			DRM_DEBUG_ATOMIC("[MST PORT:%p] releases all VCPI slots\n",
					 vcpi->port);
			जारी;
		पूर्ण

		DRM_DEBUG_ATOMIC("[MST PORT:%p] requires %d vcpi slots\n",
				 vcpi->port, vcpi->vcpi);

		avail_slots -= vcpi->vcpi;
		अगर (avail_slots < 0) अणु
			DRM_DEBUG_ATOMIC("[MST PORT:%p] not enough VCPI slots in mst state %p (avail=%d)\n",
					 vcpi->port, mst_state,
					 avail_slots + vcpi->vcpi);
			वापस -ENOSPC;
		पूर्ण

		अगर (++payload_count > mgr->max_payloads) अणु
			DRM_DEBUG_ATOMIC("[MST MGR:%p] state %p has too many payloads (max=%d)\n",
					 mgr, mst_state, mgr->max_payloads);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	DRM_DEBUG_ATOMIC("[MST MGR:%p] mst state %p VCPI avail=%d used=%d\n",
			 mgr, mst_state, avail_slots,
			 63 - avail_slots);

	वापस 0;
पूर्ण

/**
 * drm_dp_mst_add_affected_dsc_crtcs
 * @state: Poपूर्णांकer to the new काष्ठा drm_dp_mst_topology_state
 * @mgr: MST topology manager
 *
 * Whenever there is a change in mst topology
 * DSC configuration would have to be recalculated
 * thereक्रमe we need to trigger modeset on all affected
 * CRTCs in that topology
 *
 * See also:
 * drm_dp_mst_atomic_enable_dsc()
 */
पूर्णांक drm_dp_mst_add_affected_dsc_crtcs(काष्ठा drm_atomic_state *state, काष्ठा drm_dp_mst_topology_mgr *mgr)
अणु
	काष्ठा drm_dp_mst_topology_state *mst_state;
	काष्ठा drm_dp_vcpi_allocation *pos;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *crtc_state;

	mst_state = drm_atomic_get_mst_topology_state(state, mgr);

	अगर (IS_ERR(mst_state))
		वापस -EINVAL;

	list_क्रम_each_entry(pos, &mst_state->vcpis, next) अणु

		connector = pos->port->connector;

		अगर (!connector)
			वापस -EINVAL;

		conn_state = drm_atomic_get_connector_state(state, connector);

		अगर (IS_ERR(conn_state))
			वापस PTR_ERR(conn_state);

		crtc = conn_state->crtc;

		अगर (!crtc)
			जारी;

		अगर (!drm_dp_mst_dsc_aux_क्रम_port(pos->port))
			जारी;

		crtc_state = drm_atomic_get_crtc_state(mst_state->base.state, crtc);

		अगर (IS_ERR(crtc_state))
			वापस PTR_ERR(crtc_state);

		DRM_DEBUG_ATOMIC("[MST MGR:%p] Setting mode_changed flag on CRTC %p\n",
				 mgr, crtc);

		crtc_state->mode_changed = true;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_add_affected_dsc_crtcs);

/**
 * drm_dp_mst_atomic_enable_dsc - Set DSC Enable Flag to On/Off
 * @state: Poपूर्णांकer to the new drm_atomic_state
 * @port: Poपूर्णांकer to the affected MST Port
 * @pbn: Newly recalculated bw required क्रम link with DSC enabled
 * @pbn_भाग: Divider to calculate correct number of pbn per slot
 * @enable: Boolean flag to enable or disable DSC on the port
 *
 * This function enables DSC on the given Port
 * by recalculating its vcpi from pbn provided
 * and sets dsc_enable flag to keep track of which
 * ports have DSC enabled
 *
 */
पूर्णांक drm_dp_mst_atomic_enable_dsc(काष्ठा drm_atomic_state *state,
				 काष्ठा drm_dp_mst_port *port,
				 पूर्णांक pbn, पूर्णांक pbn_भाग,
				 bool enable)
अणु
	काष्ठा drm_dp_mst_topology_state *mst_state;
	काष्ठा drm_dp_vcpi_allocation *pos;
	bool found = false;
	पूर्णांक vcpi = 0;

	mst_state = drm_atomic_get_mst_topology_state(state, port->mgr);

	अगर (IS_ERR(mst_state))
		वापस PTR_ERR(mst_state);

	list_क्रम_each_entry(pos, &mst_state->vcpis, next) अणु
		अगर (pos->port == port) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		DRM_DEBUG_ATOMIC("[MST PORT:%p] Couldn't find VCPI allocation in mst state %p\n",
				 port, mst_state);
		वापस -EINVAL;
	पूर्ण

	अगर (pos->dsc_enabled == enable) अणु
		DRM_DEBUG_ATOMIC("[MST PORT:%p] DSC flag is already set to %d, returning %d VCPI slots\n",
				 port, enable, pos->vcpi);
		vcpi = pos->vcpi;
	पूर्ण

	अगर (enable) अणु
		vcpi = drm_dp_atomic_find_vcpi_slots(state, port->mgr, port, pbn, pbn_भाग);
		DRM_DEBUG_ATOMIC("[MST PORT:%p] Enabling DSC flag, reallocating %d VCPI slots on the port\n",
				 port, vcpi);
		अगर (vcpi < 0)
			वापस -EINVAL;
	पूर्ण

	pos->dsc_enabled = enable;

	वापस vcpi;
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_atomic_enable_dsc);
/**
 * drm_dp_mst_atomic_check - Check that the new state of an MST topology in an
 * atomic update is valid
 * @state: Poपूर्णांकer to the new &काष्ठा drm_dp_mst_topology_state
 *
 * Checks the given topology state क्रम an atomic update to ensure that it's
 * valid. This includes checking whether there's enough bandwidth to support
 * the new VCPI allocations in the atomic update.
 *
 * Any atomic drivers supporting DP MST must make sure to call this after
 * checking the rest of their state in their
 * &drm_mode_config_funcs.atomic_check() callback.
 *
 * See also:
 * drm_dp_atomic_find_vcpi_slots()
 * drm_dp_atomic_release_vcpi_slots()
 *
 * Returns:
 *
 * 0 अगर the new state is valid, negative error code otherwise.
 */
पूर्णांक drm_dp_mst_atomic_check(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_dp_mst_topology_mgr *mgr;
	काष्ठा drm_dp_mst_topology_state *mst_state;
	पूर्णांक i, ret = 0;

	क्रम_each_new_mst_mgr_in_state(state, mgr, mst_state, i) अणु
		अगर (!mgr->mst_state)
			जारी;

		ret = drm_dp_mst_atomic_check_vcpi_alloc_limit(mgr, mst_state);
		अगर (ret)
			अवरोध;

		mutex_lock(&mgr->lock);
		ret = drm_dp_mst_atomic_check_mstb_bw_limit(mgr->mst_primary,
							    mst_state);
		mutex_unlock(&mgr->lock);
		अगर (ret < 0)
			अवरोध;
		अन्यथा
			ret = 0;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_atomic_check);

स्थिर काष्ठा drm_निजी_state_funcs drm_dp_mst_topology_state_funcs = अणु
	.atomic_duplicate_state = drm_dp_mst_duplicate_state,
	.atomic_destroy_state = drm_dp_mst_destroy_state,
पूर्ण;
EXPORT_SYMBOL(drm_dp_mst_topology_state_funcs);

/**
 * drm_atomic_get_mst_topology_state: get MST topology state
 *
 * @state: global atomic state
 * @mgr: MST topology manager, also the निजी object in this हाल
 *
 * This function wraps drm_atomic_get_priv_obj_state() passing in the MST atomic
 * state vtable so that the निजी object state वापसed is that of a MST
 * topology object. Also, drm_atomic_get_निजी_obj_state() expects the caller
 * to care of the locking, so warn अगर करोn't hold the connection_mutex.
 *
 * RETURNS:
 *
 * The MST topology state or error poपूर्णांकer.
 */
काष्ठा drm_dp_mst_topology_state *drm_atomic_get_mst_topology_state(काष्ठा drm_atomic_state *state,
								    काष्ठा drm_dp_mst_topology_mgr *mgr)
अणु
	वापस to_dp_mst_topology_state(drm_atomic_get_निजी_obj_state(state, &mgr->base));
पूर्ण
EXPORT_SYMBOL(drm_atomic_get_mst_topology_state);

/**
 * drm_dp_mst_topology_mgr_init - initialise a topology manager
 * @mgr: manager काष्ठा to initialise
 * @dev: device providing this काष्ठाure - क्रम i2c addition.
 * @aux: DP helper aux channel to talk to this device
 * @max_dpcd_transaction_bytes: hw specअगरic DPCD transaction limit
 * @max_payloads: maximum number of payloads this GPU can source
 * @conn_base_id: the connector object ID the MST device is connected to.
 *
 * Return 0 क्रम success, or negative error code on failure
 */
पूर्णांक drm_dp_mst_topology_mgr_init(काष्ठा drm_dp_mst_topology_mgr *mgr,
				 काष्ठा drm_device *dev, काष्ठा drm_dp_aux *aux,
				 पूर्णांक max_dpcd_transaction_bytes,
				 पूर्णांक max_payloads, पूर्णांक conn_base_id)
अणु
	काष्ठा drm_dp_mst_topology_state *mst_state;

	mutex_init(&mgr->lock);
	mutex_init(&mgr->qlock);
	mutex_init(&mgr->payload_lock);
	mutex_init(&mgr->delayed_destroy_lock);
	mutex_init(&mgr->up_req_lock);
	mutex_init(&mgr->probe_lock);
#अगर IS_ENABLED(CONFIG_DRM_DEBUG_DP_MST_TOPOLOGY_REFS)
	mutex_init(&mgr->topology_ref_history_lock);
#पूर्ण_अगर
	INIT_LIST_HEAD(&mgr->tx_msg_करोwnq);
	INIT_LIST_HEAD(&mgr->destroy_port_list);
	INIT_LIST_HEAD(&mgr->destroy_branch_device_list);
	INIT_LIST_HEAD(&mgr->up_req_list);

	/*
	 * delayed_destroy_work will be queued on a dedicated WQ, so that any
	 * requeuing will be also flushed when deiniting the topology manager.
	 */
	mgr->delayed_destroy_wq = alloc_ordered_workqueue("drm_dp_mst_wq", 0);
	अगर (mgr->delayed_destroy_wq == शून्य)
		वापस -ENOMEM;

	INIT_WORK(&mgr->work, drm_dp_mst_link_probe_work);
	INIT_WORK(&mgr->tx_work, drm_dp_tx_work);
	INIT_WORK(&mgr->delayed_destroy_work, drm_dp_delayed_destroy_work);
	INIT_WORK(&mgr->up_req_work, drm_dp_mst_up_req_work);
	init_रुकोqueue_head(&mgr->tx_रुकोq);
	mgr->dev = dev;
	mgr->aux = aux;
	mgr->max_dpcd_transaction_bytes = max_dpcd_transaction_bytes;
	mgr->max_payloads = max_payloads;
	mgr->conn_base_id = conn_base_id;
	अगर (max_payloads + 1 > माप(mgr->payload_mask) * 8 ||
	    max_payloads + 1 > माप(mgr->vcpi_mask) * 8)
		वापस -EINVAL;
	mgr->payloads = kसुस्मृति(max_payloads, माप(काष्ठा drm_dp_payload), GFP_KERNEL);
	अगर (!mgr->payloads)
		वापस -ENOMEM;
	mgr->proposed_vcpis = kसुस्मृति(max_payloads, माप(काष्ठा drm_dp_vcpi *), GFP_KERNEL);
	अगर (!mgr->proposed_vcpis)
		वापस -ENOMEM;
	set_bit(0, &mgr->payload_mask);

	mst_state = kzalloc(माप(*mst_state), GFP_KERNEL);
	अगर (mst_state == शून्य)
		वापस -ENOMEM;

	mst_state->mgr = mgr;
	INIT_LIST_HEAD(&mst_state->vcpis);

	drm_atomic_निजी_obj_init(dev, &mgr->base,
				    &mst_state->base,
				    &drm_dp_mst_topology_state_funcs);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_topology_mgr_init);

/**
 * drm_dp_mst_topology_mgr_destroy() - destroy topology manager.
 * @mgr: manager to destroy
 */
व्योम drm_dp_mst_topology_mgr_destroy(काष्ठा drm_dp_mst_topology_mgr *mgr)
अणु
	drm_dp_mst_topology_mgr_set_mst(mgr, false);
	flush_work(&mgr->work);
	/* The following will also drain any requeued work on the WQ. */
	अगर (mgr->delayed_destroy_wq) अणु
		destroy_workqueue(mgr->delayed_destroy_wq);
		mgr->delayed_destroy_wq = शून्य;
	पूर्ण
	mutex_lock(&mgr->payload_lock);
	kमुक्त(mgr->payloads);
	mgr->payloads = शून्य;
	kमुक्त(mgr->proposed_vcpis);
	mgr->proposed_vcpis = शून्य;
	mutex_unlock(&mgr->payload_lock);
	mgr->dev = शून्य;
	mgr->aux = शून्य;
	drm_atomic_निजी_obj_fini(&mgr->base);
	mgr->funcs = शून्य;

	mutex_destroy(&mgr->delayed_destroy_lock);
	mutex_destroy(&mgr->payload_lock);
	mutex_destroy(&mgr->qlock);
	mutex_destroy(&mgr->lock);
	mutex_destroy(&mgr->up_req_lock);
	mutex_destroy(&mgr->probe_lock);
#अगर IS_ENABLED(CONFIG_DRM_DEBUG_DP_MST_TOPOLOGY_REFS)
	mutex_destroy(&mgr->topology_ref_history_lock);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_topology_mgr_destroy);

अटल bool remote_i2c_पढ़ो_ok(स्थिर काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	पूर्णांक i;

	अगर (num - 1 > DP_REMOTE_I2C_READ_MAX_TRANSACTIONS)
		वापस false;

	क्रम (i = 0; i < num - 1; i++) अणु
		अगर (msgs[i].flags & I2C_M_RD ||
		    msgs[i].len > 0xff)
			वापस false;
	पूर्ण

	वापस msgs[num - 1].flags & I2C_M_RD &&
		msgs[num - 1].len <= 0xff;
पूर्ण

अटल bool remote_i2c_ग_लिखो_ok(स्थिर काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num - 1; i++) अणु
		अगर (msgs[i].flags & I2C_M_RD || !(msgs[i].flags & I2C_M_STOP) ||
		    msgs[i].len > 0xff)
			वापस false;
	पूर्ण

	वापस !(msgs[num - 1].flags & I2C_M_RD) && msgs[num - 1].len <= 0xff;
पूर्ण

अटल पूर्णांक drm_dp_mst_i2c_पढ़ो(काष्ठा drm_dp_mst_branch *mstb,
			       काष्ठा drm_dp_mst_port *port,
			       काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा drm_dp_mst_topology_mgr *mgr = port->mgr;
	अचिन्हित पूर्णांक i;
	काष्ठा drm_dp_sideband_msg_req_body msg;
	काष्ठा drm_dp_sideband_msg_tx *txmsg = शून्य;
	पूर्णांक ret;

	स_रखो(&msg, 0, माप(msg));
	msg.req_type = DP_REMOTE_I2C_READ;
	msg.u.i2c_पढ़ो.num_transactions = num - 1;
	msg.u.i2c_पढ़ो.port_number = port->port_num;
	क्रम (i = 0; i < num - 1; i++) अणु
		msg.u.i2c_पढ़ो.transactions[i].i2c_dev_id = msgs[i].addr;
		msg.u.i2c_पढ़ो.transactions[i].num_bytes = msgs[i].len;
		msg.u.i2c_पढ़ो.transactions[i].bytes = msgs[i].buf;
		msg.u.i2c_पढ़ो.transactions[i].no_stop_bit = !(msgs[i].flags & I2C_M_STOP);
	पूर्ण
	msg.u.i2c_पढ़ो.पढ़ो_i2c_device_id = msgs[num - 1].addr;
	msg.u.i2c_पढ़ो.num_bytes_पढ़ो = msgs[num - 1].len;

	txmsg = kzalloc(माप(*txmsg), GFP_KERNEL);
	अगर (!txmsg) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	txmsg->dst = mstb;
	drm_dp_encode_sideband_req(&msg, txmsg);

	drm_dp_queue_करोwn_tx(mgr, txmsg);

	ret = drm_dp_mst_रुको_tx_reply(mstb, txmsg);
	अगर (ret > 0) अणु

		अगर (txmsg->reply.reply_type == DP_SIDEBAND_REPLY_NAK) अणु
			ret = -EREMOTEIO;
			जाओ out;
		पूर्ण
		अगर (txmsg->reply.u.remote_i2c_पढ़ो_ack.num_bytes != msgs[num - 1].len) अणु
			ret = -EIO;
			जाओ out;
		पूर्ण
		स_नकल(msgs[num - 1].buf, txmsg->reply.u.remote_i2c_पढ़ो_ack.bytes, msgs[num - 1].len);
		ret = num;
	पूर्ण
out:
	kमुक्त(txmsg);
	वापस ret;
पूर्ण

अटल पूर्णांक drm_dp_mst_i2c_ग_लिखो(काष्ठा drm_dp_mst_branch *mstb,
				काष्ठा drm_dp_mst_port *port,
				काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा drm_dp_mst_topology_mgr *mgr = port->mgr;
	अचिन्हित पूर्णांक i;
	काष्ठा drm_dp_sideband_msg_req_body msg;
	काष्ठा drm_dp_sideband_msg_tx *txmsg = शून्य;
	पूर्णांक ret;

	txmsg = kzalloc(माप(*txmsg), GFP_KERNEL);
	अगर (!txmsg) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	क्रम (i = 0; i < num; i++) अणु
		स_रखो(&msg, 0, माप(msg));
		msg.req_type = DP_REMOTE_I2C_WRITE;
		msg.u.i2c_ग_लिखो.port_number = port->port_num;
		msg.u.i2c_ग_लिखो.ग_लिखो_i2c_device_id = msgs[i].addr;
		msg.u.i2c_ग_लिखो.num_bytes = msgs[i].len;
		msg.u.i2c_ग_लिखो.bytes = msgs[i].buf;

		स_रखो(txmsg, 0, माप(*txmsg));
		txmsg->dst = mstb;

		drm_dp_encode_sideband_req(&msg, txmsg);
		drm_dp_queue_करोwn_tx(mgr, txmsg);

		ret = drm_dp_mst_रुको_tx_reply(mstb, txmsg);
		अगर (ret > 0) अणु
			अगर (txmsg->reply.reply_type == DP_SIDEBAND_REPLY_NAK) अणु
				ret = -EREMOTEIO;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			जाओ out;
		पूर्ण
	पूर्ण
	ret = num;
out:
	kमुक्त(txmsg);
	वापस ret;
पूर्ण

/* I2C device */
अटल पूर्णांक drm_dp_mst_i2c_xfer(काष्ठा i2c_adapter *adapter,
			       काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा drm_dp_aux *aux = adapter->algo_data;
	काष्ठा drm_dp_mst_port *port =
		container_of(aux, काष्ठा drm_dp_mst_port, aux);
	काष्ठा drm_dp_mst_branch *mstb;
	काष्ठा drm_dp_mst_topology_mgr *mgr = port->mgr;
	पूर्णांक ret;

	mstb = drm_dp_mst_topology_get_mstb_validated(mgr, port->parent);
	अगर (!mstb)
		वापस -EREMOTEIO;

	अगर (remote_i2c_पढ़ो_ok(msgs, num)) अणु
		ret = drm_dp_mst_i2c_पढ़ो(mstb, port, msgs, num);
	पूर्ण अन्यथा अगर (remote_i2c_ग_लिखो_ok(msgs, num)) अणु
		ret = drm_dp_mst_i2c_ग_लिखो(mstb, port, msgs, num);
	पूर्ण अन्यथा अणु
		DRM_DEBUG_KMS("Unsupported I2C transaction for MST device\n");
		ret = -EIO;
	पूर्ण

	drm_dp_mst_topology_put_mstb(mstb);
	वापस ret;
पूर्ण

अटल u32 drm_dp_mst_i2c_functionality(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL |
	       I2C_FUNC_SMBUS_READ_BLOCK_DATA |
	       I2C_FUNC_SMBUS_BLOCK_PROC_CALL |
	       I2C_FUNC_10BIT_ADDR;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm drm_dp_mst_i2c_algo = अणु
	.functionality = drm_dp_mst_i2c_functionality,
	.master_xfer = drm_dp_mst_i2c_xfer,
पूर्ण;

/**
 * drm_dp_mst_रेजिस्टर_i2c_bus() - रेजिस्टर an I2C adapter क्रम I2C-over-AUX
 * @port: The port to add the I2C bus on
 *
 * Returns 0 on success or a negative error code on failure.
 */
अटल पूर्णांक drm_dp_mst_रेजिस्टर_i2c_bus(काष्ठा drm_dp_mst_port *port)
अणु
	काष्ठा drm_dp_aux *aux = &port->aux;
	काष्ठा device *parent_dev = port->mgr->dev->dev;

	aux->ddc.algo = &drm_dp_mst_i2c_algo;
	aux->ddc.algo_data = aux;
	aux->ddc.retries = 3;

	aux->ddc.class = I2C_CLASS_DDC;
	aux->ddc.owner = THIS_MODULE;
	/* FIXME: set the kdev of the port's connector as parent */
	aux->ddc.dev.parent = parent_dev;
	aux->ddc.dev.of_node = parent_dev->of_node;

	strlcpy(aux->ddc.name, aux->name ? aux->name : dev_name(parent_dev),
		माप(aux->ddc.name));

	वापस i2c_add_adapter(&aux->ddc);
पूर्ण

/**
 * drm_dp_mst_unरेजिस्टर_i2c_bus() - unरेजिस्टर an I2C-over-AUX adapter
 * @port: The port to हटाओ the I2C bus from
 */
अटल व्योम drm_dp_mst_unरेजिस्टर_i2c_bus(काष्ठा drm_dp_mst_port *port)
अणु
	i2c_del_adapter(&port->aux.ddc);
पूर्ण

/**
 * drm_dp_mst_is_भव_dpcd() - Is the given port a भव DP Peer Device
 * @port: The port to check
 *
 * A single physical MST hub object can be represented in the topology
 * by multiple branches, with भव ports between those branches.
 *
 * As of DP1.4, An MST hub with पूर्णांकernal (भव) ports must expose
 * certain DPCD रेजिस्टरs over those ports. See sections 2.6.1.1.1
 * and 2.6.1.1.2 of Display Port specअगरication v1.4 क्रम details.
 *
 * May acquire mgr->lock
 *
 * Returns:
 * true अगर the port is a भव DP peer device, false otherwise
 */
अटल bool drm_dp_mst_is_भव_dpcd(काष्ठा drm_dp_mst_port *port)
अणु
	काष्ठा drm_dp_mst_port *करोwnstream_port;

	अगर (!port || port->dpcd_rev < DP_DPCD_REV_14)
		वापस false;

	/* Virtual DP Sink (Internal Display Panel) */
	अगर (port->port_num >= 8)
		वापस true;

	/* DP-to-HDMI Protocol Converter */
	अगर (port->pdt == DP_PEER_DEVICE_DP_LEGACY_CONV &&
	    !port->mcs &&
	    port->ldps)
		वापस true;

	/* DP-to-DP */
	mutex_lock(&port->mgr->lock);
	अगर (port->pdt == DP_PEER_DEVICE_MST_BRANCHING &&
	    port->mstb &&
	    port->mstb->num_ports == 2) अणु
		list_क्रम_each_entry(करोwnstream_port, &port->mstb->ports, next) अणु
			अगर (करोwnstream_port->pdt == DP_PEER_DEVICE_SST_SINK &&
			    !करोwnstream_port->input) अणु
				mutex_unlock(&port->mgr->lock);
				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&port->mgr->lock);

	वापस false;
पूर्ण

/**
 * drm_dp_mst_dsc_aux_क्रम_port() - Find the correct aux क्रम DSC
 * @port: The port to check. A leaf of the MST tree with an attached display.
 *
 * Depending on the situation, DSC may be enabled via the endpoपूर्णांक aux,
 * the immediately upstream aux, or the connector's physical aux.
 *
 * This is both the correct aux to पढ़ो DSC_CAPABILITY and the
 * correct aux to ग_लिखो DSC_ENABLED.
 *
 * This operation can be expensive (up to four aux पढ़ोs), so
 * the caller should cache the वापस.
 *
 * Returns:
 * शून्य अगर DSC cannot be enabled on this port, otherwise the aux device
 */
काष्ठा drm_dp_aux *drm_dp_mst_dsc_aux_क्रम_port(काष्ठा drm_dp_mst_port *port)
अणु
	काष्ठा drm_dp_mst_port *immediate_upstream_port;
	काष्ठा drm_dp_mst_port *fec_port;
	काष्ठा drm_dp_desc desc = अणुपूर्ण;
	u8 endpoपूर्णांक_fec;
	u8 endpoपूर्णांक_dsc;

	अगर (!port)
		वापस शून्य;

	अगर (port->parent->port_parent)
		immediate_upstream_port = port->parent->port_parent;
	अन्यथा
		immediate_upstream_port = शून्य;

	fec_port = immediate_upstream_port;
	जबतक (fec_port) अणु
		/*
		 * Each physical link (i.e. not a भव port) between the
		 * output and the primary device must support FEC
		 */
		अगर (!drm_dp_mst_is_भव_dpcd(fec_port) &&
		    !fec_port->fec_capable)
			वापस शून्य;

		fec_port = fec_port->parent->port_parent;
	पूर्ण

	/* DP-to-DP peer device */
	अगर (drm_dp_mst_is_भव_dpcd(immediate_upstream_port)) अणु
		u8 upstream_dsc;

		अगर (drm_dp_dpcd_पढ़ो(&port->aux,
				     DP_DSC_SUPPORT, &endpoपूर्णांक_dsc, 1) != 1)
			वापस शून्य;
		अगर (drm_dp_dpcd_पढ़ो(&port->aux,
				     DP_FEC_CAPABILITY, &endpoपूर्णांक_fec, 1) != 1)
			वापस शून्य;
		अगर (drm_dp_dpcd_पढ़ो(&immediate_upstream_port->aux,
				     DP_DSC_SUPPORT, &upstream_dsc, 1) != 1)
			वापस शून्य;

		/* Enpoपूर्णांक decompression with DP-to-DP peer device */
		अगर ((endpoपूर्णांक_dsc & DP_DSC_DECOMPRESSION_IS_SUPPORTED) &&
		    (endpoपूर्णांक_fec & DP_FEC_CAPABLE) &&
		    (upstream_dsc & 0x2) /* DSC passthrough */)
			वापस &port->aux;

		/* Virtual DPCD decompression with DP-to-DP peer device */
		वापस &immediate_upstream_port->aux;
	पूर्ण

	/* Virtual DPCD decompression with DP-to-HDMI or Virtual DP Sink */
	अगर (drm_dp_mst_is_भव_dpcd(port))
		वापस &port->aux;

	/*
	 * Synaptics quirk
	 * Applies to ports क्रम which:
	 * - Physical aux has Synaptics OUI
	 * - DPv1.4 or higher
	 * - Port is on primary branch device
	 * - Not a VGA adapter (DP_DWN_STRM_PORT_TYPE_ANALOG)
	 */
	अगर (drm_dp_पढ़ो_desc(port->mgr->aux, &desc, true))
		वापस शून्य;

	अगर (drm_dp_has_quirk(&desc, DP_DPCD_QUIRK_DSC_WITHOUT_VIRTUAL_DPCD) &&
	    port->mgr->dpcd[DP_DPCD_REV] >= DP_DPCD_REV_14 &&
	    port->parent == port->mgr->mst_primary) अणु
		u8 करोwnstreamport;

		अगर (drm_dp_dpcd_पढ़ो(&port->aux, DP_DOWNSTREAMPORT_PRESENT,
				     &करोwnstreamport, 1) < 0)
			वापस शून्य;

		अगर ((करोwnstreamport & DP_DWN_STRM_PORT_PRESENT) &&
		   ((करोwnstreamport & DP_DWN_STRM_PORT_TYPE_MASK)
		     != DP_DWN_STRM_PORT_TYPE_ANALOG))
			वापस port->mgr->aux;
	पूर्ण

	/*
	 * The check below verअगरies अगर the MST sink
	 * connected to the GPU is capable of DSC -
	 * thereक्रमe the endpoपूर्णांक needs to be
	 * both DSC and FEC capable.
	 */
	अगर (drm_dp_dpcd_पढ़ो(&port->aux,
	   DP_DSC_SUPPORT, &endpoपूर्णांक_dsc, 1) != 1)
		वापस शून्य;
	अगर (drm_dp_dpcd_पढ़ो(&port->aux,
	   DP_FEC_CAPABILITY, &endpoपूर्णांक_fec, 1) != 1)
		वापस शून्य;
	अगर ((endpoपूर्णांक_dsc & DP_DSC_DECOMPRESSION_IS_SUPPORTED) &&
	   (endpoपूर्णांक_fec & DP_FEC_CAPABLE))
		वापस &port->aux;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(drm_dp_mst_dsc_aux_क्रम_port);
