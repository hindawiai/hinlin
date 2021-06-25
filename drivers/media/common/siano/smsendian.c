<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/****************************************************************

 Siano Mobile Silicon, Inc.
 MDTV receiver kernel modules.
 Copyright (C) 2006-2009, Uri Shkolnik


 ****************************************************************/

#समावेश <linux/export.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "smsendian.h"
#समावेश "smscoreapi.h"

व्योम smsendian_handle_tx_message(व्योम *buffer)
अणु
#अगर_घोषित __BIG_ENDIAN
	काष्ठा sms_msg_data *msg = (काष्ठा sms_msg_data *)buffer;
	पूर्णांक i;
	पूर्णांक msg_words;

	चयन (msg->x_msg_header.msg_type) अणु
	हाल MSG_SMS_DATA_DOWNLOAD_REQ:
	अणु
		msg->msg_data[0] = le32_to_cpu((__क्रमce __le32)(msg->msg_data[0]));
		अवरोध;
	पूर्ण

	शेष:
		msg_words = (msg->x_msg_header.msg_length -
				माप(काष्ठा sms_msg_hdr))/4;

		क्रम (i = 0; i < msg_words; i++)
			msg->msg_data[i] = le32_to_cpu((__क्रमce __le32)msg->msg_data[i]);

		अवरोध;
	पूर्ण
#पूर्ण_अगर /* __BIG_ENDIAN */
पूर्ण
EXPORT_SYMBOL_GPL(smsendian_handle_tx_message);

व्योम smsendian_handle_rx_message(व्योम *buffer)
अणु
#अगर_घोषित __BIG_ENDIAN
	काष्ठा sms_msg_data *msg = (काष्ठा sms_msg_data *)buffer;
	पूर्णांक i;
	पूर्णांक msg_words;

	चयन (msg->x_msg_header.msg_type) अणु
	हाल MSG_SMS_GET_VERSION_EX_RES:
	अणु
		काष्ठा sms_version_res *ver =
			(काष्ठा sms_version_res *) msg;
		ver->chip_model = le16_to_cpu((__क्रमce __le16)ver->chip_model);
		अवरोध;
	पूर्ण

	हाल MSG_SMS_DVBT_BDA_DATA:
	हाल MSG_SMS_DAB_CHANNEL:
	हाल MSG_SMS_DATA_MSG:
	अणु
		अवरोध;
	पूर्ण

	शेष:
	अणु
		msg_words = (msg->x_msg_header.msg_length -
				माप(काष्ठा sms_msg_hdr))/4;

		क्रम (i = 0; i < msg_words; i++)
			msg->msg_data[i] = le32_to_cpu((__क्रमce __le32)msg->msg_data[i]);

		अवरोध;
	पूर्ण
	पूर्ण
#पूर्ण_अगर /* __BIG_ENDIAN */
पूर्ण
EXPORT_SYMBOL_GPL(smsendian_handle_rx_message);

व्योम smsendian_handle_message_header(व्योम *msg)
अणु
#अगर_घोषित __BIG_ENDIAN
	काष्ठा sms_msg_hdr *phdr = (काष्ठा sms_msg_hdr *)msg;

	phdr->msg_type = le16_to_cpu((__क्रमce __le16)phdr->msg_type);
	phdr->msg_length = le16_to_cpu((__क्रमce __le16)phdr->msg_length);
	phdr->msg_flags = le16_to_cpu((__क्रमce __le16)phdr->msg_flags);
#पूर्ण_अगर /* __BIG_ENDIAN */
पूर्ण
EXPORT_SYMBOL_GPL(smsendian_handle_message_header);
