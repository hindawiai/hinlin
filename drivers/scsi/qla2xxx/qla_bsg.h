<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#अगर_अघोषित __QLA_BSG_H
#घोषणा __QLA_BSG_H

/* BSG Venकरोr specअगरic commands */
#घोषणा QL_VND_LOOPBACK		0x01
#घोषणा QL_VND_A84_RESET	0x02
#घोषणा QL_VND_A84_UPDATE_FW	0x03
#घोषणा QL_VND_A84_MGMT_CMD	0x04
#घोषणा QL_VND_IIDMA		0x05
#घोषणा QL_VND_FCP_PRIO_CFG_CMD	0x06
#घोषणा QL_VND_READ_FLASH	0x07
#घोषणा QL_VND_UPDATE_FLASH	0x08
#घोषणा QL_VND_SET_FRU_VERSION	0x0B
#घोषणा QL_VND_READ_FRU_STATUS	0x0C
#घोषणा QL_VND_WRITE_FRU_STATUS	0x0D
#घोषणा QL_VND_DIAG_IO_CMD	0x0A
#घोषणा QL_VND_WRITE_I2C	0x10
#घोषणा QL_VND_READ_I2C		0x11
#घोषणा QL_VND_FX00_MGMT_CMD	0x12
#घोषणा QL_VND_SERDES_OP	0x13
#घोषणा	QL_VND_SERDES_OP_EX	0x14
#घोषणा QL_VND_GET_FLASH_UPDATE_CAPS    0x15
#घोषणा QL_VND_SET_FLASH_UPDATE_CAPS    0x16
#घोषणा QL_VND_GET_BBCR_DATA    0x17
#घोषणा QL_VND_GET_PRIV_STATS	0x18
#घोषणा QL_VND_DPORT_DIAGNOSTICS	0x19
#घोषणा QL_VND_GET_PRIV_STATS_EX	0x1A
#घोषणा QL_VND_SS_GET_FLASH_IMAGE_STATUS	0x1E
#घोषणा QL_VND_MANAGE_HOST_STATS	0x23
#घोषणा QL_VND_GET_HOST_STATS		0x24
#घोषणा QL_VND_GET_TGT_STATS		0x25
#घोषणा QL_VND_MANAGE_HOST_PORT		0x26

/* BSG Venकरोr specअगरic subcode वापसs */
#घोषणा EXT_STATUS_OK			0
#घोषणा EXT_STATUS_ERR			1
#घोषणा EXT_STATUS_BUSY			2
#घोषणा EXT_STATUS_INVALID_PARAM	6
#घोषणा EXT_STATUS_DATA_OVERRUN		7
#घोषणा EXT_STATUS_DATA_UNDERRUN	8
#घोषणा EXT_STATUS_MAILBOX		11
#घोषणा EXT_STATUS_BUFFER_TOO_SMALL	16
#घोषणा EXT_STATUS_NO_MEMORY		17
#घोषणा EXT_STATUS_DEVICE_OFFLINE	22

/*
 * To support bidirectional iocb
 * BSG Venकरोr specअगरic वापसs
 */
#घोषणा EXT_STATUS_NOT_SUPPORTED	27
#घोषणा EXT_STATUS_INVALID_CFG		28
#घोषणा EXT_STATUS_DMA_ERR		29
#घोषणा EXT_STATUS_TIMEOUT		30
#घोषणा EXT_STATUS_THREAD_FAILED	31
#घोषणा EXT_STATUS_DATA_CMP_FAILED	32

/* BSG definations क्रम पूर्णांकerpreting CommandSent field */
#घोषणा INT_DEF_LB_LOOPBACK_CMD         0
#घोषणा INT_DEF_LB_ECHO_CMD             1

/* Loopback related definations */
#घोषणा INTERNAL_LOOPBACK		0xF1
#घोषणा EXTERNAL_LOOPBACK		0xF2
#घोषणा ENABLE_INTERNAL_LOOPBACK	0x02
#घोषणा ENABLE_EXTERNAL_LOOPBACK	0x04
#घोषणा INTERNAL_LOOPBACK_MASK		0x000E
#घोषणा MAX_ELS_FRAME_PAYLOAD		252
#घोषणा ELS_OPCODE_BYTE			0x10

/* BSG Venकरोr specअगरic definations */
#घोषणा A84_ISSUE_WRITE_TYPE_CMD        0
#घोषणा A84_ISSUE_READ_TYPE_CMD         1
#घोषणा A84_CLEANUP_CMD                 2
#घोषणा A84_ISSUE_RESET_OP_FW           3
#घोषणा A84_ISSUE_RESET_DIAG_FW         4
#घोषणा A84_ISSUE_UPDATE_OPFW_CMD       5
#घोषणा A84_ISSUE_UPDATE_DIAGFW_CMD     6

काष्ठा qla84_mgmt_param अणु
	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t start_addr;
		पूर्ण mem; /* क्रम QLA84_MGMT_READ/WRITE_MEM */
		काष्ठा अणु
			uपूर्णांक32_t id;
#घोषणा QLA84_MGMT_CONFIG_ID_UIF        1
#घोषणा QLA84_MGMT_CONFIG_ID_FCOE_COS   2
#घोषणा QLA84_MGMT_CONFIG_ID_PAUSE      3
#घोषणा QLA84_MGMT_CONFIG_ID_TIMEOUTS   4

		uपूर्णांक32_t param0;
		uपूर्णांक32_t param1;
	पूर्ण config; /* क्रम QLA84_MGMT_CHNG_CONFIG */

	काष्ठा अणु
		uपूर्णांक32_t type;
#घोषणा QLA84_MGMT_INFO_CONFIG_LOG_DATA         1 /* Get Config Log Data */
#घोषणा QLA84_MGMT_INFO_LOG_DATA                2 /* Get Log Data */
#घोषणा QLA84_MGMT_INFO_PORT_STAT               3 /* Get Port Statistics */
#घोषणा QLA84_MGMT_INFO_LIF_STAT                4 /* Get LIF Statistics  */
#घोषणा QLA84_MGMT_INFO_ASIC_STAT               5 /* Get ASIC Statistics */
#घोषणा QLA84_MGMT_INFO_CONFIG_PARAMS           6 /* Get Config Parameters */
#घोषणा QLA84_MGMT_INFO_PANIC_LOG               7 /* Get Panic Log */

		uपूर्णांक32_t context;
/*
* context definitions क्रम QLA84_MGMT_INFO_CONFIG_LOG_DATA
*/
#घोषणा IC_LOG_DATA_LOG_ID_DEBUG_LOG                    0
#घोषणा IC_LOG_DATA_LOG_ID_LEARN_LOG                    1
#घोषणा IC_LOG_DATA_LOG_ID_FC_ACL_INGRESS_LOG           2
#घोषणा IC_LOG_DATA_LOG_ID_FC_ACL_EGRESS_LOG            3
#घोषणा IC_LOG_DATA_LOG_ID_ETHERNET_ACL_INGRESS_LOG     4
#घोषणा IC_LOG_DATA_LOG_ID_ETHERNET_ACL_EGRESS_LOG      5
#घोषणा IC_LOG_DATA_LOG_ID_MESSAGE_TRANSMIT_LOG         6
#घोषणा IC_LOG_DATA_LOG_ID_MESSAGE_RECEIVE_LOG          7
#घोषणा IC_LOG_DATA_LOG_ID_LINK_EVENT_LOG               8
#घोषणा IC_LOG_DATA_LOG_ID_DCX_LOG                      9

/*
* context definitions क्रम QLA84_MGMT_INFO_PORT_STAT
*/
#घोषणा IC_PORT_STATISTICS_PORT_NUMBER_ETHERNET_PORT0   0
#घोषणा IC_PORT_STATISTICS_PORT_NUMBER_ETHERNET_PORT1   1
#घोषणा IC_PORT_STATISTICS_PORT_NUMBER_NSL_PORT0        2
#घोषणा IC_PORT_STATISTICS_PORT_NUMBER_NSL_PORT1        3
#घोषणा IC_PORT_STATISTICS_PORT_NUMBER_FC_PORT0         4
#घोषणा IC_PORT_STATISTICS_PORT_NUMBER_FC_PORT1         5


/*
* context definitions क्रम QLA84_MGMT_INFO_LIF_STAT
*/
#घोषणा IC_LIF_STATISTICS_LIF_NUMBER_ETHERNET_PORT0     0
#घोषणा IC_LIF_STATISTICS_LIF_NUMBER_ETHERNET_PORT1     1
#घोषणा IC_LIF_STATISTICS_LIF_NUMBER_FC_PORT0           2
#घोषणा IC_LIF_STATISTICS_LIF_NUMBER_FC_PORT1           3
#घोषणा IC_LIF_STATISTICS_LIF_NUMBER_CPU                6

		पूर्ण info; /* क्रम QLA84_MGMT_GET_INFO */
	पूर्ण u;
पूर्ण;

काष्ठा qla84_msg_mgmt अणु
	uपूर्णांक16_t cmd;
#घोषणा QLA84_MGMT_READ_MEM     0x00
#घोषणा QLA84_MGMT_WRITE_MEM    0x01
#घोषणा QLA84_MGMT_CHNG_CONFIG  0x02
#घोषणा QLA84_MGMT_GET_INFO     0x03
	uपूर्णांक16_t rsrvd;
	काष्ठा qla84_mgmt_param mgmtp;/* parameters क्रम cmd */
	uपूर्णांक32_t len; /* bytes in payload following this काष्ठा */
	uपूर्णांक8_t payload[0]; /* payload क्रम cmd */
पूर्ण;

काष्ठा qla_bsg_a84_mgmt अणु
	काष्ठा qla84_msg_mgmt mgmt;
पूर्ण __attribute__ ((packed));

काष्ठा qla_scsi_addr अणु
	uपूर्णांक16_t bus;
	uपूर्णांक16_t target;
पूर्ण __attribute__ ((packed));

काष्ठा qla_ext_dest_addr अणु
	जोड़ अणु
		uपूर्णांक8_t wwnn[8];
		uपूर्णांक8_t wwpn[8];
		uपूर्णांक8_t id[4];
		काष्ठा qla_scsi_addr scsi_addr;
	पूर्ण dest_addr;
	uपूर्णांक16_t dest_type;
#घोषणा	EXT_DEF_TYPE_WWPN	2
	uपूर्णांक16_t lun;
	uपूर्णांक16_t padding[2];
पूर्ण __attribute__ ((packed));

काष्ठा qla_port_param अणु
	काष्ठा qla_ext_dest_addr fc_scsi_addr;
	uपूर्णांक16_t mode;
	uपूर्णांक16_t speed;
पूर्ण __attribute__ ((packed));


/* FRU VPD */

#घोषणा MAX_FRU_SIZE	36

काष्ठा qla_field_address अणु
	uपूर्णांक16_t offset;
	uपूर्णांक16_t device;
	uपूर्णांक16_t option;
पूर्ण __packed;

काष्ठा qla_field_info अणु
	uपूर्णांक8_t version[MAX_FRU_SIZE];
पूर्ण __packed;

काष्ठा qla_image_version अणु
	काष्ठा qla_field_address field_address;
	काष्ठा qla_field_info field_info;
पूर्ण __packed;

काष्ठा qla_image_version_list अणु
	uपूर्णांक32_t count;
	काष्ठा qla_image_version version[0];
पूर्ण __packed;

काष्ठा qla_status_reg अणु
	काष्ठा qla_field_address field_address;
	uपूर्णांक8_t status_reg;
	uपूर्णांक8_t reserved[7];
पूर्ण __packed;

काष्ठा qla_i2c_access अणु
	uपूर्णांक16_t device;
	uपूर्णांक16_t offset;
	uपूर्णांक16_t option;
	uपूर्णांक16_t length;
	uपूर्णांक8_t  buffer[0x40];
पूर्ण __packed;

/* 26xx serdes रेजिस्टर पूर्णांकerface */

/* serdes reg commands */
#घोषणा INT_SC_SERDES_READ_REG		1
#घोषणा INT_SC_SERDES_WRITE_REG		2

काष्ठा qla_serdes_reg अणु
	uपूर्णांक16_t cmd;
	uपूर्णांक16_t addr;
	uपूर्णांक16_t val;
पूर्ण __packed;

काष्ठा qla_serdes_reg_ex अणु
	uपूर्णांक16_t cmd;
	uपूर्णांक32_t addr;
	uपूर्णांक32_t val;
पूर्ण __packed;

काष्ठा qla_flash_update_caps अणु
	uपूर्णांक64_t  capabilities;
	uपूर्णांक32_t  outage_duration;
	uपूर्णांक8_t   reserved[20];
पूर्ण __packed;

/* BB_CR Status */
#घोषणा QLA_BBCR_STATUS_DISABLED       0
#घोषणा QLA_BBCR_STATUS_ENABLED        1
#घोषणा QLA_BBCR_STATUS_UNKNOWN        2

/* BB_CR State */
#घोषणा QLA_BBCR_STATE_OFFLINE         0
#घोषणा QLA_BBCR_STATE_ONLINE          1

/* BB_CR Offline Reason Code */
#घोषणा QLA_BBCR_REASON_PORT_SPEED     1
#घोषणा QLA_BBCR_REASON_PEER_PORT      2
#घोषणा QLA_BBCR_REASON_SWITCH         3
#घोषणा QLA_BBCR_REASON_LOGIN_REJECT   4

काष्ठा  qla_bbcr_data अणु
	uपूर्णांक8_t   status;         /* 1 - enabled, 0 - Disabled */
	uपूर्णांक8_t   state;          /* 1 - online, 0 - offline */
	uपूर्णांक8_t   configured_bbscn;       /* 0-15 */
	uपूर्णांक8_t   negotiated_bbscn;       /* 0-15 */
	uपूर्णांक8_t   offline_reason_code;
	uपूर्णांक16_t  mbx1;			/* Port state */
	uपूर्णांक8_t   reserved[9];
पूर्ण __packed;

काष्ठा qla_dport_diag अणु
	uपूर्णांक16_t options;
	uपूर्णांक32_t buf[16];
	uपूर्णांक8_t  unused[62];
पूर्ण __packed;

/* D_Port options */
#घोषणा QLA_DPORT_RESULT	0x0
#घोषणा QLA_DPORT_START		0x2

/* active images in flash */
काष्ठा qla_active_regions अणु
	uपूर्णांक8_t global_image;
	uपूर्णांक8_t board_config;
	uपूर्णांक8_t vpd_nvram;
	uपूर्णांक8_t npiv_config_0_1;
	uपूर्णांक8_t npiv_config_2_3;
	uपूर्णांक8_t reserved[32];
पूर्ण __packed;

#पूर्ण_अगर
