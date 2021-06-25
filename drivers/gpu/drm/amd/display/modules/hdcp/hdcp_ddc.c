<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#समावेश "hdcp.h"

#घोषणा MIN(a, b) ((a) < (b) ? (a) : (b))
#घोषणा HDCP_I2C_ADDR 0x3a	/* 0x74 >> 1*/
#घोषणा KSV_READ_SIZE 0xf	/* 0x6803b - 0x6802c */
#घोषणा HDCP_MAX_AUX_TRANSACTION_SIZE 16

#घोषणा DP_CP_IRQ (1 << 2)

क्रमागत mod_hdcp_ddc_message_id अणु
	MOD_HDCP_MESSAGE_ID_INVALID = -1,

	/* HDCP 1.4 */

	MOD_HDCP_MESSAGE_ID_READ_BKSV = 0,
	MOD_HDCP_MESSAGE_ID_READ_RI_R0,
	MOD_HDCP_MESSAGE_ID_WRITE_AKSV,
	MOD_HDCP_MESSAGE_ID_WRITE_AINFO,
	MOD_HDCP_MESSAGE_ID_WRITE_AN,
	MOD_HDCP_MESSAGE_ID_READ_VH_X,
	MOD_HDCP_MESSAGE_ID_READ_VH_0,
	MOD_HDCP_MESSAGE_ID_READ_VH_1,
	MOD_HDCP_MESSAGE_ID_READ_VH_2,
	MOD_HDCP_MESSAGE_ID_READ_VH_3,
	MOD_HDCP_MESSAGE_ID_READ_VH_4,
	MOD_HDCP_MESSAGE_ID_READ_BCAPS,
	MOD_HDCP_MESSAGE_ID_READ_BSTATUS,
	MOD_HDCP_MESSAGE_ID_READ_KSV_FIFO,
	MOD_HDCP_MESSAGE_ID_READ_BINFO,

	/* HDCP 2.2 */

	MOD_HDCP_MESSAGE_ID_HDCP2VERSION,
	MOD_HDCP_MESSAGE_ID_RX_CAPS,
	MOD_HDCP_MESSAGE_ID_WRITE_AKE_INIT,
	MOD_HDCP_MESSAGE_ID_READ_AKE_SEND_CERT,
	MOD_HDCP_MESSAGE_ID_WRITE_AKE_NO_STORED_KM,
	MOD_HDCP_MESSAGE_ID_WRITE_AKE_STORED_KM,
	MOD_HDCP_MESSAGE_ID_READ_AKE_SEND_H_PRIME,
	MOD_HDCP_MESSAGE_ID_READ_AKE_SEND_PAIRING_INFO,
	MOD_HDCP_MESSAGE_ID_WRITE_LC_INIT,
	MOD_HDCP_MESSAGE_ID_READ_LC_SEND_L_PRIME,
	MOD_HDCP_MESSAGE_ID_WRITE_SKE_SEND_EKS,
	MOD_HDCP_MESSAGE_ID_READ_REPEATER_AUTH_SEND_RECEIVERID_LIST,
	MOD_HDCP_MESSAGE_ID_READ_REPEATER_AUTH_SEND_RECEIVERID_LIST_PART2,
	MOD_HDCP_MESSAGE_ID_WRITE_REPEATER_AUTH_SEND_ACK,
	MOD_HDCP_MESSAGE_ID_WRITE_REPEATER_AUTH_STREAM_MANAGE,
	MOD_HDCP_MESSAGE_ID_READ_REPEATER_AUTH_STREAM_READY,
	MOD_HDCP_MESSAGE_ID_READ_RXSTATUS,
	MOD_HDCP_MESSAGE_ID_WRITE_CONTENT_STREAM_TYPE,

	MOD_HDCP_MESSAGE_ID_MAX
पूर्ण;

अटल स्थिर uपूर्णांक8_t hdcp_i2c_offsets[] = अणु
	[MOD_HDCP_MESSAGE_ID_READ_BKSV] = 0x0,
	[MOD_HDCP_MESSAGE_ID_READ_RI_R0] = 0x8,
	[MOD_HDCP_MESSAGE_ID_WRITE_AKSV] = 0x10,
	[MOD_HDCP_MESSAGE_ID_WRITE_AINFO] = 0x15,
	[MOD_HDCP_MESSAGE_ID_WRITE_AN] = 0x18,
	[MOD_HDCP_MESSAGE_ID_READ_VH_X] = 0x20,
	[MOD_HDCP_MESSAGE_ID_READ_VH_0] = 0x20,
	[MOD_HDCP_MESSAGE_ID_READ_VH_1] = 0x24,
	[MOD_HDCP_MESSAGE_ID_READ_VH_2] = 0x28,
	[MOD_HDCP_MESSAGE_ID_READ_VH_3] = 0x2C,
	[MOD_HDCP_MESSAGE_ID_READ_VH_4] = 0x30,
	[MOD_HDCP_MESSAGE_ID_READ_BCAPS] = 0x40,
	[MOD_HDCP_MESSAGE_ID_READ_BSTATUS] = 0x41,
	[MOD_HDCP_MESSAGE_ID_READ_KSV_FIFO] = 0x43,
	[MOD_HDCP_MESSAGE_ID_READ_BINFO] = 0xFF,
	[MOD_HDCP_MESSAGE_ID_HDCP2VERSION] = 0x50,
	[MOD_HDCP_MESSAGE_ID_WRITE_AKE_INIT] = 0x60,
	[MOD_HDCP_MESSAGE_ID_READ_AKE_SEND_CERT] = 0x80,
	[MOD_HDCP_MESSAGE_ID_WRITE_AKE_NO_STORED_KM] = 0x60,
	[MOD_HDCP_MESSAGE_ID_WRITE_AKE_STORED_KM] = 0x60,
	[MOD_HDCP_MESSAGE_ID_READ_AKE_SEND_H_PRIME] = 0x80,
	[MOD_HDCP_MESSAGE_ID_READ_AKE_SEND_PAIRING_INFO] = 0x80,
	[MOD_HDCP_MESSAGE_ID_WRITE_LC_INIT] = 0x60,
	[MOD_HDCP_MESSAGE_ID_READ_LC_SEND_L_PRIME] = 0x80,
	[MOD_HDCP_MESSAGE_ID_WRITE_SKE_SEND_EKS] = 0x60,
	[MOD_HDCP_MESSAGE_ID_READ_REPEATER_AUTH_SEND_RECEIVERID_LIST] = 0x80,
	[MOD_HDCP_MESSAGE_ID_READ_REPEATER_AUTH_SEND_RECEIVERID_LIST_PART2] = 0x80,
	[MOD_HDCP_MESSAGE_ID_WRITE_REPEATER_AUTH_SEND_ACK] = 0x60,
	[MOD_HDCP_MESSAGE_ID_WRITE_REPEATER_AUTH_STREAM_MANAGE] = 0x60,
	[MOD_HDCP_MESSAGE_ID_READ_REPEATER_AUTH_STREAM_READY] = 0x80,
	[MOD_HDCP_MESSAGE_ID_READ_RXSTATUS] = 0x70,
	[MOD_HDCP_MESSAGE_ID_WRITE_CONTENT_STREAM_TYPE] = 0x0
पूर्ण;

अटल स्थिर uपूर्णांक32_t hdcp_dpcd_addrs[] = अणु
	[MOD_HDCP_MESSAGE_ID_READ_BKSV] = 0x68000,
	[MOD_HDCP_MESSAGE_ID_READ_RI_R0] = 0x68005,
	[MOD_HDCP_MESSAGE_ID_WRITE_AKSV] = 0x68007,
	[MOD_HDCP_MESSAGE_ID_WRITE_AINFO] = 0x6803B,
	[MOD_HDCP_MESSAGE_ID_WRITE_AN] = 0x6800c,
	[MOD_HDCP_MESSAGE_ID_READ_VH_X] = 0x68014,
	[MOD_HDCP_MESSAGE_ID_READ_VH_0] = 0x68014,
	[MOD_HDCP_MESSAGE_ID_READ_VH_1] = 0x68018,
	[MOD_HDCP_MESSAGE_ID_READ_VH_2] = 0x6801c,
	[MOD_HDCP_MESSAGE_ID_READ_VH_3] = 0x68020,
	[MOD_HDCP_MESSAGE_ID_READ_VH_4] = 0x68024,
	[MOD_HDCP_MESSAGE_ID_READ_BCAPS] = 0x68028,
	[MOD_HDCP_MESSAGE_ID_READ_BSTATUS] = 0x68029,
	[MOD_HDCP_MESSAGE_ID_READ_KSV_FIFO] = 0x6802c,
	[MOD_HDCP_MESSAGE_ID_READ_BINFO] = 0x6802a,
	[MOD_HDCP_MESSAGE_ID_RX_CAPS] = 0x6921d,
	[MOD_HDCP_MESSAGE_ID_WRITE_AKE_INIT] = 0x69000,
	[MOD_HDCP_MESSAGE_ID_READ_AKE_SEND_CERT] = 0x6900b,
	[MOD_HDCP_MESSAGE_ID_WRITE_AKE_NO_STORED_KM] = 0x69220,
	[MOD_HDCP_MESSAGE_ID_WRITE_AKE_STORED_KM] = 0x692a0,
	[MOD_HDCP_MESSAGE_ID_READ_AKE_SEND_H_PRIME] = 0x692c0,
	[MOD_HDCP_MESSAGE_ID_READ_AKE_SEND_PAIRING_INFO] = 0x692e0,
	[MOD_HDCP_MESSAGE_ID_WRITE_LC_INIT] = 0x692f0,
	[MOD_HDCP_MESSAGE_ID_READ_LC_SEND_L_PRIME] = 0x692f8,
	[MOD_HDCP_MESSAGE_ID_WRITE_SKE_SEND_EKS] = 0x69318,
	[MOD_HDCP_MESSAGE_ID_READ_REPEATER_AUTH_SEND_RECEIVERID_LIST] = 0x69330,
	[MOD_HDCP_MESSAGE_ID_READ_REPEATER_AUTH_SEND_RECEIVERID_LIST_PART2] = 0x69340,
	[MOD_HDCP_MESSAGE_ID_WRITE_REPEATER_AUTH_SEND_ACK] = 0x693e0,
	[MOD_HDCP_MESSAGE_ID_WRITE_REPEATER_AUTH_STREAM_MANAGE] = 0x693f0,
	[MOD_HDCP_MESSAGE_ID_READ_REPEATER_AUTH_STREAM_READY] = 0x69473,
	[MOD_HDCP_MESSAGE_ID_READ_RXSTATUS] = 0x69493,
	[MOD_HDCP_MESSAGE_ID_WRITE_CONTENT_STREAM_TYPE] = 0x69494
पूर्ण;

अटल क्रमागत mod_hdcp_status पढ़ो(काष्ठा mod_hdcp *hdcp,
		क्रमागत mod_hdcp_ddc_message_id msg_id,
		uपूर्णांक8_t *buf,
		uपूर्णांक32_t buf_len)
अणु
	bool success = true;
	uपूर्णांक32_t cur_size = 0;
	uपूर्णांक32_t data_offset = 0;

	अगर (is_dp_hdcp(hdcp)) अणु
		जबतक (buf_len > 0) अणु
			cur_size = MIN(buf_len, HDCP_MAX_AUX_TRANSACTION_SIZE);
			success = hdcp->config.ddc.funcs.पढ़ो_dpcd(hdcp->config.ddc.handle,
					hdcp_dpcd_addrs[msg_id] + data_offset,
					buf + data_offset,
					cur_size);

			अगर (!success)
				अवरोध;

			buf_len -= cur_size;
			data_offset += cur_size;
		पूर्ण
	पूर्ण अन्यथा अणु
		success = hdcp->config.ddc.funcs.पढ़ो_i2c(
				hdcp->config.ddc.handle,
				HDCP_I2C_ADDR,
				hdcp_i2c_offsets[msg_id],
				buf,
				(uपूर्णांक32_t)buf_len);
	पूर्ण

	वापस success ? MOD_HDCP_STATUS_SUCCESS : MOD_HDCP_STATUS_DDC_FAILURE;
पूर्ण

अटल क्रमागत mod_hdcp_status पढ़ो_repeatedly(काष्ठा mod_hdcp *hdcp,
		क्रमागत mod_hdcp_ddc_message_id msg_id,
		uपूर्णांक8_t *buf,
		uपूर्णांक32_t buf_len,
		uपूर्णांक8_t पढ़ो_size)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_DDC_FAILURE;
	uपूर्णांक32_t cur_size = 0;
	uपूर्णांक32_t data_offset = 0;

	जबतक (buf_len > 0) अणु
		cur_size = MIN(buf_len, पढ़ो_size);
		status = पढ़ो(hdcp, msg_id, buf + data_offset, cur_size);

		अगर (status != MOD_HDCP_STATUS_SUCCESS)
			अवरोध;

		buf_len -= cur_size;
		data_offset += cur_size;
	पूर्ण

	वापस status;
पूर्ण

अटल क्रमागत mod_hdcp_status ग_लिखो(काष्ठा mod_hdcp *hdcp,
		क्रमागत mod_hdcp_ddc_message_id msg_id,
		uपूर्णांक8_t *buf,
		uपूर्णांक32_t buf_len)
अणु
	bool success = true;
	uपूर्णांक32_t cur_size = 0;
	uपूर्णांक32_t data_offset = 0;

	अगर (is_dp_hdcp(hdcp)) अणु
		जबतक (buf_len > 0) अणु
			cur_size = MIN(buf_len, HDCP_MAX_AUX_TRANSACTION_SIZE);
			success = hdcp->config.ddc.funcs.ग_लिखो_dpcd(
					hdcp->config.ddc.handle,
					hdcp_dpcd_addrs[msg_id] + data_offset,
					buf + data_offset,
					cur_size);

			अगर (!success)
				अवरोध;

			buf_len -= cur_size;
			data_offset += cur_size;
		पूर्ण
	पूर्ण अन्यथा अणु
		hdcp->buf[0] = hdcp_i2c_offsets[msg_id];
		स_हटाओ(&hdcp->buf[1], buf, buf_len);
		success = hdcp->config.ddc.funcs.ग_लिखो_i2c(
				hdcp->config.ddc.handle,
				HDCP_I2C_ADDR,
				hdcp->buf,
				(uपूर्णांक32_t)(buf_len+1));
	पूर्ण

	वापस success ? MOD_HDCP_STATUS_SUCCESS : MOD_HDCP_STATUS_DDC_FAILURE;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_bksv(काष्ठा mod_hdcp *hdcp)
अणु
	वापस पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_BKSV,
			hdcp->auth.msg.hdcp1.bksv,
			माप(hdcp->auth.msg.hdcp1.bksv));
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_bcaps(काष्ठा mod_hdcp *hdcp)
अणु
	वापस पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_BCAPS,
			&hdcp->auth.msg.hdcp1.bcaps,
			माप(hdcp->auth.msg.hdcp1.bcaps));
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_bstatus(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp))
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_BSTATUS,
					(uपूर्णांक8_t *)&hdcp->auth.msg.hdcp1.bstatus,
					1);
	अन्यथा
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_BSTATUS,
				(uपूर्णांक8_t *)&hdcp->auth.msg.hdcp1.bstatus,
				माप(hdcp->auth.msg.hdcp1.bstatus));
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_r0p(काष्ठा mod_hdcp *hdcp)
अणु
	वापस पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_RI_R0,
			(uपूर्णांक8_t *)&hdcp->auth.msg.hdcp1.r0p,
			माप(hdcp->auth.msg.hdcp1.r0p));
पूर्ण

/* special हाल, पढ़ोing repeatedly at the same address, करोn't use पढ़ो() */
क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_ksvlist(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp))
		status = पढ़ो_repeatedly(hdcp, MOD_HDCP_MESSAGE_ID_READ_KSV_FIFO,
				hdcp->auth.msg.hdcp1.ksvlist,
				hdcp->auth.msg.hdcp1.ksvlist_size,
				KSV_READ_SIZE);
	अन्यथा
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_KSV_FIFO,
				(uपूर्णांक8_t *)&hdcp->auth.msg.hdcp1.ksvlist,
				hdcp->auth.msg.hdcp1.ksvlist_size);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_vp(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_VH_0,
			&hdcp->auth.msg.hdcp1.vp[0], 4);
	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		जाओ out;

	status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_VH_1,
			&hdcp->auth.msg.hdcp1.vp[4], 4);
	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		जाओ out;

	status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_VH_2,
			&hdcp->auth.msg.hdcp1.vp[8], 4);
	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		जाओ out;

	status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_VH_3,
			&hdcp->auth.msg.hdcp1.vp[12], 4);
	अगर (status != MOD_HDCP_STATUS_SUCCESS)
		जाओ out;

	status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_VH_4,
			&hdcp->auth.msg.hdcp1.vp[16], 4);
out:
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_binfo(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp))
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_BINFO,
				(uपूर्णांक8_t *)&hdcp->auth.msg.hdcp1.binfo_dp,
				माप(hdcp->auth.msg.hdcp1.binfo_dp));
	अन्यथा
		status = MOD_HDCP_STATUS_INVALID_OPERATION;

	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_aksv(काष्ठा mod_hdcp *hdcp)
अणु
	वापस ग_लिखो(hdcp, MOD_HDCP_MESSAGE_ID_WRITE_AKSV,
			hdcp->auth.msg.hdcp1.aksv,
			माप(hdcp->auth.msg.hdcp1.aksv));
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_ainfo(काष्ठा mod_hdcp *hdcp)
अणु
	वापस ग_लिखो(hdcp, MOD_HDCP_MESSAGE_ID_WRITE_AINFO,
			&hdcp->auth.msg.hdcp1.ainfo,
			माप(hdcp->auth.msg.hdcp1.ainfo));
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_an(काष्ठा mod_hdcp *hdcp)
अणु
	वापस ग_लिखो(hdcp, MOD_HDCP_MESSAGE_ID_WRITE_AN,
			hdcp->auth.msg.hdcp1.an,
			माप(hdcp->auth.msg.hdcp1.an));
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_hdcp2version(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp))
		status = MOD_HDCP_STATUS_INVALID_OPERATION;
	अन्यथा
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_HDCP2VERSION,
				&hdcp->auth.msg.hdcp2.hdcp2version_hdmi,
				माप(hdcp->auth.msg.hdcp2.hdcp2version_hdmi));

	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_rxcaps(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (!is_dp_hdcp(hdcp))
		status = MOD_HDCP_STATUS_INVALID_OPERATION;
	अन्यथा
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_RX_CAPS,
				hdcp->auth.msg.hdcp2.rxcaps_dp,
				माप(hdcp->auth.msg.hdcp2.rxcaps_dp));

	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_rxstatus(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp)) अणु
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_RXSTATUS,
				&hdcp->auth.msg.hdcp2.rxstatus_dp,
				1);
	पूर्ण अन्यथा अणु
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_RXSTATUS,
					(uपूर्णांक8_t *)&hdcp->auth.msg.hdcp2.rxstatus,
					माप(hdcp->auth.msg.hdcp2.rxstatus));
	पूर्ण
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_ake_cert(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp)) अणु
		hdcp->auth.msg.hdcp2.ake_cert[0] = HDCP_2_2_AKE_SEND_CERT;
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_AKE_SEND_CERT,
				hdcp->auth.msg.hdcp2.ake_cert+1,
				माप(hdcp->auth.msg.hdcp2.ake_cert)-1);

	पूर्ण अन्यथा अणु
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_AKE_SEND_CERT,
					hdcp->auth.msg.hdcp2.ake_cert,
					माप(hdcp->auth.msg.hdcp2.ake_cert));
	पूर्ण
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_h_prime(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp)) अणु
		hdcp->auth.msg.hdcp2.ake_h_prime[0] = HDCP_2_2_AKE_SEND_HPRIME;
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_AKE_SEND_H_PRIME,
				hdcp->auth.msg.hdcp2.ake_h_prime+1,
				माप(hdcp->auth.msg.hdcp2.ake_h_prime)-1);

	पूर्ण अन्यथा अणु
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_AKE_SEND_H_PRIME,
				hdcp->auth.msg.hdcp2.ake_h_prime,
				माप(hdcp->auth.msg.hdcp2.ake_h_prime));
	पूर्ण
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_pairing_info(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp)) अणु
		hdcp->auth.msg.hdcp2.ake_pairing_info[0] = HDCP_2_2_AKE_SEND_PAIRING_INFO;
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_AKE_SEND_PAIRING_INFO,
				hdcp->auth.msg.hdcp2.ake_pairing_info+1,
				माप(hdcp->auth.msg.hdcp2.ake_pairing_info)-1);

	पूर्ण अन्यथा अणु
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_AKE_SEND_PAIRING_INFO,
				hdcp->auth.msg.hdcp2.ake_pairing_info,
				माप(hdcp->auth.msg.hdcp2.ake_pairing_info));
	पूर्ण
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_l_prime(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp)) अणु
		hdcp->auth.msg.hdcp2.lc_l_prime[0] = HDCP_2_2_LC_SEND_LPRIME;
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_LC_SEND_L_PRIME,
				hdcp->auth.msg.hdcp2.lc_l_prime+1,
				माप(hdcp->auth.msg.hdcp2.lc_l_prime)-1);

	पूर्ण अन्यथा अणु
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_LC_SEND_L_PRIME,
				hdcp->auth.msg.hdcp2.lc_l_prime,
				माप(hdcp->auth.msg.hdcp2.lc_l_prime));
	पूर्ण
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_rx_id_list(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	अगर (is_dp_hdcp(hdcp)) अणु
		uपूर्णांक32_t device_count = 0;
		uपूर्णांक32_t rx_id_list_size = 0;
		uपूर्णांक32_t bytes_पढ़ो = 0;

		hdcp->auth.msg.hdcp2.rx_id_list[0] = HDCP_2_2_REP_SEND_RECVID_LIST;
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_REPEATER_AUTH_SEND_RECEIVERID_LIST,
						hdcp->auth.msg.hdcp2.rx_id_list+1,
						HDCP_MAX_AUX_TRANSACTION_SIZE);
		अगर (status == MOD_HDCP_STATUS_SUCCESS) अणु
			bytes_पढ़ो = HDCP_MAX_AUX_TRANSACTION_SIZE;
			device_count = HDCP_2_2_DEV_COUNT_LO(hdcp->auth.msg.hdcp2.rx_id_list[2]) +
					(HDCP_2_2_DEV_COUNT_HI(hdcp->auth.msg.hdcp2.rx_id_list[1]) << 4);
			rx_id_list_size = MIN((21 + 5 * device_count),
					(माप(hdcp->auth.msg.hdcp2.rx_id_list) - 1));
			status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_REPEATER_AUTH_SEND_RECEIVERID_LIST_PART2,
					hdcp->auth.msg.hdcp2.rx_id_list + 1 + bytes_पढ़ो,
					(rx_id_list_size - 1) / HDCP_MAX_AUX_TRANSACTION_SIZE * HDCP_MAX_AUX_TRANSACTION_SIZE);
		पूर्ण
	पूर्ण अन्यथा अणु
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_REPEATER_AUTH_SEND_RECEIVERID_LIST,
				hdcp->auth.msg.hdcp2.rx_id_list,
				hdcp->auth.msg.hdcp2.rx_id_list_size);
	पूर्ण
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_पढ़ो_stream_पढ़ोy(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp)) अणु
		hdcp->auth.msg.hdcp2.repeater_auth_stream_पढ़ोy[0] = HDCP_2_2_REP_STREAM_READY;
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_REPEATER_AUTH_STREAM_READY,
				hdcp->auth.msg.hdcp2.repeater_auth_stream_पढ़ोy+1,
				माप(hdcp->auth.msg.hdcp2.repeater_auth_stream_पढ़ोy)-1);

	पूर्ण अन्यथा अणु
		status = पढ़ो(hdcp, MOD_HDCP_MESSAGE_ID_READ_REPEATER_AUTH_STREAM_READY,
				hdcp->auth.msg.hdcp2.repeater_auth_stream_पढ़ोy,
				माप(hdcp->auth.msg.hdcp2.repeater_auth_stream_पढ़ोy));
	पूर्ण
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_ake_init(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp))
		status = ग_लिखो(hdcp, MOD_HDCP_MESSAGE_ID_WRITE_AKE_INIT,
				hdcp->auth.msg.hdcp2.ake_init+1,
				माप(hdcp->auth.msg.hdcp2.ake_init)-1);
	अन्यथा
		status = ग_लिखो(hdcp, MOD_HDCP_MESSAGE_ID_WRITE_AKE_INIT,
					hdcp->auth.msg.hdcp2.ake_init,
					माप(hdcp->auth.msg.hdcp2.ake_init));
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_no_stored_km(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp))
		status = ग_लिखो(hdcp, MOD_HDCP_MESSAGE_ID_WRITE_AKE_NO_STORED_KM,
				hdcp->auth.msg.hdcp2.ake_no_stored_km+1,
				माप(hdcp->auth.msg.hdcp2.ake_no_stored_km)-1);
	अन्यथा
		status = ग_लिखो(hdcp, MOD_HDCP_MESSAGE_ID_WRITE_AKE_NO_STORED_KM,
			hdcp->auth.msg.hdcp2.ake_no_stored_km,
			माप(hdcp->auth.msg.hdcp2.ake_no_stored_km));
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_stored_km(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp))
		status = ग_लिखो(hdcp, MOD_HDCP_MESSAGE_ID_WRITE_AKE_STORED_KM,
				hdcp->auth.msg.hdcp2.ake_stored_km+1,
				माप(hdcp->auth.msg.hdcp2.ake_stored_km)-1);
	अन्यथा
		status = ग_लिखो(hdcp, MOD_HDCP_MESSAGE_ID_WRITE_AKE_STORED_KM,
				hdcp->auth.msg.hdcp2.ake_stored_km,
				माप(hdcp->auth.msg.hdcp2.ake_stored_km));
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_lc_init(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp))
		status = ग_लिखो(hdcp, MOD_HDCP_MESSAGE_ID_WRITE_LC_INIT,
				hdcp->auth.msg.hdcp2.lc_init+1,
				माप(hdcp->auth.msg.hdcp2.lc_init)-1);
	अन्यथा
		status = ग_लिखो(hdcp, MOD_HDCP_MESSAGE_ID_WRITE_LC_INIT,
				hdcp->auth.msg.hdcp2.lc_init,
				माप(hdcp->auth.msg.hdcp2.lc_init));
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_eks(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp))
		status = ग_लिखो(hdcp,
				MOD_HDCP_MESSAGE_ID_WRITE_SKE_SEND_EKS,
				hdcp->auth.msg.hdcp2.ske_eks+1,
				माप(hdcp->auth.msg.hdcp2.ske_eks)-1);
	अन्यथा
		status = ग_लिखो(hdcp,
			MOD_HDCP_MESSAGE_ID_WRITE_SKE_SEND_EKS,
			hdcp->auth.msg.hdcp2.ske_eks,
			माप(hdcp->auth.msg.hdcp2.ske_eks));
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_repeater_auth_ack(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp))
		status = ग_लिखो(hdcp, MOD_HDCP_MESSAGE_ID_WRITE_REPEATER_AUTH_SEND_ACK,
				hdcp->auth.msg.hdcp2.repeater_auth_ack+1,
				माप(hdcp->auth.msg.hdcp2.repeater_auth_ack)-1);
	अन्यथा
		status = ग_लिखो(hdcp, MOD_HDCP_MESSAGE_ID_WRITE_REPEATER_AUTH_SEND_ACK,
				hdcp->auth.msg.hdcp2.repeater_auth_ack,
				माप(hdcp->auth.msg.hdcp2.repeater_auth_ack));
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_stream_manage(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp))
		status = ग_लिखो(hdcp,
				MOD_HDCP_MESSAGE_ID_WRITE_REPEATER_AUTH_STREAM_MANAGE,
				hdcp->auth.msg.hdcp2.repeater_auth_stream_manage+1,
				hdcp->auth.msg.hdcp2.stream_manage_size-1);
	अन्यथा
		status = ग_लिखो(hdcp,
				MOD_HDCP_MESSAGE_ID_WRITE_REPEATER_AUTH_STREAM_MANAGE,
				hdcp->auth.msg.hdcp2.repeater_auth_stream_manage,
				hdcp->auth.msg.hdcp2.stream_manage_size);
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_ग_लिखो_content_type(काष्ठा mod_hdcp *hdcp)
अणु
	क्रमागत mod_hdcp_status status;

	अगर (is_dp_hdcp(hdcp))
		status = ग_लिखो(hdcp, MOD_HDCP_MESSAGE_ID_WRITE_CONTENT_STREAM_TYPE,
				hdcp->auth.msg.hdcp2.content_stream_type_dp+1,
				माप(hdcp->auth.msg.hdcp2.content_stream_type_dp)-1);
	अन्यथा
		status = MOD_HDCP_STATUS_INVALID_OPERATION;
	वापस status;
पूर्ण

क्रमागत mod_hdcp_status mod_hdcp_clear_cp_irq_status(काष्ठा mod_hdcp *hdcp)
अणु
	uपूर्णांक8_t clear_cp_irq_bit = DP_CP_IRQ;
	uपूर्णांक32_t size = 1;

	अगर (is_dp_hdcp(hdcp)) अणु
		uपूर्णांक32_t cp_irq_addrs = (hdcp->connection.link.dp.rev >= 0x14)
				? DP_DEVICE_SERVICE_IRQ_VECTOR_ESI0:DP_DEVICE_SERVICE_IRQ_VECTOR;
		वापस hdcp->config.ddc.funcs.ग_लिखो_dpcd(hdcp->config.ddc.handle, cp_irq_addrs,
				&clear_cp_irq_bit, size) ? MOD_HDCP_STATUS_SUCCESS : MOD_HDCP_STATUS_DDC_FAILURE;
	पूर्ण

	वापस MOD_HDCP_STATUS_INVALID_OPERATION;
पूर्ण
