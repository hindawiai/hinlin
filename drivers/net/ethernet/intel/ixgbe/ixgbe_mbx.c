<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश "ixgbe.h"
#समावेश "ixgbe_mbx.h"

/**
 *  ixgbe_पढ़ो_mbx - Reads a message from the mailbox
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *  @mbx_id: id of mailbox to पढ़ो
 *
 *  वापसs SUCCESS अगर it successfully पढ़ो message from buffer
 **/
s32 ixgbe_पढ़ो_mbx(काष्ठा ixgbe_hw *hw, u32 *msg, u16 size, u16 mbx_id)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;

	/* limit पढ़ो to size of mailbox */
	अगर (size > mbx->size)
		size = mbx->size;

	अगर (!mbx->ops)
		वापस IXGBE_ERR_MBX;

	वापस mbx->ops->पढ़ो(hw, msg, size, mbx_id);
पूर्ण

/**
 *  ixgbe_ग_लिखो_mbx - Write a message to the mailbox
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *  @mbx_id: id of mailbox to ग_लिखो
 *
 *  वापसs SUCCESS अगर it successfully copied message पूर्णांकo the buffer
 **/
s32 ixgbe_ग_लिखो_mbx(काष्ठा ixgbe_hw *hw, u32 *msg, u16 size, u16 mbx_id)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;

	अगर (size > mbx->size)
		वापस IXGBE_ERR_MBX;

	अगर (!mbx->ops)
		वापस IXGBE_ERR_MBX;

	वापस mbx->ops->ग_लिखो(hw, msg, size, mbx_id);
पूर्ण

/**
 *  ixgbe_check_क्रम_msg - checks to see अगर someone sent us mail
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mbx_id: id of mailbox to check
 *
 *  वापसs SUCCESS अगर the Status bit was found or अन्यथा ERR_MBX
 **/
s32 ixgbe_check_क्रम_msg(काष्ठा ixgbe_hw *hw, u16 mbx_id)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;

	अगर (!mbx->ops)
		वापस IXGBE_ERR_MBX;

	वापस mbx->ops->check_क्रम_msg(hw, mbx_id);
पूर्ण

/**
 *  ixgbe_check_क्रम_ack - checks to see अगर someone sent us ACK
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mbx_id: id of mailbox to check
 *
 *  वापसs SUCCESS अगर the Status bit was found or अन्यथा ERR_MBX
 **/
s32 ixgbe_check_क्रम_ack(काष्ठा ixgbe_hw *hw, u16 mbx_id)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;

	अगर (!mbx->ops)
		वापस IXGBE_ERR_MBX;

	वापस mbx->ops->check_क्रम_ack(hw, mbx_id);
पूर्ण

/**
 *  ixgbe_check_क्रम_rst - checks to see अगर other side has reset
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mbx_id: id of mailbox to check
 *
 *  वापसs SUCCESS अगर the Status bit was found or अन्यथा ERR_MBX
 **/
s32 ixgbe_check_क्रम_rst(काष्ठा ixgbe_hw *hw, u16 mbx_id)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;

	अगर (!mbx->ops)
		वापस IXGBE_ERR_MBX;

	वापस mbx->ops->check_क्रम_rst(hw, mbx_id);
पूर्ण

/**
 *  ixgbe_poll_क्रम_msg - Wait क्रम message notअगरication
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mbx_id: id of mailbox to ग_लिखो
 *
 *  वापसs SUCCESS अगर it successfully received a message notअगरication
 **/
अटल s32 ixgbe_poll_क्रम_msg(काष्ठा ixgbe_hw *hw, u16 mbx_id)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;
	पूर्णांक countकरोwn = mbx->समयout;

	अगर (!countकरोwn || !mbx->ops)
		वापस IXGBE_ERR_MBX;

	जबतक (mbx->ops->check_क्रम_msg(hw, mbx_id)) अणु
		countकरोwn--;
		अगर (!countकरोwn)
			वापस IXGBE_ERR_MBX;
		udelay(mbx->usec_delay);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_poll_क्रम_ack - Wait क्रम message acknowledgement
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mbx_id: id of mailbox to ग_लिखो
 *
 *  वापसs SUCCESS अगर it successfully received a message acknowledgement
 **/
अटल s32 ixgbe_poll_क्रम_ack(काष्ठा ixgbe_hw *hw, u16 mbx_id)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;
	पूर्णांक countकरोwn = mbx->समयout;

	अगर (!countकरोwn || !mbx->ops)
		वापस IXGBE_ERR_MBX;

	जबतक (mbx->ops->check_क्रम_ack(hw, mbx_id)) अणु
		countकरोwn--;
		अगर (!countकरोwn)
			वापस IXGBE_ERR_MBX;
		udelay(mbx->usec_delay);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_पढ़ो_posted_mbx - Wait क्रम message notअगरication and receive message
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *  @mbx_id: id of mailbox to ग_लिखो
 *
 *  वापसs SUCCESS अगर it successfully received a message notअगरication and
 *  copied it पूर्णांकo the receive buffer.
 **/
अटल s32 ixgbe_पढ़ो_posted_mbx(काष्ठा ixgbe_hw *hw, u32 *msg, u16 size,
				 u16 mbx_id)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;
	s32 ret_val;

	अगर (!mbx->ops)
		वापस IXGBE_ERR_MBX;

	ret_val = ixgbe_poll_क्रम_msg(hw, mbx_id);
	अगर (ret_val)
		वापस ret_val;

	/* अगर ack received पढ़ो message */
	वापस mbx->ops->पढ़ो(hw, msg, size, mbx_id);
पूर्ण

/**
 *  ixgbe_ग_लिखो_posted_mbx - Write a message to the mailbox, रुको क्रम ack
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *  @mbx_id: id of mailbox to ग_लिखो
 *
 *  वापसs SUCCESS अगर it successfully copied message पूर्णांकo the buffer and
 *  received an ack to that message within delay * समयout period
 **/
अटल s32 ixgbe_ग_लिखो_posted_mbx(काष्ठा ixgbe_hw *hw, u32 *msg, u16 size,
			   u16 mbx_id)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;
	s32 ret_val;

	/* निकास अगर either we can't write or there isn't a defined समयout */
	अगर (!mbx->ops || !mbx->समयout)
		वापस IXGBE_ERR_MBX;

	/* send msg */
	ret_val = mbx->ops->ग_लिखो(hw, msg, size, mbx_id);
	अगर (ret_val)
		वापस ret_val;

	/* अगर msg sent रुको until we receive an ack */
	वापस ixgbe_poll_क्रम_ack(hw, mbx_id);
पूर्ण

अटल s32 ixgbe_check_क्रम_bit_pf(काष्ठा ixgbe_hw *hw, u32 mask, s32 index)
अणु
	u32 mbvficr = IXGBE_READ_REG(hw, IXGBE_MBVFICR(index));

	अगर (mbvficr & mask) अणु
		IXGBE_WRITE_REG(hw, IXGBE_MBVFICR(index), mask);
		वापस 0;
	पूर्ण

	वापस IXGBE_ERR_MBX;
पूर्ण

/**
 *  ixgbe_check_क्रम_msg_pf - checks to see अगर the VF has sent mail
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @vf_number: the VF index
 *
 *  वापसs SUCCESS अगर the VF has set the Status bit or अन्यथा ERR_MBX
 **/
अटल s32 ixgbe_check_क्रम_msg_pf(काष्ठा ixgbe_hw *hw, u16 vf_number)
अणु
	s32 index = IXGBE_MBVFICR_INDEX(vf_number);
	u32 vf_bit = vf_number % 16;

	अगर (!ixgbe_check_क्रम_bit_pf(hw, IXGBE_MBVFICR_VFREQ_VF1 << vf_bit,
				    index)) अणु
		hw->mbx.stats.reqs++;
		वापस 0;
	पूर्ण

	वापस IXGBE_ERR_MBX;
पूर्ण

/**
 *  ixgbe_check_क्रम_ack_pf - checks to see अगर the VF has ACKed
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @vf_number: the VF index
 *
 *  वापसs SUCCESS अगर the VF has set the Status bit or अन्यथा ERR_MBX
 **/
अटल s32 ixgbe_check_क्रम_ack_pf(काष्ठा ixgbe_hw *hw, u16 vf_number)
अणु
	s32 index = IXGBE_MBVFICR_INDEX(vf_number);
	u32 vf_bit = vf_number % 16;

	अगर (!ixgbe_check_क्रम_bit_pf(hw, IXGBE_MBVFICR_VFACK_VF1 << vf_bit,
				    index)) अणु
		hw->mbx.stats.acks++;
		वापस 0;
	पूर्ण

	वापस IXGBE_ERR_MBX;
पूर्ण

/**
 *  ixgbe_check_क्रम_rst_pf - checks to see अगर the VF has reset
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @vf_number: the VF index
 *
 *  वापसs SUCCESS अगर the VF has set the Status bit or अन्यथा ERR_MBX
 **/
अटल s32 ixgbe_check_क्रम_rst_pf(काष्ठा ixgbe_hw *hw, u16 vf_number)
अणु
	u32 reg_offset = (vf_number < 32) ? 0 : 1;
	u32 vf_shअगरt = vf_number % 32;
	u32 vflre = 0;

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82599EB:
		vflre = IXGBE_READ_REG(hw, IXGBE_VFLRE(reg_offset));
		अवरोध;
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		vflre = IXGBE_READ_REG(hw, IXGBE_VFLREC(reg_offset));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (vflre & BIT(vf_shअगरt)) अणु
		IXGBE_WRITE_REG(hw, IXGBE_VFLREC(reg_offset), BIT(vf_shअगरt));
		hw->mbx.stats.rsts++;
		वापस 0;
	पूर्ण

	वापस IXGBE_ERR_MBX;
पूर्ण

/**
 *  ixgbe_obtain_mbx_lock_pf - obtain mailbox lock
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @vf_number: the VF index
 *
 *  वापस SUCCESS अगर we obtained the mailbox lock
 **/
अटल s32 ixgbe_obtain_mbx_lock_pf(काष्ठा ixgbe_hw *hw, u16 vf_number)
अणु
	u32 p2v_mailbox;

	/* Take ownership of the buffer */
	IXGBE_WRITE_REG(hw, IXGBE_PFMAILBOX(vf_number), IXGBE_PFMAILBOX_PFU);

	/* reserve mailbox क्रम vf use */
	p2v_mailbox = IXGBE_READ_REG(hw, IXGBE_PFMAILBOX(vf_number));
	अगर (p2v_mailbox & IXGBE_PFMAILBOX_PFU)
		वापस 0;

	वापस IXGBE_ERR_MBX;
पूर्ण

/**
 *  ixgbe_ग_लिखो_mbx_pf - Places a message in the mailbox
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *  @vf_number: the VF index
 *
 *  वापसs SUCCESS अगर it successfully copied message पूर्णांकo the buffer
 **/
अटल s32 ixgbe_ग_लिखो_mbx_pf(काष्ठा ixgbe_hw *hw, u32 *msg, u16 size,
			      u16 vf_number)
अणु
	s32 ret_val;
	u16 i;

	/* lock the mailbox to prevent pf/vf race condition */
	ret_val = ixgbe_obtain_mbx_lock_pf(hw, vf_number);
	अगर (ret_val)
		वापस ret_val;

	/* flush msg and acks as we are overwriting the message buffer */
	ixgbe_check_क्रम_msg_pf(hw, vf_number);
	ixgbe_check_क्रम_ack_pf(hw, vf_number);

	/* copy the caller specअगरied message to the mailbox memory buffer */
	क्रम (i = 0; i < size; i++)
		IXGBE_WRITE_REG_ARRAY(hw, IXGBE_PFMBMEM(vf_number), i, msg[i]);

	/* Interrupt VF to tell it a message has been sent and release buffer*/
	IXGBE_WRITE_REG(hw, IXGBE_PFMAILBOX(vf_number), IXGBE_PFMAILBOX_STS);

	/* update stats */
	hw->mbx.stats.msgs_tx++;

	वापस 0;
पूर्ण

/**
 *  ixgbe_पढ़ो_mbx_pf - Read a message from the mailbox
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *  @vf_number: the VF index
 *
 *  This function copies a message from the mailbox buffer to the caller's
 *  memory buffer.  The presumption is that the caller knows that there was
 *  a message due to a VF request so no polling क्रम message is needed.
 **/
अटल s32 ixgbe_पढ़ो_mbx_pf(काष्ठा ixgbe_hw *hw, u32 *msg, u16 size,
			     u16 vf_number)
अणु
	s32 ret_val;
	u16 i;

	/* lock the mailbox to prevent pf/vf race condition */
	ret_val = ixgbe_obtain_mbx_lock_pf(hw, vf_number);
	अगर (ret_val)
		वापस ret_val;

	/* copy the message to the mailbox memory buffer */
	क्रम (i = 0; i < size; i++)
		msg[i] = IXGBE_READ_REG_ARRAY(hw, IXGBE_PFMBMEM(vf_number), i);

	/* Acknowledge the message and release buffer */
	IXGBE_WRITE_REG(hw, IXGBE_PFMAILBOX(vf_number), IXGBE_PFMAILBOX_ACK);

	/* update stats */
	hw->mbx.stats.msgs_rx++;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
/**
 *  ixgbe_init_mbx_params_pf - set initial values क्रम pf mailbox
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Initializes the hw->mbx काष्ठा to correct values क्रम pf mailbox
 */
व्योम ixgbe_init_mbx_params_pf(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;

	अगर (hw->mac.type != ixgbe_mac_82599EB &&
	    hw->mac.type != ixgbe_mac_X550 &&
	    hw->mac.type != ixgbe_mac_X550EM_x &&
	    hw->mac.type != ixgbe_mac_x550em_a &&
	    hw->mac.type != ixgbe_mac_X540)
		वापस;

	mbx->समयout = 0;
	mbx->usec_delay = 0;

	mbx->stats.msgs_tx = 0;
	mbx->stats.msgs_rx = 0;
	mbx->stats.reqs = 0;
	mbx->stats.acks = 0;
	mbx->stats.rsts = 0;

	mbx->size = IXGBE_VFMAILBOX_SIZE;
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_IOV */

स्थिर काष्ठा ixgbe_mbx_operations mbx_ops_generic = अणु
	.पढ़ो                   = ixgbe_पढ़ो_mbx_pf,
	.ग_लिखो                  = ixgbe_ग_लिखो_mbx_pf,
	.पढ़ो_posted            = ixgbe_पढ़ो_posted_mbx,
	.ग_लिखो_posted           = ixgbe_ग_लिखो_posted_mbx,
	.check_क्रम_msg          = ixgbe_check_क्रम_msg_pf,
	.check_क्रम_ack          = ixgbe_check_क्रम_ack_pf,
	.check_क्रम_rst          = ixgbe_check_क्रम_rst_pf,
पूर्ण;

