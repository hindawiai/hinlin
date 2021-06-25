<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Arm Limited. All rights reserved.
 *
 * Coresight Address Translation Unit support
 *
 * Author: Suzuki K Poulose <suzuki.poulose@arm.com>
 */

#समावेश <linux/amba/bus.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश "coresight-catu.h"
#समावेश "coresight-priv.h"
#समावेश "coresight-tmc.h"

#घोषणा csdev_to_catu_drvdata(csdev)	\
	dev_get_drvdata(csdev->dev.parent)

/* Verbose output क्रम CATU table contents */
#अगर_घोषित CATU_DEBUG
#घोषणा catu_dbg(x, ...) dev_dbg(x, __VA_ARGS__)
#अन्यथा
#घोषणा catu_dbg(x, ...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

DEFINE_CORESIGHT_DEVLIST(catu_devs, "catu");

काष्ठा catu_etr_buf अणु
	काष्ठा पंचांगc_sg_table *catu_table;
	dma_addr_t sladdr;
पूर्ण;

/*
 * CATU uses a page size of 4KB क्रम page tables as well as data pages.
 * Each 64bit entry in the table has the following क्रमmat.
 *
 *	63			12	1  0
 *	------------------------------------
 *	|	 Address [63-12] | SBZ	| V|
 *	------------------------------------
 *
 * Where bit[0] V indicates अगर the address is valid or not.
 * Each 4K table pages have upto 256 data page poपूर्णांकers, taking upto 2K
 * size. There are two Link poपूर्णांकers, poपूर्णांकing to the previous and next
 * table pages respectively at the end of the 4K page. (i.e, entry 510
 * and 511).
 *  E.g, a table of two pages could look like :
 *
 *                 Table Page 0               Table Page 1
 * SLADDR ===> x------------------x  x--> x-----------------x
 * INADDR    ->|  Page 0      | V |  |    | Page 256    | V | <- INADDR+1M
 *             |------------------|  |    |-----------------|
 * INADDR+4K ->|  Page 1      | V |  |    |                 |
 *             |------------------|  |    |-----------------|
 *             |  Page 2      | V |  |    |                 |
 *             |------------------|  |    |-----------------|
 *             |   ...        | V |  |    |    ...          |
 *             |------------------|  |    |-----------------|
 * INADDR+1020K|  Page 255    | V |  |    |   Page 511  | V |
 * SLADDR+2K==>|------------------|  |    |-----------------|
 *             |  UNUSED      |   |  |    |                 |
 *             |------------------|  |    |                 |
 *             |  UNUSED      |   |  |    |                 |
 *             |------------------|  |    |                 |
 *             |    ...       |   |  |    |                 |
 *             |------------------|  |    |-----------------|
 *             |   IGNORED    | 0 |  |    | Table Page 0| 1 |
 *             |------------------|  |    |-----------------|
 *             |  Table Page 1| 1 |--x    | IGNORED     | 0 |
 *             x------------------x       x-----------------x
 * SLADDR+4K==>
 *
 * The base input address (used by the ETR, programmed in INADDR_अणुLO,HIपूर्ण)
 * must be aligned to 1MB (the size addressable by a single page table).
 * The CATU maps INADDRअणुLO:HIपूर्ण to the first page in the table poपूर्णांकed
 * to by SLADDRअणुLO:HIपूर्ण and so on.
 *
 */
प्रकार u64 cate_t;

#घोषणा CATU_PAGE_SHIFT		12
#घोषणा CATU_PAGE_SIZE		(1UL << CATU_PAGE_SHIFT)
#घोषणा CATU_PAGES_PER_SYSPAGE	(PAGE_SIZE / CATU_PAGE_SIZE)

/* Page poपूर्णांकers are only allocated in the first 2K half */
#घोषणा CATU_PTRS_PER_PAGE	((CATU_PAGE_SIZE >> 1) / माप(cate_t))
#घोषणा CATU_PTRS_PER_SYSPAGE	(CATU_PAGES_PER_SYSPAGE * CATU_PTRS_PER_PAGE)
#घोषणा CATU_LINK_PREV		((CATU_PAGE_SIZE / माप(cate_t)) - 2)
#घोषणा CATU_LINK_NEXT		((CATU_PAGE_SIZE / माप(cate_t)) - 1)

#घोषणा CATU_ADDR_SHIFT		12
#घोषणा CATU_ADDR_MASK		~(((cate_t)1 << CATU_ADDR_SHIFT) - 1)
#घोषणा CATU_ENTRY_VALID	((cate_t)0x1)
#घोषणा CATU_VALID_ENTRY(addr) \
	(((cate_t)(addr) & CATU_ADDR_MASK) | CATU_ENTRY_VALID)
#घोषणा CATU_ENTRY_ADDR(entry)	((cate_t)(entry) & ~((cate_t)CATU_ENTRY_VALID))

/* CATU expects the INADDR to be aligned to 1M. */
#घोषणा CATU_DEFAULT_INADDR	(1ULL << 20)

/*
 * catu_get_table : Retrieve the table poपूर्णांकers क्रम the given @offset
 * within the buffer. The buffer is wrapped around to a valid offset.
 *
 * Returns : The CPU भव address क्रम the beginning of the table
 * containing the data page poपूर्णांकer क्रम @offset. If @daddrp is not शून्य,
 * @daddrp poपूर्णांकs the DMA address of the beginning of the table.
 */
अटल अंतरभूत cate_t *catu_get_table(काष्ठा पंचांगc_sg_table *catu_table,
				     अचिन्हित दीर्घ offset,
				     dma_addr_t *daddrp)
अणु
	अचिन्हित दीर्घ buf_size = पंचांगc_sg_table_buf_size(catu_table);
	अचिन्हित पूर्णांक table_nr, pg_idx, pg_offset;
	काष्ठा पंचांगc_pages *table_pages = &catu_table->table_pages;
	व्योम *ptr;

	/* Make sure offset is within the range */
	offset %= buf_size;

	/*
	 * Each table can address 1MB and a single kernel page can
	 * contain "CATU_PAGES_PER_SYSPAGE" CATU tables.
	 */
	table_nr = offset >> 20;
	/* Find the table page where the table_nr lies in */
	pg_idx = table_nr / CATU_PAGES_PER_SYSPAGE;
	pg_offset = (table_nr % CATU_PAGES_PER_SYSPAGE) * CATU_PAGE_SIZE;
	अगर (daddrp)
		*daddrp = table_pages->daddrs[pg_idx] + pg_offset;
	ptr = page_address(table_pages->pages[pg_idx]);
	वापस (cate_t *)((अचिन्हित दीर्घ)ptr + pg_offset);
पूर्ण

#अगर_घोषित CATU_DEBUG
अटल व्योम catu_dump_table(काष्ठा पंचांगc_sg_table *catu_table)
अणु
	पूर्णांक i;
	cate_t *table;
	अचिन्हित दीर्घ table_end, buf_size, offset = 0;

	buf_size = पंचांगc_sg_table_buf_size(catu_table);
	dev_dbg(catu_table->dev,
		"Dump table %p, tdaddr: %llx\n",
		catu_table, catu_table->table_daddr);

	जबतक (offset < buf_size) अणु
		table_end = offset + SZ_1M < buf_size ?
			    offset + SZ_1M : buf_size;
		table = catu_get_table(catu_table, offset, शून्य);
		क्रम (i = 0; offset < table_end; i++, offset += CATU_PAGE_SIZE)
			dev_dbg(catu_table->dev, "%d: %llx\n", i, table[i]);
		dev_dbg(catu_table->dev, "Prev : %llx, Next: %llx\n",
			table[CATU_LINK_PREV], table[CATU_LINK_NEXT]);
		dev_dbg(catu_table->dev, "== End of sub-table ===");
	पूर्ण
	dev_dbg(catu_table->dev, "== End of Table ===");
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम catu_dump_table(काष्ठा पंचांगc_sg_table *catu_table)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत cate_t catu_make_entry(dma_addr_t addr)
अणु
	वापस addr ? CATU_VALID_ENTRY(addr) : 0;
पूर्ण

/*
 * catu_populate_table : Populate the given CATU table.
 * The table is always populated as a circular table.
 * i.e, the "prev" link of the "first" table poपूर्णांकs to the "last"
 * table and the "next" link of the "last" table poपूर्णांकs to the
 * "first" table. The buffer should be made linear by calling
 * catu_set_table().
 */
अटल व्योम
catu_populate_table(काष्ठा पंचांगc_sg_table *catu_table)
अणु
	पूर्णांक i;
	पूर्णांक sys_pidx;	/* Index to current प्रणाली data page */
	पूर्णांक catu_pidx;	/* Index of CATU page within the प्रणाली data page */
	अचिन्हित दीर्घ offset, buf_size, table_end;
	dma_addr_t data_daddr;
	dma_addr_t prev_taddr, next_taddr, cur_taddr;
	cate_t *table_ptr, *next_table;

	buf_size = पंचांगc_sg_table_buf_size(catu_table);
	sys_pidx = catu_pidx = 0;
	offset = 0;

	table_ptr = catu_get_table(catu_table, 0, &cur_taddr);
	prev_taddr = 0;	/* Prev link क्रम the first table */

	जबतक (offset < buf_size) अणु
		/*
		 * The @offset is always 1M aligned here and we have an
		 * empty table @table_ptr to fill. Each table can address
		 * upto 1MB data buffer. The last table may have fewer
		 * entries अगर the buffer size is not aligned.
		 */
		table_end = (offset + SZ_1M) < buf_size ?
			    (offset + SZ_1M) : buf_size;
		क्रम (i = 0; offset < table_end;
		     i++, offset += CATU_PAGE_SIZE) अणु

			data_daddr = catu_table->data_pages.daddrs[sys_pidx] +
				     catu_pidx * CATU_PAGE_SIZE;
			catu_dbg(catu_table->dev,
				"[table %5ld:%03d] 0x%llx\n",
				(offset >> 20), i, data_daddr);
			table_ptr[i] = catu_make_entry(data_daddr);
			/* Move the poपूर्णांकers क्रम data pages */
			catu_pidx = (catu_pidx + 1) % CATU_PAGES_PER_SYSPAGE;
			अगर (catu_pidx == 0)
				sys_pidx++;
		पूर्ण

		/*
		 * If we have finished all the valid entries, fill the rest of
		 * the table (i.e, last table page) with invalid entries,
		 * to fail the lookups.
		 */
		अगर (offset == buf_size) अणु
			स_रखो(&table_ptr[i], 0,
			       माप(cate_t) * (CATU_PTRS_PER_PAGE - i));
			next_taddr = 0;
		पूर्ण अन्यथा अणु
			next_table = catu_get_table(catu_table,
						    offset, &next_taddr);
		पूर्ण

		table_ptr[CATU_LINK_PREV] = catu_make_entry(prev_taddr);
		table_ptr[CATU_LINK_NEXT] = catu_make_entry(next_taddr);

		catu_dbg(catu_table->dev,
			"[table%5ld]: Cur: 0x%llx Prev: 0x%llx, Next: 0x%llx\n",
			(offset >> 20) - 1,  cur_taddr, prev_taddr, next_taddr);

		/* Update the prev/next addresses */
		अगर (next_taddr) अणु
			prev_taddr = cur_taddr;
			cur_taddr = next_taddr;
			table_ptr = next_table;
		पूर्ण
	पूर्ण

	/* Sync the table क्रम device */
	पंचांगc_sg_table_sync_table(catu_table);
पूर्ण

अटल काष्ठा पंचांगc_sg_table *
catu_init_sg_table(काष्ठा device *catu_dev, पूर्णांक node,
		   sमाप_प्रकार size, व्योम **pages)
अणु
	पूर्णांक nr_tpages;
	काष्ठा पंचांगc_sg_table *catu_table;

	/*
	 * Each table can address upto 1MB and we can have
	 * CATU_PAGES_PER_SYSPAGE tables in a प्रणाली page.
	 */
	nr_tpages = DIV_ROUND_UP(size, SZ_1M) / CATU_PAGES_PER_SYSPAGE;
	catu_table = पंचांगc_alloc_sg_table(catu_dev, node, nr_tpages,
					size >> PAGE_SHIFT, pages);
	अगर (IS_ERR(catu_table))
		वापस catu_table;

	catu_populate_table(catu_table);
	dev_dbg(catu_dev,
		"Setup table %p, size %ldKB, %d table pages\n",
		catu_table, (अचिन्हित दीर्घ)size >> 10,  nr_tpages);
	catu_dump_table(catu_table);
	वापस catu_table;
पूर्ण

अटल व्योम catu_मुक्त_etr_buf(काष्ठा etr_buf *etr_buf)
अणु
	काष्ठा catu_etr_buf *catu_buf;

	अगर (!etr_buf || etr_buf->mode != ETR_MODE_CATU || !etr_buf->निजी)
		वापस;

	catu_buf = etr_buf->निजी;
	पंचांगc_मुक्त_sg_table(catu_buf->catu_table);
	kमुक्त(catu_buf);
पूर्ण

अटल sमाप_प्रकार catu_get_data_etr_buf(काष्ठा etr_buf *etr_buf, u64 offset,
				     माप_प्रकार len, अक्षर **bufpp)
अणु
	काष्ठा catu_etr_buf *catu_buf = etr_buf->निजी;

	वापस पंचांगc_sg_table_get_data(catu_buf->catu_table, offset, len, bufpp);
पूर्ण

अटल व्योम catu_sync_etr_buf(काष्ठा etr_buf *etr_buf, u64 rrp, u64 rwp)
अणु
	काष्ठा catu_etr_buf *catu_buf = etr_buf->निजी;
	काष्ठा पंचांगc_sg_table *catu_table = catu_buf->catu_table;
	u64 r_offset, w_offset;

	/*
	 * ETR started off at etr_buf->hwaddr. Convert the RRP/RWP to
	 * offsets within the trace buffer.
	 */
	r_offset = rrp - etr_buf->hwaddr;
	w_offset = rwp - etr_buf->hwaddr;

	अगर (!etr_buf->full) अणु
		etr_buf->len = w_offset - r_offset;
		अगर (w_offset < r_offset)
			etr_buf->len += etr_buf->size;
	पूर्ण अन्यथा अणु
		etr_buf->len = etr_buf->size;
	पूर्ण

	etr_buf->offset = r_offset;
	पंचांगc_sg_table_sync_data_range(catu_table, r_offset, etr_buf->len);
पूर्ण

अटल पूर्णांक catu_alloc_etr_buf(काष्ठा पंचांगc_drvdata *पंचांगc_drvdata,
			      काष्ठा etr_buf *etr_buf, पूर्णांक node, व्योम **pages)
अणु
	काष्ठा coresight_device *csdev;
	काष्ठा पंचांगc_sg_table *catu_table;
	काष्ठा catu_etr_buf *catu_buf;

	csdev = पंचांगc_etr_get_catu_device(पंचांगc_drvdata);
	अगर (!csdev)
		वापस -ENODEV;
	catu_buf = kzalloc(माप(*catu_buf), GFP_KERNEL);
	अगर (!catu_buf)
		वापस -ENOMEM;

	catu_table = catu_init_sg_table(&csdev->dev, node,
					etr_buf->size, pages);
	अगर (IS_ERR(catu_table)) अणु
		kमुक्त(catu_buf);
		वापस PTR_ERR(catu_table);
	पूर्ण

	etr_buf->mode = ETR_MODE_CATU;
	etr_buf->निजी = catu_buf;
	etr_buf->hwaddr = CATU_DEFAULT_INADDR;

	catu_buf->catu_table = catu_table;
	/* Get the table base address */
	catu_buf->sladdr = catu_table->table_daddr;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा etr_buf_operations etr_catu_buf_ops = अणु
	.alloc = catu_alloc_etr_buf,
	.मुक्त = catu_मुक्त_etr_buf,
	.sync = catu_sync_etr_buf,
	.get_data = catu_get_data_etr_buf,
पूर्ण;

coresight_simple_reg32(काष्ठा catu_drvdata, devid, CORESIGHT_DEVID);
coresight_simple_reg32(काष्ठा catu_drvdata, control, CATU_CONTROL);
coresight_simple_reg32(काष्ठा catu_drvdata, status, CATU_STATUS);
coresight_simple_reg32(काष्ठा catu_drvdata, mode, CATU_MODE);
coresight_simple_reg32(काष्ठा catu_drvdata, axictrl, CATU_AXICTRL);
coresight_simple_reg32(काष्ठा catu_drvdata, irqen, CATU_IRQEN);
coresight_simple_reg64(काष्ठा catu_drvdata, sladdr,
		       CATU_SLADDRLO, CATU_SLADDRHI);
coresight_simple_reg64(काष्ठा catu_drvdata, inaddr,
		       CATU_INADDRLO, CATU_INADDRHI);

अटल काष्ठा attribute *catu_mgmt_attrs[] = अणु
	&dev_attr_devid.attr,
	&dev_attr_control.attr,
	&dev_attr_status.attr,
	&dev_attr_mode.attr,
	&dev_attr_axictrl.attr,
	&dev_attr_irqen.attr,
	&dev_attr_sladdr.attr,
	&dev_attr_inaddr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group catu_mgmt_group = अणु
	.attrs = catu_mgmt_attrs,
	.name = "mgmt",
पूर्ण;

अटल स्थिर काष्ठा attribute_group *catu_groups[] = अणु
	&catu_mgmt_group,
	शून्य,
पूर्ण;


अटल अंतरभूत पूर्णांक catu_रुको_क्रम_पढ़ोy(काष्ठा catu_drvdata *drvdata)
अणु
	काष्ठा csdev_access *csa = &drvdata->csdev->access;

	वापस coresight_समयout(csa, CATU_STATUS, CATU_STATUS_READY, 1);
पूर्ण

अटल पूर्णांक catu_enable_hw(काष्ठा catu_drvdata *drvdata, व्योम *data)
अणु
	पूर्णांक rc;
	u32 control, mode;
	काष्ठा etr_buf *etr_buf = data;
	काष्ठा device *dev = &drvdata->csdev->dev;
	काष्ठा coresight_device *csdev = drvdata->csdev;

	अगर (catu_रुको_क्रम_पढ़ोy(drvdata))
		dev_warn(dev, "Timeout while waiting for READY\n");

	control = catu_पढ़ो_control(drvdata);
	अगर (control & BIT(CATU_CONTROL_ENABLE)) अणु
		dev_warn(dev, "CATU is already enabled\n");
		वापस -EBUSY;
	पूर्ण

	rc = coresight_claim_device_unlocked(csdev);
	अगर (rc)
		वापस rc;

	control |= BIT(CATU_CONTROL_ENABLE);

	अगर (etr_buf && etr_buf->mode == ETR_MODE_CATU) अणु
		काष्ठा catu_etr_buf *catu_buf = etr_buf->निजी;

		mode = CATU_MODE_TRANSLATE;
		catu_ग_लिखो_axictrl(drvdata, CATU_OS_AXICTRL);
		catu_ग_लिखो_sladdr(drvdata, catu_buf->sladdr);
		catu_ग_लिखो_inaddr(drvdata, CATU_DEFAULT_INADDR);
	पूर्ण अन्यथा अणु
		mode = CATU_MODE_PASS_THROUGH;
		catu_ग_लिखो_sladdr(drvdata, 0);
		catu_ग_लिखो_inaddr(drvdata, 0);
	पूर्ण

	catu_ग_लिखो_irqen(drvdata, 0);
	catu_ग_लिखो_mode(drvdata, mode);
	catu_ग_लिखो_control(drvdata, control);
	dev_dbg(dev, "Enabled in %s mode\n",
		(mode == CATU_MODE_PASS_THROUGH) ?
		"Pass through" :
		"Translate");
	वापस 0;
पूर्ण

अटल पूर्णांक catu_enable(काष्ठा coresight_device *csdev, व्योम *data)
अणु
	पूर्णांक rc;
	काष्ठा catu_drvdata *catu_drvdata = csdev_to_catu_drvdata(csdev);

	CS_UNLOCK(catu_drvdata->base);
	rc = catu_enable_hw(catu_drvdata, data);
	CS_LOCK(catu_drvdata->base);
	वापस rc;
पूर्ण

अटल पूर्णांक catu_disable_hw(काष्ठा catu_drvdata *drvdata)
अणु
	पूर्णांक rc = 0;
	काष्ठा device *dev = &drvdata->csdev->dev;
	काष्ठा coresight_device *csdev = drvdata->csdev;

	catu_ग_लिखो_control(drvdata, 0);
	coresight_disclaim_device_unlocked(csdev);
	अगर (catu_रुको_क्रम_पढ़ोy(drvdata)) अणु
		dev_info(dev, "Timeout while waiting for READY\n");
		rc = -EAGAIN;
	पूर्ण

	dev_dbg(dev, "Disabled\n");
	वापस rc;
पूर्ण

अटल पूर्णांक catu_disable(काष्ठा coresight_device *csdev, व्योम *__unused)
अणु
	पूर्णांक rc;
	काष्ठा catu_drvdata *catu_drvdata = csdev_to_catu_drvdata(csdev);

	CS_UNLOCK(catu_drvdata->base);
	rc = catu_disable_hw(catu_drvdata);
	CS_LOCK(catu_drvdata->base);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा coresight_ops_helper catu_helper_ops = अणु
	.enable = catu_enable,
	.disable = catu_disable,
पूर्ण;

अटल स्थिर काष्ठा coresight_ops catu_ops = अणु
	.helper_ops = &catu_helper_ops,
पूर्ण;

अटल पूर्णांक catu_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	पूर्णांक ret = 0;
	u32 dma_mask;
	काष्ठा catu_drvdata *drvdata;
	काष्ठा coresight_desc catu_desc;
	काष्ठा coresight_platक्रमm_data *pdata = शून्य;
	काष्ठा device *dev = &adev->dev;
	व्योम __iomem *base;

	catu_desc.name = coresight_alloc_device_name(&catu_devs, dev);
	अगर (!catu_desc.name)
		वापस -ENOMEM;

	drvdata = devm_kzalloc(dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	dev_set_drvdata(dev, drvdata);
	base = devm_ioremap_resource(dev, &adev->res);
	अगर (IS_ERR(base)) अणु
		ret = PTR_ERR(base);
		जाओ out;
	पूर्ण

	/* Setup dma mask क्रम the device */
	dma_mask = पढ़ोl_relaxed(base + CORESIGHT_DEVID) & 0x3f;
	चयन (dma_mask) अणु
	हाल 32:
	हाल 40:
	हाल 44:
	हाल 48:
	हाल 52:
	हाल 56:
	हाल 64:
		अवरोध;
	शेष:
		/* Default to the 40bits as supported by TMC-ETR */
		dma_mask = 40;
	पूर्ण
	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(dma_mask));
	अगर (ret)
		जाओ out;

	pdata = coresight_get_platक्रमm_data(dev);
	अगर (IS_ERR(pdata)) अणु
		ret = PTR_ERR(pdata);
		जाओ out;
	पूर्ण
	dev->platक्रमm_data = pdata;

	drvdata->base = base;
	catu_desc.access = CSDEV_ACCESS_IOMEM(base);
	catu_desc.pdata = pdata;
	catu_desc.dev = dev;
	catu_desc.groups = catu_groups;
	catu_desc.type = CORESIGHT_DEV_TYPE_HELPER;
	catu_desc.subtype.helper_subtype = CORESIGHT_DEV_SUBTYPE_HELPER_CATU;
	catu_desc.ops = &catu_ops;

	drvdata->csdev = coresight_रेजिस्टर(&catu_desc);
	अगर (IS_ERR(drvdata->csdev))
		ret = PTR_ERR(drvdata->csdev);
	अन्यथा
		pm_runसमय_put(&adev->dev);
out:
	वापस ret;
पूर्ण

अटल व्योम catu_हटाओ(काष्ठा amba_device *adev)
अणु
	काष्ठा catu_drvdata *drvdata = dev_get_drvdata(&adev->dev);

	coresight_unरेजिस्टर(drvdata->csdev);
पूर्ण

अटल काष्ठा amba_id catu_ids[] = अणु
	CS_AMBA_ID(0x000bb9ee),
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, catu_ids);

अटल काष्ठा amba_driver catu_driver = अणु
	.drv = अणु
		.name			= "coresight-catu",
		.owner			= THIS_MODULE,
		.suppress_bind_attrs	= true,
	पूर्ण,
	.probe				= catu_probe,
	.हटाओ				= catu_हटाओ,
	.id_table			= catu_ids,
पूर्ण;

अटल पूर्णांक __init catu_init(व्योम)
अणु
	पूर्णांक ret;

	ret = amba_driver_रेजिस्टर(&catu_driver);
	अगर (ret)
		pr_info("Error registering catu driver\n");
	पंचांगc_etr_set_catu_ops(&etr_catu_buf_ops);
	वापस ret;
पूर्ण

अटल व्योम __निकास catu_निकास(व्योम)
अणु
	पंचांगc_etr_हटाओ_catu_ops();
	amba_driver_unरेजिस्टर(&catu_driver);
पूर्ण

module_init(catu_init);
module_निकास(catu_निकास);

MODULE_AUTHOR("Suzuki K Poulose <suzuki.poulose@arm.com>");
MODULE_DESCRIPTION("Arm CoreSight Address Translation Unit (CATU) Driver");
MODULE_LICENSE("GPL v2");
