<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IOMMU API क्रम Rockchip
 *
 * Module Authors:	Simon Xue <xxm@rock-chips.com>
 *			Daniel Kurtz <djkurtz@chromium.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/compiler.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-iommu.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iommu.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_iommu.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

/** MMU रेजिस्टर offsets */
#घोषणा RK_MMU_DTE_ADDR		0x00	/* Directory table address */
#घोषणा RK_MMU_STATUS		0x04
#घोषणा RK_MMU_COMMAND		0x08
#घोषणा RK_MMU_PAGE_FAULT_ADDR	0x0C	/* IOVA of last page fault */
#घोषणा RK_MMU_ZAP_ONE_LINE	0x10	/* Shootकरोwn one IOTLB entry */
#घोषणा RK_MMU_INT_RAWSTAT	0x14	/* IRQ status ignoring mask */
#घोषणा RK_MMU_INT_CLEAR	0x18	/* Acknowledge and re-arm irq */
#घोषणा RK_MMU_INT_MASK		0x1C	/* IRQ enable */
#घोषणा RK_MMU_INT_STATUS	0x20	/* IRQ status after masking */
#घोषणा RK_MMU_AUTO_GATING	0x24

#घोषणा DTE_ADDR_DUMMY		0xCAFEBABE

#घोषणा RK_MMU_POLL_PERIOD_US		100
#घोषणा RK_MMU_FORCE_RESET_TIMEOUT_US	100000
#घोषणा RK_MMU_POLL_TIMEOUT_US		1000

/* RK_MMU_STATUS fields */
#घोषणा RK_MMU_STATUS_PAGING_ENABLED       BIT(0)
#घोषणा RK_MMU_STATUS_PAGE_FAULT_ACTIVE    BIT(1)
#घोषणा RK_MMU_STATUS_STALL_ACTIVE         BIT(2)
#घोषणा RK_MMU_STATUS_IDLE                 BIT(3)
#घोषणा RK_MMU_STATUS_REPLAY_BUFFER_EMPTY  BIT(4)
#घोषणा RK_MMU_STATUS_PAGE_FAULT_IS_WRITE  BIT(5)
#घोषणा RK_MMU_STATUS_STALL_NOT_ACTIVE     BIT(31)

/* RK_MMU_COMMAND command values */
#घोषणा RK_MMU_CMD_ENABLE_PAGING    0  /* Enable memory translation */
#घोषणा RK_MMU_CMD_DISABLE_PAGING   1  /* Disable memory translation */
#घोषणा RK_MMU_CMD_ENABLE_STALL     2  /* Stall paging to allow other cmds */
#घोषणा RK_MMU_CMD_DISABLE_STALL    3  /* Stop stall re-enables paging */
#घोषणा RK_MMU_CMD_ZAP_CACHE        4  /* Shoot करोwn entire IOTLB */
#घोषणा RK_MMU_CMD_PAGE_FAULT_DONE  5  /* Clear page fault */
#घोषणा RK_MMU_CMD_FORCE_RESET      6  /* Reset all रेजिस्टरs */

/* RK_MMU_INT_* रेजिस्टर fields */
#घोषणा RK_MMU_IRQ_PAGE_FAULT    0x01  /* page fault */
#घोषणा RK_MMU_IRQ_BUS_ERROR     0x02  /* bus पढ़ो error */
#घोषणा RK_MMU_IRQ_MASK          (RK_MMU_IRQ_PAGE_FAULT | RK_MMU_IRQ_BUS_ERROR)

#घोषणा NUM_DT_ENTRIES 1024
#घोषणा NUM_PT_ENTRIES 1024

#घोषणा SPAGE_ORDER 12
#घोषणा SPAGE_SIZE (1 << SPAGE_ORDER)

 /*
  * Support mapping any size that fits in one page table:
  *   4 KiB to 4 MiB
  */
#घोषणा RK_IOMMU_PGSIZE_BITMAP 0x007ff000

काष्ठा rk_iommu_करोमुख्य अणु
	काष्ठा list_head iommus;
	u32 *dt; /* page directory table */
	dma_addr_t dt_dma;
	spinlock_t iommus_lock; /* lock क्रम iommus list */
	spinlock_t dt_lock; /* lock क्रम modअगरying page directory table */

	काष्ठा iommu_करोमुख्य करोमुख्य;
पूर्ण;

/* list of घड़ीs required by IOMMU */
अटल स्थिर अक्षर * स्थिर rk_iommu_घड़ीs[] = अणु
	"aclk", "iface",
पूर्ण;

काष्ठा rk_iommu अणु
	काष्ठा device *dev;
	व्योम __iomem **bases;
	पूर्णांक num_mmu;
	पूर्णांक num_irq;
	काष्ठा clk_bulk_data *घड़ीs;
	पूर्णांक num_घड़ीs;
	bool reset_disabled;
	काष्ठा iommu_device iommu;
	काष्ठा list_head node; /* entry in rk_iommu_करोमुख्य.iommus */
	काष्ठा iommu_करोमुख्य *करोमुख्य; /* करोमुख्य to which iommu is attached */
	काष्ठा iommu_group *group;
पूर्ण;

काष्ठा rk_iommudata अणु
	काष्ठा device_link *link; /* runसमय PM link from IOMMU to master */
	काष्ठा rk_iommu *iommu;
पूर्ण;

अटल काष्ठा device *dma_dev;

अटल अंतरभूत व्योम rk_table_flush(काष्ठा rk_iommu_करोमुख्य *करोm, dma_addr_t dma,
				  अचिन्हित पूर्णांक count)
अणु
	माप_प्रकार size = count * माप(u32); /* count of u32 entry */

	dma_sync_single_क्रम_device(dma_dev, dma, size, DMA_TO_DEVICE);
पूर्ण

अटल काष्ठा rk_iommu_करोमुख्य *to_rk_करोमुख्य(काष्ठा iommu_करोमुख्य *करोm)
अणु
	वापस container_of(करोm, काष्ठा rk_iommu_करोमुख्य, करोमुख्य);
पूर्ण

/*
 * The Rockchip rk3288 iommu uses a 2-level page table.
 * The first level is the "Directory Table" (DT).
 * The DT consists of 1024 4-byte Directory Table Entries (DTEs), each poपूर्णांकing
 * to a "Page Table".
 * The second level is the 1024 Page Tables (PT).
 * Each PT consists of 1024 4-byte Page Table Entries (PTEs), each poपूर्णांकing to
 * a 4 KB page of physical memory.
 *
 * The DT and each PT fits in a single 4 KB page (4-bytes * 1024 entries).
 * Each iommu device has a MMU_DTE_ADDR रेजिस्टर that contains the physical
 * address of the start of the DT page.
 *
 * The काष्ठाure of the page table is as follows:
 *
 *                   DT
 * MMU_DTE_ADDR -> +-----+
 *                 |     |
 *                 +-----+     PT
 *                 | DTE | -> +-----+
 *                 +-----+    |     |     Memory
 *                 |     |    +-----+     Page
 *                 |     |    | PTE | -> +-----+
 *                 +-----+    +-----+    |     |
 *                            |     |    |     |
 *                            |     |    |     |
 *                            +-----+    |     |
 *                                       |     |
 *                                       |     |
 *                                       +-----+
 */

/*
 * Each DTE has a PT address and a valid bit:
 * +---------------------+-----------+-+
 * | PT address          | Reserved  |V|
 * +---------------------+-----------+-+
 *  31:12 - PT address (PTs always starts on a 4 KB boundary)
 *  11: 1 - Reserved
 *      0 - 1 अगर PT @ PT address is valid
 */
#घोषणा RK_DTE_PT_ADDRESS_MASK    0xfffff000
#घोषणा RK_DTE_PT_VALID           BIT(0)

अटल अंतरभूत phys_addr_t rk_dte_pt_address(u32 dte)
अणु
	वापस (phys_addr_t)dte & RK_DTE_PT_ADDRESS_MASK;
पूर्ण

अटल अंतरभूत bool rk_dte_is_pt_valid(u32 dte)
अणु
	वापस dte & RK_DTE_PT_VALID;
पूर्ण

अटल अंतरभूत u32 rk_mk_dte(dma_addr_t pt_dma)
अणु
	वापस (pt_dma & RK_DTE_PT_ADDRESS_MASK) | RK_DTE_PT_VALID;
पूर्ण

/*
 * Each PTE has a Page address, some flags and a valid bit:
 * +---------------------+---+-------+-+
 * | Page address        |Rsv| Flags |V|
 * +---------------------+---+-------+-+
 *  31:12 - Page address (Pages always start on a 4 KB boundary)
 *  11: 9 - Reserved
 *   8: 1 - Flags
 *      8 - Read allocate - allocate cache space on पढ़ो misses
 *      7 - Read cache - enable cache & prefetch of data
 *      6 - Write buffer - enable delaying ग_लिखोs on their way to memory
 *      5 - Write allocate - allocate cache space on ग_लिखो misses
 *      4 - Write cache - dअगरferent ग_लिखोs can be merged together
 *      3 - Override cache attributes
 *          अगर 1, bits 4-8 control cache attributes
 *          अगर 0, the प्रणाली bus शेषs are used
 *      2 - Writable
 *      1 - Readable
 *      0 - 1 अगर Page @ Page address is valid
 */
#घोषणा RK_PTE_PAGE_ADDRESS_MASK  0xfffff000
#घोषणा RK_PTE_PAGE_FLAGS_MASK    0x000001fe
#घोषणा RK_PTE_PAGE_WRITABLE      BIT(2)
#घोषणा RK_PTE_PAGE_READABLE      BIT(1)
#घोषणा RK_PTE_PAGE_VALID         BIT(0)

अटल अंतरभूत phys_addr_t rk_pte_page_address(u32 pte)
अणु
	वापस (phys_addr_t)pte & RK_PTE_PAGE_ADDRESS_MASK;
पूर्ण

अटल अंतरभूत bool rk_pte_is_page_valid(u32 pte)
अणु
	वापस pte & RK_PTE_PAGE_VALID;
पूर्ण

/* TODO: set cache flags per prot IOMMU_CACHE */
अटल u32 rk_mk_pte(phys_addr_t page, पूर्णांक prot)
अणु
	u32 flags = 0;
	flags |= (prot & IOMMU_READ) ? RK_PTE_PAGE_READABLE : 0;
	flags |= (prot & IOMMU_WRITE) ? RK_PTE_PAGE_WRITABLE : 0;
	page &= RK_PTE_PAGE_ADDRESS_MASK;
	वापस page | flags | RK_PTE_PAGE_VALID;
पूर्ण

अटल u32 rk_mk_pte_invalid(u32 pte)
अणु
	वापस pte & ~RK_PTE_PAGE_VALID;
पूर्ण

/*
 * rk3288 iova (IOMMU Virtual Address) क्रमmat
 *  31       22.21       12.11          0
 * +-----------+-----------+-------------+
 * | DTE index | PTE index | Page offset |
 * +-----------+-----------+-------------+
 *  31:22 - DTE index   - index of DTE in DT
 *  21:12 - PTE index   - index of PTE in PT @ DTE.pt_address
 *  11: 0 - Page offset - offset पूर्णांकo page @ PTE.page_address
 */
#घोषणा RK_IOVA_DTE_MASK    0xffc00000
#घोषणा RK_IOVA_DTE_SHIFT   22
#घोषणा RK_IOVA_PTE_MASK    0x003ff000
#घोषणा RK_IOVA_PTE_SHIFT   12
#घोषणा RK_IOVA_PAGE_MASK   0x00000fff
#घोषणा RK_IOVA_PAGE_SHIFT  0

अटल u32 rk_iova_dte_index(dma_addr_t iova)
अणु
	वापस (u32)(iova & RK_IOVA_DTE_MASK) >> RK_IOVA_DTE_SHIFT;
पूर्ण

अटल u32 rk_iova_pte_index(dma_addr_t iova)
अणु
	वापस (u32)(iova & RK_IOVA_PTE_MASK) >> RK_IOVA_PTE_SHIFT;
पूर्ण

अटल u32 rk_iova_page_offset(dma_addr_t iova)
अणु
	वापस (u32)(iova & RK_IOVA_PAGE_MASK) >> RK_IOVA_PAGE_SHIFT;
पूर्ण

अटल u32 rk_iommu_पढ़ो(व्योम __iomem *base, u32 offset)
अणु
	वापस पढ़ोl(base + offset);
पूर्ण

अटल व्योम rk_iommu_ग_लिखो(व्योम __iomem *base, u32 offset, u32 value)
अणु
	ग_लिखोl(value, base + offset);
पूर्ण

अटल व्योम rk_iommu_command(काष्ठा rk_iommu *iommu, u32 command)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < iommu->num_mmu; i++)
		ग_लिखोl(command, iommu->bases[i] + RK_MMU_COMMAND);
पूर्ण

अटल व्योम rk_iommu_base_command(व्योम __iomem *base, u32 command)
अणु
	ग_लिखोl(command, base + RK_MMU_COMMAND);
पूर्ण
अटल व्योम rk_iommu_zap_lines(काष्ठा rk_iommu *iommu, dma_addr_t ioबहु_शुरू,
			       माप_प्रकार size)
अणु
	पूर्णांक i;
	dma_addr_t ioबहु_पूर्ण = ioबहु_शुरू + size;
	/*
	 * TODO(djkurtz): Figure out when it is more efficient to shootकरोwn the
	 * entire iotlb rather than iterate over inभागidual iovas.
	 */
	क्रम (i = 0; i < iommu->num_mmu; i++) अणु
		dma_addr_t iova;

		क्रम (iova = ioबहु_शुरू; iova < ioबहु_पूर्ण; iova += SPAGE_SIZE)
			rk_iommu_ग_लिखो(iommu->bases[i], RK_MMU_ZAP_ONE_LINE, iova);
	पूर्ण
पूर्ण

अटल bool rk_iommu_is_stall_active(काष्ठा rk_iommu *iommu)
अणु
	bool active = true;
	पूर्णांक i;

	क्रम (i = 0; i < iommu->num_mmu; i++)
		active &= !!(rk_iommu_पढ़ो(iommu->bases[i], RK_MMU_STATUS) &
					   RK_MMU_STATUS_STALL_ACTIVE);

	वापस active;
पूर्ण

अटल bool rk_iommu_is_paging_enabled(काष्ठा rk_iommu *iommu)
अणु
	bool enable = true;
	पूर्णांक i;

	क्रम (i = 0; i < iommu->num_mmu; i++)
		enable &= !!(rk_iommu_पढ़ो(iommu->bases[i], RK_MMU_STATUS) &
					   RK_MMU_STATUS_PAGING_ENABLED);

	वापस enable;
पूर्ण

अटल bool rk_iommu_is_reset_करोne(काष्ठा rk_iommu *iommu)
अणु
	bool करोne = true;
	पूर्णांक i;

	क्रम (i = 0; i < iommu->num_mmu; i++)
		करोne &= rk_iommu_पढ़ो(iommu->bases[i], RK_MMU_DTE_ADDR) == 0;

	वापस करोne;
पूर्ण

अटल पूर्णांक rk_iommu_enable_stall(काष्ठा rk_iommu *iommu)
अणु
	पूर्णांक ret, i;
	bool val;

	अगर (rk_iommu_is_stall_active(iommu))
		वापस 0;

	/* Stall can only be enabled अगर paging is enabled */
	अगर (!rk_iommu_is_paging_enabled(iommu))
		वापस 0;

	rk_iommu_command(iommu, RK_MMU_CMD_ENABLE_STALL);

	ret = पढ़ोx_poll_समयout(rk_iommu_is_stall_active, iommu, val,
				 val, RK_MMU_POLL_PERIOD_US,
				 RK_MMU_POLL_TIMEOUT_US);
	अगर (ret)
		क्रम (i = 0; i < iommu->num_mmu; i++)
			dev_err(iommu->dev, "Enable stall request timed out, status: %#08x\n",
				rk_iommu_पढ़ो(iommu->bases[i], RK_MMU_STATUS));

	वापस ret;
पूर्ण

अटल पूर्णांक rk_iommu_disable_stall(काष्ठा rk_iommu *iommu)
अणु
	पूर्णांक ret, i;
	bool val;

	अगर (!rk_iommu_is_stall_active(iommu))
		वापस 0;

	rk_iommu_command(iommu, RK_MMU_CMD_DISABLE_STALL);

	ret = पढ़ोx_poll_समयout(rk_iommu_is_stall_active, iommu, val,
				 !val, RK_MMU_POLL_PERIOD_US,
				 RK_MMU_POLL_TIMEOUT_US);
	अगर (ret)
		क्रम (i = 0; i < iommu->num_mmu; i++)
			dev_err(iommu->dev, "Disable stall request timed out, status: %#08x\n",
				rk_iommu_पढ़ो(iommu->bases[i], RK_MMU_STATUS));

	वापस ret;
पूर्ण

अटल पूर्णांक rk_iommu_enable_paging(काष्ठा rk_iommu *iommu)
अणु
	पूर्णांक ret, i;
	bool val;

	अगर (rk_iommu_is_paging_enabled(iommu))
		वापस 0;

	rk_iommu_command(iommu, RK_MMU_CMD_ENABLE_PAGING);

	ret = पढ़ोx_poll_समयout(rk_iommu_is_paging_enabled, iommu, val,
				 val, RK_MMU_POLL_PERIOD_US,
				 RK_MMU_POLL_TIMEOUT_US);
	अगर (ret)
		क्रम (i = 0; i < iommu->num_mmu; i++)
			dev_err(iommu->dev, "Enable paging request timed out, status: %#08x\n",
				rk_iommu_पढ़ो(iommu->bases[i], RK_MMU_STATUS));

	वापस ret;
पूर्ण

अटल पूर्णांक rk_iommu_disable_paging(काष्ठा rk_iommu *iommu)
अणु
	पूर्णांक ret, i;
	bool val;

	अगर (!rk_iommu_is_paging_enabled(iommu))
		वापस 0;

	rk_iommu_command(iommu, RK_MMU_CMD_DISABLE_PAGING);

	ret = पढ़ोx_poll_समयout(rk_iommu_is_paging_enabled, iommu, val,
				 !val, RK_MMU_POLL_PERIOD_US,
				 RK_MMU_POLL_TIMEOUT_US);
	अगर (ret)
		क्रम (i = 0; i < iommu->num_mmu; i++)
			dev_err(iommu->dev, "Disable paging request timed out, status: %#08x\n",
				rk_iommu_पढ़ो(iommu->bases[i], RK_MMU_STATUS));

	वापस ret;
पूर्ण

अटल पूर्णांक rk_iommu_क्रमce_reset(काष्ठा rk_iommu *iommu)
अणु
	पूर्णांक ret, i;
	u32 dte_addr;
	bool val;

	अगर (iommu->reset_disabled)
		वापस 0;

	/*
	 * Check अगर रेजिस्टर DTE_ADDR is working by writing DTE_ADDR_DUMMY
	 * and verअगरying that upper 5 nybbles are पढ़ो back.
	 */
	क्रम (i = 0; i < iommu->num_mmu; i++) अणु
		rk_iommu_ग_लिखो(iommu->bases[i], RK_MMU_DTE_ADDR, DTE_ADDR_DUMMY);

		dte_addr = rk_iommu_पढ़ो(iommu->bases[i], RK_MMU_DTE_ADDR);
		अगर (dte_addr != (DTE_ADDR_DUMMY & RK_DTE_PT_ADDRESS_MASK)) अणु
			dev_err(iommu->dev, "Error during raw reset. MMU_DTE_ADDR is not functioning\n");
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	rk_iommu_command(iommu, RK_MMU_CMD_FORCE_RESET);

	ret = पढ़ोx_poll_समयout(rk_iommu_is_reset_करोne, iommu, val,
				 val, RK_MMU_FORCE_RESET_TIMEOUT_US,
				 RK_MMU_POLL_TIMEOUT_US);
	अगर (ret) अणु
		dev_err(iommu->dev, "FORCE_RESET command timed out\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम log_iova(काष्ठा rk_iommu *iommu, पूर्णांक index, dma_addr_t iova)
अणु
	व्योम __iomem *base = iommu->bases[index];
	u32 dte_index, pte_index, page_offset;
	u32 mmu_dte_addr;
	phys_addr_t mmu_dte_addr_phys, dte_addr_phys;
	u32 *dte_addr;
	u32 dte;
	phys_addr_t pte_addr_phys = 0;
	u32 *pte_addr = शून्य;
	u32 pte = 0;
	phys_addr_t page_addr_phys = 0;
	u32 page_flags = 0;

	dte_index = rk_iova_dte_index(iova);
	pte_index = rk_iova_pte_index(iova);
	page_offset = rk_iova_page_offset(iova);

	mmu_dte_addr = rk_iommu_पढ़ो(base, RK_MMU_DTE_ADDR);
	mmu_dte_addr_phys = (phys_addr_t)mmu_dte_addr;

	dte_addr_phys = mmu_dte_addr_phys + (4 * dte_index);
	dte_addr = phys_to_virt(dte_addr_phys);
	dte = *dte_addr;

	अगर (!rk_dte_is_pt_valid(dte))
		जाओ prपूर्णांक_it;

	pte_addr_phys = rk_dte_pt_address(dte) + (pte_index * 4);
	pte_addr = phys_to_virt(pte_addr_phys);
	pte = *pte_addr;

	अगर (!rk_pte_is_page_valid(pte))
		जाओ prपूर्णांक_it;

	page_addr_phys = rk_pte_page_address(pte) + page_offset;
	page_flags = pte & RK_PTE_PAGE_FLAGS_MASK;

prपूर्णांक_it:
	dev_err(iommu->dev, "iova = %pad: dte_index: %#03x pte_index: %#03x page_offset: %#03x\n",
		&iova, dte_index, pte_index, page_offset);
	dev_err(iommu->dev, "mmu_dte_addr: %pa dte@%pa: %#08x valid: %u pte@%pa: %#08x valid: %u page@%pa flags: %#03x\n",
		&mmu_dte_addr_phys, &dte_addr_phys, dte,
		rk_dte_is_pt_valid(dte), &pte_addr_phys, pte,
		rk_pte_is_page_valid(pte), &page_addr_phys, page_flags);
पूर्ण

अटल irqवापस_t rk_iommu_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rk_iommu *iommu = dev_id;
	u32 status;
	u32 पूर्णांक_status;
	dma_addr_t iova;
	irqवापस_t ret = IRQ_NONE;
	पूर्णांक i, err;

	err = pm_runसमय_get_अगर_in_use(iommu->dev);
	अगर (!err || WARN_ON_ONCE(err < 0))
		वापस ret;

	अगर (WARN_ON(clk_bulk_enable(iommu->num_घड़ीs, iommu->घड़ीs)))
		जाओ out;

	क्रम (i = 0; i < iommu->num_mmu; i++) अणु
		पूर्णांक_status = rk_iommu_पढ़ो(iommu->bases[i], RK_MMU_INT_STATUS);
		अगर (पूर्णांक_status == 0)
			जारी;

		ret = IRQ_HANDLED;
		iova = rk_iommu_पढ़ो(iommu->bases[i], RK_MMU_PAGE_FAULT_ADDR);

		अगर (पूर्णांक_status & RK_MMU_IRQ_PAGE_FAULT) अणु
			पूर्णांक flags;

			status = rk_iommu_पढ़ो(iommu->bases[i], RK_MMU_STATUS);
			flags = (status & RK_MMU_STATUS_PAGE_FAULT_IS_WRITE) ?
					IOMMU_FAULT_WRITE : IOMMU_FAULT_READ;

			dev_err(iommu->dev, "Page fault at %pad of type %s\n",
				&iova,
				(flags == IOMMU_FAULT_WRITE) ? "write" : "read");

			log_iova(iommu, i, iova);

			/*
			 * Report page fault to any installed handlers.
			 * Ignore the वापस code, though, since we always zap cache
			 * and clear the page fault anyway.
			 */
			अगर (iommu->करोमुख्य)
				report_iommu_fault(iommu->करोमुख्य, iommu->dev, iova,
						   flags);
			अन्यथा
				dev_err(iommu->dev, "Page fault while iommu not attached to domain?\n");

			rk_iommu_base_command(iommu->bases[i], RK_MMU_CMD_ZAP_CACHE);
			rk_iommu_base_command(iommu->bases[i], RK_MMU_CMD_PAGE_FAULT_DONE);
		पूर्ण

		अगर (पूर्णांक_status & RK_MMU_IRQ_BUS_ERROR)
			dev_err(iommu->dev, "BUS_ERROR occurred at %pad\n", &iova);

		अगर (पूर्णांक_status & ~RK_MMU_IRQ_MASK)
			dev_err(iommu->dev, "unexpected int_status: %#08x\n",
				पूर्णांक_status);

		rk_iommu_ग_लिखो(iommu->bases[i], RK_MMU_INT_CLEAR, पूर्णांक_status);
	पूर्ण

	clk_bulk_disable(iommu->num_घड़ीs, iommu->घड़ीs);

out:
	pm_runसमय_put(iommu->dev);
	वापस ret;
पूर्ण

अटल phys_addr_t rk_iommu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य,
					 dma_addr_t iova)
अणु
	काष्ठा rk_iommu_करोमुख्य *rk_करोमुख्य = to_rk_करोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ flags;
	phys_addr_t pt_phys, phys = 0;
	u32 dte, pte;
	u32 *page_table;

	spin_lock_irqsave(&rk_करोमुख्य->dt_lock, flags);

	dte = rk_करोमुख्य->dt[rk_iova_dte_index(iova)];
	अगर (!rk_dte_is_pt_valid(dte))
		जाओ out;

	pt_phys = rk_dte_pt_address(dte);
	page_table = (u32 *)phys_to_virt(pt_phys);
	pte = page_table[rk_iova_pte_index(iova)];
	अगर (!rk_pte_is_page_valid(pte))
		जाओ out;

	phys = rk_pte_page_address(pte) + rk_iova_page_offset(iova);
out:
	spin_unlock_irqrestore(&rk_करोमुख्य->dt_lock, flags);

	वापस phys;
पूर्ण

अटल व्योम rk_iommu_zap_iova(काष्ठा rk_iommu_करोमुख्य *rk_करोमुख्य,
			      dma_addr_t iova, माप_प्रकार size)
अणु
	काष्ठा list_head *pos;
	अचिन्हित दीर्घ flags;

	/* shootकरोwn these iova from all iommus using this करोमुख्य */
	spin_lock_irqsave(&rk_करोमुख्य->iommus_lock, flags);
	list_क्रम_each(pos, &rk_करोमुख्य->iommus) अणु
		काष्ठा rk_iommu *iommu;
		पूर्णांक ret;

		iommu = list_entry(pos, काष्ठा rk_iommu, node);

		/* Only zap TLBs of IOMMUs that are घातered on. */
		ret = pm_runसमय_get_अगर_in_use(iommu->dev);
		अगर (WARN_ON_ONCE(ret < 0))
			जारी;
		अगर (ret) अणु
			WARN_ON(clk_bulk_enable(iommu->num_घड़ीs,
						iommu->घड़ीs));
			rk_iommu_zap_lines(iommu, iova, size);
			clk_bulk_disable(iommu->num_घड़ीs, iommu->घड़ीs);
			pm_runसमय_put(iommu->dev);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&rk_करोमुख्य->iommus_lock, flags);
पूर्ण

अटल व्योम rk_iommu_zap_iova_first_last(काष्ठा rk_iommu_करोमुख्य *rk_करोमुख्य,
					 dma_addr_t iova, माप_प्रकार size)
अणु
	rk_iommu_zap_iova(rk_करोमुख्य, iova, SPAGE_SIZE);
	अगर (size > SPAGE_SIZE)
		rk_iommu_zap_iova(rk_करोमुख्य, iova + size - SPAGE_SIZE,
					SPAGE_SIZE);
पूर्ण

अटल u32 *rk_dte_get_page_table(काष्ठा rk_iommu_करोमुख्य *rk_करोमुख्य,
				  dma_addr_t iova)
अणु
	u32 *page_table, *dte_addr;
	u32 dte_index, dte;
	phys_addr_t pt_phys;
	dma_addr_t pt_dma;

	निश्चित_spin_locked(&rk_करोमुख्य->dt_lock);

	dte_index = rk_iova_dte_index(iova);
	dte_addr = &rk_करोमुख्य->dt[dte_index];
	dte = *dte_addr;
	अगर (rk_dte_is_pt_valid(dte))
		जाओ करोne;

	page_table = (u32 *)get_zeroed_page(GFP_ATOMIC | GFP_DMA32);
	अगर (!page_table)
		वापस ERR_PTR(-ENOMEM);

	pt_dma = dma_map_single(dma_dev, page_table, SPAGE_SIZE, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dma_dev, pt_dma)) अणु
		dev_err(dma_dev, "DMA mapping error while allocating page table\n");
		मुक्त_page((अचिन्हित दीर्घ)page_table);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	dte = rk_mk_dte(pt_dma);
	*dte_addr = dte;

	rk_table_flush(rk_करोमुख्य, pt_dma, NUM_PT_ENTRIES);
	rk_table_flush(rk_करोमुख्य,
		       rk_करोमुख्य->dt_dma + dte_index * माप(u32), 1);
करोne:
	pt_phys = rk_dte_pt_address(dte);
	वापस (u32 *)phys_to_virt(pt_phys);
पूर्ण

अटल माप_प्रकार rk_iommu_unmap_iova(काष्ठा rk_iommu_करोमुख्य *rk_करोमुख्य,
				  u32 *pte_addr, dma_addr_t pte_dma,
				  माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक pte_count;
	अचिन्हित पूर्णांक pte_total = size / SPAGE_SIZE;

	निश्चित_spin_locked(&rk_करोमुख्य->dt_lock);

	क्रम (pte_count = 0; pte_count < pte_total; pte_count++) अणु
		u32 pte = pte_addr[pte_count];
		अगर (!rk_pte_is_page_valid(pte))
			अवरोध;

		pte_addr[pte_count] = rk_mk_pte_invalid(pte);
	पूर्ण

	rk_table_flush(rk_करोमुख्य, pte_dma, pte_count);

	वापस pte_count * SPAGE_SIZE;
पूर्ण

अटल पूर्णांक rk_iommu_map_iova(काष्ठा rk_iommu_करोमुख्य *rk_करोमुख्य, u32 *pte_addr,
			     dma_addr_t pte_dma, dma_addr_t iova,
			     phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot)
अणु
	अचिन्हित पूर्णांक pte_count;
	अचिन्हित पूर्णांक pte_total = size / SPAGE_SIZE;
	phys_addr_t page_phys;

	निश्चित_spin_locked(&rk_करोमुख्य->dt_lock);

	क्रम (pte_count = 0; pte_count < pte_total; pte_count++) अणु
		u32 pte = pte_addr[pte_count];

		अगर (rk_pte_is_page_valid(pte))
			जाओ unwind;

		pte_addr[pte_count] = rk_mk_pte(paddr, prot);

		paddr += SPAGE_SIZE;
	पूर्ण

	rk_table_flush(rk_करोमुख्य, pte_dma, pte_total);

	/*
	 * Zap the first and last iova to evict from iotlb any previously
	 * mapped cachelines holding stale values क्रम its dte and pte.
	 * We only zap the first and last iova, since only they could have
	 * dte or pte shared with an existing mapping.
	 */
	rk_iommu_zap_iova_first_last(rk_करोमुख्य, iova, size);

	वापस 0;
unwind:
	/* Unmap the range of iovas that we just mapped */
	rk_iommu_unmap_iova(rk_करोमुख्य, pte_addr, pte_dma,
			    pte_count * SPAGE_SIZE);

	iova += pte_count * SPAGE_SIZE;
	page_phys = rk_pte_page_address(pte_addr[pte_count]);
	pr_err("iova: %pad already mapped to %pa cannot remap to phys: %pa prot: %#x\n",
	       &iova, &page_phys, &paddr, prot);

	वापस -EADDRINUSE;
पूर्ण

अटल पूर्णांक rk_iommu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ _iova,
			phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp)
अणु
	काष्ठा rk_iommu_करोमुख्य *rk_करोमुख्य = to_rk_करोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ flags;
	dma_addr_t pte_dma, iova = (dma_addr_t)_iova;
	u32 *page_table, *pte_addr;
	u32 dte_index, pte_index;
	पूर्णांक ret;

	spin_lock_irqsave(&rk_करोमुख्य->dt_lock, flags);

	/*
	 * pgsize_biपंचांगap specअगरies iova sizes that fit in one page table
	 * (1024 4-KiB pages = 4 MiB).
	 * So, size will always be 4096 <= size <= 4194304.
	 * Since iommu_map() guarantees that both iova and size will be
	 * aligned, we will always only be mapping from a single dte here.
	 */
	page_table = rk_dte_get_page_table(rk_करोमुख्य, iova);
	अगर (IS_ERR(page_table)) अणु
		spin_unlock_irqrestore(&rk_करोमुख्य->dt_lock, flags);
		वापस PTR_ERR(page_table);
	पूर्ण

	dte_index = rk_करोमुख्य->dt[rk_iova_dte_index(iova)];
	pte_index = rk_iova_pte_index(iova);
	pte_addr = &page_table[pte_index];
	pte_dma = rk_dte_pt_address(dte_index) + pte_index * माप(u32);
	ret = rk_iommu_map_iova(rk_करोमुख्य, pte_addr, pte_dma, iova,
				paddr, size, prot);

	spin_unlock_irqrestore(&rk_करोमुख्य->dt_lock, flags);

	वापस ret;
पूर्ण

अटल माप_प्रकार rk_iommu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ _iova,
			     माप_प्रकार size, काष्ठा iommu_iotlb_gather *gather)
अणु
	काष्ठा rk_iommu_करोमुख्य *rk_करोमुख्य = to_rk_करोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ flags;
	dma_addr_t pte_dma, iova = (dma_addr_t)_iova;
	phys_addr_t pt_phys;
	u32 dte;
	u32 *pte_addr;
	माप_प्रकार unmap_size;

	spin_lock_irqsave(&rk_करोमुख्य->dt_lock, flags);

	/*
	 * pgsize_biपंचांगap specअगरies iova sizes that fit in one page table
	 * (1024 4-KiB pages = 4 MiB).
	 * So, size will always be 4096 <= size <= 4194304.
	 * Since iommu_unmap() guarantees that both iova and size will be
	 * aligned, we will always only be unmapping from a single dte here.
	 */
	dte = rk_करोमुख्य->dt[rk_iova_dte_index(iova)];
	/* Just वापस 0 अगर iova is unmapped */
	अगर (!rk_dte_is_pt_valid(dte)) अणु
		spin_unlock_irqrestore(&rk_करोमुख्य->dt_lock, flags);
		वापस 0;
	पूर्ण

	pt_phys = rk_dte_pt_address(dte);
	pte_addr = (u32 *)phys_to_virt(pt_phys) + rk_iova_pte_index(iova);
	pte_dma = pt_phys + rk_iova_pte_index(iova) * माप(u32);
	unmap_size = rk_iommu_unmap_iova(rk_करोमुख्य, pte_addr, pte_dma, size);

	spin_unlock_irqrestore(&rk_करोमुख्य->dt_lock, flags);

	/* Shootकरोwn iotlb entries क्रम iova range that was just unmapped */
	rk_iommu_zap_iova(rk_करोमुख्य, iova, unmap_size);

	वापस unmap_size;
पूर्ण

अटल काष्ठा rk_iommu *rk_iommu_from_dev(काष्ठा device *dev)
अणु
	काष्ठा rk_iommudata *data = dev_iommu_priv_get(dev);

	वापस data ? data->iommu : शून्य;
पूर्ण

/* Must be called with iommu घातered on and attached */
अटल व्योम rk_iommu_disable(काष्ठा rk_iommu *iommu)
अणु
	पूर्णांक i;

	/* Ignore error जबतक disabling, just keep going */
	WARN_ON(clk_bulk_enable(iommu->num_घड़ीs, iommu->घड़ीs));
	rk_iommu_enable_stall(iommu);
	rk_iommu_disable_paging(iommu);
	क्रम (i = 0; i < iommu->num_mmu; i++) अणु
		rk_iommu_ग_लिखो(iommu->bases[i], RK_MMU_INT_MASK, 0);
		rk_iommu_ग_लिखो(iommu->bases[i], RK_MMU_DTE_ADDR, 0);
	पूर्ण
	rk_iommu_disable_stall(iommu);
	clk_bulk_disable(iommu->num_घड़ीs, iommu->घड़ीs);
पूर्ण

/* Must be called with iommu घातered on and attached */
अटल पूर्णांक rk_iommu_enable(काष्ठा rk_iommu *iommu)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = iommu->करोमुख्य;
	काष्ठा rk_iommu_करोमुख्य *rk_करोमुख्य = to_rk_करोमुख्य(करोमुख्य);
	पूर्णांक ret, i;

	ret = clk_bulk_enable(iommu->num_घड़ीs, iommu->घड़ीs);
	अगर (ret)
		वापस ret;

	ret = rk_iommu_enable_stall(iommu);
	अगर (ret)
		जाओ out_disable_घड़ीs;

	ret = rk_iommu_क्रमce_reset(iommu);
	अगर (ret)
		जाओ out_disable_stall;

	क्रम (i = 0; i < iommu->num_mmu; i++) अणु
		rk_iommu_ग_लिखो(iommu->bases[i], RK_MMU_DTE_ADDR,
			       rk_करोमुख्य->dt_dma);
		rk_iommu_base_command(iommu->bases[i], RK_MMU_CMD_ZAP_CACHE);
		rk_iommu_ग_लिखो(iommu->bases[i], RK_MMU_INT_MASK, RK_MMU_IRQ_MASK);
	पूर्ण

	ret = rk_iommu_enable_paging(iommu);

out_disable_stall:
	rk_iommu_disable_stall(iommu);
out_disable_घड़ीs:
	clk_bulk_disable(iommu->num_घड़ीs, iommu->घड़ीs);
	वापस ret;
पूर्ण

अटल व्योम rk_iommu_detach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				   काष्ठा device *dev)
अणु
	काष्ठा rk_iommu *iommu;
	काष्ठा rk_iommu_करोमुख्य *rk_करोमुख्य = to_rk_करोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Allow 'virtual devices' (eg drm) to detach from करोमुख्य */
	iommu = rk_iommu_from_dev(dev);
	अगर (!iommu)
		वापस;

	dev_dbg(dev, "Detaching from iommu domain\n");

	/* iommu alपढ़ोy detached */
	अगर (iommu->करोमुख्य != करोमुख्य)
		वापस;

	iommu->करोमुख्य = शून्य;

	spin_lock_irqsave(&rk_करोमुख्य->iommus_lock, flags);
	list_del_init(&iommu->node);
	spin_unlock_irqrestore(&rk_करोमुख्य->iommus_lock, flags);

	ret = pm_runसमय_get_अगर_in_use(iommu->dev);
	WARN_ON_ONCE(ret < 0);
	अगर (ret > 0) अणु
		rk_iommu_disable(iommu);
		pm_runसमय_put(iommu->dev);
	पूर्ण
पूर्ण

अटल पूर्णांक rk_iommu_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
		काष्ठा device *dev)
अणु
	काष्ठा rk_iommu *iommu;
	काष्ठा rk_iommu_करोमुख्य *rk_करोमुख्य = to_rk_करोमुख्य(करोमुख्य);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/*
	 * Allow 'virtual devices' (e.g., drm) to attach to करोमुख्य.
	 * Such a device करोes not beदीर्घ to an iommu group.
	 */
	iommu = rk_iommu_from_dev(dev);
	अगर (!iommu)
		वापस 0;

	dev_dbg(dev, "Attaching to iommu domain\n");

	/* iommu alपढ़ोy attached */
	अगर (iommu->करोमुख्य == करोमुख्य)
		वापस 0;

	अगर (iommu->करोमुख्य)
		rk_iommu_detach_device(iommu->करोमुख्य, dev);

	iommu->करोमुख्य = करोमुख्य;

	spin_lock_irqsave(&rk_करोमुख्य->iommus_lock, flags);
	list_add_tail(&iommu->node, &rk_करोमुख्य->iommus);
	spin_unlock_irqrestore(&rk_करोमुख्य->iommus_lock, flags);

	ret = pm_runसमय_get_अगर_in_use(iommu->dev);
	अगर (!ret || WARN_ON_ONCE(ret < 0))
		वापस 0;

	ret = rk_iommu_enable(iommu);
	अगर (ret)
		rk_iommu_detach_device(iommu->करोमुख्य, dev);

	pm_runसमय_put(iommu->dev);

	वापस ret;
पूर्ण

अटल काष्ठा iommu_करोमुख्य *rk_iommu_करोमुख्य_alloc(अचिन्हित type)
अणु
	काष्ठा rk_iommu_करोमुख्य *rk_करोमुख्य;

	अगर (type != IOMMU_DOMAIN_UNMANAGED && type != IOMMU_DOMAIN_DMA)
		वापस शून्य;

	अगर (!dma_dev)
		वापस शून्य;

	rk_करोमुख्य = kzalloc(माप(*rk_करोमुख्य), GFP_KERNEL);
	अगर (!rk_करोमुख्य)
		वापस शून्य;

	अगर (type == IOMMU_DOMAIN_DMA &&
	    iommu_get_dma_cookie(&rk_करोमुख्य->करोमुख्य))
		जाओ err_मुक्त_करोमुख्य;

	/*
	 * rk32xx iommus use a 2 level pagetable.
	 * Each level1 (dt) and level2 (pt) table has 1024 4-byte entries.
	 * Allocate one 4 KiB page क्रम each table.
	 */
	rk_करोमुख्य->dt = (u32 *)get_zeroed_page(GFP_KERNEL | GFP_DMA32);
	अगर (!rk_करोमुख्य->dt)
		जाओ err_put_cookie;

	rk_करोमुख्य->dt_dma = dma_map_single(dma_dev, rk_करोमुख्य->dt,
					   SPAGE_SIZE, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dma_dev, rk_करोमुख्य->dt_dma)) अणु
		dev_err(dma_dev, "DMA map error for DT\n");
		जाओ err_मुक्त_dt;
	पूर्ण

	rk_table_flush(rk_करोमुख्य, rk_करोमुख्य->dt_dma, NUM_DT_ENTRIES);

	spin_lock_init(&rk_करोमुख्य->iommus_lock);
	spin_lock_init(&rk_करोमुख्य->dt_lock);
	INIT_LIST_HEAD(&rk_करोमुख्य->iommus);

	rk_करोमुख्य->करोमुख्य.geometry.aperture_start = 0;
	rk_करोमुख्य->करोमुख्य.geometry.aperture_end   = DMA_BIT_MASK(32);
	rk_करोमुख्य->करोमुख्य.geometry.क्रमce_aperture = true;

	वापस &rk_करोमुख्य->करोमुख्य;

err_मुक्त_dt:
	मुक्त_page((अचिन्हित दीर्घ)rk_करोमुख्य->dt);
err_put_cookie:
	अगर (type == IOMMU_DOMAIN_DMA)
		iommu_put_dma_cookie(&rk_करोमुख्य->करोमुख्य);
err_मुक्त_करोमुख्य:
	kमुक्त(rk_करोमुख्य);

	वापस शून्य;
पूर्ण

अटल व्योम rk_iommu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	काष्ठा rk_iommu_करोमुख्य *rk_करोमुख्य = to_rk_करोमुख्य(करोमुख्य);
	पूर्णांक i;

	WARN_ON(!list_empty(&rk_करोमुख्य->iommus));

	क्रम (i = 0; i < NUM_DT_ENTRIES; i++) अणु
		u32 dte = rk_करोमुख्य->dt[i];
		अगर (rk_dte_is_pt_valid(dte)) अणु
			phys_addr_t pt_phys = rk_dte_pt_address(dte);
			u32 *page_table = phys_to_virt(pt_phys);
			dma_unmap_single(dma_dev, pt_phys,
					 SPAGE_SIZE, DMA_TO_DEVICE);
			मुक्त_page((अचिन्हित दीर्घ)page_table);
		पूर्ण
	पूर्ण

	dma_unmap_single(dma_dev, rk_करोमुख्य->dt_dma,
			 SPAGE_SIZE, DMA_TO_DEVICE);
	मुक्त_page((अचिन्हित दीर्घ)rk_करोमुख्य->dt);

	अगर (करोमुख्य->type == IOMMU_DOMAIN_DMA)
		iommu_put_dma_cookie(&rk_करोमुख्य->करोमुख्य);
	kमुक्त(rk_करोमुख्य);
पूर्ण

अटल काष्ठा iommu_device *rk_iommu_probe_device(काष्ठा device *dev)
अणु
	काष्ठा rk_iommudata *data;
	काष्ठा rk_iommu *iommu;

	data = dev_iommu_priv_get(dev);
	अगर (!data)
		वापस ERR_PTR(-ENODEV);

	iommu = rk_iommu_from_dev(dev);

	data->link = device_link_add(dev, iommu->dev,
				     DL_FLAG_STATELESS | DL_FLAG_PM_RUNTIME);

	वापस &iommu->iommu;
पूर्ण

अटल व्योम rk_iommu_release_device(काष्ठा device *dev)
अणु
	काष्ठा rk_iommudata *data = dev_iommu_priv_get(dev);

	device_link_del(data->link);
पूर्ण

अटल काष्ठा iommu_group *rk_iommu_device_group(काष्ठा device *dev)
अणु
	काष्ठा rk_iommu *iommu;

	iommu = rk_iommu_from_dev(dev);

	वापस iommu_group_ref_get(iommu->group);
पूर्ण

अटल पूर्णांक rk_iommu_of_xlate(काष्ठा device *dev,
			     काष्ठा of_phandle_args *args)
अणु
	काष्ठा platक्रमm_device *iommu_dev;
	काष्ठा rk_iommudata *data;

	data = devm_kzalloc(dma_dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	iommu_dev = of_find_device_by_node(args->np);

	data->iommu = platक्रमm_get_drvdata(iommu_dev);
	dev_iommu_priv_set(dev, data);

	platक्रमm_device_put(iommu_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iommu_ops rk_iommu_ops = अणु
	.करोमुख्य_alloc = rk_iommu_करोमुख्य_alloc,
	.करोमुख्य_मुक्त = rk_iommu_करोमुख्य_मुक्त,
	.attach_dev = rk_iommu_attach_device,
	.detach_dev = rk_iommu_detach_device,
	.map = rk_iommu_map,
	.unmap = rk_iommu_unmap,
	.probe_device = rk_iommu_probe_device,
	.release_device = rk_iommu_release_device,
	.iova_to_phys = rk_iommu_iova_to_phys,
	.device_group = rk_iommu_device_group,
	.pgsize_biपंचांगap = RK_IOMMU_PGSIZE_BITMAP,
	.of_xlate = rk_iommu_of_xlate,
पूर्ण;

अटल पूर्णांक rk_iommu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rk_iommu *iommu;
	काष्ठा resource *res;
	पूर्णांक num_res = pdev->num_resources;
	पूर्णांक err, i;

	iommu = devm_kzalloc(dev, माप(*iommu), GFP_KERNEL);
	अगर (!iommu)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, iommu);
	iommu->dev = dev;
	iommu->num_mmu = 0;

	iommu->bases = devm_kसुस्मृति(dev, num_res, माप(*iommu->bases),
				    GFP_KERNEL);
	अगर (!iommu->bases)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_res; i++) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, i);
		अगर (!res)
			जारी;
		iommu->bases[i] = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(iommu->bases[i]))
			जारी;
		iommu->num_mmu++;
	पूर्ण
	अगर (iommu->num_mmu == 0)
		वापस PTR_ERR(iommu->bases[0]);

	iommu->num_irq = platक्रमm_irq_count(pdev);
	अगर (iommu->num_irq < 0)
		वापस iommu->num_irq;

	iommu->reset_disabled = device_property_पढ़ो_bool(dev,
					"rockchip,disable-mmu-reset");

	iommu->num_घड़ीs = ARRAY_SIZE(rk_iommu_घड़ीs);
	iommu->घड़ीs = devm_kसुस्मृति(iommu->dev, iommu->num_घड़ीs,
				     माप(*iommu->घड़ीs), GFP_KERNEL);
	अगर (!iommu->घड़ीs)
		वापस -ENOMEM;

	क्रम (i = 0; i < iommu->num_घड़ीs; ++i)
		iommu->घड़ीs[i].id = rk_iommu_घड़ीs[i];

	/*
	 * iommu घड़ीs should be present क्रम all new devices and devicetrees
	 * but there are older devicetrees without घड़ीs out in the wild.
	 * So घड़ीs as optional क्रम the समय being.
	 */
	err = devm_clk_bulk_get(iommu->dev, iommu->num_घड़ीs, iommu->घड़ीs);
	अगर (err == -ENOENT)
		iommu->num_घड़ीs = 0;
	अन्यथा अगर (err)
		वापस err;

	err = clk_bulk_prepare(iommu->num_घड़ीs, iommu->घड़ीs);
	अगर (err)
		वापस err;

	iommu->group = iommu_group_alloc();
	अगर (IS_ERR(iommu->group)) अणु
		err = PTR_ERR(iommu->group);
		जाओ err_unprepare_घड़ीs;
	पूर्ण

	err = iommu_device_sysfs_add(&iommu->iommu, dev, शून्य, dev_name(dev));
	अगर (err)
		जाओ err_put_group;

	err = iommu_device_रेजिस्टर(&iommu->iommu, &rk_iommu_ops, dev);
	अगर (err)
		जाओ err_हटाओ_sysfs;

	/*
	 * Use the first रेजिस्टरed IOMMU device क्रम करोमुख्य to use with DMA
	 * API, since a करोमुख्य might not physically correspond to a single
	 * IOMMU device..
	 */
	अगर (!dma_dev)
		dma_dev = &pdev->dev;

	bus_set_iommu(&platक्रमm_bus_type, &rk_iommu_ops);

	pm_runसमय_enable(dev);

	क्रम (i = 0; i < iommu->num_irq; i++) अणु
		पूर्णांक irq = platक्रमm_get_irq(pdev, i);

		अगर (irq < 0)
			वापस irq;

		err = devm_request_irq(iommu->dev, irq, rk_iommu_irq,
				       IRQF_SHARED, dev_name(dev), iommu);
		अगर (err) अणु
			pm_runसमय_disable(dev);
			जाओ err_हटाओ_sysfs;
		पूर्ण
	पूर्ण

	वापस 0;
err_हटाओ_sysfs:
	iommu_device_sysfs_हटाओ(&iommu->iommu);
err_put_group:
	iommu_group_put(iommu->group);
err_unprepare_घड़ीs:
	clk_bulk_unprepare(iommu->num_घड़ीs, iommu->घड़ीs);
	वापस err;
पूर्ण

अटल व्योम rk_iommu_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rk_iommu *iommu = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < iommu->num_irq; i++) अणु
		पूर्णांक irq = platक्रमm_get_irq(pdev, i);

		devm_मुक्त_irq(iommu->dev, irq, iommu);
	पूर्ण

	pm_runसमय_क्रमce_suspend(&pdev->dev);
पूर्ण

अटल पूर्णांक __maybe_unused rk_iommu_suspend(काष्ठा device *dev)
अणु
	काष्ठा rk_iommu *iommu = dev_get_drvdata(dev);

	अगर (!iommu->करोमुख्य)
		वापस 0;

	rk_iommu_disable(iommu);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rk_iommu_resume(काष्ठा device *dev)
अणु
	काष्ठा rk_iommu *iommu = dev_get_drvdata(dev);

	अगर (!iommu->करोमुख्य)
		वापस 0;

	वापस rk_iommu_enable(iommu);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rk_iommu_pm_ops = अणु
	SET_RUNTIME_PM_OPS(rk_iommu_suspend, rk_iommu_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id rk_iommu_dt_ids[] = अणु
	अणु .compatible = "rockchip,iommu" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver rk_iommu_driver = अणु
	.probe = rk_iommu_probe,
	.shutकरोwn = rk_iommu_shutकरोwn,
	.driver = अणु
		   .name = "rk_iommu",
		   .of_match_table = rk_iommu_dt_ids,
		   .pm = &rk_iommu_pm_ops,
		   .suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init rk_iommu_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&rk_iommu_driver);
पूर्ण
subsys_initcall(rk_iommu_init);
