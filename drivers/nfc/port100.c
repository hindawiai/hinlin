<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sony NFC Port-100 Series driver
 * Copyright (c) 2013, Intel Corporation.
 *
 * Partly based/Inspired by Stephen Tiedemann's nfcpy
 */

#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <net/nfc/digital.h>

#घोषणा VERSION "0.1"

#घोषणा SONY_VENDOR_ID		0x054c
#घोषणा RCS380S_PRODUCT_ID	0x06c1
#घोषणा RCS380P_PRODUCT_ID	0x06c3

#घोषणा PORT100_PROTOCOLS (NFC_PROTO_JEWEL_MASK    | \
			   NFC_PROTO_MIFARE_MASK   | \
			   NFC_PROTO_FELICA_MASK   | \
			   NFC_PROTO_NFC_DEP_MASK  | \
			   NFC_PROTO_ISO14443_MASK | \
			   NFC_PROTO_ISO14443_B_MASK)

#घोषणा PORT100_CAPABILITIES (NFC_DIGITAL_DRV_CAPS_IN_CRC | \
			      NFC_DIGITAL_DRV_CAPS_TG_CRC)

/* Standard port100 frame definitions */
#घोषणा PORT100_FRAME_HEADER_LEN (माप(काष्ठा port100_frame) \
				  + 2) /* data[0] CC, data[1] SCC */
#घोषणा PORT100_FRAME_TAIL_LEN 2 /* data[len] DCS, data[len + 1] postamble*/

#घोषणा PORT100_COMM_RF_HEAD_MAX_LEN (माप(काष्ठा port100_tg_comm_rf_cmd))

/*
 * Max extended frame payload len, excluding CC and SCC
 * which are alपढ़ोy in PORT100_FRAME_HEADER_LEN.
 */
#घोषणा PORT100_FRAME_MAX_PAYLOAD_LEN 1001

#घोषणा PORT100_FRAME_ACK_SIZE 6 /* Preamble (1), SoPC (2), ACK Code (2),
				    Postamble (1) */
अटल u8 ack_frame[PORT100_FRAME_ACK_SIZE] = अणु
	0x00, 0x00, 0xff, 0x00, 0xff, 0x00
पूर्ण;

#घोषणा PORT100_FRAME_CHECKSUM(f) (f->data[le16_to_cpu(f->datalen)])
#घोषणा PORT100_FRAME_POSTAMBLE(f) (f->data[le16_to_cpu(f->datalen) + 1])

/* start of frame */
#घोषणा PORT100_FRAME_SOF	0x00FF
#घोषणा PORT100_FRAME_EXT	0xFFFF
#घोषणा PORT100_FRAME_ACK	0x00FF

/* Port-100 command: in or out */
#घोषणा PORT100_FRAME_सूचीECTION(f) (f->data[0]) /* CC */
#घोषणा PORT100_FRAME_सूची_OUT 0xD6
#घोषणा PORT100_FRAME_सूची_IN  0xD7

/* Port-100 sub-command */
#घोषणा PORT100_FRAME_CMD(f) (f->data[1]) /* SCC */

#घोषणा PORT100_CMD_GET_FIRMWARE_VERSION 0x20
#घोषणा PORT100_CMD_GET_COMMAND_TYPE     0x28
#घोषणा PORT100_CMD_SET_COMMAND_TYPE     0x2A

#घोषणा PORT100_CMD_IN_SET_RF       0x00
#घोषणा PORT100_CMD_IN_SET_PROTOCOL 0x02
#घोषणा PORT100_CMD_IN_COMM_RF      0x04

#घोषणा PORT100_CMD_TG_SET_RF       0x40
#घोषणा PORT100_CMD_TG_SET_PROTOCOL 0x42
#घोषणा PORT100_CMD_TG_SET_RF_OFF   0x46
#घोषणा PORT100_CMD_TG_COMM_RF      0x48

#घोषणा PORT100_CMD_SWITCH_RF       0x06

#घोषणा PORT100_CMD_RESPONSE(cmd) (cmd + 1)

#घोषणा PORT100_CMD_TYPE_IS_SUPPORTED(mask, cmd_type) \
	((mask) & (0x01 << (cmd_type)))
#घोषणा PORT100_CMD_TYPE_0	0
#घोषणा PORT100_CMD_TYPE_1	1

#घोषणा PORT100_CMD_STATUS_OK      0x00
#घोषणा PORT100_CMD_STATUS_TIMEOUT 0x80

#घोषणा PORT100_MDAA_TGT_HAS_BEEN_ACTIVATED_MASK 0x01
#घोषणा PORT100_MDAA_TGT_WAS_ACTIVATED_MASK      0x02

काष्ठा port100;

प्रकार व्योम (*port100_send_async_complete_t)(काष्ठा port100 *dev, व्योम *arg,
					      काष्ठा sk_buff *resp);

/**
 * Setting sets काष्ठाure क्रम in_set_rf command
 *
 * @in_*_set_number: Represent the entry indexes in the port-100 RF Base Table.
 *              This table contains multiple RF setting sets required क्रम RF
 *              communication.
 *
 * @in_*_comm_type: Theses fields set the communication type to be used.
 */
काष्ठा port100_in_rf_setting अणु
	u8 in_send_set_number;
	u8 in_send_comm_type;
	u8 in_recv_set_number;
	u8 in_recv_comm_type;
पूर्ण __packed;

#घोषणा PORT100_COMM_TYPE_IN_212F 0x01
#घोषणा PORT100_COMM_TYPE_IN_424F 0x02
#घोषणा PORT100_COMM_TYPE_IN_106A 0x03
#घोषणा PORT100_COMM_TYPE_IN_106B 0x07

अटल स्थिर काष्ठा port100_in_rf_setting in_rf_settings[] = अणु
	[NFC_DIGITAL_RF_TECH_212F] = अणु
		.in_send_set_number = 1,
		.in_send_comm_type  = PORT100_COMM_TYPE_IN_212F,
		.in_recv_set_number = 15,
		.in_recv_comm_type  = PORT100_COMM_TYPE_IN_212F,
	पूर्ण,
	[NFC_DIGITAL_RF_TECH_424F] = अणु
		.in_send_set_number = 1,
		.in_send_comm_type  = PORT100_COMM_TYPE_IN_424F,
		.in_recv_set_number = 15,
		.in_recv_comm_type  = PORT100_COMM_TYPE_IN_424F,
	पूर्ण,
	[NFC_DIGITAL_RF_TECH_106A] = अणु
		.in_send_set_number = 2,
		.in_send_comm_type  = PORT100_COMM_TYPE_IN_106A,
		.in_recv_set_number = 15,
		.in_recv_comm_type  = PORT100_COMM_TYPE_IN_106A,
	पूर्ण,
	[NFC_DIGITAL_RF_TECH_106B] = अणु
		.in_send_set_number = 3,
		.in_send_comm_type  = PORT100_COMM_TYPE_IN_106B,
		.in_recv_set_number = 15,
		.in_recv_comm_type  = PORT100_COMM_TYPE_IN_106B,
	पूर्ण,
	/* Ensures the array has NFC_DIGITAL_RF_TECH_LAST elements */
	[NFC_DIGITAL_RF_TECH_LAST] = अणु 0 पूर्ण,
पूर्ण;

/**
 * Setting sets काष्ठाure क्रम tg_set_rf command
 *
 * @tg_set_number: Represents the entry index in the port-100 RF Base Table.
 *                 This table contains multiple RF setting sets required क्रम RF
 *                 communication. this field is used क्रम both send and receive
 *                 settings.
 *
 * @tg_comm_type: Sets the communication type to be used to send and receive
 *                data.
 */
काष्ठा port100_tg_rf_setting अणु
	u8 tg_set_number;
	u8 tg_comm_type;
पूर्ण __packed;

#घोषणा PORT100_COMM_TYPE_TG_106A 0x0B
#घोषणा PORT100_COMM_TYPE_TG_212F 0x0C
#घोषणा PORT100_COMM_TYPE_TG_424F 0x0D

अटल स्थिर काष्ठा port100_tg_rf_setting tg_rf_settings[] = अणु
	[NFC_DIGITAL_RF_TECH_106A] = अणु
		.tg_set_number = 8,
		.tg_comm_type = PORT100_COMM_TYPE_TG_106A,
	पूर्ण,
	[NFC_DIGITAL_RF_TECH_212F] = अणु
		.tg_set_number = 8,
		.tg_comm_type = PORT100_COMM_TYPE_TG_212F,
	पूर्ण,
	[NFC_DIGITAL_RF_TECH_424F] = अणु
		.tg_set_number = 8,
		.tg_comm_type = PORT100_COMM_TYPE_TG_424F,
	पूर्ण,
	/* Ensures the array has NFC_DIGITAL_RF_TECH_LAST elements */
	[NFC_DIGITAL_RF_TECH_LAST] = अणु 0 पूर्ण,

पूर्ण;

#घोषणा PORT100_IN_PROT_INITIAL_GUARD_TIME      0x00
#घोषणा PORT100_IN_PROT_ADD_CRC                 0x01
#घोषणा PORT100_IN_PROT_CHECK_CRC               0x02
#घोषणा PORT100_IN_PROT_MULTI_CARD              0x03
#घोषणा PORT100_IN_PROT_ADD_PARITY              0x04
#घोषणा PORT100_IN_PROT_CHECK_PARITY            0x05
#घोषणा PORT100_IN_PROT_BITWISE_AC_RECV_MODE    0x06
#घोषणा PORT100_IN_PROT_VALID_BIT_NUMBER        0x07
#घोषणा PORT100_IN_PROT_CRYPTO1                 0x08
#घोषणा PORT100_IN_PROT_ADD_SOF                 0x09
#घोषणा PORT100_IN_PROT_CHECK_SOF               0x0A
#घोषणा PORT100_IN_PROT_ADD_खातापूर्ण                 0x0B
#घोषणा PORT100_IN_PROT_CHECK_खातापूर्ण               0x0C
#घोषणा PORT100_IN_PROT_DEAF_TIME               0x0E
#घोषणा PORT100_IN_PROT_CRM                     0x0F
#घोषणा PORT100_IN_PROT_CRM_MIN_LEN             0x10
#घोषणा PORT100_IN_PROT_T1_TAG_FRAME            0x11
#घोषणा PORT100_IN_PROT_RFCA                    0x12
#घोषणा PORT100_IN_PROT_GUARD_TIME_AT_INITIATOR 0x13
#घोषणा PORT100_IN_PROT_END                     0x14

#घोषणा PORT100_IN_MAX_NUM_PROTOCOLS            19

#घोषणा PORT100_TG_PROT_TU           0x00
#घोषणा PORT100_TG_PROT_RF_OFF       0x01
#घोषणा PORT100_TG_PROT_CRM          0x02
#घोषणा PORT100_TG_PROT_END          0x03

#घोषणा PORT100_TG_MAX_NUM_PROTOCOLS 3

काष्ठा port100_protocol अणु
	u8 number;
	u8 value;
पूर्ण __packed;

अटल काष्ठा port100_protocol
in_protocols[][PORT100_IN_MAX_NUM_PROTOCOLS + 1] = अणु
	[NFC_DIGITAL_FRAMING_NFCA_SHORT] = अणु
		अणु PORT100_IN_PROT_INITIAL_GUARD_TIME,      6 पूर्ण,
		अणु PORT100_IN_PROT_ADD_CRC,                 0 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_CRC,               0 पूर्ण,
		अणु PORT100_IN_PROT_MULTI_CARD,              0 पूर्ण,
		अणु PORT100_IN_PROT_ADD_PARITY,              0 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_PARITY,            1 पूर्ण,
		अणु PORT100_IN_PROT_BITWISE_AC_RECV_MODE,    0 पूर्ण,
		अणु PORT100_IN_PROT_VALID_BIT_NUMBER,        7 पूर्ण,
		अणु PORT100_IN_PROT_CRYPTO1,                 0 पूर्ण,
		अणु PORT100_IN_PROT_ADD_SOF,                 0 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_SOF,               0 पूर्ण,
		अणु PORT100_IN_PROT_ADD_खातापूर्ण,                 0 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_खातापूर्ण,               0 पूर्ण,
		अणु PORT100_IN_PROT_DEAF_TIME,               4 पूर्ण,
		अणु PORT100_IN_PROT_CRM,                     0 पूर्ण,
		अणु PORT100_IN_PROT_CRM_MIN_LEN,             0 पूर्ण,
		अणु PORT100_IN_PROT_T1_TAG_FRAME,            0 पूर्ण,
		अणु PORT100_IN_PROT_RFCA,                    0 पूर्ण,
		अणु PORT100_IN_PROT_GUARD_TIME_AT_INITIATOR, 6 पूर्ण,
		अणु PORT100_IN_PROT_END,                     0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCA_STANDARD] = अणु
		अणु PORT100_IN_PROT_INITIAL_GUARD_TIME,      6 पूर्ण,
		अणु PORT100_IN_PROT_ADD_CRC,                 0 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_CRC,               0 पूर्ण,
		अणु PORT100_IN_PROT_MULTI_CARD,              0 पूर्ण,
		अणु PORT100_IN_PROT_ADD_PARITY,              1 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_PARITY,            1 पूर्ण,
		अणु PORT100_IN_PROT_BITWISE_AC_RECV_MODE,    0 पूर्ण,
		अणु PORT100_IN_PROT_VALID_BIT_NUMBER,        8 पूर्ण,
		अणु PORT100_IN_PROT_CRYPTO1,                 0 पूर्ण,
		अणु PORT100_IN_PROT_ADD_SOF,                 0 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_SOF,               0 पूर्ण,
		अणु PORT100_IN_PROT_ADD_खातापूर्ण,                 0 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_खातापूर्ण,               0 पूर्ण,
		अणु PORT100_IN_PROT_DEAF_TIME,               4 पूर्ण,
		अणु PORT100_IN_PROT_CRM,                     0 पूर्ण,
		अणु PORT100_IN_PROT_CRM_MIN_LEN,             0 पूर्ण,
		अणु PORT100_IN_PROT_T1_TAG_FRAME,            0 पूर्ण,
		अणु PORT100_IN_PROT_RFCA,                    0 पूर्ण,
		अणु PORT100_IN_PROT_GUARD_TIME_AT_INITIATOR, 6 पूर्ण,
		अणु PORT100_IN_PROT_END,                     0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A] = अणु
		अणु PORT100_IN_PROT_INITIAL_GUARD_TIME,      6 पूर्ण,
		अणु PORT100_IN_PROT_ADD_CRC,                 1 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_CRC,               1 पूर्ण,
		अणु PORT100_IN_PROT_MULTI_CARD,              0 पूर्ण,
		अणु PORT100_IN_PROT_ADD_PARITY,              1 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_PARITY,            1 पूर्ण,
		अणु PORT100_IN_PROT_BITWISE_AC_RECV_MODE,    0 पूर्ण,
		अणु PORT100_IN_PROT_VALID_BIT_NUMBER,        8 पूर्ण,
		अणु PORT100_IN_PROT_CRYPTO1,                 0 पूर्ण,
		अणु PORT100_IN_PROT_ADD_SOF,                 0 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_SOF,               0 पूर्ण,
		अणु PORT100_IN_PROT_ADD_खातापूर्ण,                 0 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_खातापूर्ण,               0 पूर्ण,
		अणु PORT100_IN_PROT_DEAF_TIME,               4 पूर्ण,
		अणु PORT100_IN_PROT_CRM,                     0 पूर्ण,
		अणु PORT100_IN_PROT_CRM_MIN_LEN,             0 पूर्ण,
		अणु PORT100_IN_PROT_T1_TAG_FRAME,            0 पूर्ण,
		अणु PORT100_IN_PROT_RFCA,                    0 पूर्ण,
		अणु PORT100_IN_PROT_GUARD_TIME_AT_INITIATOR, 6 पूर्ण,
		अणु PORT100_IN_PROT_END,                     0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCA_T1T] = अणु
		/* nfc_digital_framing_nfca_लघु */
		अणु PORT100_IN_PROT_ADD_CRC,          2 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_CRC,        2 पूर्ण,
		अणु PORT100_IN_PROT_VALID_BIT_NUMBER, 8 पूर्ण,
		अणु PORT100_IN_PROT_T1_TAG_FRAME,     2 पूर्ण,
		अणु PORT100_IN_PROT_END,              0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCA_T2T] = अणु
		/* nfc_digital_framing_nfca_standard */
		अणु PORT100_IN_PROT_ADD_CRC,   1 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_CRC, 0 पूर्ण,
		अणु PORT100_IN_PROT_END,       0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCA_T4T] = अणु
		/* nfc_digital_framing_nfca_standard_with_crc_a */
		अणु PORT100_IN_PROT_END,       0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCA_NFC_DEP] = अणु
		/* nfc_digital_framing_nfca_standard */
		अणु PORT100_IN_PROT_END, 0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCF] = अणु
		अणु PORT100_IN_PROT_INITIAL_GUARD_TIME,     18 पूर्ण,
		अणु PORT100_IN_PROT_ADD_CRC,                 1 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_CRC,               1 पूर्ण,
		अणु PORT100_IN_PROT_MULTI_CARD,              0 पूर्ण,
		अणु PORT100_IN_PROT_ADD_PARITY,              0 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_PARITY,            0 पूर्ण,
		अणु PORT100_IN_PROT_BITWISE_AC_RECV_MODE,    0 पूर्ण,
		अणु PORT100_IN_PROT_VALID_BIT_NUMBER,        8 पूर्ण,
		अणु PORT100_IN_PROT_CRYPTO1,                 0 पूर्ण,
		अणु PORT100_IN_PROT_ADD_SOF,                 0 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_SOF,               0 पूर्ण,
		अणु PORT100_IN_PROT_ADD_खातापूर्ण,                 0 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_खातापूर्ण,               0 पूर्ण,
		अणु PORT100_IN_PROT_DEAF_TIME,               4 पूर्ण,
		अणु PORT100_IN_PROT_CRM,                     0 पूर्ण,
		अणु PORT100_IN_PROT_CRM_MIN_LEN,             0 पूर्ण,
		अणु PORT100_IN_PROT_T1_TAG_FRAME,            0 पूर्ण,
		अणु PORT100_IN_PROT_RFCA,                    0 पूर्ण,
		अणु PORT100_IN_PROT_GUARD_TIME_AT_INITIATOR, 6 पूर्ण,
		अणु PORT100_IN_PROT_END,                     0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCF_T3T] = अणु
		/* nfc_digital_framing_nfcf */
		अणु PORT100_IN_PROT_END, 0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCF_NFC_DEP] = अणु
		/* nfc_digital_framing_nfcf */
		अणु PORT100_IN_PROT_INITIAL_GUARD_TIME,     18 पूर्ण,
		अणु PORT100_IN_PROT_ADD_CRC,                 1 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_CRC,               1 पूर्ण,
		अणु PORT100_IN_PROT_MULTI_CARD,              0 पूर्ण,
		अणु PORT100_IN_PROT_ADD_PARITY,              0 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_PARITY,            0 पूर्ण,
		अणु PORT100_IN_PROT_BITWISE_AC_RECV_MODE,    0 पूर्ण,
		अणु PORT100_IN_PROT_VALID_BIT_NUMBER,        8 पूर्ण,
		अणु PORT100_IN_PROT_CRYPTO1,                 0 पूर्ण,
		अणु PORT100_IN_PROT_ADD_SOF,                 0 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_SOF,               0 पूर्ण,
		अणु PORT100_IN_PROT_ADD_खातापूर्ण,                 0 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_खातापूर्ण,               0 पूर्ण,
		अणु PORT100_IN_PROT_DEAF_TIME,               4 पूर्ण,
		अणु PORT100_IN_PROT_CRM,                     0 पूर्ण,
		अणु PORT100_IN_PROT_CRM_MIN_LEN,             0 पूर्ण,
		अणु PORT100_IN_PROT_T1_TAG_FRAME,            0 पूर्ण,
		अणु PORT100_IN_PROT_RFCA,                    0 पूर्ण,
		अणु PORT100_IN_PROT_GUARD_TIME_AT_INITIATOR, 6 पूर्ण,
		अणु PORT100_IN_PROT_END,                     0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFC_DEP_ACTIVATED] = अणु
		अणु PORT100_IN_PROT_END, 0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCB] = अणु
		अणु PORT100_IN_PROT_INITIAL_GUARD_TIME,     20 पूर्ण,
		अणु PORT100_IN_PROT_ADD_CRC,                 1 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_CRC,               1 पूर्ण,
		अणु PORT100_IN_PROT_MULTI_CARD,              0 पूर्ण,
		अणु PORT100_IN_PROT_ADD_PARITY,              0 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_PARITY,            0 पूर्ण,
		अणु PORT100_IN_PROT_BITWISE_AC_RECV_MODE,    0 पूर्ण,
		अणु PORT100_IN_PROT_VALID_BIT_NUMBER,        8 पूर्ण,
		अणु PORT100_IN_PROT_CRYPTO1,                 0 पूर्ण,
		अणु PORT100_IN_PROT_ADD_SOF,                 1 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_SOF,               1 पूर्ण,
		अणु PORT100_IN_PROT_ADD_खातापूर्ण,                 1 पूर्ण,
		अणु PORT100_IN_PROT_CHECK_खातापूर्ण,               1 पूर्ण,
		अणु PORT100_IN_PROT_DEAF_TIME,               4 पूर्ण,
		अणु PORT100_IN_PROT_CRM,                     0 पूर्ण,
		अणु PORT100_IN_PROT_CRM_MIN_LEN,             0 पूर्ण,
		अणु PORT100_IN_PROT_T1_TAG_FRAME,            0 पूर्ण,
		अणु PORT100_IN_PROT_RFCA,                    0 पूर्ण,
		अणु PORT100_IN_PROT_GUARD_TIME_AT_INITIATOR, 6 पूर्ण,
		अणु PORT100_IN_PROT_END,                     0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCB_T4T] = अणु
		/* nfc_digital_framing_nfcb */
		अणु PORT100_IN_PROT_END,                     0 पूर्ण,
	पूर्ण,
	/* Ensures the array has NFC_DIGITAL_FRAMING_LAST elements */
	[NFC_DIGITAL_FRAMING_LAST] = अणु
		अणु PORT100_IN_PROT_END, 0 पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा port100_protocol
tg_protocols[][PORT100_TG_MAX_NUM_PROTOCOLS + 1] = अणु
	[NFC_DIGITAL_FRAMING_NFCA_SHORT] = अणु
		अणु PORT100_TG_PROT_END, 0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCA_STANDARD] = अणु
		अणु PORT100_TG_PROT_END, 0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A] = अणु
		अणु PORT100_TG_PROT_END, 0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCA_T1T] = अणु
		अणु PORT100_TG_PROT_END, 0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCA_T2T] = अणु
		अणु PORT100_TG_PROT_END, 0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCA_NFC_DEP] = अणु
		अणु PORT100_TG_PROT_TU,     1 पूर्ण,
		अणु PORT100_TG_PROT_RF_OFF, 0 पूर्ण,
		अणु PORT100_TG_PROT_CRM,    7 पूर्ण,
		अणु PORT100_TG_PROT_END,    0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCF] = अणु
		अणु PORT100_TG_PROT_END, 0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCF_T3T] = अणु
		अणु PORT100_TG_PROT_END, 0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFCF_NFC_DEP] = अणु
		अणु PORT100_TG_PROT_TU,     1 पूर्ण,
		अणु PORT100_TG_PROT_RF_OFF, 0 पूर्ण,
		अणु PORT100_TG_PROT_CRM,    7 पूर्ण,
		अणु PORT100_TG_PROT_END,    0 पूर्ण,
	पूर्ण,
	[NFC_DIGITAL_FRAMING_NFC_DEP_ACTIVATED] = अणु
		अणु PORT100_TG_PROT_RF_OFF, 1 पूर्ण,
		अणु PORT100_TG_PROT_END,    0 पूर्ण,
	पूर्ण,
	/* Ensures the array has NFC_DIGITAL_FRAMING_LAST elements */
	[NFC_DIGITAL_FRAMING_LAST] = अणु
		अणु PORT100_TG_PROT_END,    0 पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा port100 अणु
	काष्ठा nfc_digital_dev *nfc_digital_dev;

	पूर्णांक skb_headroom;
	पूर्णांक skb_tailroom;

	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;

	काष्ठा urb *out_urb;
	काष्ठा urb *in_urb;

	/* This mutex protects the out_urb and aव्योमs to submit a new command
	 * through port100_send_frame_async() जबतक the previous one is being
	 * canceled through port100_पात_cmd().
	 */
	काष्ठा mutex out_urb_lock;

	काष्ठा work_काष्ठा cmd_complete_work;

	u8 cmd_type;

	/* The digital stack serializes commands to be sent. There is no need
	 * क्रम any queuing/locking mechanism at driver level.
	 */
	काष्ठा port100_cmd *cmd;

	bool cmd_cancel;
	काष्ठा completion cmd_cancel_करोne;
पूर्ण;

काष्ठा port100_cmd अणु
	u8 code;
	पूर्णांक status;
	काष्ठा sk_buff *req;
	काष्ठा sk_buff *resp;
	पूर्णांक resp_len;
	port100_send_async_complete_t  complete_cb;
	व्योम *complete_cb_context;
पूर्ण;

काष्ठा port100_frame अणु
	u8 preamble;
	__be16 start_frame;
	__be16 extended_frame;
	__le16 datalen;
	u8 datalen_checksum;
	u8 data[];
पूर्ण __packed;

काष्ठा port100_ack_frame अणु
	u8 preamble;
	__be16 start_frame;
	__be16 ack_frame;
	u8 postambule;
पूर्ण __packed;

काष्ठा port100_cb_arg अणु
	nfc_digital_cmd_complete_t complete_cb;
	व्योम *complete_arg;
	u8 mdaa;
पूर्ण;

काष्ठा port100_tg_comm_rf_cmd अणु
	__le16 guard_समय;
	__le16 send_समयout;
	u8 mdaa;
	u8 nfca_param[6];
	u8 nfcf_param[18];
	u8 mf_halted;
	u8 arae_flag;
	__le16 recv_समयout;
	u8 data[];
पूर्ण __packed;

काष्ठा port100_tg_comm_rf_res अणु
	u8 comm_type;
	u8 ar_status;
	u8 target_activated;
	__le32 status;
	u8 data[];
पूर्ण __packed;

/* The rule: value + checksum = 0 */
अटल अंतरभूत u8 port100_checksum(u16 value)
अणु
	वापस ~(((u8 *)&value)[0] + ((u8 *)&value)[1]) + 1;
पूर्ण

/* The rule: sum(data elements) + checksum = 0 */
अटल u8 port100_data_checksum(u8 *data, पूर्णांक datalen)
अणु
	u8 sum = 0;
	पूर्णांक i;

	क्रम (i = 0; i < datalen; i++)
		sum += data[i];

	वापस port100_checksum(sum);
पूर्ण

अटल व्योम port100_tx_frame_init(व्योम *_frame, u8 cmd_code)
अणु
	काष्ठा port100_frame *frame = _frame;

	frame->preamble = 0;
	frame->start_frame = cpu_to_be16(PORT100_FRAME_SOF);
	frame->extended_frame = cpu_to_be16(PORT100_FRAME_EXT);
	PORT100_FRAME_सूचीECTION(frame) = PORT100_FRAME_सूची_OUT;
	PORT100_FRAME_CMD(frame) = cmd_code;
	frame->datalen = cpu_to_le16(2);
पूर्ण

अटल व्योम port100_tx_frame_finish(व्योम *_frame)
अणु
	काष्ठा port100_frame *frame = _frame;

	frame->datalen_checksum = port100_checksum(le16_to_cpu(frame->datalen));

	PORT100_FRAME_CHECKSUM(frame) =
		port100_data_checksum(frame->data, le16_to_cpu(frame->datalen));

	PORT100_FRAME_POSTAMBLE(frame) = 0;
पूर्ण

अटल व्योम port100_tx_update_payload_len(व्योम *_frame, पूर्णांक len)
अणु
	काष्ठा port100_frame *frame = _frame;

	le16_add_cpu(&frame->datalen, len);
पूर्ण

अटल bool port100_rx_frame_is_valid(व्योम *_frame)
अणु
	u8 checksum;
	काष्ठा port100_frame *frame = _frame;

	अगर (frame->start_frame != cpu_to_be16(PORT100_FRAME_SOF) ||
	    frame->extended_frame != cpu_to_be16(PORT100_FRAME_EXT))
		वापस false;

	checksum = port100_checksum(le16_to_cpu(frame->datalen));
	अगर (checksum != frame->datalen_checksum)
		वापस false;

	checksum = port100_data_checksum(frame->data,
					 le16_to_cpu(frame->datalen));
	अगर (checksum != PORT100_FRAME_CHECKSUM(frame))
		वापस false;

	वापस true;
पूर्ण

अटल bool port100_rx_frame_is_ack(काष्ठा port100_ack_frame *frame)
अणु
	वापस (frame->start_frame == cpu_to_be16(PORT100_FRAME_SOF) &&
		frame->ack_frame == cpu_to_be16(PORT100_FRAME_ACK));
पूर्ण

अटल अंतरभूत पूर्णांक port100_rx_frame_size(व्योम *frame)
अणु
	काष्ठा port100_frame *f = frame;

	वापस माप(काष्ठा port100_frame) + le16_to_cpu(f->datalen) +
	       PORT100_FRAME_TAIL_LEN;
पूर्ण

अटल bool port100_rx_frame_is_cmd_response(काष्ठा port100 *dev, व्योम *frame)
अणु
	काष्ठा port100_frame *f = frame;

	वापस (PORT100_FRAME_CMD(f) == PORT100_CMD_RESPONSE(dev->cmd->code));
पूर्ण

अटल व्योम port100_recv_response(काष्ठा urb *urb)
अणु
	काष्ठा port100 *dev = urb->context;
	काष्ठा port100_cmd *cmd = dev->cmd;
	u8 *in_frame;

	cmd->status = urb->status;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध; /* success */
	हाल -ECONNRESET:
	हाल -ENOENT:
		nfc_err(&dev->पूर्णांकerface->dev,
			"The urb has been canceled (status %d)\n", urb->status);
		जाओ sched_wq;
	हाल -ESHUTDOWN:
	शेष:
		nfc_err(&dev->पूर्णांकerface->dev, "Urb failure (status %d)\n",
			urb->status);
		जाओ sched_wq;
	पूर्ण

	in_frame = dev->in_urb->transfer_buffer;

	अगर (!port100_rx_frame_is_valid(in_frame)) अणु
		nfc_err(&dev->पूर्णांकerface->dev, "Received an invalid frame\n");
		cmd->status = -EIO;
		जाओ sched_wq;
	पूर्ण

	prपूर्णांक_hex_dump_debug("PORT100 RX: ", DUMP_PREFIX_NONE, 16, 1, in_frame,
			     port100_rx_frame_size(in_frame), false);

	अगर (!port100_rx_frame_is_cmd_response(dev, in_frame)) अणु
		nfc_err(&dev->पूर्णांकerface->dev,
			"It's not the response to the last command\n");
		cmd->status = -EIO;
		जाओ sched_wq;
	पूर्ण

sched_wq:
	schedule_work(&dev->cmd_complete_work);
पूर्ण

अटल पूर्णांक port100_submit_urb_क्रम_response(काष्ठा port100 *dev, gfp_t flags)
अणु
	dev->in_urb->complete = port100_recv_response;

	वापस usb_submit_urb(dev->in_urb, flags);
पूर्ण

अटल व्योम port100_recv_ack(काष्ठा urb *urb)
अणु
	काष्ठा port100 *dev = urb->context;
	काष्ठा port100_cmd *cmd = dev->cmd;
	काष्ठा port100_ack_frame *in_frame;
	पूर्णांक rc;

	cmd->status = urb->status;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध; /* success */
	हाल -ECONNRESET:
	हाल -ENOENT:
		nfc_err(&dev->पूर्णांकerface->dev,
			"The urb has been stopped (status %d)\n", urb->status);
		जाओ sched_wq;
	हाल -ESHUTDOWN:
	शेष:
		nfc_err(&dev->पूर्णांकerface->dev, "Urb failure (status %d)\n",
			urb->status);
		जाओ sched_wq;
	पूर्ण

	in_frame = dev->in_urb->transfer_buffer;

	अगर (!port100_rx_frame_is_ack(in_frame)) अणु
		nfc_err(&dev->पूर्णांकerface->dev, "Received an invalid ack\n");
		cmd->status = -EIO;
		जाओ sched_wq;
	पूर्ण

	rc = port100_submit_urb_क्रम_response(dev, GFP_ATOMIC);
	अगर (rc) अणु
		nfc_err(&dev->पूर्णांकerface->dev,
			"usb_submit_urb failed with result %d\n", rc);
		cmd->status = rc;
		जाओ sched_wq;
	पूर्ण

	वापस;

sched_wq:
	schedule_work(&dev->cmd_complete_work);
पूर्ण

अटल पूर्णांक port100_submit_urb_क्रम_ack(काष्ठा port100 *dev, gfp_t flags)
अणु
	dev->in_urb->complete = port100_recv_ack;

	वापस usb_submit_urb(dev->in_urb, flags);
पूर्ण

अटल पूर्णांक port100_send_ack(काष्ठा port100 *dev)
अणु
	पूर्णांक rc = 0;

	mutex_lock(&dev->out_urb_lock);

	/*
	 * If prior cancel is in-flight (dev->cmd_cancel == true), we
	 * can skip to send cancel. Then this will रुको the prior
	 * cancel, or merged पूर्णांकo the next cancel rarely अगर next
	 * cancel was started beक्रमe रुकोing करोne. In any हाल, this
	 * will be waked up soon or later.
	 */
	अगर (!dev->cmd_cancel) अणु
		reinit_completion(&dev->cmd_cancel_करोne);

		usb_समाप्त_urb(dev->out_urb);

		dev->out_urb->transfer_buffer = ack_frame;
		dev->out_urb->transfer_buffer_length = माप(ack_frame);
		rc = usb_submit_urb(dev->out_urb, GFP_KERNEL);

		/*
		 * Set the cmd_cancel flag only अगर the URB has been
		 * successfully submitted. It will be reset by the out
		 * URB completion callback port100_send_complete().
		 */
		dev->cmd_cancel = !rc;
	पूर्ण

	mutex_unlock(&dev->out_urb_lock);

	अगर (!rc)
		रुको_क्रम_completion(&dev->cmd_cancel_करोne);

	वापस rc;
पूर्ण

अटल पूर्णांक port100_send_frame_async(काष्ठा port100 *dev, काष्ठा sk_buff *out,
				    काष्ठा sk_buff *in, पूर्णांक in_len)
अणु
	पूर्णांक rc;

	mutex_lock(&dev->out_urb_lock);

	/* A command cancel frame as been sent through dev->out_urb. Don't try
	 * to submit a new one.
	 */
	अगर (dev->cmd_cancel) अणु
		rc = -EAGAIN;
		जाओ निकास;
	पूर्ण

	dev->out_urb->transfer_buffer = out->data;
	dev->out_urb->transfer_buffer_length = out->len;

	dev->in_urb->transfer_buffer = in->data;
	dev->in_urb->transfer_buffer_length = in_len;

	prपूर्णांक_hex_dump_debug("PORT100 TX: ", DUMP_PREFIX_NONE, 16, 1,
			     out->data, out->len, false);

	rc = usb_submit_urb(dev->out_urb, GFP_KERNEL);
	अगर (rc)
		जाओ निकास;

	rc = port100_submit_urb_क्रम_ack(dev, GFP_KERNEL);
	अगर (rc)
		usb_समाप्त_urb(dev->out_urb);

निकास:
	mutex_unlock(&dev->out_urb_lock);

	वापस rc;
पूर्ण

अटल व्योम port100_build_cmd_frame(काष्ठा port100 *dev, u8 cmd_code,
				    काष्ठा sk_buff *skb)
अणु
	/* payload is alपढ़ोy there, just update datalen */
	पूर्णांक payload_len = skb->len;

	skb_push(skb, PORT100_FRAME_HEADER_LEN);
	skb_put(skb, PORT100_FRAME_TAIL_LEN);

	port100_tx_frame_init(skb->data, cmd_code);
	port100_tx_update_payload_len(skb->data, payload_len);
	port100_tx_frame_finish(skb->data);
पूर्ण

अटल व्योम port100_send_async_complete(काष्ठा port100 *dev)
अणु
	काष्ठा port100_cmd *cmd = dev->cmd;
	पूर्णांक status = cmd->status;

	काष्ठा sk_buff *req = cmd->req;
	काष्ठा sk_buff *resp = cmd->resp;

	dev_kमुक्त_skb(req);

	dev->cmd = शून्य;

	अगर (status < 0) अणु
		cmd->complete_cb(dev, cmd->complete_cb_context,
				 ERR_PTR(status));
		dev_kमुक्त_skb(resp);
		जाओ करोne;
	पूर्ण

	skb_put(resp, port100_rx_frame_size(resp->data));
	skb_pull(resp, PORT100_FRAME_HEADER_LEN);
	skb_trim(resp, resp->len - PORT100_FRAME_TAIL_LEN);

	cmd->complete_cb(dev, cmd->complete_cb_context, resp);

करोne:
	kमुक्त(cmd);
पूर्ण

अटल पूर्णांक port100_send_cmd_async(काष्ठा port100 *dev, u8 cmd_code,
				काष्ठा sk_buff *req,
				port100_send_async_complete_t complete_cb,
				व्योम *complete_cb_context)
अणु
	काष्ठा port100_cmd *cmd;
	काष्ठा sk_buff *resp;
	पूर्णांक rc;
	पूर्णांक  resp_len = PORT100_FRAME_HEADER_LEN +
			PORT100_FRAME_MAX_PAYLOAD_LEN +
			PORT100_FRAME_TAIL_LEN;

	अगर (dev->cmd) अणु
		nfc_err(&dev->पूर्णांकerface->dev,
			"A command is still in process\n");
		वापस -EBUSY;
	पूर्ण

	resp = alloc_skb(resp_len, GFP_KERNEL);
	अगर (!resp)
		वापस -ENOMEM;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		dev_kमुक्त_skb(resp);
		वापस -ENOMEM;
	पूर्ण

	cmd->code = cmd_code;
	cmd->req = req;
	cmd->resp = resp;
	cmd->resp_len = resp_len;
	cmd->complete_cb = complete_cb;
	cmd->complete_cb_context = complete_cb_context;

	port100_build_cmd_frame(dev, cmd_code, req);

	dev->cmd = cmd;

	rc = port100_send_frame_async(dev, req, resp, resp_len);
	अगर (rc) अणु
		kमुक्त(cmd);
		dev_kमुक्त_skb(resp);
		dev->cmd = शून्य;
	पूर्ण

	वापस rc;
पूर्ण

काष्ठा port100_sync_cmd_response अणु
	काष्ठा sk_buff *resp;
	काष्ठा completion करोne;
पूर्ण;

अटल व्योम port100_wq_cmd_complete(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा port100 *dev = container_of(work, काष्ठा port100,
					   cmd_complete_work);

	port100_send_async_complete(dev);
पूर्ण

अटल व्योम port100_send_sync_complete(काष्ठा port100 *dev, व्योम *_arg,
				      काष्ठा sk_buff *resp)
अणु
	काष्ठा port100_sync_cmd_response *arg = _arg;

	arg->resp = resp;
	complete(&arg->करोne);
पूर्ण

अटल काष्ठा sk_buff *port100_send_cmd_sync(काष्ठा port100 *dev, u8 cmd_code,
					     काष्ठा sk_buff *req)
अणु
	पूर्णांक rc;
	काष्ठा port100_sync_cmd_response arg;

	init_completion(&arg.करोne);

	rc = port100_send_cmd_async(dev, cmd_code, req,
				    port100_send_sync_complete, &arg);
	अगर (rc) अणु
		dev_kमुक्त_skb(req);
		वापस ERR_PTR(rc);
	पूर्ण

	रुको_क्रम_completion(&arg.करोne);

	वापस arg.resp;
पूर्ण

अटल व्योम port100_send_complete(काष्ठा urb *urb)
अणु
	काष्ठा port100 *dev = urb->context;

	अगर (dev->cmd_cancel) अणु
		complete_all(&dev->cmd_cancel_करोne);
		dev->cmd_cancel = false;
	पूर्ण

	चयन (urb->status) अणु
	हाल 0:
		अवरोध; /* success */
	हाल -ECONNRESET:
	हाल -ENOENT:
		nfc_err(&dev->पूर्णांकerface->dev,
			"The urb has been stopped (status %d)\n", urb->status);
		अवरोध;
	हाल -ESHUTDOWN:
	शेष:
		nfc_err(&dev->पूर्णांकerface->dev, "Urb failure (status %d)\n",
			urb->status);
	पूर्ण
पूर्ण

अटल व्योम port100_पात_cmd(काष्ठा nfc_digital_dev *ddev)
अणु
	काष्ठा port100 *dev = nfc_digital_get_drvdata(ddev);

	/* An ack will cancel the last issued command */
	port100_send_ack(dev);

	/* cancel the urb request */
	usb_समाप्त_urb(dev->in_urb);
पूर्ण

अटल काष्ठा sk_buff *port100_alloc_skb(काष्ठा port100 *dev, अचिन्हित पूर्णांक size)
अणु
	काष्ठा sk_buff *skb;

	skb = alloc_skb(dev->skb_headroom + dev->skb_tailroom + size,
			GFP_KERNEL);
	अगर (skb)
		skb_reserve(skb, dev->skb_headroom);

	वापस skb;
पूर्ण

अटल पूर्णांक port100_set_command_type(काष्ठा port100 *dev, u8 command_type)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *resp;
	पूर्णांक rc;

	skb = port100_alloc_skb(dev, 1);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_u8(skb, command_type);

	resp = port100_send_cmd_sync(dev, PORT100_CMD_SET_COMMAND_TYPE, skb);
	अगर (IS_ERR(resp))
		वापस PTR_ERR(resp);

	rc = resp->data[0];

	dev_kमुक्त_skb(resp);

	वापस rc;
पूर्ण

अटल u64 port100_get_command_type_mask(काष्ठा port100 *dev)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *resp;
	u64 mask;

	skb = port100_alloc_skb(dev, 0);
	अगर (!skb)
		वापस -ENOMEM;

	resp = port100_send_cmd_sync(dev, PORT100_CMD_GET_COMMAND_TYPE, skb);
	अगर (IS_ERR(resp))
		वापस PTR_ERR(resp);

	अगर (resp->len < 8)
		mask = 0;
	अन्यथा
		mask = be64_to_cpu(*(__be64 *)resp->data);

	dev_kमुक्त_skb(resp);

	वापस mask;
पूर्ण

अटल u16 port100_get_firmware_version(काष्ठा port100 *dev)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *resp;
	u16 fw_ver;

	skb = port100_alloc_skb(dev, 0);
	अगर (!skb)
		वापस 0;

	resp = port100_send_cmd_sync(dev, PORT100_CMD_GET_FIRMWARE_VERSION,
				     skb);
	अगर (IS_ERR(resp))
		वापस 0;

	fw_ver = le16_to_cpu(*(__le16 *)resp->data);

	dev_kमुक्त_skb(resp);

	वापस fw_ver;
पूर्ण

अटल पूर्णांक port100_चयन_rf(काष्ठा nfc_digital_dev *ddev, bool on)
अणु
	काष्ठा port100 *dev = nfc_digital_get_drvdata(ddev);
	काष्ठा sk_buff *skb, *resp;

	skb = port100_alloc_skb(dev, 1);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_u8(skb, on ? 1 : 0);

	/* Cancel the last command अगर the device is being चयनed off */
	अगर (!on)
		port100_पात_cmd(ddev);

	resp = port100_send_cmd_sync(dev, PORT100_CMD_SWITCH_RF, skb);

	अगर (IS_ERR(resp))
		वापस PTR_ERR(resp);

	dev_kमुक्त_skb(resp);

	वापस 0;
पूर्ण

अटल पूर्णांक port100_in_set_rf(काष्ठा nfc_digital_dev *ddev, u8 rf)
अणु
	काष्ठा port100 *dev = nfc_digital_get_drvdata(ddev);
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *resp;
	पूर्णांक rc;

	अगर (rf >= NFC_DIGITAL_RF_TECH_LAST)
		वापस -EINVAL;

	skb = port100_alloc_skb(dev, माप(काष्ठा port100_in_rf_setting));
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_data(skb, &in_rf_settings[rf],
		     माप(काष्ठा port100_in_rf_setting));

	resp = port100_send_cmd_sync(dev, PORT100_CMD_IN_SET_RF, skb);

	अगर (IS_ERR(resp))
		वापस PTR_ERR(resp);

	rc = resp->data[0];

	dev_kमुक्त_skb(resp);

	वापस rc;
पूर्ण

अटल पूर्णांक port100_in_set_framing(काष्ठा nfc_digital_dev *ddev, पूर्णांक param)
अणु
	काष्ठा port100 *dev = nfc_digital_get_drvdata(ddev);
	काष्ठा port100_protocol *protocols;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *resp;
	पूर्णांक num_protocols;
	माप_प्रकार size;
	पूर्णांक rc;

	अगर (param >= NFC_DIGITAL_FRAMING_LAST)
		वापस -EINVAL;

	protocols = in_protocols[param];

	num_protocols = 0;
	जबतक (protocols[num_protocols].number != PORT100_IN_PROT_END)
		num_protocols++;

	अगर (!num_protocols)
		वापस 0;

	size = माप(काष्ठा port100_protocol) * num_protocols;

	skb = port100_alloc_skb(dev, size);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_data(skb, protocols, size);

	resp = port100_send_cmd_sync(dev, PORT100_CMD_IN_SET_PROTOCOL, skb);

	अगर (IS_ERR(resp))
		वापस PTR_ERR(resp);

	rc = resp->data[0];

	dev_kमुक्त_skb(resp);

	वापस rc;
पूर्ण

अटल पूर्णांक port100_in_configure_hw(काष्ठा nfc_digital_dev *ddev, पूर्णांक type,
				   पूर्णांक param)
अणु
	अगर (type == NFC_DIGITAL_CONFIG_RF_TECH)
		वापस port100_in_set_rf(ddev, param);

	अगर (type == NFC_DIGITAL_CONFIG_FRAMING)
		वापस port100_in_set_framing(ddev, param);

	वापस -EINVAL;
पूर्ण

अटल व्योम port100_in_comm_rf_complete(काष्ठा port100 *dev, व्योम *arg,
				       काष्ठा sk_buff *resp)
अणु
	काष्ठा port100_cb_arg *cb_arg = arg;
	nfc_digital_cmd_complete_t cb = cb_arg->complete_cb;
	u32 status;
	पूर्णांक rc;

	अगर (IS_ERR(resp)) अणु
		rc =  PTR_ERR(resp);
		जाओ निकास;
	पूर्ण

	अगर (resp->len < 4) अणु
		nfc_err(&dev->पूर्णांकerface->dev,
			"Invalid packet length received\n");
		rc = -EIO;
		जाओ error;
	पूर्ण

	status = le32_to_cpu(*(__le32 *)resp->data);

	skb_pull(resp, माप(u32));

	अगर (status == PORT100_CMD_STATUS_TIMEOUT) अणु
		rc = -ETIMEDOUT;
		जाओ error;
	पूर्ण

	अगर (status != PORT100_CMD_STATUS_OK) अणु
		nfc_err(&dev->पूर्णांकerface->dev,
			"in_comm_rf failed with status 0x%08x\n", status);
		rc = -EIO;
		जाओ error;
	पूर्ण

	/* Remove collision bits byte */
	skb_pull(resp, 1);

	जाओ निकास;

error:
	kमुक्त_skb(resp);
	resp = ERR_PTR(rc);

निकास:
	cb(dev->nfc_digital_dev, cb_arg->complete_arg, resp);

	kमुक्त(cb_arg);
पूर्ण

अटल पूर्णांक port100_in_send_cmd(काष्ठा nfc_digital_dev *ddev,
			       काष्ठा sk_buff *skb, u16 _समयout,
			       nfc_digital_cmd_complete_t cb, व्योम *arg)
अणु
	काष्ठा port100 *dev = nfc_digital_get_drvdata(ddev);
	काष्ठा port100_cb_arg *cb_arg;
	__le16 समयout;

	cb_arg = kzalloc(माप(काष्ठा port100_cb_arg), GFP_KERNEL);
	अगर (!cb_arg)
		वापस -ENOMEM;

	cb_arg->complete_cb = cb;
	cb_arg->complete_arg = arg;

	समयout = cpu_to_le16(_समयout * 10);

	स_नकल(skb_push(skb, माप(__le16)), &समयout, माप(__le16));

	वापस port100_send_cmd_async(dev, PORT100_CMD_IN_COMM_RF, skb,
				      port100_in_comm_rf_complete, cb_arg);
पूर्ण

अटल पूर्णांक port100_tg_set_rf(काष्ठा nfc_digital_dev *ddev, u8 rf)
अणु
	काष्ठा port100 *dev = nfc_digital_get_drvdata(ddev);
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *resp;
	पूर्णांक rc;

	अगर (rf >= NFC_DIGITAL_RF_TECH_LAST)
		वापस -EINVAL;

	skb = port100_alloc_skb(dev, माप(काष्ठा port100_tg_rf_setting));
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_data(skb, &tg_rf_settings[rf],
		     माप(काष्ठा port100_tg_rf_setting));

	resp = port100_send_cmd_sync(dev, PORT100_CMD_TG_SET_RF, skb);

	अगर (IS_ERR(resp))
		वापस PTR_ERR(resp);

	rc = resp->data[0];

	dev_kमुक्त_skb(resp);

	वापस rc;
पूर्ण

अटल पूर्णांक port100_tg_set_framing(काष्ठा nfc_digital_dev *ddev, पूर्णांक param)
अणु
	काष्ठा port100 *dev = nfc_digital_get_drvdata(ddev);
	काष्ठा port100_protocol *protocols;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *resp;
	पूर्णांक rc;
	पूर्णांक num_protocols;
	माप_प्रकार size;

	अगर (param >= NFC_DIGITAL_FRAMING_LAST)
		वापस -EINVAL;

	protocols = tg_protocols[param];

	num_protocols = 0;
	जबतक (protocols[num_protocols].number != PORT100_TG_PROT_END)
		num_protocols++;

	अगर (!num_protocols)
		वापस 0;

	size = माप(काष्ठा port100_protocol) * num_protocols;

	skb = port100_alloc_skb(dev, size);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_data(skb, protocols, size);

	resp = port100_send_cmd_sync(dev, PORT100_CMD_TG_SET_PROTOCOL, skb);

	अगर (IS_ERR(resp))
		वापस PTR_ERR(resp);

	rc = resp->data[0];

	dev_kमुक्त_skb(resp);

	वापस rc;
पूर्ण

अटल पूर्णांक port100_tg_configure_hw(काष्ठा nfc_digital_dev *ddev, पूर्णांक type,
				   पूर्णांक param)
अणु
	अगर (type == NFC_DIGITAL_CONFIG_RF_TECH)
		वापस port100_tg_set_rf(ddev, param);

	अगर (type == NFC_DIGITAL_CONFIG_FRAMING)
		वापस port100_tg_set_framing(ddev, param);

	वापस -EINVAL;
पूर्ण

अटल bool port100_tg_target_activated(काष्ठा port100 *dev, u8 tgt_activated)
अणु
	u8 mask;

	चयन (dev->cmd_type) अणु
	हाल PORT100_CMD_TYPE_0:
		mask = PORT100_MDAA_TGT_HAS_BEEN_ACTIVATED_MASK;
		अवरोध;
	हाल PORT100_CMD_TYPE_1:
		mask = PORT100_MDAA_TGT_HAS_BEEN_ACTIVATED_MASK |
		       PORT100_MDAA_TGT_WAS_ACTIVATED_MASK;
		अवरोध;
	शेष:
		nfc_err(&dev->पूर्णांकerface->dev, "Unknown command type\n");
		वापस false;
	पूर्ण

	वापस ((tgt_activated & mask) == mask);
पूर्ण

अटल व्योम port100_tg_comm_rf_complete(काष्ठा port100 *dev, व्योम *arg,
					काष्ठा sk_buff *resp)
अणु
	u32 status;
	काष्ठा port100_cb_arg *cb_arg = arg;
	nfc_digital_cmd_complete_t cb = cb_arg->complete_cb;
	काष्ठा port100_tg_comm_rf_res *hdr;

	अगर (IS_ERR(resp))
		जाओ निकास;

	hdr = (काष्ठा port100_tg_comm_rf_res *)resp->data;

	status = le32_to_cpu(hdr->status);

	अगर (cb_arg->mdaa &&
	    !port100_tg_target_activated(dev, hdr->target_activated)) अणु
		kमुक्त_skb(resp);
		resp = ERR_PTR(-ETIMEDOUT);

		जाओ निकास;
	पूर्ण

	skb_pull(resp, माप(काष्ठा port100_tg_comm_rf_res));

	अगर (status != PORT100_CMD_STATUS_OK) अणु
		kमुक्त_skb(resp);

		अगर (status == PORT100_CMD_STATUS_TIMEOUT)
			resp = ERR_PTR(-ETIMEDOUT);
		अन्यथा
			resp = ERR_PTR(-EIO);
	पूर्ण

निकास:
	cb(dev->nfc_digital_dev, cb_arg->complete_arg, resp);

	kमुक्त(cb_arg);
पूर्ण

अटल पूर्णांक port100_tg_send_cmd(काष्ठा nfc_digital_dev *ddev,
			       काष्ठा sk_buff *skb, u16 समयout,
			       nfc_digital_cmd_complete_t cb, व्योम *arg)
अणु
	काष्ठा port100 *dev = nfc_digital_get_drvdata(ddev);
	काष्ठा port100_tg_comm_rf_cmd *hdr;
	काष्ठा port100_cb_arg *cb_arg;

	cb_arg = kzalloc(माप(काष्ठा port100_cb_arg), GFP_KERNEL);
	अगर (!cb_arg)
		वापस -ENOMEM;

	cb_arg->complete_cb = cb;
	cb_arg->complete_arg = arg;

	skb_push(skb, माप(काष्ठा port100_tg_comm_rf_cmd));

	hdr = (काष्ठा port100_tg_comm_rf_cmd *)skb->data;

	स_रखो(hdr, 0, माप(काष्ठा port100_tg_comm_rf_cmd));
	hdr->guard_समय = cpu_to_le16(500);
	hdr->send_समयout = cpu_to_le16(0xFFFF);
	hdr->recv_समयout = cpu_to_le16(समयout);

	वापस port100_send_cmd_async(dev, PORT100_CMD_TG_COMM_RF, skb,
				      port100_tg_comm_rf_complete, cb_arg);
पूर्ण

अटल पूर्णांक port100_listen_mdaa(काष्ठा nfc_digital_dev *ddev,
			       काष्ठा digital_tg_mdaa_params *params,
			       u16 समयout,
			       nfc_digital_cmd_complete_t cb, व्योम *arg)
अणु
	काष्ठा port100 *dev = nfc_digital_get_drvdata(ddev);
	काष्ठा port100_tg_comm_rf_cmd *hdr;
	काष्ठा port100_cb_arg *cb_arg;
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	rc = port100_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_RF_TECH,
				     NFC_DIGITAL_RF_TECH_106A);
	अगर (rc)
		वापस rc;

	rc = port100_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				     NFC_DIGITAL_FRAMING_NFCA_NFC_DEP);
	अगर (rc)
		वापस rc;

	cb_arg = kzalloc(माप(काष्ठा port100_cb_arg), GFP_KERNEL);
	अगर (!cb_arg)
		वापस -ENOMEM;

	cb_arg->complete_cb = cb;
	cb_arg->complete_arg = arg;
	cb_arg->mdaa = 1;

	skb = port100_alloc_skb(dev, 0);
	अगर (!skb) अणु
		kमुक्त(cb_arg);
		वापस -ENOMEM;
	पूर्ण

	skb_push(skb, माप(काष्ठा port100_tg_comm_rf_cmd));
	hdr = (काष्ठा port100_tg_comm_rf_cmd *)skb->data;

	स_रखो(hdr, 0, माप(काष्ठा port100_tg_comm_rf_cmd));

	hdr->guard_समय = 0;
	hdr->send_समयout = cpu_to_le16(0xFFFF);
	hdr->mdaa = 1;
	hdr->nfca_param[0] = (params->sens_res >> 8) & 0xFF;
	hdr->nfca_param[1] = params->sens_res & 0xFF;
	स_नकल(hdr->nfca_param + 2, params->nfcid1, 3);
	hdr->nfca_param[5] = params->sel_res;
	स_नकल(hdr->nfcf_param, params->nfcid2, 8);
	hdr->nfcf_param[16] = (params->sc >> 8) & 0xFF;
	hdr->nfcf_param[17] = params->sc & 0xFF;
	hdr->recv_समयout = cpu_to_le16(समयout);

	वापस port100_send_cmd_async(dev, PORT100_CMD_TG_COMM_RF, skb,
				      port100_tg_comm_rf_complete, cb_arg);
पूर्ण

अटल पूर्णांक port100_listen(काष्ठा nfc_digital_dev *ddev, u16 समयout,
			  nfc_digital_cmd_complete_t cb, व्योम *arg)
अणु
	काष्ठा port100 *dev = nfc_digital_get_drvdata(ddev);
	काष्ठा sk_buff *skb;

	skb = port100_alloc_skb(dev, 0);
	अगर (!skb)
		वापस -ENOMEM;

	वापस port100_tg_send_cmd(ddev, skb, समयout, cb, arg);
पूर्ण

अटल काष्ठा nfc_digital_ops port100_digital_ops = अणु
	.in_configure_hw = port100_in_configure_hw,
	.in_send_cmd = port100_in_send_cmd,

	.tg_listen_mdaa = port100_listen_mdaa,
	.tg_listen = port100_listen,
	.tg_configure_hw = port100_tg_configure_hw,
	.tg_send_cmd = port100_tg_send_cmd,

	.चयन_rf = port100_चयन_rf,
	.पात_cmd = port100_पात_cmd,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id port100_table[] = अणु
	अणु USB_DEVICE(SONY_VENDOR_ID, RCS380S_PRODUCT_ID), पूर्ण,
	अणु USB_DEVICE(SONY_VENDOR_ID, RCS380P_PRODUCT_ID), पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, port100_table);

अटल पूर्णांक port100_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा port100 *dev;
	पूर्णांक rc;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	पूर्णांक in_endpoपूर्णांक;
	पूर्णांक out_endpoपूर्णांक;
	u16 fw_version;
	u64 cmd_type_mask;
	पूर्णांक i;

	dev = devm_kzalloc(&पूर्णांकerface->dev, माप(काष्ठा port100), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	mutex_init(&dev->out_urb_lock);
	dev->udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));
	dev->पूर्णांकerface = पूर्णांकerface;
	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);

	in_endpoपूर्णांक = out_endpoपूर्णांक = 0;
	अगरace_desc = पूर्णांकerface->cur_altsetting;
	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;

		अगर (!in_endpoपूर्णांक && usb_endpoपूर्णांक_is_bulk_in(endpoपूर्णांक))
			in_endpoपूर्णांक = endpoपूर्णांक->bEndpoपूर्णांकAddress;

		अगर (!out_endpoपूर्णांक && usb_endpoपूर्णांक_is_bulk_out(endpoपूर्णांक))
			out_endpoपूर्णांक = endpoपूर्णांक->bEndpoपूर्णांकAddress;
	पूर्ण

	अगर (!in_endpoपूर्णांक || !out_endpoपूर्णांक) अणु
		nfc_err(&पूर्णांकerface->dev,
			"Could not find bulk-in or bulk-out endpoint\n");
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	dev->in_urb = usb_alloc_urb(0, GFP_KERNEL);
	dev->out_urb = usb_alloc_urb(0, GFP_KERNEL);

	अगर (!dev->in_urb || !dev->out_urb) अणु
		nfc_err(&पूर्णांकerface->dev, "Could not allocate USB URBs\n");
		rc = -ENOMEM;
		जाओ error;
	पूर्ण

	usb_fill_bulk_urb(dev->in_urb, dev->udev,
			  usb_rcvbulkpipe(dev->udev, in_endpoपूर्णांक),
			  शून्य, 0, शून्य, dev);
	usb_fill_bulk_urb(dev->out_urb, dev->udev,
			  usb_sndbulkpipe(dev->udev, out_endpoपूर्णांक),
			  शून्य, 0, port100_send_complete, dev);
	dev->out_urb->transfer_flags = URB_ZERO_PACKET;

	dev->skb_headroom = PORT100_FRAME_HEADER_LEN +
			    PORT100_COMM_RF_HEAD_MAX_LEN;
	dev->skb_tailroom = PORT100_FRAME_TAIL_LEN;

	init_completion(&dev->cmd_cancel_करोne);
	INIT_WORK(&dev->cmd_complete_work, port100_wq_cmd_complete);

	/* The first thing to करो with the Port-100 is to set the command type
	 * to be used. If supported we use command type 1. 0 otherwise.
	 */
	cmd_type_mask = port100_get_command_type_mask(dev);
	अगर (!cmd_type_mask) अणु
		nfc_err(&पूर्णांकerface->dev,
			"Could not get supported command types\n");
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (PORT100_CMD_TYPE_IS_SUPPORTED(cmd_type_mask, PORT100_CMD_TYPE_1))
		dev->cmd_type = PORT100_CMD_TYPE_1;
	अन्यथा
		dev->cmd_type = PORT100_CMD_TYPE_0;

	rc = port100_set_command_type(dev, dev->cmd_type);
	अगर (rc) अणु
		nfc_err(&पूर्णांकerface->dev,
			"The device does not support command type %u\n",
			dev->cmd_type);
		जाओ error;
	पूर्ण

	fw_version = port100_get_firmware_version(dev);
	अगर (!fw_version)
		nfc_err(&पूर्णांकerface->dev,
			"Could not get device firmware version\n");

	nfc_info(&पूर्णांकerface->dev,
		 "Sony NFC Port-100 Series attached (firmware v%x.%02x)\n",
		 (fw_version & 0xFF00) >> 8, fw_version & 0xFF);

	dev->nfc_digital_dev = nfc_digital_allocate_device(&port100_digital_ops,
							   PORT100_PROTOCOLS,
							   PORT100_CAPABILITIES,
							   dev->skb_headroom,
							   dev->skb_tailroom);
	अगर (!dev->nfc_digital_dev) अणु
		nfc_err(&पूर्णांकerface->dev,
			"Could not allocate nfc_digital_dev\n");
		rc = -ENOMEM;
		जाओ error;
	पूर्ण

	nfc_digital_set_parent_dev(dev->nfc_digital_dev, &पूर्णांकerface->dev);
	nfc_digital_set_drvdata(dev->nfc_digital_dev, dev);

	rc = nfc_digital_रेजिस्टर_device(dev->nfc_digital_dev);
	अगर (rc) अणु
		nfc_err(&पूर्णांकerface->dev,
			"Could not register digital device\n");
		जाओ मुक्त_nfc_dev;
	पूर्ण

	वापस 0;

मुक्त_nfc_dev:
	nfc_digital_मुक्त_device(dev->nfc_digital_dev);

error:
	usb_मुक्त_urb(dev->in_urb);
	usb_मुक्त_urb(dev->out_urb);
	usb_put_dev(dev->udev);

	वापस rc;
पूर्ण

अटल व्योम port100_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा port100 *dev;

	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	nfc_digital_unरेजिस्टर_device(dev->nfc_digital_dev);
	nfc_digital_मुक्त_device(dev->nfc_digital_dev);

	usb_समाप्त_urb(dev->in_urb);
	usb_समाप्त_urb(dev->out_urb);

	usb_मुक्त_urb(dev->in_urb);
	usb_मुक्त_urb(dev->out_urb);
	usb_put_dev(dev->udev);

	kमुक्त(dev->cmd);

	nfc_info(&पूर्णांकerface->dev, "Sony Port-100 NFC device disconnected\n");
पूर्ण

अटल काष्ठा usb_driver port100_driver = अणु
	.name =		"port100",
	.probe =	port100_probe,
	.disconnect =	port100_disconnect,
	.id_table =	port100_table,
पूर्ण;

module_usb_driver(port100_driver);

MODULE_DESCRIPTION("NFC Port-100 series usb driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
