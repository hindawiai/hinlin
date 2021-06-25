<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/swab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/aer.h>
#समावेश <linux/log2.h>
#समावेश <linux/pci.h>
#समावेश <net/vxlan.h>

#समावेश "qlcnic.h"
#समावेश "qlcnic_sriov.h"
#समावेश "qlcnic_hw.h"

MODULE_DESCRIPTION("QLogic 1/10 GbE Converged/Intelligent Ethernet Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(QLCNIC_LINUX_VERSIONID);
MODULE_FIRMWARE(QLCNIC_UNIFIED_ROMIMAGE_NAME);

अक्षर qlcnic_driver_name[] = "qlcnic";
अटल स्थिर अक्षर qlcnic_driver_string[] = "QLogic 1/10 GbE "
	"Converged/Intelligent Ethernet Driver v" QLCNIC_LINUX_VERSIONID;

अटल पूर्णांक qlcnic_mac_learn;
module_param(qlcnic_mac_learn, पूर्णांक, 0444);
MODULE_PARM_DESC(qlcnic_mac_learn,
		 "Mac Filter (0=learning is disabled, 1=Driver learning is enabled, 2=FDB learning is enabled)");

पूर्णांक qlcnic_use_msi = 1;
MODULE_PARM_DESC(use_msi, "MSI interrupt (0=disabled, 1=enabled)");
module_param_named(use_msi, qlcnic_use_msi, पूर्णांक, 0444);

पूर्णांक qlcnic_use_msi_x = 1;
MODULE_PARM_DESC(use_msi_x, "MSI-X interrupt (0=disabled, 1=enabled)");
module_param_named(use_msi_x, qlcnic_use_msi_x, पूर्णांक, 0444);

पूर्णांक qlcnic_स्वतः_fw_reset = 1;
MODULE_PARM_DESC(स्वतः_fw_reset, "Auto firmware reset (0=disabled, 1=enabled)");
module_param_named(स्वतः_fw_reset, qlcnic_स्वतः_fw_reset, पूर्णांक, 0644);

पूर्णांक qlcnic_load_fw_file;
MODULE_PARM_DESC(load_fw_file, "Load firmware from (0=flash, 1=file, 2=POST in fast mode, 3= POST in medium mode, 4=POST in slow mode)");
module_param_named(load_fw_file, qlcnic_load_fw_file, पूर्णांक, 0444);

अटल पूर्णांक qlcnic_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
अटल व्योम qlcnic_हटाओ(काष्ठा pci_dev *pdev);
अटल पूर्णांक qlcnic_खोलो(काष्ठा net_device *netdev);
अटल पूर्णांक qlcnic_बंद(काष्ठा net_device *netdev);
अटल व्योम qlcnic_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue);
अटल व्योम qlcnic_attach_work(काष्ठा work_काष्ठा *work);
अटल व्योम qlcnic_fwinit_work(काष्ठा work_काष्ठा *work);

अटल व्योम qlcnic_idc_debug_info(काष्ठा qlcnic_adapter *adapter, u8 encoding);
अटल पूर्णांक qlcnic_can_start_firmware(काष्ठा qlcnic_adapter *adapter);

अटल irqवापस_t qlcnic_पंचांगp_पूर्णांकr(पूर्णांक irq, व्योम *data);
अटल irqवापस_t qlcnic_पूर्णांकr(पूर्णांक irq, व्योम *data);
अटल irqवापस_t qlcnic_msi_पूर्णांकr(पूर्णांक irq, व्योम *data);
अटल irqवापस_t qlcnic_msix_पूर्णांकr(पूर्णांक irq, व्योम *data);
अटल irqवापस_t qlcnic_msix_tx_पूर्णांकr(पूर्णांक irq, व्योम *data);

अटल काष्ठा net_device_stats *qlcnic_get_stats(काष्ठा net_device *netdev);
अटल पूर्णांक qlcnic_start_firmware(काष्ठा qlcnic_adapter *);

अटल व्योम qlcnic_मुक्त_lb_filters_mem(काष्ठा qlcnic_adapter *adapter);
अटल व्योम qlcnic_dev_set_npar_पढ़ोy(काष्ठा qlcnic_adapter *);
अटल पूर्णांक qlcnicvf_start_firmware(काष्ठा qlcnic_adapter *);
अटल पूर्णांक qlcnic_vlan_rx_add(काष्ठा net_device *, __be16, u16);
अटल पूर्णांक qlcnic_vlan_rx_del(काष्ठा net_device *, __be16, u16);

अटल पूर्णांक qlcnic_82xx_setup_पूर्णांकr(काष्ठा qlcnic_adapter *);
अटल व्योम qlcnic_82xx_dev_request_reset(काष्ठा qlcnic_adapter *, u32);
अटल irqवापस_t qlcnic_82xx_clear_legacy_पूर्णांकr(काष्ठा qlcnic_adapter *);
अटल pci_ers_result_t qlcnic_82xx_io_slot_reset(काष्ठा pci_dev *);
अटल पूर्णांक qlcnic_82xx_start_firmware(काष्ठा qlcnic_adapter *);
अटल व्योम qlcnic_82xx_io_resume(काष्ठा pci_dev *);
अटल व्योम qlcnic_82xx_set_mac_filter_count(काष्ठा qlcnic_adapter *);
अटल pci_ers_result_t qlcnic_82xx_io_error_detected(काष्ठा pci_dev *,
						      pci_channel_state_t);
अटल u32 qlcnic_vlan_tx_check(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	अगर (adapter->pdev->device == PCI_DEVICE_ID_QLOGIC_QLE824X)
		वापस ahw->capabilities & QLCNIC_FW_CAPABILITY_FVLANTX;
	अन्यथा
		वापस 1;
पूर्ण

/*  PCI Device ID Table  */
#घोषणा ENTRY(device) \
	अणुPCI_DEVICE(PCI_VENDOR_ID_QLOGIC, (device)), \
	.class = PCI_CLASS_NETWORK_ETHERNET << 8, .class_mask = ~0पूर्ण

अटल स्थिर काष्ठा pci_device_id qlcnic_pci_tbl[] = अणु
	ENTRY(PCI_DEVICE_ID_QLOGIC_QLE824X),
	ENTRY(PCI_DEVICE_ID_QLOGIC_QLE834X),
	ENTRY(PCI_DEVICE_ID_QLOGIC_VF_QLE834X),
	ENTRY(PCI_DEVICE_ID_QLOGIC_QLE8830),
	ENTRY(PCI_DEVICE_ID_QLOGIC_VF_QLE8C30),
	ENTRY(PCI_DEVICE_ID_QLOGIC_QLE844X),
	ENTRY(PCI_DEVICE_ID_QLOGIC_VF_QLE844X),
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, qlcnic_pci_tbl);


अंतरभूत व्योम qlcnic_update_cmd_producer(काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	ग_लिखोl(tx_ring->producer, tx_ring->crb_cmd_producer);
पूर्ण

अटल स्थिर u32 msi_tgt_status[8] = अणु
	ISR_INT_TARGET_STATUS, ISR_INT_TARGET_STATUS_F1,
	ISR_INT_TARGET_STATUS_F2, ISR_INT_TARGET_STATUS_F3,
	ISR_INT_TARGET_STATUS_F4, ISR_INT_TARGET_STATUS_F5,
	ISR_INT_TARGET_STATUS_F6, ISR_INT_TARGET_STATUS_F7
पूर्ण;

अटल स्थिर u32 qlcnic_reg_tbl[] = अणु
	0x1B20A8,	/* PEG_HALT_STAT1 */
	0x1B20AC,	/* PEG_HALT_STAT2 */
	0x1B20B0,	/* FW_HEARTBEAT */
	0x1B2100,	/* LOCK ID */
	0x1B2128,	/* FW_CAPABILITIES */
	0x1B2138,	/* drv active */
	0x1B2140,	/* dev state */
	0x1B2144,	/* drv state */
	0x1B2148,	/* drv scratch */
	0x1B214C,	/* dev partition info */
	0x1B2174,	/* drv idc ver */
	0x1B2150,	/* fw version major */
	0x1B2154,	/* fw version minor */
	0x1B2158,	/* fw version sub */
	0x1B219C,	/* npar state */
	0x1B21FC,	/* FW_IMG_VALID */
	0x1B2250,	/* CMD_PEG_STATE */
	0x1B233C,	/* RCV_PEG_STATE */
	0x1B23B4,	/* ASIC TEMP */
	0x1B216C,	/* FW api */
	0x1B2170,	/* drv op mode */
	0x13C010,	/* flash lock */
	0x13C014,	/* flash unlock */
पूर्ण;

अटल स्थिर काष्ठा qlcnic_board_info qlcnic_boards[] = अणु
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE844X,
	  0x0,
	  0x0,
	  "8400 series 10GbE Converged Network Adapter (TCP/IP Networking)" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE834X,
	  PCI_VENDOR_ID_QLOGIC,
	  0x24e,
	  "8300 Series Dual Port 10GbE Converged Network Adapter "
	  "(TCP/IP Networking)" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE834X,
	  PCI_VENDOR_ID_QLOGIC,
	  0x243,
	  "8300 Series Single Port 10GbE Converged Network Adapter "
	  "(TCP/IP Networking)" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE834X,
	  PCI_VENDOR_ID_QLOGIC,
	  0x24a,
	  "8300 Series Dual Port 10GbE Converged Network Adapter "
	  "(TCP/IP Networking)" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE834X,
	  PCI_VENDOR_ID_QLOGIC,
	  0x246,
	  "8300 Series Dual Port 10GbE Converged Network Adapter "
	  "(TCP/IP Networking)" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE834X,
	  PCI_VENDOR_ID_QLOGIC,
	  0x252,
	  "8300 Series Dual Port 10GbE Converged Network Adapter "
	  "(TCP/IP Networking)" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE834X,
	  PCI_VENDOR_ID_QLOGIC,
	  0x26e,
	  "8300 Series Dual Port 10GbE Converged Network Adapter "
	  "(TCP/IP Networking)" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE834X,
	  PCI_VENDOR_ID_QLOGIC,
	  0x260,
	  "8300 Series Dual Port 10GbE Converged Network Adapter "
	  "(TCP/IP Networking)" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE834X,
	  PCI_VENDOR_ID_QLOGIC,
	  0x266,
	  "8300 Series Single Port 10GbE Converged Network Adapter "
	  "(TCP/IP Networking)" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE834X,
	  PCI_VENDOR_ID_QLOGIC,
	  0x269,
	  "8300 Series Dual Port 10GbE Converged Network Adapter "
	  "(TCP/IP Networking)" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE834X,
	  PCI_VENDOR_ID_QLOGIC,
	  0x271,
	  "8300 Series Dual Port 10GbE Converged Network Adapter "
	  "(TCP/IP Networking)" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE834X,
	  0x0, 0x0, "8300 Series 1/10GbE Controller" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE8830,
	  0x0,
	  0x0,
	  "8830 Series 1/10GbE Controller" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE824X,
	  PCI_VENDOR_ID_QLOGIC,
	  0x203,
	  "8200 Series Single Port 10GbE Converged Network Adapter"
	  "(TCP/IP Networking)" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE824X,
	  PCI_VENDOR_ID_QLOGIC,
	  0x207,
	  "8200 Series Dual Port 10GbE Converged Network Adapter"
	  "(TCP/IP Networking)" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE824X,
	  PCI_VENDOR_ID_QLOGIC,
	  0x20b,
	  "3200 Series Dual Port 10Gb Intelligent Ethernet Adapter" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE824X,
	  PCI_VENDOR_ID_QLOGIC,
	  0x20c,
	  "3200 Series Quad Port 1Gb Intelligent Ethernet Adapter" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE824X,
	  PCI_VENDOR_ID_QLOGIC,
	  0x20f,
	  "3200 Series Single Port 10Gb Intelligent Ethernet Adapter" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE824X,
	  0x103c, 0x3733,
	  "NC523SFP 10Gb 2-port Server Adapter" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE824X,
	  0x103c, 0x3346,
	  "CN1000Q Dual Port Converged Network Adapter" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE824X,
	  PCI_VENDOR_ID_QLOGIC,
	  0x210,
	  "QME8242-k 10GbE Dual Port Mezzanine Card" पूर्ण,
	अणु PCI_VENDOR_ID_QLOGIC,
	  PCI_DEVICE_ID_QLOGIC_QLE824X,
	  0x0, 0x0, "cLOM8214 1/10GbE Controller" पूर्ण,
पूर्ण;

#घोषणा NUM_SUPPORTED_BOARDS ARRAY_SIZE(qlcnic_boards)

अटल स्थिर
काष्ठा qlcnic_legacy_पूर्णांकr_set legacy_पूर्णांकr[] = QLCNIC_LEGACY_INTR_CONFIG;

पूर्णांक qlcnic_alloc_sds_rings(काष्ठा qlcnic_recv_context *recv_ctx, पूर्णांक count)
अणु
	पूर्णांक size = माप(काष्ठा qlcnic_host_sds_ring) * count;

	recv_ctx->sds_rings = kzalloc(size, GFP_KERNEL);

	वापस recv_ctx->sds_rings == शून्य;
पूर्ण

व्योम qlcnic_मुक्त_sds_rings(काष्ठा qlcnic_recv_context *recv_ctx)
अणु
	kमुक्त(recv_ctx->sds_rings);
	recv_ctx->sds_rings = शून्य;
पूर्ण

पूर्णांक qlcnic_पढ़ो_mac_addr(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	u8 mac_addr[ETH_ALEN];
	पूर्णांक ret;

	ret = qlcnic_get_mac_address(adapter, mac_addr,
				     adapter->ahw->pci_func);
	अगर (ret)
		वापस ret;

	स_नकल(netdev->dev_addr, mac_addr, ETH_ALEN);
	स_नकल(adapter->mac_addr, netdev->dev_addr, netdev->addr_len);

	/* set station address */

	अगर (!is_valid_ether_addr(netdev->dev_addr))
		dev_warn(&pdev->dev, "Bad MAC address %pM.\n",
					netdev->dev_addr);

	वापस 0;
पूर्ण

अटल व्योम qlcnic_delete_adapter_mac(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_mac_vlan_list *cur;
	काष्ठा list_head *head;

	list_क्रम_each(head, &adapter->mac_list) अणु
		cur = list_entry(head, काष्ठा qlcnic_mac_vlan_list, list);
		अगर (ether_addr_equal_unaligned(adapter->mac_addr, cur->mac_addr)) अणु
			qlcnic_sre_macaddr_change(adapter, cur->mac_addr,
						  0, QLCNIC_MAC_DEL);
			list_del(&cur->list);
			kमुक्त(cur);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक qlcnic_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा sockaddr *addr = p;

	अगर (qlcnic_sriov_vf_check(adapter))
		वापस -EINVAL;

	अगर ((adapter->flags & QLCNIC_MAC_OVERRIDE_DISABLED))
		वापस -EOPNOTSUPP;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EINVAL;

	अगर (ether_addr_equal_unaligned(adapter->mac_addr, addr->sa_data) &&
	    ether_addr_equal_unaligned(netdev->dev_addr, addr->sa_data))
		वापस 0;

	अगर (test_bit(__QLCNIC_DEV_UP, &adapter->state)) अणु
		netअगर_device_detach(netdev);
		qlcnic_napi_disable(adapter);
	पूर्ण

	qlcnic_delete_adapter_mac(adapter);
	स_नकल(adapter->mac_addr, addr->sa_data, netdev->addr_len);
	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	qlcnic_set_multi(adapter->netdev);

	अगर (test_bit(__QLCNIC_DEV_UP, &adapter->state)) अणु
		netअगर_device_attach(netdev);
		qlcnic_napi_enable(adapter);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_fdb_del(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
			काष्ठा net_device *netdev,
			स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err = -EOPNOTSUPP;

	अगर (!adapter->fdb_mac_learn)
		वापस nकरो_dflt_fdb_del(ndm, tb, netdev, addr, vid);

	अगर ((adapter->flags & QLCNIC_ESWITCH_ENABLED) ||
	    qlcnic_sriov_check(adapter)) अणु
		अगर (is_unicast_ether_addr(addr)) अणु
			err = dev_uc_del(netdev, addr);
			अगर (!err)
				err = qlcnic_nic_del_mac(adapter, addr);
		पूर्ण अन्यथा अगर (is_multicast_ether_addr(addr)) अणु
			err = dev_mc_del(netdev, addr);
		पूर्ण अन्यथा अणु
			err =  -EINVAL;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_fdb_add(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
			काष्ठा net_device *netdev,
			स्थिर अचिन्हित अक्षर *addr, u16 vid, u16 flags,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err = 0;

	अगर (!adapter->fdb_mac_learn)
		वापस nकरो_dflt_fdb_add(ndm, tb, netdev, addr, vid, flags);

	अगर (!(adapter->flags & QLCNIC_ESWITCH_ENABLED) &&
	    !qlcnic_sriov_check(adapter)) अणु
		pr_info("%s: FDB e-switch is not enabled\n", __func__);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (ether_addr_equal(addr, adapter->mac_addr))
		वापस err;

	अगर (is_unicast_ether_addr(addr)) अणु
		अगर (netdev_uc_count(netdev) < adapter->ahw->max_uc_count)
			err = dev_uc_add_excl(netdev, addr);
		अन्यथा
			err = -ENOMEM;
	पूर्ण अन्यथा अगर (is_multicast_ether_addr(addr)) अणु
		err = dev_mc_add_excl(netdev, addr);
	पूर्ण अन्यथा अणु
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_fdb_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *ncb,
			काष्ठा net_device *netdev,
			काष्ठा net_device *filter_dev, पूर्णांक *idx)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err = 0;

	अगर (!adapter->fdb_mac_learn)
		वापस nकरो_dflt_fdb_dump(skb, ncb, netdev, filter_dev, idx);

	अगर ((adapter->flags & QLCNIC_ESWITCH_ENABLED) ||
	    qlcnic_sriov_check(adapter))
		err = nकरो_dflt_fdb_dump(skb, ncb, netdev, filter_dev, idx);

	वापस err;
पूर्ण

अटल व्योम qlcnic_82xx_cancel_idc_work(काष्ठा qlcnic_adapter *adapter)
अणु
	जबतक (test_and_set_bit(__QLCNIC_RESETTING, &adapter->state))
		usleep_range(10000, 11000);

	अगर (!adapter->fw_work.work.func)
		वापस;

	cancel_delayed_work_sync(&adapter->fw_work);
पूर्ण

अटल पूर्णांक qlcnic_get_phys_port_id(काष्ठा net_device *netdev,
				   काष्ठा netdev_phys_item_id *ppid)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	अगर (!(adapter->flags & QLCNIC_HAS_PHYS_PORT_ID))
		वापस -EOPNOTSUPP;

	ppid->id_len = माप(ahw->phys_port_id);
	स_नकल(ppid->id, ahw->phys_port_id, ppid->id_len);

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_udp_tunnel_sync(काष्ठा net_device *dev, अचिन्हित पूर्णांक table)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);
	काष्ठा udp_tunnel_info ti;
	पूर्णांक err;

	udp_tunnel_nic_get_port(dev, table, 0, &ti);
	अगर (ti.port) अणु
		err = qlcnic_set_vxlan_port(adapter, ntohs(ti.port));
		अगर (err)
			वापस err;
	पूर्ण

	वापस qlcnic_set_vxlan_parsing(adapter, ntohs(ti.port));
पूर्ण

अटल स्थिर काष्ठा udp_tunnel_nic_info qlcnic_udp_tunnels = अणु
	.sync_table	= qlcnic_udp_tunnel_sync,
	.flags		= UDP_TUNNEL_NIC_INFO_MAY_SLEEP,
	.tables		= अणु
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_VXLAN, पूर्ण,
	पूर्ण,
पूर्ण;

अटल netdev_features_t qlcnic_features_check(काष्ठा sk_buff *skb,
					       काष्ठा net_device *dev,
					       netdev_features_t features)
अणु
	features = vlan_features_check(skb, features);
	वापस vxlan_features_check(skb, features);
पूर्ण

अटल स्थिर काष्ठा net_device_ops qlcnic_netdev_ops = अणु
	.nकरो_खोलो	   = qlcnic_खोलो,
	.nकरो_stop	   = qlcnic_बंद,
	.nकरो_start_xmit    = qlcnic_xmit_frame,
	.nकरो_get_stats	   = qlcnic_get_stats,
	.nकरो_validate_addr = eth_validate_addr,
	.nकरो_set_rx_mode   = qlcnic_set_multi,
	.nकरो_set_mac_address    = qlcnic_set_mac,
	.nकरो_change_mtu	   = qlcnic_change_mtu,
	.nकरो_fix_features  = qlcnic_fix_features,
	.nकरो_set_features  = qlcnic_set_features,
	.nकरो_tx_समयout	   = qlcnic_tx_समयout,
	.nकरो_vlan_rx_add_vid	= qlcnic_vlan_rx_add,
	.nकरो_vlan_rx_समाप्त_vid	= qlcnic_vlan_rx_del,
	.nकरो_fdb_add		= qlcnic_fdb_add,
	.nकरो_fdb_del		= qlcnic_fdb_del,
	.nकरो_fdb_dump		= qlcnic_fdb_dump,
	.nकरो_get_phys_port_id	= qlcnic_get_phys_port_id,
	.nकरो_features_check	= qlcnic_features_check,
#अगर_घोषित CONFIG_QLCNIC_SRIOV
	.nकरो_set_vf_mac		= qlcnic_sriov_set_vf_mac,
	.nकरो_set_vf_rate	= qlcnic_sriov_set_vf_tx_rate,
	.nकरो_get_vf_config	= qlcnic_sriov_get_vf_config,
	.nकरो_set_vf_vlan	= qlcnic_sriov_set_vf_vlan,
	.nकरो_set_vf_spoofchk	= qlcnic_sriov_set_vf_spoofchk,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा net_device_ops qlcnic_netdev_failed_ops = अणु
	.nकरो_खोलो	   = qlcnic_खोलो,
पूर्ण;

अटल काष्ठा qlcnic_nic_ढाँचा qlcnic_ops = अणु
	.config_bridged_mode	= qlcnic_config_bridged_mode,
	.config_led		= qlcnic_82xx_config_led,
	.start_firmware		= qlcnic_82xx_start_firmware,
	.request_reset		= qlcnic_82xx_dev_request_reset,
	.cancel_idc_work	= qlcnic_82xx_cancel_idc_work,
	.napi_add		= qlcnic_82xx_napi_add,
	.napi_del		= qlcnic_82xx_napi_del,
	.config_ipaddr		= qlcnic_82xx_config_ipaddr,
	.shutकरोwn		= qlcnic_82xx_shutकरोwn,
	.resume			= qlcnic_82xx_resume,
	.clear_legacy_पूर्णांकr	= qlcnic_82xx_clear_legacy_पूर्णांकr,
पूर्ण;

काष्ठा qlcnic_nic_ढाँचा qlcnic_vf_ops = अणु
	.config_bridged_mode	= qlcnicvf_config_bridged_mode,
	.config_led		= qlcnicvf_config_led,
	.start_firmware		= qlcnicvf_start_firmware
पूर्ण;

अटल काष्ठा qlcnic_hardware_ops qlcnic_hw_ops = अणु
	.पढ़ो_crb			= qlcnic_82xx_पढ़ो_crb,
	.ग_लिखो_crb			= qlcnic_82xx_ग_लिखो_crb,
	.पढ़ो_reg			= qlcnic_82xx_hw_पढ़ो_wx_2M,
	.ग_लिखो_reg			= qlcnic_82xx_hw_ग_लिखो_wx_2M,
	.get_mac_address		= qlcnic_82xx_get_mac_address,
	.setup_पूर्णांकr			= qlcnic_82xx_setup_पूर्णांकr,
	.alloc_mbx_args			= qlcnic_82xx_alloc_mbx_args,
	.mbx_cmd			= qlcnic_82xx_issue_cmd,
	.get_func_no			= qlcnic_82xx_get_func_no,
	.api_lock			= qlcnic_82xx_api_lock,
	.api_unlock			= qlcnic_82xx_api_unlock,
	.add_sysfs			= qlcnic_82xx_add_sysfs,
	.हटाओ_sysfs			= qlcnic_82xx_हटाओ_sysfs,
	.process_lb_rcv_ring_diag	= qlcnic_82xx_process_rcv_ring_diag,
	.create_rx_ctx			= qlcnic_82xx_fw_cmd_create_rx_ctx,
	.create_tx_ctx			= qlcnic_82xx_fw_cmd_create_tx_ctx,
	.del_rx_ctx			= qlcnic_82xx_fw_cmd_del_rx_ctx,
	.del_tx_ctx			= qlcnic_82xx_fw_cmd_del_tx_ctx,
	.setup_link_event		= qlcnic_82xx_linkevent_request,
	.get_nic_info			= qlcnic_82xx_get_nic_info,
	.get_pci_info			= qlcnic_82xx_get_pci_info,
	.set_nic_info			= qlcnic_82xx_set_nic_info,
	.change_macvlan			= qlcnic_82xx_sre_macaddr_change,
	.napi_enable			= qlcnic_82xx_napi_enable,
	.napi_disable			= qlcnic_82xx_napi_disable,
	.config_पूर्णांकr_coal		= qlcnic_82xx_config_पूर्णांकr_coalesce,
	.config_rss			= qlcnic_82xx_config_rss,
	.config_hw_lro			= qlcnic_82xx_config_hw_lro,
	.config_loopback		= qlcnic_82xx_set_lb_mode,
	.clear_loopback			= qlcnic_82xx_clear_lb_mode,
	.config_promisc_mode		= qlcnic_82xx_nic_set_promisc,
	.change_l2_filter		= qlcnic_82xx_change_filter,
	.get_board_info			= qlcnic_82xx_get_board_info,
	.set_mac_filter_count		= qlcnic_82xx_set_mac_filter_count,
	.मुक्त_mac_list			= qlcnic_82xx_मुक्त_mac_list,
	.पढ़ो_phys_port_id		= qlcnic_82xx_पढ़ो_phys_port_id,
	.io_error_detected		= qlcnic_82xx_io_error_detected,
	.io_slot_reset			= qlcnic_82xx_io_slot_reset,
	.io_resume			= qlcnic_82xx_io_resume,
	.get_beacon_state		= qlcnic_82xx_get_beacon_state,
	.enable_sds_पूर्णांकr		= qlcnic_82xx_enable_sds_पूर्णांकr,
	.disable_sds_पूर्णांकr		= qlcnic_82xx_disable_sds_पूर्णांकr,
	.enable_tx_पूर्णांकr			= qlcnic_82xx_enable_tx_पूर्णांकr,
	.disable_tx_पूर्णांकr		= qlcnic_82xx_disable_tx_पूर्णांकr,
	.get_saved_state		= qlcnic_82xx_get_saved_state,
	.set_saved_state		= qlcnic_82xx_set_saved_state,
	.cache_पंचांगpl_hdr_values		= qlcnic_82xx_cache_पंचांगpl_hdr_values,
	.get_cap_size			= qlcnic_82xx_get_cap_size,
	.set_sys_info			= qlcnic_82xx_set_sys_info,
	.store_cap_mask			= qlcnic_82xx_store_cap_mask,
	.encap_rx_offload               = qlcnic_82xx_encap_rx_offload,
	.encap_tx_offload               = qlcnic_82xx_encap_tx_offload,
पूर्ण;

अटल पूर्णांक qlcnic_check_multi_tx_capability(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	अगर (qlcnic_82xx_check(adapter) &&
	    (ahw->extra_capability[0] & QLCNIC_FW_CAPABILITY_2_MULTI_TX)) अणु
		test_and_set_bit(__QLCNIC_MULTI_TX_UNIQUE, &adapter->state);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक qlcnic_max_rings(काष्ठा qlcnic_adapter *adapter, u8 ring_cnt,
			    पूर्णांक queue_type)
अणु
	पूर्णांक num_rings, max_rings = QLCNIC_MAX_SDS_RINGS;

	अगर (queue_type == QLCNIC_RX_QUEUE)
		max_rings = adapter->max_sds_rings;
	अन्यथा अगर (queue_type == QLCNIC_TX_QUEUE)
		max_rings = adapter->max_tx_rings;

	num_rings = roundकरोwn_घात_of_two(min_t(पूर्णांक, num_online_cpus(),
					      max_rings));

	अगर (ring_cnt > num_rings)
		वापस num_rings;
	अन्यथा
		वापस ring_cnt;
पूर्ण

व्योम qlcnic_set_tx_ring_count(काष्ठा qlcnic_adapter *adapter, u8 tx_cnt)
अणु
	/* 83xx adapter करोes not have max_tx_rings पूर्णांकialized in probe */
	अगर (adapter->max_tx_rings)
		adapter->drv_tx_rings = qlcnic_max_rings(adapter, tx_cnt,
							 QLCNIC_TX_QUEUE);
	अन्यथा
		adapter->drv_tx_rings = tx_cnt;
पूर्ण

व्योम qlcnic_set_sds_ring_count(काष्ठा qlcnic_adapter *adapter, u8 rx_cnt)
अणु
	/* 83xx adapter करोes not have max_sds_rings पूर्णांकialized in probe */
	अगर (adapter->max_sds_rings)
		adapter->drv_sds_rings = qlcnic_max_rings(adapter, rx_cnt,
							  QLCNIC_RX_QUEUE);
	अन्यथा
		adapter->drv_sds_rings = rx_cnt;
पूर्ण

पूर्णांक qlcnic_setup_tss_rss_पूर्णांकr(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक num_msix = 0, err = 0, vector;

	adapter->flags &= ~QLCNIC_TSS_RSS;

	अगर (adapter->drv_tss_rings > 0)
		num_msix += adapter->drv_tss_rings;
	अन्यथा
		num_msix += adapter->drv_tx_rings;

	अगर (adapter->drv_rss_rings > 0)
		num_msix += adapter->drv_rss_rings;
	अन्यथा
		num_msix += adapter->drv_sds_rings;

	अगर (qlcnic_83xx_check(adapter))
		num_msix += 1;

	अगर (!adapter->msix_entries) अणु
		adapter->msix_entries = kसुस्मृति(num_msix,
						माप(काष्ठा msix_entry),
						GFP_KERNEL);
		अगर (!adapter->msix_entries)
			वापस -ENOMEM;
	पूर्ण

	क्रम (vector = 0; vector < num_msix; vector++)
		adapter->msix_entries[vector].entry = vector;

restore:
	err = pci_enable_msix_exact(pdev, adapter->msix_entries, num_msix);
	अगर (err == -ENOSPC) अणु
		अगर (!adapter->drv_tss_rings && !adapter->drv_rss_rings)
			वापस err;

		netdev_info(adapter->netdev,
			    "Unable to allocate %d MSI-X vectors, Available vectors %d\n",
			    num_msix, err);

		num_msix = adapter->drv_tx_rings + adapter->drv_sds_rings;

		/* Set rings to 0 so we can restore original TSS/RSS count */
		adapter->drv_tss_rings = 0;
		adapter->drv_rss_rings = 0;

		अगर (qlcnic_83xx_check(adapter))
			num_msix += 1;

		netdev_info(adapter->netdev,
			    "Restoring %d Tx, %d SDS rings for total %d vectors.\n",
			    adapter->drv_tx_rings, adapter->drv_sds_rings,
			    num_msix);

		जाओ restore;
	पूर्ण अन्यथा अगर (err < 0) अणु
		वापस err;
	पूर्ण

	adapter->ahw->num_msix = num_msix;
	अगर (adapter->drv_tss_rings > 0)
		adapter->drv_tx_rings = adapter->drv_tss_rings;

	अगर (adapter->drv_rss_rings > 0)
		adapter->drv_sds_rings = adapter->drv_rss_rings;

	वापस 0;
पूर्ण

पूर्णांक qlcnic_enable_msix(काष्ठा qlcnic_adapter *adapter, u32 num_msix)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक err, vector;

	अगर (!adapter->msix_entries) अणु
		adapter->msix_entries = kसुस्मृति(num_msix,
						माप(काष्ठा msix_entry),
						GFP_KERNEL);
		अगर (!adapter->msix_entries)
			वापस -ENOMEM;
	पूर्ण

	adapter->flags &= ~(QLCNIC_MSI_ENABLED | QLCNIC_MSIX_ENABLED);

	अगर (adapter->ahw->msix_supported) अणु
enable_msix:
		क्रम (vector = 0; vector < num_msix; vector++)
			adapter->msix_entries[vector].entry = vector;

		err = pci_enable_msix_range(pdev,
					    adapter->msix_entries, 1, num_msix);

		अगर (err == num_msix) अणु
			adapter->flags |= QLCNIC_MSIX_ENABLED;
			adapter->ahw->num_msix = num_msix;
			dev_info(&pdev->dev, "using msi-x interrupts\n");
			वापस 0;
		पूर्ण अन्यथा अगर (err > 0) अणु
			pci_disable_msix(pdev);

			dev_info(&pdev->dev,
				 "Unable to allocate %d MSI-X vectors, Available vectors %d\n",
				 num_msix, err);

			अगर (qlcnic_82xx_check(adapter)) अणु
				num_msix = roundकरोwn_घात_of_two(err);
				अगर (err < QLCNIC_82XX_MINIMUM_VECTOR)
					वापस -ENOSPC;
			पूर्ण अन्यथा अणु
				num_msix = roundकरोwn_घात_of_two(err - 1);
				num_msix += 1;
				अगर (err < QLCNIC_83XX_MINIMUM_VECTOR)
					वापस -ENOSPC;
			पूर्ण

			अगर (qlcnic_82xx_check(adapter) &&
			    !qlcnic_check_multi_tx(adapter)) अणु
				adapter->drv_sds_rings = num_msix;
				adapter->drv_tx_rings = QLCNIC_SINGLE_RING;
			पूर्ण अन्यथा अणु
				/* Distribute vectors equally */
				adapter->drv_tx_rings = num_msix / 2;
				adapter->drv_sds_rings = adapter->drv_tx_rings;
			पूर्ण

			अगर (num_msix) अणु
				dev_info(&pdev->dev,
					 "Trying to allocate %d MSI-X interrupt vectors\n",
					 num_msix);
				जाओ enable_msix;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_info(&pdev->dev,
				 "Unable to allocate %d MSI-X vectors, err=%d\n",
				 num_msix, err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक qlcnic_82xx_calculate_msix_vector(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक num_msix;

	num_msix = adapter->drv_sds_rings;

	अगर (qlcnic_check_multi_tx(adapter))
		num_msix += adapter->drv_tx_rings;
	अन्यथा
		num_msix += QLCNIC_SINGLE_RING;

	वापस num_msix;
पूर्ण

अटल पूर्णांक qlcnic_enable_msi_legacy(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक err = 0;
	u32 offset, mask_reg;
	स्थिर काष्ठा qlcnic_legacy_पूर्णांकr_set *legacy_पूर्णांकrp;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा pci_dev *pdev = adapter->pdev;

	अगर (qlcnic_use_msi && !pci_enable_msi(pdev)) अणु
		adapter->flags |= QLCNIC_MSI_ENABLED;
		offset = msi_tgt_status[adapter->ahw->pci_func];
		adapter->tgt_status_reg = qlcnic_get_ioaddr(adapter->ahw,
							    offset);
		dev_info(&pdev->dev, "using msi interrupts\n");
		adapter->msix_entries[0].vector = pdev->irq;
		वापस err;
	पूर्ण

	अगर (qlcnic_use_msi || qlcnic_use_msi_x)
		वापस -EOPNOTSUPP;

	legacy_पूर्णांकrp = &legacy_पूर्णांकr[adapter->ahw->pci_func];
	adapter->ahw->पूर्णांक_vec_bit = legacy_पूर्णांकrp->पूर्णांक_vec_bit;
	offset = legacy_पूर्णांकrp->tgt_status_reg;
	adapter->tgt_status_reg = qlcnic_get_ioaddr(ahw, offset);
	mask_reg = legacy_पूर्णांकrp->tgt_mask_reg;
	adapter->tgt_mask_reg = qlcnic_get_ioaddr(ahw, mask_reg);
	adapter->isr_पूर्णांक_vec = qlcnic_get_ioaddr(ahw, ISR_INT_VECTOR);
	adapter->crb_पूर्णांक_state_reg = qlcnic_get_ioaddr(ahw, ISR_INT_STATE_REG);
	dev_info(&pdev->dev, "using legacy interrupts\n");
	adapter->msix_entries[0].vector = pdev->irq;
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_82xx_setup_पूर्णांकr(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक num_msix, err = 0;

	अगर (adapter->flags & QLCNIC_TSS_RSS) अणु
		err = qlcnic_setup_tss_rss_पूर्णांकr(adapter);
		अगर (err < 0)
			वापस err;
		num_msix = adapter->ahw->num_msix;
	पूर्ण अन्यथा अणु
		num_msix = qlcnic_82xx_calculate_msix_vector(adapter);

		err = qlcnic_enable_msix(adapter, num_msix);
		अगर (err == -ENOMEM)
			वापस err;

		अगर (!(adapter->flags & QLCNIC_MSIX_ENABLED)) अणु
			qlcnic_disable_multi_tx(adapter);
			adapter->drv_sds_rings = QLCNIC_SINGLE_RING;

			err = qlcnic_enable_msi_legacy(adapter);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qlcnic_82xx_mq_पूर्णांकrpt(काष्ठा qlcnic_adapter *adapter, पूर्णांक op_type)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक err, i;

	अगर (qlcnic_check_multi_tx(adapter) &&
	    !ahw->diag_test &&
	    (adapter->flags & QLCNIC_MSIX_ENABLED)) अणु
		ahw->पूर्णांकr_tbl =
			vzalloc(array_size(माप(काष्ठा qlcnic_पूर्णांकrpt_config),
					   ahw->num_msix));
		अगर (!ahw->पूर्णांकr_tbl)
			वापस -ENOMEM;

		क्रम (i = 0; i < ahw->num_msix; i++) अणु
			ahw->पूर्णांकr_tbl[i].type = QLCNIC_INTRPT_MSIX;
			ahw->पूर्णांकr_tbl[i].id = i;
			ahw->पूर्णांकr_tbl[i].src = 0;
		पूर्ण

		err = qlcnic_82xx_config_पूर्णांकrpt(adapter, 1);
		अगर (err)
			dev_err(&adapter->pdev->dev,
				"Failed to configure Interrupt for %d vector\n",
				ahw->num_msix);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम qlcnic_tearकरोwn_पूर्णांकr(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (adapter->flags & QLCNIC_MSIX_ENABLED)
		pci_disable_msix(adapter->pdev);
	अगर (adapter->flags & QLCNIC_MSI_ENABLED)
		pci_disable_msi(adapter->pdev);

	kमुक्त(adapter->msix_entries);
	adapter->msix_entries = शून्य;

	अगर (adapter->ahw->पूर्णांकr_tbl) अणु
		vमुक्त(adapter->ahw->पूर्णांकr_tbl);
		adapter->ahw->पूर्णांकr_tbl = शून्य;
	पूर्ण
पूर्ण

अटल व्योम qlcnic_cleanup_pci_map(काष्ठा qlcnic_hardware_context *ahw)
अणु
	अगर (ahw->pci_base0 != शून्य)
		iounmap(ahw->pci_base0);
पूर्ण

अटल पूर्णांक qlcnic_get_act_pci_func(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_pci_info *pci_info;
	पूर्णांक ret;

	अगर (!(adapter->flags & QLCNIC_ESWITCH_ENABLED)) अणु
		चयन (ahw->port_type) अणु
		हाल QLCNIC_GBE:
			ahw->total_nic_func = QLCNIC_NIU_MAX_GBE_PORTS;
			अवरोध;
		हाल QLCNIC_XGBE:
			ahw->total_nic_func = QLCNIC_NIU_MAX_XG_PORTS;
			अवरोध;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (ahw->op_mode == QLCNIC_MGMT_FUNC)
		वापस 0;

	pci_info = kसुस्मृति(ahw->max_vnic_func, माप(*pci_info), GFP_KERNEL);
	अगर (!pci_info)
		वापस -ENOMEM;

	ret = qlcnic_get_pci_info(adapter, pci_info);
	kमुक्त(pci_info);
	वापस ret;
पूर्ण

अटल bool qlcnic_port_eचयन_cfg_capability(काष्ठा qlcnic_adapter *adapter)
अणु
	bool ret = false;

	अगर (qlcnic_84xx_check(adapter)) अणु
		ret = true;
	पूर्ण अन्यथा अगर (qlcnic_83xx_check(adapter)) अणु
		अगर (adapter->ahw->extra_capability[0] &
		    QLCNIC_FW_CAPABILITY_2_PER_PORT_ESWITCH_CFG)
			ret = true;
		अन्यथा
			ret = false;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक qlcnic_init_pci_info(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_pci_info *pci_info;
	पूर्णांक i, id = 0, ret = 0, j = 0;
	u16 act_pci_func;
	u8 pfn;

	pci_info = kसुस्मृति(ahw->max_vnic_func, माप(*pci_info), GFP_KERNEL);
	अगर (!pci_info)
		वापस -ENOMEM;

	ret = qlcnic_get_pci_info(adapter, pci_info);
	अगर (ret)
		जाओ err_pci_info;

	act_pci_func = ahw->total_nic_func;

	adapter->npars = kसुस्मृति(act_pci_func,
				 माप(काष्ठा qlcnic_npar_info),
				 GFP_KERNEL);
	अगर (!adapter->npars) अणु
		ret = -ENOMEM;
		जाओ err_pci_info;
	पूर्ण

	adapter->eचयन = kसुस्मृति(QLCNIC_NIU_MAX_XG_PORTS,
				   माप(काष्ठा qlcnic_eचयन),
				   GFP_KERNEL);
	अगर (!adapter->eचयन) अणु
		ret = -ENOMEM;
		जाओ err_npars;
	पूर्ण

	क्रम (i = 0; i < ahw->max_vnic_func; i++) अणु
		pfn = pci_info[i].id;

		अगर (pfn >= ahw->max_vnic_func) अणु
			ret = -EINVAL;
			dev_err(&adapter->pdev->dev, "%s: Invalid function 0x%x, max 0x%x\n",
				__func__, pfn, ahw->max_vnic_func);
			जाओ err_eचयन;
		पूर्ण

		अगर (!pci_info[i].active ||
		    (pci_info[i].type != QLCNIC_TYPE_NIC))
			जारी;

		अगर (qlcnic_port_eचयन_cfg_capability(adapter)) अणु
			अगर (!qlcnic_83xx_set_port_eचयन_status(adapter, pfn,
								 &id))
				adapter->npars[j].eचयन_status = true;
			अन्यथा
				जारी;
		पूर्ण अन्यथा अणु
			adapter->npars[j].eचयन_status = true;
		पूर्ण

		adapter->npars[j].pci_func = pfn;
		adapter->npars[j].active = (u8)pci_info[i].active;
		adapter->npars[j].type = (u8)pci_info[i].type;
		adapter->npars[j].phy_port = (u8)pci_info[i].शेष_port;
		adapter->npars[j].min_bw = pci_info[i].tx_min_bw;
		adapter->npars[j].max_bw = pci_info[i].tx_max_bw;

		स_नकल(&adapter->npars[j].mac, &pci_info[i].mac, ETH_ALEN);
		j++;
	पूर्ण

	/* Update eSwitch status क्रम adapters without per port eSwitch
	 * configuration capability
	 */
	अगर (!qlcnic_port_eचयन_cfg_capability(adapter)) अणु
		क्रम (i = 0; i < QLCNIC_NIU_MAX_XG_PORTS; i++)
			adapter->eचयन[i].flags |= QLCNIC_SWITCH_ENABLE;
	पूर्ण

	kमुक्त(pci_info);
	वापस 0;

err_eचयन:
	kमुक्त(adapter->eचयन);
	adapter->eचयन = शून्य;
err_npars:
	kमुक्त(adapter->npars);
	adapter->npars = शून्य;
err_pci_info:
	kमुक्त(pci_info);

	वापस ret;
पूर्ण

अटल पूर्णांक
qlcnic_set_function_modes(काष्ठा qlcnic_adapter *adapter)
अणु
	u8 id;
	पूर्णांक ret;
	u32 data = QLCNIC_MGMT_FUNC;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	ret = qlcnic_api_lock(adapter);
	अगर (ret)
		जाओ err_lock;

	id = ahw->pci_func;
	data = QLC_SHARED_REG_RD32(adapter, QLCNIC_DRV_OP_MODE);
	data = (data & ~QLC_DEV_SET_DRV(0xf, id)) |
	       QLC_DEV_SET_DRV(QLCNIC_MGMT_FUNC, id);
	QLC_SHARED_REG_WR32(adapter, QLCNIC_DRV_OP_MODE, data);
	qlcnic_api_unlock(adapter);
err_lock:
	वापस ret;
पूर्ण

अटल व्योम qlcnic_check_vf(काष्ठा qlcnic_adapter *adapter,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	u32 op_mode, priv_level;

	/* Determine FW API version */
	adapter->ahw->fw_hal_version = QLC_SHARED_REG_RD32(adapter,
							   QLCNIC_FW_API);

	/* Find PCI function number */
	qlcnic_get_func_no(adapter);

	/* Determine function privilege level */
	op_mode = QLC_SHARED_REG_RD32(adapter, QLCNIC_DRV_OP_MODE);
	अगर (op_mode == QLC_DEV_DRV_DEFAULT)
		priv_level = QLCNIC_MGMT_FUNC;
	अन्यथा
		priv_level = QLC_DEV_GET_DRV(op_mode, adapter->ahw->pci_func);

	अगर (priv_level == QLCNIC_NON_PRIV_FUNC) अणु
		adapter->ahw->op_mode = QLCNIC_NON_PRIV_FUNC;
		dev_info(&adapter->pdev->dev,
			"HAL Version: %d Non Privileged function\n",
			 adapter->ahw->fw_hal_version);
		adapter->nic_ops = &qlcnic_vf_ops;
	पूर्ण अन्यथा
		adapter->nic_ops = &qlcnic_ops;
पूर्ण

#घोषणा QLCNIC_82XX_BAR0_LENGTH 0x00200000UL
#घोषणा QLCNIC_83XX_BAR0_LENGTH 0x4000
अटल व्योम qlcnic_get_bar_length(u32 dev_id, uदीर्घ *bar)
अणु
	चयन (dev_id) अणु
	हाल PCI_DEVICE_ID_QLOGIC_QLE824X:
		*bar = QLCNIC_82XX_BAR0_LENGTH;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_QLE834X:
	हाल PCI_DEVICE_ID_QLOGIC_QLE8830:
	हाल PCI_DEVICE_ID_QLOGIC_QLE844X:
	हाल PCI_DEVICE_ID_QLOGIC_VF_QLE834X:
	हाल PCI_DEVICE_ID_QLOGIC_VF_QLE844X:
	हाल PCI_DEVICE_ID_QLOGIC_VF_QLE8C30:
		*bar = QLCNIC_83XX_BAR0_LENGTH;
		अवरोध;
	शेष:
		*bar = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक qlcnic_setup_pci_map(काष्ठा pci_dev *pdev,
				काष्ठा qlcnic_hardware_context *ahw)
अणु
	u32 offset;
	व्योम __iomem *mem_ptr0 = शून्य;
	अचिन्हित दीर्घ mem_len, pci_len0 = 0, bar0_len;

	/* remap phys address */
	mem_len = pci_resource_len(pdev, 0);

	qlcnic_get_bar_length(pdev->device, &bar0_len);
	अगर (mem_len >= bar0_len) अणु

		mem_ptr0 = pci_ioremap_bar(pdev, 0);
		अगर (mem_ptr0 == शून्य) अणु
			dev_err(&pdev->dev, "failed to map PCI bar 0\n");
			वापस -EIO;
		पूर्ण
		pci_len0 = mem_len;
	पूर्ण अन्यथा अणु
		वापस -EIO;
	पूर्ण

	dev_info(&pdev->dev, "%dKB memory map\n", (पूर्णांक)(mem_len >> 10));

	ahw->pci_base0 = mem_ptr0;
	ahw->pci_len0 = pci_len0;
	offset = QLCNIC_PCIX_PS_REG(PCIX_OCM_WINDOW_REG(ahw->pci_func));
	qlcnic_get_ioaddr(ahw, offset);

	वापस 0;
पूर्ण

अटल bool qlcnic_validate_subप्रणाली_id(काष्ठा qlcnic_adapter *adapter,
					 पूर्णांक index)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	अचिन्हित लघु subप्रणाली_venकरोr;
	bool ret = true;

	subप्रणाली_venकरोr = pdev->subप्रणाली_venकरोr;

	अगर (pdev->device == PCI_DEVICE_ID_QLOGIC_QLE824X ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_QLE834X) अणु
		अगर (qlcnic_boards[index].sub_venकरोr == subप्रणाली_venकरोr &&
		    qlcnic_boards[index].sub_device == pdev->subप्रणाली_device)
			ret = true;
		अन्यथा
			ret = false;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम qlcnic_get_board_name(काष्ठा qlcnic_adapter *adapter, अक्षर *name)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक i, found = 0;

	क्रम (i = 0; i < NUM_SUPPORTED_BOARDS; ++i) अणु
		अगर (qlcnic_boards[i].venकरोr == pdev->venकरोr &&
		    qlcnic_boards[i].device == pdev->device &&
		    qlcnic_validate_subप्रणाली_id(adapter, i)) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		प्र_लिखो(name, "%pM Gigabit Ethernet", adapter->mac_addr);
	अन्यथा
		प्र_लिखो(name, "%pM: %s" , adapter->mac_addr,
			qlcnic_boards[i].लघु_name);
पूर्ण

अटल व्योम
qlcnic_check_options(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक err;
	u32 fw_major, fw_minor, fw_build, prev_fw_version;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_fw_dump *fw_dump = &ahw->fw_dump;

	prev_fw_version = adapter->fw_version;

	fw_major = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_MAJOR);
	fw_minor = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_MINOR);
	fw_build = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_SUB);

	adapter->fw_version = QLCNIC_VERSION_CODE(fw_major, fw_minor, fw_build);

	err = qlcnic_get_board_info(adapter);
	अगर (err) अणु
		dev_err(&pdev->dev, "Error getting board config info.\n");
		वापस;
	पूर्ण
	अगर (ahw->op_mode != QLCNIC_NON_PRIV_FUNC) अणु
		अगर (fw_dump->पंचांगpl_hdr == शून्य ||
				adapter->fw_version > prev_fw_version) अणु
			vमुक्त(fw_dump->पंचांगpl_hdr);
			अगर (!qlcnic_fw_cmd_get_minidump_temp(adapter))
				dev_info(&pdev->dev,
					"Supports FW dump capability\n");
		पूर्ण
	पूर्ण

	dev_info(&pdev->dev, "Driver v%s, firmware v%d.%d.%d\n",
		 QLCNIC_LINUX_VERSIONID, fw_major, fw_minor, fw_build);

	अगर (adapter->ahw->port_type == QLCNIC_XGBE) अणु
		अगर (adapter->flags & QLCNIC_ESWITCH_ENABLED) अणु
			adapter->num_rxd = DEFAULT_RCV_DESCRIPTORS_VF;
			adapter->max_rxd = MAX_RCV_DESCRIPTORS_VF;
		पूर्ण अन्यथा अणु
			adapter->num_rxd = DEFAULT_RCV_DESCRIPTORS_10G;
			adapter->max_rxd = MAX_RCV_DESCRIPTORS_10G;
		पूर्ण

		adapter->num_jumbo_rxd = MAX_JUMBO_RCV_DESCRIPTORS_10G;
		adapter->max_jumbo_rxd = MAX_JUMBO_RCV_DESCRIPTORS_10G;

	पूर्ण अन्यथा अगर (adapter->ahw->port_type == QLCNIC_GBE) अणु
		adapter->num_rxd = DEFAULT_RCV_DESCRIPTORS_1G;
		adapter->num_jumbo_rxd = MAX_JUMBO_RCV_DESCRIPTORS_1G;
		adapter->max_jumbo_rxd = MAX_JUMBO_RCV_DESCRIPTORS_1G;
		adapter->max_rxd = MAX_RCV_DESCRIPTORS_1G;
	पूर्ण

	adapter->ahw->msix_supported = !!qlcnic_use_msi_x;

	adapter->num_txd = MAX_CMD_DESCRIPTORS;

	adapter->max_rds_rings = MAX_RDS_RINGS;
पूर्ण

अटल पूर्णांक
qlcnic_initialize_nic(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_info nic_info;
	पूर्णांक err = 0;

	स_रखो(&nic_info, 0, माप(काष्ठा qlcnic_info));
	err = qlcnic_get_nic_info(adapter, &nic_info, adapter->ahw->pci_func);
	अगर (err)
		वापस err;

	adapter->ahw->physical_port = (u8)nic_info.phys_port;
	adapter->ahw->चयन_mode = nic_info.चयन_mode;
	adapter->ahw->max_tx_ques = nic_info.max_tx_ques;
	adapter->ahw->max_rx_ques = nic_info.max_rx_ques;
	adapter->ahw->capabilities = nic_info.capabilities;

	अगर (adapter->ahw->capabilities & QLCNIC_FW_CAPABILITY_MORE_CAPS) अणु
		u32 temp;
		temp = QLCRD32(adapter, CRB_FW_CAPABILITIES_2, &err);
		अगर (err == -EIO)
			वापस err;
		adapter->ahw->extra_capability[0] = temp;
	पूर्ण अन्यथा अणु
		adapter->ahw->extra_capability[0] = 0;
	पूर्ण

	adapter->ahw->max_mac_filters = nic_info.max_mac_filters;
	adapter->ahw->max_mtu = nic_info.max_mtu;

	अगर (adapter->ahw->capabilities & BIT_6) अणु
		adapter->flags |= QLCNIC_ESWITCH_ENABLED;
		adapter->ahw->nic_mode = QLCNIC_VNIC_MODE;
		adapter->max_tx_rings = QLCNIC_MAX_HW_VNIC_TX_RINGS;
		adapter->max_sds_rings = QLCNIC_MAX_VNIC_SDS_RINGS;

		dev_info(&adapter->pdev->dev, "vNIC mode enabled.\n");
	पूर्ण अन्यथा अणु
		adapter->ahw->nic_mode = QLCNIC_DEFAULT_MODE;
		adapter->max_tx_rings = QLCNIC_MAX_HW_TX_RINGS;
		adapter->max_sds_rings = QLCNIC_MAX_SDS_RINGS;
		adapter->flags &= ~QLCNIC_ESWITCH_ENABLED;
	पूर्ण

	वापस err;
पूर्ण

व्योम qlcnic_set_vlan_config(काष्ठा qlcnic_adapter *adapter,
			    काष्ठा qlcnic_esw_func_cfg *esw_cfg)
अणु
	अगर (esw_cfg->discard_tagged)
		adapter->flags &= ~QLCNIC_TAGGING_ENABLED;
	अन्यथा
		adapter->flags |= QLCNIC_TAGGING_ENABLED;

	अगर (esw_cfg->vlan_id) अणु
		adapter->rx_pvid = esw_cfg->vlan_id;
		adapter->tx_pvid = esw_cfg->vlan_id;
	पूर्ण अन्यथा अणु
		adapter->rx_pvid = 0;
		adapter->tx_pvid = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
qlcnic_vlan_rx_add(काष्ठा net_device *netdev, __be16 proto, u16 vid)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err;

	अगर (qlcnic_sriov_vf_check(adapter)) अणु
		err = qlcnic_sriov_cfg_vf_guest_vlan(adapter, vid, 1);
		अगर (err) अणु
			netdev_err(netdev,
				   "Cannot add VLAN filter for VLAN id %d, err=%d",
				   vid, err);
			वापस err;
		पूर्ण
	पूर्ण

	set_bit(vid, adapter->vlans);
	वापस 0;
पूर्ण

अटल पूर्णांक
qlcnic_vlan_rx_del(काष्ठा net_device *netdev, __be16 proto, u16 vid)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err;

	अगर (qlcnic_sriov_vf_check(adapter)) अणु
		err = qlcnic_sriov_cfg_vf_guest_vlan(adapter, vid, 0);
		अगर (err) अणु
			netdev_err(netdev,
				   "Cannot delete VLAN filter for VLAN id %d, err=%d",
				   vid, err);
			वापस err;
		पूर्ण
	पूर्ण

	qlcnic_restore_indev_addr(netdev, NETDEV_DOWN);
	clear_bit(vid, adapter->vlans);
	वापस 0;
पूर्ण

व्योम qlcnic_set_eचयन_port_features(काष्ठा qlcnic_adapter *adapter,
				      काष्ठा qlcnic_esw_func_cfg *esw_cfg)
अणु
	adapter->flags &= ~(QLCNIC_MACSPOOF | QLCNIC_MAC_OVERRIDE_DISABLED |
				QLCNIC_PROMISC_DISABLED);

	अगर (esw_cfg->mac_anti_spoof)
		adapter->flags |= QLCNIC_MACSPOOF;

	अगर (!esw_cfg->mac_override)
		adapter->flags |= QLCNIC_MAC_OVERRIDE_DISABLED;

	अगर (!esw_cfg->promisc_mode)
		adapter->flags |= QLCNIC_PROMISC_DISABLED;
पूर्ण

पूर्णांक qlcnic_set_eचयन_port_config(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_esw_func_cfg esw_cfg;

	अगर (!(adapter->flags & QLCNIC_ESWITCH_ENABLED))
		वापस 0;

	esw_cfg.pci_func = adapter->ahw->pci_func;
	अगर (qlcnic_get_eचयन_port_config(adapter, &esw_cfg))
			वापस -EIO;
	qlcnic_set_vlan_config(adapter, &esw_cfg);
	qlcnic_set_eचयन_port_features(adapter, &esw_cfg);
	qlcnic_set_netdev_features(adapter, &esw_cfg);

	वापस 0;
पूर्ण

व्योम qlcnic_set_netdev_features(काष्ठा qlcnic_adapter *adapter,
				काष्ठा qlcnic_esw_func_cfg *esw_cfg)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (qlcnic_83xx_check(adapter))
		वापस;

	adapter->offload_flags = esw_cfg->offload_flags;
	adapter->flags |= QLCNIC_APP_CHANGED_FLAGS;
	netdev_update_features(netdev);
	adapter->flags &= ~QLCNIC_APP_CHANGED_FLAGS;
पूर्ण

अटल पूर्णांक
qlcnic_check_eचयन_mode(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 op_mode, priv_level;
	पूर्णांक err = 0;

	err = qlcnic_initialize_nic(adapter);
	अगर (err)
		वापस err;

	अगर (adapter->flags & QLCNIC_ADAPTER_INITIALIZED)
		वापस 0;

	op_mode = QLC_SHARED_REG_RD32(adapter, QLCNIC_DRV_OP_MODE);
	priv_level = QLC_DEV_GET_DRV(op_mode, adapter->ahw->pci_func);

	अगर (op_mode == QLC_DEV_DRV_DEFAULT)
		priv_level = QLCNIC_MGMT_FUNC;
	अन्यथा
		priv_level = QLC_DEV_GET_DRV(op_mode, adapter->ahw->pci_func);

	अगर (adapter->flags & QLCNIC_ESWITCH_ENABLED) अणु
		अगर (priv_level == QLCNIC_MGMT_FUNC) अणु
			adapter->ahw->op_mode = QLCNIC_MGMT_FUNC;
			err = qlcnic_init_pci_info(adapter);
			अगर (err)
				वापस err;
			/* Set privilege level क्रम other functions */
			qlcnic_set_function_modes(adapter);
			dev_info(&adapter->pdev->dev,
				"HAL Version: %d, Management function\n",
				 adapter->ahw->fw_hal_version);
		पूर्ण अन्यथा अगर (priv_level == QLCNIC_PRIV_FUNC) अणु
			adapter->ahw->op_mode = QLCNIC_PRIV_FUNC;
			dev_info(&adapter->pdev->dev,
				"HAL Version: %d, Privileged function\n",
				 adapter->ahw->fw_hal_version);
		पूर्ण
	पूर्ण अन्यथा अणु
		adapter->ahw->nic_mode = QLCNIC_DEFAULT_MODE;
	पूर्ण

	adapter->flags |= QLCNIC_ADAPTER_INITIALIZED;

	वापस err;
पूर्ण

पूर्णांक qlcnic_set_शेष_offload_settings(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_esw_func_cfg esw_cfg;
	काष्ठा qlcnic_npar_info *npar;
	u8 i;

	अगर (adapter->need_fw_reset)
		वापस 0;

	क्रम (i = 0; i < adapter->ahw->total_nic_func; i++) अणु
		अगर (!adapter->npars[i].eचयन_status)
			जारी;

		स_रखो(&esw_cfg, 0, माप(काष्ठा qlcnic_esw_func_cfg));
		esw_cfg.pci_func = adapter->npars[i].pci_func;
		esw_cfg.mac_override = BIT_0;
		esw_cfg.promisc_mode = BIT_0;
		अगर (qlcnic_82xx_check(adapter)) अणु
			esw_cfg.offload_flags = BIT_0;
			अगर (QLCNIC_IS_TSO_CAPABLE(adapter))
				esw_cfg.offload_flags |= (BIT_1 | BIT_2);
		पूर्ण
		अगर (qlcnic_config_चयन_port(adapter, &esw_cfg))
			वापस -EIO;
		npar = &adapter->npars[i];
		npar->pvid = esw_cfg.vlan_id;
		npar->mac_override = esw_cfg.mac_override;
		npar->mac_anti_spoof = esw_cfg.mac_anti_spoof;
		npar->discard_tagged = esw_cfg.discard_tagged;
		npar->promisc_mode = esw_cfg.promisc_mode;
		npar->offload_flags = esw_cfg.offload_flags;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक
qlcnic_reset_eचयन_config(काष्ठा qlcnic_adapter *adapter,
			काष्ठा qlcnic_npar_info *npar, पूर्णांक pci_func)
अणु
	काष्ठा qlcnic_esw_func_cfg esw_cfg;
	esw_cfg.op_mode = QLCNIC_PORT_DEFAULTS;
	esw_cfg.pci_func = pci_func;
	esw_cfg.vlan_id = npar->pvid;
	esw_cfg.mac_override = npar->mac_override;
	esw_cfg.discard_tagged = npar->discard_tagged;
	esw_cfg.mac_anti_spoof = npar->mac_anti_spoof;
	esw_cfg.offload_flags = npar->offload_flags;
	esw_cfg.promisc_mode = npar->promisc_mode;
	अगर (qlcnic_config_चयन_port(adapter, &esw_cfg))
		वापस -EIO;

	esw_cfg.op_mode = QLCNIC_ADD_VLAN;
	अगर (qlcnic_config_चयन_port(adapter, &esw_cfg))
		वापस -EIO;

	वापस 0;
पूर्ण

पूर्णांक qlcnic_reset_npar_config(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक i, err;
	काष्ठा qlcnic_npar_info *npar;
	काष्ठा qlcnic_info nic_info;
	u8 pci_func;

	अगर (qlcnic_82xx_check(adapter))
		अगर (!adapter->need_fw_reset)
			वापस 0;

	/* Set the NPAR config data after FW reset */
	क्रम (i = 0; i < adapter->ahw->total_nic_func; i++) अणु
		npar = &adapter->npars[i];
		pci_func = npar->pci_func;
		अगर (!adapter->npars[i].eचयन_status)
			जारी;

		स_रखो(&nic_info, 0, माप(काष्ठा qlcnic_info));
		err = qlcnic_get_nic_info(adapter, &nic_info, pci_func);
		अगर (err)
			वापस err;
		nic_info.min_tx_bw = npar->min_bw;
		nic_info.max_tx_bw = npar->max_bw;
		err = qlcnic_set_nic_info(adapter, &nic_info);
		अगर (err)
			वापस err;

		अगर (npar->enable_pm) अणु
			err = qlcnic_config_port_mirroring(adapter,
							   npar->dest_npar, 1,
							   pci_func);
			अगर (err)
				वापस err;
		पूर्ण
		err = qlcnic_reset_eचयन_config(adapter, npar, pci_func);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_check_npar_opertional(काष्ठा qlcnic_adapter *adapter)
अणु
	u8 npar_opt_समयo = QLCNIC_DEV_NPAR_OPER_TIMEO;
	u32 npar_state;

	अगर (adapter->ahw->op_mode == QLCNIC_MGMT_FUNC)
		वापस 0;

	npar_state = QLC_SHARED_REG_RD32(adapter,
					 QLCNIC_CRB_DEV_NPAR_STATE);
	जबतक (npar_state != QLCNIC_DEV_NPAR_OPER && --npar_opt_समयo) अणु
		msleep(1000);
		npar_state = QLC_SHARED_REG_RD32(adapter,
						 QLCNIC_CRB_DEV_NPAR_STATE);
	पूर्ण
	अगर (!npar_opt_समयo) अणु
		dev_err(&adapter->pdev->dev,
			"Waiting for NPAR state to operational timeout\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
qlcnic_set_mgmt_operations(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक err;

	अगर (!(adapter->flags & QLCNIC_ESWITCH_ENABLED) ||
	    adapter->ahw->op_mode != QLCNIC_MGMT_FUNC)
		वापस 0;

	err = qlcnic_set_शेष_offload_settings(adapter);
	अगर (err)
		वापस err;

	err = qlcnic_reset_npar_config(adapter);
	अगर (err)
		वापस err;

	qlcnic_dev_set_npar_पढ़ोy(adapter);

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_82xx_start_firmware(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक err;

	err = qlcnic_can_start_firmware(adapter);
	अगर (err < 0)
		वापस err;
	अन्यथा अगर (!err)
		जाओ check_fw_status;

	अगर (qlcnic_load_fw_file)
		qlcnic_request_firmware(adapter);
	अन्यथा अणु
		err = qlcnic_check_flash_fw_ver(adapter);
		अगर (err)
			जाओ err_out;

		adapter->ahw->fw_type = QLCNIC_FLASH_ROMIMAGE;
	पूर्ण

	err = qlcnic_need_fw_reset(adapter);
	अगर (err == 0)
		जाओ check_fw_status;

	err = qlcnic_pinit_from_rom(adapter);
	अगर (err)
		जाओ err_out;

	err = qlcnic_load_firmware(adapter);
	अगर (err)
		जाओ err_out;

	qlcnic_release_firmware(adapter);
	QLCWR32(adapter, CRB_DRIVER_VERSION, QLCNIC_DRIVER_VERSION);

check_fw_status:
	err = qlcnic_check_fw_status(adapter);
	अगर (err)
		जाओ err_out;

	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DEV_STATE, QLCNIC_DEV_READY);
	qlcnic_idc_debug_info(adapter, 1);
	err = qlcnic_check_eचयन_mode(adapter);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"Memory allocation failed for eswitch\n");
		जाओ err_out;
	पूर्ण
	err = qlcnic_set_mgmt_operations(adapter);
	अगर (err)
		जाओ err_out;

	qlcnic_check_options(adapter);
	adapter->need_fw_reset = 0;

	qlcnic_release_firmware(adapter);
	वापस 0;

err_out:
	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DEV_STATE, QLCNIC_DEV_FAILED);
	dev_err(&adapter->pdev->dev, "Device state set to failed\n");

	qlcnic_release_firmware(adapter);
	वापस err;
पूर्ण

अटल पूर्णांक
qlcnic_request_irq(काष्ठा qlcnic_adapter *adapter)
अणु
	irq_handler_t handler;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_host_tx_ring *tx_ring;
	पूर्णांक err, ring, num_sds_rings;

	अचिन्हित दीर्घ flags = 0;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;

	अगर (adapter->ahw->diag_test == QLCNIC_INTERRUPT_TEST) अणु
		अगर (qlcnic_82xx_check(adapter))
			handler = qlcnic_पंचांगp_पूर्णांकr;
		अन्यथा
			handler = qlcnic_83xx_पंचांगp_पूर्णांकr;
		अगर (!QLCNIC_IS_MSI_FAMILY(adapter))
			flags |= IRQF_SHARED;

	पूर्ण अन्यथा अणु
		अगर (adapter->flags & QLCNIC_MSIX_ENABLED)
			handler = qlcnic_msix_पूर्णांकr;
		अन्यथा अगर (adapter->flags & QLCNIC_MSI_ENABLED)
			handler = qlcnic_msi_पूर्णांकr;
		अन्यथा अणु
			flags |= IRQF_SHARED;
			अगर (qlcnic_82xx_check(adapter))
				handler = qlcnic_पूर्णांकr;
			अन्यथा
				handler = qlcnic_83xx_पूर्णांकr;
		पूर्ण
	पूर्ण
	adapter->irq = netdev->irq;

	अगर (adapter->ahw->diag_test != QLCNIC_LOOPBACK_TEST) अणु
		अगर (qlcnic_82xx_check(adapter) ||
		    (qlcnic_83xx_check(adapter) &&
		     (adapter->flags & QLCNIC_MSIX_ENABLED))) अणु
			num_sds_rings = adapter->drv_sds_rings;
			क्रम (ring = 0; ring < num_sds_rings; ring++) अणु
				sds_ring = &recv_ctx->sds_rings[ring];
				अगर (qlcnic_82xx_check(adapter) &&
				    !qlcnic_check_multi_tx(adapter) &&
				    (ring == (num_sds_rings - 1))) अणु
					अगर (!(adapter->flags &
					      QLCNIC_MSIX_ENABLED))
						snम_लिखो(sds_ring->name,
							 माप(sds_ring->name),
							 "qlcnic");
					अन्यथा
						snम_लिखो(sds_ring->name,
							 माप(sds_ring->name),
							 "%s-tx-0-rx-%d",
							 netdev->name, ring);
				पूर्ण अन्यथा अणु
					snम_लिखो(sds_ring->name,
						 माप(sds_ring->name),
						 "%s-rx-%d",
						 netdev->name, ring);
				पूर्ण
				err = request_irq(sds_ring->irq, handler, flags,
						  sds_ring->name, sds_ring);
				अगर (err)
					वापस err;
			पूर्ण
		पूर्ण
		अगर ((qlcnic_82xx_check(adapter) &&
		     qlcnic_check_multi_tx(adapter)) ||
		    (qlcnic_83xx_check(adapter) &&
		     (adapter->flags & QLCNIC_MSIX_ENABLED) &&
		     !(adapter->flags & QLCNIC_TX_INTR_SHARED))) अणु
			handler = qlcnic_msix_tx_पूर्णांकr;
			क्रम (ring = 0; ring < adapter->drv_tx_rings;
			     ring++) अणु
				tx_ring = &adapter->tx_ring[ring];
				snम_लिखो(tx_ring->name, माप(tx_ring->name),
					 "%s-tx-%d", netdev->name, ring);
				err = request_irq(tx_ring->irq, handler, flags,
						  tx_ring->name, tx_ring);
				अगर (err)
					वापस err;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
qlcnic_मुक्त_irq(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक ring;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_host_tx_ring *tx_ring;

	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;

	अगर (adapter->ahw->diag_test != QLCNIC_LOOPBACK_TEST) अणु
		अगर (qlcnic_82xx_check(adapter) ||
		    (qlcnic_83xx_check(adapter) &&
		     (adapter->flags & QLCNIC_MSIX_ENABLED))) अणु
			क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
				sds_ring = &recv_ctx->sds_rings[ring];
				मुक्त_irq(sds_ring->irq, sds_ring);
			पूर्ण
		पूर्ण
		अगर ((qlcnic_83xx_check(adapter) &&
		     !(adapter->flags & QLCNIC_TX_INTR_SHARED)) ||
		    (qlcnic_82xx_check(adapter) &&
		     qlcnic_check_multi_tx(adapter))) अणु
			क्रम (ring = 0; ring < adapter->drv_tx_rings;
			     ring++) अणु
				tx_ring = &adapter->tx_ring[ring];
				अगर (tx_ring->irq)
					मुक्त_irq(tx_ring->irq, tx_ring);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qlcnic_get_lro_mss_capability(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 capab = 0;

	अगर (qlcnic_82xx_check(adapter)) अणु
		अगर (adapter->ahw->extra_capability[0] &
		    QLCNIC_FW_CAPABILITY_2_LRO_MAX_TCP_SEG)
			adapter->flags |= QLCNIC_FW_LRO_MSS_CAP;
	पूर्ण अन्यथा अणु
		capab = adapter->ahw->capabilities;
		अगर (QLC_83XX_GET_FW_LRO_MSS_CAPABILITY(capab))
			adapter->flags |= QLCNIC_FW_LRO_MSS_CAP;
	पूर्ण
पूर्ण

अटल पूर्णांक qlcnic_config_def_पूर्णांकr_coalesce(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक err;

	/* Initialize पूर्णांकerrupt coalesce parameters */
	ahw->coal.flag = QLCNIC_INTR_DEFAULT;

	अगर (qlcnic_83xx_check(adapter)) अणु
		ahw->coal.type = QLCNIC_INTR_COAL_TYPE_RX_TX;
		ahw->coal.tx_समय_us = QLCNIC_DEF_INTR_COALESCE_TX_TIME_US;
		ahw->coal.tx_packets = QLCNIC_DEF_INTR_COALESCE_TX_PACKETS;
		ahw->coal.rx_समय_us = QLCNIC_DEF_INTR_COALESCE_RX_TIME_US;
		ahw->coal.rx_packets = QLCNIC_DEF_INTR_COALESCE_RX_PACKETS;

		err = qlcnic_83xx_set_rx_tx_पूर्णांकr_coal(adapter);
	पूर्ण अन्यथा अणु
		ahw->coal.type = QLCNIC_INTR_COAL_TYPE_RX;
		ahw->coal.rx_समय_us = QLCNIC_DEF_INTR_COALESCE_RX_TIME_US;
		ahw->coal.rx_packets = QLCNIC_DEF_INTR_COALESCE_RX_PACKETS;

		err = qlcnic_82xx_set_rx_coalesce(adapter);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक __qlcnic_up(काष्ठा qlcnic_adapter *adapter, काष्ठा net_device *netdev)
अणु
	पूर्णांक ring;
	काष्ठा qlcnic_host_rds_ring *rds_ring;

	अगर (adapter->is_up != QLCNIC_ADAPTER_UP_MAGIC)
		वापस -EIO;

	अगर (test_bit(__QLCNIC_DEV_UP, &adapter->state))
		वापस 0;

	अगर (qlcnic_set_eचयन_port_config(adapter))
		वापस -EIO;

	qlcnic_get_lro_mss_capability(adapter);

	अगर (qlcnic_fw_create_ctx(adapter))
		वापस -EIO;

	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &adapter->recv_ctx->rds_rings[ring];
		qlcnic_post_rx_buffers(adapter, rds_ring, ring);
	पूर्ण

	qlcnic_set_multi(netdev);
	qlcnic_fw_cmd_set_mtu(adapter, netdev->mtu);

	adapter->ahw->linkup = 0;

	अगर (adapter->drv_sds_rings > 1)
		qlcnic_config_rss(adapter, 1);

	qlcnic_config_def_पूर्णांकr_coalesce(adapter);

	अगर (netdev->features & NETIF_F_LRO)
		qlcnic_config_hw_lro(adapter, QLCNIC_LRO_ENABLED);

	set_bit(__QLCNIC_DEV_UP, &adapter->state);
	qlcnic_napi_enable(adapter);

	qlcnic_linkevent_request(adapter, 1);

	adapter->ahw->reset_context = 0;
	netअगर_tx_start_all_queues(netdev);
	वापस 0;
पूर्ण

पूर्णांक qlcnic_up(काष्ठा qlcnic_adapter *adapter, काष्ठा net_device *netdev)
अणु
	पूर्णांक err = 0;

	rtnl_lock();
	अगर (netअगर_running(netdev))
		err = __qlcnic_up(adapter, netdev);
	rtnl_unlock();

	वापस err;
पूर्ण

व्योम __qlcnic_करोwn(काष्ठा qlcnic_adapter *adapter, काष्ठा net_device *netdev)
अणु
	पूर्णांक ring;

	अगर (adapter->is_up != QLCNIC_ADAPTER_UP_MAGIC)
		वापस;

	अगर (!test_and_clear_bit(__QLCNIC_DEV_UP, &adapter->state))
		वापस;

	smp_mb();
	netअगर_carrier_off(netdev);
	adapter->ahw->linkup = 0;
	netअगर_tx_disable(netdev);

	qlcnic_मुक्त_mac_list(adapter);

	अगर (adapter->fhash.fnum)
		qlcnic_delete_lb_filters(adapter);

	qlcnic_nic_set_promisc(adapter, QLCNIC_NIU_NON_PROMISC_MODE);
	अगर (qlcnic_sriov_vf_check(adapter))
		qlcnic_sriov_cleanup_async_list(&adapter->ahw->sriov->bc);

	qlcnic_napi_disable(adapter);

	qlcnic_fw_destroy_ctx(adapter);
	adapter->flags &= ~QLCNIC_FW_LRO_MSS_CAP;

	qlcnic_reset_rx_buffers_list(adapter);

	क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++)
		qlcnic_release_tx_buffers(adapter, &adapter->tx_ring[ring]);
पूर्ण

/* Usage: During suspend and firmware recovery module */

व्योम qlcnic_करोwn(काष्ठा qlcnic_adapter *adapter, काष्ठा net_device *netdev)
अणु
	rtnl_lock();
	अगर (netअगर_running(netdev))
		__qlcnic_करोwn(adapter, netdev);
	rtnl_unlock();

पूर्ण

पूर्णांक
qlcnic_attach(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक err;

	अगर (adapter->is_up == QLCNIC_ADAPTER_UP_MAGIC)
		वापस 0;

	err = qlcnic_napi_add(adapter, netdev);
	अगर (err)
		वापस err;

	err = qlcnic_alloc_sw_resources(adapter);
	अगर (err) अणु
		dev_err(&pdev->dev, "Error in setting sw resources\n");
		जाओ err_out_napi_del;
	पूर्ण

	err = qlcnic_alloc_hw_resources(adapter);
	अगर (err) अणु
		dev_err(&pdev->dev, "Error in setting hw resources\n");
		जाओ err_out_मुक्त_sw;
	पूर्ण

	err = qlcnic_request_irq(adapter);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to setup interrupt\n");
		जाओ err_out_मुक्त_hw;
	पूर्ण

	qlcnic_create_sysfs_entries(adapter);

	अगर (qlcnic_encap_rx_offload(adapter))
		udp_tunnel_nic_reset_ntf(netdev);

	adapter->is_up = QLCNIC_ADAPTER_UP_MAGIC;
	वापस 0;

err_out_मुक्त_hw:
	qlcnic_मुक्त_hw_resources(adapter);
err_out_मुक्त_sw:
	qlcnic_मुक्त_sw_resources(adapter);
err_out_napi_del:
	qlcnic_napi_del(adapter);
	वापस err;
पूर्ण

व्योम qlcnic_detach(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (adapter->is_up != QLCNIC_ADAPTER_UP_MAGIC)
		वापस;

	qlcnic_हटाओ_sysfs_entries(adapter);

	qlcnic_मुक्त_hw_resources(adapter);
	qlcnic_release_rx_buffers(adapter);
	qlcnic_मुक्त_irq(adapter);
	qlcnic_napi_del(adapter);
	qlcnic_मुक्त_sw_resources(adapter);

	adapter->is_up = 0;
पूर्ण

व्योम qlcnic_diag_मुक्त_res(काष्ठा net_device *netdev, पूर्णांक drv_sds_rings)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	पूर्णांक drv_tx_rings = adapter->drv_tx_rings;
	पूर्णांक ring;

	clear_bit(__QLCNIC_DEV_UP, &adapter->state);
	अगर (adapter->ahw->diag_test == QLCNIC_INTERRUPT_TEST) अणु
		क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
			sds_ring = &adapter->recv_ctx->sds_rings[ring];
			qlcnic_disable_sds_पूर्णांकr(adapter, sds_ring);
		पूर्ण
	पूर्ण

	qlcnic_fw_destroy_ctx(adapter);

	qlcnic_detach(adapter);

	adapter->ahw->diag_test = 0;
	adapter->drv_sds_rings = drv_sds_rings;
	adapter->drv_tx_rings = drv_tx_rings;

	अगर (qlcnic_attach(adapter))
		जाओ out;

	अगर (netअगर_running(netdev))
		__qlcnic_up(adapter, netdev);
out:
	netअगर_device_attach(netdev);
पूर्ण

अटल पूर्णांक qlcnic_alloc_adapter_resources(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक err = 0;

	adapter->recv_ctx = kzalloc(माप(काष्ठा qlcnic_recv_context),
				GFP_KERNEL);
	अगर (!adapter->recv_ctx) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	अगर (qlcnic_83xx_check(adapter)) अणु
		ahw->coal.type = QLCNIC_INTR_COAL_TYPE_RX_TX;
		ahw->coal.tx_समय_us = QLCNIC_DEF_INTR_COALESCE_TX_TIME_US;
		ahw->coal.tx_packets = QLCNIC_DEF_INTR_COALESCE_TX_PACKETS;
		ahw->coal.rx_समय_us = QLCNIC_DEF_INTR_COALESCE_RX_TIME_US;
		ahw->coal.rx_packets = QLCNIC_DEF_INTR_COALESCE_RX_PACKETS;
	पूर्ण अन्यथा अणु
		ahw->coal.type = QLCNIC_INTR_COAL_TYPE_RX;
		ahw->coal.rx_समय_us = QLCNIC_DEF_INTR_COALESCE_RX_TIME_US;
		ahw->coal.rx_packets = QLCNIC_DEF_INTR_COALESCE_RX_PACKETS;
	पूर्ण

	/* clear stats */
	स_रखो(&adapter->stats, 0, माप(adapter->stats));
err_out:
	वापस err;
पूर्ण

अटल व्योम qlcnic_मुक्त_adapter_resources(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;

	kमुक्त(adapter->recv_ctx);
	adapter->recv_ctx = शून्य;

	अगर (fw_dump->पंचांगpl_hdr) अणु
		vमुक्त(fw_dump->पंचांगpl_hdr);
		fw_dump->पंचांगpl_hdr = शून्य;
	पूर्ण

	अगर (fw_dump->dma_buffer) अणु
		dma_मुक्त_coherent(&adapter->pdev->dev, QLC_PEX_DMA_READ_SIZE,
				  fw_dump->dma_buffer, fw_dump->phys_addr);
		fw_dump->dma_buffer = शून्य;
	पूर्ण

	kमुक्त(adapter->ahw->reset.buff);
	adapter->ahw->fw_dump.पंचांगpl_hdr = शून्य;
पूर्ण

पूर्णांक qlcnic_diag_alloc_res(काष्ठा net_device *netdev, पूर्णांक test)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	पूर्णांक ring;
	पूर्णांक ret;

	netअगर_device_detach(netdev);

	अगर (netअगर_running(netdev))
		__qlcnic_करोwn(adapter, netdev);

	qlcnic_detach(adapter);

	adapter->drv_sds_rings = QLCNIC_SINGLE_RING;
	adapter->ahw->diag_test = test;
	adapter->ahw->linkup = 0;

	ret = qlcnic_attach(adapter);
	अगर (ret) अणु
		netअगर_device_attach(netdev);
		वापस ret;
	पूर्ण

	ret = qlcnic_fw_create_ctx(adapter);
	अगर (ret) अणु
		qlcnic_detach(adapter);
		netअगर_device_attach(netdev);
		वापस ret;
	पूर्ण

	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &adapter->recv_ctx->rds_rings[ring];
		qlcnic_post_rx_buffers(adapter, rds_ring, ring);
	पूर्ण

	अगर (adapter->ahw->diag_test == QLCNIC_INTERRUPT_TEST) अणु
		क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
			sds_ring = &adapter->recv_ctx->sds_rings[ring];
			qlcnic_enable_sds_पूर्णांकr(adapter, sds_ring);
		पूर्ण
	पूर्ण

	अगर (adapter->ahw->diag_test == QLCNIC_LOOPBACK_TEST) अणु
		adapter->ahw->loopback_state = 0;
		qlcnic_linkevent_request(adapter, 1);
	पूर्ण

	set_bit(__QLCNIC_DEV_UP, &adapter->state);

	वापस 0;
पूर्ण

/* Reset context in hardware only */
अटल पूर्णांक
qlcnic_reset_hw_context(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (test_and_set_bit(__QLCNIC_RESETTING, &adapter->state))
		वापस -EBUSY;

	netअगर_device_detach(netdev);

	qlcnic_करोwn(adapter, netdev);

	qlcnic_up(adapter, netdev);

	netअगर_device_attach(netdev);

	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	netdev_info(adapter->netdev, "%s: soft reset complete\n", __func__);
	वापस 0;
पूर्ण

पूर्णांक
qlcnic_reset_context(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक err = 0;
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (test_and_set_bit(__QLCNIC_RESETTING, &adapter->state))
		वापस -EBUSY;

	अगर (adapter->is_up == QLCNIC_ADAPTER_UP_MAGIC) अणु

		netअगर_device_detach(netdev);

		अगर (netअगर_running(netdev))
			__qlcnic_करोwn(adapter, netdev);

		qlcnic_detach(adapter);

		अगर (netअगर_running(netdev)) अणु
			err = qlcnic_attach(adapter);
			अगर (!err) अणु
				__qlcnic_up(adapter, netdev);
				qlcnic_restore_indev_addr(netdev, NETDEV_UP);
			पूर्ण
		पूर्ण

		netअगर_device_attach(netdev);
	पूर्ण

	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	वापस err;
पूर्ण

अटल व्योम qlcnic_82xx_set_mac_filter_count(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	u16 act_pci_fn = ahw->total_nic_func;
	u16 count;

	ahw->max_mc_count = QLCNIC_MAX_MC_COUNT;
	अगर (act_pci_fn <= 2)
		count = (QLCNIC_MAX_UC_COUNT - QLCNIC_MAX_MC_COUNT) /
			 act_pci_fn;
	अन्यथा
		count = (QLCNIC_LB_MAX_FILTERS - QLCNIC_MAX_MC_COUNT) /
			 act_pci_fn;
	ahw->max_uc_count = count;
पूर्ण

अटल पूर्णांक qlcnic_set_real_num_queues(काष्ठा qlcnic_adapter *adapter,
				      u8 tx_queues, u8 rx_queues)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err = 0;

	अगर (tx_queues) अणु
		err = netअगर_set_real_num_tx_queues(netdev, tx_queues);
		अगर (err) अणु
			netdev_err(netdev, "failed to set %d Tx queues\n",
				   tx_queues);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (rx_queues) अणु
		err = netअगर_set_real_num_rx_queues(netdev, rx_queues);
		अगर (err)
			netdev_err(netdev, "failed to set %d Rx queues\n",
				   rx_queues);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक
qlcnic_setup_netdev(काष्ठा qlcnic_adapter *adapter, काष्ठा net_device *netdev,
		    पूर्णांक pci_using_dac)
अणु
	पूर्णांक err;
	काष्ठा pci_dev *pdev = adapter->pdev;

	adapter->rx_csum = 1;
	adapter->ahw->mc_enabled = 0;
	qlcnic_set_mac_filter_count(adapter);

	netdev->netdev_ops	   = &qlcnic_netdev_ops;
	netdev->watchकरोg_समयo     = QLCNIC_WATCHDOG_TIMEOUTVALUE * HZ;

	qlcnic_change_mtu(netdev, netdev->mtu);

	netdev->ethtool_ops = (qlcnic_sriov_vf_check(adapter)) ?
		&qlcnic_sriov_vf_ethtool_ops : &qlcnic_ethtool_ops;

	netdev->features |= (NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_RXCSUM |
			     NETIF_F_IPV6_CSUM | NETIF_F_GRO |
			     NETIF_F_HW_VLAN_CTAG_RX);
	netdev->vlan_features |= (NETIF_F_SG | NETIF_F_IP_CSUM |
				  NETIF_F_IPV6_CSUM);

	अगर (QLCNIC_IS_TSO_CAPABLE(adapter)) अणु
		netdev->features |= (NETIF_F_TSO | NETIF_F_TSO6);
		netdev->vlan_features |= (NETIF_F_TSO | NETIF_F_TSO6);
	पूर्ण

	अगर (pci_using_dac) अणु
		netdev->features |= NETIF_F_HIGHDMA;
		netdev->vlan_features |= NETIF_F_HIGHDMA;
	पूर्ण

	अगर (qlcnic_vlan_tx_check(adapter))
		netdev->features |= (NETIF_F_HW_VLAN_CTAG_TX);

	अगर (qlcnic_sriov_vf_check(adapter))
		netdev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;

	अगर (adapter->ahw->capabilities & QLCNIC_FW_CAPABILITY_HW_LRO)
		netdev->features |= NETIF_F_LRO;

	अगर (qlcnic_encap_tx_offload(adapter)) अणु
		netdev->features |= NETIF_F_GSO_UDP_TUNNEL;

		/* encapsulation Tx offload supported by Adapter */
		netdev->hw_enc_features = NETIF_F_IP_CSUM        |
					  NETIF_F_GSO_UDP_TUNNEL |
					  NETIF_F_TSO            |
					  NETIF_F_TSO6;
	पूर्ण

	अगर (qlcnic_encap_rx_offload(adapter)) अणु
		netdev->hw_enc_features |= NETIF_F_RXCSUM;

		netdev->udp_tunnel_nic_info = &qlcnic_udp_tunnels;
	पूर्ण

	netdev->hw_features = netdev->features;
	netdev->priv_flags |= IFF_UNICAST_FLT;
	netdev->irq = adapter->msix_entries[0].vector;

	/* MTU range: 68 - 9600 */
	netdev->min_mtu = P3P_MIN_MTU;
	netdev->max_mtu = P3P_MAX_MTU;

	err = qlcnic_set_real_num_queues(adapter, adapter->drv_tx_rings,
					 adapter->drv_sds_rings);
	अगर (err)
		वापस err;

	qlcnic_dcb_init_dcbnl_ops(adapter->dcb);

	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register net device\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_set_dma_mask(काष्ठा pci_dev *pdev, पूर्णांक *pci_using_dac)
अणु
	अगर (!pci_set_dma_mask(pdev, DMA_BIT_MASK(64)) &&
			!pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64)))
		*pci_using_dac = 1;
	अन्यथा अगर (!pci_set_dma_mask(pdev, DMA_BIT_MASK(32)) &&
			!pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32)))
		*pci_using_dac = 0;
	अन्यथा अणु
		dev_err(&pdev->dev, "Unable to set DMA mask, aborting\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

व्योम qlcnic_मुक्त_tx_rings(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक ring;
	काष्ठा qlcnic_host_tx_ring *tx_ring;

	क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++) अणु
		tx_ring = &adapter->tx_ring[ring];
		अगर (tx_ring) अणु
			vमुक्त(tx_ring->cmd_buf_arr);
			tx_ring->cmd_buf_arr = शून्य;
		पूर्ण
	पूर्ण
	kमुक्त(adapter->tx_ring);
पूर्ण

पूर्णांक qlcnic_alloc_tx_rings(काष्ठा qlcnic_adapter *adapter,
			  काष्ठा net_device *netdev)
अणु
	पूर्णांक ring, vector, index;
	काष्ठा qlcnic_host_tx_ring *tx_ring;
	काष्ठा qlcnic_cmd_buffer *cmd_buf_arr;

	tx_ring = kसुस्मृति(adapter->drv_tx_rings,
			  माप(काष्ठा qlcnic_host_tx_ring), GFP_KERNEL);
	अगर (tx_ring == शून्य)
		वापस -ENOMEM;

	adapter->tx_ring = tx_ring;

	क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++) अणु
		tx_ring = &adapter->tx_ring[ring];
		tx_ring->num_desc = adapter->num_txd;
		tx_ring->txq = netdev_get_tx_queue(netdev, ring);
		cmd_buf_arr = vzalloc(TX_BUFF_RINGSIZE(tx_ring));
		अगर (cmd_buf_arr == शून्य) अणु
			qlcnic_मुक्त_tx_rings(adapter);
			वापस -ENOMEM;
		पूर्ण
		tx_ring->cmd_buf_arr = cmd_buf_arr;
		spin_lock_init(&tx_ring->tx_clean_lock);
	पूर्ण

	अगर (qlcnic_83xx_check(adapter) ||
	    (qlcnic_82xx_check(adapter) && qlcnic_check_multi_tx(adapter))) अणु
		क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++) अणु
			tx_ring = &adapter->tx_ring[ring];
			tx_ring->adapter = adapter;
			अगर (adapter->flags & QLCNIC_MSIX_ENABLED) अणु
				index = adapter->drv_sds_rings + ring;
				vector = adapter->msix_entries[index].vector;
				tx_ring->irq = vector;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम qlcnic_set_drv_version(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	u32 fw_cmd = 0;

	अगर (qlcnic_82xx_check(adapter))
		fw_cmd = QLCNIC_CMD_82XX_SET_DRV_VER;
	अन्यथा अगर (qlcnic_83xx_check(adapter))
		fw_cmd = QLCNIC_CMD_83XX_SET_DRV_VER;

	अगर (ahw->extra_capability[0] & QLCNIC_FW_CAPABILITY_SET_DRV_VER)
		qlcnic_fw_cmd_set_drv_version(adapter, fw_cmd);
पूर्ण

/* Reset firmware API lock */
अटल व्योम qlcnic_reset_api_lock(काष्ठा qlcnic_adapter *adapter)
अणु
	qlcnic_api_lock(adapter);
	qlcnic_api_unlock(adapter);
पूर्ण


अटल पूर्णांक
qlcnic_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev = शून्य;
	काष्ठा qlcnic_adapter *adapter = शून्य;
	काष्ठा qlcnic_hardware_context *ahw;
	पूर्णांक err, pci_using_dac = -1;
	अक्षर board_name[QLCNIC_MAX_BOARD_NAME_LEN + 19]; /* MAC + ": " + name */

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		err = -ENODEV;
		जाओ err_out_disable_pdev;
	पूर्ण

	err = qlcnic_set_dma_mask(pdev, &pci_using_dac);
	अगर (err)
		जाओ err_out_disable_pdev;

	err = pci_request_regions(pdev, qlcnic_driver_name);
	अगर (err)
		जाओ err_out_disable_pdev;

	pci_set_master(pdev);
	pci_enable_pcie_error_reporting(pdev);

	ahw = kzalloc(माप(काष्ठा qlcnic_hardware_context), GFP_KERNEL);
	अगर (!ahw) अणु
		err = -ENOMEM;
		जाओ err_out_मुक्त_res;
	पूर्ण

	चयन (ent->device) अणु
	हाल PCI_DEVICE_ID_QLOGIC_QLE824X:
		ahw->hw_ops = &qlcnic_hw_ops;
		ahw->reg_tbl = (u32 *) qlcnic_reg_tbl;
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_QLE834X:
	हाल PCI_DEVICE_ID_QLOGIC_QLE8830:
	हाल PCI_DEVICE_ID_QLOGIC_QLE844X:
		qlcnic_83xx_रेजिस्टर_map(ahw);
		अवरोध;
	हाल PCI_DEVICE_ID_QLOGIC_VF_QLE834X:
	हाल PCI_DEVICE_ID_QLOGIC_VF_QLE8C30:
	हाल PCI_DEVICE_ID_QLOGIC_VF_QLE844X:
		qlcnic_sriov_vf_रेजिस्टर_map(ahw);
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ err_out_मुक्त_hw_res;
	पूर्ण

	err = qlcnic_setup_pci_map(pdev, ahw);
	अगर (err)
		जाओ err_out_मुक्त_hw_res;

	netdev = alloc_etherdev_mq(माप(काष्ठा qlcnic_adapter),
				   QLCNIC_MAX_TX_RINGS);
	अगर (!netdev) अणु
		err = -ENOMEM;
		जाओ err_out_iounmap;
	पूर्ण

	SET_NETDEV_DEV(netdev, &pdev->dev);

	adapter = netdev_priv(netdev);
	adapter->netdev  = netdev;
	adapter->pdev    = pdev;
	adapter->ahw = ahw;

	adapter->qlcnic_wq = create_singlethपढ़ो_workqueue("qlcnic");
	अगर (adapter->qlcnic_wq == शून्य) अणु
		err = -ENOMEM;
		dev_err(&pdev->dev, "Failed to create workqueue\n");
		जाओ err_out_मुक्त_netdev;
	पूर्ण

	err = qlcnic_alloc_adapter_resources(adapter);
	अगर (err)
		जाओ err_out_मुक्त_wq;

	adapter->dev_rst_समय = jअगरfies;
	ahw->revision_id = pdev->revision;
	ahw->max_vnic_func = qlcnic_get_vnic_func_count(adapter);
	अगर (qlcnic_mac_learn == FDB_MAC_LEARN)
		adapter->fdb_mac_learn = true;
	अन्यथा अगर (qlcnic_mac_learn == DRV_MAC_LEARN)
		adapter->drv_mac_learn = true;

	rwlock_init(&adapter->ahw->crb_lock);
	mutex_init(&adapter->ahw->mem_lock);

	INIT_LIST_HEAD(&adapter->mac_list);

	qlcnic_रेजिस्टर_dcb(adapter);

	अगर (qlcnic_82xx_check(adapter)) अणु
		qlcnic_check_vf(adapter, ent);
		adapter->portnum = adapter->ahw->pci_func;
		qlcnic_reset_api_lock(adapter);
		err = qlcnic_start_firmware(adapter);
		अगर (err) अणु
			dev_err(&pdev->dev, "Loading fw failed.Please Reboot\n"
				"\t\tIf reboot doesn't help, try flashing the card\n");
			जाओ err_out_मुख्यtenance_mode;
		पूर्ण

		/* compute and set शेष and max tx/sds rings */
		अगर (adapter->ahw->msix_supported) अणु
			अगर (qlcnic_check_multi_tx_capability(adapter) == 1)
				qlcnic_set_tx_ring_count(adapter,
							 QLCNIC_SINGLE_RING);
			अन्यथा
				qlcnic_set_tx_ring_count(adapter,
							 QLCNIC_DEF_TX_RINGS);
			qlcnic_set_sds_ring_count(adapter,
						  QLCNIC_DEF_SDS_RINGS);
		पूर्ण अन्यथा अणु
			qlcnic_set_tx_ring_count(adapter, QLCNIC_SINGLE_RING);
			qlcnic_set_sds_ring_count(adapter, QLCNIC_SINGLE_RING);
		पूर्ण

		err = qlcnic_setup_idc_param(adapter);
		अगर (err)
			जाओ err_out_मुक्त_hw;

		adapter->flags |= QLCNIC_NEED_FLR;

	पूर्ण अन्यथा अगर (qlcnic_83xx_check(adapter)) अणु
		qlcnic_83xx_check_vf(adapter, ent);
		adapter->portnum = adapter->ahw->pci_func;
		err = qlcnic_83xx_init(adapter, pci_using_dac);
		अगर (err) अणु
			चयन (err) अणु
			हाल -ENOTRECOVERABLE:
				dev_err(&pdev->dev, "Adapter initialization failed due to a faulty hardware\n");
				dev_err(&pdev->dev, "Please replace the adapter with new one and return the faulty adapter for repair\n");
				जाओ err_out_मुक्त_hw;
			हाल -ENOMEM:
				dev_err(&pdev->dev, "Adapter initialization failed. Please reboot\n");
				जाओ err_out_मुक्त_hw;
			हाल -EOPNOTSUPP:
				dev_err(&pdev->dev, "Adapter initialization failed\n");
				जाओ err_out_मुक्त_hw;
			शेष:
				dev_err(&pdev->dev, "Adapter initialization failed. Driver will load in maintenance mode to recover the adapter using the application\n");
				जाओ err_out_मुख्यtenance_mode;
			पूर्ण
		पूर्ण

		अगर (qlcnic_sriov_vf_check(adapter))
			वापस 0;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev,
			"%s: failed. Please Reboot\n", __func__);
		err = -ENODEV;
		जाओ err_out_मुक्त_hw;
	पूर्ण

	अगर (qlcnic_पढ़ो_mac_addr(adapter))
		dev_warn(&pdev->dev, "failed to read mac addr\n");

	qlcnic_पढ़ो_phys_port_id(adapter);

	अगर (adapter->portnum == 0) अणु
		qlcnic_get_board_name(adapter, board_name);

		pr_info("%s: %s Board Chip rev 0x%x\n",
			module_name(THIS_MODULE),
			board_name, adapter->ahw->revision_id);
	पूर्ण

	अगर (qlcnic_83xx_check(adapter) && !qlcnic_use_msi_x &&
	    !!qlcnic_use_msi)
		dev_warn(&pdev->dev,
			 "Device does not support MSI interrupts\n");

	अगर (qlcnic_82xx_check(adapter)) अणु
		qlcnic_dcb_enable(adapter->dcb);
		qlcnic_dcb_get_info(adapter->dcb);
		err = qlcnic_setup_पूर्णांकr(adapter);

		अगर (err) अणु
			dev_err(&pdev->dev, "Failed to setup interrupt\n");
			जाओ err_out_disable_msi;
		पूर्ण
	पूर्ण

	err = qlcnic_get_act_pci_func(adapter);
	अगर (err)
		जाओ err_out_disable_mbx_पूर्णांकr;

	अगर (adapter->portnum == 0)
		qlcnic_set_drv_version(adapter);

	err = qlcnic_setup_netdev(adapter, netdev, pci_using_dac);
	अगर (err)
		जाओ err_out_disable_mbx_पूर्णांकr;

	pci_set_drvdata(pdev, adapter);

	अगर (qlcnic_82xx_check(adapter))
		qlcnic_schedule_work(adapter, qlcnic_fw_poll_work,
				     FW_POLL_DELAY);

	चयन (adapter->ahw->port_type) अणु
	हाल QLCNIC_GBE:
		dev_info(&adapter->pdev->dev, "%s: GbE port initialized\n",
				adapter->netdev->name);
		अवरोध;
	हाल QLCNIC_XGBE:
		dev_info(&adapter->pdev->dev, "%s: XGbE port initialized\n",
				adapter->netdev->name);
		अवरोध;
	पूर्ण

	अगर (adapter->drv_mac_learn)
		qlcnic_alloc_lb_filters_mem(adapter);

	qlcnic_add_sysfs(adapter);
	qlcnic_रेजिस्टर_hwmon_dev(adapter);
	वापस 0;

err_out_disable_mbx_पूर्णांकr:
	अगर (qlcnic_83xx_check(adapter))
		qlcnic_83xx_मुक्त_mbx_पूर्णांकr(adapter);

err_out_disable_msi:
	qlcnic_tearकरोwn_पूर्णांकr(adapter);
	qlcnic_cancel_idc_work(adapter);
	qlcnic_clr_all_drv_state(adapter, 0);

err_out_मुक्त_hw:
	qlcnic_मुक्त_adapter_resources(adapter);

err_out_मुक्त_wq:
	destroy_workqueue(adapter->qlcnic_wq);

err_out_मुक्त_netdev:
	मुक्त_netdev(netdev);

err_out_iounmap:
	qlcnic_cleanup_pci_map(ahw);

err_out_मुक्त_hw_res:
	kमुक्त(ahw);

err_out_मुक्त_res:
	pci_disable_pcie_error_reporting(pdev);
	pci_release_regions(pdev);

err_out_disable_pdev:
	pci_disable_device(pdev);
	वापस err;

err_out_मुख्यtenance_mode:
	set_bit(__QLCNIC_MAINTEन_अंकCE_MODE, &adapter->state);
	netdev->netdev_ops = &qlcnic_netdev_failed_ops;
	netdev->ethtool_ops = &qlcnic_ethtool_failed_ops;
	ahw->port_type = QLCNIC_XGBE;

	अगर (qlcnic_83xx_check(adapter))
		adapter->tgt_status_reg = शून्य;
	अन्यथा
		ahw->board_type = QLCNIC_BRDTYPE_P3P_10G_SFP_PLUS;

	err = रेजिस्टर_netdev(netdev);

	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to register net device\n");
		qlcnic_clr_all_drv_state(adapter, 0);
		जाओ err_out_मुक्त_hw;
	पूर्ण

	pci_set_drvdata(pdev, adapter);
	qlcnic_add_sysfs(adapter);

	वापस 0;
पूर्ण

अटल व्योम qlcnic_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qlcnic_adapter *adapter;
	काष्ठा net_device *netdev;
	काष्ठा qlcnic_hardware_context *ahw;

	adapter = pci_get_drvdata(pdev);
	अगर (adapter == शून्य)
		वापस;

	netdev = adapter->netdev;

	qlcnic_cancel_idc_work(adapter);
	qlcnic_sriov_pf_disable(adapter);
	ahw = adapter->ahw;

	unरेजिस्टर_netdev(netdev);
	qlcnic_sriov_cleanup(adapter);

	अगर (qlcnic_83xx_check(adapter)) अणु
		qlcnic_83xx_initialize_nic(adapter, 0);
		cancel_delayed_work_sync(&adapter->idc_aen_work);
		qlcnic_83xx_मुक्त_mbx_पूर्णांकr(adapter);
		qlcnic_83xx_detach_mailbox_work(adapter);
		qlcnic_83xx_मुक्त_mailbox(ahw->mailbox);
		kमुक्त(ahw->fw_info);
	पूर्ण

	qlcnic_dcb_मुक्त(adapter->dcb);
	qlcnic_detach(adapter);
	kमुक्त(adapter->npars);
	kमुक्त(adapter->eचयन);

	अगर (qlcnic_82xx_check(adapter))
		qlcnic_clr_all_drv_state(adapter, 0);

	clear_bit(__QLCNIC_RESETTING, &adapter->state);

	qlcnic_मुक्त_lb_filters_mem(adapter);

	qlcnic_tearकरोwn_पूर्णांकr(adapter);

	qlcnic_हटाओ_sysfs(adapter);

	qlcnic_unरेजिस्टर_hwmon_dev(adapter);

	qlcnic_cleanup_pci_map(adapter->ahw);

	qlcnic_release_firmware(adapter);

	pci_disable_pcie_error_reporting(pdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);

	अगर (adapter->qlcnic_wq) अणु
		destroy_workqueue(adapter->qlcnic_wq);
		adapter->qlcnic_wq = शून्य;
	पूर्ण

	qlcnic_मुक्त_adapter_resources(adapter);
	kमुक्त(ahw);
	मुक्त_netdev(netdev);
पूर्ण

अटल व्योम qlcnic_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	अगर (__qlcnic_shutकरोwn(pdev))
		वापस;

	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक __maybe_unused qlcnic_suspend(काष्ठा device *dev_d)
अणु
	वापस __qlcnic_shutकरोwn(to_pci_dev(dev_d));
पूर्ण

अटल पूर्णांक __maybe_unused qlcnic_resume(काष्ठा device *dev_d)
अणु
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev_d);

	वापस  __qlcnic_resume(adapter);
पूर्ण

अटल पूर्णांक qlcnic_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err;

	अगर (test_bit(__QLCNIC_MAINTEन_अंकCE_MODE, &adapter->state)) अणु
		netdev_err(netdev, "%s: Device is in non-operational state\n",
			   __func__);

		वापस -EIO;
	पूर्ण

	netअगर_carrier_off(netdev);

	err = qlcnic_attach(adapter);
	अगर (err)
		वापस err;

	err = __qlcnic_up(adapter, netdev);
	अगर (err)
		qlcnic_detach(adapter);

	वापस err;
पूर्ण

/*
 * qlcnic_बंद - Disables a network पूर्णांकerface entry poपूर्णांक
 */
अटल पूर्णांक qlcnic_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);

	__qlcnic_करोwn(adapter, netdev);

	वापस 0;
पूर्ण

#घोषणा QLCNIC_VF_LB_BUCKET_SIZE 1

व्योम qlcnic_alloc_lb_filters_mem(काष्ठा qlcnic_adapter *adapter)
अणु
	व्योम *head;
	पूर्णांक i;
	काष्ठा net_device *netdev = adapter->netdev;
	u32 filter_size = 0;
	u16 act_pci_func = 0;

	अगर (adapter->fhash.fmax && adapter->fhash.fhead)
		वापस;

	act_pci_func = adapter->ahw->total_nic_func;
	spin_lock_init(&adapter->mac_learn_lock);
	spin_lock_init(&adapter->rx_mac_learn_lock);

	अगर (qlcnic_sriov_vf_check(adapter)) अणु
		filter_size = QLCNIC_83XX_SRIOV_VF_MAX_MAC - 1;
		adapter->fhash.fbucket_size = QLCNIC_VF_LB_BUCKET_SIZE;
	पूर्ण अन्यथा अगर (qlcnic_82xx_check(adapter)) अणु
		filter_size = QLCNIC_LB_MAX_FILTERS;
		adapter->fhash.fbucket_size = QLCNIC_LB_BUCKET_SIZE;
	पूर्ण अन्यथा अणु
		filter_size = QLC_83XX_LB_MAX_FILTERS;
		adapter->fhash.fbucket_size = QLC_83XX_LB_BUCKET_SIZE;
	पूर्ण

	head = kसुस्मृति(adapter->fhash.fbucket_size,
		       माप(काष्ठा hlist_head), GFP_ATOMIC);

	अगर (!head)
		वापस;

	adapter->fhash.fmax = (filter_size / act_pci_func);
	adapter->fhash.fhead = head;

	netdev_info(netdev, "active nic func = %d, mac filter size=%d\n",
		    act_pci_func, adapter->fhash.fmax);

	क्रम (i = 0; i < adapter->fhash.fbucket_size; i++)
		INIT_HLIST_HEAD(&adapter->fhash.fhead[i]);

	adapter->rx_fhash.fbucket_size = adapter->fhash.fbucket_size;

	head = kसुस्मृति(adapter->rx_fhash.fbucket_size,
		       माप(काष्ठा hlist_head), GFP_ATOMIC);

	अगर (!head)
		वापस;

	adapter->rx_fhash.fmax = (filter_size / act_pci_func);
	adapter->rx_fhash.fhead = head;

	क्रम (i = 0; i < adapter->rx_fhash.fbucket_size; i++)
		INIT_HLIST_HEAD(&adapter->rx_fhash.fhead[i]);
पूर्ण

अटल व्योम qlcnic_मुक्त_lb_filters_mem(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (adapter->fhash.fmax)
		kमुक्त(adapter->fhash.fhead);

	adapter->fhash.fhead = शून्य;
	adapter->fhash.fmax = 0;

	अगर (adapter->rx_fhash.fmax)
		kमुक्त(adapter->rx_fhash.fhead);

	adapter->rx_fhash.fmax = 0;
	adapter->rx_fhash.fhead = शून्य;
पूर्ण

पूर्णांक qlcnic_check_temp(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	u32 temp_state, temp_val, temp = 0;
	पूर्णांक rv = 0;

	अगर (qlcnic_83xx_check(adapter))
		temp = QLCRDX(adapter->ahw, QLC_83XX_ASIC_TEMP);

	अगर (qlcnic_82xx_check(adapter))
		temp = QLC_SHARED_REG_RD32(adapter, QLCNIC_ASIC_TEMP);

	temp_state = qlcnic_get_temp_state(temp);
	temp_val = qlcnic_get_temp_val(temp);

	अगर (temp_state == QLCNIC_TEMP_PANIC) अणु
		dev_err(&netdev->dev,
		       "Device temperature %d degrees C exceeds"
		       " maximum allowed. Hardware has been shut down.\n",
		       temp_val);
		rv = 1;
	पूर्ण अन्यथा अगर (temp_state == QLCNIC_TEMP_WARN) अणु
		अगर (adapter->ahw->temp == QLCNIC_TEMP_NORMAL) अणु
			dev_err(&netdev->dev,
			       "Device temperature %d degrees C "
			       "exceeds operating range."
			       " Immediate action needed.\n",
			       temp_val);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (adapter->ahw->temp == QLCNIC_TEMP_WARN) अणु
			dev_info(&netdev->dev,
			       "Device temperature is now %d degrees C"
			       " in normal range.\n", temp_val);
		पूर्ण
	पूर्ण
	adapter->ahw->temp = temp_state;
	वापस rv;
पूर्ण

अटल अंतरभूत व्योम dump_tx_ring_desc(काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tx_ring->num_desc; i++) अणु
		pr_info("TX Desc: %d\n", i);
		prपूर्णांक_hex_dump(KERN_INFO, "TX: ", DUMP_PREFIX_OFFSET, 16, 1,
			       &tx_ring->desc_head[i],
			       माप(काष्ठा cmd_desc_type0), true);
	पूर्ण
पूर्ण

अटल व्योम qlcnic_dump_rings(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_host_tx_ring *tx_ring;
	पूर्णांक ring;

	अगर (!netdev || !netअगर_running(netdev))
		वापस;

	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &recv_ctx->rds_rings[ring];
		अगर (!rds_ring)
			जारी;
		netdev_info(netdev,
			    "rds_ring=%d crb_rcv_producer=%d producer=%u num_desc=%u\n",
			     ring, पढ़ोl(rds_ring->crb_rcv_producer),
			     rds_ring->producer, rds_ring->num_desc);
	पूर्ण

	क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
		sds_ring = &(recv_ctx->sds_rings[ring]);
		अगर (!sds_ring)
			जारी;
		netdev_info(netdev,
			    "sds_ring=%d crb_sts_consumer=%d consumer=%u crb_intr_mask=%d num_desc=%u\n",
			    ring, पढ़ोl(sds_ring->crb_sts_consumer),
			    sds_ring->consumer, पढ़ोl(sds_ring->crb_पूर्णांकr_mask),
			    sds_ring->num_desc);
	पूर्ण

	क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++) अणु
		tx_ring = &adapter->tx_ring[ring];
		अगर (!tx_ring)
			जारी;
		netdev_info(netdev, "Tx ring=%d Context Id=0x%x\n",
			    ring, tx_ring->ctx_id);
		netdev_info(netdev,
			    "xmit_finished=%llu, xmit_called=%llu, xmit_on=%llu, xmit_off=%llu\n",
			    tx_ring->tx_stats.xmit_finished,
			    tx_ring->tx_stats.xmit_called,
			    tx_ring->tx_stats.xmit_on,
			    tx_ring->tx_stats.xmit_off);

		अगर (tx_ring->crb_पूर्णांकr_mask)
			netdev_info(netdev, "crb_intr_mask=%d\n",
				    पढ़ोl(tx_ring->crb_पूर्णांकr_mask));

		netdev_info(netdev,
			    "hw_producer=%d, sw_producer=%d sw_consumer=%d, hw_consumer=%d\n",
			    पढ़ोl(tx_ring->crb_cmd_producer),
			    tx_ring->producer, tx_ring->sw_consumer,
			    le32_to_cpu(*(tx_ring->hw_consumer)));

		netdev_info(netdev, "Total desc=%d, Available desc=%d\n",
			    tx_ring->num_desc, qlcnic_tx_avail(tx_ring));

		अगर (netअगर_msg_tx_err(adapter->ahw))
			dump_tx_ring_desc(tx_ring);
	पूर्ण

पूर्ण

अटल व्योम qlcnic_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);

	अगर (test_bit(__QLCNIC_RESETTING, &adapter->state))
		वापस;

	qlcnic_dump_rings(adapter);

	अगर (++adapter->tx_समयo_cnt >= QLCNIC_MAX_TX_TIMEOUTS ||
	    netअगर_msg_tx_err(adapter->ahw)) अणु
		netdev_err(netdev, "Tx timeout, reset the adapter.\n");
		अगर (qlcnic_82xx_check(adapter))
			adapter->need_fw_reset = 1;
		अन्यथा अगर (qlcnic_83xx_check(adapter))
			qlcnic_83xx_idc_request_reset(adapter,
						      QLCNIC_FORCE_FW_DUMP_KEY);
	पूर्ण अन्यथा अणु
		netdev_err(netdev, "Tx timeout, reset adapter context.\n");
		adapter->ahw->reset_context = 1;
	पूर्ण
पूर्ण

अटल काष्ठा net_device_stats *qlcnic_get_stats(काष्ठा net_device *netdev)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा net_device_stats *stats = &netdev->stats;

	अगर (test_bit(__QLCNIC_DEV_UP, &adapter->state))
		qlcnic_update_stats(adapter);

	stats->rx_packets = adapter->stats.rx_pkts + adapter->stats.lro_pkts;
	stats->tx_packets = adapter->stats.xmitfinished;
	stats->rx_bytes = adapter->stats.rxbytes + adapter->stats.lrobytes;
	stats->tx_bytes = adapter->stats.txbytes;
	stats->rx_dropped = adapter->stats.rxdropped;
	stats->tx_dropped = adapter->stats.txdropped;

	वापस stats;
पूर्ण

अटल irqवापस_t qlcnic_82xx_clear_legacy_पूर्णांकr(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 status;

	status = पढ़ोl(adapter->isr_पूर्णांक_vec);

	अगर (!(status & adapter->ahw->पूर्णांक_vec_bit))
		वापस IRQ_NONE;

	/* check पूर्णांकerrupt state machine, to be sure */
	status = पढ़ोl(adapter->crb_पूर्णांक_state_reg);
	अगर (!ISR_LEGACY_INT_TRIGGERED(status))
		वापस IRQ_NONE;

	ग_लिखोl(0xffffffff, adapter->tgt_status_reg);
	/* पढ़ो twice to ensure ग_लिखो is flushed */
	पढ़ोl(adapter->isr_पूर्णांक_vec);
	पढ़ोl(adapter->isr_पूर्णांक_vec);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t qlcnic_पंचांगp_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qlcnic_host_sds_ring *sds_ring = data;
	काष्ठा qlcnic_adapter *adapter = sds_ring->adapter;

	अगर (adapter->flags & QLCNIC_MSIX_ENABLED)
		जाओ करोne;
	अन्यथा अगर (adapter->flags & QLCNIC_MSI_ENABLED) अणु
		ग_लिखोl(0xffffffff, adapter->tgt_status_reg);
		जाओ करोne;
	पूर्ण

	अगर (qlcnic_clear_legacy_पूर्णांकr(adapter) == IRQ_NONE)
		वापस IRQ_NONE;

करोne:
	adapter->ahw->diag_cnt++;
	qlcnic_enable_sds_पूर्णांकr(adapter, sds_ring);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t qlcnic_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qlcnic_host_sds_ring *sds_ring = data;
	काष्ठा qlcnic_adapter *adapter = sds_ring->adapter;

	अगर (qlcnic_clear_legacy_पूर्णांकr(adapter) == IRQ_NONE)
		वापस IRQ_NONE;

	napi_schedule(&sds_ring->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t qlcnic_msi_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qlcnic_host_sds_ring *sds_ring = data;
	काष्ठा qlcnic_adapter *adapter = sds_ring->adapter;

	/* clear पूर्णांकerrupt */
	ग_लिखोl(0xffffffff, adapter->tgt_status_reg);

	napi_schedule(&sds_ring->napi);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t qlcnic_msix_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qlcnic_host_sds_ring *sds_ring = data;

	napi_schedule(&sds_ring->napi);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t qlcnic_msix_tx_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qlcnic_host_tx_ring *tx_ring = data;

	napi_schedule(&tx_ring->napi);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम
qlcnic_idc_debug_info(काष्ठा qlcnic_adapter *adapter, u8 encoding)
अणु
	u32 val;

	val = adapter->portnum & 0xf;
	val |= encoding << 7;
	val |= (jअगरfies - adapter->dev_rst_समय) << 8;

	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_SCRATCH, val);
	adapter->dev_rst_समय = jअगरfies;
पूर्ण

अटल पूर्णांक
qlcnic_set_drv_state(काष्ठा qlcnic_adapter *adapter, u8 state)
अणु
	u32  val;

	WARN_ON(state != QLCNIC_DEV_NEED_RESET &&
			state != QLCNIC_DEV_NEED_QUISCENT);

	अगर (qlcnic_api_lock(adapter))
		वापस -EIO;

	val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_STATE);

	अगर (state == QLCNIC_DEV_NEED_RESET)
		QLC_DEV_SET_RST_RDY(val, adapter->portnum);
	अन्यथा अगर (state == QLCNIC_DEV_NEED_QUISCENT)
		QLC_DEV_SET_QSCNT_RDY(val, adapter->portnum);

	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_STATE, val);

	qlcnic_api_unlock(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक
qlcnic_clr_drv_state(काष्ठा qlcnic_adapter *adapter)
अणु
	u32  val;

	अगर (qlcnic_api_lock(adapter))
		वापस -EBUSY;

	val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_STATE);
	QLC_DEV_CLR_RST_QSCNT(val, adapter->portnum);
	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_STATE, val);

	qlcnic_api_unlock(adapter);

	वापस 0;
पूर्ण

व्योम qlcnic_clr_all_drv_state(काष्ठा qlcnic_adapter *adapter, u8 failed)
अणु
	u32  val;

	अगर (qlcnic_api_lock(adapter))
		जाओ err;

	val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_ACTIVE);
	QLC_DEV_CLR_REF_CNT(val, adapter->portnum);
	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_ACTIVE, val);

	अगर (failed) अणु
		QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DEV_STATE,
				    QLCNIC_DEV_FAILED);
		dev_info(&adapter->pdev->dev,
				"Device state set to Failed. Please Reboot\n");
	पूर्ण अन्यथा अगर (!(val & 0x11111111))
		QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DEV_STATE,
				    QLCNIC_DEV_COLD);

	val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_STATE);
	QLC_DEV_CLR_RST_QSCNT(val, adapter->portnum);
	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_STATE, val);

	qlcnic_api_unlock(adapter);
err:
	adapter->fw_fail_cnt = 0;
	adapter->flags &= ~QLCNIC_FW_HANG;
	clear_bit(__QLCNIC_START_FW, &adapter->state);
	clear_bit(__QLCNIC_RESETTING, &adapter->state);
पूर्ण

/* Grab api lock, beक्रमe checking state */
अटल पूर्णांक
qlcnic_check_drv_state(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक act, state, active_mask;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	state = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_STATE);
	act = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_ACTIVE);

	अगर (adapter->flags & QLCNIC_FW_RESET_OWNER) अणु
		active_mask = (~(1 << (ahw->pci_func * 4)));
		act = act & active_mask;
	पूर्ण

	अगर (((state & 0x11111111) == (act & 0x11111111)) ||
			((act & 0x11111111) == ((state >> 1) & 0x11111111)))
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक qlcnic_check_idc_ver(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_IDC_VER);

	अगर (val != QLCNIC_DRV_IDC_VER) अणु
		dev_warn(&adapter->pdev->dev, "IDC Version mismatch, driver's"
			" idc ver = %x; reqd = %x\n", QLCNIC_DRV_IDC_VER, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qlcnic_can_start_firmware(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 val, prev_state;
	u8 dev_init_समयo = adapter->dev_init_समयo;
	u8 portnum = adapter->portnum;
	u8 ret;

	अगर (test_and_clear_bit(__QLCNIC_START_FW, &adapter->state))
		वापस 1;

	अगर (qlcnic_api_lock(adapter))
		वापस -1;

	val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_ACTIVE);
	अगर (!(val & (1 << (portnum * 4)))) अणु
		QLC_DEV_SET_REF_CNT(val, portnum);
		QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_ACTIVE, val);
	पूर्ण

	prev_state = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DEV_STATE);
	QLCDB(adapter, HW, "Device state = %u\n", prev_state);

	चयन (prev_state) अणु
	हाल QLCNIC_DEV_COLD:
		QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DEV_STATE,
				    QLCNIC_DEV_INITIALIZING);
		QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_IDC_VER,
				    QLCNIC_DRV_IDC_VER);
		qlcnic_idc_debug_info(adapter, 0);
		qlcnic_api_unlock(adapter);
		वापस 1;

	हाल QLCNIC_DEV_READY:
		ret = qlcnic_check_idc_ver(adapter);
		qlcnic_api_unlock(adapter);
		वापस ret;

	हाल QLCNIC_DEV_NEED_RESET:
		val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_STATE);
		QLC_DEV_SET_RST_RDY(val, portnum);
		QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_STATE, val);
		अवरोध;

	हाल QLCNIC_DEV_NEED_QUISCENT:
		val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_STATE);
		QLC_DEV_SET_QSCNT_RDY(val, portnum);
		QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_STATE, val);
		अवरोध;

	हाल QLCNIC_DEV_FAILED:
		dev_err(&adapter->pdev->dev, "Device in failed state.\n");
		qlcnic_api_unlock(adapter);
		वापस -1;

	हाल QLCNIC_DEV_INITIALIZING:
	हाल QLCNIC_DEV_QUISCENT:
		अवरोध;
	पूर्ण

	qlcnic_api_unlock(adapter);

	करो अणु
		msleep(1000);
		prev_state = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DEV_STATE);

		अगर (prev_state == QLCNIC_DEV_QUISCENT)
			जारी;
	पूर्ण जबतक ((prev_state != QLCNIC_DEV_READY) && --dev_init_समयo);

	अगर (!dev_init_समयo) अणु
		dev_err(&adapter->pdev->dev,
			"Waiting for device to initialize timeout\n");
		वापस -1;
	पूर्ण

	अगर (qlcnic_api_lock(adapter))
		वापस -1;

	val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DRV_STATE);
	QLC_DEV_CLR_RST_QSCNT(val, portnum);
	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DRV_STATE, val);

	ret = qlcnic_check_idc_ver(adapter);
	qlcnic_api_unlock(adapter);

	वापस ret;
पूर्ण

अटल व्योम
qlcnic_fwinit_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlcnic_adapter *adapter = container_of(work,
			काष्ठा qlcnic_adapter, fw_work.work);
	u32 dev_state = 0xf;
	u32 val;

	अगर (qlcnic_api_lock(adapter))
		जाओ err_ret;

	dev_state = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DEV_STATE);
	अगर (dev_state == QLCNIC_DEV_QUISCENT ||
	    dev_state == QLCNIC_DEV_NEED_QUISCENT) अणु
		qlcnic_api_unlock(adapter);
		qlcnic_schedule_work(adapter, qlcnic_fwinit_work,
						FW_POLL_DELAY * 2);
		वापस;
	पूर्ण

	अगर (adapter->ahw->op_mode == QLCNIC_NON_PRIV_FUNC) अणु
		qlcnic_api_unlock(adapter);
		जाओ रुको_npar;
	पूर्ण

	अगर (dev_state == QLCNIC_DEV_INITIALIZING ||
	    dev_state == QLCNIC_DEV_READY) अणु
		dev_info(&adapter->pdev->dev, "Detected state change from "
				"DEV_NEED_RESET, skipping ack check\n");
		जाओ skip_ack_check;
	पूर्ण

	अगर (adapter->fw_रुको_cnt++ > adapter->reset_ack_समयo) अणु
		dev_info(&adapter->pdev->dev, "Reset:Failed to get ack %d sec\n",
					adapter->reset_ack_समयo);
		जाओ skip_ack_check;
	पूर्ण

	अगर (!qlcnic_check_drv_state(adapter)) अणु
skip_ack_check:
		dev_state = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DEV_STATE);

		अगर (dev_state == QLCNIC_DEV_NEED_RESET) अणु
			QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DEV_STATE,
					    QLCNIC_DEV_INITIALIZING);
			set_bit(__QLCNIC_START_FW, &adapter->state);
			QLCDB(adapter, DRV, "Restarting fw\n");
			qlcnic_idc_debug_info(adapter, 0);
			val = QLC_SHARED_REG_RD32(adapter,
						  QLCNIC_CRB_DRV_STATE);
			QLC_DEV_SET_RST_RDY(val, adapter->portnum);
			QLC_SHARED_REG_WR32(adapter,
					    QLCNIC_CRB_DRV_STATE, val);
		पूर्ण

		qlcnic_api_unlock(adapter);

		rtnl_lock();
		अगर (qlcnic_check_fw_dump_state(adapter) &&
		    (adapter->flags & QLCNIC_FW_RESET_OWNER)) अणु
			QLCDB(adapter, DRV, "Take FW dump\n");
			qlcnic_dump_fw(adapter);
			adapter->flags |= QLCNIC_FW_HANG;
		पूर्ण
		rtnl_unlock();

		adapter->flags &= ~QLCNIC_FW_RESET_OWNER;
		अगर (!adapter->nic_ops->start_firmware(adapter)) अणु
			qlcnic_schedule_work(adapter, qlcnic_attach_work, 0);
			adapter->fw_रुको_cnt = 0;
			वापस;
		पूर्ण
		जाओ err_ret;
	पूर्ण

	qlcnic_api_unlock(adapter);

रुको_npar:
	dev_state = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DEV_STATE);
	QLCDB(adapter, HW, "Func waiting: Device state=%u\n", dev_state);

	चयन (dev_state) अणु
	हाल QLCNIC_DEV_READY:
		अगर (!qlcnic_start_firmware(adapter)) अणु
			qlcnic_schedule_work(adapter, qlcnic_attach_work, 0);
			adapter->fw_रुको_cnt = 0;
			वापस;
		पूर्ण
	हाल QLCNIC_DEV_FAILED:
		अवरोध;
	शेष:
		qlcnic_schedule_work(adapter,
			qlcnic_fwinit_work, FW_POLL_DELAY);
		वापस;
	पूर्ण

err_ret:
	dev_err(&adapter->pdev->dev, "Fwinit work failed state=%u "
		"fw_wait_cnt=%u\n", dev_state, adapter->fw_रुको_cnt);
	netअगर_device_attach(adapter->netdev);
	qlcnic_clr_all_drv_state(adapter, 0);
पूर्ण

अटल व्योम
qlcnic_detach_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlcnic_adapter *adapter = container_of(work,
			काष्ठा qlcnic_adapter, fw_work.work);
	काष्ठा net_device *netdev = adapter->netdev;
	u32 status;

	netअगर_device_detach(netdev);

	/* Dont grab rtnl lock during Quiscent mode */
	अगर (adapter->dev_state == QLCNIC_DEV_NEED_QUISCENT) अणु
		अगर (netअगर_running(netdev))
			__qlcnic_करोwn(adapter, netdev);
	पूर्ण अन्यथा
		qlcnic_करोwn(adapter, netdev);

	status = QLC_SHARED_REG_RD32(adapter, QLCNIC_PEG_HALT_STATUS1);

	अगर (status & QLCNIC_RCODE_FATAL_ERROR) अणु
		dev_err(&adapter->pdev->dev,
			"Detaching the device: peg halt status1=0x%x\n",
					status);

		अगर (QLCNIC_FWERROR_CODE(status) == QLCNIC_FWERROR_FAN_FAILURE) अणु
			dev_err(&adapter->pdev->dev,
			"On board active cooling fan failed. "
				"Device has been halted.\n");
			dev_err(&adapter->pdev->dev,
				"Replace the adapter.\n");
		पूर्ण

		जाओ err_ret;
	पूर्ण

	अगर (adapter->ahw->temp == QLCNIC_TEMP_PANIC) अणु
		dev_err(&adapter->pdev->dev, "Detaching the device: temp=%d\n",
			adapter->ahw->temp);
		जाओ err_ret;
	पूर्ण

	/* Dont ack अगर this instance is the reset owner */
	अगर (!(adapter->flags & QLCNIC_FW_RESET_OWNER)) अणु
		अगर (qlcnic_set_drv_state(adapter, adapter->dev_state)) अणु
			dev_err(&adapter->pdev->dev,
				"Failed to set driver state,"
					"detaching the device.\n");
			जाओ err_ret;
		पूर्ण
	पूर्ण

	adapter->fw_रुको_cnt = 0;

	qlcnic_schedule_work(adapter, qlcnic_fwinit_work, FW_POLL_DELAY);

	वापस;

err_ret:
	netअगर_device_attach(netdev);
	qlcnic_clr_all_drv_state(adapter, 1);
पूर्ण

/*Transit NPAR state to NON Operational */
अटल व्योम
qlcnic_set_npar_non_operational(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 state;

	state = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DEV_NPAR_STATE);
	अगर (state == QLCNIC_DEV_NPAR_NON_OPER)
		वापस;

	अगर (qlcnic_api_lock(adapter))
		वापस;
	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DEV_NPAR_STATE,
			    QLCNIC_DEV_NPAR_NON_OPER);
	qlcnic_api_unlock(adapter);
पूर्ण

अटल व्योम qlcnic_82xx_dev_request_reset(काष्ठा qlcnic_adapter *adapter,
					  u32 key)
अणु
	u32 state, xg_val = 0, gb_val = 0;

	qlcnic_xg_set_xg0_mask(xg_val);
	qlcnic_xg_set_xg1_mask(xg_val);
	QLCWR32(adapter, QLCNIC_NIU_XG_PAUSE_CTL, xg_val);
	qlcnic_gb_set_gb0_mask(gb_val);
	qlcnic_gb_set_gb1_mask(gb_val);
	qlcnic_gb_set_gb2_mask(gb_val);
	qlcnic_gb_set_gb3_mask(gb_val);
	QLCWR32(adapter, QLCNIC_NIU_GB_PAUSE_CTL, gb_val);
	dev_info(&adapter->pdev->dev, "Pause control frames disabled"
				" on all ports\n");
	adapter->need_fw_reset = 1;

	अगर (qlcnic_api_lock(adapter))
		वापस;

	state = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DEV_STATE);

	अगर (test_bit(__QLCNIC_MAINTEन_अंकCE_MODE, &adapter->state)) अणु
		netdev_err(adapter->netdev, "%s: Device is in non-operational state\n",
			   __func__);
		qlcnic_api_unlock(adapter);

		वापस;
	पूर्ण

	अगर (state == QLCNIC_DEV_READY) अणु
		QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DEV_STATE,
				    QLCNIC_DEV_NEED_RESET);
		adapter->flags |= QLCNIC_FW_RESET_OWNER;
		QLCDB(adapter, DRV, "NEED_RESET state set\n");
		qlcnic_idc_debug_info(adapter, 0);
	पूर्ण

	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DEV_NPAR_STATE,
			    QLCNIC_DEV_NPAR_NON_OPER);
	qlcnic_api_unlock(adapter);
पूर्ण

/* Transit to NPAR READY state from NPAR NOT READY state */
अटल व्योम
qlcnic_dev_set_npar_पढ़ोy(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (qlcnic_api_lock(adapter))
		वापस;

	QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DEV_NPAR_STATE,
			    QLCNIC_DEV_NPAR_OPER);
	QLCDB(adapter, DRV, "NPAR operational state set\n");

	qlcnic_api_unlock(adapter);
पूर्ण

व्योम qlcnic_schedule_work(काष्ठा qlcnic_adapter *adapter,
			  work_func_t func, पूर्णांक delay)
अणु
	अगर (test_bit(__QLCNIC_AER, &adapter->state))
		वापस;

	INIT_DELAYED_WORK(&adapter->fw_work, func);
	queue_delayed_work(adapter->qlcnic_wq, &adapter->fw_work,
			   round_jअगरfies_relative(delay));
पूर्ण

अटल व्योम
qlcnic_attach_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlcnic_adapter *adapter = container_of(work,
				काष्ठा qlcnic_adapter, fw_work.work);
	काष्ठा net_device *netdev = adapter->netdev;
	u32 npar_state;

	अगर (adapter->ahw->op_mode != QLCNIC_MGMT_FUNC) अणु
		npar_state = QLC_SHARED_REG_RD32(adapter,
						 QLCNIC_CRB_DEV_NPAR_STATE);
		अगर (adapter->fw_रुको_cnt++ > QLCNIC_DEV_NPAR_OPER_TIMEO)
			qlcnic_clr_all_drv_state(adapter, 0);
		अन्यथा अगर (npar_state != QLCNIC_DEV_NPAR_OPER)
			qlcnic_schedule_work(adapter, qlcnic_attach_work,
							FW_POLL_DELAY);
		अन्यथा
			जाओ attach;
		QLCDB(adapter, DRV, "Waiting for NPAR state to operational\n");
		वापस;
	पूर्ण
attach:
	qlcnic_dcb_get_info(adapter->dcb);

	अगर (netअगर_running(netdev)) अणु
		अगर (qlcnic_up(adapter, netdev))
			जाओ करोne;

		qlcnic_restore_indev_addr(netdev, NETDEV_UP);
	पूर्ण

करोne:
	netअगर_device_attach(netdev);
	adapter->fw_fail_cnt = 0;
	adapter->flags &= ~QLCNIC_FW_HANG;
	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	अगर (adapter->portnum == 0)
		qlcnic_set_drv_version(adapter);

	अगर (!qlcnic_clr_drv_state(adapter))
		qlcnic_schedule_work(adapter, qlcnic_fw_poll_work,
							FW_POLL_DELAY);
पूर्ण

अटल पूर्णांक
qlcnic_check_health(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_fw_dump *fw_dump = &ahw->fw_dump;
	u32 state = 0, heartbeat;
	u32 peg_status;
	पूर्णांक err = 0;

	अगर (qlcnic_check_temp(adapter))
		जाओ detach;

	अगर (adapter->need_fw_reset)
		qlcnic_dev_request_reset(adapter, 0);

	state = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DEV_STATE);
	अगर (state == QLCNIC_DEV_NEED_RESET) अणु
		qlcnic_set_npar_non_operational(adapter);
		adapter->need_fw_reset = 1;
	पूर्ण अन्यथा अगर (state == QLCNIC_DEV_NEED_QUISCENT)
		जाओ detach;

	heartbeat = QLC_SHARED_REG_RD32(adapter, QLCNIC_PEG_ALIVE_COUNTER);
	अगर (heartbeat != adapter->heartbeat) अणु
		adapter->heartbeat = heartbeat;
		adapter->fw_fail_cnt = 0;
		अगर (adapter->need_fw_reset)
			जाओ detach;

		अगर (ahw->reset_context && qlcnic_स्वतः_fw_reset)
			qlcnic_reset_hw_context(adapter);

		वापस 0;
	पूर्ण

	अगर (++adapter->fw_fail_cnt < FW_FAIL_THRESH)
		वापस 0;

	adapter->flags |= QLCNIC_FW_HANG;

	qlcnic_dev_request_reset(adapter, 0);

	अगर (qlcnic_स्वतः_fw_reset)
		clear_bit(__QLCNIC_FW_ATTACHED, &adapter->state);

	dev_err(&adapter->pdev->dev, "firmware hang detected\n");
	peg_status = QLC_SHARED_REG_RD32(adapter, QLCNIC_PEG_HALT_STATUS1);
	dev_err(&adapter->pdev->dev, "Dumping hw/fw registers\n"
			"PEG_HALT_STATUS1: 0x%x, PEG_HALT_STATUS2: 0x%x,\n"
			"PEG_NET_0_PC: 0x%x, PEG_NET_1_PC: 0x%x,\n"
			"PEG_NET_2_PC: 0x%x, PEG_NET_3_PC: 0x%x,\n"
			"PEG_NET_4_PC: 0x%x\n",
			peg_status,
			QLC_SHARED_REG_RD32(adapter, QLCNIC_PEG_HALT_STATUS2),
			QLCRD32(adapter, QLCNIC_CRB_PEG_NET_0 + 0x3c, &err),
			QLCRD32(adapter, QLCNIC_CRB_PEG_NET_1 + 0x3c, &err),
			QLCRD32(adapter, QLCNIC_CRB_PEG_NET_2 + 0x3c, &err),
			QLCRD32(adapter, QLCNIC_CRB_PEG_NET_3 + 0x3c, &err),
			QLCRD32(adapter, QLCNIC_CRB_PEG_NET_4 + 0x3c, &err));
	अगर (QLCNIC_FWERROR_CODE(peg_status) == 0x67)
		dev_err(&adapter->pdev->dev,
			"Firmware aborted with error code 0x00006700. "
				"Device is being reset.\n");
detach:
	adapter->dev_state = (state == QLCNIC_DEV_NEED_QUISCENT) ? state :
		QLCNIC_DEV_NEED_RESET;

	अगर (qlcnic_स्वतः_fw_reset && !test_and_set_bit(__QLCNIC_RESETTING,
						      &adapter->state)) अणु

		qlcnic_schedule_work(adapter, qlcnic_detach_work, 0);
		QLCDB(adapter, DRV, "fw recovery scheduled.\n");
	पूर्ण अन्यथा अगर (!qlcnic_स्वतः_fw_reset && fw_dump->enable &&
		   adapter->flags & QLCNIC_FW_RESET_OWNER) अणु
		qlcnic_dump_fw(adapter);
	पूर्ण

	वापस 1;
पूर्ण

व्योम qlcnic_fw_poll_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlcnic_adapter *adapter = container_of(work,
				काष्ठा qlcnic_adapter, fw_work.work);

	अगर (test_bit(__QLCNIC_RESETTING, &adapter->state))
		जाओ reschedule;


	अगर (qlcnic_check_health(adapter))
		वापस;

	अगर (adapter->fhash.fnum)
		qlcnic_prune_lb_filters(adapter);

reschedule:
	qlcnic_schedule_work(adapter, qlcnic_fw_poll_work, FW_POLL_DELAY);
पूर्ण

अटल पूर्णांक qlcnic_is_first_func(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *oth_pdev;
	पूर्णांक val = pdev->devfn;

	जबतक (val-- > 0) अणु
		oth_pdev = pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr
			(pdev->bus), pdev->bus->number,
			PCI_DEVFN(PCI_SLOT(pdev->devfn), val));
		अगर (!oth_pdev)
			जारी;

		अगर (oth_pdev->current_state != PCI_D3cold) अणु
			pci_dev_put(oth_pdev);
			वापस 0;
		पूर्ण
		pci_dev_put(oth_pdev);
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक qlcnic_attach_func(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक err, first_func;
	काष्ठा qlcnic_adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = adapter->netdev;

	pdev->error_state = pci_channel_io_normal;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;

	pci_set_master(pdev);
	pci_restore_state(pdev);

	first_func = qlcnic_is_first_func(pdev);

	अगर (qlcnic_api_lock(adapter))
		वापस -EINVAL;

	अगर (adapter->ahw->op_mode != QLCNIC_NON_PRIV_FUNC && first_func) अणु
		adapter->need_fw_reset = 1;
		set_bit(__QLCNIC_START_FW, &adapter->state);
		QLC_SHARED_REG_WR32(adapter, QLCNIC_CRB_DEV_STATE,
				    QLCNIC_DEV_INITIALIZING);
		QLCDB(adapter, DRV, "Restarting fw\n");
	पूर्ण
	qlcnic_api_unlock(adapter);

	err = qlcnic_start_firmware(adapter);
	अगर (err)
		वापस err;

	qlcnic_clr_drv_state(adapter);
	kमुक्त(adapter->msix_entries);
	adapter->msix_entries = शून्य;
	err = qlcnic_setup_पूर्णांकr(adapter);

	अगर (err) अणु
		kमुक्त(adapter->msix_entries);
		netdev_err(netdev, "failed to setup interrupt\n");
		वापस err;
	पूर्ण

	अगर (netअगर_running(netdev)) अणु
		err = qlcnic_attach(adapter);
		अगर (err) अणु
			qlcnic_clr_all_drv_state(adapter, 1);
			clear_bit(__QLCNIC_AER, &adapter->state);
			netअगर_device_attach(netdev);
			वापस err;
		पूर्ण

		err = qlcnic_up(adapter, netdev);
		अगर (err)
			जाओ करोne;

		qlcnic_restore_indev_addr(netdev, NETDEV_UP);
	पूर्ण
 करोne:
	netअगर_device_attach(netdev);
	वापस err;
पूर्ण

अटल pci_ers_result_t qlcnic_82xx_io_error_detected(काष्ठा pci_dev *pdev,
						      pci_channel_state_t state)
अणु
	काष्ठा qlcnic_adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	अगर (state == pci_channel_io_normal)
		वापस PCI_ERS_RESULT_RECOVERED;

	set_bit(__QLCNIC_AER, &adapter->state);
	netअगर_device_detach(netdev);

	cancel_delayed_work_sync(&adapter->fw_work);

	अगर (netअगर_running(netdev))
		qlcnic_करोwn(adapter, netdev);

	qlcnic_detach(adapter);
	qlcnic_tearकरोwn_पूर्णांकr(adapter);

	clear_bit(__QLCNIC_RESETTING, &adapter->state);

	pci_save_state(pdev);
	pci_disable_device(pdev);

	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

अटल pci_ers_result_t qlcnic_82xx_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	pci_ers_result_t res;

	rtnl_lock();
	res = qlcnic_attach_func(pdev) ? PCI_ERS_RESULT_DISCONNECT :
					 PCI_ERS_RESULT_RECOVERED;
	rtnl_unlock();

	वापस res;
पूर्ण

अटल व्योम qlcnic_82xx_io_resume(काष्ठा pci_dev *pdev)
अणु
	u32 state;
	काष्ठा qlcnic_adapter *adapter = pci_get_drvdata(pdev);

	state = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DEV_STATE);
	अगर (state == QLCNIC_DEV_READY && test_and_clear_bit(__QLCNIC_AER,
							    &adapter->state))
		qlcnic_schedule_work(adapter, qlcnic_fw_poll_work,
				     FW_POLL_DELAY);
पूर्ण

अटल pci_ers_result_t qlcnic_io_error_detected(काष्ठा pci_dev *pdev,
						 pci_channel_state_t state)
अणु
	काष्ठा qlcnic_adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा qlcnic_hardware_ops *hw_ops = adapter->ahw->hw_ops;

	अगर (hw_ops->io_error_detected) अणु
		वापस hw_ops->io_error_detected(pdev, state);
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "AER error_detected handler not registered.\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण
पूर्ण

अटल pci_ers_result_t qlcnic_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qlcnic_adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा qlcnic_hardware_ops *hw_ops = adapter->ahw->hw_ops;

	अगर (hw_ops->io_slot_reset) अणु
		वापस hw_ops->io_slot_reset(pdev);
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "AER slot_reset handler not registered.\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण
पूर्ण

अटल व्योम qlcnic_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qlcnic_adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा qlcnic_hardware_ops *hw_ops = adapter->ahw->hw_ops;

	अगर (hw_ops->io_resume)
		hw_ops->io_resume(pdev);
	अन्यथा
		dev_err(&pdev->dev, "AER resume handler not registered.\n");
पूर्ण


अटल पूर्णांक
qlcnicvf_start_firmware(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक err;

	err = qlcnic_can_start_firmware(adapter);
	अगर (err)
		वापस err;

	err = qlcnic_check_npar_opertional(adapter);
	अगर (err)
		वापस err;

	err = qlcnic_initialize_nic(adapter);
	अगर (err)
		वापस err;

	qlcnic_check_options(adapter);

	err = qlcnic_set_eचयन_port_config(adapter);
	अगर (err)
		वापस err;

	adapter->need_fw_reset = 0;

	वापस err;
पूर्ण

पूर्णांक qlcnic_validate_rings(काष्ठा qlcnic_adapter *adapter, __u32 ring_cnt,
			  पूर्णांक queue_type)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	अक्षर buf[8];

	अगर (queue_type == QLCNIC_RX_QUEUE)
		म_नकल(buf, "SDS");
	अन्यथा
		म_नकल(buf, "Tx");

	अगर (!is_घातer_of_2(ring_cnt)) अणु
		netdev_err(netdev, "%s rings value should be a power of 2\n",
			   buf);
		वापस -EINVAL;
	पूर्ण

	अगर (qlcnic_82xx_check(adapter) && (queue_type == QLCNIC_TX_QUEUE) &&
	    !qlcnic_check_multi_tx(adapter)) अणु
			netdev_err(netdev, "No Multi Tx queue support\n");
			वापस -EINVAL;
	पूर्ण

	अगर (ring_cnt > num_online_cpus()) अणु
		netdev_err(netdev,
			   "%s value[%u] should not be higher than, number of online CPUs\n",
			   buf, num_online_cpus());
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qlcnic_setup_rings(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	u8 tx_rings, rx_rings;
	पूर्णांक err;

	अगर (test_bit(__QLCNIC_RESETTING, &adapter->state))
		वापस -EBUSY;

	tx_rings = adapter->drv_tss_rings;
	rx_rings = adapter->drv_rss_rings;

	netअगर_device_detach(netdev);

	err = qlcnic_set_real_num_queues(adapter, tx_rings, rx_rings);
	अगर (err)
		जाओ करोne;

	अगर (netअगर_running(netdev))
		__qlcnic_करोwn(adapter, netdev);

	qlcnic_detach(adapter);

	अगर (qlcnic_83xx_check(adapter)) अणु
		qlcnic_83xx_मुक्त_mbx_पूर्णांकr(adapter);
		qlcnic_83xx_enable_mbx_poll(adapter);
	पूर्ण

	qlcnic_tearकरोwn_पूर्णांकr(adapter);

	err = qlcnic_setup_पूर्णांकr(adapter);
	अगर (err) अणु
		kमुक्त(adapter->msix_entries);
		netdev_err(netdev, "failed to setup interrupt\n");
		वापस err;
	पूर्ण

	/* Check अगर we need to update real_num_अणुtx|rxपूर्ण_queues because
	 * qlcnic_setup_पूर्णांकr() may change Tx/Rx rings size
	 */
	अगर ((tx_rings != adapter->drv_tx_rings) ||
	    (rx_rings != adapter->drv_sds_rings)) अणु
		err = qlcnic_set_real_num_queues(adapter,
						 adapter->drv_tx_rings,
						 adapter->drv_sds_rings);
		अगर (err)
			जाओ करोne;
	पूर्ण

	अगर (qlcnic_83xx_check(adapter)) अणु
		qlcnic_83xx_initialize_nic(adapter, 1);
		err = qlcnic_83xx_setup_mbx_पूर्णांकr(adapter);
		qlcnic_83xx_disable_mbx_poll(adapter);
		अगर (err) अणु
			dev_err(&adapter->pdev->dev,
				"failed to setup mbx interrupt\n");
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (netअगर_running(netdev)) अणु
		err = qlcnic_attach(adapter);
		अगर (err)
			जाओ करोne;
		err = __qlcnic_up(adapter, netdev);
		अगर (err)
			जाओ करोne;
		qlcnic_restore_indev_addr(netdev, NETDEV_UP);
	पूर्ण
करोne:
	netअगर_device_attach(netdev);
	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_INET

#घोषणा is_qlcnic_netdev(dev) (dev->netdev_ops == &qlcnic_netdev_ops)

अटल व्योम
qlcnic_config_indev_addr(काष्ठा qlcnic_adapter *adapter,
			काष्ठा net_device *dev, अचिन्हित दीर्घ event)
अणु
	स्थिर काष्ठा in_अगरaddr *अगरa;
	काष्ठा in_device *indev;

	indev = in_dev_get(dev);
	अगर (!indev)
		वापस;

	in_dev_क्रम_each_अगरa_rtnl(अगरa, indev) अणु
		चयन (event) अणु
		हाल NETDEV_UP:
			qlcnic_config_ipaddr(adapter,
					अगरa->अगरa_address, QLCNIC_IP_UP);
			अवरोध;
		हाल NETDEV_DOWN:
			qlcnic_config_ipaddr(adapter,
					अगरa->अगरa_address, QLCNIC_IP_DOWN);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	in_dev_put(indev);
पूर्ण

व्योम qlcnic_restore_indev_addr(काष्ठा net_device *netdev, अचिन्हित दीर्घ event)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा net_device *dev;
	u16 vid;

	qlcnic_config_indev_addr(adapter, netdev, event);

	rcu_पढ़ो_lock();
	क्रम_each_set_bit(vid, adapter->vlans, VLAN_N_VID) अणु
		dev = __vlan_find_dev_deep_rcu(netdev, htons(ETH_P_8021Q), vid);
		अगर (!dev)
			जारी;
		qlcnic_config_indev_addr(adapter, dev, event);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक qlcnic_netdev_event(काष्ठा notअगरier_block *this,
				 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा qlcnic_adapter *adapter;
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

recheck:
	अगर (dev == शून्य)
		जाओ करोne;

	अगर (is_vlan_dev(dev)) अणु
		dev = vlan_dev_real_dev(dev);
		जाओ recheck;
	पूर्ण

	अगर (!is_qlcnic_netdev(dev))
		जाओ करोne;

	adapter = netdev_priv(dev);

	अगर (!adapter)
		जाओ करोne;

	अगर (!test_bit(__QLCNIC_DEV_UP, &adapter->state))
		जाओ करोne;

	qlcnic_config_indev_addr(adapter, dev, event);
करोne:
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक
qlcnic_inetaddr_event(काष्ठा notअगरier_block *this,
		अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा qlcnic_adapter *adapter;
	काष्ठा net_device *dev;

	काष्ठा in_अगरaddr *अगरa = (काष्ठा in_अगरaddr *)ptr;

	dev = अगरa->अगरa_dev ? अगरa->अगरa_dev->dev : शून्य;

recheck:
	अगर (dev == शून्य)
		जाओ करोne;

	अगर (is_vlan_dev(dev)) अणु
		dev = vlan_dev_real_dev(dev);
		जाओ recheck;
	पूर्ण

	अगर (!is_qlcnic_netdev(dev))
		जाओ करोne;

	adapter = netdev_priv(dev);

	अगर (!adapter)
		जाओ करोne;

	अगर (!test_bit(__QLCNIC_DEV_UP, &adapter->state))
		जाओ करोne;

	चयन (event) अणु
	हाल NETDEV_UP:
		qlcnic_config_ipaddr(adapter, अगरa->अगरa_address, QLCNIC_IP_UP);

		अवरोध;
	हाल NETDEV_DOWN:
		qlcnic_config_ipaddr(adapter, अगरa->अगरa_address, QLCNIC_IP_DOWN);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

करोne:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block	qlcnic_netdev_cb = अणु
	.notअगरier_call = qlcnic_netdev_event,
पूर्ण;

अटल काष्ठा notअगरier_block qlcnic_inetaddr_cb = अणु
	.notअगरier_call = qlcnic_inetaddr_event,
पूर्ण;
#अन्यथा
व्योम qlcnic_restore_indev_addr(काष्ठा net_device *dev, अचिन्हित दीर्घ event)
अणु पूर्ण
#पूर्ण_अगर
अटल स्थिर काष्ठा pci_error_handlers qlcnic_err_handler = अणु
	.error_detected = qlcnic_io_error_detected,
	.slot_reset = qlcnic_io_slot_reset,
	.resume = qlcnic_io_resume,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(qlcnic_pm_ops, qlcnic_suspend, qlcnic_resume);

अटल काष्ठा pci_driver qlcnic_driver = अणु
	.name = qlcnic_driver_name,
	.id_table = qlcnic_pci_tbl,
	.probe = qlcnic_probe,
	.हटाओ = qlcnic_हटाओ,
	.driver.pm = &qlcnic_pm_ops,
	.shutकरोwn = qlcnic_shutकरोwn,
	.err_handler = &qlcnic_err_handler,
#अगर_घोषित CONFIG_QLCNIC_SRIOV
	.sriov_configure = qlcnic_pci_sriov_configure,
#पूर्ण_अगर

पूर्ण;

अटल पूर्णांक __init qlcnic_init_module(व्योम)
अणु
	पूर्णांक ret;

	prपूर्णांकk(KERN_INFO "%s\n", qlcnic_driver_string);

#अगर_घोषित CONFIG_INET
	रेजिस्टर_netdevice_notअगरier(&qlcnic_netdev_cb);
	रेजिस्टर_inetaddr_notअगरier(&qlcnic_inetaddr_cb);
#पूर्ण_अगर

	ret = pci_रेजिस्टर_driver(&qlcnic_driver);
	अगर (ret) अणु
#अगर_घोषित CONFIG_INET
		unरेजिस्टर_inetaddr_notअगरier(&qlcnic_inetaddr_cb);
		unरेजिस्टर_netdevice_notअगरier(&qlcnic_netdev_cb);
#पूर्ण_अगर
	पूर्ण

	वापस ret;
पूर्ण

module_init(qlcnic_init_module);

अटल व्योम __निकास qlcnic_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&qlcnic_driver);

#अगर_घोषित CONFIG_INET
	unरेजिस्टर_inetaddr_notअगरier(&qlcnic_inetaddr_cb);
	unरेजिस्टर_netdevice_notअगरier(&qlcnic_netdev_cb);
#पूर्ण_अगर
पूर्ण

module_निकास(qlcnic_निकास_module);
