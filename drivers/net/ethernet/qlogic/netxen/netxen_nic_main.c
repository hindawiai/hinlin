<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2003 - 2009 NetXen, Inc.
 * Copyright (C) 2009 - QLogic Corporation.
 * All rights reserved.
 */

#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "netxen_nic_hw.h"

#समावेश "netxen_nic.h"

#समावेश <linux/dma-mapping.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/aer.h>

MODULE_DESCRIPTION("QLogic/NetXen (1/10) GbE Intelligent Ethernet Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(NETXEN_NIC_LINUX_VERSIONID);
MODULE_FIRMWARE(NX_UNIFIED_ROMIMAGE_NAME);

अक्षर netxen_nic_driver_name[] = "netxen_nic";
अटल अक्षर netxen_nic_driver_string[] = "QLogic/NetXen Network Driver v"
    NETXEN_NIC_LINUX_VERSIONID;

अटल पूर्णांक port_mode = NETXEN_PORT_MODE_AUTO_NEG;

/* Default to restricted 1G स्वतः-neg mode */
अटल पूर्णांक wol_port_mode = 5;

अटल पूर्णांक use_msi = 1;

अटल पूर्णांक use_msi_x = 1;

अटल पूर्णांक स्वतः_fw_reset = AUTO_FW_RESET_ENABLED;
module_param(स्वतः_fw_reset, पूर्णांक, 0644);
MODULE_PARM_DESC(स्वतः_fw_reset,"Auto firmware reset (0=disabled, 1=enabled");

अटल पूर्णांक netxen_nic_probe(काष्ठा pci_dev *pdev,
		स्थिर काष्ठा pci_device_id *ent);
अटल व्योम netxen_nic_हटाओ(काष्ठा pci_dev *pdev);
अटल पूर्णांक netxen_nic_खोलो(काष्ठा net_device *netdev);
अटल पूर्णांक netxen_nic_बंद(काष्ठा net_device *netdev);
अटल netdev_tx_t netxen_nic_xmit_frame(काष्ठा sk_buff *,
					       काष्ठा net_device *);
अटल व्योम netxen_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue);
अटल व्योम netxen_tx_समयout_task(काष्ठा work_काष्ठा *work);
अटल व्योम netxen_fw_poll_work(काष्ठा work_काष्ठा *work);
अटल व्योम netxen_schedule_work(काष्ठा netxen_adapter *adapter,
		work_func_t func, पूर्णांक delay);
अटल व्योम netxen_cancel_fw_work(काष्ठा netxen_adapter *adapter);
अटल पूर्णांक netxen_nic_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);

अटल व्योम netxen_create_sysfs_entries(काष्ठा netxen_adapter *adapter);
अटल व्योम netxen_हटाओ_sysfs_entries(काष्ठा netxen_adapter *adapter);
अटल व्योम netxen_create_diag_entries(काष्ठा netxen_adapter *adapter);
अटल व्योम netxen_हटाओ_diag_entries(काष्ठा netxen_adapter *adapter);
अटल पूर्णांक nx_dev_request_aer(काष्ठा netxen_adapter *adapter);
अटल पूर्णांक nx_decr_dev_ref_cnt(काष्ठा netxen_adapter *adapter);
अटल पूर्णांक netxen_can_start_firmware(काष्ठा netxen_adapter *adapter);

अटल irqवापस_t netxen_पूर्णांकr(पूर्णांक irq, व्योम *data);
अटल irqवापस_t netxen_msi_पूर्णांकr(पूर्णांक irq, व्योम *data);
अटल irqवापस_t netxen_msix_पूर्णांकr(पूर्णांक irq, व्योम *data);

अटल व्योम netxen_मुक्त_ip_list(काष्ठा netxen_adapter *, bool);
अटल व्योम netxen_restore_indev_addr(काष्ठा net_device *dev, अचिन्हित दीर्घ);
अटल व्योम netxen_nic_get_stats(काष्ठा net_device *dev,
				 काष्ठा rtnl_link_stats64 *stats);
अटल पूर्णांक netxen_nic_set_mac(काष्ठा net_device *netdev, व्योम *p);

/*  PCI Device ID Table  */
#घोषणा ENTRY(device) \
	अणुPCI_DEVICE(PCI_VENDOR_ID_NETXEN, (device)), \
	.class = PCI_CLASS_NETWORK_ETHERNET << 8, .class_mask = ~0पूर्ण

अटल स्थिर काष्ठा pci_device_id netxen_pci_tbl[] = अणु
	ENTRY(PCI_DEVICE_ID_NX2031_10GXSR),
	ENTRY(PCI_DEVICE_ID_NX2031_10GCX4),
	ENTRY(PCI_DEVICE_ID_NX2031_4GCU),
	ENTRY(PCI_DEVICE_ID_NX2031_IMEZ),
	ENTRY(PCI_DEVICE_ID_NX2031_HMEZ),
	ENTRY(PCI_DEVICE_ID_NX2031_XG_MGMT),
	ENTRY(PCI_DEVICE_ID_NX2031_XG_MGMT2),
	ENTRY(PCI_DEVICE_ID_NX3031),
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, netxen_pci_tbl);

अटल uपूर्णांक32_t crb_cmd_producer[4] = अणु
	CRB_CMD_PRODUCER_OFFSET, CRB_CMD_PRODUCER_OFFSET_1,
	CRB_CMD_PRODUCER_OFFSET_2, CRB_CMD_PRODUCER_OFFSET_3
पूर्ण;

व्योम
netxen_nic_update_cmd_producer(काष्ठा netxen_adapter *adapter,
		काष्ठा nx_host_tx_ring *tx_ring)
अणु
	NXWRIO(adapter, tx_ring->crb_cmd_producer, tx_ring->producer);
पूर्ण

अटल uपूर्णांक32_t crb_cmd_consumer[4] = अणु
	CRB_CMD_CONSUMER_OFFSET, CRB_CMD_CONSUMER_OFFSET_1,
	CRB_CMD_CONSUMER_OFFSET_2, CRB_CMD_CONSUMER_OFFSET_3
पूर्ण;

अटल अंतरभूत व्योम
netxen_nic_update_cmd_consumer(काष्ठा netxen_adapter *adapter,
		काष्ठा nx_host_tx_ring *tx_ring)
अणु
	NXWRIO(adapter, tx_ring->crb_cmd_consumer, tx_ring->sw_consumer);
पूर्ण

अटल uपूर्णांक32_t msi_tgt_status[8] = अणु
	ISR_INT_TARGET_STATUS, ISR_INT_TARGET_STATUS_F1,
	ISR_INT_TARGET_STATUS_F2, ISR_INT_TARGET_STATUS_F3,
	ISR_INT_TARGET_STATUS_F4, ISR_INT_TARGET_STATUS_F5,
	ISR_INT_TARGET_STATUS_F6, ISR_INT_TARGET_STATUS_F7
पूर्ण;

अटल काष्ठा netxen_legacy_पूर्णांकr_set legacy_पूर्णांकr[] = NX_LEGACY_INTR_CONFIG;

अटल अंतरभूत व्योम netxen_nic_disable_पूर्णांक(काष्ठा nx_host_sds_ring *sds_ring)
अणु
	काष्ठा netxen_adapter *adapter = sds_ring->adapter;

	NXWRIO(adapter, sds_ring->crb_पूर्णांकr_mask, 0);
पूर्ण

अटल अंतरभूत व्योम netxen_nic_enable_पूर्णांक(काष्ठा nx_host_sds_ring *sds_ring)
अणु
	काष्ठा netxen_adapter *adapter = sds_ring->adapter;

	NXWRIO(adapter, sds_ring->crb_पूर्णांकr_mask, 0x1);

	अगर (!NETXEN_IS_MSI_FAMILY(adapter))
		NXWRIO(adapter, adapter->tgt_mask_reg, 0xfbff);
पूर्ण

अटल पूर्णांक
netxen_alloc_sds_rings(काष्ठा netxen_recv_context *recv_ctx, पूर्णांक count)
अणु
	पूर्णांक size = माप(काष्ठा nx_host_sds_ring) * count;

	recv_ctx->sds_rings = kzalloc(size, GFP_KERNEL);

	वापस recv_ctx->sds_rings == शून्य;
पूर्ण

अटल व्योम
netxen_मुक्त_sds_rings(काष्ठा netxen_recv_context *recv_ctx)
अणु
	kमुक्त(recv_ctx->sds_rings);
	recv_ctx->sds_rings = शून्य;
पूर्ण

अटल पूर्णांक
netxen_napi_add(काष्ठा netxen_adapter *adapter, काष्ठा net_device *netdev)
अणु
	पूर्णांक ring;
	काष्ठा nx_host_sds_ring *sds_ring;
	काष्ठा netxen_recv_context *recv_ctx = &adapter->recv_ctx;

	अगर (netxen_alloc_sds_rings(recv_ctx, adapter->max_sds_rings))
		वापस -ENOMEM;

	क्रम (ring = 0; ring < adapter->max_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];
		netअगर_napi_add(netdev, &sds_ring->napi,
				netxen_nic_poll, NAPI_POLL_WEIGHT);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
netxen_napi_del(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक ring;
	काष्ठा nx_host_sds_ring *sds_ring;
	काष्ठा netxen_recv_context *recv_ctx = &adapter->recv_ctx;

	क्रम (ring = 0; ring < adapter->max_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];
		netअगर_napi_del(&sds_ring->napi);
	पूर्ण

	netxen_मुक्त_sds_rings(&adapter->recv_ctx);
पूर्ण

अटल व्योम
netxen_napi_enable(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक ring;
	काष्ठा nx_host_sds_ring *sds_ring;
	काष्ठा netxen_recv_context *recv_ctx = &adapter->recv_ctx;

	क्रम (ring = 0; ring < adapter->max_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];
		napi_enable(&sds_ring->napi);
		netxen_nic_enable_पूर्णांक(sds_ring);
	पूर्ण
पूर्ण

अटल व्योम
netxen_napi_disable(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक ring;
	काष्ठा nx_host_sds_ring *sds_ring;
	काष्ठा netxen_recv_context *recv_ctx = &adapter->recv_ctx;

	क्रम (ring = 0; ring < adapter->max_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];
		netxen_nic_disable_पूर्णांक(sds_ring);
		napi_synchronize(&sds_ring->napi);
		napi_disable(&sds_ring->napi);
	पूर्ण
पूर्ण

अटल पूर्णांक nx_set_dma_mask(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	uपूर्णांक64_t mask, cmask;

	adapter->pci_using_dac = 0;

	mask = DMA_BIT_MASK(32);
	cmask = DMA_BIT_MASK(32);

	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id)) अणु
#अगर_अघोषित CONFIG_IA64
		mask = DMA_BIT_MASK(35);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		mask = DMA_BIT_MASK(39);
		cmask = mask;
	पूर्ण

	अगर (dma_set_mask(&pdev->dev, mask) == 0 &&
	    dma_set_coherent_mask(&pdev->dev, cmask) == 0) अणु
		adapter->pci_using_dac = 1;
		वापस 0;
	पूर्ण

	वापस -EIO;
पूर्ण

/* Update addressable range अगर firmware supports it */
अटल पूर्णांक
nx_update_dma_mask(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक change, shअगरt, err;
	uपूर्णांक64_t mask, old_mask, old_cmask;
	काष्ठा pci_dev *pdev = adapter->pdev;

	change = 0;

	shअगरt = NXRD32(adapter, CRB_DMA_SHIFT);
	अगर (shअगरt > 32)
		वापस 0;

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id) && (shअगरt > 9))
		change = 1;
	अन्यथा अगर ((adapter->ahw.revision_id == NX_P2_C1) && (shअगरt <= 4))
		change = 1;

	अगर (change) अणु
		old_mask = pdev->dma_mask;
		old_cmask = pdev->dev.coherent_dma_mask;

		mask = DMA_BIT_MASK(32+shअगरt);

		err = dma_set_mask(&pdev->dev, mask);
		अगर (err)
			जाओ err_out;

		अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id)) अणु

			err = dma_set_coherent_mask(&pdev->dev, mask);
			अगर (err)
				जाओ err_out;
		पूर्ण
		dev_info(&pdev->dev, "using %d-bit dma mask\n", 32+shअगरt);
	पूर्ण

	वापस 0;

err_out:
	dma_set_mask(&pdev->dev, old_mask);
	dma_set_coherent_mask(&pdev->dev, old_cmask);
	वापस err;
पूर्ण

अटल पूर्णांक
netxen_check_hw_init(काष्ठा netxen_adapter *adapter, पूर्णांक first_boot)
अणु
	u32 val, समयout;

	अगर (first_boot == 0x55555555) अणु
		/* This is the first boot after घातer up */
		NXWR32(adapter, NETXEN_CAM_RAM(0x1fc), NETXEN_BDINFO_MAGIC);

		अगर (!NX_IS_REVISION_P2(adapter->ahw.revision_id))
			वापस 0;

		/* PCI bus master workaround */
		first_boot = NXRD32(adapter, NETXEN_PCIE_REG(0x4));
		अगर (!(first_boot & 0x4)) अणु
			first_boot |= 0x4;
			NXWR32(adapter, NETXEN_PCIE_REG(0x4), first_boot);
			NXRD32(adapter, NETXEN_PCIE_REG(0x4));
		पूर्ण

		/* This is the first boot after घातer up */
		first_boot = NXRD32(adapter, NETXEN_ROMUSB_GLB_SW_RESET);
		अगर (first_boot != 0x80000f) अणु
			/* clear the रेजिस्टर क्रम future unloads/loads */
			NXWR32(adapter, NETXEN_CAM_RAM(0x1fc), 0);
			वापस -EIO;
		पूर्ण

		/* Start P2 boot loader */
		val = NXRD32(adapter, NETXEN_ROMUSB_GLB_PEGTUNE_DONE);
		NXWR32(adapter, NETXEN_ROMUSB_GLB_PEGTUNE_DONE, val | 0x1);
		समयout = 0;
		करो अणु
			msleep(1);
			val = NXRD32(adapter, NETXEN_CAM_RAM(0x1fc));

			अगर (++समयout > 5000)
				वापस -EIO;

		पूर्ण जबतक (val == NETXEN_BDINFO_MAGIC);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम netxen_set_port_mode(काष्ठा netxen_adapter *adapter)
अणु
	u32 val, data;

	val = adapter->ahw.board_type;
	अगर ((val == NETXEN_BRDTYPE_P3_HMEZ) ||
		(val == NETXEN_BRDTYPE_P3_XG_LOM)) अणु
		अगर (port_mode == NETXEN_PORT_MODE_802_3_AP) अणु
			data = NETXEN_PORT_MODE_802_3_AP;
			NXWR32(adapter, NETXEN_PORT_MODE_ADDR, data);
		पूर्ण अन्यथा अगर (port_mode == NETXEN_PORT_MODE_XG) अणु
			data = NETXEN_PORT_MODE_XG;
			NXWR32(adapter, NETXEN_PORT_MODE_ADDR, data);
		पूर्ण अन्यथा अगर (port_mode == NETXEN_PORT_MODE_AUTO_NEG_1G) अणु
			data = NETXEN_PORT_MODE_AUTO_NEG_1G;
			NXWR32(adapter, NETXEN_PORT_MODE_ADDR, data);
		पूर्ण अन्यथा अगर (port_mode == NETXEN_PORT_MODE_AUTO_NEG_XG) अणु
			data = NETXEN_PORT_MODE_AUTO_NEG_XG;
			NXWR32(adapter, NETXEN_PORT_MODE_ADDR, data);
		पूर्ण अन्यथा अणु
			data = NETXEN_PORT_MODE_AUTO_NEG;
			NXWR32(adapter, NETXEN_PORT_MODE_ADDR, data);
		पूर्ण

		अगर ((wol_port_mode != NETXEN_PORT_MODE_802_3_AP) &&
			(wol_port_mode != NETXEN_PORT_MODE_XG) &&
			(wol_port_mode != NETXEN_PORT_MODE_AUTO_NEG_1G) &&
			(wol_port_mode != NETXEN_PORT_MODE_AUTO_NEG_XG)) अणु
			wol_port_mode = NETXEN_PORT_MODE_AUTO_NEG;
		पूर्ण
		NXWR32(adapter, NETXEN_WOL_PORT_MODE, wol_port_mode);
	पूर्ण
पूर्ण

#घोषणा PCI_CAP_ID_GEN  0x10

अटल व्योम netxen_pcie_strap_init(काष्ठा netxen_adapter *adapter)
अणु
	u32 pdevfuncsave;
	u32 c8c9value = 0;
	u32 chicken = 0;
	u32 control = 0;
	पूर्णांक i, pos;
	काष्ठा pci_dev *pdev;

	pdev = adapter->pdev;

	chicken = NXRD32(adapter, NETXEN_PCIE_REG(PCIE_CHICKEN3));
	/* clear chicken3.25:24 */
	chicken &= 0xFCFFFFFF;
	/*
	 * अगर gen1 and B0, set F1020 - अगर gen 2, करो nothing
	 * अगर gen2 set to F1000
	 */
	pos = pci_find_capability(pdev, PCI_CAP_ID_GEN);
	अगर (pos == 0xC0) अणु
		pci_पढ़ो_config_dword(pdev, pos + 0x10, &control);
		अगर ((control & 0x000F0000) != 0x00020000) अणु
			/*  set chicken3.24 अगर gen1 */
			chicken |= 0x01000000;
		पूर्ण
		dev_info(&adapter->pdev->dev, "Gen2 strapping detected\n");
		c8c9value = 0xF1000;
	पूर्ण अन्यथा अणु
		/* set chicken3.24 अगर gen1 */
		chicken |= 0x01000000;
		dev_info(&adapter->pdev->dev, "Gen1 strapping detected\n");
		अगर (adapter->ahw.revision_id == NX_P3_B0)
			c8c9value = 0xF1020;
		अन्यथा
			c8c9value = 0;
	पूर्ण

	NXWR32(adapter, NETXEN_PCIE_REG(PCIE_CHICKEN3), chicken);

	अगर (!c8c9value)
		वापस;

	pdevfuncsave = pdev->devfn;
	अगर (pdevfuncsave & 0x07)
		वापस;

	क्रम (i = 0; i < 8; i++) अणु
		pci_पढ़ो_config_dword(pdev, pos + 8, &control);
		pci_पढ़ो_config_dword(pdev, pos + 8, &control);
		pci_ग_लिखो_config_dword(pdev, pos + 8, c8c9value);
		pdev->devfn++;
	पूर्ण
	pdev->devfn = pdevfuncsave;
पूर्ण

अटल व्योम netxen_set_msix_bit(काष्ठा pci_dev *pdev, पूर्णांक enable)
अणु
	u32 control;

	अगर (pdev->msix_cap) अणु
		pci_पढ़ो_config_dword(pdev, pdev->msix_cap, &control);
		अगर (enable)
			control |= PCI_MSIX_FLAGS_ENABLE;
		अन्यथा
			control = 0;
		pci_ग_लिखो_config_dword(pdev, pdev->msix_cap, control);
	पूर्ण
पूर्ण

अटल व्योम netxen_init_msix_entries(काष्ठा netxen_adapter *adapter, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		adapter->msix_entries[i].entry = i;
पूर्ण

अटल पूर्णांक
netxen_पढ़ो_mac_addr(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर *p;
	u64 mac_addr;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id)) अणु
		अगर (netxen_p3_get_mac_addr(adapter, &mac_addr) != 0)
			वापस -EIO;
	पूर्ण अन्यथा अणु
		अगर (netxen_get_flash_mac_addr(adapter, &mac_addr) != 0)
			वापस -EIO;
	पूर्ण

	p = (अचिन्हित अक्षर *)&mac_addr;
	क्रम (i = 0; i < 6; i++)
		netdev->dev_addr[i] = *(p + 5 - i);

	स_नकल(adapter->mac_addr, netdev->dev_addr, netdev->addr_len);

	/* set station address */

	अगर (!is_valid_ether_addr(netdev->dev_addr))
		dev_warn(&pdev->dev, "Bad MAC address %pM.\n", netdev->dev_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक netxen_nic_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(netdev);
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	अगर (netअगर_running(netdev)) अणु
		netअगर_device_detach(netdev);
		netxen_napi_disable(adapter);
	पूर्ण

	स_नकल(adapter->mac_addr, addr->sa_data, netdev->addr_len);
	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	adapter->macaddr_set(adapter, addr->sa_data);

	अगर (netअगर_running(netdev)) अणु
		netअगर_device_attach(netdev);
		netxen_napi_enable(adapter);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम netxen_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(dev);

	adapter->set_multi(dev);
पूर्ण

अटल netdev_features_t netxen_fix_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	अगर (!(features & NETIF_F_RXCSUM)) अणु
		netdev_info(dev, "disabling LRO as RXCSUM is off\n");

		features &= ~NETIF_F_LRO;
	पूर्ण

	वापस features;
पूर्ण

अटल पूर्णांक netxen_set_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(dev);
	पूर्णांक hw_lro;

	अगर (!((dev->features ^ features) & NETIF_F_LRO))
		वापस 0;

	hw_lro = (features & NETIF_F_LRO) ? NETXEN_NIC_LRO_ENABLED
	         : NETXEN_NIC_LRO_DISABLED;

	अगर (netxen_config_hw_lro(adapter, hw_lro))
		वापस -EIO;

	अगर (!(features & NETIF_F_LRO) && netxen_send_lro_cleanup(adapter))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops netxen_netdev_ops = अणु
	.nकरो_खोलो	   = netxen_nic_खोलो,
	.nकरो_stop	   = netxen_nic_बंद,
	.nकरो_start_xmit    = netxen_nic_xmit_frame,
	.nकरो_get_stats64   = netxen_nic_get_stats,
	.nकरो_validate_addr = eth_validate_addr,
	.nकरो_set_rx_mode   = netxen_set_multicast_list,
	.nकरो_set_mac_address    = netxen_nic_set_mac,
	.nकरो_change_mtu	   = netxen_nic_change_mtu,
	.nकरो_tx_समयout	   = netxen_tx_समयout,
	.nकरो_fix_features = netxen_fix_features,
	.nकरो_set_features = netxen_set_features,
पूर्ण;

अटल अंतरभूत व्योम netxen_set_पूर्णांकerrupt_mode(काष्ठा netxen_adapter *adapter,
					     u32 mode)
अणु
	NXWR32(adapter, NETXEN_INTR_MODE_REG, mode);
पूर्ण

अटल अंतरभूत u32 netxen_get_पूर्णांकerrupt_mode(काष्ठा netxen_adapter *adapter)
अणु
	वापस NXRD32(adapter, NETXEN_INTR_MODE_REG);
पूर्ण

अटल व्योम
netxen_initialize_पूर्णांकerrupt_रेजिस्टरs(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा netxen_legacy_पूर्णांकr_set *legacy_पूर्णांकrp;
	u32 tgt_status_reg, पूर्णांक_state_reg;

	अगर (adapter->ahw.revision_id >= NX_P3_B0)
		legacy_पूर्णांकrp = &legacy_पूर्णांकr[adapter->ahw.pci_func];
	अन्यथा
		legacy_पूर्णांकrp = &legacy_पूर्णांकr[0];

	tgt_status_reg = legacy_पूर्णांकrp->tgt_status_reg;
	पूर्णांक_state_reg = ISR_INT_STATE_REG;

	adapter->पूर्णांक_vec_bit = legacy_पूर्णांकrp->पूर्णांक_vec_bit;
	adapter->tgt_status_reg = netxen_get_ioaddr(adapter, tgt_status_reg);
	adapter->tgt_mask_reg = netxen_get_ioaddr(adapter,
						  legacy_पूर्णांकrp->tgt_mask_reg);
	adapter->pci_पूर्णांक_reg = netxen_get_ioaddr(adapter,
						 legacy_पूर्णांकrp->pci_पूर्णांक_reg);
	adapter->isr_पूर्णांक_vec = netxen_get_ioaddr(adapter, ISR_INT_VECTOR);

	अगर (adapter->ahw.revision_id >= NX_P3_B1)
		adapter->crb_पूर्णांक_state_reg = netxen_get_ioaddr(adapter,
							       पूर्णांक_state_reg);
	अन्यथा
		adapter->crb_पूर्णांक_state_reg = netxen_get_ioaddr(adapter,
							       CRB_INT_VECTOR);
पूर्ण

अटल पूर्णांक netxen_setup_msi_पूर्णांकerrupts(काष्ठा netxen_adapter *adapter,
				       पूर्णांक num_msix)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	u32 value;
	पूर्णांक err;

	अगर (adapter->msix_supported) अणु
		netxen_init_msix_entries(adapter, num_msix);
		err = pci_enable_msix_range(pdev, adapter->msix_entries,
					    num_msix, num_msix);
		अगर (err > 0) अणु
			adapter->flags |= NETXEN_NIC_MSIX_ENABLED;
			netxen_set_msix_bit(pdev, 1);

			अगर (adapter->rss_supported)
				adapter->max_sds_rings = num_msix;

			dev_info(&pdev->dev, "using msi-x interrupts\n");
			वापस 0;
		पूर्ण
		/* fall through क्रम msi */
	पूर्ण

	अगर (use_msi && !pci_enable_msi(pdev)) अणु
		value = msi_tgt_status[adapter->ahw.pci_func];
		adapter->flags |= NETXEN_NIC_MSI_ENABLED;
		adapter->tgt_status_reg = netxen_get_ioaddr(adapter, value);
		adapter->msix_entries[0].vector = pdev->irq;
		dev_info(&pdev->dev, "using msi interrupts\n");
		वापस 0;
	पूर्ण

	dev_err(&pdev->dev, "Failed to acquire MSI-X/MSI interrupt vector\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक netxen_setup_पूर्णांकr(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक num_msix;

	अगर (adapter->rss_supported)
		num_msix = (num_online_cpus() >= MSIX_ENTRIES_PER_ADAPTER) ?
			    MSIX_ENTRIES_PER_ADAPTER : 2;
	अन्यथा
		num_msix = 1;

	adapter->max_sds_rings = 1;
	adapter->flags &= ~(NETXEN_NIC_MSI_ENABLED | NETXEN_NIC_MSIX_ENABLED);

	netxen_initialize_पूर्णांकerrupt_रेजिस्टरs(adapter);
	netxen_set_msix_bit(pdev, 0);

	अगर (adapter->portnum == 0) अणु
		अगर (!netxen_setup_msi_पूर्णांकerrupts(adapter, num_msix))
			netxen_set_पूर्णांकerrupt_mode(adapter, NETXEN_MSI_MODE);
		अन्यथा
			netxen_set_पूर्णांकerrupt_mode(adapter, NETXEN_INTX_MODE);
	पूर्ण अन्यथा अणु
		अगर (netxen_get_पूर्णांकerrupt_mode(adapter) == NETXEN_MSI_MODE &&
		    netxen_setup_msi_पूर्णांकerrupts(adapter, num_msix)) अणु
			dev_err(&pdev->dev, "Co-existence of MSI-X/MSI and INTx interrupts is not supported\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	अगर (!NETXEN_IS_MSI_FAMILY(adapter)) अणु
		adapter->msix_entries[0].vector = pdev->irq;
		dev_info(&pdev->dev, "using legacy interrupts\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
netxen_tearकरोwn_पूर्णांकr(काष्ठा netxen_adapter *adapter)
अणु
	अगर (adapter->flags & NETXEN_NIC_MSIX_ENABLED)
		pci_disable_msix(adapter->pdev);
	अगर (adapter->flags & NETXEN_NIC_MSI_ENABLED)
		pci_disable_msi(adapter->pdev);
पूर्ण

अटल व्योम
netxen_cleanup_pci_map(काष्ठा netxen_adapter *adapter)
अणु
	अगर (adapter->ahw.db_base != शून्य)
		iounmap(adapter->ahw.db_base);
	अगर (adapter->ahw.pci_base0 != शून्य)
		iounmap(adapter->ahw.pci_base0);
	अगर (adapter->ahw.pci_base1 != शून्य)
		iounmap(adapter->ahw.pci_base1);
	अगर (adapter->ahw.pci_base2 != शून्य)
		iounmap(adapter->ahw.pci_base2);
पूर्ण

अटल पूर्णांक
netxen_setup_pci_map(काष्ठा netxen_adapter *adapter)
अणु
	व्योम __iomem *db_ptr = शून्य;

	resource_माप_प्रकार mem_base, db_base;
	अचिन्हित दीर्घ mem_len, db_len = 0;

	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक pci_func = adapter->ahw.pci_func;
	काष्ठा netxen_hardware_context *ahw = &adapter->ahw;

	पूर्णांक err = 0;

	/*
	 * Set the CRB winकरोw to invalid. If any रेजिस्टर in winकरोw 0 is
	 * accessed it should set the winकरोw to 0 and then reset it to 1.
	 */
	adapter->ahw.crb_win = -1;
	adapter->ahw.ocm_win = -1;

	/* remap phys address */
	mem_base = pci_resource_start(pdev, 0);	/* 0 is क्रम BAR 0 */
	mem_len = pci_resource_len(pdev, 0);

	/* 128 Meg of memory */
	अगर (mem_len == NETXEN_PCI_128MB_SIZE) अणु

		ahw->pci_base0 = ioremap(mem_base, FIRST_PAGE_GROUP_SIZE);
		ahw->pci_base1 = ioremap(mem_base + SECOND_PAGE_GROUP_START,
				SECOND_PAGE_GROUP_SIZE);
		ahw->pci_base2 = ioremap(mem_base + THIRD_PAGE_GROUP_START,
				THIRD_PAGE_GROUP_SIZE);
		अगर (ahw->pci_base0 == शून्य || ahw->pci_base1 == शून्य ||
						ahw->pci_base2 == शून्य) अणु
			dev_err(&pdev->dev, "failed to map PCI bar 0\n");
			err = -EIO;
			जाओ err_out;
		पूर्ण

		ahw->pci_len0 = FIRST_PAGE_GROUP_SIZE;

	पूर्ण अन्यथा अगर (mem_len == NETXEN_PCI_32MB_SIZE) अणु

		ahw->pci_base1 = ioremap(mem_base, SECOND_PAGE_GROUP_SIZE);
		ahw->pci_base2 = ioremap(mem_base + THIRD_PAGE_GROUP_START -
			SECOND_PAGE_GROUP_START, THIRD_PAGE_GROUP_SIZE);
		अगर (ahw->pci_base1 == शून्य || ahw->pci_base2 == शून्य) अणु
			dev_err(&pdev->dev, "failed to map PCI bar 0\n");
			err = -EIO;
			जाओ err_out;
		पूर्ण

	पूर्ण अन्यथा अगर (mem_len == NETXEN_PCI_2MB_SIZE) अणु

		ahw->pci_base0 = pci_ioremap_bar(pdev, 0);
		अगर (ahw->pci_base0 == शून्य) अणु
			dev_err(&pdev->dev, "failed to map PCI bar 0\n");
			वापस -EIO;
		पूर्ण
		ahw->pci_len0 = mem_len;
	पूर्ण अन्यथा अणु
		वापस -EIO;
	पूर्ण

	netxen_setup_hwops(adapter);

	dev_info(&pdev->dev, "%dMB memory map\n", (पूर्णांक)(mem_len>>20));

	अगर (NX_IS_REVISION_P3P(adapter->ahw.revision_id)) अणु
		adapter->ahw.ocm_win_crb = netxen_get_ioaddr(adapter,
			NETXEN_PCIX_PS_REG(PCIX_OCM_WINDOW_REG(pci_func)));

	पूर्ण अन्यथा अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id)) अणु
		adapter->ahw.ocm_win_crb = netxen_get_ioaddr(adapter,
			NETXEN_PCIX_PS_REG(PCIE_MN_WINDOW_REG(pci_func)));
	पूर्ण

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		जाओ skip_करोorbell;

	db_base = pci_resource_start(pdev, 4);	/* करोorbell is on bar 4 */
	db_len = pci_resource_len(pdev, 4);

	अगर (db_len == 0) अणु
		prपूर्णांकk(KERN_ERR "%s: doorbell is disabled\n",
				netxen_nic_driver_name);
		err = -EIO;
		जाओ err_out;
	पूर्ण

	db_ptr = ioremap(db_base, NETXEN_DB_MAPSIZE_BYTES);
	अगर (!db_ptr) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed to allocate doorbell map.",
				netxen_nic_driver_name);
		err = -EIO;
		जाओ err_out;
	पूर्ण

skip_करोorbell:
	adapter->ahw.db_base = db_ptr;
	adapter->ahw.db_len = db_len;
	वापस 0;

err_out:
	netxen_cleanup_pci_map(adapter);
	वापस err;
पूर्ण

अटल व्योम
netxen_check_options(काष्ठा netxen_adapter *adapter)
अणु
	u32 fw_major, fw_minor, fw_build, prev_fw_version;
	अक्षर brd_name[NETXEN_MAX_SHORT_NAME];
	अक्षर serial_num[32];
	पूर्णांक i, offset, val, err;
	__le32 *ptr32;
	काष्ठा pci_dev *pdev = adapter->pdev;

	adapter->driver_mismatch = 0;

	ptr32 = (__le32 *)&serial_num;
	offset = NX_FW_SERIAL_NUM_OFFSET;
	क्रम (i = 0; i < 8; i++) अणु
		err = netxen_rom_fast_पढ़ो(adapter, offset, &val);
		अगर (err) अणु
			dev_err(&pdev->dev, "error reading board info\n");
			adapter->driver_mismatch = 1;
			वापस;
		पूर्ण
		ptr32[i] = cpu_to_le32(val);
		offset += माप(u32);
	पूर्ण

	fw_major = NXRD32(adapter, NETXEN_FW_VERSION_MAJOR);
	fw_minor = NXRD32(adapter, NETXEN_FW_VERSION_MINOR);
	fw_build = NXRD32(adapter, NETXEN_FW_VERSION_SUB);
	prev_fw_version = adapter->fw_version;
	adapter->fw_version = NETXEN_VERSION_CODE(fw_major, fw_minor, fw_build);

	/* Get FW Mini Coredump ढाँचा and store it */
	 अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id)) अणु
		अगर (adapter->mdump.md_ढाँचा == शून्य ||
				adapter->fw_version > prev_fw_version) अणु
			kमुक्त(adapter->mdump.md_ढाँचा);
			adapter->mdump.md_ढाँचा = शून्य;
			err = netxen_setup_minidump(adapter);
			अगर (err)
				dev_err(&adapter->pdev->dev,
				"Failed to setup minidump rcode = %d\n", err);
		पूर्ण
	पूर्ण

	अगर (adapter->portnum == 0) अणु
		अगर (netxen_nic_get_brd_name_by_type(adapter->ahw.board_type,
						    brd_name))
			म_नकल(serial_num, "Unknown");

		pr_info("%s: %s Board S/N %s  Chip rev 0x%x\n",
				module_name(THIS_MODULE),
				brd_name, serial_num, adapter->ahw.revision_id);
	पूर्ण

	अगर (adapter->fw_version < NETXEN_VERSION_CODE(3, 4, 216)) अणु
		adapter->driver_mismatch = 1;
		dev_warn(&pdev->dev, "firmware version %d.%d.%d unsupported\n",
				fw_major, fw_minor, fw_build);
		वापस;
	पूर्ण

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id)) अणु
		i = NXRD32(adapter, NETXEN_SRE_MISC);
		adapter->ahw.cut_through = (i & 0x8000) ? 1 : 0;
	पूर्ण

	dev_info(&pdev->dev, "Driver v%s, firmware v%d.%d.%d [%s]\n",
		 NETXEN_NIC_LINUX_VERSIONID, fw_major, fw_minor, fw_build,
		 adapter->ahw.cut_through ? "cut-through" : "legacy");

	अगर (adapter->fw_version >= NETXEN_VERSION_CODE(4, 0, 222))
		adapter->capabilities = NXRD32(adapter, CRB_FW_CAPABILITIES_1);

	अगर (adapter->ahw.port_type == NETXEN_NIC_XGBE) अणु
		adapter->num_rxd = DEFAULT_RCV_DESCRIPTORS_10G;
		adapter->num_jumbo_rxd = MAX_JUMBO_RCV_DESCRIPTORS_10G;
	पूर्ण अन्यथा अगर (adapter->ahw.port_type == NETXEN_NIC_GBE) अणु
		adapter->num_rxd = DEFAULT_RCV_DESCRIPTORS_1G;
		adapter->num_jumbo_rxd = MAX_JUMBO_RCV_DESCRIPTORS_1G;
	पूर्ण

	adapter->msix_supported = 0;
	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id)) अणु
		adapter->msix_supported = !!use_msi_x;
		adapter->rss_supported = !!use_msi_x;
	पूर्ण अन्यथा अणु
		u32 flashed_ver = 0;
		netxen_rom_fast_पढ़ो(adapter,
				NX_FW_VERSION_OFFSET, (पूर्णांक *)&flashed_ver);
		flashed_ver = NETXEN_DECODE_VERSION(flashed_ver);

		अगर (flashed_ver >= NETXEN_VERSION_CODE(3, 4, 336)) अणु
			चयन (adapter->ahw.board_type) अणु
			हाल NETXEN_BRDTYPE_P2_SB31_10G:
			हाल NETXEN_BRDTYPE_P2_SB31_10G_CX4:
				adapter->msix_supported = !!use_msi_x;
				adapter->rss_supported = !!use_msi_x;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	adapter->num_txd = MAX_CMD_DESCRIPTORS;

	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id)) अणु
		adapter->num_lro_rxd = MAX_LRO_RCV_DESCRIPTORS;
		adapter->max_rds_rings = 3;
	पूर्ण अन्यथा अणु
		adapter->num_lro_rxd = 0;
		adapter->max_rds_rings = 2;
	पूर्ण
पूर्ण

अटल पूर्णांक
netxen_start_firmware(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक val, err, first_boot;
	काष्ठा pci_dev *pdev = adapter->pdev;

	/* required क्रम NX2031 dummy dma */
	err = nx_set_dma_mask(adapter);
	अगर (err)
		वापस err;

	err = netxen_can_start_firmware(adapter);

	अगर (err < 0)
		वापस err;

	अगर (!err)
		जाओ रुको_init;

	first_boot = NXRD32(adapter, NETXEN_CAM_RAM(0x1fc));

	err = netxen_check_hw_init(adapter, first_boot);
	अगर (err) अणु
		dev_err(&pdev->dev, "error in init HW init sequence\n");
		वापस err;
	पूर्ण

	netxen_request_firmware(adapter);

	err = netxen_need_fw_reset(adapter);
	अगर (err < 0)
		जाओ err_out;
	अगर (err == 0)
		जाओ pcie_strap_init;

	अगर (first_boot != 0x55555555) अणु
		NXWR32(adapter, CRB_CMDPEG_STATE, 0);
		netxen_pinit_from_rom(adapter);
		msleep(1);
	पूर्ण

	NXWR32(adapter, CRB_DMA_SHIFT, 0x55555555);
	NXWR32(adapter, NETXEN_PEG_HALT_STATUS1, 0);
	NXWR32(adapter, NETXEN_PEG_HALT_STATUS2, 0);

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		netxen_set_port_mode(adapter);

	err = netxen_load_firmware(adapter);
	अगर (err)
		जाओ err_out;

	netxen_release_firmware(adapter);

	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id)) अणु

		/* Initialize multicast addr pool owners */
		val = 0x7654;
		अगर (adapter->ahw.port_type == NETXEN_NIC_XGBE)
			val |= 0x0f000000;
		NXWR32(adapter, NETXEN_MAC_ADDR_CNTL_REG, val);

	पूर्ण

	err = netxen_init_dummy_dma(adapter);
	अगर (err)
		जाओ err_out;

	/*
	 * Tell the hardware our version number.
	 */
	val = (_NETXEN_NIC_LINUX_MAJOR << 16)
		| ((_NETXEN_NIC_LINUX_MINOR << 8))
		| (_NETXEN_NIC_LINUX_SUBVERSION);
	NXWR32(adapter, CRB_DRIVER_VERSION, val);

pcie_strap_init:
	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		netxen_pcie_strap_init(adapter);

रुको_init:
	/* Handshake with the card beक्रमe we रेजिस्टर the devices. */
	err = netxen_phantom_init(adapter, NETXEN_NIC_PEG_TUNE);
	अगर (err) अणु
		netxen_मुक्त_dummy_dma(adapter);
		जाओ err_out;
	पूर्ण

	NXWR32(adapter, NX_CRB_DEV_STATE, NX_DEV_READY);

	nx_update_dma_mask(adapter);

	netxen_check_options(adapter);

	adapter->need_fw_reset = 0;

	/* fall through and release firmware */

err_out:
	netxen_release_firmware(adapter);
	वापस err;
पूर्ण

अटल पूर्णांक
netxen_nic_request_irq(काष्ठा netxen_adapter *adapter)
अणु
	irq_handler_t handler;
	काष्ठा nx_host_sds_ring *sds_ring;
	पूर्णांक err, ring;

	अचिन्हित दीर्घ flags = 0;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा netxen_recv_context *recv_ctx = &adapter->recv_ctx;

	अगर (adapter->flags & NETXEN_NIC_MSIX_ENABLED)
		handler = netxen_msix_पूर्णांकr;
	अन्यथा अगर (adapter->flags & NETXEN_NIC_MSI_ENABLED)
		handler = netxen_msi_पूर्णांकr;
	अन्यथा अणु
		flags |= IRQF_SHARED;
		handler = netxen_पूर्णांकr;
	पूर्ण
	adapter->irq = netdev->irq;

	क्रम (ring = 0; ring < adapter->max_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];
		प्र_लिखो(sds_ring->name, "%s[%d]", netdev->name, ring);
		err = request_irq(sds_ring->irq, handler,
				  flags, sds_ring->name, sds_ring);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
netxen_nic_मुक्त_irq(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक ring;
	काष्ठा nx_host_sds_ring *sds_ring;

	काष्ठा netxen_recv_context *recv_ctx = &adapter->recv_ctx;

	क्रम (ring = 0; ring < adapter->max_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];
		मुक्त_irq(sds_ring->irq, sds_ring);
	पूर्ण
पूर्ण

अटल व्योम
netxen_nic_init_coalesce_शेषs(काष्ठा netxen_adapter *adapter)
अणु
	adapter->coal.flags = NETXEN_NIC_INTR_DEFAULT;
	adapter->coal.normal.data.rx_समय_us =
		NETXEN_DEFAULT_INTR_COALESCE_RX_TIME_US;
	adapter->coal.normal.data.rx_packets =
		NETXEN_DEFAULT_INTR_COALESCE_RX_PACKETS;
	adapter->coal.normal.data.tx_समय_us =
		NETXEN_DEFAULT_INTR_COALESCE_TX_TIME_US;
	adapter->coal.normal.data.tx_packets =
		NETXEN_DEFAULT_INTR_COALESCE_TX_PACKETS;
पूर्ण

/* with rtnl_lock */
अटल पूर्णांक
__netxen_nic_up(काष्ठा netxen_adapter *adapter, काष्ठा net_device *netdev)
अणु
	पूर्णांक err;

	अगर (adapter->is_up != NETXEN_ADAPTER_UP_MAGIC)
		वापस -EIO;

	err = adapter->init_port(adapter, adapter->physical_port);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed to initialize port %d\n",
				netxen_nic_driver_name, adapter->portnum);
		वापस err;
	पूर्ण
	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		adapter->macaddr_set(adapter, adapter->mac_addr);

	adapter->set_multi(netdev);
	adapter->set_mtu(adapter, netdev->mtu);

	adapter->ahw.linkup = 0;

	अगर (adapter->max_sds_rings > 1)
		netxen_config_rss(adapter, 1);

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		netxen_config_पूर्णांकr_coalesce(adapter);

	अगर (netdev->features & NETIF_F_LRO)
		netxen_config_hw_lro(adapter, NETXEN_NIC_LRO_ENABLED);

	netxen_napi_enable(adapter);

	अगर (adapter->capabilities & NX_FW_CAPABILITY_LINK_NOTIFICATION)
		netxen_linkevent_request(adapter, 1);
	अन्यथा
		netxen_nic_set_link_parameters(adapter);

	set_bit(__NX_DEV_UP, &adapter->state);
	वापस 0;
पूर्ण

/* Usage: During resume and firmware recovery module.*/

अटल अंतरभूत पूर्णांक
netxen_nic_up(काष्ठा netxen_adapter *adapter, काष्ठा net_device *netdev)
अणु
	पूर्णांक err = 0;

	rtnl_lock();
	अगर (netअगर_running(netdev))
		err = __netxen_nic_up(adapter, netdev);
	rtnl_unlock();

	वापस err;
पूर्ण

/* with rtnl_lock */
अटल व्योम
__netxen_nic_करोwn(काष्ठा netxen_adapter *adapter, काष्ठा net_device *netdev)
अणु
	अगर (adapter->is_up != NETXEN_ADAPTER_UP_MAGIC)
		वापस;

	अगर (!test_and_clear_bit(__NX_DEV_UP, &adapter->state))
		वापस;

	smp_mb();
	netअगर_carrier_off(netdev);
	netअगर_tx_disable(netdev);

	अगर (adapter->capabilities & NX_FW_CAPABILITY_LINK_NOTIFICATION)
		netxen_linkevent_request(adapter, 0);

	अगर (adapter->stop_port)
		adapter->stop_port(adapter);

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		netxen_p3_मुक्त_mac_list(adapter);

	adapter->set_promisc(adapter, NETXEN_NIU_NON_PROMISC_MODE);

	netxen_napi_disable(adapter);

	netxen_release_tx_buffers(adapter);
पूर्ण

/* Usage: During suspend and firmware recovery module */

अटल अंतरभूत व्योम
netxen_nic_करोwn(काष्ठा netxen_adapter *adapter, काष्ठा net_device *netdev)
अणु
	rtnl_lock();
	अगर (netअगर_running(netdev))
		__netxen_nic_करोwn(adapter, netdev);
	rtnl_unlock();

पूर्ण

अटल पूर्णांक
netxen_nic_attach(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक err, ring;
	काष्ठा nx_host_rds_ring *rds_ring;
	काष्ठा nx_host_tx_ring *tx_ring;
	u32 capab2;

	अगर (adapter->is_up == NETXEN_ADAPTER_UP_MAGIC)
		वापस 0;

	err = netxen_init_firmware(adapter);
	अगर (err)
		वापस err;

	adapter->flags &= ~NETXEN_FW_MSS_CAP;
	अगर (adapter->capabilities & NX_FW_CAPABILITY_MORE_CAPS) अणु
		capab2 = NXRD32(adapter, CRB_FW_CAPABILITIES_2);
		अगर (capab2 & NX_FW_CAPABILITY_2_LRO_MAX_TCP_SEG)
			adapter->flags |= NETXEN_FW_MSS_CAP;
	पूर्ण

	err = netxen_napi_add(adapter, netdev);
	अगर (err)
		वापस err;

	err = netxen_alloc_sw_resources(adapter);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Error in setting sw resources\n",
				netdev->name);
		वापस err;
	पूर्ण

	err = netxen_alloc_hw_resources(adapter);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Error in setting hw resources\n",
				netdev->name);
		जाओ err_out_मुक्त_sw;
	पूर्ण

	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id)) अणु
		tx_ring = adapter->tx_ring;
		tx_ring->crb_cmd_producer = netxen_get_ioaddr(adapter,
				crb_cmd_producer[adapter->portnum]);
		tx_ring->crb_cmd_consumer = netxen_get_ioaddr(adapter,
				crb_cmd_consumer[adapter->portnum]);

		tx_ring->producer = 0;
		tx_ring->sw_consumer = 0;

		netxen_nic_update_cmd_producer(adapter, tx_ring);
		netxen_nic_update_cmd_consumer(adapter, tx_ring);
	पूर्ण

	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &adapter->recv_ctx.rds_rings[ring];
		netxen_post_rx_buffers(adapter, ring, rds_ring);
	पूर्ण

	err = netxen_nic_request_irq(adapter);
	अगर (err) अणु
		dev_err(&pdev->dev, "%s: failed to setup interrupt\n",
				netdev->name);
		जाओ err_out_मुक्त_rxbuf;
	पूर्ण

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		netxen_nic_init_coalesce_शेषs(adapter);

	netxen_create_sysfs_entries(adapter);

	adapter->is_up = NETXEN_ADAPTER_UP_MAGIC;
	वापस 0;

err_out_मुक्त_rxbuf:
	netxen_release_rx_buffers(adapter);
	netxen_मुक्त_hw_resources(adapter);
err_out_मुक्त_sw:
	netxen_मुक्त_sw_resources(adapter);
	वापस err;
पूर्ण

अटल व्योम
netxen_nic_detach(काष्ठा netxen_adapter *adapter)
अणु
	अगर (adapter->is_up != NETXEN_ADAPTER_UP_MAGIC)
		वापस;

	netxen_हटाओ_sysfs_entries(adapter);

	netxen_मुक्त_hw_resources(adapter);
	netxen_release_rx_buffers(adapter);
	netxen_nic_मुक्त_irq(adapter);
	netxen_napi_del(adapter);
	netxen_मुक्त_sw_resources(adapter);

	adapter->is_up = 0;
पूर्ण

पूर्णांक
netxen_nic_reset_context(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक err = 0;
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (test_and_set_bit(__NX_RESETTING, &adapter->state))
		वापस -EBUSY;

	अगर (adapter->is_up == NETXEN_ADAPTER_UP_MAGIC) अणु

		netअगर_device_detach(netdev);

		अगर (netअगर_running(netdev))
			__netxen_nic_करोwn(adapter, netdev);

		netxen_nic_detach(adapter);

		अगर (netअगर_running(netdev)) अणु
			err = netxen_nic_attach(adapter);
			अगर (!err)
				err = __netxen_nic_up(adapter, netdev);

			अगर (err)
				जाओ करोne;
		पूर्ण

		netअगर_device_attach(netdev);
	पूर्ण

करोne:
	clear_bit(__NX_RESETTING, &adapter->state);
	वापस err;
पूर्ण

अटल पूर्णांक
netxen_setup_netdev(काष्ठा netxen_adapter *adapter,
		काष्ठा net_device *netdev)
अणु
	पूर्णांक err = 0;
	काष्ठा pci_dev *pdev = adapter->pdev;

	adapter->mc_enabled = 0;
	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		adapter->max_mc_count = 38;
	अन्यथा
		adapter->max_mc_count = 16;

	netdev->netdev_ops	   = &netxen_netdev_ops;
	netdev->watchकरोg_समयo     = 5*HZ;

	netxen_nic_change_mtu(netdev, netdev->mtu);

	netdev->ethtool_ops = &netxen_nic_ethtool_ops;

	netdev->hw_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_TSO |
	                      NETIF_F_RXCSUM;

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		netdev->hw_features |= NETIF_F_IPV6_CSUM | NETIF_F_TSO6;

	netdev->vlan_features |= netdev->hw_features;

	अगर (adapter->pci_using_dac) अणु
		netdev->features |= NETIF_F_HIGHDMA;
		netdev->vlan_features |= NETIF_F_HIGHDMA;
	पूर्ण

	अगर (adapter->capabilities & NX_FW_CAPABILITY_FVLANTX)
		netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_TX;

	अगर (adapter->capabilities & NX_FW_CAPABILITY_HW_LRO)
		netdev->hw_features |= NETIF_F_LRO;

	netdev->features |= netdev->hw_features;

	netdev->irq = adapter->msix_entries[0].vector;

	INIT_WORK(&adapter->tx_समयout_task, netxen_tx_समयout_task);

	अगर (netxen_पढ़ो_mac_addr(adapter))
		dev_warn(&pdev->dev, "failed to read mac addr\n");

	netअगर_carrier_off(netdev);

	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register net device\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा NETXEN_ULA_ADAPTER_KEY		(0xdaddad01)
#घोषणा NETXEN_NON_ULA_ADAPTER_KEY	(0xdaddad00)

अटल व्योम netxen_पढ़ो_ula_info(काष्ठा netxen_adapter *adapter)
अणु
	u32 temp;

	/* Prपूर्णांक ULA info only once क्रम an adapter */
	अगर (adapter->portnum != 0)
		वापस;

	temp = NXRD32(adapter, NETXEN_ULA_KEY);
	चयन (temp) अणु
	हाल NETXEN_ULA_ADAPTER_KEY:
		dev_info(&adapter->pdev->dev, "ULA adapter");
		अवरोध;
	हाल NETXEN_NON_ULA_ADAPTER_KEY:
		dev_info(&adapter->pdev->dev, "non ULA adapter");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस;
पूर्ण

#अगर_घोषित CONFIG_PCIEAER
अटल व्योम netxen_mask_aer_correctable(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा pci_dev *root = pdev->bus->self;
	u32 aer_pos;

	/* root bus? */
	अगर (!root)
		वापस;

	अगर (adapter->ahw.board_type != NETXEN_BRDTYPE_P3_4_GB_MM &&
		adapter->ahw.board_type != NETXEN_BRDTYPE_P3_10G_TP)
		वापस;

	अगर (pci_pcie_type(root) != PCI_EXP_TYPE_ROOT_PORT)
		वापस;

	aer_pos = pci_find_ext_capability(root, PCI_EXT_CAP_ID_ERR);
	अगर (!aer_pos)
		वापस;

	pci_ग_लिखो_config_dword(root, aer_pos + PCI_ERR_COR_MASK, 0xffff);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
netxen_nic_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev = शून्य;
	काष्ठा netxen_adapter *adapter = शून्य;
	पूर्णांक i = 0, err;
	पूर्णांक pci_func_id = PCI_FUNC(pdev->devfn);
	uपूर्णांक8_t revision_id;
	u32 val;

	अगर (pdev->revision >= NX_P3_A0 && pdev->revision <= NX_P3_B1) अणु
		pr_warn("%s: chip revisions between 0x%x-0x%x will not be enabled\n",
			module_name(THIS_MODULE), NX_P3_A0, NX_P3_B1);
		वापस -ENODEV;
	पूर्ण

	अगर ((err = pci_enable_device(pdev)))
		वापस err;

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		err = -ENODEV;
		जाओ err_out_disable_pdev;
	पूर्ण

	अगर ((err = pci_request_regions(pdev, netxen_nic_driver_name)))
		जाओ err_out_disable_pdev;

	अगर (NX_IS_REVISION_P3(pdev->revision))
		pci_enable_pcie_error_reporting(pdev);

	pci_set_master(pdev);

	netdev = alloc_etherdev(माप(काष्ठा netxen_adapter));
	अगर(!netdev) अणु
		err = -ENOMEM;
		जाओ err_out_मुक्त_res;
	पूर्ण

	SET_NETDEV_DEV(netdev, &pdev->dev);

	adapter = netdev_priv(netdev);
	adapter->netdev  = netdev;
	adapter->pdev    = pdev;
	adapter->ahw.pci_func  = pci_func_id;

	revision_id = pdev->revision;
	adapter->ahw.revision_id = revision_id;

	rwlock_init(&adapter->ahw.crb_lock);
	spin_lock_init(&adapter->ahw.mem_lock);

	spin_lock_init(&adapter->tx_clean_lock);
	INIT_LIST_HEAD(&adapter->mac_list);
	INIT_LIST_HEAD(&adapter->ip_list);

	err = netxen_setup_pci_map(adapter);
	अगर (err)
		जाओ err_out_मुक्त_netdev;

	/* This will be reset क्रम mezz cards  */
	adapter->portnum = pci_func_id;

	err = netxen_nic_get_board_info(adapter);
	अगर (err) अणु
		dev_err(&pdev->dev, "Error getting board config info.\n");
		जाओ err_out_iounmap;
	पूर्ण

#अगर_घोषित CONFIG_PCIEAER
	netxen_mask_aer_correctable(adapter);
#पूर्ण_अगर

	/* Mezz cards have PCI function 0,2,3 enabled */
	चयन (adapter->ahw.board_type) अणु
	हाल NETXEN_BRDTYPE_P2_SB31_10G_IMEZ:
	हाल NETXEN_BRDTYPE_P2_SB31_10G_HMEZ:
		अगर (pci_func_id >= 2)
			adapter->portnum = pci_func_id - 2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	err = netxen_check_flash_fw_compatibility(adapter);
	अगर (err)
		जाओ err_out_iounmap;

	अगर (adapter->portnum == 0) अणु
		val = NXRD32(adapter, NX_CRB_DEV_REF_COUNT);
		अगर (val != 0xffffffff && val != 0) अणु
			NXWR32(adapter, NX_CRB_DEV_REF_COUNT, 0);
			adapter->need_fw_reset = 1;
		पूर्ण
	पूर्ण

	err = netxen_start_firmware(adapter);
	अगर (err)
		जाओ err_out_decr_ref;

	/*
	 * See अगर the firmware gave us a भव-physical port mapping.
	 */
	adapter->physical_port = adapter->portnum;
	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id)) अणु
		i = NXRD32(adapter, CRB_V2P(adapter->portnum));
		अगर (i != 0x55555555)
			adapter->physical_port = i;
	पूर्ण

	/* MTU range: 0 - 8000 (P2) or 9600 (P3) */
	netdev->min_mtu = 0;
	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		netdev->max_mtu = P3_MAX_MTU;
	अन्यथा
		netdev->max_mtu = P2_MAX_MTU;

	netxen_nic_clear_stats(adapter);

	err = netxen_setup_पूर्णांकr(adapter);

	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"Failed to setup interrupts, error = %d\n", err);
		जाओ err_out_disable_msi;
	पूर्ण

	netxen_पढ़ो_ula_info(adapter);

	err = netxen_setup_netdev(adapter, netdev);
	अगर (err)
		जाओ err_out_disable_msi;

	pci_set_drvdata(pdev, adapter);

	netxen_schedule_work(adapter, netxen_fw_poll_work, FW_POLL_DELAY);

	चयन (adapter->ahw.port_type) अणु
	हाल NETXEN_NIC_GBE:
		dev_info(&adapter->pdev->dev, "%s: GbE port initialized\n",
				adapter->netdev->name);
		अवरोध;
	हाल NETXEN_NIC_XGBE:
		dev_info(&adapter->pdev->dev, "%s: XGbE port initialized\n",
				adapter->netdev->name);
		अवरोध;
	पूर्ण

	netxen_create_diag_entries(adapter);

	वापस 0;

err_out_disable_msi:
	netxen_tearकरोwn_पूर्णांकr(adapter);

	netxen_मुक्त_dummy_dma(adapter);

err_out_decr_ref:
	nx_decr_dev_ref_cnt(adapter);

err_out_iounmap:
	netxen_cleanup_pci_map(adapter);

err_out_मुक्त_netdev:
	मुक्त_netdev(netdev);

err_out_मुक्त_res:
	अगर (NX_IS_REVISION_P3(pdev->revision))
		pci_disable_pcie_error_reporting(pdev);
	pci_release_regions(pdev);

err_out_disable_pdev:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

अटल
व्योम netxen_cleanup_minidump(काष्ठा netxen_adapter *adapter)
अणु
	kमुक्त(adapter->mdump.md_ढाँचा);
	adapter->mdump.md_ढाँचा = शून्य;

	अगर (adapter->mdump.md_capture_buff) अणु
		vमुक्त(adapter->mdump.md_capture_buff);
		adapter->mdump.md_capture_buff = शून्य;
	पूर्ण
पूर्ण

अटल व्योम netxen_nic_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा netxen_adapter *adapter;
	काष्ठा net_device *netdev;

	adapter = pci_get_drvdata(pdev);
	अगर (adapter == शून्य)
		वापस;

	netdev = adapter->netdev;

	netxen_cancel_fw_work(adapter);

	unरेजिस्टर_netdev(netdev);

	cancel_work_sync(&adapter->tx_समयout_task);

	netxen_मुक्त_ip_list(adapter, false);
	netxen_nic_detach(adapter);

	nx_decr_dev_ref_cnt(adapter);

	अगर (adapter->portnum == 0)
		netxen_मुक्त_dummy_dma(adapter);

	clear_bit(__NX_RESETTING, &adapter->state);

	netxen_tearकरोwn_पूर्णांकr(adapter);
	netxen_set_पूर्णांकerrupt_mode(adapter, 0);
	netxen_हटाओ_diag_entries(adapter);

	netxen_cleanup_pci_map(adapter);

	netxen_release_firmware(adapter);

	अगर (NX_IS_REVISION_P3(pdev->revision)) अणु
		netxen_cleanup_minidump(adapter);
		pci_disable_pcie_error_reporting(pdev);
	पूर्ण

	pci_release_regions(pdev);
	pci_disable_device(pdev);

	मुक्त_netdev(netdev);
पूर्ण

अटल व्योम netxen_nic_detach_func(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	netअगर_device_detach(netdev);

	netxen_cancel_fw_work(adapter);

	अगर (netअगर_running(netdev))
		netxen_nic_करोwn(adapter, netdev);

	cancel_work_sync(&adapter->tx_समयout_task);

	netxen_nic_detach(adapter);

	अगर (adapter->portnum == 0)
		netxen_मुक्त_dummy_dma(adapter);

	nx_decr_dev_ref_cnt(adapter);

	clear_bit(__NX_RESETTING, &adapter->state);
पूर्ण

अटल पूर्णांक netxen_nic_attach_late_func(काष्ठा pci_dev *pdev)
अणु
	काष्ठा netxen_adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err;

	pci_set_master(pdev);

	adapter->ahw.crb_win = -1;
	adapter->ahw.ocm_win = -1;

	err = netxen_start_firmware(adapter);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to start firmware\n");
		वापस err;
	पूर्ण

	अगर (netअगर_running(netdev)) अणु
		err = netxen_nic_attach(adapter);
		अगर (err)
			जाओ err_out;

		err = netxen_nic_up(adapter, netdev);
		अगर (err)
			जाओ err_out_detach;

		netxen_restore_indev_addr(netdev, NETDEV_UP);
	पूर्ण

	netअगर_device_attach(netdev);
	netxen_schedule_work(adapter, netxen_fw_poll_work, FW_POLL_DELAY);
	वापस 0;

err_out_detach:
	netxen_nic_detach(adapter);
err_out:
	nx_decr_dev_ref_cnt(adapter);
	वापस err;
पूर्ण

अटल पूर्णांक netxen_nic_attach_func(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक err;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;

	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);

	वापस netxen_nic_attach_late_func(pdev);
पूर्ण

अटल pci_ers_result_t netxen_io_error_detected(काष्ठा pci_dev *pdev,
						pci_channel_state_t state)
अणु
	काष्ठा netxen_adapter *adapter = pci_get_drvdata(pdev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	अगर (nx_dev_request_aer(adapter))
		वापस PCI_ERS_RESULT_RECOVERED;

	netxen_nic_detach_func(adapter);

	pci_disable_device(pdev);

	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

अटल pci_ers_result_t netxen_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक err = 0;

	err = netxen_nic_attach_func(pdev);

	वापस err ? PCI_ERS_RESULT_DISCONNECT : PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल व्योम netxen_nic_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा netxen_adapter *adapter = pci_get_drvdata(pdev);

	netxen_nic_detach_func(adapter);

	अगर (pci_save_state(pdev))
		वापस;

	अगर (netxen_nic_wol_supported(adapter)) अणु
		pci_enable_wake(pdev, PCI_D3cold, 1);
		pci_enable_wake(pdev, PCI_D3hot, 1);
	पूर्ण

	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक __maybe_unused
netxen_nic_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा netxen_adapter *adapter = dev_get_drvdata(dev_d);

	netxen_nic_detach_func(adapter);

	अगर (netxen_nic_wol_supported(adapter))
		device_wakeup_enable(dev_d);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused
netxen_nic_resume(काष्ठा device *dev_d)
अणु
	वापस netxen_nic_attach_late_func(to_pci_dev(dev_d));
पूर्ण

अटल पूर्णांक netxen_nic_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err = 0;

	अगर (adapter->driver_mismatch)
		वापस -EIO;

	err = netxen_nic_attach(adapter);
	अगर (err)
		वापस err;

	err = __netxen_nic_up(adapter, netdev);
	अगर (err)
		जाओ err_out;

	netअगर_start_queue(netdev);

	वापस 0;

err_out:
	netxen_nic_detach(adapter);
	वापस err;
पूर्ण

/*
 * netxen_nic_बंद - Disables a network पूर्णांकerface entry poपूर्णांक
 */
अटल पूर्णांक netxen_nic_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(netdev);

	__netxen_nic_करोwn(adapter, netdev);
	वापस 0;
पूर्ण

अटल व्योम
netxen_tso_check(काष्ठा net_device *netdev,
		काष्ठा nx_host_tx_ring *tx_ring,
		काष्ठा cmd_desc_type0 *first_desc,
		काष्ठा sk_buff *skb)
अणु
	u8 opcode = TX_ETHER_PKT;
	__be16 protocol = skb->protocol;
	u16 flags = 0, vid = 0;
	u32 producer;
	पूर्णांक copied, offset, copy_len, hdr_len = 0, tso = 0, vlan_oob = 0;
	काष्ठा cmd_desc_type0 *hwdesc;
	काष्ठा vlan_ethhdr *vh;

	अगर (protocol == cpu_to_be16(ETH_P_8021Q)) अणु

		vh = (काष्ठा vlan_ethhdr *)skb->data;
		protocol = vh->h_vlan_encapsulated_proto;
		flags = FLAGS_VLAN_TAGGED;

	पूर्ण अन्यथा अगर (skb_vlan_tag_present(skb)) अणु
		flags = FLAGS_VLAN_OOB;
		vid = skb_vlan_tag_get(skb);
		netxen_set_tx_vlan_tci(first_desc, vid);
		vlan_oob = 1;
	पूर्ण

	अगर ((netdev->features & (NETIF_F_TSO | NETIF_F_TSO6)) &&
			skb_shinfo(skb)->gso_size > 0) अणु

		hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);

		first_desc->mss = cpu_to_le16(skb_shinfo(skb)->gso_size);
		first_desc->total_hdr_length = hdr_len;
		अगर (vlan_oob) अणु
			first_desc->total_hdr_length += VLAN_HLEN;
			first_desc->tcp_hdr_offset = VLAN_HLEN;
			first_desc->ip_hdr_offset = VLAN_HLEN;
			/* Only in हाल of TSO on vlan device */
			flags |= FLAGS_VLAN_TAGGED;
		पूर्ण

		opcode = (protocol == cpu_to_be16(ETH_P_IPV6)) ?
				TX_TCP_LSO6 : TX_TCP_LSO;
		tso = 1;

	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		u8 l4proto;

		अगर (protocol == cpu_to_be16(ETH_P_IP)) अणु
			l4proto = ip_hdr(skb)->protocol;

			अगर (l4proto == IPPROTO_TCP)
				opcode = TX_TCP_PKT;
			अन्यथा अगर(l4proto == IPPROTO_UDP)
				opcode = TX_UDP_PKT;
		पूर्ण अन्यथा अगर (protocol == cpu_to_be16(ETH_P_IPV6)) अणु
			l4proto = ipv6_hdr(skb)->nexthdr;

			अगर (l4proto == IPPROTO_TCP)
				opcode = TX_TCPV6_PKT;
			अन्यथा अगर(l4proto == IPPROTO_UDP)
				opcode = TX_UDPV6_PKT;
		पूर्ण
	पूर्ण

	first_desc->tcp_hdr_offset += skb_transport_offset(skb);
	first_desc->ip_hdr_offset += skb_network_offset(skb);
	netxen_set_tx_flags_opcode(first_desc, flags, opcode);

	अगर (!tso)
		वापस;

	/* For LSO, we need to copy the MAC/IP/TCP headers पूर्णांकo
	 * the descriptor ring
	 */
	producer = tx_ring->producer;
	copied = 0;
	offset = 2;

	अगर (vlan_oob) अणु
		/* Create a TSO vlan header ढाँचा क्रम firmware */

		hwdesc = &tx_ring->desc_head[producer];
		tx_ring->cmd_buf_arr[producer].skb = शून्य;

		copy_len = min((पूर्णांक)माप(काष्ठा cmd_desc_type0) - offset,
				hdr_len + VLAN_HLEN);

		vh = (काष्ठा vlan_ethhdr *)((अक्षर *)hwdesc + 2);
		skb_copy_from_linear_data(skb, vh, 12);
		vh->h_vlan_proto = htons(ETH_P_8021Q);
		vh->h_vlan_TCI = htons(vid);
		skb_copy_from_linear_data_offset(skb, 12,
				(अक्षर *)vh + 16, copy_len - 16);

		copied = copy_len - VLAN_HLEN;
		offset = 0;

		producer = get_next_index(producer, tx_ring->num_desc);
	पूर्ण

	जबतक (copied < hdr_len) अणु

		copy_len = min((पूर्णांक)माप(काष्ठा cmd_desc_type0) - offset,
				(hdr_len - copied));

		hwdesc = &tx_ring->desc_head[producer];
		tx_ring->cmd_buf_arr[producer].skb = शून्य;

		skb_copy_from_linear_data_offset(skb, copied,
				 (अक्षर *)hwdesc + offset, copy_len);

		copied += copy_len;
		offset = 0;

		producer = get_next_index(producer, tx_ring->num_desc);
	पूर्ण

	tx_ring->producer = producer;
	barrier();
पूर्ण

अटल पूर्णांक
netxen_map_tx_skb(काष्ठा pci_dev *pdev,
		काष्ठा sk_buff *skb, काष्ठा netxen_cmd_buffer *pbuf)
अणु
	काष्ठा netxen_skb_frag *nf;
	skb_frag_t *frag;
	पूर्णांक i, nr_frags;
	dma_addr_t map;

	nr_frags = skb_shinfo(skb)->nr_frags;
	nf = &pbuf->frag_array[0];

	map = dma_map_single(&pdev->dev, skb->data, skb_headlen(skb),
			     DMA_TO_DEVICE);
	अगर (dma_mapping_error(&pdev->dev, map))
		जाओ out_err;

	nf->dma = map;
	nf->length = skb_headlen(skb);

	क्रम (i = 0; i < nr_frags; i++) अणु
		frag = &skb_shinfo(skb)->frags[i];
		nf = &pbuf->frag_array[i+1];

		map = skb_frag_dma_map(&pdev->dev, frag, 0, skb_frag_size(frag),
				       DMA_TO_DEVICE);
		अगर (dma_mapping_error(&pdev->dev, map))
			जाओ unwind;

		nf->dma = map;
		nf->length = skb_frag_size(frag);
	पूर्ण

	वापस 0;

unwind:
	जबतक (--i >= 0) अणु
		nf = &pbuf->frag_array[i+1];
		dma_unmap_page(&pdev->dev, nf->dma, nf->length, DMA_TO_DEVICE);
		nf->dma = 0ULL;
	पूर्ण

	nf = &pbuf->frag_array[0];
	dma_unmap_single(&pdev->dev, nf->dma, skb_headlen(skb), DMA_TO_DEVICE);
	nf->dma = 0ULL;

out_err:
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत व्योम
netxen_clear_cmddesc(u64 *desc)
अणु
	desc[0] = 0ULL;
	desc[2] = 0ULL;
पूर्ण

अटल netdev_tx_t
netxen_nic_xmit_frame(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(netdev);
	काष्ठा nx_host_tx_ring *tx_ring = adapter->tx_ring;
	काष्ठा netxen_cmd_buffer *pbuf;
	काष्ठा netxen_skb_frag *buffrag;
	काष्ठा cmd_desc_type0 *hwdesc, *first_desc;
	काष्ठा pci_dev *pdev;
	पूर्णांक i, k;
	पूर्णांक delta = 0;
	skb_frag_t *frag;

	u32 producer;
	पूर्णांक frag_count;
	u32 num_txd = tx_ring->num_desc;

	frag_count = skb_shinfo(skb)->nr_frags + 1;

	/* 14 frags supported क्रम normal packet and
	 * 32 frags supported क्रम TSO packet
	 */
	अगर (!skb_is_gso(skb) && frag_count > NETXEN_MAX_FRAGS_PER_TX) अणु

		क्रम (i = 0; i < (frag_count - NETXEN_MAX_FRAGS_PER_TX); i++) अणु
			frag = &skb_shinfo(skb)->frags[i];
			delta += skb_frag_size(frag);
		पूर्ण

		अगर (!__pskb_pull_tail(skb, delta))
			जाओ drop_packet;

		frag_count = 1 + skb_shinfo(skb)->nr_frags;
	पूर्ण

	अगर (unlikely(netxen_tx_avail(tx_ring) <= TX_STOP_THRESH)) अणु
		netअगर_stop_queue(netdev);
		smp_mb();
		अगर (netxen_tx_avail(tx_ring) > TX_STOP_THRESH)
			netअगर_start_queue(netdev);
		अन्यथा
			वापस NETDEV_TX_BUSY;
	पूर्ण

	producer = tx_ring->producer;
	pbuf = &tx_ring->cmd_buf_arr[producer];

	pdev = adapter->pdev;

	अगर (netxen_map_tx_skb(pdev, skb, pbuf))
		जाओ drop_packet;

	pbuf->skb = skb;
	pbuf->frag_count = frag_count;

	first_desc = hwdesc = &tx_ring->desc_head[producer];
	netxen_clear_cmddesc((u64 *)hwdesc);

	netxen_set_tx_frags_len(first_desc, frag_count, skb->len);
	netxen_set_tx_port(first_desc, adapter->portnum);

	क्रम (i = 0; i < frag_count; i++) अणु

		k = i % 4;

		अगर ((k == 0) && (i > 0)) अणु
			/* move to next desc.*/
			producer = get_next_index(producer, num_txd);
			hwdesc = &tx_ring->desc_head[producer];
			netxen_clear_cmddesc((u64 *)hwdesc);
			tx_ring->cmd_buf_arr[producer].skb = शून्य;
		पूर्ण

		buffrag = &pbuf->frag_array[i];

		hwdesc->buffer_length[k] = cpu_to_le16(buffrag->length);
		चयन (k) अणु
		हाल 0:
			hwdesc->addr_buffer1 = cpu_to_le64(buffrag->dma);
			अवरोध;
		हाल 1:
			hwdesc->addr_buffer2 = cpu_to_le64(buffrag->dma);
			अवरोध;
		हाल 2:
			hwdesc->addr_buffer3 = cpu_to_le64(buffrag->dma);
			अवरोध;
		हाल 3:
			hwdesc->addr_buffer4 = cpu_to_le64(buffrag->dma);
			अवरोध;
		पूर्ण
	पूर्ण

	tx_ring->producer = get_next_index(producer, num_txd);

	netxen_tso_check(netdev, tx_ring, first_desc, skb);

	adapter->stats.txbytes += skb->len;
	adapter->stats.xmitcalled++;

	netxen_nic_update_cmd_producer(adapter, tx_ring);

	वापस NETDEV_TX_OK;

drop_packet:
	adapter->stats.txdropped++;
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक netxen_nic_check_temp(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	uपूर्णांक32_t temp, temp_state, temp_val;
	पूर्णांक rv = 0;

	temp = NXRD32(adapter, CRB_TEMP_STATE);

	temp_state = nx_get_temp_state(temp);
	temp_val = nx_get_temp_val(temp);

	अगर (temp_state == NX_TEMP_PANIC) अणु
		prपूर्णांकk(KERN_ALERT
		       "%s: Device temperature %d degrees C exceeds"
		       " maximum allowed. Hardware has been shut down.\n",
		       netdev->name, temp_val);
		rv = 1;
	पूर्ण अन्यथा अगर (temp_state == NX_TEMP_WARN) अणु
		अगर (adapter->temp == NX_TEMP_NORMAL) अणु
			prपूर्णांकk(KERN_ALERT
			       "%s: Device temperature %d degrees C "
			       "exceeds operating range."
			       " Immediate action needed.\n",
			       netdev->name, temp_val);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (adapter->temp == NX_TEMP_WARN) अणु
			prपूर्णांकk(KERN_INFO
			       "%s: Device temperature is now %d degrees C"
			       " in normal range.\n", netdev->name,
			       temp_val);
		पूर्ण
	पूर्ण
	adapter->temp = temp_state;
	वापस rv;
पूर्ण

व्योम netxen_advert_link_change(काष्ठा netxen_adapter *adapter, पूर्णांक linkup)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (adapter->ahw.linkup && !linkup) अणु
		prपूर्णांकk(KERN_INFO "%s: %s NIC Link is down\n",
		       netxen_nic_driver_name, netdev->name);
		adapter->ahw.linkup = 0;
		अगर (netअगर_running(netdev)) अणु
			netअगर_carrier_off(netdev);
			netअगर_stop_queue(netdev);
		पूर्ण
		adapter->link_changed = !adapter->has_link_events;
	पूर्ण अन्यथा अगर (!adapter->ahw.linkup && linkup) अणु
		prपूर्णांकk(KERN_INFO "%s: %s NIC Link is up\n",
		       netxen_nic_driver_name, netdev->name);
		adapter->ahw.linkup = 1;
		अगर (netअगर_running(netdev)) अणु
			netअगर_carrier_on(netdev);
			netअगर_wake_queue(netdev);
		पूर्ण
		adapter->link_changed = !adapter->has_link_events;
	पूर्ण
पूर्ण

अटल व्योम netxen_nic_handle_phy_पूर्णांकr(काष्ठा netxen_adapter *adapter)
अणु
	u32 val, port, linkup;

	port = adapter->physical_port;

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id)) अणु
		val = NXRD32(adapter, CRB_XG_STATE_P3);
		val = XG_LINK_STATE_P3(adapter->ahw.pci_func, val);
		linkup = (val == XG_LINK_UP_P3);
	पूर्ण अन्यथा अणु
		val = NXRD32(adapter, CRB_XG_STATE);
		val = (val >> port*8) & 0xff;
		linkup = (val == XG_LINK_UP);
	पूर्ण

	netxen_advert_link_change(adapter, linkup);
पूर्ण

अटल व्योम netxen_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(netdev);

	अगर (test_bit(__NX_RESETTING, &adapter->state))
		वापस;

	dev_err(&netdev->dev, "transmit timeout, resetting.\n");
	schedule_work(&adapter->tx_समयout_task);
पूर्ण

अटल व्योम netxen_tx_समयout_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा netxen_adapter *adapter =
		container_of(work, काष्ठा netxen_adapter, tx_समयout_task);

	अगर (!netअगर_running(adapter->netdev))
		वापस;

	अगर (test_and_set_bit(__NX_RESETTING, &adapter->state))
		वापस;

	अगर (++adapter->tx_समयo_cnt >= NX_MAX_TX_TIMEOUTS)
		जाओ request_reset;

	rtnl_lock();
	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id)) अणु
		/* try to scrub पूर्णांकerrupt */
		netxen_napi_disable(adapter);

		netxen_napi_enable(adapter);

		netअगर_wake_queue(adapter->netdev);

		clear_bit(__NX_RESETTING, &adapter->state);
	पूर्ण अन्यथा अणु
		clear_bit(__NX_RESETTING, &adapter->state);
		अगर (netxen_nic_reset_context(adapter)) अणु
			rtnl_unlock();
			जाओ request_reset;
		पूर्ण
	पूर्ण
	netअगर_trans_update(adapter->netdev);
	rtnl_unlock();
	वापस;

request_reset:
	adapter->need_fw_reset = 1;
	clear_bit(__NX_RESETTING, &adapter->state);
पूर्ण

अटल व्योम netxen_nic_get_stats(काष्ठा net_device *netdev,
				 काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(netdev);

	stats->rx_packets = adapter->stats.rx_pkts + adapter->stats.lro_pkts;
	stats->tx_packets = adapter->stats.xmitfinished;
	stats->rx_bytes = adapter->stats.rxbytes;
	stats->tx_bytes = adapter->stats.txbytes;
	stats->rx_dropped = adapter->stats.rxdropped;
	stats->tx_dropped = adapter->stats.txdropped;
पूर्ण

अटल irqवापस_t netxen_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा nx_host_sds_ring *sds_ring = data;
	काष्ठा netxen_adapter *adapter = sds_ring->adapter;
	u32 status = 0;

	status = पढ़ोl(adapter->isr_पूर्णांक_vec);

	अगर (!(status & adapter->पूर्णांक_vec_bit))
		वापस IRQ_NONE;

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id)) अणु
		/* check पूर्णांकerrupt state machine, to be sure */
		status = पढ़ोl(adapter->crb_पूर्णांक_state_reg);
		अगर (!ISR_LEGACY_INT_TRIGGERED(status))
			वापस IRQ_NONE;

	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ our_पूर्णांक = 0;

		our_पूर्णांक = पढ़ोl(adapter->crb_पूर्णांक_state_reg);

		/* not our पूर्णांकerrupt */
		अगर (!test_and_clear_bit((7 + adapter->portnum), &our_पूर्णांक))
			वापस IRQ_NONE;

		/* claim पूर्णांकerrupt */
		ग_लिखोl((our_पूर्णांक & 0xffffffff), adapter->crb_पूर्णांक_state_reg);

		/* clear पूर्णांकerrupt */
		netxen_nic_disable_पूर्णांक(sds_ring);
	पूर्ण

	ग_लिखोl(0xffffffff, adapter->tgt_status_reg);
	/* पढ़ो twice to ensure ग_लिखो is flushed */
	पढ़ोl(adapter->isr_पूर्णांक_vec);
	पढ़ोl(adapter->isr_पूर्णांक_vec);

	napi_schedule(&sds_ring->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t netxen_msi_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा nx_host_sds_ring *sds_ring = data;
	काष्ठा netxen_adapter *adapter = sds_ring->adapter;

	/* clear पूर्णांकerrupt */
	ग_लिखोl(0xffffffff, adapter->tgt_status_reg);

	napi_schedule(&sds_ring->napi);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t netxen_msix_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा nx_host_sds_ring *sds_ring = data;

	napi_schedule(&sds_ring->napi);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक netxen_nic_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा nx_host_sds_ring *sds_ring =
		container_of(napi, काष्ठा nx_host_sds_ring, napi);

	काष्ठा netxen_adapter *adapter = sds_ring->adapter;

	पूर्णांक tx_complete;
	पूर्णांक work_करोne;

	tx_complete = netxen_process_cmd_ring(adapter);

	work_करोne = netxen_process_rcv_ring(sds_ring, budget);

	अगर (!tx_complete)
		work_करोne = budget;

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(&sds_ring->napi, work_करोne);
		अगर (test_bit(__NX_DEV_UP, &adapter->state))
			netxen_nic_enable_पूर्णांक(sds_ring);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल पूर्णांक
nx_incr_dev_ref_cnt(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक count;
	अगर (netxen_api_lock(adapter))
		वापस -EIO;

	count = NXRD32(adapter, NX_CRB_DEV_REF_COUNT);

	NXWR32(adapter, NX_CRB_DEV_REF_COUNT, ++count);

	netxen_api_unlock(adapter);
	वापस count;
पूर्ण

अटल पूर्णांक
nx_decr_dev_ref_cnt(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक count, state;
	अगर (netxen_api_lock(adapter))
		वापस -EIO;

	count = NXRD32(adapter, NX_CRB_DEV_REF_COUNT);
	WARN_ON(count == 0);

	NXWR32(adapter, NX_CRB_DEV_REF_COUNT, --count);
	state = NXRD32(adapter, NX_CRB_DEV_STATE);

	अगर (count == 0 && state != NX_DEV_FAILED)
		NXWR32(adapter, NX_CRB_DEV_STATE, NX_DEV_COLD);

	netxen_api_unlock(adapter);
	वापस count;
पूर्ण

अटल पूर्णांक
nx_dev_request_aer(काष्ठा netxen_adapter *adapter)
अणु
	u32 state;
	पूर्णांक ret = -EINVAL;

	अगर (netxen_api_lock(adapter))
		वापस ret;

	state = NXRD32(adapter, NX_CRB_DEV_STATE);

	अगर (state == NX_DEV_NEED_AER)
		ret = 0;
	अन्यथा अगर (state == NX_DEV_READY) अणु
		NXWR32(adapter, NX_CRB_DEV_STATE, NX_DEV_NEED_AER);
		ret = 0;
	पूर्ण

	netxen_api_unlock(adapter);
	वापस ret;
पूर्ण

पूर्णांक
nx_dev_request_reset(काष्ठा netxen_adapter *adapter)
अणु
	u32 state;
	पूर्णांक ret = -EINVAL;

	अगर (netxen_api_lock(adapter))
		वापस ret;

	state = NXRD32(adapter, NX_CRB_DEV_STATE);

	अगर (state == NX_DEV_NEED_RESET || state == NX_DEV_FAILED)
		ret = 0;
	अन्यथा अगर (state != NX_DEV_INITALIZING && state != NX_DEV_NEED_AER) अणु
		NXWR32(adapter, NX_CRB_DEV_STATE, NX_DEV_NEED_RESET);
		adapter->flags |= NETXEN_FW_RESET_OWNER;
		ret = 0;
	पूर्ण

	netxen_api_unlock(adapter);

	वापस ret;
पूर्ण

अटल पूर्णांक
netxen_can_start_firmware(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक count;
	पूर्णांक can_start = 0;

	अगर (netxen_api_lock(adapter)) अणु
		nx_incr_dev_ref_cnt(adapter);
		वापस -1;
	पूर्ण

	count = NXRD32(adapter, NX_CRB_DEV_REF_COUNT);

	अगर ((count < 0) || (count >= NX_MAX_PCI_FUNC))
		count = 0;

	अगर (count == 0) अणु
		can_start = 1;
		NXWR32(adapter, NX_CRB_DEV_STATE, NX_DEV_INITALIZING);
	पूर्ण

	NXWR32(adapter, NX_CRB_DEV_REF_COUNT, ++count);

	netxen_api_unlock(adapter);

	वापस can_start;
पूर्ण

अटल व्योम
netxen_schedule_work(काष्ठा netxen_adapter *adapter,
		work_func_t func, पूर्णांक delay)
अणु
	INIT_DELAYED_WORK(&adapter->fw_work, func);
	schedule_delayed_work(&adapter->fw_work, delay);
पूर्ण

अटल व्योम
netxen_cancel_fw_work(काष्ठा netxen_adapter *adapter)
अणु
	जबतक (test_and_set_bit(__NX_RESETTING, &adapter->state))
		msleep(10);

	cancel_delayed_work_sync(&adapter->fw_work);
पूर्ण

अटल व्योम
netxen_attach_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा netxen_adapter *adapter = container_of(work,
				काष्ठा netxen_adapter, fw_work.work);
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err = 0;

	अगर (netअगर_running(netdev)) अणु
		err = netxen_nic_attach(adapter);
		अगर (err)
			जाओ करोne;

		err = netxen_nic_up(adapter, netdev);
		अगर (err) अणु
			netxen_nic_detach(adapter);
			जाओ करोne;
		पूर्ण

		netxen_restore_indev_addr(netdev, NETDEV_UP);
	पूर्ण

	netअगर_device_attach(netdev);

करोne:
	adapter->fw_fail_cnt = 0;
	clear_bit(__NX_RESETTING, &adapter->state);
	netxen_schedule_work(adapter, netxen_fw_poll_work, FW_POLL_DELAY);
पूर्ण

अटल व्योम
netxen_fwinit_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा netxen_adapter *adapter = container_of(work,
				काष्ठा netxen_adapter, fw_work.work);
	पूर्णांक dev_state;
	पूर्णांक count;
	dev_state = NXRD32(adapter, NX_CRB_DEV_STATE);
	अगर (adapter->flags & NETXEN_FW_RESET_OWNER) अणु
		count = NXRD32(adapter, NX_CRB_DEV_REF_COUNT);
		WARN_ON(count == 0);
		अगर (count == 1) अणु
			अगर (adapter->mdump.md_enabled) अणु
				rtnl_lock();
				netxen_dump_fw(adapter);
				rtnl_unlock();
			पूर्ण
			adapter->flags &= ~NETXEN_FW_RESET_OWNER;
			अगर (netxen_api_lock(adapter)) अणु
				clear_bit(__NX_RESETTING, &adapter->state);
				NXWR32(adapter, NX_CRB_DEV_STATE,
						NX_DEV_FAILED);
				वापस;
			पूर्ण
			count = NXRD32(adapter, NX_CRB_DEV_REF_COUNT);
			NXWR32(adapter, NX_CRB_DEV_REF_COUNT, --count);
			NXWR32(adapter, NX_CRB_DEV_STATE, NX_DEV_COLD);
			dev_state = NX_DEV_COLD;
			netxen_api_unlock(adapter);
		पूर्ण
	पूर्ण

	चयन (dev_state) अणु
	हाल NX_DEV_COLD:
	हाल NX_DEV_READY:
		अगर (!netxen_start_firmware(adapter)) अणु
			netxen_schedule_work(adapter, netxen_attach_work, 0);
			वापस;
		पूर्ण
		अवरोध;

	हाल NX_DEV_NEED_RESET:
	हाल NX_DEV_INITALIZING:
			netxen_schedule_work(adapter,
					netxen_fwinit_work, 2 * FW_POLL_DELAY);
			वापस;

	हाल NX_DEV_FAILED:
	शेष:
		nx_incr_dev_ref_cnt(adapter);
		अवरोध;
	पूर्ण

	अगर (netxen_api_lock(adapter)) अणु
		clear_bit(__NX_RESETTING, &adapter->state);
		वापस;
	पूर्ण
	NXWR32(adapter, NX_CRB_DEV_STATE, NX_DEV_FAILED);
	netxen_api_unlock(adapter);
	dev_err(&adapter->pdev->dev, "%s: Device initialization Failed\n",
				adapter->netdev->name);

	clear_bit(__NX_RESETTING, &adapter->state);
पूर्ण

अटल व्योम
netxen_detach_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा netxen_adapter *adapter = container_of(work,
				काष्ठा netxen_adapter, fw_work.work);
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक ref_cnt = 0, delay;
	u32 status;

	netअगर_device_detach(netdev);

	netxen_nic_करोwn(adapter, netdev);

	rtnl_lock();
	netxen_nic_detach(adapter);
	rtnl_unlock();

	status = NXRD32(adapter, NETXEN_PEG_HALT_STATUS1);

	अगर (status & NX_RCODE_FATAL_ERROR)
		जाओ err_ret;

	अगर (adapter->temp == NX_TEMP_PANIC)
		जाओ err_ret;

	अगर (!(adapter->flags & NETXEN_FW_RESET_OWNER))
		ref_cnt = nx_decr_dev_ref_cnt(adapter);

	अगर (ref_cnt == -EIO)
		जाओ err_ret;

	delay = (ref_cnt == 0) ? 0 : (2 * FW_POLL_DELAY);

	adapter->fw_रुको_cnt = 0;
	netxen_schedule_work(adapter, netxen_fwinit_work, delay);

	वापस;

err_ret:
	clear_bit(__NX_RESETTING, &adapter->state);
पूर्ण

अटल पूर्णांक
netxen_check_health(काष्ठा netxen_adapter *adapter)
अणु
	u32 state, heartbit;
	u32 peg_status;
	काष्ठा net_device *netdev = adapter->netdev;

	state = NXRD32(adapter, NX_CRB_DEV_STATE);
	अगर (state == NX_DEV_NEED_AER)
		वापस 0;

	अगर (netxen_nic_check_temp(adapter))
		जाओ detach;

	अगर (adapter->need_fw_reset) अणु
		अगर (nx_dev_request_reset(adapter))
			वापस 0;
		जाओ detach;
	पूर्ण

	/* NX_DEV_NEED_RESET, this state can be marked in two हालs
	 * 1. Tx समयout 2. Fw hang
	 * Send request to destroy context in हाल of tx समयout only
	 * and करोesn't required in हाल of Fw hang
	 */
	अगर (state == NX_DEV_NEED_RESET || state == NX_DEV_FAILED) अणु
		adapter->need_fw_reset = 1;
		अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id))
			जाओ detach;
	पूर्ण

	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		वापस 0;

	heartbit = NXRD32(adapter, NETXEN_PEG_ALIVE_COUNTER);
	अगर (heartbit != adapter->heartbit) अणु
		adapter->heartbit = heartbit;
		adapter->fw_fail_cnt = 0;
		अगर (adapter->need_fw_reset)
			जाओ detach;
		वापस 0;
	पूर्ण

	अगर (++adapter->fw_fail_cnt < FW_FAIL_THRESH)
		वापस 0;

	अगर (nx_dev_request_reset(adapter))
		वापस 0;

	clear_bit(__NX_FW_ATTACHED, &adapter->state);

	dev_err(&netdev->dev, "firmware hang detected\n");
	peg_status = NXRD32(adapter, NETXEN_PEG_HALT_STATUS1);
	dev_err(&adapter->pdev->dev, "Dumping hw/fw registers\n"
			"PEG_HALT_STATUS1: 0x%x, PEG_HALT_STATUS2: 0x%x,\n"
			"PEG_NET_0_PC: 0x%x, PEG_NET_1_PC: 0x%x,\n"
			"PEG_NET_2_PC: 0x%x, PEG_NET_3_PC: 0x%x,\n"
			"PEG_NET_4_PC: 0x%x\n",
			peg_status,
			NXRD32(adapter, NETXEN_PEG_HALT_STATUS2),
			NXRD32(adapter, NETXEN_CRB_PEG_NET_0 + 0x3c),
			NXRD32(adapter, NETXEN_CRB_PEG_NET_1 + 0x3c),
			NXRD32(adapter, NETXEN_CRB_PEG_NET_2 + 0x3c),
			NXRD32(adapter, NETXEN_CRB_PEG_NET_3 + 0x3c),
			NXRD32(adapter, NETXEN_CRB_PEG_NET_4 + 0x3c));
	अगर (NX_FWERROR_PEGSTAT1(peg_status) == 0x67)
		dev_err(&adapter->pdev->dev,
			"Firmware aborted with error code 0x00006700. "
				"Device is being reset.\n");
detach:
	अगर ((स्वतः_fw_reset == AUTO_FW_RESET_ENABLED) &&
			!test_and_set_bit(__NX_RESETTING, &adapter->state))
		netxen_schedule_work(adapter, netxen_detach_work, 0);
	वापस 1;
पूर्ण

अटल व्योम
netxen_fw_poll_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा netxen_adapter *adapter = container_of(work,
				काष्ठा netxen_adapter, fw_work.work);

	अगर (test_bit(__NX_RESETTING, &adapter->state))
		जाओ reschedule;

	अगर (test_bit(__NX_DEV_UP, &adapter->state) &&
	    !(adapter->capabilities & NX_FW_CAPABILITY_LINK_NOTIFICATION)) अणु
		अगर (!adapter->has_link_events) अणु

			netxen_nic_handle_phy_पूर्णांकr(adapter);

			अगर (adapter->link_changed)
				netxen_nic_set_link_parameters(adapter);
		पूर्ण
	पूर्ण

	अगर (netxen_check_health(adapter))
		वापस;

reschedule:
	netxen_schedule_work(adapter, netxen_fw_poll_work, FW_POLL_DELAY);
पूर्ण

अटल sमाप_प्रकार
netxen_store_bridged_mode(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा net_device *net = to_net_dev(dev);
	काष्ठा netxen_adapter *adapter = netdev_priv(net);
	अचिन्हित दीर्घ new;
	पूर्णांक ret = -EINVAL;

	अगर (!(adapter->capabilities & NX_FW_CAPABILITY_BDG))
		जाओ err_out;

	अगर (adapter->is_up != NETXEN_ADAPTER_UP_MAGIC)
		जाओ err_out;

	अगर (kम_से_अदीर्घ(buf, 2, &new))
		जाओ err_out;

	अगर (!netxen_config_bridged_mode(adapter, !!new))
		ret = len;

err_out:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
netxen_show_bridged_mode(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_device *net = to_net_dev(dev);
	काष्ठा netxen_adapter *adapter;
	पूर्णांक bridged_mode = 0;

	adapter = netdev_priv(net);

	अगर (adapter->capabilities & NX_FW_CAPABILITY_BDG)
		bridged_mode = !!(adapter->flags & NETXEN_NIC_BRIDGE_ENABLED);

	वापस प्र_लिखो(buf, "%d\n", bridged_mode);
पूर्ण

अटल स्थिर काष्ठा device_attribute dev_attr_bridged_mode = अणु
	.attr = अणु .name = "bridged_mode", .mode = 0644 पूर्ण,
	.show = netxen_show_bridged_mode,
	.store = netxen_store_bridged_mode,
पूर्ण;

अटल sमाप_प्रकार
netxen_store_diag_mode(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा netxen_adapter *adapter = dev_get_drvdata(dev);
	अचिन्हित दीर्घ new;

	अगर (kम_से_अदीर्घ(buf, 2, &new))
		वापस -EINVAL;

	अगर (!!new != !!(adapter->flags & NETXEN_NIC_DIAG_ENABLED))
		adapter->flags ^= NETXEN_NIC_DIAG_ENABLED;

	वापस len;
पूर्ण

अटल sमाप_प्रकार
netxen_show_diag_mode(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा netxen_adapter *adapter = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n",
			!!(adapter->flags & NETXEN_NIC_DIAG_ENABLED));
पूर्ण

अटल स्थिर काष्ठा device_attribute dev_attr_diag_mode = अणु
	.attr = अणु .name = "diag_mode", .mode = 0644 पूर्ण,
	.show = netxen_show_diag_mode,
	.store = netxen_store_diag_mode,
पूर्ण;

अटल पूर्णांक
netxen_sysfs_validate_crb(काष्ठा netxen_adapter *adapter,
		loff_t offset, माप_प्रकार size)
अणु
	माप_प्रकार crb_size = 4;

	अगर (!(adapter->flags & NETXEN_NIC_DIAG_ENABLED))
		वापस -EIO;

	अगर (offset < NETXEN_PCI_CRBSPACE) अणु
		अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id))
			वापस -EINVAL;

		अगर (ADDR_IN_RANGE(offset, NETXEN_PCI_CAMQM,
						NETXEN_PCI_CAMQM_2M_END))
			crb_size = 8;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर ((size != crb_size) || (offset & (crb_size-1)))
		वापस  -EINVAL;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
netxen_sysfs_पढ़ो_crb(काष्ठा file *filp, काष्ठा kobject *kobj,
		काष्ठा bin_attribute *attr,
		अक्षर *buf, loff_t offset, माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा netxen_adapter *adapter = dev_get_drvdata(dev);
	u32 data;
	u64 qmdata;
	पूर्णांक ret;

	ret = netxen_sysfs_validate_crb(adapter, offset, size);
	अगर (ret != 0)
		वापस ret;

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id) &&
		ADDR_IN_RANGE(offset, NETXEN_PCI_CAMQM,
					NETXEN_PCI_CAMQM_2M_END)) अणु
		netxen_pci_camqm_पढ़ो_2M(adapter, offset, &qmdata);
		स_नकल(buf, &qmdata, size);
	पूर्ण अन्यथा अणु
		data = NXRD32(adapter, offset);
		स_नकल(buf, &data, size);
	पूर्ण

	वापस size;
पूर्ण

अटल sमाप_प्रकार
netxen_sysfs_ग_लिखो_crb(काष्ठा file *filp, काष्ठा kobject *kobj,
		काष्ठा bin_attribute *attr,
		अक्षर *buf, loff_t offset, माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा netxen_adapter *adapter = dev_get_drvdata(dev);
	u32 data;
	u64 qmdata;
	पूर्णांक ret;

	ret = netxen_sysfs_validate_crb(adapter, offset, size);
	अगर (ret != 0)
		वापस ret;

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id) &&
		ADDR_IN_RANGE(offset, NETXEN_PCI_CAMQM,
					NETXEN_PCI_CAMQM_2M_END)) अणु
		स_नकल(&qmdata, buf, size);
		netxen_pci_camqm_ग_लिखो_2M(adapter, offset, qmdata);
	पूर्ण अन्यथा अणु
		स_नकल(&data, buf, size);
		NXWR32(adapter, offset, data);
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक
netxen_sysfs_validate_mem(काष्ठा netxen_adapter *adapter,
		loff_t offset, माप_प्रकार size)
अणु
	अगर (!(adapter->flags & NETXEN_NIC_DIAG_ENABLED))
		वापस -EIO;

	अगर ((size != 8) || (offset & 0x7))
		वापस  -EIO;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
netxen_sysfs_पढ़ो_mem(काष्ठा file *filp, काष्ठा kobject *kobj,
		काष्ठा bin_attribute *attr,
		अक्षर *buf, loff_t offset, माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा netxen_adapter *adapter = dev_get_drvdata(dev);
	u64 data;
	पूर्णांक ret;

	ret = netxen_sysfs_validate_mem(adapter, offset, size);
	अगर (ret != 0)
		वापस ret;

	अगर (adapter->pci_mem_पढ़ो(adapter, offset, &data))
		वापस -EIO;

	स_नकल(buf, &data, size);

	वापस size;
पूर्ण

अटल sमाप_प्रकार netxen_sysfs_ग_लिखो_mem(काष्ठा file *filp, काष्ठा kobject *kobj,
		काष्ठा bin_attribute *attr, अक्षर *buf,
		loff_t offset, माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा netxen_adapter *adapter = dev_get_drvdata(dev);
	u64 data;
	पूर्णांक ret;

	ret = netxen_sysfs_validate_mem(adapter, offset, size);
	अगर (ret != 0)
		वापस ret;

	स_नकल(&data, buf, size);

	अगर (adapter->pci_mem_ग_लिखो(adapter, offset, data))
		वापस -EIO;

	वापस size;
पूर्ण


अटल स्थिर काष्ठा bin_attribute bin_attr_crb = अणु
	.attr = अणु .name = "crb", .mode = 0644 पूर्ण,
	.size = 0,
	.पढ़ो = netxen_sysfs_पढ़ो_crb,
	.ग_लिखो = netxen_sysfs_ग_लिखो_crb,
पूर्ण;

अटल स्थिर काष्ठा bin_attribute bin_attr_mem = अणु
	.attr = अणु .name = "mem", .mode = 0644 पूर्ण,
	.size = 0,
	.पढ़ो = netxen_sysfs_पढ़ो_mem,
	.ग_लिखो = netxen_sysfs_ग_लिखो_mem,
पूर्ण;

अटल sमाप_प्रकार
netxen_sysfs_पढ़ो_dimm(काष्ठा file *filp, काष्ठा kobject *kobj,
		काष्ठा bin_attribute *attr,
		अक्षर *buf, loff_t offset, माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा netxen_adapter *adapter = dev_get_drvdata(dev);
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा netxen_dimm_cfg dimm;
	u8 dw, rows, cols, banks, ranks;
	u32 val;

	अगर (size < attr->size) अणु
		netdev_err(netdev, "Invalid size\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&dimm, 0, माप(काष्ठा netxen_dimm_cfg));
	val = NXRD32(adapter, NETXEN_DIMM_CAPABILITY);

	/* Checks अगर DIMM info is valid. */
	अगर (val & NETXEN_DIMM_VALID_FLAG) अणु
		netdev_err(netdev, "Invalid DIMM flag\n");
		dimm.presence = 0xff;
		जाओ out;
	पूर्ण

	rows = NETXEN_DIMM_NUMROWS(val);
	cols = NETXEN_DIMM_NUMCOLS(val);
	ranks = NETXEN_DIMM_NUMRANKS(val);
	banks = NETXEN_DIMM_NUMBANKS(val);
	dw = NETXEN_DIMM_DATAWIDTH(val);

	dimm.presence = (val & NETXEN_DIMM_PRESENT);

	/* Checks अगर DIMM info is present. */
	अगर (!dimm.presence) अणु
		netdev_err(netdev, "DIMM not present\n");
		जाओ out;
	पूर्ण

	dimm.dimm_type = NETXEN_DIMM_TYPE(val);

	चयन (dimm.dimm_type) अणु
	हाल NETXEN_DIMM_TYPE_RDIMM:
	हाल NETXEN_DIMM_TYPE_UDIMM:
	हाल NETXEN_DIMM_TYPE_SO_DIMM:
	हाल NETXEN_DIMM_TYPE_Micro_DIMM:
	हाल NETXEN_DIMM_TYPE_Mini_RDIMM:
	हाल NETXEN_DIMM_TYPE_Mini_UDIMM:
		अवरोध;
	शेष:
		netdev_err(netdev, "Invalid DIMM type %x\n", dimm.dimm_type);
		जाओ out;
	पूर्ण

	अगर (val & NETXEN_DIMM_MEMTYPE_DDR2_SDRAM)
		dimm.mem_type = NETXEN_DIMM_MEM_DDR2_SDRAM;
	अन्यथा
		dimm.mem_type = NETXEN_DIMM_MEMTYPE(val);

	अगर (val & NETXEN_DIMM_SIZE) अणु
		dimm.size = NETXEN_DIMM_STD_MEM_SIZE;
		जाओ out;
	पूर्ण

	अगर (!rows) अणु
		netdev_err(netdev, "Invalid no of rows %x\n", rows);
		जाओ out;
	पूर्ण

	अगर (!cols) अणु
		netdev_err(netdev, "Invalid no of columns %x\n", cols);
		जाओ out;
	पूर्ण

	अगर (!banks) अणु
		netdev_err(netdev, "Invalid no of banks %x\n", banks);
		जाओ out;
	पूर्ण

	ranks += 1;

	चयन (dw) अणु
	हाल 0x0:
		dw = 32;
		अवरोध;
	हाल 0x1:
		dw = 33;
		अवरोध;
	हाल 0x2:
		dw = 36;
		अवरोध;
	हाल 0x3:
		dw = 64;
		अवरोध;
	हाल 0x4:
		dw = 72;
		अवरोध;
	हाल 0x5:
		dw = 80;
		अवरोध;
	हाल 0x6:
		dw = 128;
		अवरोध;
	हाल 0x7:
		dw = 144;
		अवरोध;
	शेष:
		netdev_err(netdev, "Invalid data-width %x\n", dw);
		जाओ out;
	पूर्ण

	dimm.size = ((1 << rows) * (1 << cols) * dw * banks * ranks) / 8;
	/* Size वापसed in MB. */
	dimm.size = (dimm.size) / 0x100000;
out:
	स_नकल(buf, &dimm, माप(काष्ठा netxen_dimm_cfg));
	वापस माप(काष्ठा netxen_dimm_cfg);

पूर्ण

अटल स्थिर काष्ठा bin_attribute bin_attr_dimm = अणु
	.attr = अणु .name = "dimm", .mode = 0644 पूर्ण,
	.size = माप(काष्ठा netxen_dimm_cfg),
	.पढ़ो = netxen_sysfs_पढ़ो_dimm,
पूर्ण;


अटल व्योम
netxen_create_sysfs_entries(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;

	अगर (adapter->capabilities & NX_FW_CAPABILITY_BDG) अणु
		/* bridged_mode control */
		अगर (device_create_file(dev, &dev_attr_bridged_mode)) अणु
			dev_warn(dev,
				"failed to create bridged_mode sysfs entry\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
netxen_हटाओ_sysfs_entries(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;

	अगर (adapter->capabilities & NX_FW_CAPABILITY_BDG)
		device_हटाओ_file(dev, &dev_attr_bridged_mode);
पूर्ण

अटल व्योम
netxen_create_diag_entries(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा device *dev;

	dev = &pdev->dev;
	अगर (device_create_file(dev, &dev_attr_diag_mode))
		dev_info(dev, "failed to create diag_mode sysfs entry\n");
	अगर (device_create_bin_file(dev, &bin_attr_crb))
		dev_info(dev, "failed to create crb sysfs entry\n");
	अगर (device_create_bin_file(dev, &bin_attr_mem))
		dev_info(dev, "failed to create mem sysfs entry\n");
	अगर (device_create_bin_file(dev, &bin_attr_dimm))
		dev_info(dev, "failed to create dimm sysfs entry\n");
पूर्ण


अटल व्योम
netxen_हटाओ_diag_entries(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा device *dev = &pdev->dev;

	device_हटाओ_file(dev, &dev_attr_diag_mode);
	device_हटाओ_bin_file(dev, &bin_attr_crb);
	device_हटाओ_bin_file(dev, &bin_attr_mem);
	device_हटाओ_bin_file(dev, &bin_attr_dimm);
पूर्ण

#अगर_घोषित CONFIG_INET

#घोषणा is_netxen_netdev(dev) (dev->netdev_ops == &netxen_netdev_ops)

अटल पूर्णांक
netxen_destip_supported(काष्ठा netxen_adapter *adapter)
अणु
	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		वापस 0;

	अगर (adapter->ahw.cut_through)
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम
netxen_मुक्त_ip_list(काष्ठा netxen_adapter *adapter, bool master)
अणु
	काष्ठा nx_ip_list  *cur, *पंचांगp_cur;

	list_क्रम_each_entry_safe(cur, पंचांगp_cur, &adapter->ip_list, list) अणु
		अगर (master) अणु
			अगर (cur->master) अणु
				netxen_config_ipaddr(adapter, cur->ip_addr,
						     NX_IP_DOWN);
				list_del(&cur->list);
				kमुक्त(cur);
			पूर्ण
		पूर्ण अन्यथा अणु
			netxen_config_ipaddr(adapter, cur->ip_addr, NX_IP_DOWN);
			list_del(&cur->list);
			kमुक्त(cur);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool
netxen_list_config_ip(काष्ठा netxen_adapter *adapter,
		काष्ठा in_अगरaddr *अगरa, अचिन्हित दीर्घ event)
अणु
	काष्ठा net_device *dev;
	काष्ठा nx_ip_list *cur, *पंचांगp_cur;
	काष्ठा list_head *head;
	bool ret = false;

	dev = अगरa->अगरa_dev ? अगरa->अगरa_dev->dev : शून्य;

	अगर (dev == शून्य)
		जाओ out;

	चयन (event) अणु
	हाल NX_IP_UP:
		list_क्रम_each(head, &adapter->ip_list) अणु
			cur = list_entry(head, काष्ठा nx_ip_list, list);

			अगर (cur->ip_addr == अगरa->अगरa_address)
				जाओ out;
		पूर्ण

		cur = kzalloc(माप(काष्ठा nx_ip_list), GFP_ATOMIC);
		अगर (cur == शून्य)
			जाओ out;
		अगर (is_vlan_dev(dev))
			dev = vlan_dev_real_dev(dev);
		cur->master = !!netअगर_is_bond_master(dev);
		cur->ip_addr = अगरa->अगरa_address;
		list_add_tail(&cur->list, &adapter->ip_list);
		netxen_config_ipaddr(adapter, अगरa->अगरa_address, NX_IP_UP);
		ret = true;
		अवरोध;
	हाल NX_IP_DOWN:
		list_क्रम_each_entry_safe(cur, पंचांगp_cur,
					&adapter->ip_list, list) अणु
			अगर (cur->ip_addr == अगरa->अगरa_address) अणु
				list_del(&cur->list);
				kमुक्त(cur);
				netxen_config_ipaddr(adapter, अगरa->अगरa_address,
						     NX_IP_DOWN);
				ret = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल व्योम
netxen_config_indev_addr(काष्ठा netxen_adapter *adapter,
		काष्ठा net_device *dev, अचिन्हित दीर्घ event)
अणु
	काष्ठा in_device *indev;
	काष्ठा in_अगरaddr *अगरa;

	अगर (!netxen_destip_supported(adapter))
		वापस;

	indev = in_dev_get(dev);
	अगर (!indev)
		वापस;

	rcu_पढ़ो_lock();
	in_dev_क्रम_each_अगरa_rcu(अगरa, indev) अणु
		चयन (event) अणु
		हाल NETDEV_UP:
			netxen_list_config_ip(adapter, अगरa, NX_IP_UP);
			अवरोध;
		हाल NETDEV_DOWN:
			netxen_list_config_ip(adapter, अगरa, NX_IP_DOWN);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	in_dev_put(indev);
पूर्ण

अटल व्योम
netxen_restore_indev_addr(काष्ठा net_device *netdev, अचिन्हित दीर्घ event)

अणु
	काष्ठा netxen_adapter *adapter = netdev_priv(netdev);
	काष्ठा nx_ip_list *pos, *पंचांगp_pos;
	अचिन्हित दीर्घ ip_event;

	ip_event = (event == NETDEV_UP) ? NX_IP_UP : NX_IP_DOWN;
	netxen_config_indev_addr(adapter, netdev, event);

	list_क्रम_each_entry_safe(pos, पंचांगp_pos, &adapter->ip_list, list) अणु
		netxen_config_ipaddr(adapter, pos->ip_addr, ip_event);
	पूर्ण
पूर्ण

अटल अंतरभूत bool
netxen_config_checkdev(काष्ठा net_device *dev)
अणु
	काष्ठा netxen_adapter *adapter;

	अगर (!is_netxen_netdev(dev))
		वापस false;
	adapter = netdev_priv(dev);
	अगर (!adapter)
		वापस false;
	अगर (!netxen_destip_supported(adapter))
		वापस false;
	अगर (adapter->is_up != NETXEN_ADAPTER_UP_MAGIC)
		वापस false;

	वापस true;
पूर्ण

/**
 * netxen_config_master - configure addresses based on master
 * @dev: netxen device
 * @event: netdev event
 */
अटल व्योम netxen_config_master(काष्ठा net_device *dev, अचिन्हित दीर्घ event)
अणु
	काष्ठा net_device *master, *slave;
	काष्ठा netxen_adapter *adapter = netdev_priv(dev);

	rcu_पढ़ो_lock();
	master = netdev_master_upper_dev_get_rcu(dev);
	/*
	 * This is the हाल where the netxen nic is being
	 * enslaved and is dev_खोलो()ed in bond_enslave()
	 * Now we should program the bond's (and its vlans')
	 * addresses in the netxen NIC.
	 */
	अगर (master && netअगर_is_bond_master(master) &&
	    !netअगर_is_bond_slave(dev)) अणु
		netxen_config_indev_addr(adapter, master, event);
		क्रम_each_netdev_rcu(&init_net, slave)
			अगर (is_vlan_dev(slave) &&
			    vlan_dev_real_dev(slave) == master)
				netxen_config_indev_addr(adapter, slave, event);
	पूर्ण
	rcu_पढ़ो_unlock();
	/*
	 * This is the हाल where the netxen nic is being
	 * released and is dev_बंद()ed in bond_release()
	 * just beक्रमe IFF_BONDING is stripped.
	 */
	अगर (!master && dev->priv_flags & IFF_BONDING)
		netxen_मुक्त_ip_list(adapter, true);
पूर्ण

अटल पूर्णांक netxen_netdev_event(काष्ठा notअगरier_block *this,
				 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा netxen_adapter *adapter;
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा net_device *orig_dev = dev;
	काष्ठा net_device *slave;

recheck:
	अगर (dev == शून्य)
		जाओ करोne;

	अगर (is_vlan_dev(dev)) अणु
		dev = vlan_dev_real_dev(dev);
		जाओ recheck;
	पूर्ण
	अगर (event == NETDEV_UP || event == NETDEV_DOWN) अणु
		/* If this is a bonding device, look क्रम netxen-based slaves*/
		अगर (netअगर_is_bond_master(dev)) अणु
			rcu_पढ़ो_lock();
			क्रम_each_netdev_in_bond_rcu(dev, slave) अणु
				अगर (!netxen_config_checkdev(slave))
					जारी;
				adapter = netdev_priv(slave);
				netxen_config_indev_addr(adapter,
							 orig_dev, event);
			पूर्ण
			rcu_पढ़ो_unlock();
		पूर्ण अन्यथा अणु
			अगर (!netxen_config_checkdev(dev))
				जाओ करोne;
			adapter = netdev_priv(dev);
			/* Act only अगर the actual netxen is the target */
			अगर (orig_dev == dev)
				netxen_config_master(dev, event);
			netxen_config_indev_addr(adapter, orig_dev, event);
		पूर्ण
	पूर्ण
करोne:
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक
netxen_inetaddr_event(काष्ठा notअगरier_block *this,
		अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा netxen_adapter *adapter;
	काष्ठा net_device *dev, *slave;
	काष्ठा in_अगरaddr *अगरa = (काष्ठा in_अगरaddr *)ptr;
	अचिन्हित दीर्घ ip_event;

	dev = अगरa->अगरa_dev ? अगरa->अगरa_dev->dev : शून्य;
	ip_event = (event == NETDEV_UP) ? NX_IP_UP : NX_IP_DOWN;
recheck:
	अगर (dev == शून्य)
		जाओ करोne;

	अगर (is_vlan_dev(dev)) अणु
		dev = vlan_dev_real_dev(dev);
		जाओ recheck;
	पूर्ण
	अगर (event == NETDEV_UP || event == NETDEV_DOWN) अणु
		/* If this is a bonding device, look क्रम netxen-based slaves*/
		अगर (netअगर_is_bond_master(dev)) अणु
			rcu_पढ़ो_lock();
			क्रम_each_netdev_in_bond_rcu(dev, slave) अणु
				अगर (!netxen_config_checkdev(slave))
					जारी;
				adapter = netdev_priv(slave);
				netxen_list_config_ip(adapter, अगरa, ip_event);
			पूर्ण
			rcu_पढ़ो_unlock();
		पूर्ण अन्यथा अणु
			अगर (!netxen_config_checkdev(dev))
				जाओ करोne;
			adapter = netdev_priv(dev);
			netxen_list_config_ip(adapter, अगरa, ip_event);
		पूर्ण
	पूर्ण
करोne:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block	netxen_netdev_cb = अणु
	.notअगरier_call = netxen_netdev_event,
पूर्ण;

अटल काष्ठा notअगरier_block netxen_inetaddr_cb = अणु
	.notअगरier_call = netxen_inetaddr_event,
पूर्ण;
#अन्यथा
अटल व्योम
netxen_restore_indev_addr(काष्ठा net_device *dev, अचिन्हित दीर्घ event)
अणु पूर्ण
अटल व्योम
netxen_मुक्त_ip_list(काष्ठा netxen_adapter *adapter, bool master)
अणु पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_error_handlers netxen_err_handler = अणु
	.error_detected = netxen_io_error_detected,
	.slot_reset = netxen_io_slot_reset,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(netxen_nic_pm_ops,
			 netxen_nic_suspend,
			 netxen_nic_resume);

अटल काष्ठा pci_driver netxen_driver = अणु
	.name = netxen_nic_driver_name,
	.id_table = netxen_pci_tbl,
	.probe = netxen_nic_probe,
	.हटाओ = netxen_nic_हटाओ,
	.driver.pm = &netxen_nic_pm_ops,
	.shutकरोwn = netxen_nic_shutकरोwn,
	.err_handler = &netxen_err_handler
पूर्ण;

अटल पूर्णांक __init netxen_init_module(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "%s\n", netxen_nic_driver_string);

#अगर_घोषित CONFIG_INET
	रेजिस्टर_netdevice_notअगरier(&netxen_netdev_cb);
	रेजिस्टर_inetaddr_notअगरier(&netxen_inetaddr_cb);
#पूर्ण_अगर
	वापस pci_रेजिस्टर_driver(&netxen_driver);
पूर्ण

module_init(netxen_init_module);

अटल व्योम __निकास netxen_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&netxen_driver);

#अगर_घोषित CONFIG_INET
	unरेजिस्टर_inetaddr_notअगरier(&netxen_inetaddr_cb);
	unरेजिस्टर_netdevice_notअगरier(&netxen_netdev_cb);
#पूर्ण_अगर
पूर्ण

module_निकास(netxen_निकास_module);
