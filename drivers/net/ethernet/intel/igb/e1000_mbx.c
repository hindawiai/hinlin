<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2007 - 2018 Intel Corporation. */

#समावेश "e1000_mbx.h"

/**
 *  igb_पढ़ो_mbx - Reads a message from the mailbox
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *  @mbx_id: id of mailbox to पढ़ो
 *  @unlock: skip locking or not
 *
 *  वापसs SUCCESS अगर it successfully पढ़ो message from buffer
 **/
s32 igb_पढ़ो_mbx(काष्ठा e1000_hw *hw, u32 *msg, u16 size, u16 mbx_id,
		 bool unlock)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	s32 ret_val = -E1000_ERR_MBX;

	/* limit पढ़ो to size of mailbox */
	अगर (size > mbx->size)
		size = mbx->size;

	अगर (mbx->ops.पढ़ो)
		ret_val = mbx->ops.पढ़ो(hw, msg, size, mbx_id, unlock);

	वापस ret_val;
पूर्ण

/**
 *  igb_ग_लिखो_mbx - Write a message to the mailbox
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *  @mbx_id: id of mailbox to ग_लिखो
 *
 *  वापसs SUCCESS अगर it successfully copied message पूर्णांकo the buffer
 **/
s32 igb_ग_लिखो_mbx(काष्ठा e1000_hw *hw, u32 *msg, u16 size, u16 mbx_id)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	s32 ret_val = 0;

	अगर (size > mbx->size)
		ret_val = -E1000_ERR_MBX;

	अन्यथा अगर (mbx->ops.ग_लिखो)
		ret_val = mbx->ops.ग_लिखो(hw, msg, size, mbx_id);

	वापस ret_val;
पूर्ण

/**
 *  igb_check_क्रम_msg - checks to see अगर someone sent us mail
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mbx_id: id of mailbox to check
 *
 *  वापसs SUCCESS अगर the Status bit was found or अन्यथा ERR_MBX
 **/
s32 igb_check_क्रम_msg(काष्ठा e1000_hw *hw, u16 mbx_id)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	s32 ret_val = -E1000_ERR_MBX;

	अगर (mbx->ops.check_क्रम_msg)
		ret_val = mbx->ops.check_क्रम_msg(hw, mbx_id);

	वापस ret_val;
पूर्ण

/**
 *  igb_check_क्रम_ack - checks to see अगर someone sent us ACK
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mbx_id: id of mailbox to check
 *
 *  वापसs SUCCESS अगर the Status bit was found or अन्यथा ERR_MBX
 **/
s32 igb_check_क्रम_ack(काष्ठा e1000_hw *hw, u16 mbx_id)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	s32 ret_val = -E1000_ERR_MBX;

	अगर (mbx->ops.check_क्रम_ack)
		ret_val = mbx->ops.check_क्रम_ack(hw, mbx_id);

	वापस ret_val;
पूर्ण

/**
 *  igb_check_क्रम_rst - checks to see अगर other side has reset
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mbx_id: id of mailbox to check
 *
 *  वापसs SUCCESS अगर the Status bit was found or अन्यथा ERR_MBX
 **/
s32 igb_check_क्रम_rst(काष्ठा e1000_hw *hw, u16 mbx_id)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	s32 ret_val = -E1000_ERR_MBX;

	अगर (mbx->ops.check_क्रम_rst)
		ret_val = mbx->ops.check_क्रम_rst(hw, mbx_id);

	वापस ret_val;
पूर्ण

/**
 *  igb_unlock_mbx - unlock the mailbox
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mbx_id: id of mailbox to check
 *
 *  वापसs SUCCESS अगर the mailbox was unlocked or अन्यथा ERR_MBX
 **/
s32 igb_unlock_mbx(काष्ठा e1000_hw *hw, u16 mbx_id)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	s32 ret_val = -E1000_ERR_MBX;

	अगर (mbx->ops.unlock)
		ret_val = mbx->ops.unlock(hw, mbx_id);

	वापस ret_val;
पूर्ण

/**
 *  igb_poll_क्रम_msg - Wait क्रम message notअगरication
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mbx_id: id of mailbox to ग_लिखो
 *
 *  वापसs SUCCESS अगर it successfully received a message notअगरication
 **/
अटल s32 igb_poll_क्रम_msg(काष्ठा e1000_hw *hw, u16 mbx_id)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	पूर्णांक countकरोwn = mbx->समयout;

	अगर (!countकरोwn || !mbx->ops.check_क्रम_msg)
		जाओ out;

	जबतक (countकरोwn && mbx->ops.check_क्रम_msg(hw, mbx_id)) अणु
		countकरोwn--;
		अगर (!countकरोwn)
			अवरोध;
		udelay(mbx->usec_delay);
	पूर्ण

	/* अगर we failed, all future posted messages fail until reset */
	अगर (!countकरोwn)
		mbx->समयout = 0;
out:
	वापस countकरोwn ? 0 : -E1000_ERR_MBX;
पूर्ण

/**
 *  igb_poll_क्रम_ack - Wait क्रम message acknowledgement
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mbx_id: id of mailbox to ग_लिखो
 *
 *  वापसs SUCCESS अगर it successfully received a message acknowledgement
 **/
अटल s32 igb_poll_क्रम_ack(काष्ठा e1000_hw *hw, u16 mbx_id)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	पूर्णांक countकरोwn = mbx->समयout;

	अगर (!countकरोwn || !mbx->ops.check_क्रम_ack)
		जाओ out;

	जबतक (countकरोwn && mbx->ops.check_क्रम_ack(hw, mbx_id)) अणु
		countकरोwn--;
		अगर (!countकरोwn)
			अवरोध;
		udelay(mbx->usec_delay);
	पूर्ण

	/* अगर we failed, all future posted messages fail until reset */
	अगर (!countकरोwn)
		mbx->समयout = 0;
out:
	वापस countकरोwn ? 0 : -E1000_ERR_MBX;
पूर्ण

/**
 *  igb_पढ़ो_posted_mbx - Wait क्रम message notअगरication and receive message
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *  @mbx_id: id of mailbox to ग_लिखो
 *
 *  वापसs SUCCESS अगर it successfully received a message notअगरication and
 *  copied it पूर्णांकo the receive buffer.
 **/
अटल s32 igb_पढ़ो_posted_mbx(काष्ठा e1000_hw *hw, u32 *msg, u16 size,
			       u16 mbx_id)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	s32 ret_val = -E1000_ERR_MBX;

	अगर (!mbx->ops.पढ़ो)
		जाओ out;

	ret_val = igb_poll_क्रम_msg(hw, mbx_id);

	अगर (!ret_val)
		ret_val = mbx->ops.पढ़ो(hw, msg, size, mbx_id, true);
out:
	वापस ret_val;
पूर्ण

/**
 *  igb_ग_लिखो_posted_mbx - Write a message to the mailbox, रुको क्रम ack
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *  @mbx_id: id of mailbox to ग_लिखो
 *
 *  वापसs SUCCESS अगर it successfully copied message पूर्णांकo the buffer and
 *  received an ack to that message within delay * समयout period
 **/
अटल s32 igb_ग_लिखो_posted_mbx(काष्ठा e1000_hw *hw, u32 *msg, u16 size,
				u16 mbx_id)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	s32 ret_val = -E1000_ERR_MBX;

	/* निकास अगर either we can't write or there isn't a defined समयout */
	अगर (!mbx->ops.ग_लिखो || !mbx->समयout)
		जाओ out;

	/* send msg */
	ret_val = mbx->ops.ग_लिखो(hw, msg, size, mbx_id);

	/* अगर msg sent रुको until we receive an ack */
	अगर (!ret_val)
		ret_val = igb_poll_क्रम_ack(hw, mbx_id);
out:
	वापस ret_val;
पूर्ण

अटल s32 igb_check_क्रम_bit_pf(काष्ठा e1000_hw *hw, u32 mask)
अणु
	u32 mbvficr = rd32(E1000_MBVFICR);
	s32 ret_val = -E1000_ERR_MBX;

	अगर (mbvficr & mask) अणु
		ret_val = 0;
		wr32(E1000_MBVFICR, mask);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  igb_check_क्रम_msg_pf - checks to see अगर the VF has sent mail
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @vf_number: the VF index
 *
 *  वापसs SUCCESS अगर the VF has set the Status bit or अन्यथा ERR_MBX
 **/
अटल s32 igb_check_क्रम_msg_pf(काष्ठा e1000_hw *hw, u16 vf_number)
अणु
	s32 ret_val = -E1000_ERR_MBX;

	अगर (!igb_check_क्रम_bit_pf(hw, E1000_MBVFICR_VFREQ_VF1 << vf_number)) अणु
		ret_val = 0;
		hw->mbx.stats.reqs++;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  igb_check_क्रम_ack_pf - checks to see अगर the VF has ACKed
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @vf_number: the VF index
 *
 *  वापसs SUCCESS अगर the VF has set the Status bit or अन्यथा ERR_MBX
 **/
अटल s32 igb_check_क्रम_ack_pf(काष्ठा e1000_hw *hw, u16 vf_number)
अणु
	s32 ret_val = -E1000_ERR_MBX;

	अगर (!igb_check_क्रम_bit_pf(hw, E1000_MBVFICR_VFACK_VF1 << vf_number)) अणु
		ret_val = 0;
		hw->mbx.stats.acks++;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  igb_check_क्रम_rst_pf - checks to see अगर the VF has reset
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @vf_number: the VF index
 *
 *  वापसs SUCCESS अगर the VF has set the Status bit or अन्यथा ERR_MBX
 **/
अटल s32 igb_check_क्रम_rst_pf(काष्ठा e1000_hw *hw, u16 vf_number)
अणु
	u32 vflre = rd32(E1000_VFLRE);
	s32 ret_val = -E1000_ERR_MBX;

	अगर (vflre & BIT(vf_number)) अणु
		ret_val = 0;
		wr32(E1000_VFLRE, BIT(vf_number));
		hw->mbx.stats.rsts++;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  igb_obtain_mbx_lock_pf - obtain mailbox lock
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @vf_number: the VF index
 *
 *  वापस SUCCESS अगर we obtained the mailbox lock
 **/
अटल s32 igb_obtain_mbx_lock_pf(काष्ठा e1000_hw *hw, u16 vf_number)
अणु
	s32 ret_val = -E1000_ERR_MBX;
	u32 p2v_mailbox;
	पूर्णांक count = 10;

	करो अणु
		/* Take ownership of the buffer */
		wr32(E1000_P2VMAILBOX(vf_number), E1000_P2VMAILBOX_PFU);

		/* reserve mailbox क्रम vf use */
		p2v_mailbox = rd32(E1000_P2VMAILBOX(vf_number));
		अगर (p2v_mailbox & E1000_P2VMAILBOX_PFU) अणु
			ret_val = 0;
			अवरोध;
		पूर्ण
		udelay(1000);
	पूर्ण जबतक (count-- > 0);

	वापस ret_val;
पूर्ण

/**
 *  igb_release_mbx_lock_pf - release mailbox lock
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @vf_number: the VF index
 *
 *  वापस SUCCESS अगर we released the mailbox lock
 **/
अटल s32 igb_release_mbx_lock_pf(काष्ठा e1000_hw *hw, u16 vf_number)
अणु
	u32 p2v_mailbox;

	/* drop PF lock of mailbox, अगर set */
	p2v_mailbox = rd32(E1000_P2VMAILBOX(vf_number));
	अगर (p2v_mailbox & E1000_P2VMAILBOX_PFU)
		wr32(E1000_P2VMAILBOX(vf_number),
		     p2v_mailbox & ~E1000_P2VMAILBOX_PFU);

	वापस 0;
पूर्ण

/**
 *  igb_ग_लिखो_mbx_pf - Places a message in the mailbox
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *  @vf_number: the VF index
 *
 *  वापसs SUCCESS अगर it successfully copied message पूर्णांकo the buffer
 **/
अटल s32 igb_ग_लिखो_mbx_pf(काष्ठा e1000_hw *hw, u32 *msg, u16 size,
			    u16 vf_number)
अणु
	s32 ret_val;
	u16 i;

	/* lock the mailbox to prevent pf/vf race condition */
	ret_val = igb_obtain_mbx_lock_pf(hw, vf_number);
	अगर (ret_val)
		जाओ out_no_ग_लिखो;

	/* flush msg and acks as we are overwriting the message buffer */
	igb_check_क्रम_msg_pf(hw, vf_number);
	igb_check_क्रम_ack_pf(hw, vf_number);

	/* copy the caller specअगरied message to the mailbox memory buffer */
	क्रम (i = 0; i < size; i++)
		array_wr32(E1000_VMBMEM(vf_number), i, msg[i]);

	/* Interrupt VF to tell it a message has been sent and release buffer*/
	wr32(E1000_P2VMAILBOX(vf_number), E1000_P2VMAILBOX_STS);

	/* update stats */
	hw->mbx.stats.msgs_tx++;

out_no_ग_लिखो:
	वापस ret_val;

पूर्ण

/**
 *  igb_पढ़ो_mbx_pf - Read a message from the mailbox
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *  @vf_number: the VF index
 *  @unlock: unlock the mailbox when करोne?
 *
 *  This function copies a message from the mailbox buffer to the caller's
 *  memory buffer.  The presumption is that the caller knows that there was
 *  a message due to a VF request so no polling क्रम message is needed.
 **/
अटल s32 igb_पढ़ो_mbx_pf(काष्ठा e1000_hw *hw, u32 *msg, u16 size,
			   u16 vf_number, bool unlock)
अणु
	s32 ret_val;
	u16 i;

	/* lock the mailbox to prevent pf/vf race condition */
	ret_val = igb_obtain_mbx_lock_pf(hw, vf_number);
	अगर (ret_val)
		जाओ out_no_पढ़ो;

	/* copy the message to the mailbox memory buffer */
	क्रम (i = 0; i < size; i++)
		msg[i] = array_rd32(E1000_VMBMEM(vf_number), i);

	/* Acknowledge the message and release mailbox lock (or not) */
	अगर (unlock)
		wr32(E1000_P2VMAILBOX(vf_number), E1000_P2VMAILBOX_ACK);
	अन्यथा
		wr32(E1000_P2VMAILBOX(vf_number),
		     E1000_P2VMAILBOX_ACK | E1000_P2VMAILBOX_PFU);

	/* update stats */
	hw->mbx.stats.msgs_rx++;

out_no_पढ़ो:
	वापस ret_val;
पूर्ण

/**
 *  igb_init_mbx_params_pf - set initial values क्रम pf mailbox
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Initializes the hw->mbx काष्ठा to correct values क्रम pf mailbox
 */
s32 igb_init_mbx_params_pf(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;

	mbx->समयout = 0;
	mbx->usec_delay = 0;

	mbx->size = E1000_VFMAILBOX_SIZE;

	mbx->ops.पढ़ो = igb_पढ़ो_mbx_pf;
	mbx->ops.ग_लिखो = igb_ग_लिखो_mbx_pf;
	mbx->ops.पढ़ो_posted = igb_पढ़ो_posted_mbx;
	mbx->ops.ग_लिखो_posted = igb_ग_लिखो_posted_mbx;
	mbx->ops.check_क्रम_msg = igb_check_क्रम_msg_pf;
	mbx->ops.check_क्रम_ack = igb_check_क्रम_ack_pf;
	mbx->ops.check_क्रम_rst = igb_check_क्रम_rst_pf;
	mbx->ops.unlock = igb_release_mbx_lock_pf;

	mbx->stats.msgs_tx = 0;
	mbx->stats.msgs_rx = 0;
	mbx->stats.reqs = 0;
	mbx->stats.acks = 0;
	mbx->stats.rsts = 0;

	वापस 0;
पूर्ण

