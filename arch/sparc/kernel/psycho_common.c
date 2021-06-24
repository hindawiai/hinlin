<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* psycho_common.c: Code common to PSYCHO and derivative PCI controllers.
 *
 * Copyright (C) 2008 David S. Miller <davem@davemloft.net>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/numa.h>

#समावेश <यंत्र/upa.h>

#समावेश "pci_impl.h"
#समावेश "iommu_common.h"
#समावेश "psycho_common.h"

#घोषणा  PSYCHO_STRBUF_CTRL_DENAB	0x0000000000000002ULL
#घोषणा  PSYCHO_STCERR_WRITE		0x0000000000000002ULL
#घोषणा  PSYCHO_STCERR_READ		0x0000000000000001ULL
#घोषणा  PSYCHO_STCTAG_PPN		0x0fffffff00000000ULL
#घोषणा  PSYCHO_STCTAG_VPN		0x00000000ffffe000ULL
#घोषणा  PSYCHO_STCTAG_VALID		0x0000000000000002ULL
#घोषणा  PSYCHO_STCTAG_WRITE		0x0000000000000001ULL
#घोषणा  PSYCHO_STCLINE_LINDX		0x0000000001e00000ULL
#घोषणा  PSYCHO_STCLINE_SPTR		0x00000000001f8000ULL
#घोषणा  PSYCHO_STCLINE_LADDR		0x0000000000007f00ULL
#घोषणा  PSYCHO_STCLINE_EPTR		0x00000000000000fcULL
#घोषणा  PSYCHO_STCLINE_VALID		0x0000000000000002ULL
#घोषणा  PSYCHO_STCLINE_FOFN		0x0000000000000001ULL

अटल DEFINE_SPINLOCK(stc_buf_lock);
अटल अचिन्हित दीर्घ stc_error_buf[128];
अटल अचिन्हित दीर्घ stc_tag_buf[16];
अटल अचिन्हित दीर्घ stc_line_buf[16];

अटल व्योम psycho_check_stc_error(काष्ठा pci_pbm_info *pbm)
अणु
	अचिन्हित दीर्घ err_base, tag_base, line_base;
	काष्ठा strbuf *strbuf = &pbm->stc;
	u64 control;
	पूर्णांक i;

	अगर (!strbuf->strbuf_control)
		वापस;

	err_base = strbuf->strbuf_err_stat;
	tag_base = strbuf->strbuf_tag_diag;
	line_base = strbuf->strbuf_line_diag;

	spin_lock(&stc_buf_lock);

	/* This is __REALLY__ dangerous.  When we put the streaming
	 * buffer पूर्णांकo diagnostic mode to probe it's tags and error
	 * status, we _must_ clear all of the line tag valid bits
	 * beक्रमe re-enabling the streaming buffer.  If any dirty data
	 * lives in the STC when we करो this, we will end up
	 * invalidating it beक्रमe it has a chance to reach मुख्य
	 * memory.
	 */
	control = upa_पढ़ोq(strbuf->strbuf_control);
	upa_ग_लिखोq(control | PSYCHO_STRBUF_CTRL_DENAB, strbuf->strbuf_control);
	क्रम (i = 0; i < 128; i++) अणु
		u64 val;

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
			u64 errval = stc_error_buf[j];
			अगर (errval != 0) अणु
				saw_error++;
				prपूर्णांकk(KERN_ERR "%s: STC_ERR(%d)[wr(%d)"
				       "rd(%d)]\n",
				       pbm->name,
				       j,
				       (errval & PSYCHO_STCERR_WRITE) ? 1 : 0,
				       (errval & PSYCHO_STCERR_READ) ? 1 : 0);
			पूर्ण
		पूर्ण
		अगर (saw_error != 0) अणु
			u64 tagval = stc_tag_buf[i];
			u64 lineval = stc_line_buf[i];
			prपूर्णांकk(KERN_ERR "%s: STC_TAG(%d)[PA(%016llx)VA(%08llx)"
			       "V(%d)W(%d)]\n",
			       pbm->name,
			       i,
			       ((tagval & PSYCHO_STCTAG_PPN) >> 19UL),
			       (tagval & PSYCHO_STCTAG_VPN),
			       ((tagval & PSYCHO_STCTAG_VALID) ? 1 : 0),
			       ((tagval & PSYCHO_STCTAG_WRITE) ? 1 : 0));
			prपूर्णांकk(KERN_ERR "%s: STC_LINE(%d)[LIDX(%llx)SP(%llx)"
			       "LADDR(%llx)EP(%llx)V(%d)FOFN(%d)]\n",
			       pbm->name,
			       i,
			       ((lineval & PSYCHO_STCLINE_LINDX) >> 21UL),
			       ((lineval & PSYCHO_STCLINE_SPTR) >> 15UL),
			       ((lineval & PSYCHO_STCLINE_LADDR) >> 8UL),
			       ((lineval & PSYCHO_STCLINE_EPTR) >> 2UL),
			       ((lineval & PSYCHO_STCLINE_VALID) ? 1 : 0),
			       ((lineval & PSYCHO_STCLINE_FOFN) ? 1 : 0));
		पूर्ण
	पूर्ण

	spin_unlock(&stc_buf_lock);
पूर्ण

#घोषणा PSYCHO_IOMMU_TAG		0xa580UL
#घोषणा PSYCHO_IOMMU_DATA		0xa600UL

अटल व्योम psycho_record_iommu_tags_and_data(काष्ठा pci_pbm_info *pbm,
					      u64 *tag, u64 *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++) अणु
		अचिन्हित दीर्घ base = pbm->controller_regs;
		अचिन्हित दीर्घ off = i * 8UL;

		tag[i] = upa_पढ़ोq(base + PSYCHO_IOMMU_TAG+off);
		data[i] = upa_पढ़ोq(base + PSYCHO_IOMMU_DATA+off);

		/* Now clear out the entry. */
		upa_ग_लिखोq(0, base + PSYCHO_IOMMU_TAG + off);
		upa_ग_लिखोq(0, base + PSYCHO_IOMMU_DATA + off);
	पूर्ण
पूर्ण

#घोषणा  PSYCHO_IOMMU_TAG_ERRSTS (0x3UL << 23UL)
#घोषणा  PSYCHO_IOMMU_TAG_ERR	 (0x1UL << 22UL)
#घोषणा  PSYCHO_IOMMU_TAG_WRITE	 (0x1UL << 21UL)
#घोषणा  PSYCHO_IOMMU_TAG_STREAM (0x1UL << 20UL)
#घोषणा  PSYCHO_IOMMU_TAG_SIZE	 (0x1UL << 19UL)
#घोषणा  PSYCHO_IOMMU_TAG_VPAGE	 0x7ffffULL
#घोषणा  PSYCHO_IOMMU_DATA_VALID (1UL << 30UL)
#घोषणा  PSYCHO_IOMMU_DATA_CACHE (1UL << 28UL)
#घोषणा  PSYCHO_IOMMU_DATA_PPAGE 0xfffffffULL

अटल व्योम psycho_dump_iommu_tags_and_data(काष्ठा pci_pbm_info *pbm,
					    u64 *tag, u64 *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++) अणु
		u64 tag_val, data_val;
		स्थिर अक्षर *type_str;
		tag_val = tag[i];
		अगर (!(tag_val & PSYCHO_IOMMU_TAG_ERR))
			जारी;

		data_val = data[i];
		चयन((tag_val & PSYCHO_IOMMU_TAG_ERRSTS) >> 23UL) अणु
		हाल 0:
			type_str = "Protection Error";
			अवरोध;
		हाल 1:
			type_str = "Invalid Error";
			अवरोध;
		हाल 2:
			type_str = "TimeOut Error";
			अवरोध;
		हाल 3:
		शेष:
			type_str = "ECC Error";
			अवरोध;
		पूर्ण

		prपूर्णांकk(KERN_ERR "%s: IOMMU TAG(%d)[error(%s) wr(%d) "
		       "str(%d) sz(%dK) vpg(%08llx)]\n",
		       pbm->name, i, type_str,
		       ((tag_val & PSYCHO_IOMMU_TAG_WRITE) ? 1 : 0),
		       ((tag_val & PSYCHO_IOMMU_TAG_STREAM) ? 1 : 0),
		       ((tag_val & PSYCHO_IOMMU_TAG_SIZE) ? 64 : 8),
		       (tag_val & PSYCHO_IOMMU_TAG_VPAGE) << IOMMU_PAGE_SHIFT);
		prपूर्णांकk(KERN_ERR "%s: IOMMU DATA(%d)[valid(%d) cache(%d) "
		       "ppg(%016llx)]\n",
		       pbm->name, i,
		       ((data_val & PSYCHO_IOMMU_DATA_VALID) ? 1 : 0),
		       ((data_val & PSYCHO_IOMMU_DATA_CACHE) ? 1 : 0),
		       (data_val & PSYCHO_IOMMU_DATA_PPAGE) << IOMMU_PAGE_SHIFT);
	पूर्ण
पूर्ण

#घोषणा  PSYCHO_IOMMU_CTRL_XLTESTAT	0x0000000006000000UL
#घोषणा  PSYCHO_IOMMU_CTRL_XLTEERR	0x0000000001000000UL

व्योम psycho_check_iommu_error(काष्ठा pci_pbm_info *pbm,
			      अचिन्हित दीर्घ afsr,
			      अचिन्हित दीर्घ afar,
			      क्रमागत psycho_error_type type)
अणु
	u64 control, iommu_tag[16], iommu_data[16];
	काष्ठा iommu *iommu = pbm->iommu;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iommu->lock, flags);
	control = upa_पढ़ोq(iommu->iommu_control);
	अगर (control & PSYCHO_IOMMU_CTRL_XLTEERR) अणु
		स्थिर अक्षर *type_str;

		control &= ~PSYCHO_IOMMU_CTRL_XLTEERR;
		upa_ग_लिखोq(control, iommu->iommu_control);

		चयन ((control & PSYCHO_IOMMU_CTRL_XLTESTAT) >> 25UL) अणु
		हाल 0:
			type_str = "Protection Error";
			अवरोध;
		हाल 1:
			type_str = "Invalid Error";
			अवरोध;
		हाल 2:
			type_str = "TimeOut Error";
			अवरोध;
		हाल 3:
		शेष:
			type_str = "ECC Error";
			अवरोध;
		पूर्ण
		prपूर्णांकk(KERN_ERR "%s: IOMMU Error, type[%s]\n",
		       pbm->name, type_str);

		/* It is very possible क्रम another DVMA to occur जबतक
		 * we करो this probe, and corrupt the प्रणाली further.
		 * But we are so screwed at this poपूर्णांक that we are
		 * likely to crash hard anyways, so get as much
		 * diagnostic inक्रमmation to the console as we can.
		 */
		psycho_record_iommu_tags_and_data(pbm, iommu_tag, iommu_data);
		psycho_dump_iommu_tags_and_data(pbm, iommu_tag, iommu_data);
	पूर्ण
	psycho_check_stc_error(pbm);
	spin_unlock_irqrestore(&iommu->lock, flags);
पूर्ण

#घोषणा  PSYCHO_PCICTRL_SBH_ERR	 0x0000000800000000UL
#घोषणा  PSYCHO_PCICTRL_SERR	 0x0000000400000000UL

अटल irqवापस_t psycho_pcierr_पूर्णांकr_other(काष्ठा pci_pbm_info *pbm)
अणु
	irqवापस_t ret = IRQ_NONE;
	u64 csr, csr_error_bits;
	u16 stat, *addr;

	csr = upa_पढ़ोq(pbm->pci_csr);
	csr_error_bits = csr & (PSYCHO_PCICTRL_SBH_ERR | PSYCHO_PCICTRL_SERR);
	अगर (csr_error_bits) अणु
		/* Clear the errors.  */
		upa_ग_लिखोq(csr, pbm->pci_csr);

		/* Log 'em.  */
		अगर (csr_error_bits & PSYCHO_PCICTRL_SBH_ERR)
			prपूर्णांकk(KERN_ERR "%s: PCI streaming byte hole "
			       "error asserted.\n", pbm->name);
		अगर (csr_error_bits & PSYCHO_PCICTRL_SERR)
			prपूर्णांकk(KERN_ERR "%s: PCI SERR signal asserted.\n",
			       pbm->name);
		ret = IRQ_HANDLED;
	पूर्ण
	addr = psycho_pci_config_mkaddr(pbm, pbm->pci_first_busno,
					0, PCI_STATUS);
	pci_config_पढ़ो16(addr, &stat);
	अगर (stat & (PCI_STATUS_PARITY |
		    PCI_STATUS_SIG_TARGET_ABORT |
		    PCI_STATUS_REC_TARGET_ABORT |
		    PCI_STATUS_REC_MASTER_ABORT |
		    PCI_STATUS_SIG_SYSTEM_ERROR)) अणु
		prपूर्णांकk(KERN_ERR "%s: PCI bus error, PCI_STATUS[%04x]\n",
		       pbm->name, stat);
		pci_config_ग_लिखो16(addr, 0xffff);
		ret = IRQ_HANDLED;
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा  PSYCHO_PCIAFSR_PMA	0x8000000000000000ULL
#घोषणा  PSYCHO_PCIAFSR_PTA	0x4000000000000000ULL
#घोषणा  PSYCHO_PCIAFSR_PRTRY	0x2000000000000000ULL
#घोषणा  PSYCHO_PCIAFSR_PPERR	0x1000000000000000ULL
#घोषणा  PSYCHO_PCIAFSR_SMA	0x0800000000000000ULL
#घोषणा  PSYCHO_PCIAFSR_STA	0x0400000000000000ULL
#घोषणा  PSYCHO_PCIAFSR_SRTRY	0x0200000000000000ULL
#घोषणा  PSYCHO_PCIAFSR_SPERR	0x0100000000000000ULL
#घोषणा  PSYCHO_PCIAFSR_RESV1	0x00ff000000000000ULL
#घोषणा  PSYCHO_PCIAFSR_BMSK	0x0000ffff00000000ULL
#घोषणा  PSYCHO_PCIAFSR_BLK	0x0000000080000000ULL
#घोषणा  PSYCHO_PCIAFSR_RESV2	0x0000000040000000ULL
#घोषणा  PSYCHO_PCIAFSR_MID	0x000000003e000000ULL
#घोषणा  PSYCHO_PCIAFSR_RESV3	0x0000000001ffffffULL

irqवापस_t psycho_pcierr_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pci_pbm_info *pbm = dev_id;
	u64 afsr, afar, error_bits;
	पूर्णांक reported;

	afsr = upa_पढ़ोq(pbm->pci_afsr);
	afar = upa_पढ़ोq(pbm->pci_afar);
	error_bits = afsr &
		(PSYCHO_PCIAFSR_PMA | PSYCHO_PCIAFSR_PTA |
		 PSYCHO_PCIAFSR_PRTRY | PSYCHO_PCIAFSR_PPERR |
		 PSYCHO_PCIAFSR_SMA | PSYCHO_PCIAFSR_STA |
		 PSYCHO_PCIAFSR_SRTRY | PSYCHO_PCIAFSR_SPERR);
	अगर (!error_bits)
		वापस psycho_pcierr_पूर्णांकr_other(pbm);
	upa_ग_लिखोq(error_bits, pbm->pci_afsr);
	prपूर्णांकk(KERN_ERR "%s: PCI Error, primary error type[%s]\n",
	       pbm->name,
	       (((error_bits & PSYCHO_PCIAFSR_PMA) ?
		 "Master Abort" :
		 ((error_bits & PSYCHO_PCIAFSR_PTA) ?
		  "Target Abort" :
		  ((error_bits & PSYCHO_PCIAFSR_PRTRY) ?
		   "Excessive Retries" :
		   ((error_bits & PSYCHO_PCIAFSR_PPERR) ?
		    "Parity Error" : "???"))))));
	prपूर्णांकk(KERN_ERR "%s: bytemask[%04llx] UPA_MID[%02llx] was_block(%d)\n",
	       pbm->name,
	       (afsr & PSYCHO_PCIAFSR_BMSK) >> 32UL,
	       (afsr & PSYCHO_PCIAFSR_MID) >> 25UL,
	       (afsr & PSYCHO_PCIAFSR_BLK) ? 1 : 0);
	prपूर्णांकk(KERN_ERR "%s: PCI AFAR [%016llx]\n", pbm->name, afar);
	prपूर्णांकk(KERN_ERR "%s: PCI Secondary errors [", pbm->name);
	reported = 0;
	अगर (afsr & PSYCHO_PCIAFSR_SMA) अणु
		reported++;
		prपूर्णांकk("(Master Abort)");
	पूर्ण
	अगर (afsr & PSYCHO_PCIAFSR_STA) अणु
		reported++;
		prपूर्णांकk("(Target Abort)");
	पूर्ण
	अगर (afsr & PSYCHO_PCIAFSR_SRTRY) अणु
		reported++;
		prपूर्णांकk("(Excessive Retries)");
	पूर्ण
	अगर (afsr & PSYCHO_PCIAFSR_SPERR) अणु
		reported++;
		prपूर्णांकk("(Parity Error)");
	पूर्ण
	अगर (!reported)
		prपूर्णांकk("(none)");
	prपूर्णांकk("]\n");

	अगर (error_bits & (PSYCHO_PCIAFSR_PTA | PSYCHO_PCIAFSR_STA)) अणु
		psycho_check_iommu_error(pbm, afsr, afar, PCI_ERR);
		pci_scan_क्रम_target_पात(pbm, pbm->pci_bus);
	पूर्ण
	अगर (error_bits & (PSYCHO_PCIAFSR_PMA | PSYCHO_PCIAFSR_SMA))
		pci_scan_क्रम_master_पात(pbm, pbm->pci_bus);

	अगर (error_bits & (PSYCHO_PCIAFSR_PPERR | PSYCHO_PCIAFSR_SPERR))
		pci_scan_क्रम_parity_error(pbm, pbm->pci_bus);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम psycho_iommu_flush(काष्ठा pci_pbm_info *pbm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++) अणु
		अचिन्हित दीर्घ off = i * 8;

		upa_ग_लिखोq(0, pbm->controller_regs + PSYCHO_IOMMU_TAG + off);
		upa_ग_लिखोq(0, pbm->controller_regs + PSYCHO_IOMMU_DATA + off);
	पूर्ण
पूर्ण

#घोषणा PSYCHO_IOMMU_CONTROL		0x0200UL
#घोषणा  PSYCHO_IOMMU_CTRL_TSBSZ	0x0000000000070000UL
#घोषणा  PSYCHO_IOMMU_TSBSZ_1K      	0x0000000000000000UL
#घोषणा  PSYCHO_IOMMU_TSBSZ_2K      	0x0000000000010000UL
#घोषणा  PSYCHO_IOMMU_TSBSZ_4K      	0x0000000000020000UL
#घोषणा  PSYCHO_IOMMU_TSBSZ_8K      	0x0000000000030000UL
#घोषणा  PSYCHO_IOMMU_TSBSZ_16K     	0x0000000000040000UL
#घोषणा  PSYCHO_IOMMU_TSBSZ_32K     	0x0000000000050000UL
#घोषणा  PSYCHO_IOMMU_TSBSZ_64K     	0x0000000000060000UL
#घोषणा  PSYCHO_IOMMU_TSBSZ_128K    	0x0000000000070000UL
#घोषणा  PSYCHO_IOMMU_CTRL_TBWSZ    	0x0000000000000004UL
#घोषणा  PSYCHO_IOMMU_CTRL_DENAB    	0x0000000000000002UL
#घोषणा  PSYCHO_IOMMU_CTRL_ENAB     	0x0000000000000001UL
#घोषणा PSYCHO_IOMMU_FLUSH		0x0210UL
#घोषणा PSYCHO_IOMMU_TSBBASE		0x0208UL

पूर्णांक psycho_iommu_init(काष्ठा pci_pbm_info *pbm, पूर्णांक tsbsize,
		      u32 dvma_offset, u32 dma_mask,
		      अचिन्हित दीर्घ ग_लिखो_complete_offset)
अणु
	काष्ठा iommu *iommu = pbm->iommu;
	u64 control;
	पूर्णांक err;

	iommu->iommu_control  = pbm->controller_regs + PSYCHO_IOMMU_CONTROL;
	iommu->iommu_tsbbase  = pbm->controller_regs + PSYCHO_IOMMU_TSBBASE;
	iommu->iommu_flush    = pbm->controller_regs + PSYCHO_IOMMU_FLUSH;
	iommu->iommu_tags     = pbm->controller_regs + PSYCHO_IOMMU_TAG;
	iommu->ग_लिखो_complete_reg = (pbm->controller_regs +
				     ग_लिखो_complete_offset);

	iommu->iommu_ctxflush = 0;

	control = upa_पढ़ोq(iommu->iommu_control);
	control |= PSYCHO_IOMMU_CTRL_DENAB;
	upa_ग_लिखोq(control, iommu->iommu_control);

	psycho_iommu_flush(pbm);

	/* Leave diag mode enabled क्रम full-flushing करोne in pci_iommu.c */
	err = iommu_table_init(iommu, tsbsize * 1024 * 8,
			       dvma_offset, dma_mask, pbm->numa_node);
	अगर (err)
		वापस err;

	upa_ग_लिखोq(__pa(iommu->page_table), iommu->iommu_tsbbase);

	control = upa_पढ़ोq(iommu->iommu_control);
	control &= ~(PSYCHO_IOMMU_CTRL_TSBSZ | PSYCHO_IOMMU_CTRL_TBWSZ);
	control |= PSYCHO_IOMMU_CTRL_ENAB;

	चयन (tsbsize) अणु
	हाल 64:
		control |= PSYCHO_IOMMU_TSBSZ_64K;
		अवरोध;
	हाल 128:
		control |= PSYCHO_IOMMU_TSBSZ_128K;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	upa_ग_लिखोq(control, iommu->iommu_control);

	वापस 0;

पूर्ण

व्योम psycho_pbm_init_common(काष्ठा pci_pbm_info *pbm, काष्ठा platक्रमm_device *op,
			    स्थिर अक्षर *chip_name, पूर्णांक chip_type)
अणु
	काष्ठा device_node *dp = op->dev.of_node;

	pbm->name = dp->full_name;
	pbm->numa_node = NUMA_NO_NODE;
	pbm->chip_type = chip_type;
	pbm->chip_version = of_getपूर्णांकprop_शेष(dp, "version#", 0);
	pbm->chip_revision = of_getपूर्णांकprop_शेष(dp, "module-revision#", 0);
	pbm->op = op;
	pbm->pci_ops = &sun4u_pci_ops;
	pbm->config_space_reg_bits = 8;
	pbm->index = pci_num_pbms++;
	pci_get_pbm_props(pbm);
	pci_determine_mem_io_space(pbm);

	prपूर्णांकk(KERN_INFO "%s: %s PCI Bus Module ver[%x:%x]\n",
	       pbm->name, chip_name,
	       pbm->chip_version, pbm->chip_revision);
पूर्ण
