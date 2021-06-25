<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश "mbx.h"
#समावेश "ixgbevf.h"

/**
 *  ixgbevf_poll_क्रम_msg - Wait क्रम message notअगरication
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  वापसs 0 अगर it successfully received a message notअगरication
 **/
अटल s32 ixgbevf_poll_क्रम_msg(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;
	पूर्णांक countकरोwn = mbx->समयout;

	जबतक (countकरोwn && mbx->ops.check_क्रम_msg(hw)) अणु
		countकरोwn--;
		udelay(mbx->udelay);
	पूर्ण

	/* अगर we failed, all future posted messages fail until reset */
	अगर (!countकरोwn)
		mbx->समयout = 0;

	वापस countकरोwn ? 0 : IXGBE_ERR_MBX;
पूर्ण

/**
 *  ixgbevf_poll_क्रम_ack - Wait क्रम message acknowledgment
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  वापसs 0 अगर it successfully received a message acknowledgment
 **/
अटल s32 ixgbevf_poll_क्रम_ack(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;
	पूर्णांक countकरोwn = mbx->समयout;

	जबतक (countकरोwn && mbx->ops.check_क्रम_ack(hw)) अणु
		countकरोwn--;
		udelay(mbx->udelay);
	पूर्ण

	/* अगर we failed, all future posted messages fail until reset */
	अगर (!countकरोwn)
		mbx->समयout = 0;

	वापस countकरोwn ? 0 : IXGBE_ERR_MBX;
पूर्ण

/**
 *  ixgbevf_पढ़ो_posted_mbx - Wait क्रम message notअगरication and receive message
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *
 *  वापसs 0 अगर it successfully received a message notअगरication and
 *  copied it पूर्णांकo the receive buffer.
 **/
अटल s32 ixgbevf_पढ़ो_posted_mbx(काष्ठा ixgbe_hw *hw, u32 *msg, u16 size)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;
	s32 ret_val = IXGBE_ERR_MBX;

	अगर (!mbx->ops.पढ़ो)
		जाओ out;

	ret_val = ixgbevf_poll_क्रम_msg(hw);

	/* अगर ack received पढ़ो message, otherwise we समयd out */
	अगर (!ret_val)
		ret_val = mbx->ops.पढ़ो(hw, msg, size);
out:
	वापस ret_val;
पूर्ण

/**
 *  ixgbevf_ग_लिखो_posted_mbx - Write a message to the mailbox, रुको क्रम ack
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *
 *  वापसs 0 अगर it successfully copied message पूर्णांकo the buffer and
 *  received an ack to that message within delay * समयout period
 **/
अटल s32 ixgbevf_ग_लिखो_posted_mbx(काष्ठा ixgbe_hw *hw, u32 *msg, u16 size)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;
	s32 ret_val = IXGBE_ERR_MBX;

	/* निकास अगर either we can't write or there isn't a defined समयout */
	अगर (!mbx->ops.ग_लिखो || !mbx->समयout)
		जाओ out;

	/* send msg */
	ret_val = mbx->ops.ग_लिखो(hw, msg, size);

	/* अगर msg sent रुको until we receive an ack */
	अगर (!ret_val)
		ret_val = ixgbevf_poll_क्रम_ack(hw);
out:
	वापस ret_val;
पूर्ण

/**
 *  ixgbevf_पढ़ो_v2p_mailbox - पढ़ो v2p mailbox
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  This function is used to पढ़ो the v2p mailbox without losing the पढ़ो to
 *  clear status bits.
 **/
अटल u32 ixgbevf_पढ़ो_v2p_mailbox(काष्ठा ixgbe_hw *hw)
अणु
	u32 v2p_mailbox = IXGBE_READ_REG(hw, IXGBE_VFMAILBOX);

	v2p_mailbox |= hw->mbx.v2p_mailbox;
	hw->mbx.v2p_mailbox |= v2p_mailbox & IXGBE_VFMAILBOX_R2C_BITS;

	वापस v2p_mailbox;
पूर्ण

/**
 *  ixgbevf_check_क्रम_bit_vf - Determine अगर a status bit was set
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mask: biपंचांगask क्रम bits to be tested and cleared
 *
 *  This function is used to check क्रम the पढ़ो to clear bits within
 *  the V2P mailbox.
 **/
अटल s32 ixgbevf_check_क्रम_bit_vf(काष्ठा ixgbe_hw *hw, u32 mask)
अणु
	u32 v2p_mailbox = ixgbevf_पढ़ो_v2p_mailbox(hw);
	s32 ret_val = IXGBE_ERR_MBX;

	अगर (v2p_mailbox & mask)
		ret_val = 0;

	hw->mbx.v2p_mailbox &= ~mask;

	वापस ret_val;
पूर्ण

/**
 *  ixgbevf_check_क्रम_msg_vf - checks to see अगर the PF has sent mail
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  वापसs 0 अगर the PF has set the Status bit or अन्यथा ERR_MBX
 **/
अटल s32 ixgbevf_check_क्रम_msg_vf(काष्ठा ixgbe_hw *hw)
अणु
	s32 ret_val = IXGBE_ERR_MBX;

	अगर (!ixgbevf_check_क्रम_bit_vf(hw, IXGBE_VFMAILBOX_PFSTS)) अणु
		ret_val = 0;
		hw->mbx.stats.reqs++;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  ixgbevf_check_क्रम_ack_vf - checks to see अगर the PF has ACK'd
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  वापसs 0 अगर the PF has set the ACK bit or अन्यथा ERR_MBX
 **/
अटल s32 ixgbevf_check_क्रम_ack_vf(काष्ठा ixgbe_hw *hw)
अणु
	s32 ret_val = IXGBE_ERR_MBX;

	अगर (!ixgbevf_check_क्रम_bit_vf(hw, IXGBE_VFMAILBOX_PFACK)) अणु
		ret_val = 0;
		hw->mbx.stats.acks++;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  ixgbevf_check_क्रम_rst_vf - checks to see अगर the PF has reset
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  वापसs true अगर the PF has set the reset करोne bit or अन्यथा false
 **/
अटल s32 ixgbevf_check_क्रम_rst_vf(काष्ठा ixgbe_hw *hw)
अणु
	s32 ret_val = IXGBE_ERR_MBX;

	अगर (!ixgbevf_check_क्रम_bit_vf(hw, (IXGBE_VFMAILBOX_RSTD |
					   IXGBE_VFMAILBOX_RSTI))) अणु
		ret_val = 0;
		hw->mbx.stats.rsts++;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  ixgbevf_obtain_mbx_lock_vf - obtain mailbox lock
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  वापस 0 अगर we obtained the mailbox lock
 **/
अटल s32 ixgbevf_obtain_mbx_lock_vf(काष्ठा ixgbe_hw *hw)
अणु
	s32 ret_val = IXGBE_ERR_MBX;

	/* Take ownership of the buffer */
	IXGBE_WRITE_REG(hw, IXGBE_VFMAILBOX, IXGBE_VFMAILBOX_VFU);

	/* reserve mailbox क्रम VF use */
	अगर (ixgbevf_पढ़ो_v2p_mailbox(hw) & IXGBE_VFMAILBOX_VFU)
		ret_val = 0;

	वापस ret_val;
पूर्ण

/**
 *  ixgbevf_ग_लिखो_mbx_vf - Write a message to the mailbox
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *
 *  वापसs 0 अगर it successfully copied message पूर्णांकo the buffer
 **/
अटल s32 ixgbevf_ग_लिखो_mbx_vf(काष्ठा ixgbe_hw *hw, u32 *msg, u16 size)
अणु
	s32 ret_val;
	u16 i;

	/* lock the mailbox to prevent PF/VF race condition */
	ret_val = ixgbevf_obtain_mbx_lock_vf(hw);
	अगर (ret_val)
		जाओ out_no_ग_लिखो;

	/* flush msg and acks as we are overwriting the message buffer */
	ixgbevf_check_क्रम_msg_vf(hw);
	ixgbevf_check_क्रम_ack_vf(hw);

	/* copy the caller specअगरied message to the mailbox memory buffer */
	क्रम (i = 0; i < size; i++)
		IXGBE_WRITE_REG_ARRAY(hw, IXGBE_VFMBMEM, i, msg[i]);

	/* update stats */
	hw->mbx.stats.msgs_tx++;

	/* Drop VFU and पूर्णांकerrupt the PF to tell it a message has been sent */
	IXGBE_WRITE_REG(hw, IXGBE_VFMAILBOX, IXGBE_VFMAILBOX_REQ);

out_no_ग_लिखो:
	वापस ret_val;
पूर्ण

/**
 *  ixgbevf_पढ़ो_mbx_vf - Reads a message from the inbox पूर्णांकended क्रम VF
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @msg: The message buffer
 *  @size: Length of buffer
 *
 *  वापसs 0 अगर it successfully पढ़ो message from buffer
 **/
अटल s32 ixgbevf_पढ़ो_mbx_vf(काष्ठा ixgbe_hw *hw, u32 *msg, u16 size)
अणु
	s32 ret_val = 0;
	u16 i;

	/* lock the mailbox to prevent PF/VF race condition */
	ret_val = ixgbevf_obtain_mbx_lock_vf(hw);
	अगर (ret_val)
		जाओ out_no_पढ़ो;

	/* copy the message from the mailbox memory buffer */
	क्रम (i = 0; i < size; i++)
		msg[i] = IXGBE_READ_REG_ARRAY(hw, IXGBE_VFMBMEM, i);

	/* Acknowledge receipt and release mailbox, then we're करोne */
	IXGBE_WRITE_REG(hw, IXGBE_VFMAILBOX, IXGBE_VFMAILBOX_ACK);

	/* update stats */
	hw->mbx.stats.msgs_rx++;

out_no_पढ़ो:
	वापस ret_val;
पूर्ण

/**
 *  ixgbevf_init_mbx_params_vf - set initial values क्रम VF mailbox
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Initializes the hw->mbx काष्ठा to correct values क्रम VF mailbox
 */
अटल s32 ixgbevf_init_mbx_params_vf(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;

	/* start mailbox as समयd out and let the reset_hw call set the समयout
	 * value to begin communications
	 */
	mbx->समयout = 0;
	mbx->udelay = IXGBE_VF_MBX_INIT_DELAY;

	mbx->size = IXGBE_VFMAILBOX_SIZE;

	mbx->stats.msgs_tx = 0;
	mbx->stats.msgs_rx = 0;
	mbx->stats.reqs = 0;
	mbx->stats.acks = 0;
	mbx->stats.rsts = 0;

	वापस 0;
पूर्ण

स्थिर काष्ठा ixgbe_mbx_operations ixgbevf_mbx_ops = अणु
	.init_params	= ixgbevf_init_mbx_params_vf,
	.पढ़ो		= ixgbevf_पढ़ो_mbx_vf,
	.ग_लिखो		= ixgbevf_ग_लिखो_mbx_vf,
	.पढ़ो_posted	= ixgbevf_पढ़ो_posted_mbx,
	.ग_लिखो_posted	= ixgbevf_ग_लिखो_posted_mbx,
	.check_क्रम_msg	= ixgbevf_check_क्रम_msg_vf,
	.check_क्रम_ack	= ixgbevf_check_क्रम_ack_vf,
	.check_क्रम_rst	= ixgbevf_check_क्रम_rst_vf,
पूर्ण;

/* Mailbox operations when running on Hyper-V.
 * On Hyper-V, PF/VF communication is not through the
 * hardware mailbox; this communication is through
 * a software mediated path.
 * Most mail box operations are noop जबतक running on
 * Hyper-V.
 */
स्थिर काष्ठा ixgbe_mbx_operations ixgbevf_hv_mbx_ops = अणु
	.init_params	= ixgbevf_init_mbx_params_vf,
	.check_क्रम_rst	= ixgbevf_check_क्रम_rst_vf,
पूर्ण;
