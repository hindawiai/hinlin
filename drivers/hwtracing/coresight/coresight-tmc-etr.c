<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(C) 2016 Linaro Limited. All rights reserved.
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 */

#समावेश <linux/atomic.h>
#समावेश <linux/coresight.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/iommu.h>
#समावेश <linux/idr.h>
#समावेश <linux/mutex.h>
#समावेश <linux/refcount.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "coresight-catu.h"
#समावेश "coresight-etm-perf.h"
#समावेश "coresight-priv.h"
#समावेश "coresight-tmc.h"

काष्ठा etr_flat_buf अणु
	काष्ठा device	*dev;
	dma_addr_t	daddr;
	व्योम		*vaddr;
	माप_प्रकार		size;
पूर्ण;

/*
 * etr_perf_buffer - Perf buffer used क्रम ETR
 * @drvdata		- The ETR drvdaga this buffer has been allocated क्रम.
 * @etr_buf		- Actual buffer used by the ETR
 * @pid			- The PID this etr_perf_buffer beदीर्घs to.
 * @snaphost		- Perf session mode
 * @head		- handle->head at the beginning of the session.
 * @nr_pages		- Number of pages in the ring buffer.
 * @pages		- Array of Pages in the ring buffer.
 */
काष्ठा etr_perf_buffer अणु
	काष्ठा पंचांगc_drvdata	*drvdata;
	काष्ठा etr_buf		*etr_buf;
	pid_t			pid;
	bool			snapshot;
	अचिन्हित दीर्घ		head;
	पूर्णांक			nr_pages;
	व्योम			**pages;
पूर्ण;

/* Convert the perf index to an offset within the ETR buffer */
#घोषणा PERF_IDX2OFF(idx, buf)	((idx) % ((buf)->nr_pages << PAGE_SHIFT))

/* Lower limit क्रम ETR hardware buffer */
#घोषणा TMC_ETR_PERF_MIN_BUF_SIZE	SZ_1M

/*
 * The TMC ETR SG has a page size of 4K. The SG table contains poपूर्णांकers
 * to 4KB buffers. However, the OS may use a PAGE_SIZE dअगरferent from
 * 4K (i.e, 16KB or 64KB). This implies that a single OS page could
 * contain more than one SG buffer and tables.
 *
 * A table entry has the following क्रमmat:
 *
 * ---Bit31------------Bit4-------Bit1-----Bit0--
 * |     Address[39:12]    | SBZ |  Entry Type  |
 * ----------------------------------------------
 *
 * Address: Bits [39:12] of a physical page address. Bits [11:0] are
 *	    always zero.
 *
 * Entry type:
 *	b00 - Reserved.
 *	b01 - Last entry in the tables, poपूर्णांकs to 4K page buffer.
 *	b10 - Normal entry, poपूर्णांकs to 4K page buffer.
 *	b11 - Link. The address poपूर्णांकs to the base of next table.
 */

प्रकार u32 sgte_t;

#घोषणा ETR_SG_PAGE_SHIFT		12
#घोषणा ETR_SG_PAGE_SIZE		(1UL << ETR_SG_PAGE_SHIFT)
#घोषणा ETR_SG_PAGES_PER_SYSPAGE	(PAGE_SIZE / ETR_SG_PAGE_SIZE)
#घोषणा ETR_SG_PTRS_PER_PAGE		(ETR_SG_PAGE_SIZE / माप(sgte_t))
#घोषणा ETR_SG_PTRS_PER_SYSPAGE		(PAGE_SIZE / माप(sgte_t))

#घोषणा ETR_SG_ET_MASK			0x3
#घोषणा ETR_SG_ET_LAST			0x1
#घोषणा ETR_SG_ET_NORMAL		0x2
#घोषणा ETR_SG_ET_LINK			0x3

#घोषणा ETR_SG_ADDR_SHIFT		4

#घोषणा ETR_SG_ENTRY(addr, type) \
	(sgte_t)((((addr) >> ETR_SG_PAGE_SHIFT) << ETR_SG_ADDR_SHIFT) | \
		 (type & ETR_SG_ET_MASK))

#घोषणा ETR_SG_ADDR(entry) \
	(((dma_addr_t)(entry) >> ETR_SG_ADDR_SHIFT) << ETR_SG_PAGE_SHIFT)
#घोषणा ETR_SG_ET(entry)		((entry) & ETR_SG_ET_MASK)

/*
 * काष्ठा etr_sg_table : ETR SG Table
 * @sg_table:		Generic SG Table holding the data/table pages.
 * @hwaddr:		hwaddress used by the TMC, which is the base
 *			address of the table.
 */
काष्ठा etr_sg_table अणु
	काष्ठा पंचांगc_sg_table	*sg_table;
	dma_addr_t		hwaddr;
पूर्ण;

/*
 * पंचांगc_etr_sg_table_entries: Total number of table entries required to map
 * @nr_pages प्रणाली pages.
 *
 * We need to map @nr_pages * ETR_SG_PAGES_PER_SYSPAGE data pages.
 * Each TMC page can map (ETR_SG_PTRS_PER_PAGE - 1) buffer poपूर्णांकers,
 * with the last entry poपूर्णांकing to another page of table entries.
 * If we spill over to a new page क्रम mapping 1 entry, we could as
 * well replace the link entry of the previous page with the last entry.
 */
अटल अंतरभूत अचिन्हित दीर्घ __attribute_स्थिर__
पंचांगc_etr_sg_table_entries(पूर्णांक nr_pages)
अणु
	अचिन्हित दीर्घ nr_sgpages = nr_pages * ETR_SG_PAGES_PER_SYSPAGE;
	अचिन्हित दीर्घ nr_sglinks = nr_sgpages / (ETR_SG_PTRS_PER_PAGE - 1);
	/*
	 * If we spill over to a new page क्रम 1 entry, we could as well
	 * make it the LAST entry in the previous page, skipping the Link
	 * address.
	 */
	अगर (nr_sglinks && (nr_sgpages % (ETR_SG_PTRS_PER_PAGE - 1) < 2))
		nr_sglinks--;
	वापस nr_sgpages + nr_sglinks;
पूर्ण

/*
 * पंचांगc_pages_get_offset:  Go through all the pages in the पंचांगc_pages
 * and map the device address @addr to an offset within the भव
 * contiguous buffer.
 */
अटल दीर्घ
पंचांगc_pages_get_offset(काष्ठा पंचांगc_pages *पंचांगc_pages, dma_addr_t addr)
अणु
	पूर्णांक i;
	dma_addr_t page_start;

	क्रम (i = 0; i < पंचांगc_pages->nr_pages; i++) अणु
		page_start = पंचांगc_pages->daddrs[i];
		अगर (addr >= page_start && addr < (page_start + PAGE_SIZE))
			वापस i * PAGE_SIZE + (addr - page_start);
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * पंचांगc_pages_मुक्त : Unmap and मुक्त the pages used by पंचांगc_pages.
 * If the pages were not allocated in पंचांगc_pages_alloc(), we would
 * simply drop the refcount.
 */
अटल व्योम पंचांगc_pages_मुक्त(काष्ठा पंचांगc_pages *पंचांगc_pages,
			   काष्ठा device *dev, क्रमागत dma_data_direction dir)
अणु
	पूर्णांक i;
	काष्ठा device *real_dev = dev->parent;

	क्रम (i = 0; i < पंचांगc_pages->nr_pages; i++) अणु
		अगर (पंचांगc_pages->daddrs && पंचांगc_pages->daddrs[i])
			dma_unmap_page(real_dev, पंचांगc_pages->daddrs[i],
					 PAGE_SIZE, dir);
		अगर (पंचांगc_pages->pages && पंचांगc_pages->pages[i])
			__मुक्त_page(पंचांगc_pages->pages[i]);
	पूर्ण

	kमुक्त(पंचांगc_pages->pages);
	kमुक्त(पंचांगc_pages->daddrs);
	पंचांगc_pages->pages = शून्य;
	पंचांगc_pages->daddrs = शून्य;
	पंचांगc_pages->nr_pages = 0;
पूर्ण

/*
 * पंचांगc_pages_alloc : Allocate and map pages क्रम a given @पंचांगc_pages.
 * If @pages is not शून्य, the list of page भव addresses are
 * used as the data pages. The pages are then dma_map'ed क्रम @dev
 * with dma_direction @dir.
 *
 * Returns 0 upon success, अन्यथा the error number.
 */
अटल पूर्णांक पंचांगc_pages_alloc(काष्ठा पंचांगc_pages *पंचांगc_pages,
			   काष्ठा device *dev, पूर्णांक node,
			   क्रमागत dma_data_direction dir, व्योम **pages)
अणु
	पूर्णांक i, nr_pages;
	dma_addr_t paddr;
	काष्ठा page *page;
	काष्ठा device *real_dev = dev->parent;

	nr_pages = पंचांगc_pages->nr_pages;
	पंचांगc_pages->daddrs = kसुस्मृति(nr_pages, माप(*पंचांगc_pages->daddrs),
					 GFP_KERNEL);
	अगर (!पंचांगc_pages->daddrs)
		वापस -ENOMEM;
	पंचांगc_pages->pages = kसुस्मृति(nr_pages, माप(*पंचांगc_pages->pages),
					 GFP_KERNEL);
	अगर (!पंचांगc_pages->pages) अणु
		kमुक्त(पंचांगc_pages->daddrs);
		पंचांगc_pages->daddrs = शून्य;
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < nr_pages; i++) अणु
		अगर (pages && pages[i]) अणु
			page = virt_to_page(pages[i]);
			/* Hold a refcount on the page */
			get_page(page);
		पूर्ण अन्यथा अणु
			page = alloc_pages_node(node,
						GFP_KERNEL | __GFP_ZERO, 0);
			अगर (!page)
				जाओ err;
		पूर्ण
		paddr = dma_map_page(real_dev, page, 0, PAGE_SIZE, dir);
		अगर (dma_mapping_error(real_dev, paddr))
			जाओ err;
		पंचांगc_pages->daddrs[i] = paddr;
		पंचांगc_pages->pages[i] = page;
	पूर्ण
	वापस 0;
err:
	पंचांगc_pages_मुक्त(पंचांगc_pages, dev, dir);
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत दीर्घ
पंचांगc_sg_get_data_page_offset(काष्ठा पंचांगc_sg_table *sg_table, dma_addr_t addr)
अणु
	वापस पंचांगc_pages_get_offset(&sg_table->data_pages, addr);
पूर्ण

अटल अंतरभूत व्योम पंचांगc_मुक्त_table_pages(काष्ठा पंचांगc_sg_table *sg_table)
अणु
	अगर (sg_table->table_vaddr)
		vunmap(sg_table->table_vaddr);
	पंचांगc_pages_मुक्त(&sg_table->table_pages, sg_table->dev, DMA_TO_DEVICE);
पूर्ण

अटल व्योम पंचांगc_मुक्त_data_pages(काष्ठा पंचांगc_sg_table *sg_table)
अणु
	अगर (sg_table->data_vaddr)
		vunmap(sg_table->data_vaddr);
	पंचांगc_pages_मुक्त(&sg_table->data_pages, sg_table->dev, DMA_FROM_DEVICE);
पूर्ण

व्योम पंचांगc_मुक्त_sg_table(काष्ठा पंचांगc_sg_table *sg_table)
अणु
	पंचांगc_मुक्त_table_pages(sg_table);
	पंचांगc_मुक्त_data_pages(sg_table);
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगc_मुक्त_sg_table);

/*
 * Alloc pages क्रम the table. Since this will be used by the device,
 * allocate the pages बंदr to the device (i.e, dev_to_node(dev)
 * rather than the CPU node).
 */
अटल पूर्णांक पंचांगc_alloc_table_pages(काष्ठा पंचांगc_sg_table *sg_table)
अणु
	पूर्णांक rc;
	काष्ठा पंचांगc_pages *table_pages = &sg_table->table_pages;

	rc = पंचांगc_pages_alloc(table_pages, sg_table->dev,
			     dev_to_node(sg_table->dev),
			     DMA_TO_DEVICE, शून्य);
	अगर (rc)
		वापस rc;
	sg_table->table_vaddr = vmap(table_pages->pages,
				     table_pages->nr_pages,
				     VM_MAP,
				     PAGE_KERNEL);
	अगर (!sg_table->table_vaddr)
		rc = -ENOMEM;
	अन्यथा
		sg_table->table_daddr = table_pages->daddrs[0];
	वापस rc;
पूर्ण

अटल पूर्णांक पंचांगc_alloc_data_pages(काष्ठा पंचांगc_sg_table *sg_table, व्योम **pages)
अणु
	पूर्णांक rc;

	/* Allocate data pages on the node requested by the caller */
	rc = पंचांगc_pages_alloc(&sg_table->data_pages,
			     sg_table->dev, sg_table->node,
			     DMA_FROM_DEVICE, pages);
	अगर (!rc) अणु
		sg_table->data_vaddr = vmap(sg_table->data_pages.pages,
					    sg_table->data_pages.nr_pages,
					    VM_MAP,
					    PAGE_KERNEL);
		अगर (!sg_table->data_vaddr)
			rc = -ENOMEM;
	पूर्ण
	वापस rc;
पूर्ण

/*
 * पंचांगc_alloc_sg_table: Allocate and setup dma pages क्रम the TMC SG table
 * and data buffers. TMC ग_लिखोs to the data buffers and पढ़ोs from the SG
 * Table pages.
 *
 * @dev		- Coresight device to which page should be DMA mapped.
 * @node	- Numa node क्रम mem allocations
 * @nr_tpages	- Number of pages क्रम the table entries.
 * @nr_dpages	- Number of pages क्रम Data buffer.
 * @pages	- Optional list of भव address of pages.
 */
काष्ठा पंचांगc_sg_table *पंचांगc_alloc_sg_table(काष्ठा device *dev,
					पूर्णांक node,
					पूर्णांक nr_tpages,
					पूर्णांक nr_dpages,
					व्योम **pages)
अणु
	दीर्घ rc;
	काष्ठा पंचांगc_sg_table *sg_table;

	sg_table = kzalloc(माप(*sg_table), GFP_KERNEL);
	अगर (!sg_table)
		वापस ERR_PTR(-ENOMEM);
	sg_table->data_pages.nr_pages = nr_dpages;
	sg_table->table_pages.nr_pages = nr_tpages;
	sg_table->node = node;
	sg_table->dev = dev;

	rc  = पंचांगc_alloc_data_pages(sg_table, pages);
	अगर (!rc)
		rc = पंचांगc_alloc_table_pages(sg_table);
	अगर (rc) अणु
		पंचांगc_मुक्त_sg_table(sg_table);
		kमुक्त(sg_table);
		वापस ERR_PTR(rc);
	पूर्ण

	वापस sg_table;
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगc_alloc_sg_table);

/*
 * पंचांगc_sg_table_sync_data_range: Sync the data buffer written
 * by the device from @offset upto a @size bytes.
 */
व्योम पंचांगc_sg_table_sync_data_range(काष्ठा पंचांगc_sg_table *table,
				  u64 offset, u64 size)
अणु
	पूर्णांक i, index, start;
	पूर्णांक npages = DIV_ROUND_UP(size, PAGE_SIZE);
	काष्ठा device *real_dev = table->dev->parent;
	काष्ठा पंचांगc_pages *data = &table->data_pages;

	start = offset >> PAGE_SHIFT;
	क्रम (i = start; i < (start + npages); i++) अणु
		index = i % data->nr_pages;
		dma_sync_single_क्रम_cpu(real_dev, data->daddrs[index],
					PAGE_SIZE, DMA_FROM_DEVICE);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगc_sg_table_sync_data_range);

/* पंचांगc_sg_sync_table: Sync the page table */
व्योम पंचांगc_sg_table_sync_table(काष्ठा पंचांगc_sg_table *sg_table)
अणु
	पूर्णांक i;
	काष्ठा device *real_dev = sg_table->dev->parent;
	काष्ठा पंचांगc_pages *table_pages = &sg_table->table_pages;

	क्रम (i = 0; i < table_pages->nr_pages; i++)
		dma_sync_single_क्रम_device(real_dev, table_pages->daddrs[i],
					   PAGE_SIZE, DMA_TO_DEVICE);
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगc_sg_table_sync_table);

/*
 * पंचांगc_sg_table_get_data: Get the buffer poपूर्णांकer क्रम data @offset
 * in the SG buffer. The @bufpp is updated to poपूर्णांक to the buffer.
 * Returns :
 *	the length of linear data available at @offset.
 *	or
 *	<= 0 अगर no data is available.
 */
sमाप_प्रकार पंचांगc_sg_table_get_data(काष्ठा पंचांगc_sg_table *sg_table,
			      u64 offset, माप_प्रकार len, अक्षर **bufpp)
अणु
	माप_प्रकार size;
	पूर्णांक pg_idx = offset >> PAGE_SHIFT;
	पूर्णांक pg_offset = offset & (PAGE_SIZE - 1);
	काष्ठा पंचांगc_pages *data_pages = &sg_table->data_pages;

	size = पंचांगc_sg_table_buf_size(sg_table);
	अगर (offset >= size)
		वापस -EINVAL;

	/* Make sure we करोn't go beyond the end */
	len = (len < (size - offset)) ? len : size - offset;
	/* Respect the page boundaries */
	len = (len < (PAGE_SIZE - pg_offset)) ? len : (PAGE_SIZE - pg_offset);
	अगर (len > 0)
		*bufpp = page_address(data_pages->pages[pg_idx]) + pg_offset;
	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगc_sg_table_get_data);

#अगर_घोषित ETR_SG_DEBUG
/* Map a dma address to भव address */
अटल अचिन्हित दीर्घ
पंचांगc_sg_daddr_to_vaddr(काष्ठा पंचांगc_sg_table *sg_table,
		      dma_addr_t addr, bool table)
अणु
	दीर्घ offset;
	अचिन्हित दीर्घ base;
	काष्ठा पंचांगc_pages *पंचांगc_pages;

	अगर (table) अणु
		पंचांगc_pages = &sg_table->table_pages;
		base = (अचिन्हित दीर्घ)sg_table->table_vaddr;
	पूर्ण अन्यथा अणु
		पंचांगc_pages = &sg_table->data_pages;
		base = (अचिन्हित दीर्घ)sg_table->data_vaddr;
	पूर्ण

	offset = पंचांगc_pages_get_offset(पंचांगc_pages, addr);
	अगर (offset < 0)
		वापस 0;
	वापस base + offset;
पूर्ण

/* Dump the given sg_table */
अटल व्योम पंचांगc_etr_sg_table_dump(काष्ठा etr_sg_table *etr_table)
अणु
	sgte_t *ptr;
	पूर्णांक i = 0;
	dma_addr_t addr;
	काष्ठा पंचांगc_sg_table *sg_table = etr_table->sg_table;

	ptr = (sgte_t *)पंचांगc_sg_daddr_to_vaddr(sg_table,
					      etr_table->hwaddr, true);
	जबतक (ptr) अणु
		addr = ETR_SG_ADDR(*ptr);
		चयन (ETR_SG_ET(*ptr)) अणु
		हाल ETR_SG_ET_NORMAL:
			dev_dbg(sg_table->dev,
				"%05d: %p\t:[N] 0x%llx\n", i, ptr, addr);
			ptr++;
			अवरोध;
		हाल ETR_SG_ET_LINK:
			dev_dbg(sg_table->dev,
				"%05d: *** %p\t:{L} 0x%llx ***\n",
				 i, ptr, addr);
			ptr = (sgte_t *)पंचांगc_sg_daddr_to_vaddr(sg_table,
							      addr, true);
			अवरोध;
		हाल ETR_SG_ET_LAST:
			dev_dbg(sg_table->dev,
				"%05d: ### %p\t:[L] 0x%llx ###\n",
				 i, ptr, addr);
			वापस;
		शेष:
			dev_dbg(sg_table->dev,
				"%05d: xxx %p\t:[INVALID] 0x%llx xxx\n",
				 i, ptr, addr);
			वापस;
		पूर्ण
		i++;
	पूर्ण
	dev_dbg(sg_table->dev, "******* End of Table *****\n");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम पंचांगc_etr_sg_table_dump(काष्ठा etr_sg_table *etr_table) अणुपूर्ण
#पूर्ण_अगर

/*
 * Populate the SG Table page table entries from table/data
 * pages allocated. Each Data page has ETR_SG_PAGES_PER_SYSPAGE SG pages.
 * So करोes a Table page. So we keep track of indices of the tables
 * in each प्रणाली page and move the poपूर्णांकers accordingly.
 */
#घोषणा INC_IDX_ROUND(idx, size) ((idx) = ((idx) + 1) % (size))
अटल व्योम पंचांगc_etr_sg_table_populate(काष्ठा etr_sg_table *etr_table)
अणु
	dma_addr_t paddr;
	पूर्णांक i, type, nr_entries;
	पूर्णांक tpidx = 0; /* index to the current प्रणाली table_page */
	पूर्णांक sgtidx = 0;	/* index to the sg_table within the current syspage */
	पूर्णांक sgtentry = 0; /* the entry within the sg_table */
	पूर्णांक dpidx = 0; /* index to the current प्रणाली data_page */
	पूर्णांक spidx = 0; /* index to the SG page within the current data page */
	sgte_t *ptr; /* poपूर्णांकer to the table entry to fill */
	काष्ठा पंचांगc_sg_table *sg_table = etr_table->sg_table;
	dma_addr_t *table_daddrs = sg_table->table_pages.daddrs;
	dma_addr_t *data_daddrs = sg_table->data_pages.daddrs;

	nr_entries = पंचांगc_etr_sg_table_entries(sg_table->data_pages.nr_pages);
	/*
	 * Use the contiguous भव address of the table to update entries.
	 */
	ptr = sg_table->table_vaddr;
	/*
	 * Fill all the entries, except the last entry to aव्योम special
	 * checks within the loop.
	 */
	क्रम (i = 0; i < nr_entries - 1; i++) अणु
		अगर (sgtentry == ETR_SG_PTRS_PER_PAGE - 1) अणु
			/*
			 * Last entry in a sg_table page is a link address to
			 * the next table page. If this sg_table is the last
			 * one in the प्रणाली page, it links to the first
			 * sg_table in the next प्रणाली page. Otherwise, it
			 * links to the next sg_table page within the प्रणाली
			 * page.
			 */
			अगर (sgtidx == ETR_SG_PAGES_PER_SYSPAGE - 1) अणु
				paddr = table_daddrs[tpidx + 1];
			पूर्ण अन्यथा अणु
				paddr = table_daddrs[tpidx] +
					(ETR_SG_PAGE_SIZE * (sgtidx + 1));
			पूर्ण
			type = ETR_SG_ET_LINK;
		पूर्ण अन्यथा अणु
			/*
			 * Update the indices to the data_pages to poपूर्णांक to the
			 * next sg_page in the data buffer.
			 */
			type = ETR_SG_ET_NORMAL;
			paddr = data_daddrs[dpidx] + spidx * ETR_SG_PAGE_SIZE;
			अगर (!INC_IDX_ROUND(spidx, ETR_SG_PAGES_PER_SYSPAGE))
				dpidx++;
		पूर्ण
		*ptr++ = ETR_SG_ENTRY(paddr, type);
		/*
		 * Move to the next table poपूर्णांकer, moving the table page index
		 * अगर necessary
		 */
		अगर (!INC_IDX_ROUND(sgtentry, ETR_SG_PTRS_PER_PAGE)) अणु
			अगर (!INC_IDX_ROUND(sgtidx, ETR_SG_PAGES_PER_SYSPAGE))
				tpidx++;
		पूर्ण
	पूर्ण

	/* Set up the last entry, which is always a data poपूर्णांकer */
	paddr = data_daddrs[dpidx] + spidx * ETR_SG_PAGE_SIZE;
	*ptr++ = ETR_SG_ENTRY(paddr, ETR_SG_ET_LAST);
पूर्ण

/*
 * पंचांगc_init_etr_sg_table: Allocate a TMC ETR SG table, data buffer of @size and
 * populate the table.
 *
 * @dev		- Device poपूर्णांकer क्रम the TMC
 * @node	- NUMA node where the memory should be allocated
 * @size	- Total size of the data buffer
 * @pages	- Optional list of page भव address
 */
अटल काष्ठा etr_sg_table *
पंचांगc_init_etr_sg_table(काष्ठा device *dev, पूर्णांक node,
		      अचिन्हित दीर्घ size, व्योम **pages)
अणु
	पूर्णांक nr_entries, nr_tpages;
	पूर्णांक nr_dpages = size >> PAGE_SHIFT;
	काष्ठा पंचांगc_sg_table *sg_table;
	काष्ठा etr_sg_table *etr_table;

	etr_table = kzalloc(माप(*etr_table), GFP_KERNEL);
	अगर (!etr_table)
		वापस ERR_PTR(-ENOMEM);
	nr_entries = पंचांगc_etr_sg_table_entries(nr_dpages);
	nr_tpages = DIV_ROUND_UP(nr_entries, ETR_SG_PTRS_PER_SYSPAGE);

	sg_table = पंचांगc_alloc_sg_table(dev, node, nr_tpages, nr_dpages, pages);
	अगर (IS_ERR(sg_table)) अणु
		kमुक्त(etr_table);
		वापस ERR_CAST(sg_table);
	पूर्ण

	etr_table->sg_table = sg_table;
	/* TMC should use table base address क्रम DBA */
	etr_table->hwaddr = sg_table->table_daddr;
	पंचांगc_etr_sg_table_populate(etr_table);
	/* Sync the table pages क्रम the HW */
	पंचांगc_sg_table_sync_table(sg_table);
	पंचांगc_etr_sg_table_dump(etr_table);

	वापस etr_table;
पूर्ण

/*
 * पंचांगc_etr_alloc_flat_buf: Allocate a contiguous DMA buffer.
 */
अटल पूर्णांक पंचांगc_etr_alloc_flat_buf(काष्ठा पंचांगc_drvdata *drvdata,
				  काष्ठा etr_buf *etr_buf, पूर्णांक node,
				  व्योम **pages)
अणु
	काष्ठा etr_flat_buf *flat_buf;
	काष्ठा device *real_dev = drvdata->csdev->dev.parent;

	/* We cannot reuse existing pages क्रम flat buf */
	अगर (pages)
		वापस -EINVAL;

	flat_buf = kzalloc(माप(*flat_buf), GFP_KERNEL);
	अगर (!flat_buf)
		वापस -ENOMEM;

	flat_buf->vaddr = dma_alloc_coherent(real_dev, etr_buf->size,
					     &flat_buf->daddr, GFP_KERNEL);
	अगर (!flat_buf->vaddr) अणु
		kमुक्त(flat_buf);
		वापस -ENOMEM;
	पूर्ण

	flat_buf->size = etr_buf->size;
	flat_buf->dev = &drvdata->csdev->dev;
	etr_buf->hwaddr = flat_buf->daddr;
	etr_buf->mode = ETR_MODE_FLAT;
	etr_buf->निजी = flat_buf;
	वापस 0;
पूर्ण

अटल व्योम पंचांगc_etr_मुक्त_flat_buf(काष्ठा etr_buf *etr_buf)
अणु
	काष्ठा etr_flat_buf *flat_buf = etr_buf->निजी;

	अगर (flat_buf && flat_buf->daddr) अणु
		काष्ठा device *real_dev = flat_buf->dev->parent;

		dma_मुक्त_coherent(real_dev, flat_buf->size,
				  flat_buf->vaddr, flat_buf->daddr);
	पूर्ण
	kमुक्त(flat_buf);
पूर्ण

अटल व्योम पंचांगc_etr_sync_flat_buf(काष्ठा etr_buf *etr_buf, u64 rrp, u64 rwp)
अणु
	/*
	 * Adjust the buffer to poपूर्णांक to the beginning of the trace data
	 * and update the available trace data.
	 */
	etr_buf->offset = rrp - etr_buf->hwaddr;
	अगर (etr_buf->full)
		etr_buf->len = etr_buf->size;
	अन्यथा
		etr_buf->len = rwp - rrp;
पूर्ण

अटल sमाप_प्रकार पंचांगc_etr_get_data_flat_buf(काष्ठा etr_buf *etr_buf,
					 u64 offset, माप_प्रकार len, अक्षर **bufpp)
अणु
	काष्ठा etr_flat_buf *flat_buf = etr_buf->निजी;

	*bufpp = (अक्षर *)flat_buf->vaddr + offset;
	/*
	 * पंचांगc_etr_buf_get_data alपढ़ोy adjusts the length to handle
	 * buffer wrapping around.
	 */
	वापस len;
पूर्ण

अटल स्थिर काष्ठा etr_buf_operations etr_flat_buf_ops = अणु
	.alloc = पंचांगc_etr_alloc_flat_buf,
	.मुक्त = पंचांगc_etr_मुक्त_flat_buf,
	.sync = पंचांगc_etr_sync_flat_buf,
	.get_data = पंचांगc_etr_get_data_flat_buf,
पूर्ण;

/*
 * पंचांगc_etr_alloc_sg_buf: Allocate an SG buf @etr_buf. Setup the parameters
 * appropriately.
 */
अटल पूर्णांक पंचांगc_etr_alloc_sg_buf(काष्ठा पंचांगc_drvdata *drvdata,
				काष्ठा etr_buf *etr_buf, पूर्णांक node,
				व्योम **pages)
अणु
	काष्ठा etr_sg_table *etr_table;
	काष्ठा device *dev = &drvdata->csdev->dev;

	etr_table = पंचांगc_init_etr_sg_table(dev, node,
					  etr_buf->size, pages);
	अगर (IS_ERR(etr_table))
		वापस -ENOMEM;
	etr_buf->hwaddr = etr_table->hwaddr;
	etr_buf->mode = ETR_MODE_ETR_SG;
	etr_buf->निजी = etr_table;
	वापस 0;
पूर्ण

अटल व्योम पंचांगc_etr_मुक्त_sg_buf(काष्ठा etr_buf *etr_buf)
अणु
	काष्ठा etr_sg_table *etr_table = etr_buf->निजी;

	अगर (etr_table) अणु
		पंचांगc_मुक्त_sg_table(etr_table->sg_table);
		kमुक्त(etr_table);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार पंचांगc_etr_get_data_sg_buf(काष्ठा etr_buf *etr_buf, u64 offset,
				       माप_प्रकार len, अक्षर **bufpp)
अणु
	काष्ठा etr_sg_table *etr_table = etr_buf->निजी;

	वापस पंचांगc_sg_table_get_data(etr_table->sg_table, offset, len, bufpp);
पूर्ण

अटल व्योम पंचांगc_etr_sync_sg_buf(काष्ठा etr_buf *etr_buf, u64 rrp, u64 rwp)
अणु
	दीर्घ r_offset, w_offset;
	काष्ठा etr_sg_table *etr_table = etr_buf->निजी;
	काष्ठा पंचांगc_sg_table *table = etr_table->sg_table;

	/* Convert hw address to offset in the buffer */
	r_offset = पंचांगc_sg_get_data_page_offset(table, rrp);
	अगर (r_offset < 0) अणु
		dev_warn(table->dev,
			 "Unable to map RRP %llx to offset\n", rrp);
		etr_buf->len = 0;
		वापस;
	पूर्ण

	w_offset = पंचांगc_sg_get_data_page_offset(table, rwp);
	अगर (w_offset < 0) अणु
		dev_warn(table->dev,
			 "Unable to map RWP %llx to offset\n", rwp);
		etr_buf->len = 0;
		वापस;
	पूर्ण

	etr_buf->offset = r_offset;
	अगर (etr_buf->full)
		etr_buf->len = etr_buf->size;
	अन्यथा
		etr_buf->len = ((w_offset < r_offset) ? etr_buf->size : 0) +
				w_offset - r_offset;
	पंचांगc_sg_table_sync_data_range(table, r_offset, etr_buf->len);
पूर्ण

अटल स्थिर काष्ठा etr_buf_operations etr_sg_buf_ops = अणु
	.alloc = पंचांगc_etr_alloc_sg_buf,
	.मुक्त = पंचांगc_etr_मुक्त_sg_buf,
	.sync = पंचांगc_etr_sync_sg_buf,
	.get_data = पंचांगc_etr_get_data_sg_buf,
पूर्ण;

/*
 * TMC ETR could be connected to a CATU device, which can provide address
 * translation service. This is represented by the Output port of the TMC
 * (ETR) connected to the input port of the CATU.
 *
 * Returns	: coresight_device ptr क्रम the CATU device अगर a CATU is found.
 *		: शून्य otherwise.
 */
काष्ठा coresight_device *
पंचांगc_etr_get_catu_device(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	पूर्णांक i;
	काष्ठा coresight_device *पंचांगp, *etr = drvdata->csdev;

	अगर (!IS_ENABLED(CONFIG_CORESIGHT_CATU))
		वापस शून्य;

	क्रम (i = 0; i < etr->pdata->nr_outport; i++) अणु
		पंचांगp = etr->pdata->conns[i].child_dev;
		अगर (पंचांगp && coresight_is_catu_device(पंचांगp))
			वापस पंचांगp;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगc_etr_get_catu_device);

अटल अंतरभूत पूर्णांक पंचांगc_etr_enable_catu(काष्ठा पंचांगc_drvdata *drvdata,
				      काष्ठा etr_buf *etr_buf)
अणु
	काष्ठा coresight_device *catu = पंचांगc_etr_get_catu_device(drvdata);

	अगर (catu && helper_ops(catu)->enable)
		वापस helper_ops(catu)->enable(catu, etr_buf);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम पंचांगc_etr_disable_catu(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	काष्ठा coresight_device *catu = पंचांगc_etr_get_catu_device(drvdata);

	अगर (catu && helper_ops(catu)->disable)
		helper_ops(catu)->disable(catu, drvdata->etr_buf);
पूर्ण

अटल स्थिर काष्ठा etr_buf_operations *etr_buf_ops[] = अणु
	[ETR_MODE_FLAT] = &etr_flat_buf_ops,
	[ETR_MODE_ETR_SG] = &etr_sg_buf_ops,
	[ETR_MODE_CATU] = शून्य,
पूर्ण;

व्योम पंचांगc_etr_set_catu_ops(स्थिर काष्ठा etr_buf_operations *catu)
अणु
	etr_buf_ops[ETR_MODE_CATU] = catu;
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगc_etr_set_catu_ops);

व्योम पंचांगc_etr_हटाओ_catu_ops(व्योम)
अणु
	etr_buf_ops[ETR_MODE_CATU] = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(पंचांगc_etr_हटाओ_catu_ops);

अटल अंतरभूत पूर्णांक पंचांगc_etr_mode_alloc_buf(पूर्णांक mode,
					 काष्ठा पंचांगc_drvdata *drvdata,
					 काष्ठा etr_buf *etr_buf, पूर्णांक node,
					 व्योम **pages)
अणु
	पूर्णांक rc = -EINVAL;

	चयन (mode) अणु
	हाल ETR_MODE_FLAT:
	हाल ETR_MODE_ETR_SG:
	हाल ETR_MODE_CATU:
		अगर (etr_buf_ops[mode] && etr_buf_ops[mode]->alloc)
			rc = etr_buf_ops[mode]->alloc(drvdata, etr_buf,
						      node, pages);
		अगर (!rc)
			etr_buf->ops = etr_buf_ops[mode];
		वापस rc;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * पंचांगc_alloc_etr_buf: Allocate a buffer use by ETR.
 * @drvdata	: ETR device details.
 * @size	: size of the requested buffer.
 * @flags	: Required properties क्रम the buffer.
 * @node	: Node क्रम memory allocations.
 * @pages	: An optional list of pages.
 */
अटल काष्ठा etr_buf *पंचांगc_alloc_etr_buf(काष्ठा पंचांगc_drvdata *drvdata,
					 sमाप_प्रकार size, पूर्णांक flags,
					 पूर्णांक node, व्योम **pages)
अणु
	पूर्णांक rc = -ENOMEM;
	bool has_etr_sg, has_iommu;
	bool has_sg, has_catu;
	काष्ठा etr_buf *etr_buf;
	काष्ठा device *dev = &drvdata->csdev->dev;

	has_etr_sg = पंचांगc_etr_has_cap(drvdata, TMC_ETR_SG);
	has_iommu = iommu_get_करोमुख्य_क्रम_dev(dev->parent);
	has_catu = !!पंचांगc_etr_get_catu_device(drvdata);

	has_sg = has_catu || has_etr_sg;

	etr_buf = kzalloc(माप(*etr_buf), GFP_KERNEL);
	अगर (!etr_buf)
		वापस ERR_PTR(-ENOMEM);

	etr_buf->size = size;

	/*
	 * If we have to use an existing list of pages, we cannot reliably
	 * use a contiguous DMA memory (even अगर we have an IOMMU). Otherwise,
	 * we use the contiguous DMA memory अगर at least one of the following
	 * conditions is true:
	 *  a) The ETR cannot use Scatter-Gather.
	 *  b) we have a backing IOMMU
	 *  c) The requested memory size is smaller (< 1M).
	 *
	 * Fallback to available mechanisms.
	 *
	 */
	अगर (!pages &&
	    (!has_sg || has_iommu || size < SZ_1M))
		rc = पंचांगc_etr_mode_alloc_buf(ETR_MODE_FLAT, drvdata,
					    etr_buf, node, pages);
	अगर (rc && has_etr_sg)
		rc = पंचांगc_etr_mode_alloc_buf(ETR_MODE_ETR_SG, drvdata,
					    etr_buf, node, pages);
	अगर (rc && has_catu)
		rc = पंचांगc_etr_mode_alloc_buf(ETR_MODE_CATU, drvdata,
					    etr_buf, node, pages);
	अगर (rc) अणु
		kमुक्त(etr_buf);
		वापस ERR_PTR(rc);
	पूर्ण

	refcount_set(&etr_buf->refcount, 1);
	dev_dbg(dev, "allocated buffer of size %ldKB in mode %d\n",
		(अचिन्हित दीर्घ)size >> 10, etr_buf->mode);
	वापस etr_buf;
पूर्ण

अटल व्योम पंचांगc_मुक्त_etr_buf(काष्ठा etr_buf *etr_buf)
अणु
	WARN_ON(!etr_buf->ops || !etr_buf->ops->मुक्त);
	etr_buf->ops->मुक्त(etr_buf);
	kमुक्त(etr_buf);
पूर्ण

/*
 * पंचांगc_etr_buf_get_data: Get the poपूर्णांकer the trace data at @offset
 * with a maximum of @len bytes.
 * Returns: The size of the linear data available @pos, with *bufpp
 * updated to poपूर्णांक to the buffer.
 */
अटल sमाप_प्रकार पंचांगc_etr_buf_get_data(काष्ठा etr_buf *etr_buf,
				    u64 offset, माप_प्रकार len, अक्षर **bufpp)
अणु
	/* Adjust the length to limit this transaction to end of buffer */
	len = (len < (etr_buf->size - offset)) ? len : etr_buf->size - offset;

	वापस etr_buf->ops->get_data(etr_buf, (u64)offset, len, bufpp);
पूर्ण

अटल अंतरभूत s64
पंचांगc_etr_buf_insert_barrier_packet(काष्ठा etr_buf *etr_buf, u64 offset)
अणु
	sमाप_प्रकार len;
	अक्षर *bufp;

	len = पंचांगc_etr_buf_get_data(etr_buf, offset,
				   CORESIGHT_BARRIER_PKT_SIZE, &bufp);
	अगर (WARN_ON(len < CORESIGHT_BARRIER_PKT_SIZE))
		वापस -EINVAL;
	coresight_insert_barrier_packet(bufp);
	वापस offset + CORESIGHT_BARRIER_PKT_SIZE;
पूर्ण

/*
 * पंचांगc_sync_etr_buf: Sync the trace buffer availability with drvdata.
 * Makes sure the trace data is synced to the memory क्रम consumption.
 * @etr_buf->offset will hold the offset to the beginning of the trace data
 * within the buffer, with @etr_buf->len bytes to consume.
 */
अटल व्योम पंचांगc_sync_etr_buf(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	काष्ठा etr_buf *etr_buf = drvdata->etr_buf;
	u64 rrp, rwp;
	u32 status;

	rrp = पंचांगc_पढ़ो_rrp(drvdata);
	rwp = पंचांगc_पढ़ो_rwp(drvdata);
	status = पढ़ोl_relaxed(drvdata->base + TMC_STS);

	/*
	 * If there were memory errors in the session, truncate the
	 * buffer.
	 */
	अगर (WARN_ON_ONCE(status & TMC_STS_MEMERR)) अणु
		dev_dbg(&drvdata->csdev->dev,
			"tmc memory error detected, truncating buffer\n");
		etr_buf->len = 0;
		etr_buf->full = false;
		वापस;
	पूर्ण

	etr_buf->full = !!(status & TMC_STS_FULL);

	WARN_ON(!etr_buf->ops || !etr_buf->ops->sync);

	etr_buf->ops->sync(etr_buf, rrp, rwp);
पूर्ण

अटल व्योम __पंचांगc_etr_enable_hw(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	u32 axictl, sts;
	काष्ठा etr_buf *etr_buf = drvdata->etr_buf;

	CS_UNLOCK(drvdata->base);

	/* Wait क्रम TMCSReady bit to be set */
	पंचांगc_रुको_क्रम_पंचांगcपढ़ोy(drvdata);

	ग_लिखोl_relaxed(etr_buf->size / 4, drvdata->base + TMC_RSZ);
	ग_लिखोl_relaxed(TMC_MODE_CIRCULAR_BUFFER, drvdata->base + TMC_MODE);

	axictl = पढ़ोl_relaxed(drvdata->base + TMC_AXICTL);
	axictl &= ~TMC_AXICTL_CLEAR_MASK;
	axictl |= (TMC_AXICTL_PROT_CTL_B1 | TMC_AXICTL_WR_BURST_16);
	axictl |= TMC_AXICTL_AXCACHE_OS;

	अगर (पंचांगc_etr_has_cap(drvdata, TMC_ETR_AXI_ARCACHE)) अणु
		axictl &= ~TMC_AXICTL_ARCACHE_MASK;
		axictl |= TMC_AXICTL_ARCACHE_OS;
	पूर्ण

	अगर (etr_buf->mode == ETR_MODE_ETR_SG)
		axictl |= TMC_AXICTL_SCT_GAT_MODE;

	ग_लिखोl_relaxed(axictl, drvdata->base + TMC_AXICTL);
	पंचांगc_ग_लिखो_dba(drvdata, etr_buf->hwaddr);
	/*
	 * If the TMC poपूर्णांकers must be programmed beक्रमe the session,
	 * we have to set it properly (i.e, RRP/RWP to base address and
	 * STS to "not full").
	 */
	अगर (पंचांगc_etr_has_cap(drvdata, TMC_ETR_SAVE_RESTORE)) अणु
		पंचांगc_ग_लिखो_rrp(drvdata, etr_buf->hwaddr);
		पंचांगc_ग_लिखो_rwp(drvdata, etr_buf->hwaddr);
		sts = पढ़ोl_relaxed(drvdata->base + TMC_STS) & ~TMC_STS_FULL;
		ग_लिखोl_relaxed(sts, drvdata->base + TMC_STS);
	पूर्ण

	ग_लिखोl_relaxed(TMC_FFCR_EN_FMT | TMC_FFCR_EN_TI |
		       TMC_FFCR_FON_FLIN | TMC_FFCR_FON_TRIG_EVT |
		       TMC_FFCR_TRIGON_TRIGIN,
		       drvdata->base + TMC_FFCR);
	ग_लिखोl_relaxed(drvdata->trigger_cntr, drvdata->base + TMC_TRG);
	पंचांगc_enable_hw(drvdata);

	CS_LOCK(drvdata->base);
पूर्ण

अटल पूर्णांक पंचांगc_etr_enable_hw(काष्ठा पंचांगc_drvdata *drvdata,
			     काष्ठा etr_buf *etr_buf)
अणु
	पूर्णांक rc;

	/* Callers should provide an appropriate buffer क्रम use */
	अगर (WARN_ON(!etr_buf))
		वापस -EINVAL;

	अगर ((etr_buf->mode == ETR_MODE_ETR_SG) &&
	    WARN_ON(!पंचांगc_etr_has_cap(drvdata, TMC_ETR_SG)))
		वापस -EINVAL;

	अगर (WARN_ON(drvdata->etr_buf))
		वापस -EBUSY;

	/*
	 * If this ETR is connected to a CATU, enable it beक्रमe we turn
	 * this on.
	 */
	rc = पंचांगc_etr_enable_catu(drvdata, etr_buf);
	अगर (rc)
		वापस rc;
	rc = coresight_claim_device(drvdata->csdev);
	अगर (!rc) अणु
		drvdata->etr_buf = etr_buf;
		__पंचांगc_etr_enable_hw(drvdata);
	पूर्ण

	वापस rc;
पूर्ण

/*
 * Return the available trace data in the buffer (starts at etr_buf->offset,
 * limited by etr_buf->len) from @pos, with a maximum limit of @len,
 * also updating the @bufpp on where to find it. Since the trace data
 * starts at anywhere in the buffer, depending on the RRP, we adjust the
 * @len वापसed to handle buffer wrapping around.
 *
 * We are रक्षित here by drvdata->पढ़ोing != 0, which ensures the
 * sysfs_buf stays alive.
 */
sमाप_प्रकार पंचांगc_etr_get_sysfs_trace(काष्ठा पंचांगc_drvdata *drvdata,
				loff_t pos, माप_प्रकार len, अक्षर **bufpp)
अणु
	s64 offset;
	sमाप_प्रकार actual = len;
	काष्ठा etr_buf *etr_buf = drvdata->sysfs_buf;

	अगर (pos + actual > etr_buf->len)
		actual = etr_buf->len - pos;
	अगर (actual <= 0)
		वापस actual;

	/* Compute the offset from which we पढ़ो the data */
	offset = etr_buf->offset + pos;
	अगर (offset >= etr_buf->size)
		offset -= etr_buf->size;
	वापस पंचांगc_etr_buf_get_data(etr_buf, offset, actual, bufpp);
पूर्ण

अटल काष्ठा etr_buf *
पंचांगc_etr_setup_sysfs_buf(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	वापस पंचांगc_alloc_etr_buf(drvdata, drvdata->size,
				 0, cpu_to_node(0), शून्य);
पूर्ण

अटल व्योम
पंचांगc_etr_मुक्त_sysfs_buf(काष्ठा etr_buf *buf)
अणु
	अगर (buf)
		पंचांगc_मुक्त_etr_buf(buf);
पूर्ण

अटल व्योम पंचांगc_etr_sync_sysfs_buf(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	काष्ठा etr_buf *etr_buf = drvdata->etr_buf;

	अगर (WARN_ON(drvdata->sysfs_buf != etr_buf)) अणु
		पंचांगc_etr_मुक्त_sysfs_buf(drvdata->sysfs_buf);
		drvdata->sysfs_buf = शून्य;
	पूर्ण अन्यथा अणु
		पंचांगc_sync_etr_buf(drvdata);
		/*
		 * Insert barrier packets at the beginning, अगर there was
		 * an overflow.
		 */
		अगर (etr_buf->full)
			पंचांगc_etr_buf_insert_barrier_packet(etr_buf,
							  etr_buf->offset);
	पूर्ण
पूर्ण

अटल व्योम __पंचांगc_etr_disable_hw(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	CS_UNLOCK(drvdata->base);

	पंचांगc_flush_and_stop(drvdata);
	/*
	 * When operating in sysFS mode the content of the buffer needs to be
	 * पढ़ो beक्रमe the TMC is disabled.
	 */
	अगर (drvdata->mode == CS_MODE_SYSFS)
		पंचांगc_etr_sync_sysfs_buf(drvdata);

	पंचांगc_disable_hw(drvdata);

	CS_LOCK(drvdata->base);

पूर्ण

व्योम पंचांगc_etr_disable_hw(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	__पंचांगc_etr_disable_hw(drvdata);
	/* Disable CATU device अगर this ETR is connected to one */
	पंचांगc_etr_disable_catu(drvdata);
	coresight_disclaim_device(drvdata->csdev);
	/* Reset the ETR buf used by hardware */
	drvdata->etr_buf = शून्य;
पूर्ण

अटल पूर्णांक पंचांगc_enable_etr_sink_sysfs(काष्ठा coresight_device *csdev)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा पंचांगc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	काष्ठा etr_buf *sysfs_buf = शून्य, *new_buf = शून्य, *मुक्त_buf = शून्य;

	/*
	 * If we are enabling the ETR from disabled state, we need to make
	 * sure we have a buffer with the right size. The etr_buf is not reset
	 * immediately after we stop the tracing in SYSFS mode as we रुको क्रम
	 * the user to collect the data. We may be able to reuse the existing
	 * buffer, provided the size matches. Any allocation has to be करोne
	 * with the lock released.
	 */
	spin_lock_irqsave(&drvdata->spinlock, flags);
	sysfs_buf = READ_ONCE(drvdata->sysfs_buf);
	अगर (!sysfs_buf || (sysfs_buf->size != drvdata->size)) अणु
		spin_unlock_irqrestore(&drvdata->spinlock, flags);

		/* Allocate memory with the locks released */
		मुक्त_buf = new_buf = पंचांगc_etr_setup_sysfs_buf(drvdata);
		अगर (IS_ERR(new_buf))
			वापस PTR_ERR(new_buf);

		/* Let's try again */
		spin_lock_irqsave(&drvdata->spinlock, flags);
	पूर्ण

	अगर (drvdata->पढ़ोing || drvdata->mode == CS_MODE_PERF) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/*
	 * In sysFS mode we can have multiple ग_लिखोrs per sink.  Since this
	 * sink is alपढ़ोy enabled no memory is needed and the HW need not be
	 * touched, even अगर the buffer size has changed.
	 */
	अगर (drvdata->mode == CS_MODE_SYSFS) अणु
		atomic_inc(csdev->refcnt);
		जाओ out;
	पूर्ण

	/*
	 * If we करोn't have a buffer or it doesn't match the requested size,
	 * use the buffer allocated above. Otherwise reuse the existing buffer.
	 */
	sysfs_buf = READ_ONCE(drvdata->sysfs_buf);
	अगर (!sysfs_buf || (new_buf && sysfs_buf->size != new_buf->size)) अणु
		मुक्त_buf = sysfs_buf;
		drvdata->sysfs_buf = new_buf;
	पूर्ण

	ret = पंचांगc_etr_enable_hw(drvdata, drvdata->sysfs_buf);
	अगर (!ret) अणु
		drvdata->mode = CS_MODE_SYSFS;
		atomic_inc(csdev->refcnt);
	पूर्ण
out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	/* Free memory outside the spinlock अगर need be */
	अगर (मुक्त_buf)
		पंचांगc_etr_मुक्त_sysfs_buf(मुक्त_buf);

	अगर (!ret)
		dev_dbg(&csdev->dev, "TMC-ETR enabled\n");

	वापस ret;
पूर्ण

/*
 * alloc_etr_buf: Allocate ETR buffer क्रम use by perf.
 * The size of the hardware buffer is dependent on the size configured
 * via sysfs and the perf ring buffer size. We prefer to allocate the
 * largest possible size, scaling करोwn the size by half until it
 * reaches a minimum limit (1M), beyond which we give up.
 */
अटल काष्ठा etr_buf *
alloc_etr_buf(काष्ठा पंचांगc_drvdata *drvdata, काष्ठा perf_event *event,
	      पूर्णांक nr_pages, व्योम **pages, bool snapshot)
अणु
	पूर्णांक node;
	काष्ठा etr_buf *etr_buf;
	अचिन्हित दीर्घ size;

	node = (event->cpu == -1) ? NUMA_NO_NODE : cpu_to_node(event->cpu);
	/*
	 * Try to match the perf ring buffer size अगर it is larger
	 * than the size requested via sysfs.
	 */
	अगर ((nr_pages << PAGE_SHIFT) > drvdata->size) अणु
		etr_buf = पंचांगc_alloc_etr_buf(drvdata, (nr_pages << PAGE_SHIFT),
					    0, node, शून्य);
		अगर (!IS_ERR(etr_buf))
			जाओ करोne;
	पूर्ण

	/*
	 * Else चयन to configured size क्रम this ETR
	 * and scale करोwn until we hit the minimum limit.
	 */
	size = drvdata->size;
	करो अणु
		etr_buf = पंचांगc_alloc_etr_buf(drvdata, size, 0, node, शून्य);
		अगर (!IS_ERR(etr_buf))
			जाओ करोne;
		size /= 2;
	पूर्ण जबतक (size >= TMC_ETR_PERF_MIN_BUF_SIZE);

	वापस ERR_PTR(-ENOMEM);

करोne:
	वापस etr_buf;
पूर्ण

अटल काष्ठा etr_buf *
get_perf_etr_buf_cpu_wide(काष्ठा पंचांगc_drvdata *drvdata,
			  काष्ठा perf_event *event, पूर्णांक nr_pages,
			  व्योम **pages, bool snapshot)
अणु
	पूर्णांक ret;
	pid_t pid = task_pid_nr(event->owner);
	काष्ठा etr_buf *etr_buf;

retry:
	/*
	 * An etr_perf_buffer is associated with an event and holds a reference
	 * to the AUX ring buffer that was created क्रम that event.  In CPU-wide
	 * N:1 mode multiple events (one per CPU), each with its own AUX ring
	 * buffer, share a sink.  As such an etr_perf_buffer is created क्रम each
	 * event but a single etr_buf associated with the ETR is shared between
	 * them.  The last event in a trace session will copy the content of the
	 * etr_buf to its AUX ring buffer.  Ring buffer associated to other
	 * events are simply not used an मुक्तd as events are destoyed.  We still
	 * need to allocate a ring buffer क्रम each event since we करोn't know
	 * which event will be last.
	 */

	/*
	 * The first thing to करो here is check अगर an etr_buf has alपढ़ोy been
	 * allocated क्रम this session.  If so it is shared with this event,
	 * otherwise it is created.
	 */
	mutex_lock(&drvdata->idr_mutex);
	etr_buf = idr_find(&drvdata->idr, pid);
	अगर (etr_buf) अणु
		refcount_inc(&etr_buf->refcount);
		mutex_unlock(&drvdata->idr_mutex);
		वापस etr_buf;
	पूर्ण

	/* If we made it here no buffer has been allocated, करो so now. */
	mutex_unlock(&drvdata->idr_mutex);

	etr_buf = alloc_etr_buf(drvdata, event, nr_pages, pages, snapshot);
	अगर (IS_ERR(etr_buf))
		वापस etr_buf;

	/* Now that we have a buffer, add it to the IDR. */
	mutex_lock(&drvdata->idr_mutex);
	ret = idr_alloc(&drvdata->idr, etr_buf, pid, pid + 1, GFP_KERNEL);
	mutex_unlock(&drvdata->idr_mutex);

	/* Another event with this session ID has allocated this buffer. */
	अगर (ret == -ENOSPC) अणु
		पंचांगc_मुक्त_etr_buf(etr_buf);
		जाओ retry;
	पूर्ण

	/* The IDR can't allocate room क्रम a new session, abanकरोn ship. */
	अगर (ret == -ENOMEM) अणु
		पंचांगc_मुक्त_etr_buf(etr_buf);
		वापस ERR_PTR(ret);
	पूर्ण


	वापस etr_buf;
पूर्ण

अटल काष्ठा etr_buf *
get_perf_etr_buf_per_thपढ़ो(काष्ठा पंचांगc_drvdata *drvdata,
			    काष्ठा perf_event *event, पूर्णांक nr_pages,
			    व्योम **pages, bool snapshot)
अणु
	/*
	 * In per-thपढ़ो mode the etr_buf isn't shared, so just go ahead
	 * with memory allocation.
	 */
	वापस alloc_etr_buf(drvdata, event, nr_pages, pages, snapshot);
पूर्ण

अटल काष्ठा etr_buf *
get_perf_etr_buf(काष्ठा पंचांगc_drvdata *drvdata, काष्ठा perf_event *event,
		 पूर्णांक nr_pages, व्योम **pages, bool snapshot)
अणु
	अगर (event->cpu == -1)
		वापस get_perf_etr_buf_per_thपढ़ो(drvdata, event, nr_pages,
						   pages, snapshot);

	वापस get_perf_etr_buf_cpu_wide(drvdata, event, nr_pages,
					 pages, snapshot);
पूर्ण

अटल काष्ठा etr_perf_buffer *
पंचांगc_etr_setup_perf_buf(काष्ठा पंचांगc_drvdata *drvdata, काष्ठा perf_event *event,
		       पूर्णांक nr_pages, व्योम **pages, bool snapshot)
अणु
	पूर्णांक node;
	काष्ठा etr_buf *etr_buf;
	काष्ठा etr_perf_buffer *etr_perf;

	node = (event->cpu == -1) ? NUMA_NO_NODE : cpu_to_node(event->cpu);

	etr_perf = kzalloc_node(माप(*etr_perf), GFP_KERNEL, node);
	अगर (!etr_perf)
		वापस ERR_PTR(-ENOMEM);

	etr_buf = get_perf_etr_buf(drvdata, event, nr_pages, pages, snapshot);
	अगर (!IS_ERR(etr_buf))
		जाओ करोne;

	kमुक्त(etr_perf);
	वापस ERR_PTR(-ENOMEM);

करोne:
	/*
	 * Keep a reference to the ETR this buffer has been allocated क्रम
	 * in order to have access to the IDR in पंचांगc_मुक्त_etr_buffer().
	 */
	etr_perf->drvdata = drvdata;
	etr_perf->etr_buf = etr_buf;

	वापस etr_perf;
पूर्ण


अटल व्योम *पंचांगc_alloc_etr_buffer(काष्ठा coresight_device *csdev,
				  काष्ठा perf_event *event, व्योम **pages,
				  पूर्णांक nr_pages, bool snapshot)
अणु
	काष्ठा etr_perf_buffer *etr_perf;
	काष्ठा पंचांगc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	etr_perf = पंचांगc_etr_setup_perf_buf(drvdata, event,
					  nr_pages, pages, snapshot);
	अगर (IS_ERR(etr_perf)) अणु
		dev_dbg(&csdev->dev, "Unable to allocate ETR buffer\n");
		वापस शून्य;
	पूर्ण

	etr_perf->pid = task_pid_nr(event->owner);
	etr_perf->snapshot = snapshot;
	etr_perf->nr_pages = nr_pages;
	etr_perf->pages = pages;

	वापस etr_perf;
पूर्ण

अटल व्योम पंचांगc_मुक्त_etr_buffer(व्योम *config)
अणु
	काष्ठा etr_perf_buffer *etr_perf = config;
	काष्ठा पंचांगc_drvdata *drvdata = etr_perf->drvdata;
	काष्ठा etr_buf *buf, *etr_buf = etr_perf->etr_buf;

	अगर (!etr_buf)
		जाओ मुक्त_etr_perf_buffer;

	mutex_lock(&drvdata->idr_mutex);
	/* If we are not the last one to use the buffer, करोn't touch it. */
	अगर (!refcount_dec_and_test(&etr_buf->refcount)) अणु
		mutex_unlock(&drvdata->idr_mutex);
		जाओ मुक्त_etr_perf_buffer;
	पूर्ण

	/* We are the last one, हटाओ from the IDR and मुक्त the buffer. */
	buf = idr_हटाओ(&drvdata->idr, etr_perf->pid);
	mutex_unlock(&drvdata->idr_mutex);

	/*
	 * Something went very wrong अगर the buffer associated with this ID
	 * is not the same in the IDR.  Leak to aव्योम use after मुक्त.
	 */
	अगर (buf && WARN_ON(buf != etr_buf))
		जाओ मुक्त_etr_perf_buffer;

	पंचांगc_मुक्त_etr_buf(etr_perf->etr_buf);

मुक्त_etr_perf_buffer:
	kमुक्त(etr_perf);
पूर्ण

/*
 * पंचांगc_etr_sync_perf_buffer: Copy the actual trace data from the hardware
 * buffer to the perf ring buffer.
 */
अटल व्योम पंचांगc_etr_sync_perf_buffer(काष्ठा etr_perf_buffer *etr_perf,
				     अचिन्हित दीर्घ src_offset,
				     अचिन्हित दीर्घ to_copy)
अणु
	दीर्घ bytes;
	दीर्घ pg_idx, pg_offset;
	अचिन्हित दीर्घ head = etr_perf->head;
	अक्षर **dst_pages, *src_buf;
	काष्ठा etr_buf *etr_buf = etr_perf->etr_buf;

	head = etr_perf->head;
	pg_idx = head >> PAGE_SHIFT;
	pg_offset = head & (PAGE_SIZE - 1);
	dst_pages = (अक्षर **)etr_perf->pages;

	जबतक (to_copy > 0) अणु
		/*
		 * In one iteration, we can copy minimum of :
		 *  1) what is available in the source buffer,
		 *  2) what is available in the source buffer, beक्रमe it
		 *     wraps around.
		 *  3) what is available in the destination page.
		 * in one iteration.
		 */
		अगर (src_offset >= etr_buf->size)
			src_offset -= etr_buf->size;
		bytes = पंचांगc_etr_buf_get_data(etr_buf, src_offset, to_copy,
					     &src_buf);
		अगर (WARN_ON_ONCE(bytes <= 0))
			अवरोध;
		bytes = min(bytes, (दीर्घ)(PAGE_SIZE - pg_offset));

		स_नकल(dst_pages[pg_idx] + pg_offset, src_buf, bytes);

		to_copy -= bytes;

		/* Move destination poपूर्णांकers */
		pg_offset += bytes;
		अगर (pg_offset == PAGE_SIZE) अणु
			pg_offset = 0;
			अगर (++pg_idx == etr_perf->nr_pages)
				pg_idx = 0;
		पूर्ण

		/* Move source poपूर्णांकers */
		src_offset += bytes;
	पूर्ण
पूर्ण

/*
 * पंचांगc_update_etr_buffer : Update the perf ring buffer with the
 * available trace data. We use software द्विगुन buffering at the moment.
 *
 * TODO: Add support क्रम reusing the perf ring buffer.
 */
अटल अचिन्हित दीर्घ
पंचांगc_update_etr_buffer(काष्ठा coresight_device *csdev,
		      काष्ठा perf_output_handle *handle,
		      व्योम *config)
अणु
	bool lost = false;
	अचिन्हित दीर्घ flags, offset, size = 0;
	काष्ठा पंचांगc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	काष्ठा etr_perf_buffer *etr_perf = config;
	काष्ठा etr_buf *etr_buf = etr_perf->etr_buf;

	spin_lock_irqsave(&drvdata->spinlock, flags);

	/* Don't करो anything अगर another tracer is using this sink */
	अगर (atomic_पढ़ो(csdev->refcnt) != 1) अणु
		spin_unlock_irqrestore(&drvdata->spinlock, flags);
		जाओ out;
	पूर्ण

	अगर (WARN_ON(drvdata->perf_buf != etr_buf)) अणु
		lost = true;
		spin_unlock_irqrestore(&drvdata->spinlock, flags);
		जाओ out;
	पूर्ण

	CS_UNLOCK(drvdata->base);

	पंचांगc_flush_and_stop(drvdata);
	पंचांगc_sync_etr_buf(drvdata);

	CS_LOCK(drvdata->base);
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	lost = etr_buf->full;
	offset = etr_buf->offset;
	size = etr_buf->len;

	/*
	 * The ETR buffer may be bigger than the space available in the
	 * perf ring buffer (handle->size).  If so advance the offset so that we
	 * get the latest trace data.  In snapshot mode none of that matters
	 * since we are expected to clobber stale data in favour of the latest
	 * traces.
	 */
	अगर (!etr_perf->snapshot && size > handle->size) अणु
		u32 mask = पंचांगc_get_memwidth_mask(drvdata);

		/*
		 * Make sure the new size is aligned in accordance with the
		 * requirement explained in function पंचांगc_get_memwidth_mask().
		 */
		size = handle->size & mask;
		offset = etr_buf->offset + etr_buf->len - size;

		अगर (offset >= etr_buf->size)
			offset -= etr_buf->size;
		lost = true;
	पूर्ण

	/* Insert barrier packets at the beginning, अगर there was an overflow */
	अगर (lost)
		पंचांगc_etr_buf_insert_barrier_packet(etr_buf, offset);
	पंचांगc_etr_sync_perf_buffer(etr_perf, offset, size);

	/*
	 * In snapshot mode we simply increment the head by the number of byte
	 * that were written.  User space function  cs_eपंचांग_find_snapshot() will
	 * figure out how many bytes to get from the AUX buffer based on the
	 * position of the head.
	 */
	अगर (etr_perf->snapshot)
		handle->head += size;
out:
	/*
	 * Don't set the TRUNCATED flag in snapshot mode because 1) the
	 * captured buffer is expected to be truncated and 2) a full buffer
	 * prevents the event from being re-enabled by the perf core,
	 * resulting in stale data being send to user space.
	 */
	अगर (!etr_perf->snapshot && lost)
		perf_aux_output_flag(handle, PERF_AUX_FLAG_TRUNCATED);
	वापस size;
पूर्ण

अटल पूर्णांक पंचांगc_enable_etr_sink_perf(काष्ठा coresight_device *csdev, व्योम *data)
अणु
	पूर्णांक rc = 0;
	pid_t pid;
	अचिन्हित दीर्घ flags;
	काष्ठा पंचांगc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	काष्ठा perf_output_handle *handle = data;
	काष्ठा etr_perf_buffer *etr_perf = eपंचांग_perf_sink_config(handle);

	spin_lock_irqsave(&drvdata->spinlock, flags);
	 /* Don't use this sink अगर it is alपढ़ोy claimed by sysFS */
	अगर (drvdata->mode == CS_MODE_SYSFS) अणु
		rc = -EBUSY;
		जाओ unlock_out;
	पूर्ण

	अगर (WARN_ON(!etr_perf || !etr_perf->etr_buf)) अणु
		rc = -EINVAL;
		जाओ unlock_out;
	पूर्ण

	/* Get a handle on the pid of the process to monitor */
	pid = etr_perf->pid;

	/* Do not proceed अगर this device is associated with another session */
	अगर (drvdata->pid != -1 && drvdata->pid != pid) अणु
		rc = -EBUSY;
		जाओ unlock_out;
	पूर्ण

	etr_perf->head = PERF_IDX2OFF(handle->head, etr_perf);

	/*
	 * No HW configuration is needed अगर the sink is alपढ़ोy in
	 * use क्रम this session.
	 */
	अगर (drvdata->pid == pid) अणु
		atomic_inc(csdev->refcnt);
		जाओ unlock_out;
	पूर्ण

	rc = पंचांगc_etr_enable_hw(drvdata, etr_perf->etr_buf);
	अगर (!rc) अणु
		/* Associate with monitored process. */
		drvdata->pid = pid;
		drvdata->mode = CS_MODE_PERF;
		drvdata->perf_buf = etr_perf->etr_buf;
		atomic_inc(csdev->refcnt);
	पूर्ण

unlock_out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);
	वापस rc;
पूर्ण

अटल पूर्णांक पंचांगc_enable_etr_sink(काष्ठा coresight_device *csdev,
			       u32 mode, व्योम *data)
अणु
	चयन (mode) अणु
	हाल CS_MODE_SYSFS:
		वापस पंचांगc_enable_etr_sink_sysfs(csdev);
	हाल CS_MODE_PERF:
		वापस पंचांगc_enable_etr_sink_perf(csdev, data);
	पूर्ण

	/* We shouldn't be here */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक पंचांगc_disable_etr_sink(काष्ठा coresight_device *csdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा पंचांगc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	spin_lock_irqsave(&drvdata->spinlock, flags);

	अगर (drvdata->पढ़ोing) अणु
		spin_unlock_irqrestore(&drvdata->spinlock, flags);
		वापस -EBUSY;
	पूर्ण

	अगर (atomic_dec_वापस(csdev->refcnt)) अणु
		spin_unlock_irqrestore(&drvdata->spinlock, flags);
		वापस -EBUSY;
	पूर्ण

	/* Complain अगर we (somehow) got out of sync */
	WARN_ON_ONCE(drvdata->mode == CS_MODE_DISABLED);
	पंचांगc_etr_disable_hw(drvdata);
	/* Dissociate from monitored process. */
	drvdata->pid = -1;
	drvdata->mode = CS_MODE_DISABLED;
	/* Reset perf specअगरic data */
	drvdata->perf_buf = शून्य;

	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	dev_dbg(&csdev->dev, "TMC-ETR disabled\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा coresight_ops_sink पंचांगc_etr_sink_ops = अणु
	.enable		= पंचांगc_enable_etr_sink,
	.disable	= पंचांगc_disable_etr_sink,
	.alloc_buffer	= पंचांगc_alloc_etr_buffer,
	.update_buffer	= पंचांगc_update_etr_buffer,
	.मुक्त_buffer	= पंचांगc_मुक्त_etr_buffer,
पूर्ण;

स्थिर काष्ठा coresight_ops पंचांगc_etr_cs_ops = अणु
	.sink_ops	= &पंचांगc_etr_sink_ops,
पूर्ण;

पूर्णांक पंचांगc_पढ़ो_prepare_etr(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	/* config types are set a boot समय and never change */
	अगर (WARN_ON_ONCE(drvdata->config_type != TMC_CONFIG_TYPE_ETR))
		वापस -EINVAL;

	spin_lock_irqsave(&drvdata->spinlock, flags);
	अगर (drvdata->पढ़ोing) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/*
	 * We can safely allow पढ़ोs even अगर the ETR is operating in PERF mode,
	 * since the sysfs session is captured in mode specअगरic data.
	 * If drvdata::sysfs_data is शून्य the trace data has been पढ़ो alपढ़ोy.
	 */
	अगर (!drvdata->sysfs_buf) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Disable the TMC अगर we are trying to पढ़ो from a running session. */
	अगर (drvdata->mode == CS_MODE_SYSFS)
		__पंचांगc_etr_disable_hw(drvdata);

	drvdata->पढ़ोing = true;
out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	वापस ret;
पूर्ण

पूर्णांक पंचांगc_पढ़ो_unprepare_etr(काष्ठा पंचांगc_drvdata *drvdata)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा etr_buf *sysfs_buf = शून्य;

	/* config types are set a boot समय and never change */
	अगर (WARN_ON_ONCE(drvdata->config_type != TMC_CONFIG_TYPE_ETR))
		वापस -EINVAL;

	spin_lock_irqsave(&drvdata->spinlock, flags);

	/* RE-enable the TMC अगर need be */
	अगर (drvdata->mode == CS_MODE_SYSFS) अणु
		/*
		 * The trace run will जारी with the same allocated trace
		 * buffer. Since the tracer is still enabled drvdata::buf can't
		 * be शून्य.
		 */
		__पंचांगc_etr_enable_hw(drvdata);
	पूर्ण अन्यथा अणु
		/*
		 * The ETR is not tracing and the buffer was just पढ़ो.
		 * As such prepare to मुक्त the trace buffer.
		 */
		sysfs_buf = drvdata->sysfs_buf;
		drvdata->sysfs_buf = शून्य;
	पूर्ण

	drvdata->पढ़ोing = false;
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	/* Free allocated memory out side of the spinlock */
	अगर (sysfs_buf)
		पंचांगc_etr_मुक्त_sysfs_buf(sysfs_buf);

	वापस 0;
पूर्ण
