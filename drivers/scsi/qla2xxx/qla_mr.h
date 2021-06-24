<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#अगर_अघोषित __QLA_MR_H
#घोषणा __QLA_MR_H

#समावेश "qla_dsd.h"

/*
 * The PCI VenकरोrID and DeviceID क्रम our board.
 */
#घोषणा PCI_DEVICE_ID_QLOGIC_ISPF001		0xF001

/* FX00 specअगरic definitions */

#घोषणा FX00_COMMAND_TYPE_7	0x07	/* Command Type 7 entry क्रम 7XXX */
काष्ठा cmd_type_7_fx00 अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */
	uपूर्णांक8_t reserved_0;
	uपूर्णांक8_t port_path_ctrl;
	uपूर्णांक16_t reserved_1;

	__le16 tgt_idx;		/* Target Idx. */
	uपूर्णांक16_t समयout;		/* Command समयout. */

	__le16 dseg_count;		/* Data segment count. */
	uपूर्णांक8_t	scsi_rsp_dsd_len;
	uपूर्णांक8_t reserved_2;

	काष्ठा scsi_lun lun;		/* LUN (LE). */

	uपूर्णांक8_t cntrl_flags;

	uपूर्णांक8_t task_mgmt_flags;	/* Task management flags. */

	uपूर्णांक8_t task;

	uपूर्णांक8_t crn;

	uपूर्णांक8_t fcp_cdb[MAX_CMDSZ];	/* SCSI command words. */
	__le32 byte_count;		/* Total byte count. */

	काष्ठा dsd64 dsd;
पूर्ण;

#घोषणा	STATUS_TYPE_FX00	0x01		/* Status entry. */
काष्ठा sts_entry_fx00 अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */
	uपूर्णांक32_t reserved_3;		/* System handle. */

	__le16 comp_status;		/* Completion status. */
	uपूर्णांक16_t reserved_0;		/* OX_ID used by the firmware. */

	__le32 residual_len;		/* FW calc residual transfer length. */

	uपूर्णांक16_t reserved_1;
	uपूर्णांक16_t state_flags;		/* State flags. */

	uपूर्णांक16_t reserved_2;
	__le16 scsi_status;		/* SCSI status. */

	uपूर्णांक32_t sense_len;		/* FCP SENSE length. */
	uपूर्णांक8_t data[32];		/* FCP response/sense inक्रमmation. */
पूर्ण;


#घोषणा MAX_HANDLE_COUNT	15
#घोषणा MULTI_STATUS_TYPE_FX00	0x0D

काष्ठा multi_sts_entry_fx00 अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t handle_count;
	uपूर्णांक8_t entry_status;

	__le32 handles[MAX_HANDLE_COUNT];
पूर्ण;

#घोषणा TSK_MGMT_IOCB_TYPE_FX00		0x05
काष्ठा tsk_mgmt_entry_fx00 अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */

	uपूर्णांक32_t reserved_0;

	__le16 tgt_id;		/* Target Idx. */

	uपूर्णांक16_t reserved_1;
	uपूर्णांक16_t reserved_3;
	uपूर्णांक16_t reserved_4;

	काष्ठा scsi_lun lun;		/* LUN (LE). */

	__le32 control_flags;		/* Control Flags. */

	uपूर्णांक8_t reserved_2[32];
पूर्ण;


#घोषणा	ABORT_IOCB_TYPE_FX00	0x08		/* Abort IOCB status. */
काष्ठा पात_iocb_entry_fx00 अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */
	__le32 reserved_0;

	__le16 tgt_id_sts;		/* Completion status. */
	__le16 options;

	uपूर्णांक32_t पात_handle;		/* System handle. */
	__le32 reserved_2;

	__le16 req_que_no;
	uपूर्णांक8_t reserved_1[38];
पूर्ण;

#घोषणा IOCTL_IOSB_TYPE_FX00	0x0C
काष्ठा ioctl_iocb_entry_fx00 अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */
	uपूर्णांक32_t reserved_0;		/* System handle. */

	uपूर्णांक16_t comp_func_num;
	__le16 fw_iotcl_flags;

	__le32 dataword_r;		/* Data word वापसed */
	uपूर्णांक32_t adapid;		/* Adapter ID */
	uपूर्णांक32_t dataword_r_extra;

	__le32 seq_no;
	uपूर्णांक8_t reserved_2[20];
	uपूर्णांक32_t residuallen;
	__le32 status;
पूर्ण;

#घोषणा STATUS_CONT_TYPE_FX00 0x04

#घोषणा FX00_IOCB_TYPE		0x0B
काष्ठा fxdisc_entry_fx00 अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System Defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */
	__le32 reserved_0;		/* System handle. */

	__le16 func_num;
	__le16 req_xfrcnt;
	__le16 req_dsdcnt;
	__le16 rsp_xfrcnt;
	__le16 rsp_dsdcnt;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t reserved_1;

	/*
	 * Use array size 1 below to prevent that Coverity complains about
	 * the append_dsd64() calls क्रम the two arrays below.
	 */
	काष्ठा dsd64 dseg_rq[1];
	काष्ठा dsd64 dseg_rsp[1];

	__le32 dataword;
	__le32 adapid;
	__le32 adapid_hi;
	__le32 dataword_extra;
पूर्ण;

काष्ठा qlafx00_tgt_node_info अणु
	uपूर्णांक8_t tgt_node_wwpn[WWN_SIZE];
	uपूर्णांक8_t tgt_node_wwnn[WWN_SIZE];
	uपूर्णांक32_t tgt_node_state;
	uपूर्णांक8_t reserved[128];
	uपूर्णांक32_t reserved_1[8];
	uपूर्णांक64_t reserved_2[4];
पूर्ण __packed;

#घोषणा QLAFX00_TGT_NODE_INFO माप(काष्ठा qlafx00_tgt_node_info)

#घोषणा QLAFX00_LINK_STATUS_DOWN	0x10
#घोषणा QLAFX00_LINK_STATUS_UP		0x11

#घोषणा QLAFX00_PORT_SPEED_2G	0x2
#घोषणा QLAFX00_PORT_SPEED_4G	0x4
#घोषणा QLAFX00_PORT_SPEED_8G	0x8
#घोषणा QLAFX00_PORT_SPEED_10G	0xa
काष्ठा port_info_data अणु
	uपूर्णांक8_t         port_state;
	uपूर्णांक8_t         port_type;
	uपूर्णांक16_t        port_identअगरier;
	uपूर्णांक32_t        up_port_state;
	uपूर्णांक8_t         fw_ver_num[32];
	uपूर्णांक8_t         portal_attrib;
	uपूर्णांक16_t        host_option;
	uपूर्णांक8_t         reset_delay;
	uपूर्णांक8_t         pdwn_retry_cnt;
	uपूर्णांक16_t        max_luns2tgt;
	uपूर्णांक8_t         risc_ver;
	uपूर्णांक8_t         pconn_option;
	uपूर्णांक16_t        risc_option;
	uपूर्णांक16_t        max_frame_len;
	uपूर्णांक16_t        max_iocb_alloc;
	uपूर्णांक16_t        exec_throttle;
	uपूर्णांक8_t         retry_cnt;
	uपूर्णांक8_t         retry_delay;
	uपूर्णांक8_t         port_name[8];
	uपूर्णांक8_t         port_id[3];
	uपूर्णांक8_t         link_status;
	uपूर्णांक8_t         plink_rate;
	uपूर्णांक32_t        link_config;
	uपूर्णांक16_t        adap_haddr;
	uपूर्णांक8_t         tgt_disc;
	uपूर्णांक8_t         log_tout;
	uपूर्णांक8_t         node_name[8];
	uपूर्णांक16_t        erisc_opt1;
	uपूर्णांक8_t         resp_acc_पंचांगr;
	uपूर्णांक8_t         पूर्णांकr_del_पंचांगr;
	uपूर्णांक8_t         erisc_opt2;
	uपूर्णांक8_t         alt_port_name[8];
	uपूर्णांक8_t         alt_node_name[8];
	uपूर्णांक8_t         link_करोwn_tout;
	uपूर्णांक8_t         conn_type;
	uपूर्णांक8_t         fc_fw_mode;
	uपूर्णांक32_t        uiReserved[48];
पूर्ण __packed;

/* OS Type Designations */
#घोषणा OS_TYPE_UNKNOWN             0
#घोषणा OS_TYPE_LINUX               2

/* Linux Info */
#घोषणा SYSNAME_LENGTH              128
#घोषणा NODENAME_LENGTH             64
#घोषणा RELEASE_LENGTH              64
#घोषणा VERSION_LENGTH              64
#घोषणा MACHINE_LENGTH              64
#घोषणा DOMNAME_LENGTH              64

काष्ठा host_प्रणाली_info अणु
	uपूर्णांक32_t os_type;
	अक्षर    sysname[SYSNAME_LENGTH];
	अक्षर    nodename[NODENAME_LENGTH];
	अक्षर    release[RELEASE_LENGTH];
	अक्षर    version[VERSION_LENGTH];
	अक्षर    machine[MACHINE_LENGTH];
	अक्षर    करोमुख्यname[DOMNAME_LENGTH];
	अक्षर    hostdriver[VERSION_LENGTH];
	uपूर्णांक32_t reserved[64];
पूर्ण __packed;

काष्ठा रेजिस्टर_host_info अणु
	काष्ठा host_प्रणाली_info     hsi;	/* host प्रणाली info */
	uपूर्णांक64_t        utc;			/* UTC (प्रणाली समय) */
	uपूर्णांक32_t        reserved[64];		/* future additions */
पूर्ण __packed;


#घोषणा QLAFX00_PORT_DATA_INFO (माप(काष्ठा port_info_data))
#घोषणा QLAFX00_TGT_NODE_LIST_SIZE (माप(uपूर्णांक32_t) * 32)

काष्ठा config_info_data अणु
	uपूर्णांक8_t		model_num[16];
	uपूर्णांक8_t		model_description[80];
	uपूर्णांक8_t		reserved0[160];
	uपूर्णांक8_t		symbolic_name[64];
	uपूर्णांक8_t		serial_num[32];
	uपूर्णांक8_t		hw_version[16];
	uपूर्णांक8_t		fw_version[16];
	uपूर्णांक8_t		uboot_version[16];
	uपूर्णांक8_t		fru_serial_num[32];

	uपूर्णांक8_t		fc_port_count;
	uपूर्णांक8_t		iscsi_port_count;
	uपूर्णांक8_t		reserved1[2];

	uपूर्णांक8_t		mode;
	uपूर्णांक8_t		log_level;
	uपूर्णांक8_t		reserved2[2];

	uपूर्णांक32_t	log_size;

	uपूर्णांक8_t		tgt_pres_mode;
	uपूर्णांक8_t		iqn_flags;
	uपूर्णांक8_t		lun_mapping;

	uपूर्णांक64_t	adapter_id;

	uपूर्णांक32_t	cluster_key_len;
	uपूर्णांक8_t		cluster_key[16];

	uपूर्णांक64_t	cluster_master_id;
	uपूर्णांक64_t	cluster_slave_id;
	uपूर्णांक8_t		cluster_flags;
	uपूर्णांक32_t	enabled_capabilities;
	uपूर्णांक32_t	nominal_temp_value;
पूर्ण __packed;

#घोषणा FXDISC_GET_CONFIG_INFO		0x01
#घोषणा FXDISC_GET_PORT_INFO		0x02
#घोषणा FXDISC_GET_TGT_NODE_INFO	0x80
#घोषणा FXDISC_GET_TGT_NODE_LIST	0x81
#घोषणा FXDISC_REG_HOST_INFO		0x99
#घोषणा FXDISC_ABORT_IOCTL		0xff

#घोषणा QLAFX00_HBA_ICNTRL_REG		0x20B08
#घोषणा QLAFX00_ICR_ENB_MASK            0x80000000
#घोषणा QLAFX00_ICR_DIS_MASK            0x7fffffff
#घोषणा QLAFX00_HST_RST_REG		0x18264
#घोषणा QLAFX00_SOC_TEMP_REG		0x184C4
#घोषणा QLAFX00_HST_TO_HBA_REG		0x20A04
#घोषणा QLAFX00_HBA_TO_HOST_REG		0x21B70
#घोषणा QLAFX00_HST_INT_STS_BITS	0x7
#घोषणा QLAFX00_BAR1_BASE_ADDR_REG	0x40018
#घोषणा QLAFX00_PEX0_WIN0_BASE_ADDR_REG	0x41824

#घोषणा QLAFX00_INTR_MB_CMPLT		0x1
#घोषणा QLAFX00_INTR_RSP_CMPLT		0x2
#घोषणा QLAFX00_INTR_ASYNC_CMPLT	0x4

#घोषणा QLAFX00_MBA_SYSTEM_ERR		0x8002
#घोषणा QLAFX00_MBA_TEMP_OVER		0x8005
#घोषणा QLAFX00_MBA_TEMP_NORM		0x8006
#घोषणा	QLAFX00_MBA_TEMP_CRIT		0x8007
#घोषणा QLAFX00_MBA_LINK_UP		0x8011
#घोषणा QLAFX00_MBA_LINK_DOWN		0x8012
#घोषणा QLAFX00_MBA_PORT_UPDATE		0x8014
#घोषणा QLAFX00_MBA_SHUTDOWN_RQSTD	0x8062

#घोषणा SOC_SW_RST_CONTROL_REG_CORE0     0x0020800
#घोषणा SOC_FABRIC_RST_CONTROL_REG       0x0020840
#घोषणा SOC_FABRIC_CONTROL_REG           0x0020200
#घोषणा SOC_FABRIC_CONFIG_REG            0x0020204
#घोषणा SOC_PWR_MANAGEMENT_PWR_DOWN_REG  0x001820C

#घोषणा SOC_INTERRUPT_SOURCE_I_CONTROL_REG     0x0020B00
#घोषणा SOC_CORE_TIMER_REG                     0x0021850
#घोषणा SOC_IRQ_ACK_REG                        0x00218b4

#घोषणा CONTINUE_A64_TYPE_FX00	0x03	/* Continuation entry. */

#घोषणा QLAFX00_SET_HST_INTR(ha, value) \
	wrt_reg_dword((ha)->cregbase + QLAFX00_HST_TO_HBA_REG, \
	value)

#घोषणा QLAFX00_CLR_HST_INTR(ha, value) \
	wrt_reg_dword((ha)->cregbase + QLAFX00_HBA_TO_HOST_REG, \
	~value)

#घोषणा QLAFX00_RD_INTR_REG(ha) \
	rd_reg_dword((ha)->cregbase + QLAFX00_HBA_TO_HOST_REG)

#घोषणा QLAFX00_CLR_INTR_REG(ha, value) \
	wrt_reg_dword((ha)->cregbase + QLAFX00_HBA_TO_HOST_REG, \
	~value)

#घोषणा QLAFX00_SET_HBA_SOC_REG(ha, off, val)\
	wrt_reg_dword((ha)->cregbase + off, val)

#घोषणा QLAFX00_GET_HBA_SOC_REG(ha, off)\
	rd_reg_dword((ha)->cregbase + off)

#घोषणा QLAFX00_HBA_RST_REG(ha, val)\
	wrt_reg_dword((ha)->cregbase + QLAFX00_HST_RST_REG, val)

#घोषणा QLAFX00_RD_ICNTRL_REG(ha) \
	rd_reg_dword((ha)->cregbase + QLAFX00_HBA_ICNTRL_REG)

#घोषणा QLAFX00_ENABLE_ICNTRL_REG(ha) \
	wrt_reg_dword((ha)->cregbase + QLAFX00_HBA_ICNTRL_REG, \
	(QLAFX00_GET_HBA_SOC_REG(ha, QLAFX00_HBA_ICNTRL_REG) | \
	 QLAFX00_ICR_ENB_MASK))

#घोषणा QLAFX00_DISABLE_ICNTRL_REG(ha) \
	wrt_reg_dword((ha)->cregbase + QLAFX00_HBA_ICNTRL_REG, \
	(QLAFX00_GET_HBA_SOC_REG(ha, QLAFX00_HBA_ICNTRL_REG) & \
	 QLAFX00_ICR_DIS_MASK))

#घोषणा QLAFX00_RD_REG(ha, off) \
	rd_reg_dword((ha)->cregbase + off)

#घोषणा QLAFX00_WR_REG(ha, off, val) \
	wrt_reg_dword((ha)->cregbase + off, val)

काष्ठा qla_mt_iocb_rqst_fx00 अणु
	__le32 reserved_0;

	__le16 func_type;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t reserved_1;

	__le32 dataword;

	__le32 adapid;
	__le32 adapid_hi;

	__le32 dataword_extra;

	__le16 req_len;
	__le16 reserved_2;

	__le16 rsp_len;
	__le16 reserved_3;
पूर्ण;

काष्ठा qla_mt_iocb_rsp_fx00 अणु
	uपूर्णांक32_t reserved_1;

	uपूर्णांक16_t func_type;
	__le16 ioctl_flags;

	__le32 ioctl_data;

	uपूर्णांक32_t adapid;
	uपूर्णांक32_t adapid_hi;

	uपूर्णांक32_t reserved_2;
	__le32 seq_number;

	uपूर्णांक8_t reserved_3[20];

	पूर्णांक32_t res_count;

	__le32 status;
पूर्ण;


#घोषणा MAILBOX_REGISTER_COUNT_FX00	16
#घोषणा AEN_MAILBOX_REGISTER_COUNT_FX00	8
#घोषणा MAX_FIBRE_DEVICES_FX00	512
#घोषणा MAX_LUNS_FX00		0x1024
#घोषणा MAX_TARGETS_FX00	MAX_ISA_DEVICES
#घोषणा REQUEST_ENTRY_CNT_FX00		512	/* Number of request entries. */
#घोषणा RESPONSE_ENTRY_CNT_FX00		256	/* Number of response entries.*/

/*
 * Firmware state codes क्रम QLAFX00 adapters
 */
#घोषणा FSTATE_FX00_CONFIG_WAIT     0x0000	/* Waiting क्रम driver to issue
						 * Initialize FW Mbox cmd
						 */
#घोषणा FSTATE_FX00_INITIALIZED     0x1000	/* FW has been initialized by
						 * the driver
						 */

#घोषणा FX00_DEF_RATOV	10

काष्ठा mr_data_fx00 अणु
	uपूर्णांक8_t	symbolic_name[64];
	uपूर्णांक8_t	serial_num[32];
	uपूर्णांक8_t	hw_version[16];
	uपूर्णांक8_t	fw_version[16];
	uपूर्णांक8_t	uboot_version[16];
	uपूर्णांक8_t	fru_serial_num[32];
	fc_port_t       fcport;		/* fcport used क्रम requests
					 * that are not linked
					 * to a particular target
					 */
	uपूर्णांक8_t fw_hbt_en;
	uपूर्णांक8_t fw_hbt_cnt;
	uपूर्णांक8_t fw_hbt_miss_cnt;
	uपूर्णांक32_t old_fw_hbt_cnt;
	uपूर्णांक16_t fw_reset_समयr_tick;
	uपूर्णांक8_t fw_reset_समयr_exp;
	uपूर्णांक16_t fw_critemp_समयr_tick;
	uपूर्णांक32_t old_aenmbx0_state;
	uपूर्णांक32_t critical_temperature;
	bool extended_io_enabled;
	bool host_info_resend;
	uपूर्णांक8_t hinfo_resend_समयr_tick;
पूर्ण;

#घोषणा QLAFX00_EXTENDED_IO_EN_MASK    0x20

/*
 * SoC Junction Temperature is stored in
 * bits 9:1 of SoC Junction Temperature Register
 * in a firmware specअगरic क्रमmat क्रमmat.
 * To get the temperature in Celsius degrees
 * the value from this bitfiled should be converted
 * using this क्रमmula:
 * Temperature (degrees C) = ((3,153,000 - (10,000 * X)) / 13,825)
 * where X is the bit field value
 * this macro पढ़ोs the रेजिस्टर, extracts the bitfield value,
 * perक्रमms the calcualtions and वापसs temperature in Celsius
 */
#घोषणा QLAFX00_GET_TEMPERATURE(ha) ((3153000 - (10000 * \
	((QLAFX00_RD_REG(ha, QLAFX00_SOC_TEMP_REG) & 0x3FE) >> 1))) / 13825)


#घोषणा QLAFX00_LOOP_DOWN_TIME		615     /* 600 */
#घोषणा QLAFX00_HEARTBEAT_INTERVAL	6	/* number of seconds */
#घोषणा QLAFX00_HEARTBEAT_MISS_CNT	3	/* number of miss */
#घोषणा QLAFX00_RESET_INTERVAL		120	/* number of seconds */
#घोषणा QLAFX00_MAX_RESET_INTERVAL	600	/* number of seconds */
#घोषणा QLAFX00_CRITEMP_INTERVAL	60	/* number of seconds */
#घोषणा QLAFX00_HINFO_RESEND_INTERVAL	60	/* number of seconds */

#घोषणा QLAFX00_CRITEMP_THRSHLD		80	/* Celsius degrees */

/* Max conncurrent IOs that can be queued */
#घोषणा QLAFX00_MAX_CANQUEUE		1024

/* IOCTL IOCB पात success */
#घोषणा QLAFX00_IOCTL_ICOB_ABORT_SUCCESS	0x68

#पूर्ण_अगर
