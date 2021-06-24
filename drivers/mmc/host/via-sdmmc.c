<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  drivers/mmc/host/via-sdmmc.c - VIA SD/MMC Card Reader driver
 *  Copyright (c) 2008, VIA Technologies Inc. All Rights Reserved.
 */

#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/mmc/host.h>

#घोषणा DRV_NAME	"via_sdmmc"

#घोषणा PCI_DEVICE_ID_VIA_9530	0x9530

#घोषणा VIA_CRDR_SDC_OFF	0x200
#घोषणा VIA_CRDR_DDMA_OFF	0x400
#घोषणा VIA_CRDR_PCICTRL_OFF	0x600

#घोषणा VIA_CRDR_MIN_CLOCK	375000
#घोषणा VIA_CRDR_MAX_CLOCK	48000000

/*
 * PCI रेजिस्टरs
 */

#घोषणा VIA_CRDR_PCI_WORK_MODE	0x40
#घोषणा VIA_CRDR_PCI_DBG_MODE	0x41

/*
 * SDC MMIO Registers
 */

#घोषणा VIA_CRDR_SDCTRL			0x0
#घोषणा VIA_CRDR_SDCTRL_START		0x01
#घोषणा VIA_CRDR_SDCTRL_WRITE		0x04
#घोषणा VIA_CRDR_SDCTRL_SINGLE_WR	0x10
#घोषणा VIA_CRDR_SDCTRL_SINGLE_RD	0x20
#घोषणा VIA_CRDR_SDCTRL_MULTI_WR	0x30
#घोषणा VIA_CRDR_SDCTRL_MULTI_RD	0x40
#घोषणा VIA_CRDR_SDCTRL_STOP		0x70

#घोषणा VIA_CRDR_SDCTRL_RSP_NONE	0x0
#घोषणा VIA_CRDR_SDCTRL_RSP_R1		0x10000
#घोषणा VIA_CRDR_SDCTRL_RSP_R2		0x20000
#घोषणा VIA_CRDR_SDCTRL_RSP_R3		0x30000
#घोषणा VIA_CRDR_SDCTRL_RSP_R1B		0x90000

#घोषणा VIA_CRDR_SDCARG 	0x4

#घोषणा VIA_CRDR_SDBUSMODE	0x8
#घोषणा VIA_CRDR_SDMODE_4BIT	0x02
#घोषणा VIA_CRDR_SDMODE_CLK_ON	0x40

#घोषणा VIA_CRDR_SDBLKLEN	0xc
/*
 * Bit 0 -Bit 10 : Block length. So, the maximum block length should be 2048.
 * Bit 11 - Bit 13 : Reserved.
 * GPIDET : Select GPI pin to detect card, GPI means CR_CD# in top design.
 * INTEN : Enable SD host पूर्णांकerrupt.
 * Bit 16 - Bit 31 : Block count. So, the maximun block count should be 65536.
 */
#घोषणा VIA_CRDR_SDBLKLEN_GPIDET	0x2000
#घोषणा VIA_CRDR_SDBLKLEN_INTEN		0x8000
#घोषणा VIA_CRDR_MAX_BLOCK_COUNT	65536
#घोषणा VIA_CRDR_MAX_BLOCK_LENGTH	2048

#घोषणा VIA_CRDR_SDRESP0	0x10
#घोषणा VIA_CRDR_SDRESP1	0x14
#घोषणा VIA_CRDR_SDRESP2	0x18
#घोषणा VIA_CRDR_SDRESP3	0x1c

#घोषणा VIA_CRDR_SDCURBLKCNT	0x20

#घोषणा VIA_CRDR_SDINTMASK	0x24
/*
 * MBDIE : Multiple Blocks transfer Done Interrupt Enable
 * BDDIE : Block Data transfer Done Interrupt Enable
 * CIRIE : Card Insertion or Removal Interrupt Enable
 * CRDIE : Command-Response transfer Done Interrupt Enable
 * CRTOIE : Command-Response response TimeOut Interrupt Enable
 * ASCRDIE : Auto Stop Command-Response transfer Done Interrupt Enable
 * DTIE : Data access Timeout Interrupt Enable
 * SCIE : reSponse CRC error Interrupt Enable
 * RCIE : Read data CRC error Interrupt Enable
 * WCIE : Write data CRC error Interrupt Enable
 */
#घोषणा VIA_CRDR_SDINTMASK_MBDIE	0x10
#घोषणा VIA_CRDR_SDINTMASK_BDDIE	0x20
#घोषणा VIA_CRDR_SDINTMASK_CIRIE	0x80
#घोषणा VIA_CRDR_SDINTMASK_CRDIE	0x200
#घोषणा VIA_CRDR_SDINTMASK_CRTOIE	0x400
#घोषणा VIA_CRDR_SDINTMASK_ASCRDIE	0x800
#घोषणा VIA_CRDR_SDINTMASK_DTIE		0x1000
#घोषणा VIA_CRDR_SDINTMASK_SCIE		0x2000
#घोषणा VIA_CRDR_SDINTMASK_RCIE		0x4000
#घोषणा VIA_CRDR_SDINTMASK_WCIE		0x8000

#घोषणा VIA_CRDR_SDACTIVE_INTMASK \
	(VIA_CRDR_SDINTMASK_MBDIE | VIA_CRDR_SDINTMASK_CIRIE \
	| VIA_CRDR_SDINTMASK_CRDIE | VIA_CRDR_SDINTMASK_CRTOIE \
	| VIA_CRDR_SDINTMASK_DTIE | VIA_CRDR_SDINTMASK_SCIE \
	| VIA_CRDR_SDINTMASK_RCIE | VIA_CRDR_SDINTMASK_WCIE)

#घोषणा VIA_CRDR_SDSTATUS	0x28
/*
 * CECC : Reserved
 * WP : SD card Write Protect status
 * SLOTD : Reserved
 * SLOTG : SD SLOT status(Gpi pin status)
 * MBD : Multiple Blocks transfer Done पूर्णांकerrupt status
 * BDD : Block Data transfer Done पूर्णांकerrupt status
 * CD : Reserved
 * CIR : Card Insertion or Removal पूर्णांकerrupt detected on GPI pin
 * IO : Reserved
 * CRD : Command-Response transfer Done पूर्णांकerrupt status
 * CRTO : Command-Response response TimeOut पूर्णांकerrupt status
 * ASCRDIE : Auto Stop Command-Response transfer Done पूर्णांकerrupt status
 * DT : Data access Timeout पूर्णांकerrupt status
 * SC : reSponse CRC error पूर्णांकerrupt status
 * RC : Read data CRC error पूर्णांकerrupt status
 * WC : Write data CRC error पूर्णांकerrupt status
 */
#घोषणा VIA_CRDR_SDSTS_CECC		0x01
#घोषणा VIA_CRDR_SDSTS_WP		0x02
#घोषणा VIA_CRDR_SDSTS_SLOTD		0x04
#घोषणा VIA_CRDR_SDSTS_SLOTG		0x08
#घोषणा VIA_CRDR_SDSTS_MBD		0x10
#घोषणा VIA_CRDR_SDSTS_BDD		0x20
#घोषणा VIA_CRDR_SDSTS_CD		0x40
#घोषणा VIA_CRDR_SDSTS_CIR		0x80
#घोषणा VIA_CRDR_SDSTS_IO		0x100
#घोषणा VIA_CRDR_SDSTS_CRD		0x200
#घोषणा VIA_CRDR_SDSTS_CRTO		0x400
#घोषणा VIA_CRDR_SDSTS_ASCRDIE		0x800
#घोषणा VIA_CRDR_SDSTS_DT		0x1000
#घोषणा VIA_CRDR_SDSTS_SC		0x2000
#घोषणा VIA_CRDR_SDSTS_RC		0x4000
#घोषणा VIA_CRDR_SDSTS_WC		0x8000

#घोषणा VIA_CRDR_SDSTS_IGN_MASK\
	(VIA_CRDR_SDSTS_BDD | VIA_CRDR_SDSTS_ASCRDIE | VIA_CRDR_SDSTS_IO)
#घोषणा VIA_CRDR_SDSTS_INT_MASK \
	(VIA_CRDR_SDSTS_MBD | VIA_CRDR_SDSTS_BDD | VIA_CRDR_SDSTS_CD \
	| VIA_CRDR_SDSTS_CIR | VIA_CRDR_SDSTS_IO | VIA_CRDR_SDSTS_CRD \
	| VIA_CRDR_SDSTS_CRTO | VIA_CRDR_SDSTS_ASCRDIE | VIA_CRDR_SDSTS_DT \
	| VIA_CRDR_SDSTS_SC | VIA_CRDR_SDSTS_RC | VIA_CRDR_SDSTS_WC)
#घोषणा VIA_CRDR_SDSTS_W1C_MASK \
	(VIA_CRDR_SDSTS_CECC | VIA_CRDR_SDSTS_MBD | VIA_CRDR_SDSTS_BDD \
	| VIA_CRDR_SDSTS_CD | VIA_CRDR_SDSTS_CIR | VIA_CRDR_SDSTS_CRD \
	| VIA_CRDR_SDSTS_CRTO | VIA_CRDR_SDSTS_ASCRDIE | VIA_CRDR_SDSTS_DT \
	| VIA_CRDR_SDSTS_SC | VIA_CRDR_SDSTS_RC | VIA_CRDR_SDSTS_WC)
#घोषणा  VIA_CRDR_SDSTS_CMD_MASK \
	(VIA_CRDR_SDSTS_CRD | VIA_CRDR_SDSTS_CRTO | VIA_CRDR_SDSTS_SC)
#घोषणा  VIA_CRDR_SDSTS_DATA_MASK\
	(VIA_CRDR_SDSTS_MBD | VIA_CRDR_SDSTS_DT \
	| VIA_CRDR_SDSTS_RC | VIA_CRDR_SDSTS_WC)

#घोषणा VIA_CRDR_SDSTATUS2	0x2a
/*
 * CFE : Enable SD host स्वतःmatic Clock FReezing
 */
#घोषणा VIA_CRDR_SDSTS_CFE		0x80

#घोषणा VIA_CRDR_SDRSPTMO	0x2C

#घोषणा VIA_CRDR_SDCLKSEL	0x30

#घोषणा VIA_CRDR_SDEXTCTRL	0x34
#घोषणा VIS_CRDR_SDEXTCTRL_AUTOSTOP_SD	0x01
#घोषणा VIS_CRDR_SDEXTCTRL_SHIFT_9	0x02
#घोषणा VIS_CRDR_SDEXTCTRL_MMC_8BIT	0x04
#घोषणा VIS_CRDR_SDEXTCTRL_RELD_BLK	0x08
#घोषणा VIS_CRDR_SDEXTCTRL_BAD_CMDA	0x10
#घोषणा VIS_CRDR_SDEXTCTRL_BAD_DATA	0x20
#घोषणा VIS_CRDR_SDEXTCTRL_AUTOSTOP_SPI	0x40
#घोषणा VIA_CRDR_SDEXTCTRL_HISPD	0x80
/* 0x38-0xFF reserved */

/*
 * Data DMA Control Registers
 */

#घोषणा VIA_CRDR_DMABASEADD	0x0
#घोषणा VIA_CRDR_DMACOUNTER	0x4

#घोषणा VIA_CRDR_DMACTRL	0x8
/*
 * सूची :Transaction Direction
 * 0 : From card to memory
 * 1 : From memory to card
 */
#घोषणा VIA_CRDR_DMACTRL_सूची		0x100
#घोषणा VIA_CRDR_DMACTRL_ENIRQ		0x10000
#घोषणा VIA_CRDR_DMACTRL_SFTRST		0x1000000

#घोषणा VIA_CRDR_DMASTS		0xc

#घोषणा VIA_CRDR_DMASTART	0x10
/*0x14-0xFF reserved*/

/*
 * PCI Control Registers
 */

/*0x0 - 0x1 reserved*/
#घोषणा VIA_CRDR_PCICLKGATT	0x2
/*
 * SFTRST :
 * 0 : Soft reset all the controller and it will be de-निश्चितed स्वतःmatically
 * 1 : Soft reset is de-निश्चितed
 */
#घोषणा VIA_CRDR_PCICLKGATT_SFTRST	0x01
/*
 * 3V3 : Pad घातer select
 * 0 : 1.8V
 * 1 : 3.3V
 * NOTE : No mater what the actual value should be, this bit always
 * पढ़ो as 0. This is a hardware bug.
 */
#घोषणा VIA_CRDR_PCICLKGATT_3V3	0x10
/*
 * PAD_PWRON : Pad Power on/off select
 * 0 : Power off
 * 1 : Power on
  * NOTE : No mater what the actual value should be, this bit always
 * पढ़ो as 0. This is a hardware bug.
 */
#घोषणा VIA_CRDR_PCICLKGATT_PAD_PWRON	0x20

#घोषणा VIA_CRDR_PCISDCCLK	0x5

#घोषणा VIA_CRDR_PCIDMACLK	0x7
#घोषणा VIA_CRDR_PCIDMACLK_SDC		0x2

#घोषणा VIA_CRDR_PCIINTCTRL	0x8
#घोषणा VIA_CRDR_PCIINTCTRL_SDCIRQEN	0x04

#घोषणा VIA_CRDR_PCIINTSTATUS	0x9
#घोषणा VIA_CRDR_PCIINTSTATUS_SDC	0x04

#घोषणा  VIA_CRDR_PCITMOCTRL	0xa
#घोषणा VIA_CRDR_PCITMOCTRL_NO		0x0
#घोषणा VIA_CRDR_PCITMOCTRL_32US	0x1
#घोषणा VIA_CRDR_PCITMOCTRL_256US	0x2
#घोषणा VIA_CRDR_PCITMOCTRL_1024US	0x3
#घोषणा VIA_CRDR_PCITMOCTRL_256MS	0x4
#घोषणा VIA_CRDR_PCITMOCTRL_512MS	0x5
#घोषणा VIA_CRDR_PCITMOCTRL_1024MS	0x6

/*0xB-0xFF reserved*/

क्रमागत PCI_HOST_CLK_CONTROL अणु
	PCI_CLK_375K = 0x03,
	PCI_CLK_8M = 0x04,
	PCI_CLK_12M = 0x00,
	PCI_CLK_16M = 0x05,
	PCI_CLK_24M = 0x01,
	PCI_CLK_33M = 0x06,
	PCI_CLK_48M = 0x02
पूर्ण;

काष्ठा sdhcreg अणु
	u32 sdcontrol_reg;
	u32 sdcmdarg_reg;
	u32 sdbusmode_reg;
	u32 sdblklen_reg;
	u32 sdresp_reg[4];
	u32 sdcurblkcnt_reg;
	u32 sdपूर्णांकmask_reg;
	u32 sdstatus_reg;
	u32 sdrspपंचांगo_reg;
	u32 sdclksel_reg;
	u32 sdextctrl_reg;
पूर्ण;

काष्ठा pcictrlreg अणु
	u8 reserve[2];
	u8 pciclkgat_reg;
	u8 pcinfcclk_reg;
	u8 pcimscclk_reg;
	u8 pcisdclk_reg;
	u8 pcicaclk_reg;
	u8 pcidmaclk_reg;
	u8 pciपूर्णांकctrl_reg;
	u8 pciपूर्णांकstatus_reg;
	u8 pciपंचांगoctrl_reg;
	u8 Resv;
पूर्ण;

काष्ठा via_crdr_mmc_host अणु
	काष्ठा mmc_host *mmc;
	काष्ठा mmc_request *mrq;
	काष्ठा mmc_command *cmd;
	काष्ठा mmc_data *data;

	व्योम __iomem *mmiobase;
	व्योम __iomem *sdhc_mmiobase;
	व्योम __iomem *ddma_mmiobase;
	व्योम __iomem *pcictrl_mmiobase;

	काष्ठा pcictrlreg pm_pcictrl_reg;
	काष्ठा sdhcreg pm_sdhc_reg;

	काष्ठा work_काष्ठा carddet_work;
	काष्ठा tasklet_काष्ठा finish_tasklet;

	काष्ठा समयr_list समयr;
	spinlock_t lock;
	u8 घातer;
	पूर्णांक reject;
	अचिन्हित पूर्णांक quirks;
पूर्ण;

/* some devices need a very दीर्घ delay क्रम घातer to stabilize */
#घोषणा VIA_CRDR_QUIRK_300MS_PWRDELAY	0x0001

#घोषणा VIA_CMD_TIMEOUT_MS		1000

अटल स्थिर काष्ठा pci_device_id via_ids[] = अणु
	अणुPCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_9530,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0,पूर्ण,
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, via_ids);

अटल व्योम via_prपूर्णांक_sdchc(काष्ठा via_crdr_mmc_host *host)
अणु
	व्योम __iomem *addrbase = host->sdhc_mmiobase;

	pr_debug("SDC MMIO Registers:\n");
	pr_debug("SDCONTROL=%08x, SDCMDARG=%08x, SDBUSMODE=%08x\n",
		 पढ़ोl(addrbase + VIA_CRDR_SDCTRL),
		 पढ़ोl(addrbase + VIA_CRDR_SDCARG),
		 पढ़ोl(addrbase + VIA_CRDR_SDBUSMODE));
	pr_debug("SDBLKLEN=%08x, SDCURBLKCNT=%08x, SDINTMASK=%08x\n",
		 पढ़ोl(addrbase + VIA_CRDR_SDBLKLEN),
		 पढ़ोl(addrbase + VIA_CRDR_SDCURBLKCNT),
		 पढ़ोl(addrbase + VIA_CRDR_SDINTMASK));
	pr_debug("SDSTATUS=%08x, SDCLKSEL=%08x, SDEXTCTRL=%08x\n",
		 पढ़ोl(addrbase + VIA_CRDR_SDSTATUS),
		 पढ़ोl(addrbase + VIA_CRDR_SDCLKSEL),
		 पढ़ोl(addrbase + VIA_CRDR_SDEXTCTRL));
पूर्ण

अटल व्योम via_prपूर्णांक_pcictrl(काष्ठा via_crdr_mmc_host *host)
अणु
	व्योम __iomem *addrbase = host->pcictrl_mmiobase;

	pr_debug("PCI Control Registers:\n");
	pr_debug("PCICLKGATT=%02x, PCISDCCLK=%02x, PCIDMACLK=%02x\n",
		 पढ़ोb(addrbase + VIA_CRDR_PCICLKGATT),
		 पढ़ोb(addrbase + VIA_CRDR_PCISDCCLK),
		 पढ़ोb(addrbase + VIA_CRDR_PCIDMACLK));
	pr_debug("PCIINTCTRL=%02x, PCIINTSTATUS=%02x\n",
		 पढ़ोb(addrbase + VIA_CRDR_PCIINTCTRL),
		 पढ़ोb(addrbase + VIA_CRDR_PCIINTSTATUS));
पूर्ण

अटल व्योम via_save_pcictrlreg(काष्ठा via_crdr_mmc_host *host)
अणु
	काष्ठा pcictrlreg *pm_pcictrl_reg;
	व्योम __iomem *addrbase;

	pm_pcictrl_reg = &(host->pm_pcictrl_reg);
	addrbase = host->pcictrl_mmiobase;

	pm_pcictrl_reg->pciclkgat_reg = पढ़ोb(addrbase + VIA_CRDR_PCICLKGATT);
	pm_pcictrl_reg->pciclkgat_reg |=
		VIA_CRDR_PCICLKGATT_3V3 | VIA_CRDR_PCICLKGATT_PAD_PWRON;
	pm_pcictrl_reg->pcisdclk_reg = पढ़ोb(addrbase + VIA_CRDR_PCISDCCLK);
	pm_pcictrl_reg->pcidmaclk_reg = पढ़ोb(addrbase + VIA_CRDR_PCIDMACLK);
	pm_pcictrl_reg->pciपूर्णांकctrl_reg = पढ़ोb(addrbase + VIA_CRDR_PCIINTCTRL);
	pm_pcictrl_reg->pciपूर्णांकstatus_reg =
		पढ़ोb(addrbase + VIA_CRDR_PCIINTSTATUS);
	pm_pcictrl_reg->pciपंचांगoctrl_reg = पढ़ोb(addrbase + VIA_CRDR_PCITMOCTRL);
पूर्ण

अटल व्योम via_restore_pcictrlreg(काष्ठा via_crdr_mmc_host *host)
अणु
	काष्ठा pcictrlreg *pm_pcictrl_reg;
	व्योम __iomem *addrbase;

	pm_pcictrl_reg = &(host->pm_pcictrl_reg);
	addrbase = host->pcictrl_mmiobase;

	ग_लिखोb(pm_pcictrl_reg->pciclkgat_reg, addrbase + VIA_CRDR_PCICLKGATT);
	ग_लिखोb(pm_pcictrl_reg->pcisdclk_reg, addrbase + VIA_CRDR_PCISDCCLK);
	ग_लिखोb(pm_pcictrl_reg->pcidmaclk_reg, addrbase + VIA_CRDR_PCIDMACLK);
	ग_लिखोb(pm_pcictrl_reg->pciपूर्णांकctrl_reg, addrbase + VIA_CRDR_PCIINTCTRL);
	ग_लिखोb(pm_pcictrl_reg->pciपूर्णांकstatus_reg,
		addrbase + VIA_CRDR_PCIINTSTATUS);
	ग_लिखोb(pm_pcictrl_reg->pciपंचांगoctrl_reg, addrbase + VIA_CRDR_PCITMOCTRL);
पूर्ण

अटल व्योम via_save_sdcreg(काष्ठा via_crdr_mmc_host *host)
अणु
	काष्ठा sdhcreg *pm_sdhc_reg;
	व्योम __iomem *addrbase;

	pm_sdhc_reg = &(host->pm_sdhc_reg);
	addrbase = host->sdhc_mmiobase;

	pm_sdhc_reg->sdcontrol_reg = पढ़ोl(addrbase + VIA_CRDR_SDCTRL);
	pm_sdhc_reg->sdcmdarg_reg = पढ़ोl(addrbase + VIA_CRDR_SDCARG);
	pm_sdhc_reg->sdbusmode_reg = पढ़ोl(addrbase + VIA_CRDR_SDBUSMODE);
	pm_sdhc_reg->sdblklen_reg = पढ़ोl(addrbase + VIA_CRDR_SDBLKLEN);
	pm_sdhc_reg->sdcurblkcnt_reg = पढ़ोl(addrbase + VIA_CRDR_SDCURBLKCNT);
	pm_sdhc_reg->sdपूर्णांकmask_reg = पढ़ोl(addrbase + VIA_CRDR_SDINTMASK);
	pm_sdhc_reg->sdstatus_reg = पढ़ोl(addrbase + VIA_CRDR_SDSTATUS);
	pm_sdhc_reg->sdrspपंचांगo_reg = पढ़ोl(addrbase + VIA_CRDR_SDRSPTMO);
	pm_sdhc_reg->sdclksel_reg = पढ़ोl(addrbase + VIA_CRDR_SDCLKSEL);
	pm_sdhc_reg->sdextctrl_reg = पढ़ोl(addrbase + VIA_CRDR_SDEXTCTRL);
पूर्ण

अटल व्योम via_restore_sdcreg(काष्ठा via_crdr_mmc_host *host)
अणु
	काष्ठा sdhcreg *pm_sdhc_reg;
	व्योम __iomem *addrbase;

	pm_sdhc_reg = &(host->pm_sdhc_reg);
	addrbase = host->sdhc_mmiobase;

	ग_लिखोl(pm_sdhc_reg->sdcontrol_reg, addrbase + VIA_CRDR_SDCTRL);
	ग_लिखोl(pm_sdhc_reg->sdcmdarg_reg, addrbase + VIA_CRDR_SDCARG);
	ग_लिखोl(pm_sdhc_reg->sdbusmode_reg, addrbase + VIA_CRDR_SDBUSMODE);
	ग_लिखोl(pm_sdhc_reg->sdblklen_reg, addrbase + VIA_CRDR_SDBLKLEN);
	ग_लिखोl(pm_sdhc_reg->sdcurblkcnt_reg, addrbase + VIA_CRDR_SDCURBLKCNT);
	ग_लिखोl(pm_sdhc_reg->sdपूर्णांकmask_reg, addrbase + VIA_CRDR_SDINTMASK);
	ग_लिखोl(pm_sdhc_reg->sdstatus_reg, addrbase + VIA_CRDR_SDSTATUS);
	ग_लिखोl(pm_sdhc_reg->sdrspपंचांगo_reg, addrbase + VIA_CRDR_SDRSPTMO);
	ग_लिखोl(pm_sdhc_reg->sdclksel_reg, addrbase + VIA_CRDR_SDCLKSEL);
	ग_लिखोl(pm_sdhc_reg->sdextctrl_reg, addrbase + VIA_CRDR_SDEXTCTRL);
पूर्ण

अटल व्योम via_pwron_sleep(काष्ठा via_crdr_mmc_host *sdhost)
अणु
	अगर (sdhost->quirks & VIA_CRDR_QUIRK_300MS_PWRDELAY)
		msleep(300);
	अन्यथा
		msleep(3);
पूर्ण

अटल व्योम via_set_ddma(काष्ठा via_crdr_mmc_host *host,
			 dma_addr_t dmaaddr, u32 count, पूर्णांक dir, पूर्णांक enirq)
अणु
	व्योम __iomem *addrbase;
	u32 ctrl_data = 0;

	अगर (enirq)
		ctrl_data |= VIA_CRDR_DMACTRL_ENIRQ;

	अगर (dir)
		ctrl_data |= VIA_CRDR_DMACTRL_सूची;

	addrbase = host->ddma_mmiobase;

	ग_लिखोl(dmaaddr, addrbase + VIA_CRDR_DMABASEADD);
	ग_लिखोl(count, addrbase + VIA_CRDR_DMACOUNTER);
	ग_लिखोl(ctrl_data, addrbase + VIA_CRDR_DMACTRL);
	ग_लिखोl(0x01, addrbase + VIA_CRDR_DMASTART);

	/* It seems that our DMA can not work normally with 375kHz घड़ी */
	/* FIXME: करोn't brute-क्रमce 8MHz but use PIO at 375kHz !! */
	addrbase = host->pcictrl_mmiobase;
	अगर (पढ़ोb(addrbase + VIA_CRDR_PCISDCCLK) == PCI_CLK_375K) अणु
		dev_info(host->mmc->parent, "forcing card speed to 8MHz\n");
		ग_लिखोb(PCI_CLK_8M, addrbase + VIA_CRDR_PCISDCCLK);
	पूर्ण
पूर्ण

अटल व्योम via_sdc_preparedata(काष्ठा via_crdr_mmc_host *host,
				काष्ठा mmc_data *data)
अणु
	व्योम __iomem *addrbase;
	u32 blk_reg;
	पूर्णांक count;

	WARN_ON(host->data);

	/* Sanity checks */
	BUG_ON(data->blksz > host->mmc->max_blk_size);
	BUG_ON(data->blocks > host->mmc->max_blk_count);

	host->data = data;

	count = dma_map_sg(mmc_dev(host->mmc), data->sg, data->sg_len,
		((data->flags & MMC_DATA_READ) ?
		PCI_DMA_FROMDEVICE : PCI_DMA_TODEVICE));
	BUG_ON(count != 1);

	via_set_ddma(host, sg_dma_address(data->sg), sg_dma_len(data->sg),
		(data->flags & MMC_DATA_WRITE) ? 1 : 0, 1);

	addrbase = host->sdhc_mmiobase;

	blk_reg = data->blksz - 1;
	blk_reg |= VIA_CRDR_SDBLKLEN_GPIDET | VIA_CRDR_SDBLKLEN_INTEN;
	blk_reg |= (data->blocks) << 16;

	ग_लिखोl(blk_reg, addrbase + VIA_CRDR_SDBLKLEN);
पूर्ण

अटल व्योम via_sdc_get_response(काष्ठा via_crdr_mmc_host *host,
				 काष्ठा mmc_command *cmd)
अणु
	व्योम __iomem *addrbase = host->sdhc_mmiobase;
	u32 dwdata0 = पढ़ोl(addrbase + VIA_CRDR_SDRESP0);
	u32 dwdata1 = पढ़ोl(addrbase + VIA_CRDR_SDRESP1);
	u32 dwdata2 = पढ़ोl(addrbase + VIA_CRDR_SDRESP2);
	u32 dwdata3 = पढ़ोl(addrbase + VIA_CRDR_SDRESP3);

	अगर (cmd->flags & MMC_RSP_136) अणु
		cmd->resp[0] = ((u8) (dwdata1)) |
		    (((u8) (dwdata0 >> 24)) << 8) |
		    (((u8) (dwdata0 >> 16)) << 16) |
		    (((u8) (dwdata0 >> 8)) << 24);

		cmd->resp[1] = ((u8) (dwdata2)) |
		    (((u8) (dwdata1 >> 24)) << 8) |
		    (((u8) (dwdata1 >> 16)) << 16) |
		    (((u8) (dwdata1 >> 8)) << 24);

		cmd->resp[2] = ((u8) (dwdata3)) |
		    (((u8) (dwdata2 >> 24)) << 8) |
		    (((u8) (dwdata2 >> 16)) << 16) |
		    (((u8) (dwdata2 >> 8)) << 24);

		cmd->resp[3] = 0xff |
		    ((((u8) (dwdata3 >> 24))) << 8) |
		    (((u8) (dwdata3 >> 16)) << 16) |
		    (((u8) (dwdata3 >> 8)) << 24);
	पूर्ण अन्यथा अणु
		dwdata0 >>= 8;
		cmd->resp[0] = ((dwdata0 & 0xff) << 24) |
		    (((dwdata0 >> 8) & 0xff) << 16) |
		    (((dwdata0 >> 16) & 0xff) << 8) | (dwdata1 & 0xff);

		dwdata1 >>= 8;
		cmd->resp[1] = ((dwdata1 & 0xff) << 24) |
		    (((dwdata1 >> 8) & 0xff) << 16) |
		    (((dwdata1 >> 16) & 0xff) << 8);
	पूर्ण
पूर्ण

अटल व्योम via_sdc_send_command(काष्ठा via_crdr_mmc_host *host,
				 काष्ठा mmc_command *cmd)
अणु
	व्योम __iomem *addrbase;
	काष्ठा mmc_data *data;
	अचिन्हित पूर्णांक समयout_ms;
	u32 cmdctrl = 0;

	WARN_ON(host->cmd);

	data = cmd->data;
	host->cmd = cmd;

	समयout_ms = cmd->busy_समयout ? cmd->busy_समयout : VIA_CMD_TIMEOUT_MS;
	mod_समयr(&host->समयr, jअगरfies + msecs_to_jअगरfies(समयout_ms));

	/*Command index*/
	cmdctrl = cmd->opcode << 8;

	/*Response type*/
	चयन (mmc_resp_type(cmd)) अणु
	हाल MMC_RSP_NONE:
		cmdctrl |= VIA_CRDR_SDCTRL_RSP_NONE;
		अवरोध;
	हाल MMC_RSP_R1:
		cmdctrl |= VIA_CRDR_SDCTRL_RSP_R1;
		अवरोध;
	हाल MMC_RSP_R1B:
		cmdctrl |= VIA_CRDR_SDCTRL_RSP_R1B;
		अवरोध;
	हाल MMC_RSP_R2:
		cmdctrl |= VIA_CRDR_SDCTRL_RSP_R2;
		अवरोध;
	हाल MMC_RSP_R3:
		cmdctrl |= VIA_CRDR_SDCTRL_RSP_R3;
		अवरोध;
	शेष:
		pr_err("%s: cmd->flag is not valid\n", mmc_hostname(host->mmc));
		अवरोध;
	पूर्ण

	अगर (!(cmd->data))
		जाओ nodata;

	via_sdc_preparedata(host, data);

	/*Command control*/
	अगर (data->blocks > 1) अणु
		अगर (data->flags & MMC_DATA_WRITE) अणु
			cmdctrl |= VIA_CRDR_SDCTRL_WRITE;
			cmdctrl |= VIA_CRDR_SDCTRL_MULTI_WR;
		पूर्ण अन्यथा अणु
			cmdctrl |= VIA_CRDR_SDCTRL_MULTI_RD;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (data->flags & MMC_DATA_WRITE) अणु
			cmdctrl |= VIA_CRDR_SDCTRL_WRITE;
			cmdctrl |= VIA_CRDR_SDCTRL_SINGLE_WR;
		पूर्ण अन्यथा अणु
			cmdctrl |= VIA_CRDR_SDCTRL_SINGLE_RD;
		पूर्ण
	पूर्ण

nodata:
	अगर (cmd == host->mrq->stop)
		cmdctrl |= VIA_CRDR_SDCTRL_STOP;

	cmdctrl |= VIA_CRDR_SDCTRL_START;

	addrbase = host->sdhc_mmiobase;
	ग_लिखोl(cmd->arg, addrbase + VIA_CRDR_SDCARG);
	ग_लिखोl(cmdctrl, addrbase + VIA_CRDR_SDCTRL);
पूर्ण

अटल व्योम via_sdc_finish_data(काष्ठा via_crdr_mmc_host *host)
अणु
	काष्ठा mmc_data *data;

	BUG_ON(!host->data);

	data = host->data;
	host->data = शून्य;

	अगर (data->error)
		data->bytes_xfered = 0;
	अन्यथा
		data->bytes_xfered = data->blocks * data->blksz;

	dma_unmap_sg(mmc_dev(host->mmc), data->sg, data->sg_len,
		((data->flags & MMC_DATA_READ) ?
		PCI_DMA_FROMDEVICE : PCI_DMA_TODEVICE));

	अगर (data->stop)
		via_sdc_send_command(host, data->stop);
	अन्यथा
		tasklet_schedule(&host->finish_tasklet);
पूर्ण

अटल व्योम via_sdc_finish_command(काष्ठा via_crdr_mmc_host *host)
अणु
	via_sdc_get_response(host, host->cmd);

	host->cmd->error = 0;

	अगर (!host->cmd->data)
		tasklet_schedule(&host->finish_tasklet);

	host->cmd = शून्य;
पूर्ण

अटल व्योम via_sdc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	व्योम __iomem *addrbase;
	काष्ठा via_crdr_mmc_host *host;
	अचिन्हित दीर्घ flags;
	u16 status;

	host = mmc_priv(mmc);

	spin_lock_irqsave(&host->lock, flags);

	addrbase = host->pcictrl_mmiobase;
	ग_लिखोb(VIA_CRDR_PCIDMACLK_SDC, addrbase + VIA_CRDR_PCIDMACLK);

	status = पढ़ोw(host->sdhc_mmiobase + VIA_CRDR_SDSTATUS);
	status &= VIA_CRDR_SDSTS_W1C_MASK;
	ग_लिखोw(status, host->sdhc_mmiobase + VIA_CRDR_SDSTATUS);

	WARN_ON(host->mrq != शून्य);
	host->mrq = mrq;

	status = पढ़ोw(host->sdhc_mmiobase + VIA_CRDR_SDSTATUS);
	अगर (!(status & VIA_CRDR_SDSTS_SLOTG) || host->reject) अणु
		host->mrq->cmd->error = -ENOMEDIUM;
		tasklet_schedule(&host->finish_tasklet);
	पूर्ण अन्यथा अणु
		via_sdc_send_command(host, mrq->cmd);
	पूर्ण

	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल व्योम via_sdc_set_घातer(काष्ठा via_crdr_mmc_host *host,
			      अचिन्हित लघु घातer, अचिन्हित पूर्णांक on)
अणु
	अचिन्हित दीर्घ flags;
	u8 gatt;

	spin_lock_irqsave(&host->lock, flags);

	host->घातer = (1 << घातer);

	gatt = पढ़ोb(host->pcictrl_mmiobase + VIA_CRDR_PCICLKGATT);
	अगर (host->घातer == MMC_VDD_165_195)
		gatt &= ~VIA_CRDR_PCICLKGATT_3V3;
	अन्यथा
		gatt |= VIA_CRDR_PCICLKGATT_3V3;
	अगर (on)
		gatt |= VIA_CRDR_PCICLKGATT_PAD_PWRON;
	अन्यथा
		gatt &= ~VIA_CRDR_PCICLKGATT_PAD_PWRON;
	ग_लिखोb(gatt, host->pcictrl_mmiobase + VIA_CRDR_PCICLKGATT);

	spin_unlock_irqrestore(&host->lock, flags);

	via_pwron_sleep(host);
पूर्ण

अटल व्योम via_sdc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा via_crdr_mmc_host *host;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *addrbase;
	u32 org_data, sdextctrl;
	u8 घड़ी;

	host = mmc_priv(mmc);

	spin_lock_irqsave(&host->lock, flags);

	addrbase = host->sdhc_mmiobase;
	org_data = पढ़ोl(addrbase + VIA_CRDR_SDBUSMODE);
	sdextctrl = पढ़ोl(addrbase + VIA_CRDR_SDEXTCTRL);

	अगर (ios->bus_width == MMC_BUS_WIDTH_1)
		org_data &= ~VIA_CRDR_SDMODE_4BIT;
	अन्यथा
		org_data |= VIA_CRDR_SDMODE_4BIT;

	अगर (ios->घातer_mode == MMC_POWER_OFF)
		org_data &= ~VIA_CRDR_SDMODE_CLK_ON;
	अन्यथा
		org_data |= VIA_CRDR_SDMODE_CLK_ON;

	अगर (ios->timing == MMC_TIMING_SD_HS)
		sdextctrl |= VIA_CRDR_SDEXTCTRL_HISPD;
	अन्यथा
		sdextctrl &= ~VIA_CRDR_SDEXTCTRL_HISPD;

	ग_लिखोl(org_data, addrbase + VIA_CRDR_SDBUSMODE);
	ग_लिखोl(sdextctrl, addrbase + VIA_CRDR_SDEXTCTRL);

	अगर (ios->घड़ी >= 48000000)
		घड़ी = PCI_CLK_48M;
	अन्यथा अगर (ios->घड़ी >= 33000000)
		घड़ी = PCI_CLK_33M;
	अन्यथा अगर (ios->घड़ी >= 24000000)
		घड़ी = PCI_CLK_24M;
	अन्यथा अगर (ios->घड़ी >= 16000000)
		घड़ी = PCI_CLK_16M;
	अन्यथा अगर (ios->घड़ी >= 12000000)
		घड़ी = PCI_CLK_12M;
	अन्यथा अगर (ios->घड़ी >=  8000000)
		घड़ी = PCI_CLK_8M;
	अन्यथा
		घड़ी = PCI_CLK_375K;

	addrbase = host->pcictrl_mmiobase;
	अगर (पढ़ोb(addrbase + VIA_CRDR_PCISDCCLK) != घड़ी)
		ग_लिखोb(घड़ी, addrbase + VIA_CRDR_PCISDCCLK);

	spin_unlock_irqrestore(&host->lock, flags);

	अगर (ios->घातer_mode != MMC_POWER_OFF)
		via_sdc_set_घातer(host, ios->vdd, 1);
	अन्यथा
		via_sdc_set_घातer(host, ios->vdd, 0);
पूर्ण

अटल पूर्णांक via_sdc_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा via_crdr_mmc_host *host;
	अचिन्हित दीर्घ flags;
	u16 status;

	host = mmc_priv(mmc);

	spin_lock_irqsave(&host->lock, flags);

	status = पढ़ोw(host->sdhc_mmiobase + VIA_CRDR_SDSTATUS);

	spin_unlock_irqrestore(&host->lock, flags);

	वापस !(status & VIA_CRDR_SDSTS_WP);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops via_sdc_ops = अणु
	.request = via_sdc_request,
	.set_ios = via_sdc_set_ios,
	.get_ro = via_sdc_get_ro,
पूर्ण;

अटल व्योम via_reset_pcictrl(काष्ठा via_crdr_mmc_host *host)
अणु
	अचिन्हित दीर्घ flags;
	u8 gatt;

	spin_lock_irqsave(&host->lock, flags);

	via_save_pcictrlreg(host);
	via_save_sdcreg(host);

	spin_unlock_irqrestore(&host->lock, flags);

	gatt = VIA_CRDR_PCICLKGATT_PAD_PWRON;
	अगर (host->घातer == MMC_VDD_165_195)
		gatt &= VIA_CRDR_PCICLKGATT_3V3;
	अन्यथा
		gatt |= VIA_CRDR_PCICLKGATT_3V3;
	ग_लिखोb(gatt, host->pcictrl_mmiobase + VIA_CRDR_PCICLKGATT);
	via_pwron_sleep(host);
	gatt |= VIA_CRDR_PCICLKGATT_SFTRST;
	ग_लिखोb(gatt, host->pcictrl_mmiobase + VIA_CRDR_PCICLKGATT);
	msleep(3);

	spin_lock_irqsave(&host->lock, flags);

	via_restore_pcictrlreg(host);
	via_restore_sdcreg(host);

	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल व्योम via_sdc_cmd_isr(काष्ठा via_crdr_mmc_host *host, u16 पूर्णांकmask)
अणु
	BUG_ON(पूर्णांकmask == 0);

	अगर (!host->cmd) अणु
		pr_err("%s: Got command interrupt 0x%x even "
		       "though no command operation was in progress.\n",
		       mmc_hostname(host->mmc), पूर्णांकmask);
		वापस;
	पूर्ण

	अगर (पूर्णांकmask & VIA_CRDR_SDSTS_CRTO)
		host->cmd->error = -ETIMEDOUT;
	अन्यथा अगर (पूर्णांकmask & VIA_CRDR_SDSTS_SC)
		host->cmd->error = -EILSEQ;

	अगर (host->cmd->error)
		tasklet_schedule(&host->finish_tasklet);
	अन्यथा अगर (पूर्णांकmask & VIA_CRDR_SDSTS_CRD)
		via_sdc_finish_command(host);
पूर्ण

अटल व्योम via_sdc_data_isr(काष्ठा via_crdr_mmc_host *host, u16 पूर्णांकmask)
अणु
	BUG_ON(पूर्णांकmask == 0);

	अगर (पूर्णांकmask & VIA_CRDR_SDSTS_DT)
		host->data->error = -ETIMEDOUT;
	अन्यथा अगर (पूर्णांकmask & (VIA_CRDR_SDSTS_RC | VIA_CRDR_SDSTS_WC))
		host->data->error = -EILSEQ;

	via_sdc_finish_data(host);
पूर्ण

अटल irqवापस_t via_sdc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा via_crdr_mmc_host *sdhost = dev_id;
	व्योम __iomem *addrbase;
	u8 pci_status;
	u16 sd_status;
	irqवापस_t result;

	अगर (!sdhost)
		वापस IRQ_NONE;

	spin_lock(&sdhost->lock);

	addrbase = sdhost->pcictrl_mmiobase;
	pci_status = पढ़ोb(addrbase + VIA_CRDR_PCIINTSTATUS);
	अगर (!(pci_status & VIA_CRDR_PCIINTSTATUS_SDC)) अणु
		result = IRQ_NONE;
		जाओ out;
	पूर्ण

	addrbase = sdhost->sdhc_mmiobase;
	sd_status = पढ़ोw(addrbase + VIA_CRDR_SDSTATUS);
	sd_status &= VIA_CRDR_SDSTS_INT_MASK;
	sd_status &= ~VIA_CRDR_SDSTS_IGN_MASK;
	अगर (!sd_status) अणु
		result = IRQ_NONE;
		जाओ out;
	पूर्ण

	अगर (sd_status & VIA_CRDR_SDSTS_CIR) अणु
		ग_लिखोw(sd_status & VIA_CRDR_SDSTS_CIR,
			addrbase + VIA_CRDR_SDSTATUS);

		schedule_work(&sdhost->carddet_work);
	पूर्ण

	sd_status &= ~VIA_CRDR_SDSTS_CIR;
	अगर (sd_status & VIA_CRDR_SDSTS_CMD_MASK) अणु
		ग_लिखोw(sd_status & VIA_CRDR_SDSTS_CMD_MASK,
			addrbase + VIA_CRDR_SDSTATUS);
		via_sdc_cmd_isr(sdhost, sd_status & VIA_CRDR_SDSTS_CMD_MASK);
	पूर्ण
	अगर (sd_status & VIA_CRDR_SDSTS_DATA_MASK) अणु
		ग_लिखोw(sd_status & VIA_CRDR_SDSTS_DATA_MASK,
			addrbase + VIA_CRDR_SDSTATUS);
		via_sdc_data_isr(sdhost, sd_status & VIA_CRDR_SDSTS_DATA_MASK);
	पूर्ण

	sd_status &= ~(VIA_CRDR_SDSTS_CMD_MASK | VIA_CRDR_SDSTS_DATA_MASK);
	अगर (sd_status) अणु
		pr_err("%s: Unexpected interrupt 0x%x\n",
		       mmc_hostname(sdhost->mmc), sd_status);
		ग_लिखोw(sd_status, addrbase + VIA_CRDR_SDSTATUS);
	पूर्ण

	result = IRQ_HANDLED;

out:
	spin_unlock(&sdhost->lock);

	वापस result;
पूर्ण

अटल व्योम via_sdc_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा via_crdr_mmc_host *sdhost;
	अचिन्हित दीर्घ flags;

	sdhost = from_समयr(sdhost, t, समयr);

	spin_lock_irqsave(&sdhost->lock, flags);

	अगर (sdhost->mrq) अणु
		pr_err("%s: Timeout waiting for hardware interrupt."
		       "cmd:0x%x\n", mmc_hostname(sdhost->mmc),
		       sdhost->mrq->cmd->opcode);

		अगर (sdhost->data) अणु
			ग_लिखोl(VIA_CRDR_DMACTRL_SFTRST,
				sdhost->ddma_mmiobase + VIA_CRDR_DMACTRL);
			sdhost->data->error = -ETIMEDOUT;
			via_sdc_finish_data(sdhost);
		पूर्ण अन्यथा अणु
			अगर (sdhost->cmd)
				sdhost->cmd->error = -ETIMEDOUT;
			अन्यथा
				sdhost->mrq->cmd->error = -ETIMEDOUT;
			tasklet_schedule(&sdhost->finish_tasklet);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&sdhost->lock, flags);
पूर्ण

अटल व्योम via_sdc_tasklet_finish(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा via_crdr_mmc_host *host = from_tasklet(host, t, finish_tasklet);
	अचिन्हित दीर्घ flags;
	काष्ठा mmc_request *mrq;

	spin_lock_irqsave(&host->lock, flags);

	del_समयr(&host->समयr);
	mrq = host->mrq;
	host->mrq = शून्य;
	host->cmd = शून्य;
	host->data = शून्य;

	spin_unlock_irqrestore(&host->lock, flags);

	mmc_request_करोne(host->mmc, mrq);
पूर्ण

अटल व्योम via_sdc_card_detect(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा via_crdr_mmc_host *host;
	व्योम __iomem *addrbase;
	अचिन्हित दीर्घ flags;
	u16 status;

	host = container_of(work, काष्ठा via_crdr_mmc_host, carddet_work);

	addrbase = host->ddma_mmiobase;
	ग_लिखोl(VIA_CRDR_DMACTRL_SFTRST, addrbase + VIA_CRDR_DMACTRL);

	spin_lock_irqsave(&host->lock, flags);

	addrbase = host->pcictrl_mmiobase;
	ग_लिखोb(VIA_CRDR_PCIDMACLK_SDC, addrbase + VIA_CRDR_PCIDMACLK);

	addrbase = host->sdhc_mmiobase;
	status = पढ़ोw(addrbase + VIA_CRDR_SDSTATUS);
	अगर (!(status & VIA_CRDR_SDSTS_SLOTG)) अणु
		अगर (host->mrq) अणु
			pr_err("%s: Card removed during transfer!\n",
			       mmc_hostname(host->mmc));
			host->mrq->cmd->error = -ENOMEDIUM;
			tasklet_schedule(&host->finish_tasklet);
		पूर्ण

		spin_unlock_irqrestore(&host->lock, flags);

		via_reset_pcictrl(host);

		spin_lock_irqsave(&host->lock, flags);
	पूर्ण

	spin_unlock_irqrestore(&host->lock, flags);

	via_prपूर्णांक_pcictrl(host);
	via_prपूर्णांक_sdchc(host);

	mmc_detect_change(host->mmc, msecs_to_jअगरfies(500));
पूर्ण

अटल व्योम via_init_mmc_host(काष्ठा via_crdr_mmc_host *host)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	व्योम __iomem *addrbase;
	u32 lenreg;
	u32 status;

	समयr_setup(&host->समयr, via_sdc_समयout, 0);

	spin_lock_init(&host->lock);

	mmc->f_min = VIA_CRDR_MIN_CLOCK;
	mmc->f_max = VIA_CRDR_MAX_CLOCK;
	mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34 | MMC_VDD_165_195;
	mmc->caps = MMC_CAP_4_BIT_DATA | MMC_CAP_SD_HIGHSPEED;
	mmc->ops = &via_sdc_ops;

	/*Hardware cannot करो scatter lists*/
	mmc->max_segs = 1;

	mmc->max_blk_size = VIA_CRDR_MAX_BLOCK_LENGTH;
	mmc->max_blk_count = VIA_CRDR_MAX_BLOCK_COUNT;

	mmc->max_seg_size = mmc->max_blk_size * mmc->max_blk_count;
	mmc->max_req_size = mmc->max_seg_size;

	INIT_WORK(&host->carddet_work, via_sdc_card_detect);

	tasklet_setup(&host->finish_tasklet, via_sdc_tasklet_finish);

	addrbase = host->sdhc_mmiobase;
	ग_लिखोl(0x0, addrbase + VIA_CRDR_SDINTMASK);
	msleep(1);

	lenreg = VIA_CRDR_SDBLKLEN_GPIDET | VIA_CRDR_SDBLKLEN_INTEN;
	ग_लिखोl(lenreg, addrbase + VIA_CRDR_SDBLKLEN);

	status = पढ़ोw(addrbase + VIA_CRDR_SDSTATUS);
	status &= VIA_CRDR_SDSTS_W1C_MASK;
	ग_लिखोw(status, addrbase + VIA_CRDR_SDSTATUS);

	status = पढ़ोw(addrbase + VIA_CRDR_SDSTATUS2);
	status |= VIA_CRDR_SDSTS_CFE;
	ग_लिखोw(status, addrbase + VIA_CRDR_SDSTATUS2);

	ग_लिखोb(0x0, addrbase + VIA_CRDR_SDEXTCTRL);

	ग_लिखोl(VIA_CRDR_SDACTIVE_INTMASK, addrbase + VIA_CRDR_SDINTMASK);
	msleep(1);
पूर्ण

अटल पूर्णांक via_sd_probe(काष्ठा pci_dev *pcidev,
				    स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा mmc_host *mmc;
	काष्ठा via_crdr_mmc_host *sdhost;
	u32 base, len;
	u8  gatt;
	पूर्णांक ret;

	pr_info(DRV_NAME
		": VIA SDMMC controller found at %s [%04x:%04x] (rev %x)\n",
		pci_name(pcidev), (पूर्णांक)pcidev->venकरोr, (पूर्णांक)pcidev->device,
		(पूर्णांक)pcidev->revision);

	ret = pci_enable_device(pcidev);
	अगर (ret)
		वापस ret;

	ret = pci_request_regions(pcidev, DRV_NAME);
	अगर (ret)
		जाओ disable;

	pci_ग_लिखो_config_byte(pcidev, VIA_CRDR_PCI_WORK_MODE, 0);
	pci_ग_लिखो_config_byte(pcidev, VIA_CRDR_PCI_DBG_MODE, 0);

	mmc = mmc_alloc_host(माप(काष्ठा via_crdr_mmc_host), &pcidev->dev);
	अगर (!mmc) अणु
		ret = -ENOMEM;
		जाओ release;
	पूर्ण

	sdhost = mmc_priv(mmc);
	sdhost->mmc = mmc;
	dev_set_drvdata(&pcidev->dev, sdhost);

	len = pci_resource_len(pcidev, 0);
	base = pci_resource_start(pcidev, 0);
	sdhost->mmiobase = ioremap(base, len);
	अगर (!sdhost->mmiobase) अणु
		ret = -ENOMEM;
		जाओ मुक्त_mmc_host;
	पूर्ण

	sdhost->sdhc_mmiobase =
		sdhost->mmiobase + VIA_CRDR_SDC_OFF;
	sdhost->ddma_mmiobase =
		sdhost->mmiobase + VIA_CRDR_DDMA_OFF;
	sdhost->pcictrl_mmiobase =
		sdhost->mmiobase + VIA_CRDR_PCICTRL_OFF;

	sdhost->घातer = MMC_VDD_165_195;

	gatt = VIA_CRDR_PCICLKGATT_3V3 | VIA_CRDR_PCICLKGATT_PAD_PWRON;
	ग_लिखोb(gatt, sdhost->pcictrl_mmiobase + VIA_CRDR_PCICLKGATT);
	via_pwron_sleep(sdhost);
	gatt |= VIA_CRDR_PCICLKGATT_SFTRST;
	ग_लिखोb(gatt, sdhost->pcictrl_mmiobase + VIA_CRDR_PCICLKGATT);
	msleep(3);

	via_init_mmc_host(sdhost);

	ret =
	    request_irq(pcidev->irq, via_sdc_isr, IRQF_SHARED, DRV_NAME,
			sdhost);
	अगर (ret)
		जाओ unmap;

	ग_लिखोb(VIA_CRDR_PCIINTCTRL_SDCIRQEN,
	       sdhost->pcictrl_mmiobase + VIA_CRDR_PCIINTCTRL);
	ग_लिखोb(VIA_CRDR_PCITMOCTRL_1024MS,
	       sdhost->pcictrl_mmiobase + VIA_CRDR_PCITMOCTRL);

	/* device-specअगरic quirks */
	अगर (pcidev->subप्रणाली_venकरोr == PCI_VENDOR_ID_LENOVO &&
	    pcidev->subप्रणाली_device == 0x3891)
		sdhost->quirks = VIA_CRDR_QUIRK_300MS_PWRDELAY;

	mmc_add_host(mmc);

	वापस 0;

unmap:
	iounmap(sdhost->mmiobase);
मुक्त_mmc_host:
	dev_set_drvdata(&pcidev->dev, शून्य);
	mmc_मुक्त_host(mmc);
release:
	pci_release_regions(pcidev);
disable:
	pci_disable_device(pcidev);

	वापस ret;
पूर्ण

अटल व्योम via_sd_हटाओ(काष्ठा pci_dev *pcidev)
अणु
	काष्ठा via_crdr_mmc_host *sdhost = pci_get_drvdata(pcidev);
	अचिन्हित दीर्घ flags;
	u8 gatt;

	spin_lock_irqsave(&sdhost->lock, flags);

	/* Ensure we करोn't accept more commands from mmc layer */
	sdhost->reject = 1;

	/* Disable generating further पूर्णांकerrupts */
	ग_लिखोb(0x0, sdhost->pcictrl_mmiobase + VIA_CRDR_PCIINTCTRL);

	अगर (sdhost->mrq) अणु
		pr_err("%s: Controller removed during "
			"transfer\n", mmc_hostname(sdhost->mmc));

		/* make sure all DMA is stopped */
		ग_लिखोl(VIA_CRDR_DMACTRL_SFTRST,
			sdhost->ddma_mmiobase + VIA_CRDR_DMACTRL);
		sdhost->mrq->cmd->error = -ENOMEDIUM;
		अगर (sdhost->mrq->stop)
			sdhost->mrq->stop->error = -ENOMEDIUM;
		tasklet_schedule(&sdhost->finish_tasklet);
	पूर्ण
	spin_unlock_irqrestore(&sdhost->lock, flags);

	mmc_हटाओ_host(sdhost->mmc);

	मुक्त_irq(pcidev->irq, sdhost);

	del_समयr_sync(&sdhost->समयr);

	tasklet_समाप्त(&sdhost->finish_tasklet);

	/* चयन off घातer */
	gatt = पढ़ोb(sdhost->pcictrl_mmiobase + VIA_CRDR_PCICLKGATT);
	gatt &= ~VIA_CRDR_PCICLKGATT_PAD_PWRON;
	ग_लिखोb(gatt, sdhost->pcictrl_mmiobase + VIA_CRDR_PCICLKGATT);

	iounmap(sdhost->mmiobase);
	dev_set_drvdata(&pcidev->dev, शून्य);
	mmc_मुक्त_host(sdhost->mmc);
	pci_release_regions(pcidev);
	pci_disable_device(pcidev);

	pr_info(DRV_NAME
		": VIA SDMMC controller at %s [%04x:%04x] has been removed\n",
		pci_name(pcidev), (पूर्णांक)pcidev->venकरोr, (पूर्णांक)pcidev->device);
पूर्ण

अटल व्योम __maybe_unused via_init_sdc_pm(काष्ठा via_crdr_mmc_host *host)
अणु
	काष्ठा sdhcreg *pm_sdhcreg;
	व्योम __iomem *addrbase;
	u32 lenreg;
	u16 status;

	pm_sdhcreg = &(host->pm_sdhc_reg);
	addrbase = host->sdhc_mmiobase;

	ग_लिखोl(0x0, addrbase + VIA_CRDR_SDINTMASK);

	lenreg = VIA_CRDR_SDBLKLEN_GPIDET | VIA_CRDR_SDBLKLEN_INTEN;
	ग_लिखोl(lenreg, addrbase + VIA_CRDR_SDBLKLEN);

	status = पढ़ोw(addrbase + VIA_CRDR_SDSTATUS);
	status &= VIA_CRDR_SDSTS_W1C_MASK;
	ग_लिखोw(status, addrbase + VIA_CRDR_SDSTATUS);

	status = पढ़ोw(addrbase + VIA_CRDR_SDSTATUS2);
	status |= VIA_CRDR_SDSTS_CFE;
	ग_लिखोw(status, addrbase + VIA_CRDR_SDSTATUS2);

	ग_लिखोl(pm_sdhcreg->sdcontrol_reg, addrbase + VIA_CRDR_SDCTRL);
	ग_लिखोl(pm_sdhcreg->sdcmdarg_reg, addrbase + VIA_CRDR_SDCARG);
	ग_लिखोl(pm_sdhcreg->sdपूर्णांकmask_reg, addrbase + VIA_CRDR_SDINTMASK);
	ग_लिखोl(pm_sdhcreg->sdrspपंचांगo_reg, addrbase + VIA_CRDR_SDRSPTMO);
	ग_लिखोl(pm_sdhcreg->sdclksel_reg, addrbase + VIA_CRDR_SDCLKSEL);
	ग_लिखोl(pm_sdhcreg->sdextctrl_reg, addrbase + VIA_CRDR_SDEXTCTRL);

	via_prपूर्णांक_pcictrl(host);
	via_prपूर्णांक_sdchc(host);
पूर्ण

अटल पूर्णांक __maybe_unused via_sd_suspend(काष्ठा device *dev)
अणु
	काष्ठा via_crdr_mmc_host *host;
	अचिन्हित दीर्घ flags;

	host = dev_get_drvdata(dev);

	spin_lock_irqsave(&host->lock, flags);
	via_save_pcictrlreg(host);
	via_save_sdcreg(host);
	spin_unlock_irqrestore(&host->lock, flags);

	device_wakeup_enable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused via_sd_resume(काष्ठा device *dev)
अणु
	काष्ठा via_crdr_mmc_host *sdhost;
	u8 gatt;

	sdhost = dev_get_drvdata(dev);

	gatt = VIA_CRDR_PCICLKGATT_PAD_PWRON;
	अगर (sdhost->घातer == MMC_VDD_165_195)
		gatt &= ~VIA_CRDR_PCICLKGATT_3V3;
	अन्यथा
		gatt |= VIA_CRDR_PCICLKGATT_3V3;
	ग_लिखोb(gatt, sdhost->pcictrl_mmiobase + VIA_CRDR_PCICLKGATT);
	via_pwron_sleep(sdhost);
	gatt |= VIA_CRDR_PCICLKGATT_SFTRST;
	ग_लिखोb(gatt, sdhost->pcictrl_mmiobase + VIA_CRDR_PCICLKGATT);
	msleep(3);

	msleep(100);

	via_restore_pcictrlreg(sdhost);
	via_init_sdc_pm(sdhost);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(via_sd_pm_ops, via_sd_suspend, via_sd_resume);

अटल काष्ठा pci_driver via_sd_driver = अणु
	.name = DRV_NAME,
	.id_table = via_ids,
	.probe = via_sd_probe,
	.हटाओ = via_sd_हटाओ,
	.driver.pm = &via_sd_pm_ops,
पूर्ण;

module_pci_driver(via_sd_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VIA Technologies Inc.");
MODULE_DESCRIPTION("VIA SD/MMC Card Interface driver");
