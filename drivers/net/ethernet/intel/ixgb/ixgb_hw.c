<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2008 Intel Corporation. */

/* ixgb_hw.c
 * Shared functions क्रम accessing and configuring the adapter
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/pci_ids.h>
#समावेश "ixgb_hw.h"
#समावेश "ixgb_ids.h"

#समावेश <linux/etherdevice.h>

/*  Local function prototypes */

अटल u32 ixgb_hash_mc_addr(काष्ठा ixgb_hw *hw, u8 * mc_addr);

अटल व्योम ixgb_mta_set(काष्ठा ixgb_hw *hw, u32 hash_value);

अटल व्योम ixgb_get_bus_info(काष्ठा ixgb_hw *hw);

अटल bool ixgb_link_reset(काष्ठा ixgb_hw *hw);

अटल व्योम ixgb_optics_reset(काष्ठा ixgb_hw *hw);

अटल व्योम ixgb_optics_reset_bcm(काष्ठा ixgb_hw *hw);

अटल ixgb_phy_type ixgb_identअगरy_phy(काष्ठा ixgb_hw *hw);

अटल व्योम ixgb_clear_hw_cntrs(काष्ठा ixgb_hw *hw);

अटल व्योम ixgb_clear_vfta(काष्ठा ixgb_hw *hw);

अटल व्योम ixgb_init_rx_addrs(काष्ठा ixgb_hw *hw);

अटल u16 ixgb_पढ़ो_phy_reg(काष्ठा ixgb_hw *hw,
				  u32 reg_address,
				  u32 phy_address,
				  u32 device_type);

अटल bool ixgb_setup_fc(काष्ठा ixgb_hw *hw);

अटल bool mac_addr_valid(u8 *mac_addr);

अटल u32 ixgb_mac_reset(काष्ठा ixgb_hw *hw)
अणु
	u32 ctrl_reg;

	ctrl_reg =  IXGB_CTRL0_RST |
				IXGB_CTRL0_SDP3_सूची |   /* All pins are Output=1 */
				IXGB_CTRL0_SDP2_सूची |
				IXGB_CTRL0_SDP1_सूची |
				IXGB_CTRL0_SDP0_सूची |
				IXGB_CTRL0_SDP3	 |   /* Initial value 1101   */
				IXGB_CTRL0_SDP2	 |
				IXGB_CTRL0_SDP0;

#अगर_घोषित HP_ZX1
	/* Workaround क्रम 82597EX reset errata */
	IXGB_WRITE_REG_IO(hw, CTRL0, ctrl_reg);
#अन्यथा
	IXGB_WRITE_REG(hw, CTRL0, ctrl_reg);
#पूर्ण_अगर

	/* Delay a few ms just to allow the reset to complete */
	msleep(IXGB_DELAY_AFTER_RESET);
	ctrl_reg = IXGB_READ_REG(hw, CTRL0);
#अगर_घोषित DBG
	/* Make sure the self-clearing global reset bit did self clear */
	ASSERT(!(ctrl_reg & IXGB_CTRL0_RST));
#पूर्ण_अगर

	अगर (hw->subप्रणाली_venकरोr_id == PCI_VENDOR_ID_SUN) अणु
		ctrl_reg =  /* Enable पूर्णांकerrupt from XFP and SerDes */
			   IXGB_CTRL1_GPI0_EN |
			   IXGB_CTRL1_SDP6_सूची |
			   IXGB_CTRL1_SDP7_सूची |
			   IXGB_CTRL1_SDP6 |
			   IXGB_CTRL1_SDP7;
		IXGB_WRITE_REG(hw, CTRL1, ctrl_reg);
		ixgb_optics_reset_bcm(hw);
	पूर्ण

	अगर (hw->phy_type == ixgb_phy_type_txn17401)
		ixgb_optics_reset(hw);

	वापस ctrl_reg;
पूर्ण

/******************************************************************************
 * Reset the transmit and receive units; mask and clear all पूर्णांकerrupts.
 *
 * hw - Struct containing variables accessed by shared code
 *****************************************************************************/
bool
ixgb_adapter_stop(काष्ठा ixgb_hw *hw)
अणु
	u32 ctrl_reg;

	ENTER();

	/* If we are stopped or resetting निकास gracefully and रुको to be
	 * started again beक्रमe accessing the hardware.
	 */
	अगर (hw->adapter_stopped) अणु
		pr_debug("Exiting because the adapter is already stopped!!!\n");
		वापस false;
	पूर्ण

	/* Set the Adapter Stopped flag so other driver functions stop
	 * touching the Hardware.
	 */
	hw->adapter_stopped = true;

	/* Clear पूर्णांकerrupt mask to stop board from generating पूर्णांकerrupts */
	pr_debug("Masking off all interrupts\n");
	IXGB_WRITE_REG(hw, IMC, 0xFFFFFFFF);

	/* Disable the Transmit and Receive units.  Then delay to allow
	 * any pending transactions to complete beक्रमe we hit the MAC with
	 * the global reset.
	 */
	IXGB_WRITE_REG(hw, RCTL, IXGB_READ_REG(hw, RCTL) & ~IXGB_RCTL_RXEN);
	IXGB_WRITE_REG(hw, TCTL, IXGB_READ_REG(hw, TCTL) & ~IXGB_TCTL_TXEN);
	IXGB_WRITE_FLUSH(hw);
	msleep(IXGB_DELAY_BEFORE_RESET);

	/* Issue a global reset to the MAC.  This will reset the chip's
	 * transmit, receive, DMA, and link units.  It will not effect
	 * the current PCI configuration.  The global reset bit is self-
	 * clearing, and should clear within a microsecond.
	 */
	pr_debug("Issuing a global reset to MAC\n");

	ctrl_reg = ixgb_mac_reset(hw);

	/* Clear पूर्णांकerrupt mask to stop board from generating पूर्णांकerrupts */
	pr_debug("Masking off all interrupts\n");
	IXGB_WRITE_REG(hw, IMC, 0xffffffff);

	/* Clear any pending पूर्णांकerrupt events. */
	IXGB_READ_REG(hw, ICR);

	वापस ctrl_reg & IXGB_CTRL0_RST;
पूर्ण


/******************************************************************************
 * Identअगरies the venकरोr of the optics module on the adapter.  The SR adapters
 * support two dअगरferent types of XPAK optics, so it is necessary to determine
 * which optics are present beक्रमe applying any optics-specअगरic workarounds.
 *
 * hw - Struct containing variables accessed by shared code.
 *
 * Returns: the venकरोr of the XPAK optics module.
 *****************************************************************************/
अटल ixgb_xpak_venकरोr
ixgb_identअगरy_xpak_venकरोr(काष्ठा ixgb_hw *hw)
अणु
	u32 i;
	u16 venकरोr_name[5];
	ixgb_xpak_venकरोr xpak_venकरोr;

	ENTER();

	/* Read the first few bytes of the venकरोr string from the XPAK NVR
	 * रेजिस्टरs.  These are standard XENPAK/XPAK रेजिस्टरs, so all XPAK
	 * devices should implement them. */
	क्रम (i = 0; i < 5; i++) अणु
		venकरोr_name[i] = ixgb_पढ़ो_phy_reg(hw,
						   MDIO_PMA_PMD_XPAK_VENDOR_NAME
						   + i, IXGB_PHY_ADDRESS,
						   MDIO_MMD_PMAPMD);
	पूर्ण

	/* Determine the actual venकरोr */
	अगर (venकरोr_name[0] == 'I' &&
	    venकरोr_name[1] == 'N' &&
	    venकरोr_name[2] == 'T' &&
	    venकरोr_name[3] == 'E' && vendor_name[4] == 'L') अणु
		xpak_venकरोr = ixgb_xpak_venकरोr_पूर्णांकel;
	पूर्ण अन्यथा अणु
		xpak_venकरोr = ixgb_xpak_venकरोr_infineon;
	पूर्ण

	वापस xpak_venकरोr;
पूर्ण

/******************************************************************************
 * Determine the physical layer module on the adapter.
 *
 * hw - Struct containing variables accessed by shared code.  The device_id
 *      field must be (correctly) populated beक्रमe calling this routine.
 *
 * Returns: the phy type of the adapter.
 *****************************************************************************/
अटल ixgb_phy_type
ixgb_identअगरy_phy(काष्ठा ixgb_hw *hw)
अणु
	ixgb_phy_type phy_type;
	ixgb_xpak_venकरोr xpak_venकरोr;

	ENTER();

	/* Infer the transceiver/phy type from the device id */
	चयन (hw->device_id) अणु
	हाल IXGB_DEVICE_ID_82597EX:
		pr_debug("Identified TXN17401 optics\n");
		phy_type = ixgb_phy_type_txn17401;
		अवरोध;

	हाल IXGB_DEVICE_ID_82597EX_SR:
		/* The SR adapters carry two dअगरferent types of XPAK optics
		 * modules; पढ़ो the venकरोr identअगरier to determine the exact
		 * type of optics. */
		xpak_venकरोr = ixgb_identअगरy_xpak_venकरोr(hw);
		अगर (xpak_venकरोr == ixgb_xpak_venकरोr_पूर्णांकel) अणु
			pr_debug("Identified TXN17201 optics\n");
			phy_type = ixgb_phy_type_txn17201;
		पूर्ण अन्यथा अणु
			pr_debug("Identified G6005 optics\n");
			phy_type = ixgb_phy_type_g6005;
		पूर्ण
		अवरोध;
	हाल IXGB_DEVICE_ID_82597EX_LR:
		pr_debug("Identified G6104 optics\n");
		phy_type = ixgb_phy_type_g6104;
		अवरोध;
	हाल IXGB_DEVICE_ID_82597EX_CX4:
		pr_debug("Identified CX4\n");
		xpak_venकरोr = ixgb_identअगरy_xpak_venकरोr(hw);
		अगर (xpak_venकरोr == ixgb_xpak_venकरोr_पूर्णांकel) अणु
			pr_debug("Identified TXN17201 optics\n");
			phy_type = ixgb_phy_type_txn17201;
		पूर्ण अन्यथा अणु
			pr_debug("Identified G6005 optics\n");
			phy_type = ixgb_phy_type_g6005;
		पूर्ण
		अवरोध;
	शेष:
		pr_debug("Unknown physical layer module\n");
		phy_type = ixgb_phy_type_unknown;
		अवरोध;
	पूर्ण

	/* update phy type क्रम sun specअगरic board */
	अगर (hw->subप्रणाली_venकरोr_id == PCI_VENDOR_ID_SUN)
		phy_type = ixgb_phy_type_bcm;

	वापस phy_type;
पूर्ण

/******************************************************************************
 * Perक्रमms basic configuration of the adapter.
 *
 * hw - Struct containing variables accessed by shared code
 *
 * Resets the controller.
 * Reads and validates the EEPROM.
 * Initializes the receive address रेजिस्टरs.
 * Initializes the multicast table.
 * Clears all on-chip counters.
 * Calls routine to setup flow control settings.
 * Leaves the transmit and receive units disabled and uninitialized.
 *
 * Returns:
 *      true अगर successful,
 *      false अगर unrecoverable problems were encountered.
 *****************************************************************************/
bool
ixgb_init_hw(काष्ठा ixgb_hw *hw)
अणु
	u32 i;
	bool status;

	ENTER();

	/* Issue a global reset to the MAC.  This will reset the chip's
	 * transmit, receive, DMA, and link units.  It will not effect
	 * the current PCI configuration.  The global reset bit is self-
	 * clearing, and should clear within a microsecond.
	 */
	pr_debug("Issuing a global reset to MAC\n");

	ixgb_mac_reset(hw);

	pr_debug("Issuing an EE reset to MAC\n");
#अगर_घोषित HP_ZX1
	/* Workaround क्रम 82597EX reset errata */
	IXGB_WRITE_REG_IO(hw, CTRL1, IXGB_CTRL1_EE_RST);
#अन्यथा
	IXGB_WRITE_REG(hw, CTRL1, IXGB_CTRL1_EE_RST);
#पूर्ण_अगर

	/* Delay a few ms just to allow the reset to complete */
	msleep(IXGB_DELAY_AFTER_EE_RESET);

	अगर (!ixgb_get_eeprom_data(hw))
		वापस false;

	/* Use the device id to determine the type of phy/transceiver. */
	hw->device_id = ixgb_get_ee_device_id(hw);
	hw->phy_type = ixgb_identअगरy_phy(hw);

	/* Setup the receive addresses.
	 * Receive Address Registers (RARs 0 - 15).
	 */
	ixgb_init_rx_addrs(hw);

	/*
	 * Check that a valid MAC address has been set.
	 * If it is not valid, we fail hardware init.
	 */
	अगर (!mac_addr_valid(hw->curr_mac_addr)) अणु
		pr_debug("MAC address invalid after ixgb_init_rx_addrs\n");
		वापस(false);
	पूर्ण

	/* tell the routines in this file they can access hardware again */
	hw->adapter_stopped = false;

	/* Fill in the bus_info काष्ठाure */
	ixgb_get_bus_info(hw);

	/* Zero out the Multicast HASH table */
	pr_debug("Zeroing the MTA\n");
	क्रम (i = 0; i < IXGB_MC_TBL_SIZE; i++)
		IXGB_WRITE_REG_ARRAY(hw, MTA, i, 0);

	/* Zero out the VLAN Filter Table Array */
	ixgb_clear_vfta(hw);

	/* Zero all of the hardware counters */
	ixgb_clear_hw_cntrs(hw);

	/* Call a subroutine to setup flow control. */
	status = ixgb_setup_fc(hw);

	/* 82597EX errata: Call check-क्रम-link in हाल lane deskew is locked */
	ixgb_check_क्रम_link(hw);

	वापस status;
पूर्ण

/******************************************************************************
 * Initializes receive address filters.
 *
 * hw - Struct containing variables accessed by shared code
 *
 * Places the MAC address in receive address रेजिस्टर 0 and clears the rest
 * of the receive address रेजिस्टरs. Clears the multicast table. Assumes
 * the receiver is in reset when the routine is called.
 *****************************************************************************/
अटल व्योम
ixgb_init_rx_addrs(काष्ठा ixgb_hw *hw)
अणु
	u32 i;

	ENTER();

	/*
	 * If the current mac address is valid, assume it is a software override
	 * to the permanent address.
	 * Otherwise, use the permanent address from the eeprom.
	 */
	अगर (!mac_addr_valid(hw->curr_mac_addr)) अणु

		/* Get the MAC address from the eeprom क्रम later reference */
		ixgb_get_ee_mac_addr(hw, hw->curr_mac_addr);

		pr_debug("Keeping Permanent MAC Addr = %pM\n",
			 hw->curr_mac_addr);
	पूर्ण अन्यथा अणु

		/* Setup the receive address. */
		pr_debug("Overriding MAC Address in RAR[0]\n");
		pr_debug("New MAC Addr = %pM\n", hw->curr_mac_addr);

		ixgb_rar_set(hw, hw->curr_mac_addr, 0);
	पूर्ण

	/* Zero out the other 15 receive addresses. */
	pr_debug("Clearing RAR[1-15]\n");
	क्रम (i = 1; i < IXGB_RAR_ENTRIES; i++) अणु
		/* Write high reg first to disable the AV bit first */
		IXGB_WRITE_REG_ARRAY(hw, RA, ((i << 1) + 1), 0);
		IXGB_WRITE_REG_ARRAY(hw, RA, (i << 1), 0);
	पूर्ण
पूर्ण

/******************************************************************************
 * Updates the MAC's list of multicast addresses.
 *
 * hw - Struct containing variables accessed by shared code
 * mc_addr_list - the list of new multicast addresses
 * mc_addr_count - number of addresses
 * pad - number of bytes between addresses in the list
 *
 * The given list replaces any existing list. Clears the last 15 receive
 * address रेजिस्टरs and the multicast table. Uses receive address रेजिस्टरs
 * क्रम the first 15 multicast addresses, and hashes the rest पूर्णांकo the
 * multicast table.
 *****************************************************************************/
व्योम
ixgb_mc_addr_list_update(काष्ठा ixgb_hw *hw,
			  u8 *mc_addr_list,
			  u32 mc_addr_count,
			  u32 pad)
अणु
	u32 hash_value;
	u32 i;
	u32 rar_used_count = 1;		/* RAR[0] is used क्रम our MAC address */
	u8 *mca;

	ENTER();

	/* Set the new number of MC addresses that we are being requested to use. */
	hw->num_mc_addrs = mc_addr_count;

	/* Clear RAR[1-15] */
	pr_debug("Clearing RAR[1-15]\n");
	क्रम (i = rar_used_count; i < IXGB_RAR_ENTRIES; i++) अणु
		IXGB_WRITE_REG_ARRAY(hw, RA, (i << 1), 0);
		IXGB_WRITE_REG_ARRAY(hw, RA, ((i << 1) + 1), 0);
	पूर्ण

	/* Clear the MTA */
	pr_debug("Clearing MTA\n");
	क्रम (i = 0; i < IXGB_MC_TBL_SIZE; i++)
		IXGB_WRITE_REG_ARRAY(hw, MTA, i, 0);

	/* Add the new addresses */
	mca = mc_addr_list;
	क्रम (i = 0; i < mc_addr_count; i++) अणु
		pr_debug("Adding the multicast addresses:\n");
		pr_debug("MC Addr #%d = %pM\n", i, mca);

		/* Place this multicast address in the RAR अगर there is room, *
		 * अन्यथा put it in the MTA
		 */
		अगर (rar_used_count < IXGB_RAR_ENTRIES) अणु
			ixgb_rar_set(hw, mca, rar_used_count);
			pr_debug("Added a multicast address to RAR[%d]\n", i);
			rar_used_count++;
		पूर्ण अन्यथा अणु
			hash_value = ixgb_hash_mc_addr(hw, mca);

			pr_debug("Hash value = 0x%03X\n", hash_value);

			ixgb_mta_set(hw, hash_value);
		पूर्ण

		mca += ETH_ALEN + pad;
	पूर्ण

	pr_debug("MC Update Complete\n");
पूर्ण

/******************************************************************************
 * Hashes an address to determine its location in the multicast table
 *
 * hw - Struct containing variables accessed by shared code
 * mc_addr - the multicast address to hash
 *
 * Returns:
 *      The hash value
 *****************************************************************************/
अटल u32
ixgb_hash_mc_addr(काष्ठा ixgb_hw *hw,
		   u8 *mc_addr)
अणु
	u32 hash_value = 0;

	ENTER();

	/* The portion of the address that is used क्रम the hash table is
	 * determined by the mc_filter_type setting.
	 */
	चयन (hw->mc_filter_type) अणु
		/* [0] [1] [2] [3] [4] [5]
		 * 01  AA  00  12  34  56
		 * LSB                 MSB - According to H/W करोcs */
	हाल 0:
		/* [47:36] i.e. 0x563 क्रम above example address */
		hash_value =
		    ((mc_addr[4] >> 4) | (((u16) mc_addr[5]) << 4));
		अवरोध;
	हाल 1:		/* [46:35] i.e. 0xAC6 क्रम above example address */
		hash_value =
		    ((mc_addr[4] >> 3) | (((u16) mc_addr[5]) << 5));
		अवरोध;
	हाल 2:		/* [45:34] i.e. 0x5D8 क्रम above example address */
		hash_value =
		    ((mc_addr[4] >> 2) | (((u16) mc_addr[5]) << 6));
		अवरोध;
	हाल 3:		/* [43:32] i.e. 0x634 क्रम above example address */
		hash_value = ((mc_addr[4]) | (((u16) mc_addr[5]) << 8));
		अवरोध;
	शेष:
		/* Invalid mc_filter_type, what should we करो? */
		pr_debug("MC filter type param set incorrectly\n");
		ASSERT(0);
		अवरोध;
	पूर्ण

	hash_value &= 0xFFF;
	वापस hash_value;
पूर्ण

/******************************************************************************
 * Sets the bit in the multicast table corresponding to the hash value.
 *
 * hw - Struct containing variables accessed by shared code
 * hash_value - Multicast address hash value
 *****************************************************************************/
अटल व्योम
ixgb_mta_set(काष्ठा ixgb_hw *hw,
		  u32 hash_value)
अणु
	u32 hash_bit, hash_reg;
	u32 mta_reg;

	/* The MTA is a रेजिस्टर array of 128 32-bit रेजिस्टरs.
	 * It is treated like an array of 4096 bits.  We want to set
	 * bit BitArray[hash_value]. So we figure out what रेजिस्टर
	 * the bit is in, पढ़ो it, OR in the new bit, then ग_लिखो
	 * back the new value.  The रेजिस्टर is determined by the
	 * upper 7 bits of the hash value and the bit within that
	 * रेजिस्टर are determined by the lower 5 bits of the value.
	 */
	hash_reg = (hash_value >> 5) & 0x7F;
	hash_bit = hash_value & 0x1F;

	mta_reg = IXGB_READ_REG_ARRAY(hw, MTA, hash_reg);

	mta_reg |= (1 << hash_bit);

	IXGB_WRITE_REG_ARRAY(hw, MTA, hash_reg, mta_reg);
पूर्ण

/******************************************************************************
 * Puts an ethernet address पूर्णांकo a receive address रेजिस्टर.
 *
 * hw - Struct containing variables accessed by shared code
 * addr - Address to put पूर्णांकo receive address रेजिस्टर
 * index - Receive address रेजिस्टर to ग_लिखो
 *****************************************************************************/
व्योम
ixgb_rar_set(काष्ठा ixgb_hw *hw,
		  u8 *addr,
		  u32 index)
अणु
	u32 rar_low, rar_high;

	ENTER();

	/* HW expects these in little endian so we reverse the byte order
	 * from network order (big endian) to little endian
	 */
	rar_low = ((u32) addr[0] |
		   ((u32)addr[1] << 8) |
		   ((u32)addr[2] << 16) |
		   ((u32)addr[3] << 24));

	rar_high = ((u32) addr[4] |
			((u32)addr[5] << 8) |
			IXGB_RAH_AV);

	IXGB_WRITE_REG_ARRAY(hw, RA, (index << 1), rar_low);
	IXGB_WRITE_REG_ARRAY(hw, RA, ((index << 1) + 1), rar_high);
पूर्ण

/******************************************************************************
 * Writes a value to the specअगरied offset in the VLAN filter table.
 *
 * hw - Struct containing variables accessed by shared code
 * offset - Offset in VLAN filer table to ग_लिखो
 * value - Value to ग_लिखो पूर्णांकo VLAN filter table
 *****************************************************************************/
व्योम
ixgb_ग_लिखो_vfta(काष्ठा ixgb_hw *hw,
		 u32 offset,
		 u32 value)
अणु
	IXGB_WRITE_REG_ARRAY(hw, VFTA, offset, value);
पूर्ण

/******************************************************************************
 * Clears the VLAN filer table
 *
 * hw - Struct containing variables accessed by shared code
 *****************************************************************************/
अटल व्योम
ixgb_clear_vfta(काष्ठा ixgb_hw *hw)
अणु
	u32 offset;

	क्रम (offset = 0; offset < IXGB_VLAN_FILTER_TBL_SIZE; offset++)
		IXGB_WRITE_REG_ARRAY(hw, VFTA, offset, 0);
पूर्ण

/******************************************************************************
 * Configures the flow control settings based on SW configuration.
 *
 * hw - Struct containing variables accessed by shared code
 *****************************************************************************/

अटल bool
ixgb_setup_fc(काष्ठा ixgb_hw *hw)
अणु
	u32 ctrl_reg;
	u32 pap_reg = 0;   /* by शेष, assume no छोड़ो समय */
	bool status = true;

	ENTER();

	/* Get the current control reg 0 settings */
	ctrl_reg = IXGB_READ_REG(hw, CTRL0);

	/* Clear the Receive Pause Enable and Transmit Pause Enable bits */
	ctrl_reg &= ~(IXGB_CTRL0_RPE | IXGB_CTRL0_TPE);

	/* The possible values of the "flow_control" parameter are:
	 *      0:  Flow control is completely disabled
	 *      1:  Rx flow control is enabled (we can receive छोड़ो frames
	 *          but not send छोड़ो frames).
	 *      2:  Tx flow control is enabled (we can send छोड़ो frames
	 *          but we करो not support receiving छोड़ो frames).
	 *      3:  Both Rx and TX flow control (symmetric) are enabled.
	 *  other:  Invalid.
	 */
	चयन (hw->fc.type) अणु
	हाल ixgb_fc_none:	/* 0 */
		/* Set CMDC bit to disable Rx Flow control */
		ctrl_reg |= (IXGB_CTRL0_CMDC);
		अवरोध;
	हाल ixgb_fc_rx_छोड़ो:	/* 1 */
		/* RX Flow control is enabled, and TX Flow control is
		 * disabled.
		 */
		ctrl_reg |= (IXGB_CTRL0_RPE);
		अवरोध;
	हाल ixgb_fc_tx_छोड़ो:	/* 2 */
		/* TX Flow control is enabled, and RX Flow control is
		 * disabled, by a software over-ride.
		 */
		ctrl_reg |= (IXGB_CTRL0_TPE);
		pap_reg = hw->fc.छोड़ो_समय;
		अवरोध;
	हाल ixgb_fc_full:	/* 3 */
		/* Flow control (both RX and TX) is enabled by a software
		 * over-ride.
		 */
		ctrl_reg |= (IXGB_CTRL0_RPE | IXGB_CTRL0_TPE);
		pap_reg = hw->fc.छोड़ो_समय;
		अवरोध;
	शेष:
		/* We should never get here.  The value should be 0-3. */
		pr_debug("Flow control param set incorrectly\n");
		ASSERT(0);
		अवरोध;
	पूर्ण

	/* Write the new settings */
	IXGB_WRITE_REG(hw, CTRL0, ctrl_reg);

	अगर (pap_reg != 0)
		IXGB_WRITE_REG(hw, PAP, pap_reg);

	/* Set the flow control receive threshold रेजिस्टरs.  Normally,
	 * these रेजिस्टरs will be set to a शेष threshold that may be
	 * adjusted later by the driver's runसमय code.  However, अगर the
	 * ability to transmit छोड़ो frames in not enabled, then these
	 * रेजिस्टरs will be set to 0.
	 */
	अगर (!(hw->fc.type & ixgb_fc_tx_छोड़ो)) अणु
		IXGB_WRITE_REG(hw, FCRTL, 0);
		IXGB_WRITE_REG(hw, FCRTH, 0);
	पूर्ण अन्यथा अणु
	   /* We need to set up the Receive Threshold high and low water
	    * marks as well as (optionally) enabling the transmission of XON
	    * frames. */
		अगर (hw->fc.send_xon) अणु
			IXGB_WRITE_REG(hw, FCRTL,
				(hw->fc.low_water | IXGB_FCRTL_XONE));
		पूर्ण अन्यथा अणु
			IXGB_WRITE_REG(hw, FCRTL, hw->fc.low_water);
		पूर्ण
		IXGB_WRITE_REG(hw, FCRTH, hw->fc.high_water);
	पूर्ण
	वापस status;
पूर्ण

/******************************************************************************
 * Reads a word from a device over the Management Data Interface (MDI) bus.
 * This पूर्णांकerface is used to manage Physical layer devices.
 *
 * hw          - Struct containing variables accessed by hw code
 * reg_address - Offset of device रेजिस्टर being पढ़ो.
 * phy_address - Address of device on MDI.
 *
 * Returns:  Data word (16 bits) from MDI device.
 *
 * The 82597EX has support क्रम several MDI access methods.  This routine
 * uses the new protocol MDI Single Command and Address Operation.
 * This requires that first an address cycle command is sent, followed by a
 * पढ़ो command.
 *****************************************************************************/
अटल u16
ixgb_पढ़ो_phy_reg(काष्ठा ixgb_hw *hw,
		u32 reg_address,
		u32 phy_address,
		u32 device_type)
अणु
	u32 i;
	u32 data;
	u32 command = 0;

	ASSERT(reg_address <= IXGB_MAX_PHY_REG_ADDRESS);
	ASSERT(phy_address <= IXGB_MAX_PHY_ADDRESS);
	ASSERT(device_type <= IXGB_MAX_PHY_DEV_TYPE);

	/* Setup and ग_लिखो the address cycle command */
	command = ((reg_address << IXGB_MSCA_NP_ADDR_SHIFT) |
		   (device_type << IXGB_MSCA_DEV_TYPE_SHIFT) |
		   (phy_address << IXGB_MSCA_PHY_ADDR_SHIFT) |
		   (IXGB_MSCA_ADDR_CYCLE | IXGB_MSCA_MDI_COMMAND));

	IXGB_WRITE_REG(hw, MSCA, command);

    /**************************************************************
    ** Check every 10 usec to see अगर the address cycle completed
    ** The COMMAND bit will clear when the operation is complete.
    ** This may take as दीर्घ as 64 usecs (we'll रुको 100 usecs max)
    ** from the CPU Write to the Ready bit निश्चितion.
    **************************************************************/

	क्रम (i = 0; i < 10; i++)
	अणु
		udelay(10);

		command = IXGB_READ_REG(hw, MSCA);

		अगर ((command & IXGB_MSCA_MDI_COMMAND) == 0)
			अवरोध;
	पूर्ण

	ASSERT((command & IXGB_MSCA_MDI_COMMAND) == 0);

	/* Address cycle complete, setup and ग_लिखो the पढ़ो command */
	command = ((reg_address << IXGB_MSCA_NP_ADDR_SHIFT) |
		   (device_type << IXGB_MSCA_DEV_TYPE_SHIFT) |
		   (phy_address << IXGB_MSCA_PHY_ADDR_SHIFT) |
		   (IXGB_MSCA_READ | IXGB_MSCA_MDI_COMMAND));

	IXGB_WRITE_REG(hw, MSCA, command);

    /**************************************************************
    ** Check every 10 usec to see अगर the पढ़ो command completed
    ** The COMMAND bit will clear when the operation is complete.
    ** The पढ़ो may take as दीर्घ as 64 usecs (we'll रुको 100 usecs max)
    ** from the CPU Write to the Ready bit निश्चितion.
    **************************************************************/

	क्रम (i = 0; i < 10; i++)
	अणु
		udelay(10);

		command = IXGB_READ_REG(hw, MSCA);

		अगर ((command & IXGB_MSCA_MDI_COMMAND) == 0)
			अवरोध;
	पूर्ण

	ASSERT((command & IXGB_MSCA_MDI_COMMAND) == 0);

	/* Operation is complete, get the data from the MDIO Read/Write Data
	 * रेजिस्टर and वापस.
	 */
	data = IXGB_READ_REG(hw, MSRWD);
	data >>= IXGB_MSRWD_READ_DATA_SHIFT;
	वापस((u16) data);
पूर्ण

/******************************************************************************
 * Writes a word to a device over the Management Data Interface (MDI) bus.
 * This पूर्णांकerface is used to manage Physical layer devices.
 *
 * hw          - Struct containing variables accessed by hw code
 * reg_address - Offset of device रेजिस्टर being पढ़ो.
 * phy_address - Address of device on MDI.
 * device_type - Also known as the Device ID or DID.
 * data        - 16-bit value to be written
 *
 * Returns:  व्योम.
 *
 * The 82597EX has support क्रम several MDI access methods.  This routine
 * uses the new protocol MDI Single Command and Address Operation.
 * This requires that first an address cycle command is sent, followed by a
 * ग_लिखो command.
 *****************************************************************************/
अटल व्योम
ixgb_ग_लिखो_phy_reg(काष्ठा ixgb_hw *hw,
			u32 reg_address,
			u32 phy_address,
			u32 device_type,
			u16 data)
अणु
	u32 i;
	u32 command = 0;

	ASSERT(reg_address <= IXGB_MAX_PHY_REG_ADDRESS);
	ASSERT(phy_address <= IXGB_MAX_PHY_ADDRESS);
	ASSERT(device_type <= IXGB_MAX_PHY_DEV_TYPE);

	/* Put the data in the MDIO Read/Write Data रेजिस्टर */
	IXGB_WRITE_REG(hw, MSRWD, (u32)data);

	/* Setup and ग_लिखो the address cycle command */
	command = ((reg_address << IXGB_MSCA_NP_ADDR_SHIFT)  |
			   (device_type << IXGB_MSCA_DEV_TYPE_SHIFT) |
			   (phy_address << IXGB_MSCA_PHY_ADDR_SHIFT) |
			   (IXGB_MSCA_ADDR_CYCLE | IXGB_MSCA_MDI_COMMAND));

	IXGB_WRITE_REG(hw, MSCA, command);

	/**************************************************************
	** Check every 10 usec to see अगर the address cycle completed
	** The COMMAND bit will clear when the operation is complete.
	** This may take as दीर्घ as 64 usecs (we'll रुको 100 usecs max)
	** from the CPU Write to the Ready bit निश्चितion.
	**************************************************************/

	क्रम (i = 0; i < 10; i++)
	अणु
		udelay(10);

		command = IXGB_READ_REG(hw, MSCA);

		अगर ((command & IXGB_MSCA_MDI_COMMAND) == 0)
			अवरोध;
	पूर्ण

	ASSERT((command & IXGB_MSCA_MDI_COMMAND) == 0);

	/* Address cycle complete, setup and ग_लिखो the ग_लिखो command */
	command = ((reg_address << IXGB_MSCA_NP_ADDR_SHIFT)  |
			   (device_type << IXGB_MSCA_DEV_TYPE_SHIFT) |
			   (phy_address << IXGB_MSCA_PHY_ADDR_SHIFT) |
			   (IXGB_MSCA_WRITE | IXGB_MSCA_MDI_COMMAND));

	IXGB_WRITE_REG(hw, MSCA, command);

	/**************************************************************
	** Check every 10 usec to see अगर the पढ़ो command completed
	** The COMMAND bit will clear when the operation is complete.
	** The ग_लिखो may take as दीर्घ as 64 usecs (we'll रुको 100 usecs max)
	** from the CPU Write to the Ready bit निश्चितion.
	**************************************************************/

	क्रम (i = 0; i < 10; i++)
	अणु
		udelay(10);

		command = IXGB_READ_REG(hw, MSCA);

		अगर ((command & IXGB_MSCA_MDI_COMMAND) == 0)
			अवरोध;
	पूर्ण

	ASSERT((command & IXGB_MSCA_MDI_COMMAND) == 0);

	/* Operation is complete, वापस. */
पूर्ण

/******************************************************************************
 * Checks to see अगर the link status of the hardware has changed.
 *
 * hw - Struct containing variables accessed by hw code
 *
 * Called by any function that needs to check the link status of the adapter.
 *****************************************************************************/
व्योम
ixgb_check_क्रम_link(काष्ठा ixgb_hw *hw)
अणु
	u32 status_reg;
	u32 xpcss_reg;

	ENTER();

	xpcss_reg = IXGB_READ_REG(hw, XPCSS);
	status_reg = IXGB_READ_REG(hw, STATUS);

	अगर ((xpcss_reg & IXGB_XPCSS_ALIGN_STATUS) &&
	    (status_reg & IXGB_STATUS_LU)) अणु
		hw->link_up = true;
	पूर्ण अन्यथा अगर (!(xpcss_reg & IXGB_XPCSS_ALIGN_STATUS) &&
		   (status_reg & IXGB_STATUS_LU)) अणु
		pr_debug("XPCSS Not Aligned while Status:LU is set\n");
		hw->link_up = ixgb_link_reset(hw);
	पूर्ण अन्यथा अणु
		/*
		 * 82597EX errata.  Since the lane deskew problem may prevent
		 * link, reset the link beक्रमe reporting link करोwn.
		 */
		hw->link_up = ixgb_link_reset(hw);
	पूर्ण
	/*  Anything अन्यथा क्रम 10 Gig?? */
पूर्ण

/******************************************************************************
 * Check क्रम a bad link condition that may have occurred.
 * The indication is that the RFC / LFC रेजिस्टरs may be incrementing
 * continually.  A full adapter reset is required to recover.
 *
 * hw - Struct containing variables accessed by hw code
 *
 * Called by any function that needs to check the link status of the adapter.
 *****************************************************************************/
bool ixgb_check_क्रम_bad_link(काष्ठा ixgb_hw *hw)
अणु
	u32 newLFC, newRFC;
	bool bad_link_वापसcode = false;

	अगर (hw->phy_type == ixgb_phy_type_txn17401) अणु
		newLFC = IXGB_READ_REG(hw, LFC);
		newRFC = IXGB_READ_REG(hw, RFC);
		अगर ((hw->lastLFC + 250 < newLFC)
		    || (hw->lastRFC + 250 < newRFC)) अणु
			pr_debug("BAD LINK! too many LFC/RFC since last check\n");
			bad_link_वापसcode = true;
		पूर्ण
		hw->lastLFC = newLFC;
		hw->lastRFC = newRFC;
	पूर्ण

	वापस bad_link_वापसcode;
पूर्ण

/******************************************************************************
 * Clears all hardware statistics counters.
 *
 * hw - Struct containing variables accessed by shared code
 *****************************************************************************/
अटल व्योम
ixgb_clear_hw_cntrs(काष्ठा ixgb_hw *hw)
अणु
	ENTER();

	/* अगर we are stopped or resetting निकास gracefully */
	अगर (hw->adapter_stopped) अणु
		pr_debug("Exiting because the adapter is stopped!!!\n");
		वापस;
	पूर्ण

	IXGB_READ_REG(hw, TPRL);
	IXGB_READ_REG(hw, TPRH);
	IXGB_READ_REG(hw, GPRCL);
	IXGB_READ_REG(hw, GPRCH);
	IXGB_READ_REG(hw, BPRCL);
	IXGB_READ_REG(hw, BPRCH);
	IXGB_READ_REG(hw, MPRCL);
	IXGB_READ_REG(hw, MPRCH);
	IXGB_READ_REG(hw, UPRCL);
	IXGB_READ_REG(hw, UPRCH);
	IXGB_READ_REG(hw, VPRCL);
	IXGB_READ_REG(hw, VPRCH);
	IXGB_READ_REG(hw, JPRCL);
	IXGB_READ_REG(hw, JPRCH);
	IXGB_READ_REG(hw, GORCL);
	IXGB_READ_REG(hw, GORCH);
	IXGB_READ_REG(hw, TORL);
	IXGB_READ_REG(hw, TORH);
	IXGB_READ_REG(hw, RNBC);
	IXGB_READ_REG(hw, RUC);
	IXGB_READ_REG(hw, ROC);
	IXGB_READ_REG(hw, RLEC);
	IXGB_READ_REG(hw, CRCERRS);
	IXGB_READ_REG(hw, ICBC);
	IXGB_READ_REG(hw, ECBC);
	IXGB_READ_REG(hw, MPC);
	IXGB_READ_REG(hw, TPTL);
	IXGB_READ_REG(hw, TPTH);
	IXGB_READ_REG(hw, GPTCL);
	IXGB_READ_REG(hw, GPTCH);
	IXGB_READ_REG(hw, BPTCL);
	IXGB_READ_REG(hw, BPTCH);
	IXGB_READ_REG(hw, MPTCL);
	IXGB_READ_REG(hw, MPTCH);
	IXGB_READ_REG(hw, UPTCL);
	IXGB_READ_REG(hw, UPTCH);
	IXGB_READ_REG(hw, VPTCL);
	IXGB_READ_REG(hw, VPTCH);
	IXGB_READ_REG(hw, JPTCL);
	IXGB_READ_REG(hw, JPTCH);
	IXGB_READ_REG(hw, GOTCL);
	IXGB_READ_REG(hw, GOTCH);
	IXGB_READ_REG(hw, TOTL);
	IXGB_READ_REG(hw, TOTH);
	IXGB_READ_REG(hw, DC);
	IXGB_READ_REG(hw, PLT64C);
	IXGB_READ_REG(hw, TSCTC);
	IXGB_READ_REG(hw, TSCTFC);
	IXGB_READ_REG(hw, IBIC);
	IXGB_READ_REG(hw, RFC);
	IXGB_READ_REG(hw, LFC);
	IXGB_READ_REG(hw, PFRC);
	IXGB_READ_REG(hw, PFTC);
	IXGB_READ_REG(hw, MCFRC);
	IXGB_READ_REG(hw, MCFTC);
	IXGB_READ_REG(hw, XONRXC);
	IXGB_READ_REG(hw, XONTXC);
	IXGB_READ_REG(hw, XOFFRXC);
	IXGB_READ_REG(hw, XOFFTXC);
	IXGB_READ_REG(hw, RJC);
पूर्ण

/******************************************************************************
 * Turns on the software controllable LED
 *
 * hw - Struct containing variables accessed by shared code
 *****************************************************************************/
व्योम
ixgb_led_on(काष्ठा ixgb_hw *hw)
अणु
	u32 ctrl0_reg = IXGB_READ_REG(hw, CTRL0);

	/* To turn on the LED, clear software-definable pin 0 (SDP0). */
	ctrl0_reg &= ~IXGB_CTRL0_SDP0;
	IXGB_WRITE_REG(hw, CTRL0, ctrl0_reg);
पूर्ण

/******************************************************************************
 * Turns off the software controllable LED
 *
 * hw - Struct containing variables accessed by shared code
 *****************************************************************************/
व्योम
ixgb_led_off(काष्ठा ixgb_hw *hw)
अणु
	u32 ctrl0_reg = IXGB_READ_REG(hw, CTRL0);

	/* To turn off the LED, set software-definable pin 0 (SDP0). */
	ctrl0_reg |= IXGB_CTRL0_SDP0;
	IXGB_WRITE_REG(hw, CTRL0, ctrl0_reg);
पूर्ण

/******************************************************************************
 * Gets the current PCI bus type, speed, and width of the hardware
 *
 * hw - Struct containing variables accessed by shared code
 *****************************************************************************/
अटल व्योम
ixgb_get_bus_info(काष्ठा ixgb_hw *hw)
अणु
	u32 status_reg;

	status_reg = IXGB_READ_REG(hw, STATUS);

	hw->bus.type = (status_reg & IXGB_STATUS_PCIX_MODE) ?
		ixgb_bus_type_pcix : ixgb_bus_type_pci;

	अगर (hw->bus.type == ixgb_bus_type_pci) अणु
		hw->bus.speed = (status_reg & IXGB_STATUS_PCI_SPD) ?
			ixgb_bus_speed_66 : ixgb_bus_speed_33;
	पूर्ण अन्यथा अणु
		चयन (status_reg & IXGB_STATUS_PCIX_SPD_MASK) अणु
		हाल IXGB_STATUS_PCIX_SPD_66:
			hw->bus.speed = ixgb_bus_speed_66;
			अवरोध;
		हाल IXGB_STATUS_PCIX_SPD_100:
			hw->bus.speed = ixgb_bus_speed_100;
			अवरोध;
		हाल IXGB_STATUS_PCIX_SPD_133:
			hw->bus.speed = ixgb_bus_speed_133;
			अवरोध;
		शेष:
			hw->bus.speed = ixgb_bus_speed_reserved;
			अवरोध;
		पूर्ण
	पूर्ण

	hw->bus.width = (status_reg & IXGB_STATUS_BUS64) ?
		ixgb_bus_width_64 : ixgb_bus_width_32;
पूर्ण

/******************************************************************************
 * Tests a MAC address to ensure it is a valid Inभागidual Address
 *
 * mac_addr - poपूर्णांकer to MAC address.
 *
 *****************************************************************************/
अटल bool
mac_addr_valid(u8 *mac_addr)
अणु
	bool is_valid = true;
	ENTER();

	/* Make sure it is not a multicast address */
	अगर (is_multicast_ether_addr(mac_addr)) अणु
		pr_debug("MAC address is multicast\n");
		is_valid = false;
	पूर्ण
	/* Not a broadcast address */
	अन्यथा अगर (is_broadcast_ether_addr(mac_addr)) अणु
		pr_debug("MAC address is broadcast\n");
		is_valid = false;
	पूर्ण
	/* Reject the zero address */
	अन्यथा अगर (is_zero_ether_addr(mac_addr)) अणु
		pr_debug("MAC address is all zeros\n");
		is_valid = false;
	पूर्ण
	वापस is_valid;
पूर्ण

/******************************************************************************
 * Resets the 10GbE link.  Waits the settle समय and वापसs the state of
 * the link.
 *
 * hw - Struct containing variables accessed by shared code
 *****************************************************************************/
अटल bool
ixgb_link_reset(काष्ठा ixgb_hw *hw)
अणु
	bool link_status = false;
	u8 रुको_retries = MAX_RESET_ITERATIONS;
	u8 lrst_retries = MAX_RESET_ITERATIONS;

	करो अणु
		/* Reset the link */
		IXGB_WRITE_REG(hw, CTRL0,
			       IXGB_READ_REG(hw, CTRL0) | IXGB_CTRL0_LRST);

		/* Wait क्रम link-up and lane re-alignment */
		करो अणु
			udelay(IXGB_DELAY_USECS_AFTER_LINK_RESET);
			link_status =
			    ((IXGB_READ_REG(hw, STATUS) & IXGB_STATUS_LU)
			     && (IXGB_READ_REG(hw, XPCSS) &
				 IXGB_XPCSS_ALIGN_STATUS)) ? true : false;
		पूर्ण जबतक (!link_status && --रुको_retries);

	पूर्ण जबतक (!link_status && --lrst_retries);

	वापस link_status;
पूर्ण

/******************************************************************************
 * Resets the 10GbE optics module.
 *
 * hw - Struct containing variables accessed by shared code
 *****************************************************************************/
अटल व्योम
ixgb_optics_reset(काष्ठा ixgb_hw *hw)
अणु
	अगर (hw->phy_type == ixgb_phy_type_txn17401) अणु
		ixgb_ग_लिखो_phy_reg(hw,
				   MDIO_CTRL1,
				   IXGB_PHY_ADDRESS,
				   MDIO_MMD_PMAPMD,
				   MDIO_CTRL1_RESET);

		ixgb_पढ़ो_phy_reg(hw, MDIO_CTRL1, IXGB_PHY_ADDRESS, MDIO_MMD_PMAPMD);
	पूर्ण
पूर्ण

/******************************************************************************
 * Resets the 10GbE optics module क्रम Sun variant NIC.
 *
 * hw - Struct containing variables accessed by shared code
 *****************************************************************************/

#घोषणा   IXGB_BCM8704_USER_PMD_TX_CTRL_REG         0xC803
#घोषणा   IXGB_BCM8704_USER_PMD_TX_CTRL_REG_VAL     0x0164
#घोषणा   IXGB_BCM8704_USER_CTRL_REG                0xC800
#घोषणा   IXGB_BCM8704_USER_CTRL_REG_VAL            0x7FBF
#घोषणा   IXGB_BCM8704_USER_DEV3_ADDR               0x0003
#घोषणा   IXGB_SUN_PHY_ADDRESS                      0x0000
#घोषणा   IXGB_SUN_PHY_RESET_DELAY                     305

अटल व्योम
ixgb_optics_reset_bcm(काष्ठा ixgb_hw *hw)
अणु
	u32 ctrl = IXGB_READ_REG(hw, CTRL0);
	ctrl &= ~IXGB_CTRL0_SDP2;
	ctrl |= IXGB_CTRL0_SDP3;
	IXGB_WRITE_REG(hw, CTRL0, ctrl);
	IXGB_WRITE_FLUSH(hw);

	/* SerDes needs extra delay */
	msleep(IXGB_SUN_PHY_RESET_DELAY);

	/* Broadcom 7408L configuration */
	/* Reference घड़ी config */
	ixgb_ग_लिखो_phy_reg(hw,
			   IXGB_BCM8704_USER_PMD_TX_CTRL_REG,
			   IXGB_SUN_PHY_ADDRESS,
			   IXGB_BCM8704_USER_DEV3_ADDR,
			   IXGB_BCM8704_USER_PMD_TX_CTRL_REG_VAL);
	/*  we must पढ़ो the रेजिस्टरs twice */
	ixgb_पढ़ो_phy_reg(hw,
			  IXGB_BCM8704_USER_PMD_TX_CTRL_REG,
			  IXGB_SUN_PHY_ADDRESS,
			  IXGB_BCM8704_USER_DEV3_ADDR);
	ixgb_पढ़ो_phy_reg(hw,
			  IXGB_BCM8704_USER_PMD_TX_CTRL_REG,
			  IXGB_SUN_PHY_ADDRESS,
			  IXGB_BCM8704_USER_DEV3_ADDR);

	ixgb_ग_लिखो_phy_reg(hw,
			   IXGB_BCM8704_USER_CTRL_REG,
			   IXGB_SUN_PHY_ADDRESS,
			   IXGB_BCM8704_USER_DEV3_ADDR,
			   IXGB_BCM8704_USER_CTRL_REG_VAL);
	ixgb_पढ़ो_phy_reg(hw,
			  IXGB_BCM8704_USER_CTRL_REG,
			  IXGB_SUN_PHY_ADDRESS,
			  IXGB_BCM8704_USER_DEV3_ADDR);
	ixgb_पढ़ो_phy_reg(hw,
			  IXGB_BCM8704_USER_CTRL_REG,
			  IXGB_SUN_PHY_ADDRESS,
			  IXGB_BCM8704_USER_DEV3_ADDR);

	/* SerDes needs extra delay */
	msleep(IXGB_SUN_PHY_RESET_DELAY);
पूर्ण
