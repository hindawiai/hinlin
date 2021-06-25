<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश "vf.h"
#समावेश "ixgbevf.h"

/* On Hyper-V, to reset, we need to पढ़ो from this offset
 * from the PCI config space. This is the mechanism used on
 * Hyper-V to support PF/VF communication.
 */
#घोषणा IXGBE_HV_RESET_OFFSET           0x201

अटल अंतरभूत s32 ixgbevf_ग_लिखो_msg_पढ़ो_ack(काष्ठा ixgbe_hw *hw, u32 *msg,
					     u32 *reपंचांगsg, u16 size)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;
	s32 retval = mbx->ops.ग_लिखो_posted(hw, msg, size);

	अगर (retval)
		वापस retval;

	वापस mbx->ops.पढ़ो_posted(hw, reपंचांगsg, size);
पूर्ण

/**
 *  ixgbevf_start_hw_vf - Prepare hardware क्रम Tx/Rx
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Starts the hardware by filling the bus info काष्ठाure and media type, clears
 *  all on chip counters, initializes receive address रेजिस्टरs, multicast
 *  table, VLAN filter table, calls routine to set up link and flow control
 *  settings, and leaves transmit and receive units disabled and uninitialized
 **/
अटल s32 ixgbevf_start_hw_vf(काष्ठा ixgbe_hw *hw)
अणु
	/* Clear adapter stopped flag */
	hw->adapter_stopped = false;

	वापस 0;
पूर्ण

/**
 *  ixgbevf_init_hw_vf - भव function hardware initialization
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Initialize the hardware by resetting the hardware and then starting
 *  the hardware
 **/
अटल s32 ixgbevf_init_hw_vf(काष्ठा ixgbe_hw *hw)
अणु
	s32 status = hw->mac.ops.start_hw(hw);

	hw->mac.ops.get_mac_addr(hw, hw->mac.addr);

	वापस status;
पूर्ण

/**
 *  ixgbevf_reset_hw_vf - Perक्रमms hardware reset
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Resets the hardware by resetting the transmit and receive units, masks and
 *  clears all पूर्णांकerrupts.
 **/
अटल s32 ixgbevf_reset_hw_vf(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;
	u32 समयout = IXGBE_VF_INIT_TIMEOUT;
	s32 ret_val = IXGBE_ERR_INVALID_MAC_ADDR;
	u32 msgbuf[IXGBE_VF_PERMADDR_MSG_LEN];
	u8 *addr = (u8 *)(&msgbuf[1]);

	/* Call adapter stop to disable tx/rx and clear पूर्णांकerrupts */
	hw->mac.ops.stop_adapter(hw);

	/* reset the api version */
	hw->api_version = ixgbe_mbox_api_10;

	IXGBE_WRITE_REG(hw, IXGBE_VFCTRL, IXGBE_CTRL_RST);
	IXGBE_WRITE_FLUSH(hw);

	/* we cannot reset जबतक the RSTI / RSTD bits are निश्चितed */
	जबतक (!mbx->ops.check_क्रम_rst(hw) && समयout) अणु
		समयout--;
		udelay(5);
	पूर्ण

	अगर (!समयout)
		वापस IXGBE_ERR_RESET_FAILED;

	/* mailbox समयout can now become active */
	mbx->समयout = IXGBE_VF_MBX_INIT_TIMEOUT;

	msgbuf[0] = IXGBE_VF_RESET;
	mbx->ops.ग_लिखो_posted(hw, msgbuf, 1);

	mdelay(10);

	/* set our "perm_addr" based on info provided by PF
	 * also set up the mc_filter_type which is piggy backed
	 * on the mac address in word 3
	 */
	ret_val = mbx->ops.पढ़ो_posted(hw, msgbuf, IXGBE_VF_PERMADDR_MSG_LEN);
	अगर (ret_val)
		वापस ret_val;

	/* New versions of the PF may NACK the reset वापस message
	 * to indicate that no MAC address has yet been asचिन्हित क्रम
	 * the VF.
	 */
	अगर (msgbuf[0] != (IXGBE_VF_RESET | IXGBE_VT_MSGTYPE_ACK) &&
	    msgbuf[0] != (IXGBE_VF_RESET | IXGBE_VT_MSGTYPE_NACK))
		वापस IXGBE_ERR_INVALID_MAC_ADDR;

	अगर (msgbuf[0] == (IXGBE_VF_RESET | IXGBE_VT_MSGTYPE_ACK))
		ether_addr_copy(hw->mac.perm_addr, addr);

	hw->mac.mc_filter_type = msgbuf[IXGBE_VF_MC_TYPE_WORD];

	वापस 0;
पूर्ण

/**
 * ixgbevf_hv_reset_hw_vf - reset via Hyper-V
 * @hw: poपूर्णांकer to निजी hardware काष्ठा
 *
 * Hyper-V variant; the VF/PF communication is through the PCI
 * config space.
 */
अटल s32 ixgbevf_hv_reset_hw_vf(काष्ठा ixgbe_hw *hw)
अणु
#अगर IS_ENABLED(CONFIG_PCI_MMCONFIG)
	काष्ठा ixgbevf_adapter *adapter = hw->back;
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++)
		pci_पढ़ो_config_byte(adapter->pdev,
				     (i + IXGBE_HV_RESET_OFFSET),
				     &hw->mac.perm_addr[i]);
	वापस 0;
#अन्यथा
	pr_err("PCI_MMCONFIG needs to be enabled for Hyper-V\n");
	वापस -EOPNOTSUPP;
#पूर्ण_अगर
पूर्ण

/**
 *  ixgbevf_stop_hw_vf - Generic stop Tx/Rx units
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Sets the adapter_stopped flag within ixgbe_hw काष्ठा. Clears पूर्णांकerrupts,
 *  disables transmit and receive units. The adapter_stopped flag is used by
 *  the shared code and drivers to determine अगर the adapter is in a stopped
 *  state and should not touch the hardware.
 **/
अटल s32 ixgbevf_stop_hw_vf(काष्ठा ixgbe_hw *hw)
अणु
	u32 number_of_queues;
	u32 reg_val;
	u16 i;

	/* Set the adapter_stopped flag so other driver functions stop touching
	 * the hardware
	 */
	hw->adapter_stopped = true;

	/* Disable the receive unit by stopped each queue */
	number_of_queues = hw->mac.max_rx_queues;
	क्रम (i = 0; i < number_of_queues; i++) अणु
		reg_val = IXGBE_READ_REG(hw, IXGBE_VFRXDCTL(i));
		अगर (reg_val & IXGBE_RXDCTL_ENABLE) अणु
			reg_val &= ~IXGBE_RXDCTL_ENABLE;
			IXGBE_WRITE_REG(hw, IXGBE_VFRXDCTL(i), reg_val);
		पूर्ण
	पूर्ण

	IXGBE_WRITE_FLUSH(hw);

	/* Clear पूर्णांकerrupt mask to stop from पूर्णांकerrupts being generated */
	IXGBE_WRITE_REG(hw, IXGBE_VTEIMC, IXGBE_VF_IRQ_CLEAR_MASK);

	/* Clear any pending पूर्णांकerrupts */
	IXGBE_READ_REG(hw, IXGBE_VTEICR);

	/* Disable the transmit unit.  Each queue must be disabled. */
	number_of_queues = hw->mac.max_tx_queues;
	क्रम (i = 0; i < number_of_queues; i++) अणु
		reg_val = IXGBE_READ_REG(hw, IXGBE_VFTXDCTL(i));
		अगर (reg_val & IXGBE_TXDCTL_ENABLE) अणु
			reg_val &= ~IXGBE_TXDCTL_ENABLE;
			IXGBE_WRITE_REG(hw, IXGBE_VFTXDCTL(i), reg_val);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbevf_mta_vector - Determines bit-vector in multicast table to set
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mc_addr: the multicast address
 *
 *  Extracts the 12 bits, from a multicast address, to determine which
 *  bit-vector to set in the multicast table. The hardware uses 12 bits, from
 *  incoming Rx multicast addresses, to determine the bit-vector to check in
 *  the MTA. Which of the 4 combination, of 12-bits, the hardware uses is set
 *  by the MO field of the MCSTCTRL. The MO field is set during initialization
 *  to mc_filter_type.
 **/
अटल s32 ixgbevf_mta_vector(काष्ठा ixgbe_hw *hw, u8 *mc_addr)
अणु
	u32 vector = 0;

	चयन (hw->mac.mc_filter_type) अणु
	हाल 0:   /* use bits [47:36] of the address */
		vector = ((mc_addr[4] >> 4) | (((u16)mc_addr[5]) << 4));
		अवरोध;
	हाल 1:   /* use bits [46:35] of the address */
		vector = ((mc_addr[4] >> 3) | (((u16)mc_addr[5]) << 5));
		अवरोध;
	हाल 2:   /* use bits [45:34] of the address */
		vector = ((mc_addr[4] >> 2) | (((u16)mc_addr[5]) << 6));
		अवरोध;
	हाल 3:   /* use bits [43:32] of the address */
		vector = ((mc_addr[4]) | (((u16)mc_addr[5]) << 8));
		अवरोध;
	शेष:  /* Invalid mc_filter_type */
		अवरोध;
	पूर्ण

	/* vector can only be 12-bits or boundary will be exceeded */
	vector &= 0xFFF;
	वापस vector;
पूर्ण

/**
 *  ixgbevf_get_mac_addr_vf - Read device MAC address
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mac_addr: poपूर्णांकer to storage क्रम retrieved MAC address
 **/
अटल s32 ixgbevf_get_mac_addr_vf(काष्ठा ixgbe_hw *hw, u8 *mac_addr)
अणु
	ether_addr_copy(mac_addr, hw->mac.perm_addr);

	वापस 0;
पूर्ण

अटल s32 ixgbevf_set_uc_addr_vf(काष्ठा ixgbe_hw *hw, u32 index, u8 *addr)
अणु
	u32 msgbuf[3], msgbuf_chk;
	u8 *msg_addr = (u8 *)(&msgbuf[1]);
	s32 ret_val;

	स_रखो(msgbuf, 0, माप(msgbuf));
	/* If index is one then this is the start of a new list and needs
	 * indication to the PF so it can करो it's own list management.
	 * If it is zero then that tells the PF to just clear all of
	 * this VF's macvlans and there is no new list.
	 */
	msgbuf[0] |= index << IXGBE_VT_MSGINFO_SHIFT;
	msgbuf[0] |= IXGBE_VF_SET_MACVLAN;
	msgbuf_chk = msgbuf[0];

	अगर (addr)
		ether_addr_copy(msg_addr, addr);

	ret_val = ixgbevf_ग_लिखो_msg_पढ़ो_ack(hw, msgbuf, msgbuf,
					     ARRAY_SIZE(msgbuf));
	अगर (!ret_val) अणु
		msgbuf[0] &= ~IXGBE_VT_MSGTYPE_CTS;

		अगर (msgbuf[0] == (msgbuf_chk | IXGBE_VT_MSGTYPE_NACK))
			वापस -ENOMEM;
	पूर्ण

	वापस ret_val;
पूर्ण

अटल s32 ixgbevf_hv_set_uc_addr_vf(काष्ठा ixgbe_hw *hw, u32 index, u8 *addr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

/**
 * ixgbevf_get_reta_locked - get the RSS redirection table (RETA) contents.
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @reta: buffer to fill with RETA contents.
 * @num_rx_queues: Number of Rx queues configured क्रम this port
 *
 * The "reta" buffer should be big enough to contain 32 रेजिस्टरs.
 *
 * Returns: 0 on success.
 *          अगर API करोesn't support this operation - (-EOPNOTSUPP).
 */
पूर्णांक ixgbevf_get_reta_locked(काष्ठा ixgbe_hw *hw, u32 *reta, पूर्णांक num_rx_queues)
अणु
	पूर्णांक err, i, j;
	u32 msgbuf[IXGBE_VFMAILBOX_SIZE];
	u32 *hw_reta = &msgbuf[1];
	u32 mask = 0;

	/* We have to use a mailbox क्रम 82599 and x540 devices only.
	 * For these devices RETA has 128 entries.
	 * Also these VFs support up to 4 RSS queues. Thereक्रमe PF will compress
	 * 16 RETA entries in each DWORD giving 2 bits to each entry.
	 */
	पूर्णांक dwords = IXGBEVF_82599_RETA_SIZE / 16;

	/* We support the RSS querying क्रम 82599 and x540 devices only.
	 * Thus वापस an error अगर API करोesn't support RETA querying or querying
	 * is not supported क्रम this device type.
	 */
	चयन (hw->api_version) अणु
	हाल ixgbe_mbox_api_14:
	हाल ixgbe_mbox_api_13:
	हाल ixgbe_mbox_api_12:
		अगर (hw->mac.type < ixgbe_mac_X550_vf)
			अवरोध;
		fallthrough;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	msgbuf[0] = IXGBE_VF_GET_RETA;

	err = hw->mbx.ops.ग_लिखो_posted(hw, msgbuf, 1);

	अगर (err)
		वापस err;

	err = hw->mbx.ops.पढ़ो_posted(hw, msgbuf, dwords + 1);

	अगर (err)
		वापस err;

	msgbuf[0] &= ~IXGBE_VT_MSGTYPE_CTS;

	/* If the operation has been refused by a PF वापस -EPERM */
	अगर (msgbuf[0] == (IXGBE_VF_GET_RETA | IXGBE_VT_MSGTYPE_NACK))
		वापस -EPERM;

	/* If we didn't get an ACK there must have been
	 * some sort of mailbox error so we should treat it
	 * as such.
	 */
	अगर (msgbuf[0] != (IXGBE_VF_GET_RETA | IXGBE_VT_MSGTYPE_ACK))
		वापस IXGBE_ERR_MBX;

	/* ixgbevf करोesn't support more than 2 queues at the moment */
	अगर (num_rx_queues > 1)
		mask = 0x1;

	क्रम (i = 0; i < dwords; i++)
		क्रम (j = 0; j < 16; j++)
			reta[i * 16 + j] = (hw_reta[i] >> (2 * j)) & mask;

	वापस 0;
पूर्ण

/**
 * ixgbevf_get_rss_key_locked - get the RSS Ranकरोm Key
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @rss_key: buffer to fill with RSS Hash Key contents.
 *
 * The "rss_key" buffer should be big enough to contain 10 रेजिस्टरs.
 *
 * Returns: 0 on success.
 *          अगर API करोesn't support this operation - (-EOPNOTSUPP).
 */
पूर्णांक ixgbevf_get_rss_key_locked(काष्ठा ixgbe_hw *hw, u8 *rss_key)
अणु
	पूर्णांक err;
	u32 msgbuf[IXGBE_VFMAILBOX_SIZE];

	/* We currently support the RSS Ranकरोm Key retrieval क्रम 82599 and x540
	 * devices only.
	 *
	 * Thus वापस an error अगर API करोesn't support RSS Ranकरोm Key retrieval
	 * or अगर the operation is not supported क्रम this device type.
	 */
	चयन (hw->api_version) अणु
	हाल ixgbe_mbox_api_14:
	हाल ixgbe_mbox_api_13:
	हाल ixgbe_mbox_api_12:
		अगर (hw->mac.type < ixgbe_mac_X550_vf)
			अवरोध;
		fallthrough;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	msgbuf[0] = IXGBE_VF_GET_RSS_KEY;
	err = hw->mbx.ops.ग_लिखो_posted(hw, msgbuf, 1);

	अगर (err)
		वापस err;

	err = hw->mbx.ops.पढ़ो_posted(hw, msgbuf, 11);

	अगर (err)
		वापस err;

	msgbuf[0] &= ~IXGBE_VT_MSGTYPE_CTS;

	/* If the operation has been refused by a PF वापस -EPERM */
	अगर (msgbuf[0] == (IXGBE_VF_GET_RSS_KEY | IXGBE_VT_MSGTYPE_NACK))
		वापस -EPERM;

	/* If we didn't get an ACK there must have been
	 * some sort of mailbox error so we should treat it
	 * as such.
	 */
	अगर (msgbuf[0] != (IXGBE_VF_GET_RSS_KEY | IXGBE_VT_MSGTYPE_ACK))
		वापस IXGBE_ERR_MBX;

	स_नकल(rss_key, msgbuf + 1, IXGBEVF_RSS_HASH_KEY_SIZE);

	वापस 0;
पूर्ण

/**
 *  ixgbevf_set_rar_vf - set device MAC address
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @index: Receive address रेजिस्टर to ग_लिखो
 *  @addr: Address to put पूर्णांकo receive address रेजिस्टर
 *  @vmdq: Unused in this implementation
 **/
अटल s32 ixgbevf_set_rar_vf(काष्ठा ixgbe_hw *hw, u32 index, u8 *addr,
			      u32 vmdq)
अणु
	u32 msgbuf[3];
	u8 *msg_addr = (u8 *)(&msgbuf[1]);
	s32 ret_val;

	स_रखो(msgbuf, 0, माप(msgbuf));
	msgbuf[0] = IXGBE_VF_SET_MAC_ADDR;
	ether_addr_copy(msg_addr, addr);

	ret_val = ixgbevf_ग_लिखो_msg_पढ़ो_ack(hw, msgbuf, msgbuf,
					     ARRAY_SIZE(msgbuf));
	msgbuf[0] &= ~IXGBE_VT_MSGTYPE_CTS;

	/* अगर nacked the address was rejected, use "perm_addr" */
	अगर (!ret_val &&
	    (msgbuf[0] == (IXGBE_VF_SET_MAC_ADDR | IXGBE_VT_MSGTYPE_NACK))) अणु
		ixgbevf_get_mac_addr_vf(hw, hw->mac.addr);
		वापस IXGBE_ERR_MBX;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  ixgbevf_hv_set_rar_vf - set device MAC address Hyper-V variant
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @index: Receive address रेजिस्टर to ग_लिखो
 *  @addr: Address to put पूर्णांकo receive address रेजिस्टर
 *  @vmdq: Unused in this implementation
 *
 * We करोn't really allow setting the device MAC address. However,
 * अगर the address being set is the permanent MAC address we will
 * permit that.
 **/
अटल s32 ixgbevf_hv_set_rar_vf(काष्ठा ixgbe_hw *hw, u32 index, u8 *addr,
				 u32 vmdq)
अणु
	अगर (ether_addr_equal(addr, hw->mac.perm_addr))
		वापस 0;

	वापस -EOPNOTSUPP;
पूर्ण

/**
 *  ixgbevf_update_mc_addr_list_vf - Update Multicast addresses
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @netdev: poपूर्णांकer to net device काष्ठाure
 *
 *  Updates the Multicast Table Array.
 **/
अटल s32 ixgbevf_update_mc_addr_list_vf(काष्ठा ixgbe_hw *hw,
					  काष्ठा net_device *netdev)
अणु
	काष्ठा netdev_hw_addr *ha;
	u32 msgbuf[IXGBE_VFMAILBOX_SIZE];
	u16 *vector_list = (u16 *)&msgbuf[1];
	u32 cnt, i;

	/* Each entry in the list uses 1 16 bit word.  We have 30
	 * 16 bit words available in our HW msg buffer (minus 1 क्रम the
	 * msg type).  That's 30 hash values if we pack 'em right.  If
	 * there are more than 30 MC addresses to add then punt the
	 * extras क्रम now and then add code to handle more than 30 later.
	 * It would be unusual क्रम a server to request that many multi-cast
	 * addresses except क्रम in large enterprise network environments.
	 */

	cnt = netdev_mc_count(netdev);
	अगर (cnt > 30)
		cnt = 30;
	msgbuf[0] = IXGBE_VF_SET_MULTICAST;
	msgbuf[0] |= cnt << IXGBE_VT_MSGINFO_SHIFT;

	i = 0;
	netdev_क्रम_each_mc_addr(ha, netdev) अणु
		अगर (i == cnt)
			अवरोध;
		अगर (is_link_local_ether_addr(ha->addr))
			जारी;

		vector_list[i++] = ixgbevf_mta_vector(hw, ha->addr);
	पूर्ण

	वापस ixgbevf_ग_लिखो_msg_पढ़ो_ack(hw, msgbuf, msgbuf,
			IXGBE_VFMAILBOX_SIZE);
पूर्ण

/**
 * ixgbevf_hv_update_mc_addr_list_vf - stub
 * @hw: unused
 * @netdev: unused
 *
 * Hyper-V variant - just a stub.
 */
अटल s32 ixgbevf_hv_update_mc_addr_list_vf(काष्ठा ixgbe_hw *hw,
					     काष्ठा net_device *netdev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

/**
 *  ixgbevf_update_xcast_mode - Update Multicast mode
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @xcast_mode: new multicast mode
 *
 *  Updates the Multicast Mode of VF.
 **/
अटल s32 ixgbevf_update_xcast_mode(काष्ठा ixgbe_hw *hw, पूर्णांक xcast_mode)
अणु
	u32 msgbuf[2];
	s32 err;

	चयन (hw->api_version) अणु
	हाल ixgbe_mbox_api_12:
		/* promisc पूर्णांकroduced in 1.3 version */
		अगर (xcast_mode == IXGBEVF_XCAST_MODE_PROMISC)
			वापस -EOPNOTSUPP;
		fallthrough;
	हाल ixgbe_mbox_api_14:
	हाल ixgbe_mbox_api_13:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	msgbuf[0] = IXGBE_VF_UPDATE_XCAST_MODE;
	msgbuf[1] = xcast_mode;

	err = ixgbevf_ग_लिखो_msg_पढ़ो_ack(hw, msgbuf, msgbuf,
					 ARRAY_SIZE(msgbuf));
	अगर (err)
		वापस err;

	msgbuf[0] &= ~IXGBE_VT_MSGTYPE_CTS;
	अगर (msgbuf[0] == (IXGBE_VF_UPDATE_XCAST_MODE | IXGBE_VT_MSGTYPE_NACK))
		वापस -EPERM;

	वापस 0;
पूर्ण

/**
 * ixgbevf_hv_update_xcast_mode - stub
 * @hw: unused
 * @xcast_mode: unused
 *
 * Hyper-V variant - just a stub.
 */
अटल s32 ixgbevf_hv_update_xcast_mode(काष्ठा ixgbe_hw *hw, पूर्णांक xcast_mode)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

/**
 *  ixgbevf_set_vfta_vf - Set/Unset VLAN filter table address
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @vlan: 12 bit VLAN ID
 *  @vind: unused by VF drivers
 *  @vlan_on: अगर true then set bit, अन्यथा clear bit
 **/
अटल s32 ixgbevf_set_vfta_vf(काष्ठा ixgbe_hw *hw, u32 vlan, u32 vind,
			       bool vlan_on)
अणु
	u32 msgbuf[2];
	s32 err;

	msgbuf[0] = IXGBE_VF_SET_VLAN;
	msgbuf[1] = vlan;
	/* Setting the 8 bit field MSG INFO to TRUE indicates "add" */
	msgbuf[0] |= vlan_on << IXGBE_VT_MSGINFO_SHIFT;

	err = ixgbevf_ग_लिखो_msg_पढ़ो_ack(hw, msgbuf, msgbuf,
					 ARRAY_SIZE(msgbuf));
	अगर (err)
		जाओ mbx_err;

	/* हटाओ extra bits from the message */
	msgbuf[0] &= ~IXGBE_VT_MSGTYPE_CTS;
	msgbuf[0] &= ~(0xFF << IXGBE_VT_MSGINFO_SHIFT);

	अगर (msgbuf[0] != (IXGBE_VF_SET_VLAN | IXGBE_VT_MSGTYPE_ACK))
		err = IXGBE_ERR_INVALID_ARGUMENT;

mbx_err:
	वापस err;
पूर्ण

/**
 * ixgbevf_hv_set_vfta_vf - * Hyper-V variant - just a stub.
 * @hw: unused
 * @vlan: unused
 * @vind: unused
 * @vlan_on: unused
 */
अटल s32 ixgbevf_hv_set_vfta_vf(काष्ठा ixgbe_hw *hw, u32 vlan, u32 vind,
				  bool vlan_on)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

/**
 *  ixgbevf_setup_mac_link_vf - Setup MAC link settings
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @speed: Unused in this implementation
 *  @स्वतःneg: Unused in this implementation
 *  @स्वतःneg_रुको_to_complete: Unused in this implementation
 *
 *  Do nothing and वापस success.  VF drivers are not allowed to change
 *  global settings.  Maपूर्णांकained क्रम driver compatibility.
 **/
अटल s32 ixgbevf_setup_mac_link_vf(काष्ठा ixgbe_hw *hw,
				     ixgbe_link_speed speed, bool स्वतःneg,
				     bool स्वतःneg_रुको_to_complete)
अणु
	वापस 0;
पूर्ण

/**
 *  ixgbevf_check_mac_link_vf - Get link/speed status
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @speed: poपूर्णांकer to link speed
 *  @link_up: true is link is up, false otherwise
 *  @स्वतःneg_रुको_to_complete: unused
 *
 *  Reads the links रेजिस्टर to determine अगर link is up and the current speed
 **/
अटल s32 ixgbevf_check_mac_link_vf(काष्ठा ixgbe_hw *hw,
				     ixgbe_link_speed *speed,
				     bool *link_up,
				     bool स्वतःneg_रुको_to_complete)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;
	काष्ठा ixgbe_mac_info *mac = &hw->mac;
	s32 ret_val = 0;
	u32 links_reg;
	u32 in_msg = 0;

	/* If we were hit with a reset drop the link */
	अगर (!mbx->ops.check_क्रम_rst(hw) || !mbx->समयout)
		mac->get_link_status = true;

	अगर (!mac->get_link_status)
		जाओ out;

	/* अगर link status is करोwn no poपूर्णांक in checking to see अगर pf is up */
	links_reg = IXGBE_READ_REG(hw, IXGBE_VFLINKS);
	अगर (!(links_reg & IXGBE_LINKS_UP))
		जाओ out;

	/* क्रम SFP+ modules and DA cables on 82599 it can take up to 500usecs
	 * beक्रमe the link status is correct
	 */
	अगर (mac->type == ixgbe_mac_82599_vf) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 5; i++) अणु
			udelay(100);
			links_reg = IXGBE_READ_REG(hw, IXGBE_VFLINKS);

			अगर (!(links_reg & IXGBE_LINKS_UP))
				जाओ out;
		पूर्ण
	पूर्ण

	चयन (links_reg & IXGBE_LINKS_SPEED_82599) अणु
	हाल IXGBE_LINKS_SPEED_10G_82599:
		*speed = IXGBE_LINK_SPEED_10GB_FULL;
		अवरोध;
	हाल IXGBE_LINKS_SPEED_1G_82599:
		*speed = IXGBE_LINK_SPEED_1GB_FULL;
		अवरोध;
	हाल IXGBE_LINKS_SPEED_100_82599:
		*speed = IXGBE_LINK_SPEED_100_FULL;
		अवरोध;
	पूर्ण

	/* अगर the पढ़ो failed it could just be a mailbox collision, best रुको
	 * until we are called again and करोn't report an error
	 */
	अगर (mbx->ops.पढ़ो(hw, &in_msg, 1))
		जाओ out;

	अगर (!(in_msg & IXGBE_VT_MSGTYPE_CTS)) अणु
		/* msg is not CTS and is NACK we must have lost CTS status */
		अगर (in_msg & IXGBE_VT_MSGTYPE_NACK)
			ret_val = -1;
		जाओ out;
	पूर्ण

	/* the pf is talking, अगर we समयd out in the past we reinit */
	अगर (!mbx->समयout) अणु
		ret_val = -1;
		जाओ out;
	पूर्ण

	/* अगर we passed all the tests above then the link is up and we no
	 * दीर्घer need to check क्रम link
	 */
	mac->get_link_status = false;

out:
	*link_up = !mac->get_link_status;
	वापस ret_val;
पूर्ण

/**
 * ixgbevf_hv_check_mac_link_vf - check link
 * @hw: poपूर्णांकer to निजी hardware काष्ठा
 * @speed: poपूर्णांकer to link speed
 * @link_up: true is link is up, false otherwise
 * @स्वतःneg_रुको_to_complete: unused
 *
 * Hyper-V variant; there is no mailbox communication.
 */
अटल s32 ixgbevf_hv_check_mac_link_vf(काष्ठा ixgbe_hw *hw,
					ixgbe_link_speed *speed,
					bool *link_up,
					bool स्वतःneg_रुको_to_complete)
अणु
	काष्ठा ixgbe_mbx_info *mbx = &hw->mbx;
	काष्ठा ixgbe_mac_info *mac = &hw->mac;
	u32 links_reg;

	/* If we were hit with a reset drop the link */
	अगर (!mbx->ops.check_क्रम_rst(hw) || !mbx->समयout)
		mac->get_link_status = true;

	अगर (!mac->get_link_status)
		जाओ out;

	/* अगर link status is करोwn no poपूर्णांक in checking to see अगर pf is up */
	links_reg = IXGBE_READ_REG(hw, IXGBE_VFLINKS);
	अगर (!(links_reg & IXGBE_LINKS_UP))
		जाओ out;

	/* क्रम SFP+ modules and DA cables on 82599 it can take up to 500usecs
	 * beक्रमe the link status is correct
	 */
	अगर (mac->type == ixgbe_mac_82599_vf) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 5; i++) अणु
			udelay(100);
			links_reg = IXGBE_READ_REG(hw, IXGBE_VFLINKS);

			अगर (!(links_reg & IXGBE_LINKS_UP))
				जाओ out;
		पूर्ण
	पूर्ण

	चयन (links_reg & IXGBE_LINKS_SPEED_82599) अणु
	हाल IXGBE_LINKS_SPEED_10G_82599:
		*speed = IXGBE_LINK_SPEED_10GB_FULL;
		अवरोध;
	हाल IXGBE_LINKS_SPEED_1G_82599:
		*speed = IXGBE_LINK_SPEED_1GB_FULL;
		अवरोध;
	हाल IXGBE_LINKS_SPEED_100_82599:
		*speed = IXGBE_LINK_SPEED_100_FULL;
		अवरोध;
	पूर्ण

	/* अगर we passed all the tests above then the link is up and we no
	 * दीर्घer need to check क्रम link
	 */
	mac->get_link_status = false;

out:
	*link_up = !mac->get_link_status;
	वापस 0;
पूर्ण

/**
 *  ixgbevf_set_rlpml_vf - Set the maximum receive packet length
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @max_size: value to assign to max frame size
 **/
अटल s32 ixgbevf_set_rlpml_vf(काष्ठा ixgbe_hw *hw, u16 max_size)
अणु
	u32 msgbuf[2];
	s32 ret_val;

	msgbuf[0] = IXGBE_VF_SET_LPE;
	msgbuf[1] = max_size;

	ret_val = ixgbevf_ग_लिखो_msg_पढ़ो_ack(hw, msgbuf, msgbuf,
					     ARRAY_SIZE(msgbuf));
	अगर (ret_val)
		वापस ret_val;
	अगर ((msgbuf[0] & IXGBE_VF_SET_LPE) &&
	    (msgbuf[0] & IXGBE_VT_MSGTYPE_NACK))
		वापस IXGBE_ERR_MBX;

	वापस 0;
पूर्ण

/**
 * ixgbevf_hv_set_rlpml_vf - Set the maximum receive packet length
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @max_size: value to assign to max frame size
 * Hyper-V variant.
 **/
अटल s32 ixgbevf_hv_set_rlpml_vf(काष्ठा ixgbe_hw *hw, u16 max_size)
अणु
	u32 reg;

	/* If we are on Hyper-V, we implement this functionality
	 * dअगरferently.
	 */
	reg =  IXGBE_READ_REG(hw, IXGBE_VFRXDCTL(0));
	/* CRC == 4 */
	reg |= ((max_size + 4) | IXGBE_RXDCTL_RLPML_EN);
	IXGBE_WRITE_REG(hw, IXGBE_VFRXDCTL(0), reg);

	वापस 0;
पूर्ण

/**
 *  ixgbevf_negotiate_api_version_vf - Negotiate supported API version
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @api: पूर्णांकeger containing requested API version
 **/
अटल पूर्णांक ixgbevf_negotiate_api_version_vf(काष्ठा ixgbe_hw *hw, पूर्णांक api)
अणु
	पूर्णांक err;
	u32 msg[3];

	/* Negotiate the mailbox API version */
	msg[0] = IXGBE_VF_API_NEGOTIATE;
	msg[1] = api;
	msg[2] = 0;

	err = ixgbevf_ग_लिखो_msg_पढ़ो_ack(hw, msg, msg, ARRAY_SIZE(msg));
	अगर (!err) अणु
		msg[0] &= ~IXGBE_VT_MSGTYPE_CTS;

		/* Store value and वापस 0 on success */
		अगर (msg[0] == (IXGBE_VF_API_NEGOTIATE | IXGBE_VT_MSGTYPE_ACK)) अणु
			hw->api_version = api;
			वापस 0;
		पूर्ण

		err = IXGBE_ERR_INVALID_ARGUMENT;
	पूर्ण

	वापस err;
पूर्ण

/**
 *  ixgbevf_hv_negotiate_api_version_vf - Negotiate supported API version
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @api: पूर्णांकeger containing requested API version
 *  Hyper-V version - only ixgbe_mbox_api_10 supported.
 **/
अटल पूर्णांक ixgbevf_hv_negotiate_api_version_vf(काष्ठा ixgbe_hw *hw, पूर्णांक api)
अणु
	/* Hyper-V only supports api version ixgbe_mbox_api_10 */
	अगर (api != ixgbe_mbox_api_10)
		वापस IXGBE_ERR_INVALID_ARGUMENT;

	वापस 0;
पूर्ण

पूर्णांक ixgbevf_get_queues(काष्ठा ixgbe_hw *hw, अचिन्हित पूर्णांक *num_tcs,
		       अचिन्हित पूर्णांक *शेष_tc)
अणु
	पूर्णांक err;
	u32 msg[5];

	/* करो nothing अगर API करोesn't support ixgbevf_get_queues */
	चयन (hw->api_version) अणु
	हाल ixgbe_mbox_api_11:
	हाल ixgbe_mbox_api_12:
	हाल ixgbe_mbox_api_13:
	हाल ixgbe_mbox_api_14:
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	/* Fetch queue configuration from the PF */
	msg[0] = IXGBE_VF_GET_QUEUE;
	msg[1] = msg[2] = msg[3] = msg[4] = 0;

	err = ixgbevf_ग_लिखो_msg_पढ़ो_ack(hw, msg, msg, ARRAY_SIZE(msg));
	अगर (!err) अणु
		msg[0] &= ~IXGBE_VT_MSGTYPE_CTS;

		/* अगर we we didn't get an ACK there must have been
		 * some sort of mailbox error so we should treat it
		 * as such
		 */
		अगर (msg[0] != (IXGBE_VF_GET_QUEUE | IXGBE_VT_MSGTYPE_ACK))
			वापस IXGBE_ERR_MBX;

		/* record and validate values from message */
		hw->mac.max_tx_queues = msg[IXGBE_VF_TX_QUEUES];
		अगर (hw->mac.max_tx_queues == 0 ||
		    hw->mac.max_tx_queues > IXGBE_VF_MAX_TX_QUEUES)
			hw->mac.max_tx_queues = IXGBE_VF_MAX_TX_QUEUES;

		hw->mac.max_rx_queues = msg[IXGBE_VF_RX_QUEUES];
		अगर (hw->mac.max_rx_queues == 0 ||
		    hw->mac.max_rx_queues > IXGBE_VF_MAX_RX_QUEUES)
			hw->mac.max_rx_queues = IXGBE_VF_MAX_RX_QUEUES;

		*num_tcs = msg[IXGBE_VF_TRANS_VLAN];
		/* in हाल of unknown state assume we cannot tag frames */
		अगर (*num_tcs > hw->mac.max_rx_queues)
			*num_tcs = 1;

		*शेष_tc = msg[IXGBE_VF_DEF_QUEUE];
		/* शेष to queue 0 on out-of-bounds queue number */
		अगर (*शेष_tc >= hw->mac.max_tx_queues)
			*शेष_tc = 0;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा ixgbe_mac_operations ixgbevf_mac_ops = अणु
	.init_hw		= ixgbevf_init_hw_vf,
	.reset_hw		= ixgbevf_reset_hw_vf,
	.start_hw		= ixgbevf_start_hw_vf,
	.get_mac_addr		= ixgbevf_get_mac_addr_vf,
	.stop_adapter		= ixgbevf_stop_hw_vf,
	.setup_link		= ixgbevf_setup_mac_link_vf,
	.check_link		= ixgbevf_check_mac_link_vf,
	.negotiate_api_version	= ixgbevf_negotiate_api_version_vf,
	.set_rar		= ixgbevf_set_rar_vf,
	.update_mc_addr_list	= ixgbevf_update_mc_addr_list_vf,
	.update_xcast_mode	= ixgbevf_update_xcast_mode,
	.set_uc_addr		= ixgbevf_set_uc_addr_vf,
	.set_vfta		= ixgbevf_set_vfta_vf,
	.set_rlpml		= ixgbevf_set_rlpml_vf,
पूर्ण;

अटल स्थिर काष्ठा ixgbe_mac_operations ixgbevf_hv_mac_ops = अणु
	.init_hw		= ixgbevf_init_hw_vf,
	.reset_hw		= ixgbevf_hv_reset_hw_vf,
	.start_hw		= ixgbevf_start_hw_vf,
	.get_mac_addr		= ixgbevf_get_mac_addr_vf,
	.stop_adapter		= ixgbevf_stop_hw_vf,
	.setup_link		= ixgbevf_setup_mac_link_vf,
	.check_link		= ixgbevf_hv_check_mac_link_vf,
	.negotiate_api_version	= ixgbevf_hv_negotiate_api_version_vf,
	.set_rar		= ixgbevf_hv_set_rar_vf,
	.update_mc_addr_list	= ixgbevf_hv_update_mc_addr_list_vf,
	.update_xcast_mode	= ixgbevf_hv_update_xcast_mode,
	.set_uc_addr		= ixgbevf_hv_set_uc_addr_vf,
	.set_vfta		= ixgbevf_hv_set_vfta_vf,
	.set_rlpml		= ixgbevf_hv_set_rlpml_vf,
पूर्ण;

स्थिर काष्ठा ixgbevf_info ixgbevf_82599_vf_info = अणु
	.mac = ixgbe_mac_82599_vf,
	.mac_ops = &ixgbevf_mac_ops,
पूर्ण;

स्थिर काष्ठा ixgbevf_info ixgbevf_82599_vf_hv_info = अणु
	.mac = ixgbe_mac_82599_vf,
	.mac_ops = &ixgbevf_hv_mac_ops,
पूर्ण;

स्थिर काष्ठा ixgbevf_info ixgbevf_X540_vf_info = अणु
	.mac = ixgbe_mac_X540_vf,
	.mac_ops = &ixgbevf_mac_ops,
पूर्ण;

स्थिर काष्ठा ixgbevf_info ixgbevf_X540_vf_hv_info = अणु
	.mac = ixgbe_mac_X540_vf,
	.mac_ops = &ixgbevf_hv_mac_ops,
पूर्ण;

स्थिर काष्ठा ixgbevf_info ixgbevf_X550_vf_info = अणु
	.mac = ixgbe_mac_X550_vf,
	.mac_ops = &ixgbevf_mac_ops,
पूर्ण;

स्थिर काष्ठा ixgbevf_info ixgbevf_X550_vf_hv_info = अणु
	.mac = ixgbe_mac_X550_vf,
	.mac_ops = &ixgbevf_hv_mac_ops,
पूर्ण;

स्थिर काष्ठा ixgbevf_info ixgbevf_X550EM_x_vf_info = अणु
	.mac = ixgbe_mac_X550EM_x_vf,
	.mac_ops = &ixgbevf_mac_ops,
पूर्ण;

स्थिर काष्ठा ixgbevf_info ixgbevf_X550EM_x_vf_hv_info = अणु
	.mac = ixgbe_mac_X550EM_x_vf,
	.mac_ops = &ixgbevf_hv_mac_ops,
पूर्ण;

स्थिर काष्ठा ixgbevf_info ixgbevf_x550em_a_vf_info = अणु
	.mac = ixgbe_mac_x550em_a_vf,
	.mac_ops = &ixgbevf_mac_ops,
पूर्ण;
