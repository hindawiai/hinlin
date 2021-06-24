<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2008 Intel Corporation. */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/prefetch.h>
#समावेश "ixgb.h"

अक्षर ixgb_driver_name[] = "ixgb";
अटल अक्षर ixgb_driver_string[] = "Intel(R) PRO/10GbE Network Driver";

अटल स्थिर अक्षर ixgb_copyright[] = "Copyright (c) 1999-2008 Intel Corporation.";

#घोषणा IXGB_CB_LENGTH 256
अटल अचिन्हित पूर्णांक copyअवरोध __पढ़ो_mostly = IXGB_CB_LENGTH;
module_param(copyअवरोध, uपूर्णांक, 0644);
MODULE_PARM_DESC(copyअवरोध,
	"Maximum size of packet that is copied to a new buffer on receive");

/* ixgb_pci_tbl - PCI Device ID Table
 *
 * Wildcard entries (PCI_ANY_ID) should come last
 * Last entry must be all 0s
 *
 * अणु Venकरोr ID, Device ID, SubVenकरोr ID, SubDevice ID,
 *   Class, Class Mask, निजी data (not used) पूर्ण
 */
अटल स्थिर काष्ठा pci_device_id ixgb_pci_tbl[] = अणु
	अणुPCI_VENDOR_ID_INTEL, IXGB_DEVICE_ID_82597EX,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, IXGB_DEVICE_ID_82597EX_CX4,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, IXGB_DEVICE_ID_82597EX_SR,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, IXGB_DEVICE_ID_82597EX_LR,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,

	/* required last entry */
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, ixgb_pci_tbl);

/* Local Function Prototypes */
अटल पूर्णांक ixgb_init_module(व्योम);
अटल व्योम ixgb_निकास_module(व्योम);
अटल पूर्णांक ixgb_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
अटल व्योम ixgb_हटाओ(काष्ठा pci_dev *pdev);
अटल पूर्णांक ixgb_sw_init(काष्ठा ixgb_adapter *adapter);
अटल पूर्णांक ixgb_खोलो(काष्ठा net_device *netdev);
अटल पूर्णांक ixgb_बंद(काष्ठा net_device *netdev);
अटल व्योम ixgb_configure_tx(काष्ठा ixgb_adapter *adapter);
अटल व्योम ixgb_configure_rx(काष्ठा ixgb_adapter *adapter);
अटल व्योम ixgb_setup_rctl(काष्ठा ixgb_adapter *adapter);
अटल व्योम ixgb_clean_tx_ring(काष्ठा ixgb_adapter *adapter);
अटल व्योम ixgb_clean_rx_ring(काष्ठा ixgb_adapter *adapter);
अटल व्योम ixgb_set_multi(काष्ठा net_device *netdev);
अटल व्योम ixgb_watchकरोg(काष्ठा समयr_list *t);
अटल netdev_tx_t ixgb_xmit_frame(काष्ठा sk_buff *skb,
				   काष्ठा net_device *netdev);
अटल पूर्णांक ixgb_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu);
अटल पूर्णांक ixgb_set_mac(काष्ठा net_device *netdev, व्योम *p);
अटल irqवापस_t ixgb_पूर्णांकr(पूर्णांक irq, व्योम *data);
अटल bool ixgb_clean_tx_irq(काष्ठा ixgb_adapter *adapter);

अटल पूर्णांक ixgb_clean(काष्ठा napi_काष्ठा *, पूर्णांक);
अटल bool ixgb_clean_rx_irq(काष्ठा ixgb_adapter *, पूर्णांक *, पूर्णांक);
अटल व्योम ixgb_alloc_rx_buffers(काष्ठा ixgb_adapter *, पूर्णांक);

अटल व्योम ixgb_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम ixgb_tx_समयout_task(काष्ठा work_काष्ठा *work);

अटल व्योम ixgb_vlan_strip_enable(काष्ठा ixgb_adapter *adapter);
अटल व्योम ixgb_vlan_strip_disable(काष्ठा ixgb_adapter *adapter);
अटल पूर्णांक ixgb_vlan_rx_add_vid(काष्ठा net_device *netdev,
				__be16 proto, u16 vid);
अटल पूर्णांक ixgb_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
				 __be16 proto, u16 vid);
अटल व्योम ixgb_restore_vlan(काष्ठा ixgb_adapter *adapter);

अटल pci_ers_result_t ixgb_io_error_detected (काष्ठा pci_dev *pdev,
                             pci_channel_state_t state);
अटल pci_ers_result_t ixgb_io_slot_reset (काष्ठा pci_dev *pdev);
अटल व्योम ixgb_io_resume (काष्ठा pci_dev *pdev);

अटल स्थिर काष्ठा pci_error_handlers ixgb_err_handler = अणु
	.error_detected = ixgb_io_error_detected,
	.slot_reset = ixgb_io_slot_reset,
	.resume = ixgb_io_resume,
पूर्ण;

अटल काष्ठा pci_driver ixgb_driver = अणु
	.name     = ixgb_driver_name,
	.id_table = ixgb_pci_tbl,
	.probe    = ixgb_probe,
	.हटाओ   = ixgb_हटाओ,
	.err_handler = &ixgb_err_handler
पूर्ण;

MODULE_AUTHOR("Intel Corporation, <linux.nics@intel.com>");
MODULE_DESCRIPTION("Intel(R) PRO/10GbE Network Driver");
MODULE_LICENSE("GPL v2");

#घोषणा DEFAULT_MSG_ENABLE (NETIF_MSG_DRV|NETIF_MSG_PROBE|NETIF_MSG_LINK)
अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");

/**
 * ixgb_init_module - Driver Registration Routine
 *
 * ixgb_init_module is the first routine called when the driver is
 * loaded. All it करोes is रेजिस्टर with the PCI subप्रणाली.
 **/

अटल पूर्णांक __init
ixgb_init_module(व्योम)
अणु
	pr_info("%s\n", ixgb_driver_string);
	pr_info("%s\n", ixgb_copyright);

	वापस pci_रेजिस्टर_driver(&ixgb_driver);
पूर्ण

module_init(ixgb_init_module);

/**
 * ixgb_निकास_module - Driver Exit Cleanup Routine
 *
 * ixgb_निकास_module is called just beक्रमe the driver is हटाओd
 * from memory.
 **/

अटल व्योम __निकास
ixgb_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ixgb_driver);
पूर्ण

module_निकास(ixgb_निकास_module);

/**
 * ixgb_irq_disable - Mask off पूर्णांकerrupt generation on the NIC
 * @adapter: board निजी काष्ठाure
 **/

अटल व्योम
ixgb_irq_disable(काष्ठा ixgb_adapter *adapter)
अणु
	IXGB_WRITE_REG(&adapter->hw, IMC, ~0);
	IXGB_WRITE_FLUSH(&adapter->hw);
	synchronize_irq(adapter->pdev->irq);
पूर्ण

/**
 * ixgb_irq_enable - Enable शेष पूर्णांकerrupt generation settings
 * @adapter: board निजी काष्ठाure
 **/

अटल व्योम
ixgb_irq_enable(काष्ठा ixgb_adapter *adapter)
अणु
	u32 val = IXGB_INT_RXT0 | IXGB_INT_RXDMT0 |
		  IXGB_INT_TXDW | IXGB_INT_LSC;
	अगर (adapter->hw.subप्रणाली_venकरोr_id == PCI_VENDOR_ID_SUN)
		val |= IXGB_INT_GPI0;
	IXGB_WRITE_REG(&adapter->hw, IMS, val);
	IXGB_WRITE_FLUSH(&adapter->hw);
पूर्ण

पूर्णांक
ixgb_up(काष्ठा ixgb_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err, irq_flags = IRQF_SHARED;
	पूर्णांक max_frame = netdev->mtu + ENET_HEADER_SIZE + ENET_FCS_LENGTH;
	काष्ठा ixgb_hw *hw = &adapter->hw;

	/* hardware has been reset, we need to reload some things */

	ixgb_rar_set(hw, netdev->dev_addr, 0);
	ixgb_set_multi(netdev);

	ixgb_restore_vlan(adapter);

	ixgb_configure_tx(adapter);
	ixgb_setup_rctl(adapter);
	ixgb_configure_rx(adapter);
	ixgb_alloc_rx_buffers(adapter, IXGB_DESC_UNUSED(&adapter->rx_ring));

	/* disable पूर्णांकerrupts and get the hardware पूर्णांकo a known state */
	IXGB_WRITE_REG(&adapter->hw, IMC, 0xffffffff);

	/* only enable MSI अगर bus is in PCI-X mode */
	अगर (IXGB_READ_REG(&adapter->hw, STATUS) & IXGB_STATUS_PCIX_MODE) अणु
		err = pci_enable_msi(adapter->pdev);
		अगर (!err) अणु
			adapter->have_msi = true;
			irq_flags = 0;
		पूर्ण
		/* proceed to try to request regular पूर्णांकerrupt */
	पूर्ण

	err = request_irq(adapter->pdev->irq, ixgb_पूर्णांकr, irq_flags,
	                  netdev->name, netdev);
	अगर (err) अणु
		अगर (adapter->have_msi)
			pci_disable_msi(adapter->pdev);
		netअगर_err(adapter, probe, adapter->netdev,
			  "Unable to allocate interrupt Error: %d\n", err);
		वापस err;
	पूर्ण

	अगर ((hw->max_frame_size != max_frame) ||
		(hw->max_frame_size !=
		(IXGB_READ_REG(hw, MFS) >> IXGB_MFS_SHIFT))) अणु

		hw->max_frame_size = max_frame;

		IXGB_WRITE_REG(hw, MFS, hw->max_frame_size << IXGB_MFS_SHIFT);

		अगर (hw->max_frame_size >
		   IXGB_MAX_ENET_FRAME_SIZE_WITHOUT_FCS + ENET_FCS_LENGTH) अणु
			u32 ctrl0 = IXGB_READ_REG(hw, CTRL0);

			अगर (!(ctrl0 & IXGB_CTRL0_JFE)) अणु
				ctrl0 |= IXGB_CTRL0_JFE;
				IXGB_WRITE_REG(hw, CTRL0, ctrl0);
			पूर्ण
		पूर्ण
	पूर्ण

	clear_bit(__IXGB_DOWN, &adapter->flags);

	napi_enable(&adapter->napi);
	ixgb_irq_enable(adapter);

	netअगर_wake_queue(netdev);

	mod_समयr(&adapter->watchकरोg_समयr, jअगरfies);

	वापस 0;
पूर्ण

व्योम
ixgb_करोwn(काष्ठा ixgb_adapter *adapter, bool समाप्त_watchकरोg)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	/* prevent the पूर्णांकerrupt handler from restarting watchकरोg */
	set_bit(__IXGB_DOWN, &adapter->flags);

	netअगर_carrier_off(netdev);

	napi_disable(&adapter->napi);
	/* रुकोing क्रम NAPI to complete can re-enable पूर्णांकerrupts */
	ixgb_irq_disable(adapter);
	मुक्त_irq(adapter->pdev->irq, netdev);

	अगर (adapter->have_msi)
		pci_disable_msi(adapter->pdev);

	अगर (समाप्त_watchकरोg)
		del_समयr_sync(&adapter->watchकरोg_समयr);

	adapter->link_speed = 0;
	adapter->link_duplex = 0;
	netअगर_stop_queue(netdev);

	ixgb_reset(adapter);
	ixgb_clean_tx_ring(adapter);
	ixgb_clean_rx_ring(adapter);
पूर्ण

व्योम
ixgb_reset(काष्ठा ixgb_adapter *adapter)
अणु
	काष्ठा ixgb_hw *hw = &adapter->hw;

	ixgb_adapter_stop(hw);
	अगर (!ixgb_init_hw(hw))
		netअगर_err(adapter, probe, adapter->netdev, "ixgb_init_hw failed\n");

	/* restore frame size inक्रमmation */
	IXGB_WRITE_REG(hw, MFS, hw->max_frame_size << IXGB_MFS_SHIFT);
	अगर (hw->max_frame_size >
	    IXGB_MAX_ENET_FRAME_SIZE_WITHOUT_FCS + ENET_FCS_LENGTH) अणु
		u32 ctrl0 = IXGB_READ_REG(hw, CTRL0);
		अगर (!(ctrl0 & IXGB_CTRL0_JFE)) अणु
			ctrl0 |= IXGB_CTRL0_JFE;
			IXGB_WRITE_REG(hw, CTRL0, ctrl0);
		पूर्ण
	पूर्ण
पूर्ण

अटल netdev_features_t
ixgb_fix_features(काष्ठा net_device *netdev, netdev_features_t features)
अणु
	/*
	 * Tx VLAN insertion करोes not work per HW design when Rx stripping is
	 * disabled.
	 */
	अगर (!(features & NETIF_F_HW_VLAN_CTAG_RX))
		features &= ~NETIF_F_HW_VLAN_CTAG_TX;

	वापस features;
पूर्ण

अटल पूर्णांक
ixgb_set_features(काष्ठा net_device *netdev, netdev_features_t features)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	netdev_features_t changed = features ^ netdev->features;

	अगर (!(changed & (NETIF_F_RXCSUM|NETIF_F_HW_VLAN_CTAG_RX)))
		वापस 0;

	adapter->rx_csum = !!(features & NETIF_F_RXCSUM);

	अगर (netअगर_running(netdev)) अणु
		ixgb_करोwn(adapter, true);
		ixgb_up(adapter);
		ixgb_set_speed_duplex(netdev);
	पूर्ण अन्यथा
		ixgb_reset(adapter);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा net_device_ops ixgb_netdev_ops = अणु
	.nकरो_खोलो 		= ixgb_खोलो,
	.nकरो_stop		= ixgb_बंद,
	.nकरो_start_xmit		= ixgb_xmit_frame,
	.nकरो_set_rx_mode	= ixgb_set_multi,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= ixgb_set_mac,
	.nकरो_change_mtu		= ixgb_change_mtu,
	.nकरो_tx_समयout		= ixgb_tx_समयout,
	.nकरो_vlan_rx_add_vid	= ixgb_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= ixgb_vlan_rx_समाप्त_vid,
	.nकरो_fix_features       = ixgb_fix_features,
	.nकरो_set_features       = ixgb_set_features,
पूर्ण;

/**
 * ixgb_probe - Device Initialization Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in ixgb_pci_tbl
 *
 * Returns 0 on success, negative on failure
 *
 * ixgb_probe initializes an adapter identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring of the adapter निजी काष्ठाure,
 * and a hardware reset occur.
 **/

अटल पूर्णांक
ixgb_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev = शून्य;
	काष्ठा ixgb_adapter *adapter;
	अटल पूर्णांक cards_found = 0;
	पूर्णांक pci_using_dac;
	पूर्णांक i;
	पूर्णांक err;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;

	pci_using_dac = 0;
	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (!err) अणु
		pci_using_dac = 1;
	पूर्ण अन्यथा अणु
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			pr_err("No usable DMA configuration, aborting\n");
			जाओ err_dma_mask;
		पूर्ण
	पूर्ण

	err = pci_request_regions(pdev, ixgb_driver_name);
	अगर (err)
		जाओ err_request_regions;

	pci_set_master(pdev);

	netdev = alloc_etherdev(माप(काष्ठा ixgb_adapter));
	अगर (!netdev) अणु
		err = -ENOMEM;
		जाओ err_alloc_etherdev;
	पूर्ण

	SET_NETDEV_DEV(netdev, &pdev->dev);

	pci_set_drvdata(pdev, netdev);
	adapter = netdev_priv(netdev);
	adapter->netdev = netdev;
	adapter->pdev = pdev;
	adapter->hw.back = adapter;
	adapter->msg_enable = netअगर_msg_init(debug, DEFAULT_MSG_ENABLE);

	adapter->hw.hw_addr = pci_ioremap_bar(pdev, BAR_0);
	अगर (!adapter->hw.hw_addr) अणु
		err = -EIO;
		जाओ err_ioremap;
	पूर्ण

	क्रम (i = BAR_1; i < PCI_STD_NUM_BARS; i++) अणु
		अगर (pci_resource_len(pdev, i) == 0)
			जारी;
		अगर (pci_resource_flags(pdev, i) & IORESOURCE_IO) अणु
			adapter->hw.io_base = pci_resource_start(pdev, i);
			अवरोध;
		पूर्ण
	पूर्ण

	netdev->netdev_ops = &ixgb_netdev_ops;
	ixgb_set_ethtool_ops(netdev);
	netdev->watchकरोg_समयo = 5 * HZ;
	netअगर_napi_add(netdev, &adapter->napi, ixgb_clean, 64);

	म_नकलन(netdev->name, pci_name(pdev), माप(netdev->name) - 1);

	adapter->bd_number = cards_found;
	adapter->link_speed = 0;
	adapter->link_duplex = 0;

	/* setup the निजी काष्ठाure */

	err = ixgb_sw_init(adapter);
	अगर (err)
		जाओ err_sw_init;

	netdev->hw_features = NETIF_F_SG |
			   NETIF_F_TSO |
			   NETIF_F_HW_CSUM |
			   NETIF_F_HW_VLAN_CTAG_TX |
			   NETIF_F_HW_VLAN_CTAG_RX;
	netdev->features = netdev->hw_features |
			   NETIF_F_HW_VLAN_CTAG_FILTER;
	netdev->hw_features |= NETIF_F_RXCSUM;

	अगर (pci_using_dac) अणु
		netdev->features |= NETIF_F_HIGHDMA;
		netdev->vlan_features |= NETIF_F_HIGHDMA;
	पूर्ण

	/* MTU range: 68 - 16114 */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = IXGB_MAX_JUMBO_FRAME_SIZE - ETH_HLEN;

	/* make sure the EEPROM is good */

	अगर (!ixgb_validate_eeprom_checksum(&adapter->hw)) अणु
		netअगर_err(adapter, probe, adapter->netdev,
			  "The EEPROM Checksum Is Not Valid\n");
		err = -EIO;
		जाओ err_eeprom;
	पूर्ण

	ixgb_get_ee_mac_addr(&adapter->hw, netdev->dev_addr);

	अगर (!is_valid_ether_addr(netdev->dev_addr)) अणु
		netअगर_err(adapter, probe, adapter->netdev, "Invalid MAC Address\n");
		err = -EIO;
		जाओ err_eeprom;
	पूर्ण

	adapter->part_num = ixgb_get_ee_pba_number(&adapter->hw);

	समयr_setup(&adapter->watchकरोg_समयr, ixgb_watchकरोg, 0);

	INIT_WORK(&adapter->tx_समयout_task, ixgb_tx_समयout_task);

	म_नकल(netdev->name, "eth%d");
	err = रेजिस्टर_netdev(netdev);
	अगर (err)
		जाओ err_रेजिस्टर;

	/* carrier off reporting is important to ethtool even BEFORE खोलो */
	netअगर_carrier_off(netdev);

	netअगर_info(adapter, probe, adapter->netdev,
		   "Intel(R) PRO/10GbE Network Connection\n");
	ixgb_check_options(adapter);
	/* reset the hardware with the new settings */

	ixgb_reset(adapter);

	cards_found++;
	वापस 0;

err_रेजिस्टर:
err_sw_init:
err_eeprom:
	iounmap(adapter->hw.hw_addr);
err_ioremap:
	मुक्त_netdev(netdev);
err_alloc_etherdev:
	pci_release_regions(pdev);
err_request_regions:
err_dma_mask:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

/**
 * ixgb_हटाओ - Device Removal Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * ixgb_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device.  The could be caused by a
 * Hot-Plug event, or because the driver is going to be हटाओd from
 * memory.
 **/

अटल व्योम
ixgb_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);

	cancel_work_sync(&adapter->tx_समयout_task);

	unरेजिस्टर_netdev(netdev);

	iounmap(adapter->hw.hw_addr);
	pci_release_regions(pdev);

	मुक्त_netdev(netdev);
	pci_disable_device(pdev);
पूर्ण

/**
 * ixgb_sw_init - Initialize general software काष्ठाures (काष्ठा ixgb_adapter)
 * @adapter: board निजी काष्ठाure to initialize
 *
 * ixgb_sw_init initializes the Adapter निजी data काष्ठाure.
 * Fields are initialized based on PCI device inक्रमmation and
 * OS network device settings (MTU size).
 **/

अटल पूर्णांक
ixgb_sw_init(काष्ठा ixgb_adapter *adapter)
अणु
	काष्ठा ixgb_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;

	/* PCI config space info */

	hw->venकरोr_id = pdev->venकरोr;
	hw->device_id = pdev->device;
	hw->subप्रणाली_venकरोr_id = pdev->subप्रणाली_venकरोr;
	hw->subप्रणाली_id = pdev->subप्रणाली_device;

	hw->max_frame_size = netdev->mtu + ENET_HEADER_SIZE + ENET_FCS_LENGTH;
	adapter->rx_buffer_len = hw->max_frame_size + 8; /* + 8 क्रम errata */

	अगर ((hw->device_id == IXGB_DEVICE_ID_82597EX) ||
	    (hw->device_id == IXGB_DEVICE_ID_82597EX_CX4) ||
	    (hw->device_id == IXGB_DEVICE_ID_82597EX_LR) ||
	    (hw->device_id == IXGB_DEVICE_ID_82597EX_SR))
		hw->mac_type = ixgb_82597;
	अन्यथा अणु
		/* should never have loaded on this device */
		netअगर_err(adapter, probe, adapter->netdev, "unsupported device id\n");
	पूर्ण

	/* enable flow control to be programmed */
	hw->fc.send_xon = 1;

	set_bit(__IXGB_DOWN, &adapter->flags);
	वापस 0;
पूर्ण

/**
 * ixgb_खोलो - Called when a network पूर्णांकerface is made active
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

अटल पूर्णांक
ixgb_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err;

	/* allocate transmit descriptors */
	err = ixgb_setup_tx_resources(adapter);
	अगर (err)
		जाओ err_setup_tx;

	netअगर_carrier_off(netdev);

	/* allocate receive descriptors */

	err = ixgb_setup_rx_resources(adapter);
	अगर (err)
		जाओ err_setup_rx;

	err = ixgb_up(adapter);
	अगर (err)
		जाओ err_up;

	netअगर_start_queue(netdev);

	वापस 0;

err_up:
	ixgb_मुक्त_rx_resources(adapter);
err_setup_rx:
	ixgb_मुक्त_tx_resources(adapter);
err_setup_tx:
	ixgb_reset(adapter);

	वापस err;
पूर्ण

/**
 * ixgb_बंद - Disables a network पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0, this is not allowed to fail
 *
 * The बंद entry poपूर्णांक is called when an पूर्णांकerface is de-activated
 * by the OS.  The hardware is still under the drivers control, but
 * needs to be disabled.  A global MAC reset is issued to stop the
 * hardware, and all transmit and receive resources are मुक्तd.
 **/

अटल पूर्णांक
ixgb_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);

	ixgb_करोwn(adapter, true);

	ixgb_मुक्त_tx_resources(adapter);
	ixgb_मुक्त_rx_resources(adapter);

	वापस 0;
पूर्ण

/**
 * ixgb_setup_tx_resources - allocate Tx resources (Descriptors)
 * @adapter: board निजी काष्ठाure
 *
 * Return 0 on success, negative on failure
 **/

पूर्णांक
ixgb_setup_tx_resources(काष्ठा ixgb_adapter *adapter)
अणु
	काष्ठा ixgb_desc_ring *txdr = &adapter->tx_ring;
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक size;

	size = माप(काष्ठा ixgb_buffer) * txdr->count;
	txdr->buffer_info = vzalloc(size);
	अगर (!txdr->buffer_info)
		वापस -ENOMEM;

	/* round up to nearest 4K */

	txdr->size = txdr->count * माप(काष्ठा ixgb_tx_desc);
	txdr->size = ALIGN(txdr->size, 4096);

	txdr->desc = dma_alloc_coherent(&pdev->dev, txdr->size, &txdr->dma,
					GFP_KERNEL);
	अगर (!txdr->desc) अणु
		vमुक्त(txdr->buffer_info);
		वापस -ENOMEM;
	पूर्ण

	txdr->next_to_use = 0;
	txdr->next_to_clean = 0;

	वापस 0;
पूर्ण

/**
 * ixgb_configure_tx - Configure 82597 Transmit Unit after Reset.
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Tx unit of the MAC after a reset.
 **/

अटल व्योम
ixgb_configure_tx(काष्ठा ixgb_adapter *adapter)
अणु
	u64 tdba = adapter->tx_ring.dma;
	u32 tdlen = adapter->tx_ring.count * माप(काष्ठा ixgb_tx_desc);
	u32 tctl;
	काष्ठा ixgb_hw *hw = &adapter->hw;

	/* Setup the Base and Length of the Tx Descriptor Ring
	 * tx_ring.dma can be either a 32 or 64 bit value
	 */

	IXGB_WRITE_REG(hw, TDBAL, (tdba & 0x00000000ffffffffULL));
	IXGB_WRITE_REG(hw, TDBAH, (tdba >> 32));

	IXGB_WRITE_REG(hw, TDLEN, tdlen);

	/* Setup the HW Tx Head and Tail descriptor poपूर्णांकers */

	IXGB_WRITE_REG(hw, TDH, 0);
	IXGB_WRITE_REG(hw, TDT, 0);

	/* करोn't set up txdctl, it induces perक्रमmance problems अगर configured
	 * incorrectly */
	/* Set the Tx Interrupt Delay रेजिस्टर */

	IXGB_WRITE_REG(hw, TIDV, adapter->tx_पूर्णांक_delay);

	/* Program the Transmit Control Register */

	tctl = IXGB_TCTL_TCE | IXGB_TCTL_TXEN | IXGB_TCTL_TPDE;
	IXGB_WRITE_REG(hw, TCTL, tctl);

	/* Setup Transmit Descriptor Settings क्रम this adapter */
	adapter->tx_cmd_type =
		IXGB_TX_DESC_TYPE |
		(adapter->tx_पूर्णांक_delay_enable ? IXGB_TX_DESC_CMD_IDE : 0);
पूर्ण

/**
 * ixgb_setup_rx_resources - allocate Rx resources (Descriptors)
 * @adapter: board निजी काष्ठाure
 *
 * Returns 0 on success, negative on failure
 **/

पूर्णांक
ixgb_setup_rx_resources(काष्ठा ixgb_adapter *adapter)
अणु
	काष्ठा ixgb_desc_ring *rxdr = &adapter->rx_ring;
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक size;

	size = माप(काष्ठा ixgb_buffer) * rxdr->count;
	rxdr->buffer_info = vzalloc(size);
	अगर (!rxdr->buffer_info)
		वापस -ENOMEM;

	/* Round up to nearest 4K */

	rxdr->size = rxdr->count * माप(काष्ठा ixgb_rx_desc);
	rxdr->size = ALIGN(rxdr->size, 4096);

	rxdr->desc = dma_alloc_coherent(&pdev->dev, rxdr->size, &rxdr->dma,
					GFP_KERNEL);

	अगर (!rxdr->desc) अणु
		vमुक्त(rxdr->buffer_info);
		वापस -ENOMEM;
	पूर्ण

	rxdr->next_to_clean = 0;
	rxdr->next_to_use = 0;

	वापस 0;
पूर्ण

/**
 * ixgb_setup_rctl - configure the receive control रेजिस्टर
 * @adapter: Board निजी काष्ठाure
 **/

अटल व्योम
ixgb_setup_rctl(काष्ठा ixgb_adapter *adapter)
अणु
	u32 rctl;

	rctl = IXGB_READ_REG(&adapter->hw, RCTL);

	rctl &= ~(3 << IXGB_RCTL_MO_SHIFT);

	rctl |=
		IXGB_RCTL_BAM | IXGB_RCTL_RDMTS_1_2 |
		IXGB_RCTL_RXEN | IXGB_RCTL_CFF |
		(adapter->hw.mc_filter_type << IXGB_RCTL_MO_SHIFT);

	rctl |= IXGB_RCTL_SECRC;

	अगर (adapter->rx_buffer_len <= IXGB_RXBUFFER_2048)
		rctl |= IXGB_RCTL_BSIZE_2048;
	अन्यथा अगर (adapter->rx_buffer_len <= IXGB_RXBUFFER_4096)
		rctl |= IXGB_RCTL_BSIZE_4096;
	अन्यथा अगर (adapter->rx_buffer_len <= IXGB_RXBUFFER_8192)
		rctl |= IXGB_RCTL_BSIZE_8192;
	अन्यथा अगर (adapter->rx_buffer_len <= IXGB_RXBUFFER_16384)
		rctl |= IXGB_RCTL_BSIZE_16384;

	IXGB_WRITE_REG(&adapter->hw, RCTL, rctl);
पूर्ण

/**
 * ixgb_configure_rx - Configure 82597 Receive Unit after Reset.
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Rx unit of the MAC after a reset.
 **/

अटल व्योम
ixgb_configure_rx(काष्ठा ixgb_adapter *adapter)
अणु
	u64 rdba = adapter->rx_ring.dma;
	u32 rdlen = adapter->rx_ring.count * माप(काष्ठा ixgb_rx_desc);
	काष्ठा ixgb_hw *hw = &adapter->hw;
	u32 rctl;
	u32 rxcsum;

	/* make sure receives are disabled जबतक setting up the descriptors */

	rctl = IXGB_READ_REG(hw, RCTL);
	IXGB_WRITE_REG(hw, RCTL, rctl & ~IXGB_RCTL_RXEN);

	/* set the Receive Delay Timer Register */

	IXGB_WRITE_REG(hw, RDTR, adapter->rx_पूर्णांक_delay);

	/* Setup the Base and Length of the Rx Descriptor Ring */

	IXGB_WRITE_REG(hw, RDBAL, (rdba & 0x00000000ffffffffULL));
	IXGB_WRITE_REG(hw, RDBAH, (rdba >> 32));

	IXGB_WRITE_REG(hw, RDLEN, rdlen);

	/* Setup the HW Rx Head and Tail Descriptor Poपूर्णांकers */
	IXGB_WRITE_REG(hw, RDH, 0);
	IXGB_WRITE_REG(hw, RDT, 0);

	/* due to the hardware errata with RXDCTL, we are unable to use any of
	 * the perक्रमmance enhancing features of it without causing other
	 * subtle bugs, some of the bugs could include receive length
	 * corruption at high data rates (WTHRESH > 0) and/or receive
	 * descriptor ring irregularites (particularly in hardware cache) */
	IXGB_WRITE_REG(hw, RXDCTL, 0);

	/* Enable Receive Checksum Offload क्रम TCP and UDP */
	अगर (adapter->rx_csum) अणु
		rxcsum = IXGB_READ_REG(hw, RXCSUM);
		rxcsum |= IXGB_RXCSUM_TUOFL;
		IXGB_WRITE_REG(hw, RXCSUM, rxcsum);
	पूर्ण

	/* Enable Receives */

	IXGB_WRITE_REG(hw, RCTL, rctl);
पूर्ण

/**
 * ixgb_मुक्त_tx_resources - Free Tx Resources
 * @adapter: board निजी काष्ठाure
 *
 * Free all transmit software resources
 **/

व्योम
ixgb_मुक्त_tx_resources(काष्ठा ixgb_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;

	ixgb_clean_tx_ring(adapter);

	vमुक्त(adapter->tx_ring.buffer_info);
	adapter->tx_ring.buffer_info = शून्य;

	dma_मुक्त_coherent(&pdev->dev, adapter->tx_ring.size,
			  adapter->tx_ring.desc, adapter->tx_ring.dma);

	adapter->tx_ring.desc = शून्य;
पूर्ण

अटल व्योम
ixgb_unmap_and_मुक्त_tx_resource(काष्ठा ixgb_adapter *adapter,
                                काष्ठा ixgb_buffer *buffer_info)
अणु
	अगर (buffer_info->dma) अणु
		अगर (buffer_info->mapped_as_page)
			dma_unmap_page(&adapter->pdev->dev, buffer_info->dma,
				       buffer_info->length, DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_single(&adapter->pdev->dev, buffer_info->dma,
					 buffer_info->length, DMA_TO_DEVICE);
		buffer_info->dma = 0;
	पूर्ण

	अगर (buffer_info->skb) अणु
		dev_kमुक्त_skb_any(buffer_info->skb);
		buffer_info->skb = शून्य;
	पूर्ण
	buffer_info->समय_stamp = 0;
	/* these fields must always be initialized in tx
	 * buffer_info->length = 0;
	 * buffer_info->next_to_watch = 0; */
पूर्ण

/**
 * ixgb_clean_tx_ring - Free Tx Buffers
 * @adapter: board निजी काष्ठाure
 **/

अटल व्योम
ixgb_clean_tx_ring(काष्ठा ixgb_adapter *adapter)
अणु
	काष्ठा ixgb_desc_ring *tx_ring = &adapter->tx_ring;
	काष्ठा ixgb_buffer *buffer_info;
	अचिन्हित दीर्घ size;
	अचिन्हित पूर्णांक i;

	/* Free all the Tx ring sk_buffs */

	क्रम (i = 0; i < tx_ring->count; i++) अणु
		buffer_info = &tx_ring->buffer_info[i];
		ixgb_unmap_and_मुक्त_tx_resource(adapter, buffer_info);
	पूर्ण

	size = माप(काष्ठा ixgb_buffer) * tx_ring->count;
	स_रखो(tx_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */

	स_रखो(tx_ring->desc, 0, tx_ring->size);

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	IXGB_WRITE_REG(&adapter->hw, TDH, 0);
	IXGB_WRITE_REG(&adapter->hw, TDT, 0);
पूर्ण

/**
 * ixgb_मुक्त_rx_resources - Free Rx Resources
 * @adapter: board निजी काष्ठाure
 *
 * Free all receive software resources
 **/

व्योम
ixgb_मुक्त_rx_resources(काष्ठा ixgb_adapter *adapter)
अणु
	काष्ठा ixgb_desc_ring *rx_ring = &adapter->rx_ring;
	काष्ठा pci_dev *pdev = adapter->pdev;

	ixgb_clean_rx_ring(adapter);

	vमुक्त(rx_ring->buffer_info);
	rx_ring->buffer_info = शून्य;

	dma_मुक्त_coherent(&pdev->dev, rx_ring->size, rx_ring->desc,
			  rx_ring->dma);

	rx_ring->desc = शून्य;
पूर्ण

/**
 * ixgb_clean_rx_ring - Free Rx Buffers
 * @adapter: board निजी काष्ठाure
 **/

अटल व्योम
ixgb_clean_rx_ring(काष्ठा ixgb_adapter *adapter)
अणु
	काष्ठा ixgb_desc_ring *rx_ring = &adapter->rx_ring;
	काष्ठा ixgb_buffer *buffer_info;
	काष्ठा pci_dev *pdev = adapter->pdev;
	अचिन्हित दीर्घ size;
	अचिन्हित पूर्णांक i;

	/* Free all the Rx ring sk_buffs */

	क्रम (i = 0; i < rx_ring->count; i++) अणु
		buffer_info = &rx_ring->buffer_info[i];
		अगर (buffer_info->dma) अणु
			dma_unmap_single(&pdev->dev,
					 buffer_info->dma,
					 buffer_info->length,
					 DMA_FROM_DEVICE);
			buffer_info->dma = 0;
			buffer_info->length = 0;
		पूर्ण

		अगर (buffer_info->skb) अणु
			dev_kमुक्त_skb(buffer_info->skb);
			buffer_info->skb = शून्य;
		पूर्ण
	पूर्ण

	size = माप(काष्ठा ixgb_buffer) * rx_ring->count;
	स_रखो(rx_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */

	स_रखो(rx_ring->desc, 0, rx_ring->size);

	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;

	IXGB_WRITE_REG(&adapter->hw, RDH, 0);
	IXGB_WRITE_REG(&adapter->hw, RDT, 0);
पूर्ण

/**
 * ixgb_set_mac - Change the Ethernet Address of the NIC
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @p: poपूर्णांकer to an address काष्ठाure
 *
 * Returns 0 on success, negative on failure
 **/

अटल पूर्णांक
ixgb_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);

	ixgb_rar_set(&adapter->hw, addr->sa_data, 0);

	वापस 0;
पूर्ण

/**
 * ixgb_set_multi - Multicast and Promiscuous mode set
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * The set_multi entry poपूर्णांक is called whenever the multicast address
 * list or the network पूर्णांकerface flags are updated.  This routine is
 * responsible क्रम configuring the hardware क्रम proper multicast,
 * promiscuous mode, and all-multi behavior.
 **/

अटल व्योम
ixgb_set_multi(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgb_hw *hw = &adapter->hw;
	काष्ठा netdev_hw_addr *ha;
	u32 rctl;

	/* Check क्रम Promiscuous and All Multicast modes */

	rctl = IXGB_READ_REG(hw, RCTL);

	अगर (netdev->flags & IFF_PROMISC) अणु
		rctl |= (IXGB_RCTL_UPE | IXGB_RCTL_MPE);
		/* disable VLAN filtering */
		rctl &= ~IXGB_RCTL_CFIEN;
		rctl &= ~IXGB_RCTL_VFE;
	पूर्ण अन्यथा अणु
		अगर (netdev->flags & IFF_ALLMULTI) अणु
			rctl |= IXGB_RCTL_MPE;
			rctl &= ~IXGB_RCTL_UPE;
		पूर्ण अन्यथा अणु
			rctl &= ~(IXGB_RCTL_UPE | IXGB_RCTL_MPE);
		पूर्ण
		/* enable VLAN filtering */
		rctl |= IXGB_RCTL_VFE;
		rctl &= ~IXGB_RCTL_CFIEN;
	पूर्ण

	अगर (netdev_mc_count(netdev) > IXGB_MAX_NUM_MULTICAST_ADDRESSES) अणु
		rctl |= IXGB_RCTL_MPE;
		IXGB_WRITE_REG(hw, RCTL, rctl);
	पूर्ण अन्यथा अणु
		u8 *mta = kदो_स्मृति_array(ETH_ALEN,
				        IXGB_MAX_NUM_MULTICAST_ADDRESSES,
				        GFP_ATOMIC);
		u8 *addr;
		अगर (!mta)
			जाओ alloc_failed;

		IXGB_WRITE_REG(hw, RCTL, rctl);

		addr = mta;
		netdev_क्रम_each_mc_addr(ha, netdev) अणु
			स_नकल(addr, ha->addr, ETH_ALEN);
			addr += ETH_ALEN;
		पूर्ण

		ixgb_mc_addr_list_update(hw, mta, netdev_mc_count(netdev), 0);
		kमुक्त(mta);
	पूर्ण

alloc_failed:
	अगर (netdev->features & NETIF_F_HW_VLAN_CTAG_RX)
		ixgb_vlan_strip_enable(adapter);
	अन्यथा
		ixgb_vlan_strip_disable(adapter);

पूर्ण

/**
 * ixgb_watchकरोg - Timer Call-back
 * @t: poपूर्णांकer to समयr_list containing our निजी info poपूर्णांकer
 **/

अटल व्योम
ixgb_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा ixgb_adapter *adapter = from_समयr(adapter, t, watchकरोg_समयr);
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा ixgb_desc_ring *txdr = &adapter->tx_ring;

	ixgb_check_क्रम_link(&adapter->hw);

	अगर (ixgb_check_क्रम_bad_link(&adapter->hw)) अणु
		/* क्रमce the reset path */
		netअगर_stop_queue(netdev);
	पूर्ण

	अगर (adapter->hw.link_up) अणु
		अगर (!netअगर_carrier_ok(netdev)) अणु
			netdev_info(netdev,
				    "NIC Link is Up 10 Gbps Full Duplex, Flow Control: %s\n",
				    (adapter->hw.fc.type == ixgb_fc_full) ?
				    "RX/TX" :
				    (adapter->hw.fc.type == ixgb_fc_rx_छोड़ो) ?
				     "RX" :
				    (adapter->hw.fc.type == ixgb_fc_tx_छोड़ो) ?
				    "TX" : "None");
			adapter->link_speed = 10000;
			adapter->link_duplex = FULL_DUPLEX;
			netअगर_carrier_on(netdev);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (netअगर_carrier_ok(netdev)) अणु
			adapter->link_speed = 0;
			adapter->link_duplex = 0;
			netdev_info(netdev, "NIC Link is Down\n");
			netअगर_carrier_off(netdev);
		पूर्ण
	पूर्ण

	ixgb_update_stats(adapter);

	अगर (!netअगर_carrier_ok(netdev)) अणु
		अगर (IXGB_DESC_UNUSED(txdr) + 1 < txdr->count) अणु
			/* We've lost link, so the controller stops DMA,
			 * but we've got queued Tx work that's never going
			 * to get करोne, so reset controller to flush Tx.
			 * (Do the reset outside of पूर्णांकerrupt context). */
			schedule_work(&adapter->tx_समयout_task);
			/* वापस immediately since reset is imminent */
			वापस;
		पूर्ण
	पूर्ण

	/* Force detection of hung controller every watchकरोg period */
	adapter->detect_tx_hung = true;

	/* generate an पूर्णांकerrupt to क्रमce clean up of any stragglers */
	IXGB_WRITE_REG(&adapter->hw, ICS, IXGB_INT_TXDW);

	/* Reset the समयr */
	mod_समयr(&adapter->watchकरोg_समयr, jअगरfies + 2 * HZ);
पूर्ण

#घोषणा IXGB_TX_FLAGS_CSUM		0x00000001
#घोषणा IXGB_TX_FLAGS_VLAN		0x00000002
#घोषणा IXGB_TX_FLAGS_TSO		0x00000004

अटल पूर्णांक
ixgb_tso(काष्ठा ixgb_adapter *adapter, काष्ठा sk_buff *skb)
अणु
	काष्ठा ixgb_context_desc *context_desc;
	अचिन्हित पूर्णांक i;
	u8 ipcss, ipcso, tucss, tucso, hdr_len;
	u16 ipcse, tucse, mss;

	अगर (likely(skb_is_gso(skb))) अणु
		काष्ठा ixgb_buffer *buffer_info;
		काष्ठा iphdr *iph;
		पूर्णांक err;

		err = skb_cow_head(skb, 0);
		अगर (err < 0)
			वापस err;

		hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
		mss = skb_shinfo(skb)->gso_size;
		iph = ip_hdr(skb);
		iph->tot_len = 0;
		iph->check = 0;
		tcp_hdr(skb)->check = ~csum_tcpudp_magic(iph->saddr,
							 iph->daddr, 0,
							 IPPROTO_TCP, 0);
		ipcss = skb_network_offset(skb);
		ipcso = (व्योम *)&(iph->check) - (व्योम *)skb->data;
		ipcse = skb_transport_offset(skb) - 1;
		tucss = skb_transport_offset(skb);
		tucso = (व्योम *)&(tcp_hdr(skb)->check) - (व्योम *)skb->data;
		tucse = 0;

		i = adapter->tx_ring.next_to_use;
		context_desc = IXGB_CONTEXT_DESC(adapter->tx_ring, i);
		buffer_info = &adapter->tx_ring.buffer_info[i];
		WARN_ON(buffer_info->dma != 0);

		context_desc->ipcss = ipcss;
		context_desc->ipcso = ipcso;
		context_desc->ipcse = cpu_to_le16(ipcse);
		context_desc->tucss = tucss;
		context_desc->tucso = tucso;
		context_desc->tucse = cpu_to_le16(tucse);
		context_desc->mss = cpu_to_le16(mss);
		context_desc->hdr_len = hdr_len;
		context_desc->status = 0;
		context_desc->cmd_type_len = cpu_to_le32(
						  IXGB_CONTEXT_DESC_TYPE
						| IXGB_CONTEXT_DESC_CMD_TSE
						| IXGB_CONTEXT_DESC_CMD_IP
						| IXGB_CONTEXT_DESC_CMD_TCP
						| IXGB_CONTEXT_DESC_CMD_IDE
						| (skb->len - (hdr_len)));


		अगर (++i == adapter->tx_ring.count) i = 0;
		adapter->tx_ring.next_to_use = i;

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
ixgb_tx_csum(काष्ठा ixgb_adapter *adapter, काष्ठा sk_buff *skb)
अणु
	काष्ठा ixgb_context_desc *context_desc;
	अचिन्हित पूर्णांक i;
	u8 css, cso;

	अगर (likely(skb->ip_summed == CHECKSUM_PARTIAL)) अणु
		काष्ठा ixgb_buffer *buffer_info;
		css = skb_checksum_start_offset(skb);
		cso = css + skb->csum_offset;

		i = adapter->tx_ring.next_to_use;
		context_desc = IXGB_CONTEXT_DESC(adapter->tx_ring, i);
		buffer_info = &adapter->tx_ring.buffer_info[i];
		WARN_ON(buffer_info->dma != 0);

		context_desc->tucss = css;
		context_desc->tucso = cso;
		context_desc->tucse = 0;
		/* zero out any previously existing data in one inकाष्ठाion */
		*(u32 *)&(context_desc->ipcss) = 0;
		context_desc->status = 0;
		context_desc->hdr_len = 0;
		context_desc->mss = 0;
		context_desc->cmd_type_len =
			cpu_to_le32(IXGB_CONTEXT_DESC_TYPE
				    | IXGB_TX_DESC_CMD_IDE);

		अगर (++i == adapter->tx_ring.count) i = 0;
		adapter->tx_ring.next_to_use = i;

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

#घोषणा IXGB_MAX_TXD_PWR	14
#घोषणा IXGB_MAX_DATA_PER_TXD	(1<<IXGB_MAX_TXD_PWR)

अटल पूर्णांक
ixgb_tx_map(काष्ठा ixgb_adapter *adapter, काष्ठा sk_buff *skb,
	    अचिन्हित पूर्णांक first)
अणु
	काष्ठा ixgb_desc_ring *tx_ring = &adapter->tx_ring;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा ixgb_buffer *buffer_info;
	पूर्णांक len = skb_headlen(skb);
	अचिन्हित पूर्णांक offset = 0, size, count = 0, i;
	अचिन्हित पूर्णांक mss = skb_shinfo(skb)->gso_size;
	अचिन्हित पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	अचिन्हित पूर्णांक f;

	i = tx_ring->next_to_use;

	जबतक (len) अणु
		buffer_info = &tx_ring->buffer_info[i];
		size = min(len, IXGB_MAX_DATA_PER_TXD);
		/* Workaround क्रम premature desc ग_लिखो-backs
		 * in TSO mode.  Append 4-byte sentinel desc */
		अगर (unlikely(mss && !nr_frags && size == len && size > 8))
			size -= 4;

		buffer_info->length = size;
		WARN_ON(buffer_info->dma != 0);
		buffer_info->समय_stamp = jअगरfies;
		buffer_info->mapped_as_page = false;
		buffer_info->dma = dma_map_single(&pdev->dev,
						  skb->data + offset,
						  size, DMA_TO_DEVICE);
		अगर (dma_mapping_error(&pdev->dev, buffer_info->dma))
			जाओ dma_error;
		buffer_info->next_to_watch = 0;

		len -= size;
		offset += size;
		count++;
		अगर (len) अणु
			i++;
			अगर (i == tx_ring->count)
				i = 0;
		पूर्ण
	पूर्ण

	क्रम (f = 0; f < nr_frags; f++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[f];
		len = skb_frag_size(frag);
		offset = 0;

		जबतक (len) अणु
			i++;
			अगर (i == tx_ring->count)
				i = 0;

			buffer_info = &tx_ring->buffer_info[i];
			size = min(len, IXGB_MAX_DATA_PER_TXD);

			/* Workaround क्रम premature desc ग_लिखो-backs
			 * in TSO mode.  Append 4-byte sentinel desc */
			अगर (unlikely(mss && (f == (nr_frags - 1))
				     && size == len && size > 8))
				size -= 4;

			buffer_info->length = size;
			buffer_info->समय_stamp = jअगरfies;
			buffer_info->mapped_as_page = true;
			buffer_info->dma =
				skb_frag_dma_map(&pdev->dev, frag, offset, size,
						 DMA_TO_DEVICE);
			अगर (dma_mapping_error(&pdev->dev, buffer_info->dma))
				जाओ dma_error;
			buffer_info->next_to_watch = 0;

			len -= size;
			offset += size;
			count++;
		पूर्ण
	पूर्ण
	tx_ring->buffer_info[i].skb = skb;
	tx_ring->buffer_info[first].next_to_watch = i;

	वापस count;

dma_error:
	dev_err(&pdev->dev, "TX DMA map failed\n");
	buffer_info->dma = 0;
	अगर (count)
		count--;

	जबतक (count--) अणु
		अगर (i==0)
			i += tx_ring->count;
		i--;
		buffer_info = &tx_ring->buffer_info[i];
		ixgb_unmap_and_मुक्त_tx_resource(adapter, buffer_info);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
ixgb_tx_queue(काष्ठा ixgb_adapter *adapter, पूर्णांक count, पूर्णांक vlan_id,पूर्णांक tx_flags)
अणु
	काष्ठा ixgb_desc_ring *tx_ring = &adapter->tx_ring;
	काष्ठा ixgb_tx_desc *tx_desc = शून्य;
	काष्ठा ixgb_buffer *buffer_info;
	u32 cmd_type_len = adapter->tx_cmd_type;
	u8 status = 0;
	u8 popts = 0;
	अचिन्हित पूर्णांक i;

	अगर (tx_flags & IXGB_TX_FLAGS_TSO) अणु
		cmd_type_len |= IXGB_TX_DESC_CMD_TSE;
		popts |= (IXGB_TX_DESC_POPTS_IXSM | IXGB_TX_DESC_POPTS_TXSM);
	पूर्ण

	अगर (tx_flags & IXGB_TX_FLAGS_CSUM)
		popts |= IXGB_TX_DESC_POPTS_TXSM;

	अगर (tx_flags & IXGB_TX_FLAGS_VLAN)
		cmd_type_len |= IXGB_TX_DESC_CMD_VLE;

	i = tx_ring->next_to_use;

	जबतक (count--) अणु
		buffer_info = &tx_ring->buffer_info[i];
		tx_desc = IXGB_TX_DESC(*tx_ring, i);
		tx_desc->buff_addr = cpu_to_le64(buffer_info->dma);
		tx_desc->cmd_type_len =
			cpu_to_le32(cmd_type_len | buffer_info->length);
		tx_desc->status = status;
		tx_desc->popts = popts;
		tx_desc->vlan = cpu_to_le16(vlan_id);

		अगर (++i == tx_ring->count) i = 0;
	पूर्ण

	tx_desc->cmd_type_len |=
		cpu_to_le32(IXGB_TX_DESC_CMD_EOP | IXGB_TX_DESC_CMD_RS);

	/* Force memory ग_लिखोs to complete beक्रमe letting h/w
	 * know there are new descriptors to fetch.  (Only
	 * applicable क्रम weak-ordered memory model archs,
	 * such as IA-64). */
	wmb();

	tx_ring->next_to_use = i;
	IXGB_WRITE_REG(&adapter->hw, TDT, i);
पूर्ण

अटल पूर्णांक __ixgb_maybe_stop_tx(काष्ठा net_device *netdev, पूर्णांक size)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgb_desc_ring *tx_ring = &adapter->tx_ring;

	netअगर_stop_queue(netdev);
	/* Herbert's original patch had:
	 *  smp_mb__after_netअगर_stop_queue();
	 * but since that करोesn't exist yet, just खोलो code it. */
	smp_mb();

	/* We need to check again in a हाल another CPU has just
	 * made room available. */
	अगर (likely(IXGB_DESC_UNUSED(tx_ring) < size))
		वापस -EBUSY;

	/* A reprieve! */
	netअगर_start_queue(netdev);
	++adapter->restart_queue;
	वापस 0;
पूर्ण

अटल पूर्णांक ixgb_maybe_stop_tx(काष्ठा net_device *netdev,
                              काष्ठा ixgb_desc_ring *tx_ring, पूर्णांक size)
अणु
	अगर (likely(IXGB_DESC_UNUSED(tx_ring) >= size))
		वापस 0;
	वापस __ixgb_maybe_stop_tx(netdev, size);
पूर्ण


/* Tx Descriptors needed, worst हाल */
#घोषणा TXD_USE_COUNT(S) (((S) >> IXGB_MAX_TXD_PWR) + \
			 (((S) & (IXGB_MAX_DATA_PER_TXD - 1)) ? 1 : 0))
#घोषणा DESC_NEEDED TXD_USE_COUNT(IXGB_MAX_DATA_PER_TXD) /* skb->date */ + \
	MAX_SKB_FRAGS * TXD_USE_COUNT(PAGE_SIZE) + 1 /* क्रम context */ \
	+ 1 /* one more needed क्रम sentinel TSO workaround */

अटल netdev_tx_t
ixgb_xmit_frame(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	अचिन्हित पूर्णांक first;
	अचिन्हित पूर्णांक tx_flags = 0;
	पूर्णांक vlan_id = 0;
	पूर्णांक count = 0;
	पूर्णांक tso;

	अगर (test_bit(__IXGB_DOWN, &adapter->flags)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (skb->len <= 0) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (unlikely(ixgb_maybe_stop_tx(netdev, &adapter->tx_ring,
                     DESC_NEEDED)))
		वापस NETDEV_TX_BUSY;

	अगर (skb_vlan_tag_present(skb)) अणु
		tx_flags |= IXGB_TX_FLAGS_VLAN;
		vlan_id = skb_vlan_tag_get(skb);
	पूर्ण

	first = adapter->tx_ring.next_to_use;

	tso = ixgb_tso(adapter, skb);
	अगर (tso < 0) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (likely(tso))
		tx_flags |= IXGB_TX_FLAGS_TSO;
	अन्यथा अगर (ixgb_tx_csum(adapter, skb))
		tx_flags |= IXGB_TX_FLAGS_CSUM;

	count = ixgb_tx_map(adapter, skb, first);

	अगर (count) अणु
		ixgb_tx_queue(adapter, count, vlan_id, tx_flags);
		/* Make sure there is space in the ring क्रम the next send. */
		ixgb_maybe_stop_tx(netdev, &adapter->tx_ring, DESC_NEEDED);

	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb_any(skb);
		adapter->tx_ring.buffer_info[first].समय_stamp = 0;
		adapter->tx_ring.next_to_use = first;
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

/**
 * ixgb_tx_समयout - Respond to a Tx Hang
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @txqueue: queue hanging (unused)
 **/

अटल व्योम
ixgb_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक __always_unused txqueue)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);

	/* Do the reset outside of पूर्णांकerrupt context */
	schedule_work(&adapter->tx_समयout_task);
पूर्ण

अटल व्योम
ixgb_tx_समयout_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ixgb_adapter *adapter =
		container_of(work, काष्ठा ixgb_adapter, tx_समयout_task);

	adapter->tx_समयout_count++;
	ixgb_करोwn(adapter, true);
	ixgb_up(adapter);
पूर्ण

/**
 * ixgb_change_mtu - Change the Maximum Transfer Unit
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @new_mtu: new value क्रम maximum frame size
 *
 * Returns 0 on success, negative on failure
 **/

अटल पूर्णांक
ixgb_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	पूर्णांक max_frame = new_mtu + ENET_HEADER_SIZE + ENET_FCS_LENGTH;

	अगर (netअगर_running(netdev))
		ixgb_करोwn(adapter, true);

	adapter->rx_buffer_len = max_frame + 8; /* + 8 क्रम errata */

	netdev->mtu = new_mtu;

	अगर (netअगर_running(netdev))
		ixgb_up(adapter);

	वापस 0;
पूर्ण

/**
 * ixgb_update_stats - Update the board statistics counters.
 * @adapter: board निजी काष्ठाure
 **/

व्योम
ixgb_update_stats(काष्ठा ixgb_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;

	/* Prevent stats update जबतक adapter is being reset */
	अगर (pci_channel_offline(pdev))
		वापस;

	अगर ((netdev->flags & IFF_PROMISC) || (netdev->flags & IFF_ALLMULTI) ||
	   (netdev_mc_count(netdev) > IXGB_MAX_NUM_MULTICAST_ADDRESSES)) अणु
		u64 multi = IXGB_READ_REG(&adapter->hw, MPRCL);
		u32 bcast_l = IXGB_READ_REG(&adapter->hw, BPRCL);
		u32 bcast_h = IXGB_READ_REG(&adapter->hw, BPRCH);
		u64 bcast = ((u64)bcast_h << 32) | bcast_l;

		multi |= ((u64)IXGB_READ_REG(&adapter->hw, MPRCH) << 32);
		/* fix up multicast stats by removing broadcasts */
		अगर (multi >= bcast)
			multi -= bcast;

		adapter->stats.mprcl += (multi & 0xFFFFFFFF);
		adapter->stats.mprch += (multi >> 32);
		adapter->stats.bprcl += bcast_l;
		adapter->stats.bprch += bcast_h;
	पूर्ण अन्यथा अणु
		adapter->stats.mprcl += IXGB_READ_REG(&adapter->hw, MPRCL);
		adapter->stats.mprch += IXGB_READ_REG(&adapter->hw, MPRCH);
		adapter->stats.bprcl += IXGB_READ_REG(&adapter->hw, BPRCL);
		adapter->stats.bprch += IXGB_READ_REG(&adapter->hw, BPRCH);
	पूर्ण
	adapter->stats.tprl += IXGB_READ_REG(&adapter->hw, TPRL);
	adapter->stats.tprh += IXGB_READ_REG(&adapter->hw, TPRH);
	adapter->stats.gprcl += IXGB_READ_REG(&adapter->hw, GPRCL);
	adapter->stats.gprch += IXGB_READ_REG(&adapter->hw, GPRCH);
	adapter->stats.uprcl += IXGB_READ_REG(&adapter->hw, UPRCL);
	adapter->stats.uprch += IXGB_READ_REG(&adapter->hw, UPRCH);
	adapter->stats.vprcl += IXGB_READ_REG(&adapter->hw, VPRCL);
	adapter->stats.vprch += IXGB_READ_REG(&adapter->hw, VPRCH);
	adapter->stats.jprcl += IXGB_READ_REG(&adapter->hw, JPRCL);
	adapter->stats.jprch += IXGB_READ_REG(&adapter->hw, JPRCH);
	adapter->stats.gorcl += IXGB_READ_REG(&adapter->hw, GORCL);
	adapter->stats.gorch += IXGB_READ_REG(&adapter->hw, GORCH);
	adapter->stats.torl += IXGB_READ_REG(&adapter->hw, TORL);
	adapter->stats.torh += IXGB_READ_REG(&adapter->hw, TORH);
	adapter->stats.rnbc += IXGB_READ_REG(&adapter->hw, RNBC);
	adapter->stats.ruc += IXGB_READ_REG(&adapter->hw, RUC);
	adapter->stats.roc += IXGB_READ_REG(&adapter->hw, ROC);
	adapter->stats.rlec += IXGB_READ_REG(&adapter->hw, RLEC);
	adapter->stats.crcerrs += IXGB_READ_REG(&adapter->hw, CRCERRS);
	adapter->stats.icbc += IXGB_READ_REG(&adapter->hw, ICBC);
	adapter->stats.ecbc += IXGB_READ_REG(&adapter->hw, ECBC);
	adapter->stats.mpc += IXGB_READ_REG(&adapter->hw, MPC);
	adapter->stats.tptl += IXGB_READ_REG(&adapter->hw, TPTL);
	adapter->stats.tpth += IXGB_READ_REG(&adapter->hw, TPTH);
	adapter->stats.gptcl += IXGB_READ_REG(&adapter->hw, GPTCL);
	adapter->stats.gptch += IXGB_READ_REG(&adapter->hw, GPTCH);
	adapter->stats.bptcl += IXGB_READ_REG(&adapter->hw, BPTCL);
	adapter->stats.bptch += IXGB_READ_REG(&adapter->hw, BPTCH);
	adapter->stats.mptcl += IXGB_READ_REG(&adapter->hw, MPTCL);
	adapter->stats.mptch += IXGB_READ_REG(&adapter->hw, MPTCH);
	adapter->stats.uptcl += IXGB_READ_REG(&adapter->hw, UPTCL);
	adapter->stats.uptch += IXGB_READ_REG(&adapter->hw, UPTCH);
	adapter->stats.vptcl += IXGB_READ_REG(&adapter->hw, VPTCL);
	adapter->stats.vptch += IXGB_READ_REG(&adapter->hw, VPTCH);
	adapter->stats.jptcl += IXGB_READ_REG(&adapter->hw, JPTCL);
	adapter->stats.jptch += IXGB_READ_REG(&adapter->hw, JPTCH);
	adapter->stats.gotcl += IXGB_READ_REG(&adapter->hw, GOTCL);
	adapter->stats.gotch += IXGB_READ_REG(&adapter->hw, GOTCH);
	adapter->stats.totl += IXGB_READ_REG(&adapter->hw, TOTL);
	adapter->stats.toth += IXGB_READ_REG(&adapter->hw, TOTH);
	adapter->stats.dc += IXGB_READ_REG(&adapter->hw, DC);
	adapter->stats.plt64c += IXGB_READ_REG(&adapter->hw, PLT64C);
	adapter->stats.tsctc += IXGB_READ_REG(&adapter->hw, TSCTC);
	adapter->stats.tsctfc += IXGB_READ_REG(&adapter->hw, TSCTFC);
	adapter->stats.ibic += IXGB_READ_REG(&adapter->hw, IBIC);
	adapter->stats.rfc += IXGB_READ_REG(&adapter->hw, RFC);
	adapter->stats.lfc += IXGB_READ_REG(&adapter->hw, LFC);
	adapter->stats.pfrc += IXGB_READ_REG(&adapter->hw, PFRC);
	adapter->stats.pftc += IXGB_READ_REG(&adapter->hw, PFTC);
	adapter->stats.mcfrc += IXGB_READ_REG(&adapter->hw, MCFRC);
	adapter->stats.mcftc += IXGB_READ_REG(&adapter->hw, MCFTC);
	adapter->stats.xonrxc += IXGB_READ_REG(&adapter->hw, XONRXC);
	adapter->stats.xontxc += IXGB_READ_REG(&adapter->hw, XONTXC);
	adapter->stats.xoffrxc += IXGB_READ_REG(&adapter->hw, XOFFRXC);
	adapter->stats.xofftxc += IXGB_READ_REG(&adapter->hw, XOFFTXC);
	adapter->stats.rjc += IXGB_READ_REG(&adapter->hw, RJC);

	/* Fill out the OS statistics काष्ठाure */

	netdev->stats.rx_packets = adapter->stats.gprcl;
	netdev->stats.tx_packets = adapter->stats.gptcl;
	netdev->stats.rx_bytes = adapter->stats.gorcl;
	netdev->stats.tx_bytes = adapter->stats.gotcl;
	netdev->stats.multicast = adapter->stats.mprcl;
	netdev->stats.collisions = 0;

	/* ignore RLEC as it reports errors क्रम padded (<64bytes) frames
	 * with a length in the type/len field */
	netdev->stats.rx_errors =
	    /* adapter->stats.rnbc + */ adapter->stats.crcerrs +
	    adapter->stats.ruc +
	    adapter->stats.roc /*+ adapter->stats.rlec */  +
	    adapter->stats.icbc +
	    adapter->stats.ecbc + adapter->stats.mpc;

	/* see above
	 * netdev->stats.rx_length_errors = adapter->stats.rlec;
	 */

	netdev->stats.rx_crc_errors = adapter->stats.crcerrs;
	netdev->stats.rx_fअगरo_errors = adapter->stats.mpc;
	netdev->stats.rx_missed_errors = adapter->stats.mpc;
	netdev->stats.rx_over_errors = adapter->stats.mpc;

	netdev->stats.tx_errors = 0;
	netdev->stats.rx_frame_errors = 0;
	netdev->stats.tx_पातed_errors = 0;
	netdev->stats.tx_carrier_errors = 0;
	netdev->stats.tx_fअगरo_errors = 0;
	netdev->stats.tx_heartbeat_errors = 0;
	netdev->stats.tx_winकरोw_errors = 0;
पूर्ण

#घोषणा IXGB_MAX_INTR 10
/**
 * ixgb_पूर्णांकr - Interrupt Handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a network पूर्णांकerface device काष्ठाure
 **/

अटल irqवापस_t
ixgb_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = data;
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgb_hw *hw = &adapter->hw;
	u32 icr = IXGB_READ_REG(hw, ICR);

	अगर (unlikely(!icr))
		वापस IRQ_NONE;  /* Not our पूर्णांकerrupt */

	अगर (unlikely(icr & (IXGB_INT_RXSEQ | IXGB_INT_LSC)))
		अगर (!test_bit(__IXGB_DOWN, &adapter->flags))
			mod_समयr(&adapter->watchकरोg_समयr, jअगरfies);

	अगर (napi_schedule_prep(&adapter->napi)) अणु

		/* Disable पूर्णांकerrupts and रेजिस्टर क्रम poll. The flush
		  of the posted ग_लिखो is पूर्णांकentionally left out.
		*/

		IXGB_WRITE_REG(&adapter->hw, IMC, ~0);
		__napi_schedule(&adapter->napi);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/**
 * ixgb_clean - NAPI Rx polling callback
 * @napi: napi काष्ठा poपूर्णांकer
 * @budget: max number of receives to clean
 **/

अटल पूर्णांक
ixgb_clean(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ixgb_adapter *adapter = container_of(napi, काष्ठा ixgb_adapter, napi);
	पूर्णांक work_करोne = 0;

	ixgb_clean_tx_irq(adapter);
	ixgb_clean_rx_irq(adapter, &work_करोne, budget);

	/* If budget not fully consumed, निकास the polling mode */
	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		अगर (!test_bit(__IXGB_DOWN, &adapter->flags))
			ixgb_irq_enable(adapter);
	पूर्ण

	वापस work_करोne;
पूर्ण

/**
 * ixgb_clean_tx_irq - Reclaim resources after transmit completes
 * @adapter: board निजी काष्ठाure
 **/

अटल bool
ixgb_clean_tx_irq(काष्ठा ixgb_adapter *adapter)
अणु
	काष्ठा ixgb_desc_ring *tx_ring = &adapter->tx_ring;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा ixgb_tx_desc *tx_desc, *eop_desc;
	काष्ठा ixgb_buffer *buffer_info;
	अचिन्हित पूर्णांक i, eop;
	bool cleaned = false;

	i = tx_ring->next_to_clean;
	eop = tx_ring->buffer_info[i].next_to_watch;
	eop_desc = IXGB_TX_DESC(*tx_ring, eop);

	जबतक (eop_desc->status & IXGB_TX_DESC_STATUS_DD) अणु

		rmb(); /* पढ़ो buffer_info after eop_desc */
		क्रम (cleaned = false; !cleaned; ) अणु
			tx_desc = IXGB_TX_DESC(*tx_ring, i);
			buffer_info = &tx_ring->buffer_info[i];

			अगर (tx_desc->popts &
			   (IXGB_TX_DESC_POPTS_TXSM |
			    IXGB_TX_DESC_POPTS_IXSM))
				adapter->hw_csum_tx_good++;

			ixgb_unmap_and_मुक्त_tx_resource(adapter, buffer_info);

			*(u32 *)&(tx_desc->status) = 0;

			cleaned = (i == eop);
			अगर (++i == tx_ring->count) i = 0;
		पूर्ण

		eop = tx_ring->buffer_info[i].next_to_watch;
		eop_desc = IXGB_TX_DESC(*tx_ring, eop);
	पूर्ण

	tx_ring->next_to_clean = i;

	अगर (unlikely(cleaned && netअगर_carrier_ok(netdev) &&
		     IXGB_DESC_UNUSED(tx_ring) >= DESC_NEEDED)) अणु
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean. */
		smp_mb();

		अगर (netअगर_queue_stopped(netdev) &&
		    !(test_bit(__IXGB_DOWN, &adapter->flags))) अणु
			netअगर_wake_queue(netdev);
			++adapter->restart_queue;
		पूर्ण
	पूर्ण

	अगर (adapter->detect_tx_hung) अणु
		/* detect a transmit hang in hardware, this serializes the
		 * check with the clearing of समय_stamp and movement of i */
		adapter->detect_tx_hung = false;
		अगर (tx_ring->buffer_info[eop].समय_stamp &&
		   समय_after(jअगरfies, tx_ring->buffer_info[eop].समय_stamp + HZ)
		   && !(IXGB_READ_REG(&adapter->hw, STATUS) &
		        IXGB_STATUS_TXOFF)) अणु
			/* detected Tx unit hang */
			netअगर_err(adapter, drv, adapter->netdev,
				  "Detected Tx Unit Hang\n"
				  "  TDH                  <%x>\n"
				  "  TDT                  <%x>\n"
				  "  next_to_use          <%x>\n"
				  "  next_to_clean        <%x>\n"
				  "buffer_info[next_to_clean]\n"
				  "  time_stamp           <%lx>\n"
				  "  next_to_watch        <%x>\n"
				  "  jiffies              <%lx>\n"
				  "  next_to_watch.status <%x>\n",
				  IXGB_READ_REG(&adapter->hw, TDH),
				  IXGB_READ_REG(&adapter->hw, TDT),
				  tx_ring->next_to_use,
				  tx_ring->next_to_clean,
				  tx_ring->buffer_info[eop].समय_stamp,
				  eop,
				  jअगरfies,
				  eop_desc->status);
			netअगर_stop_queue(netdev);
		पूर्ण
	पूर्ण

	वापस cleaned;
पूर्ण

/**
 * ixgb_rx_checksum - Receive Checksum Offload क्रम 82597.
 * @adapter: board निजी काष्ठाure
 * @rx_desc: receive descriptor
 * @skb: socket buffer with received data
 **/

अटल व्योम
ixgb_rx_checksum(काष्ठा ixgb_adapter *adapter,
                 काष्ठा ixgb_rx_desc *rx_desc,
                 काष्ठा sk_buff *skb)
अणु
	/* Ignore Checksum bit is set OR
	 * TCP Checksum has not been calculated
	 */
	अगर ((rx_desc->status & IXGB_RX_DESC_STATUS_IXSM) ||
	   (!(rx_desc->status & IXGB_RX_DESC_STATUS_TCPCS))) अणु
		skb_checksum_none_निश्चित(skb);
		वापस;
	पूर्ण

	/* At this poपूर्णांक we know the hardware did the TCP checksum */
	/* now look at the TCP checksum error bit */
	अगर (rx_desc->errors & IXGB_RX_DESC_ERRORS_TCPE) अणु
		/* let the stack verअगरy checksum errors */
		skb_checksum_none_निश्चित(skb);
		adapter->hw_csum_rx_error++;
	पूर्ण अन्यथा अणु
		/* TCP checksum is good */
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		adapter->hw_csum_rx_good++;
	पूर्ण
पूर्ण

/*
 * this should improve perक्रमmance क्रम small packets with large amounts
 * of reassembly being करोne in the stack
 */
अटल व्योम ixgb_check_copyअवरोध(काष्ठा napi_काष्ठा *napi,
				 काष्ठा ixgb_buffer *buffer_info,
				 u32 length, काष्ठा sk_buff **skb)
अणु
	काष्ठा sk_buff *new_skb;

	अगर (length > copyअवरोध)
		वापस;

	new_skb = napi_alloc_skb(napi, length);
	अगर (!new_skb)
		वापस;

	skb_copy_to_linear_data_offset(new_skb, -NET_IP_ALIGN,
				       (*skb)->data - NET_IP_ALIGN,
				       length + NET_IP_ALIGN);
	/* save the skb in buffer_info as good */
	buffer_info->skb = *skb;
	*skb = new_skb;
पूर्ण

/**
 * ixgb_clean_rx_irq - Send received data up the network stack,
 * @adapter: board निजी काष्ठाure
 * @work_करोne: output poपूर्णांकer to amount of packets cleaned
 * @work_to_करो: how much work we can complete
 **/

अटल bool
ixgb_clean_rx_irq(काष्ठा ixgb_adapter *adapter, पूर्णांक *work_करोne, पूर्णांक work_to_करो)
अणु
	काष्ठा ixgb_desc_ring *rx_ring = &adapter->rx_ring;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा ixgb_rx_desc *rx_desc, *next_rxd;
	काष्ठा ixgb_buffer *buffer_info, *next_buffer, *next2_buffer;
	u32 length;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक cleaned_count = 0;
	bool cleaned = false;

	i = rx_ring->next_to_clean;
	rx_desc = IXGB_RX_DESC(*rx_ring, i);
	buffer_info = &rx_ring->buffer_info[i];

	जबतक (rx_desc->status & IXGB_RX_DESC_STATUS_DD) अणु
		काष्ठा sk_buff *skb;
		u8 status;

		अगर (*work_करोne >= work_to_करो)
			अवरोध;

		(*work_करोne)++;
		rmb();	/* पढ़ो descriptor and rx_buffer_info after status DD */
		status = rx_desc->status;
		skb = buffer_info->skb;
		buffer_info->skb = शून्य;

		prefetch(skb->data - NET_IP_ALIGN);

		अगर (++i == rx_ring->count)
			i = 0;
		next_rxd = IXGB_RX_DESC(*rx_ring, i);
		prefetch(next_rxd);

		j = i + 1;
		अगर (j == rx_ring->count)
			j = 0;
		next2_buffer = &rx_ring->buffer_info[j];
		prefetch(next2_buffer);

		next_buffer = &rx_ring->buffer_info[i];

		cleaned = true;
		cleaned_count++;

		dma_unmap_single(&pdev->dev,
				 buffer_info->dma,
				 buffer_info->length,
				 DMA_FROM_DEVICE);
		buffer_info->dma = 0;

		length = le16_to_cpu(rx_desc->length);
		rx_desc->length = 0;

		अगर (unlikely(!(status & IXGB_RX_DESC_STATUS_EOP))) अणु

			/* All receives must fit पूर्णांकo a single buffer */

			pr_debug("Receive packet consumed multiple buffers length<%x>\n",
				 length);

			dev_kमुक्त_skb_irq(skb);
			जाओ rxdesc_करोne;
		पूर्ण

		अगर (unlikely(rx_desc->errors &
		    (IXGB_RX_DESC_ERRORS_CE | IXGB_RX_DESC_ERRORS_SE |
		     IXGB_RX_DESC_ERRORS_P | IXGB_RX_DESC_ERRORS_RXE))) अणु
			dev_kमुक्त_skb_irq(skb);
			जाओ rxdesc_करोne;
		पूर्ण

		ixgb_check_copyअवरोध(&adapter->napi, buffer_info, length, &skb);

		/* Good Receive */
		skb_put(skb, length);

		/* Receive Checksum Offload */
		ixgb_rx_checksum(adapter, rx_desc, skb);

		skb->protocol = eth_type_trans(skb, netdev);
		अगर (status & IXGB_RX_DESC_STATUS_VP)
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       le16_to_cpu(rx_desc->special));

		netअगर_receive_skb(skb);

rxdesc_करोne:
		/* clean up descriptor, might be written over by hw */
		rx_desc->status = 0;

		/* वापस some buffers to hardware, one at a समय is too slow */
		अगर (unlikely(cleaned_count >= IXGB_RX_BUFFER_WRITE)) अणु
			ixgb_alloc_rx_buffers(adapter, cleaned_count);
			cleaned_count = 0;
		पूर्ण

		/* use prefetched values */
		rx_desc = next_rxd;
		buffer_info = next_buffer;
	पूर्ण

	rx_ring->next_to_clean = i;

	cleaned_count = IXGB_DESC_UNUSED(rx_ring);
	अगर (cleaned_count)
		ixgb_alloc_rx_buffers(adapter, cleaned_count);

	वापस cleaned;
पूर्ण

/**
 * ixgb_alloc_rx_buffers - Replace used receive buffers
 * @adapter: address of board निजी काष्ठाure
 * @cleaned_count: how many buffers to allocate
 **/

अटल व्योम
ixgb_alloc_rx_buffers(काष्ठा ixgb_adapter *adapter, पूर्णांक cleaned_count)
अणु
	काष्ठा ixgb_desc_ring *rx_ring = &adapter->rx_ring;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा ixgb_rx_desc *rx_desc;
	काष्ठा ixgb_buffer *buffer_info;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक i;
	दीर्घ cleancount;

	i = rx_ring->next_to_use;
	buffer_info = &rx_ring->buffer_info[i];
	cleancount = IXGB_DESC_UNUSED(rx_ring);


	/* leave three descriptors unused */
	जबतक (--cleancount > 2 && cleaned_count--) अणु
		/* recycle! its good क्रम you */
		skb = buffer_info->skb;
		अगर (skb) अणु
			skb_trim(skb, 0);
			जाओ map_skb;
		पूर्ण

		skb = netdev_alloc_skb_ip_align(netdev, adapter->rx_buffer_len);
		अगर (unlikely(!skb)) अणु
			/* Better luck next round */
			adapter->alloc_rx_buff_failed++;
			अवरोध;
		पूर्ण

		buffer_info->skb = skb;
		buffer_info->length = adapter->rx_buffer_len;
map_skb:
		buffer_info->dma = dma_map_single(&pdev->dev,
		                                  skb->data,
		                                  adapter->rx_buffer_len,
						  DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&pdev->dev, buffer_info->dma)) अणु
			adapter->alloc_rx_buff_failed++;
			अवरोध;
		पूर्ण

		rx_desc = IXGB_RX_DESC(*rx_ring, i);
		rx_desc->buff_addr = cpu_to_le64(buffer_info->dma);
		/* guarantee DD bit not set now beक्रमe h/w माला_लो descriptor
		 * this is the rest of the workaround क्रम h/w द्विगुन
		 * ग_लिखोback. */
		rx_desc->status = 0;


		अगर (++i == rx_ring->count)
			i = 0;
		buffer_info = &rx_ring->buffer_info[i];
	पूर्ण

	अगर (likely(rx_ring->next_to_use != i)) अणु
		rx_ring->next_to_use = i;
		अगर (unlikely(i-- == 0))
			i = (rx_ring->count - 1);

		/* Force memory ग_लिखोs to complete beक्रमe letting h/w
		 * know there are new descriptors to fetch.  (Only
		 * applicable क्रम weak-ordered memory model archs, such
		 * as IA-64). */
		wmb();
		IXGB_WRITE_REG(&adapter->hw, RDT, i);
	पूर्ण
पूर्ण

अटल व्योम
ixgb_vlan_strip_enable(काष्ठा ixgb_adapter *adapter)
अणु
	u32 ctrl;

	/* enable VLAN tag insert/strip */
	ctrl = IXGB_READ_REG(&adapter->hw, CTRL0);
	ctrl |= IXGB_CTRL0_VME;
	IXGB_WRITE_REG(&adapter->hw, CTRL0, ctrl);
पूर्ण

अटल व्योम
ixgb_vlan_strip_disable(काष्ठा ixgb_adapter *adapter)
अणु
	u32 ctrl;

	/* disable VLAN tag insert/strip */
	ctrl = IXGB_READ_REG(&adapter->hw, CTRL0);
	ctrl &= ~IXGB_CTRL0_VME;
	IXGB_WRITE_REG(&adapter->hw, CTRL0, ctrl);
पूर्ण

अटल पूर्णांक
ixgb_vlan_rx_add_vid(काष्ठा net_device *netdev, __be16 proto, u16 vid)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	u32 vfta, index;

	/* add VID to filter table */

	index = (vid >> 5) & 0x7F;
	vfta = IXGB_READ_REG_ARRAY(&adapter->hw, VFTA, index);
	vfta |= (1 << (vid & 0x1F));
	ixgb_ग_लिखो_vfta(&adapter->hw, index, vfta);
	set_bit(vid, adapter->active_vlans);

	वापस 0;
पूर्ण

अटल पूर्णांक
ixgb_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev, __be16 proto, u16 vid)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	u32 vfta, index;

	/* हटाओ VID from filter table */

	index = (vid >> 5) & 0x7F;
	vfta = IXGB_READ_REG_ARRAY(&adapter->hw, VFTA, index);
	vfta &= ~(1 << (vid & 0x1F));
	ixgb_ग_लिखो_vfta(&adapter->hw, index, vfta);
	clear_bit(vid, adapter->active_vlans);

	वापस 0;
पूर्ण

अटल व्योम
ixgb_restore_vlan(काष्ठा ixgb_adapter *adapter)
अणु
	u16 vid;

	क्रम_each_set_bit(vid, adapter->active_vlans, VLAN_N_VID)
		ixgb_vlan_rx_add_vid(adapter->netdev, htons(ETH_P_8021Q), vid);
पूर्ण

/**
 * ixgb_io_error_detected - called when PCI error is detected
 * @pdev:    poपूर्णांकer to pci device with error
 * @state:   pci channel state after error
 *
 * This callback is called by the PCI subप्रणाली whenever
 * a PCI bus error is detected.
 */
अटल pci_ers_result_t ixgb_io_error_detected(काष्ठा pci_dev *pdev,
                                               pci_channel_state_t state)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);

	netअगर_device_detach(netdev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	अगर (netअगर_running(netdev))
		ixgb_करोwn(adapter, true);

	pci_disable_device(pdev);

	/* Request a slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * ixgb_io_slot_reset - called after the pci bus has been reset.
 * @pdev: poपूर्णांकer to pci device with error
 *
 * This callback is called after the PCI bus has been reset.
 * Basically, this tries to restart the card from scratch.
 * This is a लघुened version of the device probe/discovery code,
 * it resembles the first-half of the ixgb_probe() routine.
 */
अटल pci_ers_result_t ixgb_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);

	अगर (pci_enable_device(pdev)) अणु
		netअगर_err(adapter, probe, adapter->netdev,
			  "Cannot re-enable PCI device after reset\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	/* Perक्रमm card reset only on one instance of the card */
	अगर (0 != PCI_FUNC (pdev->devfn))
		वापस PCI_ERS_RESULT_RECOVERED;

	pci_set_master(pdev);

	netअगर_carrier_off(netdev);
	netअगर_stop_queue(netdev);
	ixgb_reset(adapter);

	/* Make sure the EEPROM is good */
	अगर (!ixgb_validate_eeprom_checksum(&adapter->hw)) अणु
		netअगर_err(adapter, probe, adapter->netdev,
			  "After reset, the EEPROM checksum is not valid\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण
	ixgb_get_ee_mac_addr(&adapter->hw, netdev->dev_addr);
	स_नकल(netdev->perm_addr, netdev->dev_addr, netdev->addr_len);

	अगर (!is_valid_ether_addr(netdev->perm_addr)) अणु
		netअगर_err(adapter, probe, adapter->netdev,
			  "After reset, invalid MAC address\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * ixgb_io_resume - called when its OK to resume normal operations
 * @pdev: poपूर्णांकer to pci device with error
 *
 * The error recovery driver tells us that its OK to resume
 * normal operation. Implementation resembles the second-half
 * of the ixgb_probe() routine.
 */
अटल व्योम ixgb_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);

	pci_set_master(pdev);

	अगर (netअगर_running(netdev)) अणु
		अगर (ixgb_up(adapter)) अणु
			pr_err("can't bring device back up after reset\n");
			वापस;
		पूर्ण
	पूर्ण

	netअगर_device_attach(netdev);
	mod_समयr(&adapter->watchकरोg_समयr, jअगरfies);
पूर्ण

/* ixgb_मुख्य.c */
