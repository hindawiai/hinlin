<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* pci_psycho.c: PSYCHO/U2P specअगरic PCI controller support.
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

#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/starfire.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/upa.h>

#समावेश "pci_impl.h"
#समावेश "iommu_common.h"
#समावेश "psycho_common.h"

#घोषणा DRIVER_NAME	"psycho"
#घोषणा PFX		DRIVER_NAME ": "

/* Misc. PSYCHO PCI controller रेजिस्टर offsets and definitions. */
#घोषणा PSYCHO_CONTROL		0x0010UL
#घोषणा  PSYCHO_CONTROL_IMPL	 0xf000000000000000UL /* Implementation of this PSYCHO*/
#घोषणा  PSYCHO_CONTROL_VER	 0x0f00000000000000UL /* Version of this PSYCHO       */
#घोषणा  PSYCHO_CONTROL_MID	 0x00f8000000000000UL /* UPA Module ID of PSYCHO      */
#घोषणा  PSYCHO_CONTROL_IGN	 0x0007c00000000000UL /* Interrupt Group Number       */
#घोषणा  PSYCHO_CONTROL_RESV     0x00003ffffffffff0UL /* Reserved                     */
#घोषणा  PSYCHO_CONTROL_APCKEN	 0x0000000000000008UL /* Address Parity Check Enable  */
#घोषणा  PSYCHO_CONTROL_APERR	 0x0000000000000004UL /* Incoming System Addr Parerr  */
#घोषणा  PSYCHO_CONTROL_IAP	 0x0000000000000002UL /* Invert UPA Parity            */
#घोषणा  PSYCHO_CONTROL_MODE	 0x0000000000000001UL /* PSYCHO घड़ी mode            */
#घोषणा PSYCHO_PCIA_CTRL	0x2000UL
#घोषणा PSYCHO_PCIB_CTRL	0x4000UL
#घोषणा  PSYCHO_PCICTRL_RESV1	 0xfffffff000000000UL /* Reserved                     */
#घोषणा  PSYCHO_PCICTRL_SBH_ERR	 0x0000000800000000UL /* Streaming byte hole error    */
#घोषणा  PSYCHO_PCICTRL_SERR	 0x0000000400000000UL /* SERR संकेत निश्चितed         */
#घोषणा  PSYCHO_PCICTRL_SPEED	 0x0000000200000000UL /* PCI speed (1 is U2P घड़ी)   */
#घोषणा  PSYCHO_PCICTRL_RESV2	 0x00000001ffc00000UL /* Reserved                     */
#घोषणा  PSYCHO_PCICTRL_ARB_PARK 0x0000000000200000UL /* PCI arbitration parking      */
#घोषणा  PSYCHO_PCICTRL_RESV3	 0x00000000001ff800UL /* Reserved                     */
#घोषणा  PSYCHO_PCICTRL_SBH_INT	 0x0000000000000400UL /* Streaming byte hole पूर्णांक enab */
#घोषणा  PSYCHO_PCICTRL_WEN	 0x0000000000000200UL /* Power Mgmt Wake Enable       */
#घोषणा  PSYCHO_PCICTRL_EEN	 0x0000000000000100UL /* PCI Error Interrupt Enable   */
#घोषणा  PSYCHO_PCICTRL_RESV4	 0x00000000000000c0UL /* Reserved                     */
#घोषणा  PSYCHO_PCICTRL_AEN	 0x000000000000003fUL /* PCI DVMA Arbitration Enable  */

/* PSYCHO error handling support. */

/* Helper function of IOMMU error checking, which checks out
 * the state of the streaming buffers.  The IOMMU lock is
 * held when this is called.
 *
 * For the PCI error हाल we know which PBM (and thus which
 * streaming buffer) caused the error, but क्रम the uncorrectable
 * error हाल we करो not.  So we always check both streaming caches.
 */
#घोषणा PSYCHO_STRBUF_CONTROL_A 0x2800UL
#घोषणा PSYCHO_STRBUF_CONTROL_B 0x4800UL
#घोषणा  PSYCHO_STRBUF_CTRL_LPTR    0x00000000000000f0UL /* LRU Lock Poपूर्णांकer */
#घोषणा  PSYCHO_STRBUF_CTRL_LENAB   0x0000000000000008UL /* LRU Lock Enable */
#घोषणा  PSYCHO_STRBUF_CTRL_RRDIS   0x0000000000000004UL /* Rerun Disable */
#घोषणा  PSYCHO_STRBUF_CTRL_DENAB   0x0000000000000002UL /* Diagnostic Mode Enable */
#घोषणा  PSYCHO_STRBUF_CTRL_ENAB    0x0000000000000001UL /* Streaming Buffer Enable */
#घोषणा PSYCHO_STRBUF_FLUSH_A   0x2808UL
#घोषणा PSYCHO_STRBUF_FLUSH_B   0x4808UL
#घोषणा PSYCHO_STRBUF_FSYNC_A   0x2810UL
#घोषणा PSYCHO_STRBUF_FSYNC_B   0x4810UL
#घोषणा PSYCHO_STC_DATA_A	0xb000UL
#घोषणा PSYCHO_STC_DATA_B	0xc000UL
#घोषणा PSYCHO_STC_ERR_A	0xb400UL
#घोषणा PSYCHO_STC_ERR_B	0xc400UL
#घोषणा PSYCHO_STC_TAG_A	0xb800UL
#घोषणा PSYCHO_STC_TAG_B	0xc800UL
#घोषणा PSYCHO_STC_LINE_A	0xb900UL
#घोषणा PSYCHO_STC_LINE_B	0xc900UL

/* When an Uncorrectable Error or a PCI Error happens, we
 * पूर्णांकerrogate the IOMMU state to see अगर it is the cause.
 */
#घोषणा PSYCHO_IOMMU_CONTROL	0x0200UL
#घोषणा  PSYCHO_IOMMU_CTRL_RESV     0xfffffffff9000000UL /* Reserved                      */
#घोषणा  PSYCHO_IOMMU_CTRL_XLTESTAT 0x0000000006000000UL /* Translation Error Status      */
#घोषणा  PSYCHO_IOMMU_CTRL_XLTEERR  0x0000000001000000UL /* Translation Error encountered */
#घोषणा  PSYCHO_IOMMU_CTRL_LCKEN    0x0000000000800000UL /* Enable translation locking    */
#घोषणा  PSYCHO_IOMMU_CTRL_LCKPTR   0x0000000000780000UL /* Translation lock poपूर्णांकer      */
#घोषणा  PSYCHO_IOMMU_CTRL_TSBSZ    0x0000000000070000UL /* TSB Size                      */
#घोषणा  PSYCHO_IOMMU_TSBSZ_1K      0x0000000000000000UL /* TSB Table 1024 8-byte entries */
#घोषणा  PSYCHO_IOMMU_TSBSZ_2K      0x0000000000010000UL /* TSB Table 2048 8-byte entries */
#घोषणा  PSYCHO_IOMMU_TSBSZ_4K      0x0000000000020000UL /* TSB Table 4096 8-byte entries */
#घोषणा  PSYCHO_IOMMU_TSBSZ_8K      0x0000000000030000UL /* TSB Table 8192 8-byte entries */
#घोषणा  PSYCHO_IOMMU_TSBSZ_16K     0x0000000000040000UL /* TSB Table 16k 8-byte entries  */
#घोषणा  PSYCHO_IOMMU_TSBSZ_32K     0x0000000000050000UL /* TSB Table 32k 8-byte entries  */
#घोषणा  PSYCHO_IOMMU_TSBSZ_64K     0x0000000000060000UL /* TSB Table 64k 8-byte entries  */
#घोषणा  PSYCHO_IOMMU_TSBSZ_128K    0x0000000000070000UL /* TSB Table 128k 8-byte entries */
#घोषणा  PSYCHO_IOMMU_CTRL_RESV2    0x000000000000fff8UL /* Reserved                      */
#घोषणा  PSYCHO_IOMMU_CTRL_TBWSZ    0x0000000000000004UL /* Assumed page size, 0=8k 1=64k */
#घोषणा  PSYCHO_IOMMU_CTRL_DENAB    0x0000000000000002UL /* Diagnostic mode enable        */
#घोषणा  PSYCHO_IOMMU_CTRL_ENAB     0x0000000000000001UL /* IOMMU Enable                  */
#घोषणा PSYCHO_IOMMU_TSBBASE	0x0208UL
#घोषणा PSYCHO_IOMMU_FLUSH	0x0210UL
#घोषणा PSYCHO_IOMMU_TAG	0xa580UL
#घोषणा PSYCHO_IOMMU_DATA	0xa600UL

/* Uncorrectable Errors.  Cause of the error and the address are
 * recorded in the UE_AFSR and UE_AFAR of PSYCHO.  They are errors
 * relating to UPA पूर्णांकerface transactions.
 */
#घोषणा PSYCHO_UE_AFSR	0x0030UL
#घोषणा  PSYCHO_UEAFSR_PPIO	0x8000000000000000UL /* Primary PIO is cause         */
#घोषणा  PSYCHO_UEAFSR_PDRD	0x4000000000000000UL /* Primary DVMA पढ़ो is cause   */
#घोषणा  PSYCHO_UEAFSR_PDWR	0x2000000000000000UL /* Primary DVMA ग_लिखो is cause  */
#घोषणा  PSYCHO_UEAFSR_SPIO	0x1000000000000000UL /* Secondary PIO is cause       */
#घोषणा  PSYCHO_UEAFSR_SDRD	0x0800000000000000UL /* Secondary DVMA पढ़ो is cause */
#घोषणा  PSYCHO_UEAFSR_SDWR	0x0400000000000000UL /* Secondary DVMA ग_लिखो is cause*/
#घोषणा  PSYCHO_UEAFSR_RESV1	0x03ff000000000000UL /* Reserved                     */
#घोषणा  PSYCHO_UEAFSR_BMSK	0x0000ffff00000000UL /* Bytemask of failed transfer  */
#घोषणा  PSYCHO_UEAFSR_DOFF	0x00000000e0000000UL /* Doubleword Offset            */
#घोषणा  PSYCHO_UEAFSR_MID	0x000000001f000000UL /* UPA MID causing the fault    */
#घोषणा  PSYCHO_UEAFSR_BLK	0x0000000000800000UL /* Trans was block operation    */
#घोषणा  PSYCHO_UEAFSR_RESV2	0x00000000007fffffUL /* Reserved                     */
#घोषणा PSYCHO_UE_AFAR	0x0038UL

अटल irqवापस_t psycho_ue_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pci_pbm_info *pbm = dev_id;
	अचिन्हित दीर्घ afsr_reg = pbm->controller_regs + PSYCHO_UE_AFSR;
	अचिन्हित दीर्घ afar_reg = pbm->controller_regs + PSYCHO_UE_AFAR;
	अचिन्हित दीर्घ afsr, afar, error_bits;
	पूर्णांक reported;

	/* Latch uncorrectable error status. */
	afar = upa_पढ़ोq(afar_reg);
	afsr = upa_पढ़ोq(afsr_reg);

	/* Clear the primary/secondary error status bits. */
	error_bits = afsr &
		(PSYCHO_UEAFSR_PPIO | PSYCHO_UEAFSR_PDRD | PSYCHO_UEAFSR_PDWR |
		 PSYCHO_UEAFSR_SPIO | PSYCHO_UEAFSR_SDRD | PSYCHO_UEAFSR_SDWR);
	अगर (!error_bits)
		वापस IRQ_NONE;
	upa_ग_लिखोq(error_bits, afsr_reg);

	/* Log the error. */
	prपूर्णांकk("%s: Uncorrectable Error, primary error type[%s]\n",
	       pbm->name,
	       (((error_bits & PSYCHO_UEAFSR_PPIO) ?
		 "PIO" :
		 ((error_bits & PSYCHO_UEAFSR_PDRD) ?
		  "DMA Read" :
		  ((error_bits & PSYCHO_UEAFSR_PDWR) ?
		   "DMA Write" : "???")))));
	prपूर्णांकk("%s: bytemask[%04lx] dword_offset[%lx] UPA_MID[%02lx] was_block(%d)\n",
	       pbm->name,
	       (afsr & PSYCHO_UEAFSR_BMSK) >> 32UL,
	       (afsr & PSYCHO_UEAFSR_DOFF) >> 29UL,
	       (afsr & PSYCHO_UEAFSR_MID) >> 24UL,
	       ((afsr & PSYCHO_UEAFSR_BLK) ? 1 : 0));
	prपूर्णांकk("%s: UE AFAR [%016lx]\n", pbm->name, afar);
	prपूर्णांकk("%s: UE Secondary errors [", pbm->name);
	reported = 0;
	अगर (afsr & PSYCHO_UEAFSR_SPIO) अणु
		reported++;
		prपूर्णांकk("(PIO)");
	पूर्ण
	अगर (afsr & PSYCHO_UEAFSR_SDRD) अणु
		reported++;
		prपूर्णांकk("(DMA Read)");
	पूर्ण
	अगर (afsr & PSYCHO_UEAFSR_SDWR) अणु
		reported++;
		prपूर्णांकk("(DMA Write)");
	पूर्ण
	अगर (!reported)
		prपूर्णांकk("(none)");
	prपूर्णांकk("]\n");

	/* Interrogate both IOMMUs क्रम error status. */
	psycho_check_iommu_error(pbm, afsr, afar, UE_ERR);
	अगर (pbm->sibling)
		psycho_check_iommu_error(pbm->sibling, afsr, afar, UE_ERR);

	वापस IRQ_HANDLED;
पूर्ण

/* Correctable Errors. */
#घोषणा PSYCHO_CE_AFSR	0x0040UL
#घोषणा  PSYCHO_CEAFSR_PPIO	0x8000000000000000UL /* Primary PIO is cause         */
#घोषणा  PSYCHO_CEAFSR_PDRD	0x4000000000000000UL /* Primary DVMA पढ़ो is cause   */
#घोषणा  PSYCHO_CEAFSR_PDWR	0x2000000000000000UL /* Primary DVMA ग_लिखो is cause  */
#घोषणा  PSYCHO_CEAFSR_SPIO	0x1000000000000000UL /* Secondary PIO is cause       */
#घोषणा  PSYCHO_CEAFSR_SDRD	0x0800000000000000UL /* Secondary DVMA पढ़ो is cause */
#घोषणा  PSYCHO_CEAFSR_SDWR	0x0400000000000000UL /* Secondary DVMA ग_लिखो is cause*/
#घोषणा  PSYCHO_CEAFSR_RESV1	0x0300000000000000UL /* Reserved                     */
#घोषणा  PSYCHO_CEAFSR_ESYND	0x00ff000000000000UL /* Syndrome Bits                */
#घोषणा  PSYCHO_CEAFSR_BMSK	0x0000ffff00000000UL /* Bytemask of failed transfer  */
#घोषणा  PSYCHO_CEAFSR_DOFF	0x00000000e0000000UL /* Double Offset                */
#घोषणा  PSYCHO_CEAFSR_MID	0x000000001f000000UL /* UPA MID causing the fault    */
#घोषणा  PSYCHO_CEAFSR_BLK	0x0000000000800000UL /* Trans was block operation    */
#घोषणा  PSYCHO_CEAFSR_RESV2	0x00000000007fffffUL /* Reserved                     */
#घोषणा PSYCHO_CE_AFAR	0x0040UL

अटल irqवापस_t psycho_ce_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pci_pbm_info *pbm = dev_id;
	अचिन्हित दीर्घ afsr_reg = pbm->controller_regs + PSYCHO_CE_AFSR;
	अचिन्हित दीर्घ afar_reg = pbm->controller_regs + PSYCHO_CE_AFAR;
	अचिन्हित दीर्घ afsr, afar, error_bits;
	पूर्णांक reported;

	/* Latch error status. */
	afar = upa_पढ़ोq(afar_reg);
	afsr = upa_पढ़ोq(afsr_reg);

	/* Clear primary/secondary error status bits. */
	error_bits = afsr &
		(PSYCHO_CEAFSR_PPIO | PSYCHO_CEAFSR_PDRD | PSYCHO_CEAFSR_PDWR |
		 PSYCHO_CEAFSR_SPIO | PSYCHO_CEAFSR_SDRD | PSYCHO_CEAFSR_SDWR);
	अगर (!error_bits)
		वापस IRQ_NONE;
	upa_ग_लिखोq(error_bits, afsr_reg);

	/* Log the error. */
	prपूर्णांकk("%s: Correctable Error, primary error type[%s]\n",
	       pbm->name,
	       (((error_bits & PSYCHO_CEAFSR_PPIO) ?
		 "PIO" :
		 ((error_bits & PSYCHO_CEAFSR_PDRD) ?
		  "DMA Read" :
		  ((error_bits & PSYCHO_CEAFSR_PDWR) ?
		   "DMA Write" : "???")))));

	/* XXX Use syndrome and afar to prपूर्णांक out module string just like
	 * XXX UDB CE trap handler करोes... -DaveM
	 */
	prपूर्णांकk("%s: syndrome[%02lx] bytemask[%04lx] dword_offset[%lx] "
	       "UPA_MID[%02lx] was_block(%d)\n",
	       pbm->name,
	       (afsr & PSYCHO_CEAFSR_ESYND) >> 48UL,
	       (afsr & PSYCHO_CEAFSR_BMSK) >> 32UL,
	       (afsr & PSYCHO_CEAFSR_DOFF) >> 29UL,
	       (afsr & PSYCHO_CEAFSR_MID) >> 24UL,
	       ((afsr & PSYCHO_CEAFSR_BLK) ? 1 : 0));
	prपूर्णांकk("%s: CE AFAR [%016lx]\n", pbm->name, afar);
	prपूर्णांकk("%s: CE Secondary errors [", pbm->name);
	reported = 0;
	अगर (afsr & PSYCHO_CEAFSR_SPIO) अणु
		reported++;
		prपूर्णांकk("(PIO)");
	पूर्ण
	अगर (afsr & PSYCHO_CEAFSR_SDRD) अणु
		reported++;
		prपूर्णांकk("(DMA Read)");
	पूर्ण
	अगर (afsr & PSYCHO_CEAFSR_SDWR) अणु
		reported++;
		prपूर्णांकk("(DMA Write)");
	पूर्ण
	अगर (!reported)
		prपूर्णांकk("(none)");
	prपूर्णांकk("]\n");

	वापस IRQ_HANDLED;
पूर्ण

/* PCI Errors.  They are संकेतled by the PCI bus module since they
 * are associated with a specअगरic bus segment.
 */
#घोषणा PSYCHO_PCI_AFSR_A	0x2010UL
#घोषणा PSYCHO_PCI_AFSR_B	0x4010UL
#घोषणा PSYCHO_PCI_AFAR_A	0x2018UL
#घोषणा PSYCHO_PCI_AFAR_B	0x4018UL

/* XXX What about PowerFail/PowerManagement??? -DaveM */
#घोषणा PSYCHO_ECC_CTRL		0x0020
#घोषणा  PSYCHO_ECCCTRL_EE	 0x8000000000000000UL /* Enable ECC Checking */
#घोषणा  PSYCHO_ECCCTRL_UE	 0x4000000000000000UL /* Enable UE Interrupts */
#घोषणा  PSYCHO_ECCCTRL_CE	 0x2000000000000000UL /* Enable CE INterrupts */
अटल व्योम psycho_रेजिस्टर_error_handlers(काष्ठा pci_pbm_info *pbm)
अणु
	काष्ठा platक्रमm_device *op = of_find_device_by_node(pbm->op->dev.of_node);
	अचिन्हित दीर्घ base = pbm->controller_regs;
	u64 पंचांगp;
	पूर्णांक err;

	अगर (!op)
		वापस;

	/* Psycho पूर्णांकerrupt property order is:
	 * 0: PCIERR INO क्रम this PBM
	 * 1: UE ERR
	 * 2: CE ERR
	 * 3: POWER FAIL
	 * 4: SPARE HARDWARE
	 * 5: POWER MANAGEMENT
	 */

	अगर (op->archdata.num_irqs < 6)
		वापस;

	/* We really mean to ignore the वापस result here.  Two
	 * PCI controller share the same पूर्णांकerrupt numbers and
	 * drive the same front-end hardware.
	 */
	err = request_irq(op->archdata.irqs[1], psycho_ue_पूर्णांकr, IRQF_SHARED,
			  "PSYCHO_UE", pbm);
	err = request_irq(op->archdata.irqs[2], psycho_ce_पूर्णांकr, IRQF_SHARED,
			  "PSYCHO_CE", pbm);

	/* This one, however, ought not to fail.  We can just warn
	 * about it since the प्रणाली can still operate properly even
	 * अगर this fails.
	 */
	err = request_irq(op->archdata.irqs[0], psycho_pcierr_पूर्णांकr, IRQF_SHARED,
			  "PSYCHO_PCIERR", pbm);
	अगर (err)
		prपूर्णांकk(KERN_WARNING "%s: Could not register PCIERR, "
		       "err=%d\n", pbm->name, err);

	/* Enable UE and CE पूर्णांकerrupts क्रम controller. */
	upa_ग_लिखोq((PSYCHO_ECCCTRL_EE |
		    PSYCHO_ECCCTRL_UE |
		    PSYCHO_ECCCTRL_CE), base + PSYCHO_ECC_CTRL);

	/* Enable PCI Error पूर्णांकerrupts and clear error
	 * bits क्रम each PBM.
	 */
	पंचांगp = upa_पढ़ोq(base + PSYCHO_PCIA_CTRL);
	पंचांगp |= (PSYCHO_PCICTRL_SERR |
		PSYCHO_PCICTRL_SBH_ERR |
		PSYCHO_PCICTRL_EEN);
	पंचांगp &= ~(PSYCHO_PCICTRL_SBH_INT);
	upa_ग_लिखोq(पंचांगp, base + PSYCHO_PCIA_CTRL);
		     
	पंचांगp = upa_पढ़ोq(base + PSYCHO_PCIB_CTRL);
	पंचांगp |= (PSYCHO_PCICTRL_SERR |
		PSYCHO_PCICTRL_SBH_ERR |
		PSYCHO_PCICTRL_EEN);
	पंचांगp &= ~(PSYCHO_PCICTRL_SBH_INT);
	upa_ग_लिखोq(पंचांगp, base + PSYCHO_PCIB_CTRL);
पूर्ण

/* PSYCHO boot समय probing and initialization. */
अटल व्योम pbm_config_busmastering(काष्ठा pci_pbm_info *pbm)
अणु
	u8 *addr;

	/* Set cache-line size to 64 bytes, this is actually
	 * a nop but I करो it क्रम completeness.
	 */
	addr = psycho_pci_config_mkaddr(pbm, pbm->pci_first_busno,
					0, PCI_CACHE_LINE_SIZE);
	pci_config_ग_लिखो8(addr, 64 / माप(u32));

	/* Set PBM latency समयr to 64 PCI घड़ीs. */
	addr = psycho_pci_config_mkaddr(pbm, pbm->pci_first_busno,
					0, PCI_LATENCY_TIMER);
	pci_config_ग_लिखो8(addr, 64);
पूर्ण

अटल व्योम psycho_scan_bus(काष्ठा pci_pbm_info *pbm,
			    काष्ठा device *parent)
अणु
	pbm_config_busmastering(pbm);
	pbm->is_66mhz_capable = 0;
	pbm->pci_bus = pci_scan_one_pbm(pbm, parent);

	/* After the PCI bus scan is complete, we can रेजिस्टर
	 * the error पूर्णांकerrupt handlers.
	 */
	psycho_रेजिस्टर_error_handlers(pbm);
पूर्ण

#घोषणा PSYCHO_IRQ_RETRY	0x1a00UL
#घोषणा PSYCHO_PCIA_DIAG	0x2020UL
#घोषणा PSYCHO_PCIB_DIAG	0x4020UL
#घोषणा  PSYCHO_PCIDIAG_RESV	 0xffffffffffffff80UL /* Reserved                     */
#घोषणा  PSYCHO_PCIDIAG_DRETRY	 0x0000000000000040UL /* Disable retry limit          */
#घोषणा  PSYCHO_PCIDIAG_DISYNC	 0x0000000000000020UL /* Disable DMA wr / irq sync    */
#घोषणा  PSYCHO_PCIDIAG_DDWSYNC	 0x0000000000000010UL /* Disable DMA wr / PIO rd sync */
#घोषणा  PSYCHO_PCIDIAG_IDDPAR	 0x0000000000000008UL /* Invert DMA data parity       */
#घोषणा  PSYCHO_PCIDIAG_IPDPAR	 0x0000000000000004UL /* Invert PIO data parity       */
#घोषणा  PSYCHO_PCIDIAG_IPAPAR	 0x0000000000000002UL /* Invert PIO address parity    */
#घोषणा  PSYCHO_PCIDIAG_LPBACK	 0x0000000000000001UL /* Enable loopback mode         */

अटल व्योम psycho_controller_hwinit(काष्ठा pci_pbm_info *pbm)
अणु
	u64 पंचांगp;

	upa_ग_लिखोq(5, pbm->controller_regs + PSYCHO_IRQ_RETRY);

	/* Enable arbiter क्रम all PCI slots. */
	पंचांगp = upa_पढ़ोq(pbm->controller_regs + PSYCHO_PCIA_CTRL);
	पंचांगp |= PSYCHO_PCICTRL_AEN;
	upa_ग_लिखोq(पंचांगp, pbm->controller_regs + PSYCHO_PCIA_CTRL);

	पंचांगp = upa_पढ़ोq(pbm->controller_regs + PSYCHO_PCIB_CTRL);
	पंचांगp |= PSYCHO_PCICTRL_AEN;
	upa_ग_लिखोq(पंचांगp, pbm->controller_regs + PSYCHO_PCIB_CTRL);

	/* Disable DMA ग_लिखो / PIO पढ़ो synchronization on
	 * both PCI bus segments.
	 * [ U2P Erratum 1243770, STP2223BGA data sheet ]
	 */
	पंचांगp = upa_पढ़ोq(pbm->controller_regs + PSYCHO_PCIA_DIAG);
	पंचांगp |= PSYCHO_PCIDIAG_DDWSYNC;
	upa_ग_लिखोq(पंचांगp, pbm->controller_regs + PSYCHO_PCIA_DIAG);

	पंचांगp = upa_पढ़ोq(pbm->controller_regs + PSYCHO_PCIB_DIAG);
	पंचांगp |= PSYCHO_PCIDIAG_DDWSYNC;
	upa_ग_लिखोq(पंचांगp, pbm->controller_regs + PSYCHO_PCIB_DIAG);
पूर्ण

अटल व्योम psycho_pbm_strbuf_init(काष्ठा pci_pbm_info *pbm,
				   पूर्णांक is_pbm_a)
अणु
	अचिन्हित दीर्घ base = pbm->controller_regs;
	u64 control;

	अगर (is_pbm_a) अणु
		pbm->stc.strbuf_control  = base + PSYCHO_STRBUF_CONTROL_A;
		pbm->stc.strbuf_pflush   = base + PSYCHO_STRBUF_FLUSH_A;
		pbm->stc.strbuf_fsync    = base + PSYCHO_STRBUF_FSYNC_A;
		pbm->stc.strbuf_err_stat = base + PSYCHO_STC_ERR_A;
		pbm->stc.strbuf_tag_diag = base + PSYCHO_STC_TAG_A;
		pbm->stc.strbuf_line_diag= base + PSYCHO_STC_LINE_A;
	पूर्ण अन्यथा अणु
		pbm->stc.strbuf_control  = base + PSYCHO_STRBUF_CONTROL_B;
		pbm->stc.strbuf_pflush   = base + PSYCHO_STRBUF_FLUSH_B;
		pbm->stc.strbuf_fsync    = base + PSYCHO_STRBUF_FSYNC_B;
		pbm->stc.strbuf_err_stat = base + PSYCHO_STC_ERR_B;
		pbm->stc.strbuf_tag_diag = base + PSYCHO_STC_TAG_B;
		pbm->stc.strbuf_line_diag= base + PSYCHO_STC_LINE_B;
	पूर्ण
	/* PSYCHO's streaming buffer lacks ctx flushing. */
	pbm->stc.strbuf_ctxflush      = 0;
	pbm->stc.strbuf_ctxmatch_base = 0;

	pbm->stc.strbuf_flushflag = (अस्थिर अचिन्हित दीर्घ *)
		((((अचिन्हित दीर्घ)&pbm->stc.__flushflag_buf[0])
		  + 63UL)
		 & ~63UL);
	pbm->stc.strbuf_flushflag_pa = (अचिन्हित दीर्घ)
		__pa(pbm->stc.strbuf_flushflag);

	/* Enable the streaming buffer.  We have to be careful
	 * just in हाल OBP left it with LRU locking enabled.
	 *
	 * It is possible to control अगर PBM will be rerun on
	 * line misses.  Currently I just retain whatever setting
	 * OBP left us with.  All checks so far show it having
	 * a value of zero.
	 */
#अघोषित PSYCHO_STRBUF_RERUN_ENABLE
#अघोषित PSYCHO_STRBUF_RERUN_DISABLE
	control = upa_पढ़ोq(pbm->stc.strbuf_control);
	control |= PSYCHO_STRBUF_CTRL_ENAB;
	control &= ~(PSYCHO_STRBUF_CTRL_LENAB | PSYCHO_STRBUF_CTRL_LPTR);
#अगर_घोषित PSYCHO_STRBUF_RERUN_ENABLE
	control &= ~(PSYCHO_STRBUF_CTRL_RRDIS);
#अन्यथा
#अगर_घोषित PSYCHO_STRBUF_RERUN_DISABLE
	control |= PSYCHO_STRBUF_CTRL_RRDIS;
#पूर्ण_अगर
#पूर्ण_अगर
	upa_ग_लिखोq(control, pbm->stc.strbuf_control);

	pbm->stc.strbuf_enabled = 1;
पूर्ण

#घोषणा PSYCHO_IOSPACE_A	0x002000000UL
#घोषणा PSYCHO_IOSPACE_B	0x002010000UL
#घोषणा PSYCHO_IOSPACE_SIZE	0x00000ffffUL
#घोषणा PSYCHO_MEMSPACE_A	0x100000000UL
#घोषणा PSYCHO_MEMSPACE_B	0x180000000UL
#घोषणा PSYCHO_MEMSPACE_SIZE	0x07fffffffUL

अटल व्योम psycho_pbm_init(काष्ठा pci_pbm_info *pbm,
			    काष्ठा platक्रमm_device *op, पूर्णांक is_pbm_a)
अणु
	psycho_pbm_init_common(pbm, op, "PSYCHO", PBM_CHIP_TYPE_PSYCHO);
	psycho_pbm_strbuf_init(pbm, is_pbm_a);
	psycho_scan_bus(pbm, &op->dev);
पूर्ण

अटल काष्ठा pci_pbm_info *psycho_find_sibling(u32 upa_portid)
अणु
	काष्ठा pci_pbm_info *pbm;

	क्रम (pbm = pci_pbm_root; pbm; pbm = pbm->next) अणु
		अगर (pbm->portid == upa_portid)
			वापस pbm;
	पूर्ण
	वापस शून्य;
पूर्ण

#घोषणा PSYCHO_CONFIGSPACE	0x001000000UL

अटल पूर्णांक psycho_probe(काष्ठा platक्रमm_device *op)
अणु
	स्थिर काष्ठा linux_prom64_रेजिस्टरs *pr_regs;
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा pci_pbm_info *pbm;
	काष्ठा iommu *iommu;
	पूर्णांक is_pbm_a, err;
	u32 upa_portid;

	upa_portid = of_getपूर्णांकprop_शेष(dp, "upa-portid", 0xff);

	err = -ENOMEM;
	pbm = kzalloc(माप(*pbm), GFP_KERNEL);
	अगर (!pbm) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot allocate pci_pbm_info.\n");
		जाओ out_err;
	पूर्ण

	pbm->sibling = psycho_find_sibling(upa_portid);
	अगर (pbm->sibling) अणु
		iommu = pbm->sibling->iommu;
	पूर्ण अन्यथा अणु
		iommu = kzalloc(माप(काष्ठा iommu), GFP_KERNEL);
		अगर (!iommu) अणु
			prपूर्णांकk(KERN_ERR PFX "Cannot allocate PBM iommu.\n");
			जाओ out_मुक्त_controller;
		पूर्ण
	पूर्ण

	pbm->iommu = iommu;
	pbm->portid = upa_portid;

	pr_regs = of_get_property(dp, "reg", शून्य);
	err = -ENODEV;
	अगर (!pr_regs) अणु
		prपूर्णांकk(KERN_ERR PFX "No reg property.\n");
		जाओ out_मुक्त_iommu;
	पूर्ण

	is_pbm_a = ((pr_regs[0].phys_addr & 0x6000) == 0x2000);

	pbm->controller_regs = pr_regs[2].phys_addr;
	pbm->config_space = (pr_regs[2].phys_addr + PSYCHO_CONFIGSPACE);

	अगर (is_pbm_a) अणु
		pbm->pci_afsr = pbm->controller_regs + PSYCHO_PCI_AFSR_A;
		pbm->pci_afar = pbm->controller_regs + PSYCHO_PCI_AFAR_A;
		pbm->pci_csr  = pbm->controller_regs + PSYCHO_PCIA_CTRL;
	पूर्ण अन्यथा अणु
		pbm->pci_afsr = pbm->controller_regs + PSYCHO_PCI_AFSR_B;
		pbm->pci_afar = pbm->controller_regs + PSYCHO_PCI_AFAR_B;
		pbm->pci_csr  = pbm->controller_regs + PSYCHO_PCIB_CTRL;
	पूर्ण

	psycho_controller_hwinit(pbm);
	अगर (!pbm->sibling) अणु
		err = psycho_iommu_init(pbm, 128, 0xc0000000,
					0xffffffff, PSYCHO_CONTROL);
		अगर (err)
			जाओ out_मुक्त_iommu;

		/* If necessary, hook us up क्रम starfire IRQ translations. */
		अगर (this_is_starfire)
			starfire_hookup(pbm->portid);
	पूर्ण

	psycho_pbm_init(pbm, op, is_pbm_a);

	pbm->next = pci_pbm_root;
	pci_pbm_root = pbm;

	अगर (pbm->sibling)
		pbm->sibling->sibling = pbm;

	dev_set_drvdata(&op->dev, pbm);

	वापस 0;

out_मुक्त_iommu:
	अगर (!pbm->sibling)
		kमुक्त(pbm->iommu);

out_मुक्त_controller:
	kमुक्त(pbm);

out_err:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id psycho_match[] = अणु
	अणु
		.name = "pci",
		.compatible = "pci108e,8000",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver psycho_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = psycho_match,
	पूर्ण,
	.probe		= psycho_probe,
पूर्ण;

अटल पूर्णांक __init psycho_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&psycho_driver);
पूर्ण

subsys_initcall(psycho_init);
