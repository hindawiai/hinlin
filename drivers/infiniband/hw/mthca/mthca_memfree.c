<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Cisco Systems.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/mm.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/page.h>

#समावेश "mthca_memfree.h"
#समावेश "mthca_dev.h"
#समावेश "mthca_cmd.h"

/*
 * We allocate in as big chunks as we can, up to a maximum of 256 KB
 * per chunk.
 */
क्रमागत अणु
	MTHCA_ICM_ALLOC_SIZE   = 1 << 18,
	MTHCA_TABLE_CHUNK_SIZE = 1 << 18
पूर्ण;

काष्ठा mthca_user_db_table अणु
	काष्ठा mutex mutex;
	काष्ठा अणु
		u64                uvirt;
		काष्ठा scatterlist mem;
		पूर्णांक                refcount;
	पूर्ण page[];
पूर्ण;

अटल व्योम mthca_मुक्त_icm_pages(काष्ठा mthca_dev *dev, काष्ठा mthca_icm_chunk *chunk)
अणु
	पूर्णांक i;

	अगर (chunk->nsg > 0)
		pci_unmap_sg(dev->pdev, chunk->mem, chunk->npages,
			     PCI_DMA_BIसूचीECTIONAL);

	क्रम (i = 0; i < chunk->npages; ++i)
		__मुक्त_pages(sg_page(&chunk->mem[i]),
			     get_order(chunk->mem[i].length));
पूर्ण

अटल व्योम mthca_मुक्त_icm_coherent(काष्ठा mthca_dev *dev, काष्ठा mthca_icm_chunk *chunk)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < chunk->npages; ++i) अणु
		dma_मुक्त_coherent(&dev->pdev->dev, chunk->mem[i].length,
				  lowmem_page_address(sg_page(&chunk->mem[i])),
				  sg_dma_address(&chunk->mem[i]));
	पूर्ण
पूर्ण

व्योम mthca_मुक्त_icm(काष्ठा mthca_dev *dev, काष्ठा mthca_icm *icm, पूर्णांक coherent)
अणु
	काष्ठा mthca_icm_chunk *chunk, *पंचांगp;

	अगर (!icm)
		वापस;

	list_क्रम_each_entry_safe(chunk, पंचांगp, &icm->chunk_list, list) अणु
		अगर (coherent)
			mthca_मुक्त_icm_coherent(dev, chunk);
		अन्यथा
			mthca_मुक्त_icm_pages(dev, chunk);

		kमुक्त(chunk);
	पूर्ण

	kमुक्त(icm);
पूर्ण

अटल पूर्णांक mthca_alloc_icm_pages(काष्ठा scatterlist *mem, पूर्णांक order, gfp_t gfp_mask)
अणु
	काष्ठा page *page;

	/*
	 * Use __GFP_ZERO because buggy firmware assumes ICM pages are
	 * cleared, and subtle failures are seen अगर they aren't.
	 */
	page = alloc_pages(gfp_mask | __GFP_ZERO, order);
	अगर (!page)
		वापस -ENOMEM;

	sg_set_page(mem, page, PAGE_SIZE << order, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक mthca_alloc_icm_coherent(काष्ठा device *dev, काष्ठा scatterlist *mem,
				    पूर्णांक order, gfp_t gfp_mask)
अणु
	व्योम *buf = dma_alloc_coherent(dev, PAGE_SIZE << order, &sg_dma_address(mem),
				       gfp_mask);
	अगर (!buf)
		वापस -ENOMEM;

	sg_set_buf(mem, buf, PAGE_SIZE << order);
	BUG_ON(mem->offset);
	sg_dma_len(mem) = PAGE_SIZE << order;
	वापस 0;
पूर्ण

काष्ठा mthca_icm *mthca_alloc_icm(काष्ठा mthca_dev *dev, पूर्णांक npages,
				  gfp_t gfp_mask, पूर्णांक coherent)
अणु
	काष्ठा mthca_icm *icm;
	काष्ठा mthca_icm_chunk *chunk = शून्य;
	पूर्णांक cur_order;
	पूर्णांक ret;

	/* We use sg_set_buf क्रम coherent allocs, which assumes low memory */
	BUG_ON(coherent && (gfp_mask & __GFP_HIGHMEM));

	icm = kदो_स्मृति(माप *icm, gfp_mask & ~(__GFP_HIGHMEM | __GFP_NOWARN));
	अगर (!icm)
		वापस icm;

	icm->refcount = 0;
	INIT_LIST_HEAD(&icm->chunk_list);

	cur_order = get_order(MTHCA_ICM_ALLOC_SIZE);

	जबतक (npages > 0) अणु
		अगर (!chunk) अणु
			chunk = kदो_स्मृति(माप *chunk,
					gfp_mask & ~(__GFP_HIGHMEM | __GFP_NOWARN));
			अगर (!chunk)
				जाओ fail;

			sg_init_table(chunk->mem, MTHCA_ICM_CHUNK_LEN);
			chunk->npages = 0;
			chunk->nsg    = 0;
			list_add_tail(&chunk->list, &icm->chunk_list);
		पूर्ण

		जबतक (1 << cur_order > npages)
			--cur_order;

		अगर (coherent)
			ret = mthca_alloc_icm_coherent(&dev->pdev->dev,
						       &chunk->mem[chunk->npages],
						       cur_order, gfp_mask);
		अन्यथा
			ret = mthca_alloc_icm_pages(&chunk->mem[chunk->npages],
						    cur_order, gfp_mask);

		अगर (!ret) अणु
			++chunk->npages;

			अगर (coherent)
				++chunk->nsg;
			अन्यथा अगर (chunk->npages == MTHCA_ICM_CHUNK_LEN) अणु
				chunk->nsg = pci_map_sg(dev->pdev, chunk->mem,
							chunk->npages,
							PCI_DMA_BIसूचीECTIONAL);

				अगर (chunk->nsg <= 0)
					जाओ fail;
			पूर्ण

			अगर (chunk->npages == MTHCA_ICM_CHUNK_LEN)
				chunk = शून्य;

			npages -= 1 << cur_order;
		पूर्ण अन्यथा अणु
			--cur_order;
			अगर (cur_order < 0)
				जाओ fail;
		पूर्ण
	पूर्ण

	अगर (!coherent && chunk) अणु
		chunk->nsg = pci_map_sg(dev->pdev, chunk->mem,
					chunk->npages,
					PCI_DMA_BIसूचीECTIONAL);

		अगर (chunk->nsg <= 0)
			जाओ fail;
	पूर्ण

	वापस icm;

fail:
	mthca_मुक्त_icm(dev, icm, coherent);
	वापस शून्य;
पूर्ण

पूर्णांक mthca_table_get(काष्ठा mthca_dev *dev, काष्ठा mthca_icm_table *table, पूर्णांक obj)
अणु
	पूर्णांक i = (obj & (table->num_obj - 1)) * table->obj_size / MTHCA_TABLE_CHUNK_SIZE;
	पूर्णांक ret = 0;

	mutex_lock(&table->mutex);

	अगर (table->icm[i]) अणु
		++table->icm[i]->refcount;
		जाओ out;
	पूर्ण

	table->icm[i] = mthca_alloc_icm(dev, MTHCA_TABLE_CHUNK_SIZE >> PAGE_SHIFT,
					(table->lowmem ? GFP_KERNEL : GFP_HIGHUSER) |
					__GFP_NOWARN, table->coherent);
	अगर (!table->icm[i]) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (mthca_MAP_ICM(dev, table->icm[i],
			  table->virt + i * MTHCA_TABLE_CHUNK_SIZE)) अणु
		mthca_मुक्त_icm(dev, table->icm[i], table->coherent);
		table->icm[i] = शून्य;
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	++table->icm[i]->refcount;

out:
	mutex_unlock(&table->mutex);
	वापस ret;
पूर्ण

व्योम mthca_table_put(काष्ठा mthca_dev *dev, काष्ठा mthca_icm_table *table, पूर्णांक obj)
अणु
	पूर्णांक i;

	अगर (!mthca_is_memमुक्त(dev))
		वापस;

	i = (obj & (table->num_obj - 1)) * table->obj_size / MTHCA_TABLE_CHUNK_SIZE;

	mutex_lock(&table->mutex);

	अगर (--table->icm[i]->refcount == 0) अणु
		mthca_UNMAP_ICM(dev, table->virt + i * MTHCA_TABLE_CHUNK_SIZE,
				MTHCA_TABLE_CHUNK_SIZE / MTHCA_ICM_PAGE_SIZE);
		mthca_मुक्त_icm(dev, table->icm[i], table->coherent);
		table->icm[i] = शून्य;
	पूर्ण

	mutex_unlock(&table->mutex);
पूर्ण

व्योम *mthca_table_find(काष्ठा mthca_icm_table *table, पूर्णांक obj, dma_addr_t *dma_handle)
अणु
	पूर्णांक idx, offset, dma_offset, i;
	काष्ठा mthca_icm_chunk *chunk;
	काष्ठा mthca_icm *icm;
	काष्ठा page *page = शून्य;

	अगर (!table->lowmem)
		वापस शून्य;

	mutex_lock(&table->mutex);

	idx = (obj & (table->num_obj - 1)) * table->obj_size;
	icm = table->icm[idx / MTHCA_TABLE_CHUNK_SIZE];
	dma_offset = offset = idx % MTHCA_TABLE_CHUNK_SIZE;

	अगर (!icm)
		जाओ out;

	list_क्रम_each_entry(chunk, &icm->chunk_list, list) अणु
		क्रम (i = 0; i < chunk->npages; ++i) अणु
			अगर (dma_handle && dma_offset >= 0) अणु
				अगर (sg_dma_len(&chunk->mem[i]) > dma_offset)
					*dma_handle = sg_dma_address(&chunk->mem[i]) +
						dma_offset;
				dma_offset -= sg_dma_len(&chunk->mem[i]);
			पूर्ण
			/* DMA mapping can merge pages but not split them,
			 * so अगर we found the page, dma_handle has alपढ़ोy
			 * been asचिन्हित to. */
			अगर (chunk->mem[i].length > offset) अणु
				page = sg_page(&chunk->mem[i]);
				जाओ out;
			पूर्ण
			offset -= chunk->mem[i].length;
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&table->mutex);
	वापस page ? lowmem_page_address(page) + offset : शून्य;
पूर्ण

पूर्णांक mthca_table_get_range(काष्ठा mthca_dev *dev, काष्ठा mthca_icm_table *table,
			  पूर्णांक start, पूर्णांक end)
अणु
	पूर्णांक inc = MTHCA_TABLE_CHUNK_SIZE / table->obj_size;
	पूर्णांक i, err;

	क्रम (i = start; i <= end; i += inc) अणु
		err = mthca_table_get(dev, table, i);
		अगर (err)
			जाओ fail;
	पूर्ण

	वापस 0;

fail:
	जबतक (i > start) अणु
		i -= inc;
		mthca_table_put(dev, table, i);
	पूर्ण

	वापस err;
पूर्ण

व्योम mthca_table_put_range(काष्ठा mthca_dev *dev, काष्ठा mthca_icm_table *table,
			   पूर्णांक start, पूर्णांक end)
अणु
	पूर्णांक i;

	अगर (!mthca_is_memमुक्त(dev))
		वापस;

	क्रम (i = start; i <= end; i += MTHCA_TABLE_CHUNK_SIZE / table->obj_size)
		mthca_table_put(dev, table, i);
पूर्ण

काष्ठा mthca_icm_table *mthca_alloc_icm_table(काष्ठा mthca_dev *dev,
					      u64 virt, पूर्णांक obj_size,
					      पूर्णांक nobj, पूर्णांक reserved,
					      पूर्णांक use_lowmem, पूर्णांक use_coherent)
अणु
	काष्ठा mthca_icm_table *table;
	पूर्णांक obj_per_chunk;
	पूर्णांक num_icm;
	अचिन्हित chunk_size;
	पूर्णांक i;

	obj_per_chunk = MTHCA_TABLE_CHUNK_SIZE / obj_size;
	num_icm = DIV_ROUND_UP(nobj, obj_per_chunk);

	table = kदो_स्मृति(काष्ठा_size(table, icm, num_icm), GFP_KERNEL);
	अगर (!table)
		वापस शून्य;

	table->virt     = virt;
	table->num_icm  = num_icm;
	table->num_obj  = nobj;
	table->obj_size = obj_size;
	table->lowmem   = use_lowmem;
	table->coherent = use_coherent;
	mutex_init(&table->mutex);

	क्रम (i = 0; i < num_icm; ++i)
		table->icm[i] = शून्य;

	क्रम (i = 0; i * MTHCA_TABLE_CHUNK_SIZE < reserved * obj_size; ++i) अणु
		chunk_size = MTHCA_TABLE_CHUNK_SIZE;
		अगर ((i + 1) * MTHCA_TABLE_CHUNK_SIZE > nobj * obj_size)
			chunk_size = nobj * obj_size - i * MTHCA_TABLE_CHUNK_SIZE;

		table->icm[i] = mthca_alloc_icm(dev, chunk_size >> PAGE_SHIFT,
						(use_lowmem ? GFP_KERNEL : GFP_HIGHUSER) |
						__GFP_NOWARN, use_coherent);
		अगर (!table->icm[i])
			जाओ err;
		अगर (mthca_MAP_ICM(dev, table->icm[i],
				  virt + i * MTHCA_TABLE_CHUNK_SIZE)) अणु
			mthca_मुक्त_icm(dev, table->icm[i], table->coherent);
			table->icm[i] = शून्य;
			जाओ err;
		पूर्ण

		/*
		 * Add a reference to this ICM chunk so that it never
		 * माला_लो मुक्तd (since it contains reserved firmware objects).
		 */
		++table->icm[i]->refcount;
	पूर्ण

	वापस table;

err:
	क्रम (i = 0; i < num_icm; ++i)
		अगर (table->icm[i]) अणु
			mthca_UNMAP_ICM(dev, virt + i * MTHCA_TABLE_CHUNK_SIZE,
					MTHCA_TABLE_CHUNK_SIZE / MTHCA_ICM_PAGE_SIZE);
			mthca_मुक्त_icm(dev, table->icm[i], table->coherent);
		पूर्ण

	kमुक्त(table);

	वापस शून्य;
पूर्ण

व्योम mthca_मुक्त_icm_table(काष्ठा mthca_dev *dev, काष्ठा mthca_icm_table *table)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < table->num_icm; ++i)
		अगर (table->icm[i]) अणु
			mthca_UNMAP_ICM(dev,
					table->virt + i * MTHCA_TABLE_CHUNK_SIZE,
					MTHCA_TABLE_CHUNK_SIZE / MTHCA_ICM_PAGE_SIZE);
			mthca_मुक्त_icm(dev, table->icm[i], table->coherent);
		पूर्ण

	kमुक्त(table);
पूर्ण

अटल u64 mthca_uarc_virt(काष्ठा mthca_dev *dev, काष्ठा mthca_uar *uar, पूर्णांक page)
अणु
	वापस dev->uar_table.uarc_base +
		uar->index * dev->uar_table.uarc_size +
		page * MTHCA_ICM_PAGE_SIZE;
पूर्ण

पूर्णांक mthca_map_user_db(काष्ठा mthca_dev *dev, काष्ठा mthca_uar *uar,
		      काष्ठा mthca_user_db_table *db_tab, पूर्णांक index, u64 uaddr)
अणु
	काष्ठा page *pages[1];
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (!mthca_is_memमुक्त(dev))
		वापस 0;

	अगर (index < 0 || index > dev->uar_table.uarc_size / 8)
		वापस -EINVAL;

	mutex_lock(&db_tab->mutex);

	i = index / MTHCA_DB_REC_PER_PAGE;

	अगर ((db_tab->page[i].refcount >= MTHCA_DB_REC_PER_PAGE)       ||
	    (db_tab->page[i].uvirt && db_tab->page[i].uvirt != uaddr) ||
	    (uaddr & 4095)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (db_tab->page[i].refcount) अणु
		++db_tab->page[i].refcount;
		जाओ out;
	पूर्ण

	ret = pin_user_pages_fast(uaddr & PAGE_MASK, 1,
				  FOLL_WRITE | FOLL_LONGTERM, pages);
	अगर (ret < 0)
		जाओ out;

	sg_set_page(&db_tab->page[i].mem, pages[0], MTHCA_ICM_PAGE_SIZE,
			uaddr & ~PAGE_MASK);

	ret = pci_map_sg(dev->pdev, &db_tab->page[i].mem, 1, PCI_DMA_TODEVICE);
	अगर (ret < 0) अणु
		unpin_user_page(pages[0]);
		जाओ out;
	पूर्ण

	ret = mthca_MAP_ICM_page(dev, sg_dma_address(&db_tab->page[i].mem),
				 mthca_uarc_virt(dev, uar, i));
	अगर (ret) अणु
		pci_unmap_sg(dev->pdev, &db_tab->page[i].mem, 1, PCI_DMA_TODEVICE);
		unpin_user_page(sg_page(&db_tab->page[i].mem));
		जाओ out;
	पूर्ण

	db_tab->page[i].uvirt    = uaddr;
	db_tab->page[i].refcount = 1;

out:
	mutex_unlock(&db_tab->mutex);
	वापस ret;
पूर्ण

व्योम mthca_unmap_user_db(काष्ठा mthca_dev *dev, काष्ठा mthca_uar *uar,
			 काष्ठा mthca_user_db_table *db_tab, पूर्णांक index)
अणु
	अगर (!mthca_is_memमुक्त(dev))
		वापस;

	/*
	 * To make our bookkeeping simpler, we करोn't unmap DB
	 * pages until we clean up the whole db table.
	 */

	mutex_lock(&db_tab->mutex);

	--db_tab->page[index / MTHCA_DB_REC_PER_PAGE].refcount;

	mutex_unlock(&db_tab->mutex);
पूर्ण

काष्ठा mthca_user_db_table *mthca_init_user_db_tab(काष्ठा mthca_dev *dev)
अणु
	काष्ठा mthca_user_db_table *db_tab;
	पूर्णांक npages;
	पूर्णांक i;

	अगर (!mthca_is_memमुक्त(dev))
		वापस शून्य;

	npages = dev->uar_table.uarc_size / MTHCA_ICM_PAGE_SIZE;
	db_tab = kदो_स्मृति(काष्ठा_size(db_tab, page, npages), GFP_KERNEL);
	अगर (!db_tab)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&db_tab->mutex);
	क्रम (i = 0; i < npages; ++i) अणु
		db_tab->page[i].refcount = 0;
		db_tab->page[i].uvirt    = 0;
		sg_init_table(&db_tab->page[i].mem, 1);
	पूर्ण

	वापस db_tab;
पूर्ण

व्योम mthca_cleanup_user_db_tab(काष्ठा mthca_dev *dev, काष्ठा mthca_uar *uar,
			       काष्ठा mthca_user_db_table *db_tab)
अणु
	पूर्णांक i;

	अगर (!mthca_is_memमुक्त(dev))
		वापस;

	क्रम (i = 0; i < dev->uar_table.uarc_size / MTHCA_ICM_PAGE_SIZE; ++i) अणु
		अगर (db_tab->page[i].uvirt) अणु
			mthca_UNMAP_ICM(dev, mthca_uarc_virt(dev, uar, i), 1);
			pci_unmap_sg(dev->pdev, &db_tab->page[i].mem, 1, PCI_DMA_TODEVICE);
			unpin_user_page(sg_page(&db_tab->page[i].mem));
		पूर्ण
	पूर्ण

	kमुक्त(db_tab);
पूर्ण

पूर्णांक mthca_alloc_db(काष्ठा mthca_dev *dev, क्रमागत mthca_db_type type,
		   u32 qn, __be32 **db)
अणु
	पूर्णांक group;
	पूर्णांक start, end, dir;
	पूर्णांक i, j;
	काष्ठा mthca_db_page *page;
	पूर्णांक ret = 0;

	mutex_lock(&dev->db_tab->mutex);

	चयन (type) अणु
	हाल MTHCA_DB_TYPE_CQ_ARM:
	हाल MTHCA_DB_TYPE_SQ:
		group = 0;
		start = 0;
		end   = dev->db_tab->max_group1;
		dir   = 1;
		अवरोध;

	हाल MTHCA_DB_TYPE_CQ_SET_CI:
	हाल MTHCA_DB_TYPE_RQ:
	हाल MTHCA_DB_TYPE_SRQ:
		group = 1;
		start = dev->db_tab->npages - 1;
		end   = dev->db_tab->min_group2;
		dir   = -1;
		अवरोध;

	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम (i = start; i != end; i += dir)
		अगर (dev->db_tab->page[i].db_rec &&
		    !biपंचांगap_full(dev->db_tab->page[i].used,
				 MTHCA_DB_REC_PER_PAGE)) अणु
			page = dev->db_tab->page + i;
			जाओ found;
		पूर्ण

	क्रम (i = start; i != end; i += dir)
		अगर (!dev->db_tab->page[i].db_rec) अणु
			page = dev->db_tab->page + i;
			जाओ alloc;
		पूर्ण

	अगर (dev->db_tab->max_group1 >= dev->db_tab->min_group2 - 1) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (group == 0)
		++dev->db_tab->max_group1;
	अन्यथा
		--dev->db_tab->min_group2;

	page = dev->db_tab->page + end;

alloc:
	page->db_rec = dma_alloc_coherent(&dev->pdev->dev,
					  MTHCA_ICM_PAGE_SIZE, &page->mapping,
					  GFP_KERNEL);
	अगर (!page->db_rec) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = mthca_MAP_ICM_page(dev, page->mapping,
				 mthca_uarc_virt(dev, &dev->driver_uar, i));
	अगर (ret) अणु
		dma_मुक्त_coherent(&dev->pdev->dev, MTHCA_ICM_PAGE_SIZE,
				  page->db_rec, page->mapping);
		जाओ out;
	पूर्ण

	biपंचांगap_zero(page->used, MTHCA_DB_REC_PER_PAGE);

found:
	j = find_first_zero_bit(page->used, MTHCA_DB_REC_PER_PAGE);
	set_bit(j, page->used);

	अगर (group == 1)
		j = MTHCA_DB_REC_PER_PAGE - 1 - j;

	ret = i * MTHCA_DB_REC_PER_PAGE + j;

	page->db_rec[j] = cpu_to_be64((qn << 8) | (type << 5));

	*db = (__be32 *) &page->db_rec[j];

out:
	mutex_unlock(&dev->db_tab->mutex);

	वापस ret;
पूर्ण

व्योम mthca_मुक्त_db(काष्ठा mthca_dev *dev, पूर्णांक type, पूर्णांक db_index)
अणु
	पूर्णांक i, j;
	काष्ठा mthca_db_page *page;

	i = db_index / MTHCA_DB_REC_PER_PAGE;
	j = db_index % MTHCA_DB_REC_PER_PAGE;

	page = dev->db_tab->page + i;

	mutex_lock(&dev->db_tab->mutex);

	page->db_rec[j] = 0;
	अगर (i >= dev->db_tab->min_group2)
		j = MTHCA_DB_REC_PER_PAGE - 1 - j;
	clear_bit(j, page->used);

	अगर (biपंचांगap_empty(page->used, MTHCA_DB_REC_PER_PAGE) &&
	    i >= dev->db_tab->max_group1 - 1) अणु
		mthca_UNMAP_ICM(dev, mthca_uarc_virt(dev, &dev->driver_uar, i), 1);

		dma_मुक्त_coherent(&dev->pdev->dev, MTHCA_ICM_PAGE_SIZE,
				  page->db_rec, page->mapping);
		page->db_rec = शून्य;

		अगर (i == dev->db_tab->max_group1) अणु
			--dev->db_tab->max_group1;
			/* XXX may be able to unmap more pages now */
		पूर्ण
		अगर (i == dev->db_tab->min_group2)
			++dev->db_tab->min_group2;
	पूर्ण

	mutex_unlock(&dev->db_tab->mutex);
पूर्ण

पूर्णांक mthca_init_db_tab(काष्ठा mthca_dev *dev)
अणु
	पूर्णांक i;

	अगर (!mthca_is_memमुक्त(dev))
		वापस 0;

	dev->db_tab = kदो_स्मृति(माप *dev->db_tab, GFP_KERNEL);
	अगर (!dev->db_tab)
		वापस -ENOMEM;

	mutex_init(&dev->db_tab->mutex);

	dev->db_tab->npages     = dev->uar_table.uarc_size / MTHCA_ICM_PAGE_SIZE;
	dev->db_tab->max_group1 = 0;
	dev->db_tab->min_group2 = dev->db_tab->npages - 1;

	dev->db_tab->page = kदो_स्मृति_array(dev->db_tab->npages,
					  माप(*dev->db_tab->page),
					  GFP_KERNEL);
	अगर (!dev->db_tab->page) अणु
		kमुक्त(dev->db_tab);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < dev->db_tab->npages; ++i)
		dev->db_tab->page[i].db_rec = शून्य;

	वापस 0;
पूर्ण

व्योम mthca_cleanup_db_tab(काष्ठा mthca_dev *dev)
अणु
	पूर्णांक i;

	अगर (!mthca_is_memमुक्त(dev))
		वापस;

	/*
	 * Because we करोn't always मुक्त our UARC pages when they
	 * become empty to make mthca_मुक्त_db() simpler we need to
	 * make a sweep through the करोorbell pages and मुक्त any
	 * leftover pages now.
	 */
	क्रम (i = 0; i < dev->db_tab->npages; ++i) अणु
		अगर (!dev->db_tab->page[i].db_rec)
			जारी;

		अगर (!biपंचांगap_empty(dev->db_tab->page[i].used, MTHCA_DB_REC_PER_PAGE))
			mthca_warn(dev, "Kernel UARC page %d not empty\n", i);

		mthca_UNMAP_ICM(dev, mthca_uarc_virt(dev, &dev->driver_uar, i), 1);

		dma_मुक्त_coherent(&dev->pdev->dev, MTHCA_ICM_PAGE_SIZE,
				  dev->db_tab->page[i].db_rec,
				  dev->db_tab->page[i].mapping);
	पूर्ण

	kमुक्त(dev->db_tab->page);
	kमुक्त(dev->db_tab);
पूर्ण
