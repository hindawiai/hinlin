<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2019 Intel Corporation. */

#समावेश "fm10k_pf.h"
#समावेश "fm10k_vf.h"

/**
 *  fm10k_reset_hw_pf - PF hardware reset
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  This function should वापस the hardware to a state similar to the
 *  one it is in after being घातered on.
 **/
अटल s32 fm10k_reset_hw_pf(काष्ठा fm10k_hw *hw)
अणु
	s32 err;
	u32 reg;
	u16 i;

	/* Disable पूर्णांकerrupts */
	fm10k_ग_लिखो_reg(hw, FM10K_EIMR, FM10K_EIMR_DISABLE(ALL));

	/* Lock ITR2 reg 0 पूर्णांकo itself and disable पूर्णांकerrupt moderation */
	fm10k_ग_लिखो_reg(hw, FM10K_ITR2(0), 0);
	fm10k_ग_लिखो_reg(hw, FM10K_INT_CTRL, 0);

	/* We assume here Tx and Rx queue 0 are owned by the PF */

	/* Shut off VF access to their queues क्रमcing them to queue 0 */
	क्रम (i = 0; i < FM10K_TQMAP_TABLE_SIZE; i++) अणु
		fm10k_ग_लिखो_reg(hw, FM10K_TQMAP(i), 0);
		fm10k_ग_लिखो_reg(hw, FM10K_RQMAP(i), 0);
	पूर्ण

	/* shut करोwn all rings */
	err = fm10k_disable_queues_generic(hw, FM10K_MAX_QUEUES);
	अगर (err == FM10K_ERR_REQUESTS_PENDING) अणु
		hw->mac.reset_जबतक_pending++;
		जाओ क्रमce_reset;
	पूर्ण अन्यथा अगर (err) अणु
		वापस err;
	पूर्ण

	/* Verअगरy that DMA is no दीर्घer active */
	reg = fm10k_पढ़ो_reg(hw, FM10K_DMA_CTRL);
	अगर (reg & (FM10K_DMA_CTRL_TX_ACTIVE | FM10K_DMA_CTRL_RX_ACTIVE))
		वापस FM10K_ERR_DMA_PENDING;

क्रमce_reset:
	/* Inititate data path reset */
	reg = FM10K_DMA_CTRL_DATAPATH_RESET;
	fm10k_ग_लिखो_reg(hw, FM10K_DMA_CTRL, reg);

	/* Flush ग_लिखो and allow 100us क्रम reset to complete */
	fm10k_ग_लिखो_flush(hw);
	udelay(FM10K_RESET_TIMEOUT);

	/* Verअगरy we made it out of reset */
	reg = fm10k_पढ़ो_reg(hw, FM10K_IP);
	अगर (!(reg & FM10K_IP_NOTINRESET))
		वापस FM10K_ERR_RESET_FAILED;

	वापस 0;
पूर्ण

/**
 *  fm10k_is_ari_hierarchy_pf - Indicate ARI hierarchy support
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Looks at the ARI hierarchy bit to determine whether ARI is supported or not.
 **/
अटल bool fm10k_is_ari_hierarchy_pf(काष्ठा fm10k_hw *hw)
अणु
	u16 sriov_ctrl = fm10k_पढ़ो_pci_cfg_word(hw, FM10K_PCIE_SRIOV_CTRL);

	वापस !!(sriov_ctrl & FM10K_PCIE_SRIOV_CTRL_VFARI);
पूर्ण

/**
 *  fm10k_init_hw_pf - PF hardware initialization
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 **/
अटल s32 fm10k_init_hw_pf(काष्ठा fm10k_hw *hw)
अणु
	u32 dma_ctrl, txqctl;
	u16 i;

	/* Establish शेष VSI as valid */
	fm10k_ग_लिखो_reg(hw, FM10K_DGLORTDEC(fm10k_dglort_शेष), 0);
	fm10k_ग_लिखो_reg(hw, FM10K_DGLORTMAP(fm10k_dglort_शेष),
			FM10K_DGLORTMAP_ANY);

	/* Invalidate all other GLORT entries */
	क्रम (i = 1; i < FM10K_DGLORT_COUNT; i++)
		fm10k_ग_लिखो_reg(hw, FM10K_DGLORTMAP(i), FM10K_DGLORTMAP_NONE);

	/* reset ITR2(0) to poपूर्णांक to itself */
	fm10k_ग_लिखो_reg(hw, FM10K_ITR2(0), 0);

	/* reset VF ITR2(0) to poपूर्णांक to 0 aव्योम PF रेजिस्टरs */
	fm10k_ग_लिखो_reg(hw, FM10K_ITR2(FM10K_ITR_REG_COUNT_PF), 0);

	/* loop through all PF ITR2 रेजिस्टरs poपूर्णांकing them to the previous */
	क्रम (i = 1; i < FM10K_ITR_REG_COUNT_PF; i++)
		fm10k_ग_लिखो_reg(hw, FM10K_ITR2(i), i - 1);

	/* Enable पूर्णांकerrupt moderator अगर not alपढ़ोy enabled */
	fm10k_ग_लिखो_reg(hw, FM10K_INT_CTRL, FM10K_INT_CTRL_ENABLEMODERATOR);

	/* compute the शेष txqctl configuration */
	txqctl = FM10K_TXQCTL_PF | FM10K_TXQCTL_UNLIMITED_BW |
		 (hw->mac.शेष_vid << FM10K_TXQCTL_VID_SHIFT);

	क्रम (i = 0; i < FM10K_MAX_QUEUES; i++) अणु
		/* configure rings क्रम 256 Queue / 32 Descriptor cache mode */
		fm10k_ग_लिखो_reg(hw, FM10K_TQDLOC(i),
				(i * FM10K_TQDLOC_BASE_32_DESC) |
				FM10K_TQDLOC_SIZE_32_DESC);
		fm10k_ग_लिखो_reg(hw, FM10K_TXQCTL(i), txqctl);

		/* configure rings to provide TPH processing hपूर्णांकs */
		fm10k_ग_लिखो_reg(hw, FM10K_TPH_TXCTRL(i),
				FM10K_TPH_TXCTRL_DESC_TPHEN |
				FM10K_TPH_TXCTRL_DESC_RROEN |
				FM10K_TPH_TXCTRL_DESC_WROEN |
				FM10K_TPH_TXCTRL_DATA_RROEN);
		fm10k_ग_लिखो_reg(hw, FM10K_TPH_RXCTRL(i),
				FM10K_TPH_RXCTRL_DESC_TPHEN |
				FM10K_TPH_RXCTRL_DESC_RROEN |
				FM10K_TPH_RXCTRL_DATA_WROEN |
				FM10K_TPH_RXCTRL_HDR_WROEN);
	पूर्ण

	/* set max hold पूर्णांकerval to align with 1.024 usec in all modes and
	 * store ITR scale
	 */
	चयन (hw->bus.speed) अणु
	हाल fm10k_bus_speed_2500:
		dma_ctrl = FM10K_DMA_CTRL_MAX_HOLD_1US_GEN1;
		hw->mac.itr_scale = FM10K_TDLEN_ITR_SCALE_GEN1;
		अवरोध;
	हाल fm10k_bus_speed_5000:
		dma_ctrl = FM10K_DMA_CTRL_MAX_HOLD_1US_GEN2;
		hw->mac.itr_scale = FM10K_TDLEN_ITR_SCALE_GEN2;
		अवरोध;
	हाल fm10k_bus_speed_8000:
		dma_ctrl = FM10K_DMA_CTRL_MAX_HOLD_1US_GEN3;
		hw->mac.itr_scale = FM10K_TDLEN_ITR_SCALE_GEN3;
		अवरोध;
	शेष:
		dma_ctrl = 0;
		/* just in हाल, assume Gen3 ITR scale */
		hw->mac.itr_scale = FM10K_TDLEN_ITR_SCALE_GEN3;
		अवरोध;
	पूर्ण

	/* Configure TSO flags */
	fm10k_ग_लिखो_reg(hw, FM10K_DTXTCPFLGL, FM10K_TSO_FLAGS_LOW);
	fm10k_ग_लिखो_reg(hw, FM10K_DTXTCPFLGH, FM10K_TSO_FLAGS_HI);

	/* Enable DMA engine
	 * Set Rx Descriptor size to 32
	 * Set Minimum MSS to 64
	 * Set Maximum number of Rx queues to 256 / 32 Descriptor
	 */
	dma_ctrl |= FM10K_DMA_CTRL_TX_ENABLE | FM10K_DMA_CTRL_RX_ENABLE |
		    FM10K_DMA_CTRL_RX_DESC_SIZE | FM10K_DMA_CTRL_MINMSS_64 |
		    FM10K_DMA_CTRL_32_DESC;

	fm10k_ग_लिखो_reg(hw, FM10K_DMA_CTRL, dma_ctrl);

	/* record maximum queue count, we limit ourselves to 128 */
	hw->mac.max_queues = FM10K_MAX_QUEUES_PF;

	/* We support either 64 VFs or 7 VFs depending on अगर we have ARI */
	hw->iov.total_vfs = fm10k_is_ari_hierarchy_pf(hw) ? 64 : 7;

	वापस 0;
पूर्ण

/**
 *  fm10k_update_vlan_pf - Update status of VLAN ID in VLAN filter table
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @vid: VLAN ID to add to table
 *  @vsi: Index indicating VF ID or PF ID in table
 *  @set: Indicates अगर this is a set or clear operation
 *
 *  This function adds or हटाओs the corresponding VLAN ID from the VLAN
 *  filter table क्रम the corresponding function.  In addition to the
 *  standard set/clear that supports one bit a multi-bit ग_लिखो is
 *  supported to set 64 bits at a समय.
 **/
अटल s32 fm10k_update_vlan_pf(काष्ठा fm10k_hw *hw, u32 vid, u8 vsi, bool set)
अणु
	u32 vlan_table, reg, mask, bit, len;

	/* verअगरy the VSI index is valid */
	अगर (vsi > FM10K_VLAN_TABLE_VSI_MAX)
		वापस FM10K_ERR_PARAM;

	/* VLAN multi-bit ग_लिखो:
	 * The multi-bit ग_लिखो has several parts to it.
	 *               24              16               8               0
	 *  7 6 5 4 3 2 1 0 7 6 5 4 3 2 1 0 7 6 5 4 3 2 1 0 7 6 5 4 3 2 1 0
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * | RSVD0 |         Length        |C|RSVD0|        VLAN ID        |
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 *
	 * VLAN ID: Vlan Starting value
	 * RSVD0: Reserved section, must be 0
	 * C: Flag field, 0 is set, 1 is clear (Used in VF VLAN message)
	 * Length: Number of बार to repeat the bit being set
	 */
	len = vid >> 16;
	vid = (vid << 17) >> 17;

	/* verअगरy the reserved 0 fields are 0 */
	अगर (len >= FM10K_VLAN_TABLE_VID_MAX || vid >= FM10K_VLAN_TABLE_VID_MAX)
		वापस FM10K_ERR_PARAM;

	/* Loop through the table updating all required VLANs */
	क्रम (reg = FM10K_VLAN_TABLE(vsi, vid / 32), bit = vid % 32;
	     len < FM10K_VLAN_TABLE_VID_MAX;
	     len -= 32 - bit, reg++, bit = 0) अणु
		/* record the initial state of the रेजिस्टर */
		vlan_table = fm10k_पढ़ो_reg(hw, reg);

		/* truncate mask अगर we are at the start or end of the run */
		mask = (~(u32)0 >> ((len < 31) ? 31 - len : 0)) << bit;

		/* make necessary modअगरications to the रेजिस्टर */
		mask &= set ? ~vlan_table : vlan_table;
		अगर (mask)
			fm10k_ग_लिखो_reg(hw, reg, vlan_table ^ mask);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  fm10k_पढ़ो_mac_addr_pf - Read device MAC address
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Reads the device MAC address from the SM_AREA and stores the value.
 **/
अटल s32 fm10k_पढ़ो_mac_addr_pf(काष्ठा fm10k_hw *hw)
अणु
	u8 perm_addr[ETH_ALEN];
	u32 serial_num;

	serial_num = fm10k_पढ़ो_reg(hw, FM10K_SM_AREA(1));

	/* last byte should be all 1's */
	अगर ((~serial_num) << 24)
		वापस  FM10K_ERR_INVALID_MAC_ADDR;

	perm_addr[0] = (u8)(serial_num >> 24);
	perm_addr[1] = (u8)(serial_num >> 16);
	perm_addr[2] = (u8)(serial_num >> 8);

	serial_num = fm10k_पढ़ो_reg(hw, FM10K_SM_AREA(0));

	/* first byte should be all 1's */
	अगर ((~serial_num) >> 24)
		वापस  FM10K_ERR_INVALID_MAC_ADDR;

	perm_addr[3] = (u8)(serial_num >> 16);
	perm_addr[4] = (u8)(serial_num >> 8);
	perm_addr[5] = (u8)(serial_num);

	ether_addr_copy(hw->mac.perm_addr, perm_addr);
	ether_addr_copy(hw->mac.addr, perm_addr);

	वापस 0;
पूर्ण

/**
 *  fm10k_glort_valid_pf - Validate that the provided glort is valid
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @glort: base glort to be validated
 *
 *  This function will वापस an error अगर the provided glort is invalid
 **/
bool fm10k_glort_valid_pf(काष्ठा fm10k_hw *hw, u16 glort)
अणु
	glort &= hw->mac.dglort_map >> FM10K_DGLORTMAP_MASK_SHIFT;

	वापस glort == (hw->mac.dglort_map & FM10K_DGLORTMAP_NONE);
पूर्ण

/**
 *  fm10k_update_xc_addr_pf - Update device addresses
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @glort: base resource tag क्रम this request
 *  @mac: MAC address to add/हटाओ from table
 *  @vid: VLAN ID to add/हटाओ from table
 *  @add: Indicates अगर this is an add or हटाओ operation
 *  @flags: flags field to indicate add and secure
 *
 *  This function generates a message to the Switch API requesting
 *  that the given logical port add/हटाओ the given L2 MAC/VLAN address.
 **/
अटल s32 fm10k_update_xc_addr_pf(काष्ठा fm10k_hw *hw, u16 glort,
				   स्थिर u8 *mac, u16 vid, bool add, u8 flags)
अणु
	काष्ठा fm10k_mbx_info *mbx = &hw->mbx;
	काष्ठा fm10k_mac_update mac_update;
	u32 msg[5];

	/* clear set bit from VLAN ID */
	vid &= ~FM10K_VLAN_CLEAR;

	/* अगर glort or VLAN are not valid वापस error */
	अगर (!fm10k_glort_valid_pf(hw, glort) || vid >= FM10K_VLAN_TABLE_VID_MAX)
		वापस FM10K_ERR_PARAM;

	/* record fields */
	mac_update.mac_lower = cpu_to_le32(((u32)mac[2] << 24) |
						 ((u32)mac[3] << 16) |
						 ((u32)mac[4] << 8) |
						 ((u32)mac[5]));
	mac_update.mac_upper = cpu_to_le16(((u16)mac[0] << 8) |
					   ((u16)mac[1]));
	mac_update.vlan = cpu_to_le16(vid);
	mac_update.glort = cpu_to_le16(glort);
	mac_update.action = add ? 0 : 1;
	mac_update.flags = flags;

	/* populate mac_update fields */
	fm10k_tlv_msg_init(msg, FM10K_PF_MSG_ID_UPDATE_MAC_FWD_RULE);
	fm10k_tlv_attr_put_le_काष्ठा(msg, FM10K_PF_ATTR_ID_MAC_UPDATE,
				     &mac_update, माप(mac_update));

	/* load onto outgoing mailbox */
	वापस mbx->ops.enqueue_tx(hw, mbx, msg);
पूर्ण

/**
 *  fm10k_update_uc_addr_pf - Update device unicast addresses
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @glort: base resource tag क्रम this request
 *  @mac: MAC address to add/हटाओ from table
 *  @vid: VLAN ID to add/हटाओ from table
 *  @add: Indicates अगर this is an add or हटाओ operation
 *  @flags: flags field to indicate add and secure
 *
 *  This function is used to add or हटाओ unicast addresses क्रम
 *  the PF.
 **/
अटल s32 fm10k_update_uc_addr_pf(काष्ठा fm10k_hw *hw, u16 glort,
				   स्थिर u8 *mac, u16 vid, bool add, u8 flags)
अणु
	/* verअगरy MAC address is valid */
	अगर (!is_valid_ether_addr(mac))
		वापस FM10K_ERR_PARAM;

	वापस fm10k_update_xc_addr_pf(hw, glort, mac, vid, add, flags);
पूर्ण

/**
 *  fm10k_update_mc_addr_pf - Update device multicast addresses
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @glort: base resource tag क्रम this request
 *  @mac: MAC address to add/हटाओ from table
 *  @vid: VLAN ID to add/हटाओ from table
 *  @add: Indicates अगर this is an add or हटाओ operation
 *
 *  This function is used to add or हटाओ multicast MAC addresses क्रम
 *  the PF.
 **/
अटल s32 fm10k_update_mc_addr_pf(काष्ठा fm10k_hw *hw, u16 glort,
				   स्थिर u8 *mac, u16 vid, bool add)
अणु
	/* verअगरy multicast address is valid */
	अगर (!is_multicast_ether_addr(mac))
		वापस FM10K_ERR_PARAM;

	वापस fm10k_update_xc_addr_pf(hw, glort, mac, vid, add, 0);
पूर्ण

/**
 *  fm10k_update_xcast_mode_pf - Request update of multicast mode
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @glort: base resource tag क्रम this request
 *  @mode: पूर्णांकeger value indicating mode being requested
 *
 *  This function will attempt to request a higher mode क्रम the port
 *  so that it can enable either multicast, multicast promiscuous, or
 *  promiscuous mode of operation.
 **/
अटल s32 fm10k_update_xcast_mode_pf(काष्ठा fm10k_hw *hw, u16 glort, u8 mode)
अणु
	काष्ठा fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[3], xcast_mode;

	अगर (mode > FM10K_XCAST_MODE_NONE)
		वापस FM10K_ERR_PARAM;

	/* अगर glort is not valid वापस error */
	अगर (!fm10k_glort_valid_pf(hw, glort))
		वापस FM10K_ERR_PARAM;

	/* ग_लिखो xcast mode as a single u32 value,
	 * lower 16 bits: glort
	 * upper 16 bits: mode
	 */
	xcast_mode = ((u32)mode << 16) | glort;

	/* generate message requesting to change xcast mode */
	fm10k_tlv_msg_init(msg, FM10K_PF_MSG_ID_XCAST_MODES);
	fm10k_tlv_attr_put_u32(msg, FM10K_PF_ATTR_ID_XCAST_MODE, xcast_mode);

	/* load onto outgoing mailbox */
	वापस mbx->ops.enqueue_tx(hw, mbx, msg);
पूर्ण

/**
 *  fm10k_update_पूर्णांक_moderator_pf - Update पूर्णांकerrupt moderator linked list
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  This function walks through the MSI-X vector table to determine the
 *  number of active पूर्णांकerrupts and based on that inक्रमmation updates the
 *  पूर्णांकerrupt moderator linked list.
 **/
अटल व्योम fm10k_update_पूर्णांक_moderator_pf(काष्ठा fm10k_hw *hw)
अणु
	u32 i;

	/* Disable पूर्णांकerrupt moderator */
	fm10k_ग_लिखो_reg(hw, FM10K_INT_CTRL, 0);

	/* loop through PF from last to first looking enabled vectors */
	क्रम (i = FM10K_ITR_REG_COUNT_PF - 1; i; i--) अणु
		अगर (!fm10k_पढ़ो_reg(hw, FM10K_MSIX_VECTOR_MASK(i)))
			अवरोध;
	पूर्ण

	/* always reset VFITR2[0] to poपूर्णांक to last enabled PF vector */
	fm10k_ग_लिखो_reg(hw, FM10K_ITR2(FM10K_ITR_REG_COUNT_PF), i);

	/* reset ITR2[0] to poपूर्णांक to last enabled PF vector */
	अगर (!hw->iov.num_vfs)
		fm10k_ग_लिखो_reg(hw, FM10K_ITR2(0), i);

	/* Enable पूर्णांकerrupt moderator */
	fm10k_ग_लिखो_reg(hw, FM10K_INT_CTRL, FM10K_INT_CTRL_ENABLEMODERATOR);
पूर्ण

/**
 *  fm10k_update_lport_state_pf - Notअगरy the चयन of a change in port state
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @glort: base resource tag क्रम this request
 *  @count: number of logical ports being updated
 *  @enable: boolean value indicating enable or disable
 *
 *  This function is used to add/हटाओ a logical port from the चयन.
 **/
अटल s32 fm10k_update_lport_state_pf(काष्ठा fm10k_hw *hw, u16 glort,
				       u16 count, bool enable)
अणु
	काष्ठा fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[3], lport_msg;

	/* करो nothing अगर we are being asked to create or destroy 0 ports */
	अगर (!count)
		वापस 0;

	/* अगर glort is not valid वापस error */
	अगर (!fm10k_glort_valid_pf(hw, glort))
		वापस FM10K_ERR_PARAM;

	/* reset multicast mode अगर deleting lport */
	अगर (!enable)
		fm10k_update_xcast_mode_pf(hw, glort, FM10K_XCAST_MODE_NONE);

	/* स्थिरruct the lport message from the 2 pieces of data we have */
	lport_msg = ((u32)count << 16) | glort;

	/* generate lport create/delete message */
	fm10k_tlv_msg_init(msg, enable ? FM10K_PF_MSG_ID_LPORT_CREATE :
					 FM10K_PF_MSG_ID_LPORT_DELETE);
	fm10k_tlv_attr_put_u32(msg, FM10K_PF_ATTR_ID_PORT, lport_msg);

	/* load onto outgoing mailbox */
	वापस mbx->ops.enqueue_tx(hw, mbx, msg);
पूर्ण

/**
 *  fm10k_configure_dglort_map_pf - Configures GLORT entry and queues
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @dglort: poपूर्णांकer to dglort configuration काष्ठाure
 *
 *  Reads the configuration काष्ठाure contained in dglort_cfg and uses
 *  that inक्रमmation to then populate a DGLORTMAP/DEC entry and the queues
 *  to which it has been asचिन्हित.
 **/
अटल s32 fm10k_configure_dglort_map_pf(काष्ठा fm10k_hw *hw,
					 काष्ठा fm10k_dglort_cfg *dglort)
अणु
	u16 glort, queue_count, vsi_count, pc_count;
	u16 vsi, queue, pc, q_idx;
	u32 txqctl, dglortdec, dglorपंचांगap;

	/* verअगरy the dglort poपूर्णांकer */
	अगर (!dglort)
		वापस FM10K_ERR_PARAM;

	/* verअगरy the dglort values */
	अगर ((dglort->idx > 7) || (dglort->rss_l > 7) || (dglort->pc_l > 3) ||
	    (dglort->vsi_l > 6) || (dglort->vsi_b > 64) ||
	    (dglort->queue_l > 8) || (dglort->queue_b >= 256))
		वापस FM10K_ERR_PARAM;

	/* determine count of VSIs and queues */
	queue_count = BIT(dglort->rss_l + dglort->pc_l);
	vsi_count = BIT(dglort->vsi_l + dglort->queue_l);
	glort = dglort->glort;
	q_idx = dglort->queue_b;

	/* configure SGLORT क्रम queues */
	क्रम (vsi = 0; vsi < vsi_count; vsi++, glort++) अणु
		क्रम (queue = 0; queue < queue_count; queue++, q_idx++) अणु
			अगर (q_idx >= FM10K_MAX_QUEUES)
				अवरोध;

			fm10k_ग_लिखो_reg(hw, FM10K_TX_SGLORT(q_idx), glort);
			fm10k_ग_लिखो_reg(hw, FM10K_RX_SGLORT(q_idx), glort);
		पूर्ण
	पूर्ण

	/* determine count of PCs and queues */
	queue_count = BIT(dglort->queue_l + dglort->rss_l + dglort->vsi_l);
	pc_count = BIT(dglort->pc_l);

	/* configure PC क्रम Tx queues */
	क्रम (pc = 0; pc < pc_count; pc++) अणु
		q_idx = pc + dglort->queue_b;
		क्रम (queue = 0; queue < queue_count; queue++) अणु
			अगर (q_idx >= FM10K_MAX_QUEUES)
				अवरोध;

			txqctl = fm10k_पढ़ो_reg(hw, FM10K_TXQCTL(q_idx));
			txqctl &= ~FM10K_TXQCTL_PC_MASK;
			txqctl |= pc << FM10K_TXQCTL_PC_SHIFT;
			fm10k_ग_लिखो_reg(hw, FM10K_TXQCTL(q_idx), txqctl);

			q_idx += pc_count;
		पूर्ण
	पूर्ण

	/* configure DGLORTDEC */
	dglortdec = ((u32)(dglort->rss_l) << FM10K_DGLORTDEC_RSSLENGTH_SHIFT) |
		    ((u32)(dglort->queue_b) << FM10K_DGLORTDEC_QBASE_SHIFT) |
		    ((u32)(dglort->pc_l) << FM10K_DGLORTDEC_PCLENGTH_SHIFT) |
		    ((u32)(dglort->vsi_b) << FM10K_DGLORTDEC_VSIBASE_SHIFT) |
		    ((u32)(dglort->vsi_l) << FM10K_DGLORTDEC_VSILENGTH_SHIFT) |
		    ((u32)(dglort->queue_l));
	अगर (dglort->inner_rss)
		dglortdec |=  FM10K_DGLORTDEC_INNERRSS_ENABLE;

	/* configure DGLORTMAP */
	dglorपंचांगap = (dglort->idx == fm10k_dglort_शेष) ?
			FM10K_DGLORTMAP_ANY : FM10K_DGLORTMAP_ZERO;
	dglorपंचांगap <<= dglort->vsi_l + dglort->queue_l + dglort->shared_l;
	dglorपंचांगap |= dglort->glort;

	/* ग_लिखो values to hardware */
	fm10k_ग_लिखो_reg(hw, FM10K_DGLORTDEC(dglort->idx), dglortdec);
	fm10k_ग_लिखो_reg(hw, FM10K_DGLORTMAP(dglort->idx), dglorपंचांगap);

	वापस 0;
पूर्ण

u16 fm10k_queues_per_pool(काष्ठा fm10k_hw *hw)
अणु
	u16 num_pools = hw->iov.num_pools;

	वापस (num_pools > 32) ? 2 : (num_pools > 16) ? 4 : (num_pools > 8) ?
	       8 : FM10K_MAX_QUEUES_POOL;
पूर्ण

u16 fm10k_vf_queue_index(काष्ठा fm10k_hw *hw, u16 vf_idx)
अणु
	u16 num_vfs = hw->iov.num_vfs;
	u16 vf_q_idx = FM10K_MAX_QUEUES;

	vf_q_idx -= fm10k_queues_per_pool(hw) * (num_vfs - vf_idx);

	वापस vf_q_idx;
पूर्ण

अटल u16 fm10k_vectors_per_pool(काष्ठा fm10k_hw *hw)
अणु
	u16 num_pools = hw->iov.num_pools;

	वापस (num_pools > 32) ? 8 : (num_pools > 16) ? 16 :
	       FM10K_MAX_VECTORS_POOL;
पूर्ण

अटल u16 fm10k_vf_vector_index(काष्ठा fm10k_hw *hw, u16 vf_idx)
अणु
	u16 vf_v_idx = FM10K_MAX_VECTORS_PF;

	vf_v_idx += fm10k_vectors_per_pool(hw) * vf_idx;

	वापस vf_v_idx;
पूर्ण

/**
 *  fm10k_iov_assign_resources_pf - Assign pool resources क्रम भवization
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @num_vfs: number of VFs to be allocated
 *  @num_pools: number of भवization pools to be allocated
 *
 *  Allocates queues and traffic classes to भवization entities to prepare
 *  the PF क्रम SR-IOV and VMDq
 **/
अटल s32 fm10k_iov_assign_resources_pf(काष्ठा fm10k_hw *hw, u16 num_vfs,
					 u16 num_pools)
अणु
	u16 qmap_stride, qpp, vpp, vf_q_idx, vf_q_idx0, qmap_idx;
	u32 vid = hw->mac.शेष_vid << FM10K_TXQCTL_VID_SHIFT;
	पूर्णांक i, j;

	/* hardware only supports up to 64 pools */
	अगर (num_pools > 64)
		वापस FM10K_ERR_PARAM;

	/* the number of VFs cannot exceed the number of pools */
	अगर ((num_vfs > num_pools) || (num_vfs > hw->iov.total_vfs))
		वापस FM10K_ERR_PARAM;

	/* record number of भवization entities */
	hw->iov.num_vfs = num_vfs;
	hw->iov.num_pools = num_pools;

	/* determine qmap offsets and counts */
	qmap_stride = (num_vfs > 8) ? 32 : 256;
	qpp = fm10k_queues_per_pool(hw);
	vpp = fm10k_vectors_per_pool(hw);

	/* calculate starting index क्रम queues */
	vf_q_idx = fm10k_vf_queue_index(hw, 0);
	qmap_idx = 0;

	/* establish TCs with -1 credits and no quanta to prevent transmit */
	क्रम (i = 0; i < num_vfs; i++) अणु
		fm10k_ग_लिखो_reg(hw, FM10K_TC_MAXCREDIT(i), 0);
		fm10k_ग_लिखो_reg(hw, FM10K_TC_RATE(i), 0);
		fm10k_ग_लिखो_reg(hw, FM10K_TC_CREDIT(i),
				FM10K_TC_CREDIT_CREDIT_MASK);
	पूर्ण

	/* zero out all mbmem रेजिस्टरs */
	क्रम (i = FM10K_VFMBMEM_LEN * num_vfs; i--;)
		fm10k_ग_लिखो_reg(hw, FM10K_MBMEM(i), 0);

	/* clear event notअगरication of VF FLR */
	fm10k_ग_लिखो_reg(hw, FM10K_PFVFLREC(0), ~0);
	fm10k_ग_लिखो_reg(hw, FM10K_PFVFLREC(1), ~0);

	/* loop through unallocated rings assigning them back to PF */
	क्रम (i = FM10K_MAX_QUEUES_PF; i < vf_q_idx; i++) अणु
		fm10k_ग_लिखो_reg(hw, FM10K_TXDCTL(i), 0);
		fm10k_ग_लिखो_reg(hw, FM10K_TXQCTL(i), FM10K_TXQCTL_PF |
				FM10K_TXQCTL_UNLIMITED_BW | vid);
		fm10k_ग_लिखो_reg(hw, FM10K_RXQCTL(i), FM10K_RXQCTL_PF);
	पूर्ण

	/* PF should have alपढ़ोy updated VFITR2[0] */

	/* update all ITR रेजिस्टरs to flow to VFITR2[0] */
	क्रम (i = FM10K_ITR_REG_COUNT_PF + 1; i < FM10K_ITR_REG_COUNT; i++) अणु
		अगर (!(i & (vpp - 1)))
			fm10k_ग_लिखो_reg(hw, FM10K_ITR2(i), i - vpp);
		अन्यथा
			fm10k_ग_लिखो_reg(hw, FM10K_ITR2(i), i - 1);
	पूर्ण

	/* update PF ITR2[0] to reference the last vector */
	fm10k_ग_लिखो_reg(hw, FM10K_ITR2(0),
			fm10k_vf_vector_index(hw, num_vfs - 1));

	/* loop through rings populating rings and TCs */
	क्रम (i = 0; i < num_vfs; i++) अणु
		/* record index क्रम VF queue 0 क्रम use in end of loop */
		vf_q_idx0 = vf_q_idx;

		क्रम (j = 0; j < qpp; j++, qmap_idx++, vf_q_idx++) अणु
			/* assign VF and locked TC to queues */
			fm10k_ग_लिखो_reg(hw, FM10K_TXDCTL(vf_q_idx), 0);
			fm10k_ग_लिखो_reg(hw, FM10K_TXQCTL(vf_q_idx),
					(i << FM10K_TXQCTL_TC_SHIFT) | i |
					FM10K_TXQCTL_VF | vid);
			fm10k_ग_लिखो_reg(hw, FM10K_RXDCTL(vf_q_idx),
					FM10K_RXDCTL_WRITE_BACK_MIN_DELAY |
					FM10K_RXDCTL_DROP_ON_EMPTY);
			fm10k_ग_लिखो_reg(hw, FM10K_RXQCTL(vf_q_idx),
					(i << FM10K_RXQCTL_VF_SHIFT) |
					FM10K_RXQCTL_VF);

			/* map queue pair to VF */
			fm10k_ग_लिखो_reg(hw, FM10K_TQMAP(qmap_idx), vf_q_idx);
			fm10k_ग_लिखो_reg(hw, FM10K_RQMAP(qmap_idx), vf_q_idx);
		पूर्ण

		/* repeat the first ring क्रम all of the reमुख्यing VF rings */
		क्रम (; j < qmap_stride; j++, qmap_idx++) अणु
			fm10k_ग_लिखो_reg(hw, FM10K_TQMAP(qmap_idx), vf_q_idx0);
			fm10k_ग_लिखो_reg(hw, FM10K_RQMAP(qmap_idx), vf_q_idx0);
		पूर्ण
	पूर्ण

	/* loop through reमुख्यing indexes assigning all to queue 0 */
	जबतक (qmap_idx < FM10K_TQMAP_TABLE_SIZE) अणु
		fm10k_ग_लिखो_reg(hw, FM10K_TQMAP(qmap_idx), 0);
		fm10k_ग_लिखो_reg(hw, FM10K_RQMAP(qmap_idx), 0);
		qmap_idx++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  fm10k_iov_configure_tc_pf - Configure the shaping group क्रम VF
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @vf_idx: index of VF receiving GLORT
 *  @rate: Rate indicated in Mb/s
 *
 *  Configured the TC क्रम a given VF to allow only up to a given number
 *  of Mb/s of outgoing Tx throughput.
 **/
अटल s32 fm10k_iov_configure_tc_pf(काष्ठा fm10k_hw *hw, u16 vf_idx, पूर्णांक rate)
अणु
	/* configure शेषs */
	u32 पूर्णांकerval = FM10K_TC_RATE_INTERVAL_4US_GEN3;
	u32 tc_rate = FM10K_TC_RATE_QUANTA_MASK;

	/* verअगरy vf is in range */
	अगर (vf_idx >= hw->iov.num_vfs)
		वापस FM10K_ERR_PARAM;

	/* set पूर्णांकerval to align with 4.096 usec in all modes */
	चयन (hw->bus.speed) अणु
	हाल fm10k_bus_speed_2500:
		पूर्णांकerval = FM10K_TC_RATE_INTERVAL_4US_GEN1;
		अवरोध;
	हाल fm10k_bus_speed_5000:
		पूर्णांकerval = FM10K_TC_RATE_INTERVAL_4US_GEN2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (rate) अणु
		अगर (rate > FM10K_VF_TC_MAX || rate < FM10K_VF_TC_MIN)
			वापस FM10K_ERR_PARAM;

		/* The quanta is measured in Bytes per 4.096 or 8.192 usec
		 * The rate is provided in Mbits per second
		 * To tralslate from rate to quanta we need to multiply the
		 * rate by 8.192 usec and भागide by 8 bits/byte.  To aव्योम
		 * dealing with भग्नing poपूर्णांक we can round the values up
		 * to the nearest whole number ratio which gives us 128 / 125.
		 */
		tc_rate = (rate * 128) / 125;

		/* try to keep the rate limiting accurate by increasing
		 * the number of credits and पूर्णांकerval क्रम rates less than 4Gb/s
		 */
		अगर (rate < 4000)
			पूर्णांकerval <<= 1;
		अन्यथा
			tc_rate >>= 1;
	पूर्ण

	/* update rate limiter with new values */
	fm10k_ग_लिखो_reg(hw, FM10K_TC_RATE(vf_idx), tc_rate | पूर्णांकerval);
	fm10k_ग_लिखो_reg(hw, FM10K_TC_MAXCREDIT(vf_idx), FM10K_TC_MAXCREDIT_64K);
	fm10k_ग_लिखो_reg(hw, FM10K_TC_CREDIT(vf_idx), FM10K_TC_MAXCREDIT_64K);

	वापस 0;
पूर्ण

/**
 *  fm10k_iov_assign_पूर्णांक_moderator_pf - Add VF पूर्णांकerrupts to moderator list
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @vf_idx: index of VF receiving GLORT
 *
 *  Update the पूर्णांकerrupt moderator linked list to include any MSI-X
 *  पूर्णांकerrupts which the VF has enabled in the MSI-X vector table.
 **/
अटल s32 fm10k_iov_assign_पूर्णांक_moderator_pf(काष्ठा fm10k_hw *hw, u16 vf_idx)
अणु
	u16 vf_v_idx, vf_v_limit, i;

	/* verअगरy vf is in range */
	अगर (vf_idx >= hw->iov.num_vfs)
		वापस FM10K_ERR_PARAM;

	/* determine vector offset and count */
	vf_v_idx = fm10k_vf_vector_index(hw, vf_idx);
	vf_v_limit = vf_v_idx + fm10k_vectors_per_pool(hw);

	/* search क्रम first vector that is not masked */
	क्रम (i = vf_v_limit - 1; i > vf_v_idx; i--) अणु
		अगर (!fm10k_पढ़ो_reg(hw, FM10K_MSIX_VECTOR_MASK(i)))
			अवरोध;
	पूर्ण

	/* reset linked list so it now includes our active vectors */
	अगर (vf_idx == (hw->iov.num_vfs - 1))
		fm10k_ग_लिखो_reg(hw, FM10K_ITR2(0), i);
	अन्यथा
		fm10k_ग_लिखो_reg(hw, FM10K_ITR2(vf_v_limit), i);

	वापस 0;
पूर्ण

/**
 *  fm10k_iov_assign_शेष_mac_vlan_pf - Assign a MAC and VLAN to VF
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @vf_info: poपूर्णांकer to VF inक्रमmation काष्ठाure
 *
 *  Assign a MAC address and शेष VLAN to a VF and notअगरy it of the update
 **/
अटल s32 fm10k_iov_assign_शेष_mac_vlan_pf(काष्ठा fm10k_hw *hw,
						काष्ठा fm10k_vf_info *vf_info)
अणु
	u16 qmap_stride, queues_per_pool, vf_q_idx, समयout, qmap_idx, i;
	u32 msg[4], txdctl, txqctl, tdbal = 0, tdbah = 0;
	s32 err = 0;
	u16 vf_idx, vf_vid;

	/* verअगरy vf is in range */
	अगर (!vf_info || vf_info->vf_idx >= hw->iov.num_vfs)
		वापस FM10K_ERR_PARAM;

	/* determine qmap offsets and counts */
	qmap_stride = (hw->iov.num_vfs > 8) ? 32 : 256;
	queues_per_pool = fm10k_queues_per_pool(hw);

	/* calculate starting index क्रम queues */
	vf_idx = vf_info->vf_idx;
	vf_q_idx = fm10k_vf_queue_index(hw, vf_idx);
	qmap_idx = qmap_stride * vf_idx;

	/* Determine correct शेष VLAN ID. The FM10K_VLAN_OVERRIDE bit is
	 * used here to indicate to the VF that it will not have privilege to
	 * ग_लिखो VLAN_TABLE. All policy is enक्रमced on the PF but this allows
	 * the VF to correctly report errors to userspace requests.
	 */
	अगर (vf_info->pf_vid)
		vf_vid = vf_info->pf_vid | FM10K_VLAN_OVERRIDE;
	अन्यथा
		vf_vid = vf_info->sw_vid;

	/* generate MAC_ADDR request */
	fm10k_tlv_msg_init(msg, FM10K_VF_MSG_ID_MAC_VLAN);
	fm10k_tlv_attr_put_mac_vlan(msg, FM10K_MAC_VLAN_MSG_DEFAULT_MAC,
				    vf_info->mac, vf_vid);

	/* Configure Queue control रेजिस्टर with new VLAN ID. The TXQCTL
	 * रेजिस्टर is RO from the VF, so the PF must करो this even in the
	 * हाल of notअगरying the VF of a new VID via the mailbox.
	 */
	txqctl = ((u32)vf_vid << FM10K_TXQCTL_VID_SHIFT) &
		 FM10K_TXQCTL_VID_MASK;
	txqctl |= (vf_idx << FM10K_TXQCTL_TC_SHIFT) |
		  FM10K_TXQCTL_VF | vf_idx;

	क्रम (i = 0; i < queues_per_pool; i++)
		fm10k_ग_लिखो_reg(hw, FM10K_TXQCTL(vf_q_idx + i), txqctl);

	/* try loading a message onto outgoing mailbox first */
	अगर (vf_info->mbx.ops.enqueue_tx) अणु
		err = vf_info->mbx.ops.enqueue_tx(hw, &vf_info->mbx, msg);
		अगर (err != FM10K_MBX_ERR_NO_MBX)
			वापस err;
		err = 0;
	पूर्ण

	/* If we aren't connected to a mailbox, this is most likely because
	 * the VF driver is not running. It should thus be safe to re-map
	 * queues and use the रेजिस्टरs to pass the MAC address so that the VF
	 * driver माला_लो correct inक्रमmation during its initialization.
	 */

	/* MAP Tx queue back to 0 temporarily, and disable it */
	fm10k_ग_लिखो_reg(hw, FM10K_TQMAP(qmap_idx), 0);
	fm10k_ग_लिखो_reg(hw, FM10K_TXDCTL(vf_q_idx), 0);

	/* verअगरy ring has disabled beक्रमe modअगरying base address रेजिस्टरs */
	txdctl = fm10k_पढ़ो_reg(hw, FM10K_TXDCTL(vf_q_idx));
	क्रम (समयout = 0; txdctl & FM10K_TXDCTL_ENABLE; समयout++) अणु
		/* limit ourselves to a 1ms समयout */
		अगर (समयout == 10) अणु
			err = FM10K_ERR_DMA_PENDING;
			जाओ err_out;
		पूर्ण

		usleep_range(100, 200);
		txdctl = fm10k_पढ़ो_reg(hw, FM10K_TXDCTL(vf_q_idx));
	पूर्ण

	/* Update base address रेजिस्टरs to contain MAC address */
	अगर (is_valid_ether_addr(vf_info->mac)) अणु
		tdbal = (((u32)vf_info->mac[3]) << 24) |
			(((u32)vf_info->mac[4]) << 16) |
			(((u32)vf_info->mac[5]) << 8);

		tdbah = (((u32)0xFF)	        << 24) |
			(((u32)vf_info->mac[0]) << 16) |
			(((u32)vf_info->mac[1]) << 8) |
			((u32)vf_info->mac[2]);
	पूर्ण

	/* Record the base address पूर्णांकo queue 0 */
	fm10k_ग_लिखो_reg(hw, FM10K_TDBAL(vf_q_idx), tdbal);
	fm10k_ग_लिखो_reg(hw, FM10K_TDBAH(vf_q_idx), tdbah);

	/* Provide the VF the ITR scale, using software-defined fields in TDLEN
	 * to pass the inक्रमmation during VF initialization. See definition of
	 * FM10K_TDLEN_ITR_SCALE_SHIFT क्रम more details.
	 */
	fm10k_ग_लिखो_reg(hw, FM10K_TDLEN(vf_q_idx), hw->mac.itr_scale <<
						   FM10K_TDLEN_ITR_SCALE_SHIFT);

err_out:
	/* restore the queue back to VF ownership */
	fm10k_ग_लिखो_reg(hw, FM10K_TQMAP(qmap_idx), vf_q_idx);
	वापस err;
पूर्ण

/**
 *  fm10k_iov_reset_resources_pf - Reassign queues and पूर्णांकerrupts to a VF
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @vf_info: poपूर्णांकer to VF inक्रमmation काष्ठाure
 *
 *  Reassign the पूर्णांकerrupts and queues to a VF following an FLR
 **/
अटल s32 fm10k_iov_reset_resources_pf(काष्ठा fm10k_hw *hw,
					काष्ठा fm10k_vf_info *vf_info)
अणु
	u16 qmap_stride, queues_per_pool, vf_q_idx, qmap_idx;
	u32 tdbal = 0, tdbah = 0, txqctl, rxqctl;
	u16 vf_v_idx, vf_v_limit, vf_vid;
	u8 vf_idx = vf_info->vf_idx;
	पूर्णांक i;

	/* verअगरy vf is in range */
	अगर (vf_idx >= hw->iov.num_vfs)
		वापस FM10K_ERR_PARAM;

	/* clear event notअगरication of VF FLR */
	fm10k_ग_लिखो_reg(hw, FM10K_PFVFLREC(vf_idx / 32), BIT(vf_idx % 32));

	/* क्रमce समयout and then disconnect the mailbox */
	vf_info->mbx.समयout = 0;
	अगर (vf_info->mbx.ops.disconnect)
		vf_info->mbx.ops.disconnect(hw, &vf_info->mbx);

	/* determine vector offset and count */
	vf_v_idx = fm10k_vf_vector_index(hw, vf_idx);
	vf_v_limit = vf_v_idx + fm10k_vectors_per_pool(hw);

	/* determine qmap offsets and counts */
	qmap_stride = (hw->iov.num_vfs > 8) ? 32 : 256;
	queues_per_pool = fm10k_queues_per_pool(hw);
	qmap_idx = qmap_stride * vf_idx;

	/* make all the queues inaccessible to the VF */
	क्रम (i = qmap_idx; i < (qmap_idx + qmap_stride); i++) अणु
		fm10k_ग_लिखो_reg(hw, FM10K_TQMAP(i), 0);
		fm10k_ग_लिखो_reg(hw, FM10K_RQMAP(i), 0);
	पूर्ण

	/* calculate starting index क्रम queues */
	vf_q_idx = fm10k_vf_queue_index(hw, vf_idx);

	/* determine correct शेष VLAN ID */
	अगर (vf_info->pf_vid)
		vf_vid = vf_info->pf_vid;
	अन्यथा
		vf_vid = vf_info->sw_vid;

	/* configure Queue control रेजिस्टर */
	txqctl = ((u32)vf_vid << FM10K_TXQCTL_VID_SHIFT) |
		 (vf_idx << FM10K_TXQCTL_TC_SHIFT) |
		 FM10K_TXQCTL_VF | vf_idx;
	rxqctl = (vf_idx << FM10K_RXQCTL_VF_SHIFT) | FM10K_RXQCTL_VF;

	/* stop further DMA and reset queue ownership back to VF */
	क्रम (i = vf_q_idx; i < (queues_per_pool + vf_q_idx); i++) अणु
		fm10k_ग_लिखो_reg(hw, FM10K_TXDCTL(i), 0);
		fm10k_ग_लिखो_reg(hw, FM10K_TXQCTL(i), txqctl);
		fm10k_ग_लिखो_reg(hw, FM10K_RXDCTL(i),
				FM10K_RXDCTL_WRITE_BACK_MIN_DELAY |
				FM10K_RXDCTL_DROP_ON_EMPTY);
		fm10k_ग_लिखो_reg(hw, FM10K_RXQCTL(i), rxqctl);
	पूर्ण

	/* reset TC with -1 credits and no quanta to prevent transmit */
	fm10k_ग_लिखो_reg(hw, FM10K_TC_MAXCREDIT(vf_idx), 0);
	fm10k_ग_लिखो_reg(hw, FM10K_TC_RATE(vf_idx), 0);
	fm10k_ग_लिखो_reg(hw, FM10K_TC_CREDIT(vf_idx),
			FM10K_TC_CREDIT_CREDIT_MASK);

	/* update our first entry in the table based on previous VF */
	अगर (!vf_idx)
		hw->mac.ops.update_पूर्णांक_moderator(hw);
	अन्यथा
		hw->iov.ops.assign_पूर्णांक_moderator(hw, vf_idx - 1);

	/* reset linked list so it now includes our active vectors */
	अगर (vf_idx == (hw->iov.num_vfs - 1))
		fm10k_ग_लिखो_reg(hw, FM10K_ITR2(0), vf_v_idx);
	अन्यथा
		fm10k_ग_लिखो_reg(hw, FM10K_ITR2(vf_v_limit), vf_v_idx);

	/* link reमुख्यing vectors so that next poपूर्णांकs to previous */
	क्रम (vf_v_idx++; vf_v_idx < vf_v_limit; vf_v_idx++)
		fm10k_ग_लिखो_reg(hw, FM10K_ITR2(vf_v_idx), vf_v_idx - 1);

	/* zero out MBMEM, VLAN_TABLE, RETA, RSSRK, and MRQC रेजिस्टरs */
	क्रम (i = FM10K_VFMBMEM_LEN; i--;)
		fm10k_ग_लिखो_reg(hw, FM10K_MBMEM_VF(vf_idx, i), 0);
	क्रम (i = FM10K_VLAN_TABLE_SIZE; i--;)
		fm10k_ग_लिखो_reg(hw, FM10K_VLAN_TABLE(vf_info->vsi, i), 0);
	क्रम (i = FM10K_RETA_SIZE; i--;)
		fm10k_ग_लिखो_reg(hw, FM10K_RETA(vf_info->vsi, i), 0);
	क्रम (i = FM10K_RSSRK_SIZE; i--;)
		fm10k_ग_लिखो_reg(hw, FM10K_RSSRK(vf_info->vsi, i), 0);
	fm10k_ग_लिखो_reg(hw, FM10K_MRQC(vf_info->vsi), 0);

	/* Update base address रेजिस्टरs to contain MAC address */
	अगर (is_valid_ether_addr(vf_info->mac)) अणु
		tdbal = (((u32)vf_info->mac[3]) << 24) |
			(((u32)vf_info->mac[4]) << 16) |
			(((u32)vf_info->mac[5]) << 8);
		tdbah = (((u32)0xFF)	   << 24) |
			(((u32)vf_info->mac[0]) << 16) |
			(((u32)vf_info->mac[1]) << 8) |
			((u32)vf_info->mac[2]);
	पूर्ण

	/* map queue pairs back to VF from last to first */
	क्रम (i = queues_per_pool; i--;) अणु
		fm10k_ग_लिखो_reg(hw, FM10K_TDBAL(vf_q_idx + i), tdbal);
		fm10k_ग_लिखो_reg(hw, FM10K_TDBAH(vf_q_idx + i), tdbah);
		/* See definition of FM10K_TDLEN_ITR_SCALE_SHIFT क्रम an
		 * explanation of how TDLEN is used.
		 */
		fm10k_ग_लिखो_reg(hw, FM10K_TDLEN(vf_q_idx + i),
				hw->mac.itr_scale <<
				FM10K_TDLEN_ITR_SCALE_SHIFT);
		fm10k_ग_लिखो_reg(hw, FM10K_TQMAP(qmap_idx + i), vf_q_idx + i);
		fm10k_ग_लिखो_reg(hw, FM10K_RQMAP(qmap_idx + i), vf_q_idx + i);
	पूर्ण

	/* repeat the first ring क्रम all the reमुख्यing VF rings */
	क्रम (i = queues_per_pool; i < qmap_stride; i++) अणु
		fm10k_ग_लिखो_reg(hw, FM10K_TQMAP(qmap_idx + i), vf_q_idx);
		fm10k_ग_लिखो_reg(hw, FM10K_RQMAP(qmap_idx + i), vf_q_idx);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  fm10k_iov_set_lport_pf - Assign and enable a logical port क्रम a given VF
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @vf_info: poपूर्णांकer to VF inक्रमmation काष्ठाure
 *  @lport_idx: Logical port offset from the hardware glort
 *  @flags: Set of capability flags to extend port beyond basic functionality
 *
 *  This function allows enabling a VF port by assigning it a GLORT and
 *  setting the flags so that it can enable an Rx mode.
 **/
अटल s32 fm10k_iov_set_lport_pf(काष्ठा fm10k_hw *hw,
				  काष्ठा fm10k_vf_info *vf_info,
				  u16 lport_idx, u8 flags)
अणु
	u16 glort = (hw->mac.dglort_map + lport_idx) & FM10K_DGLORTMAP_NONE;

	/* अगर glort is not valid वापस error */
	अगर (!fm10k_glort_valid_pf(hw, glort))
		वापस FM10K_ERR_PARAM;

	vf_info->vf_flags = flags | FM10K_VF_FLAG_NONE_CAPABLE;
	vf_info->glort = glort;

	वापस 0;
पूर्ण

/**
 *  fm10k_iov_reset_lport_pf - Disable a logical port क्रम a given VF
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @vf_info: poपूर्णांकer to VF inक्रमmation काष्ठाure
 *
 *  This function disables a VF port by stripping it of a GLORT and
 *  setting the flags so that it cannot enable any Rx mode.
 **/
अटल व्योम fm10k_iov_reset_lport_pf(काष्ठा fm10k_hw *hw,
				     काष्ठा fm10k_vf_info *vf_info)
अणु
	u32 msg[1];

	/* need to disable the port अगर it is alपढ़ोy enabled */
	अगर (FM10K_VF_FLAG_ENABLED(vf_info)) अणु
		/* notअगरy चयन that this port has been disabled */
		fm10k_update_lport_state_pf(hw, vf_info->glort, 1, false);

		/* generate port state response to notअगरy VF it is not पढ़ोy */
		fm10k_tlv_msg_init(msg, FM10K_VF_MSG_ID_LPORT_STATE);
		vf_info->mbx.ops.enqueue_tx(hw, &vf_info->mbx, msg);
	पूर्ण

	/* clear flags and glort अगर it exists */
	vf_info->vf_flags = 0;
	vf_info->glort = 0;
पूर्ण

/**
 *  fm10k_iov_update_stats_pf - Updates hardware related statistics क्रम VFs
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @q: stats क्रम all queues of a VF
 *  @vf_idx: index of VF
 *
 *  This function collects queue stats क्रम VFs.
 **/
अटल व्योम fm10k_iov_update_stats_pf(काष्ठा fm10k_hw *hw,
				      काष्ठा fm10k_hw_stats_q *q,
				      u16 vf_idx)
अणु
	u32 idx, qpp;

	/* get stats क्रम all of the queues */
	qpp = fm10k_queues_per_pool(hw);
	idx = fm10k_vf_queue_index(hw, vf_idx);
	fm10k_update_hw_stats_q(hw, q, idx, qpp);
पूर्ण

/**
 *  fm10k_iov_msg_msix_pf - Message handler क्रम MSI-X request from VF
 *  @hw: Poपूर्णांकer to hardware काष्ठाure
 *  @results: Poपूर्णांकer array to message, results[0] is poपूर्णांकer to message
 *  @mbx: Poपूर्णांकer to mailbox inक्रमmation काष्ठाure
 *
 *  This function is a शेष handler क्रम MSI-X requests from the VF. The
 *  assumption is that in this हाल it is acceptable to just directly
 *  hand off the message from the VF to the underlying shared code.
 **/
s32 fm10k_iov_msg_msix_pf(काष्ठा fm10k_hw *hw, u32 __always_unused **results,
			  काष्ठा fm10k_mbx_info *mbx)
अणु
	काष्ठा fm10k_vf_info *vf_info = (काष्ठा fm10k_vf_info *)mbx;
	u8 vf_idx = vf_info->vf_idx;

	वापस hw->iov.ops.assign_पूर्णांक_moderator(hw, vf_idx);
पूर्ण

/**
 * fm10k_iov_select_vid - Select correct शेष VLAN ID
 * @vf_info: poपूर्णांकer to VF inक्रमmation काष्ठाure
 * @vid: VLAN ID to correct
 *
 * Will report an error अगर the VLAN ID is out of range. For VID = 0, it will
 * वापस either the pf_vid or sw_vid depending on which one is set.
 */
s32 fm10k_iov_select_vid(काष्ठा fm10k_vf_info *vf_info, u16 vid)
अणु
	अगर (!vid)
		वापस vf_info->pf_vid ? vf_info->pf_vid : vf_info->sw_vid;
	अन्यथा अगर (vf_info->pf_vid && vid != vf_info->pf_vid)
		वापस FM10K_ERR_PARAM;
	अन्यथा
		वापस vid;
पूर्ण

/**
 *  fm10k_iov_msg_mac_vlan_pf - Message handler क्रम MAC/VLAN request from VF
 *  @hw: Poपूर्णांकer to hardware काष्ठाure
 *  @results: Poपूर्णांकer array to message, results[0] is poपूर्णांकer to message
 *  @mbx: Poपूर्णांकer to mailbox inक्रमmation काष्ठाure
 *
 *  This function is a शेष handler क्रम MAC/VLAN requests from the VF.
 *  The assumption is that in this हाल it is acceptable to just directly
 *  hand off the message from the VF to the underlying shared code.
 **/
s32 fm10k_iov_msg_mac_vlan_pf(काष्ठा fm10k_hw *hw, u32 **results,
			      काष्ठा fm10k_mbx_info *mbx)
अणु
	काष्ठा fm10k_vf_info *vf_info = (काष्ठा fm10k_vf_info *)mbx;
	u8 mac[ETH_ALEN];
	u32 *result;
	पूर्णांक err = 0;
	bool set;
	u16 vlan;
	u32 vid;

	/* we shouldn't be updating rules on a disabled पूर्णांकerface */
	अगर (!FM10K_VF_FLAG_ENABLED(vf_info))
		err = FM10K_ERR_PARAM;

	अगर (!err && !!results[FM10K_MAC_VLAN_MSG_VLAN]) अणु
		result = results[FM10K_MAC_VLAN_MSG_VLAN];

		/* record VLAN id requested */
		err = fm10k_tlv_attr_get_u32(result, &vid);
		अगर (err)
			वापस err;

		set = !(vid & FM10K_VLAN_CLEAR);
		vid &= ~FM10K_VLAN_CLEAR;

		/* अगर the length field has been set, this is a multi-bit
		 * update request. For multi-bit requests, simply disallow
		 * them when the pf_vid has been set. In this हाल, the PF
		 * should have alपढ़ोy cleared the VLAN_TABLE, and अगर we
		 * allowed them, it could allow a rogue VF to receive traffic
		 * on a VLAN it was not asचिन्हित. In the single-bit हाल, we
		 * need to modअगरy requests क्रम VLAN 0 to use the शेष PF or
		 * SW vid when asचिन्हित.
		 */

		अगर (vid >> 16) अणु
			/* prevent multi-bit requests when PF has
			 * administratively set the VLAN क्रम this VF
			 */
			अगर (vf_info->pf_vid)
				वापस FM10K_ERR_PARAM;
		पूर्ण अन्यथा अणु
			err = fm10k_iov_select_vid(vf_info, (u16)vid);
			अगर (err < 0)
				वापस err;

			vid = err;
		पूर्ण

		/* update VSI info क्रम VF in regards to VLAN table */
		err = hw->mac.ops.update_vlan(hw, vid, vf_info->vsi, set);
	पूर्ण

	अगर (!err && !!results[FM10K_MAC_VLAN_MSG_MAC]) अणु
		result = results[FM10K_MAC_VLAN_MSG_MAC];

		/* record unicast MAC address requested */
		err = fm10k_tlv_attr_get_mac_vlan(result, mac, &vlan);
		अगर (err)
			वापस err;

		/* block attempts to set MAC क्रम a locked device */
		अगर (is_valid_ether_addr(vf_info->mac) &&
		    !ether_addr_equal(mac, vf_info->mac))
			वापस FM10K_ERR_PARAM;

		set = !(vlan & FM10K_VLAN_CLEAR);
		vlan &= ~FM10K_VLAN_CLEAR;

		err = fm10k_iov_select_vid(vf_info, vlan);
		अगर (err < 0)
			वापस err;

		vlan = (u16)err;

		/* notअगरy चयन of request क्रम new unicast address */
		err = hw->mac.ops.update_uc_addr(hw, vf_info->glort,
						 mac, vlan, set, 0);
	पूर्ण

	अगर (!err && !!results[FM10K_MAC_VLAN_MSG_MULTICAST]) अणु
		result = results[FM10K_MAC_VLAN_MSG_MULTICAST];

		/* record multicast MAC address requested */
		err = fm10k_tlv_attr_get_mac_vlan(result, mac, &vlan);
		अगर (err)
			वापस err;

		/* verअगरy that the VF is allowed to request multicast */
		अगर (!(vf_info->vf_flags & FM10K_VF_FLAG_MULTI_ENABLED))
			वापस FM10K_ERR_PARAM;

		set = !(vlan & FM10K_VLAN_CLEAR);
		vlan &= ~FM10K_VLAN_CLEAR;

		err = fm10k_iov_select_vid(vf_info, vlan);
		अगर (err < 0)
			वापस err;

		vlan = (u16)err;

		/* notअगरy चयन of request क्रम new multicast address */
		err = hw->mac.ops.update_mc_addr(hw, vf_info->glort,
						 mac, vlan, set);
	पूर्ण

	वापस err;
पूर्ण

/**
 *  fm10k_iov_supported_xcast_mode_pf - Determine best match क्रम xcast mode
 *  @vf_info: VF info काष्ठाure containing capability flags
 *  @mode: Requested xcast mode
 *
 *  This function outमाला_दो the mode that most बंदly matches the requested
 *  mode.  If not modes match it will request we disable the port
 **/
अटल u8 fm10k_iov_supported_xcast_mode_pf(काष्ठा fm10k_vf_info *vf_info,
					    u8 mode)
अणु
	u8 vf_flags = vf_info->vf_flags;

	/* match up mode to capabilities as best as possible */
	चयन (mode) अणु
	हाल FM10K_XCAST_MODE_PROMISC:
		अगर (vf_flags & FM10K_VF_FLAG_PROMISC_CAPABLE)
			वापस FM10K_XCAST_MODE_PROMISC;
		fallthrough;
	हाल FM10K_XCAST_MODE_ALLMULTI:
		अगर (vf_flags & FM10K_VF_FLAG_ALLMULTI_CAPABLE)
			वापस FM10K_XCAST_MODE_ALLMULTI;
		fallthrough;
	हाल FM10K_XCAST_MODE_MULTI:
		अगर (vf_flags & FM10K_VF_FLAG_MULTI_CAPABLE)
			वापस FM10K_XCAST_MODE_MULTI;
		fallthrough;
	हाल FM10K_XCAST_MODE_NONE:
		अगर (vf_flags & FM10K_VF_FLAG_NONE_CAPABLE)
			वापस FM10K_XCAST_MODE_NONE;
		fallthrough;
	शेष:
		अवरोध;
	पूर्ण

	/* disable पूर्णांकerface as it should not be able to request any */
	वापस FM10K_XCAST_MODE_DISABLE;
पूर्ण

/**
 *  fm10k_iov_msg_lport_state_pf - Message handler क्रम port state requests
 *  @hw: Poपूर्णांकer to hardware काष्ठाure
 *  @results: Poपूर्णांकer array to message, results[0] is poपूर्णांकer to message
 *  @mbx: Poपूर्णांकer to mailbox inक्रमmation काष्ठाure
 *
 *  This function is a शेष handler क्रम port state requests.  The port
 *  state requests क्रम now are basic and consist of enabling or disabling
 *  the port.
 **/
s32 fm10k_iov_msg_lport_state_pf(काष्ठा fm10k_hw *hw, u32 **results,
				 काष्ठा fm10k_mbx_info *mbx)
अणु
	काष्ठा fm10k_vf_info *vf_info = (काष्ठा fm10k_vf_info *)mbx;
	s32 err = 0;
	u32 msg[2];
	u8 mode = 0;

	/* verअगरy VF is allowed to enable even minimal mode */
	अगर (!(vf_info->vf_flags & FM10K_VF_FLAG_NONE_CAPABLE))
		वापस FM10K_ERR_PARAM;

	अगर (!!results[FM10K_LPORT_STATE_MSG_XCAST_MODE]) अणु
		u32 *result = results[FM10K_LPORT_STATE_MSG_XCAST_MODE];

		/* XCAST mode update requested */
		err = fm10k_tlv_attr_get_u8(result, &mode);
		अगर (err)
			वापस FM10K_ERR_PARAM;

		/* prep क्रम possible demotion depending on capabilities */
		mode = fm10k_iov_supported_xcast_mode_pf(vf_info, mode);

		/* अगर mode is not currently enabled, enable it */
		अगर (!(FM10K_VF_FLAG_ENABLED(vf_info) & BIT(mode)))
			fm10k_update_xcast_mode_pf(hw, vf_info->glort, mode);

		/* swap mode back to a bit flag */
		mode = FM10K_VF_FLAG_SET_MODE(mode);
	पूर्ण अन्यथा अगर (!results[FM10K_LPORT_STATE_MSG_DISABLE]) अणु
		/* need to disable the port अगर it is alपढ़ोy enabled */
		अगर (FM10K_VF_FLAG_ENABLED(vf_info))
			err = fm10k_update_lport_state_pf(hw, vf_info->glort,
							  1, false);

		/* we need to clear VF_FLAG_ENABLED flags in order to ensure
		 * that we actually re-enable the LPORT state below. Note that
		 * this has no impact अगर the VF is alपढ़ोy disabled, as the
		 * flags are alपढ़ोy cleared.
		 */
		अगर (!err)
			vf_info->vf_flags = FM10K_VF_FLAG_CAPABLE(vf_info);

		/* when enabling the port we should reset the rate limiters */
		hw->iov.ops.configure_tc(hw, vf_info->vf_idx, vf_info->rate);

		/* set mode क्रम minimal functionality */
		mode = FM10K_VF_FLAG_SET_MODE_NONE;

		/* generate port state response to notअगरy VF it is पढ़ोy */
		fm10k_tlv_msg_init(msg, FM10K_VF_MSG_ID_LPORT_STATE);
		fm10k_tlv_attr_put_bool(msg, FM10K_LPORT_STATE_MSG_READY);
		mbx->ops.enqueue_tx(hw, mbx, msg);
	पूर्ण

	/* अगर enable state toggled note the update */
	अगर (!err && (!FM10K_VF_FLAG_ENABLED(vf_info) != !mode))
		err = fm10k_update_lport_state_pf(hw, vf_info->glort, 1,
						  !!mode);

	/* अगर state change succeeded, then update our stored state */
	mode |= FM10K_VF_FLAG_CAPABLE(vf_info);
	अगर (!err)
		vf_info->vf_flags = mode;

	वापस err;
पूर्ण

/**
 *  fm10k_update_hw_stats_pf - Updates hardware related statistics of PF
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @stats: poपूर्णांकer to the stats काष्ठाure to update
 *
 *  This function collects and aggregates global and per queue hardware
 *  statistics.
 **/
अटल व्योम fm10k_update_hw_stats_pf(काष्ठा fm10k_hw *hw,
				     काष्ठा fm10k_hw_stats *stats)
अणु
	u32 समयout, ur, ca, um, xec, vlan_drop, loopback_drop, nodesc_drop;
	u32 id, id_prev;

	/* Use Tx queue 0 as a canary to detect a reset */
	id = fm10k_पढ़ो_reg(hw, FM10K_TXQCTL(0));

	/* Read Global Statistics */
	करो अणु
		समयout = fm10k_पढ़ो_hw_stats_32b(hw, FM10K_STATS_TIMEOUT,
						  &stats->समयout);
		ur = fm10k_पढ़ो_hw_stats_32b(hw, FM10K_STATS_UR, &stats->ur);
		ca = fm10k_पढ़ो_hw_stats_32b(hw, FM10K_STATS_CA, &stats->ca);
		um = fm10k_पढ़ो_hw_stats_32b(hw, FM10K_STATS_UM, &stats->um);
		xec = fm10k_पढ़ो_hw_stats_32b(hw, FM10K_STATS_XEC, &stats->xec);
		vlan_drop = fm10k_पढ़ो_hw_stats_32b(hw, FM10K_STATS_VLAN_DROP,
						    &stats->vlan_drop);
		loopback_drop =
			fm10k_पढ़ो_hw_stats_32b(hw,
						FM10K_STATS_LOOPBACK_DROP,
						&stats->loopback_drop);
		nodesc_drop = fm10k_पढ़ो_hw_stats_32b(hw,
						      FM10K_STATS_NODESC_DROP,
						      &stats->nodesc_drop);

		/* अगर value has not changed then we have consistent data */
		id_prev = id;
		id = fm10k_पढ़ो_reg(hw, FM10K_TXQCTL(0));
	पूर्ण जबतक ((id ^ id_prev) & FM10K_TXQCTL_ID_MASK);

	/* drop non-ID bits and set VALID ID bit */
	id &= FM10K_TXQCTL_ID_MASK;
	id |= FM10K_STAT_VALID;

	/* Update Global Statistics */
	अगर (stats->stats_idx == id) अणु
		stats->समयout.count += समयout;
		stats->ur.count += ur;
		stats->ca.count += ca;
		stats->um.count += um;
		stats->xec.count += xec;
		stats->vlan_drop.count += vlan_drop;
		stats->loopback_drop.count += loopback_drop;
		stats->nodesc_drop.count += nodesc_drop;
	पूर्ण

	/* Update bases and record current PF id */
	fm10k_update_hw_base_32b(&stats->समयout, समयout);
	fm10k_update_hw_base_32b(&stats->ur, ur);
	fm10k_update_hw_base_32b(&stats->ca, ca);
	fm10k_update_hw_base_32b(&stats->um, um);
	fm10k_update_hw_base_32b(&stats->xec, xec);
	fm10k_update_hw_base_32b(&stats->vlan_drop, vlan_drop);
	fm10k_update_hw_base_32b(&stats->loopback_drop, loopback_drop);
	fm10k_update_hw_base_32b(&stats->nodesc_drop, nodesc_drop);
	stats->stats_idx = id;

	/* Update Queue Statistics */
	fm10k_update_hw_stats_q(hw, stats->q, 0, hw->mac.max_queues);
पूर्ण

/**
 *  fm10k_rebind_hw_stats_pf - Resets base क्रम hardware statistics of PF
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @stats: poपूर्णांकer to the stats काष्ठाure to update
 *
 *  This function resets the base क्रम global and per queue hardware
 *  statistics.
 **/
अटल व्योम fm10k_rebind_hw_stats_pf(काष्ठा fm10k_hw *hw,
				     काष्ठा fm10k_hw_stats *stats)
अणु
	/* Unbind Global Statistics */
	fm10k_unbind_hw_stats_32b(&stats->समयout);
	fm10k_unbind_hw_stats_32b(&stats->ur);
	fm10k_unbind_hw_stats_32b(&stats->ca);
	fm10k_unbind_hw_stats_32b(&stats->um);
	fm10k_unbind_hw_stats_32b(&stats->xec);
	fm10k_unbind_hw_stats_32b(&stats->vlan_drop);
	fm10k_unbind_hw_stats_32b(&stats->loopback_drop);
	fm10k_unbind_hw_stats_32b(&stats->nodesc_drop);

	/* Unbind Queue Statistics */
	fm10k_unbind_hw_stats_q(stats->q, 0, hw->mac.max_queues);

	/* Reinitialize bases क्रम all stats */
	fm10k_update_hw_stats_pf(hw, stats);
पूर्ण

/**
 *  fm10k_set_dma_mask_pf - Configures PhyAddrSpace to limit DMA to प्रणाली
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @dma_mask: 64 bit DMA mask required क्रम platक्रमm
 *
 *  This function sets the PHYADDR.PhyAddrSpace bits क्रम the endpoपूर्णांक in order
 *  to limit the access to memory beyond what is physically in the प्रणाली.
 **/
अटल व्योम fm10k_set_dma_mask_pf(काष्ठा fm10k_hw *hw, u64 dma_mask)
अणु
	/* we need to ग_लिखो the upper 32 bits of DMA mask to PhyAddrSpace */
	u32 phyaddr = (u32)(dma_mask >> 32);

	fm10k_ग_लिखो_reg(hw, FM10K_PHYADDR, phyaddr);
पूर्ण

/**
 *  fm10k_get_fault_pf - Record a fault in one of the पूर्णांकerface units
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @type: poपूर्णांकer to fault type रेजिस्टर offset
 *  @fault: poपूर्णांकer to memory location to record the fault
 *
 *  Record the fault रेजिस्टर contents to the fault data काष्ठाure and
 *  clear the entry from the रेजिस्टर.
 *
 *  Returns ERR_PARAM अगर invalid रेजिस्टर is specअगरied or no error is present.
 **/
अटल s32 fm10k_get_fault_pf(काष्ठा fm10k_hw *hw, पूर्णांक type,
			      काष्ठा fm10k_fault *fault)
अणु
	u32 func;

	/* verअगरy the fault रेजिस्टर is in range and is aligned */
	चयन (type) अणु
	हाल FM10K_PCA_FAULT:
	हाल FM10K_THI_FAULT:
	हाल FM10K_FUM_FAULT:
		अवरोध;
	शेष:
		वापस FM10K_ERR_PARAM;
	पूर्ण

	/* only service faults that are valid */
	func = fm10k_पढ़ो_reg(hw, type + FM10K_FAULT_FUNC);
	अगर (!(func & FM10K_FAULT_FUNC_VALID))
		वापस FM10K_ERR_PARAM;

	/* पढ़ो reमुख्यing fields */
	fault->address = fm10k_पढ़ो_reg(hw, type + FM10K_FAULT_ADDR_HI);
	fault->address <<= 32;
	fault->address |= fm10k_पढ़ो_reg(hw, type + FM10K_FAULT_ADDR_LO);
	fault->specinfo = fm10k_पढ़ो_reg(hw, type + FM10K_FAULT_SPECINFO);

	/* clear valid bit to allow क्रम next error */
	fm10k_ग_लिखो_reg(hw, type + FM10K_FAULT_FUNC, FM10K_FAULT_FUNC_VALID);

	/* Record which function triggered the error */
	अगर (func & FM10K_FAULT_FUNC_PF)
		fault->func = 0;
	अन्यथा
		fault->func = 1 + ((func & FM10K_FAULT_FUNC_VF_MASK) >>
				   FM10K_FAULT_FUNC_VF_SHIFT);

	/* record fault type */
	fault->type = func & FM10K_FAULT_FUNC_TYPE_MASK;

	वापस 0;
पूर्ण

/**
 *  fm10k_request_lport_map_pf - Request LPORT map from the चयन API
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 **/
अटल s32 fm10k_request_lport_map_pf(काष्ठा fm10k_hw *hw)
अणु
	काष्ठा fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[1];

	/* issue request asking क्रम LPORT map */
	fm10k_tlv_msg_init(msg, FM10K_PF_MSG_ID_LPORT_MAP);

	/* load onto outgoing mailbox */
	वापस mbx->ops.enqueue_tx(hw, mbx, msg);
पूर्ण

/**
 *  fm10k_get_host_state_pf - Returns the state of the चयन and mailbox
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @चयन_पढ़ोy: poपूर्णांकer to boolean value that will record चयन state
 *
 *  This function will check the DMA_CTRL2 रेजिस्टर and mailbox in order
 *  to determine अगर the चयन is पढ़ोy क्रम the PF to begin requesting
 *  addresses and mapping traffic to the local पूर्णांकerface.
 **/
अटल s32 fm10k_get_host_state_pf(काष्ठा fm10k_hw *hw, bool *चयन_पढ़ोy)
अणु
	u32 dma_ctrl2;

	/* verअगरy the चयन is पढ़ोy क्रम पूर्णांकeraction */
	dma_ctrl2 = fm10k_पढ़ो_reg(hw, FM10K_DMA_CTRL2);
	अगर (!(dma_ctrl2 & FM10K_DMA_CTRL2_SWITCH_READY))
		वापस 0;

	/* retrieve generic host state info */
	वापस fm10k_get_host_state_generic(hw, चयन_पढ़ोy);
पूर्ण

/* This काष्ठाure defines the attibutes to be parsed below */
स्थिर काष्ठा fm10k_tlv_attr fm10k_lport_map_msg_attr[] = अणु
	FM10K_TLV_ATTR_LE_STRUCT(FM10K_PF_ATTR_ID_ERR,
				 माप(काष्ठा fm10k_swapi_error)),
	FM10K_TLV_ATTR_U32(FM10K_PF_ATTR_ID_LPORT_MAP),
	FM10K_TLV_ATTR_LAST
पूर्ण;

/**
 *  fm10k_msg_lport_map_pf - Message handler क्रम lport_map message from SM
 *  @hw: Poपूर्णांकer to hardware काष्ठाure
 *  @results: poपूर्णांकer array containing parsed data
 *  @mbx: Poपूर्णांकer to mailbox inक्रमmation काष्ठाure
 *
 *  This handler configures the lport mapping based on the reply from the
 *  चयन API.
 **/
s32 fm10k_msg_lport_map_pf(काष्ठा fm10k_hw *hw, u32 **results,
			   काष्ठा fm10k_mbx_info __always_unused *mbx)
अणु
	u16 glort, mask;
	u32 dglort_map;
	s32 err;

	err = fm10k_tlv_attr_get_u32(results[FM10K_PF_ATTR_ID_LPORT_MAP],
				     &dglort_map);
	अगर (err)
		वापस err;

	/* extract values out of the header */
	glort = FM10K_MSG_HDR_FIELD_GET(dglort_map, LPORT_MAP_GLORT);
	mask = FM10K_MSG_HDR_FIELD_GET(dglort_map, LPORT_MAP_MASK);

	/* verअगरy mask is set and none of the masked bits in glort are set */
	अगर (!mask || (glort & ~mask))
		वापस FM10K_ERR_PARAM;

	/* verअगरy the mask is contiguous, and that it is 1's followed by 0's */
	अगर (((~(mask - 1) & mask) + mask) & FM10K_DGLORTMAP_NONE)
		वापस FM10K_ERR_PARAM;

	/* record the glort, mask, and port count */
	hw->mac.dglort_map = dglort_map;

	वापस 0;
पूर्ण

स्थिर काष्ठा fm10k_tlv_attr fm10k_update_pvid_msg_attr[] = अणु
	FM10K_TLV_ATTR_U32(FM10K_PF_ATTR_ID_UPDATE_PVID),
	FM10K_TLV_ATTR_LAST
पूर्ण;

/**
 *  fm10k_msg_update_pvid_pf - Message handler क्रम port VLAN message from SM
 *  @hw: Poपूर्णांकer to hardware काष्ठाure
 *  @results: poपूर्णांकer array containing parsed data
 *  @mbx: Poपूर्णांकer to mailbox inक्रमmation काष्ठाure
 *
 *  This handler configures the शेष VLAN क्रम the PF
 **/
अटल s32 fm10k_msg_update_pvid_pf(काष्ठा fm10k_hw *hw, u32 **results,
				    काष्ठा fm10k_mbx_info __always_unused *mbx)
अणु
	u16 glort, pvid;
	u32 pvid_update;
	s32 err;

	err = fm10k_tlv_attr_get_u32(results[FM10K_PF_ATTR_ID_UPDATE_PVID],
				     &pvid_update);
	अगर (err)
		वापस err;

	/* extract values from the pvid update */
	glort = FM10K_MSG_HDR_FIELD_GET(pvid_update, UPDATE_PVID_GLORT);
	pvid = FM10K_MSG_HDR_FIELD_GET(pvid_update, UPDATE_PVID_PVID);

	/* अगर glort is not valid वापस error */
	अगर (!fm10k_glort_valid_pf(hw, glort))
		वापस FM10K_ERR_PARAM;

	/* verअगरy VLAN ID is valid */
	अगर (pvid >= FM10K_VLAN_TABLE_VID_MAX)
		वापस FM10K_ERR_PARAM;

	/* record the port VLAN ID value */
	hw->mac.शेष_vid = pvid;

	वापस 0;
पूर्ण

/**
 *  fm10k_record_global_table_data - Move global table data to swapi table info
 *  @from: poपूर्णांकer to source table data काष्ठाure
 *  @to: poपूर्णांकer to destination table info काष्ठाure
 *
 *  This function is will copy table_data to the table_info contained in
 *  the hw काष्ठा.
 **/
अटल व्योम fm10k_record_global_table_data(काष्ठा fm10k_global_table_data *from,
					   काष्ठा fm10k_swapi_table_info *to)
अणु
	/* convert from le32 काष्ठा to CPU byte ordered values */
	to->used = le32_to_cpu(from->used);
	to->avail = le32_to_cpu(from->avail);
पूर्ण

स्थिर काष्ठा fm10k_tlv_attr fm10k_err_msg_attr[] = अणु
	FM10K_TLV_ATTR_LE_STRUCT(FM10K_PF_ATTR_ID_ERR,
				 माप(काष्ठा fm10k_swapi_error)),
	FM10K_TLV_ATTR_LAST
पूर्ण;

/**
 *  fm10k_msg_err_pf - Message handler क्रम error reply
 *  @hw: Poपूर्णांकer to hardware काष्ठाure
 *  @results: poपूर्णांकer array containing parsed data
 *  @mbx: Poपूर्णांकer to mailbox inक्रमmation काष्ठाure
 *
 *  This handler will capture the data क्रम any error replies to previous
 *  messages that the PF has sent.
 **/
s32 fm10k_msg_err_pf(काष्ठा fm10k_hw *hw, u32 **results,
		     काष्ठा fm10k_mbx_info __always_unused *mbx)
अणु
	काष्ठा fm10k_swapi_error err_msg;
	s32 err;

	/* extract काष्ठाure from message */
	err = fm10k_tlv_attr_get_le_काष्ठा(results[FM10K_PF_ATTR_ID_ERR],
					   &err_msg, माप(err_msg));
	अगर (err)
		वापस err;

	/* record table status */
	fm10k_record_global_table_data(&err_msg.mac, &hw->swapi.mac);
	fm10k_record_global_table_data(&err_msg.nexthop, &hw->swapi.nexthop);
	fm10k_record_global_table_data(&err_msg.ffu, &hw->swapi.ffu);

	/* record SW API status value */
	hw->swapi.status = le32_to_cpu(err_msg.status);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fm10k_msg_data fm10k_msg_data_pf[] = अणु
	FM10K_PF_MSG_ERR_HANDLER(XCAST_MODES, fm10k_msg_err_pf),
	FM10K_PF_MSG_ERR_HANDLER(UPDATE_MAC_FWD_RULE, fm10k_msg_err_pf),
	FM10K_PF_MSG_LPORT_MAP_HANDLER(fm10k_msg_lport_map_pf),
	FM10K_PF_MSG_ERR_HANDLER(LPORT_CREATE, fm10k_msg_err_pf),
	FM10K_PF_MSG_ERR_HANDLER(LPORT_DELETE, fm10k_msg_err_pf),
	FM10K_PF_MSG_UPDATE_PVID_HANDLER(fm10k_msg_update_pvid_pf),
	FM10K_TLV_MSG_ERROR_HANDLER(fm10k_tlv_msg_error),
पूर्ण;

अटल स्थिर काष्ठा fm10k_mac_ops mac_ops_pf = अणु
	.get_bus_info		= fm10k_get_bus_info_generic,
	.reset_hw		= fm10k_reset_hw_pf,
	.init_hw		= fm10k_init_hw_pf,
	.start_hw		= fm10k_start_hw_generic,
	.stop_hw		= fm10k_stop_hw_generic,
	.update_vlan		= fm10k_update_vlan_pf,
	.पढ़ो_mac_addr		= fm10k_पढ़ो_mac_addr_pf,
	.update_uc_addr		= fm10k_update_uc_addr_pf,
	.update_mc_addr		= fm10k_update_mc_addr_pf,
	.update_xcast_mode	= fm10k_update_xcast_mode_pf,
	.update_पूर्णांक_moderator	= fm10k_update_पूर्णांक_moderator_pf,
	.update_lport_state	= fm10k_update_lport_state_pf,
	.update_hw_stats	= fm10k_update_hw_stats_pf,
	.rebind_hw_stats	= fm10k_rebind_hw_stats_pf,
	.configure_dglort_map	= fm10k_configure_dglort_map_pf,
	.set_dma_mask		= fm10k_set_dma_mask_pf,
	.get_fault		= fm10k_get_fault_pf,
	.get_host_state		= fm10k_get_host_state_pf,
	.request_lport_map	= fm10k_request_lport_map_pf,
पूर्ण;

अटल स्थिर काष्ठा fm10k_iov_ops iov_ops_pf = अणु
	.assign_resources		= fm10k_iov_assign_resources_pf,
	.configure_tc			= fm10k_iov_configure_tc_pf,
	.assign_पूर्णांक_moderator		= fm10k_iov_assign_पूर्णांक_moderator_pf,
	.assign_शेष_mac_vlan	= fm10k_iov_assign_शेष_mac_vlan_pf,
	.reset_resources		= fm10k_iov_reset_resources_pf,
	.set_lport			= fm10k_iov_set_lport_pf,
	.reset_lport			= fm10k_iov_reset_lport_pf,
	.update_stats			= fm10k_iov_update_stats_pf,
पूर्ण;

अटल s32 fm10k_get_invariants_pf(काष्ठा fm10k_hw *hw)
अणु
	fm10k_get_invariants_generic(hw);

	वापस fm10k_sm_mbx_init(hw, &hw->mbx, fm10k_msg_data_pf);
पूर्ण

स्थिर काष्ठा fm10k_info fm10k_pf_info = अणु
	.mac		= fm10k_mac_pf,
	.get_invariants	= fm10k_get_invariants_pf,
	.mac_ops	= &mac_ops_pf,
	.iov_ops	= &iov_ops_pf,
पूर्ण;
