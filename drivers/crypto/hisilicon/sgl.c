<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 HiSilicon Limited. */
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश "qm.h"

#घोषणा HISI_ACC_SGL_SGE_NR_MIN		1
#घोषणा HISI_ACC_SGL_NR_MAX		256
#घोषणा HISI_ACC_SGL_ALIGN_SIZE		64
#घोषणा HISI_ACC_MEM_BLOCK_NR		5

काष्ठा acc_hw_sge अणु
	dma_addr_t buf;
	व्योम *page_ctrl;
	__le32 len;
	__le32 pad;
	__le32 pad0;
	__le32 pad1;
पूर्ण;

/* use शेष sgl head size 64B */
काष्ठा hisi_acc_hw_sgl अणु
	dma_addr_t next_dma;
	__le16 entry_sum_in_chain;
	__le16 entry_sum_in_sgl;
	__le16 entry_length_in_sgl;
	__le16 pad0;
	__le64 pad1[5];
	काष्ठा hisi_acc_hw_sgl *next;
	काष्ठा acc_hw_sge sge_entries[];
पूर्ण __aligned(1);

काष्ठा hisi_acc_sgl_pool अणु
	काष्ठा mem_block अणु
		काष्ठा hisi_acc_hw_sgl *sgl;
		dma_addr_t sgl_dma;
		माप_प्रकार size;
	पूर्ण mem_block[HISI_ACC_MEM_BLOCK_NR];
	u32 sgl_num_per_block;
	u32 block_num;
	u32 count;
	u32 sge_nr;
	माप_प्रकार sgl_size;
पूर्ण;

/**
 * hisi_acc_create_sgl_pool() - Create a hw sgl pool.
 * @dev: The device which hw sgl pool beदीर्घs to.
 * @count: Count of hisi_acc_hw_sgl in pool.
 * @sge_nr: The count of sge in hw_sgl
 *
 * This function creates a hw sgl pool, after this user can get hw sgl memory
 * from it.
 */
काष्ठा hisi_acc_sgl_pool *hisi_acc_create_sgl_pool(काष्ठा device *dev,
						   u32 count, u32 sge_nr)
अणु
	u32 sgl_size, block_size, sgl_num_per_block, block_num, reमुख्य_sgl;
	काष्ठा hisi_acc_sgl_pool *pool;
	काष्ठा mem_block *block;
	u32 i, j;

	अगर (!dev || !count || !sge_nr || sge_nr > HISI_ACC_SGL_SGE_NR_MAX)
		वापस ERR_PTR(-EINVAL);

	sgl_size = माप(काष्ठा acc_hw_sge) * sge_nr +
		   माप(काष्ठा hisi_acc_hw_sgl);

	/*
	 * the pool may allocate a block of memory of size PAGE_SIZE * 2^(MAX_ORDER - 1),
	 * block size may exceed 2^31 on ia64, so the max of block size is 2^31
	 */
	block_size = 1 << (PAGE_SHIFT + MAX_ORDER <= 32 ?
			   PAGE_SHIFT + MAX_ORDER - 1 : 31);
	sgl_num_per_block = block_size / sgl_size;
	block_num = count / sgl_num_per_block;
	reमुख्य_sgl = count % sgl_num_per_block;

	अगर ((!reमुख्य_sgl && block_num > HISI_ACC_MEM_BLOCK_NR) ||
	    (reमुख्य_sgl > 0 && block_num > HISI_ACC_MEM_BLOCK_NR - 1))
		वापस ERR_PTR(-EINVAL);

	pool = kzalloc(माप(*pool), GFP_KERNEL);
	अगर (!pool)
		वापस ERR_PTR(-ENOMEM);
	block = pool->mem_block;

	क्रम (i = 0; i < block_num; i++) अणु
		block[i].sgl = dma_alloc_coherent(dev, block_size,
						  &block[i].sgl_dma,
						  GFP_KERNEL);
		अगर (!block[i].sgl) अणु
			dev_err(dev, "Fail to allocate hw SG buffer!\n");
			जाओ err_मुक्त_mem;
		पूर्ण

		block[i].size = block_size;
	पूर्ण

	अगर (reमुख्य_sgl > 0) अणु
		block[i].sgl = dma_alloc_coherent(dev, reमुख्य_sgl * sgl_size,
						  &block[i].sgl_dma,
						  GFP_KERNEL);
		अगर (!block[i].sgl) अणु
			dev_err(dev, "Fail to allocate remained hw SG buffer!\n");
			जाओ err_मुक्त_mem;
		पूर्ण

		block[i].size = reमुख्य_sgl * sgl_size;
	पूर्ण

	pool->sgl_num_per_block = sgl_num_per_block;
	pool->block_num = reमुख्य_sgl ? block_num + 1 : block_num;
	pool->count = count;
	pool->sgl_size = sgl_size;
	pool->sge_nr = sge_nr;

	वापस pool;

err_मुक्त_mem:
	क्रम (j = 0; j < i; j++) अणु
		dma_मुक्त_coherent(dev, block_size, block[j].sgl,
				  block[j].sgl_dma);
		स_रखो(block + j, 0, माप(*block));
	पूर्ण
	kमुक्त(pool);
	वापस ERR_PTR(-ENOMEM);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_acc_create_sgl_pool);

/**
 * hisi_acc_मुक्त_sgl_pool() - Free a hw sgl pool.
 * @dev: The device which hw sgl pool beदीर्घs to.
 * @pool: Poपूर्णांकer of pool.
 *
 * This function मुक्तs memory of a hw sgl pool.
 */
व्योम hisi_acc_मुक्त_sgl_pool(काष्ठा device *dev, काष्ठा hisi_acc_sgl_pool *pool)
अणु
	काष्ठा mem_block *block;
	पूर्णांक i;

	अगर (!dev || !pool)
		वापस;

	block = pool->mem_block;

	क्रम (i = 0; i < pool->block_num; i++)
		dma_मुक्त_coherent(dev, block[i].size, block[i].sgl,
				  block[i].sgl_dma);

	kमुक्त(pool);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_acc_मुक्त_sgl_pool);

अटल काष्ठा hisi_acc_hw_sgl *acc_get_sgl(काष्ठा hisi_acc_sgl_pool *pool,
					   u32 index, dma_addr_t *hw_sgl_dma)
अणु
	काष्ठा mem_block *block;
	u32 block_index, offset;

	अगर (!pool || !hw_sgl_dma || index >= pool->count)
		वापस ERR_PTR(-EINVAL);

	block = pool->mem_block;
	block_index = index / pool->sgl_num_per_block;
	offset = index % pool->sgl_num_per_block;

	*hw_sgl_dma = block[block_index].sgl_dma + pool->sgl_size * offset;
	वापस (व्योम *)block[block_index].sgl + pool->sgl_size * offset;
पूर्ण

अटल व्योम sg_map_to_hw_sg(काष्ठा scatterlist *sgl,
			    काष्ठा acc_hw_sge *hw_sge)
अणु
	hw_sge->buf = sg_dma_address(sgl);
	hw_sge->len = cpu_to_le32(sg_dma_len(sgl));
	hw_sge->page_ctrl = sg_virt(sgl);
पूर्ण

अटल व्योम inc_hw_sgl_sge(काष्ठा hisi_acc_hw_sgl *hw_sgl)
अणु
	u16 var = le16_to_cpu(hw_sgl->entry_sum_in_sgl);

	var++;
	hw_sgl->entry_sum_in_sgl = cpu_to_le16(var);
पूर्ण

अटल व्योम update_hw_sgl_sum_sge(काष्ठा hisi_acc_hw_sgl *hw_sgl, u16 sum)
अणु
	hw_sgl->entry_sum_in_chain = cpu_to_le16(sum);
पूर्ण

अटल व्योम clear_hw_sgl_sge(काष्ठा hisi_acc_hw_sgl *hw_sgl)
अणु
	काष्ठा acc_hw_sge *hw_sge = hw_sgl->sge_entries;
	पूर्णांक i;

	क्रम (i = 0; i < le16_to_cpu(hw_sgl->entry_sum_in_sgl); i++) अणु
		hw_sge[i].page_ctrl = शून्य;
		hw_sge[i].buf = 0;
		hw_sge[i].len = 0;
	पूर्ण
पूर्ण

/**
 * hisi_acc_sg_buf_map_to_hw_sgl - Map a scatterlist to a hw sgl.
 * @dev: The device which hw sgl beदीर्घs to.
 * @sgl: Scatterlist which will be mapped to hw sgl.
 * @pool: Pool which hw sgl memory will be allocated in.
 * @index: Index of hisi_acc_hw_sgl in pool.
 * @hw_sgl_dma: The dma address of allocated hw sgl.
 *
 * This function builds hw sgl according input sgl, user can use hw_sgl_dma
 * as src/dst in its BD. Only support single hw sgl currently.
 */
काष्ठा hisi_acc_hw_sgl *
hisi_acc_sg_buf_map_to_hw_sgl(काष्ठा device *dev,
			      काष्ठा scatterlist *sgl,
			      काष्ठा hisi_acc_sgl_pool *pool,
			      u32 index, dma_addr_t *hw_sgl_dma)
अणु
	काष्ठा hisi_acc_hw_sgl *curr_hw_sgl;
	dma_addr_t curr_sgl_dma = 0;
	काष्ठा acc_hw_sge *curr_hw_sge;
	काष्ठा scatterlist *sg;
	पूर्णांक i, sg_n, sg_n_mapped;

	अगर (!dev || !sgl || !pool || !hw_sgl_dma)
		वापस ERR_PTR(-EINVAL);

	sg_n = sg_nents(sgl);

	sg_n_mapped = dma_map_sg(dev, sgl, sg_n, DMA_BIसूचीECTIONAL);
	अगर (!sg_n_mapped) अणु
		dev_err(dev, "DMA mapping for SG error!\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (sg_n_mapped > pool->sge_nr) अणु
		dev_err(dev, "the number of entries in input scatterlist is bigger than SGL pool setting.\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	curr_hw_sgl = acc_get_sgl(pool, index, &curr_sgl_dma);
	अगर (IS_ERR(curr_hw_sgl)) अणु
		dev_err(dev, "Get SGL error!\n");
		dma_unmap_sg(dev, sgl, sg_n, DMA_BIसूचीECTIONAL);
		वापस ERR_PTR(-ENOMEM);

	पूर्ण
	curr_hw_sgl->entry_length_in_sgl = cpu_to_le16(pool->sge_nr);
	curr_hw_sge = curr_hw_sgl->sge_entries;

	क्रम_each_sg(sgl, sg, sg_n_mapped, i) अणु
		sg_map_to_hw_sg(sg, curr_hw_sge);
		inc_hw_sgl_sge(curr_hw_sgl);
		curr_hw_sge++;
	पूर्ण

	update_hw_sgl_sum_sge(curr_hw_sgl, pool->sge_nr);
	*hw_sgl_dma = curr_sgl_dma;

	वापस curr_hw_sgl;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_acc_sg_buf_map_to_hw_sgl);

/**
 * hisi_acc_sg_buf_unmap() - Unmap allocated hw sgl.
 * @dev: The device which hw sgl beदीर्घs to.
 * @sgl: Related scatterlist.
 * @hw_sgl: Virtual address of hw sgl.
 *
 * This function unmaps allocated hw sgl.
 */
व्योम hisi_acc_sg_buf_unmap(काष्ठा device *dev, काष्ठा scatterlist *sgl,
			   काष्ठा hisi_acc_hw_sgl *hw_sgl)
अणु
	अगर (!dev || !sgl || !hw_sgl)
		वापस;

	dma_unmap_sg(dev, sgl, sg_nents(sgl), DMA_BIसूचीECTIONAL);
	clear_hw_sgl_sge(hw_sgl);
	hw_sgl->entry_sum_in_chain = 0;
	hw_sgl->entry_sum_in_sgl = 0;
	hw_sgl->entry_length_in_sgl = 0;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_acc_sg_buf_unmap);
