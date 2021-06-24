<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/******************************************************************************
*                  QLOGIC LINUX SOFTWARE
*
* QLogic ISP1280 (Ultra2) /12160 (Ultra3) SCSI driver
* Copyright (C) 2000 Qlogic Corporation
* (www.qlogic.com)
*
******************************************************************************/

#अगर_अघोषित	_QLA1280_H
#घोषणा	_QLA1280_H

/*
 * Data bit definitions.
 */
#घोषणा BIT_0	0x1
#घोषणा BIT_1	0x2
#घोषणा BIT_2	0x4
#घोषणा BIT_3	0x8
#घोषणा BIT_4	0x10
#घोषणा BIT_5	0x20
#घोषणा BIT_6	0x40
#घोषणा BIT_7	0x80
#घोषणा BIT_8	0x100
#घोषणा BIT_9	0x200
#घोषणा BIT_10	0x400
#घोषणा BIT_11	0x800
#घोषणा BIT_12	0x1000
#घोषणा BIT_13	0x2000
#घोषणा BIT_14	0x4000
#घोषणा BIT_15	0x8000
#घोषणा BIT_16	0x10000
#घोषणा BIT_17	0x20000
#घोषणा BIT_18	0x40000
#घोषणा BIT_19	0x80000
#घोषणा BIT_20	0x100000
#घोषणा BIT_21	0x200000
#घोषणा BIT_22	0x400000
#घोषणा BIT_23	0x800000
#घोषणा BIT_24	0x1000000
#घोषणा BIT_25	0x2000000
#घोषणा BIT_26	0x4000000
#घोषणा BIT_27	0x8000000
#घोषणा BIT_28	0x10000000
#घोषणा BIT_29	0x20000000
#घोषणा BIT_30	0x40000000
#घोषणा BIT_31	0x80000000

#अगर MEMORY_MAPPED_IO
#घोषणा RD_REG_WORD(addr)		पढ़ोw_relaxed(addr)
#घोषणा RD_REG_WORD_dmasync(addr)	पढ़ोw(addr)
#घोषणा WRT_REG_WORD(addr, data)	ग_लिखोw(data, addr)
#अन्यथा				/* MEMORY_MAPPED_IO */
#घोषणा RD_REG_WORD(addr)		inw((अचिन्हित दीर्घ)addr)
#घोषणा RD_REG_WORD_dmasync(addr)	RD_REG_WORD(addr)
#घोषणा WRT_REG_WORD(addr, data)	outw(data, (अचिन्हित दीर्घ)addr)
#पूर्ण_अगर				/* MEMORY_MAPPED_IO */

/*
 * Host adapter शेष definitions.
 */
#घोषणा MAX_BUSES	2	/* 2 */
#घोषणा MAX_B_BITS	1

#घोषणा MAX_TARGETS	16	/* 16 */
#घोषणा MAX_T_BITS	4	/* 4 */

#घोषणा MAX_LUNS	8	/* 32 */
#घोषणा MAX_L_BITS	3	/* 5 */

/*
 * Watchकरोg समय quantum
 */
#घोषणा QLA1280_WDG_TIME_QUANTUM	5	/* In seconds */

/* Command retry count (0-65535) */
#घोषणा COMMAND_RETRY_COUNT		255

/* Maximum outstanding commands in ISP queues */
#घोषणा MAX_OUTSTANDING_COMMANDS	512
#घोषणा COMPLETED_HANDLE		((अचिन्हित अक्षर *) \
					(MAX_OUTSTANDING_COMMANDS + 2))

/* ISP request and response entry counts (37-65535) */
#घोषणा REQUEST_ENTRY_CNT		255 /* Number of request entries. */
#घोषणा RESPONSE_ENTRY_CNT		63  /* Number of response entries. */

/*
 * SCSI Request Block काष्ठाure  (sp)  that is placed
 * on cmd->SCp location of every I/O
 */
काष्ठा srb अणु
	काष्ठा list_head list;		/* (8/16) LU queue */
	काष्ठा scsi_cmnd *cmd;	/* (4/8) SCSI command block */
	/* NOTE: the sp->cmd will be शून्य when this completion is
	 * called, so you should know the scsi_cmnd when using this */
	काष्ठा completion *रुको;
	dma_addr_t saved_dma_handle;	/* क्रम unmap of single transfers */
	uपूर्णांक8_t flags;		/* (1) Status flags. */
	uपूर्णांक8_t dir;		/* direction of transfer */
पूर्ण;

/*
 * SRB flag definitions
 */
#घोषणा SRB_TIMEOUT		(1 << 0)	/* Command समयd out */
#घोषणा SRB_SENT		(1 << 1)	/* Command sent to ISP */
#घोषणा SRB_ABORT_PENDING	(1 << 2)	/* Command पात sent to device */
#घोषणा SRB_ABORTED		(1 << 3)	/* Command पातed command alपढ़ोy */

/*
 *  ISP I/O Register Set काष्ठाure definitions.
 */
काष्ठा device_reg अणु
	uपूर्णांक16_t id_l;		/* ID low */
	uपूर्णांक16_t id_h;		/* ID high */
	uपूर्णांक16_t cfg_0;		/* Configuration 0 */
#घोषणा ISP_CFG0_HWMSK   0x000f	/* Hardware revision mask */
#घोषणा ISP_CFG0_1020    BIT_0	/* ISP1020 */
#घोषणा ISP_CFG0_1020A	 BIT_1	/* ISP1020A */
#घोषणा ISP_CFG0_1040	 BIT_2	/* ISP1040 */
#घोषणा ISP_CFG0_1040A	 BIT_3	/* ISP1040A */
#घोषणा ISP_CFG0_1040B	 BIT_4	/* ISP1040B */
#घोषणा ISP_CFG0_1040C	 BIT_5	/* ISP1040C */
	uपूर्णांक16_t cfg_1;		/* Configuration 1 */
#घोषणा ISP_CFG1_F128    BIT_6  /* 128-byte FIFO threshold */
#घोषणा ISP_CFG1_F64     BIT_4|BIT_5 /* 128-byte FIFO threshold */
#घोषणा ISP_CFG1_F32     BIT_5  /* 128-byte FIFO threshold */
#घोषणा ISP_CFG1_F16     BIT_4  /* 128-byte FIFO threshold */
#घोषणा ISP_CFG1_BENAB   BIT_2  /* Global Bus burst enable */
#घोषणा ISP_CFG1_SXP     BIT_0  /* SXP रेजिस्टर select */
	uपूर्णांक16_t ictrl;		/* Interface control */
#घोषणा ISP_RESET        BIT_0	/* ISP soft reset */
#घोषणा ISP_EN_INT       BIT_1	/* ISP enable पूर्णांकerrupts. */
#घोषणा ISP_EN_RISC      BIT_2	/* ISP enable RISC पूर्णांकerrupts. */
#घोषणा ISP_FLASH_ENABLE BIT_8	/* Flash BIOS Read/Write enable */
#घोषणा ISP_FLASH_UPPER  BIT_9	/* Flash upper bank select */
	uपूर्णांक16_t istatus;	/* Interface status */
#घोषणा PCI_64BIT_SLOT   BIT_14	/* PCI 64-bit slot indicator. */
#घोषणा RISC_INT         BIT_2	/* RISC पूर्णांकerrupt */
#घोषणा PCI_INT          BIT_1	/* PCI पूर्णांकerrupt */
	uपूर्णांक16_t semaphore;	/* Semaphore */
	uपूर्णांक16_t nvram;		/* NVRAM रेजिस्टर. */
#घोषणा NV_DESELECT     0
#घोषणा NV_CLOCK        BIT_0
#घोषणा NV_SELECT       BIT_1
#घोषणा NV_DATA_OUT     BIT_2
#घोषणा NV_DATA_IN      BIT_3
	uपूर्णांक16_t flash_data;	/* Flash BIOS data */
	uपूर्णांक16_t flash_address;	/* Flash BIOS address */

	uपूर्णांक16_t unused_1[0x06];
	
	/* cdma_* and ddma_* are 1040 only */
	uपूर्णांक16_t cdma_cfg;
#घोषणा CDMA_CONF_SENAB  BIT_3	/* SXP to DMA Data enable */
#घोषणा CDMA_CONF_RIRQ   BIT_2	/* RISC पूर्णांकerrupt enable */
#घोषणा CDMA_CONF_BENAB  BIT_1	/* Bus burst enable */
#घोषणा CDMA_CONF_सूची    BIT_0	/* DMA direction (0=fअगरo->host 1=host->fअगरo) */
	uपूर्णांक16_t cdma_ctrl; 
	uपूर्णांक16_t cdma_status;   
	uपूर्णांक16_t cdma_fअगरo_status;
	uपूर्णांक16_t cdma_count;
	uपूर्णांक16_t cdma_reserved;
	uपूर्णांक16_t cdma_address_count_0;
	uपूर्णांक16_t cdma_address_count_1;
	uपूर्णांक16_t cdma_address_count_2;
	uपूर्णांक16_t cdma_address_count_3;

	uपूर्णांक16_t unused_2[0x06];

	uपूर्णांक16_t ddma_cfg;
#घोषणा DDMA_CONF_SENAB  BIT_3	/* SXP to DMA Data enable */
#घोषणा DDMA_CONF_RIRQ   BIT_2	/* RISC पूर्णांकerrupt enable */
#घोषणा DDMA_CONF_BENAB  BIT_1	/* Bus burst enable */
#घोषणा DDMA_CONF_सूची    BIT_0	/* DMA direction (0=fअगरo->host 1=host->fअगरo) */
	uपूर्णांक16_t ddma_ctrl;
	uपूर्णांक16_t ddma_status; 
	uपूर्णांक16_t ddma_fअगरo_status;
	uपूर्णांक16_t ddma_xfer_count_low;
	uपूर्णांक16_t ddma_xfer_count_high;
	uपूर्णांक16_t ddma_addr_count_0;
	uपूर्णांक16_t ddma_addr_count_1;
	uपूर्णांक16_t ddma_addr_count_2;
	uपूर्णांक16_t ddma_addr_count_3; 

	uपूर्णांक16_t unused_3[0x0e];

	uपूर्णांक16_t mailbox0;	/* Mailbox 0 */
	uपूर्णांक16_t mailbox1;	/* Mailbox 1 */
	uपूर्णांक16_t mailbox2;	/* Mailbox 2 */
	uपूर्णांक16_t mailbox3;	/* Mailbox 3 */
	uपूर्णांक16_t mailbox4;	/* Mailbox 4 */
	uपूर्णांक16_t mailbox5;	/* Mailbox 5 */
	uपूर्णांक16_t mailbox6;	/* Mailbox 6 */
	uपूर्णांक16_t mailbox7;	/* Mailbox 7 */

	uपूर्णांक16_t unused_4[0x20];/* 0x80-0xbf Gap */

	uपूर्णांक16_t host_cmd;	/* Host command and control */
#घोषणा HOST_INT      BIT_7	/* host पूर्णांकerrupt bit */
#घोषणा BIOS_ENABLE   BIT_0

	uपूर्णांक16_t unused_5[0x5];	/* 0xc2-0xcb Gap */

	uपूर्णांक16_t gpio_data;
	uपूर्णांक16_t gpio_enable;

	uपूर्णांक16_t unused_6[0x11];	/* d0-f0 */
	uपूर्णांक16_t scsiControlPins;	/* f2 */
पूर्ण;

#घोषणा MAILBOX_REGISTER_COUNT	8

/*
 *  ISP product identअगरication definitions in mailboxes after reset.
 */
#घोषणा PROD_ID_1		0x4953
#घोषणा PROD_ID_2		0x0000
#घोषणा PROD_ID_2a		0x5020
#घोषणा PROD_ID_3		0x2020
#घोषणा PROD_ID_4		0x1

/*
 * ISP host command and control रेजिस्टर command definitions
 */
#घोषणा HC_RESET_RISC		0x1000	/* Reset RISC */
#घोषणा HC_PAUSE_RISC		0x2000	/* Pause RISC */
#घोषणा HC_RELEASE_RISC		0x3000	/* Release RISC from reset. */
#घोषणा HC_SET_HOST_INT		0x5000	/* Set host पूर्णांकerrupt */
#घोषणा HC_CLR_HOST_INT		0x6000	/* Clear HOST पूर्णांकerrupt */
#घोषणा HC_CLR_RISC_INT		0x7000	/* Clear RISC पूर्णांकerrupt */
#घोषणा HC_DISABLE_BIOS		0x9000	/* Disable BIOS. */

/*
 * ISP mailbox Self-Test status codes
 */
#घोषणा MBS_FRM_ALIVE		0	/* Firmware Alive. */
#घोषणा MBS_CHKSUM_ERR		1	/* Checksum Error. */
#घोषणा MBS_SHADOW_LD_ERR	2	/* Shaकरोw Load Error. */
#घोषणा MBS_BUSY		4	/* Busy. */

/*
 * ISP mailbox command complete status codes
 */
#घोषणा MBS_CMD_CMP		0x4000	/* Command Complete. */
#घोषणा MBS_INV_CMD		0x4001	/* Invalid Command. */
#घोषणा MBS_HOST_INF_ERR	0x4002	/* Host Interface Error. */
#घोषणा MBS_TEST_FAILED		0x4003	/* Test Failed. */
#घोषणा MBS_CMD_ERR		0x4005	/* Command Error. */
#घोषणा MBS_CMD_PARAM_ERR	0x4006	/* Command Parameter Error. */

/*
 * ISP mailbox asynchronous event status codes
 */
#घोषणा MBA_ASYNC_EVENT		0x8000	/* Asynchronous event. */
#घोषणा MBA_BUS_RESET		0x8001	/* SCSI Bus Reset. */
#घोषणा MBA_SYSTEM_ERR		0x8002	/* System Error. */
#घोषणा MBA_REQ_TRANSFER_ERR	0x8003	/* Request Transfer Error. */
#घोषणा MBA_RSP_TRANSFER_ERR	0x8004	/* Response Transfer Error. */
#घोषणा MBA_WAKEUP_THRES	0x8005	/* Request Queue Wake-up. */
#घोषणा MBA_TIMEOUT_RESET	0x8006	/* Execution Timeout Reset. */
#घोषणा MBA_DEVICE_RESET	0x8007	/* Bus Device Reset. */
#घोषणा MBA_BUS_MODE_CHANGE	0x800E	/* SCSI bus mode transition. */
#घोषणा MBA_SCSI_COMPLETION	0x8020	/* Completion response. */

/*
 * ISP mailbox commands
 */
#घोषणा MBC_NOP				0	/* No Operation */
#घोषणा MBC_LOAD_RAM			1	/* Load RAM */
#घोषणा MBC_EXECUTE_FIRMWARE		2	/* Execute firmware */
#घोषणा MBC_DUMP_RAM			3	/* Dump RAM contents */
#घोषणा MBC_WRITE_RAM_WORD		4	/* Write ram word */
#घोषणा MBC_READ_RAM_WORD		5	/* Read ram word */
#घोषणा MBC_MAILBOX_REGISTER_TEST	6	/* Wrap incoming mailboxes */
#घोषणा MBC_VERIFY_CHECKSUM		7	/* Verअगरy checksum */
#घोषणा MBC_ABOUT_FIRMWARE		8	/* Get firmware revision */
#घोषणा MBC_LOAD_RAM_A64_ROM		9	/* Load RAM 64bit ROM version */
#घोषणा MBC_DUMP_RAM_A64_ROM		0x0a	/* Dump RAM 64bit ROM version */
#घोषणा MBC_INIT_REQUEST_QUEUE		0x10	/* Initialize request queue */
#घोषणा MBC_INIT_RESPONSE_QUEUE		0x11	/* Initialize response queue */
#घोषणा MBC_EXECUTE_IOCB		0x12	/* Execute IOCB command */
#घोषणा MBC_ABORT_COMMAND		0x15	/* Abort IOCB command */
#घोषणा MBC_ABORT_DEVICE		0x16	/* Abort device (ID/LUN) */
#घोषणा MBC_ABORT_TARGET		0x17	/* Abort target (ID) */
#घोषणा MBC_BUS_RESET			0x18	/* SCSI bus reset */
#घोषणा MBC_GET_RETRY_COUNT		0x22	/* Get retry count and delay */
#घोषणा MBC_GET_TARGET_PARAMETERS	0x28	/* Get target parameters */
#घोषणा MBC_SET_INITIATOR_ID		0x30	/* Set initiator SCSI ID */
#घोषणा MBC_SET_SELECTION_TIMEOUT	0x31	/* Set selection समयout */
#घोषणा MBC_SET_RETRY_COUNT		0x32	/* Set retry count and delay */
#घोषणा MBC_SET_TAG_AGE_LIMIT		0x33	/* Set tag age limit */
#घोषणा MBC_SET_CLOCK_RATE		0x34	/* Set घड़ी rate */
#घोषणा MBC_SET_ACTIVE_NEGATION		0x35	/* Set active negation state */
#घोषणा MBC_SET_ASYNC_DATA_SETUP	0x36	/* Set async data setup समय */
#घोषणा MBC_SET_PCI_CONTROL		0x37	/* Set BUS control parameters */
#घोषणा MBC_SET_TARGET_PARAMETERS	0x38	/* Set target parameters */
#घोषणा MBC_SET_DEVICE_QUEUE		0x39	/* Set device queue parameters */
#घोषणा MBC_SET_RESET_DELAY_PARAMETERS	0x3A	/* Set reset delay parameters */
#घोषणा MBC_SET_SYSTEM_PARAMETER	0x45	/* Set प्रणाली parameter word */
#घोषणा MBC_SET_FIRMWARE_FEATURES	0x4A	/* Set firmware feature word */
#घोषणा MBC_INIT_REQUEST_QUEUE_A64	0x52	/* Initialize request queue A64 */
#घोषणा MBC_INIT_RESPONSE_QUEUE_A64	0x53	/* Initialize response q A64 */
#घोषणा MBC_ENABLE_TARGET_MODE		0x55	/* Enable target mode */
#घोषणा MBC_SET_DATA_OVERRUN_RECOVERY	0x5A	/* Set data overrun recovery mode */

/*
 * ISP Get/Set Target Parameters mailbox command control flags.
 */
#घोषणा TP_PPR			BIT_5	/* PPR */
#घोषणा TP_RENEGOTIATE		BIT_8	/* Renegotiate on error. */
#घोषणा TP_STOP_QUEUE           BIT_9	/* Stop que on check condition */
#घोषणा TP_AUTO_REQUEST_SENSE   BIT_10	/* Automatic request sense. */
#घोषणा TP_TAGGED_QUEUE         BIT_11	/* Tagged queuing. */
#घोषणा TP_SYNC                 BIT_12	/* Synchronous data transfers. */
#घोषणा TP_WIDE                 BIT_13	/* Wide data transfers. */
#घोषणा TP_PARITY               BIT_14	/* Parity checking. */
#घोषणा TP_DISCONNECT           BIT_15	/* Disconnect privilege. */

/*
 * NVRAM Command values.
 */
#घोषणा NV_START_BIT		BIT_2
#घोषणा NV_WRITE_OP		(BIT_26 | BIT_24)
#घोषणा NV_READ_OP		(BIT_26 | BIT_25)
#घोषणा NV_ERASE_OP		(BIT_26 | BIT_25 | BIT_24)
#घोषणा NV_MASK_OP		(BIT_26 | BIT_25 | BIT_24)
#घोषणा NV_DELAY_COUNT		10

/*
 *  QLogic ISP1280/ISP12160 NVRAM काष्ठाure definition.
 */
काष्ठा nvram अणु
	uपूर्णांक8_t id0;		/* 0 */
	uपूर्णांक8_t id1;		/* 1 */
	uपूर्णांक8_t id2;		/* 2 */
	uपूर्णांक8_t id3;		/* 3 */
	uपूर्णांक8_t version;	/* 4 */

	काष्ठा अणु
		uपूर्णांक8_t bios_configuration_mode:2;
		uपूर्णांक8_t bios_disable:1;
		uपूर्णांक8_t selectable_scsi_boot_enable:1;
		uपूर्णांक8_t cd_rom_boot_enable:1;
		uपूर्णांक8_t disable_loading_risc_code:1;
		uपूर्णांक8_t enable_64bit_addressing:1;
		uपूर्णांक8_t unused_7:1;
	पूर्ण cntr_flags_1;		/* 5 */

	काष्ठा अणु
		uपूर्णांक8_t boot_lun_number:5;
		uपूर्णांक8_t scsi_bus_number:1;
		uपूर्णांक8_t unused_6:1;
		uपूर्णांक8_t unused_7:1;
	पूर्ण cntr_flags_2l;	/* 7 */

	काष्ठा अणु
		uपूर्णांक8_t boot_target_number:4;
		uपूर्णांक8_t unused_12:1;
		uपूर्णांक8_t unused_13:1;
		uपूर्णांक8_t unused_14:1;
		uपूर्णांक8_t unused_15:1;
	पूर्ण cntr_flags_2h;	/* 8 */

	uपूर्णांक16_t unused_8;	/* 8, 9 */
	uपूर्णांक16_t unused_10;	/* 10, 11 */
	uपूर्णांक16_t unused_12;	/* 12, 13 */
	uपूर्णांक16_t unused_14;	/* 14, 15 */

	काष्ठा अणु
		uपूर्णांक8_t reserved:2;
		uपूर्णांक8_t burst_enable:1;
		uपूर्णांक8_t reserved_1:1;
		uपूर्णांक8_t fअगरo_threshold:4;
	पूर्ण isp_config;		/* 16 */

	/* Termination
	 * 0 = Disable, 1 = high only, 3 = Auto term
	 */
	काष्ठा अणु
		uपूर्णांक8_t scsi_bus_1_control:2;
		uपूर्णांक8_t scsi_bus_0_control:2;
		uपूर्णांक8_t unused_0:1;
		uपूर्णांक8_t unused_1:1;
		uपूर्णांक8_t unused_2:1;
		uपूर्णांक8_t स्वतः_term_support:1;
	पूर्ण termination;		/* 17 */

	uपूर्णांक16_t isp_parameter;	/* 18, 19 */

	जोड़ अणु
		uपूर्णांक16_t w;
		काष्ठा अणु
			uपूर्णांक16_t enable_fast_posting:1;
			uपूर्णांक16_t report_lvd_bus_transition:1;
			uपूर्णांक16_t unused_2:1;
			uपूर्णांक16_t unused_3:1;
			uपूर्णांक16_t disable_iosbs_with_bus_reset_status:1;
			uपूर्णांक16_t disable_synchronous_backoff:1;
			uपूर्णांक16_t unused_6:1;
			uपूर्णांक16_t synchronous_backoff_reporting:1;
			uपूर्णांक16_t disable_reselection_fairness:1;
			uपूर्णांक16_t unused_9:1;
			uपूर्णांक16_t unused_10:1;
			uपूर्णांक16_t unused_11:1;
			uपूर्णांक16_t unused_12:1;
			uपूर्णांक16_t unused_13:1;
			uपूर्णांक16_t unused_14:1;
			uपूर्णांक16_t unused_15:1;
		पूर्ण f;
	पूर्ण firmware_feature;	/* 20, 21 */

	uपूर्णांक16_t unused_22;	/* 22, 23 */

	काष्ठा अणु
		काष्ठा अणु
			uपूर्णांक8_t initiator_id:4;
			uपूर्णांक8_t scsi_reset_disable:1;
			uपूर्णांक8_t scsi_bus_size:1;
			uपूर्णांक8_t scsi_bus_type:1;
			uपूर्णांक8_t unused_7:1;
		पूर्ण config_1;	/* 24 */

		uपूर्णांक8_t bus_reset_delay;	/* 25 */
		uपूर्णांक8_t retry_count;	/* 26 */
		uपूर्णांक8_t retry_delay;	/* 27 */

		काष्ठा अणु
			uपूर्णांक8_t async_data_setup_समय:4;
			uपूर्णांक8_t req_ack_active_negation:1;
			uपूर्णांक8_t data_line_active_negation:1;
			uपूर्णांक8_t unused_6:1;
			uपूर्णांक8_t unused_7:1;
		पूर्ण config_2;	/* 28 */

		uपूर्णांक8_t unused_29;	/* 29 */

		uपूर्णांक16_t selection_समयout;	/* 30, 31 */
		uपूर्णांक16_t max_queue_depth;	/* 32, 33 */

		uपूर्णांक16_t unused_34;	/* 34, 35 */
		uपूर्णांक16_t unused_36;	/* 36, 37 */
		uपूर्णांक16_t unused_38;	/* 38, 39 */

		काष्ठा अणु
			काष्ठा अणु
				uपूर्णांक8_t renegotiate_on_error:1;
				uपूर्णांक8_t stop_queue_on_check:1;
				uपूर्णांक8_t स्वतः_request_sense:1;
				uपूर्णांक8_t tag_queuing:1;
				uपूर्णांक8_t enable_sync:1;
				uपूर्णांक8_t enable_wide:1;
				uपूर्णांक8_t parity_checking:1;
				uपूर्णांक8_t disconnect_allowed:1;
			पूर्ण parameter;	/* 40 */

			uपूर्णांक8_t execution_throttle;	/* 41 */
			uपूर्णांक8_t sync_period;	/* 42 */

			जोड़ अणु		/* 43 */
				uपूर्णांक8_t flags_43;
				काष्ठा अणु
					uपूर्णांक8_t sync_offset:4;
					uपूर्णांक8_t device_enable:1;
					uपूर्णांक8_t lun_disable:1;
					uपूर्णांक8_t unused_6:1;
					uपूर्णांक8_t unused_7:1;
				पूर्ण flags1x80;
				काष्ठा अणु
					uपूर्णांक8_t sync_offset:5;
					uपूर्णांक8_t device_enable:1;
					uपूर्णांक8_t unused_6:1;
					uपूर्णांक8_t unused_7:1;
				पूर्ण flags1x160;
			पूर्ण flags;
			जोड़ अणु	/* PPR flags क्रम the 1x160 controllers */
				uपूर्णांक8_t unused_44;
				काष्ठा अणु
					uपूर्णांक8_t ppr_options:4;
					uपूर्णांक8_t ppr_bus_width:2;
					uपूर्णांक8_t unused_8:1;
					uपूर्णांक8_t enable_ppr:1;
				पूर्ण flags;	/* 44 */
			पूर्ण ppr_1x160;
			uपूर्णांक8_t unused_45;	/* 45 */
		पूर्ण target[MAX_TARGETS];
	पूर्ण bus[MAX_BUSES];

	uपूर्णांक16_t unused_248;	/* 248, 249 */

	uपूर्णांक16_t subप्रणाली_id[2];	/* 250, 251, 252, 253 */

	जोड़ अणु				/* 254 */
		uपूर्णांक8_t unused_254;
		uपूर्णांक8_t प्रणाली_id_poपूर्णांकer;
	पूर्ण sysid_1x160;

	uपूर्णांक8_t chksum;		/* 255 */
पूर्ण;

/*
 * ISP queue - command entry काष्ठाure definition.
 */
#घोषणा MAX_CMDSZ	12		/* SCSI maximum CDB size. */
काष्ठा cmd_entry अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
#घोषणा COMMAND_TYPE    1		/* Command entry */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */
	__le32 handle;			/* System handle. */
	uपूर्णांक8_t lun;			/* SCSI LUN */
	uपूर्णांक8_t target;			/* SCSI ID */
	__le16 cdb_len;			/* SCSI command length. */
	__le16 control_flags;		/* Control flags. */
	__le16 reserved;
	__le16 समयout;			/* Command समयout. */
	__le16 dseg_count;		/* Data segment count. */
	uपूर्णांक8_t scsi_cdb[MAX_CMDSZ];	/* SCSI command words. */
	__le32 dseg_0_address;		/* Data segment 0 address. */
	__le32 dseg_0_length;		/* Data segment 0 length. */
	__le32 dseg_1_address;		/* Data segment 1 address. */
	__le32 dseg_1_length;		/* Data segment 1 length. */
	__le32 dseg_2_address;		/* Data segment 2 address. */
	__le32 dseg_2_length;		/* Data segment 2 length. */
	__le32 dseg_3_address;		/* Data segment 3 address. */
	__le32 dseg_3_length;		/* Data segment 3 length. */
पूर्ण;

/*
 * ISP queue - continuation entry काष्ठाure definition.
 */
काष्ठा cont_entry अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
#घोषणा CONTINUE_TYPE   2		/* Continuation entry. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */
	__le32 reserved;		/* Reserved */
	__le32 dseg_0_address;		/* Data segment 0 address. */
	__le32 dseg_0_length;		/* Data segment 0 length. */
	__le32 dseg_1_address;		/* Data segment 1 address. */
	__le32 dseg_1_length;		/* Data segment 1 length. */
	__le32 dseg_2_address;		/* Data segment 2 address. */
	__le32 dseg_2_length;		/* Data segment 2 length. */
	__le32 dseg_3_address;		/* Data segment 3 address. */
	__le32 dseg_3_length;		/* Data segment 3 length. */
	__le32 dseg_4_address;		/* Data segment 4 address. */
	__le32 dseg_4_length;		/* Data segment 4 length. */
	__le32 dseg_5_address;		/* Data segment 5 address. */
	__le32 dseg_5_length;		/* Data segment 5 length. */
	__le32 dseg_6_address;		/* Data segment 6 address. */
	__le32 dseg_6_length;		/* Data segment 6 length. */
पूर्ण;

/*
 * ISP queue - status entry काष्ठाure definition.
 */
काष्ठा response अणु
	uपूर्णांक8_t entry_type;	/* Entry type. */
#घोषणा STATUS_TYPE     3	/* Status entry. */
	uपूर्णांक8_t entry_count;	/* Entry count. */
	uपूर्णांक8_t sys_define;	/* System defined. */
	uपूर्णांक8_t entry_status;	/* Entry Status. */
#घोषणा RF_CONT         BIT_0	/* Continuation. */
#घोषणा RF_FULL         BIT_1	/* Full */
#घोषणा RF_BAD_HEADER   BIT_2	/* Bad header. */
#घोषणा RF_BAD_PAYLOAD  BIT_3	/* Bad payload. */
	__le32 handle;		/* System handle. */
	__le16 scsi_status;	/* SCSI status. */
	__le16 comp_status;	/* Completion status. */
	__le16 state_flags;	/* State flags. */
#घोषणा SF_TRANSFER_CMPL	BIT_14	/* Transfer Complete. */
#घोषणा SF_GOT_SENSE	 	BIT_13	/* Got Sense */
#घोषणा SF_GOT_STATUS	 	BIT_12	/* Got Status */
#घोषणा SF_TRANSFERRED_DATA	BIT_11	/* Transferred data */
#घोषणा SF_SENT_CDB	 	BIT_10	/* Send CDB */
#घोषणा SF_GOT_TARGET	 	BIT_9	/*  */
#घोषणा SF_GOT_BUS	 	BIT_8	/*  */
	__le16 status_flags;	/* Status flags. */
	__le16 समय;		/* Time. */
	__le16 req_sense_length;/* Request sense data length. */
	__le32 residual_length;	/* Residual transfer length. */
	__le16 reserved[4];
	uपूर्णांक8_t req_sense_data[32];	/* Request sense data. */
पूर्ण;

/*
 * ISP queue - marker entry काष्ठाure definition.
 */
काष्ठा mrk_entry अणु
	uपूर्णांक8_t entry_type;	/* Entry type. */
#घोषणा MARKER_TYPE     4	/* Marker entry. */
	uपूर्णांक8_t entry_count;	/* Entry count. */
	uपूर्णांक8_t sys_define;	/* System defined. */
	uपूर्णांक8_t entry_status;	/* Entry Status. */
	__le32 reserved;
	uपूर्णांक8_t lun;		/* SCSI LUN */
	uपूर्णांक8_t target;		/* SCSI ID */
	uपूर्णांक8_t modअगरier;	/* Modअगरier (7-0). */
#घोषणा MK_SYNC_ID_LUN      0	/* Synchronize ID/LUN */
#घोषणा MK_SYNC_ID          1	/* Synchronize ID */
#घोषणा MK_SYNC_ALL         2	/* Synchronize all ID/LUN */
	uपूर्णांक8_t reserved_1[53];
पूर्ण;

/*
 * ISP queue - extended command entry काष्ठाure definition.
 *
 * Unused by the driver!
 */
काष्ठा ecmd_entry अणु
	uपूर्णांक8_t entry_type;	/* Entry type. */
#घोषणा EXTENDED_CMD_TYPE  5	/* Extended command entry. */
	uपूर्णांक8_t entry_count;	/* Entry count. */
	uपूर्णांक8_t sys_define;	/* System defined. */
	uपूर्णांक8_t entry_status;	/* Entry Status. */
	uपूर्णांक32_t handle;	/* System handle. */
	uपूर्णांक8_t lun;		/* SCSI LUN */
	uपूर्णांक8_t target;		/* SCSI ID */
	__le16 cdb_len;		/* SCSI command length. */
	__le16 control_flags;	/* Control flags. */
	__le16 reserved;
	__le16 समयout;		/* Command समयout. */
	__le16 dseg_count;	/* Data segment count. */
	uपूर्णांक8_t scsi_cdb[88];	/* SCSI command words. */
पूर्ण;

/*
 * ISP queue - 64-Bit addressing, command entry काष्ठाure definition.
 */
प्रकार काष्ठा अणु
	uपूर्णांक8_t entry_type;	/* Entry type. */
#घोषणा COMMAND_A64_TYPE 9	/* Command A64 entry */
	uपूर्णांक8_t entry_count;	/* Entry count. */
	uपूर्णांक8_t sys_define;	/* System defined. */
	uपूर्णांक8_t entry_status;	/* Entry Status. */
	__le32 handle;	/* System handle. */
	uपूर्णांक8_t lun;		/* SCSI LUN */
	uपूर्णांक8_t target;		/* SCSI ID */
	__le16 cdb_len;	/* SCSI command length. */
	__le16 control_flags;	/* Control flags. */
	__le16 reserved;
	__le16 समयout;	/* Command समयout. */
	__le16 dseg_count;	/* Data segment count. */
	uपूर्णांक8_t scsi_cdb[MAX_CMDSZ];	/* SCSI command words. */
	__le32 reserved_1[2];	/* unused */
	__le32 dseg_0_address[2];	/* Data segment 0 address. */
	__le32 dseg_0_length;	/* Data segment 0 length. */
	__le32 dseg_1_address[2];	/* Data segment 1 address. */
	__le32 dseg_1_length;	/* Data segment 1 length. */
पूर्ण cmd_a64_entry_t, request_t;

/*
 * ISP queue - 64-Bit addressing, continuation entry काष्ठाure definition.
 */
काष्ठा cont_a64_entry अणु
	uपूर्णांक8_t entry_type;	/* Entry type. */
#घोषणा CONTINUE_A64_TYPE 0xA	/* Continuation A64 entry. */
	uपूर्णांक8_t entry_count;	/* Entry count. */
	uपूर्णांक8_t sys_define;	/* System defined. */
	uपूर्णांक8_t entry_status;	/* Entry Status. */
	__le32 dseg_0_address[2];	/* Data segment 0 address. */
	__le32 dseg_0_length;		/* Data segment 0 length. */
	__le32 dseg_1_address[2];	/* Data segment 1 address. */
	__le32 dseg_1_length;		/* Data segment 1 length. */
	__le32 dseg_2_address[2];	/* Data segment 2 address. */
	__le32 dseg_2_length;		/* Data segment 2 length. */
	__le32 dseg_3_address[2];	/* Data segment 3 address. */
	__le32 dseg_3_length;		/* Data segment 3 length. */
	__le32 dseg_4_address[2];	/* Data segment 4 address. */
	__le32 dseg_4_length;		/* Data segment 4 length. */
पूर्ण;

/*
 * ISP queue - enable LUN entry काष्ठाure definition.
 */
काष्ठा elun_entry अणु
	uपूर्णांक8_t entry_type;	/* Entry type. */
#घोषणा ENABLE_LUN_TYPE 0xB	/* Enable LUN entry. */
	uपूर्णांक8_t entry_count;	/* Entry count. */
	uपूर्णांक8_t reserved_1;
	uपूर्णांक8_t entry_status;	/* Entry Status not used. */
	__le32 reserved_2;
	__le16 lun;		/* Bit 15 is bus number. */
	__le16 reserved_4;
	__le32 option_flags;
	uपूर्णांक8_t status;
	uपूर्णांक8_t reserved_5;
	uपूर्णांक8_t command_count;	/* Number of ATIOs allocated. */
	uपूर्णांक8_t immed_notअगरy_count;	/* Number of Immediate Notअगरy */
	/* entries allocated. */
	uपूर्णांक8_t group_6_length;	/* SCSI CDB length क्रम group 6 */
	/* commands (2-26). */
	uपूर्णांक8_t group_7_length;	/* SCSI CDB length क्रम group 7 */
	/* commands (2-26). */
	__le16 समयout;		/* 0 = 30 seconds, 0xFFFF = disable */
	__le16 reserved_6[20];
पूर्ण;

/*
 * ISP queue - modअगरy LUN entry काष्ठाure definition.
 *
 * Unused by the driver!
 */
काष्ठा modअगरy_lun_entry अणु
	uपूर्णांक8_t entry_type;	/* Entry type. */
#घोषणा MODIFY_LUN_TYPE 0xC	/* Modअगरy LUN entry. */
	uपूर्णांक8_t entry_count;	/* Entry count. */
	uपूर्णांक8_t reserved_1;
	uपूर्णांक8_t entry_status;	/* Entry Status. */
	__le32 reserved_2;
	uपूर्णांक8_t lun;		/* SCSI LUN */
	uपूर्णांक8_t reserved_3;
	uपूर्णांक8_t चालकs;
	uपूर्णांक8_t reserved_4;
	__le32 option_flags;
	uपूर्णांक8_t status;
	uपूर्णांक8_t reserved_5;
	uपूर्णांक8_t command_count;	/* Number of ATIOs allocated. */
	uपूर्णांक8_t immed_notअगरy_count;	/* Number of Immediate Notअगरy */
	/* entries allocated. */
	__le16 reserved_6;
	__le16 समयout;		/* 0 = 30 seconds, 0xFFFF = disable */
	__le16 reserved_7[20];
पूर्ण;

/*
 * ISP queue - immediate notअगरy entry काष्ठाure definition.
 */
काष्ठा notअगरy_entry अणु
	uपूर्णांक8_t entry_type;	/* Entry type. */
#घोषणा IMMED_NOTIFY_TYPE 0xD	/* Immediate notअगरy entry. */
	uपूर्णांक8_t entry_count;	/* Entry count. */
	uपूर्णांक8_t reserved_1;
	uपूर्णांक8_t entry_status;	/* Entry Status. */
	__le32 reserved_2;
	uपूर्णांक8_t lun;
	uपूर्णांक8_t initiator_id;
	uपूर्णांक8_t reserved_3;
	uपूर्णांक8_t target_id;
	__le32 option_flags;
	uपूर्णांक8_t status;
	uपूर्णांक8_t reserved_4;
	uपूर्णांक8_t tag_value;	/* Received queue tag message value */
	uपूर्णांक8_t tag_type;	/* Received queue tag message type */
	/* entries allocated. */
	__le16 seq_id;
	uपूर्णांक8_t scsi_msg[8];	/* SCSI message not handled by ISP */
	__le16 reserved_5[8];
	uपूर्णांक8_t sense_data[18];
पूर्ण;

/*
 * ISP queue - notअगरy acknowledge entry काष्ठाure definition.
 */
काष्ठा nack_entry अणु
	uपूर्णांक8_t entry_type;	/* Entry type. */
#घोषणा NOTIFY_ACK_TYPE 0xE	/* Notअगरy acknowledge entry. */
	uपूर्णांक8_t entry_count;	/* Entry count. */
	uपूर्णांक8_t reserved_1;
	uपूर्णांक8_t entry_status;	/* Entry Status. */
	__le32 reserved_2;
	uपूर्णांक8_t lun;
	uपूर्णांक8_t initiator_id;
	uपूर्णांक8_t reserved_3;
	uपूर्णांक8_t target_id;
	__le32 option_flags;
	uपूर्णांक8_t status;
	uपूर्णांक8_t event;
	__le16 seq_id;
	__le16 reserved_4[22];
पूर्ण;

/*
 * ISP queue - Accept Target I/O (ATIO) entry काष्ठाure definition.
 */
काष्ठा atio_entry अणु
	uपूर्णांक8_t entry_type;	/* Entry type. */
#घोषणा ACCEPT_TGT_IO_TYPE 6	/* Accept target I/O entry. */
	uपूर्णांक8_t entry_count;	/* Entry count. */
	uपूर्णांक8_t reserved_1;
	uपूर्णांक8_t entry_status;	/* Entry Status. */
	__le32 reserved_2;
	uपूर्णांक8_t lun;
	uपूर्णांक8_t initiator_id;
	uपूर्णांक8_t cdb_len;
	uपूर्णांक8_t target_id;
	__le32 option_flags;
	uपूर्णांक8_t status;
	uपूर्णांक8_t scsi_status;
	uपूर्णांक8_t tag_value;	/* Received queue tag message value */
	uपूर्णांक8_t tag_type;	/* Received queue tag message type */
	uपूर्णांक8_t cdb[26];
	uपूर्णांक8_t sense_data[18];
पूर्ण;

/*
 * ISP queue - Continue Target I/O (CTIO) entry काष्ठाure definition.
 */
काष्ठा ctio_entry अणु
	uपूर्णांक8_t entry_type;	/* Entry type. */
#घोषणा CONTINUE_TGT_IO_TYPE 7	/* CTIO entry */
	uपूर्णांक8_t entry_count;	/* Entry count. */
	uपूर्णांक8_t reserved_1;
	uपूर्णांक8_t entry_status;	/* Entry Status. */
	__le32 reserved_2;
	uपूर्णांक8_t lun;		/* SCSI LUN */
	uपूर्णांक8_t initiator_id;
	uपूर्णांक8_t reserved_3;
	uपूर्णांक8_t target_id;
	__le32 option_flags;
	uपूर्णांक8_t status;
	uपूर्णांक8_t scsi_status;
	uपूर्णांक8_t tag_value;	/* Received queue tag message value */
	uपूर्णांक8_t tag_type;	/* Received queue tag message type */
	__le32 transfer_length;
	__le32 residual;
	__le16 समयout;		/* 0 = 30 seconds, 0xFFFF = disable */
	__le16 dseg_count;	/* Data segment count. */
	__le32 dseg_0_address;	/* Data segment 0 address. */
	__le32 dseg_0_length;	/* Data segment 0 length. */
	__le32 dseg_1_address;	/* Data segment 1 address. */
	__le32 dseg_1_length;	/* Data segment 1 length. */
	__le32 dseg_2_address;	/* Data segment 2 address. */
	__le32 dseg_2_length;	/* Data segment 2 length. */
	__le32 dseg_3_address;	/* Data segment 3 address. */
	__le32 dseg_3_length;	/* Data segment 3 length. */
पूर्ण;

/*
 * ISP queue - CTIO वापसed entry काष्ठाure definition.
 */
काष्ठा ctio_ret_entry अणु
	uपूर्णांक8_t entry_type;	/* Entry type. */
#घोषणा CTIO_RET_TYPE   7	/* CTIO वापस entry */
	uपूर्णांक8_t entry_count;	/* Entry count. */
	uपूर्णांक8_t reserved_1;
	uपूर्णांक8_t entry_status;	/* Entry Status. */
	__le32 reserved_2;
	uपूर्णांक8_t lun;		/* SCSI LUN */
	uपूर्णांक8_t initiator_id;
	uपूर्णांक8_t reserved_3;
	uपूर्णांक8_t target_id;
	__le32 option_flags;
	uपूर्णांक8_t status;
	uपूर्णांक8_t scsi_status;
	uपूर्णांक8_t tag_value;	/* Received queue tag message value */
	uपूर्णांक8_t tag_type;	/* Received queue tag message type */
	__le32 transfer_length;
	__le32 residual;
	__le16 समयout;		/* 0 = 30 seconds, 0xFFFF = disable */
	__le16 dseg_count;	/* Data segment count. */
	__le32 dseg_0_address;	/* Data segment 0 address. */
	__le32 dseg_0_length;	/* Data segment 0 length. */
	__le32 dseg_1_address;	/* Data segment 1 address. */
	__le16 dseg_1_length;	/* Data segment 1 length. */
	uपूर्णांक8_t sense_data[18];
पूर्ण;

/*
 * ISP queue - CTIO A64 entry काष्ठाure definition.
 */
काष्ठा ctio_a64_entry अणु
	uपूर्णांक8_t entry_type;	/* Entry type. */
#घोषणा CTIO_A64_TYPE 0xF	/* CTIO A64 entry */
	uपूर्णांक8_t entry_count;	/* Entry count. */
	uपूर्णांक8_t reserved_1;
	uपूर्णांक8_t entry_status;	/* Entry Status. */
	__le32 reserved_2;
	uपूर्णांक8_t lun;		/* SCSI LUN */
	uपूर्णांक8_t initiator_id;
	uपूर्णांक8_t reserved_3;
	uपूर्णांक8_t target_id;
	__le32 option_flags;
	uपूर्णांक8_t status;
	uपूर्णांक8_t scsi_status;
	uपूर्णांक8_t tag_value;	/* Received queue tag message value */
	uपूर्णांक8_t tag_type;	/* Received queue tag message type */
	__le32 transfer_length;
	__le32 residual;
	__le16 समयout;		/* 0 = 30 seconds, 0xFFFF = disable */
	__le16 dseg_count;	/* Data segment count. */
	__le32 reserved_4[2];
	__le32 dseg_0_address[2];/* Data segment 0 address. */
	__le32 dseg_0_length;	/* Data segment 0 length. */
	__le32 dseg_1_address[2];/* Data segment 1 address. */
	__le32 dseg_1_length;	/* Data segment 1 length. */
पूर्ण;

/*
 * ISP queue - CTIO वापसed entry काष्ठाure definition.
 */
काष्ठा ctio_a64_ret_entry अणु
	uपूर्णांक8_t entry_type;	/* Entry type. */
#घोषणा CTIO_A64_RET_TYPE 0xF	/* CTIO A64 वापसed entry */
	uपूर्णांक8_t entry_count;	/* Entry count. */
	uपूर्णांक8_t reserved_1;
	uपूर्णांक8_t entry_status;	/* Entry Status. */
	__le32 reserved_2;
	uपूर्णांक8_t lun;		/* SCSI LUN */
	uपूर्णांक8_t initiator_id;
	uपूर्णांक8_t reserved_3;
	uपूर्णांक8_t target_id;
	__le32 option_flags;
	uपूर्णांक8_t status;
	uपूर्णांक8_t scsi_status;
	uपूर्णांक8_t tag_value;	/* Received queue tag message value */
	uपूर्णांक8_t tag_type;	/* Received queue tag message type */
	__le32 transfer_length;
	__le32 residual;
	__le16 समयout;		/* 0 = 30 seconds, 0xFFFF = disable */
	__le16 dseg_count;	/* Data segment count. */
	__le16 reserved_4[7];
	uपूर्णांक8_t sense_data[18];
पूर्ण;

/*
 * ISP request and response queue entry sizes
 */
#घोषणा RESPONSE_ENTRY_SIZE	(माप(काष्ठा response))
#घोषणा REQUEST_ENTRY_SIZE	(माप(request_t))

/*
 * ISP status entry - completion status definitions.
 */
#घोषणा CS_COMPLETE         0x0	/* No errors */
#घोषणा CS_INCOMPLETE       0x1	/* Incomplete transfer of cmd. */
#घोषणा CS_DMA              0x2	/* A DMA direction error. */
#घोषणा CS_TRANSPORT        0x3	/* Transport error. */
#घोषणा CS_RESET            0x4	/* SCSI bus reset occurred */
#घोषणा CS_ABORTED          0x5	/* System पातed command. */
#घोषणा CS_TIMEOUT          0x6	/* Timeout error. */
#घोषणा CS_DATA_OVERRUN     0x7	/* Data overrun. */
#घोषणा CS_COMMAND_OVERRUN  0x8	/* Command Overrun. */
#घोषणा CS_STATUS_OVERRUN   0x9	/* Status Overrun. */
#घोषणा CS_BAD_MSG          0xA	/* Bad msg after status phase. */
#घोषणा CS_NO_MSG_OUT       0xB	/* No msg out after selection. */
#घोषणा CS_EXTENDED_ID      0xC	/* Extended ID failed. */
#घोषणा CS_IDE_MSG          0xD	/* Target rejected IDE msg. */
#घोषणा CS_ABORT_MSG        0xE	/* Target rejected पात msg. */
#घोषणा CS_REJECT_MSG       0xF	/* Target rejected reject msg. */
#घोषणा CS_NOP_MSG          0x10	/* Target rejected NOP msg. */
#घोषणा CS_PARITY_MSG       0x11	/* Target rejected parity msg. */
#घोषणा CS_DEV_RESET_MSG    0x12	/* Target rejected dev rst msg. */
#घोषणा CS_ID_MSG           0x13	/* Target rejected ID msg. */
#घोषणा CS_FREE             0x14	/* Unexpected bus मुक्त. */
#घोषणा CS_DATA_UNDERRUN    0x15	/* Data Underrun. */
#घोषणा CS_TRANACTION_1     0x18	/* Transaction error 1 */
#घोषणा CS_TRANACTION_2     0x19	/* Transaction error 2 */
#घोषणा CS_TRANACTION_3     0x1a	/* Transaction error 3 */
#घोषणा CS_INV_ENTRY_TYPE   0x1b	/* Invalid entry type */
#घोषणा CS_DEV_QUEUE_FULL   0x1c	/* Device queue full */
#घोषणा CS_PHASED_SKIPPED   0x1d	/* SCSI phase skipped */
#घोषणा CS_ARS_FAILED       0x1e	/* ARS failed */
#घोषणा CS_LVD_BUS_ERROR    0x21	/* LVD bus error */
#घोषणा CS_BAD_PAYLOAD      0x80	/* Driver defined */
#घोषणा CS_UNKNOWN          0x81	/* Driver defined */
#घोषणा CS_RETRY            0x82	/* Driver defined */

/*
 * ISP target entries - Option flags bit definitions.
 */
#घोषणा OF_ENABLE_TAG       BIT_1	/* Tagged queue action enable */
#घोषणा OF_DATA_IN          BIT_6	/* Data in to initiator */
					/*  (data from target to initiator) */
#घोषणा OF_DATA_OUT         BIT_7	/* Data out from initiator */
					/*  (data from initiator to target) */
#घोषणा OF_NO_DATA          (BIT_7 | BIT_6)
#घोषणा OF_DISC_DISABLED    BIT_15	/* Disconnects disabled */
#घोषणा OF_DISABLE_SDP      BIT_24	/* Disable sending save data ptr */
#घोषणा OF_SEND_RDP         BIT_26	/* Send restore data poपूर्णांकers msg */
#घोषणा OF_FORCE_DISC       BIT_30	/* Disconnects mandatory */
#घोषणा OF_SSTS             BIT_31	/* Send SCSI status */


/*
 * BUS parameters/settings काष्ठाure - UNUSED
 */
काष्ठा bus_param अणु
	uपूर्णांक8_t id;		/* Host adapter SCSI id */
	uपूर्णांक8_t bus_reset_delay;	/* SCSI bus reset delay. */
	uपूर्णांक8_t failed_reset_count;	/* number of समय reset failed */
	uपूर्णांक8_t unused;
	uपूर्णांक16_t device_enables;	/* Device enable bits. */
	uपूर्णांक16_t lun_disables;	/* LUN disable bits. */
	uपूर्णांक16_t qtag_enables;	/* Tag queue enables. */
	uपूर्णांक16_t hiwat;		/* High water mark per device. */
	uपूर्णांक8_t reset_marker:1;
	uपूर्णांक8_t disable_scsi_reset:1;
	uपूर्णांक8_t scsi_bus_dead:1;	/* SCSI Bus is Dead, when 5 back to back resets failed */
पूर्ण;


काष्ठा qla_driver_setup अणु
	uपूर्णांक32_t no_sync:1;
	uपूर्णांक32_t no_wide:1;
	uपूर्णांक32_t no_ppr:1;
	uपूर्णांक32_t no_nvram:1;
	uपूर्णांक16_t sync_mask;
	uपूर्णांक16_t wide_mask;
	uपूर्णांक16_t ppr_mask;
पूर्ण;


/*
 * Linux Host Adapter काष्ठाure
 */
काष्ठा scsi_qla_host अणु
	/* Linux adapter configuration data */
	काष्ठा Scsi_Host *host;	/* poपूर्णांकer to host data */
	काष्ठा scsi_qla_host *next;
	काष्ठा device_reg __iomem *iobase;	/* Base Memory-mapped I/O address */

	अचिन्हित अक्षर __iomem *mmpbase;	/* memory mapped address */
	अचिन्हित दीर्घ host_no;
	काष्ठा pci_dev *pdev;
	uपूर्णांक8_t devnum;
	uपूर्णांक8_t revision;
	uपूर्णांक8_t ports;

	अचिन्हित दीर्घ actthपढ़ोs;
	अचिन्हित दीर्घ isr_count;	/* Interrupt count */
	अचिन्हित दीर्घ spurious_पूर्णांक;

	/* Outstandings ISP commands. */
	काष्ठा srb *outstanding_cmds[MAX_OUTSTANDING_COMMANDS];

	/* BUS configuration data */
	काष्ठा bus_param bus_settings[MAX_BUSES];

	/* Received ISP mailbox data. */
	अस्थिर uपूर्णांक16_t mailbox_out[MAILBOX_REGISTER_COUNT];

	dma_addr_t request_dma;		/* Physical Address */
	request_t *request_ring;	/* Base भव address */
	request_t *request_ring_ptr;	/* Current address. */
	uपूर्णांक16_t req_ring_index;	/* Current index. */
	uपूर्णांक16_t req_q_cnt;		/* Number of available entries. */

	dma_addr_t response_dma;	/* Physical address. */
	काष्ठा response *response_ring;	/* Base भव address */
	काष्ठा response *response_ring_ptr;	/* Current address. */
	uपूर्णांक16_t rsp_ring_index;	/* Current index. */

	काष्ठा list_head करोne_q;	/* Done queue */

	काष्ठा completion *mailbox_रुको;
	काष्ठा समयr_list mailbox_समयr;

	अस्थिर काष्ठा अणु
		uपूर्णांक32_t online:1;			/* 0 */
		uपूर्णांक32_t reset_marker:1;		/* 1 */
		uपूर्णांक32_t disable_host_adapter:1;	/* 2 */
		uपूर्णांक32_t reset_active:1;		/* 3 */
		uपूर्णांक32_t पात_isp_active:1;		/* 4 */
		uपूर्णांक32_t disable_risc_code_load:1;	/* 5 */
	पूर्ण flags;

	काष्ठा nvram nvram;
	पूर्णांक nvram_valid;

	/* Firmware Info */
	अचिन्हित लघु fwstart; /* start address क्रम F/W   */
	अचिन्हित अक्षर fwver1;   /* F/W version first अक्षर  */
	अचिन्हित अक्षर fwver2;   /* F/W version second अक्षर */
	अचिन्हित अक्षर fwver3;   /* F/W version third अक्षर  */
पूर्ण;

#पूर्ण_अगर /* _QLA1280_H */
