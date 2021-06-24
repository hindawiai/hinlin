<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sata_sil24.c - Driver क्रम Silicon Image 3124/3132 SATA-2 controllers
 *
 * Copyright 2005  Tejun Heo
 *
 * Based on preview driver from Silicon Image.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME	"sata_sil24"
#घोषणा DRV_VERSION	"1.1"

/*
 * Port request block (PRB) 32 bytes
 */
काष्ठा sil24_prb अणु
	__le16	ctrl;
	__le16	prot;
	__le32	rx_cnt;
	u8	fis[6 * 4];
पूर्ण;

/*
 * Scatter gather entry (SGE) 16 bytes
 */
काष्ठा sil24_sge अणु
	__le64	addr;
	__le32	cnt;
	__le32	flags;
पूर्ण;


क्रमागत अणु
	SIL24_HOST_BAR		= 0,
	SIL24_PORT_BAR		= 2,

	/* sil24 fetches in chunks of 64bytes.  The first block
	 * contains the PRB and two SGEs.  From the second block, it's
	 * consisted of four SGEs and called SGT.  Calculate the
	 * number of SGTs that fit पूर्णांकo one page.
	 */
	SIL24_PRB_SZ		= माप(काष्ठा sil24_prb)
				  + 2 * माप(काष्ठा sil24_sge),
	SIL24_MAX_SGT		= (PAGE_SIZE - SIL24_PRB_SZ)
				  / (4 * माप(काष्ठा sil24_sge)),

	/* This will give us one unused SGEs क्रम ATA.  This extra SGE
	 * will be used to store CDB क्रम ATAPI devices.
	 */
	SIL24_MAX_SGE		= 4 * SIL24_MAX_SGT + 1,

	/*
	 * Global controller रेजिस्टरs (128 bytes @ BAR0)
	 */
		/* 32 bit regs */
	HOST_SLOT_STAT		= 0x00, /* 32 bit slot stat * 4 */
	HOST_CTRL		= 0x40,
	HOST_IRQ_STAT		= 0x44,
	HOST_PHY_CFG		= 0x48,
	HOST_BIST_CTRL		= 0x50,
	HOST_BIST_PTRN		= 0x54,
	HOST_BIST_STAT		= 0x58,
	HOST_MEM_BIST_STAT	= 0x5c,
	HOST_FLASH_CMD		= 0x70,
		/* 8 bit regs */
	HOST_FLASH_DATA		= 0x74,
	HOST_TRANSITION_DETECT	= 0x75,
	HOST_GPIO_CTRL		= 0x76,
	HOST_I2C_ADDR		= 0x78, /* 32 bit */
	HOST_I2C_DATA		= 0x7c,
	HOST_I2C_XFER_CNT	= 0x7e,
	HOST_I2C_CTRL		= 0x7f,

	/* HOST_SLOT_STAT bits */
	HOST_SSTAT_ATTN		= (1 << 31),

	/* HOST_CTRL bits */
	HOST_CTRL_M66EN		= (1 << 16), /* M66EN PCI bus संकेत */
	HOST_CTRL_TRDY		= (1 << 17), /* latched PCI TRDY */
	HOST_CTRL_STOP		= (1 << 18), /* latched PCI STOP */
	HOST_CTRL_DEVSEL	= (1 << 19), /* latched PCI DEVSEL */
	HOST_CTRL_REQ64		= (1 << 20), /* latched PCI REQ64 */
	HOST_CTRL_GLOBAL_RST	= (1 << 31), /* global reset */

	/*
	 * Port रेजिस्टरs
	 * (8192 bytes @ +0x0000, +0x2000, +0x4000 and +0x6000 @ BAR2)
	 */
	PORT_REGS_SIZE		= 0x2000,

	PORT_LRAM		= 0x0000, /* 31 LRAM slots and PMP regs */
	PORT_LRAM_SLOT_SZ	= 0x0080, /* 32 bytes PRB + 2 SGE, ACT... */

	PORT_PMP		= 0x0f80, /* 8 bytes PMP * 16 (128 bytes) */
	PORT_PMP_STATUS		= 0x0000, /* port device status offset */
	PORT_PMP_QACTIVE	= 0x0004, /* port device QActive offset */
	PORT_PMP_SIZE		= 0x0008, /* 8 bytes per PMP */

		/* 32 bit regs */
	PORT_CTRL_STAT		= 0x1000, /* ग_लिखो: ctrl-set, पढ़ो: stat */
	PORT_CTRL_CLR		= 0x1004, /* ग_लिखो: ctrl-clear */
	PORT_IRQ_STAT		= 0x1008, /* high: status, low: पूर्णांकerrupt */
	PORT_IRQ_ENABLE_SET	= 0x1010, /* ग_लिखो: enable-set */
	PORT_IRQ_ENABLE_CLR	= 0x1014, /* ग_लिखो: enable-clear */
	PORT_ACTIVATE_UPPER_ADDR= 0x101c,
	PORT_EXEC_FIFO		= 0x1020, /* command execution fअगरo */
	PORT_CMD_ERR		= 0x1024, /* command error number */
	PORT_FIS_CFG		= 0x1028,
	PORT_FIFO_THRES		= 0x102c,
		/* 16 bit regs */
	PORT_DECODE_ERR_CNT	= 0x1040,
	PORT_DECODE_ERR_THRESH	= 0x1042,
	PORT_CRC_ERR_CNT	= 0x1044,
	PORT_CRC_ERR_THRESH	= 0x1046,
	PORT_HSHK_ERR_CNT	= 0x1048,
	PORT_HSHK_ERR_THRESH	= 0x104a,
		/* 32 bit regs */
	PORT_PHY_CFG		= 0x1050,
	PORT_SLOT_STAT		= 0x1800,
	PORT_CMD_ACTIVATE	= 0x1c00, /* 64 bit cmd activate * 31 (248 bytes) */
	PORT_CONTEXT		= 0x1e04,
	PORT_EXEC_DIAG		= 0x1e00, /* 32bit exec diag * 16 (64 bytes, 0-10 used on 3124) */
	PORT_PSD_DIAG		= 0x1e40, /* 32bit psd diag * 16 (64 bytes, 0-8 used on 3124) */
	PORT_SCONTROL		= 0x1f00,
	PORT_SSTATUS		= 0x1f04,
	PORT_SERROR		= 0x1f08,
	PORT_SACTIVE		= 0x1f0c,

	/* PORT_CTRL_STAT bits */
	PORT_CS_PORT_RST	= (1 << 0), /* port reset */
	PORT_CS_DEV_RST		= (1 << 1), /* device reset */
	PORT_CS_INIT		= (1 << 2), /* port initialize */
	PORT_CS_IRQ_WOC		= (1 << 3), /* पूर्णांकerrupt ग_लिखो one to clear */
	PORT_CS_CDB16		= (1 << 5), /* 0=12b cdb, 1=16b cdb */
	PORT_CS_PMP_RESUME	= (1 << 6), /* PMP resume */
	PORT_CS_32BIT_ACTV	= (1 << 10), /* 32-bit activation */
	PORT_CS_PMP_EN		= (1 << 13), /* port multiplier enable */
	PORT_CS_RDY		= (1 << 31), /* port पढ़ोy to accept commands */

	/* PORT_IRQ_STAT/ENABLE_SET/CLR */
	/* bits[11:0] are masked */
	PORT_IRQ_COMPLETE	= (1 << 0), /* command(s) completed */
	PORT_IRQ_ERROR		= (1 << 1), /* command execution error */
	PORT_IRQ_PORTRDY_CHG	= (1 << 2), /* port पढ़ोy change */
	PORT_IRQ_PWR_CHG	= (1 << 3), /* घातer management change */
	PORT_IRQ_PHYRDY_CHG	= (1 << 4), /* PHY पढ़ोy change */
	PORT_IRQ_COMWAKE	= (1 << 5), /* COMWAKE received */
	PORT_IRQ_UNK_FIS	= (1 << 6), /* unknown FIS received */
	PORT_IRQ_DEV_XCHG	= (1 << 7), /* device exchanged */
	PORT_IRQ_8B10B		= (1 << 8), /* 8b/10b decode error threshold */
	PORT_IRQ_CRC		= (1 << 9), /* CRC error threshold */
	PORT_IRQ_HANDSHAKE	= (1 << 10), /* handshake error threshold */
	PORT_IRQ_SDB_NOTIFY	= (1 << 11), /* SDB notअगरy received */

	DEF_PORT_IRQ		= PORT_IRQ_COMPLETE | PORT_IRQ_ERROR |
				  PORT_IRQ_PHYRDY_CHG | PORT_IRQ_DEV_XCHG |
				  PORT_IRQ_UNK_FIS | PORT_IRQ_SDB_NOTIFY,

	/* bits[27:16] are unmasked (raw) */
	PORT_IRQ_RAW_SHIFT	= 16,
	PORT_IRQ_MASKED_MASK	= 0x7ff,
	PORT_IRQ_RAW_MASK	= (0x7ff << PORT_IRQ_RAW_SHIFT),

	/* ENABLE_SET/CLR specअगरic, पूर्णांकr steering - 2 bit field */
	PORT_IRQ_STEER_SHIFT	= 30,
	PORT_IRQ_STEER_MASK	= (3 << PORT_IRQ_STEER_SHIFT),

	/* PORT_CMD_ERR स्थिरants */
	PORT_CERR_DEV		= 1, /* Error bit in D2H Register FIS */
	PORT_CERR_SDB		= 2, /* Error bit in SDB FIS */
	PORT_CERR_DATA		= 3, /* Error in data FIS not detected by dev */
	PORT_CERR_SEND		= 4, /* Initial cmd FIS transmission failure */
	PORT_CERR_INCONSISTENT	= 5, /* Protocol mismatch */
	PORT_CERR_सूचीECTION	= 6, /* Data direction mismatch */
	PORT_CERR_UNDERRUN	= 7, /* Ran out of SGEs जबतक writing */
	PORT_CERR_OVERRUN	= 8, /* Ran out of SGEs जबतक पढ़ोing */
	PORT_CERR_PKT_PROT	= 11, /* सूची invalid in 1st PIO setup of ATAPI */
	PORT_CERR_SGT_BOUNDARY	= 16, /* PLD ecode 00 - SGT not on qword boundary */
	PORT_CERR_SGT_TGTABRT	= 17, /* PLD ecode 01 - target पात */
	PORT_CERR_SGT_MSTABRT	= 18, /* PLD ecode 10 - master पात */
	PORT_CERR_SGT_PCIPERR	= 19, /* PLD ecode 11 - PCI parity err जबतक fetching SGT */
	PORT_CERR_CMD_BOUNDARY	= 24, /* ctrl[15:13] 001 - PRB not on qword boundary */
	PORT_CERR_CMD_TGTABRT	= 25, /* ctrl[15:13] 010 - target पात */
	PORT_CERR_CMD_MSTABRT	= 26, /* ctrl[15:13] 100 - master पात */
	PORT_CERR_CMD_PCIPERR	= 27, /* ctrl[15:13] 110 - PCI parity err जबतक fetching PRB */
	PORT_CERR_XFR_UNDEF	= 32, /* PSD ecode 00 - undefined */
	PORT_CERR_XFR_TGTABRT	= 33, /* PSD ecode 01 - target पात */
	PORT_CERR_XFR_MSTABRT	= 34, /* PSD ecode 10 - master पात */
	PORT_CERR_XFR_PCIPERR	= 35, /* PSD ecode 11 - PCI prity err during transfer */
	PORT_CERR_SENDSERVICE	= 36, /* FIS received जबतक sending service */

	/* bits of PRB control field */
	PRB_CTRL_PROTOCOL	= (1 << 0), /* override def. ATA protocol */
	PRB_CTRL_PACKET_READ	= (1 << 4), /* PACKET cmd पढ़ो */
	PRB_CTRL_PACKET_WRITE	= (1 << 5), /* PACKET cmd ग_लिखो */
	PRB_CTRL_NIEN		= (1 << 6), /* Mask completion irq */
	PRB_CTRL_SRST		= (1 << 7), /* Soft reset request (ign BSY?) */

	/* PRB protocol field */
	PRB_PROT_PACKET		= (1 << 0),
	PRB_PROT_TCQ		= (1 << 1),
	PRB_PROT_NCQ		= (1 << 2),
	PRB_PROT_READ		= (1 << 3),
	PRB_PROT_WRITE		= (1 << 4),
	PRB_PROT_TRANSPARENT	= (1 << 5),

	/*
	 * Other स्थिरants
	 */
	SGE_TRM			= (1 << 31), /* Last SGE in chain */
	SGE_LNK			= (1 << 30), /* linked list
						Poपूर्णांकs to SGT, not SGE */
	SGE_DRD			= (1 << 29), /* discard data पढ़ो (/dev/null)
						data address ignored */

	SIL24_MAX_CMDS		= 31,

	/* board id */
	BID_SIL3124		= 0,
	BID_SIL3132		= 1,
	BID_SIL3131		= 2,

	/* host flags */
	SIL24_COMMON_FLAGS	= ATA_FLAG_SATA | ATA_FLAG_PIO_DMA |
				  ATA_FLAG_NCQ | ATA_FLAG_ACPI_SATA |
				  ATA_FLAG_AN | ATA_FLAG_PMP,
	SIL24_FLAG_PCIX_IRQ_WOC	= (1 << 24), /* IRQ loss errata on PCI-X */

	IRQ_STAT_4PORTS		= 0xf,
पूर्ण;

काष्ठा sil24_ata_block अणु
	काष्ठा sil24_prb prb;
	काष्ठा sil24_sge sge[SIL24_MAX_SGE];
पूर्ण;

काष्ठा sil24_atapi_block अणु
	काष्ठा sil24_prb prb;
	u8 cdb[16];
	काष्ठा sil24_sge sge[SIL24_MAX_SGE];
पूर्ण;

जोड़ sil24_cmd_block अणु
	काष्ठा sil24_ata_block ata;
	काष्ठा sil24_atapi_block atapi;
पूर्ण;

अटल स्थिर काष्ठा sil24_cerr_info अणु
	अचिन्हित पूर्णांक err_mask, action;
	स्थिर अक्षर *desc;
पूर्ण sil24_cerr_db[] = अणु
	[0]			= अणु AC_ERR_DEV, 0,
				    "device error" पूर्ण,
	[PORT_CERR_DEV]		= अणु AC_ERR_DEV, 0,
				    "device error via D2H FIS" पूर्ण,
	[PORT_CERR_SDB]		= अणु AC_ERR_DEV, 0,
				    "device error via SDB FIS" पूर्ण,
	[PORT_CERR_DATA]	= अणु AC_ERR_ATA_BUS, ATA_EH_RESET,
				    "error in data FIS" पूर्ण,
	[PORT_CERR_SEND]	= अणु AC_ERR_ATA_BUS, ATA_EH_RESET,
				    "failed to transmit command FIS" पूर्ण,
	[PORT_CERR_INCONSISTENT] = अणु AC_ERR_HSM, ATA_EH_RESET,
				     "protocol mismatch" पूर्ण,
	[PORT_CERR_सूचीECTION]	= अणु AC_ERR_HSM, ATA_EH_RESET,
				    "data direction mismatch" पूर्ण,
	[PORT_CERR_UNDERRUN]	= अणु AC_ERR_HSM, ATA_EH_RESET,
				    "ran out of SGEs while writing" पूर्ण,
	[PORT_CERR_OVERRUN]	= अणु AC_ERR_HSM, ATA_EH_RESET,
				    "ran out of SGEs while reading" पूर्ण,
	[PORT_CERR_PKT_PROT]	= अणु AC_ERR_HSM, ATA_EH_RESET,
				    "invalid data direction for ATAPI CDB" पूर्ण,
	[PORT_CERR_SGT_BOUNDARY] = अणु AC_ERR_SYSTEM, ATA_EH_RESET,
				     "SGT not on qword boundary" पूर्ण,
	[PORT_CERR_SGT_TGTABRT]	= अणु AC_ERR_HOST_BUS, ATA_EH_RESET,
				    "PCI target abort while fetching SGT" पूर्ण,
	[PORT_CERR_SGT_MSTABRT]	= अणु AC_ERR_HOST_BUS, ATA_EH_RESET,
				    "PCI master abort while fetching SGT" पूर्ण,
	[PORT_CERR_SGT_PCIPERR]	= अणु AC_ERR_HOST_BUS, ATA_EH_RESET,
				    "PCI parity error while fetching SGT" पूर्ण,
	[PORT_CERR_CMD_BOUNDARY] = अणु AC_ERR_SYSTEM, ATA_EH_RESET,
				     "PRB not on qword boundary" पूर्ण,
	[PORT_CERR_CMD_TGTABRT]	= अणु AC_ERR_HOST_BUS, ATA_EH_RESET,
				    "PCI target abort while fetching PRB" पूर्ण,
	[PORT_CERR_CMD_MSTABRT]	= अणु AC_ERR_HOST_BUS, ATA_EH_RESET,
				    "PCI master abort while fetching PRB" पूर्ण,
	[PORT_CERR_CMD_PCIPERR]	= अणु AC_ERR_HOST_BUS, ATA_EH_RESET,
				    "PCI parity error while fetching PRB" पूर्ण,
	[PORT_CERR_XFR_UNDEF]	= अणु AC_ERR_HOST_BUS, ATA_EH_RESET,
				    "undefined error while transferring data" पूर्ण,
	[PORT_CERR_XFR_TGTABRT]	= अणु AC_ERR_HOST_BUS, ATA_EH_RESET,
				    "PCI target abort while transferring data" पूर्ण,
	[PORT_CERR_XFR_MSTABRT]	= अणु AC_ERR_HOST_BUS, ATA_EH_RESET,
				    "PCI master abort while transferring data" पूर्ण,
	[PORT_CERR_XFR_PCIPERR]	= अणु AC_ERR_HOST_BUS, ATA_EH_RESET,
				    "PCI parity error while transferring data" पूर्ण,
	[PORT_CERR_SENDSERVICE]	= अणु AC_ERR_HSM, ATA_EH_RESET,
				    "FIS received while sending service FIS" पूर्ण,
पूर्ण;

/*
 * ap->निजी_data
 *
 * The preview driver always वापसed 0 क्रम status.  We emulate it
 * here from the previous पूर्णांकerrupt.
 */
काष्ठा sil24_port_priv अणु
	जोड़ sil24_cmd_block *cmd_block;	/* 32 cmd blocks */
	dma_addr_t cmd_block_dma;		/* DMA base addr क्रम them */
	पूर्णांक करो_port_rst;
पूर्ण;

अटल व्योम sil24_dev_config(काष्ठा ata_device *dev);
अटल पूर्णांक sil24_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित sc_reg, u32 *val);
अटल पूर्णांक sil24_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित sc_reg, u32 val);
अटल पूर्णांक sil24_qc_defer(काष्ठा ata_queued_cmd *qc);
अटल क्रमागत ata_completion_errors sil24_qc_prep(काष्ठा ata_queued_cmd *qc);
अटल अचिन्हित पूर्णांक sil24_qc_issue(काष्ठा ata_queued_cmd *qc);
अटल bool sil24_qc_fill_rtf(काष्ठा ata_queued_cmd *qc);
अटल व्योम sil24_pmp_attach(काष्ठा ata_port *ap);
अटल व्योम sil24_pmp_detach(काष्ठा ata_port *ap);
अटल व्योम sil24_मुक्तze(काष्ठा ata_port *ap);
अटल व्योम sil24_thaw(काष्ठा ata_port *ap);
अटल पूर्णांक sil24_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			   अचिन्हित दीर्घ deadline);
अटल पूर्णांक sil24_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			   अचिन्हित दीर्घ deadline);
अटल पूर्णांक sil24_pmp_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			       अचिन्हित दीर्घ deadline);
अटल व्योम sil24_error_handler(काष्ठा ata_port *ap);
अटल व्योम sil24_post_पूर्णांकernal_cmd(काष्ठा ata_queued_cmd *qc);
अटल पूर्णांक sil24_port_start(काष्ठा ata_port *ap);
अटल पूर्णांक sil24_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sil24_pci_device_resume(काष्ठा pci_dev *pdev);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PM
अटल पूर्णांक sil24_port_resume(काष्ठा ata_port *ap);
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id sil24_pci_tbl[] = अणु
	अणु PCI_VDEVICE(CMD, 0x3124), BID_SIL3124 पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x3124), BID_SIL3124 पूर्ण,
	अणु PCI_VDEVICE(CMD, 0x3132), BID_SIL3132 पूर्ण,
	अणु PCI_VDEVICE(CMD, 0x0242), BID_SIL3132 पूर्ण,
	अणु PCI_VDEVICE(CMD, 0x0244), BID_SIL3132 पूर्ण,
	अणु PCI_VDEVICE(CMD, 0x3131), BID_SIL3131 पूर्ण,
	अणु PCI_VDEVICE(CMD, 0x3531), BID_SIL3131 पूर्ण,

	अणु पूर्ण /* terminate list */
पूर्ण;

अटल काष्ठा pci_driver sil24_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= sil24_pci_tbl,
	.probe			= sil24_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= sil24_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा sil24_sht = अणु
	ATA_NCQ_SHT(DRV_NAME),
	.can_queue		= SIL24_MAX_CMDS,
	.sg_tablesize		= SIL24_MAX_SGE,
	.dma_boundary		= ATA_DMA_BOUNDARY,
	.tag_alloc_policy	= BLK_TAG_ALLOC_FIFO,
पूर्ण;

अटल काष्ठा ata_port_operations sil24_ops = अणु
	.inherits		= &sata_pmp_port_ops,

	.qc_defer		= sil24_qc_defer,
	.qc_prep		= sil24_qc_prep,
	.qc_issue		= sil24_qc_issue,
	.qc_fill_rtf		= sil24_qc_fill_rtf,

	.मुक्तze			= sil24_मुक्तze,
	.thaw			= sil24_thaw,
	.softreset		= sil24_softreset,
	.hardreset		= sil24_hardreset,
	.pmp_softreset		= sil24_softreset,
	.pmp_hardreset		= sil24_pmp_hardreset,
	.error_handler		= sil24_error_handler,
	.post_पूर्णांकernal_cmd	= sil24_post_पूर्णांकernal_cmd,
	.dev_config		= sil24_dev_config,

	.scr_पढ़ो		= sil24_scr_पढ़ो,
	.scr_ग_लिखो		= sil24_scr_ग_लिखो,
	.pmp_attach		= sil24_pmp_attach,
	.pmp_detach		= sil24_pmp_detach,

	.port_start		= sil24_port_start,
#अगर_घोषित CONFIG_PM
	.port_resume		= sil24_port_resume,
#पूर्ण_अगर
पूर्ण;

अटल bool sata_sil24_msi;    /* Disable MSI */
module_param_named(msi, sata_sil24_msi, bool, S_IRUGO);
MODULE_PARM_DESC(msi, "Enable MSI (Default: false)");

/*
 * Use bits 30-31 of port_flags to encode available port numbers.
 * Current maxium is 4.
 */
#घोषणा SIL24_NPORTS2FLAG(nports)	((((अचिन्हित)(nports) - 1) & 0x3) << 30)
#घोषणा SIL24_FLAG2NPORTS(flag)		((((flag) >> 30) & 0x3) + 1)

अटल स्थिर काष्ठा ata_port_info sil24_port_info[] = अणु
	/* sil_3124 */
	अणु
		.flags		= SIL24_COMMON_FLAGS | SIL24_NPORTS2FLAG(4) |
				  SIL24_FLAG_PCIX_IRQ_WOC,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
		.port_ops	= &sil24_ops,
	पूर्ण,
	/* sil_3132 */
	अणु
		.flags		= SIL24_COMMON_FLAGS | SIL24_NPORTS2FLAG(2),
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
		.port_ops	= &sil24_ops,
	पूर्ण,
	/* sil_3131/sil_3531 */
	अणु
		.flags		= SIL24_COMMON_FLAGS | SIL24_NPORTS2FLAG(1),
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
		.port_ops	= &sil24_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक sil24_tag(पूर्णांक tag)
अणु
	अगर (unlikely(ata_tag_पूर्णांकernal(tag)))
		वापस 0;
	वापस tag;
पूर्ण

अटल अचिन्हित दीर्घ sil24_port_offset(काष्ठा ata_port *ap)
अणु
	वापस ap->port_no * PORT_REGS_SIZE;
पूर्ण

अटल व्योम __iomem *sil24_port_base(काष्ठा ata_port *ap)
अणु
	वापस ap->host->iomap[SIL24_PORT_BAR] + sil24_port_offset(ap);
पूर्ण

अटल व्योम sil24_dev_config(काष्ठा ata_device *dev)
अणु
	व्योम __iomem *port = sil24_port_base(dev->link->ap);

	अगर (dev->cdb_len == 16)
		ग_लिखोl(PORT_CS_CDB16, port + PORT_CTRL_STAT);
	अन्यथा
		ग_लिखोl(PORT_CS_CDB16, port + PORT_CTRL_CLR);
पूर्ण

अटल व्योम sil24_पढ़ो_tf(काष्ठा ata_port *ap, पूर्णांक tag, काष्ठा ata_taskfile *tf)
अणु
	व्योम __iomem *port = sil24_port_base(ap);
	काष्ठा sil24_prb __iomem *prb;
	u8 fis[6 * 4];

	prb = port + PORT_LRAM + sil24_tag(tag) * PORT_LRAM_SLOT_SZ;
	स_नकल_fromio(fis, prb->fis, माप(fis));
	ata_tf_from_fis(fis, tf);
पूर्ण

अटल पूर्णांक sil24_scr_map[] = अणु
	[SCR_CONTROL]	= 0,
	[SCR_STATUS]	= 1,
	[SCR_ERROR]	= 2,
	[SCR_ACTIVE]	= 3,
पूर्ण;

अटल पूर्णांक sil24_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित sc_reg, u32 *val)
अणु
	व्योम __iomem *scr_addr = sil24_port_base(link->ap) + PORT_SCONTROL;

	अगर (sc_reg < ARRAY_SIZE(sil24_scr_map)) अणु
		*val = पढ़ोl(scr_addr + sil24_scr_map[sc_reg] * 4);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sil24_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित sc_reg, u32 val)
अणु
	व्योम __iomem *scr_addr = sil24_port_base(link->ap) + PORT_SCONTROL;

	अगर (sc_reg < ARRAY_SIZE(sil24_scr_map)) अणु
		ग_लिखोl(val, scr_addr + sil24_scr_map[sc_reg] * 4);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम sil24_config_port(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port = sil24_port_base(ap);

	/* configure IRQ WoC */
	अगर (ap->flags & SIL24_FLAG_PCIX_IRQ_WOC)
		ग_लिखोl(PORT_CS_IRQ_WOC, port + PORT_CTRL_STAT);
	अन्यथा
		ग_लिखोl(PORT_CS_IRQ_WOC, port + PORT_CTRL_CLR);

	/* zero error counters. */
	ग_लिखोw(0x8000, port + PORT_DECODE_ERR_THRESH);
	ग_लिखोw(0x8000, port + PORT_CRC_ERR_THRESH);
	ग_लिखोw(0x8000, port + PORT_HSHK_ERR_THRESH);
	ग_लिखोw(0x0000, port + PORT_DECODE_ERR_CNT);
	ग_लिखोw(0x0000, port + PORT_CRC_ERR_CNT);
	ग_लिखोw(0x0000, port + PORT_HSHK_ERR_CNT);

	/* always use 64bit activation */
	ग_लिखोl(PORT_CS_32BIT_ACTV, port + PORT_CTRL_CLR);

	/* clear port multiplier enable and resume bits */
	ग_लिखोl(PORT_CS_PMP_EN | PORT_CS_PMP_RESUME, port + PORT_CTRL_CLR);
पूर्ण

अटल व्योम sil24_config_pmp(काष्ठा ata_port *ap, पूर्णांक attached)
अणु
	व्योम __iomem *port = sil24_port_base(ap);

	अगर (attached)
		ग_लिखोl(PORT_CS_PMP_EN, port + PORT_CTRL_STAT);
	अन्यथा
		ग_लिखोl(PORT_CS_PMP_EN, port + PORT_CTRL_CLR);
पूर्ण

अटल व्योम sil24_clear_pmp(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port = sil24_port_base(ap);
	पूर्णांक i;

	ग_लिखोl(PORT_CS_PMP_RESUME, port + PORT_CTRL_CLR);

	क्रम (i = 0; i < SATA_PMP_MAX_PORTS; i++) अणु
		व्योम __iomem *pmp_base = port + PORT_PMP + i * PORT_PMP_SIZE;

		ग_लिखोl(0, pmp_base + PORT_PMP_STATUS);
		ग_लिखोl(0, pmp_base + PORT_PMP_QACTIVE);
	पूर्ण
पूर्ण

अटल पूर्णांक sil24_init_port(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port = sil24_port_base(ap);
	काष्ठा sil24_port_priv *pp = ap->निजी_data;
	u32 पंचांगp;

	/* clear PMP error status */
	अगर (sata_pmp_attached(ap))
		sil24_clear_pmp(ap);

	ग_लिखोl(PORT_CS_INIT, port + PORT_CTRL_STAT);
	ata_रुको_रेजिस्टर(ap, port + PORT_CTRL_STAT,
			  PORT_CS_INIT, PORT_CS_INIT, 10, 100);
	पंचांगp = ata_रुको_रेजिस्टर(ap, port + PORT_CTRL_STAT,
				PORT_CS_RDY, 0, 10, 100);

	अगर ((पंचांगp & (PORT_CS_INIT | PORT_CS_RDY)) != PORT_CS_RDY) अणु
		pp->करो_port_rst = 1;
		ap->link.eh_context.i.action |= ATA_EH_RESET;
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sil24_exec_polled_cmd(काष्ठा ata_port *ap, पूर्णांक pmp,
				 स्थिर काष्ठा ata_taskfile *tf,
				 पूर्णांक is_cmd, u32 ctrl,
				 अचिन्हित दीर्घ समयout_msec)
अणु
	व्योम __iomem *port = sil24_port_base(ap);
	काष्ठा sil24_port_priv *pp = ap->निजी_data;
	काष्ठा sil24_prb *prb = &pp->cmd_block[0].ata.prb;
	dma_addr_t paddr = pp->cmd_block_dma;
	u32 irq_enabled, irq_mask, irq_stat;
	पूर्णांक rc;

	prb->ctrl = cpu_to_le16(ctrl);
	ata_tf_to_fis(tf, pmp, is_cmd, prb->fis);

	/* temporarily plug completion and error पूर्णांकerrupts */
	irq_enabled = पढ़ोl(port + PORT_IRQ_ENABLE_SET);
	ग_लिखोl(PORT_IRQ_COMPLETE | PORT_IRQ_ERROR, port + PORT_IRQ_ENABLE_CLR);

	/*
	 * The barrier is required to ensure that ग_लिखोs to cmd_block reach
	 * the memory beक्रमe the ग_लिखो to PORT_CMD_ACTIVATE.
	 */
	wmb();
	ग_लिखोl((u32)paddr, port + PORT_CMD_ACTIVATE);
	ग_लिखोl((u64)paddr >> 32, port + PORT_CMD_ACTIVATE + 4);

	irq_mask = (PORT_IRQ_COMPLETE | PORT_IRQ_ERROR) << PORT_IRQ_RAW_SHIFT;
	irq_stat = ata_रुको_रेजिस्टर(ap, port + PORT_IRQ_STAT, irq_mask, 0x0,
				     10, समयout_msec);

	ग_लिखोl(irq_mask, port + PORT_IRQ_STAT); /* clear IRQs */
	irq_stat >>= PORT_IRQ_RAW_SHIFT;

	अगर (irq_stat & PORT_IRQ_COMPLETE)
		rc = 0;
	अन्यथा अणु
		/* क्रमce port पूर्णांकo known state */
		sil24_init_port(ap);

		अगर (irq_stat & PORT_IRQ_ERROR)
			rc = -EIO;
		अन्यथा
			rc = -EBUSY;
	पूर्ण

	/* restore IRQ enabled */
	ग_लिखोl(irq_enabled, port + PORT_IRQ_ENABLE_SET);

	वापस rc;
पूर्ण

अटल पूर्णांक sil24_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			   अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	पूर्णांक pmp = sata_srst_pmp(link);
	अचिन्हित दीर्घ समयout_msec = 0;
	काष्ठा ata_taskfile tf;
	स्थिर अक्षर *reason;
	पूर्णांक rc;

	DPRINTK("ENTER\n");

	/* put the port पूर्णांकo known state */
	अगर (sil24_init_port(ap)) अणु
		reason = "port not ready";
		जाओ err;
	पूर्ण

	/* करो SRST */
	अगर (समय_after(deadline, jअगरfies))
		समयout_msec = jअगरfies_to_msecs(deadline - jअगरfies);

	ata_tf_init(link->device, &tf);	/* करोesn't really matter */
	rc = sil24_exec_polled_cmd(ap, pmp, &tf, 0, PRB_CTRL_SRST,
				   समयout_msec);
	अगर (rc == -EBUSY) अणु
		reason = "timeout";
		जाओ err;
	पूर्ण अन्यथा अगर (rc) अणु
		reason = "SRST command error";
		जाओ err;
	पूर्ण

	sil24_पढ़ो_tf(ap, 0, &tf);
	*class = ata_dev_classअगरy(&tf);

	DPRINTK("EXIT, class=%u\n", *class);
	वापस 0;

 err:
	ata_link_err(link, "softreset failed (%s)\n", reason);
	वापस -EIO;
पूर्ण

अटल पूर्णांक sil24_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			   अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	व्योम __iomem *port = sil24_port_base(ap);
	काष्ठा sil24_port_priv *pp = ap->निजी_data;
	पूर्णांक did_port_rst = 0;
	स्थिर अक्षर *reason;
	पूर्णांक tout_msec, rc;
	u32 पंचांगp;

 retry:
	/* Someबार, DEV_RST is not enough to recover the controller.
	 * This happens often after PM DMA CS errata.
	 */
	अगर (pp->करो_port_rst) अणु
		ata_port_warn(ap,
			      "controller in dubious state, performing PORT_RST\n");

		ग_लिखोl(PORT_CS_PORT_RST, port + PORT_CTRL_STAT);
		ata_msleep(ap, 10);
		ग_लिखोl(PORT_CS_PORT_RST, port + PORT_CTRL_CLR);
		ata_रुको_रेजिस्टर(ap, port + PORT_CTRL_STAT, PORT_CS_RDY, 0,
				  10, 5000);

		/* restore port configuration */
		sil24_config_port(ap);
		sil24_config_pmp(ap, ap->nr_pmp_links);

		pp->करो_port_rst = 0;
		did_port_rst = 1;
	पूर्ण

	/* sil24 करोes the right thing(पंचांग) without any protection */
	sata_set_spd(link);

	tout_msec = 100;
	अगर (ata_link_online(link))
		tout_msec = 5000;

	ग_लिखोl(PORT_CS_DEV_RST, port + PORT_CTRL_STAT);
	पंचांगp = ata_रुको_रेजिस्टर(ap, port + PORT_CTRL_STAT,
				PORT_CS_DEV_RST, PORT_CS_DEV_RST, 10,
				tout_msec);

	/* SStatus oscillates between zero and valid status after
	 * DEV_RST, debounce it.
	 */
	rc = sata_link_debounce(link, sata_deb_timing_दीर्घ, deadline);
	अगर (rc) अणु
		reason = "PHY debouncing failed";
		जाओ err;
	पूर्ण

	अगर (पंचांगp & PORT_CS_DEV_RST) अणु
		अगर (ata_link_offline(link))
			वापस 0;
		reason = "link not ready";
		जाओ err;
	पूर्ण

	/* Sil24 करोesn't store signature FIS after hardreset, so we
	 * can't रुको क्रम BSY to clear.  Some devices take a दीर्घ समय
	 * to get पढ़ोy and those devices will choke अगर we करोn't रुको
	 * क्रम BSY clearance here.  Tell libata to perक्रमm follow-up
	 * softreset.
	 */
	वापस -EAGAIN;

 err:
	अगर (!did_port_rst) अणु
		pp->करो_port_rst = 1;
		जाओ retry;
	पूर्ण

	ata_link_err(link, "hardreset failed (%s)\n", reason);
	वापस -EIO;
पूर्ण

अटल अंतरभूत व्योम sil24_fill_sg(काष्ठा ata_queued_cmd *qc,
				 काष्ठा sil24_sge *sge)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा sil24_sge *last_sge = शून्य;
	अचिन्हित पूर्णांक si;

	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		sge->addr = cpu_to_le64(sg_dma_address(sg));
		sge->cnt = cpu_to_le32(sg_dma_len(sg));
		sge->flags = 0;

		last_sge = sge;
		sge++;
	पूर्ण

	last_sge->flags = cpu_to_le32(SGE_TRM);
पूर्ण

अटल पूर्णांक sil24_qc_defer(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_link *link = qc->dev->link;
	काष्ठा ata_port *ap = link->ap;
	u8 prot = qc->tf.protocol;

	/*
	 * There is a bug in the chip:
	 * Port LRAM Causes the PRB/SGT Data to be Corrupted
	 * If the host issues a पढ़ो request क्रम LRAM and SActive रेजिस्टरs
	 * जबतक active commands are available in the port, PRB/SGT data in
	 * the LRAM can become corrupted. This issue applies only when
	 * पढ़ोing from, but not writing to, the LRAM.
	 *
	 * Thereक्रमe, पढ़ोing LRAM when there is no particular error [and
	 * other commands may be outstanding] is prohibited.
	 *
	 * To aव्योम this bug there are two situations where a command must run
	 * exclusive of any other commands on the port:
	 *
	 * - ATAPI commands which check the sense data
	 * - Passthrough ATA commands which always have ATA_QCFLAG_RESULT_TF
	 *   set.
	 *
 	 */
	पूर्णांक is_excl = (ata_is_atapi(prot) ||
		       (qc->flags & ATA_QCFLAG_RESULT_TF));

	अगर (unlikely(ap->excl_link)) अणु
		अगर (link == ap->excl_link) अणु
			अगर (ap->nr_active_links)
				वापस ATA_DEFER_PORT;
			qc->flags |= ATA_QCFLAG_CLEAR_EXCL;
		पूर्ण अन्यथा
			वापस ATA_DEFER_PORT;
	पूर्ण अन्यथा अगर (unlikely(is_excl)) अणु
		ap->excl_link = link;
		अगर (ap->nr_active_links)
			वापस ATA_DEFER_PORT;
		qc->flags |= ATA_QCFLAG_CLEAR_EXCL;
	पूर्ण

	वापस ata_std_qc_defer(qc);
पूर्ण

अटल क्रमागत ata_completion_errors sil24_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा sil24_port_priv *pp = ap->निजी_data;
	जोड़ sil24_cmd_block *cb;
	काष्ठा sil24_prb *prb;
	काष्ठा sil24_sge *sge;
	u16 ctrl = 0;

	cb = &pp->cmd_block[sil24_tag(qc->hw_tag)];

	अगर (!ata_is_atapi(qc->tf.protocol)) अणु
		prb = &cb->ata.prb;
		sge = cb->ata.sge;
		अगर (ata_is_data(qc->tf.protocol)) अणु
			u16 prot = 0;
			ctrl = PRB_CTRL_PROTOCOL;
			अगर (ata_is_ncq(qc->tf.protocol))
				prot |= PRB_PROT_NCQ;
			अगर (qc->tf.flags & ATA_TFLAG_WRITE)
				prot |= PRB_PROT_WRITE;
			अन्यथा
				prot |= PRB_PROT_READ;
			prb->prot = cpu_to_le16(prot);
		पूर्ण
	पूर्ण अन्यथा अणु
		prb = &cb->atapi.prb;
		sge = cb->atapi.sge;
		स_रखो(cb->atapi.cdb, 0, माप(cb->atapi.cdb));
		स_नकल(cb->atapi.cdb, qc->cdb, qc->dev->cdb_len);

		अगर (ata_is_data(qc->tf.protocol)) अणु
			अगर (qc->tf.flags & ATA_TFLAG_WRITE)
				ctrl = PRB_CTRL_PACKET_WRITE;
			अन्यथा
				ctrl = PRB_CTRL_PACKET_READ;
		पूर्ण
	पूर्ण

	prb->ctrl = cpu_to_le16(ctrl);
	ata_tf_to_fis(&qc->tf, qc->dev->link->pmp, 1, prb->fis);

	अगर (qc->flags & ATA_QCFLAG_DMAMAP)
		sil24_fill_sg(qc, sge);

	वापस AC_ERR_OK;
पूर्ण

अटल अचिन्हित पूर्णांक sil24_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा sil24_port_priv *pp = ap->निजी_data;
	व्योम __iomem *port = sil24_port_base(ap);
	अचिन्हित पूर्णांक tag = sil24_tag(qc->hw_tag);
	dma_addr_t paddr;
	व्योम __iomem *activate;

	paddr = pp->cmd_block_dma + tag * माप(*pp->cmd_block);
	activate = port + PORT_CMD_ACTIVATE + tag * 8;

	/*
	 * The barrier is required to ensure that ग_लिखोs to cmd_block reach
	 * the memory beक्रमe the ग_लिखो to PORT_CMD_ACTIVATE.
	 */
	wmb();
	ग_लिखोl((u32)paddr, activate);
	ग_लिखोl((u64)paddr >> 32, activate + 4);

	वापस 0;
पूर्ण

अटल bool sil24_qc_fill_rtf(काष्ठा ata_queued_cmd *qc)
अणु
	sil24_पढ़ो_tf(qc->ap, qc->hw_tag, &qc->result_tf);
	वापस true;
पूर्ण

अटल व्योम sil24_pmp_attach(काष्ठा ata_port *ap)
अणु
	u32 *gscr = ap->link.device->gscr;

	sil24_config_pmp(ap, 1);
	sil24_init_port(ap);

	अगर (sata_pmp_gscr_venकरोr(gscr) == 0x11ab &&
	    sata_pmp_gscr_devid(gscr) == 0x4140) अणु
		ata_port_info(ap,
			"disabling NCQ support due to sil24-mv4140 quirk\n");
		ap->flags &= ~ATA_FLAG_NCQ;
	पूर्ण
पूर्ण

अटल व्योम sil24_pmp_detach(काष्ठा ata_port *ap)
अणु
	sil24_init_port(ap);
	sil24_config_pmp(ap, 0);

	ap->flags |= ATA_FLAG_NCQ;
पूर्ण

अटल पूर्णांक sil24_pmp_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			       अचिन्हित दीर्घ deadline)
अणु
	पूर्णांक rc;

	rc = sil24_init_port(link->ap);
	अगर (rc) अणु
		ata_link_err(link, "hardreset failed (port not ready)\n");
		वापस rc;
	पूर्ण

	वापस sata_std_hardreset(link, class, deadline);
पूर्ण

अटल व्योम sil24_मुक्तze(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port = sil24_port_base(ap);

	/* Port-wide IRQ mask in HOST_CTRL करोesn't really work, clear
	 * PORT_IRQ_ENABLE instead.
	 */
	ग_लिखोl(0xffff, port + PORT_IRQ_ENABLE_CLR);
पूर्ण

अटल व्योम sil24_thaw(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port = sil24_port_base(ap);
	u32 पंचांगp;

	/* clear IRQ */
	पंचांगp = पढ़ोl(port + PORT_IRQ_STAT);
	ग_लिखोl(पंचांगp, port + PORT_IRQ_STAT);

	/* turn IRQ back on */
	ग_लिखोl(DEF_PORT_IRQ, port + PORT_IRQ_ENABLE_SET);
पूर्ण

अटल व्योम sil24_error_पूर्णांकr(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port = sil24_port_base(ap);
	काष्ठा sil24_port_priv *pp = ap->निजी_data;
	काष्ठा ata_queued_cmd *qc = शून्य;
	काष्ठा ata_link *link;
	काष्ठा ata_eh_info *ehi;
	पूर्णांक पात = 0, मुक्तze = 0;
	u32 irq_stat;

	/* on error, we need to clear IRQ explicitly */
	irq_stat = पढ़ोl(port + PORT_IRQ_STAT);
	ग_लिखोl(irq_stat, port + PORT_IRQ_STAT);

	/* first, analyze and record host port events */
	link = &ap->link;
	ehi = &link->eh_info;
	ata_ehi_clear_desc(ehi);

	ata_ehi_push_desc(ehi, "irq_stat 0x%08x", irq_stat);

	अगर (irq_stat & PORT_IRQ_SDB_NOTIFY) अणु
		ata_ehi_push_desc(ehi, "SDB notify");
		sata_async_notअगरication(ap);
	पूर्ण

	अगर (irq_stat & (PORT_IRQ_PHYRDY_CHG | PORT_IRQ_DEV_XCHG)) अणु
		ata_ehi_hotplugged(ehi);
		ata_ehi_push_desc(ehi, "%s",
				  irq_stat & PORT_IRQ_PHYRDY_CHG ?
				  "PHY RDY changed" : "device exchanged");
		मुक्तze = 1;
	पूर्ण

	अगर (irq_stat & PORT_IRQ_UNK_FIS) अणु
		ehi->err_mask |= AC_ERR_HSM;
		ehi->action |= ATA_EH_RESET;
		ata_ehi_push_desc(ehi, "unknown FIS");
		मुक्तze = 1;
	पूर्ण

	/* deal with command error */
	अगर (irq_stat & PORT_IRQ_ERROR) अणु
		स्थिर काष्ठा sil24_cerr_info *ci = शून्य;
		अचिन्हित पूर्णांक err_mask = 0, action = 0;
		u32 context, cerr;
		पूर्णांक pmp;

		पात = 1;

		/* DMA Context Switch Failure in Port Multiplier Mode
		 * errata.  If we have active commands to 3 or more
		 * devices, any error condition on active devices can
		 * corrupt DMA context चयनing.
		 */
		अगर (ap->nr_active_links >= 3) अणु
			ehi->err_mask |= AC_ERR_OTHER;
			ehi->action |= ATA_EH_RESET;
			ata_ehi_push_desc(ehi, "PMP DMA CS errata");
			pp->करो_port_rst = 1;
			मुक्तze = 1;
		पूर्ण

		/* find out the offending link and qc */
		अगर (sata_pmp_attached(ap)) अणु
			context = पढ़ोl(port + PORT_CONTEXT);
			pmp = (context >> 5) & 0xf;

			अगर (pmp < ap->nr_pmp_links) अणु
				link = &ap->pmp_link[pmp];
				ehi = &link->eh_info;
				qc = ata_qc_from_tag(ap, link->active_tag);

				ata_ehi_clear_desc(ehi);
				ata_ehi_push_desc(ehi, "irq_stat 0x%08x",
						  irq_stat);
			पूर्ण अन्यथा अणु
				err_mask |= AC_ERR_HSM;
				action |= ATA_EH_RESET;
				मुक्तze = 1;
			पूर्ण
		पूर्ण अन्यथा
			qc = ata_qc_from_tag(ap, link->active_tag);

		/* analyze CMD_ERR */
		cerr = पढ़ोl(port + PORT_CMD_ERR);
		अगर (cerr < ARRAY_SIZE(sil24_cerr_db))
			ci = &sil24_cerr_db[cerr];

		अगर (ci && ci->desc) अणु
			err_mask |= ci->err_mask;
			action |= ci->action;
			अगर (action & ATA_EH_RESET)
				मुक्तze = 1;
			ata_ehi_push_desc(ehi, "%s", ci->desc);
		पूर्ण अन्यथा अणु
			err_mask |= AC_ERR_OTHER;
			action |= ATA_EH_RESET;
			मुक्तze = 1;
			ata_ehi_push_desc(ehi, "unknown command error %d",
					  cerr);
		पूर्ण

		/* record error info */
		अगर (qc)
			qc->err_mask |= err_mask;
		अन्यथा
			ehi->err_mask |= err_mask;

		ehi->action |= action;

		/* अगर PMP, resume */
		अगर (sata_pmp_attached(ap))
			ग_लिखोl(PORT_CS_PMP_RESUME, port + PORT_CTRL_STAT);
	पूर्ण

	/* मुक्तze or पात */
	अगर (मुक्तze)
		ata_port_मुक्तze(ap);
	अन्यथा अगर (पात) अणु
		अगर (qc)
			ata_link_पात(qc->dev->link);
		अन्यथा
			ata_port_पात(ap);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sil24_host_पूर्णांकr(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port = sil24_port_base(ap);
	u32 slot_stat, qc_active;
	पूर्णांक rc;

	/* If PCIX_IRQ_WOC, there's an inherent race winकरोw between
	 * clearing IRQ pending status and पढ़ोing PORT_SLOT_STAT
	 * which may cause spurious पूर्णांकerrupts afterwards.  This is
	 * unaव्योमable and much better than losing पूर्णांकerrupts which
	 * happens अगर IRQ pending is cleared after पढ़ोing
	 * PORT_SLOT_STAT.
	 */
	अगर (ap->flags & SIL24_FLAG_PCIX_IRQ_WOC)
		ग_लिखोl(PORT_IRQ_COMPLETE, port + PORT_IRQ_STAT);

	slot_stat = पढ़ोl(port + PORT_SLOT_STAT);

	अगर (unlikely(slot_stat & HOST_SSTAT_ATTN)) अणु
		sil24_error_पूर्णांकr(ap);
		वापस;
	पूर्ण

	qc_active = slot_stat & ~HOST_SSTAT_ATTN;
	rc = ata_qc_complete_multiple(ap, qc_active);
	अगर (rc > 0)
		वापस;
	अगर (rc < 0) अणु
		काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
		ehi->err_mask |= AC_ERR_HSM;
		ehi->action |= ATA_EH_RESET;
		ata_port_मुक्तze(ap);
		वापस;
	पूर्ण

	/* spurious पूर्णांकerrupts are expected अगर PCIX_IRQ_WOC */
	अगर (!(ap->flags & SIL24_FLAG_PCIX_IRQ_WOC) && ata_ratelimit())
		ata_port_info(ap,
			"spurious interrupt (slot_stat 0x%x active_tag %d sactive 0x%x)\n",
			slot_stat, ap->link.active_tag, ap->link.sactive);
पूर्ण

अटल irqवापस_t sil24_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	व्योम __iomem *host_base = host->iomap[SIL24_HOST_BAR];
	अचिन्हित handled = 0;
	u32 status;
	पूर्णांक i;

	status = पढ़ोl(host_base + HOST_IRQ_STAT);

	अगर (status == 0xffffffff) अणु
		dev_err(host->dev, "IRQ status == 0xffffffff, "
			"PCI fault or device removal?\n");
		जाओ out;
	पूर्ण

	अगर (!(status & IRQ_STAT_4PORTS))
		जाओ out;

	spin_lock(&host->lock);

	क्रम (i = 0; i < host->n_ports; i++)
		अगर (status & (1 << i)) अणु
			sil24_host_पूर्णांकr(host->ports[i]);
			handled++;
		पूर्ण

	spin_unlock(&host->lock);
 out:
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम sil24_error_handler(काष्ठा ata_port *ap)
अणु
	काष्ठा sil24_port_priv *pp = ap->निजी_data;

	अगर (sil24_init_port(ap))
		ata_eh_मुक्तze_port(ap);

	sata_pmp_error_handler(ap);

	pp->करो_port_rst = 0;
पूर्ण

अटल व्योम sil24_post_पूर्णांकernal_cmd(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;

	/* make DMA engine क्रमget about the failed command */
	अगर ((qc->flags & ATA_QCFLAG_FAILED) && sil24_init_port(ap))
		ata_eh_मुक्तze_port(ap);
पूर्ण

अटल पूर्णांक sil24_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा device *dev = ap->host->dev;
	काष्ठा sil24_port_priv *pp;
	जोड़ sil24_cmd_block *cb;
	माप_प्रकार cb_size = माप(*cb) * SIL24_MAX_CMDS;
	dma_addr_t cb_dma;

	pp = devm_kzalloc(dev, माप(*pp), GFP_KERNEL);
	अगर (!pp)
		वापस -ENOMEM;

	cb = dmam_alloc_coherent(dev, cb_size, &cb_dma, GFP_KERNEL);
	अगर (!cb)
		वापस -ENOMEM;

	pp->cmd_block = cb;
	pp->cmd_block_dma = cb_dma;

	ap->निजी_data = pp;

	ata_port_pbar_desc(ap, SIL24_HOST_BAR, -1, "host");
	ata_port_pbar_desc(ap, SIL24_PORT_BAR, sil24_port_offset(ap), "port");

	वापस 0;
पूर्ण

अटल व्योम sil24_init_controller(काष्ठा ata_host *host)
अणु
	व्योम __iomem *host_base = host->iomap[SIL24_HOST_BAR];
	u32 पंचांगp;
	पूर्णांक i;

	/* GPIO off */
	ग_लिखोl(0, host_base + HOST_FLASH_CMD);

	/* clear global reset & mask पूर्णांकerrupts during initialization */
	ग_लिखोl(0, host_base + HOST_CTRL);

	/* init ports */
	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		व्योम __iomem *port = sil24_port_base(ap);


		/* Initial PHY setting */
		ग_लिखोl(0x20c, port + PORT_PHY_CFG);

		/* Clear port RST */
		पंचांगp = पढ़ोl(port + PORT_CTRL_STAT);
		अगर (पंचांगp & PORT_CS_PORT_RST) अणु
			ग_लिखोl(PORT_CS_PORT_RST, port + PORT_CTRL_CLR);
			पंचांगp = ata_रुको_रेजिस्टर(शून्य, port + PORT_CTRL_STAT,
						PORT_CS_PORT_RST,
						PORT_CS_PORT_RST, 10, 100);
			अगर (पंचांगp & PORT_CS_PORT_RST)
				dev_err(host->dev,
					"failed to clear port RST\n");
		पूर्ण

		/* configure port */
		sil24_config_port(ap);
	पूर्ण

	/* Turn on पूर्णांकerrupts */
	ग_लिखोl(IRQ_STAT_4PORTS, host_base + HOST_CTRL);
पूर्ण

अटल पूर्णांक sil24_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	बाह्य पूर्णांक __MARKER__sil24_cmd_block_is_sized_wrongly;
	काष्ठा ata_port_info pi = sil24_port_info[ent->driver_data];
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &pi, शून्य पूर्ण;
	व्योम __iomem * स्थिर *iomap;
	काष्ठा ata_host *host;
	पूर्णांक rc;
	u32 पंचांगp;

	/* cause link error अगर sil24_cmd_block is sized wrongly */
	अगर (माप(जोड़ sil24_cmd_block) != PAGE_SIZE)
		__MARKER__sil24_cmd_block_is_sized_wrongly = 1;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	/* acquire resources */
	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	rc = pcim_iomap_regions(pdev,
				(1 << SIL24_HOST_BAR) | (1 << SIL24_PORT_BAR),
				DRV_NAME);
	अगर (rc)
		वापस rc;
	iomap = pcim_iomap_table(pdev);

	/* apply workaround क्रम completion IRQ loss on PCI-X errata */
	अगर (pi.flags & SIL24_FLAG_PCIX_IRQ_WOC) अणु
		पंचांगp = पढ़ोl(iomap[SIL24_HOST_BAR] + HOST_CTRL);
		अगर (पंचांगp & (HOST_CTRL_TRDY | HOST_CTRL_STOP | HOST_CTRL_DEVSEL))
			dev_info(&pdev->dev,
				 "Applying completion IRQ loss on PCI-X errata fix\n");
		अन्यथा
			pi.flags &= ~SIL24_FLAG_PCIX_IRQ_WOC;
	पूर्ण

	/* allocate and fill host */
	host = ata_host_alloc_pinfo(&pdev->dev, ppi,
				    SIL24_FLAG2NPORTS(ppi[0]->flags));
	अगर (!host)
		वापस -ENOMEM;
	host->iomap = iomap;

	/* configure and activate the device */
	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (rc) अणु
		dev_err(&pdev->dev, "DMA enable failed\n");
		वापस rc;
	पूर्ण

	/* Set max पढ़ो request size to 4096.  This slightly increases
	 * ग_लिखो throughput क्रम pci-e variants.
	 */
	pcie_set_पढ़ोrq(pdev, 4096);

	sil24_init_controller(host);

	अगर (sata_sil24_msi && !pci_enable_msi(pdev)) अणु
		dev_info(&pdev->dev, "Using MSI\n");
		pci_पूर्णांकx(pdev, 0);
	पूर्ण

	pci_set_master(pdev);
	वापस ata_host_activate(host, pdev->irq, sil24_पूर्णांकerrupt, IRQF_SHARED,
				 &sil24_sht);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sil24_pci_device_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	व्योम __iomem *host_base = host->iomap[SIL24_HOST_BAR];
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	अगर (pdev->dev.घातer.घातer_state.event == PM_EVENT_SUSPEND)
		ग_लिखोl(HOST_CTRL_GLOBAL_RST, host_base + HOST_CTRL);

	sil24_init_controller(host);

	ata_host_resume(host);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sil24_port_resume(काष्ठा ata_port *ap)
अणु
	sil24_config_pmp(ap, ap->nr_pmp_links);
	वापस 0;
पूर्ण
#पूर्ण_अगर

module_pci_driver(sil24_pci_driver);

MODULE_AUTHOR("Tejun Heo");
MODULE_DESCRIPTION("Silicon Image 3124/3132 SATA low-level driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, sil24_pci_tbl);
