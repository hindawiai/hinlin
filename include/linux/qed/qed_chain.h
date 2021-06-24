<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_CHAIN_H
#घोषणा _QED_CHAIN_H

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/qed/common_hsi.h>

क्रमागत qed_chain_mode अणु
	/* Each Page contains a next poपूर्णांकer at its end */
	QED_CHAIN_MODE_NEXT_PTR,

	/* Chain is a single page (next ptr) is not required */
	QED_CHAIN_MODE_SINGLE,

	/* Page poपूर्णांकers are located in a side list */
	QED_CHAIN_MODE_PBL,
पूर्ण;

क्रमागत qed_chain_use_mode अणु
	QED_CHAIN_USE_TO_PRODUCE,			/* Chain starts empty */
	QED_CHAIN_USE_TO_CONSUME,			/* Chain starts full */
	QED_CHAIN_USE_TO_CONSUME_PRODUCE,		/* Chain starts empty */
पूर्ण;

क्रमागत qed_chain_cnt_type अणु
	/* The chain's size/prod/cons are kept in 16-bit variables */
	QED_CHAIN_CNT_TYPE_U16,

	/* The chain's size/prod/cons are kept in 32-bit variables  */
	QED_CHAIN_CNT_TYPE_U32,
पूर्ण;

काष्ठा qed_chain_next अणु
	काष्ठा regpair					next_phys;
	व्योम						*next_virt;
पूर्ण;

काष्ठा qed_chain_pbl_u16 अणु
	u16						prod_page_idx;
	u16						cons_page_idx;
पूर्ण;

काष्ठा qed_chain_pbl_u32 अणु
	u32						prod_page_idx;
	u32						cons_page_idx;
पूर्ण;

काष्ठा qed_chain_u16 अणु
	/* Cyclic index of next element to produce/consume */
	u16						prod_idx;
	u16						cons_idx;
पूर्ण;

काष्ठा qed_chain_u32 अणु
	/* Cyclic index of next element to produce/consume */
	u32						prod_idx;
	u32						cons_idx;
पूर्ण;

काष्ठा addr_tbl_entry अणु
	व्योम						*virt_addr;
	dma_addr_t					dma_map;
पूर्ण;

काष्ठा qed_chain अणु
	/* Fastpath portion of the chain - required क्रम commands such
	 * as produce / consume.
	 */

	/* Poपूर्णांक to next element to produce/consume */
	व्योम						*p_prod_elem;
	व्योम						*p_cons_elem;

	/* Fastpath portions of the PBL [अगर exists] */

	काष्ठा अणु
		/* Table क्रम keeping the भव and physical addresses of the
		 * chain pages, respectively to the physical addresses
		 * in the pbl table.
		 */
		काष्ठा addr_tbl_entry			*pp_addr_tbl;

		जोड़ अणु
			काष्ठा qed_chain_pbl_u16	u16;
			काष्ठा qed_chain_pbl_u32	u32;
		पूर्ण					c;
	पूर्ण						pbl;

	जोड़ अणु
		काष्ठा qed_chain_u16			chain16;
		काष्ठा qed_chain_u32			chain32;
	पूर्ण						u;

	/* Capacity counts only usable elements */
	u32						capacity;
	u32						page_cnt;

	क्रमागत qed_chain_mode				mode;

	/* Elements inक्रमmation क्रम fast calculations */
	u16						elem_per_page;
	u16						elem_per_page_mask;
	u16						elem_size;
	u16						next_page_mask;
	u16						usable_per_page;
	u8						elem_unusable;

	क्रमागत qed_chain_cnt_type				cnt_type;

	/* Slowpath of the chain - required क्रम initialization and deकाष्ठाion,
	 * but isn't involved in regular functionality.
	 */

	u32						page_size;

	/* Base address of a pre-allocated buffer क्रम pbl */
	काष्ठा अणु
		__le64					*table_virt;
		dma_addr_t				table_phys;
		माप_प्रकार					table_size;
	पूर्ण						pbl_sp;

	/* Address of first page of the chain - the address is required
	 * क्रम fastpath operation [consume/produce] but only क्रम the SINGLE
	 * flavour which isn't considered fastpath [== SPQ].
	 */
	व्योम						*p_virt_addr;
	dma_addr_t					p_phys_addr;

	/* Total number of elements [क्रम entire chain] */
	u32						size;

	क्रमागत qed_chain_use_mode				पूर्णांकended_use;

	bool						b_बाह्यal_pbl;
पूर्ण;

काष्ठा qed_chain_init_params अणु
	क्रमागत qed_chain_mode				mode;
	क्रमागत qed_chain_use_mode				पूर्णांकended_use;
	क्रमागत qed_chain_cnt_type				cnt_type;

	u32						page_size;
	u32						num_elems;
	माप_प्रकार						elem_size;

	व्योम						*ext_pbl_virt;
	dma_addr_t					ext_pbl_phys;
पूर्ण;

#घोषणा QED_CHAIN_PAGE_SIZE				SZ_4K

#घोषणा ELEMS_PER_PAGE(elem_size, page_size)				     \
	((page_size) / (elem_size))

#घोषणा UNUSABLE_ELEMS_PER_PAGE(elem_size, mode)			     \
	(((mode) == QED_CHAIN_MODE_NEXT_PTR) ?				     \
	 (u8)(1 + ((माप(काष्ठा qed_chain_next) - 1) / (elem_size))) :     \
	 0)

#घोषणा USABLE_ELEMS_PER_PAGE(elem_size, page_size, mode)		     \
	((u32)(ELEMS_PER_PAGE((elem_size), (page_size)) -		     \
	       UNUSABLE_ELEMS_PER_PAGE((elem_size), (mode))))

#घोषणा QED_CHAIN_PAGE_CNT(elem_cnt, elem_size, page_size, mode)	     \
	DIV_ROUND_UP((elem_cnt),					     \
		     USABLE_ELEMS_PER_PAGE((elem_size), (page_size), (mode)))

#घोषणा is_chain_u16(p)							     \
	((p)->cnt_type == QED_CHAIN_CNT_TYPE_U16)
#घोषणा is_chain_u32(p)							     \
	((p)->cnt_type == QED_CHAIN_CNT_TYPE_U32)

/* Accessors */

अटल अंतरभूत u16 qed_chain_get_prod_idx(स्थिर काष्ठा qed_chain *chain)
अणु
	वापस chain->u.chain16.prod_idx;
पूर्ण

अटल अंतरभूत u16 qed_chain_get_cons_idx(स्थिर काष्ठा qed_chain *chain)
अणु
	वापस chain->u.chain16.cons_idx;
पूर्ण

अटल अंतरभूत u32 qed_chain_get_prod_idx_u32(स्थिर काष्ठा qed_chain *chain)
अणु
	वापस chain->u.chain32.prod_idx;
पूर्ण

अटल अंतरभूत u32 qed_chain_get_cons_idx_u32(स्थिर काष्ठा qed_chain *chain)
अणु
	वापस chain->u.chain32.cons_idx;
पूर्ण

अटल अंतरभूत u16 qed_chain_get_elem_used(स्थिर काष्ठा qed_chain *chain)
अणु
	u32 prod = qed_chain_get_prod_idx(chain);
	u32 cons = qed_chain_get_cons_idx(chain);
	u16 elem_per_page = chain->elem_per_page;
	u16 used;

	अगर (prod < cons)
		prod += (u32)U16_MAX + 1;

	used = (u16)(prod - cons);
	अगर (chain->mode == QED_CHAIN_MODE_NEXT_PTR)
		used -= (u16)(prod / elem_per_page - cons / elem_per_page);

	वापस used;
पूर्ण

अटल अंतरभूत u16 qed_chain_get_elem_left(स्थिर काष्ठा qed_chain *chain)
अणु
	वापस (u16)(chain->capacity - qed_chain_get_elem_used(chain));
पूर्ण

अटल अंतरभूत u32 qed_chain_get_elem_used_u32(स्थिर काष्ठा qed_chain *chain)
अणु
	u64 prod = qed_chain_get_prod_idx_u32(chain);
	u64 cons = qed_chain_get_cons_idx_u32(chain);
	u16 elem_per_page = chain->elem_per_page;
	u32 used;

	अगर (prod < cons)
		prod += (u64)U32_MAX + 1;

	used = (u32)(prod - cons);
	अगर (chain->mode == QED_CHAIN_MODE_NEXT_PTR)
		used -= (u32)(prod / elem_per_page - cons / elem_per_page);

	वापस used;
पूर्ण

अटल अंतरभूत u32 qed_chain_get_elem_left_u32(स्थिर काष्ठा qed_chain *chain)
अणु
	वापस chain->capacity - qed_chain_get_elem_used_u32(chain);
पूर्ण

अटल अंतरभूत u16 qed_chain_get_usable_per_page(स्थिर काष्ठा qed_chain *chain)
अणु
	वापस chain->usable_per_page;
पूर्ण

अटल अंतरभूत u8 qed_chain_get_unusable_per_page(स्थिर काष्ठा qed_chain *chain)
अणु
	वापस chain->elem_unusable;
पूर्ण

अटल अंतरभूत u32 qed_chain_get_page_cnt(स्थिर काष्ठा qed_chain *chain)
अणु
	वापस chain->page_cnt;
पूर्ण

अटल अंतरभूत dma_addr_t qed_chain_get_pbl_phys(स्थिर काष्ठा qed_chain *chain)
अणु
	वापस chain->pbl_sp.table_phys;
पूर्ण

/**
 * @brief qed_chain_advance_page -
 *
 * Advance the next element across pages क्रम a linked chain
 *
 * @param p_chain
 * @param p_next_elem
 * @param idx_to_inc
 * @param page_to_inc
 */
अटल अंतरभूत व्योम
qed_chain_advance_page(काष्ठा qed_chain *p_chain,
		       व्योम **p_next_elem, व्योम *idx_to_inc, व्योम *page_to_inc)
अणु
	काष्ठा qed_chain_next *p_next = शून्य;
	u32 page_index = 0;

	चयन (p_chain->mode) अणु
	हाल QED_CHAIN_MODE_NEXT_PTR:
		p_next = *p_next_elem;
		*p_next_elem = p_next->next_virt;
		अगर (is_chain_u16(p_chain))
			*(u16 *)idx_to_inc += p_chain->elem_unusable;
		अन्यथा
			*(u32 *)idx_to_inc += p_chain->elem_unusable;
		अवरोध;
	हाल QED_CHAIN_MODE_SINGLE:
		*p_next_elem = p_chain->p_virt_addr;
		अवरोध;

	हाल QED_CHAIN_MODE_PBL:
		अगर (is_chain_u16(p_chain)) अणु
			अगर (++(*(u16 *)page_to_inc) == p_chain->page_cnt)
				*(u16 *)page_to_inc = 0;
			page_index = *(u16 *)page_to_inc;
		पूर्ण अन्यथा अणु
			अगर (++(*(u32 *)page_to_inc) == p_chain->page_cnt)
				*(u32 *)page_to_inc = 0;
			page_index = *(u32 *)page_to_inc;
		पूर्ण
		*p_next_elem = p_chain->pbl.pp_addr_tbl[page_index].virt_addr;
	पूर्ण
पूर्ण

#घोषणा is_unusable_idx(p, idx)	\
	(((p)->u.chain16.idx & (p)->elem_per_page_mask) == (p)->usable_per_page)

#घोषणा is_unusable_idx_u32(p, idx) \
	(((p)->u.chain32.idx & (p)->elem_per_page_mask) == (p)->usable_per_page)
#घोषणा is_unusable_next_idx(p, idx)				 \
	((((p)->u.chain16.idx + 1) & (p)->elem_per_page_mask) == \
	 (p)->usable_per_page)

#घोषणा is_unusable_next_idx_u32(p, idx)			 \
	((((p)->u.chain32.idx + 1) & (p)->elem_per_page_mask) == \
	 (p)->usable_per_page)

#घोषणा test_and_skip(p, idx)						   \
	करो अणु						\
		अगर (is_chain_u16(p)) अणु					   \
			अगर (is_unusable_idx(p, idx))			   \
				(p)->u.chain16.idx += (p)->elem_unusable;  \
		पूर्ण अन्यथा अणु						   \
			अगर (is_unusable_idx_u32(p, idx))		   \
				(p)->u.chain32.idx += (p)->elem_unusable;  \
		पूर्ण					\
	पूर्ण जबतक (0)

/**
 * @brief qed_chain_वापस_produced -
 *
 * A chain in which the driver "Produces" elements should use this API
 * to indicate previous produced elements are now consumed.
 *
 * @param p_chain
 */
अटल अंतरभूत व्योम qed_chain_वापस_produced(काष्ठा qed_chain *p_chain)
अणु
	अगर (is_chain_u16(p_chain))
		p_chain->u.chain16.cons_idx++;
	अन्यथा
		p_chain->u.chain32.cons_idx++;
	test_and_skip(p_chain, cons_idx);
पूर्ण

/**
 * @brief qed_chain_produce -
 *
 * A chain in which the driver "Produces" elements should use this to get
 * a poपूर्णांकer to the next element which can be "Produced". It's driver
 * responsibility to validate that the chain has room क्रम new element.
 *
 * @param p_chain
 *
 * @वापस व्योम*, a poपूर्णांकer to next element
 */
अटल अंतरभूत व्योम *qed_chain_produce(काष्ठा qed_chain *p_chain)
अणु
	व्योम *p_ret = शून्य, *p_prod_idx, *p_prod_page_idx;

	अगर (is_chain_u16(p_chain)) अणु
		अगर ((p_chain->u.chain16.prod_idx &
		     p_chain->elem_per_page_mask) == p_chain->next_page_mask) अणु
			p_prod_idx = &p_chain->u.chain16.prod_idx;
			p_prod_page_idx = &p_chain->pbl.c.u16.prod_page_idx;
			qed_chain_advance_page(p_chain, &p_chain->p_prod_elem,
					       p_prod_idx, p_prod_page_idx);
		पूर्ण
		p_chain->u.chain16.prod_idx++;
	पूर्ण अन्यथा अणु
		अगर ((p_chain->u.chain32.prod_idx &
		     p_chain->elem_per_page_mask) == p_chain->next_page_mask) अणु
			p_prod_idx = &p_chain->u.chain32.prod_idx;
			p_prod_page_idx = &p_chain->pbl.c.u32.prod_page_idx;
			qed_chain_advance_page(p_chain, &p_chain->p_prod_elem,
					       p_prod_idx, p_prod_page_idx);
		पूर्ण
		p_chain->u.chain32.prod_idx++;
	पूर्ण

	p_ret = p_chain->p_prod_elem;
	p_chain->p_prod_elem = (व्योम *)(((u8 *)p_chain->p_prod_elem) +
					p_chain->elem_size);

	वापस p_ret;
पूर्ण

/**
 * @brief qed_chain_get_capacity -
 *
 * Get the maximum number of BDs in chain
 *
 * @param p_chain
 * @param num
 *
 * @वापस number of unusable BDs
 */
अटल अंतरभूत u32 qed_chain_get_capacity(काष्ठा qed_chain *p_chain)
अणु
	वापस p_chain->capacity;
पूर्ण

/**
 * @brief qed_chain_recycle_consumed -
 *
 * Returns an element which was previously consumed;
 * Increments producers so they could be written to FW.
 *
 * @param p_chain
 */
अटल अंतरभूत व्योम qed_chain_recycle_consumed(काष्ठा qed_chain *p_chain)
अणु
	test_and_skip(p_chain, prod_idx);
	अगर (is_chain_u16(p_chain))
		p_chain->u.chain16.prod_idx++;
	अन्यथा
		p_chain->u.chain32.prod_idx++;
पूर्ण

/**
 * @brief qed_chain_consume -
 *
 * A Chain in which the driver utilizes data written by a dअगरferent source
 * (i.e., FW) should use this to access passed buffers.
 *
 * @param p_chain
 *
 * @वापस व्योम*, a poपूर्णांकer to the next buffer written
 */
अटल अंतरभूत व्योम *qed_chain_consume(काष्ठा qed_chain *p_chain)
अणु
	व्योम *p_ret = शून्य, *p_cons_idx, *p_cons_page_idx;

	अगर (is_chain_u16(p_chain)) अणु
		अगर ((p_chain->u.chain16.cons_idx &
		     p_chain->elem_per_page_mask) == p_chain->next_page_mask) अणु
			p_cons_idx = &p_chain->u.chain16.cons_idx;
			p_cons_page_idx = &p_chain->pbl.c.u16.cons_page_idx;
			qed_chain_advance_page(p_chain, &p_chain->p_cons_elem,
					       p_cons_idx, p_cons_page_idx);
		पूर्ण
		p_chain->u.chain16.cons_idx++;
	पूर्ण अन्यथा अणु
		अगर ((p_chain->u.chain32.cons_idx &
		     p_chain->elem_per_page_mask) == p_chain->next_page_mask) अणु
			p_cons_idx = &p_chain->u.chain32.cons_idx;
			p_cons_page_idx = &p_chain->pbl.c.u32.cons_page_idx;
			qed_chain_advance_page(p_chain, &p_chain->p_cons_elem,
					       p_cons_idx, p_cons_page_idx);
		पूर्ण
		p_chain->u.chain32.cons_idx++;
	पूर्ण

	p_ret = p_chain->p_cons_elem;
	p_chain->p_cons_elem = (व्योम *)(((u8 *)p_chain->p_cons_elem) +
					p_chain->elem_size);

	वापस p_ret;
पूर्ण

/**
 * @brief qed_chain_reset - Resets the chain to its start state
 *
 * @param p_chain poपूर्णांकer to a previously allocated chain
 */
अटल अंतरभूत व्योम qed_chain_reset(काष्ठा qed_chain *p_chain)
अणु
	u32 i;

	अगर (is_chain_u16(p_chain)) अणु
		p_chain->u.chain16.prod_idx = 0;
		p_chain->u.chain16.cons_idx = 0;
	पूर्ण अन्यथा अणु
		p_chain->u.chain32.prod_idx = 0;
		p_chain->u.chain32.cons_idx = 0;
	पूर्ण
	p_chain->p_cons_elem = p_chain->p_virt_addr;
	p_chain->p_prod_elem = p_chain->p_virt_addr;

	अगर (p_chain->mode == QED_CHAIN_MODE_PBL) अणु
		/* Use (page_cnt - 1) as a reset value क्रम the prod/cons page's
		 * indices, to aव्योम unnecessary page advancing on the first
		 * call to qed_chain_produce/consume. Instead, the indices
		 * will be advanced to page_cnt and then will be wrapped to 0.
		 */
		u32 reset_val = p_chain->page_cnt - 1;

		अगर (is_chain_u16(p_chain)) अणु
			p_chain->pbl.c.u16.prod_page_idx = (u16)reset_val;
			p_chain->pbl.c.u16.cons_page_idx = (u16)reset_val;
		पूर्ण अन्यथा अणु
			p_chain->pbl.c.u32.prod_page_idx = reset_val;
			p_chain->pbl.c.u32.cons_page_idx = reset_val;
		पूर्ण
	पूर्ण

	चयन (p_chain->पूर्णांकended_use) अणु
	हाल QED_CHAIN_USE_TO_CONSUME:
		/* produce empty elements */
		क्रम (i = 0; i < p_chain->capacity; i++)
			qed_chain_recycle_consumed(p_chain);
		अवरोध;

	हाल QED_CHAIN_USE_TO_CONSUME_PRODUCE:
	हाल QED_CHAIN_USE_TO_PRODUCE:
	शेष:
		/* Do nothing */
		अवरोध;
	पूर्ण
पूर्ण

/**
 * @brief qed_chain_get_last_elem -
 *
 * Returns a poपूर्णांकer to the last element of the chain
 *
 * @param p_chain
 *
 * @वापस व्योम*
 */
अटल अंतरभूत व्योम *qed_chain_get_last_elem(काष्ठा qed_chain *p_chain)
अणु
	काष्ठा qed_chain_next *p_next = शून्य;
	व्योम *p_virt_addr = शून्य;
	u32 size, last_page_idx;

	अगर (!p_chain->p_virt_addr)
		जाओ out;

	चयन (p_chain->mode) अणु
	हाल QED_CHAIN_MODE_NEXT_PTR:
		size = p_chain->elem_size * p_chain->usable_per_page;
		p_virt_addr = p_chain->p_virt_addr;
		p_next = (काष्ठा qed_chain_next *)((u8 *)p_virt_addr + size);
		जबतक (p_next->next_virt != p_chain->p_virt_addr) अणु
			p_virt_addr = p_next->next_virt;
			p_next = (काष्ठा qed_chain_next *)((u8 *)p_virt_addr +
							   size);
		पूर्ण
		अवरोध;
	हाल QED_CHAIN_MODE_SINGLE:
		p_virt_addr = p_chain->p_virt_addr;
		अवरोध;
	हाल QED_CHAIN_MODE_PBL:
		last_page_idx = p_chain->page_cnt - 1;
		p_virt_addr = p_chain->pbl.pp_addr_tbl[last_page_idx].virt_addr;
		अवरोध;
	पूर्ण
	/* p_virt_addr poपूर्णांकs at this stage to the last page of the chain */
	size = p_chain->elem_size * (p_chain->usable_per_page - 1);
	p_virt_addr = (u8 *)p_virt_addr + size;
out:
	वापस p_virt_addr;
पूर्ण

/**
 * @brief qed_chain_set_prod - sets the prod to the given value
 *
 * @param prod_idx
 * @param p_prod_elem
 */
अटल अंतरभूत व्योम qed_chain_set_prod(काष्ठा qed_chain *p_chain,
				      u32 prod_idx, व्योम *p_prod_elem)
अणु
	अगर (p_chain->mode == QED_CHAIN_MODE_PBL) अणु
		u32 cur_prod, page_mask, page_cnt, page_dअगरf;

		cur_prod = is_chain_u16(p_chain) ? p_chain->u.chain16.prod_idx :
			   p_chain->u.chain32.prod_idx;

		/* Assume that number of elements in a page is घातer of 2 */
		page_mask = ~p_chain->elem_per_page_mask;

		/* Use "cur_prod - 1" and "prod_idx - 1" since producer index
		 * reaches the first element of next page beक्रमe the page index
		 * is incremented. See qed_chain_produce().
		 * Index wrap around is not a problem because the dअगरference
		 * between current and given producer indices is always
		 * positive and lower than the chain's capacity.
		 */
		page_dअगरf = (((cur_prod - 1) & page_mask) -
			     ((prod_idx - 1) & page_mask)) /
			    p_chain->elem_per_page;

		page_cnt = qed_chain_get_page_cnt(p_chain);
		अगर (is_chain_u16(p_chain))
			p_chain->pbl.c.u16.prod_page_idx =
				(p_chain->pbl.c.u16.prod_page_idx -
				 page_dअगरf + page_cnt) % page_cnt;
		अन्यथा
			p_chain->pbl.c.u32.prod_page_idx =
				(p_chain->pbl.c.u32.prod_page_idx -
				 page_dअगरf + page_cnt) % page_cnt;
	पूर्ण

	अगर (is_chain_u16(p_chain))
		p_chain->u.chain16.prod_idx = (u16) prod_idx;
	अन्यथा
		p_chain->u.chain32.prod_idx = prod_idx;
	p_chain->p_prod_elem = p_prod_elem;
पूर्ण

/**
 * @brief qed_chain_pbl_zero_mem - set chain memory to 0
 *
 * @param p_chain
 */
अटल अंतरभूत व्योम qed_chain_pbl_zero_mem(काष्ठा qed_chain *p_chain)
अणु
	u32 i, page_cnt;

	अगर (p_chain->mode != QED_CHAIN_MODE_PBL)
		वापस;

	page_cnt = qed_chain_get_page_cnt(p_chain);

	क्रम (i = 0; i < page_cnt; i++)
		स_रखो(p_chain->pbl.pp_addr_tbl[i].virt_addr, 0,
		       p_chain->page_size);
पूर्ण

#पूर्ण_अगर
