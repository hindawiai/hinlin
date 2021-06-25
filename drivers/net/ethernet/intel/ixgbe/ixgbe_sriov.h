<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _IXGBE_SRIOV_H_
#घोषणा _IXGBE_SRIOV_H_

/*  ixgbe driver limit the max number of VFs could be enabled to
 *  63 (IXGBE_MAX_VF_FUNCTIONS - 1)
 */
#घोषणा IXGBE_MAX_VFS_DRV_LIMIT  (IXGBE_MAX_VF_FUNCTIONS - 1)
#घोषणा IXGBE_MAX_VFS_1TC		IXGBE_MAX_VF_FUNCTIONS
#घोषणा IXGBE_MAX_VFS_4TC		32
#घोषणा IXGBE_MAX_VFS_8TC		16

#अगर_घोषित CONFIG_PCI_IOV
व्योम ixgbe_restore_vf_multicasts(काष्ठा ixgbe_adapter *adapter);
#पूर्ण_अगर
व्योम ixgbe_msg_task(काष्ठा ixgbe_adapter *adapter);
पूर्णांक ixgbe_vf_configuration(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक event_mask);
व्योम ixgbe_disable_tx_rx(काष्ठा ixgbe_adapter *adapter);
व्योम ixgbe_ping_all_vfs(काष्ठा ixgbe_adapter *adapter);
पूर्णांक ixgbe_nकरो_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक queue, u8 *mac);
पूर्णांक ixgbe_nकरो_set_vf_vlan(काष्ठा net_device *netdev, पूर्णांक queue, u16 vlan,
			   u8 qos, __be16 vlan_proto);
पूर्णांक ixgbe_link_mbps(काष्ठा ixgbe_adapter *adapter);
पूर्णांक ixgbe_nकरो_set_vf_bw(काष्ठा net_device *netdev, पूर्णांक vf, पूर्णांक min_tx_rate,
			पूर्णांक max_tx_rate);
पूर्णांक ixgbe_nकरो_set_vf_spoofchk(काष्ठा net_device *netdev, पूर्णांक vf, bool setting);
पूर्णांक ixgbe_nकरो_set_vf_rss_query_en(काष्ठा net_device *netdev, पूर्णांक vf,
				  bool setting);
पूर्णांक ixgbe_nकरो_set_vf_trust(काष्ठा net_device *netdev, पूर्णांक vf, bool setting);
पूर्णांक ixgbe_nकरो_get_vf_config(काष्ठा net_device *netdev,
			    पूर्णांक vf, काष्ठा अगरla_vf_info *ivi);
व्योम ixgbe_check_vf_rate_limit(काष्ठा ixgbe_adapter *adapter);
पूर्णांक ixgbe_disable_sriov(काष्ठा ixgbe_adapter *adapter);
#अगर_घोषित CONFIG_PCI_IOV
व्योम ixgbe_enable_sriov(काष्ठा ixgbe_adapter *adapter, अचिन्हित पूर्णांक max_vfs);
#पूर्ण_अगर
पूर्णांक ixgbe_pci_sriov_configure(काष्ठा pci_dev *dev, पूर्णांक num_vfs);

अटल अंतरभूत व्योम ixgbe_set_vmvir(काष्ठा ixgbe_adapter *adapter,
				   u16 vid, u16 qos, u32 vf)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 vmvir = vid | (qos << VLAN_PRIO_SHIFT) | IXGBE_VMVIR_VLANA_DEFAULT;

	IXGBE_WRITE_REG(hw, IXGBE_VMVIR(vf), vmvir);
पूर्ण

#पूर्ण_अगर /* _IXGBE_SRIOV_H_ */

