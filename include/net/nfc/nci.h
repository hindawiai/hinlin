<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  The NFC Controller Interface is the communication protocol between an
 *  NFC Controller (NFCC) and a Device Host (DH).
 *
 *  Copyright (C) 2014 Marvell International Ltd.
 *  Copyright (C) 2011 Texas Instruments, Inc.
 *
 *  Written by Ilan Elias <ilane@ti.com>
 *
 *  Acknowledgements:
 *  This file is based on hci.h, which was written
 *  by Maxim Krasnyansky.
 */

#अगर_अघोषित __NCI_H
#घोषणा __NCI_H

#समावेश <net/nfc/nfc.h>

/* NCI स्थिरants */
#घोषणा NCI_MAX_NUM_MAPPING_CONFIGS				10
#घोषणा NCI_MAX_NUM_RF_CONFIGS					10
#घोषणा NCI_MAX_NUM_CONN					10
#घोषणा NCI_MAX_PARAM_LEN					251
#घोषणा NCI_MAX_PAYLOAD_SIZE					255
#घोषणा NCI_MAX_PACKET_SIZE					258
#घोषणा NCI_MAX_LARGE_PARAMS_NCI_v2				15
#घोषणा NCI_VER_2_MASK						0x20

/* NCI Status Codes */
#घोषणा NCI_STATUS_OK						0x00
#घोषणा NCI_STATUS_REJECTED					0x01
#घोषणा NCI_STATUS_RF_FRAME_CORRUPTED				0x02
#घोषणा NCI_STATUS_FAILED					0x03
#घोषणा NCI_STATUS_NOT_INITIALIZED				0x04
#घोषणा NCI_STATUS_SYNTAX_ERROR					0x05
#घोषणा NCI_STATUS_SEMANTIC_ERROR				0x06
#घोषणा NCI_STATUS_UNKNOWN_GID					0x07
#घोषणा NCI_STATUS_UNKNOWN_OID					0x08
#घोषणा NCI_STATUS_INVALID_PARAM				0x09
#घोषणा NCI_STATUS_MESSAGE_SIZE_EXCEEDED			0x0a
/* Discovery Specअगरic Status Codes */
#घोषणा NCI_STATUS_DISCOVERY_ALREADY_STARTED			0xa0
#घोषणा NCI_STATUS_DISCOVERY_TARGET_ACTIVATION_FAILED		0xa1
#घोषणा NCI_STATUS_DISCOVERY_TEAR_DOWN				0xa2
/* RF Interface Specअगरic Status Codes */
#घोषणा NCI_STATUS_RF_TRANSMISSION_ERROR			0xb0
#घोषणा NCI_STATUS_RF_PROTOCOL_ERROR				0xb1
#घोषणा NCI_STATUS_RF_TIMEOUT_ERROR				0xb2
/* NFCEE Interface Specअगरic Status Codes */
#घोषणा NCI_STATUS_NFCEE_INTERFACE_ACTIVATION_FAILED		0xc0
#घोषणा NCI_STATUS_NFCEE_TRANSMISSION_ERROR			0xc1
#घोषणा NCI_STATUS_NFCEE_PROTOCOL_ERROR				0xc2
#घोषणा NCI_STATUS_NFCEE_TIMEOUT_ERROR				0xc3

/* NFCEE Interface/Protocols */
#घोषणा NCI_NFCEE_INTERFACE_APDU           0x00
#घोषणा NCI_NFCEE_INTERFACE_HCI_ACCESS     0x01
#घोषणा NCI_NFCEE_INTERFACE_TYPE3_CMD_SET  0x02
#घोषणा NCI_NFCEE_INTERFACE_TRANSPARENT        0x03

/* Destination type */
#घोषणा NCI_DESTINATION_NFCC_LOOPBACK      0x01
#घोषणा NCI_DESTINATION_REMOTE_NFC_ENDPOINT    0x02
#घोषणा NCI_DESTINATION_NFCEE              0x03

/* Destination-specअगरic parameters type */
#घोषणा NCI_DESTINATION_SPECIFIC_PARAM_RF_TYPE     0x00
#घोषणा NCI_DESTINATION_SPECIFIC_PARAM_NFCEE_TYPE  0x01

/* NFCEE Discovery Action */
#घोषणा NCI_NFCEE_DISCOVERY_ACTION_DISABLE			0x00
#घोषणा NCI_NFCEE_DISCOVERY_ACTION_ENABLE			0x01

/* NCI RF Technology and Mode */
#घोषणा NCI_NFC_A_PASSIVE_POLL_MODE				0x00
#घोषणा NCI_NFC_B_PASSIVE_POLL_MODE				0x01
#घोषणा NCI_NFC_F_PASSIVE_POLL_MODE				0x02
#घोषणा NCI_NFC_A_ACTIVE_POLL_MODE				0x03
#घोषणा NCI_NFC_F_ACTIVE_POLL_MODE				0x05
#घोषणा NCI_NFC_V_PASSIVE_POLL_MODE				0x06
#घोषणा NCI_NFC_A_PASSIVE_LISTEN_MODE				0x80
#घोषणा NCI_NFC_B_PASSIVE_LISTEN_MODE				0x81
#घोषणा NCI_NFC_F_PASSIVE_LISTEN_MODE				0x82
#घोषणा NCI_NFC_A_ACTIVE_LISTEN_MODE				0x83
#घोषणा NCI_NFC_F_ACTIVE_LISTEN_MODE				0x85

#घोषणा NCI_RF_TECH_MODE_LISTEN_MASK				0x80

/* NCI RF Technologies */
#घोषणा NCI_NFC_RF_TECHNOLOGY_A					0x00
#घोषणा NCI_NFC_RF_TECHNOLOGY_B					0x01
#घोषणा NCI_NFC_RF_TECHNOLOGY_F					0x02
#घोषणा NCI_NFC_RF_TECHNOLOGY_V					0x03

/* NCI Bit Rates */
#घोषणा NCI_NFC_BIT_RATE_106					0x00
#घोषणा NCI_NFC_BIT_RATE_212					0x01
#घोषणा NCI_NFC_BIT_RATE_424					0x02
#घोषणा NCI_NFC_BIT_RATE_848					0x03
#घोषणा NCI_NFC_BIT_RATE_1695					0x04
#घोषणा NCI_NFC_BIT_RATE_3390					0x05
#घोषणा NCI_NFC_BIT_RATE_6780					0x06
#घोषणा NCI_NFC_BIT_RATE_26					0x20

/* NCI RF Protocols */
#घोषणा NCI_RF_PROTOCOL_UNKNOWN					0x00
#घोषणा NCI_RF_PROTOCOL_T1T					0x01
#घोषणा NCI_RF_PROTOCOL_T2T					0x02
#घोषणा NCI_RF_PROTOCOL_T3T					0x03
#घोषणा NCI_RF_PROTOCOL_ISO_DEP					0x04
#घोषणा NCI_RF_PROTOCOL_NFC_DEP					0x05
#घोषणा NCI_RF_PROTOCOL_T5T					0x06

/* NCI RF Interfaces */
#घोषणा NCI_RF_INTERFACE_NFCEE_सूचीECT				0x00
#घोषणा NCI_RF_INTERFACE_FRAME					0x01
#घोषणा NCI_RF_INTERFACE_ISO_DEP				0x02
#घोषणा NCI_RF_INTERFACE_NFC_DEP				0x03

/* NCI Configuration Parameter Tags */
#घोषणा NCI_PN_ATR_REQ_GEN_BYTES				0x29
#घोषणा NCI_LN_ATR_RES_GEN_BYTES				0x61
#घोषणा NCI_LA_SEL_INFO						0x32
#घोषणा NCI_LF_PROTOCOL_TYPE					0x50
#घोषणा NCI_LF_CON_BITR_F					0x54

/* NCI Configuration Parameters masks */
#घोषणा NCI_LA_SEL_INFO_ISO_DEP_MASK				0x20
#घोषणा NCI_LA_SEL_INFO_NFC_DEP_MASK				0x40
#घोषणा NCI_LF_PROTOCOL_TYPE_NFC_DEP_MASK			0x02
#घोषणा NCI_LF_CON_BITR_F_212					0x02
#घोषणा NCI_LF_CON_BITR_F_424					0x04

/* NCI 2.x Feature Enable Bit */
#घोषणा NCI_FEATURE_DISABLE					0x00

/* NCI Reset types */
#घोषणा NCI_RESET_TYPE_KEEP_CONFIG				0x00
#घोषणा NCI_RESET_TYPE_RESET_CONFIG				0x01

/* NCI Static RF connection ID */
#घोषणा NCI_STATIC_RF_CONN_ID					0x00

/* NCI Data Flow Control */
#घोषणा NCI_DATA_FLOW_CONTROL_NOT_USED				0xff

/* NCI RF_DISCOVER_MAP_CMD modes */
#घोषणा NCI_DISC_MAP_MODE_POLL					0x01
#घोषणा NCI_DISC_MAP_MODE_LISTEN				0x02

/* NCI Discover Notअगरication Type */
#घोषणा NCI_DISCOVER_NTF_TYPE_LAST				0x00
#घोषणा NCI_DISCOVER_NTF_TYPE_LAST_NFCC				0x01
#घोषणा NCI_DISCOVER_NTF_TYPE_MORE				0x02

/* NCI Deactivation Type */
#घोषणा NCI_DEACTIVATE_TYPE_IDLE_MODE				0x00
#घोषणा NCI_DEACTIVATE_TYPE_SLEEP_MODE				0x01
#घोषणा NCI_DEACTIVATE_TYPE_SLEEP_AF_MODE			0x02
#घोषणा NCI_DEACTIVATE_TYPE_DISCOVERY				0x03

/* Message Type (MT) */
#घोषणा NCI_MT_DATA_PKT						0x00
#घोषणा NCI_MT_CMD_PKT						0x01
#घोषणा NCI_MT_RSP_PKT						0x02
#घोषणा NCI_MT_NTF_PKT						0x03

#घोषणा nci_mt(hdr)			(((hdr)[0]>>5)&0x07)
#घोषणा nci_mt_set(hdr, mt)		((hdr)[0] |= (__u8)(((mt)&0x07)<<5))

/* Packet Boundary Flag (PBF) */
#घोषणा NCI_PBF_LAST						0x00
#घोषणा NCI_PBF_CONT						0x01

#घोषणा nci_pbf(hdr)			(__u8)(((hdr)[0]>>4)&0x01)
#घोषणा nci_pbf_set(hdr, pbf)		((hdr)[0] |= (__u8)(((pbf)&0x01)<<4))

/* Control Opcode manipulation */
#घोषणा nci_opcode_pack(gid, oid)	(__u16)((((__u16)((gid)&0x0f))<<8)|\
					((__u16)((oid)&0x3f)))
#घोषणा nci_opcode(hdr)			nci_opcode_pack(hdr[0], hdr[1])
#घोषणा nci_opcode_gid(op)		(__u8)(((op)&0x0f00)>>8)
#घोषणा nci_opcode_oid(op)		(__u8)((op)&0x003f)

/* Payload Length */
#घोषणा nci_plen(hdr)			(__u8)((hdr)[2])

/* Connection ID */
#घोषणा nci_conn_id(hdr)		(__u8)(((hdr)[0])&0x0f)

/* GID values */
#घोषणा NCI_GID_CORE						0x0
#घोषणा NCI_GID_RF_MGMT						0x1
#घोषणा NCI_GID_NFCEE_MGMT					0x2
#घोषणा NCI_GID_PROPRIETARY					0xf

/* ----- NCI over SPI head/crc(tail) room needed क्रम outgoing frames ----- */
#घोषणा NCI_SPI_HDR_LEN						4
#घोषणा NCI_SPI_CRC_LEN						2

/* ---- NCI Packet काष्ठाures ---- */
#घोषणा NCI_CTRL_HDR_SIZE					3
#घोषणा NCI_DATA_HDR_SIZE					3

काष्ठा nci_ctrl_hdr अणु
	__u8	gid;		/* MT & PBF & GID */
	__u8	oid;
	__u8	plen;
पूर्ण __packed;

काष्ठा nci_data_hdr अणु
	__u8	conn_id;	/* MT & PBF & ConnID */
	__u8	rfu;
	__u8	plen;
पूर्ण __packed;

/* ------------------------ */
/* -----  NCI Commands ---- */
/* ------------------------ */
#घोषणा NCI_OP_CORE_RESET_CMD		nci_opcode_pack(NCI_GID_CORE, 0x00)
काष्ठा nci_core_reset_cmd अणु
	__u8	reset_type;
पूर्ण __packed;

#घोषणा NCI_OP_CORE_INIT_CMD		nci_opcode_pack(NCI_GID_CORE, 0x01)
/* To support NCI 2.x */
काष्ठा nci_core_init_v2_cmd अणु
	u8	feature1;
	u8	feature2;
पूर्ण;

#घोषणा NCI_OP_CORE_SET_CONFIG_CMD	nci_opcode_pack(NCI_GID_CORE, 0x02)
काष्ठा set_config_param अणु
	__u8	id;
	__u8	len;
	__u8	val[NCI_MAX_PARAM_LEN];
पूर्ण __packed;

काष्ठा nci_core_set_config_cmd अणु
	__u8	num_params;
	काष्ठा	set_config_param param; /* support 1 param per cmd is enough */
पूर्ण __packed;

#घोषणा NCI_OP_CORE_CONN_CREATE_CMD	nci_opcode_pack(NCI_GID_CORE, 0x04)
#घोषणा DEST_SPEC_PARAMS_ID_INDEX	0
#घोषणा DEST_SPEC_PARAMS_PROTOCOL_INDEX	1
काष्ठा dest_spec_params अणु
	__u8    id;
	__u8    protocol;
पूर्ण __packed;

काष्ठा core_conn_create_dest_spec_params अणु
	__u8    type;
	__u8    length;
	__u8    value[];
पूर्ण __packed;

काष्ठा nci_core_conn_create_cmd अणु
	__u8    destination_type;
	__u8    number_destination_params;
	काष्ठा core_conn_create_dest_spec_params params[];
पूर्ण __packed;

#घोषणा NCI_OP_CORE_CONN_CLOSE_CMD	nci_opcode_pack(NCI_GID_CORE, 0x05)

#घोषणा NCI_OP_RF_DISCOVER_MAP_CMD	nci_opcode_pack(NCI_GID_RF_MGMT, 0x00)
काष्ठा disc_map_config अणु
	__u8	rf_protocol;
	__u8	mode;
	__u8	rf_पूर्णांकerface;
पूर्ण __packed;

काष्ठा nci_rf_disc_map_cmd अणु
	__u8				num_mapping_configs;
	काष्ठा disc_map_config		mapping_configs
					[NCI_MAX_NUM_MAPPING_CONFIGS];
पूर्ण __packed;

#घोषणा NCI_OP_RF_DISCOVER_CMD		nci_opcode_pack(NCI_GID_RF_MGMT, 0x03)
काष्ठा disc_config अणु
	__u8	rf_tech_and_mode;
	__u8	frequency;
पूर्ण __packed;

काष्ठा nci_rf_disc_cmd अणु
	__u8				num_disc_configs;
	काष्ठा disc_config		disc_configs[NCI_MAX_NUM_RF_CONFIGS];
पूर्ण __packed;

#घोषणा NCI_OP_RF_DISCOVER_SELECT_CMD	nci_opcode_pack(NCI_GID_RF_MGMT, 0x04)
काष्ठा nci_rf_discover_select_cmd अणु
	__u8	rf_discovery_id;
	__u8	rf_protocol;
	__u8	rf_पूर्णांकerface;
पूर्ण __packed;

#घोषणा NCI_OP_RF_DEACTIVATE_CMD	nci_opcode_pack(NCI_GID_RF_MGMT, 0x06)
काष्ठा nci_rf_deactivate_cmd अणु
	__u8	type;
पूर्ण __packed;

#घोषणा NCI_OP_NFCEE_DISCOVER_CMD nci_opcode_pack(NCI_GID_NFCEE_MGMT, 0x00)
काष्ठा nci_nfcee_discover_cmd अणु
	__u8	discovery_action;
पूर्ण __packed;

#घोषणा NCI_OP_NFCEE_MODE_SET_CMD nci_opcode_pack(NCI_GID_NFCEE_MGMT, 0x01)
#घोषणा NCI_NFCEE_DISABLE	0x00
#घोषणा NCI_NFCEE_ENABLE	0x01
काष्ठा nci_nfcee_mode_set_cmd अणु
	__u8	nfcee_id;
	__u8	nfcee_mode;
पूर्ण __packed;

#घोषणा NCI_OP_CORE_GET_CONFIG_CMD	nci_opcode_pack(NCI_GID_CORE, 0x03)

/* ----------------------- */
/* ---- NCI Responses ---- */
/* ----------------------- */
#घोषणा NCI_OP_CORE_RESET_RSP		nci_opcode_pack(NCI_GID_CORE, 0x00)
काष्ठा nci_core_reset_rsp अणु
	__u8	status;
	__u8	nci_ver;
	__u8	config_status;
पूर्ण __packed;

#घोषणा NCI_OP_CORE_INIT_RSP		nci_opcode_pack(NCI_GID_CORE, 0x01)
काष्ठा nci_core_init_rsp_1 अणु
	__u8	status;
	__le32	nfcc_features;
	__u8	num_supported_rf_पूर्णांकerfaces;
	__u8	supported_rf_पूर्णांकerfaces[];	/* variable size array */
	/* continuted in nci_core_init_rsp_2 */
पूर्ण __packed;

काष्ठा nci_core_init_rsp_2 अणु
	__u8	max_logical_connections;
	__le16	max_routing_table_size;
	__u8	max_ctrl_pkt_payload_len;
	__le16	max_size_क्रम_large_params;
	__u8	manufact_id;
	__le32	manufact_specअगरic_info;
पूर्ण __packed;

/* To support NCI ver 2.x */
काष्ठा nci_core_init_rsp_nci_ver2 अणु
	u8	status;
	__le32	nfcc_features;
	u8	max_logical_connections;
	__le16	max_routing_table_size;
	u8	max_ctrl_pkt_payload_len;
	u8	max_data_pkt_hci_payload_len;
	u8	number_of_hci_credit;
	__le16	max_nfc_v_frame_size;
	u8	num_supported_rf_पूर्णांकerfaces;
	u8	supported_rf_पूर्णांकerfaces[];
पूर्ण __packed;

#घोषणा NCI_OP_CORE_SET_CONFIG_RSP	nci_opcode_pack(NCI_GID_CORE, 0x02)
काष्ठा nci_core_set_config_rsp अणु
	__u8	status;
	__u8	num_params;
	__u8	params_id[];	/* variable size array */
पूर्ण __packed;

#घोषणा NCI_OP_CORE_CONN_CREATE_RSP	nci_opcode_pack(NCI_GID_CORE, 0x04)
काष्ठा nci_core_conn_create_rsp अणु
	__u8	status;
	__u8	max_ctrl_pkt_payload_len;
	__u8    credits_cnt;
	__u8	conn_id;
पूर्ण __packed;

#घोषणा NCI_OP_CORE_CONN_CLOSE_RSP	nci_opcode_pack(NCI_GID_CORE, 0x05)

#घोषणा NCI_OP_RF_DISCOVER_MAP_RSP	nci_opcode_pack(NCI_GID_RF_MGMT, 0x00)

#घोषणा NCI_OP_RF_DISCOVER_RSP		nci_opcode_pack(NCI_GID_RF_MGMT, 0x03)

#घोषणा NCI_OP_RF_DISCOVER_SELECT_RSP	nci_opcode_pack(NCI_GID_RF_MGMT, 0x04)

#घोषणा NCI_OP_RF_DEACTIVATE_RSP	nci_opcode_pack(NCI_GID_RF_MGMT, 0x06)

#घोषणा NCI_OP_NFCEE_DISCOVER_RSP nci_opcode_pack(NCI_GID_NFCEE_MGMT, 0x00)
काष्ठा nci_nfcee_discover_rsp अणु
	__u8	status;
	__u8	num_nfcee;
पूर्ण __packed;

#घोषणा NCI_OP_NFCEE_MODE_SET_RSP nci_opcode_pack(NCI_GID_NFCEE_MGMT, 0x01)

#घोषणा NCI_OP_CORE_GET_CONFIG_RSP	nci_opcode_pack(NCI_GID_CORE, 0x03)

/* --------------------------- */
/* ---- NCI Notअगरications ---- */
/* --------------------------- */
#घोषणा NCI_OP_CORE_RESET_NTF		nci_opcode_pack(NCI_GID_CORE, 0x00)
काष्ठा nci_core_reset_ntf अणु
	u8	reset_trigger;
	u8	config_status;
	u8	nci_ver;
	u8	manufact_id;
	u8	manufacturer_specअगरic_len;
	__le32	manufact_specअगरic_info;
पूर्ण __packed;

#घोषणा NCI_OP_CORE_CONN_CREDITS_NTF	nci_opcode_pack(NCI_GID_CORE, 0x06)
काष्ठा conn_credit_entry अणु
	__u8	conn_id;
	__u8	credits;
पूर्ण __packed;

काष्ठा nci_core_conn_credit_ntf अणु
	__u8				num_entries;
	काष्ठा conn_credit_entry	conn_entries[NCI_MAX_NUM_CONN];
पूर्ण __packed;

#घोषणा NCI_OP_CORE_GENERIC_ERROR_NTF	nci_opcode_pack(NCI_GID_CORE, 0x07)

#घोषणा NCI_OP_CORE_INTF_ERROR_NTF	nci_opcode_pack(NCI_GID_CORE, 0x08)
काष्ठा nci_core_पूर्णांकf_error_ntf अणु
	__u8	status;
	__u8	conn_id;
पूर्ण __packed;

#घोषणा NCI_OP_RF_DISCOVER_NTF		nci_opcode_pack(NCI_GID_RF_MGMT, 0x03)
काष्ठा rf_tech_specअगरic_params_nfca_poll अणु
	__u16	sens_res;
	__u8	nfcid1_len;	/* 0, 4, 7, or 10 Bytes */
	__u8	nfcid1[NFC_NFCID1_MAXSIZE];
	__u8	sel_res_len;	/* 0 or 1 Bytes */
	__u8	sel_res;
पूर्ण __packed;

काष्ठा rf_tech_specअगरic_params_nfcb_poll अणु
	__u8	sensb_res_len;
	__u8	sensb_res[NFC_SENSB_RES_MAXSIZE];	/* 11 or 12 Bytes */
पूर्ण __packed;

काष्ठा rf_tech_specअगरic_params_nfcf_poll अणु
	__u8	bit_rate;
	__u8	sensf_res_len;
	__u8	sensf_res[NFC_SENSF_RES_MAXSIZE];	/* 16 or 18 Bytes */
पूर्ण __packed;

काष्ठा rf_tech_specअगरic_params_nfcv_poll अणु
	__u8	res_flags;
	__u8	dsfid;
	__u8	uid[NFC_ISO15693_UID_MAXSIZE];	/* 8 Bytes */
पूर्ण __packed;

काष्ठा rf_tech_specअगरic_params_nfcf_listen अणु
	__u8	local_nfcid2_len;
	__u8	local_nfcid2[NFC_NFCID2_MAXSIZE];	/* 0 or 8 Bytes */
पूर्ण __packed;

काष्ठा nci_rf_discover_ntf अणु
	__u8	rf_discovery_id;
	__u8	rf_protocol;
	__u8	rf_tech_and_mode;
	__u8	rf_tech_specअगरic_params_len;

	जोड़ अणु
		काष्ठा rf_tech_specअगरic_params_nfca_poll nfca_poll;
		काष्ठा rf_tech_specअगरic_params_nfcb_poll nfcb_poll;
		काष्ठा rf_tech_specअगरic_params_nfcf_poll nfcf_poll;
		काष्ठा rf_tech_specअगरic_params_nfcv_poll nfcv_poll;
	पूर्ण rf_tech_specअगरic_params;

	__u8	ntf_type;
पूर्ण __packed;

#घोषणा NCI_OP_RF_INTF_ACTIVATED_NTF	nci_opcode_pack(NCI_GID_RF_MGMT, 0x05)
काष्ठा activation_params_nfca_poll_iso_dep अणु
	__u8	rats_res_len;
	__u8	rats_res[20];
पूर्ण;

काष्ठा activation_params_nfcb_poll_iso_dep अणु
	__u8	attrib_res_len;
	__u8	attrib_res[50];
पूर्ण;

काष्ठा activation_params_poll_nfc_dep अणु
	__u8	atr_res_len;
	__u8	atr_res[NFC_ATR_RES_MAXSIZE - 2]; /* ATR_RES from byte 3 */
पूर्ण;

काष्ठा activation_params_listen_nfc_dep अणु
	__u8	atr_req_len;
	__u8	atr_req[NFC_ATR_REQ_MAXSIZE - 2]; /* ATR_REQ from byte 3 */
पूर्ण;

काष्ठा nci_rf_पूर्णांकf_activated_ntf अणु
	__u8	rf_discovery_id;
	__u8	rf_पूर्णांकerface;
	__u8	rf_protocol;
	__u8	activation_rf_tech_and_mode;
	__u8	max_data_pkt_payload_size;
	__u8	initial_num_credits;
	__u8	rf_tech_specअगरic_params_len;

	जोड़ अणु
		काष्ठा rf_tech_specअगरic_params_nfca_poll nfca_poll;
		काष्ठा rf_tech_specअगरic_params_nfcb_poll nfcb_poll;
		काष्ठा rf_tech_specअगरic_params_nfcf_poll nfcf_poll;
		काष्ठा rf_tech_specअगरic_params_nfcv_poll nfcv_poll;
		काष्ठा rf_tech_specअगरic_params_nfcf_listen nfcf_listen;
	पूर्ण rf_tech_specअगरic_params;

	__u8	data_exch_rf_tech_and_mode;
	__u8	data_exch_tx_bit_rate;
	__u8	data_exch_rx_bit_rate;
	__u8	activation_params_len;

	जोड़ अणु
		काष्ठा activation_params_nfca_poll_iso_dep nfca_poll_iso_dep;
		काष्ठा activation_params_nfcb_poll_iso_dep nfcb_poll_iso_dep;
		काष्ठा activation_params_poll_nfc_dep poll_nfc_dep;
		काष्ठा activation_params_listen_nfc_dep listen_nfc_dep;
	पूर्ण activation_params;

पूर्ण __packed;

#घोषणा NCI_OP_RF_DEACTIVATE_NTF	nci_opcode_pack(NCI_GID_RF_MGMT, 0x06)
काष्ठा nci_rf_deactivate_ntf अणु
	__u8	type;
	__u8	reason;
पूर्ण __packed;

#घोषणा NCI_OP_RF_NFCEE_ACTION_NTF	nci_opcode_pack(NCI_GID_RF_MGMT, 0x09)
काष्ठा nci_rf_nfcee_action_ntf अणु
	__u8 nfcee_id;
	__u8 trigger;
	__u8 supported_data_length;
	__u8 supported_data[];
पूर्ण __packed;

#घोषणा NCI_OP_NFCEE_DISCOVER_NTF nci_opcode_pack(NCI_GID_NFCEE_MGMT, 0x00)
काष्ठा nci_nfcee_supported_protocol अणु
	__u8	num_protocol;
	__u8	supported_protocol[];
पूर्ण __packed;

काष्ठा nci_nfcee_inक्रमmation_tlv अणु
	__u8	num_tlv;
	__u8	inक्रमmation_tlv[];
पूर्ण __packed;

काष्ठा nci_nfcee_discover_ntf अणु
	__u8	nfcee_id;
	__u8	nfcee_status;
	काष्ठा nci_nfcee_supported_protocol supported_protocols;
	काष्ठा nci_nfcee_inक्रमmation_tlv	inक्रमmation_tlv;
पूर्ण __packed;

#घोषणा NCI_OP_CORE_RESET_NTF		nci_opcode_pack(NCI_GID_CORE, 0x00)

#पूर्ण_अगर /* __NCI_H */
