<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ibmvfc.h -- driver क्रम IBM Power Virtual Fibre Channel Adapter
 *
 * Written By: Brian King <brking@linux.vnet.ibm.com>, IBM Corporation
 *
 * Copyright (C) IBM Corporation, 2008
 */

#अगर_अघोषित _IBMVFC_H
#घोषणा _IBMVFC_H

#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <scsi/viosrp.h>

#घोषणा IBMVFC_NAME	"ibmvfc"
#घोषणा IBMVFC_DRIVER_VERSION		"1.0.11"
#घोषणा IBMVFC_DRIVER_DATE		"(April 12, 2013)"

#घोषणा IBMVFC_DEFAULT_TIMEOUT	60
#घोषणा IBMVFC_ADISC_CANCEL_TIMEOUT	45
#घोषणा IBMVFC_ADISC_TIMEOUT		15
#घोषणा IBMVFC_ADISC_PLUS_CANCEL_TIMEOUT	\
		(IBMVFC_ADISC_TIMEOUT + IBMVFC_ADISC_CANCEL_TIMEOUT)
#घोषणा IBMVFC_INIT_TIMEOUT		120
#घोषणा IBMVFC_ABORT_TIMEOUT		8
#घोषणा IBMVFC_ABORT_WAIT_TIMEOUT	40
#घोषणा IBMVFC_MAX_REQUESTS_DEFAULT	100

#घोषणा IBMVFC_DEBUG			0
#घोषणा IBMVFC_MAX_TARGETS		1024
#घोषणा IBMVFC_MAX_LUN			0xffffffff
#घोषणा IBMVFC_MAX_SECTORS		0xffffu
#घोषणा IBMVFC_MAX_DISC_THREADS	4
#घोषणा IBMVFC_TGT_MEMPOOL_SZ		64
#घोषणा IBMVFC_MAX_CMDS_PER_LUN	64
#घोषणा IBMVFC_MAX_HOST_INIT_RETRIES	6
#घोषणा IBMVFC_MAX_TGT_INIT_RETRIES		3
#घोषणा IBMVFC_DEV_LOSS_TMO		(5 * 60)
#घोषणा IBMVFC_DEFAULT_LOG_LEVEL	2
#घोषणा IBMVFC_MAX_CDB_LEN		16
#घोषणा IBMVFC_CLS3_ERROR		0
#घोषणा IBMVFC_MQ			1
#घोषणा IBMVFC_SCSI_CHANNELS		8
#घोषणा IBMVFC_MAX_SCSI_QUEUES		16
#घोषणा IBMVFC_SCSI_HW_QUEUES		8
#घोषणा IBMVFC_MIG_NO_SUB_TO_CRQ	0
#घोषणा IBMVFC_MIG_NO_N_TO_M		0

/*
 * Ensure we have resources क्रम ERP and initialization:
 * 1 क्रम ERP
 * 1 क्रम initialization
 * 1 क्रम NPIV Logout
 * 2 क्रम BSG passthru
 * 2 क्रम each discovery thपढ़ो
 */
#घोषणा IBMVFC_NUM_INTERNAL_REQ	(1 + 1 + 1 + 2 + (disc_thपढ़ोs * 2))

#घोषणा IBMVFC_MAD_SUCCESS		0x00
#घोषणा IBMVFC_MAD_NOT_SUPPORTED	0xF1
#घोषणा IBMVFC_MAD_VERSION_NOT_SUPP	0xF2
#घोषणा IBMVFC_MAD_FAILED		0xF7
#घोषणा IBMVFC_MAD_DRIVER_FAILED	0xEE
#घोषणा IBMVFC_MAD_CRQ_ERROR		0xEF

क्रमागत ibmvfc_crq_valid अणु
	IBMVFC_CRQ_CMD_RSP		= 0x80,
	IBMVFC_CRQ_INIT_RSP		= 0xC0,
	IBMVFC_CRQ_XPORT_EVENT		= 0xFF,
पूर्ण;

क्रमागत ibmvfc_crq_init_msg अणु
	IBMVFC_CRQ_INIT			= 0x01,
	IBMVFC_CRQ_INIT_COMPLETE	= 0x02,
पूर्ण;

क्रमागत ibmvfc_crq_xport_evts अणु
	IBMVFC_PARTNER_FAILED		= 0x01,
	IBMVFC_PARTNER_DEREGISTER	= 0x02,
	IBMVFC_PARTITION_MIGRATED	= 0x06,
पूर्ण;

क्रमागत ibmvfc_cmd_status_flags अणु
	IBMVFC_FABRIC_MAPPED		= 0x0001,
	IBMVFC_VIOS_FAILURE		= 0x0002,
	IBMVFC_FC_FAILURE			= 0x0004,
	IBMVFC_FC_SCSI_ERROR		= 0x0008,
	IBMVFC_HW_EVENT_LOGGED		= 0x0010,
	IBMVFC_VIOS_LOGGED		= 0x0020,
पूर्ण;

क्रमागत ibmvfc_fabric_mapped_errors अणु
	IBMVFC_UNABLE_TO_ESTABLISH	= 0x0001,
	IBMVFC_XPORT_FAULT		= 0x0002,
	IBMVFC_CMD_TIMEOUT		= 0x0003,
	IBMVFC_ENETDOWN			= 0x0004,
	IBMVFC_HW_FAILURE			= 0x0005,
	IBMVFC_LINK_DOWN_ERR		= 0x0006,
	IBMVFC_LINK_DEAD_ERR		= 0x0007,
	IBMVFC_UNABLE_TO_REGISTER	= 0x0008,
	IBMVFC_XPORT_BUSY			= 0x000A,
	IBMVFC_XPORT_DEAD			= 0x000B,
	IBMVFC_CONFIG_ERROR		= 0x000C,
	IBMVFC_NAME_SERVER_FAIL		= 0x000D,
	IBMVFC_LINK_HALTED		= 0x000E,
	IBMVFC_XPORT_GENERAL		= 0x8000,
पूर्ण;

क्रमागत ibmvfc_vios_errors अणु
	IBMVFC_CRQ_FAILURE			= 0x0001,
	IBMVFC_SW_FAILURE				= 0x0002,
	IBMVFC_INVALID_PARAMETER		= 0x0003,
	IBMVFC_MISSING_PARAMETER		= 0x0004,
	IBMVFC_HOST_IO_BUS			= 0x0005,
	IBMVFC_TRANS_CANCELLED			= 0x0006,
	IBMVFC_TRANS_CANCELLED_IMPLICIT	= 0x0007,
	IBMVFC_INSUFFICIENT_RESOURCE		= 0x0008,
	IBMVFC_PLOGI_REQUIRED			= 0x0010,
	IBMVFC_COMMAND_FAILED			= 0x8000,
पूर्ण;

क्रमागत ibmvfc_mad_types अणु
	IBMVFC_NPIV_LOGIN		= 0x0001,
	IBMVFC_DISC_TARGETS	= 0x0002,
	IBMVFC_PORT_LOGIN		= 0x0004,
	IBMVFC_PROCESS_LOGIN	= 0x0008,
	IBMVFC_QUERY_TARGET	= 0x0010,
	IBMVFC_MOVE_LOGIN		= 0x0020,
	IBMVFC_IMPLICIT_LOGOUT	= 0x0040,
	IBMVFC_PASSTHRU		= 0x0200,
	IBMVFC_TMF_MAD		= 0x0100,
	IBMVFC_NPIV_LOGOUT	= 0x0800,
	IBMVFC_CHANNEL_ENQUIRY	= 0x1000,
	IBMVFC_CHANNEL_SETUP	= 0x2000,
	IBMVFC_CONNECTION_INFO	= 0x4000,
पूर्ण;

काष्ठा ibmvfc_mad_common अणु
	__be32 version;
	__be32 reserved;
	__be32 opcode;
	__be16 status;
	__be16 length;
	__be64 tag;
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_npiv_login_mad अणु
	काष्ठा ibmvfc_mad_common common;
	काष्ठा srp_direct_buf buffer;
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_npiv_logout_mad अणु
	काष्ठा ibmvfc_mad_common common;
पूर्ण __packed __aligned(8);

#घोषणा IBMVFC_MAX_NAME 256

काष्ठा ibmvfc_npiv_login अणु
	__be32 ostype;
#घोषणा IBMVFC_OS_LINUX	0x02
	__be32 pad;
	__be64 max_dma_len;
	__be32 max_payload;
	__be32 max_response;
	__be32 partition_num;
	__be32 vfc_frame_version;
	__be16 fcp_version;
	__be16 flags;
#घोषणा IBMVFC_CLIENT_MIGRATED	0x01
#घोषणा IBMVFC_FLUSH_ON_HALT		0x02
	__be32 max_cmds;
	__be64 capabilities;
#घोषणा IBMVFC_CAN_MIGRATE		0x01
#घोषणा IBMVFC_CAN_USE_CHANNELS		0x02
#घोषणा IBMVFC_CAN_HANDLE_FPIN		0x04
#घोषणा IBMVFC_CAN_USE_MAD_VERSION	0x08
#घोषणा IBMVFC_CAN_SEND_VF_WWPN		0x10
	__be64 node_name;
	काष्ठा srp_direct_buf async;
	u8 partition_name[IBMVFC_MAX_NAME];
	u8 device_name[IBMVFC_MAX_NAME];
	u8 drc_name[IBMVFC_MAX_NAME];
	__be64 reserved2[2];
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_common_svc_parms अणु
	__be16 fcph_version;
	__be16 b2b_credit;
	__be16 features;
	__be16 bb_rcv_sz; /* upper nibble is BB_SC_N */
	__be32 ratov;
	__be32 edtov;
पूर्ण __packed __aligned(4);

काष्ठा ibmvfc_service_parms अणु
	काष्ठा ibmvfc_common_svc_parms common;
	u8 port_name[8];
	u8 node_name[8];
	__be32 class1_parms[4];
	__be32 class2_parms[4];
	__be32 class3_parms[4];
	__be32 obsolete[4];
	__be32 venकरोr_version[4];
	__be32 services_avail[2];
	__be32 ext_len;
	__be32 reserved[30];
	__be32 clk_sync_qos[2];
	__be32 reserved2;
पूर्ण __packed __aligned(4);

काष्ठा ibmvfc_npiv_login_resp अणु
	__be32 version;
	__be16 status;
	__be16 error;
	__be32 flags;
#घोषणा IBMVFC_NATIVE_FC		0x01
	__be32 reserved;
	__be64 capabilities;
#घोषणा IBMVFC_CAN_FLUSH_ON_HALT	0x08
#घोषणा IBMVFC_CAN_SUPPRESS_ABTS	0x10
#घोषणा IBMVFC_MAD_VERSION_CAP		0x20
#घोषणा IBMVFC_HANDLE_VF_WWPN		0x40
#घोषणा IBMVFC_CAN_SUPPORT_CHANNELS	0x80
	__be32 max_cmds;
	__be32 scsi_id_sz;
	__be64 max_dma_len;
	__be64 scsi_id;
	__be64 port_name;
	__be64 node_name;
	__be64 link_speed;
	u8 partition_name[IBMVFC_MAX_NAME];
	u8 device_name[IBMVFC_MAX_NAME];
	u8 port_loc_code[IBMVFC_MAX_NAME];
	u8 drc_name[IBMVFC_MAX_NAME];
	काष्ठा ibmvfc_service_parms service_parms;
	__be64 reserved2;
पूर्ण __packed __aligned(8);

जोड़ ibmvfc_npiv_login_data अणु
	काष्ठा ibmvfc_npiv_login login;
	काष्ठा ibmvfc_npiv_login_resp resp;
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_discover_tarमाला_लो_entry अणु
	__be32 scsi_id;
	__be32 pad;
	__be64 wwpn;
#घोषणा IBMVFC_DISC_TGT_SCSI_ID_MASK	0x00ffffff
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_discover_tarमाला_लो अणु
	काष्ठा ibmvfc_mad_common common;
	काष्ठा srp_direct_buf buffer;
	__be32 flags;
#घोषणा IBMVFC_DISC_TGT_PORT_ID_WWPN_LIST	0x02
	__be16 status;
	__be16 error;
	__be32 bufflen;
	__be32 num_avail;
	__be32 num_written;
	__be64 reserved[2];
पूर्ण __packed __aligned(8);

क्रमागत ibmvfc_fc_reason अणु
	IBMVFC_INVALID_ELS_CMD_CODE	= 0x01,
	IBMVFC_INVALID_VERSION		= 0x02,
	IBMVFC_LOGICAL_ERROR		= 0x03,
	IBMVFC_INVALID_CT_IU_SIZE	= 0x04,
	IBMVFC_LOGICAL_BUSY		= 0x05,
	IBMVFC_PROTOCOL_ERROR		= 0x07,
	IBMVFC_UNABLE_TO_PERFORM_REQ	= 0x09,
	IBMVFC_CMD_NOT_SUPPORTED	= 0x0B,
	IBMVFC_SERVER_NOT_AVAIL		= 0x0D,
	IBMVFC_CMD_IN_PROGRESS		= 0x0E,
	IBMVFC_VENDOR_SPECIFIC		= 0xFF,
पूर्ण;

क्रमागत ibmvfc_fc_type अणु
	IBMVFC_FABRIC_REJECT	= 0x01,
	IBMVFC_PORT_REJECT	= 0x02,
	IBMVFC_LS_REJECT		= 0x03,
	IBMVFC_FABRIC_BUSY	= 0x04,
	IBMVFC_PORT_BUSY		= 0x05,
	IBMVFC_BASIC_REJECT	= 0x06,
पूर्ण;

क्रमागत ibmvfc_gs_explain अणु
	IBMVFC_PORT_NAME_NOT_REG	= 0x02,
पूर्ण;

काष्ठा ibmvfc_port_login अणु
	काष्ठा ibmvfc_mad_common common;
	__be64 scsi_id;
	__be16 reserved;
	__be16 fc_service_class;
	__be32 blksz;
	__be32 hdr_per_blk;
	__be16 status;
	__be16 error;		/* also fc_reason */
	__be16 fc_explain;
	__be16 fc_type;
	__be32 reserved2;
	काष्ठा ibmvfc_service_parms service_parms;
	काष्ठा ibmvfc_service_parms service_parms_change;
	__be64 target_wwpn;
	__be64 reserved3[2];
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_move_login अणु
	काष्ठा ibmvfc_mad_common common;
	__be64 old_scsi_id;
	__be64 new_scsi_id;
	__be64 wwpn;
	__be64 node_name;
	__be32 flags;
#घोषणा IBMVFC_MOVE_LOGIN_IMPLICIT_OLD_FAILED	0x01
#घोषणा IBMVFC_MOVE_LOGIN_IMPLICIT_NEW_FAILED	0x02
#घोषणा IBMVFC_MOVE_LOGIN_PORT_LOGIN_FAILED	0x04
	__be32 reserved;
	काष्ठा ibmvfc_service_parms service_parms;
	काष्ठा ibmvfc_service_parms service_parms_change;
	__be32 reserved2;
	__be16 service_class;
	__be16 vios_flags;
#घोषणा IBMVFC_MOVE_LOGIN_VF_NOT_SENT_ADAPTER	0x01
	__be64 reserved3;
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_prli_svc_parms अणु
	u8 type;
#घोषणा IBMVFC_SCSI_FCP_TYPE		0x08
	u8 type_ext;
	__be16 flags;
#घोषणा IBMVFC_PRLI_ORIG_PA_VALID			0x8000
#घोषणा IBMVFC_PRLI_RESP_PA_VALID			0x4000
#घोषणा IBMVFC_PRLI_EST_IMG_PAIR			0x2000
	__be32 orig_pa;
	__be32 resp_pa;
	__be32 service_parms;
#घोषणा IBMVFC_PRLI_TASK_RETRY			0x00000200
#घोषणा IBMVFC_PRLI_RETRY				0x00000100
#घोषणा IBMVFC_PRLI_DATA_OVERLAY			0x00000040
#घोषणा IBMVFC_PRLI_INITIATOR_FUNC			0x00000020
#घोषणा IBMVFC_PRLI_TARGET_FUNC			0x00000010
#घोषणा IBMVFC_PRLI_READ_FCP_XFER_RDY_DISABLED	0x00000002
#घोषणा IBMVFC_PRLI_WR_FCP_XFER_RDY_DISABLED	0x00000001
पूर्ण __packed __aligned(4);

काष्ठा ibmvfc_process_login अणु
	काष्ठा ibmvfc_mad_common common;
	__be64 scsi_id;
	काष्ठा ibmvfc_prli_svc_parms parms;
	u8 reserved[48];
	__be16 status;
	__be16 error;			/* also fc_reason */
	__be32 reserved2;
	__be64 target_wwpn;
	__be64 reserved3[2];
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_query_tgt अणु
	काष्ठा ibmvfc_mad_common common;
	__be64 wwpn;
	__be64 scsi_id;
	__be16 status;
	__be16 error;
	__be16 fc_explain;
	__be16 fc_type;
	__be64 reserved[2];
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_implicit_logout अणु
	काष्ठा ibmvfc_mad_common common;
	__be64 old_scsi_id;
	__be64 reserved[2];
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_पंचांगf अणु
	काष्ठा ibmvfc_mad_common common;
	__be64 scsi_id;
	काष्ठा scsi_lun lun;
	__be32 flags;
#घोषणा IBMVFC_TMF_ABORT_TASK		0x02
#घोषणा IBMVFC_TMF_ABORT_TASK_SET	0x04
#घोषणा IBMVFC_TMF_LUN_RESET		0x10
#घोषणा IBMVFC_TMF_TGT_RESET		0x20
#घोषणा IBMVFC_TMF_LUA_VALID		0x40
#घोषणा IBMVFC_TMF_SUPPRESS_ABTS	0x80
	__be32 cancel_key;
	__be32 my_cancel_key;
	__be32 pad;
	__be64 target_wwpn;
	__be64 task_tag;
	__be64 reserved[2];
पूर्ण __packed __aligned(8);

क्रमागत ibmvfc_fcp_rsp_info_codes अणु
	RSP_NO_FAILURE		= 0x00,
	RSP_TMF_REJECTED		= 0x04,
	RSP_TMF_FAILED		= 0x05,
	RSP_TMF_INVALID_LUN	= 0x09,
पूर्ण;

काष्ठा ibmvfc_fcp_rsp_info अणु
	u8 reserved[3];
	u8 rsp_code;
	u8 reserved2[4];
पूर्ण __packed __aligned(2);

क्रमागत ibmvfc_fcp_rsp_flags अणु
	FCP_BIDI_RSP			= 0x80,
	FCP_BIDI_READ_RESID_UNDER	= 0x40,
	FCP_BIDI_READ_RESID_OVER	= 0x20,
	FCP_CONF_REQ			= 0x10,
	FCP_RESID_UNDER			= 0x08,
	FCP_RESID_OVER			= 0x04,
	FCP_SNS_LEN_VALID			= 0x02,
	FCP_RSP_LEN_VALID			= 0x01,
पूर्ण;

जोड़ ibmvfc_fcp_rsp_data अणु
	काष्ठा ibmvfc_fcp_rsp_info info;
	u8 sense[SCSI_SENSE_BUFFERSIZE + माप(काष्ठा ibmvfc_fcp_rsp_info)];
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_fcp_rsp अणु
	__be64 reserved;
	__be16 retry_delay_समयr;
	u8 flags;
	u8 scsi_status;
	__be32 fcp_resid;
	__be32 fcp_sense_len;
	__be32 fcp_rsp_len;
	जोड़ ibmvfc_fcp_rsp_data data;
पूर्ण __packed __aligned(8);

क्रमागत ibmvfc_cmd_flags अणु
	IBMVFC_SCATTERLIST	= 0x0001,
	IBMVFC_NO_MEM_DESC	= 0x0002,
	IBMVFC_READ			= 0x0004,
	IBMVFC_WRITE		= 0x0008,
	IBMVFC_TMF			= 0x0080,
	IBMVFC_CLASS_3_ERR	= 0x0100,
पूर्ण;

क्रमागत ibmvfc_fc_task_attr अणु
	IBMVFC_SIMPLE_TASK	= 0x00,
	IBMVFC_HEAD_OF_QUEUE	= 0x01,
	IBMVFC_ORDERED_TASK	= 0x02,
	IBMVFC_ACA_TASK		= 0x04,
पूर्ण;

क्रमागत ibmvfc_fc_पंचांगf_flags अणु
	IBMVFC_ABORT_TASK_SET	= 0x02,
	IBMVFC_LUN_RESET		= 0x10,
	IBMVFC_TARGET_RESET	= 0x20,
पूर्ण;

काष्ठा ibmvfc_fcp_cmd_iu अणु
	काष्ठा scsi_lun lun;
	u8 crn;
	u8 pri_task_attr;
	u8 पंचांगf_flags;
	u8 add_cdb_len;
#घोषणा IBMVFC_RDDATA		0x02
#घोषणा IBMVFC_WRDATA		0x01
	u8 cdb[IBMVFC_MAX_CDB_LEN];
	__be32 xfer_len;
पूर्ण __packed __aligned(4);

काष्ठा ibmvfc_cmd अणु
	__be64 task_tag;
	__be32 frame_type;
	__be32 payload_len;
	__be32 resp_len;
	__be32 adapter_resid;
	__be16 status;
	__be16 error;
	__be16 flags;
	__be16 response_flags;
#घोषणा IBMVFC_ADAPTER_RESID_VALID	0x01
	__be32 cancel_key;
	__be32 exchange_id;
	काष्ठा srp_direct_buf ext_func;
	काष्ठा srp_direct_buf ioba;
	काष्ठा srp_direct_buf resp;
	__be64 correlation;
	__be64 tgt_scsi_id;
	__be64 tag;
	__be64 target_wwpn;
	__be64 reserved3;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा ibmvfc_fcp_cmd_iu iu;
			काष्ठा ibmvfc_fcp_rsp rsp;
		पूर्ण v1;
		काष्ठा अणु
			__be64 reserved4;
			काष्ठा ibmvfc_fcp_cmd_iu iu;
			काष्ठा ibmvfc_fcp_rsp rsp;
		पूर्ण v2;
	पूर्ण;
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_passthru_fc_iu अणु
	__be32 payload[7];
#घोषणा IBMVFC_ADISC	0x52000000
	__be32 response[7];
पूर्ण;

काष्ठा ibmvfc_passthru_iu अणु
	__be64 task_tag;
	__be32 cmd_len;
	__be32 rsp_len;
	__be16 status;
	__be16 error;
	__be32 flags;
#घोषणा IBMVFC_FC_ELS		0x01
#घोषणा IBMVFC_FC_CT_IU		0x02
	__be32 cancel_key;
#घोषणा IBMVFC_PASSTHRU_CANCEL_KEY	0x80000000
#घोषणा IBMVFC_INTERNAL_CANCEL_KEY	0x80000001
	__be32 reserved;
	काष्ठा srp_direct_buf cmd;
	काष्ठा srp_direct_buf rsp;
	__be64 correlation;
	__be64 scsi_id;
	__be64 tag;
	__be64 target_wwpn;
	__be64 reserved2[2];
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_passthru_mad अणु
	काष्ठा ibmvfc_mad_common common;
	काष्ठा srp_direct_buf cmd_ioba;
	काष्ठा ibmvfc_passthru_iu iu;
	काष्ठा ibmvfc_passthru_fc_iu fc_iu;
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_channel_enquiry अणु
	काष्ठा ibmvfc_mad_common common;
	__be32 flags;
#घोषणा IBMVFC_NO_CHANNELS_TO_CRQ_SUPPORT	0x01
#घोषणा IBMVFC_SUPPORT_VARIABLE_SUBQ_MSG	0x02
#घोषणा IBMVFC_NO_N_TO_M_CHANNELS_SUPPORT	0x04
	__be32 num_scsi_subq_channels;
	__be32 num_nvmeof_subq_channels;
	__be32 num_scsi_vas_channels;
	__be32 num_nvmeof_vas_channels;
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_channel_setup_mad अणु
	काष्ठा ibmvfc_mad_common common;
	काष्ठा srp_direct_buf buffer;
पूर्ण __packed __aligned(8);

#घोषणा IBMVFC_MAX_CHANNELS	502

काष्ठा ibmvfc_channel_setup अणु
	__be32 flags;
#घोषणा IBMVFC_CANCEL_CHANNELS		0x01
#घोषणा IBMVFC_USE_BUFFER		0x02
#घोषणा IBMVFC_CHANNELS_CANCELED	0x04
	__be32 reserved;
	__be32 num_scsi_subq_channels;
	__be32 num_nvmeof_subq_channels;
	__be32 num_scsi_vas_channels;
	__be32 num_nvmeof_vas_channels;
	काष्ठा srp_direct_buf buffer;
	__be64 reserved2[5];
	__be64 channel_handles[IBMVFC_MAX_CHANNELS];
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_connection_info अणु
	काष्ठा ibmvfc_mad_common common;
	__be64 inक्रमmation_bits;
#घोषणा IBMVFC_NO_FC_IO_CHANNEL		0x01
#घोषणा IBMVFC_NO_PHYP_VAS		0x02
#घोषणा IBMVFC_NO_PHYP_SUBQ		0x04
#घोषणा IBMVFC_PHYP_DEPRECATED_SUBQ	0x08
#घोषणा IBMVFC_PHYP_PRESERVED_SUBQ	0x10
#घोषणा IBMVFC_PHYP_FULL_SUBQ		0x20
	__be64 reserved[16];
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_trace_start_entry अणु
	u32 xfer_len;
पूर्ण __packed;

काष्ठा ibmvfc_trace_end_entry अणु
	u16 status;
	u16 error;
	u8 fcp_rsp_flags;
	u8 rsp_code;
	u8 scsi_status;
	u8 reserved;
पूर्ण __packed;

काष्ठा ibmvfc_trace_entry अणु
	काष्ठा ibmvfc_event *evt;
	u32 समय;
	u32 scsi_id;
	u32 lun;
	u8 fmt;
	u8 op_code;
	u8 पंचांगf_flags;
	u8 type;
#घोषणा IBMVFC_TRC_START	0x00
#घोषणा IBMVFC_TRC_END		0xff
	जोड़ अणु
		काष्ठा ibmvfc_trace_start_entry start;
		काष्ठा ibmvfc_trace_end_entry end;
	पूर्ण u;
पूर्ण __packed __aligned(8);

क्रमागत ibmvfc_crq_क्रमmats अणु
	IBMVFC_CMD_FORMAT		= 0x01,
	IBMVFC_ASYNC_EVENT	= 0x02,
	IBMVFC_MAD_FORMAT		= 0x04,
पूर्ण;

क्रमागत ibmvfc_async_event अणु
	IBMVFC_AE_ELS_PLOGI		= 0x0001,
	IBMVFC_AE_ELS_LOGO		= 0x0002,
	IBMVFC_AE_ELS_PRLO		= 0x0004,
	IBMVFC_AE_SCN_NPORT		= 0x0008,
	IBMVFC_AE_SCN_GROUP		= 0x0010,
	IBMVFC_AE_SCN_DOMAIN		= 0x0020,
	IBMVFC_AE_SCN_FABRIC		= 0x0040,
	IBMVFC_AE_LINK_UP			= 0x0080,
	IBMVFC_AE_LINK_DOWN		= 0x0100,
	IBMVFC_AE_LINK_DEAD		= 0x0200,
	IBMVFC_AE_HALT			= 0x0400,
	IBMVFC_AE_RESUME			= 0x0800,
	IBMVFC_AE_ADAPTER_FAILED	= 0x1000,
	IBMVFC_AE_FPIN			= 0x2000,
पूर्ण;

काष्ठा ibmvfc_async_desc अणु
	स्थिर अक्षर *desc;
	क्रमागत ibmvfc_async_event ae;
	पूर्णांक log_level;
पूर्ण;

काष्ठा ibmvfc_crq अणु
	अस्थिर u8 valid;
	अस्थिर u8 क्रमmat;
	u8 reserved[6];
	अस्थिर __be64 ioba;
पूर्ण __packed __aligned(8);

काष्ठा ibmvfc_sub_crq अणु
	काष्ठा ibmvfc_crq crq;
	__be64 reserved[2];
पूर्ण __packed __aligned(8);

क्रमागत ibmvfc_ae_link_state अणु
	IBMVFC_AE_LS_LINK_UP		= 0x01,
	IBMVFC_AE_LS_LINK_BOUNCED	= 0x02,
	IBMVFC_AE_LS_LINK_DOWN		= 0x04,
	IBMVFC_AE_LS_LINK_DEAD		= 0x08,
पूर्ण;

क्रमागत ibmvfc_ae_fpin_status अणु
	IBMVFC_AE_FPIN_LINK_CONGESTED	= 0x1,
	IBMVFC_AE_FPIN_PORT_CONGESTED	= 0x2,
	IBMVFC_AE_FPIN_PORT_CLEARED	= 0x3,
	IBMVFC_AE_FPIN_PORT_DEGRADED	= 0x4,
पूर्ण;

काष्ठा ibmvfc_async_crq अणु
	अस्थिर u8 valid;
	u8 link_state;
	u8 fpin_status;
	u8 pad;
	__be32 pad2;
	अस्थिर __be64 event;
	अस्थिर __be64 scsi_id;
	अस्थिर __be64 wwpn;
	अस्थिर __be64 node_name;
	__be64 reserved;
पूर्ण __packed __aligned(8);

जोड़ ibmvfc_iu अणु
	काष्ठा ibmvfc_mad_common mad_common;
	काष्ठा ibmvfc_npiv_login_mad npiv_login;
	काष्ठा ibmvfc_npiv_logout_mad npiv_logout;
	काष्ठा ibmvfc_discover_tarमाला_लो discover_tarमाला_लो;
	काष्ठा ibmvfc_port_login plogi;
	काष्ठा ibmvfc_process_login prli;
	काष्ठा ibmvfc_move_login move_login;
	काष्ठा ibmvfc_query_tgt query_tgt;
	काष्ठा ibmvfc_implicit_logout implicit_logout;
	काष्ठा ibmvfc_पंचांगf पंचांगf;
	काष्ठा ibmvfc_cmd cmd;
	काष्ठा ibmvfc_passthru_mad passthru;
	काष्ठा ibmvfc_channel_enquiry channel_enquiry;
	काष्ठा ibmvfc_channel_setup_mad channel_setup;
	काष्ठा ibmvfc_connection_info connection_info;
पूर्ण __packed __aligned(8);

क्रमागत ibmvfc_target_action अणु
	IBMVFC_TGT_ACTION_NONE = 0,
	IBMVFC_TGT_ACTION_INIT,
	IBMVFC_TGT_ACTION_INIT_WAIT,
	IBMVFC_TGT_ACTION_LOGOUT_RPORT,
	IBMVFC_TGT_ACTION_LOGOUT_RPORT_WAIT,
	IBMVFC_TGT_ACTION_DEL_RPORT,
	IBMVFC_TGT_ACTION_DELETED_RPORT,
	IBMVFC_TGT_ACTION_DEL_AND_LOGOUT_RPORT,
	IBMVFC_TGT_ACTION_LOGOUT_DELETED_RPORT,
पूर्ण;

काष्ठा ibmvfc_target अणु
	काष्ठा list_head queue;
	काष्ठा ibmvfc_host *vhost;
	u64 scsi_id;
	u64 wwpn;
	u64 old_scsi_id;
	काष्ठा fc_rport *rport;
	पूर्णांक target_id;
	क्रमागत ibmvfc_target_action action;
	पूर्णांक need_login;
	पूर्णांक add_rport;
	पूर्णांक init_retries;
	पूर्णांक logo_rcvd;
	u32 cancel_key;
	काष्ठा ibmvfc_service_parms service_parms;
	काष्ठा ibmvfc_service_parms service_parms_change;
	काष्ठा fc_rport_identअगरiers ids;
	व्योम (*job_step) (काष्ठा ibmvfc_target *);
	काष्ठा समयr_list समयr;
	काष्ठा kref kref;
पूर्ण;

/* a unit of work क्रम the hosting partition */
काष्ठा ibmvfc_event अणु
	काष्ठा list_head queue_list;
	काष्ठा list_head cancel;
	काष्ठा ibmvfc_host *vhost;
	काष्ठा ibmvfc_queue *queue;
	काष्ठा ibmvfc_target *tgt;
	काष्ठा scsi_cmnd *cmnd;
	atomic_t मुक्त;
	जोड़ ibmvfc_iu *xfer_iu;
	व्योम (*करोne)(काष्ठा ibmvfc_event *evt);
	व्योम (*_करोne)(काष्ठा ibmvfc_event *evt);
	काष्ठा ibmvfc_crq crq;
	जोड़ ibmvfc_iu iu;
	जोड़ ibmvfc_iu *sync_iu;
	काष्ठा srp_direct_buf *ext_list;
	dma_addr_t ext_list_token;
	काष्ठा completion comp;
	काष्ठा completion *eh_comp;
	काष्ठा समयr_list समयr;
	u16 hwq;
पूर्ण;

/* a pool of event काष्ठाs क्रम use */
काष्ठा ibmvfc_event_pool अणु
	काष्ठा ibmvfc_event *events;
	u32 size;
	जोड़ ibmvfc_iu *iu_storage;
	dma_addr_t iu_token;
पूर्ण;

क्रमागत ibmvfc_msg_fmt अणु
	IBMVFC_CRQ_FMT = 0,
	IBMVFC_ASYNC_FMT,
	IBMVFC_SUB_CRQ_FMT,
पूर्ण;

जोड़ ibmvfc_msgs अणु
	व्योम *handle;
	काष्ठा ibmvfc_crq *crq;
	काष्ठा ibmvfc_async_crq *async;
	काष्ठा ibmvfc_sub_crq *scrq;
पूर्ण;

काष्ठा ibmvfc_queue अणु
	जोड़ ibmvfc_msgs msgs;
	dma_addr_t msg_token;
	क्रमागत ibmvfc_msg_fmt fmt;
	पूर्णांक size, cur;
	spinlock_t _lock;
	spinlock_t *q_lock;

	काष्ठा ibmvfc_event_pool evt_pool;
	काष्ठा list_head sent;
	काष्ठा list_head मुक्त;
	spinlock_t l_lock;

	जोड़ ibmvfc_iu cancel_rsp;

	/* Sub-CRQ fields */
	काष्ठा ibmvfc_host *vhost;
	अचिन्हित दीर्घ cookie;
	अचिन्हित दीर्घ vios_cookie;
	अचिन्हित दीर्घ hw_irq;
	अचिन्हित दीर्घ irq;
	अचिन्हित दीर्घ hwq_id;
	अक्षर name[32];
पूर्ण;

काष्ठा ibmvfc_scsi_channels अणु
	काष्ठा ibmvfc_queue *scrqs;
	अचिन्हित पूर्णांक active_queues;
पूर्ण;

क्रमागत ibmvfc_host_action अणु
	IBMVFC_HOST_ACTION_NONE = 0,
	IBMVFC_HOST_ACTION_RESET,
	IBMVFC_HOST_ACTION_REENABLE,
	IBMVFC_HOST_ACTION_LOGO,
	IBMVFC_HOST_ACTION_LOGO_WAIT,
	IBMVFC_HOST_ACTION_INIT,
	IBMVFC_HOST_ACTION_INIT_WAIT,
	IBMVFC_HOST_ACTION_QUERY,
	IBMVFC_HOST_ACTION_QUERY_TGTS,
	IBMVFC_HOST_ACTION_TGT_DEL,
	IBMVFC_HOST_ACTION_ALLOC_TGTS,
	IBMVFC_HOST_ACTION_TGT_INIT,
	IBMVFC_HOST_ACTION_TGT_DEL_FAILED,
पूर्ण;

क्रमागत ibmvfc_host_state अणु
	IBMVFC_NO_CRQ = 0,
	IBMVFC_INITIALIZING,
	IBMVFC_ACTIVE,
	IBMVFC_HALTED,
	IBMVFC_LINK_DOWN,
	IBMVFC_LINK_DEAD,
	IBMVFC_HOST_OFFLINE,
पूर्ण;

काष्ठा ibmvfc_host अणु
	अक्षर name[8];
	काष्ठा list_head queue;
	काष्ठा Scsi_Host *host;
	क्रमागत ibmvfc_host_state state;
	क्रमागत ibmvfc_host_action action;
#घोषणा IBMVFC_NUM_TRACE_INDEX_BITS		8
#घोषणा IBMVFC_NUM_TRACE_ENTRIES		(1 << IBMVFC_NUM_TRACE_INDEX_BITS)
#घोषणा IBMVFC_TRACE_INDEX_MASK			(IBMVFC_NUM_TRACE_ENTRIES - 1)
#घोषणा IBMVFC_TRACE_SIZE	(माप(काष्ठा ibmvfc_trace_entry) * IBMVFC_NUM_TRACE_ENTRIES)
	काष्ठा ibmvfc_trace_entry *trace;
	atomic_t trace_index;
	पूर्णांक num_tarमाला_लो;
	काष्ठा list_head tarमाला_लो;
	काष्ठा list_head purge;
	काष्ठा device *dev;
	काष्ठा dma_pool *sg_pool;
	mempool_t *tgt_pool;
	काष्ठा ibmvfc_queue crq;
	काष्ठा ibmvfc_queue async_crq;
	काष्ठा ibmvfc_scsi_channels scsi_scrqs;
	काष्ठा ibmvfc_npiv_login login_info;
	जोड़ ibmvfc_npiv_login_data *login_buf;
	dma_addr_t login_buf_dma;
	काष्ठा ibmvfc_channel_setup *channel_setup_buf;
	dma_addr_t channel_setup_dma;
	पूर्णांक disc_buf_sz;
	पूर्णांक log_level;
	काष्ठा ibmvfc_discover_tarमाला_लो_entry *disc_buf;
	काष्ठा mutex passthru_mutex;
	पूर्णांक max_vios_scsi_channels;
	पूर्णांक task_set;
	पूर्णांक init_retries;
	पूर्णांक discovery_thपढ़ोs;
	पूर्णांक पात_thपढ़ोs;
	पूर्णांक client_migrated;
	पूर्णांक reinit;
	पूर्णांक delay_init;
	पूर्णांक scan_complete;
	पूर्णांक logged_in;
	पूर्णांक mq_enabled;
	पूर्णांक using_channels;
	पूर्णांक करो_enquiry;
	पूर्णांक client_scsi_channels;
	पूर्णांक पातing_passthru;
	पूर्णांक events_to_log;
#घोषणा IBMVFC_AE_LINKUP	0x0001
#घोषणा IBMVFC_AE_LINKDOWN	0x0002
#घोषणा IBMVFC_AE_RSCN		0x0004
	dma_addr_t disc_buf_dma;
	अचिन्हित पूर्णांक partition_number;
	अक्षर partition_name[97];
	व्योम (*job_step) (काष्ठा ibmvfc_host *);
	काष्ठा task_काष्ठा *work_thपढ़ो;
	काष्ठा tasklet_काष्ठा tasklet;
	काष्ठा work_काष्ठा rport_add_work_q;
	रुको_queue_head_t init_रुको_q;
	रुको_queue_head_t work_रुको_q;
पूर्ण;

#घोषणा DBG_CMD(CMD) करो अणु अगर (ibmvfc_debug) CMD; पूर्ण जबतक (0)

#घोषणा tgt_dbg(t, fmt, ...)			\
	DBG_CMD(dev_info((t)->vhost->dev, "%llX: " fmt, (t)->scsi_id, ##__VA_ARGS__))

#घोषणा tgt_info(t, fmt, ...)		\
	dev_info((t)->vhost->dev, "%llX: " fmt, (t)->scsi_id, ##__VA_ARGS__)

#घोषणा tgt_err(t, fmt, ...)		\
	dev_err((t)->vhost->dev, "%llX: " fmt, (t)->scsi_id, ##__VA_ARGS__)

#घोषणा tgt_log(t, level, fmt, ...) \
	करो अणु \
		अगर ((t)->vhost->log_level >= level) \
			tgt_err(t, fmt, ##__VA_ARGS__); \
	पूर्ण जबतक (0)

#घोषणा ibmvfc_dbg(vhost, ...) \
	DBG_CMD(dev_info((vhost)->dev, ##__VA_ARGS__))

#घोषणा ibmvfc_log(vhost, level, ...) \
	करो अणु \
		अगर ((vhost)->log_level >= level) \
			dev_err((vhost)->dev, ##__VA_ARGS__); \
	पूर्ण जबतक (0)

#घोषणा ENTER DBG_CMD(prपूर्णांकk(KERN_INFO IBMVFC_NAME": Entering %s\n", __func__))
#घोषणा LEAVE DBG_CMD(prपूर्णांकk(KERN_INFO IBMVFC_NAME": Leaving %s\n", __func__))

#अगर_घोषित CONFIG_SCSI_IBMVFC_TRACE
#घोषणा ibmvfc_create_trace_file(kobj, attr) sysfs_create_bin_file(kobj, attr)
#घोषणा ibmvfc_हटाओ_trace_file(kobj, attr) sysfs_हटाओ_bin_file(kobj, attr)
#अन्यथा
#घोषणा ibmvfc_create_trace_file(kobj, attr) 0
#घोषणा ibmvfc_हटाओ_trace_file(kobj, attr) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर
