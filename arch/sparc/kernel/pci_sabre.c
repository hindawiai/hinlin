<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* pci_sabre.c: Sabre specअगरic PCI controller support.
 *
 * Copyright (C) 1997, 1998, 1999, 2007 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1998, 1999 Eddie C. Dost   (ecd@skynet.be)
 * Copyright (C) 1999 Jakub Jelinek   (jakub@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/apb.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/upa.h>

#समावेश "pci_impl.h"
#समावेश "iommu_common.h"
#समावेश "psycho_common.h"

#घोषणा DRIVER_NAME	"sabre"
#घोषणा PFX		DRIVER_NAME ": "

/* SABRE PCI controller रेजिस्टर offsets and definitions. */
#घोषणा SABRE_UE_AFSR		0x0030UL
#घोषणा  SABRE_UEAFSR_PDRD	 0x4000000000000000UL	/* Primary PCI DMA Read */
#घोषणा  SABRE_UEAFSR_PDWR	 0x2000000000000000UL	/* Primary PCI DMA Write */
#घोषणा  SABRE_UEAFSR_SDRD	 0x0800000000000000UL	/* Secondary PCI DMA Read */
#घोषणा  SABRE_UEAFSR_SDWR	 0x0400000000000000UL	/* Secondary PCI DMA Write */
#घोषणा  SABRE_UEAFSR_SDTE	 0x0200000000000000UL	/* Secondary DMA Translation Error */
#घोषणा  SABRE_UEAFSR_PDTE	 0x0100000000000000UL	/* Primary DMA Translation Error */
#घोषणा  SABRE_UEAFSR_BMSK	 0x0000ffff00000000UL	/* Bytemask */
#घोषणा  SABRE_UEAFSR_OFF	 0x00000000e0000000UL	/* Offset (AFAR bits [5:3] */
#घोषणा  SABRE_UEAFSR_BLK	 0x0000000000800000UL	/* Was block operation */
#घोषणा SABRE_UECE_AFAR		0x0038UL
#घोषणा SABRE_CE_AFSR		0x0040UL
#घोषणा  SABRE_CEAFSR_PDRD	 0x4000000000000000UL	/* Primary PCI DMA Read */
#घोषणा  SABRE_CEAFSR_PDWR	 0x2000000000000000UL	/* Primary PCI DMA Write */
#घोषणा  SABRE_CEAFSR_SDRD	 0x0800000000000000UL	/* Secondary PCI DMA Read */
#घोषणा  SABRE_CEAFSR_SDWR	 0x0400000000000000UL	/* Secondary PCI DMA Write */
#घोषणा  SABRE_CEAFSR_ESYND	 0x00ff000000000000UL	/* ECC Syndrome */
#घोषणा  SABRE_CEAFSR_BMSK	 0x0000ffff00000000UL	/* Bytemask */
#घोषणा  SABRE_CEAFSR_OFF	 0x00000000e0000000UL	/* Offset */
#घोषणा  SABRE_CEAFSR_BLK	 0x0000000000800000UL	/* Was block operation */
#घोषणा SABRE_UECE_AFAR_ALIAS	0x0048UL	/* Aliases to 0x0038 */
#घोषणा SABRE_IOMMU_CONTROL	0x0200UL
#घोषणा  SABRE_IOMMUCTRL_ERRSTS	 0x0000000006000000UL	/* Error status bits */
#घोषणा  SABRE_IOMMUCTRL_ERR	 0x0000000001000000UL	/* Error present in IOTLB */
#घोषणा  SABRE_IOMMUCTRL_LCKEN	 0x0000000000800000UL	/* IOTLB lock enable */
#घोषणा  SABRE_IOMMUCTRL_LCKPTR	 0x0000000000780000UL	/* IOTLB lock poपूर्णांकer */
#घोषणा  SABRE_IOMMUCTRL_TSBSZ	 0x0000000000070000UL	/* TSB Size */
#घोषणा  SABRE_IOMMU_TSBSZ_1K   0x0000000000000000
#घोषणा  SABRE_IOMMU_TSBSZ_2K   0x0000000000010000
#घोषणा  SABRE_IOMMU_TSBSZ_4K   0x0000000000020000
#घोषणा  SABRE_IOMMU_TSBSZ_8K   0x0000000000030000
#घोषणा  SABRE_IOMMU_TSBSZ_16K  0x0000000000040000
#घोषणा  SABRE_IOMMU_TSBSZ_32K  0x0000000000050000
#घोषणा  SABRE_IOMMU_TSBSZ_64K  0x0000000000060000
#घोषणा  SABRE_IOMMU_TSBSZ_128K 0x0000000000070000
#घोषणा  SABRE_IOMMUCTRL_TBWSZ	 0x0000000000000004UL	/* TSB assumed page size */
#घोषणा  SABRE_IOMMUCTRL_DENAB	 0x0000000000000002UL	/* Diagnostic Mode Enable */
#घोषणा  SABRE_IOMMUCTRL_ENAB	 0x0000000000000001UL	/* IOMMU Enable */
#घोषणा SABRE_IOMMU_TSBBASE	0x0208UL
#घोषणा SABRE_IOMMU_FLUSH	0x0210UL
#घोषणा SABRE_IMAP_A_SLOT0	0x0c00UL
#घोषणा SABRE_IMAP_B_SLOT0	0x0c20UL
#घोषणा SABRE_IMAP_SCSI		0x1000UL
#घोषणा SABRE_IMAP_ETH		0x1008UL
#घोषणा SABRE_IMAP_BPP		0x1010UL
#घोषणा SABRE_IMAP_AU_REC	0x1018UL
#घोषणा SABRE_IMAP_AU_PLAY	0x1020UL
#घोषणा SABRE_IMAP_PFAIL	0x1028UL
#घोषणा SABRE_IMAP_KMS		0x1030UL
#घोषणा SABRE_IMAP_FLPY		0x1038UL
#घोषणा SABRE_IMAP_SHW		0x1040UL
#घोषणा SABRE_IMAP_KBD		0x1048UL
#घोषणा SABRE_IMAP_MS		0x1050UL
#घोषणा SABRE_IMAP_SER		0x1058UL
#घोषणा SABRE_IMAP_UE		0x1070UL
#घोषणा SABRE_IMAP_CE		0x1078UL
#घोषणा SABRE_IMAP_PCIERR	0x1080UL
#घोषणा SABRE_IMAP_GFX		0x1098UL
#घोषणा SABRE_IMAP_EUPA		0x10a0UL
#घोषणा SABRE_ICLR_A_SLOT0	0x1400UL
#घोषणा SABRE_ICLR_B_SLOT0	0x1480UL
#घोषणा SABRE_ICLR_SCSI		0x1800UL
#घोषणा SABRE_ICLR_ETH		0x1808UL
#घोषणा SABRE_ICLR_BPP		0x1810UL
#घोषणा SABRE_ICLR_AU_REC	0x1818UL
#घोषणा SABRE_ICLR_AU_PLAY	0x1820UL
#घोषणा SABRE_ICLR_PFAIL	0x1828UL
#घोषणा SABRE_ICLR_KMS		0x1830UL
#घोषणा SABRE_ICLR_FLPY		0x1838UL
#घोषणा SABRE_ICLR_SHW		0x1840UL
#घोषणा SABRE_ICLR_KBD		0x1848UL
#घोषणा SABRE_ICLR_MS		0x1850UL
#घोषणा SABRE_ICLR_SER		0x1858UL
#घोषणा SABRE_ICLR_UE		0x1870UL
#घोषणा SABRE_ICLR_CE		0x1878UL
#घोषणा SABRE_ICLR_PCIERR	0x1880UL
#घोषणा SABRE_WRSYNC		0x1c20UL
#घोषणा SABRE_PCICTRL		0x2000UL
#घोषणा  SABRE_PCICTRL_MRLEN	 0x0000001000000000UL	/* Use MemoryReadLine क्रम block loads/stores */
#घोषणा  SABRE_PCICTRL_SERR	 0x0000000400000000UL	/* Set when SERR निश्चितed on PCI bus */
#घोषणा  SABRE_PCICTRL_ARBPARK	 0x0000000000200000UL	/* Bus Parking 0=Ultra-IIi 1=prev-bus-owner */
#घोषणा  SABRE_PCICTRL_CPUPRIO	 0x0000000000100000UL	/* Ultra-IIi granted every other bus cycle */
#घोषणा  SABRE_PCICTRL_ARBPRIO	 0x00000000000f0000UL	/* Slot which is granted every other bus cycle */
#घोषणा  SABRE_PCICTRL_ERREN	 0x0000000000000100UL	/* PCI Error Interrupt Enable */
#घोषणा  SABRE_PCICTRL_RTRYWE	 0x0000000000000080UL	/* DMA Flow Control 0=रुको-अगर-possible 1=retry */
#घोषणा  SABRE_PCICTRL_AEN	 0x000000000000000fUL	/* Slot PCI arbitration enables */
#घोषणा SABRE_PIOAFSR		0x2010UL
#घोषणा  SABRE_PIOAFSR_PMA	 0x8000000000000000UL	/* Primary Master Abort */
#घोषणा  SABRE_PIOAFSR_PTA	 0x4000000000000000UL	/* Primary Target Abort */
#घोषणा  SABRE_PIOAFSR_PRTRY	 0x2000000000000000UL	/* Primary Excessive Retries */
#घोषणा  SABRE_PIOAFSR_PPERR	 0x1000000000000000UL	/* Primary Parity Error */
#घोषणा  SABRE_PIOAFSR_SMA	 0x0800000000000000UL	/* Secondary Master Abort */
#घोषणा  SABRE_PIOAFSR_STA	 0x0400000000000000UL	/* Secondary Target Abort */
#घोषणा  SABRE_PIOAFSR_SRTRY	 0x0200000000000000UL	/* Secondary Excessive Retries */
#घोषणा  SABRE_PIOAFSR_SPERR	 0x0100000000000000UL	/* Secondary Parity Error */
#घोषणा  SABRE_PIOAFSR_BMSK	 0x0000ffff00000000UL	/* Byte Mask */
#घोषणा  SABRE_PIOAFSR_BLK	 0x0000000080000000UL	/* Was Block Operation */
#घोषणा SABRE_PIOAFAR		0x2018UL
#घोषणा SABRE_PCIDIAG		0x2020UL
#घोषणा  SABRE_PCIDIAG_DRTRY	 0x0000000000000040UL	/* Disable PIO Retry Limit */
#घोषणा  SABRE_PCIDIAG_IPAPAR	 0x0000000000000008UL	/* Invert PIO Address Parity */
#घोषणा  SABRE_PCIDIAG_IPDPAR	 0x0000000000000004UL	/* Invert PIO Data Parity */
#घोषणा  SABRE_PCIDIAG_IDDPAR	 0x0000000000000002UL	/* Invert DMA Data Parity */
#घोषणा  SABRE_PCIDIAG_ELPBK	 0x0000000000000001UL	/* Loopback Enable - not supported */
#घोषणा SABRE_PCITASR		0x2028UL
#घोषणा  SABRE_PCITASR_EF	 0x0000000000000080UL	/* Respond to 0xe0000000-0xffffffff */
#घोषणा  SABRE_PCITASR_CD	 0x0000000000000040UL	/* Respond to 0xc0000000-0xdfffffff */
#घोषणा  SABRE_PCITASR_AB	 0x0000000000000020UL	/* Respond to 0xa0000000-0xbfffffff */
#घोषणा  SABRE_PCITASR_89	 0x0000000000000010UL	/* Respond to 0x80000000-0x9fffffff */
#घोषणा  SABRE_PCITASR_67	 0x0000000000000008UL	/* Respond to 0x60000000-0x7fffffff */
#घोषणा  SABRE_PCITASR_45	 0x0000000000000004UL	/* Respond to 0x40000000-0x5fffffff */
#घोषणा  SABRE_PCITASR_23	 0x0000000000000002UL	/* Respond to 0x20000000-0x3fffffff */
#घोषणा  SABRE_PCITASR_01	 0x0000000000000001UL	/* Respond to 0x00000000-0x1fffffff */
#घोषणा SABRE_PIOBUF_DIAG	0x5000UL
#घोषणा SABRE_DMABUF_DIAGLO	0x5100UL
#घोषणा SABRE_DMABUF_DIAGHI	0x51c0UL
#घोषणा SABRE_IMAP_GFX_ALIAS	0x6000UL	/* Aliases to 0x1098 */
#घोषणा SABRE_IMAP_EUPA_ALIAS	0x8000UL	/* Aliases to 0x10a0 */
#घोषणा SABRE_IOMMU_VADIAG	0xa400UL
#घोषणा SABRE_IOMMU_TCDIAG	0xa408UL
#घोषणा SABRE_IOMMU_TAG		0xa580UL
#घोषणा  SABRE_IOMMUTAG_ERRSTS	 0x0000000001800000UL	/* Error status bits */
#घोषणा  SABRE_IOMMUTAG_ERR	 0x0000000000400000UL	/* Error present */
#घोषणा  SABRE_IOMMUTAG_WRITE	 0x0000000000200000UL	/* Page is writable */
#घोषणा  SABRE_IOMMUTAG_STREAM	 0x0000000000100000UL	/* Streamable bit - unused */
#घोषणा  SABRE_IOMMUTAG_SIZE	 0x0000000000080000UL	/* 0=8k 1=16k */
#घोषणा  SABRE_IOMMUTAG_VPN	 0x000000000007ffffUL	/* Virtual Page Number [31:13] */
#घोषणा SABRE_IOMMU_DATA	0xa600UL
#घोषणा SABRE_IOMMUDATA_VALID	 0x0000000040000000UL	/* Valid */
#घोषणा SABRE_IOMMUDATA_USED	 0x0000000020000000UL	/* Used (क्रम LRU algorithm) */
#घोषणा SABRE_IOMMUDATA_CACHE	 0x0000000010000000UL	/* Cacheable */
#घोषणा SABRE_IOMMUDATA_PPN	 0x00000000001fffffUL	/* Physical Page Number [33:13] */
#घोषणा SABRE_PCI_IRQSTATE	0xa800UL
#घोषणा SABRE_OBIO_IRQSTATE	0xa808UL
#घोषणा SABRE_FFBCFG		0xf000UL
#घोषणा  SABRE_FFBCFG_SPRQS	 0x000000000f000000	/* Slave P_RQST queue size */
#घोषणा  SABRE_FFBCFG_ONEREAD	 0x0000000000004000	/* Slave supports one outstanding पढ़ो */
#घोषणा SABRE_MCCTRL0		0xf010UL
#घोषणा  SABRE_MCCTRL0_RENAB	 0x0000000080000000	/* Refresh Enable */
#घोषणा  SABRE_MCCTRL0_EENAB	 0x0000000010000000	/* Enable all ECC functions */
#घोषणा  SABRE_MCCTRL0_11BIT	 0x0000000000001000	/* Enable 11-bit column addressing */
#घोषणा  SABRE_MCCTRL0_DPP	 0x0000000000000f00	/* DIMM Pair Present Bits */
#घोषणा  SABRE_MCCTRL0_RINTVL	 0x00000000000000ff	/* Refresh Interval */
#घोषणा SABRE_MCCTRL1		0xf018UL
#घोषणा  SABRE_MCCTRL1_AMDC	 0x0000000038000000	/* Advance Memdata Clock */
#घोषणा  SABRE_MCCTRL1_ARDC	 0x0000000007000000	/* Advance DRAM Read Data Clock */
#घोषणा  SABRE_MCCTRL1_CSR	 0x0000000000e00000	/* CAS to RAS delay क्रम CBR refresh */
#घोषणा  SABRE_MCCTRL1_CASRW	 0x00000000001c0000	/* CAS length क्रम पढ़ो/ग_लिखो */
#घोषणा  SABRE_MCCTRL1_RCD	 0x0000000000038000	/* RAS to CAS delay */
#घोषणा  SABRE_MCCTRL1_CP	 0x0000000000007000	/* CAS Preअक्षरge */
#घोषणा  SABRE_MCCTRL1_RP	 0x0000000000000e00	/* RAS Preअक्षरge */
#घोषणा  SABRE_MCCTRL1_RAS	 0x00000000000001c0	/* Length of RAS क्रम refresh */
#घोषणा  SABRE_MCCTRL1_CASRW2	 0x0000000000000038	/* Must be same as CASRW */
#घोषणा  SABRE_MCCTRL1_RSC	 0x0000000000000007	/* RAS after CAS hold समय */
#घोषणा SABRE_RESETCTRL		0xf020UL

#घोषणा SABRE_CONFIGSPACE	0x001000000UL
#घोषणा SABRE_IOSPACE		0x002000000UL
#घोषणा SABRE_IOSPACE_SIZE	0x000ffffffUL
#घोषणा SABRE_MEMSPACE		0x100000000UL
#घोषणा SABRE_MEMSPACE_SIZE	0x07fffffffUL

अटल पूर्णांक hummingbird_p;
अटल काष्ठा pci_bus *sabre_root_bus;

अटल irqवापस_t sabre_ue_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pci_pbm_info *pbm = dev_id;
	अचिन्हित दीर्घ afsr_reg = pbm->controller_regs + SABRE_UE_AFSR;
	अचिन्हित दीर्घ afar_reg = pbm->controller_regs + SABRE_UECE_AFAR;
	अचिन्हित दीर्घ afsr, afar, error_bits;
	पूर्णांक reported;

	/* Latch uncorrectable error status. */
	afar = upa_पढ़ोq(afar_reg);
	afsr = upa_पढ़ोq(afsr_reg);

	/* Clear the primary/secondary error status bits. */
	error_bits = afsr &
		(SABRE_UEAFSR_PDRD | SABRE_UEAFSR_PDWR |
		 SABRE_UEAFSR_SDRD | SABRE_UEAFSR_SDWR |
		 SABRE_UEAFSR_SDTE | SABRE_UEAFSR_PDTE);
	अगर (!error_bits)
		वापस IRQ_NONE;
	upa_ग_लिखोq(error_bits, afsr_reg);

	/* Log the error. */
	prपूर्णांकk("%s: Uncorrectable Error, primary error type[%s%s]\n",
	       pbm->name,
	       ((error_bits & SABRE_UEAFSR_PDRD) ?
		"DMA Read" :
		((error_bits & SABRE_UEAFSR_PDWR) ?
		 "DMA Write" : "???")),
	       ((error_bits & SABRE_UEAFSR_PDTE) ?
		":Translation Error" : ""));
	prपूर्णांकk("%s: bytemask[%04lx] dword_offset[%lx] was_block(%d)\n",
	       pbm->name,
	       (afsr & SABRE_UEAFSR_BMSK) >> 32UL,
	       (afsr & SABRE_UEAFSR_OFF) >> 29UL,
	       ((afsr & SABRE_UEAFSR_BLK) ? 1 : 0));
	prपूर्णांकk("%s: UE AFAR [%016lx]\n", pbm->name, afar);
	prपूर्णांकk("%s: UE Secondary errors [", pbm->name);
	reported = 0;
	अगर (afsr & SABRE_UEAFSR_SDRD) अणु
		reported++;
		prपूर्णांकk("(DMA Read)");
	पूर्ण
	अगर (afsr & SABRE_UEAFSR_SDWR) अणु
		reported++;
		prपूर्णांकk("(DMA Write)");
	पूर्ण
	अगर (afsr & SABRE_UEAFSR_SDTE) अणु
		reported++;
		prपूर्णांकk("(Translation Error)");
	पूर्ण
	अगर (!reported)
		prपूर्णांकk("(none)");
	prपूर्णांकk("]\n");

	/* Interrogate IOMMU क्रम error status. */
	psycho_check_iommu_error(pbm, afsr, afar, UE_ERR);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sabre_ce_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pci_pbm_info *pbm = dev_id;
	अचिन्हित दीर्घ afsr_reg = pbm->controller_regs + SABRE_CE_AFSR;
	अचिन्हित दीर्घ afar_reg = pbm->controller_regs + SABRE_UECE_AFAR;
	अचिन्हित दीर्घ afsr, afar, error_bits;
	पूर्णांक reported;

	/* Latch error status. */
	afar = upa_पढ़ोq(afar_reg);
	afsr = upa_पढ़ोq(afsr_reg);

	/* Clear primary/secondary error status bits. */
	error_bits = afsr &
		(SABRE_CEAFSR_PDRD | SABRE_CEAFSR_PDWR |
		 SABRE_CEAFSR_SDRD | SABRE_CEAFSR_SDWR);
	अगर (!error_bits)
		वापस IRQ_NONE;
	upa_ग_लिखोq(error_bits, afsr_reg);

	/* Log the error. */
	prपूर्णांकk("%s: Correctable Error, primary error type[%s]\n",
	       pbm->name,
	       ((error_bits & SABRE_CEAFSR_PDRD) ?
		"DMA Read" :
		((error_bits & SABRE_CEAFSR_PDWR) ?
		 "DMA Write" : "???")));

	/* XXX Use syndrome and afar to prपूर्णांक out module string just like
	 * XXX UDB CE trap handler करोes... -DaveM
	 */
	prपूर्णांकk("%s: syndrome[%02lx] bytemask[%04lx] dword_offset[%lx] "
	       "was_block(%d)\n",
	       pbm->name,
	       (afsr & SABRE_CEAFSR_ESYND) >> 48UL,
	       (afsr & SABRE_CEAFSR_BMSK) >> 32UL,
	       (afsr & SABRE_CEAFSR_OFF) >> 29UL,
	       ((afsr & SABRE_CEAFSR_BLK) ? 1 : 0));
	prपूर्णांकk("%s: CE AFAR [%016lx]\n", pbm->name, afar);
	prपूर्णांकk("%s: CE Secondary errors [", pbm->name);
	reported = 0;
	अगर (afsr & SABRE_CEAFSR_SDRD) अणु
		reported++;
		prपूर्णांकk("(DMA Read)");
	पूर्ण
	अगर (afsr & SABRE_CEAFSR_SDWR) अणु
		reported++;
		prपूर्णांकk("(DMA Write)");
	पूर्ण
	अगर (!reported)
		prपूर्णांकk("(none)");
	prपूर्णांकk("]\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sabre_रेजिस्टर_error_handlers(काष्ठा pci_pbm_info *pbm)
अणु
	काष्ठा device_node *dp = pbm->op->dev.of_node;
	काष्ठा platक्रमm_device *op;
	अचिन्हित दीर्घ base = pbm->controller_regs;
	u64 पंचांगp;
	पूर्णांक err;

	अगर (pbm->chip_type == PBM_CHIP_TYPE_SABRE)
		dp = dp->parent;

	op = of_find_device_by_node(dp);
	अगर (!op)
		वापस;

	/* Sabre/Hummingbird IRQ property layout is:
	 * 0: PCI ERR
	 * 1: UE ERR
	 * 2: CE ERR
	 * 3: POWER FAIL
	 */
	अगर (op->archdata.num_irqs < 4)
		वापस;

	/* We clear the error bits in the appropriate AFSR beक्रमe
	 * रेजिस्टरing the handler so that we करोn't get spurious
	 * पूर्णांकerrupts.
	 */
	upa_ग_लिखोq((SABRE_UEAFSR_PDRD | SABRE_UEAFSR_PDWR |
		    SABRE_UEAFSR_SDRD | SABRE_UEAFSR_SDWR |
		    SABRE_UEAFSR_SDTE | SABRE_UEAFSR_PDTE),
		   base + SABRE_UE_AFSR);

	err = request_irq(op->archdata.irqs[1], sabre_ue_पूर्णांकr, 0, "SABRE_UE", pbm);
	अगर (err)
		prपूर्णांकk(KERN_WARNING "%s: Couldn't register UE, err=%d.\n",
		       pbm->name, err);

	upa_ग_लिखोq((SABRE_CEAFSR_PDRD | SABRE_CEAFSR_PDWR |
		    SABRE_CEAFSR_SDRD | SABRE_CEAFSR_SDWR),
		   base + SABRE_CE_AFSR);


	err = request_irq(op->archdata.irqs[2], sabre_ce_पूर्णांकr, 0, "SABRE_CE", pbm);
	अगर (err)
		prपूर्णांकk(KERN_WARNING "%s: Couldn't register CE, err=%d.\n",
		       pbm->name, err);
	err = request_irq(op->archdata.irqs[0], psycho_pcierr_पूर्णांकr, 0,
			  "SABRE_PCIERR", pbm);
	अगर (err)
		prपूर्णांकk(KERN_WARNING "%s: Couldn't register PCIERR, err=%d.\n",
		       pbm->name, err);

	पंचांगp = upa_पढ़ोq(base + SABRE_PCICTRL);
	पंचांगp |= SABRE_PCICTRL_ERREN;
	upa_ग_लिखोq(पंचांगp, base + SABRE_PCICTRL);
पूर्ण

अटल व्योम apb_init(काष्ठा pci_bus *sabre_bus)
अणु
	काष्ठा pci_dev *pdev;

	list_क्रम_each_entry(pdev, &sabre_bus->devices, bus_list) अणु
		अगर (pdev->venकरोr == PCI_VENDOR_ID_SUN &&
		    pdev->device == PCI_DEVICE_ID_SUN_SIMBA) अणु
			u16 word16;

			pci_पढ़ो_config_word(pdev, PCI_COMMAND, &word16);
			word16 |= PCI_COMMAND_SERR | PCI_COMMAND_PARITY |
				PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY |
				PCI_COMMAND_IO;
			pci_ग_लिखो_config_word(pdev, PCI_COMMAND, word16);

			/* Status रेजिस्टर bits are "write 1 to clear". */
			pci_ग_लिखो_config_word(pdev, PCI_STATUS, 0xffff);
			pci_ग_लिखो_config_word(pdev, PCI_SEC_STATUS, 0xffff);

			/* Use a primary/seconday latency समयr value
			 * of 64.
			 */
			pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 64);
			pci_ग_लिखो_config_byte(pdev, PCI_SEC_LATENCY_TIMER, 64);

			/* Enable reporting/क्रमwarding of master पातs,
			 * parity, and SERR.
			 */
			pci_ग_लिखो_config_byte(pdev, PCI_BRIDGE_CONTROL,
					      (PCI_BRIDGE_CTL_PARITY |
					       PCI_BRIDGE_CTL_SERR |
					       PCI_BRIDGE_CTL_MASTER_ABORT));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sabre_scan_bus(काष्ठा pci_pbm_info *pbm, काष्ठा device *parent)
अणु
	अटल पूर्णांक once;

	/* The APB bridge speaks to the Sabre host PCI bridge
	 * at 66Mhz, but the front side of APB runs at 33Mhz
	 * क्रम both segments.
	 *
	 * Hummingbird प्रणालीs करो not use APB, so they run
	 * at 66MHZ.
	 */
	अगर (hummingbird_p)
		pbm->is_66mhz_capable = 1;
	अन्यथा
		pbm->is_66mhz_capable = 0;

	/* This driver has not been verअगरied to handle
	 * multiple SABREs yet, so trap this.
	 *
	 * Also note that the SABRE host bridge is hardwired
	 * to live at bus 0.
	 */
	अगर (once != 0) अणु
		prपूर्णांकk(KERN_ERR PFX "Multiple controllers unsupported.\n");
		वापस;
	पूर्ण
	once++;

	pbm->pci_bus = pci_scan_one_pbm(pbm, parent);
	अगर (!pbm->pci_bus)
		वापस;

	sabre_root_bus = pbm->pci_bus;

	apb_init(pbm->pci_bus);

	sabre_रेजिस्टर_error_handlers(pbm);
पूर्ण

अटल व्योम sabre_pbm_init(काष्ठा pci_pbm_info *pbm,
			   काष्ठा platक्रमm_device *op)
अणु
	psycho_pbm_init_common(pbm, op, "SABRE", PBM_CHIP_TYPE_SABRE);
	pbm->pci_afsr = pbm->controller_regs + SABRE_PIOAFSR;
	pbm->pci_afar = pbm->controller_regs + SABRE_PIOAFAR;
	pbm->pci_csr = pbm->controller_regs + SABRE_PCICTRL;
	sabre_scan_bus(pbm, &op->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id sabre_match[];
अटल पूर्णांक sabre_probe(काष्ठा platक्रमm_device *op)
अणु
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा linux_prom64_रेजिस्टरs *pr_regs;
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा pci_pbm_info *pbm;
	u32 upa_portid, dma_mask;
	काष्ठा iommu *iommu;
	पूर्णांक tsbsize, err;
	स्थिर u32 *vdma;
	u64 clear_irq;

	match = of_match_device(sabre_match, &op->dev);
	hummingbird_p = match && (match->data != शून्य);
	अगर (!hummingbird_p) अणु
		काष्ठा device_node *cpu_dp;

		/* Of course, Sun has to encode things a thousand
		 * dअगरferent ways, inconsistently.
		 */
		क्रम_each_node_by_type(cpu_dp, "cpu") अणु
			अगर (of_node_name_eq(cpu_dp, "SUNW,UltraSPARC-IIe"))
				hummingbird_p = 1;
		पूर्ण
	पूर्ण

	err = -ENOMEM;
	pbm = kzalloc(माप(*pbm), GFP_KERNEL);
	अगर (!pbm) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot allocate pci_pbm_info.\n");
		जाओ out_err;
	पूर्ण

	iommu = kzalloc(माप(*iommu), GFP_KERNEL);
	अगर (!iommu) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot allocate PBM iommu.\n");
		जाओ out_मुक्त_controller;
	पूर्ण

	pbm->iommu = iommu;

	upa_portid = of_getपूर्णांकprop_शेष(dp, "upa-portid", 0xff);

	pbm->portid = upa_portid;

	/*
	 * Map in SABRE रेजिस्टर set and report the presence of this SABRE.
	 */
	
	pr_regs = of_get_property(dp, "reg", शून्य);
	err = -ENODEV;
	अगर (!pr_regs) अणु
		prपूर्णांकk(KERN_ERR PFX "No reg property\n");
		जाओ out_मुक्त_iommu;
	पूर्ण

	/*
	 * First REG in property is base of entire SABRE रेजिस्टर space.
	 */
	pbm->controller_regs = pr_regs[0].phys_addr;

	/* Clear पूर्णांकerrupts */

	/* PCI first */
	क्रम (clear_irq = SABRE_ICLR_A_SLOT0; clear_irq < SABRE_ICLR_B_SLOT0 + 0x80; clear_irq += 8)
		upa_ग_लिखोq(0x0UL, pbm->controller_regs + clear_irq);

	/* Then OBIO */
	क्रम (clear_irq = SABRE_ICLR_SCSI; clear_irq < SABRE_ICLR_SCSI + 0x80; clear_irq += 8)
		upa_ग_लिखोq(0x0UL, pbm->controller_regs + clear_irq);

	/* Error पूर्णांकerrupts are enabled later after the bus scan. */
	upa_ग_लिखोq((SABRE_PCICTRL_MRLEN   | SABRE_PCICTRL_SERR |
		    SABRE_PCICTRL_ARBPARK | SABRE_PCICTRL_AEN),
		   pbm->controller_regs + SABRE_PCICTRL);

	/* Now map in PCI config space क्रम entire SABRE. */
	pbm->config_space = pbm->controller_regs + SABRE_CONFIGSPACE;

	vdma = of_get_property(dp, "virtual-dma", शून्य);
	अगर (!vdma) अणु
		prपूर्णांकk(KERN_ERR PFX "No virtual-dma property\n");
		जाओ out_मुक्त_iommu;
	पूर्ण

	dma_mask = vdma[0];
	चयन(vdma[1]) अणु
		हाल 0x20000000:
			dma_mask |= 0x1fffffff;
			tsbsize = 64;
			अवरोध;
		हाल 0x40000000:
			dma_mask |= 0x3fffffff;
			tsbsize = 128;
			अवरोध;

		हाल 0x80000000:
			dma_mask |= 0x7fffffff;
			tsbsize = 128;
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_ERR PFX "Strange virtual-dma size.\n");
			जाओ out_मुक्त_iommu;
	पूर्ण

	err = psycho_iommu_init(pbm, tsbsize, vdma[0], dma_mask, SABRE_WRSYNC);
	अगर (err)
		जाओ out_मुक्त_iommu;

	/*
	 * Look क्रम APB underneath.
	 */
	sabre_pbm_init(pbm, op);

	pbm->next = pci_pbm_root;
	pci_pbm_root = pbm;

	dev_set_drvdata(&op->dev, pbm);

	वापस 0;

out_मुक्त_iommu:
	kमुक्त(pbm->iommu);

out_मुक्त_controller:
	kमुक्त(pbm);

out_err:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id sabre_match[] = अणु
	अणु
		.name = "pci",
		.compatible = "pci108e,a001",
		.data = (व्योम *) 1,
	पूर्ण,
	अणु
		.name = "pci",
		.compatible = "pci108e,a000",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver sabre_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = sabre_match,
	पूर्ण,
	.probe		= sabre_probe,
पूर्ण;

अटल पूर्णांक __init sabre_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sabre_driver);
पूर्ण

subsys_initcall(sabre_init);
