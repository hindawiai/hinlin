<शैली गुरु>
/*
 * Copyright (c) 2005, 2006, 2007, 2008 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2006, 2007 Cisco Systems, Inc.  All rights reserved.
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

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>

#समावेश <linux/mlx4/cmd.h>

#समावेश "mlx4.h"
#समावेश "icm.h"
#समावेश "fw.h"

/*
 * We allocate in as big chunks as we can, up to a maximum of 256 KB
 * per chunk. Note that the chunks are not necessarily in contiguous
 * physical memory.
 */
क्रमागत अणु
	MLX4_ICM_ALLOC_SIZE	= 1 << 18,
	MLX4_TABLE_CHUNK_SIZE	= 1 << 18,
पूर्ण;

अटल व्योम mlx4_मुक्त_icm_pages(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm_chunk *chunk)
अणु
	पूर्णांक i;

	अगर (chunk->nsg > 0)
		dma_unmap_sg(&dev->persist->pdev->dev, chunk->sg, chunk->npages,
			     DMA_BIसूचीECTIONAL);

	क्रम (i = 0; i < chunk->npages; ++i)
		__मुक्त_pages(sg_page(&chunk->sg[i]),
			     get_order(chunk->sg[i].length));
पूर्ण

अटल व्योम mlx4_मुक्त_icm_coherent(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm_chunk *chunk)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < chunk->npages; ++i)
		dma_मुक्त_coherent(&dev->persist->pdev->dev,
				  chunk->buf[i].size,
				  chunk->buf[i].addr,
				  chunk->buf[i].dma_addr);
पूर्ण

व्योम mlx4_मुक्त_icm(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm *icm, पूर्णांक coherent)
अणु
	काष्ठा mlx4_icm_chunk *chunk, *पंचांगp;

	अगर (!icm)
		वापस;

	list_क्रम_each_entry_safe(chunk, पंचांगp, &icm->chunk_list, list) अणु
		अगर (coherent)
			mlx4_मुक्त_icm_coherent(dev, chunk);
		अन्यथा
			mlx4_मुक्त_icm_pages(dev, chunk);

		kमुक्त(chunk);
	पूर्ण

	kमुक्त(icm);
पूर्ण

अटल पूर्णांक mlx4_alloc_icm_pages(काष्ठा scatterlist *mem, पूर्णांक order,
				gfp_t gfp_mask, पूर्णांक node)
अणु
	काष्ठा page *page;

	page = alloc_pages_node(node, gfp_mask, order);
	अगर (!page) अणु
		page = alloc_pages(gfp_mask, order);
		अगर (!page)
			वापस -ENOMEM;
	पूर्ण

	sg_set_page(mem, page, PAGE_SIZE << order, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_alloc_icm_coherent(काष्ठा device *dev, काष्ठा mlx4_icm_buf *buf,
				   पूर्णांक order, gfp_t gfp_mask)
अणु
	buf->addr = dma_alloc_coherent(dev, PAGE_SIZE << order,
				       &buf->dma_addr, gfp_mask);
	अगर (!buf->addr)
		वापस -ENOMEM;

	अगर (offset_in_page(buf->addr)) अणु
		dma_मुक्त_coherent(dev, PAGE_SIZE << order, buf->addr,
				  buf->dma_addr);
		वापस -ENOMEM;
	पूर्ण

	buf->size = PAGE_SIZE << order;
	वापस 0;
पूर्ण

काष्ठा mlx4_icm *mlx4_alloc_icm(काष्ठा mlx4_dev *dev, पूर्णांक npages,
				gfp_t gfp_mask, पूर्णांक coherent)
अणु
	काष्ठा mlx4_icm *icm;
	काष्ठा mlx4_icm_chunk *chunk = शून्य;
	पूर्णांक cur_order;
	gfp_t mask;
	पूर्णांक ret;

	/* We use sg_set_buf क्रम coherent allocs, which assumes low memory */
	BUG_ON(coherent && (gfp_mask & __GFP_HIGHMEM));

	icm = kदो_स्मृति_node(माप(*icm),
			   gfp_mask & ~(__GFP_HIGHMEM | __GFP_NOWARN),
			   dev->numa_node);
	अगर (!icm) अणु
		icm = kदो_स्मृति(माप(*icm),
			      gfp_mask & ~(__GFP_HIGHMEM | __GFP_NOWARN));
		अगर (!icm)
			वापस शून्य;
	पूर्ण

	icm->refcount = 0;
	INIT_LIST_HEAD(&icm->chunk_list);

	cur_order = get_order(MLX4_ICM_ALLOC_SIZE);

	जबतक (npages > 0) अणु
		अगर (!chunk) अणु
			chunk = kzalloc_node(माप(*chunk),
					     gfp_mask & ~(__GFP_HIGHMEM |
							  __GFP_NOWARN),
					     dev->numa_node);
			अगर (!chunk) अणु
				chunk = kzalloc(माप(*chunk),
						gfp_mask & ~(__GFP_HIGHMEM |
							     __GFP_NOWARN));
				अगर (!chunk)
					जाओ fail;
			पूर्ण
			chunk->coherent = coherent;

			अगर (!coherent)
				sg_init_table(chunk->sg, MLX4_ICM_CHUNK_LEN);
			list_add_tail(&chunk->list, &icm->chunk_list);
		पूर्ण

		जबतक (1 << cur_order > npages)
			--cur_order;

		mask = gfp_mask;
		अगर (cur_order)
			mask &= ~__GFP_सूचीECT_RECLAIM;

		अगर (coherent)
			ret = mlx4_alloc_icm_coherent(&dev->persist->pdev->dev,
						&chunk->buf[chunk->npages],
						cur_order, mask);
		अन्यथा
			ret = mlx4_alloc_icm_pages(&chunk->sg[chunk->npages],
						   cur_order, mask,
						   dev->numa_node);

		अगर (ret) अणु
			अगर (--cur_order < 0)
				जाओ fail;
			अन्यथा
				जारी;
		पूर्ण

		++chunk->npages;

		अगर (coherent)
			++chunk->nsg;
		अन्यथा अगर (chunk->npages == MLX4_ICM_CHUNK_LEN) अणु
			chunk->nsg = dma_map_sg(&dev->persist->pdev->dev,
						chunk->sg, chunk->npages,
						DMA_BIसूचीECTIONAL);

			अगर (chunk->nsg <= 0)
				जाओ fail;
		पूर्ण

		अगर (chunk->npages == MLX4_ICM_CHUNK_LEN)
			chunk = शून्य;

		npages -= 1 << cur_order;
	पूर्ण

	अगर (!coherent && chunk) अणु
		chunk->nsg = dma_map_sg(&dev->persist->pdev->dev, chunk->sg,
					chunk->npages, DMA_BIसूचीECTIONAL);

		अगर (chunk->nsg <= 0)
			जाओ fail;
	पूर्ण

	वापस icm;

fail:
	mlx4_मुक्त_icm(dev, icm, coherent);
	वापस शून्य;
पूर्ण

अटल पूर्णांक mlx4_MAP_ICM(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm *icm, u64 virt)
अणु
	वापस mlx4_map_cmd(dev, MLX4_CMD_MAP_ICM, icm, virt);
पूर्ण

अटल पूर्णांक mlx4_UNMAP_ICM(काष्ठा mlx4_dev *dev, u64 virt, u32 page_count)
अणु
	वापस mlx4_cmd(dev, virt, page_count, 0, MLX4_CMD_UNMAP_ICM,
			MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);
पूर्ण

पूर्णांक mlx4_MAP_ICM_AUX(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm *icm)
अणु
	वापस mlx4_map_cmd(dev, MLX4_CMD_MAP_ICM_AUX, icm, -1);
पूर्ण

पूर्णांक mlx4_UNMAP_ICM_AUX(काष्ठा mlx4_dev *dev)
अणु
	वापस mlx4_cmd(dev, 0, 0, 0, MLX4_CMD_UNMAP_ICM_AUX,
			MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);
पूर्ण

पूर्णांक mlx4_table_get(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm_table *table, u32 obj)
अणु
	u32 i = (obj & (table->num_obj - 1)) /
			(MLX4_TABLE_CHUNK_SIZE / table->obj_size);
	पूर्णांक ret = 0;

	mutex_lock(&table->mutex);

	अगर (table->icm[i]) अणु
		++table->icm[i]->refcount;
		जाओ out;
	पूर्ण

	table->icm[i] = mlx4_alloc_icm(dev, MLX4_TABLE_CHUNK_SIZE >> PAGE_SHIFT,
				       (table->lowmem ? GFP_KERNEL : GFP_HIGHUSER) |
				       __GFP_NOWARN, table->coherent);
	अगर (!table->icm[i]) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (mlx4_MAP_ICM(dev, table->icm[i], table->virt +
			 (u64) i * MLX4_TABLE_CHUNK_SIZE)) अणु
		mlx4_मुक्त_icm(dev, table->icm[i], table->coherent);
		table->icm[i] = शून्य;
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	++table->icm[i]->refcount;

out:
	mutex_unlock(&table->mutex);
	वापस ret;
पूर्ण

व्योम mlx4_table_put(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm_table *table, u32 obj)
अणु
	u32 i;
	u64 offset;

	i = (obj & (table->num_obj - 1)) / (MLX4_TABLE_CHUNK_SIZE / table->obj_size);

	mutex_lock(&table->mutex);

	अगर (--table->icm[i]->refcount == 0) अणु
		offset = (u64) i * MLX4_TABLE_CHUNK_SIZE;
		mlx4_UNMAP_ICM(dev, table->virt + offset,
			       MLX4_TABLE_CHUNK_SIZE / MLX4_ICM_PAGE_SIZE);
		mlx4_मुक्त_icm(dev, table->icm[i], table->coherent);
		table->icm[i] = शून्य;
	पूर्ण

	mutex_unlock(&table->mutex);
पूर्ण

व्योम *mlx4_table_find(काष्ठा mlx4_icm_table *table, u32 obj,
			dma_addr_t *dma_handle)
अणु
	पूर्णांक offset, dma_offset, i;
	u64 idx;
	काष्ठा mlx4_icm_chunk *chunk;
	काष्ठा mlx4_icm *icm;
	व्योम *addr = शून्य;

	अगर (!table->lowmem)
		वापस शून्य;

	mutex_lock(&table->mutex);

	idx = (u64) (obj & (table->num_obj - 1)) * table->obj_size;
	icm = table->icm[idx / MLX4_TABLE_CHUNK_SIZE];
	dma_offset = offset = idx % MLX4_TABLE_CHUNK_SIZE;

	अगर (!icm)
		जाओ out;

	list_क्रम_each_entry(chunk, &icm->chunk_list, list) अणु
		क्रम (i = 0; i < chunk->npages; ++i) अणु
			dma_addr_t dma_addr;
			माप_प्रकार len;

			अगर (table->coherent) अणु
				len = chunk->buf[i].size;
				dma_addr = chunk->buf[i].dma_addr;
				addr = chunk->buf[i].addr;
			पूर्ण अन्यथा अणु
				काष्ठा page *page;

				len = sg_dma_len(&chunk->sg[i]);
				dma_addr = sg_dma_address(&chunk->sg[i]);

				/* XXX: we should never करो this क्रम highmem
				 * allocation.  This function either needs
				 * to be split, or the kernel भव address
				 * वापस needs to be made optional.
				 */
				page = sg_page(&chunk->sg[i]);
				addr = lowmem_page_address(page);
			पूर्ण

			अगर (dma_handle && dma_offset >= 0) अणु
				अगर (len > dma_offset)
					*dma_handle = dma_addr + dma_offset;
				dma_offset -= len;
			पूर्ण

			/*
			 * DMA mapping can merge pages but not split them,
			 * so अगर we found the page, dma_handle has alपढ़ोy
			 * been asचिन्हित to.
			 */
			अगर (len > offset)
				जाओ out;
			offset -= len;
		पूर्ण
	पूर्ण

	addr = शून्य;
out:
	mutex_unlock(&table->mutex);
	वापस addr ? addr + offset : शून्य;
पूर्ण

पूर्णांक mlx4_table_get_range(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm_table *table,
			 u32 start, u32 end)
अणु
	पूर्णांक inc = MLX4_TABLE_CHUNK_SIZE / table->obj_size;
	पूर्णांक err;
	u32 i;

	क्रम (i = start; i <= end; i += inc) अणु
		err = mlx4_table_get(dev, table, i);
		अगर (err)
			जाओ fail;
	पूर्ण

	वापस 0;

fail:
	जबतक (i > start) अणु
		i -= inc;
		mlx4_table_put(dev, table, i);
	पूर्ण

	वापस err;
पूर्ण

व्योम mlx4_table_put_range(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm_table *table,
			  u32 start, u32 end)
अणु
	u32 i;

	क्रम (i = start; i <= end; i += MLX4_TABLE_CHUNK_SIZE / table->obj_size)
		mlx4_table_put(dev, table, i);
पूर्ण

पूर्णांक mlx4_init_icm_table(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm_table *table,
			u64 virt, पूर्णांक obj_size,	u32 nobj, पूर्णांक reserved,
			पूर्णांक use_lowmem, पूर्णांक use_coherent)
अणु
	पूर्णांक obj_per_chunk;
	पूर्णांक num_icm;
	अचिन्हित chunk_size;
	पूर्णांक i;
	u64 size;

	obj_per_chunk = MLX4_TABLE_CHUNK_SIZE / obj_size;
	अगर (WARN_ON(!obj_per_chunk))
		वापस -EINVAL;
	num_icm = DIV_ROUND_UP(nobj, obj_per_chunk);

	table->icm      = kvसुस्मृति(num_icm, माप(*table->icm), GFP_KERNEL);
	अगर (!table->icm)
		वापस -ENOMEM;
	table->virt     = virt;
	table->num_icm  = num_icm;
	table->num_obj  = nobj;
	table->obj_size = obj_size;
	table->lowmem   = use_lowmem;
	table->coherent = use_coherent;
	mutex_init(&table->mutex);

	size = (u64) nobj * obj_size;
	क्रम (i = 0; i * MLX4_TABLE_CHUNK_SIZE < reserved * obj_size; ++i) अणु
		chunk_size = MLX4_TABLE_CHUNK_SIZE;
		अगर ((i + 1) * MLX4_TABLE_CHUNK_SIZE > size)
			chunk_size = PAGE_ALIGN(size -
					i * MLX4_TABLE_CHUNK_SIZE);

		table->icm[i] = mlx4_alloc_icm(dev, chunk_size >> PAGE_SHIFT,
					       (use_lowmem ? GFP_KERNEL : GFP_HIGHUSER) |
					       __GFP_NOWARN, use_coherent);
		अगर (!table->icm[i])
			जाओ err;
		अगर (mlx4_MAP_ICM(dev, table->icm[i], virt + i * MLX4_TABLE_CHUNK_SIZE)) अणु
			mlx4_मुक्त_icm(dev, table->icm[i], use_coherent);
			table->icm[i] = शून्य;
			जाओ err;
		पूर्ण

		/*
		 * Add a reference to this ICM chunk so that it never
		 * माला_लो मुक्तd (since it contains reserved firmware objects).
		 */
		++table->icm[i]->refcount;
	पूर्ण

	वापस 0;

err:
	क्रम (i = 0; i < num_icm; ++i)
		अगर (table->icm[i]) अणु
			mlx4_UNMAP_ICM(dev, virt + i * MLX4_TABLE_CHUNK_SIZE,
				       MLX4_TABLE_CHUNK_SIZE / MLX4_ICM_PAGE_SIZE);
			mlx4_मुक्त_icm(dev, table->icm[i], use_coherent);
		पूर्ण

	kvमुक्त(table->icm);

	वापस -ENOMEM;
पूर्ण

व्योम mlx4_cleanup_icm_table(काष्ठा mlx4_dev *dev, काष्ठा mlx4_icm_table *table)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < table->num_icm; ++i)
		अगर (table->icm[i]) अणु
			mlx4_UNMAP_ICM(dev, table->virt + i * MLX4_TABLE_CHUNK_SIZE,
				       MLX4_TABLE_CHUNK_SIZE / MLX4_ICM_PAGE_SIZE);
			mlx4_मुक्त_icm(dev, table->icm[i], table->coherent);
		पूर्ण

	kvमुक्त(table->icm);
पूर्ण
