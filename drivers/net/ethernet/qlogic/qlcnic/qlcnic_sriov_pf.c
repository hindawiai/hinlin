<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#समावेश <linux/types.h>

#समावेश "qlcnic_sriov.h"
#समावेश "qlcnic.h"

#घोषणा QLCNIC_SRIOV_VF_MAX_MAC 7
#घोषणा QLC_VF_MIN_TX_RATE	100
#घोषणा QLC_VF_MAX_TX_RATE	9999
#घोषणा QLC_MAC_OPCODE_MASK	0x7
#घोषणा QLC_VF_FLOOD_BIT	BIT_16
#घोषणा QLC_FLOOD_MODE		0x5
#घोषणा QLC_SRIOV_ALLOW_VLAN0	BIT_19
#घोषणा QLC_INTR_COAL_TYPE_MASK	0x7

अटल पूर्णांक qlcnic_sriov_pf_get_vport_handle(काष्ठा qlcnic_adapter *, u8);

काष्ठा qlcnic_sriov_cmd_handler अणु
	पूर्णांक (*fn) (काष्ठा qlcnic_bc_trans *, काष्ठा qlcnic_cmd_args *);
पूर्ण;

काष्ठा qlcnic_sriov_fw_cmd_handler अणु
	u32 cmd;
	पूर्णांक (*fn) (काष्ठा qlcnic_bc_trans *, काष्ठा qlcnic_cmd_args *);
पूर्ण;

अटल पूर्णांक qlcnic_sriov_pf_set_vport_info(काष्ठा qlcnic_adapter *adapter,
					  काष्ठा qlcnic_info *npar_info,
					  u16 vport_id)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक err;

	अगर (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_SET_NIC_INFO))
		वापस -ENOMEM;

	cmd.req.arg[1] = (vport_id << 16) | 0x1;
	cmd.req.arg[2] = npar_info->bit_offsets;
	cmd.req.arg[2] |= npar_info->min_tx_bw << 16;
	cmd.req.arg[3] = npar_info->max_tx_bw | (npar_info->max_tx_ques << 16);
	cmd.req.arg[4] = npar_info->max_tx_mac_filters;
	cmd.req.arg[4] |= npar_info->max_rx_mcast_mac_filters << 16;
	cmd.req.arg[5] = npar_info->max_rx_ucast_mac_filters |
			 (npar_info->max_rx_ip_addr << 16);
	cmd.req.arg[6] = npar_info->max_rx_lro_flow |
			 (npar_info->max_rx_status_rings << 16);
	cmd.req.arg[7] = npar_info->max_rx_buf_rings |
			 (npar_info->max_rx_ques << 16);
	cmd.req.arg[8] = npar_info->max_tx_vlan_keys;
	cmd.req.arg[8] |= npar_info->max_local_ipv6_addrs << 16;
	cmd.req.arg[9] = npar_info->max_remote_ipv6_addrs;

	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err)
		dev_err(&adapter->pdev->dev,
			"Failed to set vport info, err=%d\n", err);

	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_cal_res_limit(काष्ठा qlcnic_adapter *adapter,
					 काष्ठा qlcnic_info *info, u16 func)
अणु
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	काष्ठा qlcnic_resources *res = &sriov->ff_max;
	u16 num_macs = sriov->num_allowed_vlans + 1;
	पूर्णांक ret = -EIO, vpid, id;
	काष्ठा qlcnic_vport *vp;
	u32 num_vfs, max, temp;

	vpid = qlcnic_sriov_pf_get_vport_handle(adapter, func);
	अगर (vpid < 0)
		वापस -EINVAL;

	num_vfs = sriov->num_vfs;
	max = num_vfs + 1;
	info->bit_offsets = 0xffff;
	info->max_tx_ques = res->num_tx_queues / max;

	अगर (qlcnic_83xx_pf_check(adapter))
		num_macs = QLCNIC_83XX_SRIOV_VF_MAX_MAC;

	info->max_rx_mcast_mac_filters = res->num_rx_mcast_mac_filters;

	अगर (adapter->ahw->pci_func == func) अणु
		info->min_tx_bw = 0;
		info->max_tx_bw = MAX_BW;

		temp = res->num_rx_ucast_mac_filters - num_macs * num_vfs;
		info->max_rx_ucast_mac_filters = temp;
		temp = res->num_tx_mac_filters - num_macs * num_vfs;
		info->max_tx_mac_filters = temp;
		temp = num_macs * num_vfs * QLCNIC_SRIOV_VF_MAX_MAC;
		temp = res->num_rx_mcast_mac_filters - temp;
		info->max_rx_mcast_mac_filters = temp;

		info->max_tx_ques = res->num_tx_queues - sriov->num_vfs;
	पूर्ण अन्यथा अणु
		id = qlcnic_sriov_func_to_index(adapter, func);
		अगर (id < 0)
			वापस id;
		vp = sriov->vf_info[id].vp;
		info->min_tx_bw = vp->min_tx_bw;
		info->max_tx_bw = vp->max_tx_bw;

		info->max_rx_ucast_mac_filters = num_macs;
		info->max_tx_mac_filters = num_macs;
		temp = num_macs * QLCNIC_SRIOV_VF_MAX_MAC;
		info->max_rx_mcast_mac_filters = temp;

		info->max_tx_ques = QLCNIC_SINGLE_RING;
	पूर्ण

	info->max_rx_ip_addr = res->num_destip / max;
	info->max_rx_status_rings = res->num_rx_status_rings / max;
	info->max_rx_buf_rings = res->num_rx_buf_rings / max;
	info->max_rx_ques = res->num_rx_queues / max;
	info->max_rx_lro_flow = res->num_lro_flows_supported / max;
	info->max_tx_vlan_keys = res->num_txvlan_keys;
	info->max_local_ipv6_addrs = res->max_local_ipv6_addrs;
	info->max_remote_ipv6_addrs = res->max_remote_ipv6_addrs;

	ret = qlcnic_sriov_pf_set_vport_info(adapter, info, vpid);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम qlcnic_sriov_pf_set_ff_max_res(काष्ठा qlcnic_adapter *adapter,
					   काष्ठा qlcnic_info *info)
अणु
	काष्ठा qlcnic_resources *ff_max = &adapter->ahw->sriov->ff_max;

	ff_max->num_tx_mac_filters = info->max_tx_mac_filters;
	ff_max->num_rx_ucast_mac_filters = info->max_rx_ucast_mac_filters;
	ff_max->num_rx_mcast_mac_filters = info->max_rx_mcast_mac_filters;
	ff_max->num_txvlan_keys = info->max_tx_vlan_keys;
	ff_max->num_rx_queues = info->max_rx_ques;
	ff_max->num_tx_queues = info->max_tx_ques;
	ff_max->num_lro_flows_supported = info->max_rx_lro_flow;
	ff_max->num_destip = info->max_rx_ip_addr;
	ff_max->num_rx_buf_rings = info->max_rx_buf_rings;
	ff_max->num_rx_status_rings = info->max_rx_status_rings;
	ff_max->max_remote_ipv6_addrs = info->max_remote_ipv6_addrs;
	ff_max->max_local_ipv6_addrs = info->max_local_ipv6_addrs;
पूर्ण

अटल व्योम qlcnic_sriov_set_vf_max_vlan(काष्ठा qlcnic_adapter *adapter,
					 काष्ठा qlcnic_info *npar_info)
अणु
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	पूर्णांक temp, total_fn;

	temp = npar_info->max_rx_mcast_mac_filters;
	total_fn = sriov->num_vfs + 1;

	temp = temp / (QLCNIC_SRIOV_VF_MAX_MAC * total_fn);
	sriov->num_allowed_vlans = temp - 1;

	अगर (qlcnic_83xx_pf_check(adapter))
		sriov->num_allowed_vlans = 1;

	netdev_info(adapter->netdev, "Max Guest VLANs supported per VF = %d\n",
		    sriov->num_allowed_vlans);
पूर्ण

अटल पूर्णांक qlcnic_sriov_get_pf_info(काष्ठा qlcnic_adapter *adapter,
				    काष्ठा qlcnic_info *npar_info)
अणु
	पूर्णांक err;
	काष्ठा qlcnic_cmd_args cmd;

	अगर (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_NIC_INFO))
		वापस -ENOMEM;

	cmd.req.arg[1] = 0x2;
	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"Failed to get PF info, err=%d\n", err);
		जाओ out;
	पूर्ण

	npar_info->total_pf = cmd.rsp.arg[2] & 0xff;
	npar_info->total_rss_engines = (cmd.rsp.arg[2] >> 8) & 0xff;
	npar_info->max_vports = MSW(cmd.rsp.arg[2]);
	npar_info->max_tx_ques =  LSW(cmd.rsp.arg[3]);
	npar_info->max_tx_mac_filters = MSW(cmd.rsp.arg[3]);
	npar_info->max_rx_mcast_mac_filters = LSW(cmd.rsp.arg[4]);
	npar_info->max_rx_ucast_mac_filters = MSW(cmd.rsp.arg[4]);
	npar_info->max_rx_ip_addr = LSW(cmd.rsp.arg[5]);
	npar_info->max_rx_lro_flow = MSW(cmd.rsp.arg[5]);
	npar_info->max_rx_status_rings = LSW(cmd.rsp.arg[6]);
	npar_info->max_rx_buf_rings = MSW(cmd.rsp.arg[6]);
	npar_info->max_rx_ques = LSW(cmd.rsp.arg[7]);
	npar_info->max_tx_vlan_keys = MSW(cmd.rsp.arg[7]);
	npar_info->max_local_ipv6_addrs = LSW(cmd.rsp.arg[8]);
	npar_info->max_remote_ipv6_addrs = MSW(cmd.rsp.arg[8]);

	qlcnic_sriov_set_vf_max_vlan(adapter, npar_info);
	qlcnic_sriov_pf_set_ff_max_res(adapter, npar_info);
	dev_info(&adapter->pdev->dev,
		 "\n\ttotal_pf: %d,\n"
		 "\n\ttotal_rss_engines: %d max_vports: %d max_tx_ques %d,\n"
		 "\tmax_tx_mac_filters: %d max_rx_mcast_mac_filters: %d,\n"
		 "\tmax_rx_ucast_mac_filters: 0x%x, max_rx_ip_addr: %d,\n"
		 "\tmax_rx_lro_flow: %d max_rx_status_rings: %d,\n"
		 "\tmax_rx_buf_rings: %d, max_rx_ques: %d, max_tx_vlan_keys %d\n"
		 "\tmax_local_ipv6_addrs: %d, max_remote_ipv6_addrs: %d\n",
		 npar_info->total_pf, npar_info->total_rss_engines,
		 npar_info->max_vports, npar_info->max_tx_ques,
		 npar_info->max_tx_mac_filters,
		 npar_info->max_rx_mcast_mac_filters,
		 npar_info->max_rx_ucast_mac_filters, npar_info->max_rx_ip_addr,
		 npar_info->max_rx_lro_flow, npar_info->max_rx_status_rings,
		 npar_info->max_rx_buf_rings, npar_info->max_rx_ques,
		 npar_info->max_tx_vlan_keys, npar_info->max_local_ipv6_addrs,
		 npar_info->max_remote_ipv6_addrs);

out:
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

अटल व्योम qlcnic_sriov_pf_reset_vport_handle(काष्ठा qlcnic_adapter *adapter,
					       u8 func)
अणु
	काष्ठा qlcnic_sriov  *sriov = adapter->ahw->sriov;
	काष्ठा qlcnic_vport *vp;
	पूर्णांक index;

	अगर (adapter->ahw->pci_func == func) अणु
		sriov->vp_handle = 0;
	पूर्ण अन्यथा अणु
		index = qlcnic_sriov_func_to_index(adapter, func);
		अगर (index < 0)
			वापस;
		vp = sriov->vf_info[index].vp;
		vp->handle = 0;
	पूर्ण
पूर्ण

अटल व्योम qlcnic_sriov_pf_set_vport_handle(काष्ठा qlcnic_adapter *adapter,
					     u16 vport_handle, u8 func)
अणु
	काष्ठा qlcnic_sriov  *sriov = adapter->ahw->sriov;
	काष्ठा qlcnic_vport *vp;
	पूर्णांक index;

	अगर (adapter->ahw->pci_func == func) अणु
		sriov->vp_handle = vport_handle;
	पूर्ण अन्यथा अणु
		index = qlcnic_sriov_func_to_index(adapter, func);
		अगर (index < 0)
			वापस;
		vp = sriov->vf_info[index].vp;
		vp->handle = vport_handle;
	पूर्ण
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_get_vport_handle(काष्ठा qlcnic_adapter *adapter,
					    u8 func)
अणु
	काष्ठा qlcnic_sriov  *sriov = adapter->ahw->sriov;
	काष्ठा qlcnic_vf_info *vf_info;
	पूर्णांक index;

	अगर (adapter->ahw->pci_func == func) अणु
		वापस sriov->vp_handle;
	पूर्ण अन्यथा अणु
		index = qlcnic_sriov_func_to_index(adapter, func);
		अगर (index >= 0) अणु
			vf_info = &sriov->vf_info[index];
			वापस vf_info->vp->handle;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_config_vport(काष्ठा qlcnic_adapter *adapter,
					u8 flag, u16 func)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक ret;
	पूर्णांक vpid;

	अगर (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CONFIG_VPORT))
		वापस -ENOMEM;

	अगर (flag) अणु
		cmd.req.arg[3] = func << 8;
	पूर्ण अन्यथा अणु
		vpid = qlcnic_sriov_pf_get_vport_handle(adapter, func);
		अगर (vpid < 0) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		cmd.req.arg[3] = ((vpid & 0xffff) << 8) | 1;
	पूर्ण

	ret = qlcnic_issue_cmd(adapter, &cmd);
	अगर (ret) अणु
		dev_err(&adapter->pdev->dev,
			"Failed %s vport, err %d for func 0x%x\n",
			(flag ? "enable" : "disable"), ret, func);
		जाओ out;
	पूर्ण

	अगर (flag) अणु
		vpid = cmd.rsp.arg[2] & 0xffff;
		qlcnic_sriov_pf_set_vport_handle(adapter, vpid, func);
	पूर्ण अन्यथा अणु
		qlcnic_sriov_pf_reset_vport_handle(adapter, func);
	पूर्ण

out:
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस ret;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_cfg_vlan_filtering(काष्ठा qlcnic_adapter *adapter,
					      u8 enable)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक err;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_SET_NIC_INFO);
	अगर (err)
		वापस err;

	cmd.req.arg[1] = 0x4;
	अगर (enable) अणु
		adapter->flags |= QLCNIC_VLAN_FILTERING;
		cmd.req.arg[1] |= BIT_16;
		अगर (qlcnic_84xx_check(adapter))
			cmd.req.arg[1] |= QLC_SRIOV_ALLOW_VLAN0;
	पूर्ण अन्यथा अणु
		adapter->flags &= ~QLCNIC_VLAN_FILTERING;
	पूर्ण

	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err)
		dev_err(&adapter->pdev->dev,
			"Failed to configure VLAN filtering, err=%d\n", err);

	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

/* On configuring VF flood bit, PFD will receive traffic from all VFs */
अटल पूर्णांक qlcnic_sriov_pf_cfg_flood(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक err;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_SET_NIC_INFO);
	अगर (err)
		वापस err;

	cmd.req.arg[1] = QLC_FLOOD_MODE | QLC_VF_FLOOD_BIT;

	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err)
		dev_err(&adapter->pdev->dev,
			"Failed to configure VF Flood bit on PF, err=%d\n",
			err);

	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_cfg_eचयन(काष्ठा qlcnic_adapter *adapter,
				       u8 func, u8 enable)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक err = -EIO;

	अगर (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_TOGGLE_ESWITCH))
		वापस -ENOMEM;

	cmd.req.arg[0] |= (3 << 29);
	cmd.req.arg[1] = ((func & 0xf) << 2) | BIT_6 | BIT_1;
	अगर (enable)
		cmd.req.arg[1] |= BIT_0;

	err = qlcnic_issue_cmd(adapter, &cmd);

	अगर (err != QLCNIC_RCODE_SUCCESS) अणु
		dev_err(&adapter->pdev->dev,
			"Failed to enable sriov eswitch%d\n", err);
		err = -EIO;
	पूर्ण

	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

अटल व्योम qlcnic_sriov_pf_del_flr_queue(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	काष्ठा qlcnic_back_channel *bc = &sriov->bc;
	पूर्णांक i;

	क्रम (i = 0; i < sriov->num_vfs; i++)
		cancel_work_sync(&sriov->vf_info[i].flr_work);

	destroy_workqueue(bc->bc_flr_wq);
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_create_flr_queue(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_back_channel *bc = &adapter->ahw->sriov->bc;
	काष्ठा workqueue_काष्ठा *wq;

	wq = create_singlethपढ़ो_workqueue("qlcnic-flr");
	अगर (wq == शून्य) अणु
		dev_err(&adapter->pdev->dev, "Cannot create FLR workqueue\n");
		वापस -ENOMEM;
	पूर्ण

	bc->bc_flr_wq =  wq;
	वापस 0;
पूर्ण

व्योम qlcnic_sriov_pf_cleanup(काष्ठा qlcnic_adapter *adapter)
अणु
	u8 func = adapter->ahw->pci_func;

	अगर (!qlcnic_sriov_enable_check(adapter))
		वापस;

	qlcnic_sriov_pf_del_flr_queue(adapter);
	qlcnic_sriov_cfg_bc_पूर्णांकr(adapter, 0);
	qlcnic_sriov_pf_config_vport(adapter, 0, func);
	qlcnic_sriov_pf_cfg_eचयन(adapter, func, 0);
	qlcnic_sriov_pf_cfg_vlan_filtering(adapter, 0);
	__qlcnic_sriov_cleanup(adapter);
	adapter->ahw->op_mode = QLCNIC_MGMT_FUNC;
	clear_bit(__QLCNIC_SRIOV_ENABLE, &adapter->state);
पूर्ण

व्योम qlcnic_sriov_pf_disable(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (!qlcnic_sriov_pf_check(adapter))
		वापस;

	अगर (!qlcnic_sriov_enable_check(adapter))
		वापस;

	pci_disable_sriov(adapter->pdev);
	netdev_info(adapter->netdev,
		    "SR-IOV is disabled successfully on port %d\n",
		    adapter->portnum);
पूर्ण

अटल पूर्णांक qlcnic_pci_sriov_disable(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (pci_vfs_asचिन्हित(adapter->pdev)) अणु
		netdev_err(adapter->netdev,
			   "SR-IOV VFs belonging to port %d are assigned to VMs. SR-IOV can not be disabled on this port\n",
			   adapter->portnum);
		netdev_info(adapter->netdev,
			    "Please detach SR-IOV VFs belonging to port %d from VMs, and then try to disable SR-IOV on this port\n",
			    adapter->portnum);
		वापस -EPERM;
	पूर्ण

	qlcnic_sriov_pf_disable(adapter);

	rtnl_lock();
	अगर (netअगर_running(netdev))
		__qlcnic_करोwn(adapter, netdev);

	qlcnic_sriov_मुक्त_vlans(adapter);

	qlcnic_sriov_pf_cleanup(adapter);

	/* After disabling SRIOV re-init the driver in शेष mode
	   configure opmode based on op_mode of function
	 */
	अगर (qlcnic_83xx_configure_opmode(adapter)) अणु
		rtnl_unlock();
		वापस -EIO;
	पूर्ण

	अगर (netअगर_running(netdev))
		__qlcnic_up(adapter, netdev);

	rtnl_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_init(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_info nic_info, pf_info, vp_info;
	पूर्णांक err;
	u8 func = ahw->pci_func;

	अगर (!qlcnic_sriov_enable_check(adapter))
		वापस 0;

	err = qlcnic_sriov_pf_cfg_vlan_filtering(adapter, 1);
	अगर (err)
		वापस err;

	अगर (qlcnic_84xx_check(adapter)) अणु
		err = qlcnic_sriov_pf_cfg_flood(adapter);
		अगर (err)
			जाओ disable_vlan_filtering;
	पूर्ण

	err = qlcnic_sriov_pf_cfg_eचयन(adapter, func, 1);
	अगर (err)
		जाओ disable_vlan_filtering;

	err = qlcnic_sriov_pf_config_vport(adapter, 1, func);
	अगर (err)
		जाओ disable_eचयन;

	err = qlcnic_sriov_get_pf_info(adapter, &pf_info);
	अगर (err)
		जाओ delete_vport;

	err = qlcnic_get_nic_info(adapter, &nic_info, func);
	अगर (err)
		जाओ delete_vport;

	err = qlcnic_sriov_pf_cal_res_limit(adapter, &vp_info, func);
	अगर (err)
		जाओ delete_vport;

	err = qlcnic_sriov_cfg_bc_पूर्णांकr(adapter, 1);
	अगर (err)
		जाओ delete_vport;

	ahw->physical_port = (u8) nic_info.phys_port;
	ahw->चयन_mode = nic_info.चयन_mode;
	ahw->max_mtu = nic_info.max_mtu;
	ahw->capabilities = nic_info.capabilities;
	ahw->nic_mode = QLC_83XX_SRIOV_MODE;
	वापस err;

delete_vport:
	qlcnic_sriov_pf_config_vport(adapter, 0, func);

disable_eचयन:
	qlcnic_sriov_pf_cfg_eचयन(adapter, func, 0);

disable_vlan_filtering:
	qlcnic_sriov_pf_cfg_vlan_filtering(adapter, 0);

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_enable(काष्ठा qlcnic_adapter *adapter, पूर्णांक num_vfs)
अणु
	पूर्णांक err;

	अगर (!qlcnic_sriov_enable_check(adapter))
		वापस 0;

	err = pci_enable_sriov(adapter->pdev, num_vfs);
	अगर (err)
		qlcnic_sriov_pf_cleanup(adapter);

	वापस err;
पूर्ण

अटल पूर्णांक __qlcnic_pci_sriov_enable(काष्ठा qlcnic_adapter *adapter,
				     पूर्णांक num_vfs)
अणु
	पूर्णांक err = 0;

	set_bit(__QLCNIC_SRIOV_ENABLE, &adapter->state);
	adapter->ahw->op_mode = QLCNIC_SRIOV_PF_FUNC;

	err = qlcnic_sriov_init(adapter, num_vfs);
	अगर (err)
		जाओ clear_op_mode;

	err = qlcnic_sriov_pf_create_flr_queue(adapter);
	अगर (err)
		जाओ sriov_cleanup;

	err = qlcnic_sriov_pf_init(adapter);
	अगर (err)
		जाओ del_flr_queue;

	qlcnic_sriov_alloc_vlans(adapter);

	वापस err;

del_flr_queue:
	qlcnic_sriov_pf_del_flr_queue(adapter);

sriov_cleanup:
	__qlcnic_sriov_cleanup(adapter);

clear_op_mode:
	clear_bit(__QLCNIC_SRIOV_ENABLE, &adapter->state);
	adapter->ahw->op_mode = QLCNIC_MGMT_FUNC;
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_pci_sriov_enable(काष्ठा qlcnic_adapter *adapter, पूर्णांक num_vfs)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err;

	अगर (!(adapter->flags & QLCNIC_MSIX_ENABLED)) अणु
		netdev_err(netdev,
			   "SR-IOV cannot be enabled, when legacy interrupts are enabled\n");
		वापस -EIO;
	पूर्ण

	rtnl_lock();
	अगर (netअगर_running(netdev))
		__qlcnic_करोwn(adapter, netdev);

	err = __qlcnic_pci_sriov_enable(adapter, num_vfs);
	अगर (err)
		जाओ error;

	अगर (netअगर_running(netdev))
		__qlcnic_up(adapter, netdev);

	rtnl_unlock();
	err = qlcnic_sriov_pf_enable(adapter, num_vfs);
	अगर (!err) अणु
		netdev_info(netdev,
			    "SR-IOV is enabled successfully on port %d\n",
			    adapter->portnum);
		/* Return number of vfs enabled */
		वापस num_vfs;
	पूर्ण

	rtnl_lock();
	अगर (netअगर_running(netdev))
		__qlcnic_करोwn(adapter, netdev);

error:
	अगर (!qlcnic_83xx_configure_opmode(adapter)) अणु
		अगर (netअगर_running(netdev))
			__qlcnic_up(adapter, netdev);
	पूर्ण

	rtnl_unlock();
	netdev_info(netdev, "Failed to enable SR-IOV on port %d\n",
		    adapter->portnum);

	वापस err;
पूर्ण

पूर्णांक qlcnic_pci_sriov_configure(काष्ठा pci_dev *dev, पूर्णांक num_vfs)
अणु
	काष्ठा qlcnic_adapter *adapter = pci_get_drvdata(dev);
	पूर्णांक err;

	अगर (test_and_set_bit(__QLCNIC_RESETTING, &adapter->state))
		वापस -EBUSY;

	अगर (num_vfs == 0)
		err = qlcnic_pci_sriov_disable(adapter);
	अन्यथा
		err = qlcnic_pci_sriov_enable(adapter, num_vfs);

	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_set_vf_acl(काष्ठा qlcnic_adapter *adapter, u8 func)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	काष्ठा qlcnic_vport *vp;
	पूर्णांक err, id;
	u8 *mac;

	id = qlcnic_sriov_func_to_index(adapter, func);
	अगर (id < 0)
		वापस id;

	vp = adapter->ahw->sriov->vf_info[id].vp;
	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_SET_NIC_INFO);
	अगर (err)
		वापस err;

	cmd.req.arg[1] = 0x3 | func << 16;
	अगर (vp->spoofchk == true) अणु
		mac = vp->mac;
		cmd.req.arg[2] |= BIT_1 | BIT_3 | BIT_8;
		cmd.req.arg[4] = mac[5] | mac[4] << 8 | mac[3] << 16 |
				 mac[2] << 24;
		cmd.req.arg[5] = mac[1] | mac[0] << 8;
	पूर्ण

	अगर (vp->vlan_mode == QLC_PVID_MODE) अणु
		cmd.req.arg[2] |= BIT_6;
		cmd.req.arg[3] |= vp->pvid << 8;
	पूर्ण

	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err)
		dev_err(&adapter->pdev->dev, "Failed to set ACL, err=%d\n",
			err);

	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_set_vf_vport_info(काष्ठा qlcnic_adapter *adapter,
					  u16 func)
अणु
	काष्ठा qlcnic_info defvp_info;
	पूर्णांक err;

	err = qlcnic_sriov_pf_cal_res_limit(adapter, &defvp_info, func);
	अगर (err)
		वापस -EIO;

	err = qlcnic_sriov_set_vf_acl(adapter, func);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_channel_cfg_cmd(काष्ठा qlcnic_bc_trans *trans,
					   काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info *vf = trans->vf;
	काष्ठा qlcnic_vport *vp = vf->vp;
	काष्ठा qlcnic_adapter *adapter;
	काष्ठा qlcnic_sriov *sriov;
	u16 func = vf->pci_func;
	माप_प्रकार size;
	पूर्णांक err;

	adapter = vf->adapter;
	sriov = adapter->ahw->sriov;

	अगर (trans->req_hdr->cmd_op == QLCNIC_BC_CMD_CHANNEL_INIT) अणु
		err = qlcnic_sriov_pf_config_vport(adapter, 1, func);
		अगर (!err) अणु
			err = qlcnic_sriov_set_vf_vport_info(adapter, func);
			अगर (err)
				qlcnic_sriov_pf_config_vport(adapter, 0, func);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (vp->vlan_mode == QLC_GUEST_VLAN_MODE) अणु
			size = माप(*vf->sriov_vlans);
			size = size * sriov->num_allowed_vlans;
			स_रखो(vf->sriov_vlans, 0, size);
		पूर्ण

		err = qlcnic_sriov_pf_config_vport(adapter, 0, func);
	पूर्ण

	अगर (err)
		जाओ err_out;

	cmd->rsp.arg[0] |= (1 << 25);

	अगर (trans->req_hdr->cmd_op == QLCNIC_BC_CMD_CHANNEL_INIT)
		set_bit(QLC_BC_VF_STATE, &vf->state);
	अन्यथा
		clear_bit(QLC_BC_VF_STATE, &vf->state);

	वापस err;

err_out:
	cmd->rsp.arg[0] |= (2 << 25);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_cfg_vf_def_mac(काष्ठा qlcnic_adapter *adapter,
				       काष्ठा qlcnic_vf_info *vf,
				       u16 vlan, u8 op)
अणु
	काष्ठा qlcnic_cmd_args *cmd;
	काष्ठा qlcnic_macvlan_mbx mv;
	काष्ठा qlcnic_vport *vp;
	u8 *addr;
	पूर्णांक err;
	u32 *buf;
	पूर्णांक vpid;

	vp = vf->vp;

	cmd = kzalloc(माप(*cmd), GFP_ATOMIC);
	अगर (!cmd)
		वापस -ENOMEM;

	err = qlcnic_alloc_mbx_args(cmd, adapter, QLCNIC_CMD_CONFIG_MAC_VLAN);
	अगर (err)
		जाओ मुक्त_cmd;

	cmd->type = QLC_83XX_MBX_CMD_NO_WAIT;
	vpid = qlcnic_sriov_pf_get_vport_handle(adapter, vf->pci_func);
	अगर (vpid < 0) अणु
		err = -EINVAL;
		जाओ मुक्त_args;
	पूर्ण

	अगर (vlan)
		op = ((op == QLCNIC_MAC_ADD || op == QLCNIC_MAC_VLAN_ADD) ?
		      QLCNIC_MAC_VLAN_ADD : QLCNIC_MAC_VLAN_DEL);

	cmd->req.arg[1] = op | (1 << 8) | (3 << 6);
	cmd->req.arg[1] |= ((vpid & 0xffff) << 16) | BIT_31;

	addr = vp->mac;
	mv.vlan = vlan;
	mv.mac_addr0 = addr[0];
	mv.mac_addr1 = addr[1];
	mv.mac_addr2 = addr[2];
	mv.mac_addr3 = addr[3];
	mv.mac_addr4 = addr[4];
	mv.mac_addr5 = addr[5];
	buf = &cmd->req.arg[2];
	स_नकल(buf, &mv, माप(काष्ठा qlcnic_macvlan_mbx));

	err = qlcnic_issue_cmd(adapter, cmd);

	अगर (!err)
		वापस err;

मुक्त_args:
	qlcnic_मुक्त_mbx_args(cmd);
मुक्त_cmd:
	kमुक्त(cmd);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_validate_create_rx_ctx(काष्ठा qlcnic_cmd_args *cmd)
अणु
	अगर ((cmd->req.arg[0] >> 29) != 0x3)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम qlcnic_83xx_cfg_शेष_mac_vlan(काष्ठा qlcnic_adapter *adapter,
					     काष्ठा qlcnic_vf_info *vf,
					     पूर्णांक opcode)
अणु
	काष्ठा qlcnic_sriov *sriov;
	u16 vlan;
	पूर्णांक i;

	sriov = adapter->ahw->sriov;

	spin_lock_bh(&vf->vlan_list_lock);
	अगर (vf->num_vlan) अणु
		क्रम (i = 0; i < sriov->num_allowed_vlans; i++) अणु
			vlan = vf->sriov_vlans[i];
			अगर (vlan)
				qlcnic_sriov_cfg_vf_def_mac(adapter, vf, vlan,
							    opcode);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&vf->vlan_list_lock);

	अगर (vf->vp->vlan_mode != QLC_PVID_MODE) अणु
		अगर (qlcnic_83xx_pf_check(adapter) &&
		    qlcnic_sriov_check_any_vlan(vf))
			वापस;
		qlcnic_sriov_cfg_vf_def_mac(adapter, vf, 0, opcode);
	पूर्ण
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_create_rx_ctx_cmd(काष्ठा qlcnic_bc_trans *tran,
					     काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info *vf = tran->vf;
	काष्ठा qlcnic_adapter *adapter = vf->adapter;
	काष्ठा qlcnic_rcv_mbx_out *mbx_out;
	पूर्णांक err;

	err = qlcnic_sriov_validate_create_rx_ctx(cmd);
	अगर (err) अणु
		cmd->rsp.arg[0] |= (0x6 << 25);
		वापस err;
	पूर्ण

	cmd->req.arg[6] = vf->vp->handle;
	err = qlcnic_issue_cmd(adapter, cmd);

	अगर (!err) अणु
		mbx_out = (काष्ठा qlcnic_rcv_mbx_out *)&cmd->rsp.arg[1];
		vf->rx_ctx_id = mbx_out->ctx_id;
		qlcnic_83xx_cfg_शेष_mac_vlan(adapter, vf, QLCNIC_MAC_ADD);
	पूर्ण अन्यथा अणु
		vf->rx_ctx_id = 0;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_mac_address_cmd(काष्ठा qlcnic_bc_trans *trans,
					   काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info *vf = trans->vf;
	u8 type, *mac;

	type = cmd->req.arg[1];
	चयन (type) अणु
	हाल QLCNIC_SET_STATION_MAC:
	हाल QLCNIC_SET_FAC_DEF_MAC:
		cmd->rsp.arg[0] = (2 << 25);
		अवरोध;
	हाल QLCNIC_GET_CURRENT_MAC:
		cmd->rsp.arg[0] = (1 << 25);
		mac = vf->vp->mac;
		cmd->rsp.arg[2] = mac[1] | ((mac[0] << 8) & 0xff00);
		cmd->rsp.arg[1] = mac[5] | ((mac[4] << 8) & 0xff00) |
				  ((mac[3]) << 16 & 0xff0000) |
				  ((mac[2]) << 24 & 0xff000000);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_validate_create_tx_ctx(काष्ठा qlcnic_cmd_args *cmd)
अणु
	अगर ((cmd->req.arg[0] >> 29) != 0x3)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_create_tx_ctx_cmd(काष्ठा qlcnic_bc_trans *trans,
					     काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info *vf = trans->vf;
	काष्ठा qlcnic_adapter *adapter = vf->adapter;
	काष्ठा qlcnic_tx_mbx_out *mbx_out;
	पूर्णांक err;

	err = qlcnic_sriov_validate_create_tx_ctx(cmd);
	अगर (err) अणु
		cmd->rsp.arg[0] |= (0x6 << 25);
		वापस err;
	पूर्ण

	cmd->req.arg[5] |= vf->vp->handle << 16;
	err = qlcnic_issue_cmd(adapter, cmd);
	अगर (!err) अणु
		mbx_out = (काष्ठा qlcnic_tx_mbx_out *)&cmd->rsp.arg[2];
		vf->tx_ctx_id = mbx_out->ctx_id;
	पूर्ण अन्यथा अणु
		vf->tx_ctx_id = 0;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_validate_del_rx_ctx(काष्ठा qlcnic_vf_info *vf,
					    काष्ठा qlcnic_cmd_args *cmd)
अणु
	अगर ((cmd->req.arg[0] >> 29) != 0x3)
		वापस -EINVAL;

	अगर ((cmd->req.arg[1] & 0xffff) != vf->rx_ctx_id)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_del_rx_ctx_cmd(काष्ठा qlcnic_bc_trans *trans,
					  काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info *vf = trans->vf;
	काष्ठा qlcnic_adapter *adapter = vf->adapter;
	पूर्णांक err;

	err = qlcnic_sriov_validate_del_rx_ctx(vf, cmd);
	अगर (err) अणु
		cmd->rsp.arg[0] |= (0x6 << 25);
		वापस err;
	पूर्ण

	qlcnic_83xx_cfg_शेष_mac_vlan(adapter, vf, QLCNIC_MAC_DEL);
	cmd->req.arg[1] |= vf->vp->handle << 16;
	err = qlcnic_issue_cmd(adapter, cmd);

	अगर (!err)
		vf->rx_ctx_id = 0;

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_validate_del_tx_ctx(काष्ठा qlcnic_vf_info *vf,
					    काष्ठा qlcnic_cmd_args *cmd)
अणु
	अगर ((cmd->req.arg[0] >> 29) != 0x3)
		वापस -EINVAL;

	अगर ((cmd->req.arg[1] & 0xffff) != vf->tx_ctx_id)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_del_tx_ctx_cmd(काष्ठा qlcnic_bc_trans *trans,
					  काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info *vf = trans->vf;
	काष्ठा qlcnic_adapter *adapter = vf->adapter;
	पूर्णांक err;

	err = qlcnic_sriov_validate_del_tx_ctx(vf, cmd);
	अगर (err) अणु
		cmd->rsp.arg[0] |= (0x6 << 25);
		वापस err;
	पूर्ण

	cmd->req.arg[1] |= vf->vp->handle << 16;
	err = qlcnic_issue_cmd(adapter, cmd);

	अगर (!err)
		vf->tx_ctx_id = 0;

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_validate_cfg_lro(काष्ठा qlcnic_vf_info *vf,
					 काष्ठा qlcnic_cmd_args *cmd)
अणु
	अगर ((cmd->req.arg[1] >> 16) != vf->rx_ctx_id)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_cfg_lro_cmd(काष्ठा qlcnic_bc_trans *trans,
				       काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info *vf = trans->vf;
	काष्ठा qlcnic_adapter *adapter = vf->adapter;
	पूर्णांक err;

	err = qlcnic_sriov_validate_cfg_lro(vf, cmd);
	अगर (err) अणु
		cmd->rsp.arg[0] |= (0x6 << 25);
		वापस err;
	पूर्ण

	err = qlcnic_issue_cmd(adapter, cmd);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_cfg_ip_cmd(काष्ठा qlcnic_bc_trans *trans,
				      काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info *vf = trans->vf;
	काष्ठा qlcnic_adapter *adapter = vf->adapter;
	पूर्णांक err;

	cmd->req.arg[1] |= vf->vp->handle << 16;
	cmd->req.arg[1] |= BIT_31;

	err = qlcnic_issue_cmd(adapter, cmd);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_validate_cfg_पूर्णांकrpt(काष्ठा qlcnic_vf_info *vf,
					    काष्ठा qlcnic_cmd_args *cmd)
अणु
	अगर (((cmd->req.arg[1] >> 8) & 0xff) != vf->pci_func)
		वापस -EINVAL;

	अगर (!(cmd->req.arg[1] & BIT_16))
		वापस -EINVAL;

	अगर ((cmd->req.arg[1] & 0xff) != 0x1)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_cfg_पूर्णांकrpt_cmd(काष्ठा qlcnic_bc_trans *trans,
					  काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info *vf = trans->vf;
	काष्ठा qlcnic_adapter *adapter = vf->adapter;
	पूर्णांक err;

	err = qlcnic_sriov_validate_cfg_पूर्णांकrpt(vf, cmd);
	अगर (err)
		cmd->rsp.arg[0] |= (0x6 << 25);
	अन्यथा
		err = qlcnic_issue_cmd(adapter, cmd);

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_validate_mtu(काष्ठा qlcnic_adapter *adapter,
				     काष्ठा qlcnic_vf_info *vf,
				     काष्ठा qlcnic_cmd_args *cmd)
अणु
	अगर (cmd->req.arg[1] != vf->rx_ctx_id)
		वापस -EINVAL;

	अगर (cmd->req.arg[2] > adapter->ahw->max_mtu)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_set_mtu_cmd(काष्ठा qlcnic_bc_trans *trans,
				       काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info *vf = trans->vf;
	काष्ठा qlcnic_adapter *adapter = vf->adapter;
	पूर्णांक err;

	err = qlcnic_sriov_validate_mtu(adapter, vf, cmd);
	अगर (err)
		cmd->rsp.arg[0] |= (0x6 << 25);
	अन्यथा
		err = qlcnic_issue_cmd(adapter, cmd);

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_validate_get_nic_info(काष्ठा qlcnic_vf_info *vf,
					      काष्ठा qlcnic_cmd_args *cmd)
अणु
	अगर (cmd->req.arg[1] & BIT_31) अणु
		अगर (((cmd->req.arg[1] >> 16) & 0x7fff) != vf->pci_func)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		cmd->req.arg[1] |= vf->vp->handle << 16;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_get_nic_info_cmd(काष्ठा qlcnic_bc_trans *trans,
					    काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info *vf = trans->vf;
	काष्ठा qlcnic_adapter *adapter = vf->adapter;
	पूर्णांक err;

	err = qlcnic_sriov_validate_get_nic_info(vf, cmd);
	अगर (err) अणु
		cmd->rsp.arg[0] |= (0x6 << 25);
		वापस err;
	पूर्ण

	err = qlcnic_issue_cmd(adapter, cmd);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_validate_cfg_rss(काष्ठा qlcnic_vf_info *vf,
					 काष्ठा qlcnic_cmd_args *cmd)
अणु
	अगर (cmd->req.arg[1] != vf->rx_ctx_id)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_cfg_rss_cmd(काष्ठा qlcnic_bc_trans *trans,
				       काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info *vf = trans->vf;
	काष्ठा qlcnic_adapter *adapter = vf->adapter;
	पूर्णांक err;

	err = qlcnic_sriov_validate_cfg_rss(vf, cmd);
	अगर (err)
		cmd->rsp.arg[0] |= (0x6 << 25);
	अन्यथा
		err = qlcnic_issue_cmd(adapter, cmd);

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_validate_cfg_पूर्णांकrcoal(काष्ठा qlcnic_adapter *adapter,
					      काष्ठा qlcnic_vf_info *vf,
					      काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_nic_पूर्णांकr_coalesce *coal = &adapter->ahw->coal;
	u16 ctx_id, pkts, समय;
	पूर्णांक err = -EINVAL;
	u8 type;

	type = cmd->req.arg[1] & QLC_INTR_COAL_TYPE_MASK;
	ctx_id = cmd->req.arg[1] >> 16;
	pkts = cmd->req.arg[2] & 0xffff;
	समय = cmd->req.arg[2] >> 16;

	चयन (type) अणु
	हाल QLCNIC_INTR_COAL_TYPE_RX:
		अगर (ctx_id != vf->rx_ctx_id || pkts > coal->rx_packets ||
		    समय < coal->rx_समय_us)
			जाओ err_label;
		अवरोध;
	हाल QLCNIC_INTR_COAL_TYPE_TX:
		अगर (ctx_id != vf->tx_ctx_id || pkts > coal->tx_packets ||
		    समय < coal->tx_समय_us)
			जाओ err_label;
		अवरोध;
	शेष:
		netdev_err(adapter->netdev, "Invalid coalescing type 0x%x received\n",
			   type);
		वापस err;
	पूर्ण

	वापस 0;

err_label:
	netdev_err(adapter->netdev, "Expected: rx_ctx_id 0x%x rx_packets 0x%x rx_time_us 0x%x tx_ctx_id 0x%x tx_packets 0x%x tx_time_us 0x%x\n",
		   vf->rx_ctx_id, coal->rx_packets, coal->rx_समय_us,
		   vf->tx_ctx_id, coal->tx_packets, coal->tx_समय_us);
	netdev_err(adapter->netdev, "Received: ctx_id 0x%x packets 0x%x time_us 0x%x type 0x%x\n",
		   ctx_id, pkts, समय, type);

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_cfg_पूर्णांकrcoal_cmd(काष्ठा qlcnic_bc_trans *tran,
					    काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info *vf = tran->vf;
	काष्ठा qlcnic_adapter *adapter = vf->adapter;
	पूर्णांक err;

	err = qlcnic_sriov_validate_cfg_पूर्णांकrcoal(adapter, vf, cmd);
	अगर (err) अणु
		cmd->rsp.arg[0] |= (0x6 << 25);
		वापस err;
	पूर्ण

	err = qlcnic_issue_cmd(adapter, cmd);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_validate_cfg_macvlan(काष्ठा qlcnic_adapter *adapter,
					     काष्ठा qlcnic_vf_info *vf,
					     काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vport *vp = vf->vp;
	u8 op, new_op;

	अगर (!(cmd->req.arg[1] & BIT_8))
		वापस -EINVAL;

	cmd->req.arg[1] |= (vf->vp->handle << 16);
	cmd->req.arg[1] |= BIT_31;

	अगर (vp->vlan_mode == QLC_PVID_MODE) अणु
		op = cmd->req.arg[1] & 0x7;
		cmd->req.arg[1] &= ~0x7;
		new_op = (op == QLCNIC_MAC_ADD || op == QLCNIC_MAC_VLAN_ADD) ?
			 QLCNIC_MAC_VLAN_ADD : QLCNIC_MAC_VLAN_DEL;
		cmd->req.arg[3] |= vp->pvid << 16;
		cmd->req.arg[1] |= new_op;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_cfg_macvlan_cmd(काष्ठा qlcnic_bc_trans *trans,
					   काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info *vf = trans->vf;
	काष्ठा qlcnic_adapter *adapter = vf->adapter;
	पूर्णांक err;

	err = qlcnic_sriov_validate_cfg_macvlan(adapter, vf, cmd);
	अगर (err) अणु
		cmd->rsp.arg[0] |= (0x6 << 25);
		वापस err;
	पूर्ण

	err = qlcnic_issue_cmd(adapter, cmd);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_validate_linkevent(काष्ठा qlcnic_vf_info *vf,
					   काष्ठा qlcnic_cmd_args *cmd)
अणु
	अगर ((cmd->req.arg[1] >> 16) != vf->rx_ctx_id)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_linkevent_cmd(काष्ठा qlcnic_bc_trans *trans,
					 काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info *vf = trans->vf;
	काष्ठा qlcnic_adapter *adapter = vf->adapter;
	पूर्णांक err;

	err = qlcnic_sriov_validate_linkevent(vf, cmd);
	अगर (err) अणु
		cmd->rsp.arg[0] |= (0x6 << 25);
		वापस err;
	पूर्ण

	err = qlcnic_issue_cmd(adapter, cmd);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_cfg_promisc_cmd(काष्ठा qlcnic_bc_trans *trans,
					   काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info *vf = trans->vf;
	काष्ठा qlcnic_adapter *adapter = vf->adapter;
	पूर्णांक err;

	cmd->req.arg[1] |= vf->vp->handle << 16;
	cmd->req.arg[1] |= BIT_31;
	err = qlcnic_issue_cmd(adapter, cmd);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_get_acl_cmd(काष्ठा qlcnic_bc_trans *trans,
				       काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info *vf = trans->vf;
	काष्ठा qlcnic_vport *vp = vf->vp;
	u8 mode = vp->vlan_mode;
	काष्ठा qlcnic_adapter *adapter;
	काष्ठा qlcnic_sriov *sriov;

	adapter = vf->adapter;
	sriov = adapter->ahw->sriov;

	cmd->rsp.arg[0] |= 1 << 25;

	/* For 84xx adapter in हाल of PVID , PFD should send vlan mode as
	 * QLC_NO_VLAN_MODE to VFD which is zero in mailbox response
	 */
	अगर (qlcnic_84xx_check(adapter) && mode == QLC_PVID_MODE)
		वापस 0;

	चयन (mode) अणु
	हाल QLC_GUEST_VLAN_MODE:
		cmd->rsp.arg[1] = mode | 1 << 8;
		cmd->rsp.arg[2] = sriov->num_allowed_vlans << 16;
		अवरोध;
	हाल QLC_PVID_MODE:
		cmd->rsp.arg[1] = mode | 1 << 8 | vp->pvid << 16;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_del_guest_vlan(काष्ठा qlcnic_adapter *adapter,
					  काष्ठा qlcnic_vf_info *vf,
					  काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	u16 vlan;

	अगर (!qlcnic_sriov_check_any_vlan(vf))
		वापस -EINVAL;

	vlan = cmd->req.arg[1] >> 16;
	अगर (!vf->rx_ctx_id) अणु
		qlcnic_sriov_del_vlan_id(sriov, vf, vlan);
		वापस 0;
	पूर्ण

	qlcnic_sriov_cfg_vf_def_mac(adapter, vf, vlan, QLCNIC_MAC_DEL);
	qlcnic_sriov_del_vlan_id(sriov, vf, vlan);

	अगर (qlcnic_83xx_pf_check(adapter))
		qlcnic_sriov_cfg_vf_def_mac(adapter, vf,
					    0, QLCNIC_MAC_ADD);
	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_add_guest_vlan(काष्ठा qlcnic_adapter *adapter,
					  काष्ठा qlcnic_vf_info *vf,
					  काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	पूर्णांक err = -EIO;
	u16 vlan;

	अगर (qlcnic_83xx_pf_check(adapter) && qlcnic_sriov_check_any_vlan(vf))
		वापस err;

	vlan = cmd->req.arg[1] >> 16;

	अगर (!vf->rx_ctx_id) अणु
		qlcnic_sriov_add_vlan_id(sriov, vf, vlan);
		वापस 0;
	पूर्ण

	अगर (qlcnic_83xx_pf_check(adapter)) अणु
		err = qlcnic_sriov_cfg_vf_def_mac(adapter, vf, 0,
						  QLCNIC_MAC_DEL);
		अगर (err)
			वापस err;
	पूर्ण

	err = qlcnic_sriov_cfg_vf_def_mac(adapter, vf, vlan, QLCNIC_MAC_ADD);

	अगर (err) अणु
		अगर (qlcnic_83xx_pf_check(adapter))
			qlcnic_sriov_cfg_vf_def_mac(adapter, vf, 0,
						    QLCNIC_MAC_ADD);
		वापस err;
	पूर्ण

	qlcnic_sriov_add_vlan_id(sriov, vf, vlan);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_pf_cfg_guest_vlan_cmd(काष्ठा qlcnic_bc_trans *tran,
					      काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_vf_info  *vf = tran->vf;
	काष्ठा qlcnic_adapter *adapter =  vf->adapter;
	काष्ठा qlcnic_vport *vp = vf->vp;
	पूर्णांक err = -EIO;
	u8 op;

	अगर (vp->vlan_mode != QLC_GUEST_VLAN_MODE) अणु
		cmd->rsp.arg[0] |= 2 << 25;
		वापस err;
	पूर्ण

	op = cmd->req.arg[1] & 0xf;

	अगर (op)
		err = qlcnic_sriov_pf_add_guest_vlan(adapter, vf, cmd);
	अन्यथा
		err = qlcnic_sriov_pf_del_guest_vlan(adapter, vf, cmd);

	cmd->rsp.arg[0] |= err ? 2 << 25 : 1 << 25;
	वापस err;
पूर्ण

अटल स्थिर पूर्णांक qlcnic_pf_passthru_supp_cmds[] = अणु
	QLCNIC_CMD_GET_STATISTICS,
	QLCNIC_CMD_GET_PORT_CONFIG,
	QLCNIC_CMD_GET_LINK_STATUS,
	QLCNIC_CMD_INIT_NIC_FUNC,
	QLCNIC_CMD_STOP_NIC_FUNC,
पूर्ण;

अटल स्थिर काष्ठा qlcnic_sriov_cmd_handler qlcnic_pf_bc_cmd_hdlr[] = अणु
	[QLCNIC_BC_CMD_CHANNEL_INIT] = अणु&qlcnic_sriov_pf_channel_cfg_cmdपूर्ण,
	[QLCNIC_BC_CMD_CHANNEL_TERM] = अणु&qlcnic_sriov_pf_channel_cfg_cmdपूर्ण,
	[QLCNIC_BC_CMD_GET_ACL]	= अणु&qlcnic_sriov_pf_get_acl_cmdपूर्ण,
	[QLCNIC_BC_CMD_CFG_GUEST_VLAN]	= अणु&qlcnic_sriov_pf_cfg_guest_vlan_cmdपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा qlcnic_sriov_fw_cmd_handler qlcnic_pf_fw_cmd_hdlr[] = अणु
	अणुQLCNIC_CMD_CREATE_RX_CTX, qlcnic_sriov_pf_create_rx_ctx_cmdपूर्ण,
	अणुQLCNIC_CMD_CREATE_TX_CTX, qlcnic_sriov_pf_create_tx_ctx_cmdपूर्ण,
	अणुQLCNIC_CMD_MAC_ADDRESS, qlcnic_sriov_pf_mac_address_cmdपूर्ण,
	अणुQLCNIC_CMD_DESTROY_RX_CTX, qlcnic_sriov_pf_del_rx_ctx_cmdपूर्ण,
	अणुQLCNIC_CMD_DESTROY_TX_CTX, qlcnic_sriov_pf_del_tx_ctx_cmdपूर्ण,
	अणुQLCNIC_CMD_CONFIGURE_HW_LRO, qlcnic_sriov_pf_cfg_lro_cmdपूर्ण,
	अणुQLCNIC_CMD_CONFIGURE_IP_ADDR, qlcnic_sriov_pf_cfg_ip_cmdपूर्ण,
	अणुQLCNIC_CMD_CONFIG_INTRPT, qlcnic_sriov_pf_cfg_पूर्णांकrpt_cmdपूर्ण,
	अणुQLCNIC_CMD_SET_MTU, qlcnic_sriov_pf_set_mtu_cmdपूर्ण,
	अणुQLCNIC_CMD_GET_NIC_INFO, qlcnic_sriov_pf_get_nic_info_cmdपूर्ण,
	अणुQLCNIC_CMD_CONFIGURE_RSS, qlcnic_sriov_pf_cfg_rss_cmdपूर्ण,
	अणुQLCNIC_CMD_CONFIG_INTR_COAL, qlcnic_sriov_pf_cfg_पूर्णांकrcoal_cmdपूर्ण,
	अणुQLCNIC_CMD_CONFIG_MAC_VLAN, qlcnic_sriov_pf_cfg_macvlan_cmdपूर्ण,
	अणुQLCNIC_CMD_GET_LINK_EVENT, qlcnic_sriov_pf_linkevent_cmdपूर्ण,
	अणुQLCNIC_CMD_CONFIGURE_MAC_RX_MODE, qlcnic_sriov_pf_cfg_promisc_cmdपूर्ण,
पूर्ण;

व्योम qlcnic_sriov_pf_process_bc_cmd(काष्ठा qlcnic_adapter *adapter,
				    काष्ठा qlcnic_bc_trans *trans,
				    काष्ठा qlcnic_cmd_args *cmd)
अणु
	u8 size, cmd_op;

	cmd_op = trans->req_hdr->cmd_op;

	अगर (trans->req_hdr->op_type == QLC_BC_CMD) अणु
		size = ARRAY_SIZE(qlcnic_pf_bc_cmd_hdlr);
		अगर (cmd_op < size) अणु
			qlcnic_pf_bc_cmd_hdlr[cmd_op].fn(trans, cmd);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		size = ARRAY_SIZE(qlcnic_pf_fw_cmd_hdlr);
		क्रम (i = 0; i < size; i++) अणु
			अगर (cmd_op == qlcnic_pf_fw_cmd_hdlr[i].cmd) अणु
				qlcnic_pf_fw_cmd_hdlr[i].fn(trans, cmd);
				वापस;
			पूर्ण
		पूर्ण

		size = ARRAY_SIZE(qlcnic_pf_passthru_supp_cmds);
		क्रम (i = 0; i < size; i++) अणु
			अगर (cmd_op == qlcnic_pf_passthru_supp_cmds[i]) अणु
				qlcnic_issue_cmd(adapter, cmd);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	cmd->rsp.arg[0] |= (0x9 << 25);
पूर्ण

व्योम qlcnic_pf_set_पूर्णांकerface_id_create_rx_ctx(काष्ठा qlcnic_adapter *adapter,
					     u32 *पूर्णांक_id)
अणु
	u16 vpid;

	vpid = qlcnic_sriov_pf_get_vport_handle(adapter,
						adapter->ahw->pci_func);
	*पूर्णांक_id |= vpid;
पूर्ण

व्योम qlcnic_pf_set_पूर्णांकerface_id_del_rx_ctx(काष्ठा qlcnic_adapter *adapter,
					   u32 *पूर्णांक_id)
अणु
	u16 vpid;

	vpid = qlcnic_sriov_pf_get_vport_handle(adapter,
						adapter->ahw->pci_func);
	*पूर्णांक_id |= vpid << 16;
पूर्ण

व्योम qlcnic_pf_set_पूर्णांकerface_id_create_tx_ctx(काष्ठा qlcnic_adapter *adapter,
					      u32 *पूर्णांक_id)
अणु
	पूर्णांक vpid;

	vpid = qlcnic_sriov_pf_get_vport_handle(adapter,
						adapter->ahw->pci_func);
	*पूर्णांक_id |= vpid << 16;
पूर्ण

व्योम qlcnic_pf_set_पूर्णांकerface_id_del_tx_ctx(काष्ठा qlcnic_adapter *adapter,
					   u32 *पूर्णांक_id)
अणु
	u16 vpid;

	vpid = qlcnic_sriov_pf_get_vport_handle(adapter,
						adapter->ahw->pci_func);
	*पूर्णांक_id |= vpid << 16;
पूर्ण

व्योम qlcnic_pf_set_पूर्णांकerface_id_promisc(काष्ठा qlcnic_adapter *adapter,
					u32 *पूर्णांक_id)
अणु
	u16 vpid;

	vpid = qlcnic_sriov_pf_get_vport_handle(adapter,
						adapter->ahw->pci_func);
	*पूर्णांक_id |= (vpid << 16) | BIT_31;
पूर्ण

व्योम qlcnic_pf_set_पूर्णांकerface_id_ipaddr(काष्ठा qlcnic_adapter *adapter,
				       u32 *पूर्णांक_id)
अणु
	u16 vpid;

	vpid = qlcnic_sriov_pf_get_vport_handle(adapter,
						adapter->ahw->pci_func);
	*पूर्णांक_id |= (vpid << 16) | BIT_31;
पूर्ण

व्योम qlcnic_pf_set_पूर्णांकerface_id_macaddr(काष्ठा qlcnic_adapter *adapter,
					u32 *पूर्णांक_id)
अणु
	u16 vpid;

	vpid = qlcnic_sriov_pf_get_vport_handle(adapter,
						adapter->ahw->pci_func);
	*पूर्णांक_id |= (vpid << 16) | BIT_31;
पूर्ण

अटल व्योम qlcnic_sriov_del_rx_ctx(काष्ठा qlcnic_adapter *adapter,
				    काष्ठा qlcnic_vf_info *vf)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक vpid;

	अगर (!vf->rx_ctx_id)
		वापस;

	अगर (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_DESTROY_RX_CTX))
		वापस;

	vpid = qlcnic_sriov_pf_get_vport_handle(adapter, vf->pci_func);
	अगर (vpid >= 0) अणु
		cmd.req.arg[1] = vf->rx_ctx_id | (vpid & 0xffff) << 16;
		अगर (qlcnic_issue_cmd(adapter, &cmd))
			dev_err(&adapter->pdev->dev,
				"Failed to delete Tx ctx in firmware for func 0x%x\n",
				vf->pci_func);
		अन्यथा
			vf->rx_ctx_id = 0;
	पूर्ण

	qlcnic_मुक्त_mbx_args(&cmd);
पूर्ण

अटल व्योम qlcnic_sriov_del_tx_ctx(काष्ठा qlcnic_adapter *adapter,
				    काष्ठा qlcnic_vf_info *vf)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक vpid;

	अगर (!vf->tx_ctx_id)
		वापस;

	अगर (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_DESTROY_TX_CTX))
		वापस;

	vpid = qlcnic_sriov_pf_get_vport_handle(adapter, vf->pci_func);
	अगर (vpid >= 0) अणु
		cmd.req.arg[1] |= vf->tx_ctx_id | (vpid & 0xffff) << 16;
		अगर (qlcnic_issue_cmd(adapter, &cmd))
			dev_err(&adapter->pdev->dev,
				"Failed to delete Tx ctx in firmware for func 0x%x\n",
				vf->pci_func);
		अन्यथा
			vf->tx_ctx_id = 0;
	पूर्ण

	qlcnic_मुक्त_mbx_args(&cmd);
पूर्ण

अटल पूर्णांक qlcnic_sriov_add_act_list_irqsave(काष्ठा qlcnic_sriov *sriov,
					     काष्ठा qlcnic_vf_info *vf,
					     काष्ठा qlcnic_bc_trans *trans)
अणु
	काष्ठा qlcnic_trans_list *t_list = &vf->rcv_act;
	अचिन्हित दीर्घ flag;

	spin_lock_irqsave(&t_list->lock, flag);

	__qlcnic_sriov_add_act_list(sriov, vf, trans);

	spin_unlock_irqrestore(&t_list->lock, flag);
	वापस 0;
पूर्ण

अटल व्योम __qlcnic_sriov_process_flr(काष्ठा qlcnic_vf_info *vf)
अणु
	काष्ठा qlcnic_adapter *adapter = vf->adapter;

	qlcnic_sriov_cleanup_list(&vf->rcv_pend);
	cancel_work_sync(&vf->trans_work);
	qlcnic_sriov_cleanup_list(&vf->rcv_act);

	अगर (test_bit(QLC_BC_VF_SOFT_FLR, &vf->state)) अणु
		qlcnic_sriov_del_tx_ctx(adapter, vf);
		qlcnic_sriov_del_rx_ctx(adapter, vf);
	पूर्ण

	qlcnic_sriov_pf_config_vport(adapter, 0, vf->pci_func);

	clear_bit(QLC_BC_VF_FLR, &vf->state);
	अगर (test_bit(QLC_BC_VF_SOFT_FLR, &vf->state)) अणु
		qlcnic_sriov_add_act_list_irqsave(adapter->ahw->sriov, vf,
						  vf->flr_trans);
		clear_bit(QLC_BC_VF_SOFT_FLR, &vf->state);
		vf->flr_trans = शून्य;
	पूर्ण
पूर्ण

अटल व्योम qlcnic_sriov_pf_process_flr(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlcnic_vf_info *vf;

	vf = container_of(work, काष्ठा qlcnic_vf_info, flr_work);
	__qlcnic_sriov_process_flr(vf);
	वापस;
पूर्ण

अटल व्योम qlcnic_sriov_schedule_flr(काष्ठा qlcnic_sriov *sriov,
				      काष्ठा qlcnic_vf_info *vf,
				      work_func_t func)
अणु
	अगर (test_bit(__QLCNIC_RESETTING, &vf->adapter->state))
		वापस;

	INIT_WORK(&vf->flr_work, func);
	queue_work(sriov->bc.bc_flr_wq, &vf->flr_work);
पूर्ण

अटल व्योम qlcnic_sriov_handle_soft_flr(काष्ठा qlcnic_adapter *adapter,
					 काष्ठा qlcnic_bc_trans *trans,
					 काष्ठा qlcnic_vf_info *vf)
अणु
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;

	set_bit(QLC_BC_VF_FLR, &vf->state);
	clear_bit(QLC_BC_VF_STATE, &vf->state);
	set_bit(QLC_BC_VF_SOFT_FLR, &vf->state);
	vf->flr_trans = trans;
	qlcnic_sriov_schedule_flr(sriov, vf, qlcnic_sriov_pf_process_flr);
	netdev_info(adapter->netdev, "Software FLR for PCI func %d\n",
		    vf->pci_func);
पूर्ण

bool qlcnic_sriov_soft_flr_check(काष्ठा qlcnic_adapter *adapter,
				 काष्ठा qlcnic_bc_trans *trans,
				 काष्ठा qlcnic_vf_info *vf)
अणु
	काष्ठा qlcnic_bc_hdr *hdr = trans->req_hdr;

	अगर ((hdr->cmd_op == QLCNIC_BC_CMD_CHANNEL_INIT) &&
	    (hdr->op_type == QLC_BC_CMD) &&
	     test_bit(QLC_BC_VF_STATE, &vf->state)) अणु
		qlcnic_sriov_handle_soft_flr(adapter, trans, vf);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम qlcnic_sriov_pf_handle_flr(काष्ठा qlcnic_sriov *sriov,
				काष्ठा qlcnic_vf_info *vf)
अणु
	काष्ठा net_device *dev = vf->adapter->netdev;
	काष्ठा qlcnic_vport *vp = vf->vp;

	अगर (!test_and_clear_bit(QLC_BC_VF_STATE, &vf->state)) अणु
		clear_bit(QLC_BC_VF_FLR, &vf->state);
		वापस;
	पूर्ण

	अगर (test_and_set_bit(QLC_BC_VF_FLR, &vf->state)) अणु
		netdev_info(dev, "FLR for PCI func %d in progress\n",
			    vf->pci_func);
		वापस;
	पूर्ण

	अगर (vp->vlan_mode == QLC_GUEST_VLAN_MODE)
		स_रखो(vf->sriov_vlans, 0,
		       माप(*vf->sriov_vlans) * sriov->num_allowed_vlans);

	qlcnic_sriov_schedule_flr(sriov, vf, qlcnic_sriov_pf_process_flr);
	netdev_info(dev, "FLR received for PCI func %d\n", vf->pci_func);
पूर्ण

व्योम qlcnic_sriov_pf_reset(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_sriov *sriov = ahw->sriov;
	काष्ठा qlcnic_vf_info *vf;
	u16 num_vfs = sriov->num_vfs;
	पूर्णांक i;

	क्रम (i = 0; i < num_vfs; i++) अणु
		vf = &sriov->vf_info[i];
		vf->rx_ctx_id = 0;
		vf->tx_ctx_id = 0;
		cancel_work_sync(&vf->flr_work);
		__qlcnic_sriov_process_flr(vf);
		clear_bit(QLC_BC_VF_STATE, &vf->state);
	पूर्ण

	qlcnic_sriov_pf_reset_vport_handle(adapter, ahw->pci_func);
	QLCWRX(ahw, QLCNIC_MBX_INTR_ENBL, (ahw->num_msix - 1) << 8);
पूर्ण

पूर्णांक qlcnic_sriov_pf_reinit(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक err;

	अगर (!qlcnic_sriov_enable_check(adapter))
		वापस 0;

	ahw->op_mode = QLCNIC_SRIOV_PF_FUNC;

	err = qlcnic_sriov_pf_init(adapter);
	अगर (err)
		वापस err;

	dev_info(&adapter->pdev->dev, "%s: op_mode %d\n",
		 __func__, ahw->op_mode);
	वापस err;
पूर्ण

पूर्णांक qlcnic_sriov_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf, u8 *mac)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	पूर्णांक i, num_vfs;
	काष्ठा qlcnic_vf_info *vf_info;
	u8 *curr_mac;

	अगर (!qlcnic_sriov_pf_check(adapter))
		वापस -EOPNOTSUPP;

	num_vfs = sriov->num_vfs;

	अगर (!is_valid_ether_addr(mac) || vf >= num_vfs)
		वापस -EINVAL;

	अगर (ether_addr_equal(adapter->mac_addr, mac)) अणु
		netdev_err(netdev, "MAC address is already in use by the PF\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < num_vfs; i++) अणु
		vf_info = &sriov->vf_info[i];
		अगर (ether_addr_equal(vf_info->vp->mac, mac)) अणु
			netdev_err(netdev,
				   "MAC address is already in use by VF %d\n",
				   i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	vf_info = &sriov->vf_info[vf];
	curr_mac = vf_info->vp->mac;

	अगर (test_bit(QLC_BC_VF_STATE, &vf_info->state)) अणु
		netdev_err(netdev,
			   "MAC address change failed for VF %d, as VF driver is loaded. Please unload VF driver and retry the operation\n",
			   vf);
		वापस -EOPNOTSUPP;
	पूर्ण

	स_नकल(curr_mac, mac, netdev->addr_len);
	netdev_info(netdev, "MAC Address %pM  is configured for VF %d\n",
		    mac, vf);
	वापस 0;
पूर्ण

पूर्णांक qlcnic_sriov_set_vf_tx_rate(काष्ठा net_device *netdev, पूर्णांक vf,
				पूर्णांक min_tx_rate, पूर्णांक max_tx_rate)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	काष्ठा qlcnic_vf_info *vf_info;
	काष्ठा qlcnic_info nic_info;
	काष्ठा qlcnic_vport *vp;
	u16 vpid;

	अगर (!qlcnic_sriov_pf_check(adapter))
		वापस -EOPNOTSUPP;

	अगर (vf >= sriov->num_vfs)
		वापस -EINVAL;

	vf_info = &sriov->vf_info[vf];
	vp = vf_info->vp;
	vpid = vp->handle;

	अगर (!min_tx_rate)
		min_tx_rate = QLC_VF_MIN_TX_RATE;

	अगर (max_tx_rate &&
	    (max_tx_rate >= 10000 || max_tx_rate < min_tx_rate)) अणु
		netdev_err(netdev,
			   "Invalid max Tx rate, allowed range is [%d - %d]",
			   min_tx_rate, QLC_VF_MAX_TX_RATE);
		वापस -EINVAL;
	पूर्ण

	अगर (!max_tx_rate)
		max_tx_rate = 10000;

	अगर (min_tx_rate &&
	    (min_tx_rate > max_tx_rate || min_tx_rate < QLC_VF_MIN_TX_RATE)) अणु
		netdev_err(netdev,
			   "Invalid min Tx rate, allowed range is [%d - %d]",
			   QLC_VF_MIN_TX_RATE, max_tx_rate);
		वापस -EINVAL;
	पूर्ण

	अगर (test_bit(QLC_BC_VF_STATE, &vf_info->state)) अणु
		अगर (qlcnic_sriov_get_vf_vport_info(adapter, &nic_info, vpid))
			वापस -EIO;

		nic_info.max_tx_bw = max_tx_rate / 100;
		nic_info.min_tx_bw = min_tx_rate / 100;
		nic_info.bit_offsets = BIT_0;

		अगर (qlcnic_sriov_pf_set_vport_info(adapter, &nic_info, vpid))
			वापस -EIO;
	पूर्ण

	vp->max_tx_bw = max_tx_rate / 100;
	netdev_info(netdev,
		    "Setting Max Tx rate %d (Mbps), %d %% of PF bandwidth, for VF %d\n",
		    max_tx_rate, vp->max_tx_bw, vf);
	vp->min_tx_bw = min_tx_rate / 100;
	netdev_info(netdev,
		    "Setting Min Tx rate %d (Mbps), %d %% of PF bandwidth, for VF %d\n",
		    min_tx_rate, vp->min_tx_bw, vf);
	वापस 0;
पूर्ण

पूर्णांक qlcnic_sriov_set_vf_vlan(काष्ठा net_device *netdev, पूर्णांक vf,
			     u16 vlan, u8 qos, __be16 vlan_proto)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	काष्ठा qlcnic_vf_info *vf_info;
	काष्ठा qlcnic_vport *vp;

	अगर (!qlcnic_sriov_pf_check(adapter))
		वापस -EOPNOTSUPP;

	अगर (vf >= sriov->num_vfs || qos > 7)
		वापस -EINVAL;

	अगर (vlan_proto != htons(ETH_P_8021Q))
		वापस -EPROTONOSUPPORT;

	अगर (vlan > MAX_VLAN_ID) अणु
		netdev_err(netdev,
			   "Invalid VLAN ID, allowed range is [0 - %d]\n",
			   MAX_VLAN_ID);
		वापस -EINVAL;
	पूर्ण

	vf_info = &sriov->vf_info[vf];
	vp = vf_info->vp;
	अगर (test_bit(QLC_BC_VF_STATE, &vf_info->state)) अणु
		netdev_err(netdev,
			   "VLAN change failed for VF %d, as VF driver is loaded. Please unload VF driver and retry the operation\n",
			   vf);
		वापस -EOPNOTSUPP;
	पूर्ण

	स_रखो(vf_info->sriov_vlans, 0,
	       माप(*vf_info->sriov_vlans) * sriov->num_allowed_vlans);

	चयन (vlan) अणु
	हाल 4095:
		vp->vlan_mode = QLC_GUEST_VLAN_MODE;
		अवरोध;
	हाल 0:
		vp->vlan_mode = QLC_NO_VLAN_MODE;
		vp->qos = 0;
		अवरोध;
	शेष:
		vp->vlan_mode = QLC_PVID_MODE;
		qlcnic_sriov_add_vlan_id(sriov, vf_info, vlan);
		vp->qos = qos;
		vp->pvid = vlan;
	पूर्ण

	netdev_info(netdev, "Setting VLAN %d, QoS %d, for VF %d\n",
		    vlan, qos, vf);
	वापस 0;
पूर्ण

अटल __u32 qlcnic_sriov_get_vf_vlan(काष्ठा qlcnic_adapter *adapter,
				      काष्ठा qlcnic_vport *vp, पूर्णांक vf)
अणु
	__u32 vlan = 0;

	चयन (vp->vlan_mode) अणु
	हाल QLC_PVID_MODE:
		vlan = vp->pvid;
		अवरोध;
	हाल QLC_GUEST_VLAN_MODE:
		vlan = MAX_VLAN_ID;
		अवरोध;
	हाल QLC_NO_VLAN_MODE:
		vlan = 0;
		अवरोध;
	शेष:
		netdev_info(adapter->netdev, "Invalid VLAN mode = %d for VF %d\n",
			    vp->vlan_mode, vf);
	पूर्ण

	वापस vlan;
पूर्ण

पूर्णांक qlcnic_sriov_get_vf_config(काष्ठा net_device *netdev,
			       पूर्णांक vf, काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	काष्ठा qlcnic_vport *vp;

	अगर (!qlcnic_sriov_pf_check(adapter))
		वापस -EOPNOTSUPP;

	अगर (vf >= sriov->num_vfs)
		वापस -EINVAL;

	vp = sriov->vf_info[vf].vp;
	स_नकल(&ivi->mac, vp->mac, ETH_ALEN);
	ivi->vlan = qlcnic_sriov_get_vf_vlan(adapter, vp, vf);
	ivi->qos = vp->qos;
	ivi->spoofchk = vp->spoofchk;
	अगर (vp->max_tx_bw == MAX_BW)
		ivi->max_tx_rate = 0;
	अन्यथा
		ivi->max_tx_rate = vp->max_tx_bw * 100;
	अगर (vp->min_tx_bw == MIN_BW)
		ivi->min_tx_rate = 0;
	अन्यथा
		ivi->min_tx_rate = vp->min_tx_bw * 100;

	ivi->vf = vf;
	वापस 0;
पूर्ण

पूर्णांक qlcnic_sriov_set_vf_spoofchk(काष्ठा net_device *netdev, पूर्णांक vf, bool chk)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	काष्ठा qlcnic_vf_info *vf_info;
	काष्ठा qlcnic_vport *vp;

	अगर (!qlcnic_sriov_pf_check(adapter))
		वापस -EOPNOTSUPP;

	अगर (vf >= sriov->num_vfs)
		वापस -EINVAL;

	vf_info = &sriov->vf_info[vf];
	vp = vf_info->vp;
	अगर (test_bit(QLC_BC_VF_STATE, &vf_info->state)) अणु
		netdev_err(netdev,
			   "Spoof check change failed for VF %d, as VF driver is loaded. Please unload VF driver and retry the operation\n",
			   vf);
		वापस -EOPNOTSUPP;
	पूर्ण

	vp->spoofchk = chk;
	वापस 0;
पूर्ण
