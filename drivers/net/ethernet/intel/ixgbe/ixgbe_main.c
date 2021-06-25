<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/माला.स>
#समावेश <linux/in.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/sctp.h>
#समावेश <linux/pkt_sched.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/slab.h>
#समावेश <net/checksum.h>
#समावेश <net/ip6_checksum.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_macvlan.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>
#समावेश <linux/atomic.h>
#समावेश <linux/numa.h>
#समावेश <generated/utsrelease.h>
#समावेश <scsi/fc/fc_fcoe.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/tc_act/tc_gact.h>
#समावेश <net/tc_act/tc_mirred.h>
#समावेश <net/vxlan.h>
#समावेश <net/mpls.h>
#समावेश <net/xdp_sock_drv.h>
#समावेश <net/xfrm.h>

#समावेश "ixgbe.h"
#समावेश "ixgbe_common.h"
#समावेश "ixgbe_dcb_82599.h"
#समावेश "ixgbe_phy.h"
#समावेश "ixgbe_sriov.h"
#समावेश "ixgbe_model.h"
#समावेश "ixgbe_txrx_common.h"

अक्षर ixgbe_driver_name[] = "ixgbe";
अटल स्थिर अक्षर ixgbe_driver_string[] =
			      "Intel(R) 10 Gigabit PCI Express Network Driver";
#अगर_घोषित IXGBE_FCOE
अक्षर ixgbe_शेष_device_descr[] =
			      "Intel(R) 10 Gigabit Network Connection";
#अन्यथा
अटल अक्षर ixgbe_शेष_device_descr[] =
			      "Intel(R) 10 Gigabit Network Connection";
#पूर्ण_अगर
अटल स्थिर अक्षर ixgbe_copyright[] =
				"Copyright (c) 1999-2016 Intel Corporation.";

अटल स्थिर अक्षर ixgbe_overheat_msg[] = "Network adapter has been stopped because it has over heated. Restart the computer. If the problem persists, power off the system and replace the adapter";

अटल स्थिर काष्ठा ixgbe_info *ixgbe_info_tbl[] = अणु
	[board_82598]		= &ixgbe_82598_info,
	[board_82599]		= &ixgbe_82599_info,
	[board_X540]		= &ixgbe_X540_info,
	[board_X550]		= &ixgbe_X550_info,
	[board_X550EM_x]	= &ixgbe_X550EM_x_info,
	[board_x550em_x_fw]	= &ixgbe_x550em_x_fw_info,
	[board_x550em_a]	= &ixgbe_x550em_a_info,
	[board_x550em_a_fw]	= &ixgbe_x550em_a_fw_info,
पूर्ण;

/* ixgbe_pci_tbl - PCI Device ID Table
 *
 * Wildcard entries (PCI_ANY_ID) should come last
 * Last entry must be all 0s
 *
 * अणु Venकरोr ID, Device ID, SubVenकरोr ID, SubDevice ID,
 *   Class, Class Mask, निजी data (not used) पूर्ण
 */
अटल स्थिर काष्ठा pci_device_id ixgbe_pci_tbl[] = अणु
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82598), board_82598 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82598AF_DUAL_PORT), board_82598 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82598AF_SINGLE_PORT), board_82598 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82598AT), board_82598 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82598AT2), board_82598 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82598EB_CX4), board_82598 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82598_CX4_DUAL_PORT), board_82598 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82598_DA_DUAL_PORT), board_82598 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82598_SR_DUAL_PORT_EM), board_82598 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82598EB_XF_LR), board_82598 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82598EB_SFP_LOM), board_82598 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82598_BX), board_82598 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599_KX4), board_82599 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599_XAUI_LOM), board_82599 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599_KR), board_82599 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599_SFP), board_82599 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599_SFP_EM), board_82599 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599_KX4_MEZZ), board_82599 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599_CX4), board_82599 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599_BACKPLANE_FCOE), board_82599 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599_SFP_FCOE), board_82599 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599_T3_LOM), board_82599 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599_COMBO_BACKPLANE), board_82599 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X540T), board_X540 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599_SFP_SF2), board_82599 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599_LS), board_82599 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599_QSFP_SF_QP), board_82599 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599EN_SFP), board_82599 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599_SFP_SF_QP), board_82599 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X540T1), board_X540 पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550T), board_X550पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550T1), board_X550पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_X_KX4), board_X550EM_xपूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_X_XFI), board_X550EM_xपूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_X_KR), board_X550EM_xपूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_X_10G_T), board_X550EM_xपूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_X_SFP), board_X550EM_xपूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_X_1G_T), board_x550em_x_fwपूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_A_KR), board_x550em_a पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_A_KR_L), board_x550em_a पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_A_SFP_N), board_x550em_a पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_A_SGMII), board_x550em_a पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_A_SGMII_L), board_x550em_a पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_A_10G_T), board_x550em_aपूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_A_SFP), board_x550em_a पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_A_1G_T), board_x550em_a_fw पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_A_1G_T_L), board_x550em_a_fw पूर्ण,
	/* required last entry */
	अणु0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ixgbe_pci_tbl);

#अगर_घोषित CONFIG_IXGBE_DCA
अटल पूर्णांक ixgbe_notअगरy_dca(काष्ठा notअगरier_block *, अचिन्हित दीर्घ event,
			    व्योम *p);
अटल काष्ठा notअगरier_block dca_notअगरier = अणु
	.notअगरier_call = ixgbe_notअगरy_dca,
	.next          = शून्य,
	.priority      = 0
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI_IOV
अटल अचिन्हित पूर्णांक max_vfs;
module_param(max_vfs, uपूर्णांक, 0);
MODULE_PARM_DESC(max_vfs,
		 "Maximum number of virtual functions to allocate per physical function - default is zero and maximum value is 63. (Deprecated)");
#पूर्ण_अगर /* CONFIG_PCI_IOV */

अटल अचिन्हित पूर्णांक allow_unsupported_sfp;
module_param(allow_unsupported_sfp, uपूर्णांक, 0);
MODULE_PARM_DESC(allow_unsupported_sfp,
		 "Allow unsupported and untested SFP+ modules on 82599-based adapters");

#घोषणा DEFAULT_MSG_ENABLE (NETIF_MSG_DRV|NETIF_MSG_PROBE|NETIF_MSG_LINK)
अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");

MODULE_AUTHOR("Intel Corporation, <linux.nics@intel.com>");
MODULE_DESCRIPTION("Intel(R) 10 Gigabit PCI Express Network Driver");
MODULE_LICENSE("GPL v2");

अटल काष्ठा workqueue_काष्ठा *ixgbe_wq;

अटल bool ixgbe_check_cfg_हटाओ(काष्ठा ixgbe_hw *hw, काष्ठा pci_dev *pdev);
अटल व्योम ixgbe_watchकरोg_link_is_करोwn(काष्ठा ixgbe_adapter *);

अटल स्थिर काष्ठा net_device_ops ixgbe_netdev_ops;

अटल bool netअगर_is_ixgbe(काष्ठा net_device *dev)
अणु
	वापस dev && (dev->netdev_ops == &ixgbe_netdev_ops);
पूर्ण

अटल पूर्णांक ixgbe_पढ़ो_pci_cfg_word_parent(काष्ठा ixgbe_adapter *adapter,
					  u32 reg, u16 *value)
अणु
	काष्ठा pci_dev *parent_dev;
	काष्ठा pci_bus *parent_bus;

	parent_bus = adapter->pdev->bus->parent;
	अगर (!parent_bus)
		वापस -1;

	parent_dev = parent_bus->self;
	अगर (!parent_dev)
		वापस -1;

	अगर (!pci_is_pcie(parent_dev))
		वापस -1;

	pcie_capability_पढ़ो_word(parent_dev, reg, value);
	अगर (*value == IXGBE_FAILED_READ_CFG_WORD &&
	    ixgbe_check_cfg_हटाओ(&adapter->hw, parent_dev))
		वापस -1;
	वापस 0;
पूर्ण

अटल s32 ixgbe_get_parent_bus_info(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u16 link_status = 0;
	पूर्णांक err;

	hw->bus.type = ixgbe_bus_type_pci_express;

	/* Get the negotiated link width and speed from PCI config space of the
	 * parent, as this device is behind a चयन
	 */
	err = ixgbe_पढ़ो_pci_cfg_word_parent(adapter, 18, &link_status);

	/* assume caller will handle error हाल */
	अगर (err)
		वापस err;

	hw->bus.width = ixgbe_convert_bus_width(link_status);
	hw->bus.speed = ixgbe_convert_bus_speed(link_status);

	वापस 0;
पूर्ण

/**
 * ixgbe_pcie_from_parent - Determine whether PCIe info should come from parent
 * @hw: hw specअगरic details
 *
 * This function is used by probe to determine whether a device's PCI-Express
 * bandwidth details should be gathered from the parent bus instead of from the
 * device. Used to ensure that various locations all have the correct device ID
 * checks.
 */
अटल अंतरभूत bool ixgbe_pcie_from_parent(काष्ठा ixgbe_hw *hw)
अणु
	चयन (hw->device_id) अणु
	हाल IXGBE_DEV_ID_82599_SFP_SF_QP:
	हाल IXGBE_DEV_ID_82599_QSFP_SF_QP:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम ixgbe_check_minimum_link(काष्ठा ixgbe_adapter *adapter,
				     पूर्णांक expected_gts)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा pci_dev *pdev;

	/* Some devices are not connected over PCIe and thus करो not negotiate
	 * speed. These devices करो not have valid bus info, and thus any report
	 * we generate may not be correct.
	 */
	अगर (hw->bus.type == ixgbe_bus_type_पूर्णांकernal)
		वापस;

	/* determine whether to use the parent device */
	अगर (ixgbe_pcie_from_parent(&adapter->hw))
		pdev = adapter->pdev->bus->parent->self;
	अन्यथा
		pdev = adapter->pdev;

	pcie_prपूर्णांक_link_status(pdev);
पूर्ण

अटल व्योम ixgbe_service_event_schedule(काष्ठा ixgbe_adapter *adapter)
अणु
	अगर (!test_bit(__IXGBE_DOWN, &adapter->state) &&
	    !test_bit(__IXGBE_REMOVING, &adapter->state) &&
	    !test_and_set_bit(__IXGBE_SERVICE_SCHED, &adapter->state))
		queue_work(ixgbe_wq, &adapter->service_task);
पूर्ण

अटल व्योम ixgbe_हटाओ_adapter(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_adapter *adapter = hw->back;

	अगर (!hw->hw_addr)
		वापस;
	hw->hw_addr = शून्य;
	e_dev_err("Adapter removed\n");
	अगर (test_bit(__IXGBE_SERVICE_INITED, &adapter->state))
		ixgbe_service_event_schedule(adapter);
पूर्ण

अटल u32 ixgbe_check_हटाओ(काष्ठा ixgbe_hw *hw, u32 reg)
अणु
	u8 __iomem *reg_addr;
	u32 value;
	पूर्णांक i;

	reg_addr = READ_ONCE(hw->hw_addr);
	अगर (ixgbe_हटाओd(reg_addr))
		वापस IXGBE_FAILED_READ_REG;

	/* Register पढ़ो of 0xFFFFFFF can indicate the adapter has been हटाओd,
	 * so perक्रमm several status रेजिस्टर पढ़ोs to determine अगर the adapter
	 * has been हटाओd.
	 */
	क्रम (i = 0; i < IXGBE_FAILED_READ_RETRIES; i++) अणु
		value = पढ़ोl(reg_addr + IXGBE_STATUS);
		अगर (value != IXGBE_FAILED_READ_REG)
			अवरोध;
		mdelay(3);
	पूर्ण

	अगर (value == IXGBE_FAILED_READ_REG)
		ixgbe_हटाओ_adapter(hw);
	अन्यथा
		value = पढ़ोl(reg_addr + reg);
	वापस value;
पूर्ण

/**
 * ixgbe_पढ़ो_reg - Read from device रेजिस्टर
 * @hw: hw specअगरic details
 * @reg: offset of रेजिस्टर to पढ़ो
 *
 * Returns : value पढ़ो or IXGBE_FAILED_READ_REG अगर हटाओd
 *
 * This function is used to पढ़ो device रेजिस्टरs. It checks क्रम device
 * removal by confirming any पढ़ो that वापसs all ones by checking the
 * status रेजिस्टर value क्रम all ones. This function aव्योमs पढ़ोing from
 * the hardware अगर a removal was previously detected in which हाल it
 * वापसs IXGBE_FAILED_READ_REG (all ones).
 */
u32 ixgbe_पढ़ो_reg(काष्ठा ixgbe_hw *hw, u32 reg)
अणु
	u8 __iomem *reg_addr = READ_ONCE(hw->hw_addr);
	u32 value;

	अगर (ixgbe_हटाओd(reg_addr))
		वापस IXGBE_FAILED_READ_REG;
	अगर (unlikely(hw->phy.nw_mng_अगर_sel &
		     IXGBE_NW_MNG_IF_SEL_SGMII_ENABLE)) अणु
		काष्ठा ixgbe_adapter *adapter;
		पूर्णांक i;

		क्रम (i = 0; i < 200; ++i) अणु
			value = पढ़ोl(reg_addr + IXGBE_MAC_SGMII_BUSY);
			अगर (likely(!value))
				जाओ ग_लिखोs_completed;
			अगर (value == IXGBE_FAILED_READ_REG) अणु
				ixgbe_हटाओ_adapter(hw);
				वापस IXGBE_FAILED_READ_REG;
			पूर्ण
			udelay(5);
		पूर्ण

		adapter = hw->back;
		e_warn(hw, "register writes incomplete %08x\n", value);
	पूर्ण

ग_लिखोs_completed:
	value = पढ़ोl(reg_addr + reg);
	अगर (unlikely(value == IXGBE_FAILED_READ_REG))
		value = ixgbe_check_हटाओ(hw, reg);
	वापस value;
पूर्ण

अटल bool ixgbe_check_cfg_हटाओ(काष्ठा ixgbe_hw *hw, काष्ठा pci_dev *pdev)
अणु
	u16 value;

	pci_पढ़ो_config_word(pdev, PCI_VENDOR_ID, &value);
	अगर (value == IXGBE_FAILED_READ_CFG_WORD) अणु
		ixgbe_हटाओ_adapter(hw);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

u16 ixgbe_पढ़ो_pci_cfg_word(काष्ठा ixgbe_hw *hw, u32 reg)
अणु
	काष्ठा ixgbe_adapter *adapter = hw->back;
	u16 value;

	अगर (ixgbe_हटाओd(hw->hw_addr))
		वापस IXGBE_FAILED_READ_CFG_WORD;
	pci_पढ़ो_config_word(adapter->pdev, reg, &value);
	अगर (value == IXGBE_FAILED_READ_CFG_WORD &&
	    ixgbe_check_cfg_हटाओ(hw, adapter->pdev))
		वापस IXGBE_FAILED_READ_CFG_WORD;
	वापस value;
पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
अटल u32 ixgbe_पढ़ो_pci_cfg_dword(काष्ठा ixgbe_hw *hw, u32 reg)
अणु
	काष्ठा ixgbe_adapter *adapter = hw->back;
	u32 value;

	अगर (ixgbe_हटाओd(hw->hw_addr))
		वापस IXGBE_FAILED_READ_CFG_DWORD;
	pci_पढ़ो_config_dword(adapter->pdev, reg, &value);
	अगर (value == IXGBE_FAILED_READ_CFG_DWORD &&
	    ixgbe_check_cfg_हटाओ(hw, adapter->pdev))
		वापस IXGBE_FAILED_READ_CFG_DWORD;
	वापस value;
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_IOV */

व्योम ixgbe_ग_लिखो_pci_cfg_word(काष्ठा ixgbe_hw *hw, u32 reg, u16 value)
अणु
	काष्ठा ixgbe_adapter *adapter = hw->back;

	अगर (ixgbe_हटाओd(hw->hw_addr))
		वापस;
	pci_ग_लिखो_config_word(adapter->pdev, reg, value);
पूर्ण

अटल व्योम ixgbe_service_event_complete(काष्ठा ixgbe_adapter *adapter)
अणु
	BUG_ON(!test_bit(__IXGBE_SERVICE_SCHED, &adapter->state));

	/* flush memory to make sure state is correct beक्रमe next watchकरोg */
	smp_mb__beक्रमe_atomic();
	clear_bit(__IXGBE_SERVICE_SCHED, &adapter->state);
पूर्ण

काष्ठा ixgbe_reg_info अणु
	u32 ofs;
	अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा ixgbe_reg_info ixgbe_reg_info_tbl[] = अणु

	/* General Registers */
	अणुIXGBE_CTRL, "CTRL"पूर्ण,
	अणुIXGBE_STATUS, "STATUS"पूर्ण,
	अणुIXGBE_CTRL_EXT, "CTRL_EXT"पूर्ण,

	/* Interrupt Registers */
	अणुIXGBE_EICR, "EICR"पूर्ण,

	/* RX Registers */
	अणुIXGBE_SRRCTL(0), "SRRCTL"पूर्ण,
	अणुIXGBE_DCA_RXCTRL(0), "DRXCTL"पूर्ण,
	अणुIXGBE_RDLEN(0), "RDLEN"पूर्ण,
	अणुIXGBE_RDH(0), "RDH"पूर्ण,
	अणुIXGBE_RDT(0), "RDT"पूर्ण,
	अणुIXGBE_RXDCTL(0), "RXDCTL"पूर्ण,
	अणुIXGBE_RDBAL(0), "RDBAL"पूर्ण,
	अणुIXGBE_RDBAH(0), "RDBAH"पूर्ण,

	/* TX Registers */
	अणुIXGBE_TDBAL(0), "TDBAL"पूर्ण,
	अणुIXGBE_TDBAH(0), "TDBAH"पूर्ण,
	अणुIXGBE_TDLEN(0), "TDLEN"पूर्ण,
	अणुIXGBE_TDH(0), "TDH"पूर्ण,
	अणुIXGBE_TDT(0), "TDT"पूर्ण,
	अणुIXGBE_TXDCTL(0), "TXDCTL"पूर्ण,

	/* List Terminator */
	अणु .name = शून्य पूर्ण
पूर्ण;


/*
 * ixgbe_regdump - रेजिस्टर prपूर्णांकout routine
 */
अटल व्योम ixgbe_regdump(काष्ठा ixgbe_hw *hw, काष्ठा ixgbe_reg_info *reginfo)
अणु
	पूर्णांक i;
	अक्षर rname[16];
	u32 regs[64];

	चयन (reginfo->ofs) अणु
	हाल IXGBE_SRRCTL(0):
		क्रम (i = 0; i < 64; i++)
			regs[i] = IXGBE_READ_REG(hw, IXGBE_SRRCTL(i));
		अवरोध;
	हाल IXGBE_DCA_RXCTRL(0):
		क्रम (i = 0; i < 64; i++)
			regs[i] = IXGBE_READ_REG(hw, IXGBE_DCA_RXCTRL(i));
		अवरोध;
	हाल IXGBE_RDLEN(0):
		क्रम (i = 0; i < 64; i++)
			regs[i] = IXGBE_READ_REG(hw, IXGBE_RDLEN(i));
		अवरोध;
	हाल IXGBE_RDH(0):
		क्रम (i = 0; i < 64; i++)
			regs[i] = IXGBE_READ_REG(hw, IXGBE_RDH(i));
		अवरोध;
	हाल IXGBE_RDT(0):
		क्रम (i = 0; i < 64; i++)
			regs[i] = IXGBE_READ_REG(hw, IXGBE_RDT(i));
		अवरोध;
	हाल IXGBE_RXDCTL(0):
		क्रम (i = 0; i < 64; i++)
			regs[i] = IXGBE_READ_REG(hw, IXGBE_RXDCTL(i));
		अवरोध;
	हाल IXGBE_RDBAL(0):
		क्रम (i = 0; i < 64; i++)
			regs[i] = IXGBE_READ_REG(hw, IXGBE_RDBAL(i));
		अवरोध;
	हाल IXGBE_RDBAH(0):
		क्रम (i = 0; i < 64; i++)
			regs[i] = IXGBE_READ_REG(hw, IXGBE_RDBAH(i));
		अवरोध;
	हाल IXGBE_TDBAL(0):
		क्रम (i = 0; i < 64; i++)
			regs[i] = IXGBE_READ_REG(hw, IXGBE_TDBAL(i));
		अवरोध;
	हाल IXGBE_TDBAH(0):
		क्रम (i = 0; i < 64; i++)
			regs[i] = IXGBE_READ_REG(hw, IXGBE_TDBAH(i));
		अवरोध;
	हाल IXGBE_TDLEN(0):
		क्रम (i = 0; i < 64; i++)
			regs[i] = IXGBE_READ_REG(hw, IXGBE_TDLEN(i));
		अवरोध;
	हाल IXGBE_TDH(0):
		क्रम (i = 0; i < 64; i++)
			regs[i] = IXGBE_READ_REG(hw, IXGBE_TDH(i));
		अवरोध;
	हाल IXGBE_TDT(0):
		क्रम (i = 0; i < 64; i++)
			regs[i] = IXGBE_READ_REG(hw, IXGBE_TDT(i));
		अवरोध;
	हाल IXGBE_TXDCTL(0):
		क्रम (i = 0; i < 64; i++)
			regs[i] = IXGBE_READ_REG(hw, IXGBE_TXDCTL(i));
		अवरोध;
	शेष:
		pr_info("%-15s %08x\n",
			reginfo->name, IXGBE_READ_REG(hw, reginfo->ofs));
		वापस;
	पूर्ण

	i = 0;
	जबतक (i < 64) अणु
		पूर्णांक j;
		अक्षर buf[9 * 8 + 1];
		अक्षर *p = buf;

		snम_लिखो(rname, 16, "%s[%d-%d]", reginfo->name, i, i + 7);
		क्रम (j = 0; j < 8; j++)
			p += प्र_लिखो(p, " %08x", regs[i++]);
		pr_err("%-15s%s\n", rname, buf);
	पूर्ण

पूर्ण

अटल व्योम ixgbe_prपूर्णांक_buffer(काष्ठा ixgbe_ring *ring, पूर्णांक n)
अणु
	काष्ठा ixgbe_tx_buffer *tx_buffer;

	tx_buffer = &ring->tx_buffer_info[ring->next_to_clean];
	pr_info(" %5d %5X %5X %016llX %08X %p %016llX\n",
		n, ring->next_to_use, ring->next_to_clean,
		(u64)dma_unmap_addr(tx_buffer, dma),
		dma_unmap_len(tx_buffer, len),
		tx_buffer->next_to_watch,
		(u64)tx_buffer->समय_stamp);
पूर्ण

/*
 * ixgbe_dump - Prपूर्णांक रेजिस्टरs, tx-rings and rx-rings
 */
अटल व्योम ixgbe_dump(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा ixgbe_reg_info *reginfo;
	पूर्णांक n = 0;
	काष्ठा ixgbe_ring *ring;
	काष्ठा ixgbe_tx_buffer *tx_buffer;
	जोड़ ixgbe_adv_tx_desc *tx_desc;
	काष्ठा my_u0 अणु u64 a; u64 b; पूर्ण *u0;
	काष्ठा ixgbe_ring *rx_ring;
	जोड़ ixgbe_adv_rx_desc *rx_desc;
	काष्ठा ixgbe_rx_buffer *rx_buffer_info;
	पूर्णांक i = 0;

	अगर (!netअगर_msg_hw(adapter))
		वापस;

	/* Prपूर्णांक netdevice Info */
	अगर (netdev) अणु
		dev_info(&adapter->pdev->dev, "Net device Info\n");
		pr_info("Device Name     state            "
			"trans_start\n");
		pr_info("%-15s %016lX %016lX\n",
			netdev->name,
			netdev->state,
			dev_trans_start(netdev));
	पूर्ण

	/* Prपूर्णांक Registers */
	dev_info(&adapter->pdev->dev, "Register Dump\n");
	pr_info(" Register Name   Value\n");
	क्रम (reginfo = (काष्ठा ixgbe_reg_info *)ixgbe_reg_info_tbl;
	     reginfo->name; reginfo++) अणु
		ixgbe_regdump(hw, reginfo);
	पूर्ण

	/* Prपूर्णांक TX Ring Summary */
	अगर (!netdev || !netअगर_running(netdev))
		वापस;

	dev_info(&adapter->pdev->dev, "TX Rings Summary\n");
	pr_info(" %s     %s              %s        %s\n",
		"Queue [NTU] [NTC] [bi(ntc)->dma  ]",
		"leng", "ntw", "timestamp");
	क्रम (n = 0; n < adapter->num_tx_queues; n++) अणु
		ring = adapter->tx_ring[n];
		ixgbe_prपूर्णांक_buffer(ring, n);
	पूर्ण

	क्रम (n = 0; n < adapter->num_xdp_queues; n++) अणु
		ring = adapter->xdp_ring[n];
		ixgbe_prपूर्णांक_buffer(ring, n);
	पूर्ण

	/* Prपूर्णांक TX Rings */
	अगर (!netअगर_msg_tx_करोne(adapter))
		जाओ rx_ring_summary;

	dev_info(&adapter->pdev->dev, "TX Rings Dump\n");

	/* Transmit Descriptor Formats
	 *
	 * 82598 Advanced Transmit Descriptor
	 *   +--------------------------------------------------------------+
	 * 0 |         Buffer Address [63:0]                                |
	 *   +--------------------------------------------------------------+
	 * 8 |  PAYLEN  | POPTS  | IDX | STA | DCMD  |DTYP |  RSV |  DTALEN |
	 *   +--------------------------------------------------------------+
	 *   63       46 45    40 39 36 35 32 31   24 23 20 19              0
	 *
	 * 82598 Advanced Transmit Descriptor (Write-Back Format)
	 *   +--------------------------------------------------------------+
	 * 0 |                          RSV [63:0]                          |
	 *   +--------------------------------------------------------------+
	 * 8 |            RSV           |  STA  |          NXTSEQ           |
	 *   +--------------------------------------------------------------+
	 *   63                       36 35   32 31                         0
	 *
	 * 82599+ Advanced Transmit Descriptor
	 *   +--------------------------------------------------------------+
	 * 0 |         Buffer Address [63:0]                                |
	 *   +--------------------------------------------------------------+
	 * 8 |PAYLEN  |POPTS|CC|IDX  |STA  |DCMD  |DTYP |MAC  |RSV  |DTALEN |
	 *   +--------------------------------------------------------------+
	 *   63     46 45 40 39 38 36 35 32 31  24 23 20 19 18 17 16 15     0
	 *
	 * 82599+ Advanced Transmit Descriptor (Write-Back Format)
	 *   +--------------------------------------------------------------+
	 * 0 |                          RSV [63:0]                          |
	 *   +--------------------------------------------------------------+
	 * 8 |            RSV           |  STA  |           RSV             |
	 *   +--------------------------------------------------------------+
	 *   63                       36 35   32 31                         0
	 */

	क्रम (n = 0; n < adapter->num_tx_queues; n++) अणु
		ring = adapter->tx_ring[n];
		pr_info("------------------------------------\n");
		pr_info("TX QUEUE INDEX = %d\n", ring->queue_index);
		pr_info("------------------------------------\n");
		pr_info("%s%s    %s              %s        %s          %s\n",
			"T [desc]     [address 63:0  ] ",
			"[PlPOIdStDDt Ln] [bi->dma       ] ",
			"leng", "ntw", "timestamp", "bi->skb");

		क्रम (i = 0; ring->desc && (i < ring->count); i++) अणु
			tx_desc = IXGBE_TX_DESC(ring, i);
			tx_buffer = &ring->tx_buffer_info[i];
			u0 = (काष्ठा my_u0 *)tx_desc;
			अगर (dma_unmap_len(tx_buffer, len) > 0) अणु
				स्थिर अक्षर *ring_desc;

				अगर (i == ring->next_to_use &&
				    i == ring->next_to_clean)
					ring_desc = " NTC/U";
				अन्यथा अगर (i == ring->next_to_use)
					ring_desc = " NTU";
				अन्यथा अगर (i == ring->next_to_clean)
					ring_desc = " NTC";
				अन्यथा
					ring_desc = "";
				pr_info("T [0x%03X]    %016llX %016llX %016llX %08X %p %016llX %p%s",
					i,
					le64_to_cpu((__क्रमce __le64)u0->a),
					le64_to_cpu((__क्रमce __le64)u0->b),
					(u64)dma_unmap_addr(tx_buffer, dma),
					dma_unmap_len(tx_buffer, len),
					tx_buffer->next_to_watch,
					(u64)tx_buffer->समय_stamp,
					tx_buffer->skb,
					ring_desc);

				अगर (netअगर_msg_pktdata(adapter) &&
				    tx_buffer->skb)
					prपूर्णांक_hex_dump(KERN_INFO, "",
						DUMP_PREFIX_ADDRESS, 16, 1,
						tx_buffer->skb->data,
						dma_unmap_len(tx_buffer, len),
						true);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Prपूर्णांक RX Rings Summary */
rx_ring_summary:
	dev_info(&adapter->pdev->dev, "RX Rings Summary\n");
	pr_info("Queue [NTU] [NTC]\n");
	क्रम (n = 0; n < adapter->num_rx_queues; n++) अणु
		rx_ring = adapter->rx_ring[n];
		pr_info("%5d %5X %5X\n",
			n, rx_ring->next_to_use, rx_ring->next_to_clean);
	पूर्ण

	/* Prपूर्णांक RX Rings */
	अगर (!netअगर_msg_rx_status(adapter))
		वापस;

	dev_info(&adapter->pdev->dev, "RX Rings Dump\n");

	/* Receive Descriptor Formats
	 *
	 * 82598 Advanced Receive Descriptor (Read) Format
	 *    63                                           1        0
	 *    +-----------------------------------------------------+
	 *  0 |       Packet Buffer Address [63:1]           |A0/NSE|
	 *    +----------------------------------------------+------+
	 *  8 |       Header Buffer Address [63:1]           |  DD  |
	 *    +-----------------------------------------------------+
	 *
	 *
	 * 82598 Advanced Receive Descriptor (Write-Back) Format
	 *
	 *   63       48 47    32 31  30      21 20 16 15   4 3     0
	 *   +------------------------------------------------------+
	 * 0 |       RSS Hash /  |SPH| HDR_LEN  | RSV |Packet|  RSS |
	 *   | Packet   | IP     |   |          |     | Type | Type |
	 *   | Checksum | Ident  |   |          |     |      |      |
	 *   +------------------------------------------------------+
	 * 8 | VLAN Tag | Length | Extended Error | Extended Status |
	 *   +------------------------------------------------------+
	 *   63       48 47    32 31            20 19               0
	 *
	 * 82599+ Advanced Receive Descriptor (Read) Format
	 *    63                                           1        0
	 *    +-----------------------------------------------------+
	 *  0 |       Packet Buffer Address [63:1]           |A0/NSE|
	 *    +----------------------------------------------+------+
	 *  8 |       Header Buffer Address [63:1]           |  DD  |
	 *    +-----------------------------------------------------+
	 *
	 *
	 * 82599+ Advanced Receive Descriptor (Write-Back) Format
	 *
	 *   63       48 47    32 31  30      21 20 17 16   4 3     0
	 *   +------------------------------------------------------+
	 * 0 |RSS / Frag Checksum|SPH| HDR_LEN  |RSC- |Packet|  RSS |
	 *   |/ RTT / PCoE_PARAM |   |          | CNT | Type | Type |
	 *   |/ Flow Dir Flt ID  |   |          |     |      |      |
	 *   +------------------------------------------------------+
	 * 8 | VLAN Tag | Length |Extended Error| Xtnd Status/NEXTP |
	 *   +------------------------------------------------------+
	 *   63       48 47    32 31          20 19                 0
	 */

	क्रम (n = 0; n < adapter->num_rx_queues; n++) अणु
		rx_ring = adapter->rx_ring[n];
		pr_info("------------------------------------\n");
		pr_info("RX QUEUE INDEX = %d\n", rx_ring->queue_index);
		pr_info("------------------------------------\n");
		pr_info("%s%s%s\n",
			"R  [desc]      [ PktBuf     A0] ",
			"[  HeadBuf   DD] [bi->dma       ] [bi->skb       ] ",
			"<-- Adv Rx Read format");
		pr_info("%s%s%s\n",
			"RWB[desc]      [PcsmIpSHl PtRs] ",
			"[vl er S cks ln] ---------------- [bi->skb       ] ",
			"<-- Adv Rx Write-Back format");

		क्रम (i = 0; i < rx_ring->count; i++) अणु
			स्थिर अक्षर *ring_desc;

			अगर (i == rx_ring->next_to_use)
				ring_desc = " NTU";
			अन्यथा अगर (i == rx_ring->next_to_clean)
				ring_desc = " NTC";
			अन्यथा
				ring_desc = "";

			rx_buffer_info = &rx_ring->rx_buffer_info[i];
			rx_desc = IXGBE_RX_DESC(rx_ring, i);
			u0 = (काष्ठा my_u0 *)rx_desc;
			अगर (rx_desc->wb.upper.length) अणु
				/* Descriptor Done */
				pr_info("RWB[0x%03X]     %016llX %016llX ---------------- %p%s\n",
					i,
					le64_to_cpu((__क्रमce __le64)u0->a),
					le64_to_cpu((__क्रमce __le64)u0->b),
					rx_buffer_info->skb,
					ring_desc);
			पूर्ण अन्यथा अणु
				pr_info("R  [0x%03X]     %016llX %016llX %016llX %p%s\n",
					i,
					le64_to_cpu((__क्रमce __le64)u0->a),
					le64_to_cpu((__क्रमce __le64)u0->b),
					(u64)rx_buffer_info->dma,
					rx_buffer_info->skb,
					ring_desc);

				अगर (netअगर_msg_pktdata(adapter) &&
				    rx_buffer_info->dma) अणु
					prपूर्णांक_hex_dump(KERN_INFO, "",
					   DUMP_PREFIX_ADDRESS, 16, 1,
					   page_address(rx_buffer_info->page) +
						    rx_buffer_info->page_offset,
					   ixgbe_rx_bufsz(rx_ring), true);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ixgbe_release_hw_control(काष्ठा ixgbe_adapter *adapter)
अणु
	u32 ctrl_ext;

	/* Let firmware take over control of h/w */
	ctrl_ext = IXGBE_READ_REG(&adapter->hw, IXGBE_CTRL_EXT);
	IXGBE_WRITE_REG(&adapter->hw, IXGBE_CTRL_EXT,
			ctrl_ext & ~IXGBE_CTRL_EXT_DRV_LOAD);
पूर्ण

अटल व्योम ixgbe_get_hw_control(काष्ठा ixgbe_adapter *adapter)
अणु
	u32 ctrl_ext;

	/* Let firmware know the driver has taken over */
	ctrl_ext = IXGBE_READ_REG(&adapter->hw, IXGBE_CTRL_EXT);
	IXGBE_WRITE_REG(&adapter->hw, IXGBE_CTRL_EXT,
			ctrl_ext | IXGBE_CTRL_EXT_DRV_LOAD);
पूर्ण

/**
 * ixgbe_set_ivar - set the IVAR रेजिस्टरs, mapping पूर्णांकerrupt causes to vectors
 * @adapter: poपूर्णांकer to adapter काष्ठा
 * @direction: 0 क्रम Rx, 1 क्रम Tx, -1 क्रम other causes
 * @queue: queue to map the corresponding पूर्णांकerrupt to
 * @msix_vector: the vector to map to the corresponding queue
 *
 */
अटल व्योम ixgbe_set_ivar(काष्ठा ixgbe_adapter *adapter, s8 direction,
			   u8 queue, u8 msix_vector)
अणु
	u32 ivar, index;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		msix_vector |= IXGBE_IVAR_ALLOC_VAL;
		अगर (direction == -1)
			direction = 0;
		index = (((direction * 64) + queue) >> 2) & 0x1F;
		ivar = IXGBE_READ_REG(hw, IXGBE_IVAR(index));
		ivar &= ~(0xFF << (8 * (queue & 0x3)));
		ivar |= (msix_vector << (8 * (queue & 0x3)));
		IXGBE_WRITE_REG(hw, IXGBE_IVAR(index), ivar);
		अवरोध;
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		अगर (direction == -1) अणु
			/* other causes */
			msix_vector |= IXGBE_IVAR_ALLOC_VAL;
			index = ((queue & 1) * 8);
			ivar = IXGBE_READ_REG(&adapter->hw, IXGBE_IVAR_MISC);
			ivar &= ~(0xFF << index);
			ivar |= (msix_vector << index);
			IXGBE_WRITE_REG(&adapter->hw, IXGBE_IVAR_MISC, ivar);
			अवरोध;
		पूर्ण अन्यथा अणु
			/* tx or rx causes */
			msix_vector |= IXGBE_IVAR_ALLOC_VAL;
			index = ((16 * (queue & 1)) + (8 * direction));
			ivar = IXGBE_READ_REG(hw, IXGBE_IVAR(queue >> 1));
			ivar &= ~(0xFF << index);
			ivar |= (msix_vector << index);
			IXGBE_WRITE_REG(hw, IXGBE_IVAR(queue >> 1), ivar);
			अवरोध;
		पूर्ण
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम ixgbe_irq_rearm_queues(काष्ठा ixgbe_adapter *adapter,
			    u64 qmask)
अणु
	u32 mask;

	चयन (adapter->hw.mac.type) अणु
	हाल ixgbe_mac_82598EB:
		mask = (IXGBE_EIMS_RTX_QUEUE & qmask);
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_EICS, mask);
		अवरोध;
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		mask = (qmask & 0xFFFFFFFF);
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_EICS_EX(0), mask);
		mask = (qmask >> 32);
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_EICS_EX(1), mask);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ixgbe_update_xoff_rx_lfc(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा ixgbe_hw_stats *hwstats = &adapter->stats;
	पूर्णांक i;
	u32 data;

	अगर ((hw->fc.current_mode != ixgbe_fc_full) &&
	    (hw->fc.current_mode != ixgbe_fc_rx_छोड़ो))
		वापस;

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		data = IXGBE_READ_REG(hw, IXGBE_LXOFFRXC);
		अवरोध;
	शेष:
		data = IXGBE_READ_REG(hw, IXGBE_LXOFFRXCNT);
	पूर्ण
	hwstats->lxoffrxc += data;

	/* refill credits (no tx hang) अगर we received xoff */
	अगर (!data)
		वापस;

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		clear_bit(__IXGBE_HANG_CHECK_ARMED,
			  &adapter->tx_ring[i]->state);

	क्रम (i = 0; i < adapter->num_xdp_queues; i++)
		clear_bit(__IXGBE_HANG_CHECK_ARMED,
			  &adapter->xdp_ring[i]->state);
पूर्ण

अटल व्योम ixgbe_update_xoff_received(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा ixgbe_hw_stats *hwstats = &adapter->stats;
	u32 xoff[8] = अणु0पूर्ण;
	u8 tc;
	पूर्णांक i;
	bool pfc_en = adapter->dcb_cfg.pfc_mode_enable;

	अगर (adapter->ixgbe_ieee_pfc)
		pfc_en |= !!(adapter->ixgbe_ieee_pfc->pfc_en);

	अगर (!(adapter->flags & IXGBE_FLAG_DCB_ENABLED) || !pfc_en) अणु
		ixgbe_update_xoff_rx_lfc(adapter);
		वापस;
	पूर्ण

	/* update stats क्रम each tc, only valid with PFC enabled */
	क्रम (i = 0; i < MAX_TX_PACKET_BUFFERS; i++) अणु
		u32 pxoffrxc;

		चयन (hw->mac.type) अणु
		हाल ixgbe_mac_82598EB:
			pxoffrxc = IXGBE_READ_REG(hw, IXGBE_PXOFFRXC(i));
			अवरोध;
		शेष:
			pxoffrxc = IXGBE_READ_REG(hw, IXGBE_PXOFFRXCNT(i));
		पूर्ण
		hwstats->pxoffrxc[i] += pxoffrxc;
		/* Get the TC क्रम given UP */
		tc = netdev_get_prio_tc_map(adapter->netdev, i);
		xoff[tc] += pxoffrxc;
	पूर्ण

	/* disarm tx queues that have received xoff frames */
	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		काष्ठा ixgbe_ring *tx_ring = adapter->tx_ring[i];

		tc = tx_ring->dcb_tc;
		अगर (xoff[tc])
			clear_bit(__IXGBE_HANG_CHECK_ARMED, &tx_ring->state);
	पूर्ण

	क्रम (i = 0; i < adapter->num_xdp_queues; i++) अणु
		काष्ठा ixgbe_ring *xdp_ring = adapter->xdp_ring[i];

		tc = xdp_ring->dcb_tc;
		अगर (xoff[tc])
			clear_bit(__IXGBE_HANG_CHECK_ARMED, &xdp_ring->state);
	पूर्ण
पूर्ण

अटल u64 ixgbe_get_tx_completed(काष्ठा ixgbe_ring *ring)
अणु
	वापस ring->stats.packets;
पूर्ण

अटल u64 ixgbe_get_tx_pending(काष्ठा ixgbe_ring *ring)
अणु
	अचिन्हित पूर्णांक head, tail;

	head = ring->next_to_clean;
	tail = ring->next_to_use;

	वापस ((head <= tail) ? tail : tail + ring->count) - head;
पूर्ण

अटल अंतरभूत bool ixgbe_check_tx_hang(काष्ठा ixgbe_ring *tx_ring)
अणु
	u32 tx_करोne = ixgbe_get_tx_completed(tx_ring);
	u32 tx_करोne_old = tx_ring->tx_stats.tx_करोne_old;
	u32 tx_pending = ixgbe_get_tx_pending(tx_ring);

	clear_check_क्रम_tx_hang(tx_ring);

	/*
	 * Check क्रम a hung queue, but be thorough. This verअगरies
	 * that a transmit has been completed since the previous
	 * check AND there is at least one packet pending. The
	 * ARMED bit is set to indicate a potential hang. The
	 * bit is cleared अगर a छोड़ो frame is received to हटाओ
	 * false hang detection due to PFC or 802.3x frames. By
	 * requiring this to fail twice we aव्योम races with
	 * pfc clearing the ARMED bit and conditions where we
	 * run the check_tx_hang logic with a transmit completion
	 * pending but without समय to complete it yet.
	 */
	अगर (tx_करोne_old == tx_करोne && tx_pending)
		/* make sure it is true क्रम two checks in a row */
		वापस test_and_set_bit(__IXGBE_HANG_CHECK_ARMED,
					&tx_ring->state);
	/* update completed stats and जारी */
	tx_ring->tx_stats.tx_करोne_old = tx_करोne;
	/* reset the countकरोwn */
	clear_bit(__IXGBE_HANG_CHECK_ARMED, &tx_ring->state);

	वापस false;
पूर्ण

/**
 * ixgbe_tx_समयout_reset - initiate reset due to Tx समयout
 * @adapter: driver निजी काष्ठा
 **/
अटल व्योम ixgbe_tx_समयout_reset(काष्ठा ixgbe_adapter *adapter)
अणु

	/* Do the reset outside of पूर्णांकerrupt context */
	अगर (!test_bit(__IXGBE_DOWN, &adapter->state)) अणु
		set_bit(__IXGBE_RESET_REQUESTED, &adapter->state);
		e_warn(drv, "initiating reset due to tx timeout\n");
		ixgbe_service_event_schedule(adapter);
	पूर्ण
पूर्ण

/**
 * ixgbe_tx_maxrate - callback to set the maximum per-queue bitrate
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @queue_index: Tx queue to set
 * @maxrate: desired maximum transmit bitrate
 **/
अटल पूर्णांक ixgbe_tx_maxrate(काष्ठा net_device *netdev,
			    पूर्णांक queue_index, u32 maxrate)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 bcnrc_val = ixgbe_link_mbps(adapter);

	अगर (!maxrate)
		वापस 0;

	/* Calculate the rate factor values to set */
	bcnrc_val <<= IXGBE_RTTBCNRC_RF_INT_SHIFT;
	bcnrc_val /= maxrate;

	/* clear everything but the rate factor */
	bcnrc_val &= IXGBE_RTTBCNRC_RF_INT_MASK |
	IXGBE_RTTBCNRC_RF_DEC_MASK;

	/* enable the rate scheduler */
	bcnrc_val |= IXGBE_RTTBCNRC_RS_ENA;

	IXGBE_WRITE_REG(hw, IXGBE_RTTDQSEL, queue_index);
	IXGBE_WRITE_REG(hw, IXGBE_RTTBCNRC, bcnrc_val);

	वापस 0;
पूर्ण

/**
 * ixgbe_clean_tx_irq - Reclaim resources after transmit completes
 * @q_vector: काष्ठाure containing पूर्णांकerrupt and ring inक्रमmation
 * @tx_ring: tx ring to clean
 * @napi_budget: Used to determine अगर we are in netpoll
 **/
अटल bool ixgbe_clean_tx_irq(काष्ठा ixgbe_q_vector *q_vector,
			       काष्ठा ixgbe_ring *tx_ring, पूर्णांक napi_budget)
अणु
	काष्ठा ixgbe_adapter *adapter = q_vector->adapter;
	काष्ठा ixgbe_tx_buffer *tx_buffer;
	जोड़ ixgbe_adv_tx_desc *tx_desc;
	अचिन्हित पूर्णांक total_bytes = 0, total_packets = 0, total_ipsec = 0;
	अचिन्हित पूर्णांक budget = q_vector->tx.work_limit;
	अचिन्हित पूर्णांक i = tx_ring->next_to_clean;

	अगर (test_bit(__IXGBE_DOWN, &adapter->state))
		वापस true;

	tx_buffer = &tx_ring->tx_buffer_info[i];
	tx_desc = IXGBE_TX_DESC(tx_ring, i);
	i -= tx_ring->count;

	करो अणु
		जोड़ ixgbe_adv_tx_desc *eop_desc = tx_buffer->next_to_watch;

		/* अगर next_to_watch is not set then there is no work pending */
		अगर (!eop_desc)
			अवरोध;

		/* prevent any other पढ़ोs prior to eop_desc */
		smp_rmb();

		/* अगर DD is not set pending work has not been completed */
		अगर (!(eop_desc->wb.status & cpu_to_le32(IXGBE_TXD_STAT_DD)))
			अवरोध;

		/* clear next_to_watch to prevent false hangs */
		tx_buffer->next_to_watch = शून्य;

		/* update the statistics क्रम this packet */
		total_bytes += tx_buffer->bytecount;
		total_packets += tx_buffer->gso_segs;
		अगर (tx_buffer->tx_flags & IXGBE_TX_FLAGS_IPSEC)
			total_ipsec++;

		/* मुक्त the skb */
		अगर (ring_is_xdp(tx_ring))
			xdp_वापस_frame(tx_buffer->xdpf);
		अन्यथा
			napi_consume_skb(tx_buffer->skb, napi_budget);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer, dma),
				 dma_unmap_len(tx_buffer, len),
				 DMA_TO_DEVICE);

		/* clear tx_buffer data */
		dma_unmap_len_set(tx_buffer, len, 0);

		/* unmap reमुख्यing buffers */
		जबतक (tx_desc != eop_desc) अणु
			tx_buffer++;
			tx_desc++;
			i++;
			अगर (unlikely(!i)) अणु
				i -= tx_ring->count;
				tx_buffer = tx_ring->tx_buffer_info;
				tx_desc = IXGBE_TX_DESC(tx_ring, 0);
			पूर्ण

			/* unmap any reमुख्यing paged data */
			अगर (dma_unmap_len(tx_buffer, len)) अणु
				dma_unmap_page(tx_ring->dev,
					       dma_unmap_addr(tx_buffer, dma),
					       dma_unmap_len(tx_buffer, len),
					       DMA_TO_DEVICE);
				dma_unmap_len_set(tx_buffer, len, 0);
			पूर्ण
		पूर्ण

		/* move us one more past the eop_desc क्रम start of next pkt */
		tx_buffer++;
		tx_desc++;
		i++;
		अगर (unlikely(!i)) अणु
			i -= tx_ring->count;
			tx_buffer = tx_ring->tx_buffer_info;
			tx_desc = IXGBE_TX_DESC(tx_ring, 0);
		पूर्ण

		/* issue prefetch क्रम next Tx descriptor */
		prefetch(tx_desc);

		/* update budget accounting */
		budget--;
	पूर्ण जबतक (likely(budget));

	i += tx_ring->count;
	tx_ring->next_to_clean = i;
	u64_stats_update_begin(&tx_ring->syncp);
	tx_ring->stats.bytes += total_bytes;
	tx_ring->stats.packets += total_packets;
	u64_stats_update_end(&tx_ring->syncp);
	q_vector->tx.total_bytes += total_bytes;
	q_vector->tx.total_packets += total_packets;
	adapter->tx_ipsec += total_ipsec;

	अगर (check_क्रम_tx_hang(tx_ring) && ixgbe_check_tx_hang(tx_ring)) अणु
		/* schedule immediate reset अगर we believe we hung */
		काष्ठा ixgbe_hw *hw = &adapter->hw;
		e_err(drv, "Detected Tx Unit Hang %s\n"
			"  Tx Queue             <%d>\n"
			"  TDH, TDT             <%x>, <%x>\n"
			"  next_to_use          <%x>\n"
			"  next_to_clean        <%x>\n"
			"tx_buffer_info[next_to_clean]\n"
			"  time_stamp           <%lx>\n"
			"  jiffies              <%lx>\n",
			ring_is_xdp(tx_ring) ? "(XDP)" : "",
			tx_ring->queue_index,
			IXGBE_READ_REG(hw, IXGBE_TDH(tx_ring->reg_idx)),
			IXGBE_READ_REG(hw, IXGBE_TDT(tx_ring->reg_idx)),
			tx_ring->next_to_use, i,
			tx_ring->tx_buffer_info[i].समय_stamp, jअगरfies);

		अगर (!ring_is_xdp(tx_ring))
			netअगर_stop_subqueue(tx_ring->netdev,
					    tx_ring->queue_index);

		e_info(probe,
		       "tx hang %d detected on queue %d, resetting adapter\n",
			adapter->tx_समयout_count + 1, tx_ring->queue_index);

		/* schedule immediate reset अगर we believe we hung */
		ixgbe_tx_समयout_reset(adapter);

		/* the adapter is about to reset, no poपूर्णांक in enabling stuff */
		वापस true;
	पूर्ण

	अगर (ring_is_xdp(tx_ring))
		वापस !!budget;

	netdev_tx_completed_queue(txring_txq(tx_ring),
				  total_packets, total_bytes);

#घोषणा TX_WAKE_THRESHOLD (DESC_NEEDED * 2)
	अगर (unlikely(total_packets && netअगर_carrier_ok(tx_ring->netdev) &&
		     (ixgbe_desc_unused(tx_ring) >= TX_WAKE_THRESHOLD))) अणु
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();
		अगर (__netअगर_subqueue_stopped(tx_ring->netdev,
					     tx_ring->queue_index)
		    && !test_bit(__IXGBE_DOWN, &adapter->state)) अणु
			netअगर_wake_subqueue(tx_ring->netdev,
					    tx_ring->queue_index);
			++tx_ring->tx_stats.restart_queue;
		पूर्ण
	पूर्ण

	वापस !!budget;
पूर्ण

#अगर_घोषित CONFIG_IXGBE_DCA
अटल व्योम ixgbe_update_tx_dca(काष्ठा ixgbe_adapter *adapter,
				काष्ठा ixgbe_ring *tx_ring,
				पूर्णांक cpu)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 txctrl = 0;
	u16 reg_offset;

	अगर (adapter->flags & IXGBE_FLAG_DCA_ENABLED)
		txctrl = dca3_get_tag(tx_ring->dev, cpu);

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		reg_offset = IXGBE_DCA_TXCTRL(tx_ring->reg_idx);
		अवरोध;
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
		reg_offset = IXGBE_DCA_TXCTRL_82599(tx_ring->reg_idx);
		txctrl <<= IXGBE_DCA_TXCTRL_CPUID_SHIFT_82599;
		अवरोध;
	शेष:
		/* क्रम unknown hardware करो not ग_लिखो रेजिस्टर */
		वापस;
	पूर्ण

	/*
	 * We can enable relaxed ordering क्रम पढ़ोs, but not ग_लिखोs when
	 * DCA is enabled.  This is due to a known issue in some chipsets
	 * which will cause the DCA tag to be cleared.
	 */
	txctrl |= IXGBE_DCA_TXCTRL_DESC_RRO_EN |
		  IXGBE_DCA_TXCTRL_DATA_RRO_EN |
		  IXGBE_DCA_TXCTRL_DESC_DCA_EN;

	IXGBE_WRITE_REG(hw, reg_offset, txctrl);
पूर्ण

अटल व्योम ixgbe_update_rx_dca(काष्ठा ixgbe_adapter *adapter,
				काष्ठा ixgbe_ring *rx_ring,
				पूर्णांक cpu)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 rxctrl = 0;
	u8 reg_idx = rx_ring->reg_idx;

	अगर (adapter->flags & IXGBE_FLAG_DCA_ENABLED)
		rxctrl = dca3_get_tag(rx_ring->dev, cpu);

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
		rxctrl <<= IXGBE_DCA_RXCTRL_CPUID_SHIFT_82599;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * We can enable relaxed ordering क्रम पढ़ोs, but not ग_लिखोs when
	 * DCA is enabled.  This is due to a known issue in some chipsets
	 * which will cause the DCA tag to be cleared.
	 */
	rxctrl |= IXGBE_DCA_RXCTRL_DESC_RRO_EN |
		  IXGBE_DCA_RXCTRL_DATA_DCA_EN |
		  IXGBE_DCA_RXCTRL_DESC_DCA_EN;

	IXGBE_WRITE_REG(hw, IXGBE_DCA_RXCTRL(reg_idx), rxctrl);
पूर्ण

अटल व्योम ixgbe_update_dca(काष्ठा ixgbe_q_vector *q_vector)
अणु
	काष्ठा ixgbe_adapter *adapter = q_vector->adapter;
	काष्ठा ixgbe_ring *ring;
	पूर्णांक cpu = get_cpu();

	अगर (q_vector->cpu == cpu)
		जाओ out_no_update;

	ixgbe_क्रम_each_ring(ring, q_vector->tx)
		ixgbe_update_tx_dca(adapter, ring, cpu);

	ixgbe_क्रम_each_ring(ring, q_vector->rx)
		ixgbe_update_rx_dca(adapter, ring, cpu);

	q_vector->cpu = cpu;
out_no_update:
	put_cpu();
पूर्ण

अटल व्योम ixgbe_setup_dca(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक i;

	/* always use CB2 mode, dअगरference is masked in the CB driver */
	अगर (adapter->flags & IXGBE_FLAG_DCA_ENABLED)
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_DCA_CTRL,
				IXGBE_DCA_CTRL_DCA_MODE_CB2);
	अन्यथा
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_DCA_CTRL,
				IXGBE_DCA_CTRL_DCA_DISABLE);

	क्रम (i = 0; i < adapter->num_q_vectors; i++) अणु
		adapter->q_vector[i]->cpu = -1;
		ixgbe_update_dca(adapter->q_vector[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक __ixgbe_notअगरy_dca(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा ixgbe_adapter *adapter = dev_get_drvdata(dev);
	अचिन्हित दीर्घ event = *(अचिन्हित दीर्घ *)data;

	अगर (!(adapter->flags & IXGBE_FLAG_DCA_CAPABLE))
		वापस 0;

	चयन (event) अणु
	हाल DCA_PROVIDER_ADD:
		/* अगर we're already enabled, don't करो it again */
		अगर (adapter->flags & IXGBE_FLAG_DCA_ENABLED)
			अवरोध;
		अगर (dca_add_requester(dev) == 0) अणु
			adapter->flags |= IXGBE_FLAG_DCA_ENABLED;
			IXGBE_WRITE_REG(&adapter->hw, IXGBE_DCA_CTRL,
					IXGBE_DCA_CTRL_DCA_MODE_CB2);
			अवरोध;
		पूर्ण
		fallthrough; /* DCA is disabled. */
	हाल DCA_PROVIDER_REMOVE:
		अगर (adapter->flags & IXGBE_FLAG_DCA_ENABLED) अणु
			dca_हटाओ_requester(dev);
			adapter->flags &= ~IXGBE_FLAG_DCA_ENABLED;
			IXGBE_WRITE_REG(&adapter->hw, IXGBE_DCA_CTRL,
					IXGBE_DCA_CTRL_DCA_DISABLE);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_IXGBE_DCA */

#घोषणा IXGBE_RSS_L4_TYPES_MASK \
	((1ul << IXGBE_RXDADV_RSSTYPE_IPV4_TCP) | \
	 (1ul << IXGBE_RXDADV_RSSTYPE_IPV4_UDP) | \
	 (1ul << IXGBE_RXDADV_RSSTYPE_IPV6_TCP) | \
	 (1ul << IXGBE_RXDADV_RSSTYPE_IPV6_UDP))

अटल अंतरभूत व्योम ixgbe_rx_hash(काष्ठा ixgbe_ring *ring,
				 जोड़ ixgbe_adv_rx_desc *rx_desc,
				 काष्ठा sk_buff *skb)
अणु
	u16 rss_type;

	अगर (!(ring->netdev->features & NETIF_F_RXHASH))
		वापस;

	rss_type = le16_to_cpu(rx_desc->wb.lower.lo_dword.hs_rss.pkt_info) &
		   IXGBE_RXDADV_RSSTYPE_MASK;

	अगर (!rss_type)
		वापस;

	skb_set_hash(skb, le32_to_cpu(rx_desc->wb.lower.hi_dword.rss),
		     (IXGBE_RSS_L4_TYPES_MASK & (1ul << rss_type)) ?
		     PKT_HASH_TYPE_L4 : PKT_HASH_TYPE_L3);
पूर्ण

#अगर_घोषित IXGBE_FCOE
/**
 * ixgbe_rx_is_fcoe - check the rx desc क्रम incoming pkt type
 * @ring: काष्ठाure containing ring specअगरic data
 * @rx_desc: advanced rx descriptor
 *
 * Returns : true अगर it is FCoE pkt
 */
अटल अंतरभूत bool ixgbe_rx_is_fcoe(काष्ठा ixgbe_ring *ring,
				    जोड़ ixgbe_adv_rx_desc *rx_desc)
अणु
	__le16 pkt_info = rx_desc->wb.lower.lo_dword.hs_rss.pkt_info;

	वापस test_bit(__IXGBE_RX_FCOE, &ring->state) &&
	       ((pkt_info & cpu_to_le16(IXGBE_RXDADV_PKTTYPE_ETQF_MASK)) ==
		(cpu_to_le16(IXGBE_ETQF_FILTER_FCOE <<
			     IXGBE_RXDADV_PKTTYPE_ETQF_SHIFT)));
पूर्ण

#पूर्ण_अगर /* IXGBE_FCOE */
/**
 * ixgbe_rx_checksum - indicate in skb अगर hw indicated a good cksum
 * @ring: काष्ठाure containing ring specअगरic data
 * @rx_desc: current Rx descriptor being processed
 * @skb: skb currently being received and modअगरied
 **/
अटल अंतरभूत व्योम ixgbe_rx_checksum(काष्ठा ixgbe_ring *ring,
				     जोड़ ixgbe_adv_rx_desc *rx_desc,
				     काष्ठा sk_buff *skb)
अणु
	__le16 pkt_info = rx_desc->wb.lower.lo_dword.hs_rss.pkt_info;
	bool encap_pkt = false;

	skb_checksum_none_निश्चित(skb);

	/* Rx csum disabled */
	अगर (!(ring->netdev->features & NETIF_F_RXCSUM))
		वापस;

	/* check क्रम VXLAN and Geneve packets */
	अगर (pkt_info & cpu_to_le16(IXGBE_RXDADV_PKTTYPE_VXLAN)) अणु
		encap_pkt = true;
		skb->encapsulation = 1;
	पूर्ण

	/* अगर IP and error */
	अगर (ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_IPCS) &&
	    ixgbe_test_staterr(rx_desc, IXGBE_RXDADV_ERR_IPE)) अणु
		ring->rx_stats.csum_err++;
		वापस;
	पूर्ण

	अगर (!ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_L4CS))
		वापस;

	अगर (ixgbe_test_staterr(rx_desc, IXGBE_RXDADV_ERR_TCPE)) अणु
		/*
		 * 82599 errata, UDP frames with a 0 checksum can be marked as
		 * checksum errors.
		 */
		अगर ((pkt_info & cpu_to_le16(IXGBE_RXDADV_PKTTYPE_UDP)) &&
		    test_bit(__IXGBE_RX_CSUM_UDP_ZERO_ERR, &ring->state))
			वापस;

		ring->rx_stats.csum_err++;
		वापस;
	पूर्ण

	/* It must be a TCP or UDP packet with a valid checksum */
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	अगर (encap_pkt) अणु
		अगर (!ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_OUTERIPCS))
			वापस;

		अगर (ixgbe_test_staterr(rx_desc, IXGBE_RXDADV_ERR_OUTERIPER)) अणु
			skb->ip_summed = CHECKSUM_NONE;
			वापस;
		पूर्ण
		/* If we checked the outer header let the stack know */
		skb->csum_level = 1;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक ixgbe_rx_offset(काष्ठा ixgbe_ring *rx_ring)
अणु
	वापस ring_uses_build_skb(rx_ring) ? IXGBE_SKB_PAD : 0;
पूर्ण

अटल bool ixgbe_alloc_mapped_page(काष्ठा ixgbe_ring *rx_ring,
				    काष्ठा ixgbe_rx_buffer *bi)
अणु
	काष्ठा page *page = bi->page;
	dma_addr_t dma;

	/* since we are recycling buffers we should selकरोm need to alloc */
	अगर (likely(page))
		वापस true;

	/* alloc new page क्रम storage */
	page = dev_alloc_pages(ixgbe_rx_pg_order(rx_ring));
	अगर (unlikely(!page)) अणु
		rx_ring->rx_stats.alloc_rx_page_failed++;
		वापस false;
	पूर्ण

	/* map page क्रम use */
	dma = dma_map_page_attrs(rx_ring->dev, page, 0,
				 ixgbe_rx_pg_size(rx_ring),
				 DMA_FROM_DEVICE,
				 IXGBE_RX_DMA_ATTR);

	/*
	 * अगर mapping failed मुक्त memory back to प्रणाली since
	 * there isn't much point in holding memory we can't use
	 */
	अगर (dma_mapping_error(rx_ring->dev, dma)) अणु
		__मुक्त_pages(page, ixgbe_rx_pg_order(rx_ring));

		rx_ring->rx_stats.alloc_rx_page_failed++;
		वापस false;
	पूर्ण

	bi->dma = dma;
	bi->page = page;
	bi->page_offset = rx_ring->rx_offset;
	page_ref_add(page, अच_लघु_उच्च - 1);
	bi->pagecnt_bias = अच_लघु_उच्च;
	rx_ring->rx_stats.alloc_rx_page++;

	वापस true;
पूर्ण

/**
 * ixgbe_alloc_rx_buffers - Replace used receive buffers
 * @rx_ring: ring to place buffers on
 * @cleaned_count: number of buffers to replace
 **/
व्योम ixgbe_alloc_rx_buffers(काष्ठा ixgbe_ring *rx_ring, u16 cleaned_count)
अणु
	जोड़ ixgbe_adv_rx_desc *rx_desc;
	काष्ठा ixgbe_rx_buffer *bi;
	u16 i = rx_ring->next_to_use;
	u16 bufsz;

	/* nothing to करो */
	अगर (!cleaned_count)
		वापस;

	rx_desc = IXGBE_RX_DESC(rx_ring, i);
	bi = &rx_ring->rx_buffer_info[i];
	i -= rx_ring->count;

	bufsz = ixgbe_rx_bufsz(rx_ring);

	करो अणु
		अगर (!ixgbe_alloc_mapped_page(rx_ring, bi))
			अवरोध;

		/* sync the buffer क्रम use by the device */
		dma_sync_single_range_क्रम_device(rx_ring->dev, bi->dma,
						 bi->page_offset, bufsz,
						 DMA_FROM_DEVICE);

		/*
		 * Refresh the desc even अगर buffer_addrs didn't change
		 * because each ग_लिखो-back erases this info.
		 */
		rx_desc->पढ़ो.pkt_addr = cpu_to_le64(bi->dma + bi->page_offset);

		rx_desc++;
		bi++;
		i++;
		अगर (unlikely(!i)) अणु
			rx_desc = IXGBE_RX_DESC(rx_ring, 0);
			bi = rx_ring->rx_buffer_info;
			i -= rx_ring->count;
		पूर्ण

		/* clear the length क्रम the next_to_use descriptor */
		rx_desc->wb.upper.length = 0;

		cleaned_count--;
	पूर्ण जबतक (cleaned_count);

	i += rx_ring->count;

	अगर (rx_ring->next_to_use != i) अणु
		rx_ring->next_to_use = i;

		/* update next to alloc since we have filled the ring */
		rx_ring->next_to_alloc = i;

		/* Force memory ग_लिखोs to complete beक्रमe letting h/w
		 * know there are new descriptors to fetch.  (Only
		 * applicable क्रम weak-ordered memory model archs,
		 * such as IA-64).
		 */
		wmb();
		ग_लिखोl(i, rx_ring->tail);
	पूर्ण
पूर्ण

अटल व्योम ixgbe_set_rsc_gso_size(काष्ठा ixgbe_ring *ring,
				   काष्ठा sk_buff *skb)
अणु
	u16 hdr_len = skb_headlen(skb);

	/* set gso_size to aव्योम messing up TCP MSS */
	skb_shinfo(skb)->gso_size = DIV_ROUND_UP((skb->len - hdr_len),
						 IXGBE_CB(skb)->append_cnt);
	skb_shinfo(skb)->gso_type = SKB_GSO_TCPV4;
पूर्ण

अटल व्योम ixgbe_update_rsc_stats(काष्ठा ixgbe_ring *rx_ring,
				   काष्ठा sk_buff *skb)
अणु
	/* अगर append_cnt is 0 then frame is not RSC */
	अगर (!IXGBE_CB(skb)->append_cnt)
		वापस;

	rx_ring->rx_stats.rsc_count += IXGBE_CB(skb)->append_cnt;
	rx_ring->rx_stats.rsc_flush++;

	ixgbe_set_rsc_gso_size(rx_ring, skb);

	/* gso_size is computed using append_cnt so always clear it last */
	IXGBE_CB(skb)->append_cnt = 0;
पूर्ण

/**
 * ixgbe_process_skb_fields - Populate skb header fields from Rx descriptor
 * @rx_ring: rx descriptor ring packet is being transacted on
 * @rx_desc: poपूर्णांकer to the EOP Rx descriptor
 * @skb: poपूर्णांकer to current skb being populated
 *
 * This function checks the ring, descriptor, and packet inक्रमmation in
 * order to populate the hash, checksum, VLAN, बारtamp, protocol, and
 * other fields within the skb.
 **/
व्योम ixgbe_process_skb_fields(काष्ठा ixgbe_ring *rx_ring,
			      जोड़ ixgbe_adv_rx_desc *rx_desc,
			      काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = rx_ring->netdev;
	u32 flags = rx_ring->q_vector->adapter->flags;

	ixgbe_update_rsc_stats(rx_ring, skb);

	ixgbe_rx_hash(rx_ring, rx_desc, skb);

	ixgbe_rx_checksum(rx_ring, rx_desc, skb);

	अगर (unlikely(flags & IXGBE_FLAG_RX_HWTSTAMP_ENABLED))
		ixgbe_ptp_rx_hwtstamp(rx_ring, rx_desc, skb);

	अगर ((dev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
	    ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_VP)) अणु
		u16 vid = le16_to_cpu(rx_desc->wb.upper.vlan);
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);
	पूर्ण

	अगर (ixgbe_test_staterr(rx_desc, IXGBE_RXDADV_STAT_SECP))
		ixgbe_ipsec_rx(rx_ring, rx_desc, skb);

	/* record Rx queue, or update MACVLAN statistics */
	अगर (netअगर_is_ixgbe(dev))
		skb_record_rx_queue(skb, rx_ring->queue_index);
	अन्यथा
		macvlan_count_rx(netdev_priv(dev), skb->len + ETH_HLEN, true,
				 false);

	skb->protocol = eth_type_trans(skb, dev);
पूर्ण

व्योम ixgbe_rx_skb(काष्ठा ixgbe_q_vector *q_vector,
		  काष्ठा sk_buff *skb)
अणु
	napi_gro_receive(&q_vector->napi, skb);
पूर्ण

/**
 * ixgbe_is_non_eop - process handling of non-EOP buffers
 * @rx_ring: Rx ring being processed
 * @rx_desc: Rx descriptor क्रम current buffer
 * @skb: Current socket buffer containing buffer in progress
 *
 * This function updates next to clean.  If the buffer is an EOP buffer
 * this function निकासs वापसing false, otherwise it will place the
 * sk_buff in the next buffer to be chained and वापस true indicating
 * that this is in fact a non-EOP buffer.
 **/
अटल bool ixgbe_is_non_eop(काष्ठा ixgbe_ring *rx_ring,
			     जोड़ ixgbe_adv_rx_desc *rx_desc,
			     काष्ठा sk_buff *skb)
अणु
	u32 ntc = rx_ring->next_to_clean + 1;

	/* fetch, update, and store next to clean */
	ntc = (ntc < rx_ring->count) ? ntc : 0;
	rx_ring->next_to_clean = ntc;

	prefetch(IXGBE_RX_DESC(rx_ring, ntc));

	/* update RSC append count अगर present */
	अगर (ring_is_rsc_enabled(rx_ring)) अणु
		__le32 rsc_enabled = rx_desc->wb.lower.lo_dword.data &
				     cpu_to_le32(IXGBE_RXDADV_RSCCNT_MASK);

		अगर (unlikely(rsc_enabled)) अणु
			u32 rsc_cnt = le32_to_cpu(rsc_enabled);

			rsc_cnt >>= IXGBE_RXDADV_RSCCNT_SHIFT;
			IXGBE_CB(skb)->append_cnt += rsc_cnt - 1;

			/* update ntc based on RSC value */
			ntc = le32_to_cpu(rx_desc->wb.upper.status_error);
			ntc &= IXGBE_RXDADV_NEXTP_MASK;
			ntc >>= IXGBE_RXDADV_NEXTP_SHIFT;
		पूर्ण
	पूर्ण

	/* अगर we are the last buffer then there is nothing अन्यथा to करो */
	अगर (likely(ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_EOP)))
		वापस false;

	/* place skb in next buffer to be received */
	rx_ring->rx_buffer_info[ntc].skb = skb;
	rx_ring->rx_stats.non_eop_descs++;

	वापस true;
पूर्ण

/**
 * ixgbe_pull_tail - ixgbe specअगरic version of skb_pull_tail
 * @rx_ring: rx descriptor ring packet is being transacted on
 * @skb: poपूर्णांकer to current skb being adjusted
 *
 * This function is an ixgbe specअगरic version of __pskb_pull_tail.  The
 * मुख्य dअगरference between this version and the original function is that
 * this function can make several assumptions about the state of things
 * that allow क्रम signअगरicant optimizations versus the standard function.
 * As a result we can करो things like drop a frag and मुख्यtain an accurate
 * truesize क्रम the skb.
 */
अटल व्योम ixgbe_pull_tail(काष्ठा ixgbe_ring *rx_ring,
			    काष्ठा sk_buff *skb)
अणु
	skb_frag_t *frag = &skb_shinfo(skb)->frags[0];
	अचिन्हित अक्षर *va;
	अचिन्हित पूर्णांक pull_len;

	/*
	 * it is valid to use page_address instead of kmap since we are
	 * working with pages allocated out of the lomem pool per
	 * alloc_page(GFP_ATOMIC)
	 */
	va = skb_frag_address(frag);

	/*
	 * we need the header to contain the greater of either ETH_HLEN or
	 * 60 bytes अगर the skb->len is less than 60 क्रम skb_pad.
	 */
	pull_len = eth_get_headlen(skb->dev, va, IXGBE_RX_HDR_SIZE);

	/* align pull length to size of दीर्घ to optimize स_नकल perक्रमmance */
	skb_copy_to_linear_data(skb, va, ALIGN(pull_len, माप(दीर्घ)));

	/* update all of the poपूर्णांकers */
	skb_frag_size_sub(frag, pull_len);
	skb_frag_off_add(frag, pull_len);
	skb->data_len -= pull_len;
	skb->tail += pull_len;
पूर्ण

/**
 * ixgbe_dma_sync_frag - perक्रमm DMA sync क्रम first frag of SKB
 * @rx_ring: rx descriptor ring packet is being transacted on
 * @skb: poपूर्णांकer to current skb being updated
 *
 * This function provides a basic DMA sync up क्रम the first fragment of an
 * skb.  The reason क्रम करोing this is that the first fragment cannot be
 * unmapped until we have reached the end of packet descriptor क्रम a buffer
 * chain.
 */
अटल व्योम ixgbe_dma_sync_frag(काष्ठा ixgbe_ring *rx_ring,
				काष्ठा sk_buff *skb)
अणु
	अगर (ring_uses_build_skb(rx_ring)) अणु
		अचिन्हित दीर्घ offset = (अचिन्हित दीर्घ)(skb->data) & ~PAGE_MASK;

		dma_sync_single_range_क्रम_cpu(rx_ring->dev,
					      IXGBE_CB(skb)->dma,
					      offset,
					      skb_headlen(skb),
					      DMA_FROM_DEVICE);
	पूर्ण अन्यथा अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[0];

		dma_sync_single_range_क्रम_cpu(rx_ring->dev,
					      IXGBE_CB(skb)->dma,
					      skb_frag_off(frag),
					      skb_frag_size(frag),
					      DMA_FROM_DEVICE);
	पूर्ण

	/* If the page was released, just unmap it. */
	अगर (unlikely(IXGBE_CB(skb)->page_released)) अणु
		dma_unmap_page_attrs(rx_ring->dev, IXGBE_CB(skb)->dma,
				     ixgbe_rx_pg_size(rx_ring),
				     DMA_FROM_DEVICE,
				     IXGBE_RX_DMA_ATTR);
	पूर्ण
पूर्ण

/**
 * ixgbe_cleanup_headers - Correct corrupted or empty headers
 * @rx_ring: rx descriptor ring packet is being transacted on
 * @rx_desc: poपूर्णांकer to the EOP Rx descriptor
 * @skb: poपूर्णांकer to current skb being fixed
 *
 * Check अगर the skb is valid in the XDP हाल it will be an error poपूर्णांकer.
 * Return true in this हाल to पात processing and advance to next
 * descriptor.
 *
 * Check क्रम corrupted packet headers caused by senders on the local L2
 * embedded NIC चयन not setting up their Tx Descriptors right.  These
 * should be very rare.
 *
 * Also address the हाल where we are pulling data in on pages only
 * and as such no data is present in the skb header.
 *
 * In addition अगर skb is not at least 60 bytes we need to pad it so that
 * it is large enough to qualअगरy as a valid Ethernet frame.
 *
 * Returns true अगर an error was encountered and skb was मुक्तd.
 **/
bool ixgbe_cleanup_headers(काष्ठा ixgbe_ring *rx_ring,
			   जोड़ ixgbe_adv_rx_desc *rx_desc,
			   काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *netdev = rx_ring->netdev;

	/* XDP packets use error poपूर्णांकer so पात at this poपूर्णांक */
	अगर (IS_ERR(skb))
		वापस true;

	/* Verअगरy netdev is present, and that packet करोes not have any
	 * errors that would be unacceptable to the netdev.
	 */
	अगर (!netdev ||
	    (unlikely(ixgbe_test_staterr(rx_desc,
					 IXGBE_RXDADV_ERR_FRAME_ERR_MASK) &&
	     !(netdev->features & NETIF_F_RXALL)))) अणु
		dev_kमुक्त_skb_any(skb);
		वापस true;
	पूर्ण

	/* place header in linear portion of buffer */
	अगर (!skb_headlen(skb))
		ixgbe_pull_tail(rx_ring, skb);

#अगर_घोषित IXGBE_FCOE
	/* करो not attempt to pad FCoE Frames as this will disrupt DDP */
	अगर (ixgbe_rx_is_fcoe(rx_ring, rx_desc))
		वापस false;

#पूर्ण_अगर
	/* अगर eth_skb_pad वापसs an error the skb was मुक्तd */
	अगर (eth_skb_pad(skb))
		वापस true;

	वापस false;
पूर्ण

/**
 * ixgbe_reuse_rx_page - page flip buffer and store it back on the ring
 * @rx_ring: rx descriptor ring to store buffers on
 * @old_buff: करोnor buffer to have page reused
 *
 * Synchronizes page क्रम reuse by the adapter
 **/
अटल व्योम ixgbe_reuse_rx_page(काष्ठा ixgbe_ring *rx_ring,
				काष्ठा ixgbe_rx_buffer *old_buff)
अणु
	काष्ठा ixgbe_rx_buffer *new_buff;
	u16 nta = rx_ring->next_to_alloc;

	new_buff = &rx_ring->rx_buffer_info[nta];

	/* update, and store next to alloc */
	nta++;
	rx_ring->next_to_alloc = (nta < rx_ring->count) ? nta : 0;

	/* Transfer page from old buffer to new buffer.
	 * Move each member inभागidually to aव्योम possible store
	 * क्रमwarding stalls and unnecessary copy of skb.
	 */
	new_buff->dma		= old_buff->dma;
	new_buff->page		= old_buff->page;
	new_buff->page_offset	= old_buff->page_offset;
	new_buff->pagecnt_bias	= old_buff->pagecnt_bias;
पूर्ण

अटल bool ixgbe_can_reuse_rx_page(काष्ठा ixgbe_rx_buffer *rx_buffer,
				    पूर्णांक rx_buffer_pgcnt)
अणु
	अचिन्हित पूर्णांक pagecnt_bias = rx_buffer->pagecnt_bias;
	काष्ठा page *page = rx_buffer->page;

	/* aव्योम re-using remote and pfmeदो_स्मृति pages */
	अगर (!dev_page_is_reusable(page))
		वापस false;

#अगर (PAGE_SIZE < 8192)
	/* अगर we are only owner of page we can reuse it */
	अगर (unlikely((rx_buffer_pgcnt - pagecnt_bias) > 1))
		वापस false;
#अन्यथा
	/* The last offset is a bit aggressive in that we assume the
	 * worst हाल of FCoE being enabled and using a 3K buffer.
	 * However this should have minimal impact as the 1K extra is
	 * still less than one buffer in size.
	 */
#घोषणा IXGBE_LAST_OFFSET \
	(SKB_WITH_OVERHEAD(PAGE_SIZE) - IXGBE_RXBUFFER_3K)
	अगर (rx_buffer->page_offset > IXGBE_LAST_OFFSET)
		वापस false;
#पूर्ण_अगर

	/* If we have drained the page fragment pool we need to update
	 * the pagecnt_bias and page count so that we fully restock the
	 * number of references the driver holds.
	 */
	अगर (unlikely(pagecnt_bias == 1)) अणु
		page_ref_add(page, अच_लघु_उच्च - 1);
		rx_buffer->pagecnt_bias = अच_लघु_उच्च;
	पूर्ण

	वापस true;
पूर्ण

/**
 * ixgbe_add_rx_frag - Add contents of Rx buffer to sk_buff
 * @rx_ring: rx descriptor ring to transact packets on
 * @rx_buffer: buffer containing page to add
 * @skb: sk_buff to place the data पूर्णांकo
 * @size: size of data in rx_buffer
 *
 * This function will add the data contained in rx_buffer->page to the skb.
 * This is करोne either through a direct copy अगर the data in the buffer is
 * less than the skb header size, otherwise it will just attach the page as
 * a frag to the skb.
 *
 * The function will then update the page offset अगर necessary and वापस
 * true अगर the buffer can be reused by the adapter.
 **/
अटल व्योम ixgbe_add_rx_frag(काष्ठा ixgbe_ring *rx_ring,
			      काष्ठा ixgbe_rx_buffer *rx_buffer,
			      काष्ठा sk_buff *skb,
			      अचिन्हित पूर्णांक size)
अणु
#अगर (PAGE_SIZE < 8192)
	अचिन्हित पूर्णांक truesize = ixgbe_rx_pg_size(rx_ring) / 2;
#अन्यथा
	अचिन्हित पूर्णांक truesize = rx_ring->rx_offset ?
				SKB_DATA_ALIGN(rx_ring->rx_offset + size) :
				SKB_DATA_ALIGN(size);
#पूर्ण_अगर
	skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, rx_buffer->page,
			rx_buffer->page_offset, size, truesize);
#अगर (PAGE_SIZE < 8192)
	rx_buffer->page_offset ^= truesize;
#अन्यथा
	rx_buffer->page_offset += truesize;
#पूर्ण_अगर
पूर्ण

अटल काष्ठा ixgbe_rx_buffer *ixgbe_get_rx_buffer(काष्ठा ixgbe_ring *rx_ring,
						   जोड़ ixgbe_adv_rx_desc *rx_desc,
						   काष्ठा sk_buff **skb,
						   स्थिर अचिन्हित पूर्णांक size,
						   पूर्णांक *rx_buffer_pgcnt)
अणु
	काष्ठा ixgbe_rx_buffer *rx_buffer;

	rx_buffer = &rx_ring->rx_buffer_info[rx_ring->next_to_clean];
	*rx_buffer_pgcnt =
#अगर (PAGE_SIZE < 8192)
		page_count(rx_buffer->page);
#अन्यथा
		0;
#पूर्ण_अगर
	prefetchw(rx_buffer->page);
	*skb = rx_buffer->skb;

	/* Delay unmapping of the first packet. It carries the header
	 * inक्रमmation, HW may still access the header after the ग_लिखोback.
	 * Only unmap it when EOP is reached
	 */
	अगर (!ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_EOP)) अणु
		अगर (!*skb)
			जाओ skip_sync;
	पूर्ण अन्यथा अणु
		अगर (*skb)
			ixgbe_dma_sync_frag(rx_ring, *skb);
	पूर्ण

	/* we are reusing so sync this buffer क्रम CPU use */
	dma_sync_single_range_क्रम_cpu(rx_ring->dev,
				      rx_buffer->dma,
				      rx_buffer->page_offset,
				      size,
				      DMA_FROM_DEVICE);
skip_sync:
	rx_buffer->pagecnt_bias--;

	वापस rx_buffer;
पूर्ण

अटल व्योम ixgbe_put_rx_buffer(काष्ठा ixgbe_ring *rx_ring,
				काष्ठा ixgbe_rx_buffer *rx_buffer,
				काष्ठा sk_buff *skb,
				पूर्णांक rx_buffer_pgcnt)
अणु
	अगर (ixgbe_can_reuse_rx_page(rx_buffer, rx_buffer_pgcnt)) अणु
		/* hand second half of page back to the ring */
		ixgbe_reuse_rx_page(rx_ring, rx_buffer);
	पूर्ण अन्यथा अणु
		अगर (!IS_ERR(skb) && IXGBE_CB(skb)->dma == rx_buffer->dma) अणु
			/* the page has been released from the ring */
			IXGBE_CB(skb)->page_released = true;
		पूर्ण अन्यथा अणु
			/* we are not reusing the buffer so unmap it */
			dma_unmap_page_attrs(rx_ring->dev, rx_buffer->dma,
					     ixgbe_rx_pg_size(rx_ring),
					     DMA_FROM_DEVICE,
					     IXGBE_RX_DMA_ATTR);
		पूर्ण
		__page_frag_cache_drain(rx_buffer->page,
					rx_buffer->pagecnt_bias);
	पूर्ण

	/* clear contents of rx_buffer */
	rx_buffer->page = शून्य;
	rx_buffer->skb = शून्य;
पूर्ण

अटल काष्ठा sk_buff *ixgbe_स्थिरruct_skb(काष्ठा ixgbe_ring *rx_ring,
					   काष्ठा ixgbe_rx_buffer *rx_buffer,
					   काष्ठा xdp_buff *xdp,
					   जोड़ ixgbe_adv_rx_desc *rx_desc)
अणु
	अचिन्हित पूर्णांक size = xdp->data_end - xdp->data;
#अगर (PAGE_SIZE < 8192)
	अचिन्हित पूर्णांक truesize = ixgbe_rx_pg_size(rx_ring) / 2;
#अन्यथा
	अचिन्हित पूर्णांक truesize = SKB_DATA_ALIGN(xdp->data_end -
					       xdp->data_hard_start);
#पूर्ण_अगर
	काष्ठा sk_buff *skb;

	/* prefetch first cache line of first page */
	net_prefetch(xdp->data);

	/* Note, we get here by enabling legacy-rx via:
	 *
	 *    ethtool --set-priv-flags <dev> legacy-rx on
	 *
	 * In this mode, we currently get 0 extra XDP headroom as
	 * opposed to having legacy-rx off, where we process XDP
	 * packets going to stack via ixgbe_build_skb(). The latter
	 * provides us currently with 192 bytes of headroom.
	 *
	 * For ixgbe_स्थिरruct_skb() mode it means that the
	 * xdp->data_meta will always poपूर्णांक to xdp->data, since
	 * the helper cannot expand the head. Should this ever
	 * change in future क्रम legacy-rx mode on, then lets also
	 * add xdp->data_meta handling here.
	 */

	/* allocate a skb to store the frags */
	skb = napi_alloc_skb(&rx_ring->q_vector->napi, IXGBE_RX_HDR_SIZE);
	अगर (unlikely(!skb))
		वापस शून्य;

	अगर (size > IXGBE_RX_HDR_SIZE) अणु
		अगर (!ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_EOP))
			IXGBE_CB(skb)->dma = rx_buffer->dma;

		skb_add_rx_frag(skb, 0, rx_buffer->page,
				xdp->data - page_address(rx_buffer->page),
				size, truesize);
#अगर (PAGE_SIZE < 8192)
		rx_buffer->page_offset ^= truesize;
#अन्यथा
		rx_buffer->page_offset += truesize;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		स_नकल(__skb_put(skb, size),
		       xdp->data, ALIGN(size, माप(दीर्घ)));
		rx_buffer->pagecnt_bias++;
	पूर्ण

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *ixgbe_build_skb(काष्ठा ixgbe_ring *rx_ring,
				       काष्ठा ixgbe_rx_buffer *rx_buffer,
				       काष्ठा xdp_buff *xdp,
				       जोड़ ixgbe_adv_rx_desc *rx_desc)
अणु
	अचिन्हित पूर्णांक metasize = xdp->data - xdp->data_meta;
#अगर (PAGE_SIZE < 8192)
	अचिन्हित पूर्णांक truesize = ixgbe_rx_pg_size(rx_ring) / 2;
#अन्यथा
	अचिन्हित पूर्णांक truesize = SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)) +
				SKB_DATA_ALIGN(xdp->data_end -
					       xdp->data_hard_start);
#पूर्ण_अगर
	काष्ठा sk_buff *skb;

	/* Prefetch first cache line of first page. If xdp->data_meta
	 * is unused, this poपूर्णांकs extactly as xdp->data, otherwise we
	 * likely have a consumer accessing first few bytes of meta
	 * data, and then actual data.
	 */
	net_prefetch(xdp->data_meta);

	/* build an skb to around the page buffer */
	skb = build_skb(xdp->data_hard_start, truesize);
	अगर (unlikely(!skb))
		वापस शून्य;

	/* update poपूर्णांकers within the skb to store the data */
	skb_reserve(skb, xdp->data - xdp->data_hard_start);
	__skb_put(skb, xdp->data_end - xdp->data);
	अगर (metasize)
		skb_metadata_set(skb, metasize);

	/* record DMA address अगर this is the start of a chain of buffers */
	अगर (!ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_EOP))
		IXGBE_CB(skb)->dma = rx_buffer->dma;

	/* update buffer offset */
#अगर (PAGE_SIZE < 8192)
	rx_buffer->page_offset ^= truesize;
#अन्यथा
	rx_buffer->page_offset += truesize;
#पूर्ण_अगर

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *ixgbe_run_xdp(काष्ठा ixgbe_adapter *adapter,
				     काष्ठा ixgbe_ring *rx_ring,
				     काष्ठा xdp_buff *xdp)
अणु
	पूर्णांक err, result = IXGBE_XDP_PASS;
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा xdp_frame *xdpf;
	u32 act;

	rcu_पढ़ो_lock();
	xdp_prog = READ_ONCE(rx_ring->xdp_prog);

	अगर (!xdp_prog)
		जाओ xdp_out;

	prefetchw(xdp->data_hard_start); /* xdp_frame ग_लिखो */

	act = bpf_prog_run_xdp(xdp_prog, xdp);
	चयन (act) अणु
	हाल XDP_PASS:
		अवरोध;
	हाल XDP_TX:
		xdpf = xdp_convert_buff_to_frame(xdp);
		अगर (unlikely(!xdpf))
			जाओ out_failure;
		result = ixgbe_xmit_xdp_ring(adapter, xdpf);
		अगर (result == IXGBE_XDP_CONSUMED)
			जाओ out_failure;
		अवरोध;
	हाल XDP_REसूचीECT:
		err = xdp_करो_redirect(adapter->netdev, xdp, xdp_prog);
		अगर (err)
			जाओ out_failure;
		result = IXGBE_XDP_REसूची;
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
out_failure:
		trace_xdp_exception(rx_ring->netdev, xdp_prog, act);
		fallthrough; /* handle पातs by dropping packet */
	हाल XDP_DROP:
		result = IXGBE_XDP_CONSUMED;
		अवरोध;
	पूर्ण
xdp_out:
	rcu_पढ़ो_unlock();
	वापस ERR_PTR(-result);
पूर्ण

अटल अचिन्हित पूर्णांक ixgbe_rx_frame_truesize(काष्ठा ixgbe_ring *rx_ring,
					    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक truesize;

#अगर (PAGE_SIZE < 8192)
	truesize = ixgbe_rx_pg_size(rx_ring) / 2; /* Must be घातer-of-2 */
#अन्यथा
	truesize = rx_ring->rx_offset ?
		SKB_DATA_ALIGN(rx_ring->rx_offset + size) +
		SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)) :
		SKB_DATA_ALIGN(size);
#पूर्ण_अगर
	वापस truesize;
पूर्ण

अटल व्योम ixgbe_rx_buffer_flip(काष्ठा ixgbe_ring *rx_ring,
				 काष्ठा ixgbe_rx_buffer *rx_buffer,
				 अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक truesize = ixgbe_rx_frame_truesize(rx_ring, size);
#अगर (PAGE_SIZE < 8192)
	rx_buffer->page_offset ^= truesize;
#अन्यथा
	rx_buffer->page_offset += truesize;
#पूर्ण_अगर
पूर्ण

/**
 * ixgbe_clean_rx_irq - Clean completed descriptors from Rx ring - bounce buf
 * @q_vector: काष्ठाure containing पूर्णांकerrupt and ring inक्रमmation
 * @rx_ring: rx descriptor ring to transact packets on
 * @budget: Total limit on number of packets to process
 *
 * This function provides a "bounce buffer" approach to Rx पूर्णांकerrupt
 * processing.  The advantage to this is that on प्रणालीs that have
 * expensive overhead क्रम IOMMU access this provides a means of aव्योमing
 * it by मुख्यtaining the mapping of the page to the syste.
 *
 * Returns amount of work completed
 **/
अटल पूर्णांक ixgbe_clean_rx_irq(काष्ठा ixgbe_q_vector *q_vector,
			       काष्ठा ixgbe_ring *rx_ring,
			       स्थिर पूर्णांक budget)
अणु
	अचिन्हित पूर्णांक total_rx_bytes = 0, total_rx_packets = 0, frame_sz = 0;
	काष्ठा ixgbe_adapter *adapter = q_vector->adapter;
#अगर_घोषित IXGBE_FCOE
	पूर्णांक ddp_bytes;
	अचिन्हित पूर्णांक mss = 0;
#पूर्ण_अगर /* IXGBE_FCOE */
	u16 cleaned_count = ixgbe_desc_unused(rx_ring);
	अचिन्हित पूर्णांक offset = rx_ring->rx_offset;
	अचिन्हित पूर्णांक xdp_xmit = 0;
	काष्ठा xdp_buff xdp;

	/* Frame size depend on rx_ring setup when PAGE_SIZE=4K */
#अगर (PAGE_SIZE < 8192)
	frame_sz = ixgbe_rx_frame_truesize(rx_ring, 0);
#पूर्ण_अगर
	xdp_init_buff(&xdp, frame_sz, &rx_ring->xdp_rxq);

	जबतक (likely(total_rx_packets < budget)) अणु
		जोड़ ixgbe_adv_rx_desc *rx_desc;
		काष्ठा ixgbe_rx_buffer *rx_buffer;
		काष्ठा sk_buff *skb;
		पूर्णांक rx_buffer_pgcnt;
		अचिन्हित पूर्णांक size;

		/* वापस some buffers to hardware, one at a समय is too slow */
		अगर (cleaned_count >= IXGBE_RX_BUFFER_WRITE) अणु
			ixgbe_alloc_rx_buffers(rx_ring, cleaned_count);
			cleaned_count = 0;
		पूर्ण

		rx_desc = IXGBE_RX_DESC(rx_ring, rx_ring->next_to_clean);
		size = le16_to_cpu(rx_desc->wb.upper.length);
		अगर (!size)
			अवरोध;

		/* This memory barrier is needed to keep us from पढ़ोing
		 * any other fields out of the rx_desc until we know the
		 * descriptor has been written back
		 */
		dma_rmb();

		rx_buffer = ixgbe_get_rx_buffer(rx_ring, rx_desc, &skb, size, &rx_buffer_pgcnt);

		/* retrieve a buffer from the ring */
		अगर (!skb) अणु
			अचिन्हित अक्षर *hard_start;

			hard_start = page_address(rx_buffer->page) +
				     rx_buffer->page_offset - offset;
			xdp_prepare_buff(&xdp, hard_start, offset, size, true);
#अगर (PAGE_SIZE > 4096)
			/* At larger PAGE_SIZE, frame_sz depend on len size */
			xdp.frame_sz = ixgbe_rx_frame_truesize(rx_ring, size);
#पूर्ण_अगर
			skb = ixgbe_run_xdp(adapter, rx_ring, &xdp);
		पूर्ण

		अगर (IS_ERR(skb)) अणु
			अचिन्हित पूर्णांक xdp_res = -PTR_ERR(skb);

			अगर (xdp_res & (IXGBE_XDP_TX | IXGBE_XDP_REसूची)) अणु
				xdp_xmit |= xdp_res;
				ixgbe_rx_buffer_flip(rx_ring, rx_buffer, size);
			पूर्ण अन्यथा अणु
				rx_buffer->pagecnt_bias++;
			पूर्ण
			total_rx_packets++;
			total_rx_bytes += size;
		पूर्ण अन्यथा अगर (skb) अणु
			ixgbe_add_rx_frag(rx_ring, rx_buffer, skb, size);
		पूर्ण अन्यथा अगर (ring_uses_build_skb(rx_ring)) अणु
			skb = ixgbe_build_skb(rx_ring, rx_buffer,
					      &xdp, rx_desc);
		पूर्ण अन्यथा अणु
			skb = ixgbe_स्थिरruct_skb(rx_ring, rx_buffer,
						  &xdp, rx_desc);
		पूर्ण

		/* निकास अगर we failed to retrieve a buffer */
		अगर (!skb) अणु
			rx_ring->rx_stats.alloc_rx_buff_failed++;
			rx_buffer->pagecnt_bias++;
			अवरोध;
		पूर्ण

		ixgbe_put_rx_buffer(rx_ring, rx_buffer, skb, rx_buffer_pgcnt);
		cleaned_count++;

		/* place incomplete frames back on ring क्रम completion */
		अगर (ixgbe_is_non_eop(rx_ring, rx_desc, skb))
			जारी;

		/* verअगरy the packet layout is correct */
		अगर (ixgbe_cleanup_headers(rx_ring, rx_desc, skb))
			जारी;

		/* probably a little skewed due to removing CRC */
		total_rx_bytes += skb->len;

		/* populate checksum, बारtamp, VLAN, and protocol */
		ixgbe_process_skb_fields(rx_ring, rx_desc, skb);

#अगर_घोषित IXGBE_FCOE
		/* अगर ddp, not passing to ULD unless क्रम FCP_RSP or error */
		अगर (ixgbe_rx_is_fcoe(rx_ring, rx_desc)) अणु
			ddp_bytes = ixgbe_fcoe_ddp(adapter, rx_desc, skb);
			/* include DDPed FCoE data */
			अगर (ddp_bytes > 0) अणु
				अगर (!mss) अणु
					mss = rx_ring->netdev->mtu -
						माप(काष्ठा fcoe_hdr) -
						माप(काष्ठा fc_frame_header) -
						माप(काष्ठा fcoe_crc_eof);
					अगर (mss > 512)
						mss &= ~511;
				पूर्ण
				total_rx_bytes += ddp_bytes;
				total_rx_packets += DIV_ROUND_UP(ddp_bytes,
								 mss);
			पूर्ण
			अगर (!ddp_bytes) अणु
				dev_kमुक्त_skb_any(skb);
				जारी;
			पूर्ण
		पूर्ण

#पूर्ण_अगर /* IXGBE_FCOE */
		ixgbe_rx_skb(q_vector, skb);

		/* update budget accounting */
		total_rx_packets++;
	पूर्ण

	अगर (xdp_xmit & IXGBE_XDP_REसूची)
		xdp_करो_flush_map();

	अगर (xdp_xmit & IXGBE_XDP_TX) अणु
		काष्ठा ixgbe_ring *ring = adapter->xdp_ring[smp_processor_id()];

		/* Force memory ग_लिखोs to complete beक्रमe letting h/w
		 * know there are new descriptors to fetch.
		 */
		wmb();
		ग_लिखोl(ring->next_to_use, ring->tail);
	पूर्ण

	u64_stats_update_begin(&rx_ring->syncp);
	rx_ring->stats.packets += total_rx_packets;
	rx_ring->stats.bytes += total_rx_bytes;
	u64_stats_update_end(&rx_ring->syncp);
	q_vector->rx.total_packets += total_rx_packets;
	q_vector->rx.total_bytes += total_rx_bytes;

	वापस total_rx_packets;
पूर्ण

/**
 * ixgbe_configure_msix - Configure MSI-X hardware
 * @adapter: board निजी काष्ठाure
 *
 * ixgbe_configure_msix sets up the hardware to properly generate MSI-X
 * पूर्णांकerrupts.
 **/
अटल व्योम ixgbe_configure_msix(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_q_vector *q_vector;
	पूर्णांक v_idx;
	u32 mask;

	/* Populate MSIX to EITR Select */
	अगर (adapter->num_vfs > 32) अणु
		u32 eitrsel = BIT(adapter->num_vfs - 32) - 1;
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_EITRSEL, eitrsel);
	पूर्ण

	/*
	 * Populate the IVAR table and set the ITR values to the
	 * corresponding रेजिस्टर.
	 */
	क्रम (v_idx = 0; v_idx < adapter->num_q_vectors; v_idx++) अणु
		काष्ठा ixgbe_ring *ring;
		q_vector = adapter->q_vector[v_idx];

		ixgbe_क्रम_each_ring(ring, q_vector->rx)
			ixgbe_set_ivar(adapter, 0, ring->reg_idx, v_idx);

		ixgbe_क्रम_each_ring(ring, q_vector->tx)
			ixgbe_set_ivar(adapter, 1, ring->reg_idx, v_idx);

		ixgbe_ग_लिखो_eitr(q_vector);
	पूर्ण

	चयन (adapter->hw.mac.type) अणु
	हाल ixgbe_mac_82598EB:
		ixgbe_set_ivar(adapter, -1, IXGBE_IVAR_OTHER_CAUSES_INDEX,
			       v_idx);
		अवरोध;
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		ixgbe_set_ivar(adapter, -1, 1, v_idx);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	IXGBE_WRITE_REG(&adapter->hw, IXGBE_EITR(v_idx), 1950);

	/* set up to स्वतःclear समयr, and the vectors */
	mask = IXGBE_EIMS_ENABLE_MASK;
	mask &= ~(IXGBE_EIMS_OTHER |
		  IXGBE_EIMS_MAILBOX |
		  IXGBE_EIMS_LSC);

	IXGBE_WRITE_REG(&adapter->hw, IXGBE_EIAC, mask);
पूर्ण

/**
 * ixgbe_update_itr - update the dynamic ITR value based on statistics
 * @q_vector: काष्ठाure containing पूर्णांकerrupt and ring inक्रमmation
 * @ring_container: काष्ठाure containing ring perक्रमmance data
 *
 *      Stores a new ITR value based on packets and byte
 *      counts during the last पूर्णांकerrupt.  The advantage of per पूर्णांकerrupt
 *      computation is faster updates and more accurate ITR क्रम the current
 *      traffic pattern.  Constants in this function were computed
 *      based on theoretical maximum wire speed and thresholds were set based
 *      on testing data as well as attempting to minimize response समय
 *      जबतक increasing bulk throughput.
 **/
अटल व्योम ixgbe_update_itr(काष्ठा ixgbe_q_vector *q_vector,
			     काष्ठा ixgbe_ring_container *ring_container)
अणु
	अचिन्हित पूर्णांक itr = IXGBE_ITR_ADAPTIVE_MIN_USECS |
			   IXGBE_ITR_ADAPTIVE_LATENCY;
	अचिन्हित पूर्णांक avg_wire_size, packets, bytes;
	अचिन्हित दीर्घ next_update = jअगरfies;

	/* If we करोn't have any rings just leave ourselves set क्रम maximum
	 * possible latency so we take ourselves out of the equation.
	 */
	अगर (!ring_container->ring)
		वापस;

	/* If we didn't update within up to 1 - 2 jअगरfies we can assume
	 * that either packets are coming in so slow there hasn't been
	 * any work, or that there is so much work that NAPI is dealing
	 * with पूर्णांकerrupt moderation and we करोn't need to करो anything.
	 */
	अगर (समय_after(next_update, ring_container->next_update))
		जाओ clear_counts;

	packets = ring_container->total_packets;

	/* We have no packets to actually measure against. This means
	 * either one of the other queues on this vector is active or
	 * we are a Tx queue करोing TSO with too high of an पूर्णांकerrupt rate.
	 *
	 * When this occurs just tick up our delay by the minimum value
	 * and hope that this extra delay will prevent us from being called
	 * without any work on our queue.
	 */
	अगर (!packets) अणु
		itr = (q_vector->itr >> 2) + IXGBE_ITR_ADAPTIVE_MIN_INC;
		अगर (itr > IXGBE_ITR_ADAPTIVE_MAX_USECS)
			itr = IXGBE_ITR_ADAPTIVE_MAX_USECS;
		itr += ring_container->itr & IXGBE_ITR_ADAPTIVE_LATENCY;
		जाओ clear_counts;
	पूर्ण

	bytes = ring_container->total_bytes;

	/* If packets are less than 4 or bytes are less than 9000 assume
	 * insufficient data to use bulk rate limiting approach. We are
	 * likely latency driven.
	 */
	अगर (packets < 4 && bytes < 9000) अणु
		itr = IXGBE_ITR_ADAPTIVE_LATENCY;
		जाओ adjust_by_size;
	पूर्ण

	/* Between 4 and 48 we can assume that our current पूर्णांकerrupt delay
	 * is only slightly too low. As such we should increase it by a small
	 * fixed amount.
	 */
	अगर (packets < 48) अणु
		itr = (q_vector->itr >> 2) + IXGBE_ITR_ADAPTIVE_MIN_INC;
		अगर (itr > IXGBE_ITR_ADAPTIVE_MAX_USECS)
			itr = IXGBE_ITR_ADAPTIVE_MAX_USECS;
		जाओ clear_counts;
	पूर्ण

	/* Between 48 and 96 is our "goldilocks" zone where we are working
	 * out "just right". Just report that our current ITR is good क्रम us.
	 */
	अगर (packets < 96) अणु
		itr = q_vector->itr >> 2;
		जाओ clear_counts;
	पूर्ण

	/* If packet count is 96 or greater we are likely looking at a slight
	 * overrun of the delay we want. Try halving our delay to see अगर that
	 * will cut the number of packets in half per पूर्णांकerrupt.
	 */
	अगर (packets < 256) अणु
		itr = q_vector->itr >> 3;
		अगर (itr < IXGBE_ITR_ADAPTIVE_MIN_USECS)
			itr = IXGBE_ITR_ADAPTIVE_MIN_USECS;
		जाओ clear_counts;
	पूर्ण

	/* The paths below assume we are dealing with a bulk ITR since number
	 * of packets is 256 or greater. We are just going to have to compute
	 * a value and try to bring the count under control, though क्रम smaller
	 * packet sizes there isn't much we can करो as NAPI polling will likely
	 * be kicking in sooner rather than later.
	 */
	itr = IXGBE_ITR_ADAPTIVE_BULK;

adjust_by_size:
	/* If packet counts are 256 or greater we can assume we have a gross
	 * overestimation of what the rate should be. Instead of trying to fine
	 * tune it just use the क्रमmula below to try and dial in an exact value
	 * give the current packet size of the frame.
	 */
	avg_wire_size = bytes / packets;

	/* The following is a crude approximation of:
	 *  wmem_शेष / (size + overhead) = desired_pkts_per_पूर्णांक
	 *  rate / bits_per_byte / (size + ethernet overhead) = pkt_rate
	 *  (desired_pkt_rate / pkt_rate) * usecs_per_sec = ITR value
	 *
	 * Assuming wmem_शेष is 212992 and overhead is 640 bytes per
	 * packet, (256 skb, 64 headroom, 320 shared info), we can reduce the
	 * क्रमmula करोwn to
	 *
	 *  (170 * (size + 24)) / (size + 640) = ITR
	 *
	 * We first करो some math on the packet size and then finally bitshअगरt
	 * by 8 after rounding up. We also have to account क्रम PCIe link speed
	 * dअगरference as ITR scales based on this.
	 */
	अगर (avg_wire_size <= 60) अणु
		/* Start at 50k पूर्णांकs/sec */
		avg_wire_size = 5120;
	पूर्ण अन्यथा अगर (avg_wire_size <= 316) अणु
		/* 50K पूर्णांकs/sec to 16K पूर्णांकs/sec */
		avg_wire_size *= 40;
		avg_wire_size += 2720;
	पूर्ण अन्यथा अगर (avg_wire_size <= 1084) अणु
		/* 16K पूर्णांकs/sec to 9.2K पूर्णांकs/sec */
		avg_wire_size *= 15;
		avg_wire_size += 11452;
	पूर्ण अन्यथा अगर (avg_wire_size < 1968) अणु
		/* 9.2K पूर्णांकs/sec to 8K पूर्णांकs/sec */
		avg_wire_size *= 5;
		avg_wire_size += 22420;
	पूर्ण अन्यथा अणु
		/* plateau at a limit of 8K पूर्णांकs/sec */
		avg_wire_size = 32256;
	पूर्ण

	/* If we are in low latency mode half our delay which द्विगुनs the rate
	 * to somewhere between 100K to 16K पूर्णांकs/sec
	 */
	अगर (itr & IXGBE_ITR_ADAPTIVE_LATENCY)
		avg_wire_size >>= 1;

	/* Resultant value is 256 बार larger than it needs to be. This
	 * gives us room to adjust the value as needed to either increase
	 * or decrease the value based on link speeds of 10G, 2.5G, 1G, etc.
	 *
	 * Use addition as we have alपढ़ोy recorded the new latency flag
	 * क्रम the ITR value.
	 */
	चयन (q_vector->adapter->link_speed) अणु
	हाल IXGBE_LINK_SPEED_10GB_FULL:
	हाल IXGBE_LINK_SPEED_100_FULL:
	शेष:
		itr += DIV_ROUND_UP(avg_wire_size,
				    IXGBE_ITR_ADAPTIVE_MIN_INC * 256) *
		       IXGBE_ITR_ADAPTIVE_MIN_INC;
		अवरोध;
	हाल IXGBE_LINK_SPEED_2_5GB_FULL:
	हाल IXGBE_LINK_SPEED_1GB_FULL:
	हाल IXGBE_LINK_SPEED_10_FULL:
		अगर (avg_wire_size > 8064)
			avg_wire_size = 8064;
		itr += DIV_ROUND_UP(avg_wire_size,
				    IXGBE_ITR_ADAPTIVE_MIN_INC * 64) *
		       IXGBE_ITR_ADAPTIVE_MIN_INC;
		अवरोध;
	पूर्ण

clear_counts:
	/* ग_लिखो back value */
	ring_container->itr = itr;

	/* next update should occur within next jअगरfy */
	ring_container->next_update = next_update + 1;

	ring_container->total_bytes = 0;
	ring_container->total_packets = 0;
पूर्ण

/**
 * ixgbe_ग_लिखो_eitr - ग_लिखो EITR रेजिस्टर in hardware specअगरic way
 * @q_vector: काष्ठाure containing पूर्णांकerrupt and ring inक्रमmation
 *
 * This function is made to be called by ethtool and by the driver
 * when it needs to update EITR रेजिस्टरs at runसमय.  Hardware
 * specअगरic quirks/dअगरferences are taken care of here.
 */
व्योम ixgbe_ग_लिखो_eitr(काष्ठा ixgbe_q_vector *q_vector)
अणु
	काष्ठा ixgbe_adapter *adapter = q_vector->adapter;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक v_idx = q_vector->v_idx;
	u32 itr_reg = q_vector->itr & IXGBE_MAX_EITR;

	चयन (adapter->hw.mac.type) अणु
	हाल ixgbe_mac_82598EB:
		/* must ग_लिखो high and low 16 bits to reset counter */
		itr_reg |= (itr_reg << 16);
		अवरोध;
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		/*
		 * set the WDIS bit to not clear the समयr bits and cause an
		 * immediate निश्चितion of the पूर्णांकerrupt
		 */
		itr_reg |= IXGBE_EITR_CNT_WDIS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	IXGBE_WRITE_REG(hw, IXGBE_EITR(v_idx), itr_reg);
पूर्ण

अटल व्योम ixgbe_set_itr(काष्ठा ixgbe_q_vector *q_vector)
अणु
	u32 new_itr;

	ixgbe_update_itr(q_vector, &q_vector->tx);
	ixgbe_update_itr(q_vector, &q_vector->rx);

	/* use the smallest value of new ITR delay calculations */
	new_itr = min(q_vector->rx.itr, q_vector->tx.itr);

	/* Clear latency flag अगर set, shअगरt पूर्णांकo correct position */
	new_itr &= ~IXGBE_ITR_ADAPTIVE_LATENCY;
	new_itr <<= 2;

	अगर (new_itr != q_vector->itr) अणु
		/* save the algorithm value here */
		q_vector->itr = new_itr;

		ixgbe_ग_लिखो_eitr(q_vector);
	पूर्ण
पूर्ण

/**
 * ixgbe_check_overtemp_subtask - check क्रम over temperature
 * @adapter: poपूर्णांकer to adapter
 **/
अटल व्योम ixgbe_check_overtemp_subtask(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 eicr = adapter->पूर्णांकerrupt_event;
	s32 rc;

	अगर (test_bit(__IXGBE_DOWN, &adapter->state))
		वापस;

	अगर (!(adapter->flags2 & IXGBE_FLAG2_TEMP_SENSOR_EVENT))
		वापस;

	adapter->flags2 &= ~IXGBE_FLAG2_TEMP_SENSOR_EVENT;

	चयन (hw->device_id) अणु
	हाल IXGBE_DEV_ID_82599_T3_LOM:
		/*
		 * Since the warning पूर्णांकerrupt is क्रम both ports
		 * we करोn't have to check अगर:
		 *  - This पूर्णांकerrupt wasn't क्रम our port.
		 *  - We may have missed the पूर्णांकerrupt so always have to
		 *    check अगर we  got a LSC
		 */
		अगर (!(eicr & IXGBE_EICR_GPI_SDP0_8259X) &&
		    !(eicr & IXGBE_EICR_LSC))
			वापस;

		अगर (!(eicr & IXGBE_EICR_LSC) && hw->mac.ops.check_link) अणु
			u32 speed;
			bool link_up = false;

			hw->mac.ops.check_link(hw, &speed, &link_up, false);

			अगर (link_up)
				वापस;
		पूर्ण

		/* Check अगर this is not due to overtemp */
		अगर (hw->phy.ops.check_overtemp(hw) != IXGBE_ERR_OVERTEMP)
			वापस;

		अवरोध;
	हाल IXGBE_DEV_ID_X550EM_A_1G_T:
	हाल IXGBE_DEV_ID_X550EM_A_1G_T_L:
		rc = hw->phy.ops.check_overtemp(hw);
		अगर (rc != IXGBE_ERR_OVERTEMP)
			वापस;
		अवरोध;
	शेष:
		अगर (adapter->hw.mac.type >= ixgbe_mac_X540)
			वापस;
		अगर (!(eicr & IXGBE_EICR_GPI_SDP0(hw)))
			वापस;
		अवरोध;
	पूर्ण
	e_crit(drv, "%s\n", ixgbe_overheat_msg);

	adapter->पूर्णांकerrupt_event = 0;
पूर्ण

अटल व्योम ixgbe_check_fan_failure(काष्ठा ixgbe_adapter *adapter, u32 eicr)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	अगर ((adapter->flags & IXGBE_FLAG_FAN_FAIL_CAPABLE) &&
	    (eicr & IXGBE_EICR_GPI_SDP1(hw))) अणु
		e_crit(probe, "Fan has stopped, replace the adapter\n");
		/* ग_लिखो to clear the पूर्णांकerrupt */
		IXGBE_WRITE_REG(hw, IXGBE_EICR, IXGBE_EICR_GPI_SDP1(hw));
	पूर्ण
पूर्ण

अटल व्योम ixgbe_check_overtemp_event(काष्ठा ixgbe_adapter *adapter, u32 eicr)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	अगर (!(adapter->flags2 & IXGBE_FLAG2_TEMP_SENSOR_CAPABLE))
		वापस;

	चयन (adapter->hw.mac.type) अणु
	हाल ixgbe_mac_82599EB:
		/*
		 * Need to check link state so complete overtemp check
		 * on service task
		 */
		अगर (((eicr & IXGBE_EICR_GPI_SDP0(hw)) ||
		     (eicr & IXGBE_EICR_LSC)) &&
		    (!test_bit(__IXGBE_DOWN, &adapter->state))) अणु
			adapter->पूर्णांकerrupt_event = eicr;
			adapter->flags2 |= IXGBE_FLAG2_TEMP_SENSOR_EVENT;
			ixgbe_service_event_schedule(adapter);
			वापस;
		पूर्ण
		वापस;
	हाल ixgbe_mac_x550em_a:
		अगर (eicr & IXGBE_EICR_GPI_SDP0_X550EM_a) अणु
			adapter->पूर्णांकerrupt_event = eicr;
			adapter->flags2 |= IXGBE_FLAG2_TEMP_SENSOR_EVENT;
			ixgbe_service_event_schedule(adapter);
			IXGBE_WRITE_REG(&adapter->hw, IXGBE_EIMC,
					IXGBE_EICR_GPI_SDP0_X550EM_a);
			IXGBE_WRITE_REG(&adapter->hw, IXGBE_EICR,
					IXGBE_EICR_GPI_SDP0_X550EM_a);
		पूर्ण
		वापस;
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X540:
		अगर (!(eicr & IXGBE_EICR_TS))
			वापस;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	e_crit(drv, "%s\n", ixgbe_overheat_msg);
पूर्ण

अटल अंतरभूत bool ixgbe_is_sfp(काष्ठा ixgbe_hw *hw)
अणु
	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		अगर (hw->phy.type == ixgbe_phy_nl)
			वापस true;
		वापस false;
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		चयन (hw->mac.ops.get_media_type(hw)) अणु
		हाल ixgbe_media_type_fiber:
		हाल ixgbe_media_type_fiber_qsfp:
			वापस true;
		शेष:
			वापस false;
		पूर्ण
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम ixgbe_check_sfp_event(काष्ठा ixgbe_adapter *adapter, u32 eicr)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 eicr_mask = IXGBE_EICR_GPI_SDP2(hw);

	अगर (!ixgbe_is_sfp(hw))
		वापस;

	/* Later MAC's use dअगरferent SDP */
	अगर (hw->mac.type >= ixgbe_mac_X540)
		eicr_mask = IXGBE_EICR_GPI_SDP0_X540;

	अगर (eicr & eicr_mask) अणु
		/* Clear the पूर्णांकerrupt */
		IXGBE_WRITE_REG(hw, IXGBE_EICR, eicr_mask);
		अगर (!test_bit(__IXGBE_DOWN, &adapter->state)) अणु
			adapter->flags2 |= IXGBE_FLAG2_SFP_NEEDS_RESET;
			adapter->sfp_poll_समय = 0;
			ixgbe_service_event_schedule(adapter);
		पूर्ण
	पूर्ण

	अगर (adapter->hw.mac.type == ixgbe_mac_82599EB &&
	    (eicr & IXGBE_EICR_GPI_SDP1(hw))) अणु
		/* Clear the पूर्णांकerrupt */
		IXGBE_WRITE_REG(hw, IXGBE_EICR, IXGBE_EICR_GPI_SDP1(hw));
		अगर (!test_bit(__IXGBE_DOWN, &adapter->state)) अणु
			adapter->flags |= IXGBE_FLAG_NEED_LINK_CONFIG;
			ixgbe_service_event_schedule(adapter);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ixgbe_check_lsc(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	adapter->lsc_पूर्णांक++;
	adapter->flags |= IXGBE_FLAG_NEED_LINK_UPDATE;
	adapter->link_check_समयout = jअगरfies;
	अगर (!test_bit(__IXGBE_DOWN, &adapter->state)) अणु
		IXGBE_WRITE_REG(hw, IXGBE_EIMC, IXGBE_EIMC_LSC);
		IXGBE_WRITE_FLUSH(hw);
		ixgbe_service_event_schedule(adapter);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ixgbe_irq_enable_queues(काष्ठा ixgbe_adapter *adapter,
					   u64 qmask)
अणु
	u32 mask;
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		mask = (IXGBE_EIMS_RTX_QUEUE & qmask);
		IXGBE_WRITE_REG(hw, IXGBE_EIMS, mask);
		अवरोध;
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		mask = (qmask & 0xFFFFFFFF);
		अगर (mask)
			IXGBE_WRITE_REG(hw, IXGBE_EIMS_EX(0), mask);
		mask = (qmask >> 32);
		अगर (mask)
			IXGBE_WRITE_REG(hw, IXGBE_EIMS_EX(1), mask);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	/* skip the flush */
पूर्ण

/**
 * ixgbe_irq_enable - Enable शेष पूर्णांकerrupt generation settings
 * @adapter: board निजी काष्ठाure
 * @queues: enable irqs क्रम queues
 * @flush: flush रेजिस्टर ग_लिखो
 **/
अटल अंतरभूत व्योम ixgbe_irq_enable(काष्ठा ixgbe_adapter *adapter, bool queues,
				    bool flush)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 mask = (IXGBE_EIMS_ENABLE_MASK & ~IXGBE_EIMS_RTX_QUEUE);

	/* करोn't reenable LSC जबतक रुकोing क्रम link */
	अगर (adapter->flags & IXGBE_FLAG_NEED_LINK_UPDATE)
		mask &= ~IXGBE_EIMS_LSC;

	अगर (adapter->flags2 & IXGBE_FLAG2_TEMP_SENSOR_CAPABLE)
		चयन (adapter->hw.mac.type) अणु
		हाल ixgbe_mac_82599EB:
			mask |= IXGBE_EIMS_GPI_SDP0(hw);
			अवरोध;
		हाल ixgbe_mac_X540:
		हाल ixgbe_mac_X550:
		हाल ixgbe_mac_X550EM_x:
		हाल ixgbe_mac_x550em_a:
			mask |= IXGBE_EIMS_TS;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	अगर (adapter->flags & IXGBE_FLAG_FAN_FAIL_CAPABLE)
		mask |= IXGBE_EIMS_GPI_SDP1(hw);
	चयन (adapter->hw.mac.type) अणु
	हाल ixgbe_mac_82599EB:
		mask |= IXGBE_EIMS_GPI_SDP1(hw);
		mask |= IXGBE_EIMS_GPI_SDP2(hw);
		fallthrough;
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		अगर (adapter->hw.device_id == IXGBE_DEV_ID_X550EM_X_SFP ||
		    adapter->hw.device_id == IXGBE_DEV_ID_X550EM_A_SFP ||
		    adapter->hw.device_id == IXGBE_DEV_ID_X550EM_A_SFP_N)
			mask |= IXGBE_EIMS_GPI_SDP0(&adapter->hw);
		अगर (adapter->hw.phy.type == ixgbe_phy_x550em_ext_t)
			mask |= IXGBE_EICR_GPI_SDP0_X540;
		mask |= IXGBE_EIMS_ECC;
		mask |= IXGBE_EIMS_MAILBOX;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर ((adapter->flags & IXGBE_FLAG_Fसूची_HASH_CAPABLE) &&
	    !(adapter->flags2 & IXGBE_FLAG2_Fसूची_REQUIRES_REINIT))
		mask |= IXGBE_EIMS_FLOW_सूची;

	IXGBE_WRITE_REG(&adapter->hw, IXGBE_EIMS, mask);
	अगर (queues)
		ixgbe_irq_enable_queues(adapter, ~0);
	अगर (flush)
		IXGBE_WRITE_FLUSH(&adapter->hw);
पूर्ण

अटल irqवापस_t ixgbe_msix_other(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ixgbe_adapter *adapter = data;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 eicr;

	/*
	 * Workaround क्रम Silicon errata.  Use clear-by-ग_लिखो instead
	 * of clear-by-पढ़ो.  Reading with EICS will वापस the
	 * पूर्णांकerrupt causes without clearing, which later be करोne
	 * with the ग_लिखो to EICR.
	 */
	eicr = IXGBE_READ_REG(hw, IXGBE_EICS);

	/* The lower 16bits of the EICR रेजिस्टर are क्रम the queue पूर्णांकerrupts
	 * which should be masked here in order to not accidentally clear them अगर
	 * the bits are high when ixgbe_msix_other is called. There is a race
	 * condition otherwise which results in possible perक्रमmance loss
	 * especially अगर the ixgbe_msix_other पूर्णांकerrupt is triggering
	 * consistently (as it would when PPS is turned on क्रम the X540 device)
	 */
	eicr &= 0xFFFF0000;

	IXGBE_WRITE_REG(hw, IXGBE_EICR, eicr);

	अगर (eicr & IXGBE_EICR_LSC)
		ixgbe_check_lsc(adapter);

	अगर (eicr & IXGBE_EICR_MAILBOX)
		ixgbe_msg_task(adapter);

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		अगर (hw->phy.type == ixgbe_phy_x550em_ext_t &&
		    (eicr & IXGBE_EICR_GPI_SDP0_X540)) अणु
			adapter->flags2 |= IXGBE_FLAG2_PHY_INTERRUPT;
			ixgbe_service_event_schedule(adapter);
			IXGBE_WRITE_REG(hw, IXGBE_EICR,
					IXGBE_EICR_GPI_SDP0_X540);
		पूर्ण
		अगर (eicr & IXGBE_EICR_ECC) अणु
			e_info(link, "Received ECC Err, initiating reset\n");
			set_bit(__IXGBE_RESET_REQUESTED, &adapter->state);
			ixgbe_service_event_schedule(adapter);
			IXGBE_WRITE_REG(hw, IXGBE_EICR, IXGBE_EICR_ECC);
		पूर्ण
		/* Handle Flow Director Full threshold पूर्णांकerrupt */
		अगर (eicr & IXGBE_EICR_FLOW_सूची) अणु
			पूर्णांक reinit_count = 0;
			पूर्णांक i;
			क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
				काष्ठा ixgbe_ring *ring = adapter->tx_ring[i];
				अगर (test_and_clear_bit(__IXGBE_TX_Fसूची_INIT_DONE,
						       &ring->state))
					reinit_count++;
			पूर्ण
			अगर (reinit_count) अणु
				/* no more flow director पूर्णांकerrupts until after init */
				IXGBE_WRITE_REG(hw, IXGBE_EIMC, IXGBE_EIMC_FLOW_सूची);
				adapter->flags2 |= IXGBE_FLAG2_Fसूची_REQUIRES_REINIT;
				ixgbe_service_event_schedule(adapter);
			पूर्ण
		पूर्ण
		ixgbe_check_sfp_event(adapter, eicr);
		ixgbe_check_overtemp_event(adapter, eicr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ixgbe_check_fan_failure(adapter, eicr);

	अगर (unlikely(eicr & IXGBE_EICR_TIMESYNC))
		ixgbe_ptp_check_pps_event(adapter);

	/* re-enable the original पूर्णांकerrupt state, no lsc, no queues */
	अगर (!test_bit(__IXGBE_DOWN, &adapter->state))
		ixgbe_irq_enable(adapter, false, false);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ixgbe_msix_clean_rings(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ixgbe_q_vector *q_vector = data;

	/* EIAM disabled पूर्णांकerrupts (on this vector) क्रम us */

	अगर (q_vector->rx.ring || q_vector->tx.ring)
		napi_schedule_irqoff(&q_vector->napi);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ixgbe_poll - NAPI Rx polling callback
 * @napi: काष्ठाure क्रम representing this polling device
 * @budget: how many packets driver is allowed to clean
 *
 * This function is used क्रम legacy and MSI, NAPI mode
 **/
पूर्णांक ixgbe_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ixgbe_q_vector *q_vector =
				container_of(napi, काष्ठा ixgbe_q_vector, napi);
	काष्ठा ixgbe_adapter *adapter = q_vector->adapter;
	काष्ठा ixgbe_ring *ring;
	पूर्णांक per_ring_budget, work_करोne = 0;
	bool clean_complete = true;

#अगर_घोषित CONFIG_IXGBE_DCA
	अगर (adapter->flags & IXGBE_FLAG_DCA_ENABLED)
		ixgbe_update_dca(q_vector);
#पूर्ण_अगर

	ixgbe_क्रम_each_ring(ring, q_vector->tx) अणु
		bool wd = ring->xsk_pool ?
			  ixgbe_clean_xdp_tx_irq(q_vector, ring, budget) :
			  ixgbe_clean_tx_irq(q_vector, ring, budget);

		अगर (!wd)
			clean_complete = false;
	पूर्ण

	/* Exit अगर we are called by netpoll */
	अगर (budget <= 0)
		वापस budget;

	/* attempt to distribute budget to each queue fairly, but करोn't allow
	 * the budget to go below 1 because we'll निकास polling */
	अगर (q_vector->rx.count > 1)
		per_ring_budget = max(budget/q_vector->rx.count, 1);
	अन्यथा
		per_ring_budget = budget;

	ixgbe_क्रम_each_ring(ring, q_vector->rx) अणु
		पूर्णांक cleaned = ring->xsk_pool ?
			      ixgbe_clean_rx_irq_zc(q_vector, ring,
						    per_ring_budget) :
			      ixgbe_clean_rx_irq(q_vector, ring,
						 per_ring_budget);

		work_करोne += cleaned;
		अगर (cleaned >= per_ring_budget)
			clean_complete = false;
	पूर्ण

	/* If all work not completed, वापस budget and keep polling */
	अगर (!clean_complete)
		वापस budget;

	/* all work करोne, निकास the polling mode */
	अगर (likely(napi_complete_करोne(napi, work_करोne))) अणु
		अगर (adapter->rx_itr_setting & 1)
			ixgbe_set_itr(q_vector);
		अगर (!test_bit(__IXGBE_DOWN, &adapter->state))
			ixgbe_irq_enable_queues(adapter,
						BIT_ULL(q_vector->v_idx));
	पूर्ण

	वापस min(work_करोne, budget - 1);
पूर्ण

/**
 * ixgbe_request_msix_irqs - Initialize MSI-X पूर्णांकerrupts
 * @adapter: board निजी काष्ठाure
 *
 * ixgbe_request_msix_irqs allocates MSI-X vectors and requests
 * पूर्णांकerrupts from the kernel.
 **/
अटल पूर्णांक ixgbe_request_msix_irqs(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	अचिन्हित पूर्णांक ri = 0, ti = 0;
	पूर्णांक vector, err;

	क्रम (vector = 0; vector < adapter->num_q_vectors; vector++) अणु
		काष्ठा ixgbe_q_vector *q_vector = adapter->q_vector[vector];
		काष्ठा msix_entry *entry = &adapter->msix_entries[vector];

		अगर (q_vector->tx.ring && q_vector->rx.ring) अणु
			snम_लिखो(q_vector->name, माप(q_vector->name),
				 "%s-TxRx-%u", netdev->name, ri++);
			ti++;
		पूर्ण अन्यथा अगर (q_vector->rx.ring) अणु
			snम_लिखो(q_vector->name, माप(q_vector->name),
				 "%s-rx-%u", netdev->name, ri++);
		पूर्ण अन्यथा अगर (q_vector->tx.ring) अणु
			snम_लिखो(q_vector->name, माप(q_vector->name),
				 "%s-tx-%u", netdev->name, ti++);
		पूर्ण अन्यथा अणु
			/* skip this unused q_vector */
			जारी;
		पूर्ण
		err = request_irq(entry->vector, &ixgbe_msix_clean_rings, 0,
				  q_vector->name, q_vector);
		अगर (err) अणु
			e_err(probe, "request_irq failed for MSIX interrupt "
			      "Error: %d\n", err);
			जाओ मुक्त_queue_irqs;
		पूर्ण
		/* If Flow Director is enabled, set पूर्णांकerrupt affinity */
		अगर (adapter->flags & IXGBE_FLAG_Fसूची_HASH_CAPABLE) अणु
			/* assign the mask क्रम this irq */
			irq_set_affinity_hपूर्णांक(entry->vector,
					      &q_vector->affinity_mask);
		पूर्ण
	पूर्ण

	err = request_irq(adapter->msix_entries[vector].vector,
			  ixgbe_msix_other, 0, netdev->name, adapter);
	अगर (err) अणु
		e_err(probe, "request_irq for msix_other failed: %d\n", err);
		जाओ मुक्त_queue_irqs;
	पूर्ण

	वापस 0;

मुक्त_queue_irqs:
	जबतक (vector) अणु
		vector--;
		irq_set_affinity_hपूर्णांक(adapter->msix_entries[vector].vector,
				      शून्य);
		मुक्त_irq(adapter->msix_entries[vector].vector,
			 adapter->q_vector[vector]);
	पूर्ण
	adapter->flags &= ~IXGBE_FLAG_MSIX_ENABLED;
	pci_disable_msix(adapter->pdev);
	kमुक्त(adapter->msix_entries);
	adapter->msix_entries = शून्य;
	वापस err;
पूर्ण

/**
 * ixgbe_पूर्णांकr - legacy mode Interrupt Handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a network पूर्णांकerface device काष्ठाure
 **/
अटल irqवापस_t ixgbe_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ixgbe_adapter *adapter = data;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा ixgbe_q_vector *q_vector = adapter->q_vector[0];
	u32 eicr;

	/*
	 * Workaround क्रम silicon errata #26 on 82598.  Mask the पूर्णांकerrupt
	 * beक्रमe the पढ़ो of EICR.
	 */
	IXGBE_WRITE_REG(hw, IXGBE_EIMC, IXGBE_IRQ_CLEAR_MASK);

	/* क्रम NAPI, using EIAM to स्वतः-mask tx/rx पूर्णांकerrupt bits on पढ़ो
	 * thereक्रमe no explicit पूर्णांकerrupt disable is necessary */
	eicr = IXGBE_READ_REG(hw, IXGBE_EICR);
	अगर (!eicr) अणु
		/*
		 * shared पूर्णांकerrupt alert!
		 * make sure पूर्णांकerrupts are enabled because the पढ़ो will
		 * have disabled पूर्णांकerrupts due to EIAM
		 * finish the workaround of silicon errata on 82598.  Unmask
		 * the पूर्णांकerrupt that we masked beक्रमe the EICR पढ़ो.
		 */
		अगर (!test_bit(__IXGBE_DOWN, &adapter->state))
			ixgbe_irq_enable(adapter, true, true);
		वापस IRQ_NONE;	/* Not our पूर्णांकerrupt */
	पूर्ण

	अगर (eicr & IXGBE_EICR_LSC)
		ixgbe_check_lsc(adapter);

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82599EB:
		ixgbe_check_sfp_event(adapter, eicr);
		fallthrough;
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		अगर (eicr & IXGBE_EICR_ECC) अणु
			e_info(link, "Received ECC Err, initiating reset\n");
			set_bit(__IXGBE_RESET_REQUESTED, &adapter->state);
			ixgbe_service_event_schedule(adapter);
			IXGBE_WRITE_REG(hw, IXGBE_EICR, IXGBE_EICR_ECC);
		पूर्ण
		ixgbe_check_overtemp_event(adapter, eicr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ixgbe_check_fan_failure(adapter, eicr);
	अगर (unlikely(eicr & IXGBE_EICR_TIMESYNC))
		ixgbe_ptp_check_pps_event(adapter);

	/* would disable पूर्णांकerrupts here but EIAM disabled it */
	napi_schedule_irqoff(&q_vector->napi);

	/*
	 * re-enable link(maybe) and non-queue पूर्णांकerrupts, no flush.
	 * ixgbe_poll will re-enable the queue पूर्णांकerrupts
	 */
	अगर (!test_bit(__IXGBE_DOWN, &adapter->state))
		ixgbe_irq_enable(adapter, false, false);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ixgbe_request_irq - initialize पूर्णांकerrupts
 * @adapter: board निजी काष्ठाure
 *
 * Attempts to configure पूर्णांकerrupts using the best available
 * capabilities of the hardware and kernel.
 **/
अटल पूर्णांक ixgbe_request_irq(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err;

	अगर (adapter->flags & IXGBE_FLAG_MSIX_ENABLED)
		err = ixgbe_request_msix_irqs(adapter);
	अन्यथा अगर (adapter->flags & IXGBE_FLAG_MSI_ENABLED)
		err = request_irq(adapter->pdev->irq, ixgbe_पूर्णांकr, 0,
				  netdev->name, adapter);
	अन्यथा
		err = request_irq(adapter->pdev->irq, ixgbe_पूर्णांकr, IRQF_SHARED,
				  netdev->name, adapter);

	अगर (err)
		e_err(probe, "request_irq failed, Error %d\n", err);

	वापस err;
पूर्ण

अटल व्योम ixgbe_मुक्त_irq(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक vector;

	अगर (!(adapter->flags & IXGBE_FLAG_MSIX_ENABLED)) अणु
		मुक्त_irq(adapter->pdev->irq, adapter);
		वापस;
	पूर्ण

	अगर (!adapter->msix_entries)
		वापस;

	क्रम (vector = 0; vector < adapter->num_q_vectors; vector++) अणु
		काष्ठा ixgbe_q_vector *q_vector = adapter->q_vector[vector];
		काष्ठा msix_entry *entry = &adapter->msix_entries[vector];

		/* मुक्त only the irqs that were actually requested */
		अगर (!q_vector->rx.ring && !q_vector->tx.ring)
			जारी;

		/* clear the affinity_mask in the IRQ descriptor */
		irq_set_affinity_hपूर्णांक(entry->vector, शून्य);

		मुक्त_irq(entry->vector, q_vector);
	पूर्ण

	मुक्त_irq(adapter->msix_entries[vector].vector, adapter);
पूर्ण

/**
 * ixgbe_irq_disable - Mask off पूर्णांकerrupt generation on the NIC
 * @adapter: board निजी काष्ठाure
 **/
अटल अंतरभूत व्योम ixgbe_irq_disable(काष्ठा ixgbe_adapter *adapter)
अणु
	चयन (adapter->hw.mac.type) अणु
	हाल ixgbe_mac_82598EB:
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_EIMC, ~0);
		अवरोध;
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_EIMC, 0xFFFF0000);
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_EIMC_EX(0), ~0);
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_EIMC_EX(1), ~0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	IXGBE_WRITE_FLUSH(&adapter->hw);
	अगर (adapter->flags & IXGBE_FLAG_MSIX_ENABLED) अणु
		पूर्णांक vector;

		क्रम (vector = 0; vector < adapter->num_q_vectors; vector++)
			synchronize_irq(adapter->msix_entries[vector].vector);

		synchronize_irq(adapter->msix_entries[vector++].vector);
	पूर्ण अन्यथा अणु
		synchronize_irq(adapter->pdev->irq);
	पूर्ण
पूर्ण

/**
 * ixgbe_configure_msi_and_legacy - Initialize PIN (INTA...) and MSI पूर्णांकerrupts
 * @adapter: board निजी काष्ठाure
 *
 **/
अटल व्योम ixgbe_configure_msi_and_legacy(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_q_vector *q_vector = adapter->q_vector[0];

	ixgbe_ग_लिखो_eitr(q_vector);

	ixgbe_set_ivar(adapter, 0, 0, 0);
	ixgbe_set_ivar(adapter, 1, 0, 0);

	e_info(hw, "Legacy interrupt IVAR setup done\n");
पूर्ण

/**
 * ixgbe_configure_tx_ring - Configure 8259x Tx ring after Reset
 * @adapter: board निजी काष्ठाure
 * @ring: काष्ठाure containing ring specअगरic data
 *
 * Configure the Tx descriptor ring after a reset.
 **/
व्योम ixgbe_configure_tx_ring(काष्ठा ixgbe_adapter *adapter,
			     काष्ठा ixgbe_ring *ring)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u64 tdba = ring->dma;
	पूर्णांक रुको_loop = 10;
	u32 txdctl = IXGBE_TXDCTL_ENABLE;
	u8 reg_idx = ring->reg_idx;

	ring->xsk_pool = शून्य;
	अगर (ring_is_xdp(ring))
		ring->xsk_pool = ixgbe_xsk_pool(adapter, ring);

	/* disable queue to aव्योम issues जबतक updating state */
	IXGBE_WRITE_REG(hw, IXGBE_TXDCTL(reg_idx), 0);
	IXGBE_WRITE_FLUSH(hw);

	IXGBE_WRITE_REG(hw, IXGBE_TDBAL(reg_idx),
			(tdba & DMA_BIT_MASK(32)));
	IXGBE_WRITE_REG(hw, IXGBE_TDBAH(reg_idx), (tdba >> 32));
	IXGBE_WRITE_REG(hw, IXGBE_TDLEN(reg_idx),
			ring->count * माप(जोड़ ixgbe_adv_tx_desc));
	IXGBE_WRITE_REG(hw, IXGBE_TDH(reg_idx), 0);
	IXGBE_WRITE_REG(hw, IXGBE_TDT(reg_idx), 0);
	ring->tail = adapter->io_addr + IXGBE_TDT(reg_idx);

	/*
	 * set WTHRESH to encourage burst ग_लिखोback, it should not be set
	 * higher than 1 when:
	 * - ITR is 0 as it could cause false TX hangs
	 * - ITR is set to > 100k पूर्णांक/sec and BQL is enabled
	 *
	 * In order to aव्योम issues WTHRESH + PTHRESH should always be equal
	 * to or less than the number of on chip descriptors, which is
	 * currently 40.
	 */
	अगर (!ring->q_vector || (ring->q_vector->itr < IXGBE_100K_ITR))
		txdctl |= 1u << 16;	/* WTHRESH = 1 */
	अन्यथा
		txdctl |= 8u << 16;	/* WTHRESH = 8 */

	/*
	 * Setting PTHRESH to 32 both improves perक्रमmance
	 * and aव्योमs a TX hang with DFP enabled
	 */
	txdctl |= (1u << 8) |	/* HTHRESH = 1 */
		   32;		/* PTHRESH = 32 */

	/* reinitialize flowdirector state */
	अगर (adapter->flags & IXGBE_FLAG_Fसूची_HASH_CAPABLE) अणु
		ring->atr_sample_rate = adapter->atr_sample_rate;
		ring->atr_count = 0;
		set_bit(__IXGBE_TX_Fसूची_INIT_DONE, &ring->state);
	पूर्ण अन्यथा अणु
		ring->atr_sample_rate = 0;
	पूर्ण

	/* initialize XPS */
	अगर (!test_and_set_bit(__IXGBE_TX_XPS_INIT_DONE, &ring->state)) अणु
		काष्ठा ixgbe_q_vector *q_vector = ring->q_vector;

		अगर (q_vector)
			netअगर_set_xps_queue(ring->netdev,
					    &q_vector->affinity_mask,
					    ring->queue_index);
	पूर्ण

	clear_bit(__IXGBE_HANG_CHECK_ARMED, &ring->state);

	/* reinitialize tx_buffer_info */
	स_रखो(ring->tx_buffer_info, 0,
	       माप(काष्ठा ixgbe_tx_buffer) * ring->count);

	/* enable queue */
	IXGBE_WRITE_REG(hw, IXGBE_TXDCTL(reg_idx), txdctl);

	/* TXDCTL.EN will वापस 0 on 82598 अगर link is करोwn, so skip it */
	अगर (hw->mac.type == ixgbe_mac_82598EB &&
	    !(IXGBE_READ_REG(hw, IXGBE_LINKS) & IXGBE_LINKS_UP))
		वापस;

	/* poll to verअगरy queue is enabled */
	करो अणु
		usleep_range(1000, 2000);
		txdctl = IXGBE_READ_REG(hw, IXGBE_TXDCTL(reg_idx));
	पूर्ण जबतक (--रुको_loop && !(txdctl & IXGBE_TXDCTL_ENABLE));
	अगर (!रुको_loop)
		hw_dbg(hw, "Could not enable Tx Queue %d\n", reg_idx);
पूर्ण

अटल व्योम ixgbe_setup_mtqc(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 rttdcs, mtqc;
	u8 tcs = adapter->hw_tcs;

	अगर (hw->mac.type == ixgbe_mac_82598EB)
		वापस;

	/* disable the arbiter जबतक setting MTQC */
	rttdcs = IXGBE_READ_REG(hw, IXGBE_RTTDCS);
	rttdcs |= IXGBE_RTTDCS_ARBDIS;
	IXGBE_WRITE_REG(hw, IXGBE_RTTDCS, rttdcs);

	/* set transmit pool layout */
	अगर (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) अणु
		mtqc = IXGBE_MTQC_VT_ENA;
		अगर (tcs > 4)
			mtqc |= IXGBE_MTQC_RT_ENA | IXGBE_MTQC_8TC_8TQ;
		अन्यथा अगर (tcs > 1)
			mtqc |= IXGBE_MTQC_RT_ENA | IXGBE_MTQC_4TC_4TQ;
		अन्यथा अगर (adapter->ring_feature[RING_F_VMDQ].mask ==
			 IXGBE_82599_VMDQ_4Q_MASK)
			mtqc |= IXGBE_MTQC_32VF;
		अन्यथा
			mtqc |= IXGBE_MTQC_64VF;
	पूर्ण अन्यथा अणु
		अगर (tcs > 4) अणु
			mtqc = IXGBE_MTQC_RT_ENA | IXGBE_MTQC_8TC_8TQ;
		पूर्ण अन्यथा अगर (tcs > 1) अणु
			mtqc = IXGBE_MTQC_RT_ENA | IXGBE_MTQC_4TC_4TQ;
		पूर्ण अन्यथा अणु
			u8 max_txq = adapter->num_tx_queues +
				adapter->num_xdp_queues;
			अगर (max_txq > 63)
				mtqc = IXGBE_MTQC_RT_ENA | IXGBE_MTQC_4TC_4TQ;
			अन्यथा
				mtqc = IXGBE_MTQC_64Q_1PB;
		पूर्ण
	पूर्ण

	IXGBE_WRITE_REG(hw, IXGBE_MTQC, mtqc);

	/* Enable Security TX Buffer IFG क्रम multiple pb */
	अगर (tcs) अणु
		u32 sectx = IXGBE_READ_REG(hw, IXGBE_SECTXMINIFG);
		sectx |= IXGBE_SECTX_DCB;
		IXGBE_WRITE_REG(hw, IXGBE_SECTXMINIFG, sectx);
	पूर्ण

	/* re-enable the arbiter */
	rttdcs &= ~IXGBE_RTTDCS_ARBDIS;
	IXGBE_WRITE_REG(hw, IXGBE_RTTDCS, rttdcs);
पूर्ण

/**
 * ixgbe_configure_tx - Configure 8259x Transmit Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Tx unit of the MAC after a reset.
 **/
अटल व्योम ixgbe_configure_tx(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 dmatxctl;
	u32 i;

	ixgbe_setup_mtqc(adapter);

	अगर (hw->mac.type != ixgbe_mac_82598EB) अणु
		/* DMATXCTL.EN must be beक्रमe Tx queues are enabled */
		dmatxctl = IXGBE_READ_REG(hw, IXGBE_DMATXCTL);
		dmatxctl |= IXGBE_DMATXCTL_TE;
		IXGBE_WRITE_REG(hw, IXGBE_DMATXCTL, dmatxctl);
	पूर्ण

	/* Setup the HW Tx Head and Tail descriptor poपूर्णांकers */
	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		ixgbe_configure_tx_ring(adapter, adapter->tx_ring[i]);
	क्रम (i = 0; i < adapter->num_xdp_queues; i++)
		ixgbe_configure_tx_ring(adapter, adapter->xdp_ring[i]);
पूर्ण

अटल व्योम ixgbe_enable_rx_drop(काष्ठा ixgbe_adapter *adapter,
				 काष्ठा ixgbe_ring *ring)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u8 reg_idx = ring->reg_idx;
	u32 srrctl = IXGBE_READ_REG(hw, IXGBE_SRRCTL(reg_idx));

	srrctl |= IXGBE_SRRCTL_DROP_EN;

	IXGBE_WRITE_REG(hw, IXGBE_SRRCTL(reg_idx), srrctl);
पूर्ण

अटल व्योम ixgbe_disable_rx_drop(काष्ठा ixgbe_adapter *adapter,
				  काष्ठा ixgbe_ring *ring)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u8 reg_idx = ring->reg_idx;
	u32 srrctl = IXGBE_READ_REG(hw, IXGBE_SRRCTL(reg_idx));

	srrctl &= ~IXGBE_SRRCTL_DROP_EN;

	IXGBE_WRITE_REG(hw, IXGBE_SRRCTL(reg_idx), srrctl);
पूर्ण

#अगर_घोषित CONFIG_IXGBE_DCB
व्योम ixgbe_set_rx_drop_en(काष्ठा ixgbe_adapter *adapter)
#अन्यथा
अटल व्योम ixgbe_set_rx_drop_en(काष्ठा ixgbe_adapter *adapter)
#पूर्ण_अगर
अणु
	पूर्णांक i;
	bool pfc_en = adapter->dcb_cfg.pfc_mode_enable;

	अगर (adapter->ixgbe_ieee_pfc)
		pfc_en |= !!(adapter->ixgbe_ieee_pfc->pfc_en);

	/*
	 * We should set the drop enable bit अगर:
	 *  SR-IOV is enabled
	 *   or
	 *  Number of Rx queues > 1 and flow control is disabled
	 *
	 *  This allows us to aव्योम head of line blocking क्रम security
	 *  and perक्रमmance reasons.
	 */
	अगर (adapter->num_vfs || (adapter->num_rx_queues > 1 &&
	    !(adapter->hw.fc.current_mode & ixgbe_fc_tx_छोड़ो) && !pfc_en)) अणु
		क्रम (i = 0; i < adapter->num_rx_queues; i++)
			ixgbe_enable_rx_drop(adapter, adapter->rx_ring[i]);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < adapter->num_rx_queues; i++)
			ixgbe_disable_rx_drop(adapter, adapter->rx_ring[i]);
	पूर्ण
पूर्ण

#घोषणा IXGBE_SRRCTL_BSIZEHDRSIZE_SHIFT 2

अटल व्योम ixgbe_configure_srrctl(काष्ठा ixgbe_adapter *adapter,
				   काष्ठा ixgbe_ring *rx_ring)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 srrctl;
	u8 reg_idx = rx_ring->reg_idx;

	अगर (hw->mac.type == ixgbe_mac_82598EB) अणु
		u16 mask = adapter->ring_feature[RING_F_RSS].mask;

		/*
		 * अगर VMDq is not active we must program one srrctl रेजिस्टर
		 * per RSS queue since we have enabled RDRXCTL.MVMEN
		 */
		reg_idx &= mask;
	पूर्ण

	/* configure header buffer length, needed क्रम RSC */
	srrctl = IXGBE_RX_HDR_SIZE << IXGBE_SRRCTL_BSIZEHDRSIZE_SHIFT;

	/* configure the packet buffer length */
	अगर (rx_ring->xsk_pool) अणु
		u32 xsk_buf_len = xsk_pool_get_rx_frame_size(rx_ring->xsk_pool);

		/* If the MAC support setting RXDCTL.RLPML, the
		 * SRRCTL[n].BSIZEPKT is set to PAGE_SIZE and
		 * RXDCTL.RLPML is set to the actual UMEM buffer
		 * size. If not, then we are stuck with a 1k buffer
		 * size resolution. In this हाल frames larger than
		 * the UMEM buffer size viewed in a 1k resolution will
		 * be dropped.
		 */
		अगर (hw->mac.type != ixgbe_mac_82599EB)
			srrctl |= PAGE_SIZE >> IXGBE_SRRCTL_BSIZEPKT_SHIFT;
		अन्यथा
			srrctl |= xsk_buf_len >> IXGBE_SRRCTL_BSIZEPKT_SHIFT;
	पूर्ण अन्यथा अगर (test_bit(__IXGBE_RX_3K_BUFFER, &rx_ring->state)) अणु
		srrctl |= IXGBE_RXBUFFER_3K >> IXGBE_SRRCTL_BSIZEPKT_SHIFT;
	पूर्ण अन्यथा अणु
		srrctl |= IXGBE_RXBUFFER_2K >> IXGBE_SRRCTL_BSIZEPKT_SHIFT;
	पूर्ण

	/* configure descriptor type */
	srrctl |= IXGBE_SRRCTL_DESCTYPE_ADV_ONEBUF;

	IXGBE_WRITE_REG(hw, IXGBE_SRRCTL(reg_idx), srrctl);
पूर्ण

/**
 * ixgbe_rss_indir_tbl_entries - Return RSS indirection table entries
 * @adapter: device handle
 *
 *  - 82598/82599/X540:     128
 *  - X550(non-SRIOV mode): 512
 *  - X550(SRIOV mode):     64
 */
u32 ixgbe_rss_indir_tbl_entries(काष्ठा ixgbe_adapter *adapter)
अणु
	अगर (adapter->hw.mac.type < ixgbe_mac_X550)
		वापस 128;
	अन्यथा अगर (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED)
		वापस 64;
	अन्यथा
		वापस 512;
पूर्ण

/**
 * ixgbe_store_key - Write the RSS key to HW
 * @adapter: device handle
 *
 * Write the RSS key stored in adapter.rss_key to HW.
 */
व्योम ixgbe_store_key(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++)
		IXGBE_WRITE_REG(hw, IXGBE_RSSRK(i), adapter->rss_key[i]);
पूर्ण

/**
 * ixgbe_init_rss_key - Initialize adapter RSS key
 * @adapter: device handle
 *
 * Allocates and initializes the RSS key अगर it is not allocated.
 **/
अटल अंतरभूत पूर्णांक ixgbe_init_rss_key(काष्ठा ixgbe_adapter *adapter)
अणु
	u32 *rss_key;

	अगर (!adapter->rss_key) अणु
		rss_key = kzalloc(IXGBE_RSS_KEY_SIZE, GFP_KERNEL);
		अगर (unlikely(!rss_key))
			वापस -ENOMEM;

		netdev_rss_key_fill(rss_key, IXGBE_RSS_KEY_SIZE);
		adapter->rss_key = rss_key;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ixgbe_store_reta - Write the RETA table to HW
 * @adapter: device handle
 *
 * Write the RSS redirection table stored in adapter.rss_indir_tbl[] to HW.
 */
व्योम ixgbe_store_reta(काष्ठा ixgbe_adapter *adapter)
अणु
	u32 i, reta_entries = ixgbe_rss_indir_tbl_entries(adapter);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 reta = 0;
	u32 indices_multi;
	u8 *indir_tbl = adapter->rss_indir_tbl;

	/* Fill out the redirection table as follows:
	 *  - 82598:      8 bit wide entries containing pair of 4 bit RSS
	 *    indices.
	 *  - 82599/X540: 8 bit wide entries containing 4 bit RSS index
	 *  - X550:       8 bit wide entries containing 6 bit RSS index
	 */
	अगर (adapter->hw.mac.type == ixgbe_mac_82598EB)
		indices_multi = 0x11;
	अन्यथा
		indices_multi = 0x1;

	/* Write redirection table to HW */
	क्रम (i = 0; i < reta_entries; i++) अणु
		reta |= indices_multi * indir_tbl[i] << (i & 0x3) * 8;
		अगर ((i & 3) == 3) अणु
			अगर (i < 128)
				IXGBE_WRITE_REG(hw, IXGBE_RETA(i >> 2), reta);
			अन्यथा
				IXGBE_WRITE_REG(hw, IXGBE_ERETA((i >> 2) - 32),
						reta);
			reta = 0;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ixgbe_store_vfreta - Write the RETA table to HW (x550 devices in SRIOV mode)
 * @adapter: device handle
 *
 * Write the RSS redirection table stored in adapter.rss_indir_tbl[] to HW.
 */
अटल व्योम ixgbe_store_vfreta(काष्ठा ixgbe_adapter *adapter)
अणु
	u32 i, reta_entries = ixgbe_rss_indir_tbl_entries(adapter);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 vfreta = 0;

	/* Write redirection table to HW */
	क्रम (i = 0; i < reta_entries; i++) अणु
		u16 pool = adapter->num_rx_pools;

		vfreta |= (u32)adapter->rss_indir_tbl[i] << (i & 0x3) * 8;
		अगर ((i & 3) != 3)
			जारी;

		जबतक (pool--)
			IXGBE_WRITE_REG(hw,
					IXGBE_PFVFRETA(i >> 2, VMDQ_P(pool)),
					vfreta);
		vfreta = 0;
	पूर्ण
पूर्ण

अटल व्योम ixgbe_setup_reta(काष्ठा ixgbe_adapter *adapter)
अणु
	u32 i, j;
	u32 reta_entries = ixgbe_rss_indir_tbl_entries(adapter);
	u16 rss_i = adapter->ring_feature[RING_F_RSS].indices;

	/* Program table क्रम at least 4 queues w/ SR-IOV so that VFs can
	 * make full use of any rings they may have.  We will use the
	 * PSRTYPE रेजिस्टर to control how many rings we use within the PF.
	 */
	अगर ((adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) && (rss_i < 4))
		rss_i = 4;

	/* Fill out hash function seeds */
	ixgbe_store_key(adapter);

	/* Fill out redirection table */
	स_रखो(adapter->rss_indir_tbl, 0, माप(adapter->rss_indir_tbl));

	क्रम (i = 0, j = 0; i < reta_entries; i++, j++) अणु
		अगर (j == rss_i)
			j = 0;

		adapter->rss_indir_tbl[i] = j;
	पूर्ण

	ixgbe_store_reta(adapter);
पूर्ण

अटल व्योम ixgbe_setup_vfreta(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u16 rss_i = adapter->ring_feature[RING_F_RSS].indices;
	पूर्णांक i, j;

	/* Fill out hash function seeds */
	क्रम (i = 0; i < 10; i++) अणु
		u16 pool = adapter->num_rx_pools;

		जबतक (pool--)
			IXGBE_WRITE_REG(hw,
					IXGBE_PFVFRSSRK(i, VMDQ_P(pool)),
					*(adapter->rss_key + i));
	पूर्ण

	/* Fill out the redirection table */
	क्रम (i = 0, j = 0; i < 64; i++, j++) अणु
		अगर (j == rss_i)
			j = 0;

		adapter->rss_indir_tbl[i] = j;
	पूर्ण

	ixgbe_store_vfreta(adapter);
पूर्ण

अटल व्योम ixgbe_setup_mrqc(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 mrqc = 0, rss_field = 0, vfmrqc = 0;
	u32 rxcsum;

	/* Disable indicating checksum in descriptor, enables RSS hash */
	rxcsum = IXGBE_READ_REG(hw, IXGBE_RXCSUM);
	rxcsum |= IXGBE_RXCSUM_PCSD;
	IXGBE_WRITE_REG(hw, IXGBE_RXCSUM, rxcsum);

	अगर (adapter->hw.mac.type == ixgbe_mac_82598EB) अणु
		अगर (adapter->ring_feature[RING_F_RSS].mask)
			mrqc = IXGBE_MRQC_RSSEN;
	पूर्ण अन्यथा अणु
		u8 tcs = adapter->hw_tcs;

		अगर (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) अणु
			अगर (tcs > 4)
				mrqc = IXGBE_MRQC_VMDQRT8TCEN;	/* 8 TCs */
			अन्यथा अगर (tcs > 1)
				mrqc = IXGBE_MRQC_VMDQRT4TCEN;	/* 4 TCs */
			अन्यथा अगर (adapter->ring_feature[RING_F_VMDQ].mask ==
				 IXGBE_82599_VMDQ_4Q_MASK)
				mrqc = IXGBE_MRQC_VMDQRSS32EN;
			अन्यथा
				mrqc = IXGBE_MRQC_VMDQRSS64EN;

			/* Enable L3/L4 क्रम Tx Switched packets only क्रम X550,
			 * older devices करो not support this feature
			 */
			अगर (hw->mac.type >= ixgbe_mac_X550)
				mrqc |= IXGBE_MRQC_L3L4TXSWEN;
		पूर्ण अन्यथा अणु
			अगर (tcs > 4)
				mrqc = IXGBE_MRQC_RTRSS8TCEN;
			अन्यथा अगर (tcs > 1)
				mrqc = IXGBE_MRQC_RTRSS4TCEN;
			अन्यथा
				mrqc = IXGBE_MRQC_RSSEN;
		पूर्ण
	पूर्ण

	/* Perक्रमm hash on these packet types */
	rss_field |= IXGBE_MRQC_RSS_FIELD_IPV4 |
		     IXGBE_MRQC_RSS_FIELD_IPV4_TCP |
		     IXGBE_MRQC_RSS_FIELD_IPV6 |
		     IXGBE_MRQC_RSS_FIELD_IPV6_TCP;

	अगर (adapter->flags2 & IXGBE_FLAG2_RSS_FIELD_IPV4_UDP)
		rss_field |= IXGBE_MRQC_RSS_FIELD_IPV4_UDP;
	अगर (adapter->flags2 & IXGBE_FLAG2_RSS_FIELD_IPV6_UDP)
		rss_field |= IXGBE_MRQC_RSS_FIELD_IPV6_UDP;

	अगर ((hw->mac.type >= ixgbe_mac_X550) &&
	    (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED)) अणु
		u16 pool = adapter->num_rx_pools;

		/* Enable VF RSS mode */
		mrqc |= IXGBE_MRQC_MULTIPLE_RSS;
		IXGBE_WRITE_REG(hw, IXGBE_MRQC, mrqc);

		/* Setup RSS through the VF रेजिस्टरs */
		ixgbe_setup_vfreta(adapter);
		vfmrqc = IXGBE_MRQC_RSSEN;
		vfmrqc |= rss_field;

		जबतक (pool--)
			IXGBE_WRITE_REG(hw,
					IXGBE_PFVFMRQC(VMDQ_P(pool)),
					vfmrqc);
	पूर्ण अन्यथा अणु
		ixgbe_setup_reta(adapter);
		mrqc |= rss_field;
		IXGBE_WRITE_REG(hw, IXGBE_MRQC, mrqc);
	पूर्ण
पूर्ण

/**
 * ixgbe_configure_rscctl - enable RSC क्रम the indicated ring
 * @adapter: address of board निजी काष्ठाure
 * @ring: काष्ठाure containing ring specअगरic data
 **/
अटल व्योम ixgbe_configure_rscctl(काष्ठा ixgbe_adapter *adapter,
				   काष्ठा ixgbe_ring *ring)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 rscctrl;
	u8 reg_idx = ring->reg_idx;

	अगर (!ring_is_rsc_enabled(ring))
		वापस;

	rscctrl = IXGBE_READ_REG(hw, IXGBE_RSCCTL(reg_idx));
	rscctrl |= IXGBE_RSCCTL_RSCEN;
	/*
	 * we must limit the number of descriptors so that the
	 * total size of max desc * buf_len is not greater
	 * than 65536
	 */
	rscctrl |= IXGBE_RSCCTL_MAXDESC_16;
	IXGBE_WRITE_REG(hw, IXGBE_RSCCTL(reg_idx), rscctrl);
पूर्ण

#घोषणा IXGBE_MAX_RX_DESC_POLL 10
अटल व्योम ixgbe_rx_desc_queue_enable(काष्ठा ixgbe_adapter *adapter,
				       काष्ठा ixgbe_ring *ring)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक रुको_loop = IXGBE_MAX_RX_DESC_POLL;
	u32 rxdctl;
	u8 reg_idx = ring->reg_idx;

	अगर (ixgbe_हटाओd(hw->hw_addr))
		वापस;
	/* RXDCTL.EN will वापस 0 on 82598 अगर link is करोwn, so skip it */
	अगर (hw->mac.type == ixgbe_mac_82598EB &&
	    !(IXGBE_READ_REG(hw, IXGBE_LINKS) & IXGBE_LINKS_UP))
		वापस;

	करो अणु
		usleep_range(1000, 2000);
		rxdctl = IXGBE_READ_REG(hw, IXGBE_RXDCTL(reg_idx));
	पूर्ण जबतक (--रुको_loop && !(rxdctl & IXGBE_RXDCTL_ENABLE));

	अगर (!रुको_loop) अणु
		e_err(drv, "RXDCTL.ENABLE on Rx queue %d not set within "
		      "the polling period\n", reg_idx);
	पूर्ण
पूर्ण

व्योम ixgbe_configure_rx_ring(काष्ठा ixgbe_adapter *adapter,
			     काष्ठा ixgbe_ring *ring)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	जोड़ ixgbe_adv_rx_desc *rx_desc;
	u64 rdba = ring->dma;
	u32 rxdctl;
	u8 reg_idx = ring->reg_idx;

	xdp_rxq_info_unreg_mem_model(&ring->xdp_rxq);
	ring->xsk_pool = ixgbe_xsk_pool(adapter, ring);
	अगर (ring->xsk_pool) अणु
		WARN_ON(xdp_rxq_info_reg_mem_model(&ring->xdp_rxq,
						   MEM_TYPE_XSK_BUFF_POOL,
						   शून्य));
		xsk_pool_set_rxq_info(ring->xsk_pool, &ring->xdp_rxq);
	पूर्ण अन्यथा अणु
		WARN_ON(xdp_rxq_info_reg_mem_model(&ring->xdp_rxq,
						   MEM_TYPE_PAGE_SHARED, शून्य));
	पूर्ण

	/* disable queue to aव्योम use of these values जबतक updating state */
	rxdctl = IXGBE_READ_REG(hw, IXGBE_RXDCTL(reg_idx));
	rxdctl &= ~IXGBE_RXDCTL_ENABLE;

	/* ग_लिखो value back with RXDCTL.ENABLE bit cleared */
	IXGBE_WRITE_REG(hw, IXGBE_RXDCTL(reg_idx), rxdctl);
	IXGBE_WRITE_FLUSH(hw);

	IXGBE_WRITE_REG(hw, IXGBE_RDBAL(reg_idx), (rdba & DMA_BIT_MASK(32)));
	IXGBE_WRITE_REG(hw, IXGBE_RDBAH(reg_idx), (rdba >> 32));
	IXGBE_WRITE_REG(hw, IXGBE_RDLEN(reg_idx),
			ring->count * माप(जोड़ ixgbe_adv_rx_desc));
	/* Force flushing of IXGBE_RDLEN to prevent MDD */
	IXGBE_WRITE_FLUSH(hw);

	IXGBE_WRITE_REG(hw, IXGBE_RDH(reg_idx), 0);
	IXGBE_WRITE_REG(hw, IXGBE_RDT(reg_idx), 0);
	ring->tail = adapter->io_addr + IXGBE_RDT(reg_idx);

	ixgbe_configure_srrctl(adapter, ring);
	ixgbe_configure_rscctl(adapter, ring);

	अगर (hw->mac.type == ixgbe_mac_82598EB) अणु
		/*
		 * enable cache line मित्रly hardware ग_लिखोs:
		 * PTHRESH=32 descriptors (half the पूर्णांकernal cache),
		 * this also हटाओs ugly rx_no_buffer_count increment
		 * HTHRESH=4 descriptors (to minimize latency on fetch)
		 * WTHRESH=8 burst ग_लिखोback up to two cache lines
		 */
		rxdctl &= ~0x3FFFFF;
		rxdctl |=  0x080420;
#अगर (PAGE_SIZE < 8192)
	/* RXDCTL.RLPML करोes not work on 82599 */
	पूर्ण अन्यथा अगर (hw->mac.type != ixgbe_mac_82599EB) अणु
		rxdctl &= ~(IXGBE_RXDCTL_RLPMLMASK |
			    IXGBE_RXDCTL_RLPML_EN);

		/* Limit the maximum frame size so we करोn't overrun the skb.
		 * This can happen in SRIOV mode when the MTU of the VF is
		 * higher than the MTU of the PF.
		 */
		अगर (ring_uses_build_skb(ring) &&
		    !test_bit(__IXGBE_RX_3K_BUFFER, &ring->state))
			rxdctl |= IXGBE_MAX_2K_FRAME_BUILD_SKB |
				  IXGBE_RXDCTL_RLPML_EN;
#पूर्ण_अगर
	पूर्ण

	ring->rx_offset = ixgbe_rx_offset(ring);

	अगर (ring->xsk_pool && hw->mac.type != ixgbe_mac_82599EB) अणु
		u32 xsk_buf_len = xsk_pool_get_rx_frame_size(ring->xsk_pool);

		rxdctl &= ~(IXGBE_RXDCTL_RLPMLMASK |
			    IXGBE_RXDCTL_RLPML_EN);
		rxdctl |= xsk_buf_len | IXGBE_RXDCTL_RLPML_EN;

		ring->rx_buf_len = xsk_buf_len;
	पूर्ण

	/* initialize rx_buffer_info */
	स_रखो(ring->rx_buffer_info, 0,
	       माप(काष्ठा ixgbe_rx_buffer) * ring->count);

	/* initialize Rx descriptor 0 */
	rx_desc = IXGBE_RX_DESC(ring, 0);
	rx_desc->wb.upper.length = 0;

	/* enable receive descriptor ring */
	rxdctl |= IXGBE_RXDCTL_ENABLE;
	IXGBE_WRITE_REG(hw, IXGBE_RXDCTL(reg_idx), rxdctl);

	ixgbe_rx_desc_queue_enable(adapter, ring);
	अगर (ring->xsk_pool)
		ixgbe_alloc_rx_buffers_zc(ring, ixgbe_desc_unused(ring));
	अन्यथा
		ixgbe_alloc_rx_buffers(ring, ixgbe_desc_unused(ring));
पूर्ण

अटल व्योम ixgbe_setup_psrtype(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक rss_i = adapter->ring_feature[RING_F_RSS].indices;
	u16 pool = adapter->num_rx_pools;

	/* PSRTYPE must be initialized in non 82598 adapters */
	u32 psrtype = IXGBE_PSRTYPE_TCPHDR |
		      IXGBE_PSRTYPE_UDPHDR |
		      IXGBE_PSRTYPE_IPV4HDR |
		      IXGBE_PSRTYPE_L2HDR |
		      IXGBE_PSRTYPE_IPV6HDR;

	अगर (hw->mac.type == ixgbe_mac_82598EB)
		वापस;

	अगर (rss_i > 3)
		psrtype |= 2u << 29;
	अन्यथा अगर (rss_i > 1)
		psrtype |= 1u << 29;

	जबतक (pool--)
		IXGBE_WRITE_REG(hw, IXGBE_PSRTYPE(VMDQ_P(pool)), psrtype);
पूर्ण

अटल व्योम ixgbe_configure_भवization(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u16 pool = adapter->num_rx_pools;
	u32 reg_offset, vf_shअगरt, vmolr;
	u32 gcr_ext, vmdctl;
	पूर्णांक i;

	अगर (!(adapter->flags & IXGBE_FLAG_SRIOV_ENABLED))
		वापस;

	vmdctl = IXGBE_READ_REG(hw, IXGBE_VT_CTL);
	vmdctl |= IXGBE_VMD_CTL_VMDQ_EN;
	vmdctl &= ~IXGBE_VT_CTL_POOL_MASK;
	vmdctl |= VMDQ_P(0) << IXGBE_VT_CTL_POOL_SHIFT;
	vmdctl |= IXGBE_VT_CTL_REPLEN;
	IXGBE_WRITE_REG(hw, IXGBE_VT_CTL, vmdctl);

	/* accept untagged packets until a vlan tag is
	 * specअगरically set क्रम the VMDQ queue/pool
	 */
	vmolr = IXGBE_VMOLR_AUPE;
	जबतक (pool--)
		IXGBE_WRITE_REG(hw, IXGBE_VMOLR(VMDQ_P(pool)), vmolr);

	vf_shअगरt = VMDQ_P(0) % 32;
	reg_offset = (VMDQ_P(0) >= 32) ? 1 : 0;

	/* Enable only the PF's pool क्रम Tx/Rx */
	IXGBE_WRITE_REG(hw, IXGBE_VFRE(reg_offset), GENMASK(31, vf_shअगरt));
	IXGBE_WRITE_REG(hw, IXGBE_VFRE(reg_offset ^ 1), reg_offset - 1);
	IXGBE_WRITE_REG(hw, IXGBE_VFTE(reg_offset), GENMASK(31, vf_shअगरt));
	IXGBE_WRITE_REG(hw, IXGBE_VFTE(reg_offset ^ 1), reg_offset - 1);
	अगर (adapter->bridge_mode == BRIDGE_MODE_VEB)
		IXGBE_WRITE_REG(hw, IXGBE_PFDTXGSWC, IXGBE_PFDTXGSWC_VT_LBEN);

	/* Map PF MAC address in RAR Entry 0 to first pool following VFs */
	hw->mac.ops.set_vmdq(hw, 0, VMDQ_P(0));

	/* clear VLAN promisc flag so VFTA will be updated अगर necessary */
	adapter->flags2 &= ~IXGBE_FLAG2_VLAN_PROMISC;

	/*
	 * Set up VF रेजिस्टर offsets क्रम selected VT Mode,
	 * i.e. 32 or 64 VFs क्रम SR-IOV
	 */
	चयन (adapter->ring_feature[RING_F_VMDQ].mask) अणु
	हाल IXGBE_82599_VMDQ_8Q_MASK:
		gcr_ext = IXGBE_GCR_EXT_VT_MODE_16;
		अवरोध;
	हाल IXGBE_82599_VMDQ_4Q_MASK:
		gcr_ext = IXGBE_GCR_EXT_VT_MODE_32;
		अवरोध;
	शेष:
		gcr_ext = IXGBE_GCR_EXT_VT_MODE_64;
		अवरोध;
	पूर्ण

	IXGBE_WRITE_REG(hw, IXGBE_GCR_EXT, gcr_ext);

	क्रम (i = 0; i < adapter->num_vfs; i++) अणु
		/* configure spoof checking */
		ixgbe_nकरो_set_vf_spoofchk(adapter->netdev, i,
					  adapter->vfinfo[i].spoofchk_enabled);

		/* Enable/Disable RSS query feature  */
		ixgbe_nकरो_set_vf_rss_query_en(adapter->netdev, i,
					  adapter->vfinfo[i].rss_query_enabled);
	पूर्ण
पूर्ण

अटल व्योम ixgbe_set_rx_buffer_len(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक max_frame = netdev->mtu + ETH_HLEN + ETH_FCS_LEN;
	काष्ठा ixgbe_ring *rx_ring;
	पूर्णांक i;
	u32 mhadd, hlreg0;

#अगर_घोषित IXGBE_FCOE
	/* adjust max frame to be able to करो baby jumbo क्रम FCoE */
	अगर ((adapter->flags & IXGBE_FLAG_FCOE_ENABLED) &&
	    (max_frame < IXGBE_FCOE_JUMBO_FRAME_SIZE))
		max_frame = IXGBE_FCOE_JUMBO_FRAME_SIZE;

#पूर्ण_अगर /* IXGBE_FCOE */

	/* adjust max frame to be at least the size of a standard frame */
	अगर (max_frame < (ETH_FRAME_LEN + ETH_FCS_LEN))
		max_frame = (ETH_FRAME_LEN + ETH_FCS_LEN);

	mhadd = IXGBE_READ_REG(hw, IXGBE_MHADD);
	अगर (max_frame != (mhadd >> IXGBE_MHADD_MFS_SHIFT)) अणु
		mhadd &= ~IXGBE_MHADD_MFS_MASK;
		mhadd |= max_frame << IXGBE_MHADD_MFS_SHIFT;

		IXGBE_WRITE_REG(hw, IXGBE_MHADD, mhadd);
	पूर्ण

	hlreg0 = IXGBE_READ_REG(hw, IXGBE_HLREG0);
	/* set jumbo enable since MHADD.MFS is keeping size locked at max_frame */
	hlreg0 |= IXGBE_HLREG0_JUMBOEN;
	IXGBE_WRITE_REG(hw, IXGBE_HLREG0, hlreg0);

	/*
	 * Setup the HW Rx Head and Tail Descriptor Poपूर्णांकers and
	 * the Base and Length of the Rx Descriptor Ring
	 */
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		rx_ring = adapter->rx_ring[i];

		clear_ring_rsc_enabled(rx_ring);
		clear_bit(__IXGBE_RX_3K_BUFFER, &rx_ring->state);
		clear_bit(__IXGBE_RX_BUILD_SKB_ENABLED, &rx_ring->state);

		अगर (adapter->flags2 & IXGBE_FLAG2_RSC_ENABLED)
			set_ring_rsc_enabled(rx_ring);

		अगर (test_bit(__IXGBE_RX_FCOE, &rx_ring->state))
			set_bit(__IXGBE_RX_3K_BUFFER, &rx_ring->state);

		अगर (adapter->flags2 & IXGBE_FLAG2_RX_LEGACY)
			जारी;

		set_bit(__IXGBE_RX_BUILD_SKB_ENABLED, &rx_ring->state);

#अगर (PAGE_SIZE < 8192)
		अगर (adapter->flags2 & IXGBE_FLAG2_RSC_ENABLED)
			set_bit(__IXGBE_RX_3K_BUFFER, &rx_ring->state);

		अगर (IXGBE_2K_TOO_SMALL_WITH_PADDING ||
		    (max_frame > (ETH_FRAME_LEN + ETH_FCS_LEN)))
			set_bit(__IXGBE_RX_3K_BUFFER, &rx_ring->state);
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल व्योम ixgbe_setup_rdrxctl(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 rdrxctl = IXGBE_READ_REG(hw, IXGBE_RDRXCTL);

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		/*
		 * For VMDq support of dअगरferent descriptor types or
		 * buffer sizes through the use of multiple SRRCTL
		 * रेजिस्टरs, RDRXCTL.MVMEN must be set to 1
		 *
		 * also, the manual करोesn't mention it clearly but DCA hपूर्णांकs
		 * will only use queue 0's tags unless this bit is set.  Side
		 * effects of setting this bit are only that SRRCTL must be
		 * fully programmed [0..15]
		 */
		rdrxctl |= IXGBE_RDRXCTL_MVMEN;
		अवरोध;
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		अगर (adapter->num_vfs)
			rdrxctl |= IXGBE_RDRXCTL_PSP;
		fallthrough;
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
		/* Disable RSC क्रम ACK packets */
		IXGBE_WRITE_REG(hw, IXGBE_RSCDBU,
		   (IXGBE_RSCDBU_RSCACKDIS | IXGBE_READ_REG(hw, IXGBE_RSCDBU)));
		rdrxctl &= ~IXGBE_RDRXCTL_RSCFRSTSIZE;
		/* hardware requires some bits to be set by शेष */
		rdrxctl |= (IXGBE_RDRXCTL_RSCACKC | IXGBE_RDRXCTL_FCOE_WRFIX);
		rdrxctl |= IXGBE_RDRXCTL_CRCSTRIP;
		अवरोध;
	शेष:
		/* We should करो nothing since we करोn't know this hardware */
		वापस;
	पूर्ण

	IXGBE_WRITE_REG(hw, IXGBE_RDRXCTL, rdrxctl);
पूर्ण

/**
 * ixgbe_configure_rx - Configure 8259x Receive Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Rx unit of the MAC after a reset.
 **/
अटल व्योम ixgbe_configure_rx(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i;
	u32 rxctrl, rfctl;

	/* disable receives जबतक setting up the descriptors */
	hw->mac.ops.disable_rx(hw);

	ixgbe_setup_psrtype(adapter);
	ixgbe_setup_rdrxctl(adapter);

	/* RSC Setup */
	rfctl = IXGBE_READ_REG(hw, IXGBE_RFCTL);
	rfctl &= ~IXGBE_RFCTL_RSC_DIS;
	अगर (!(adapter->flags2 & IXGBE_FLAG2_RSC_ENABLED))
		rfctl |= IXGBE_RFCTL_RSC_DIS;

	/* disable NFS filtering */
	rfctl |= (IXGBE_RFCTL_NFSW_DIS | IXGBE_RFCTL_NFSR_DIS);
	IXGBE_WRITE_REG(hw, IXGBE_RFCTL, rfctl);

	/* Program रेजिस्टरs क्रम the distribution of queues */
	ixgbe_setup_mrqc(adapter);

	/* set_rx_buffer_len must be called beक्रमe ring initialization */
	ixgbe_set_rx_buffer_len(adapter);

	/*
	 * Setup the HW Rx Head and Tail Descriptor Poपूर्णांकers and
	 * the Base and Length of the Rx Descriptor Ring
	 */
	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		ixgbe_configure_rx_ring(adapter, adapter->rx_ring[i]);

	rxctrl = IXGBE_READ_REG(hw, IXGBE_RXCTRL);
	/* disable drop enable क्रम 82598 parts */
	अगर (hw->mac.type == ixgbe_mac_82598EB)
		rxctrl |= IXGBE_RXCTRL_DMBYPS;

	/* enable all receives */
	rxctrl |= IXGBE_RXCTRL_RXEN;
	hw->mac.ops.enable_rx_dma(hw, rxctrl);
पूर्ण

अटल पूर्णांक ixgbe_vlan_rx_add_vid(काष्ठा net_device *netdev,
				 __be16 proto, u16 vid)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	/* add VID to filter table */
	अगर (!vid || !(adapter->flags2 & IXGBE_FLAG2_VLAN_PROMISC))
		hw->mac.ops.set_vfta(&adapter->hw, vid, VMDQ_P(0), true, !!vid);

	set_bit(vid, adapter->active_vlans);

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_find_vlvf_entry(काष्ठा ixgbe_hw *hw, u32 vlan)
अणु
	u32 vlvf;
	पूर्णांक idx;

	/* लघु cut the special हाल */
	अगर (vlan == 0)
		वापस 0;

	/* Search क्रम the vlan id in the VLVF entries */
	क्रम (idx = IXGBE_VLVF_ENTRIES; --idx;) अणु
		vlvf = IXGBE_READ_REG(hw, IXGBE_VLVF(idx));
		अगर ((vlvf & VLAN_VID_MASK) == vlan)
			अवरोध;
	पूर्ण

	वापस idx;
पूर्ण

व्योम ixgbe_update_pf_promisc_vlvf(काष्ठा ixgbe_adapter *adapter, u32 vid)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 bits, word;
	पूर्णांक idx;

	idx = ixgbe_find_vlvf_entry(hw, vid);
	अगर (!idx)
		वापस;

	/* See अगर any other pools are set क्रम this VLAN filter
	 * entry other than the PF.
	 */
	word = idx * 2 + (VMDQ_P(0) / 32);
	bits = ~BIT(VMDQ_P(0) % 32);
	bits &= IXGBE_READ_REG(hw, IXGBE_VLVFB(word));

	/* Disable the filter so this falls पूर्णांकo the शेष pool. */
	अगर (!bits && !IXGBE_READ_REG(hw, IXGBE_VLVFB(word ^ 1))) अणु
		अगर (!(adapter->flags2 & IXGBE_FLAG2_VLAN_PROMISC))
			IXGBE_WRITE_REG(hw, IXGBE_VLVFB(word), 0);
		IXGBE_WRITE_REG(hw, IXGBE_VLVF(idx), 0);
	पूर्ण
पूर्ण

अटल पूर्णांक ixgbe_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
				  __be16 proto, u16 vid)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	/* हटाओ VID from filter table */
	अगर (vid && !(adapter->flags2 & IXGBE_FLAG2_VLAN_PROMISC))
		hw->mac.ops.set_vfta(hw, vid, VMDQ_P(0), false, true);

	clear_bit(vid, adapter->active_vlans);

	वापस 0;
पूर्ण

/**
 * ixgbe_vlan_strip_disable - helper to disable hw vlan stripping
 * @adapter: driver data
 */
अटल व्योम ixgbe_vlan_strip_disable(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 vlnctrl;
	पूर्णांक i, j;

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		vlnctrl = IXGBE_READ_REG(hw, IXGBE_VLNCTRL);
		vlnctrl &= ~IXGBE_VLNCTRL_VME;
		IXGBE_WRITE_REG(hw, IXGBE_VLNCTRL, vlnctrl);
		अवरोध;
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			काष्ठा ixgbe_ring *ring = adapter->rx_ring[i];

			अगर (!netअगर_is_ixgbe(ring->netdev))
				जारी;

			j = ring->reg_idx;
			vlnctrl = IXGBE_READ_REG(hw, IXGBE_RXDCTL(j));
			vlnctrl &= ~IXGBE_RXDCTL_VME;
			IXGBE_WRITE_REG(hw, IXGBE_RXDCTL(j), vlnctrl);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ixgbe_vlan_strip_enable - helper to enable hw vlan stripping
 * @adapter: driver data
 */
अटल व्योम ixgbe_vlan_strip_enable(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 vlnctrl;
	पूर्णांक i, j;

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		vlnctrl = IXGBE_READ_REG(hw, IXGBE_VLNCTRL);
		vlnctrl |= IXGBE_VLNCTRL_VME;
		IXGBE_WRITE_REG(hw, IXGBE_VLNCTRL, vlnctrl);
		अवरोध;
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			काष्ठा ixgbe_ring *ring = adapter->rx_ring[i];

			अगर (!netअगर_is_ixgbe(ring->netdev))
				जारी;

			j = ring->reg_idx;
			vlnctrl = IXGBE_READ_REG(hw, IXGBE_RXDCTL(j));
			vlnctrl |= IXGBE_RXDCTL_VME;
			IXGBE_WRITE_REG(hw, IXGBE_RXDCTL(j), vlnctrl);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ixgbe_vlan_promisc_enable(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 vlnctrl, i;

	vlnctrl = IXGBE_READ_REG(hw, IXGBE_VLNCTRL);

	अगर (adapter->flags & IXGBE_FLAG_VMDQ_ENABLED) अणु
	/* For VMDq and SR-IOV we must leave VLAN filtering enabled */
		vlnctrl |= IXGBE_VLNCTRL_VFE;
		IXGBE_WRITE_REG(hw, IXGBE_VLNCTRL, vlnctrl);
	पूर्ण अन्यथा अणु
		vlnctrl &= ~IXGBE_VLNCTRL_VFE;
		IXGBE_WRITE_REG(hw, IXGBE_VLNCTRL, vlnctrl);
		वापस;
	पूर्ण

	/* Nothing to करो क्रम 82598 */
	अगर (hw->mac.type == ixgbe_mac_82598EB)
		वापस;

	/* We are alपढ़ोy in VLAN promisc, nothing to करो */
	अगर (adapter->flags2 & IXGBE_FLAG2_VLAN_PROMISC)
		वापस;

	/* Set flag so we करोn't reकरो unnecessary work */
	adapter->flags2 |= IXGBE_FLAG2_VLAN_PROMISC;

	/* Add PF to all active pools */
	क्रम (i = IXGBE_VLVF_ENTRIES; --i;) अणु
		u32 reg_offset = IXGBE_VLVFB(i * 2 + VMDQ_P(0) / 32);
		u32 vlvfb = IXGBE_READ_REG(hw, reg_offset);

		vlvfb |= BIT(VMDQ_P(0) % 32);
		IXGBE_WRITE_REG(hw, reg_offset, vlvfb);
	पूर्ण

	/* Set all bits in the VLAN filter table array */
	क्रम (i = hw->mac.vft_size; i--;)
		IXGBE_WRITE_REG(hw, IXGBE_VFTA(i), ~0U);
पूर्ण

#घोषणा VFTA_BLOCK_SIZE 8
अटल व्योम ixgbe_scrub_vfta(काष्ठा ixgbe_adapter *adapter, u32 vfta_offset)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 vfta[VFTA_BLOCK_SIZE] = अणु 0 पूर्ण;
	u32 vid_start = vfta_offset * 32;
	u32 vid_end = vid_start + (VFTA_BLOCK_SIZE * 32);
	u32 i, vid, word, bits;

	क्रम (i = IXGBE_VLVF_ENTRIES; --i;) अणु
		u32 vlvf = IXGBE_READ_REG(hw, IXGBE_VLVF(i));

		/* pull VLAN ID from VLVF */
		vid = vlvf & VLAN_VID_MASK;

		/* only concern outselves with a certain range */
		अगर (vid < vid_start || vid >= vid_end)
			जारी;

		अगर (vlvf) अणु
			/* record VLAN ID in VFTA */
			vfta[(vid - vid_start) / 32] |= BIT(vid % 32);

			/* अगर PF is part of this then जारी */
			अगर (test_bit(vid, adapter->active_vlans))
				जारी;
		पूर्ण

		/* हटाओ PF from the pool */
		word = i * 2 + VMDQ_P(0) / 32;
		bits = ~BIT(VMDQ_P(0) % 32);
		bits &= IXGBE_READ_REG(hw, IXGBE_VLVFB(word));
		IXGBE_WRITE_REG(hw, IXGBE_VLVFB(word), bits);
	पूर्ण

	/* extract values from active_vlans and ग_लिखो back to VFTA */
	क्रम (i = VFTA_BLOCK_SIZE; i--;) अणु
		vid = (vfta_offset + i) * 32;
		word = vid / BITS_PER_LONG;
		bits = vid % BITS_PER_LONG;

		vfta[i] |= adapter->active_vlans[word] >> bits;

		IXGBE_WRITE_REG(hw, IXGBE_VFTA(vfta_offset + i), vfta[i]);
	पूर्ण
पूर्ण

अटल व्योम ixgbe_vlan_promisc_disable(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 vlnctrl, i;

	/* Set VLAN filtering to enabled */
	vlnctrl = IXGBE_READ_REG(hw, IXGBE_VLNCTRL);
	vlnctrl |= IXGBE_VLNCTRL_VFE;
	IXGBE_WRITE_REG(hw, IXGBE_VLNCTRL, vlnctrl);

	अगर (!(adapter->flags & IXGBE_FLAG_VMDQ_ENABLED) ||
	    hw->mac.type == ixgbe_mac_82598EB)
		वापस;

	/* We are not in VLAN promisc, nothing to करो */
	अगर (!(adapter->flags2 & IXGBE_FLAG2_VLAN_PROMISC))
		वापस;

	/* Set flag so we करोn't reकरो unnecessary work */
	adapter->flags2 &= ~IXGBE_FLAG2_VLAN_PROMISC;

	क्रम (i = 0; i < hw->mac.vft_size; i += VFTA_BLOCK_SIZE)
		ixgbe_scrub_vfta(adapter, i);
पूर्ण

अटल व्योम ixgbe_restore_vlan(काष्ठा ixgbe_adapter *adapter)
अणु
	u16 vid = 1;

	ixgbe_vlan_rx_add_vid(adapter->netdev, htons(ETH_P_8021Q), 0);

	क्रम_each_set_bit_from(vid, adapter->active_vlans, VLAN_N_VID)
		ixgbe_vlan_rx_add_vid(adapter->netdev, htons(ETH_P_8021Q), vid);
पूर्ण

/**
 * ixgbe_ग_लिखो_mc_addr_list - ग_लिखो multicast addresses to MTA
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Writes multicast address list to the MTA hash table.
 * Returns: -ENOMEM on failure
 *                0 on no addresses written
 *                X on writing X addresses to MTA
 **/
अटल पूर्णांक ixgbe_ग_लिखो_mc_addr_list(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	अगर (!netअगर_running(netdev))
		वापस 0;

	अगर (hw->mac.ops.update_mc_addr_list)
		hw->mac.ops.update_mc_addr_list(hw, netdev);
	अन्यथा
		वापस -ENOMEM;

#अगर_घोषित CONFIG_PCI_IOV
	ixgbe_restore_vf_multicasts(adapter);
#पूर्ण_अगर

	वापस netdev_mc_count(netdev);
पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
व्योम ixgbe_full_sync_mac_table(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_mac_addr *mac_table = &adapter->mac_table[0];
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i;

	क्रम (i = 0; i < hw->mac.num_rar_entries; i++, mac_table++) अणु
		mac_table->state &= ~IXGBE_MAC_STATE_MODIFIED;

		अगर (mac_table->state & IXGBE_MAC_STATE_IN_USE)
			hw->mac.ops.set_rar(hw, i,
					    mac_table->addr,
					    mac_table->pool,
					    IXGBE_RAH_AV);
		अन्यथा
			hw->mac.ops.clear_rar(hw, i);
	पूर्ण
पूर्ण

#पूर्ण_अगर
अटल व्योम ixgbe_sync_mac_table(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_mac_addr *mac_table = &adapter->mac_table[0];
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i;

	क्रम (i = 0; i < hw->mac.num_rar_entries; i++, mac_table++) अणु
		अगर (!(mac_table->state & IXGBE_MAC_STATE_MODIFIED))
			जारी;

		mac_table->state &= ~IXGBE_MAC_STATE_MODIFIED;

		अगर (mac_table->state & IXGBE_MAC_STATE_IN_USE)
			hw->mac.ops.set_rar(hw, i,
					    mac_table->addr,
					    mac_table->pool,
					    IXGBE_RAH_AV);
		अन्यथा
			hw->mac.ops.clear_rar(hw, i);
	पूर्ण
पूर्ण

अटल व्योम ixgbe_flush_sw_mac_table(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_mac_addr *mac_table = &adapter->mac_table[0];
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i;

	क्रम (i = 0; i < hw->mac.num_rar_entries; i++, mac_table++) अणु
		mac_table->state |= IXGBE_MAC_STATE_MODIFIED;
		mac_table->state &= ~IXGBE_MAC_STATE_IN_USE;
	पूर्ण

	ixgbe_sync_mac_table(adapter);
पूर्ण

अटल पूर्णांक ixgbe_available_rars(काष्ठा ixgbe_adapter *adapter, u16 pool)
अणु
	काष्ठा ixgbe_mac_addr *mac_table = &adapter->mac_table[0];
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i, count = 0;

	क्रम (i = 0; i < hw->mac.num_rar_entries; i++, mac_table++) अणु
		/* करो not count शेष RAR as available */
		अगर (mac_table->state & IXGBE_MAC_STATE_DEFAULT)
			जारी;

		/* only count unused and addresses that beदीर्घ to us */
		अगर (mac_table->state & IXGBE_MAC_STATE_IN_USE) अणु
			अगर (mac_table->pool != pool)
				जारी;
		पूर्ण

		count++;
	पूर्ण

	वापस count;
पूर्ण

/* this function destroys the first RAR entry */
अटल व्योम ixgbe_mac_set_शेष_filter(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_mac_addr *mac_table = &adapter->mac_table[0];
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	स_नकल(&mac_table->addr, hw->mac.addr, ETH_ALEN);
	mac_table->pool = VMDQ_P(0);

	mac_table->state = IXGBE_MAC_STATE_DEFAULT | IXGBE_MAC_STATE_IN_USE;

	hw->mac.ops.set_rar(hw, 0, mac_table->addr, mac_table->pool,
			    IXGBE_RAH_AV);
पूर्ण

पूर्णांक ixgbe_add_mac_filter(काष्ठा ixgbe_adapter *adapter,
			 स्थिर u8 *addr, u16 pool)
अणु
	काष्ठा ixgbe_mac_addr *mac_table = &adapter->mac_table[0];
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i;

	अगर (is_zero_ether_addr(addr))
		वापस -EINVAL;

	क्रम (i = 0; i < hw->mac.num_rar_entries; i++, mac_table++) अणु
		अगर (mac_table->state & IXGBE_MAC_STATE_IN_USE)
			जारी;

		ether_addr_copy(mac_table->addr, addr);
		mac_table->pool = pool;

		mac_table->state |= IXGBE_MAC_STATE_MODIFIED |
				    IXGBE_MAC_STATE_IN_USE;

		ixgbe_sync_mac_table(adapter);

		वापस i;
	पूर्ण

	वापस -ENOMEM;
पूर्ण

पूर्णांक ixgbe_del_mac_filter(काष्ठा ixgbe_adapter *adapter,
			 स्थिर u8 *addr, u16 pool)
अणु
	काष्ठा ixgbe_mac_addr *mac_table = &adapter->mac_table[0];
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i;

	अगर (is_zero_ether_addr(addr))
		वापस -EINVAL;

	/* search table क्रम addr, अगर found clear IN_USE flag and sync */
	क्रम (i = 0; i < hw->mac.num_rar_entries; i++, mac_table++) अणु
		/* we can only delete an entry अगर it is in use */
		अगर (!(mac_table->state & IXGBE_MAC_STATE_IN_USE))
			जारी;
		/* we only care about entries that beदीर्घ to the given pool */
		अगर (mac_table->pool != pool)
			जारी;
		/* we only care about a specअगरic MAC address */
		अगर (!ether_addr_equal(addr, mac_table->addr))
			जारी;

		mac_table->state |= IXGBE_MAC_STATE_MODIFIED;
		mac_table->state &= ~IXGBE_MAC_STATE_IN_USE;

		ixgbe_sync_mac_table(adapter);

		वापस 0;
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक ixgbe_uc_sync(काष्ठा net_device *netdev, स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	पूर्णांक ret;

	ret = ixgbe_add_mac_filter(adapter, addr, VMDQ_P(0));

	वापस min_t(पूर्णांक, ret, 0);
पूर्ण

अटल पूर्णांक ixgbe_uc_unsync(काष्ठा net_device *netdev, स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	ixgbe_del_mac_filter(adapter, addr, VMDQ_P(0));

	वापस 0;
पूर्ण

/**
 * ixgbe_set_rx_mode - Unicast, Multicast and Promiscuous mode set
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * The set_rx_method entry poपूर्णांक is called whenever the unicast/multicast
 * address list or the network पूर्णांकerface flags are updated.  This routine is
 * responsible क्रम configuring the hardware क्रम proper unicast, multicast and
 * promiscuous mode.
 **/
व्योम ixgbe_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 fctrl, vmolr = IXGBE_VMOLR_BAM | IXGBE_VMOLR_AUPE;
	netdev_features_t features = netdev->features;
	पूर्णांक count;

	/* Check क्रम Promiscuous and All Multicast modes */
	fctrl = IXGBE_READ_REG(hw, IXGBE_FCTRL);

	/* set all bits that we expect to always be set */
	fctrl &= ~IXGBE_FCTRL_SBP; /* disable store-bad-packets */
	fctrl |= IXGBE_FCTRL_BAM;
	fctrl |= IXGBE_FCTRL_DPF; /* discard छोड़ो frames when FC enabled */
	fctrl |= IXGBE_FCTRL_PMCF;

	/* clear the bits we are changing the status of */
	fctrl &= ~(IXGBE_FCTRL_UPE | IXGBE_FCTRL_MPE);
	अगर (netdev->flags & IFF_PROMISC) अणु
		hw->addr_ctrl.user_set_promisc = true;
		fctrl |= (IXGBE_FCTRL_UPE | IXGBE_FCTRL_MPE);
		vmolr |= IXGBE_VMOLR_MPE;
		features &= ~NETIF_F_HW_VLAN_CTAG_FILTER;
	पूर्ण अन्यथा अणु
		अगर (netdev->flags & IFF_ALLMULTI) अणु
			fctrl |= IXGBE_FCTRL_MPE;
			vmolr |= IXGBE_VMOLR_MPE;
		पूर्ण
		hw->addr_ctrl.user_set_promisc = false;
	पूर्ण

	/*
	 * Write addresses to available RAR रेजिस्टरs, अगर there is not
	 * sufficient space to store all the addresses then enable
	 * unicast promiscuous mode
	 */
	अगर (__dev_uc_sync(netdev, ixgbe_uc_sync, ixgbe_uc_unsync)) अणु
		fctrl |= IXGBE_FCTRL_UPE;
		vmolr |= IXGBE_VMOLR_ROPE;
	पूर्ण

	/* Write addresses to the MTA, अगर the attempt fails
	 * then we should just turn on promiscuous mode so
	 * that we can at least receive multicast traffic
	 */
	count = ixgbe_ग_लिखो_mc_addr_list(netdev);
	अगर (count < 0) अणु
		fctrl |= IXGBE_FCTRL_MPE;
		vmolr |= IXGBE_VMOLR_MPE;
	पूर्ण अन्यथा अगर (count) अणु
		vmolr |= IXGBE_VMOLR_ROMPE;
	पूर्ण

	अगर (hw->mac.type != ixgbe_mac_82598EB) अणु
		vmolr |= IXGBE_READ_REG(hw, IXGBE_VMOLR(VMDQ_P(0))) &
			 ~(IXGBE_VMOLR_MPE | IXGBE_VMOLR_ROMPE |
			   IXGBE_VMOLR_ROPE);
		IXGBE_WRITE_REG(hw, IXGBE_VMOLR(VMDQ_P(0)), vmolr);
	पूर्ण

	/* This is useful क्रम snअगरfing bad packets. */
	अगर (features & NETIF_F_RXALL) अणु
		/* UPE and MPE will be handled by normal PROMISC logic
		 * in e1000e_set_rx_mode */
		fctrl |= (IXGBE_FCTRL_SBP | /* Receive bad packets */
			  IXGBE_FCTRL_BAM | /* RX All Bcast Pkts */
			  IXGBE_FCTRL_PMCF); /* RX All MAC Ctrl Pkts */

		fctrl &= ~(IXGBE_FCTRL_DPF);
		/* NOTE:  VLAN filtering is disabled by setting PROMISC */
	पूर्ण

	IXGBE_WRITE_REG(hw, IXGBE_FCTRL, fctrl);

	अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
		ixgbe_vlan_strip_enable(adapter);
	अन्यथा
		ixgbe_vlan_strip_disable(adapter);

	अगर (features & NETIF_F_HW_VLAN_CTAG_FILTER)
		ixgbe_vlan_promisc_disable(adapter);
	अन्यथा
		ixgbe_vlan_promisc_enable(adapter);
पूर्ण

अटल व्योम ixgbe_napi_enable_all(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक q_idx;

	क्रम (q_idx = 0; q_idx < adapter->num_q_vectors; q_idx++)
		napi_enable(&adapter->q_vector[q_idx]->napi);
पूर्ण

अटल व्योम ixgbe_napi_disable_all(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक q_idx;

	क्रम (q_idx = 0; q_idx < adapter->num_q_vectors; q_idx++)
		napi_disable(&adapter->q_vector[q_idx]->napi);
पूर्ण

अटल पूर्णांक ixgbe_udp_tunnel_sync(काष्ठा net_device *dev, अचिन्हित पूर्णांक table)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा udp_tunnel_info ti;

	udp_tunnel_nic_get_port(dev, table, 0, &ti);
	अगर (ti.type == UDP_TUNNEL_TYPE_VXLAN)
		adapter->vxlan_port = ti.port;
	अन्यथा
		adapter->geneve_port = ti.port;

	IXGBE_WRITE_REG(hw, IXGBE_VXLANCTRL,
			ntohs(adapter->vxlan_port) |
			ntohs(adapter->geneve_port) <<
				IXGBE_VXLANCTRL_GENEVE_UDPPORT_SHIFT);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा udp_tunnel_nic_info ixgbe_udp_tunnels_x550 = अणु
	.sync_table	= ixgbe_udp_tunnel_sync,
	.flags		= UDP_TUNNEL_NIC_INFO_IPV4_ONLY,
	.tables		= अणु
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_VXLAN,  पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा udp_tunnel_nic_info ixgbe_udp_tunnels_x550em_a = अणु
	.sync_table	= ixgbe_udp_tunnel_sync,
	.flags		= UDP_TUNNEL_NIC_INFO_IPV4_ONLY,
	.tables		= अणु
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_VXLAN,  पूर्ण,
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_GENEVE, पूर्ण,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_IXGBE_DCB
/**
 * ixgbe_configure_dcb - Configure DCB hardware
 * @adapter: ixgbe adapter काष्ठा
 *
 * This is called by the driver on खोलो to configure the DCB hardware.
 * This is also called by the gennetlink पूर्णांकerface when reconfiguring
 * the DCB state.
 */
अटल व्योम ixgbe_configure_dcb(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक max_frame = adapter->netdev->mtu + ETH_HLEN + ETH_FCS_LEN;

	अगर (!(adapter->flags & IXGBE_FLAG_DCB_ENABLED)) अणु
		अगर (hw->mac.type == ixgbe_mac_82598EB)
			netअगर_set_gso_max_size(adapter->netdev, 65536);
		वापस;
	पूर्ण

	अगर (hw->mac.type == ixgbe_mac_82598EB)
		netअगर_set_gso_max_size(adapter->netdev, 32768);

#अगर_घोषित IXGBE_FCOE
	अगर (adapter->netdev->features & NETIF_F_FCOE_MTU)
		max_frame = max(max_frame, IXGBE_FCOE_JUMBO_FRAME_SIZE);
#पूर्ण_अगर

	/* reconfigure the hardware */
	अगर (adapter->dcbx_cap & DCB_CAP_DCBX_VER_CEE) अणु
		ixgbe_dcb_calculate_tc_credits(hw, &adapter->dcb_cfg, max_frame,
						DCB_TX_CONFIG);
		ixgbe_dcb_calculate_tc_credits(hw, &adapter->dcb_cfg, max_frame,
						DCB_RX_CONFIG);
		ixgbe_dcb_hw_config(hw, &adapter->dcb_cfg);
	पूर्ण अन्यथा अगर (adapter->ixgbe_ieee_ets && adapter->ixgbe_ieee_pfc) अणु
		ixgbe_dcb_hw_ets(&adapter->hw,
				 adapter->ixgbe_ieee_ets,
				 max_frame);
		ixgbe_dcb_hw_pfc_config(&adapter->hw,
					adapter->ixgbe_ieee_pfc->pfc_en,
					adapter->ixgbe_ieee_ets->prio_tc);
	पूर्ण

	/* Enable RSS Hash per TC */
	अगर (hw->mac.type != ixgbe_mac_82598EB) अणु
		u32 msb = 0;
		u16 rss_i = adapter->ring_feature[RING_F_RSS].indices - 1;

		जबतक (rss_i) अणु
			msb++;
			rss_i >>= 1;
		पूर्ण

		/* ग_लिखो msb to all 8 TCs in one ग_लिखो */
		IXGBE_WRITE_REG(hw, IXGBE_RQTC, msb * 0x11111111);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/* Additional bitसमय to account क्रम IXGBE framing */
#घोषणा IXGBE_ETH_FRAMING 20

/**
 * ixgbe_hpbthresh - calculate high water mark क्रम flow control
 *
 * @adapter: board निजी काष्ठाure to calculate क्रम
 * @pb: packet buffer to calculate
 */
अटल पूर्णांक ixgbe_hpbthresh(काष्ठा ixgbe_adapter *adapter, पूर्णांक pb)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा net_device *dev = adapter->netdev;
	पूर्णांक link, tc, kb, marker;
	u32 dv_id, rx_pba;

	/* Calculate max LAN frame size */
	tc = link = dev->mtu + ETH_HLEN + ETH_FCS_LEN + IXGBE_ETH_FRAMING;

#अगर_घोषित IXGBE_FCOE
	/* FCoE traffic class uses FCOE jumbo frames */
	अगर ((dev->features & NETIF_F_FCOE_MTU) &&
	    (tc < IXGBE_FCOE_JUMBO_FRAME_SIZE) &&
	    (pb == ixgbe_fcoe_get_tc(adapter)))
		tc = IXGBE_FCOE_JUMBO_FRAME_SIZE;
#पूर्ण_अगर

	/* Calculate delay value क्रम device */
	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		dv_id = IXGBE_DV_X540(link, tc);
		अवरोध;
	शेष:
		dv_id = IXGBE_DV(link, tc);
		अवरोध;
	पूर्ण

	/* Loopback चयन पूर्णांकroduces additional latency */
	अगर (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED)
		dv_id += IXGBE_B2BT(tc);

	/* Delay value is calculated in bit बार convert to KB */
	kb = IXGBE_BT2KB(dv_id);
	rx_pba = IXGBE_READ_REG(hw, IXGBE_RXPBSIZE(pb)) >> 10;

	marker = rx_pba - kb;

	/* It is possible that the packet buffer is not large enough
	 * to provide required headroom. In this हाल throw an error
	 * to user and a करो the best we can.
	 */
	अगर (marker < 0) अणु
		e_warn(drv, "Packet Buffer(%i) can not provide enough"
			    "headroom to support flow control."
			    "Decrease MTU or number of traffic classes\n", pb);
		marker = tc + 1;
	पूर्ण

	वापस marker;
पूर्ण

/**
 * ixgbe_lpbthresh - calculate low water mark क्रम क्रम flow control
 *
 * @adapter: board निजी काष्ठाure to calculate क्रम
 * @pb: packet buffer to calculate
 */
अटल पूर्णांक ixgbe_lpbthresh(काष्ठा ixgbe_adapter *adapter, पूर्णांक pb)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा net_device *dev = adapter->netdev;
	पूर्णांक tc;
	u32 dv_id;

	/* Calculate max LAN frame size */
	tc = dev->mtu + ETH_HLEN + ETH_FCS_LEN;

#अगर_घोषित IXGBE_FCOE
	/* FCoE traffic class uses FCOE jumbo frames */
	अगर ((dev->features & NETIF_F_FCOE_MTU) &&
	    (tc < IXGBE_FCOE_JUMBO_FRAME_SIZE) &&
	    (pb == netdev_get_prio_tc_map(dev, adapter->fcoe.up)))
		tc = IXGBE_FCOE_JUMBO_FRAME_SIZE;
#पूर्ण_अगर

	/* Calculate delay value क्रम device */
	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		dv_id = IXGBE_LOW_DV_X540(tc);
		अवरोध;
	शेष:
		dv_id = IXGBE_LOW_DV(tc);
		अवरोध;
	पूर्ण

	/* Delay value is calculated in bit बार convert to KB */
	वापस IXGBE_BT2KB(dv_id);
पूर्ण

/*
 * ixgbe_pbthresh_setup - calculate and setup high low water marks
 */
अटल व्योम ixgbe_pbthresh_setup(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक num_tc = adapter->hw_tcs;
	पूर्णांक i;

	अगर (!num_tc)
		num_tc = 1;

	क्रम (i = 0; i < num_tc; i++) अणु
		hw->fc.high_water[i] = ixgbe_hpbthresh(adapter, i);
		hw->fc.low_water[i] = ixgbe_lpbthresh(adapter, i);

		/* Low water marks must not be larger than high water marks */
		अगर (hw->fc.low_water[i] > hw->fc.high_water[i])
			hw->fc.low_water[i] = 0;
	पूर्ण

	क्रम (; i < MAX_TRAFFIC_CLASS; i++)
		hw->fc.high_water[i] = 0;
पूर्ण

अटल व्योम ixgbe_configure_pb(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक hdrm;
	u8 tc = adapter->hw_tcs;

	अगर (adapter->flags & IXGBE_FLAG_Fसूची_HASH_CAPABLE ||
	    adapter->flags & IXGBE_FLAG_Fसूची_PERFECT_CAPABLE)
		hdrm = 32 << adapter->fdir_pballoc;
	अन्यथा
		hdrm = 0;

	hw->mac.ops.set_rxpba(hw, tc, hdrm, PBA_STRATEGY_EQUAL);
	ixgbe_pbthresh_setup(adapter);
पूर्ण

अटल व्योम ixgbe_fdir_filter_restore(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा hlist_node *node2;
	काष्ठा ixgbe_fdir_filter *filter;
	u8 queue;

	spin_lock(&adapter->fdir_perfect_lock);

	अगर (!hlist_empty(&adapter->fdir_filter_list))
		ixgbe_fdir_set_input_mask_82599(hw, &adapter->fdir_mask);

	hlist_क्रम_each_entry_safe(filter, node2,
				  &adapter->fdir_filter_list, fdir_node) अणु
		अगर (filter->action == IXGBE_Fसूची_DROP_QUEUE) अणु
			queue = IXGBE_Fसूची_DROP_QUEUE;
		पूर्ण अन्यथा अणु
			u32 ring = ethtool_get_flow_spec_ring(filter->action);
			u8 vf = ethtool_get_flow_spec_ring_vf(filter->action);

			अगर (!vf && (ring >= adapter->num_rx_queues)) अणु
				e_err(drv, "FDIR restore failed without VF, ring: %u\n",
				      ring);
				जारी;
			पूर्ण अन्यथा अगर (vf &&
				   ((vf > adapter->num_vfs) ||
				     ring >= adapter->num_rx_queues_per_pool)) अणु
				e_err(drv, "FDIR restore failed with VF, vf: %hhu, ring: %u\n",
				      vf, ring);
				जारी;
			पूर्ण

			/* Map the ring onto the असलolute queue index */
			अगर (!vf)
				queue = adapter->rx_ring[ring]->reg_idx;
			अन्यथा
				queue = ((vf - 1) *
					adapter->num_rx_queues_per_pool) + ring;
		पूर्ण

		ixgbe_fdir_ग_लिखो_perfect_filter_82599(hw,
				&filter->filter, filter->sw_idx, queue);
	पूर्ण

	spin_unlock(&adapter->fdir_perfect_lock);
पूर्ण

/**
 * ixgbe_clean_rx_ring - Free Rx Buffers per Queue
 * @rx_ring: ring to मुक्त buffers from
 **/
अटल व्योम ixgbe_clean_rx_ring(काष्ठा ixgbe_ring *rx_ring)
अणु
	u16 i = rx_ring->next_to_clean;
	काष्ठा ixgbe_rx_buffer *rx_buffer = &rx_ring->rx_buffer_info[i];

	अगर (rx_ring->xsk_pool) अणु
		ixgbe_xsk_clean_rx_ring(rx_ring);
		जाओ skip_मुक्त;
	पूर्ण

	/* Free all the Rx ring sk_buffs */
	जबतक (i != rx_ring->next_to_alloc) अणु
		अगर (rx_buffer->skb) अणु
			काष्ठा sk_buff *skb = rx_buffer->skb;
			अगर (IXGBE_CB(skb)->page_released)
				dma_unmap_page_attrs(rx_ring->dev,
						     IXGBE_CB(skb)->dma,
						     ixgbe_rx_pg_size(rx_ring),
						     DMA_FROM_DEVICE,
						     IXGBE_RX_DMA_ATTR);
			dev_kमुक्त_skb(skb);
		पूर्ण

		/* Invalidate cache lines that may have been written to by
		 * device so that we aव्योम corrupting memory.
		 */
		dma_sync_single_range_क्रम_cpu(rx_ring->dev,
					      rx_buffer->dma,
					      rx_buffer->page_offset,
					      ixgbe_rx_bufsz(rx_ring),
					      DMA_FROM_DEVICE);

		/* मुक्त resources associated with mapping */
		dma_unmap_page_attrs(rx_ring->dev, rx_buffer->dma,
				     ixgbe_rx_pg_size(rx_ring),
				     DMA_FROM_DEVICE,
				     IXGBE_RX_DMA_ATTR);
		__page_frag_cache_drain(rx_buffer->page,
					rx_buffer->pagecnt_bias);

		i++;
		rx_buffer++;
		अगर (i == rx_ring->count) अणु
			i = 0;
			rx_buffer = rx_ring->rx_buffer_info;
		पूर्ण
	पूर्ण

skip_मुक्त:
	rx_ring->next_to_alloc = 0;
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
पूर्ण

अटल पूर्णांक ixgbe_fwd_ring_up(काष्ठा ixgbe_adapter *adapter,
			     काष्ठा ixgbe_fwd_adapter *accel)
अणु
	u16 rss_i = adapter->ring_feature[RING_F_RSS].indices;
	पूर्णांक num_tc = netdev_get_num_tc(adapter->netdev);
	काष्ठा net_device *vdev = accel->netdev;
	पूर्णांक i, baseq, err;

	baseq = accel->pool * adapter->num_rx_queues_per_pool;
	netdev_dbg(vdev, "pool %i:%i queues %i:%i\n",
		   accel->pool, adapter->num_rx_pools,
		   baseq, baseq + adapter->num_rx_queues_per_pool);

	accel->rx_base_queue = baseq;
	accel->tx_base_queue = baseq;

	/* record configuration क्रम macvlan पूर्णांकerface in vdev */
	क्रम (i = 0; i < num_tc; i++)
		netdev_bind_sb_channel_queue(adapter->netdev, vdev,
					     i, rss_i, baseq + (rss_i * i));

	क्रम (i = 0; i < adapter->num_rx_queues_per_pool; i++)
		adapter->rx_ring[baseq + i]->netdev = vdev;

	/* Guarantee all rings are updated beक्रमe we update the
	 * MAC address filter.
	 */
	wmb();

	/* ixgbe_add_mac_filter will वापस an index अगर it succeeds, so we
	 * need to only treat it as an error value अगर it is negative.
	 */
	err = ixgbe_add_mac_filter(adapter, vdev->dev_addr,
				   VMDQ_P(accel->pool));
	अगर (err >= 0)
		वापस 0;

	/* अगर we cannot add the MAC rule then disable the offload */
	macvlan_release_l2fw_offload(vdev);

	क्रम (i = 0; i < adapter->num_rx_queues_per_pool; i++)
		adapter->rx_ring[baseq + i]->netdev = शून्य;

	netdev_err(vdev, "L2FW offload disabled due to L2 filter error\n");

	/* unbind the queues and drop the subordinate channel config */
	netdev_unbind_sb_channel(adapter->netdev, vdev);
	netdev_set_sb_channel(vdev, 0);

	clear_bit(accel->pool, adapter->fwd_biपंचांगask);
	kमुक्त(accel);

	वापस err;
पूर्ण

अटल पूर्णांक ixgbe_macvlan_up(काष्ठा net_device *vdev,
			    काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा ixgbe_adapter *adapter = (काष्ठा ixgbe_adapter *)priv->data;
	काष्ठा ixgbe_fwd_adapter *accel;

	अगर (!netअगर_is_macvlan(vdev))
		वापस 0;

	accel = macvlan_accel_priv(vdev);
	अगर (!accel)
		वापस 0;

	ixgbe_fwd_ring_up(adapter, accel);

	वापस 0;
पूर्ण

अटल व्योम ixgbe_configure_dfwd(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.data = (व्योम *)adapter,
	पूर्ण;

	netdev_walk_all_upper_dev_rcu(adapter->netdev,
				      ixgbe_macvlan_up, &priv);
पूर्ण

अटल व्योम ixgbe_configure(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	ixgbe_configure_pb(adapter);
#अगर_घोषित CONFIG_IXGBE_DCB
	ixgbe_configure_dcb(adapter);
#पूर्ण_अगर
	/*
	 * We must restore भवization beक्रमe VLANs or अन्यथा
	 * the VLVF रेजिस्टरs will not be populated
	 */
	ixgbe_configure_भवization(adapter);

	ixgbe_set_rx_mode(adapter->netdev);
	ixgbe_restore_vlan(adapter);
	ixgbe_ipsec_restore(adapter);

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
		hw->mac.ops.disable_rx_buff(hw);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (adapter->flags & IXGBE_FLAG_Fसूची_HASH_CAPABLE) अणु
		ixgbe_init_fdir_signature_82599(&adapter->hw,
						adapter->fdir_pballoc);
	पूर्ण अन्यथा अगर (adapter->flags & IXGBE_FLAG_Fसूची_PERFECT_CAPABLE) अणु
		ixgbe_init_fdir_perfect_82599(&adapter->hw,
					      adapter->fdir_pballoc);
		ixgbe_fdir_filter_restore(adapter);
	पूर्ण

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
		hw->mac.ops.enable_rx_buff(hw);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

#अगर_घोषित CONFIG_IXGBE_DCA
	/* configure DCA */
	अगर (adapter->flags & IXGBE_FLAG_DCA_CAPABLE)
		ixgbe_setup_dca(adapter);
#पूर्ण_अगर /* CONFIG_IXGBE_DCA */

#अगर_घोषित IXGBE_FCOE
	/* configure FCoE L2 filters, redirection table, and Rx control */
	ixgbe_configure_fcoe(adapter);

#पूर्ण_अगर /* IXGBE_FCOE */
	ixgbe_configure_tx(adapter);
	ixgbe_configure_rx(adapter);
	ixgbe_configure_dfwd(adapter);
पूर्ण

/**
 * ixgbe_sfp_link_config - set up SFP+ link
 * @adapter: poपूर्णांकer to निजी adapter काष्ठा
 **/
अटल व्योम ixgbe_sfp_link_config(काष्ठा ixgbe_adapter *adapter)
अणु
	/*
	 * We are assuming the worst हाल scenario here, and that
	 * is that an SFP was inserted/हटाओd after the reset
	 * but beक्रमe SFP detection was enabled.  As such the best
	 * solution is to just start searching as soon as we start
	 */
	अगर (adapter->hw.mac.type == ixgbe_mac_82598EB)
		adapter->flags2 |= IXGBE_FLAG2_SEARCH_FOR_SFP;

	adapter->flags2 |= IXGBE_FLAG2_SFP_NEEDS_RESET;
	adapter->sfp_poll_समय = 0;
पूर्ण

/**
 * ixgbe_non_sfp_link_config - set up non-SFP+ link
 * @hw: poपूर्णांकer to निजी hardware काष्ठा
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक ixgbe_non_sfp_link_config(काष्ठा ixgbe_hw *hw)
अणु
	u32 speed;
	bool स्वतःneg, link_up = false;
	पूर्णांक ret = IXGBE_ERR_LINK_SETUP;

	अगर (hw->mac.ops.check_link)
		ret = hw->mac.ops.check_link(hw, &speed, &link_up, false);

	अगर (ret)
		वापस ret;

	speed = hw->phy.स्वतःneg_advertised;
	अगर (!speed && hw->mac.ops.get_link_capabilities) अणु
		ret = hw->mac.ops.get_link_capabilities(hw, &speed,
							&स्वतःneg);
		speed &= ~(IXGBE_LINK_SPEED_5GB_FULL |
			   IXGBE_LINK_SPEED_2_5GB_FULL);
	पूर्ण

	अगर (ret)
		वापस ret;

	अगर (hw->mac.ops.setup_link)
		ret = hw->mac.ops.setup_link(hw, speed, link_up);

	वापस ret;
पूर्ण

अटल व्योम ixgbe_setup_gpie(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 gpie = 0;

	अगर (adapter->flags & IXGBE_FLAG_MSIX_ENABLED) अणु
		gpie = IXGBE_GPIE_MSIX_MODE | IXGBE_GPIE_PBA_SUPPORT |
		       IXGBE_GPIE_OCD;
		gpie |= IXGBE_GPIE_EIAME;
		/*
		 * use EIAM to स्वतः-mask when MSI-X पूर्णांकerrupt is निश्चितed
		 * this saves a रेजिस्टर ग_लिखो क्रम every पूर्णांकerrupt
		 */
		चयन (hw->mac.type) अणु
		हाल ixgbe_mac_82598EB:
			IXGBE_WRITE_REG(hw, IXGBE_EIAM, IXGBE_EICS_RTX_QUEUE);
			अवरोध;
		हाल ixgbe_mac_82599EB:
		हाल ixgbe_mac_X540:
		हाल ixgbe_mac_X550:
		हाल ixgbe_mac_X550EM_x:
		हाल ixgbe_mac_x550em_a:
		शेष:
			IXGBE_WRITE_REG(hw, IXGBE_EIAM_EX(0), 0xFFFFFFFF);
			IXGBE_WRITE_REG(hw, IXGBE_EIAM_EX(1), 0xFFFFFFFF);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* legacy पूर्णांकerrupts, use EIAM to स्वतः-mask when पढ़ोing EICR,
		 * specअगरically only स्वतः mask tx and rx पूर्णांकerrupts */
		IXGBE_WRITE_REG(hw, IXGBE_EIAM, IXGBE_EICS_RTX_QUEUE);
	पूर्ण

	/* XXX: to पूर्णांकerrupt immediately क्रम EICS ग_लिखोs, enable this */
	/* gpie |= IXGBE_GPIE_EIMEN; */

	अगर (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) अणु
		gpie &= ~IXGBE_GPIE_VTMODE_MASK;

		चयन (adapter->ring_feature[RING_F_VMDQ].mask) अणु
		हाल IXGBE_82599_VMDQ_8Q_MASK:
			gpie |= IXGBE_GPIE_VTMODE_16;
			अवरोध;
		हाल IXGBE_82599_VMDQ_4Q_MASK:
			gpie |= IXGBE_GPIE_VTMODE_32;
			अवरोध;
		शेष:
			gpie |= IXGBE_GPIE_VTMODE_64;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Enable Thermal over heat sensor पूर्णांकerrupt */
	अगर (adapter->flags2 & IXGBE_FLAG2_TEMP_SENSOR_CAPABLE) अणु
		चयन (adapter->hw.mac.type) अणु
		हाल ixgbe_mac_82599EB:
			gpie |= IXGBE_SDP0_GPIEN_8259X;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* Enable fan failure पूर्णांकerrupt */
	अगर (adapter->flags & IXGBE_FLAG_FAN_FAIL_CAPABLE)
		gpie |= IXGBE_SDP1_GPIEN(hw);

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82599EB:
		gpie |= IXGBE_SDP1_GPIEN_8259X | IXGBE_SDP2_GPIEN_8259X;
		अवरोध;
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		gpie |= IXGBE_SDP0_GPIEN_X540;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	IXGBE_WRITE_REG(hw, IXGBE_GPIE, gpie);
पूर्ण

अटल व्योम ixgbe_up_complete(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक err;
	u32 ctrl_ext;

	ixgbe_get_hw_control(adapter);
	ixgbe_setup_gpie(adapter);

	अगर (adapter->flags & IXGBE_FLAG_MSIX_ENABLED)
		ixgbe_configure_msix(adapter);
	अन्यथा
		ixgbe_configure_msi_and_legacy(adapter);

	/* enable the optics क्रम 82599 SFP+ fiber */
	अगर (hw->mac.ops.enable_tx_laser)
		hw->mac.ops.enable_tx_laser(hw);

	अगर (hw->phy.ops.set_phy_घातer)
		hw->phy.ops.set_phy_घातer(hw, true);

	smp_mb__beक्रमe_atomic();
	clear_bit(__IXGBE_DOWN, &adapter->state);
	ixgbe_napi_enable_all(adapter);

	अगर (ixgbe_is_sfp(hw)) अणु
		ixgbe_sfp_link_config(adapter);
	पूर्ण अन्यथा अणु
		err = ixgbe_non_sfp_link_config(hw);
		अगर (err)
			e_err(probe, "link_config FAILED %d\n", err);
	पूर्ण

	/* clear any pending पूर्णांकerrupts, may स्वतः mask */
	IXGBE_READ_REG(hw, IXGBE_EICR);
	ixgbe_irq_enable(adapter, true, true);

	/*
	 * If this adapter has a fan, check to see अगर we had a failure
	 * beक्रमe we enabled the पूर्णांकerrupt.
	 */
	अगर (adapter->flags & IXGBE_FLAG_FAN_FAIL_CAPABLE) अणु
		u32 esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);
		अगर (esdp & IXGBE_ESDP_SDP1)
			e_crit(drv, "Fan has stopped, replace the adapter\n");
	पूर्ण

	/* bring the link up in the watchकरोg, this could race with our first
	 * link up पूर्णांकerrupt but shouldn't be a problem */
	adapter->flags |= IXGBE_FLAG_NEED_LINK_UPDATE;
	adapter->link_check_समयout = jअगरfies;
	mod_समयr(&adapter->service_समयr, jअगरfies);

	/* Set PF Reset Done bit so PF/VF Mail Ops can work */
	ctrl_ext = IXGBE_READ_REG(hw, IXGBE_CTRL_EXT);
	ctrl_ext |= IXGBE_CTRL_EXT_PFRSTD;
	IXGBE_WRITE_REG(hw, IXGBE_CTRL_EXT, ctrl_ext);
पूर्ण

व्योम ixgbe_reinit_locked(काष्ठा ixgbe_adapter *adapter)
अणु
	/* put off any impending NetWatchDogTimeout */
	netअगर_trans_update(adapter->netdev);

	जबतक (test_and_set_bit(__IXGBE_RESETTING, &adapter->state))
		usleep_range(1000, 2000);
	अगर (adapter->hw.phy.type == ixgbe_phy_fw)
		ixgbe_watchकरोg_link_is_करोwn(adapter);
	ixgbe_करोwn(adapter);
	/*
	 * If SR-IOV enabled then रुको a bit beक्रमe bringing the adapter
	 * back up to give the VFs समय to respond to the reset.  The
	 * two second रुको is based upon the watchकरोg समयr cycle in
	 * the VF driver.
	 */
	अगर (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED)
		msleep(2000);
	ixgbe_up(adapter);
	clear_bit(__IXGBE_RESETTING, &adapter->state);
पूर्ण

व्योम ixgbe_up(काष्ठा ixgbe_adapter *adapter)
अणु
	/* hardware has been reset, we need to reload some things */
	ixgbe_configure(adapter);

	ixgbe_up_complete(adapter);
पूर्ण

अटल अचिन्हित दीर्घ ixgbe_get_completion_समयout(काष्ठा ixgbe_adapter *adapter)
अणु
	u16 devctl2;

	pcie_capability_पढ़ो_word(adapter->pdev, PCI_EXP_DEVCTL2, &devctl2);

	चयन (devctl2 & IXGBE_PCIDEVCTRL2_TIMEO_MASK) अणु
	हाल IXGBE_PCIDEVCTRL2_17_34s:
	हाल IXGBE_PCIDEVCTRL2_4_8s:
		/* For now we cap the upper limit on delay to 2 seconds
		 * as we end up going up to 34 seconds of delay in worst
		 * हाल समयout value.
		 */
	हाल IXGBE_PCIDEVCTRL2_1_2s:
		वापस 2000000ul;	/* 2.0 s */
	हाल IXGBE_PCIDEVCTRL2_260_520ms:
		वापस 520000ul;	/* 520 ms */
	हाल IXGBE_PCIDEVCTRL2_65_130ms:
		वापस 130000ul;	/* 130 ms */
	हाल IXGBE_PCIDEVCTRL2_16_32ms:
		वापस 32000ul;		/* 32 ms */
	हाल IXGBE_PCIDEVCTRL2_1_2ms:
		वापस 2000ul;		/* 2 ms */
	हाल IXGBE_PCIDEVCTRL2_50_100us:
		वापस 100ul;		/* 100 us */
	हाल IXGBE_PCIDEVCTRL2_16_32ms_def:
		वापस 32000ul;		/* 32 ms */
	शेष:
		अवरोध;
	पूर्ण

	/* We shouldn't need to hit this path, but just in हाल शेष as
	 * though completion समयout is not supported and support 32ms.
	 */
	वापस 32000ul;
पूर्ण

व्योम ixgbe_disable_rx(काष्ठा ixgbe_adapter *adapter)
अणु
	अचिन्हित दीर्घ रुको_delay, delay_पूर्णांकerval;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i, रुको_loop;
	u32 rxdctl;

	/* disable receives */
	hw->mac.ops.disable_rx(hw);

	अगर (ixgbe_हटाओd(hw->hw_addr))
		वापस;

	/* disable all enabled Rx queues */
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा ixgbe_ring *ring = adapter->rx_ring[i];
		u8 reg_idx = ring->reg_idx;

		rxdctl = IXGBE_READ_REG(hw, IXGBE_RXDCTL(reg_idx));
		rxdctl &= ~IXGBE_RXDCTL_ENABLE;
		rxdctl |= IXGBE_RXDCTL_SWFLSH;

		/* ग_लिखो value back with RXDCTL.ENABLE bit cleared */
		IXGBE_WRITE_REG(hw, IXGBE_RXDCTL(reg_idx), rxdctl);
	पूर्ण

	/* RXDCTL.EN may not change on 82598 अगर link is करोwn, so skip it */
	अगर (hw->mac.type == ixgbe_mac_82598EB &&
	    !(IXGBE_READ_REG(hw, IXGBE_LINKS) & IXGBE_LINKS_UP))
		वापस;

	/* Determine our minimum delay पूर्णांकerval. We will increase this value
	 * with each subsequent test. This way अगर the device वापसs quickly
	 * we should spend as little समय as possible रुकोing, however as
	 * the समय increases we will रुको क्रम larger periods of समय.
	 *
	 * The trick here is that we increase the पूर्णांकerval using the
	 * following pattern: 1x 3x 5x 7x 9x 11x 13x 15x 17x 19x. The result
	 * of that रुको is that it totals up to 100x whatever पूर्णांकerval we
	 * choose. Since our minimum रुको is 100us we can just भागide the
	 * total समयout by 100 to get our minimum delay पूर्णांकerval.
	 */
	delay_पूर्णांकerval = ixgbe_get_completion_समयout(adapter) / 100;

	रुको_loop = IXGBE_MAX_RX_DESC_POLL;
	रुको_delay = delay_पूर्णांकerval;

	जबतक (रुको_loop--) अणु
		usleep_range(रुको_delay, रुको_delay + 10);
		रुको_delay += delay_पूर्णांकerval * 2;
		rxdctl = 0;

		/* OR together the पढ़ोing of all the active RXDCTL रेजिस्टरs,
		 * and then test the result. We need the disable to complete
		 * beक्रमe we start मुक्तing the memory and invalidating the
		 * DMA mappings.
		 */
		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			काष्ठा ixgbe_ring *ring = adapter->rx_ring[i];
			u8 reg_idx = ring->reg_idx;

			rxdctl |= IXGBE_READ_REG(hw, IXGBE_RXDCTL(reg_idx));
		पूर्ण

		अगर (!(rxdctl & IXGBE_RXDCTL_ENABLE))
			वापस;
	पूर्ण

	e_err(drv,
	      "RXDCTL.ENABLE for one or more queues not cleared within the polling period\n");
पूर्ण

व्योम ixgbe_disable_tx(काष्ठा ixgbe_adapter *adapter)
अणु
	अचिन्हित दीर्घ रुको_delay, delay_पूर्णांकerval;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i, रुको_loop;
	u32 txdctl;

	अगर (ixgbe_हटाओd(hw->hw_addr))
		वापस;

	/* disable all enabled Tx queues */
	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		काष्ठा ixgbe_ring *ring = adapter->tx_ring[i];
		u8 reg_idx = ring->reg_idx;

		IXGBE_WRITE_REG(hw, IXGBE_TXDCTL(reg_idx), IXGBE_TXDCTL_SWFLSH);
	पूर्ण

	/* disable all enabled XDP Tx queues */
	क्रम (i = 0; i < adapter->num_xdp_queues; i++) अणु
		काष्ठा ixgbe_ring *ring = adapter->xdp_ring[i];
		u8 reg_idx = ring->reg_idx;

		IXGBE_WRITE_REG(hw, IXGBE_TXDCTL(reg_idx), IXGBE_TXDCTL_SWFLSH);
	पूर्ण

	/* If the link is not up there shouldn't be much in the way of
	 * pending transactions. Those that are left will be flushed out
	 * when the reset logic goes through the flush sequence to clean out
	 * the pending Tx transactions.
	 */
	अगर (!(IXGBE_READ_REG(hw, IXGBE_LINKS) & IXGBE_LINKS_UP))
		जाओ dma_engine_disable;

	/* Determine our minimum delay पूर्णांकerval. We will increase this value
	 * with each subsequent test. This way अगर the device वापसs quickly
	 * we should spend as little समय as possible रुकोing, however as
	 * the समय increases we will रुको क्रम larger periods of समय.
	 *
	 * The trick here is that we increase the पूर्णांकerval using the
	 * following pattern: 1x 3x 5x 7x 9x 11x 13x 15x 17x 19x. The result
	 * of that रुको is that it totals up to 100x whatever पूर्णांकerval we
	 * choose. Since our minimum रुको is 100us we can just भागide the
	 * total समयout by 100 to get our minimum delay पूर्णांकerval.
	 */
	delay_पूर्णांकerval = ixgbe_get_completion_समयout(adapter) / 100;

	रुको_loop = IXGBE_MAX_RX_DESC_POLL;
	रुको_delay = delay_पूर्णांकerval;

	जबतक (रुको_loop--) अणु
		usleep_range(रुको_delay, रुको_delay + 10);
		रुको_delay += delay_पूर्णांकerval * 2;
		txdctl = 0;

		/* OR together the पढ़ोing of all the active TXDCTL रेजिस्टरs,
		 * and then test the result. We need the disable to complete
		 * beक्रमe we start मुक्तing the memory and invalidating the
		 * DMA mappings.
		 */
		क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
			काष्ठा ixgbe_ring *ring = adapter->tx_ring[i];
			u8 reg_idx = ring->reg_idx;

			txdctl |= IXGBE_READ_REG(hw, IXGBE_TXDCTL(reg_idx));
		पूर्ण
		क्रम (i = 0; i < adapter->num_xdp_queues; i++) अणु
			काष्ठा ixgbe_ring *ring = adapter->xdp_ring[i];
			u8 reg_idx = ring->reg_idx;

			txdctl |= IXGBE_READ_REG(hw, IXGBE_TXDCTL(reg_idx));
		पूर्ण

		अगर (!(txdctl & IXGBE_TXDCTL_ENABLE))
			जाओ dma_engine_disable;
	पूर्ण

	e_err(drv,
	      "TXDCTL.ENABLE for one or more queues not cleared within the polling period\n");

dma_engine_disable:
	/* Disable the Tx DMA engine on 82599 and later MAC */
	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		IXGBE_WRITE_REG(hw, IXGBE_DMATXCTL,
				(IXGBE_READ_REG(hw, IXGBE_DMATXCTL) &
				 ~IXGBE_DMATXCTL_TE));
		fallthrough;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम ixgbe_reset(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err;

	अगर (ixgbe_हटाओd(hw->hw_addr))
		वापस;
	/* lock SFP init bit to prevent race conditions with the watchकरोg */
	जबतक (test_and_set_bit(__IXGBE_IN_SFP_INIT, &adapter->state))
		usleep_range(1000, 2000);

	/* clear all SFP and link config related flags जबतक holding SFP_INIT */
	adapter->flags2 &= ~(IXGBE_FLAG2_SEARCH_FOR_SFP |
			     IXGBE_FLAG2_SFP_NEEDS_RESET);
	adapter->flags &= ~IXGBE_FLAG_NEED_LINK_CONFIG;

	err = hw->mac.ops.init_hw(hw);
	चयन (err) अणु
	हाल 0:
	हाल IXGBE_ERR_SFP_NOT_PRESENT:
	हाल IXGBE_ERR_SFP_NOT_SUPPORTED:
		अवरोध;
	हाल IXGBE_ERR_MASTER_REQUESTS_PENDING:
		e_dev_err("master disable timed out\n");
		अवरोध;
	हाल IXGBE_ERR_EEPROM_VERSION:
		/* We are running on a pre-production device, log a warning */
		e_dev_warn("This device is a pre-production adapter/LOM. "
			   "Please be aware there may be issues associated with "
			   "your hardware.  If you are experiencing problems "
			   "please contact your Intel or hardware "
			   "representative who provided you with this "
			   "hardware.\n");
		अवरोध;
	शेष:
		e_dev_err("Hardware Error: %d\n", err);
	पूर्ण

	clear_bit(__IXGBE_IN_SFP_INIT, &adapter->state);

	/* flush entries out of MAC table */
	ixgbe_flush_sw_mac_table(adapter);
	__dev_uc_unsync(netdev, शून्य);

	/* करो not flush user set addresses */
	ixgbe_mac_set_शेष_filter(adapter);

	/* update SAN MAC vmdq pool selection */
	अगर (hw->mac.san_mac_rar_index)
		hw->mac.ops.set_vmdq_san_mac(hw, VMDQ_P(0));

	अगर (test_bit(__IXGBE_PTP_RUNNING, &adapter->state))
		ixgbe_ptp_reset(adapter);

	अगर (hw->phy.ops.set_phy_घातer) अणु
		अगर (!netअगर_running(adapter->netdev) && !adapter->wol)
			hw->phy.ops.set_phy_घातer(hw, false);
		अन्यथा
			hw->phy.ops.set_phy_घातer(hw, true);
	पूर्ण
पूर्ण

/**
 * ixgbe_clean_tx_ring - Free Tx Buffers
 * @tx_ring: ring to be cleaned
 **/
अटल व्योम ixgbe_clean_tx_ring(काष्ठा ixgbe_ring *tx_ring)
अणु
	u16 i = tx_ring->next_to_clean;
	काष्ठा ixgbe_tx_buffer *tx_buffer = &tx_ring->tx_buffer_info[i];

	अगर (tx_ring->xsk_pool) अणु
		ixgbe_xsk_clean_tx_ring(tx_ring);
		जाओ out;
	पूर्ण

	जबतक (i != tx_ring->next_to_use) अणु
		जोड़ ixgbe_adv_tx_desc *eop_desc, *tx_desc;

		/* Free all the Tx ring sk_buffs */
		अगर (ring_is_xdp(tx_ring))
			xdp_वापस_frame(tx_buffer->xdpf);
		अन्यथा
			dev_kमुक्त_skb_any(tx_buffer->skb);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer, dma),
				 dma_unmap_len(tx_buffer, len),
				 DMA_TO_DEVICE);

		/* check क्रम eop_desc to determine the end of the packet */
		eop_desc = tx_buffer->next_to_watch;
		tx_desc = IXGBE_TX_DESC(tx_ring, i);

		/* unmap reमुख्यing buffers */
		जबतक (tx_desc != eop_desc) अणु
			tx_buffer++;
			tx_desc++;
			i++;
			अगर (unlikely(i == tx_ring->count)) अणु
				i = 0;
				tx_buffer = tx_ring->tx_buffer_info;
				tx_desc = IXGBE_TX_DESC(tx_ring, 0);
			पूर्ण

			/* unmap any reमुख्यing paged data */
			अगर (dma_unmap_len(tx_buffer, len))
				dma_unmap_page(tx_ring->dev,
					       dma_unmap_addr(tx_buffer, dma),
					       dma_unmap_len(tx_buffer, len),
					       DMA_TO_DEVICE);
		पूर्ण

		/* move us one more past the eop_desc क्रम start of next pkt */
		tx_buffer++;
		i++;
		अगर (unlikely(i == tx_ring->count)) अणु
			i = 0;
			tx_buffer = tx_ring->tx_buffer_info;
		पूर्ण
	पूर्ण

	/* reset BQL क्रम queue */
	अगर (!ring_is_xdp(tx_ring))
		netdev_tx_reset_queue(txring_txq(tx_ring));

out:
	/* reset next_to_use and next_to_clean */
	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
पूर्ण

/**
 * ixgbe_clean_all_rx_rings - Free Rx Buffers क्रम all queues
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम ixgbe_clean_all_rx_rings(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		ixgbe_clean_rx_ring(adapter->rx_ring[i]);
पूर्ण

/**
 * ixgbe_clean_all_tx_rings - Free Tx Buffers क्रम all queues
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम ixgbe_clean_all_tx_rings(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		ixgbe_clean_tx_ring(adapter->tx_ring[i]);
	क्रम (i = 0; i < adapter->num_xdp_queues; i++)
		ixgbe_clean_tx_ring(adapter->xdp_ring[i]);
पूर्ण

अटल व्योम ixgbe_fdir_filter_निकास(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा hlist_node *node2;
	काष्ठा ixgbe_fdir_filter *filter;

	spin_lock(&adapter->fdir_perfect_lock);

	hlist_क्रम_each_entry_safe(filter, node2,
				  &adapter->fdir_filter_list, fdir_node) अणु
		hlist_del(&filter->fdir_node);
		kमुक्त(filter);
	पूर्ण
	adapter->fdir_filter_count = 0;

	spin_unlock(&adapter->fdir_perfect_lock);
पूर्ण

व्योम ixgbe_करोwn(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i;

	/* संकेत that we are करोwn to the पूर्णांकerrupt handler */
	अगर (test_and_set_bit(__IXGBE_DOWN, &adapter->state))
		वापस; /* करो nothing अगर alपढ़ोy करोwn */

	/* Shut off incoming Tx traffic */
	netअगर_tx_stop_all_queues(netdev);

	/* call carrier off first to aव्योम false dev_watchकरोg समयouts */
	netअगर_carrier_off(netdev);
	netअगर_tx_disable(netdev);

	/* Disable Rx */
	ixgbe_disable_rx(adapter);

	/* synchronize_rcu() needed क्रम pending XDP buffers to drain */
	अगर (adapter->xdp_ring[0])
		synchronize_rcu();

	ixgbe_irq_disable(adapter);

	ixgbe_napi_disable_all(adapter);

	clear_bit(__IXGBE_RESET_REQUESTED, &adapter->state);
	adapter->flags2 &= ~IXGBE_FLAG2_Fसूची_REQUIRES_REINIT;
	adapter->flags &= ~IXGBE_FLAG_NEED_LINK_UPDATE;

	del_समयr_sync(&adapter->service_समयr);

	अगर (adapter->num_vfs) अणु
		/* Clear EITR Select mapping */
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_EITRSEL, 0);

		/* Mark all the VFs as inactive */
		क्रम (i = 0 ; i < adapter->num_vfs; i++)
			adapter->vfinfo[i].clear_to_send = false;

		/* ping all the active vfs to let them know we are going करोwn */
		ixgbe_ping_all_vfs(adapter);

		/* Disable all VFTE/VFRE TX/RX */
		ixgbe_disable_tx_rx(adapter);
	पूर्ण

	/* disable transmits in the hardware now that पूर्णांकerrupts are off */
	ixgbe_disable_tx(adapter);

	अगर (!pci_channel_offline(adapter->pdev))
		ixgbe_reset(adapter);

	/* घातer करोwn the optics क्रम 82599 SFP+ fiber */
	अगर (hw->mac.ops.disable_tx_laser)
		hw->mac.ops.disable_tx_laser(hw);

	ixgbe_clean_all_tx_rings(adapter);
	ixgbe_clean_all_rx_rings(adapter);
पूर्ण

/**
 * ixgbe_set_eee_capable - helper function to determine EEE support on X550
 * @adapter: board निजी काष्ठाure
 */
अटल व्योम ixgbe_set_eee_capable(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	चयन (hw->device_id) अणु
	हाल IXGBE_DEV_ID_X550EM_A_1G_T:
	हाल IXGBE_DEV_ID_X550EM_A_1G_T_L:
		अगर (!hw->phy.eee_speeds_supported)
			अवरोध;
		adapter->flags2 |= IXGBE_FLAG2_EEE_CAPABLE;
		अगर (!hw->phy.eee_speeds_advertised)
			अवरोध;
		adapter->flags2 |= IXGBE_FLAG2_EEE_ENABLED;
		अवरोध;
	शेष:
		adapter->flags2 &= ~IXGBE_FLAG2_EEE_CAPABLE;
		adapter->flags2 &= ~IXGBE_FLAG2_EEE_ENABLED;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ixgbe_tx_समयout - Respond to a Tx Hang
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @txqueue: queue number that समयd out
 **/
अटल व्योम ixgbe_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक __always_unused txqueue)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	/* Do the reset outside of पूर्णांकerrupt context */
	ixgbe_tx_समयout_reset(adapter);
पूर्ण

#अगर_घोषित CONFIG_IXGBE_DCB
अटल व्योम ixgbe_init_dcb(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा tc_configuration *tc;
	पूर्णांक j;

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
	हाल ixgbe_mac_82599EB:
		adapter->dcb_cfg.num_tcs.pg_tcs = MAX_TRAFFIC_CLASS;
		adapter->dcb_cfg.num_tcs.pfc_tcs = MAX_TRAFFIC_CLASS;
		अवरोध;
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
		adapter->dcb_cfg.num_tcs.pg_tcs = X540_TRAFFIC_CLASS;
		adapter->dcb_cfg.num_tcs.pfc_tcs = X540_TRAFFIC_CLASS;
		अवरोध;
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
	शेष:
		adapter->dcb_cfg.num_tcs.pg_tcs = DEF_TRAFFIC_CLASS;
		adapter->dcb_cfg.num_tcs.pfc_tcs = DEF_TRAFFIC_CLASS;
		अवरोध;
	पूर्ण

	/* Configure DCB traffic classes */
	क्रम (j = 0; j < MAX_TRAFFIC_CLASS; j++) अणु
		tc = &adapter->dcb_cfg.tc_config[j];
		tc->path[DCB_TX_CONFIG].bwg_id = 0;
		tc->path[DCB_TX_CONFIG].bwg_percent = 12 + (j & 1);
		tc->path[DCB_RX_CONFIG].bwg_id = 0;
		tc->path[DCB_RX_CONFIG].bwg_percent = 12 + (j & 1);
		tc->dcb_pfc = pfc_disabled;
	पूर्ण

	/* Initialize शेष user to priority mapping, UPx->TC0 */
	tc = &adapter->dcb_cfg.tc_config[0];
	tc->path[DCB_TX_CONFIG].up_to_tc_biपंचांगap = 0xFF;
	tc->path[DCB_RX_CONFIG].up_to_tc_biपंचांगap = 0xFF;

	adapter->dcb_cfg.bw_percentage[DCB_TX_CONFIG][0] = 100;
	adapter->dcb_cfg.bw_percentage[DCB_RX_CONFIG][0] = 100;
	adapter->dcb_cfg.pfc_mode_enable = false;
	adapter->dcb_set_biपंचांगap = 0x00;
	अगर (adapter->flags & IXGBE_FLAG_DCB_CAPABLE)
		adapter->dcbx_cap = DCB_CAP_DCBX_HOST | DCB_CAP_DCBX_VER_CEE;
	स_नकल(&adapter->temp_dcb_cfg, &adapter->dcb_cfg,
	       माप(adapter->temp_dcb_cfg));
पूर्ण
#पूर्ण_अगर

/**
 * ixgbe_sw_init - Initialize general software काष्ठाures (काष्ठा ixgbe_adapter)
 * @adapter: board निजी काष्ठाure to initialize
 * @ii: poपूर्णांकer to ixgbe_info क्रम device
 *
 * ixgbe_sw_init initializes the Adapter निजी data काष्ठाure.
 * Fields are initialized based on PCI device inक्रमmation and
 * OS network device settings (MTU size).
 **/
अटल पूर्णांक ixgbe_sw_init(काष्ठा ixgbe_adapter *adapter,
			 स्थिर काष्ठा ixgbe_info *ii)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा pci_dev *pdev = adapter->pdev;
	अचिन्हित पूर्णांक rss, fdir;
	u32 fwsm;
	पूर्णांक i;

	/* PCI config space info */

	hw->venकरोr_id = pdev->venकरोr;
	hw->device_id = pdev->device;
	hw->revision_id = pdev->revision;
	hw->subप्रणाली_venकरोr_id = pdev->subप्रणाली_venकरोr;
	hw->subप्रणाली_device_id = pdev->subप्रणाली_device;

	/* get_invariants needs the device IDs */
	ii->get_invariants(hw);

	/* Set common capability flags and settings */
	rss = min_t(पूर्णांक, ixgbe_max_rss_indices(adapter), num_online_cpus());
	adapter->ring_feature[RING_F_RSS].limit = rss;
	adapter->flags2 |= IXGBE_FLAG2_RSC_CAPABLE;
	adapter->max_q_vectors = MAX_Q_VECTORS_82599;
	adapter->atr_sample_rate = 20;
	fdir = min_t(पूर्णांक, IXGBE_MAX_Fसूची_INDICES, num_online_cpus());
	adapter->ring_feature[RING_F_Fसूची].limit = fdir;
	adapter->fdir_pballoc = IXGBE_Fसूची_PBALLOC_64K;
	adapter->ring_feature[RING_F_VMDQ].limit = 1;
#अगर_घोषित CONFIG_IXGBE_DCA
	adapter->flags |= IXGBE_FLAG_DCA_CAPABLE;
#पूर्ण_अगर
#अगर_घोषित CONFIG_IXGBE_DCB
	adapter->flags |= IXGBE_FLAG_DCB_CAPABLE;
	adapter->flags &= ~IXGBE_FLAG_DCB_ENABLED;
#पूर्ण_अगर
#अगर_घोषित IXGBE_FCOE
	adapter->flags |= IXGBE_FLAG_FCOE_CAPABLE;
	adapter->flags &= ~IXGBE_FLAG_FCOE_ENABLED;
#अगर_घोषित CONFIG_IXGBE_DCB
	/* Default traffic class to use क्रम FCoE */
	adapter->fcoe.up = IXGBE_FCOE_DEFTC;
#पूर्ण_अगर /* CONFIG_IXGBE_DCB */
#पूर्ण_अगर /* IXGBE_FCOE */

	/* initialize अटल ixgbe jump table entries */
	adapter->jump_tables[0] = kzalloc(माप(*adapter->jump_tables[0]),
					  GFP_KERNEL);
	अगर (!adapter->jump_tables[0])
		वापस -ENOMEM;
	adapter->jump_tables[0]->mat = ixgbe_ipv4_fields;

	क्रम (i = 1; i < IXGBE_MAX_LINK_HANDLE; i++)
		adapter->jump_tables[i] = शून्य;

	adapter->mac_table = kसुस्मृति(hw->mac.num_rar_entries,
				     माप(काष्ठा ixgbe_mac_addr),
				     GFP_KERNEL);
	अगर (!adapter->mac_table)
		वापस -ENOMEM;

	अगर (ixgbe_init_rss_key(adapter))
		वापस -ENOMEM;

	adapter->af_xdp_zc_qps = biपंचांगap_zalloc(MAX_XDP_QUEUES, GFP_KERNEL);
	अगर (!adapter->af_xdp_zc_qps)
		वापस -ENOMEM;

	/* Set MAC specअगरic capability flags and exceptions */
	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		adapter->flags2 &= ~IXGBE_FLAG2_RSC_CAPABLE;

		अगर (hw->device_id == IXGBE_DEV_ID_82598AT)
			adapter->flags |= IXGBE_FLAG_FAN_FAIL_CAPABLE;

		adapter->max_q_vectors = MAX_Q_VECTORS_82598;
		adapter->ring_feature[RING_F_Fसूची].limit = 0;
		adapter->atr_sample_rate = 0;
		adapter->fdir_pballoc = 0;
#अगर_घोषित IXGBE_FCOE
		adapter->flags &= ~IXGBE_FLAG_FCOE_CAPABLE;
		adapter->flags &= ~IXGBE_FLAG_FCOE_ENABLED;
#अगर_घोषित CONFIG_IXGBE_DCB
		adapter->fcoe.up = 0;
#पूर्ण_अगर /* IXGBE_DCB */
#पूर्ण_अगर /* IXGBE_FCOE */
		अवरोध;
	हाल ixgbe_mac_82599EB:
		अगर (hw->device_id == IXGBE_DEV_ID_82599_T3_LOM)
			adapter->flags2 |= IXGBE_FLAG2_TEMP_SENSOR_CAPABLE;
		अवरोध;
	हाल ixgbe_mac_X540:
		fwsm = IXGBE_READ_REG(hw, IXGBE_FWSM(hw));
		अगर (fwsm & IXGBE_FWSM_TS_ENABLED)
			adapter->flags2 |= IXGBE_FLAG2_TEMP_SENSOR_CAPABLE;
		अवरोध;
	हाल ixgbe_mac_x550em_a:
		चयन (hw->device_id) अणु
		हाल IXGBE_DEV_ID_X550EM_A_1G_T:
		हाल IXGBE_DEV_ID_X550EM_A_1G_T_L:
			adapter->flags2 |= IXGBE_FLAG2_TEMP_SENSOR_CAPABLE;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		fallthrough;
	हाल ixgbe_mac_X550EM_x:
#अगर_घोषित CONFIG_IXGBE_DCB
		adapter->flags &= ~IXGBE_FLAG_DCB_CAPABLE;
#पूर्ण_अगर
#अगर_घोषित IXGBE_FCOE
		adapter->flags &= ~IXGBE_FLAG_FCOE_CAPABLE;
#अगर_घोषित CONFIG_IXGBE_DCB
		adapter->fcoe.up = 0;
#पूर्ण_अगर /* IXGBE_DCB */
#पूर्ण_अगर /* IXGBE_FCOE */
		fallthrough;
	हाल ixgbe_mac_X550:
		अगर (hw->mac.type == ixgbe_mac_X550)
			adapter->flags2 |= IXGBE_FLAG2_TEMP_SENSOR_CAPABLE;
#अगर_घोषित CONFIG_IXGBE_DCA
		adapter->flags &= ~IXGBE_FLAG_DCA_CAPABLE;
#पूर्ण_अगर
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

#अगर_घोषित IXGBE_FCOE
	/* FCoE support exists, always init the FCoE lock */
	spin_lock_init(&adapter->fcoe.lock);

#पूर्ण_अगर
	/* n-tuple support exists, always init our spinlock */
	spin_lock_init(&adapter->fdir_perfect_lock);

#अगर_घोषित CONFIG_IXGBE_DCB
	ixgbe_init_dcb(adapter);
#पूर्ण_अगर
	ixgbe_init_ipsec_offload(adapter);

	/* शेष flow control settings */
	hw->fc.requested_mode = ixgbe_fc_full;
	hw->fc.current_mode = ixgbe_fc_full;	/* init क्रम ethtool output */
	ixgbe_pbthresh_setup(adapter);
	hw->fc.छोड़ो_समय = IXGBE_DEFAULT_FCPAUSE;
	hw->fc.send_xon = true;
	hw->fc.disable_fc_स्वतःneg = ixgbe_device_supports_स्वतःneg_fc(hw);

#अगर_घोषित CONFIG_PCI_IOV
	अगर (max_vfs > 0)
		e_dev_warn("Enabling SR-IOV VFs using the max_vfs module parameter is deprecated - please use the pci sysfs interface instead.\n");

	/* assign number of SR-IOV VFs */
	अगर (hw->mac.type != ixgbe_mac_82598EB) अणु
		अगर (max_vfs > IXGBE_MAX_VFS_DRV_LIMIT) अणु
			max_vfs = 0;
			e_dev_warn("max_vfs parameter out of range. Not assigning any SR-IOV VFs\n");
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_IOV */

	/* enable itr by शेष in dynamic mode */
	adapter->rx_itr_setting = 1;
	adapter->tx_itr_setting = 1;

	/* set शेष ring sizes */
	adapter->tx_ring_count = IXGBE_DEFAULT_TXD;
	adapter->rx_ring_count = IXGBE_DEFAULT_RXD;

	/* set शेष work limits */
	adapter->tx_work_limit = IXGBE_DEFAULT_TX_WORK;

	/* initialize eeprom parameters */
	अगर (ixgbe_init_eeprom_params_generic(hw)) अणु
		e_dev_err("EEPROM initialization failed\n");
		वापस -EIO;
	पूर्ण

	/* PF holds first pool slot */
	set_bit(0, adapter->fwd_biपंचांगask);
	set_bit(__IXGBE_DOWN, &adapter->state);

	वापस 0;
पूर्ण

/**
 * ixgbe_setup_tx_resources - allocate Tx resources (Descriptors)
 * @tx_ring:    tx descriptor ring (क्रम a specअगरic queue) to setup
 *
 * Return 0 on success, negative on failure
 **/
पूर्णांक ixgbe_setup_tx_resources(काष्ठा ixgbe_ring *tx_ring)
अणु
	काष्ठा device *dev = tx_ring->dev;
	पूर्णांक orig_node = dev_to_node(dev);
	पूर्णांक ring_node = NUMA_NO_NODE;
	पूर्णांक size;

	size = माप(काष्ठा ixgbe_tx_buffer) * tx_ring->count;

	अगर (tx_ring->q_vector)
		ring_node = tx_ring->q_vector->numa_node;

	tx_ring->tx_buffer_info = vदो_स्मृति_node(size, ring_node);
	अगर (!tx_ring->tx_buffer_info)
		tx_ring->tx_buffer_info = vदो_स्मृति(size);
	अगर (!tx_ring->tx_buffer_info)
		जाओ err;

	/* round up to nearest 4K */
	tx_ring->size = tx_ring->count * माप(जोड़ ixgbe_adv_tx_desc);
	tx_ring->size = ALIGN(tx_ring->size, 4096);

	set_dev_node(dev, ring_node);
	tx_ring->desc = dma_alloc_coherent(dev,
					   tx_ring->size,
					   &tx_ring->dma,
					   GFP_KERNEL);
	set_dev_node(dev, orig_node);
	अगर (!tx_ring->desc)
		tx_ring->desc = dma_alloc_coherent(dev, tx_ring->size,
						   &tx_ring->dma, GFP_KERNEL);
	अगर (!tx_ring->desc)
		जाओ err;

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
	वापस 0;

err:
	vमुक्त(tx_ring->tx_buffer_info);
	tx_ring->tx_buffer_info = शून्य;
	dev_err(dev, "Unable to allocate memory for the Tx descriptor ring\n");
	वापस -ENOMEM;
पूर्ण

/**
 * ixgbe_setup_all_tx_resources - allocate all queues Tx resources
 * @adapter: board निजी काष्ठाure
 *
 * If this function वापसs with an error, then it's possible one or
 * more of the rings is populated (जबतक the rest are not).  It is the
 * callers duty to clean those orphaned rings.
 *
 * Return 0 on success, negative on failure
 **/
अटल पूर्णांक ixgbe_setup_all_tx_resources(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक i, j = 0, err = 0;

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		err = ixgbe_setup_tx_resources(adapter->tx_ring[i]);
		अगर (!err)
			जारी;

		e_err(probe, "Allocation for Tx Queue %u failed\n", i);
		जाओ err_setup_tx;
	पूर्ण
	क्रम (j = 0; j < adapter->num_xdp_queues; j++) अणु
		err = ixgbe_setup_tx_resources(adapter->xdp_ring[j]);
		अगर (!err)
			जारी;

		e_err(probe, "Allocation for Tx Queue %u failed\n", j);
		जाओ err_setup_tx;
	पूर्ण

	वापस 0;
err_setup_tx:
	/* शुरुआत the index मुक्तing the rings as we go */
	जबतक (j--)
		ixgbe_मुक्त_tx_resources(adapter->xdp_ring[j]);
	जबतक (i--)
		ixgbe_मुक्त_tx_resources(adapter->tx_ring[i]);
	वापस err;
पूर्ण

अटल पूर्णांक ixgbe_rx_napi_id(काष्ठा ixgbe_ring *rx_ring)
अणु
	काष्ठा ixgbe_q_vector *q_vector = rx_ring->q_vector;

	वापस q_vector ? q_vector->napi.napi_id : 0;
पूर्ण

/**
 * ixgbe_setup_rx_resources - allocate Rx resources (Descriptors)
 * @adapter: poपूर्णांकer to ixgbe_adapter
 * @rx_ring:    rx descriptor ring (क्रम a specअगरic queue) to setup
 *
 * Returns 0 on success, negative on failure
 **/
पूर्णांक ixgbe_setup_rx_resources(काष्ठा ixgbe_adapter *adapter,
			     काष्ठा ixgbe_ring *rx_ring)
अणु
	काष्ठा device *dev = rx_ring->dev;
	पूर्णांक orig_node = dev_to_node(dev);
	पूर्णांक ring_node = NUMA_NO_NODE;
	पूर्णांक size;

	size = माप(काष्ठा ixgbe_rx_buffer) * rx_ring->count;

	अगर (rx_ring->q_vector)
		ring_node = rx_ring->q_vector->numa_node;

	rx_ring->rx_buffer_info = vदो_स्मृति_node(size, ring_node);
	अगर (!rx_ring->rx_buffer_info)
		rx_ring->rx_buffer_info = vदो_स्मृति(size);
	अगर (!rx_ring->rx_buffer_info)
		जाओ err;

	/* Round up to nearest 4K */
	rx_ring->size = rx_ring->count * माप(जोड़ ixgbe_adv_rx_desc);
	rx_ring->size = ALIGN(rx_ring->size, 4096);

	set_dev_node(dev, ring_node);
	rx_ring->desc = dma_alloc_coherent(dev,
					   rx_ring->size,
					   &rx_ring->dma,
					   GFP_KERNEL);
	set_dev_node(dev, orig_node);
	अगर (!rx_ring->desc)
		rx_ring->desc = dma_alloc_coherent(dev, rx_ring->size,
						   &rx_ring->dma, GFP_KERNEL);
	अगर (!rx_ring->desc)
		जाओ err;

	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;

	/* XDP RX-queue info */
	अगर (xdp_rxq_info_reg(&rx_ring->xdp_rxq, adapter->netdev,
			     rx_ring->queue_index, ixgbe_rx_napi_id(rx_ring)) < 0)
		जाओ err;

	rx_ring->xdp_prog = adapter->xdp_prog;

	वापस 0;
err:
	vमुक्त(rx_ring->rx_buffer_info);
	rx_ring->rx_buffer_info = शून्य;
	dev_err(dev, "Unable to allocate memory for the Rx descriptor ring\n");
	वापस -ENOMEM;
पूर्ण

/**
 * ixgbe_setup_all_rx_resources - allocate all queues Rx resources
 * @adapter: board निजी काष्ठाure
 *
 * If this function वापसs with an error, then it's possible one or
 * more of the rings is populated (जबतक the rest are not).  It is the
 * callers duty to clean those orphaned rings.
 *
 * Return 0 on success, negative on failure
 **/
अटल पूर्णांक ixgbe_setup_all_rx_resources(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		err = ixgbe_setup_rx_resources(adapter, adapter->rx_ring[i]);
		अगर (!err)
			जारी;

		e_err(probe, "Allocation for Rx Queue %u failed\n", i);
		जाओ err_setup_rx;
	पूर्ण

#अगर_घोषित IXGBE_FCOE
	err = ixgbe_setup_fcoe_ddp_resources(adapter);
	अगर (!err)
#पूर्ण_अगर
		वापस 0;
err_setup_rx:
	/* शुरुआत the index मुक्तing the rings as we go */
	जबतक (i--)
		ixgbe_मुक्त_rx_resources(adapter->rx_ring[i]);
	वापस err;
पूर्ण

/**
 * ixgbe_मुक्त_tx_resources - Free Tx Resources per Queue
 * @tx_ring: Tx descriptor ring क्रम a specअगरic queue
 *
 * Free all transmit software resources
 **/
व्योम ixgbe_मुक्त_tx_resources(काष्ठा ixgbe_ring *tx_ring)
अणु
	ixgbe_clean_tx_ring(tx_ring);

	vमुक्त(tx_ring->tx_buffer_info);
	tx_ring->tx_buffer_info = शून्य;

	/* अगर not set, then करोn't मुक्त */
	अगर (!tx_ring->desc)
		वापस;

	dma_मुक्त_coherent(tx_ring->dev, tx_ring->size,
			  tx_ring->desc, tx_ring->dma);

	tx_ring->desc = शून्य;
पूर्ण

/**
 * ixgbe_मुक्त_all_tx_resources - Free Tx Resources क्रम All Queues
 * @adapter: board निजी काष्ठाure
 *
 * Free all transmit software resources
 **/
अटल व्योम ixgbe_मुक्त_all_tx_resources(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		अगर (adapter->tx_ring[i]->desc)
			ixgbe_मुक्त_tx_resources(adapter->tx_ring[i]);
	क्रम (i = 0; i < adapter->num_xdp_queues; i++)
		अगर (adapter->xdp_ring[i]->desc)
			ixgbe_मुक्त_tx_resources(adapter->xdp_ring[i]);
पूर्ण

/**
 * ixgbe_मुक्त_rx_resources - Free Rx Resources
 * @rx_ring: ring to clean the resources from
 *
 * Free all receive software resources
 **/
व्योम ixgbe_मुक्त_rx_resources(काष्ठा ixgbe_ring *rx_ring)
अणु
	ixgbe_clean_rx_ring(rx_ring);

	rx_ring->xdp_prog = शून्य;
	xdp_rxq_info_unreg(&rx_ring->xdp_rxq);
	vमुक्त(rx_ring->rx_buffer_info);
	rx_ring->rx_buffer_info = शून्य;

	/* अगर not set, then करोn't मुक्त */
	अगर (!rx_ring->desc)
		वापस;

	dma_मुक्त_coherent(rx_ring->dev, rx_ring->size,
			  rx_ring->desc, rx_ring->dma);

	rx_ring->desc = शून्य;
पूर्ण

/**
 * ixgbe_मुक्त_all_rx_resources - Free Rx Resources क्रम All Queues
 * @adapter: board निजी काष्ठाure
 *
 * Free all receive software resources
 **/
अटल व्योम ixgbe_मुक्त_all_rx_resources(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक i;

#अगर_घोषित IXGBE_FCOE
	ixgbe_मुक्त_fcoe_ddp_resources(adapter);

#पूर्ण_अगर
	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		अगर (adapter->rx_ring[i]->desc)
			ixgbe_मुक्त_rx_resources(adapter->rx_ring[i]);
पूर्ण

/**
 * ixgbe_change_mtu - Change the Maximum Transfer Unit
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @new_mtu: new value क्रम maximum frame size
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक ixgbe_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	अगर (adapter->xdp_prog) अणु
		पूर्णांक new_frame_size = new_mtu + ETH_HLEN + ETH_FCS_LEN +
				     VLAN_HLEN;
		पूर्णांक i;

		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			काष्ठा ixgbe_ring *ring = adapter->rx_ring[i];

			अगर (new_frame_size > ixgbe_rx_bufsz(ring)) अणु
				e_warn(probe, "Requested MTU size is not supported with XDP\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * For 82599EB we cannot allow legacy VFs to enable their receive
	 * paths when MTU greater than 1500 is configured.  So display a
	 * warning that legacy VFs will be disabled.
	 */
	अगर ((adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) &&
	    (adapter->hw.mac.type == ixgbe_mac_82599EB) &&
	    (new_mtu > ETH_DATA_LEN))
		e_warn(probe, "Setting MTU > 1500 will disable legacy VFs\n");

	netdev_dbg(netdev, "changing MTU from %d to %d\n",
		   netdev->mtu, new_mtu);

	/* must set new MTU beक्रमe calling करोwn or up */
	netdev->mtu = new_mtu;

	अगर (netअगर_running(netdev))
		ixgbe_reinit_locked(adapter);

	वापस 0;
पूर्ण

/**
 * ixgbe_खोलो - Called when a network पूर्णांकerface is made active
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0 on success, negative value on failure
 *
 * The खोलो entry poपूर्णांक is called when a network पूर्णांकerface is made
 * active by the प्रणाली (IFF_UP).  At this poपूर्णांक all resources needed
 * क्रम transmit and receive operations are allocated, the पूर्णांकerrupt
 * handler is रेजिस्टरed with the OS, the watchकरोg समयr is started,
 * and the stack is notअगरied that the पूर्णांकerface is पढ़ोy.
 **/
पूर्णांक ixgbe_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक err, queues;

	/* disallow खोलो during test */
	अगर (test_bit(__IXGBE_TESTING, &adapter->state))
		वापस -EBUSY;

	netअगर_carrier_off(netdev);

	/* allocate transmit descriptors */
	err = ixgbe_setup_all_tx_resources(adapter);
	अगर (err)
		जाओ err_setup_tx;

	/* allocate receive descriptors */
	err = ixgbe_setup_all_rx_resources(adapter);
	अगर (err)
		जाओ err_setup_rx;

	ixgbe_configure(adapter);

	err = ixgbe_request_irq(adapter);
	अगर (err)
		जाओ err_req_irq;

	/* Notअगरy the stack of the actual queue counts. */
	queues = adapter->num_tx_queues;
	err = netअगर_set_real_num_tx_queues(netdev, queues);
	अगर (err)
		जाओ err_set_queues;

	queues = adapter->num_rx_queues;
	err = netअगर_set_real_num_rx_queues(netdev, queues);
	अगर (err)
		जाओ err_set_queues;

	ixgbe_ptp_init(adapter);

	ixgbe_up_complete(adapter);

	udp_tunnel_nic_reset_ntf(netdev);

	वापस 0;

err_set_queues:
	ixgbe_मुक्त_irq(adapter);
err_req_irq:
	ixgbe_मुक्त_all_rx_resources(adapter);
	अगर (hw->phy.ops.set_phy_घातer && !adapter->wol)
		hw->phy.ops.set_phy_घातer(&adapter->hw, false);
err_setup_rx:
	ixgbe_मुक्त_all_tx_resources(adapter);
err_setup_tx:
	ixgbe_reset(adapter);

	वापस err;
पूर्ण

अटल व्योम ixgbe_बंद_suspend(काष्ठा ixgbe_adapter *adapter)
अणु
	ixgbe_ptp_suspend(adapter);

	अगर (adapter->hw.phy.ops.enter_lplu) अणु
		adapter->hw.phy.reset_disable = true;
		ixgbe_करोwn(adapter);
		adapter->hw.phy.ops.enter_lplu(&adapter->hw);
		adapter->hw.phy.reset_disable = false;
	पूर्ण अन्यथा अणु
		ixgbe_करोwn(adapter);
	पूर्ण

	ixgbe_मुक्त_irq(adapter);

	ixgbe_मुक्त_all_tx_resources(adapter);
	ixgbe_मुक्त_all_rx_resources(adapter);
पूर्ण

/**
 * ixgbe_बंद - Disables a network पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0, this is not allowed to fail
 *
 * The बंद entry poपूर्णांक is called when an पूर्णांकerface is de-activated
 * by the OS.  The hardware is still under the drivers control, but
 * needs to be disabled.  A global MAC reset is issued to stop the
 * hardware, and all transmit and receive resources are मुक्तd.
 **/
पूर्णांक ixgbe_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	ixgbe_ptp_stop(adapter);

	अगर (netअगर_device_present(netdev))
		ixgbe_बंद_suspend(adapter);

	ixgbe_fdir_filter_निकास(adapter);

	ixgbe_release_hw_control(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ixgbe_resume(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा ixgbe_adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = adapter->netdev;
	u32 err;

	adapter->hw.hw_addr = adapter->io_addr;

	err = pci_enable_device_mem(pdev);
	अगर (err) अणु
		e_dev_err("Cannot enable PCI device from suspend\n");
		वापस err;
	पूर्ण
	smp_mb__beक्रमe_atomic();
	clear_bit(__IXGBE_DISABLED, &adapter->state);
	pci_set_master(pdev);

	device_wakeup_disable(dev_d);

	ixgbe_reset(adapter);

	IXGBE_WRITE_REG(&adapter->hw, IXGBE_WUS, ~0);

	rtnl_lock();
	err = ixgbe_init_पूर्णांकerrupt_scheme(adapter);
	अगर (!err && netअगर_running(netdev))
		err = ixgbe_खोलो(netdev);


	अगर (!err)
		netअगर_device_attach(netdev);
	rtnl_unlock();

	वापस err;
पूर्ण

अटल पूर्णांक __ixgbe_shutकरोwn(काष्ठा pci_dev *pdev, bool *enable_wake)
अणु
	काष्ठा ixgbe_adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 ctrl;
	u32 wufc = adapter->wol;

	rtnl_lock();
	netअगर_device_detach(netdev);

	अगर (netअगर_running(netdev))
		ixgbe_बंद_suspend(adapter);

	ixgbe_clear_पूर्णांकerrupt_scheme(adapter);
	rtnl_unlock();

	अगर (hw->mac.ops.stop_link_on_d3)
		hw->mac.ops.stop_link_on_d3(hw);

	अगर (wufc) अणु
		u32 fctrl;

		ixgbe_set_rx_mode(netdev);

		/* enable the optics क्रम 82599 SFP+ fiber as we can WoL */
		अगर (hw->mac.ops.enable_tx_laser)
			hw->mac.ops.enable_tx_laser(hw);

		/* enable the reception of multicast packets */
		fctrl = IXGBE_READ_REG(hw, IXGBE_FCTRL);
		fctrl |= IXGBE_FCTRL_MPE;
		IXGBE_WRITE_REG(hw, IXGBE_FCTRL, fctrl);

		ctrl = IXGBE_READ_REG(hw, IXGBE_CTRL);
		ctrl |= IXGBE_CTRL_GIO_DIS;
		IXGBE_WRITE_REG(hw, IXGBE_CTRL, ctrl);

		IXGBE_WRITE_REG(hw, IXGBE_WUFC, wufc);
	पूर्ण अन्यथा अणु
		IXGBE_WRITE_REG(hw, IXGBE_WUC, 0);
		IXGBE_WRITE_REG(hw, IXGBE_WUFC, 0);
	पूर्ण

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		pci_wake_from_d3(pdev, false);
		अवरोध;
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		pci_wake_from_d3(pdev, !!wufc);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	*enable_wake = !!wufc;
	अगर (hw->phy.ops.set_phy_घातer && !*enable_wake)
		hw->phy.ops.set_phy_घातer(hw, false);

	ixgbe_release_hw_control(adapter);

	अगर (!test_and_set_bit(__IXGBE_DISABLED, &adapter->state))
		pci_disable_device(pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ixgbe_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	पूर्णांक retval;
	bool wake;

	retval = __ixgbe_shutकरोwn(pdev, &wake);

	device_set_wakeup_enable(dev_d, wake);

	वापस retval;
पूर्ण

अटल व्योम ixgbe_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	bool wake;

	__ixgbe_shutकरोwn(pdev, &wake);

	अगर (प्रणाली_state == SYSTEM_POWER_OFF) अणु
		pci_wake_from_d3(pdev, wake);
		pci_set_घातer_state(pdev, PCI_D3hot);
	पूर्ण
पूर्ण

/**
 * ixgbe_update_stats - Update the board statistics counters.
 * @adapter: board निजी काष्ठाure
 **/
व्योम ixgbe_update_stats(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा ixgbe_hw_stats *hwstats = &adapter->stats;
	u64 total_mpc = 0;
	u32 i, missed_rx = 0, mpc, bprc, lxon, lxoff, xon_off_tot;
	u64 non_eop_descs = 0, restart_queue = 0, tx_busy = 0;
	u64 alloc_rx_page_failed = 0, alloc_rx_buff_failed = 0;
	u64 alloc_rx_page = 0;
	u64 bytes = 0, packets = 0, hw_csum_rx_error = 0;

	अगर (test_bit(__IXGBE_DOWN, &adapter->state) ||
	    test_bit(__IXGBE_RESETTING, &adapter->state))
		वापस;

	अगर (adapter->flags2 & IXGBE_FLAG2_RSC_ENABLED) अणु
		u64 rsc_count = 0;
		u64 rsc_flush = 0;
		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			rsc_count += adapter->rx_ring[i]->rx_stats.rsc_count;
			rsc_flush += adapter->rx_ring[i]->rx_stats.rsc_flush;
		पूर्ण
		adapter->rsc_total_count = rsc_count;
		adapter->rsc_total_flush = rsc_flush;
	पूर्ण

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा ixgbe_ring *rx_ring = READ_ONCE(adapter->rx_ring[i]);

		अगर (!rx_ring)
			जारी;
		non_eop_descs += rx_ring->rx_stats.non_eop_descs;
		alloc_rx_page += rx_ring->rx_stats.alloc_rx_page;
		alloc_rx_page_failed += rx_ring->rx_stats.alloc_rx_page_failed;
		alloc_rx_buff_failed += rx_ring->rx_stats.alloc_rx_buff_failed;
		hw_csum_rx_error += rx_ring->rx_stats.csum_err;
		bytes += rx_ring->stats.bytes;
		packets += rx_ring->stats.packets;
	पूर्ण
	adapter->non_eop_descs = non_eop_descs;
	adapter->alloc_rx_page = alloc_rx_page;
	adapter->alloc_rx_page_failed = alloc_rx_page_failed;
	adapter->alloc_rx_buff_failed = alloc_rx_buff_failed;
	adapter->hw_csum_rx_error = hw_csum_rx_error;
	netdev->stats.rx_bytes = bytes;
	netdev->stats.rx_packets = packets;

	bytes = 0;
	packets = 0;
	/* gather some stats to the adapter काष्ठा that are per queue */
	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		काष्ठा ixgbe_ring *tx_ring = READ_ONCE(adapter->tx_ring[i]);

		अगर (!tx_ring)
			जारी;
		restart_queue += tx_ring->tx_stats.restart_queue;
		tx_busy += tx_ring->tx_stats.tx_busy;
		bytes += tx_ring->stats.bytes;
		packets += tx_ring->stats.packets;
	पूर्ण
	क्रम (i = 0; i < adapter->num_xdp_queues; i++) अणु
		काष्ठा ixgbe_ring *xdp_ring = READ_ONCE(adapter->xdp_ring[i]);

		अगर (!xdp_ring)
			जारी;
		restart_queue += xdp_ring->tx_stats.restart_queue;
		tx_busy += xdp_ring->tx_stats.tx_busy;
		bytes += xdp_ring->stats.bytes;
		packets += xdp_ring->stats.packets;
	पूर्ण
	adapter->restart_queue = restart_queue;
	adapter->tx_busy = tx_busy;
	netdev->stats.tx_bytes = bytes;
	netdev->stats.tx_packets = packets;

	hwstats->crcerrs += IXGBE_READ_REG(hw, IXGBE_CRCERRS);

	/* 8 रेजिस्टर पढ़ोs */
	क्रम (i = 0; i < 8; i++) अणु
		/* क्रम packet buffers not used, the रेजिस्टर should पढ़ो 0 */
		mpc = IXGBE_READ_REG(hw, IXGBE_MPC(i));
		missed_rx += mpc;
		hwstats->mpc[i] += mpc;
		total_mpc += hwstats->mpc[i];
		hwstats->pxontxc[i] += IXGBE_READ_REG(hw, IXGBE_PXONTXC(i));
		hwstats->pxofftxc[i] += IXGBE_READ_REG(hw, IXGBE_PXOFFTXC(i));
		चयन (hw->mac.type) अणु
		हाल ixgbe_mac_82598EB:
			hwstats->rnbc[i] += IXGBE_READ_REG(hw, IXGBE_RNBC(i));
			hwstats->qbtc[i] += IXGBE_READ_REG(hw, IXGBE_QBTC(i));
			hwstats->qbrc[i] += IXGBE_READ_REG(hw, IXGBE_QBRC(i));
			hwstats->pxonrxc[i] +=
				IXGBE_READ_REG(hw, IXGBE_PXONRXC(i));
			अवरोध;
		हाल ixgbe_mac_82599EB:
		हाल ixgbe_mac_X540:
		हाल ixgbe_mac_X550:
		हाल ixgbe_mac_X550EM_x:
		हाल ixgbe_mac_x550em_a:
			hwstats->pxonrxc[i] +=
				IXGBE_READ_REG(hw, IXGBE_PXONRXCNT(i));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/*16 रेजिस्टर पढ़ोs */
	क्रम (i = 0; i < 16; i++) अणु
		hwstats->qptc[i] += IXGBE_READ_REG(hw, IXGBE_QPTC(i));
		hwstats->qprc[i] += IXGBE_READ_REG(hw, IXGBE_QPRC(i));
		अगर ((hw->mac.type == ixgbe_mac_82599EB) ||
		    (hw->mac.type == ixgbe_mac_X540) ||
		    (hw->mac.type == ixgbe_mac_X550) ||
		    (hw->mac.type == ixgbe_mac_X550EM_x) ||
		    (hw->mac.type == ixgbe_mac_x550em_a)) अणु
			hwstats->qbtc[i] += IXGBE_READ_REG(hw, IXGBE_QBTC_L(i));
			IXGBE_READ_REG(hw, IXGBE_QBTC_H(i)); /* to clear */
			hwstats->qbrc[i] += IXGBE_READ_REG(hw, IXGBE_QBRC_L(i));
			IXGBE_READ_REG(hw, IXGBE_QBRC_H(i)); /* to clear */
		पूर्ण
	पूर्ण

	hwstats->gprc += IXGBE_READ_REG(hw, IXGBE_GPRC);
	/* work around hardware counting issue */
	hwstats->gprc -= missed_rx;

	ixgbe_update_xoff_received(adapter);

	/* 82598 hardware only has a 32 bit counter in the high रेजिस्टर */
	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		hwstats->lxonrxc += IXGBE_READ_REG(hw, IXGBE_LXONRXC);
		hwstats->gorc += IXGBE_READ_REG(hw, IXGBE_GORCH);
		hwstats->gotc += IXGBE_READ_REG(hw, IXGBE_GOTCH);
		hwstats->tor += IXGBE_READ_REG(hw, IXGBE_TORH);
		अवरोध;
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		/* OS2BMC stats are X540 and later */
		hwstats->o2bgptc += IXGBE_READ_REG(hw, IXGBE_O2BGPTC);
		hwstats->o2bspc += IXGBE_READ_REG(hw, IXGBE_O2BSPC);
		hwstats->b2ospc += IXGBE_READ_REG(hw, IXGBE_B2OSPC);
		hwstats->b2ogprc += IXGBE_READ_REG(hw, IXGBE_B2OGPRC);
		fallthrough;
	हाल ixgbe_mac_82599EB:
		क्रम (i = 0; i < 16; i++)
			adapter->hw_rx_no_dma_resources +=
					     IXGBE_READ_REG(hw, IXGBE_QPRDC(i));
		hwstats->gorc += IXGBE_READ_REG(hw, IXGBE_GORCL);
		IXGBE_READ_REG(hw, IXGBE_GORCH); /* to clear */
		hwstats->gotc += IXGBE_READ_REG(hw, IXGBE_GOTCL);
		IXGBE_READ_REG(hw, IXGBE_GOTCH); /* to clear */
		hwstats->tor += IXGBE_READ_REG(hw, IXGBE_TORL);
		IXGBE_READ_REG(hw, IXGBE_TORH); /* to clear */
		hwstats->lxonrxc += IXGBE_READ_REG(hw, IXGBE_LXONRXCNT);
		hwstats->fdirmatch += IXGBE_READ_REG(hw, IXGBE_FसूचीMATCH);
		hwstats->fdirmiss += IXGBE_READ_REG(hw, IXGBE_FसूचीMISS);
#अगर_घोषित IXGBE_FCOE
		hwstats->fccrc += IXGBE_READ_REG(hw, IXGBE_FCCRC);
		hwstats->fcoerpdc += IXGBE_READ_REG(hw, IXGBE_FCOERPDC);
		hwstats->fcoeprc += IXGBE_READ_REG(hw, IXGBE_FCOEPRC);
		hwstats->fcoeptc += IXGBE_READ_REG(hw, IXGBE_FCOEPTC);
		hwstats->fcoedwrc += IXGBE_READ_REG(hw, IXGBE_FCOEDWRC);
		hwstats->fcoedwtc += IXGBE_READ_REG(hw, IXGBE_FCOEDWTC);
		/* Add up per cpu counters क्रम total ddp aloc fail */
		अगर (adapter->fcoe.ddp_pool) अणु
			काष्ठा ixgbe_fcoe *fcoe = &adapter->fcoe;
			काष्ठा ixgbe_fcoe_ddp_pool *ddp_pool;
			अचिन्हित पूर्णांक cpu;
			u64 noddp = 0, noddp_ext_buff = 0;
			क्रम_each_possible_cpu(cpu) अणु
				ddp_pool = per_cpu_ptr(fcoe->ddp_pool, cpu);
				noddp += ddp_pool->noddp;
				noddp_ext_buff += ddp_pool->noddp_ext_buff;
			पूर्ण
			hwstats->fcoe_noddp = noddp;
			hwstats->fcoe_noddp_ext_buff = noddp_ext_buff;
		पूर्ण
#पूर्ण_अगर /* IXGBE_FCOE */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	bprc = IXGBE_READ_REG(hw, IXGBE_BPRC);
	hwstats->bprc += bprc;
	hwstats->mprc += IXGBE_READ_REG(hw, IXGBE_MPRC);
	अगर (hw->mac.type == ixgbe_mac_82598EB)
		hwstats->mprc -= bprc;
	hwstats->roc += IXGBE_READ_REG(hw, IXGBE_ROC);
	hwstats->prc64 += IXGBE_READ_REG(hw, IXGBE_PRC64);
	hwstats->prc127 += IXGBE_READ_REG(hw, IXGBE_PRC127);
	hwstats->prc255 += IXGBE_READ_REG(hw, IXGBE_PRC255);
	hwstats->prc511 += IXGBE_READ_REG(hw, IXGBE_PRC511);
	hwstats->prc1023 += IXGBE_READ_REG(hw, IXGBE_PRC1023);
	hwstats->prc1522 += IXGBE_READ_REG(hw, IXGBE_PRC1522);
	hwstats->rlec += IXGBE_READ_REG(hw, IXGBE_RLEC);
	lxon = IXGBE_READ_REG(hw, IXGBE_LXONTXC);
	hwstats->lxontxc += lxon;
	lxoff = IXGBE_READ_REG(hw, IXGBE_LXOFFTXC);
	hwstats->lxofftxc += lxoff;
	hwstats->gptc += IXGBE_READ_REG(hw, IXGBE_GPTC);
	hwstats->mptc += IXGBE_READ_REG(hw, IXGBE_MPTC);
	/*
	 * 82598 errata - tx of flow control packets is included in tx counters
	 */
	xon_off_tot = lxon + lxoff;
	hwstats->gptc -= xon_off_tot;
	hwstats->mptc -= xon_off_tot;
	hwstats->gotc -= (xon_off_tot * (ETH_ZLEN + ETH_FCS_LEN));
	hwstats->ruc += IXGBE_READ_REG(hw, IXGBE_RUC);
	hwstats->rfc += IXGBE_READ_REG(hw, IXGBE_RFC);
	hwstats->rjc += IXGBE_READ_REG(hw, IXGBE_RJC);
	hwstats->tpr += IXGBE_READ_REG(hw, IXGBE_TPR);
	hwstats->ptc64 += IXGBE_READ_REG(hw, IXGBE_PTC64);
	hwstats->ptc64 -= xon_off_tot;
	hwstats->ptc127 += IXGBE_READ_REG(hw, IXGBE_PTC127);
	hwstats->ptc255 += IXGBE_READ_REG(hw, IXGBE_PTC255);
	hwstats->ptc511 += IXGBE_READ_REG(hw, IXGBE_PTC511);
	hwstats->ptc1023 += IXGBE_READ_REG(hw, IXGBE_PTC1023);
	hwstats->ptc1522 += IXGBE_READ_REG(hw, IXGBE_PTC1522);
	hwstats->bptc += IXGBE_READ_REG(hw, IXGBE_BPTC);

	/* Fill out the OS statistics काष्ठाure */
	netdev->stats.multicast = hwstats->mprc;

	/* Rx Errors */
	netdev->stats.rx_errors = hwstats->crcerrs + hwstats->rlec;
	netdev->stats.rx_dropped = 0;
	netdev->stats.rx_length_errors = hwstats->rlec;
	netdev->stats.rx_crc_errors = hwstats->crcerrs;
	netdev->stats.rx_missed_errors = total_mpc;
पूर्ण

/**
 * ixgbe_fdir_reinit_subtask - worker thपढ़ो to reinit Fसूची filter table
 * @adapter: poपूर्णांकer to the device adapter काष्ठाure
 **/
अटल व्योम ixgbe_fdir_reinit_subtask(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i;

	अगर (!(adapter->flags2 & IXGBE_FLAG2_Fसूची_REQUIRES_REINIT))
		वापस;

	adapter->flags2 &= ~IXGBE_FLAG2_Fसूची_REQUIRES_REINIT;

	/* अगर पूर्णांकerface is करोwn करो nothing */
	अगर (test_bit(__IXGBE_DOWN, &adapter->state))
		वापस;

	/* करो nothing अगर we are not using signature filters */
	अगर (!(adapter->flags & IXGBE_FLAG_Fसूची_HASH_CAPABLE))
		वापस;

	adapter->fdir_overflow++;

	अगर (ixgbe_reinit_fdir_tables_82599(hw) == 0) अणु
		क्रम (i = 0; i < adapter->num_tx_queues; i++)
			set_bit(__IXGBE_TX_Fसूची_INIT_DONE,
				&(adapter->tx_ring[i]->state));
		क्रम (i = 0; i < adapter->num_xdp_queues; i++)
			set_bit(__IXGBE_TX_Fसूची_INIT_DONE,
				&adapter->xdp_ring[i]->state);
		/* re-enable flow director पूर्णांकerrupts */
		IXGBE_WRITE_REG(hw, IXGBE_EIMS, IXGBE_EIMS_FLOW_सूची);
	पूर्ण अन्यथा अणु
		e_err(probe, "failed to finish FDIR re-initialization, "
		      "ignored adding FDIR ATR filters\n");
	पूर्ण
पूर्ण

/**
 * ixgbe_check_hang_subtask - check क्रम hung queues and dropped पूर्णांकerrupts
 * @adapter: poपूर्णांकer to the device adapter काष्ठाure
 *
 * This function serves two purposes.  First it strobes the पूर्णांकerrupt lines
 * in order to make certain पूर्णांकerrupts are occurring.  Secondly it sets the
 * bits needed to check क्रम TX hangs.  As a result we should immediately
 * determine अगर a hang has occurred.
 */
अटल व्योम ixgbe_check_hang_subtask(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u64 eics = 0;
	पूर्णांक i;

	/* If we're करोwn, removing or resetting, just bail */
	अगर (test_bit(__IXGBE_DOWN, &adapter->state) ||
	    test_bit(__IXGBE_REMOVING, &adapter->state) ||
	    test_bit(__IXGBE_RESETTING, &adapter->state))
		वापस;

	/* Force detection of hung controller */
	अगर (netअगर_carrier_ok(adapter->netdev)) अणु
		क्रम (i = 0; i < adapter->num_tx_queues; i++)
			set_check_क्रम_tx_hang(adapter->tx_ring[i]);
		क्रम (i = 0; i < adapter->num_xdp_queues; i++)
			set_check_क्रम_tx_hang(adapter->xdp_ring[i]);
	पूर्ण

	अगर (!(adapter->flags & IXGBE_FLAG_MSIX_ENABLED)) अणु
		/*
		 * क्रम legacy and MSI पूर्णांकerrupts करोn't set any bits
		 * that are enabled क्रम EIAM, because this operation
		 * would set *both* EIMS and EICS क्रम any bit in EIAM
		 */
		IXGBE_WRITE_REG(hw, IXGBE_EICS,
			(IXGBE_EICS_TCP_TIMER | IXGBE_EICS_OTHER));
	पूर्ण अन्यथा अणु
		/* get one bit क्रम every active tx/rx पूर्णांकerrupt vector */
		क्रम (i = 0; i < adapter->num_q_vectors; i++) अणु
			काष्ठा ixgbe_q_vector *qv = adapter->q_vector[i];
			अगर (qv->rx.ring || qv->tx.ring)
				eics |= BIT_ULL(i);
		पूर्ण
	पूर्ण

	/* Cause software पूर्णांकerrupt to ensure rings are cleaned */
	ixgbe_irq_rearm_queues(adapter, eics);
पूर्ण

/**
 * ixgbe_watchकरोg_update_link - update the link status
 * @adapter: poपूर्णांकer to the device adapter काष्ठाure
 **/
अटल व्योम ixgbe_watchकरोg_update_link(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 link_speed = adapter->link_speed;
	bool link_up = adapter->link_up;
	bool pfc_en = adapter->dcb_cfg.pfc_mode_enable;

	अगर (!(adapter->flags & IXGBE_FLAG_NEED_LINK_UPDATE))
		वापस;

	अगर (hw->mac.ops.check_link) अणु
		hw->mac.ops.check_link(hw, &link_speed, &link_up, false);
	पूर्ण अन्यथा अणु
		/* always assume link is up, अगर no check link function */
		link_speed = IXGBE_LINK_SPEED_10GB_FULL;
		link_up = true;
	पूर्ण

	अगर (adapter->ixgbe_ieee_pfc)
		pfc_en |= !!(adapter->ixgbe_ieee_pfc->pfc_en);

	अगर (link_up && !((adapter->flags & IXGBE_FLAG_DCB_ENABLED) && pfc_en)) अणु
		hw->mac.ops.fc_enable(hw);
		ixgbe_set_rx_drop_en(adapter);
	पूर्ण

	अगर (link_up ||
	    समय_after(jअगरfies, (adapter->link_check_समयout +
				 IXGBE_TRY_LINK_TIMEOUT))) अणु
		adapter->flags &= ~IXGBE_FLAG_NEED_LINK_UPDATE;
		IXGBE_WRITE_REG(hw, IXGBE_EIMS, IXGBE_EIMC_LSC);
		IXGBE_WRITE_FLUSH(hw);
	पूर्ण

	adapter->link_up = link_up;
	adapter->link_speed = link_speed;
पूर्ण

अटल व्योम ixgbe_update_शेष_up(काष्ठा ixgbe_adapter *adapter)
अणु
#अगर_घोषित CONFIG_IXGBE_DCB
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा dcb_app app = अणु
			      .selector = IEEE_8021QAZ_APP_SEL_ETHERTYPE,
			      .protocol = 0,
			     पूर्ण;
	u8 up = 0;

	अगर (adapter->dcbx_cap & DCB_CAP_DCBX_VER_IEEE)
		up = dcb_ieee_getapp_mask(netdev, &app);

	adapter->शेष_up = (up > 1) ? (ffs(up) - 1) : 0;
#पूर्ण_अगर
पूर्ण

/**
 * ixgbe_watchकरोg_link_is_up - update netअगर_carrier status and
 *                             prपूर्णांक link up message
 * @adapter: poपूर्णांकer to the device adapter काष्ठाure
 **/
अटल व्योम ixgbe_watchकरोg_link_is_up(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 link_speed = adapter->link_speed;
	स्थिर अक्षर *speed_str;
	bool flow_rx, flow_tx;

	/* only जारी अगर link was previously करोwn */
	अगर (netअगर_carrier_ok(netdev))
		वापस;

	adapter->flags2 &= ~IXGBE_FLAG2_SEARCH_FOR_SFP;

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB: अणु
		u32 frctl = IXGBE_READ_REG(hw, IXGBE_FCTRL);
		u32 rmcs = IXGBE_READ_REG(hw, IXGBE_RMCS);
		flow_rx = !!(frctl & IXGBE_FCTRL_RFCE);
		flow_tx = !!(rmcs & IXGBE_RMCS_TFCE_802_3X);
	पूर्ण
		अवरोध;
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
	हाल ixgbe_mac_82599EB: अणु
		u32 mflcn = IXGBE_READ_REG(hw, IXGBE_MFLCN);
		u32 fccfg = IXGBE_READ_REG(hw, IXGBE_FCCFG);
		flow_rx = !!(mflcn & IXGBE_MFLCN_RFCE);
		flow_tx = !!(fccfg & IXGBE_FCCFG_TFCE_802_3X);
	पूर्ण
		अवरोध;
	शेष:
		flow_tx = false;
		flow_rx = false;
		अवरोध;
	पूर्ण

	adapter->last_rx_ptp_check = jअगरfies;

	अगर (test_bit(__IXGBE_PTP_RUNNING, &adapter->state))
		ixgbe_ptp_start_cyclecounter(adapter);

	चयन (link_speed) अणु
	हाल IXGBE_LINK_SPEED_10GB_FULL:
		speed_str = "10 Gbps";
		अवरोध;
	हाल IXGBE_LINK_SPEED_5GB_FULL:
		speed_str = "5 Gbps";
		अवरोध;
	हाल IXGBE_LINK_SPEED_2_5GB_FULL:
		speed_str = "2.5 Gbps";
		अवरोध;
	हाल IXGBE_LINK_SPEED_1GB_FULL:
		speed_str = "1 Gbps";
		अवरोध;
	हाल IXGBE_LINK_SPEED_100_FULL:
		speed_str = "100 Mbps";
		अवरोध;
	हाल IXGBE_LINK_SPEED_10_FULL:
		speed_str = "10 Mbps";
		अवरोध;
	शेष:
		speed_str = "unknown speed";
		अवरोध;
	पूर्ण
	e_info(drv, "NIC Link is Up %s, Flow Control: %s\n", speed_str,
	       ((flow_rx && flow_tx) ? "RX/TX" :
	       (flow_rx ? "RX" :
	       (flow_tx ? "TX" : "None"))));

	netअगर_carrier_on(netdev);
	ixgbe_check_vf_rate_limit(adapter);

	/* enable transmits */
	netअगर_tx_wake_all_queues(adapter->netdev);

	/* update the शेष user priority क्रम VFs */
	ixgbe_update_शेष_up(adapter);

	/* ping all the active vfs to let them know link has changed */
	ixgbe_ping_all_vfs(adapter);
पूर्ण

/**
 * ixgbe_watchकरोg_link_is_करोwn - update netअगर_carrier status and
 *                               prपूर्णांक link करोwn message
 * @adapter: poपूर्णांकer to the adapter काष्ठाure
 **/
अटल व्योम ixgbe_watchकरोg_link_is_करोwn(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	adapter->link_up = false;
	adapter->link_speed = 0;

	/* only जारी अगर link was up previously */
	अगर (!netअगर_carrier_ok(netdev))
		वापस;

	/* poll क्रम SFP+ cable when link is करोwn */
	अगर (ixgbe_is_sfp(hw) && hw->mac.type == ixgbe_mac_82598EB)
		adapter->flags2 |= IXGBE_FLAG2_SEARCH_FOR_SFP;

	अगर (test_bit(__IXGBE_PTP_RUNNING, &adapter->state))
		ixgbe_ptp_start_cyclecounter(adapter);

	e_info(drv, "NIC Link is Down\n");
	netअगर_carrier_off(netdev);

	/* ping all the active vfs to let them know link has changed */
	ixgbe_ping_all_vfs(adapter);
पूर्ण

अटल bool ixgbe_ring_tx_pending(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		काष्ठा ixgbe_ring *tx_ring = adapter->tx_ring[i];

		अगर (tx_ring->next_to_use != tx_ring->next_to_clean)
			वापस true;
	पूर्ण

	क्रम (i = 0; i < adapter->num_xdp_queues; i++) अणु
		काष्ठा ixgbe_ring *ring = adapter->xdp_ring[i];

		अगर (ring->next_to_use != ring->next_to_clean)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool ixgbe_vf_tx_pending(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा ixgbe_ring_feature *vmdq = &adapter->ring_feature[RING_F_VMDQ];
	u32 q_per_pool = __ALIGN_MASK(1, ~vmdq->mask);

	पूर्णांक i, j;

	अगर (!adapter->num_vfs)
		वापस false;

	/* resetting the PF is only needed क्रम MAC beक्रमe X550 */
	अगर (hw->mac.type >= ixgbe_mac_X550)
		वापस false;

	क्रम (i = 0; i < adapter->num_vfs; i++) अणु
		क्रम (j = 0; j < q_per_pool; j++) अणु
			u32 h, t;

			h = IXGBE_READ_REG(hw, IXGBE_PVFTDHN(q_per_pool, i, j));
			t = IXGBE_READ_REG(hw, IXGBE_PVFTDTN(q_per_pool, i, j));

			अगर (h != t)
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

/**
 * ixgbe_watchकरोg_flush_tx - flush queues on link करोwn
 * @adapter: poपूर्णांकer to the device adapter काष्ठाure
 **/
अटल व्योम ixgbe_watchकरोg_flush_tx(काष्ठा ixgbe_adapter *adapter)
अणु
	अगर (!netअगर_carrier_ok(adapter->netdev)) अणु
		अगर (ixgbe_ring_tx_pending(adapter) ||
		    ixgbe_vf_tx_pending(adapter)) अणु
			/* We've lost link, so the controller stops DMA,
			 * but we've got queued Tx work that's never going
			 * to get करोne, so reset controller to flush Tx.
			 * (Do the reset outside of पूर्णांकerrupt context).
			 */
			e_warn(drv, "initiating reset to clear Tx work after link loss\n");
			set_bit(__IXGBE_RESET_REQUESTED, &adapter->state);
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
अटल व्योम ixgbe_check_क्रम_bad_vf(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा pci_dev *pdev = adapter->pdev;
	अचिन्हित पूर्णांक vf;
	u32 gpc;

	अगर (!(netअगर_carrier_ok(adapter->netdev)))
		वापस;

	gpc = IXGBE_READ_REG(hw, IXGBE_TXDGPC);
	अगर (gpc) /* If incrementing then no need क्रम the check below */
		वापस;
	/* Check to see अगर a bad DMA ग_लिखो target from an errant or
	 * malicious VF has caused a PCIe error.  If so then we can
	 * issue a VFLR to the offending VF(s) and then resume without
	 * requesting a full slot reset.
	 */

	अगर (!pdev)
		वापस;

	/* check status reg क्रम all VFs owned by this PF */
	क्रम (vf = 0; vf < adapter->num_vfs; ++vf) अणु
		काष्ठा pci_dev *vfdev = adapter->vfinfo[vf].vfdev;
		u16 status_reg;

		अगर (!vfdev)
			जारी;
		pci_पढ़ो_config_word(vfdev, PCI_STATUS, &status_reg);
		अगर (status_reg != IXGBE_FAILED_READ_CFG_WORD &&
		    status_reg & PCI_STATUS_REC_MASTER_ABORT)
			pcie_flr(vfdev);
	पूर्ण
पूर्ण

अटल व्योम ixgbe_spoof_check(काष्ठा ixgbe_adapter *adapter)
अणु
	u32 ssvpc;

	/* Do not perक्रमm spoof check क्रम 82598 or अगर not in IOV mode */
	अगर (adapter->hw.mac.type == ixgbe_mac_82598EB ||
	    adapter->num_vfs == 0)
		वापस;

	ssvpc = IXGBE_READ_REG(&adapter->hw, IXGBE_SSVPC);

	/*
	 * ssvpc रेजिस्टर is cleared on पढ़ो, अगर zero then no
	 * spoofed packets in the last पूर्णांकerval.
	 */
	अगर (!ssvpc)
		वापस;

	e_warn(drv, "%u Spoofed packets detected\n", ssvpc);
पूर्ण
#अन्यथा
अटल व्योम ixgbe_spoof_check(काष्ठा ixgbe_adapter __always_unused *adapter)
अणु
पूर्ण

अटल व्योम
ixgbe_check_क्रम_bad_vf(काष्ठा ixgbe_adapter __always_unused *adapter)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_IOV */


/**
 * ixgbe_watchकरोg_subtask - check and bring link up
 * @adapter: poपूर्णांकer to the device adapter काष्ठाure
 **/
अटल व्योम ixgbe_watchकरोg_subtask(काष्ठा ixgbe_adapter *adapter)
अणु
	/* अगर पूर्णांकerface is करोwn, removing or resetting, करो nothing */
	अगर (test_bit(__IXGBE_DOWN, &adapter->state) ||
	    test_bit(__IXGBE_REMOVING, &adapter->state) ||
	    test_bit(__IXGBE_RESETTING, &adapter->state))
		वापस;

	ixgbe_watchकरोg_update_link(adapter);

	अगर (adapter->link_up)
		ixgbe_watchकरोg_link_is_up(adapter);
	अन्यथा
		ixgbe_watchकरोg_link_is_करोwn(adapter);

	ixgbe_check_क्रम_bad_vf(adapter);
	ixgbe_spoof_check(adapter);
	ixgbe_update_stats(adapter);

	ixgbe_watchकरोg_flush_tx(adapter);
पूर्ण

/**
 * ixgbe_sfp_detection_subtask - poll क्रम SFP+ cable
 * @adapter: the ixgbe adapter काष्ठाure
 **/
अटल व्योम ixgbe_sfp_detection_subtask(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	s32 err;

	/* not searching क्रम SFP so there is nothing to करो here */
	अगर (!(adapter->flags2 & IXGBE_FLAG2_SEARCH_FOR_SFP) &&
	    !(adapter->flags2 & IXGBE_FLAG2_SFP_NEEDS_RESET))
		वापस;

	अगर (adapter->sfp_poll_समय &&
	    समय_after(adapter->sfp_poll_समय, jअगरfies))
		वापस; /* If not yet समय to poll क्रम SFP */

	/* someone अन्यथा is in init, रुको until next service event */
	अगर (test_and_set_bit(__IXGBE_IN_SFP_INIT, &adapter->state))
		वापस;

	adapter->sfp_poll_समय = jअगरfies + IXGBE_SFP_POLL_JIFFIES - 1;

	err = hw->phy.ops.identअगरy_sfp(hw);
	अगर (err == IXGBE_ERR_SFP_NOT_SUPPORTED)
		जाओ sfp_out;

	अगर (err == IXGBE_ERR_SFP_NOT_PRESENT) अणु
		/* If no cable is present, then we need to reset
		 * the next समय we find a good cable. */
		adapter->flags2 |= IXGBE_FLAG2_SFP_NEEDS_RESET;
	पूर्ण

	/* निकास on error */
	अगर (err)
		जाओ sfp_out;

	/* निकास अगर reset not needed */
	अगर (!(adapter->flags2 & IXGBE_FLAG2_SFP_NEEDS_RESET))
		जाओ sfp_out;

	adapter->flags2 &= ~IXGBE_FLAG2_SFP_NEEDS_RESET;

	/*
	 * A module may be identअगरied correctly, but the EEPROM may not have
	 * support क्रम that module.  setup_sfp() will fail in that हाल, so
	 * we should not allow that module to load.
	 */
	अगर (hw->mac.type == ixgbe_mac_82598EB)
		err = hw->phy.ops.reset(hw);
	अन्यथा
		err = hw->mac.ops.setup_sfp(hw);

	अगर (err == IXGBE_ERR_SFP_NOT_SUPPORTED)
		जाओ sfp_out;

	adapter->flags |= IXGBE_FLAG_NEED_LINK_CONFIG;
	e_info(probe, "detected SFP+: %d\n", hw->phy.sfp_type);

sfp_out:
	clear_bit(__IXGBE_IN_SFP_INIT, &adapter->state);

	अगर ((err == IXGBE_ERR_SFP_NOT_SUPPORTED) &&
	    (adapter->netdev->reg_state == NETREG_REGISTERED)) अणु
		e_dev_err("failed to initialize because an unsupported "
			  "SFP+ module type was detected.\n");
		e_dev_err("Reload the driver after installing a "
			  "supported module.\n");
		unरेजिस्टर_netdev(adapter->netdev);
	पूर्ण
पूर्ण

/**
 * ixgbe_sfp_link_config_subtask - set up link SFP after module install
 * @adapter: the ixgbe adapter काष्ठाure
 **/
अटल व्योम ixgbe_sfp_link_config_subtask(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 cap_speed;
	u32 speed;
	bool स्वतःneg = false;

	अगर (!(adapter->flags & IXGBE_FLAG_NEED_LINK_CONFIG))
		वापस;

	/* someone अन्यथा is in init, रुको until next service event */
	अगर (test_and_set_bit(__IXGBE_IN_SFP_INIT, &adapter->state))
		वापस;

	adapter->flags &= ~IXGBE_FLAG_NEED_LINK_CONFIG;

	hw->mac.ops.get_link_capabilities(hw, &cap_speed, &स्वतःneg);

	/* advertise highest capable link speed */
	अगर (!स्वतःneg && (cap_speed & IXGBE_LINK_SPEED_10GB_FULL))
		speed = IXGBE_LINK_SPEED_10GB_FULL;
	अन्यथा
		speed = cap_speed & (IXGBE_LINK_SPEED_10GB_FULL |
				     IXGBE_LINK_SPEED_1GB_FULL);

	अगर (hw->mac.ops.setup_link)
		hw->mac.ops.setup_link(hw, speed, true);

	adapter->flags |= IXGBE_FLAG_NEED_LINK_UPDATE;
	adapter->link_check_समयout = jअगरfies;
	clear_bit(__IXGBE_IN_SFP_INIT, &adapter->state);
पूर्ण

/**
 * ixgbe_service_समयr - Timer Call-back
 * @t: poपूर्णांकer to समयr_list काष्ठाure
 **/
अटल व्योम ixgbe_service_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ixgbe_adapter *adapter = from_समयr(adapter, t, service_समयr);
	अचिन्हित दीर्घ next_event_offset;

	/* poll faster when रुकोing क्रम link */
	अगर (adapter->flags & IXGBE_FLAG_NEED_LINK_UPDATE)
		next_event_offset = HZ / 10;
	अन्यथा
		next_event_offset = HZ * 2;

	/* Reset the समयr */
	mod_समयr(&adapter->service_समयr, next_event_offset + jअगरfies);

	ixgbe_service_event_schedule(adapter);
पूर्ण

अटल व्योम ixgbe_phy_पूर्णांकerrupt_subtask(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 status;

	अगर (!(adapter->flags2 & IXGBE_FLAG2_PHY_INTERRUPT))
		वापस;

	adapter->flags2 &= ~IXGBE_FLAG2_PHY_INTERRUPT;

	अगर (!hw->phy.ops.handle_lasi)
		वापस;

	status = hw->phy.ops.handle_lasi(&adapter->hw);
	अगर (status != IXGBE_ERR_OVERTEMP)
		वापस;

	e_crit(drv, "%s\n", ixgbe_overheat_msg);
पूर्ण

अटल व्योम ixgbe_reset_subtask(काष्ठा ixgbe_adapter *adapter)
अणु
	अगर (!test_and_clear_bit(__IXGBE_RESET_REQUESTED, &adapter->state))
		वापस;

	rtnl_lock();
	/* If we're alपढ़ोy करोwn, removing or resetting, just bail */
	अगर (test_bit(__IXGBE_DOWN, &adapter->state) ||
	    test_bit(__IXGBE_REMOVING, &adapter->state) ||
	    test_bit(__IXGBE_RESETTING, &adapter->state)) अणु
		rtnl_unlock();
		वापस;
	पूर्ण

	ixgbe_dump(adapter);
	netdev_err(adapter->netdev, "Reset adapter\n");
	adapter->tx_समयout_count++;

	ixgbe_reinit_locked(adapter);
	rtnl_unlock();
पूर्ण

/**
 * ixgbe_check_fw_error - Check firmware क्रम errors
 * @adapter: the adapter निजी काष्ठाure
 *
 * Check firmware errors in रेजिस्टर FWSM
 */
अटल bool ixgbe_check_fw_error(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 fwsm;

	/* पढ़ो fwsm.ext_err_ind रेजिस्टर and log errors */
	fwsm = IXGBE_READ_REG(hw, IXGBE_FWSM(hw));

	अगर (fwsm & IXGBE_FWSM_EXT_ERR_IND_MASK ||
	    !(fwsm & IXGBE_FWSM_FW_VAL_BIT))
		e_dev_warn("Warning firmware error detected FWSM: 0x%08X\n",
			   fwsm);

	अगर (hw->mac.ops.fw_recovery_mode && hw->mac.ops.fw_recovery_mode(hw)) अणु
		e_dev_err("Firmware recovery mode detected. Limiting functionality. Refer to the Intel(R) Ethernet Adapters and Devices User Guide for details on firmware recovery mode.\n");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * ixgbe_service_task - manages and runs subtasks
 * @work: poपूर्णांकer to work_काष्ठा containing our data
 **/
अटल व्योम ixgbe_service_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ixgbe_adapter *adapter = container_of(work,
						     काष्ठा ixgbe_adapter,
						     service_task);
	अगर (ixgbe_हटाओd(adapter->hw.hw_addr)) अणु
		अगर (!test_bit(__IXGBE_DOWN, &adapter->state)) अणु
			rtnl_lock();
			ixgbe_करोwn(adapter);
			rtnl_unlock();
		पूर्ण
		ixgbe_service_event_complete(adapter);
		वापस;
	पूर्ण
	अगर (ixgbe_check_fw_error(adapter)) अणु
		अगर (!test_bit(__IXGBE_DOWN, &adapter->state))
			unरेजिस्टर_netdev(adapter->netdev);
		ixgbe_service_event_complete(adapter);
		वापस;
	पूर्ण
	ixgbe_reset_subtask(adapter);
	ixgbe_phy_पूर्णांकerrupt_subtask(adapter);
	ixgbe_sfp_detection_subtask(adapter);
	ixgbe_sfp_link_config_subtask(adapter);
	ixgbe_check_overtemp_subtask(adapter);
	ixgbe_watchकरोg_subtask(adapter);
	ixgbe_fdir_reinit_subtask(adapter);
	ixgbe_check_hang_subtask(adapter);

	अगर (test_bit(__IXGBE_PTP_RUNNING, &adapter->state)) अणु
		ixgbe_ptp_overflow_check(adapter);
		अगर (adapter->flags & IXGBE_FLAG_RX_HWTSTAMP_IN_REGISTER)
			ixgbe_ptp_rx_hang(adapter);
		ixgbe_ptp_tx_hang(adapter);
	पूर्ण

	ixgbe_service_event_complete(adapter);
पूर्ण

अटल पूर्णांक ixgbe_tso(काष्ठा ixgbe_ring *tx_ring,
		     काष्ठा ixgbe_tx_buffer *first,
		     u8 *hdr_len,
		     काष्ठा ixgbe_ipsec_tx_data *itd)
अणु
	u32 vlan_macip_lens, type_tucmd, mss_l4len_idx;
	काष्ठा sk_buff *skb = first->skb;
	जोड़ अणु
		काष्ठा iphdr *v4;
		काष्ठा ipv6hdr *v6;
		अचिन्हित अक्षर *hdr;
	पूर्ण ip;
	जोड़ अणु
		काष्ठा tcphdr *tcp;
		काष्ठा udphdr *udp;
		अचिन्हित अक्षर *hdr;
	पूर्ण l4;
	u32 paylen, l4_offset;
	u32 fceof_saidx = 0;
	पूर्णांक err;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	अगर (!skb_is_gso(skb))
		वापस 0;

	err = skb_cow_head(skb, 0);
	अगर (err < 0)
		वापस err;

	अगर (eth_p_mpls(first->protocol))
		ip.hdr = skb_inner_network_header(skb);
	अन्यथा
		ip.hdr = skb_network_header(skb);
	l4.hdr = skb_checksum_start(skb);

	/* ADV DTYP TUCMD MKRLOC/ISCSIHEDLEN */
	type_tucmd = (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4) ?
		      IXGBE_ADVTXD_TUCMD_L4T_UDP : IXGBE_ADVTXD_TUCMD_L4T_TCP;

	/* initialize outer IP header fields */
	अगर (ip.v4->version == 4) अणु
		अचिन्हित अक्षर *csum_start = skb_checksum_start(skb);
		अचिन्हित अक्षर *trans_start = ip.hdr + (ip.v4->ihl * 4);
		पूर्णांक len = csum_start - trans_start;

		/* IP header will have to cancel out any data that
		 * is not a part of the outer IP header, so set to
		 * a reverse csum अगर needed, अन्यथा init check to 0.
		 */
		ip.v4->check = (skb_shinfo(skb)->gso_type & SKB_GSO_PARTIAL) ?
					   csum_fold(csum_partial(trans_start,
								  len, 0)) : 0;
		type_tucmd |= IXGBE_ADVTXD_TUCMD_IPV4;

		ip.v4->tot_len = 0;
		first->tx_flags |= IXGBE_TX_FLAGS_TSO |
				   IXGBE_TX_FLAGS_CSUM |
				   IXGBE_TX_FLAGS_IPV4;
	पूर्ण अन्यथा अणु
		ip.v6->payload_len = 0;
		first->tx_flags |= IXGBE_TX_FLAGS_TSO |
				   IXGBE_TX_FLAGS_CSUM;
	पूर्ण

	/* determine offset of inner transport header */
	l4_offset = l4.hdr - skb->data;

	/* हटाओ payload length from inner checksum */
	paylen = skb->len - l4_offset;

	अगर (type_tucmd & IXGBE_ADVTXD_TUCMD_L4T_TCP) अणु
		/* compute length of segmentation header */
		*hdr_len = (l4.tcp->करोff * 4) + l4_offset;
		csum_replace_by_dअगरf(&l4.tcp->check,
				     (__क्रमce __wsum)htonl(paylen));
	पूर्ण अन्यथा अणु
		/* compute length of segmentation header */
		*hdr_len = माप(*l4.udp) + l4_offset;
		csum_replace_by_dअगरf(&l4.udp->check,
				     (__क्रमce __wsum)htonl(paylen));
	पूर्ण

	/* update gso size and bytecount with header size */
	first->gso_segs = skb_shinfo(skb)->gso_segs;
	first->bytecount += (first->gso_segs - 1) * *hdr_len;

	/* mss_l4len_id: use 0 as index क्रम TSO */
	mss_l4len_idx = (*hdr_len - l4_offset) << IXGBE_ADVTXD_L4LEN_SHIFT;
	mss_l4len_idx |= skb_shinfo(skb)->gso_size << IXGBE_ADVTXD_MSS_SHIFT;

	fceof_saidx |= itd->sa_idx;
	type_tucmd |= itd->flags | itd->trailer_len;

	/* vlan_macip_lens: HEADLEN, MACLEN, VLAN tag */
	vlan_macip_lens = l4.hdr - ip.hdr;
	vlan_macip_lens |= (ip.hdr - skb->data) << IXGBE_ADVTXD_MACLEN_SHIFT;
	vlan_macip_lens |= first->tx_flags & IXGBE_TX_FLAGS_VLAN_MASK;

	ixgbe_tx_ctxtdesc(tx_ring, vlan_macip_lens, fceof_saidx, type_tucmd,
			  mss_l4len_idx);

	वापस 1;
पूर्ण

अटल व्योम ixgbe_tx_csum(काष्ठा ixgbe_ring *tx_ring,
			  काष्ठा ixgbe_tx_buffer *first,
			  काष्ठा ixgbe_ipsec_tx_data *itd)
अणु
	काष्ठा sk_buff *skb = first->skb;
	u32 vlan_macip_lens = 0;
	u32 fceof_saidx = 0;
	u32 type_tucmd = 0;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL) अणु
csum_failed:
		अगर (!(first->tx_flags & (IXGBE_TX_FLAGS_HW_VLAN |
					 IXGBE_TX_FLAGS_CC)))
			वापस;
		जाओ no_csum;
	पूर्ण

	चयन (skb->csum_offset) अणु
	हाल दुरत्व(काष्ठा tcphdr, check):
		type_tucmd = IXGBE_ADVTXD_TUCMD_L4T_TCP;
		fallthrough;
	हाल दुरत्व(काष्ठा udphdr, check):
		अवरोध;
	हाल दुरत्व(काष्ठा sctphdr, checksum):
		/* validate that this is actually an SCTP request */
		अगर (skb_csum_is_sctp(skb)) अणु
			type_tucmd = IXGBE_ADVTXD_TUCMD_L4T_SCTP;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		skb_checksum_help(skb);
		जाओ csum_failed;
	पूर्ण

	/* update TX checksum flag */
	first->tx_flags |= IXGBE_TX_FLAGS_CSUM;
	vlan_macip_lens = skb_checksum_start_offset(skb) -
			  skb_network_offset(skb);
no_csum:
	/* vlan_macip_lens: MACLEN, VLAN tag */
	vlan_macip_lens |= skb_network_offset(skb) << IXGBE_ADVTXD_MACLEN_SHIFT;
	vlan_macip_lens |= first->tx_flags & IXGBE_TX_FLAGS_VLAN_MASK;

	fceof_saidx |= itd->sa_idx;
	type_tucmd |= itd->flags | itd->trailer_len;

	ixgbe_tx_ctxtdesc(tx_ring, vlan_macip_lens, fceof_saidx, type_tucmd, 0);
पूर्ण

#घोषणा IXGBE_SET_FLAG(_input, _flag, _result) \
	((_flag <= _result) ? \
	 ((u32)(_input & _flag) * (_result / _flag)) : \
	 ((u32)(_input & _flag) / (_flag / _result)))

अटल u32 ixgbe_tx_cmd_type(काष्ठा sk_buff *skb, u32 tx_flags)
अणु
	/* set type क्रम advanced descriptor with frame checksum insertion */
	u32 cmd_type = IXGBE_ADVTXD_DTYP_DATA |
		       IXGBE_ADVTXD_DCMD_DEXT |
		       IXGBE_ADVTXD_DCMD_IFCS;

	/* set HW vlan bit अगर vlan is present */
	cmd_type |= IXGBE_SET_FLAG(tx_flags, IXGBE_TX_FLAGS_HW_VLAN,
				   IXGBE_ADVTXD_DCMD_VLE);

	/* set segmentation enable bits क्रम TSO/FSO */
	cmd_type |= IXGBE_SET_FLAG(tx_flags, IXGBE_TX_FLAGS_TSO,
				   IXGBE_ADVTXD_DCMD_TSE);

	/* set बारtamp bit अगर present */
	cmd_type |= IXGBE_SET_FLAG(tx_flags, IXGBE_TX_FLAGS_TSTAMP,
				   IXGBE_ADVTXD_MAC_TSTAMP);

	/* insert frame checksum */
	cmd_type ^= IXGBE_SET_FLAG(skb->no_fcs, 1, IXGBE_ADVTXD_DCMD_IFCS);

	वापस cmd_type;
पूर्ण

अटल व्योम ixgbe_tx_olinfo_status(जोड़ ixgbe_adv_tx_desc *tx_desc,
				   u32 tx_flags, अचिन्हित पूर्णांक paylen)
अणु
	u32 olinfo_status = paylen << IXGBE_ADVTXD_PAYLEN_SHIFT;

	/* enable L4 checksum क्रम TSO and TX checksum offload */
	olinfo_status |= IXGBE_SET_FLAG(tx_flags,
					IXGBE_TX_FLAGS_CSUM,
					IXGBE_ADVTXD_POPTS_TXSM);

	/* enable IPv4 checksum क्रम TSO */
	olinfo_status |= IXGBE_SET_FLAG(tx_flags,
					IXGBE_TX_FLAGS_IPV4,
					IXGBE_ADVTXD_POPTS_IXSM);

	/* enable IPsec */
	olinfo_status |= IXGBE_SET_FLAG(tx_flags,
					IXGBE_TX_FLAGS_IPSEC,
					IXGBE_ADVTXD_POPTS_IPSEC);

	/*
	 * Check Context must be set अगर Tx चयन is enabled, which it
	 * always is क्रम हाल where भव functions are running
	 */
	olinfo_status |= IXGBE_SET_FLAG(tx_flags,
					IXGBE_TX_FLAGS_CC,
					IXGBE_ADVTXD_CC);

	tx_desc->पढ़ो.olinfo_status = cpu_to_le32(olinfo_status);
पूर्ण

अटल पूर्णांक __ixgbe_maybe_stop_tx(काष्ठा ixgbe_ring *tx_ring, u16 size)
अणु
	netअगर_stop_subqueue(tx_ring->netdev, tx_ring->queue_index);

	/* Herbert's original patch had:
	 *  smp_mb__after_netअगर_stop_queue();
	 * but since that करोesn't exist yet, just खोलो code it.
	 */
	smp_mb();

	/* We need to check again in a हाल another CPU has just
	 * made room available.
	 */
	अगर (likely(ixgbe_desc_unused(tx_ring) < size))
		वापस -EBUSY;

	/* A reprieve! - use start_queue because it करोesn't call schedule */
	netअगर_start_subqueue(tx_ring->netdev, tx_ring->queue_index);
	++tx_ring->tx_stats.restart_queue;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ixgbe_maybe_stop_tx(काष्ठा ixgbe_ring *tx_ring, u16 size)
अणु
	अगर (likely(ixgbe_desc_unused(tx_ring) >= size))
		वापस 0;

	वापस __ixgbe_maybe_stop_tx(tx_ring, size);
पूर्ण

अटल पूर्णांक ixgbe_tx_map(काष्ठा ixgbe_ring *tx_ring,
			काष्ठा ixgbe_tx_buffer *first,
			स्थिर u8 hdr_len)
अणु
	काष्ठा sk_buff *skb = first->skb;
	काष्ठा ixgbe_tx_buffer *tx_buffer;
	जोड़ ixgbe_adv_tx_desc *tx_desc;
	skb_frag_t *frag;
	dma_addr_t dma;
	अचिन्हित पूर्णांक data_len, size;
	u32 tx_flags = first->tx_flags;
	u32 cmd_type = ixgbe_tx_cmd_type(skb, tx_flags);
	u16 i = tx_ring->next_to_use;

	tx_desc = IXGBE_TX_DESC(tx_ring, i);

	ixgbe_tx_olinfo_status(tx_desc, tx_flags, skb->len - hdr_len);

	size = skb_headlen(skb);
	data_len = skb->data_len;

#अगर_घोषित IXGBE_FCOE
	अगर (tx_flags & IXGBE_TX_FLAGS_FCOE) अणु
		अगर (data_len < माप(काष्ठा fcoe_crc_eof)) अणु
			size -= माप(काष्ठा fcoe_crc_eof) - data_len;
			data_len = 0;
		पूर्ण अन्यथा अणु
			data_len -= माप(काष्ठा fcoe_crc_eof);
		पूर्ण
	पूर्ण

#पूर्ण_अगर
	dma = dma_map_single(tx_ring->dev, skb->data, size, DMA_TO_DEVICE);

	tx_buffer = first;

	क्रम (frag = &skb_shinfo(skb)->frags[0];; frag++) अणु
		अगर (dma_mapping_error(tx_ring->dev, dma))
			जाओ dma_error;

		/* record length, and DMA address */
		dma_unmap_len_set(tx_buffer, len, size);
		dma_unmap_addr_set(tx_buffer, dma, dma);

		tx_desc->पढ़ो.buffer_addr = cpu_to_le64(dma);

		जबतक (unlikely(size > IXGBE_MAX_DATA_PER_TXD)) अणु
			tx_desc->पढ़ो.cmd_type_len =
				cpu_to_le32(cmd_type ^ IXGBE_MAX_DATA_PER_TXD);

			i++;
			tx_desc++;
			अगर (i == tx_ring->count) अणु
				tx_desc = IXGBE_TX_DESC(tx_ring, 0);
				i = 0;
			पूर्ण
			tx_desc->पढ़ो.olinfo_status = 0;

			dma += IXGBE_MAX_DATA_PER_TXD;
			size -= IXGBE_MAX_DATA_PER_TXD;

			tx_desc->पढ़ो.buffer_addr = cpu_to_le64(dma);
		पूर्ण

		अगर (likely(!data_len))
			अवरोध;

		tx_desc->पढ़ो.cmd_type_len = cpu_to_le32(cmd_type ^ size);

		i++;
		tx_desc++;
		अगर (i == tx_ring->count) अणु
			tx_desc = IXGBE_TX_DESC(tx_ring, 0);
			i = 0;
		पूर्ण
		tx_desc->पढ़ो.olinfo_status = 0;

#अगर_घोषित IXGBE_FCOE
		size = min_t(अचिन्हित पूर्णांक, data_len, skb_frag_size(frag));
#अन्यथा
		size = skb_frag_size(frag);
#पूर्ण_अगर
		data_len -= size;

		dma = skb_frag_dma_map(tx_ring->dev, frag, 0, size,
				       DMA_TO_DEVICE);

		tx_buffer = &tx_ring->tx_buffer_info[i];
	पूर्ण

	/* ग_लिखो last descriptor with RS and EOP bits */
	cmd_type |= size | IXGBE_TXD_CMD;
	tx_desc->पढ़ो.cmd_type_len = cpu_to_le32(cmd_type);

	netdev_tx_sent_queue(txring_txq(tx_ring), first->bytecount);

	/* set the बारtamp */
	first->समय_stamp = jअगरfies;

	skb_tx_बारtamp(skb);

	/*
	 * Force memory ग_लिखोs to complete beक्रमe letting h/w know there
	 * are new descriptors to fetch.  (Only applicable क्रम weak-ordered
	 * memory model archs, such as IA-64).
	 *
	 * We also need this memory barrier to make certain all of the
	 * status bits have been updated beक्रमe next_to_watch is written.
	 */
	wmb();

	/* set next_to_watch value indicating a packet is present */
	first->next_to_watch = tx_desc;

	i++;
	अगर (i == tx_ring->count)
		i = 0;

	tx_ring->next_to_use = i;

	ixgbe_maybe_stop_tx(tx_ring, DESC_NEEDED);

	अगर (netअगर_xmit_stopped(txring_txq(tx_ring)) || !netdev_xmit_more()) अणु
		ग_लिखोl(i, tx_ring->tail);
	पूर्ण

	वापस 0;
dma_error:
	dev_err(tx_ring->dev, "TX DMA map failed\n");

	/* clear dma mappings क्रम failed tx_buffer_info map */
	क्रम (;;) अणु
		tx_buffer = &tx_ring->tx_buffer_info[i];
		अगर (dma_unmap_len(tx_buffer, len))
			dma_unmap_page(tx_ring->dev,
				       dma_unmap_addr(tx_buffer, dma),
				       dma_unmap_len(tx_buffer, len),
				       DMA_TO_DEVICE);
		dma_unmap_len_set(tx_buffer, len, 0);
		अगर (tx_buffer == first)
			अवरोध;
		अगर (i == 0)
			i += tx_ring->count;
		i--;
	पूर्ण

	dev_kमुक्त_skb_any(first->skb);
	first->skb = शून्य;

	tx_ring->next_to_use = i;

	वापस -1;
पूर्ण

अटल व्योम ixgbe_atr(काष्ठा ixgbe_ring *ring,
		      काष्ठा ixgbe_tx_buffer *first)
अणु
	काष्ठा ixgbe_q_vector *q_vector = ring->q_vector;
	जोड़ ixgbe_atr_hash_dword input = अणु .dword = 0 पूर्ण;
	जोड़ ixgbe_atr_hash_dword common = अणु .dword = 0 पूर्ण;
	जोड़ अणु
		अचिन्हित अक्षर *network;
		काष्ठा iphdr *ipv4;
		काष्ठा ipv6hdr *ipv6;
	पूर्ण hdr;
	काष्ठा tcphdr *th;
	अचिन्हित पूर्णांक hlen;
	काष्ठा sk_buff *skb;
	__be16 vlan_id;
	पूर्णांक l4_proto;

	/* अगर ring करोesn't have a पूर्णांकerrupt vector, cannot perक्रमm ATR */
	अगर (!q_vector)
		वापस;

	/* करो nothing अगर sampling is disabled */
	अगर (!ring->atr_sample_rate)
		वापस;

	ring->atr_count++;

	/* currently only IPv4/IPv6 with TCP is supported */
	अगर ((first->protocol != htons(ETH_P_IP)) &&
	    (first->protocol != htons(ETH_P_IPV6)))
		वापस;

	/* snag network header to get L4 type and address */
	skb = first->skb;
	hdr.network = skb_network_header(skb);
	अगर (unlikely(hdr.network <= skb->data))
		वापस;
	अगर (skb->encapsulation &&
	    first->protocol == htons(ETH_P_IP) &&
	    hdr.ipv4->protocol == IPPROTO_UDP) अणु
		काष्ठा ixgbe_adapter *adapter = q_vector->adapter;

		अगर (unlikely(skb_tail_poपूर्णांकer(skb) < hdr.network +
			     VXLAN_HEADROOM))
			वापस;

		/* verअगरy the port is recognized as VXLAN */
		अगर (adapter->vxlan_port &&
		    udp_hdr(skb)->dest == adapter->vxlan_port)
			hdr.network = skb_inner_network_header(skb);

		अगर (adapter->geneve_port &&
		    udp_hdr(skb)->dest == adapter->geneve_port)
			hdr.network = skb_inner_network_header(skb);
	पूर्ण

	/* Make sure we have at least [minimum IPv4 header + TCP]
	 * or [IPv6 header] bytes
	 */
	अगर (unlikely(skb_tail_poपूर्णांकer(skb) < hdr.network + 40))
		वापस;

	/* Currently only IPv4/IPv6 with TCP is supported */
	चयन (hdr.ipv4->version) अणु
	हाल IPVERSION:
		/* access ihl as u8 to aव्योम unaligned access on ia64 */
		hlen = (hdr.network[0] & 0x0F) << 2;
		l4_proto = hdr.ipv4->protocol;
		अवरोध;
	हाल 6:
		hlen = hdr.network - skb->data;
		l4_proto = ipv6_find_hdr(skb, &hlen, IPPROTO_TCP, शून्य, शून्य);
		hlen -= hdr.network - skb->data;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (l4_proto != IPPROTO_TCP)
		वापस;

	अगर (unlikely(skb_tail_poपूर्णांकer(skb) < hdr.network +
		     hlen + माप(काष्ठा tcphdr)))
		वापस;

	th = (काष्ठा tcphdr *)(hdr.network + hlen);

	/* skip this packet since the socket is closing */
	अगर (th->fin)
		वापस;

	/* sample on all syn packets or once every atr sample count */
	अगर (!th->syn && (ring->atr_count < ring->atr_sample_rate))
		वापस;

	/* reset sample count */
	ring->atr_count = 0;

	vlan_id = htons(first->tx_flags >> IXGBE_TX_FLAGS_VLAN_SHIFT);

	/*
	 * src and dst are inverted, think how the receiver sees them
	 *
	 * The input is broken पूर्णांकo two sections, a non-compressed section
	 * containing vm_pool, vlan_id, and flow_type.  The rest of the data
	 * is XORed together and stored in the compressed dword.
	 */
	input.क्रमmatted.vlan_id = vlan_id;

	/*
	 * since src port and flex bytes occupy the same word XOR them together
	 * and ग_लिखो the value to source port portion of compressed dword
	 */
	अगर (first->tx_flags & (IXGBE_TX_FLAGS_SW_VLAN | IXGBE_TX_FLAGS_HW_VLAN))
		common.port.src ^= th->dest ^ htons(ETH_P_8021Q);
	अन्यथा
		common.port.src ^= th->dest ^ first->protocol;
	common.port.dst ^= th->source;

	चयन (hdr.ipv4->version) अणु
	हाल IPVERSION:
		input.क्रमmatted.flow_type = IXGBE_ATR_FLOW_TYPE_TCPV4;
		common.ip ^= hdr.ipv4->saddr ^ hdr.ipv4->daddr;
		अवरोध;
	हाल 6:
		input.क्रमmatted.flow_type = IXGBE_ATR_FLOW_TYPE_TCPV6;
		common.ip ^= hdr.ipv6->saddr.s6_addr32[0] ^
			     hdr.ipv6->saddr.s6_addr32[1] ^
			     hdr.ipv6->saddr.s6_addr32[2] ^
			     hdr.ipv6->saddr.s6_addr32[3] ^
			     hdr.ipv6->daddr.s6_addr32[0] ^
			     hdr.ipv6->daddr.s6_addr32[1] ^
			     hdr.ipv6->daddr.s6_addr32[2] ^
			     hdr.ipv6->daddr.s6_addr32[3];
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (hdr.network != skb_network_header(skb))
		input.क्रमmatted.flow_type |= IXGBE_ATR_L4TYPE_TUNNEL_MASK;

	/* This assumes the Rx queue and Tx queue are bound to the same CPU */
	ixgbe_fdir_add_signature_filter_82599(&q_vector->adapter->hw,
					      input, common, ring->queue_index);
पूर्ण

#अगर_घोषित IXGBE_FCOE
अटल u16 ixgbe_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			      काष्ठा net_device *sb_dev)
अणु
	काष्ठा ixgbe_adapter *adapter;
	काष्ठा ixgbe_ring_feature *f;
	पूर्णांक txq;

	अगर (sb_dev) अणु
		u8 tc = netdev_get_prio_tc_map(dev, skb->priority);
		काष्ठा net_device *vdev = sb_dev;

		txq = vdev->tc_to_txq[tc].offset;
		txq += reciprocal_scale(skb_get_hash(skb),
					vdev->tc_to_txq[tc].count);

		वापस txq;
	पूर्ण

	/*
	 * only execute the code below अगर protocol is FCoE
	 * or FIP and we have FCoE enabled on the adapter
	 */
	चयन (vlan_get_protocol(skb)) अणु
	हाल htons(ETH_P_FCOE):
	हाल htons(ETH_P_FIP):
		adapter = netdev_priv(dev);

		अगर (!sb_dev && (adapter->flags & IXGBE_FLAG_FCOE_ENABLED))
			अवरोध;
		fallthrough;
	शेष:
		वापस netdev_pick_tx(dev, skb, sb_dev);
	पूर्ण

	f = &adapter->ring_feature[RING_F_FCOE];

	txq = skb_rx_queue_recorded(skb) ? skb_get_rx_queue(skb) :
					   smp_processor_id();

	जबतक (txq >= f->indices)
		txq -= f->indices;

	वापस txq + f->offset;
पूर्ण

#पूर्ण_अगर
पूर्णांक ixgbe_xmit_xdp_ring(काष्ठा ixgbe_adapter *adapter,
			काष्ठा xdp_frame *xdpf)
अणु
	काष्ठा ixgbe_ring *ring = adapter->xdp_ring[smp_processor_id()];
	काष्ठा ixgbe_tx_buffer *tx_buffer;
	जोड़ ixgbe_adv_tx_desc *tx_desc;
	u32 len, cmd_type;
	dma_addr_t dma;
	u16 i;

	len = xdpf->len;

	अगर (unlikely(!ixgbe_desc_unused(ring)))
		वापस IXGBE_XDP_CONSUMED;

	dma = dma_map_single(ring->dev, xdpf->data, len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(ring->dev, dma))
		वापस IXGBE_XDP_CONSUMED;

	/* record the location of the first descriptor क्रम this packet */
	tx_buffer = &ring->tx_buffer_info[ring->next_to_use];
	tx_buffer->bytecount = len;
	tx_buffer->gso_segs = 1;
	tx_buffer->protocol = 0;

	i = ring->next_to_use;
	tx_desc = IXGBE_TX_DESC(ring, i);

	dma_unmap_len_set(tx_buffer, len, len);
	dma_unmap_addr_set(tx_buffer, dma, dma);
	tx_buffer->xdpf = xdpf;

	tx_desc->पढ़ो.buffer_addr = cpu_to_le64(dma);

	/* put descriptor type bits */
	cmd_type = IXGBE_ADVTXD_DTYP_DATA |
		   IXGBE_ADVTXD_DCMD_DEXT |
		   IXGBE_ADVTXD_DCMD_IFCS;
	cmd_type |= len | IXGBE_TXD_CMD;
	tx_desc->पढ़ो.cmd_type_len = cpu_to_le32(cmd_type);
	tx_desc->पढ़ो.olinfo_status =
		cpu_to_le32(len << IXGBE_ADVTXD_PAYLEN_SHIFT);

	/* Aव्योम any potential race with xdp_xmit and cleanup */
	smp_wmb();

	/* set next_to_watch value indicating a packet is present */
	i++;
	अगर (i == ring->count)
		i = 0;

	tx_buffer->next_to_watch = tx_desc;
	ring->next_to_use = i;

	वापस IXGBE_XDP_TX;
पूर्ण

netdev_tx_t ixgbe_xmit_frame_ring(काष्ठा sk_buff *skb,
			  काष्ठा ixgbe_adapter *adapter,
			  काष्ठा ixgbe_ring *tx_ring)
अणु
	काष्ठा ixgbe_tx_buffer *first;
	पूर्णांक tso;
	u32 tx_flags = 0;
	अचिन्हित लघु f;
	u16 count = TXD_USE_COUNT(skb_headlen(skb));
	काष्ठा ixgbe_ipsec_tx_data ipsec_tx = अणु 0 पूर्ण;
	__be16 protocol = skb->protocol;
	u8 hdr_len = 0;

	/*
	 * need: 1 descriptor per page * PAGE_SIZE/IXGBE_MAX_DATA_PER_TXD,
	 *       + 1 desc क्रम skb_headlen/IXGBE_MAX_DATA_PER_TXD,
	 *       + 2 desc gap to keep tail from touching head,
	 *       + 1 desc क्रम context descriptor,
	 * otherwise try next समय
	 */
	क्रम (f = 0; f < skb_shinfo(skb)->nr_frags; f++)
		count += TXD_USE_COUNT(skb_frag_size(
						&skb_shinfo(skb)->frags[f]));

	अगर (ixgbe_maybe_stop_tx(tx_ring, count + 3)) अणु
		tx_ring->tx_stats.tx_busy++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* record the location of the first descriptor क्रम this packet */
	first = &tx_ring->tx_buffer_info[tx_ring->next_to_use];
	first->skb = skb;
	first->bytecount = skb->len;
	first->gso_segs = 1;

	/* अगर we have a HW VLAN tag being added शेष to the HW one */
	अगर (skb_vlan_tag_present(skb)) अणु
		tx_flags |= skb_vlan_tag_get(skb) << IXGBE_TX_FLAGS_VLAN_SHIFT;
		tx_flags |= IXGBE_TX_FLAGS_HW_VLAN;
	/* अन्यथा अगर it is a SW VLAN check the next protocol and store the tag */
	पूर्ण अन्यथा अगर (protocol == htons(ETH_P_8021Q)) अणु
		काष्ठा vlan_hdr *vhdr, _vhdr;
		vhdr = skb_header_poपूर्णांकer(skb, ETH_HLEN, माप(_vhdr), &_vhdr);
		अगर (!vhdr)
			जाओ out_drop;

		tx_flags |= ntohs(vhdr->h_vlan_TCI) <<
				  IXGBE_TX_FLAGS_VLAN_SHIFT;
		tx_flags |= IXGBE_TX_FLAGS_SW_VLAN;
	पूर्ण
	protocol = vlan_get_protocol(skb);

	अगर (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) &&
	    adapter->ptp_घड़ी) अणु
		अगर (adapter->tstamp_config.tx_type == HWTSTAMP_TX_ON &&
		    !test_and_set_bit_lock(__IXGBE_PTP_TX_IN_PROGRESS,
					   &adapter->state)) अणु
			skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
			tx_flags |= IXGBE_TX_FLAGS_TSTAMP;

			/* schedule check क्रम Tx बारtamp */
			adapter->ptp_tx_skb = skb_get(skb);
			adapter->ptp_tx_start = jअगरfies;
			schedule_work(&adapter->ptp_tx_work);
		पूर्ण अन्यथा अणु
			adapter->tx_hwtstamp_skipped++;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
	/*
	 * Use the l2चयन_enable flag - would be false अगर the DMA
	 * Tx चयन had been disabled.
	 */
	अगर (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED)
		tx_flags |= IXGBE_TX_FLAGS_CC;

#पूर्ण_अगर
	/* DCB maps skb priorities 0-7 onto 3 bit PCP of VLAN tag. */
	अगर ((adapter->flags & IXGBE_FLAG_DCB_ENABLED) &&
	    ((tx_flags & (IXGBE_TX_FLAGS_HW_VLAN | IXGBE_TX_FLAGS_SW_VLAN)) ||
	     (skb->priority != TC_PRIO_CONTROL))) अणु
		tx_flags &= ~IXGBE_TX_FLAGS_VLAN_PRIO_MASK;
		tx_flags |= (skb->priority & 0x7) <<
					IXGBE_TX_FLAGS_VLAN_PRIO_SHIFT;
		अगर (tx_flags & IXGBE_TX_FLAGS_SW_VLAN) अणु
			काष्ठा vlan_ethhdr *vhdr;

			अगर (skb_cow_head(skb, 0))
				जाओ out_drop;
			vhdr = (काष्ठा vlan_ethhdr *)skb->data;
			vhdr->h_vlan_TCI = htons(tx_flags >>
						 IXGBE_TX_FLAGS_VLAN_SHIFT);
		पूर्ण अन्यथा अणु
			tx_flags |= IXGBE_TX_FLAGS_HW_VLAN;
		पूर्ण
	पूर्ण

	/* record initial flags and protocol */
	first->tx_flags = tx_flags;
	first->protocol = protocol;

#अगर_घोषित IXGBE_FCOE
	/* setup tx offload क्रम FCoE */
	अगर ((protocol == htons(ETH_P_FCOE)) &&
	    (tx_ring->netdev->features & (NETIF_F_FSO | NETIF_F_FCOE_CRC))) अणु
		tso = ixgbe_fso(tx_ring, first, &hdr_len);
		अगर (tso < 0)
			जाओ out_drop;

		जाओ xmit_fcoe;
	पूर्ण

#पूर्ण_अगर /* IXGBE_FCOE */

#अगर_घोषित CONFIG_IXGBE_IPSEC
	अगर (xfrm_offload(skb) &&
	    !ixgbe_ipsec_tx(tx_ring, first, &ipsec_tx))
		जाओ out_drop;
#पूर्ण_अगर
	tso = ixgbe_tso(tx_ring, first, &hdr_len, &ipsec_tx);
	अगर (tso < 0)
		जाओ out_drop;
	अन्यथा अगर (!tso)
		ixgbe_tx_csum(tx_ring, first, &ipsec_tx);

	/* add the ATR filter अगर ATR is on */
	अगर (test_bit(__IXGBE_TX_Fसूची_INIT_DONE, &tx_ring->state))
		ixgbe_atr(tx_ring, first);

#अगर_घोषित IXGBE_FCOE
xmit_fcoe:
#पूर्ण_अगर /* IXGBE_FCOE */
	अगर (ixgbe_tx_map(tx_ring, first, hdr_len))
		जाओ cleanup_tx_बारtamp;

	वापस NETDEV_TX_OK;

out_drop:
	dev_kमुक्त_skb_any(first->skb);
	first->skb = शून्य;
cleanup_tx_बारtamp:
	अगर (unlikely(tx_flags & IXGBE_TX_FLAGS_TSTAMP)) अणु
		dev_kमुक्त_skb_any(adapter->ptp_tx_skb);
		adapter->ptp_tx_skb = शून्य;
		cancel_work_sync(&adapter->ptp_tx_work);
		clear_bit_unlock(__IXGBE_PTP_TX_IN_PROGRESS, &adapter->state);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल netdev_tx_t __ixgbe_xmit_frame(काष्ठा sk_buff *skb,
				      काष्ठा net_device *netdev,
				      काष्ठा ixgbe_ring *ring)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_ring *tx_ring;

	/*
	 * The minimum packet size क्रम olinfo paylen is 17 so pad the skb
	 * in order to meet this minimum size requirement.
	 */
	अगर (skb_put_padto(skb, 17))
		वापस NETDEV_TX_OK;

	tx_ring = ring ? ring : adapter->tx_ring[skb_get_queue_mapping(skb)];
	अगर (unlikely(test_bit(__IXGBE_TX_DISABLED, &tx_ring->state)))
		वापस NETDEV_TX_BUSY;

	वापस ixgbe_xmit_frame_ring(skb, adapter, tx_ring);
पूर्ण

अटल netdev_tx_t ixgbe_xmit_frame(काष्ठा sk_buff *skb,
				    काष्ठा net_device *netdev)
अणु
	वापस __ixgbe_xmit_frame(skb, netdev, शून्य);
पूर्ण

/**
 * ixgbe_set_mac - Change the Ethernet Address of the NIC
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @p: poपूर्णांकer to an address काष्ठाure
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक ixgbe_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	स_नकल(hw->mac.addr, addr->sa_data, netdev->addr_len);

	ixgbe_mac_set_शेष_filter(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक
ixgbe_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक prtad, पूर्णांक devad, u16 addr)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u16 value;
	पूर्णांक rc;

	अगर (adapter->mii_bus) अणु
		पूर्णांक regnum = addr;

		अगर (devad != MDIO_DEVAD_NONE)
			regnum |= (devad << 16) | MII_ADDR_C45;

		वापस mdiobus_पढ़ो(adapter->mii_bus, prtad, regnum);
	पूर्ण

	अगर (prtad != hw->phy.mdio.prtad)
		वापस -EINVAL;
	rc = hw->phy.ops.पढ़ो_reg(hw, addr, devad, &value);
	अगर (!rc)
		rc = value;
	वापस rc;
पूर्ण

अटल पूर्णांक ixgbe_mdio_ग_लिखो(काष्ठा net_device *netdev, पूर्णांक prtad, पूर्णांक devad,
			    u16 addr, u16 value)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	अगर (adapter->mii_bus) अणु
		पूर्णांक regnum = addr;

		अगर (devad != MDIO_DEVAD_NONE)
			regnum |= (devad << 16) | MII_ADDR_C45;

		वापस mdiobus_ग_लिखो(adapter->mii_bus, prtad, regnum, value);
	पूर्ण

	अगर (prtad != hw->phy.mdio.prtad)
		वापस -EINVAL;
	वापस hw->phy.ops.ग_लिखो_reg(hw, addr, devad, value);
पूर्ण

अटल पूर्णांक ixgbe_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *req, पूर्णांक cmd)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		वापस ixgbe_ptp_set_ts_config(adapter, req);
	हाल SIOCGHWTSTAMP:
		वापस ixgbe_ptp_get_ts_config(adapter, req);
	हाल SIOCGMIIPHY:
		अगर (!adapter->hw.phy.ops.पढ़ो_reg)
			वापस -EOPNOTSUPP;
		fallthrough;
	शेष:
		वापस mdio_mii_ioctl(&adapter->hw.phy.mdio, अगर_mii(req), cmd);
	पूर्ण
पूर्ण

/**
 * ixgbe_add_sanmac_netdev - Add the SAN MAC address to the corresponding
 * netdev->dev_addrs
 * @dev: network पूर्णांकerface device काष्ठाure
 *
 * Returns non-zero on failure
 **/
अटल पूर्णांक ixgbe_add_sanmac_netdev(काष्ठा net_device *dev)
अणु
	पूर्णांक err = 0;
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	अगर (is_valid_ether_addr(hw->mac.san_addr)) अणु
		rtnl_lock();
		err = dev_addr_add(dev, hw->mac.san_addr, NETDEV_HW_ADDR_T_SAN);
		rtnl_unlock();

		/* update SAN MAC vmdq pool selection */
		hw->mac.ops.set_vmdq_san_mac(hw, VMDQ_P(0));
	पूर्ण
	वापस err;
पूर्ण

/**
 * ixgbe_del_sanmac_netdev - Removes the SAN MAC address to the corresponding
 * netdev->dev_addrs
 * @dev: network पूर्णांकerface device काष्ठाure
 *
 * Returns non-zero on failure
 **/
अटल पूर्णांक ixgbe_del_sanmac_netdev(काष्ठा net_device *dev)
अणु
	पूर्णांक err = 0;
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा ixgbe_mac_info *mac = &adapter->hw.mac;

	अगर (is_valid_ether_addr(mac->san_addr)) अणु
		rtnl_lock();
		err = dev_addr_del(dev, mac->san_addr, NETDEV_HW_ADDR_T_SAN);
		rtnl_unlock();
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम ixgbe_get_ring_stats64(काष्ठा rtnl_link_stats64 *stats,
				   काष्ठा ixgbe_ring *ring)
अणु
	u64 bytes, packets;
	अचिन्हित पूर्णांक start;

	अगर (ring) अणु
		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			packets = ring->stats.packets;
			bytes   = ring->stats.bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->syncp, start));
		stats->tx_packets += packets;
		stats->tx_bytes   += bytes;
	पूर्ण
पूर्ण

अटल व्योम ixgbe_get_stats64(काष्ठा net_device *netdev,
			      काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	पूर्णांक i;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा ixgbe_ring *ring = READ_ONCE(adapter->rx_ring[i]);
		u64 bytes, packets;
		अचिन्हित पूर्णांक start;

		अगर (ring) अणु
			करो अणु
				start = u64_stats_fetch_begin_irq(&ring->syncp);
				packets = ring->stats.packets;
				bytes   = ring->stats.bytes;
			पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->syncp, start));
			stats->rx_packets += packets;
			stats->rx_bytes   += bytes;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		काष्ठा ixgbe_ring *ring = READ_ONCE(adapter->tx_ring[i]);

		ixgbe_get_ring_stats64(stats, ring);
	पूर्ण
	क्रम (i = 0; i < adapter->num_xdp_queues; i++) अणु
		काष्ठा ixgbe_ring *ring = READ_ONCE(adapter->xdp_ring[i]);

		ixgbe_get_ring_stats64(stats, ring);
	पूर्ण
	rcu_पढ़ो_unlock();

	/* following stats updated by ixgbe_watchकरोg_task() */
	stats->multicast	= netdev->stats.multicast;
	stats->rx_errors	= netdev->stats.rx_errors;
	stats->rx_length_errors	= netdev->stats.rx_length_errors;
	stats->rx_crc_errors	= netdev->stats.rx_crc_errors;
	stats->rx_missed_errors	= netdev->stats.rx_missed_errors;
पूर्ण

#अगर_घोषित CONFIG_IXGBE_DCB
/**
 * ixgbe_validate_rtr - verअगरy 802.1Qp to Rx packet buffer mapping is valid.
 * @adapter: poपूर्णांकer to ixgbe_adapter
 * @tc: number of traffic classes currently enabled
 *
 * Configure a valid 802.1Qp to Rx packet buffer mapping ie confirm
 * 802.1Q priority maps to a packet buffer that exists.
 */
अटल व्योम ixgbe_validate_rtr(काष्ठा ixgbe_adapter *adapter, u8 tc)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 reg, rsave;
	पूर्णांक i;

	/* 82598 have a अटल priority to TC mapping that can not
	 * be changed so no validation is needed.
	 */
	अगर (hw->mac.type == ixgbe_mac_82598EB)
		वापस;

	reg = IXGBE_READ_REG(hw, IXGBE_RTRUP2TC);
	rsave = reg;

	क्रम (i = 0; i < MAX_TRAFFIC_CLASS; i++) अणु
		u8 up2tc = reg >> (i * IXGBE_RTRUP2TC_UP_SHIFT);

		/* If up2tc is out of bounds शेष to zero */
		अगर (up2tc > tc)
			reg &= ~(0x7 << IXGBE_RTRUP2TC_UP_SHIFT);
	पूर्ण

	अगर (reg != rsave)
		IXGBE_WRITE_REG(hw, IXGBE_RTRUP2TC, reg);

	वापस;
पूर्ण

/**
 * ixgbe_set_prio_tc_map - Configure netdev prio tc map
 * @adapter: Poपूर्णांकer to adapter काष्ठा
 *
 * Populate the netdev user priority to tc map
 */
अटल व्योम ixgbe_set_prio_tc_map(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा net_device *dev = adapter->netdev;
	काष्ठा ixgbe_dcb_config *dcb_cfg = &adapter->dcb_cfg;
	काष्ठा ieee_ets *ets = adapter->ixgbe_ieee_ets;
	u8 prio;

	क्रम (prio = 0; prio < MAX_USER_PRIORITY; prio++) अणु
		u8 tc = 0;

		अगर (adapter->dcbx_cap & DCB_CAP_DCBX_VER_CEE)
			tc = ixgbe_dcb_get_tc_from_up(dcb_cfg, 0, prio);
		अन्यथा अगर (ets)
			tc = ets->prio_tc[prio];

		netdev_set_prio_tc_map(dev, prio, tc);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_IXGBE_DCB */
अटल पूर्णांक ixgbe_reassign_macvlan_pool(काष्ठा net_device *vdev,
				       काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा ixgbe_adapter *adapter = (काष्ठा ixgbe_adapter *)priv->data;
	काष्ठा ixgbe_fwd_adapter *accel;
	पूर्णांक pool;

	/* we only care about macvlans... */
	अगर (!netअगर_is_macvlan(vdev))
		वापस 0;

	/* that have hardware offload enabled... */
	accel = macvlan_accel_priv(vdev);
	अगर (!accel)
		वापस 0;

	/* If we can relocate to a dअगरferent bit करो so */
	pool = find_first_zero_bit(adapter->fwd_biपंचांगask, adapter->num_rx_pools);
	अगर (pool < adapter->num_rx_pools) अणु
		set_bit(pool, adapter->fwd_biपंचांगask);
		accel->pool = pool;
		वापस 0;
	पूर्ण

	/* अगर we cannot find a मुक्त pool then disable the offload */
	netdev_err(vdev, "L2FW offload disabled due to lack of queue resources\n");
	macvlan_release_l2fw_offload(vdev);

	/* unbind the queues and drop the subordinate channel config */
	netdev_unbind_sb_channel(adapter->netdev, vdev);
	netdev_set_sb_channel(vdev, 0);

	kमुक्त(accel);

	वापस 0;
पूर्ण

अटल व्योम ixgbe_defrag_macvlan_pools(काष्ठा net_device *dev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा netdev_nested_priv priv = अणु
		.data = (व्योम *)adapter,
	पूर्ण;

	/* flush any stale bits out of the fwd biपंचांगask */
	biपंचांगap_clear(adapter->fwd_biपंचांगask, 1, 63);

	/* walk through upper devices reassigning pools */
	netdev_walk_all_upper_dev_rcu(dev, ixgbe_reassign_macvlan_pool,
				      &priv);
पूर्ण

/**
 * ixgbe_setup_tc - configure net_device क्रम multiple traffic classes
 *
 * @dev: net device to configure
 * @tc: number of traffic classes to enable
 */
पूर्णांक ixgbe_setup_tc(काष्ठा net_device *dev, u8 tc)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	/* Hardware supports up to 8 traffic classes */
	अगर (tc > adapter->dcb_cfg.num_tcs.pg_tcs)
		वापस -EINVAL;

	अगर (hw->mac.type == ixgbe_mac_82598EB && tc && tc < MAX_TRAFFIC_CLASS)
		वापस -EINVAL;

	/* Hardware has to reinitialize queues and पूर्णांकerrupts to
	 * match packet buffer alignment. Unक्रमtunately, the
	 * hardware is not flexible enough to करो this dynamically.
	 */
	अगर (netअगर_running(dev))
		ixgbe_बंद(dev);
	अन्यथा
		ixgbe_reset(adapter);

	ixgbe_clear_पूर्णांकerrupt_scheme(adapter);

#अगर_घोषित CONFIG_IXGBE_DCB
	अगर (tc) अणु
		अगर (adapter->xdp_prog) अणु
			e_warn(probe, "DCB is not supported with XDP\n");

			ixgbe_init_पूर्णांकerrupt_scheme(adapter);
			अगर (netअगर_running(dev))
				ixgbe_खोलो(dev);
			वापस -EINVAL;
		पूर्ण

		netdev_set_num_tc(dev, tc);
		ixgbe_set_prio_tc_map(adapter);

		adapter->hw_tcs = tc;
		adapter->flags |= IXGBE_FLAG_DCB_ENABLED;

		अगर (adapter->hw.mac.type == ixgbe_mac_82598EB) अणु
			adapter->last_lfc_mode = adapter->hw.fc.requested_mode;
			adapter->hw.fc.requested_mode = ixgbe_fc_none;
		पूर्ण
	पूर्ण अन्यथा अणु
		netdev_reset_tc(dev);

		अगर (adapter->hw.mac.type == ixgbe_mac_82598EB)
			adapter->hw.fc.requested_mode = adapter->last_lfc_mode;

		adapter->flags &= ~IXGBE_FLAG_DCB_ENABLED;
		adapter->hw_tcs = tc;

		adapter->temp_dcb_cfg.pfc_mode_enable = false;
		adapter->dcb_cfg.pfc_mode_enable = false;
	पूर्ण

	ixgbe_validate_rtr(adapter, tc);

#पूर्ण_अगर /* CONFIG_IXGBE_DCB */
	ixgbe_init_पूर्णांकerrupt_scheme(adapter);

	ixgbe_defrag_macvlan_pools(dev);

	अगर (netअगर_running(dev))
		वापस ixgbe_खोलो(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_delete_clsu32(काष्ठा ixgbe_adapter *adapter,
			       काष्ठा tc_cls_u32_offload *cls)
अणु
	u32 hdl = cls->knode.handle;
	u32 uhtid = TC_U32_USERHTID(cls->knode.handle);
	u32 loc = cls->knode.handle & 0xfffff;
	पूर्णांक err = 0, i, j;
	काष्ठा ixgbe_jump_table *jump = शून्य;

	अगर (loc > IXGBE_MAX_HW_ENTRIES)
		वापस -EINVAL;

	अगर ((uhtid != 0x800) && (uhtid >= IXGBE_MAX_LINK_HANDLE))
		वापस -EINVAL;

	/* Clear this filter in the link data it is associated with */
	अगर (uhtid != 0x800) अणु
		jump = adapter->jump_tables[uhtid];
		अगर (!jump)
			वापस -EINVAL;
		अगर (!test_bit(loc - 1, jump->child_loc_map))
			वापस -EINVAL;
		clear_bit(loc - 1, jump->child_loc_map);
	पूर्ण

	/* Check अगर the filter being deleted is a link */
	क्रम (i = 1; i < IXGBE_MAX_LINK_HANDLE; i++) अणु
		jump = adapter->jump_tables[i];
		अगर (jump && jump->link_hdl == hdl) अणु
			/* Delete filters in the hardware in the child hash
			 * table associated with this link
			 */
			क्रम (j = 0; j < IXGBE_MAX_HW_ENTRIES; j++) अणु
				अगर (!test_bit(j, jump->child_loc_map))
					जारी;
				spin_lock(&adapter->fdir_perfect_lock);
				err = ixgbe_update_ethtool_fdir_entry(adapter,
								      शून्य,
								      j + 1);
				spin_unlock(&adapter->fdir_perfect_lock);
				clear_bit(j, jump->child_loc_map);
			पूर्ण
			/* Remove resources क्रम this link */
			kमुक्त(jump->input);
			kमुक्त(jump->mask);
			kमुक्त(jump);
			adapter->jump_tables[i] = शून्य;
			वापस err;
		पूर्ण
	पूर्ण

	spin_lock(&adapter->fdir_perfect_lock);
	err = ixgbe_update_ethtool_fdir_entry(adapter, शून्य, loc);
	spin_unlock(&adapter->fdir_perfect_lock);
	वापस err;
पूर्ण

अटल पूर्णांक ixgbe_configure_clsu32_add_hnode(काष्ठा ixgbe_adapter *adapter,
					    काष्ठा tc_cls_u32_offload *cls)
अणु
	u32 uhtid = TC_U32_USERHTID(cls->hnode.handle);

	अगर (uhtid >= IXGBE_MAX_LINK_HANDLE)
		वापस -EINVAL;

	/* This ixgbe devices करो not support hash tables at the moment
	 * so पात when given hash tables.
	 */
	अगर (cls->hnode.भागisor > 0)
		वापस -EINVAL;

	set_bit(uhtid - 1, &adapter->tables);
	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_configure_clsu32_del_hnode(काष्ठा ixgbe_adapter *adapter,
					    काष्ठा tc_cls_u32_offload *cls)
अणु
	u32 uhtid = TC_U32_USERHTID(cls->hnode.handle);

	अगर (uhtid >= IXGBE_MAX_LINK_HANDLE)
		वापस -EINVAL;

	clear_bit(uhtid - 1, &adapter->tables);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_CLS_ACT
काष्ठा upper_walk_data अणु
	काष्ठा ixgbe_adapter *adapter;
	u64 action;
	पूर्णांक अगरindex;
	u8 queue;
पूर्ण;

अटल पूर्णांक get_macvlan_queue(काष्ठा net_device *upper,
			     काष्ठा netdev_nested_priv *priv)
अणु
	अगर (netअगर_is_macvlan(upper)) अणु
		काष्ठा ixgbe_fwd_adapter *vadapter = macvlan_accel_priv(upper);
		काष्ठा ixgbe_adapter *adapter;
		काष्ठा upper_walk_data *data;
		पूर्णांक अगरindex;

		data = (काष्ठा upper_walk_data *)priv->data;
		अगरindex = data->अगरindex;
		adapter = data->adapter;
		अगर (vadapter && upper->अगरindex == अगरindex) अणु
			data->queue = adapter->rx_ring[vadapter->rx_base_queue]->reg_idx;
			data->action = data->queue;
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक handle_redirect_action(काष्ठा ixgbe_adapter *adapter, पूर्णांक अगरindex,
				  u8 *queue, u64 *action)
अणु
	काष्ठा ixgbe_ring_feature *vmdq = &adapter->ring_feature[RING_F_VMDQ];
	अचिन्हित पूर्णांक num_vfs = adapter->num_vfs, vf;
	काष्ठा netdev_nested_priv priv;
	काष्ठा upper_walk_data data;
	काष्ठा net_device *upper;

	/* redirect to a SRIOV VF */
	क्रम (vf = 0; vf < num_vfs; ++vf) अणु
		upper = pci_get_drvdata(adapter->vfinfo[vf].vfdev);
		अगर (upper->अगरindex == अगरindex) अणु
			*queue = vf * __ALIGN_MASK(1, ~vmdq->mask);
			*action = vf + 1;
			*action <<= ETHTOOL_RX_FLOW_SPEC_RING_VF_OFF;
			वापस 0;
		पूर्ण
	पूर्ण

	/* redirect to a offloaded macvlan netdev */
	data.adapter = adapter;
	data.अगरindex = अगरindex;
	data.action = 0;
	data.queue = 0;
	priv.data = (व्योम *)&data;
	अगर (netdev_walk_all_upper_dev_rcu(adapter->netdev,
					  get_macvlan_queue, &priv)) अणु
		*action = data.action;
		*queue = data.queue;

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक parse_tc_actions(काष्ठा ixgbe_adapter *adapter,
			    काष्ठा tcf_exts *exts, u64 *action, u8 *queue)
अणु
	स्थिर काष्ठा tc_action *a;
	पूर्णांक i;

	अगर (!tcf_exts_has_actions(exts))
		वापस -EINVAL;

	tcf_exts_क्रम_each_action(i, a, exts) अणु
		/* Drop action */
		अगर (is_tcf_gact_shot(a)) अणु
			*action = IXGBE_Fसूची_DROP_QUEUE;
			*queue = IXGBE_Fसूची_DROP_QUEUE;
			वापस 0;
		पूर्ण

		/* Redirect to a VF or a offloaded macvlan */
		अगर (is_tcf_mirred_egress_redirect(a)) अणु
			काष्ठा net_device *dev = tcf_mirred_dev(a);

			अगर (!dev)
				वापस -EINVAL;
			वापस handle_redirect_action(adapter, dev->अगरindex,
						      queue, action);
		पूर्ण

		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण
#अन्यथा
अटल पूर्णांक parse_tc_actions(काष्ठा ixgbe_adapter *adapter,
			    काष्ठा tcf_exts *exts, u64 *action, u8 *queue)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_NET_CLS_ACT */

अटल पूर्णांक ixgbe_clsu32_build_input(काष्ठा ixgbe_fdir_filter *input,
				    जोड़ ixgbe_atr_input *mask,
				    काष्ठा tc_cls_u32_offload *cls,
				    काष्ठा ixgbe_mat_field *field_ptr,
				    काष्ठा ixgbe_nexthdr *nexthdr)
अणु
	पूर्णांक i, j, off;
	__be32 val, m;
	bool found_entry = false, found_jump_field = false;

	क्रम (i = 0; i < cls->knode.sel->nkeys; i++) अणु
		off = cls->knode.sel->keys[i].off;
		val = cls->knode.sel->keys[i].val;
		m = cls->knode.sel->keys[i].mask;

		क्रम (j = 0; field_ptr[j].val; j++) अणु
			अगर (field_ptr[j].off == off) अणु
				field_ptr[j].val(input, mask, (__क्रमce u32)val,
						 (__क्रमce u32)m);
				input->filter.क्रमmatted.flow_type |=
					field_ptr[j].type;
				found_entry = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (nexthdr) अणु
			अगर (nexthdr->off == cls->knode.sel->keys[i].off &&
			    nexthdr->val ==
			    (__क्रमce u32)cls->knode.sel->keys[i].val &&
			    nexthdr->mask ==
			    (__क्रमce u32)cls->knode.sel->keys[i].mask)
				found_jump_field = true;
			अन्यथा
				जारी;
		पूर्ण
	पूर्ण

	अगर (nexthdr && !found_jump_field)
		वापस -EINVAL;

	अगर (!found_entry)
		वापस 0;

	mask->क्रमmatted.flow_type = IXGBE_ATR_L4TYPE_IPV6_MASK |
				    IXGBE_ATR_L4TYPE_MASK;

	अगर (input->filter.क्रमmatted.flow_type == IXGBE_ATR_FLOW_TYPE_IPV4)
		mask->क्रमmatted.flow_type &= IXGBE_ATR_L4TYPE_IPV6_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_configure_clsu32(काष्ठा ixgbe_adapter *adapter,
				  काष्ठा tc_cls_u32_offload *cls)
अणु
	__be16 protocol = cls->common.protocol;
	u32 loc = cls->knode.handle & 0xfffff;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा ixgbe_mat_field *field_ptr;
	काष्ठा ixgbe_fdir_filter *input = शून्य;
	जोड़ ixgbe_atr_input *mask = शून्य;
	काष्ठा ixgbe_jump_table *jump = शून्य;
	पूर्णांक i, err = -EINVAL;
	u8 queue;
	u32 uhtid, link_uhtid;

	uhtid = TC_U32_USERHTID(cls->knode.handle);
	link_uhtid = TC_U32_USERHTID(cls->knode.link_handle);

	/* At the moment cls_u32 jumps to network layer and skips past
	 * L2 headers. The canonical method to match L2 frames is to use
	 * negative values. However this is error prone at best but really
	 * just broken because there is no way to "know" what sort of hdr
	 * is in front of the network layer. Fix cls_u32 to support L2
	 * headers when needed.
	 */
	अगर (protocol != htons(ETH_P_IP))
		वापस err;

	अगर (loc >= ((1024 << adapter->fdir_pballoc) - 2)) अणु
		e_err(drv, "Location out of range\n");
		वापस err;
	पूर्ण

	/* cls u32 is a graph starting at root node 0x800. The driver tracks
	 * links and also the fields used to advance the parser across each
	 * link (e.g. nexthdr/eat parameters from 'tc'). This way we can map
	 * the u32 graph onto the hardware parse graph denoted in ixgbe_model.h
	 * To add support क्रम new nodes update ixgbe_model.h parse काष्ठाures
	 * this function _should_ be generic try not to hardcode values here.
	 */
	अगर (uhtid == 0x800) अणु
		field_ptr = (adapter->jump_tables[0])->mat;
	पूर्ण अन्यथा अणु
		अगर (uhtid >= IXGBE_MAX_LINK_HANDLE)
			वापस err;
		अगर (!adapter->jump_tables[uhtid])
			वापस err;
		field_ptr = (adapter->jump_tables[uhtid])->mat;
	पूर्ण

	अगर (!field_ptr)
		वापस err;

	/* At this poपूर्णांक we know the field_ptr is valid and need to either
	 * build cls_u32 link or attach filter. Because adding a link to
	 * a handle that करोes not exist is invalid and the same क्रम adding
	 * rules to handles that करोn't exist.
	 */

	अगर (link_uhtid) अणु
		काष्ठा ixgbe_nexthdr *nexthdr = ixgbe_ipv4_jumps;

		अगर (link_uhtid >= IXGBE_MAX_LINK_HANDLE)
			वापस err;

		अगर (!test_bit(link_uhtid - 1, &adapter->tables))
			वापस err;

		/* Multiple filters as links to the same hash table are not
		 * supported. To add a new filter with the same next header
		 * but dअगरferent match/jump conditions, create a new hash table
		 * and link to it.
		 */
		अगर (adapter->jump_tables[link_uhtid] &&
		    (adapter->jump_tables[link_uhtid])->link_hdl) अणु
			e_err(drv, "Link filter exists for link: %x\n",
			      link_uhtid);
			वापस err;
		पूर्ण

		क्रम (i = 0; nexthdr[i].jump; i++) अणु
			अगर (nexthdr[i].o != cls->knode.sel->offoff ||
			    nexthdr[i].s != cls->knode.sel->offshअगरt ||
			    nexthdr[i].m !=
			    (__क्रमce u32)cls->knode.sel->offmask)
				वापस err;

			jump = kzalloc(माप(*jump), GFP_KERNEL);
			अगर (!jump)
				वापस -ENOMEM;
			input = kzalloc(माप(*input), GFP_KERNEL);
			अगर (!input) अणु
				err = -ENOMEM;
				जाओ मुक्त_jump;
			पूर्ण
			mask = kzalloc(माप(*mask), GFP_KERNEL);
			अगर (!mask) अणु
				err = -ENOMEM;
				जाओ मुक्त_input;
			पूर्ण
			jump->input = input;
			jump->mask = mask;
			jump->link_hdl = cls->knode.handle;

			err = ixgbe_clsu32_build_input(input, mask, cls,
						       field_ptr, &nexthdr[i]);
			अगर (!err) अणु
				jump->mat = nexthdr[i].jump;
				adapter->jump_tables[link_uhtid] = jump;
				अवरोध;
			पूर्ण अन्यथा अणु
				kमुक्त(mask);
				kमुक्त(input);
				kमुक्त(jump);
			पूर्ण
		पूर्ण
		वापस 0;
	पूर्ण

	input = kzalloc(माप(*input), GFP_KERNEL);
	अगर (!input)
		वापस -ENOMEM;
	mask = kzalloc(माप(*mask), GFP_KERNEL);
	अगर (!mask) अणु
		err = -ENOMEM;
		जाओ मुक्त_input;
	पूर्ण

	अगर ((uhtid != 0x800) && (adapter->jump_tables[uhtid])) अणु
		अगर ((adapter->jump_tables[uhtid])->input)
			स_नकल(input, (adapter->jump_tables[uhtid])->input,
			       माप(*input));
		अगर ((adapter->jump_tables[uhtid])->mask)
			स_नकल(mask, (adapter->jump_tables[uhtid])->mask,
			       माप(*mask));

		/* Lookup in all child hash tables अगर this location is alपढ़ोy
		 * filled with a filter
		 */
		क्रम (i = 1; i < IXGBE_MAX_LINK_HANDLE; i++) अणु
			काष्ठा ixgbe_jump_table *link = adapter->jump_tables[i];

			अगर (link && (test_bit(loc - 1, link->child_loc_map))) अणु
				e_err(drv, "Filter exists in location: %x\n",
				      loc);
				err = -EINVAL;
				जाओ err_out;
			पूर्ण
		पूर्ण
	पूर्ण
	err = ixgbe_clsu32_build_input(input, mask, cls, field_ptr, शून्य);
	अगर (err)
		जाओ err_out;

	err = parse_tc_actions(adapter, cls->knode.exts, &input->action,
			       &queue);
	अगर (err < 0)
		जाओ err_out;

	input->sw_idx = loc;

	spin_lock(&adapter->fdir_perfect_lock);

	अगर (hlist_empty(&adapter->fdir_filter_list)) अणु
		स_नकल(&adapter->fdir_mask, mask, माप(*mask));
		err = ixgbe_fdir_set_input_mask_82599(hw, mask);
		अगर (err)
			जाओ err_out_w_lock;
	पूर्ण अन्यथा अगर (स_भेद(&adapter->fdir_mask, mask, माप(*mask))) अणु
		err = -EINVAL;
		जाओ err_out_w_lock;
	पूर्ण

	ixgbe_atr_compute_perfect_hash_82599(&input->filter, mask);
	err = ixgbe_fdir_ग_लिखो_perfect_filter_82599(hw, &input->filter,
						    input->sw_idx, queue);
	अगर (err)
		जाओ err_out_w_lock;

	ixgbe_update_ethtool_fdir_entry(adapter, input, input->sw_idx);
	spin_unlock(&adapter->fdir_perfect_lock);

	अगर ((uhtid != 0x800) && (adapter->jump_tables[uhtid]))
		set_bit(loc - 1, (adapter->jump_tables[uhtid])->child_loc_map);

	kमुक्त(mask);
	वापस err;
err_out_w_lock:
	spin_unlock(&adapter->fdir_perfect_lock);
err_out:
	kमुक्त(mask);
मुक्त_input:
	kमुक्त(input);
मुक्त_jump:
	kमुक्त(jump);
	वापस err;
पूर्ण

अटल पूर्णांक ixgbe_setup_tc_cls_u32(काष्ठा ixgbe_adapter *adapter,
				  काष्ठा tc_cls_u32_offload *cls_u32)
अणु
	चयन (cls_u32->command) अणु
	हाल TC_CLSU32_NEW_KNODE:
	हाल TC_CLSU32_REPLACE_KNODE:
		वापस ixgbe_configure_clsu32(adapter, cls_u32);
	हाल TC_CLSU32_DELETE_KNODE:
		वापस ixgbe_delete_clsu32(adapter, cls_u32);
	हाल TC_CLSU32_NEW_HNODE:
	हाल TC_CLSU32_REPLACE_HNODE:
		वापस ixgbe_configure_clsu32_add_hnode(adapter, cls_u32);
	हाल TC_CLSU32_DELETE_HNODE:
		वापस ixgbe_configure_clsu32_del_hnode(adapter, cls_u32);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ixgbe_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data,
				   व्योम *cb_priv)
अणु
	काष्ठा ixgbe_adapter *adapter = cb_priv;

	अगर (!tc_cls_can_offload_and_chain0(adapter->netdev, type_data))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSU32:
		वापस ixgbe_setup_tc_cls_u32(adapter, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ixgbe_setup_tc_mqprio(काष्ठा net_device *dev,
				 काष्ठा tc_mqprio_qopt *mqprio)
अणु
	mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;
	वापस ixgbe_setup_tc(dev, mqprio->num_tc);
पूर्ण

अटल LIST_HEAD(ixgbe_block_cb_list);

अटल पूर्णांक __ixgbe_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
			    व्योम *type_data)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);

	चयन (type) अणु
	हाल TC_SETUP_BLOCK:
		वापस flow_block_cb_setup_simple(type_data,
						  &ixgbe_block_cb_list,
						  ixgbe_setup_tc_block_cb,
						  adapter, adapter, true);
	हाल TC_SETUP_QDISC_MQPRIO:
		वापस ixgbe_setup_tc_mqprio(dev, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
व्योम ixgbe_sriov_reinit(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	rtnl_lock();
	ixgbe_setup_tc(netdev, adapter->hw_tcs);
	rtnl_unlock();
पूर्ण

#पूर्ण_अगर
व्योम ixgbe_करो_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	अगर (netअगर_running(netdev))
		ixgbe_reinit_locked(adapter);
	अन्यथा
		ixgbe_reset(adapter);
पूर्ण

अटल netdev_features_t ixgbe_fix_features(काष्ठा net_device *netdev,
					    netdev_features_t features)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	/* If Rx checksum is disabled, then RSC/LRO should also be disabled */
	अगर (!(features & NETIF_F_RXCSUM))
		features &= ~NETIF_F_LRO;

	/* Turn off LRO अगर not RSC capable */
	अगर (!(adapter->flags2 & IXGBE_FLAG2_RSC_CAPABLE))
		features &= ~NETIF_F_LRO;

	अगर (adapter->xdp_prog && (features & NETIF_F_LRO)) अणु
		e_dev_err("LRO is not supported with XDP\n");
		features &= ~NETIF_F_LRO;
	पूर्ण

	वापस features;
पूर्ण

अटल व्योम ixgbe_reset_l2fw_offload(काष्ठा ixgbe_adapter *adapter)
अणु
	पूर्णांक rss = min_t(पूर्णांक, ixgbe_max_rss_indices(adapter),
			num_online_cpus());

	/* go back to full RSS अगर we're not running SR-IOV */
	अगर (!adapter->ring_feature[RING_F_VMDQ].offset)
		adapter->flags &= ~(IXGBE_FLAG_VMDQ_ENABLED |
				    IXGBE_FLAG_SRIOV_ENABLED);

	adapter->ring_feature[RING_F_RSS].limit = rss;
	adapter->ring_feature[RING_F_VMDQ].limit = 1;

	ixgbe_setup_tc(adapter->netdev, adapter->hw_tcs);
पूर्ण

अटल पूर्णांक ixgbe_set_features(काष्ठा net_device *netdev,
			      netdev_features_t features)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	netdev_features_t changed = netdev->features ^ features;
	bool need_reset = false;

	/* Make sure RSC matches LRO, reset अगर change */
	अगर (!(features & NETIF_F_LRO)) अणु
		अगर (adapter->flags2 & IXGBE_FLAG2_RSC_ENABLED)
			need_reset = true;
		adapter->flags2 &= ~IXGBE_FLAG2_RSC_ENABLED;
	पूर्ण अन्यथा अगर ((adapter->flags2 & IXGBE_FLAG2_RSC_CAPABLE) &&
		   !(adapter->flags2 & IXGBE_FLAG2_RSC_ENABLED)) अणु
		अगर (adapter->rx_itr_setting == 1 ||
		    adapter->rx_itr_setting > IXGBE_MIN_RSC_ITR) अणु
			adapter->flags2 |= IXGBE_FLAG2_RSC_ENABLED;
			need_reset = true;
		पूर्ण अन्यथा अगर ((changed ^ features) & NETIF_F_LRO) अणु
			e_info(probe, "rx-usecs set too low, "
			       "disabling RSC\n");
		पूर्ण
	पूर्ण

	/*
	 * Check अगर Flow Director n-tuple support or hw_tc support was
	 * enabled or disabled.  If the state changed, we need to reset.
	 */
	अगर ((features & NETIF_F_NTUPLE) || (features & NETIF_F_HW_TC)) अणु
		/* turn off ATR, enable perfect filters and reset */
		अगर (!(adapter->flags & IXGBE_FLAG_Fसूची_PERFECT_CAPABLE))
			need_reset = true;

		adapter->flags &= ~IXGBE_FLAG_Fसूची_HASH_CAPABLE;
		adapter->flags |= IXGBE_FLAG_Fसूची_PERFECT_CAPABLE;
	पूर्ण अन्यथा अणु
		/* turn off perfect filters, enable ATR and reset */
		अगर (adapter->flags & IXGBE_FLAG_Fसूची_PERFECT_CAPABLE)
			need_reset = true;

		adapter->flags &= ~IXGBE_FLAG_Fसूची_PERFECT_CAPABLE;

		/* We cannot enable ATR अगर SR-IOV is enabled */
		अगर (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED ||
		    /* We cannot enable ATR अगर we have 2 or more tcs */
		    (adapter->hw_tcs > 1) ||
		    /* We cannot enable ATR अगर RSS is disabled */
		    (adapter->ring_feature[RING_F_RSS].limit <= 1) ||
		    /* A sample rate of 0 indicates ATR disabled */
		    (!adapter->atr_sample_rate))
			; /* करो nothing not supported */
		अन्यथा /* otherwise supported and set the flag */
			adapter->flags |= IXGBE_FLAG_Fसूची_HASH_CAPABLE;
	पूर्ण

	अगर (changed & NETIF_F_RXALL)
		need_reset = true;

	netdev->features = features;

	अगर ((changed & NETIF_F_HW_L2FW_DOFFLOAD) && adapter->num_rx_pools > 1)
		ixgbe_reset_l2fw_offload(adapter);
	अन्यथा अगर (need_reset)
		ixgbe_करो_reset(netdev);
	अन्यथा अगर (changed & (NETIF_F_HW_VLAN_CTAG_RX |
			    NETIF_F_HW_VLAN_CTAG_FILTER))
		ixgbe_set_rx_mode(netdev);

	वापस 1;
पूर्ण

अटल पूर्णांक ixgbe_nकरो_fdb_add(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
			     काष्ठा net_device *dev,
			     स्थिर अचिन्हित अक्षर *addr, u16 vid,
			     u16 flags,
			     काष्ठा netlink_ext_ack *extack)
अणु
	/* guarantee we can provide a unique filter क्रम the unicast address */
	अगर (is_unicast_ether_addr(addr) || is_link_local_ether_addr(addr)) अणु
		काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
		u16 pool = VMDQ_P(0);

		अगर (netdev_uc_count(dev) >= ixgbe_available_rars(adapter, pool))
			वापस -ENOMEM;
	पूर्ण

	वापस nकरो_dflt_fdb_add(ndm, tb, dev, addr, vid, flags);
पूर्ण

/**
 * ixgbe_configure_bridge_mode - set various bridge modes
 * @adapter: the निजी काष्ठाure
 * @mode: requested bridge mode
 *
 * Configure some settings require क्रम various bridge modes.
 **/
अटल पूर्णांक ixgbe_configure_bridge_mode(काष्ठा ixgbe_adapter *adapter,
				       __u16 mode)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	अचिन्हित पूर्णांक p, num_pools;
	u32 vmdctl;

	चयन (mode) अणु
	हाल BRIDGE_MODE_VEPA:
		/* disable Tx loopback, rely on चयन hairpin mode */
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_PFDTXGSWC, 0);

		/* must enable Rx चयनing replication to allow multicast
		 * packet reception on all VFs, and to enable source address
		 * pruning.
		 */
		vmdctl = IXGBE_READ_REG(hw, IXGBE_VMD_CTL);
		vmdctl |= IXGBE_VT_CTL_REPLEN;
		IXGBE_WRITE_REG(hw, IXGBE_VMD_CTL, vmdctl);

		/* enable Rx source address pruning. Note, this requires
		 * replication to be enabled or अन्यथा it करोes nothing.
		 */
		num_pools = adapter->num_vfs + adapter->num_rx_pools;
		क्रम (p = 0; p < num_pools; p++) अणु
			अगर (hw->mac.ops.set_source_address_pruning)
				hw->mac.ops.set_source_address_pruning(hw,
								       true,
								       p);
		पूर्ण
		अवरोध;
	हाल BRIDGE_MODE_VEB:
		/* enable Tx loopback क्रम पूर्णांकernal VF/PF communication */
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_PFDTXGSWC,
				IXGBE_PFDTXGSWC_VT_LBEN);

		/* disable Rx चयनing replication unless we have SR-IOV
		 * भव functions
		 */
		vmdctl = IXGBE_READ_REG(hw, IXGBE_VMD_CTL);
		अगर (!adapter->num_vfs)
			vmdctl &= ~IXGBE_VT_CTL_REPLEN;
		IXGBE_WRITE_REG(hw, IXGBE_VMD_CTL, vmdctl);

		/* disable Rx source address pruning, since we करोn't expect to
		 * be receiving बाह्यal loopback of our transmitted frames.
		 */
		num_pools = adapter->num_vfs + adapter->num_rx_pools;
		क्रम (p = 0; p < num_pools; p++) अणु
			अगर (hw->mac.ops.set_source_address_pruning)
				hw->mac.ops.set_source_address_pruning(hw,
								       false,
								       p);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	adapter->bridge_mode = mode;

	e_info(drv, "enabling bridge mode: %s\n",
	       mode == BRIDGE_MODE_VEPA ? "VEPA" : "VEB");

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_nकरो_bridge_setlink(काष्ठा net_device *dev,
				    काष्ठा nlmsghdr *nlh, u16 flags,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा nlattr *attr, *br_spec;
	पूर्णांक rem;

	अगर (!(adapter->flags & IXGBE_FLAG_SRIOV_ENABLED))
		वापस -EOPNOTSUPP;

	br_spec = nlmsg_find_attr(nlh, माप(काष्ठा अगरinfomsg), IFLA_AF_SPEC);
	अगर (!br_spec)
		वापस -EINVAL;

	nla_क्रम_each_nested(attr, br_spec, rem) अणु
		पूर्णांक status;
		__u16 mode;

		अगर (nla_type(attr) != IFLA_BRIDGE_MODE)
			जारी;

		अगर (nla_len(attr) < माप(mode))
			वापस -EINVAL;

		mode = nla_get_u16(attr);
		status = ixgbe_configure_bridge_mode(adapter, mode);
		अगर (status)
			वापस status;

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_nकरो_bridge_getlink(काष्ठा sk_buff *skb, u32 pid, u32 seq,
				    काष्ठा net_device *dev,
				    u32 filter_mask, पूर्णांक nlflags)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);

	अगर (!(adapter->flags & IXGBE_FLAG_SRIOV_ENABLED))
		वापस 0;

	वापस nकरो_dflt_bridge_getlink(skb, pid, seq, dev,
				       adapter->bridge_mode, 0, 0, nlflags,
				       filter_mask, शून्य);
पूर्ण

अटल व्योम *ixgbe_fwd_add(काष्ठा net_device *pdev, काष्ठा net_device *vdev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(pdev);
	काष्ठा ixgbe_fwd_adapter *accel;
	पूर्णांक tcs = adapter->hw_tcs ? : 1;
	पूर्णांक pool, err;

	अगर (adapter->xdp_prog) अणु
		e_warn(probe, "L2FW offload is not supported with XDP\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* The hardware supported by ixgbe only filters on the destination MAC
	 * address. In order to aव्योम issues we only support offloading modes
	 * where the hardware can actually provide the functionality.
	 */
	अगर (!macvlan_supports_dest_filter(vdev))
		वापस ERR_PTR(-EMEDIUMTYPE);

	/* We need to lock करोwn the macvlan to be a single queue device so that
	 * we can reuse the tc_to_txq field in the macvlan netdev to represent
	 * the queue mapping to our netdev.
	 */
	अगर (netअगर_is_multiqueue(vdev))
		वापस ERR_PTR(-दुस्फल);

	pool = find_first_zero_bit(adapter->fwd_biपंचांगask, adapter->num_rx_pools);
	अगर (pool == adapter->num_rx_pools) अणु
		u16 used_pools = adapter->num_vfs + adapter->num_rx_pools;
		u16 reserved_pools;

		अगर (((adapter->flags & IXGBE_FLAG_DCB_ENABLED) &&
		     adapter->num_rx_pools >= (MAX_TX_QUEUES / tcs)) ||
		    adapter->num_rx_pools > IXGBE_MAX_MACVLANS)
			वापस ERR_PTR(-EBUSY);

		/* Hardware has a limited number of available pools. Each VF,
		 * and the PF require a pool. Check to ensure we करोn't
		 * attempt to use more then the available number of pools.
		 */
		अगर (used_pools >= IXGBE_MAX_VF_FUNCTIONS)
			वापस ERR_PTR(-EBUSY);

		/* Enable VMDq flag so device will be set in VM mode */
		adapter->flags |= IXGBE_FLAG_VMDQ_ENABLED |
				  IXGBE_FLAG_SRIOV_ENABLED;

		/* Try to reserve as many queues per pool as possible,
		 * we start with the configurations that support 4 queues
		 * per pools, followed by 2, and then by just 1 per pool.
		 */
		अगर (used_pools < 32 && adapter->num_rx_pools < 16)
			reserved_pools = min_t(u16,
					       32 - used_pools,
					       16 - adapter->num_rx_pools);
		अन्यथा अगर (adapter->num_rx_pools < 32)
			reserved_pools = min_t(u16,
					       64 - used_pools,
					       32 - adapter->num_rx_pools);
		अन्यथा
			reserved_pools = 64 - used_pools;


		अगर (!reserved_pools)
			वापस ERR_PTR(-EBUSY);

		adapter->ring_feature[RING_F_VMDQ].limit += reserved_pools;

		/* Force reinit of ring allocation with VMDQ enabled */
		err = ixgbe_setup_tc(pdev, adapter->hw_tcs);
		अगर (err)
			वापस ERR_PTR(err);

		अगर (pool >= adapter->num_rx_pools)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण

	accel = kzalloc(माप(*accel), GFP_KERNEL);
	अगर (!accel)
		वापस ERR_PTR(-ENOMEM);

	set_bit(pool, adapter->fwd_biपंचांगask);
	netdev_set_sb_channel(vdev, pool);
	accel->pool = pool;
	accel->netdev = vdev;

	अगर (!netअगर_running(pdev))
		वापस accel;

	err = ixgbe_fwd_ring_up(adapter, accel);
	अगर (err)
		वापस ERR_PTR(err);

	वापस accel;
पूर्ण

अटल व्योम ixgbe_fwd_del(काष्ठा net_device *pdev, व्योम *priv)
अणु
	काष्ठा ixgbe_fwd_adapter *accel = priv;
	काष्ठा ixgbe_adapter *adapter = netdev_priv(pdev);
	अचिन्हित पूर्णांक rxbase = accel->rx_base_queue;
	अचिन्हित पूर्णांक i;

	/* delete unicast filter associated with offloaded पूर्णांकerface */
	ixgbe_del_mac_filter(adapter, accel->netdev->dev_addr,
			     VMDQ_P(accel->pool));

	/* Allow reमुख्यing Rx packets to get flushed out of the
	 * Rx FIFO beक्रमe we drop the netdev क्रम the ring.
	 */
	usleep_range(10000, 20000);

	क्रम (i = 0; i < adapter->num_rx_queues_per_pool; i++) अणु
		काष्ठा ixgbe_ring *ring = adapter->rx_ring[rxbase + i];
		काष्ठा ixgbe_q_vector *qv = ring->q_vector;

		/* Make sure we aren't processing any packets and clear
		 * netdev to shut करोwn the ring.
		 */
		अगर (netअगर_running(adapter->netdev))
			napi_synchronize(&qv->napi);
		ring->netdev = शून्य;
	पूर्ण

	/* unbind the queues and drop the subordinate channel config */
	netdev_unbind_sb_channel(pdev, accel->netdev);
	netdev_set_sb_channel(accel->netdev, 0);

	clear_bit(accel->pool, adapter->fwd_biपंचांगask);
	kमुक्त(accel);
पूर्ण

#घोषणा IXGBE_MAX_MAC_HDR_LEN		127
#घोषणा IXGBE_MAX_NETWORK_HDR_LEN	511

अटल netdev_features_t
ixgbe_features_check(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		     netdev_features_t features)
अणु
	अचिन्हित पूर्णांक network_hdr_len, mac_hdr_len;

	/* Make certain the headers can be described by a context descriptor */
	mac_hdr_len = skb_network_header(skb) - skb->data;
	अगर (unlikely(mac_hdr_len > IXGBE_MAX_MAC_HDR_LEN))
		वापस features & ~(NETIF_F_HW_CSUM |
				    NETIF_F_SCTP_CRC |
				    NETIF_F_GSO_UDP_L4 |
				    NETIF_F_HW_VLAN_CTAG_TX |
				    NETIF_F_TSO |
				    NETIF_F_TSO6);

	network_hdr_len = skb_checksum_start(skb) - skb_network_header(skb);
	अगर (unlikely(network_hdr_len >  IXGBE_MAX_NETWORK_HDR_LEN))
		वापस features & ~(NETIF_F_HW_CSUM |
				    NETIF_F_SCTP_CRC |
				    NETIF_F_GSO_UDP_L4 |
				    NETIF_F_TSO |
				    NETIF_F_TSO6);

	/* We can only support IPV4 TSO in tunnels अगर we can mangle the
	 * inner IP ID field, so strip TSO अगर MANGLEID is not supported.
	 * IPsec offoad sets skb->encapsulation but still can handle
	 * the TSO, so it's the exception.
	 */
	अगर (skb->encapsulation && !(features & NETIF_F_TSO_MANGLEID)) अणु
#अगर_घोषित CONFIG_IXGBE_IPSEC
		अगर (!secpath_exists(skb))
#पूर्ण_अगर
			features &= ~NETIF_F_TSO;
	पूर्ण

	वापस features;
पूर्ण

अटल पूर्णांक ixgbe_xdp_setup(काष्ठा net_device *dev, काष्ठा bpf_prog *prog)
अणु
	पूर्णांक i, frame_size = dev->mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा bpf_prog *old_prog;
	bool need_reset;

	अगर (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED)
		वापस -EINVAL;

	अगर (adapter->flags & IXGBE_FLAG_DCB_ENABLED)
		वापस -EINVAL;

	/* verअगरy ixgbe ring attributes are sufficient क्रम XDP */
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा ixgbe_ring *ring = adapter->rx_ring[i];

		अगर (ring_is_rsc_enabled(ring))
			वापस -EINVAL;

		अगर (frame_size > ixgbe_rx_bufsz(ring))
			वापस -EINVAL;
	पूर्ण

	अगर (nr_cpu_ids > MAX_XDP_QUEUES)
		वापस -ENOMEM;

	old_prog = xchg(&adapter->xdp_prog, prog);
	need_reset = (!!prog != !!old_prog);

	/* If transitioning XDP modes reconfigure rings */
	अगर (need_reset) अणु
		पूर्णांक err;

		अगर (!prog)
			/* Wait until nकरो_xsk_wakeup completes. */
			synchronize_rcu();
		err = ixgbe_setup_tc(dev, adapter->hw_tcs);

		अगर (err) अणु
			rcu_assign_poपूर्णांकer(adapter->xdp_prog, old_prog);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < adapter->num_rx_queues; i++)
			(व्योम)xchg(&adapter->rx_ring[i]->xdp_prog,
			    adapter->xdp_prog);
	पूर्ण

	अगर (old_prog)
		bpf_prog_put(old_prog);

	/* Kick start the NAPI context अगर there is an AF_XDP socket खोलो
	 * on that queue id. This so that receiving will start.
	 */
	अगर (need_reset && prog)
		क्रम (i = 0; i < adapter->num_rx_queues; i++)
			अगर (adapter->xdp_ring[i]->xsk_pool)
				(व्योम)ixgbe_xsk_wakeup(adapter->netdev, i,
						       XDP_WAKEUP_RX);

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);

	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस ixgbe_xdp_setup(dev, xdp->prog);
	हाल XDP_SETUP_XSK_POOL:
		वापस ixgbe_xsk_pool_setup(adapter, xdp->xsk.pool,
					    xdp->xsk.queue_id);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

व्योम ixgbe_xdp_ring_update_tail(काष्ठा ixgbe_ring *ring)
अणु
	/* Force memory ग_लिखोs to complete beक्रमe letting h/w know there
	 * are new descriptors to fetch.
	 */
	wmb();
	ग_लिखोl(ring->next_to_use, ring->tail);
पूर्ण

अटल पूर्णांक ixgbe_xdp_xmit(काष्ठा net_device *dev, पूर्णांक n,
			  काष्ठा xdp_frame **frames, u32 flags)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा ixgbe_ring *ring;
	पूर्णांक nxmit = 0;
	पूर्णांक i;

	अगर (unlikely(test_bit(__IXGBE_DOWN, &adapter->state)))
		वापस -ENETDOWN;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	/* During program transitions its possible adapter->xdp_prog is asचिन्हित
	 * but ring has not been configured yet. In this हाल simply पात xmit.
	 */
	ring = adapter->xdp_prog ? adapter->xdp_ring[smp_processor_id()] : शून्य;
	अगर (unlikely(!ring))
		वापस -ENXIO;

	अगर (unlikely(test_bit(__IXGBE_TX_DISABLED, &ring->state)))
		वापस -ENXIO;

	क्रम (i = 0; i < n; i++) अणु
		काष्ठा xdp_frame *xdpf = frames[i];
		पूर्णांक err;

		err = ixgbe_xmit_xdp_ring(adapter, xdpf);
		अगर (err != IXGBE_XDP_TX)
			अवरोध;
		nxmit++;
	पूर्ण

	अगर (unlikely(flags & XDP_XMIT_FLUSH))
		ixgbe_xdp_ring_update_tail(ring);

	वापस nxmit;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ixgbe_netdev_ops = अणु
	.nकरो_खोलो		= ixgbe_खोलो,
	.nकरो_stop		= ixgbe_बंद,
	.nकरो_start_xmit		= ixgbe_xmit_frame,
	.nकरो_set_rx_mode	= ixgbe_set_rx_mode,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= ixgbe_set_mac,
	.nकरो_change_mtu		= ixgbe_change_mtu,
	.nकरो_tx_समयout		= ixgbe_tx_समयout,
	.nकरो_set_tx_maxrate	= ixgbe_tx_maxrate,
	.nकरो_vlan_rx_add_vid	= ixgbe_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= ixgbe_vlan_rx_समाप्त_vid,
	.nकरो_करो_ioctl		= ixgbe_ioctl,
	.nकरो_set_vf_mac		= ixgbe_nकरो_set_vf_mac,
	.nकरो_set_vf_vlan	= ixgbe_nकरो_set_vf_vlan,
	.nकरो_set_vf_rate	= ixgbe_nकरो_set_vf_bw,
	.nकरो_set_vf_spoofchk	= ixgbe_nकरो_set_vf_spoofchk,
	.nकरो_set_vf_rss_query_en = ixgbe_nकरो_set_vf_rss_query_en,
	.nकरो_set_vf_trust	= ixgbe_nकरो_set_vf_trust,
	.nकरो_get_vf_config	= ixgbe_nकरो_get_vf_config,
	.nकरो_get_stats64	= ixgbe_get_stats64,
	.nकरो_setup_tc		= __ixgbe_setup_tc,
#अगर_घोषित IXGBE_FCOE
	.nकरो_select_queue	= ixgbe_select_queue,
	.nकरो_fcoe_ddp_setup = ixgbe_fcoe_ddp_get,
	.nकरो_fcoe_ddp_target = ixgbe_fcoe_ddp_target,
	.nकरो_fcoe_ddp_करोne = ixgbe_fcoe_ddp_put,
	.nकरो_fcoe_enable = ixgbe_fcoe_enable,
	.nकरो_fcoe_disable = ixgbe_fcoe_disable,
	.nकरो_fcoe_get_wwn = ixgbe_fcoe_get_wwn,
	.nकरो_fcoe_get_hbainfo = ixgbe_fcoe_get_hbainfo,
#पूर्ण_अगर /* IXGBE_FCOE */
	.nकरो_set_features = ixgbe_set_features,
	.nकरो_fix_features = ixgbe_fix_features,
	.nकरो_fdb_add		= ixgbe_nकरो_fdb_add,
	.nकरो_bridge_setlink	= ixgbe_nकरो_bridge_setlink,
	.nकरो_bridge_getlink	= ixgbe_nकरो_bridge_getlink,
	.nकरो_dfwd_add_station	= ixgbe_fwd_add,
	.nकरो_dfwd_del_station	= ixgbe_fwd_del,
	.nकरो_features_check	= ixgbe_features_check,
	.nकरो_bpf		= ixgbe_xdp,
	.nकरो_xdp_xmit		= ixgbe_xdp_xmit,
	.nकरो_xsk_wakeup         = ixgbe_xsk_wakeup,
पूर्ण;

अटल व्योम ixgbe_disable_txr_hw(काष्ठा ixgbe_adapter *adapter,
				 काष्ठा ixgbe_ring *tx_ring)
अणु
	अचिन्हित दीर्घ रुको_delay, delay_पूर्णांकerval;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u8 reg_idx = tx_ring->reg_idx;
	पूर्णांक रुको_loop;
	u32 txdctl;

	IXGBE_WRITE_REG(hw, IXGBE_TXDCTL(reg_idx), IXGBE_TXDCTL_SWFLSH);

	/* delay mechanism from ixgbe_disable_tx */
	delay_पूर्णांकerval = ixgbe_get_completion_समयout(adapter) / 100;

	रुको_loop = IXGBE_MAX_RX_DESC_POLL;
	रुको_delay = delay_पूर्णांकerval;

	जबतक (रुको_loop--) अणु
		usleep_range(रुको_delay, रुको_delay + 10);
		रुको_delay += delay_पूर्णांकerval * 2;
		txdctl = IXGBE_READ_REG(hw, IXGBE_TXDCTL(reg_idx));

		अगर (!(txdctl & IXGBE_TXDCTL_ENABLE))
			वापस;
	पूर्ण

	e_err(drv, "TXDCTL.ENABLE not cleared within the polling period\n");
पूर्ण

अटल व्योम ixgbe_disable_txr(काष्ठा ixgbe_adapter *adapter,
			      काष्ठा ixgbe_ring *tx_ring)
अणु
	set_bit(__IXGBE_TX_DISABLED, &tx_ring->state);
	ixgbe_disable_txr_hw(adapter, tx_ring);
पूर्ण

अटल व्योम ixgbe_disable_rxr_hw(काष्ठा ixgbe_adapter *adapter,
				 काष्ठा ixgbe_ring *rx_ring)
अणु
	अचिन्हित दीर्घ रुको_delay, delay_पूर्णांकerval;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u8 reg_idx = rx_ring->reg_idx;
	पूर्णांक रुको_loop;
	u32 rxdctl;

	rxdctl = IXGBE_READ_REG(hw, IXGBE_RXDCTL(reg_idx));
	rxdctl &= ~IXGBE_RXDCTL_ENABLE;
	rxdctl |= IXGBE_RXDCTL_SWFLSH;

	/* ग_लिखो value back with RXDCTL.ENABLE bit cleared */
	IXGBE_WRITE_REG(hw, IXGBE_RXDCTL(reg_idx), rxdctl);

	/* RXDCTL.EN may not change on 82598 अगर link is करोwn, so skip it */
	अगर (hw->mac.type == ixgbe_mac_82598EB &&
	    !(IXGBE_READ_REG(hw, IXGBE_LINKS) & IXGBE_LINKS_UP))
		वापस;

	/* delay mechanism from ixgbe_disable_rx */
	delay_पूर्णांकerval = ixgbe_get_completion_समयout(adapter) / 100;

	रुको_loop = IXGBE_MAX_RX_DESC_POLL;
	रुको_delay = delay_पूर्णांकerval;

	जबतक (रुको_loop--) अणु
		usleep_range(रुको_delay, रुको_delay + 10);
		रुको_delay += delay_पूर्णांकerval * 2;
		rxdctl = IXGBE_READ_REG(hw, IXGBE_RXDCTL(reg_idx));

		अगर (!(rxdctl & IXGBE_RXDCTL_ENABLE))
			वापस;
	पूर्ण

	e_err(drv, "RXDCTL.ENABLE not cleared within the polling period\n");
पूर्ण

अटल व्योम ixgbe_reset_txr_stats(काष्ठा ixgbe_ring *tx_ring)
अणु
	स_रखो(&tx_ring->stats, 0, माप(tx_ring->stats));
	स_रखो(&tx_ring->tx_stats, 0, माप(tx_ring->tx_stats));
पूर्ण

अटल व्योम ixgbe_reset_rxr_stats(काष्ठा ixgbe_ring *rx_ring)
अणु
	स_रखो(&rx_ring->stats, 0, माप(rx_ring->stats));
	स_रखो(&rx_ring->rx_stats, 0, माप(rx_ring->rx_stats));
पूर्ण

/**
 * ixgbe_txrx_ring_disable - Disable Rx/Tx/XDP Tx rings
 * @adapter: adapter काष्ठाure
 * @ring: ring index
 *
 * This function disables a certain Rx/Tx/XDP Tx ring. The function
 * assumes that the netdev is running.
 **/
व्योम ixgbe_txrx_ring_disable(काष्ठा ixgbe_adapter *adapter, पूर्णांक ring)
अणु
	काष्ठा ixgbe_ring *rx_ring, *tx_ring, *xdp_ring;

	rx_ring = adapter->rx_ring[ring];
	tx_ring = adapter->tx_ring[ring];
	xdp_ring = adapter->xdp_ring[ring];

	ixgbe_disable_txr(adapter, tx_ring);
	अगर (xdp_ring)
		ixgbe_disable_txr(adapter, xdp_ring);
	ixgbe_disable_rxr_hw(adapter, rx_ring);

	अगर (xdp_ring)
		synchronize_rcu();

	/* Rx/Tx/XDP Tx share the same napi context. */
	napi_disable(&rx_ring->q_vector->napi);

	ixgbe_clean_tx_ring(tx_ring);
	अगर (xdp_ring)
		ixgbe_clean_tx_ring(xdp_ring);
	ixgbe_clean_rx_ring(rx_ring);

	ixgbe_reset_txr_stats(tx_ring);
	अगर (xdp_ring)
		ixgbe_reset_txr_stats(xdp_ring);
	ixgbe_reset_rxr_stats(rx_ring);
पूर्ण

/**
 * ixgbe_txrx_ring_enable - Enable Rx/Tx/XDP Tx rings
 * @adapter: adapter काष्ठाure
 * @ring: ring index
 *
 * This function enables a certain Rx/Tx/XDP Tx ring. The function
 * assumes that the netdev is running.
 **/
व्योम ixgbe_txrx_ring_enable(काष्ठा ixgbe_adapter *adapter, पूर्णांक ring)
अणु
	काष्ठा ixgbe_ring *rx_ring, *tx_ring, *xdp_ring;

	rx_ring = adapter->rx_ring[ring];
	tx_ring = adapter->tx_ring[ring];
	xdp_ring = adapter->xdp_ring[ring];

	/* Rx/Tx/XDP Tx share the same napi context. */
	napi_enable(&rx_ring->q_vector->napi);

	ixgbe_configure_tx_ring(adapter, tx_ring);
	अगर (xdp_ring)
		ixgbe_configure_tx_ring(adapter, xdp_ring);
	ixgbe_configure_rx_ring(adapter, rx_ring);

	clear_bit(__IXGBE_TX_DISABLED, &tx_ring->state);
	अगर (xdp_ring)
		clear_bit(__IXGBE_TX_DISABLED, &xdp_ring->state);
पूर्ण

/**
 * ixgbe_क्रमागतerate_functions - Get the number of ports this device has
 * @adapter: adapter काष्ठाure
 *
 * This function क्रमागतerates the phsyical functions co-located on a single slot,
 * in order to determine how many ports a device has. This is most useful in
 * determining the required GT/s of PCIe bandwidth necessary क्रम optimal
 * perक्रमmance.
 **/
अटल अंतरभूत पूर्णांक ixgbe_क्रमागतerate_functions(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा pci_dev *entry, *pdev = adapter->pdev;
	पूर्णांक physfns = 0;

	/* Some cards can not use the generic count PCIe functions method,
	 * because they are behind a parent चयन, so we hardcode these with
	 * the correct number of functions.
	 */
	अगर (ixgbe_pcie_from_parent(&adapter->hw))
		physfns = 4;

	list_क्रम_each_entry(entry, &adapter->pdev->bus->devices, bus_list) अणु
		/* करोn't count भव functions */
		अगर (entry->is_virtfn)
			जारी;

		/* When the devices on the bus करोn't all match our device ID,
		 * we can't reliably determine the correct number of
		 * functions. This can occur अगर a function has been direct
		 * attached to a भव machine using VT-d, क्रम example. In
		 * this हाल, simply वापस -1 to indicate this.
		 */
		अगर ((entry->venकरोr != pdev->venकरोr) ||
		    (entry->device != pdev->device))
			वापस -1;

		physfns++;
	पूर्ण

	वापस physfns;
पूर्ण

/**
 * ixgbe_wol_supported - Check whether device supports WoL
 * @adapter: the adapter निजी काष्ठाure
 * @device_id: the device ID
 * @subdevice_id: the subप्रणाली device ID
 *
 * This function is used by probe and ethtool to determine
 * which devices have WoL support
 *
 **/
bool ixgbe_wol_supported(काष्ठा ixgbe_adapter *adapter, u16 device_id,
			 u16 subdevice_id)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u16 wol_cap = adapter->eeprom_cap & IXGBE_DEVICE_CAPS_WOL_MASK;

	/* WOL not supported on 82598 */
	अगर (hw->mac.type == ixgbe_mac_82598EB)
		वापस false;

	/* check eeprom to see अगर WOL is enabled क्रम X540 and newer */
	अगर (hw->mac.type >= ixgbe_mac_X540) अणु
		अगर ((wol_cap == IXGBE_DEVICE_CAPS_WOL_PORT0_1) ||
		    ((wol_cap == IXGBE_DEVICE_CAPS_WOL_PORT0) &&
		     (hw->bus.func == 0)))
			वापस true;
	पूर्ण

	/* WOL is determined based on device IDs क्रम 82599 MACs */
	चयन (device_id) अणु
	हाल IXGBE_DEV_ID_82599_SFP:
		/* Only these subdevices could supports WOL */
		चयन (subdevice_id) अणु
		हाल IXGBE_SUBDEV_ID_82599_560FLR:
		हाल IXGBE_SUBDEV_ID_82599_LOM_SNAP6:
		हाल IXGBE_SUBDEV_ID_82599_SFP_WOL0:
		हाल IXGBE_SUBDEV_ID_82599_SFP_2OCP:
			/* only support first port */
			अगर (hw->bus.func != 0)
				अवरोध;
			fallthrough;
		हाल IXGBE_SUBDEV_ID_82599_SP_560FLR:
		हाल IXGBE_SUBDEV_ID_82599_SFP:
		हाल IXGBE_SUBDEV_ID_82599_RNDC:
		हाल IXGBE_SUBDEV_ID_82599_ECNA_DP:
		हाल IXGBE_SUBDEV_ID_82599_SFP_1OCP:
		हाल IXGBE_SUBDEV_ID_82599_SFP_LOM_OEM1:
		हाल IXGBE_SUBDEV_ID_82599_SFP_LOM_OEM2:
			वापस true;
		पूर्ण
		अवरोध;
	हाल IXGBE_DEV_ID_82599EN_SFP:
		/* Only these subdevices support WOL */
		चयन (subdevice_id) अणु
		हाल IXGBE_SUBDEV_ID_82599EN_SFP_OCP1:
			वापस true;
		पूर्ण
		अवरोध;
	हाल IXGBE_DEV_ID_82599_COMBO_BACKPLANE:
		/* All except this subdevice support WOL */
		अगर (subdevice_id != IXGBE_SUBDEV_ID_82599_KX4_KR_MEZZ)
			वापस true;
		अवरोध;
	हाल IXGBE_DEV_ID_82599_KX4:
		वापस  true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

/**
 * ixgbe_set_fw_version - Set FW version
 * @adapter: the adapter निजी काष्ठाure
 *
 * This function is used by probe and ethtool to determine the FW version to
 * क्रमmat to display. The FW version is taken from the EEPROM/NVM.
 */
अटल व्योम ixgbe_set_fw_version(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा ixgbe_nvm_version nvm_ver;

	ixgbe_get_oem_prod_version(hw, &nvm_ver);
	अगर (nvm_ver.oem_valid) अणु
		snम_लिखो(adapter->eeprom_id, माप(adapter->eeprom_id),
			 "%x.%x.%x", nvm_ver.oem_major, nvm_ver.oem_minor,
			 nvm_ver.oem_release);
		वापस;
	पूर्ण

	ixgbe_get_etk_id(hw, &nvm_ver);
	ixgbe_get_orom_version(hw, &nvm_ver);

	अगर (nvm_ver.or_valid) अणु
		snम_लिखो(adapter->eeprom_id, माप(adapter->eeprom_id),
			 "0x%08x, %d.%d.%d", nvm_ver.etk_id, nvm_ver.or_major,
			 nvm_ver.or_build, nvm_ver.or_patch);
		वापस;
	पूर्ण

	/* Set ETrack ID क्रमmat */
	snम_लिखो(adapter->eeprom_id, माप(adapter->eeprom_id),
		 "0x%08x", nvm_ver.etk_id);
पूर्ण

/**
 * ixgbe_probe - Device Initialization Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in ixgbe_pci_tbl
 *
 * Returns 0 on success, negative on failure
 *
 * ixgbe_probe initializes an adapter identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring of the adapter निजी काष्ठाure,
 * and a hardware reset occur.
 **/
अटल पूर्णांक ixgbe_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev;
	काष्ठा ixgbe_adapter *adapter = शून्य;
	काष्ठा ixgbe_hw *hw;
	स्थिर काष्ठा ixgbe_info *ii = ixgbe_info_tbl[ent->driver_data];
	पूर्णांक i, err, pci_using_dac, expected_gts;
	अचिन्हित पूर्णांक indices = MAX_TX_QUEUES;
	u8 part_str[IXGBE_PBANUM_LENGTH];
	bool disable_dev = false;
#अगर_घोषित IXGBE_FCOE
	u16 device_caps;
#पूर्ण_अगर
	u32 eec;

	/* Catch broken hardware that put the wrong VF device ID in
	 * the PCIe SR-IOV capability.
	 */
	अगर (pdev->is_virtfn) अणु
		WARN(1, KERN_ERR "%s (%hx:%hx) should not be a VF!\n",
		     pci_name(pdev), pdev->venकरोr, pdev->device);
		वापस -EINVAL;
	पूर्ण

	err = pci_enable_device_mem(pdev);
	अगर (err)
		वापस err;

	अगर (!dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64))) अणु
		pci_using_dac = 1;
	पूर्ण अन्यथा अणु
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev,
				"No usable DMA configuration, aborting\n");
			जाओ err_dma;
		पूर्ण
		pci_using_dac = 0;
	पूर्ण

	err = pci_request_mem_regions(pdev, ixgbe_driver_name);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"pci_request_selected_regions failed 0x%x\n", err);
		जाओ err_pci_reg;
	पूर्ण

	pci_enable_pcie_error_reporting(pdev);

	pci_set_master(pdev);
	pci_save_state(pdev);

	अगर (ii->mac == ixgbe_mac_82598EB) अणु
#अगर_घोषित CONFIG_IXGBE_DCB
		/* 8 TC w/ 4 queues per TC */
		indices = 4 * MAX_TRAFFIC_CLASS;
#अन्यथा
		indices = IXGBE_MAX_RSS_INDICES;
#पूर्ण_अगर
	पूर्ण

	netdev = alloc_etherdev_mq(माप(काष्ठा ixgbe_adapter), indices);
	अगर (!netdev) अणु
		err = -ENOMEM;
		जाओ err_alloc_etherdev;
	पूर्ण

	SET_NETDEV_DEV(netdev, &pdev->dev);

	adapter = netdev_priv(netdev);

	adapter->netdev = netdev;
	adapter->pdev = pdev;
	hw = &adapter->hw;
	hw->back = adapter;
	adapter->msg_enable = netअगर_msg_init(debug, DEFAULT_MSG_ENABLE);

	hw->hw_addr = ioremap(pci_resource_start(pdev, 0),
			      pci_resource_len(pdev, 0));
	adapter->io_addr = hw->hw_addr;
	अगर (!hw->hw_addr) अणु
		err = -EIO;
		जाओ err_ioremap;
	पूर्ण

	netdev->netdev_ops = &ixgbe_netdev_ops;
	ixgbe_set_ethtool_ops(netdev);
	netdev->watchकरोg_समयo = 5 * HZ;
	strlcpy(netdev->name, pci_name(pdev), माप(netdev->name));

	/* Setup hw api */
	hw->mac.ops   = *ii->mac_ops;
	hw->mac.type  = ii->mac;
	hw->mvals     = ii->mvals;
	अगर (ii->link_ops)
		hw->link.ops  = *ii->link_ops;

	/* EEPROM */
	hw->eeprom.ops = *ii->eeprom_ops;
	eec = IXGBE_READ_REG(hw, IXGBE_EEC(hw));
	अगर (ixgbe_हटाओd(hw->hw_addr)) अणु
		err = -EIO;
		जाओ err_ioremap;
	पूर्ण
	/* If EEPROM is valid (bit 8 = 1), use शेष otherwise use bit bang */
	अगर (!(eec & BIT(8)))
		hw->eeprom.ops.पढ़ो = &ixgbe_पढ़ो_eeprom_bit_bang_generic;

	/* PHY */
	hw->phy.ops = *ii->phy_ops;
	hw->phy.sfp_type = ixgbe_sfp_type_unknown;
	/* ixgbe_identअगरy_phy_generic will set prtad and mmds properly */
	hw->phy.mdio.prtad = MDIO_PRTAD_NONE;
	hw->phy.mdio.mmds = 0;
	hw->phy.mdio.mode_support = MDIO_SUPPORTS_C45 | MDIO_EMULATE_C22;
	hw->phy.mdio.dev = netdev;
	hw->phy.mdio.mdio_पढ़ो = ixgbe_mdio_पढ़ो;
	hw->phy.mdio.mdio_ग_लिखो = ixgbe_mdio_ग_लिखो;

	/* setup the निजी काष्ठाure */
	err = ixgbe_sw_init(adapter, ii);
	अगर (err)
		जाओ err_sw_init;

	चयन (adapter->hw.mac.type) अणु
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
		netdev->udp_tunnel_nic_info = &ixgbe_udp_tunnels_x550;
		अवरोध;
	हाल ixgbe_mac_x550em_a:
		netdev->udp_tunnel_nic_info = &ixgbe_udp_tunnels_x550em_a;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Make sure the SWFW semaphore is in a valid state */
	अगर (hw->mac.ops.init_swfw_sync)
		hw->mac.ops.init_swfw_sync(hw);

	/* Make it possible the adapter to be woken up via WOL */
	चयन (adapter->hw.mac.type) अणु
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_WUS, ~0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * If there is a fan on this device and it has failed log the
	 * failure.
	 */
	अगर (adapter->flags & IXGBE_FLAG_FAN_FAIL_CAPABLE) अणु
		u32 esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);
		अगर (esdp & IXGBE_ESDP_SDP1)
			e_crit(probe, "Fan has stopped, replace the adapter\n");
	पूर्ण

	अगर (allow_unsupported_sfp)
		hw->allow_unsupported_sfp = allow_unsupported_sfp;

	/* reset_hw fills in the perm_addr as well */
	hw->phy.reset_अगर_overtemp = true;
	err = hw->mac.ops.reset_hw(hw);
	hw->phy.reset_अगर_overtemp = false;
	ixgbe_set_eee_capable(adapter);
	अगर (err == IXGBE_ERR_SFP_NOT_PRESENT) अणु
		err = 0;
	पूर्ण अन्यथा अगर (err == IXGBE_ERR_SFP_NOT_SUPPORTED) अणु
		e_dev_err("failed to load because an unsupported SFP+ or QSFP module type was detected.\n");
		e_dev_err("Reload the driver after installing a supported module.\n");
		जाओ err_sw_init;
	पूर्ण अन्यथा अगर (err) अणु
		e_dev_err("HW Init failed: %d\n", err);
		जाओ err_sw_init;
	पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
	/* SR-IOV not supported on the 82598 */
	अगर (adapter->hw.mac.type == ixgbe_mac_82598EB)
		जाओ skip_sriov;
	/* Mailbox */
	ixgbe_init_mbx_params_pf(hw);
	hw->mbx.ops = ii->mbx_ops;
	pci_sriov_set_totalvfs(pdev, IXGBE_MAX_VFS_DRV_LIMIT);
	ixgbe_enable_sriov(adapter, max_vfs);
skip_sriov:

#पूर्ण_अगर
	netdev->features = NETIF_F_SG |
			   NETIF_F_TSO |
			   NETIF_F_TSO6 |
			   NETIF_F_RXHASH |
			   NETIF_F_RXCSUM |
			   NETIF_F_HW_CSUM;

#घोषणा IXGBE_GSO_PARTIAL_FEATURES (NETIF_F_GSO_GRE | \
				    NETIF_F_GSO_GRE_CSUM | \
				    NETIF_F_GSO_IPXIP4 | \
				    NETIF_F_GSO_IPXIP6 | \
				    NETIF_F_GSO_UDP_TUNNEL | \
				    NETIF_F_GSO_UDP_TUNNEL_CSUM)

	netdev->gso_partial_features = IXGBE_GSO_PARTIAL_FEATURES;
	netdev->features |= NETIF_F_GSO_PARTIAL |
			    IXGBE_GSO_PARTIAL_FEATURES;

	अगर (hw->mac.type >= ixgbe_mac_82599EB)
		netdev->features |= NETIF_F_SCTP_CRC | NETIF_F_GSO_UDP_L4;

#अगर_घोषित CONFIG_IXGBE_IPSEC
#घोषणा IXGBE_ESP_FEATURES	(NETIF_F_HW_ESP | \
				 NETIF_F_HW_ESP_TX_CSUM | \
				 NETIF_F_GSO_ESP)

	अगर (adapter->ipsec)
		netdev->features |= IXGBE_ESP_FEATURES;
#पूर्ण_अगर
	/* copy netdev features पूर्णांकo list of user selectable features */
	netdev->hw_features |= netdev->features |
			       NETIF_F_HW_VLAN_CTAG_FILTER |
			       NETIF_F_HW_VLAN_CTAG_RX |
			       NETIF_F_HW_VLAN_CTAG_TX |
			       NETIF_F_RXALL |
			       NETIF_F_HW_L2FW_DOFFLOAD;

	अगर (hw->mac.type >= ixgbe_mac_82599EB)
		netdev->hw_features |= NETIF_F_NTUPLE |
				       NETIF_F_HW_TC;

	अगर (pci_using_dac)
		netdev->features |= NETIF_F_HIGHDMA;

	netdev->vlan_features |= netdev->features | NETIF_F_TSO_MANGLEID;
	netdev->hw_enc_features |= netdev->vlan_features;
	netdev->mpls_features |= NETIF_F_SG |
				 NETIF_F_TSO |
				 NETIF_F_TSO6 |
				 NETIF_F_HW_CSUM;
	netdev->mpls_features |= IXGBE_GSO_PARTIAL_FEATURES;

	/* set this bit last since it cannot be part of vlan_features */
	netdev->features |= NETIF_F_HW_VLAN_CTAG_FILTER |
			    NETIF_F_HW_VLAN_CTAG_RX |
			    NETIF_F_HW_VLAN_CTAG_TX;

	netdev->priv_flags |= IFF_UNICAST_FLT;
	netdev->priv_flags |= IFF_SUPP_NOFCS;

	/* MTU range: 68 - 9710 */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = IXGBE_MAX_JUMBO_FRAME_SIZE - (ETH_HLEN + ETH_FCS_LEN);

#अगर_घोषित CONFIG_IXGBE_DCB
	अगर (adapter->flags & IXGBE_FLAG_DCB_CAPABLE)
		netdev->dcbnl_ops = &ixgbe_dcbnl_ops;
#पूर्ण_अगर

#अगर_घोषित IXGBE_FCOE
	अगर (adapter->flags & IXGBE_FLAG_FCOE_CAPABLE) अणु
		अचिन्हित पूर्णांक fcoe_l;

		अगर (hw->mac.ops.get_device_caps) अणु
			hw->mac.ops.get_device_caps(hw, &device_caps);
			अगर (device_caps & IXGBE_DEVICE_CAPS_FCOE_OFFLOADS)
				adapter->flags &= ~IXGBE_FLAG_FCOE_CAPABLE;
		पूर्ण


		fcoe_l = min_t(पूर्णांक, IXGBE_FCRETA_SIZE, num_online_cpus());
		adapter->ring_feature[RING_F_FCOE].limit = fcoe_l;

		netdev->features |= NETIF_F_FSO |
				    NETIF_F_FCOE_CRC;

		netdev->vlan_features |= NETIF_F_FSO |
					 NETIF_F_FCOE_CRC |
					 NETIF_F_FCOE_MTU;
	पूर्ण
#पूर्ण_अगर /* IXGBE_FCOE */
	अगर (adapter->flags2 & IXGBE_FLAG2_RSC_CAPABLE)
		netdev->hw_features |= NETIF_F_LRO;
	अगर (adapter->flags2 & IXGBE_FLAG2_RSC_ENABLED)
		netdev->features |= NETIF_F_LRO;

	अगर (ixgbe_check_fw_error(adapter)) अणु
		err = -EIO;
		जाओ err_sw_init;
	पूर्ण

	/* make sure the EEPROM is good */
	अगर (hw->eeprom.ops.validate_checksum(hw, शून्य) < 0) अणु
		e_dev_err("The EEPROM Checksum Is Not Valid\n");
		err = -EIO;
		जाओ err_sw_init;
	पूर्ण

	eth_platक्रमm_get_mac_address(&adapter->pdev->dev,
				     adapter->hw.mac.perm_addr);

	स_नकल(netdev->dev_addr, hw->mac.perm_addr, netdev->addr_len);

	अगर (!is_valid_ether_addr(netdev->dev_addr)) अणु
		e_dev_err("invalid MAC address\n");
		err = -EIO;
		जाओ err_sw_init;
	पूर्ण

	/* Set hw->mac.addr to permanent MAC address */
	ether_addr_copy(hw->mac.addr, hw->mac.perm_addr);
	ixgbe_mac_set_शेष_filter(adapter);

	समयr_setup(&adapter->service_समयr, ixgbe_service_समयr, 0);

	अगर (ixgbe_हटाओd(hw->hw_addr)) अणु
		err = -EIO;
		जाओ err_sw_init;
	पूर्ण
	INIT_WORK(&adapter->service_task, ixgbe_service_task);
	set_bit(__IXGBE_SERVICE_INITED, &adapter->state);
	clear_bit(__IXGBE_SERVICE_SCHED, &adapter->state);

	err = ixgbe_init_पूर्णांकerrupt_scheme(adapter);
	अगर (err)
		जाओ err_sw_init;

	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		u64_stats_init(&adapter->rx_ring[i]->syncp);
	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		u64_stats_init(&adapter->tx_ring[i]->syncp);
	क्रम (i = 0; i < adapter->num_xdp_queues; i++)
		u64_stats_init(&adapter->xdp_ring[i]->syncp);

	/* WOL not supported क्रम all devices */
	adapter->wol = 0;
	hw->eeprom.ops.पढ़ो(hw, 0x2c, &adapter->eeprom_cap);
	hw->wol_enabled = ixgbe_wol_supported(adapter, pdev->device,
						pdev->subप्रणाली_device);
	अगर (hw->wol_enabled)
		adapter->wol = IXGBE_WUFC_MAG;

	device_set_wakeup_enable(&adapter->pdev->dev, adapter->wol);

	/* save off EEPROM version number */
	ixgbe_set_fw_version(adapter);

	/* pick up the PCI bus settings क्रम reporting later */
	अगर (ixgbe_pcie_from_parent(hw))
		ixgbe_get_parent_bus_info(adapter);
	अन्यथा
		 hw->mac.ops.get_bus_info(hw);

	/* calculate the expected PCIe bandwidth required क्रम optimal
	 * perक्रमmance. Note that some older parts will never have enough
	 * bandwidth due to being older generation PCIe parts. We clamp these
	 * parts to ensure no warning is displayed अगर it can't be fixed.
	 */
	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		expected_gts = min(ixgbe_क्रमागतerate_functions(adapter) * 10, 16);
		अवरोध;
	शेष:
		expected_gts = ixgbe_क्रमागतerate_functions(adapter) * 10;
		अवरोध;
	पूर्ण

	/* करोn't check link अगर we failed to क्रमागतerate functions */
	अगर (expected_gts > 0)
		ixgbe_check_minimum_link(adapter, expected_gts);

	err = ixgbe_पढ़ो_pba_string_generic(hw, part_str, माप(part_str));
	अगर (err)
		strlcpy(part_str, "Unknown", माप(part_str));
	अगर (ixgbe_is_sfp(hw) && hw->phy.sfp_type != ixgbe_sfp_type_not_present)
		e_dev_info("MAC: %d, PHY: %d, SFP+: %d, PBA No: %s\n",
			   hw->mac.type, hw->phy.type, hw->phy.sfp_type,
			   part_str);
	अन्यथा
		e_dev_info("MAC: %d, PHY: %d, PBA No: %s\n",
			   hw->mac.type, hw->phy.type, part_str);

	e_dev_info("%pM\n", netdev->dev_addr);

	/* reset the hardware with the new settings */
	err = hw->mac.ops.start_hw(hw);
	अगर (err == IXGBE_ERR_EEPROM_VERSION) अणु
		/* We are running on a pre-production device, log a warning */
		e_dev_warn("This device is a pre-production adapter/LOM. "
			   "Please be aware there may be issues associated "
			   "with your hardware.  If you are experiencing "
			   "problems please contact your Intel or hardware "
			   "representative who provided you with this "
			   "hardware.\n");
	पूर्ण
	म_नकल(netdev->name, "eth%d");
	pci_set_drvdata(pdev, adapter);
	err = रेजिस्टर_netdev(netdev);
	अगर (err)
		जाओ err_रेजिस्टर;


	/* घातer करोwn the optics क्रम 82599 SFP+ fiber */
	अगर (hw->mac.ops.disable_tx_laser)
		hw->mac.ops.disable_tx_laser(hw);

	/* carrier off reporting is important to ethtool even BEFORE खोलो */
	netअगर_carrier_off(netdev);

#अगर_घोषित CONFIG_IXGBE_DCA
	अगर (dca_add_requester(&pdev->dev) == 0) अणु
		adapter->flags |= IXGBE_FLAG_DCA_ENABLED;
		ixgbe_setup_dca(adapter);
	पूर्ण
#पूर्ण_अगर
	अगर (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) अणु
		e_info(probe, "IOV is enabled with %d VFs\n", adapter->num_vfs);
		क्रम (i = 0; i < adapter->num_vfs; i++)
			ixgbe_vf_configuration(pdev, (i | 0x10000000));
	पूर्ण

	/* firmware requires driver version to be 0xFFFFFFFF
	 * since os करोes not support feature
	 */
	अगर (hw->mac.ops.set_fw_drv_ver)
		hw->mac.ops.set_fw_drv_ver(hw, 0xFF, 0xFF, 0xFF, 0xFF,
					   माप(UTS_RELEASE) - 1,
					   UTS_RELEASE);

	/* add san mac addr to netdev */
	ixgbe_add_sanmac_netdev(netdev);

	e_dev_info("%s\n", ixgbe_शेष_device_descr);

#अगर_घोषित CONFIG_IXGBE_HWMON
	अगर (ixgbe_sysfs_init(adapter))
		e_err(probe, "failed to allocate sysfs resources\n");
#पूर्ण_अगर /* CONFIG_IXGBE_HWMON */

	ixgbe_dbg_adapter_init(adapter);

	/* setup link क्रम SFP devices with MNG FW, अन्यथा रुको क्रम IXGBE_UP */
	अगर (ixgbe_mng_enabled(hw) && ixgbe_is_sfp(hw) && hw->mac.ops.setup_link)
		hw->mac.ops.setup_link(hw,
			IXGBE_LINK_SPEED_10GB_FULL | IXGBE_LINK_SPEED_1GB_FULL,
			true);

	err = ixgbe_mii_bus_init(hw);
	अगर (err)
		जाओ err_netdev;

	वापस 0;

err_netdev:
	unरेजिस्टर_netdev(netdev);
err_रेजिस्टर:
	ixgbe_release_hw_control(adapter);
	ixgbe_clear_पूर्णांकerrupt_scheme(adapter);
err_sw_init:
	ixgbe_disable_sriov(adapter);
	adapter->flags2 &= ~IXGBE_FLAG2_SEARCH_FOR_SFP;
	iounmap(adapter->io_addr);
	kमुक्त(adapter->jump_tables[0]);
	kमुक्त(adapter->mac_table);
	kमुक्त(adapter->rss_key);
	biपंचांगap_मुक्त(adapter->af_xdp_zc_qps);
err_ioremap:
	disable_dev = !test_and_set_bit(__IXGBE_DISABLED, &adapter->state);
	मुक्त_netdev(netdev);
err_alloc_etherdev:
	pci_release_mem_regions(pdev);
err_pci_reg:
err_dma:
	अगर (!adapter || disable_dev)
		pci_disable_device(pdev);
	वापस err;
पूर्ण

/**
 * ixgbe_हटाओ - Device Removal Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * ixgbe_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device.  The could be caused by a
 * Hot-Plug event, or because the driver is going to be हटाओd from
 * memory.
 **/
अटल व्योम ixgbe_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ixgbe_adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev;
	bool disable_dev;
	पूर्णांक i;

	/* अगर !adapter then we alपढ़ोy cleaned up in probe */
	अगर (!adapter)
		वापस;

	netdev  = adapter->netdev;
	ixgbe_dbg_adapter_निकास(adapter);

	set_bit(__IXGBE_REMOVING, &adapter->state);
	cancel_work_sync(&adapter->service_task);

	अगर (adapter->mii_bus)
		mdiobus_unरेजिस्टर(adapter->mii_bus);

#अगर_घोषित CONFIG_IXGBE_DCA
	अगर (adapter->flags & IXGBE_FLAG_DCA_ENABLED) अणु
		adapter->flags &= ~IXGBE_FLAG_DCA_ENABLED;
		dca_हटाओ_requester(&pdev->dev);
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_DCA_CTRL,
				IXGBE_DCA_CTRL_DCA_DISABLE);
	पूर्ण

#पूर्ण_अगर
#अगर_घोषित CONFIG_IXGBE_HWMON
	ixgbe_sysfs_निकास(adapter);
#पूर्ण_अगर /* CONFIG_IXGBE_HWMON */

	/* हटाओ the added san mac */
	ixgbe_del_sanmac_netdev(netdev);

#अगर_घोषित CONFIG_PCI_IOV
	ixgbe_disable_sriov(adapter);
#पूर्ण_अगर
	अगर (netdev->reg_state == NETREG_REGISTERED)
		unरेजिस्टर_netdev(netdev);

	ixgbe_stop_ipsec_offload(adapter);
	ixgbe_clear_पूर्णांकerrupt_scheme(adapter);

	ixgbe_release_hw_control(adapter);

#अगर_घोषित CONFIG_DCB
	kमुक्त(adapter->ixgbe_ieee_pfc);
	kमुक्त(adapter->ixgbe_ieee_ets);

#पूर्ण_अगर
	iounmap(adapter->io_addr);
	pci_release_mem_regions(pdev);

	e_dev_info("complete\n");

	क्रम (i = 0; i < IXGBE_MAX_LINK_HANDLE; i++) अणु
		अगर (adapter->jump_tables[i]) अणु
			kमुक्त(adapter->jump_tables[i]->input);
			kमुक्त(adapter->jump_tables[i]->mask);
		पूर्ण
		kमुक्त(adapter->jump_tables[i]);
	पूर्ण

	kमुक्त(adapter->mac_table);
	kमुक्त(adapter->rss_key);
	biपंचांगap_मुक्त(adapter->af_xdp_zc_qps);
	disable_dev = !test_and_set_bit(__IXGBE_DISABLED, &adapter->state);
	मुक्त_netdev(netdev);

	pci_disable_pcie_error_reporting(pdev);

	अगर (disable_dev)
		pci_disable_device(pdev);
पूर्ण

/**
 * ixgbe_io_error_detected - called when PCI error is detected
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 *
 * This function is called after a PCI bus error affecting
 * this device has been detected.
 */
अटल pci_ers_result_t ixgbe_io_error_detected(काष्ठा pci_dev *pdev,
						pci_channel_state_t state)
अणु
	काष्ठा ixgbe_adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = adapter->netdev;

#अगर_घोषित CONFIG_PCI_IOV
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा pci_dev *bdev, *vfdev;
	u32 dw0, dw1, dw2, dw3;
	पूर्णांक vf, pos;
	u16 req_id, pf_func;

	अगर (adapter->hw.mac.type == ixgbe_mac_82598EB ||
	    adapter->num_vfs == 0)
		जाओ skip_bad_vf_detection;

	bdev = pdev->bus->self;
	जबतक (bdev && (pci_pcie_type(bdev) != PCI_EXP_TYPE_ROOT_PORT))
		bdev = bdev->bus->self;

	अगर (!bdev)
		जाओ skip_bad_vf_detection;

	pos = pci_find_ext_capability(bdev, PCI_EXT_CAP_ID_ERR);
	अगर (!pos)
		जाओ skip_bad_vf_detection;

	dw0 = ixgbe_पढ़ो_pci_cfg_dword(hw, pos + PCI_ERR_HEADER_LOG);
	dw1 = ixgbe_पढ़ो_pci_cfg_dword(hw, pos + PCI_ERR_HEADER_LOG + 4);
	dw2 = ixgbe_पढ़ो_pci_cfg_dword(hw, pos + PCI_ERR_HEADER_LOG + 8);
	dw3 = ixgbe_पढ़ो_pci_cfg_dword(hw, pos + PCI_ERR_HEADER_LOG + 12);
	अगर (ixgbe_हटाओd(hw->hw_addr))
		जाओ skip_bad_vf_detection;

	req_id = dw1 >> 16;
	/* On the 82599 अगर bit 7 of the requestor ID is set then it's a VF */
	अगर (!(req_id & 0x0080))
		जाओ skip_bad_vf_detection;

	pf_func = req_id & 0x01;
	अगर ((pf_func & 1) == (pdev->devfn & 1)) अणु
		अचिन्हित पूर्णांक device_id;

		vf = (req_id & 0x7F) >> 1;
		e_dev_err("VF %d has caused a PCIe error\n", vf);
		e_dev_err("TLP: dw0: %8.8x\tdw1: %8.8x\tdw2: "
				"%8.8x\tdw3: %8.8x\n",
		dw0, dw1, dw2, dw3);
		चयन (adapter->hw.mac.type) अणु
		हाल ixgbe_mac_82599EB:
			device_id = IXGBE_82599_VF_DEVICE_ID;
			अवरोध;
		हाल ixgbe_mac_X540:
			device_id = IXGBE_X540_VF_DEVICE_ID;
			अवरोध;
		हाल ixgbe_mac_X550:
			device_id = IXGBE_DEV_ID_X550_VF;
			अवरोध;
		हाल ixgbe_mac_X550EM_x:
			device_id = IXGBE_DEV_ID_X550EM_X_VF;
			अवरोध;
		हाल ixgbe_mac_x550em_a:
			device_id = IXGBE_DEV_ID_X550EM_A_VF;
			अवरोध;
		शेष:
			device_id = 0;
			अवरोध;
		पूर्ण

		/* Find the pci device of the offending VF */
		vfdev = pci_get_device(PCI_VENDOR_ID_INTEL, device_id, शून्य);
		जबतक (vfdev) अणु
			अगर (vfdev->devfn == (req_id & 0xFF))
				अवरोध;
			vfdev = pci_get_device(PCI_VENDOR_ID_INTEL,
					       device_id, vfdev);
		पूर्ण
		/*
		 * There's a slim chance the VF could have been hot plugged,
		 * so अगर it is no दीर्घer present we करोn't need to issue the
		 * VFLR.  Just clean up the AER in that हाल.
		 */
		अगर (vfdev) अणु
			pcie_flr(vfdev);
			/* Free device reference count */
			pci_dev_put(vfdev);
		पूर्ण
	पूर्ण

	/*
	 * Even though the error may have occurred on the other port
	 * we still need to increment the vf error reference count क्रम
	 * both ports because the I/O resume function will be called
	 * क्रम both of them.
	 */
	adapter->vferr_refcount++;

	वापस PCI_ERS_RESULT_RECOVERED;

skip_bad_vf_detection:
#पूर्ण_अगर /* CONFIG_PCI_IOV */
	अगर (!test_bit(__IXGBE_SERVICE_INITED, &adapter->state))
		वापस PCI_ERS_RESULT_DISCONNECT;

	अगर (!netअगर_device_present(netdev))
		वापस PCI_ERS_RESULT_DISCONNECT;

	rtnl_lock();
	netअगर_device_detach(netdev);

	अगर (netअगर_running(netdev))
		ixgbe_बंद_suspend(adapter);

	अगर (state == pci_channel_io_perm_failure) अणु
		rtnl_unlock();
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	अगर (!test_and_set_bit(__IXGBE_DISABLED, &adapter->state))
		pci_disable_device(pdev);
	rtnl_unlock();

	/* Request a slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * ixgbe_io_slot_reset - called after the pci bus has been reset.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Restart the card from scratch, as अगर from a cold-boot.
 */
अटल pci_ers_result_t ixgbe_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ixgbe_adapter *adapter = pci_get_drvdata(pdev);
	pci_ers_result_t result;

	अगर (pci_enable_device_mem(pdev)) अणु
		e_err(probe, "Cannot re-enable PCI device after reset.\n");
		result = PCI_ERS_RESULT_DISCONNECT;
	पूर्ण अन्यथा अणु
		smp_mb__beक्रमe_atomic();
		clear_bit(__IXGBE_DISABLED, &adapter->state);
		adapter->hw.hw_addr = adapter->io_addr;
		pci_set_master(pdev);
		pci_restore_state(pdev);
		pci_save_state(pdev);

		pci_wake_from_d3(pdev, false);

		ixgbe_reset(adapter);
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_WUS, ~0);
		result = PCI_ERS_RESULT_RECOVERED;
	पूर्ण

	वापस result;
पूर्ण

/**
 * ixgbe_io_resume - called when traffic can start flowing again.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called when the error recovery driver tells us that
 * its OK to resume normal operation.
 */
अटल व्योम ixgbe_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ixgbe_adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = adapter->netdev;

#अगर_घोषित CONFIG_PCI_IOV
	अगर (adapter->vferr_refcount) अणु
		e_info(drv, "Resuming after VF err\n");
		adapter->vferr_refcount--;
		वापस;
	पूर्ण

#पूर्ण_अगर
	rtnl_lock();
	अगर (netअगर_running(netdev))
		ixgbe_खोलो(netdev);

	netअगर_device_attach(netdev);
	rtnl_unlock();
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers ixgbe_err_handler = अणु
	.error_detected = ixgbe_io_error_detected,
	.slot_reset = ixgbe_io_slot_reset,
	.resume = ixgbe_io_resume,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(ixgbe_pm_ops, ixgbe_suspend, ixgbe_resume);

अटल काष्ठा pci_driver ixgbe_driver = अणु
	.name      = ixgbe_driver_name,
	.id_table  = ixgbe_pci_tbl,
	.probe     = ixgbe_probe,
	.हटाओ    = ixgbe_हटाओ,
	.driver.pm = &ixgbe_pm_ops,
	.shutकरोwn  = ixgbe_shutकरोwn,
	.sriov_configure = ixgbe_pci_sriov_configure,
	.err_handler = &ixgbe_err_handler
पूर्ण;

/**
 * ixgbe_init_module - Driver Registration Routine
 *
 * ixgbe_init_module is the first routine called when the driver is
 * loaded. All it करोes is रेजिस्टर with the PCI subप्रणाली.
 **/
अटल पूर्णांक __init ixgbe_init_module(व्योम)
अणु
	पूर्णांक ret;
	pr_info("%s\n", ixgbe_driver_string);
	pr_info("%s\n", ixgbe_copyright);

	ixgbe_wq = create_singlethपढ़ो_workqueue(ixgbe_driver_name);
	अगर (!ixgbe_wq) अणु
		pr_err("%s: Failed to create workqueue\n", ixgbe_driver_name);
		वापस -ENOMEM;
	पूर्ण

	ixgbe_dbg_init();

	ret = pci_रेजिस्टर_driver(&ixgbe_driver);
	अगर (ret) अणु
		destroy_workqueue(ixgbe_wq);
		ixgbe_dbg_निकास();
		वापस ret;
	पूर्ण

#अगर_घोषित CONFIG_IXGBE_DCA
	dca_रेजिस्टर_notअगरy(&dca_notअगरier);
#पूर्ण_अगर

	वापस 0;
पूर्ण

module_init(ixgbe_init_module);

/**
 * ixgbe_निकास_module - Driver Exit Cleanup Routine
 *
 * ixgbe_निकास_module is called just beक्रमe the driver is हटाओd
 * from memory.
 **/
अटल व्योम __निकास ixgbe_निकास_module(व्योम)
अणु
#अगर_घोषित CONFIG_IXGBE_DCA
	dca_unरेजिस्टर_notअगरy(&dca_notअगरier);
#पूर्ण_अगर
	pci_unरेजिस्टर_driver(&ixgbe_driver);

	ixgbe_dbg_निकास();
	अगर (ixgbe_wq) अणु
		destroy_workqueue(ixgbe_wq);
		ixgbe_wq = शून्य;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_IXGBE_DCA
अटल पूर्णांक ixgbe_notअगरy_dca(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			    व्योम *p)
अणु
	पूर्णांक ret_val;

	ret_val = driver_क्रम_each_device(&ixgbe_driver.driver, शून्य, &event,
					 __ixgbe_notअगरy_dca);

	वापस ret_val ? NOTIFY_BAD : NOTIFY_DONE;
पूर्ण

#पूर्ण_अगर /* CONFIG_IXGBE_DCA */

module_निकास(ixgbe_निकास_module);

/* ixgbe_मुख्य.c */
