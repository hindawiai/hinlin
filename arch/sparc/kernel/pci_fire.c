<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* pci_fire.c: Sun4u platक्रमm PCI-E controller support.
 *
 * Copyright (C) 2007 David S. Miller (davem@davemloft.net)
 */
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/msi.h>
#समावेश <linux/export.h>
#समावेश <linux/irq.h>
#समावेश <linux/of_device.h>
#समावेश <linux/numa.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/upa.h>

#समावेश "pci_impl.h"

#घोषणा DRIVER_NAME	"fire"
#घोषणा PFX		DRIVER_NAME ": "

#घोषणा FIRE_IOMMU_CONTROL	0x40000UL
#घोषणा FIRE_IOMMU_TSBBASE	0x40008UL
#घोषणा FIRE_IOMMU_FLUSH	0x40100UL
#घोषणा FIRE_IOMMU_FLUSHINV	0x40108UL

अटल पूर्णांक pci_fire_pbm_iommu_init(काष्ठा pci_pbm_info *pbm)
अणु
	काष्ठा iommu *iommu = pbm->iommu;
	u32 vdma[2], dma_mask;
	u64 control;
	पूर्णांक tsbsize, err;

	/* No भव-dma property on these guys, use largest size.  */
	vdma[0] = 0xc0000000; /* base */
	vdma[1] = 0x40000000; /* size */
	dma_mask = 0xffffffff;
	tsbsize = 128;

	/* Register addresses. */
	iommu->iommu_control  = pbm->pbm_regs + FIRE_IOMMU_CONTROL;
	iommu->iommu_tsbbase  = pbm->pbm_regs + FIRE_IOMMU_TSBBASE;
	iommu->iommu_flush    = pbm->pbm_regs + FIRE_IOMMU_FLUSH;
	iommu->iommu_flushinv = pbm->pbm_regs + FIRE_IOMMU_FLUSHINV;

	/* We use the मुख्य control/status रेजिस्टर of FIRE as the ग_लिखो
	 * completion रेजिस्टर.
	 */
	iommu->ग_लिखो_complete_reg = pbm->controller_regs + 0x410000UL;

	/*
	 * Invalidate TLB Entries.
	 */
	upa_ग_लिखोq(~(u64)0, iommu->iommu_flushinv);

	err = iommu_table_init(iommu, tsbsize * 8 * 1024, vdma[0], dma_mask,
			       pbm->numa_node);
	अगर (err)
		वापस err;

	upa_ग_लिखोq(__pa(iommu->page_table) | 0x7UL, iommu->iommu_tsbbase);

	control = upa_पढ़ोq(iommu->iommu_control);
	control |= (0x00000400 /* TSB cache snoop enable */	|
		    0x00000300 /* Cache mode */			|
		    0x00000002 /* Bypass enable */		|
		    0x00000001 /* Translation enable */);
	upa_ग_लिखोq(control, iommu->iommu_control);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PCI_MSI
काष्ठा pci_msiq_entry अणु
	u64		word0;
#घोषणा MSIQ_WORD0_RESV			0x8000000000000000UL
#घोषणा MSIQ_WORD0_FMT_TYPE		0x7f00000000000000UL
#घोषणा MSIQ_WORD0_FMT_TYPE_SHIFT	56
#घोषणा MSIQ_WORD0_LEN			0x00ffc00000000000UL
#घोषणा MSIQ_WORD0_LEN_SHIFT		46
#घोषणा MSIQ_WORD0_ADDR0		0x00003fff00000000UL
#घोषणा MSIQ_WORD0_ADDR0_SHIFT		32
#घोषणा MSIQ_WORD0_RID			0x00000000ffff0000UL
#घोषणा MSIQ_WORD0_RID_SHIFT		16
#घोषणा MSIQ_WORD0_DATA0		0x000000000000ffffUL
#घोषणा MSIQ_WORD0_DATA0_SHIFT		0

#घोषणा MSIQ_TYPE_MSG			0x6
#घोषणा MSIQ_TYPE_MSI32			0xb
#घोषणा MSIQ_TYPE_MSI64			0xf

	u64		word1;
#घोषणा MSIQ_WORD1_ADDR1		0xffffffffffff0000UL
#घोषणा MSIQ_WORD1_ADDR1_SHIFT		16
#घोषणा MSIQ_WORD1_DATA1		0x000000000000ffffUL
#घोषणा MSIQ_WORD1_DATA1_SHIFT		0

	u64		resv[6];
पूर्ण;

/* All MSI रेजिस्टरs are offset from pbm->pbm_regs */
#घोषणा EVENT_QUEUE_BASE_ADDR_REG	0x010000UL
#घोषणा  EVENT_QUEUE_BASE_ADDR_ALL_ONES	0xfffc000000000000UL

#घोषणा EVENT_QUEUE_CONTROL_SET(EQ)	(0x011000UL + (EQ) * 0x8UL)
#घोषणा  EVENT_QUEUE_CONTROL_SET_OFLOW	0x0200000000000000UL
#घोषणा  EVENT_QUEUE_CONTROL_SET_EN	0x0000100000000000UL

#घोषणा EVENT_QUEUE_CONTROL_CLEAR(EQ)	(0x011200UL + (EQ) * 0x8UL)
#घोषणा  EVENT_QUEUE_CONTROL_CLEAR_OF	0x0200000000000000UL
#घोषणा  EVENT_QUEUE_CONTROL_CLEAR_E2I	0x0000800000000000UL
#घोषणा  EVENT_QUEUE_CONTROL_CLEAR_DIS	0x0000100000000000UL

#घोषणा EVENT_QUEUE_STATE(EQ)		(0x011400UL + (EQ) * 0x8UL)
#घोषणा  EVENT_QUEUE_STATE_MASK		0x0000000000000007UL
#घोषणा  EVENT_QUEUE_STATE_IDLE		0x0000000000000001UL
#घोषणा  EVENT_QUEUE_STATE_ACTIVE	0x0000000000000002UL
#घोषणा  EVENT_QUEUE_STATE_ERROR	0x0000000000000004UL

#घोषणा EVENT_QUEUE_TAIL(EQ)		(0x011600UL + (EQ) * 0x8UL)
#घोषणा  EVENT_QUEUE_TAIL_OFLOW		0x0200000000000000UL
#घोषणा  EVENT_QUEUE_TAIL_VAL		0x000000000000007fUL

#घोषणा EVENT_QUEUE_HEAD(EQ)		(0x011800UL + (EQ) * 0x8UL)
#घोषणा  EVENT_QUEUE_HEAD_VAL		0x000000000000007fUL

#घोषणा MSI_MAP(MSI)			(0x020000UL + (MSI) * 0x8UL)
#घोषणा  MSI_MAP_VALID			0x8000000000000000UL
#घोषणा  MSI_MAP_EQWR_N			0x4000000000000000UL
#घोषणा  MSI_MAP_EQNUM			0x000000000000003fUL

#घोषणा MSI_CLEAR(MSI)			(0x028000UL + (MSI) * 0x8UL)
#घोषणा  MSI_CLEAR_EQWR_N		0x4000000000000000UL

#घोषणा IMONDO_DATA0			0x02C000UL
#घोषणा  IMONDO_DATA0_DATA		0xffffffffffffffc0UL

#घोषणा IMONDO_DATA1			0x02C008UL
#घोषणा  IMONDO_DATA1_DATA		0xffffffffffffffffUL

#घोषणा MSI_32BIT_ADDR			0x034000UL
#घोषणा  MSI_32BIT_ADDR_VAL		0x00000000ffff0000UL

#घोषणा MSI_64BIT_ADDR			0x034008UL
#घोषणा  MSI_64BIT_ADDR_VAL		0xffffffffffff0000UL

अटल पूर्णांक pci_fire_get_head(काष्ठा pci_pbm_info *pbm, अचिन्हित दीर्घ msiqid,
			     अचिन्हित दीर्घ *head)
अणु
	*head = upa_पढ़ोq(pbm->pbm_regs + EVENT_QUEUE_HEAD(msiqid));
	वापस 0;
पूर्ण

अटल पूर्णांक pci_fire_dequeue_msi(काष्ठा pci_pbm_info *pbm, अचिन्हित दीर्घ msiqid,
				अचिन्हित दीर्घ *head, अचिन्हित दीर्घ *msi)
अणु
	अचिन्हित दीर्घ type_fmt, type, msi_num;
	काष्ठा pci_msiq_entry *base, *ep;

	base = (pbm->msi_queues + ((msiqid - pbm->msiq_first) * 8192));
	ep = &base[*head];

	अगर ((ep->word0 & MSIQ_WORD0_FMT_TYPE) == 0)
		वापस 0;

	type_fmt = ((ep->word0 & MSIQ_WORD0_FMT_TYPE) >>
		    MSIQ_WORD0_FMT_TYPE_SHIFT);
	type = (type_fmt >> 3);
	अगर (unlikely(type != MSIQ_TYPE_MSI32 &&
		     type != MSIQ_TYPE_MSI64))
		वापस -EINVAL;

	*msi = msi_num = ((ep->word0 & MSIQ_WORD0_DATA0) >>
			  MSIQ_WORD0_DATA0_SHIFT);

	upa_ग_लिखोq(MSI_CLEAR_EQWR_N, pbm->pbm_regs + MSI_CLEAR(msi_num));

	/* Clear the entry.  */
	ep->word0 &= ~MSIQ_WORD0_FMT_TYPE;

	/* Go to next entry in ring.  */
	(*head)++;
	अगर (*head >= pbm->msiq_ent_count)
		*head = 0;

	वापस 1;
पूर्ण

अटल पूर्णांक pci_fire_set_head(काष्ठा pci_pbm_info *pbm, अचिन्हित दीर्घ msiqid,
			     अचिन्हित दीर्घ head)
अणु
	upa_ग_लिखोq(head, pbm->pbm_regs + EVENT_QUEUE_HEAD(msiqid));
	वापस 0;
पूर्ण

अटल पूर्णांक pci_fire_msi_setup(काष्ठा pci_pbm_info *pbm, अचिन्हित दीर्घ msiqid,
			      अचिन्हित दीर्घ msi, पूर्णांक is_msi64)
अणु
	u64 val;

	val = upa_पढ़ोq(pbm->pbm_regs + MSI_MAP(msi));
	val &= ~(MSI_MAP_EQNUM);
	val |= msiqid;
	upa_ग_लिखोq(val, pbm->pbm_regs + MSI_MAP(msi));

	upa_ग_लिखोq(MSI_CLEAR_EQWR_N, pbm->pbm_regs + MSI_CLEAR(msi));

	val = upa_पढ़ोq(pbm->pbm_regs + MSI_MAP(msi));
	val |= MSI_MAP_VALID;
	upa_ग_लिखोq(val, pbm->pbm_regs + MSI_MAP(msi));

	वापस 0;
पूर्ण

अटल पूर्णांक pci_fire_msi_tearकरोwn(काष्ठा pci_pbm_info *pbm, अचिन्हित दीर्घ msi)
अणु
	u64 val;

	val = upa_पढ़ोq(pbm->pbm_regs + MSI_MAP(msi));

	val &= ~MSI_MAP_VALID;

	upa_ग_लिखोq(val, pbm->pbm_regs + MSI_MAP(msi));

	वापस 0;
पूर्ण

अटल पूर्णांक pci_fire_msiq_alloc(काष्ठा pci_pbm_info *pbm)
अणु
	अचिन्हित दीर्घ pages, order, i;

	order = get_order(512 * 1024);
	pages = __get_मुक्त_pages(GFP_KERNEL | __GFP_COMP, order);
	अगर (pages == 0UL) अणु
		prपूर्णांकk(KERN_ERR "MSI: Cannot allocate MSI queues (o=%lu).\n",
		       order);
		वापस -ENOMEM;
	पूर्ण
	स_रखो((अक्षर *)pages, 0, PAGE_SIZE << order);
	pbm->msi_queues = (व्योम *) pages;

	upa_ग_लिखोq((EVENT_QUEUE_BASE_ADDR_ALL_ONES |
		    __pa(pbm->msi_queues)),
		   pbm->pbm_regs + EVENT_QUEUE_BASE_ADDR_REG);

	upa_ग_लिखोq(pbm->portid << 6, pbm->pbm_regs + IMONDO_DATA0);
	upa_ग_लिखोq(0, pbm->pbm_regs + IMONDO_DATA1);

	upa_ग_लिखोq(pbm->msi32_start, pbm->pbm_regs + MSI_32BIT_ADDR);
	upa_ग_लिखोq(pbm->msi64_start, pbm->pbm_regs + MSI_64BIT_ADDR);

	क्रम (i = 0; i < pbm->msiq_num; i++) अणु
		upa_ग_लिखोq(0, pbm->pbm_regs + EVENT_QUEUE_HEAD(i));
		upa_ग_लिखोq(0, pbm->pbm_regs + EVENT_QUEUE_TAIL(i));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pci_fire_msiq_मुक्त(काष्ठा pci_pbm_info *pbm)
अणु
	अचिन्हित दीर्घ pages, order;

	order = get_order(512 * 1024);
	pages = (अचिन्हित दीर्घ) pbm->msi_queues;

	मुक्त_pages(pages, order);

	pbm->msi_queues = शून्य;
पूर्ण

अटल पूर्णांक pci_fire_msiq_build_irq(काष्ठा pci_pbm_info *pbm,
				   अचिन्हित दीर्घ msiqid,
				   अचिन्हित दीर्घ devino)
अणु
	अचिन्हित दीर्घ cregs = (अचिन्हित दीर्घ) pbm->pbm_regs;
	अचिन्हित दीर्घ imap_reg, iclr_reg, पूर्णांक_ctrlr;
	अचिन्हित पूर्णांक irq;
	पूर्णांक fixup;
	u64 val;

	imap_reg = cregs + (0x001000UL + (devino * 0x08UL));
	iclr_reg = cregs + (0x001400UL + (devino * 0x08UL));

	/* XXX iterate amongst the 4 IRQ controllers XXX */
	पूर्णांक_ctrlr = (1UL << 6);

	val = upa_पढ़ोq(imap_reg);
	val |= (1UL << 63) | पूर्णांक_ctrlr;
	upa_ग_लिखोq(val, imap_reg);

	fixup = ((pbm->portid << 6) | devino) - पूर्णांक_ctrlr;

	irq = build_irq(fixup, iclr_reg, imap_reg);
	अगर (!irq)
		वापस -ENOMEM;

	upa_ग_लिखोq(EVENT_QUEUE_CONTROL_SET_EN,
		   pbm->pbm_regs + EVENT_QUEUE_CONTROL_SET(msiqid));

	वापस irq;
पूर्ण

अटल स्थिर काष्ठा sparc64_msiq_ops pci_fire_msiq_ops = अणु
	.get_head	=	pci_fire_get_head,
	.dequeue_msi	=	pci_fire_dequeue_msi,
	.set_head	=	pci_fire_set_head,
	.msi_setup	=	pci_fire_msi_setup,
	.msi_tearकरोwn	=	pci_fire_msi_tearकरोwn,
	.msiq_alloc	=	pci_fire_msiq_alloc,
	.msiq_मुक्त	=	pci_fire_msiq_मुक्त,
	.msiq_build_irq	=	pci_fire_msiq_build_irq,
पूर्ण;

अटल व्योम pci_fire_msi_init(काष्ठा pci_pbm_info *pbm)
अणु
	sparc64_pbm_msi_init(pbm, &pci_fire_msiq_ops);
पूर्ण
#अन्यथा /* CONFIG_PCI_MSI */
अटल व्योम pci_fire_msi_init(काष्ठा pci_pbm_info *pbm)
अणु
पूर्ण
#पूर्ण_अगर /* !(CONFIG_PCI_MSI) */

/* Based at pbm->controller_regs */
#घोषणा FIRE_PARITY_CONTROL	0x470010UL
#घोषणा  FIRE_PARITY_ENAB	0x8000000000000000UL
#घोषणा FIRE_FATAL_RESET_CTL	0x471028UL
#घोषणा  FIRE_FATAL_RESET_SPARE	0x0000000004000000UL
#घोषणा  FIRE_FATAL_RESET_MB	0x0000000002000000UL
#घोषणा  FIRE_FATAL_RESET_CPE	0x0000000000008000UL
#घोषणा  FIRE_FATAL_RESET_APE	0x0000000000004000UL
#घोषणा  FIRE_FATAL_RESET_PIO	0x0000000000000040UL
#घोषणा  FIRE_FATAL_RESET_JW	0x0000000000000004UL
#घोषणा  FIRE_FATAL_RESET_JI	0x0000000000000002UL
#घोषणा  FIRE_FATAL_RESET_JR	0x0000000000000001UL
#घोषणा FIRE_CORE_INTR_ENABLE	0x471800UL

/* Based at pbm->pbm_regs */
#घोषणा FIRE_TLU_CTRL		0x80000UL
#घोषणा  FIRE_TLU_CTRL_TIM	0x00000000da000000UL
#घोषणा  FIRE_TLU_CTRL_QDET	0x0000000000000100UL
#घोषणा  FIRE_TLU_CTRL_CFG	0x0000000000000001UL
#घोषणा FIRE_TLU_DEV_CTRL	0x90008UL
#घोषणा FIRE_TLU_LINK_CTRL	0x90020UL
#घोषणा FIRE_TLU_LINK_CTRL_CLK	0x0000000000000040UL
#घोषणा FIRE_LPU_RESET		0xe2008UL
#घोषणा FIRE_LPU_LLCFG		0xe2200UL
#घोषणा  FIRE_LPU_LLCFG_VC0	0x0000000000000100UL
#घोषणा FIRE_LPU_FCTRL_UCTRL	0xe2240UL
#घोषणा  FIRE_LPU_FCTRL_UCTRL_N	0x0000000000000002UL
#घोषणा  FIRE_LPU_FCTRL_UCTRL_P	0x0000000000000001UL
#घोषणा FIRE_LPU_TXL_FIFOP	0xe2430UL
#घोषणा FIRE_LPU_LTSSM_CFG2	0xe2788UL
#घोषणा FIRE_LPU_LTSSM_CFG3	0xe2790UL
#घोषणा FIRE_LPU_LTSSM_CFG4	0xe2798UL
#घोषणा FIRE_LPU_LTSSM_CFG5	0xe27a0UL
#घोषणा FIRE_DMC_IENAB		0x31800UL
#घोषणा FIRE_DMC_DBG_SEL_A	0x53000UL
#घोषणा FIRE_DMC_DBG_SEL_B	0x53008UL
#घोषणा FIRE_PEC_IENAB		0x51800UL

अटल व्योम pci_fire_hw_init(काष्ठा pci_pbm_info *pbm)
अणु
	u64 val;

	upa_ग_लिखोq(FIRE_PARITY_ENAB,
		   pbm->controller_regs + FIRE_PARITY_CONTROL);

	upa_ग_लिखोq((FIRE_FATAL_RESET_SPARE |
		    FIRE_FATAL_RESET_MB |
		    FIRE_FATAL_RESET_CPE |
		    FIRE_FATAL_RESET_APE |
		    FIRE_FATAL_RESET_PIO |
		    FIRE_FATAL_RESET_JW |
		    FIRE_FATAL_RESET_JI |
		    FIRE_FATAL_RESET_JR),
		   pbm->controller_regs + FIRE_FATAL_RESET_CTL);

	upa_ग_लिखोq(~(u64)0, pbm->controller_regs + FIRE_CORE_INTR_ENABLE);

	val = upa_पढ़ोq(pbm->pbm_regs + FIRE_TLU_CTRL);
	val |= (FIRE_TLU_CTRL_TIM |
		FIRE_TLU_CTRL_QDET |
		FIRE_TLU_CTRL_CFG);
	upa_ग_लिखोq(val, pbm->pbm_regs + FIRE_TLU_CTRL);
	upa_ग_लिखोq(0, pbm->pbm_regs + FIRE_TLU_DEV_CTRL);
	upa_ग_लिखोq(FIRE_TLU_LINK_CTRL_CLK,
		   pbm->pbm_regs + FIRE_TLU_LINK_CTRL);

	upa_ग_लिखोq(0, pbm->pbm_regs + FIRE_LPU_RESET);
	upa_ग_लिखोq(FIRE_LPU_LLCFG_VC0, pbm->pbm_regs + FIRE_LPU_LLCFG);
	upa_ग_लिखोq((FIRE_LPU_FCTRL_UCTRL_N | FIRE_LPU_FCTRL_UCTRL_P),
		   pbm->pbm_regs + FIRE_LPU_FCTRL_UCTRL);
	upa_ग_लिखोq(((0xffff << 16) | (0x0000 << 0)),
		   pbm->pbm_regs + FIRE_LPU_TXL_FIFOP);
	upa_ग_लिखोq(3000000, pbm->pbm_regs + FIRE_LPU_LTSSM_CFG2);
	upa_ग_लिखोq(500000, pbm->pbm_regs + FIRE_LPU_LTSSM_CFG3);
	upa_ग_लिखोq((2 << 16) | (140 << 8),
		   pbm->pbm_regs + FIRE_LPU_LTSSM_CFG4);
	upa_ग_लिखोq(0, pbm->pbm_regs + FIRE_LPU_LTSSM_CFG5);

	upa_ग_लिखोq(~(u64)0, pbm->pbm_regs + FIRE_DMC_IENAB);
	upa_ग_लिखोq(0, pbm->pbm_regs + FIRE_DMC_DBG_SEL_A);
	upa_ग_लिखोq(0, pbm->pbm_regs + FIRE_DMC_DBG_SEL_B);

	upa_ग_लिखोq(~(u64)0, pbm->pbm_regs + FIRE_PEC_IENAB);
पूर्ण

अटल पूर्णांक pci_fire_pbm_init(काष्ठा pci_pbm_info *pbm,
			     काष्ठा platक्रमm_device *op, u32 portid)
अणु
	स्थिर काष्ठा linux_prom64_रेजिस्टरs *regs;
	काष्ठा device_node *dp = op->dev.of_node;
	पूर्णांक err;

	pbm->numa_node = NUMA_NO_NODE;

	pbm->pci_ops = &sun4u_pci_ops;
	pbm->config_space_reg_bits = 12;

	pbm->index = pci_num_pbms++;

	pbm->portid = portid;
	pbm->op = op;
	pbm->name = dp->full_name;

	regs = of_get_property(dp, "reg", शून्य);
	pbm->pbm_regs = regs[0].phys_addr;
	pbm->controller_regs = regs[1].phys_addr - 0x410000UL;

	prपूर्णांकk("%s: SUN4U PCIE Bus Module\n", pbm->name);

	pci_determine_mem_io_space(pbm);

	pci_get_pbm_props(pbm);

	pci_fire_hw_init(pbm);

	err = pci_fire_pbm_iommu_init(pbm);
	अगर (err)
		वापस err;

	pci_fire_msi_init(pbm);

	pbm->pci_bus = pci_scan_one_pbm(pbm, &op->dev);

	/* XXX रेजिस्टर error पूर्णांकerrupt handlers XXX */

	pbm->next = pci_pbm_root;
	pci_pbm_root = pbm;

	वापस 0;
पूर्ण

अटल पूर्णांक fire_probe(काष्ठा platक्रमm_device *op)
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
		prपूर्णांकk(KERN_ERR PFX "Cannot allocate pci_pbminfo.\n");
		जाओ out_err;
	पूर्ण

	iommu = kzalloc(माप(काष्ठा iommu), GFP_KERNEL);
	अगर (!iommu) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot allocate PBM iommu.\n");
		जाओ out_मुक्त_controller;
	पूर्ण

	pbm->iommu = iommu;

	err = pci_fire_pbm_init(pbm, op, portid);
	अगर (err)
		जाओ out_मुक्त_iommu;

	dev_set_drvdata(&op->dev, pbm);

	वापस 0;

out_मुक्त_iommu:
	kमुक्त(pbm->iommu);
			
out_मुक्त_controller:
	kमुक्त(pbm);

out_err:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id fire_match[] = अणु
	अणु
		.name = "pci",
		.compatible = "pciex108e,80f0",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver fire_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = fire_match,
	पूर्ण,
	.probe		= fire_probe,
पूर्ण;

अटल पूर्णांक __init fire_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&fire_driver);
पूर्ण

subsys_initcall(fire_init);
