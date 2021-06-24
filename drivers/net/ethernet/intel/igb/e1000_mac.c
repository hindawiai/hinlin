<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2007 - 2018 Intel Corporation. */

#समावेश <linux/अगर_ether.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>

#समावेश "e1000_mac.h"

#समावेश "igb.h"

अटल s32 igb_set_शेष_fc(काष्ठा e1000_hw *hw);
अटल व्योम igb_set_fc_watermarks(काष्ठा e1000_hw *hw);

/**
 *  igb_get_bus_info_pcie - Get PCIe bus inक्रमmation
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Determines and stores the प्रणाली bus inक्रमmation क्रम a particular
 *  network पूर्णांकerface.  The following bus inक्रमmation is determined and stored:
 *  bus speed, bus width, type (PCIe), and PCIe function.
 **/
s32 igb_get_bus_info_pcie(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_bus_info *bus = &hw->bus;
	s32 ret_val;
	u32 reg;
	u16 pcie_link_status;

	bus->type = e1000_bus_type_pci_express;

	ret_val = igb_पढ़ो_pcie_cap_reg(hw,
					PCI_EXP_LNKSTA,
					&pcie_link_status);
	अगर (ret_val) अणु
		bus->width = e1000_bus_width_unknown;
		bus->speed = e1000_bus_speed_unknown;
	पूर्ण अन्यथा अणु
		चयन (pcie_link_status & PCI_EXP_LNKSTA_CLS) अणु
		हाल PCI_EXP_LNKSTA_CLS_2_5GB:
			bus->speed = e1000_bus_speed_2500;
			अवरोध;
		हाल PCI_EXP_LNKSTA_CLS_5_0GB:
			bus->speed = e1000_bus_speed_5000;
			अवरोध;
		शेष:
			bus->speed = e1000_bus_speed_unknown;
			अवरोध;
		पूर्ण

		bus->width = (क्रमागत e1000_bus_width)((pcie_link_status &
						     PCI_EXP_LNKSTA_NLW) >>
						     PCI_EXP_LNKSTA_NLW_SHIFT);
	पूर्ण

	reg = rd32(E1000_STATUS);
	bus->func = (reg & E1000_STATUS_FUNC_MASK) >> E1000_STATUS_FUNC_SHIFT;

	वापस 0;
पूर्ण

/**
 *  igb_clear_vfta - Clear VLAN filter table
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Clears the रेजिस्टर array which contains the VLAN filter table by
 *  setting all the values to 0.
 **/
व्योम igb_clear_vfta(काष्ठा e1000_hw *hw)
अणु
	u32 offset;

	क्रम (offset = E1000_VLAN_FILTER_TBL_SIZE; offset--;)
		hw->mac.ops.ग_लिखो_vfta(hw, offset, 0);
पूर्ण

/**
 *  igb_ग_लिखो_vfta - Write value to VLAN filter table
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset in VLAN filter table
 *  @value: रेजिस्टर value written to VLAN filter table
 *
 *  Writes value at the given offset in the रेजिस्टर array which stores
 *  the VLAN filter table.
 **/
व्योम igb_ग_लिखो_vfta(काष्ठा e1000_hw *hw, u32 offset, u32 value)
अणु
	काष्ठा igb_adapter *adapter = hw->back;

	array_wr32(E1000_VFTA, offset, value);
	wrfl();

	adapter->shaकरोw_vfta[offset] = value;
पूर्ण

/**
 *  igb_init_rx_addrs - Initialize receive address's
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @rar_count: receive address रेजिस्टरs
 *
 *  Setups the receive address रेजिस्टरs by setting the base receive address
 *  रेजिस्टर to the devices MAC address and clearing all the other receive
 *  address रेजिस्टरs to 0.
 **/
व्योम igb_init_rx_addrs(काष्ठा e1000_hw *hw, u16 rar_count)
अणु
	u32 i;
	u8 mac_addr[ETH_ALEN] = अणु0पूर्ण;

	/* Setup the receive address */
	hw_dbg("Programming MAC Address into RAR[0]\n");

	hw->mac.ops.rar_set(hw, hw->mac.addr, 0);

	/* Zero out the other (rar_entry_count - 1) receive addresses */
	hw_dbg("Clearing RAR[1-%u]\n", rar_count-1);
	क्रम (i = 1; i < rar_count; i++)
		hw->mac.ops.rar_set(hw, mac_addr, i);
पूर्ण

/**
 *  igb_find_vlvf_slot - find the VLAN id or the first empty slot
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @vlan: VLAN id to ग_लिखो to VLAN filter
 *  @vlvf_bypass: skip VLVF अगर no match is found
 *
 *  वापस the VLVF index where this VLAN id should be placed
 *
 **/
अटल s32 igb_find_vlvf_slot(काष्ठा e1000_hw *hw, u32 vlan, bool vlvf_bypass)
अणु
	s32 regindex, first_empty_slot;
	u32 bits;

	/* लघु cut the special हाल */
	अगर (vlan == 0)
		वापस 0;

	/* अगर vlvf_bypass is set we करोn't want to use an empty slot, we
	 * will simply bypass the VLVF अगर there are no entries present in the
	 * VLVF that contain our VLAN
	 */
	first_empty_slot = vlvf_bypass ? -E1000_ERR_NO_SPACE : 0;

	/* Search क्रम the VLAN id in the VLVF entries. Save off the first empty
	 * slot found aदीर्घ the way.
	 *
	 * pre-decrement loop covering (IXGBE_VLVF_ENTRIES - 1) .. 1
	 */
	क्रम (regindex = E1000_VLVF_ARRAY_SIZE; --regindex > 0;) अणु
		bits = rd32(E1000_VLVF(regindex)) & E1000_VLVF_VLANID_MASK;
		अगर (bits == vlan)
			वापस regindex;
		अगर (!first_empty_slot && !bits)
			first_empty_slot = regindex;
	पूर्ण

	वापस first_empty_slot ? : -E1000_ERR_NO_SPACE;
पूर्ण

/**
 *  igb_vfta_set - enable or disable vlan in VLAN filter table
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @vlan: VLAN id to add or हटाओ
 *  @vind: VMDq output index that maps queue to VLAN id
 *  @vlan_on: अगर true add filter, अगर false हटाओ
 *  @vlvf_bypass: skip VLVF अगर no match is found
 *
 *  Sets or clears a bit in the VLAN filter table array based on VLAN id
 *  and अगर we are adding or removing the filter
 **/
s32 igb_vfta_set(काष्ठा e1000_hw *hw, u32 vlan, u32 vind,
		 bool vlan_on, bool vlvf_bypass)
अणु
	काष्ठा igb_adapter *adapter = hw->back;
	u32 regidx, vfta_delta, vfta, bits;
	s32 vlvf_index;

	अगर ((vlan > 4095) || (vind > 7))
		वापस -E1000_ERR_PARAM;

	/* this is a 2 part operation - first the VFTA, then the
	 * VLVF and VLVFB अगर VT Mode is set
	 * We करोn't ग_लिखो the VFTA until we know the VLVF part succeeded.
	 */

	/* Part 1
	 * The VFTA is a bitstring made up of 128 32-bit रेजिस्टरs
	 * that enable the particular VLAN id, much like the MTA:
	 *    bits[11-5]: which रेजिस्टर
	 *    bits[4-0]:  which bit in the रेजिस्टर
	 */
	regidx = vlan / 32;
	vfta_delta = BIT(vlan % 32);
	vfta = adapter->shaकरोw_vfta[regidx];

	/* vfta_delta represents the dअगरference between the current value
	 * of vfta and the value we want in the रेजिस्टर.  Since the dअगरf
	 * is an XOR mask we can just update vfta using an XOR.
	 */
	vfta_delta &= vlan_on ? ~vfta : vfta;
	vfta ^= vfta_delta;

	/* Part 2
	 * If VT Mode is set
	 *   Either vlan_on
	 *     make sure the VLAN is in VLVF
	 *     set the vind bit in the matching VLVFB
	 *   Or !vlan_on
	 *     clear the pool bit and possibly the vind
	 */
	अगर (!adapter->vfs_allocated_count)
		जाओ vfta_update;

	vlvf_index = igb_find_vlvf_slot(hw, vlan, vlvf_bypass);
	अगर (vlvf_index < 0) अणु
		अगर (vlvf_bypass)
			जाओ vfta_update;
		वापस vlvf_index;
	पूर्ण

	bits = rd32(E1000_VLVF(vlvf_index));

	/* set the pool bit */
	bits |= BIT(E1000_VLVF_POOLSEL_SHIFT + vind);
	अगर (vlan_on)
		जाओ vlvf_update;

	/* clear the pool bit */
	bits ^= BIT(E1000_VLVF_POOLSEL_SHIFT + vind);

	अगर (!(bits & E1000_VLVF_POOLSEL_MASK)) अणु
		/* Clear VFTA first, then disable VLVF.  Otherwise
		 * we run the risk of stray packets leaking पूर्णांकo
		 * the PF via the शेष pool
		 */
		अगर (vfta_delta)
			hw->mac.ops.ग_लिखो_vfta(hw, regidx, vfta);

		/* disable VLVF and clear reमुख्यing bit from pool */
		wr32(E1000_VLVF(vlvf_index), 0);

		वापस 0;
	पूर्ण

	/* If there are still bits set in the VLVFB रेजिस्टरs
	 * क्रम the VLAN ID indicated we need to see अगर the
	 * caller is requesting that we clear the VFTA entry bit.
	 * If the caller has requested that we clear the VFTA
	 * entry bit but there are still pools/VFs using this VLAN
	 * ID entry then ignore the request.  We're not worried
	 * about the हाल where we're turning the VFTA VLAN ID
	 * entry bit on, only when requested to turn it off as
	 * there may be multiple pools and/or VFs using the
	 * VLAN ID entry.  In that हाल we cannot clear the
	 * VFTA bit until all pools/VFs using that VLAN ID have also
	 * been cleared.  This will be indicated by "bits" being
	 * zero.
	 */
	vfta_delta = 0;

vlvf_update:
	/* record pool change and enable VLAN ID अगर not alपढ़ोy enabled */
	wr32(E1000_VLVF(vlvf_index), bits | vlan | E1000_VLVF_VLANID_ENABLE);

vfta_update:
	/* bit was set/cleared beक्रमe we started */
	अगर (vfta_delta)
		hw->mac.ops.ग_लिखो_vfta(hw, regidx, vfta);

	वापस 0;
पूर्ण

/**
 *  igb_check_alt_mac_addr - Check क्रम alternate MAC addr
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Checks the nvm क्रम an alternate MAC address.  An alternate MAC address
 *  can be setup by pre-boot software and must be treated like a permanent
 *  address and must override the actual permanent MAC address.  If an
 *  alternate MAC address is found it is saved in the hw काष्ठा and
 *  programmed पूर्णांकo RAR0 and the function वापसs success, otherwise the
 *  function वापसs an error.
 **/
s32 igb_check_alt_mac_addr(काष्ठा e1000_hw *hw)
अणु
	u32 i;
	s32 ret_val = 0;
	u16 offset, nvm_alt_mac_addr_offset, nvm_data;
	u8 alt_mac_addr[ETH_ALEN];

	/* Alternate MAC address is handled by the option ROM क्रम 82580
	 * and newer. SW support not required.
	 */
	अगर (hw->mac.type >= e1000_82580)
		जाओ out;

	ret_val = hw->nvm.ops.पढ़ो(hw, NVM_ALT_MAC_ADDR_PTR, 1,
				 &nvm_alt_mac_addr_offset);
	अगर (ret_val) अणु
		hw_dbg("NVM Read Error\n");
		जाओ out;
	पूर्ण

	अगर ((nvm_alt_mac_addr_offset == 0xFFFF) ||
	    (nvm_alt_mac_addr_offset == 0x0000))
		/* There is no Alternate MAC Address */
		जाओ out;

	अगर (hw->bus.func == E1000_FUNC_1)
		nvm_alt_mac_addr_offset += E1000_ALT_MAC_ADDRESS_OFFSET_LAN1;
	अगर (hw->bus.func == E1000_FUNC_2)
		nvm_alt_mac_addr_offset += E1000_ALT_MAC_ADDRESS_OFFSET_LAN2;

	अगर (hw->bus.func == E1000_FUNC_3)
		nvm_alt_mac_addr_offset += E1000_ALT_MAC_ADDRESS_OFFSET_LAN3;
	क्रम (i = 0; i < ETH_ALEN; i += 2) अणु
		offset = nvm_alt_mac_addr_offset + (i >> 1);
		ret_val = hw->nvm.ops.पढ़ो(hw, offset, 1, &nvm_data);
		अगर (ret_val) अणु
			hw_dbg("NVM Read Error\n");
			जाओ out;
		पूर्ण

		alt_mac_addr[i] = (u8)(nvm_data & 0xFF);
		alt_mac_addr[i + 1] = (u8)(nvm_data >> 8);
	पूर्ण

	/* अगर multicast bit is set, the alternate address will not be used */
	अगर (is_multicast_ether_addr(alt_mac_addr)) अणु
		hw_dbg("Ignoring Alternate Mac Address with MC bit set\n");
		जाओ out;
	पूर्ण

	/* We have a valid alternate MAC address, and we want to treat it the
	 * same as the normal permanent MAC address stored by the HW पूर्णांकo the
	 * RAR. Do this by mapping this address पूर्णांकo RAR0.
	 */
	hw->mac.ops.rar_set(hw, alt_mac_addr, 0);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_rar_set - Set receive address रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @addr: poपूर्णांकer to the receive address
 *  @index: receive address array रेजिस्टर
 *
 *  Sets the receive address array रेजिस्टर at index to the address passed
 *  in by addr.
 **/
व्योम igb_rar_set(काष्ठा e1000_hw *hw, u8 *addr, u32 index)
अणु
	u32 rar_low, rar_high;

	/* HW expects these in little endian so we reverse the byte order
	 * from network order (big endian) to little endian
	 */
	rar_low = ((u32) addr[0] |
		   ((u32) addr[1] << 8) |
		    ((u32) addr[2] << 16) | ((u32) addr[3] << 24));

	rar_high = ((u32) addr[4] | ((u32) addr[5] << 8));

	/* If MAC address zero, no need to set the AV bit */
	अगर (rar_low || rar_high)
		rar_high |= E1000_RAH_AV;

	/* Some bridges will combine consecutive 32-bit ग_लिखोs पूर्णांकo
	 * a single burst ग_लिखो, which will malfunction on some parts.
	 * The flushes aव्योम this.
	 */
	wr32(E1000_RAL(index), rar_low);
	wrfl();
	wr32(E1000_RAH(index), rar_high);
	wrfl();
पूर्ण

/**
 *  igb_mta_set - Set multicast filter table address
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @hash_value: determines the MTA रेजिस्टर and bit to set
 *
 *  The multicast table address is a रेजिस्टर array of 32-bit रेजिस्टरs.
 *  The hash_value is used to determine what रेजिस्टर the bit is in, the
 *  current value is पढ़ो, the new bit is OR'd in and the new value is
 *  written back पूर्णांकo the रेजिस्टर.
 **/
व्योम igb_mta_set(काष्ठा e1000_hw *hw, u32 hash_value)
अणु
	u32 hash_bit, hash_reg, mta;

	/* The MTA is a रेजिस्टर array of 32-bit रेजिस्टरs. It is
	 * treated like an array of (32*mta_reg_count) bits.  We want to
	 * set bit BitArray[hash_value]. So we figure out what रेजिस्टर
	 * the bit is in, पढ़ो it, OR in the new bit, then ग_लिखो
	 * back the new value.  The (hw->mac.mta_reg_count - 1) serves as a
	 * mask to bits 31:5 of the hash value which gives us the
	 * रेजिस्टर we're modअगरying.  The hash bit within that रेजिस्टर
	 * is determined by the lower 5 bits of the hash value.
	 */
	hash_reg = (hash_value >> 5) & (hw->mac.mta_reg_count - 1);
	hash_bit = hash_value & 0x1F;

	mta = array_rd32(E1000_MTA, hash_reg);

	mta |= BIT(hash_bit);

	array_wr32(E1000_MTA, hash_reg, mta);
	wrfl();
पूर्ण

/**
 *  igb_hash_mc_addr - Generate a multicast hash value
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mc_addr: poपूर्णांकer to a multicast address
 *
 *  Generates a multicast address hash value which is used to determine
 *  the multicast filter table array address and new table value.  See
 *  igb_mta_set()
 **/
अटल u32 igb_hash_mc_addr(काष्ठा e1000_hw *hw, u8 *mc_addr)
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
	 * LSB                 MSB
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
				  (((u16) mc_addr[5]) << bit_shअगरt)));

	वापस hash_value;
पूर्ण

/**
 * igb_i21x_hw_द्विगुनcheck - द्विगुन checks potential HW issue in i21X
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Checks अगर multicast array is wrote correctly
 * If not then reग_लिखोs again to रेजिस्टर
 **/
अटल व्योम igb_i21x_hw_द्विगुनcheck(काष्ठा e1000_hw *hw)
अणु
	bool is_failed;
	पूर्णांक i;

	करो अणु
		is_failed = false;
		क्रम (i = hw->mac.mta_reg_count - 1; i >= 0; i--) अणु
			अगर (array_rd32(E1000_MTA, i) != hw->mac.mta_shaकरोw[i]) अणु
				is_failed = true;
				array_wr32(E1000_MTA, i, hw->mac.mta_shaकरोw[i]);
				wrfl();
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (is_failed);
पूर्ण

/**
 *  igb_update_mc_addr_list - Update Multicast addresses
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mc_addr_list: array of multicast addresses to program
 *  @mc_addr_count: number of multicast addresses to program
 *
 *  Updates entire Multicast Table Array.
 *  The caller must have a packed mc_addr_list of multicast addresses.
 **/
व्योम igb_update_mc_addr_list(काष्ठा e1000_hw *hw,
			     u8 *mc_addr_list, u32 mc_addr_count)
अणु
	u32 hash_value, hash_bit, hash_reg;
	पूर्णांक i;

	/* clear mta_shaकरोw */
	स_रखो(&hw->mac.mta_shaकरोw, 0, माप(hw->mac.mta_shaकरोw));

	/* update mta_shaकरोw from mc_addr_list */
	क्रम (i = 0; (u32) i < mc_addr_count; i++) अणु
		hash_value = igb_hash_mc_addr(hw, mc_addr_list);

		hash_reg = (hash_value >> 5) & (hw->mac.mta_reg_count - 1);
		hash_bit = hash_value & 0x1F;

		hw->mac.mta_shaकरोw[hash_reg] |= BIT(hash_bit);
		mc_addr_list += (ETH_ALEN);
	पूर्ण

	/* replace the entire MTA table */
	क्रम (i = hw->mac.mta_reg_count - 1; i >= 0; i--)
		array_wr32(E1000_MTA, i, hw->mac.mta_shaकरोw[i]);
	wrfl();
	अगर (hw->mac.type == e1000_i210 || hw->mac.type == e1000_i211)
		igb_i21x_hw_द्विगुनcheck(hw);
पूर्ण

/**
 *  igb_clear_hw_cntrs_base - Clear base hardware counters
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Clears the base hardware counters by पढ़ोing the counter रेजिस्टरs.
 **/
व्योम igb_clear_hw_cntrs_base(काष्ठा e1000_hw *hw)
अणु
	rd32(E1000_CRCERRS);
	rd32(E1000_SYMERRS);
	rd32(E1000_MPC);
	rd32(E1000_SCC);
	rd32(E1000_ECOL);
	rd32(E1000_MCC);
	rd32(E1000_LATECOL);
	rd32(E1000_COLC);
	rd32(E1000_DC);
	rd32(E1000_SEC);
	rd32(E1000_RLEC);
	rd32(E1000_XONRXC);
	rd32(E1000_XONTXC);
	rd32(E1000_XOFFRXC);
	rd32(E1000_XOFFTXC);
	rd32(E1000_FCRUC);
	rd32(E1000_GPRC);
	rd32(E1000_BPRC);
	rd32(E1000_MPRC);
	rd32(E1000_GPTC);
	rd32(E1000_GORCL);
	rd32(E1000_GORCH);
	rd32(E1000_GOTCL);
	rd32(E1000_GOTCH);
	rd32(E1000_RNBC);
	rd32(E1000_RUC);
	rd32(E1000_RFC);
	rd32(E1000_ROC);
	rd32(E1000_RJC);
	rd32(E1000_TORL);
	rd32(E1000_TORH);
	rd32(E1000_TOTL);
	rd32(E1000_TOTH);
	rd32(E1000_TPR);
	rd32(E1000_TPT);
	rd32(E1000_MPTC);
	rd32(E1000_BPTC);
पूर्ण

/**
 *  igb_check_क्रम_copper_link - Check क्रम link (Copper)
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Checks to see of the link status of the hardware has changed.  If a
 *  change in link status has been detected, then we पढ़ो the PHY रेजिस्टरs
 *  to get the current speed/duplex अगर link exists.
 **/
s32 igb_check_क्रम_copper_link(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	s32 ret_val;
	bool link;

	/* We only want to go out to the PHY रेजिस्टरs to see अगर Auto-Neg
	 * has completed and/or अगर our link status has changed.  The
	 * get_link_status flag is set upon receiving a Link Status
	 * Change or Rx Sequence Error पूर्णांकerrupt.
	 */
	अगर (!mac->get_link_status) अणु
		ret_val = 0;
		जाओ out;
	पूर्ण

	/* First we want to see अगर the MII Status Register reports
	 * link.  If so, then we want to get the current speed/duplex
	 * of the PHY.
	 */
	ret_val = igb_phy_has_link(hw, 1, 0, &link);
	अगर (ret_val)
		जाओ out;

	अगर (!link)
		जाओ out; /* No link detected */

	mac->get_link_status = false;

	/* Check अगर there was DownShअगरt, must be checked
	 * immediately after link-up
	 */
	igb_check_करोwnshअगरt(hw);

	/* If we are क्रमcing speed/duplex, then we simply वापस since
	 * we have alपढ़ोy determined whether we have link or not.
	 */
	अगर (!mac->स्वतःneg) अणु
		ret_val = -E1000_ERR_CONFIG;
		जाओ out;
	पूर्ण

	/* Auto-Neg is enabled.  Auto Speed Detection takes care
	 * of MAC speed/duplex configuration.  So we only need to
	 * configure Collision Distance in the MAC.
	 */
	igb_config_collision_dist(hw);

	/* Configure Flow Control now that Auto-Neg has completed.
	 * First, we need to restore the desired flow control
	 * settings because we may have had to re-स्वतःneg with a
	 * dअगरferent link partner.
	 */
	ret_val = igb_config_fc_after_link_up(hw);
	अगर (ret_val)
		hw_dbg("Error configuring flow control\n");

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_setup_link - Setup flow control and link settings
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Determines which flow control settings to use, then configures flow
 *  control.  Calls the appropriate media-specअगरic link configuration
 *  function.  Assuming the adapter has a valid link partner, a valid link
 *  should be established.  Assumes the hardware has previously been reset
 *  and the transmitter and receiver are not enabled.
 **/
s32 igb_setup_link(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;

	/* In the हाल of the phy reset being blocked, we alपढ़ोy have a link.
	 * We करो not need to set it up again.
	 */
	अगर (igb_check_reset_block(hw))
		जाओ out;

	/* If requested flow control is set to शेष, set flow control
	 * based on the EEPROM flow control settings.
	 */
	अगर (hw->fc.requested_mode == e1000_fc_शेष) अणु
		ret_val = igb_set_शेष_fc(hw);
		अगर (ret_val)
			जाओ out;
	पूर्ण

	/* We want to save off the original Flow Control configuration just
	 * in हाल we get disconnected and then reconnected पूर्णांकo a dअगरferent
	 * hub or चयन with dअगरferent Flow Control capabilities.
	 */
	hw->fc.current_mode = hw->fc.requested_mode;

	hw_dbg("After fix-ups FlowControl is now = %x\n", hw->fc.current_mode);

	/* Call the necessary media_type subroutine to configure the link. */
	ret_val = hw->mac.ops.setup_physical_पूर्णांकerface(hw);
	अगर (ret_val)
		जाओ out;

	/* Initialize the flow control address, type, and PAUSE समयr
	 * रेजिस्टरs to their शेष values.  This is करोne even अगर flow
	 * control is disabled, because it करोes not hurt anything to
	 * initialize these रेजिस्टरs.
	 */
	hw_dbg("Initializing the Flow Control address, type and timer regs\n");
	wr32(E1000_FCT, FLOW_CONTROL_TYPE);
	wr32(E1000_FCAH, FLOW_CONTROL_ADDRESS_HIGH);
	wr32(E1000_FCAL, FLOW_CONTROL_ADDRESS_LOW);

	wr32(E1000_FCTTV, hw->fc.छोड़ो_समय);

	igb_set_fc_watermarks(hw);

out:

	वापस ret_val;
पूर्ण

/**
 *  igb_config_collision_dist - Configure collision distance
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Configures the collision distance to the शेष value and is used
 *  during link setup. Currently no func poपूर्णांकer exists and all
 *  implementations are handled in the generic version of this function.
 **/
व्योम igb_config_collision_dist(काष्ठा e1000_hw *hw)
अणु
	u32 tctl;

	tctl = rd32(E1000_TCTL);

	tctl &= ~E1000_TCTL_COLD;
	tctl |= E1000_COLLISION_DISTANCE << E1000_COLD_SHIFT;

	wr32(E1000_TCTL, tctl);
	wrfl();
पूर्ण

/**
 *  igb_set_fc_watermarks - Set flow control high/low watermarks
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Sets the flow control high/low threshold (watermark) रेजिस्टरs.  If
 *  flow control XON frame transmission is enabled, then set XON frame
 *  tansmission as well.
 **/
अटल व्योम igb_set_fc_watermarks(काष्ठा e1000_hw *hw)
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
	wr32(E1000_FCRTL, fcrtl);
	wr32(E1000_FCRTH, fcrth);
पूर्ण

/**
 *  igb_set_शेष_fc - Set flow control शेष values
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Read the EEPROM क्रम the शेष values क्रम flow control and store the
 *  values.
 **/
अटल s32 igb_set_शेष_fc(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	u16 lan_offset;
	u16 nvm_data;

	/* Read and store word 0x0F of the EEPROM. This word contains bits
	 * that determine the hardware's शेष PAUSE (flow control) mode,
	 * a bit that determines whether the HW शेषs to enabling or
	 * disabling स्वतः-negotiation, and the direction of the
	 * SW defined pins. If there is no SW over-ride of the flow
	 * control setting, then the variable hw->fc will
	 * be initialized based on a value in the EEPROM.
	 */
	अगर (hw->mac.type == e1000_i350)
		lan_offset = NVM_82580_LAN_FUNC_OFFSET(hw->bus.func);
	अन्यथा
		lan_offset = 0;

	ret_val = hw->nvm.ops.पढ़ो(hw, NVM_INIT_CONTROL2_REG + lan_offset,
				   1, &nvm_data);
	अगर (ret_val) अणु
		hw_dbg("NVM Read Error\n");
		जाओ out;
	पूर्ण

	अगर ((nvm_data & NVM_WORD0F_PAUSE_MASK) == 0)
		hw->fc.requested_mode = e1000_fc_none;
	अन्यथा अगर ((nvm_data & NVM_WORD0F_PAUSE_MASK) == NVM_WORD0F_ASM_सूची)
		hw->fc.requested_mode = e1000_fc_tx_छोड़ो;
	अन्यथा
		hw->fc.requested_mode = e1000_fc_full;

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_क्रमce_mac_fc - Force the MAC's flow control settings
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Force the MAC's flow control settings.  Sets the TFCE and RFCE bits in the
 *  device control रेजिस्टर to reflect the adapter settings.  TFCE and RFCE
 *  need to be explicitly set by software when a copper PHY is used because
 *  स्वतःnegotiation is managed by the PHY rather than the MAC.  Software must
 *  also configure these bits when link is क्रमced on a fiber connection.
 **/
s32 igb_क्रमce_mac_fc(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	s32 ret_val = 0;

	ctrl = rd32(E1000_CTRL);

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
	 *      3:  Both Rx and TX flow control (symmetric) is enabled.
	 *  other:  No other values should be possible at this poपूर्णांक.
	 */
	hw_dbg("hw->fc.current_mode = %u\n", hw->fc.current_mode);

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
		hw_dbg("Flow control param set incorrectly\n");
		ret_val = -E1000_ERR_CONFIG;
		जाओ out;
	पूर्ण

	wr32(E1000_CTRL, ctrl);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_config_fc_after_link_up - Configures flow control after link
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Checks the status of स्वतः-negotiation after link up to ensure that the
 *  speed and duplex were not क्रमced.  If the link needed to be क्रमced, then
 *  flow control needs to be क्रमced also.  If स्वतः-negotiation is enabled
 *  and did not fail, then we configure flow control based on our link
 *  partner.
 **/
s32 igb_config_fc_after_link_up(काष्ठा e1000_hw *hw)
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
		अगर (hw->phy.media_type == e1000_media_type_पूर्णांकernal_serdes)
			ret_val = igb_क्रमce_mac_fc(hw);
	पूर्ण अन्यथा अणु
		अगर (hw->phy.media_type == e1000_media_type_copper)
			ret_val = igb_क्रमce_mac_fc(hw);
	पूर्ण

	अगर (ret_val) अणु
		hw_dbg("Error forcing flow control settings\n");
		जाओ out;
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
		ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_STATUS,
						   &mii_status_reg);
		अगर (ret_val)
			जाओ out;
		ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_STATUS,
						   &mii_status_reg);
		अगर (ret_val)
			जाओ out;

		अगर (!(mii_status_reg & MII_SR_AUTONEG_COMPLETE)) अणु
			hw_dbg("Copper PHY and Auto Neg has not completed.\n");
			जाओ out;
		पूर्ण

		/* The AutoNeg process has completed, so we now need to
		 * पढ़ो both the Auto Negotiation Advertisement
		 * Register (Address 4) and the Auto_Negotiation Base
		 * Page Ability Register (Address 5) to determine how
		 * flow control was negotiated.
		 */
		ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_AUTONEG_ADV,
					    &mii_nway_adv_reg);
		अगर (ret_val)
			जाओ out;
		ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_LP_ABILITY,
					    &mii_nway_lp_ability_reg);
		अगर (ret_val)
			जाओ out;

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
		अगर ((mii_nway_adv_reg & NWAY_AR_PAUSE) &&
		    (mii_nway_lp_ability_reg & NWAY_LPAR_PAUSE)) अणु
			/* Now we need to check अगर the user selected RX ONLY
			 * of छोड़ो frames.  In this हाल, we had to advertise
			 * FULL flow control because we could not advertise RX
			 * ONLY. Hence, we must now check to see अगर we need to
			 * turn OFF  the TRANSMISSION of PAUSE frames.
			 */
			अगर (hw->fc.requested_mode == e1000_fc_full) अणु
				hw->fc.current_mode = e1000_fc_full;
				hw_dbg("Flow Control = FULL.\n");
			पूर्ण अन्यथा अणु
				hw->fc.current_mode = e1000_fc_rx_छोड़ो;
				hw_dbg("Flow Control = RX PAUSE frames only.\n");
			पूर्ण
		पूर्ण
		/* For receiving PAUSE frames ONLY.
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | Result
		 *-------|---------|-------|---------|--------------------
		 *   0   |    1    |   1   |    1    | e1000_fc_tx_छोड़ो
		 */
		अन्यथा अगर (!(mii_nway_adv_reg & NWAY_AR_PAUSE) &&
			  (mii_nway_adv_reg & NWAY_AR_ASM_सूची) &&
			  (mii_nway_lp_ability_reg & NWAY_LPAR_PAUSE) &&
			  (mii_nway_lp_ability_reg & NWAY_LPAR_ASM_सूची)) अणु
			hw->fc.current_mode = e1000_fc_tx_छोड़ो;
			hw_dbg("Flow Control = TX PAUSE frames only.\n");
		पूर्ण
		/* For transmitting PAUSE frames ONLY.
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | Result
		 *-------|---------|-------|---------|--------------------
		 *   1   |    1    |   0   |    1    | e1000_fc_rx_छोड़ो
		 */
		अन्यथा अगर ((mii_nway_adv_reg & NWAY_AR_PAUSE) &&
			 (mii_nway_adv_reg & NWAY_AR_ASM_सूची) &&
			 !(mii_nway_lp_ability_reg & NWAY_LPAR_PAUSE) &&
			 (mii_nway_lp_ability_reg & NWAY_LPAR_ASM_सूची)) अणु
			hw->fc.current_mode = e1000_fc_rx_छोड़ो;
			hw_dbg("Flow Control = RX PAUSE frames only.\n");
		पूर्ण
		/* Per the IEEE spec, at this poपूर्णांक flow control should be
		 * disabled.  However, we want to consider that we could
		 * be connected to a legacy चयन that करोesn't advertise
		 * desired flow control, but can be क्रमced on the link
		 * partner.  So अगर we advertised no flow control, that is
		 * what we will resolve to.  If we advertised some kind of
		 * receive capability (Rx Pause Only or Full Flow Control)
		 * and the link partner advertised none, we will configure
		 * ourselves to enable Rx Flow Control only.  We can करो
		 * this safely क्रम two reasons:  If the link partner really
		 * didn't want flow control enabled, and we enable Rx, no
		 * harm करोne since we won't be receiving any PAUSE frames
		 * anyway.  If the पूर्णांकent on the link partner was to have
		 * flow control enabled, then by us enabling RX only, we
		 * can at least receive छोड़ो frames and process them.
		 * This is a good idea because in most हालs, since we are
		 * preकरोminantly a server NIC, more बार than not we will
		 * be asked to delay transmission of packets than asking
		 * our link partner to छोड़ो transmission of frames.
		 */
		अन्यथा अगर ((hw->fc.requested_mode == e1000_fc_none) ||
			 (hw->fc.requested_mode == e1000_fc_tx_छोड़ो) ||
			 (hw->fc.strict_ieee)) अणु
			hw->fc.current_mode = e1000_fc_none;
			hw_dbg("Flow Control = NONE.\n");
		पूर्ण अन्यथा अणु
			hw->fc.current_mode = e1000_fc_rx_छोड़ो;
			hw_dbg("Flow Control = RX PAUSE frames only.\n");
		पूर्ण

		/* Now we need to करो one last check...  If we स्वतः-
		 * negotiated to HALF DUPLEX, flow control should not be
		 * enabled per IEEE 802.3 spec.
		 */
		ret_val = hw->mac.ops.get_speed_and_duplex(hw, &speed, &duplex);
		अगर (ret_val) अणु
			hw_dbg("Error getting link speed and duplex\n");
			जाओ out;
		पूर्ण

		अगर (duplex == HALF_DUPLEX)
			hw->fc.current_mode = e1000_fc_none;

		/* Now we call a subroutine to actually क्रमce the MAC
		 * controller to use the correct flow control settings.
		 */
		ret_val = igb_क्रमce_mac_fc(hw);
		अगर (ret_val) अणु
			hw_dbg("Error forcing flow control settings\n");
			जाओ out;
		पूर्ण
	पूर्ण
	/* Check क्रम the हाल where we have SerDes media and स्वतः-neg is
	 * enabled.  In this हाल, we need to check and see अगर Auto-Neg
	 * has completed, and अगर so, how the PHY and link partner has
	 * flow control configured.
	 */
	अगर ((hw->phy.media_type == e1000_media_type_पूर्णांकernal_serdes)
		&& mac->स्वतःneg) अणु
		/* Read the PCS_LSTS and check to see अगर AutoNeg
		 * has completed.
		 */
		pcs_status_reg = rd32(E1000_PCS_LSTAT);

		अगर (!(pcs_status_reg & E1000_PCS_LSTS_AN_COMPLETE)) अणु
			hw_dbg("PCS Auto Neg has not completed.\n");
			वापस ret_val;
		पूर्ण

		/* The AutoNeg process has completed, so we now need to
		 * पढ़ो both the Auto Negotiation Advertisement
		 * Register (PCS_ANADV) and the Auto_Negotiation Base
		 * Page Ability Register (PCS_LPAB) to determine how
		 * flow control was negotiated.
		 */
		pcs_adv_reg = rd32(E1000_PCS_ANADV);
		pcs_lp_ability_reg = rd32(E1000_PCS_LPAB);

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
				hw_dbg("Flow Control = FULL.\n");
			पूर्ण अन्यथा अणु
				hw->fc.current_mode = e1000_fc_rx_छोड़ो;
				hw_dbg("Flow Control = Rx PAUSE frames only.\n");
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
			hw_dbg("Flow Control = Tx PAUSE frames only.\n");
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
			hw_dbg("Flow Control = Rx PAUSE frames only.\n");
		पूर्ण अन्यथा अणु
			/* Per the IEEE spec, at this poपूर्णांक flow control
			 * should be disabled.
			 */
			hw->fc.current_mode = e1000_fc_none;
			hw_dbg("Flow Control = NONE.\n");
		पूर्ण

		/* Now we call a subroutine to actually क्रमce the MAC
		 * controller to use the correct flow control settings.
		 */
		pcs_ctrl_reg = rd32(E1000_PCS_LCTL);
		pcs_ctrl_reg |= E1000_PCS_LCTL_FORCE_FCTRL;
		wr32(E1000_PCS_LCTL, pcs_ctrl_reg);

		ret_val = igb_क्रमce_mac_fc(hw);
		अगर (ret_val) अणु
			hw_dbg("Error forcing flow control settings\n");
			वापस ret_val;
		पूर्ण
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_get_speed_and_duplex_copper - Retrieve current speed/duplex
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @speed: stores the current speed
 *  @duplex: stores the current duplex
 *
 *  Read the status रेजिस्टर क्रम the current speed/duplex and store the current
 *  speed and duplex क्रम copper connections.
 **/
s32 igb_get_speed_and_duplex_copper(काष्ठा e1000_hw *hw, u16 *speed,
				      u16 *duplex)
अणु
	u32 status;

	status = rd32(E1000_STATUS);
	अगर (status & E1000_STATUS_SPEED_1000) अणु
		*speed = SPEED_1000;
		hw_dbg("1000 Mbs, ");
	पूर्ण अन्यथा अगर (status & E1000_STATUS_SPEED_100) अणु
		*speed = SPEED_100;
		hw_dbg("100 Mbs, ");
	पूर्ण अन्यथा अणु
		*speed = SPEED_10;
		hw_dbg("10 Mbs, ");
	पूर्ण

	अगर (status & E1000_STATUS_FD) अणु
		*duplex = FULL_DUPLEX;
		hw_dbg("Full Duplex\n");
	पूर्ण अन्यथा अणु
		*duplex = HALF_DUPLEX;
		hw_dbg("Half Duplex\n");
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  igb_get_hw_semaphore - Acquire hardware semaphore
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Acquire the HW semaphore to access the PHY or NVM
 **/
s32 igb_get_hw_semaphore(काष्ठा e1000_hw *hw)
अणु
	u32 swsm;
	s32 ret_val = 0;
	s32 समयout = hw->nvm.word_size + 1;
	s32 i = 0;

	/* Get the SW semaphore */
	जबतक (i < समयout) अणु
		swsm = rd32(E1000_SWSM);
		अगर (!(swsm & E1000_SWSM_SMBI))
			अवरोध;

		udelay(50);
		i++;
	पूर्ण

	अगर (i == समयout) अणु
		hw_dbg("Driver can't access device - SMBI bit is set.\n");
		ret_val = -E1000_ERR_NVM;
		जाओ out;
	पूर्ण

	/* Get the FW semaphore. */
	क्रम (i = 0; i < समयout; i++) अणु
		swsm = rd32(E1000_SWSM);
		wr32(E1000_SWSM, swsm | E1000_SWSM_SWESMBI);

		/* Semaphore acquired अगर bit latched */
		अगर (rd32(E1000_SWSM) & E1000_SWSM_SWESMBI)
			अवरोध;

		udelay(50);
	पूर्ण

	अगर (i == समयout) अणु
		/* Release semaphores */
		igb_put_hw_semaphore(hw);
		hw_dbg("Driver can't access the NVM\n");
		ret_val = -E1000_ERR_NVM;
		जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_put_hw_semaphore - Release hardware semaphore
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Release hardware semaphore used to access the PHY or NVM
 **/
व्योम igb_put_hw_semaphore(काष्ठा e1000_hw *hw)
अणु
	u32 swsm;

	swsm = rd32(E1000_SWSM);

	swsm &= ~(E1000_SWSM_SMBI | E1000_SWSM_SWESMBI);

	wr32(E1000_SWSM, swsm);
पूर्ण

/**
 *  igb_get_स्वतः_rd_करोne - Check क्रम स्वतः पढ़ो completion
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Check EEPROM क्रम Auto Read करोne bit.
 **/
s32 igb_get_स्वतः_rd_करोne(काष्ठा e1000_hw *hw)
अणु
	s32 i = 0;
	s32 ret_val = 0;


	जबतक (i < AUTO_READ_DONE_TIMEOUT) अणु
		अगर (rd32(E1000_EECD) & E1000_EECD_AUTO_RD)
			अवरोध;
		usleep_range(1000, 2000);
		i++;
	पूर्ण

	अगर (i == AUTO_READ_DONE_TIMEOUT) अणु
		hw_dbg("Auto read by HW from NVM has not completed.\n");
		ret_val = -E1000_ERR_RESET;
		जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_valid_led_शेष - Verअगरy a valid शेष LED config
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @data: poपूर्णांकer to the NVM (EEPROM)
 *
 *  Read the EEPROM क्रम the current शेष LED configuration.  If the
 *  LED configuration is not valid, set to a valid LED configuration.
 **/
अटल s32 igb_valid_led_शेष(काष्ठा e1000_hw *hw, u16 *data)
अणु
	s32 ret_val;

	ret_val = hw->nvm.ops.पढ़ो(hw, NVM_ID_LED_SETTINGS, 1, data);
	अगर (ret_val) अणु
		hw_dbg("NVM Read Error\n");
		जाओ out;
	पूर्ण

	अगर (*data == ID_LED_RESERVED_0000 || *data == ID_LED_RESERVED_FFFF) अणु
		चयन (hw->phy.media_type) अणु
		हाल e1000_media_type_पूर्णांकernal_serdes:
			*data = ID_LED_DEFAULT_82575_SERDES;
			अवरोध;
		हाल e1000_media_type_copper:
		शेष:
			*data = ID_LED_DEFAULT;
			अवरोध;
		पूर्ण
	पूर्ण
out:
	वापस ret_val;
पूर्ण

/**
 *  igb_id_led_init -
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 **/
s32 igb_id_led_init(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	s32 ret_val;
	स्थिर u32 ledctl_mask = 0x000000FF;
	स्थिर u32 ledctl_on = E1000_LEDCTL_MODE_LED_ON;
	स्थिर u32 ledctl_off = E1000_LEDCTL_MODE_LED_OFF;
	u16 data, i, temp;
	स्थिर u16 led_mask = 0x0F;

	/* i210 and i211 devices have dअगरferent LED mechanism */
	अगर ((hw->mac.type == e1000_i210) ||
	    (hw->mac.type == e1000_i211))
		ret_val = igb_valid_led_शेष_i210(hw, &data);
	अन्यथा
		ret_val = igb_valid_led_शेष(hw, &data);

	अगर (ret_val)
		जाओ out;

	mac->ledctl_शेष = rd32(E1000_LEDCTL);
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

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_cleanup_led - Set LED config to शेष operation
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Remove the current LED configuration and set the LED configuration
 *  to the शेष value, saved from the EEPROM.
 **/
s32 igb_cleanup_led(काष्ठा e1000_hw *hw)
अणु
	wr32(E1000_LEDCTL, hw->mac.ledctl_शेष);
	वापस 0;
पूर्ण

/**
 *  igb_blink_led - Blink LED
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Blink the led's which are set to be on.
 **/
s32 igb_blink_led(काष्ठा e1000_hw *hw)
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

	wr32(E1000_LEDCTL, ledctl_blink);

	वापस 0;
पूर्ण

/**
 *  igb_led_off - Turn LED off
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Turn LED off.
 **/
s32 igb_led_off(काष्ठा e1000_hw *hw)
अणु
	चयन (hw->phy.media_type) अणु
	हाल e1000_media_type_copper:
		wr32(E1000_LEDCTL, hw->mac.ledctl_mode1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  igb_disable_pcie_master - Disables PCI-express master access
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Returns 0 (0) अगर successful, अन्यथा वापसs -10
 *  (-E1000_ERR_MASTER_REQUESTS_PENDING) अगर master disable bit has not caused
 *  the master requests to be disabled.
 *
 *  Disables PCI-Express master access and verअगरies there are no pending
 *  requests.
 **/
s32 igb_disable_pcie_master(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	s32 समयout = MASTER_DISABLE_TIMEOUT;
	s32 ret_val = 0;

	अगर (hw->bus.type != e1000_bus_type_pci_express)
		जाओ out;

	ctrl = rd32(E1000_CTRL);
	ctrl |= E1000_CTRL_GIO_MASTER_DISABLE;
	wr32(E1000_CTRL, ctrl);

	जबतक (समयout) अणु
		अगर (!(rd32(E1000_STATUS) &
		      E1000_STATUS_GIO_MASTER_ENABLE))
			अवरोध;
		udelay(100);
		समयout--;
	पूर्ण

	अगर (!समयout) अणु
		hw_dbg("Master requests are pending.\n");
		ret_val = -E1000_ERR_MASTER_REQUESTS_PENDING;
		जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_validate_mdi_setting - Verअगरy MDI/MDIx settings
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Verअगरy that when not using स्वतः-negotitation that MDI/MDIx is correctly
 *  set, which is क्रमced to MDI mode only.
 **/
s32 igb_validate_mdi_setting(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;

	/* All MDI settings are supported on 82580 and newer. */
	अगर (hw->mac.type >= e1000_82580)
		जाओ out;

	अगर (!hw->mac.स्वतःneg && (hw->phy.mdix == 0 || hw->phy.mdix == 3)) अणु
		hw_dbg("Invalid MDI setting detected\n");
		hw->phy.mdix = 1;
		ret_val = -E1000_ERR_CONFIG;
		जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_ग_लिखो_8bit_ctrl_reg - Write a 8bit CTRL रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @reg: 32bit रेजिस्टर offset such as E1000_SCTL
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *
 *  Writes an address/data control type रेजिस्टर.  There are several of these
 *  and they all have the क्रमmat address << 8 | data and bit 31 is polled क्रम
 *  completion.
 **/
s32 igb_ग_लिखो_8bit_ctrl_reg(काष्ठा e1000_hw *hw, u32 reg,
			      u32 offset, u8 data)
अणु
	u32 i, regvalue = 0;
	s32 ret_val = 0;

	/* Set up the address and data */
	regvalue = ((u32)data) | (offset << E1000_GEN_CTL_ADDRESS_SHIFT);
	wr32(reg, regvalue);

	/* Poll the पढ़ोy bit to see अगर the MDI पढ़ो completed */
	क्रम (i = 0; i < E1000_GEN_POLL_TIMEOUT; i++) अणु
		udelay(5);
		regvalue = rd32(reg);
		अगर (regvalue & E1000_GEN_CTL_READY)
			अवरोध;
	पूर्ण
	अगर (!(regvalue & E1000_GEN_CTL_READY)) अणु
		hw_dbg("Reg %08x did not indicate ready\n", reg);
		ret_val = -E1000_ERR_PHY;
		जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_enable_mng_pass_thru - Enable processing of ARP's
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Verअगरies the hardware needs to leave पूर्णांकerface enabled so that frames can
 *  be directed to and from the management पूर्णांकerface.
 **/
bool igb_enable_mng_pass_thru(काष्ठा e1000_hw *hw)
अणु
	u32 manc;
	u32 fwsm, factps;
	bool ret_val = false;

	अगर (!hw->mac.asf_firmware_present)
		जाओ out;

	manc = rd32(E1000_MANC);

	अगर (!(manc & E1000_MANC_RCV_TCO_EN))
		जाओ out;

	अगर (hw->mac.arc_subप्रणाली_valid) अणु
		fwsm = rd32(E1000_FWSM);
		factps = rd32(E1000_FACTPS);

		अगर (!(factps & E1000_FACTPS_MNGCG) &&
		    ((fwsm & E1000_FWSM_MODE_MASK) ==
		     (e1000_mng_mode_pt << E1000_FWSM_MODE_SHIFT))) अणु
			ret_val = true;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((manc & E1000_MANC_SMBUS_EN) &&
		    !(manc & E1000_MANC_ASF_EN)) अणु
			ret_val = true;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस ret_val;
पूर्ण
