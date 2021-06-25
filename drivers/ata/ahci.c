<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ahci.c - AHCI SATA support
 *
 *  Maपूर्णांकained by:  Tejun Heo <tj@kernel.org>
 *    		    Please ALWAYS copy linux-ide@vger.kernel.org
 *		    on emails.
 *
 *  Copyright 2004-2005 Red Hat, Inc.
 *
 * libata करोcumentation is available via 'make {ps|pdf}docs',
 * as Documentation/driver-api/libata.rst
 *
 * AHCI hardware करोcumentation:
 * http://www.पूर्णांकel.com/technology/serialata/pdf/rev1_0.pdf
 * http://www.पूर्णांकel.com/technology/serialata/pdf/rev1_1.pdf
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/device.h>
#समावेश <linux/dmi.h>
#समावेश <linux/gfp.h>
#समावेश <linux/msi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <linux/libata.h>
#समावेश <linux/ahci-remap.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश "ahci.h"

#घोषणा DRV_NAME	"ahci"
#घोषणा DRV_VERSION	"3.0"

क्रमागत अणु
	AHCI_PCI_BAR_STA2X11	= 0,
	AHCI_PCI_BAR_CAVIUM	= 0,
	AHCI_PCI_BAR_LOONGSON	= 0,
	AHCI_PCI_BAR_ENMOTUS	= 2,
	AHCI_PCI_BAR_CAVIUM_GEN5	= 4,
	AHCI_PCI_BAR_STANDARD	= 5,
पूर्ण;

क्रमागत board_ids अणु
	/* board IDs by feature in alphabetical order */
	board_ahci,
	board_ahci_ign_अगरerr,
	board_ahci_mobile,
	board_ahci_nomsi,
	board_ahci_noncq,
	board_ahci_nosntf,
	board_ahci_yes_fbs,

	/* board IDs क्रम specअगरic chipsets in alphabetical order */
	board_ahci_al,
	board_ahci_avn,
	board_ahci_mcp65,
	board_ahci_mcp77,
	board_ahci_mcp89,
	board_ahci_mv,
	board_ahci_sb600,
	board_ahci_sb700,	/* क्रम SB700 and SB800 */
	board_ahci_vt8251,

	/*
	 * board IDs क्रम Intel chipsets that support more than 6 ports
	 * *and* end up needing the PCS quirk.
	 */
	board_ahci_pcs7,

	/* aliases */
	board_ahci_mcp_linux	= board_ahci_mcp65,
	board_ahci_mcp67	= board_ahci_mcp65,
	board_ahci_mcp73	= board_ahci_mcp65,
	board_ahci_mcp79	= board_ahci_mcp77,
पूर्ण;

अटल पूर्णांक ahci_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
अटल व्योम ahci_हटाओ_one(काष्ठा pci_dev *dev);
अटल व्योम ahci_shutकरोwn_one(काष्ठा pci_dev *dev);
अटल पूर्णांक ahci_vt8251_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
				 अचिन्हित दीर्घ deadline);
अटल पूर्णांक ahci_avn_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			      अचिन्हित दीर्घ deadline);
अटल व्योम ahci_mcp89_apple_enable(काष्ठा pci_dev *pdev);
अटल bool is_mcp89_apple(काष्ठा pci_dev *pdev);
अटल पूर्णांक ahci_p5wdh_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
				अचिन्हित दीर्घ deadline);
#अगर_घोषित CONFIG_PM
अटल पूर्णांक ahci_pci_device_runसमय_suspend(काष्ठा device *dev);
अटल पूर्णांक ahci_pci_device_runसमय_resume(काष्ठा device *dev);
#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ahci_pci_device_suspend(काष्ठा device *dev);
अटल पूर्णांक ahci_pci_device_resume(काष्ठा device *dev);
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा scsi_host_ढाँचा ahci_sht = अणु
	AHCI_SHT("ahci"),
पूर्ण;

अटल काष्ठा ata_port_operations ahci_vt8251_ops = अणु
	.inherits		= &ahci_ops,
	.hardreset		= ahci_vt8251_hardreset,
पूर्ण;

अटल काष्ठा ata_port_operations ahci_p5wdh_ops = अणु
	.inherits		= &ahci_ops,
	.hardreset		= ahci_p5wdh_hardreset,
पूर्ण;

अटल काष्ठा ata_port_operations ahci_avn_ops = अणु
	.inherits		= &ahci_ops,
	.hardreset		= ahci_avn_hardreset,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info ahci_port_info[] = अणु
	/* by features */
	[board_ahci] = अणु
		.flags		= AHCI_FLAG_COMMON,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &ahci_ops,
	पूर्ण,
	[board_ahci_ign_अगरerr] = अणु
		AHCI_HFLAGS	(AHCI_HFLAG_IGN_IRQ_IF_ERR),
		.flags		= AHCI_FLAG_COMMON,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &ahci_ops,
	पूर्ण,
	[board_ahci_mobile] = अणु
		AHCI_HFLAGS	(AHCI_HFLAG_IS_MOBILE),
		.flags		= AHCI_FLAG_COMMON,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &ahci_ops,
	पूर्ण,
	[board_ahci_nomsi] = अणु
		AHCI_HFLAGS	(AHCI_HFLAG_NO_MSI),
		.flags		= AHCI_FLAG_COMMON,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &ahci_ops,
	पूर्ण,
	[board_ahci_noncq] = अणु
		AHCI_HFLAGS	(AHCI_HFLAG_NO_NCQ),
		.flags		= AHCI_FLAG_COMMON,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &ahci_ops,
	पूर्ण,
	[board_ahci_nosntf] = अणु
		AHCI_HFLAGS	(AHCI_HFLAG_NO_SNTF),
		.flags		= AHCI_FLAG_COMMON,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &ahci_ops,
	पूर्ण,
	[board_ahci_yes_fbs] = अणु
		AHCI_HFLAGS	(AHCI_HFLAG_YES_FBS),
		.flags		= AHCI_FLAG_COMMON,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &ahci_ops,
	पूर्ण,
	/* by chipsets */
	[board_ahci_al] = अणु
		AHCI_HFLAGS	(AHCI_HFLAG_NO_PMP | AHCI_HFLAG_NO_MSI),
		.flags		= AHCI_FLAG_COMMON,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &ahci_ops,
	पूर्ण,
	[board_ahci_avn] = अणु
		.flags		= AHCI_FLAG_COMMON,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &ahci_avn_ops,
	पूर्ण,
	[board_ahci_mcp65] = अणु
		AHCI_HFLAGS	(AHCI_HFLAG_NO_FPDMA_AA | AHCI_HFLAG_NO_PMP |
				 AHCI_HFLAG_YES_NCQ),
		.flags		= AHCI_FLAG_COMMON | ATA_FLAG_NO_DIPM,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &ahci_ops,
	पूर्ण,
	[board_ahci_mcp77] = अणु
		AHCI_HFLAGS	(AHCI_HFLAG_NO_FPDMA_AA | AHCI_HFLAG_NO_PMP),
		.flags		= AHCI_FLAG_COMMON,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &ahci_ops,
	पूर्ण,
	[board_ahci_mcp89] = अणु
		AHCI_HFLAGS	(AHCI_HFLAG_NO_FPDMA_AA),
		.flags		= AHCI_FLAG_COMMON,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &ahci_ops,
	पूर्ण,
	[board_ahci_mv] = अणु
		AHCI_HFLAGS	(AHCI_HFLAG_NO_NCQ | AHCI_HFLAG_NO_MSI |
				 AHCI_HFLAG_MV_PATA | AHCI_HFLAG_NO_PMP),
		.flags		= ATA_FLAG_SATA | ATA_FLAG_PIO_DMA,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &ahci_ops,
	पूर्ण,
	[board_ahci_sb600] = अणु
		AHCI_HFLAGS	(AHCI_HFLAG_IGN_SERR_INTERNAL |
				 AHCI_HFLAG_NO_MSI | AHCI_HFLAG_SECT255 |
				 AHCI_HFLAG_32BIT_ONLY),
		.flags		= AHCI_FLAG_COMMON,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &ahci_pmp_retry_srst_ops,
	पूर्ण,
	[board_ahci_sb700] = अणु	/* क्रम SB700 and SB800 */
		AHCI_HFLAGS	(AHCI_HFLAG_IGN_SERR_INTERNAL),
		.flags		= AHCI_FLAG_COMMON,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &ahci_pmp_retry_srst_ops,
	पूर्ण,
	[board_ahci_vt8251] = अणु
		AHCI_HFLAGS	(AHCI_HFLAG_NO_NCQ | AHCI_HFLAG_NO_PMP),
		.flags		= AHCI_FLAG_COMMON,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &ahci_vt8251_ops,
	पूर्ण,
	[board_ahci_pcs7] = अणु
		.flags		= AHCI_FLAG_COMMON,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &ahci_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id ahci_pci_tbl[] = अणु
	/* Intel */
	अणु PCI_VDEVICE(INTEL, 0x06d6), board_ahci पूर्ण, /* Comet Lake PCH-H RAID */
	अणु PCI_VDEVICE(INTEL, 0x2652), board_ahci पूर्ण, /* ICH6 */
	अणु PCI_VDEVICE(INTEL, 0x2653), board_ahci पूर्ण, /* ICH6M */
	अणु PCI_VDEVICE(INTEL, 0x27c1), board_ahci पूर्ण, /* ICH7 */
	अणु PCI_VDEVICE(INTEL, 0x27c5), board_ahci पूर्ण, /* ICH7M */
	अणु PCI_VDEVICE(INTEL, 0x27c3), board_ahci पूर्ण, /* ICH7R */
	अणु PCI_VDEVICE(AL, 0x5288), board_ahci_ign_अगरerr पूर्ण, /* ULi M5288 */
	अणु PCI_VDEVICE(INTEL, 0x2681), board_ahci पूर्ण, /* ESB2 */
	अणु PCI_VDEVICE(INTEL, 0x2682), board_ahci पूर्ण, /* ESB2 */
	अणु PCI_VDEVICE(INTEL, 0x2683), board_ahci पूर्ण, /* ESB2 */
	अणु PCI_VDEVICE(INTEL, 0x27c6), board_ahci पूर्ण, /* ICH7-M DH */
	अणु PCI_VDEVICE(INTEL, 0x2821), board_ahci पूर्ण, /* ICH8 */
	अणु PCI_VDEVICE(INTEL, 0x2822), board_ahci_nosntf पूर्ण, /* ICH8 */
	अणु PCI_VDEVICE(INTEL, 0x2824), board_ahci पूर्ण, /* ICH8 */
	अणु PCI_VDEVICE(INTEL, 0x2829), board_ahci पूर्ण, /* ICH8M */
	अणु PCI_VDEVICE(INTEL, 0x282a), board_ahci पूर्ण, /* ICH8M */
	अणु PCI_VDEVICE(INTEL, 0x2922), board_ahci पूर्ण, /* ICH9 */
	अणु PCI_VDEVICE(INTEL, 0x2923), board_ahci पूर्ण, /* ICH9 */
	अणु PCI_VDEVICE(INTEL, 0x2924), board_ahci पूर्ण, /* ICH9 */
	अणु PCI_VDEVICE(INTEL, 0x2925), board_ahci पूर्ण, /* ICH9 */
	अणु PCI_VDEVICE(INTEL, 0x2927), board_ahci पूर्ण, /* ICH9 */
	अणु PCI_VDEVICE(INTEL, 0x2929), board_ahci_mobile पूर्ण, /* ICH9M */
	अणु PCI_VDEVICE(INTEL, 0x292a), board_ahci_mobile पूर्ण, /* ICH9M */
	अणु PCI_VDEVICE(INTEL, 0x292b), board_ahci_mobile पूर्ण, /* ICH9M */
	अणु PCI_VDEVICE(INTEL, 0x292c), board_ahci_mobile पूर्ण, /* ICH9M */
	अणु PCI_VDEVICE(INTEL, 0x292f), board_ahci_mobile पूर्ण, /* ICH9M */
	अणु PCI_VDEVICE(INTEL, 0x294d), board_ahci पूर्ण, /* ICH9 */
	अणु PCI_VDEVICE(INTEL, 0x294e), board_ahci_mobile पूर्ण, /* ICH9M */
	अणु PCI_VDEVICE(INTEL, 0x502a), board_ahci पूर्ण, /* Tolapai */
	अणु PCI_VDEVICE(INTEL, 0x502b), board_ahci पूर्ण, /* Tolapai */
	अणु PCI_VDEVICE(INTEL, 0x3a05), board_ahci पूर्ण, /* ICH10 */
	अणु PCI_VDEVICE(INTEL, 0x3a22), board_ahci पूर्ण, /* ICH10 */
	अणु PCI_VDEVICE(INTEL, 0x3a25), board_ahci पूर्ण, /* ICH10 */
	अणु PCI_VDEVICE(INTEL, 0x3b22), board_ahci पूर्ण, /* PCH AHCI */
	अणु PCI_VDEVICE(INTEL, 0x3b23), board_ahci पूर्ण, /* PCH AHCI */
	अणु PCI_VDEVICE(INTEL, 0x3b24), board_ahci पूर्ण, /* PCH RAID */
	अणु PCI_VDEVICE(INTEL, 0x3b25), board_ahci पूर्ण, /* PCH RAID */
	अणु PCI_VDEVICE(INTEL, 0x3b29), board_ahci_mobile पूर्ण, /* PCH M AHCI */
	अणु PCI_VDEVICE(INTEL, 0x3b2b), board_ahci पूर्ण, /* PCH RAID */
	अणु PCI_VDEVICE(INTEL, 0x3b2c), board_ahci_mobile पूर्ण, /* PCH M RAID */
	अणु PCI_VDEVICE(INTEL, 0x3b2f), board_ahci पूर्ण, /* PCH AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19b0), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19b1), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19b2), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19b3), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19b4), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19b5), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19b6), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19b7), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19bE), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19bF), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19c0), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19c1), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19c2), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19c3), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19c4), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19c5), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19c6), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19c7), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19cE), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x19cF), board_ahci_pcs7 पूर्ण, /* DNV AHCI */
	अणु PCI_VDEVICE(INTEL, 0x1c02), board_ahci पूर्ण, /* CPT AHCI */
	अणु PCI_VDEVICE(INTEL, 0x1c03), board_ahci_mobile पूर्ण, /* CPT M AHCI */
	अणु PCI_VDEVICE(INTEL, 0x1c04), board_ahci पूर्ण, /* CPT RAID */
	अणु PCI_VDEVICE(INTEL, 0x1c05), board_ahci_mobile पूर्ण, /* CPT M RAID */
	अणु PCI_VDEVICE(INTEL, 0x1c06), board_ahci पूर्ण, /* CPT RAID */
	अणु PCI_VDEVICE(INTEL, 0x1c07), board_ahci पूर्ण, /* CPT RAID */
	अणु PCI_VDEVICE(INTEL, 0x1d02), board_ahci पूर्ण, /* PBG AHCI */
	अणु PCI_VDEVICE(INTEL, 0x1d04), board_ahci पूर्ण, /* PBG RAID */
	अणु PCI_VDEVICE(INTEL, 0x1d06), board_ahci पूर्ण, /* PBG RAID */
	अणु PCI_VDEVICE(INTEL, 0x2826), board_ahci पूर्ण, /* PBG RAID */
	अणु PCI_VDEVICE(INTEL, 0x2323), board_ahci पूर्ण, /* DH89xxCC AHCI */
	अणु PCI_VDEVICE(INTEL, 0x1e02), board_ahci पूर्ण, /* Panther Poपूर्णांक AHCI */
	अणु PCI_VDEVICE(INTEL, 0x1e03), board_ahci_mobile पूर्ण, /* Panther M AHCI */
	अणु PCI_VDEVICE(INTEL, 0x1e04), board_ahci पूर्ण, /* Panther Poपूर्णांक RAID */
	अणु PCI_VDEVICE(INTEL, 0x1e05), board_ahci पूर्ण, /* Panther Poपूर्णांक RAID */
	अणु PCI_VDEVICE(INTEL, 0x1e06), board_ahci पूर्ण, /* Panther Poपूर्णांक RAID */
	अणु PCI_VDEVICE(INTEL, 0x1e07), board_ahci_mobile पूर्ण, /* Panther M RAID */
	अणु PCI_VDEVICE(INTEL, 0x1e0e), board_ahci पूर्ण, /* Panther Poपूर्णांक RAID */
	अणु PCI_VDEVICE(INTEL, 0x8c02), board_ahci पूर्ण, /* Lynx Poपूर्णांक AHCI */
	अणु PCI_VDEVICE(INTEL, 0x8c03), board_ahci_mobile पूर्ण, /* Lynx M AHCI */
	अणु PCI_VDEVICE(INTEL, 0x8c04), board_ahci पूर्ण, /* Lynx Poपूर्णांक RAID */
	अणु PCI_VDEVICE(INTEL, 0x8c05), board_ahci_mobile पूर्ण, /* Lynx M RAID */
	अणु PCI_VDEVICE(INTEL, 0x8c06), board_ahci पूर्ण, /* Lynx Poपूर्णांक RAID */
	अणु PCI_VDEVICE(INTEL, 0x8c07), board_ahci_mobile पूर्ण, /* Lynx M RAID */
	अणु PCI_VDEVICE(INTEL, 0x8c0e), board_ahci पूर्ण, /* Lynx Poपूर्णांक RAID */
	अणु PCI_VDEVICE(INTEL, 0x8c0f), board_ahci_mobile पूर्ण, /* Lynx M RAID */
	अणु PCI_VDEVICE(INTEL, 0x9c02), board_ahci_mobile पूर्ण, /* Lynx LP AHCI */
	अणु PCI_VDEVICE(INTEL, 0x9c03), board_ahci_mobile पूर्ण, /* Lynx LP AHCI */
	अणु PCI_VDEVICE(INTEL, 0x9c04), board_ahci_mobile पूर्ण, /* Lynx LP RAID */
	अणु PCI_VDEVICE(INTEL, 0x9c05), board_ahci_mobile पूर्ण, /* Lynx LP RAID */
	अणु PCI_VDEVICE(INTEL, 0x9c06), board_ahci_mobile पूर्ण, /* Lynx LP RAID */
	अणु PCI_VDEVICE(INTEL, 0x9c07), board_ahci_mobile पूर्ण, /* Lynx LP RAID */
	अणु PCI_VDEVICE(INTEL, 0x9c0e), board_ahci_mobile पूर्ण, /* Lynx LP RAID */
	अणु PCI_VDEVICE(INTEL, 0x9c0f), board_ahci_mobile पूर्ण, /* Lynx LP RAID */
	अणु PCI_VDEVICE(INTEL, 0x9dd3), board_ahci_mobile पूर्ण, /* Cannon Lake PCH-LP AHCI */
	अणु PCI_VDEVICE(INTEL, 0x1f22), board_ahci पूर्ण, /* Avoton AHCI */
	अणु PCI_VDEVICE(INTEL, 0x1f23), board_ahci पूर्ण, /* Avoton AHCI */
	अणु PCI_VDEVICE(INTEL, 0x1f24), board_ahci पूर्ण, /* Avoton RAID */
	अणु PCI_VDEVICE(INTEL, 0x1f25), board_ahci पूर्ण, /* Avoton RAID */
	अणु PCI_VDEVICE(INTEL, 0x1f26), board_ahci पूर्ण, /* Avoton RAID */
	अणु PCI_VDEVICE(INTEL, 0x1f27), board_ahci पूर्ण, /* Avoton RAID */
	अणु PCI_VDEVICE(INTEL, 0x1f2e), board_ahci पूर्ण, /* Avoton RAID */
	अणु PCI_VDEVICE(INTEL, 0x1f2f), board_ahci पूर्ण, /* Avoton RAID */
	अणु PCI_VDEVICE(INTEL, 0x1f32), board_ahci_avn पूर्ण, /* Avoton AHCI */
	अणु PCI_VDEVICE(INTEL, 0x1f33), board_ahci_avn पूर्ण, /* Avoton AHCI */
	अणु PCI_VDEVICE(INTEL, 0x1f34), board_ahci_avn पूर्ण, /* Avoton RAID */
	अणु PCI_VDEVICE(INTEL, 0x1f35), board_ahci_avn पूर्ण, /* Avoton RAID */
	अणु PCI_VDEVICE(INTEL, 0x1f36), board_ahci_avn पूर्ण, /* Avoton RAID */
	अणु PCI_VDEVICE(INTEL, 0x1f37), board_ahci_avn पूर्ण, /* Avoton RAID */
	अणु PCI_VDEVICE(INTEL, 0x1f3e), board_ahci_avn पूर्ण, /* Avoton RAID */
	अणु PCI_VDEVICE(INTEL, 0x1f3f), board_ahci_avn पूर्ण, /* Avoton RAID */
	अणु PCI_VDEVICE(INTEL, 0x2823), board_ahci पूर्ण, /* Wellsburg RAID */
	अणु PCI_VDEVICE(INTEL, 0x2827), board_ahci पूर्ण, /* Wellsburg RAID */
	अणु PCI_VDEVICE(INTEL, 0x43d4), board_ahci पूर्ण, /* Rocket Lake PCH-H RAID */
	अणु PCI_VDEVICE(INTEL, 0x43d5), board_ahci पूर्ण, /* Rocket Lake PCH-H RAID */
	अणु PCI_VDEVICE(INTEL, 0x43d6), board_ahci पूर्ण, /* Rocket Lake PCH-H RAID */
	अणु PCI_VDEVICE(INTEL, 0x43d7), board_ahci पूर्ण, /* Rocket Lake PCH-H RAID */
	अणु PCI_VDEVICE(INTEL, 0x8d02), board_ahci पूर्ण, /* Wellsburg AHCI */
	अणु PCI_VDEVICE(INTEL, 0x8d04), board_ahci पूर्ण, /* Wellsburg RAID */
	अणु PCI_VDEVICE(INTEL, 0x8d06), board_ahci पूर्ण, /* Wellsburg RAID */
	अणु PCI_VDEVICE(INTEL, 0x8d0e), board_ahci पूर्ण, /* Wellsburg RAID */
	अणु PCI_VDEVICE(INTEL, 0x8d62), board_ahci पूर्ण, /* Wellsburg AHCI */
	अणु PCI_VDEVICE(INTEL, 0x8d64), board_ahci पूर्ण, /* Wellsburg RAID */
	अणु PCI_VDEVICE(INTEL, 0x8d66), board_ahci पूर्ण, /* Wellsburg RAID */
	अणु PCI_VDEVICE(INTEL, 0x8d6e), board_ahci पूर्ण, /* Wellsburg RAID */
	अणु PCI_VDEVICE(INTEL, 0x23a3), board_ahci पूर्ण, /* Coleto Creek AHCI */
	अणु PCI_VDEVICE(INTEL, 0x9c83), board_ahci_mobile पूर्ण, /* Wildcat LP AHCI */
	अणु PCI_VDEVICE(INTEL, 0x9c85), board_ahci_mobile पूर्ण, /* Wildcat LP RAID */
	अणु PCI_VDEVICE(INTEL, 0x9c87), board_ahci_mobile पूर्ण, /* Wildcat LP RAID */
	अणु PCI_VDEVICE(INTEL, 0x9c8f), board_ahci_mobile पूर्ण, /* Wildcat LP RAID */
	अणु PCI_VDEVICE(INTEL, 0x8c82), board_ahci पूर्ण, /* 9 Series AHCI */
	अणु PCI_VDEVICE(INTEL, 0x8c83), board_ahci_mobile पूर्ण, /* 9 Series M AHCI */
	अणु PCI_VDEVICE(INTEL, 0x8c84), board_ahci पूर्ण, /* 9 Series RAID */
	अणु PCI_VDEVICE(INTEL, 0x8c85), board_ahci_mobile पूर्ण, /* 9 Series M RAID */
	अणु PCI_VDEVICE(INTEL, 0x8c86), board_ahci पूर्ण, /* 9 Series RAID */
	अणु PCI_VDEVICE(INTEL, 0x8c87), board_ahci_mobile पूर्ण, /* 9 Series M RAID */
	अणु PCI_VDEVICE(INTEL, 0x8c8e), board_ahci पूर्ण, /* 9 Series RAID */
	अणु PCI_VDEVICE(INTEL, 0x8c8f), board_ahci_mobile पूर्ण, /* 9 Series M RAID */
	अणु PCI_VDEVICE(INTEL, 0x9d03), board_ahci_mobile पूर्ण, /* Sunrise LP AHCI */
	अणु PCI_VDEVICE(INTEL, 0x9d05), board_ahci_mobile पूर्ण, /* Sunrise LP RAID */
	अणु PCI_VDEVICE(INTEL, 0x9d07), board_ahci_mobile पूर्ण, /* Sunrise LP RAID */
	अणु PCI_VDEVICE(INTEL, 0xa102), board_ahci पूर्ण, /* Sunrise Poपूर्णांक-H AHCI */
	अणु PCI_VDEVICE(INTEL, 0xa103), board_ahci_mobile पूर्ण, /* Sunrise M AHCI */
	अणु PCI_VDEVICE(INTEL, 0xa105), board_ahci पूर्ण, /* Sunrise Poपूर्णांक-H RAID */
	अणु PCI_VDEVICE(INTEL, 0xa106), board_ahci पूर्ण, /* Sunrise Poपूर्णांक-H RAID */
	अणु PCI_VDEVICE(INTEL, 0xa107), board_ahci_mobile पूर्ण, /* Sunrise M RAID */
	अणु PCI_VDEVICE(INTEL, 0xa10f), board_ahci पूर्ण, /* Sunrise Poपूर्णांक-H RAID */
	अणु PCI_VDEVICE(INTEL, 0x2822), board_ahci पूर्ण, /* Lewisburg RAID*/
	अणु PCI_VDEVICE(INTEL, 0x2823), board_ahci पूर्ण, /* Lewisburg AHCI*/
	अणु PCI_VDEVICE(INTEL, 0x2826), board_ahci पूर्ण, /* Lewisburg RAID*/
	अणु PCI_VDEVICE(INTEL, 0x2827), board_ahci पूर्ण, /* Lewisburg RAID*/
	अणु PCI_VDEVICE(INTEL, 0xa182), board_ahci पूर्ण, /* Lewisburg AHCI*/
	अणु PCI_VDEVICE(INTEL, 0xa186), board_ahci पूर्ण, /* Lewisburg RAID*/
	अणु PCI_VDEVICE(INTEL, 0xa1d2), board_ahci पूर्ण, /* Lewisburg RAID*/
	अणु PCI_VDEVICE(INTEL, 0xa1d6), board_ahci पूर्ण, /* Lewisburg RAID*/
	अणु PCI_VDEVICE(INTEL, 0xa202), board_ahci पूर्ण, /* Lewisburg AHCI*/
	अणु PCI_VDEVICE(INTEL, 0xa206), board_ahci पूर्ण, /* Lewisburg RAID*/
	अणु PCI_VDEVICE(INTEL, 0xa252), board_ahci पूर्ण, /* Lewisburg RAID*/
	अणु PCI_VDEVICE(INTEL, 0xa256), board_ahci पूर्ण, /* Lewisburg RAID*/
	अणु PCI_VDEVICE(INTEL, 0xa356), board_ahci पूर्ण, /* Cannon Lake PCH-H RAID */
	अणु PCI_VDEVICE(INTEL, 0x06d7), board_ahci पूर्ण, /* Comet Lake-H RAID */
	अणु PCI_VDEVICE(INTEL, 0xa386), board_ahci पूर्ण, /* Comet Lake PCH-V RAID */
	अणु PCI_VDEVICE(INTEL, 0x0f22), board_ahci_mobile पूर्ण, /* Bay Trail AHCI */
	अणु PCI_VDEVICE(INTEL, 0x0f23), board_ahci_mobile पूर्ण, /* Bay Trail AHCI */
	अणु PCI_VDEVICE(INTEL, 0x22a3), board_ahci_mobile पूर्ण, /* Cherry Tr. AHCI */
	अणु PCI_VDEVICE(INTEL, 0x5ae3), board_ahci_mobile पूर्ण, /* ApolloLake AHCI */
	अणु PCI_VDEVICE(INTEL, 0x34d3), board_ahci_mobile पूर्ण, /* Ice Lake LP AHCI */
	अणु PCI_VDEVICE(INTEL, 0x02d3), board_ahci_mobile पूर्ण, /* Comet Lake PCH-U AHCI */
	अणु PCI_VDEVICE(INTEL, 0x02d7), board_ahci_mobile पूर्ण, /* Comet Lake PCH RAID */

	/* JMicron 360/1/3/5/6, match class to aव्योम IDE function */
	अणु PCI_VENDOR_ID_JMICRON, PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID,
	  PCI_CLASS_STORAGE_SATA_AHCI, 0xffffff, board_ahci_ign_अगरerr पूर्ण,
	/* JMicron 362B and 362C have an AHCI function with IDE class code */
	अणु PCI_VDEVICE(JMICRON, 0x2362), board_ahci_ign_अगरerr पूर्ण,
	अणु PCI_VDEVICE(JMICRON, 0x236f), board_ahci_ign_अगरerr पूर्ण,
	/* May need to update quirk_jmicron_async_suspend() क्रम additions */

	/* ATI */
	अणु PCI_VDEVICE(ATI, 0x4380), board_ahci_sb600 पूर्ण, /* ATI SB600 */
	अणु PCI_VDEVICE(ATI, 0x4390), board_ahci_sb700 पूर्ण, /* ATI SB700/800 */
	अणु PCI_VDEVICE(ATI, 0x4391), board_ahci_sb700 पूर्ण, /* ATI SB700/800 */
	अणु PCI_VDEVICE(ATI, 0x4392), board_ahci_sb700 पूर्ण, /* ATI SB700/800 */
	अणु PCI_VDEVICE(ATI, 0x4393), board_ahci_sb700 पूर्ण, /* ATI SB700/800 */
	अणु PCI_VDEVICE(ATI, 0x4394), board_ahci_sb700 पूर्ण, /* ATI SB700/800 */
	अणु PCI_VDEVICE(ATI, 0x4395), board_ahci_sb700 पूर्ण, /* ATI SB700/800 */

	/* Amazon's Annapurna Lअसल support */
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMAZON_ANNAPURNA_LABS, 0x0031),
		.class = PCI_CLASS_STORAGE_SATA_AHCI,
		.class_mask = 0xffffff,
		board_ahci_al पूर्ण,
	/* AMD */
	अणु PCI_VDEVICE(AMD, 0x7800), board_ahci पूर्ण, /* AMD Hudson-2 */
	अणु PCI_VDEVICE(AMD, 0x7900), board_ahci पूर्ण, /* AMD CZ */
	/* AMD is using RAID class only क्रम ahci controllers */
	अणु PCI_VENDOR_ID_AMD, PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID,
	  PCI_CLASS_STORAGE_RAID << 8, 0xffffff, board_ahci पूर्ण,

	/* VIA */
	अणु PCI_VDEVICE(VIA, 0x3349), board_ahci_vt8251 पूर्ण, /* VIA VT8251 */
	अणु PCI_VDEVICE(VIA, 0x6287), board_ahci_vt8251 पूर्ण, /* VIA VT8251 */

	/* NVIDIA */
	अणु PCI_VDEVICE(NVIDIA, 0x044c), board_ahci_mcp65 पूर्ण,	/* MCP65 */
	अणु PCI_VDEVICE(NVIDIA, 0x044d), board_ahci_mcp65 पूर्ण,	/* MCP65 */
	अणु PCI_VDEVICE(NVIDIA, 0x044e), board_ahci_mcp65 पूर्ण,	/* MCP65 */
	अणु PCI_VDEVICE(NVIDIA, 0x044f), board_ahci_mcp65 पूर्ण,	/* MCP65 */
	अणु PCI_VDEVICE(NVIDIA, 0x045c), board_ahci_mcp65 पूर्ण,	/* MCP65 */
	अणु PCI_VDEVICE(NVIDIA, 0x045d), board_ahci_mcp65 पूर्ण,	/* MCP65 */
	अणु PCI_VDEVICE(NVIDIA, 0x045e), board_ahci_mcp65 पूर्ण,	/* MCP65 */
	अणु PCI_VDEVICE(NVIDIA, 0x045f), board_ahci_mcp65 पूर्ण,	/* MCP65 */
	अणु PCI_VDEVICE(NVIDIA, 0x0550), board_ahci_mcp67 पूर्ण,	/* MCP67 */
	अणु PCI_VDEVICE(NVIDIA, 0x0551), board_ahci_mcp67 पूर्ण,	/* MCP67 */
	अणु PCI_VDEVICE(NVIDIA, 0x0552), board_ahci_mcp67 पूर्ण,	/* MCP67 */
	अणु PCI_VDEVICE(NVIDIA, 0x0553), board_ahci_mcp67 पूर्ण,	/* MCP67 */
	अणु PCI_VDEVICE(NVIDIA, 0x0554), board_ahci_mcp67 पूर्ण,	/* MCP67 */
	अणु PCI_VDEVICE(NVIDIA, 0x0555), board_ahci_mcp67 पूर्ण,	/* MCP67 */
	अणु PCI_VDEVICE(NVIDIA, 0x0556), board_ahci_mcp67 पूर्ण,	/* MCP67 */
	अणु PCI_VDEVICE(NVIDIA, 0x0557), board_ahci_mcp67 पूर्ण,	/* MCP67 */
	अणु PCI_VDEVICE(NVIDIA, 0x0558), board_ahci_mcp67 पूर्ण,	/* MCP67 */
	अणु PCI_VDEVICE(NVIDIA, 0x0559), board_ahci_mcp67 पूर्ण,	/* MCP67 */
	अणु PCI_VDEVICE(NVIDIA, 0x055a), board_ahci_mcp67 पूर्ण,	/* MCP67 */
	अणु PCI_VDEVICE(NVIDIA, 0x055b), board_ahci_mcp67 पूर्ण,	/* MCP67 */
	अणु PCI_VDEVICE(NVIDIA, 0x0580), board_ahci_mcp_linux पूर्ण,	/* Linux ID */
	अणु PCI_VDEVICE(NVIDIA, 0x0581), board_ahci_mcp_linux पूर्ण,	/* Linux ID */
	अणु PCI_VDEVICE(NVIDIA, 0x0582), board_ahci_mcp_linux पूर्ण,	/* Linux ID */
	अणु PCI_VDEVICE(NVIDIA, 0x0583), board_ahci_mcp_linux पूर्ण,	/* Linux ID */
	अणु PCI_VDEVICE(NVIDIA, 0x0584), board_ahci_mcp_linux पूर्ण,	/* Linux ID */
	अणु PCI_VDEVICE(NVIDIA, 0x0585), board_ahci_mcp_linux पूर्ण,	/* Linux ID */
	अणु PCI_VDEVICE(NVIDIA, 0x0586), board_ahci_mcp_linux पूर्ण,	/* Linux ID */
	अणु PCI_VDEVICE(NVIDIA, 0x0587), board_ahci_mcp_linux पूर्ण,	/* Linux ID */
	अणु PCI_VDEVICE(NVIDIA, 0x0588), board_ahci_mcp_linux पूर्ण,	/* Linux ID */
	अणु PCI_VDEVICE(NVIDIA, 0x0589), board_ahci_mcp_linux पूर्ण,	/* Linux ID */
	अणु PCI_VDEVICE(NVIDIA, 0x058a), board_ahci_mcp_linux पूर्ण,	/* Linux ID */
	अणु PCI_VDEVICE(NVIDIA, 0x058b), board_ahci_mcp_linux पूर्ण,	/* Linux ID */
	अणु PCI_VDEVICE(NVIDIA, 0x058c), board_ahci_mcp_linux पूर्ण,	/* Linux ID */
	अणु PCI_VDEVICE(NVIDIA, 0x058d), board_ahci_mcp_linux पूर्ण,	/* Linux ID */
	अणु PCI_VDEVICE(NVIDIA, 0x058e), board_ahci_mcp_linux पूर्ण,	/* Linux ID */
	अणु PCI_VDEVICE(NVIDIA, 0x058f), board_ahci_mcp_linux पूर्ण,	/* Linux ID */
	अणु PCI_VDEVICE(NVIDIA, 0x07f0), board_ahci_mcp73 पूर्ण,	/* MCP73 */
	अणु PCI_VDEVICE(NVIDIA, 0x07f1), board_ahci_mcp73 पूर्ण,	/* MCP73 */
	अणु PCI_VDEVICE(NVIDIA, 0x07f2), board_ahci_mcp73 पूर्ण,	/* MCP73 */
	अणु PCI_VDEVICE(NVIDIA, 0x07f3), board_ahci_mcp73 पूर्ण,	/* MCP73 */
	अणु PCI_VDEVICE(NVIDIA, 0x07f4), board_ahci_mcp73 पूर्ण,	/* MCP73 */
	अणु PCI_VDEVICE(NVIDIA, 0x07f5), board_ahci_mcp73 पूर्ण,	/* MCP73 */
	अणु PCI_VDEVICE(NVIDIA, 0x07f6), board_ahci_mcp73 पूर्ण,	/* MCP73 */
	अणु PCI_VDEVICE(NVIDIA, 0x07f7), board_ahci_mcp73 पूर्ण,	/* MCP73 */
	अणु PCI_VDEVICE(NVIDIA, 0x07f8), board_ahci_mcp73 पूर्ण,	/* MCP73 */
	अणु PCI_VDEVICE(NVIDIA, 0x07f9), board_ahci_mcp73 पूर्ण,	/* MCP73 */
	अणु PCI_VDEVICE(NVIDIA, 0x07fa), board_ahci_mcp73 पूर्ण,	/* MCP73 */
	अणु PCI_VDEVICE(NVIDIA, 0x07fb), board_ahci_mcp73 पूर्ण,	/* MCP73 */
	अणु PCI_VDEVICE(NVIDIA, 0x0ad0), board_ahci_mcp77 पूर्ण,	/* MCP77 */
	अणु PCI_VDEVICE(NVIDIA, 0x0ad1), board_ahci_mcp77 पूर्ण,	/* MCP77 */
	अणु PCI_VDEVICE(NVIDIA, 0x0ad2), board_ahci_mcp77 पूर्ण,	/* MCP77 */
	अणु PCI_VDEVICE(NVIDIA, 0x0ad3), board_ahci_mcp77 पूर्ण,	/* MCP77 */
	अणु PCI_VDEVICE(NVIDIA, 0x0ad4), board_ahci_mcp77 पूर्ण,	/* MCP77 */
	अणु PCI_VDEVICE(NVIDIA, 0x0ad5), board_ahci_mcp77 पूर्ण,	/* MCP77 */
	अणु PCI_VDEVICE(NVIDIA, 0x0ad6), board_ahci_mcp77 पूर्ण,	/* MCP77 */
	अणु PCI_VDEVICE(NVIDIA, 0x0ad7), board_ahci_mcp77 पूर्ण,	/* MCP77 */
	अणु PCI_VDEVICE(NVIDIA, 0x0ad8), board_ahci_mcp77 पूर्ण,	/* MCP77 */
	अणु PCI_VDEVICE(NVIDIA, 0x0ad9), board_ahci_mcp77 पूर्ण,	/* MCP77 */
	अणु PCI_VDEVICE(NVIDIA, 0x0ada), board_ahci_mcp77 पूर्ण,	/* MCP77 */
	अणु PCI_VDEVICE(NVIDIA, 0x0adb), board_ahci_mcp77 पूर्ण,	/* MCP77 */
	अणु PCI_VDEVICE(NVIDIA, 0x0ab4), board_ahci_mcp79 पूर्ण,	/* MCP79 */
	अणु PCI_VDEVICE(NVIDIA, 0x0ab5), board_ahci_mcp79 पूर्ण,	/* MCP79 */
	अणु PCI_VDEVICE(NVIDIA, 0x0ab6), board_ahci_mcp79 पूर्ण,	/* MCP79 */
	अणु PCI_VDEVICE(NVIDIA, 0x0ab7), board_ahci_mcp79 पूर्ण,	/* MCP79 */
	अणु PCI_VDEVICE(NVIDIA, 0x0ab8), board_ahci_mcp79 पूर्ण,	/* MCP79 */
	अणु PCI_VDEVICE(NVIDIA, 0x0ab9), board_ahci_mcp79 पूर्ण,	/* MCP79 */
	अणु PCI_VDEVICE(NVIDIA, 0x0aba), board_ahci_mcp79 पूर्ण,	/* MCP79 */
	अणु PCI_VDEVICE(NVIDIA, 0x0abb), board_ahci_mcp79 पूर्ण,	/* MCP79 */
	अणु PCI_VDEVICE(NVIDIA, 0x0abc), board_ahci_mcp79 पूर्ण,	/* MCP79 */
	अणु PCI_VDEVICE(NVIDIA, 0x0abd), board_ahci_mcp79 पूर्ण,	/* MCP79 */
	अणु PCI_VDEVICE(NVIDIA, 0x0abe), board_ahci_mcp79 पूर्ण,	/* MCP79 */
	अणु PCI_VDEVICE(NVIDIA, 0x0abf), board_ahci_mcp79 पूर्ण,	/* MCP79 */
	अणु PCI_VDEVICE(NVIDIA, 0x0d84), board_ahci_mcp89 पूर्ण,	/* MCP89 */
	अणु PCI_VDEVICE(NVIDIA, 0x0d85), board_ahci_mcp89 पूर्ण,	/* MCP89 */
	अणु PCI_VDEVICE(NVIDIA, 0x0d86), board_ahci_mcp89 पूर्ण,	/* MCP89 */
	अणु PCI_VDEVICE(NVIDIA, 0x0d87), board_ahci_mcp89 पूर्ण,	/* MCP89 */
	अणु PCI_VDEVICE(NVIDIA, 0x0d88), board_ahci_mcp89 पूर्ण,	/* MCP89 */
	अणु PCI_VDEVICE(NVIDIA, 0x0d89), board_ahci_mcp89 पूर्ण,	/* MCP89 */
	अणु PCI_VDEVICE(NVIDIA, 0x0d8a), board_ahci_mcp89 पूर्ण,	/* MCP89 */
	अणु PCI_VDEVICE(NVIDIA, 0x0d8b), board_ahci_mcp89 पूर्ण,	/* MCP89 */
	अणु PCI_VDEVICE(NVIDIA, 0x0d8c), board_ahci_mcp89 पूर्ण,	/* MCP89 */
	अणु PCI_VDEVICE(NVIDIA, 0x0d8d), board_ahci_mcp89 पूर्ण,	/* MCP89 */
	अणु PCI_VDEVICE(NVIDIA, 0x0d8e), board_ahci_mcp89 पूर्ण,	/* MCP89 */
	अणु PCI_VDEVICE(NVIDIA, 0x0d8f), board_ahci_mcp89 पूर्ण,	/* MCP89 */

	/* SiS */
	अणु PCI_VDEVICE(SI, 0x1184), board_ahci पूर्ण,		/* SiS 966 */
	अणु PCI_VDEVICE(SI, 0x1185), board_ahci पूर्ण,		/* SiS 968 */
	अणु PCI_VDEVICE(SI, 0x0186), board_ahci पूर्ण,		/* SiS 968 */

	/* ST Microelectronics */
	अणु PCI_VDEVICE(STMICRO, 0xCC06), board_ahci पूर्ण,		/* ST ConneXt */

	/* Marvell */
	अणु PCI_VDEVICE(MARVELL, 0x6145), board_ahci_mv पूर्ण,	/* 6145 */
	अणु PCI_VDEVICE(MARVELL, 0x6121), board_ahci_mv पूर्ण,	/* 6121 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL_EXT, 0x9123),
	  .class = PCI_CLASS_STORAGE_SATA_AHCI,
	  .class_mask = 0xffffff,
	  .driver_data = board_ahci_yes_fbs पूर्ण,			/* 88se9128 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL_EXT, 0x9125),
	  .driver_data = board_ahci_yes_fbs पूर्ण,			/* 88se9125 */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_MARVELL_EXT, 0x9178,
			 PCI_VENDOR_ID_MARVELL_EXT, 0x9170),
	  .driver_data = board_ahci_yes_fbs पूर्ण,			/* 88se9170 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL_EXT, 0x917a),
	  .driver_data = board_ahci_yes_fbs पूर्ण,			/* 88se9172 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL_EXT, 0x9172),
	  .driver_data = board_ahci_yes_fbs पूर्ण,			/* 88se9182 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL_EXT, 0x9182),
	  .driver_data = board_ahci_yes_fbs पूर्ण,			/* 88se9172 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL_EXT, 0x9192),
	  .driver_data = board_ahci_yes_fbs पूर्ण,			/* 88se9172 on some Gigabyte */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL_EXT, 0x91a0),
	  .driver_data = board_ahci_yes_fbs पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL_EXT, 0x91a2), 	/* 88se91a2 */
	  .driver_data = board_ahci_yes_fbs पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL_EXT, 0x91a3),
	  .driver_data = board_ahci_yes_fbs पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL_EXT, 0x9230),
	  .driver_data = board_ahci_yes_fbs पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_TTI, 0x0642), /* highpoपूर्णांक rocketraid 642L */
	  .driver_data = board_ahci_yes_fbs पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_TTI, 0x0645), /* highpoपूर्णांक rocketraid 644L */
	  .driver_data = board_ahci_yes_fbs पूर्ण,

	/* Promise */
	अणु PCI_VDEVICE(PROMISE, 0x3f20), board_ahci पूर्ण,	/* PDC42819 */
	अणु PCI_VDEVICE(PROMISE, 0x3781), board_ahci पूर्ण,   /* FastTrak TX8660 ahci-mode */

	/* Asmedia */
	अणु PCI_VDEVICE(ASMEDIA, 0x0601), board_ahci पूर्ण,	/* ASM1060 */
	अणु PCI_VDEVICE(ASMEDIA, 0x0602), board_ahci पूर्ण,	/* ASM1060 */
	अणु PCI_VDEVICE(ASMEDIA, 0x0611), board_ahci पूर्ण,	/* ASM1061 */
	अणु PCI_VDEVICE(ASMEDIA, 0x0612), board_ahci पूर्ण,	/* ASM1062 */
	अणु PCI_VDEVICE(ASMEDIA, 0x0621), board_ahci पूर्ण,   /* ASM1061R */
	अणु PCI_VDEVICE(ASMEDIA, 0x0622), board_ahci पूर्ण,   /* ASM1062R */

	/*
	 * Samsung SSDs found on some macbooks.  NCQ बार out अगर MSI is
	 * enabled.  https://bugzilla.kernel.org/show_bug.cgi?id=60731
	 */
	अणु PCI_VDEVICE(SAMSUNG, 0x1600), board_ahci_nomsi पूर्ण,
	अणु PCI_VDEVICE(SAMSUNG, 0xa800), board_ahci_nomsi पूर्ण,

	/* Enmotus */
	अणु PCI_DEVICE(0x1c44, 0x8000), board_ahci पूर्ण,

	/* Loongson */
	अणु PCI_VDEVICE(LOONGSON, 0x7a08), board_ahci पूर्ण,

	/* Generic, PCI class code क्रम AHCI */
	अणु PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID,
	  PCI_CLASS_STORAGE_SATA_AHCI, 0xffffff, board_ahci पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops ahci_pci_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ahci_pci_device_suspend, ahci_pci_device_resume)
	SET_RUNTIME_PM_OPS(ahci_pci_device_runसमय_suspend,
			   ahci_pci_device_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा pci_driver ahci_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= ahci_pci_tbl,
	.probe			= ahci_init_one,
	.हटाओ			= ahci_हटाओ_one,
	.shutकरोwn		= ahci_shutकरोwn_one,
	.driver = अणु
		.pm		= &ahci_pci_pm_ops,
	पूर्ण,
पूर्ण;

#अगर IS_ENABLED(CONFIG_PATA_MARVELL)
अटल पूर्णांक marvell_enable;
#अन्यथा
अटल पूर्णांक marvell_enable = 1;
#पूर्ण_अगर
module_param(marvell_enable, पूर्णांक, 0644);
MODULE_PARM_DESC(marvell_enable, "Marvell SATA via AHCI (1 = enabled)");

अटल पूर्णांक mobile_lpm_policy = -1;
module_param(mobile_lpm_policy, पूर्णांक, 0644);
MODULE_PARM_DESC(mobile_lpm_policy, "Default LPM policy for mobile chipsets");

अटल व्योम ahci_pci_save_initial_config(काष्ठा pci_dev *pdev,
					 काष्ठा ahci_host_priv *hpriv)
अणु
	अगर (pdev->venकरोr == PCI_VENDOR_ID_JMICRON && pdev->device == 0x2361) अणु
		dev_info(&pdev->dev, "JMB361 has only one port\n");
		hpriv->क्रमce_port_map = 1;
	पूर्ण

	/*
	 * Temporary Marvell 6145 hack: PATA port presence
	 * is निश्चितed through the standard AHCI port
	 * presence रेजिस्टर, as bit 4 (counting from 0)
	 */
	अगर (hpriv->flags & AHCI_HFLAG_MV_PATA) अणु
		अगर (pdev->device == 0x6121)
			hpriv->mask_port_map = 0x3;
		अन्यथा
			hpriv->mask_port_map = 0xf;
		dev_info(&pdev->dev,
			  "Disabling your PATA port. Use the boot option 'ahci.marvell_enable=0' to avoid this.\n");
	पूर्ण

	ahci_save_initial_config(&pdev->dev, hpriv);
पूर्ण

अटल व्योम ahci_pci_init_controller(काष्ठा ata_host *host)
अणु
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	काष्ठा pci_dev *pdev = to_pci_dev(host->dev);
	व्योम __iomem *port_mmio;
	u32 पंचांगp;
	पूर्णांक mv;

	अगर (hpriv->flags & AHCI_HFLAG_MV_PATA) अणु
		अगर (pdev->device == 0x6121)
			mv = 2;
		अन्यथा
			mv = 4;
		port_mmio = __ahci_port_base(host, mv);

		ग_लिखोl(0, port_mmio + PORT_IRQ_MASK);

		/* clear port IRQ */
		पंचांगp = पढ़ोl(port_mmio + PORT_IRQ_STAT);
		VPRINTK("PORT_IRQ_STAT 0x%x\n", पंचांगp);
		अगर (पंचांगp)
			ग_लिखोl(पंचांगp, port_mmio + PORT_IRQ_STAT);
	पूर्ण

	ahci_init_controller(host);
पूर्ण

अटल पूर्णांक ahci_vt8251_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
				 अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	bool online;
	पूर्णांक rc;

	DPRINTK("ENTER\n");

	hpriv->stop_engine(ap);

	rc = sata_link_hardreset(link, sata_ehc_deb_timing(&link->eh_context),
				 deadline, &online, शून्य);

	hpriv->start_engine(ap);

	DPRINTK("EXIT, rc=%d, class=%u\n", rc, *class);

	/* vt8251 करोesn't clear BSY on signature FIS reception,
	 * request follow-up softreset.
	 */
	वापस online ? -EAGAIN : rc;
पूर्ण

अटल पूर्णांक ahci_p5wdh_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
				अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	u8 *d2h_fis = pp->rx_fis + RX_FIS_D2H_REG;
	काष्ठा ata_taskfile tf;
	bool online;
	पूर्णांक rc;

	hpriv->stop_engine(ap);

	/* clear D2H reception area to properly रुको क्रम D2H FIS */
	ata_tf_init(link->device, &tf);
	tf.command = ATA_BUSY;
	ata_tf_to_fis(&tf, 0, 0, d2h_fis);

	rc = sata_link_hardreset(link, sata_ehc_deb_timing(&link->eh_context),
				 deadline, &online, शून्य);

	hpriv->start_engine(ap);

	/* The pseuकरो configuration device on SIMG4726 attached to
	 * ASUS P5W-DH Deluxe करोesn't send signature FIS after
	 * hardreset अगर no device is attached to the first करोwnstream
	 * port && the pseuकरो device locks up on SRST w/ PMP==0.  To
	 * work around this, रुको क्रम !BSY only briefly.  If BSY isn't
	 * cleared, perक्रमm CLO and proceed to IDENTIFY (achieved by
	 * ATA_LFLAG_NO_SRST and ATA_LFLAG_ASSUME_ATA).
	 *
	 * Wait क्रम two seconds.  Devices attached to करोwnstream port
	 * which can't process the following IDENTIFY after this will
	 * have to be reset again.  For most हालs, this should
	 * suffice जबतक making probing snappish enough.
	 */
	अगर (online) अणु
		rc = ata_रुको_after_reset(link, jअगरfies + 2 * HZ,
					  ahci_check_पढ़ोy);
		अगर (rc)
			ahci_kick_engine(ap);
	पूर्ण
	वापस rc;
पूर्ण

/*
 * ahci_avn_hardreset - attempt more aggressive recovery of Avoton ports.
 *
 * It has been observed with some SSDs that the timing of events in the
 * link synchronization phase can leave the port in a state that can not
 * be recovered by a SATA-hard-reset alone.  The failing signature is
 * SStatus.DET stuck at 1 ("Device presence detected but Phy
 * communication not established").  It was found that unloading and
 * reloading the driver when this problem occurs allows the drive
 * connection to be recovered (DET advanced to 0x3).  The critical
 * component of reloading the driver is that the port state machines are
 * reset by bouncing "port enable" in the AHCI PCS configuration
 * रेजिस्टर.  So, reproduce that effect by bouncing a port whenever we
 * see DET==1 after a reset.
 */
अटल पूर्णांक ahci_avn_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			      अचिन्हित दीर्घ deadline)
अणु
	स्थिर अचिन्हित दीर्घ *timing = sata_ehc_deb_timing(&link->eh_context);
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	u8 *d2h_fis = pp->rx_fis + RX_FIS_D2H_REG;
	अचिन्हित दीर्घ पंचांगo = deadline - jअगरfies;
	काष्ठा ata_taskfile tf;
	bool online;
	पूर्णांक rc, i;

	DPRINTK("ENTER\n");

	hpriv->stop_engine(ap);

	क्रम (i = 0; i < 2; i++) अणु
		u16 val;
		u32 sstatus;
		पूर्णांक port = ap->port_no;
		काष्ठा ata_host *host = ap->host;
		काष्ठा pci_dev *pdev = to_pci_dev(host->dev);

		/* clear D2H reception area to properly रुको क्रम D2H FIS */
		ata_tf_init(link->device, &tf);
		tf.command = ATA_BUSY;
		ata_tf_to_fis(&tf, 0, 0, d2h_fis);

		rc = sata_link_hardreset(link, timing, deadline, &online,
				ahci_check_पढ़ोy);

		अगर (sata_scr_पढ़ो(link, SCR_STATUS, &sstatus) != 0 ||
				(sstatus & 0xf) != 1)
			अवरोध;

		ata_link_info(link,  "avn bounce port%d\n", port);

		pci_पढ़ो_config_word(pdev, 0x92, &val);
		val &= ~(1 << port);
		pci_ग_लिखो_config_word(pdev, 0x92, val);
		ata_msleep(ap, 1000);
		val |= 1 << port;
		pci_ग_लिखो_config_word(pdev, 0x92, val);
		deadline += पंचांगo;
	पूर्ण

	hpriv->start_engine(ap);

	अगर (online)
		*class = ahci_dev_classअगरy(ap);

	DPRINTK("EXIT, rc=%d, class=%u\n", rc, *class);
	वापस rc;
पूर्ण


#अगर_घोषित CONFIG_PM
अटल व्योम ahci_pci_disable_पूर्णांकerrupts(काष्ठा ata_host *host)
अणु
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *mmio = hpriv->mmio;
	u32 ctl;

	/* AHCI spec rev1.1 section 8.3.3:
	 * Software must disable पूर्णांकerrupts prior to requesting a
	 * transition of the HBA to D3 state.
	 */
	ctl = पढ़ोl(mmio + HOST_CTL);
	ctl &= ~HOST_IRQ_EN;
	ग_लिखोl(ctl, mmio + HOST_CTL);
	पढ़ोl(mmio + HOST_CTL); /* flush */
पूर्ण

अटल पूर्णांक ahci_pci_device_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा ata_host *host = pci_get_drvdata(pdev);

	ahci_pci_disable_पूर्णांकerrupts(host);
	वापस 0;
पूर्ण

अटल पूर्णांक ahci_pci_device_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ahci_reset_controller(host);
	अगर (rc)
		वापस rc;
	ahci_pci_init_controller(host);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ahci_pci_device_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;

	अगर (hpriv->flags & AHCI_HFLAG_NO_SUSPEND) अणु
		dev_err(&pdev->dev,
			"BIOS update required for suspend/resume\n");
		वापस -EIO;
	पूर्ण

	ahci_pci_disable_पूर्णांकerrupts(host);
	वापस ata_host_suspend(host, PMSG_SUSPEND);
पूर्ण

अटल पूर्णांक ahci_pci_device_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	/* Apple BIOS helpfully mangles the रेजिस्टरs on resume */
	अगर (is_mcp89_apple(pdev))
		ahci_mcp89_apple_enable(pdev);

	अगर (pdev->dev.घातer.घातer_state.event == PM_EVENT_SUSPEND) अणु
		rc = ahci_reset_controller(host);
		अगर (rc)
			वापस rc;

		ahci_pci_init_controller(host);
	पूर्ण

	ata_host_resume(host);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक ahci_configure_dma_masks(काष्ठा pci_dev *pdev, पूर्णांक using_dac)
अणु
	स्थिर पूर्णांक dma_bits = using_dac ? 64 : 32;
	पूर्णांक rc;

	/*
	 * If the device fixup alपढ़ोy set the dma_mask to some non-standard
	 * value, करोn't extend it here. This happens on STA2X11, क्रम example.
	 *
	 * XXX: manipulating the DMA mask from platक्रमm code is completely
	 * bogus, platक्रमm code should use dev->bus_dma_limit instead..
	 */
	अगर (pdev->dma_mask && pdev->dma_mask < DMA_BIT_MASK(32))
		वापस 0;

	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(dma_bits));
	अगर (rc)
		dev_err(&pdev->dev, "DMA enable failed\n");
	वापस rc;
पूर्ण

अटल व्योम ahci_pci_prपूर्णांक_info(काष्ठा ata_host *host)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(host->dev);
	u16 cc;
	स्थिर अक्षर *scc_s;

	pci_पढ़ो_config_word(pdev, 0x0a, &cc);
	अगर (cc == PCI_CLASS_STORAGE_IDE)
		scc_s = "IDE";
	अन्यथा अगर (cc == PCI_CLASS_STORAGE_SATA)
		scc_s = "SATA";
	अन्यथा अगर (cc == PCI_CLASS_STORAGE_RAID)
		scc_s = "RAID";
	अन्यथा
		scc_s = "unknown";

	ahci_prपूर्णांक_info(host, scc_s);
पूर्ण

/* On ASUS P5W DH Deluxe, the second port of PCI device 00:1f.2 is
 * hardwired to on-board SIMG 4726.  The chipset is ICH8 and करोesn't
 * support PMP and the 4726 either directly exports the device
 * attached to the first करोwnstream port or acts as a hardware storage
 * controller and emulate a single ATA device (can be RAID 0/1 or some
 * other configuration).
 *
 * When there's no device attached to the first करोwnstream port of the
 * 4726, "Config Disk" appears, which is a pseuकरो ATA device to
 * configure the 4726.  However, ATA emulation of the device is very
 * lame.  It करोesn't send signature D2H Reg FIS after the initial
 * hardreset, pukes on SRST w/ PMP==0 and has bunch of other issues.
 *
 * The following function works around the problem by always using
 * hardreset on the port and not depending on receiving signature FIS
 * afterward.  If signature FIS isn't received soon, ATA class is
 * assumed without follow-up softreset.
 */
अटल व्योम ahci_p5wdh_workaround(काष्ठा ata_host *host)
अणु
	अटल स्थिर काष्ठा dmi_प्रणाली_id sysids[] = अणु
		अणु
			.ident = "P5W DH Deluxe",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR,
					  "ASUSTEK COMPUTER INC"),
				DMI_MATCH(DMI_PRODUCT_NAME, "P5W DH Deluxe"),
			पूर्ण,
		पूर्ण,
		अणु पूर्ण
	पूर्ण;
	काष्ठा pci_dev *pdev = to_pci_dev(host->dev);

	अगर (pdev->bus->number == 0 && pdev->devfn == PCI_DEVFN(0x1f, 2) &&
	    dmi_check_प्रणाली(sysids)) अणु
		काष्ठा ata_port *ap = host->ports[1];

		dev_info(&pdev->dev,
			 "enabling ASUS P5W DH Deluxe on-board SIMG4726 workaround\n");

		ap->ops = &ahci_p5wdh_ops;
		ap->link.flags |= ATA_LFLAG_NO_SRST | ATA_LFLAG_ASSUME_ATA;
	पूर्ण
पूर्ण

/*
 * Macbook7,1 firmware क्रमcibly disables MCP89 AHCI and changes PCI ID when
 * booting in BIOS compatibility mode.  We restore the रेजिस्टरs but not ID.
 */
अटल व्योम ahci_mcp89_apple_enable(काष्ठा pci_dev *pdev)
अणु
	u32 val;

	prपूर्णांकk(KERN_INFO "ahci: enabling MCP89 AHCI mode\n");

	pci_पढ़ो_config_dword(pdev, 0xf8, &val);
	val |= 1 << 0x1b;
	/* the following changes the device ID, but appears not to affect function */
	/* val = (val & ~0xf0000000) | 0x80000000; */
	pci_ग_लिखो_config_dword(pdev, 0xf8, val);

	pci_पढ़ो_config_dword(pdev, 0x54c, &val);
	val |= 1 << 0xc;
	pci_ग_लिखो_config_dword(pdev, 0x54c, val);

	pci_पढ़ो_config_dword(pdev, 0x4a4, &val);
	val &= 0xff;
	val |= 0x01060100;
	pci_ग_लिखो_config_dword(pdev, 0x4a4, val);

	pci_पढ़ो_config_dword(pdev, 0x54c, &val);
	val &= ~(1 << 0xc);
	pci_ग_लिखो_config_dword(pdev, 0x54c, val);

	pci_पढ़ो_config_dword(pdev, 0xf8, &val);
	val &= ~(1 << 0x1b);
	pci_ग_लिखो_config_dword(pdev, 0xf8, val);
पूर्ण

अटल bool is_mcp89_apple(काष्ठा pci_dev *pdev)
अणु
	वापस pdev->venकरोr == PCI_VENDOR_ID_NVIDIA &&
		pdev->device == PCI_DEVICE_ID_NVIDIA_NFORCE_MCP89_SATA &&
		pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_APPLE &&
		pdev->subप्रणाली_device == 0xcb89;
पूर्ण

/* only some SB600 ahci controllers can करो 64bit DMA */
अटल bool ahci_sb600_enable_64bit(काष्ठा pci_dev *pdev)
अणु
	अटल स्थिर काष्ठा dmi_प्रणाली_id sysids[] = अणु
		/*
		 * The oldest version known to be broken is 0901 and
		 * working is 1501 which was released on 2007-10-26.
		 * Enable 64bit DMA on 1501 and anything newer.
		 *
		 * Please पढ़ो bko#9412 क्रम more info.
		 */
		अणु
			.ident = "ASUS M2A-VM",
			.matches = अणु
				DMI_MATCH(DMI_BOARD_VENDOR,
					  "ASUSTeK Computer INC."),
				DMI_MATCH(DMI_BOARD_NAME, "M2A-VM"),
			पूर्ण,
			.driver_data = "20071026",	/* yyyymmdd */
		पूर्ण,
		/*
		 * All BIOS versions क्रम the MSI K9A2 Platinum (MS-7376)
		 * support 64bit DMA.
		 *
		 * BIOS versions earlier than 1.5 had the Manufacturer DMI
		 * fields as "MICRO-STAR INTERANTIONAL CO.,LTD".
		 * This spelling mistake was fixed in BIOS version 1.5, so
		 * 1.5 and later have the Manufacturer as
		 * "MICRO-STAR INTERNATIONAL CO.,LTD".
		 * So try to match on DMI_BOARD_VENDOR of "MICRO-STAR INTER".
		 *
		 * BIOS versions earlier than 1.9 had a Board Product Name
		 * DMI field of "MS-7376". This was changed to be
		 * "K9A2 Platinum (MS-7376)" in version 1.9, but we can still
		 * match on DMI_BOARD_NAME of "MS-7376".
		 */
		अणु
			.ident = "MSI K9A2 Platinum",
			.matches = अणु
				DMI_MATCH(DMI_BOARD_VENDOR,
					  "MICRO-STAR INTER"),
				DMI_MATCH(DMI_BOARD_NAME, "MS-7376"),
			पूर्ण,
		पूर्ण,
		/*
		 * All BIOS versions क्रम the MSI K9AGM2 (MS-7327) support
		 * 64bit DMA.
		 *
		 * This board also had the typo mentioned above in the
		 * Manufacturer DMI field (fixed in BIOS version 1.5), so
		 * match on DMI_BOARD_VENDOR of "MICRO-STAR INTER" again.
		 */
		अणु
			.ident = "MSI K9AGM2",
			.matches = अणु
				DMI_MATCH(DMI_BOARD_VENDOR,
					  "MICRO-STAR INTER"),
				DMI_MATCH(DMI_BOARD_NAME, "MS-7327"),
			पूर्ण,
		पूर्ण,
		/*
		 * All BIOS versions क्रम the Asus M3A support 64bit DMA.
		 * (all release versions from 0301 to 1206 were tested)
		 */
		अणु
			.ident = "ASUS M3A",
			.matches = अणु
				DMI_MATCH(DMI_BOARD_VENDOR,
					  "ASUSTeK Computer INC."),
				DMI_MATCH(DMI_BOARD_NAME, "M3A"),
			पूर्ण,
		पूर्ण,
		अणु पूर्ण
	पूर्ण;
	स्थिर काष्ठा dmi_प्रणाली_id *match;
	पूर्णांक year, month, date;
	अक्षर buf[9];

	match = dmi_first_match(sysids);
	अगर (pdev->bus->number != 0 || pdev->devfn != PCI_DEVFN(0x12, 0) ||
	    !match)
		वापस false;

	अगर (!match->driver_data)
		जाओ enable_64bit;

	dmi_get_date(DMI_BIOS_DATE, &year, &month, &date);
	snम_लिखो(buf, माप(buf), "%04d%02d%02d", year, month, date);

	अगर (म_भेद(buf, match->driver_data) >= 0)
		जाओ enable_64bit;
	अन्यथा अणु
		dev_warn(&pdev->dev,
			 "%s: BIOS too old, forcing 32bit DMA, update BIOS\n",
			 match->ident);
		वापस false;
	पूर्ण

enable_64bit:
	dev_warn(&pdev->dev, "%s: enabling 64bit DMA\n", match->ident);
	वापस true;
पूर्ण

अटल bool ahci_broken_प्रणाली_घातeroff(काष्ठा pci_dev *pdev)
अणु
	अटल स्थिर काष्ठा dmi_प्रणाली_id broken_प्रणालीs[] = अणु
		अणु
			.ident = "HP Compaq nx6310",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
				DMI_MATCH(DMI_PRODUCT_NAME, "HP Compaq nx6310"),
			पूर्ण,
			/* PCI slot number of the controller */
			.driver_data = (व्योम *)0x1FUL,
		पूर्ण,
		अणु
			.ident = "HP Compaq 6720s",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
				DMI_MATCH(DMI_PRODUCT_NAME, "HP Compaq 6720s"),
			पूर्ण,
			/* PCI slot number of the controller */
			.driver_data = (व्योम *)0x1FUL,
		पूर्ण,

		अणु पूर्ण	/* terminate list */
	पूर्ण;
	स्थिर काष्ठा dmi_प्रणाली_id *dmi = dmi_first_match(broken_प्रणालीs);

	अगर (dmi) अणु
		अचिन्हित दीर्घ slot = (अचिन्हित दीर्घ)dmi->driver_data;
		/* apply the quirk only to on-board controllers */
		वापस slot == PCI_SLOT(pdev->devfn);
	पूर्ण

	वापस false;
पूर्ण

अटल bool ahci_broken_suspend(काष्ठा pci_dev *pdev)
अणु
	अटल स्थिर काष्ठा dmi_प्रणाली_id sysids[] = अणु
		/*
		 * On HP dv[4-6] and HDX18 with earlier BIOSen, link
		 * to the harddisk करोesn't become online after
		 * resuming from STR.  Warn and fail suspend.
		 *
		 * http://bugzilla.kernel.org/show_bug.cgi?id=12276
		 *
		 * Use dates instead of versions to match as HP is
		 * apparently recycling both product and version
		 * strings.
		 *
		 * http://bugzilla.kernel.org/show_bug.cgi?id=15462
		 */
		अणु
			.ident = "dv4",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
				DMI_MATCH(DMI_PRODUCT_NAME,
					  "HP Pavilion dv4 Notebook PC"),
			पूर्ण,
			.driver_data = "20090105",	/* F.30 */
		पूर्ण,
		अणु
			.ident = "dv5",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
				DMI_MATCH(DMI_PRODUCT_NAME,
					  "HP Pavilion dv5 Notebook PC"),
			पूर्ण,
			.driver_data = "20090506",	/* F.16 */
		पूर्ण,
		अणु
			.ident = "dv6",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
				DMI_MATCH(DMI_PRODUCT_NAME,
					  "HP Pavilion dv6 Notebook PC"),
			पूर्ण,
			.driver_data = "20090423",	/* F.21 */
		पूर्ण,
		अणु
			.ident = "HDX18",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
				DMI_MATCH(DMI_PRODUCT_NAME,
					  "HP HDX18 Notebook PC"),
			पूर्ण,
			.driver_data = "20090430",	/* F.23 */
		पूर्ण,
		/*
		 * Acer eMachines G725 has the same problem.  BIOS
		 * V1.03 is known to be broken.  V3.04 is known to
		 * work.  Between, there are V1.06, V2.06 and V3.03
		 * that we करोn't have much idea about.  For now,
		 * blacklist anything older than V3.04.
		 *
		 * http://bugzilla.kernel.org/show_bug.cgi?id=15104
		 */
		अणु
			.ident = "G725",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "eMachines"),
				DMI_MATCH(DMI_PRODUCT_NAME, "eMachines G725"),
			पूर्ण,
			.driver_data = "20091216",	/* V3.04 */
		पूर्ण,
		अणु पूर्ण	/* terminate list */
	पूर्ण;
	स्थिर काष्ठा dmi_प्रणाली_id *dmi = dmi_first_match(sysids);
	पूर्णांक year, month, date;
	अक्षर buf[9];

	अगर (!dmi || pdev->bus->number || pdev->devfn != PCI_DEVFN(0x1f, 2))
		वापस false;

	dmi_get_date(DMI_BIOS_DATE, &year, &month, &date);
	snम_लिखो(buf, माप(buf), "%04d%02d%02d", year, month, date);

	वापस म_भेद(buf, dmi->driver_data) < 0;
पूर्ण

अटल bool ahci_broken_lpm(काष्ठा pci_dev *pdev)
अणु
	अटल स्थिर काष्ठा dmi_प्रणाली_id sysids[] = अणु
		/* Various Lenovo 50 series have LPM issues with older BIOSen */
		अणु
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
				DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad X250"),
			पूर्ण,
			.driver_data = "20180406", /* 1.31 */
		पूर्ण,
		अणु
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
				DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad L450"),
			पूर्ण,
			.driver_data = "20180420", /* 1.28 */
		पूर्ण,
		अणु
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
				DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad T450s"),
			पूर्ण,
			.driver_data = "20180315", /* 1.33 */
		पूर्ण,
		अणु
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
				DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad W541"),
			पूर्ण,
			/*
			 * Note date based on release notes, 2.35 has been
			 * reported to be good, but I've been unable to get
			 * a hold of the reporter to get the DMI BIOS date.
			 * TODO: fix this.
			 */
			.driver_data = "20180310", /* 2.35 */
		पूर्ण,
		अणु पूर्ण	/* terminate list */
	पूर्ण;
	स्थिर काष्ठा dmi_प्रणाली_id *dmi = dmi_first_match(sysids);
	पूर्णांक year, month, date;
	अक्षर buf[9];

	अगर (!dmi)
		वापस false;

	dmi_get_date(DMI_BIOS_DATE, &year, &month, &date);
	snम_लिखो(buf, माप(buf), "%04d%02d%02d", year, month, date);

	वापस म_भेद(buf, dmi->driver_data) < 0;
पूर्ण

अटल bool ahci_broken_online(काष्ठा pci_dev *pdev)
अणु
#घोषणा ENCODE_BUSDEVFN(bus, slot, func)			\
	(व्योम *)(अचिन्हित दीर्घ)(((bus) << 8) | PCI_DEVFN((slot), (func)))
	अटल स्थिर काष्ठा dmi_प्रणाली_id sysids[] = अणु
		/*
		 * There are several gigabyte boards which use
		 * SIMG5723s configured as hardware RAID.  Certain
		 * 5723 firmware revisions shipped there keep the link
		 * online but fail to answer properly to SRST or
		 * IDENTIFY when no device is attached करोwnstream
		 * causing libata to retry quite a few बार leading
		 * to excessive detection delay.
		 *
		 * As these firmwares respond to the second reset try
		 * with invalid device signature, considering unknown
		 * sig as offline works around the problem acceptably.
		 */
		अणु
			.ident = "EP45-DQ6",
			.matches = अणु
				DMI_MATCH(DMI_BOARD_VENDOR,
					  "Gigabyte Technology Co., Ltd."),
				DMI_MATCH(DMI_BOARD_NAME, "EP45-DQ6"),
			पूर्ण,
			.driver_data = ENCODE_BUSDEVFN(0x0a, 0x00, 0),
		पूर्ण,
		अणु
			.ident = "EP45-DS5",
			.matches = अणु
				DMI_MATCH(DMI_BOARD_VENDOR,
					  "Gigabyte Technology Co., Ltd."),
				DMI_MATCH(DMI_BOARD_NAME, "EP45-DS5"),
			पूर्ण,
			.driver_data = ENCODE_BUSDEVFN(0x03, 0x00, 0),
		पूर्ण,
		अणु पूर्ण	/* terminate list */
	पूर्ण;
#अघोषित ENCODE_BUSDEVFN
	स्थिर काष्ठा dmi_प्रणाली_id *dmi = dmi_first_match(sysids);
	अचिन्हित पूर्णांक val;

	अगर (!dmi)
		वापस false;

	val = (अचिन्हित दीर्घ)dmi->driver_data;

	वापस pdev->bus->number == (val >> 8) && pdev->devfn == (val & 0xff);
पूर्ण

अटल bool ahci_broken_devslp(काष्ठा pci_dev *pdev)
अणु
	/* device with broken DEVSLP but still showing SDS capability */
	अटल स्थिर काष्ठा pci_device_id ids[] = अणु
		अणु PCI_VDEVICE(INTEL, 0x0f23)पूर्ण, /* Valleyview SoC */
		अणुपूर्ण
	पूर्ण;

	वापस pci_match_id(ids, pdev);
पूर्ण

#अगर_घोषित CONFIG_ATA_ACPI
अटल व्योम ahci_gtf_filter_workaround(काष्ठा ata_host *host)
अणु
	अटल स्थिर काष्ठा dmi_प्रणाली_id sysids[] = अणु
		/*
		 * Aspire 3810T issues a bunch of SATA enable commands
		 * via _GTF including an invalid one and one which is
		 * rejected by the device.  Among the successful ones
		 * is FPDMA non-zero offset enable which when enabled
		 * only on the drive side leads to NCQ command
		 * failures.  Filter it out.
		 */
		अणु
			.ident = "Aspire 3810T",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
				DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 3810T"),
			पूर्ण,
			.driver_data = (व्योम *)ATA_ACPI_FILTER_FPDMA_OFFSET,
		पूर्ण,
		अणु पूर्ण
	पूर्ण;
	स्थिर काष्ठा dmi_प्रणाली_id *dmi = dmi_first_match(sysids);
	अचिन्हित पूर्णांक filter;
	पूर्णांक i;

	अगर (!dmi)
		वापस;

	filter = (अचिन्हित दीर्घ)dmi->driver_data;
	dev_info(host->dev, "applying extra ACPI _GTF filter 0x%x for %s\n",
		 filter, dmi->ident);

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		काष्ठा ata_link *link;
		काष्ठा ata_device *dev;

		ata_क्रम_each_link(link, ap, EDGE)
			ata_क्रम_each_dev(dev, link, ALL)
				dev->gtf_filter |= filter;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ahci_gtf_filter_workaround(काष्ठा ata_host *host)
अणुपूर्ण
#पूर्ण_अगर

/*
 * On the Acer Aspire Switch Alpha 12, someबार all SATA ports are detected
 * as DUMMY, or detected but eventually get a "link down" and never get up
 * again. When this happens, CAP.NP may hold a value of 0x00 or 0x01, and the
 * port_map may hold a value of 0x00.
 *
 * Overriding CAP.NP to 0x02 and the port_map to 0x7 will reveal all 3 ports
 * and can signअगरicantly reduce the occurrence of the problem.
 *
 * https://bugzilla.kernel.org/show_bug.cgi?id=189471
 */
अटल व्योम acer_sa5_271_workaround(काष्ठा ahci_host_priv *hpriv,
				    काष्ठा pci_dev *pdev)
अणु
	अटल स्थिर काष्ठा dmi_प्रणाली_id sysids[] = अणु
		अणु
			.ident = "Acer Switch Alpha 12",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
				DMI_MATCH(DMI_PRODUCT_NAME, "Switch SA5-271")
			पूर्ण,
		पूर्ण,
		अणु पूर्ण
	पूर्ण;

	अगर (dmi_check_प्रणाली(sysids)) अणु
		dev_info(&pdev->dev, "enabling Acer Switch Alpha 12 workaround\n");
		अगर ((hpriv->saved_cap & 0xC734FF00) == 0xC734FF00) अणु
			hpriv->port_map = 0x7;
			hpriv->cap = 0xC734FF02;
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ARM64
/*
 * Due to ERRATA#22536, ThunderX needs to handle HOST_IRQ_STAT dअगरferently.
 * Workaround is to make sure all pending IRQs are served beक्रमe leaving
 * handler.
 */
अटल irqवापस_t ahci_thunderx_irq_handler(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	काष्ठा ahci_host_priv *hpriv;
	अचिन्हित पूर्णांक rc = 0;
	व्योम __iomem *mmio;
	u32 irq_stat, irq_masked;
	अचिन्हित पूर्णांक handled = 1;

	VPRINTK("ENTER\n");
	hpriv = host->निजी_data;
	mmio = hpriv->mmio;
	irq_stat = पढ़ोl(mmio + HOST_IRQ_STAT);
	अगर (!irq_stat)
		वापस IRQ_NONE;

	करो अणु
		irq_masked = irq_stat & hpriv->port_map;
		spin_lock(&host->lock);
		rc = ahci_handle_port_पूर्णांकr(host, irq_masked);
		अगर (!rc)
			handled = 0;
		ग_लिखोl(irq_stat, mmio + HOST_IRQ_STAT);
		irq_stat = पढ़ोl(mmio + HOST_IRQ_STAT);
		spin_unlock(&host->lock);
	पूर्ण जबतक (irq_stat);
	VPRINTK("EXIT\n");

	वापस IRQ_RETVAL(handled);
पूर्ण
#पूर्ण_अगर

अटल व्योम ahci_remap_check(काष्ठा pci_dev *pdev, पूर्णांक bar,
		काष्ठा ahci_host_priv *hpriv)
अणु
	पूर्णांक i;
	u32 cap;

	/*
	 * Check अगर this device might have remapped nvme devices.
	 */
	अगर (pdev->venकरोr != PCI_VENDOR_ID_INTEL ||
	    pci_resource_len(pdev, bar) < SZ_512K ||
	    bar != AHCI_PCI_BAR_STANDARD ||
	    !(पढ़ोl(hpriv->mmio + AHCI_VSCAP) & 1))
		वापस;

	cap = पढ़ोq(hpriv->mmio + AHCI_REMAP_CAP);
	क्रम (i = 0; i < AHCI_MAX_REMAP; i++) अणु
		अगर ((cap & (1 << i)) == 0)
			जारी;
		अगर (पढ़ोl(hpriv->mmio + ahci_remap_dcc(i))
				!= PCI_CLASS_STORAGE_EXPRESS)
			जारी;

		/* We've found a remapped device */
		hpriv->remapped_nvme++;
	पूर्ण

	अगर (!hpriv->remapped_nvme)
		वापस;

	dev_warn(&pdev->dev, "Found %u remapped NVMe devices.\n",
		 hpriv->remapped_nvme);
	dev_warn(&pdev->dev,
		 "Switch your BIOS from RAID to AHCI mode to use them.\n");

	/*
	 * Don't rely on the msi-x capability in the remap हाल,
	 * share the legacy पूर्णांकerrupt across ahci and remapped devices.
	 */
	hpriv->flags |= AHCI_HFLAG_NO_MSI;
पूर्ण

अटल पूर्णांक ahci_get_irq_vector(काष्ठा ata_host *host, पूर्णांक port)
अणु
	वापस pci_irq_vector(to_pci_dev(host->dev), port);
पूर्ण

अटल पूर्णांक ahci_init_msi(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक n_ports,
			काष्ठा ahci_host_priv *hpriv)
अणु
	पूर्णांक nvec;

	अगर (hpriv->flags & AHCI_HFLAG_NO_MSI)
		वापस -ENODEV;

	/*
	 * If number of MSIs is less than number of ports then Sharing Last
	 * Message mode could be enक्रमced. In this हाल assume that advantage
	 * of multipe MSIs is negated and use single MSI mode instead.
	 */
	अगर (n_ports > 1) अणु
		nvec = pci_alloc_irq_vectors(pdev, n_ports, पूर्णांक_उच्च,
				PCI_IRQ_MSIX | PCI_IRQ_MSI);
		अगर (nvec > 0) अणु
			अगर (!(पढ़ोl(hpriv->mmio + HOST_CTL) & HOST_MRSM)) अणु
				hpriv->get_irq_vector = ahci_get_irq_vector;
				hpriv->flags |= AHCI_HFLAG_MULTI_MSI;
				वापस nvec;
			पूर्ण

			/*
			 * Fallback to single MSI mode अगर the controller
			 * enक्रमced MRSM mode.
			 */
			prपूर्णांकk(KERN_INFO
				"ahci: MRSM is on, fallback to single MSI\n");
			pci_मुक्त_irq_vectors(pdev);
		पूर्ण
	पूर्ण

	/*
	 * If the host is not capable of supporting per-port vectors, fall
	 * back to single MSI beक्रमe finally attempting single MSI-X.
	 */
	nvec = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_MSI);
	अगर (nvec == 1)
		वापस nvec;
	वापस pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_MSIX);
पूर्ण

अटल व्योम ahci_update_initial_lpm_policy(काष्ठा ata_port *ap,
					   काष्ठा ahci_host_priv *hpriv)
अणु
	पूर्णांक policy = CONFIG_SATA_MOBILE_LPM_POLICY;


	/* Ignore processing क्रम non mobile platक्रमms */
	अगर (!(hpriv->flags & AHCI_HFLAG_IS_MOBILE))
		वापस;

	/* user modअगरied policy via module param */
	अगर (mobile_lpm_policy != -1) अणु
		policy = mobile_lpm_policy;
		जाओ update_policy;
	पूर्ण

#अगर_घोषित CONFIG_ACPI
	अगर (policy > ATA_LPM_MED_POWER &&
	    (acpi_gbl_FADT.flags & ACPI_FADT_LOW_POWER_S0)) अणु
		अगर (hpriv->cap & HOST_CAP_PART)
			policy = ATA_LPM_MIN_POWER_WITH_PARTIAL;
		अन्यथा अगर (hpriv->cap & HOST_CAP_SSC)
			policy = ATA_LPM_MIN_POWER;
	पूर्ण
#पूर्ण_अगर

update_policy:
	अगर (policy >= ATA_LPM_UNKNOWN && policy <= ATA_LPM_MIN_POWER)
		ap->target_lpm_policy = policy;
पूर्ण

अटल व्योम ahci_पूर्णांकel_pcs_quirk(काष्ठा pci_dev *pdev, काष्ठा ahci_host_priv *hpriv)
अणु
	स्थिर काष्ठा pci_device_id *id = pci_match_id(ahci_pci_tbl, pdev);
	u16 पंचांगp16;

	/*
	 * Only apply the 6-port PCS quirk क्रम known legacy platक्रमms.
	 */
	अगर (!id || id->venकरोr != PCI_VENDOR_ID_INTEL)
		वापस;

	/* Skip applying the quirk on Denverton and beyond */
	अगर (((क्रमागत board_ids) id->driver_data) >= board_ahci_pcs7)
		वापस;

	/*
	 * port_map is determined from PORTS_IMPL PCI रेजिस्टर which is
	 * implemented as ग_लिखो or ग_लिखो-once रेजिस्टर.  If the रेजिस्टर
	 * isn't programmed, ahci स्वतःmatically generates it from number
	 * of ports, which is good enough क्रम PCS programming. It is
	 * otherwise expected that platक्रमm firmware enables the ports
	 * beक्रमe the OS boots.
	 */
	pci_पढ़ो_config_word(pdev, PCS_6, &पंचांगp16);
	अगर ((पंचांगp16 & hpriv->port_map) != hpriv->port_map) अणु
		पंचांगp16 |= hpriv->port_map;
		pci_ग_लिखो_config_word(pdev, PCS_6, पंचांगp16);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार remapped_nvme_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;

	वापस प्र_लिखो(buf, "%u\n", hpriv->remapped_nvme);
पूर्ण

अटल DEVICE_ATTR_RO(remapped_nvme);

अटल पूर्णांक ahci_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित पूर्णांक board_id = ent->driver_data;
	काष्ठा ata_port_info pi = ahci_port_info[board_id];
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &pi, शून्य पूर्ण;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ahci_host_priv *hpriv;
	काष्ठा ata_host *host;
	पूर्णांक n_ports, i, rc;
	पूर्णांक ahci_pci_bar = AHCI_PCI_BAR_STANDARD;

	VPRINTK("ENTER\n");

	WARN_ON((पूर्णांक)ATA_MAX_QUEUE > AHCI_MAX_CMDS);

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	/* The AHCI driver can only drive the SATA ports, the PATA driver
	   can drive them all so अगर both drivers are selected make sure
	   AHCI stays out of the way */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_MARVELL && !marvell_enable)
		वापस -ENODEV;

	/* Apple BIOS on MCP89 prevents us using AHCI */
	अगर (is_mcp89_apple(pdev))
		ahci_mcp89_apple_enable(pdev);

	/* Promise's PDC42819 is a SAS/SATA controller that has an AHCI mode.
	 * At the moment, we can only use the AHCI mode. Let the users know
	 * that क्रम SAS drives they're out of luck.
	 */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_PROMISE)
		dev_info(&pdev->dev,
			 "PDC42819 can only drive SATA devices with this driver\n");

	/* Some devices use non-standard BARs */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_STMICRO && pdev->device == 0xCC06)
		ahci_pci_bar = AHCI_PCI_BAR_STA2X11;
	अन्यथा अगर (pdev->venकरोr == 0x1c44 && pdev->device == 0x8000)
		ahci_pci_bar = AHCI_PCI_BAR_ENMOTUS;
	अन्यथा अगर (pdev->venकरोr == PCI_VENDOR_ID_CAVIUM) अणु
		अगर (pdev->device == 0xa01c)
			ahci_pci_bar = AHCI_PCI_BAR_CAVIUM;
		अगर (pdev->device == 0xa084)
			ahci_pci_bar = AHCI_PCI_BAR_CAVIUM_GEN5;
	पूर्ण अन्यथा अगर (pdev->venकरोr == PCI_VENDOR_ID_LOONGSON) अणु
		अगर (pdev->device == 0x7a08)
			ahci_pci_bar = AHCI_PCI_BAR_LOONGSON;
	पूर्ण

	/* acquire resources */
	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL &&
	    (pdev->device == 0x2652 || pdev->device == 0x2653)) अणु
		u8 map;

		/* ICH6s share the same PCI ID क्रम both piix and ahci
		 * modes.  Enabling ahci mode जबतक MAP indicates
		 * combined mode is a bad idea.  Yield to ata_piix.
		 */
		pci_पढ़ो_config_byte(pdev, ICH_MAP, &map);
		अगर (map & 0x3) अणु
			dev_info(&pdev->dev,
				 "controller is in combined mode, can't enable AHCI mode\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* AHCI controllers often implement SFF compatible पूर्णांकerface.
	 * Grab all PCI BARs just in हाल.
	 */
	rc = pcim_iomap_regions_request_all(pdev, 1 << ahci_pci_bar, DRV_NAME);
	अगर (rc == -EBUSY)
		pcim_pin_device(pdev);
	अगर (rc)
		वापस rc;

	hpriv = devm_kzalloc(dev, माप(*hpriv), GFP_KERNEL);
	अगर (!hpriv)
		वापस -ENOMEM;
	hpriv->flags |= (अचिन्हित दीर्घ)pi.निजी_data;

	/* MCP65 revision A1 and A2 can't करो MSI */
	अगर (board_id == board_ahci_mcp65 &&
	    (pdev->revision == 0xa1 || pdev->revision == 0xa2))
		hpriv->flags |= AHCI_HFLAG_NO_MSI;

	/* SB800 करोes NOT need the workaround to ignore SERR_INTERNAL */
	अगर (board_id == board_ahci_sb700 && pdev->revision >= 0x40)
		hpriv->flags &= ~AHCI_HFLAG_IGN_SERR_INTERNAL;

	/* only some SB600s can करो 64bit DMA */
	अगर (ahci_sb600_enable_64bit(pdev))
		hpriv->flags &= ~AHCI_HFLAG_32BIT_ONLY;

	hpriv->mmio = pcim_iomap_table(pdev)[ahci_pci_bar];

	/* detect remapped nvme devices */
	ahci_remap_check(pdev, ahci_pci_bar, hpriv);

	sysfs_add_file_to_group(&pdev->dev.kobj,
				&dev_attr_remapped_nvme.attr,
				शून्य);

	/* must set flag prior to save config in order to take effect */
	अगर (ahci_broken_devslp(pdev))
		hpriv->flags |= AHCI_HFLAG_NO_DEVSLP;

#अगर_घोषित CONFIG_ARM64
	अगर (pdev->venकरोr == PCI_VENDOR_ID_HUAWEI &&
	    pdev->device == 0xa235 &&
	    pdev->revision < 0x30)
		hpriv->flags |= AHCI_HFLAG_NO_SXS;

	अगर (pdev->venकरोr == 0x177d && pdev->device == 0xa01c)
		hpriv->irq_handler = ahci_thunderx_irq_handler;
#पूर्ण_अगर

	/* save initial config */
	ahci_pci_save_initial_config(pdev, hpriv);

	/*
	 * If platक्रमm firmware failed to enable ports, try to enable
	 * them here.
	 */
	ahci_पूर्णांकel_pcs_quirk(pdev, hpriv);

	/* prepare host */
	अगर (hpriv->cap & HOST_CAP_NCQ) अणु
		pi.flags |= ATA_FLAG_NCQ;
		/*
		 * Auto-activate optimization is supposed to be
		 * supported on all AHCI controllers indicating NCQ
		 * capability, but it seems to be broken on some
		 * chipsets including NVIDIAs.
		 */
		अगर (!(hpriv->flags & AHCI_HFLAG_NO_FPDMA_AA))
			pi.flags |= ATA_FLAG_FPDMA_AA;

		/*
		 * All AHCI controllers should be क्रमward-compatible
		 * with the new auxiliary field. This code should be
		 * conditionalized अगर any buggy AHCI controllers are
		 * encountered.
		 */
		pi.flags |= ATA_FLAG_FPDMA_AUX;
	पूर्ण

	अगर (hpriv->cap & HOST_CAP_PMP)
		pi.flags |= ATA_FLAG_PMP;

	ahci_set_em_messages(hpriv, &pi);

	अगर (ahci_broken_प्रणाली_घातeroff(pdev)) अणु
		pi.flags |= ATA_FLAG_NO_POWEROFF_SPINDOWN;
		dev_info(&pdev->dev,
			"quirky BIOS, skipping spindown on poweroff\n");
	पूर्ण

	अगर (ahci_broken_lpm(pdev)) अणु
		pi.flags |= ATA_FLAG_NO_LPM;
		dev_warn(&pdev->dev,
			 "BIOS update required for Link Power Management support\n");
	पूर्ण

	अगर (ahci_broken_suspend(pdev)) अणु
		hpriv->flags |= AHCI_HFLAG_NO_SUSPEND;
		dev_warn(&pdev->dev,
			 "BIOS update required for suspend/resume\n");
	पूर्ण

	अगर (ahci_broken_online(pdev)) अणु
		hpriv->flags |= AHCI_HFLAG_SRST_TOUT_IS_OFFLINE;
		dev_info(&pdev->dev,
			 "online status unreliable, applying workaround\n");
	पूर्ण


	/* Acer SA5-271 workaround modअगरies निजी_data */
	acer_sa5_271_workaround(hpriv, pdev);

	/* CAP.NP someबार indicate the index of the last enabled
	 * port, at other बार, that of the last possible port, so
	 * determining the maximum port number requires looking at
	 * both CAP.NP and port_map.
	 */
	n_ports = max(ahci_nr_ports(hpriv->cap), fls(hpriv->port_map));

	host = ata_host_alloc_pinfo(&pdev->dev, ppi, n_ports);
	अगर (!host)
		वापस -ENOMEM;
	host->निजी_data = hpriv;

	अगर (ahci_init_msi(pdev, n_ports, hpriv) < 0) अणु
		/* legacy पूर्णांकx पूर्णांकerrupts */
		pci_पूर्णांकx(pdev, 1);
	पूर्ण
	hpriv->irq = pci_irq_vector(pdev, 0);

	अगर (!(hpriv->cap & HOST_CAP_SSS) || ahci_ignore_sss)
		host->flags |= ATA_HOST_PARALLEL_SCAN;
	अन्यथा
		dev_info(&pdev->dev, "SSS flag set, parallel bus scan disabled\n");

	अगर (pi.flags & ATA_FLAG_EM)
		ahci_reset_em(host);

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		ata_port_pbar_desc(ap, ahci_pci_bar, -1, "abar");
		ata_port_pbar_desc(ap, ahci_pci_bar,
				   0x100 + ap->port_no * 0x80, "port");

		/* set enclosure management message type */
		अगर (ap->flags & ATA_FLAG_EM)
			ap->em_message_type = hpriv->em_msg_type;

		ahci_update_initial_lpm_policy(ap, hpriv);

		/* disabled/not-implemented port */
		अगर (!(hpriv->port_map & (1 << i)))
			ap->ops = &ata_dummy_port_ops;
	पूर्ण

	/* apply workaround क्रम ASUS P5W DH Deluxe मुख्यboard */
	ahci_p5wdh_workaround(host);

	/* apply gtf filter quirk */
	ahci_gtf_filter_workaround(host);

	/* initialize adapter */
	rc = ahci_configure_dma_masks(pdev, hpriv->cap & HOST_CAP_64);
	अगर (rc)
		वापस rc;

	rc = ahci_reset_controller(host);
	अगर (rc)
		वापस rc;

	ahci_pci_init_controller(host);
	ahci_pci_prपूर्णांक_info(host);

	pci_set_master(pdev);

	rc = ahci_host_activate(host, &ahci_sht);
	अगर (rc)
		वापस rc;

	pm_runसमय_put_noidle(&pdev->dev);
	वापस 0;
पूर्ण

अटल व्योम ahci_shutकरोwn_one(काष्ठा pci_dev *pdev)
अणु
	ata_pci_shutकरोwn_one(pdev);
पूर्ण

अटल व्योम ahci_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	sysfs_हटाओ_file_from_group(&pdev->dev.kobj,
				     &dev_attr_remapped_nvme.attr,
				     शून्य);
	pm_runसमय_get_noresume(&pdev->dev);
	ata_pci_हटाओ_one(pdev);
पूर्ण

module_pci_driver(ahci_pci_driver);

MODULE_AUTHOR("Jeff Garzik");
MODULE_DESCRIPTION("AHCI SATA low-level driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, ahci_pci_tbl);
MODULE_VERSION(DRV_VERSION);
