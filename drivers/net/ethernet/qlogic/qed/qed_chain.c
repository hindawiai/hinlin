<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* Copyright (c) 2020 Marvell International Ltd. */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/qed/qed_chain.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "qed_dev_api.h"

अटल व्योम qed_chain_init(काष्ठा qed_chain *chain,
			   स्थिर काष्ठा qed_chain_init_params *params,
			   u32 page_cnt)
अणु
	स_रखो(chain, 0, माप(*chain));

	chain->elem_size = params->elem_size;
	chain->पूर्णांकended_use = params->पूर्णांकended_use;
	chain->mode = params->mode;
	chain->cnt_type = params->cnt_type;

	chain->elem_per_page = ELEMS_PER_PAGE(params->elem_size,
					      params->page_size);
	chain->usable_per_page = USABLE_ELEMS_PER_PAGE(params->elem_size,
						       params->page_size,
						       params->mode);
	chain->elem_unusable = UNUSABLE_ELEMS_PER_PAGE(params->elem_size,
						       params->mode);

	chain->elem_per_page_mask = chain->elem_per_page - 1;
	chain->next_page_mask = chain->usable_per_page &
				chain->elem_per_page_mask;

	chain->page_size = params->page_size;
	chain->page_cnt = page_cnt;
	chain->capacity = chain->usable_per_page * page_cnt;
	chain->size = chain->elem_per_page * page_cnt;

	अगर (params->ext_pbl_virt) अणु
		chain->pbl_sp.table_virt = params->ext_pbl_virt;
		chain->pbl_sp.table_phys = params->ext_pbl_phys;

		chain->b_बाह्यal_pbl = true;
	पूर्ण
पूर्ण

अटल व्योम qed_chain_init_next_ptr_elem(स्थिर काष्ठा qed_chain *chain,
					 व्योम *virt_curr, व्योम *virt_next,
					 dma_addr_t phys_next)
अणु
	काष्ठा qed_chain_next *next;
	u32 size;

	size = chain->elem_size * chain->usable_per_page;
	next = virt_curr + size;

	DMA_REGPAIR_LE(next->next_phys, phys_next);
	next->next_virt = virt_next;
पूर्ण

अटल व्योम qed_chain_init_mem(काष्ठा qed_chain *chain, व्योम *virt_addr,
			       dma_addr_t phys_addr)
अणु
	chain->p_virt_addr = virt_addr;
	chain->p_phys_addr = phys_addr;
पूर्ण

अटल व्योम qed_chain_मुक्त_next_ptr(काष्ठा qed_dev *cdev,
				    काष्ठा qed_chain *chain)
अणु
	काष्ठा device *dev = &cdev->pdev->dev;
	काष्ठा qed_chain_next *next;
	dma_addr_t phys, phys_next;
	व्योम *virt, *virt_next;
	u32 size, i;

	size = chain->elem_size * chain->usable_per_page;
	virt = chain->p_virt_addr;
	phys = chain->p_phys_addr;

	क्रम (i = 0; i < chain->page_cnt; i++) अणु
		अगर (!virt)
			अवरोध;

		next = virt + size;
		virt_next = next->next_virt;
		phys_next = HILO_DMA_REGPAIR(next->next_phys);

		dma_मुक्त_coherent(dev, chain->page_size, virt, phys);

		virt = virt_next;
		phys = phys_next;
	पूर्ण
पूर्ण

अटल व्योम qed_chain_मुक्त_single(काष्ठा qed_dev *cdev,
				  काष्ठा qed_chain *chain)
अणु
	अगर (!chain->p_virt_addr)
		वापस;

	dma_मुक्त_coherent(&cdev->pdev->dev, chain->page_size,
			  chain->p_virt_addr, chain->p_phys_addr);
पूर्ण

अटल व्योम qed_chain_मुक्त_pbl(काष्ठा qed_dev *cdev, काष्ठा qed_chain *chain)
अणु
	काष्ठा device *dev = &cdev->pdev->dev;
	काष्ठा addr_tbl_entry *entry;
	u32 i;

	अगर (!chain->pbl.pp_addr_tbl)
		वापस;

	क्रम (i = 0; i < chain->page_cnt; i++) अणु
		entry = chain->pbl.pp_addr_tbl + i;
		अगर (!entry->virt_addr)
			अवरोध;

		dma_मुक्त_coherent(dev, chain->page_size, entry->virt_addr,
				  entry->dma_map);
	पूर्ण

	अगर (!chain->b_बाह्यal_pbl)
		dma_मुक्त_coherent(dev, chain->pbl_sp.table_size,
				  chain->pbl_sp.table_virt,
				  chain->pbl_sp.table_phys);

	vमुक्त(chain->pbl.pp_addr_tbl);
	chain->pbl.pp_addr_tbl = शून्य;
पूर्ण

/**
 * qed_chain_मुक्त() - Free chain DMA memory.
 *
 * @cdev: Main device काष्ठाure.
 * @chain: Chain to मुक्त.
 */
व्योम qed_chain_मुक्त(काष्ठा qed_dev *cdev, काष्ठा qed_chain *chain)
अणु
	चयन (chain->mode) अणु
	हाल QED_CHAIN_MODE_NEXT_PTR:
		qed_chain_मुक्त_next_ptr(cdev, chain);
		अवरोध;
	हाल QED_CHAIN_MODE_SINGLE:
		qed_chain_मुक्त_single(cdev, chain);
		अवरोध;
	हाल QED_CHAIN_MODE_PBL:
		qed_chain_मुक्त_pbl(cdev, chain);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	qed_chain_init_mem(chain, शून्य, 0);
पूर्ण

अटल पूर्णांक
qed_chain_alloc_sanity_check(काष्ठा qed_dev *cdev,
			     स्थिर काष्ठा qed_chain_init_params *params,
			     u32 page_cnt)
अणु
	u64 chain_size;

	chain_size = ELEMS_PER_PAGE(params->elem_size, params->page_size);
	chain_size *= page_cnt;

	अगर (!chain_size)
		वापस -EINVAL;

	/* The actual chain size can be larger than the maximal possible value
	 * after rounding up the requested elements number to pages, and after
	 * taking पूर्णांकo account the unusuable elements (next-ptr elements).
	 * The size of a "u16" chain can be (U16_MAX + 1) since the chain
	 * size/capacity fields are of u32 type.
	 */
	चयन (params->cnt_type) अणु
	हाल QED_CHAIN_CNT_TYPE_U16:
		अगर (chain_size > U16_MAX + 1)
			अवरोध;

		वापस 0;
	हाल QED_CHAIN_CNT_TYPE_U32:
		अगर (chain_size > U32_MAX)
			अवरोध;

		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	DP_NOTICE(cdev,
		  "The actual chain size (0x%llx) is larger than the maximal possible value\n",
		  chain_size);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक qed_chain_alloc_next_ptr(काष्ठा qed_dev *cdev,
				    काष्ठा qed_chain *chain)
अणु
	काष्ठा device *dev = &cdev->pdev->dev;
	व्योम *virt, *virt_prev = शून्य;
	dma_addr_t phys;
	u32 i;

	क्रम (i = 0; i < chain->page_cnt; i++) अणु
		virt = dma_alloc_coherent(dev, chain->page_size, &phys,
					  GFP_KERNEL);
		अगर (!virt)
			वापस -ENOMEM;

		अगर (i == 0) अणु
			qed_chain_init_mem(chain, virt, phys);
			qed_chain_reset(chain);
		पूर्ण अन्यथा अणु
			qed_chain_init_next_ptr_elem(chain, virt_prev, virt,
						     phys);
		पूर्ण

		virt_prev = virt;
	पूर्ण

	/* Last page's next element should poपूर्णांक to the beginning of the
	 * chain.
	 */
	qed_chain_init_next_ptr_elem(chain, virt_prev, chain->p_virt_addr,
				     chain->p_phys_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_chain_alloc_single(काष्ठा qed_dev *cdev,
				  काष्ठा qed_chain *chain)
अणु
	dma_addr_t phys;
	व्योम *virt;

	virt = dma_alloc_coherent(&cdev->pdev->dev, chain->page_size,
				  &phys, GFP_KERNEL);
	अगर (!virt)
		वापस -ENOMEM;

	qed_chain_init_mem(chain, virt, phys);
	qed_chain_reset(chain);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_chain_alloc_pbl(काष्ठा qed_dev *cdev, काष्ठा qed_chain *chain)
अणु
	काष्ठा device *dev = &cdev->pdev->dev;
	काष्ठा addr_tbl_entry *addr_tbl;
	dma_addr_t phys, pbl_phys;
	__le64 *pbl_virt;
	u32 page_cnt, i;
	माप_प्रकार size;
	व्योम *virt;

	page_cnt = chain->page_cnt;

	size = array_size(page_cnt, माप(*addr_tbl));
	अगर (unlikely(size == SIZE_MAX))
		वापस -EOVERFLOW;

	addr_tbl = vzalloc(size);
	अगर (!addr_tbl)
		वापस -ENOMEM;

	chain->pbl.pp_addr_tbl = addr_tbl;

	अगर (chain->b_बाह्यal_pbl) अणु
		pbl_virt = chain->pbl_sp.table_virt;
		जाओ alloc_pages;
	पूर्ण

	size = array_size(page_cnt, माप(*pbl_virt));
	अगर (unlikely(size == SIZE_MAX))
		वापस -EOVERFLOW;

	pbl_virt = dma_alloc_coherent(dev, size, &pbl_phys, GFP_KERNEL);
	अगर (!pbl_virt)
		वापस -ENOMEM;

	chain->pbl_sp.table_virt = pbl_virt;
	chain->pbl_sp.table_phys = pbl_phys;
	chain->pbl_sp.table_size = size;

alloc_pages:
	क्रम (i = 0; i < page_cnt; i++) अणु
		virt = dma_alloc_coherent(dev, chain->page_size, &phys,
					  GFP_KERNEL);
		अगर (!virt)
			वापस -ENOMEM;

		अगर (i == 0) अणु
			qed_chain_init_mem(chain, virt, phys);
			qed_chain_reset(chain);
		पूर्ण

		/* Fill the PBL table with the physical address of the page */
		pbl_virt[i] = cpu_to_le64(phys);

		/* Keep the भव address of the page */
		addr_tbl[i].virt_addr = virt;
		addr_tbl[i].dma_map = phys;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * qed_chain_alloc() - Allocate and initialize a chain.
 *
 * @cdev: Main device काष्ठाure.
 * @chain: Chain to be processed.
 * @params: Chain initialization parameters.
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise.
 */
पूर्णांक qed_chain_alloc(काष्ठा qed_dev *cdev, काष्ठा qed_chain *chain,
		    काष्ठा qed_chain_init_params *params)
अणु
	u32 page_cnt;
	पूर्णांक rc;

	अगर (!params->page_size)
		params->page_size = QED_CHAIN_PAGE_SIZE;

	अगर (params->mode == QED_CHAIN_MODE_SINGLE)
		page_cnt = 1;
	अन्यथा
		page_cnt = QED_CHAIN_PAGE_CNT(params->num_elems,
					      params->elem_size,
					      params->page_size,
					      params->mode);

	rc = qed_chain_alloc_sanity_check(cdev, params, page_cnt);
	अगर (rc) अणु
		DP_NOTICE(cdev,
			  "Cannot allocate a chain with the given arguments:\n");
		DP_NOTICE(cdev,
			  "[use_mode %d, mode %d, cnt_type %d, num_elems %d, elem_size %zu, page_size %u]\n",
			  params->पूर्णांकended_use, params->mode, params->cnt_type,
			  params->num_elems, params->elem_size,
			  params->page_size);
		वापस rc;
	पूर्ण

	qed_chain_init(chain, params, page_cnt);

	चयन (params->mode) अणु
	हाल QED_CHAIN_MODE_NEXT_PTR:
		rc = qed_chain_alloc_next_ptr(cdev, chain);
		अवरोध;
	हाल QED_CHAIN_MODE_SINGLE:
		rc = qed_chain_alloc_single(cdev, chain);
		अवरोध;
	हाल QED_CHAIN_MODE_PBL:
		rc = qed_chain_alloc_pbl(cdev, chain);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!rc)
		वापस 0;

	qed_chain_मुक्त(cdev, chain);

	वापस rc;
पूर्ण
