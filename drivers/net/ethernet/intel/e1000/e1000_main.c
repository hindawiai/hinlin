<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2006 Intel Corporation. */

#समावेश "e1000.h"
#समावेश <net/ip6_checksum.h>
#समावेश <linux/पन.स>
#समावेश <linux/prefetch.h>
#समावेश <linux/bitops.h>
#समावेश <linux/अगर_vlan.h>

अक्षर e1000_driver_name[] = "e1000";
अटल अक्षर e1000_driver_string[] = "Intel(R) PRO/1000 Network Driver";
अटल स्थिर अक्षर e1000_copyright[] = "Copyright (c) 1999-2006 Intel Corporation.";

/* e1000_pci_tbl - PCI Device ID Table
 *
 * Last entry must be all 0s
 *
 * Macro expands to...
 *   अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, device_id)पूर्ण
 */
अटल स्थिर काष्ठा pci_device_id e1000_pci_tbl[] = अणु
	INTEL_E1000_ETHERNET_DEVICE(0x1000),
	INTEL_E1000_ETHERNET_DEVICE(0x1001),
	INTEL_E1000_ETHERNET_DEVICE(0x1004),
	INTEL_E1000_ETHERNET_DEVICE(0x1008),
	INTEL_E1000_ETHERNET_DEVICE(0x1009),
	INTEL_E1000_ETHERNET_DEVICE(0x100C),
	INTEL_E1000_ETHERNET_DEVICE(0x100D),
	INTEL_E1000_ETHERNET_DEVICE(0x100E),
	INTEL_E1000_ETHERNET_DEVICE(0x100F),
	INTEL_E1000_ETHERNET_DEVICE(0x1010),
	INTEL_E1000_ETHERNET_DEVICE(0x1011),
	INTEL_E1000_ETHERNET_DEVICE(0x1012),
	INTEL_E1000_ETHERNET_DEVICE(0x1013),
	INTEL_E1000_ETHERNET_DEVICE(0x1014),
	INTEL_E1000_ETHERNET_DEVICE(0x1015),
	INTEL_E1000_ETHERNET_DEVICE(0x1016),
	INTEL_E1000_ETHERNET_DEVICE(0x1017),
	INTEL_E1000_ETHERNET_DEVICE(0x1018),
	INTEL_E1000_ETHERNET_DEVICE(0x1019),
	INTEL_E1000_ETHERNET_DEVICE(0x101A),
	INTEL_E1000_ETHERNET_DEVICE(0x101D),
	INTEL_E1000_ETHERNET_DEVICE(0x101E),
	INTEL_E1000_ETHERNET_DEVICE(0x1026),
	INTEL_E1000_ETHERNET_DEVICE(0x1027),
	INTEL_E1000_ETHERNET_DEVICE(0x1028),
	INTEL_E1000_ETHERNET_DEVICE(0x1075),
	INTEL_E1000_ETHERNET_DEVICE(0x1076),
	INTEL_E1000_ETHERNET_DEVICE(0x1077),
	INTEL_E1000_ETHERNET_DEVICE(0x1078),
	INTEL_E1000_ETHERNET_DEVICE(0x1079),
	INTEL_E1000_ETHERNET_DEVICE(0x107A),
	INTEL_E1000_ETHERNET_DEVICE(0x107B),
	INTEL_E1000_ETHERNET_DEVICE(0x107C),
	INTEL_E1000_ETHERNET_DEVICE(0x108A),
	INTEL_E1000_ETHERNET_DEVICE(0x1099),
	INTEL_E1000_ETHERNET_DEVICE(0x10B5),
	INTEL_E1000_ETHERNET_DEVICE(0x2E6E),
	/* required last entry */
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, e1000_pci_tbl);

पूर्णांक e1000_up(काष्ठा e1000_adapter *adapter);
व्योम e1000_करोwn(काष्ठा e1000_adapter *adapter);
व्योम e1000_reinit_locked(काष्ठा e1000_adapter *adapter);
व्योम e1000_reset(काष्ठा e1000_adapter *adapter);
पूर्णांक e1000_setup_all_tx_resources(काष्ठा e1000_adapter *adapter);
पूर्णांक e1000_setup_all_rx_resources(काष्ठा e1000_adapter *adapter);
व्योम e1000_मुक्त_all_tx_resources(काष्ठा e1000_adapter *adapter);
व्योम e1000_मुक्त_all_rx_resources(काष्ठा e1000_adapter *adapter);
अटल पूर्णांक e1000_setup_tx_resources(काष्ठा e1000_adapter *adapter,
				    काष्ठा e1000_tx_ring *txdr);
अटल पूर्णांक e1000_setup_rx_resources(काष्ठा e1000_adapter *adapter,
				    काष्ठा e1000_rx_ring *rxdr);
अटल व्योम e1000_मुक्त_tx_resources(काष्ठा e1000_adapter *adapter,
				    काष्ठा e1000_tx_ring *tx_ring);
अटल व्योम e1000_मुक्त_rx_resources(काष्ठा e1000_adapter *adapter,
				    काष्ठा e1000_rx_ring *rx_ring);
व्योम e1000_update_stats(काष्ठा e1000_adapter *adapter);

अटल पूर्णांक e1000_init_module(व्योम);
अटल व्योम e1000_निकास_module(व्योम);
अटल पूर्णांक e1000_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
अटल व्योम e1000_हटाओ(काष्ठा pci_dev *pdev);
अटल पूर्णांक e1000_alloc_queues(काष्ठा e1000_adapter *adapter);
अटल पूर्णांक e1000_sw_init(काष्ठा e1000_adapter *adapter);
पूर्णांक e1000_खोलो(काष्ठा net_device *netdev);
पूर्णांक e1000_बंद(काष्ठा net_device *netdev);
अटल व्योम e1000_configure_tx(काष्ठा e1000_adapter *adapter);
अटल व्योम e1000_configure_rx(काष्ठा e1000_adapter *adapter);
अटल व्योम e1000_setup_rctl(काष्ठा e1000_adapter *adapter);
अटल व्योम e1000_clean_all_tx_rings(काष्ठा e1000_adapter *adapter);
अटल व्योम e1000_clean_all_rx_rings(काष्ठा e1000_adapter *adapter);
अटल व्योम e1000_clean_tx_ring(काष्ठा e1000_adapter *adapter,
				काष्ठा e1000_tx_ring *tx_ring);
अटल व्योम e1000_clean_rx_ring(काष्ठा e1000_adapter *adapter,
				काष्ठा e1000_rx_ring *rx_ring);
अटल व्योम e1000_set_rx_mode(काष्ठा net_device *netdev);
अटल व्योम e1000_update_phy_info_task(काष्ठा work_काष्ठा *work);
अटल व्योम e1000_watchकरोg(काष्ठा work_काष्ठा *work);
अटल व्योम e1000_82547_tx_fअगरo_stall_task(काष्ठा work_काष्ठा *work);
अटल netdev_tx_t e1000_xmit_frame(काष्ठा sk_buff *skb,
				    काष्ठा net_device *netdev);
अटल पूर्णांक e1000_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu);
अटल पूर्णांक e1000_set_mac(काष्ठा net_device *netdev, व्योम *p);
अटल irqवापस_t e1000_पूर्णांकr(पूर्णांक irq, व्योम *data);
अटल bool e1000_clean_tx_irq(काष्ठा e1000_adapter *adapter,
			       काष्ठा e1000_tx_ring *tx_ring);
अटल पूर्णांक e1000_clean(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
अटल bool e1000_clean_rx_irq(काष्ठा e1000_adapter *adapter,
			       काष्ठा e1000_rx_ring *rx_ring,
			       पूर्णांक *work_करोne, पूर्णांक work_to_करो);
अटल bool e1000_clean_jumbo_rx_irq(काष्ठा e1000_adapter *adapter,
				     काष्ठा e1000_rx_ring *rx_ring,
				     पूर्णांक *work_करोne, पूर्णांक work_to_करो);
अटल व्योम e1000_alloc_dummy_rx_buffers(काष्ठा e1000_adapter *adapter,
					 काष्ठा e1000_rx_ring *rx_ring,
					 पूर्णांक cleaned_count)
अणु
पूर्ण
अटल व्योम e1000_alloc_rx_buffers(काष्ठा e1000_adapter *adapter,
				   काष्ठा e1000_rx_ring *rx_ring,
				   पूर्णांक cleaned_count);
अटल व्योम e1000_alloc_jumbo_rx_buffers(काष्ठा e1000_adapter *adapter,
					 काष्ठा e1000_rx_ring *rx_ring,
					 पूर्णांक cleaned_count);
अटल पूर्णांक e1000_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);
अटल पूर्णांक e1000_mii_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr,
			   पूर्णांक cmd);
अटल व्योम e1000_enter_82542_rst(काष्ठा e1000_adapter *adapter);
अटल व्योम e1000_leave_82542_rst(काष्ठा e1000_adapter *adapter);
अटल व्योम e1000_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम e1000_reset_task(काष्ठा work_काष्ठा *work);
अटल व्योम e1000_smartspeed(काष्ठा e1000_adapter *adapter);
अटल पूर्णांक e1000_82547_fअगरo_workaround(काष्ठा e1000_adapter *adapter,
				       काष्ठा sk_buff *skb);

अटल bool e1000_vlan_used(काष्ठा e1000_adapter *adapter);
अटल व्योम e1000_vlan_mode(काष्ठा net_device *netdev,
			    netdev_features_t features);
अटल व्योम e1000_vlan_filter_on_off(काष्ठा e1000_adapter *adapter,
				     bool filter_on);
अटल पूर्णांक e1000_vlan_rx_add_vid(काष्ठा net_device *netdev,
				 __be16 proto, u16 vid);
अटल पूर्णांक e1000_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
				  __be16 proto, u16 vid);
अटल व्योम e1000_restore_vlan(काष्ठा e1000_adapter *adapter);

अटल पूर्णांक __maybe_unused e1000_suspend(काष्ठा device *dev);
अटल पूर्णांक __maybe_unused e1000_resume(काष्ठा device *dev);
अटल व्योम e1000_shutकरोwn(काष्ठा pci_dev *pdev);

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/* क्रम netdump / net console */
अटल व्योम e1000_netpoll (काष्ठा net_device *netdev);
#पूर्ण_अगर

#घोषणा COPYBREAK_DEFAULT 256
अटल अचिन्हित पूर्णांक copyअवरोध __पढ़ो_mostly = COPYBREAK_DEFAULT;
module_param(copyअवरोध, uपूर्णांक, 0644);
MODULE_PARM_DESC(copyअवरोध,
	"Maximum size of packet that is copied to a new buffer on receive");

अटल pci_ers_result_t e1000_io_error_detected(काष्ठा pci_dev *pdev,
						pci_channel_state_t state);
अटल pci_ers_result_t e1000_io_slot_reset(काष्ठा pci_dev *pdev);
अटल व्योम e1000_io_resume(काष्ठा pci_dev *pdev);

अटल स्थिर काष्ठा pci_error_handlers e1000_err_handler = अणु
	.error_detected = e1000_io_error_detected,
	.slot_reset = e1000_io_slot_reset,
	.resume = e1000_io_resume,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(e1000_pm_ops, e1000_suspend, e1000_resume);

अटल काष्ठा pci_driver e1000_driver = अणु
	.name     = e1000_driver_name,
	.id_table = e1000_pci_tbl,
	.probe    = e1000_probe,
	.हटाओ   = e1000_हटाओ,
	.driver = अणु
		.pm = &e1000_pm_ops,
	पूर्ण,
	.shutकरोwn = e1000_shutकरोwn,
	.err_handler = &e1000_err_handler
पूर्ण;

MODULE_AUTHOR("Intel Corporation, <linux.nics@intel.com>");
MODULE_DESCRIPTION("Intel(R) PRO/1000 Network Driver");
MODULE_LICENSE("GPL v2");

#घोषणा DEFAULT_MSG_ENABLE (NETIF_MSG_DRV|NETIF_MSG_PROBE|NETIF_MSG_LINK)
अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");

/**
 * e1000_get_hw_dev - helper function क्रम getting netdev
 * @hw: poपूर्णांकer to HW काष्ठा
 *
 * वापस device used by hardware layer to prपूर्णांक debugging inक्रमmation
 *
 **/
काष्ठा net_device *e1000_get_hw_dev(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_adapter *adapter = hw->back;
	वापस adapter->netdev;
पूर्ण

/**
 * e1000_init_module - Driver Registration Routine
 *
 * e1000_init_module is the first routine called when the driver is
 * loaded. All it करोes is रेजिस्टर with the PCI subप्रणाली.
 **/
अटल पूर्णांक __init e1000_init_module(व्योम)
अणु
	पूर्णांक ret;
	pr_info("%s\n", e1000_driver_string);

	pr_info("%s\n", e1000_copyright);

	ret = pci_रेजिस्टर_driver(&e1000_driver);
	अगर (copyअवरोध != COPYBREAK_DEFAULT) अणु
		अगर (copyअवरोध == 0)
			pr_info("copybreak disabled\n");
		अन्यथा
			pr_info("copybreak enabled for "
				   "packets <= %u bytes\n", copyअवरोध);
	पूर्ण
	वापस ret;
पूर्ण

module_init(e1000_init_module);

/**
 * e1000_निकास_module - Driver Exit Cleanup Routine
 *
 * e1000_निकास_module is called just beक्रमe the driver is हटाओd
 * from memory.
 **/
अटल व्योम __निकास e1000_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&e1000_driver);
पूर्ण

module_निकास(e1000_निकास_module);

अटल पूर्णांक e1000_request_irq(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	irq_handler_t handler = e1000_पूर्णांकr;
	पूर्णांक irq_flags = IRQF_SHARED;
	पूर्णांक err;

	err = request_irq(adapter->pdev->irq, handler, irq_flags, netdev->name,
			  netdev);
	अगर (err) अणु
		e_err(probe, "Unable to allocate interrupt Error: %d\n", err);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम e1000_मुक्त_irq(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	मुक्त_irq(adapter->pdev->irq, netdev);
पूर्ण

/**
 * e1000_irq_disable - Mask off पूर्णांकerrupt generation on the NIC
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम e1000_irq_disable(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	ew32(IMC, ~0);
	E1000_WRITE_FLUSH();
	synchronize_irq(adapter->pdev->irq);
पूर्ण

/**
 * e1000_irq_enable - Enable शेष पूर्णांकerrupt generation settings
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम e1000_irq_enable(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	ew32(IMS, IMS_ENABLE_MASK);
	E1000_WRITE_FLUSH();
पूर्ण

अटल व्योम e1000_update_mng_vlan(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	u16 vid = hw->mng_cookie.vlan_id;
	u16 old_vid = adapter->mng_vlan_id;

	अगर (!e1000_vlan_used(adapter))
		वापस;

	अगर (!test_bit(vid, adapter->active_vlans)) अणु
		अगर (hw->mng_cookie.status &
		    E1000_MNG_DHCP_COOKIE_STATUS_VLAN_SUPPORT) अणु
			e1000_vlan_rx_add_vid(netdev, htons(ETH_P_8021Q), vid);
			adapter->mng_vlan_id = vid;
		पूर्ण अन्यथा अणु
			adapter->mng_vlan_id = E1000_MNG_VLAN_NONE;
		पूर्ण
		अगर ((old_vid != (u16)E1000_MNG_VLAN_NONE) &&
		    (vid != old_vid) &&
		    !test_bit(old_vid, adapter->active_vlans))
			e1000_vlan_rx_समाप्त_vid(netdev, htons(ETH_P_8021Q),
					       old_vid);
	पूर्ण अन्यथा अणु
		adapter->mng_vlan_id = vid;
	पूर्ण
पूर्ण

अटल व्योम e1000_init_manageability(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	अगर (adapter->en_mng_pt) अणु
		u32 manc = er32(MANC);

		/* disable hardware पूर्णांकerception of ARP */
		manc &= ~(E1000_MANC_ARP_EN);

		ew32(MANC, manc);
	पूर्ण
पूर्ण

अटल व्योम e1000_release_manageability(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	अगर (adapter->en_mng_pt) अणु
		u32 manc = er32(MANC);

		/* re-enable hardware पूर्णांकerception of ARP */
		manc |= E1000_MANC_ARP_EN;

		ew32(MANC, manc);
	पूर्ण
पूर्ण

/**
 * e1000_configure - configure the hardware क्रम RX and TX
 * @adapter: निजी board काष्ठाure
 **/
अटल व्योम e1000_configure(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक i;

	e1000_set_rx_mode(netdev);

	e1000_restore_vlan(adapter);
	e1000_init_manageability(adapter);

	e1000_configure_tx(adapter);
	e1000_setup_rctl(adapter);
	e1000_configure_rx(adapter);
	/* call E1000_DESC_UNUSED which always leaves
	 * at least 1 descriptor unused to make sure
	 * next_to_use != next_to_clean
	 */
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा e1000_rx_ring *ring = &adapter->rx_ring[i];
		adapter->alloc_rx_buf(adapter, ring,
				      E1000_DESC_UNUSED(ring));
	पूर्ण
पूर्ण

पूर्णांक e1000_up(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* hardware has been reset, we need to reload some things */
	e1000_configure(adapter);

	clear_bit(__E1000_DOWN, &adapter->flags);

	napi_enable(&adapter->napi);

	e1000_irq_enable(adapter);

	netअगर_wake_queue(adapter->netdev);

	/* fire a link change पूर्णांकerrupt to start the watchकरोg */
	ew32(ICS, E1000_ICS_LSC);
	वापस 0;
पूर्ण

/**
 * e1000_घातer_up_phy - restore link in हाल the phy was घातered करोwn
 * @adapter: address of board निजी काष्ठाure
 *
 * The phy may be घातered करोwn to save घातer and turn off link when the
 * driver is unloaded and wake on lan is not enabled (among others)
 * *** this routine MUST be followed by a call to e1000_reset ***
 **/
व्योम e1000_घातer_up_phy(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 mii_reg = 0;

	/* Just clear the घातer करोwn bit to wake the phy back up */
	अगर (hw->media_type == e1000_media_type_copper) अणु
		/* according to the manual, the phy will retain its
		 * settings across a घातer-करोwn/up cycle
		 */
		e1000_पढ़ो_phy_reg(hw, PHY_CTRL, &mii_reg);
		mii_reg &= ~MII_CR_POWER_DOWN;
		e1000_ग_लिखो_phy_reg(hw, PHY_CTRL, mii_reg);
	पूर्ण
पूर्ण

अटल व्योम e1000_घातer_करोwn_phy(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* Power करोwn the PHY so no link is implied when पूर्णांकerface is करोwn *
	 * The PHY cannot be घातered करोwn अगर any of the following is true *
	 * (a) WoL is enabled
	 * (b) AMT is active
	 * (c) SoL/IDER session is active
	 */
	अगर (!adapter->wol && hw->mac_type >= e1000_82540 &&
	   hw->media_type == e1000_media_type_copper) अणु
		u16 mii_reg = 0;

		चयन (hw->mac_type) अणु
		हाल e1000_82540:
		हाल e1000_82545:
		हाल e1000_82545_rev_3:
		हाल e1000_82546:
		हाल e1000_ce4100:
		हाल e1000_82546_rev_3:
		हाल e1000_82541:
		हाल e1000_82541_rev_2:
		हाल e1000_82547:
		हाल e1000_82547_rev_2:
			अगर (er32(MANC) & E1000_MANC_SMBUS_EN)
				जाओ out;
			अवरोध;
		शेष:
			जाओ out;
		पूर्ण
		e1000_पढ़ो_phy_reg(hw, PHY_CTRL, &mii_reg);
		mii_reg |= MII_CR_POWER_DOWN;
		e1000_ग_लिखो_phy_reg(hw, PHY_CTRL, mii_reg);
		msleep(1);
	पूर्ण
out:
	वापस;
पूर्ण

अटल व्योम e1000_करोwn_and_stop(काष्ठा e1000_adapter *adapter)
अणु
	set_bit(__E1000_DOWN, &adapter->flags);

	cancel_delayed_work_sync(&adapter->watchकरोg_task);

	/*
	 * Since the watchकरोg task can reschedule other tasks, we should cancel
	 * it first, otherwise we can run पूर्णांकo the situation when a work is
	 * still running after the adapter has been turned करोwn.
	 */

	cancel_delayed_work_sync(&adapter->phy_info_task);
	cancel_delayed_work_sync(&adapter->fअगरo_stall_task);

	/* Only समाप्त reset task अगर adapter is not resetting */
	अगर (!test_bit(__E1000_RESETTING, &adapter->flags))
		cancel_work_sync(&adapter->reset_task);
पूर्ण

व्योम e1000_करोwn(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	u32 rctl, tctl;

	/* disable receives in the hardware */
	rctl = er32(RCTL);
	ew32(RCTL, rctl & ~E1000_RCTL_EN);
	/* flush and sleep below */

	netअगर_tx_disable(netdev);

	/* disable transmits in the hardware */
	tctl = er32(TCTL);
	tctl &= ~E1000_TCTL_EN;
	ew32(TCTL, tctl);
	/* flush both disables and रुको क्रम them to finish */
	E1000_WRITE_FLUSH();
	msleep(10);

	/* Set the carrier off after transmits have been disabled in the
	 * hardware, to aव्योम race conditions with e1000_watchकरोg() (which
	 * may be running concurrently to us, checking क्रम the carrier
	 * bit to decide whether it should enable transmits again). Such
	 * a race condition would result पूर्णांकo transmission being disabled
	 * in the hardware until the next IFF_DOWN+IFF_UP cycle.
	 */
	netअगर_carrier_off(netdev);

	napi_disable(&adapter->napi);

	e1000_irq_disable(adapter);

	/* Setting DOWN must be after irq_disable to prevent
	 * a screaming पूर्णांकerrupt.  Setting DOWN also prevents
	 * tasks from rescheduling.
	 */
	e1000_करोwn_and_stop(adapter);

	adapter->link_speed = 0;
	adapter->link_duplex = 0;

	e1000_reset(adapter);
	e1000_clean_all_tx_rings(adapter);
	e1000_clean_all_rx_rings(adapter);
पूर्ण

व्योम e1000_reinit_locked(काष्ठा e1000_adapter *adapter)
अणु
	जबतक (test_and_set_bit(__E1000_RESETTING, &adapter->flags))
		msleep(1);

	/* only run the task अगर not alपढ़ोy करोwn */
	अगर (!test_bit(__E1000_DOWN, &adapter->flags)) अणु
		e1000_करोwn(adapter);
		e1000_up(adapter);
	पूर्ण

	clear_bit(__E1000_RESETTING, &adapter->flags);
पूर्ण

व्योम e1000_reset(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 pba = 0, tx_space, min_tx_space, min_rx_space;
	bool legacy_pba_adjust = false;
	u16 hwm;

	/* Repartition Pba क्रम greater than 9k mtu
	 * To take effect CTRL.RST is required.
	 */

	चयन (hw->mac_type) अणु
	हाल e1000_82542_rev2_0:
	हाल e1000_82542_rev2_1:
	हाल e1000_82543:
	हाल e1000_82544:
	हाल e1000_82540:
	हाल e1000_82541:
	हाल e1000_82541_rev_2:
		legacy_pba_adjust = true;
		pba = E1000_PBA_48K;
		अवरोध;
	हाल e1000_82545:
	हाल e1000_82545_rev_3:
	हाल e1000_82546:
	हाल e1000_ce4100:
	हाल e1000_82546_rev_3:
		pba = E1000_PBA_48K;
		अवरोध;
	हाल e1000_82547:
	हाल e1000_82547_rev_2:
		legacy_pba_adjust = true;
		pba = E1000_PBA_30K;
		अवरोध;
	हाल e1000_undefined:
	हाल e1000_num_macs:
		अवरोध;
	पूर्ण

	अगर (legacy_pba_adjust) अणु
		अगर (hw->max_frame_size > E1000_RXBUFFER_8192)
			pba -= 8; /* allocate more FIFO क्रम Tx */

		अगर (hw->mac_type == e1000_82547) अणु
			adapter->tx_fअगरo_head = 0;
			adapter->tx_head_addr = pba << E1000_TX_HEAD_ADDR_SHIFT;
			adapter->tx_fअगरo_size =
				(E1000_PBA_40K - pba) << E1000_PBA_BYTES_SHIFT;
			atomic_set(&adapter->tx_fअगरo_stall, 0);
		पूर्ण
	पूर्ण अन्यथा अगर (hw->max_frame_size >  ETH_FRAME_LEN + ETH_FCS_LEN) अणु
		/* adjust PBA क्रम jumbo frames */
		ew32(PBA, pba);

		/* To मुख्यtain wire speed transmits, the Tx FIFO should be
		 * large enough to accommodate two full transmit packets,
		 * rounded up to the next 1KB and expressed in KB.  Likewise,
		 * the Rx FIFO should be large enough to accommodate at least
		 * one full receive packet and is similarly rounded up and
		 * expressed in KB.
		 */
		pba = er32(PBA);
		/* upper 16 bits has Tx packet buffer allocation size in KB */
		tx_space = pba >> 16;
		/* lower 16 bits has Rx packet buffer allocation size in KB */
		pba &= 0xffff;
		/* the Tx fअगरo also stores 16 bytes of inक्रमmation about the Tx
		 * but करोn't include ethernet FCS because hardware appends it
		 */
		min_tx_space = (hw->max_frame_size +
				माप(काष्ठा e1000_tx_desc) -
				ETH_FCS_LEN) * 2;
		min_tx_space = ALIGN(min_tx_space, 1024);
		min_tx_space >>= 10;
		/* software strips receive CRC, so leave room क्रम it */
		min_rx_space = hw->max_frame_size;
		min_rx_space = ALIGN(min_rx_space, 1024);
		min_rx_space >>= 10;

		/* If current Tx allocation is less than the min Tx FIFO size,
		 * and the min Tx FIFO size is less than the current Rx FIFO
		 * allocation, take space away from current Rx allocation
		 */
		अगर (tx_space < min_tx_space &&
		    ((min_tx_space - tx_space) < pba)) अणु
			pba = pba - (min_tx_space - tx_space);

			/* PCI/PCIx hardware has PBA alignment स्थिरraपूर्णांकs */
			चयन (hw->mac_type) अणु
			हाल e1000_82545 ... e1000_82546_rev_3:
				pba &= ~(E1000_PBA_8K - 1);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

			/* अगर लघु on Rx space, Rx wins and must trump Tx
			 * adjusपंचांगent or use Early Receive अगर available
			 */
			अगर (pba < min_rx_space)
				pba = min_rx_space;
		पूर्ण
	पूर्ण

	ew32(PBA, pba);

	/* flow control settings:
	 * The high water mark must be low enough to fit one full frame
	 * (or the size used क्रम early receive) above it in the Rx FIFO.
	 * Set it to the lower of:
	 * - 90% of the Rx FIFO size, and
	 * - the full Rx FIFO size minus the early receive size (क्रम parts
	 *   with ERT support assuming ERT set to E1000_ERT_2048), or
	 * - the full Rx FIFO size minus one full frame
	 */
	hwm = min(((pba << 10) * 9 / 10),
		  ((pba << 10) - hw->max_frame_size));

	hw->fc_high_water = hwm & 0xFFF8;	/* 8-byte granularity */
	hw->fc_low_water = hw->fc_high_water - 8;
	hw->fc_छोड़ो_समय = E1000_FC_PAUSE_TIME;
	hw->fc_send_xon = 1;
	hw->fc = hw->original_fc;

	/* Allow समय क्रम pending master requests to run */
	e1000_reset_hw(hw);
	अगर (hw->mac_type >= e1000_82544)
		ew32(WUC, 0);

	अगर (e1000_init_hw(hw))
		e_dev_err("Hardware Error\n");
	e1000_update_mng_vlan(adapter);

	/* अगर (adapter->hwflags & HWFLAGS_PHY_PWR_BIT) अणु */
	अगर (hw->mac_type >= e1000_82544 &&
	    hw->स्वतःneg == 1 &&
	    hw->स्वतःneg_advertised == ADVERTISE_1000_FULL) अणु
		u32 ctrl = er32(CTRL);
		/* clear phy घातer management bit अगर we are in gig only mode,
		 * which अगर enabled will attempt negotiation to 100Mb, which
		 * can cause a loss of link at घातer off or driver unload
		 */
		ctrl &= ~E1000_CTRL_SWDPIN3;
		ew32(CTRL, ctrl);
	पूर्ण

	/* Enable h/w to recognize an 802.1Q VLAN Ethernet packet */
	ew32(VET, ETHERNET_IEEE_VLAN_TYPE);

	e1000_reset_adaptive(hw);
	e1000_phy_get_info(hw, &adapter->phy_info);

	e1000_release_manageability(adapter);
पूर्ण

/* Dump the eeprom क्रम users having checksum issues */
अटल व्योम e1000_dump_eeprom(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा ethtool_eeprom eeprom;
	स्थिर काष्ठा ethtool_ops *ops = netdev->ethtool_ops;
	u8 *data;
	पूर्णांक i;
	u16 csum_old, csum_new = 0;

	eeprom.len = ops->get_eeprom_len(netdev);
	eeprom.offset = 0;

	data = kदो_स्मृति(eeprom.len, GFP_KERNEL);
	अगर (!data)
		वापस;

	ops->get_eeprom(netdev, &eeprom, data);

	csum_old = (data[EEPROM_CHECKSUM_REG * 2]) +
		   (data[EEPROM_CHECKSUM_REG * 2 + 1] << 8);
	क्रम (i = 0; i < EEPROM_CHECKSUM_REG * 2; i += 2)
		csum_new += data[i] + (data[i + 1] << 8);
	csum_new = EEPROM_SUM - csum_new;

	pr_err("/*********************/\n");
	pr_err("Current EEPROM Checksum : 0x%04x\n", csum_old);
	pr_err("Calculated              : 0x%04x\n", csum_new);

	pr_err("Offset    Values\n");
	pr_err("========  ======\n");
	prपूर्णांक_hex_dump(KERN_ERR, "", DUMP_PREFIX_OFFSET, 16, 1, data, 128, 0);

	pr_err("Include this output when contacting your support provider.\n");
	pr_err("This is not a software error! Something bad happened to\n");
	pr_err("your hardware or EEPROM image. Ignoring this problem could\n");
	pr_err("result in further problems, possibly loss of data,\n");
	pr_err("corruption or system hangs!\n");
	pr_err("The MAC Address will be reset to 00:00:00:00:00:00,\n");
	pr_err("which is invalid and requires you to set the proper MAC\n");
	pr_err("address manually before continuing to enable this network\n");
	pr_err("device. Please inspect the EEPROM dump and report the\n");
	pr_err("issue to your hardware vendor or Intel Customer Support.\n");
	pr_err("/*********************/\n");

	kमुक्त(data);
पूर्ण

/**
 * e1000_is_need_ioport - determine अगर an adapter needs ioport resources or not
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * Return true अगर an adapter needs ioport resources
 **/
अटल पूर्णांक e1000_is_need_ioport(काष्ठा pci_dev *pdev)
अणु
	चयन (pdev->device) अणु
	हाल E1000_DEV_ID_82540EM:
	हाल E1000_DEV_ID_82540EM_LOM:
	हाल E1000_DEV_ID_82540EP:
	हाल E1000_DEV_ID_82540EP_LOM:
	हाल E1000_DEV_ID_82540EP_LP:
	हाल E1000_DEV_ID_82541EI:
	हाल E1000_DEV_ID_82541EI_MOBILE:
	हाल E1000_DEV_ID_82541ER:
	हाल E1000_DEV_ID_82541ER_LOM:
	हाल E1000_DEV_ID_82541GI:
	हाल E1000_DEV_ID_82541GI_LF:
	हाल E1000_DEV_ID_82541GI_MOBILE:
	हाल E1000_DEV_ID_82544EI_COPPER:
	हाल E1000_DEV_ID_82544EI_FIBER:
	हाल E1000_DEV_ID_82544GC_COPPER:
	हाल E1000_DEV_ID_82544GC_LOM:
	हाल E1000_DEV_ID_82545EM_COPPER:
	हाल E1000_DEV_ID_82545EM_FIBER:
	हाल E1000_DEV_ID_82546EB_COPPER:
	हाल E1000_DEV_ID_82546EB_FIBER:
	हाल E1000_DEV_ID_82546EB_QUAD_COPPER:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल netdev_features_t e1000_fix_features(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	/* Since there is no support क्रम separate Rx/Tx vlan accel
	 * enable/disable make sure Tx flag is always in same state as Rx.
	 */
	अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
		features |= NETIF_F_HW_VLAN_CTAG_TX;
	अन्यथा
		features &= ~NETIF_F_HW_VLAN_CTAG_TX;

	वापस features;
पूर्ण

अटल पूर्णांक e1000_set_features(काष्ठा net_device *netdev,
	netdev_features_t features)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	netdev_features_t changed = features ^ netdev->features;

	अगर (changed & NETIF_F_HW_VLAN_CTAG_RX)
		e1000_vlan_mode(netdev, features);

	अगर (!(changed & (NETIF_F_RXCSUM | NETIF_F_RXALL)))
		वापस 0;

	netdev->features = features;
	adapter->rx_csum = !!(features & NETIF_F_RXCSUM);

	अगर (netअगर_running(netdev))
		e1000_reinit_locked(adapter);
	अन्यथा
		e1000_reset(adapter);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा net_device_ops e1000_netdev_ops = अणु
	.nकरो_खोलो		= e1000_खोलो,
	.nकरो_stop		= e1000_बंद,
	.nकरो_start_xmit		= e1000_xmit_frame,
	.nकरो_set_rx_mode	= e1000_set_rx_mode,
	.nकरो_set_mac_address	= e1000_set_mac,
	.nकरो_tx_समयout		= e1000_tx_समयout,
	.nकरो_change_mtu		= e1000_change_mtu,
	.nकरो_करो_ioctl		= e1000_ioctl,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_vlan_rx_add_vid	= e1000_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= e1000_vlan_rx_समाप्त_vid,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= e1000_netpoll,
#पूर्ण_अगर
	.nकरो_fix_features	= e1000_fix_features,
	.nकरो_set_features	= e1000_set_features,
पूर्ण;

/**
 * e1000_init_hw_काष्ठा - initialize members of hw काष्ठा
 * @adapter: board निजी काष्ठा
 * @hw: काष्ठाure used by e1000_hw.c
 *
 * Factors out initialization of the e1000_hw काष्ठा to its own function
 * that can be called very early at init (just after काष्ठा allocation).
 * Fields are initialized based on PCI device inक्रमmation and
 * OS network device settings (MTU size).
 * Returns negative error codes अगर MAC type setup fails.
 */
अटल पूर्णांक e1000_init_hw_काष्ठा(काष्ठा e1000_adapter *adapter,
				काष्ठा e1000_hw *hw)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;

	/* PCI config space info */
	hw->venकरोr_id = pdev->venकरोr;
	hw->device_id = pdev->device;
	hw->subप्रणाली_venकरोr_id = pdev->subप्रणाली_venकरोr;
	hw->subप्रणाली_id = pdev->subप्रणाली_device;
	hw->revision_id = pdev->revision;

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &hw->pci_cmd_word);

	hw->max_frame_size = adapter->netdev->mtu +
			     ENET_HEADER_SIZE + ETHERNET_FCS_SIZE;
	hw->min_frame_size = MINIMUM_ETHERNET_FRAME_SIZE;

	/* identअगरy the MAC */
	अगर (e1000_set_mac_type(hw)) अणु
		e_err(probe, "Unknown MAC Type\n");
		वापस -EIO;
	पूर्ण

	चयन (hw->mac_type) अणु
	शेष:
		अवरोध;
	हाल e1000_82541:
	हाल e1000_82547:
	हाल e1000_82541_rev_2:
	हाल e1000_82547_rev_2:
		hw->phy_init_script = 1;
		अवरोध;
	पूर्ण

	e1000_set_media_type(hw);
	e1000_get_bus_info(hw);

	hw->रुको_स्वतःneg_complete = false;
	hw->tbi_compatibility_en = true;
	hw->adaptive_अगरs = true;

	/* Copper options */

	अगर (hw->media_type == e1000_media_type_copper) अणु
		hw->mdix = AUTO_ALL_MODES;
		hw->disable_polarity_correction = false;
		hw->master_slave = E1000_MASTER_SLAVE;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * e1000_probe - Device Initialization Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in e1000_pci_tbl
 *
 * Returns 0 on success, negative on failure
 *
 * e1000_probe initializes an adapter identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring of the adapter निजी काष्ठाure,
 * and a hardware reset occur.
 **/
अटल पूर्णांक e1000_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev;
	काष्ठा e1000_adapter *adapter = शून्य;
	काष्ठा e1000_hw *hw;

	अटल पूर्णांक cards_found;
	अटल पूर्णांक global_quad_port_a; /* global ksp3 port a indication */
	पूर्णांक i, err, pci_using_dac;
	u16 eeprom_data = 0;
	u16 पंचांगp = 0;
	u16 eeprom_apme_mask = E1000_EEPROM_APME;
	पूर्णांक bars, need_ioport;
	bool disable_dev = false;

	/* करो not allocate ioport bars when not needed */
	need_ioport = e1000_is_need_ioport(pdev);
	अगर (need_ioport) अणु
		bars = pci_select_bars(pdev, IORESOURCE_MEM | IORESOURCE_IO);
		err = pci_enable_device(pdev);
	पूर्ण अन्यथा अणु
		bars = pci_select_bars(pdev, IORESOURCE_MEM);
		err = pci_enable_device_mem(pdev);
	पूर्ण
	अगर (err)
		वापस err;

	err = pci_request_selected_regions(pdev, bars, e1000_driver_name);
	अगर (err)
		जाओ err_pci_reg;

	pci_set_master(pdev);
	err = pci_save_state(pdev);
	अगर (err)
		जाओ err_alloc_etherdev;

	err = -ENOMEM;
	netdev = alloc_etherdev(माप(काष्ठा e1000_adapter));
	अगर (!netdev)
		जाओ err_alloc_etherdev;

	SET_NETDEV_DEV(netdev, &pdev->dev);

	pci_set_drvdata(pdev, netdev);
	adapter = netdev_priv(netdev);
	adapter->netdev = netdev;
	adapter->pdev = pdev;
	adapter->msg_enable = netअगर_msg_init(debug, DEFAULT_MSG_ENABLE);
	adapter->bars = bars;
	adapter->need_ioport = need_ioport;

	hw = &adapter->hw;
	hw->back = adapter;

	err = -EIO;
	hw->hw_addr = pci_ioremap_bar(pdev, BAR_0);
	अगर (!hw->hw_addr)
		जाओ err_ioremap;

	अगर (adapter->need_ioport) अणु
		क्रम (i = BAR_1; i < PCI_STD_NUM_BARS; i++) अणु
			अगर (pci_resource_len(pdev, i) == 0)
				जारी;
			अगर (pci_resource_flags(pdev, i) & IORESOURCE_IO) अणु
				hw->io_base = pci_resource_start(pdev, i);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* make पढ़ोy क्रम any अगर (hw->...) below */
	err = e1000_init_hw_काष्ठा(adapter, hw);
	अगर (err)
		जाओ err_sw_init;

	/* there is a workaround being applied below that limits
	 * 64-bit DMA addresses to 64-bit hardware.  There are some
	 * 32-bit adapters that Tx hang when given 64-bit DMA addresses
	 */
	pci_using_dac = 0;
	अगर ((hw->bus_type == e1000_bus_type_pcix) &&
	    !dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64))) अणु
		pci_using_dac = 1;
	पूर्ण अन्यथा अणु
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			pr_err("No usable DMA config, aborting\n");
			जाओ err_dma;
		पूर्ण
	पूर्ण

	netdev->netdev_ops = &e1000_netdev_ops;
	e1000_set_ethtool_ops(netdev);
	netdev->watchकरोg_समयo = 5 * HZ;
	netअगर_napi_add(netdev, &adapter->napi, e1000_clean, 64);

	म_नकलन(netdev->name, pci_name(pdev), माप(netdev->name) - 1);

	adapter->bd_number = cards_found;

	/* setup the निजी काष्ठाure */

	err = e1000_sw_init(adapter);
	अगर (err)
		जाओ err_sw_init;

	err = -EIO;
	अगर (hw->mac_type == e1000_ce4100) अणु
		hw->ce4100_gbe_mdio_base_virt =
					ioremap(pci_resource_start(pdev, BAR_1),
						pci_resource_len(pdev, BAR_1));

		अगर (!hw->ce4100_gbe_mdio_base_virt)
			जाओ err_mdio_ioremap;
	पूर्ण

	अगर (hw->mac_type >= e1000_82543) अणु
		netdev->hw_features = NETIF_F_SG |
				   NETIF_F_HW_CSUM |
				   NETIF_F_HW_VLAN_CTAG_RX;
		netdev->features = NETIF_F_HW_VLAN_CTAG_TX |
				   NETIF_F_HW_VLAN_CTAG_FILTER;
	पूर्ण

	अगर ((hw->mac_type >= e1000_82544) &&
	   (hw->mac_type != e1000_82547))
		netdev->hw_features |= NETIF_F_TSO;

	netdev->priv_flags |= IFF_SUPP_NOFCS;

	netdev->features |= netdev->hw_features;
	netdev->hw_features |= (NETIF_F_RXCSUM |
				NETIF_F_RXALL |
				NETIF_F_RXFCS);

	अगर (pci_using_dac) अणु
		netdev->features |= NETIF_F_HIGHDMA;
		netdev->vlan_features |= NETIF_F_HIGHDMA;
	पूर्ण

	netdev->vlan_features |= (NETIF_F_TSO |
				  NETIF_F_HW_CSUM |
				  NETIF_F_SG);

	/* Do not set IFF_UNICAST_FLT क्रम VMWare's 82545EM */
	अगर (hw->device_id != E1000_DEV_ID_82545EM_COPPER ||
	    hw->subप्रणाली_venकरोr_id != PCI_VENDOR_ID_VMWARE)
		netdev->priv_flags |= IFF_UNICAST_FLT;

	/* MTU range: 46 - 16110 */
	netdev->min_mtu = ETH_ZLEN - ETH_HLEN;
	netdev->max_mtu = MAX_JUMBO_FRAME_SIZE - (ETH_HLEN + ETH_FCS_LEN);

	adapter->en_mng_pt = e1000_enable_mng_pass_thru(hw);

	/* initialize eeprom parameters */
	अगर (e1000_init_eeprom_params(hw)) अणु
		e_err(probe, "EEPROM initialization failed\n");
		जाओ err_eeprom;
	पूर्ण

	/* beक्रमe पढ़ोing the EEPROM, reset the controller to
	 * put the device in a known good starting state
	 */

	e1000_reset_hw(hw);

	/* make sure the EEPROM is good */
	अगर (e1000_validate_eeprom_checksum(hw) < 0) अणु
		e_err(probe, "The EEPROM Checksum Is Not Valid\n");
		e1000_dump_eeprom(adapter);
		/* set MAC address to all zeroes to invalidate and temporary
		 * disable this device क्रम the user. This blocks regular
		 * traffic जबतक still permitting ethtool ioctls from reaching
		 * the hardware as well as allowing the user to run the
		 * पूर्णांकerface after manually setting a hw addr using
		 * `ip set address`
		 */
		स_रखो(hw->mac_addr, 0, netdev->addr_len);
	पूर्ण अन्यथा अणु
		/* copy the MAC address out of the EEPROM */
		अगर (e1000_पढ़ो_mac_addr(hw))
			e_err(probe, "EEPROM Read Error\n");
	पूर्ण
	/* करोn't block initialization here due to bad MAC address */
	स_नकल(netdev->dev_addr, hw->mac_addr, netdev->addr_len);

	अगर (!is_valid_ether_addr(netdev->dev_addr))
		e_err(probe, "Invalid MAC Address\n");


	INIT_DELAYED_WORK(&adapter->watchकरोg_task, e1000_watchकरोg);
	INIT_DELAYED_WORK(&adapter->fअगरo_stall_task,
			  e1000_82547_tx_fअगरo_stall_task);
	INIT_DELAYED_WORK(&adapter->phy_info_task, e1000_update_phy_info_task);
	INIT_WORK(&adapter->reset_task, e1000_reset_task);

	e1000_check_options(adapter);

	/* Initial Wake on LAN setting
	 * If APM wake is enabled in the EEPROM,
	 * enable the ACPI Magic Packet filter
	 */

	चयन (hw->mac_type) अणु
	हाल e1000_82542_rev2_0:
	हाल e1000_82542_rev2_1:
	हाल e1000_82543:
		अवरोध;
	हाल e1000_82544:
		e1000_पढ़ो_eeprom(hw,
			EEPROM_INIT_CONTROL2_REG, 1, &eeprom_data);
		eeprom_apme_mask = E1000_EEPROM_82544_APM;
		अवरोध;
	हाल e1000_82546:
	हाल e1000_82546_rev_3:
		अगर (er32(STATUS) & E1000_STATUS_FUNC_1) अणु
			e1000_पढ़ो_eeprom(hw,
				EEPROM_INIT_CONTROL3_PORT_B, 1, &eeprom_data);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		e1000_पढ़ो_eeprom(hw,
			EEPROM_INIT_CONTROL3_PORT_A, 1, &eeprom_data);
		अवरोध;
	पूर्ण
	अगर (eeprom_data & eeprom_apme_mask)
		adapter->eeprom_wol |= E1000_WUFC_MAG;

	/* now that we have the eeprom settings, apply the special हालs
	 * where the eeprom may be wrong or the board simply won't support
	 * wake on lan on a particular port
	 */
	चयन (pdev->device) अणु
	हाल E1000_DEV_ID_82546GB_PCIE:
		adapter->eeprom_wol = 0;
		अवरोध;
	हाल E1000_DEV_ID_82546EB_FIBER:
	हाल E1000_DEV_ID_82546GB_FIBER:
		/* Wake events only supported on port A क्रम dual fiber
		 * regardless of eeprom setting
		 */
		अगर (er32(STATUS) & E1000_STATUS_FUNC_1)
			adapter->eeprom_wol = 0;
		अवरोध;
	हाल E1000_DEV_ID_82546GB_QUAD_COPPER_KSP3:
		/* अगर quad port adapter, disable WoL on all but port A */
		अगर (global_quad_port_a != 0)
			adapter->eeprom_wol = 0;
		अन्यथा
			adapter->quad_port_a = true;
		/* Reset क्रम multiple quad port adapters */
		अगर (++global_quad_port_a == 4)
			global_quad_port_a = 0;
		अवरोध;
	पूर्ण

	/* initialize the wol settings based on the eeprom settings */
	adapter->wol = adapter->eeprom_wol;
	device_set_wakeup_enable(&adapter->pdev->dev, adapter->wol);

	/* Auto detect PHY address */
	अगर (hw->mac_type == e1000_ce4100) अणु
		क्रम (i = 0; i < 32; i++) अणु
			hw->phy_addr = i;
			e1000_पढ़ो_phy_reg(hw, PHY_ID2, &पंचांगp);

			अगर (पंचांगp != 0 && पंचांगp != 0xFF)
				अवरोध;
		पूर्ण

		अगर (i >= 32)
			जाओ err_eeprom;
	पूर्ण

	/* reset the hardware with the new settings */
	e1000_reset(adapter);

	म_नकल(netdev->name, "eth%d");
	err = रेजिस्टर_netdev(netdev);
	अगर (err)
		जाओ err_रेजिस्टर;

	e1000_vlan_filter_on_off(adapter, false);

	/* prपूर्णांक bus type/speed/width info */
	e_info(probe, "(PCI%s:%dMHz:%d-bit) %pM\n",
	       ((hw->bus_type == e1000_bus_type_pcix) ? "-X" : ""),
	       ((hw->bus_speed == e1000_bus_speed_133) ? 133 :
		(hw->bus_speed == e1000_bus_speed_120) ? 120 :
		(hw->bus_speed == e1000_bus_speed_100) ? 100 :
		(hw->bus_speed == e1000_bus_speed_66) ? 66 : 33),
	       ((hw->bus_width == e1000_bus_width_64) ? 64 : 32),
	       netdev->dev_addr);

	/* carrier off reporting is important to ethtool even BEFORE खोलो */
	netअगर_carrier_off(netdev);

	e_info(probe, "Intel(R) PRO/1000 Network Connection\n");

	cards_found++;
	वापस 0;

err_रेजिस्टर:
err_eeprom:
	e1000_phy_hw_reset(hw);

	अगर (hw->flash_address)
		iounmap(hw->flash_address);
	kमुक्त(adapter->tx_ring);
	kमुक्त(adapter->rx_ring);
err_dma:
err_sw_init:
err_mdio_ioremap:
	iounmap(hw->ce4100_gbe_mdio_base_virt);
	iounmap(hw->hw_addr);
err_ioremap:
	disable_dev = !test_and_set_bit(__E1000_DISABLED, &adapter->flags);
	मुक्त_netdev(netdev);
err_alloc_etherdev:
	pci_release_selected_regions(pdev, bars);
err_pci_reg:
	अगर (!adapter || disable_dev)
		pci_disable_device(pdev);
	वापस err;
पूर्ण

/**
 * e1000_हटाओ - Device Removal Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * e1000_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device. That could be caused by a
 * Hot-Plug event, or because the driver is going to be हटाओd from
 * memory.
 **/
अटल व्योम e1000_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	bool disable_dev;

	e1000_करोwn_and_stop(adapter);
	e1000_release_manageability(adapter);

	unरेजिस्टर_netdev(netdev);

	e1000_phy_hw_reset(hw);

	kमुक्त(adapter->tx_ring);
	kमुक्त(adapter->rx_ring);

	अगर (hw->mac_type == e1000_ce4100)
		iounmap(hw->ce4100_gbe_mdio_base_virt);
	iounmap(hw->hw_addr);
	अगर (hw->flash_address)
		iounmap(hw->flash_address);
	pci_release_selected_regions(pdev, adapter->bars);

	disable_dev = !test_and_set_bit(__E1000_DISABLED, &adapter->flags);
	मुक्त_netdev(netdev);

	अगर (disable_dev)
		pci_disable_device(pdev);
पूर्ण

/**
 * e1000_sw_init - Initialize general software काष्ठाures (काष्ठा e1000_adapter)
 * @adapter: board निजी काष्ठाure to initialize
 *
 * e1000_sw_init initializes the Adapter निजी data काष्ठाure.
 * e1000_init_hw_काष्ठा MUST be called beक्रमe this function
 **/
अटल पूर्णांक e1000_sw_init(काष्ठा e1000_adapter *adapter)
अणु
	adapter->rx_buffer_len = MAXIMUM_ETHERNET_VLAN_SIZE;

	adapter->num_tx_queues = 1;
	adapter->num_rx_queues = 1;

	अगर (e1000_alloc_queues(adapter)) अणु
		e_err(probe, "Unable to allocate memory for queues\n");
		वापस -ENOMEM;
	पूर्ण

	/* Explicitly disable IRQ since the NIC can be in any state. */
	e1000_irq_disable(adapter);

	spin_lock_init(&adapter->stats_lock);

	set_bit(__E1000_DOWN, &adapter->flags);

	वापस 0;
पूर्ण

/**
 * e1000_alloc_queues - Allocate memory क्रम all rings
 * @adapter: board निजी काष्ठाure to initialize
 *
 * We allocate one ring per queue at run-समय since we करोn't know the
 * number of queues at compile-समय.
 **/
अटल पूर्णांक e1000_alloc_queues(काष्ठा e1000_adapter *adapter)
अणु
	adapter->tx_ring = kसुस्मृति(adapter->num_tx_queues,
				   माप(काष्ठा e1000_tx_ring), GFP_KERNEL);
	अगर (!adapter->tx_ring)
		वापस -ENOMEM;

	adapter->rx_ring = kसुस्मृति(adapter->num_rx_queues,
				   माप(काष्ठा e1000_rx_ring), GFP_KERNEL);
	अगर (!adapter->rx_ring) अणु
		kमुक्त(adapter->tx_ring);
		वापस -ENOMEM;
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_खोलो - Called when a network पूर्णांकerface is made active
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0 on success, negative value on failure
 *
 * The खोलो entry poपूर्णांक is called when a network पूर्णांकerface is made
 * active by the प्रणाली (IFF_UP).  At this poपूर्णांक all resources needed
 * क्रम transmit and receive operations are allocated, the पूर्णांकerrupt
 * handler is रेजिस्टरed with the OS, the watchकरोg task is started,
 * and the stack is notअगरied that the पूर्णांकerface is पढ़ोy.
 **/
पूर्णांक e1000_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक err;

	/* disallow खोलो during test */
	अगर (test_bit(__E1000_TESTING, &adapter->flags))
		वापस -EBUSY;

	netअगर_carrier_off(netdev);

	/* allocate transmit descriptors */
	err = e1000_setup_all_tx_resources(adapter);
	अगर (err)
		जाओ err_setup_tx;

	/* allocate receive descriptors */
	err = e1000_setup_all_rx_resources(adapter);
	अगर (err)
		जाओ err_setup_rx;

	e1000_घातer_up_phy(adapter);

	adapter->mng_vlan_id = E1000_MNG_VLAN_NONE;
	अगर ((hw->mng_cookie.status &
			  E1000_MNG_DHCP_COOKIE_STATUS_VLAN_SUPPORT)) अणु
		e1000_update_mng_vlan(adapter);
	पूर्ण

	/* beक्रमe we allocate an पूर्णांकerrupt, we must be पढ़ोy to handle it.
	 * Setting DEBUG_SHIRQ in the kernel makes it fire an पूर्णांकerrupt
	 * as soon as we call pci_request_irq, so we have to setup our
	 * clean_rx handler beक्रमe we करो so.
	 */
	e1000_configure(adapter);

	err = e1000_request_irq(adapter);
	अगर (err)
		जाओ err_req_irq;

	/* From here on the code is the same as e1000_up() */
	clear_bit(__E1000_DOWN, &adapter->flags);

	napi_enable(&adapter->napi);

	e1000_irq_enable(adapter);

	netअगर_start_queue(netdev);

	/* fire a link status change पूर्णांकerrupt to start the watchकरोg */
	ew32(ICS, E1000_ICS_LSC);

	वापस E1000_SUCCESS;

err_req_irq:
	e1000_घातer_करोwn_phy(adapter);
	e1000_मुक्त_all_rx_resources(adapter);
err_setup_rx:
	e1000_मुक्त_all_tx_resources(adapter);
err_setup_tx:
	e1000_reset(adapter);

	वापस err;
पूर्ण

/**
 * e1000_बंद - Disables a network पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0, this is not allowed to fail
 *
 * The बंद entry poपूर्णांक is called when an पूर्णांकerface is de-activated
 * by the OS.  The hardware is still under the drivers control, but
 * needs to be disabled.  A global MAC reset is issued to stop the
 * hardware, and all transmit and receive resources are मुक्तd.
 **/
पूर्णांक e1000_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक count = E1000_CHECK_RESET_COUNT;

	जबतक (test_and_set_bit(__E1000_RESETTING, &adapter->flags) && count--)
		usleep_range(10000, 20000);

	WARN_ON(count < 0);

	/* संकेत that we're करोwn so that the reset task will no दीर्घer run */
	set_bit(__E1000_DOWN, &adapter->flags);
	clear_bit(__E1000_RESETTING, &adapter->flags);

	e1000_करोwn(adapter);
	e1000_घातer_करोwn_phy(adapter);
	e1000_मुक्त_irq(adapter);

	e1000_मुक्त_all_tx_resources(adapter);
	e1000_मुक्त_all_rx_resources(adapter);

	/* समाप्त manageability vlan ID अगर supported, but not अगर a vlan with
	 * the same ID is रेजिस्टरed on the host OS (let 8021q समाप्त it)
	 */
	अगर ((hw->mng_cookie.status &
	     E1000_MNG_DHCP_COOKIE_STATUS_VLAN_SUPPORT) &&
	    !test_bit(adapter->mng_vlan_id, adapter->active_vlans)) अणु
		e1000_vlan_rx_समाप्त_vid(netdev, htons(ETH_P_8021Q),
				       adapter->mng_vlan_id);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * e1000_check_64k_bound - check that memory करोesn't cross 64kB boundary
 * @adapter: address of board निजी काष्ठाure
 * @start: address of beginning of memory
 * @len: length of memory
 **/
अटल bool e1000_check_64k_bound(काष्ठा e1000_adapter *adapter, व्योम *start,
				  अचिन्हित दीर्घ len)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	अचिन्हित दीर्घ begin = (अचिन्हित दीर्घ)start;
	अचिन्हित दीर्घ end = begin + len;

	/* First rev 82545 and 82546 need to not allow any memory
	 * ग_लिखो location to cross 64k boundary due to errata 23
	 */
	अगर (hw->mac_type == e1000_82545 ||
	    hw->mac_type == e1000_ce4100 ||
	    hw->mac_type == e1000_82546) अणु
		वापस ((begin ^ (end - 1)) >> 16) == 0;
	पूर्ण

	वापस true;
पूर्ण

/**
 * e1000_setup_tx_resources - allocate Tx resources (Descriptors)
 * @adapter: board निजी काष्ठाure
 * @txdr:    tx descriptor ring (क्रम a specअगरic queue) to setup
 *
 * Return 0 on success, negative on failure
 **/
अटल पूर्णांक e1000_setup_tx_resources(काष्ठा e1000_adapter *adapter,
				    काष्ठा e1000_tx_ring *txdr)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक size;

	size = माप(काष्ठा e1000_tx_buffer) * txdr->count;
	txdr->buffer_info = vzalloc(size);
	अगर (!txdr->buffer_info)
		वापस -ENOMEM;

	/* round up to nearest 4K */

	txdr->size = txdr->count * माप(काष्ठा e1000_tx_desc);
	txdr->size = ALIGN(txdr->size, 4096);

	txdr->desc = dma_alloc_coherent(&pdev->dev, txdr->size, &txdr->dma,
					GFP_KERNEL);
	अगर (!txdr->desc) अणु
setup_tx_desc_die:
		vमुक्त(txdr->buffer_info);
		वापस -ENOMEM;
	पूर्ण

	/* Fix क्रम errata 23, can't cross 64kB boundary */
	अगर (!e1000_check_64k_bound(adapter, txdr->desc, txdr->size)) अणु
		व्योम *olddesc = txdr->desc;
		dma_addr_t olddma = txdr->dma;
		e_err(tx_err, "txdr align check failed: %u bytes at %p\n",
		      txdr->size, txdr->desc);
		/* Try again, without मुक्तing the previous */
		txdr->desc = dma_alloc_coherent(&pdev->dev, txdr->size,
						&txdr->dma, GFP_KERNEL);
		/* Failed allocation, critical failure */
		अगर (!txdr->desc) अणु
			dma_मुक्त_coherent(&pdev->dev, txdr->size, olddesc,
					  olddma);
			जाओ setup_tx_desc_die;
		पूर्ण

		अगर (!e1000_check_64k_bound(adapter, txdr->desc, txdr->size)) अणु
			/* give up */
			dma_मुक्त_coherent(&pdev->dev, txdr->size, txdr->desc,
					  txdr->dma);
			dma_मुक्त_coherent(&pdev->dev, txdr->size, olddesc,
					  olddma);
			e_err(probe, "Unable to allocate aligned memory "
			      "for the transmit descriptor ring\n");
			vमुक्त(txdr->buffer_info);
			वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			/* Free old allocation, new allocation was successful */
			dma_मुक्त_coherent(&pdev->dev, txdr->size, olddesc,
					  olddma);
		पूर्ण
	पूर्ण
	स_रखो(txdr->desc, 0, txdr->size);

	txdr->next_to_use = 0;
	txdr->next_to_clean = 0;

	वापस 0;
पूर्ण

/**
 * e1000_setup_all_tx_resources - wrapper to allocate Tx resources
 * 				  (Descriptors) क्रम all queues
 * @adapter: board निजी काष्ठाure
 *
 * Return 0 on success, negative on failure
 **/
पूर्णांक e1000_setup_all_tx_resources(काष्ठा e1000_adapter *adapter)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		err = e1000_setup_tx_resources(adapter, &adapter->tx_ring[i]);
		अगर (err) अणु
			e_err(probe, "Allocation for Tx Queue %u failed\n", i);
			क्रम (i-- ; i >= 0; i--)
				e1000_मुक्त_tx_resources(adapter,
							&adapter->tx_ring[i]);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/**
 * e1000_configure_tx - Configure 8254x Transmit Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Tx unit of the MAC after a reset.
 **/
अटल व्योम e1000_configure_tx(काष्ठा e1000_adapter *adapter)
अणु
	u64 tdba;
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 tdlen, tctl, tipg;
	u32 ipgr1, ipgr2;

	/* Setup the HW Tx Head and Tail descriptor poपूर्णांकers */

	चयन (adapter->num_tx_queues) अणु
	हाल 1:
	शेष:
		tdba = adapter->tx_ring[0].dma;
		tdlen = adapter->tx_ring[0].count *
			माप(काष्ठा e1000_tx_desc);
		ew32(TDLEN, tdlen);
		ew32(TDBAH, (tdba >> 32));
		ew32(TDBAL, (tdba & 0x00000000ffffffffULL));
		ew32(TDT, 0);
		ew32(TDH, 0);
		adapter->tx_ring[0].tdh = ((hw->mac_type >= e1000_82543) ?
					   E1000_TDH : E1000_82542_TDH);
		adapter->tx_ring[0].tdt = ((hw->mac_type >= e1000_82543) ?
					   E1000_TDT : E1000_82542_TDT);
		अवरोध;
	पूर्ण

	/* Set the शेष values क्रम the Tx Inter Packet Gap समयr */
	अगर ((hw->media_type == e1000_media_type_fiber ||
	     hw->media_type == e1000_media_type_पूर्णांकernal_serdes))
		tipg = DEFAULT_82543_TIPG_IPGT_FIBER;
	अन्यथा
		tipg = DEFAULT_82543_TIPG_IPGT_COPPER;

	चयन (hw->mac_type) अणु
	हाल e1000_82542_rev2_0:
	हाल e1000_82542_rev2_1:
		tipg = DEFAULT_82542_TIPG_IPGT;
		ipgr1 = DEFAULT_82542_TIPG_IPGR1;
		ipgr2 = DEFAULT_82542_TIPG_IPGR2;
		अवरोध;
	शेष:
		ipgr1 = DEFAULT_82543_TIPG_IPGR1;
		ipgr2 = DEFAULT_82543_TIPG_IPGR2;
		अवरोध;
	पूर्ण
	tipg |= ipgr1 << E1000_TIPG_IPGR1_SHIFT;
	tipg |= ipgr2 << E1000_TIPG_IPGR2_SHIFT;
	ew32(TIPG, tipg);

	/* Set the Tx Interrupt Delay रेजिस्टर */

	ew32(TIDV, adapter->tx_पूर्णांक_delay);
	अगर (hw->mac_type >= e1000_82540)
		ew32(TADV, adapter->tx_असल_पूर्णांक_delay);

	/* Program the Transmit Control Register */

	tctl = er32(TCTL);
	tctl &= ~E1000_TCTL_CT;
	tctl |= E1000_TCTL_PSP | E1000_TCTL_RTLC |
		(E1000_COLLISION_THRESHOLD << E1000_CT_SHIFT);

	e1000_config_collision_dist(hw);

	/* Setup Transmit Descriptor Settings क्रम eop descriptor */
	adapter->txd_cmd = E1000_TXD_CMD_EOP | E1000_TXD_CMD_IFCS;

	/* only set IDE अगर we are delaying पूर्णांकerrupts using the समयrs */
	अगर (adapter->tx_पूर्णांक_delay)
		adapter->txd_cmd |= E1000_TXD_CMD_IDE;

	अगर (hw->mac_type < e1000_82543)
		adapter->txd_cmd |= E1000_TXD_CMD_RPS;
	अन्यथा
		adapter->txd_cmd |= E1000_TXD_CMD_RS;

	/* Cache अगर we're 82544 running in PCI-X because we'll
	 * need this to apply a workaround later in the send path.
	 */
	अगर (hw->mac_type == e1000_82544 &&
	    hw->bus_type == e1000_bus_type_pcix)
		adapter->pcix_82544 = true;

	ew32(TCTL, tctl);

पूर्ण

/**
 * e1000_setup_rx_resources - allocate Rx resources (Descriptors)
 * @adapter: board निजी काष्ठाure
 * @rxdr:    rx descriptor ring (क्रम a specअगरic queue) to setup
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक e1000_setup_rx_resources(काष्ठा e1000_adapter *adapter,
				    काष्ठा e1000_rx_ring *rxdr)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक size, desc_len;

	size = माप(काष्ठा e1000_rx_buffer) * rxdr->count;
	rxdr->buffer_info = vzalloc(size);
	अगर (!rxdr->buffer_info)
		वापस -ENOMEM;

	desc_len = माप(काष्ठा e1000_rx_desc);

	/* Round up to nearest 4K */

	rxdr->size = rxdr->count * desc_len;
	rxdr->size = ALIGN(rxdr->size, 4096);

	rxdr->desc = dma_alloc_coherent(&pdev->dev, rxdr->size, &rxdr->dma,
					GFP_KERNEL);
	अगर (!rxdr->desc) अणु
setup_rx_desc_die:
		vमुक्त(rxdr->buffer_info);
		वापस -ENOMEM;
	पूर्ण

	/* Fix क्रम errata 23, can't cross 64kB boundary */
	अगर (!e1000_check_64k_bound(adapter, rxdr->desc, rxdr->size)) अणु
		व्योम *olddesc = rxdr->desc;
		dma_addr_t olddma = rxdr->dma;
		e_err(rx_err, "rxdr align check failed: %u bytes at %p\n",
		      rxdr->size, rxdr->desc);
		/* Try again, without मुक्तing the previous */
		rxdr->desc = dma_alloc_coherent(&pdev->dev, rxdr->size,
						&rxdr->dma, GFP_KERNEL);
		/* Failed allocation, critical failure */
		अगर (!rxdr->desc) अणु
			dma_मुक्त_coherent(&pdev->dev, rxdr->size, olddesc,
					  olddma);
			जाओ setup_rx_desc_die;
		पूर्ण

		अगर (!e1000_check_64k_bound(adapter, rxdr->desc, rxdr->size)) अणु
			/* give up */
			dma_मुक्त_coherent(&pdev->dev, rxdr->size, rxdr->desc,
					  rxdr->dma);
			dma_मुक्त_coherent(&pdev->dev, rxdr->size, olddesc,
					  olddma);
			e_err(probe, "Unable to allocate aligned memory for "
			      "the Rx descriptor ring\n");
			जाओ setup_rx_desc_die;
		पूर्ण अन्यथा अणु
			/* Free old allocation, new allocation was successful */
			dma_मुक्त_coherent(&pdev->dev, rxdr->size, olddesc,
					  olddma);
		पूर्ण
	पूर्ण
	स_रखो(rxdr->desc, 0, rxdr->size);

	rxdr->next_to_clean = 0;
	rxdr->next_to_use = 0;
	rxdr->rx_skb_top = शून्य;

	वापस 0;
पूर्ण

/**
 * e1000_setup_all_rx_resources - wrapper to allocate Rx resources
 * 				  (Descriptors) क्रम all queues
 * @adapter: board निजी काष्ठाure
 *
 * Return 0 on success, negative on failure
 **/
पूर्णांक e1000_setup_all_rx_resources(काष्ठा e1000_adapter *adapter)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		err = e1000_setup_rx_resources(adapter, &adapter->rx_ring[i]);
		अगर (err) अणु
			e_err(probe, "Allocation for Rx Queue %u failed\n", i);
			क्रम (i-- ; i >= 0; i--)
				e1000_मुक्त_rx_resources(adapter,
							&adapter->rx_ring[i]);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/**
 * e1000_setup_rctl - configure the receive control रेजिस्टरs
 * @adapter: Board निजी काष्ठाure
 **/
अटल व्योम e1000_setup_rctl(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rctl;

	rctl = er32(RCTL);

	rctl &= ~(3 << E1000_RCTL_MO_SHIFT);

	rctl |= E1000_RCTL_BAM | E1000_RCTL_LBM_NO |
		E1000_RCTL_RDMTS_HALF |
		(hw->mc_filter_type << E1000_RCTL_MO_SHIFT);

	अगर (hw->tbi_compatibility_on == 1)
		rctl |= E1000_RCTL_SBP;
	अन्यथा
		rctl &= ~E1000_RCTL_SBP;

	अगर (adapter->netdev->mtu <= ETH_DATA_LEN)
		rctl &= ~E1000_RCTL_LPE;
	अन्यथा
		rctl |= E1000_RCTL_LPE;

	/* Setup buffer sizes */
	rctl &= ~E1000_RCTL_SZ_4096;
	rctl |= E1000_RCTL_BSEX;
	चयन (adapter->rx_buffer_len) अणु
	हाल E1000_RXBUFFER_2048:
	शेष:
		rctl |= E1000_RCTL_SZ_2048;
		rctl &= ~E1000_RCTL_BSEX;
		अवरोध;
	हाल E1000_RXBUFFER_4096:
		rctl |= E1000_RCTL_SZ_4096;
		अवरोध;
	हाल E1000_RXBUFFER_8192:
		rctl |= E1000_RCTL_SZ_8192;
		अवरोध;
	हाल E1000_RXBUFFER_16384:
		rctl |= E1000_RCTL_SZ_16384;
		अवरोध;
	पूर्ण

	/* This is useful क्रम snअगरfing bad packets. */
	अगर (adapter->netdev->features & NETIF_F_RXALL) अणु
		/* UPE and MPE will be handled by normal PROMISC logic
		 * in e1000e_set_rx_mode
		 */
		rctl |= (E1000_RCTL_SBP | /* Receive bad packets */
			 E1000_RCTL_BAM | /* RX All Bcast Pkts */
			 E1000_RCTL_PMCF); /* RX All MAC Ctrl Pkts */

		rctl &= ~(E1000_RCTL_VFE | /* Disable VLAN filter */
			  E1000_RCTL_DPF | /* Allow filtered छोड़ो */
			  E1000_RCTL_CFIEN); /* Dis VLAN CFIEN Filter */
		/* Do not mess with E1000_CTRL_VME, it affects transmit as well,
		 * and that अवरोधs VLANs.
		 */
	पूर्ण

	ew32(RCTL, rctl);
पूर्ण

/**
 * e1000_configure_rx - Configure 8254x Receive Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Rx unit of the MAC after a reset.
 **/
अटल व्योम e1000_configure_rx(काष्ठा e1000_adapter *adapter)
अणु
	u64 rdba;
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rdlen, rctl, rxcsum;

	अगर (adapter->netdev->mtu > ETH_DATA_LEN) अणु
		rdlen = adapter->rx_ring[0].count *
			माप(काष्ठा e1000_rx_desc);
		adapter->clean_rx = e1000_clean_jumbo_rx_irq;
		adapter->alloc_rx_buf = e1000_alloc_jumbo_rx_buffers;
	पूर्ण अन्यथा अणु
		rdlen = adapter->rx_ring[0].count *
			माप(काष्ठा e1000_rx_desc);
		adapter->clean_rx = e1000_clean_rx_irq;
		adapter->alloc_rx_buf = e1000_alloc_rx_buffers;
	पूर्ण

	/* disable receives जबतक setting up the descriptors */
	rctl = er32(RCTL);
	ew32(RCTL, rctl & ~E1000_RCTL_EN);

	/* set the Receive Delay Timer Register */
	ew32(RDTR, adapter->rx_पूर्णांक_delay);

	अगर (hw->mac_type >= e1000_82540) अणु
		ew32(RADV, adapter->rx_असल_पूर्णांक_delay);
		अगर (adapter->itr_setting != 0)
			ew32(ITR, 1000000000 / (adapter->itr * 256));
	पूर्ण

	/* Setup the HW Rx Head and Tail Descriptor Poपूर्णांकers and
	 * the Base and Length of the Rx Descriptor Ring
	 */
	चयन (adapter->num_rx_queues) अणु
	हाल 1:
	शेष:
		rdba = adapter->rx_ring[0].dma;
		ew32(RDLEN, rdlen);
		ew32(RDBAH, (rdba >> 32));
		ew32(RDBAL, (rdba & 0x00000000ffffffffULL));
		ew32(RDT, 0);
		ew32(RDH, 0);
		adapter->rx_ring[0].rdh = ((hw->mac_type >= e1000_82543) ?
					   E1000_RDH : E1000_82542_RDH);
		adapter->rx_ring[0].rdt = ((hw->mac_type >= e1000_82543) ?
					   E1000_RDT : E1000_82542_RDT);
		अवरोध;
	पूर्ण

	/* Enable 82543 Receive Checksum Offload क्रम TCP and UDP */
	अगर (hw->mac_type >= e1000_82543) अणु
		rxcsum = er32(RXCSUM);
		अगर (adapter->rx_csum)
			rxcsum |= E1000_RXCSUM_TUOFL;
		अन्यथा
			/* करोn't need to clear IPPCSE as it शेषs to 0 */
			rxcsum &= ~E1000_RXCSUM_TUOFL;
		ew32(RXCSUM, rxcsum);
	पूर्ण

	/* Enable Receives */
	ew32(RCTL, rctl | E1000_RCTL_EN);
पूर्ण

/**
 * e1000_मुक्त_tx_resources - Free Tx Resources per Queue
 * @adapter: board निजी काष्ठाure
 * @tx_ring: Tx descriptor ring क्रम a specअगरic queue
 *
 * Free all transmit software resources
 **/
अटल व्योम e1000_मुक्त_tx_resources(काष्ठा e1000_adapter *adapter,
				    काष्ठा e1000_tx_ring *tx_ring)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;

	e1000_clean_tx_ring(adapter, tx_ring);

	vमुक्त(tx_ring->buffer_info);
	tx_ring->buffer_info = शून्य;

	dma_मुक्त_coherent(&pdev->dev, tx_ring->size, tx_ring->desc,
			  tx_ring->dma);

	tx_ring->desc = शून्य;
पूर्ण

/**
 * e1000_मुक्त_all_tx_resources - Free Tx Resources क्रम All Queues
 * @adapter: board निजी काष्ठाure
 *
 * Free all transmit software resources
 **/
व्योम e1000_मुक्त_all_tx_resources(काष्ठा e1000_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		e1000_मुक्त_tx_resources(adapter, &adapter->tx_ring[i]);
पूर्ण

अटल व्योम
e1000_unmap_and_मुक्त_tx_resource(काष्ठा e1000_adapter *adapter,
				 काष्ठा e1000_tx_buffer *buffer_info)
अणु
	अगर (buffer_info->dma) अणु
		अगर (buffer_info->mapped_as_page)
			dma_unmap_page(&adapter->pdev->dev, buffer_info->dma,
				       buffer_info->length, DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_single(&adapter->pdev->dev, buffer_info->dma,
					 buffer_info->length,
					 DMA_TO_DEVICE);
		buffer_info->dma = 0;
	पूर्ण
	अगर (buffer_info->skb) अणु
		dev_kमुक्त_skb_any(buffer_info->skb);
		buffer_info->skb = शून्य;
	पूर्ण
	buffer_info->समय_stamp = 0;
	/* buffer_info must be completely set up in the transmit path */
पूर्ण

/**
 * e1000_clean_tx_ring - Free Tx Buffers
 * @adapter: board निजी काष्ठाure
 * @tx_ring: ring to be cleaned
 **/
अटल व्योम e1000_clean_tx_ring(काष्ठा e1000_adapter *adapter,
				काष्ठा e1000_tx_ring *tx_ring)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_tx_buffer *buffer_info;
	अचिन्हित दीर्घ size;
	अचिन्हित पूर्णांक i;

	/* Free all the Tx ring sk_buffs */

	क्रम (i = 0; i < tx_ring->count; i++) अणु
		buffer_info = &tx_ring->buffer_info[i];
		e1000_unmap_and_मुक्त_tx_resource(adapter, buffer_info);
	पूर्ण

	netdev_reset_queue(adapter->netdev);
	size = माप(काष्ठा e1000_tx_buffer) * tx_ring->count;
	स_रखो(tx_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */

	स_रखो(tx_ring->desc, 0, tx_ring->size);

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
	tx_ring->last_tx_tso = false;

	ग_लिखोl(0, hw->hw_addr + tx_ring->tdh);
	ग_लिखोl(0, hw->hw_addr + tx_ring->tdt);
पूर्ण

/**
 * e1000_clean_all_tx_rings - Free Tx Buffers क्रम all queues
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम e1000_clean_all_tx_rings(काष्ठा e1000_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		e1000_clean_tx_ring(adapter, &adapter->tx_ring[i]);
पूर्ण

/**
 * e1000_मुक्त_rx_resources - Free Rx Resources
 * @adapter: board निजी काष्ठाure
 * @rx_ring: ring to clean the resources from
 *
 * Free all receive software resources
 **/
अटल व्योम e1000_मुक्त_rx_resources(काष्ठा e1000_adapter *adapter,
				    काष्ठा e1000_rx_ring *rx_ring)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;

	e1000_clean_rx_ring(adapter, rx_ring);

	vमुक्त(rx_ring->buffer_info);
	rx_ring->buffer_info = शून्य;

	dma_मुक्त_coherent(&pdev->dev, rx_ring->size, rx_ring->desc,
			  rx_ring->dma);

	rx_ring->desc = शून्य;
पूर्ण

/**
 * e1000_मुक्त_all_rx_resources - Free Rx Resources क्रम All Queues
 * @adapter: board निजी काष्ठाure
 *
 * Free all receive software resources
 **/
व्योम e1000_मुक्त_all_rx_resources(काष्ठा e1000_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		e1000_मुक्त_rx_resources(adapter, &adapter->rx_ring[i]);
पूर्ण

#घोषणा E1000_HEADROOM (NET_SKB_PAD + NET_IP_ALIGN)
अटल अचिन्हित पूर्णांक e1000_frag_len(स्थिर काष्ठा e1000_adapter *a)
अणु
	वापस SKB_DATA_ALIGN(a->rx_buffer_len + E1000_HEADROOM) +
		SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
पूर्ण

अटल व्योम *e1000_alloc_frag(स्थिर काष्ठा e1000_adapter *a)
अणु
	अचिन्हित पूर्णांक len = e1000_frag_len(a);
	u8 *data = netdev_alloc_frag(len);

	अगर (likely(data))
		data += E1000_HEADROOM;
	वापस data;
पूर्ण

/**
 * e1000_clean_rx_ring - Free Rx Buffers per Queue
 * @adapter: board निजी काष्ठाure
 * @rx_ring: ring to मुक्त buffers from
 **/
अटल व्योम e1000_clean_rx_ring(काष्ठा e1000_adapter *adapter,
				काष्ठा e1000_rx_ring *rx_ring)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_rx_buffer *buffer_info;
	काष्ठा pci_dev *pdev = adapter->pdev;
	अचिन्हित दीर्घ size;
	अचिन्हित पूर्णांक i;

	/* Free all the Rx netfrags */
	क्रम (i = 0; i < rx_ring->count; i++) अणु
		buffer_info = &rx_ring->buffer_info[i];
		अगर (adapter->clean_rx == e1000_clean_rx_irq) अणु
			अगर (buffer_info->dma)
				dma_unmap_single(&pdev->dev, buffer_info->dma,
						 adapter->rx_buffer_len,
						 DMA_FROM_DEVICE);
			अगर (buffer_info->rxbuf.data) अणु
				skb_मुक्त_frag(buffer_info->rxbuf.data);
				buffer_info->rxbuf.data = शून्य;
			पूर्ण
		पूर्ण अन्यथा अगर (adapter->clean_rx == e1000_clean_jumbo_rx_irq) अणु
			अगर (buffer_info->dma)
				dma_unmap_page(&pdev->dev, buffer_info->dma,
					       adapter->rx_buffer_len,
					       DMA_FROM_DEVICE);
			अगर (buffer_info->rxbuf.page) अणु
				put_page(buffer_info->rxbuf.page);
				buffer_info->rxbuf.page = शून्य;
			पूर्ण
		पूर्ण

		buffer_info->dma = 0;
	पूर्ण

	/* there also may be some cached data from a chained receive */
	napi_मुक्त_frags(&adapter->napi);
	rx_ring->rx_skb_top = शून्य;

	size = माप(काष्ठा e1000_rx_buffer) * rx_ring->count;
	स_रखो(rx_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */
	स_रखो(rx_ring->desc, 0, rx_ring->size);

	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;

	ग_लिखोl(0, hw->hw_addr + rx_ring->rdh);
	ग_लिखोl(0, hw->hw_addr + rx_ring->rdt);
पूर्ण

/**
 * e1000_clean_all_rx_rings - Free Rx Buffers क्रम all queues
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम e1000_clean_all_rx_rings(काष्ठा e1000_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		e1000_clean_rx_ring(adapter, &adapter->rx_ring[i]);
पूर्ण

/* The 82542 2.0 (revision 2) needs to have the receive unit in reset
 * and memory ग_लिखो and invalidate disabled क्रम certain operations
 */
अटल व्योम e1000_enter_82542_rst(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	u32 rctl;

	e1000_pci_clear_mwi(hw);

	rctl = er32(RCTL);
	rctl |= E1000_RCTL_RST;
	ew32(RCTL, rctl);
	E1000_WRITE_FLUSH();
	mdelay(5);

	अगर (netअगर_running(netdev))
		e1000_clean_all_rx_rings(adapter);
पूर्ण

अटल व्योम e1000_leave_82542_rst(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	u32 rctl;

	rctl = er32(RCTL);
	rctl &= ~E1000_RCTL_RST;
	ew32(RCTL, rctl);
	E1000_WRITE_FLUSH();
	mdelay(5);

	अगर (hw->pci_cmd_word & PCI_COMMAND_INVALIDATE)
		e1000_pci_set_mwi(hw);

	अगर (netअगर_running(netdev)) अणु
		/* No need to loop, because 82542 supports only 1 queue */
		काष्ठा e1000_rx_ring *ring = &adapter->rx_ring[0];
		e1000_configure_rx(adapter);
		adapter->alloc_rx_buf(adapter, ring, E1000_DESC_UNUSED(ring));
	पूर्ण
पूर्ण

/**
 * e1000_set_mac - Change the Ethernet Address of the NIC
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @p: poपूर्णांकer to an address काष्ठाure
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक e1000_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	/* 82542 2.0 needs to be in reset to ग_लिखो receive address रेजिस्टरs */

	अगर (hw->mac_type == e1000_82542_rev2_0)
		e1000_enter_82542_rst(adapter);

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	स_नकल(hw->mac_addr, addr->sa_data, netdev->addr_len);

	e1000_rar_set(hw, hw->mac_addr, 0);

	अगर (hw->mac_type == e1000_82542_rev2_0)
		e1000_leave_82542_rst(adapter);

	वापस 0;
पूर्ण

/**
 * e1000_set_rx_mode - Secondary Unicast, Multicast and Promiscuous mode set
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * The set_rx_mode entry poपूर्णांक is called whenever the unicast or multicast
 * address lists or the network पूर्णांकerface flags are updated. This routine is
 * responsible क्रम configuring the hardware क्रम proper unicast, multicast,
 * promiscuous mode, and all-multi behavior.
 **/
अटल व्योम e1000_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा netdev_hw_addr *ha;
	bool use_uc = false;
	u32 rctl;
	u32 hash_value;
	पूर्णांक i, rar_entries = E1000_RAR_ENTRIES;
	पूर्णांक mta_reg_count = E1000_NUM_MTA_REGISTERS;
	u32 *mcarray = kसुस्मृति(mta_reg_count, माप(u32), GFP_ATOMIC);

	अगर (!mcarray)
		वापस;

	/* Check क्रम Promiscuous and All Multicast modes */

	rctl = er32(RCTL);

	अगर (netdev->flags & IFF_PROMISC) अणु
		rctl |= (E1000_RCTL_UPE | E1000_RCTL_MPE);
		rctl &= ~E1000_RCTL_VFE;
	पूर्ण अन्यथा अणु
		अगर (netdev->flags & IFF_ALLMULTI)
			rctl |= E1000_RCTL_MPE;
		अन्यथा
			rctl &= ~E1000_RCTL_MPE;
		/* Enable VLAN filter अगर there is a VLAN */
		अगर (e1000_vlan_used(adapter))
			rctl |= E1000_RCTL_VFE;
	पूर्ण

	अगर (netdev_uc_count(netdev) > rar_entries - 1) अणु
		rctl |= E1000_RCTL_UPE;
	पूर्ण अन्यथा अगर (!(netdev->flags & IFF_PROMISC)) अणु
		rctl &= ~E1000_RCTL_UPE;
		use_uc = true;
	पूर्ण

	ew32(RCTL, rctl);

	/* 82542 2.0 needs to be in reset to ग_लिखो receive address रेजिस्टरs */

	अगर (hw->mac_type == e1000_82542_rev2_0)
		e1000_enter_82542_rst(adapter);

	/* load the first 14 addresses पूर्णांकo the exact filters 1-14. Unicast
	 * addresses take precedence to aव्योम disabling unicast filtering
	 * when possible.
	 *
	 * RAR 0 is used क्रम the station MAC address
	 * अगर there are not 14 addresses, go ahead and clear the filters
	 */
	i = 1;
	अगर (use_uc)
		netdev_क्रम_each_uc_addr(ha, netdev) अणु
			अगर (i == rar_entries)
				अवरोध;
			e1000_rar_set(hw, ha->addr, i++);
		पूर्ण

	netdev_क्रम_each_mc_addr(ha, netdev) अणु
		अगर (i == rar_entries) अणु
			/* load any reमुख्यing addresses पूर्णांकo the hash table */
			u32 hash_reg, hash_bit, mta;
			hash_value = e1000_hash_mc_addr(hw, ha->addr);
			hash_reg = (hash_value >> 5) & 0x7F;
			hash_bit = hash_value & 0x1F;
			mta = (1 << hash_bit);
			mcarray[hash_reg] |= mta;
		पूर्ण अन्यथा अणु
			e1000_rar_set(hw, ha->addr, i++);
		पूर्ण
	पूर्ण

	क्रम (; i < rar_entries; i++) अणु
		E1000_WRITE_REG_ARRAY(hw, RA, i << 1, 0);
		E1000_WRITE_FLUSH();
		E1000_WRITE_REG_ARRAY(hw, RA, (i << 1) + 1, 0);
		E1000_WRITE_FLUSH();
	पूर्ण

	/* ग_लिखो the hash table completely, ग_लिखो from bottom to aव्योम
	 * both stupid ग_लिखो combining chipsets, and flushing each ग_लिखो
	 */
	क्रम (i = mta_reg_count - 1; i >= 0 ; i--) अणु
		/* If we are on an 82544 has an errata where writing odd
		 * offsets overग_लिखोs the previous even offset, but writing
		 * backwards over the range solves the issue by always
		 * writing the odd offset first
		 */
		E1000_WRITE_REG_ARRAY(hw, MTA, i, mcarray[i]);
	पूर्ण
	E1000_WRITE_FLUSH();

	अगर (hw->mac_type == e1000_82542_rev2_0)
		e1000_leave_82542_rst(adapter);

	kमुक्त(mcarray);
पूर्ण

/**
 * e1000_update_phy_info_task - get phy info
 * @work: work काष्ठा contained inside adapter काष्ठा
 *
 * Need to रुको a few seconds after link up to get diagnostic inक्रमmation from
 * the phy
 */
अटल व्योम e1000_update_phy_info_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा e1000_adapter *adapter = container_of(work,
						     काष्ठा e1000_adapter,
						     phy_info_task.work);

	e1000_phy_get_info(&adapter->hw, &adapter->phy_info);
पूर्ण

/**
 * e1000_82547_tx_fअगरo_stall_task - task to complete work
 * @work: work काष्ठा contained inside adapter काष्ठा
 **/
अटल व्योम e1000_82547_tx_fअगरo_stall_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा e1000_adapter *adapter = container_of(work,
						     काष्ठा e1000_adapter,
						     fअगरo_stall_task.work);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	u32 tctl;

	अगर (atomic_पढ़ो(&adapter->tx_fअगरo_stall)) अणु
		अगर ((er32(TDT) == er32(TDH)) &&
		   (er32(TDFT) == er32(TDFH)) &&
		   (er32(TDFTS) == er32(TDFHS))) अणु
			tctl = er32(TCTL);
			ew32(TCTL, tctl & ~E1000_TCTL_EN);
			ew32(TDFT, adapter->tx_head_addr);
			ew32(TDFH, adapter->tx_head_addr);
			ew32(TDFTS, adapter->tx_head_addr);
			ew32(TDFHS, adapter->tx_head_addr);
			ew32(TCTL, tctl);
			E1000_WRITE_FLUSH();

			adapter->tx_fअगरo_head = 0;
			atomic_set(&adapter->tx_fअगरo_stall, 0);
			netअगर_wake_queue(netdev);
		पूर्ण अन्यथा अगर (!test_bit(__E1000_DOWN, &adapter->flags)) अणु
			schedule_delayed_work(&adapter->fअगरo_stall_task, 1);
		पूर्ण
	पूर्ण
पूर्ण

bool e1000_has_link(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	bool link_active = false;

	/* get_link_status is set on LSC (link status) पूर्णांकerrupt or rx
	 * sequence error पूर्णांकerrupt (except on पूर्णांकel ce4100).
	 * get_link_status will stay false until the
	 * e1000_check_क्रम_link establishes link क्रम copper adapters
	 * ONLY
	 */
	चयन (hw->media_type) अणु
	हाल e1000_media_type_copper:
		अगर (hw->mac_type == e1000_ce4100)
			hw->get_link_status = 1;
		अगर (hw->get_link_status) अणु
			e1000_check_क्रम_link(hw);
			link_active = !hw->get_link_status;
		पूर्ण अन्यथा अणु
			link_active = true;
		पूर्ण
		अवरोध;
	हाल e1000_media_type_fiber:
		e1000_check_क्रम_link(hw);
		link_active = !!(er32(STATUS) & E1000_STATUS_LU);
		अवरोध;
	हाल e1000_media_type_पूर्णांकernal_serdes:
		e1000_check_क्रम_link(hw);
		link_active = hw->serdes_has_link;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस link_active;
पूर्ण

/**
 * e1000_watchकरोg - work function
 * @work: work काष्ठा contained inside adapter काष्ठा
 **/
अटल व्योम e1000_watchकरोg(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा e1000_adapter *adapter = container_of(work,
						     काष्ठा e1000_adapter,
						     watchकरोg_task.work);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_tx_ring *txdr = adapter->tx_ring;
	u32 link, tctl;

	link = e1000_has_link(adapter);
	अगर ((netअगर_carrier_ok(netdev)) && link)
		जाओ link_up;

	अगर (link) अणु
		अगर (!netअगर_carrier_ok(netdev)) अणु
			u32 ctrl;
			/* update snapshot of PHY रेजिस्टरs on LSC */
			e1000_get_speed_and_duplex(hw,
						   &adapter->link_speed,
						   &adapter->link_duplex);

			ctrl = er32(CTRL);
			pr_info("%s NIC Link is Up %d Mbps %s, "
				"Flow Control: %s\n",
				netdev->name,
				adapter->link_speed,
				adapter->link_duplex == FULL_DUPLEX ?
				"Full Duplex" : "Half Duplex",
				((ctrl & E1000_CTRL_TFCE) && (ctrl &
				E1000_CTRL_RFCE)) ? "RX/TX" : ((ctrl &
				E1000_CTRL_RFCE) ? "RX" : ((ctrl &
				E1000_CTRL_TFCE) ? "TX" : "None")));

			/* adjust समयout factor according to speed/duplex */
			adapter->tx_समयout_factor = 1;
			चयन (adapter->link_speed) अणु
			हाल SPEED_10:
				adapter->tx_समयout_factor = 16;
				अवरोध;
			हाल SPEED_100:
				/* maybe add some समयout factor ? */
				अवरोध;
			पूर्ण

			/* enable transmits in the hardware */
			tctl = er32(TCTL);
			tctl |= E1000_TCTL_EN;
			ew32(TCTL, tctl);

			netअगर_carrier_on(netdev);
			अगर (!test_bit(__E1000_DOWN, &adapter->flags))
				schedule_delayed_work(&adapter->phy_info_task,
						      2 * HZ);
			adapter->smartspeed = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (netअगर_carrier_ok(netdev)) अणु
			adapter->link_speed = 0;
			adapter->link_duplex = 0;
			pr_info("%s NIC Link is Down\n",
				netdev->name);
			netअगर_carrier_off(netdev);

			अगर (!test_bit(__E1000_DOWN, &adapter->flags))
				schedule_delayed_work(&adapter->phy_info_task,
						      2 * HZ);
		पूर्ण

		e1000_smartspeed(adapter);
	पूर्ण

link_up:
	e1000_update_stats(adapter);

	hw->tx_packet_delta = adapter->stats.tpt - adapter->tpt_old;
	adapter->tpt_old = adapter->stats.tpt;
	hw->collision_delta = adapter->stats.colc - adapter->colc_old;
	adapter->colc_old = adapter->stats.colc;

	adapter->gorcl = adapter->stats.gorcl - adapter->gorcl_old;
	adapter->gorcl_old = adapter->stats.gorcl;
	adapter->gotcl = adapter->stats.gotcl - adapter->gotcl_old;
	adapter->gotcl_old = adapter->stats.gotcl;

	e1000_update_adaptive(hw);

	अगर (!netअगर_carrier_ok(netdev)) अणु
		अगर (E1000_DESC_UNUSED(txdr) + 1 < txdr->count) अणु
			/* We've lost link, so the controller stops DMA,
			 * but we've got queued Tx work that's never going
			 * to get करोne, so reset controller to flush Tx.
			 * (Do the reset outside of पूर्णांकerrupt context).
			 */
			adapter->tx_समयout_count++;
			schedule_work(&adapter->reset_task);
			/* निकास immediately since reset is imminent */
			वापस;
		पूर्ण
	पूर्ण

	/* Simple mode क्रम Interrupt Throttle Rate (ITR) */
	अगर (hw->mac_type >= e1000_82540 && adapter->itr_setting == 4) अणु
		/* Symmetric Tx/Rx माला_लो a reduced ITR=2000;
		 * Total asymmetrical Tx or Rx माला_लो ITR=8000;
		 * everyone अन्यथा is between 2000-8000.
		 */
		u32 goc = (adapter->gotcl + adapter->gorcl) / 10000;
		u32 dअगर = (adapter->gotcl > adapter->gorcl ?
			    adapter->gotcl - adapter->gorcl :
			    adapter->gorcl - adapter->gotcl) / 10000;
		u32 itr = goc > 0 ? (dअगर * 6000 / goc + 2000) : 8000;

		ew32(ITR, 1000000000 / (itr * 256));
	पूर्ण

	/* Cause software पूर्णांकerrupt to ensure rx ring is cleaned */
	ew32(ICS, E1000_ICS_RXDMT0);

	/* Force detection of hung controller every watchकरोg period */
	adapter->detect_tx_hung = true;

	/* Reschedule the task */
	अगर (!test_bit(__E1000_DOWN, &adapter->flags))
		schedule_delayed_work(&adapter->watchकरोg_task, 2 * HZ);
पूर्ण

क्रमागत latency_range अणु
	lowest_latency = 0,
	low_latency = 1,
	bulk_latency = 2,
	latency_invalid = 255
पूर्ण;

/**
 * e1000_update_itr - update the dynamic ITR value based on statistics
 * @adapter: poपूर्णांकer to adapter
 * @itr_setting: current adapter->itr
 * @packets: the number of packets during this measurement पूर्णांकerval
 * @bytes: the number of bytes during this measurement पूर्णांकerval
 *
 *      Stores a new ITR value based on packets and byte
 *      counts during the last पूर्णांकerrupt.  The advantage of per पूर्णांकerrupt
 *      computation is faster updates and more accurate ITR क्रम the current
 *      traffic pattern.  Constants in this function were computed
 *      based on theoretical maximum wire speed and thresholds were set based
 *      on testing data as well as attempting to minimize response समय
 *      जबतक increasing bulk throughput.
 *      this functionality is controlled by the InterruptThrottleRate module
 *      parameter (see e1000_param.c)
 **/
अटल अचिन्हित पूर्णांक e1000_update_itr(काष्ठा e1000_adapter *adapter,
				     u16 itr_setting, पूर्णांक packets, पूर्णांक bytes)
अणु
	अचिन्हित पूर्णांक retval = itr_setting;
	काष्ठा e1000_hw *hw = &adapter->hw;

	अगर (unlikely(hw->mac_type < e1000_82540))
		जाओ update_itr_करोne;

	अगर (packets == 0)
		जाओ update_itr_करोne;

	चयन (itr_setting) अणु
	हाल lowest_latency:
		/* jumbo frames get bulk treaपंचांगent*/
		अगर (bytes/packets > 8000)
			retval = bulk_latency;
		अन्यथा अगर ((packets < 5) && (bytes > 512))
			retval = low_latency;
		अवरोध;
	हाल low_latency:  /* 50 usec aka 20000 पूर्णांकs/s */
		अगर (bytes > 10000) अणु
			/* jumbo frames need bulk latency setting */
			अगर (bytes/packets > 8000)
				retval = bulk_latency;
			अन्यथा अगर ((packets < 10) || ((bytes/packets) > 1200))
				retval = bulk_latency;
			अन्यथा अगर ((packets > 35))
				retval = lowest_latency;
		पूर्ण अन्यथा अगर (bytes/packets > 2000)
			retval = bulk_latency;
		अन्यथा अगर (packets <= 2 && bytes < 512)
			retval = lowest_latency;
		अवरोध;
	हाल bulk_latency: /* 250 usec aka 4000 पूर्णांकs/s */
		अगर (bytes > 25000) अणु
			अगर (packets > 35)
				retval = low_latency;
		पूर्ण अन्यथा अगर (bytes < 6000) अणु
			retval = low_latency;
		पूर्ण
		अवरोध;
	पूर्ण

update_itr_करोne:
	वापस retval;
पूर्ण

अटल व्योम e1000_set_itr(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 current_itr;
	u32 new_itr = adapter->itr;

	अगर (unlikely(hw->mac_type < e1000_82540))
		वापस;

	/* क्रम non-gigabit speeds, just fix the पूर्णांकerrupt rate at 4000 */
	अगर (unlikely(adapter->link_speed != SPEED_1000)) अणु
		new_itr = 4000;
		जाओ set_itr_now;
	पूर्ण

	adapter->tx_itr = e1000_update_itr(adapter, adapter->tx_itr,
					   adapter->total_tx_packets,
					   adapter->total_tx_bytes);
	/* conservative mode (itr 3) eliminates the lowest_latency setting */
	अगर (adapter->itr_setting == 3 && adapter->tx_itr == lowest_latency)
		adapter->tx_itr = low_latency;

	adapter->rx_itr = e1000_update_itr(adapter, adapter->rx_itr,
					   adapter->total_rx_packets,
					   adapter->total_rx_bytes);
	/* conservative mode (itr 3) eliminates the lowest_latency setting */
	अगर (adapter->itr_setting == 3 && adapter->rx_itr == lowest_latency)
		adapter->rx_itr = low_latency;

	current_itr = max(adapter->rx_itr, adapter->tx_itr);

	चयन (current_itr) अणु
	/* counts and packets in update_itr are dependent on these numbers */
	हाल lowest_latency:
		new_itr = 70000;
		अवरोध;
	हाल low_latency:
		new_itr = 20000; /* aka hwitr = ~200 */
		अवरोध;
	हाल bulk_latency:
		new_itr = 4000;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

set_itr_now:
	अगर (new_itr != adapter->itr) अणु
		/* this attempts to bias the पूर्णांकerrupt rate towards Bulk
		 * by adding पूर्णांकermediate steps when पूर्णांकerrupt rate is
		 * increasing
		 */
		new_itr = new_itr > adapter->itr ?
			  min(adapter->itr + (new_itr >> 2), new_itr) :
			  new_itr;
		adapter->itr = new_itr;
		ew32(ITR, 1000000000 / (new_itr * 256));
	पूर्ण
पूर्ण

#घोषणा E1000_TX_FLAGS_CSUM		0x00000001
#घोषणा E1000_TX_FLAGS_VLAN		0x00000002
#घोषणा E1000_TX_FLAGS_TSO		0x00000004
#घोषणा E1000_TX_FLAGS_IPV4		0x00000008
#घोषणा E1000_TX_FLAGS_NO_FCS		0x00000010
#घोषणा E1000_TX_FLAGS_VLAN_MASK	0xffff0000
#घोषणा E1000_TX_FLAGS_VLAN_SHIFT	16

अटल पूर्णांक e1000_tso(काष्ठा e1000_adapter *adapter,
		     काष्ठा e1000_tx_ring *tx_ring, काष्ठा sk_buff *skb,
		     __be16 protocol)
अणु
	काष्ठा e1000_context_desc *context_desc;
	काष्ठा e1000_tx_buffer *buffer_info;
	अचिन्हित पूर्णांक i;
	u32 cmd_length = 0;
	u16 ipcse = 0, tucse, mss;
	u8 ipcss, ipcso, tucss, tucso, hdr_len;

	अगर (skb_is_gso(skb)) अणु
		पूर्णांक err;

		err = skb_cow_head(skb, 0);
		अगर (err < 0)
			वापस err;

		hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
		mss = skb_shinfo(skb)->gso_size;
		अगर (protocol == htons(ETH_P_IP)) अणु
			काष्ठा iphdr *iph = ip_hdr(skb);
			iph->tot_len = 0;
			iph->check = 0;
			tcp_hdr(skb)->check = ~csum_tcpudp_magic(iph->saddr,
								 iph->daddr, 0,
								 IPPROTO_TCP,
								 0);
			cmd_length = E1000_TXD_CMD_IP;
			ipcse = skb_transport_offset(skb) - 1;
		पूर्ण अन्यथा अगर (skb_is_gso_v6(skb)) अणु
			tcp_v6_gso_csum_prep(skb);
			ipcse = 0;
		पूर्ण
		ipcss = skb_network_offset(skb);
		ipcso = (व्योम *)&(ip_hdr(skb)->check) - (व्योम *)skb->data;
		tucss = skb_transport_offset(skb);
		tucso = (व्योम *)&(tcp_hdr(skb)->check) - (व्योम *)skb->data;
		tucse = 0;

		cmd_length |= (E1000_TXD_CMD_DEXT | E1000_TXD_CMD_TSE |
			       E1000_TXD_CMD_TCP | (skb->len - (hdr_len)));

		i = tx_ring->next_to_use;
		context_desc = E1000_CONTEXT_DESC(*tx_ring, i);
		buffer_info = &tx_ring->buffer_info[i];

		context_desc->lower_setup.ip_fields.ipcss  = ipcss;
		context_desc->lower_setup.ip_fields.ipcso  = ipcso;
		context_desc->lower_setup.ip_fields.ipcse  = cpu_to_le16(ipcse);
		context_desc->upper_setup.tcp_fields.tucss = tucss;
		context_desc->upper_setup.tcp_fields.tucso = tucso;
		context_desc->upper_setup.tcp_fields.tucse = cpu_to_le16(tucse);
		context_desc->tcp_seg_setup.fields.mss     = cpu_to_le16(mss);
		context_desc->tcp_seg_setup.fields.hdr_len = hdr_len;
		context_desc->cmd_and_length = cpu_to_le32(cmd_length);

		buffer_info->समय_stamp = jअगरfies;
		buffer_info->next_to_watch = i;

		अगर (++i == tx_ring->count)
			i = 0;

		tx_ring->next_to_use = i;

		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool e1000_tx_csum(काष्ठा e1000_adapter *adapter,
			  काष्ठा e1000_tx_ring *tx_ring, काष्ठा sk_buff *skb,
			  __be16 protocol)
अणु
	काष्ठा e1000_context_desc *context_desc;
	काष्ठा e1000_tx_buffer *buffer_info;
	अचिन्हित पूर्णांक i;
	u8 css;
	u32 cmd_len = E1000_TXD_CMD_DEXT;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस false;

	चयन (protocol) अणु
	हाल cpu_to_be16(ETH_P_IP):
		अगर (ip_hdr(skb)->protocol == IPPROTO_TCP)
			cmd_len |= E1000_TXD_CMD_TCP;
		अवरोध;
	हाल cpu_to_be16(ETH_P_IPV6):
		/* XXX not handling all IPV6 headers */
		अगर (ipv6_hdr(skb)->nexthdr == IPPROTO_TCP)
			cmd_len |= E1000_TXD_CMD_TCP;
		अवरोध;
	शेष:
		अगर (unlikely(net_ratelimit()))
			e_warn(drv, "checksum_partial proto=%x!\n",
			       skb->protocol);
		अवरोध;
	पूर्ण

	css = skb_checksum_start_offset(skb);

	i = tx_ring->next_to_use;
	buffer_info = &tx_ring->buffer_info[i];
	context_desc = E1000_CONTEXT_DESC(*tx_ring, i);

	context_desc->lower_setup.ip_config = 0;
	context_desc->upper_setup.tcp_fields.tucss = css;
	context_desc->upper_setup.tcp_fields.tucso =
		css + skb->csum_offset;
	context_desc->upper_setup.tcp_fields.tucse = 0;
	context_desc->tcp_seg_setup.data = 0;
	context_desc->cmd_and_length = cpu_to_le32(cmd_len);

	buffer_info->समय_stamp = jअगरfies;
	buffer_info->next_to_watch = i;

	अगर (unlikely(++i == tx_ring->count))
		i = 0;

	tx_ring->next_to_use = i;

	वापस true;
पूर्ण

#घोषणा E1000_MAX_TXD_PWR	12
#घोषणा E1000_MAX_DATA_PER_TXD	(1<<E1000_MAX_TXD_PWR)

अटल पूर्णांक e1000_tx_map(काष्ठा e1000_adapter *adapter,
			काष्ठा e1000_tx_ring *tx_ring,
			काष्ठा sk_buff *skb, अचिन्हित पूर्णांक first,
			अचिन्हित पूर्णांक max_per_txd, अचिन्हित पूर्णांक nr_frags,
			अचिन्हित पूर्णांक mss)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा e1000_tx_buffer *buffer_info;
	अचिन्हित पूर्णांक len = skb_headlen(skb);
	अचिन्हित पूर्णांक offset = 0, size, count = 0, i;
	अचिन्हित पूर्णांक f, bytecount, segs;

	i = tx_ring->next_to_use;

	जबतक (len) अणु
		buffer_info = &tx_ring->buffer_info[i];
		size = min(len, max_per_txd);
		/* Workaround क्रम Controller erratum --
		 * descriptor क्रम non-tso packet in a linear SKB that follows a
		 * tso माला_लो written back prematurely beक्रमe the data is fully
		 * DMA'd to the controller
		 */
		अगर (!skb->data_len && tx_ring->last_tx_tso &&
		    !skb_is_gso(skb)) अणु
			tx_ring->last_tx_tso = false;
			size -= 4;
		पूर्ण

		/* Workaround क्रम premature desc ग_लिखो-backs
		 * in TSO mode.  Append 4-byte sentinel desc
		 */
		अगर (unlikely(mss && !nr_frags && size == len && size > 8))
			size -= 4;
		/* work-around क्रम errata 10 and it applies
		 * to all controllers in PCI-X mode
		 * The fix is to make sure that the first descriptor of a
		 * packet is smaller than 2048 - 16 - 16 (or 2016) bytes
		 */
		अगर (unlikely((hw->bus_type == e1000_bus_type_pcix) &&
			     (size > 2015) && count == 0))
			size = 2015;

		/* Workaround क्रम potential 82544 hang in PCI-X.  Aव्योम
		 * terminating buffers within evenly-aligned dwords.
		 */
		अगर (unlikely(adapter->pcix_82544 &&
		   !((अचिन्हित दीर्घ)(skb->data + offset + size - 1) & 4) &&
		   size > 4))
			size -= 4;

		buffer_info->length = size;
		/* set समय_stamp *beक्रमe* dma to help aव्योम a possible race */
		buffer_info->समय_stamp = jअगरfies;
		buffer_info->mapped_as_page = false;
		buffer_info->dma = dma_map_single(&pdev->dev,
						  skb->data + offset,
						  size, DMA_TO_DEVICE);
		अगर (dma_mapping_error(&pdev->dev, buffer_info->dma))
			जाओ dma_error;
		buffer_info->next_to_watch = i;

		len -= size;
		offset += size;
		count++;
		अगर (len) अणु
			i++;
			अगर (unlikely(i == tx_ring->count))
				i = 0;
		पूर्ण
	पूर्ण

	क्रम (f = 0; f < nr_frags; f++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[f];

		len = skb_frag_size(frag);
		offset = 0;

		जबतक (len) अणु
			अचिन्हित दीर्घ bufend;
			i++;
			अगर (unlikely(i == tx_ring->count))
				i = 0;

			buffer_info = &tx_ring->buffer_info[i];
			size = min(len, max_per_txd);
			/* Workaround क्रम premature desc ग_लिखो-backs
			 * in TSO mode.  Append 4-byte sentinel desc
			 */
			अगर (unlikely(mss && f == (nr_frags-1) &&
			    size == len && size > 8))
				size -= 4;
			/* Workaround क्रम potential 82544 hang in PCI-X.
			 * Aव्योम terminating buffers within evenly-aligned
			 * dwords.
			 */
			bufend = (अचिन्हित दीर्घ)
				page_to_phys(skb_frag_page(frag));
			bufend += offset + size - 1;
			अगर (unlikely(adapter->pcix_82544 &&
				     !(bufend & 4) &&
				     size > 4))
				size -= 4;

			buffer_info->length = size;
			buffer_info->समय_stamp = jअगरfies;
			buffer_info->mapped_as_page = true;
			buffer_info->dma = skb_frag_dma_map(&pdev->dev, frag,
						offset, size, DMA_TO_DEVICE);
			अगर (dma_mapping_error(&pdev->dev, buffer_info->dma))
				जाओ dma_error;
			buffer_info->next_to_watch = i;

			len -= size;
			offset += size;
			count++;
		पूर्ण
	पूर्ण

	segs = skb_shinfo(skb)->gso_segs ?: 1;
	/* multiply data chunks by size of headers */
	bytecount = ((segs - 1) * skb_headlen(skb)) + skb->len;

	tx_ring->buffer_info[i].skb = skb;
	tx_ring->buffer_info[i].segs = segs;
	tx_ring->buffer_info[i].bytecount = bytecount;
	tx_ring->buffer_info[first].next_to_watch = i;

	वापस count;

dma_error:
	dev_err(&pdev->dev, "TX DMA map failed\n");
	buffer_info->dma = 0;
	अगर (count)
		count--;

	जबतक (count--) अणु
		अगर (i == 0)
			i += tx_ring->count;
		i--;
		buffer_info = &tx_ring->buffer_info[i];
		e1000_unmap_and_मुक्त_tx_resource(adapter, buffer_info);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम e1000_tx_queue(काष्ठा e1000_adapter *adapter,
			   काष्ठा e1000_tx_ring *tx_ring, पूर्णांक tx_flags,
			   पूर्णांक count)
अणु
	काष्ठा e1000_tx_desc *tx_desc = शून्य;
	काष्ठा e1000_tx_buffer *buffer_info;
	u32 txd_upper = 0, txd_lower = E1000_TXD_CMD_IFCS;
	अचिन्हित पूर्णांक i;

	अगर (likely(tx_flags & E1000_TX_FLAGS_TSO)) अणु
		txd_lower |= E1000_TXD_CMD_DEXT | E1000_TXD_DTYP_D |
			     E1000_TXD_CMD_TSE;
		txd_upper |= E1000_TXD_POPTS_TXSM << 8;

		अगर (likely(tx_flags & E1000_TX_FLAGS_IPV4))
			txd_upper |= E1000_TXD_POPTS_IXSM << 8;
	पूर्ण

	अगर (likely(tx_flags & E1000_TX_FLAGS_CSUM)) अणु
		txd_lower |= E1000_TXD_CMD_DEXT | E1000_TXD_DTYP_D;
		txd_upper |= E1000_TXD_POPTS_TXSM << 8;
	पूर्ण

	अगर (unlikely(tx_flags & E1000_TX_FLAGS_VLAN)) अणु
		txd_lower |= E1000_TXD_CMD_VLE;
		txd_upper |= (tx_flags & E1000_TX_FLAGS_VLAN_MASK);
	पूर्ण

	अगर (unlikely(tx_flags & E1000_TX_FLAGS_NO_FCS))
		txd_lower &= ~(E1000_TXD_CMD_IFCS);

	i = tx_ring->next_to_use;

	जबतक (count--) अणु
		buffer_info = &tx_ring->buffer_info[i];
		tx_desc = E1000_TX_DESC(*tx_ring, i);
		tx_desc->buffer_addr = cpu_to_le64(buffer_info->dma);
		tx_desc->lower.data =
			cpu_to_le32(txd_lower | buffer_info->length);
		tx_desc->upper.data = cpu_to_le32(txd_upper);
		अगर (unlikely(++i == tx_ring->count))
			i = 0;
	पूर्ण

	tx_desc->lower.data |= cpu_to_le32(adapter->txd_cmd);

	/* txd_cmd re-enables FCS, so we'll re-disable it here as desired. */
	अगर (unlikely(tx_flags & E1000_TX_FLAGS_NO_FCS))
		tx_desc->lower.data &= ~(cpu_to_le32(E1000_TXD_CMD_IFCS));

	/* Force memory ग_लिखोs to complete beक्रमe letting h/w
	 * know there are new descriptors to fetch.  (Only
	 * applicable क्रम weak-ordered memory model archs,
	 * such as IA-64).
	 */
	dma_wmb();

	tx_ring->next_to_use = i;
पूर्ण

/* 82547 workaround to aव्योम controller hang in half-duplex environment.
 * The workaround is to aव्योम queuing a large packet that would span
 * the पूर्णांकernal Tx FIFO ring boundary by notअगरying the stack to resend
 * the packet at a later समय.  This gives the Tx FIFO an opportunity to
 * flush all packets.  When that occurs, we reset the Tx FIFO poपूर्णांकers
 * to the beginning of the Tx FIFO.
 */

#घोषणा E1000_FIFO_HDR			0x10
#घोषणा E1000_82547_PAD_LEN		0x3E0

अटल पूर्णांक e1000_82547_fअगरo_workaround(काष्ठा e1000_adapter *adapter,
				       काष्ठा sk_buff *skb)
अणु
	u32 fअगरo_space = adapter->tx_fअगरo_size - adapter->tx_fअगरo_head;
	u32 skb_fअगरo_len = skb->len + E1000_FIFO_HDR;

	skb_fअगरo_len = ALIGN(skb_fअगरo_len, E1000_FIFO_HDR);

	अगर (adapter->link_duplex != HALF_DUPLEX)
		जाओ no_fअगरo_stall_required;

	अगर (atomic_पढ़ो(&adapter->tx_fअगरo_stall))
		वापस 1;

	अगर (skb_fअगरo_len >= (E1000_82547_PAD_LEN + fअगरo_space)) अणु
		atomic_set(&adapter->tx_fअगरo_stall, 1);
		वापस 1;
	पूर्ण

no_fअगरo_stall_required:
	adapter->tx_fअगरo_head += skb_fअगरo_len;
	अगर (adapter->tx_fअगरo_head >= adapter->tx_fअगरo_size)
		adapter->tx_fअगरo_head -= adapter->tx_fअगरo_size;
	वापस 0;
पूर्ण

अटल पूर्णांक __e1000_maybe_stop_tx(काष्ठा net_device *netdev, पूर्णांक size)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_tx_ring *tx_ring = adapter->tx_ring;

	netअगर_stop_queue(netdev);
	/* Herbert's original patch had:
	 *  smp_mb__after_netअगर_stop_queue();
	 * but since that करोesn't exist yet, just खोलो code it.
	 */
	smp_mb();

	/* We need to check again in a हाल another CPU has just
	 * made room available.
	 */
	अगर (likely(E1000_DESC_UNUSED(tx_ring) < size))
		वापस -EBUSY;

	/* A reprieve! */
	netअगर_start_queue(netdev);
	++adapter->restart_queue;
	वापस 0;
पूर्ण

अटल पूर्णांक e1000_maybe_stop_tx(काष्ठा net_device *netdev,
			       काष्ठा e1000_tx_ring *tx_ring, पूर्णांक size)
अणु
	अगर (likely(E1000_DESC_UNUSED(tx_ring) >= size))
		वापस 0;
	वापस __e1000_maybe_stop_tx(netdev, size);
पूर्ण

#घोषणा TXD_USE_COUNT(S, X) (((S) + ((1 << (X)) - 1)) >> (X))
अटल netdev_tx_t e1000_xmit_frame(काष्ठा sk_buff *skb,
				    काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_tx_ring *tx_ring;
	अचिन्हित पूर्णांक first, max_per_txd = E1000_MAX_DATA_PER_TXD;
	अचिन्हित पूर्णांक max_txd_pwr = E1000_MAX_TXD_PWR;
	अचिन्हित पूर्णांक tx_flags = 0;
	अचिन्हित पूर्णांक len = skb_headlen(skb);
	अचिन्हित पूर्णांक nr_frags;
	अचिन्हित पूर्णांक mss;
	पूर्णांक count = 0;
	पूर्णांक tso;
	अचिन्हित पूर्णांक f;
	__be16 protocol = vlan_get_protocol(skb);

	/* This goes back to the question of how to logically map a Tx queue
	 * to a flow.  Right now, perक्रमmance is impacted slightly negatively
	 * अगर using multiple Tx queues.  If the stack अवरोधs away from a
	 * single qdisc implementation, we can look at this again.
	 */
	tx_ring = adapter->tx_ring;

	/* On PCI/PCI-X HW, अगर packet size is less than ETH_ZLEN,
	 * packets may get corrupted during padding by HW.
	 * To WA this issue, pad all small packets manually.
	 */
	अगर (eth_skb_pad(skb))
		वापस NETDEV_TX_OK;

	mss = skb_shinfo(skb)->gso_size;
	/* The controller करोes a simple calculation to
	 * make sure there is enough room in the FIFO beक्रमe
	 * initiating the DMA क्रम each buffer.  The calc is:
	 * 4 = उच्चमान(buffer len/mss).  To make sure we करोn't
	 * overrun the FIFO, adjust the max buffer len अगर mss
	 * drops.
	 */
	अगर (mss) अणु
		u8 hdr_len;
		max_per_txd = min(mss << 2, max_per_txd);
		max_txd_pwr = fls(max_per_txd) - 1;

		hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
		अगर (skb->data_len && hdr_len == len) अणु
			चयन (hw->mac_type) अणु
			हाल e1000_82544: अणु
				अचिन्हित पूर्णांक pull_size;

				/* Make sure we have room to chop off 4 bytes,
				 * and that the end alignment will work out to
				 * this hardware's requirements
				 * NOTE: this is a TSO only workaround
				 * अगर end byte alignment not correct move us
				 * पूर्णांकo the next dword
				 */
				अगर ((अचिन्हित दीर्घ)(skb_tail_poपूर्णांकer(skb) - 1)
				    & 4)
					अवरोध;
				pull_size = min((अचिन्हित पूर्णांक)4, skb->data_len);
				अगर (!__pskb_pull_tail(skb, pull_size)) अणु
					e_err(drv, "__pskb_pull_tail "
					      "failed.\n");
					dev_kमुक्त_skb_any(skb);
					वापस NETDEV_TX_OK;
				पूर्ण
				len = skb_headlen(skb);
				अवरोध;
			पूर्ण
			शेष:
				/* करो nothing */
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* reserve a descriptor क्रम the offload context */
	अगर ((mss) || (skb->ip_summed == CHECKSUM_PARTIAL))
		count++;
	count++;

	/* Controller Erratum workaround */
	अगर (!skb->data_len && tx_ring->last_tx_tso && !skb_is_gso(skb))
		count++;

	count += TXD_USE_COUNT(len, max_txd_pwr);

	अगर (adapter->pcix_82544)
		count++;

	/* work-around क्रम errata 10 and it applies to all controllers
	 * in PCI-X mode, so add one more descriptor to the count
	 */
	अगर (unlikely((hw->bus_type == e1000_bus_type_pcix) &&
			(len > 2015)))
		count++;

	nr_frags = skb_shinfo(skb)->nr_frags;
	क्रम (f = 0; f < nr_frags; f++)
		count += TXD_USE_COUNT(skb_frag_size(&skb_shinfo(skb)->frags[f]),
				       max_txd_pwr);
	अगर (adapter->pcix_82544)
		count += nr_frags;

	/* need: count + 2 desc gap to keep tail from touching
	 * head, otherwise try next समय
	 */
	अगर (unlikely(e1000_maybe_stop_tx(netdev, tx_ring, count + 2)))
		वापस NETDEV_TX_BUSY;

	अगर (unlikely((hw->mac_type == e1000_82547) &&
		     (e1000_82547_fअगरo_workaround(adapter, skb)))) अणु
		netअगर_stop_queue(netdev);
		अगर (!test_bit(__E1000_DOWN, &adapter->flags))
			schedule_delayed_work(&adapter->fअगरo_stall_task, 1);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (skb_vlan_tag_present(skb)) अणु
		tx_flags |= E1000_TX_FLAGS_VLAN;
		tx_flags |= (skb_vlan_tag_get(skb) <<
			     E1000_TX_FLAGS_VLAN_SHIFT);
	पूर्ण

	first = tx_ring->next_to_use;

	tso = e1000_tso(adapter, tx_ring, skb, protocol);
	अगर (tso < 0) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (likely(tso)) अणु
		अगर (likely(hw->mac_type != e1000_82544))
			tx_ring->last_tx_tso = true;
		tx_flags |= E1000_TX_FLAGS_TSO;
	पूर्ण अन्यथा अगर (likely(e1000_tx_csum(adapter, tx_ring, skb, protocol)))
		tx_flags |= E1000_TX_FLAGS_CSUM;

	अगर (protocol == htons(ETH_P_IP))
		tx_flags |= E1000_TX_FLAGS_IPV4;

	अगर (unlikely(skb->no_fcs))
		tx_flags |= E1000_TX_FLAGS_NO_FCS;

	count = e1000_tx_map(adapter, tx_ring, skb, first, max_per_txd,
			     nr_frags, mss);

	अगर (count) अणु
		/* The descriptors needed is higher than other Intel drivers
		 * due to a number of workarounds.  The अवरोधकरोwn is below:
		 * Data descriptors: MAX_SKB_FRAGS + 1
		 * Context Descriptor: 1
		 * Keep head from touching tail: 2
		 * Workarounds: 3
		 */
		पूर्णांक desc_needed = MAX_SKB_FRAGS + 7;

		netdev_sent_queue(netdev, skb->len);
		skb_tx_बारtamp(skb);

		e1000_tx_queue(adapter, tx_ring, tx_flags, count);

		/* 82544 potentially requires twice as many data descriptors
		 * in order to guarantee buffers करोn't end on evenly-aligned
		 * dwords
		 */
		अगर (adapter->pcix_82544)
			desc_needed += MAX_SKB_FRAGS + 1;

		/* Make sure there is space in the ring क्रम the next send. */
		e1000_maybe_stop_tx(netdev, tx_ring, desc_needed);

		अगर (!netdev_xmit_more() ||
		    netअगर_xmit_stopped(netdev_get_tx_queue(netdev, 0))) अणु
			ग_लिखोl(tx_ring->next_to_use, hw->hw_addr + tx_ring->tdt);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb_any(skb);
		tx_ring->buffer_info[first].समय_stamp = 0;
		tx_ring->next_to_use = first;
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

#घोषणा NUM_REGS 38 /* 1 based count */
अटल व्योम e1000_regdump(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 regs[NUM_REGS];
	u32 *regs_buff = regs;
	पूर्णांक i = 0;

	अटल स्थिर अक्षर * स्थिर reg_name[] = अणु
		"CTRL",  "STATUS",
		"RCTL", "RDLEN", "RDH", "RDT", "RDTR",
		"TCTL", "TDBAL", "TDBAH", "TDLEN", "TDH", "TDT",
		"TIDV", "TXDCTL", "TADV", "TARC0",
		"TDBAL1", "TDBAH1", "TDLEN1", "TDH1", "TDT1",
		"TXDCTL1", "TARC1",
		"CTRL_EXT", "ERT", "RDBAL", "RDBAH",
		"TDFH", "TDFT", "TDFHS", "TDFTS", "TDFPC",
		"RDFH", "RDFT", "RDFHS", "RDFTS", "RDFPC"
	पूर्ण;

	regs_buff[0]  = er32(CTRL);
	regs_buff[1]  = er32(STATUS);

	regs_buff[2]  = er32(RCTL);
	regs_buff[3]  = er32(RDLEN);
	regs_buff[4]  = er32(RDH);
	regs_buff[5]  = er32(RDT);
	regs_buff[6]  = er32(RDTR);

	regs_buff[7]  = er32(TCTL);
	regs_buff[8]  = er32(TDBAL);
	regs_buff[9]  = er32(TDBAH);
	regs_buff[10] = er32(TDLEN);
	regs_buff[11] = er32(TDH);
	regs_buff[12] = er32(TDT);
	regs_buff[13] = er32(TIDV);
	regs_buff[14] = er32(TXDCTL);
	regs_buff[15] = er32(TADV);
	regs_buff[16] = er32(TARC0);

	regs_buff[17] = er32(TDBAL1);
	regs_buff[18] = er32(TDBAH1);
	regs_buff[19] = er32(TDLEN1);
	regs_buff[20] = er32(TDH1);
	regs_buff[21] = er32(TDT1);
	regs_buff[22] = er32(TXDCTL1);
	regs_buff[23] = er32(TARC1);
	regs_buff[24] = er32(CTRL_EXT);
	regs_buff[25] = er32(ERT);
	regs_buff[26] = er32(RDBAL0);
	regs_buff[27] = er32(RDBAH0);
	regs_buff[28] = er32(TDFH);
	regs_buff[29] = er32(TDFT);
	regs_buff[30] = er32(TDFHS);
	regs_buff[31] = er32(TDFTS);
	regs_buff[32] = er32(TDFPC);
	regs_buff[33] = er32(RDFH);
	regs_buff[34] = er32(RDFT);
	regs_buff[35] = er32(RDFHS);
	regs_buff[36] = er32(RDFTS);
	regs_buff[37] = er32(RDFPC);

	pr_info("Register dump\n");
	क्रम (i = 0; i < NUM_REGS; i++)
		pr_info("%-15s  %08x\n", reg_name[i], regs_buff[i]);
पूर्ण

/*
 * e1000_dump: Prपूर्णांक रेजिस्टरs, tx ring and rx ring
 */
अटल व्योम e1000_dump(काष्ठा e1000_adapter *adapter)
अणु
	/* this code करोesn't handle multiple rings */
	काष्ठा e1000_tx_ring *tx_ring = adapter->tx_ring;
	काष्ठा e1000_rx_ring *rx_ring = adapter->rx_ring;
	पूर्णांक i;

	अगर (!netअगर_msg_hw(adapter))
		वापस;

	/* Prपूर्णांक Registers */
	e1000_regdump(adapter);

	/* transmit dump */
	pr_info("TX Desc ring0 dump\n");

	/* Transmit Descriptor Formats - DEXT[29] is 0 (Legacy) or 1 (Extended)
	 *
	 * Legacy Transmit Descriptor
	 *   +--------------------------------------------------------------+
	 * 0 |         Buffer Address [63:0] (Reserved on Write Back)       |
	 *   +--------------------------------------------------------------+
	 * 8 | Special  |    CSS     | Status |  CMD    |  CSO   |  Length  |
	 *   +--------------------------------------------------------------+
	 *   63       48 47        36 35    32 31     24 23    16 15        0
	 *
	 * Extended Context Descriptor (DTYP=0x0) क्रम TSO or checksum offload
	 *   63      48 47    40 39       32 31             16 15    8 7      0
	 *   +----------------------------------------------------------------+
	 * 0 |  TUCSE  | TUCS0  |   TUCSS   |     IPCSE       | IPCS0 | IPCSS |
	 *   +----------------------------------------------------------------+
	 * 8 |   MSS   | HDRLEN | RSV | STA | TUCMD | DTYP |      PAYLEN      |
	 *   +----------------------------------------------------------------+
	 *   63      48 47    40 39 36 35 32 31   24 23  20 19                0
	 *
	 * Extended Data Descriptor (DTYP=0x1)
	 *   +----------------------------------------------------------------+
	 * 0 |                     Buffer Address [63:0]                      |
	 *   +----------------------------------------------------------------+
	 * 8 | VLAN tag |  POPTS  | Rsvd | Status | Command | DTYP |  DTALEN  |
	 *   +----------------------------------------------------------------+
	 *   63       48 47     40 39  36 35    32 31     24 23  20 19        0
	 */
	pr_info("Tc[desc]     [Ce CoCsIpceCoS] [MssHlRSCm0Plen] [bi->dma       ] leng  ntw timestmp         bi->skb\n");
	pr_info("Td[desc]     [address 63:0  ] [VlaPoRSCm1Dlen] [bi->dma       ] leng  ntw timestmp         bi->skb\n");

	अगर (!netअगर_msg_tx_करोne(adapter))
		जाओ rx_ring_summary;

	क्रम (i = 0; tx_ring->desc && (i < tx_ring->count); i++) अणु
		काष्ठा e1000_tx_desc *tx_desc = E1000_TX_DESC(*tx_ring, i);
		काष्ठा e1000_tx_buffer *buffer_info = &tx_ring->buffer_info[i];
		काष्ठा my_u अणु __le64 a; __le64 b; पूर्ण;
		काष्ठा my_u *u = (काष्ठा my_u *)tx_desc;
		स्थिर अक्षर *type;

		अगर (i == tx_ring->next_to_use && i == tx_ring->next_to_clean)
			type = "NTC/U";
		अन्यथा अगर (i == tx_ring->next_to_use)
			type = "NTU";
		अन्यथा अगर (i == tx_ring->next_to_clean)
			type = "NTC";
		अन्यथा
			type = "";

		pr_info("T%c[0x%03X]    %016llX %016llX %016llX %04X  %3X %016llX %p %s\n",
			((le64_to_cpu(u->b) & (1<<20)) ? 'd' : 'c'), i,
			le64_to_cpu(u->a), le64_to_cpu(u->b),
			(u64)buffer_info->dma, buffer_info->length,
			buffer_info->next_to_watch,
			(u64)buffer_info->समय_stamp, buffer_info->skb, type);
	पूर्ण

rx_ring_summary:
	/* receive dump */
	pr_info("\nRX Desc ring dump\n");

	/* Legacy Receive Descriptor Format
	 *
	 * +-----------------------------------------------------+
	 * |                Buffer Address [63:0]                |
	 * +-----------------------------------------------------+
	 * | VLAN Tag | Errors | Status 0 | Packet csum | Length |
	 * +-----------------------------------------------------+
	 * 63       48 47    40 39      32 31         16 15      0
	 */
	pr_info("R[desc]      [address 63:0  ] [vl er S cks ln] [bi->dma       ] [bi->skb]\n");

	अगर (!netअगर_msg_rx_status(adapter))
		जाओ निकास;

	क्रम (i = 0; rx_ring->desc && (i < rx_ring->count); i++) अणु
		काष्ठा e1000_rx_desc *rx_desc = E1000_RX_DESC(*rx_ring, i);
		काष्ठा e1000_rx_buffer *buffer_info = &rx_ring->buffer_info[i];
		काष्ठा my_u अणु __le64 a; __le64 b; पूर्ण;
		काष्ठा my_u *u = (काष्ठा my_u *)rx_desc;
		स्थिर अक्षर *type;

		अगर (i == rx_ring->next_to_use)
			type = "NTU";
		अन्यथा अगर (i == rx_ring->next_to_clean)
			type = "NTC";
		अन्यथा
			type = "";

		pr_info("R[0x%03X]     %016llX %016llX %016llX %p %s\n",
			i, le64_to_cpu(u->a), le64_to_cpu(u->b),
			(u64)buffer_info->dma, buffer_info->rxbuf.data, type);
	पूर्ण /* क्रम */

	/* dump the descriptor caches */
	/* rx */
	pr_info("Rx descriptor cache in 64bit format\n");
	क्रम (i = 0x6000; i <= 0x63FF ; i += 0x10) अणु
		pr_info("R%04X: %08X|%08X %08X|%08X\n",
			i,
			पढ़ोl(adapter->hw.hw_addr + i+4),
			पढ़ोl(adapter->hw.hw_addr + i),
			पढ़ोl(adapter->hw.hw_addr + i+12),
			पढ़ोl(adapter->hw.hw_addr + i+8));
	पूर्ण
	/* tx */
	pr_info("Tx descriptor cache in 64bit format\n");
	क्रम (i = 0x7000; i <= 0x73FF ; i += 0x10) अणु
		pr_info("T%04X: %08X|%08X %08X|%08X\n",
			i,
			पढ़ोl(adapter->hw.hw_addr + i+4),
			पढ़ोl(adapter->hw.hw_addr + i),
			पढ़ोl(adapter->hw.hw_addr + i+12),
			पढ़ोl(adapter->hw.hw_addr + i+8));
	पूर्ण
निकास:
	वापस;
पूर्ण

/**
 * e1000_tx_समयout - Respond to a Tx Hang
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @txqueue: number of the Tx queue that hung (unused)
 **/
अटल व्योम e1000_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक __always_unused txqueue)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	/* Do the reset outside of पूर्णांकerrupt context */
	adapter->tx_समयout_count++;
	schedule_work(&adapter->reset_task);
पूर्ण

अटल व्योम e1000_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा e1000_adapter *adapter =
		container_of(work, काष्ठा e1000_adapter, reset_task);

	e_err(drv, "Reset adapter\n");
	e1000_reinit_locked(adapter);
पूर्ण

/**
 * e1000_change_mtu - Change the Maximum Transfer Unit
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @new_mtu: new value क्रम maximum frame size
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक e1000_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक max_frame = new_mtu + ETH_HLEN + ETH_FCS_LEN;

	/* Adapter-specअगरic max frame size limits. */
	चयन (hw->mac_type) अणु
	हाल e1000_undefined ... e1000_82542_rev2_1:
		अगर (max_frame > (ETH_FRAME_LEN + ETH_FCS_LEN)) अणु
			e_err(probe, "Jumbo Frames not supported.\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		/* Capable of supporting up to MAX_JUMBO_FRAME_SIZE limit. */
		अवरोध;
	पूर्ण

	जबतक (test_and_set_bit(__E1000_RESETTING, &adapter->flags))
		msleep(1);
	/* e1000_करोwn has a dependency on max_frame_size */
	hw->max_frame_size = max_frame;
	अगर (netअगर_running(netdev)) अणु
		/* prevent buffers from being पुनः_स्मृतिated */
		adapter->alloc_rx_buf = e1000_alloc_dummy_rx_buffers;
		e1000_करोwn(adapter);
	पूर्ण

	/* NOTE: netdev_alloc_skb reserves 16 bytes, and typically NET_IP_ALIGN
	 * means we reserve 2 more, this pushes us to allocate from the next
	 * larger slab size.
	 * i.e. RXBUFFER_2048 --> size-4096 slab
	 * however with the new *_jumbo_rx* routines, jumbo receives will use
	 * fragmented skbs
	 */

	अगर (max_frame <= E1000_RXBUFFER_2048)
		adapter->rx_buffer_len = E1000_RXBUFFER_2048;
	अन्यथा
#अगर (PAGE_SIZE >= E1000_RXBUFFER_16384)
		adapter->rx_buffer_len = E1000_RXBUFFER_16384;
#या_अगर (PAGE_SIZE >= E1000_RXBUFFER_4096)
		adapter->rx_buffer_len = PAGE_SIZE;
#पूर्ण_अगर

	/* adjust allocation अगर LPE protects us, and we aren't using SBP */
	अगर (!hw->tbi_compatibility_on &&
	    ((max_frame == (ETH_FRAME_LEN + ETH_FCS_LEN)) ||
	     (max_frame == MAXIMUM_ETHERNET_VLAN_SIZE)))
		adapter->rx_buffer_len = MAXIMUM_ETHERNET_VLAN_SIZE;

	netdev_dbg(netdev, "changing MTU from %d to %d\n",
		   netdev->mtu, new_mtu);
	netdev->mtu = new_mtu;

	अगर (netअगर_running(netdev))
		e1000_up(adapter);
	अन्यथा
		e1000_reset(adapter);

	clear_bit(__E1000_RESETTING, &adapter->flags);

	वापस 0;
पूर्ण

/**
 * e1000_update_stats - Update the board statistics counters
 * @adapter: board निजी काष्ठाure
 **/
व्योम e1000_update_stats(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा pci_dev *pdev = adapter->pdev;
	अचिन्हित दीर्घ flags;
	u16 phy_पंचांगp;

#घोषणा PHY_IDLE_ERROR_COUNT_MASK 0x00FF

	/* Prevent stats update जबतक adapter is being reset, or अगर the pci
	 * connection is करोwn.
	 */
	अगर (adapter->link_speed == 0)
		वापस;
	अगर (pci_channel_offline(pdev))
		वापस;

	spin_lock_irqsave(&adapter->stats_lock, flags);

	/* these counters are modअगरied from e1000_tbi_adjust_stats,
	 * called from the पूर्णांकerrupt context, so they must only
	 * be written जबतक holding adapter->stats_lock
	 */

	adapter->stats.crcerrs += er32(CRCERRS);
	adapter->stats.gprc += er32(GPRC);
	adapter->stats.gorcl += er32(GORCL);
	adapter->stats.gorch += er32(GORCH);
	adapter->stats.bprc += er32(BPRC);
	adapter->stats.mprc += er32(MPRC);
	adapter->stats.roc += er32(ROC);

	adapter->stats.prc64 += er32(PRC64);
	adapter->stats.prc127 += er32(PRC127);
	adapter->stats.prc255 += er32(PRC255);
	adapter->stats.prc511 += er32(PRC511);
	adapter->stats.prc1023 += er32(PRC1023);
	adapter->stats.prc1522 += er32(PRC1522);

	adapter->stats.symerrs += er32(SYMERRS);
	adapter->stats.mpc += er32(MPC);
	adapter->stats.scc += er32(SCC);
	adapter->stats.ecol += er32(ECOL);
	adapter->stats.mcc += er32(MCC);
	adapter->stats.latecol += er32(LATECOL);
	adapter->stats.dc += er32(DC);
	adapter->stats.sec += er32(SEC);
	adapter->stats.rlec += er32(RLEC);
	adapter->stats.xonrxc += er32(XONRXC);
	adapter->stats.xontxc += er32(XONTXC);
	adapter->stats.xoffrxc += er32(XOFFRXC);
	adapter->stats.xofftxc += er32(XOFFTXC);
	adapter->stats.fcruc += er32(FCRUC);
	adapter->stats.gptc += er32(GPTC);
	adapter->stats.gotcl += er32(GOTCL);
	adapter->stats.gotch += er32(GOTCH);
	adapter->stats.rnbc += er32(RNBC);
	adapter->stats.ruc += er32(RUC);
	adapter->stats.rfc += er32(RFC);
	adapter->stats.rjc += er32(RJC);
	adapter->stats.torl += er32(TORL);
	adapter->stats.torh += er32(TORH);
	adapter->stats.totl += er32(TOTL);
	adapter->stats.toth += er32(TOTH);
	adapter->stats.tpr += er32(TPR);

	adapter->stats.ptc64 += er32(PTC64);
	adapter->stats.ptc127 += er32(PTC127);
	adapter->stats.ptc255 += er32(PTC255);
	adapter->stats.ptc511 += er32(PTC511);
	adapter->stats.ptc1023 += er32(PTC1023);
	adapter->stats.ptc1522 += er32(PTC1522);

	adapter->stats.mptc += er32(MPTC);
	adapter->stats.bptc += er32(BPTC);

	/* used क्रम adaptive IFS */

	hw->tx_packet_delta = er32(TPT);
	adapter->stats.tpt += hw->tx_packet_delta;
	hw->collision_delta = er32(COLC);
	adapter->stats.colc += hw->collision_delta;

	अगर (hw->mac_type >= e1000_82543) अणु
		adapter->stats.algnerrc += er32(ALGNERRC);
		adapter->stats.rxerrc += er32(RXERRC);
		adapter->stats.tncrs += er32(TNCRS);
		adapter->stats.cexterr += er32(CEXTERR);
		adapter->stats.tsctc += er32(TSCTC);
		adapter->stats.tsctfc += er32(TSCTFC);
	पूर्ण

	/* Fill out the OS statistics काष्ठाure */
	netdev->stats.multicast = adapter->stats.mprc;
	netdev->stats.collisions = adapter->stats.colc;

	/* Rx Errors */

	/* RLEC on some newer hardware can be incorrect so build
	 * our own version based on RUC and ROC
	 */
	netdev->stats.rx_errors = adapter->stats.rxerrc +
		adapter->stats.crcerrs + adapter->stats.algnerrc +
		adapter->stats.ruc + adapter->stats.roc +
		adapter->stats.cexterr;
	adapter->stats.rlerrc = adapter->stats.ruc + adapter->stats.roc;
	netdev->stats.rx_length_errors = adapter->stats.rlerrc;
	netdev->stats.rx_crc_errors = adapter->stats.crcerrs;
	netdev->stats.rx_frame_errors = adapter->stats.algnerrc;
	netdev->stats.rx_missed_errors = adapter->stats.mpc;

	/* Tx Errors */
	adapter->stats.txerrc = adapter->stats.ecol + adapter->stats.latecol;
	netdev->stats.tx_errors = adapter->stats.txerrc;
	netdev->stats.tx_पातed_errors = adapter->stats.ecol;
	netdev->stats.tx_winकरोw_errors = adapter->stats.latecol;
	netdev->stats.tx_carrier_errors = adapter->stats.tncrs;
	अगर (hw->bad_tx_carr_stats_fd &&
	    adapter->link_duplex == FULL_DUPLEX) अणु
		netdev->stats.tx_carrier_errors = 0;
		adapter->stats.tncrs = 0;
	पूर्ण

	/* Tx Dropped needs to be मुख्यtained अन्यथाwhere */

	/* Phy Stats */
	अगर (hw->media_type == e1000_media_type_copper) अणु
		अगर ((adapter->link_speed == SPEED_1000) &&
		   (!e1000_पढ़ो_phy_reg(hw, PHY_1000T_STATUS, &phy_पंचांगp))) अणु
			phy_पंचांगp &= PHY_IDLE_ERROR_COUNT_MASK;
			adapter->phy_stats.idle_errors += phy_पंचांगp;
		पूर्ण

		अगर ((hw->mac_type <= e1000_82546) &&
		   (hw->phy_type == e1000_phy_m88) &&
		   !e1000_पढ़ो_phy_reg(hw, M88E1000_RX_ERR_CNTR, &phy_पंचांगp))
			adapter->phy_stats.receive_errors += phy_पंचांगp;
	पूर्ण

	/* Management Stats */
	अगर (hw->has_smbus) अणु
		adapter->stats.mgptc += er32(MGTPTC);
		adapter->stats.mgprc += er32(MGTPRC);
		adapter->stats.mgpdc += er32(MGTPDC);
	पूर्ण

	spin_unlock_irqrestore(&adapter->stats_lock, flags);
पूर्ण

/**
 * e1000_पूर्णांकr - Interrupt Handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a network पूर्णांकerface device काष्ठाure
 **/
अटल irqवापस_t e1000_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = data;
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 icr = er32(ICR);

	अगर (unlikely((!icr)))
		वापस IRQ_NONE;  /* Not our पूर्णांकerrupt */

	/* we might have caused the पूर्णांकerrupt, but the above
	 * पढ़ो cleared it, and just in हाल the driver is
	 * करोwn there is nothing to करो so वापस handled
	 */
	अगर (unlikely(test_bit(__E1000_DOWN, &adapter->flags)))
		वापस IRQ_HANDLED;

	अगर (unlikely(icr & (E1000_ICR_RXSEQ | E1000_ICR_LSC))) अणु
		hw->get_link_status = 1;
		/* guard against पूर्णांकerrupt when we're going करोwn */
		अगर (!test_bit(__E1000_DOWN, &adapter->flags))
			schedule_delayed_work(&adapter->watchकरोg_task, 1);
	पूर्ण

	/* disable पूर्णांकerrupts, without the synchronize_irq bit */
	ew32(IMC, ~0);
	E1000_WRITE_FLUSH();

	अगर (likely(napi_schedule_prep(&adapter->napi))) अणु
		adapter->total_tx_bytes = 0;
		adapter->total_tx_packets = 0;
		adapter->total_rx_bytes = 0;
		adapter->total_rx_packets = 0;
		__napi_schedule(&adapter->napi);
	पूर्ण अन्यथा अणु
		/* this really should not happen! अगर it करोes it is basically a
		 * bug, but not a hard error, so enable पूर्णांकs and जारी
		 */
		अगर (!test_bit(__E1000_DOWN, &adapter->flags))
			e1000_irq_enable(adapter);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * e1000_clean - NAPI Rx polling callback
 * @napi: napi काष्ठा containing references to driver info
 * @budget: budget given to driver क्रम receive packets
 **/
अटल पूर्णांक e1000_clean(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा e1000_adapter *adapter = container_of(napi, काष्ठा e1000_adapter,
						     napi);
	पूर्णांक tx_clean_complete = 0, work_करोne = 0;

	tx_clean_complete = e1000_clean_tx_irq(adapter, &adapter->tx_ring[0]);

	adapter->clean_rx(adapter, &adapter->rx_ring[0], &work_करोne, budget);

	अगर (!tx_clean_complete || work_करोne == budget)
		वापस budget;

	/* Exit the polling mode, but करोn't re-enable पूर्णांकerrupts अगर stack might
	 * poll us due to busy-polling
	 */
	अगर (likely(napi_complete_करोne(napi, work_करोne))) अणु
		अगर (likely(adapter->itr_setting & 3))
			e1000_set_itr(adapter);
		अगर (!test_bit(__E1000_DOWN, &adapter->flags))
			e1000_irq_enable(adapter);
	पूर्ण

	वापस work_करोne;
पूर्ण

/**
 * e1000_clean_tx_irq - Reclaim resources after transmit completes
 * @adapter: board निजी काष्ठाure
 * @tx_ring: ring to clean
 **/
अटल bool e1000_clean_tx_irq(काष्ठा e1000_adapter *adapter,
			       काष्ठा e1000_tx_ring *tx_ring)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_tx_desc *tx_desc, *eop_desc;
	काष्ठा e1000_tx_buffer *buffer_info;
	अचिन्हित पूर्णांक i, eop;
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित पूर्णांक total_tx_bytes = 0, total_tx_packets = 0;
	अचिन्हित पूर्णांक bytes_compl = 0, pkts_compl = 0;

	i = tx_ring->next_to_clean;
	eop = tx_ring->buffer_info[i].next_to_watch;
	eop_desc = E1000_TX_DESC(*tx_ring, eop);

	जबतक ((eop_desc->upper.data & cpu_to_le32(E1000_TXD_STAT_DD)) &&
	       (count < tx_ring->count)) अणु
		bool cleaned = false;
		dma_rmb();	/* पढ़ो buffer_info after eop_desc */
		क्रम ( ; !cleaned; count++) अणु
			tx_desc = E1000_TX_DESC(*tx_ring, i);
			buffer_info = &tx_ring->buffer_info[i];
			cleaned = (i == eop);

			अगर (cleaned) अणु
				total_tx_packets += buffer_info->segs;
				total_tx_bytes += buffer_info->bytecount;
				अगर (buffer_info->skb) अणु
					bytes_compl += buffer_info->skb->len;
					pkts_compl++;
				पूर्ण

			पूर्ण
			e1000_unmap_and_मुक्त_tx_resource(adapter, buffer_info);
			tx_desc->upper.data = 0;

			अगर (unlikely(++i == tx_ring->count))
				i = 0;
		पूर्ण

		eop = tx_ring->buffer_info[i].next_to_watch;
		eop_desc = E1000_TX_DESC(*tx_ring, eop);
	पूर्ण

	/* Synchronize with E1000_DESC_UNUSED called from e1000_xmit_frame,
	 * which will reuse the cleaned buffers.
	 */
	smp_store_release(&tx_ring->next_to_clean, i);

	netdev_completed_queue(netdev, pkts_compl, bytes_compl);

#घोषणा TX_WAKE_THRESHOLD 32
	अगर (unlikely(count && netअगर_carrier_ok(netdev) &&
		     E1000_DESC_UNUSED(tx_ring) >= TX_WAKE_THRESHOLD)) अणु
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();

		अगर (netअगर_queue_stopped(netdev) &&
		    !(test_bit(__E1000_DOWN, &adapter->flags))) अणु
			netअगर_wake_queue(netdev);
			++adapter->restart_queue;
		पूर्ण
	पूर्ण

	अगर (adapter->detect_tx_hung) अणु
		/* Detect a transmit hang in hardware, this serializes the
		 * check with the clearing of समय_stamp and movement of i
		 */
		adapter->detect_tx_hung = false;
		अगर (tx_ring->buffer_info[eop].समय_stamp &&
		    समय_after(jअगरfies, tx_ring->buffer_info[eop].समय_stamp +
			       (adapter->tx_समयout_factor * HZ)) &&
		    !(er32(STATUS) & E1000_STATUS_TXOFF)) अणु

			/* detected Tx unit hang */
			e_err(drv, "Detected Tx Unit Hang\n"
			      "  Tx Queue             <%lu>\n"
			      "  TDH                  <%x>\n"
			      "  TDT                  <%x>\n"
			      "  next_to_use          <%x>\n"
			      "  next_to_clean        <%x>\n"
			      "buffer_info[next_to_clean]\n"
			      "  time_stamp           <%lx>\n"
			      "  next_to_watch        <%x>\n"
			      "  jiffies              <%lx>\n"
			      "  next_to_watch.status <%x>\n",
				(अचिन्हित दीर्घ)(tx_ring - adapter->tx_ring),
				पढ़ोl(hw->hw_addr + tx_ring->tdh),
				पढ़ोl(hw->hw_addr + tx_ring->tdt),
				tx_ring->next_to_use,
				tx_ring->next_to_clean,
				tx_ring->buffer_info[eop].समय_stamp,
				eop,
				jअगरfies,
				eop_desc->upper.fields.status);
			e1000_dump(adapter);
			netअगर_stop_queue(netdev);
		पूर्ण
	पूर्ण
	adapter->total_tx_bytes += total_tx_bytes;
	adapter->total_tx_packets += total_tx_packets;
	netdev->stats.tx_bytes += total_tx_bytes;
	netdev->stats.tx_packets += total_tx_packets;
	वापस count < tx_ring->count;
पूर्ण

/**
 * e1000_rx_checksum - Receive Checksum Offload क्रम 82543
 * @adapter:     board निजी काष्ठाure
 * @status_err:  receive descriptor status and error fields
 * @csum:        receive descriptor csum field
 * @skb:         socket buffer with received data
 **/
अटल व्योम e1000_rx_checksum(काष्ठा e1000_adapter *adapter, u32 status_err,
			      u32 csum, काष्ठा sk_buff *skb)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 status = (u16)status_err;
	u8 errors = (u8)(status_err >> 24);

	skb_checksum_none_निश्चित(skb);

	/* 82543 or newer only */
	अगर (unlikely(hw->mac_type < e1000_82543))
		वापस;
	/* Ignore Checksum bit is set */
	अगर (unlikely(status & E1000_RXD_STAT_IXSM))
		वापस;
	/* TCP/UDP checksum error bit is set */
	अगर (unlikely(errors & E1000_RXD_ERR_TCPE)) अणु
		/* let the stack verअगरy checksum errors */
		adapter->hw_csum_err++;
		वापस;
	पूर्ण
	/* TCP/UDP Checksum has not been calculated */
	अगर (!(status & E1000_RXD_STAT_TCPCS))
		वापस;

	/* It must be a TCP or UDP packet with a valid checksum */
	अगर (likely(status & E1000_RXD_STAT_TCPCS)) अणु
		/* TCP checksum is good */
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण
	adapter->hw_csum_good++;
पूर्ण

/**
 * e1000_consume_page - helper function क्रम jumbo Rx path
 * @bi: software descriptor shaकरोw data
 * @skb: skb being modअगरied
 * @length: length of data being added
 **/
अटल व्योम e1000_consume_page(काष्ठा e1000_rx_buffer *bi, काष्ठा sk_buff *skb,
			       u16 length)
अणु
	bi->rxbuf.page = शून्य;
	skb->len += length;
	skb->data_len += length;
	skb->truesize += PAGE_SIZE;
पूर्ण

/**
 * e1000_receive_skb - helper function to handle rx indications
 * @adapter: board निजी काष्ठाure
 * @status: descriptor status field as written by hardware
 * @vlan: descriptor vlan field as written by hardware (no le/be conversion)
 * @skb: poपूर्णांकer to sk_buff to be indicated to stack
 */
अटल व्योम e1000_receive_skb(काष्ठा e1000_adapter *adapter, u8 status,
			      __le16 vlan, काष्ठा sk_buff *skb)
अणु
	skb->protocol = eth_type_trans(skb, adapter->netdev);

	अगर (status & E1000_RXD_STAT_VP) अणु
		u16 vid = le16_to_cpu(vlan) & E1000_RXD_SPC_VLAN_MASK;

		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);
	पूर्ण
	napi_gro_receive(&adapter->napi, skb);
पूर्ण

/**
 * e1000_tbi_adjust_stats
 * @hw: Struct containing variables accessed by shared code
 * @stats: poपूर्णांक to stats काष्ठा
 * @frame_len: The length of the frame in question
 * @mac_addr: The Ethernet destination address of the frame in question
 *
 * Adjusts the statistic counters when a frame is accepted by TBI_ACCEPT
 */
अटल व्योम e1000_tbi_adjust_stats(काष्ठा e1000_hw *hw,
				   काष्ठा e1000_hw_stats *stats,
				   u32 frame_len, स्थिर u8 *mac_addr)
अणु
	u64 carry_bit;

	/* First adjust the frame length. */
	frame_len--;
	/* We need to adjust the statistics counters, since the hardware
	 * counters overcount this packet as a CRC error and undercount
	 * the packet as a good packet
	 */
	/* This packet should not be counted as a CRC error. */
	stats->crcerrs--;
	/* This packet करोes count as a Good Packet Received. */
	stats->gprc++;

	/* Adjust the Good Octets received counters */
	carry_bit = 0x80000000 & stats->gorcl;
	stats->gorcl += frame_len;
	/* If the high bit of Gorcl (the low 32 bits of the Good Octets
	 * Received Count) was one beक्रमe the addition,
	 * AND it is zero after, then we lost the carry out,
	 * need to add one to Gorch (Good Octets Received Count High).
	 * This could be simplअगरied अगर all environments supported
	 * 64-bit पूर्णांकegers.
	 */
	अगर (carry_bit && ((stats->gorcl & 0x80000000) == 0))
		stats->gorch++;
	/* Is this a broadcast or multicast?  Check broadcast first,
	 * since the test क्रम a multicast frame will test positive on
	 * a broadcast frame.
	 */
	अगर (is_broadcast_ether_addr(mac_addr))
		stats->bprc++;
	अन्यथा अगर (is_multicast_ether_addr(mac_addr))
		stats->mprc++;

	अगर (frame_len == hw->max_frame_size) अणु
		/* In this हाल, the hardware has overcounted the number of
		 * oversize frames.
		 */
		अगर (stats->roc > 0)
			stats->roc--;
	पूर्ण

	/* Adjust the bin counters when the extra byte put the frame in the
	 * wrong bin. Remember that the frame_len was adjusted above.
	 */
	अगर (frame_len == 64) अणु
		stats->prc64++;
		stats->prc127--;
	पूर्ण अन्यथा अगर (frame_len == 127) अणु
		stats->prc127++;
		stats->prc255--;
	पूर्ण अन्यथा अगर (frame_len == 255) अणु
		stats->prc255++;
		stats->prc511--;
	पूर्ण अन्यथा अगर (frame_len == 511) अणु
		stats->prc511++;
		stats->prc1023--;
	पूर्ण अन्यथा अगर (frame_len == 1023) अणु
		stats->prc1023++;
		stats->prc1522--;
	पूर्ण अन्यथा अगर (frame_len == 1522) अणु
		stats->prc1522++;
	पूर्ण
पूर्ण

अटल bool e1000_tbi_should_accept(काष्ठा e1000_adapter *adapter,
				    u8 status, u8 errors,
				    u32 length, स्थिर u8 *data)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u8 last_byte = *(data + length - 1);

	अगर (TBI_ACCEPT(hw, status, errors, length, last_byte)) अणु
		अचिन्हित दीर्घ irq_flags;

		spin_lock_irqsave(&adapter->stats_lock, irq_flags);
		e1000_tbi_adjust_stats(hw, &adapter->stats, length, data);
		spin_unlock_irqrestore(&adapter->stats_lock, irq_flags);

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा sk_buff *e1000_alloc_rx_skb(काष्ठा e1000_adapter *adapter,
					  अचिन्हित पूर्णांक bufsz)
अणु
	काष्ठा sk_buff *skb = napi_alloc_skb(&adapter->napi, bufsz);

	अगर (unlikely(!skb))
		adapter->alloc_rx_buff_failed++;
	वापस skb;
पूर्ण

/**
 * e1000_clean_jumbo_rx_irq - Send received data up the network stack; legacy
 * @adapter: board निजी काष्ठाure
 * @rx_ring: ring to clean
 * @work_करोne: amount of napi work completed this call
 * @work_to_करो: max amount of work allowed क्रम this call to करो
 *
 * the वापस value indicates whether actual cleaning was करोne, there
 * is no guarantee that everything was cleaned
 */
अटल bool e1000_clean_jumbo_rx_irq(काष्ठा e1000_adapter *adapter,
				     काष्ठा e1000_rx_ring *rx_ring,
				     पूर्णांक *work_करोne, पूर्णांक work_to_करो)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा e1000_rx_desc *rx_desc, *next_rxd;
	काष्ठा e1000_rx_buffer *buffer_info, *next_buffer;
	u32 length;
	अचिन्हित पूर्णांक i;
	पूर्णांक cleaned_count = 0;
	bool cleaned = false;
	अचिन्हित पूर्णांक total_rx_bytes = 0, total_rx_packets = 0;

	i = rx_ring->next_to_clean;
	rx_desc = E1000_RX_DESC(*rx_ring, i);
	buffer_info = &rx_ring->buffer_info[i];

	जबतक (rx_desc->status & E1000_RXD_STAT_DD) अणु
		काष्ठा sk_buff *skb;
		u8 status;

		अगर (*work_करोne >= work_to_करो)
			अवरोध;
		(*work_करोne)++;
		dma_rmb(); /* पढ़ो descriptor and rx_buffer_info after status DD */

		status = rx_desc->status;

		अगर (++i == rx_ring->count)
			i = 0;

		next_rxd = E1000_RX_DESC(*rx_ring, i);
		prefetch(next_rxd);

		next_buffer = &rx_ring->buffer_info[i];

		cleaned = true;
		cleaned_count++;
		dma_unmap_page(&pdev->dev, buffer_info->dma,
			       adapter->rx_buffer_len, DMA_FROM_DEVICE);
		buffer_info->dma = 0;

		length = le16_to_cpu(rx_desc->length);

		/* errors is only valid क्रम DD + EOP descriptors */
		अगर (unlikely((status & E1000_RXD_STAT_EOP) &&
		    (rx_desc->errors & E1000_RXD_ERR_FRAME_ERR_MASK))) अणु
			u8 *mapped = page_address(buffer_info->rxbuf.page);

			अगर (e1000_tbi_should_accept(adapter, status,
						    rx_desc->errors,
						    length, mapped)) अणु
				length--;
			पूर्ण अन्यथा अगर (netdev->features & NETIF_F_RXALL) अणु
				जाओ process_skb;
			पूर्ण अन्यथा अणु
				/* an error means any chain goes out the winकरोw
				 * too
				 */
				dev_kमुक्त_skb(rx_ring->rx_skb_top);
				rx_ring->rx_skb_top = शून्य;
				जाओ next_desc;
			पूर्ण
		पूर्ण

#घोषणा rxtop rx_ring->rx_skb_top
process_skb:
		अगर (!(status & E1000_RXD_STAT_EOP)) अणु
			/* this descriptor is only the beginning (or middle) */
			अगर (!rxtop) अणु
				/* this is the beginning of a chain */
				rxtop = napi_get_frags(&adapter->napi);
				अगर (!rxtop)
					अवरोध;

				skb_fill_page_desc(rxtop, 0,
						   buffer_info->rxbuf.page,
						   0, length);
			पूर्ण अन्यथा अणु
				/* this is the middle of a chain */
				skb_fill_page_desc(rxtop,
				    skb_shinfo(rxtop)->nr_frags,
				    buffer_info->rxbuf.page, 0, length);
			पूर्ण
			e1000_consume_page(buffer_info, rxtop, length);
			जाओ next_desc;
		पूर्ण अन्यथा अणु
			अगर (rxtop) अणु
				/* end of the chain */
				skb_fill_page_desc(rxtop,
				    skb_shinfo(rxtop)->nr_frags,
				    buffer_info->rxbuf.page, 0, length);
				skb = rxtop;
				rxtop = शून्य;
				e1000_consume_page(buffer_info, skb, length);
			पूर्ण अन्यथा अणु
				काष्ठा page *p;
				/* no chain, got EOP, this buf is the packet
				 * copyअवरोध to save the put_page/alloc_page
				 */
				p = buffer_info->rxbuf.page;
				अगर (length <= copyअवरोध) अणु
					u8 *vaddr;

					अगर (likely(!(netdev->features & NETIF_F_RXFCS)))
						length -= 4;
					skb = e1000_alloc_rx_skb(adapter,
								 length);
					अगर (!skb)
						अवरोध;

					vaddr = kmap_atomic(p);
					स_नकल(skb_tail_poपूर्णांकer(skb), vaddr,
					       length);
					kunmap_atomic(vaddr);
					/* re-use the page, so करोn't erase
					 * buffer_info->rxbuf.page
					 */
					skb_put(skb, length);
					e1000_rx_checksum(adapter,
							  status | rx_desc->errors << 24,
							  le16_to_cpu(rx_desc->csum), skb);

					total_rx_bytes += skb->len;
					total_rx_packets++;

					e1000_receive_skb(adapter, status,
							  rx_desc->special, skb);
					जाओ next_desc;
				पूर्ण अन्यथा अणु
					skb = napi_get_frags(&adapter->napi);
					अगर (!skb) अणु
						adapter->alloc_rx_buff_failed++;
						अवरोध;
					पूर्ण
					skb_fill_page_desc(skb, 0, p, 0,
							   length);
					e1000_consume_page(buffer_info, skb,
							   length);
				पूर्ण
			पूर्ण
		पूर्ण

		/* Receive Checksum Offload XXX recompute due to CRC strip? */
		e1000_rx_checksum(adapter,
				  (u32)(status) |
				  ((u32)(rx_desc->errors) << 24),
				  le16_to_cpu(rx_desc->csum), skb);

		total_rx_bytes += (skb->len - 4); /* करोn't count FCS */
		अगर (likely(!(netdev->features & NETIF_F_RXFCS)))
			pskb_trim(skb, skb->len - 4);
		total_rx_packets++;

		अगर (status & E1000_RXD_STAT_VP) अणु
			__le16 vlan = rx_desc->special;
			u16 vid = le16_to_cpu(vlan) & E1000_RXD_SPC_VLAN_MASK;

			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);
		पूर्ण

		napi_gro_frags(&adapter->napi);

next_desc:
		rx_desc->status = 0;

		/* वापस some buffers to hardware, one at a समय is too slow */
		अगर (unlikely(cleaned_count >= E1000_RX_BUFFER_WRITE)) अणु
			adapter->alloc_rx_buf(adapter, rx_ring, cleaned_count);
			cleaned_count = 0;
		पूर्ण

		/* use prefetched values */
		rx_desc = next_rxd;
		buffer_info = next_buffer;
	पूर्ण
	rx_ring->next_to_clean = i;

	cleaned_count = E1000_DESC_UNUSED(rx_ring);
	अगर (cleaned_count)
		adapter->alloc_rx_buf(adapter, rx_ring, cleaned_count);

	adapter->total_rx_packets += total_rx_packets;
	adapter->total_rx_bytes += total_rx_bytes;
	netdev->stats.rx_bytes += total_rx_bytes;
	netdev->stats.rx_packets += total_rx_packets;
	वापस cleaned;
पूर्ण

/* this should improve perक्रमmance क्रम small packets with large amounts
 * of reassembly being करोne in the stack
 */
अटल काष्ठा sk_buff *e1000_copyअवरोध(काष्ठा e1000_adapter *adapter,
				       काष्ठा e1000_rx_buffer *buffer_info,
				       u32 length, स्थिर व्योम *data)
अणु
	काष्ठा sk_buff *skb;

	अगर (length > copyअवरोध)
		वापस शून्य;

	skb = e1000_alloc_rx_skb(adapter, length);
	अगर (!skb)
		वापस शून्य;

	dma_sync_single_क्रम_cpu(&adapter->pdev->dev, buffer_info->dma,
				length, DMA_FROM_DEVICE);

	skb_put_data(skb, data, length);

	वापस skb;
पूर्ण

/**
 * e1000_clean_rx_irq - Send received data up the network stack; legacy
 * @adapter: board निजी काष्ठाure
 * @rx_ring: ring to clean
 * @work_करोne: amount of napi work completed this call
 * @work_to_करो: max amount of work allowed क्रम this call to करो
 */
अटल bool e1000_clean_rx_irq(काष्ठा e1000_adapter *adapter,
			       काष्ठा e1000_rx_ring *rx_ring,
			       पूर्णांक *work_करोne, पूर्णांक work_to_करो)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा e1000_rx_desc *rx_desc, *next_rxd;
	काष्ठा e1000_rx_buffer *buffer_info, *next_buffer;
	u32 length;
	अचिन्हित पूर्णांक i;
	पूर्णांक cleaned_count = 0;
	bool cleaned = false;
	अचिन्हित पूर्णांक total_rx_bytes = 0, total_rx_packets = 0;

	i = rx_ring->next_to_clean;
	rx_desc = E1000_RX_DESC(*rx_ring, i);
	buffer_info = &rx_ring->buffer_info[i];

	जबतक (rx_desc->status & E1000_RXD_STAT_DD) अणु
		काष्ठा sk_buff *skb;
		u8 *data;
		u8 status;

		अगर (*work_करोne >= work_to_करो)
			अवरोध;
		(*work_करोne)++;
		dma_rmb(); /* पढ़ो descriptor and rx_buffer_info after status DD */

		status = rx_desc->status;
		length = le16_to_cpu(rx_desc->length);

		data = buffer_info->rxbuf.data;
		prefetch(data);
		skb = e1000_copyअवरोध(adapter, buffer_info, length, data);
		अगर (!skb) अणु
			अचिन्हित पूर्णांक frag_len = e1000_frag_len(adapter);

			skb = build_skb(data - E1000_HEADROOM, frag_len);
			अगर (!skb) अणु
				adapter->alloc_rx_buff_failed++;
				अवरोध;
			पूर्ण

			skb_reserve(skb, E1000_HEADROOM);
			dma_unmap_single(&pdev->dev, buffer_info->dma,
					 adapter->rx_buffer_len,
					 DMA_FROM_DEVICE);
			buffer_info->dma = 0;
			buffer_info->rxbuf.data = शून्य;
		पूर्ण

		अगर (++i == rx_ring->count)
			i = 0;

		next_rxd = E1000_RX_DESC(*rx_ring, i);
		prefetch(next_rxd);

		next_buffer = &rx_ring->buffer_info[i];

		cleaned = true;
		cleaned_count++;

		/* !EOP means multiple descriptors were used to store a single
		 * packet, अगर thats the हाल we need to toss it.  In fact, we
		 * to toss every packet with the EOP bit clear and the next
		 * frame that _करोes_ have the EOP bit set, as it is by
		 * definition only a frame fragment
		 */
		अगर (unlikely(!(status & E1000_RXD_STAT_EOP)))
			adapter->discarding = true;

		अगर (adapter->discarding) अणु
			/* All receives must fit पूर्णांकo a single buffer */
			netdev_dbg(netdev, "Receive packet consumed multiple buffers\n");
			dev_kमुक्त_skb(skb);
			अगर (status & E1000_RXD_STAT_EOP)
				adapter->discarding = false;
			जाओ next_desc;
		पूर्ण

		अगर (unlikely(rx_desc->errors & E1000_RXD_ERR_FRAME_ERR_MASK)) अणु
			अगर (e1000_tbi_should_accept(adapter, status,
						    rx_desc->errors,
						    length, data)) अणु
				length--;
			पूर्ण अन्यथा अगर (netdev->features & NETIF_F_RXALL) अणु
				जाओ process_skb;
			पूर्ण अन्यथा अणु
				dev_kमुक्त_skb(skb);
				जाओ next_desc;
			पूर्ण
		पूर्ण

process_skb:
		total_rx_bytes += (length - 4); /* करोn't count FCS */
		total_rx_packets++;

		अगर (likely(!(netdev->features & NETIF_F_RXFCS)))
			/* adjust length to हटाओ Ethernet CRC, this must be
			 * करोne after the TBI_ACCEPT workaround above
			 */
			length -= 4;

		अगर (buffer_info->rxbuf.data == शून्य)
			skb_put(skb, length);
		अन्यथा /* copyअवरोध skb */
			skb_trim(skb, length);

		/* Receive Checksum Offload */
		e1000_rx_checksum(adapter,
				  (u32)(status) |
				  ((u32)(rx_desc->errors) << 24),
				  le16_to_cpu(rx_desc->csum), skb);

		e1000_receive_skb(adapter, status, rx_desc->special, skb);

next_desc:
		rx_desc->status = 0;

		/* वापस some buffers to hardware, one at a समय is too slow */
		अगर (unlikely(cleaned_count >= E1000_RX_BUFFER_WRITE)) अणु
			adapter->alloc_rx_buf(adapter, rx_ring, cleaned_count);
			cleaned_count = 0;
		पूर्ण

		/* use prefetched values */
		rx_desc = next_rxd;
		buffer_info = next_buffer;
	पूर्ण
	rx_ring->next_to_clean = i;

	cleaned_count = E1000_DESC_UNUSED(rx_ring);
	अगर (cleaned_count)
		adapter->alloc_rx_buf(adapter, rx_ring, cleaned_count);

	adapter->total_rx_packets += total_rx_packets;
	adapter->total_rx_bytes += total_rx_bytes;
	netdev->stats.rx_bytes += total_rx_bytes;
	netdev->stats.rx_packets += total_rx_packets;
	वापस cleaned;
पूर्ण

/**
 * e1000_alloc_jumbo_rx_buffers - Replace used jumbo receive buffers
 * @adapter: address of board निजी काष्ठाure
 * @rx_ring: poपूर्णांकer to receive ring काष्ठाure
 * @cleaned_count: number of buffers to allocate this pass
 **/
अटल व्योम
e1000_alloc_jumbo_rx_buffers(काष्ठा e1000_adapter *adapter,
			     काष्ठा e1000_rx_ring *rx_ring, पूर्णांक cleaned_count)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा e1000_rx_desc *rx_desc;
	काष्ठा e1000_rx_buffer *buffer_info;
	अचिन्हित पूर्णांक i;

	i = rx_ring->next_to_use;
	buffer_info = &rx_ring->buffer_info[i];

	जबतक (cleaned_count--) अणु
		/* allocate a new page अगर necessary */
		अगर (!buffer_info->rxbuf.page) अणु
			buffer_info->rxbuf.page = alloc_page(GFP_ATOMIC);
			अगर (unlikely(!buffer_info->rxbuf.page)) अणु
				adapter->alloc_rx_buff_failed++;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!buffer_info->dma) अणु
			buffer_info->dma = dma_map_page(&pdev->dev,
							buffer_info->rxbuf.page, 0,
							adapter->rx_buffer_len,
							DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&pdev->dev, buffer_info->dma)) अणु
				put_page(buffer_info->rxbuf.page);
				buffer_info->rxbuf.page = शून्य;
				buffer_info->dma = 0;
				adapter->alloc_rx_buff_failed++;
				अवरोध;
			पूर्ण
		पूर्ण

		rx_desc = E1000_RX_DESC(*rx_ring, i);
		rx_desc->buffer_addr = cpu_to_le64(buffer_info->dma);

		अगर (unlikely(++i == rx_ring->count))
			i = 0;
		buffer_info = &rx_ring->buffer_info[i];
	पूर्ण

	अगर (likely(rx_ring->next_to_use != i)) अणु
		rx_ring->next_to_use = i;
		अगर (unlikely(i-- == 0))
			i = (rx_ring->count - 1);

		/* Force memory ग_लिखोs to complete beक्रमe letting h/w
		 * know there are new descriptors to fetch.  (Only
		 * applicable क्रम weak-ordered memory model archs,
		 * such as IA-64).
		 */
		dma_wmb();
		ग_लिखोl(i, adapter->hw.hw_addr + rx_ring->rdt);
	पूर्ण
पूर्ण

/**
 * e1000_alloc_rx_buffers - Replace used receive buffers; legacy & extended
 * @adapter: address of board निजी काष्ठाure
 * @rx_ring: poपूर्णांकer to ring काष्ठा
 * @cleaned_count: number of new Rx buffers to try to allocate
 **/
अटल व्योम e1000_alloc_rx_buffers(काष्ठा e1000_adapter *adapter,
				   काष्ठा e1000_rx_ring *rx_ring,
				   पूर्णांक cleaned_count)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा e1000_rx_desc *rx_desc;
	काष्ठा e1000_rx_buffer *buffer_info;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक bufsz = adapter->rx_buffer_len;

	i = rx_ring->next_to_use;
	buffer_info = &rx_ring->buffer_info[i];

	जबतक (cleaned_count--) अणु
		व्योम *data;

		अगर (buffer_info->rxbuf.data)
			जाओ skip;

		data = e1000_alloc_frag(adapter);
		अगर (!data) अणु
			/* Better luck next round */
			adapter->alloc_rx_buff_failed++;
			अवरोध;
		पूर्ण

		/* Fix क्रम errata 23, can't cross 64kB boundary */
		अगर (!e1000_check_64k_bound(adapter, data, bufsz)) अणु
			व्योम *olddata = data;
			e_err(rx_err, "skb align check failed: %u bytes at "
			      "%p\n", bufsz, data);
			/* Try again, without मुक्तing the previous */
			data = e1000_alloc_frag(adapter);
			/* Failed allocation, critical failure */
			अगर (!data) अणु
				skb_मुक्त_frag(olddata);
				adapter->alloc_rx_buff_failed++;
				अवरोध;
			पूर्ण

			अगर (!e1000_check_64k_bound(adapter, data, bufsz)) अणु
				/* give up */
				skb_मुक्त_frag(data);
				skb_मुक्त_frag(olddata);
				adapter->alloc_rx_buff_failed++;
				अवरोध;
			पूर्ण

			/* Use new allocation */
			skb_मुक्त_frag(olddata);
		पूर्ण
		buffer_info->dma = dma_map_single(&pdev->dev,
						  data,
						  adapter->rx_buffer_len,
						  DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&pdev->dev, buffer_info->dma)) अणु
			skb_मुक्त_frag(data);
			buffer_info->dma = 0;
			adapter->alloc_rx_buff_failed++;
			अवरोध;
		पूर्ण

		/* XXX अगर it was allocated cleanly it will never map to a
		 * boundary crossing
		 */

		/* Fix क्रम errata 23, can't cross 64kB boundary */
		अगर (!e1000_check_64k_bound(adapter,
					(व्योम *)(अचिन्हित दीर्घ)buffer_info->dma,
					adapter->rx_buffer_len)) अणु
			e_err(rx_err, "dma align check failed: %u bytes at "
			      "%p\n", adapter->rx_buffer_len,
			      (व्योम *)(अचिन्हित दीर्घ)buffer_info->dma);

			dma_unmap_single(&pdev->dev, buffer_info->dma,
					 adapter->rx_buffer_len,
					 DMA_FROM_DEVICE);

			skb_मुक्त_frag(data);
			buffer_info->rxbuf.data = शून्य;
			buffer_info->dma = 0;

			adapter->alloc_rx_buff_failed++;
			अवरोध;
		पूर्ण
		buffer_info->rxbuf.data = data;
 skip:
		rx_desc = E1000_RX_DESC(*rx_ring, i);
		rx_desc->buffer_addr = cpu_to_le64(buffer_info->dma);

		अगर (unlikely(++i == rx_ring->count))
			i = 0;
		buffer_info = &rx_ring->buffer_info[i];
	पूर्ण

	अगर (likely(rx_ring->next_to_use != i)) अणु
		rx_ring->next_to_use = i;
		अगर (unlikely(i-- == 0))
			i = (rx_ring->count - 1);

		/* Force memory ग_लिखोs to complete beक्रमe letting h/w
		 * know there are new descriptors to fetch.  (Only
		 * applicable क्रम weak-ordered memory model archs,
		 * such as IA-64).
		 */
		dma_wmb();
		ग_लिखोl(i, hw->hw_addr + rx_ring->rdt);
	पूर्ण
पूर्ण

/**
 * e1000_smartspeed - Workaround क्रम SmartSpeed on 82541 and 82547 controllers.
 * @adapter: address of board निजी काष्ठाure
 **/
अटल व्योम e1000_smartspeed(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 phy_status;
	u16 phy_ctrl;

	अगर ((hw->phy_type != e1000_phy_igp) || !hw->स्वतःneg ||
	   !(hw->स्वतःneg_advertised & ADVERTISE_1000_FULL))
		वापस;

	अगर (adapter->smartspeed == 0) अणु
		/* If Master/Slave config fault is निश्चितed twice,
		 * we assume back-to-back
		 */
		e1000_पढ़ो_phy_reg(hw, PHY_1000T_STATUS, &phy_status);
		अगर (!(phy_status & SR_1000T_MS_CONFIG_FAULT))
			वापस;
		e1000_पढ़ो_phy_reg(hw, PHY_1000T_STATUS, &phy_status);
		अगर (!(phy_status & SR_1000T_MS_CONFIG_FAULT))
			वापस;
		e1000_पढ़ो_phy_reg(hw, PHY_1000T_CTRL, &phy_ctrl);
		अगर (phy_ctrl & CR_1000T_MS_ENABLE) अणु
			phy_ctrl &= ~CR_1000T_MS_ENABLE;
			e1000_ग_लिखो_phy_reg(hw, PHY_1000T_CTRL,
					    phy_ctrl);
			adapter->smartspeed++;
			अगर (!e1000_phy_setup_स्वतःneg(hw) &&
			   !e1000_पढ़ो_phy_reg(hw, PHY_CTRL,
					       &phy_ctrl)) अणु
				phy_ctrl |= (MII_CR_AUTO_NEG_EN |
					     MII_CR_RESTART_AUTO_NEG);
				e1000_ग_लिखो_phy_reg(hw, PHY_CTRL,
						    phy_ctrl);
			पूर्ण
		पूर्ण
		वापस;
	पूर्ण अन्यथा अगर (adapter->smartspeed == E1000_SMARTSPEED_DOWNSHIFT) अणु
		/* If still no link, perhaps using 2/3 pair cable */
		e1000_पढ़ो_phy_reg(hw, PHY_1000T_CTRL, &phy_ctrl);
		phy_ctrl |= CR_1000T_MS_ENABLE;
		e1000_ग_लिखो_phy_reg(hw, PHY_1000T_CTRL, phy_ctrl);
		अगर (!e1000_phy_setup_स्वतःneg(hw) &&
		   !e1000_पढ़ो_phy_reg(hw, PHY_CTRL, &phy_ctrl)) अणु
			phy_ctrl |= (MII_CR_AUTO_NEG_EN |
				     MII_CR_RESTART_AUTO_NEG);
			e1000_ग_लिखो_phy_reg(hw, PHY_CTRL, phy_ctrl);
		पूर्ण
	पूर्ण
	/* Restart process after E1000_SMARTSPEED_MAX iterations */
	अगर (adapter->smartspeed++ == E1000_SMARTSPEED_MAX)
		adapter->smartspeed = 0;
पूर्ण

/**
 * e1000_ioctl - handle ioctl calls
 * @netdev: poपूर्णांकer to our netdev
 * @अगरr: poपूर्णांकer to पूर्णांकerface request काष्ठाure
 * @cmd: ioctl data
 **/
अटल पूर्णांक e1000_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
	हाल SIOCGMIIREG:
	हाल SIOCSMIIREG:
		वापस e1000_mii_ioctl(netdev, अगरr, cmd);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/**
 * e1000_mii_ioctl -
 * @netdev: poपूर्णांकer to our netdev
 * @अगरr: poपूर्णांकer to पूर्णांकerface request काष्ठाure
 * @cmd: ioctl data
 **/
अटल पूर्णांक e1000_mii_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr,
			   पूर्णांक cmd)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);
	पूर्णांक retval;
	u16 mii_reg;
	अचिन्हित दीर्घ flags;

	अगर (hw->media_type != e1000_media_type_copper)
		वापस -EOPNOTSUPP;

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		data->phy_id = hw->phy_addr;
		अवरोध;
	हाल SIOCGMIIREG:
		spin_lock_irqsave(&adapter->stats_lock, flags);
		अगर (e1000_पढ़ो_phy_reg(hw, data->reg_num & 0x1F,
				   &data->val_out)) अणु
			spin_unlock_irqrestore(&adapter->stats_lock, flags);
			वापस -EIO;
		पूर्ण
		spin_unlock_irqrestore(&adapter->stats_lock, flags);
		अवरोध;
	हाल SIOCSMIIREG:
		अगर (data->reg_num & ~(0x1F))
			वापस -EFAULT;
		mii_reg = data->val_in;
		spin_lock_irqsave(&adapter->stats_lock, flags);
		अगर (e1000_ग_लिखो_phy_reg(hw, data->reg_num,
					mii_reg)) अणु
			spin_unlock_irqrestore(&adapter->stats_lock, flags);
			वापस -EIO;
		पूर्ण
		spin_unlock_irqrestore(&adapter->stats_lock, flags);
		अगर (hw->media_type == e1000_media_type_copper) अणु
			चयन (data->reg_num) अणु
			हाल PHY_CTRL:
				अगर (mii_reg & MII_CR_POWER_DOWN)
					अवरोध;
				अगर (mii_reg & MII_CR_AUTO_NEG_EN) अणु
					hw->स्वतःneg = 1;
					hw->स्वतःneg_advertised = 0x2F;
				पूर्ण अन्यथा अणु
					u32 speed;
					अगर (mii_reg & 0x40)
						speed = SPEED_1000;
					अन्यथा अगर (mii_reg & 0x2000)
						speed = SPEED_100;
					अन्यथा
						speed = SPEED_10;
					retval = e1000_set_spd_dplx(
						adapter, speed,
						((mii_reg & 0x100)
						 ? DUPLEX_FULL :
						 DUPLEX_HALF));
					अगर (retval)
						वापस retval;
				पूर्ण
				अगर (netअगर_running(adapter->netdev))
					e1000_reinit_locked(adapter);
				अन्यथा
					e1000_reset(adapter);
				अवरोध;
			हाल M88E1000_PHY_SPEC_CTRL:
			हाल M88E1000_EXT_PHY_SPEC_CTRL:
				अगर (e1000_phy_reset(hw))
					वापस -EIO;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (data->reg_num) अणु
			हाल PHY_CTRL:
				अगर (mii_reg & MII_CR_POWER_DOWN)
					अवरोध;
				अगर (netअगर_running(adapter->netdev))
					e1000_reinit_locked(adapter);
				अन्यथा
					e1000_reset(adapter);
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस E1000_SUCCESS;
पूर्ण

व्योम e1000_pci_set_mwi(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_adapter *adapter = hw->back;
	पूर्णांक ret_val = pci_set_mwi(adapter->pdev);

	अगर (ret_val)
		e_err(probe, "Error in setting MWI\n");
पूर्ण

व्योम e1000_pci_clear_mwi(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_adapter *adapter = hw->back;

	pci_clear_mwi(adapter->pdev);
पूर्ण

पूर्णांक e1000_pcix_get_mmrbc(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_adapter *adapter = hw->back;
	वापस pcix_get_mmrbc(adapter->pdev);
पूर्ण

व्योम e1000_pcix_set_mmrbc(काष्ठा e1000_hw *hw, पूर्णांक mmrbc)
अणु
	काष्ठा e1000_adapter *adapter = hw->back;
	pcix_set_mmrbc(adapter->pdev, mmrbc);
पूर्ण

व्योम e1000_io_ग_लिखो(काष्ठा e1000_hw *hw, अचिन्हित दीर्घ port, u32 value)
अणु
	outl(value, port);
पूर्ण

अटल bool e1000_vlan_used(काष्ठा e1000_adapter *adapter)
अणु
	u16 vid;

	क्रम_each_set_bit(vid, adapter->active_vlans, VLAN_N_VID)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम __e1000_vlan_mode(काष्ठा e1000_adapter *adapter,
			      netdev_features_t features)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl;

	ctrl = er32(CTRL);
	अगर (features & NETIF_F_HW_VLAN_CTAG_RX) अणु
		/* enable VLAN tag insert/strip */
		ctrl |= E1000_CTRL_VME;
	पूर्ण अन्यथा अणु
		/* disable VLAN tag insert/strip */
		ctrl &= ~E1000_CTRL_VME;
	पूर्ण
	ew32(CTRL, ctrl);
पूर्ण
अटल व्योम e1000_vlan_filter_on_off(काष्ठा e1000_adapter *adapter,
				     bool filter_on)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rctl;

	अगर (!test_bit(__E1000_DOWN, &adapter->flags))
		e1000_irq_disable(adapter);

	__e1000_vlan_mode(adapter, adapter->netdev->features);
	अगर (filter_on) अणु
		/* enable VLAN receive filtering */
		rctl = er32(RCTL);
		rctl &= ~E1000_RCTL_CFIEN;
		अगर (!(adapter->netdev->flags & IFF_PROMISC))
			rctl |= E1000_RCTL_VFE;
		ew32(RCTL, rctl);
		e1000_update_mng_vlan(adapter);
	पूर्ण अन्यथा अणु
		/* disable VLAN receive filtering */
		rctl = er32(RCTL);
		rctl &= ~E1000_RCTL_VFE;
		ew32(RCTL, rctl);
	पूर्ण

	अगर (!test_bit(__E1000_DOWN, &adapter->flags))
		e1000_irq_enable(adapter);
पूर्ण

अटल व्योम e1000_vlan_mode(काष्ठा net_device *netdev,
			    netdev_features_t features)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	अगर (!test_bit(__E1000_DOWN, &adapter->flags))
		e1000_irq_disable(adapter);

	__e1000_vlan_mode(adapter, features);

	अगर (!test_bit(__E1000_DOWN, &adapter->flags))
		e1000_irq_enable(adapter);
पूर्ण

अटल पूर्णांक e1000_vlan_rx_add_vid(काष्ठा net_device *netdev,
				 __be16 proto, u16 vid)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 vfta, index;

	अगर ((hw->mng_cookie.status &
	     E1000_MNG_DHCP_COOKIE_STATUS_VLAN_SUPPORT) &&
	    (vid == adapter->mng_vlan_id))
		वापस 0;

	अगर (!e1000_vlan_used(adapter))
		e1000_vlan_filter_on_off(adapter, true);

	/* add VID to filter table */
	index = (vid >> 5) & 0x7F;
	vfta = E1000_READ_REG_ARRAY(hw, VFTA, index);
	vfta |= (1 << (vid & 0x1F));
	e1000_ग_लिखो_vfta(hw, index, vfta);

	set_bit(vid, adapter->active_vlans);

	वापस 0;
पूर्ण

अटल पूर्णांक e1000_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
				  __be16 proto, u16 vid)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 vfta, index;

	अगर (!test_bit(__E1000_DOWN, &adapter->flags))
		e1000_irq_disable(adapter);
	अगर (!test_bit(__E1000_DOWN, &adapter->flags))
		e1000_irq_enable(adapter);

	/* हटाओ VID from filter table */
	index = (vid >> 5) & 0x7F;
	vfta = E1000_READ_REG_ARRAY(hw, VFTA, index);
	vfta &= ~(1 << (vid & 0x1F));
	e1000_ग_लिखो_vfta(hw, index, vfta);

	clear_bit(vid, adapter->active_vlans);

	अगर (!e1000_vlan_used(adapter))
		e1000_vlan_filter_on_off(adapter, false);

	वापस 0;
पूर्ण

अटल व्योम e1000_restore_vlan(काष्ठा e1000_adapter *adapter)
अणु
	u16 vid;

	अगर (!e1000_vlan_used(adapter))
		वापस;

	e1000_vlan_filter_on_off(adapter, true);
	क्रम_each_set_bit(vid, adapter->active_vlans, VLAN_N_VID)
		e1000_vlan_rx_add_vid(adapter->netdev, htons(ETH_P_8021Q), vid);
पूर्ण

पूर्णांक e1000_set_spd_dplx(काष्ठा e1000_adapter *adapter, u32 spd, u8 dplx)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	hw->स्वतःneg = 0;

	/* Make sure dplx is at most 1 bit and lsb of speed is not set
	 * क्रम the चयन() below to work
	 */
	अगर ((spd & 1) || (dplx & ~1))
		जाओ err_inval;

	/* Fiber NICs only allow 1000 gbps Full duplex */
	अगर ((hw->media_type == e1000_media_type_fiber) &&
	    spd != SPEED_1000 &&
	    dplx != DUPLEX_FULL)
		जाओ err_inval;

	चयन (spd + dplx) अणु
	हाल SPEED_10 + DUPLEX_HALF:
		hw->क्रमced_speed_duplex = e1000_10_half;
		अवरोध;
	हाल SPEED_10 + DUPLEX_FULL:
		hw->क्रमced_speed_duplex = e1000_10_full;
		अवरोध;
	हाल SPEED_100 + DUPLEX_HALF:
		hw->क्रमced_speed_duplex = e1000_100_half;
		अवरोध;
	हाल SPEED_100 + DUPLEX_FULL:
		hw->क्रमced_speed_duplex = e1000_100_full;
		अवरोध;
	हाल SPEED_1000 + DUPLEX_FULL:
		hw->स्वतःneg = 1;
		hw->स्वतःneg_advertised = ADVERTISE_1000_FULL;
		अवरोध;
	हाल SPEED_1000 + DUPLEX_HALF: /* not supported */
	शेष:
		जाओ err_inval;
	पूर्ण

	/* clear MDI, MDI(-X) override is only allowed when स्वतःneg enabled */
	hw->mdix = AUTO_ALL_MODES;

	वापस 0;

err_inval:
	e_err(probe, "Unsupported Speed/Duplex configuration\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __e1000_shutकरोwn(काष्ठा pci_dev *pdev, bool *enable_wake)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl, ctrl_ext, rctl, status;
	u32 wufc = adapter->wol;

	netअगर_device_detach(netdev);

	अगर (netअगर_running(netdev)) अणु
		पूर्णांक count = E1000_CHECK_RESET_COUNT;

		जबतक (test_bit(__E1000_RESETTING, &adapter->flags) && count--)
			usleep_range(10000, 20000);

		WARN_ON(test_bit(__E1000_RESETTING, &adapter->flags));
		e1000_करोwn(adapter);
	पूर्ण

	status = er32(STATUS);
	अगर (status & E1000_STATUS_LU)
		wufc &= ~E1000_WUFC_LNKC;

	अगर (wufc) अणु
		e1000_setup_rctl(adapter);
		e1000_set_rx_mode(netdev);

		rctl = er32(RCTL);

		/* turn on all-multi mode अगर wake on multicast is enabled */
		अगर (wufc & E1000_WUFC_MC)
			rctl |= E1000_RCTL_MPE;

		/* enable receives in the hardware */
		ew32(RCTL, rctl | E1000_RCTL_EN);

		अगर (hw->mac_type >= e1000_82540) अणु
			ctrl = er32(CTRL);
			/* advertise wake from D3Cold */
			#घोषणा E1000_CTRL_ADVD3WUC 0x00100000
			/* phy घातer management enable */
			#घोषणा E1000_CTRL_EN_PHY_PWR_MGMT 0x00200000
			ctrl |= E1000_CTRL_ADVD3WUC |
				E1000_CTRL_EN_PHY_PWR_MGMT;
			ew32(CTRL, ctrl);
		पूर्ण

		अगर (hw->media_type == e1000_media_type_fiber ||
		    hw->media_type == e1000_media_type_पूर्णांकernal_serdes) अणु
			/* keep the laser running in D3 */
			ctrl_ext = er32(CTRL_EXT);
			ctrl_ext |= E1000_CTRL_EXT_SDP7_DATA;
			ew32(CTRL_EXT, ctrl_ext);
		पूर्ण

		ew32(WUC, E1000_WUC_PME_EN);
		ew32(WUFC, wufc);
	पूर्ण अन्यथा अणु
		ew32(WUC, 0);
		ew32(WUFC, 0);
	पूर्ण

	e1000_release_manageability(adapter);

	*enable_wake = !!wufc;

	/* make sure adapter isn't asleep अगर manageability is enabled */
	अगर (adapter->en_mng_pt)
		*enable_wake = true;

	अगर (netअगर_running(netdev))
		e1000_मुक्त_irq(adapter);

	अगर (!test_and_set_bit(__E1000_DISABLED, &adapter->flags))
		pci_disable_device(pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused e1000_suspend(काष्ठा device *dev)
अणु
	पूर्णांक retval;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	bool wake;

	retval = __e1000_shutकरोwn(pdev, &wake);
	device_set_wakeup_enable(dev, wake);

	वापस retval;
पूर्ण

अटल पूर्णांक __maybe_unused e1000_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 err;

	अगर (adapter->need_ioport)
		err = pci_enable_device(pdev);
	अन्यथा
		err = pci_enable_device_mem(pdev);
	अगर (err) अणु
		pr_err("Cannot enable PCI device from suspend\n");
		वापस err;
	पूर्ण

	/* flush memory to make sure state is correct */
	smp_mb__beक्रमe_atomic();
	clear_bit(__E1000_DISABLED, &adapter->flags);
	pci_set_master(pdev);

	pci_enable_wake(pdev, PCI_D3hot, 0);
	pci_enable_wake(pdev, PCI_D3cold, 0);

	अगर (netअगर_running(netdev)) अणु
		err = e1000_request_irq(adapter);
		अगर (err)
			वापस err;
	पूर्ण

	e1000_घातer_up_phy(adapter);
	e1000_reset(adapter);
	ew32(WUS, ~0);

	e1000_init_manageability(adapter);

	अगर (netअगर_running(netdev))
		e1000_up(adapter);

	netअगर_device_attach(netdev);

	वापस 0;
पूर्ण

अटल व्योम e1000_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	bool wake;

	__e1000_shutकरोwn(pdev, &wake);

	अगर (प्रणाली_state == SYSTEM_POWER_OFF) अणु
		pci_wake_from_d3(pdev, wake);
		pci_set_घातer_state(pdev, PCI_D3hot);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/* Polling 'interrupt' - used by things like netconsole to send skbs
 * without having to re-enable पूर्णांकerrupts. It's not called जबतक
 * the पूर्णांकerrupt routine is executing.
 */
अटल व्योम e1000_netpoll(काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	अगर (disable_hardirq(adapter->pdev->irq))
		e1000_पूर्णांकr(adapter->pdev->irq, netdev);
	enable_irq(adapter->pdev->irq);
पूर्ण
#पूर्ण_अगर

/**
 * e1000_io_error_detected - called when PCI error is detected
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 *
 * This function is called after a PCI bus error affecting
 * this device has been detected.
 */
अटल pci_ers_result_t e1000_io_error_detected(काष्ठा pci_dev *pdev,
						pci_channel_state_t state)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	netअगर_device_detach(netdev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	अगर (netअगर_running(netdev))
		e1000_करोwn(adapter);

	अगर (!test_and_set_bit(__E1000_DISABLED, &adapter->flags))
		pci_disable_device(pdev);

	/* Request a slot slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * e1000_io_slot_reset - called after the pci bus has been reset.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Restart the card from scratch, as अगर from a cold-boot. Implementation
 * resembles the first-half of the e1000_resume routine.
 */
अटल pci_ers_result_t e1000_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक err;

	अगर (adapter->need_ioport)
		err = pci_enable_device(pdev);
	अन्यथा
		err = pci_enable_device_mem(pdev);
	अगर (err) अणु
		pr_err("Cannot re-enable PCI device after reset.\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	/* flush memory to make sure state is correct */
	smp_mb__beक्रमe_atomic();
	clear_bit(__E1000_DISABLED, &adapter->flags);
	pci_set_master(pdev);

	pci_enable_wake(pdev, PCI_D3hot, 0);
	pci_enable_wake(pdev, PCI_D3cold, 0);

	e1000_reset(adapter);
	ew32(WUS, ~0);

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * e1000_io_resume - called when traffic can start flowing again.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called when the error recovery driver tells us that
 * its OK to resume normal operation. Implementation resembles the
 * second-half of the e1000_resume routine.
 */
अटल व्योम e1000_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	e1000_init_manageability(adapter);

	अगर (netअगर_running(netdev)) अणु
		अगर (e1000_up(adapter)) अणु
			pr_info("can't bring device back up after reset\n");
			वापस;
		पूर्ण
	पूर्ण

	netअगर_device_attach(netdev);
पूर्ण

/* e1000_मुख्य.c */
