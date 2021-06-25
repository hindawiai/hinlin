<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, Intel Corporation. */

#समावेश "ice_common.h"

#घोषणा ICE_CQ_INIT_REGS(qinfo, prefix)				\
करो अणु								\
	(qinfo)->sq.head = prefix##_ATQH;			\
	(qinfo)->sq.tail = prefix##_ATQT;			\
	(qinfo)->sq.len = prefix##_ATQLEN;			\
	(qinfo)->sq.bah = prefix##_ATQBAH;			\
	(qinfo)->sq.bal = prefix##_ATQBAL;			\
	(qinfo)->sq.len_mask = prefix##_ATQLEN_ATQLEN_M;	\
	(qinfo)->sq.len_ena_mask = prefix##_ATQLEN_ATQENABLE_M;	\
	(qinfo)->sq.len_crit_mask = prefix##_ATQLEN_ATQCRIT_M;	\
	(qinfo)->sq.head_mask = prefix##_ATQH_ATQH_M;		\
	(qinfo)->rq.head = prefix##_ARQH;			\
	(qinfo)->rq.tail = prefix##_ARQT;			\
	(qinfo)->rq.len = prefix##_ARQLEN;			\
	(qinfo)->rq.bah = prefix##_ARQBAH;			\
	(qinfo)->rq.bal = prefix##_ARQBAL;			\
	(qinfo)->rq.len_mask = prefix##_ARQLEN_ARQLEN_M;	\
	(qinfo)->rq.len_ena_mask = prefix##_ARQLEN_ARQENABLE_M;	\
	(qinfo)->rq.len_crit_mask = prefix##_ARQLEN_ARQCRIT_M;	\
	(qinfo)->rq.head_mask = prefix##_ARQH_ARQH_M;		\
पूर्ण जबतक (0)

/**
 * ice_adminq_init_regs - Initialize AdminQ रेजिस्टरs
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * This assumes the alloc_sq and alloc_rq functions have alपढ़ोy been called
 */
अटल व्योम ice_adminq_init_regs(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_ctl_q_info *cq = &hw->adminq;

	ICE_CQ_INIT_REGS(cq, PF_FW);
पूर्ण

/**
 * ice_mailbox_init_regs - Initialize Mailbox रेजिस्टरs
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * This assumes the alloc_sq and alloc_rq functions have alपढ़ोy been called
 */
अटल व्योम ice_mailbox_init_regs(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_ctl_q_info *cq = &hw->mailboxq;

	ICE_CQ_INIT_REGS(cq, PF_MBX);
पूर्ण

/**
 * ice_check_sq_alive
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @cq: poपूर्णांकer to the specअगरic Control queue
 *
 * Returns true अगर Queue is enabled अन्यथा false.
 */
bool ice_check_sq_alive(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq)
अणु
	/* check both queue-length and queue-enable fields */
	अगर (cq->sq.len && cq->sq.len_mask && cq->sq.len_ena_mask)
		वापस (rd32(hw, cq->sq.len) & (cq->sq.len_mask |
						cq->sq.len_ena_mask)) ==
			(cq->num_sq_entries | cq->sq.len_ena_mask);

	वापस false;
पूर्ण

/**
 * ice_alloc_ctrlq_sq_ring - Allocate Control Transmit Queue (ATQ) rings
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @cq: poपूर्णांकer to the specअगरic Control queue
 */
अटल क्रमागत ice_status
ice_alloc_ctrlq_sq_ring(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq)
अणु
	माप_प्रकार size = cq->num_sq_entries * माप(काष्ठा ice_aq_desc);

	cq->sq.desc_buf.va = dmam_alloc_coherent(ice_hw_to_dev(hw), size,
						 &cq->sq.desc_buf.pa,
						 GFP_KERNEL | __GFP_ZERO);
	अगर (!cq->sq.desc_buf.va)
		वापस ICE_ERR_NO_MEMORY;
	cq->sq.desc_buf.size = size;

	cq->sq.cmd_buf = devm_kसुस्मृति(ice_hw_to_dev(hw), cq->num_sq_entries,
				      माप(काष्ठा ice_sq_cd), GFP_KERNEL);
	अगर (!cq->sq.cmd_buf) अणु
		dmam_मुक्त_coherent(ice_hw_to_dev(hw), cq->sq.desc_buf.size,
				   cq->sq.desc_buf.va, cq->sq.desc_buf.pa);
		cq->sq.desc_buf.va = शून्य;
		cq->sq.desc_buf.pa = 0;
		cq->sq.desc_buf.size = 0;
		वापस ICE_ERR_NO_MEMORY;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_alloc_ctrlq_rq_ring - Allocate Control Receive Queue (ARQ) rings
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @cq: poपूर्णांकer to the specअगरic Control queue
 */
अटल क्रमागत ice_status
ice_alloc_ctrlq_rq_ring(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq)
अणु
	माप_प्रकार size = cq->num_rq_entries * माप(काष्ठा ice_aq_desc);

	cq->rq.desc_buf.va = dmam_alloc_coherent(ice_hw_to_dev(hw), size,
						 &cq->rq.desc_buf.pa,
						 GFP_KERNEL | __GFP_ZERO);
	अगर (!cq->rq.desc_buf.va)
		वापस ICE_ERR_NO_MEMORY;
	cq->rq.desc_buf.size = size;
	वापस 0;
पूर्ण

/**
 * ice_मुक्त_cq_ring - Free control queue ring
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @ring: poपूर्णांकer to the specअगरic control queue ring
 *
 * This assumes the posted buffers have alपढ़ोy been cleaned
 * and de-allocated
 */
अटल व्योम ice_मुक्त_cq_ring(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_ring *ring)
अणु
	dmam_मुक्त_coherent(ice_hw_to_dev(hw), ring->desc_buf.size,
			   ring->desc_buf.va, ring->desc_buf.pa);
	ring->desc_buf.va = शून्य;
	ring->desc_buf.pa = 0;
	ring->desc_buf.size = 0;
पूर्ण

/**
 * ice_alloc_rq_bufs - Allocate pre-posted buffers क्रम the ARQ
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @cq: poपूर्णांकer to the specअगरic Control queue
 */
अटल क्रमागत ice_status
ice_alloc_rq_bufs(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq)
अणु
	पूर्णांक i;

	/* We'll be allocating the buffer info memory first, then we can
	 * allocate the mapped buffers क्रम the event processing
	 */
	cq->rq.dma_head = devm_kसुस्मृति(ice_hw_to_dev(hw), cq->num_rq_entries,
				       माप(cq->rq.desc_buf), GFP_KERNEL);
	अगर (!cq->rq.dma_head)
		वापस ICE_ERR_NO_MEMORY;
	cq->rq.r.rq_bi = (काष्ठा ice_dma_mem *)cq->rq.dma_head;

	/* allocate the mapped buffers */
	क्रम (i = 0; i < cq->num_rq_entries; i++) अणु
		काष्ठा ice_aq_desc *desc;
		काष्ठा ice_dma_mem *bi;

		bi = &cq->rq.r.rq_bi[i];
		bi->va = dmam_alloc_coherent(ice_hw_to_dev(hw),
					     cq->rq_buf_size, &bi->pa,
					     GFP_KERNEL | __GFP_ZERO);
		अगर (!bi->va)
			जाओ unwind_alloc_rq_bufs;
		bi->size = cq->rq_buf_size;

		/* now configure the descriptors क्रम use */
		desc = ICE_CTL_Q_DESC(cq->rq, i);

		desc->flags = cpu_to_le16(ICE_AQ_FLAG_BUF);
		अगर (cq->rq_buf_size > ICE_AQ_LG_BUF)
			desc->flags |= cpu_to_le16(ICE_AQ_FLAG_LB);
		desc->opcode = 0;
		/* This is in accordance with Admin queue design, there is no
		 * रेजिस्टर क्रम buffer size configuration
		 */
		desc->datalen = cpu_to_le16(bi->size);
		desc->retval = 0;
		desc->cookie_high = 0;
		desc->cookie_low = 0;
		desc->params.generic.addr_high =
			cpu_to_le32(upper_32_bits(bi->pa));
		desc->params.generic.addr_low =
			cpu_to_le32(lower_32_bits(bi->pa));
		desc->params.generic.param0 = 0;
		desc->params.generic.param1 = 0;
	पूर्ण
	वापस 0;

unwind_alloc_rq_bufs:
	/* करोn't try to मुक्त the one that failed... */
	i--;
	क्रम (; i >= 0; i--) अणु
		dmam_मुक्त_coherent(ice_hw_to_dev(hw), cq->rq.r.rq_bi[i].size,
				   cq->rq.r.rq_bi[i].va, cq->rq.r.rq_bi[i].pa);
		cq->rq.r.rq_bi[i].va = शून्य;
		cq->rq.r.rq_bi[i].pa = 0;
		cq->rq.r.rq_bi[i].size = 0;
	पूर्ण
	cq->rq.r.rq_bi = शून्य;
	devm_kमुक्त(ice_hw_to_dev(hw), cq->rq.dma_head);
	cq->rq.dma_head = शून्य;

	वापस ICE_ERR_NO_MEMORY;
पूर्ण

/**
 * ice_alloc_sq_bufs - Allocate empty buffer काष्ठाs क्रम the ATQ
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @cq: poपूर्णांकer to the specअगरic Control queue
 */
अटल क्रमागत ice_status
ice_alloc_sq_bufs(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq)
अणु
	पूर्णांक i;

	/* No mapped memory needed yet, just the buffer info काष्ठाures */
	cq->sq.dma_head = devm_kसुस्मृति(ice_hw_to_dev(hw), cq->num_sq_entries,
				       माप(cq->sq.desc_buf), GFP_KERNEL);
	अगर (!cq->sq.dma_head)
		वापस ICE_ERR_NO_MEMORY;
	cq->sq.r.sq_bi = (काष्ठा ice_dma_mem *)cq->sq.dma_head;

	/* allocate the mapped buffers */
	क्रम (i = 0; i < cq->num_sq_entries; i++) अणु
		काष्ठा ice_dma_mem *bi;

		bi = &cq->sq.r.sq_bi[i];
		bi->va = dmam_alloc_coherent(ice_hw_to_dev(hw),
					     cq->sq_buf_size, &bi->pa,
					     GFP_KERNEL | __GFP_ZERO);
		अगर (!bi->va)
			जाओ unwind_alloc_sq_bufs;
		bi->size = cq->sq_buf_size;
	पूर्ण
	वापस 0;

unwind_alloc_sq_bufs:
	/* करोn't try to मुक्त the one that failed... */
	i--;
	क्रम (; i >= 0; i--) अणु
		dmam_मुक्त_coherent(ice_hw_to_dev(hw), cq->sq.r.sq_bi[i].size,
				   cq->sq.r.sq_bi[i].va, cq->sq.r.sq_bi[i].pa);
		cq->sq.r.sq_bi[i].va = शून्य;
		cq->sq.r.sq_bi[i].pa = 0;
		cq->sq.r.sq_bi[i].size = 0;
	पूर्ण
	cq->sq.r.sq_bi = शून्य;
	devm_kमुक्त(ice_hw_to_dev(hw), cq->sq.dma_head);
	cq->sq.dma_head = शून्य;

	वापस ICE_ERR_NO_MEMORY;
पूर्ण

अटल क्रमागत ice_status
ice_cfg_cq_regs(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_ring *ring, u16 num_entries)
अणु
	/* Clear Head and Tail */
	wr32(hw, ring->head, 0);
	wr32(hw, ring->tail, 0);

	/* set starting poपूर्णांक */
	wr32(hw, ring->len, (num_entries | ring->len_ena_mask));
	wr32(hw, ring->bal, lower_32_bits(ring->desc_buf.pa));
	wr32(hw, ring->bah, upper_32_bits(ring->desc_buf.pa));

	/* Check one रेजिस्टर to verअगरy that config was applied */
	अगर (rd32(hw, ring->bal) != lower_32_bits(ring->desc_buf.pa))
		वापस ICE_ERR_AQ_ERROR;

	वापस 0;
पूर्ण

/**
 * ice_cfg_sq_regs - configure Control ATQ रेजिस्टरs
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @cq: poपूर्णांकer to the specअगरic Control queue
 *
 * Configure base address and length रेजिस्टरs क्रम the transmit queue
 */
अटल क्रमागत ice_status
ice_cfg_sq_regs(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq)
अणु
	वापस ice_cfg_cq_regs(hw, &cq->sq, cq->num_sq_entries);
पूर्ण

/**
 * ice_cfg_rq_regs - configure Control ARQ रेजिस्टर
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @cq: poपूर्णांकer to the specअगरic Control queue
 *
 * Configure base address and length रेजिस्टरs क्रम the receive (event queue)
 */
अटल क्रमागत ice_status
ice_cfg_rq_regs(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq)
अणु
	क्रमागत ice_status status;

	status = ice_cfg_cq_regs(hw, &cq->rq, cq->num_rq_entries);
	अगर (status)
		वापस status;

	/* Update tail in the HW to post pre-allocated buffers */
	wr32(hw, cq->rq.tail, (u32)(cq->num_rq_entries - 1));

	वापस 0;
पूर्ण

#घोषणा ICE_FREE_CQ_BUFS(hw, qi, ring)					\
करो अणु									\
	/* मुक्त descriptors */						\
	अगर ((qi)->ring.r.ring##_bi) अणु					\
		पूर्णांक i;							\
									\
		क्रम (i = 0; i < (qi)->num_##ring##_entries; i++)	\
			अगर ((qi)->ring.r.ring##_bi[i].pa) अणु		\
				dmam_मुक्त_coherent(ice_hw_to_dev(hw),	\
					(qi)->ring.r.ring##_bi[i].size,	\
					(qi)->ring.r.ring##_bi[i].va,	\
					(qi)->ring.r.ring##_bi[i].pa);	\
					(qi)->ring.r.ring##_bi[i].va = शून्य;\
					(qi)->ring.r.ring##_bi[i].pa = 0;\
					(qi)->ring.r.ring##_bi[i].size = 0;\
		पूर्ण							\
	पूर्ण								\
	/* मुक्त the buffer info list */					\
	अगर ((qi)->ring.cmd_buf)						\
		devm_kमुक्त(ice_hw_to_dev(hw), (qi)->ring.cmd_buf);	\
	/* मुक्त DMA head */						\
	devm_kमुक्त(ice_hw_to_dev(hw), (qi)->ring.dma_head);		\
पूर्ण जबतक (0)

/**
 * ice_init_sq - मुख्य initialization routine क्रम Control ATQ
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @cq: poपूर्णांकer to the specअगरic Control queue
 *
 * This is the मुख्य initialization routine क्रम the Control Send Queue
 * Prior to calling this function, the driver *MUST* set the following fields
 * in the cq->काष्ठाure:
 *     - cq->num_sq_entries
 *     - cq->sq_buf_size
 *
 * Do *NOT* hold the lock when calling this as the memory allocation routines
 * called are not going to be atomic context safe
 */
अटल क्रमागत ice_status ice_init_sq(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq)
अणु
	क्रमागत ice_status ret_code;

	अगर (cq->sq.count > 0) अणु
		/* queue alपढ़ोy initialized */
		ret_code = ICE_ERR_NOT_READY;
		जाओ init_ctrlq_निकास;
	पूर्ण

	/* verअगरy input क्रम valid configuration */
	अगर (!cq->num_sq_entries || !cq->sq_buf_size) अणु
		ret_code = ICE_ERR_CFG;
		जाओ init_ctrlq_निकास;
	पूर्ण

	cq->sq.next_to_use = 0;
	cq->sq.next_to_clean = 0;

	/* allocate the ring memory */
	ret_code = ice_alloc_ctrlq_sq_ring(hw, cq);
	अगर (ret_code)
		जाओ init_ctrlq_निकास;

	/* allocate buffers in the rings */
	ret_code = ice_alloc_sq_bufs(hw, cq);
	अगर (ret_code)
		जाओ init_ctrlq_मुक्त_rings;

	/* initialize base रेजिस्टरs */
	ret_code = ice_cfg_sq_regs(hw, cq);
	अगर (ret_code)
		जाओ init_ctrlq_मुक्त_rings;

	/* success! */
	cq->sq.count = cq->num_sq_entries;
	जाओ init_ctrlq_निकास;

init_ctrlq_मुक्त_rings:
	ICE_FREE_CQ_BUFS(hw, cq, sq);
	ice_मुक्त_cq_ring(hw, &cq->sq);

init_ctrlq_निकास:
	वापस ret_code;
पूर्ण

/**
 * ice_init_rq - initialize ARQ
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @cq: poपूर्णांकer to the specअगरic Control queue
 *
 * The मुख्य initialization routine क्रम the Admin Receive (Event) Queue.
 * Prior to calling this function, the driver *MUST* set the following fields
 * in the cq->काष्ठाure:
 *     - cq->num_rq_entries
 *     - cq->rq_buf_size
 *
 * Do *NOT* hold the lock when calling this as the memory allocation routines
 * called are not going to be atomic context safe
 */
अटल क्रमागत ice_status ice_init_rq(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq)
अणु
	क्रमागत ice_status ret_code;

	अगर (cq->rq.count > 0) अणु
		/* queue alपढ़ोy initialized */
		ret_code = ICE_ERR_NOT_READY;
		जाओ init_ctrlq_निकास;
	पूर्ण

	/* verअगरy input क्रम valid configuration */
	अगर (!cq->num_rq_entries || !cq->rq_buf_size) अणु
		ret_code = ICE_ERR_CFG;
		जाओ init_ctrlq_निकास;
	पूर्ण

	cq->rq.next_to_use = 0;
	cq->rq.next_to_clean = 0;

	/* allocate the ring memory */
	ret_code = ice_alloc_ctrlq_rq_ring(hw, cq);
	अगर (ret_code)
		जाओ init_ctrlq_निकास;

	/* allocate buffers in the rings */
	ret_code = ice_alloc_rq_bufs(hw, cq);
	अगर (ret_code)
		जाओ init_ctrlq_मुक्त_rings;

	/* initialize base रेजिस्टरs */
	ret_code = ice_cfg_rq_regs(hw, cq);
	अगर (ret_code)
		जाओ init_ctrlq_मुक्त_rings;

	/* success! */
	cq->rq.count = cq->num_rq_entries;
	जाओ init_ctrlq_निकास;

init_ctrlq_मुक्त_rings:
	ICE_FREE_CQ_BUFS(hw, cq, rq);
	ice_मुक्त_cq_ring(hw, &cq->rq);

init_ctrlq_निकास:
	वापस ret_code;
पूर्ण

/**
 * ice_shutकरोwn_sq - shutकरोwn the Control ATQ
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @cq: poपूर्णांकer to the specअगरic Control queue
 *
 * The मुख्य shutकरोwn routine क्रम the Control Transmit Queue
 */
अटल क्रमागत ice_status
ice_shutकरोwn_sq(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq)
अणु
	क्रमागत ice_status ret_code = 0;

	mutex_lock(&cq->sq_lock);

	अगर (!cq->sq.count) अणु
		ret_code = ICE_ERR_NOT_READY;
		जाओ shutकरोwn_sq_out;
	पूर्ण

	/* Stop firmware AdminQ processing */
	wr32(hw, cq->sq.head, 0);
	wr32(hw, cq->sq.tail, 0);
	wr32(hw, cq->sq.len, 0);
	wr32(hw, cq->sq.bal, 0);
	wr32(hw, cq->sq.bah, 0);

	cq->sq.count = 0;	/* to indicate uninitialized queue */

	/* मुक्त ring buffers and the ring itself */
	ICE_FREE_CQ_BUFS(hw, cq, sq);
	ice_मुक्त_cq_ring(hw, &cq->sq);

shutकरोwn_sq_out:
	mutex_unlock(&cq->sq_lock);
	वापस ret_code;
पूर्ण

/**
 * ice_aq_ver_check - Check the reported AQ API version.
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * Checks अगर the driver should load on a given AQ API version.
 *
 * Return: 'true' iff the driver should attempt to load. 'false' otherwise.
 */
अटल bool ice_aq_ver_check(काष्ठा ice_hw *hw)
अणु
	अगर (hw->api_maj_ver > EXP_FW_API_VER_MAJOR) अणु
		/* Major API version is newer than expected, करोn't load */
		dev_warn(ice_hw_to_dev(hw),
			 "The driver for the device stopped because the NVM image is newer than expected. You must install the most recent version of the network driver.\n");
		वापस false;
	पूर्ण अन्यथा अगर (hw->api_maj_ver == EXP_FW_API_VER_MAJOR) अणु
		अगर (hw->api_min_ver > (EXP_FW_API_VER_MINOR + 2))
			dev_info(ice_hw_to_dev(hw),
				 "The driver for the device detected a newer version of the NVM image than expected. Please install the most recent version of the network driver.\n");
		अन्यथा अगर ((hw->api_min_ver + 2) < EXP_FW_API_VER_MINOR)
			dev_info(ice_hw_to_dev(hw),
				 "The driver for the device detected an older version of the NVM image than expected. Please update the NVM image.\n");
	पूर्ण अन्यथा अणु
		/* Major API version is older than expected, log a warning */
		dev_info(ice_hw_to_dev(hw),
			 "The driver for the device detected an older version of the NVM image than expected. Please update the NVM image.\n");
	पूर्ण
	वापस true;
पूर्ण

/**
 * ice_shutकरोwn_rq - shutकरोwn Control ARQ
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @cq: poपूर्णांकer to the specअगरic Control queue
 *
 * The मुख्य shutकरोwn routine क्रम the Control Receive Queue
 */
अटल क्रमागत ice_status
ice_shutकरोwn_rq(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq)
अणु
	क्रमागत ice_status ret_code = 0;

	mutex_lock(&cq->rq_lock);

	अगर (!cq->rq.count) अणु
		ret_code = ICE_ERR_NOT_READY;
		जाओ shutकरोwn_rq_out;
	पूर्ण

	/* Stop Control Queue processing */
	wr32(hw, cq->rq.head, 0);
	wr32(hw, cq->rq.tail, 0);
	wr32(hw, cq->rq.len, 0);
	wr32(hw, cq->rq.bal, 0);
	wr32(hw, cq->rq.bah, 0);

	/* set rq.count to 0 to indicate uninitialized queue */
	cq->rq.count = 0;

	/* मुक्त ring buffers and the ring itself */
	ICE_FREE_CQ_BUFS(hw, cq, rq);
	ice_मुक्त_cq_ring(hw, &cq->rq);

shutकरोwn_rq_out:
	mutex_unlock(&cq->rq_lock);
	वापस ret_code;
पूर्ण

/**
 * ice_init_check_adminq - Check version क्रम Admin Queue to know अगर its alive
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 */
अटल क्रमागत ice_status ice_init_check_adminq(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_ctl_q_info *cq = &hw->adminq;
	क्रमागत ice_status status;

	status = ice_aq_get_fw_ver(hw, शून्य);
	अगर (status)
		जाओ init_ctrlq_मुक्त_rq;

	अगर (!ice_aq_ver_check(hw)) अणु
		status = ICE_ERR_FW_API_VER;
		जाओ init_ctrlq_मुक्त_rq;
	पूर्ण

	वापस 0;

init_ctrlq_मुक्त_rq:
	ice_shutकरोwn_rq(hw, cq);
	ice_shutकरोwn_sq(hw, cq);
	वापस status;
पूर्ण

/**
 * ice_init_ctrlq - मुख्य initialization routine क्रम any control Queue
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @q_type: specअगरic Control queue type
 *
 * Prior to calling this function, the driver *MUST* set the following fields
 * in the cq->काष्ठाure:
 *     - cq->num_sq_entries
 *     - cq->num_rq_entries
 *     - cq->rq_buf_size
 *     - cq->sq_buf_size
 *
 * NOTE: this function करोes not initialize the controlq locks
 */
अटल क्रमागत ice_status ice_init_ctrlq(काष्ठा ice_hw *hw, क्रमागत ice_ctl_q q_type)
अणु
	काष्ठा ice_ctl_q_info *cq;
	क्रमागत ice_status ret_code;

	चयन (q_type) अणु
	हाल ICE_CTL_Q_ADMIN:
		ice_adminq_init_regs(hw);
		cq = &hw->adminq;
		अवरोध;
	हाल ICE_CTL_Q_MAILBOX:
		ice_mailbox_init_regs(hw);
		cq = &hw->mailboxq;
		अवरोध;
	शेष:
		वापस ICE_ERR_PARAM;
	पूर्ण
	cq->qtype = q_type;

	/* verअगरy input क्रम valid configuration */
	अगर (!cq->num_rq_entries || !cq->num_sq_entries ||
	    !cq->rq_buf_size || !cq->sq_buf_size) अणु
		वापस ICE_ERR_CFG;
	पूर्ण

	/* setup SQ command ग_लिखो back समयout */
	cq->sq_cmd_समयout = ICE_CTL_Q_SQ_CMD_TIMEOUT;

	/* allocate the ATQ */
	ret_code = ice_init_sq(hw, cq);
	अगर (ret_code)
		वापस ret_code;

	/* allocate the ARQ */
	ret_code = ice_init_rq(hw, cq);
	अगर (ret_code)
		जाओ init_ctrlq_मुक्त_sq;

	/* success! */
	वापस 0;

init_ctrlq_मुक्त_sq:
	ice_shutकरोwn_sq(hw, cq);
	वापस ret_code;
पूर्ण

/**
 * ice_shutकरोwn_ctrlq - shutकरोwn routine क्रम any control queue
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @q_type: specअगरic Control queue type
 *
 * NOTE: this function करोes not destroy the control queue locks.
 */
अटल व्योम ice_shutकरोwn_ctrlq(काष्ठा ice_hw *hw, क्रमागत ice_ctl_q q_type)
अणु
	काष्ठा ice_ctl_q_info *cq;

	चयन (q_type) अणु
	हाल ICE_CTL_Q_ADMIN:
		cq = &hw->adminq;
		अगर (ice_check_sq_alive(hw, cq))
			ice_aq_q_shutकरोwn(hw, true);
		अवरोध;
	हाल ICE_CTL_Q_MAILBOX:
		cq = &hw->mailboxq;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	ice_shutकरोwn_sq(hw, cq);
	ice_shutकरोwn_rq(hw, cq);
पूर्ण

/**
 * ice_shutकरोwn_all_ctrlq - shutकरोwn routine क्रम all control queues
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * NOTE: this function करोes not destroy the control queue locks. The driver
 * may call this at runसमय to shutकरोwn and later restart control queues, such
 * as in response to a reset event.
 */
व्योम ice_shutकरोwn_all_ctrlq(काष्ठा ice_hw *hw)
अणु
	/* Shutकरोwn FW admin queue */
	ice_shutकरोwn_ctrlq(hw, ICE_CTL_Q_ADMIN);
	/* Shutकरोwn PF-VF Mailbox */
	ice_shutकरोwn_ctrlq(hw, ICE_CTL_Q_MAILBOX);
पूर्ण

/**
 * ice_init_all_ctrlq - मुख्य initialization routine क्रम all control queues
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * Prior to calling this function, the driver MUST* set the following fields
 * in the cq->काष्ठाure क्रम all control queues:
 *     - cq->num_sq_entries
 *     - cq->num_rq_entries
 *     - cq->rq_buf_size
 *     - cq->sq_buf_size
 *
 * NOTE: this function करोes not initialize the controlq locks.
 */
क्रमागत ice_status ice_init_all_ctrlq(काष्ठा ice_hw *hw)
अणु
	क्रमागत ice_status status;
	u32 retry = 0;

	/* Init FW admin queue */
	करो अणु
		status = ice_init_ctrlq(hw, ICE_CTL_Q_ADMIN);
		अगर (status)
			वापस status;

		status = ice_init_check_adminq(hw);
		अगर (status != ICE_ERR_AQ_FW_CRITICAL)
			अवरोध;

		ice_debug(hw, ICE_DBG_AQ_MSG, "Retry Admin Queue init due to FW critical error\n");
		ice_shutकरोwn_ctrlq(hw, ICE_CTL_Q_ADMIN);
		msleep(ICE_CTL_Q_ADMIN_INIT_MSEC);
	पूर्ण जबतक (retry++ < ICE_CTL_Q_ADMIN_INIT_TIMEOUT);

	अगर (status)
		वापस status;
	/* Init Mailbox queue */
	वापस ice_init_ctrlq(hw, ICE_CTL_Q_MAILBOX);
पूर्ण

/**
 * ice_init_ctrlq_locks - Initialize locks क्रम a control queue
 * @cq: poपूर्णांकer to the control queue
 *
 * Initializes the send and receive queue locks क्रम a given control queue.
 */
अटल व्योम ice_init_ctrlq_locks(काष्ठा ice_ctl_q_info *cq)
अणु
	mutex_init(&cq->sq_lock);
	mutex_init(&cq->rq_lock);
पूर्ण

/**
 * ice_create_all_ctrlq - मुख्य initialization routine क्रम all control queues
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * Prior to calling this function, the driver *MUST* set the following fields
 * in the cq->काष्ठाure क्रम all control queues:
 *     - cq->num_sq_entries
 *     - cq->num_rq_entries
 *     - cq->rq_buf_size
 *     - cq->sq_buf_size
 *
 * This function creates all the control queue locks and then calls
 * ice_init_all_ctrlq. It should be called once during driver load. If the
 * driver needs to re-initialize control queues at run समय it should call
 * ice_init_all_ctrlq instead.
 */
क्रमागत ice_status ice_create_all_ctrlq(काष्ठा ice_hw *hw)
अणु
	ice_init_ctrlq_locks(&hw->adminq);
	ice_init_ctrlq_locks(&hw->mailboxq);

	वापस ice_init_all_ctrlq(hw);
पूर्ण

/**
 * ice_destroy_ctrlq_locks - Destroy locks क्रम a control queue
 * @cq: poपूर्णांकer to the control queue
 *
 * Destroys the send and receive queue locks क्रम a given control queue.
 */
अटल व्योम ice_destroy_ctrlq_locks(काष्ठा ice_ctl_q_info *cq)
अणु
	mutex_destroy(&cq->sq_lock);
	mutex_destroy(&cq->rq_lock);
पूर्ण

/**
 * ice_destroy_all_ctrlq - निकास routine क्रम all control queues
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * This function shuts करोwn all the control queues and then destroys the
 * control queue locks. It should be called once during driver unload. The
 * driver should call ice_shutकरोwn_all_ctrlq अगर it needs to shut करोwn and
 * reinitialize control queues, such as in response to a reset event.
 */
व्योम ice_destroy_all_ctrlq(काष्ठा ice_hw *hw)
अणु
	/* shut करोwn all the control queues first */
	ice_shutकरोwn_all_ctrlq(hw);

	ice_destroy_ctrlq_locks(&hw->adminq);
	ice_destroy_ctrlq_locks(&hw->mailboxq);
पूर्ण

/**
 * ice_clean_sq - cleans Admin send queue (ATQ)
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @cq: poपूर्णांकer to the specअगरic Control queue
 *
 * वापसs the number of मुक्त desc
 */
अटल u16 ice_clean_sq(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq)
अणु
	काष्ठा ice_ctl_q_ring *sq = &cq->sq;
	u16 ntc = sq->next_to_clean;
	काष्ठा ice_sq_cd *details;
	काष्ठा ice_aq_desc *desc;

	desc = ICE_CTL_Q_DESC(*sq, ntc);
	details = ICE_CTL_Q_DETAILS(*sq, ntc);

	जबतक (rd32(hw, cq->sq.head) != ntc) अणु
		ice_debug(hw, ICE_DBG_AQ_MSG, "ntc %d head %d.\n", ntc, rd32(hw, cq->sq.head));
		स_रखो(desc, 0, माप(*desc));
		स_रखो(details, 0, माप(*details));
		ntc++;
		अगर (ntc == sq->count)
			ntc = 0;
		desc = ICE_CTL_Q_DESC(*sq, ntc);
		details = ICE_CTL_Q_DETAILS(*sq, ntc);
	पूर्ण

	sq->next_to_clean = ntc;

	वापस ICE_CTL_Q_DESC_UNUSED(sq);
पूर्ण

/**
 * ice_debug_cq
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @desc: poपूर्णांकer to control queue descriptor
 * @buf: poपूर्णांकer to command buffer
 * @buf_len: max length of buf
 *
 * Dumps debug log about control command with descriptor contents.
 */
अटल व्योम ice_debug_cq(काष्ठा ice_hw *hw, व्योम *desc, व्योम *buf, u16 buf_len)
अणु
	काष्ठा ice_aq_desc *cq_desc = desc;
	u16 len;

	अगर (!IS_ENABLED(CONFIG_DYNAMIC_DEBUG) &&
	    !((ICE_DBG_AQ_DESC | ICE_DBG_AQ_DESC_BUF) & hw->debug_mask))
		वापस;

	अगर (!desc)
		वापस;

	len = le16_to_cpu(cq_desc->datalen);

	ice_debug(hw, ICE_DBG_AQ_DESC, "CQ CMD: opcode 0x%04X, flags 0x%04X, datalen 0x%04X, retval 0x%04X\n",
		  le16_to_cpu(cq_desc->opcode),
		  le16_to_cpu(cq_desc->flags),
		  le16_to_cpu(cq_desc->datalen), le16_to_cpu(cq_desc->retval));
	ice_debug(hw, ICE_DBG_AQ_DESC, "\tcookie (h,l) 0x%08X 0x%08X\n",
		  le32_to_cpu(cq_desc->cookie_high),
		  le32_to_cpu(cq_desc->cookie_low));
	ice_debug(hw, ICE_DBG_AQ_DESC, "\tparam (0,1)  0x%08X 0x%08X\n",
		  le32_to_cpu(cq_desc->params.generic.param0),
		  le32_to_cpu(cq_desc->params.generic.param1));
	ice_debug(hw, ICE_DBG_AQ_DESC, "\taddr (h,l)   0x%08X 0x%08X\n",
		  le32_to_cpu(cq_desc->params.generic.addr_high),
		  le32_to_cpu(cq_desc->params.generic.addr_low));
	अगर (buf && cq_desc->datalen != 0) अणु
		ice_debug(hw, ICE_DBG_AQ_DESC_BUF, "Buffer:\n");
		अगर (buf_len < len)
			len = buf_len;

		ice_debug_array(hw, ICE_DBG_AQ_DESC_BUF, 16, 1, buf, len);
	पूर्ण
पूर्ण

/**
 * ice_sq_करोne - check अगर FW has processed the Admin Send Queue (ATQ)
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @cq: poपूर्णांकer to the specअगरic Control queue
 *
 * Returns true अगर the firmware has processed all descriptors on the
 * admin send queue. Returns false अगर there are still requests pending.
 */
अटल bool ice_sq_करोne(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq)
अणु
	/* AQ designers suggest use of head क्रम better
	 * timing reliability than DD bit
	 */
	वापस rd32(hw, cq->sq.head) == cq->sq.next_to_use;
पूर्ण

/**
 * ice_sq_send_cmd - send command to Control Queue (ATQ)
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @cq: poपूर्णांकer to the specअगरic Control queue
 * @desc: prefilled descriptor describing the command
 * @buf: buffer to use क्रम indirect commands (or शून्य क्रम direct commands)
 * @buf_size: size of buffer क्रम indirect commands (or 0 क्रम direct commands)
 * @cd: poपूर्णांकer to command details काष्ठाure
 *
 * This is the मुख्य send command routine क्रम the ATQ. It runs the queue,
 * cleans the queue, etc.
 */
क्रमागत ice_status
ice_sq_send_cmd(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq,
		काष्ठा ice_aq_desc *desc, व्योम *buf, u16 buf_size,
		काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_dma_mem *dma_buf = शून्य;
	काष्ठा ice_aq_desc *desc_on_ring;
	bool cmd_completed = false;
	क्रमागत ice_status status = 0;
	काष्ठा ice_sq_cd *details;
	u32 total_delay = 0;
	u16 retval = 0;
	u32 val = 0;

	/* अगर reset is in progress वापस a soft error */
	अगर (hw->reset_ongoing)
		वापस ICE_ERR_RESET_ONGOING;
	mutex_lock(&cq->sq_lock);

	cq->sq_last_status = ICE_AQ_RC_OK;

	अगर (!cq->sq.count) अणु
		ice_debug(hw, ICE_DBG_AQ_MSG, "Control Send queue not initialized.\n");
		status = ICE_ERR_AQ_EMPTY;
		जाओ sq_send_command_error;
	पूर्ण

	अगर ((buf && !buf_size) || (!buf && buf_size)) अणु
		status = ICE_ERR_PARAM;
		जाओ sq_send_command_error;
	पूर्ण

	अगर (buf) अणु
		अगर (buf_size > cq->sq_buf_size) अणु
			ice_debug(hw, ICE_DBG_AQ_MSG, "Invalid buffer size for Control Send queue: %d.\n",
				  buf_size);
			status = ICE_ERR_INVAL_SIZE;
			जाओ sq_send_command_error;
		पूर्ण

		desc->flags |= cpu_to_le16(ICE_AQ_FLAG_BUF);
		अगर (buf_size > ICE_AQ_LG_BUF)
			desc->flags |= cpu_to_le16(ICE_AQ_FLAG_LB);
	पूर्ण

	val = rd32(hw, cq->sq.head);
	अगर (val >= cq->num_sq_entries) अणु
		ice_debug(hw, ICE_DBG_AQ_MSG, "head overrun at %d in the Control Send Queue ring\n",
			  val);
		status = ICE_ERR_AQ_EMPTY;
		जाओ sq_send_command_error;
	पूर्ण

	details = ICE_CTL_Q_DETAILS(cq->sq, cq->sq.next_to_use);
	अगर (cd)
		*details = *cd;
	अन्यथा
		स_रखो(details, 0, माप(*details));

	/* Call clean and check queue available function to reclaim the
	 * descriptors that were processed by FW/MBX; the function वापसs the
	 * number of desc available. The clean function called here could be
	 * called in a separate thपढ़ो in हाल of asynchronous completions.
	 */
	अगर (ice_clean_sq(hw, cq) == 0) अणु
		ice_debug(hw, ICE_DBG_AQ_MSG, "Error: Control Send Queue is full.\n");
		status = ICE_ERR_AQ_FULL;
		जाओ sq_send_command_error;
	पूर्ण

	/* initialize the temp desc poपूर्णांकer with the right desc */
	desc_on_ring = ICE_CTL_Q_DESC(cq->sq, cq->sq.next_to_use);

	/* अगर the desc is available copy the temp desc to the right place */
	स_नकल(desc_on_ring, desc, माप(*desc_on_ring));

	/* अगर buf is not शून्य assume indirect command */
	अगर (buf) अणु
		dma_buf = &cq->sq.r.sq_bi[cq->sq.next_to_use];
		/* copy the user buf पूर्णांकo the respective DMA buf */
		स_नकल(dma_buf->va, buf, buf_size);
		desc_on_ring->datalen = cpu_to_le16(buf_size);

		/* Update the address values in the desc with the pa value
		 * क्रम respective buffer
		 */
		desc_on_ring->params.generic.addr_high =
			cpu_to_le32(upper_32_bits(dma_buf->pa));
		desc_on_ring->params.generic.addr_low =
			cpu_to_le32(lower_32_bits(dma_buf->pa));
	पूर्ण

	/* Debug desc and buffer */
	ice_debug(hw, ICE_DBG_AQ_DESC, "ATQ: Control Send queue desc and buffer:\n");

	ice_debug_cq(hw, (व्योम *)desc_on_ring, buf, buf_size);

	(cq->sq.next_to_use)++;
	अगर (cq->sq.next_to_use == cq->sq.count)
		cq->sq.next_to_use = 0;
	wr32(hw, cq->sq.tail, cq->sq.next_to_use);

	करो अणु
		अगर (ice_sq_करोne(hw, cq))
			अवरोध;

		udelay(ICE_CTL_Q_SQ_CMD_USEC);
		total_delay++;
	पूर्ण जबतक (total_delay < cq->sq_cmd_समयout);

	/* अगर पढ़ोy, copy the desc back to temp */
	अगर (ice_sq_करोne(hw, cq)) अणु
		स_नकल(desc, desc_on_ring, माप(*desc));
		अगर (buf) अणु
			/* get वापसed length to copy */
			u16 copy_size = le16_to_cpu(desc->datalen);

			अगर (copy_size > buf_size) अणु
				ice_debug(hw, ICE_DBG_AQ_MSG, "Return len %d > than buf len %d\n",
					  copy_size, buf_size);
				status = ICE_ERR_AQ_ERROR;
			पूर्ण अन्यथा अणु
				स_नकल(buf, dma_buf->va, copy_size);
			पूर्ण
		पूर्ण
		retval = le16_to_cpu(desc->retval);
		अगर (retval) अणु
			ice_debug(hw, ICE_DBG_AQ_MSG, "Control Send Queue command 0x%04X completed with error 0x%X\n",
				  le16_to_cpu(desc->opcode),
				  retval);

			/* strip off FW पूर्णांकernal code */
			retval &= 0xff;
		पूर्ण
		cmd_completed = true;
		अगर (!status && retval != ICE_AQ_RC_OK)
			status = ICE_ERR_AQ_ERROR;
		cq->sq_last_status = (क्रमागत ice_aq_err)retval;
	पूर्ण

	ice_debug(hw, ICE_DBG_AQ_MSG, "ATQ: desc and buffer writeback:\n");

	ice_debug_cq(hw, (व्योम *)desc, buf, buf_size);

	/* save ग_लिखोback AQ अगर requested */
	अगर (details->wb_desc)
		स_नकल(details->wb_desc, desc_on_ring,
		       माप(*details->wb_desc));

	/* update the error अगर समय out occurred */
	अगर (!cmd_completed) अणु
		अगर (rd32(hw, cq->rq.len) & cq->rq.len_crit_mask ||
		    rd32(hw, cq->sq.len) & cq->sq.len_crit_mask) अणु
			ice_debug(hw, ICE_DBG_AQ_MSG, "Critical FW error.\n");
			status = ICE_ERR_AQ_FW_CRITICAL;
		पूर्ण अन्यथा अणु
			ice_debug(hw, ICE_DBG_AQ_MSG, "Control Send Queue Writeback timeout.\n");
			status = ICE_ERR_AQ_TIMEOUT;
		पूर्ण
	पूर्ण

sq_send_command_error:
	mutex_unlock(&cq->sq_lock);
	वापस status;
पूर्ण

/**
 * ice_fill_dflt_direct_cmd_desc - AQ descriptor helper function
 * @desc: poपूर्णांकer to the temp descriptor (non DMA mem)
 * @opcode: the opcode can be used to decide which flags to turn off or on
 *
 * Fill the desc with शेष values
 */
व्योम ice_fill_dflt_direct_cmd_desc(काष्ठा ice_aq_desc *desc, u16 opcode)
अणु
	/* zero out the desc */
	स_रखो(desc, 0, माप(*desc));
	desc->opcode = cpu_to_le16(opcode);
	desc->flags = cpu_to_le16(ICE_AQ_FLAG_SI);
पूर्ण

/**
 * ice_clean_rq_elem
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @cq: poपूर्णांकer to the specअगरic Control queue
 * @e: event info from the receive descriptor, includes any buffers
 * @pending: number of events that could be left to process
 *
 * This function cleans one Admin Receive Queue element and वापसs
 * the contents through e. It can also वापस how many events are
 * left to process through 'pending'.
 */
क्रमागत ice_status
ice_clean_rq_elem(काष्ठा ice_hw *hw, काष्ठा ice_ctl_q_info *cq,
		  काष्ठा ice_rq_event_info *e, u16 *pending)
अणु
	u16 ntc = cq->rq.next_to_clean;
	क्रमागत ice_aq_err rq_last_status;
	क्रमागत ice_status ret_code = 0;
	काष्ठा ice_aq_desc *desc;
	काष्ठा ice_dma_mem *bi;
	u16 desc_idx;
	u16 datalen;
	u16 flags;
	u16 ntu;

	/* pre-clean the event info */
	स_रखो(&e->desc, 0, माप(e->desc));

	/* take the lock beक्रमe we start messing with the ring */
	mutex_lock(&cq->rq_lock);

	अगर (!cq->rq.count) अणु
		ice_debug(hw, ICE_DBG_AQ_MSG, "Control Receive queue not initialized.\n");
		ret_code = ICE_ERR_AQ_EMPTY;
		जाओ clean_rq_elem_err;
	पूर्ण

	/* set next_to_use to head */
	ntu = (u16)(rd32(hw, cq->rq.head) & cq->rq.head_mask);

	अगर (ntu == ntc) अणु
		/* nothing to करो - shouldn't need to update ring's values */
		ret_code = ICE_ERR_AQ_NO_WORK;
		जाओ clean_rq_elem_out;
	पूर्ण

	/* now clean the next descriptor */
	desc = ICE_CTL_Q_DESC(cq->rq, ntc);
	desc_idx = ntc;

	rq_last_status = (क्रमागत ice_aq_err)le16_to_cpu(desc->retval);
	flags = le16_to_cpu(desc->flags);
	अगर (flags & ICE_AQ_FLAG_ERR) अणु
		ret_code = ICE_ERR_AQ_ERROR;
		ice_debug(hw, ICE_DBG_AQ_MSG, "Control Receive Queue Event 0x%04X received with error 0x%X\n",
			  le16_to_cpu(desc->opcode), rq_last_status);
	पूर्ण
	स_नकल(&e->desc, desc, माप(e->desc));
	datalen = le16_to_cpu(desc->datalen);
	e->msg_len = min_t(u16, datalen, e->buf_len);
	अगर (e->msg_buf && e->msg_len)
		स_नकल(e->msg_buf, cq->rq.r.rq_bi[desc_idx].va, e->msg_len);

	ice_debug(hw, ICE_DBG_AQ_DESC, "ARQ: desc and buffer:\n");

	ice_debug_cq(hw, (व्योम *)desc, e->msg_buf, cq->rq_buf_size);

	/* Restore the original datalen and buffer address in the desc,
	 * FW updates datalen to indicate the event message size
	 */
	bi = &cq->rq.r.rq_bi[ntc];
	स_रखो(desc, 0, माप(*desc));

	desc->flags = cpu_to_le16(ICE_AQ_FLAG_BUF);
	अगर (cq->rq_buf_size > ICE_AQ_LG_BUF)
		desc->flags |= cpu_to_le16(ICE_AQ_FLAG_LB);
	desc->datalen = cpu_to_le16(bi->size);
	desc->params.generic.addr_high = cpu_to_le32(upper_32_bits(bi->pa));
	desc->params.generic.addr_low = cpu_to_le32(lower_32_bits(bi->pa));

	/* set tail = the last cleaned desc index. */
	wr32(hw, cq->rq.tail, ntc);
	/* ntc is updated to tail + 1 */
	ntc++;
	अगर (ntc == cq->num_rq_entries)
		ntc = 0;
	cq->rq.next_to_clean = ntc;
	cq->rq.next_to_use = ntu;

clean_rq_elem_out:
	/* Set pending अगर needed, unlock and वापस */
	अगर (pending) अणु
		/* re-पढ़ो HW head to calculate actual pending messages */
		ntu = (u16)(rd32(hw, cq->rq.head) & cq->rq.head_mask);
		*pending = (u16)((ntc > ntu ? cq->rq.count : 0) + (ntu - ntc));
	पूर्ण
clean_rq_elem_err:
	mutex_unlock(&cq->rq_lock);

	वापस ret_code;
पूर्ण
