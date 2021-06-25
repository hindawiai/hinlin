<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>

#समावेश "hinic_hw_csr.h"
#समावेश "hinic_hw_if.h"

#घोषणा PCIE_ATTR_ENTRY         0

#घोषणा VALID_MSIX_IDX(attr, msix_index) ((msix_index) < (attr)->num_irqs)

#घोषणा WAIT_HWIF_READY_TIMEOUT	10000

#घोषणा HINIC_SELFTEST_RESULT 0x883C

/**
 * hinic_msix_attr_set - set message attribute क्रम msix entry
 * @hwअगर: the HW पूर्णांकerface of a pci function device
 * @msix_index: msix_index
 * @pending_limit: the maximum pending पूर्णांकerrupt events (unit 8)
 * @coalesc_समयr: coalesc period क्रम पूर्णांकerrupt (unit 8 us)
 * @lli_समयr: replenishing period क्रम low latency credit (unit 8 us)
 * @lli_credit_limit: maximum credits क्रम low latency msix messages (unit 8)
 * @resend_समयr: maximum रुको क्रम resending msix (unit coalesc period)
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_msix_attr_set(काष्ठा hinic_hwअगर *hwअगर, u16 msix_index,
			u8 pending_limit, u8 coalesc_समयr,
			u8 lli_समयr, u8 lli_credit_limit,
			u8 resend_समयr)
अणु
	u32 msix_ctrl, addr;

	अगर (!VALID_MSIX_IDX(&hwअगर->attr, msix_index))
		वापस -EINVAL;

	msix_ctrl = HINIC_MSIX_ATTR_SET(pending_limit, PENDING_LIMIT)   |
		    HINIC_MSIX_ATTR_SET(coalesc_समयr, COALESC_TIMER)   |
		    HINIC_MSIX_ATTR_SET(lli_समयr, LLI_TIMER)           |
		    HINIC_MSIX_ATTR_SET(lli_credit_limit, LLI_CREDIT)   |
		    HINIC_MSIX_ATTR_SET(resend_समयr, RESEND_TIMER);

	addr = HINIC_CSR_MSIX_CTRL_ADDR(msix_index);

	hinic_hwअगर_ग_लिखो_reg(hwअगर, addr, msix_ctrl);
	वापस 0;
पूर्ण

/**
 * hinic_msix_attr_get - get message attribute of msix entry
 * @hwअगर: the HW पूर्णांकerface of a pci function device
 * @msix_index: msix_index
 * @pending_limit: the maximum pending पूर्णांकerrupt events (unit 8)
 * @coalesc_समयr: coalesc period क्रम पूर्णांकerrupt (unit 8 us)
 * @lli_समयr: replenishing period क्रम low latency credit (unit 8 us)
 * @lli_credit_limit: maximum credits क्रम low latency msix messages (unit 8)
 * @resend_समयr: maximum रुको क्रम resending msix (unit coalesc period)
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_msix_attr_get(काष्ठा hinic_hwअगर *hwअगर, u16 msix_index,
			u8 *pending_limit, u8 *coalesc_समयr,
			u8 *lli_समयr, u8 *lli_credit_limit,
			u8 *resend_समयr)
अणु
	u32 addr, val;

	अगर (!VALID_MSIX_IDX(&hwअगर->attr, msix_index))
		वापस -EINVAL;

	addr = HINIC_CSR_MSIX_CTRL_ADDR(msix_index);
	val  = hinic_hwअगर_पढ़ो_reg(hwअगर, addr);

	*pending_limit    = HINIC_MSIX_ATTR_GET(val, PENDING_LIMIT);
	*coalesc_समयr    = HINIC_MSIX_ATTR_GET(val, COALESC_TIMER);
	*lli_समयr        = HINIC_MSIX_ATTR_GET(val, LLI_TIMER);
	*lli_credit_limit = HINIC_MSIX_ATTR_GET(val, LLI_CREDIT);
	*resend_समयr     = HINIC_MSIX_ATTR_GET(val, RESEND_TIMER);
	वापस 0;
पूर्ण

/**
 * hinic_msix_attr_cnt_clear - clear message attribute counters क्रम msix entry
 * @hwअगर: the HW पूर्णांकerface of a pci function device
 * @msix_index: msix_index
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_msix_attr_cnt_clear(काष्ठा hinic_hwअगर *hwअगर, u16 msix_index)
अणु
	u32 msix_ctrl, addr;

	अगर (!VALID_MSIX_IDX(&hwअगर->attr, msix_index))
		वापस -EINVAL;

	msix_ctrl = HINIC_MSIX_CNT_SET(1, RESEND_TIMER);
	addr = HINIC_CSR_MSIX_CNT_ADDR(msix_index);

	hinic_hwअगर_ग_लिखो_reg(hwअगर, addr, msix_ctrl);
	वापस 0;
पूर्ण

/**
 * hinic_set_pf_action - set action on pf channel
 * @hwअगर: the HW पूर्णांकerface of a pci function device
 * @action: action on pf channel
 *
 * Return 0 - Success, negative - Failure
 **/
व्योम hinic_set_pf_action(काष्ठा hinic_hwअगर *hwअगर, क्रमागत hinic_pf_action action)
अणु
	u32 attr5;

	अगर (HINIC_IS_VF(hwअगर))
		वापस;

	attr5 = hinic_hwअगर_पढ़ो_reg(hwअगर, HINIC_CSR_FUNC_ATTR5_ADDR);
	attr5 = HINIC_FA5_CLEAR(attr5, PF_ACTION);
	attr5 |= HINIC_FA5_SET(action, PF_ACTION);

	hinic_hwअगर_ग_लिखो_reg(hwअगर, HINIC_CSR_FUNC_ATTR5_ADDR, attr5);
पूर्ण

क्रमागत hinic_outbound_state hinic_outbound_state_get(काष्ठा hinic_hwअगर *hwअगर)
अणु
	u32 attr4 = hinic_hwअगर_पढ़ो_reg(hwअगर, HINIC_CSR_FUNC_ATTR4_ADDR);

	वापस HINIC_FA4_GET(attr4, OUTBOUND_STATE);
पूर्ण

व्योम hinic_outbound_state_set(काष्ठा hinic_hwअगर *hwअगर,
			      क्रमागत hinic_outbound_state outbound_state)
अणु
	u32 attr4 = hinic_hwअगर_पढ़ो_reg(hwअगर, HINIC_CSR_FUNC_ATTR4_ADDR);

	attr4 = HINIC_FA4_CLEAR(attr4, OUTBOUND_STATE);
	attr4 |= HINIC_FA4_SET(outbound_state, OUTBOUND_STATE);

	hinic_hwअगर_ग_लिखो_reg(hwअगर, HINIC_CSR_FUNC_ATTR4_ADDR, attr4);
पूर्ण

क्रमागत hinic_db_state hinic_db_state_get(काष्ठा hinic_hwअगर *hwअगर)
अणु
	u32 attr4 = hinic_hwअगर_पढ़ो_reg(hwअगर, HINIC_CSR_FUNC_ATTR4_ADDR);

	वापस HINIC_FA4_GET(attr4, DB_STATE);
पूर्ण

व्योम hinic_db_state_set(काष्ठा hinic_hwअगर *hwअगर,
			क्रमागत hinic_db_state db_state)
अणु
	u32 attr4 = hinic_hwअगर_पढ़ो_reg(hwअगर, HINIC_CSR_FUNC_ATTR4_ADDR);

	attr4 = HINIC_FA4_CLEAR(attr4, DB_STATE);
	attr4 |= HINIC_FA4_SET(db_state, DB_STATE);

	hinic_hwअगर_ग_लिखो_reg(hwअगर, HINIC_CSR_FUNC_ATTR4_ADDR, attr4);
पूर्ण

व्योम hinic_set_msix_state(काष्ठा hinic_hwअगर *hwअगर, u16 msix_idx,
			  क्रमागत hinic_msix_state flag)
अणु
	u32 offset = msix_idx * HINIC_PCI_MSIX_ENTRY_SIZE +
			HINIC_PCI_MSIX_ENTRY_VECTOR_CTRL;
	u32 mask_bits;

	mask_bits = पढ़ोl(hwअगर->पूर्णांकr_regs_base + offset);
	mask_bits &= ~HINIC_PCI_MSIX_ENTRY_CTRL_MASKBIT;

	अगर (flag)
		mask_bits |= HINIC_PCI_MSIX_ENTRY_CTRL_MASKBIT;

	ग_लिखोl(mask_bits, hwअगर->पूर्णांकr_regs_base + offset);
पूर्ण

/**
 * hwअगर_पढ़ोy - test अगर the HW is पढ़ोy क्रम use
 * @hwअगर: the HW पूर्णांकerface of a pci function device
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक hwअगर_पढ़ोy(काष्ठा hinic_hwअगर *hwअगर)
अणु
	u32 addr, attr1;

	addr   = HINIC_CSR_FUNC_ATTR1_ADDR;
	attr1  = hinic_hwअगर_पढ़ो_reg(hwअगर, addr);

	अगर (!HINIC_FA1_GET(attr1, MGMT_INIT_STATUS))
		वापस -EBUSY;

	अगर (HINIC_IS_VF(hwअगर)) अणु
		अगर (!HINIC_FA1_GET(attr1, PF_INIT_STATUS))
			वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक रुको_hwअगर_पढ़ोy(काष्ठा hinic_hwअगर *hwअगर)
अणु
	अचिन्हित दीर्घ समयout = 0;

	करो अणु
		अगर (!hwअगर_पढ़ोy(hwअगर))
			वापस 0;

		usleep_range(999, 1000);
		समयout++;
	पूर्ण जबतक (समयout <= WAIT_HWIF_READY_TIMEOUT);

	dev_err(&hwअगर->pdev->dev, "Wait for hwif timeout\n");

	वापस -EBUSY;
पूर्ण

/**
 * set_hwअगर_attr - set the attributes in the relevant members in hwअगर
 * @hwअगर: the HW पूर्णांकerface of a pci function device
 * @attr0: the first attribute that was पढ़ो from the hw
 * @attr1: the second attribute that was पढ़ो from the hw
 * @attr2: the third attribute that was पढ़ो from the hw
 **/
अटल व्योम set_hwअगर_attr(काष्ठा hinic_hwअगर *hwअगर, u32 attr0, u32 attr1,
			  u32 attr2)
अणु
	hwअगर->attr.func_idx     = HINIC_FA0_GET(attr0, FUNC_IDX);
	hwअगर->attr.pf_idx       = HINIC_FA0_GET(attr0, PF_IDX);
	hwअगर->attr.pci_पूर्णांकf_idx = HINIC_FA0_GET(attr0, PCI_INTF_IDX);
	hwअगर->attr.func_type    = HINIC_FA0_GET(attr0, FUNC_TYPE);

	hwअगर->attr.num_aeqs = BIT(HINIC_FA1_GET(attr1, AEQS_PER_FUNC));
	hwअगर->attr.num_ceqs = BIT(HINIC_FA1_GET(attr1, CEQS_PER_FUNC));
	hwअगर->attr.num_irqs = BIT(HINIC_FA1_GET(attr1, IRQS_PER_FUNC));
	hwअगर->attr.num_dma_attr = BIT(HINIC_FA1_GET(attr1, DMA_ATTR_PER_FUNC));
	hwअगर->attr.global_vf_id_of_pf = HINIC_FA2_GET(attr2,
						      GLOBAL_VF_ID_OF_PF);
पूर्ण

/**
 * पढ़ो_hwअगर_attr - पढ़ो the attributes and set members in hwअगर
 * @hwअगर: the HW पूर्णांकerface of a pci function device
 **/
अटल व्योम पढ़ो_hwअगर_attr(काष्ठा hinic_hwअगर *hwअगर)
अणु
	u32 addr, attr0, attr1, attr2;

	addr   = HINIC_CSR_FUNC_ATTR0_ADDR;
	attr0  = hinic_hwअगर_पढ़ो_reg(hwअगर, addr);

	addr   = HINIC_CSR_FUNC_ATTR1_ADDR;
	attr1  = hinic_hwअगर_पढ़ो_reg(hwअगर, addr);

	addr   = HINIC_CSR_FUNC_ATTR2_ADDR;
	attr2  = hinic_hwअगर_पढ़ो_reg(hwअगर, addr);

	set_hwअगर_attr(hwअगर, attr0, attr1, attr2);
पूर्ण

/**
 * set_ppf - try to set hwअगर as ppf and set the type of hwअगर in this हाल
 * @hwअगर: the HW पूर्णांकerface of a pci function device
 **/
अटल व्योम set_ppf(काष्ठा hinic_hwअगर *hwअगर)
अणु
	काष्ठा hinic_func_attr *attr = &hwअगर->attr;
	u32 addr, val, ppf_election;

	/* Read Modअगरy Write */
	addr = HINIC_CSR_PPF_ELECTION_ADDR(HINIC_HWIF_PCI_INTF(hwअगर));

	val = hinic_hwअगर_पढ़ो_reg(hwअगर, addr);
	val = HINIC_PPF_ELECTION_CLEAR(val, IDX);

	ppf_election = HINIC_PPF_ELECTION_SET(HINIC_HWIF_FUNC_IDX(hwअगर), IDX);

	val |= ppf_election;
	hinic_hwअगर_ग_लिखो_reg(hwअगर, addr, val);

	/* check PPF */
	val = hinic_hwअगर_पढ़ो_reg(hwअगर, addr);

	attr->ppf_idx = HINIC_PPF_ELECTION_GET(val, IDX);
	अगर (attr->ppf_idx == HINIC_HWIF_FUNC_IDX(hwअगर))
		attr->func_type = HINIC_PPF;
पूर्ण

/**
 * set_dma_attr - set the dma attributes in the HW
 * @hwअगर: the HW पूर्णांकerface of a pci function device
 * @entry_idx: the entry index in the dma table
 * @st: PCIE TLP steering tag
 * @at: PCIE TLP AT field
 * @ph: PCIE TLP Processing Hपूर्णांक field
 * @no_snooping: PCIE TLP No snooping
 * @tph_en: PCIE TLP Processing Hपूर्णांक Enable
 **/
अटल व्योम set_dma_attr(काष्ठा hinic_hwअगर *hwअगर, u32 entry_idx,
			 u8 st, u8 at, u8 ph,
			 क्रमागत hinic_pcie_nosnoop no_snooping,
			 क्रमागत hinic_pcie_tph tph_en)
अणु
	u32 addr, val, dma_attr_entry;

	/* Read Modअगरy Write */
	addr = HINIC_CSR_DMA_ATTR_ADDR(entry_idx);

	val = hinic_hwअगर_पढ़ो_reg(hwअगर, addr);
	val = HINIC_DMA_ATTR_CLEAR(val, ST)             &
	      HINIC_DMA_ATTR_CLEAR(val, AT)             &
	      HINIC_DMA_ATTR_CLEAR(val, PH)             &
	      HINIC_DMA_ATTR_CLEAR(val, NO_SNOOPING)    &
	      HINIC_DMA_ATTR_CLEAR(val, TPH_EN);

	dma_attr_entry = HINIC_DMA_ATTR_SET(st, ST)                     |
			 HINIC_DMA_ATTR_SET(at, AT)                     |
			 HINIC_DMA_ATTR_SET(ph, PH)                     |
			 HINIC_DMA_ATTR_SET(no_snooping, NO_SNOOPING)   |
			 HINIC_DMA_ATTR_SET(tph_en, TPH_EN);

	val |= dma_attr_entry;
	hinic_hwअगर_ग_लिखो_reg(hwअगर, addr, val);
पूर्ण

/**
 * dma_attr_table_init - initialize the शेष dma attributes
 * @hwअगर: the HW पूर्णांकerface of a pci function device
 **/
अटल व्योम dma_attr_init(काष्ठा hinic_hwअगर *hwअगर)
अणु
	set_dma_attr(hwअगर, PCIE_ATTR_ENTRY, HINIC_PCIE_ST_DISABLE,
		     HINIC_PCIE_AT_DISABLE, HINIC_PCIE_PH_DISABLE,
		     HINIC_PCIE_SNOOP, HINIC_PCIE_TPH_DISABLE);
पूर्ण

u16 hinic_glb_pf_vf_offset(काष्ठा hinic_hwअगर *hwअगर)
अणु
	अगर (!hwअगर)
		वापस 0;

	वापस hwअगर->attr.global_vf_id_of_pf;
पूर्ण

u16 hinic_global_func_id_hw(काष्ठा hinic_hwअगर *hwअगर)
अणु
	u32 addr, attr0;

	addr   = HINIC_CSR_FUNC_ATTR0_ADDR;
	attr0  = hinic_hwअगर_पढ़ो_reg(hwअगर, addr);

	वापस HINIC_FA0_GET(attr0, FUNC_IDX);
पूर्ण

u16 hinic_pf_id_of_vf_hw(काष्ठा hinic_hwअगर *hwअगर)
अणु
	u32 addr, attr0;

	addr   = HINIC_CSR_FUNC_ATTR0_ADDR;
	attr0  = hinic_hwअगर_पढ़ो_reg(hwअगर, addr);

	वापस HINIC_FA0_GET(attr0, PF_IDX);
पूर्ण

अटल व्योम __prपूर्णांक_selftest_reg(काष्ठा hinic_hwअगर *hwअगर)
अणु
	u32 addr, attr0, attr1;

	addr   = HINIC_CSR_FUNC_ATTR1_ADDR;
	attr1  = hinic_hwअगर_पढ़ो_reg(hwअगर, addr);

	अगर (attr1 == HINIC_PCIE_LINK_DOWN) अणु
		dev_err(&hwअगर->pdev->dev, "PCIE is link down\n");
		वापस;
	पूर्ण

	addr   = HINIC_CSR_FUNC_ATTR0_ADDR;
	attr0  = hinic_hwअगर_पढ़ो_reg(hwअगर, addr);
	अगर (HINIC_FA0_GET(attr0, FUNC_TYPE) != HINIC_VF &&
	    !HINIC_FA0_GET(attr0, PCI_INTF_IDX))
		dev_err(&hwअगर->pdev->dev, "Selftest reg: 0x%08x\n",
			hinic_hwअगर_पढ़ो_reg(hwअगर, HINIC_SELFTEST_RESULT));
पूर्ण

/**
 * hinic_init_hwअगर - initialize the hw पूर्णांकerface
 * @hwअगर: the HW पूर्णांकerface of a pci function device
 * @pdev: the pci device क्रम acessing PCI resources
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_init_hwअगर(काष्ठा hinic_hwअगर *hwअगर, काष्ठा pci_dev *pdev)
अणु
	पूर्णांक err;

	hwअगर->pdev = pdev;

	hwअगर->cfg_regs_bar = pci_ioremap_bar(pdev, HINIC_PCI_CFG_REGS_BAR);
	अगर (!hwअगर->cfg_regs_bar) अणु
		dev_err(&pdev->dev, "Failed to map configuration regs\n");
		वापस -ENOMEM;
	पूर्ण

	hwअगर->पूर्णांकr_regs_base = pci_ioremap_bar(pdev, HINIC_PCI_INTR_REGS_BAR);
	अगर (!hwअगर->पूर्णांकr_regs_base) अणु
		dev_err(&pdev->dev, "Failed to map configuration regs\n");
		err = -ENOMEM;
		जाओ err_map_पूर्णांकr_bar;
	पूर्ण

	err = रुको_hwअगर_पढ़ोy(hwअगर);
	अगर (err) अणु
		dev_err(&pdev->dev, "HW interface is not ready\n");
		__prपूर्णांक_selftest_reg(hwअगर);
		जाओ err_hwअगर_पढ़ोy;
	पूर्ण

	पढ़ो_hwअगर_attr(hwअगर);

	अगर (HINIC_IS_PF(hwअगर))
		set_ppf(hwअगर);

	/* No transactionss beक्रमe DMA is initialized */
	dma_attr_init(hwअगर);
	वापस 0;

err_hwअगर_पढ़ोy:
	iounmap(hwअगर->पूर्णांकr_regs_base);

err_map_पूर्णांकr_bar:
	iounmap(hwअगर->cfg_regs_bar);

	वापस err;
पूर्ण

/**
 * hinic_मुक्त_hwअगर - मुक्त the HW पूर्णांकerface
 * @hwअगर: the HW पूर्णांकerface of a pci function device
 **/
व्योम hinic_मुक्त_hwअगर(काष्ठा hinic_hwअगर *hwअगर)
अणु
	iounmap(hwअगर->पूर्णांकr_regs_base);
	iounmap(hwअगर->cfg_regs_bar);
पूर्ण
