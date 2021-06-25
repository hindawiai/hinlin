<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sbus.c: UltraSparc SBUS controller support.
 *
 * Copyright (C) 1999 David S. Miller (davem@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/numa.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/upa.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/starfire.h>

#समावेश "iommu_common.h"

#घोषणा MAP_BASE	((u32)0xc0000000)

/* Offsets from iommu_regs */
#घोषणा SYSIO_IOMMUREG_BASE	0x2400UL
#घोषणा IOMMU_CONTROL	(0x2400UL - 0x2400UL)	/* IOMMU control रेजिस्टर */
#घोषणा IOMMU_TSBBASE	(0x2408UL - 0x2400UL)	/* TSB base address रेजिस्टर */
#घोषणा IOMMU_FLUSH	(0x2410UL - 0x2400UL)	/* IOMMU flush रेजिस्टर */
#घोषणा IOMMU_VADIAG	(0x4400UL - 0x2400UL)	/* SBUS भव address diagnostic */
#घोषणा IOMMU_TAGCMP	(0x4408UL - 0x2400UL)	/* TLB tag compare diagnostics */
#घोषणा IOMMU_LRUDIAG	(0x4500UL - 0x2400UL)	/* IOMMU LRU queue diagnostics */
#घोषणा IOMMU_TAGDIAG	(0x4580UL - 0x2400UL)	/* TLB tag diagnostics */
#घोषणा IOMMU_DRAMDIAG	(0x4600UL - 0x2400UL)	/* TLB data RAM diagnostics */

#घोषणा IOMMU_DRAM_VALID	(1UL << 30UL)

/* Offsets from strbuf_regs */
#घोषणा SYSIO_STRBUFREG_BASE	0x2800UL
#घोषणा STRBUF_CONTROL	(0x2800UL - 0x2800UL)	/* Control */
#घोषणा STRBUF_PFLUSH	(0x2808UL - 0x2800UL)	/* Page flush/invalidate */
#घोषणा STRBUF_FSYNC	(0x2810UL - 0x2800UL)	/* Flush synchronization */
#घोषणा STRBUF_DRAMDIAG	(0x5000UL - 0x2800UL)	/* data RAM diagnostic */
#घोषणा STRBUF_ERRDIAG	(0x5400UL - 0x2800UL)	/* error status diagnostics */
#घोषणा STRBUF_PTAGDIAG	(0x5800UL - 0x2800UL)	/* Page tag diagnostics */
#घोषणा STRBUF_LTAGDIAG	(0x5900UL - 0x2800UL)	/* Line tag diagnostics */

#घोषणा STRBUF_TAG_VALID	0x02UL

/* Enable 64-bit DVMA mode क्रम the given device. */
व्योम sbus_set_sbus64(काष्ठा device *dev, पूर्णांक bursts)
अणु
	काष्ठा iommu *iommu = dev->archdata.iommu;
	काष्ठा platक्रमm_device *op = to_platक्रमm_device(dev);
	स्थिर काष्ठा linux_prom_रेजिस्टरs *regs;
	अचिन्हित दीर्घ cfg_reg;
	पूर्णांक slot;
	u64 val;

	regs = of_get_property(op->dev.of_node, "reg", शून्य);
	अगर (!regs) अणु
		prपूर्णांकk(KERN_ERR "sbus_set_sbus64: Cannot find regs for %pOF\n",
		       op->dev.of_node);
		वापस;
	पूर्ण
	slot = regs->which_io;

	cfg_reg = iommu->ग_लिखो_complete_reg;
	चयन (slot) अणु
	हाल 0:
		cfg_reg += 0x20UL;
		अवरोध;
	हाल 1:
		cfg_reg += 0x28UL;
		अवरोध;
	हाल 2:
		cfg_reg += 0x30UL;
		अवरोध;
	हाल 3:
		cfg_reg += 0x38UL;
		अवरोध;
	हाल 13:
		cfg_reg += 0x40UL;
		अवरोध;
	हाल 14:
		cfg_reg += 0x48UL;
		अवरोध;
	हाल 15:
		cfg_reg += 0x50UL;
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	val = upa_पढ़ोq(cfg_reg);
	अगर (val & (1UL << 14UL)) अणु
		/* Extended transfer mode alपढ़ोy enabled. */
		वापस;
	पूर्ण

	val |= (1UL << 14UL);

	अगर (bursts & DMA_BURST8)
		val |= (1UL << 1UL);
	अगर (bursts & DMA_BURST16)
		val |= (1UL << 2UL);
	अगर (bursts & DMA_BURST32)
		val |= (1UL << 3UL);
	अगर (bursts & DMA_BURST64)
		val |= (1UL << 4UL);
	upa_ग_लिखोq(val, cfg_reg);
पूर्ण
EXPORT_SYMBOL(sbus_set_sbus64);

/* INO number to IMAP रेजिस्टर offset क्रम SYSIO बाह्यal IRQ's.
 * This should conक्रमm to both Sunfire/Wildfire server and Fusion
 * desktop designs.
 */
#घोषणा SYSIO_IMAP_SLOT0	0x2c00UL
#घोषणा SYSIO_IMAP_SLOT1	0x2c08UL
#घोषणा SYSIO_IMAP_SLOT2	0x2c10UL
#घोषणा SYSIO_IMAP_SLOT3	0x2c18UL
#घोषणा SYSIO_IMAP_SCSI		0x3000UL
#घोषणा SYSIO_IMAP_ETH		0x3008UL
#घोषणा SYSIO_IMAP_BPP		0x3010UL
#घोषणा SYSIO_IMAP_AUDIO	0x3018UL
#घोषणा SYSIO_IMAP_PFAIL	0x3020UL
#घोषणा SYSIO_IMAP_KMS		0x3028UL
#घोषणा SYSIO_IMAP_FLPY		0x3030UL
#घोषणा SYSIO_IMAP_SHW		0x3038UL
#घोषणा SYSIO_IMAP_KBD		0x3040UL
#घोषणा SYSIO_IMAP_MS		0x3048UL
#घोषणा SYSIO_IMAP_SER		0x3050UL
#घोषणा SYSIO_IMAP_TIM0		0x3060UL
#घोषणा SYSIO_IMAP_TIM1		0x3068UL
#घोषणा SYSIO_IMAP_UE		0x3070UL
#घोषणा SYSIO_IMAP_CE		0x3078UL
#घोषणा SYSIO_IMAP_SBERR	0x3080UL
#घोषणा SYSIO_IMAP_PMGMT	0x3088UL
#घोषणा SYSIO_IMAP_GFX		0x3090UL
#घोषणा SYSIO_IMAP_EUPA		0x3098UL

#घोषणा bogon     ((अचिन्हित दीर्घ) -1)
अटल अचिन्हित दीर्घ sysio_irq_offsets[] = अणु
	/* SBUS Slot 0 --> 3, level 1 --> 7 */
	SYSIO_IMAP_SLOT0, SYSIO_IMAP_SLOT0, SYSIO_IMAP_SLOT0, SYSIO_IMAP_SLOT0,
	SYSIO_IMAP_SLOT0, SYSIO_IMAP_SLOT0, SYSIO_IMAP_SLOT0, SYSIO_IMAP_SLOT0,
	SYSIO_IMAP_SLOT1, SYSIO_IMAP_SLOT1, SYSIO_IMAP_SLOT1, SYSIO_IMAP_SLOT1,
	SYSIO_IMAP_SLOT1, SYSIO_IMAP_SLOT1, SYSIO_IMAP_SLOT1, SYSIO_IMAP_SLOT1,
	SYSIO_IMAP_SLOT2, SYSIO_IMAP_SLOT2, SYSIO_IMAP_SLOT2, SYSIO_IMAP_SLOT2,
	SYSIO_IMAP_SLOT2, SYSIO_IMAP_SLOT2, SYSIO_IMAP_SLOT2, SYSIO_IMAP_SLOT2,
	SYSIO_IMAP_SLOT3, SYSIO_IMAP_SLOT3, SYSIO_IMAP_SLOT3, SYSIO_IMAP_SLOT3,
	SYSIO_IMAP_SLOT3, SYSIO_IMAP_SLOT3, SYSIO_IMAP_SLOT3, SYSIO_IMAP_SLOT3,

	/* Onboard devices (not relevant/used on SunFire). */
	SYSIO_IMAP_SCSI,
	SYSIO_IMAP_ETH,
	SYSIO_IMAP_BPP,
	bogon,
	SYSIO_IMAP_AUDIO,
	SYSIO_IMAP_PFAIL,
	bogon,
	bogon,
	SYSIO_IMAP_KMS,
	SYSIO_IMAP_FLPY,
	SYSIO_IMAP_SHW,
	SYSIO_IMAP_KBD,
	SYSIO_IMAP_MS,
	SYSIO_IMAP_SER,
	bogon,
	bogon,
	SYSIO_IMAP_TIM0,
	SYSIO_IMAP_TIM1,
	bogon,
	bogon,
	SYSIO_IMAP_UE,
	SYSIO_IMAP_CE,
	SYSIO_IMAP_SBERR,
	SYSIO_IMAP_PMGMT,
पूर्ण;

#अघोषित bogon

#घोषणा NUM_SYSIO_OFFSETS ARRAY_SIZE(sysio_irq_offsets)

/* Convert Interrupt Mapping रेजिस्टर poपूर्णांकer to associated
 * Interrupt Clear रेजिस्टर poपूर्णांकer, SYSIO specअगरic version.
 */
#घोषणा SYSIO_ICLR_UNUSED0	0x3400UL
#घोषणा SYSIO_ICLR_SLOT0	0x3408UL
#घोषणा SYSIO_ICLR_SLOT1	0x3448UL
#घोषणा SYSIO_ICLR_SLOT2	0x3488UL
#घोषणा SYSIO_ICLR_SLOT3	0x34c8UL
अटल अचिन्हित दीर्घ sysio_imap_to_iclr(अचिन्हित दीर्घ imap)
अणु
	अचिन्हित दीर्घ dअगरf = SYSIO_ICLR_UNUSED0 - SYSIO_IMAP_SLOT0;
	वापस imap + dअगरf;
पूर्ण

अटल अचिन्हित पूर्णांक sbus_build_irq(काष्ठा platक्रमm_device *op, अचिन्हित पूर्णांक ino)
अणु
	काष्ठा iommu *iommu = op->dev.archdata.iommu;
	अचिन्हित दीर्घ reg_base = iommu->ग_लिखो_complete_reg - 0x2000UL;
	अचिन्हित दीर्घ imap, iclr;
	पूर्णांक sbus_level = 0;

	imap = sysio_irq_offsets[ino];
	अगर (imap == ((अचिन्हित दीर्घ)-1)) अणु
		prom_म_लिखो("get_irq_translations: Bad SYSIO INO[%x]\n",
			    ino);
		prom_halt();
	पूर्ण
	imap += reg_base;

	/* SYSIO inconsistency.  For बाह्यal SLOTS, we have to select
	 * the right ICLR रेजिस्टर based upon the lower SBUS irq level
	 * bits.
	 */
	अगर (ino >= 0x20) अणु
		iclr = sysio_imap_to_iclr(imap);
	पूर्ण अन्यथा अणु
		पूर्णांक sbus_slot = (ino & 0x18)>>3;
		
		sbus_level = ino & 0x7;

		चयन(sbus_slot) अणु
		हाल 0:
			iclr = reg_base + SYSIO_ICLR_SLOT0;
			अवरोध;
		हाल 1:
			iclr = reg_base + SYSIO_ICLR_SLOT1;
			अवरोध;
		हाल 2:
			iclr = reg_base + SYSIO_ICLR_SLOT2;
			अवरोध;
		शेष:
		हाल 3:
			iclr = reg_base + SYSIO_ICLR_SLOT3;
			अवरोध;
		पूर्ण

		iclr += ((अचिन्हित दीर्घ)sbus_level - 1UL) * 8UL;
	पूर्ण
	वापस build_irq(sbus_level, iclr, imap);
पूर्ण

/* Error पूर्णांकerrupt handling. */
#घोषणा SYSIO_UE_AFSR	0x0030UL
#घोषणा SYSIO_UE_AFAR	0x0038UL
#घोषणा  SYSIO_UEAFSR_PPIO  0x8000000000000000UL /* Primary PIO cause         */
#घोषणा  SYSIO_UEAFSR_PDRD  0x4000000000000000UL /* Primary DVMA पढ़ो cause   */
#घोषणा  SYSIO_UEAFSR_PDWR  0x2000000000000000UL /* Primary DVMA ग_लिखो cause  */
#घोषणा  SYSIO_UEAFSR_SPIO  0x1000000000000000UL /* Secondary PIO is cause    */
#घोषणा  SYSIO_UEAFSR_SDRD  0x0800000000000000UL /* Secondary DVMA पढ़ो cause */
#घोषणा  SYSIO_UEAFSR_SDWR  0x0400000000000000UL /* Secondary DVMA ग_लिखो cause*/
#घोषणा  SYSIO_UEAFSR_RESV1 0x03ff000000000000UL /* Reserved                  */
#घोषणा  SYSIO_UEAFSR_DOFF  0x0000e00000000000UL /* Doubleword Offset         */
#घोषणा  SYSIO_UEAFSR_SIZE  0x00001c0000000000UL /* Bad transfer size 2^SIZE  */
#घोषणा  SYSIO_UEAFSR_MID   0x000003e000000000UL /* UPA MID causing the fault */
#घोषणा  SYSIO_UEAFSR_RESV2 0x0000001fffffffffUL /* Reserved                  */
अटल irqवापस_t sysio_ue_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा platक्रमm_device *op = dev_id;
	काष्ठा iommu *iommu = op->dev.archdata.iommu;
	अचिन्हित दीर्घ reg_base = iommu->ग_लिखो_complete_reg - 0x2000UL;
	अचिन्हित दीर्घ afsr_reg, afar_reg;
	अचिन्हित दीर्घ afsr, afar, error_bits;
	पूर्णांक reported, portid;

	afsr_reg = reg_base + SYSIO_UE_AFSR;
	afar_reg = reg_base + SYSIO_UE_AFAR;

	/* Latch error status. */
	afsr = upa_पढ़ोq(afsr_reg);
	afar = upa_पढ़ोq(afar_reg);

	/* Clear primary/secondary error status bits. */
	error_bits = afsr &
		(SYSIO_UEAFSR_PPIO | SYSIO_UEAFSR_PDRD | SYSIO_UEAFSR_PDWR |
		 SYSIO_UEAFSR_SPIO | SYSIO_UEAFSR_SDRD | SYSIO_UEAFSR_SDWR);
	upa_ग_लिखोq(error_bits, afsr_reg);

	portid = of_getपूर्णांकprop_शेष(op->dev.of_node, "portid", -1);

	/* Log the error. */
	prपूर्णांकk("SYSIO[%x]: Uncorrectable ECC Error, primary error type[%s]\n",
	       portid,
	       (((error_bits & SYSIO_UEAFSR_PPIO) ?
		 "PIO" :
		 ((error_bits & SYSIO_UEAFSR_PDRD) ?
		  "DVMA Read" :
		  ((error_bits & SYSIO_UEAFSR_PDWR) ?
		   "DVMA Write" : "???")))));
	prपूर्णांकk("SYSIO[%x]: DOFF[%lx] SIZE[%lx] MID[%lx]\n",
	       portid,
	       (afsr & SYSIO_UEAFSR_DOFF) >> 45UL,
	       (afsr & SYSIO_UEAFSR_SIZE) >> 42UL,
	       (afsr & SYSIO_UEAFSR_MID) >> 37UL);
	prपूर्णांकk("SYSIO[%x]: AFAR[%016lx]\n", portid, afar);
	prपूर्णांकk("SYSIO[%x]: Secondary UE errors [", portid);
	reported = 0;
	अगर (afsr & SYSIO_UEAFSR_SPIO) अणु
		reported++;
		prपूर्णांकk("(PIO)");
	पूर्ण
	अगर (afsr & SYSIO_UEAFSR_SDRD) अणु
		reported++;
		prपूर्णांकk("(DVMA Read)");
	पूर्ण
	अगर (afsr & SYSIO_UEAFSR_SDWR) अणु
		reported++;
		prपूर्णांकk("(DVMA Write)");
	पूर्ण
	अगर (!reported)
		prपूर्णांकk("(none)");
	prपूर्णांकk("]\n");

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा SYSIO_CE_AFSR	0x0040UL
#घोषणा SYSIO_CE_AFAR	0x0048UL
#घोषणा  SYSIO_CEAFSR_PPIO  0x8000000000000000UL /* Primary PIO cause         */
#घोषणा  SYSIO_CEAFSR_PDRD  0x4000000000000000UL /* Primary DVMA पढ़ो cause   */
#घोषणा  SYSIO_CEAFSR_PDWR  0x2000000000000000UL /* Primary DVMA ग_लिखो cause  */
#घोषणा  SYSIO_CEAFSR_SPIO  0x1000000000000000UL /* Secondary PIO cause       */
#घोषणा  SYSIO_CEAFSR_SDRD  0x0800000000000000UL /* Secondary DVMA पढ़ो cause */
#घोषणा  SYSIO_CEAFSR_SDWR  0x0400000000000000UL /* Secondary DVMA ग_लिखो cause*/
#घोषणा  SYSIO_CEAFSR_RESV1 0x0300000000000000UL /* Reserved                  */
#घोषणा  SYSIO_CEAFSR_ESYND 0x00ff000000000000UL /* Syndrome Bits             */
#घोषणा  SYSIO_CEAFSR_DOFF  0x0000e00000000000UL /* Double Offset             */
#घोषणा  SYSIO_CEAFSR_SIZE  0x00001c0000000000UL /* Bad transfer size 2^SIZE  */
#घोषणा  SYSIO_CEAFSR_MID   0x000003e000000000UL /* UPA MID causing the fault */
#घोषणा  SYSIO_CEAFSR_RESV2 0x0000001fffffffffUL /* Reserved                  */
अटल irqवापस_t sysio_ce_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा platक्रमm_device *op = dev_id;
	काष्ठा iommu *iommu = op->dev.archdata.iommu;
	अचिन्हित दीर्घ reg_base = iommu->ग_लिखो_complete_reg - 0x2000UL;
	अचिन्हित दीर्घ afsr_reg, afar_reg;
	अचिन्हित दीर्घ afsr, afar, error_bits;
	पूर्णांक reported, portid;

	afsr_reg = reg_base + SYSIO_CE_AFSR;
	afar_reg = reg_base + SYSIO_CE_AFAR;

	/* Latch error status. */
	afsr = upa_पढ़ोq(afsr_reg);
	afar = upa_पढ़ोq(afar_reg);

	/* Clear primary/secondary error status bits. */
	error_bits = afsr &
		(SYSIO_CEAFSR_PPIO | SYSIO_CEAFSR_PDRD | SYSIO_CEAFSR_PDWR |
		 SYSIO_CEAFSR_SPIO | SYSIO_CEAFSR_SDRD | SYSIO_CEAFSR_SDWR);
	upa_ग_लिखोq(error_bits, afsr_reg);

	portid = of_getपूर्णांकprop_शेष(op->dev.of_node, "portid", -1);

	prपूर्णांकk("SYSIO[%x]: Correctable ECC Error, primary error type[%s]\n",
	       portid,
	       (((error_bits & SYSIO_CEAFSR_PPIO) ?
		 "PIO" :
		 ((error_bits & SYSIO_CEAFSR_PDRD) ?
		  "DVMA Read" :
		  ((error_bits & SYSIO_CEAFSR_PDWR) ?
		   "DVMA Write" : "???")))));

	/* XXX Use syndrome and afar to prपूर्णांक out module string just like
	 * XXX UDB CE trap handler करोes... -DaveM
	 */
	prपूर्णांकk("SYSIO[%x]: DOFF[%lx] ECC Syndrome[%lx] Size[%lx] MID[%lx]\n",
	       portid,
	       (afsr & SYSIO_CEAFSR_DOFF) >> 45UL,
	       (afsr & SYSIO_CEAFSR_ESYND) >> 48UL,
	       (afsr & SYSIO_CEAFSR_SIZE) >> 42UL,
	       (afsr & SYSIO_CEAFSR_MID) >> 37UL);
	prपूर्णांकk("SYSIO[%x]: AFAR[%016lx]\n", portid, afar);

	prपूर्णांकk("SYSIO[%x]: Secondary CE errors [", portid);
	reported = 0;
	अगर (afsr & SYSIO_CEAFSR_SPIO) अणु
		reported++;
		prपूर्णांकk("(PIO)");
	पूर्ण
	अगर (afsr & SYSIO_CEAFSR_SDRD) अणु
		reported++;
		prपूर्णांकk("(DVMA Read)");
	पूर्ण
	अगर (afsr & SYSIO_CEAFSR_SDWR) अणु
		reported++;
		prपूर्णांकk("(DVMA Write)");
	पूर्ण
	अगर (!reported)
		prपूर्णांकk("(none)");
	prपूर्णांकk("]\n");

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा SYSIO_SBUS_AFSR		0x2010UL
#घोषणा SYSIO_SBUS_AFAR		0x2018UL
#घोषणा  SYSIO_SBAFSR_PLE   0x8000000000000000UL /* Primary Late PIO Error    */
#घोषणा  SYSIO_SBAFSR_PTO   0x4000000000000000UL /* Primary SBUS Timeout      */
#घोषणा  SYSIO_SBAFSR_PBERR 0x2000000000000000UL /* Primary SBUS Error ACK    */
#घोषणा  SYSIO_SBAFSR_SLE   0x1000000000000000UL /* Secondary Late PIO Error  */
#घोषणा  SYSIO_SBAFSR_STO   0x0800000000000000UL /* Secondary SBUS Timeout    */
#घोषणा  SYSIO_SBAFSR_SBERR 0x0400000000000000UL /* Secondary SBUS Error ACK  */
#घोषणा  SYSIO_SBAFSR_RESV1 0x03ff000000000000UL /* Reserved                  */
#घोषणा  SYSIO_SBAFSR_RD    0x0000800000000000UL /* Primary was late PIO पढ़ो */
#घोषणा  SYSIO_SBAFSR_RESV2 0x0000600000000000UL /* Reserved                  */
#घोषणा  SYSIO_SBAFSR_SIZE  0x00001c0000000000UL /* Size of transfer          */
#घोषणा  SYSIO_SBAFSR_MID   0x000003e000000000UL /* MID causing the error     */
#घोषणा  SYSIO_SBAFSR_RESV3 0x0000001fffffffffUL /* Reserved                  */
अटल irqवापस_t sysio_sbus_error_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा platक्रमm_device *op = dev_id;
	काष्ठा iommu *iommu = op->dev.archdata.iommu;
	अचिन्हित दीर्घ afsr_reg, afar_reg, reg_base;
	अचिन्हित दीर्घ afsr, afar, error_bits;
	पूर्णांक reported, portid;

	reg_base = iommu->ग_लिखो_complete_reg - 0x2000UL;
	afsr_reg = reg_base + SYSIO_SBUS_AFSR;
	afar_reg = reg_base + SYSIO_SBUS_AFAR;

	afsr = upa_पढ़ोq(afsr_reg);
	afar = upa_पढ़ोq(afar_reg);

	/* Clear primary/secondary error status bits. */
	error_bits = afsr &
		(SYSIO_SBAFSR_PLE | SYSIO_SBAFSR_PTO | SYSIO_SBAFSR_PBERR |
		 SYSIO_SBAFSR_SLE | SYSIO_SBAFSR_STO | SYSIO_SBAFSR_SBERR);
	upa_ग_लिखोq(error_bits, afsr_reg);

	portid = of_getपूर्णांकprop_शेष(op->dev.of_node, "portid", -1);

	/* Log the error. */
	prपूर्णांकk("SYSIO[%x]: SBUS Error, primary error type[%s] read(%d)\n",
	       portid,
	       (((error_bits & SYSIO_SBAFSR_PLE) ?
		 "Late PIO Error" :
		 ((error_bits & SYSIO_SBAFSR_PTO) ?
		  "Time Out" :
		  ((error_bits & SYSIO_SBAFSR_PBERR) ?
		   "Error Ack" : "???")))),
	       (afsr & SYSIO_SBAFSR_RD) ? 1 : 0);
	prपूर्णांकk("SYSIO[%x]: size[%lx] MID[%lx]\n",
	       portid,
	       (afsr & SYSIO_SBAFSR_SIZE) >> 42UL,
	       (afsr & SYSIO_SBAFSR_MID) >> 37UL);
	prपूर्णांकk("SYSIO[%x]: AFAR[%016lx]\n", portid, afar);
	prपूर्णांकk("SYSIO[%x]: Secondary SBUS errors [", portid);
	reported = 0;
	अगर (afsr & SYSIO_SBAFSR_SLE) अणु
		reported++;
		prपूर्णांकk("(Late PIO Error)");
	पूर्ण
	अगर (afsr & SYSIO_SBAFSR_STO) अणु
		reported++;
		prपूर्णांकk("(Time Out)");
	पूर्ण
	अगर (afsr & SYSIO_SBAFSR_SBERR) अणु
		reported++;
		prपूर्णांकk("(Error Ack)");
	पूर्ण
	अगर (!reported)
		prपूर्णांकk("(none)");
	prपूर्णांकk("]\n");

	/* XXX check iommu/strbuf क्रम further error status XXX */

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा ECC_CONTROL	0x0020UL
#घोषणा  SYSIO_ECNTRL_ECCEN	0x8000000000000000UL /* Enable ECC Checking   */
#घोषणा  SYSIO_ECNTRL_UEEN	0x4000000000000000UL /* Enable UE Interrupts  */
#घोषणा  SYSIO_ECNTRL_CEEN	0x2000000000000000UL /* Enable CE Interrupts  */

#घोषणा SYSIO_UE_INO		0x34
#घोषणा SYSIO_CE_INO		0x35
#घोषणा SYSIO_SBUSERR_INO	0x36

अटल व्योम __init sysio_रेजिस्टर_error_handlers(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा iommu *iommu = op->dev.archdata.iommu;
	अचिन्हित दीर्घ reg_base = iommu->ग_लिखो_complete_reg - 0x2000UL;
	अचिन्हित पूर्णांक irq;
	u64 control;
	पूर्णांक portid;

	portid = of_getपूर्णांकprop_शेष(op->dev.of_node, "portid", -1);

	irq = sbus_build_irq(op, SYSIO_UE_INO);
	अगर (request_irq(irq, sysio_ue_handler, 0,
			"SYSIO_UE", op) < 0) अणु
		prom_म_लिखो("SYSIO[%x]: Cannot register UE interrupt.\n",
			    portid);
		prom_halt();
	पूर्ण

	irq = sbus_build_irq(op, SYSIO_CE_INO);
	अगर (request_irq(irq, sysio_ce_handler, 0,
			"SYSIO_CE", op) < 0) अणु
		prom_म_लिखो("SYSIO[%x]: Cannot register CE interrupt.\n",
			    portid);
		prom_halt();
	पूर्ण

	irq = sbus_build_irq(op, SYSIO_SBUSERR_INO);
	अगर (request_irq(irq, sysio_sbus_error_handler, 0,
			"SYSIO_SBERR", op) < 0) अणु
		prom_म_लिखो("SYSIO[%x]: Cannot register SBUS Error interrupt.\n",
			    portid);
		prom_halt();
	पूर्ण

	/* Now turn the error पूर्णांकerrupts on and also enable ECC checking. */
	upa_ग_लिखोq((SYSIO_ECNTRL_ECCEN |
		    SYSIO_ECNTRL_UEEN  |
		    SYSIO_ECNTRL_CEEN),
		   reg_base + ECC_CONTROL);

	control = upa_पढ़ोq(iommu->ग_लिखो_complete_reg);
	control |= 0x100UL; /* SBUS Error Interrupt Enable */
	upa_ग_लिखोq(control, iommu->ग_लिखो_complete_reg);
पूर्ण

/* Boot समय initialization. */
अटल व्योम __init sbus_iommu_init(काष्ठा platक्रमm_device *op)
अणु
	स्थिर काष्ठा linux_prom64_रेजिस्टरs *pr;
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा iommu *iommu;
	काष्ठा strbuf *strbuf;
	अचिन्हित दीर्घ regs, reg_base;
	पूर्णांक i, portid;
	u64 control;

	pr = of_get_property(dp, "reg", शून्य);
	अगर (!pr) अणु
		prom_म_लिखो("sbus_iommu_init: Cannot map SYSIO "
			    "control registers.\n");
		prom_halt();
	पूर्ण
	regs = pr->phys_addr;

	iommu = kzalloc(माप(*iommu), GFP_ATOMIC);
	strbuf = kzalloc(माप(*strbuf), GFP_ATOMIC);
	अगर (!iommu || !strbuf)
		जाओ fatal_memory_error;

	op->dev.archdata.iommu = iommu;
	op->dev.archdata.stc = strbuf;
	op->dev.archdata.numa_node = NUMA_NO_NODE;

	reg_base = regs + SYSIO_IOMMUREG_BASE;
	iommu->iommu_control = reg_base + IOMMU_CONTROL;
	iommu->iommu_tsbbase = reg_base + IOMMU_TSBBASE;
	iommu->iommu_flush = reg_base + IOMMU_FLUSH;
	iommu->iommu_tags = iommu->iommu_control +
		(IOMMU_TAGDIAG - IOMMU_CONTROL);

	reg_base = regs + SYSIO_STRBUFREG_BASE;
	strbuf->strbuf_control = reg_base + STRBUF_CONTROL;
	strbuf->strbuf_pflush = reg_base + STRBUF_PFLUSH;
	strbuf->strbuf_fsync = reg_base + STRBUF_FSYNC;

	strbuf->strbuf_enabled = 1;

	strbuf->strbuf_flushflag = (अस्थिर अचिन्हित दीर्घ *)
		((((अचिन्हित दीर्घ)&strbuf->__flushflag_buf[0])
		  + 63UL)
		 & ~63UL);
	strbuf->strbuf_flushflag_pa = (अचिन्हित दीर्घ)
		__pa(strbuf->strbuf_flushflag);

	/* The SYSIO SBUS control रेजिस्टर is used क्रम dummy पढ़ोs
	 * in order to ensure ग_लिखो completion.
	 */
	iommu->ग_लिखो_complete_reg = regs + 0x2000UL;

	portid = of_getपूर्णांकprop_शेष(op->dev.of_node, "portid", -1);
	prपूर्णांकk(KERN_INFO "SYSIO: UPA portID %x, at %016lx\n",
	       portid, regs);

	/* Setup क्रम TSB_SIZE=7, TBW_SIZE=0, MMU_DE=1, MMU_EN=1 */
	अगर (iommu_table_init(iommu, IO_TSB_SIZE, MAP_BASE, 0xffffffff, -1))
		जाओ fatal_memory_error;

	control = upa_पढ़ोq(iommu->iommu_control);
	control = ((7UL << 16UL)	|
		   (0UL << 2UL)		|
		   (1UL << 1UL)		|
		   (1UL << 0UL));
	upa_ग_लिखोq(control, iommu->iommu_control);

	/* Clean out any cruft in the IOMMU using
	 * diagnostic accesses.
	 */
	क्रम (i = 0; i < 16; i++) अणु
		अचिन्हित दीर्घ dram, tag;

		dram = iommu->iommu_control + (IOMMU_DRAMDIAG - IOMMU_CONTROL);
		tag = iommu->iommu_control + (IOMMU_TAGDIAG - IOMMU_CONTROL);

		dram += (अचिन्हित दीर्घ)i * 8UL;
		tag += (अचिन्हित दीर्घ)i * 8UL;
		upa_ग_लिखोq(0, dram);
		upa_ग_लिखोq(0, tag);
	पूर्ण
	upa_पढ़ोq(iommu->ग_लिखो_complete_reg);

	/* Give the TSB to SYSIO. */
	upa_ग_लिखोq(__pa(iommu->page_table), iommu->iommu_tsbbase);

	/* Setup streaming buffer, DE=1 SB_EN=1 */
	control = (1UL << 1UL) | (1UL << 0UL);
	upa_ग_लिखोq(control, strbuf->strbuf_control);

	/* Clear out the tags using diagnostics. */
	क्रम (i = 0; i < 16; i++) अणु
		अचिन्हित दीर्घ ptag, ltag;

		ptag = strbuf->strbuf_control +
			(STRBUF_PTAGDIAG - STRBUF_CONTROL);
		ltag = strbuf->strbuf_control +
			(STRBUF_LTAGDIAG - STRBUF_CONTROL);
		ptag += (अचिन्हित दीर्घ)i * 8UL;
		ltag += (अचिन्हित दीर्घ)i * 8UL;

		upa_ग_लिखोq(0UL, ptag);
		upa_ग_लिखोq(0UL, ltag);
	पूर्ण

	/* Enable DVMA arbitration क्रम all devices/slots. */
	control = upa_पढ़ोq(iommu->ग_लिखो_complete_reg);
	control |= 0x3fUL;
	upa_ग_लिखोq(control, iommu->ग_लिखो_complete_reg);

	/* Now some Xfire specअगरic grot... */
	अगर (this_is_starfire)
		starfire_hookup(portid);

	sysio_रेजिस्टर_error_handlers(op);
	वापस;

fatal_memory_error:
	kमुक्त(iommu);
	kमुक्त(strbuf);
	prom_म_लिखो("sbus_iommu_init: Fatal memory allocation error.\n");
पूर्ण

अटल पूर्णांक __init sbus_init(व्योम)
अणु
	काष्ठा device_node *dp;

	क्रम_each_node_by_name(dp, "sbus") अणु
		काष्ठा platक्रमm_device *op = of_find_device_by_node(dp);

		sbus_iommu_init(op);
		of_propagate_archdata(op);
	पूर्ण

	वापस 0;
पूर्ण

subsys_initcall(sbus_init);
