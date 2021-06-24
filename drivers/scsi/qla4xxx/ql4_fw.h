<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c)  2003-2013 QLogic Corporation
 */

#अगर_अघोषित _QLA4X_FW_H
#घोषणा _QLA4X_FW_H


#घोषणा MAX_PRST_DEV_DB_ENTRIES		64
#घोषणा MIN_DISC_DEV_DB_ENTRY		MAX_PRST_DEV_DB_ENTRIES
#घोषणा MAX_DEV_DB_ENTRIES		512
#घोषणा MAX_DEV_DB_ENTRIES_40XX		256

/*************************************************************************
 *
 *		ISP 4010 I/O Register Set Structure and Definitions
 *
 *************************************************************************/

काष्ठा port_ctrl_stat_regs अणु
	__le32 ext_hw_conf;	/* 0x50  R/W */
	__le32 rsrvd0;		/* 0x54 */
	__le32 port_ctrl;	/* 0x58 */
	__le32 port_status;	/* 0x5c */
	__le32 rsrvd1[32];	/* 0x60-0xdf */
	__le32 gp_out;		/* 0xe0 */
	__le32 gp_in;		/* 0xe4 */
	__le32 rsrvd2[5];	/* 0xe8-0xfb */
	__le32 port_err_status; /* 0xfc */
पूर्ण;

काष्ठा host_mem_cfg_regs अणु
	__le32 rsrvd0[12];	/* 0x50-0x79 */
	__le32 req_q_out;	/* 0x80 */
	__le32 rsrvd1[31];	/* 0x84-0xFF */
पूर्ण;

/*
 * ISP 82xx I/O Register Set काष्ठाure definitions.
 */
काष्ठा device_reg_82xx अणु
	__le32 req_q_out;	/* 0x0000 (R): Request Queue out-Poपूर्णांकer. */
	__le32 reserve1[63];	/* Request Queue out-Poपूर्णांकer. (64 * 4) */
	__le32 rsp_q_in;	/* 0x0100 (R/W): Response Queue In-Poपूर्णांकer. */
	__le32 reserve2[63];	/* Response Queue In-Poपूर्णांकer. */
	__le32 rsp_q_out;	/* 0x0200 (R/W): Response Queue Out-Poपूर्णांकer. */
	__le32 reserve3[63];	/* Response Queue Out-Poपूर्णांकer. */

	__le32 mailbox_in[8];	/* 0x0300 (R/W): Mail box In रेजिस्टरs */
	__le32 reserve4[24];
	__le32 hपूर्णांक;		/* 0x0380 (R/W): Host पूर्णांकerrupt रेजिस्टर */
#घोषणा HINT_MBX_INT_PENDING	BIT_0
	__le32 reserve5[31];
	__le32 mailbox_out[8];	/* 0x0400 (R): Mail box Out रेजिस्टरs */
	__le32 reserve6[56];

	__le32 host_status;	/* Offset 0x500 (R): host status */
#घोषणा HSRX_RISC_MB_INT	BIT_0  /* RISC to Host Mailbox पूर्णांकerrupt */
#घोषणा HSRX_RISC_IOCB_INT	BIT_1  /* RISC to Host IOCB पूर्णांकerrupt */

	__le32 host_पूर्णांक;	/* Offset 0x0504 (R/W): Interrupt status. */
#घोषणा ISRX_82XX_RISC_INT	BIT_0 /* RISC पूर्णांकerrupt. */
पूर्ण;

/* ISP 83xx I/O Register Set काष्ठाure */
काष्ठा device_reg_83xx अणु
	__le32 mailbox_in[16];	/* 0x0000 */
	__le32 reserve1[496];	/* 0x0040 */
	__le32 mailbox_out[16];	/* 0x0800 */
	__le32 reserve2[496];
	__le32 mbox_पूर्णांक;	/* 0x1000 */
	__le32 reserve3[63];
	__le32 req_q_out;	/* 0x1100 */
	__le32 reserve4[63];

	__le32 rsp_q_in;	/* 0x1200 */
	__le32 reserve5[1919];

	__le32 req_q_in;	/* 0x3000 */
	__le32 reserve6[3];
	__le32 iocb_पूर्णांक_mask;	/* 0x3010 */
	__le32 reserve7[3];
	__le32 rsp_q_out;	/* 0x3020 */
	__le32 reserve8[3];
	__le32 anonymousbuff;	/* 0x3030 */
	__le32 mb_पूर्णांक_mask;	/* 0x3034 */

	__le32 host_पूर्णांकr;	/* 0x3038 - Host Interrupt Register */
	__le32 risc_पूर्णांकr;	/* 0x303C - RISC Interrupt Register */
	__le32 reserve9[544];
	__le32 leg_पूर्णांक_ptr;	/* 0x38C0 - Legacy Interrupt Poपूर्णांकer Register */
	__le32 leg_पूर्णांक_trig;	/* 0x38C4 - Legacy Interrupt Trigger Control */
	__le32 leg_पूर्णांक_mask;	/* 0x38C8 - Legacy Interrupt Mask Register */
पूर्ण;

#घोषणा INT_ENABLE_FW_MB	(1 << 2)
#घोषणा INT_MASK_FW_MB		(1 << 2)

/*  remote रेजिस्टर set (access via PCI memory पढ़ो/ग_लिखो) */
काष्ठा isp_reg अणु
#घोषणा MBOX_REG_COUNT 8
	__le32 mailbox[MBOX_REG_COUNT];

	__le32 flash_address;	/* 0x20 */
	__le32 flash_data;
	__le32 ctrl_status;

	जोड़ अणु
		काष्ठा अणु
			__le32 nvram;
			__le32 reserved1[2]; /* 0x30 */
		पूर्ण __attribute__ ((packed)) isp4010;
		काष्ठा अणु
			__le32 पूर्णांकr_mask;
			__le32 nvram; /* 0x30 */
			__le32 semaphore;
		पूर्ण __attribute__ ((packed)) isp4022;
	पूर्ण u1;

	__le32 req_q_in;    /* SCSI Request Queue Producer Index */
	__le32 rsp_q_out;   /* SCSI Completion Queue Consumer Index */

	__le32 reserved2[4];	/* 0x40 */

	जोड़ अणु
		काष्ठा अणु
			__le32 ext_hw_conf; /* 0x50 */
			__le32 flow_ctrl;
			__le32 port_ctrl;
			__le32 port_status;

			__le32 reserved3[8]; /* 0x60 */

			__le32 req_q_out; /* 0x80 */

			__le32 reserved4[23]; /* 0x84 */

			__le32 gp_out; /* 0xe0 */
			__le32 gp_in;

			__le32 reserved5[5];

			__le32 port_err_status; /* 0xfc */
		पूर्ण __attribute__ ((packed)) isp4010;
		काष्ठा अणु
			जोड़ अणु
				काष्ठा port_ctrl_stat_regs p0;
				काष्ठा host_mem_cfg_regs p1;
			पूर्ण;
		पूर्ण __attribute__ ((packed)) isp4022;
	पूर्ण u2;
पूर्ण;				/* 256 x100 */


/* Semaphore Defines क्रम 4010 */
#घोषणा QL4010_DRVR_SEM_BITS	0x00000030
#घोषणा QL4010_GPIO_SEM_BITS	0x000000c0
#घोषणा QL4010_SDRAM_SEM_BITS	0x00000300
#घोषणा QL4010_PHY_SEM_BITS	0x00000c00
#घोषणा QL4010_NVRAM_SEM_BITS	0x00003000
#घोषणा QL4010_FLASH_SEM_BITS	0x0000c000

#घोषणा QL4010_DRVR_SEM_MASK	0x00300000
#घोषणा QL4010_GPIO_SEM_MASK	0x00c00000
#घोषणा QL4010_SDRAM_SEM_MASK	0x03000000
#घोषणा QL4010_PHY_SEM_MASK	0x0c000000
#घोषणा QL4010_NVRAM_SEM_MASK	0x30000000
#घोषणा QL4010_FLASH_SEM_MASK	0xc0000000

/* Semaphore Defines क्रम 4022 */
#घोषणा QL4022_RESOURCE_MASK_BASE_CODE 0x7
#घोषणा QL4022_RESOURCE_BITS_BASE_CODE 0x4


#घोषणा QL4022_DRVR_SEM_MASK	(QL4022_RESOURCE_MASK_BASE_CODE << (1+16))
#घोषणा QL4022_DDR_RAM_SEM_MASK (QL4022_RESOURCE_MASK_BASE_CODE << (4+16))
#घोषणा QL4022_PHY_GIO_SEM_MASK (QL4022_RESOURCE_MASK_BASE_CODE << (7+16))
#घोषणा QL4022_NVRAM_SEM_MASK	(QL4022_RESOURCE_MASK_BASE_CODE << (10+16))
#घोषणा QL4022_FLASH_SEM_MASK	(QL4022_RESOURCE_MASK_BASE_CODE << (13+16))

/* nvram address क्रम 4032 */
#घोषणा NVRAM_PORT0_BOOT_MODE		0x03b1
#घोषणा NVRAM_PORT0_BOOT_PRI_TGT	0x03b2
#घोषणा NVRAM_PORT0_BOOT_SEC_TGT	0x03bb
#घोषणा NVRAM_PORT1_BOOT_MODE		0x07b1
#घोषणा NVRAM_PORT1_BOOT_PRI_TGT	0x07b2
#घोषणा NVRAM_PORT1_BOOT_SEC_TGT	0x07bb


/* Page # defines क्रम 4022 */
#घोषणा PORT_CTRL_STAT_PAGE			0	/* 4022 */
#घोषणा HOST_MEM_CFG_PAGE			1	/* 4022 */
#घोषणा LOCAL_RAM_CFG_PAGE			2	/* 4022 */
#घोषणा PROT_STAT_PAGE				3	/* 4022 */

/* Register Mask - sets corresponding mask bits in the upper word */
अटल अंतरभूत uपूर्णांक32_t set_rmask(uपूर्णांक32_t val)
अणु
	वापस (val & 0xffff) | (val << 16);
पूर्ण


अटल अंतरभूत uपूर्णांक32_t clr_rmask(uपूर्णांक32_t val)
अणु
	वापस 0 | (val << 16);
पूर्ण

/*  ctrl_status definitions */
#घोषणा CSR_SCSI_PAGE_SELECT			0x00000003
#घोषणा CSR_SCSI_INTR_ENABLE			0x00000004	/* 4010 */
#घोषणा CSR_SCSI_RESET_INTR			0x00000008
#घोषणा CSR_SCSI_COMPLETION_INTR		0x00000010
#घोषणा CSR_SCSI_PROCESSOR_INTR			0x00000020
#घोषणा CSR_INTR_RISC				0x00000040
#घोषणा CSR_BOOT_ENABLE				0x00000080
#घोषणा CSR_NET_PAGE_SELECT			0x00000300	/* 4010 */
#घोषणा CSR_FUNC_NUM				0x00000700	/* 4022 */
#घोषणा CSR_NET_RESET_INTR			0x00000800	/* 4010 */
#घोषणा CSR_FORCE_SOFT_RESET			0x00002000	/* 4022 */
#घोषणा CSR_FATAL_ERROR				0x00004000
#घोषणा CSR_SOFT_RESET				0x00008000
#घोषणा ISP_CONTROL_FN_MASK			CSR_FUNC_NUM
#घोषणा ISP_CONTROL_FN0_SCSI			0x0500
#घोषणा ISP_CONTROL_FN1_SCSI			0x0700

#घोषणा INTR_PENDING				(CSR_SCSI_COMPLETION_INTR |\
						 CSR_SCSI_PROCESSOR_INTR |\
						 CSR_SCSI_RESET_INTR)

/* ISP InterruptMask definitions */
#घोषणा IMR_SCSI_INTR_ENABLE			0x00000004	/* 4022 */

/* ISP 4022 nvram definitions */
#घोषणा NVR_WRITE_ENABLE			0x00000010	/* 4022 */

#घोषणा QL4010_NVRAM_SIZE			0x200
#घोषणा QL40X2_NVRAM_SIZE			0x800

/*  ISP port_status definitions */

/*  ISP Semaphore definitions */

/*  ISP General Purpose Output definitions */
#घोषणा GPOR_TOPCAT_RESET			0x00000004

/*  shaकरोw रेजिस्टरs (DMA'd from HA to प्रणाली memory.  पढ़ो only) */
काष्ठा shaकरोw_regs अणु
	/* SCSI Request Queue Consumer Index */
	__le32 req_q_out;	/*  0 x0   R */

	/* SCSI Completion Queue Producer Index */
	__le32 rsp_q_in;	/*  4 x4   R */
पूर्ण;		  /*  8 x8 */


/*  External hardware configuration रेजिस्टर */
जोड़ बाह्यal_hw_config_reg अणु
	काष्ठा अणु
		/* FIXME: Do we even need this?	 All values are
		 * referred to by 16 bit quantities.  Platक्रमm and
		 * endianess issues. */
		__le32 bReserved0:1;
		__le32 bSDRAMProtectionMethod:2;
		__le32 bSDRAMBanks:1;
		__le32 bSDRAMChipWidth:1;
		__le32 bSDRAMChipSize:2;
		__le32 bParityDisable:1;
		__le32 bExternalMemoryType:1;
		__le32 bFlashBIOSWriteEnable:1;
		__le32 bFlashUpperBankSelect:1;
		__le32 bWriteBurst:2;
		__le32 bReserved1:3;
		__le32 bMask:16;
	पूर्ण;
	uपूर्णांक32_t Asuपूर्णांक32_t;
पूर्ण;

/* 82XX Support  start */
/* 82xx Default FLT Addresses */
#घोषणा FA_FLASH_LAYOUT_ADDR_82		0xFC400
#घोषणा FA_FLASH_DESCR_ADDR_82		0xFC000
#घोषणा FA_BOOT_LOAD_ADDR_82		0x04000
#घोषणा FA_BOOT_CODE_ADDR_82		0x20000
#घोषणा FA_RISC_CODE_ADDR_82		0x40000
#घोषणा FA_GOLD_RISC_CODE_ADDR_82	0x80000
#घोषणा FA_FLASH_ISCSI_CHAP		0x540000
#घोषणा FA_FLASH_CHAP_SIZE		0xC0000
#घोषणा FA_FLASH_ISCSI_DDB		0x420000
#घोषणा FA_FLASH_DDB_SIZE		0x080000

/* Flash Description Table */
काष्ठा qla_fdt_layout अणु
	uपूर्णांक8_t sig[4];
	uपूर्णांक16_t version;
	uपूर्णांक16_t len;
	uपूर्णांक16_t checksum;
	uपूर्णांक8_t unused1[2];
	uपूर्णांक8_t model[16];
	uपूर्णांक16_t man_id;
	uपूर्णांक16_t id;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t erase_cmd;
	uपूर्णांक8_t alt_erase_cmd;
	uपूर्णांक8_t wrt_enable_cmd;
	uपूर्णांक8_t wrt_enable_bits;
	uपूर्णांक8_t wrt_sts_reg_cmd;
	uपूर्णांक8_t unprotect_sec_cmd;
	uपूर्णांक8_t पढ़ो_man_id_cmd;
	uपूर्णांक32_t block_size;
	uपूर्णांक32_t alt_block_size;
	uपूर्णांक32_t flash_size;
	uपूर्णांक32_t wrt_enable_data;
	uपूर्णांक8_t पढ़ो_id_addr_len;
	uपूर्णांक8_t wrt_disable_bits;
	uपूर्णांक8_t पढ़ो_dev_id_len;
	uपूर्णांक8_t chip_erase_cmd;
	uपूर्णांक16_t पढ़ो_समयout;
	uपूर्णांक8_t protect_sec_cmd;
	uपूर्णांक8_t unused2[65];
पूर्ण;

/* Flash Layout Table */

काष्ठा qla_flt_location अणु
	uपूर्णांक8_t sig[4];
	uपूर्णांक16_t start_lo;
	uपूर्णांक16_t start_hi;
	uपूर्णांक8_t version;
	uपूर्णांक8_t unused[5];
	uपूर्णांक16_t checksum;
पूर्ण;

काष्ठा qla_flt_header अणु
	uपूर्णांक16_t version;
	uपूर्णांक16_t length;
	uपूर्णांक16_t checksum;
	uपूर्णांक16_t unused;
पूर्ण;

/* 82xx FLT Regions */
#घोषणा FLT_REG_FDT		0x1a
#घोषणा FLT_REG_FLT		0x1c
#घोषणा FLT_REG_BOOTLOAD_82	0x72
#घोषणा FLT_REG_FW_82		0x74
#घोषणा FLT_REG_FW_82_1		0x97
#घोषणा FLT_REG_GOLD_FW_82	0x75
#घोषणा FLT_REG_BOOT_CODE_82	0x78
#घोषणा FLT_REG_ISCSI_PARAM	0x65
#घोषणा FLT_REG_ISCSI_CHAP	0x63
#घोषणा FLT_REG_ISCSI_DDB	0x6A

काष्ठा qla_flt_region अणु
	uपूर्णांक32_t code;
	uपूर्णांक32_t size;
	uपूर्णांक32_t start;
	uपूर्णांक32_t end;
पूर्ण;

/*************************************************************************
 *
 *		Mailbox Commands Structures and Definitions
 *
 *************************************************************************/

/*  Mailbox command definitions */
#घोषणा MBOX_CMD_ABOUT_FW			0x0009
#घोषणा MBOX_CMD_PING				0x000B
#घोषणा PING_IPV6_PROTOCOL_ENABLE		0x1
#घोषणा PING_IPV6_LINKLOCAL_ADDR		0x4
#घोषणा PING_IPV6_ADDR0				0x8
#घोषणा PING_IPV6_ADDR1				0xC
#घोषणा MBOX_CMD_ENABLE_INTRS			0x0010
#घोषणा INTR_DISABLE				0
#घोषणा INTR_ENABLE				1
#घोषणा MBOX_CMD_STOP_FW			0x0014
#घोषणा MBOX_CMD_ABORT_TASK			0x0015
#घोषणा MBOX_CMD_LUN_RESET			0x0016
#घोषणा MBOX_CMD_TARGET_WARM_RESET		0x0017
#घोषणा MBOX_CMD_GET_MANAGEMENT_DATA		0x001E
#घोषणा MBOX_CMD_GET_FW_STATUS			0x001F
#घोषणा MBOX_CMD_SET_ISNS_SERVICE		0x0021
#घोषणा ISNS_DISABLE				0
#घोषणा ISNS_ENABLE				1
#घोषणा MBOX_CMD_COPY_FLASH			0x0024
#घोषणा MBOX_CMD_WRITE_FLASH			0x0025
#घोषणा MBOX_CMD_READ_FLASH			0x0026
#घोषणा MBOX_CMD_CLEAR_DATABASE_ENTRY		0x0031
#घोषणा MBOX_CMD_CONN_OPEN			0x0074
#घोषणा MBOX_CMD_CONN_CLOSE_SESS_LOGOUT		0x0056
#घोषणा DDB_NOT_LOGGED_IN			0x09
#घोषणा LOGOUT_OPTION_CLOSE_SESSION		0x0002
#घोषणा LOGOUT_OPTION_RELOGIN			0x0004
#घोषणा LOGOUT_OPTION_FREE_DDB			0x0008
#घोषणा MBOX_CMD_SET_PARAM			0x0059
#घोषणा SET_DRVR_VERSION			0x200
#घोषणा MAX_DRVR_VER_LEN			24
#घोषणा MBOX_CMD_EXECUTE_IOCB_A64		0x005A
#घोषणा MBOX_CMD_INITIALIZE_FIRMWARE		0x0060
#घोषणा MBOX_CMD_GET_INIT_FW_CTRL_BLOCK		0x0061
#घोषणा MBOX_CMD_REQUEST_DATABASE_ENTRY		0x0062
#घोषणा MBOX_CMD_SET_DATABASE_ENTRY		0x0063
#घोषणा MBOX_CMD_GET_DATABASE_ENTRY		0x0064
#घोषणा DDB_DS_UNASSIGNED			0x00
#घोषणा DDB_DS_NO_CONNECTION_ACTIVE		0x01
#घोषणा DDB_DS_DISCOVERY			0x02
#घोषणा DDB_DS_SESSION_ACTIVE			0x04
#घोषणा DDB_DS_SESSION_FAILED			0x06
#घोषणा DDB_DS_LOGIN_IN_PROCESS			0x07
#घोषणा MBOX_CMD_GET_FW_STATE			0x0069
#घोषणा MBOX_CMD_GET_INIT_FW_CTRL_BLOCK_DEFAULTS 0x006A
#घोषणा MBOX_CMD_DIAG_TEST			0x0075
#घोषणा MBOX_CMD_GET_SYS_INFO			0x0078
#घोषणा MBOX_CMD_GET_NVRAM			0x0078	/* For 40xx */
#घोषणा MBOX_CMD_SET_NVRAM			0x0079	/* For 40xx */
#घोषणा MBOX_CMD_RESTORE_FACTORY_DEFAULTS	0x0087
#घोषणा MBOX_CMD_SET_ACB			0x0088
#घोषणा MBOX_CMD_GET_ACB			0x0089
#घोषणा MBOX_CMD_DISABLE_ACB			0x008A
#घोषणा MBOX_CMD_GET_IPV6_NEIGHBOR_CACHE	0x008B
#घोषणा MBOX_CMD_GET_IPV6_DEST_CACHE		0x008C
#घोषणा MBOX_CMD_GET_IPV6_DEF_ROUTER_LIST	0x008D
#घोषणा MBOX_CMD_GET_IPV6_LCL_PREFIX_LIST	0x008E
#घोषणा MBOX_CMD_SET_IPV6_NEIGHBOR_CACHE	0x0090
#घोषणा MBOX_CMD_GET_IP_ADDR_STATE		0x0091
#घोषणा MBOX_CMD_SEND_IPV6_ROUTER_SOL		0x0092
#घोषणा MBOX_CMD_GET_DB_ENTRY_CURRENT_IP_ADDR	0x0093
#घोषणा MBOX_CMD_SET_PORT_CONFIG		0x0122
#घोषणा MBOX_CMD_GET_PORT_CONFIG		0x0123
#घोषणा MBOX_CMD_SET_LED_CONFIG			0x0125
#घोषणा MBOX_CMD_GET_LED_CONFIG			0x0126
#घोषणा MBOX_CMD_MINIDUMP			0x0129

/* Port Config */
#घोषणा ENABLE_INTERNAL_LOOPBACK		0x04
#घोषणा ENABLE_EXTERNAL_LOOPBACK		0x08
#घोषणा ENABLE_DCBX				0x10

/* Minidump subcommand */
#घोषणा MINIDUMP_GET_SIZE_SUBCOMMAND		0x00
#घोषणा MINIDUMP_GET_TMPLT_SUBCOMMAND		0x01

/* Mailbox 1 */
#घोषणा FW_STATE_READY				0x0000
#घोषणा FW_STATE_CONFIG_WAIT			0x0001
#घोषणा FW_STATE_WAIT_AUTOCONNECT		0x0002
#घोषणा FW_STATE_ERROR				0x0004
#घोषणा FW_STATE_CONFIGURING_IP			0x0008

/* Mailbox 3 */
#घोषणा FW_ADDSTATE_OPTICAL_MEDIA		0x0001
#घोषणा FW_ADDSTATE_DHCPv4_ENABLED		0x0002
#घोषणा FW_ADDSTATE_DHCPv4_LEASE_ACQUIRED	0x0004
#घोषणा FW_ADDSTATE_DHCPv4_LEASE_EXPIRED	0x0008
#घोषणा FW_ADDSTATE_LINK_UP			0x0010
#घोषणा FW_ADDSTATE_ISNS_SVC_ENABLED		0x0020
#घोषणा FW_ADDSTATE_LINK_SPEED_10MBPS		0x0100
#घोषणा FW_ADDSTATE_LINK_SPEED_100MBPS		0x0200
#घोषणा FW_ADDSTATE_LINK_SPEED_1GBPS		0x0400
#घोषणा FW_ADDSTATE_LINK_SPEED_10GBPS		0x0800

#घोषणा MBOX_CMD_GET_DATABASE_ENTRY_DEFAULTS	0x006B
#घोषणा IPV6_DEFAULT_DDB_ENTRY			0x0001

#घोषणा MBOX_CMD_CONN_OPEN_SESS_LOGIN		0x0074
#घोषणा MBOX_CMD_GET_CRASH_RECORD		0x0076	/* 4010 only */
#घोषणा MBOX_CMD_GET_CONN_EVENT_LOG		0x0077

#घोषणा MBOX_CMD_IDC_ACK			0x0101
#घोषणा MBOX_CMD_IDC_TIME_EXTEND		0x0102
#घोषणा MBOX_CMD_PORT_RESET			0x0120
#घोषणा MBOX_CMD_SET_PORT_CONFIG		0x0122

/*  Mailbox status definitions */
#घोषणा MBOX_COMPLETION_STATUS			4
#घोषणा MBOX_STS_BUSY				0x0007
#घोषणा MBOX_STS_INTERMEDIATE_COMPLETION	0x1000
#घोषणा MBOX_STS_COMMAND_COMPLETE		0x4000
#घोषणा MBOX_STS_COMMAND_ERROR			0x4005

#घोषणा MBOX_ASYNC_EVENT_STATUS			8
#घोषणा MBOX_ASTS_SYSTEM_ERROR			0x8002
#घोषणा MBOX_ASTS_REQUEST_TRANSFER_ERROR	0x8003
#घोषणा MBOX_ASTS_RESPONSE_TRANSFER_ERROR	0x8004
#घोषणा MBOX_ASTS_PROTOCOL_STATISTIC_ALARM	0x8005
#घोषणा MBOX_ASTS_SCSI_COMMAND_PDU_REJECTED	0x8006
#घोषणा MBOX_ASTS_LINK_UP			0x8010
#घोषणा MBOX_ASTS_LINK_DOWN			0x8011
#घोषणा MBOX_ASTS_DATABASE_CHANGED		0x8014
#घोषणा MBOX_ASTS_UNSOLICITED_PDU_RECEIVED	0x8015
#घोषणा MBOX_ASTS_SELF_TEST_FAILED		0x8016
#घोषणा MBOX_ASTS_LOGIN_FAILED			0x8017
#घोषणा MBOX_ASTS_DNS				0x8018
#घोषणा MBOX_ASTS_HEARTBEAT			0x8019
#घोषणा MBOX_ASTS_NVRAM_INVALID			0x801A
#घोषणा MBOX_ASTS_MAC_ADDRESS_CHANGED		0x801B
#घोषणा MBOX_ASTS_IP_ADDRESS_CHANGED		0x801C
#घोषणा MBOX_ASTS_DHCP_LEASE_EXPIRED		0x801D
#घोषणा MBOX_ASTS_DHCP_LEASE_ACQUIRED		0x801F
#घोषणा MBOX_ASTS_ISNS_UNSOLICITED_PDU_RECEIVED 0x8021
#घोषणा MBOX_ASTS_DUPLICATE_IP			0x8025
#घोषणा MBOX_ASTS_ARP_COMPLETE			0x8026
#घोषणा MBOX_ASTS_SUBNET_STATE_CHANGE		0x8027
#घोषणा MBOX_ASTS_RESPONSE_QUEUE_FULL		0x8028
#घोषणा MBOX_ASTS_IP_ADDR_STATE_CHANGED		0x8029
#घोषणा MBOX_ASTS_IPV6_DEFAULT_ROUTER_CHANGED	0x802A
#घोषणा MBOX_ASTS_IPV6_LINK_MTU_CHANGE		0x802B
#घोषणा MBOX_ASTS_IPV6_AUTO_PREFIX_IGNORED	0x802C
#घोषणा MBOX_ASTS_IPV6_ND_LOCAL_PREFIX_IGNORED	0x802D
#घोषणा MBOX_ASTS_ICMPV6_ERROR_MSG_RCVD		0x802E
#घोषणा MBOX_ASTS_INITIALIZATION_FAILED		0x8031
#घोषणा MBOX_ASTS_SYSTEM_WARNING_EVENT		0x8036
#घोषणा MBOX_ASTS_IDC_COMPLETE			0x8100
#घोषणा MBOX_ASTS_IDC_REQUEST_NOTIFICATION	0x8101
#घोषणा MBOX_ASTS_IDC_TIME_EXTEND_NOTIFICATION	0x8102
#घोषणा MBOX_ASTS_DCBX_CONF_CHANGE		0x8110
#घोषणा MBOX_ASTS_TXSCVR_INSERTED		0x8130
#घोषणा MBOX_ASTS_TXSCVR_REMOVED		0x8131

#घोषणा ISNS_EVENT_DATA_RECEIVED		0x0000
#घोषणा ISNS_EVENT_CONNECTION_OPENED		0x0001
#घोषणा ISNS_EVENT_CONNECTION_FAILED		0x0002
#घोषणा MBOX_ASTS_IPSEC_SYSTEM_FATAL_ERROR	0x8022
#घोषणा MBOX_ASTS_SUBNET_STATE_CHANGE		0x8027

/* ACB Configuration Defines */
#घोषणा ACB_CONFIG_DISABLE		0x00
#घोषणा ACB_CONFIG_SET			0x01

/* ACB/IP Address State Defines */
#घोषणा IP_ADDRSTATE_UNCONFIGURED	0
#घोषणा IP_ADDRSTATE_INVALID		1
#घोषणा IP_ADDRSTATE_ACQUIRING		2
#घोषणा IP_ADDRSTATE_TENTATIVE		3
#घोषणा IP_ADDRSTATE_DEPRICATED		4
#घोषणा IP_ADDRSTATE_PREFERRED		5
#घोषणा IP_ADDRSTATE_DISABLING		6

/* FLASH offsets */
#घोषणा FLASH_SEGMENT_IFCB	0x04000000

#घोषणा FLASH_OPT_RMW_HOLD	0
#घोषणा FLASH_OPT_RMW_INIT	1
#घोषणा FLASH_OPT_COMMIT	2
#घोषणा FLASH_OPT_RMW_COMMIT	3

/* generic defines to enable/disable params */
#घोषणा QL4_PARAM_DISABLE	0
#घोषणा QL4_PARAM_ENABLE	1

/*************************************************************************/

/* Host Adapter Initialization Control Block (from host) */
काष्ठा addr_ctrl_blk अणु
	uपूर्णांक8_t version;	/* 00 */
#घोषणा  IFCB_VER_MIN			0x01
#घोषणा  IFCB_VER_MAX			0x02
	uपूर्णांक8_t control;	/* 01 */
#घोषणा	 CTRLOPT_NEW_CONN_DISABLE	0x0002

	uपूर्णांक16_t fw_options;	/* 02-03 */
#घोषणा	 FWOPT_HEARTBEAT_ENABLE		  0x1000
#घोषणा	 FWOPT_SESSION_MODE		  0x0040
#घोषणा	 FWOPT_INITIATOR_MODE		  0x0020
#घोषणा	 FWOPT_TARGET_MODE		  0x0010
#घोषणा	 FWOPT_ENABLE_CRBDB		  0x8000

	uपूर्णांक16_t exec_throttle;	/* 04-05 */
	uपूर्णांक8_t zio_count;	/* 06 */
	uपूर्णांक8_t res0;	/* 07 */
	uपूर्णांक16_t eth_mtu_size;	/* 08-09 */
	uपूर्णांक16_t add_fw_options;	/* 0A-0B */
#घोषणा ADFWOPT_SERIALIZE_TASK_MGMT	0x0400
#घोषणा ADFWOPT_AUTOCONN_DISABLE	0x0002

	uपूर्णांक8_t hb_पूर्णांकerval;	/* 0C */
	uपूर्णांक8_t inst_num; /* 0D */
	uपूर्णांक16_t res1;		/* 0E-0F */
	uपूर्णांक16_t rqq_consumer_idx;	/* 10-11 */
	uपूर्णांक16_t compq_producer_idx;	/* 12-13 */
	uपूर्णांक16_t rqq_len;	/* 14-15 */
	uपूर्णांक16_t compq_len;	/* 16-17 */
	uपूर्णांक32_t rqq_addr_lo;	/* 18-1B */
	uपूर्णांक32_t rqq_addr_hi;	/* 1C-1F */
	uपूर्णांक32_t compq_addr_lo;	/* 20-23 */
	uपूर्णांक32_t compq_addr_hi;	/* 24-27 */
	uपूर्णांक32_t shdwreg_addr_lo;	/* 28-2B */
	uपूर्णांक32_t shdwreg_addr_hi;	/* 2C-2F */

	uपूर्णांक16_t iscsi_opts;	/* 30-31 */
#घोषणा ISCSIOPTS_HEADER_DIGEST_EN		0x2000
#घोषणा ISCSIOPTS_DATA_DIGEST_EN		0x1000
#घोषणा ISCSIOPTS_IMMEDIATE_DATA_EN		0x0800
#घोषणा ISCSIOPTS_INITIAL_R2T_EN		0x0400
#घोषणा ISCSIOPTS_DATA_SEQ_INORDER_EN		0x0200
#घोषणा ISCSIOPTS_DATA_PDU_INORDER_EN		0x0100
#घोषणा ISCSIOPTS_CHAP_AUTH_EN			0x0080
#घोषणा ISCSIOPTS_SNACK_EN			0x0040
#घोषणा ISCSIOPTS_DISCOVERY_LOGOUT_EN		0x0020
#घोषणा ISCSIOPTS_BIDI_CHAP_EN			0x0010
#घोषणा ISCSIOPTS_DISCOVERY_AUTH_EN		0x0008
#घोषणा ISCSIOPTS_STRICT_LOGIN_COMP_EN		0x0004
#घोषणा ISCSIOPTS_ERL				0x0003
	uपूर्णांक16_t ipv4_tcp_opts;	/* 32-33 */
#घोषणा TCPOPT_DELAYED_ACK_DISABLE	0x8000
#घोषणा TCPOPT_DHCP_ENABLE		0x0200
#घोषणा TCPOPT_DNS_SERVER_IP_EN		0x0100
#घोषणा TCPOPT_SLP_DA_INFO_EN		0x0080
#घोषणा TCPOPT_NAGLE_ALGO_DISABLE	0x0020
#घोषणा TCPOPT_WINDOW_SCALE_DISABLE	0x0010
#घोषणा TCPOPT_TIMER_SCALE		0x000E
#घोषणा TCPOPT_TIMESTAMP_ENABLE		0x0001
	uपूर्णांक16_t ipv4_ip_opts;	/* 34-35 */
#घोषणा IPOPT_IPV4_PROTOCOL_ENABLE	0x8000
#घोषणा IPOPT_IPV4_TOS_EN		0x4000
#घोषणा IPOPT_VLAN_TAGGING_ENABLE	0x2000
#घोषणा IPOPT_GRAT_ARP_EN		0x1000
#घोषणा IPOPT_ALT_CID_EN		0x0800
#घोषणा IPOPT_REQ_VID_EN		0x0400
#घोषणा IPOPT_USE_VID_EN		0x0200
#घोषणा IPOPT_LEARN_IQN_EN		0x0100
#घोषणा IPOPT_FRAGMENTATION_DISABLE	0x0010
#घोषणा IPOPT_IN_FORWARD_EN		0x0008
#घोषणा IPOPT_ARP_REसूचीECT_EN		0x0004

	uपूर्णांक16_t iscsi_max_pdu_size;	/* 36-37 */
	uपूर्णांक8_t ipv4_tos;	/* 38 */
	uपूर्णांक8_t ipv4_ttl;	/* 39 */
	uपूर्णांक8_t acb_version;	/* 3A */
#घोषणा ACB_NOT_SUPPORTED		0x00
#घोषणा ACB_SUPPORTED			0x02 /* Capable of ACB Version 2
						Features */

	uपूर्णांक8_t res2;	/* 3B */
	uपूर्णांक16_t def_समयout;	/* 3C-3D */
	uपूर्णांक16_t iscsi_fburst_len;	/* 3E-3F */
	uपूर्णांक16_t iscsi_def_समय2रुको;	/* 40-41 */
	uपूर्णांक16_t iscsi_def_समय2retain;	/* 42-43 */
	uपूर्णांक16_t iscsi_max_outstnd_r2t;	/* 44-45 */
	uपूर्णांक16_t conn_ka_समयout;	/* 46-47 */
	uपूर्णांक16_t ipv4_port;	/* 48-49 */
	uपूर्णांक16_t iscsi_max_burst_len;	/* 4A-4B */
	uपूर्णांक32_t res5;		/* 4C-4F */
	uपूर्णांक8_t ipv4_addr[4];	/* 50-53 */
	uपूर्णांक16_t ipv4_vlan_tag;	/* 54-55 */
	uपूर्णांक8_t ipv4_addr_state;	/* 56 */
	uपूर्णांक8_t ipv4_cacheid;	/* 57 */
	uपूर्णांक8_t res6[8];	/* 58-5F */
	uपूर्णांक8_t ipv4_subnet[4];	/* 60-63 */
	uपूर्णांक8_t res7[12];	/* 64-6F */
	uपूर्णांक8_t ipv4_gw_addr[4];	/* 70-73 */
	uपूर्णांक8_t res8[0xc];	/* 74-7F */
	uपूर्णांक8_t pri_dns_srvr_ip[4];/* 80-83 */
	uपूर्णांक8_t sec_dns_srvr_ip[4];/* 84-87 */
	uपूर्णांक16_t min_eph_port;	/* 88-89 */
	uपूर्णांक16_t max_eph_port;	/* 8A-8B */
	uपूर्णांक8_t res9[4];	/* 8C-8F */
	uपूर्णांक8_t iscsi_alias[32];/* 90-AF */
	uपूर्णांक8_t res9_1[0x16];	/* B0-C5 */
	uपूर्णांक16_t tgt_portal_grp;/* C6-C7 */
	uपूर्णांक8_t पात_समयr;	/* C8	 */
	uपूर्णांक8_t ipv4_tcp_wsf;	/* C9	 */
	uपूर्णांक8_t res10[6];	/* CA-CF */
	uपूर्णांक8_t ipv4_sec_ip_addr[4];	/* D0-D3 */
	uपूर्णांक8_t ipv4_dhcp_vid_len;	/* D4 */
	uपूर्णांक8_t ipv4_dhcp_vid[11];	/* D5-DF */
	uपूर्णांक8_t res11[20];	/* E0-F3 */
	uपूर्णांक8_t ipv4_dhcp_alt_cid_len;	/* F4 */
	uपूर्णांक8_t ipv4_dhcp_alt_cid[11];	/* F5-FF */
	uपूर्णांक8_t iscsi_name[224];	/* 100-1DF */
	uपूर्णांक8_t res12[32];	/* 1E0-1FF */
	uपूर्णांक32_t cookie;	/* 200-203 */
	uपूर्णांक16_t ipv6_port;	/* 204-205 */
	uपूर्णांक16_t ipv6_opts;	/* 206-207 */
#घोषणा IPV6_OPT_IPV6_PROTOCOL_ENABLE		0x8000
#घोषणा IPV6_OPT_VLAN_TAGGING_ENABLE		0x2000
#घोषणा IPV6_OPT_GRAT_NEIGHBOR_ADV_EN		0x1000
#घोषणा IPV6_OPT_REसूचीECT_EN			0x0004

	uपूर्णांक16_t ipv6_addtl_opts;	/* 208-209 */
#घोषणा IPV6_ADDOPT_IGNORE_ICMP_ECHO_REQ		0x0040
#घोषणा IPV6_ADDOPT_MLD_EN				0x0004
#घोषणा IPV6_ADDOPT_NEIGHBOR_DISCOVERY_ADDR_ENABLE	0x0002 /* Pri ACB
								  Only */
#घोषणा IPV6_ADDOPT_AUTOCONFIG_LINK_LOCAL_ADDR		0x0001

	uपूर्णांक16_t ipv6_tcp_opts;	/* 20A-20B */
#घोषणा IPV6_TCPOPT_DELAYED_ACK_DISABLE		0x8000
#घोषणा IPV6_TCPOPT_NAGLE_ALGO_DISABLE		0x0020
#घोषणा IPV6_TCPOPT_WINDOW_SCALE_DISABLE	0x0010
#घोषणा IPV6_TCPOPT_TIMER_SCALE			0x000E
#घोषणा IPV6_TCPOPT_TIMESTAMP_EN		0x0001
	uपूर्णांक8_t ipv6_tcp_wsf;	/* 20C */
	uपूर्णांक16_t ipv6_flow_lbl;	/* 20D-20F */
	uपूर्णांक8_t ipv6_dflt_rtr_addr[16]; /* 210-21F */
	uपूर्णांक16_t ipv6_vlan_tag;	/* 220-221 */
	uपूर्णांक8_t ipv6_lnk_lcl_addr_state;/* 222 */
	uपूर्णांक8_t ipv6_addr0_state;	/* 223 */
	uपूर्णांक8_t ipv6_addr1_state;	/* 224 */
	uपूर्णांक8_t ipv6_dflt_rtr_state;    /* 225 */
#घोषणा IPV6_RTRSTATE_UNKNOWN                   0
#घोषणा IPV6_RTRSTATE_MANUAL                    1
#घोषणा IPV6_RTRSTATE_ADVERTISED                3
#घोषणा IPV6_RTRSTATE_STALE                     4

	uपूर्णांक8_t ipv6_traffic_class;	/* 226 */
	uपूर्णांक8_t ipv6_hop_limit;	/* 227 */
	uपूर्णांक8_t ipv6_अगर_id[8];	/* 228-22F */
	uपूर्णांक8_t ipv6_addr0[16];	/* 230-23F */
	uपूर्णांक8_t ipv6_addr1[16];	/* 240-24F */
	uपूर्णांक32_t ipv6_nd_reach_समय;	/* 250-253 */
	uपूर्णांक32_t ipv6_nd_rexmit_समयr;	/* 254-257 */
	uपूर्णांक32_t ipv6_nd_stale_समयout;	/* 258-25B */
	uपूर्णांक8_t ipv6_dup_addr_detect_count;	/* 25C */
	uपूर्णांक8_t ipv6_cache_id;	/* 25D */
	uपूर्णांक8_t res13[18];	/* 25E-26F */
	uपूर्णांक32_t ipv6_gw_advrt_mtu;	/* 270-273 */
	uपूर्णांक8_t res14[140];	/* 274-2FF */
पूर्ण;

#घोषणा IP_ADDR_COUNT	4 /* Total 4 IP address supported in one पूर्णांकerface
			   * One IPv4, one IPv6 link local and 2 IPv6
			   */

#घोषणा IP_STATE_MASK	0x0F000000
#घोषणा IP_STATE_SHIFT	24

काष्ठा init_fw_ctrl_blk अणु
	काष्ठा addr_ctrl_blk pri;
/*	काष्ठा addr_ctrl_blk sec;*/
पूर्ण;

#घोषणा PRIMARI_ACB		0
#घोषणा SECONDARY_ACB		1

काष्ठा addr_ctrl_blk_def अणु
	uपूर्णांक8_t reserved1[1];	/* 00 */
	uपूर्णांक8_t control;	/* 01 */
	uपूर्णांक8_t reserved2[11];	/* 02-0C */
	uपूर्णांक8_t inst_num;	/* 0D */
	uपूर्णांक8_t reserved3[34];	/* 0E-2F */
	uपूर्णांक16_t iscsi_opts;	/* 30-31 */
	uपूर्णांक16_t ipv4_tcp_opts;	/* 32-33 */
	uपूर्णांक16_t ipv4_ip_opts;	/* 34-35 */
	uपूर्णांक16_t iscsi_max_pdu_size;	/* 36-37 */
	uपूर्णांक8_t ipv4_tos;	/* 38 */
	uपूर्णांक8_t ipv4_ttl;	/* 39 */
	uपूर्णांक8_t reserved4[2];	/* 3A-3B */
	uपूर्णांक16_t def_समयout;	/* 3C-3D */
	uपूर्णांक16_t iscsi_fburst_len;	/* 3E-3F */
	uपूर्णांक8_t reserved5[4];	/* 40-43 */
	uपूर्णांक16_t iscsi_max_outstnd_r2t;	/* 44-45 */
	uपूर्णांक8_t reserved6[2];	/* 46-47 */
	uपूर्णांक16_t ipv4_port;	/* 48-49 */
	uपूर्णांक16_t iscsi_max_burst_len;	/* 4A-4B */
	uपूर्णांक8_t reserved7[4];	/* 4C-4F */
	uपूर्णांक8_t ipv4_addr[4];	/* 50-53 */
	uपूर्णांक16_t ipv4_vlan_tag;	/* 54-55 */
	uपूर्णांक8_t ipv4_addr_state;	/* 56 */
	uपूर्णांक8_t ipv4_cacheid;	/* 57 */
	uपूर्णांक8_t reserved8[8];	/* 58-5F */
	uपूर्णांक8_t ipv4_subnet[4];	/* 60-63 */
	uपूर्णांक8_t reserved9[12];	/* 64-6F */
	uपूर्णांक8_t ipv4_gw_addr[4];	/* 70-73 */
	uपूर्णांक8_t reserved10[84];	/* 74-C7 */
	uपूर्णांक8_t पात_समयr;	/* C8    */
	uपूर्णांक8_t ipv4_tcp_wsf;	/* C9    */
	uपूर्णांक8_t reserved11[10];	/* CA-D3 */
	uपूर्णांक8_t ipv4_dhcp_vid_len;	/* D4 */
	uपूर्णांक8_t ipv4_dhcp_vid[11];	/* D5-DF */
	uपूर्णांक8_t reserved12[20];	/* E0-F3 */
	uपूर्णांक8_t ipv4_dhcp_alt_cid_len;	/* F4 */
	uपूर्णांक8_t ipv4_dhcp_alt_cid[11];	/* F5-FF */
	uपूर्णांक8_t iscsi_name[224];	/* 100-1DF */
	uपूर्णांक8_t reserved13[32];	/* 1E0-1FF */
	uपूर्णांक32_t cookie;	/* 200-203 */
	uपूर्णांक16_t ipv6_port;	/* 204-205 */
	uपूर्णांक16_t ipv6_opts;	/* 206-207 */
	uपूर्णांक16_t ipv6_addtl_opts;	/* 208-209 */
	uपूर्णांक16_t ipv6_tcp_opts;		/* 20A-20B */
	uपूर्णांक8_t ipv6_tcp_wsf;		/* 20C */
	uपूर्णांक16_t ipv6_flow_lbl;		/* 20D-20F */
	uपूर्णांक8_t ipv6_dflt_rtr_addr[16];	/* 210-21F */
	uपूर्णांक16_t ipv6_vlan_tag;		/* 220-221 */
	uपूर्णांक8_t ipv6_lnk_lcl_addr_state;	/* 222 */
	uपूर्णांक8_t ipv6_addr0_state;	/* 223 */
	uपूर्णांक8_t ipv6_addr1_state;	/* 224 */
	uपूर्णांक8_t ipv6_dflt_rtr_state;	/* 225 */
	uपूर्णांक8_t ipv6_traffic_class;	/* 226 */
	uपूर्णांक8_t ipv6_hop_limit;		/* 227 */
	uपूर्णांक8_t ipv6_अगर_id[8];		/* 228-22F */
	uपूर्णांक8_t ipv6_addr0[16];		/* 230-23F */
	uपूर्णांक8_t ipv6_addr1[16];		/* 240-24F */
	uपूर्णांक32_t ipv6_nd_reach_समय;	/* 250-253 */
	uपूर्णांक32_t ipv6_nd_rexmit_समयr;	/* 254-257 */
	uपूर्णांक32_t ipv6_nd_stale_समयout;	/* 258-25B */
	uपूर्णांक8_t ipv6_dup_addr_detect_count;	/* 25C */
	uपूर्णांक8_t ipv6_cache_id;		/* 25D */
	uपूर्णांक8_t reserved14[18];		/* 25E-26F */
	uपूर्णांक32_t ipv6_gw_advrt_mtu;	/* 270-273 */
	uपूर्णांक8_t reserved15[140];	/* 274-2FF */
पूर्ण;

/*************************************************************************/

#घोषणा MAX_CHAP_ENTRIES_40XX	128
#घोषणा MAX_CHAP_ENTRIES_82XX	1024
#घोषणा MAX_RESRV_CHAP_IDX	3
#घोषणा FLASH_CHAP_OFFSET	0x06000000

काष्ठा ql4_chap_table अणु
	uपूर्णांक16_t link;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t secret_len;
#घोषणा MIN_CHAP_SECRET_LEN	12
#घोषणा MAX_CHAP_SECRET_LEN	100
	uपूर्णांक8_t secret[MAX_CHAP_SECRET_LEN];
#घोषणा MAX_CHAP_NAME_LEN	256
	uपूर्णांक8_t name[MAX_CHAP_NAME_LEN];
	uपूर्णांक16_t reserved;
#घोषणा CHAP_VALID_COOKIE	0x4092
#घोषणा CHAP_INVALID_COOKIE	0xFFEE
	uपूर्णांक16_t cookie;
पूर्ण;

काष्ठा dev_db_entry अणु
	uपूर्णांक16_t options;	/* 00-01 */
#घोषणा DDB_OPT_DISC_SESSION  0x10
#घोषणा DDB_OPT_TARGET	      0x02 /* device is a target */
#घोषणा DDB_OPT_IPV6_DEVICE	0x100
#घोषणा DDB_OPT_AUTO_SENDTGTS_DISABLE		0x40
#घोषणा DDB_OPT_IPV6_शून्य_LINK_LOCAL		0x800 /* post connection */
#घोषणा DDB_OPT_IPV6_FW_DEFINED_LINK_LOCAL	0x800 /* pre connection */

#घोषणा OPT_IS_FW_ASSIGNED_IPV6		11
#घोषणा OPT_IPV6_DEVICE			8
#घोषणा OPT_AUTO_SENDTGTS_DISABLE	6
#घोषणा OPT_DISC_SESSION		4
#घोषणा OPT_ENTRY_STATE			3
	uपूर्णांक16_t exec_throttle;	/* 02-03 */
	uपूर्णांक16_t exec_count;	/* 04-05 */
	uपूर्णांक16_t res0;	/* 06-07 */
	uपूर्णांक16_t iscsi_options;	/* 08-09 */
#घोषणा ISCSIOPT_HEADER_DIGEST_EN		13
#घोषणा ISCSIOPT_DATA_DIGEST_EN			12
#घोषणा ISCSIOPT_IMMEDIATE_DATA_EN		11
#घोषणा ISCSIOPT_INITIAL_R2T_EN			10
#घोषणा ISCSIOPT_DATA_SEQ_IN_ORDER		9
#घोषणा ISCSIOPT_DATA_PDU_IN_ORDER		8
#घोषणा ISCSIOPT_CHAP_AUTH_EN			7
#घोषणा ISCSIOPT_SNACK_REQ_EN			6
#घोषणा ISCSIOPT_DISCOVERY_LOGOUT_EN		5
#घोषणा ISCSIOPT_BIDI_CHAP_EN			4
#घोषणा ISCSIOPT_DISCOVERY_AUTH_OPTIONAL	3
#घोषणा ISCSIOPT_ERL1				1
#घोषणा ISCSIOPT_ERL0				0

	uपूर्णांक16_t tcp_options;	/* 0A-0B */
#घोषणा TCPOPT_TIMESTAMP_STAT	6
#घोषणा TCPOPT_NAGLE_DISABLE	5
#घोषणा TCPOPT_WSF_DISABLE	4
#घोषणा TCPOPT_TIMER_SCALE3	3
#घोषणा TCPOPT_TIMER_SCALE2	2
#घोषणा TCPOPT_TIMER_SCALE1	1
#घोषणा TCPOPT_TIMESTAMP_EN	0

	uपूर्णांक16_t ip_options;	/* 0C-0D */
#घोषणा IPOPT_FRAGMENT_DISABLE	4

	uपूर्णांक16_t iscsi_max_rcv_data_seg_len;	/* 0E-0F */
#घोषणा BYTE_UNITS	512
	uपूर्णांक32_t res1;	/* 10-13 */
	uपूर्णांक16_t iscsi_max_snd_data_seg_len;	/* 14-15 */
	uपूर्णांक16_t iscsi_first_burst_len;	/* 16-17 */
	uपूर्णांक16_t iscsi_def_समय2रुको;	/* 18-19 */
	uपूर्णांक16_t iscsi_def_समय2retain;	/* 1A-1B */
	uपूर्णांक16_t iscsi_max_outsnd_r2t;	/* 1C-1D */
	uपूर्णांक16_t ka_समयout;	/* 1E-1F */
	uपूर्णांक8_t isid[6];	/* 20-25 big-endian, must be converted
				 * to little-endian */
	uपूर्णांक16_t tsid;		/* 26-27 */
	uपूर्णांक16_t port;	/* 28-29 */
	uपूर्णांक16_t iscsi_max_burst_len;	/* 2A-2B */
	uपूर्णांक16_t def_समयout;	/* 2C-2D */
	uपूर्णांक16_t res2;	/* 2E-2F */
	uपूर्णांक8_t ip_addr[0x10];	/* 30-3F */
	uपूर्णांक8_t iscsi_alias[0x20];	/* 40-5F */
	uपूर्णांक8_t tgt_addr[0x20];	/* 60-7F */
	uपूर्णांक16_t mss;	/* 80-81 */
	uपूर्णांक16_t res3;	/* 82-83 */
	uपूर्णांक16_t lcl_port;	/* 84-85 */
	uपूर्णांक8_t ipv4_tos;	/* 86 */
	uपूर्णांक16_t ipv6_flow_lbl;	/* 87-89 */
	uपूर्णांक8_t res4[0x36];	/* 8A-BF */
	uपूर्णांक8_t iscsi_name[0xE0];	/* C0-19F : xxzzy Make this a
					 * poपूर्णांकer to a string so we
					 * करोn't have to reserve so
					 * much RAM */
	uपूर्णांक8_t link_local_ipv6_addr[0x10]; /* 1A0-1AF */
	uपूर्णांक8_t res5[0x10];	/* 1B0-1BF */
#घोषणा DDB_NO_LINK	0xFFFF
#घोषणा DDB_ISNS	0xFFFD
	uपूर्णांक16_t ddb_link;	/* 1C0-1C1 */
	uपूर्णांक16_t chap_tbl_idx;	/* 1C2-1C3 */
	uपूर्णांक16_t tgt_portal_grp; /* 1C4-1C5 */
	uपूर्णांक8_t tcp_xmt_wsf;	/* 1C6 */
	uपूर्णांक8_t tcp_rcv_wsf;	/* 1C7 */
	uपूर्णांक32_t stat_sn;	/* 1C8-1CB */
	uपूर्णांक32_t exp_stat_sn;	/* 1CC-1CF */
	uपूर्णांक8_t res6[0x2b];	/* 1D0-1FB */
#घोषणा DDB_VALID_COOKIE	0x9034
	uपूर्णांक16_t cookie;	/* 1FC-1FD */
	uपूर्णांक16_t len;		/* 1FE-1FF */
पूर्ण;

/*************************************************************************/

/* Flash definitions */

#घोषणा FLASH_OFFSET_SYS_INFO	0x02000000
#घोषणा FLASH_DEFAULTBLOCKSIZE	0x20000
#घोषणा FLASH_खातापूर्ण_OFFSET	(FLASH_DEFAULTBLOCKSIZE-8) /* 4 bytes
							    * क्रम खातापूर्ण
							    * signature */
#घोषणा FLASH_RAW_ACCESS_ADDR	0x8e000000

#घोषणा BOOT_PARAM_OFFSET_PORT0 0x3b0
#घोषणा BOOT_PARAM_OFFSET_PORT1 0x7b0

#घोषणा FLASH_OFFSET_DB_INFO	0x05000000
#घोषणा FLASH_OFFSET_DB_END	(FLASH_OFFSET_DB_INFO + 0x7fff)


काष्ठा sys_info_phys_addr अणु
	uपूर्णांक8_t address[6];	/* 00-05 */
	uपूर्णांक8_t filler[2];	/* 06-07 */
पूर्ण;

काष्ठा flash_sys_info अणु
	uपूर्णांक32_t cookie;	/* 00-03 */
	uपूर्णांक32_t physAddrCount; /* 04-07 */
	काष्ठा sys_info_phys_addr physAddr[4]; /* 08-27 */
	uपूर्णांक8_t venकरोrId[128];	/* 28-A7 */
	uपूर्णांक8_t productId[128]; /* A8-127 */
	uपूर्णांक32_t serialNumber;	/* 128-12B */

	/*  PCI Configuration values */
	uपूर्णांक32_t pciDeviceVenकरोr;	/* 12C-12F */
	uपूर्णांक32_t pciDeviceId;	/* 130-133 */
	uपूर्णांक32_t pciSubsysVenकरोr;	/* 134-137 */
	uपूर्णांक32_t pciSubsysId;	/* 138-13B */

	/*  This validates version 1. */
	uपूर्णांक32_t crumbs;	/* 13C-13F */

	uपूर्णांक32_t enterpriseNumber;	/* 140-143 */

	uपूर्णांक32_t mtu;		/* 144-147 */
	uपूर्णांक32_t reserved0;	/* 148-14b */
	uपूर्णांक32_t crumbs2;	/* 14c-14f */
	uपूर्णांक8_t acSerialNumber[16];	/* 150-15f */
	uपूर्णांक32_t crumbs3;	/* 160-16f */

	/* Leave this last in the काष्ठा so it is declared invalid अगर
	 * any new items are added.
	 */
	uपूर्णांक32_t reserved1[39]; /* 170-1ff */
पूर्ण;	/* 200 */

काष्ठा mbx_sys_info अणु
	uपूर्णांक8_t board_id_str[16];   /*  0-f  Keep board ID string first */
				/* in this काष्ठाure क्रम GUI. */
	uपूर्णांक16_t board_id;	/* 10-11 board ID code */
	uपूर्णांक16_t phys_port_cnt;	/* 12-13 number of physical network ports */
	uपूर्णांक16_t port_num;	/* 14-15 network port क्रम this PCI function */
				/* (port 0 is first port) */
	uपूर्णांक8_t mac_addr[6];	/* 16-1b MAC address क्रम this PCI function */
	uपूर्णांक32_t iscsi_pci_func_cnt;  /* 1c-1f number of iSCSI PCI functions */
	uपूर्णांक32_t pci_func;	      /* 20-23 this PCI function */
	अचिन्हित अक्षर serial_number[16];  /* 24-33 serial number string */
	uपूर्णांक8_t reserved[12];		  /* 34-3f */
पूर्ण;

काष्ठा about_fw_info अणु
	uपूर्णांक16_t fw_major;		/* 00 - 01 */
	uपूर्णांक16_t fw_minor;		/* 02 - 03 */
	uपूर्णांक16_t fw_patch;		/* 04 - 05 */
	uपूर्णांक16_t fw_build;		/* 06 - 07 */
	uपूर्णांक8_t fw_build_date[16];	/* 08 - 17 ASCII String */
	uपूर्णांक8_t fw_build_समय[16];	/* 18 - 27 ASCII String */
	uपूर्णांक8_t fw_build_user[16];	/* 28 - 37 ASCII String */
	uपूर्णांक16_t fw_load_source;	/* 38 - 39 */
					/* 1 = Flash Primary,
					   2 = Flash Secondary,
					   3 = Host Download
					*/
	uपूर्णांक8_t reserved1[6];		/* 3A - 3F */
	uपूर्णांक16_t iscsi_major;		/* 40 - 41 */
	uपूर्णांक16_t iscsi_minor;		/* 42 - 43 */
	uपूर्णांक16_t bootload_major;	/* 44 - 45 */
	uपूर्णांक16_t bootload_minor;	/* 46 - 47 */
	uपूर्णांक16_t bootload_patch;	/* 48 - 49 */
	uपूर्णांक16_t bootload_build;	/* 4A - 4B */
	uपूर्णांक8_t extended_बारtamp[180];/* 4C - FF */
पूर्ण;

काष्ठा crash_record अणु
	uपूर्णांक16_t fw_major_version;	/* 00 - 01 */
	uपूर्णांक16_t fw_minor_version;	/* 02 - 03 */
	uपूर्णांक16_t fw_patch_version;	/* 04 - 05 */
	uपूर्णांक16_t fw_build_version;	/* 06 - 07 */

	uपूर्णांक8_t build_date[16]; /* 08 - 17 */
	uपूर्णांक8_t build_समय[16]; /* 18 - 27 */
	uपूर्णांक8_t build_user[16]; /* 28 - 37 */
	uपूर्णांक8_t card_serial_num[16];	/* 38 - 47 */

	uपूर्णांक32_t समय_of_crash_in_secs; /* 48 - 4B */
	uपूर्णांक32_t समय_of_crash_in_ms;	/* 4C - 4F */

	uपूर्णांक16_t out_RISC_sd_num_frames;	/* 50 - 51 */
	uपूर्णांक16_t OAP_sd_num_words;	/* 52 - 53 */
	uपूर्णांक16_t IAP_sd_num_frames;	/* 54 - 55 */
	uपूर्णांक16_t in_RISC_sd_num_words;	/* 56 - 57 */

	uपूर्णांक8_t reserved1[28];	/* 58 - 7F */

	uपूर्णांक8_t out_RISC_reg_dump[256]; /* 80 -17F */
	uपूर्णांक8_t in_RISC_reg_dump[256];	/*180 -27F */
	uपूर्णांक8_t in_out_RISC_stack_dump[0];	/*280 - ??? */
पूर्ण;

काष्ठा conn_event_log_entry अणु
#घोषणा MAX_CONN_EVENT_LOG_ENTRIES	100
	uपूर्णांक32_t बारtamp_sec; /* 00 - 03 seconds since boot */
	uपूर्णांक32_t बारtamp_ms;	/* 04 - 07 milliseconds since boot */
	uपूर्णांक16_t device_index;	/* 08 - 09  */
	uपूर्णांक16_t fw_conn_state; /* 0A - 0B  */
	uपूर्णांक8_t event_type;	/* 0C - 0C  */
	uपूर्णांक8_t error_code;	/* 0D - 0D  */
	uपूर्णांक16_t error_code_detail;	/* 0E - 0F  */
	uपूर्णांक8_t num_consecutive_events; /* 10 - 10  */
	uपूर्णांक8_t rsvd[3];	/* 11 - 13  */
पूर्ण;

/*************************************************************************
 *
 *				IOCB Commands Structures and Definitions
 *
 *************************************************************************/
#घोषणा IOCB_MAX_CDB_LEN	    16	/* Bytes in a CBD */
#घोषणा IOCB_MAX_SENSEDATA_LEN	    32	/* Bytes of sense data */
#घोषणा IOCB_MAX_EXT_SENSEDATA_LEN  60  /* Bytes of extended sense data */

/* IOCB header काष्ठाure */
काष्ठा qla4_header अणु
	uपूर्णांक8_t entryType;
#घोषणा ET_STATUS		 0x03
#घोषणा ET_MARKER		 0x04
#घोषणा ET_CONT_T1		 0x0A
#घोषणा ET_STATUS_CONTINUATION	 0x10
#घोषणा ET_CMND_T3		 0x19
#घोषणा ET_PASSTHRU0		 0x3A
#घोषणा ET_PASSTHRU_STATUS	 0x3C
#घोषणा ET_MBOX_CMD		0x38
#घोषणा ET_MBOX_STATUS		0x39

	uपूर्णांक8_t entryStatus;
	uपूर्णांक8_t प्रणालीDefined;
#घोषणा SD_ISCSI_PDU	0x01
	uपूर्णांक8_t entryCount;

	/* SyetemDefined definition */
पूर्ण;

/* Generic queue entry काष्ठाure*/
काष्ठा queue_entry अणु
	uपूर्णांक8_t data[60];
	uपूर्णांक32_t signature;

पूर्ण;

/* 64 bit addressing segment counts*/

#घोषणा COMMAND_SEG_A64	  1
#घोषणा CONTINUE_SEG_A64  5

/* 64 bit addressing segment definition*/

काष्ठा data_seg_a64 अणु
	काष्ठा अणु
		uपूर्णांक32_t addrLow;
		uपूर्णांक32_t addrHigh;

	पूर्ण base;

	uपूर्णांक32_t count;

पूर्ण;

/* Command Type 3 entry काष्ठाure*/

काष्ठा command_t3_entry अणु
	काष्ठा qla4_header hdr;	/* 00-03 */

	uपूर्णांक32_t handle;	/* 04-07 */
	uपूर्णांक16_t target;	/* 08-09 */
	uपूर्णांक16_t connection_id; /* 0A-0B */

	uपूर्णांक8_t control_flags;	/* 0C */

	/* data direction  (bits 5-6) */
#घोषणा CF_WRITE		0x20
#घोषणा CF_READ			0x40
#घोषणा CF_NO_DATA		0x00

	/* task attributes (bits 2-0) */
#घोषणा CF_HEAD_TAG		0x03
#घोषणा CF_ORDERED_TAG		0x02
#घोषणा CF_SIMPLE_TAG		0x01

	/* STATE FLAGS FIELD IS A PLACE HOLDER. THE FW WILL SET BITS
	 * IN THIS FIELD AS THE COMMAND IS PROCESSED. WHEN THE IOCB IS
	 * CHANGED TO AN IOSB THIS FIELD WILL HAVE THE STATE FLAGS SET
	 * PROPERLY.
	 */
	uपूर्णांक8_t state_flags;	/* 0D */
	uपूर्णांक8_t cmdRefNum;	/* 0E */
	uपूर्णांक8_t reserved1;	/* 0F */
	uपूर्णांक8_t cdb[IOCB_MAX_CDB_LEN];	/* 10-1F */
	काष्ठा scsi_lun lun;	/* FCP LUN (BE). */
	uपूर्णांक32_t cmdSeqNum;	/* 28-2B */
	uपूर्णांक16_t समयout;	/* 2C-2D */
	uपूर्णांक16_t dataSegCnt;	/* 2E-2F */
	uपूर्णांक32_t ttlByteCnt;	/* 30-33 */
	काष्ठा data_seg_a64 dataseg[COMMAND_SEG_A64];	/* 34-3F */

पूर्ण;


/* Continuation Type 1 entry काष्ठाure*/
काष्ठा continuation_t1_entry अणु
	काष्ठा qla4_header hdr;

	काष्ठा data_seg_a64 dataseg[CONTINUE_SEG_A64];

पूर्ण;

/* Parameterize क्रम 64 or 32 bits */
#घोषणा COMMAND_SEG	COMMAND_SEG_A64
#घोषणा CONTINUE_SEG	CONTINUE_SEG_A64

#घोषणा ET_COMMAND	ET_CMND_T3
#घोषणा ET_CONTINUE	ET_CONT_T1

/* Marker entry काष्ठाure*/
काष्ठा qla4_marker_entry अणु
	काष्ठा qla4_header hdr;	/* 00-03 */

	uपूर्णांक32_t प्रणाली_defined; /* 04-07 */
	uपूर्णांक16_t target;	/* 08-09 */
	uपूर्णांक16_t modअगरier;	/* 0A-0B */
#घोषणा MM_LUN_RESET		0
#घोषणा MM_TGT_WARM_RESET	1

	uपूर्णांक16_t flags;		/* 0C-0D */
	uपूर्णांक16_t reserved1;	/* 0E-0F */
	काष्ठा scsi_lun lun;	/* FCP LUN (BE). */
	uपूर्णांक64_t reserved2;	/* 18-1F */
	uपूर्णांक64_t reserved3;	/* 20-27 */
	uपूर्णांक64_t reserved4;	/* 28-2F */
	uपूर्णांक64_t reserved5;	/* 30-37 */
	uपूर्णांक64_t reserved6;	/* 38-3F */
पूर्ण;

/* Status entry काष्ठाure*/
काष्ठा status_entry अणु
	काष्ठा qla4_header hdr;	/* 00-03 */

	uपूर्णांक32_t handle;	/* 04-07 */

	uपूर्णांक8_t scsiStatus;	/* 08 */

	uपूर्णांक8_t iscsiFlags;	/* 09 */
#घोषणा ISCSI_FLAG_RESIDUAL_UNDER	  0x02
#घोषणा ISCSI_FLAG_RESIDUAL_OVER	  0x04

	uपूर्णांक8_t iscsiResponse;	/* 0A */

	uपूर्णांक8_t completionStatus;	/* 0B */
#घोषणा SCS_COMPLETE			  0x00
#घोषणा SCS_INCOMPLETE			  0x01
#घोषणा SCS_RESET_OCCURRED		  0x04
#घोषणा SCS_ABORTED			  0x05
#घोषणा SCS_TIMEOUT			  0x06
#घोषणा SCS_DATA_OVERRUN		  0x07
#घोषणा SCS_DATA_UNDERRUN		  0x15
#घोषणा SCS_QUEUE_FULL			  0x1C
#घोषणा SCS_DEVICE_UNAVAILABLE		  0x28
#घोषणा SCS_DEVICE_LOGGED_OUT		  0x29

	uपूर्णांक8_t reserved1;	/* 0C */

	/* state_flags MUST be at the same location as state_flags in
	 * the Command_T3/4_Entry */
	uपूर्णांक8_t state_flags;	/* 0D */

	uपूर्णांक16_t senseDataByteCnt;	/* 0E-0F */
	uपूर्णांक32_t residualByteCnt;	/* 10-13 */
	uपूर्णांक32_t bidiResidualByteCnt;	/* 14-17 */
	uपूर्णांक32_t expSeqNum;	/* 18-1B */
	uपूर्णांक32_t maxCmdSeqNum;	/* 1C-1F */
	uपूर्णांक8_t senseData[IOCB_MAX_SENSEDATA_LEN];	/* 20-3F */

पूर्ण;

/* Status Continuation entry */
काष्ठा status_cont_entry अणु
       काष्ठा qla4_header hdr; /* 00-03 */
       uपूर्णांक8_t ext_sense_data[IOCB_MAX_EXT_SENSEDATA_LEN]; /* 04-63 */
पूर्ण;

काष्ठा passthru0 अणु
	काष्ठा qla4_header hdr;		       /* 00-03 */
	uपूर्णांक32_t handle;	/* 04-07 */
	uपूर्णांक16_t target;	/* 08-09 */
	uपूर्णांक16_t connection_id;	/* 0A-0B */
#घोषणा ISNS_DEFAULT_SERVER_CONN_ID	((uपूर्णांक16_t)0x8000)

	uपूर्णांक16_t control_flags;	/* 0C-0D */
#घोषणा PT_FLAG_ETHERNET_FRAME		0x8000
#घोषणा PT_FLAG_ISNS_PDU		0x8000
#घोषणा PT_FLAG_SEND_BUFFER		0x0200
#घोषणा PT_FLAG_WAIT_4_RESPONSE		0x0100
#घोषणा PT_FLAG_ISCSI_PDU		0x1000

	uपूर्णांक16_t समयout;	/* 0E-0F */
#घोषणा PT_DEFAULT_TIMEOUT		30 /* seconds */

	काष्ठा data_seg_a64 out_dsd;    /* 10-1B */
	uपूर्णांक32_t res1;		/* 1C-1F */
	काष्ठा data_seg_a64 in_dsd;     /* 20-2B */
	uपूर्णांक8_t res2[20];	/* 2C-3F */
पूर्ण;

काष्ठा passthru_status अणु
	काष्ठा qla4_header hdr;		       /* 00-03 */
	uपूर्णांक32_t handle;	/* 04-07 */
	uपूर्णांक16_t target;	/* 08-09 */
	uपूर्णांक16_t connectionID;	/* 0A-0B */

	uपूर्णांक8_t completionStatus;	/* 0C */
#घोषणा PASSTHRU_STATUS_COMPLETE		0x01

	uपूर्णांक8_t residualFlags;	/* 0D */

	uपूर्णांक16_t समयout;	/* 0E-0F */
	uपूर्णांक16_t portNumber;	/* 10-11 */
	uपूर्णांक8_t res1[10];	/* 12-1B */
	uपूर्णांक32_t outResidual;	/* 1C-1F */
	uपूर्णांक8_t res2[12];	/* 20-2B */
	uपूर्णांक32_t inResidual;	/* 2C-2F */
	uपूर्णांक8_t res4[16];	/* 30-3F */
पूर्ण;

काष्ठा mbox_cmd_iocb अणु
	काष्ठा qla4_header hdr;	/* 00-03 */
	uपूर्णांक32_t handle;	/* 04-07 */
	uपूर्णांक32_t in_mbox[8];	/* 08-25 */
	uपूर्णांक32_t res1[6];	/* 26-3F */
पूर्ण;

काष्ठा mbox_status_iocb अणु
	काष्ठा qla4_header hdr;	/* 00-03 */
	uपूर्णांक32_t handle;	/* 04-07 */
	uपूर्णांक32_t out_mbox[8];	/* 08-25 */
	uपूर्णांक32_t res1[6];	/* 26-3F */
पूर्ण;

/*
 * ISP queue - response queue entry definition.
 */
काष्ठा response अणु
	uपूर्णांक8_t data[60];
	uपूर्णांक32_t signature;
#घोषणा RESPONSE_PROCESSED	0xDEADDEAD	/* Signature */
पूर्ण;

काष्ठा ql_iscsi_stats अणु
	uपूर्णांक64_t mac_tx_frames; /* 0000ै 0007 */
	uपूर्णांक64_t mac_tx_bytes; /* 0008ै 000F */
	uपूर्णांक64_t mac_tx_multicast_frames; /* 0010ै 0017 */
	uपूर्णांक64_t mac_tx_broadcast_frames; /* 0018ै 001F */
	uपूर्णांक64_t mac_tx_छोड़ो_frames; /* 0020ै 0027 */
	uपूर्णांक64_t mac_tx_control_frames; /* 0028ै 002F */
	uपूर्णांक64_t mac_tx_deferral; /* 0030ै 0037 */
	uपूर्णांक64_t mac_tx_excess_deferral; /* 0038ै 003F */
	uपूर्णांक64_t mac_tx_late_collision; /* 0040ै 0047 */
	uपूर्णांक64_t mac_tx_पात; /* 0048ै 004F */
	uपूर्णांक64_t mac_tx_single_collision; /* 0050ै 0057 */
	uपूर्णांक64_t mac_tx_multiple_collision; /* 0058ै 005F */
	uपूर्णांक64_t mac_tx_collision; /* 0060ै 0067 */
	uपूर्णांक64_t mac_tx_frames_dropped; /* 0068ै 006F */
	uपूर्णांक64_t mac_tx_jumbo_frames; /* 0070ै 0077 */
	uपूर्णांक64_t mac_rx_frames; /* 0078ै 007F */
	uपूर्णांक64_t mac_rx_bytes; /* 0080ै 0087 */
	uपूर्णांक64_t mac_rx_unknown_control_frames; /* 0088ै 008F */
	uपूर्णांक64_t mac_rx_छोड़ो_frames; /* 0090ै 0097 */
	uपूर्णांक64_t mac_rx_control_frames; /* 0098ै 009F */
	uपूर्णांक64_t mac_rx_dribble; /* 00A0ै 00A7 */
	uपूर्णांक64_t mac_rx_frame_length_error; /* 00A8ै 00AF */
	uपूर्णांक64_t mac_rx_jabber; /* 00B0ै 00B7 */
	uपूर्णांक64_t mac_rx_carrier_sense_error; /* 00B8ै 00BF */
	uपूर्णांक64_t mac_rx_frame_discarded; /* 00C0ै 00C7 */
	uपूर्णांक64_t mac_rx_frames_dropped; /* 00C8ै 00CF */
	uपूर्णांक64_t mac_crc_error; /* 00D0ै 00D7 */
	uपूर्णांक64_t mac_encoding_error; /* 00D8ै 00DF */
	uपूर्णांक64_t mac_rx_length_error_large; /* 00E0ै 00E7 */
	uपूर्णांक64_t mac_rx_length_error_small; /* 00E8ै 00EF */
	uपूर्णांक64_t mac_rx_multicast_frames; /* 00F0ै 00F7 */
	uपूर्णांक64_t mac_rx_broadcast_frames; /* 00F8ै 00FF */
	uपूर्णांक64_t ip_tx_packets; /* 0100ै 0107 */
	uपूर्णांक64_t ip_tx_bytes; /* 0108ै 010F */
	uपूर्णांक64_t ip_tx_fragments; /* 0110ै 0117 */
	uपूर्णांक64_t ip_rx_packets; /* 0118ै 011F */
	uपूर्णांक64_t ip_rx_bytes; /* 0120ै 0127 */
	uपूर्णांक64_t ip_rx_fragments; /* 0128ै 012F */
	uपूर्णांक64_t ip_datagram_reassembly; /* 0130ै 0137 */
	uपूर्णांक64_t ip_invalid_address_error; /* 0138ै 013F */
	uपूर्णांक64_t ip_error_packets; /* 0140ै 0147 */
	uपूर्णांक64_t ip_fragrx_overlap; /* 0148ै 014F */
	uपूर्णांक64_t ip_fragrx_outoक्रमder; /* 0150ै 0157 */
	uपूर्णांक64_t ip_datagram_reassembly_समयout; /* 0158ै 015F */
	uपूर्णांक64_t ipv6_tx_packets; /* 0160ै 0167 */
	uपूर्णांक64_t ipv6_tx_bytes; /* 0168ै 016F */
	uपूर्णांक64_t ipv6_tx_fragments; /* 0170ै 0177 */
	uपूर्णांक64_t ipv6_rx_packets; /* 0178ै 017F */
	uपूर्णांक64_t ipv6_rx_bytes; /* 0180ै 0187 */
	uपूर्णांक64_t ipv6_rx_fragments; /* 0188ै 018F */
	uपूर्णांक64_t ipv6_datagram_reassembly; /* 0190ै 0197 */
	uपूर्णांक64_t ipv6_invalid_address_error; /* 0198ै 019F */
	uपूर्णांक64_t ipv6_error_packets; /* 01A0ै 01A7 */
	uपूर्णांक64_t ipv6_fragrx_overlap; /* 01A8ै 01AF */
	uपूर्णांक64_t ipv6_fragrx_outoक्रमder; /* 01B0ै 01B7 */
	uपूर्णांक64_t ipv6_datagram_reassembly_समयout; /* 01B8ै 01BF */
	uपूर्णांक64_t tcp_tx_segments; /* 01C0ै 01C7 */
	uपूर्णांक64_t tcp_tx_bytes; /* 01C8ै 01CF */
	uपूर्णांक64_t tcp_rx_segments; /* 01D0ै 01D7 */
	uपूर्णांक64_t tcp_rx_byte; /* 01D8ै 01DF */
	uपूर्णांक64_t tcp_duplicate_ack_retx; /* 01E0ै 01E7 */
	uपूर्णांक64_t tcp_retx_समयr_expired; /* 01E8ै 01EF */
	uपूर्णांक64_t tcp_rx_duplicate_ack; /* 01F0ै 01F7 */
	uपूर्णांक64_t tcp_rx_pure_ackr; /* 01F8ै 01FF */
	uपूर्णांक64_t tcp_tx_delayed_ack; /* 0200ै 0207 */
	uपूर्णांक64_t tcp_tx_pure_ack; /* 0208ै 020F */
	uपूर्णांक64_t tcp_rx_segment_error; /* 0210ै 0217 */
	uपूर्णांक64_t tcp_rx_segment_outoक्रमder; /* 0218ै 021F */
	uपूर्णांक64_t tcp_rx_winकरोw_probe; /* 0220ै 0227 */
	uपूर्णांक64_t tcp_rx_winकरोw_update; /* 0228ै 022F */
	uपूर्णांक64_t tcp_tx_winकरोw_probe_persist; /* 0230ै 0237 */
	uपूर्णांक64_t ecc_error_correction; /* 0238ै 023F */
	uपूर्णांक64_t iscsi_pdu_tx; /* 0240-0247 */
	uपूर्णांक64_t iscsi_data_bytes_tx; /* 0248-024F */
	uपूर्णांक64_t iscsi_pdu_rx; /* 0250-0257 */
	uपूर्णांक64_t iscsi_data_bytes_rx; /* 0258-025F */
	uपूर्णांक64_t iscsi_io_completed; /* 0260-0267 */
	uपूर्णांक64_t iscsi_unexpected_io_rx; /* 0268-026F */
	uपूर्णांक64_t iscsi_क्रमmat_error; /* 0270-0277 */
	uपूर्णांक64_t iscsi_hdr_digest_error; /* 0278-027F */
	uपूर्णांक64_t iscsi_data_digest_error; /* 0280-0287 */
	uपूर्णांक64_t iscsi_sequence_error; /* 0288-028F */
	uपूर्णांक32_t tx_cmd_pdu; /* 0290-0293 */
	uपूर्णांक32_t tx_resp_pdu; /* 0294-0297 */
	uपूर्णांक32_t rx_cmd_pdu; /* 0298-029B */
	uपूर्णांक32_t rx_resp_pdu; /* 029C-029F */

	uपूर्णांक64_t tx_data_octets; /* 02A0-02A7 */
	uपूर्णांक64_t rx_data_octets; /* 02A8-02AF */

	uपूर्णांक32_t hdr_digest_err; /* 02B0ै 02B3 */
	uपूर्णांक32_t data_digest_err; /* 02B4ै 02B7 */
	uपूर्णांक32_t conn_समयout_err; /* 02B8ै 02BB */
	uपूर्णांक32_t framing_err; /* 02BCै 02BF */

	uपूर्णांक32_t tx_nopout_pdus; /* 02C0ै 02C3 */
	uपूर्णांक32_t tx_scsi_cmd_pdus;  /* 02C4ै 02C7 */
	uपूर्णांक32_t tx_पंचांगf_cmd_pdus; /* 02C8ै 02CB */
	uपूर्णांक32_t tx_login_cmd_pdus; /* 02CCै 02CF */
	uपूर्णांक32_t tx_text_cmd_pdus; /* 02D0ै 02D3 */
	uपूर्णांक32_t tx_scsi_ग_लिखो_pdus; /* 02D4ै 02D7 */
	uपूर्णांक32_t tx_logout_cmd_pdus; /* 02D8ै 02DB */
	uपूर्णांक32_t tx_snack_req_pdus; /* 02DCै 02DF */

	uपूर्णांक32_t rx_nopin_pdus; /* 02E0ै 02E3 */
	uपूर्णांक32_t rx_scsi_resp_pdus; /* 02E4ै 02E7 */
	uपूर्णांक32_t rx_पंचांगf_resp_pdus; /* 02E8ै 02EB */
	uपूर्णांक32_t rx_login_resp_pdus; /* 02ECै 02EF */
	uपूर्णांक32_t rx_text_resp_pdus; /* 02F0ै 02F3 */
	uपूर्णांक32_t rx_scsi_पढ़ो_pdus; /* 02F4ै 02F7 */
	uपूर्णांक32_t rx_logout_resp_pdus; /* 02F8ै 02FB */

	uपूर्णांक32_t rx_r2t_pdus; /* 02FCै 02FF */
	uपूर्णांक32_t rx_async_pdus; /* 0300ै 0303 */
	uपूर्णांक32_t rx_reject_pdus; /* 0304ै 0307 */

	uपूर्णांक8_t reserved2[264]; /* 0x0308 - 0x040F */
पूर्ण;

#घोषणा QLA8XXX_DBG_STATE_ARRAY_LEN		16
#घोषणा QLA8XXX_DBG_CAP_SIZE_ARRAY_LEN		8
#घोषणा QLA8XXX_DBG_RSVD_ARRAY_LEN		8
#घोषणा QLA83XX_DBG_OCM_WNDREG_ARRAY_LEN	16
#घोषणा QLA83XX_SS_OCM_WNDREG_INDEX		3
#घोषणा QLA83XX_SS_PCI_INDEX			0
#घोषणा QLA8022_TEMPLATE_CAP_OFFSET		172
#घोषणा QLA83XX_TEMPLATE_CAP_OFFSET		268
#घोषणा QLA80XX_TEMPLATE_RESERVED_BITS		16

काष्ठा qla4_8xxx_minidump_ढाँचा_hdr अणु
	uपूर्णांक32_t entry_type;
	uपूर्णांक32_t first_entry_offset;
	uपूर्णांक32_t size_of_ढाँचा;
	uपूर्णांक32_t capture_debug_level;
	uपूर्णांक32_t num_of_entries;
	uपूर्णांक32_t version;
	uपूर्णांक32_t driver_बारtamp;
	uपूर्णांक32_t checksum;

	uपूर्णांक32_t driver_capture_mask;
	uपूर्णांक32_t driver_info_word2;
	uपूर्णांक32_t driver_info_word3;
	uपूर्णांक32_t driver_info_word4;

	uपूर्णांक32_t saved_state_array[QLA8XXX_DBG_STATE_ARRAY_LEN];
	uपूर्णांक32_t capture_size_array[QLA8XXX_DBG_CAP_SIZE_ARRAY_LEN];
	uपूर्णांक32_t ocm_winकरोw_reg[QLA83XX_DBG_OCM_WNDREG_ARRAY_LEN];
	uपूर्णांक32_t capabilities[QLA80XX_TEMPLATE_RESERVED_BITS];
पूर्ण;

#पूर्ण_अगर /*  _QLA4X_FW_H */
