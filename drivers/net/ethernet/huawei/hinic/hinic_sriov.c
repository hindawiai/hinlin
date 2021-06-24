<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#समावेश <linux/pci.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/netdevice.h>

#समावेश "hinic_hw_dev.h"
#समावेश "hinic_dev.h"
#समावेश "hinic_hw_mbox.h"
#समावेश "hinic_hw_cmdq.h"
#समावेश "hinic_port.h"
#समावेश "hinic_sriov.h"

अटल अचिन्हित अक्षर set_vf_link_state;
module_param(set_vf_link_state, byte, 0444);
MODULE_PARM_DESC(set_vf_link_state, "Set vf link state, 0 represents link auto, 1 represents link always up, 2 represents link always down. - default is 0.");

#घोषणा HINIC_VLAN_PRIORITY_SHIFT 13
#घोषणा HINIC_ADD_VLAN_IN_MAC 0x8000
#घोषणा HINIC_TX_RATE_TABLE_FULL 12

अटल पूर्णांक hinic_set_mac(काष्ठा hinic_hwdev *hwdev, स्थिर u8 *mac_addr,
			 u16 vlan_id, u16 func_id)
अणु
	काष्ठा hinic_port_mac_cmd mac_info = अणु0पूर्ण;
	u16 out_size = माप(mac_info);
	पूर्णांक err;

	mac_info.func_idx = func_id;
	mac_info.vlan_id = vlan_id;
	स_नकल(mac_info.mac, mac_addr, ETH_ALEN);

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_MAC, &mac_info,
				 माप(mac_info), &mac_info, &out_size);
	अगर (err || out_size != माप(mac_info) ||
	    (mac_info.status && mac_info.status != HINIC_MGMT_STATUS_EXIST)) अणु
		dev_err(&hwdev->func_to_पन.सwअगर->pdev->dev, "Failed to set MAC, err: %d, status: 0x%x, out size: 0x%x\n",
			err, mac_info.status, out_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hinic_notअगरy_vf_link_status(काष्ठा hinic_hwdev *hwdev, u16 vf_id,
					u8 link_status)
अणु
	काष्ठा vf_data_storage *vf_infos = hwdev->func_to_io.vf_infos;
	काष्ठा hinic_port_link_status link = अणु0पूर्ण;
	u16 out_size = माप(link);
	पूर्णांक err;

	अगर (vf_infos[HW_VF_ID_TO_OS(vf_id)].रेजिस्टरed) अणु
		link.link = link_status;
		link.func_id = hinic_glb_pf_vf_offset(hwdev->hwअगर) + vf_id;
		err = hinic_mbox_to_vf(hwdev, HINIC_MOD_L2NIC,
				       vf_id, HINIC_PORT_CMD_LINK_STATUS_REPORT,
				       &link, माप(link),
				       &link, &out_size, 0);
		अगर (err || !out_size || link.status)
			dev_err(&hwdev->hwअगर->pdev->dev,
				"Send link change event to VF %d failed, err: %d, status: 0x%x, out_size: 0x%x\n",
				HW_VF_ID_TO_OS(vf_id), err,
				link.status, out_size);
	पूर्ण
पूर्ण

/* send link change event mbox msg to active vfs under the pf */
व्योम hinic_notअगरy_all_vfs_link_changed(काष्ठा hinic_hwdev *hwdev,
				       u8 link_status)
अणु
	काष्ठा hinic_func_to_io *nic_io = &hwdev->func_to_io;
	u16 i;

	nic_io->link_status = link_status;
	क्रम (i = 1; i <= nic_io->max_vfs; i++) अणु
		अगर (!nic_io->vf_infos[HW_VF_ID_TO_OS(i)].link_क्रमced)
			hinic_notअगरy_vf_link_status(hwdev, i,  link_status);
	पूर्ण
पूर्ण

अटल u16 hinic_vf_info_vlanprio(काष्ठा hinic_hwdev *hwdev, पूर्णांक vf_id)
अणु
	काष्ठा hinic_func_to_io *nic_io = &hwdev->func_to_io;
	u16 pf_vlan, vlanprio;
	u8 pf_qos;

	pf_vlan = nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_vlan;
	pf_qos = nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_qos;
	vlanprio = pf_vlan | pf_qos << HINIC_VLAN_PRIORITY_SHIFT;

	वापस vlanprio;
पूर्ण

अटल पूर्णांक hinic_set_vf_vlan(काष्ठा hinic_hwdev *hwdev, bool add, u16 vid,
			     u8 qos, पूर्णांक vf_id)
अणु
	काष्ठा hinic_vf_vlan_config vf_vlan = अणु0पूर्ण;
	u16 out_size = माप(vf_vlan);
	पूर्णांक err;
	u8 cmd;

	/* VLAN 0 is a special हाल, करोn't allow it to be हटाओd */
	अगर (!vid && !add)
		वापस 0;

	vf_vlan.func_id = hinic_glb_pf_vf_offset(hwdev->hwअगर) + vf_id;
	vf_vlan.vlan_id = vid;
	vf_vlan.qos = qos;

	अगर (add)
		cmd = HINIC_PORT_CMD_SET_VF_VLAN;
	अन्यथा
		cmd = HINIC_PORT_CMD_CLR_VF_VLAN;

	err = hinic_port_msg_cmd(hwdev, cmd, &vf_vlan,
				 माप(vf_vlan), &vf_vlan, &out_size);
	अगर (err || !out_size || vf_vlan.status) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to set VF %d vlan, err: %d, status: 0x%x, out size: 0x%x\n",
			HW_VF_ID_TO_OS(vf_id), err, vf_vlan.status, out_size);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_set_vf_tx_rate_max_min(काष्ठा hinic_hwdev *hwdev, u16 vf_id,
					u32 max_rate, u32 min_rate)
अणु
	काष्ठा hinic_func_to_io *nic_io = &hwdev->func_to_io;
	काष्ठा hinic_tx_rate_cfg_max_min rate_cfg = अणु0पूर्ण;
	u16 out_size = माप(rate_cfg);
	पूर्णांक err;

	rate_cfg.func_id = hinic_glb_pf_vf_offset(hwdev->hwअगर) + vf_id;
	rate_cfg.max_rate = max_rate;
	rate_cfg.min_rate = min_rate;
	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_VF_MAX_MIN_RATE,
				 &rate_cfg, माप(rate_cfg), &rate_cfg,
				 &out_size);
	अगर ((rate_cfg.status != HINIC_MGMT_CMD_UNSUPPORTED &&
	     rate_cfg.status) || err || !out_size) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to set VF(%d) max rate(%d), min rate(%d), err: %d, status: 0x%x, out size: 0x%x\n",
			HW_VF_ID_TO_OS(vf_id), max_rate, min_rate, err,
			rate_cfg.status, out_size);
		वापस -EIO;
	पूर्ण

	अगर (!rate_cfg.status) अणु
		nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].max_rate = max_rate;
		nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].min_rate = min_rate;
	पूर्ण

	वापस rate_cfg.status;
पूर्ण

अटल पूर्णांक hinic_set_vf_rate_limit(काष्ठा hinic_hwdev *hwdev, u16 vf_id,
				   u32 tx_rate)
अणु
	काष्ठा hinic_func_to_io *nic_io = &hwdev->func_to_io;
	काष्ठा hinic_tx_rate_cfg rate_cfg = अणु0पूर्ण;
	u16 out_size = माप(rate_cfg);
	पूर्णांक err;

	rate_cfg.func_id = hinic_glb_pf_vf_offset(hwdev->hwअगर) + vf_id;
	rate_cfg.tx_rate = tx_rate;
	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_SET_VF_RATE,
				 &rate_cfg, माप(rate_cfg), &rate_cfg,
				 &out_size);
	अगर (err || !out_size || rate_cfg.status) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to set VF(%d) rate(%d), err: %d, status: 0x%x, out size: 0x%x\n",
			HW_VF_ID_TO_OS(vf_id), tx_rate, err, rate_cfg.status,
			out_size);
		अगर (rate_cfg.status)
			वापस rate_cfg.status;

		वापस -EIO;
	पूर्ण

	nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].max_rate = tx_rate;
	nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].min_rate = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_set_vf_tx_rate(काष्ठा hinic_hwdev *hwdev, u16 vf_id,
				u32 max_rate, u32 min_rate)
अणु
	पूर्णांक err;

	err = hinic_set_vf_tx_rate_max_min(hwdev, vf_id, max_rate, min_rate);
	अगर (err != HINIC_MGMT_CMD_UNSUPPORTED)
		वापस err;

	अगर (min_rate) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Current firmware doesn't support to set min tx rate\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	dev_info(&hwdev->hwअगर->pdev->dev, "Current firmware doesn't support to set min tx rate, force min_tx_rate = max_tx_rate\n");

	वापस hinic_set_vf_rate_limit(hwdev, vf_id, max_rate);
पूर्ण

अटल पूर्णांक hinic_init_vf_config(काष्ठा hinic_hwdev *hwdev, u16 vf_id)
अणु
	काष्ठा vf_data_storage *vf_info;
	u16 func_id, vlan_id;
	पूर्णांक err = 0;

	vf_info = hwdev->func_to_io.vf_infos + HW_VF_ID_TO_OS(vf_id);
	अगर (vf_info->pf_set_mac) अणु
		func_id = hinic_glb_pf_vf_offset(hwdev->hwअगर) + vf_id;

		vlan_id = 0;

		err = hinic_set_mac(hwdev, vf_info->vf_mac_addr, vlan_id,
				    func_id);
		अगर (err) अणु
			dev_err(&hwdev->func_to_पन.सwअगर->pdev->dev, "Failed to set VF %d MAC\n",
				HW_VF_ID_TO_OS(vf_id));
			वापस err;
		पूर्ण
	पूर्ण

	अगर (hinic_vf_info_vlanprio(hwdev, vf_id)) अणु
		err = hinic_set_vf_vlan(hwdev, true, vf_info->pf_vlan,
					vf_info->pf_qos, vf_id);
		अगर (err) अणु
			dev_err(&hwdev->hwअगर->pdev->dev, "Failed to add VF %d VLAN_QOS\n",
				HW_VF_ID_TO_OS(vf_id));
			वापस err;
		पूर्ण
	पूर्ण

	अगर (vf_info->max_rate) अणु
		err = hinic_set_vf_tx_rate(hwdev, vf_id, vf_info->max_rate,
					   vf_info->min_rate);
		अगर (err) अणु
			dev_err(&hwdev->hwअगर->pdev->dev, "Failed to set VF %d max rate: %d, min rate: %d\n",
				HW_VF_ID_TO_OS(vf_id), vf_info->max_rate,
				vf_info->min_rate);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_रेजिस्टर_vf_msg_handler(व्योम *hwdev, u16 vf_id,
					 व्योम *buf_in, u16 in_size,
					 व्योम *buf_out, u16 *out_size)
अणु
	काष्ठा hinic_रेजिस्टर_vf *रेजिस्टर_info = buf_out;
	काष्ठा hinic_hwdev *hw_dev = hwdev;
	काष्ठा hinic_func_to_io *nic_io;
	पूर्णांक err;

	nic_io = &hw_dev->func_to_io;
	अगर (vf_id > nic_io->max_vfs) अणु
		dev_err(&hw_dev->hwअगर->pdev->dev, "Register VF id %d exceed limit[0-%d]\n",
			HW_VF_ID_TO_OS(vf_id), HW_VF_ID_TO_OS(nic_io->max_vfs));
		रेजिस्टर_info->status = EFAULT;
		वापस -EFAULT;
	पूर्ण

	*out_size = माप(*रेजिस्टर_info);
	err = hinic_init_vf_config(hw_dev, vf_id);
	अगर (err) अणु
		रेजिस्टर_info->status = EFAULT;
		वापस err;
	पूर्ण

	nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].रेजिस्टरed = true;

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_unरेजिस्टर_vf_msg_handler(व्योम *hwdev, u16 vf_id,
					   व्योम *buf_in, u16 in_size,
					   व्योम *buf_out, u16 *out_size)
अणु
	काष्ठा hinic_hwdev *hw_dev = hwdev;
	काष्ठा hinic_func_to_io *nic_io;

	nic_io = &hw_dev->func_to_io;
	*out_size = 0;
	अगर (vf_id > nic_io->max_vfs)
		वापस 0;

	nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].रेजिस्टरed = false;

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_change_vf_mtu_msg_handler(व्योम *hwdev, u16 vf_id,
					   व्योम *buf_in, u16 in_size,
					   व्योम *buf_out, u16 *out_size)
अणु
	काष्ठा hinic_hwdev *hw_dev = hwdev;
	पूर्णांक err;

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_CHANGE_MTU, buf_in,
				 in_size, buf_out, out_size);
	अगर (err) अणु
		dev_err(&hw_dev->hwअगर->pdev->dev, "Failed to set VF %u mtu\n",
			vf_id);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_get_vf_mac_msg_handler(व्योम *hwdev, u16 vf_id,
					व्योम *buf_in, u16 in_size,
					व्योम *buf_out, u16 *out_size)
अणु
	काष्ठा hinic_port_mac_cmd *mac_info = buf_out;
	काष्ठा hinic_hwdev *dev = hwdev;
	काष्ठा hinic_func_to_io *nic_io;
	काष्ठा vf_data_storage *vf_info;

	nic_io = &dev->func_to_io;
	vf_info = nic_io->vf_infos + HW_VF_ID_TO_OS(vf_id);

	स_नकल(mac_info->mac, vf_info->vf_mac_addr, ETH_ALEN);
	mac_info->status = 0;
	*out_size = माप(*mac_info);

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_set_vf_mac_msg_handler(व्योम *hwdev, u16 vf_id,
					व्योम *buf_in, u16 in_size,
					व्योम *buf_out, u16 *out_size)
अणु
	काष्ठा hinic_port_mac_cmd *mac_out = buf_out;
	काष्ठा hinic_port_mac_cmd *mac_in = buf_in;
	काष्ठा hinic_hwdev *hw_dev = hwdev;
	काष्ठा hinic_func_to_io *nic_io;
	काष्ठा vf_data_storage *vf_info;
	पूर्णांक err;

	nic_io =  &hw_dev->func_to_io;
	vf_info = nic_io->vf_infos + HW_VF_ID_TO_OS(vf_id);
	अगर (vf_info->pf_set_mac && !(vf_info->trust) &&
	    is_valid_ether_addr(mac_in->mac)) अणु
		dev_warn(&hw_dev->hwअगर->pdev->dev, "PF has already set VF %d MAC address\n",
			 HW_VF_ID_TO_OS(vf_id));
		mac_out->status = HINIC_PF_SET_VF_ALREADY;
		*out_size = माप(*mac_out);
		वापस 0;
	पूर्ण

	err = hinic_port_msg_cmd(hw_dev, HINIC_PORT_CMD_SET_MAC, buf_in,
				 in_size, buf_out, out_size);
	अगर ((err &&  err != HINIC_MBOX_PF_BUSY_ACTIVE_FW) || !(*out_size)) अणु
		dev_err(&hw_dev->hwअगर->pdev->dev,
			"Failed to set VF %d MAC address, err: %d, status: 0x%x, out size: 0x%x\n",
			HW_VF_ID_TO_OS(vf_id), err, mac_out->status, *out_size);
		वापस -EFAULT;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक hinic_del_vf_mac_msg_handler(व्योम *hwdev, u16 vf_id,
					व्योम *buf_in, u16 in_size,
					व्योम *buf_out, u16 *out_size)
अणु
	काष्ठा hinic_port_mac_cmd *mac_out = buf_out;
	काष्ठा hinic_port_mac_cmd *mac_in = buf_in;
	काष्ठा hinic_hwdev *hw_dev = hwdev;
	काष्ठा hinic_func_to_io *nic_io;
	काष्ठा vf_data_storage *vf_info;
	पूर्णांक err;

	nic_io = &hw_dev->func_to_io;
	vf_info = nic_io->vf_infos + HW_VF_ID_TO_OS(vf_id);
	अगर (vf_info->pf_set_mac && is_valid_ether_addr(mac_in->mac) &&
	    !स_भेद(vf_info->vf_mac_addr, mac_in->mac, ETH_ALEN)) अणु
		dev_warn(&hw_dev->hwअगर->pdev->dev, "PF has already set VF mac.\n");
		mac_out->status = HINIC_PF_SET_VF_ALREADY;
		*out_size = माप(*mac_out);
		वापस 0;
	पूर्ण

	err = hinic_port_msg_cmd(hw_dev, HINIC_PORT_CMD_DEL_MAC, buf_in,
				 in_size, buf_out, out_size);
	अगर ((err && err != HINIC_MBOX_PF_BUSY_ACTIVE_FW) || !(*out_size)) अणु
		dev_err(&hw_dev->hwअगर->pdev->dev, "Failed to delete VF %d MAC, err: %d, status: 0x%x, out size: 0x%x\n",
			HW_VF_ID_TO_OS(vf_id), err, mac_out->status, *out_size);
		वापस -EFAULT;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक hinic_get_vf_link_status_msg_handler(व्योम *hwdev, u16 vf_id,
						व्योम *buf_in, u16 in_size,
						व्योम *buf_out, u16 *out_size)
अणु
	काष्ठा hinic_port_link_cmd *get_link = buf_out;
	काष्ठा hinic_hwdev *hw_dev = hwdev;
	काष्ठा vf_data_storage *vf_infos;
	काष्ठा hinic_func_to_io *nic_io;
	bool link_क्रमced, link_up;

	nic_io = &hw_dev->func_to_io;
	vf_infos = nic_io->vf_infos;
	link_क्रमced = vf_infos[HW_VF_ID_TO_OS(vf_id)].link_क्रमced;
	link_up = vf_infos[HW_VF_ID_TO_OS(vf_id)].link_up;

	अगर (link_क्रमced)
		get_link->state = link_up ?
			HINIC_LINK_STATE_UP : HINIC_LINK_STATE_DOWN;
	अन्यथा
		get_link->state = nic_io->link_status;

	get_link->status = 0;
	*out_size = माप(*get_link);

	वापस 0;
पूर्ण

अटल bool check_func_table(काष्ठा hinic_hwdev *hwdev, u16 func_idx,
			     व्योम *buf_in, u16 in_size)
अणु
	काष्ठा hinic_cmd_fw_ctxt *function_table = buf_in;

	अगर (!hinic_mbox_check_func_id_8B(hwdev, func_idx, buf_in, in_size) ||
	    !function_table->rx_buf_sz)
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा vf_cmd_msg_handle nic_vf_cmd_msg_handler[] = अणु
	अणुHINIC_PORT_CMD_VF_REGISTER, hinic_रेजिस्टर_vf_msg_handlerपूर्ण,
	अणुHINIC_PORT_CMD_VF_UNREGISTER, hinic_unरेजिस्टर_vf_msg_handlerपूर्ण,
	अणुHINIC_PORT_CMD_CHANGE_MTU, hinic_change_vf_mtu_msg_handlerपूर्ण,
	अणुHINIC_PORT_CMD_GET_MAC, hinic_get_vf_mac_msg_handlerपूर्ण,
	अणुHINIC_PORT_CMD_SET_MAC, hinic_set_vf_mac_msg_handlerपूर्ण,
	अणुHINIC_PORT_CMD_DEL_MAC, hinic_del_vf_mac_msg_handlerपूर्ण,
	अणुHINIC_PORT_CMD_GET_LINK_STATE, hinic_get_vf_link_status_msg_handlerपूर्ण,
पूर्ण;

अटल काष्ठा vf_cmd_check_handle nic_cmd_support_vf[] = अणु
	अणुHINIC_PORT_CMD_VF_REGISTER, शून्यपूर्ण,
	अणुHINIC_PORT_CMD_VF_UNREGISTER, शून्यपूर्ण,
	अणुHINIC_PORT_CMD_CHANGE_MTU, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_ADD_VLAN, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_DEL_VLAN, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_SET_MAC, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_GET_MAC, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_DEL_MAC, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_SET_RX_MODE, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_GET_PAUSE_INFO, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_GET_LINK_STATE, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_SET_LRO, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_SET_RX_CSUM, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_SET_RX_VLAN_OFFLOAD, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_GET_VPORT_STAT, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_CLEAN_VPORT_STAT, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_GET_RSS_TEMPLATE_INसूची_TBL,
	 hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_SET_RSS_TEMPLATE_TBL, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_GET_RSS_TEMPLATE_TBL, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_SET_RSS_HASH_ENGINE, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_GET_RSS_HASH_ENGINE, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_GET_RSS_CTX_TBL, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_SET_RSS_CTX_TBL, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_RSS_TEMP_MGR, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_RSS_CFG, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_FWCTXT_INIT, check_func_tableपूर्ण,
	अणुHINIC_PORT_CMD_GET_MGMT_VERSION, शून्यपूर्ण,
	अणुHINIC_PORT_CMD_SET_FUNC_STATE, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_GET_GLOBAL_QPN, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_SET_TSO, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_SET_RQ_IQ_MAP, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_LINK_STATUS_REPORT, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_UPDATE_MAC, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_GET_CAP, hinic_mbox_check_func_id_8Bपूर्ण,
	अणुHINIC_PORT_CMD_GET_LINK_MODE, hinic_mbox_check_func_id_8Bपूर्ण,
पूर्ण;

#घोषणा CHECK_IPSU_15BIT	0X8000

अटल
काष्ठा hinic_sriov_info *hinic_get_sriov_info_by_pcidev(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);

	वापस &nic_dev->sriov_info;
पूर्ण

अटल पूर्णांक hinic_check_mac_info(u8 status, u16 vlan_id)
अणु
	अगर ((status && status != HINIC_MGMT_STATUS_EXIST) ||
	    (vlan_id & CHECK_IPSU_15BIT &&
	     status == HINIC_MGMT_STATUS_EXIST))
		वापस -EINVAL;

	वापस 0;
पूर्ण

#घोषणा HINIC_VLAN_ID_MASK	0x7FFF

अटल पूर्णांक hinic_update_mac(काष्ठा hinic_hwdev *hwdev, u8 *old_mac,
			    u8 *new_mac, u16 vlan_id, u16 func_id)
अणु
	काष्ठा hinic_port_mac_update mac_info = अणु0पूर्ण;
	u16 out_size = माप(mac_info);
	पूर्णांक err;

	अगर (!hwdev || !old_mac || !new_mac)
		वापस -EINVAL;

	अगर ((vlan_id & HINIC_VLAN_ID_MASK) >= VLAN_N_VID) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Invalid VLAN number: %d\n",
			(vlan_id & HINIC_VLAN_ID_MASK));
		वापस -EINVAL;
	पूर्ण

	mac_info.func_id = func_id;
	mac_info.vlan_id = vlan_id;
	स_नकल(mac_info.old_mac, old_mac, ETH_ALEN);
	स_नकल(mac_info.new_mac, new_mac, ETH_ALEN);

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_UPDATE_MAC, &mac_info,
				 माप(mac_info), &mac_info, &out_size);

	अगर (err || !out_size ||
	    hinic_check_mac_info(mac_info.status, mac_info.vlan_id)) अणु
		dev_err(&hwdev->hwअगर->pdev->dev,
			"Failed to update MAC, err: %d, status: 0x%x, out size: 0x%x\n",
			err, mac_info.status, out_size);
		वापस -EINVAL;
	पूर्ण

	अगर (mac_info.status == HINIC_MGMT_STATUS_EXIST)
		dev_warn(&hwdev->hwअगर->pdev->dev, "MAC is repeated. Ignore update operation\n");

	वापस 0;
पूर्ण

अटल व्योम hinic_get_vf_config(काष्ठा hinic_hwdev *hwdev, u16 vf_id,
				काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा vf_data_storage *vfinfo;

	vfinfo = hwdev->func_to_io.vf_infos + HW_VF_ID_TO_OS(vf_id);

	ivi->vf = HW_VF_ID_TO_OS(vf_id);
	स_नकल(ivi->mac, vfinfo->vf_mac_addr, ETH_ALEN);
	ivi->vlan = vfinfo->pf_vlan;
	ivi->qos = vfinfo->pf_qos;
	ivi->spoofchk = vfinfo->spoofchk;
	ivi->trusted = vfinfo->trust;
	ivi->max_tx_rate = vfinfo->max_rate;
	ivi->min_tx_rate = vfinfo->min_rate;

	अगर (!vfinfo->link_क्रमced)
		ivi->linkstate = IFLA_VF_LINK_STATE_AUTO;
	अन्यथा अगर (vfinfo->link_up)
		ivi->linkstate = IFLA_VF_LINK_STATE_ENABLE;
	अन्यथा
		ivi->linkstate = IFLA_VF_LINK_STATE_DISABLE;
पूर्ण

पूर्णांक hinic_nकरो_get_vf_config(काष्ठा net_device *netdev,
			    पूर्णांक vf, काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	काष्ठा hinic_sriov_info *sriov_info;

	sriov_info = &nic_dev->sriov_info;
	अगर (vf >= sriov_info->num_vfs)
		वापस -EINVAL;

	hinic_get_vf_config(sriov_info->hwdev, OS_VF_ID_TO_HW(vf), ivi);

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_set_vf_mac(काष्ठा hinic_hwdev *hwdev, पूर्णांक vf,
			    अचिन्हित अक्षर *mac_addr)
अणु
	काष्ठा hinic_func_to_io *nic_io = &hwdev->func_to_io;
	काष्ठा vf_data_storage *vf_info;
	u16 func_id;
	पूर्णांक err;

	vf_info = nic_io->vf_infos + HW_VF_ID_TO_OS(vf);

	/* duplicate request, so just वापस success */
	अगर (vf_info->pf_set_mac &&
	    !स_भेद(vf_info->vf_mac_addr, mac_addr, ETH_ALEN))
		वापस 0;

	vf_info->pf_set_mac = true;

	func_id = hinic_glb_pf_vf_offset(hwdev->hwअगर) + vf;
	err = hinic_update_mac(hwdev, vf_info->vf_mac_addr,
			       mac_addr, 0, func_id);
	अगर (err) अणु
		vf_info->pf_set_mac = false;
		वापस err;
	पूर्ण

	स_नकल(vf_info->vf_mac_addr, mac_addr, ETH_ALEN);

	वापस 0;
पूर्ण

पूर्णांक hinic_nकरो_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf, u8 *mac)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	काष्ठा hinic_sriov_info *sriov_info;
	पूर्णांक err;

	sriov_info = &nic_dev->sriov_info;
	अगर (!is_valid_ether_addr(mac) || vf >= sriov_info->num_vfs)
		वापस -EINVAL;

	err = hinic_set_vf_mac(sriov_info->hwdev, OS_VF_ID_TO_HW(vf), mac);
	अगर (err)
		वापस err;

	netअगर_info(nic_dev, drv, netdev, "Setting MAC %pM on VF %d\n", mac, vf);
	netअगर_info(nic_dev, drv, netdev, "Reload the VF driver to make this change effective.");

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_add_vf_vlan(काष्ठा hinic_hwdev *hwdev, पूर्णांक vf_id,
			     u16 vlan, u8 qos)
अणु
	काष्ठा hinic_func_to_io *nic_io = &hwdev->func_to_io;
	पूर्णांक err;

	err = hinic_set_vf_vlan(hwdev, true, vlan, qos, vf_id);
	अगर (err)
		वापस err;

	nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_vlan = vlan;
	nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_qos = qos;

	dev_info(&hwdev->hwअगर->pdev->dev, "Setting VLAN %d, QOS 0x%x on VF %d\n",
		 vlan, qos, HW_VF_ID_TO_OS(vf_id));
	वापस 0;
पूर्ण

अटल पूर्णांक hinic_समाप्त_vf_vlan(काष्ठा hinic_hwdev *hwdev, पूर्णांक vf_id)
अणु
	काष्ठा hinic_func_to_io *nic_io = &hwdev->func_to_io;
	पूर्णांक err;

	err = hinic_set_vf_vlan(hwdev, false,
				nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_vlan,
				nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_qos,
				vf_id);
	अगर (err)
		वापस err;

	dev_info(&hwdev->hwअगर->pdev->dev, "Remove VLAN %d on VF %d\n",
		 nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_vlan,
		 HW_VF_ID_TO_OS(vf_id));

	nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_vlan = 0;
	nic_io->vf_infos[HW_VF_ID_TO_OS(vf_id)].pf_qos = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_update_mac_vlan(काष्ठा hinic_dev *nic_dev, u16 old_vlan,
				 u16 new_vlan, पूर्णांक vf_id)
अणु
	काष्ठा vf_data_storage *vf_info;
	u16 vlan_id;
	पूर्णांक err;

	अगर (!nic_dev || old_vlan >= VLAN_N_VID || new_vlan >= VLAN_N_VID)
		वापस -EINVAL;

	vf_info = nic_dev->hwdev->func_to_io.vf_infos + HW_VF_ID_TO_OS(vf_id);
	अगर (!vf_info->pf_set_mac)
		वापस 0;

	vlan_id = old_vlan;
	अगर (vlan_id)
		vlan_id |= HINIC_ADD_VLAN_IN_MAC;

	err = hinic_port_del_mac(nic_dev, vf_info->vf_mac_addr, vlan_id);
	अगर (err) अणु
		dev_err(&nic_dev->hwdev->hwअगर->pdev->dev, "Failed to delete VF %d MAC %pM vlan %d\n",
			HW_VF_ID_TO_OS(vf_id), vf_info->vf_mac_addr, old_vlan);
		वापस err;
	पूर्ण

	vlan_id = new_vlan;
	अगर (vlan_id)
		vlan_id |= HINIC_ADD_VLAN_IN_MAC;

	err = hinic_port_add_mac(nic_dev, vf_info->vf_mac_addr, vlan_id);
	अगर (err) अणु
		dev_err(&nic_dev->hwdev->hwअगर->pdev->dev, "Failed to add VF %d MAC %pM vlan %d\n",
			HW_VF_ID_TO_OS(vf_id), vf_info->vf_mac_addr, new_vlan);
		जाओ out;
	पूर्ण

	वापस 0;

out:
	vlan_id = old_vlan;
	अगर (vlan_id)
		vlan_id |= HINIC_ADD_VLAN_IN_MAC;
	hinic_port_add_mac(nic_dev, vf_info->vf_mac_addr, vlan_id);

	वापस err;
पूर्ण

अटल पूर्णांक set_hw_vf_vlan(काष्ठा hinic_dev *nic_dev,
			  u16 cur_vlanprio, पूर्णांक vf, u16 vlan, u8 qos)
अणु
	u16 old_vlan = cur_vlanprio & VLAN_VID_MASK;
	पूर्णांक err = 0;

	अगर (vlan || qos) अणु
		अगर (cur_vlanprio) अणु
			err = hinic_समाप्त_vf_vlan(nic_dev->hwdev,
						 OS_VF_ID_TO_HW(vf));
			अगर (err) अणु
				dev_err(&nic_dev->sriov_info.pdev->dev, "Failed to delete vf %d old vlan %d\n",
					vf, old_vlan);
				जाओ out;
			पूर्ण
		पूर्ण
		err = hinic_add_vf_vlan(nic_dev->hwdev,
					OS_VF_ID_TO_HW(vf), vlan, qos);
		अगर (err) अणु
			dev_err(&nic_dev->sriov_info.pdev->dev, "Failed to add vf %d new vlan %d\n",
				vf, vlan);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = hinic_समाप्त_vf_vlan(nic_dev->hwdev, OS_VF_ID_TO_HW(vf));
		अगर (err) अणु
			dev_err(&nic_dev->sriov_info.pdev->dev, "Failed to delete vf %d vlan %d\n",
				vf, old_vlan);
			जाओ out;
		पूर्ण
	पूर्ण

	err = hinic_update_mac_vlan(nic_dev, old_vlan, vlan,
				    OS_VF_ID_TO_HW(vf));

out:
	वापस err;
पूर्ण

पूर्णांक hinic_nकरो_set_vf_vlan(काष्ठा net_device *netdev, पूर्णांक vf, u16 vlan, u8 qos,
			  __be16 vlan_proto)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	काष्ठा hinic_sriov_info *sriov_info;
	u16 vlanprio, cur_vlanprio;

	sriov_info = &nic_dev->sriov_info;
	अगर (vf >= sriov_info->num_vfs || vlan > 4095 || qos > 7)
		वापस -EINVAL;
	अगर (vlan_proto != htons(ETH_P_8021Q))
		वापस -EPROTONOSUPPORT;
	vlanprio = vlan | qos << HINIC_VLAN_PRIORITY_SHIFT;
	cur_vlanprio = hinic_vf_info_vlanprio(nic_dev->hwdev,
					      OS_VF_ID_TO_HW(vf));
	/* duplicate request, so just वापस success */
	अगर (vlanprio == cur_vlanprio)
		वापस 0;

	वापस set_hw_vf_vlan(nic_dev, cur_vlanprio, vf, vlan, qos);
पूर्ण

अटल पूर्णांक hinic_set_vf_trust(काष्ठा hinic_hwdev *hwdev, u16 vf_id,
			      bool trust)
अणु
	काष्ठा vf_data_storage *vf_infos;
	काष्ठा hinic_func_to_io *nic_io;

	अगर (!hwdev)
		वापस -EINVAL;

	nic_io = &hwdev->func_to_io;
	vf_infos = nic_io->vf_infos;
	vf_infos[vf_id].trust = trust;

	वापस 0;
पूर्ण

पूर्णांक hinic_nकरो_set_vf_trust(काष्ठा net_device *netdev, पूर्णांक vf, bool setting)
अणु
	काष्ठा hinic_dev *adapter = netdev_priv(netdev);
	काष्ठा hinic_sriov_info *sriov_info;
	काष्ठा hinic_func_to_io *nic_io;
	bool cur_trust;
	पूर्णांक err;

	sriov_info = &adapter->sriov_info;
	nic_io = &adapter->hwdev->func_to_io;

	अगर (vf >= sriov_info->num_vfs)
		वापस -EINVAL;

	cur_trust = nic_io->vf_infos[vf].trust;
	/* same request, so just वापस success */
	अगर ((setting && cur_trust) || (!setting && !cur_trust))
		वापस 0;

	err = hinic_set_vf_trust(adapter->hwdev, vf, setting);
	अगर (!err)
		dev_info(&sriov_info->pdev->dev, "Set VF %d trusted %s succeed\n",
			 vf, setting ? "on" : "off");
	अन्यथा
		dev_err(&sriov_info->pdev->dev, "Failed set VF %d trusted %s\n",
			vf, setting ? "on" : "off");

	वापस err;
पूर्ण

पूर्णांक hinic_nकरो_set_vf_bw(काष्ठा net_device *netdev,
			पूर्णांक vf, पूर्णांक min_tx_rate, पूर्णांक max_tx_rate)
अणु
	u32 speeds[] = अणुSPEED_10, SPEED_100, SPEED_1000, SPEED_10000,
			SPEED_25000, SPEED_40000, SPEED_100000पूर्ण;
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	काष्ठा hinic_port_cap port_cap = अणु 0 पूर्ण;
	क्रमागत hinic_port_link_state link_state;
	पूर्णांक err;

	अगर (vf >= nic_dev->sriov_info.num_vfs) अणु
		netअगर_err(nic_dev, drv, netdev, "VF number must be less than %d\n",
			  nic_dev->sriov_info.num_vfs);
		वापस -EINVAL;
	पूर्ण

	अगर (max_tx_rate < min_tx_rate) अणु
		netअगर_err(nic_dev, drv, netdev, "Max rate %d must be greater than or equal to min rate %d\n",
			  max_tx_rate, min_tx_rate);
		वापस -EINVAL;
	पूर्ण

	err = hinic_port_link_state(nic_dev, &link_state);
	अगर (err) अणु
		netअगर_err(nic_dev, drv, netdev,
			  "Get link status failed when setting vf tx rate\n");
		वापस -EIO;
	पूर्ण

	अगर (link_state == HINIC_LINK_STATE_DOWN) अणु
		netअगर_err(nic_dev, drv, netdev,
			  "Link status must be up when setting vf tx rate\n");
		वापस -EPERM;
	पूर्ण

	err = hinic_port_get_cap(nic_dev, &port_cap);
	अगर (err || port_cap.speed > LINK_SPEED_100GB)
		वापस -EIO;

	/* rate limit cannot be less than 0 and greater than link speed */
	अगर (max_tx_rate < 0 || max_tx_rate > speeds[port_cap.speed]) अणु
		netअगर_err(nic_dev, drv, netdev, "Max tx rate must be in [0 - %d]\n",
			  speeds[port_cap.speed]);
		वापस -EINVAL;
	पूर्ण

	err = hinic_set_vf_tx_rate(nic_dev->hwdev, OS_VF_ID_TO_HW(vf),
				   max_tx_rate, min_tx_rate);
	अगर (err) अणु
		netअगर_err(nic_dev, drv, netdev,
			  "Unable to set VF %d max rate %d min rate %d%s\n",
			  vf, max_tx_rate, min_tx_rate,
			  err == HINIC_TX_RATE_TABLE_FULL ?
			  ", tx rate profile is full" : "");
		वापस -EIO;
	पूर्ण

	netअगर_info(nic_dev, drv, netdev,
		   "Set VF %d max tx rate %d min tx rate %d successfully\n",
		   vf, max_tx_rate, min_tx_rate);

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_set_vf_spoofchk(काष्ठा hinic_hwdev *hwdev, u16 vf_id,
				 bool spoofchk)
अणु
	काष्ठा hinic_spoofchk_set spoofchk_cfg = अणु0पूर्ण;
	काष्ठा vf_data_storage *vf_infos = शून्य;
	u16 out_size = माप(spoofchk_cfg);
	पूर्णांक err;

	अगर (!hwdev)
		वापस -EINVAL;

	vf_infos = hwdev->func_to_io.vf_infos;

	spoofchk_cfg.func_id = hinic_glb_pf_vf_offset(hwdev->hwअगर) + vf_id;
	spoofchk_cfg.state = spoofchk ? 1 : 0;
	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_ENABLE_SPOOFCHK,
				 &spoofchk_cfg, माप(spoofchk_cfg),
				 &spoofchk_cfg, &out_size);
	अगर (spoofchk_cfg.status == HINIC_MGMT_CMD_UNSUPPORTED) अणु
		err = HINIC_MGMT_CMD_UNSUPPORTED;
	पूर्ण अन्यथा अगर (err || !out_size || spoofchk_cfg.status) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to set VF(%d) spoofchk, err: %d, status: 0x%x, out size: 0x%x\n",
			HW_VF_ID_TO_OS(vf_id), err, spoofchk_cfg.status,
			out_size);
		err = -EIO;
	पूर्ण

	vf_infos[HW_VF_ID_TO_OS(vf_id)].spoofchk = spoofchk;

	वापस err;
पूर्ण

पूर्णांक hinic_nकरो_set_vf_spoofchk(काष्ठा net_device *netdev, पूर्णांक vf, bool setting)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	काष्ठा hinic_sriov_info *sriov_info;
	bool cur_spoofchk;
	पूर्णांक err;

	sriov_info = &nic_dev->sriov_info;
	अगर (vf >= sriov_info->num_vfs)
		वापस -EINVAL;

	cur_spoofchk = nic_dev->hwdev->func_to_io.vf_infos[vf].spoofchk;

	/* same request, so just वापस success */
	अगर ((setting && cur_spoofchk) || (!setting && !cur_spoofchk))
		वापस 0;

	err = hinic_set_vf_spoofchk(sriov_info->hwdev,
				    OS_VF_ID_TO_HW(vf), setting);
	अगर (!err) अणु
		netअगर_info(nic_dev, drv, netdev, "Set VF %d spoofchk %s successfully\n",
			   vf, setting ? "on" : "off");
	पूर्ण अन्यथा अगर (err == HINIC_MGMT_CMD_UNSUPPORTED) अणु
		netअगर_err(nic_dev, drv, netdev,
			  "Current firmware doesn't support to set vf spoofchk, need to upgrade latest firmware version\n");
		err = -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक hinic_set_vf_link_state(काष्ठा hinic_hwdev *hwdev, u16 vf_id,
				   पूर्णांक link)
अणु
	काष्ठा hinic_func_to_io *nic_io = &hwdev->func_to_io;
	काष्ठा vf_data_storage *vf_infos = nic_io->vf_infos;
	u8 link_status = 0;

	चयन (link) अणु
	हाल HINIC_IFLA_VF_LINK_STATE_AUTO:
		vf_infos[HW_VF_ID_TO_OS(vf_id)].link_क्रमced = false;
		vf_infos[HW_VF_ID_TO_OS(vf_id)].link_up = nic_io->link_status ?
			true : false;
		link_status = nic_io->link_status;
		अवरोध;
	हाल HINIC_IFLA_VF_LINK_STATE_ENABLE:
		vf_infos[HW_VF_ID_TO_OS(vf_id)].link_क्रमced = true;
		vf_infos[HW_VF_ID_TO_OS(vf_id)].link_up = true;
		link_status = HINIC_LINK_UP;
		अवरोध;
	हाल HINIC_IFLA_VF_LINK_STATE_DISABLE:
		vf_infos[HW_VF_ID_TO_OS(vf_id)].link_क्रमced = true;
		vf_infos[HW_VF_ID_TO_OS(vf_id)].link_up = false;
		link_status = HINIC_LINK_DOWN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Notअगरy the VF of its new link state */
	hinic_notअगरy_vf_link_status(hwdev, vf_id, link_status);

	वापस 0;
पूर्ण

पूर्णांक hinic_nकरो_set_vf_link_state(काष्ठा net_device *netdev, पूर्णांक vf_id, पूर्णांक link)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	काष्ठा hinic_sriov_info *sriov_info;

	sriov_info = &nic_dev->sriov_info;

	अगर (vf_id >= sriov_info->num_vfs) अणु
		netअगर_err(nic_dev, drv, netdev,
			  "Invalid VF Identifier %d\n", vf_id);
		वापस -EINVAL;
	पूर्ण

	वापस hinic_set_vf_link_state(sriov_info->hwdev,
				      OS_VF_ID_TO_HW(vf_id), link);
पूर्ण

/* pf receive message from vf */
अटल पूर्णांक nic_pf_mbox_handler(व्योम *hwdev, u16 vf_id, u8 cmd, व्योम *buf_in,
			       u16 in_size, व्योम *buf_out, u16 *out_size)
अणु
	u8 size = ARRAY_SIZE(nic_cmd_support_vf);
	काष्ठा vf_cmd_msg_handle *vf_msg_handle;
	काष्ठा hinic_hwdev *dev = hwdev;
	काष्ठा hinic_func_to_io *nic_io;
	काष्ठा hinic_pfhwdev *pfhwdev;
	पूर्णांक err = 0;
	u32 i;

	अगर (!hwdev)
		वापस -EINVAL;

	अगर (!hinic_mbox_check_cmd_valid(hwdev, nic_cmd_support_vf, vf_id, cmd,
					buf_in, in_size, size)) अणु
		dev_err(&dev->hwअगर->pdev->dev,
			"PF Receive VF nic cmd: 0x%x, mbox len: 0x%x is invalid\n",
			cmd, in_size);
		वापस HINIC_MBOX_VF_CMD_ERROR;
	पूर्ण

	pfhwdev = container_of(dev, काष्ठा hinic_pfhwdev, hwdev);
	nic_io = &dev->func_to_io;
	क्रम (i = 0; i < ARRAY_SIZE(nic_vf_cmd_msg_handler); i++) अणु
		vf_msg_handle = &nic_vf_cmd_msg_handler[i];
		अगर (cmd == vf_msg_handle->cmd &&
		    vf_msg_handle->cmd_msg_handler) अणु
			err = vf_msg_handle->cmd_msg_handler(hwdev, vf_id,
							     buf_in, in_size,
							     buf_out,
							     out_size);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(nic_vf_cmd_msg_handler))
		err = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_L2NIC,
					cmd, buf_in, in_size, buf_out,
					out_size, HINIC_MGMT_MSG_SYNC);

	अगर (err &&  err != HINIC_MBOX_PF_BUSY_ACTIVE_FW)
		dev_err(&nic_io->hwअगर->pdev->dev, "PF receive VF L2NIC cmd: %d process error, err:%d\n",
			cmd, err);
	वापस err;
पूर्ण

अटल पूर्णांक cfg_mbx_pf_proc_vf_msg(व्योम *hwdev, u16 vf_id, u8 cmd, व्योम *buf_in,
				  u16 in_size, व्योम *buf_out, u16 *out_size)
अणु
	काष्ठा hinic_dev_cap *dev_cap = buf_out;
	काष्ठा hinic_hwdev *dev = hwdev;
	काष्ठा hinic_cap *cap;

	cap = &dev->nic_cap;
	स_रखो(dev_cap, 0, माप(*dev_cap));

	dev_cap->max_vf = cap->max_vf;
	dev_cap->max_sqs = cap->max_vf_qps;
	dev_cap->max_rqs = cap->max_vf_qps;
	dev_cap->port_id = dev->port_id;

	*out_size = माप(*dev_cap);

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_init_vf_infos(काष्ठा hinic_func_to_io *nic_io, u16 vf_id)
अणु
	काष्ठा vf_data_storage *vf_infos = nic_io->vf_infos;

	अगर (set_vf_link_state > HINIC_IFLA_VF_LINK_STATE_DISABLE) अणु
		dev_warn(&nic_io->hwअगर->pdev->dev, "Module Parameter set_vf_link_state value %d is out of range, resetting to %d\n",
			 set_vf_link_state, HINIC_IFLA_VF_LINK_STATE_AUTO);
		set_vf_link_state = HINIC_IFLA_VF_LINK_STATE_AUTO;
	पूर्ण

	चयन (set_vf_link_state) अणु
	हाल HINIC_IFLA_VF_LINK_STATE_AUTO:
		vf_infos[vf_id].link_क्रमced = false;
		अवरोध;
	हाल HINIC_IFLA_VF_LINK_STATE_ENABLE:
		vf_infos[vf_id].link_क्रमced = true;
		vf_infos[vf_id].link_up = true;
		अवरोध;
	हाल HINIC_IFLA_VF_LINK_STATE_DISABLE:
		vf_infos[vf_id].link_क्रमced = true;
		vf_infos[vf_id].link_up = false;
		अवरोध;
	शेष:
		dev_err(&nic_io->hwअगर->pdev->dev, "Invalid input parameter set_vf_link_state: %d\n",
			set_vf_link_state);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hinic_clear_vf_infos(काष्ठा hinic_dev *nic_dev, u16 vf_id)
अणु
	काष्ठा vf_data_storage *vf_infos;

	vf_infos = nic_dev->hwdev->func_to_io.vf_infos + HW_VF_ID_TO_OS(vf_id);
	अगर (vf_infos->pf_set_mac)
		hinic_port_del_mac(nic_dev, vf_infos->vf_mac_addr, 0);

	अगर (hinic_vf_info_vlanprio(nic_dev->hwdev, vf_id))
		hinic_समाप्त_vf_vlan(nic_dev->hwdev, vf_id);

	अगर (vf_infos->max_rate)
		hinic_set_vf_tx_rate(nic_dev->hwdev, vf_id, 0, 0);

	अगर (vf_infos->spoofchk)
		hinic_set_vf_spoofchk(nic_dev->hwdev, vf_id, false);

	अगर (vf_infos->trust)
		hinic_set_vf_trust(nic_dev->hwdev, vf_id, false);

	स_रखो(vf_infos, 0, माप(*vf_infos));
	/* set vf_infos to शेष */
	hinic_init_vf_infos(&nic_dev->hwdev->func_to_io, HW_VF_ID_TO_OS(vf_id));
पूर्ण

अटल पूर्णांक hinic_deinit_vf_hw(काष्ठा hinic_sriov_info *sriov_info,
			      u16 start_vf_id, u16 end_vf_id)
अणु
	काष्ठा hinic_dev *nic_dev;
	u16 func_idx, idx;

	nic_dev = container_of(sriov_info, काष्ठा hinic_dev, sriov_info);

	क्रम (idx = start_vf_id; idx <= end_vf_id; idx++) अणु
		func_idx = hinic_glb_pf_vf_offset(nic_dev->hwdev->hwअगर) + idx;
		hinic_set_wq_page_size(nic_dev->hwdev, func_idx,
				       HINIC_HW_WQ_PAGE_SIZE);
		hinic_clear_vf_infos(nic_dev, idx);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_vf_func_init(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_रेजिस्टर_vf रेजिस्टर_info = अणु0पूर्ण;
	u16 out_size = माप(रेजिस्टर_info);
	काष्ठा hinic_func_to_io *nic_io;
	पूर्णांक err = 0;
	u32 size, i;

	err = hinic_vf_mbox_अक्रमom_id_init(hwdev);
	अगर (err) अणु
		dev_err(&hwdev->hwअगर->pdev->dev, "Failed to init vf mbox random id, err: %d\n",
			err);
		वापस err;
	पूर्ण

	nic_io = &hwdev->func_to_io;

	अगर (HINIC_IS_VF(hwdev->hwअगर)) अणु
		err = hinic_mbox_to_pf(hwdev, HINIC_MOD_L2NIC,
				       HINIC_PORT_CMD_VF_REGISTER,
				       &रेजिस्टर_info, माप(रेजिस्टर_info),
				       &रेजिस्टर_info, &out_size, 0);
		अगर (err || रेजिस्टर_info.status || !out_size) अणु
			dev_err(&hwdev->hwअगर->pdev->dev,
				"Failed to register VF, err: %d, status: 0x%x, out size: 0x%x\n",
				err, रेजिस्टर_info.status, out_size);
			hinic_unरेजिस्टर_vf_mbox_cb(hwdev, HINIC_MOD_L2NIC);
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = hinic_रेजिस्टर_pf_mbox_cb(hwdev, HINIC_MOD_CFGM,
						cfg_mbx_pf_proc_vf_msg);
		अगर (err) अणु
			dev_err(&hwdev->hwअगर->pdev->dev,
				"Register PF mailbox callback failed\n");
			वापस err;
		पूर्ण
		nic_io->max_vfs = hwdev->nic_cap.max_vf;
		size = माप(*nic_io->vf_infos) * nic_io->max_vfs;
		अगर (size != 0) अणु
			nic_io->vf_infos = kzalloc(size, GFP_KERNEL);
			अगर (!nic_io->vf_infos) अणु
				err = -ENOMEM;
				जाओ out_मुक्त_nic_io;
			पूर्ण

			क्रम (i = 0; i < nic_io->max_vfs; i++) अणु
				err = hinic_init_vf_infos(nic_io, i);
				अगर (err)
					जाओ err_init_vf_infos;
			पूर्ण

			err = hinic_रेजिस्टर_pf_mbox_cb(hwdev, HINIC_MOD_L2NIC,
							nic_pf_mbox_handler);
			अगर (err)
				जाओ err_रेजिस्टर_pf_mbox_cb;
		पूर्ण
	पूर्ण

	वापस 0;

err_रेजिस्टर_pf_mbox_cb:
err_init_vf_infos:
	kमुक्त(nic_io->vf_infos);
out_मुक्त_nic_io:
	वापस err;
पूर्ण

व्योम hinic_vf_func_मुक्त(काष्ठा hinic_hwdev *hwdev)
अणु
	काष्ठा hinic_रेजिस्टर_vf unरेजिस्टर = अणु0पूर्ण;
	u16 out_size = माप(unरेजिस्टर);
	पूर्णांक err;

	अगर (HINIC_IS_VF(hwdev->hwअगर)) अणु
		err = hinic_mbox_to_pf(hwdev, HINIC_MOD_L2NIC,
				       HINIC_PORT_CMD_VF_UNREGISTER,
				       &unरेजिस्टर, माप(unरेजिस्टर),
				       &unरेजिस्टर, &out_size, 0);
		अगर (err || !out_size || unरेजिस्टर.status)
			dev_err(&hwdev->hwअगर->pdev->dev, "Failed to unregister VF, err: %d, status: 0x%x, out_size: 0x%x\n",
				err, unरेजिस्टर.status, out_size);
	पूर्ण अन्यथा अणु
		अगर (hwdev->func_to_io.vf_infos) अणु
			hinic_unरेजिस्टर_pf_mbox_cb(hwdev, HINIC_MOD_L2NIC);
			kमुक्त(hwdev->func_to_io.vf_infos);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hinic_init_vf_hw(काष्ठा hinic_hwdev *hwdev, u16 start_vf_id,
			    u16 end_vf_id)
अणु
	u16 i, func_idx;
	पूर्णांक err;

	/* vf use 256K as शेष wq page size, and can't change it */
	क्रम (i = start_vf_id; i <= end_vf_id; i++) अणु
		func_idx = hinic_glb_pf_vf_offset(hwdev->hwअगर) + i;
		err = hinic_set_wq_page_size(hwdev, func_idx,
					     HINIC_DEFAULT_WQ_PAGE_SIZE);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hinic_pci_sriov_disable(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hinic_sriov_info *sriov_info;
	u16 पंचांगp_vfs;

	sriov_info = hinic_get_sriov_info_by_pcidev(pdev);
	/* अगर SR-IOV is alपढ़ोy disabled then nothing will be करोne */
	अगर (!sriov_info->sriov_enabled)
		वापस 0;

	set_bit(HINIC_SRIOV_DISABLE, &sriov_info->state);

	/* If our VFs are asचिन्हित we cannot shut करोwn SR-IOV
	 * without causing issues, so just leave the hardware
	 * available but disabled
	 */
	अगर (pci_vfs_asचिन्हित(sriov_info->pdev)) अणु
		clear_bit(HINIC_SRIOV_DISABLE, &sriov_info->state);
		dev_warn(&pdev->dev, "Unloading driver while VFs are assigned - VFs will not be deallocated\n");
		वापस -EPERM;
	पूर्ण
	sriov_info->sriov_enabled = false;

	/* disable iov and allow समय क्रम transactions to clear */
	pci_disable_sriov(sriov_info->pdev);

	पंचांगp_vfs = (u16)sriov_info->num_vfs;
	sriov_info->num_vfs = 0;
	hinic_deinit_vf_hw(sriov_info, OS_VF_ID_TO_HW(0),
			   OS_VF_ID_TO_HW(पंचांगp_vfs - 1));

	clear_bit(HINIC_SRIOV_DISABLE, &sriov_info->state);

	वापस 0;
पूर्ण

पूर्णांक hinic_pci_sriov_enable(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	काष्ठा hinic_sriov_info *sriov_info;
	पूर्णांक err;

	sriov_info = hinic_get_sriov_info_by_pcidev(pdev);

	अगर (test_and_set_bit(HINIC_SRIOV_ENABLE, &sriov_info->state)) अणु
		dev_err(&pdev->dev,
			"SR-IOV enable in process, please wait, num_vfs %d\n",
			num_vfs);
		वापस -EPERM;
	पूर्ण

	err = hinic_init_vf_hw(sriov_info->hwdev, OS_VF_ID_TO_HW(0),
			       OS_VF_ID_TO_HW((u16)num_vfs - 1));
	अगर (err) अणु
		dev_err(&sriov_info->pdev->dev,
			"Failed to init vf in hardware before enable sriov, error %d\n",
			err);
		clear_bit(HINIC_SRIOV_ENABLE, &sriov_info->state);
		वापस err;
	पूर्ण

	err = pci_enable_sriov(sriov_info->pdev, num_vfs);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"Failed to enable SR-IOV, error %d\n", err);
		clear_bit(HINIC_SRIOV_ENABLE, &sriov_info->state);
		वापस err;
	पूर्ण

	sriov_info->sriov_enabled = true;
	sriov_info->num_vfs = num_vfs;
	clear_bit(HINIC_SRIOV_ENABLE, &sriov_info->state);

	वापस num_vfs;
पूर्ण

पूर्णांक hinic_pci_sriov_configure(काष्ठा pci_dev *dev, पूर्णांक num_vfs)
अणु
	काष्ठा hinic_sriov_info *sriov_info;

	sriov_info = hinic_get_sriov_info_by_pcidev(dev);

	अगर (test_bit(HINIC_FUNC_REMOVE, &sriov_info->state))
		वापस -EBUSY;

	अगर (!num_vfs)
		वापस hinic_pci_sriov_disable(dev);
	अन्यथा
		वापस hinic_pci_sriov_enable(dev, num_vfs);
पूर्ण
