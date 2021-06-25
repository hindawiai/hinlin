<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _WD719X_H_
#घोषणा _WD719X_H_

#घोषणा WD719X_SG 255		/* Scatter/gather size */

काष्ठा wd719x_sglist अणु
	__le32 ptr;
	__le32 length;
पूर्ण __packed;

क्रमागत wd719x_card_type अणु
	WD719X_TYPE_UNKNOWN = 0,
	WD719X_TYPE_7193,
	WD719X_TYPE_7197,
	WD719X_TYPE_7296,
पूर्ण;

जोड़ wd719x_regs अणु
	__le32 all;	/* All Status at once */
	काष्ठा अणु
		u8 OPC;		/* Opcode रेजिस्टर */
		u8 SCSI;	/* SCSI Errors */
		u8 SUE;		/* Spider unique Errors */
		u8 INT;		/* Interrupt Status */
	पूर्ण bytes;
पूर्ण;

/* Spider Command Block (SCB) */
काष्ठा wd719x_scb अणु
	__le32 Int_SCB;	/* 00-03 Internal SCB link poपूर्णांकer (must be cleared) */
	u8 SCB_opcode;	/* 04 SCB Command opcode */
	u8 CDB_tag;	/* 05 SCSI Tag byte क्रम CDB queues (0 अगर untagged) */
	u8 lun;		/* 06 SCSI LUN */
	u8 devid;	/* 07 SCSI Device ID */
	u8 CDB[16];	/* 08-23 SCSI CDB (16 bytes as defined by ANSI spec. */
	__le32 data_p;	/* 24-27 Data transfer address (or SG list address) */
	__le32 data_length; /* 28-31 Data transfer Length (or SG list length) */
	__le32 CDB_link;    /* 32-35 SCSI CDB Link Ptr */
	__le32 sense_buf;   /* 36-39 Auto request sense buffer address */
	u8 sense_buf_length;/* 40 Auto request sense transfer length */
	u8 reserved;	/* 41 reserved */
	u8 SCB_options;	/* 42 SCB-options */
	u8 SCB_tag_msg;	/* 43 Tagged messages options */
	/* Not filled in by host */
	__le32 req_ptr;	/* 44-47 Ptr to Host Request वापसed on पूर्णांकerrupt */
	u8 host_opcode;	/* 48 Host Command Opcode (same as AMR_00) */
	u8 scsi_stat;	/* 49 SCSI Status वापसed */
	u8 ret_error;	/* 50 SPIDER Unique Error Code वापसed (SUE) */
	u8 पूर्णांक_stat;	/* 51 Message u8 / Interrupt Status byte वापसed */
	__le32 transferred; /* 52-55 Bytes Transferred */
	u8 last_trans[3];  /* 56-58 Bytes Transferred in last session */
	u8 length;	/* 59 SCSI Messages Length (1-8) */
	u8 sync_offset;	/* 60 Synchronous offset */
	u8 sync_rate;	/* 61 Synchronous rate */
	u8 flags[2];	/* 62-63 SCB specअगरic flags (local to each thपढ़ो) */
	/* everything below is क्रम driver use (not used by card) */
	dma_addr_t phys;	/* bus address of the SCB */
	काष्ठा scsi_cmnd *cmd;	/* a copy of the poपूर्णांकer we were passed */
	काष्ठा list_head list;
	काष्ठा wd719x_sglist sg_list[WD719X_SG] __aligned(8); /* SG list */
पूर्ण __packed;

काष्ठा wd719x अणु
	काष्ठा Scsi_Host *sh;	/* poपूर्णांकer to host काष्ठाure */
	काष्ठा pci_dev *pdev;
	व्योम __iomem *base;
	क्रमागत wd719x_card_type type; /* type of card */
	व्योम *fw_virt;		/* firmware buffer CPU address */
	dma_addr_t fw_phys;	/* firmware buffer bus address */
	माप_प्रकार fw_size;		/* firmware buffer size */
	काष्ठा wd719x_host_param *params; /* host parameters (EEPROM) */
	dma_addr_t params_phys; /* host parameters bus address */
	व्योम *hash_virt;	/* hash table CPU address */
	dma_addr_t hash_phys;	/* hash table bus address */
	काष्ठा list_head active_scbs;
पूर्ण;

/* समयout delays in microsecs */
#घोषणा WD719X_WAIT_FOR_CMD_READY	500
#घोषणा WD719X_WAIT_FOR_RISC		2000
#घोषणा WD719X_WAIT_FOR_SCSI_RESET	3000000

/* All commands except 0x00 generate an पूर्णांकerrupt */
#घोषणा WD719X_CMD_READY	0x00 /* Command रेजिस्टर पढ़ोy (or noop) */
#घोषणा WD719X_CMD_INIT_RISC	0x01 /* Initialize RISC */
/* 0x02 is reserved */
#घोषणा WD719X_CMD_BUSRESET	0x03 /* Assert SCSI bus reset */
#घोषणा WD719X_CMD_READ_FIRMVER	0x04 /* Read the Firmware Revision */
#घोषणा WD719X_CMD_ECHO_BYTES	0x05 /* Echo command bytes (DW) */
/* 0x06 is reserved */
/* 0x07 is reserved */
#घोषणा WD719X_CMD_GET_PARAM	0x08 /* Get programmable parameters */
#घोषणा WD719X_CMD_SET_PARAM	0x09 /* Set programmable parameters */
#घोषणा WD719X_CMD_SLEEP	0x0a /* Put SPIDER to sleep */
#घोषणा WD719X_CMD_READ_INIT	0x0b /* Read initialization parameters */
#घोषणा WD719X_CMD_RESTORE_INIT	0x0c /* Restore initialization parameters */
/* 0x0d is reserved */
/* 0x0e is reserved */
/* 0x0f is reserved */
#घोषणा WD719X_CMD_ABORT_TAG	0x10 /* Send Abort tag message to target */
#घोषणा WD719X_CMD_ABORT	0x11 /* Send Abort message to target */
#घोषणा WD719X_CMD_RESET	0x12 /* Send Reset message to target */
#घोषणा WD719X_CMD_INIT_SCAM	0x13 /* Initiate SCAM */
#घोषणा WD719X_CMD_GET_SYNC	0x14 /* Get synchronous rates */
#घोषणा WD719X_CMD_SET_SYNC	0x15 /* Set synchronous rates */
#घोषणा WD719X_CMD_GET_WIDTH	0x16 /* Get SCSI bus width */
#घोषणा WD719X_CMD_SET_WIDTH	0x17 /* Set SCSI bus width */
#घोषणा WD719X_CMD_GET_TAGS	0x18 /* Get tag flags */
#घोषणा WD719X_CMD_SET_TAGS	0x19 /* Set tag flags */
#घोषणा WD719X_CMD_GET_PARAM2	0x1a /* Get programmable params (क्रमmat 2) */
#घोषणा WD719X_CMD_SET_PARAM2	0x1b /* Set programmable params (क्रमmat 2) */
/* Commands with request poपूर्णांकers (mailbox) */
#घोषणा WD719X_CMD_PROCESS_SCB	0x80 /* Process SCSI Control Block (SCB) */
/* No पूर्णांकerrupt generated on acceptance of SCB poपूर्णांकer */

/* पूर्णांकerrupt status defines */
#घोषणा WD719X_INT_NONE		0x00 /* No पूर्णांकerrupt pending */
#घोषणा WD719X_INT_NOERRORS	0x01 /* Command completed with no errors */
#घोषणा WD719X_INT_LINKNOERRORS	0x02 /* link cmd completed with no errors */
#घोषणा WD719X_INT_LINKNOSTATUS	0x03 /* link cmd completed with no flag set */
#घोषणा WD719X_INT_ERRORSLOGGED	0x04 /* cmd completed with errors logged */
#घोषणा WD719X_INT_SPIDERFAILED	0x05 /* cmd failed without valid SCSI status */
#घोषणा WD719X_INT_BADINT	0x80 /* unsolicited पूर्णांकerrupt */
#घोषणा WD719X_INT_PIOREADY	0xf0 /* data पढ़ोy क्रम PIO output */

/* Spider Unique Error Codes (SUE) */
#घोषणा WD719X_SUE_NOERRORS	0x00 /* No errors detected by SPIDER */
#घोषणा WD719X_SUE_REJECTED	0x01 /* Command Rejected (bad opcode/param) */
#घोषणा WD719X_SUE_SCBQFULL	0x02 /* SCB queue full */
/* 0x03 is reserved */
#घोषणा WD719X_SUE_TERM		0x04 /* Host terminated SCB via primative cmd */
#घोषणा WD719X_SUE_CHAN1PAR	0x05 /* PCI Channel 1 parity error occurred */
#घोषणा WD719X_SUE_CHAN1ABORT	0x06 /* PCI Channel 1 प्रणाली पात occurred */
#घोषणा WD719X_SUE_CHAN23PAR	0x07 /* PCI Channel 2/3 parity error occurred */
#घोषणा WD719X_SUE_CHAN23ABORT	0x08 /* PCI Channel 2/3 प्रणाली पात occurred */
#घोषणा WD719X_SUE_TIMEOUT	0x10 /* Selection/reselection समयout */
#घोषणा WD719X_SUE_RESET	0x11 /* SCSI bus reset occurred */
#घोषणा WD719X_SUE_BUSERROR	0x12 /* SCSI bus error */
#घोषणा WD719X_SUE_WRONGWAY	0x13 /* Wrong data transfer dir set by target */
#घोषणा WD719X_SUE_BADPHASE	0x14 /* SCSI phase illegal or unexpected */
#घोषणा WD719X_SUE_TOOLONG	0x15 /* target requested too much data */
#घोषणा WD719X_SUE_BUSFREE	0x16 /* Unexpected SCSI bus मुक्त */
#घोषणा WD719X_SUE_ARSDONE	0x17 /* Auto request sense executed */
#घोषणा WD719X_SUE_IGNORED	0x18 /* SCSI message was ignored by target */
#घोषणा WD719X_SUE_WRONGTAGS	0x19 /* Tagged SCB & tags off (or vice versa) */
#घोषणा WD719X_SUE_BADTAGS	0x1a /* Wrong tag message type क्रम target */
#घोषणा WD719X_SUE_NOSCAMID	0x1b /* No SCAM soft ID available */

/* code sizes */
#घोषणा	WD719X_HASH_TABLE_SIZE	4096

/* Advanced Mode Registers */
/* Regs 0x00..0x1f are क्रम Advanced Mode of the card (RISC is running). */
#घोषणा WD719X_AMR_COMMAND		0x00
#घोषणा WD719X_AMR_CMD_PARAM		0x01
#घोषणा WD719X_AMR_CMD_PARAM_2		0x02
#घोषणा WD719X_AMR_CMD_PARAM_3		0x03
#घोषणा WD719X_AMR_SCB_IN		0x04

#घोषणा WD719X_AMR_BIOS_SHARE_INT	0x0f

#घोषणा WD719X_AMR_SCB_OUT		0x18
#घोषणा WD719X_AMR_OP_CODE		0x1c
#घोषणा WD719X_AMR_SCSI_STATUS		0x1d
#घोषणा WD719X_AMR_SCB_ERROR		0x1e
#घोषणा WD719X_AMR_INT_STATUS		0x1f

#घोषणा WD719X_DISABLE_INT	0x80

/* SCB flags */
#घोषणा WD719X_SCB_FLAGS_CHECK_सूचीECTION	0x01
#घोषणा WD719X_SCB_FLAGS_PCI_TO_SCSI		0x02
#घोषणा WD719X_SCB_FLAGS_AUTO_REQUEST_SENSE	0x10
#घोषणा WD719X_SCB_FLAGS_DO_SCATTER_GATHER	0x20
#घोषणा WD719X_SCB_FLAGS_NO_DISCONNECT		0x40

/* PCI Registers used क्रम reset, initial code करोwnload */
/* Regs 0x20..0x3f are क्रम Normal (DOS) mode (RISC is asleep). */
#घोषणा WD719X_PCI_GPIO_CONTROL		0x3C
#घोषणा WD719X_PCI_GPIO_DATA		0x3D
#घोषणा WD719X_PCI_PORT_RESET		0x3E
#घोषणा WD719X_PCI_MODE_SELECT		0x3F

#घोषणा WD719X_PCI_EXTERNAL_ADDR	0x60
#घोषणा WD719X_PCI_INTERNAL_ADDR	0x64
#घोषणा WD719X_PCI_DMA_TRANSFER_SIZE	0x66
#घोषणा WD719X_PCI_CHANNEL2_3CMD	0x68
#घोषणा WD719X_PCI_CHANNEL2_3STATUS	0x69

#घोषणा WD719X_GPIO_ID_BITS		0x0a
#घोषणा WD719X_PRAM_BASE_ADDR		0x00

/* codes written to or पढ़ो from the card */
#घोषणा WD719X_PCI_RESET		 0x01
#घोषणा WD719X_ENABLE_ADVANCE_MODE	 0x01

#घोषणा WD719X_START_CHANNEL2_3DMA	 0x17
#घोषणा WD719X_START_CHANNEL2_3DONE	 0x01
#घोषणा WD719X_START_CHANNEL2_3ABORT	 0x20

/* 33C296 GPIO bits क्रम EEPROM pins */
#घोषणा WD719X_EE_DI	(1 << 1)
#घोषणा WD719X_EE_CS	(1 << 2)
#घोषणा WD719X_EE_CLK	(1 << 3)
#घोषणा WD719X_EE_DO	(1 << 4)

/* EEPROM contents */
काष्ठा wd719x_eeprom_header अणु
	u8 sig1;
	u8 sig2;
	u8 version;
	u8 checksum;
	u8 cfg_offset;
	u8 cfg_size;
	u8 setup_offset;
	u8 setup_size;
पूर्ण __packed;

#घोषणा WD719X_EE_SIG1		0
#घोषणा WD719X_EE_SIG2		1
#घोषणा WD719X_EE_VERSION	2
#घोषणा WD719X_EE_CHECKSUM	3
#घोषणा WD719X_EE_CFG_OFFSET	4
#घोषणा WD719X_EE_CFG_SIZE	5
#घोषणा WD719X_EE_SETUP_OFFSET	6
#घोषणा WD719X_EE_SETUP_SIZE	7

#घोषणा WD719X_EE_SCSI_ID_MASK	0xf

/* SPIDER Host Parameters Block (=EEPROM configuration block) */
काष्ठा wd719x_host_param अणु
	u8 ch_1_th;	/* FIFO threshold */
	u8 scsi_conf;	/* SCSI configuration */
	u8 own_scsi_id;	/* controller SCSI ID */
	u8 sel_समयout;	/* selection समयout*/
	u8 sleep_समयr;	/* seep समयr */
	__le16 cdb_size;/* CDB size groups */
	__le16 tag_en;	/* Tag msg enables (ID 0-15) */
	u8 scsi_pad;	/* SCSI pad control */
	__le32 wide;	/* WIDE msg options (ID 0-15) */
	__le32 sync;	/* SYNC msg options (ID 0-15) */
	u8 soft_mask;	/* soft error mask */
	u8 unsol_mask;	/* unsolicited error mask */
पूर्ण __packed;

#पूर्ण_अगर /* _WD719X_H_ */
