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

#समावेश <linux/slab.h>

#समावेश "dm_services.h"
#समावेश "dm_helpers.h"
#समावेश "include/hdcp_types.h"
#समावेश "include/i2caux_interface.h"
#समावेश "include/signal_types.h"
#समावेश "core_types.h"
#समावेश "dc_link_ddc.h"
#समावेश "link_hwss.h"

#घोषणा DC_LOGGER \
	link->ctx->logger
#घोषणा HDCP14_KSV_SIZE 5
#घोषणा HDCP14_MAX_KSV_FIFO_SIZE 127*HDCP14_KSV_SIZE

अटल स्थिर bool hdcp_cmd_is_पढ़ो[HDCP_MESSAGE_ID_MAX] = अणु
	[HDCP_MESSAGE_ID_READ_BKSV] = true,
	[HDCP_MESSAGE_ID_READ_RI_R0] = true,
	[HDCP_MESSAGE_ID_READ_PJ] = true,
	[HDCP_MESSAGE_ID_WRITE_AKSV] = false,
	[HDCP_MESSAGE_ID_WRITE_AINFO] = false,
	[HDCP_MESSAGE_ID_WRITE_AN] = false,
	[HDCP_MESSAGE_ID_READ_VH_X] = true,
	[HDCP_MESSAGE_ID_READ_VH_0] = true,
	[HDCP_MESSAGE_ID_READ_VH_1] = true,
	[HDCP_MESSAGE_ID_READ_VH_2] = true,
	[HDCP_MESSAGE_ID_READ_VH_3] = true,
	[HDCP_MESSAGE_ID_READ_VH_4] = true,
	[HDCP_MESSAGE_ID_READ_BCAPS] = true,
	[HDCP_MESSAGE_ID_READ_BSTATUS] = true,
	[HDCP_MESSAGE_ID_READ_KSV_FIFO] = true,
	[HDCP_MESSAGE_ID_READ_BINFO] = true,
	[HDCP_MESSAGE_ID_HDCP2VERSION] = true,
	[HDCP_MESSAGE_ID_RX_CAPS] = true,
	[HDCP_MESSAGE_ID_WRITE_AKE_INIT] = false,
	[HDCP_MESSAGE_ID_READ_AKE_SEND_CERT] = true,
	[HDCP_MESSAGE_ID_WRITE_AKE_NO_STORED_KM] = false,
	[HDCP_MESSAGE_ID_WRITE_AKE_STORED_KM] = false,
	[HDCP_MESSAGE_ID_READ_AKE_SEND_H_PRIME] = true,
	[HDCP_MESSAGE_ID_READ_AKE_SEND_PAIRING_INFO] = true,
	[HDCP_MESSAGE_ID_WRITE_LC_INIT] = false,
	[HDCP_MESSAGE_ID_READ_LC_SEND_L_PRIME] = true,
	[HDCP_MESSAGE_ID_WRITE_SKE_SEND_EKS] = false,
	[HDCP_MESSAGE_ID_READ_REPEATER_AUTH_SEND_RECEIVERID_LIST] = true,
	[HDCP_MESSAGE_ID_WRITE_REPEATER_AUTH_SEND_ACK] = false,
	[HDCP_MESSAGE_ID_WRITE_REPEATER_AUTH_STREAM_MANAGE] = false,
	[HDCP_MESSAGE_ID_READ_REPEATER_AUTH_STREAM_READY] = true,
	[HDCP_MESSAGE_ID_READ_RXSTATUS] = true,
	[HDCP_MESSAGE_ID_WRITE_CONTENT_STREAM_TYPE] = false
पूर्ण;

अटल स्थिर uपूर्णांक8_t hdcp_i2c_offsets[HDCP_MESSAGE_ID_MAX] = अणु
	[HDCP_MESSAGE_ID_READ_BKSV] = 0x0,
	[HDCP_MESSAGE_ID_READ_RI_R0] = 0x8,
	[HDCP_MESSAGE_ID_READ_PJ] = 0xA,
	[HDCP_MESSAGE_ID_WRITE_AKSV] = 0x10,
	[HDCP_MESSAGE_ID_WRITE_AINFO] = 0x15,
	[HDCP_MESSAGE_ID_WRITE_AN] = 0x18,
	[HDCP_MESSAGE_ID_READ_VH_X] = 0x20,
	[HDCP_MESSAGE_ID_READ_VH_0] = 0x20,
	[HDCP_MESSAGE_ID_READ_VH_1] = 0x24,
	[HDCP_MESSAGE_ID_READ_VH_2] = 0x28,
	[HDCP_MESSAGE_ID_READ_VH_3] = 0x2C,
	[HDCP_MESSAGE_ID_READ_VH_4] = 0x30,
	[HDCP_MESSAGE_ID_READ_BCAPS] = 0x40,
	[HDCP_MESSAGE_ID_READ_BSTATUS] = 0x41,
	[HDCP_MESSAGE_ID_READ_KSV_FIFO] = 0x43,
	[HDCP_MESSAGE_ID_READ_BINFO] = 0xFF,
	[HDCP_MESSAGE_ID_HDCP2VERSION] = 0x50,
	[HDCP_MESSAGE_ID_WRITE_AKE_INIT] = 0x60,
	[HDCP_MESSAGE_ID_READ_AKE_SEND_CERT] = 0x80,
	[HDCP_MESSAGE_ID_WRITE_AKE_NO_STORED_KM] = 0x60,
	[HDCP_MESSAGE_ID_WRITE_AKE_STORED_KM] = 0x60,
	[HDCP_MESSAGE_ID_READ_AKE_SEND_H_PRIME] = 0x80,
	[HDCP_MESSAGE_ID_READ_AKE_SEND_PAIRING_INFO] = 0x80,
	[HDCP_MESSAGE_ID_WRITE_LC_INIT] = 0x60,
	[HDCP_MESSAGE_ID_READ_LC_SEND_L_PRIME] = 0x80,
	[HDCP_MESSAGE_ID_WRITE_SKE_SEND_EKS] = 0x60,
	[HDCP_MESSAGE_ID_READ_REPEATER_AUTH_SEND_RECEIVERID_LIST] = 0x80,
	[HDCP_MESSAGE_ID_WRITE_REPEATER_AUTH_SEND_ACK] = 0x60,
	[HDCP_MESSAGE_ID_WRITE_REPEATER_AUTH_STREAM_MANAGE] = 0x60,
	[HDCP_MESSAGE_ID_READ_REPEATER_AUTH_STREAM_READY] = 0x80,
	[HDCP_MESSAGE_ID_READ_RXSTATUS] = 0x70,
	[HDCP_MESSAGE_ID_WRITE_CONTENT_STREAM_TYPE] = 0x0,
पूर्ण;

काष्ठा protection_properties अणु
	bool supported;
	bool (*process_transaction)(
		काष्ठा dc_link *link,
		काष्ठा hdcp_protection_message *message_info);
पूर्ण;

अटल स्थिर काष्ठा protection_properties non_supported_protection = अणु
	.supported = false
पूर्ण;

अटल bool hdmi_14_process_transaction(
	काष्ठा dc_link *link,
	काष्ठा hdcp_protection_message *message_info)
अणु
	uपूर्णांक8_t *buff = शून्य;
	bool result;
	स्थिर uपूर्णांक8_t hdcp_i2c_addr_link_primary = 0x3a; /* 0x74 >> 1*/
	स्थिर uपूर्णांक8_t hdcp_i2c_addr_link_secondary = 0x3b; /* 0x76 >> 1*/
	काष्ठा i2c_command i2c_command;
	uपूर्णांक8_t offset = hdcp_i2c_offsets[message_info->msg_id];
	काष्ठा i2c_payload i2c_payloads[] = अणु
		अणु true, 0, 1, &offset पूर्ण,
		/* actual hdcp payload, will be filled later, zeroed क्रम now*/
		अणु 0 पूर्ण
	पूर्ण;

	चयन (message_info->link) अणु
	हाल HDCP_LINK_SECONDARY:
		i2c_payloads[0].address = hdcp_i2c_addr_link_secondary;
		i2c_payloads[1].address = hdcp_i2c_addr_link_secondary;
		अवरोध;
	हाल HDCP_LINK_PRIMARY:
	शेष:
		i2c_payloads[0].address = hdcp_i2c_addr_link_primary;
		i2c_payloads[1].address = hdcp_i2c_addr_link_primary;
		अवरोध;
	पूर्ण

	अगर (hdcp_cmd_is_पढ़ो[message_info->msg_id]) अणु
		i2c_payloads[1].ग_लिखो = false;
		i2c_command.number_of_payloads = ARRAY_SIZE(i2c_payloads);
		i2c_payloads[1].length = message_info->length;
		i2c_payloads[1].data = message_info->data;
	पूर्ण अन्यथा अणु
		i2c_command.number_of_payloads = 1;
		buff = kzalloc(message_info->length + 1, GFP_KERNEL);

		अगर (!buff)
			वापस false;

		buff[0] = offset;
		स_हटाओ(&buff[1], message_info->data, message_info->length);
		i2c_payloads[0].length = message_info->length + 1;
		i2c_payloads[0].data = buff;
	पूर्ण

	i2c_command.payloads = i2c_payloads;
	i2c_command.engine = I2C_COMMAND_ENGINE_HW;//only HW
	i2c_command.speed = link->ddc->ctx->dc->caps.i2c_speed_in_khz;

	result = dm_helpers_submit_i2c(
			link->ctx,
			link,
			&i2c_command);
	kमुक्त(buff);

	वापस result;
पूर्ण

अटल स्थिर काष्ठा protection_properties hdmi_14_protection = अणु
	.supported = true,
	.process_transaction = hdmi_14_process_transaction
पूर्ण;

अटल स्थिर uपूर्णांक32_t hdcp_dpcd_addrs[HDCP_MESSAGE_ID_MAX] = अणु
	[HDCP_MESSAGE_ID_READ_BKSV] = 0x68000,
	[HDCP_MESSAGE_ID_READ_RI_R0] = 0x68005,
	[HDCP_MESSAGE_ID_READ_PJ] = 0xFFFFFFFF,
	[HDCP_MESSAGE_ID_WRITE_AKSV] = 0x68007,
	[HDCP_MESSAGE_ID_WRITE_AINFO] = 0x6803B,
	[HDCP_MESSAGE_ID_WRITE_AN] = 0x6800c,
	[HDCP_MESSAGE_ID_READ_VH_X] = 0x68014,
	[HDCP_MESSAGE_ID_READ_VH_0] = 0x68014,
	[HDCP_MESSAGE_ID_READ_VH_1] = 0x68018,
	[HDCP_MESSAGE_ID_READ_VH_2] = 0x6801c,
	[HDCP_MESSAGE_ID_READ_VH_3] = 0x68020,
	[HDCP_MESSAGE_ID_READ_VH_4] = 0x68024,
	[HDCP_MESSAGE_ID_READ_BCAPS] = 0x68028,
	[HDCP_MESSAGE_ID_READ_BSTATUS] = 0x68029,
	[HDCP_MESSAGE_ID_READ_KSV_FIFO] = 0x6802c,
	[HDCP_MESSAGE_ID_READ_BINFO] = 0x6802a,
	[HDCP_MESSAGE_ID_RX_CAPS] = 0x6921d,
	[HDCP_MESSAGE_ID_WRITE_AKE_INIT] = 0x69000,
	[HDCP_MESSAGE_ID_READ_AKE_SEND_CERT] = 0x6900b,
	[HDCP_MESSAGE_ID_WRITE_AKE_NO_STORED_KM] = 0x69220,
	[HDCP_MESSAGE_ID_WRITE_AKE_STORED_KM] = 0x692a0,
	[HDCP_MESSAGE_ID_READ_AKE_SEND_H_PRIME] = 0x692c0,
	[HDCP_MESSAGE_ID_READ_AKE_SEND_PAIRING_INFO] = 0x692e0,
	[HDCP_MESSAGE_ID_WRITE_LC_INIT] = 0x692f0,
	[HDCP_MESSAGE_ID_READ_LC_SEND_L_PRIME] = 0x692f8,
	[HDCP_MESSAGE_ID_WRITE_SKE_SEND_EKS] = 0x69318,
	[HDCP_MESSAGE_ID_READ_REPEATER_AUTH_SEND_RECEIVERID_LIST] = 0x69330,
	[HDCP_MESSAGE_ID_WRITE_REPEATER_AUTH_SEND_ACK] = 0x693e0,
	[HDCP_MESSAGE_ID_WRITE_REPEATER_AUTH_STREAM_MANAGE] = 0x693f0,
	[HDCP_MESSAGE_ID_READ_REPEATER_AUTH_STREAM_READY] = 0x69473,
	[HDCP_MESSAGE_ID_READ_RXSTATUS] = 0x69493,
	[HDCP_MESSAGE_ID_WRITE_CONTENT_STREAM_TYPE] = 0x69494
पूर्ण;

अटल bool dpcd_access_helper(
	काष्ठा dc_link *link,
	uपूर्णांक32_t length,
	uपूर्णांक8_t *data,
	uपूर्णांक32_t dpcd_addr,
	bool is_पढ़ो)
अणु
	क्रमागत dc_status status;
	uपूर्णांक32_t cur_length = 0;
	uपूर्णांक32_t offset = 0;
	uपूर्णांक32_t ksv_पढ़ो_size = 0x6803b - 0x6802c;

	/* Read KSV, need repeatedly handle */
	अगर (dpcd_addr == 0x6802c) अणु
		अगर (length % HDCP14_KSV_SIZE) अणु
			DC_LOG_ERROR("%s: KsvFifo Size(%d) is not a multiple of HDCP14_KSV_SIZE(%d)\n",
				__func__,
				length,
				HDCP14_KSV_SIZE);
		पूर्ण
		अगर (length > HDCP14_MAX_KSV_FIFO_SIZE) अणु
			DC_LOG_ERROR("%s: KsvFifo Size(%d) is greater than HDCP14_MAX_KSV_FIFO_SIZE(%d)\n",
				__func__,
				length,
				HDCP14_MAX_KSV_FIFO_SIZE);
		पूर्ण

		DC_LOG_ERROR("%s: Reading %d Ksv(s) from KsvFifo\n",
			__func__,
			length / HDCP14_KSV_SIZE);

		जबतक (length > 0) अणु
			अगर (length > ksv_पढ़ो_size) अणु
				status = core_link_पढ़ो_dpcd(
					link,
					dpcd_addr + offset,
					data + offset,
					ksv_पढ़ो_size);

				data += ksv_पढ़ो_size;
				length -= ksv_पढ़ो_size;
			पूर्ण अन्यथा अणु
				status = core_link_पढ़ो_dpcd(
					link,
					dpcd_addr + offset,
					data + offset,
					length);

				data += length;
				length = 0;
			पूर्ण

			अगर (status != DC_OK)
				वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (length > 0) अणु
			अगर (length > DEFAULT_AUX_MAX_DATA_SIZE)
				cur_length = DEFAULT_AUX_MAX_DATA_SIZE;
			अन्यथा
				cur_length = length;

			अगर (is_पढ़ो) अणु
				status = core_link_पढ़ो_dpcd(
					link,
					dpcd_addr + offset,
					data + offset,
					cur_length);
			पूर्ण अन्यथा अणु
				status = core_link_ग_लिखो_dpcd(
					link,
					dpcd_addr + offset,
					data + offset,
					cur_length);
			पूर्ण

			अगर (status != DC_OK)
				वापस false;

			length -= cur_length;
			offset += cur_length;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल bool dp_11_process_transaction(
	काष्ठा dc_link *link,
	काष्ठा hdcp_protection_message *message_info)
अणु
	वापस dpcd_access_helper(
		link,
		message_info->length,
		message_info->data,
		hdcp_dpcd_addrs[message_info->msg_id],
		hdcp_cmd_is_पढ़ो[message_info->msg_id]);
पूर्ण

अटल स्थिर काष्ठा protection_properties dp_11_protection = अणु
	.supported = true,
	.process_transaction = dp_11_process_transaction
पूर्ण;

अटल स्थिर काष्ठा protection_properties *get_protection_properties_by_संकेत(
	काष्ठा dc_link *link,
	क्रमागत संकेत_type st,
	क्रमागत hdcp_version version)
अणु
	चयन (version) अणु
	हाल HDCP_VERSION_14:
		चयन (st) अणु
		हाल SIGNAL_TYPE_DVI_SINGLE_LINK:
		हाल SIGNAL_TYPE_DVI_DUAL_LINK:
		हाल SIGNAL_TYPE_HDMI_TYPE_A:
			वापस &hdmi_14_protection;
		हाल SIGNAL_TYPE_DISPLAY_PORT:
			अगर (link &&
				(link->dpcd_caps.करोngle_type == DISPLAY_DONGLE_DP_VGA_CONVERTER ||
				link->dpcd_caps.करोngle_caps.करोngle_type == DISPLAY_DONGLE_DP_VGA_CONVERTER)) अणु
				वापस &non_supported_protection;
			पूर्ण
			वापस &dp_11_protection;
		हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
		हाल SIGNAL_TYPE_EDP:
			वापस &dp_11_protection;
		शेष:
			वापस &non_supported_protection;
		पूर्ण
		अवरोध;
	हाल HDCP_VERSION_22:
		चयन (st) अणु
		हाल SIGNAL_TYPE_DVI_SINGLE_LINK:
		हाल SIGNAL_TYPE_DVI_DUAL_LINK:
		हाल SIGNAL_TYPE_HDMI_TYPE_A:
			वापस &hdmi_14_protection; //toकरो version2.2
		हाल SIGNAL_TYPE_DISPLAY_PORT:
		हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
		हाल SIGNAL_TYPE_EDP:
			वापस &dp_11_protection;  //toकरो version2.2
		शेष:
			वापस &non_supported_protection;
		पूर्ण
		अवरोध;
	शेष:
		वापस &non_supported_protection;
	पूर्ण
पूर्ण

क्रमागत hdcp_message_status dc_process_hdcp_msg(
	क्रमागत संकेत_type संकेत,
	काष्ठा dc_link *link,
	काष्ठा hdcp_protection_message *message_info)
अणु
	क्रमागत hdcp_message_status status = HDCP_MESSAGE_FAILURE;
	uपूर्णांक32_t i = 0;

	स्थिर काष्ठा protection_properties *protection_props;

	अगर (!message_info)
		वापस HDCP_MESSAGE_UNSUPPORTED;

	अगर (message_info->msg_id < HDCP_MESSAGE_ID_READ_BKSV ||
		message_info->msg_id >= HDCP_MESSAGE_ID_MAX)
		वापस HDCP_MESSAGE_UNSUPPORTED;

	protection_props =
		get_protection_properties_by_संकेत(
			link,
			संकेत,
			message_info->version);

	अगर (!protection_props->supported)
		वापस HDCP_MESSAGE_UNSUPPORTED;

	अगर (protection_props->process_transaction(
		link,
		message_info)) अणु
		status = HDCP_MESSAGE_SUCCESS;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < message_info->max_retries; i++) अणु
			अगर (protection_props->process_transaction(
						link,
						message_info)) अणु
				status = HDCP_MESSAGE_SUCCESS;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

