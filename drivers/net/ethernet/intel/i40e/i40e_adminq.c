<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#समावेश "i40e_status.h"
#समावेश "i40e_type.h"
#समावेश "i40e_register.h"
#समावेश "i40e_adminq.h"
#समावेश "i40e_prototype.h"

अटल व्योम i40e_resume_aq(काष्ठा i40e_hw *hw);

/**
 *  i40e_adminq_init_regs - Initialize AdminQ रेजिस्टरs
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 *  This assumes the alloc_asq and alloc_arq functions have alपढ़ोy been called
 **/
अटल व्योम i40e_adminq_init_regs(काष्ठा i40e_hw *hw)
अणु
	/* set head and tail रेजिस्टरs in our local काष्ठा */
	अगर (i40e_is_vf(hw)) अणु
		hw->aq.asq.tail = I40E_VF_ATQT1;
		hw->aq.asq.head = I40E_VF_ATQH1;
		hw->aq.asq.len  = I40E_VF_ATQLEN1;
		hw->aq.asq.bal  = I40E_VF_ATQBAL1;
		hw->aq.asq.bah  = I40E_VF_ATQBAH1;
		hw->aq.arq.tail = I40E_VF_ARQT1;
		hw->aq.arq.head = I40E_VF_ARQH1;
		hw->aq.arq.len  = I40E_VF_ARQLEN1;
		hw->aq.arq.bal  = I40E_VF_ARQBAL1;
		hw->aq.arq.bah  = I40E_VF_ARQBAH1;
	पूर्ण अन्यथा अणु
		hw->aq.asq.tail = I40E_PF_ATQT;
		hw->aq.asq.head = I40E_PF_ATQH;
		hw->aq.asq.len  = I40E_PF_ATQLEN;
		hw->aq.asq.bal  = I40E_PF_ATQBAL;
		hw->aq.asq.bah  = I40E_PF_ATQBAH;
		hw->aq.arq.tail = I40E_PF_ARQT;
		hw->aq.arq.head = I40E_PF_ARQH;
		hw->aq.arq.len  = I40E_PF_ARQLEN;
		hw->aq.arq.bal  = I40E_PF_ARQBAL;
		hw->aq.arq.bah  = I40E_PF_ARQBAH;
	पूर्ण
पूर्ण

/**
 *  i40e_alloc_adminq_asq_ring - Allocate Admin Queue send rings
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 **/
अटल i40e_status i40e_alloc_adminq_asq_ring(काष्ठा i40e_hw *hw)
अणु
	i40e_status ret_code;

	ret_code = i40e_allocate_dma_mem(hw, &hw->aq.asq.desc_buf,
					 i40e_mem_atq_ring,
					 (hw->aq.num_asq_entries *
					 माप(काष्ठा i40e_aq_desc)),
					 I40E_ADMINQ_DESC_ALIGNMENT);
	अगर (ret_code)
		वापस ret_code;

	ret_code = i40e_allocate_virt_mem(hw, &hw->aq.asq.cmd_buf,
					  (hw->aq.num_asq_entries *
					  माप(काष्ठा i40e_asq_cmd_details)));
	अगर (ret_code) अणु
		i40e_मुक्त_dma_mem(hw, &hw->aq.asq.desc_buf);
		वापस ret_code;
	पूर्ण

	वापस ret_code;
पूर्ण

/**
 *  i40e_alloc_adminq_arq_ring - Allocate Admin Queue receive rings
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 **/
अटल i40e_status i40e_alloc_adminq_arq_ring(काष्ठा i40e_hw *hw)
अणु
	i40e_status ret_code;

	ret_code = i40e_allocate_dma_mem(hw, &hw->aq.arq.desc_buf,
					 i40e_mem_arq_ring,
					 (hw->aq.num_arq_entries *
					 माप(काष्ठा i40e_aq_desc)),
					 I40E_ADMINQ_DESC_ALIGNMENT);

	वापस ret_code;
पूर्ण

/**
 *  i40e_मुक्त_adminq_asq - Free Admin Queue send rings
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 *  This assumes the posted send buffers have alपढ़ोy been cleaned
 *  and de-allocated
 **/
अटल व्योम i40e_मुक्त_adminq_asq(काष्ठा i40e_hw *hw)
अणु
	i40e_मुक्त_dma_mem(hw, &hw->aq.asq.desc_buf);
पूर्ण

/**
 *  i40e_मुक्त_adminq_arq - Free Admin Queue receive rings
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 *  This assumes the posted receive buffers have alपढ़ोy been cleaned
 *  and de-allocated
 **/
अटल व्योम i40e_मुक्त_adminq_arq(काष्ठा i40e_hw *hw)
अणु
	i40e_मुक्त_dma_mem(hw, &hw->aq.arq.desc_buf);
पूर्ण

/**
 *  i40e_alloc_arq_bufs - Allocate pre-posted buffers क्रम the receive queue
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 **/
अटल i40e_status i40e_alloc_arq_bufs(काष्ठा i40e_hw *hw)
अणु
	i40e_status ret_code;
	काष्ठा i40e_aq_desc *desc;
	काष्ठा i40e_dma_mem *bi;
	पूर्णांक i;

	/* We'll be allocating the buffer info memory first, then we can
	 * allocate the mapped buffers क्रम the event processing
	 */

	/* buffer_info काष्ठाures करो not need alignment */
	ret_code = i40e_allocate_virt_mem(hw, &hw->aq.arq.dma_head,
		(hw->aq.num_arq_entries * माप(काष्ठा i40e_dma_mem)));
	अगर (ret_code)
		जाओ alloc_arq_bufs;
	hw->aq.arq.r.arq_bi = (काष्ठा i40e_dma_mem *)hw->aq.arq.dma_head.va;

	/* allocate the mapped buffers */
	क्रम (i = 0; i < hw->aq.num_arq_entries; i++) अणु
		bi = &hw->aq.arq.r.arq_bi[i];
		ret_code = i40e_allocate_dma_mem(hw, bi,
						 i40e_mem_arq_buf,
						 hw->aq.arq_buf_size,
						 I40E_ADMINQ_DESC_ALIGNMENT);
		अगर (ret_code)
			जाओ unwind_alloc_arq_bufs;

		/* now configure the descriptors क्रम use */
		desc = I40E_ADMINQ_DESC(hw->aq.arq, i);

		desc->flags = cpu_to_le16(I40E_AQ_FLAG_BUF);
		अगर (hw->aq.arq_buf_size > I40E_AQ_LARGE_BUF)
			desc->flags |= cpu_to_le16(I40E_AQ_FLAG_LB);
		desc->opcode = 0;
		/* This is in accordance with Admin queue design, there is no
		 * रेजिस्टर क्रम buffer size configuration
		 */
		desc->datalen = cpu_to_le16((u16)bi->size);
		desc->retval = 0;
		desc->cookie_high = 0;
		desc->cookie_low = 0;
		desc->params.बाह्यal.addr_high =
			cpu_to_le32(upper_32_bits(bi->pa));
		desc->params.बाह्यal.addr_low =
			cpu_to_le32(lower_32_bits(bi->pa));
		desc->params.बाह्यal.param0 = 0;
		desc->params.बाह्यal.param1 = 0;
	पूर्ण

alloc_arq_bufs:
	वापस ret_code;

unwind_alloc_arq_bufs:
	/* करोn't try to मुक्त the one that failed... */
	i--;
	क्रम (; i >= 0; i--)
		i40e_मुक्त_dma_mem(hw, &hw->aq.arq.r.arq_bi[i]);
	i40e_मुक्त_virt_mem(hw, &hw->aq.arq.dma_head);

	वापस ret_code;
पूर्ण

/**
 *  i40e_alloc_asq_bufs - Allocate empty buffer काष्ठाs क्रम the send queue
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 **/
अटल i40e_status i40e_alloc_asq_bufs(काष्ठा i40e_hw *hw)
अणु
	i40e_status ret_code;
	काष्ठा i40e_dma_mem *bi;
	पूर्णांक i;

	/* No mapped memory needed yet, just the buffer info काष्ठाures */
	ret_code = i40e_allocate_virt_mem(hw, &hw->aq.asq.dma_head,
		(hw->aq.num_asq_entries * माप(काष्ठा i40e_dma_mem)));
	अगर (ret_code)
		जाओ alloc_asq_bufs;
	hw->aq.asq.r.asq_bi = (काष्ठा i40e_dma_mem *)hw->aq.asq.dma_head.va;

	/* allocate the mapped buffers */
	क्रम (i = 0; i < hw->aq.num_asq_entries; i++) अणु
		bi = &hw->aq.asq.r.asq_bi[i];
		ret_code = i40e_allocate_dma_mem(hw, bi,
						 i40e_mem_asq_buf,
						 hw->aq.asq_buf_size,
						 I40E_ADMINQ_DESC_ALIGNMENT);
		अगर (ret_code)
			जाओ unwind_alloc_asq_bufs;
	पूर्ण
alloc_asq_bufs:
	वापस ret_code;

unwind_alloc_asq_bufs:
	/* करोn't try to मुक्त the one that failed... */
	i--;
	क्रम (; i >= 0; i--)
		i40e_मुक्त_dma_mem(hw, &hw->aq.asq.r.asq_bi[i]);
	i40e_मुक्त_virt_mem(hw, &hw->aq.asq.dma_head);

	वापस ret_code;
पूर्ण

/**
 *  i40e_मुक्त_arq_bufs - Free receive queue buffer info elements
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 **/
अटल व्योम i40e_मुक्त_arq_bufs(काष्ठा i40e_hw *hw)
अणु
	पूर्णांक i;

	/* मुक्त descriptors */
	क्रम (i = 0; i < hw->aq.num_arq_entries; i++)
		i40e_मुक्त_dma_mem(hw, &hw->aq.arq.r.arq_bi[i]);

	/* मुक्त the descriptor memory */
	i40e_मुक्त_dma_mem(hw, &hw->aq.arq.desc_buf);

	/* मुक्त the dma header */
	i40e_मुक्त_virt_mem(hw, &hw->aq.arq.dma_head);
पूर्ण

/**
 *  i40e_मुक्त_asq_bufs - Free send queue buffer info elements
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 **/
अटल व्योम i40e_मुक्त_asq_bufs(काष्ठा i40e_hw *hw)
अणु
	पूर्णांक i;

	/* only unmap अगर the address is non-शून्य */
	क्रम (i = 0; i < hw->aq.num_asq_entries; i++)
		अगर (hw->aq.asq.r.asq_bi[i].pa)
			i40e_मुक्त_dma_mem(hw, &hw->aq.asq.r.asq_bi[i]);

	/* मुक्त the buffer info list */
	i40e_मुक्त_virt_mem(hw, &hw->aq.asq.cmd_buf);

	/* मुक्त the descriptor memory */
	i40e_मुक्त_dma_mem(hw, &hw->aq.asq.desc_buf);

	/* मुक्त the dma header */
	i40e_मुक्त_virt_mem(hw, &hw->aq.asq.dma_head);
पूर्ण

/**
 *  i40e_config_asq_regs - configure ASQ रेजिस्टरs
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 *  Configure base address and length रेजिस्टरs क्रम the transmit queue
 **/
अटल i40e_status i40e_config_asq_regs(काष्ठा i40e_hw *hw)
अणु
	i40e_status ret_code = 0;
	u32 reg = 0;

	/* Clear Head and Tail */
	wr32(hw, hw->aq.asq.head, 0);
	wr32(hw, hw->aq.asq.tail, 0);

	/* set starting poपूर्णांक */
	wr32(hw, hw->aq.asq.len, (hw->aq.num_asq_entries |
				  I40E_PF_ATQLEN_ATQENABLE_MASK));
	wr32(hw, hw->aq.asq.bal, lower_32_bits(hw->aq.asq.desc_buf.pa));
	wr32(hw, hw->aq.asq.bah, upper_32_bits(hw->aq.asq.desc_buf.pa));

	/* Check one रेजिस्टर to verअगरy that config was applied */
	reg = rd32(hw, hw->aq.asq.bal);
	अगर (reg != lower_32_bits(hw->aq.asq.desc_buf.pa))
		ret_code = I40E_ERR_ADMIN_QUEUE_ERROR;

	वापस ret_code;
पूर्ण

/**
 *  i40e_config_arq_regs - ARQ रेजिस्टर configuration
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * Configure base address and length रेजिस्टरs क्रम the receive (event queue)
 **/
अटल i40e_status i40e_config_arq_regs(काष्ठा i40e_hw *hw)
अणु
	i40e_status ret_code = 0;
	u32 reg = 0;

	/* Clear Head and Tail */
	wr32(hw, hw->aq.arq.head, 0);
	wr32(hw, hw->aq.arq.tail, 0);

	/* set starting poपूर्णांक */
	wr32(hw, hw->aq.arq.len, (hw->aq.num_arq_entries |
				  I40E_PF_ARQLEN_ARQENABLE_MASK));
	wr32(hw, hw->aq.arq.bal, lower_32_bits(hw->aq.arq.desc_buf.pa));
	wr32(hw, hw->aq.arq.bah, upper_32_bits(hw->aq.arq.desc_buf.pa));

	/* Update tail in the HW to post pre-allocated buffers */
	wr32(hw, hw->aq.arq.tail, hw->aq.num_arq_entries - 1);

	/* Check one रेजिस्टर to verअगरy that config was applied */
	reg = rd32(hw, hw->aq.arq.bal);
	अगर (reg != lower_32_bits(hw->aq.arq.desc_buf.pa))
		ret_code = I40E_ERR_ADMIN_QUEUE_ERROR;

	वापस ret_code;
पूर्ण

/**
 *  i40e_init_asq - मुख्य initialization routine क्रम ASQ
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 *  This is the मुख्य initialization routine क्रम the Admin Send Queue
 *  Prior to calling this function, drivers *MUST* set the following fields
 *  in the hw->aq काष्ठाure:
 *     - hw->aq.num_asq_entries
 *     - hw->aq.arq_buf_size
 *
 *  Do *NOT* hold the lock when calling this as the memory allocation routines
 *  called are not going to be atomic context safe
 **/
अटल i40e_status i40e_init_asq(काष्ठा i40e_hw *hw)
अणु
	i40e_status ret_code = 0;

	अगर (hw->aq.asq.count > 0) अणु
		/* queue alपढ़ोy initialized */
		ret_code = I40E_ERR_NOT_READY;
		जाओ init_adminq_निकास;
	पूर्ण

	/* verअगरy input क्रम valid configuration */
	अगर ((hw->aq.num_asq_entries == 0) ||
	    (hw->aq.asq_buf_size == 0)) अणु
		ret_code = I40E_ERR_CONFIG;
		जाओ init_adminq_निकास;
	पूर्ण

	hw->aq.asq.next_to_use = 0;
	hw->aq.asq.next_to_clean = 0;

	/* allocate the ring memory */
	ret_code = i40e_alloc_adminq_asq_ring(hw);
	अगर (ret_code)
		जाओ init_adminq_निकास;

	/* allocate buffers in the rings */
	ret_code = i40e_alloc_asq_bufs(hw);
	अगर (ret_code)
		जाओ init_adminq_मुक्त_rings;

	/* initialize base रेजिस्टरs */
	ret_code = i40e_config_asq_regs(hw);
	अगर (ret_code)
		जाओ init_adminq_मुक्त_rings;

	/* success! */
	hw->aq.asq.count = hw->aq.num_asq_entries;
	जाओ init_adminq_निकास;

init_adminq_मुक्त_rings:
	i40e_मुक्त_adminq_asq(hw);

init_adminq_निकास:
	वापस ret_code;
पूर्ण

/**
 *  i40e_init_arq - initialize ARQ
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 *  The मुख्य initialization routine क्रम the Admin Receive (Event) Queue.
 *  Prior to calling this function, drivers *MUST* set the following fields
 *  in the hw->aq काष्ठाure:
 *     - hw->aq.num_asq_entries
 *     - hw->aq.arq_buf_size
 *
 *  Do *NOT* hold the lock when calling this as the memory allocation routines
 *  called are not going to be atomic context safe
 **/
अटल i40e_status i40e_init_arq(काष्ठा i40e_hw *hw)
अणु
	i40e_status ret_code = 0;

	अगर (hw->aq.arq.count > 0) अणु
		/* queue alपढ़ोy initialized */
		ret_code = I40E_ERR_NOT_READY;
		जाओ init_adminq_निकास;
	पूर्ण

	/* verअगरy input क्रम valid configuration */
	अगर ((hw->aq.num_arq_entries == 0) ||
	    (hw->aq.arq_buf_size == 0)) अणु
		ret_code = I40E_ERR_CONFIG;
		जाओ init_adminq_निकास;
	पूर्ण

	hw->aq.arq.next_to_use = 0;
	hw->aq.arq.next_to_clean = 0;

	/* allocate the ring memory */
	ret_code = i40e_alloc_adminq_arq_ring(hw);
	अगर (ret_code)
		जाओ init_adminq_निकास;

	/* allocate buffers in the rings */
	ret_code = i40e_alloc_arq_bufs(hw);
	अगर (ret_code)
		जाओ init_adminq_मुक्त_rings;

	/* initialize base रेजिस्टरs */
	ret_code = i40e_config_arq_regs(hw);
	अगर (ret_code)
		जाओ init_adminq_मुक्त_rings;

	/* success! */
	hw->aq.arq.count = hw->aq.num_arq_entries;
	जाओ init_adminq_निकास;

init_adminq_मुक्त_rings:
	i40e_मुक्त_adminq_arq(hw);

init_adminq_निकास:
	वापस ret_code;
पूर्ण

/**
 *  i40e_shutकरोwn_asq - shutकरोwn the ASQ
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 *  The मुख्य shutकरोwn routine क्रम the Admin Send Queue
 **/
अटल i40e_status i40e_shutकरोwn_asq(काष्ठा i40e_hw *hw)
अणु
	i40e_status ret_code = 0;

	mutex_lock(&hw->aq.asq_mutex);

	अगर (hw->aq.asq.count == 0) अणु
		ret_code = I40E_ERR_NOT_READY;
		जाओ shutकरोwn_asq_out;
	पूर्ण

	/* Stop firmware AdminQ processing */
	wr32(hw, hw->aq.asq.head, 0);
	wr32(hw, hw->aq.asq.tail, 0);
	wr32(hw, hw->aq.asq.len, 0);
	wr32(hw, hw->aq.asq.bal, 0);
	wr32(hw, hw->aq.asq.bah, 0);

	hw->aq.asq.count = 0; /* to indicate uninitialized queue */

	/* मुक्त ring buffers */
	i40e_मुक्त_asq_bufs(hw);

shutकरोwn_asq_out:
	mutex_unlock(&hw->aq.asq_mutex);
	वापस ret_code;
पूर्ण

/**
 *  i40e_shutकरोwn_arq - shutकरोwn ARQ
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 *  The मुख्य shutकरोwn routine क्रम the Admin Receive Queue
 **/
अटल i40e_status i40e_shutकरोwn_arq(काष्ठा i40e_hw *hw)
अणु
	i40e_status ret_code = 0;

	mutex_lock(&hw->aq.arq_mutex);

	अगर (hw->aq.arq.count == 0) अणु
		ret_code = I40E_ERR_NOT_READY;
		जाओ shutकरोwn_arq_out;
	पूर्ण

	/* Stop firmware AdminQ processing */
	wr32(hw, hw->aq.arq.head, 0);
	wr32(hw, hw->aq.arq.tail, 0);
	wr32(hw, hw->aq.arq.len, 0);
	wr32(hw, hw->aq.arq.bal, 0);
	wr32(hw, hw->aq.arq.bah, 0);

	hw->aq.arq.count = 0; /* to indicate uninitialized queue */

	/* मुक्त ring buffers */
	i40e_मुक्त_arq_bufs(hw);

shutकरोwn_arq_out:
	mutex_unlock(&hw->aq.arq_mutex);
	वापस ret_code;
पूर्ण

/**
 *  i40e_set_hw_flags - set HW flags
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 **/
अटल व्योम i40e_set_hw_flags(काष्ठा i40e_hw *hw)
अणु
	काष्ठा i40e_adminq_info *aq = &hw->aq;

	hw->flags = 0;

	चयन (hw->mac.type) अणु
	हाल I40E_MAC_XL710:
		अगर (aq->api_maj_ver > 1 ||
		    (aq->api_maj_ver == 1 &&
		     aq->api_min_ver >= I40E_MINOR_VER_GET_LINK_INFO_XL710)) अणु
			hw->flags |= I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE;
			hw->flags |= I40E_HW_FLAG_FW_LLDP_STOPPABLE;
			/* The ability to RX (not drop) 802.1ad frames */
			hw->flags |= I40E_HW_FLAG_802_1AD_CAPABLE;
		पूर्ण
		अवरोध;
	हाल I40E_MAC_X722:
		hw->flags |= I40E_HW_FLAG_AQ_SRCTL_ACCESS_ENABLE |
			     I40E_HW_FLAG_NVM_READ_REQUIRES_LOCK;

		अगर (aq->api_maj_ver > 1 ||
		    (aq->api_maj_ver == 1 &&
		     aq->api_min_ver >= I40E_MINOR_VER_FW_LLDP_STOPPABLE_X722))
			hw->flags |= I40E_HW_FLAG_FW_LLDP_STOPPABLE;

		अगर (aq->api_maj_ver > 1 ||
		    (aq->api_maj_ver == 1 &&
		     aq->api_min_ver >= I40E_MINOR_VER_GET_LINK_INFO_X722))
			hw->flags |= I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE;

		अगर (aq->api_maj_ver > 1 ||
		    (aq->api_maj_ver == 1 &&
		     aq->api_min_ver >= I40E_MINOR_VER_FW_REQUEST_FEC_X722))
			hw->flags |= I40E_HW_FLAG_X722_FEC_REQUEST_CAPABLE;

		fallthrough;
	शेष:
		अवरोध;
	पूर्ण

	/* Newer versions of firmware require lock when पढ़ोing the NVM */
	अगर (aq->api_maj_ver > 1 ||
	    (aq->api_maj_ver == 1 &&
	     aq->api_min_ver >= 5))
		hw->flags |= I40E_HW_FLAG_NVM_READ_REQUIRES_LOCK;

	अगर (aq->api_maj_ver > 1 ||
	    (aq->api_maj_ver == 1 &&
	     aq->api_min_ver >= 8)) अणु
		hw->flags |= I40E_HW_FLAG_FW_LLDP_PERSISTENT;
		hw->flags |= I40E_HW_FLAG_DROP_MODE;
	पूर्ण

	अगर (aq->api_maj_ver > 1 ||
	    (aq->api_maj_ver == 1 &&
	     aq->api_min_ver >= 9))
		hw->flags |= I40E_HW_FLAG_AQ_PHY_ACCESS_EXTENDED;
पूर्ण

/**
 *  i40e_init_adminq - मुख्य initialization routine क्रम Admin Queue
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 *  Prior to calling this function, drivers *MUST* set the following fields
 *  in the hw->aq काष्ठाure:
 *     - hw->aq.num_asq_entries
 *     - hw->aq.num_arq_entries
 *     - hw->aq.arq_buf_size
 *     - hw->aq.asq_buf_size
 **/
i40e_status i40e_init_adminq(काष्ठा i40e_hw *hw)
अणु
	u16 cfg_ptr, oem_hi, oem_lo;
	u16 eetrack_lo, eetrack_hi;
	i40e_status ret_code;
	पूर्णांक retry = 0;

	/* verअगरy input क्रम valid configuration */
	अगर ((hw->aq.num_arq_entries == 0) ||
	    (hw->aq.num_asq_entries == 0) ||
	    (hw->aq.arq_buf_size == 0) ||
	    (hw->aq.asq_buf_size == 0)) अणु
		ret_code = I40E_ERR_CONFIG;
		जाओ init_adminq_निकास;
	पूर्ण

	/* Set up रेजिस्टर offsets */
	i40e_adminq_init_regs(hw);

	/* setup ASQ command ग_लिखो back समयout */
	hw->aq.asq_cmd_समयout = I40E_ASQ_CMD_TIMEOUT;

	/* allocate the ASQ */
	ret_code = i40e_init_asq(hw);
	अगर (ret_code)
		जाओ init_adminq_destroy_locks;

	/* allocate the ARQ */
	ret_code = i40e_init_arq(hw);
	अगर (ret_code)
		जाओ init_adminq_मुक्त_asq;

	/* There are some हालs where the firmware may not be quite पढ़ोy
	 * क्रम AdminQ operations, so we retry the AdminQ setup a few बार
	 * अगर we see समयouts in this first AQ call.
	 */
	करो अणु
		ret_code = i40e_aq_get_firmware_version(hw,
							&hw->aq.fw_maj_ver,
							&hw->aq.fw_min_ver,
							&hw->aq.fw_build,
							&hw->aq.api_maj_ver,
							&hw->aq.api_min_ver,
							शून्य);
		अगर (ret_code != I40E_ERR_ADMIN_QUEUE_TIMEOUT)
			अवरोध;
		retry++;
		msleep(100);
		i40e_resume_aq(hw);
	पूर्ण जबतक (retry < 10);
	अगर (ret_code != I40E_SUCCESS)
		जाओ init_adminq_मुक्त_arq;

	/* Some features were पूर्णांकroduced in dअगरferent FW API version
	 * क्रम dअगरferent MAC type.
	 */
	i40e_set_hw_flags(hw);

	/* get the NVM version info */
	i40e_पढ़ो_nvm_word(hw, I40E_SR_NVM_DEV_STARTER_VERSION,
			   &hw->nvm.version);
	i40e_पढ़ो_nvm_word(hw, I40E_SR_NVM_EETRACK_LO, &eetrack_lo);
	i40e_पढ़ो_nvm_word(hw, I40E_SR_NVM_EETRACK_HI, &eetrack_hi);
	hw->nvm.eetrack = (eetrack_hi << 16) | eetrack_lo;
	i40e_पढ़ो_nvm_word(hw, I40E_SR_BOOT_CONFIG_PTR, &cfg_ptr);
	i40e_पढ़ो_nvm_word(hw, (cfg_ptr + I40E_NVM_OEM_VER_OFF),
			   &oem_hi);
	i40e_पढ़ो_nvm_word(hw, (cfg_ptr + (I40E_NVM_OEM_VER_OFF + 1)),
			   &oem_lo);
	hw->nvm.oem_ver = ((u32)oem_hi << 16) | oem_lo;

	अगर (hw->mac.type == I40E_MAC_XL710 &&
	    hw->aq.api_maj_ver == I40E_FW_API_VERSION_MAJOR &&
	    hw->aq.api_min_ver >= I40E_MINOR_VER_GET_LINK_INFO_XL710) अणु
		hw->flags |= I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE;
		hw->flags |= I40E_HW_FLAG_FW_LLDP_STOPPABLE;
	पूर्ण
	अगर (hw->mac.type == I40E_MAC_X722 &&
	    hw->aq.api_maj_ver == I40E_FW_API_VERSION_MAJOR &&
	    hw->aq.api_min_ver >= I40E_MINOR_VER_FW_LLDP_STOPPABLE_X722) अणु
		hw->flags |= I40E_HW_FLAG_FW_LLDP_STOPPABLE;
	पूर्ण

	/* The ability to RX (not drop) 802.1ad frames was added in API 1.7 */
	अगर (hw->aq.api_maj_ver > 1 ||
	    (hw->aq.api_maj_ver == 1 &&
	     hw->aq.api_min_ver >= 7))
		hw->flags |= I40E_HW_FLAG_802_1AD_CAPABLE;

	अगर (hw->aq.api_maj_ver > I40E_FW_API_VERSION_MAJOR) अणु
		ret_code = I40E_ERR_FIRMWARE_API_VERSION;
		जाओ init_adminq_मुक्त_arq;
	पूर्ण

	/* pre-emptive resource lock release */
	i40e_aq_release_resource(hw, I40E_NVM_RESOURCE_ID, 0, शून्य);
	hw->nvm_release_on_करोne = false;
	hw->nvmupd_state = I40E_NVMUPD_STATE_INIT;

	ret_code = 0;

	/* success! */
	जाओ init_adminq_निकास;

init_adminq_मुक्त_arq:
	i40e_shutकरोwn_arq(hw);
init_adminq_मुक्त_asq:
	i40e_shutकरोwn_asq(hw);
init_adminq_destroy_locks:

init_adminq_निकास:
	वापस ret_code;
पूर्ण

/**
 *  i40e_shutकरोwn_adminq - shutकरोwn routine क्रम the Admin Queue
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 **/
व्योम i40e_shutकरोwn_adminq(काष्ठा i40e_hw *hw)
अणु
	अगर (i40e_check_asq_alive(hw))
		i40e_aq_queue_shutकरोwn(hw, true);

	i40e_shutकरोwn_asq(hw);
	i40e_shutकरोwn_arq(hw);

	अगर (hw->nvm_buff.va)
		i40e_मुक्त_virt_mem(hw, &hw->nvm_buff);
पूर्ण

/**
 *  i40e_clean_asq - cleans Admin send queue
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 *  वापसs the number of मुक्त desc
 **/
अटल u16 i40e_clean_asq(काष्ठा i40e_hw *hw)
अणु
	काष्ठा i40e_adminq_ring *asq = &(hw->aq.asq);
	काष्ठा i40e_asq_cmd_details *details;
	u16 ntc = asq->next_to_clean;
	काष्ठा i40e_aq_desc desc_cb;
	काष्ठा i40e_aq_desc *desc;

	desc = I40E_ADMINQ_DESC(*asq, ntc);
	details = I40E_ADMINQ_DETAILS(*asq, ntc);
	जबतक (rd32(hw, hw->aq.asq.head) != ntc) अणु
		i40e_debug(hw, I40E_DEBUG_AQ_COMMAND,
			   "ntc %d head %d.\n", ntc, rd32(hw, hw->aq.asq.head));

		अगर (details->callback) अणु
			I40E_ADMINQ_CALLBACK cb_func =
					(I40E_ADMINQ_CALLBACK)details->callback;
			desc_cb = *desc;
			cb_func(hw, &desc_cb);
		पूर्ण
		स_रखो(desc, 0, माप(*desc));
		स_रखो(details, 0, माप(*details));
		ntc++;
		अगर (ntc == asq->count)
			ntc = 0;
		desc = I40E_ADMINQ_DESC(*asq, ntc);
		details = I40E_ADMINQ_DETAILS(*asq, ntc);
	पूर्ण

	asq->next_to_clean = ntc;

	वापस I40E_DESC_UNUSED(asq);
पूर्ण

/**
 *  i40e_asq_करोne - check अगर FW has processed the Admin Send Queue
 *  @hw: poपूर्णांकer to the hw काष्ठा
 *
 *  Returns true अगर the firmware has processed all descriptors on the
 *  admin send queue. Returns false अगर there are still requests pending.
 **/
अटल bool i40e_asq_करोne(काष्ठा i40e_hw *hw)
अणु
	/* AQ designers suggest use of head क्रम better
	 * timing reliability than DD bit
	 */
	वापस rd32(hw, hw->aq.asq.head) == hw->aq.asq.next_to_use;

पूर्ण

/**
 *  i40e_asq_send_command - send command to Admin Queue
 *  @hw: poपूर्णांकer to the hw काष्ठा
 *  @desc: prefilled descriptor describing the command (non DMA mem)
 *  @buff: buffer to use क्रम indirect commands
 *  @buff_size: size of buffer क्रम indirect commands
 *  @cmd_details: poपूर्णांकer to command details काष्ठाure
 *
 *  This is the मुख्य send command driver routine क्रम the Admin Queue send
 *  queue.  It runs the queue, cleans the queue, etc
 **/
i40e_status i40e_asq_send_command(काष्ठा i40e_hw *hw,
				काष्ठा i40e_aq_desc *desc,
				व्योम *buff, /* can be शून्य */
				u16  buff_size,
				काष्ठा i40e_asq_cmd_details *cmd_details)
अणु
	i40e_status status = 0;
	काष्ठा i40e_dma_mem *dma_buff = शून्य;
	काष्ठा i40e_asq_cmd_details *details;
	काष्ठा i40e_aq_desc *desc_on_ring;
	bool cmd_completed = false;
	u16  retval = 0;
	u32  val = 0;

	mutex_lock(&hw->aq.asq_mutex);

	अगर (hw->aq.asq.count == 0) अणु
		i40e_debug(hw, I40E_DEBUG_AQ_MESSAGE,
			   "AQTX: Admin queue not initialized.\n");
		status = I40E_ERR_QUEUE_EMPTY;
		जाओ asq_send_command_error;
	पूर्ण

	hw->aq.asq_last_status = I40E_AQ_RC_OK;

	val = rd32(hw, hw->aq.asq.head);
	अगर (val >= hw->aq.num_asq_entries) अणु
		i40e_debug(hw, I40E_DEBUG_AQ_MESSAGE,
			   "AQTX: head overrun at %d\n", val);
		status = I40E_ERR_ADMIN_QUEUE_FULL;
		जाओ asq_send_command_error;
	पूर्ण

	details = I40E_ADMINQ_DETAILS(hw->aq.asq, hw->aq.asq.next_to_use);
	अगर (cmd_details) अणु
		*details = *cmd_details;

		/* If the cmd_details are defined copy the cookie.  The
		 * cpu_to_le32 is not needed here because the data is ignored
		 * by the FW, only used by the driver
		 */
		अगर (details->cookie) अणु
			desc->cookie_high =
				cpu_to_le32(upper_32_bits(details->cookie));
			desc->cookie_low =
				cpu_to_le32(lower_32_bits(details->cookie));
		पूर्ण
	पूर्ण अन्यथा अणु
		स_रखो(details, 0, माप(काष्ठा i40e_asq_cmd_details));
	पूर्ण

	/* clear requested flags and then set additional flags अगर defined */
	desc->flags &= ~cpu_to_le16(details->flags_dis);
	desc->flags |= cpu_to_le16(details->flags_ena);

	अगर (buff_size > hw->aq.asq_buf_size) अणु
		i40e_debug(hw,
			   I40E_DEBUG_AQ_MESSAGE,
			   "AQTX: Invalid buffer size: %d.\n",
			   buff_size);
		status = I40E_ERR_INVALID_SIZE;
		जाओ asq_send_command_error;
	पूर्ण

	अगर (details->postpone && !details->async) अणु
		i40e_debug(hw,
			   I40E_DEBUG_AQ_MESSAGE,
			   "AQTX: Async flag not set along with postpone flag");
		status = I40E_ERR_PARAM;
		जाओ asq_send_command_error;
	पूर्ण

	/* call clean and check queue available function to reclaim the
	 * descriptors that were processed by FW, the function वापसs the
	 * number of desc available
	 */
	/* the clean function called here could be called in a separate thपढ़ो
	 * in हाल of asynchronous completions
	 */
	अगर (i40e_clean_asq(hw) == 0) अणु
		i40e_debug(hw,
			   I40E_DEBUG_AQ_MESSAGE,
			   "AQTX: Error queue is full.\n");
		status = I40E_ERR_ADMIN_QUEUE_FULL;
		जाओ asq_send_command_error;
	पूर्ण

	/* initialize the temp desc poपूर्णांकer with the right desc */
	desc_on_ring = I40E_ADMINQ_DESC(hw->aq.asq, hw->aq.asq.next_to_use);

	/* अगर the desc is available copy the temp desc to the right place */
	*desc_on_ring = *desc;

	/* अगर buff is not शून्य assume indirect command */
	अगर (buff != शून्य) अणु
		dma_buff = &(hw->aq.asq.r.asq_bi[hw->aq.asq.next_to_use]);
		/* copy the user buff पूर्णांकo the respective DMA buff */
		स_नकल(dma_buff->va, buff, buff_size);
		desc_on_ring->datalen = cpu_to_le16(buff_size);

		/* Update the address values in the desc with the pa value
		 * क्रम respective buffer
		 */
		desc_on_ring->params.बाह्यal.addr_high =
				cpu_to_le32(upper_32_bits(dma_buff->pa));
		desc_on_ring->params.बाह्यal.addr_low =
				cpu_to_le32(lower_32_bits(dma_buff->pa));
	पूर्ण

	/* bump the tail */
	i40e_debug(hw, I40E_DEBUG_AQ_COMMAND, "AQTX: desc and buffer:\n");
	i40e_debug_aq(hw, I40E_DEBUG_AQ_COMMAND, (व्योम *)desc_on_ring,
		      buff, buff_size);
	(hw->aq.asq.next_to_use)++;
	अगर (hw->aq.asq.next_to_use == hw->aq.asq.count)
		hw->aq.asq.next_to_use = 0;
	अगर (!details->postpone)
		wr32(hw, hw->aq.asq.tail, hw->aq.asq.next_to_use);

	/* अगर cmd_details are not defined or async flag is not set,
	 * we need to रुको क्रम desc ग_लिखो back
	 */
	अगर (!details->async && !details->postpone) अणु
		u32 total_delay = 0;

		करो अणु
			/* AQ designers suggest use of head क्रम better
			 * timing reliability than DD bit
			 */
			अगर (i40e_asq_करोne(hw))
				अवरोध;
			udelay(50);
			total_delay += 50;
		पूर्ण जबतक (total_delay < hw->aq.asq_cmd_समयout);
	पूर्ण

	/* अगर पढ़ोy, copy the desc back to temp */
	अगर (i40e_asq_करोne(hw)) अणु
		*desc = *desc_on_ring;
		अगर (buff != शून्य)
			स_नकल(buff, dma_buff->va, buff_size);
		retval = le16_to_cpu(desc->retval);
		अगर (retval != 0) अणु
			i40e_debug(hw,
				   I40E_DEBUG_AQ_MESSAGE,
				   "AQTX: Command completed with error 0x%X.\n",
				   retval);

			/* strip off FW पूर्णांकernal code */
			retval &= 0xff;
		पूर्ण
		cmd_completed = true;
		अगर ((क्रमागत i40e_admin_queue_err)retval == I40E_AQ_RC_OK)
			status = 0;
		अन्यथा अगर ((क्रमागत i40e_admin_queue_err)retval == I40E_AQ_RC_EBUSY)
			status = I40E_ERR_NOT_READY;
		अन्यथा
			status = I40E_ERR_ADMIN_QUEUE_ERROR;
		hw->aq.asq_last_status = (क्रमागत i40e_admin_queue_err)retval;
	पूर्ण

	i40e_debug(hw, I40E_DEBUG_AQ_COMMAND,
		   "AQTX: desc and buffer writeback:\n");
	i40e_debug_aq(hw, I40E_DEBUG_AQ_COMMAND, (व्योम *)desc, buff, buff_size);

	/* save ग_लिखोback aq अगर requested */
	अगर (details->wb_desc)
		*details->wb_desc = *desc_on_ring;

	/* update the error अगर समय out occurred */
	अगर ((!cmd_completed) &&
	    (!details->async && !details->postpone)) अणु
		अगर (rd32(hw, hw->aq.asq.len) & I40E_GL_ATQLEN_ATQCRIT_MASK) अणु
			i40e_debug(hw, I40E_DEBUG_AQ_MESSAGE,
				   "AQTX: AQ Critical error.\n");
			status = I40E_ERR_ADMIN_QUEUE_CRITICAL_ERROR;
		पूर्ण अन्यथा अणु
			i40e_debug(hw, I40E_DEBUG_AQ_MESSAGE,
				   "AQTX: Writeback timeout.\n");
			status = I40E_ERR_ADMIN_QUEUE_TIMEOUT;
		पूर्ण
	पूर्ण

asq_send_command_error:
	mutex_unlock(&hw->aq.asq_mutex);
	वापस status;
पूर्ण

/**
 *  i40e_fill_शेष_direct_cmd_desc - AQ descriptor helper function
 *  @desc:     poपूर्णांकer to the temp descriptor (non DMA mem)
 *  @opcode:   the opcode can be used to decide which flags to turn off or on
 *
 *  Fill the desc with शेष values
 **/
व्योम i40e_fill_शेष_direct_cmd_desc(काष्ठा i40e_aq_desc *desc,
				       u16 opcode)
अणु
	/* zero out the desc */
	स_रखो((व्योम *)desc, 0, माप(काष्ठा i40e_aq_desc));
	desc->opcode = cpu_to_le16(opcode);
	desc->flags = cpu_to_le16(I40E_AQ_FLAG_SI);
पूर्ण

/**
 *  i40e_clean_arq_element
 *  @hw: poपूर्णांकer to the hw काष्ठा
 *  @e: event info from the receive descriptor, includes any buffers
 *  @pending: number of events that could be left to process
 *
 *  This function cleans one Admin Receive Queue element and वापसs
 *  the contents through e.  It can also वापस how many events are
 *  left to process through 'pending'
 **/
i40e_status i40e_clean_arq_element(काष्ठा i40e_hw *hw,
					     काष्ठा i40e_arq_event_info *e,
					     u16 *pending)
अणु
	i40e_status ret_code = 0;
	u16 ntc = hw->aq.arq.next_to_clean;
	काष्ठा i40e_aq_desc *desc;
	काष्ठा i40e_dma_mem *bi;
	u16 desc_idx;
	u16 datalen;
	u16 flags;
	u16 ntu;

	/* pre-clean the event info */
	स_रखो(&e->desc, 0, माप(e->desc));

	/* take the lock beक्रमe we start messing with the ring */
	mutex_lock(&hw->aq.arq_mutex);

	अगर (hw->aq.arq.count == 0) अणु
		i40e_debug(hw, I40E_DEBUG_AQ_MESSAGE,
			   "AQRX: Admin queue not initialized.\n");
		ret_code = I40E_ERR_QUEUE_EMPTY;
		जाओ clean_arq_element_err;
	पूर्ण

	/* set next_to_use to head */
	ntu = rd32(hw, hw->aq.arq.head) & I40E_PF_ARQH_ARQH_MASK;
	अगर (ntu == ntc) अणु
		/* nothing to करो - shouldn't need to update ring's values */
		ret_code = I40E_ERR_ADMIN_QUEUE_NO_WORK;
		जाओ clean_arq_element_out;
	पूर्ण

	/* now clean the next descriptor */
	desc = I40E_ADMINQ_DESC(hw->aq.arq, ntc);
	desc_idx = ntc;

	hw->aq.arq_last_status =
		(क्रमागत i40e_admin_queue_err)le16_to_cpu(desc->retval);
	flags = le16_to_cpu(desc->flags);
	अगर (flags & I40E_AQ_FLAG_ERR) अणु
		ret_code = I40E_ERR_ADMIN_QUEUE_ERROR;
		i40e_debug(hw,
			   I40E_DEBUG_AQ_MESSAGE,
			   "AQRX: Event received with error 0x%X.\n",
			   hw->aq.arq_last_status);
	पूर्ण

	e->desc = *desc;
	datalen = le16_to_cpu(desc->datalen);
	e->msg_len = min(datalen, e->buf_len);
	अगर (e->msg_buf != शून्य && (e->msg_len != 0))
		स_नकल(e->msg_buf, hw->aq.arq.r.arq_bi[desc_idx].va,
		       e->msg_len);

	i40e_debug(hw, I40E_DEBUG_AQ_COMMAND, "AQRX: desc and buffer:\n");
	i40e_debug_aq(hw, I40E_DEBUG_AQ_COMMAND, (व्योम *)desc, e->msg_buf,
		      hw->aq.arq_buf_size);

	/* Restore the original datalen and buffer address in the desc,
	 * FW updates datalen to indicate the event message
	 * size
	 */
	bi = &hw->aq.arq.r.arq_bi[ntc];
	स_रखो((व्योम *)desc, 0, माप(काष्ठा i40e_aq_desc));

	desc->flags = cpu_to_le16(I40E_AQ_FLAG_BUF);
	अगर (hw->aq.arq_buf_size > I40E_AQ_LARGE_BUF)
		desc->flags |= cpu_to_le16(I40E_AQ_FLAG_LB);
	desc->datalen = cpu_to_le16((u16)bi->size);
	desc->params.बाह्यal.addr_high = cpu_to_le32(upper_32_bits(bi->pa));
	desc->params.बाह्यal.addr_low = cpu_to_le32(lower_32_bits(bi->pa));

	/* set tail = the last cleaned desc index. */
	wr32(hw, hw->aq.arq.tail, ntc);
	/* ntc is updated to tail + 1 */
	ntc++;
	अगर (ntc == hw->aq.num_arq_entries)
		ntc = 0;
	hw->aq.arq.next_to_clean = ntc;
	hw->aq.arq.next_to_use = ntu;

	i40e_nvmupd_check_रुको_event(hw, le16_to_cpu(e->desc.opcode), &e->desc);
clean_arq_element_out:
	/* Set pending अगर needed, unlock and वापस */
	अगर (pending)
		*pending = (ntc > ntu ? hw->aq.arq.count : 0) + (ntu - ntc);
clean_arq_element_err:
	mutex_unlock(&hw->aq.arq_mutex);

	वापस ret_code;
पूर्ण

अटल व्योम i40e_resume_aq(काष्ठा i40e_hw *hw)
अणु
	/* Registers are reset after PF reset */
	hw->aq.asq.next_to_use = 0;
	hw->aq.asq.next_to_clean = 0;

	i40e_config_asq_regs(hw);

	hw->aq.arq.next_to_use = 0;
	hw->aq.arq.next_to_clean = 0;

	i40e_config_arq_regs(hw);
पूर्ण
