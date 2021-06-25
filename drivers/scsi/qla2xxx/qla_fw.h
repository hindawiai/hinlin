<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#अगर_अघोषित __QLA_FW_H
#घोषणा __QLA_FW_H

#समावेश <linux/nvme.h>
#समावेश <linux/nvme-fc.h>

#समावेश "qla_dsd.h"

#घोषणा MBS_CHECKSUM_ERROR	0x4010
#घोषणा MBS_INVALID_PRODUCT_KEY	0x4020

/*
 * Firmware Options.
 */
#घोषणा FO1_ENABLE_PUREX	BIT_10
#घोषणा FO1_DISABLE_LED_CTRL	BIT_6
#घोषणा FO1_ENABLE_8016		BIT_0
#घोषणा FO2_ENABLE_SEL_CLASS2	BIT_5
#घोषणा FO3_NO_ABTS_ON_LINKDOWN	BIT_14
#घोषणा FO3_HOLD_STS_IOCB	BIT_12

/*
 * Port Database काष्ठाure definition क्रम ISP 24xx.
 */
#घोषणा PDO_FORCE_ADISC		BIT_1
#घोषणा PDO_FORCE_PLOGI		BIT_0

काष्ठा buffer_credit_24xx अणु
	u32 parameter[28];
पूर्ण;

#घोषणा	PORT_DATABASE_24XX_SIZE		64
काष्ठा port_database_24xx अणु
	uपूर्णांक16_t flags;
#घोषणा PDF_TASK_RETRY_ID	BIT_14
#घोषणा PDF_FC_TAPE		BIT_7
#घोषणा PDF_ACK0_CAPABLE	BIT_6
#घोषणा PDF_FCP2_CONF		BIT_5
#घोषणा PDF_CLASS_2		BIT_4
#घोषणा PDF_HARD_ADDR		BIT_1

	/*
	 * क्रम NVMe, the login_state field has been
	 * split पूर्णांकo nibbles.
	 * The lower nibble is क्रम FCP.
	 * The upper nibble is क्रम NVMe.
	 */
	uपूर्णांक8_t current_login_state;
	uपूर्णांक8_t last_login_state;
#घोषणा PDS_PLOGI_PENDING	0x03
#घोषणा PDS_PLOGI_COMPLETE	0x04
#घोषणा PDS_PRLI_PENDING	0x05
#घोषणा PDS_PRLI_COMPLETE	0x06
#घोषणा PDS_PORT_UNAVAILABLE	0x07
#घोषणा PDS_PRLO_PENDING	0x09
#घोषणा PDS_LOGO_PENDING	0x11
#घोषणा PDS_PRLI2_PENDING	0x12

	uपूर्णांक8_t hard_address[3];
	uपूर्णांक8_t reserved_1;

	uपूर्णांक8_t port_id[3];
	uपूर्णांक8_t sequence_id;

	uपूर्णांक16_t port_समयr;

	uपूर्णांक16_t nport_handle;			/* N_PORT handle. */

	uपूर्णांक16_t receive_data_size;
	uपूर्णांक16_t reserved_2;

	uपूर्णांक8_t prli_svc_param_word_0[2];	/* Big endian */
						/* Bits 15-0 of word 0 */
	uपूर्णांक8_t prli_svc_param_word_3[2];	/* Big endian */
						/* Bits 15-0 of word 3 */

	uपूर्णांक8_t port_name[WWN_SIZE];
	uपूर्णांक8_t node_name[WWN_SIZE];

	uपूर्णांक8_t reserved_3[4];
	uपूर्णांक16_t prli_nvme_svc_param_word_0;	/* Bits 15-0 of word 0 */
	uपूर्णांक16_t prli_nvme_svc_param_word_3;	/* Bits 15-0 of word 3 */
	uपूर्णांक16_t nvme_first_burst_size;
	uपूर्णांक8_t reserved_4[14];
पूर्ण;

/*
 * MB 75h वापसs a list of DB entries similar to port_database_24xx(64B).
 * However, in this हाल it वापसs 1st 40 bytes.
 */
काष्ठा get_name_list_extended अणु
	__le16 flags;
	u8 current_login_state;
	u8 last_login_state;
	u8 hard_address[3];
	u8 reserved_1;
	u8 port_id[3];
	u8 sequence_id;
	__le16 port_समयr;
	__le16 nport_handle;			/* N_PORT handle. */
	__le16 receive_data_size;
	__le16 reserved_2;

	/* PRLI SVC Param are Big endian */
	u8 prli_svc_param_word_0[2]; /* Bits 15-0 of word 0 */
	u8 prli_svc_param_word_3[2]; /* Bits 15-0 of word 3 */
	u8 port_name[WWN_SIZE];
	u8 node_name[WWN_SIZE];
पूर्ण;

/* MB 75h: This is the लघु version of the database */
काष्ठा get_name_list अणु
	u8 port_node_name[WWN_SIZE]; /* B7 most sig, B0 least sig */
	__le16 nport_handle;
	u8 reserved;
पूर्ण;

काष्ठा vp_database_24xx अणु
	uपूर्णांक16_t vp_status;
	uपूर्णांक8_t  options;
	uपूर्णांक8_t  id;
	uपूर्णांक8_t  port_name[WWN_SIZE];
	uपूर्णांक8_t  node_name[WWN_SIZE];
	uपूर्णांक16_t port_id_low;
	uपूर्णांक16_t port_id_high;
पूर्ण;

काष्ठा nvram_24xx अणु
	/* NVRAM header. */
	uपूर्णांक8_t id[4];
	__le16	nvram_version;
	uपूर्णांक16_t reserved_0;

	/* Firmware Initialization Control Block. */
	__le16	version;
	uपूर्णांक16_t reserved_1;
	__le16	frame_payload_size;
	__le16	execution_throttle;
	__le16	exchange_count;
	__le16	hard_address;

	uपूर्णांक8_t port_name[WWN_SIZE];
	uपूर्णांक8_t node_name[WWN_SIZE];

	__le16	login_retry_count;
	__le16	link_करोwn_on_nos;
	__le16	पूर्णांकerrupt_delay_समयr;
	__le16	login_समयout;

	__le32	firmware_options_1;
	__le32	firmware_options_2;
	__le32	firmware_options_3;

	/* Offset 56. */

	/*
	 * BIT 0     = Control Enable
	 * BIT 1-15  =
	 *
	 * BIT 0-7   = Reserved
	 * BIT 8-10  = Output Swing 1G
	 * BIT 11-13 = Output Emphasis 1G
	 * BIT 14-15 = Reserved
	 *
	 * BIT 0-7   = Reserved
	 * BIT 8-10  = Output Swing 2G
	 * BIT 11-13 = Output Emphasis 2G
	 * BIT 14-15 = Reserved
	 *
	 * BIT 0-7   = Reserved
	 * BIT 8-10  = Output Swing 4G
	 * BIT 11-13 = Output Emphasis 4G
	 * BIT 14-15 = Reserved
	 */
	__le16	seriallink_options[4];

	uपूर्णांक16_t reserved_2[16];

	/* Offset 96. */
	uपूर्णांक16_t reserved_3[16];

	/* PCIe table entries. */
	uपूर्णांक16_t reserved_4[16];

	/* Offset 160. */
	uपूर्णांक16_t reserved_5[16];

	/* Offset 192. */
	uपूर्णांक16_t reserved_6[16];

	/* Offset 224. */
	uपूर्णांक16_t reserved_7[16];

	/*
	 * BIT 0  = Enable spinup delay
	 * BIT 1  = Disable BIOS
	 * BIT 2  = Enable Memory Map BIOS
	 * BIT 3  = Enable Selectable Boot
	 * BIT 4  = Disable RISC code load
	 * BIT 5  = Disable Serdes
	 * BIT 6  =
	 * BIT 7  =
	 *
	 * BIT 8  =
	 * BIT 9  =
	 * BIT 10 = Enable lip full login
	 * BIT 11 = Enable target reset
	 * BIT 12 =
	 * BIT 13 =
	 * BIT 14 =
	 * BIT 15 = Enable alternate WWN
	 *
	 * BIT 16-31 =
	 */
	__le32	host_p;

	uपूर्णांक8_t alternate_port_name[WWN_SIZE];
	uपूर्णांक8_t alternate_node_name[WWN_SIZE];

	uपूर्णांक8_t boot_port_name[WWN_SIZE];
	__le16	boot_lun_number;
	uपूर्णांक16_t reserved_8;

	uपूर्णांक8_t alt1_boot_port_name[WWN_SIZE];
	__le16	alt1_boot_lun_number;
	uपूर्णांक16_t reserved_9;

	uपूर्णांक8_t alt2_boot_port_name[WWN_SIZE];
	__le16	alt2_boot_lun_number;
	uपूर्णांक16_t reserved_10;

	uपूर्णांक8_t alt3_boot_port_name[WWN_SIZE];
	__le16	alt3_boot_lun_number;
	uपूर्णांक16_t reserved_11;

	/*
	 * BIT 0 = Selective Login
	 * BIT 1 = Alt-Boot Enable
	 * BIT 2 = Reserved
	 * BIT 3 = Boot Order List
	 * BIT 4 = Reserved
	 * BIT 5 = Selective LUN
	 * BIT 6 = Reserved
	 * BIT 7-31 =
	 */
	__le32	efi_parameters;

	uपूर्णांक8_t reset_delay;
	uपूर्णांक8_t reserved_12;
	uपूर्णांक16_t reserved_13;

	__le16	boot_id_number;
	uपूर्णांक16_t reserved_14;

	__le16	max_luns_per_target;
	uपूर्णांक16_t reserved_15;

	__le16	port_करोwn_retry_count;
	__le16	link_करोwn_समयout;

	/* FCode parameters. */
	__le16	fcode_parameter;

	uपूर्णांक16_t reserved_16[3];

	/* Offset 352. */
	uपूर्णांक8_t prev_drv_ver_major;
	uपूर्णांक8_t prev_drv_ver_submajob;
	uपूर्णांक8_t prev_drv_ver_minor;
	uपूर्णांक8_t prev_drv_ver_subminor;

	__le16	prev_bios_ver_major;
	__le16	prev_bios_ver_minor;

	__le16	prev_efi_ver_major;
	__le16	prev_efi_ver_minor;

	__le16	prev_fw_ver_major;
	uपूर्णांक8_t prev_fw_ver_minor;
	uपूर्णांक8_t prev_fw_ver_subminor;

	uपूर्णांक16_t reserved_17[8];

	/* Offset 384. */
	uपूर्णांक16_t reserved_18[16];

	/* Offset 416. */
	uपूर्णांक16_t reserved_19[16];

	/* Offset 448. */
	uपूर्णांक16_t reserved_20[16];

	/* Offset 480. */
	uपूर्णांक8_t model_name[16];

	uपूर्णांक16_t reserved_21[2];

	/* Offset 500. */
	/* HW Parameter Block. */
	uपूर्णांक16_t pcie_table_sig;
	uपूर्णांक16_t pcie_table_offset;

	uपूर्णांक16_t subप्रणाली_venकरोr_id;
	uपूर्णांक16_t subप्रणाली_device_id;

	__le32	checksum;
पूर्ण;

/*
 * ISP Initialization Control Block.
 * Little endian except where noted.
 */
#घोषणा	ICB_VERSION 1
काष्ठा init_cb_24xx अणु
	__le16	version;
	uपूर्णांक16_t reserved_1;

	__le16	frame_payload_size;
	__le16	execution_throttle;
	__le16	exchange_count;

	__le16	hard_address;

	uपूर्णांक8_t port_name[WWN_SIZE];		/* Big endian. */
	uपूर्णांक8_t node_name[WWN_SIZE];		/* Big endian. */

	__le16	response_q_inpoपूर्णांकer;
	__le16	request_q_outpoपूर्णांकer;

	__le16	login_retry_count;

	__le16	prio_request_q_outpoपूर्णांकer;

	__le16	response_q_length;
	__le16	request_q_length;

	__le16	link_करोwn_on_nos;		/* Milliseconds. */

	__le16	prio_request_q_length;

	__le64	 request_q_address __packed;
	__le64	 response_q_address __packed;
	__le64	 prio_request_q_address __packed;

	__le16	msix;
	__le16	msix_atio;
	uपूर्णांक8_t reserved_2[4];

	__le16	atio_q_inpoपूर्णांकer;
	__le16	atio_q_length;
	__le64	atio_q_address __packed;

	__le16	पूर्णांकerrupt_delay_समयr;		/* 100us increments. */
	__le16	login_समयout;

	/*
	 * BIT 0  = Enable Hard Loop Id
	 * BIT 1  = Enable Fairness
	 * BIT 2  = Enable Full-Duplex
	 * BIT 3  = Reserved
	 * BIT 4  = Enable Target Mode
	 * BIT 5  = Disable Initiator Mode
	 * BIT 6  = Acquire FA-WWN
	 * BIT 7  = Enable D-port Diagnostics
	 *
	 * BIT 8  = Reserved
	 * BIT 9  = Non Participating LIP
	 * BIT 10 = Descending Loop ID Search
	 * BIT 11 = Acquire Loop ID in LIPA
	 * BIT 12 = Reserved
	 * BIT 13 = Full Login after LIP
	 * BIT 14 = Node Name Option
	 * BIT 15-31 = Reserved
	 */
	__le32	firmware_options_1;

	/*
	 * BIT 0  = Operation Mode bit 0
	 * BIT 1  = Operation Mode bit 1
	 * BIT 2  = Operation Mode bit 2
	 * BIT 3  = Operation Mode bit 3
	 * BIT 4  = Connection Options bit 0
	 * BIT 5  = Connection Options bit 1
	 * BIT 6  = Connection Options bit 2
	 * BIT 7  = Enable Non part on LIHA failure
	 *
	 * BIT 8  = Enable Class 2
	 * BIT 9  = Enable ACK0
	 * BIT 10 = Reserved
	 * BIT 11 = Enable FC-SP Security
	 * BIT 12 = FC Tape Enable
	 * BIT 13 = Reserved
	 * BIT 14 = Enable Target PRLI Control
	 * BIT 15-31 = Reserved
	 */
	__le32	firmware_options_2;

	/*
	 * BIT 0  = Reserved
	 * BIT 1  = Soft ID only
	 * BIT 2  = Reserved
	 * BIT 3  = Reserved
	 * BIT 4  = FCP RSP Payload bit 0
	 * BIT 5  = FCP RSP Payload bit 1
	 * BIT 6  = Enable Receive Out-of-Order data frame handling
	 * BIT 7  = Disable Automatic PLOGI on Local Loop
	 *
	 * BIT 8  = Reserved
	 * BIT 9  = Enable Out-of-Order FCP_XFER_RDY relative offset handling
	 * BIT 10 = Reserved
	 * BIT 11 = Reserved
	 * BIT 12 = Reserved
	 * BIT 13 = Data Rate bit 0
	 * BIT 14 = Data Rate bit 1
	 * BIT 15 = Data Rate bit 2
	 * BIT 16 = Enable 75 ohm Termination Select
	 * BIT 17-28 = Reserved
	 * BIT 29 = Enable response queue 0 in index shaकरोwing
	 * BIT 30 = Enable request queue 0 out index shaकरोwing
	 * BIT 31 = Reserved
	 */
	__le32	firmware_options_3;
	__le16	 qos;
	__le16	 rid;
	uपूर्णांक8_t  reserved_3[20];
पूर्ण;

/*
 * ISP queue - command entry काष्ठाure definition.
 */
#घोषणा COMMAND_BIसूचीECTIONAL 0x75
काष्ठा cmd_bidir अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined */
	uपूर्णांक8_t entry_status;		/* Entry status. */

	uपूर्णांक32_t handle;		/* System handle. */

	__le16	nport_handle;		/* N_PORT handle. */

	__le16	समयout;		/* Command समयout. */

	__le16	wr_dseg_count;		/* Write Data segment count. */
	__le16	rd_dseg_count;		/* Read Data segment count. */

	काष्ठा scsi_lun lun;		/* FCP LUN (BE). */

	__le16	control_flags;		/* Control flags. */
#घोषणा BD_WRAP_BACK			BIT_3
#घोषणा BD_READ_DATA			BIT_1
#घोषणा BD_WRITE_DATA			BIT_0

	__le16	fcp_cmnd_dseg_len;		/* Data segment length. */
	__le64	 fcp_cmnd_dseg_address __packed;/* Data segment address. */

	uपूर्णांक16_t reserved[2];			/* Reserved */

	__le32	rd_byte_count;			/* Total Byte count Read. */
	__le32	wr_byte_count;			/* Total Byte count ग_लिखो. */

	uपूर्णांक8_t port_id[3];			/* PortID of destination port.*/
	uपूर्णांक8_t vp_index;

	काष्ठा dsd64 fcp_dsd;
पूर्ण;

#घोषणा COMMAND_TYPE_6	0x48		/* Command Type 6 entry */
काष्ठा cmd_type_6 अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */

	__le16	nport_handle;		/* N_PORT handle. */
	__le16	समयout;		/* Command समयout. */

	__le16	dseg_count;		/* Data segment count. */

	__le16	fcp_rsp_dsd_len;	/* FCP_RSP DSD length. */

	काष्ठा scsi_lun lun;		/* FCP LUN (BE). */

	__le16	control_flags;		/* Control flags. */
#घोषणा CF_DIF_SEG_DESCR_ENABLE		BIT_3
#घोषणा CF_DATA_SEG_DESCR_ENABLE	BIT_2
#घोषणा CF_READ_DATA			BIT_1
#घोषणा CF_WRITE_DATA			BIT_0

	__le16	fcp_cmnd_dseg_len;	/* Data segment length. */
					/* Data segment address. */
	__le64	 fcp_cmnd_dseg_address __packed;
					/* Data segment address. */
	__le64	 fcp_rsp_dseg_address __packed;

	__le32	byte_count;		/* Total byte count. */

	uपूर्णांक8_t port_id[3];		/* PortID of destination port. */
	uपूर्णांक8_t vp_index;

	काष्ठा dsd64 fcp_dsd;
पूर्ण;

#घोषणा COMMAND_TYPE_7	0x18		/* Command Type 7 entry */
काष्ठा cmd_type_7 अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */

	__le16	nport_handle;		/* N_PORT handle. */
	__le16	समयout;		/* Command समयout. */
#घोषणा FW_MAX_TIMEOUT		0x1999

	__le16	dseg_count;		/* Data segment count. */
	uपूर्णांक16_t reserved_1;

	काष्ठा scsi_lun lun;		/* FCP LUN (BE). */

	__le16	task_mgmt_flags;	/* Task management flags. */
#घोषणा TMF_CLEAR_ACA		BIT_14
#घोषणा TMF_TARGET_RESET	BIT_13
#घोषणा TMF_LUN_RESET		BIT_12
#घोषणा TMF_CLEAR_TASK_SET	BIT_10
#घोषणा TMF_ABORT_TASK_SET	BIT_9
#घोषणा TMF_DSD_LIST_ENABLE	BIT_2
#घोषणा TMF_READ_DATA		BIT_1
#घोषणा TMF_WRITE_DATA		BIT_0

	uपूर्णांक8_t task;
#घोषणा TSK_SIMPLE		0
#घोषणा TSK_HEAD_OF_QUEUE	1
#घोषणा TSK_ORDERED		2
#घोषणा TSK_ACA			4
#घोषणा TSK_UNTAGGED		5

	uपूर्णांक8_t crn;

	uपूर्णांक8_t fcp_cdb[MAX_CMDSZ]; 	/* SCSI command words. */
	__le32	byte_count;		/* Total byte count. */

	uपूर्णांक8_t port_id[3];		/* PortID of destination port. */
	uपूर्णांक8_t vp_index;

	काष्ठा dsd64 dsd;
पूर्ण;

#घोषणा COMMAND_TYPE_CRC_2	0x6A	/* Command Type CRC_2 (Type 6)
					 * (T10-DIF) */
काष्ठा cmd_type_crc_2 अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */

	__le16	nport_handle;		/* N_PORT handle. */
	__le16	समयout;		/* Command समयout. */

	__le16	dseg_count;		/* Data segment count. */

	__le16	fcp_rsp_dseg_len;	/* FCP_RSP DSD length. */

	काष्ठा scsi_lun lun;		/* FCP LUN (BE). */

	__le16	control_flags;		/* Control flags. */

	__le16	fcp_cmnd_dseg_len;	/* Data segment length. */
	__le64	 fcp_cmnd_dseg_address __packed;
					/* Data segment address. */
	__le64	 fcp_rsp_dseg_address __packed;

	__le32	byte_count;		/* Total byte count. */

	uपूर्णांक8_t port_id[3];		/* PortID of destination port. */
	uपूर्णांक8_t vp_index;

	__le64	 crc_context_address __packed;	/* Data segment address. */
	__le16	crc_context_len;		/* Data segment length. */
	uपूर्णांक16_t reserved_1;			/* MUST be set to 0. */
पूर्ण;


/*
 * ISP queue - status entry काष्ठाure definition.
 */
#घोषणा	STATUS_TYPE	0x03		/* Status entry. */
काष्ठा sts_entry_24xx अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */

	__le16	comp_status;		/* Completion status. */
	__le16	ox_id;			/* OX_ID used by the firmware. */

	__le32	residual_len;		/* FW calc residual transfer length. */

	जोड़ अणु
		__le16 reserved_1;
		__le16	nvme_rsp_pyld_len;
	पूर्ण;

	__le16	state_flags;		/* State flags. */
#घोषणा SF_TRANSFERRED_DATA	BIT_11
#घोषणा SF_NVME_ERSP            BIT_6
#घोषणा SF_FCP_RSP_DMA		BIT_0

	__le16	status_qualअगरier;
	__le16	scsi_status;		/* SCSI status. */
#घोषणा SS_CONFIRMATION_REQ		BIT_12

	__le32	rsp_residual_count;	/* FCP RSP residual count. */

	__le32	sense_len;		/* FCP SENSE length. */

	जोड़ अणु
		काष्ठा अणु
			__le32	rsp_data_len;	/* FCP response data length  */
			uपूर्णांक8_t data[28];	/* FCP rsp/sense inक्रमmation */
		पूर्ण;
		काष्ठा nvme_fc_ersp_iu nvme_ersp;
		uपूर्णांक8_t nvme_ersp_data[32];
	पूर्ण;

	/*
	 * If DIF Error is set in comp_status, these additional fields are
	 * defined:
	 *
	 * !!! NOTE: Firmware sends expected/actual DIF data in big endian
	 * क्रमmat; but all of the "data" field माला_लो swab32-d in the beginning
	 * of qla2x00_status_entry().
	 *
	 * &data[10] : uपूर्णांक8_t report_runt_bg[2];	- computed guard
	 * &data[12] : uपूर्णांक8_t actual_dअगर[8];		- DIF Data received
	 * &data[20] : uपूर्णांक8_t expected_dअगर[8];		- DIF Data computed
	*/
पूर्ण;


/*
 * Status entry completion status
 */
#घोषणा CS_DATA_REASSEMBLY_ERROR 0x11	/* Data Reassembly Error.. */
#घोषणा CS_ABTS_BY_TARGET	0x13	/* Target send ABTS to पात IOCB. */
#घोषणा CS_FW_RESOURCE		0x2C	/* Firmware Resource Unavailable. */
#घोषणा CS_TASK_MGMT_OVERRUN	0x30	/* Task management overrun (8+). */
#घोषणा CS_ABORT_BY_TARGET	0x47	/* Abort By Target. */

/*
 * ISP queue - marker entry काष्ठाure definition.
 */
#घोषणा MARKER_TYPE	0x04		/* Marker entry. */
काष्ठा mrk_entry_24xx अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t handle_count;		/* Handle count. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */

	__le16	nport_handle;		/* N_PORT handle. */

	uपूर्णांक8_t modअगरier;		/* Modअगरier (7-0). */
#घोषणा MK_SYNC_ID_LUN	0		/* Synchronize ID/LUN */
#घोषणा MK_SYNC_ID	1		/* Synchronize ID */
#घोषणा MK_SYNC_ALL	2		/* Synchronize all ID/LUN */
	uपूर्णांक8_t reserved_1;

	uपूर्णांक8_t reserved_2;
	uपूर्णांक8_t vp_index;

	uपूर्णांक16_t reserved_3;

	uपूर्णांक8_t lun[8];			/* FCP LUN (BE). */
	uपूर्णांक8_t reserved_4[40];
पूर्ण;

/*
 * ISP queue - CT Pass-Through entry काष्ठाure definition.
 */
#घोषणा CT_IOCB_TYPE		0x29	/* CT Pass-Through IOCB entry */
काष्ठा ct_entry_24xx अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System Defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */

	__le16	comp_status;		/* Completion status. */

	__le16	nport_handle;		/* N_PORT handle. */

	__le16	cmd_dsd_count;

	uपूर्णांक8_t vp_index;
	uपूर्णांक8_t reserved_1;

	__le16	समयout;		/* Command समयout. */
	uपूर्णांक16_t reserved_2;

	__le16	rsp_dsd_count;

	uपूर्णांक8_t reserved_3[10];

	__le32	rsp_byte_count;
	__le32	cmd_byte_count;

	काष्ठा dsd64 dsd[2];
पूर्ण;

#घोषणा PURX_ELS_HEADER_SIZE	0x18

/*
 * ISP queue - PUREX IOCB entry काष्ठाure definition
 */
#घोषणा PUREX_IOCB_TYPE		0x51	/* CT Pass Through IOCB entry */
काष्ठा purex_entry_24xx अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	__le16	reserved1;
	uपूर्णांक8_t vp_idx;
	uपूर्णांक8_t reserved2;

	__le16	status_flags;
	__le16	nport_handle;

	__le16	frame_size;
	__le16	trunc_frame_size;

	__le32	rx_xchg_addr;

	uपूर्णांक8_t d_id[3];
	uपूर्णांक8_t r_ctl;

	uपूर्णांक8_t s_id[3];
	uपूर्णांक8_t cs_ctl;

	uपूर्णांक8_t f_ctl[3];
	uपूर्णांक8_t type;

	__le16	seq_cnt;
	uपूर्णांक8_t df_ctl;
	uपूर्णांक8_t seq_id;

	__le16	rx_id;
	__le16	ox_id;
	__le32	param;

	uपूर्णांक8_t els_frame_payload[20];
पूर्ण;

/*
 * ISP queue - ELS Pass-Through entry काष्ठाure definition.
 */
#घोषणा ELS_IOCB_TYPE		0x53	/* ELS Pass-Through IOCB entry */
काष्ठा els_entry_24xx अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System Defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */

	__le16	comp_status;		/* response only */
	__le16	nport_handle;

	__le16	tx_dsd_count;

	uपूर्णांक8_t vp_index;
	uपूर्णांक8_t sof_type;
#घोषणा EST_SOFI3		(1 << 4)
#घोषणा EST_SOFI2		(3 << 4)

	__le32	rx_xchg_address;	/* Receive exchange address. */
	__le16	rx_dsd_count;

	uपूर्णांक8_t opcode;
	uपूर्णांक8_t reserved_2;

	uपूर्णांक8_t d_id[3];
	uपूर्णांक8_t s_id[3];

	__le16	control_flags;		/* Control flags. */
#घोषणा ECF_PAYLOAD_DESCR_MASK	(BIT_15|BIT_14|BIT_13)
#घोषणा EPD_ELS_COMMAND		(0 << 13)
#घोषणा EPD_ELS_ACC		(1 << 13)
#घोषणा EPD_ELS_RJT		(2 << 13)
#घोषणा EPD_RX_XCHG		(3 << 13)
#घोषणा ECF_CLR_PASSTHRU_PEND	BIT_12
#घोषणा ECF_INCL_FRAME_HDR	BIT_11

	जोड़ अणु
		काष्ठा अणु
			__le32	 rx_byte_count;
			__le32	 tx_byte_count;

			__le64	 tx_address __packed;	/* DSD 0 address. */
			__le32	 tx_len;		/* DSD 0 length. */

			__le64	 rx_address __packed;	/* DSD 1 address. */
			__le32	 rx_len;		/* DSD 1 length. */
		पूर्ण;
		काष्ठा अणु
			__le32	total_byte_count;
			__le32	error_subcode_1;
			__le32	error_subcode_2;
			__le32	error_subcode_3;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा els_sts_entry_24xx अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System Defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	__le32	handle;		/* System handle. */

	__le16	comp_status;

	__le16	nport_handle;		/* N_PORT handle. */

	__le16	reserved_1;

	uपूर्णांक8_t vp_index;
	uपूर्णांक8_t sof_type;

	__le32	rx_xchg_address;	/* Receive exchange address. */
	__le16	reserved_2;

	uपूर्णांक8_t opcode;
	uपूर्णांक8_t reserved_3;

	uपूर्णांक8_t d_id[3];
	uपूर्णांक8_t s_id[3];

	__le16	control_flags;		/* Control flags. */
	__le32	total_byte_count;
	__le32	error_subcode_1;
	__le32	error_subcode_2;
	__le32	error_subcode_3;

	__le32	reserved_4[4];
पूर्ण;
/*
 * ISP queue - Mailbox Command entry काष्ठाure definition.
 */
#घोषणा MBX_IOCB_TYPE	0x39
काष्ठा mbx_entry_24xx अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t handle_count;		/* Handle count. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */

	uपूर्णांक16_t mbx[28];
पूर्ण;


#घोषणा LOGINOUT_PORT_IOCB_TYPE	0x52	/* Login/Logout Port entry. */
काष्ठा logio_entry_24xx अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */

	__le16	comp_status;		/* Completion status. */
#घोषणा CS_LOGIO_ERROR		0x31	/* Login/Logout IOCB error. */

	__le16	nport_handle;		/* N_PORT handle. */

	__le16	control_flags;		/* Control flags. */
					/* Modअगरiers. */
#घोषणा LCF_INCLUDE_SNS		BIT_10	/* Include SNS (FFFFFC) during LOGO. */
#घोषणा LCF_FCP2_OVERRIDE	BIT_9	/* Set/Reset word 3 of PRLI. */
#घोषणा LCF_CLASS_2		BIT_8	/* Enable class 2 during PLOGI. */
#घोषणा LCF_FREE_NPORT		BIT_7	/* Release NPORT handle after LOGO. */
#घोषणा LCF_EXPL_LOGO		BIT_6	/* Perक्रमm an explicit LOGO. */
#घोषणा LCF_NVME_PRLI		BIT_6   /* Perक्रमm NVME FC4 PRLI */
#घोषणा LCF_SKIP_PRLI		BIT_5	/* Skip PRLI after PLOGI. */
#घोषणा LCF_IMPL_LOGO_ALL	BIT_5	/* Implicit LOGO to all ports. */
#घोषणा LCF_COND_PLOGI		BIT_4	/* PLOGI only अगर not logged-in. */
#घोषणा LCF_IMPL_LOGO		BIT_4	/* Perक्रमm an implicit LOGO. */
#घोषणा LCF_IMPL_PRLO		BIT_4	/* Perक्रमm an implicit PRLO. */
					/* Commands. */
#घोषणा LCF_COMMAND_PLOGI	0x00	/* PLOGI. */
#घोषणा LCF_COMMAND_PRLI	0x01	/* PRLI. */
#घोषणा LCF_COMMAND_PDISC	0x02	/* PDISC. */
#घोषणा LCF_COMMAND_ADISC	0x03	/* ADISC. */
#घोषणा LCF_COMMAND_LOGO	0x08	/* LOGO. */
#घोषणा LCF_COMMAND_PRLO	0x09	/* PRLO. */
#घोषणा LCF_COMMAND_TPRLO	0x0A	/* TPRLO. */

	uपूर्णांक8_t vp_index;
	uपूर्णांक8_t reserved_1;

	uपूर्णांक8_t port_id[3];		/* PortID of destination port. */

	uपूर्णांक8_t rsp_size;		/* Response size in 32bit words. */

	__le32	io_parameter[11];	/* General I/O parameters. */
#घोषणा LSC_SCODE_NOLINK	0x01
#घोषणा LSC_SCODE_NOIOCB	0x02
#घोषणा LSC_SCODE_NOXCB		0x03
#घोषणा LSC_SCODE_CMD_FAILED	0x04
#घोषणा LSC_SCODE_NOFABRIC	0x05
#घोषणा LSC_SCODE_FW_NOT_READY	0x07
#घोषणा LSC_SCODE_NOT_LOGGED_IN	0x09
#घोषणा LSC_SCODE_NOPCB		0x0A

#घोषणा LSC_SCODE_ELS_REJECT	0x18
#घोषणा LSC_SCODE_CMD_PARAM_ERR	0x19
#घोषणा LSC_SCODE_PORTID_USED	0x1A
#घोषणा LSC_SCODE_NPORT_USED	0x1B
#घोषणा LSC_SCODE_NONPORT	0x1C
#घोषणा LSC_SCODE_LOGGED_IN	0x1D
#घोषणा LSC_SCODE_NOFLOGI_ACC	0x1F
पूर्ण;

#घोषणा TSK_MGMT_IOCB_TYPE	0x14
काष्ठा tsk_mgmt_entry अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t handle_count;		/* Handle count. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */

	__le16	nport_handle;		/* N_PORT handle. */

	uपूर्णांक16_t reserved_1;

	__le16	delay;			/* Activity delay in seconds. */

	__le16	समयout;		/* Command समयout. */

	काष्ठा scsi_lun lun;		/* FCP LUN (BE). */

	__le32	control_flags;		/* Control Flags. */
#घोषणा TCF_NOTMCMD_TO_TARGET	BIT_31
#घोषणा TCF_LUN_RESET		BIT_4
#घोषणा TCF_ABORT_TASK_SET	BIT_3
#घोषणा TCF_CLEAR_TASK_SET	BIT_2
#घोषणा TCF_TARGET_RESET	BIT_1
#घोषणा TCF_CLEAR_ACA		BIT_0

	uपूर्णांक8_t reserved_2[20];

	uपूर्णांक8_t port_id[3];		/* PortID of destination port. */
	uपूर्णांक8_t vp_index;

	uपूर्णांक8_t reserved_3[12];
पूर्ण;

#घोषणा ABORT_IOCB_TYPE	0x33
काष्ठा पात_entry_24xx अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t handle_count;		/* Handle count. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */

	जोड़ अणु
		__le16 nport_handle;            /* N_PORT handle. */
		__le16 comp_status;             /* Completion status. */
	पूर्ण;

	__le16	options;		/* Options. */
#घोषणा AOF_NO_ABTS		BIT_0	/* Do not send any ABTS. */
#घोषणा AOF_NO_RRQ		BIT_1   /* Do not send RRQ. */
#घोषणा AOF_ABTS_TIMEOUT	BIT_2   /* Disable logout on ABTS समयout. */
#घोषणा AOF_ABTS_RTY_CNT	BIT_3   /* Use driver specअगरied retry count. */
#घोषणा AOF_RSP_TIMEOUT		BIT_4   /* Use specअगरied response समयout. */


	uपूर्णांक32_t handle_to_पात;	/* System handle to पात. */

	__le16	req_que_no;
	uपूर्णांक8_t reserved_1[30];

	uपूर्णांक8_t port_id[3];		/* PortID of destination port. */
	uपूर्णांक8_t vp_index;
	u8	reserved_2[4];
	जोड़ अणु
		काष्ठा अणु
			__le16 abts_rty_cnt;
			__le16 rsp_समयout;
		पूर्ण drv;
		काष्ठा अणु
			u8	ba_rjt_venकरोrUnique;
			u8	ba_rjt_reasonCodeExpl;
			u8	ba_rjt_reasonCode;
			u8	reserved_3;
		पूर्ण fw;
	पूर्ण;
	u8	reserved_4[4];
पूर्ण;

#घोषणा ABTS_RCV_TYPE		0x54
#घोषणा ABTS_RSP_TYPE		0x55
काष्ठा abts_entry_24xx अणु
	uपूर्णांक8_t entry_type;
	uपूर्णांक8_t entry_count;
	uपूर्णांक8_t handle_count;
	uपूर्णांक8_t entry_status;

	__le32	handle;		/* type 0x55 only */

	__le16	comp_status;		/* type 0x55 only */
	__le16	nport_handle;		/* type 0x54 only */

	__le16	control_flags;		/* type 0x55 only */
	uपूर्णांक8_t vp_idx;
	uपूर्णांक8_t sof_type;		/* sof_type is upper nibble */

	__le32	rx_xch_addr;

	uपूर्णांक8_t d_id[3];
	uपूर्णांक8_t r_ctl;

	uपूर्णांक8_t s_id[3];
	uपूर्णांक8_t cs_ctl;

	uपूर्णांक8_t f_ctl[3];
	uपूर्णांक8_t type;

	__le16	seq_cnt;
	uपूर्णांक8_t df_ctl;
	uपूर्णांक8_t seq_id;

	__le16	rx_id;
	__le16	ox_id;

	__le32	param;

	जोड़ अणु
		काष्ठा अणु
			__le32	subcode3;
			__le32	rsvd;
			__le32	subcode1;
			__le32	subcode2;
		पूर्ण error;
		काष्ठा अणु
			__le16	rsrvd1;
			uपूर्णांक8_t last_seq_id;
			uपूर्णांक8_t seq_id_valid;
			__le16	पातed_rx_id;
			__le16	पातed_ox_id;
			__le16	high_seq_cnt;
			__le16	low_seq_cnt;
		पूर्ण ba_acc;
		काष्ठा अणु
			uपूर्णांक8_t venकरोr_unique;
			uपूर्णांक8_t explanation;
			uपूर्णांक8_t reason;
		पूर्ण ba_rjt;
	पूर्ण payload;

	__le32	rx_xch_addr_to_पात;
पूर्ण __packed;

/* ABTS payload explanation values */
#घोषणा BA_RJT_EXP_NO_ADDITIONAL	0
#घोषणा BA_RJT_EXP_INV_OX_RX_ID		3
#घोषणा BA_RJT_EXP_SEQ_ABORTED		5

/* ABTS payload reason values */
#घोषणा BA_RJT_RSN_INV_CMD_CODE		1
#घोषणा BA_RJT_RSN_LOGICAL_ERROR	3
#घोषणा BA_RJT_RSN_LOGICAL_BUSY		5
#घोषणा BA_RJT_RSN_PROTOCOL_ERROR	7
#घोषणा BA_RJT_RSN_UNABLE_TO_PERFORM	9
#घोषणा BA_RJT_RSN_VENDOR_SPECIFIC	0xff

/* FC_F values */
#घोषणा FC_TYPE_BLD		0x000		/* Basic link data */
#घोषणा FC_F_CTL_RSP_CNTXT	0x800000	/* Responder of exchange */
#घोषणा FC_F_CTL_LAST_SEQ	0x100000	/* Last sequence */
#घोषणा FC_F_CTL_END_SEQ	0x80000		/* Last sequence */
#घोषणा FC_F_CTL_SEQ_INIT	0x010000	/* Sequence initiative */
#घोषणा FC_ROUTING_BLD		0x80		/* Basic link data frame */
#घोषणा FC_R_CTL_BLD_BA_ACC	0x04		/* BA_ACC (basic accept) */

/*
 * ISP I/O Register Set काष्ठाure definitions.
 */
काष्ठा device_reg_24xx अणु
	__le32	flash_addr;		/* Flash/NVRAM BIOS address. */
#घोषणा FARX_DATA_FLAG	BIT_31
#घोषणा FARX_ACCESS_FLASH_CONF	0x7FFD0000
#घोषणा FARX_ACCESS_FLASH_DATA	0x7FF00000
#घोषणा FARX_ACCESS_NVRAM_CONF	0x7FFF0000
#घोषणा FARX_ACCESS_NVRAM_DATA	0x7FFE0000

#घोषणा FA_NVRAM_FUNC0_ADDR	0x80
#घोषणा FA_NVRAM_FUNC1_ADDR	0x180

#घोषणा FA_NVRAM_VPD_SIZE	0x200
#घोषणा FA_NVRAM_VPD0_ADDR	0x00
#घोषणा FA_NVRAM_VPD1_ADDR	0x100

#घोषणा FA_BOOT_CODE_ADDR	0x00000
					/*
					 * RISC code begins at offset 512KB
					 * within flash. Consisting of two
					 * contiguous RISC code segments.
					 */
#घोषणा FA_RISC_CODE_ADDR	0x20000
#घोषणा FA_RISC_CODE_SEGMENTS	2

#घोषणा FA_FLASH_DESCR_ADDR_24	0x11000
#घोषणा FA_FLASH_LAYOUT_ADDR_24	0x11400
#घोषणा FA_NPIV_CONF0_ADDR_24	0x16000
#घोषणा FA_NPIV_CONF1_ADDR_24	0x17000

#घोषणा FA_FW_AREA_ADDR		0x40000
#घोषणा FA_VPD_NVRAM_ADDR	0x48000
#घोषणा FA_FEATURE_ADDR		0x4C000
#घोषणा FA_FLASH_DESCR_ADDR	0x50000
#घोषणा FA_FLASH_LAYOUT_ADDR	0x50400
#घोषणा FA_HW_EVENT0_ADDR	0x54000
#घोषणा FA_HW_EVENT1_ADDR	0x54400
#घोषणा FA_HW_EVENT_SIZE	0x200
#घोषणा FA_HW_EVENT_ENTRY_SIZE	4
#घोषणा FA_NPIV_CONF0_ADDR	0x5C000
#घोषणा FA_NPIV_CONF1_ADDR	0x5D000
#घोषणा FA_FCP_PRIO0_ADDR	0x10000
#घोषणा FA_FCP_PRIO1_ADDR	0x12000

/*
 * Flash Error Log Event Codes.
 */
#घोषणा HW_EVENT_RESET_ERR	0xF00B
#घोषणा HW_EVENT_ISP_ERR	0xF020
#घोषणा HW_EVENT_PARITY_ERR	0xF022
#घोषणा HW_EVENT_NVRAM_CHKSUM_ERR	0xF023
#घोषणा HW_EVENT_FLASH_FW_ERR	0xF024

	__le32	flash_data;		/* Flash/NVRAM BIOS data. */

	__le32	ctrl_status;		/* Control/Status. */
#घोषणा CSRX_FLASH_ACCESS_ERROR	BIT_18	/* Flash/NVRAM Access Error. */
#घोषणा CSRX_DMA_ACTIVE		BIT_17	/* DMA Active status. */
#घोषणा CSRX_DMA_SHUTDOWN	BIT_16	/* DMA Shutकरोwn control status. */
#घोषणा CSRX_FUNCTION		BIT_15	/* Function number. */
					/* PCI-X Bus Mode. */
#घोषणा CSRX_PCIX_BUS_MODE_MASK	(BIT_11|BIT_10|BIT_9|BIT_8)
#घोषणा PBM_PCI_33MHZ		(0 << 8)
#घोषणा PBM_PCIX_M1_66MHZ	(1 << 8)
#घोषणा PBM_PCIX_M1_100MHZ	(2 << 8)
#घोषणा PBM_PCIX_M1_133MHZ	(3 << 8)
#घोषणा PBM_PCIX_M2_66MHZ	(5 << 8)
#घोषणा PBM_PCIX_M2_100MHZ	(6 << 8)
#घोषणा PBM_PCIX_M2_133MHZ	(7 << 8)
#घोषणा PBM_PCI_66MHZ		(8 << 8)
					/* Max Write Burst byte count. */
#घोषणा CSRX_MAX_WRT_BURST_MASK	(BIT_5|BIT_4)
#घोषणा MWB_512_BYTES		(0 << 4)
#घोषणा MWB_1024_BYTES		(1 << 4)
#घोषणा MWB_2048_BYTES		(2 << 4)
#घोषणा MWB_4096_BYTES		(3 << 4)

#घोषणा CSRX_64BIT_SLOT		BIT_2	/* PCI 64-Bit Bus Slot. */
#घोषणा CSRX_FLASH_ENABLE	BIT_1	/* Flash BIOS Read/Write enable. */
#घोषणा CSRX_ISP_SOFT_RESET	BIT_0	/* ISP soft reset. */

	__le32	ictrl;			/* Interrupt control. */
#घोषणा ICRX_EN_RISC_INT	BIT_3	/* Enable RISC पूर्णांकerrupts on PCI. */

	__le32	istatus;		/* Interrupt status. */
#घोषणा ISRX_RISC_INT		BIT_3	/* RISC पूर्णांकerrupt. */

	__le32	unused_1[2];		/* Gap. */

					/* Request Queue. */
	__le32	req_q_in;		/*  In-Poपूर्णांकer. */
	__le32	req_q_out;		/*  Out-Poपूर्णांकer. */
					/* Response Queue. */
	__le32	rsp_q_in;		/*  In-Poपूर्णांकer. */
	__le32	rsp_q_out;		/*  Out-Poपूर्णांकer. */
					/* Priority Request Queue. */
	__le32	preq_q_in;		/*  In-Poपूर्णांकer. */
	__le32	preq_q_out;		/*  Out-Poपूर्णांकer. */

	__le32	unused_2[2];		/* Gap. */

					/* ATIO Queue. */
	__le32	atio_q_in;		/*  In-Poपूर्णांकer. */
	__le32	atio_q_out;		/*  Out-Poपूर्णांकer. */

	__le32	host_status;
#घोषणा HSRX_RISC_INT		BIT_15	/* RISC to Host पूर्णांकerrupt. */
#घोषणा HSRX_RISC_PAUSED	BIT_8	/* RISC Paused. */

	__le32	hccr;			/* Host command & control रेजिस्टर. */
					/* HCCR statuses. */
#घोषणा HCCRX_HOST_INT		BIT_6	/* Host to RISC पूर्णांकerrupt bit. */
#घोषणा HCCRX_RISC_RESET	BIT_5	/* RISC Reset mode bit. */
					/* HCCR commands. */
					/* NOOP. */
#घोषणा HCCRX_NOOP		0x00000000
					/* Set RISC Reset. */
#घोषणा HCCRX_SET_RISC_RESET	0x10000000
					/* Clear RISC Reset. */
#घोषणा HCCRX_CLR_RISC_RESET	0x20000000
					/* Set RISC Pause. */
#घोषणा HCCRX_SET_RISC_PAUSE	0x30000000
					/* Releases RISC Pause. */
#घोषणा HCCRX_REL_RISC_PAUSE	0x40000000
					/* Set HOST to RISC पूर्णांकerrupt. */
#घोषणा HCCRX_SET_HOST_INT	0x50000000
					/* Clear HOST to RISC पूर्णांकerrupt. */
#घोषणा HCCRX_CLR_HOST_INT	0x60000000
					/* Clear RISC to PCI पूर्णांकerrupt. */
#घोषणा HCCRX_CLR_RISC_INT	0xA0000000

	__le32	gpiod;			/* GPIO Data रेजिस्टर. */

					/* LED update mask. */
#घोषणा GPDX_LED_UPDATE_MASK	(BIT_20|BIT_19|BIT_18)
					/* Data update mask. */
#घोषणा GPDX_DATA_UPDATE_MASK	(BIT_17|BIT_16)
					/* Data update mask. */
#घोषणा GPDX_DATA_UPDATE_2_MASK	(BIT_28|BIT_27|BIT_26|BIT_17|BIT_16)
					/* LED control mask. */
#घोषणा GPDX_LED_COLOR_MASK	(BIT_4|BIT_3|BIT_2)
					/* LED bit values. Color names as
					 * referenced in fw spec.
					 */
#घोषणा GPDX_LED_YELLOW_ON	BIT_2
#घोषणा GPDX_LED_GREEN_ON	BIT_3
#घोषणा GPDX_LED_AMBER_ON	BIT_4
					/* Data in/out. */
#घोषणा GPDX_DATA_INOUT		(BIT_1|BIT_0)

	__le32	gpioe;			/* GPIO Enable रेजिस्टर. */
					/* Enable update mask. */
#घोषणा GPEX_ENABLE_UPDATE_MASK	(BIT_17|BIT_16)
					/* Enable update mask. */
#घोषणा GPEX_ENABLE_UPDATE_2_MASK (BIT_28|BIT_27|BIT_26|BIT_17|BIT_16)
					/* Enable. */
#घोषणा GPEX_ENABLE		(BIT_1|BIT_0)

	__le32	iobase_addr;		/* I/O Bus Base Address रेजिस्टर. */

	__le32	unused_3[10];		/* Gap. */

	__le16	mailbox0;
	__le16	mailbox1;
	__le16	mailbox2;
	__le16	mailbox3;
	__le16	mailbox4;
	__le16	mailbox5;
	__le16	mailbox6;
	__le16	mailbox7;
	__le16	mailbox8;
	__le16	mailbox9;
	__le16	mailbox10;
	__le16	mailbox11;
	__le16	mailbox12;
	__le16	mailbox13;
	__le16	mailbox14;
	__le16	mailbox15;
	__le16	mailbox16;
	__le16	mailbox17;
	__le16	mailbox18;
	__le16	mailbox19;
	__le16	mailbox20;
	__le16	mailbox21;
	__le16	mailbox22;
	__le16	mailbox23;
	__le16	mailbox24;
	__le16	mailbox25;
	__le16	mailbox26;
	__le16	mailbox27;
	__le16	mailbox28;
	__le16	mailbox29;
	__le16	mailbox30;
	__le16	mailbox31;

	__le32	iobase_winकरोw;
	__le32	iobase_c4;
	__le32	iobase_c8;
	__le32	unused_4_1[6];		/* Gap. */
	__le32	iobase_q;
	__le32	unused_5[2];		/* Gap. */
	__le32	iobase_select;
	__le32	unused_6[2];		/* Gap. */
	__le32	iobase_sdata;
पूर्ण;
/* RISC-RISC semaphore रेजिस्टर PCI offet */
#घोषणा RISC_REGISTER_BASE_OFFSET	0x7010
#घोषणा RISC_REGISTER_WINDOW_OFFSET	0x6

/* RISC-RISC semaphore/flag रेजिस्टर (risc address 0x7016) */

#घोषणा RISC_SEMAPHORE		0x1UL
#घोषणा RISC_SEMAPHORE_WE	(RISC_SEMAPHORE << 16)
#घोषणा RISC_SEMAPHORE_CLR	(RISC_SEMAPHORE_WE | 0x0UL)
#घोषणा RISC_SEMAPHORE_SET	(RISC_SEMAPHORE_WE | RISC_SEMAPHORE)

#घोषणा RISC_SEMAPHORE_FORCE		0x8000UL
#घोषणा RISC_SEMAPHORE_FORCE_WE		(RISC_SEMAPHORE_FORCE << 16)
#घोषणा RISC_SEMAPHORE_FORCE_CLR	(RISC_SEMAPHORE_FORCE_WE | 0x0UL)
#घोषणा RISC_SEMAPHORE_FORCE_SET	\
		(RISC_SEMAPHORE_FORCE_WE | RISC_SEMAPHORE_FORCE)

/* RISC semaphore समयouts (ms) */
#घोषणा TIMEOUT_SEMAPHORE		2500
#घोषणा TIMEOUT_SEMAPHORE_FORCE		2000
#घोषणा TIMEOUT_TOTAL_ELAPSED		4500

/* Trace Control *************************************************************/

#घोषणा TC_AEN_DISABLE		0

#घोषणा TC_EFT_ENABLE		4
#घोषणा TC_EFT_DISABLE		5

#घोषणा TC_FCE_ENABLE		8
#घोषणा TC_FCE_OPTIONS		0
#घोषणा TC_FCE_DEFAULT_RX_SIZE	2112
#घोषणा TC_FCE_DEFAULT_TX_SIZE	2112
#घोषणा TC_FCE_DISABLE		9
#घोषणा TC_FCE_DISABLE_TRACE	BIT_0

/* MID Support ***************************************************************/

#घोषणा MIN_MULTI_ID_FABRIC	64	/* Must be घातer-of-2. */
#घोषणा MAX_MULTI_ID_FABRIC	256	/* ... */

काष्ठा mid_conf_entry_24xx अणु
	uपूर्णांक16_t reserved_1;

	/*
	 * BIT 0  = Enable Hard Loop Id
	 * BIT 1  = Acquire Loop ID in LIPA
	 * BIT 2  = ID not Acquired
	 * BIT 3  = Enable VP
	 * BIT 4  = Enable Initiator Mode
	 * BIT 5  = Disable Target Mode
	 * BIT 6-7 = Reserved
	 */
	uपूर्णांक8_t options;

	uपूर्णांक8_t hard_address;

	uपूर्णांक8_t port_name[WWN_SIZE];
	uपूर्णांक8_t node_name[WWN_SIZE];
पूर्ण;

काष्ठा mid_init_cb_24xx अणु
	काष्ठा init_cb_24xx init_cb;

	__le16	count;
	__le16	options;

	काष्ठा mid_conf_entry_24xx entries[MAX_MULTI_ID_FABRIC];
पूर्ण;


काष्ठा mid_db_entry_24xx अणु
	uपूर्णांक16_t status;
#घोषणा MDBS_NON_PARTIC		BIT_3
#घोषणा MDBS_ID_ACQUIRED	BIT_1
#घोषणा MDBS_ENABLED		BIT_0

	uपूर्णांक8_t options;
	uपूर्णांक8_t hard_address;

	uपूर्णांक8_t port_name[WWN_SIZE];
	uपूर्णांक8_t node_name[WWN_SIZE];

	uपूर्णांक8_t port_id[3];
	uपूर्णांक8_t reserved_1;
पूर्ण;

/*
 * Virtual Port Control IOCB
 */
#घोषणा VP_CTRL_IOCB_TYPE	0x30	/* Virtual Port Control entry. */
काष्ठा vp_ctrl_entry_24xx अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */

	__le16	vp_idx_failed;

	__le16	comp_status;		/* Completion status. */
#घोषणा CS_VCE_IOCB_ERROR       0x01    /* Error processing IOCB */
#घोषणा CS_VCE_ACQ_ID_ERROR	0x02	/* Error जबतक acquireing ID. */
#घोषणा CS_VCE_BUSY		0x05	/* Firmware not पढ़ोy to accept cmd. */

	__le16	command;
#घोषणा VCE_COMMAND_ENABLE_VPS	0x00	/* Enable VPs. */
#घोषणा VCE_COMMAND_DISABLE_VPS	0x08	/* Disable VPs. */
#घोषणा VCE_COMMAND_DISABLE_VPS_REINIT	0x09 /* Disable VPs and reinit link. */
#घोषणा VCE_COMMAND_DISABLE_VPS_LOGO	0x0a /* Disable VPs and LOGO ports. */
#घोषणा VCE_COMMAND_DISABLE_VPS_LOGO_ALL        0x0b /* Disable VPs and LOGO ports. */

	__le16	vp_count;

	uपूर्णांक8_t vp_idx_map[16];
	__le16	flags;
	__le16	id;
	uपूर्णांक16_t reserved_4;
	__le16	hopct;
	uपूर्णांक8_t reserved_5[24];
पूर्ण;

/*
 * Modअगरy Virtual Port Configuration IOCB
 */
#घोषणा VP_CONFIG_IOCB_TYPE	0x31	/* Virtual Port Config entry. */
काष्ठा vp_config_entry_24xx अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t handle_count;
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */

	__le16	flags;
#घोषणा CS_VF_BIND_VPORTS_TO_VF         BIT_0
#घोषणा CS_VF_SET_QOS_OF_VPORTS         BIT_1
#घोषणा CS_VF_SET_HOPS_OF_VPORTS        BIT_2

	__le16	comp_status;		/* Completion status. */
#घोषणा CS_VCT_STS_ERROR	0x01	/* Specअगरied VPs were not disabled. */
#घोषणा CS_VCT_CNT_ERROR	0x02	/* Invalid VP count. */
#घोषणा CS_VCT_ERROR		0x03	/* Unknown error. */
#घोषणा CS_VCT_IDX_ERROR	0x02	/* Invalid VP index. */
#घोषणा CS_VCT_BUSY		0x05	/* Firmware not पढ़ोy to accept cmd. */

	uपूर्णांक8_t command;
#घोषणा VCT_COMMAND_MOD_VPS     0x00    /* Modअगरy VP configurations. */
#घोषणा VCT_COMMAND_MOD_ENABLE_VPS 0x01 /* Modअगरy configuration & enable VPs. */

	uपूर्णांक8_t vp_count;

	uपूर्णांक8_t vp_index1;
	uपूर्णांक8_t vp_index2;

	uपूर्णांक8_t options_idx1;
	uपूर्णांक8_t hard_address_idx1;
	uपूर्णांक16_t reserved_vp1;
	uपूर्णांक8_t port_name_idx1[WWN_SIZE];
	uपूर्णांक8_t node_name_idx1[WWN_SIZE];

	uपूर्णांक8_t options_idx2;
	uपूर्णांक8_t hard_address_idx2;
	uपूर्णांक16_t reserved_vp2;
	uपूर्णांक8_t port_name_idx2[WWN_SIZE];
	uपूर्णांक8_t node_name_idx2[WWN_SIZE];
	__le16	id;
	uपूर्णांक16_t reserved_4;
	__le16	hopct;
	uपूर्णांक8_t reserved_5[2];
पूर्ण;

#घोषणा VP_RPT_ID_IOCB_TYPE	0x32	/* Report ID Acquisition entry. */
क्रमागत VP_STATUS अणु
	VP_STAT_COMPL,
	VP_STAT_FAIL,
	VP_STAT_ID_CHG,
	VP_STAT_SNS_TO,				/* समयout */
	VP_STAT_SNS_RJT,
	VP_STAT_SCR_TO,				/* समयout */
	VP_STAT_SCR_RJT,
पूर्ण;

क्रमागत VP_FLAGS अणु
	VP_FLAGS_CON_FLOOP = 1,
	VP_FLAGS_CON_P2P = 2,
	VP_FLAGS_CON_FABRIC = 3,
	VP_FLAGS_NAME_VALID = BIT_5,
पूर्ण;

काष्ठा vp_rpt_id_entry_24xx अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */
	__le32 resv1;
	uपूर्णांक8_t vp_acquired;
	uपूर्णांक8_t vp_setup;
	uपूर्णांक8_t vp_idx;		/* Format 0=reserved */
	uपूर्णांक8_t vp_status;	/* Format 0=reserved */

	uपूर्णांक8_t port_id[3];
	uपूर्णांक8_t क्रमmat;
	जोड़ अणु
		काष्ठा _f0 अणु
			/* क्रमmat 0 loop */
			uपूर्णांक8_t vp_idx_map[16];
			uपूर्णांक8_t reserved_4[32];
		पूर्ण f0;
		काष्ठा _f1 अणु
			/* क्रमmat 1 fabric */
			uपूर्णांक8_t vpstat1_subcode; /* vp_status=1 subcode */
			uपूर्णांक8_t flags;
#घोषणा TOPO_MASK  0xE
#घोषणा TOPO_FL    0x2
#घोषणा TOPO_N2N   0x4
#घोषणा TOPO_F     0x6

			uपूर्णांक16_t fip_flags;
			uपूर्णांक8_t rsv2[12];

			uपूर्णांक8_t ls_rjt_venकरोr;
			uपूर्णांक8_t ls_rjt_explanation;
			uपूर्णांक8_t ls_rjt_reason;
			uपूर्णांक8_t rsv3[5];

			uपूर्णांक8_t port_name[8];
			uपूर्णांक8_t node_name[8];
			uपूर्णांक16_t bbcr;
			uपूर्णांक8_t reserved_5[6];
		पूर्ण f1;
		काष्ठा _f2 अणु /* क्रमmat 2: N2N direct connect */
			uपूर्णांक8_t vpstat1_subcode;
			uपूर्णांक8_t flags;
			uपूर्णांक16_t fip_flags;
			uपूर्णांक8_t rsv2[12];

			uपूर्णांक8_t ls_rjt_venकरोr;
			uपूर्णांक8_t ls_rjt_explanation;
			uपूर्णांक8_t ls_rjt_reason;
			uपूर्णांक8_t rsv3[5];

			uपूर्णांक8_t port_name[8];
			uपूर्णांक8_t node_name[8];
			uपूर्णांक16_t bbcr;
			uपूर्णांक8_t reserved_5[2];
			uपूर्णांक8_t remote_nport_id[4];
		पूर्ण f2;
	पूर्ण u;
पूर्ण;

#घोषणा VF_EVFP_IOCB_TYPE       0x26    /* Exchange Virtual Fabric Parameters entry. */
काष्ठा vf_evfp_entry_24xx अणु
        uपूर्णांक8_t entry_type;             /* Entry type. */
        uपूर्णांक8_t entry_count;            /* Entry count. */
        uपूर्णांक8_t sys_define;             /* System defined. */
        uपूर्णांक8_t entry_status;           /* Entry Status. */

        uपूर्णांक32_t handle;                /* System handle. */
        __le16	comp_status;           /* Completion status. */
        __le16	समयout;               /* समयout */
        __le16	adim_tagging_mode;

        __le16	vfport_id;
        uपूर्णांक32_t exch_addr;

        __le16	nport_handle;          /* N_PORT handle. */
        __le16	control_flags;
        uपूर्णांक32_t io_parameter_0;
        uपूर्णांक32_t io_parameter_1;
	__le64	 tx_address __packed;	/* Data segment 0 address. */
        uपूर्णांक32_t tx_len;                /* Data segment 0 length. */
	__le64	 rx_address __packed;	/* Data segment 1 address. */
        uपूर्णांक32_t rx_len;                /* Data segment 1 length. */
पूर्ण;

/* END MID Support ***********************************************************/

/* Flash Description Table ***************************************************/

काष्ठा qla_fdt_layout अणु
	uपूर्णांक8_t sig[4];
	__le16	version;
	__le16	len;
	__le16	checksum;
	uपूर्णांक8_t unused1[2];
	uपूर्णांक8_t model[16];
	__le16	man_id;
	__le16	id;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t erase_cmd;
	uपूर्णांक8_t alt_erase_cmd;
	uपूर्णांक8_t wrt_enable_cmd;
	uपूर्णांक8_t wrt_enable_bits;
	uपूर्णांक8_t wrt_sts_reg_cmd;
	uपूर्णांक8_t unprotect_sec_cmd;
	uपूर्णांक8_t पढ़ो_man_id_cmd;
	__le32 block_size;
	__le32 alt_block_size;
	__le32 flash_size;
	__le32 wrt_enable_data;
	uपूर्णांक8_t पढ़ो_id_addr_len;
	uपूर्णांक8_t wrt_disable_bits;
	uपूर्णांक8_t पढ़ो_dev_id_len;
	uपूर्णांक8_t chip_erase_cmd;
	__le16	पढ़ो_समयout;
	uपूर्णांक8_t protect_sec_cmd;
	uपूर्णांक8_t unused2[65];
पूर्ण;

/* Flash Layout Table ********************************************************/

काष्ठा qla_flt_location अणु
	uपूर्णांक8_t sig[4];
	__le16	start_lo;
	__le16	start_hi;
	uपूर्णांक8_t version;
	uपूर्णांक8_t unused[5];
	__le16	checksum;
पूर्ण;

#घोषणा FLT_REG_FW		0x01
#घोषणा FLT_REG_BOOT_CODE	0x07
#घोषणा FLT_REG_VPD_0		0x14
#घोषणा FLT_REG_NVRAM_0		0x15
#घोषणा FLT_REG_VPD_1		0x16
#घोषणा FLT_REG_NVRAM_1		0x17
#घोषणा FLT_REG_VPD_2		0xD4
#घोषणा FLT_REG_NVRAM_2		0xD5
#घोषणा FLT_REG_VPD_3		0xD6
#घोषणा FLT_REG_NVRAM_3		0xD7
#घोषणा FLT_REG_FDT		0x1a
#घोषणा FLT_REG_FLT		0x1c
#घोषणा FLT_REG_HW_EVENT_0	0x1d
#घोषणा FLT_REG_HW_EVENT_1	0x1f
#घोषणा FLT_REG_NPIV_CONF_0	0x29
#घोषणा FLT_REG_NPIV_CONF_1	0x2a
#घोषणा FLT_REG_GOLD_FW		0x2f
#घोषणा FLT_REG_FCP_PRIO_0	0x87
#घोषणा FLT_REG_FCP_PRIO_1	0x88
#घोषणा FLT_REG_CNA_FW		0x97
#घोषणा FLT_REG_BOOT_CODE_8044	0xA2
#घोषणा FLT_REG_FCOE_FW		0xA4
#घोषणा FLT_REG_FCOE_NVRAM_0	0xAA
#घोषणा FLT_REG_FCOE_NVRAM_1	0xAC

/* 27xx */
#घोषणा FLT_REG_IMG_PRI_27XX	0x95
#घोषणा FLT_REG_IMG_SEC_27XX	0x96
#घोषणा FLT_REG_FW_SEC_27XX	0x02
#घोषणा FLT_REG_BOOTLOAD_SEC_27XX	0x9
#घोषणा FLT_REG_VPD_SEC_27XX_0	0x50
#घोषणा FLT_REG_VPD_SEC_27XX_1	0x52
#घोषणा FLT_REG_VPD_SEC_27XX_2	0xD8
#घोषणा FLT_REG_VPD_SEC_27XX_3	0xDA

/* 28xx */
#घोषणा FLT_REG_AUX_IMG_PRI_28XX	0x125
#घोषणा FLT_REG_AUX_IMG_SEC_28XX	0x126
#घोषणा FLT_REG_VPD_SEC_28XX_0		0x10C
#घोषणा FLT_REG_VPD_SEC_28XX_1		0x10E
#घोषणा FLT_REG_VPD_SEC_28XX_2		0x110
#घोषणा FLT_REG_VPD_SEC_28XX_3		0x112
#घोषणा FLT_REG_NVRAM_SEC_28XX_0	0x10D
#घोषणा FLT_REG_NVRAM_SEC_28XX_1	0x10F
#घोषणा FLT_REG_NVRAM_SEC_28XX_2	0x111
#घोषणा FLT_REG_NVRAM_SEC_28XX_3	0x113
#घोषणा FLT_REG_MPI_PRI_28XX		0xD3
#घोषणा FLT_REG_MPI_SEC_28XX		0xF0
#घोषणा FLT_REG_PEP_PRI_28XX		0xD1
#घोषणा FLT_REG_PEP_SEC_28XX		0xF1

काष्ठा qla_flt_region अणु
	__le16	code;
	uपूर्णांक8_t attribute;
	uपूर्णांक8_t reserved;
	__le32 size;
	__le32 start;
	__le32 end;
पूर्ण;

काष्ठा qla_flt_header अणु
	__le16	version;
	__le16	length;
	__le16	checksum;
	__le16	unused;
	काष्ठा qla_flt_region region[0];
पूर्ण;

#घोषणा FLT_REGION_SIZE		16
#घोषणा भग्न_उच्च_REGIONS		0xFF
#घोषणा FLT_REGIONS_SIZE	(FLT_REGION_SIZE * भग्न_उच्च_REGIONS)

/* Flash NPIV Configuration Table ********************************************/

काष्ठा qla_npiv_header अणु
	uपूर्णांक8_t sig[2];
	__le16	version;
	__le16	entries;
	__le16	unused[4];
	__le16	checksum;
पूर्ण;

काष्ठा qla_npiv_entry अणु
	__le16	flags;
	__le16	vf_id;
	uपूर्णांक8_t q_qos;
	uपूर्णांक8_t f_qos;
	__le16	unused1;
	uपूर्णांक8_t port_name[WWN_SIZE];
	uपूर्णांक8_t node_name[WWN_SIZE];
पूर्ण;

/* 84XX Support **************************************************************/

#घोषणा MBA_ISP84XX_ALERT	0x800f  /* Alert Notअगरication. */
#घोषणा A84_PANIC_RECOVERY	0x1
#घोषणा A84_OP_LOGIN_COMPLETE	0x2
#घोषणा A84_DIAG_LOGIN_COMPLETE	0x3
#घोषणा A84_GOLD_LOGIN_COMPLETE	0x4

#घोषणा MBC_ISP84XX_RESET	0x3a    /* Reset. */

#घोषणा FSTATE_REMOTE_FC_DOWN	BIT_0
#घोषणा FSTATE_NSL_LINK_DOWN	BIT_1
#घोषणा FSTATE_IS_DIAG_FW	BIT_2
#घोषणा FSTATE_LOGGED_IN	BIT_3
#घोषणा FSTATE_WAITING_FOR_VERIFY	BIT_4

#घोषणा VERIFY_CHIP_IOCB_TYPE	0x1B
काष्ठा verअगरy_chip_entry_84xx अणु
	uपूर्णांक8_t entry_type;
	uपूर्णांक8_t entry_count;
	uपूर्णांक8_t sys_defined;
	uपूर्णांक8_t entry_status;

	uपूर्णांक32_t handle;

	__le16	options;
#घोषणा VCO_DONT_UPDATE_FW	BIT_0
#घोषणा VCO_FORCE_UPDATE	BIT_1
#घोषणा VCO_DONT_RESET_UPDATE	BIT_2
#घोषणा VCO_DIAG_FW		BIT_3
#घोषणा VCO_END_OF_DATA		BIT_14
#घोषणा VCO_ENABLE_DSD		BIT_15

	__le16	reserved_1;

	__le16	data_seg_cnt;
	__le16	reserved_2[3];

	__le32	fw_ver;
	__le32	exchange_address;

	__le32 reserved_3[3];
	__le32	fw_size;
	__le32	fw_seq_size;
	__le32	relative_offset;

	काष्ठा dsd64 dsd;
पूर्ण;

काष्ठा verअगरy_chip_rsp_84xx अणु
	uपूर्णांक8_t entry_type;
	uपूर्णांक8_t entry_count;
	uपूर्णांक8_t sys_defined;
	uपूर्णांक8_t entry_status;

	uपूर्णांक32_t handle;

	__le16	comp_status;
#घोषणा CS_VCS_CHIP_FAILURE	0x3
#घोषणा CS_VCS_BAD_EXCHANGE	0x8
#घोषणा CS_VCS_SEQ_COMPLETEi	0x40

	__le16	failure_code;
#घोषणा VFC_CHECKSUM_ERROR	0x1
#घोषणा VFC_INVALID_LEN		0x2
#घोषणा VFC_ALREADY_IN_PROGRESS	0x8

	__le16	reserved_1[4];

	__le32	fw_ver;
	__le32	exchange_address;

	__le32 reserved_2[6];
पूर्ण;

#घोषणा ACCESS_CHIP_IOCB_TYPE	0x2B
काष्ठा access_chip_84xx अणु
	uपूर्णांक8_t entry_type;
	uपूर्णांक8_t entry_count;
	uपूर्णांक8_t sys_defined;
	uपूर्णांक8_t entry_status;

	uपूर्णांक32_t handle;

	__le16	options;
#घोषणा ACO_DUMP_MEMORY		0x0
#घोषणा ACO_LOAD_MEMORY		0x1
#घोषणा ACO_CHANGE_CONFIG_PARAM	0x2
#घोषणा ACO_REQUEST_INFO	0x3

	__le16	reserved1;

	__le16	dseg_count;
	__le16	reserved2[3];

	__le32	parameter1;
	__le32	parameter2;
	__le32	parameter3;

	__le32	reserved3[3];
	__le32	total_byte_cnt;
	__le32	reserved4;

	काष्ठा dsd64 dsd;
पूर्ण;

काष्ठा access_chip_rsp_84xx अणु
	uपूर्णांक8_t entry_type;
	uपूर्णांक8_t entry_count;
	uपूर्णांक8_t sys_defined;
	uपूर्णांक8_t entry_status;

	uपूर्णांक32_t handle;

	__le16	comp_status;
	__le16	failure_code;
	__le32	residual_count;

	__le32	reserved[12];
पूर्ण;

/* 81XX Support **************************************************************/

#घोषणा MBA_DCBX_START		0x8016
#घोषणा MBA_DCBX_COMPLETE	0x8030
#घोषणा MBA_FCF_CONF_ERR	0x8031
#घोषणा MBA_DCBX_PARAM_UPDATE	0x8032
#घोषणा MBA_IDC_COMPLETE	0x8100
#घोषणा MBA_IDC_NOTIFY		0x8101
#घोषणा MBA_IDC_TIME_EXT	0x8102

#घोषणा MBC_IDC_ACK		0x101
#घोषणा MBC_RESTART_MPI_FW	0x3d
#घोषणा MBC_FLASH_ACCESS_CTRL	0x3e	/* Control flash access. */
#घोषणा MBC_GET_XGMAC_STATS	0x7a
#घोषणा MBC_GET_DCBX_PARAMS	0x51

/*
 * ISP83xx mailbox commands
 */
#घोषणा MBC_WRITE_REMOTE_REG		0x0001 /* Write remote रेजिस्टर */
#घोषणा MBC_READ_REMOTE_REG		0x0009 /* Read remote रेजिस्टर */
#घोषणा MBC_RESTART_NIC_FIRMWARE	0x003d /* Restart NIC firmware */
#घोषणा MBC_SET_ACCESS_CONTROL		0x003e /* Access control command */

/* Flash access control option field bit definitions */
#घोषणा FAC_OPT_FORCE_SEMAPHORE		BIT_15
#घोषणा FAC_OPT_REQUESTOR_ID		BIT_14
#घोषणा FAC_OPT_CMD_SUBCODE		0xff

/* Flash access control command subcodes */
#घोषणा FAC_OPT_CMD_WRITE_PROTECT	0x00
#घोषणा FAC_OPT_CMD_WRITE_ENABLE	0x01
#घोषणा FAC_OPT_CMD_ERASE_SECTOR	0x02
#घोषणा FAC_OPT_CMD_LOCK_SEMAPHORE	0x03
#घोषणा FAC_OPT_CMD_UNLOCK_SEMAPHORE	0x04
#घोषणा FAC_OPT_CMD_GET_SECTOR_SIZE	0x05

/* enhanced features bit definitions */
#घोषणा NEF_LR_DIST_ENABLE	BIT_0

/* LR Distance bit positions */
#घोषणा LR_DIST_NV_POS		2
#घोषणा LR_DIST_NV_MASK		0xf
#घोषणा LR_DIST_FW_POS		12

/* FAC semaphore defines */
#घोषणा FAC_SEMAPHORE_UNLOCK    0
#घोषणा FAC_SEMAPHORE_LOCK      1

काष्ठा nvram_81xx अणु
	/* NVRAM header. */
	uपूर्णांक8_t id[4];
	__le16	nvram_version;
	__le16	reserved_0;

	/* Firmware Initialization Control Block. */
	__le16	version;
	__le16	reserved_1;
	__le16	frame_payload_size;
	__le16	execution_throttle;
	__le16	exchange_count;
	__le16	reserved_2;

	uपूर्णांक8_t port_name[WWN_SIZE];
	uपूर्णांक8_t node_name[WWN_SIZE];

	__le16	login_retry_count;
	__le16	reserved_3;
	__le16	पूर्णांकerrupt_delay_समयr;
	__le16	login_समयout;

	__le32	firmware_options_1;
	__le32	firmware_options_2;
	__le32	firmware_options_3;

	__le16	reserved_4[4];

	/* Offset 64. */
	uपूर्णांक8_t enode_mac[6];
	__le16	reserved_5[5];

	/* Offset 80. */
	__le16	reserved_6[24];

	/* Offset 128. */
	__le16	ex_version;
	uपूर्णांक8_t prio_fcf_matching_flags;
	uपूर्णांक8_t reserved_6_1[3];
	__le16	pri_fcf_vlan_id;
	uपूर्णांक8_t pri_fcf_fabric_name[8];
	__le16	reserved_6_2[7];
	uपूर्णांक8_t spma_mac_addr[6];
	__le16	reserved_6_3[14];

	/* Offset 192. */
	uपूर्णांक8_t min_supported_speed;
	uपूर्णांक8_t reserved_7_0;
	__le16	reserved_7[31];

	/*
	 * BIT 0  = Enable spinup delay
	 * BIT 1  = Disable BIOS
	 * BIT 2  = Enable Memory Map BIOS
	 * BIT 3  = Enable Selectable Boot
	 * BIT 4  = Disable RISC code load
	 * BIT 5  = Disable Serdes
	 * BIT 6  = Opt boot mode
	 * BIT 7  = Interrupt enable
	 *
	 * BIT 8  = EV Control enable
	 * BIT 9  = Enable lip reset
	 * BIT 10 = Enable lip full login
	 * BIT 11 = Enable target reset
	 * BIT 12 = Stop firmware
	 * BIT 13 = Enable nodename option
	 * BIT 14 = Default WWPN valid
	 * BIT 15 = Enable alternate WWN
	 *
	 * BIT 16 = CLP LUN string
	 * BIT 17 = CLP Target string
	 * BIT 18 = CLP BIOS enable string
	 * BIT 19 = CLP Serdes string
	 * BIT 20 = CLP WWPN string
	 * BIT 21 = CLP WWNN string
	 * BIT 22 =
	 * BIT 23 =
	 * BIT 24 = Keep WWPN
	 * BIT 25 = Temp WWPN
	 * BIT 26-31 =
	 */
	__le32	host_p;

	uपूर्णांक8_t alternate_port_name[WWN_SIZE];
	uपूर्णांक8_t alternate_node_name[WWN_SIZE];

	uपूर्णांक8_t boot_port_name[WWN_SIZE];
	__le16	boot_lun_number;
	__le16	reserved_8;

	uपूर्णांक8_t alt1_boot_port_name[WWN_SIZE];
	__le16	alt1_boot_lun_number;
	__le16	reserved_9;

	uपूर्णांक8_t alt2_boot_port_name[WWN_SIZE];
	__le16	alt2_boot_lun_number;
	__le16	reserved_10;

	uपूर्णांक8_t alt3_boot_port_name[WWN_SIZE];
	__le16	alt3_boot_lun_number;
	__le16	reserved_11;

	/*
	 * BIT 0 = Selective Login
	 * BIT 1 = Alt-Boot Enable
	 * BIT 2 = Reserved
	 * BIT 3 = Boot Order List
	 * BIT 4 = Reserved
	 * BIT 5 = Selective LUN
	 * BIT 6 = Reserved
	 * BIT 7-31 =
	 */
	__le32	efi_parameters;

	uपूर्णांक8_t reset_delay;
	uपूर्णांक8_t reserved_12;
	__le16	reserved_13;

	__le16	boot_id_number;
	__le16	reserved_14;

	__le16	max_luns_per_target;
	__le16	reserved_15;

	__le16	port_करोwn_retry_count;
	__le16	link_करोwn_समयout;

	/* FCode parameters. */
	__le16	fcode_parameter;

	__le16	reserved_16[3];

	/* Offset 352. */
	uपूर्णांक8_t reserved_17[4];
	__le16	reserved_18[5];
	uपूर्णांक8_t reserved_19[2];
	__le16	reserved_20[8];

	/* Offset 384. */
	uपूर्णांक8_t reserved_21[16];
	__le16	reserved_22[3];

	/* Offset 406 (0x196) Enhanced Features
	 * BIT 0    = Extended BB credits क्रम LR
	 * BIT 1    = Virtual Fabric Enable
	 * BIT 2-5  = Distance Support अगर BIT 0 is on
	 * BIT 6    = Prefer FCP
	 * BIT 7    = SCM Disabled अगर BIT is set (1)
	 * BIT 8-15 = Unused
	 */
	uपूर्णांक16_t enhanced_features;

	uपूर्णांक16_t reserved_24[4];

	/* Offset 416. */
	__le16	reserved_25[32];

	/* Offset 480. */
	uपूर्णांक8_t model_name[16];

	/* Offset 496. */
	__le16	feature_mask_l;
	__le16	feature_mask_h;
	__le16	reserved_26[2];

	__le16	subप्रणाली_venकरोr_id;
	__le16	subप्रणाली_device_id;

	__le32	checksum;
पूर्ण;

/*
 * ISP Initialization Control Block.
 * Little endian except where noted.
 */
#घोषणा	ICB_VERSION 1
काष्ठा init_cb_81xx अणु
	__le16	version;
	__le16	reserved_1;

	__le16	frame_payload_size;
	__le16	execution_throttle;
	__le16	exchange_count;

	__le16	reserved_2;

	uपूर्णांक8_t port_name[WWN_SIZE];		/* Big endian. */
	uपूर्णांक8_t node_name[WWN_SIZE];		/* Big endian. */

	__le16	response_q_inpoपूर्णांकer;
	__le16	request_q_outpoपूर्णांकer;

	__le16	login_retry_count;

	__le16	prio_request_q_outpoपूर्णांकer;

	__le16	response_q_length;
	__le16	request_q_length;

	__le16	reserved_3;

	__le16	prio_request_q_length;

	__le64	 request_q_address __packed;
	__le64	 response_q_address __packed;
	__le64	 prio_request_q_address __packed;

	uपूर्णांक8_t reserved_4[8];

	__le16	atio_q_inpoपूर्णांकer;
	__le16	atio_q_length;
	__le64	 atio_q_address __packed;

	__le16	पूर्णांकerrupt_delay_समयr;		/* 100us increments. */
	__le16	login_समयout;

	/*
	 * BIT 0-3 = Reserved
	 * BIT 4  = Enable Target Mode
	 * BIT 5  = Disable Initiator Mode
	 * BIT 6  = Reserved
	 * BIT 7  = Reserved
	 *
	 * BIT 8-13 = Reserved
	 * BIT 14 = Node Name Option
	 * BIT 15-31 = Reserved
	 */
	__le32	firmware_options_1;

	/*
	 * BIT 0  = Operation Mode bit 0
	 * BIT 1  = Operation Mode bit 1
	 * BIT 2  = Operation Mode bit 2
	 * BIT 3  = Operation Mode bit 3
	 * BIT 4-7 = Reserved
	 *
	 * BIT 8  = Enable Class 2
	 * BIT 9  = Enable ACK0
	 * BIT 10 = Reserved
	 * BIT 11 = Enable FC-SP Security
	 * BIT 12 = FC Tape Enable
	 * BIT 13 = Reserved
	 * BIT 14 = Enable Target PRLI Control
	 * BIT 15-31 = Reserved
	 */
	__le32	firmware_options_2;

	/*
	 * BIT 0-3 = Reserved
	 * BIT 4  = FCP RSP Payload bit 0
	 * BIT 5  = FCP RSP Payload bit 1
	 * BIT 6  = Enable Receive Out-of-Order data frame handling
	 * BIT 7  = Reserved
	 *
	 * BIT 8  = Reserved
	 * BIT 9  = Enable Out-of-Order FCP_XFER_RDY relative offset handling
	 * BIT 10-16 = Reserved
	 * BIT 17 = Enable multiple FCFs
	 * BIT 18-20 = MAC addressing mode
	 * BIT 21-25 = Ethernet data rate
	 * BIT 26 = Enable ethernet header rx IOCB क्रम ATIO q
	 * BIT 27 = Enable ethernet header rx IOCB क्रम response q
	 * BIT 28 = SPMA selection bit 0
	 * BIT 28 = SPMA selection bit 1
	 * BIT 30-31 = Reserved
	 */
	__le32	firmware_options_3;

	uपूर्णांक8_t  reserved_5[8];

	uपूर्णांक8_t enode_mac[6];

	uपूर्णांक8_t reserved_6[10];
पूर्ण;

काष्ठा mid_init_cb_81xx अणु
	काष्ठा init_cb_81xx init_cb;

	uपूर्णांक16_t count;
	uपूर्णांक16_t options;

	काष्ठा mid_conf_entry_24xx entries[MAX_MULTI_ID_FABRIC];
पूर्ण;

काष्ठा ex_init_cb_81xx अणु
	uपूर्णांक16_t ex_version;
	uपूर्णांक8_t prio_fcf_matching_flags;
	uपूर्णांक8_t reserved_1[3];
	uपूर्णांक16_t pri_fcf_vlan_id;
	uपूर्णांक8_t pri_fcf_fabric_name[8];
	uपूर्णांक16_t reserved_2[7];
	uपूर्णांक8_t spma_mac_addr[6];
	uपूर्णांक16_t reserved_3[14];
पूर्ण;

#घोषणा FARX_ACCESS_FLASH_CONF_81XX	0x7FFD0000
#घोषणा FARX_ACCESS_FLASH_DATA_81XX	0x7F800000
#घोषणा FARX_ACCESS_FLASH_CONF_28XX	0x7FFD0000
#घोषणा FARX_ACCESS_FLASH_DATA_28XX	0x7F7D0000

/* FCP priority config defines *************************************/
/* operations */
#घोषणा QLFC_FCP_PRIO_DISABLE           0x0
#घोषणा QLFC_FCP_PRIO_ENABLE            0x1
#घोषणा QLFC_FCP_PRIO_GET_CONFIG        0x2
#घोषणा QLFC_FCP_PRIO_SET_CONFIG        0x3

काष्ठा qla_fcp_prio_entry अणु
	uपूर्णांक16_t flags;         /* Describes parameter(s) in FCP        */
	/* priority entry that are valid        */
#घोषणा FCP_PRIO_ENTRY_VALID            0x1
#घोषणा FCP_PRIO_ENTRY_TAG_VALID        0x2
#घोषणा FCP_PRIO_ENTRY_SPID_VALID       0x4
#घोषणा FCP_PRIO_ENTRY_DPID_VALID       0x8
#घोषणा FCP_PRIO_ENTRY_LUNB_VALID       0x10
#घोषणा FCP_PRIO_ENTRY_LUNE_VALID       0x20
#घोषणा FCP_PRIO_ENTRY_SWWN_VALID       0x40
#घोषणा FCP_PRIO_ENTRY_DWWN_VALID       0x80
	uपूर्णांक8_t  tag;           /* Priority value                   */
	uपूर्णांक8_t  reserved;      /* Reserved क्रम future use          */
	uपूर्णांक32_t src_pid;       /* Src port id. high order byte     */
				/* unused; -1 (wild card)           */
	uपूर्णांक32_t dst_pid;       /* Src port id. high order byte     */
	/* unused; -1 (wild card)           */
	uपूर्णांक16_t lun_beg;       /* 1st lun num of lun range.        */
				/* -1 (wild card)                   */
	uपूर्णांक16_t lun_end;       /* 2nd lun num of lun range.        */
				/* -1 (wild card)                   */
	uपूर्णांक8_t  src_wwpn[8];   /* Source WWPN: -1 (wild card)      */
	uपूर्णांक8_t  dst_wwpn[8];   /* Destination WWPN: -1 (wild card) */
पूर्ण;

काष्ठा qla_fcp_prio_cfg अणु
	uपूर्णांक8_t  signature[4];  /* "HQOS" signature of config data  */
	uपूर्णांक16_t version;       /* 1: Initial version               */
	uपूर्णांक16_t length;        /* config data size in num bytes    */
	uपूर्णांक16_t checksum;      /* config data bytes checksum       */
	uपूर्णांक16_t num_entries;   /* Number of entries                */
	uपूर्णांक16_t size_of_entry; /* Size of each entry in num bytes  */
	uपूर्णांक8_t  attributes;    /* enable/disable, persistence      */
#घोषणा FCP_PRIO_ATTR_DISABLE   0x0
#घोषणा FCP_PRIO_ATTR_ENABLE    0x1
#घोषणा FCP_PRIO_ATTR_PERSIST   0x2
	uपूर्णांक8_t  reserved;      /* Reserved क्रम future use          */
#घोषणा FCP_PRIO_CFG_HDR_SIZE   दुरत्व(काष्ठा qla_fcp_prio_cfg, entry)
	काष्ठा qla_fcp_prio_entry entry[1023]; /* fcp priority entries  */
	uपूर्णांक8_t  reserved2[16];
पूर्ण;

#घोषणा FCP_PRIO_CFG_SIZE       (32*1024) /* fcp prio data per port*/

/* 25XX Support ****************************************************/
#घोषणा FA_FCP_PRIO0_ADDR_25	0x3C000
#घोषणा FA_FCP_PRIO1_ADDR_25	0x3E000

/* 81XX Flash locations -- occupies second 2MB region. */
#घोषणा FA_BOOT_CODE_ADDR_81	0x80000
#घोषणा FA_RISC_CODE_ADDR_81	0xA0000
#घोषणा FA_FW_AREA_ADDR_81	0xC0000
#घोषणा FA_VPD_NVRAM_ADDR_81	0xD0000
#घोषणा FA_VPD0_ADDR_81		0xD0000
#घोषणा FA_VPD1_ADDR_81		0xD0400
#घोषणा FA_NVRAM0_ADDR_81	0xD0080
#घोषणा FA_NVRAM1_ADDR_81	0xD0180
#घोषणा FA_FEATURE_ADDR_81	0xD4000
#घोषणा FA_FLASH_DESCR_ADDR_81	0xD8000
#घोषणा FA_FLASH_LAYOUT_ADDR_81	0xD8400
#घोषणा FA_HW_EVENT0_ADDR_81	0xDC000
#घोषणा FA_HW_EVENT1_ADDR_81	0xDC400
#घोषणा FA_NPIV_CONF0_ADDR_81	0xD1000
#घोषणा FA_NPIV_CONF1_ADDR_81	0xD2000

/* 83XX Flash locations -- occupies second 8MB region. */
#घोषणा FA_FLASH_LAYOUT_ADDR_83	(0x3F1000/4)
#घोषणा FA_FLASH_LAYOUT_ADDR_28	(0x11000/4)

#घोषणा NVRAM_DUAL_FCP_NVME_FLAG_OFFSET	0x196

#पूर्ण_अगर
