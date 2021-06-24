<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/atomic.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/err.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_wqe.h"
#समावेश "hinic_hw_wq.h"
#समावेश "hinic_hw_cmdq.h"

#घोषणा WQS_BLOCKS_PER_PAGE             4

#घोषणा WQ_BLOCK_SIZE                   4096
#घोषणा WQS_PAGE_SIZE                   (WQS_BLOCKS_PER_PAGE * WQ_BLOCK_SIZE)

#घोषणा WQS_MAX_NUM_BLOCKS              128
#घोषणा WQS_FREE_BLOCKS_SIZE(wqs)       (WQS_MAX_NUM_BLOCKS * \
					 माप((wqs)->मुक्त_blocks[0]))

#घोषणा WQ_SIZE(wq)                     ((wq)->q_depth * (wq)->wqebb_size)

#घोषणा WQ_PAGE_ADDR_SIZE               माप(u64)
#घोषणा WQ_MAX_PAGES                    (WQ_BLOCK_SIZE / WQ_PAGE_ADDR_SIZE)

#घोषणा CMDQ_BLOCK_SIZE                 512
#घोषणा CMDQ_PAGE_SIZE                  4096

#घोषणा CMDQ_WQ_MAX_PAGES               (CMDQ_BLOCK_SIZE / WQ_PAGE_ADDR_SIZE)

#घोषणा WQ_BASE_VADDR(wqs, wq)          \
			((व्योम *)((wqs)->page_vaddr[(wq)->page_idx]) \
				+ (wq)->block_idx * WQ_BLOCK_SIZE)

#घोषणा WQ_BASE_PADDR(wqs, wq)          \
			((wqs)->page_paddr[(wq)->page_idx] \
				+ (wq)->block_idx * WQ_BLOCK_SIZE)

#घोषणा WQ_BASE_ADDR(wqs, wq)           \
			((व्योम *)((wqs)->shaकरोw_page_vaddr[(wq)->page_idx]) \
				+ (wq)->block_idx * WQ_BLOCK_SIZE)

#घोषणा CMDQ_BASE_VADDR(cmdq_pages, wq) \
			((व्योम *)((cmdq_pages)->page_vaddr) \
				+ (wq)->block_idx * CMDQ_BLOCK_SIZE)

#घोषणा CMDQ_BASE_PADDR(cmdq_pages, wq) \
			((cmdq_pages)->page_paddr \
				+ (wq)->block_idx * CMDQ_BLOCK_SIZE)

#घोषणा CMDQ_BASE_ADDR(cmdq_pages, wq)  \
			((व्योम *)((cmdq_pages)->shaकरोw_page_vaddr) \
				+ (wq)->block_idx * CMDQ_BLOCK_SIZE)

#घोषणा WQ_PAGE_ADDR(wq, idx)           \
			((wq)->shaकरोw_block_vaddr[WQE_PAGE_NUM(wq, idx)])

#घोषणा MASKED_WQE_IDX(wq, idx)         ((idx) & (wq)->mask)

#घोषणा WQE_IN_RANGE(wqe, start, end)   \
		(((अचिन्हित दीर्घ)(wqe) >= (अचिन्हित दीर्घ)(start)) && \
		 ((अचिन्हित दीर्घ)(wqe) < (अचिन्हित दीर्घ)(end)))

#घोषणा WQE_SHADOW_PAGE(wq, wqe)        \
		(((अचिन्हित दीर्घ)(wqe) - (अचिन्हित दीर्घ)(wq)->shaकरोw_wqe) \
			/ (wq)->max_wqe_size)

अटल अंतरभूत पूर्णांक WQE_PAGE_OFF(काष्ठा hinic_wq *wq, u16 idx)
अणु
	वापस (((idx) & ((wq)->num_wqebbs_per_page - 1))
		<< (wq)->wqebb_size_shअगरt);
पूर्ण

अटल अंतरभूत पूर्णांक WQE_PAGE_NUM(काष्ठा hinic_wq *wq, u16 idx)
अणु
	वापस (((idx) >> ((wq)->wqebbs_per_page_shअगरt))
		& ((wq)->num_q_pages - 1));
पूर्ण
/**
 * queue_alloc_page - allocate page क्रम Queue
 * @hwअगर: HW पूर्णांकerface क्रम allocating DMA
 * @vaddr: भव address will be वापसed in this address
 * @paddr: physical address will be वापसed in this address
 * @shaकरोw_vaddr: VM area will be वापस here क्रम holding WQ page addresses
 * @page_sz: page size of each WQ page
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक queue_alloc_page(काष्ठा hinic_hwअगर *hwअगर, u64 **vaddr, u64 *paddr,
			    व्योम ***shaकरोw_vaddr, माप_प्रकार page_sz)
अणु
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	dma_addr_t dma_addr;

	*vaddr = dma_alloc_coherent(&pdev->dev, page_sz, &dma_addr,
				    GFP_KERNEL);
	अगर (!*vaddr) अणु
		dev_err(&pdev->dev, "Failed to allocate dma for wqs page\n");
		वापस -ENOMEM;
	पूर्ण

	*paddr = (u64)dma_addr;

	/* use vzalloc क्रम big mem */
	*shaकरोw_vaddr = vzalloc(page_sz);
	अगर (!*shaकरोw_vaddr)
		जाओ err_shaकरोw_vaddr;

	वापस 0;

err_shaकरोw_vaddr:
	dma_मुक्त_coherent(&pdev->dev, page_sz, *vaddr, dma_addr);
	वापस -ENOMEM;
पूर्ण

/**
 * wqs_allocate_page - allocate page क्रम WQ set
 * @wqs: Work Queue Set
 * @page_idx: the page index of the page will be allocated
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक wqs_allocate_page(काष्ठा hinic_wqs *wqs, पूर्णांक page_idx)
अणु
	वापस queue_alloc_page(wqs->hwअगर, &wqs->page_vaddr[page_idx],
				&wqs->page_paddr[page_idx],
				&wqs->shaकरोw_page_vaddr[page_idx],
				WQS_PAGE_SIZE);
पूर्ण

/**
 * wqs_मुक्त_page - मुक्त page of WQ set
 * @wqs: Work Queue Set
 * @page_idx: the page index of the page will be मुक्तd
 **/
अटल व्योम wqs_मुक्त_page(काष्ठा hinic_wqs *wqs, पूर्णांक page_idx)
अणु
	काष्ठा hinic_hwअगर *hwअगर = wqs->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;

	dma_मुक्त_coherent(&pdev->dev, WQS_PAGE_SIZE,
			  wqs->page_vaddr[page_idx],
			  (dma_addr_t)wqs->page_paddr[page_idx]);
	vमुक्त(wqs->shaकरोw_page_vaddr[page_idx]);
पूर्ण

/**
 * cmdq_allocate_page - allocate page क्रम cmdq
 * @cmdq_pages: the pages of the cmdq queue काष्ठा to hold the page
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक cmdq_allocate_page(काष्ठा hinic_cmdq_pages *cmdq_pages)
अणु
	वापस queue_alloc_page(cmdq_pages->hwअगर, &cmdq_pages->page_vaddr,
				&cmdq_pages->page_paddr,
				&cmdq_pages->shaकरोw_page_vaddr,
				CMDQ_PAGE_SIZE);
पूर्ण

/**
 * cmdq_मुक्त_page - मुक्त page from cmdq
 * @cmdq_pages: the pages of the cmdq queue काष्ठा that hold the page
 *
 * Return 0 - Success, negative - Failure
 **/
अटल व्योम cmdq_मुक्त_page(काष्ठा hinic_cmdq_pages *cmdq_pages)
अणु
	काष्ठा hinic_hwअगर *hwअगर = cmdq_pages->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;

	dma_मुक्त_coherent(&pdev->dev, CMDQ_PAGE_SIZE,
			  cmdq_pages->page_vaddr,
			  (dma_addr_t)cmdq_pages->page_paddr);
	vमुक्त(cmdq_pages->shaकरोw_page_vaddr);
पूर्ण

अटल पूर्णांक alloc_page_arrays(काष्ठा hinic_wqs *wqs)
अणु
	काष्ठा hinic_hwअगर *hwअगर = wqs->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	माप_प्रकार size;

	size = wqs->num_pages * माप(*wqs->page_paddr);
	wqs->page_paddr = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	अगर (!wqs->page_paddr)
		वापस -ENOMEM;

	size = wqs->num_pages * माप(*wqs->page_vaddr);
	wqs->page_vaddr = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	अगर (!wqs->page_vaddr)
		जाओ err_page_vaddr;

	size = wqs->num_pages * माप(*wqs->shaकरोw_page_vaddr);
	wqs->shaकरोw_page_vaddr = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	अगर (!wqs->shaकरोw_page_vaddr)
		जाओ err_page_shaकरोw_vaddr;

	वापस 0;

err_page_shaकरोw_vaddr:
	devm_kमुक्त(&pdev->dev, wqs->page_vaddr);

err_page_vaddr:
	devm_kमुक्त(&pdev->dev, wqs->page_paddr);
	वापस -ENOMEM;
पूर्ण

अटल व्योम मुक्त_page_arrays(काष्ठा hinic_wqs *wqs)
अणु
	काष्ठा hinic_hwअगर *hwअगर = wqs->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;

	devm_kमुक्त(&pdev->dev, wqs->shaकरोw_page_vaddr);
	devm_kमुक्त(&pdev->dev, wqs->page_vaddr);
	devm_kमुक्त(&pdev->dev, wqs->page_paddr);
पूर्ण

अटल पूर्णांक wqs_next_block(काष्ठा hinic_wqs *wqs, पूर्णांक *page_idx,
			  पूर्णांक *block_idx)
अणु
	पूर्णांक pos;

	करोwn(&wqs->alloc_blocks_lock);

	wqs->num_मुक्त_blks--;

	अगर (wqs->num_मुक्त_blks < 0) अणु
		wqs->num_मुक्त_blks++;
		up(&wqs->alloc_blocks_lock);
		वापस -ENOMEM;
	पूर्ण

	pos = wqs->alloc_blk_pos++;
	pos &= WQS_MAX_NUM_BLOCKS - 1;

	*page_idx = wqs->मुक्त_blocks[pos].page_idx;
	*block_idx = wqs->मुक्त_blocks[pos].block_idx;

	wqs->मुक्त_blocks[pos].page_idx = -1;
	wqs->मुक्त_blocks[pos].block_idx = -1;

	up(&wqs->alloc_blocks_lock);
	वापस 0;
पूर्ण

अटल व्योम wqs_वापस_block(काष्ठा hinic_wqs *wqs, पूर्णांक page_idx,
			     पूर्णांक block_idx)
अणु
	पूर्णांक pos;

	करोwn(&wqs->alloc_blocks_lock);

	pos = wqs->वापस_blk_pos++;
	pos &= WQS_MAX_NUM_BLOCKS - 1;

	wqs->मुक्त_blocks[pos].page_idx = page_idx;
	wqs->मुक्त_blocks[pos].block_idx = block_idx;

	wqs->num_मुक्त_blks++;

	up(&wqs->alloc_blocks_lock);
पूर्ण

अटल व्योम init_wqs_blocks_arr(काष्ठा hinic_wqs *wqs)
अणु
	पूर्णांक page_idx, blk_idx, pos = 0;

	क्रम (page_idx = 0; page_idx < wqs->num_pages; page_idx++) अणु
		क्रम (blk_idx = 0; blk_idx < WQS_BLOCKS_PER_PAGE; blk_idx++) अणु
			wqs->मुक्त_blocks[pos].page_idx = page_idx;
			wqs->मुक्त_blocks[pos].block_idx = blk_idx;
			pos++;
		पूर्ण
	पूर्ण

	wqs->alloc_blk_pos = 0;
	wqs->वापस_blk_pos = pos;
	wqs->num_मुक्त_blks = pos;

	sema_init(&wqs->alloc_blocks_lock, 1);
पूर्ण

/**
 * hinic_wqs_alloc - allocate Work Queues set
 * @wqs: Work Queue Set
 * @max_wqs: maximum wqs to allocate
 * @hwअगर: HW पूर्णांकerface क्रम use क्रम the allocation
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_wqs_alloc(काष्ठा hinic_wqs *wqs, पूर्णांक max_wqs,
		    काष्ठा hinic_hwअगर *hwअगर)
अणु
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक err, i, page_idx;

	max_wqs = ALIGN(max_wqs, WQS_BLOCKS_PER_PAGE);
	अगर (max_wqs > WQS_MAX_NUM_BLOCKS)  अणु
		dev_err(&pdev->dev, "Invalid max_wqs = %d\n", max_wqs);
		वापस -EINVAL;
	पूर्ण

	wqs->hwअगर = hwअगर;
	wqs->num_pages = max_wqs / WQS_BLOCKS_PER_PAGE;

	अगर (alloc_page_arrays(wqs)) अणु
		dev_err(&pdev->dev,
			"Failed to allocate mem for page addresses\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (page_idx = 0; page_idx < wqs->num_pages; page_idx++) अणु
		err = wqs_allocate_page(wqs, page_idx);
		अगर (err) अणु
			dev_err(&pdev->dev, "Failed wq page allocation\n");
			जाओ err_wq_allocate_page;
		पूर्ण
	पूर्ण

	wqs->मुक्त_blocks = devm_kzalloc(&pdev->dev, WQS_FREE_BLOCKS_SIZE(wqs),
					GFP_KERNEL);
	अगर (!wqs->मुक्त_blocks) अणु
		err = -ENOMEM;
		जाओ err_alloc_blocks;
	पूर्ण

	init_wqs_blocks_arr(wqs);
	वापस 0;

err_alloc_blocks:
err_wq_allocate_page:
	क्रम (i = 0; i < page_idx; i++)
		wqs_मुक्त_page(wqs, i);

	मुक्त_page_arrays(wqs);
	वापस err;
पूर्ण

/**
 * hinic_wqs_मुक्त - मुक्त Work Queues set
 * @wqs: Work Queue Set
 **/
व्योम hinic_wqs_मुक्त(काष्ठा hinic_wqs *wqs)
अणु
	काष्ठा hinic_hwअगर *hwअगर = wqs->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक page_idx;

	devm_kमुक्त(&pdev->dev, wqs->मुक्त_blocks);

	क्रम (page_idx = 0; page_idx < wqs->num_pages; page_idx++)
		wqs_मुक्त_page(wqs, page_idx);

	मुक्त_page_arrays(wqs);
पूर्ण

/**
 * alloc_wqes_shaकरोw - allocate WQE shaकरोws क्रम WQ
 * @wq: WQ to allocate shaकरोws क्रम
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक alloc_wqes_shaकरोw(काष्ठा hinic_wq *wq)
अणु
	काष्ठा hinic_hwअगर *hwअगर = wq->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	माप_प्रकार size;

	size = wq->num_q_pages * wq->max_wqe_size;
	wq->shaकरोw_wqe = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	अगर (!wq->shaकरोw_wqe)
		वापस -ENOMEM;

	size = wq->num_q_pages * माप(wq->prod_idx);
	wq->shaकरोw_idx = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	अगर (!wq->shaकरोw_idx)
		जाओ err_shaकरोw_idx;

	वापस 0;

err_shaकरोw_idx:
	devm_kमुक्त(&pdev->dev, wq->shaकरोw_wqe);
	वापस -ENOMEM;
पूर्ण

/**
 * मुक्त_wqes_shaकरोw - मुक्त WQE shaकरोws of WQ
 * @wq: WQ to मुक्त shaकरोws from
 **/
अटल व्योम मुक्त_wqes_shaकरोw(काष्ठा hinic_wq *wq)
अणु
	काष्ठा hinic_hwअगर *hwअगर = wq->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;

	devm_kमुक्त(&pdev->dev, wq->shaकरोw_idx);
	devm_kमुक्त(&pdev->dev, wq->shaकरोw_wqe);
पूर्ण

/**
 * मुक्त_wq_pages - मुक्त pages of WQ
 * @hwअगर: HW पूर्णांकerface क्रम releasing dma addresses
 * @wq: WQ to मुक्त pages from
 * @num_q_pages: number pages to मुक्त
 **/
अटल व्योम मुक्त_wq_pages(काष्ठा hinic_wq *wq, काष्ठा hinic_hwअगर *hwअगर,
			  पूर्णांक num_q_pages)
अणु
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक i;

	क्रम (i = 0; i < num_q_pages; i++) अणु
		व्योम **vaddr = &wq->shaकरोw_block_vaddr[i];
		u64 *paddr = &wq->block_vaddr[i];
		dma_addr_t dma_addr;

		dma_addr = (dma_addr_t)be64_to_cpu(*paddr);
		dma_मुक्त_coherent(&pdev->dev, wq->wq_page_size, *vaddr,
				  dma_addr);
	पूर्ण

	मुक्त_wqes_shaकरोw(wq);
पूर्ण

/**
 * alloc_wq_pages - alloc pages क्रम WQ
 * @hwअगर: HW पूर्णांकerface क्रम allocating dma addresses
 * @wq: WQ to allocate pages क्रम
 * @max_pages: maximum pages allowed
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक alloc_wq_pages(काष्ठा hinic_wq *wq, काष्ठा hinic_hwअगर *hwअगर,
			  पूर्णांक max_pages)
अणु
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक i, err, num_q_pages;

	num_q_pages = ALIGN(WQ_SIZE(wq), wq->wq_page_size) / wq->wq_page_size;
	अगर (num_q_pages > max_pages) अणु
		dev_err(&pdev->dev, "Number wq pages exceeds the limit\n");
		वापस -EINVAL;
	पूर्ण

	अगर (num_q_pages & (num_q_pages - 1)) अणु
		dev_err(&pdev->dev, "Number wq pages must be power of 2\n");
		वापस -EINVAL;
	पूर्ण

	wq->num_q_pages = num_q_pages;

	err = alloc_wqes_shaकरोw(wq);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate wqe shadow\n");
		वापस err;
	पूर्ण

	क्रम (i = 0; i < num_q_pages; i++) अणु
		व्योम **vaddr = &wq->shaकरोw_block_vaddr[i];
		u64 *paddr = &wq->block_vaddr[i];
		dma_addr_t dma_addr;

		*vaddr = dma_alloc_coherent(&pdev->dev, wq->wq_page_size,
					    &dma_addr, GFP_KERNEL);
		अगर (!*vaddr) अणु
			dev_err(&pdev->dev, "Failed to allocate wq page\n");
			जाओ err_alloc_wq_pages;
		पूर्ण

		/* HW uses Big Endian Format */
		*paddr = cpu_to_be64(dma_addr);
	पूर्ण

	वापस 0;

err_alloc_wq_pages:
	मुक्त_wq_pages(wq, hwअगर, i);
	वापस -ENOMEM;
पूर्ण

/**
 * hinic_wq_allocate - Allocate the WQ resources from the WQS
 * @wqs: WQ set from which to allocate the WQ resources
 * @wq: WQ to allocate resources क्रम it from the WQ set
 * @wqebb_size: Work Queue Block Byte Size
 * @wq_page_size: the page size in the Work Queue
 * @q_depth: number of wqebbs in WQ
 * @max_wqe_size: maximum WQE size that will be used in the WQ
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_wq_allocate(काष्ठा hinic_wqs *wqs, काष्ठा hinic_wq *wq,
		      u16 wqebb_size, u32 wq_page_size, u16 q_depth,
		      u16 max_wqe_size)
अणु
	काष्ठा hinic_hwअगर *hwअगर = wqs->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u16 num_wqebbs_per_page;
	u16 wqebb_size_shअगरt;
	पूर्णांक err;

	अगर (!is_घातer_of_2(wqebb_size)) अणु
		dev_err(&pdev->dev, "wqebb_size must be power of 2\n");
		वापस -EINVAL;
	पूर्ण

	अगर (wq_page_size == 0) अणु
		dev_err(&pdev->dev, "wq_page_size must be > 0\n");
		वापस -EINVAL;
	पूर्ण

	अगर (q_depth & (q_depth - 1)) अणु
		dev_err(&pdev->dev, "WQ q_depth must be power of 2\n");
		वापस -EINVAL;
	पूर्ण

	wqebb_size_shअगरt = ilog2(wqebb_size);
	num_wqebbs_per_page = ALIGN(wq_page_size, wqebb_size)
				>> wqebb_size_shअगरt;

	अगर (!is_घातer_of_2(num_wqebbs_per_page)) अणु
		dev_err(&pdev->dev, "num wqebbs per page must be power of 2\n");
		वापस -EINVAL;
	पूर्ण

	wq->hwअगर = hwअगर;

	err = wqs_next_block(wqs, &wq->page_idx, &wq->block_idx);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to get free wqs next block\n");
		वापस err;
	पूर्ण

	wq->wqebb_size = wqebb_size;
	wq->wq_page_size = wq_page_size;
	wq->q_depth = q_depth;
	wq->max_wqe_size = max_wqe_size;
	wq->num_wqebbs_per_page = num_wqebbs_per_page;
	wq->wqebbs_per_page_shअगरt = ilog2(num_wqebbs_per_page);
	wq->wqebb_size_shअगरt = wqebb_size_shअगरt;
	wq->block_vaddr = WQ_BASE_VADDR(wqs, wq);
	wq->shaकरोw_block_vaddr = WQ_BASE_ADDR(wqs, wq);
	wq->block_paddr = WQ_BASE_PADDR(wqs, wq);

	err = alloc_wq_pages(wq, wqs->hwअगर, WQ_MAX_PAGES);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate wq pages\n");
		जाओ err_alloc_wq_pages;
	पूर्ण

	atomic_set(&wq->cons_idx, 0);
	atomic_set(&wq->prod_idx, 0);
	atomic_set(&wq->delta, q_depth);
	wq->mask = q_depth - 1;

	वापस 0;

err_alloc_wq_pages:
	wqs_वापस_block(wqs, wq->page_idx, wq->block_idx);
	वापस err;
पूर्ण

/**
 * hinic_wq_मुक्त - Free the WQ resources to the WQS
 * @wqs: WQ set to मुक्त the WQ resources to it
 * @wq: WQ to मुक्त its resources to the WQ set resources
 **/
व्योम hinic_wq_मुक्त(काष्ठा hinic_wqs *wqs, काष्ठा hinic_wq *wq)
अणु
	मुक्त_wq_pages(wq, wqs->hwअगर, wq->num_q_pages);

	wqs_वापस_block(wqs, wq->page_idx, wq->block_idx);
पूर्ण

/**
 * hinic_wqs_cmdq_alloc - Allocate wqs क्रम cmdqs
 * @cmdq_pages: will hold the pages of the cmdq
 * @wq: वापसed wqs
 * @hwअगर: HW पूर्णांकerface
 * @cmdq_blocks: number of cmdq blocks/wq to allocate
 * @wqebb_size: Work Queue Block Byte Size
 * @wq_page_size: the page size in the Work Queue
 * @q_depth: number of wqebbs in WQ
 * @max_wqe_size: maximum WQE size that will be used in the WQ
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_wqs_cmdq_alloc(काष्ठा hinic_cmdq_pages *cmdq_pages,
			 काष्ठा hinic_wq *wq, काष्ठा hinic_hwअगर *hwअगर,
			 पूर्णांक cmdq_blocks, u16 wqebb_size, u32 wq_page_size,
			 u16 q_depth, u16 max_wqe_size)
अणु
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u16 num_wqebbs_per_page_shअगरt;
	u16 num_wqebbs_per_page;
	u16 wqebb_size_shअगरt;
	पूर्णांक i, j, err = -ENOMEM;

	अगर (!is_घातer_of_2(wqebb_size)) अणु
		dev_err(&pdev->dev, "wqebb_size must be power of 2\n");
		वापस -EINVAL;
	पूर्ण

	अगर (wq_page_size == 0) अणु
		dev_err(&pdev->dev, "wq_page_size must be > 0\n");
		वापस -EINVAL;
	पूर्ण

	अगर (q_depth & (q_depth - 1)) अणु
		dev_err(&pdev->dev, "WQ q_depth must be power of 2\n");
		वापस -EINVAL;
	पूर्ण

	wqebb_size_shअगरt = ilog2(wqebb_size);
	num_wqebbs_per_page = ALIGN(wq_page_size, wqebb_size)
				>> wqebb_size_shअगरt;

	अगर (!is_घातer_of_2(num_wqebbs_per_page)) अणु
		dev_err(&pdev->dev, "num wqebbs per page must be power of 2\n");
		वापस -EINVAL;
	पूर्ण

	cmdq_pages->hwअगर = hwअगर;

	err = cmdq_allocate_page(cmdq_pages);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate CMDQ page\n");
		वापस err;
	पूर्ण
	num_wqebbs_per_page_shअगरt = ilog2(num_wqebbs_per_page);

	क्रम (i = 0; i < cmdq_blocks; i++) अणु
		wq[i].hwअगर = hwअगर;
		wq[i].page_idx = 0;
		wq[i].block_idx = i;

		wq[i].wqebb_size = wqebb_size;
		wq[i].wq_page_size = wq_page_size;
		wq[i].q_depth = q_depth;
		wq[i].max_wqe_size = max_wqe_size;
		wq[i].num_wqebbs_per_page = num_wqebbs_per_page;
		wq[i].wqebbs_per_page_shअगरt = num_wqebbs_per_page_shअगरt;
		wq[i].wqebb_size_shअगरt = wqebb_size_shअगरt;
		wq[i].block_vaddr = CMDQ_BASE_VADDR(cmdq_pages, &wq[i]);
		wq[i].shaकरोw_block_vaddr = CMDQ_BASE_ADDR(cmdq_pages, &wq[i]);
		wq[i].block_paddr = CMDQ_BASE_PADDR(cmdq_pages, &wq[i]);

		err = alloc_wq_pages(&wq[i], cmdq_pages->hwअगर,
				     CMDQ_WQ_MAX_PAGES);
		अगर (err) अणु
			dev_err(&pdev->dev, "Failed to alloc CMDQ blocks\n");
			जाओ err_cmdq_block;
		पूर्ण

		atomic_set(&wq[i].cons_idx, 0);
		atomic_set(&wq[i].prod_idx, 0);
		atomic_set(&wq[i].delta, q_depth);
		wq[i].mask = q_depth - 1;
	पूर्ण

	वापस 0;

err_cmdq_block:
	क्रम (j = 0; j < i; j++)
		मुक्त_wq_pages(&wq[j], cmdq_pages->hwअगर, wq[j].num_q_pages);

	cmdq_मुक्त_page(cmdq_pages);
	वापस err;
पूर्ण

/**
 * hinic_wqs_cmdq_मुक्त - Free wqs from cmdqs
 * @cmdq_pages: hold the pages of the cmdq
 * @wq: wqs to मुक्त
 * @cmdq_blocks: number of wqs to मुक्त
 **/
व्योम hinic_wqs_cmdq_मुक्त(काष्ठा hinic_cmdq_pages *cmdq_pages,
			 काष्ठा hinic_wq *wq, पूर्णांक cmdq_blocks)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cmdq_blocks; i++)
		मुक्त_wq_pages(&wq[i], cmdq_pages->hwअगर, wq[i].num_q_pages);

	cmdq_मुक्त_page(cmdq_pages);
पूर्ण

अटल व्योम copy_wqe_to_shaकरोw(काष्ठा hinic_wq *wq, व्योम *shaकरोw_addr,
			       पूर्णांक num_wqebbs, u16 idx)
अणु
	व्योम *wqebb_addr;
	पूर्णांक i;

	क्रम (i = 0; i < num_wqebbs; i++, idx++) अणु
		idx = MASKED_WQE_IDX(wq, idx);
		wqebb_addr = WQ_PAGE_ADDR(wq, idx) +
			     WQE_PAGE_OFF(wq, idx);

		स_नकल(shaकरोw_addr, wqebb_addr, wq->wqebb_size);

		shaकरोw_addr += wq->wqebb_size;
	पूर्ण
पूर्ण

अटल व्योम copy_wqe_from_shaकरोw(काष्ठा hinic_wq *wq, व्योम *shaकरोw_addr,
				 पूर्णांक num_wqebbs, u16 idx)
अणु
	व्योम *wqebb_addr;
	पूर्णांक i;

	क्रम (i = 0; i < num_wqebbs; i++, idx++) अणु
		idx = MASKED_WQE_IDX(wq, idx);
		wqebb_addr = WQ_PAGE_ADDR(wq, idx) +
			     WQE_PAGE_OFF(wq, idx);

		स_नकल(wqebb_addr, shaकरोw_addr, wq->wqebb_size);
		shaकरोw_addr += wq->wqebb_size;
	पूर्ण
पूर्ण

/**
 * hinic_get_wqe - get wqe ptr in the current pi and update the pi
 * @wq: wq to get wqe from
 * @wqe_size: wqe size
 * @prod_idx: वापसed pi
 *
 * Return wqe poपूर्णांकer
 **/
काष्ठा hinic_hw_wqe *hinic_get_wqe(काष्ठा hinic_wq *wq, अचिन्हित पूर्णांक wqe_size,
				   u16 *prod_idx)
अणु
	पूर्णांक curr_pg, end_pg, num_wqebbs;
	u16 curr_prod_idx, end_prod_idx;

	*prod_idx = MASKED_WQE_IDX(wq, atomic_पढ़ो(&wq->prod_idx));

	num_wqebbs = ALIGN(wqe_size, wq->wqebb_size) >> wq->wqebb_size_shअगरt;

	अगर (atomic_sub_वापस(num_wqebbs, &wq->delta) <= 0) अणु
		atomic_add(num_wqebbs, &wq->delta);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	end_prod_idx = atomic_add_वापस(num_wqebbs, &wq->prod_idx);

	end_prod_idx = MASKED_WQE_IDX(wq, end_prod_idx);
	curr_prod_idx = end_prod_idx - num_wqebbs;
	curr_prod_idx = MASKED_WQE_IDX(wq, curr_prod_idx);

	/* end prod index poपूर्णांकs to the next wqebb, thereक्रमe minus 1 */
	end_prod_idx = MASKED_WQE_IDX(wq, end_prod_idx - 1);

	curr_pg = WQE_PAGE_NUM(wq, curr_prod_idx);
	end_pg = WQE_PAGE_NUM(wq, end_prod_idx);

	*prod_idx = curr_prod_idx;

	/* If we only have one page, still need to get shaकरोwn wqe when
	 * wqe rolling-over page
	 */
	अगर (curr_pg != end_pg || MASKED_WQE_IDX(wq, end_prod_idx) < *prod_idx) अणु
		व्योम *shaकरोw_addr = &wq->shaकरोw_wqe[curr_pg * wq->max_wqe_size];

		copy_wqe_to_shaकरोw(wq, shaकरोw_addr, num_wqebbs, *prod_idx);

		wq->shaकरोw_idx[curr_pg] = *prod_idx;
		वापस shaकरोw_addr;
	पूर्ण

	वापस WQ_PAGE_ADDR(wq, *prod_idx) + WQE_PAGE_OFF(wq, *prod_idx);
पूर्ण

/**
 * hinic_वापस_wqe - वापस the wqe when transmit failed
 * @wq: wq to वापस wqe
 * @wqe_size: wqe size
 **/
व्योम hinic_वापस_wqe(काष्ठा hinic_wq *wq, अचिन्हित पूर्णांक wqe_size)
अणु
	पूर्णांक num_wqebbs = ALIGN(wqe_size, wq->wqebb_size) / wq->wqebb_size;

	atomic_sub(num_wqebbs, &wq->prod_idx);

	atomic_add(num_wqebbs, &wq->delta);
पूर्ण

/**
 * hinic_put_wqe - वापस the wqe place to use क्रम a new wqe
 * @wq: wq to वापस wqe
 * @wqe_size: wqe size
 **/
व्योम hinic_put_wqe(काष्ठा hinic_wq *wq, अचिन्हित पूर्णांक wqe_size)
अणु
	पूर्णांक num_wqebbs = ALIGN(wqe_size, wq->wqebb_size)
			>> wq->wqebb_size_shअगरt;

	atomic_add(num_wqebbs, &wq->cons_idx);

	atomic_add(num_wqebbs, &wq->delta);
पूर्ण

/**
 * hinic_पढ़ो_wqe - पढ़ो wqe ptr in the current ci
 * @wq: wq to get पढ़ो from
 * @wqe_size: wqe size
 * @cons_idx: वापसed ci
 *
 * Return wqe poपूर्णांकer
 **/
काष्ठा hinic_hw_wqe *hinic_पढ़ो_wqe(काष्ठा hinic_wq *wq, अचिन्हित पूर्णांक wqe_size,
				    u16 *cons_idx)
अणु
	पूर्णांक num_wqebbs = ALIGN(wqe_size, wq->wqebb_size)
			>> wq->wqebb_size_shअगरt;
	u16 curr_cons_idx, end_cons_idx;
	पूर्णांक curr_pg, end_pg;

	अगर ((atomic_पढ़ो(&wq->delta) + num_wqebbs) > wq->q_depth)
		वापस ERR_PTR(-EBUSY);

	curr_cons_idx = atomic_पढ़ो(&wq->cons_idx);

	curr_cons_idx = MASKED_WQE_IDX(wq, curr_cons_idx);
	end_cons_idx = MASKED_WQE_IDX(wq, curr_cons_idx + num_wqebbs - 1);

	curr_pg = WQE_PAGE_NUM(wq, curr_cons_idx);
	end_pg = WQE_PAGE_NUM(wq, end_cons_idx);

	*cons_idx = curr_cons_idx;

	अगर (curr_pg != end_pg) अणु
		व्योम *shaकरोw_addr = &wq->shaकरोw_wqe[curr_pg * wq->max_wqe_size];

		copy_wqe_to_shaकरोw(wq, shaकरोw_addr, num_wqebbs, *cons_idx);
		वापस shaकरोw_addr;
	पूर्ण

	वापस WQ_PAGE_ADDR(wq, *cons_idx) + WQE_PAGE_OFF(wq, *cons_idx);
पूर्ण

/**
 * hinic_पढ़ो_wqe_direct - पढ़ो wqe directly from ci position
 * @wq: wq
 * @cons_idx: ci position
 *
 * Return wqe
 **/
काष्ठा hinic_hw_wqe *hinic_पढ़ो_wqe_direct(काष्ठा hinic_wq *wq, u16 cons_idx)
अणु
	वापस WQ_PAGE_ADDR(wq, cons_idx) + WQE_PAGE_OFF(wq, cons_idx);
पूर्ण

/**
 * wqe_shaकरोw - check अगर a wqe is shaकरोw
 * @wq: wq of the wqe
 * @wqe: the wqe क्रम shaकरोw checking
 *
 * Return true - shaकरोw, false - Not shaकरोw
 **/
अटल अंतरभूत bool wqe_shaकरोw(काष्ठा hinic_wq *wq, काष्ठा hinic_hw_wqe *wqe)
अणु
	माप_प्रकार wqe_shaकरोw_size = wq->num_q_pages * wq->max_wqe_size;

	वापस WQE_IN_RANGE(wqe, wq->shaकरोw_wqe,
			    &wq->shaकरोw_wqe[wqe_shaकरोw_size]);
पूर्ण

/**
 * hinic_ग_लिखो_wqe - ग_लिखो the wqe to the wq
 * @wq: wq to ग_लिखो wqe to
 * @wqe: wqe to ग_लिखो
 * @wqe_size: wqe size
 **/
व्योम hinic_ग_लिखो_wqe(काष्ठा hinic_wq *wq, काष्ठा hinic_hw_wqe *wqe,
		     अचिन्हित पूर्णांक wqe_size)
अणु
	पूर्णांक curr_pg, num_wqebbs;
	व्योम *shaकरोw_addr;
	u16 prod_idx;

	अगर (wqe_shaकरोw(wq, wqe)) अणु
		curr_pg = WQE_SHADOW_PAGE(wq, wqe);

		prod_idx = wq->shaकरोw_idx[curr_pg];
		num_wqebbs = ALIGN(wqe_size, wq->wqebb_size) / wq->wqebb_size;
		shaकरोw_addr = &wq->shaकरोw_wqe[curr_pg * wq->max_wqe_size];

		copy_wqe_from_shaकरोw(wq, shaकरोw_addr, num_wqebbs, prod_idx);
	पूर्ण
पूर्ण
