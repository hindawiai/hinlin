<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009 - 2018 Intel Corporation. */

#समावेश "vf.h"

अटल s32 e1000_check_क्रम_link_vf(काष्ठा e1000_hw *hw);
अटल s32 e1000_get_link_up_info_vf(काष्ठा e1000_hw *hw, u16 *speed,
				     u16 *duplex);
अटल s32 e1000_init_hw_vf(काष्ठा e1000_hw *hw);
अटल s32 e1000_reset_hw_vf(काष्ठा e1000_hw *hw);

अटल व्योम e1000_update_mc_addr_list_vf(काष्ठा e1000_hw *hw, u8 *,
					 u32, u32, u32);
अटल व्योम e1000_rar_set_vf(काष्ठा e1000_hw *, u8 *, u32);
अटल s32 e1000_पढ़ो_mac_addr_vf(काष्ठा e1000_hw *);
अटल s32 e1000_set_uc_addr_vf(काष्ठा e1000_hw *hw, u32 subcmd, u8 *addr);
अटल s32 e1000_set_vfta_vf(काष्ठा e1000_hw *, u16, bool);

/**
 *  e1000_init_mac_params_vf - Inits MAC params
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
अटल s32 e1000_init_mac_params_vf(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;

	/* VF's have no MTA Registers - PF feature only */
	mac->mta_reg_count = 128;
	/* VF's have no access to RAR entries  */
	mac->rar_entry_count = 1;

	/* Function poपूर्णांकers */
	/* reset */
	mac->ops.reset_hw = e1000_reset_hw_vf;
	/* hw initialization */
	mac->ops.init_hw = e1000_init_hw_vf;
	/* check क्रम link */
	mac->ops.check_क्रम_link = e1000_check_क्रम_link_vf;
	/* link info */
	mac->ops.get_link_up_info = e1000_get_link_up_info_vf;
	/* multicast address update */
	mac->ops.update_mc_addr_list = e1000_update_mc_addr_list_vf;
	/* set mac address */
	mac->ops.rar_set = e1000_rar_set_vf;
	/* पढ़ो mac address */
	mac->ops.पढ़ो_mac_addr = e1000_पढ़ो_mac_addr_vf;
	/* set mac filter */
	mac->ops.set_uc_addr = e1000_set_uc_addr_vf;
	/* set vlan filter table array */
	mac->ops.set_vfta = e1000_set_vfta_vf;

	वापस E1000_SUCCESS;
पूर्ण

/**
 *  e1000_init_function_poपूर्णांकers_vf - Inits function poपूर्णांकers
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
व्योम e1000_init_function_poपूर्णांकers_vf(काष्ठा e1000_hw *hw)
अणु
	hw->mac.ops.init_params = e1000_init_mac_params_vf;
	hw->mbx.ops.init_params = e1000_init_mbx_params_vf;
पूर्ण

/**
 *  e1000_get_link_up_info_vf - Gets link info.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @speed: poपूर्णांकer to 16 bit value to store link speed.
 *  @duplex: poपूर्णांकer to 16 bit value to store duplex.
 *
 *  Since we cannot पढ़ो the PHY and get accurate link info, we must rely upon
 *  the status रेजिस्टर's data which is often stale and inaccurate.
 **/
अटल s32 e1000_get_link_up_info_vf(काष्ठा e1000_hw *hw, u16 *speed,
				     u16 *duplex)
अणु
	s32 status;

	status = er32(STATUS);
	अगर (status & E1000_STATUS_SPEED_1000)
		*speed = SPEED_1000;
	अन्यथा अगर (status & E1000_STATUS_SPEED_100)
		*speed = SPEED_100;
	अन्यथा
		*speed = SPEED_10;

	अगर (status & E1000_STATUS_FD)
		*duplex = FULL_DUPLEX;
	अन्यथा
		*duplex = HALF_DUPLEX;

	वापस E1000_SUCCESS;
पूर्ण

/**
 *  e1000_reset_hw_vf - Resets the HW
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  VF's provide a function level reset. This is करोne using bit 26 of ctrl_reg.
 *  This is all the reset we can perक्रमm on a VF.
 **/
अटल s32 e1000_reset_hw_vf(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	u32 समयout = E1000_VF_INIT_TIMEOUT;
	u32 ret_val = -E1000_ERR_MAC_INIT;
	u32 msgbuf[3];
	u8 *addr = (u8 *)(&msgbuf[1]);
	u32 ctrl;

	/* निश्चित VF queue/पूर्णांकerrupt reset */
	ctrl = er32(CTRL);
	ew32(CTRL, ctrl | E1000_CTRL_RST);

	/* we cannot initialize जबतक the RSTI / RSTD bits are निश्चितed */
	जबतक (!mbx->ops.check_क्रम_rst(hw) && समयout) अणु
		समयout--;
		udelay(5);
	पूर्ण

	अगर (समयout) अणु
		/* mailbox समयout can now become active */
		mbx->समयout = E1000_VF_MBX_INIT_TIMEOUT;

		/* notअगरy PF of VF reset completion */
		msgbuf[0] = E1000_VF_RESET;
		mbx->ops.ग_लिखो_posted(hw, msgbuf, 1);

		mdelay(10);

		/* set our "perm_addr" based on info provided by PF */
		ret_val = mbx->ops.पढ़ो_posted(hw, msgbuf, 3);
		अगर (!ret_val) अणु
			अगर (msgbuf[0] == (E1000_VF_RESET |
					  E1000_VT_MSGTYPE_ACK))
				स_नकल(hw->mac.perm_addr, addr, ETH_ALEN);
			अन्यथा
				ret_val = -E1000_ERR_MAC_INIT;
		पूर्ण
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_init_hw_vf - Inits the HW
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Not much to करो here except clear the PF Reset indication अगर there is one.
 **/
अटल s32 e1000_init_hw_vf(काष्ठा e1000_hw *hw)
अणु
	/* attempt to set and restore our mac address */
	e1000_rar_set_vf(hw, hw->mac.addr, 0);

	वापस E1000_SUCCESS;
पूर्ण

/**
 *  e1000_hash_mc_addr_vf - Generate a multicast hash value
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mc_addr: poपूर्णांकer to a multicast address
 *
 *  Generates a multicast address hash value which is used to determine
 *  the multicast filter table array address and new table value.  See
 *  e1000_mta_set_generic()
 **/
अटल u32 e1000_hash_mc_addr_vf(काष्ठा e1000_hw *hw, u8 *mc_addr)
अणु
	u32 hash_value, hash_mask;
	u8 bit_shअगरt = 0;

	/* Register count multiplied by bits per रेजिस्टर */
	hash_mask = (hw->mac.mta_reg_count * 32) - 1;

	/* The bit_shअगरt is the number of left-shअगरts
	 * where 0xFF would still fall within the hash mask.
	 */
	जबतक (hash_mask >> bit_shअगरt != 0xFF)
		bit_shअगरt++;

	hash_value = hash_mask & (((mc_addr[4] >> (8 - bit_shअगरt)) |
				  (((u16)mc_addr[5]) << bit_shअगरt)));

	वापस hash_value;
पूर्ण

/**
 *  e1000_update_mc_addr_list_vf - Update Multicast addresses
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mc_addr_list: array of multicast addresses to program
 *  @mc_addr_count: number of multicast addresses to program
 *  @rar_used_count: the first RAR रेजिस्टर मुक्त to program
 *  @rar_count: total number of supported Receive Address Registers
 *
 *  Updates the Receive Address Registers and Multicast Table Array.
 *  The caller must have a packed mc_addr_list of multicast addresses.
 *  The parameter rar_count will usually be hw->mac.rar_entry_count
 *  unless there are workarounds that change this.
 **/
अटल व्योम e1000_update_mc_addr_list_vf(काष्ठा e1000_hw *hw,
					 u8 *mc_addr_list, u32 mc_addr_count,
					 u32 rar_used_count, u32 rar_count)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	u32 msgbuf[E1000_VFMAILBOX_SIZE];
	u16 *hash_list = (u16 *)&msgbuf[1];
	u32 hash_value;
	u32 cnt, i;
	s32 ret_val;

	/* Each entry in the list uses 1 16 bit word.  We have 30
	 * 16 bit words available in our HW msg buffer (minus 1 क्रम the
	 * msg type).  That's 30 hash values if we pack 'em right.  If
	 * there are more than 30 MC addresses to add then punt the
	 * extras क्रम now and then add code to handle more than 30 later.
	 * It would be unusual क्रम a server to request that many multi-cast
	 * addresses except क्रम in large enterprise network environments.
	 */

	cnt = (mc_addr_count > 30) ? 30 : mc_addr_count;
	msgbuf[0] = E1000_VF_SET_MULTICAST;
	msgbuf[0] |= cnt << E1000_VT_MSGINFO_SHIFT;

	क्रम (i = 0; i < cnt; i++) अणु
		hash_value = e1000_hash_mc_addr_vf(hw, mc_addr_list);
		hash_list[i] = hash_value & 0x0FFFF;
		mc_addr_list += ETH_ALEN;
	पूर्ण

	ret_val = mbx->ops.ग_लिखो_posted(hw, msgbuf, E1000_VFMAILBOX_SIZE);
	अगर (!ret_val)
		mbx->ops.पढ़ो_posted(hw, msgbuf, 1);
पूर्ण

/**
 *  e1000_set_vfta_vf - Set/Unset vlan filter table address
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @vid: determines the vfta रेजिस्टर and bit to set/unset
 *  @set: अगर true then set bit, अन्यथा clear bit
 **/
अटल s32 e1000_set_vfta_vf(काष्ठा e1000_hw *hw, u16 vid, bool set)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	u32 msgbuf[2];
	s32 err;

	msgbuf[0] = E1000_VF_SET_VLAN;
	msgbuf[1] = vid;
	/* Setting the 8 bit field MSG INFO to true indicates "add" */
	अगर (set)
		msgbuf[0] |= BIT(E1000_VT_MSGINFO_SHIFT);

	mbx->ops.ग_लिखो_posted(hw, msgbuf, 2);

	err = mbx->ops.पढ़ो_posted(hw, msgbuf, 2);

	msgbuf[0] &= ~E1000_VT_MSGTYPE_CTS;

	/* अगर nacked the vlan was rejected */
	अगर (!err && (msgbuf[0] == (E1000_VF_SET_VLAN | E1000_VT_MSGTYPE_NACK)))
		err = -E1000_ERR_MAC_INIT;

	वापस err;
पूर्ण

/**
 *  e1000_rlpml_set_vf - Set the maximum receive packet length
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @max_size: value to assign to max frame size
 **/
व्योम e1000_rlpml_set_vf(काष्ठा e1000_hw *hw, u16 max_size)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	u32 msgbuf[2];
	s32 ret_val;

	msgbuf[0] = E1000_VF_SET_LPE;
	msgbuf[1] = max_size;

	ret_val = mbx->ops.ग_लिखो_posted(hw, msgbuf, 2);
	अगर (!ret_val)
		mbx->ops.पढ़ो_posted(hw, msgbuf, 1);
पूर्ण

/**
 *  e1000_rar_set_vf - set device MAC address
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @addr: poपूर्णांकer to the receive address
 *  @index: receive address array रेजिस्टर
 **/
अटल व्योम e1000_rar_set_vf(काष्ठा e1000_hw *hw, u8 *addr, u32 index)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	u32 msgbuf[3];
	u8 *msg_addr = (u8 *)(&msgbuf[1]);
	s32 ret_val;

	स_रखो(msgbuf, 0, 12);
	msgbuf[0] = E1000_VF_SET_MAC_ADDR;
	स_नकल(msg_addr, addr, ETH_ALEN);
	ret_val = mbx->ops.ग_लिखो_posted(hw, msgbuf, 3);

	अगर (!ret_val)
		ret_val = mbx->ops.पढ़ो_posted(hw, msgbuf, 3);

	msgbuf[0] &= ~E1000_VT_MSGTYPE_CTS;

	/* अगर nacked the address was rejected, use "perm_addr" */
	अगर (!ret_val &&
	    (msgbuf[0] == (E1000_VF_SET_MAC_ADDR | E1000_VT_MSGTYPE_NACK)))
		e1000_पढ़ो_mac_addr_vf(hw);
पूर्ण

/**
 *  e1000_पढ़ो_mac_addr_vf - Read device MAC address
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
अटल s32 e1000_पढ़ो_mac_addr_vf(काष्ठा e1000_hw *hw)
अणु
	स_नकल(hw->mac.addr, hw->mac.perm_addr, ETH_ALEN);

	वापस E1000_SUCCESS;
पूर्ण

/**
 *  e1000_set_uc_addr_vf - Set or clear unicast filters
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @sub_cmd: add or clear filters
 *  @addr: poपूर्णांकer to the filter MAC address
 **/
अटल s32 e1000_set_uc_addr_vf(काष्ठा e1000_hw *hw, u32 sub_cmd, u8 *addr)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	u32 msgbuf[3], msgbuf_chk;
	u8 *msg_addr = (u8 *)(&msgbuf[1]);
	s32 ret_val;

	स_रखो(msgbuf, 0, माप(msgbuf));
	msgbuf[0] |= sub_cmd;
	msgbuf[0] |= E1000_VF_SET_MAC_ADDR;
	msgbuf_chk = msgbuf[0];

	अगर (addr)
		स_नकल(msg_addr, addr, ETH_ALEN);

	ret_val = mbx->ops.ग_लिखो_posted(hw, msgbuf, 3);

	अगर (!ret_val)
		ret_val = mbx->ops.पढ़ो_posted(hw, msgbuf, 3);

	msgbuf[0] &= ~E1000_VT_MSGTYPE_CTS;

	अगर (!ret_val) अणु
		msgbuf[0] &= ~E1000_VT_MSGTYPE_CTS;

		अगर (msgbuf[0] == (msgbuf_chk | E1000_VT_MSGTYPE_NACK))
			वापस -ENOSPC;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_check_क्रम_link_vf - Check क्रम link क्रम a भव पूर्णांकerface
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Checks to see अगर the underlying PF is still talking to the VF and
 *  अगर it is then it reports the link state to the hardware, otherwise
 *  it reports link करोwn and वापसs an error.
 **/
अटल s32 e1000_check_क्रम_link_vf(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mbx_info *mbx = &hw->mbx;
	काष्ठा e1000_mac_info *mac = &hw->mac;
	s32 ret_val = E1000_SUCCESS;
	u32 in_msg = 0;

	/* We only want to run this अगर there has been a rst निश्चितed.
	 * in this हाल that could mean a link change, device reset,
	 * or a भव function reset
	 */

	/* If we were hit with a reset or समयout drop the link */
	अगर (!mbx->ops.check_क्रम_rst(hw) || !mbx->समयout)
		mac->get_link_status = true;

	अगर (!mac->get_link_status)
		जाओ out;

	/* अगर link status is करोwn no poपूर्णांक in checking to see अगर PF is up */
	अगर (!(er32(STATUS) & E1000_STATUS_LU))
		जाओ out;

	/* अगर the पढ़ो failed it could just be a mailbox collision, best रुको
	 * until we are called again and करोn't report an error
	 */
	अगर (mbx->ops.पढ़ो(hw, &in_msg, 1))
		जाओ out;

	/* अगर incoming message isn't clear to send we are रुकोing on response */
	अगर (!(in_msg & E1000_VT_MSGTYPE_CTS)) अणु
		/* msg is not CTS and is NACK we must have lost CTS status */
		अगर (in_msg & E1000_VT_MSGTYPE_NACK)
			ret_val = -E1000_ERR_MAC_INIT;
		जाओ out;
	पूर्ण

	/* the PF is talking, अगर we समयd out in the past we reinit */
	अगर (!mbx->समयout) अणु
		ret_val = -E1000_ERR_MAC_INIT;
		जाओ out;
	पूर्ण

	/* अगर we passed all the tests above then the link is up and we no
	 * दीर्घer need to check क्रम link
	 */
	mac->get_link_status = false;

out:
	वापस ret_val;
पूर्ण

