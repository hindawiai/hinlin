<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Test हालs क्रम क्रम the DRM DP MST helpers
 */

#घोषणा PREFIX_STR "[drm_dp_mst_helper]"

#समावेश <linux/अक्रमom.h>

#समावेश <drm/drm_dp_mst_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "../drm_dp_mst_topology_internal.h"
#समावेश "test-drm_modeset_common.h"

पूर्णांक igt_dp_mst_calc_pbn_mode(व्योम *ignored)
अणु
	पूर्णांक pbn, i;
	स्थिर काष्ठा अणु
		पूर्णांक rate;
		पूर्णांक bpp;
		पूर्णांक expected;
		bool dsc;
	पूर्ण test_params[] = अणु
		अणु 154000, 30, 689, false पूर्ण,
		अणु 234000, 30, 1047, false पूर्ण,
		अणु 297000, 24, 1063, false पूर्ण,
		अणु 332880, 24, 50, true पूर्ण,
		अणु 324540, 24, 49, true पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(test_params); i++) अणु
		pbn = drm_dp_calc_pbn_mode(test_params[i].rate,
					   test_params[i].bpp,
					   test_params[i].dsc);
		FAIL(pbn != test_params[i].expected,
		     "Expected PBN %d for clock %d bpp %d, got %d\n",
		     test_params[i].expected, test_params[i].rate,
		     test_params[i].bpp, pbn);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
sideband_msg_req_equal(स्थिर काष्ठा drm_dp_sideband_msg_req_body *in,
		       स्थिर काष्ठा drm_dp_sideband_msg_req_body *out)
अणु
	स्थिर काष्ठा drm_dp_remote_i2c_पढ़ो_tx *txin, *txout;
	पूर्णांक i;

	अगर (in->req_type != out->req_type)
		वापस false;

	चयन (in->req_type) अणु
	/*
	 * Compare काष्ठा members manually क्रम request types which can't be
	 * compared simply using स_भेद(). This is because said request types
	 * contain poपूर्णांकers to other allocated काष्ठाs
	 */
	हाल DP_REMOTE_I2C_READ:
#घोषणा IN in->u.i2c_पढ़ो
#घोषणा OUT out->u.i2c_पढ़ो
		अगर (IN.num_bytes_पढ़ो != OUT.num_bytes_पढ़ो ||
		    IN.num_transactions != OUT.num_transactions ||
		    IN.port_number != OUT.port_number ||
		    IN.पढ़ो_i2c_device_id != OUT.पढ़ो_i2c_device_id)
			वापस false;

		क्रम (i = 0; i < IN.num_transactions; i++) अणु
			txin = &IN.transactions[i];
			txout = &OUT.transactions[i];

			अगर (txin->i2c_dev_id != txout->i2c_dev_id ||
			    txin->no_stop_bit != txout->no_stop_bit ||
			    txin->num_bytes != txout->num_bytes ||
			    txin->i2c_transaction_delay !=
			    txout->i2c_transaction_delay)
				वापस false;

			अगर (स_भेद(txin->bytes, txout->bytes,
				   txin->num_bytes) != 0)
				वापस false;
		पूर्ण
		अवरोध;
#अघोषित IN
#अघोषित OUT

	हाल DP_REMOTE_DPCD_WRITE:
#घोषणा IN in->u.dpcd_ग_लिखो
#घोषणा OUT out->u.dpcd_ग_लिखो
		अगर (IN.dpcd_address != OUT.dpcd_address ||
		    IN.num_bytes != OUT.num_bytes ||
		    IN.port_number != OUT.port_number)
			वापस false;

		वापस स_भेद(IN.bytes, OUT.bytes, IN.num_bytes) == 0;
#अघोषित IN
#अघोषित OUT

	हाल DP_REMOTE_I2C_WRITE:
#घोषणा IN in->u.i2c_ग_लिखो
#घोषणा OUT out->u.i2c_ग_लिखो
		अगर (IN.port_number != OUT.port_number ||
		    IN.ग_लिखो_i2c_device_id != OUT.ग_लिखो_i2c_device_id ||
		    IN.num_bytes != OUT.num_bytes)
			वापस false;

		वापस स_भेद(IN.bytes, OUT.bytes, IN.num_bytes) == 0;
#अघोषित IN
#अघोषित OUT

	शेष:
		वापस स_भेद(in, out, माप(*in)) == 0;
	पूर्ण

	वापस true;
पूर्ण

अटल bool
sideband_msg_req_encode_decode(काष्ठा drm_dp_sideband_msg_req_body *in)
अणु
	काष्ठा drm_dp_sideband_msg_req_body *out;
	काष्ठा drm_prपूर्णांकer p = drm_err_prपूर्णांकer(PREFIX_STR);
	काष्ठा drm_dp_sideband_msg_tx *txmsg;
	पूर्णांक i, ret;
	bool result = true;

	out = kzalloc(माप(*out), GFP_KERNEL);
	अगर (!out)
		वापस false;

	txmsg = kzalloc(माप(*txmsg), GFP_KERNEL);
	अगर (!txmsg)
		वापस false;

	drm_dp_encode_sideband_req(in, txmsg);
	ret = drm_dp_decode_sideband_req(txmsg, out);
	अगर (ret < 0) अणु
		drm_म_लिखो(&p, "Failed to decode sideband request: %d\n",
			   ret);
		result = false;
		जाओ out;
	पूर्ण

	अगर (!sideband_msg_req_equal(in, out)) अणु
		drm_म_लिखो(&p, "Encode/decode failed, expected:\n");
		drm_dp_dump_sideband_msg_req_body(in, 1, &p);
		drm_म_लिखो(&p, "Got:\n");
		drm_dp_dump_sideband_msg_req_body(out, 1, &p);
		result = false;
		जाओ out;
	पूर्ण

	चयन (in->req_type) अणु
	हाल DP_REMOTE_DPCD_WRITE:
		kमुक्त(out->u.dpcd_ग_लिखो.bytes);
		अवरोध;
	हाल DP_REMOTE_I2C_READ:
		क्रम (i = 0; i < out->u.i2c_पढ़ो.num_transactions; i++)
			kमुक्त(out->u.i2c_पढ़ो.transactions[i].bytes);
		अवरोध;
	हाल DP_REMOTE_I2C_WRITE:
		kमुक्त(out->u.i2c_ग_लिखो.bytes);
		अवरोध;
	पूर्ण

	/* Clear everything but the req_type क्रम the input */
	स_रखो(&in->u, 0, माप(in->u));

out:
	kमुक्त(out);
	kमुक्त(txmsg);
	वापस result;
पूर्ण

पूर्णांक igt_dp_mst_sideband_msg_req_decode(व्योम *unused)
अणु
	काष्ठा drm_dp_sideband_msg_req_body in = अणु 0 पूर्ण;
	u8 data[] = अणु 0xff, 0x0, 0xdd पूर्ण;
	पूर्णांक i;

#घोषणा DO_TEST() FAIL_ON(!sideband_msg_req_encode_decode(&in))

	in.req_type = DP_ENUM_PATH_RESOURCES;
	in.u.port_num.port_number = 5;
	DO_TEST();

	in.req_type = DP_POWER_UP_PHY;
	in.u.port_num.port_number = 5;
	DO_TEST();

	in.req_type = DP_POWER_DOWN_PHY;
	in.u.port_num.port_number = 5;
	DO_TEST();

	in.req_type = DP_ALLOCATE_PAYLOAD;
	in.u.allocate_payload.number_sdp_streams = 3;
	क्रम (i = 0; i < in.u.allocate_payload.number_sdp_streams; i++)
		in.u.allocate_payload.sdp_stream_sink[i] = i + 1;
	DO_TEST();
	in.u.allocate_payload.port_number = 0xf;
	DO_TEST();
	in.u.allocate_payload.vcpi = 0x7f;
	DO_TEST();
	in.u.allocate_payload.pbn = U16_MAX;
	DO_TEST();

	in.req_type = DP_QUERY_PAYLOAD;
	in.u.query_payload.port_number = 0xf;
	DO_TEST();
	in.u.query_payload.vcpi = 0x7f;
	DO_TEST();

	in.req_type = DP_REMOTE_DPCD_READ;
	in.u.dpcd_पढ़ो.port_number = 0xf;
	DO_TEST();
	in.u.dpcd_पढ़ो.dpcd_address = 0xfedcb;
	DO_TEST();
	in.u.dpcd_पढ़ो.num_bytes = U8_MAX;
	DO_TEST();

	in.req_type = DP_REMOTE_DPCD_WRITE;
	in.u.dpcd_ग_लिखो.port_number = 0xf;
	DO_TEST();
	in.u.dpcd_ग_लिखो.dpcd_address = 0xfedcb;
	DO_TEST();
	in.u.dpcd_ग_लिखो.num_bytes = ARRAY_SIZE(data);
	in.u.dpcd_ग_लिखो.bytes = data;
	DO_TEST();

	in.req_type = DP_REMOTE_I2C_READ;
	in.u.i2c_पढ़ो.port_number = 0xf;
	DO_TEST();
	in.u.i2c_पढ़ो.पढ़ो_i2c_device_id = 0x7f;
	DO_TEST();
	in.u.i2c_पढ़ो.num_transactions = 3;
	in.u.i2c_पढ़ो.num_bytes_पढ़ो = ARRAY_SIZE(data) * 3;
	क्रम (i = 0; i < in.u.i2c_पढ़ो.num_transactions; i++) अणु
		in.u.i2c_पढ़ो.transactions[i].bytes = data;
		in.u.i2c_पढ़ो.transactions[i].num_bytes = ARRAY_SIZE(data);
		in.u.i2c_पढ़ो.transactions[i].i2c_dev_id = 0x7f & ~i;
		in.u.i2c_पढ़ो.transactions[i].i2c_transaction_delay = 0xf & ~i;
	पूर्ण
	DO_TEST();

	in.req_type = DP_REMOTE_I2C_WRITE;
	in.u.i2c_ग_लिखो.port_number = 0xf;
	DO_TEST();
	in.u.i2c_ग_लिखो.ग_लिखो_i2c_device_id = 0x7f;
	DO_TEST();
	in.u.i2c_ग_लिखो.num_bytes = ARRAY_SIZE(data);
	in.u.i2c_ग_लिखो.bytes = data;
	DO_TEST();

	in.req_type = DP_QUERY_STREAM_ENC_STATUS;
	in.u.enc_status.stream_id = 1;
	DO_TEST();
	get_अक्रमom_bytes(in.u.enc_status.client_id,
			 माप(in.u.enc_status.client_id));
	DO_TEST();
	in.u.enc_status.stream_event = 3;
	DO_TEST();
	in.u.enc_status.valid_stream_event = 0;
	DO_TEST();
	in.u.enc_status.stream_behavior = 3;
	DO_TEST();
	in.u.enc_status.valid_stream_behavior = 1;
	DO_TEST();

#अघोषित DO_TEST
	वापस 0;
पूर्ण
