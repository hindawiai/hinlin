<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_SRIOV_H
#घोषणा HINIC_SRIOV_H

#समावेश "hinic_hw_dev.h"

#घोषणा OS_VF_ID_TO_HW(os_vf_id) ((os_vf_id) + 1)
#घोषणा HW_VF_ID_TO_OS(hw_vf_id) ((hw_vf_id) - 1)

क्रमागत hinic_sriov_state अणु
	HINIC_SRIOV_DISABLE,
	HINIC_SRIOV_ENABLE,
	HINIC_FUNC_REMOVE,
पूर्ण;

क्रमागत अणु
	HINIC_IFLA_VF_LINK_STATE_AUTO,	/* link state of the uplink */
	HINIC_IFLA_VF_LINK_STATE_ENABLE,	/* link always up */
	HINIC_IFLA_VF_LINK_STATE_DISABLE,	/* link always करोwn */
पूर्ण;

काष्ठा hinic_sriov_info अणु
	काष्ठा pci_dev *pdev;
	काष्ठा hinic_hwdev *hwdev;
	bool sriov_enabled;
	अचिन्हित पूर्णांक num_vfs;
	अचिन्हित दीर्घ state;
पूर्ण;

काष्ठा vf_data_storage अणु
	u8 vf_mac_addr[ETH_ALEN];
	bool रेजिस्टरed;
	bool pf_set_mac;
	u16 pf_vlan;
	u8 pf_qos;
	u32 max_rate;
	u32 min_rate;

	bool link_क्रमced;
	bool link_up;		/* only valid अगर VF link is क्रमced */
	bool spoofchk;
	bool trust;
पूर्ण;

काष्ठा hinic_रेजिस्टर_vf अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];
पूर्ण;

काष्ठा hinic_port_mac_update अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_id;
	u16	vlan_id;
	u16	rsvd1;
	u8	old_mac[ETH_ALEN];
	u16	rsvd2;
	u8	new_mac[ETH_ALEN];
पूर्ण;

काष्ठा hinic_vf_vlan_config अणु
	u8 status;
	u8 version;
	u8 rsvd0[6];

	u16 func_id;
	u16 vlan_id;
	u8  qos;
	u8  rsvd1[7];
पूर्ण;

पूर्णांक hinic_nकरो_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf, u8 *mac);

पूर्णांक hinic_nकरो_set_vf_vlan(काष्ठा net_device *netdev, पूर्णांक vf, u16 vlan, u8 qos,
			  __be16 vlan_proto);

पूर्णांक hinic_nकरो_get_vf_config(काष्ठा net_device *netdev,
			    पूर्णांक vf, काष्ठा अगरla_vf_info *ivi);

पूर्णांक hinic_nकरो_set_vf_trust(काष्ठा net_device *netdev, पूर्णांक vf, bool setting);

पूर्णांक hinic_nकरो_set_vf_bw(काष्ठा net_device *netdev,
			पूर्णांक vf, पूर्णांक min_tx_rate, पूर्णांक max_tx_rate);

पूर्णांक hinic_nकरो_set_vf_spoofchk(काष्ठा net_device *netdev, पूर्णांक vf, bool setting);

पूर्णांक hinic_nकरो_set_vf_link_state(काष्ठा net_device *netdev, पूर्णांक vf_id, पूर्णांक link);

व्योम hinic_notअगरy_all_vfs_link_changed(काष्ठा hinic_hwdev *hwdev,
				       u8 link_status);

पूर्णांक hinic_pci_sriov_disable(काष्ठा pci_dev *dev);

पूर्णांक hinic_pci_sriov_enable(काष्ठा pci_dev *dev, पूर्णांक num_vfs);

पूर्णांक hinic_vf_func_init(काष्ठा hinic_hwdev *hwdev);

व्योम hinic_vf_func_मुक्त(काष्ठा hinic_hwdev *hwdev);

पूर्णांक hinic_pci_sriov_configure(काष्ठा pci_dev *dev, पूर्णांक num_vfs);

#पूर्ण_अगर
