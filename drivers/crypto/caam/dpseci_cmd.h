<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/*
 * Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2017-2018 NXP
 */

#अगर_अघोषित _DPSECI_CMD_H_
#घोषणा _DPSECI_CMD_H_

/* DPSECI Version */
#घोषणा DPSECI_VER_MAJOR				5
#घोषणा DPSECI_VER_MINOR				3

#घोषणा DPSECI_VER(maj, min)	(((maj) << 16) | (min))
#घोषणा DPSECI_VERSION		DPSECI_VER(DPSECI_VER_MAJOR, DPSECI_VER_MINOR)

/* Command versioning */
#घोषणा DPSECI_CMD_BASE_VERSION		1
#घोषणा DPSECI_CMD_BASE_VERSION_V2	2
#घोषणा DPSECI_CMD_ID_OFFSET		4

#घोषणा DPSECI_CMD_V1(id)	(((id) << DPSECI_CMD_ID_OFFSET) | \
				 DPSECI_CMD_BASE_VERSION)

#घोषणा DPSECI_CMD_V2(id)	(((id) << DPSECI_CMD_ID_OFFSET) | \
				 DPSECI_CMD_BASE_VERSION_V2)

/* Command IDs */
#घोषणा DPSECI_CMDID_CLOSE				DPSECI_CMD_V1(0x800)
#घोषणा DPSECI_CMDID_OPEN				DPSECI_CMD_V1(0x809)
#घोषणा DPSECI_CMDID_GET_API_VERSION			DPSECI_CMD_V1(0xa09)

#घोषणा DPSECI_CMDID_ENABLE				DPSECI_CMD_V1(0x002)
#घोषणा DPSECI_CMDID_DISABLE				DPSECI_CMD_V1(0x003)
#घोषणा DPSECI_CMDID_GET_ATTR				DPSECI_CMD_V1(0x004)
#घोषणा DPSECI_CMDID_RESET				DPSECI_CMD_V1(0x005)
#घोषणा DPSECI_CMDID_IS_ENABLED				DPSECI_CMD_V1(0x006)

#घोषणा DPSECI_CMDID_SET_RX_QUEUE			DPSECI_CMD_V1(0x194)
#घोषणा DPSECI_CMDID_GET_RX_QUEUE			DPSECI_CMD_V1(0x196)
#घोषणा DPSECI_CMDID_GET_TX_QUEUE			DPSECI_CMD_V1(0x197)
#घोषणा DPSECI_CMDID_GET_SEC_ATTR			DPSECI_CMD_V2(0x198)
#घोषणा DPSECI_CMDID_SET_CONGESTION_NOTIFICATION	DPSECI_CMD_V1(0x170)
#घोषणा DPSECI_CMDID_GET_CONGESTION_NOTIFICATION	DPSECI_CMD_V1(0x171)

/* Macros क्रम accessing command fields smaller than 1 byte */
#घोषणा DPSECI_MASK(field)	\
	GENMASK(DPSECI_##field##_SHIFT + DPSECI_##field##_SIZE - 1,	\
		DPSECI_##field##_SHIFT)

#घोषणा dpseci_set_field(var, field, val)	\
	((var) |= (((val) << DPSECI_##field##_SHIFT) & DPSECI_MASK(field)))

#घोषणा dpseci_get_field(var, field)	\
	(((var) & DPSECI_MASK(field)) >> DPSECI_##field##_SHIFT)

काष्ठा dpseci_cmd_खोलो अणु
	__le32 dpseci_id;
पूर्ण;

#घोषणा DPSECI_ENABLE_SHIFT	0
#घोषणा DPSECI_ENABLE_SIZE	1

काष्ठा dpseci_rsp_is_enabled अणु
	u8 is_enabled;
पूर्ण;

काष्ठा dpseci_rsp_get_attributes अणु
	__le32 id;
	__le32 pad0;
	u8 num_tx_queues;
	u8 num_rx_queues;
	u8 pad1[6];
	__le32 options;
पूर्ण;

#घोषणा DPSECI_DEST_TYPE_SHIFT	0
#घोषणा DPSECI_DEST_TYPE_SIZE	4

#घोषणा DPSECI_ORDER_PRESERVATION_SHIFT	0
#घोषणा DPSECI_ORDER_PRESERVATION_SIZE	1

काष्ठा dpseci_cmd_queue अणु
	__le32 dest_id;
	u8 priority;
	u8 queue;
	u8 dest_type;
	u8 pad;
	__le64 user_ctx;
	जोड़ अणु
		__le32 options;
		__le32 fqid;
	पूर्ण;
	u8 order_preservation_en;
पूर्ण;

काष्ठा dpseci_rsp_get_tx_queue अणु
	__le32 pad;
	__le32 fqid;
	u8 priority;
पूर्ण;

काष्ठा dpseci_rsp_get_sec_attr अणु
	__le16 ip_id;
	u8 major_rev;
	u8 minor_rev;
	u8 era;
	u8 pad0[3];
	u8 deco_num;
	u8 zuc_auth_acc_num;
	u8 zuc_enc_acc_num;
	u8 pad1;
	u8 snow_f8_acc_num;
	u8 snow_f9_acc_num;
	u8 crc_acc_num;
	u8 pad2;
	u8 pk_acc_num;
	u8 kasumi_acc_num;
	u8 rng_acc_num;
	u8 pad3;
	u8 md_acc_num;
	u8 arc4_acc_num;
	u8 des_acc_num;
	u8 aes_acc_num;
	u8 ccha_acc_num;
	u8 ptha_acc_num;
पूर्ण;

काष्ठा dpseci_rsp_get_api_version अणु
	__le16 major;
	__le16 minor;
पूर्ण;

#घोषणा DPSECI_CGN_DEST_TYPE_SHIFT	0
#घोषणा DPSECI_CGN_DEST_TYPE_SIZE	4
#घोषणा DPSECI_CGN_UNITS_SHIFT		4
#घोषणा DPSECI_CGN_UNITS_SIZE		2

काष्ठा dpseci_cmd_congestion_notअगरication अणु
	__le32 dest_id;
	__le16 notअगरication_mode;
	u8 priority;
	u8 options;
	__le64 message_iova;
	__le64 message_ctx;
	__le32 threshold_entry;
	__le32 threshold_निकास;
पूर्ण;

#पूर्ण_अगर /* _DPSECI_CMD_H_ */
