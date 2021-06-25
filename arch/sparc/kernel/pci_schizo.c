<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* pci_schizo.c: SCHIZO/TOMATILLO specअगरic PCI controller support.
 *
 * Copyright (C) 2001, 2002, 2003, 2007, 2008 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_device.h>
#समावेश <linux/numa.h>

#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/pstate.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/upa.h>

#समावेश "pci_impl.h"
#समावेश "iommu_common.h"

#घोषणा DRIVER_NAME	"schizo"
#घोषणा PFX		DRIVER_NAME ": "

/* This is a convention that at least Excalibur and Merlin
 * follow.  I suppose the SCHIZO used in Starcat and मित्रs
 * will करो similar.
 *
 * The only way I could see this changing is अगर the newlink
 * block requires more space in Schizo's address space than
 * they predicted, thus requiring an address space reorg when
 * the newer Schizo is taped out.
 */

/* Streaming buffer control रेजिस्टर. */
#घोषणा SCHIZO_STRBUF_CTRL_LPTR    0x00000000000000f0UL /* LRU Lock Poपूर्णांकer */
#घोषणा SCHIZO_STRBUF_CTRL_LENAB   0x0000000000000008UL /* LRU Lock Enable */
#घोषणा SCHIZO_STRBUF_CTRL_RRDIS   0x0000000000000004UL /* Rerun Disable */
#घोषणा SCHIZO_STRBUF_CTRL_DENAB   0x0000000000000002UL /* Diagnostic Mode Enable */
#घोषणा SCHIZO_STRBUF_CTRL_ENAB    0x0000000000000001UL /* Streaming Buffer Enable */

/* IOMMU control रेजिस्टर. */
#घोषणा SCHIZO_IOMMU_CTRL_RESV     0xfffffffff9000000UL /* Reserved                      */
#घोषणा SCHIZO_IOMMU_CTRL_XLTESTAT 0x0000000006000000UL /* Translation Error Status      */
#घोषणा SCHIZO_IOMMU_CTRL_XLTEERR  0x0000000001000000UL /* Translation Error encountered */
#घोषणा SCHIZO_IOMMU_CTRL_LCKEN    0x0000000000800000UL /* Enable translation locking    */
#घोषणा SCHIZO_IOMMU_CTRL_LCKPTR   0x0000000000780000UL /* Translation lock poपूर्णांकer      */
#घोषणा SCHIZO_IOMMU_CTRL_TSBSZ    0x0000000000070000UL /* TSB Size                      */
#घोषणा SCHIZO_IOMMU_TSBSZ_1K      0x0000000000000000UL /* TSB Table 1024 8-byte entries */
#घोषणा SCHIZO_IOMMU_TSBSZ_2K      0x0000000000010000UL /* TSB Table 2048 8-byte entries */
#घोषणा SCHIZO_IOMMU_TSBSZ_4K      0x0000000000020000UL /* TSB Table 4096 8-byte entries */
#घोषणा SCHIZO_IOMMU_TSBSZ_8K      0x0000000000030000UL /* TSB Table 8192 8-byte entries */
#घोषणा SCHIZO_IOMMU_TSBSZ_16K     0x0000000000040000UL /* TSB Table 16k 8-byte entries  */
#घोषणा SCHIZO_IOMMU_TSBSZ_32K     0x0000000000050000UL /* TSB Table 32k 8-byte entries  */
#घोषणा SCHIZO_IOMMU_TSBSZ_64K     0x0000000000060000UL /* TSB Table 64k 8-byte entries  */
#घोषणा SCHIZO_IOMMU_TSBSZ_128K    0x0000000000070000UL /* TSB Table 128k 8-byte entries */
#घोषणा SCHIZO_IOMMU_CTRL_RESV2    0x000000000000fff8UL /* Reserved                      */
#घोषणा SCHIZO_IOMMU_CTRL_TBWSZ    0x0000000000000004UL /* Assumed page size, 0=8k 1=64k */
#घोषणा SCHIZO_IOMMU_CTRL_DENAB    0x0000000000000002UL /* Diagnostic mode enable        */
#घोषणा SCHIZO_IOMMU_CTRL_ENAB     0x0000000000000001UL /* IOMMU Enable                  */

/* Schizo config space address क्रमmat is nearly identical to
 * that of PSYCHO:
 *
 *  32             24 23 16 15    11 10       8 7   2  1 0
 * ---------------------------------------------------------
 * |0 0 0 0 0 0 0 0 0| bus | device | function | reg | 0 0 |
 * ---------------------------------------------------------
 */
#घोषणा SCHIZO_CONFIG_BASE(PBM)	((PBM)->config_space)
#घोषणा SCHIZO_CONFIG_ENCODE(BUS, DEVFN, REG)	\
	(((अचिन्हित दीर्घ)(BUS)   << 16) |	\
	 ((अचिन्हित दीर्घ)(DEVFN) << 8)  |	\
	 ((अचिन्हित दीर्घ)(REG)))

अटल व्योम *schizo_pci_config_mkaddr(काष्ठा pci_pbm_info *pbm,
				      अचिन्हित अक्षर bus,
				      अचिन्हित पूर्णांक devfn,
				      पूर्णांक where)
अणु
	अगर (!pbm)
		वापस शून्य;
	bus -= pbm->pci_first_busno;
	वापस (व्योम *)
		(SCHIZO_CONFIG_BASE(pbm) |
		 SCHIZO_CONFIG_ENCODE(bus, devfn, where));
पूर्ण

/* SCHIZO error handling support. */
क्रमागत schizo_error_type अणु
	UE_ERR, CE_ERR, PCI_ERR, SAFARI_ERR
पूर्ण;

अटल DEFINE_SPINLOCK(stc_buf_lock);
अटल अचिन्हित दीर्घ stc_error_buf[128];
अटल अचिन्हित दीर्घ stc_tag_buf[16];
अटल अचिन्हित दीर्घ stc_line_buf[16];

#घोषणा SCHIZO_UE_INO		0x30 /* Uncorrectable ECC error */
#घोषणा SCHIZO_CE_INO		0x31 /* Correctable ECC error */
#घोषणा SCHIZO_PCIERR_A_INO	0x32 /* PBM A PCI bus error */
#घोषणा SCHIZO_PCIERR_B_INO	0x33 /* PBM B PCI bus error */
#घोषणा SCHIZO_SERR_INO		0x34 /* Safari पूर्णांकerface error */

#घोषणा SCHIZO_STC_ERR	0xb800UL /* --> 0xba00 */
#घोषणा SCHIZO_STC_TAG	0xba00UL /* --> 0xba80 */
#घोषणा SCHIZO_STC_LINE	0xbb00UL /* --> 0xbb80 */

#घोषणा SCHIZO_STCERR_WRITE	0x2UL
#घोषणा SCHIZO_STCERR_READ	0x1UL

#घोषणा SCHIZO_STCTAG_PPN	0x3fffffff00000000UL
#घोषणा SCHIZO_STCTAG_VPN	0x00000000ffffe000UL
#घोषणा SCHIZO_STCTAG_VALID	0x8000000000000000UL
#घोषणा SCHIZO_STCTAG_READ	0x4000000000000000UL

#घोषणा SCHIZO_STCLINE_LINDX	0x0000000007800000UL
#घोषणा SCHIZO_STCLINE_SPTR	0x000000000007e000UL
#घोषणा SCHIZO_STCLINE_LADDR	0x0000000000001fc0UL
#घोषणा SCHIZO_STCLINE_EPTR	0x000000000000003fUL
#घोषणा SCHIZO_STCLINE_VALID	0x0000000000600000UL
#घोषणा SCHIZO_STCLINE_FOFN	0x0000000000180000UL

अटल व्योम __schizo_check_stc_error_pbm(काष्ठा pci_pbm_info *pbm,
					 क्रमागत schizo_error_type type)
अणु
	काष्ठा strbuf *strbuf = &pbm->stc;
	अचिन्हित दीर्घ regbase = pbm->pbm_regs;
	अचिन्हित दीर्घ err_base, tag_base, line_base;
	u64 control;
	पूर्णांक i;

	err_base = regbase + SCHIZO_STC_ERR;
	tag_base = regbase + SCHIZO_STC_TAG;
	line_base = regbase + SCHIZO_STC_LINE;

	spin_lock(&stc_buf_lock);

	/* This is __REALLY__ dangerous.  When we put the
	 * streaming buffer पूर्णांकo diagnostic mode to probe
	 * it's tags and error status, we _must_ clear all
	 * of the line tag valid bits beक्रमe re-enabling
	 * the streaming buffer.  If any dirty data lives
	 * in the STC when we करो this, we will end up
	 * invalidating it beक्रमe it has a chance to reach
	 * मुख्य memory.
	 */
	control = upa_पढ़ोq(strbuf->strbuf_control);
	upa_ग_लिखोq((control | SCHIZO_STRBUF_CTRL_DENAB),
		   strbuf->strbuf_control);
	क्रम (i = 0; i < 128; i++) अणु
		अचिन्हित दीर्घ val;

		val = upa_पढ़ोq(err_base + (i * 8UL));
		upa_ग_लिखोq(0UL, err_base + (i * 8UL));
		stc_error_buf[i] = val;
	पूर्ण
	क्रम (i = 0; i < 16; i++) अणु
		stc_tag_buf[i] = upa_पढ़ोq(tag_base + (i * 8UL));
		stc_line_buf[i] = upa_पढ़ोq(line_base + (i * 8UL));
		upa_ग_लिखोq(0UL, tag_base + (i * 8UL));
		upa_ग_लिखोq(0UL, line_base + (i * 8UL));
	पूर्ण

	/* OK, state is logged, निकास diagnostic mode. */
	upa_ग_लिखोq(control, strbuf->strbuf_control);

	क्रम (i = 0; i < 16; i++) अणु
		पूर्णांक j, saw_error, first, last;

		saw_error = 0;
		first = i * 8;
		last = first + 8;
		क्रम (j = first; j < last; j++) अणु
			अचिन्हित दीर्घ errval = stc_error_buf[j];
			अगर (errval != 0) अणु
				saw_error++;
				prपूर्णांकk("%s: STC_ERR(%d)[wr(%d)rd(%d)]\n",
				       pbm->name,
				       j,
				       (errval & SCHIZO_STCERR_WRITE) ? 1 : 0,
				       (errval & SCHIZO_STCERR_READ) ? 1 : 0);
			पूर्ण
		पूर्ण
		अगर (saw_error != 0) अणु
			अचिन्हित दीर्घ tagval = stc_tag_buf[i];
			अचिन्हित दीर्घ lineval = stc_line_buf[i];
			prपूर्णांकk("%s: STC_TAG(%d)[PA(%016lx)VA(%08lx)V(%d)R(%d)]\n",
			       pbm->name,
			       i,
			       ((tagval & SCHIZO_STCTAG_PPN) >> 19UL),
			       (tagval & SCHIZO_STCTAG_VPN),
			       ((tagval & SCHIZO_STCTAG_VALID) ? 1 : 0),
			       ((tagval & SCHIZO_STCTAG_READ) ? 1 : 0));

			/* XXX Should spit out per-bank error inक्रमmation... -DaveM */
			prपूर्णांकk("%s: STC_LINE(%d)[LIDX(%lx)SP(%lx)LADDR(%lx)EP(%lx)"
			       "V(%d)FOFN(%d)]\n",
			       pbm->name,
			       i,
			       ((lineval & SCHIZO_STCLINE_LINDX) >> 23UL),
			       ((lineval & SCHIZO_STCLINE_SPTR) >> 13UL),
			       ((lineval & SCHIZO_STCLINE_LADDR) >> 6UL),
			       ((lineval & SCHIZO_STCLINE_EPTR) >> 0UL),
			       ((lineval & SCHIZO_STCLINE_VALID) ? 1 : 0),
			       ((lineval & SCHIZO_STCLINE_FOFN) ? 1 : 0));
		पूर्ण
	पूर्ण

	spin_unlock(&stc_buf_lock);
पूर्ण

/* IOMMU is per-PBM in Schizo, so पूर्णांकerrogate both क्रम anonymous
 * controller level errors.
 */

#घोषणा SCHIZO_IOMMU_TAG	0xa580UL
#घोषणा SCHIZO_IOMMU_DATA	0xa600UL

#घोषणा SCHIZO_IOMMU_TAG_CTXT	0x0000001ffe000000UL
#घोषणा SCHIZO_IOMMU_TAG_ERRSTS	0x0000000001800000UL
#घोषणा SCHIZO_IOMMU_TAG_ERR	0x0000000000400000UL
#घोषणा SCHIZO_IOMMU_TAG_WRITE	0x0000000000200000UL
#घोषणा SCHIZO_IOMMU_TAG_STREAM	0x0000000000100000UL
#घोषणा SCHIZO_IOMMU_TAG_SIZE	0x0000000000080000UL
#घोषणा SCHIZO_IOMMU_TAG_VPAGE	0x000000000007ffffUL

#घोषणा SCHIZO_IOMMU_DATA_VALID	0x0000000100000000UL
#घोषणा SCHIZO_IOMMU_DATA_CACHE	0x0000000040000000UL
#घोषणा SCHIZO_IOMMU_DATA_PPAGE	0x000000003fffffffUL

अटल व्योम schizo_check_iommu_error_pbm(काष्ठा pci_pbm_info *pbm,
					 क्रमागत schizo_error_type type)
अणु
	काष्ठा iommu *iommu = pbm->iommu;
	अचिन्हित दीर्घ iommu_tag[16];
	अचिन्हित दीर्घ iommu_data[16];
	अचिन्हित दीर्घ flags;
	u64 control;
	पूर्णांक i;

	spin_lock_irqsave(&iommu->lock, flags);
	control = upa_पढ़ोq(iommu->iommu_control);
	अगर (control & SCHIZO_IOMMU_CTRL_XLTEERR) अणु
		अचिन्हित दीर्घ base;
		अक्षर *type_string;

		/* Clear the error encountered bit. */
		control &= ~SCHIZO_IOMMU_CTRL_XLTEERR;
		upa_ग_लिखोq(control, iommu->iommu_control);

		चयन((control & SCHIZO_IOMMU_CTRL_XLTESTAT) >> 25UL) अणु
		हाल 0:
			type_string = "Protection Error";
			अवरोध;
		हाल 1:
			type_string = "Invalid Error";
			अवरोध;
		हाल 2:
			type_string = "TimeOut Error";
			अवरोध;
		हाल 3:
		शेष:
			type_string = "ECC Error";
			अवरोध;
		पूर्ण
		prपूर्णांकk("%s: IOMMU Error, type[%s]\n",
		       pbm->name, type_string);

		/* Put the IOMMU पूर्णांकo diagnostic mode and probe
		 * it's TLB क्रम entries with error status.
		 *
		 * It is very possible क्रम another DVMA to occur
		 * जबतक we करो this probe, and corrupt the प्रणाली
		 * further.  But we are so screwed at this poपूर्णांक
		 * that we are likely to crash hard anyways, so
		 * get as much diagnostic inक्रमmation to the
		 * console as we can.
		 */
		upa_ग_लिखोq(control | SCHIZO_IOMMU_CTRL_DENAB,
			   iommu->iommu_control);

		base = pbm->pbm_regs;

		क्रम (i = 0; i < 16; i++) अणु
			iommu_tag[i] =
				upa_पढ़ोq(base + SCHIZO_IOMMU_TAG + (i * 8UL));
			iommu_data[i] =
				upa_पढ़ोq(base + SCHIZO_IOMMU_DATA + (i * 8UL));

			/* Now clear out the entry. */
			upa_ग_लिखोq(0, base + SCHIZO_IOMMU_TAG + (i * 8UL));
			upa_ग_लिखोq(0, base + SCHIZO_IOMMU_DATA + (i * 8UL));
		पूर्ण

		/* Leave diagnostic mode. */
		upa_ग_लिखोq(control, iommu->iommu_control);

		क्रम (i = 0; i < 16; i++) अणु
			अचिन्हित दीर्घ tag, data;

			tag = iommu_tag[i];
			अगर (!(tag & SCHIZO_IOMMU_TAG_ERR))
				जारी;

			data = iommu_data[i];
			चयन((tag & SCHIZO_IOMMU_TAG_ERRSTS) >> 23UL) अणु
			हाल 0:
				type_string = "Protection Error";
				अवरोध;
			हाल 1:
				type_string = "Invalid Error";
				अवरोध;
			हाल 2:
				type_string = "TimeOut Error";
				अवरोध;
			हाल 3:
			शेष:
				type_string = "ECC Error";
				अवरोध;
			पूर्ण
			prपूर्णांकk("%s: IOMMU TAG(%d)[error(%s) ctx(%x) wr(%d) str(%d) "
			       "sz(%dK) vpg(%08lx)]\n",
			       pbm->name, i, type_string,
			       (पूर्णांक)((tag & SCHIZO_IOMMU_TAG_CTXT) >> 25UL),
			       ((tag & SCHIZO_IOMMU_TAG_WRITE) ? 1 : 0),
			       ((tag & SCHIZO_IOMMU_TAG_STREAM) ? 1 : 0),
			       ((tag & SCHIZO_IOMMU_TAG_SIZE) ? 64 : 8),
			       (tag & SCHIZO_IOMMU_TAG_VPAGE) << IOMMU_PAGE_SHIFT);
			prपूर्णांकk("%s: IOMMU DATA(%d)[valid(%d) cache(%d) ppg(%016lx)]\n",
			       pbm->name, i,
			       ((data & SCHIZO_IOMMU_DATA_VALID) ? 1 : 0),
			       ((data & SCHIZO_IOMMU_DATA_CACHE) ? 1 : 0),
			       (data & SCHIZO_IOMMU_DATA_PPAGE) << IOMMU_PAGE_SHIFT);
		पूर्ण
	पूर्ण
	अगर (pbm->stc.strbuf_enabled)
		__schizo_check_stc_error_pbm(pbm, type);
	spin_unlock_irqrestore(&iommu->lock, flags);
पूर्ण

अटल व्योम schizo_check_iommu_error(काष्ठा pci_pbm_info *pbm,
				     क्रमागत schizo_error_type type)
अणु
	schizo_check_iommu_error_pbm(pbm, type);
	अगर (pbm->sibling)
		schizo_check_iommu_error_pbm(pbm->sibling, type);
पूर्ण

/* Uncorrectable ECC error status gathering. */
#घोषणा SCHIZO_UE_AFSR	0x10030UL
#घोषणा SCHIZO_UE_AFAR	0x10038UL

#घोषणा SCHIZO_UEAFSR_PPIO	0x8000000000000000UL /* Safari */
#घोषणा SCHIZO_UEAFSR_PDRD	0x4000000000000000UL /* Safari/Tomatillo */
#घोषणा SCHIZO_UEAFSR_PDWR	0x2000000000000000UL /* Safari */
#घोषणा SCHIZO_UEAFSR_SPIO	0x1000000000000000UL /* Safari */
#घोषणा SCHIZO_UEAFSR_SDMA	0x0800000000000000UL /* Safari/Tomatillo */
#घोषणा SCHIZO_UEAFSR_ERRPNDG	0x0300000000000000UL /* Safari */
#घोषणा SCHIZO_UEAFSR_BMSK	0x000003ff00000000UL /* Safari */
#घोषणा SCHIZO_UEAFSR_QOFF	0x00000000c0000000UL /* Safari/Tomatillo */
#घोषणा SCHIZO_UEAFSR_AID	0x000000001f000000UL /* Safari/Tomatillo */
#घोषणा SCHIZO_UEAFSR_PARTIAL	0x0000000000800000UL /* Safari */
#घोषणा SCHIZO_UEAFSR_OWNEDIN	0x0000000000400000UL /* Safari */
#घोषणा SCHIZO_UEAFSR_MTAGSYND	0x00000000000f0000UL /* Safari */
#घोषणा SCHIZO_UEAFSR_MTAG	0x000000000000e000UL /* Safari */
#घोषणा SCHIZO_UEAFSR_ECCSYND	0x00000000000001ffUL /* Safari */

अटल irqवापस_t schizo_ue_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pci_pbm_info *pbm = dev_id;
	अचिन्हित दीर्घ afsr_reg = pbm->controller_regs + SCHIZO_UE_AFSR;
	अचिन्हित दीर्घ afar_reg = pbm->controller_regs + SCHIZO_UE_AFAR;
	अचिन्हित दीर्घ afsr, afar, error_bits;
	पूर्णांक reported, limit;

	/* Latch uncorrectable error status. */
	afar = upa_पढ़ोq(afar_reg);

	/* If either of the error pending bits are set in the
	 * AFSR, the error status is being actively updated by
	 * the hardware and we must re-पढ़ो to get a clean value.
	 */
	limit = 1000;
	करो अणु
		afsr = upa_पढ़ोq(afsr_reg);
	पूर्ण जबतक ((afsr & SCHIZO_UEAFSR_ERRPNDG) != 0 && --limit);

	/* Clear the primary/secondary error status bits. */
	error_bits = afsr &
		(SCHIZO_UEAFSR_PPIO | SCHIZO_UEAFSR_PDRD | SCHIZO_UEAFSR_PDWR |
		 SCHIZO_UEAFSR_SPIO | SCHIZO_UEAFSR_SDMA);
	अगर (!error_bits)
		वापस IRQ_NONE;
	upa_ग_लिखोq(error_bits, afsr_reg);

	/* Log the error. */
	prपूर्णांकk("%s: Uncorrectable Error, primary error type[%s]\n",
	       pbm->name,
	       (((error_bits & SCHIZO_UEAFSR_PPIO) ?
		 "PIO" :
		 ((error_bits & SCHIZO_UEAFSR_PDRD) ?
		  "DMA Read" :
		  ((error_bits & SCHIZO_UEAFSR_PDWR) ?
		   "DMA Write" : "???")))));
	prपूर्णांकk("%s: bytemask[%04lx] qword_offset[%lx] SAFARI_AID[%02lx]\n",
	       pbm->name,
	       (afsr & SCHIZO_UEAFSR_BMSK) >> 32UL,
	       (afsr & SCHIZO_UEAFSR_QOFF) >> 30UL,
	       (afsr & SCHIZO_UEAFSR_AID) >> 24UL);
	prपूर्णांकk("%s: partial[%d] owned_in[%d] mtag[%lx] mtag_synd[%lx] ecc_sync[%lx]\n",
	       pbm->name,
	       (afsr & SCHIZO_UEAFSR_PARTIAL) ? 1 : 0,
	       (afsr & SCHIZO_UEAFSR_OWNEDIN) ? 1 : 0,
	       (afsr & SCHIZO_UEAFSR_MTAG) >> 13UL,
	       (afsr & SCHIZO_UEAFSR_MTAGSYND) >> 16UL,
	       (afsr & SCHIZO_UEAFSR_ECCSYND) >> 0UL);
	prपूर्णांकk("%s: UE AFAR [%016lx]\n", pbm->name, afar);
	prपूर्णांकk("%s: UE Secondary errors [", pbm->name);
	reported = 0;
	अगर (afsr & SCHIZO_UEAFSR_SPIO) अणु
		reported++;
		prपूर्णांकk("(PIO)");
	पूर्ण
	अगर (afsr & SCHIZO_UEAFSR_SDMA) अणु
		reported++;
		prपूर्णांकk("(DMA)");
	पूर्ण
	अगर (!reported)
		prपूर्णांकk("(none)");
	prपूर्णांकk("]\n");

	/* Interrogate IOMMU क्रम error status. */
	schizo_check_iommu_error(pbm, UE_ERR);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा SCHIZO_CE_AFSR	0x10040UL
#घोषणा SCHIZO_CE_AFAR	0x10048UL

#घोषणा SCHIZO_CEAFSR_PPIO	0x8000000000000000UL
#घोषणा SCHIZO_CEAFSR_PDRD	0x4000000000000000UL
#घोषणा SCHIZO_CEAFSR_PDWR	0x2000000000000000UL
#घोषणा SCHIZO_CEAFSR_SPIO	0x1000000000000000UL
#घोषणा SCHIZO_CEAFSR_SDMA	0x0800000000000000UL
#घोषणा SCHIZO_CEAFSR_ERRPNDG	0x0300000000000000UL
#घोषणा SCHIZO_CEAFSR_BMSK	0x000003ff00000000UL
#घोषणा SCHIZO_CEAFSR_QOFF	0x00000000c0000000UL
#घोषणा SCHIZO_CEAFSR_AID	0x000000001f000000UL
#घोषणा SCHIZO_CEAFSR_PARTIAL	0x0000000000800000UL
#घोषणा SCHIZO_CEAFSR_OWNEDIN	0x0000000000400000UL
#घोषणा SCHIZO_CEAFSR_MTAGSYND	0x00000000000f0000UL
#घोषणा SCHIZO_CEAFSR_MTAG	0x000000000000e000UL
#घोषणा SCHIZO_CEAFSR_ECCSYND	0x00000000000001ffUL

अटल irqवापस_t schizo_ce_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pci_pbm_info *pbm = dev_id;
	अचिन्हित दीर्घ afsr_reg = pbm->controller_regs + SCHIZO_CE_AFSR;
	अचिन्हित दीर्घ afar_reg = pbm->controller_regs + SCHIZO_CE_AFAR;
	अचिन्हित दीर्घ afsr, afar, error_bits;
	पूर्णांक reported, limit;

	/* Latch error status. */
	afar = upa_पढ़ोq(afar_reg);

	/* If either of the error pending bits are set in the
	 * AFSR, the error status is being actively updated by
	 * the hardware and we must re-पढ़ो to get a clean value.
	 */
	limit = 1000;
	करो अणु
		afsr = upa_पढ़ोq(afsr_reg);
	पूर्ण जबतक ((afsr & SCHIZO_UEAFSR_ERRPNDG) != 0 && --limit);

	/* Clear primary/secondary error status bits. */
	error_bits = afsr &
		(SCHIZO_CEAFSR_PPIO | SCHIZO_CEAFSR_PDRD | SCHIZO_CEAFSR_PDWR |
		 SCHIZO_CEAFSR_SPIO | SCHIZO_CEAFSR_SDMA);
	अगर (!error_bits)
		वापस IRQ_NONE;
	upa_ग_लिखोq(error_bits, afsr_reg);

	/* Log the error. */
	prपूर्णांकk("%s: Correctable Error, primary error type[%s]\n",
	       pbm->name,
	       (((error_bits & SCHIZO_CEAFSR_PPIO) ?
		 "PIO" :
		 ((error_bits & SCHIZO_CEAFSR_PDRD) ?
		  "DMA Read" :
		  ((error_bits & SCHIZO_CEAFSR_PDWR) ?
		   "DMA Write" : "???")))));

	/* XXX Use syndrome and afar to prपूर्णांक out module string just like
	 * XXX UDB CE trap handler करोes... -DaveM
	 */
	prपूर्णांकk("%s: bytemask[%04lx] qword_offset[%lx] SAFARI_AID[%02lx]\n",
	       pbm->name,
	       (afsr & SCHIZO_UEAFSR_BMSK) >> 32UL,
	       (afsr & SCHIZO_UEAFSR_QOFF) >> 30UL,
	       (afsr & SCHIZO_UEAFSR_AID) >> 24UL);
	prपूर्णांकk("%s: partial[%d] owned_in[%d] mtag[%lx] mtag_synd[%lx] ecc_sync[%lx]\n",
	       pbm->name,
	       (afsr & SCHIZO_UEAFSR_PARTIAL) ? 1 : 0,
	       (afsr & SCHIZO_UEAFSR_OWNEDIN) ? 1 : 0,
	       (afsr & SCHIZO_UEAFSR_MTAG) >> 13UL,
	       (afsr & SCHIZO_UEAFSR_MTAGSYND) >> 16UL,
	       (afsr & SCHIZO_UEAFSR_ECCSYND) >> 0UL);
	prपूर्णांकk("%s: CE AFAR [%016lx]\n", pbm->name, afar);
	prपूर्णांकk("%s: CE Secondary errors [", pbm->name);
	reported = 0;
	अगर (afsr & SCHIZO_CEAFSR_SPIO) अणु
		reported++;
		prपूर्णांकk("(PIO)");
	पूर्ण
	अगर (afsr & SCHIZO_CEAFSR_SDMA) अणु
		reported++;
		prपूर्णांकk("(DMA)");
	पूर्ण
	अगर (!reported)
		prपूर्णांकk("(none)");
	prपूर्णांकk("]\n");

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा SCHIZO_PCI_AFSR	0x2010UL
#घोषणा SCHIZO_PCI_AFAR	0x2018UL

#घोषणा SCHIZO_PCIAFSR_PMA	0x8000000000000000UL /* Schizo/Tomatillo */
#घोषणा SCHIZO_PCIAFSR_PTA	0x4000000000000000UL /* Schizo/Tomatillo */
#घोषणा SCHIZO_PCIAFSR_PRTRY	0x2000000000000000UL /* Schizo/Tomatillo */
#घोषणा SCHIZO_PCIAFSR_PPERR	0x1000000000000000UL /* Schizo/Tomatillo */
#घोषणा SCHIZO_PCIAFSR_PTTO	0x0800000000000000UL /* Schizo/Tomatillo */
#घोषणा SCHIZO_PCIAFSR_PUNUS	0x0400000000000000UL /* Schizo */
#घोषणा SCHIZO_PCIAFSR_SMA	0x0200000000000000UL /* Schizo/Tomatillo */
#घोषणा SCHIZO_PCIAFSR_STA	0x0100000000000000UL /* Schizo/Tomatillo */
#घोषणा SCHIZO_PCIAFSR_SRTRY	0x0080000000000000UL /* Schizo/Tomatillo */
#घोषणा SCHIZO_PCIAFSR_SPERR	0x0040000000000000UL /* Schizo/Tomatillo */
#घोषणा SCHIZO_PCIAFSR_STTO	0x0020000000000000UL /* Schizo/Tomatillo */
#घोषणा SCHIZO_PCIAFSR_SUNUS	0x0010000000000000UL /* Schizo */
#घोषणा SCHIZO_PCIAFSR_BMSK	0x000003ff00000000UL /* Schizo/Tomatillo */
#घोषणा SCHIZO_PCIAFSR_BLK	0x0000000080000000UL /* Schizo/Tomatillo */
#घोषणा SCHIZO_PCIAFSR_CFG	0x0000000040000000UL /* Schizo/Tomatillo */
#घोषणा SCHIZO_PCIAFSR_MEM	0x0000000020000000UL /* Schizo/Tomatillo */
#घोषणा SCHIZO_PCIAFSR_IO	0x0000000010000000UL /* Schizo/Tomatillo */

#घोषणा SCHIZO_PCI_CTRL		(0x2000UL)
#घोषणा SCHIZO_PCICTRL_BUS_UNUS	(1UL << 63UL) /* Safari */
#घोषणा SCHIZO_PCICTRL_DTO_INT	(1UL << 61UL) /* Tomatillo */
#घोषणा SCHIZO_PCICTRL_ARB_PRIO (0x1ff << 52UL) /* Tomatillo */
#घोषणा SCHIZO_PCICTRL_ESLCK	(1UL << 51UL) /* Safari */
#घोषणा SCHIZO_PCICTRL_ERRSLOT	(7UL << 48UL) /* Safari */
#घोषणा SCHIZO_PCICTRL_TTO_ERR	(1UL << 38UL) /* Safari/Tomatillo */
#घोषणा SCHIZO_PCICTRL_RTRY_ERR	(1UL << 37UL) /* Safari/Tomatillo */
#घोषणा SCHIZO_PCICTRL_DTO_ERR	(1UL << 36UL) /* Safari/Tomatillo */
#घोषणा SCHIZO_PCICTRL_SBH_ERR	(1UL << 35UL) /* Safari */
#घोषणा SCHIZO_PCICTRL_SERR	(1UL << 34UL) /* Safari/Tomatillo */
#घोषणा SCHIZO_PCICTRL_PCISPD	(1UL << 33UL) /* Safari */
#घोषणा SCHIZO_PCICTRL_MRM_PREF	(1UL << 30UL) /* Tomatillo */
#घोषणा SCHIZO_PCICTRL_RDO_PREF	(1UL << 29UL) /* Tomatillo */
#घोषणा SCHIZO_PCICTRL_RDL_PREF	(1UL << 28UL) /* Tomatillo */
#घोषणा SCHIZO_PCICTRL_PTO	(3UL << 24UL) /* Safari/Tomatillo */
#घोषणा SCHIZO_PCICTRL_PTO_SHIFT 24UL
#घोषणा SCHIZO_PCICTRL_TRWSW	(7UL << 21UL) /* Tomatillo */
#घोषणा SCHIZO_PCICTRL_F_TGT_A	(1UL << 20UL) /* Tomatillo */
#घोषणा SCHIZO_PCICTRL_S_DTO_INT (1UL << 19UL) /* Safari */
#घोषणा SCHIZO_PCICTRL_F_TGT_RT	(1UL << 19UL) /* Tomatillo */
#घोषणा SCHIZO_PCICTRL_SBH_INT	(1UL << 18UL) /* Safari */
#घोषणा SCHIZO_PCICTRL_T_DTO_INT (1UL << 18UL) /* Tomatillo */
#घोषणा SCHIZO_PCICTRL_EEN	(1UL << 17UL) /* Safari/Tomatillo */
#घोषणा SCHIZO_PCICTRL_PARK	(1UL << 16UL) /* Safari/Tomatillo */
#घोषणा SCHIZO_PCICTRL_PCIRST	(1UL <<  8UL) /* Safari */
#घोषणा SCHIZO_PCICTRL_ARB_S	(0x3fUL << 0UL) /* Safari */
#घोषणा SCHIZO_PCICTRL_ARB_T	(0xffUL << 0UL) /* Tomatillo */

अटल irqवापस_t schizo_pcierr_पूर्णांकr_other(काष्ठा pci_pbm_info *pbm)
अणु
	अचिन्हित दीर्घ csr_reg, csr, csr_error_bits;
	irqवापस_t ret = IRQ_NONE;
	u32 stat;

	csr_reg = pbm->pbm_regs + SCHIZO_PCI_CTRL;
	csr = upa_पढ़ोq(csr_reg);
	csr_error_bits =
		csr & (SCHIZO_PCICTRL_BUS_UNUS |
		       SCHIZO_PCICTRL_TTO_ERR |
		       SCHIZO_PCICTRL_RTRY_ERR |
		       SCHIZO_PCICTRL_DTO_ERR |
		       SCHIZO_PCICTRL_SBH_ERR |
		       SCHIZO_PCICTRL_SERR);
	अगर (csr_error_bits) अणु
		/* Clear the errors.  */
		upa_ग_लिखोq(csr, csr_reg);

		/* Log 'em.  */
		अगर (csr_error_bits & SCHIZO_PCICTRL_BUS_UNUS)
			prपूर्णांकk("%s: Bus unusable error asserted.\n",
			       pbm->name);
		अगर (csr_error_bits & SCHIZO_PCICTRL_TTO_ERR)
			prपूर्णांकk("%s: PCI TRDY# timeout error asserted.\n",
			       pbm->name);
		अगर (csr_error_bits & SCHIZO_PCICTRL_RTRY_ERR)
			prपूर्णांकk("%s: PCI excessive retry error asserted.\n",
			       pbm->name);
		अगर (csr_error_bits & SCHIZO_PCICTRL_DTO_ERR)
			prपूर्णांकk("%s: PCI discard timeout error asserted.\n",
			       pbm->name);
		अगर (csr_error_bits & SCHIZO_PCICTRL_SBH_ERR)
			prपूर्णांकk("%s: PCI streaming byte hole error asserted.\n",
			       pbm->name);
		अगर (csr_error_bits & SCHIZO_PCICTRL_SERR)
			prपूर्णांकk("%s: PCI SERR signal asserted.\n",
			       pbm->name);
		ret = IRQ_HANDLED;
	पूर्ण
	pbm->pci_ops->पढ़ो(pbm->pci_bus, 0, PCI_STATUS, 2, &stat);
	अगर (stat & (PCI_STATUS_PARITY |
		    PCI_STATUS_SIG_TARGET_ABORT |
		    PCI_STATUS_REC_TARGET_ABORT |
		    PCI_STATUS_REC_MASTER_ABORT |
		    PCI_STATUS_SIG_SYSTEM_ERROR)) अणु
		prपूर्णांकk("%s: PCI bus error, PCI_STATUS[%04x]\n",
		       pbm->name, stat);
		pbm->pci_ops->ग_लिखो(pbm->pci_bus, 0, PCI_STATUS, 2, 0xffff);
		ret = IRQ_HANDLED;
	पूर्ण
	वापस ret;
पूर्ण

अटल irqवापस_t schizo_pcierr_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pci_pbm_info *pbm = dev_id;
	अचिन्हित दीर्घ afsr_reg, afar_reg, base;
	अचिन्हित दीर्घ afsr, afar, error_bits;
	पूर्णांक reported;

	base = pbm->pbm_regs;

	afsr_reg = base + SCHIZO_PCI_AFSR;
	afar_reg = base + SCHIZO_PCI_AFAR;

	/* Latch error status. */
	afar = upa_पढ़ोq(afar_reg);
	afsr = upa_पढ़ोq(afsr_reg);

	/* Clear primary/secondary error status bits. */
	error_bits = afsr &
		(SCHIZO_PCIAFSR_PMA | SCHIZO_PCIAFSR_PTA |
		 SCHIZO_PCIAFSR_PRTRY | SCHIZO_PCIAFSR_PPERR |
		 SCHIZO_PCIAFSR_PTTO | SCHIZO_PCIAFSR_PUNUS |
		 SCHIZO_PCIAFSR_SMA | SCHIZO_PCIAFSR_STA |
		 SCHIZO_PCIAFSR_SRTRY | SCHIZO_PCIAFSR_SPERR |
		 SCHIZO_PCIAFSR_STTO | SCHIZO_PCIAFSR_SUNUS);
	अगर (!error_bits)
		वापस schizo_pcierr_पूर्णांकr_other(pbm);
	upa_ग_लिखोq(error_bits, afsr_reg);

	/* Log the error. */
	prपूर्णांकk("%s: PCI Error, primary error type[%s]\n",
	       pbm->name,
	       (((error_bits & SCHIZO_PCIAFSR_PMA) ?
		 "Master Abort" :
		 ((error_bits & SCHIZO_PCIAFSR_PTA) ?
		  "Target Abort" :
		  ((error_bits & SCHIZO_PCIAFSR_PRTRY) ?
		   "Excessive Retries" :
		   ((error_bits & SCHIZO_PCIAFSR_PPERR) ?
		    "Parity Error" :
		    ((error_bits & SCHIZO_PCIAFSR_PTTO) ?
		     "Timeout" :
		     ((error_bits & SCHIZO_PCIAFSR_PUNUS) ?
		      "Bus Unusable" : "???"))))))));
	prपूर्णांकk("%s: bytemask[%04lx] was_block(%d) space(%s)\n",
	       pbm->name,
	       (afsr & SCHIZO_PCIAFSR_BMSK) >> 32UL,
	       (afsr & SCHIZO_PCIAFSR_BLK) ? 1 : 0,
	       ((afsr & SCHIZO_PCIAFSR_CFG) ?
		"Config" :
		((afsr & SCHIZO_PCIAFSR_MEM) ?
		 "Memory" :
		 ((afsr & SCHIZO_PCIAFSR_IO) ?
		  "I/O" : "???"))));
	prपूर्णांकk("%s: PCI AFAR [%016lx]\n",
	       pbm->name, afar);
	prपूर्णांकk("%s: PCI Secondary errors [",
	       pbm->name);
	reported = 0;
	अगर (afsr & SCHIZO_PCIAFSR_SMA) अणु
		reported++;
		prपूर्णांकk("(Master Abort)");
	पूर्ण
	अगर (afsr & SCHIZO_PCIAFSR_STA) अणु
		reported++;
		prपूर्णांकk("(Target Abort)");
	पूर्ण
	अगर (afsr & SCHIZO_PCIAFSR_SRTRY) अणु
		reported++;
		prपूर्णांकk("(Excessive Retries)");
	पूर्ण
	अगर (afsr & SCHIZO_PCIAFSR_SPERR) अणु
		reported++;
		prपूर्णांकk("(Parity Error)");
	पूर्ण
	अगर (afsr & SCHIZO_PCIAFSR_STTO) अणु
		reported++;
		prपूर्णांकk("(Timeout)");
	पूर्ण
	अगर (afsr & SCHIZO_PCIAFSR_SUNUS) अणु
		reported++;
		prपूर्णांकk("(Bus Unusable)");
	पूर्ण
	अगर (!reported)
		prपूर्णांकk("(none)");
	prपूर्णांकk("]\n");

	/* For the error types shown, scan PBM's PCI bus क्रम devices
	 * which have logged that error type.
	 */

	/* If we see a Target Abort, this could be the result of an
	 * IOMMU translation error of some sort.  It is extremely
	 * useful to log this inक्रमmation as usually it indicates
	 * a bug in the IOMMU support code or a PCI device driver.
	 */
	अगर (error_bits & (SCHIZO_PCIAFSR_PTA | SCHIZO_PCIAFSR_STA)) अणु
		schizo_check_iommu_error(pbm, PCI_ERR);
		pci_scan_क्रम_target_पात(pbm, pbm->pci_bus);
	पूर्ण
	अगर (error_bits & (SCHIZO_PCIAFSR_PMA | SCHIZO_PCIAFSR_SMA))
		pci_scan_क्रम_master_पात(pbm, pbm->pci_bus);

	/* For excessive retries, PSYCHO/PBM will पात the device
	 * and there is no way to specअगरically check क्रम excessive
	 * retries in the config space status रेजिस्टरs.  So what
	 * we hope is that we'll catch it via the master/target
	 * पात events.
	 */

	अगर (error_bits & (SCHIZO_PCIAFSR_PPERR | SCHIZO_PCIAFSR_SPERR))
		pci_scan_क्रम_parity_error(pbm, pbm->pci_bus);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा SCHIZO_SAFARI_ERRLOG	0x10018UL

#घोषणा SAFARI_ERRLOG_ERROUT	0x8000000000000000UL

#घोषणा BUS_ERROR_BADCMD	0x4000000000000000UL /* Schizo/Tomatillo */
#घोषणा BUS_ERROR_SSMDIS	0x2000000000000000UL /* Safari */
#घोषणा BUS_ERROR_BADMA		0x1000000000000000UL /* Safari */
#घोषणा BUS_ERROR_BADMB		0x0800000000000000UL /* Safari */
#घोषणा BUS_ERROR_BADMC		0x0400000000000000UL /* Safari */
#घोषणा BUS_ERROR_SNOOP_GR	0x0000000000200000UL /* Tomatillo */
#घोषणा BUS_ERROR_SNOOP_PCI	0x0000000000100000UL /* Tomatillo */
#घोषणा BUS_ERROR_SNOOP_RD	0x0000000000080000UL /* Tomatillo */
#घोषणा BUS_ERROR_SNOOP_RDS	0x0000000000020000UL /* Tomatillo */
#घोषणा BUS_ERROR_SNOOP_RDSA	0x0000000000010000UL /* Tomatillo */
#घोषणा BUS_ERROR_SNOOP_OWN	0x0000000000008000UL /* Tomatillo */
#घोषणा BUS_ERROR_SNOOP_RDO	0x0000000000004000UL /* Tomatillo */
#घोषणा BUS_ERROR_CPU1PS	0x0000000000002000UL /* Safari */
#घोषणा BUS_ERROR_WDATA_PERR	0x0000000000002000UL /* Tomatillo */
#घोषणा BUS_ERROR_CPU1PB	0x0000000000001000UL /* Safari */
#घोषणा BUS_ERROR_CTRL_PERR	0x0000000000001000UL /* Tomatillo */
#घोषणा BUS_ERROR_CPU0PS	0x0000000000000800UL /* Safari */
#घोषणा BUS_ERROR_SNOOP_ERR	0x0000000000000800UL /* Tomatillo */
#घोषणा BUS_ERROR_CPU0PB	0x0000000000000400UL /* Safari */
#घोषणा BUS_ERROR_JBUS_ILL_B	0x0000000000000400UL /* Tomatillo */
#घोषणा BUS_ERROR_CIQTO		0x0000000000000200UL /* Safari */
#घोषणा BUS_ERROR_LPQTO		0x0000000000000100UL /* Safari */
#घोषणा BUS_ERROR_JBUS_ILL_C	0x0000000000000100UL /* Tomatillo */
#घोषणा BUS_ERROR_SFPQTO	0x0000000000000080UL /* Safari */
#घोषणा BUS_ERROR_UFPQTO	0x0000000000000040UL /* Safari */
#घोषणा BUS_ERROR_RD_PERR	0x0000000000000040UL /* Tomatillo */
#घोषणा BUS_ERROR_APERR		0x0000000000000020UL /* Safari/Tomatillo */
#घोषणा BUS_ERROR_UNMAP		0x0000000000000010UL /* Safari/Tomatillo */
#घोषणा BUS_ERROR_BUSERR	0x0000000000000004UL /* Safari/Tomatillo */
#घोषणा BUS_ERROR_TIMEOUT	0x0000000000000002UL /* Safari/Tomatillo */
#घोषणा BUS_ERROR_ILL		0x0000000000000001UL /* Safari */

/* We only expect UNMAP errors here.  The rest of the Safari errors
 * are marked fatal and thus cause a प्रणाली reset.
 */
अटल irqवापस_t schizo_safarierr_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pci_pbm_info *pbm = dev_id;
	u64 errlog;

	errlog = upa_पढ़ोq(pbm->controller_regs + SCHIZO_SAFARI_ERRLOG);
	upa_ग_लिखोq(errlog & ~(SAFARI_ERRLOG_ERROUT),
		   pbm->controller_regs + SCHIZO_SAFARI_ERRLOG);

	अगर (!(errlog & BUS_ERROR_UNMAP)) अणु
		prपूर्णांकk("%s: Unexpected Safari/JBUS error interrupt, errlog[%016llx]\n",
		       pbm->name, errlog);

		वापस IRQ_HANDLED;
	पूर्ण

	prपूर्णांकk("%s: Safari/JBUS interrupt, UNMAPPED error, interrogating IOMMUs.\n",
	       pbm->name);
	schizo_check_iommu_error(pbm, SAFARI_ERR);

	वापस IRQ_HANDLED;
पूर्ण

/* Nearly identical to PSYCHO equivalents... */
#घोषणा SCHIZO_ECC_CTRL		0x10020UL
#घोषणा  SCHIZO_ECCCTRL_EE	 0x8000000000000000UL /* Enable ECC Checking */
#घोषणा  SCHIZO_ECCCTRL_UE	 0x4000000000000000UL /* Enable UE Interrupts */
#घोषणा  SCHIZO_ECCCTRL_CE	 0x2000000000000000UL /* Enable CE INterrupts */

#घोषणा SCHIZO_SAFARI_ERRCTRL	0x10008UL
#घोषणा  SCHIZO_SAFERRCTRL_EN	 0x8000000000000000UL
#घोषणा SCHIZO_SAFARI_IRQCTRL	0x10010UL
#घोषणा  SCHIZO_SAFIRQCTRL_EN	 0x8000000000000000UL

अटल पूर्णांक pbm_routes_this_ino(काष्ठा pci_pbm_info *pbm, u32 ino)
अणु
	ino &= IMAP_INO;

	अगर (pbm->ino_biपंचांगap & (1UL << ino))
		वापस 1;

	वापस 0;
पूर्ण

/* How the Tomatillo IRQs are routed around is pure guesswork here.
 *
 * All the Tomatillo devices I see in prtconf dumps seem to have only
 * a single PCI bus unit attached to it.  It would seem they are separate
 * devices because their PortID (ie. JBUS ID) values are all dअगरferent
 * and thus the रेजिस्टरs are mapped to totally dअगरferent locations.
 *
 * However, two Tomatillo's look "similar" in that the only dअगरference
 * in their PortID is the lowest bit.
 *
 * So अगर we were to ignore this lower bit, it certainly looks like two
 * PCI bus units of the same Tomatillo.  I still have not really
 * figured this out...
 */
अटल व्योम tomatillo_रेजिस्टर_error_handlers(काष्ठा pci_pbm_info *pbm)
अणु
	काष्ठा platक्रमm_device *op = of_find_device_by_node(pbm->op->dev.of_node);
	u64 पंचांगp, err_mask, err_no_mask;
	पूर्णांक err;

	/* Tomatillo IRQ property layout is:
	 * 0: PCIERR
	 * 1: UE ERR
	 * 2: CE ERR
	 * 3: SERR
	 * 4: POWER FAIL?
	 */

	अगर (pbm_routes_this_ino(pbm, SCHIZO_UE_INO)) अणु
		err = request_irq(op->archdata.irqs[1], schizo_ue_पूर्णांकr, 0,
				  "TOMATILLO_UE", pbm);
		अगर (err)
			prपूर्णांकk(KERN_WARNING "%s: Could not register UE, "
			       "err=%d\n", pbm->name, err);
	पूर्ण
	अगर (pbm_routes_this_ino(pbm, SCHIZO_CE_INO)) अणु
		err = request_irq(op->archdata.irqs[2], schizo_ce_पूर्णांकr, 0,
				  "TOMATILLO_CE", pbm);
		अगर (err)
			prपूर्णांकk(KERN_WARNING "%s: Could not register CE, "
			       "err=%d\n", pbm->name, err);
	पूर्ण
	err = 0;
	अगर (pbm_routes_this_ino(pbm, SCHIZO_PCIERR_A_INO)) अणु
		err = request_irq(op->archdata.irqs[0], schizo_pcierr_पूर्णांकr, 0,
				  "TOMATILLO_PCIERR", pbm);
	पूर्ण अन्यथा अगर (pbm_routes_this_ino(pbm, SCHIZO_PCIERR_B_INO)) अणु
		err = request_irq(op->archdata.irqs[0], schizo_pcierr_पूर्णांकr, 0,
				  "TOMATILLO_PCIERR", pbm);
	पूर्ण
	अगर (err)
		prपूर्णांकk(KERN_WARNING "%s: Could not register PCIERR, "
		       "err=%d\n", pbm->name, err);

	अगर (pbm_routes_this_ino(pbm, SCHIZO_SERR_INO)) अणु
		err = request_irq(op->archdata.irqs[3], schizo_safarierr_पूर्णांकr, 0,
				  "TOMATILLO_SERR", pbm);
		अगर (err)
			prपूर्णांकk(KERN_WARNING "%s: Could not register SERR, "
			       "err=%d\n", pbm->name, err);
	पूर्ण

	/* Enable UE and CE पूर्णांकerrupts क्रम controller. */
	upa_ग_लिखोq((SCHIZO_ECCCTRL_EE |
		    SCHIZO_ECCCTRL_UE |
		    SCHIZO_ECCCTRL_CE), pbm->controller_regs + SCHIZO_ECC_CTRL);

	/* Enable PCI Error पूर्णांकerrupts and clear error
	 * bits.
	 */
	err_mask = (SCHIZO_PCICTRL_BUS_UNUS |
		    SCHIZO_PCICTRL_TTO_ERR |
		    SCHIZO_PCICTRL_RTRY_ERR |
		    SCHIZO_PCICTRL_SERR |
		    SCHIZO_PCICTRL_EEN);

	err_no_mask = SCHIZO_PCICTRL_DTO_ERR;

	पंचांगp = upa_पढ़ोq(pbm->pbm_regs + SCHIZO_PCI_CTRL);
	पंचांगp |= err_mask;
	पंचांगp &= ~err_no_mask;
	upa_ग_लिखोq(पंचांगp, pbm->pbm_regs + SCHIZO_PCI_CTRL);

	err_mask = (SCHIZO_PCIAFSR_PMA | SCHIZO_PCIAFSR_PTA |
		    SCHIZO_PCIAFSR_PRTRY | SCHIZO_PCIAFSR_PPERR |
		    SCHIZO_PCIAFSR_PTTO |
		    SCHIZO_PCIAFSR_SMA | SCHIZO_PCIAFSR_STA |
		    SCHIZO_PCIAFSR_SRTRY | SCHIZO_PCIAFSR_SPERR |
		    SCHIZO_PCIAFSR_STTO);

	upa_ग_लिखोq(err_mask, pbm->pbm_regs + SCHIZO_PCI_AFSR);

	err_mask = (BUS_ERROR_BADCMD | BUS_ERROR_SNOOP_GR |
		    BUS_ERROR_SNOOP_PCI | BUS_ERROR_SNOOP_RD |
		    BUS_ERROR_SNOOP_RDS | BUS_ERROR_SNOOP_RDSA |
		    BUS_ERROR_SNOOP_OWN | BUS_ERROR_SNOOP_RDO |
		    BUS_ERROR_WDATA_PERR | BUS_ERROR_CTRL_PERR |
		    BUS_ERROR_SNOOP_ERR | BUS_ERROR_JBUS_ILL_B |
		    BUS_ERROR_JBUS_ILL_C | BUS_ERROR_RD_PERR |
		    BUS_ERROR_APERR | BUS_ERROR_UNMAP |
		    BUS_ERROR_BUSERR | BUS_ERROR_TIMEOUT);

	upa_ग_लिखोq((SCHIZO_SAFERRCTRL_EN | err_mask),
		   pbm->controller_regs + SCHIZO_SAFARI_ERRCTRL);

	upa_ग_लिखोq((SCHIZO_SAFIRQCTRL_EN | (BUS_ERROR_UNMAP)),
		   pbm->controller_regs + SCHIZO_SAFARI_IRQCTRL);
पूर्ण

अटल व्योम schizo_रेजिस्टर_error_handlers(काष्ठा pci_pbm_info *pbm)
अणु
	काष्ठा platक्रमm_device *op = of_find_device_by_node(pbm->op->dev.of_node);
	u64 पंचांगp, err_mask, err_no_mask;
	पूर्णांक err;

	/* Schizo IRQ property layout is:
	 * 0: PCIERR
	 * 1: UE ERR
	 * 2: CE ERR
	 * 3: SERR
	 * 4: POWER FAIL?
	 */

	अगर (pbm_routes_this_ino(pbm, SCHIZO_UE_INO)) अणु
		err = request_irq(op->archdata.irqs[1], schizo_ue_पूर्णांकr, 0,
				  "SCHIZO_UE", pbm);
		अगर (err)
			prपूर्णांकk(KERN_WARNING "%s: Could not register UE, "
			       "err=%d\n", pbm->name, err);
	पूर्ण
	अगर (pbm_routes_this_ino(pbm, SCHIZO_CE_INO)) अणु
		err = request_irq(op->archdata.irqs[2], schizo_ce_पूर्णांकr, 0,
				  "SCHIZO_CE", pbm);
		अगर (err)
			prपूर्णांकk(KERN_WARNING "%s: Could not register CE, "
			       "err=%d\n", pbm->name, err);
	पूर्ण
	err = 0;
	अगर (pbm_routes_this_ino(pbm, SCHIZO_PCIERR_A_INO)) अणु
		err = request_irq(op->archdata.irqs[0], schizo_pcierr_पूर्णांकr, 0,
				  "SCHIZO_PCIERR", pbm);
	पूर्ण अन्यथा अगर (pbm_routes_this_ino(pbm, SCHIZO_PCIERR_B_INO)) अणु
		err = request_irq(op->archdata.irqs[0], schizo_pcierr_पूर्णांकr, 0,
				  "SCHIZO_PCIERR", pbm);
	पूर्ण
	अगर (err)
		prपूर्णांकk(KERN_WARNING "%s: Could not register PCIERR, "
		       "err=%d\n", pbm->name, err);

	अगर (pbm_routes_this_ino(pbm, SCHIZO_SERR_INO)) अणु
		err = request_irq(op->archdata.irqs[3], schizo_safarierr_पूर्णांकr, 0,
				  "SCHIZO_SERR", pbm);
		अगर (err)
			prपूर्णांकk(KERN_WARNING "%s: Could not register SERR, "
			       "err=%d\n", pbm->name, err);
	पूर्ण

	/* Enable UE and CE पूर्णांकerrupts क्रम controller. */
	upa_ग_लिखोq((SCHIZO_ECCCTRL_EE |
		    SCHIZO_ECCCTRL_UE |
		    SCHIZO_ECCCTRL_CE), pbm->controller_regs + SCHIZO_ECC_CTRL);

	err_mask = (SCHIZO_PCICTRL_BUS_UNUS |
		    SCHIZO_PCICTRL_ESLCK |
		    SCHIZO_PCICTRL_TTO_ERR |
		    SCHIZO_PCICTRL_RTRY_ERR |
		    SCHIZO_PCICTRL_SBH_ERR |
		    SCHIZO_PCICTRL_SERR |
		    SCHIZO_PCICTRL_EEN);

	err_no_mask = (SCHIZO_PCICTRL_DTO_ERR |
		       SCHIZO_PCICTRL_SBH_INT);

	/* Enable PCI Error पूर्णांकerrupts and clear error
	 * bits क्रम each PBM.
	 */
	पंचांगp = upa_पढ़ोq(pbm->pbm_regs + SCHIZO_PCI_CTRL);
	पंचांगp |= err_mask;
	पंचांगp &= ~err_no_mask;
	upa_ग_लिखोq(पंचांगp, pbm->pbm_regs + SCHIZO_PCI_CTRL);

	upa_ग_लिखोq((SCHIZO_PCIAFSR_PMA | SCHIZO_PCIAFSR_PTA |
		    SCHIZO_PCIAFSR_PRTRY | SCHIZO_PCIAFSR_PPERR |
		    SCHIZO_PCIAFSR_PTTO | SCHIZO_PCIAFSR_PUNUS |
		    SCHIZO_PCIAFSR_SMA | SCHIZO_PCIAFSR_STA |
		    SCHIZO_PCIAFSR_SRTRY | SCHIZO_PCIAFSR_SPERR |
		    SCHIZO_PCIAFSR_STTO | SCHIZO_PCIAFSR_SUNUS),
		   pbm->pbm_regs + SCHIZO_PCI_AFSR);

	/* Make all Safari error conditions fatal except unmapped
	 * errors which we make generate पूर्णांकerrupts.
	 */
	err_mask = (BUS_ERROR_BADCMD | BUS_ERROR_SSMDIS |
		    BUS_ERROR_BADMA | BUS_ERROR_BADMB |
		    BUS_ERROR_BADMC |
		    BUS_ERROR_CPU1PS | BUS_ERROR_CPU1PB |
		    BUS_ERROR_CPU0PS | BUS_ERROR_CPU0PB |
		    BUS_ERROR_CIQTO |
		    BUS_ERROR_LPQTO | BUS_ERROR_SFPQTO |
		    BUS_ERROR_UFPQTO | BUS_ERROR_APERR |
		    BUS_ERROR_BUSERR | BUS_ERROR_TIMEOUT |
		    BUS_ERROR_ILL);
#अगर 1
	/* XXX Something wrong with some Excalibur प्रणालीs
	 * XXX Sun is shipping.  The behavior on a 2-cpu
	 * XXX machine is that both CPU1 parity error bits
	 * XXX are set and are immediately set again when
	 * XXX their error status bits are cleared.  Just
	 * XXX ignore them क्रम now.  -DaveM
	 */
	err_mask &= ~(BUS_ERROR_CPU1PS | BUS_ERROR_CPU1PB |
		      BUS_ERROR_CPU0PS | BUS_ERROR_CPU0PB);
#पूर्ण_अगर

	upa_ग_लिखोq((SCHIZO_SAFERRCTRL_EN | err_mask),
		   pbm->controller_regs + SCHIZO_SAFARI_ERRCTRL);
पूर्ण

अटल व्योम pbm_config_busmastering(काष्ठा pci_pbm_info *pbm)
अणु
	u8 *addr;

	/* Set cache-line size to 64 bytes, this is actually
	 * a nop but I करो it क्रम completeness.
	 */
	addr = schizo_pci_config_mkaddr(pbm, pbm->pci_first_busno,
					0, PCI_CACHE_LINE_SIZE);
	pci_config_ग_लिखो8(addr, 64 / माप(u32));

	/* Set PBM latency समयr to 64 PCI घड़ीs. */
	addr = schizo_pci_config_mkaddr(pbm, pbm->pci_first_busno,
					0, PCI_LATENCY_TIMER);
	pci_config_ग_लिखो8(addr, 64);
पूर्ण

अटल व्योम schizo_scan_bus(काष्ठा pci_pbm_info *pbm, काष्ठा device *parent)
अणु
	pbm_config_busmastering(pbm);
	pbm->is_66mhz_capable =
		(of_find_property(pbm->op->dev.of_node, "66mhz-capable", शून्य)
		 != शून्य);

	pbm->pci_bus = pci_scan_one_pbm(pbm, parent);

	अगर (pbm->chip_type == PBM_CHIP_TYPE_TOMATILLO)
		tomatillo_रेजिस्टर_error_handlers(pbm);
	अन्यथा
		schizo_रेजिस्टर_error_handlers(pbm);
पूर्ण

#घोषणा SCHIZO_STRBUF_CONTROL		(0x02800UL)
#घोषणा SCHIZO_STRBUF_FLUSH		(0x02808UL)
#घोषणा SCHIZO_STRBUF_FSYNC		(0x02810UL)
#घोषणा SCHIZO_STRBUF_CTXFLUSH		(0x02818UL)
#घोषणा SCHIZO_STRBUF_CTXMATCH		(0x10000UL)

अटल व्योम schizo_pbm_strbuf_init(काष्ठा pci_pbm_info *pbm)
अणु
	अचिन्हित दीर्घ base = pbm->pbm_regs;
	u64 control;

	अगर (pbm->chip_type == PBM_CHIP_TYPE_TOMATILLO) अणु
		/* TOMATILLO lacks streaming cache.  */
		वापस;
	पूर्ण

	/* SCHIZO has context flushing. */
	pbm->stc.strbuf_control		= base + SCHIZO_STRBUF_CONTROL;
	pbm->stc.strbuf_pflush		= base + SCHIZO_STRBUF_FLUSH;
	pbm->stc.strbuf_fsync		= base + SCHIZO_STRBUF_FSYNC;
	pbm->stc.strbuf_ctxflush	= base + SCHIZO_STRBUF_CTXFLUSH;
	pbm->stc.strbuf_ctxmatch_base	= base + SCHIZO_STRBUF_CTXMATCH;

	pbm->stc.strbuf_flushflag = (अस्थिर अचिन्हित दीर्घ *)
		((((अचिन्हित दीर्घ)&pbm->stc.__flushflag_buf[0])
		  + 63UL)
		 & ~63UL);
	pbm->stc.strbuf_flushflag_pa = (अचिन्हित दीर्घ)
		__pa(pbm->stc.strbuf_flushflag);

	/* Turn off LRU locking and diag mode, enable the
	 * streaming buffer and leave the rerun-disable
	 * setting however OBP set it.
	 */
	control = upa_पढ़ोq(pbm->stc.strbuf_control);
	control &= ~(SCHIZO_STRBUF_CTRL_LPTR |
		     SCHIZO_STRBUF_CTRL_LENAB |
		     SCHIZO_STRBUF_CTRL_DENAB);
	control |= SCHIZO_STRBUF_CTRL_ENAB;
	upa_ग_लिखोq(control, pbm->stc.strbuf_control);

	pbm->stc.strbuf_enabled = 1;
पूर्ण

#घोषणा SCHIZO_IOMMU_CONTROL		(0x00200UL)
#घोषणा SCHIZO_IOMMU_TSBBASE		(0x00208UL)
#घोषणा SCHIZO_IOMMU_FLUSH		(0x00210UL)
#घोषणा SCHIZO_IOMMU_CTXFLUSH		(0x00218UL)

अटल पूर्णांक schizo_pbm_iommu_init(काष्ठा pci_pbm_info *pbm)
अणु
	अटल स्थिर u32 vdma_शेष[] = अणु 0xc0000000, 0x40000000 पूर्ण;
	अचिन्हित दीर्घ i, tagbase, database;
	काष्ठा iommu *iommu = pbm->iommu;
	पूर्णांक tsbsize, err;
	स्थिर u32 *vdma;
	u32 dma_mask;
	u64 control;

	vdma = of_get_property(pbm->op->dev.of_node, "virtual-dma", शून्य);
	अगर (!vdma)
		vdma = vdma_शेष;

	dma_mask = vdma[0];
	चयन (vdma[1]) अणु
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
			वापस -EINVAL;
	पूर्ण

	/* Register addresses, SCHIZO has iommu ctx flushing. */
	iommu->iommu_control  = pbm->pbm_regs + SCHIZO_IOMMU_CONTROL;
	iommu->iommu_tsbbase  = pbm->pbm_regs + SCHIZO_IOMMU_TSBBASE;
	iommu->iommu_flush    = pbm->pbm_regs + SCHIZO_IOMMU_FLUSH;
	iommu->iommu_tags     = iommu->iommu_flush + (0xa580UL - 0x0210UL);
	iommu->iommu_ctxflush = pbm->pbm_regs + SCHIZO_IOMMU_CTXFLUSH;

	/* We use the मुख्य control/status रेजिस्टर of SCHIZO as the ग_लिखो
	 * completion रेजिस्टर.
	 */
	iommu->ग_लिखो_complete_reg = pbm->controller_regs + 0x10000UL;

	/*
	 * Invalidate TLB Entries.
	 */
	control = upa_पढ़ोq(iommu->iommu_control);
	control |= SCHIZO_IOMMU_CTRL_DENAB;
	upa_ग_लिखोq(control, iommu->iommu_control);

	tagbase = SCHIZO_IOMMU_TAG, database = SCHIZO_IOMMU_DATA;

	क्रम (i = 0; i < 16; i++) अणु
		upa_ग_लिखोq(0, pbm->pbm_regs + tagbase + (i * 8UL));
		upa_ग_लिखोq(0, pbm->pbm_regs + database + (i * 8UL));
	पूर्ण

	/* Leave diag mode enabled क्रम full-flushing करोne
	 * in pci_iommu.c
	 */
	err = iommu_table_init(iommu, tsbsize * 8 * 1024, vdma[0], dma_mask,
			       pbm->numa_node);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR PFX "iommu_table_init() fails with %d\n", err);
		वापस err;
	पूर्ण

	upa_ग_लिखोq(__pa(iommu->page_table), iommu->iommu_tsbbase);

	control = upa_पढ़ोq(iommu->iommu_control);
	control &= ~(SCHIZO_IOMMU_CTRL_TSBSZ | SCHIZO_IOMMU_CTRL_TBWSZ);
	चयन (tsbsize) अणु
	हाल 64:
		control |= SCHIZO_IOMMU_TSBSZ_64K;
		अवरोध;
	हाल 128:
		control |= SCHIZO_IOMMU_TSBSZ_128K;
		अवरोध;
	पूर्ण

	control |= SCHIZO_IOMMU_CTRL_ENAB;
	upa_ग_लिखोq(control, iommu->iommu_control);

	वापस 0;
पूर्ण

#घोषणा SCHIZO_PCI_IRQ_RETRY	(0x1a00UL)
#घोषणा  SCHIZO_IRQ_RETRY_INF	 0xffUL

#घोषणा SCHIZO_PCI_DIAG			(0x2020UL)
#घोषणा  SCHIZO_PCIDIAG_D_BADECC	(1UL << 10UL) /* Disable BAD ECC errors (Schizo) */
#घोषणा  SCHIZO_PCIDIAG_D_BYPASS	(1UL <<  9UL) /* Disable MMU bypass mode (Schizo/Tomatillo) */
#घोषणा  SCHIZO_PCIDIAG_D_TTO		(1UL <<  8UL) /* Disable TTO errors (Schizo/Tomatillo) */
#घोषणा  SCHIZO_PCIDIAG_D_RTRYARB	(1UL <<  7UL) /* Disable retry arbitration (Schizo) */
#घोषणा  SCHIZO_PCIDIAG_D_RETRY		(1UL <<  6UL) /* Disable retry limit (Schizo/Tomatillo) */
#घोषणा  SCHIZO_PCIDIAG_D_INTSYNC	(1UL <<  5UL) /* Disable पूर्णांकerrupt/DMA synch (Schizo/Tomatillo) */
#घोषणा  SCHIZO_PCIDIAG_I_DMA_PARITY	(1UL <<  3UL) /* Invert DMA parity (Schizo/Tomatillo) */
#घोषणा  SCHIZO_PCIDIAG_I_PIOD_PARITY	(1UL <<  2UL) /* Invert PIO data parity (Schizo/Tomatillo) */
#घोषणा  SCHIZO_PCIDIAG_I_PIOA_PARITY	(1UL <<  1UL) /* Invert PIO address parity (Schizo/Tomatillo) */

#घोषणा TOMATILLO_PCI_IOC_CSR		(0x2248UL)
#घोषणा TOMATILLO_IOC_PART_WPENAB	0x0000000000080000UL
#घोषणा TOMATILLO_IOC_RDMULT_PENAB	0x0000000000040000UL
#घोषणा TOMATILLO_IOC_RDONE_PENAB	0x0000000000020000UL
#घोषणा TOMATILLO_IOC_RDLINE_PENAB	0x0000000000010000UL
#घोषणा TOMATILLO_IOC_RDMULT_PLEN	0x000000000000c000UL
#घोषणा TOMATILLO_IOC_RDMULT_PLEN_SHIFT	14UL
#घोषणा TOMATILLO_IOC_RDONE_PLEN	0x0000000000003000UL
#घोषणा TOMATILLO_IOC_RDONE_PLEN_SHIFT	12UL
#घोषणा TOMATILLO_IOC_RDLINE_PLEN	0x0000000000000c00UL
#घोषणा TOMATILLO_IOC_RDLINE_PLEN_SHIFT	10UL
#घोषणा TOMATILLO_IOC_PREF_OFF		0x00000000000003f8UL
#घोषणा TOMATILLO_IOC_PREF_OFF_SHIFT	3UL
#घोषणा TOMATILLO_IOC_RDMULT_CPENAB	0x0000000000000004UL
#घोषणा TOMATILLO_IOC_RDONE_CPENAB	0x0000000000000002UL
#घोषणा TOMATILLO_IOC_RDLINE_CPENAB	0x0000000000000001UL

#घोषणा TOMATILLO_PCI_IOC_TDIAG		(0x2250UL)
#घोषणा TOMATILLO_PCI_IOC_DDIAG		(0x2290UL)

अटल व्योम schizo_pbm_hw_init(काष्ठा pci_pbm_info *pbm)
अणु
	u64 पंचांगp;

	upa_ग_लिखोq(5, pbm->pbm_regs + SCHIZO_PCI_IRQ_RETRY);

	पंचांगp = upa_पढ़ोq(pbm->pbm_regs + SCHIZO_PCI_CTRL);

	/* Enable arbiter क्रम all PCI slots.  */
	पंचांगp |= 0xff;

	अगर (pbm->chip_type == PBM_CHIP_TYPE_TOMATILLO &&
	    pbm->chip_version >= 0x2)
		पंचांगp |= 0x3UL << SCHIZO_PCICTRL_PTO_SHIFT;

	अगर (!of_find_property(pbm->op->dev.of_node, "no-bus-parking", शून्य))
		पंचांगp |= SCHIZO_PCICTRL_PARK;
	अन्यथा
		पंचांगp &= ~SCHIZO_PCICTRL_PARK;

	अगर (pbm->chip_type == PBM_CHIP_TYPE_TOMATILLO &&
	    pbm->chip_version <= 0x1)
		पंचांगp |= SCHIZO_PCICTRL_DTO_INT;
	अन्यथा
		पंचांगp &= ~SCHIZO_PCICTRL_DTO_INT;

	अगर (pbm->chip_type == PBM_CHIP_TYPE_TOMATILLO)
		पंचांगp |= (SCHIZO_PCICTRL_MRM_PREF |
			SCHIZO_PCICTRL_RDO_PREF |
			SCHIZO_PCICTRL_RDL_PREF);

	upa_ग_लिखोq(पंचांगp, pbm->pbm_regs + SCHIZO_PCI_CTRL);

	पंचांगp = upa_पढ़ोq(pbm->pbm_regs + SCHIZO_PCI_DIAG);
	पंचांगp &= ~(SCHIZO_PCIDIAG_D_RTRYARB |
		 SCHIZO_PCIDIAG_D_RETRY |
		 SCHIZO_PCIDIAG_D_INTSYNC);
	upa_ग_लिखोq(पंचांगp, pbm->pbm_regs + SCHIZO_PCI_DIAG);

	अगर (pbm->chip_type == PBM_CHIP_TYPE_TOMATILLO) अणु
		/* Clear prefetch lengths to workaround a bug in
		 * Jalapeno...
		 */
		पंचांगp = (TOMATILLO_IOC_PART_WPENAB |
		       (1 << TOMATILLO_IOC_PREF_OFF_SHIFT) |
		       TOMATILLO_IOC_RDMULT_CPENAB |
		       TOMATILLO_IOC_RDONE_CPENAB |
		       TOMATILLO_IOC_RDLINE_CPENAB);

		upa_ग_लिखोq(पंचांगp, pbm->pbm_regs + TOMATILLO_PCI_IOC_CSR);
	पूर्ण
पूर्ण

अटल पूर्णांक schizo_pbm_init(काष्ठा pci_pbm_info *pbm,
			   काष्ठा platक्रमm_device *op, u32 portid,
			   पूर्णांक chip_type)
अणु
	स्थिर काष्ठा linux_prom64_रेजिस्टरs *regs;
	काष्ठा device_node *dp = op->dev.of_node;
	स्थिर अक्षर *chipset_name;
	पूर्णांक err;

	चयन (chip_type) अणु
	हाल PBM_CHIP_TYPE_TOMATILLO:
		chipset_name = "TOMATILLO";
		अवरोध;

	हाल PBM_CHIP_TYPE_SCHIZO_PLUS:
		chipset_name = "SCHIZO+";
		अवरोध;

	हाल PBM_CHIP_TYPE_SCHIZO:
	शेष:
		chipset_name = "SCHIZO";
		अवरोध;
	पूर्ण

	/* For SCHIZO, three OBP regs:
	 * 1) PBM controller regs
	 * 2) Schizo front-end controller regs (same क्रम both PBMs)
	 * 3) PBM PCI config space
	 *
	 * For TOMATILLO, four OBP regs:
	 * 1) PBM controller regs
	 * 2) Tomatillo front-end controller regs
	 * 3) PBM PCI config space
	 * 4) Ichip regs
	 */
	regs = of_get_property(dp, "reg", शून्य);

	pbm->next = pci_pbm_root;
	pci_pbm_root = pbm;

	pbm->numa_node = NUMA_NO_NODE;

	pbm->pci_ops = &sun4u_pci_ops;
	pbm->config_space_reg_bits = 8;

	pbm->index = pci_num_pbms++;

	pbm->portid = portid;
	pbm->op = op;

	pbm->chip_type = chip_type;
	pbm->chip_version = of_getपूर्णांकprop_शेष(dp, "version#", 0);
	pbm->chip_revision = of_getपूर्णांकprop_शेष(dp, "module-version#", 0);

	pbm->pbm_regs = regs[0].phys_addr;
	pbm->controller_regs = regs[1].phys_addr - 0x10000UL;

	अगर (chip_type == PBM_CHIP_TYPE_TOMATILLO)
		pbm->sync_reg = regs[3].phys_addr + 0x1a18UL;

	pbm->name = dp->full_name;

	prपूर्णांकk("%s: %s PCI Bus Module ver[%x:%x]\n",
	       pbm->name, chipset_name,
	       pbm->chip_version, pbm->chip_revision);

	schizo_pbm_hw_init(pbm);

	pci_determine_mem_io_space(pbm);

	pci_get_pbm_props(pbm);

	err = schizo_pbm_iommu_init(pbm);
	अगर (err)
		वापस err;

	schizo_pbm_strbuf_init(pbm);

	schizo_scan_bus(pbm, &op->dev);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक portid_compare(u32 x, u32 y, पूर्णांक chip_type)
अणु
	अगर (chip_type == PBM_CHIP_TYPE_TOMATILLO) अणु
		अगर (x == (y ^ 1))
			वापस 1;
		वापस 0;
	पूर्ण
	वापस (x == y);
पूर्ण

अटल काष्ठा pci_pbm_info *schizo_find_sibling(u32 portid, पूर्णांक chip_type)
अणु
	काष्ठा pci_pbm_info *pbm;

	क्रम (pbm = pci_pbm_root; pbm; pbm = pbm->next) अणु
		अगर (portid_compare(pbm->portid, portid, chip_type))
			वापस pbm;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक __schizo_init(काष्ठा platक्रमm_device *op, अचिन्हित दीर्घ chip_type)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा pci_pbm_info *pbm;
	काष्ठा iommu *iommu;
	u32 portid;
	पूर्णांक err;

	portid = of_getपूर्णांकprop_शेष(dp, "portid", 0xff);

	err = -ENOMEM;
	pbm = kzalloc(माप(*pbm), GFP_KERNEL);
	अगर (!pbm) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot allocate pci_pbm_info.\n");
		जाओ out_err;
	पूर्ण

	pbm->sibling = schizo_find_sibling(portid, chip_type);

	iommu = kzalloc(माप(काष्ठा iommu), GFP_KERNEL);
	अगर (!iommu) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot allocate PBM A iommu.\n");
		जाओ out_मुक्त_pbm;
	पूर्ण

	pbm->iommu = iommu;

	अगर (schizo_pbm_init(pbm, op, portid, chip_type))
		जाओ out_मुक्त_iommu;

	अगर (pbm->sibling)
		pbm->sibling->sibling = pbm;

	dev_set_drvdata(&op->dev, pbm);

	वापस 0;

out_मुक्त_iommu:
	kमुक्त(pbm->iommu);

out_मुक्त_pbm:
	kमुक्त(pbm);

out_err:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id schizo_match[];
अटल पूर्णांक schizo_probe(काष्ठा platक्रमm_device *op)
अणु
	स्थिर काष्ठा of_device_id *match;

	match = of_match_device(schizo_match, &op->dev);
	अगर (!match)
		वापस -EINVAL;
	वापस __schizo_init(op, (अचिन्हित दीर्घ)match->data);
पूर्ण

/* The ordering of this table is very important.  Some Tomatillo
 * nodes announce that they are compatible with both pci108e,a801
 * and pci108e,8001.  So list the chips in reverse chronological
 * order.
 */
अटल स्थिर काष्ठा of_device_id schizo_match[] = अणु
	अणु
		.name = "pci",
		.compatible = "pci108e,a801",
		.data = (व्योम *) PBM_CHIP_TYPE_TOMATILLO,
	पूर्ण,
	अणु
		.name = "pci",
		.compatible = "pci108e,8002",
		.data = (व्योम *) PBM_CHIP_TYPE_SCHIZO_PLUS,
	पूर्ण,
	अणु
		.name = "pci",
		.compatible = "pci108e,8001",
		.data = (व्योम *) PBM_CHIP_TYPE_SCHIZO,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver schizo_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = schizo_match,
	पूर्ण,
	.probe		= schizo_probe,
पूर्ण;

अटल पूर्णांक __init schizo_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&schizo_driver);
पूर्ण

subsys_initcall(schizo_init);
