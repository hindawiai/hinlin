<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009 - 2018 Intel Corporation. */

#समावेश "mbx.h"

/**
 *  e1000_poll_क्रम_msg - Wait क्रम message notअगरication
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  वापसs SUCCESS अगर it successfully received a message notअगरication
 **/
अटल s32 e1000_poll_क्रम_msg(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	पूर्णांक countकरोwn = mbx->समयout;

	अगर (!mbx->ops.check_क्रम_msg)
		जाओ out;

	जबतक (countकरोwn && mbx->ops.check_क्रम_msg(hw)) अणु
		countकरोwn--;
		udelay(mbx->usec_delay);
	पूर्ण

	/* अगर we failed, all future posted messages fail until reset */
	अगर (!countकरोwn)
		mbx->समयout = 0;
out:
	वापस countकरोwn ? E1000_SUCCESS : -E1000_ERR_MBX;
पूर्ण

/**
 *  e1000_poll_क्रम_ack - Wait क्रम message acknowledgment
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  वापसs SUCCESS अगर it successfully received a message acknowledgment
 **/
अटल s32 e1000_poll_क्रम_ack(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	पूर्णांक countकरोwn = mbx->समयout;

	अगर (!mbx->ops.check_क्रम_ack)
		जाओ out;

	जबतक (countकरोwn && mbx->ops.check_क्रम_ack(hw)) अणु
		countकरोwn--;
		udelay(mbx->usec_delay);
	पूर्ण

	/* अगर we failed, all future posted messages fail until reset */
	अगर (!countकरोwn)
		mbx->समयout = 0;
out:
	वापस countकरोwn ? E1000_SUCCESS : -E1000_ERR_MBX;
पूर्ण

/**
 *  e1000_पढ़ो_posted_mbx - Wait क्रम message notअगरication and receive message
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *
 *  वापसs SUCCESS अगर it successfully received a message notअगरication and
 *  copied it पूर्णांकo the receive buffer.
 **/
अटल s32 e1000_पढ़ो_posted_mbx(काष्ठा e1000_hw *hw, u32 *msg, u16 size)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	s32 ret_val = -E1000_ERR_MBX;

	अगर (!mbx->ops.पढ़ो)
		जाओ out;

	ret_val = e1000_poll_क्रम_msg(hw);

	/* अगर ack received पढ़ो message, otherwise we समयd out */
	अगर (!ret_val)
		ret_val = mbx->ops.पढ़ो(hw, msg, size);
out:
	वापस ret_val;
पूर्ण

/**
 *  e1000_ग_लिखो_posted_mbx - Write a message to the mailbox, रुको क्रम ack
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *
 *  वापसs SUCCESS अगर it successfully copied message पूर्णांकo the buffer and
 *  received an ack to that message within delay * समयout period
 **/
अटल s32 e1000_ग_लिखो_posted_mbx(काष्ठा e1000_hw *hw, u32 *msg, u16 size)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	s32 ret_val = -E1000_ERR_MBX;

	/* निकास अगर we either can't write or there isn't a defined समयout */
	अगर (!mbx->ops.ग_लिखो || !mbx->समयout)
		जाओ out;

	/* send msg*/
	ret_val = mbx->ops.ग_लिखो(hw, msg, size);

	/* अगर msg sent रुको until we receive an ack */
	अगर (!ret_val)
		ret_val = e1000_poll_क्रम_ack(hw);
out:
	वापस ret_val;
पूर्ण

/**
 *  e1000_पढ़ो_v2p_mailbox - पढ़ो v2p mailbox
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  This function is used to पढ़ो the v2p mailbox without losing the पढ़ो to
 *  clear status bits.
 **/
अटल u32 e1000_पढ़ो_v2p_mailbox(काष्ठा e1000_hw *hw)
अणु
	u32 v2p_mailbox = er32(V2PMAILBOX(0));

	v2p_mailbox |= hw->dev_spec.vf.v2p_mailbox;
	hw->dev_spec.vf.v2p_mailbox |= v2p_mailbox & E1000_V2PMAILBOX_R2C_BITS;

	वापस v2p_mailbox;
पूर्ण

/**
 *  e1000_check_क्रम_bit_vf - Determine अगर a status bit was set
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mask: biपंचांगask क्रम bits to be tested and cleared
 *
 *  This function is used to check क्रम the पढ़ो to clear bits within
 *  the V2P mailbox.
 **/
अटल s32 e1000_check_क्रम_bit_vf(काष्ठा e1000_hw *hw, u32 mask)
अणु
	u32 v2p_mailbox = e1000_पढ़ो_v2p_mailbox(hw);
	s32 ret_val = -E1000_ERR_MBX;

	अगर (v2p_mailbox & mask)
		ret_val = E1000_SUCCESS;

	hw->dev_spec.vf.v2p_mailbox &= ~mask;

	वापस ret_val;
पूर्ण

/**
 *  e1000_check_क्रम_msg_vf - checks to see अगर the PF has sent mail
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  वापसs SUCCESS अगर the PF has set the Status bit or अन्यथा ERR_MBX
 **/
अटल s32 e1000_check_क्रम_msg_vf(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = -E1000_ERR_MBX;

	अगर (!e1000_check_क्रम_bit_vf(hw, E1000_V2PMAILBOX_PFSTS)) अणु
		ret_val = E1000_SUCCESS;
		hw->mbx.stats.reqs++;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_check_क्रम_ack_vf - checks to see अगर the PF has ACK'd
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  वापसs SUCCESS अगर the PF has set the ACK bit or अन्यथा ERR_MBX
 **/
अटल s32 e1000_check_क्रम_ack_vf(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = -E1000_ERR_MBX;

	अगर (!e1000_check_क्रम_bit_vf(hw, E1000_V2PMAILBOX_PFACK)) अणु
		ret_val = E1000_SUCCESS;
		hw->mbx.stats.acks++;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_check_क्रम_rst_vf - checks to see अगर the PF has reset
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  वापसs true अगर the PF has set the reset करोne bit or अन्यथा false
 **/
अटल s32 e1000_check_क्रम_rst_vf(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = -E1000_ERR_MBX;

	अगर (!e1000_check_क्रम_bit_vf(hw, (E1000_V2PMAILBOX_RSTD |
					 E1000_V2PMAILBOX_RSTI))) अणु
		ret_val = E1000_SUCCESS;
		hw->mbx.stats.rsts++;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_obtain_mbx_lock_vf - obtain mailbox lock
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  वापस SUCCESS अगर we obtained the mailbox lock
 **/
अटल s32 e1000_obtain_mbx_lock_vf(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = -E1000_ERR_MBX;
	पूर्णांक count = 10;

	करो अणु
		/* Take ownership of the buffer */
		ew32(V2PMAILBOX(0), E1000_V2PMAILBOX_VFU);

		/* reserve mailbox क्रम VF use */
		अगर (e1000_पढ़ो_v2p_mailbox(hw) & E1000_V2PMAILBOX_VFU) अणु
			ret_val = 0;
			अवरोध;
		पूर्ण
		udelay(1000);
	पूर्ण जबतक (count-- > 0);

	वापस ret_val;
पूर्ण

/**
 *  e1000_ग_लिखो_mbx_vf - Write a message to the mailbox
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *
 *  वापसs SUCCESS अगर it successfully copied message पूर्णांकo the buffer
 **/
अटल s32 e1000_ग_लिखो_mbx_vf(काष्ठा e1000_hw *hw, u32 *msg, u16 size)
अणु
	s32 err;
	u16 i;

	lockdep_निश्चित_held(&hw->mbx_lock);

	/* lock the mailbox to prevent pf/vf race condition */
	err = e1000_obtain_mbx_lock_vf(hw);
	अगर (err)
		जाओ out_no_ग_लिखो;

	/* flush any ack or msg as we are going to overग_लिखो mailbox */
	e1000_check_क्रम_ack_vf(hw);
	e1000_check_क्रम_msg_vf(hw);

	/* copy the caller specअगरied message to the mailbox memory buffer */
	क्रम (i = 0; i < size; i++)
		array_ew32(VMBMEM(0), i, msg[i]);

	/* update stats */
	hw->mbx.stats.msgs_tx++;

	/* Drop VFU and पूर्णांकerrupt the PF to tell it a message has been sent */
	ew32(V2PMAILBOX(0), E1000_V2PMAILBOX_REQ);

out_no_ग_लिखो:
	वापस err;
पूर्ण

/**
 *  e1000_पढ़ो_mbx_vf - Reads a message from the inbox पूर्णांकended क्रम VF
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *
 *  वापसs SUCCESS अगर it successfully पढ़ो message from buffer
 **/
अटल s32 e1000_पढ़ो_mbx_vf(काष्ठा e1000_hw *hw, u32 *msg, u16 size)
अणु
	s32 err;
	u16 i;

	lockdep_निश्चित_held(&hw->mbx_lock);

	/* lock the mailbox to prevent pf/vf race condition */
	err = e1000_obtain_mbx_lock_vf(hw);
	अगर (err)
		जाओ out_no_पढ़ो;

	/* copy the message from the mailbox memory buffer */
	क्रम (i = 0; i < size; i++)
		msg[i] = array_er32(VMBMEM(0), i);

	/* Acknowledge receipt and release mailbox, then we're करोne */
	ew32(V2PMAILBOX(0), E1000_V2PMAILBOX_ACK);

	/* update stats */
	hw->mbx.stats.msgs_rx++;

out_no_पढ़ो:
	वापस err;
पूर्ण

/**
 *  e1000_init_mbx_params_vf - set initial values क्रम VF mailbox
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Initializes the hw->mbx काष्ठा to correct values क्रम VF mailbox
 */
s32 e1000_init_mbx_params_vf(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;

	/* start mailbox as समयd out and let the reset_hw call set the समयout
	 * value to being communications
	 */
	mbx->समयout = 0;
	mbx->usec_delay = E1000_VF_MBX_INIT_DELAY;

	mbx->size = E1000_VFMAILBOX_SIZE;

	mbx->ops.पढ़ो = e1000_पढ़ो_mbx_vf;
	mbx->ops.ग_लिखो = e1000_ग_लिखो_mbx_vf;
	mbx->ops.पढ़ो_posted = e1000_पढ़ो_posted_mbx;
	mbx->ops.ग_लिखो_posted = e1000_ग_लिखो_posted_mbx;
	mbx->ops.check_क्रम_msg = e1000_check_क्रम_msg_vf;
	mbx->ops.check_क्रम_ack = e1000_check_क्रम_ack_vf;
	mbx->ops.check_क्रम_rst = e1000_check_क्रम_rst_vf;

	mbx->stats.msgs_tx = 0;
	mbx->stats.msgs_rx = 0;
	mbx->stats.reqs = 0;
	mbx->stats.acks = 0;
	mbx->stats.rsts = 0;

	वापस E1000_SUCCESS;
पूर्ण
