<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    ata_piix.c - Intel PATA/SATA controllers
 *
 *    Maपूर्णांकained by:  Tejun Heo <tj@kernel.org>
 *    		    Please ALWAYS copy linux-ide@vger.kernel.org
 *		    on emails.
 *
 *	Copyright 2003-2005 Red Hat Inc
 *	Copyright 2003-2005 Jeff Garzik
 *
 *	Copyright header from piix.c:
 *
 *  Copyright (C) 1998-1999 Andrzej Krzysztofowicz, Author and Maपूर्णांकainer
 *  Copyright (C) 1998-2000 Andre Hedrick <andre@linux-ide.org>
 *  Copyright (C) 2003 Red Hat Inc
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 *
 *  Hardware करोcumentation available at http://developer.पूर्णांकel.com/
 *
 * Documentation
 *	Publicly available from Intel web site. Errata करोcumentation
 * is also खुलाly available. As an aide to anyone hacking on this
 * driver the list of errata that are relevant is below, going back to
 * PIIX4. Older device करोcumentation is now a bit tricky to find.
 *
 * The chipsets all follow very much the same design. The original Triton
 * series chipsets करो _not_ support independent device timings, but this
 * is fixed in Triton II. With the odd mobile exception the chips then
 * change little except in gaining more modes until SATA arrives. This
 * driver supports only the chips with independent timing (that is those
 * with SITRE and the 0x44 timing रेजिस्टर). See pata_oldpiix and pata_mpiix
 * क्रम the early chip drivers.
 *
 * Errata of note:
 *
 * Unfixable
 *	PIIX4    errata #9	- Only on ultra obscure hw
 *	ICH3	 errata #13     - Not observed to affect real hw
 *				  by Intel
 *
 * Things we must deal with
 *	PIIX4	errata #10	- BM IDE hang with non UDMA
 *				  (must stop/start dma to recover)
 *	440MX   errata #15	- As PIIX4 errata #10
 *	PIIX4	errata #15	- Must not पढ़ो control रेजिस्टरs
 * 				  during a PIO transfer
 *	440MX   errata #13	- As PIIX4 errata #15
 *	ICH2	errata #21	- DMA mode 0 करोesn't work right
 *	ICH0/1  errata #55	- As ICH2 errata #21
 *	ICH2	spec c #9	- Extra operations needed to handle
 *				  drive hotswap [NOT YET SUPPORTED]
 *	ICH2    spec c #20	- IDE PRD must not cross a 64K boundary
 *				  and must be dword aligned
 *	ICH2    spec c #24	- UDMA mode 4,5 t85/86 should be 6ns not 3.3
 *	ICH7	errata #16	- MWDMA1 timings are incorrect
 *
 * Should have been BIOS fixed:
 *	450NX:	errata #19	- DMA hangs on old 450NX
 *	450NX:  errata #20	- DMA hangs on old 450NX
 *	450NX:  errata #25	- Corruption with DMA on old 450NX
 *	ICH3    errata #15      - IDE deadlock under high load
 *				  (BIOS must set dev 31 fn 0 bit 23)
 *	ICH3	errata #18	- Don't use native mode
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gfp.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>
#समावेश <linux/dmi.h>

#घोषणा DRV_NAME	"ata_piix"
#घोषणा DRV_VERSION	"2.13"

क्रमागत अणु
	PIIX_IOCFG		= 0x54, /* IDE I/O configuration रेजिस्टर */
	ICH5_PMR		= 0x90, /* address map रेजिस्टर */
	ICH5_PCS		= 0x92,	/* port control and status */
	PIIX_SIDPR_BAR		= 5,
	PIIX_SIDPR_LEN		= 16,
	PIIX_SIDPR_IDX		= 0,
	PIIX_SIDPR_DATA		= 4,

	PIIX_FLAG_CHECKINTR	= (1 << 28), /* make sure PCI INTx enabled */
	PIIX_FLAG_SIDPR		= (1 << 29), /* SATA idx/data pair regs */

	PIIX_PATA_FLAGS		= ATA_FLAG_SLAVE_POSS,
	PIIX_SATA_FLAGS		= ATA_FLAG_SATA | PIIX_FLAG_CHECKINTR,

	PIIX_FLAG_PIO16		= (1 << 30), /*support 16bit PIO only*/

	PIIX_80C_PRI		= (1 << 5) | (1 << 4),
	PIIX_80C_SEC		= (1 << 7) | (1 << 6),

	/* स्थिरants क्रम mapping table */
	P0			= 0,  /* port 0 */
	P1			= 1,  /* port 1 */
	P2			= 2,  /* port 2 */
	P3			= 3,  /* port 3 */
	IDE			= -1, /* IDE */
	NA			= -2, /* not available */
	RV			= -3, /* reserved */

	PIIX_AHCI_DEVICE	= 6,

	/* host->flags bits */
	PIIX_HOST_BROKEN_SUSPEND = (1 << 24),
पूर्ण;

क्रमागत piix_controller_ids अणु
	/* controller IDs */
	piix_pata_mwdma,	/* PIIX3 MWDMA only */
	piix_pata_33,		/* PIIX4 at 33Mhz */
	ich_pata_33,		/* ICH up to UDMA 33 only */
	ich_pata_66,		/* ICH up to 66 Mhz */
	ich_pata_100,		/* ICH up to UDMA 100 */
	ich_pata_100_nomwdma1,	/* ICH up to UDMA 100 but with no MWDMA1*/
	ich5_sata,
	ich6_sata,
	ich6m_sata,
	ich8_sata,
	ich8_2port_sata,
	ich8m_apple_sata,	/* locks up on second port enable */
	tolapai_sata,
	piix_pata_vmw,			/* PIIX4 क्रम VMware, spurious DMA_ERR */
	ich8_sata_snb,
	ich8_2port_sata_snb,
	ich8_2port_sata_byt,
पूर्ण;

काष्ठा piix_map_db अणु
	स्थिर u32 mask;
	स्थिर u16 port_enable;
	स्थिर पूर्णांक map[][4];
पूर्ण;

काष्ठा piix_host_priv अणु
	स्थिर पूर्णांक *map;
	u32 saved_iocfg;
	व्योम __iomem *sidpr;
पूर्ण;

अटल अचिन्हित पूर्णांक in_module_init = 1;

अटल स्थिर काष्ठा pci_device_id piix_pci_tbl[] = अणु
	/* Intel PIIX3 क्रम the 430HX etc */
	अणु 0x8086, 0x7010, PCI_ANY_ID, PCI_ANY_ID, 0, 0, piix_pata_mwdma पूर्ण,
	/* VMware ICH4 */
	अणु 0x8086, 0x7111, 0x15ad, 0x1976, 0, 0, piix_pata_vmw पूर्ण,
	/* Intel PIIX4 क्रम the 430TX/440BX/MX chipset: UDMA 33 */
	/* Also PIIX4E (fn3 rev 2) and PIIX4M (fn3 rev 3) */
	अणु 0x8086, 0x7111, PCI_ANY_ID, PCI_ANY_ID, 0, 0, piix_pata_33 पूर्ण,
	/* Intel PIIX4 */
	अणु 0x8086, 0x7199, PCI_ANY_ID, PCI_ANY_ID, 0, 0, piix_pata_33 पूर्ण,
	/* Intel PIIX4 */
	अणु 0x8086, 0x7601, PCI_ANY_ID, PCI_ANY_ID, 0, 0, piix_pata_33 पूर्ण,
	/* Intel PIIX */
	अणु 0x8086, 0x84CA, PCI_ANY_ID, PCI_ANY_ID, 0, 0, piix_pata_33 पूर्ण,
	/* Intel ICH (i810, i815, i840) UDMA 66*/
	अणु 0x8086, 0x2411, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_66 पूर्ण,
	/* Intel ICH0 : UDMA 33*/
	अणु 0x8086, 0x2421, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_33 पूर्ण,
	/* Intel ICH2M */
	अणु 0x8086, 0x244A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 पूर्ण,
	/* Intel ICH2 (i810E2, i845, 850, 860) UDMA 100 */
	अणु 0x8086, 0x244B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 पूर्ण,
	/*  Intel ICH3M */
	अणु 0x8086, 0x248A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 पूर्ण,
	/* Intel ICH3 (E7500/1) UDMA 100 */
	अणु 0x8086, 0x248B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 पूर्ण,
	/* Intel ICH4-L */
	अणु 0x8086, 0x24C1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 पूर्ण,
	/* Intel ICH4 (i845GV, i845E, i852, i855) UDMA 100 */
	अणु 0x8086, 0x24CA, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 पूर्ण,
	अणु 0x8086, 0x24CB, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 पूर्ण,
	/* Intel ICH5 */
	अणु 0x8086, 0x24DB, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 पूर्ण,
	/* C-ICH (i810E2) */
	अणु 0x8086, 0x245B, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 पूर्ण,
	/* ESB (855GME/875P + 6300ESB) UDMA 100  */
	अणु 0x8086, 0x25A2, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 पूर्ण,
	/* ICH6 (and 6) (i915) UDMA 100 */
	अणु 0x8086, 0x266F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 पूर्ण,
	/* ICH7/7-R (i945, i975) UDMA 100*/
	अणु 0x8086, 0x27DF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100_nomwdma1 पूर्ण,
	अणु 0x8086, 0x269E, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100_nomwdma1 पूर्ण,
	/* ICH8 Mobile PATA Controller */
	अणु 0x8086, 0x2850, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich_pata_100 पूर्ण,

	/* SATA ports */

	/* 82801EB (ICH5) */
	अणु 0x8086, 0x24d1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich5_sata पूर्ण,
	/* 82801EB (ICH5) */
	अणु 0x8086, 0x24df, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich5_sata पूर्ण,
	/* 6300ESB (ICH5 variant with broken PCS present bits) */
	अणु 0x8086, 0x25a3, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich5_sata पूर्ण,
	/* 6300ESB pretending RAID */
	अणु 0x8086, 0x25b0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich5_sata पूर्ण,
	/* 82801FB/FW (ICH6/ICH6W) */
	अणु 0x8086, 0x2651, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich6_sata पूर्ण,
	/* 82801FR/FRW (ICH6R/ICH6RW) */
	अणु 0x8086, 0x2652, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich6_sata पूर्ण,
	/* 82801FBM ICH6M (ICH6R with only port 0 and 2 implemented).
	 * Attach अगरf the controller is in IDE mode. */
	अणु 0x8086, 0x2653, PCI_ANY_ID, PCI_ANY_ID,
	  PCI_CLASS_STORAGE_IDE << 8, 0xffff00, ich6m_sata पूर्ण,
	/* 82801GB/GR/GH (ICH7, identical to ICH6) */
	अणु 0x8086, 0x27c0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich6_sata पूर्ण,
	/* 82801GBM/GHM (ICH7M, identical to ICH6M)  */
	अणु 0x8086, 0x27c4, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich6m_sata पूर्ण,
	/* Enterprise Southbridge 2 (631xESB/632xESB) */
	अणु 0x8086, 0x2680, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich6_sata पूर्ण,
	/* SATA Controller 1 IDE (ICH8) */
	अणु 0x8086, 0x2820, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata पूर्ण,
	/* SATA Controller 2 IDE (ICH8) */
	अणु 0x8086, 0x2825, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* Mobile SATA Controller IDE (ICH8M), Apple */
	अणु 0x8086, 0x2828, 0x106b, 0x00a0, 0, 0, ich8m_apple_sata पूर्ण,
	अणु 0x8086, 0x2828, 0x106b, 0x00a1, 0, 0, ich8m_apple_sata पूर्ण,
	अणु 0x8086, 0x2828, 0x106b, 0x00a3, 0, 0, ich8m_apple_sata पूर्ण,
	/* Mobile SATA Controller IDE (ICH8M) */
	अणु 0x8086, 0x2828, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata पूर्ण,
	/* SATA Controller IDE (ICH9) */
	अणु 0x8086, 0x2920, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata पूर्ण,
	/* SATA Controller IDE (ICH9) */
	अणु 0x8086, 0x2921, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (ICH9) */
	अणु 0x8086, 0x2926, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (ICH9M) */
	अणु 0x8086, 0x2928, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (ICH9M) */
	अणु 0x8086, 0x292d, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (ICH9M) */
	अणु 0x8086, 0x292e, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata पूर्ण,
	/* SATA Controller IDE (Tolapai) */
	अणु 0x8086, 0x5028, PCI_ANY_ID, PCI_ANY_ID, 0, 0, tolapai_sata पूर्ण,
	/* SATA Controller IDE (ICH10) */
	अणु 0x8086, 0x3a00, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata पूर्ण,
	/* SATA Controller IDE (ICH10) */
	अणु 0x8086, 0x3a06, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (ICH10) */
	अणु 0x8086, 0x3a20, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata पूर्ण,
	/* SATA Controller IDE (ICH10) */
	अणु 0x8086, 0x3a26, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (PCH) */
	अणु 0x8086, 0x3b20, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata पूर्ण,
	/* SATA Controller IDE (PCH) */
	अणु 0x8086, 0x3b21, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (PCH) */
	अणु 0x8086, 0x3b26, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (PCH) */
	अणु 0x8086, 0x3b28, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata पूर्ण,
	/* SATA Controller IDE (PCH) */
	अणु 0x8086, 0x3b2d, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (PCH) */
	अणु 0x8086, 0x3b2e, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata पूर्ण,
	/* SATA Controller IDE (CPT) */
	अणु 0x8086, 0x1c00, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb पूर्ण,
	/* SATA Controller IDE (CPT) */
	अणु 0x8086, 0x1c01, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb पूर्ण,
	/* SATA Controller IDE (CPT) */
	अणु 0x8086, 0x1c08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (CPT) */
	अणु 0x8086, 0x1c09, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (PBG) */
	अणु 0x8086, 0x1d00, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb पूर्ण,
	/* SATA Controller IDE (PBG) */
	अणु 0x8086, 0x1d08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (Panther Poपूर्णांक) */
	अणु 0x8086, 0x1e00, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb पूर्ण,
	/* SATA Controller IDE (Panther Poपूर्णांक) */
	अणु 0x8086, 0x1e01, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb पूर्ण,
	/* SATA Controller IDE (Panther Poपूर्णांक) */
	अणु 0x8086, 0x1e08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (Panther Poपूर्णांक) */
	अणु 0x8086, 0x1e09, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (Lynx Poपूर्णांक) */
	अणु 0x8086, 0x8c00, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb पूर्ण,
	/* SATA Controller IDE (Lynx Poपूर्णांक) */
	अणु 0x8086, 0x8c01, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb पूर्ण,
	/* SATA Controller IDE (Lynx Poपूर्णांक) */
	अणु 0x8086, 0x8c08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata_snb पूर्ण,
	/* SATA Controller IDE (Lynx Poपूर्णांक) */
	अणु 0x8086, 0x8c09, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (Lynx Poपूर्णांक-LP) */
	अणु 0x8086, 0x9c00, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb पूर्ण,
	/* SATA Controller IDE (Lynx Poपूर्णांक-LP) */
	अणु 0x8086, 0x9c01, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb पूर्ण,
	/* SATA Controller IDE (Lynx Poपूर्णांक-LP) */
	अणु 0x8086, 0x9c08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (Lynx Poपूर्णांक-LP) */
	अणु 0x8086, 0x9c09, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (DH89xxCC) */
	अणु 0x8086, 0x2326, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (Avoton) */
	अणु 0x8086, 0x1f20, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb पूर्ण,
	/* SATA Controller IDE (Avoton) */
	अणु 0x8086, 0x1f21, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb पूर्ण,
	/* SATA Controller IDE (Avoton) */
	अणु 0x8086, 0x1f30, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (Avoton) */
	अणु 0x8086, 0x1f31, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (Wellsburg) */
	अणु 0x8086, 0x8d00, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb पूर्ण,
	/* SATA Controller IDE (Wellsburg) */
	अणु 0x8086, 0x8d08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata_snb पूर्ण,
	/* SATA Controller IDE (Wellsburg) */
	अणु 0x8086, 0x8d60, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb पूर्ण,
	/* SATA Controller IDE (Wellsburg) */
	अणु 0x8086, 0x8d68, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (BayTrail) */
	अणु 0x8086, 0x0F20, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata_byt पूर्ण,
	अणु 0x8086, 0x0F21, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata_byt पूर्ण,
	/* SATA Controller IDE (Coleto Creek) */
	अणु 0x8086, 0x23a6, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata पूर्ण,
	/* SATA Controller IDE (9 Series) */
	अणु 0x8086, 0x8c88, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata_snb पूर्ण,
	/* SATA Controller IDE (9 Series) */
	अणु 0x8086, 0x8c89, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_2port_sata_snb पूर्ण,
	/* SATA Controller IDE (9 Series) */
	अणु 0x8086, 0x8c80, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb पूर्ण,
	/* SATA Controller IDE (9 Series) */
	अणु 0x8086, 0x8c81, PCI_ANY_ID, PCI_ANY_ID, 0, 0, ich8_sata_snb पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल स्थिर काष्ठा piix_map_db ich5_map_db = अणु
	.mask = 0x7,
	.port_enable = 0x3,
	.map = अणु
		/* PM   PS   SM   SS       MAP  */
		अणु  P0,  NA,  P1,  NA पूर्ण, /* 000b */
		अणु  P1,  NA,  P0,  NA पूर्ण, /* 001b */
		अणु  RV,  RV,  RV,  RV पूर्ण,
		अणु  RV,  RV,  RV,  RV पूर्ण,
		अणु  P0,  P1, IDE, IDE पूर्ण, /* 100b */
		अणु  P1,  P0, IDE, IDE पूर्ण, /* 101b */
		अणु IDE, IDE,  P0,  P1 पूर्ण, /* 110b */
		अणु IDE, IDE,  P1,  P0 पूर्ण, /* 111b */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा piix_map_db ich6_map_db = अणु
	.mask = 0x3,
	.port_enable = 0xf,
	.map = अणु
		/* PM   PS   SM   SS       MAP */
		अणु  P0,  P2,  P1,  P3 पूर्ण, /* 00b */
		अणु IDE, IDE,  P1,  P3 पूर्ण, /* 01b */
		अणु  P0,  P2, IDE, IDE पूर्ण, /* 10b */
		अणु  RV,  RV,  RV,  RV पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा piix_map_db ich6m_map_db = अणु
	.mask = 0x3,
	.port_enable = 0x5,

	/* Map 01b isn't specअगरied in the करोc but some notebooks use
	 * it anyway.  MAP 01b have been spotted on both ICH6M and
	 * ICH7M.
	 */
	.map = अणु
		/* PM   PS   SM   SS       MAP */
		अणु  P0,  P2,  NA,  NA पूर्ण, /* 00b */
		अणु IDE, IDE,  P1,  P3 पूर्ण, /* 01b */
		अणु  P0,  P2, IDE, IDE पूर्ण, /* 10b */
		अणु  RV,  RV,  RV,  RV पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा piix_map_db ich8_map_db = अणु
	.mask = 0x3,
	.port_enable = 0xf,
	.map = अणु
		/* PM   PS   SM   SS       MAP */
		अणु  P0,  P2,  P1,  P3 पूर्ण, /* 00b (hardwired when in AHCI) */
		अणु  RV,  RV,  RV,  RV पूर्ण,
		अणु  P0,  P2, IDE, IDE पूर्ण, /* 10b (IDE mode) */
		अणु  RV,  RV,  RV,  RV पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा piix_map_db ich8_2port_map_db = अणु
	.mask = 0x3,
	.port_enable = 0x3,
	.map = अणु
		/* PM   PS   SM   SS       MAP */
		अणु  P0,  NA,  P1,  NA पूर्ण, /* 00b */
		अणु  RV,  RV,  RV,  RV पूर्ण, /* 01b */
		अणु  RV,  RV,  RV,  RV पूर्ण, /* 10b */
		अणु  RV,  RV,  RV,  RV पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा piix_map_db ich8m_apple_map_db = अणु
	.mask = 0x3,
	.port_enable = 0x1,
	.map = अणु
		/* PM   PS   SM   SS       MAP */
		अणु  P0,  NA,  NA,  NA पूर्ण, /* 00b */
		अणु  RV,  RV,  RV,  RV पूर्ण,
		अणु  P0,  P2, IDE, IDE पूर्ण, /* 10b */
		अणु  RV,  RV,  RV,  RV पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा piix_map_db tolapai_map_db = अणु
	.mask = 0x3,
	.port_enable = 0x3,
	.map = अणु
		/* PM   PS   SM   SS       MAP */
		अणु  P0,  NA,  P1,  NA पूर्ण, /* 00b */
		अणु  RV,  RV,  RV,  RV पूर्ण, /* 01b */
		अणु  RV,  RV,  RV,  RV पूर्ण, /* 10b */
		अणु  RV,  RV,  RV,  RV पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा piix_map_db *piix_map_db_table[] = अणु
	[ich5_sata]		= &ich5_map_db,
	[ich6_sata]		= &ich6_map_db,
	[ich6m_sata]		= &ich6m_map_db,
	[ich8_sata]		= &ich8_map_db,
	[ich8_2port_sata]	= &ich8_2port_map_db,
	[ich8m_apple_sata]	= &ich8m_apple_map_db,
	[tolapai_sata]		= &tolapai_map_db,
	[ich8_sata_snb]		= &ich8_map_db,
	[ich8_2port_sata_snb]	= &ich8_2port_map_db,
	[ich8_2port_sata_byt]	= &ich8_2port_map_db,
पूर्ण;

अटल स्थिर काष्ठा pci_bits piix_enable_bits[] = अणु
	अणु 0x41U, 1U, 0x80UL, 0x80UL पूर्ण,	/* port 0 */
	अणु 0x43U, 1U, 0x80UL, 0x80UL पूर्ण,	/* port 1 */
पूर्ण;

MODULE_AUTHOR("Andre Hedrick, Alan Cox, Andrzej Krzysztofowicz, Jeff Garzik");
MODULE_DESCRIPTION("SCSI low-level driver for Intel PIIX/ICH ATA controllers");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, piix_pci_tbl);
MODULE_VERSION(DRV_VERSION);

काष्ठा ich_laptop अणु
	u16 device;
	u16 subvenकरोr;
	u16 subdevice;
पूर्ण;

/*
 *	List of laptops that use लघु cables rather than 80 wire
 */

अटल स्थिर काष्ठा ich_laptop ich_laptop[] = अणु
	/* devid, subvenकरोr, subdev */
	अणु 0x27DF, 0x0005, 0x0280 पूर्ण,	/* ICH7 on Acer 5602WLMi */
	अणु 0x27DF, 0x1025, 0x0102 पूर्ण,	/* ICH7 on Acer 5602aWLMi */
	अणु 0x27DF, 0x1025, 0x0110 पूर्ण,	/* ICH7 on Acer 3682WLMi */
	अणु 0x27DF, 0x1028, 0x02b0 पूर्ण,	/* ICH7 on unknown Dell */
	अणु 0x27DF, 0x1043, 0x1267 पूर्ण,	/* ICH7 on Asus W5F */
	अणु 0x27DF, 0x103C, 0x30A1 पूर्ण,	/* ICH7 on HP Compaq nc2400 */
	अणु 0x27DF, 0x103C, 0x361a पूर्ण,	/* ICH7 on unknown HP  */
	अणु 0x27DF, 0x1071, 0xD221 पूर्ण,	/* ICH7 on Hercules EC-900 */
	अणु 0x27DF, 0x152D, 0x0778 पूर्ण,	/* ICH7 on unknown Intel */
	अणु 0x24CA, 0x1025, 0x0061 पूर्ण,	/* ICH4 on ACER Aspire 2023WLMi */
	अणु 0x24CA, 0x1025, 0x003d पूर्ण,	/* ICH4 on ACER TM290 */
	अणु 0x24CA, 0x10CF, 0x11AB पूर्ण,	/* ICH4M on Fujitsu-Siemens Lअगरebook S6120 */
	अणु 0x266F, 0x1025, 0x0066 पूर्ण,	/* ICH6 on ACER Aspire 1694WLMi */
	अणु 0x2653, 0x1043, 0x82D8 पूर्ण,	/* ICH6M on Asus Eee 701 */
	अणु 0x27df, 0x104d, 0x900e पूर्ण,	/* ICH7 on Sony TZ-90 */
	/* end marker */
	अणु 0, पूर्ण
पूर्ण;

अटल पूर्णांक piix_port_start(काष्ठा ata_port *ap)
अणु
	अगर (!(ap->flags & PIIX_FLAG_PIO16))
		ap->pflags |= ATA_PFLAG_PIO32 | ATA_PFLAG_PIO32CHANGE;

	वापस ata_bmdma_port_start(ap);
पूर्ण

/**
 *	ich_pata_cable_detect - Probe host controller cable detect info
 *	@ap: Port क्रम which cable detect info is desired
 *
 *	Read 80c cable indicator from ATA PCI device's PCI config
 *	रेजिस्टर.  This रेजिस्टर is normally set by firmware (BIOS).
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल पूर्णांक ich_pata_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	काष्ठा piix_host_priv *hpriv = ap->host->निजी_data;
	स्थिर काष्ठा ich_laptop *lap = &ich_laptop[0];
	u8 mask;

	/* Check क्रम specials */
	जबतक (lap->device) अणु
		अगर (lap->device == pdev->device &&
		    lap->subvenकरोr == pdev->subप्रणाली_venकरोr &&
		    lap->subdevice == pdev->subप्रणाली_device)
			वापस ATA_CBL_PATA40_SHORT;

		lap++;
	पूर्ण

	/* check BIOS cable detect results */
	mask = ap->port_no == 0 ? PIIX_80C_PRI : PIIX_80C_SEC;
	अगर ((hpriv->saved_iocfg & mask) == 0)
		वापस ATA_CBL_PATA40;
	वापस ATA_CBL_PATA80;
पूर्ण

/**
 *	piix_pata_prereset - prereset क्रम PATA host controller
 *	@link: Target link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	LOCKING:
 *	None (inherited from caller).
 */
अटल पूर्णांक piix_pata_prereset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	अगर (!pci_test_config_bits(pdev, &piix_enable_bits[ap->port_no]))
		वापस -ENOENT;
	वापस ata_sff_prereset(link, deadline);
पूर्ण

अटल DEFINE_SPINLOCK(piix_lock);

अटल व्योम piix_set_timings(काष्ठा ata_port *ap, काष्ठा ata_device *adev,
			     u8 pio)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(ap->host->dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक is_slave	= (adev->devno != 0);
	अचिन्हित पूर्णांक master_port= ap->port_no ? 0x42 : 0x40;
	अचिन्हित पूर्णांक slave_port	= 0x44;
	u16 master_data;
	u8 slave_data;
	u8 udma_enable;
	पूर्णांक control = 0;

	/*
	 *	See Intel Document 298600-004 क्रम the timing programing rules
	 *	क्रम ICH controllers.
	 */

	अटल स्थिर	 /* ISP  RTC */
	u8 timings[][2]	= अणु अणु 0, 0 पूर्ण,
			    अणु 0, 0 पूर्ण,
			    अणु 1, 0 पूर्ण,
			    अणु 2, 1 पूर्ण,
			    अणु 2, 3 पूर्ण, पूर्ण;

	अगर (pio >= 2)
		control |= 1;	/* TIME1 enable */
	अगर (ata_pio_need_iordy(adev))
		control |= 2;	/* IE enable */
	/* Intel specअगरies that the PPE functionality is क्रम disk only */
	अगर (adev->class == ATA_DEV_ATA)
		control |= 4;	/* PPE enable */
	/*
	 * If the drive MWDMA is faster than it can करो PIO then
	 * we must क्रमce PIO पूर्णांकo PIO0
	 */
	अगर (adev->pio_mode < XFER_PIO_0 + pio)
		/* Enable DMA timing only */
		control |= 8;	/* PIO cycles in PIO0 */

	spin_lock_irqsave(&piix_lock, flags);

	/* PIO configuration clears DTE unconditionally.  It will be
	 * programmed in set_dmamode which is guaranteed to be called
	 * after set_piomode अगर any DMA mode is available.
	 */
	pci_पढ़ो_config_word(dev, master_port, &master_data);
	अगर (is_slave) अणु
		/* clear TIME1|IE1|PPE1|DTE1 */
		master_data &= 0xff0f;
		/* enable PPE1, IE1 and TIME1 as needed */
		master_data |= (control << 4);
		pci_पढ़ो_config_byte(dev, slave_port, &slave_data);
		slave_data &= (ap->port_no ? 0x0f : 0xf0);
		/* Load the timing nibble क्रम this slave */
		slave_data |= ((timings[pio][0] << 2) | timings[pio][1])
						<< (ap->port_no ? 4 : 0);
	पूर्ण अन्यथा अणु
		/* clear ISP|RCT|TIME0|IE0|PPE0|DTE0 */
		master_data &= 0xccf0;
		/* Enable PPE, IE and TIME as appropriate */
		master_data |= control;
		/* load ISP and RCT */
		master_data |=
			(timings[pio][0] << 12) |
			(timings[pio][1] << 8);
	पूर्ण

	/* Enable SITRE (separate slave timing रेजिस्टर) */
	master_data |= 0x4000;
	pci_ग_लिखो_config_word(dev, master_port, master_data);
	अगर (is_slave)
		pci_ग_लिखो_config_byte(dev, slave_port, slave_data);

	/* Ensure the UDMA bit is off - it will be turned back on अगर
	   UDMA is selected */

	अगर (ap->udma_mask) अणु
		pci_पढ़ो_config_byte(dev, 0x48, &udma_enable);
		udma_enable &= ~(1 << (2 * ap->port_no + adev->devno));
		pci_ग_लिखो_config_byte(dev, 0x48, udma_enable);
	पूर्ण

	spin_unlock_irqrestore(&piix_lock, flags);
पूर्ण

/**
 *	piix_set_piomode - Initialize host controller PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Drive in question
 *
 *	Set PIO mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम piix_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	piix_set_timings(ap, adev, adev->pio_mode - XFER_PIO_0);
पूर्ण

/**
 *	करो_pata_set_dmamode - Initialize host controller PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Drive in question
 *	@isich: set अगर the chip is an ICH device
 *
 *	Set UDMA mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम करो_pata_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev, पूर्णांक isich)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(ap->host->dev);
	अचिन्हित दीर्घ flags;
	u8 speed		= adev->dma_mode;
	पूर्णांक devid		= adev->devno + 2 * ap->port_no;
	u8 udma_enable		= 0;

	अगर (speed >= XFER_UDMA_0) अणु
		अचिन्हित पूर्णांक udma = speed - XFER_UDMA_0;
		u16 udma_timing;
		u16 ideconf;
		पूर्णांक u_घड़ी, u_speed;

		spin_lock_irqsave(&piix_lock, flags);

		pci_पढ़ो_config_byte(dev, 0x48, &udma_enable);

		/*
		 * UDMA is handled by a combination of घड़ी चयनing and
		 * selection of भागiders
		 *
		 * Handy rule: Odd modes are UDMATIMx 01, even are 02
		 *	       except UDMA0 which is 00
		 */
		u_speed = min(2 - (udma & 1), udma);
		अगर (udma == 5)
			u_घड़ी = 0x1000;	/* 100Mhz */
		अन्यथा अगर (udma > 2)
			u_घड़ी = 1;		/* 66Mhz */
		अन्यथा
			u_घड़ी = 0;		/* 33Mhz */

		udma_enable |= (1 << devid);

		/* Load the CT/RP selection */
		pci_पढ़ो_config_word(dev, 0x4A, &udma_timing);
		udma_timing &= ~(3 << (4 * devid));
		udma_timing |= u_speed << (4 * devid);
		pci_ग_लिखो_config_word(dev, 0x4A, udma_timing);

		अगर (isich) अणु
			/* Select a 33/66/100Mhz घड़ी */
			pci_पढ़ो_config_word(dev, 0x54, &ideconf);
			ideconf &= ~(0x1001 << devid);
			ideconf |= u_घड़ी << devid;
			/* For ICH or later we should set bit 10 क्रम better
			   perक्रमmance (WR_PingPong_En) */
			pci_ग_लिखो_config_word(dev, 0x54, ideconf);
		पूर्ण

		pci_ग_लिखो_config_byte(dev, 0x48, udma_enable);

		spin_unlock_irqrestore(&piix_lock, flags);
	पूर्ण अन्यथा अणु
		/* MWDMA is driven by the PIO timings. */
		अचिन्हित पूर्णांक mwdma = speed - XFER_MW_DMA_0;
		स्थिर अचिन्हित पूर्णांक needed_pio[3] = अणु
			XFER_PIO_0, XFER_PIO_3, XFER_PIO_4
		पूर्ण;
		पूर्णांक pio = needed_pio[mwdma] - XFER_PIO_0;

		/* XFER_PIO_0 is never used currently */
		piix_set_timings(ap, adev, pio);
	पूर्ण
पूर्ण

/**
 *	piix_set_dmamode - Initialize host controller PATA DMA timings
 *	@ap: Port whose timings we are configuring
 *	@adev: um
 *
 *	Set MW/UDMA mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम piix_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	करो_pata_set_dmamode(ap, adev, 0);
पूर्ण

/**
 *	ich_set_dmamode - Initialize host controller PATA DMA timings
 *	@ap: Port whose timings we are configuring
 *	@adev: um
 *
 *	Set MW/UDMA mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम ich_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	करो_pata_set_dmamode(ap, adev, 1);
पूर्ण

/*
 * Serial ATA Index/Data Pair Superset Registers access
 *
 * Beginning from ICH8, there's a sane way to access SCRs using index
 * and data रेजिस्टर pair located at BAR5 which means that we have
 * separate SCRs क्रम master and slave.  This is handled using libata
 * slave_link facility.
 */
अटल स्थिर पूर्णांक piix_sidx_map[] = अणु
	[SCR_STATUS]	= 0,
	[SCR_ERROR]	= 2,
	[SCR_CONTROL]	= 1,
पूर्ण;

अटल व्योम piix_sidpr_sel(काष्ठा ata_link *link, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा piix_host_priv *hpriv = ap->host->निजी_data;

	ioग_लिखो32(((ap->port_no * 2 + link->pmp) << 8) | piix_sidx_map[reg],
		  hpriv->sidpr + PIIX_SIDPR_IDX);
पूर्ण

अटल पूर्णांक piix_sidpr_scr_पढ़ो(काष्ठा ata_link *link,
			       अचिन्हित पूर्णांक reg, u32 *val)
अणु
	काष्ठा piix_host_priv *hpriv = link->ap->host->निजी_data;

	अगर (reg >= ARRAY_SIZE(piix_sidx_map))
		वापस -EINVAL;

	piix_sidpr_sel(link, reg);
	*val = ioपढ़ो32(hpriv->sidpr + PIIX_SIDPR_DATA);
	वापस 0;
पूर्ण

अटल पूर्णांक piix_sidpr_scr_ग_लिखो(काष्ठा ata_link *link,
				अचिन्हित पूर्णांक reg, u32 val)
अणु
	काष्ठा piix_host_priv *hpriv = link->ap->host->निजी_data;

	अगर (reg >= ARRAY_SIZE(piix_sidx_map))
		वापस -EINVAL;

	piix_sidpr_sel(link, reg);
	ioग_लिखो32(val, hpriv->sidpr + PIIX_SIDPR_DATA);
	वापस 0;
पूर्ण

अटल पूर्णांक piix_sidpr_set_lpm(काष्ठा ata_link *link, क्रमागत ata_lpm_policy policy,
			      अचिन्हित hपूर्णांकs)
अणु
	वापस sata_link_scr_lpm(link, policy, false);
पूर्ण

अटल bool piix_irq_check(काष्ठा ata_port *ap)
अणु
	अगर (unlikely(!ap->ioaddr.bmdma_addr))
		वापस false;

	वापस ap->ops->bmdma_status(ap) & ATA_DMA_INTR;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक piix_broken_suspend(व्योम)
अणु
	अटल स्थिर काष्ठा dmi_प्रणाली_id sysids[] = अणु
		अणु
			.ident = "TECRA M3",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
				DMI_MATCH(DMI_PRODUCT_NAME, "TECRA M3"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "TECRA M3",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
				DMI_MATCH(DMI_PRODUCT_NAME, "Tecra M3"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "TECRA M3",
			.matches = अणु
				DMI_MATCH(DMI_OEM_STRING, "Tecra M3,"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "TECRA M4",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
				DMI_MATCH(DMI_PRODUCT_NAME, "Tecra M4"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "TECRA M4",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
				DMI_MATCH(DMI_PRODUCT_NAME, "TECRA M4"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "TECRA M5",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
				DMI_MATCH(DMI_PRODUCT_NAME, "TECRA M5"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "TECRA M6",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
				DMI_MATCH(DMI_PRODUCT_NAME, "TECRA M6"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "TECRA M7",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
				DMI_MATCH(DMI_PRODUCT_NAME, "TECRA M7"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "TECRA A8",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
				DMI_MATCH(DMI_PRODUCT_NAME, "TECRA A8"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "Satellite R20",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
				DMI_MATCH(DMI_PRODUCT_NAME, "Satellite R20"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "Satellite R25",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
				DMI_MATCH(DMI_PRODUCT_NAME, "Satellite R25"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "Satellite U200",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
				DMI_MATCH(DMI_PRODUCT_NAME, "Satellite U200"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "Satellite U200",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
				DMI_MATCH(DMI_PRODUCT_NAME, "SATELLITE U200"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "Satellite Pro U200",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
				DMI_MATCH(DMI_PRODUCT_NAME, "SATELLITE PRO U200"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "Satellite U205",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
				DMI_MATCH(DMI_PRODUCT_NAME, "Satellite U205"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "SATELLITE U205",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
				DMI_MATCH(DMI_PRODUCT_NAME, "SATELLITE U205"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "Satellite Pro A120",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
				DMI_MATCH(DMI_PRODUCT_NAME, "Satellite Pro A120"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "Portege M500",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
				DMI_MATCH(DMI_PRODUCT_NAME, "PORTEGE M500"),
			पूर्ण,
		पूर्ण,
		अणु
			.ident = "VGN-BX297XP",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
				DMI_MATCH(DMI_PRODUCT_NAME, "VGN-BX297XP"),
			पूर्ण,
		पूर्ण,

		अणु पूर्ण	/* terminate list */
	पूर्ण;

	अगर (dmi_check_प्रणाली(sysids))
		वापस 1;

	/* TECRA M4 someबार क्रममाला_लो its identअगरy and reports bogus
	 * DMI inक्रमmation.  As the bogus inक्रमmation is a bit
	 * generic, match as many entries as possible.  This manual
	 * matching is necessary because dmi_प्रणाली_id.matches is
	 * limited to four entries.
	 */
	अगर (dmi_match(DMI_SYS_VENDOR, "TOSHIBA") &&
	    dmi_match(DMI_PRODUCT_NAME, "000000") &&
	    dmi_match(DMI_PRODUCT_VERSION, "000000") &&
	    dmi_match(DMI_PRODUCT_SERIAL, "000000") &&
	    dmi_match(DMI_BOARD_VENDOR, "TOSHIBA") &&
	    dmi_match(DMI_BOARD_NAME, "Portable PC") &&
	    dmi_match(DMI_BOARD_VERSION, "Version A0"))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक piix_pci_device_suspend(काष्ठा pci_dev *pdev, pm_message_t mesg)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	rc = ata_host_suspend(host, mesg);
	अगर (rc)
		वापस rc;

	/* Some braindamaged ACPI suspend implementations expect the
	 * controller to be awake on entry; otherwise, it burns cpu
	 * cycles and घातer trying to करो something to the sleeping
	 * beauty.
	 */
	अगर (piix_broken_suspend() && (mesg.event & PM_EVENT_SLEEP)) अणु
		pci_save_state(pdev);

		/* mark its घातer state as "unknown", since we करोn't
		 * know अगर e.g. the BIOS will change its device state
		 * when we suspend.
		 */
		अगर (pdev->current_state == PCI_D0)
			pdev->current_state = PCI_UNKNOWN;

		/* tell resume that it's waking up from broken suspend */
		spin_lock_irqsave(&host->lock, flags);
		host->flags |= PIIX_HOST_BROKEN_SUSPEND;
		spin_unlock_irqrestore(&host->lock, flags);
	पूर्ण अन्यथा
		ata_pci_device_करो_suspend(pdev, mesg);

	वापस 0;
पूर्ण

अटल पूर्णांक piix_pci_device_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	अगर (host->flags & PIIX_HOST_BROKEN_SUSPEND) अणु
		spin_lock_irqsave(&host->lock, flags);
		host->flags &= ~PIIX_HOST_BROKEN_SUSPEND;
		spin_unlock_irqrestore(&host->lock, flags);

		pci_set_घातer_state(pdev, PCI_D0);
		pci_restore_state(pdev);

		/* PCI device wasn't disabled during suspend.  Use
		 * pci_reenable_device() to aव्योम affecting the enable
		 * count.
		 */
		rc = pci_reenable_device(pdev);
		अगर (rc)
			dev_err(&pdev->dev,
				"failed to enable device after resume (%d)\n",
				rc);
	पूर्ण अन्यथा
		rc = ata_pci_device_करो_resume(pdev);

	अगर (rc == 0)
		ata_host_resume(host);

	वापस rc;
पूर्ण
#पूर्ण_अगर

अटल u8 piix_vmw_bmdma_status(काष्ठा ata_port *ap)
अणु
	वापस ata_bmdma_status(ap) & ~ATA_DMA_ERR;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा piix_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations piix_sata_ops = अणु
	.inherits		= &ata_bmdma32_port_ops,
	.sff_irq_check		= piix_irq_check,
	.port_start		= piix_port_start,
पूर्ण;

अटल काष्ठा ata_port_operations piix_pata_ops = अणु
	.inherits		= &piix_sata_ops,
	.cable_detect		= ata_cable_40wire,
	.set_piomode		= piix_set_piomode,
	.set_dmamode		= piix_set_dmamode,
	.prereset		= piix_pata_prereset,
पूर्ण;

अटल काष्ठा ata_port_operations piix_vmw_ops = अणु
	.inherits		= &piix_pata_ops,
	.bmdma_status		= piix_vmw_bmdma_status,
पूर्ण;

अटल काष्ठा ata_port_operations ich_pata_ops = अणु
	.inherits		= &piix_pata_ops,
	.cable_detect		= ich_pata_cable_detect,
	.set_dmamode		= ich_set_dmamode,
पूर्ण;

अटल काष्ठा device_attribute *piix_sidpr_shost_attrs[] = अणु
	&dev_attr_link_घातer_management_policy,
	शून्य
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा piix_sidpr_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
	.shost_attrs		= piix_sidpr_shost_attrs,
पूर्ण;

अटल काष्ठा ata_port_operations piix_sidpr_sata_ops = अणु
	.inherits		= &piix_sata_ops,
	.hardreset		= sata_std_hardreset,
	.scr_पढ़ो		= piix_sidpr_scr_पढ़ो,
	.scr_ग_लिखो		= piix_sidpr_scr_ग_लिखो,
	.set_lpm		= piix_sidpr_set_lpm,
पूर्ण;

अटल काष्ठा ata_port_info piix_port_info[] = अणु
	[piix_pata_mwdma] =	/* PIIX3 MWDMA only */
	अणु
		.flags		= PIIX_PATA_FLAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONLY, /* mwdma1-2 ?? CHECK 0 should be ok but slow */
		.port_ops	= &piix_pata_ops,
	पूर्ण,

	[piix_pata_33] =	/* PIIX4 at 33MHz */
	अणु
		.flags		= PIIX_PATA_FLAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONLY, /* mwdma1-2 ?? CHECK 0 should be ok but slow */
		.udma_mask	= ATA_UDMA2,
		.port_ops	= &piix_pata_ops,
	पूर्ण,

	[ich_pata_33] =		/* ICH0 - ICH at 33Mhz*/
	अणु
		.flags		= PIIX_PATA_FLAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONLY, /* Check: maybe MWDMA0 is ok  */
		.udma_mask	= ATA_UDMA2,
		.port_ops	= &ich_pata_ops,
	पूर्ण,

	[ich_pata_66] =		/* ICH controllers up to 66MHz */
	अणु
		.flags		= PIIX_PATA_FLAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONLY, /* MWDMA0 is broken on chip */
		.udma_mask	= ATA_UDMA4,
		.port_ops	= &ich_pata_ops,
	पूर्ण,

	[ich_pata_100] =
	अणु
		.flags		= PIIX_PATA_FLAGS | PIIX_FLAG_CHECKINTR,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONLY,
		.udma_mask	= ATA_UDMA5,
		.port_ops	= &ich_pata_ops,
	पूर्ण,

	[ich_pata_100_nomwdma1] =
	अणु
		.flags		= PIIX_PATA_FLAGS | PIIX_FLAG_CHECKINTR,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2_ONLY,
		.udma_mask	= ATA_UDMA5,
		.port_ops	= &ich_pata_ops,
	पूर्ण,

	[ich5_sata] =
	अणु
		.flags		= PIIX_SATA_FLAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &piix_sata_ops,
	पूर्ण,

	[ich6_sata] =
	अणु
		.flags		= PIIX_SATA_FLAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &piix_sata_ops,
	पूर्ण,

	[ich6m_sata] =
	अणु
		.flags		= PIIX_SATA_FLAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &piix_sata_ops,
	पूर्ण,

	[ich8_sata] =
	अणु
		.flags		= PIIX_SATA_FLAGS | PIIX_FLAG_SIDPR,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &piix_sata_ops,
	पूर्ण,

	[ich8_2port_sata] =
	अणु
		.flags		= PIIX_SATA_FLAGS | PIIX_FLAG_SIDPR,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &piix_sata_ops,
	पूर्ण,

	[tolapai_sata] =
	अणु
		.flags		= PIIX_SATA_FLAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &piix_sata_ops,
	पूर्ण,

	[ich8m_apple_sata] =
	अणु
		.flags		= PIIX_SATA_FLAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &piix_sata_ops,
	पूर्ण,

	[piix_pata_vmw] =
	अणु
		.flags		= PIIX_PATA_FLAGS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONLY, /* mwdma1-2 ?? CHECK 0 should be ok but slow */
		.udma_mask	= ATA_UDMA2,
		.port_ops	= &piix_vmw_ops,
	पूर्ण,

	/*
	 * some Sandybridge chipsets have broken 32 mode up to now,
	 * see https://bugzilla.kernel.org/show_bug.cgi?id=40592
	 */
	[ich8_sata_snb] =
	अणु
		.flags		= PIIX_SATA_FLAGS | PIIX_FLAG_SIDPR | PIIX_FLAG_PIO16,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &piix_sata_ops,
	पूर्ण,

	[ich8_2port_sata_snb] =
	अणु
		.flags		= PIIX_SATA_FLAGS | PIIX_FLAG_SIDPR
					| PIIX_FLAG_PIO16,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &piix_sata_ops,
	पूर्ण,

	[ich8_2port_sata_byt] =
	अणु
		.flags          = PIIX_SATA_FLAGS | PIIX_FLAG_SIDPR | PIIX_FLAG_PIO16,
		.pio_mask       = ATA_PIO4,
		.mwdma_mask     = ATA_MWDMA2,
		.udma_mask      = ATA_UDMA6,
		.port_ops       = &piix_sata_ops,
	पूर्ण,

पूर्ण;

#घोषणा AHCI_PCI_BAR 5
#घोषणा AHCI_GLOBAL_CTL 0x04
#घोषणा AHCI_ENABLE (1 << 31)
अटल पूर्णांक piix_disable_ahci(काष्ठा pci_dev *pdev)
अणु
	व्योम __iomem *mmio;
	u32 पंचांगp;
	पूर्णांक rc = 0;

	/* BUG: pci_enable_device has not yet been called.  This
	 * works because this device is usually set up by BIOS.
	 */

	अगर (!pci_resource_start(pdev, AHCI_PCI_BAR) ||
	    !pci_resource_len(pdev, AHCI_PCI_BAR))
		वापस 0;

	mmio = pci_iomap(pdev, AHCI_PCI_BAR, 64);
	अगर (!mmio)
		वापस -ENOMEM;

	पंचांगp = ioपढ़ो32(mmio + AHCI_GLOBAL_CTL);
	अगर (पंचांगp & AHCI_ENABLE) अणु
		पंचांगp &= ~AHCI_ENABLE;
		ioग_लिखो32(पंचांगp, mmio + AHCI_GLOBAL_CTL);

		पंचांगp = ioपढ़ो32(mmio + AHCI_GLOBAL_CTL);
		अगर (पंचांगp & AHCI_ENABLE)
			rc = -EIO;
	पूर्ण

	pci_iounmap(pdev, mmio);
	वापस rc;
पूर्ण

/**
 *	piix_check_450nx_errata	-	Check क्रम problem 450NX setup
 *	@ata_dev: the PCI device to check
 *
 *	Check क्रम the present of 450NX errata #19 and errata #25. If
 *	they are found वापस an error code so we can turn off DMA
 */

अटल पूर्णांक piix_check_450nx_errata(काष्ठा pci_dev *ata_dev)
अणु
	काष्ठा pci_dev *pdev = शून्य;
	u16 cfg;
	पूर्णांक no_piix_dma = 0;

	जबतक ((pdev = pci_get_device(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82454NX, pdev)) != शून्य) अणु
		/* Look क्रम 450NX PXB. Check क्रम problem configurations
		   A PCI quirk checks bit 6 alपढ़ोy */
		pci_पढ़ो_config_word(pdev, 0x41, &cfg);
		/* Only on the original revision: IDE DMA can hang */
		अगर (pdev->revision == 0x00)
			no_piix_dma = 1;
		/* On all revisions below 5 PXB bus lock must be disabled क्रम IDE */
		अन्यथा अगर (cfg & (1<<14) && pdev->revision < 5)
			no_piix_dma = 2;
	पूर्ण
	अगर (no_piix_dma)
		dev_warn(&ata_dev->dev,
			 "450NX errata present, disabling IDE DMA%s\n",
			 no_piix_dma == 2 ? " - a BIOS update may resolve this"
			 : "");

	वापस no_piix_dma;
पूर्ण

अटल व्योम piix_init_pcs(काष्ठा ata_host *host,
			  स्थिर काष्ठा piix_map_db *map_db)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(host->dev);
	u16 pcs, new_pcs;

	pci_पढ़ो_config_word(pdev, ICH5_PCS, &pcs);

	new_pcs = pcs | map_db->port_enable;

	अगर (new_pcs != pcs) अणु
		DPRINTK("updating PCS from 0x%x to 0x%x\n", pcs, new_pcs);
		pci_ग_लिखो_config_word(pdev, ICH5_PCS, new_pcs);
		msleep(150);
	पूर्ण
पूर्ण

अटल स्थिर पूर्णांक *piix_init_sata_map(काष्ठा pci_dev *pdev,
				     काष्ठा ata_port_info *pinfo,
				     स्थिर काष्ठा piix_map_db *map_db)
अणु
	स्थिर पूर्णांक *map;
	पूर्णांक i, invalid_map = 0;
	u8 map_value;
	अक्षर buf[32];
	अक्षर *p = buf, *end = buf + माप(buf);

	pci_पढ़ो_config_byte(pdev, ICH5_PMR, &map_value);

	map = map_db->map[map_value & map_db->mask];

	क्रम (i = 0; i < 4; i++) अणु
		चयन (map[i]) अणु
		हाल RV:
			invalid_map = 1;
			p += scnम_लिखो(p, end - p, " XX");
			अवरोध;

		हाल NA:
			p += scnम_लिखो(p, end - p, " --");
			अवरोध;

		हाल IDE:
			WARN_ON((i & 1) || map[i + 1] != IDE);
			pinfo[i / 2] = piix_port_info[ich_pata_100];
			i++;
			p += scnम_लिखो(p, end - p, " IDE IDE");
			अवरोध;

		शेष:
			p += scnम_लिखो(p, end - p, " P%d", map[i]);
			अगर (i & 1)
				pinfo[i / 2].flags |= ATA_FLAG_SLAVE_POSS;
			अवरोध;
		पूर्ण
	पूर्ण
	dev_info(&pdev->dev, "MAP [%s ]\n", buf);

	अगर (invalid_map)
		dev_err(&pdev->dev, "invalid MAP value %u\n", map_value);

	वापस map;
पूर्ण

अटल bool piix_no_sidpr(काष्ठा ata_host *host)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(host->dev);

	/*
	 * Samsung DB-P70 only has three ATA ports exposed and
	 * curiously the unconnected first port reports link online
	 * जबतक not responding to SRST protocol causing excessive
	 * detection delay.
	 *
	 * Unक्रमtunately, the प्रणाली करोesn't carry enough DMI
	 * inक्रमmation to identअगरy the machine but करोes have subप्रणाली
	 * venकरोr and device set.  As it's unclear whether the
	 * subप्रणाली venकरोr/device is used only क्रम this specअगरic
	 * board, the port can't be disabled solely with the
	 * inक्रमmation; however, turning off SIDPR access works around
	 * the problem.  Turn it off.
	 *
	 * This problem is reported in bnc#441240.
	 *
	 * https://bugzilla.novell.com/show_bug.cgi?id=441420
	 */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL && pdev->device == 0x2920 &&
	    pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_SAMSUNG &&
	    pdev->subप्रणाली_device == 0xb049) अणु
		dev_warn(host->dev,
			 "Samsung DB-P70 detected, disabling SIDPR\n");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक piix_init_sidpr(काष्ठा ata_host *host)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(host->dev);
	काष्ठा piix_host_priv *hpriv = host->निजी_data;
	काष्ठा ata_link *link0 = &host->ports[0]->link;
	u32 scontrol;
	पूर्णांक i, rc;

	/* check क्रम availability */
	क्रम (i = 0; i < 4; i++)
		अगर (hpriv->map[i] == IDE)
			वापस 0;

	/* is it blacklisted? */
	अगर (piix_no_sidpr(host))
		वापस 0;

	अगर (!(host->ports[0]->flags & PIIX_FLAG_SIDPR))
		वापस 0;

	अगर (pci_resource_start(pdev, PIIX_SIDPR_BAR) == 0 ||
	    pci_resource_len(pdev, PIIX_SIDPR_BAR) != PIIX_SIDPR_LEN)
		वापस 0;

	अगर (pcim_iomap_regions(pdev, 1 << PIIX_SIDPR_BAR, DRV_NAME))
		वापस 0;

	hpriv->sidpr = pcim_iomap_table(pdev)[PIIX_SIDPR_BAR];

	/* SCR access via SIDPR करोesn't work on some configurations.
	 * Give it a test drive by inhibiting घातer save modes which
	 * we'll करो anyway.
	 */
	piix_sidpr_scr_पढ़ो(link0, SCR_CONTROL, &scontrol);

	/* अगर IPM is alपढ़ोy 3, SCR access is probably working.  Don't
	 * un-inhibit घातer save modes as BIOS might have inhibited
	 * them क्रम a reason.
	 */
	अगर ((scontrol & 0xf00) != 0x300) अणु
		scontrol |= 0x300;
		piix_sidpr_scr_ग_लिखो(link0, SCR_CONTROL, scontrol);
		piix_sidpr_scr_पढ़ो(link0, SCR_CONTROL, &scontrol);

		अगर ((scontrol & 0xf00) != 0x300) अणु
			dev_info(host->dev,
				 "SCR access via SIDPR is available but doesn't work\n");
			वापस 0;
		पूर्ण
	पूर्ण

	/* okay, SCRs available, set ops and ask libata क्रम slave_link */
	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		ap->ops = &piix_sidpr_sata_ops;

		अगर (ap->flags & ATA_FLAG_SLAVE_POSS) अणु
			rc = ata_slave_link_init(ap);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम piix_iocfg_bit18_quirk(काष्ठा ata_host *host)
अणु
	अटल स्थिर काष्ठा dmi_प्रणाली_id sysids[] = अणु
		अणु
			/* Clevo M570U sets IOCFG bit 18 अगर the cdrom
			 * isn't used to boot the प्रणाली which
			 * disables the channel.
			 */
			.ident = "M570U",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "Clevo Co."),
				DMI_MATCH(DMI_PRODUCT_NAME, "M570U"),
			पूर्ण,
		पूर्ण,

		अणु पूर्ण	/* terminate list */
	पूर्ण;
	काष्ठा pci_dev *pdev = to_pci_dev(host->dev);
	काष्ठा piix_host_priv *hpriv = host->निजी_data;

	अगर (!dmi_check_प्रणाली(sysids))
		वापस;

	/* The datasheet says that bit 18 is NOOP but certain प्रणालीs
	 * seem to use it to disable a channel.  Clear the bit on the
	 * affected प्रणालीs.
	 */
	अगर (hpriv->saved_iocfg & (1 << 18)) अणु
		dev_info(&pdev->dev, "applying IOCFG bit18 quirk\n");
		pci_ग_लिखो_config_dword(pdev, PIIX_IOCFG,
				       hpriv->saved_iocfg & ~(1 << 18));
	पूर्ण
पूर्ण

अटल bool piix_broken_प्रणाली_घातeroff(काष्ठा pci_dev *pdev)
अणु
	अटल स्थिर काष्ठा dmi_प्रणाली_id broken_प्रणालीs[] = अणु
		अणु
			.ident = "HP Compaq 2510p",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
				DMI_MATCH(DMI_PRODUCT_NAME, "HP Compaq 2510p"),
			पूर्ण,
			/* PCI slot number of the controller */
			.driver_data = (व्योम *)0x1FUL,
		पूर्ण,
		अणु
			.ident = "HP Compaq nc6000",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
				DMI_MATCH(DMI_PRODUCT_NAME, "HP Compaq nc6000"),
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

अटल पूर्णांक prefer_ms_hyperv = 1;
module_param(prefer_ms_hyperv, पूर्णांक, 0);
MODULE_PARM_DESC(prefer_ms_hyperv,
	"Prefer Hyper-V paravirtualization drivers instead of ATA, "
	"0 - Use ATA drivers, "
	"1 (Default) - Use the paravirtualization drivers.");

अटल व्योम piix_ignore_devices_quirk(काष्ठा ata_host *host)
अणु
#अगर IS_ENABLED(CONFIG_HYPERV_STORAGE)
	अटल स्थिर काष्ठा dmi_प्रणाली_id ignore_hyperv[] = अणु
		अणु
			/* On Hyper-V hypervisors the disks are exposed on
			 * both the emulated SATA controller and on the
			 * paraभवised drivers.  The CD/DVD devices
			 * are only exposed on the emulated controller.
			 * Request we ignore ATA devices on this host.
			 */
			.ident = "Hyper-V Virtual Machine",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR,
						"Microsoft Corporation"),
				DMI_MATCH(DMI_PRODUCT_NAME, "Virtual Machine"),
			पूर्ण,
		पूर्ण,
		अणु पूर्ण	/* terminate list */
	पूर्ण;
	अटल स्थिर काष्ठा dmi_प्रणाली_id allow_भव_pc[] = अणु
		अणु
			/* In MS Virtual PC guests the DMI ident is nearly
			 * identical to a Hyper-V guest. One dअगरference is the
			 * product version which is used here to identअगरy
			 * a Virtual PC guest. This entry allows ata_piix to
			 * drive the emulated hardware.
			 */
			.ident = "MS Virtual PC 2007",
			.matches = अणु
				DMI_MATCH(DMI_SYS_VENDOR,
						"Microsoft Corporation"),
				DMI_MATCH(DMI_PRODUCT_NAME, "Virtual Machine"),
				DMI_MATCH(DMI_PRODUCT_VERSION, "VS2005R2"),
			पूर्ण,
		पूर्ण,
		अणु पूर्ण	/* terminate list */
	पूर्ण;
	स्थिर काष्ठा dmi_प्रणाली_id *ignore = dmi_first_match(ignore_hyperv);
	स्थिर काष्ठा dmi_प्रणाली_id *allow = dmi_first_match(allow_भव_pc);

	अगर (ignore && !allow && prefer_ms_hyperv) अणु
		host->flags |= ATA_HOST_IGNORE_ATA;
		dev_info(host->dev, "%s detected, ATA device ignore set\n",
			ignore->ident);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/**
 *	piix_init_one - Register PIIX ATA PCI device with kernel services
 *	@pdev: PCI device to रेजिस्टर
 *	@ent: Entry in piix_pci_tbl matching with @pdev
 *
 *	Called from kernel PCI layer.  We probe क्रम combined mode (sigh),
 *	and then hand over control to libata, क्रम it to करो the rest.
 *
 *	LOCKING:
 *	Inherited from PCI layer (may sleep).
 *
 *	RETURNS:
 *	Zero on success, or -ERRNO value.
 */

अटल पूर्णांक piix_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ata_port_info port_info[2];
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &port_info[0], &port_info[1] पूर्ण;
	काष्ठा scsi_host_ढाँचा *sht = &piix_sht;
	अचिन्हित दीर्घ port_flags;
	काष्ठा ata_host *host;
	काष्ठा piix_host_priv *hpriv;
	पूर्णांक rc;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	/* no hotplugging support क्रम later devices (FIXME) */
	अगर (!in_module_init && ent->driver_data >= ich5_sata)
		वापस -ENODEV;

	अगर (piix_broken_प्रणाली_घातeroff(pdev)) अणु
		piix_port_info[ent->driver_data].flags |=
				ATA_FLAG_NO_POWEROFF_SPINDOWN |
					ATA_FLAG_NO_HIBERNATE_SPINDOWN;
		dev_info(&pdev->dev, "quirky BIOS, skipping spindown "
				"on poweroff and hibernation\n");
	पूर्ण

	port_info[0] = piix_port_info[ent->driver_data];
	port_info[1] = piix_port_info[ent->driver_data];

	port_flags = port_info[0].flags;

	/* enable device and prepare host */
	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	hpriv = devm_kzalloc(dev, माप(*hpriv), GFP_KERNEL);
	अगर (!hpriv)
		वापस -ENOMEM;

	/* Save IOCFG, this will be used क्रम cable detection, quirk
	 * detection and restoration on detach.  This is necessary
	 * because some ACPI implementations mess up cable related
	 * bits on _STM.  Reported on kernel bz#11879.
	 */
	pci_पढ़ो_config_dword(pdev, PIIX_IOCFG, &hpriv->saved_iocfg);

	/* ICH6R may be driven by either ata_piix or ahci driver
	 * regardless of BIOS configuration.  Make sure AHCI mode is
	 * off.
	 */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL && pdev->device == 0x2652) अणु
		rc = piix_disable_ahci(pdev);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* SATA map init can change port_info, करो it beक्रमe prepping host */
	अगर (port_flags & ATA_FLAG_SATA)
		hpriv->map = piix_init_sata_map(pdev, port_info,
					piix_map_db_table[ent->driver_data]);

	rc = ata_pci_bmdma_prepare_host(pdev, ppi, &host);
	अगर (rc)
		वापस rc;
	host->निजी_data = hpriv;

	/* initialize controller */
	अगर (port_flags & ATA_FLAG_SATA) अणु
		piix_init_pcs(host, piix_map_db_table[ent->driver_data]);
		rc = piix_init_sidpr(host);
		अगर (rc)
			वापस rc;
		अगर (host->ports[0]->ops == &piix_sidpr_sata_ops)
			sht = &piix_sidpr_sht;
	पूर्ण

	/* apply IOCFG bit18 quirk */
	piix_iocfg_bit18_quirk(host);

	/* On ICH5, some BIOSen disable the पूर्णांकerrupt using the
	 * PCI_COMMAND_INTX_DISABLE bit added in PCI 2.3.
	 * On ICH6, this bit has the same effect, but only when
	 * MSI is disabled (and it is disabled, as we करोn't use
	 * message-संकेतled पूर्णांकerrupts currently).
	 */
	अगर (port_flags & PIIX_FLAG_CHECKINTR)
		pci_पूर्णांकx(pdev, 1);

	अगर (piix_check_450nx_errata(pdev)) अणु
		/* This ग_लिखोs पूर्णांकo the master table but it करोes not
		   really matter क्रम this errata as we will apply it to
		   all the PIIX devices on the board */
		host->ports[0]->mwdma_mask = 0;
		host->ports[0]->udma_mask = 0;
		host->ports[1]->mwdma_mask = 0;
		host->ports[1]->udma_mask = 0;
	पूर्ण
	host->flags |= ATA_HOST_PARALLEL_SCAN;

	/* Allow hosts to specअगरy device types to ignore when scanning. */
	piix_ignore_devices_quirk(host);

	pci_set_master(pdev);
	वापस ata_pci_sff_activate_host(host, ata_bmdma_पूर्णांकerrupt, sht);
पूर्ण

अटल व्योम piix_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	काष्ठा piix_host_priv *hpriv = host->निजी_data;

	pci_ग_लिखो_config_dword(pdev, PIIX_IOCFG, hpriv->saved_iocfg);

	ata_pci_हटाओ_one(pdev);
पूर्ण

अटल काष्ठा pci_driver piix_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= piix_pci_tbl,
	.probe			= piix_init_one,
	.हटाओ			= piix_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= piix_pci_device_suspend,
	.resume			= piix_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init piix_init(व्योम)
अणु
	पूर्णांक rc;

	DPRINTK("pci_register_driver\n");
	rc = pci_रेजिस्टर_driver(&piix_pci_driver);
	अगर (rc)
		वापस rc;

	in_module_init = 0;

	DPRINTK("done\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास piix_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&piix_pci_driver);
पूर्ण

module_init(piix_init);
module_निकास(piix_निकास);
