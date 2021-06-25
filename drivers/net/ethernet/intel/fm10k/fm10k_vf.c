<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2019 Intel Corporation. */

#समावेश "fm10k_vf.h"

/**
 *  fm10k_stop_hw_vf - Stop Tx/Rx units
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 **/
अटल s32 fm10k_stop_hw_vf(काष्ठा fm10k_hw *hw)
अणु
	u8 *perm_addr = hw->mac.perm_addr;
	u32 bal = 0, bah = 0, tdlen;
	s32 err;
	u16 i;

	/* we need to disable the queues beक्रमe taking further steps */
	err = fm10k_stop_hw_generic(hw);
	अगर (err && err != FM10K_ERR_REQUESTS_PENDING)
		वापस err;

	/* If permanent address is set then we need to restore it */
	अगर (is_valid_ether_addr(perm_addr)) अणु
		bal = (((u32)perm_addr[3]) << 24) |
		      (((u32)perm_addr[4]) << 16) |
		      (((u32)perm_addr[5]) << 8);
		bah = (((u32)0xFF)	   << 24) |
		      (((u32)perm_addr[0]) << 16) |
		      (((u32)perm_addr[1]) << 8) |
		       ((u32)perm_addr[2]);
	पूर्ण

	/* restore शेष itr_scale क्रम next VF initialization */
	tdlen = hw->mac.itr_scale << FM10K_TDLEN_ITR_SCALE_SHIFT;

	/* The queues have alपढ़ोy been disabled so we just need to
	 * update their base address रेजिस्टरs
	 */
	क्रम (i = 0; i < hw->mac.max_queues; i++) अणु
		fm10k_ग_लिखो_reg(hw, FM10K_TDBAL(i), bal);
		fm10k_ग_लिखो_reg(hw, FM10K_TDBAH(i), bah);
		fm10k_ग_लिखो_reg(hw, FM10K_RDBAL(i), bal);
		fm10k_ग_लिखो_reg(hw, FM10K_RDBAH(i), bah);
		/* Restore ITR scale in software-defined mechanism in TDLEN
		 * क्रम next VF initialization. See definition of
		 * FM10K_TDLEN_ITR_SCALE_SHIFT क्रम more details on the use of
		 * TDLEN here.
		 */
		fm10k_ग_लिखो_reg(hw, FM10K_TDLEN(i), tdlen);
	पूर्ण

	वापस err;
पूर्ण

/**
 *  fm10k_reset_hw_vf - VF hardware reset
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  This function should वापस the hardware to a state similar to the
 *  one it is in after just being initialized.
 **/
अटल s32 fm10k_reset_hw_vf(काष्ठा fm10k_hw *hw)
अणु
	s32 err;

	/* shut करोwn queues we own and reset DMA configuration */
	err = fm10k_stop_hw_vf(hw);
	अगर (err == FM10K_ERR_REQUESTS_PENDING)
		hw->mac.reset_जबतक_pending++;
	अन्यथा अगर (err)
		वापस err;

	/* Inititate VF reset */
	fm10k_ग_लिखो_reg(hw, FM10K_VFCTRL, FM10K_VFCTRL_RST);

	/* Flush ग_लिखो and allow 100us क्रम reset to complete */
	fm10k_ग_लिखो_flush(hw);
	udelay(FM10K_RESET_TIMEOUT);

	/* Clear reset bit and verअगरy it was cleared */
	fm10k_ग_लिखो_reg(hw, FM10K_VFCTRL, 0);
	अगर (fm10k_पढ़ो_reg(hw, FM10K_VFCTRL) & FM10K_VFCTRL_RST)
		वापस FM10K_ERR_RESET_FAILED;

	वापस 0;
पूर्ण

/**
 *  fm10k_init_hw_vf - VF hardware initialization
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 **/
अटल s32 fm10k_init_hw_vf(काष्ठा fm10k_hw *hw)
अणु
	u32 tqdloc, tqdloc0 = ~fm10k_पढ़ो_reg(hw, FM10K_TQDLOC(0));
	s32 err;
	u16 i;

	/* verअगरy we have at least 1 queue */
	अगर (!~fm10k_पढ़ो_reg(hw, FM10K_TXQCTL(0)) ||
	    !~fm10k_पढ़ो_reg(hw, FM10K_RXQCTL(0))) अणु
		err = FM10K_ERR_NO_RESOURCES;
		जाओ reset_max_queues;
	पूर्ण

	/* determine how many queues we have */
	क्रम (i = 1; tqdloc0 && (i < FM10K_MAX_QUEUES_POOL); i++) अणु
		/* verअगरy the Descriptor cache offsets are increasing */
		tqdloc = ~fm10k_पढ़ो_reg(hw, FM10K_TQDLOC(i));
		अगर (!tqdloc || (tqdloc == tqdloc0))
			अवरोध;

		/* check to verअगरy the PF करोesn't own any of our queues */
		अगर (!~fm10k_पढ़ो_reg(hw, FM10K_TXQCTL(i)) ||
		    !~fm10k_पढ़ो_reg(hw, FM10K_RXQCTL(i)))
			अवरोध;
	पूर्ण

	/* shut करोwn queues we own and reset DMA configuration */
	err = fm10k_disable_queues_generic(hw, i);
	अगर (err)
		जाओ reset_max_queues;

	/* record maximum queue count */
	hw->mac.max_queues = i;

	/* fetch शेष VLAN and ITR scale */
	hw->mac.शेष_vid = (fm10k_पढ़ो_reg(hw, FM10K_TXQCTL(0)) &
			       FM10K_TXQCTL_VID_MASK) >> FM10K_TXQCTL_VID_SHIFT;
	/* Read the ITR scale from TDLEN. See the definition of
	 * FM10K_TDLEN_ITR_SCALE_SHIFT क्रम more inक्रमmation about how TDLEN is
	 * used here.
	 */
	hw->mac.itr_scale = (fm10k_पढ़ो_reg(hw, FM10K_TDLEN(0)) &
			     FM10K_TDLEN_ITR_SCALE_MASK) >>
			    FM10K_TDLEN_ITR_SCALE_SHIFT;

	वापस 0;

reset_max_queues:
	hw->mac.max_queues = 0;

	वापस err;
पूर्ण

/* This काष्ठाure defines the attibutes to be parsed below */
स्थिर काष्ठा fm10k_tlv_attr fm10k_mac_vlan_msg_attr[] = अणु
	FM10K_TLV_ATTR_U32(FM10K_MAC_VLAN_MSG_VLAN),
	FM10K_TLV_ATTR_BOOL(FM10K_MAC_VLAN_MSG_SET),
	FM10K_TLV_ATTR_MAC_ADDR(FM10K_MAC_VLAN_MSG_MAC),
	FM10K_TLV_ATTR_MAC_ADDR(FM10K_MAC_VLAN_MSG_DEFAULT_MAC),
	FM10K_TLV_ATTR_MAC_ADDR(FM10K_MAC_VLAN_MSG_MULTICAST),
	FM10K_TLV_ATTR_LAST
पूर्ण;

/**
 *  fm10k_update_vlan_vf - Update status of VLAN ID in VLAN filter table
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @vid: VLAN ID to add to table
 *  @vsi: Reserved, should always be 0
 *  @set: Indicates अगर this is a set or clear operation
 *
 *  This function adds or हटाओs the corresponding VLAN ID from the VLAN
 *  filter table क्रम this VF.
 **/
अटल s32 fm10k_update_vlan_vf(काष्ठा fm10k_hw *hw, u32 vid, u8 vsi, bool set)
अणु
	काष्ठा fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[4];

	/* verअगरy the index is not set */
	अगर (vsi)
		वापस FM10K_ERR_PARAM;

	/* clever trick to verअगरy reserved bits in both vid and length */
	अगर ((vid << 16 | vid) >> 28)
		वापस FM10K_ERR_PARAM;

	/* encode set bit पूर्णांकo the VLAN ID */
	अगर (!set)
		vid |= FM10K_VLAN_CLEAR;

	/* generate VLAN request */
	fm10k_tlv_msg_init(msg, FM10K_VF_MSG_ID_MAC_VLAN);
	fm10k_tlv_attr_put_u32(msg, FM10K_MAC_VLAN_MSG_VLAN, vid);

	/* load onto outgoing mailbox */
	वापस mbx->ops.enqueue_tx(hw, mbx, msg);
पूर्ण

/**
 *  fm10k_msg_mac_vlan_vf - Read device MAC address from mailbox message
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @results: Attributes क्रम message
 *  @mbx: unused mailbox data
 *
 *  This function should determine the MAC address क्रम the VF
 **/
s32 fm10k_msg_mac_vlan_vf(काष्ठा fm10k_hw *hw, u32 **results,
			  काष्ठा fm10k_mbx_info __always_unused *mbx)
अणु
	u8 perm_addr[ETH_ALEN];
	u16 vid;
	s32 err;

	/* record MAC address requested */
	err = fm10k_tlv_attr_get_mac_vlan(
					results[FM10K_MAC_VLAN_MSG_DEFAULT_MAC],
					perm_addr, &vid);
	अगर (err)
		वापस err;

	ether_addr_copy(hw->mac.perm_addr, perm_addr);
	hw->mac.शेष_vid = vid & (FM10K_VLAN_TABLE_VID_MAX - 1);
	hw->mac.vlan_override = !!(vid & FM10K_VLAN_OVERRIDE);

	वापस 0;
पूर्ण

/**
 *  fm10k_पढ़ो_mac_addr_vf - Read device MAC address
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  This function should determine the MAC address क्रम the VF
 **/
अटल s32 fm10k_पढ़ो_mac_addr_vf(काष्ठा fm10k_hw *hw)
अणु
	u8 perm_addr[ETH_ALEN];
	u32 base_addr;

	base_addr = fm10k_पढ़ो_reg(hw, FM10K_TDBAL(0));

	/* last byte should be 0 */
	अगर (base_addr << 24)
		वापस  FM10K_ERR_INVALID_MAC_ADDR;

	perm_addr[3] = (u8)(base_addr >> 24);
	perm_addr[4] = (u8)(base_addr >> 16);
	perm_addr[5] = (u8)(base_addr >> 8);

	base_addr = fm10k_पढ़ो_reg(hw, FM10K_TDBAH(0));

	/* first byte should be all 1's */
	अगर ((~base_addr) >> 24)
		वापस  FM10K_ERR_INVALID_MAC_ADDR;

	perm_addr[0] = (u8)(base_addr >> 16);
	perm_addr[1] = (u8)(base_addr >> 8);
	perm_addr[2] = (u8)(base_addr);

	ether_addr_copy(hw->mac.perm_addr, perm_addr);
	ether_addr_copy(hw->mac.addr, perm_addr);

	वापस 0;
पूर्ण

/**
 *  fm10k_update_uc_addr_vf - Update device unicast addresses
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @glort: unused
 *  @mac: MAC address to add/हटाओ from table
 *  @vid: VLAN ID to add/हटाओ from table
 *  @add: Indicates अगर this is an add or हटाओ operation
 *  @flags: flags field to indicate add and secure - unused
 *
 *  This function is used to add or हटाओ unicast MAC addresses क्रम
 *  the VF.
 **/
अटल s32 fm10k_update_uc_addr_vf(काष्ठा fm10k_hw *hw,
				   u16 __always_unused glort,
				   स्थिर u8 *mac, u16 vid, bool add,
				   u8 __always_unused flags)
अणु
	काष्ठा fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[7];

	/* verअगरy VLAN ID is valid */
	अगर (vid >= FM10K_VLAN_TABLE_VID_MAX)
		वापस FM10K_ERR_PARAM;

	/* verअगरy MAC address is valid */
	अगर (!is_valid_ether_addr(mac))
		वापस FM10K_ERR_PARAM;

	/* verअगरy we are not locked करोwn on the MAC address */
	अगर (is_valid_ether_addr(hw->mac.perm_addr) &&
	    !ether_addr_equal(hw->mac.perm_addr, mac))
		वापस FM10K_ERR_PARAM;

	/* add bit to notअगरy us अगर this is a set or clear operation */
	अगर (!add)
		vid |= FM10K_VLAN_CLEAR;

	/* generate VLAN request */
	fm10k_tlv_msg_init(msg, FM10K_VF_MSG_ID_MAC_VLAN);
	fm10k_tlv_attr_put_mac_vlan(msg, FM10K_MAC_VLAN_MSG_MAC, mac, vid);

	/* load onto outgoing mailbox */
	वापस mbx->ops.enqueue_tx(hw, mbx, msg);
पूर्ण

/**
 *  fm10k_update_mc_addr_vf - Update device multicast addresses
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @glort: unused
 *  @mac: MAC address to add/हटाओ from table
 *  @vid: VLAN ID to add/हटाओ from table
 *  @add: Indicates अगर this is an add or हटाओ operation
 *
 *  This function is used to add or हटाओ multicast MAC addresses क्रम
 *  the VF.
 **/
अटल s32 fm10k_update_mc_addr_vf(काष्ठा fm10k_hw *hw,
				   u16 __always_unused glort,
				   स्थिर u8 *mac, u16 vid, bool add)
अणु
	काष्ठा fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[7];

	/* verअगरy VLAN ID is valid */
	अगर (vid >= FM10K_VLAN_TABLE_VID_MAX)
		वापस FM10K_ERR_PARAM;

	/* verअगरy multicast address is valid */
	अगर (!is_multicast_ether_addr(mac))
		वापस FM10K_ERR_PARAM;

	/* add bit to notअगरy us अगर this is a set or clear operation */
	अगर (!add)
		vid |= FM10K_VLAN_CLEAR;

	/* generate VLAN request */
	fm10k_tlv_msg_init(msg, FM10K_VF_MSG_ID_MAC_VLAN);
	fm10k_tlv_attr_put_mac_vlan(msg, FM10K_MAC_VLAN_MSG_MULTICAST,
				    mac, vid);

	/* load onto outgoing mailbox */
	वापस mbx->ops.enqueue_tx(hw, mbx, msg);
पूर्ण

/**
 *  fm10k_update_पूर्णांक_moderator_vf - Request update of पूर्णांकerrupt moderator list
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  This function will issue a request to the PF to rescan our MSI-X table
 *  and to update the पूर्णांकerrupt moderator linked list.
 **/
अटल व्योम fm10k_update_पूर्णांक_moderator_vf(काष्ठा fm10k_hw *hw)
अणु
	काष्ठा fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[1];

	/* generate MSI-X request */
	fm10k_tlv_msg_init(msg, FM10K_VF_MSG_ID_MSIX);

	/* load onto outgoing mailbox */
	mbx->ops.enqueue_tx(hw, mbx, msg);
पूर्ण

/* This काष्ठाure defines the attibutes to be parsed below */
स्थिर काष्ठा fm10k_tlv_attr fm10k_lport_state_msg_attr[] = अणु
	FM10K_TLV_ATTR_BOOL(FM10K_LPORT_STATE_MSG_DISABLE),
	FM10K_TLV_ATTR_U8(FM10K_LPORT_STATE_MSG_XCAST_MODE),
	FM10K_TLV_ATTR_BOOL(FM10K_LPORT_STATE_MSG_READY),
	FM10K_TLV_ATTR_LAST
पूर्ण;

/**
 *  fm10k_msg_lport_state_vf - Message handler क्रम lport_state message from PF
 *  @hw: Poपूर्णांकer to hardware काष्ठाure
 *  @results: poपूर्णांकer array containing parsed data
 *  @mbx: Poपूर्णांकer to mailbox inक्रमmation काष्ठाure
 *
 *  This handler is meant to capture the indication from the PF that we
 *  are पढ़ोy to bring up the पूर्णांकerface.
 **/
s32 fm10k_msg_lport_state_vf(काष्ठा fm10k_hw *hw, u32 **results,
			     काष्ठा fm10k_mbx_info __always_unused *mbx)
अणु
	hw->mac.dglort_map = !results[FM10K_LPORT_STATE_MSG_READY] ?
			     FM10K_DGLORTMAP_NONE : FM10K_DGLORTMAP_ZERO;

	वापस 0;
पूर्ण

/**
 *  fm10k_update_lport_state_vf - Update device state in lower device
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @glort: unused
 *  @count: number of logical ports to enable - unused (always 1)
 *  @enable: boolean value indicating अगर this is an enable or disable request
 *
 *  Notअगरy the lower device of a state change.  If the lower device is
 *  enabled we can add filters, अगर it is disabled all filters क्रम this
 *  logical port are flushed.
 **/
अटल s32 fm10k_update_lport_state_vf(काष्ठा fm10k_hw *hw,
				       u16 __always_unused glort,
				       u16 __always_unused count, bool enable)
अणु
	काष्ठा fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[2];

	/* reset glort mask 0 as we have to रुको to be enabled */
	hw->mac.dglort_map = FM10K_DGLORTMAP_NONE;

	/* generate port state request */
	fm10k_tlv_msg_init(msg, FM10K_VF_MSG_ID_LPORT_STATE);
	अगर (!enable)
		fm10k_tlv_attr_put_bool(msg, FM10K_LPORT_STATE_MSG_DISABLE);

	/* load onto outgoing mailbox */
	वापस mbx->ops.enqueue_tx(hw, mbx, msg);
पूर्ण

/**
 *  fm10k_update_xcast_mode_vf - Request update of multicast mode
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @glort: unused
 *  @mode: पूर्णांकeger value indicating mode being requested
 *
 *  This function will attempt to request a higher mode क्रम the port
 *  so that it can enable either multicast, multicast promiscuous, or
 *  promiscuous mode of operation.
 **/
अटल s32 fm10k_update_xcast_mode_vf(काष्ठा fm10k_hw *hw,
				      u16 __always_unused glort, u8 mode)
अणु
	काष्ठा fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[3];

	अगर (mode > FM10K_XCAST_MODE_NONE)
		वापस FM10K_ERR_PARAM;

	/* generate message requesting to change xcast mode */
	fm10k_tlv_msg_init(msg, FM10K_VF_MSG_ID_LPORT_STATE);
	fm10k_tlv_attr_put_u8(msg, FM10K_LPORT_STATE_MSG_XCAST_MODE, mode);

	/* load onto outgoing mailbox */
	वापस mbx->ops.enqueue_tx(hw, mbx, msg);
पूर्ण

/**
 *  fm10k_update_hw_stats_vf - Updates hardware related statistics of VF
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @stats: poपूर्णांकer to statistics काष्ठाure
 *
 *  This function collects and aggregates per queue hardware statistics.
 **/
अटल व्योम fm10k_update_hw_stats_vf(काष्ठा fm10k_hw *hw,
				     काष्ठा fm10k_hw_stats *stats)
अणु
	fm10k_update_hw_stats_q(hw, stats->q, 0, hw->mac.max_queues);
पूर्ण

/**
 *  fm10k_rebind_hw_stats_vf - Resets base क्रम hardware statistics of VF
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @stats: poपूर्णांकer to the stats काष्ठाure to update
 *
 *  This function resets the base क्रम queue hardware statistics.
 **/
अटल व्योम fm10k_rebind_hw_stats_vf(काष्ठा fm10k_hw *hw,
				     काष्ठा fm10k_hw_stats *stats)
अणु
	/* Unbind Queue Statistics */
	fm10k_unbind_hw_stats_q(stats->q, 0, hw->mac.max_queues);

	/* Reinitialize bases क्रम all stats */
	fm10k_update_hw_stats_vf(hw, stats);
पूर्ण

/**
 *  fm10k_configure_dglort_map_vf - Configures GLORT entry and queues
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @dglort: poपूर्णांकer to dglort configuration काष्ठाure
 *
 *  Reads the configuration काष्ठाure contained in dglort_cfg and uses
 *  that inक्रमmation to then populate a DGLORTMAP/DEC entry and the queues
 *  to which it has been asचिन्हित.
 **/
अटल s32 fm10k_configure_dglort_map_vf(काष्ठा fm10k_hw __always_unused *hw,
					 काष्ठा fm10k_dglort_cfg *dglort)
अणु
	/* verअगरy the dglort poपूर्णांकer */
	अगर (!dglort)
		वापस FM10K_ERR_PARAM;

	/* stub क्रम now until we determine correct message क्रम this */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fm10k_msg_data fm10k_msg_data_vf[] = अणु
	FM10K_TLV_MSG_TEST_HANDLER(fm10k_tlv_msg_test),
	FM10K_VF_MSG_MAC_VLAN_HANDLER(fm10k_msg_mac_vlan_vf),
	FM10K_VF_MSG_LPORT_STATE_HANDLER(fm10k_msg_lport_state_vf),
	FM10K_TLV_MSG_ERROR_HANDLER(fm10k_tlv_msg_error),
पूर्ण;

अटल स्थिर काष्ठा fm10k_mac_ops mac_ops_vf = अणु
	.get_bus_info		= fm10k_get_bus_info_generic,
	.reset_hw		= fm10k_reset_hw_vf,
	.init_hw		= fm10k_init_hw_vf,
	.start_hw		= fm10k_start_hw_generic,
	.stop_hw		= fm10k_stop_hw_vf,
	.update_vlan		= fm10k_update_vlan_vf,
	.पढ़ो_mac_addr		= fm10k_पढ़ो_mac_addr_vf,
	.update_uc_addr		= fm10k_update_uc_addr_vf,
	.update_mc_addr		= fm10k_update_mc_addr_vf,
	.update_xcast_mode	= fm10k_update_xcast_mode_vf,
	.update_पूर्णांक_moderator	= fm10k_update_पूर्णांक_moderator_vf,
	.update_lport_state	= fm10k_update_lport_state_vf,
	.update_hw_stats	= fm10k_update_hw_stats_vf,
	.rebind_hw_stats	= fm10k_rebind_hw_stats_vf,
	.configure_dglort_map	= fm10k_configure_dglort_map_vf,
	.get_host_state		= fm10k_get_host_state_generic,
पूर्ण;

अटल s32 fm10k_get_invariants_vf(काष्ठा fm10k_hw *hw)
अणु
	fm10k_get_invariants_generic(hw);

	वापस fm10k_pfvf_mbx_init(hw, &hw->mbx, fm10k_msg_data_vf, 0);
पूर्ण

स्थिर काष्ठा fm10k_info fm10k_vf_info = अणु
	.mac		= fm10k_mac_vf,
	.get_invariants	= fm10k_get_invariants_vf,
	.mac_ops	= &mac_ops_vf,
पूर्ण;
