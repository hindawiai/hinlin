<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश "e1000.h"

/**
 *  e1000e_get_bus_info_pcie - Get PCIe bus inक्रमmation
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Determines and stores the प्रणाली bus inक्रमmation क्रम a particular
 *  network पूर्णांकerface.  The following bus inक्रमmation is determined and stored:
 *  bus speed, bus width, type (PCIe), and PCIe function.
 **/
s32 e1000e_get_bus_info_pcie(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	काष्ठा e1000_bus_info *bus = &hw->bus;
	काष्ठा e1000_adapter *adapter = hw->adapter;
	u16 pcie_link_status, cap_offset;

	cap_offset = adapter->pdev->pcie_cap;
	अगर (!cap_offset) अणु
		bus->width = e1000_bus_width_unknown;
	पूर्ण अन्यथा अणु
		pci_पढ़ो_config_word(adapter->pdev,
				     cap_offset + PCIE_LINK_STATUS,
				     &pcie_link_status);
		bus->width = (क्रमागत e1000_bus_width)((pcie_link_status &
						     PCIE_LINK_WIDTH_MASK) >>
						    PCIE_LINK_WIDTH_SHIFT);
	पूर्ण

	mac->ops.set_lan_id(hw);

	वापस 0;
पूर्ण

/**
 *  e1000_set_lan_id_multi_port_pcie - Set LAN id क्रम PCIe multiple port devices
 *
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Determines the LAN function id by पढ़ोing memory-mapped रेजिस्टरs
 *  and swaps the port value अगर requested.
 **/
व्योम e1000_set_lan_id_multi_port_pcie(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_bus_info *bus = &hw->bus;
	u32 reg;

	/* The status रेजिस्टर reports the correct function number
	 * क्रम the device regardless of function swap state.
	 */
	reg = er32(STATUS);
	bus->func = (reg & E1000_STATUS_FUNC_MASK) >> E1000_STATUS_FUNC_SHIFT;
पूर्ण

/**
 *  e1000_set_lan_id_single_port - Set LAN id क्रम a single port device
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Sets the LAN function id to zero क्रम a single port device.
 **/
व्योम e1000_set_lan_id_single_port(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_bus_info *bus = &hw->bus;

	bus->func = 0;
पूर्ण

/**
 *  e1000_clear_vfta_generic - Clear VLAN filter table
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Clears the रेजिस्टर array which contains the VLAN filter table by
 *  setting all the values to 0.
 **/
व्योम e1000_clear_vfta_generic(काष्ठा e1000_hw *hw)
अणु
	u32 offset;

	क्रम (offset = 0; offset < E1000_VLAN_FILTER_TBL_SIZE; offset++) अणु
		E1000_WRITE_REG_ARRAY(hw, E1000_VFTA, offset, 0);
		e1e_flush();
	पूर्ण
पूर्ण

/**
 *  e1000_ग_लिखो_vfta_generic - Write value to VLAN filter table
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset in VLAN filter table
 *  @value: रेजिस्टर value written to VLAN filter table
 *
 *  Writes value at the given offset in the रेजिस्टर array which stores
 *  the VLAN filter table.
 **/
व्योम e1000_ग_लिखो_vfta_generic(काष्ठा e1000_hw *hw, u32 offset, u32 value)
अणु
	E1000_WRITE_REG_ARRAY(hw, E1000_VFTA, offset, value);
	e1e_flush();
पूर्ण

/**
 *  e1000e_init_rx_addrs - Initialize receive address's
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @rar_count: receive address रेजिस्टरs
 *
 *  Setup the receive address रेजिस्टरs by setting the base receive address
 *  रेजिस्टर to the devices MAC address and clearing all the other receive
 *  address रेजिस्टरs to 0.
 **/
व्योम e1000e_init_rx_addrs(काष्ठा e1000_hw *hw, u16 rar_count)
अणु
	u32 i;
	u8 mac_addr[ETH_ALEN] = अणु 0 पूर्ण;

	/* Setup the receive address */
	e_dbg("Programming MAC Address into RAR[0]\n");

	hw->mac.ops.rar_set(hw, hw->mac.addr, 0);

	/* Zero out the other (rar_entry_count - 1) receive addresses */
	e_dbg("Clearing RAR[1-%u]\n", rar_count - 1);
	क्रम (i = 1; i < rar_count; i++)
		hw->mac.ops.rar_set(hw, mac_addr, i);
पूर्ण

/**
 *  e1000_check_alt_mac_addr_generic - Check क्रम alternate MAC addr
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Checks the nvm क्रम an alternate MAC address.  An alternate MAC address
 *  can be setup by pre-boot software and must be treated like a permanent
 *  address and must override the actual permanent MAC address. If an
 *  alternate MAC address is found it is programmed पूर्णांकo RAR0, replacing
 *  the permanent address that was installed पूर्णांकo RAR0 by the Si on reset.
 *  This function will वापस SUCCESS unless it encounters an error जबतक
 *  पढ़ोing the EEPROM.
 **/
s32 e1000_check_alt_mac_addr_generic(काष्ठा e1000_hw *hw)
अणु
	u32 i;
	s32 ret_val;
	u16 offset, nvm_alt_mac_addr_offset, nvm_data;
	u8 alt_mac_addr[ETH_ALEN];

	ret_val = e1000_पढ़ो_nvm(hw, NVM_COMPAT, 1, &nvm_data);
	अगर (ret_val)
		वापस ret_val;

	/* not supported on 82573 */
	अगर (hw->mac.type == e1000_82573)
		वापस 0;

	ret_val = e1000_पढ़ो_nvm(hw, NVM_ALT_MAC_ADDR_PTR, 1,
				 &nvm_alt_mac_addr_offset);
	अगर (ret_val) अणु
		e_dbg("NVM Read Error\n");
		वापस ret_val;
	पूर्ण

	अगर ((nvm_alt_mac_addr_offset == 0xFFFF) ||
	    (nvm_alt_mac_addr_offset == 0x0000))
		/* There is no Alternate MAC Address */
		वापस 0;

	अगर (hw->bus.func == E1000_FUNC_1)
		nvm_alt_mac_addr_offset += E1000_ALT_MAC_ADDRESS_OFFSET_LAN1;
	क्रम (i = 0; i < ETH_ALEN; i += 2) अणु
		offset = nvm_alt_mac_addr_offset + (i >> 1);
		ret_val = e1000_पढ़ो_nvm(hw, offset, 1, &nvm_data);
		अगर (ret_val) अणु
			e_dbg("NVM Read Error\n");
			वापस ret_val;
		पूर्ण

		alt_mac_addr[i] = (u8)(nvm_data & 0xFF);
		alt_mac_addr[i + 1] = (u8)(nvm_data >> 8);
	पूर्ण

	/* अगर multicast bit is set, the alternate address will not be used */
	अगर (is_multicast_ether_addr(alt_mac_addr)) अणु
		e_dbg("Ignoring Alternate Mac Address with MC bit set\n");
		वापस 0;
	पूर्ण

	/* We have a valid alternate MAC address, and we want to treat it the
	 * same as the normal permanent MAC address stored by the HW पूर्णांकo the
	 * RAR. Do this by mapping this address पूर्णांकo RAR0.
	 */
	hw->mac.ops.rar_set(hw, alt_mac_addr, 0);

	वापस 0;
पूर्ण

u32 e1000e_rar_get_count_generic(काष्ठा e1000_hw *hw)
अणु
	वापस hw->mac.rar_entry_count;
पूर्ण

/**
 *  e1000e_rar_set_generic - Set receive address रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @addr: poपूर्णांकer to the receive address
 *  @index: receive address array रेजिस्टर
 *
 *  Sets the receive address array रेजिस्टर at index to the address passed
 *  in by addr.
 **/
पूर्णांक e1000e_rar_set_generic(काष्ठा e1000_hw *hw, u8 *addr, u32 index)
अणु
	u32 rar_low, rar_high;

	/* HW expects these in little endian so we reverse the byte order
	 * from network order (big endian) to little endian
	 */
	rar_low = ((u32)addr[0] | ((u32)addr[1] << 8) |
		   ((u32)addr[2] << 16) | ((u32)addr[3] << 24));

	rar_high = ((u32)addr[4] | ((u32)addr[5] << 8));

	/* If MAC address zero, no need to set the AV bit */
	अगर (rar_low || rar_high)
		rar_high |= E1000_RAH_AV;

	/* Some bridges will combine consecutive 32-bit ग_लिखोs पूर्णांकo
	 * a single burst ग_लिखो, which will malfunction on some parts.
	 * The flushes aव्योम this.
	 */
	ew32(RAL(index), rar_low);
	e1e_flush();
	ew32(RAH(index), rar_high);
	e1e_flush();

	वापस 0;
पूर्ण

/**
 *  e1000_hash_mc_addr - Generate a multicast hash value
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mc_addr: poपूर्णांकer to a multicast address
 *
 *  Generates a multicast address hash value which is used to determine
 *  the multicast filter table array address and new table value.
 **/
अटल u32 e1000_hash_mc_addr(काष्ठा e1000_hw *hw, u8 *mc_addr)
अणु
	u32 hash_value, hash_mask;
	u8 bit_shअगरt = 0;

	/* Register count multiplied by bits per रेजिस्टर */
	hash_mask = (hw->mac.mta_reg_count * 32) - 1;

	/* For a mc_filter_type of 0, bit_shअगरt is the number of left-shअगरts
	 * where 0xFF would still fall within the hash mask.
	 */
	जबतक (hash_mask >> bit_shअगरt != 0xFF)
		bit_shअगरt++;

	/* The portion of the address that is used क्रम the hash table
	 * is determined by the mc_filter_type setting.
	 * The algorithm is such that there is a total of 8 bits of shअगरting.
	 * The bit_shअगरt क्रम a mc_filter_type of 0 represents the number of
	 * left-shअगरts where the MSB of mc_addr[5] would still fall within
	 * the hash_mask.  Case 0 करोes this exactly.  Since there are a total
	 * of 8 bits of shअगरting, then mc_addr[4] will shअगरt right the
	 * reमुख्यing number of bits. Thus 8 - bit_shअगरt.  The rest of the
	 * हालs are a variation of this algorithm...essentially raising the
	 * number of bits to shअगरt mc_addr[5] left, जबतक still keeping the
	 * 8-bit shअगरting total.
	 *
	 * For example, given the following Destination MAC Address and an
	 * mta रेजिस्टर count of 128 (thus a 4096-bit vector and 0xFFF mask),
	 * we can see that the bit_shअगरt क्रम हाल 0 is 4.  These are the hash
	 * values resulting from each mc_filter_type...
	 * [0] [1] [2] [3] [4] [5]
	 * 01  AA  00  12  34  56
	 * LSB           MSB
	 *
	 * हाल 0: hash_value = ((0x34 >> 4) | (0x56 << 4)) & 0xFFF = 0x563
	 * हाल 1: hash_value = ((0x34 >> 3) | (0x56 << 5)) & 0xFFF = 0xAC6
	 * हाल 2: hash_value = ((0x34 >> 2) | (0x56 << 6)) & 0xFFF = 0x163
	 * हाल 3: hash_value = ((0x34 >> 0) | (0x56 << 8)) & 0xFFF = 0x634
	 */
	चयन (hw->mac.mc_filter_type) अणु
	शेष:
	हाल 0:
		अवरोध;
	हाल 1:
		bit_shअगरt += 1;
		अवरोध;
	हाल 2:
		bit_shअगरt += 2;
		अवरोध;
	हाल 3:
		bit_shअगरt += 4;
		अवरोध;
	पूर्ण

	hash_value = hash_mask & (((mc_addr[4] >> (8 - bit_shअगरt)) |
				   (((u16)mc_addr[5]) << bit_shअगरt)));

	वापस hash_value;
पूर्ण

/**
 *  e1000e_update_mc_addr_list_generic - Update Multicast addresses
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mc_addr_list: array of multicast addresses to program
 *  @mc_addr_count: number of multicast addresses to program
 *
 *  Updates entire Multicast Table Array.
 *  The caller must have a packed mc_addr_list of multicast addresses.
 **/
व्योम e1000e_update_mc_addr_list_generic(काष्ठा e1000_hw *hw,
					u8 *mc_addr_list, u32 mc_addr_count)
अणु
	u32 hash_value, hash_bit, hash_reg;
	पूर्णांक i;

	/* clear mta_shaकरोw */
	स_रखो(&hw->mac.mta_shaकरोw, 0, माप(hw->mac.mta_shaकरोw));

	/* update mta_shaकरोw from mc_addr_list */
	क्रम (i = 0; (u32)i < mc_addr_count; i++) अणु
		hash_value = e1000_hash_mc_addr(hw, mc_addr_list);

		hash_reg = (hash_value >> 5) & (hw->mac.mta_reg_count - 1);
		hash_bit = hash_value & 0x1F;

		hw->mac.mta_shaकरोw[hash_reg] |= BIT(hash_bit);
		mc_addr_list += (ETH_ALEN);
	पूर्ण

	/* replace the entire MTA table */
	क्रम (i = hw->mac.mta_reg_count - 1; i >= 0; i--)
		E1000_WRITE_REG_ARRAY(hw, E1000_MTA, i, hw->mac.mta_shaकरोw[i]);
	e1e_flush();
पूर्ण

/**
 *  e1000e_clear_hw_cntrs_base - Clear base hardware counters
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Clears the base hardware counters by पढ़ोing the counter रेजिस्टरs.
 **/
व्योम e1000e_clear_hw_cntrs_base(काष्ठा e1000_hw *hw)
अणु
	er32(CRCERRS);
	er32(SYMERRS);
	er32(MPC);
	er32(SCC);
	er32(ECOL);
	er32(MCC);
	er32(LATECOL);
	er32(COLC);
	er32(DC);
	er32(SEC);
	er32(RLEC);
	er32(XONRXC);
	er32(XONTXC);
	er32(XOFFRXC);
	er32(XOFFTXC);
	er32(FCRUC);
	er32(GPRC);
	er32(BPRC);
	er32(MPRC);
	er32(GPTC);
	er32(GORCL);
	er32(GORCH);
	er32(GOTCL);
	er32(GOTCH);
	er32(RNBC);
	er32(RUC);
	er32(RFC);
	er32(ROC);
	er32(RJC);
	er32(TORL);
	er32(TORH);
	er32(TOTL);
	er32(TOTH);
	er32(TPR);
	er32(TPT);
	er32(MPTC);
	er32(BPTC);
पूर्ण

/**
 *  e1000e_check_क्रम_copper_link - Check क्रम link (Copper)
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Checks to see of the link status of the hardware has changed.  If a
 *  change in link status has been detected, then we पढ़ो the PHY रेजिस्टरs
 *  to get the current speed/duplex अगर link exists.
 **/
s32 e1000e_check_क्रम_copper_link(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	s32 ret_val;
	bool link;

	/* We only want to go out to the PHY रेजिस्टरs to see अगर Auto-Neg
	 * has completed and/or अगर our link status has changed.  The
	 * get_link_status flag is set upon receiving a Link Status
	 * Change or Rx Sequence Error पूर्णांकerrupt.
	 */
	अगर (!mac->get_link_status)
		वापस 0;
	mac->get_link_status = false;

	/* First we want to see अगर the MII Status Register reports
	 * link.  If so, then we want to get the current speed/duplex
	 * of the PHY.
	 */
	ret_val = e1000e_phy_has_link_generic(hw, 1, 0, &link);
	अगर (ret_val || !link)
		जाओ out;

	/* Check अगर there was DownShअगरt, must be checked
	 * immediately after link-up
	 */
	e1000e_check_करोwnshअगरt(hw);

	/* If we are क्रमcing speed/duplex, then we simply वापस since
	 * we have alपढ़ोy determined whether we have link or not.
	 */
	अगर (!mac->स्वतःneg)
		वापस -E1000_ERR_CONFIG;

	/* Auto-Neg is enabled.  Auto Speed Detection takes care
	 * of MAC speed/duplex configuration.  So we only need to
	 * configure Collision Distance in the MAC.
	 */
	mac->ops.config_collision_dist(hw);

	/* Configure Flow Control now that Auto-Neg has completed.
	 * First, we need to restore the desired flow control
	 * settings because we may have had to re-स्वतःneg with a
	 * dअगरferent link partner.
	 */
	ret_val = e1000e_config_fc_after_link_up(hw);
	अगर (ret_val)
		e_dbg("Error configuring flow control\n");

	वापस ret_val;

out:
	mac->get_link_status = true;
	वापस ret_val;
पूर्ण

/**
 *  e1000e_check_क्रम_fiber_link - Check क्रम link (Fiber)
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Checks क्रम link up on the hardware.  If link is not up and we have
 *  a संकेत, then we need to क्रमce link up.
 **/
s32 e1000e_check_क्रम_fiber_link(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	u32 rxcw;
	u32 ctrl;
	u32 status;
	s32 ret_val;

	ctrl = er32(CTRL);
	status = er32(STATUS);
	rxcw = er32(RXCW);

	/* If we करोn't have link (स्वतः-negotiation failed or link partner
	 * cannot स्वतः-negotiate), the cable is plugged in (we have संकेत),
	 * and our link partner is not trying to स्वतः-negotiate with us (we
	 * are receiving idles or data), we need to क्रमce link up. We also
	 * need to give स्वतः-negotiation समय to complete, in हाल the cable
	 * was just plugged in. The स्वतःneg_failed flag करोes this.
	 */
	/* (ctrl & E1000_CTRL_SWDPIN1) == 1 == have संकेत */
	अगर ((ctrl & E1000_CTRL_SWDPIN1) && !(status & E1000_STATUS_LU) &&
	    !(rxcw & E1000_RXCW_C)) अणु
		अगर (!mac->स्वतःneg_failed) अणु
			mac->स्वतःneg_failed = true;
			वापस 0;
		पूर्ण
		e_dbg("NOT Rx'ing /C/, disable AutoNeg and force link.\n");

		/* Disable स्वतः-negotiation in the TXCW रेजिस्टर */
		ew32(TXCW, (mac->txcw & ~E1000_TXCW_ANE));

		/* Force link-up and also क्रमce full-duplex. */
		ctrl = er32(CTRL);
		ctrl |= (E1000_CTRL_SLU | E1000_CTRL_FD);
		ew32(CTRL, ctrl);

		/* Configure Flow Control after क्रमcing link up. */
		ret_val = e1000e_config_fc_after_link_up(hw);
		अगर (ret_val) अणु
			e_dbg("Error configuring flow control\n");
			वापस ret_val;
		पूर्ण
	पूर्ण अन्यथा अगर ((ctrl & E1000_CTRL_SLU) && (rxcw & E1000_RXCW_C)) अणु
		/* If we are क्रमcing link and we are receiving /C/ ordered
		 * sets, re-enable स्वतः-negotiation in the TXCW रेजिस्टर
		 * and disable क्रमced link in the Device Control रेजिस्टर
		 * in an attempt to स्वतः-negotiate with our link partner.
		 */
		e_dbg("Rx'ing /C/, enable AutoNeg and stop forcing link.\n");
		ew32(TXCW, mac->txcw);
		ew32(CTRL, (ctrl & ~E1000_CTRL_SLU));

		mac->serdes_has_link = true;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_check_क्रम_serdes_link - Check क्रम link (Serdes)
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Checks क्रम link up on the hardware.  If link is not up and we have
 *  a संकेत, then we need to क्रमce link up.
 **/
s32 e1000e_check_क्रम_serdes_link(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	u32 rxcw;
	u32 ctrl;
	u32 status;
	s32 ret_val;

	ctrl = er32(CTRL);
	status = er32(STATUS);
	rxcw = er32(RXCW);

	/* If we करोn't have link (स्वतः-negotiation failed or link partner
	 * cannot स्वतः-negotiate), and our link partner is not trying to
	 * स्वतः-negotiate with us (we are receiving idles or data),
	 * we need to क्रमce link up. We also need to give स्वतः-negotiation
	 * समय to complete.
	 */
	/* (ctrl & E1000_CTRL_SWDPIN1) == 1 == have संकेत */
	अगर (!(status & E1000_STATUS_LU) && !(rxcw & E1000_RXCW_C)) अणु
		अगर (!mac->स्वतःneg_failed) अणु
			mac->स्वतःneg_failed = true;
			वापस 0;
		पूर्ण
		e_dbg("NOT Rx'ing /C/, disable AutoNeg and force link.\n");

		/* Disable स्वतः-negotiation in the TXCW रेजिस्टर */
		ew32(TXCW, (mac->txcw & ~E1000_TXCW_ANE));

		/* Force link-up and also क्रमce full-duplex. */
		ctrl = er32(CTRL);
		ctrl |= (E1000_CTRL_SLU | E1000_CTRL_FD);
		ew32(CTRL, ctrl);

		/* Configure Flow Control after क्रमcing link up. */
		ret_val = e1000e_config_fc_after_link_up(hw);
		अगर (ret_val) अणु
			e_dbg("Error configuring flow control\n");
			वापस ret_val;
		पूर्ण
	पूर्ण अन्यथा अगर ((ctrl & E1000_CTRL_SLU) && (rxcw & E1000_RXCW_C)) अणु
		/* If we are क्रमcing link and we are receiving /C/ ordered
		 * sets, re-enable स्वतः-negotiation in the TXCW रेजिस्टर
		 * and disable क्रमced link in the Device Control रेजिस्टर
		 * in an attempt to स्वतः-negotiate with our link partner.
		 */
		e_dbg("Rx'ing /C/, enable AutoNeg and stop forcing link.\n");
		ew32(TXCW, mac->txcw);
		ew32(CTRL, (ctrl & ~E1000_CTRL_SLU));

		mac->serdes_has_link = true;
	पूर्ण अन्यथा अगर (!(E1000_TXCW_ANE & er32(TXCW))) अणु
		/* If we क्रमce link क्रम non-स्वतः-negotiation चयन, check
		 * link status based on MAC synchronization क्रम पूर्णांकernal
		 * serdes media type.
		 */
		/* SYNCH bit and IV bit are sticky. */
		usleep_range(10, 20);
		rxcw = er32(RXCW);
		अगर (rxcw & E1000_RXCW_SYNCH) अणु
			अगर (!(rxcw & E1000_RXCW_IV)) अणु
				mac->serdes_has_link = true;
				e_dbg("SERDES: Link up - forced.\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			mac->serdes_has_link = false;
			e_dbg("SERDES: Link down - force failed.\n");
		पूर्ण
	पूर्ण

	अगर (E1000_TXCW_ANE & er32(TXCW)) अणु
		status = er32(STATUS);
		अगर (status & E1000_STATUS_LU) अणु
			/* SYNCH bit and IV bit are sticky, so reपढ़ो rxcw. */
			usleep_range(10, 20);
			rxcw = er32(RXCW);
			अगर (rxcw & E1000_RXCW_SYNCH) अणु
				अगर (!(rxcw & E1000_RXCW_IV)) अणु
					mac->serdes_has_link = true;
					e_dbg("SERDES: Link up - autoneg completed successfully.\n");
				पूर्ण अन्यथा अणु
					mac->serdes_has_link = false;
					e_dbg("SERDES: Link down - invalid codewords detected in autoneg.\n");
				पूर्ण
			पूर्ण अन्यथा अणु
				mac->serdes_has_link = false;
				e_dbg("SERDES: Link down - no sync.\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			mac->serdes_has_link = false;
			e_dbg("SERDES: Link down - autoneg failed\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000_set_शेष_fc_generic - Set flow control शेष values
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Read the EEPROM क्रम the शेष values क्रम flow control and store the
 *  values.
 **/
अटल s32 e1000_set_शेष_fc_generic(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 nvm_data;

	/* Read and store word 0x0F of the EEPROM. This word contains bits
	 * that determine the hardware's शेष PAUSE (flow control) mode,
	 * a bit that determines whether the HW शेषs to enabling or
	 * disabling स्वतः-negotiation, and the direction of the
	 * SW defined pins. If there is no SW over-ride of the flow
	 * control setting, then the variable hw->fc will
	 * be initialized based on a value in the EEPROM.
	 */
	ret_val = e1000_पढ़ो_nvm(hw, NVM_INIT_CONTROL2_REG, 1, &nvm_data);

	अगर (ret_val) अणु
		e_dbg("NVM Read Error\n");
		वापस ret_val;
	पूर्ण

	अगर (!(nvm_data & NVM_WORD0F_PAUSE_MASK))
		hw->fc.requested_mode = e1000_fc_none;
	अन्यथा अगर ((nvm_data & NVM_WORD0F_PAUSE_MASK) == NVM_WORD0F_ASM_सूची)
		hw->fc.requested_mode = e1000_fc_tx_छोड़ो;
	अन्यथा
		hw->fc.requested_mode = e1000_fc_full;

	वापस 0;
पूर्ण

/**
 *  e1000e_setup_link_generic - Setup flow control and link settings
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Determines which flow control settings to use, then configures flow
 *  control.  Calls the appropriate media-specअगरic link configuration
 *  function.  Assuming the adapter has a valid link partner, a valid link
 *  should be established.  Assumes the hardware has previously been reset
 *  and the transmitter and receiver are not enabled.
 **/
s32 e1000e_setup_link_generic(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;

	/* In the हाल of the phy reset being blocked, we alपढ़ोy have a link.
	 * We करो not need to set it up again.
	 */
	अगर (hw->phy.ops.check_reset_block && hw->phy.ops.check_reset_block(hw))
		वापस 0;

	/* If requested flow control is set to शेष, set flow control
	 * based on the EEPROM flow control settings.
	 */
	अगर (hw->fc.requested_mode == e1000_fc_शेष) अणु
		ret_val = e1000_set_शेष_fc_generic(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	/* Save off the requested flow control mode क्रम use later.  Depending
	 * on the link partner's capabilities, we may or may not use this mode.
	 */
	hw->fc.current_mode = hw->fc.requested_mode;

	e_dbg("After fix-ups FlowControl is now = %x\n", hw->fc.current_mode);

	/* Call the necessary media_type subroutine to configure the link. */
	ret_val = hw->mac.ops.setup_physical_पूर्णांकerface(hw);
	अगर (ret_val)
		वापस ret_val;

	/* Initialize the flow control address, type, and PAUSE समयr
	 * रेजिस्टरs to their शेष values.  This is करोne even अगर flow
	 * control is disabled, because it करोes not hurt anything to
	 * initialize these रेजिस्टरs.
	 */
	e_dbg("Initializing the Flow Control address, type and timer regs\n");
	ew32(FCT, FLOW_CONTROL_TYPE);
	ew32(FCAH, FLOW_CONTROL_ADDRESS_HIGH);
	ew32(FCAL, FLOW_CONTROL_ADDRESS_LOW);

	ew32(FCTTV, hw->fc.छोड़ो_समय);

	वापस e1000e_set_fc_watermarks(hw);
पूर्ण

/**
 *  e1000_commit_fc_settings_generic - Configure flow control
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Write the flow control settings to the Transmit Config Word Register (TXCW)
 *  base on the flow control settings in e1000_mac_info.
 **/
अटल s32 e1000_commit_fc_settings_generic(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	u32 txcw;

	/* Check क्रम a software override of the flow control settings, and
	 * setup the device accordingly.  If स्वतः-negotiation is enabled, then
	 * software will have to set the "PAUSE" bits to the correct value in
	 * the Transmit Config Word Register (TXCW) and re-start स्वतः-
	 * negotiation.  However, अगर स्वतः-negotiation is disabled, then
	 * software will have to manually configure the two flow control enable
	 * bits in the CTRL रेजिस्टर.
	 *
	 * The possible values of the "fc" parameter are:
	 *      0:  Flow control is completely disabled
	 *      1:  Rx flow control is enabled (we can receive छोड़ो frames,
	 *          but not send छोड़ो frames).
	 *      2:  Tx flow control is enabled (we can send छोड़ो frames but we
	 *          करो not support receiving छोड़ो frames).
	 *      3:  Both Rx and Tx flow control (symmetric) are enabled.
	 */
	चयन (hw->fc.current_mode) अणु
	हाल e1000_fc_none:
		/* Flow control completely disabled by a software over-ride. */
		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD);
		अवरोध;
	हाल e1000_fc_rx_छोड़ो:
		/* Rx Flow control is enabled and Tx Flow control is disabled
		 * by a software over-ride. Since there really isn't a way to
		 * advertise that we are capable of Rx Pause ONLY, we will
		 * advertise that we support both symmetric and asymmetric Rx
		 * PAUSE.  Later, we will disable the adapter's ability to send
		 * PAUSE frames.
		 */
		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD | E1000_TXCW_PAUSE_MASK);
		अवरोध;
	हाल e1000_fc_tx_छोड़ो:
		/* Tx Flow control is enabled, and Rx Flow control is disabled,
		 * by a software over-ride.
		 */
		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD | E1000_TXCW_ASM_सूची);
		अवरोध;
	हाल e1000_fc_full:
		/* Flow control (both Rx and Tx) is enabled by a software
		 * over-ride.
		 */
		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD | E1000_TXCW_PAUSE_MASK);
		अवरोध;
	शेष:
		e_dbg("Flow control param set incorrectly\n");
		वापस -E1000_ERR_CONFIG;
	पूर्ण

	ew32(TXCW, txcw);
	mac->txcw = txcw;

	वापस 0;
पूर्ण

/**
 *  e1000_poll_fiber_serdes_link_generic - Poll क्रम link up
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Polls क्रम link up by पढ़ोing the status रेजिस्टर, अगर link fails to come
 *  up with स्वतः-negotiation, then the link is क्रमced अगर a संकेत is detected.
 **/
अटल s32 e1000_poll_fiber_serdes_link_generic(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	u32 i, status;
	s32 ret_val;

	/* If we have a संकेत (the cable is plugged in, or assumed true क्रम
	 * serdes media) then poll क्रम a "Link-Up" indication in the Device
	 * Status Register.  Time-out अगर a link isn't seen in 500 milliseconds
	 * seconds (Auto-negotiation should complete in less than 500
	 * milliseconds even अगर the other end is करोing it in SW).
	 */
	क्रम (i = 0; i < FIBER_LINK_UP_LIMIT; i++) अणु
		usleep_range(10000, 11000);
		status = er32(STATUS);
		अगर (status & E1000_STATUS_LU)
			अवरोध;
	पूर्ण
	अगर (i == FIBER_LINK_UP_LIMIT) अणु
		e_dbg("Never got a valid link from auto-neg!!!\n");
		mac->स्वतःneg_failed = true;
		/* AutoNeg failed to achieve a link, so we'll call
		 * mac->check_क्रम_link. This routine will क्रमce the
		 * link up अगर we detect a संकेत. This will allow us to
		 * communicate with non-स्वतःnegotiating link partners.
		 */
		ret_val = mac->ops.check_क्रम_link(hw);
		अगर (ret_val) अणु
			e_dbg("Error while checking for link\n");
			वापस ret_val;
		पूर्ण
		mac->स्वतःneg_failed = false;
	पूर्ण अन्यथा अणु
		mac->स्वतःneg_failed = false;
		e_dbg("Valid Link Found\n");
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_setup_fiber_serdes_link - Setup link क्रम fiber/serdes
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Configures collision distance and flow control क्रम fiber and serdes
 *  links.  Upon successful setup, poll क्रम link.
 **/
s32 e1000e_setup_fiber_serdes_link(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	s32 ret_val;

	ctrl = er32(CTRL);

	/* Take the link out of reset */
	ctrl &= ~E1000_CTRL_LRST;

	hw->mac.ops.config_collision_dist(hw);

	ret_val = e1000_commit_fc_settings_generic(hw);
	अगर (ret_val)
		वापस ret_val;

	/* Since स्वतः-negotiation is enabled, take the link out of reset (the
	 * link will be in reset, because we previously reset the chip). This
	 * will restart स्वतः-negotiation.  If स्वतः-negotiation is successful
	 * then the link-up status bit will be set and the flow control enable
	 * bits (RFCE and TFCE) will be set according to their negotiated value.
	 */
	e_dbg("Auto-negotiation enabled\n");

	ew32(CTRL, ctrl);
	e1e_flush();
	usleep_range(1000, 2000);

	/* For these adapters, the SW definable pin 1 is set when the optics
	 * detect a संकेत.  If we have a संकेत, then poll क्रम a "Link-Up"
	 * indication.
	 */
	अगर (hw->phy.media_type == e1000_media_type_पूर्णांकernal_serdes ||
	    (er32(CTRL) & E1000_CTRL_SWDPIN1)) अणु
		ret_val = e1000_poll_fiber_serdes_link_generic(hw);
	पूर्ण अन्यथा अणु
		e_dbg("No signal detected\n");
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000e_config_collision_dist_generic - Configure collision distance
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Configures the collision distance to the शेष value and is used
 *  during link setup.
 **/
व्योम e1000e_config_collision_dist_generic(काष्ठा e1000_hw *hw)
अणु
	u32 tctl;

	tctl = er32(TCTL);

	tctl &= ~E1000_TCTL_COLD;
	tctl |= E1000_COLLISION_DISTANCE << E1000_COLD_SHIFT;

	ew32(TCTL, tctl);
	e1e_flush();
पूर्ण

/**
 *  e1000e_set_fc_watermarks - Set flow control high/low watermarks
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Sets the flow control high/low threshold (watermark) रेजिस्टरs.  If
 *  flow control XON frame transmission is enabled, then set XON frame
 *  transmission as well.
 **/
s32 e1000e_set_fc_watermarks(काष्ठा e1000_hw *hw)
अणु
	u32 fcrtl = 0, fcrth = 0;

	/* Set the flow control receive threshold रेजिस्टरs.  Normally,
	 * these रेजिस्टरs will be set to a शेष threshold that may be
	 * adjusted later by the driver's runसमय code.  However, अगर the
	 * ability to transmit छोड़ो frames is not enabled, then these
	 * रेजिस्टरs will be set to 0.
	 */
	अगर (hw->fc.current_mode & e1000_fc_tx_छोड़ो) अणु
		/* We need to set up the Receive Threshold high and low water
		 * marks as well as (optionally) enabling the transmission of
		 * XON frames.
		 */
		fcrtl = hw->fc.low_water;
		अगर (hw->fc.send_xon)
			fcrtl |= E1000_FCRTL_XONE;

		fcrth = hw->fc.high_water;
	पूर्ण
	ew32(FCRTL, fcrtl);
	ew32(FCRTH, fcrth);

	वापस 0;
पूर्ण

/**
 *  e1000e_क्रमce_mac_fc - Force the MAC's flow control settings
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Force the MAC's flow control settings.  Sets the TFCE and RFCE bits in the
 *  device control रेजिस्टर to reflect the adapter settings.  TFCE and RFCE
 *  need to be explicitly set by software when a copper PHY is used because
 *  स्वतःnegotiation is managed by the PHY rather than the MAC.  Software must
 *  also configure these bits when link is क्रमced on a fiber connection.
 **/
s32 e1000e_क्रमce_mac_fc(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;

	ctrl = er32(CTRL);

	/* Because we didn't get link via the पूर्णांकernal स्वतः-negotiation
	 * mechanism (we either क्रमced link or we got link via PHY
	 * स्वतः-neg), we have to manually enable/disable transmit an
	 * receive flow control.
	 *
	 * The "Case" statement below enables/disable flow control
	 * according to the "hw->fc.current_mode" parameter.
	 *
	 * The possible values of the "fc" parameter are:
	 *      0:  Flow control is completely disabled
	 *      1:  Rx flow control is enabled (we can receive छोड़ो
	 *          frames but not send छोड़ो frames).
	 *      2:  Tx flow control is enabled (we can send छोड़ो frames
	 *          frames but we करो not receive छोड़ो frames).
	 *      3:  Both Rx and Tx flow control (symmetric) is enabled.
	 *  other:  No other values should be possible at this poपूर्णांक.
	 */
	e_dbg("hw->fc.current_mode = %u\n", hw->fc.current_mode);

	चयन (hw->fc.current_mode) अणु
	हाल e1000_fc_none:
		ctrl &= (~(E1000_CTRL_TFCE | E1000_CTRL_RFCE));
		अवरोध;
	हाल e1000_fc_rx_छोड़ो:
		ctrl &= (~E1000_CTRL_TFCE);
		ctrl |= E1000_CTRL_RFCE;
		अवरोध;
	हाल e1000_fc_tx_छोड़ो:
		ctrl &= (~E1000_CTRL_RFCE);
		ctrl |= E1000_CTRL_TFCE;
		अवरोध;
	हाल e1000_fc_full:
		ctrl |= (E1000_CTRL_TFCE | E1000_CTRL_RFCE);
		अवरोध;
	शेष:
		e_dbg("Flow control param set incorrectly\n");
		वापस -E1000_ERR_CONFIG;
	पूर्ण

	ew32(CTRL, ctrl);

	वापस 0;
पूर्ण

/**
 *  e1000e_config_fc_after_link_up - Configures flow control after link
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Checks the status of स्वतः-negotiation after link up to ensure that the
 *  speed and duplex were not क्रमced.  If the link needed to be क्रमced, then
 *  flow control needs to be क्रमced also.  If स्वतः-negotiation is enabled
 *  and did not fail, then we configure flow control based on our link
 *  partner.
 **/
s32 e1000e_config_fc_after_link_up(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	s32 ret_val = 0;
	u32 pcs_status_reg, pcs_adv_reg, pcs_lp_ability_reg, pcs_ctrl_reg;
	u16 mii_status_reg, mii_nway_adv_reg, mii_nway_lp_ability_reg;
	u16 speed, duplex;

	/* Check क्रम the हाल where we have fiber media and स्वतः-neg failed
	 * so we had to क्रमce link.  In this हाल, we need to क्रमce the
	 * configuration of the MAC to match the "fc" parameter.
	 */
	अगर (mac->स्वतःneg_failed) अणु
		अगर (hw->phy.media_type == e1000_media_type_fiber ||
		    hw->phy.media_type == e1000_media_type_पूर्णांकernal_serdes)
			ret_val = e1000e_क्रमce_mac_fc(hw);
	पूर्ण अन्यथा अणु
		अगर (hw->phy.media_type == e1000_media_type_copper)
			ret_val = e1000e_क्रमce_mac_fc(hw);
	पूर्ण

	अगर (ret_val) अणु
		e_dbg("Error forcing flow control settings\n");
		वापस ret_val;
	पूर्ण

	/* Check क्रम the हाल where we have copper media and स्वतः-neg is
	 * enabled.  In this हाल, we need to check and see अगर Auto-Neg
	 * has completed, and अगर so, how the PHY and link partner has
	 * flow control configured.
	 */
	अगर ((hw->phy.media_type == e1000_media_type_copper) && mac->स्वतःneg) अणु
		/* Read the MII Status Register and check to see अगर AutoNeg
		 * has completed.  We पढ़ो this twice because this reg has
		 * some "sticky" (latched) bits.
		 */
		ret_val = e1e_rphy(hw, MII_BMSR, &mii_status_reg);
		अगर (ret_val)
			वापस ret_val;
		ret_val = e1e_rphy(hw, MII_BMSR, &mii_status_reg);
		अगर (ret_val)
			वापस ret_val;

		अगर (!(mii_status_reg & BMSR_ANEGCOMPLETE)) अणु
			e_dbg("Copper PHY and Auto Neg has not completed.\n");
			वापस ret_val;
		पूर्ण

		/* The AutoNeg process has completed, so we now need to
		 * पढ़ो both the Auto Negotiation Advertisement
		 * Register (Address 4) and the Auto_Negotiation Base
		 * Page Ability Register (Address 5) to determine how
		 * flow control was negotiated.
		 */
		ret_val = e1e_rphy(hw, MII_ADVERTISE, &mii_nway_adv_reg);
		अगर (ret_val)
			वापस ret_val;
		ret_val = e1e_rphy(hw, MII_LPA, &mii_nway_lp_ability_reg);
		अगर (ret_val)
			वापस ret_val;

		/* Two bits in the Auto Negotiation Advertisement Register
		 * (Address 4) and two bits in the Auto Negotiation Base
		 * Page Ability Register (Address 5) determine flow control
		 * क्रम both the PHY and the link partner.  The following
		 * table, taken out of the IEEE 802.3ab/D6.0 dated March 25,
		 * 1999, describes these PAUSE resolution bits and how flow
		 * control is determined based upon these settings.
		 * NOTE:  DC = Don't Care
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | NIC Resolution
		 *-------|---------|-------|---------|--------------------
		 *   0   |    0    |  DC   |   DC    | e1000_fc_none
		 *   0   |    1    |   0   |   DC    | e1000_fc_none
		 *   0   |    1    |   1   |    0    | e1000_fc_none
		 *   0   |    1    |   1   |    1    | e1000_fc_tx_छोड़ो
		 *   1   |    0    |   0   |   DC    | e1000_fc_none
		 *   1   |   DC    |   1   |   DC    | e1000_fc_full
		 *   1   |    1    |   0   |    0    | e1000_fc_none
		 *   1   |    1    |   0   |    1    | e1000_fc_rx_छोड़ो
		 *
		 * Are both PAUSE bits set to 1?  If so, this implies
		 * Symmetric Flow Control is enabled at both ends.  The
		 * ASM_सूची bits are irrelevant per the spec.
		 *
		 * For Symmetric Flow Control:
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | Result
		 *-------|---------|-------|---------|--------------------
		 *   1   |   DC    |   1   |   DC    | E1000_fc_full
		 *
		 */
		अगर ((mii_nway_adv_reg & ADVERTISE_PAUSE_CAP) &&
		    (mii_nway_lp_ability_reg & LPA_PAUSE_CAP)) अणु
			/* Now we need to check अगर the user selected Rx ONLY
			 * of छोड़ो frames.  In this हाल, we had to advertise
			 * FULL flow control because we could not advertise Rx
			 * ONLY. Hence, we must now check to see अगर we need to
			 * turn OFF the TRANSMISSION of PAUSE frames.
			 */
			अगर (hw->fc.requested_mode == e1000_fc_full) अणु
				hw->fc.current_mode = e1000_fc_full;
				e_dbg("Flow Control = FULL.\n");
			पूर्ण अन्यथा अणु
				hw->fc.current_mode = e1000_fc_rx_छोड़ो;
				e_dbg("Flow Control = Rx PAUSE frames only.\n");
			पूर्ण
		पूर्ण
		/* For receiving PAUSE frames ONLY.
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | Result
		 *-------|---------|-------|---------|--------------------
		 *   0   |    1    |   1   |    1    | e1000_fc_tx_छोड़ो
		 */
		अन्यथा अगर (!(mii_nway_adv_reg & ADVERTISE_PAUSE_CAP) &&
			 (mii_nway_adv_reg & ADVERTISE_PAUSE_ASYM) &&
			 (mii_nway_lp_ability_reg & LPA_PAUSE_CAP) &&
			 (mii_nway_lp_ability_reg & LPA_PAUSE_ASYM)) अणु
			hw->fc.current_mode = e1000_fc_tx_छोड़ो;
			e_dbg("Flow Control = Tx PAUSE frames only.\n");
		पूर्ण
		/* For transmitting PAUSE frames ONLY.
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | Result
		 *-------|---------|-------|---------|--------------------
		 *   1   |    1    |   0   |    1    | e1000_fc_rx_छोड़ो
		 */
		अन्यथा अगर ((mii_nway_adv_reg & ADVERTISE_PAUSE_CAP) &&
			 (mii_nway_adv_reg & ADVERTISE_PAUSE_ASYM) &&
			 !(mii_nway_lp_ability_reg & LPA_PAUSE_CAP) &&
			 (mii_nway_lp_ability_reg & LPA_PAUSE_ASYM)) अणु
			hw->fc.current_mode = e1000_fc_rx_छोड़ो;
			e_dbg("Flow Control = Rx PAUSE frames only.\n");
		पूर्ण अन्यथा अणु
			/* Per the IEEE spec, at this poपूर्णांक flow control
			 * should be disabled.
			 */
			hw->fc.current_mode = e1000_fc_none;
			e_dbg("Flow Control = NONE.\n");
		पूर्ण

		/* Now we need to करो one last check...  If we स्वतः-
		 * negotiated to HALF DUPLEX, flow control should not be
		 * enabled per IEEE 802.3 spec.
		 */
		ret_val = mac->ops.get_link_up_info(hw, &speed, &duplex);
		अगर (ret_val) अणु
			e_dbg("Error getting link speed and duplex\n");
			वापस ret_val;
		पूर्ण

		अगर (duplex == HALF_DUPLEX)
			hw->fc.current_mode = e1000_fc_none;

		/* Now we call a subroutine to actually क्रमce the MAC
		 * controller to use the correct flow control settings.
		 */
		ret_val = e1000e_क्रमce_mac_fc(hw);
		अगर (ret_val) अणु
			e_dbg("Error forcing flow control settings\n");
			वापस ret_val;
		पूर्ण
	पूर्ण

	/* Check क्रम the हाल where we have SerDes media and स्वतः-neg is
	 * enabled.  In this हाल, we need to check and see अगर Auto-Neg
	 * has completed, and अगर so, how the PHY and link partner has
	 * flow control configured.
	 */
	अगर ((hw->phy.media_type == e1000_media_type_पूर्णांकernal_serdes) &&
	    mac->स्वतःneg) अणु
		/* Read the PCS_LSTS and check to see अगर AutoNeg
		 * has completed.
		 */
		pcs_status_reg = er32(PCS_LSTAT);

		अगर (!(pcs_status_reg & E1000_PCS_LSTS_AN_COMPLETE)) अणु
			e_dbg("PCS Auto Neg has not completed.\n");
			वापस ret_val;
		पूर्ण

		/* The AutoNeg process has completed, so we now need to
		 * पढ़ो both the Auto Negotiation Advertisement
		 * Register (PCS_ANADV) and the Auto_Negotiation Base
		 * Page Ability Register (PCS_LPAB) to determine how
		 * flow control was negotiated.
		 */
		pcs_adv_reg = er32(PCS_ANADV);
		pcs_lp_ability_reg = er32(PCS_LPAB);

		/* Two bits in the Auto Negotiation Advertisement Register
		 * (PCS_ANADV) and two bits in the Auto Negotiation Base
		 * Page Ability Register (PCS_LPAB) determine flow control
		 * क्रम both the PHY and the link partner.  The following
		 * table, taken out of the IEEE 802.3ab/D6.0 dated March 25,
		 * 1999, describes these PAUSE resolution bits and how flow
		 * control is determined based upon these settings.
		 * NOTE:  DC = Don't Care
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | NIC Resolution
		 *-------|---------|-------|---------|--------------------
		 *   0   |    0    |  DC   |   DC    | e1000_fc_none
		 *   0   |    1    |   0   |   DC    | e1000_fc_none
		 *   0   |    1    |   1   |    0    | e1000_fc_none
		 *   0   |    1    |   1   |    1    | e1000_fc_tx_छोड़ो
		 *   1   |    0    |   0   |   DC    | e1000_fc_none
		 *   1   |   DC    |   1   |   DC    | e1000_fc_full
		 *   1   |    1    |   0   |    0    | e1000_fc_none
		 *   1   |    1    |   0   |    1    | e1000_fc_rx_छोड़ो
		 *
		 * Are both PAUSE bits set to 1?  If so, this implies
		 * Symmetric Flow Control is enabled at both ends.  The
		 * ASM_सूची bits are irrelevant per the spec.
		 *
		 * For Symmetric Flow Control:
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | Result
		 *-------|---------|-------|---------|--------------------
		 *   1   |   DC    |   1   |   DC    | e1000_fc_full
		 *
		 */
		अगर ((pcs_adv_reg & E1000_TXCW_PAUSE) &&
		    (pcs_lp_ability_reg & E1000_TXCW_PAUSE)) अणु
			/* Now we need to check अगर the user selected Rx ONLY
			 * of छोड़ो frames.  In this हाल, we had to advertise
			 * FULL flow control because we could not advertise Rx
			 * ONLY. Hence, we must now check to see अगर we need to
			 * turn OFF the TRANSMISSION of PAUSE frames.
			 */
			अगर (hw->fc.requested_mode == e1000_fc_full) अणु
				hw->fc.current_mode = e1000_fc_full;
				e_dbg("Flow Control = FULL.\n");
			पूर्ण अन्यथा अणु
				hw->fc.current_mode = e1000_fc_rx_छोड़ो;
				e_dbg("Flow Control = Rx PAUSE frames only.\n");
			पूर्ण
		पूर्ण
		/* For receiving PAUSE frames ONLY.
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | Result
		 *-------|---------|-------|---------|--------------------
		 *   0   |    1    |   1   |    1    | e1000_fc_tx_छोड़ो
		 */
		अन्यथा अगर (!(pcs_adv_reg & E1000_TXCW_PAUSE) &&
			 (pcs_adv_reg & E1000_TXCW_ASM_सूची) &&
			 (pcs_lp_ability_reg & E1000_TXCW_PAUSE) &&
			 (pcs_lp_ability_reg & E1000_TXCW_ASM_सूची)) अणु
			hw->fc.current_mode = e1000_fc_tx_छोड़ो;
			e_dbg("Flow Control = Tx PAUSE frames only.\n");
		पूर्ण
		/* For transmitting PAUSE frames ONLY.
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | Result
		 *-------|---------|-------|---------|--------------------
		 *   1   |    1    |   0   |    1    | e1000_fc_rx_छोड़ो
		 */
		अन्यथा अगर ((pcs_adv_reg & E1000_TXCW_PAUSE) &&
			 (pcs_adv_reg & E1000_TXCW_ASM_सूची) &&
			 !(pcs_lp_ability_reg & E1000_TXCW_PAUSE) &&
			 (pcs_lp_ability_reg & E1000_TXCW_ASM_सूची)) अणु
			hw->fc.current_mode = e1000_fc_rx_छोड़ो;
			e_dbg("Flow Control = Rx PAUSE frames only.\n");
		पूर्ण अन्यथा अणु
			/* Per the IEEE spec, at this poपूर्णांक flow control
			 * should be disabled.
			 */
			hw->fc.current_mode = e1000_fc_none;
			e_dbg("Flow Control = NONE.\n");
		पूर्ण

		/* Now we call a subroutine to actually क्रमce the MAC
		 * controller to use the correct flow control settings.
		 */
		pcs_ctrl_reg = er32(PCS_LCTL);
		pcs_ctrl_reg |= E1000_PCS_LCTL_FORCE_FCTRL;
		ew32(PCS_LCTL, pcs_ctrl_reg);

		ret_val = e1000e_क्रमce_mac_fc(hw);
		अगर (ret_val) अणु
			e_dbg("Error forcing flow control settings\n");
			वापस ret_val;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_get_speed_and_duplex_copper - Retrieve current speed/duplex
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @speed: stores the current speed
 *  @duplex: stores the current duplex
 *
 *  Read the status रेजिस्टर क्रम the current speed/duplex and store the current
 *  speed and duplex क्रम copper connections.
 **/
s32 e1000e_get_speed_and_duplex_copper(काष्ठा e1000_hw *hw, u16 *speed,
				       u16 *duplex)
अणु
	u32 status;

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

	e_dbg("%u Mbps, %s Duplex\n",
	      *speed == SPEED_1000 ? 1000 : *speed == SPEED_100 ? 100 : 10,
	      *duplex == FULL_DUPLEX ? "Full" : "Half");

	वापस 0;
पूर्ण

/**
 *  e1000e_get_speed_and_duplex_fiber_serdes - Retrieve current speed/duplex
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @speed: stores the current speed
 *  @duplex: stores the current duplex
 *
 *  Sets the speed and duplex to gigabit full duplex (the only possible option)
 *  क्रम fiber/serdes links.
 **/
s32 e1000e_get_speed_and_duplex_fiber_serdes(काष्ठा e1000_hw __always_unused
					     *hw, u16 *speed, u16 *duplex)
अणु
	*speed = SPEED_1000;
	*duplex = FULL_DUPLEX;

	वापस 0;
पूर्ण

/**
 *  e1000e_get_hw_semaphore - Acquire hardware semaphore
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Acquire the HW semaphore to access the PHY or NVM
 **/
s32 e1000e_get_hw_semaphore(काष्ठा e1000_hw *hw)
अणु
	u32 swsm;
	s32 समयout = hw->nvm.word_size + 1;
	s32 i = 0;

	/* Get the SW semaphore */
	जबतक (i < समयout) अणु
		swsm = er32(SWSM);
		अगर (!(swsm & E1000_SWSM_SMBI))
			अवरोध;

		udelay(100);
		i++;
	पूर्ण

	अगर (i == समयout) अणु
		e_dbg("Driver can't access device - SMBI bit is set.\n");
		वापस -E1000_ERR_NVM;
	पूर्ण

	/* Get the FW semaphore. */
	क्रम (i = 0; i < समयout; i++) अणु
		swsm = er32(SWSM);
		ew32(SWSM, swsm | E1000_SWSM_SWESMBI);

		/* Semaphore acquired अगर bit latched */
		अगर (er32(SWSM) & E1000_SWSM_SWESMBI)
			अवरोध;

		udelay(100);
	पूर्ण

	अगर (i == समयout) अणु
		/* Release semaphores */
		e1000e_put_hw_semaphore(hw);
		e_dbg("Driver can't access the NVM\n");
		वापस -E1000_ERR_NVM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_put_hw_semaphore - Release hardware semaphore
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Release hardware semaphore used to access the PHY or NVM
 **/
व्योम e1000e_put_hw_semaphore(काष्ठा e1000_hw *hw)
अणु
	u32 swsm;

	swsm = er32(SWSM);
	swsm &= ~(E1000_SWSM_SMBI | E1000_SWSM_SWESMBI);
	ew32(SWSM, swsm);
पूर्ण

/**
 *  e1000e_get_स्वतः_rd_करोne - Check क्रम स्वतः पढ़ो completion
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Check EEPROM क्रम Auto Read करोne bit.
 **/
s32 e1000e_get_स्वतः_rd_करोne(काष्ठा e1000_hw *hw)
अणु
	s32 i = 0;

	जबतक (i < AUTO_READ_DONE_TIMEOUT) अणु
		अगर (er32(EECD) & E1000_EECD_AUTO_RD)
			अवरोध;
		usleep_range(1000, 2000);
		i++;
	पूर्ण

	अगर (i == AUTO_READ_DONE_TIMEOUT) अणु
		e_dbg("Auto read by HW from NVM has not completed.\n");
		वापस -E1000_ERR_RESET;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_valid_led_शेष - Verअगरy a valid शेष LED config
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @data: poपूर्णांकer to the NVM (EEPROM)
 *
 *  Read the EEPROM क्रम the current शेष LED configuration.  If the
 *  LED configuration is not valid, set to a valid LED configuration.
 **/
s32 e1000e_valid_led_शेष(काष्ठा e1000_hw *hw, u16 *data)
अणु
	s32 ret_val;

	ret_val = e1000_पढ़ो_nvm(hw, NVM_ID_LED_SETTINGS, 1, data);
	अगर (ret_val) अणु
		e_dbg("NVM Read Error\n");
		वापस ret_val;
	पूर्ण

	अगर (*data == ID_LED_RESERVED_0000 || *data == ID_LED_RESERVED_FFFF)
		*data = ID_LED_DEFAULT;

	वापस 0;
पूर्ण

/**
 *  e1000e_id_led_init_generic -
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 **/
s32 e1000e_id_led_init_generic(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	s32 ret_val;
	स्थिर u32 ledctl_mask = 0x000000FF;
	स्थिर u32 ledctl_on = E1000_LEDCTL_MODE_LED_ON;
	स्थिर u32 ledctl_off = E1000_LEDCTL_MODE_LED_OFF;
	u16 data, i, temp;
	स्थिर u16 led_mask = 0x0F;

	ret_val = hw->nvm.ops.valid_led_शेष(hw, &data);
	अगर (ret_val)
		वापस ret_val;

	mac->ledctl_शेष = er32(LEDCTL);
	mac->ledctl_mode1 = mac->ledctl_शेष;
	mac->ledctl_mode2 = mac->ledctl_शेष;

	क्रम (i = 0; i < 4; i++) अणु
		temp = (data >> (i << 2)) & led_mask;
		चयन (temp) अणु
		हाल ID_LED_ON1_DEF2:
		हाल ID_LED_ON1_ON2:
		हाल ID_LED_ON1_OFF2:
			mac->ledctl_mode1 &= ~(ledctl_mask << (i << 3));
			mac->ledctl_mode1 |= ledctl_on << (i << 3);
			अवरोध;
		हाल ID_LED_OFF1_DEF2:
		हाल ID_LED_OFF1_ON2:
		हाल ID_LED_OFF1_OFF2:
			mac->ledctl_mode1 &= ~(ledctl_mask << (i << 3));
			mac->ledctl_mode1 |= ledctl_off << (i << 3);
			अवरोध;
		शेष:
			/* Do nothing */
			अवरोध;
		पूर्ण
		चयन (temp) अणु
		हाल ID_LED_DEF1_ON2:
		हाल ID_LED_ON1_ON2:
		हाल ID_LED_OFF1_ON2:
			mac->ledctl_mode2 &= ~(ledctl_mask << (i << 3));
			mac->ledctl_mode2 |= ledctl_on << (i << 3);
			अवरोध;
		हाल ID_LED_DEF1_OFF2:
		हाल ID_LED_ON1_OFF2:
		हाल ID_LED_OFF1_OFF2:
			mac->ledctl_mode2 &= ~(ledctl_mask << (i << 3));
			mac->ledctl_mode2 |= ledctl_off << (i << 3);
			अवरोध;
		शेष:
			/* Do nothing */
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_setup_led_generic - Configures SW controllable LED
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  This prepares the SW controllable LED क्रम use and saves the current state
 *  of the LED so it can be later restored.
 **/
s32 e1000e_setup_led_generic(काष्ठा e1000_hw *hw)
अणु
	u32 ledctl;

	अगर (hw->mac.ops.setup_led != e1000e_setup_led_generic)
		वापस -E1000_ERR_CONFIG;

	अगर (hw->phy.media_type == e1000_media_type_fiber) अणु
		ledctl = er32(LEDCTL);
		hw->mac.ledctl_शेष = ledctl;
		/* Turn off LED0 */
		ledctl &= ~(E1000_LEDCTL_LED0_IVRT | E1000_LEDCTL_LED0_BLINK |
			    E1000_LEDCTL_LED0_MODE_MASK);
		ledctl |= (E1000_LEDCTL_MODE_LED_OFF <<
			   E1000_LEDCTL_LED0_MODE_SHIFT);
		ew32(LEDCTL, ledctl);
	पूर्ण अन्यथा अगर (hw->phy.media_type == e1000_media_type_copper) अणु
		ew32(LEDCTL, hw->mac.ledctl_mode1);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_cleanup_led_generic - Set LED config to शेष operation
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Remove the current LED configuration and set the LED configuration
 *  to the शेष value, saved from the EEPROM.
 **/
s32 e1000e_cleanup_led_generic(काष्ठा e1000_hw *hw)
अणु
	ew32(LEDCTL, hw->mac.ledctl_शेष);
	वापस 0;
पूर्ण

/**
 *  e1000e_blink_led_generic - Blink LED
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Blink the LEDs which are set to be on.
 **/
s32 e1000e_blink_led_generic(काष्ठा e1000_hw *hw)
अणु
	u32 ledctl_blink = 0;
	u32 i;

	अगर (hw->phy.media_type == e1000_media_type_fiber) अणु
		/* always blink LED0 क्रम PCI-E fiber */
		ledctl_blink = E1000_LEDCTL_LED0_BLINK |
		    (E1000_LEDCTL_MODE_LED_ON << E1000_LEDCTL_LED0_MODE_SHIFT);
	पूर्ण अन्यथा अणु
		/* Set the blink bit क्रम each LED that's "on" (0x0E)
		 * (or "off" अगर inverted) in ledctl_mode2.  The blink
		 * logic in hardware only works when mode is set to "on"
		 * so it must be changed accordingly when the mode is
		 * "off" and inverted.
		 */
		ledctl_blink = hw->mac.ledctl_mode2;
		क्रम (i = 0; i < 32; i += 8) अणु
			u32 mode = (hw->mac.ledctl_mode2 >> i) &
			    E1000_LEDCTL_LED0_MODE_MASK;
			u32 led_शेष = hw->mac.ledctl_शेष >> i;

			अगर ((!(led_शेष & E1000_LEDCTL_LED0_IVRT) &&
			     (mode == E1000_LEDCTL_MODE_LED_ON)) ||
			    ((led_शेष & E1000_LEDCTL_LED0_IVRT) &&
			     (mode == E1000_LEDCTL_MODE_LED_OFF))) अणु
				ledctl_blink &=
				    ~(E1000_LEDCTL_LED0_MODE_MASK << i);
				ledctl_blink |= (E1000_LEDCTL_LED0_BLINK |
						 E1000_LEDCTL_MODE_LED_ON) << i;
			पूर्ण
		पूर्ण
	पूर्ण

	ew32(LEDCTL, ledctl_blink);

	वापस 0;
पूर्ण

/**
 *  e1000e_led_on_generic - Turn LED on
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Turn LED on.
 **/
s32 e1000e_led_on_generic(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;

	चयन (hw->phy.media_type) अणु
	हाल e1000_media_type_fiber:
		ctrl = er32(CTRL);
		ctrl &= ~E1000_CTRL_SWDPIN0;
		ctrl |= E1000_CTRL_SWDPIO0;
		ew32(CTRL, ctrl);
		अवरोध;
	हाल e1000_media_type_copper:
		ew32(LEDCTL, hw->mac.ledctl_mode2);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_led_off_generic - Turn LED off
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Turn LED off.
 **/
s32 e1000e_led_off_generic(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;

	चयन (hw->phy.media_type) अणु
	हाल e1000_media_type_fiber:
		ctrl = er32(CTRL);
		ctrl |= E1000_CTRL_SWDPIN0;
		ctrl |= E1000_CTRL_SWDPIO0;
		ew32(CTRL, ctrl);
		अवरोध;
	हाल e1000_media_type_copper:
		ew32(LEDCTL, hw->mac.ledctl_mode1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_set_pcie_no_snoop - Set PCI-express capabilities
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @no_snoop: biपंचांगap of snoop events
 *
 *  Set the PCI-express रेजिस्टर to snoop क्रम events enabled in 'no_snoop'.
 **/
व्योम e1000e_set_pcie_no_snoop(काष्ठा e1000_hw *hw, u32 no_snoop)
अणु
	u32 gcr;

	अगर (no_snoop) अणु
		gcr = er32(GCR);
		gcr &= ~(PCIE_NO_SNOOP_ALL);
		gcr |= no_snoop;
		ew32(GCR, gcr);
	पूर्ण
पूर्ण

/**
 *  e1000e_disable_pcie_master - Disables PCI-express master access
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Returns 0 अगर successful, अन्यथा वापसs -10
 *  (-E1000_ERR_MASTER_REQUESTS_PENDING) अगर master disable bit has not caused
 *  the master requests to be disabled.
 *
 *  Disables PCI-Express master access and verअगरies there are no pending
 *  requests.
 **/
s32 e1000e_disable_pcie_master(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	s32 समयout = MASTER_DISABLE_TIMEOUT;

	ctrl = er32(CTRL);
	ctrl |= E1000_CTRL_GIO_MASTER_DISABLE;
	ew32(CTRL, ctrl);

	जबतक (समयout) अणु
		अगर (!(er32(STATUS) & E1000_STATUS_GIO_MASTER_ENABLE))
			अवरोध;
		usleep_range(100, 200);
		समयout--;
	पूर्ण

	अगर (!समयout) अणु
		e_dbg("Master requests are pending.\n");
		वापस -E1000_ERR_MASTER_REQUESTS_PENDING;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_reset_adaptive - Reset Adaptive Interframe Spacing
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Reset the Adaptive Interframe Spacing throttle to शेष values.
 **/
व्योम e1000e_reset_adaptive(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;

	अगर (!mac->adaptive_अगरs) अणु
		e_dbg("Not in Adaptive IFS mode!\n");
		वापस;
	पूर्ण

	mac->current_अगरs_val = 0;
	mac->अगरs_min_val = IFS_MIN;
	mac->अगरs_max_val = IFS_MAX;
	mac->अगरs_step_size = IFS_STEP;
	mac->अगरs_ratio = IFS_RATIO;

	mac->in_अगरs_mode = false;
	ew32(AIT, 0);
पूर्ण

/**
 *  e1000e_update_adaptive - Update Adaptive Interframe Spacing
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Update the Adaptive Interframe Spacing Throttle value based on the
 *  समय between transmitted packets and समय between collisions.
 **/
व्योम e1000e_update_adaptive(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;

	अगर (!mac->adaptive_अगरs) अणु
		e_dbg("Not in Adaptive IFS mode!\n");
		वापस;
	पूर्ण

	अगर ((mac->collision_delta * mac->अगरs_ratio) > mac->tx_packet_delta) अणु
		अगर (mac->tx_packet_delta > MIN_NUM_XMITS) अणु
			mac->in_अगरs_mode = true;
			अगर (mac->current_अगरs_val < mac->अगरs_max_val) अणु
				अगर (!mac->current_अगरs_val)
					mac->current_अगरs_val = mac->अगरs_min_val;
				अन्यथा
					mac->current_अगरs_val +=
					    mac->अगरs_step_size;
				ew32(AIT, mac->current_अगरs_val);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (mac->in_अगरs_mode &&
		    (mac->tx_packet_delta <= MIN_NUM_XMITS)) अणु
			mac->current_अगरs_val = 0;
			mac->in_अगरs_mode = false;
			ew32(AIT, 0);
		पूर्ण
	पूर्ण
पूर्ण
