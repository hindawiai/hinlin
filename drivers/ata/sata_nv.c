<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  sata_nv.c - NVIDIA nForce SATA
 *
 *  Copyright 2004 NVIDIA Corp.  All rights reserved.
 *  Copyright 2004 Andrew Chew
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 *
 *  No hardware करोcumentation available outside of NVIDIA.
 *  This driver programs the NVIDIA SATA controller in a similar
 *  fashion as with other PCI IDE BMDMA controllers, with a few
 *  NV-specअगरic details such as रेजिस्टर offsets, SATA phy location,
 *  hotplug info, etc.
 *
 *  CK804/MCP04 controllers support an alternate programming पूर्णांकerface
 *  similar to the ADMA specअगरication (with some modअगरications).
 *  This allows the use of NCQ. Non-DMA-mapped ATA commands are still
 *  sent through the legacy पूर्णांकerface.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME			"sata_nv"
#घोषणा DRV_VERSION			"3.5"

#घोषणा NV_ADMA_DMA_BOUNDARY		0xffffffffUL

क्रमागत अणु
	NV_MMIO_BAR			= 5,

	NV_PORTS			= 2,
	NV_PIO_MASK			= ATA_PIO4,
	NV_MWDMA_MASK			= ATA_MWDMA2,
	NV_UDMA_MASK			= ATA_UDMA6,
	NV_PORT0_SCR_REG_OFFSET		= 0x00,
	NV_PORT1_SCR_REG_OFFSET		= 0x40,

	/* INT_STATUS/ENABLE */
	NV_INT_STATUS			= 0x10,
	NV_INT_ENABLE			= 0x11,
	NV_INT_STATUS_CK804		= 0x440,
	NV_INT_ENABLE_CK804		= 0x441,

	/* INT_STATUS/ENABLE bits */
	NV_INT_DEV			= 0x01,
	NV_INT_PM			= 0x02,
	NV_INT_ADDED			= 0x04,
	NV_INT_REMOVED			= 0x08,

	NV_INT_PORT_SHIFT		= 4,	/* each port occupies 4 bits */

	NV_INT_ALL			= 0x0f,
	NV_INT_MASK			= NV_INT_DEV |
					  NV_INT_ADDED | NV_INT_REMOVED,

	/* INT_CONFIG */
	NV_INT_CONFIG			= 0x12,
	NV_INT_CONFIG_METHD		= 0x01, // 0 = INT, 1 = SMI

	// For PCI config रेजिस्टर 20
	NV_MCP_SATA_CFG_20		= 0x50,
	NV_MCP_SATA_CFG_20_SATA_SPACE_EN = 0x04,
	NV_MCP_SATA_CFG_20_PORT0_EN	= (1 << 17),
	NV_MCP_SATA_CFG_20_PORT1_EN	= (1 << 16),
	NV_MCP_SATA_CFG_20_PORT0_PWB_EN	= (1 << 14),
	NV_MCP_SATA_CFG_20_PORT1_PWB_EN	= (1 << 12),

	NV_ADMA_MAX_CPBS		= 32,
	NV_ADMA_CPB_SZ			= 128,
	NV_ADMA_APRD_SZ			= 16,
	NV_ADMA_SGTBL_LEN		= (1024 - NV_ADMA_CPB_SZ) /
					   NV_ADMA_APRD_SZ,
	NV_ADMA_SGTBL_TOTAL_LEN		= NV_ADMA_SGTBL_LEN + 5,
	NV_ADMA_SGTBL_SZ                = NV_ADMA_SGTBL_LEN * NV_ADMA_APRD_SZ,
	NV_ADMA_PORT_PRIV_DMA_SZ        = NV_ADMA_MAX_CPBS *
					   (NV_ADMA_CPB_SZ + NV_ADMA_SGTBL_SZ),

	/* BAR5 offset to ADMA general रेजिस्टरs */
	NV_ADMA_GEN			= 0x400,
	NV_ADMA_GEN_CTL			= 0x00,
	NV_ADMA_NOTIFIER_CLEAR		= 0x30,

	/* BAR5 offset to ADMA ports */
	NV_ADMA_PORT			= 0x480,

	/* size of ADMA port रेजिस्टर space  */
	NV_ADMA_PORT_SIZE		= 0x100,

	/* ADMA port रेजिस्टरs */
	NV_ADMA_CTL			= 0x40,
	NV_ADMA_CPB_COUNT		= 0x42,
	NV_ADMA_NEXT_CPB_IDX		= 0x43,
	NV_ADMA_STAT			= 0x44,
	NV_ADMA_CPB_BASE_LOW		= 0x48,
	NV_ADMA_CPB_BASE_HIGH		= 0x4C,
	NV_ADMA_APPEND			= 0x50,
	NV_ADMA_NOTIFIER		= 0x68,
	NV_ADMA_NOTIFIER_ERROR		= 0x6C,

	/* NV_ADMA_CTL रेजिस्टर bits */
	NV_ADMA_CTL_HOTPLUG_IEN		= (1 << 0),
	NV_ADMA_CTL_CHANNEL_RESET	= (1 << 5),
	NV_ADMA_CTL_GO			= (1 << 7),
	NV_ADMA_CTL_AIEN		= (1 << 8),
	NV_ADMA_CTL_READ_NON_COHERENT	= (1 << 11),
	NV_ADMA_CTL_WRITE_NON_COHERENT	= (1 << 12),

	/* CPB response flag bits */
	NV_CPB_RESP_DONE		= (1 << 0),
	NV_CPB_RESP_ATA_ERR		= (1 << 3),
	NV_CPB_RESP_CMD_ERR		= (1 << 4),
	NV_CPB_RESP_CPB_ERR		= (1 << 7),

	/* CPB control flag bits */
	NV_CPB_CTL_CPB_VALID		= (1 << 0),
	NV_CPB_CTL_QUEUE		= (1 << 1),
	NV_CPB_CTL_APRD_VALID		= (1 << 2),
	NV_CPB_CTL_IEN			= (1 << 3),
	NV_CPB_CTL_FPDMA		= (1 << 4),

	/* APRD flags */
	NV_APRD_WRITE			= (1 << 1),
	NV_APRD_END			= (1 << 2),
	NV_APRD_CONT			= (1 << 3),

	/* NV_ADMA_STAT flags */
	NV_ADMA_STAT_TIMEOUT		= (1 << 0),
	NV_ADMA_STAT_HOTUNPLUG		= (1 << 1),
	NV_ADMA_STAT_HOTPLUG		= (1 << 2),
	NV_ADMA_STAT_CPBERR		= (1 << 4),
	NV_ADMA_STAT_SERROR		= (1 << 5),
	NV_ADMA_STAT_CMD_COMPLETE	= (1 << 6),
	NV_ADMA_STAT_IDLE		= (1 << 8),
	NV_ADMA_STAT_LEGACY		= (1 << 9),
	NV_ADMA_STAT_STOPPED		= (1 << 10),
	NV_ADMA_STAT_DONE		= (1 << 12),
	NV_ADMA_STAT_ERR		= NV_ADMA_STAT_CPBERR |
					  NV_ADMA_STAT_TIMEOUT,

	/* port flags */
	NV_ADMA_PORT_REGISTER_MODE	= (1 << 0),
	NV_ADMA_ATAPI_SETUP_COMPLETE	= (1 << 1),

	/* MCP55 reg offset */
	NV_CTL_MCP55			= 0x400,
	NV_INT_STATUS_MCP55		= 0x440,
	NV_INT_ENABLE_MCP55		= 0x444,
	NV_NCQ_REG_MCP55		= 0x448,

	/* MCP55 */
	NV_INT_ALL_MCP55		= 0xffff,
	NV_INT_PORT_SHIFT_MCP55		= 16,	/* each port occupies 16 bits */
	NV_INT_MASK_MCP55		= NV_INT_ALL_MCP55 & 0xfffd,

	/* SWNCQ ENABLE BITS*/
	NV_CTL_PRI_SWNCQ		= 0x02,
	NV_CTL_SEC_SWNCQ		= 0x04,

	/* SW NCQ status bits*/
	NV_SWNCQ_IRQ_DEV		= (1 << 0),
	NV_SWNCQ_IRQ_PM			= (1 << 1),
	NV_SWNCQ_IRQ_ADDED		= (1 << 2),
	NV_SWNCQ_IRQ_REMOVED		= (1 << 3),

	NV_SWNCQ_IRQ_BACKOUT		= (1 << 4),
	NV_SWNCQ_IRQ_SDBFIS		= (1 << 5),
	NV_SWNCQ_IRQ_DHREGFIS		= (1 << 6),
	NV_SWNCQ_IRQ_DMASETUP		= (1 << 7),

	NV_SWNCQ_IRQ_HOTPLUG		= NV_SWNCQ_IRQ_ADDED |
					  NV_SWNCQ_IRQ_REMOVED,

पूर्ण;

/* ADMA Physical Region Descriptor - one SG segment */
काष्ठा nv_adma_prd अणु
	__le64			addr;
	__le32			len;
	u8			flags;
	u8			packet_len;
	__le16			reserved;
पूर्ण;

क्रमागत nv_adma_regbits अणु
	CMDEND	= (1 << 15),		/* end of command list */
	WNB	= (1 << 14),		/* रुको-not-BSY */
	IGN	= (1 << 13),		/* ignore this entry */
	CS1n	= (1 << (4 + 8)),	/* std. PATA संकेतs follow... */
	DA2	= (1 << (2 + 8)),
	DA1	= (1 << (1 + 8)),
	DA0	= (1 << (0 + 8)),
पूर्ण;

/* ADMA Command Parameter Block
   The first 5 SG segments are stored inside the Command Parameter Block itself.
   If there are more than 5 segments the reमुख्यder are stored in a separate
   memory area indicated by next_aprd. */
काष्ठा nv_adma_cpb अणु
	u8			resp_flags;    /* 0 */
	u8			reserved1;     /* 1 */
	u8			ctl_flags;     /* 2 */
	/* len is length of taskfile in 64 bit words */
	u8			len;		/* 3  */
	u8			tag;           /* 4 */
	u8			next_cpb_idx;  /* 5 */
	__le16			reserved2;     /* 6-7 */
	__le16			tf[12];        /* 8-31 */
	काष्ठा nv_adma_prd	aprd[5];       /* 32-111 */
	__le64			next_aprd;     /* 112-119 */
	__le64			reserved3;     /* 120-127 */
पूर्ण;


काष्ठा nv_adma_port_priv अणु
	काष्ठा nv_adma_cpb	*cpb;
	dma_addr_t		cpb_dma;
	काष्ठा nv_adma_prd	*aprd;
	dma_addr_t		aprd_dma;
	व्योम __iomem		*ctl_block;
	व्योम __iomem		*gen_block;
	व्योम __iomem		*notअगरier_clear_block;
	u64			adma_dma_mask;
	u8			flags;
	पूर्णांक			last_issue_ncq;
पूर्ण;

काष्ठा nv_host_priv अणु
	अचिन्हित दीर्घ		type;
पूर्ण;

काष्ठा defer_queue अणु
	u32		defer_bits;
	अचिन्हित पूर्णांक	head;
	अचिन्हित पूर्णांक	tail;
	अचिन्हित पूर्णांक	tag[ATA_MAX_QUEUE];
पूर्ण;

क्रमागत ncq_saw_flag_list अणु
	ncq_saw_d2h	= (1U << 0),
	ncq_saw_dmas	= (1U << 1),
	ncq_saw_sdb	= (1U << 2),
	ncq_saw_backout	= (1U << 3),
पूर्ण;

काष्ठा nv_swncq_port_priv अणु
	काष्ठा ata_bmdma_prd *prd;	 /* our SG list */
	dma_addr_t	prd_dma; /* and its DMA mapping */
	व्योम __iomem	*sactive_block;
	व्योम __iomem	*irq_block;
	व्योम __iomem	*tag_block;
	u32		qc_active;

	अचिन्हित पूर्णांक	last_issue_tag;

	/* fअगरo circular queue to store deferral command */
	काष्ठा defer_queue defer_queue;

	/* क्रम NCQ पूर्णांकerrupt analysis */
	u32		dhfis_bits;
	u32		dmafis_bits;
	u32		sdbfis_bits;

	अचिन्हित पूर्णांक	ncq_flags;
पूर्ण;


#घोषणा NV_ADMA_CHECK_INTR(GCTL, PORT) ((GCTL) & (1 << (19 + (12 * (PORT)))))

अटल पूर्णांक nv_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक nv_pci_device_resume(काष्ठा pci_dev *pdev);
#पूर्ण_अगर
अटल व्योम nv_ck804_host_stop(काष्ठा ata_host *host);
अटल irqवापस_t nv_generic_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);
अटल irqवापस_t nv_nf2_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);
अटल irqवापस_t nv_ck804_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);
अटल पूर्णांक nv_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 *val);
अटल पूर्णांक nv_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 val);

अटल पूर्णांक nv_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			अचिन्हित दीर्घ deadline);
अटल व्योम nv_nf2_मुक्तze(काष्ठा ata_port *ap);
अटल व्योम nv_nf2_thaw(काष्ठा ata_port *ap);
अटल व्योम nv_ck804_मुक्तze(काष्ठा ata_port *ap);
अटल व्योम nv_ck804_thaw(काष्ठा ata_port *ap);
अटल पूर्णांक nv_adma_slave_config(काष्ठा scsi_device *sdev);
अटल पूर्णांक nv_adma_check_atapi_dma(काष्ठा ata_queued_cmd *qc);
अटल क्रमागत ata_completion_errors nv_adma_qc_prep(काष्ठा ata_queued_cmd *qc);
अटल अचिन्हित पूर्णांक nv_adma_qc_issue(काष्ठा ata_queued_cmd *qc);
अटल irqवापस_t nv_adma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);
अटल व्योम nv_adma_irq_clear(काष्ठा ata_port *ap);
अटल पूर्णांक nv_adma_port_start(काष्ठा ata_port *ap);
अटल व्योम nv_adma_port_stop(काष्ठा ata_port *ap);
#अगर_घोषित CONFIG_PM
अटल पूर्णांक nv_adma_port_suspend(काष्ठा ata_port *ap, pm_message_t mesg);
अटल पूर्णांक nv_adma_port_resume(काष्ठा ata_port *ap);
#पूर्ण_अगर
अटल व्योम nv_adma_मुक्तze(काष्ठा ata_port *ap);
अटल व्योम nv_adma_thaw(काष्ठा ata_port *ap);
अटल व्योम nv_adma_error_handler(काष्ठा ata_port *ap);
अटल व्योम nv_adma_host_stop(काष्ठा ata_host *host);
अटल व्योम nv_adma_post_पूर्णांकernal_cmd(काष्ठा ata_queued_cmd *qc);
अटल व्योम nv_adma_tf_पढ़ो(काष्ठा ata_port *ap, काष्ठा ata_taskfile *tf);

अटल व्योम nv_mcp55_thaw(काष्ठा ata_port *ap);
अटल व्योम nv_mcp55_मुक्तze(काष्ठा ata_port *ap);
अटल व्योम nv_swncq_error_handler(काष्ठा ata_port *ap);
अटल पूर्णांक nv_swncq_slave_config(काष्ठा scsi_device *sdev);
अटल पूर्णांक nv_swncq_port_start(काष्ठा ata_port *ap);
अटल क्रमागत ata_completion_errors nv_swncq_qc_prep(काष्ठा ata_queued_cmd *qc);
अटल व्योम nv_swncq_fill_sg(काष्ठा ata_queued_cmd *qc);
अटल अचिन्हित पूर्णांक nv_swncq_qc_issue(काष्ठा ata_queued_cmd *qc);
अटल व्योम nv_swncq_irq_clear(काष्ठा ata_port *ap, u16 fis);
अटल irqवापस_t nv_swncq_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);
#अगर_घोषित CONFIG_PM
अटल पूर्णांक nv_swncq_port_suspend(काष्ठा ata_port *ap, pm_message_t mesg);
अटल पूर्णांक nv_swncq_port_resume(काष्ठा ata_port *ap);
#पूर्ण_अगर

क्रमागत nv_host_type
अणु
	GENERIC,
	NFORCE2,
	NFORCE3 = NFORCE2,	/* NF2 == NF3 as far as sata_nv is concerned */
	CK804,
	ADMA,
	MCP5x,
	SWNCQ,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id nv_pci_tbl[] = अणु
	अणु PCI_VDEVICE(NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE2S_SATA), NFORCE2 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE3S_SATA), NFORCE3 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE3S_SATA2), NFORCE3 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_CK804_SATA), CK804 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_CK804_SATA2), CK804 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP04_SATA), CK804 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP04_SATA2), CK804 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP51_SATA), MCP5x पूर्ण,
	अणु PCI_VDEVICE(NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP51_SATA2), MCP5x पूर्ण,
	अणु PCI_VDEVICE(NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP55_SATA), MCP5x पूर्ण,
	अणु PCI_VDEVICE(NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP55_SATA2), MCP5x पूर्ण,
	अणु PCI_VDEVICE(NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP61_SATA), GENERIC पूर्ण,
	अणु PCI_VDEVICE(NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP61_SATA2), GENERIC पूर्ण,
	अणु PCI_VDEVICE(NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP61_SATA3), GENERIC पूर्ण,

	अणु पूर्ण /* terminate list */
पूर्ण;

अटल काष्ठा pci_driver nv_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= nv_pci_tbl,
	.probe			= nv_init_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= nv_pci_device_resume,
#पूर्ण_अगर
	.हटाओ			= ata_pci_हटाओ_one,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा nv_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा nv_adma_sht = अणु
	ATA_NCQ_SHT(DRV_NAME),
	.can_queue		= NV_ADMA_MAX_CPBS,
	.sg_tablesize		= NV_ADMA_SGTBL_TOTAL_LEN,
	.dma_boundary		= NV_ADMA_DMA_BOUNDARY,
	.slave_configure	= nv_adma_slave_config,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा nv_swncq_sht = अणु
	ATA_NCQ_SHT(DRV_NAME),
	.can_queue		= ATA_MAX_QUEUE - 1,
	.sg_tablesize		= LIBATA_MAX_PRD,
	.dma_boundary		= ATA_DMA_BOUNDARY,
	.slave_configure	= nv_swncq_slave_config,
पूर्ण;

/*
 * NV SATA controllers have various dअगरferent problems with hardreset
 * protocol depending on the specअगरic controller and device.
 *
 * GENERIC:
 *
 *  bko11195 reports that link करोesn't come online after hardreset on
 *  generic nv's and there have been several other similar reports on
 *  linux-ide.
 *
 *  bko12351#c23 reports that warmplug on MCP61 करोesn't work with
 *  softreset.
 *
 * NF2/3:
 *
 *  bko3352 reports nf2/3 controllers can't determine device signature
 *  reliably after hardreset.  The following thपढ़ो reports detection
 *  failure on cold boot with the standard debouncing timing.
 *
 *  http://thपढ़ो.gmane.org/gmane.linux.ide/34098
 *
 *  bko12176 reports that hardreset fails to bring up the link during
 *  boot on nf2.
 *
 * CK804:
 *
 *  For initial probing after boot and hot plugging, hardreset mostly
 *  works fine on CK804 but curiously, reprobing on the initial port
 *  by rescanning or rmmod/insmod fails to acquire the initial D2H Reg
 *  FIS in somewhat undeterministic way.
 *
 * SWNCQ:
 *
 *  bko12351 reports that when SWNCQ is enabled, क्रम hotplug to work,
 *  hardreset should be used and hardreset can't report proper
 *  signature, which suggests that mcp5x is बंदr to nf2 as दीर्घ as
 *  reset quirkiness is concerned.
 *
 *  bko12703 reports that boot probing fails क्रम पूर्णांकel SSD with
 *  hardreset.  Link fails to come online.  Softreset works fine.
 *
 * The failures are varied but the following patterns seem true क्रम
 * all flavors.
 *
 * - Softreset during boot always works.
 *
 * - Hardreset during boot someबार fails to bring up the link on
 *   certain comibnations and device signature acquisition is
 *   unreliable.
 *
 * - Hardreset is often necessary after hotplug.
 *
 * So, preferring softreset क्रम boot probing and error handling (as
 * hardreset might bring करोwn the link) but using hardreset क्रम
 * post-boot probing should work around the above issues in most
 * हालs.  Define nv_hardreset() which only kicks in क्रम post-boot
 * probing and use it क्रम all variants.
 */
अटल काष्ठा ata_port_operations nv_generic_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.lost_पूर्णांकerrupt		= ATA_OP_शून्य,
	.scr_पढ़ो		= nv_scr_पढ़ो,
	.scr_ग_लिखो		= nv_scr_ग_लिखो,
	.hardreset		= nv_hardreset,
पूर्ण;

अटल काष्ठा ata_port_operations nv_nf2_ops = अणु
	.inherits		= &nv_generic_ops,
	.मुक्तze			= nv_nf2_मुक्तze,
	.thaw			= nv_nf2_thaw,
पूर्ण;

अटल काष्ठा ata_port_operations nv_ck804_ops = अणु
	.inherits		= &nv_generic_ops,
	.मुक्तze			= nv_ck804_मुक्तze,
	.thaw			= nv_ck804_thaw,
	.host_stop		= nv_ck804_host_stop,
पूर्ण;

अटल काष्ठा ata_port_operations nv_adma_ops = अणु
	.inherits		= &nv_ck804_ops,

	.check_atapi_dma	= nv_adma_check_atapi_dma,
	.sff_tf_पढ़ो		= nv_adma_tf_पढ़ो,
	.qc_defer		= ata_std_qc_defer,
	.qc_prep		= nv_adma_qc_prep,
	.qc_issue		= nv_adma_qc_issue,
	.sff_irq_clear		= nv_adma_irq_clear,

	.मुक्तze			= nv_adma_मुक्तze,
	.thaw			= nv_adma_thaw,
	.error_handler		= nv_adma_error_handler,
	.post_पूर्णांकernal_cmd	= nv_adma_post_पूर्णांकernal_cmd,

	.port_start		= nv_adma_port_start,
	.port_stop		= nv_adma_port_stop,
#अगर_घोषित CONFIG_PM
	.port_suspend		= nv_adma_port_suspend,
	.port_resume		= nv_adma_port_resume,
#पूर्ण_अगर
	.host_stop		= nv_adma_host_stop,
पूर्ण;

अटल काष्ठा ata_port_operations nv_swncq_ops = अणु
	.inherits		= &nv_generic_ops,

	.qc_defer		= ata_std_qc_defer,
	.qc_prep		= nv_swncq_qc_prep,
	.qc_issue		= nv_swncq_qc_issue,

	.मुक्तze			= nv_mcp55_मुक्तze,
	.thaw			= nv_mcp55_thaw,
	.error_handler		= nv_swncq_error_handler,

#अगर_घोषित CONFIG_PM
	.port_suspend		= nv_swncq_port_suspend,
	.port_resume		= nv_swncq_port_resume,
#पूर्ण_अगर
	.port_start		= nv_swncq_port_start,
पूर्ण;

काष्ठा nv_pi_priv अणु
	irq_handler_t			irq_handler;
	काष्ठा scsi_host_ढाँचा	*sht;
पूर्ण;

#घोषणा NV_PI_PRIV(_irq_handler, _sht) \
	&(काष्ठा nv_pi_priv)अणु .irq_handler = _irq_handler, .sht = _sht पूर्ण

अटल स्थिर काष्ठा ata_port_info nv_port_info[] = अणु
	/* generic */
	अणु
		.flags		= ATA_FLAG_SATA,
		.pio_mask	= NV_PIO_MASK,
		.mwdma_mask	= NV_MWDMA_MASK,
		.udma_mask	= NV_UDMA_MASK,
		.port_ops	= &nv_generic_ops,
		.निजी_data	= NV_PI_PRIV(nv_generic_पूर्णांकerrupt, &nv_sht),
	पूर्ण,
	/* nक्रमce2/3 */
	अणु
		.flags		= ATA_FLAG_SATA,
		.pio_mask	= NV_PIO_MASK,
		.mwdma_mask	= NV_MWDMA_MASK,
		.udma_mask	= NV_UDMA_MASK,
		.port_ops	= &nv_nf2_ops,
		.निजी_data	= NV_PI_PRIV(nv_nf2_पूर्णांकerrupt, &nv_sht),
	पूर्ण,
	/* ck804 */
	अणु
		.flags		= ATA_FLAG_SATA,
		.pio_mask	= NV_PIO_MASK,
		.mwdma_mask	= NV_MWDMA_MASK,
		.udma_mask	= NV_UDMA_MASK,
		.port_ops	= &nv_ck804_ops,
		.निजी_data	= NV_PI_PRIV(nv_ck804_पूर्णांकerrupt, &nv_sht),
	पूर्ण,
	/* ADMA */
	अणु
		.flags		= ATA_FLAG_SATA | ATA_FLAG_NCQ,
		.pio_mask	= NV_PIO_MASK,
		.mwdma_mask	= NV_MWDMA_MASK,
		.udma_mask	= NV_UDMA_MASK,
		.port_ops	= &nv_adma_ops,
		.निजी_data	= NV_PI_PRIV(nv_adma_पूर्णांकerrupt, &nv_adma_sht),
	पूर्ण,
	/* MCP5x */
	अणु
		.flags		= ATA_FLAG_SATA,
		.pio_mask	= NV_PIO_MASK,
		.mwdma_mask	= NV_MWDMA_MASK,
		.udma_mask	= NV_UDMA_MASK,
		.port_ops	= &nv_generic_ops,
		.निजी_data	= NV_PI_PRIV(nv_generic_पूर्णांकerrupt, &nv_sht),
	पूर्ण,
	/* SWNCQ */
	अणु
		.flags	        = ATA_FLAG_SATA | ATA_FLAG_NCQ,
		.pio_mask	= NV_PIO_MASK,
		.mwdma_mask	= NV_MWDMA_MASK,
		.udma_mask	= NV_UDMA_MASK,
		.port_ops	= &nv_swncq_ops,
		.निजी_data	= NV_PI_PRIV(nv_swncq_पूर्णांकerrupt, &nv_swncq_sht),
	पूर्ण,
पूर्ण;

MODULE_AUTHOR("NVIDIA");
MODULE_DESCRIPTION("low-level driver for NVIDIA nForce SATA controller");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, nv_pci_tbl);
MODULE_VERSION(DRV_VERSION);

अटल bool adma_enabled;
अटल bool swncq_enabled = true;
अटल bool msi_enabled;

अटल व्योम nv_adma_रेजिस्टर_mode(काष्ठा ata_port *ap)
अणु
	काष्ठा nv_adma_port_priv *pp = ap->निजी_data;
	व्योम __iomem *mmio = pp->ctl_block;
	u16 पंचांगp, status;
	पूर्णांक count = 0;

	अगर (pp->flags & NV_ADMA_PORT_REGISTER_MODE)
		वापस;

	status = पढ़ोw(mmio + NV_ADMA_STAT);
	जबतक (!(status & NV_ADMA_STAT_IDLE) && count < 20) अणु
		ndelay(50);
		status = पढ़ोw(mmio + NV_ADMA_STAT);
		count++;
	पूर्ण
	अगर (count == 20)
		ata_port_warn(ap, "timeout waiting for ADMA IDLE, stat=0x%hx\n",
			      status);

	पंचांगp = पढ़ोw(mmio + NV_ADMA_CTL);
	ग_लिखोw(पंचांगp & ~NV_ADMA_CTL_GO, mmio + NV_ADMA_CTL);

	count = 0;
	status = पढ़ोw(mmio + NV_ADMA_STAT);
	जबतक (!(status & NV_ADMA_STAT_LEGACY) && count < 20) अणु
		ndelay(50);
		status = पढ़ोw(mmio + NV_ADMA_STAT);
		count++;
	पूर्ण
	अगर (count == 20)
		ata_port_warn(ap,
			      "timeout waiting for ADMA LEGACY, stat=0x%hx\n",
			      status);

	pp->flags |= NV_ADMA_PORT_REGISTER_MODE;
पूर्ण

अटल व्योम nv_adma_mode(काष्ठा ata_port *ap)
अणु
	काष्ठा nv_adma_port_priv *pp = ap->निजी_data;
	व्योम __iomem *mmio = pp->ctl_block;
	u16 पंचांगp, status;
	पूर्णांक count = 0;

	अगर (!(pp->flags & NV_ADMA_PORT_REGISTER_MODE))
		वापस;

	WARN_ON(pp->flags & NV_ADMA_ATAPI_SETUP_COMPLETE);

	पंचांगp = पढ़ोw(mmio + NV_ADMA_CTL);
	ग_लिखोw(पंचांगp | NV_ADMA_CTL_GO, mmio + NV_ADMA_CTL);

	status = पढ़ोw(mmio + NV_ADMA_STAT);
	जबतक (((status & NV_ADMA_STAT_LEGACY) ||
	      !(status & NV_ADMA_STAT_IDLE)) && count < 20) अणु
		ndelay(50);
		status = पढ़ोw(mmio + NV_ADMA_STAT);
		count++;
	पूर्ण
	अगर (count == 20)
		ata_port_warn(ap,
			"timeout waiting for ADMA LEGACY clear and IDLE, stat=0x%hx\n",
			status);

	pp->flags &= ~NV_ADMA_PORT_REGISTER_MODE;
पूर्ण

अटल पूर्णांक nv_adma_slave_config(काष्ठा scsi_device *sdev)
अणु
	काष्ठा ata_port *ap = ata_shost_to_port(sdev->host);
	काष्ठा nv_adma_port_priv *pp = ap->निजी_data;
	काष्ठा nv_adma_port_priv *port0, *port1;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अचिन्हित दीर्घ segment_boundary, flags;
	अचिन्हित लघु sg_tablesize;
	पूर्णांक rc;
	पूर्णांक adma_enable;
	u32 current_reg, new_reg, config_mask;

	rc = ata_scsi_slave_config(sdev);

	अगर (sdev->id >= ATA_MAX_DEVICES || sdev->channel || sdev->lun)
		/* Not a proper libata device, ignore */
		वापस rc;

	spin_lock_irqsave(ap->lock, flags);

	अगर (ap->link.device[sdev->id].class == ATA_DEV_ATAPI) अणु
		/*
		 * NVIDIA reports that ADMA mode करोes not support ATAPI commands.
		 * Thereक्रमe ATAPI commands are sent through the legacy पूर्णांकerface.
		 * However, the legacy पूर्णांकerface only supports 32-bit DMA.
		 * Restrict DMA parameters as required by the legacy पूर्णांकerface
		 * when an ATAPI device is connected.
		 */
		segment_boundary = ATA_DMA_BOUNDARY;
		/* Subtract 1 since an extra entry may be needed क्रम padding, see
		   libata-scsi.c */
		sg_tablesize = LIBATA_MAX_PRD - 1;

		/* Since the legacy DMA engine is in use, we need to disable ADMA
		   on the port. */
		adma_enable = 0;
		nv_adma_रेजिस्टर_mode(ap);
	पूर्ण अन्यथा अणु
		segment_boundary = NV_ADMA_DMA_BOUNDARY;
		sg_tablesize = NV_ADMA_SGTBL_TOTAL_LEN;
		adma_enable = 1;
	पूर्ण

	pci_पढ़ो_config_dword(pdev, NV_MCP_SATA_CFG_20, &current_reg);

	अगर (ap->port_no == 1)
		config_mask = NV_MCP_SATA_CFG_20_PORT1_EN |
			      NV_MCP_SATA_CFG_20_PORT1_PWB_EN;
	अन्यथा
		config_mask = NV_MCP_SATA_CFG_20_PORT0_EN |
			      NV_MCP_SATA_CFG_20_PORT0_PWB_EN;

	अगर (adma_enable) अणु
		new_reg = current_reg | config_mask;
		pp->flags &= ~NV_ADMA_ATAPI_SETUP_COMPLETE;
	पूर्ण अन्यथा अणु
		new_reg = current_reg & ~config_mask;
		pp->flags |= NV_ADMA_ATAPI_SETUP_COMPLETE;
	पूर्ण

	अगर (current_reg != new_reg)
		pci_ग_लिखो_config_dword(pdev, NV_MCP_SATA_CFG_20, new_reg);

	port0 = ap->host->ports[0]->निजी_data;
	port1 = ap->host->ports[1]->निजी_data;
	अगर ((port0->flags & NV_ADMA_ATAPI_SETUP_COMPLETE) ||
	    (port1->flags & NV_ADMA_ATAPI_SETUP_COMPLETE)) अणु
		/*
		 * We have to set the DMA mask to 32-bit अगर either port is in
		 * ATAPI mode, since they are on the same PCI device which is
		 * used क्रम DMA mapping.  If either SCSI device is not allocated
		 * yet, it's OK since that port will discover its correct
		 * setting when it करोes get allocated.
		 */
		rc = dma_set_mask(&pdev->dev, ATA_DMA_MASK);
	पूर्ण अन्यथा अणु
		rc = dma_set_mask(&pdev->dev, pp->adma_dma_mask);
	पूर्ण

	blk_queue_segment_boundary(sdev->request_queue, segment_boundary);
	blk_queue_max_segments(sdev->request_queue, sg_tablesize);
	ata_port_info(ap,
		      "DMA mask 0x%llX, segment boundary 0x%lX, hw segs %hu\n",
		      (अचिन्हित दीर्घ दीर्घ)*ap->host->dev->dma_mask,
		      segment_boundary, sg_tablesize);

	spin_unlock_irqrestore(ap->lock, flags);

	वापस rc;
पूर्ण

अटल पूर्णांक nv_adma_check_atapi_dma(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा nv_adma_port_priv *pp = qc->ap->निजी_data;
	वापस !(pp->flags & NV_ADMA_ATAPI_SETUP_COMPLETE);
पूर्ण

अटल व्योम nv_adma_tf_पढ़ो(काष्ठा ata_port *ap, काष्ठा ata_taskfile *tf)
अणु
	/* Other than when पूर्णांकernal or pass-through commands are executed,
	   the only समय this function will be called in ADMA mode will be
	   अगर a command fails. In the failure हाल we करोn't care about going
	   पूर्णांकo रेजिस्टर mode with ADMA commands pending, as the commands will
	   all लघुly be पातed anyway. We assume that NCQ commands are not
	   issued via passthrough, which is the only way that चयनing पूर्णांकo
	   ADMA mode could पात outstanding commands. */
	nv_adma_रेजिस्टर_mode(ap);

	ata_sff_tf_पढ़ो(ap, tf);
पूर्ण

अटल अचिन्हित पूर्णांक nv_adma_tf_to_cpb(काष्ठा ata_taskfile *tf, __le16 *cpb)
अणु
	अचिन्हित पूर्णांक idx = 0;

	अगर (tf->flags & ATA_TFLAG_ISADDR) अणु
		अगर (tf->flags & ATA_TFLAG_LBA48) अणु
			cpb[idx++] = cpu_to_le16((ATA_REG_ERR   << 8) | tf->hob_feature | WNB);
			cpb[idx++] = cpu_to_le16((ATA_REG_NSECT << 8) | tf->hob_nsect);
			cpb[idx++] = cpu_to_le16((ATA_REG_LBAL  << 8) | tf->hob_lbal);
			cpb[idx++] = cpu_to_le16((ATA_REG_LBAM  << 8) | tf->hob_lbam);
			cpb[idx++] = cpu_to_le16((ATA_REG_LBAH  << 8) | tf->hob_lbah);
			cpb[idx++] = cpu_to_le16((ATA_REG_ERR    << 8) | tf->feature);
		पूर्ण अन्यथा
			cpb[idx++] = cpu_to_le16((ATA_REG_ERR    << 8) | tf->feature | WNB);

		cpb[idx++] = cpu_to_le16((ATA_REG_NSECT  << 8) | tf->nsect);
		cpb[idx++] = cpu_to_le16((ATA_REG_LBAL   << 8) | tf->lbal);
		cpb[idx++] = cpu_to_le16((ATA_REG_LBAM   << 8) | tf->lbam);
		cpb[idx++] = cpu_to_le16((ATA_REG_LBAH   << 8) | tf->lbah);
	पूर्ण

	अगर (tf->flags & ATA_TFLAG_DEVICE)
		cpb[idx++] = cpu_to_le16((ATA_REG_DEVICE << 8) | tf->device);

	cpb[idx++] = cpu_to_le16((ATA_REG_CMD    << 8) | tf->command | CMDEND);

	जबतक (idx < 12)
		cpb[idx++] = cpu_to_le16(IGN);

	वापस idx;
पूर्ण

अटल पूर्णांक nv_adma_check_cpb(काष्ठा ata_port *ap, पूर्णांक cpb_num, पूर्णांक क्रमce_err)
अणु
	काष्ठा nv_adma_port_priv *pp = ap->निजी_data;
	u8 flags = pp->cpb[cpb_num].resp_flags;

	VPRINTK("CPB %d, flags=0x%x\n", cpb_num, flags);

	अगर (unlikely((क्रमce_err ||
		     flags & (NV_CPB_RESP_ATA_ERR |
			      NV_CPB_RESP_CMD_ERR |
			      NV_CPB_RESP_CPB_ERR)))) अणु
		काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
		पूर्णांक मुक्तze = 0;

		ata_ehi_clear_desc(ehi);
		__ata_ehi_push_desc(ehi, "CPB resp_flags 0x%x: ", flags);
		अगर (flags & NV_CPB_RESP_ATA_ERR) अणु
			ata_ehi_push_desc(ehi, "ATA error");
			ehi->err_mask |= AC_ERR_DEV;
		पूर्ण अन्यथा अगर (flags & NV_CPB_RESP_CMD_ERR) अणु
			ata_ehi_push_desc(ehi, "CMD error");
			ehi->err_mask |= AC_ERR_DEV;
		पूर्ण अन्यथा अगर (flags & NV_CPB_RESP_CPB_ERR) अणु
			ata_ehi_push_desc(ehi, "CPB error");
			ehi->err_mask |= AC_ERR_SYSTEM;
			मुक्तze = 1;
		पूर्ण अन्यथा अणु
			/* notअगरier error, but no error in CPB flags? */
			ata_ehi_push_desc(ehi, "unknown");
			ehi->err_mask |= AC_ERR_OTHER;
			मुक्तze = 1;
		पूर्ण
		/* Kill all commands. EH will determine what actually failed. */
		अगर (मुक्तze)
			ata_port_मुक्तze(ap);
		अन्यथा
			ata_port_पात(ap);
		वापस -1;
	पूर्ण

	अगर (likely(flags & NV_CPB_RESP_DONE))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक nv_host_पूर्णांकr(काष्ठा ata_port *ap, u8 irq_stat)
अणु
	काष्ठा ata_queued_cmd *qc = ata_qc_from_tag(ap, ap->link.active_tag);

	/* मुक्तze अगर hotplugged */
	अगर (unlikely(irq_stat & (NV_INT_ADDED | NV_INT_REMOVED))) अणु
		ata_port_मुक्तze(ap);
		वापस 1;
	पूर्ण

	/* bail out अगर not our पूर्णांकerrupt */
	अगर (!(irq_stat & NV_INT_DEV))
		वापस 0;

	/* DEV पूर्णांकerrupt w/ no active qc? */
	अगर (unlikely(!qc || (qc->tf.flags & ATA_TFLAG_POLLING))) अणु
		ata_sff_check_status(ap);
		वापस 1;
	पूर्ण

	/* handle पूर्णांकerrupt */
	वापस ata_bmdma_port_पूर्णांकr(ap, qc);
पूर्ण

अटल irqवापस_t nv_adma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	पूर्णांक i, handled = 0;
	u32 notअगरier_clears[2];

	spin_lock(&host->lock);

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		काष्ठा nv_adma_port_priv *pp = ap->निजी_data;
		व्योम __iomem *mmio = pp->ctl_block;
		u16 status;
		u32 gen_ctl;
		u32 notअगरier, notअगरier_error;

		notअगरier_clears[i] = 0;

		/* अगर ADMA is disabled, use standard ata पूर्णांकerrupt handler */
		अगर (pp->flags & NV_ADMA_ATAPI_SETUP_COMPLETE) अणु
			u8 irq_stat = पढ़ोb(host->iomap[NV_MMIO_BAR] + NV_INT_STATUS_CK804)
				>> (NV_INT_PORT_SHIFT * i);
			handled += nv_host_पूर्णांकr(ap, irq_stat);
			जारी;
		पूर्ण

		/* अगर in ATA रेजिस्टर mode, check क्रम standard पूर्णांकerrupts */
		अगर (pp->flags & NV_ADMA_PORT_REGISTER_MODE) अणु
			u8 irq_stat = पढ़ोb(host->iomap[NV_MMIO_BAR] + NV_INT_STATUS_CK804)
				>> (NV_INT_PORT_SHIFT * i);
			अगर (ata_tag_valid(ap->link.active_tag))
				/** NV_INT_DEV indication seems unreliable
				    at बार at least in ADMA mode. Force it
				    on always when a command is active, to
				    prevent losing पूर्णांकerrupts. */
				irq_stat |= NV_INT_DEV;
			handled += nv_host_पूर्णांकr(ap, irq_stat);
		पूर्ण

		notअगरier = पढ़ोl(mmio + NV_ADMA_NOTIFIER);
		notअगरier_error = पढ़ोl(mmio + NV_ADMA_NOTIFIER_ERROR);
		notअगरier_clears[i] = notअगरier | notअगरier_error;

		gen_ctl = पढ़ोl(pp->gen_block + NV_ADMA_GEN_CTL);

		अगर (!NV_ADMA_CHECK_INTR(gen_ctl, ap->port_no) && !notअगरier &&
		    !notअगरier_error)
			/* Nothing to करो */
			जारी;

		status = पढ़ोw(mmio + NV_ADMA_STAT);

		/*
		 * Clear status. Ensure the controller sees the
		 * clearing beक्रमe we start looking at any of the CPB
		 * statuses, so that any CPB completions after this
		 * poपूर्णांक in the handler will उठाओ another पूर्णांकerrupt.
		 */
		ग_लिखोw(status, mmio + NV_ADMA_STAT);
		पढ़ोw(mmio + NV_ADMA_STAT); /* flush posted ग_लिखो */
		rmb();

		handled++; /* irq handled अगर we got here */

		/* मुक्तze अगर hotplugged or controller error */
		अगर (unlikely(status & (NV_ADMA_STAT_HOTPLUG |
				       NV_ADMA_STAT_HOTUNPLUG |
				       NV_ADMA_STAT_TIMEOUT |
				       NV_ADMA_STAT_SERROR))) अणु
			काष्ठा ata_eh_info *ehi = &ap->link.eh_info;

			ata_ehi_clear_desc(ehi);
			__ata_ehi_push_desc(ehi, "ADMA status 0x%08x: ", status);
			अगर (status & NV_ADMA_STAT_TIMEOUT) अणु
				ehi->err_mask |= AC_ERR_SYSTEM;
				ata_ehi_push_desc(ehi, "timeout");
			पूर्ण अन्यथा अगर (status & NV_ADMA_STAT_HOTPLUG) अणु
				ata_ehi_hotplugged(ehi);
				ata_ehi_push_desc(ehi, "hotplug");
			पूर्ण अन्यथा अगर (status & NV_ADMA_STAT_HOTUNPLUG) अणु
				ata_ehi_hotplugged(ehi);
				ata_ehi_push_desc(ehi, "hot unplug");
			पूर्ण अन्यथा अगर (status & NV_ADMA_STAT_SERROR) अणु
				/* let EH analyze SError and figure out cause */
				ata_ehi_push_desc(ehi, "SError");
			पूर्ण अन्यथा
				ata_ehi_push_desc(ehi, "unknown");
			ata_port_मुक्तze(ap);
			जारी;
		पूर्ण

		अगर (status & (NV_ADMA_STAT_DONE |
			      NV_ADMA_STAT_CPBERR |
			      NV_ADMA_STAT_CMD_COMPLETE)) अणु
			u32 check_commands = notअगरier_clears[i];
			u32 करोne_mask = 0;
			पूर्णांक pos, rc;

			अगर (status & NV_ADMA_STAT_CPBERR) अणु
				/* check all active commands */
				अगर (ata_tag_valid(ap->link.active_tag))
					check_commands = 1 <<
						ap->link.active_tag;
				अन्यथा
					check_commands = ap->link.sactive;
			पूर्ण

			/* check CPBs क्रम completed commands */
			जबतक ((pos = ffs(check_commands))) अणु
				pos--;
				rc = nv_adma_check_cpb(ap, pos,
						notअगरier_error & (1 << pos));
				अगर (rc > 0)
					करोne_mask |= 1 << pos;
				अन्यथा अगर (unlikely(rc < 0))
					check_commands = 0;
				check_commands &= ~(1 << pos);
			पूर्ण
			ata_qc_complete_multiple(ap, ata_qc_get_active(ap) ^ करोne_mask);
		पूर्ण
	पूर्ण

	अगर (notअगरier_clears[0] || notअगरier_clears[1]) अणु
		/* Note: Both notअगरier clear रेजिस्टरs must be written
		   अगर either is set, even अगर one is zero, according to NVIDIA. */
		काष्ठा nv_adma_port_priv *pp = host->ports[0]->निजी_data;
		ग_लिखोl(notअगरier_clears[0], pp->notअगरier_clear_block);
		pp = host->ports[1]->निजी_data;
		ग_लिखोl(notअगरier_clears[1], pp->notअगरier_clear_block);
	पूर्ण

	spin_unlock(&host->lock);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम nv_adma_मुक्तze(काष्ठा ata_port *ap)
अणु
	काष्ठा nv_adma_port_priv *pp = ap->निजी_data;
	व्योम __iomem *mmio = pp->ctl_block;
	u16 पंचांगp;

	nv_ck804_मुक्तze(ap);

	अगर (pp->flags & NV_ADMA_ATAPI_SETUP_COMPLETE)
		वापस;

	/* clear any outstanding CK804 notअगरications */
	ग_लिखोb(NV_INT_ALL << (ap->port_no * NV_INT_PORT_SHIFT),
		ap->host->iomap[NV_MMIO_BAR] + NV_INT_STATUS_CK804);

	/* Disable पूर्णांकerrupt */
	पंचांगp = पढ़ोw(mmio + NV_ADMA_CTL);
	ग_लिखोw(पंचांगp & ~(NV_ADMA_CTL_AIEN | NV_ADMA_CTL_HOTPLUG_IEN),
		mmio + NV_ADMA_CTL);
	पढ़ोw(mmio + NV_ADMA_CTL);	/* flush posted ग_लिखो */
पूर्ण

अटल व्योम nv_adma_thaw(काष्ठा ata_port *ap)
अणु
	काष्ठा nv_adma_port_priv *pp = ap->निजी_data;
	व्योम __iomem *mmio = pp->ctl_block;
	u16 पंचांगp;

	nv_ck804_thaw(ap);

	अगर (pp->flags & NV_ADMA_ATAPI_SETUP_COMPLETE)
		वापस;

	/* Enable पूर्णांकerrupt */
	पंचांगp = पढ़ोw(mmio + NV_ADMA_CTL);
	ग_लिखोw(पंचांगp | (NV_ADMA_CTL_AIEN | NV_ADMA_CTL_HOTPLUG_IEN),
		mmio + NV_ADMA_CTL);
	पढ़ोw(mmio + NV_ADMA_CTL);	/* flush posted ग_लिखो */
पूर्ण

अटल व्योम nv_adma_irq_clear(काष्ठा ata_port *ap)
अणु
	काष्ठा nv_adma_port_priv *pp = ap->निजी_data;
	व्योम __iomem *mmio = pp->ctl_block;
	u32 notअगरier_clears[2];

	अगर (pp->flags & NV_ADMA_ATAPI_SETUP_COMPLETE) अणु
		ata_bmdma_irq_clear(ap);
		वापस;
	पूर्ण

	/* clear any outstanding CK804 notअगरications */
	ग_लिखोb(NV_INT_ALL << (ap->port_no * NV_INT_PORT_SHIFT),
		ap->host->iomap[NV_MMIO_BAR] + NV_INT_STATUS_CK804);

	/* clear ADMA status */
	ग_लिखोw(0xffff, mmio + NV_ADMA_STAT);

	/* clear notअगरiers - note both ports need to be written with
	   something even though we are only clearing on one */
	अगर (ap->port_no == 0) अणु
		notअगरier_clears[0] = 0xFFFFFFFF;
		notअगरier_clears[1] = 0;
	पूर्ण अन्यथा अणु
		notअगरier_clears[0] = 0;
		notअगरier_clears[1] = 0xFFFFFFFF;
	पूर्ण
	pp = ap->host->ports[0]->निजी_data;
	ग_लिखोl(notअगरier_clears[0], pp->notअगरier_clear_block);
	pp = ap->host->ports[1]->निजी_data;
	ग_लिखोl(notअगरier_clears[1], pp->notअगरier_clear_block);
पूर्ण

अटल व्योम nv_adma_post_पूर्णांकernal_cmd(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा nv_adma_port_priv *pp = qc->ap->निजी_data;

	अगर (pp->flags & NV_ADMA_PORT_REGISTER_MODE)
		ata_bmdma_post_पूर्णांकernal_cmd(qc);
पूर्ण

अटल पूर्णांक nv_adma_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा device *dev = ap->host->dev;
	काष्ठा nv_adma_port_priv *pp;
	पूर्णांक rc;
	व्योम *mem;
	dma_addr_t mem_dma;
	व्योम __iomem *mmio;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	u16 पंचांगp;

	VPRINTK("ENTER\n");

	/*
	 * Ensure DMA mask is set to 32-bit beक्रमe allocating legacy PRD and
	 * pad buffers.
	 */
	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (rc)
		वापस rc;

	/* we might fallback to bmdma, allocate bmdma resources */
	rc = ata_bmdma_port_start(ap);
	अगर (rc)
		वापस rc;

	pp = devm_kzalloc(dev, माप(*pp), GFP_KERNEL);
	अगर (!pp)
		वापस -ENOMEM;

	mmio = ap->host->iomap[NV_MMIO_BAR] + NV_ADMA_PORT +
	       ap->port_no * NV_ADMA_PORT_SIZE;
	pp->ctl_block = mmio;
	pp->gen_block = ap->host->iomap[NV_MMIO_BAR] + NV_ADMA_GEN;
	pp->notअगरier_clear_block = pp->gen_block +
	       NV_ADMA_NOTIFIER_CLEAR + (4 * ap->port_no);

	/*
	 * Now that the legacy PRD and padding buffer are allocated we can
	 * उठाओ the DMA mask to allocate the CPB/APRD table.
	 */
	dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));

	pp->adma_dma_mask = *dev->dma_mask;

	mem = dmam_alloc_coherent(dev, NV_ADMA_PORT_PRIV_DMA_SZ,
				  &mem_dma, GFP_KERNEL);
	अगर (!mem)
		वापस -ENOMEM;

	/*
	 * First item in chunk of DMA memory:
	 * 128-byte command parameter block (CPB)
	 * one क्रम each command tag
	 */
	pp->cpb     = mem;
	pp->cpb_dma = mem_dma;

	ग_लिखोl(mem_dma & 0xFFFFFFFF, 	mmio + NV_ADMA_CPB_BASE_LOW);
	ग_लिखोl((mem_dma >> 16) >> 16,	mmio + NV_ADMA_CPB_BASE_HIGH);

	mem     += NV_ADMA_MAX_CPBS * NV_ADMA_CPB_SZ;
	mem_dma += NV_ADMA_MAX_CPBS * NV_ADMA_CPB_SZ;

	/*
	 * Second item: block of ADMA_SGTBL_LEN s/g entries
	 */
	pp->aprd = mem;
	pp->aprd_dma = mem_dma;

	ap->निजी_data = pp;

	/* clear any outstanding पूर्णांकerrupt conditions */
	ग_लिखोw(0xffff, mmio + NV_ADMA_STAT);

	/* initialize port variables */
	pp->flags = NV_ADMA_PORT_REGISTER_MODE;

	/* clear CPB fetch count */
	ग_लिखोw(0, mmio + NV_ADMA_CPB_COUNT);

	/* clear GO क्रम रेजिस्टर mode, enable पूर्णांकerrupt */
	पंचांगp = पढ़ोw(mmio + NV_ADMA_CTL);
	ग_लिखोw((पंचांगp & ~NV_ADMA_CTL_GO) | NV_ADMA_CTL_AIEN |
		NV_ADMA_CTL_HOTPLUG_IEN, mmio + NV_ADMA_CTL);

	पंचांगp = पढ़ोw(mmio + NV_ADMA_CTL);
	ग_लिखोw(पंचांगp | NV_ADMA_CTL_CHANNEL_RESET, mmio + NV_ADMA_CTL);
	पढ़ोw(mmio + NV_ADMA_CTL);	/* flush posted ग_लिखो */
	udelay(1);
	ग_लिखोw(पंचांगp & ~NV_ADMA_CTL_CHANNEL_RESET, mmio + NV_ADMA_CTL);
	पढ़ोw(mmio + NV_ADMA_CTL);	/* flush posted ग_लिखो */

	वापस 0;
पूर्ण

अटल व्योम nv_adma_port_stop(काष्ठा ata_port *ap)
अणु
	काष्ठा nv_adma_port_priv *pp = ap->निजी_data;
	व्योम __iomem *mmio = pp->ctl_block;

	VPRINTK("ENTER\n");
	ग_लिखोw(0, mmio + NV_ADMA_CTL);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक nv_adma_port_suspend(काष्ठा ata_port *ap, pm_message_t mesg)
अणु
	काष्ठा nv_adma_port_priv *pp = ap->निजी_data;
	व्योम __iomem *mmio = pp->ctl_block;

	/* Go to रेजिस्टर mode - clears GO */
	nv_adma_रेजिस्टर_mode(ap);

	/* clear CPB fetch count */
	ग_लिखोw(0, mmio + NV_ADMA_CPB_COUNT);

	/* disable पूर्णांकerrupt, shut करोwn port */
	ग_लिखोw(0, mmio + NV_ADMA_CTL);

	वापस 0;
पूर्ण

अटल पूर्णांक nv_adma_port_resume(काष्ठा ata_port *ap)
अणु
	काष्ठा nv_adma_port_priv *pp = ap->निजी_data;
	व्योम __iomem *mmio = pp->ctl_block;
	u16 पंचांगp;

	/* set CPB block location */
	ग_लिखोl(pp->cpb_dma & 0xFFFFFFFF, 	mmio + NV_ADMA_CPB_BASE_LOW);
	ग_लिखोl((pp->cpb_dma >> 16) >> 16,	mmio + NV_ADMA_CPB_BASE_HIGH);

	/* clear any outstanding पूर्णांकerrupt conditions */
	ग_लिखोw(0xffff, mmio + NV_ADMA_STAT);

	/* initialize port variables */
	pp->flags |= NV_ADMA_PORT_REGISTER_MODE;

	/* clear CPB fetch count */
	ग_लिखोw(0, mmio + NV_ADMA_CPB_COUNT);

	/* clear GO क्रम रेजिस्टर mode, enable पूर्णांकerrupt */
	पंचांगp = पढ़ोw(mmio + NV_ADMA_CTL);
	ग_लिखोw((पंचांगp & ~NV_ADMA_CTL_GO) | NV_ADMA_CTL_AIEN |
		NV_ADMA_CTL_HOTPLUG_IEN, mmio + NV_ADMA_CTL);

	पंचांगp = पढ़ोw(mmio + NV_ADMA_CTL);
	ग_लिखोw(पंचांगp | NV_ADMA_CTL_CHANNEL_RESET, mmio + NV_ADMA_CTL);
	पढ़ोw(mmio + NV_ADMA_CTL);	/* flush posted ग_लिखो */
	udelay(1);
	ग_लिखोw(पंचांगp & ~NV_ADMA_CTL_CHANNEL_RESET, mmio + NV_ADMA_CTL);
	पढ़ोw(mmio + NV_ADMA_CTL);	/* flush posted ग_लिखो */

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम nv_adma_setup_port(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *mmio = ap->host->iomap[NV_MMIO_BAR];
	काष्ठा ata_ioports *ioport = &ap->ioaddr;

	VPRINTK("ENTER\n");

	mmio += NV_ADMA_PORT + ap->port_no * NV_ADMA_PORT_SIZE;

	ioport->cmd_addr	= mmio;
	ioport->data_addr	= mmio + (ATA_REG_DATA * 4);
	ioport->error_addr	=
	ioport->feature_addr	= mmio + (ATA_REG_ERR * 4);
	ioport->nsect_addr	= mmio + (ATA_REG_NSECT * 4);
	ioport->lbal_addr	= mmio + (ATA_REG_LBAL * 4);
	ioport->lbam_addr	= mmio + (ATA_REG_LBAM * 4);
	ioport->lbah_addr	= mmio + (ATA_REG_LBAH * 4);
	ioport->device_addr	= mmio + (ATA_REG_DEVICE * 4);
	ioport->status_addr	=
	ioport->command_addr	= mmio + (ATA_REG_STATUS * 4);
	ioport->altstatus_addr	=
	ioport->ctl_addr	= mmio + 0x20;
पूर्ण

अटल पूर्णांक nv_adma_host_init(काष्ठा ata_host *host)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(host->dev);
	अचिन्हित पूर्णांक i;
	u32 पंचांगp32;

	VPRINTK("ENTER\n");

	/* enable ADMA on the ports */
	pci_पढ़ो_config_dword(pdev, NV_MCP_SATA_CFG_20, &पंचांगp32);
	पंचांगp32 |= NV_MCP_SATA_CFG_20_PORT0_EN |
		 NV_MCP_SATA_CFG_20_PORT0_PWB_EN |
		 NV_MCP_SATA_CFG_20_PORT1_EN |
		 NV_MCP_SATA_CFG_20_PORT1_PWB_EN;

	pci_ग_लिखो_config_dword(pdev, NV_MCP_SATA_CFG_20, पंचांगp32);

	क्रम (i = 0; i < host->n_ports; i++)
		nv_adma_setup_port(host->ports[i]);

	वापस 0;
पूर्ण

अटल व्योम nv_adma_fill_aprd(काष्ठा ata_queued_cmd *qc,
			      काष्ठा scatterlist *sg,
			      पूर्णांक idx,
			      काष्ठा nv_adma_prd *aprd)
अणु
	u8 flags = 0;
	अगर (qc->tf.flags & ATA_TFLAG_WRITE)
		flags |= NV_APRD_WRITE;
	अगर (idx == qc->n_elem - 1)
		flags |= NV_APRD_END;
	अन्यथा अगर (idx != 4)
		flags |= NV_APRD_CONT;

	aprd->addr  = cpu_to_le64(((u64)sg_dma_address(sg)));
	aprd->len   = cpu_to_le32(((u32)sg_dma_len(sg))); /* len in bytes */
	aprd->flags = flags;
	aprd->packet_len = 0;
पूर्ण

अटल व्योम nv_adma_fill_sg(काष्ठा ata_queued_cmd *qc, काष्ठा nv_adma_cpb *cpb)
अणु
	काष्ठा nv_adma_port_priv *pp = qc->ap->निजी_data;
	काष्ठा nv_adma_prd *aprd;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक si;

	VPRINTK("ENTER\n");

	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		aprd = (si < 5) ? &cpb->aprd[si] :
			&pp->aprd[NV_ADMA_SGTBL_LEN * qc->hw_tag + (si-5)];
		nv_adma_fill_aprd(qc, sg, si, aprd);
	पूर्ण
	अगर (si > 5)
		cpb->next_aprd = cpu_to_le64(((u64)(pp->aprd_dma + NV_ADMA_SGTBL_SZ * qc->hw_tag)));
	अन्यथा
		cpb->next_aprd = cpu_to_le64(0);
पूर्ण

अटल पूर्णांक nv_adma_use_reg_mode(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा nv_adma_port_priv *pp = qc->ap->निजी_data;

	/* ADMA engine can only be used क्रम non-ATAPI DMA commands,
	   or पूर्णांकerrupt-driven no-data commands. */
	अगर ((pp->flags & NV_ADMA_ATAPI_SETUP_COMPLETE) ||
	   (qc->tf.flags & ATA_TFLAG_POLLING))
		वापस 1;

	अगर ((qc->flags & ATA_QCFLAG_DMAMAP) ||
	   (qc->tf.protocol == ATA_PROT_NODATA))
		वापस 0;

	वापस 1;
पूर्ण

अटल क्रमागत ata_completion_errors nv_adma_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा nv_adma_port_priv *pp = qc->ap->निजी_data;
	काष्ठा nv_adma_cpb *cpb = &pp->cpb[qc->hw_tag];
	u8 ctl_flags = NV_CPB_CTL_CPB_VALID |
		       NV_CPB_CTL_IEN;

	अगर (nv_adma_use_reg_mode(qc)) अणु
		BUG_ON(!(pp->flags & NV_ADMA_ATAPI_SETUP_COMPLETE) &&
			(qc->flags & ATA_QCFLAG_DMAMAP));
		nv_adma_रेजिस्टर_mode(qc->ap);
		ata_bmdma_qc_prep(qc);
		वापस AC_ERR_OK;
	पूर्ण

	cpb->resp_flags = NV_CPB_RESP_DONE;
	wmb();
	cpb->ctl_flags = 0;
	wmb();

	cpb->len		= 3;
	cpb->tag		= qc->hw_tag;
	cpb->next_cpb_idx	= 0;

	/* turn on NCQ flags क्रम NCQ commands */
	अगर (qc->tf.protocol == ATA_PROT_NCQ)
		ctl_flags |= NV_CPB_CTL_QUEUE | NV_CPB_CTL_FPDMA;

	VPRINTK("qc->flags = 0x%lx\n", qc->flags);

	nv_adma_tf_to_cpb(&qc->tf, cpb->tf);

	अगर (qc->flags & ATA_QCFLAG_DMAMAP) अणु
		nv_adma_fill_sg(qc, cpb);
		ctl_flags |= NV_CPB_CTL_APRD_VALID;
	पूर्ण अन्यथा
		स_रखो(&cpb->aprd[0], 0, माप(काष्ठा nv_adma_prd) * 5);

	/* Be paranoid and करोn't let the device see NV_CPB_CTL_CPB_VALID
	   until we are finished filling in all of the contents */
	wmb();
	cpb->ctl_flags = ctl_flags;
	wmb();
	cpb->resp_flags = 0;

	वापस AC_ERR_OK;
पूर्ण

अटल अचिन्हित पूर्णांक nv_adma_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा nv_adma_port_priv *pp = qc->ap->निजी_data;
	व्योम __iomem *mmio = pp->ctl_block;
	पूर्णांक curr_ncq = (qc->tf.protocol == ATA_PROT_NCQ);

	VPRINTK("ENTER\n");

	/* We can't handle result taskfile with NCQ commands, since
	   retrieving the taskfile चयनes us out of ADMA mode and would पात
	   existing commands. */
	अगर (unlikely(qc->tf.protocol == ATA_PROT_NCQ &&
		     (qc->flags & ATA_QCFLAG_RESULT_TF))) अणु
		ata_dev_err(qc->dev, "NCQ w/ RESULT_TF not allowed\n");
		वापस AC_ERR_SYSTEM;
	पूर्ण

	अगर (nv_adma_use_reg_mode(qc)) अणु
		/* use ATA रेजिस्टर mode */
		VPRINTK("using ATA register mode: 0x%lx\n", qc->flags);
		BUG_ON(!(pp->flags & NV_ADMA_ATAPI_SETUP_COMPLETE) &&
			(qc->flags & ATA_QCFLAG_DMAMAP));
		nv_adma_रेजिस्टर_mode(qc->ap);
		वापस ata_bmdma_qc_issue(qc);
	पूर्ण अन्यथा
		nv_adma_mode(qc->ap);

	/* ग_लिखो append रेजिस्टर, command tag in lower 8 bits
	   and (number of cpbs to append -1) in top 8 bits */
	wmb();

	अगर (curr_ncq != pp->last_issue_ncq) अणु
		/* Seems to need some delay beक्रमe चयनing between NCQ and
		   non-NCQ commands, अन्यथा we get command समयouts and such. */
		udelay(20);
		pp->last_issue_ncq = curr_ncq;
	पूर्ण

	ग_लिखोw(qc->hw_tag, mmio + NV_ADMA_APPEND);

	DPRINTK("Issued tag %u\n", qc->hw_tag);

	वापस 0;
पूर्ण

अटल irqवापस_t nv_generic_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक handled = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		काष्ठा ata_queued_cmd *qc;

		qc = ata_qc_from_tag(ap, ap->link.active_tag);
		अगर (qc && (!(qc->tf.flags & ATA_TFLAG_POLLING))) अणु
			handled += ata_bmdma_port_पूर्णांकr(ap, qc);
		पूर्ण अन्यथा अणु
			/*
			 * No request pending?  Clear पूर्णांकerrupt status
			 * anyway, in हाल there's one pending.
			 */
			ap->ops->sff_check_status(ap);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&host->lock, flags);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल irqवापस_t nv_करो_पूर्णांकerrupt(काष्ठा ata_host *host, u8 irq_stat)
अणु
	पूर्णांक i, handled = 0;

	क्रम (i = 0; i < host->n_ports; i++) अणु
		handled += nv_host_पूर्णांकr(host->ports[i], irq_stat);
		irq_stat >>= NV_INT_PORT_SHIFT;
	पूर्ण

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल irqवापस_t nv_nf2_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	u8 irq_stat;
	irqवापस_t ret;

	spin_lock(&host->lock);
	irq_stat = ioपढ़ो8(host->ports[0]->ioaddr.scr_addr + NV_INT_STATUS);
	ret = nv_करो_पूर्णांकerrupt(host, irq_stat);
	spin_unlock(&host->lock);

	वापस ret;
पूर्ण

अटल irqवापस_t nv_ck804_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	u8 irq_stat;
	irqवापस_t ret;

	spin_lock(&host->lock);
	irq_stat = पढ़ोb(host->iomap[NV_MMIO_BAR] + NV_INT_STATUS_CK804);
	ret = nv_करो_पूर्णांकerrupt(host, irq_stat);
	spin_unlock(&host->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक nv_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 *val)
अणु
	अगर (sc_reg > SCR_CONTROL)
		वापस -EINVAL;

	*val = ioपढ़ो32(link->ap->ioaddr.scr_addr + (sc_reg * 4));
	वापस 0;
पूर्ण

अटल पूर्णांक nv_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 val)
अणु
	अगर (sc_reg > SCR_CONTROL)
		वापस -EINVAL;

	ioग_लिखो32(val, link->ap->ioaddr.scr_addr + (sc_reg * 4));
	वापस 0;
पूर्ण

अटल पूर्णांक nv_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_eh_context *ehc = &link->eh_context;

	/* Do hardreset अगरf it's post-boot probing, please पढ़ो the
	 * comment above port ops क्रम details.
	 */
	अगर (!(link->ap->pflags & ATA_PFLAG_LOADING) &&
	    !ata_dev_enabled(link->device))
		sata_link_hardreset(link, sata_deb_timing_hotplug, deadline,
				    शून्य, शून्य);
	अन्यथा अणु
		स्थिर अचिन्हित दीर्घ *timing = sata_ehc_deb_timing(ehc);
		पूर्णांक rc;

		अगर (!(ehc->i.flags & ATA_EHI_QUIET))
			ata_link_info(link,
				      "nv: skipping hardreset on occupied port\n");

		/* make sure the link is online */
		rc = sata_link_resume(link, timing, deadline);
		/* whine about phy resume failure but proceed */
		अगर (rc && rc != -EOPNOTSUPP)
			ata_link_warn(link, "failed to resume link (errno=%d)\n",
				      rc);
	पूर्ण

	/* device signature acquisition is unreliable */
	वापस -EAGAIN;
पूर्ण

अटल व्योम nv_nf2_मुक्तze(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *scr_addr = ap->host->ports[0]->ioaddr.scr_addr;
	पूर्णांक shअगरt = ap->port_no * NV_INT_PORT_SHIFT;
	u8 mask;

	mask = ioपढ़ो8(scr_addr + NV_INT_ENABLE);
	mask &= ~(NV_INT_ALL << shअगरt);
	ioग_लिखो8(mask, scr_addr + NV_INT_ENABLE);
पूर्ण

अटल व्योम nv_nf2_thaw(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *scr_addr = ap->host->ports[0]->ioaddr.scr_addr;
	पूर्णांक shअगरt = ap->port_no * NV_INT_PORT_SHIFT;
	u8 mask;

	ioग_लिखो8(NV_INT_ALL << shअगरt, scr_addr + NV_INT_STATUS);

	mask = ioपढ़ो8(scr_addr + NV_INT_ENABLE);
	mask |= (NV_INT_MASK << shअगरt);
	ioग_लिखो8(mask, scr_addr + NV_INT_ENABLE);
पूर्ण

अटल व्योम nv_ck804_मुक्तze(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *mmio_base = ap->host->iomap[NV_MMIO_BAR];
	पूर्णांक shअगरt = ap->port_no * NV_INT_PORT_SHIFT;
	u8 mask;

	mask = पढ़ोb(mmio_base + NV_INT_ENABLE_CK804);
	mask &= ~(NV_INT_ALL << shअगरt);
	ग_लिखोb(mask, mmio_base + NV_INT_ENABLE_CK804);
पूर्ण

अटल व्योम nv_ck804_thaw(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *mmio_base = ap->host->iomap[NV_MMIO_BAR];
	पूर्णांक shअगरt = ap->port_no * NV_INT_PORT_SHIFT;
	u8 mask;

	ग_लिखोb(NV_INT_ALL << shअगरt, mmio_base + NV_INT_STATUS_CK804);

	mask = पढ़ोb(mmio_base + NV_INT_ENABLE_CK804);
	mask |= (NV_INT_MASK << shअगरt);
	ग_लिखोb(mask, mmio_base + NV_INT_ENABLE_CK804);
पूर्ण

अटल व्योम nv_mcp55_मुक्तze(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *mmio_base = ap->host->iomap[NV_MMIO_BAR];
	पूर्णांक shअगरt = ap->port_no * NV_INT_PORT_SHIFT_MCP55;
	u32 mask;

	ग_लिखोl(NV_INT_ALL_MCP55 << shअगरt, mmio_base + NV_INT_STATUS_MCP55);

	mask = पढ़ोl(mmio_base + NV_INT_ENABLE_MCP55);
	mask &= ~(NV_INT_ALL_MCP55 << shअगरt);
	ग_लिखोl(mask, mmio_base + NV_INT_ENABLE_MCP55);
पूर्ण

अटल व्योम nv_mcp55_thaw(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *mmio_base = ap->host->iomap[NV_MMIO_BAR];
	पूर्णांक shअगरt = ap->port_no * NV_INT_PORT_SHIFT_MCP55;
	u32 mask;

	ग_लिखोl(NV_INT_ALL_MCP55 << shअगरt, mmio_base + NV_INT_STATUS_MCP55);

	mask = पढ़ोl(mmio_base + NV_INT_ENABLE_MCP55);
	mask |= (NV_INT_MASK_MCP55 << shअगरt);
	ग_लिखोl(mask, mmio_base + NV_INT_ENABLE_MCP55);
पूर्ण

अटल व्योम nv_adma_error_handler(काष्ठा ata_port *ap)
अणु
	काष्ठा nv_adma_port_priv *pp = ap->निजी_data;
	अगर (!(pp->flags & NV_ADMA_PORT_REGISTER_MODE)) अणु
		व्योम __iomem *mmio = pp->ctl_block;
		पूर्णांक i;
		u16 पंचांगp;

		अगर (ata_tag_valid(ap->link.active_tag) || ap->link.sactive) अणु
			u32 notअगरier = पढ़ोl(mmio + NV_ADMA_NOTIFIER);
			u32 notअगरier_error = पढ़ोl(mmio + NV_ADMA_NOTIFIER_ERROR);
			u32 gen_ctl = पढ़ोl(pp->gen_block + NV_ADMA_GEN_CTL);
			u32 status = पढ़ोw(mmio + NV_ADMA_STAT);
			u8 cpb_count = पढ़ोb(mmio + NV_ADMA_CPB_COUNT);
			u8 next_cpb_idx = पढ़ोb(mmio + NV_ADMA_NEXT_CPB_IDX);

			ata_port_err(ap,
				"EH in ADMA mode, notifier 0x%X "
				"notifier_error 0x%X gen_ctl 0x%X status 0x%X "
				"next cpb count 0x%X next cpb idx 0x%x\n",
				notअगरier, notअगरier_error, gen_ctl, status,
				cpb_count, next_cpb_idx);

			क्रम (i = 0; i < NV_ADMA_MAX_CPBS; i++) अणु
				काष्ठा nv_adma_cpb *cpb = &pp->cpb[i];
				अगर ((ata_tag_valid(ap->link.active_tag) && i == ap->link.active_tag) ||
				    ap->link.sactive & (1 << i))
					ata_port_err(ap,
						"CPB %d: ctl_flags 0x%x, resp_flags 0x%x\n",
						i, cpb->ctl_flags, cpb->resp_flags);
			पूर्ण
		पूर्ण

		/* Push us back पूर्णांकo port रेजिस्टर mode क्रम error handling. */
		nv_adma_रेजिस्टर_mode(ap);

		/* Mark all of the CPBs as invalid to prevent them from
		   being executed */
		क्रम (i = 0; i < NV_ADMA_MAX_CPBS; i++)
			pp->cpb[i].ctl_flags &= ~NV_CPB_CTL_CPB_VALID;

		/* clear CPB fetch count */
		ग_लिखोw(0, mmio + NV_ADMA_CPB_COUNT);

		/* Reset channel */
		पंचांगp = पढ़ोw(mmio + NV_ADMA_CTL);
		ग_लिखोw(पंचांगp | NV_ADMA_CTL_CHANNEL_RESET, mmio + NV_ADMA_CTL);
		पढ़ोw(mmio + NV_ADMA_CTL);	/* flush posted ग_लिखो */
		udelay(1);
		ग_लिखोw(पंचांगp & ~NV_ADMA_CTL_CHANNEL_RESET, mmio + NV_ADMA_CTL);
		पढ़ोw(mmio + NV_ADMA_CTL);	/* flush posted ग_लिखो */
	पूर्ण

	ata_bmdma_error_handler(ap);
पूर्ण

अटल व्योम nv_swncq_qc_to_dq(काष्ठा ata_port *ap, काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा nv_swncq_port_priv *pp = ap->निजी_data;
	काष्ठा defer_queue *dq = &pp->defer_queue;

	/* queue is full */
	WARN_ON(dq->tail - dq->head == ATA_MAX_QUEUE);
	dq->defer_bits |= (1 << qc->hw_tag);
	dq->tag[dq->tail++ & (ATA_MAX_QUEUE - 1)] = qc->hw_tag;
पूर्ण

अटल काष्ठा ata_queued_cmd *nv_swncq_qc_from_dq(काष्ठा ata_port *ap)
अणु
	काष्ठा nv_swncq_port_priv *pp = ap->निजी_data;
	काष्ठा defer_queue *dq = &pp->defer_queue;
	अचिन्हित पूर्णांक tag;

	अगर (dq->head == dq->tail)	/* null queue */
		वापस शून्य;

	tag = dq->tag[dq->head & (ATA_MAX_QUEUE - 1)];
	dq->tag[dq->head++ & (ATA_MAX_QUEUE - 1)] = ATA_TAG_POISON;
	WARN_ON(!(dq->defer_bits & (1 << tag)));
	dq->defer_bits &= ~(1 << tag);

	वापस ata_qc_from_tag(ap, tag);
पूर्ण

अटल व्योम nv_swncq_fis_reinit(काष्ठा ata_port *ap)
अणु
	काष्ठा nv_swncq_port_priv *pp = ap->निजी_data;

	pp->dhfis_bits = 0;
	pp->dmafis_bits = 0;
	pp->sdbfis_bits = 0;
	pp->ncq_flags = 0;
पूर्ण

अटल व्योम nv_swncq_pp_reinit(काष्ठा ata_port *ap)
अणु
	काष्ठा nv_swncq_port_priv *pp = ap->निजी_data;
	काष्ठा defer_queue *dq = &pp->defer_queue;

	dq->head = 0;
	dq->tail = 0;
	dq->defer_bits = 0;
	pp->qc_active = 0;
	pp->last_issue_tag = ATA_TAG_POISON;
	nv_swncq_fis_reinit(ap);
पूर्ण

अटल व्योम nv_swncq_irq_clear(काष्ठा ata_port *ap, u16 fis)
अणु
	काष्ठा nv_swncq_port_priv *pp = ap->निजी_data;

	ग_लिखोw(fis, pp->irq_block);
पूर्ण

अटल व्योम __ata_bmdma_stop(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_queued_cmd qc;

	qc.ap = ap;
	ata_bmdma_stop(&qc);
पूर्ण

अटल व्योम nv_swncq_ncq_stop(काष्ठा ata_port *ap)
अणु
	काष्ठा nv_swncq_port_priv *pp = ap->निजी_data;
	अचिन्हित पूर्णांक i;
	u32 sactive;
	u32 करोne_mask;

	ata_port_err(ap, "EH in SWNCQ mode,QC:qc_active 0x%llX sactive 0x%X\n",
		     ap->qc_active, ap->link.sactive);
	ata_port_err(ap,
		"SWNCQ:qc_active 0x%X defer_bits 0x%X last_issue_tag 0x%x\n  "
		"dhfis 0x%X dmafis 0x%X sdbfis 0x%X\n",
		pp->qc_active, pp->defer_queue.defer_bits, pp->last_issue_tag,
		pp->dhfis_bits, pp->dmafis_bits, pp->sdbfis_bits);

	ata_port_err(ap, "ATA_REG 0x%X ERR_REG 0x%X\n",
		     ap->ops->sff_check_status(ap),
		     ioपढ़ो8(ap->ioaddr.error_addr));

	sactive = पढ़ोl(pp->sactive_block);
	करोne_mask = pp->qc_active ^ sactive;

	ata_port_err(ap, "tag : dhfis dmafis sdbfis sactive\n");
	क्रम (i = 0; i < ATA_MAX_QUEUE; i++) अणु
		u8 err = 0;
		अगर (pp->qc_active & (1 << i))
			err = 0;
		अन्यथा अगर (करोne_mask & (1 << i))
			err = 1;
		अन्यथा
			जारी;

		ata_port_err(ap,
			     "tag 0x%x: %01x %01x %01x %01x %s\n", i,
			     (pp->dhfis_bits >> i) & 0x1,
			     (pp->dmafis_bits >> i) & 0x1,
			     (pp->sdbfis_bits >> i) & 0x1,
			     (sactive >> i) & 0x1,
			     (err ? "error! tag doesn't exit" : " "));
	पूर्ण

	nv_swncq_pp_reinit(ap);
	ap->ops->sff_irq_clear(ap);
	__ata_bmdma_stop(ap);
	nv_swncq_irq_clear(ap, 0xffff);
पूर्ण

अटल व्योम nv_swncq_error_handler(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_eh_context *ehc = &ap->link.eh_context;

	अगर (ap->link.sactive) अणु
		nv_swncq_ncq_stop(ap);
		ehc->i.action |= ATA_EH_RESET;
	पूर्ण

	ata_bmdma_error_handler(ap);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक nv_swncq_port_suspend(काष्ठा ata_port *ap, pm_message_t mesg)
अणु
	व्योम __iomem *mmio = ap->host->iomap[NV_MMIO_BAR];
	u32 पंचांगp;

	/* clear irq */
	ग_लिखोl(~0, mmio + NV_INT_STATUS_MCP55);

	/* disable irq */
	ग_लिखोl(0, mmio + NV_INT_ENABLE_MCP55);

	/* disable swncq */
	पंचांगp = पढ़ोl(mmio + NV_CTL_MCP55);
	पंचांगp &= ~(NV_CTL_PRI_SWNCQ | NV_CTL_SEC_SWNCQ);
	ग_लिखोl(पंचांगp, mmio + NV_CTL_MCP55);

	वापस 0;
पूर्ण

अटल पूर्णांक nv_swncq_port_resume(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *mmio = ap->host->iomap[NV_MMIO_BAR];
	u32 पंचांगp;

	/* clear irq */
	ग_लिखोl(~0, mmio + NV_INT_STATUS_MCP55);

	/* enable irq */
	ग_लिखोl(0x00fd00fd, mmio + NV_INT_ENABLE_MCP55);

	/* enable swncq */
	पंचांगp = पढ़ोl(mmio + NV_CTL_MCP55);
	ग_लिखोl(पंचांगp | NV_CTL_PRI_SWNCQ | NV_CTL_SEC_SWNCQ, mmio + NV_CTL_MCP55);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम nv_swncq_host_init(काष्ठा ata_host *host)
अणु
	u32 पंचांगp;
	व्योम __iomem *mmio = host->iomap[NV_MMIO_BAR];
	काष्ठा pci_dev *pdev = to_pci_dev(host->dev);
	u8 regval;

	/* disable  ECO 398 */
	pci_पढ़ो_config_byte(pdev, 0x7f, &regval);
	regval &= ~(1 << 7);
	pci_ग_लिखो_config_byte(pdev, 0x7f, regval);

	/* enable swncq */
	पंचांगp = पढ़ोl(mmio + NV_CTL_MCP55);
	VPRINTK("HOST_CTL:0x%X\n", पंचांगp);
	ग_लिखोl(पंचांगp | NV_CTL_PRI_SWNCQ | NV_CTL_SEC_SWNCQ, mmio + NV_CTL_MCP55);

	/* enable irq पूर्णांकr */
	पंचांगp = पढ़ोl(mmio + NV_INT_ENABLE_MCP55);
	VPRINTK("HOST_ENABLE:0x%X\n", पंचांगp);
	ग_लिखोl(पंचांगp | 0x00fd00fd, mmio + NV_INT_ENABLE_MCP55);

	/*  clear port irq */
	ग_लिखोl(~0x0, mmio + NV_INT_STATUS_MCP55);
पूर्ण

अटल पूर्णांक nv_swncq_slave_config(काष्ठा scsi_device *sdev)
अणु
	काष्ठा ata_port *ap = ata_shost_to_port(sdev->host);
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	काष्ठा ata_device *dev;
	पूर्णांक rc;
	u8 rev;
	u8 check_maxtor = 0;
	अचिन्हित अक्षर model_num[ATA_ID_PROD_LEN + 1];

	rc = ata_scsi_slave_config(sdev);
	अगर (sdev->id >= ATA_MAX_DEVICES || sdev->channel || sdev->lun)
		/* Not a proper libata device, ignore */
		वापस rc;

	dev = &ap->link.device[sdev->id];
	अगर (!(ap->flags & ATA_FLAG_NCQ) || dev->class == ATA_DEV_ATAPI)
		वापस rc;

	/* अगर MCP51 and Maxtor, then disable ncq */
	अगर (pdev->device == PCI_DEVICE_ID_NVIDIA_NFORCE_MCP51_SATA ||
		pdev->device == PCI_DEVICE_ID_NVIDIA_NFORCE_MCP51_SATA2)
		check_maxtor = 1;

	/* अगर MCP55 and rev <= a2 and Maxtor, then disable ncq */
	अगर (pdev->device == PCI_DEVICE_ID_NVIDIA_NFORCE_MCP55_SATA ||
		pdev->device == PCI_DEVICE_ID_NVIDIA_NFORCE_MCP55_SATA2) अणु
		pci_पढ़ो_config_byte(pdev, 0x8, &rev);
		अगर (rev <= 0xa2)
			check_maxtor = 1;
	पूर्ण

	अगर (!check_maxtor)
		वापस rc;

	ata_id_c_string(dev->id, model_num, ATA_ID_PROD, माप(model_num));

	अगर (म_भेदन(model_num, "Maxtor", 6) == 0) अणु
		ata_scsi_change_queue_depth(sdev, 1);
		ata_dev_notice(dev, "Disabling SWNCQ mode (depth %x)\n",
			       sdev->queue_depth);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक nv_swncq_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा device *dev = ap->host->dev;
	व्योम __iomem *mmio = ap->host->iomap[NV_MMIO_BAR];
	काष्ठा nv_swncq_port_priv *pp;
	पूर्णांक rc;

	/* we might fallback to bmdma, allocate bmdma resources */
	rc = ata_bmdma_port_start(ap);
	अगर (rc)
		वापस rc;

	pp = devm_kzalloc(dev, माप(*pp), GFP_KERNEL);
	अगर (!pp)
		वापस -ENOMEM;

	pp->prd = dmam_alloc_coherent(dev, ATA_PRD_TBL_SZ * ATA_MAX_QUEUE,
				      &pp->prd_dma, GFP_KERNEL);
	अगर (!pp->prd)
		वापस -ENOMEM;

	ap->निजी_data = pp;
	pp->sactive_block = ap->ioaddr.scr_addr + 4 * SCR_ACTIVE;
	pp->irq_block = mmio + NV_INT_STATUS_MCP55 + ap->port_no * 2;
	pp->tag_block = mmio + NV_NCQ_REG_MCP55 + ap->port_no * 2;

	वापस 0;
पूर्ण

अटल क्रमागत ata_completion_errors nv_swncq_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	अगर (qc->tf.protocol != ATA_PROT_NCQ) अणु
		ata_bmdma_qc_prep(qc);
		वापस AC_ERR_OK;
	पूर्ण

	अगर (!(qc->flags & ATA_QCFLAG_DMAMAP))
		वापस AC_ERR_OK;

	nv_swncq_fill_sg(qc);

	वापस AC_ERR_OK;
पूर्ण

अटल व्योम nv_swncq_fill_sg(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा scatterlist *sg;
	काष्ठा nv_swncq_port_priv *pp = ap->निजी_data;
	काष्ठा ata_bmdma_prd *prd;
	अचिन्हित पूर्णांक si, idx;

	prd = pp->prd + ATA_MAX_PRD * qc->hw_tag;

	idx = 0;
	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		u32 addr, offset;
		u32 sg_len, len;

		addr = (u32)sg_dma_address(sg);
		sg_len = sg_dma_len(sg);

		जबतक (sg_len) अणु
			offset = addr & 0xffff;
			len = sg_len;
			अगर ((offset + sg_len) > 0x10000)
				len = 0x10000 - offset;

			prd[idx].addr = cpu_to_le32(addr);
			prd[idx].flags_len = cpu_to_le32(len & 0xffff);

			idx++;
			sg_len -= len;
			addr += len;
		पूर्ण
	पूर्ण

	prd[idx - 1].flags_len |= cpu_to_le32(ATA_PRD_EOT);
पूर्ण

अटल अचिन्हित पूर्णांक nv_swncq_issue_atacmd(काष्ठा ata_port *ap,
					  काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा nv_swncq_port_priv *pp = ap->निजी_data;

	अगर (qc == शून्य)
		वापस 0;

	DPRINTK("Enter\n");

	ग_लिखोl((1 << qc->hw_tag), pp->sactive_block);
	pp->last_issue_tag = qc->hw_tag;
	pp->dhfis_bits &= ~(1 << qc->hw_tag);
	pp->dmafis_bits &= ~(1 << qc->hw_tag);
	pp->qc_active |= (0x1 << qc->hw_tag);

	ap->ops->sff_tf_load(ap, &qc->tf);	 /* load tf रेजिस्टरs */
	ap->ops->sff_exec_command(ap, &qc->tf);

	DPRINTK("Issued tag %u\n", qc->hw_tag);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक nv_swncq_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा nv_swncq_port_priv *pp = ap->निजी_data;

	अगर (qc->tf.protocol != ATA_PROT_NCQ)
		वापस ata_bmdma_qc_issue(qc);

	DPRINTK("Enter\n");

	अगर (!pp->qc_active)
		nv_swncq_issue_atacmd(ap, qc);
	अन्यथा
		nv_swncq_qc_to_dq(ap, qc);	/* add qc to defer queue */

	वापस 0;
पूर्ण

अटल व्योम nv_swncq_hotplug(काष्ठा ata_port *ap, u32 fis)
अणु
	u32 serror;
	काष्ठा ata_eh_info *ehi = &ap->link.eh_info;

	ata_ehi_clear_desc(ehi);

	/* AHCI needs SError cleared; otherwise, it might lock up */
	sata_scr_पढ़ो(&ap->link, SCR_ERROR, &serror);
	sata_scr_ग_लिखो(&ap->link, SCR_ERROR, serror);

	/* analyze @irq_stat */
	अगर (fis & NV_SWNCQ_IRQ_ADDED)
		ata_ehi_push_desc(ehi, "hot plug");
	अन्यथा अगर (fis & NV_SWNCQ_IRQ_REMOVED)
		ata_ehi_push_desc(ehi, "hot unplug");

	ata_ehi_hotplugged(ehi);

	/* okay, let's hand over to EH */
	ehi->serror |= serror;

	ata_port_मुक्तze(ap);
पूर्ण

अटल पूर्णांक nv_swncq_sdbfis(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_queued_cmd *qc;
	काष्ठा nv_swncq_port_priv *pp = ap->निजी_data;
	काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
	u32 sactive;
	u32 करोne_mask;
	u8 host_stat;
	u8 lack_dhfis = 0;

	host_stat = ap->ops->bmdma_status(ap);
	अगर (unlikely(host_stat & ATA_DMA_ERR)) अणु
		/* error when transferring data to/from memory */
		ata_ehi_clear_desc(ehi);
		ata_ehi_push_desc(ehi, "BMDMA stat 0x%x", host_stat);
		ehi->err_mask |= AC_ERR_HOST_BUS;
		ehi->action |= ATA_EH_RESET;
		वापस -EINVAL;
	पूर्ण

	ap->ops->sff_irq_clear(ap);
	__ata_bmdma_stop(ap);

	sactive = पढ़ोl(pp->sactive_block);
	करोne_mask = pp->qc_active ^ sactive;

	pp->qc_active &= ~करोne_mask;
	pp->dhfis_bits &= ~करोne_mask;
	pp->dmafis_bits &= ~करोne_mask;
	pp->sdbfis_bits |= करोne_mask;
	ata_qc_complete_multiple(ap, ata_qc_get_active(ap) ^ करोne_mask);

	अगर (!ap->qc_active) अणु
		DPRINTK("over\n");
		nv_swncq_pp_reinit(ap);
		वापस 0;
	पूर्ण

	अगर (pp->qc_active & pp->dhfis_bits)
		वापस 0;

	अगर ((pp->ncq_flags & ncq_saw_backout) ||
	    (pp->qc_active ^ pp->dhfis_bits))
		/* अगर the controller can't get a device to host रेजिस्टर FIS,
		 * The driver needs to reissue the new command.
		 */
		lack_dhfis = 1;

	DPRINTK("id 0x%x QC: qc_active 0x%x,"
		"SWNCQ:qc_active 0x%X defer_bits %X "
		"dhfis 0x%X dmafis 0x%X last_issue_tag %x\n",
		ap->prपूर्णांक_id, ap->qc_active, pp->qc_active,
		pp->defer_queue.defer_bits, pp->dhfis_bits,
		pp->dmafis_bits, pp->last_issue_tag);

	nv_swncq_fis_reinit(ap);

	अगर (lack_dhfis) अणु
		qc = ata_qc_from_tag(ap, pp->last_issue_tag);
		nv_swncq_issue_atacmd(ap, qc);
		वापस 0;
	पूर्ण

	अगर (pp->defer_queue.defer_bits) अणु
		/* send deferral queue command */
		qc = nv_swncq_qc_from_dq(ap);
		WARN_ON(qc == शून्य);
		nv_swncq_issue_atacmd(ap, qc);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत u32 nv_swncq_tag(काष्ठा ata_port *ap)
अणु
	काष्ठा nv_swncq_port_priv *pp = ap->निजी_data;
	u32 tag;

	tag = पढ़ोb(pp->tag_block) >> 2;
	वापस (tag & 0x1f);
पूर्ण

अटल व्योम nv_swncq_dmafis(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_queued_cmd *qc;
	अचिन्हित पूर्णांक rw;
	u8 dmactl;
	u32 tag;
	काष्ठा nv_swncq_port_priv *pp = ap->निजी_data;

	__ata_bmdma_stop(ap);
	tag = nv_swncq_tag(ap);

	DPRINTK("dma setup tag 0x%x\n", tag);
	qc = ata_qc_from_tag(ap, tag);

	अगर (unlikely(!qc))
		वापस;

	rw = qc->tf.flags & ATA_TFLAG_WRITE;

	/* load PRD table addr. */
	ioग_लिखो32(pp->prd_dma + ATA_PRD_TBL_SZ * qc->hw_tag,
		  ap->ioaddr.bmdma_addr + ATA_DMA_TABLE_OFS);

	/* specअगरy data direction, triple-check start bit is clear */
	dmactl = ioपढ़ो8(ap->ioaddr.bmdma_addr + ATA_DMA_CMD);
	dmactl &= ~ATA_DMA_WR;
	अगर (!rw)
		dmactl |= ATA_DMA_WR;

	ioग_लिखो8(dmactl | ATA_DMA_START, ap->ioaddr.bmdma_addr + ATA_DMA_CMD);
पूर्ण

अटल व्योम nv_swncq_host_पूर्णांकerrupt(काष्ठा ata_port *ap, u16 fis)
अणु
	काष्ठा nv_swncq_port_priv *pp = ap->निजी_data;
	काष्ठा ata_queued_cmd *qc;
	काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
	u32 serror;
	u8 ata_stat;

	ata_stat = ap->ops->sff_check_status(ap);
	nv_swncq_irq_clear(ap, fis);
	अगर (!fis)
		वापस;

	अगर (ap->pflags & ATA_PFLAG_FROZEN)
		वापस;

	अगर (fis & NV_SWNCQ_IRQ_HOTPLUG) अणु
		nv_swncq_hotplug(ap, fis);
		वापस;
	पूर्ण

	अगर (!pp->qc_active)
		वापस;

	अगर (ap->ops->scr_पढ़ो(&ap->link, SCR_ERROR, &serror))
		वापस;
	ap->ops->scr_ग_लिखो(&ap->link, SCR_ERROR, serror);

	अगर (ata_stat & ATA_ERR) अणु
		ata_ehi_clear_desc(ehi);
		ata_ehi_push_desc(ehi, "Ata error. fis:0x%X", fis);
		ehi->err_mask |= AC_ERR_DEV;
		ehi->serror |= serror;
		ehi->action |= ATA_EH_RESET;
		ata_port_मुक्तze(ap);
		वापस;
	पूर्ण

	अगर (fis & NV_SWNCQ_IRQ_BACKOUT) अणु
		/* If the IRQ is backout, driver must issue
		 * the new command again some समय later.
		 */
		pp->ncq_flags |= ncq_saw_backout;
	पूर्ण

	अगर (fis & NV_SWNCQ_IRQ_SDBFIS) अणु
		pp->ncq_flags |= ncq_saw_sdb;
		DPRINTK("id 0x%x SWNCQ: qc_active 0x%X "
			"dhfis 0x%X dmafis 0x%X sactive 0x%X\n",
			ap->prपूर्णांक_id, pp->qc_active, pp->dhfis_bits,
			pp->dmafis_bits, पढ़ोl(pp->sactive_block));
		अगर (nv_swncq_sdbfis(ap) < 0)
			जाओ irq_error;
	पूर्ण

	अगर (fis & NV_SWNCQ_IRQ_DHREGFIS) अणु
		/* The पूर्णांकerrupt indicates the new command
		 * was transmitted correctly to the drive.
		 */
		pp->dhfis_bits |= (0x1 << pp->last_issue_tag);
		pp->ncq_flags |= ncq_saw_d2h;
		अगर (pp->ncq_flags & (ncq_saw_sdb | ncq_saw_backout)) अणु
			ata_ehi_push_desc(ehi, "illegal fis transaction");
			ehi->err_mask |= AC_ERR_HSM;
			ehi->action |= ATA_EH_RESET;
			जाओ irq_error;
		पूर्ण

		अगर (!(fis & NV_SWNCQ_IRQ_DMASETUP) &&
		    !(pp->ncq_flags & ncq_saw_dmas)) अणु
			ata_stat = ap->ops->sff_check_status(ap);
			अगर (ata_stat & ATA_BUSY)
				जाओ irq_निकास;

			अगर (pp->defer_queue.defer_bits) अणु
				DPRINTK("send next command\n");
				qc = nv_swncq_qc_from_dq(ap);
				nv_swncq_issue_atacmd(ap, qc);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (fis & NV_SWNCQ_IRQ_DMASETUP) अणु
		/* program the dma controller with appropriate PRD buffers
		 * and start the DMA transfer क्रम requested command.
		 */
		pp->dmafis_bits |= (0x1 << nv_swncq_tag(ap));
		pp->ncq_flags |= ncq_saw_dmas;
		nv_swncq_dmafis(ap);
	पूर्ण

irq_निकास:
	वापस;
irq_error:
	ata_ehi_push_desc(ehi, "fis:0x%x", fis);
	ata_port_मुक्तze(ap);
	वापस;
पूर्ण

अटल irqवापस_t nv_swncq_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक handled = 0;
	अचिन्हित दीर्घ flags;
	u32 irq_stat;

	spin_lock_irqsave(&host->lock, flags);

	irq_stat = पढ़ोl(host->iomap[NV_MMIO_BAR] + NV_INT_STATUS_MCP55);

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		अगर (ap->link.sactive) अणु
			nv_swncq_host_पूर्णांकerrupt(ap, (u16)irq_stat);
			handled = 1;
		पूर्ण अन्यथा अणु
			अगर (irq_stat)	/* reserve Hotplug */
				nv_swncq_irq_clear(ap, 0xfff0);

			handled += nv_host_पूर्णांकr(ap, (u8)irq_stat);
		पूर्ण
		irq_stat >>= NV_INT_PORT_SHIFT_MCP55;
	पूर्ण

	spin_unlock_irqrestore(&host->lock, flags);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल पूर्णांक nv_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	स्थिर काष्ठा ata_port_info *ppi[] = अणु शून्य, शून्य पूर्ण;
	काष्ठा nv_pi_priv *ipriv;
	काष्ठा ata_host *host;
	काष्ठा nv_host_priv *hpriv;
	पूर्णांक rc;
	u32 bar;
	व्योम __iomem *base;
	अचिन्हित दीर्घ type = ent->driver_data;

        // Make sure this is a SATA controller by counting the number of bars
        // (NVIDIA SATA controllers will always have six bars).  Otherwise,
        // it's an IDE controller and we ignore it.
	क्रम (bar = 0; bar < PCI_STD_NUM_BARS; bar++)
		अगर (pci_resource_start(pdev, bar) == 0)
			वापस -ENODEV;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	/* determine type and allocate host */
	अगर (type == CK804 && adma_enabled) अणु
		dev_notice(&pdev->dev, "Using ADMA mode\n");
		type = ADMA;
	पूर्ण अन्यथा अगर (type == MCP5x && swncq_enabled) अणु
		dev_notice(&pdev->dev, "Using SWNCQ mode\n");
		type = SWNCQ;
	पूर्ण

	ppi[0] = &nv_port_info[type];
	ipriv = ppi[0]->निजी_data;
	rc = ata_pci_bmdma_prepare_host(pdev, ppi, &host);
	अगर (rc)
		वापस rc;

	hpriv = devm_kzalloc(&pdev->dev, माप(*hpriv), GFP_KERNEL);
	अगर (!hpriv)
		वापस -ENOMEM;
	hpriv->type = type;
	host->निजी_data = hpriv;

	/* request and iomap NV_MMIO_BAR */
	rc = pcim_iomap_regions(pdev, 1 << NV_MMIO_BAR, DRV_NAME);
	अगर (rc)
		वापस rc;

	/* configure SCR access */
	base = host->iomap[NV_MMIO_BAR];
	host->ports[0]->ioaddr.scr_addr = base + NV_PORT0_SCR_REG_OFFSET;
	host->ports[1]->ioaddr.scr_addr = base + NV_PORT1_SCR_REG_OFFSET;

	/* enable SATA space क्रम CK804 */
	अगर (type >= CK804) अणु
		u8 regval;

		pci_पढ़ो_config_byte(pdev, NV_MCP_SATA_CFG_20, &regval);
		regval |= NV_MCP_SATA_CFG_20_SATA_SPACE_EN;
		pci_ग_लिखो_config_byte(pdev, NV_MCP_SATA_CFG_20, regval);
	पूर्ण

	/* init ADMA */
	अगर (type == ADMA) अणु
		rc = nv_adma_host_init(host);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अगर (type == SWNCQ)
		nv_swncq_host_init(host);

	अगर (msi_enabled) अणु
		dev_notice(&pdev->dev, "Using MSI\n");
		pci_enable_msi(pdev);
	पूर्ण

	pci_set_master(pdev);
	वापस ata_pci_sff_activate_host(host, ipriv->irq_handler, ipriv->sht);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक nv_pci_device_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	काष्ठा nv_host_priv *hpriv = host->निजी_data;
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	अगर (pdev->dev.घातer.घातer_state.event == PM_EVENT_SUSPEND) अणु
		अगर (hpriv->type >= CK804) अणु
			u8 regval;

			pci_पढ़ो_config_byte(pdev, NV_MCP_SATA_CFG_20, &regval);
			regval |= NV_MCP_SATA_CFG_20_SATA_SPACE_EN;
			pci_ग_लिखो_config_byte(pdev, NV_MCP_SATA_CFG_20, regval);
		पूर्ण
		अगर (hpriv->type == ADMA) अणु
			u32 पंचांगp32;
			काष्ठा nv_adma_port_priv *pp;
			/* enable/disable ADMA on the ports appropriately */
			pci_पढ़ो_config_dword(pdev, NV_MCP_SATA_CFG_20, &पंचांगp32);

			pp = host->ports[0]->निजी_data;
			अगर (pp->flags & NV_ADMA_ATAPI_SETUP_COMPLETE)
				पंचांगp32 &= ~(NV_MCP_SATA_CFG_20_PORT0_EN |
					   NV_MCP_SATA_CFG_20_PORT0_PWB_EN);
			अन्यथा
				पंचांगp32 |=  (NV_MCP_SATA_CFG_20_PORT0_EN |
					   NV_MCP_SATA_CFG_20_PORT0_PWB_EN);
			pp = host->ports[1]->निजी_data;
			अगर (pp->flags & NV_ADMA_ATAPI_SETUP_COMPLETE)
				पंचांगp32 &= ~(NV_MCP_SATA_CFG_20_PORT1_EN |
					   NV_MCP_SATA_CFG_20_PORT1_PWB_EN);
			अन्यथा
				पंचांगp32 |=  (NV_MCP_SATA_CFG_20_PORT1_EN |
					   NV_MCP_SATA_CFG_20_PORT1_PWB_EN);

			pci_ग_लिखो_config_dword(pdev, NV_MCP_SATA_CFG_20, पंचांगp32);
		पूर्ण
	पूर्ण

	ata_host_resume(host);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम nv_ck804_host_stop(काष्ठा ata_host *host)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(host->dev);
	u8 regval;

	/* disable SATA space क्रम CK804 */
	pci_पढ़ो_config_byte(pdev, NV_MCP_SATA_CFG_20, &regval);
	regval &= ~NV_MCP_SATA_CFG_20_SATA_SPACE_EN;
	pci_ग_लिखो_config_byte(pdev, NV_MCP_SATA_CFG_20, regval);
पूर्ण

अटल व्योम nv_adma_host_stop(काष्ठा ata_host *host)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(host->dev);
	u32 पंचांगp32;

	/* disable ADMA on the ports */
	pci_पढ़ो_config_dword(pdev, NV_MCP_SATA_CFG_20, &पंचांगp32);
	पंचांगp32 &= ~(NV_MCP_SATA_CFG_20_PORT0_EN |
		   NV_MCP_SATA_CFG_20_PORT0_PWB_EN |
		   NV_MCP_SATA_CFG_20_PORT1_EN |
		   NV_MCP_SATA_CFG_20_PORT1_PWB_EN);

	pci_ग_लिखो_config_dword(pdev, NV_MCP_SATA_CFG_20, पंचांगp32);

	nv_ck804_host_stop(host);
पूर्ण

module_pci_driver(nv_pci_driver);

module_param_named(adma, adma_enabled, bool, 0444);
MODULE_PARM_DESC(adma, "Enable use of ADMA (Default: false)");
module_param_named(swncq, swncq_enabled, bool, 0444);
MODULE_PARM_DESC(swncq, "Enable use of SWNCQ (Default: true)");
module_param_named(msi, msi_enabled, bool, 0444);
MODULE_PARM_DESC(msi, "Enable use of MSI (Default: false)");
