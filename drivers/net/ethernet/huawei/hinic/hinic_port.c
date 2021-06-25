<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_dev.h"
#समावेश "hinic_port.h"
#समावेश "hinic_dev.h"

#घोषणा HINIC_MIN_MTU_SIZE              256
#घोषणा HINIC_MAX_JUMBO_FRAME_SIZE      15872

क्रमागत mac_op अणु
	MAC_DEL,
	MAC_SET,
पूर्ण;

/**
 * change_mac - change(add or delete) mac address
 * @nic_dev: nic device
 * @addr: mac address
 * @vlan_id: vlan number to set with the mac
 * @op: add or delete the mac
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक change_mac(काष्ठा hinic_dev *nic_dev, स्थिर u8 *addr,
		      u16 vlan_id, क्रमागत mac_op op)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_port_mac_cmd port_mac_cmd;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	u16 out_size = माप(port_mac_cmd);
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	क्रमागत hinic_port_cmd cmd;
	पूर्णांक err;

	अगर (op == MAC_SET)
		cmd = HINIC_PORT_CMD_SET_MAC;
	अन्यथा
		cmd = HINIC_PORT_CMD_DEL_MAC;

	port_mac_cmd.func_idx = HINIC_HWIF_FUNC_IDX(hwअगर);
	port_mac_cmd.vlan_id = vlan_id;
	स_नकल(port_mac_cmd.mac, addr, ETH_ALEN);

	err = hinic_port_msg_cmd(hwdev, cmd, &port_mac_cmd,
				 माप(port_mac_cmd),
				 &port_mac_cmd, &out_size);
	अगर (err || out_size != माप(port_mac_cmd) ||
	    (port_mac_cmd.status &&
	     (port_mac_cmd.status != HINIC_PF_SET_VF_ALREADY || !HINIC_IS_VF(hwअगर)) &&
	     port_mac_cmd.status != HINIC_MGMT_STATUS_EXIST)) अणु
		dev_err(&pdev->dev, "Failed to change MAC, err: %d, status: 0x%x, out size: 0x%x\n",
			err, port_mac_cmd.status, out_size);
		वापस -EFAULT;
	पूर्ण

	अगर (port_mac_cmd.status == HINIC_PF_SET_VF_ALREADY) अणु
		dev_warn(&pdev->dev, "PF has already set VF mac, ignore %s operation\n",
			 (op == MAC_SET) ? "set" : "del");
		वापस HINIC_PF_SET_VF_ALREADY;
	पूर्ण

	अगर (cmd == HINIC_PORT_CMD_SET_MAC && port_mac_cmd.status ==
	    HINIC_MGMT_STATUS_EXIST)
		dev_warn(&pdev->dev, "MAC is repeated, ignore set operation\n");

	वापस 0;
पूर्ण

/**
 * hinic_port_add_mac - add mac address
 * @nic_dev: nic device
 * @addr: mac address
 * @vlan_id: vlan number to set with the mac
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_port_add_mac(काष्ठा hinic_dev *nic_dev,
		       स्थिर u8 *addr, u16 vlan_id)
अणु
	वापस change_mac(nic_dev, addr, vlan_id, MAC_SET);
पूर्ण

/**
 * hinic_port_del_mac - हटाओ mac address
 * @nic_dev: nic device
 * @addr: mac address
 * @vlan_id: vlan number that is connected to the mac
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_port_del_mac(काष्ठा hinic_dev *nic_dev, स्थिर u8 *addr,
		       u16 vlan_id)
अणु
	वापस change_mac(nic_dev, addr, vlan_id, MAC_DEL);
पूर्ण

/**
 * hinic_port_get_mac - get the mac address of the nic device
 * @nic_dev: nic device
 * @addr: वापसed mac address
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_port_get_mac(काष्ठा hinic_dev *nic_dev, u8 *addr)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_port_mac_cmd port_mac_cmd;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	u16 out_size = माप(port_mac_cmd);
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक err;

	port_mac_cmd.func_idx = HINIC_HWIF_FUNC_IDX(hwअगर);

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_MAC,
				 &port_mac_cmd, माप(port_mac_cmd),
				 &port_mac_cmd, &out_size);
	अगर (err || (out_size != माप(port_mac_cmd)) || port_mac_cmd.status) अणु
		dev_err(&pdev->dev, "Failed to get mac, err: %d, status: 0x%x, out size: 0x%x\n",
			err, port_mac_cmd.status, out_size);
		वापस -EFAULT;
	पूर्ण

	स_नकल(addr, port_mac_cmd.mac, ETH_ALEN);
	वापस 0;
पूर्ण

/**
 * hinic_port_set_mtu - set mtu
 * @nic_dev: nic device
 * @new_mtu: new mtu
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_port_set_mtu(काष्ठा hinic_dev *nic_dev, पूर्णांक new_mtu)
अणु
	काष्ठा net_device *netdev = nic_dev->netdev;
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_port_mtu_cmd port_mtu_cmd;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	u16 out_size = माप(port_mtu_cmd);
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक err, max_frame;

	अगर (new_mtu < HINIC_MIN_MTU_SIZE) अणु
		netअगर_err(nic_dev, drv, netdev, "mtu < MIN MTU size");
		वापस -EINVAL;
	पूर्ण

	max_frame = new_mtu + ETH_HLEN + ETH_FCS_LEN;
	अगर (max_frame > HINIC_MAX_JUMBO_FRAME_SIZE) अणु
		netअगर_err(nic_dev, drv, netdev, "mtu > MAX MTU size");
		वापस -EINVAL;
	पूर्ण

	port_mtu_cmd.func_idx = HINIC_HWIF_FUNC_IDX(hwअगर);
	port_mtu_cmd.mtu = new_mtu;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_CHANGE_MTU,
				 &port_mtu_cmd, माप(port_mtu_cmd),
				 &port_mtu_cmd, &out_size);
	अगर (err || out_size != माप(port_mtu_cmd) || port_mtu_cmd.status) अणु
		dev_err(&pdev->dev, "Failed to set mtu, err: %d, status: 0x%x, out size: 0x%x\n",
			err, port_mtu_cmd.status, out_size);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hinic_port_add_vlan - add vlan to the nic device
 * @nic_dev: nic device
 * @vlan_id: the vlan number to add
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_port_add_vlan(काष्ठा hinic_dev *nic_dev, u16 vlan_id)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_port_vlan_cmd port_vlan_cmd;

	port_vlan_cmd.func_idx = HINIC_HWIF_FUNC_IDX(hwdev->hwअगर);
	port_vlan_cmd.vlan_id = vlan_id;

	वापस hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_ADD_VLAN,
				  &port_vlan_cmd, माप(port_vlan_cmd),
				  शून्य, शून्य);
पूर्ण

/**
 * hinic_port_del_vlan - delete vlan from the nic device
 * @nic_dev: nic device
 * @vlan_id: the vlan number to delete
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_port_del_vlan(काष्ठा hinic_dev *nic_dev, u16 vlan_id)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_port_vlan_cmd port_vlan_cmd;

	port_vlan_cmd.func_idx = HINIC_HWIF_FUNC_IDX(hwdev->hwअगर);
	port_vlan_cmd.vlan_id = vlan_id;

	वापस hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_DEL_VLAN,
				 &port_vlan_cmd, माप(port_vlan_cmd),
				 शून्य, शून्य);
पूर्ण

/**
 * hinic_port_set_rx_mode - set rx mode in the nic device
 * @nic_dev: nic device
 * @rx_mode: the rx mode to set
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_port_set_rx_mode(काष्ठा hinic_dev *nic_dev, u32 rx_mode)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_port_rx_mode_cmd rx_mode_cmd;

	rx_mode_cmd.func_idx = HINIC_HWIF_FUNC_IDX(hwdev->hwअगर);
	rx_mode_cmd.rx_mode = rx_mode;

	वापस hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_RX_MODE,
				  &rx_mode_cmd, माप(rx_mode_cmd),
				  शून्य, शून्य);
पूर्ण

/**
 * hinic_port_link_state - get the link state
 * @nic_dev: nic device
 * @link_state: the वापसed link state
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_port_link_state(काष्ठा hinic_dev *nic_dev,
			  क्रमागत hinic_port_link_state *link_state)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा hinic_port_link_cmd link_cmd;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u16 out_size = माप(link_cmd);
	पूर्णांक err;

	link_cmd.func_idx = HINIC_HWIF_FUNC_IDX(hwअगर);

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_LINK_STATE,
				 &link_cmd, माप(link_cmd),
				 &link_cmd, &out_size);
	अगर (err || (out_size != माप(link_cmd)) || link_cmd.status) अणु
		dev_err(&pdev->dev, "Failed to get link state, err: %d, status: 0x%x, out size: 0x%x\n",
			err, link_cmd.status, out_size);
		वापस -EINVAL;
	पूर्ण

	*link_state = link_cmd.state;
	वापस 0;
पूर्ण

/**
 * hinic_port_set_state - set port state
 * @nic_dev: nic device
 * @state: the state to set
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_port_set_state(काष्ठा hinic_dev *nic_dev, क्रमागत hinic_port_state state)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_port_state_cmd port_state;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u16 out_size = माप(port_state);
	पूर्णांक err;

	अगर (HINIC_IS_VF(hwdev->hwअगर))
		वापस 0;

	port_state.state = state;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_PORT_STATE,
				 &port_state, माप(port_state),
				 &port_state, &out_size);
	अगर (err || (out_size != माप(port_state)) || port_state.status) अणु
		dev_err(&pdev->dev, "Failed to set port state, err: %d, status: 0x%x, out size: 0x%x\n",
			err, port_state.status, out_size);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hinic_port_set_func_state- set func device state
 * @nic_dev: nic device
 * @state: the state to set
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_port_set_func_state(काष्ठा hinic_dev *nic_dev,
			      क्रमागत hinic_func_port_state state)
अणु
	काष्ठा hinic_port_func_state_cmd func_state;
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u16 out_size = माप(func_state);
	पूर्णांक err;

	func_state.func_idx = HINIC_HWIF_FUNC_IDX(hwअगर);
	func_state.state = state;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_FUNC_STATE,
				 &func_state, माप(func_state),
				 &func_state, &out_size);
	अगर (err || (out_size != माप(func_state)) || func_state.status) अणु
		dev_err(&pdev->dev, "Failed to set port func state, err: %d, status: 0x%x, out size: 0x%x\n",
			err, func_state.status, out_size);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hinic_port_get_cap - get port capabilities
 * @nic_dev: nic device
 * @port_cap: वापसed port capabilities
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_port_get_cap(काष्ठा hinic_dev *nic_dev,
		       काष्ठा hinic_port_cap *port_cap)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u16 out_size = माप(*port_cap);
	पूर्णांक err;

	port_cap->func_idx = HINIC_HWIF_FUNC_IDX(hwअगर);

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_CAP,
				 port_cap, माप(*port_cap),
				 port_cap, &out_size);
	अगर (err || (out_size != माप(*port_cap)) || port_cap->status) अणु
		dev_err(&pdev->dev,
			"Failed to get port capabilities, err: %d, status: 0x%x, out size: 0x%x\n",
			err, port_cap->status, out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hinic_port_set_tso - set port tso configuration
 * @nic_dev: nic device
 * @state: the tso state to set
 *
 * Return 0 - Success, negative - Failure
 **/
पूर्णांक hinic_port_set_tso(काष्ठा hinic_dev *nic_dev, क्रमागत hinic_tso_state state)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा hinic_tso_config tso_cfg = अणु0पूर्ण;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u16 out_size = माप(tso_cfg);
	पूर्णांक err;

	tso_cfg.func_id = HINIC_HWIF_FUNC_IDX(hwअगर);
	tso_cfg.tso_en = state;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_TSO,
				 &tso_cfg, माप(tso_cfg),
				 &tso_cfg, &out_size);
	अगर (err || out_size != माप(tso_cfg) || tso_cfg.status) अणु
		dev_err(&pdev->dev,
			"Failed to set port tso, err: %d, status: 0x%x, out size: 0x%x\n",
			err, tso_cfg.status, out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_set_rx_csum_offload(काष्ठा hinic_dev *nic_dev, u32 en)
अणु
	काष्ठा hinic_checksum_offload rx_csum_cfg = अणु0पूर्ण;
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	u16 out_size = माप(rx_csum_cfg);
	काष्ठा hinic_hwअगर *hwअगर;
	काष्ठा pci_dev *pdev;
	पूर्णांक err;

	अगर (!hwdev)
		वापस -EINVAL;

	hwअगर = hwdev->hwअगर;
	pdev = hwअगर->pdev;
	rx_csum_cfg.func_id = HINIC_HWIF_FUNC_IDX(hwअगर);
	rx_csum_cfg.rx_csum_offload = en;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_RX_CSUM,
				 &rx_csum_cfg, माप(rx_csum_cfg),
				 &rx_csum_cfg, &out_size);
	अगर (err || !out_size || rx_csum_cfg.status) अणु
		dev_err(&pdev->dev,
			"Failed to set rx csum offload, err: %d, status: 0x%x, out size: 0x%x\n",
			err, rx_csum_cfg.status, out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_set_rx_vlan_offload(काष्ठा hinic_dev *nic_dev, u8 en)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_vlan_cfg vlan_cfg;
	काष्ठा hinic_hwअगर *hwअगर;
	काष्ठा pci_dev *pdev;
	u16 out_size;
	पूर्णांक err;

	अगर (!hwdev)
		वापस -EINVAL;

	out_size = माप(vlan_cfg);
	hwअगर = hwdev->hwअगर;
	pdev = hwअगर->pdev;
	vlan_cfg.func_id = HINIC_HWIF_FUNC_IDX(hwअगर);
	vlan_cfg.vlan_rx_offload = en;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_RX_VLAN_OFFLOAD,
				 &vlan_cfg, माप(vlan_cfg),
				 &vlan_cfg, &out_size);
	अगर (err || !out_size || vlan_cfg.status) अणु
		dev_err(&pdev->dev,
			"Failed to set rx vlan offload, err: %d, status: 0x%x, out size: 0x%x\n",
			err, vlan_cfg.status, out_size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_set_max_qnum(काष्ठा hinic_dev *nic_dev, u8 num_rqs)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा hinic_rq_num rq_num = अणु 0 पूर्ण;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u16 out_size = माप(rq_num);
	पूर्णांक err;

	rq_num.func_id = HINIC_HWIF_FUNC_IDX(hwअगर);
	rq_num.num_rqs = num_rqs;
	rq_num.rq_depth = ilog2(nic_dev->rq_depth);

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_RQ_IQ_MAP,
				 &rq_num, माप(rq_num),
				 &rq_num, &out_size);
	अगर (err || !out_size || rq_num.status) अणु
		dev_err(&pdev->dev,
			"Failed to set rxq number, err: %d, status: 0x%x, out size: 0x%x\n",
			err, rq_num.status, out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_set_rx_lro(काष्ठा hinic_dev *nic_dev, u8 ipv4_en, u8 ipv6_en,
			    u8 max_wqe_num)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_lro_config lro_cfg = अणु 0 पूर्ण;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u16 out_size = माप(lro_cfg);
	पूर्णांक err;

	lro_cfg.func_id = HINIC_HWIF_FUNC_IDX(hwअगर);
	lro_cfg.lro_ipv4_en = ipv4_en;
	lro_cfg.lro_ipv6_en = ipv6_en;
	lro_cfg.lro_max_wqe_num = max_wqe_num;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_LRO,
				 &lro_cfg, माप(lro_cfg),
				 &lro_cfg, &out_size);
	अगर (err || !out_size || lro_cfg.status) अणु
		dev_err(&pdev->dev,
			"Failed to set lro offload, err: %d, status: 0x%x, out size: 0x%x\n",
			err, lro_cfg.status, out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_set_rx_lro_समयr(काष्ठा hinic_dev *nic_dev, u32 समयr_value)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_lro_समयr lro_समयr = अणु 0 पूर्ण;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u16 out_size = माप(lro_समयr);
	पूर्णांक err;

	lro_समयr.status = 0;
	lro_समयr.type = 0;
	lro_समयr.enable = 1;
	lro_समयr.समयr = समयr_value;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_LRO_TIMER,
				 &lro_समयr, माप(lro_समयr),
				 &lro_समयr, &out_size);
	अगर (lro_समयr.status == 0xFF) अणु
		/* For this हाल, we think status (0xFF) is OK */
		lro_समयr.status = 0;
		dev_dbg(&pdev->dev,
			"Set lro timer not supported by the current FW version, it will be 1ms default\n");
	पूर्ण

	अगर (err || !out_size || lro_समयr.status) अणु
		dev_err(&pdev->dev,
			"Failed to set lro timer, err: %d, status: 0x%x, out size: 0x%x\n",
			err, lro_समयr.status, out_size);

		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_set_rx_lro_state(काष्ठा hinic_dev *nic_dev, u8 lro_en,
			   u32 lro_समयr, u32 wqe_num)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	u8 ipv4_en;
	u8 ipv6_en;
	पूर्णांक err;

	अगर (!hwdev)
		वापस -EINVAL;

	ipv4_en = lro_en ? 1 : 0;
	ipv6_en = lro_en ? 1 : 0;

	err = hinic_set_rx_lro(nic_dev, ipv4_en, ipv6_en, (u8)wqe_num);
	अगर (err)
		वापस err;

	अगर (HINIC_IS_VF(nic_dev->hwdev->hwअगर))
		वापस 0;

	err = hinic_set_rx_lro_समयr(nic_dev, lro_समयr);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

पूर्णांक hinic_rss_set_indir_tbl(काष्ठा hinic_dev *nic_dev, u32 पंचांगpl_idx,
			    स्थिर u32 *indir_table)
अणु
	काष्ठा hinic_rss_indirect_tbl *indir_tbl;
	काष्ठा hinic_func_to_io *func_to_io;
	काष्ठा hinic_cmdq_buf cmd_buf;
	काष्ठा hinic_hwdev *hwdev;
	काष्ठा hinic_hwअगर *hwअगर;
	काष्ठा pci_dev *pdev;
	u32 indir_size;
	u64 out_param;
	पूर्णांक err, i;
	u32 *temp;

	hwdev = nic_dev->hwdev;
	func_to_io = &hwdev->func_to_io;
	hwअगर = hwdev->hwअगर;
	pdev = hwअगर->pdev;

	err = hinic_alloc_cmdq_buf(&func_to_io->cmdqs, &cmd_buf);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate cmdq buf\n");
		वापस err;
	पूर्ण

	cmd_buf.size = माप(*indir_tbl);

	indir_tbl = cmd_buf.buf;
	indir_tbl->group_index = cpu_to_be32(पंचांगpl_idx);

	क्रम (i = 0; i < HINIC_RSS_INसूची_SIZE; i++) अणु
		indir_tbl->entry[i] = indir_table[i];

		अगर (0x3 == (i & 0x3)) अणु
			temp = (u32 *)&indir_tbl->entry[i - 3];
			*temp = cpu_to_be32(*temp);
		पूर्ण
	पूर्ण

	/* cfg the rss indirect table by command queue */
	indir_size = HINIC_RSS_INसूची_SIZE / 2;
	indir_tbl->offset = 0;
	indir_tbl->size = cpu_to_be32(indir_size);

	err = hinic_cmdq_direct_resp(&func_to_io->cmdqs, HINIC_MOD_L2NIC,
				     HINIC_UCODE_CMD_SET_RSS_INसूची_TABLE,
				     &cmd_buf, &out_param);
	अगर (err || out_param != 0) अणु
		dev_err(&pdev->dev, "Failed to set rss indir table\n");
		err = -EFAULT;
		जाओ मुक्त_buf;
	पूर्ण

	indir_tbl->offset = cpu_to_be32(indir_size);
	indir_tbl->size = cpu_to_be32(indir_size);
	स_नकल(&indir_tbl->entry[0], &indir_tbl->entry[indir_size], indir_size);

	err = hinic_cmdq_direct_resp(&func_to_io->cmdqs, HINIC_MOD_L2NIC,
				     HINIC_UCODE_CMD_SET_RSS_INसूची_TABLE,
				     &cmd_buf, &out_param);
	अगर (err || out_param != 0) अणु
		dev_err(&pdev->dev, "Failed to set rss indir table\n");
		err = -EFAULT;
	पूर्ण

मुक्त_buf:
	hinic_मुक्त_cmdq_buf(&func_to_io->cmdqs, &cmd_buf);

	वापस err;
पूर्ण

पूर्णांक hinic_rss_get_indir_tbl(काष्ठा hinic_dev *nic_dev, u32 पंचांगpl_idx,
			    u32 *indir_table)
अणु
	काष्ठा hinic_rss_indir_table rss_cfg = अणु 0 पूर्ण;
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u16 out_size = माप(rss_cfg);
	पूर्णांक err = 0, i;

	rss_cfg.func_id = HINIC_HWIF_FUNC_IDX(hwअगर);
	rss_cfg.ढाँचा_id = पंचांगpl_idx;

	err = hinic_port_msg_cmd(hwdev,
				 HINIC_PORT_CMD_GET_RSS_TEMPLATE_INसूची_TBL,
				 &rss_cfg, माप(rss_cfg), &rss_cfg,
				 &out_size);
	अगर (err || !out_size || rss_cfg.status) अणु
		dev_err(&pdev->dev, "Failed to get indir table, err: %d, status: 0x%x, out size: 0x%x\n",
			err, rss_cfg.status, out_size);
		वापस -EINVAL;
	पूर्ण

	hinic_be32_to_cpu(rss_cfg.indir, HINIC_RSS_INसूची_SIZE);
	क्रम (i = 0; i < HINIC_RSS_INसूची_SIZE; i++)
		indir_table[i] = rss_cfg.indir[i];

	वापस 0;
पूर्ण

पूर्णांक hinic_set_rss_type(काष्ठा hinic_dev *nic_dev, u32 पंचांगpl_idx,
		       काष्ठा hinic_rss_type rss_type)
अणु
	काष्ठा hinic_rss_context_tbl *ctx_tbl;
	काष्ठा hinic_func_to_io *func_to_io;
	काष्ठा hinic_cmdq_buf cmd_buf;
	काष्ठा hinic_hwdev *hwdev;
	काष्ठा hinic_hwअगर *hwअगर;
	काष्ठा pci_dev *pdev;
	u64 out_param;
	u32 ctx = 0;
	पूर्णांक err;

	hwdev = nic_dev->hwdev;
	func_to_io = &hwdev->func_to_io;
	hwअगर = hwdev->hwअगर;
	pdev = hwअगर->pdev;

	err = hinic_alloc_cmdq_buf(&func_to_io->cmdqs, &cmd_buf);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to allocate cmd buf\n");
		वापस -ENOMEM;
	पूर्ण

	ctx |=  HINIC_RSS_TYPE_SET(1, VALID) |
		HINIC_RSS_TYPE_SET(rss_type.ipv4, IPV4) |
		HINIC_RSS_TYPE_SET(rss_type.ipv6, IPV6) |
		HINIC_RSS_TYPE_SET(rss_type.ipv6_ext, IPV6_EXT) |
		HINIC_RSS_TYPE_SET(rss_type.tcp_ipv4, TCP_IPV4) |
		HINIC_RSS_TYPE_SET(rss_type.tcp_ipv6, TCP_IPV6) |
		HINIC_RSS_TYPE_SET(rss_type.tcp_ipv6_ext, TCP_IPV6_EXT) |
		HINIC_RSS_TYPE_SET(rss_type.udp_ipv4, UDP_IPV4) |
		HINIC_RSS_TYPE_SET(rss_type.udp_ipv6, UDP_IPV6);

	cmd_buf.size = माप(काष्ठा hinic_rss_context_tbl);

	ctx_tbl = (काष्ठा hinic_rss_context_tbl *)cmd_buf.buf;
	ctx_tbl->group_index = cpu_to_be32(पंचांगpl_idx);
	ctx_tbl->offset = 0;
	ctx_tbl->size = माप(u32);
	ctx_tbl->size = cpu_to_be32(ctx_tbl->size);
	ctx_tbl->rsvd = 0;
	ctx_tbl->ctx = cpu_to_be32(ctx);

	/* cfg the rss context table by command queue */
	err = hinic_cmdq_direct_resp(&func_to_io->cmdqs, HINIC_MOD_L2NIC,
				     HINIC_UCODE_CMD_SET_RSS_CONTEXT_TABLE,
				     &cmd_buf, &out_param);

	hinic_मुक्त_cmdq_buf(&func_to_io->cmdqs, &cmd_buf);

	अगर (err || out_param != 0) अणु
		dev_err(&pdev->dev, "Failed to set rss context table, err: %d\n",
			err);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_get_rss_type(काष्ठा hinic_dev *nic_dev, u32 पंचांगpl_idx,
		       काष्ठा hinic_rss_type *rss_type)
अणु
	काष्ठा hinic_rss_context_table ctx_tbl = अणु 0 पूर्ण;
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	u16 out_size = माप(ctx_tbl);
	काष्ठा hinic_hwअगर *hwअगर;
	काष्ठा pci_dev *pdev;
	पूर्णांक err;

	अगर (!hwdev || !rss_type)
		वापस -EINVAL;

	hwअगर = hwdev->hwअगर;
	pdev = hwअगर->pdev;

	ctx_tbl.func_id = HINIC_HWIF_FUNC_IDX(hwअगर);
	ctx_tbl.ढाँचा_id = पंचांगpl_idx;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_RSS_CTX_TBL,
				 &ctx_tbl, माप(ctx_tbl),
				 &ctx_tbl, &out_size);
	अगर (err || !out_size || ctx_tbl.status) अणु
		dev_err(&pdev->dev, "Failed to get hash type, err: %d, status: 0x%x, out size: 0x%x\n",
			err, ctx_tbl.status, out_size);
		वापस -EINVAL;
	पूर्ण

	rss_type->ipv4          = HINIC_RSS_TYPE_GET(ctx_tbl.context, IPV4);
	rss_type->ipv6          = HINIC_RSS_TYPE_GET(ctx_tbl.context, IPV6);
	rss_type->ipv6_ext      = HINIC_RSS_TYPE_GET(ctx_tbl.context, IPV6_EXT);
	rss_type->tcp_ipv4      = HINIC_RSS_TYPE_GET(ctx_tbl.context, TCP_IPV4);
	rss_type->tcp_ipv6      = HINIC_RSS_TYPE_GET(ctx_tbl.context, TCP_IPV6);
	rss_type->tcp_ipv6_ext  = HINIC_RSS_TYPE_GET(ctx_tbl.context,
						     TCP_IPV6_EXT);
	rss_type->udp_ipv4      = HINIC_RSS_TYPE_GET(ctx_tbl.context, UDP_IPV4);
	rss_type->udp_ipv6      = HINIC_RSS_TYPE_GET(ctx_tbl.context, UDP_IPV6);

	वापस 0;
पूर्ण

पूर्णांक hinic_rss_set_ढाँचा_tbl(काष्ठा hinic_dev *nic_dev, u32 ढाँचा_id,
			       स्थिर u8 *temp)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा hinic_rss_key rss_key = अणु 0 पूर्ण;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u16 out_size = माप(rss_key);
	पूर्णांक err;

	rss_key.func_id = HINIC_HWIF_FUNC_IDX(hwअगर);
	rss_key.ढाँचा_id = ढाँचा_id;
	स_नकल(rss_key.key, temp, HINIC_RSS_KEY_SIZE);

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_RSS_TEMPLATE_TBL,
				 &rss_key, माप(rss_key),
				 &rss_key, &out_size);
	अगर (err || !out_size || rss_key.status) अणु
		dev_err(&pdev->dev,
			"Failed to set rss hash key, err: %d, status: 0x%x, out size: 0x%x\n",
			err, rss_key.status, out_size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_rss_get_ढाँचा_tbl(काष्ठा hinic_dev *nic_dev, u32 पंचांगpl_idx,
			       u8 *temp)
अणु
	काष्ठा hinic_rss_ढाँचा_key temp_key = अणु 0 पूर्ण;
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	u16 out_size = माप(temp_key);
	काष्ठा hinic_hwअगर *hwअगर;
	काष्ठा pci_dev *pdev;
	पूर्णांक err;

	अगर (!hwdev || !temp)
		वापस -EINVAL;

	hwअगर = hwdev->hwअगर;
	pdev = hwअगर->pdev;

	temp_key.func_id = HINIC_HWIF_FUNC_IDX(hwअगर);
	temp_key.ढाँचा_id = पंचांगpl_idx;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_RSS_TEMPLATE_TBL,
				 &temp_key, माप(temp_key),
				 &temp_key, &out_size);
	अगर (err || !out_size || temp_key.status) अणु
		dev_err(&pdev->dev, "Failed to set hash key, err: %d, status: 0x%x, out size: 0x%x\n",
			err, temp_key.status, out_size);
		वापस -EINVAL;
	पूर्ण

	स_नकल(temp, temp_key.key, HINIC_RSS_KEY_SIZE);

	वापस 0;
पूर्ण

पूर्णांक hinic_rss_set_hash_engine(काष्ठा hinic_dev *nic_dev, u8 ढाँचा_id,
			      u8 type)
अणु
	काष्ठा hinic_rss_engine_type rss_engine = अणु 0 पूर्ण;
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u16 out_size = माप(rss_engine);
	पूर्णांक err;

	rss_engine.func_id = HINIC_HWIF_FUNC_IDX(hwअगर);
	rss_engine.hash_engine = type;
	rss_engine.ढाँचा_id = ढाँचा_id;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_RSS_HASH_ENGINE,
				 &rss_engine, माप(rss_engine),
				 &rss_engine, &out_size);
	अगर (err || !out_size || rss_engine.status) अणु
		dev_err(&pdev->dev,
			"Failed to set hash engine, err: %d, status: 0x%x, out size: 0x%x\n",
			err, rss_engine.status, out_size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_rss_get_hash_engine(काष्ठा hinic_dev *nic_dev, u8 पंचांगpl_idx, u8 *type)
अणु
	काष्ठा hinic_rss_engine_type hash_type = अणु 0 पूर्ण;
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	u16 out_size = माप(hash_type);
	काष्ठा hinic_hwअगर *hwअगर;
	काष्ठा pci_dev *pdev;
	पूर्णांक err;

	अगर (!hwdev || !type)
		वापस -EINVAL;

	hwअगर = hwdev->hwअगर;
	pdev = hwअगर->pdev;

	hash_type.func_id = HINIC_HWIF_FUNC_IDX(hwअगर);
	hash_type.ढाँचा_id = पंचांगpl_idx;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_RSS_HASH_ENGINE,
				 &hash_type, माप(hash_type),
				 &hash_type, &out_size);
	अगर (err || !out_size || hash_type.status) अणु
		dev_err(&pdev->dev, "Failed to get hash engine, err: %d, status: 0x%x, out size: 0x%x\n",
			err, hash_type.status, out_size);
		वापस -EINVAL;
	पूर्ण

	*type = hash_type.hash_engine;
	वापस 0;
पूर्ण

पूर्णांक hinic_rss_cfg(काष्ठा hinic_dev *nic_dev, u8 rss_en, u8 ढाँचा_id)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_rss_config rss_cfg = अणु 0 पूर्ण;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	u16 out_size = माप(rss_cfg);
	पूर्णांक err;

	rss_cfg.func_id = HINIC_HWIF_FUNC_IDX(hwअगर);
	rss_cfg.rss_en = rss_en;
	rss_cfg.ढाँचा_id = ढाँचा_id;
	rss_cfg.rq_priority_number = 0;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_RSS_CFG,
				 &rss_cfg, माप(rss_cfg),
				 &rss_cfg, &out_size);
	अगर (err || !out_size || rss_cfg.status) अणु
		dev_err(&pdev->dev,
			"Failed to set rss cfg, err: %d, status: 0x%x, out size: 0x%x\n",
			err, rss_cfg.status, out_size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_rss_ढाँचा_alloc(काष्ठा hinic_dev *nic_dev, u8 *पंचांगpl_idx)
अणु
	काष्ठा hinic_rss_ढाँचा_mgmt ढाँचा_mgmt = अणु 0 पूर्ण;
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	u16 out_size = माप(ढाँचा_mgmt);
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक err;

	ढाँचा_mgmt.func_id = HINIC_HWIF_FUNC_IDX(hwअगर);
	ढाँचा_mgmt.cmd = NIC_RSS_CMD_TEMP_ALLOC;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_RSS_TEMP_MGR,
				 &ढाँचा_mgmt, माप(ढाँचा_mgmt),
				 &ढाँचा_mgmt, &out_size);
	अगर (err || !out_size || ढाँचा_mgmt.status) अणु
		dev_err(&pdev->dev, "Failed to alloc rss template, err: %d, status: 0x%x, out size: 0x%x\n",
			err, ढाँचा_mgmt.status, out_size);
		वापस -EINVAL;
	पूर्ण

	*पंचांगpl_idx = ढाँचा_mgmt.ढाँचा_id;

	वापस 0;
पूर्ण

पूर्णांक hinic_rss_ढाँचा_मुक्त(काष्ठा hinic_dev *nic_dev, u8 पंचांगpl_idx)
अणु
	काष्ठा hinic_rss_ढाँचा_mgmt ढाँचा_mgmt = अणु 0 पूर्ण;
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	u16 out_size = माप(ढाँचा_mgmt);
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक err;

	ढाँचा_mgmt.func_id = HINIC_HWIF_FUNC_IDX(hwअगर);
	ढाँचा_mgmt.ढाँचा_id = पंचांगpl_idx;
	ढाँचा_mgmt.cmd = NIC_RSS_CMD_TEMP_FREE;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_RSS_TEMP_MGR,
				 &ढाँचा_mgmt, माप(ढाँचा_mgmt),
				 &ढाँचा_mgmt, &out_size);
	अगर (err || !out_size || ढाँचा_mgmt.status) अणु
		dev_err(&pdev->dev, "Failed to free rss template, err: %d, status: 0x%x, out size: 0x%x\n",
			err, ढाँचा_mgmt.status, out_size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_get_vport_stats(काष्ठा hinic_dev *nic_dev,
			  काष्ठा hinic_vport_stats *stats)
अणु
	काष्ठा hinic_cmd_vport_stats vport_stats = अणु 0 पूर्ण;
	काष्ठा hinic_port_stats_info stats_info = अणु 0 पूर्ण;
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	u16 out_size = माप(vport_stats);
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक err;

	stats_info.stats_version = HINIC_PORT_STATS_VERSION;
	stats_info.func_id = HINIC_HWIF_FUNC_IDX(hwअगर);
	stats_info.stats_size = माप(vport_stats);

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_VPORT_STAT,
				 &stats_info, माप(stats_info),
				 &vport_stats, &out_size);
	अगर (err || !out_size || vport_stats.status) अणु
		dev_err(&pdev->dev,
			"Failed to get function statistics, err: %d, status: 0x%x, out size: 0x%x\n",
			err, vport_stats.status, out_size);
		वापस -EFAULT;
	पूर्ण

	स_नकल(stats, &vport_stats.stats, माप(*stats));
	वापस 0;
पूर्ण

पूर्णांक hinic_get_phy_port_stats(काष्ठा hinic_dev *nic_dev,
			     काष्ठा hinic_phy_port_stats *stats)
अणु
	काष्ठा hinic_port_stats_info stats_info = अणु 0 पूर्ण;
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा hinic_port_stats *port_stats;
	u16 out_size = माप(*port_stats);
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक err;

	port_stats = kzalloc(माप(*port_stats), GFP_KERNEL);
	अगर (!port_stats)
		वापस -ENOMEM;

	stats_info.stats_version = HINIC_PORT_STATS_VERSION;
	stats_info.stats_size = माप(*port_stats);

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_PORT_STATISTICS,
				 &stats_info, माप(stats_info),
				 port_stats, &out_size);
	अगर (err || !out_size || port_stats->status) अणु
		dev_err(&pdev->dev,
			"Failed to get port statistics, err: %d, status: 0x%x, out size: 0x%x\n",
			err, port_stats->status, out_size);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	स_नकल(stats, &port_stats->stats, माप(*stats));

out:
	kमुक्त(port_stats);

	वापस err;
पूर्ण

पूर्णांक hinic_get_mgmt_version(काष्ठा hinic_dev *nic_dev, u8 *mgmt_ver)
अणु
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_version_info up_ver = अणु0पूर्ण;
	u16 out_size = माप(up_ver);
	काष्ठा hinic_hwअगर *hwअगर;
	काष्ठा pci_dev *pdev;
	पूर्णांक err;

	अगर (!hwdev)
		वापस -EINVAL;

	hwअगर = hwdev->hwअगर;
	pdev = hwअगर->pdev;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_MGMT_VERSION,
				 &up_ver, माप(up_ver), &up_ver,
				 &out_size);
	अगर (err || !out_size || up_ver.status) अणु
		dev_err(&pdev->dev,
			"Failed to get mgmt version, err: %d, status: 0x%x, out size: 0x%x\n",
			err, up_ver.status, out_size);
		वापस -EINVAL;
	पूर्ण

	snम_लिखो(mgmt_ver, HINIC_MGMT_VERSION_MAX_LEN, "%s", up_ver.ver);

	वापस 0;
पूर्ण

पूर्णांक hinic_get_link_mode(काष्ठा hinic_hwdev *hwdev,
			काष्ठा hinic_link_mode_cmd *link_mode)
अणु
	u16 out_size;
	पूर्णांक err;

	अगर (!hwdev || !link_mode)
		वापस -EINVAL;

	link_mode->func_id = HINIC_HWIF_FUNC_IDX(hwdev->hwअगर);
	out_size = माप(*link_mode);

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_LINK_MODE,
				 link_mode, माप(*link_mode),
				 link_mode, &out_size);
	अगर (err || !out_size || link_mode->status) अणु
		dev_err(&hwdev->hwअगर->pdev->dev,
			"Failed to get link mode, err: %d, status: 0x%x, out size: 0x%x\n",
			err, link_mode->status, out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_set_स्वतःneg(काष्ठा hinic_hwdev *hwdev, bool enable)
अणु
	काष्ठा hinic_set_स्वतःneg_cmd स्वतःneg = अणु0पूर्ण;
	u16 out_size = माप(स्वतःneg);
	पूर्णांक err;

	अगर (!hwdev)
		वापस -EINVAL;

	स्वतःneg.func_id = HINIC_HWIF_FUNC_IDX(hwdev->hwअगर);
	स्वतःneg.enable = enable;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_AUTONEG,
				 &स्वतःneg, माप(स्वतःneg),
				 &स्वतःneg, &out_size);
	अगर (err || !out_size || स्वतःneg.status) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to %s autoneg, err: %d, status: 0x%x, out size: 0x%x\n",
			enable ? "enable" : "disable", err, स्वतःneg.status,
			out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_set_speed(काष्ठा hinic_hwdev *hwdev, क्रमागत nic_speed_level speed)
अणु
	काष्ठा hinic_speed_cmd speed_info = अणु0पूर्ण;
	u16 out_size = माप(speed_info);
	पूर्णांक err;

	अगर (!hwdev)
		वापस -EINVAL;

	speed_info.func_id = HINIC_HWIF_FUNC_IDX(hwdev->hwअगर);
	speed_info.speed = speed;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_SPEED,
				 &speed_info, माप(speed_info),
				 &speed_info, &out_size);
	अगर (err || !out_size || speed_info.status) अणु
		dev_err(&hwdev->hwअगर->pdev->dev,
			"Failed to set speed, err: %d, status: 0x%x, out size: 0x%x\n",
			err, speed_info.status, out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_set_link_settings(काष्ठा hinic_hwdev *hwdev,
			    काष्ठा hinic_link_ksettings_info *info)
अणु
	u16 out_size = माप(*info);
	पूर्णांक err;

	err = hinic_hilink_msg_cmd(hwdev, HINIC_HILINK_CMD_SET_LINK_SETTINGS,
				   info, माप(*info), info, &out_size);
	अगर ((info->status != HINIC_MGMT_CMD_UNSUPPORTED &&
	     info->status) || err || !out_size) अणु
		dev_err(&hwdev->hwअगर->pdev->dev,
			"Failed to set link settings, err: %d, status: 0x%x, out size: 0x%x\n",
			err, info->status, out_size);
		वापस -EFAULT;
	पूर्ण

	वापस info->status;
पूर्ण

पूर्णांक hinic_get_hw_छोड़ो_info(काष्ठा hinic_hwdev *hwdev,
			    काष्ठा hinic_छोड़ो_config *छोड़ो_info)
अणु
	u16 out_size = माप(*छोड़ो_info);
	पूर्णांक err;

	छोड़ो_info->func_id = HINIC_HWIF_FUNC_IDX(hwdev->hwअगर);

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_PAUSE_INFO,
				 छोड़ो_info, माप(*छोड़ो_info),
				 छोड़ो_info, &out_size);
	अगर (err || !out_size || छोड़ो_info->status) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to get pause info, err: %d, status: 0x%x, out size: 0x%x\n",
			err, छोड़ो_info->status, out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_set_hw_छोड़ो_info(काष्ठा hinic_hwdev *hwdev,
			    काष्ठा hinic_छोड़ो_config *छोड़ो_info)
अणु
	u16 out_size = माप(*छोड़ो_info);
	पूर्णांक err;

	छोड़ो_info->func_id = HINIC_HWIF_FUNC_IDX(hwdev->hwअगर);

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_PAUSE_INFO,
				 छोड़ो_info, माप(*छोड़ो_info),
				 छोड़ो_info, &out_size);
	अगर (err || !out_size || छोड़ो_info->status) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to set pause info, err: %d, status: 0x%x, out size: 0x%x\n",
			err, छोड़ो_info->status, out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_dcb_set_pfc(काष्ठा hinic_hwdev *hwdev, u8 pfc_en, u8 pfc_biपंचांगap)
अणु
	काष्ठा hinic_nic_cfg *nic_cfg = &hwdev->func_to_io.nic_cfg;
	काष्ठा hinic_set_pfc pfc = अणु0पूर्ण;
	u16 out_size = माप(pfc);
	पूर्णांक err;

	अगर (HINIC_IS_VF(hwdev->hwअगर))
		वापस 0;

	mutex_lock(&nic_cfg->cfg_mutex);

	pfc.func_id = HINIC_HWIF_FUNC_IDX(hwdev->hwअगर);
	pfc.pfc_biपंचांगap = pfc_biपंचांगap;
	pfc.pfc_en = pfc_en;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_PFC,
				 &pfc, माप(pfc), &pfc, &out_size);
	अगर (err || pfc.status || !out_size) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to %s pfc, err: %d, status: 0x%x, out size: 0x%x\n",
			pfc_en ? "enable" : "disable", err, pfc.status,
			out_size);
		mutex_unlock(&nic_cfg->cfg_mutex);
		वापस -EIO;
	पूर्ण

	/* छोड़ो settings is opposite from pfc */
	nic_cfg->rx_छोड़ो = pfc_en ? 0 : 1;
	nic_cfg->tx_छोड़ो = pfc_en ? 0 : 1;

	mutex_unlock(&nic_cfg->cfg_mutex);

	वापस 0;
पूर्ण

पूर्णांक hinic_set_loopback_mode(काष्ठा hinic_hwdev *hwdev, u32 mode, u32 enable)
अणु
	काष्ठा hinic_port_loopback lb = अणु0पूर्ण;
	u16 out_size = माप(lb);
	पूर्णांक err;

	lb.mode = mode;
	lb.en = enable;

	अगर (mode < LOOP_MODE_MIN || mode > LOOP_MODE_MAX) अणु
		dev_err(&hwdev->hwअगर->pdev->dev,
			"Invalid loopback mode %d to set\n", mode);
		वापस -EINVAL;
	पूर्ण

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_LOOPBACK_MODE,
				 &lb, माप(lb), &lb, &out_size);
	अगर (err || !out_size || lb.status) अणु
		dev_err(&hwdev->hwअगर->pdev->dev,
			"Failed to set loopback mode %d en %d, err: %d, status: 0x%x, out size: 0x%x\n",
			mode, enable, err, lb.status, out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _set_led_status(काष्ठा hinic_hwdev *hwdev, u8 port,
			   क्रमागत hinic_led_type type,
			   क्रमागत hinic_led_mode mode, u8 reset)
अणु
	काष्ठा hinic_led_info led_info = अणु0पूर्ण;
	u16 out_size = माप(led_info);
	काष्ठा hinic_pfhwdev *pfhwdev;
	पूर्णांक err;

	pfhwdev = container_of(hwdev, काष्ठा hinic_pfhwdev, hwdev);

	led_info.port = port;
	led_info.reset = reset;

	led_info.type = type;
	led_info.mode = mode;

	err = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				HINIC_COMM_CMD_SET_LED_STATUS,
				&led_info, माप(led_info),
				&led_info, &out_size, HINIC_MGMT_MSG_SYNC);
	अगर (err || led_info.status || !out_size) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to set led status, err: %d, status: 0x%x, out size: 0x%x\n",
			err, led_info.status, out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_set_led_status(काष्ठा hinic_hwdev *hwdev, u8 port,
			 क्रमागत hinic_led_type type, क्रमागत hinic_led_mode mode)
अणु
	अगर (!hwdev)
		वापस -EINVAL;

	वापस _set_led_status(hwdev, port, type, mode, 0);
पूर्ण

पूर्णांक hinic_reset_led_status(काष्ठा hinic_hwdev *hwdev, u8 port)
अणु
	पूर्णांक err;

	अगर (!hwdev)
		वापस -EINVAL;

	err = _set_led_status(hwdev, port, HINIC_LED_TYPE_INVALID,
			      HINIC_LED_MODE_INVALID, 1);
	अगर (err)
		dev_err(&hwdev->hwअगर->pdev->dev,
			"Failed to reset led status\n");

	वापस err;
पूर्ण

अटल bool hinic_अगर_sfp_असलent(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_cmd_get_light_module_असल sfp_असल = अणु0पूर्ण;
	u16 out_size = माप(sfp_असल);
	u8 port_id = hwdev->port_id;
	पूर्णांक err;

	sfp_असल.port_id = port_id;
	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_SFP_ABS,
				 &sfp_असल, माप(sfp_असल), &sfp_असल,
				 &out_size);
	अगर (sfp_असल.status || err || !out_size) अणु
		dev_err(&hwdev->hwअगर->pdev->dev,
			"Failed to get port%d sfp absent status, err: %d, status: 0x%x, out size: 0x%x\n",
			port_id, err, sfp_असल.status, out_size);
		वापस true;
	पूर्ण

	वापस ((sfp_असल.असल_status == 0) ? false : true);
पूर्ण

पूर्णांक hinic_get_sfp_eeprom(काष्ठा hinic_hwdev *hwdev, u8 *data, u16 *len)
अणु
	काष्ठा hinic_cmd_get_std_sfp_info sfp_info = अणु0पूर्ण;
	u16 out_size = माप(sfp_info);
	u8 port_id;
	पूर्णांक err;

	अगर (!hwdev || !data || !len)
		वापस -EINVAL;

	port_id = hwdev->port_id;

	अगर (hinic_अगर_sfp_असलent(hwdev))
		वापस -ENXIO;

	sfp_info.port_id = port_id;
	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_STD_SFP_INFO,
				 &sfp_info, माप(sfp_info), &sfp_info,
				 &out_size);
	अगर (sfp_info.status || err || !out_size) अणु
		dev_err(&hwdev->hwअगर->pdev->dev,
			"Failed to get port%d sfp eeprom information, err: %d, status: 0x%x, out size: 0x%x\n",
			port_id, err, sfp_info.status, out_size);
		वापस -EIO;
	पूर्ण

	*len = min_t(u16, sfp_info.eeprom_len, STD_SFP_INFO_MAX_SIZE);
	स_नकल(data, sfp_info.sfp_info, STD_SFP_INFO_MAX_SIZE);

	वापस 0;
पूर्ण

पूर्णांक hinic_get_sfp_type(काष्ठा hinic_hwdev *hwdev, u8 *data0, u8 *data1)
अणु
	u8 sfp_data[STD_SFP_INFO_MAX_SIZE];
	u16 len;
	पूर्णांक err;

	अगर (hinic_अगर_sfp_असलent(hwdev))
		वापस -ENXIO;

	err = hinic_get_sfp_eeprom(hwdev, sfp_data, &len);
	अगर (err)
		वापस err;

	*data0 = sfp_data[0];
	*data1 = sfp_data[1];

	वापस 0;
पूर्ण
