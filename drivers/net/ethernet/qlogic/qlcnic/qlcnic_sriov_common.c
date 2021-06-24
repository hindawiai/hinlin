<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#समावेश <linux/types.h>

#समावेश "qlcnic_sriov.h"
#समावेश "qlcnic.h"
#समावेश "qlcnic_83xx_hw.h"

#घोषणा QLC_BC_COMMAND	0
#घोषणा QLC_BC_RESPONSE	1

#घोषणा QLC_MBOX_RESP_TIMEOUT		(10 * HZ)
#घोषणा QLC_MBOX_CH_FREE_TIMEOUT	(10 * HZ)

#घोषणा QLC_BC_MSG		0
#घोषणा QLC_BC_CFREE		1
#घोषणा QLC_BC_FLR		2
#घोषणा QLC_BC_HDR_SZ		16
#घोषणा QLC_BC_PAYLOAD_SZ	(1024 - QLC_BC_HDR_SZ)

#घोषणा QLC_DEFAULT_RCV_DESCRIPTORS_SRIOV_VF		2048
#घोषणा QLC_DEFAULT_JUMBO_RCV_DESCRIPTORS_SRIOV_VF	512

#घोषणा QLC_83XX_VF_RESET_FAIL_THRESH	8
#घोषणा QLC_BC_CMD_MAX_RETRY_CNT	5

अटल व्योम qlcnic_sriov_handle_async_issue_cmd(काष्ठा work_काष्ठा *work);
अटल व्योम qlcnic_sriov_vf_मुक्त_mac_list(काष्ठा qlcnic_adapter *);
अटल पूर्णांक qlcnic_sriov_alloc_bc_mbx_args(काष्ठा qlcnic_cmd_args *, u32);
अटल व्योम qlcnic_sriov_vf_poll_dev_state(काष्ठा work_काष्ठा *);
अटल व्योम qlcnic_sriov_vf_cancel_fw_work(काष्ठा qlcnic_adapter *);
अटल व्योम qlcnic_sriov_cleanup_transaction(काष्ठा qlcnic_bc_trans *);
अटल पूर्णांक qlcnic_sriov_issue_cmd(काष्ठा qlcnic_adapter *,
				  काष्ठा qlcnic_cmd_args *);
अटल पूर्णांक qlcnic_sriov_channel_cfg_cmd(काष्ठा qlcnic_adapter *, u8);
अटल व्योम qlcnic_sriov_process_bc_cmd(काष्ठा work_काष्ठा *);
अटल पूर्णांक qlcnic_sriov_vf_shutकरोwn(काष्ठा pci_dev *);
अटल पूर्णांक qlcnic_sriov_vf_resume(काष्ठा qlcnic_adapter *);
अटल पूर्णांक qlcnic_sriov_async_issue_cmd(काष्ठा qlcnic_adapter *,
					काष्ठा qlcnic_cmd_args *);

अटल काष्ठा qlcnic_hardware_ops qlcnic_sriov_vf_hw_ops = अणु
	.पढ़ो_crb			= qlcnic_83xx_पढ़ो_crb,
	.ग_लिखो_crb			= qlcnic_83xx_ग_लिखो_crb,
	.पढ़ो_reg			= qlcnic_83xx_rd_reg_indirect,
	.ग_लिखो_reg			= qlcnic_83xx_wrt_reg_indirect,
	.get_mac_address		= qlcnic_83xx_get_mac_address,
	.setup_पूर्णांकr			= qlcnic_83xx_setup_पूर्णांकr,
	.alloc_mbx_args			= qlcnic_83xx_alloc_mbx_args,
	.mbx_cmd			= qlcnic_sriov_issue_cmd,
	.get_func_no			= qlcnic_83xx_get_func_no,
	.api_lock			= qlcnic_83xx_cam_lock,
	.api_unlock			= qlcnic_83xx_cam_unlock,
	.process_lb_rcv_ring_diag	= qlcnic_83xx_process_rcv_ring_diag,
	.create_rx_ctx			= qlcnic_83xx_create_rx_ctx,
	.create_tx_ctx			= qlcnic_83xx_create_tx_ctx,
	.del_rx_ctx			= qlcnic_83xx_del_rx_ctx,
	.del_tx_ctx			= qlcnic_83xx_del_tx_ctx,
	.setup_link_event		= qlcnic_83xx_setup_link_event,
	.get_nic_info			= qlcnic_83xx_get_nic_info,
	.get_pci_info			= qlcnic_83xx_get_pci_info,
	.set_nic_info			= qlcnic_83xx_set_nic_info,
	.change_macvlan			= qlcnic_83xx_sre_macaddr_change,
	.napi_enable			= qlcnic_83xx_napi_enable,
	.napi_disable			= qlcnic_83xx_napi_disable,
	.config_पूर्णांकr_coal		= qlcnic_83xx_config_पूर्णांकr_coal,
	.config_rss			= qlcnic_83xx_config_rss,
	.config_hw_lro			= qlcnic_83xx_config_hw_lro,
	.config_promisc_mode		= qlcnic_83xx_nic_set_promisc,
	.change_l2_filter		= qlcnic_83xx_change_l2_filter,
	.get_board_info			= qlcnic_83xx_get_port_info,
	.मुक्त_mac_list			= qlcnic_sriov_vf_मुक्त_mac_list,
	.enable_sds_पूर्णांकr		= qlcnic_83xx_enable_sds_पूर्णांकr,
	.disable_sds_पूर्णांकr		= qlcnic_83xx_disable_sds_पूर्णांकr,
	.encap_rx_offload               = qlcnic_83xx_encap_rx_offload,
	.encap_tx_offload               = qlcnic_83xx_encap_tx_offload,
पूर्ण;

अटल काष्ठा qlcnic_nic_ढाँचा qlcnic_sriov_vf_ops = अणु
	.config_bridged_mode	= qlcnic_config_bridged_mode,
	.config_led		= qlcnic_config_led,
	.cancel_idc_work        = qlcnic_sriov_vf_cancel_fw_work,
	.napi_add		= qlcnic_83xx_napi_add,
	.napi_del		= qlcnic_83xx_napi_del,
	.shutकरोwn		= qlcnic_sriov_vf_shutकरोwn,
	.resume			= qlcnic_sriov_vf_resume,
	.config_ipaddr		= qlcnic_83xx_config_ipaddr,
	.clear_legacy_पूर्णांकr	= qlcnic_83xx_clear_legacy_पूर्णांकr,
पूर्ण;

अटल स्थिर काष्ठा qlcnic_mailbox_metadata qlcnic_sriov_bc_mbx_tbl[] = अणु
	अणुQLCNIC_BC_CMD_CHANNEL_INIT, 2, 2पूर्ण,
	अणुQLCNIC_BC_CMD_CHANNEL_TERM, 2, 2पूर्ण,
	अणुQLCNIC_BC_CMD_GET_ACL, 3, 14पूर्ण,
	अणुQLCNIC_BC_CMD_CFG_GUEST_VLAN, 2, 2पूर्ण,
पूर्ण;

अटल अंतरभूत bool qlcnic_sriov_bc_msg_check(u32 val)
अणु
	वापस (val & (1 << QLC_BC_MSG)) ? true : false;
पूर्ण

अटल अंतरभूत bool qlcnic_sriov_channel_मुक्त_check(u32 val)
अणु
	वापस (val & (1 << QLC_BC_CFREE)) ? true : false;
पूर्ण

अटल अंतरभूत bool qlcnic_sriov_flr_check(u32 val)
अणु
	वापस (val & (1 << QLC_BC_FLR)) ? true : false;
पूर्ण

अटल अंतरभूत u8 qlcnic_sriov_target_func_id(u32 val)
अणु
	वापस (val >> 4) & 0xff;
पूर्ण

अटल पूर्णांक qlcnic_sriov_virtid_fn(काष्ठा qlcnic_adapter *adapter, पूर्णांक vf_id)
अणु
	काष्ठा pci_dev *dev = adapter->pdev;
	पूर्णांक pos;
	u16 stride, offset;

	अगर (qlcnic_sriov_vf_check(adapter))
		वापस 0;

	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_SRIOV);
	अगर (!pos)
		वापस 0;
	pci_पढ़ो_config_word(dev, pos + PCI_SRIOV_VF_OFFSET, &offset);
	pci_पढ़ो_config_word(dev, pos + PCI_SRIOV_VF_STRIDE, &stride);

	वापस (dev->devfn + offset + stride * vf_id) & 0xff;
पूर्ण

पूर्णांक qlcnic_sriov_init(काष्ठा qlcnic_adapter *adapter, पूर्णांक num_vfs)
अणु
	काष्ठा qlcnic_sriov *sriov;
	काष्ठा qlcnic_back_channel *bc;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा qlcnic_vport *vp;
	काष्ठा qlcnic_vf_info *vf;
	पूर्णांक err, i;

	अगर (!qlcnic_sriov_enable_check(adapter))
		वापस -EIO;

	sriov  = kzalloc(माप(काष्ठा qlcnic_sriov), GFP_KERNEL);
	अगर (!sriov)
		वापस -ENOMEM;

	adapter->ahw->sriov = sriov;
	sriov->num_vfs = num_vfs;
	bc = &sriov->bc;
	sriov->vf_info = kसुस्मृति(num_vfs, माप(काष्ठा qlcnic_vf_info),
				 GFP_KERNEL);
	अगर (!sriov->vf_info) अणु
		err = -ENOMEM;
		जाओ qlcnic_मुक्त_sriov;
	पूर्ण

	wq = create_singlethपढ़ो_workqueue("bc-trans");
	अगर (wq == शून्य) अणु
		err = -ENOMEM;
		dev_err(&adapter->pdev->dev,
			"Cannot create bc-trans workqueue\n");
		जाओ qlcnic_मुक्त_vf_info;
	पूर्ण

	bc->bc_trans_wq = wq;

	wq = create_singlethपढ़ो_workqueue("async");
	अगर (wq == शून्य) अणु
		err = -ENOMEM;
		dev_err(&adapter->pdev->dev, "Cannot create async workqueue\n");
		जाओ qlcnic_destroy_trans_wq;
	पूर्ण

	bc->bc_async_wq =  wq;
	INIT_LIST_HEAD(&bc->async_cmd_list);
	INIT_WORK(&bc->vf_async_work, qlcnic_sriov_handle_async_issue_cmd);
	spin_lock_init(&bc->queue_lock);
	bc->adapter = adapter;

	क्रम (i = 0; i < num_vfs; i++) अणु
		vf = &sriov->vf_info[i];
		vf->adapter = adapter;
		vf->pci_func = qlcnic_sriov_virtid_fn(adapter, i);
		mutex_init(&vf->send_cmd_lock);
		spin_lock_init(&vf->vlan_list_lock);
		INIT_LIST_HEAD(&vf->rcv_act.रुको_list);
		INIT_LIST_HEAD(&vf->rcv_pend.रुको_list);
		spin_lock_init(&vf->rcv_act.lock);
		spin_lock_init(&vf->rcv_pend.lock);
		init_completion(&vf->ch_मुक्त_cmpl);

		INIT_WORK(&vf->trans_work, qlcnic_sriov_process_bc_cmd);

		अगर (qlcnic_sriov_pf_check(adapter)) अणु
			vp = kzalloc(माप(काष्ठा qlcnic_vport), GFP_KERNEL);
			अगर (!vp) अणु
				err = -ENOMEM;
				जाओ qlcnic_destroy_async_wq;
			पूर्ण
			sriov->vf_info[i].vp = vp;
			vp->vlan_mode = QLC_GUEST_VLAN_MODE;
			vp->max_tx_bw = MAX_BW;
			vp->min_tx_bw = MIN_BW;
			vp->spoofchk = false;
			eth_अक्रमom_addr(vp->mac);
			dev_info(&adapter->pdev->dev,
				 "MAC Address %pM is configured for VF %d\n",
				 vp->mac, i);
		पूर्ण
	पूर्ण

	वापस 0;

qlcnic_destroy_async_wq:
	destroy_workqueue(bc->bc_async_wq);

qlcnic_destroy_trans_wq:
	destroy_workqueue(bc->bc_trans_wq);

qlcnic_मुक्त_vf_info:
	kमुक्त(sriov->vf_info);

qlcnic_मुक्त_sriov:
	kमुक्त(adapter->ahw->sriov);
	वापस err;
पूर्ण

व्योम qlcnic_sriov_cleanup_list(काष्ठा qlcnic_trans_list *t_list)
अणु
	काष्ठा qlcnic_bc_trans *trans;
	काष्ठा qlcnic_cmd_args cmd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&t_list->lock, flags);

	जबतक (!list_empty(&t_list->रुको_list)) अणु
		trans = list_first_entry(&t_list->रुको_list,
					 काष्ठा qlcnic_bc_trans, list);
		list_del(&trans->list);
		t_list->count--;
		cmd.req.arg = (u32 *)trans->req_pay;
		cmd.rsp.arg = (u32 *)trans->rsp_pay;
		qlcnic_मुक्त_mbx_args(&cmd);
		qlcnic_sriov_cleanup_transaction(trans);
	पूर्ण

	spin_unlock_irqrestore(&t_list->lock, flags);
पूर्ण

व्योम __qlcnic_sriov_cleanup(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	काष्ठा qlcnic_back_channel *bc = &sriov->bc;
	काष्ठा qlcnic_vf_info *vf;
	पूर्णांक i;

	अगर (!qlcnic_sriov_enable_check(adapter))
		वापस;

	qlcnic_sriov_cleanup_async_list(bc);
	destroy_workqueue(bc->bc_async_wq);

	क्रम (i = 0; i < sriov->num_vfs; i++) अणु
		vf = &sriov->vf_info[i];
		qlcnic_sriov_cleanup_list(&vf->rcv_pend);
		cancel_work_sync(&vf->trans_work);
		qlcnic_sriov_cleanup_list(&vf->rcv_act);
	पूर्ण

	destroy_workqueue(bc->bc_trans_wq);

	क्रम (i = 0; i < sriov->num_vfs; i++)
		kमुक्त(sriov->vf_info[i].vp);

	kमुक्त(sriov->vf_info);
	kमुक्त(adapter->ahw->sriov);
पूर्ण

अटल व्योम qlcnic_sriov_vf_cleanup(काष्ठा qlcnic_adapter *adapter)
अणु
	qlcnic_sriov_channel_cfg_cmd(adapter, QLCNIC_BC_CMD_CHANNEL_TERM);
	qlcnic_sriov_cfg_bc_पूर्णांकr(adapter, 0);
	__qlcnic_sriov_cleanup(adapter);
पूर्ण

व्योम qlcnic_sriov_cleanup(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (!test_bit(__QLCNIC_SRIOV_ENABLE, &adapter->state))
		वापस;

	qlcnic_sriov_मुक्त_vlans(adapter);

	अगर (qlcnic_sriov_pf_check(adapter))
		qlcnic_sriov_pf_cleanup(adapter);

	अगर (qlcnic_sriov_vf_check(adapter))
		qlcnic_sriov_vf_cleanup(adapter);
पूर्ण

अटल पूर्णांक qlcnic_sriov_post_bc_msg(काष्ठा qlcnic_adapter *adapter, u32 *hdr,
				    u32 *pay, u8 pci_func, u8 size)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_mailbox *mbx = ahw->mailbox;
	काष्ठा qlcnic_cmd_args cmd;
	अचिन्हित दीर्घ समयout;
	पूर्णांक err;

	स_रखो(&cmd, 0, माप(काष्ठा qlcnic_cmd_args));
	cmd.hdr = hdr;
	cmd.pay = pay;
	cmd.pay_size = size;
	cmd.func_num = pci_func;
	cmd.op_type = QLC_83XX_MBX_POST_BC_OP;
	cmd.cmd_op = ((काष्ठा qlcnic_bc_hdr *)hdr)->cmd_op;

	err = mbx->ops->enqueue_cmd(adapter, &cmd, &समयout);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"%s: Mailbox not available, cmd_op=0x%x, cmd_type=0x%x, pci_func=0x%x, op_mode=0x%x\n",
			__func__, cmd.cmd_op, cmd.type, ahw->pci_func,
			ahw->op_mode);
		वापस err;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&cmd.completion, समयout)) अणु
		dev_err(&adapter->pdev->dev,
			"%s: Mailbox command timed out, cmd_op=0x%x, cmd_type=0x%x, pci_func=0x%x, op_mode=0x%x\n",
			__func__, cmd.cmd_op, cmd.type, ahw->pci_func,
			ahw->op_mode);
		flush_workqueue(mbx->work_q);
	पूर्ण

	वापस cmd.rsp_opcode;
पूर्ण

अटल व्योम qlcnic_sriov_vf_cfg_buff_desc(काष्ठा qlcnic_adapter *adapter)
अणु
	adapter->num_rxd = QLC_DEFAULT_RCV_DESCRIPTORS_SRIOV_VF;
	adapter->max_rxd = MAX_RCV_DESCRIPTORS_10G;
	adapter->num_jumbo_rxd = QLC_DEFAULT_JUMBO_RCV_DESCRIPTORS_SRIOV_VF;
	adapter->max_jumbo_rxd = MAX_JUMBO_RCV_DESCRIPTORS_10G;
	adapter->num_txd = MAX_CMD_DESCRIPTORS;
	adapter->max_rds_rings = MAX_RDS_RINGS;
पूर्ण

पूर्णांक qlcnic_sriov_get_vf_vport_info(काष्ठा qlcnic_adapter *adapter,
				   काष्ठा qlcnic_info *npar_info, u16 vport_id)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक err;
	u32 status;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_NIC_INFO);
	अगर (err)
		वापस err;

	cmd.req.arg[1] = vport_id << 16 | 0x1;
	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"Failed to get vport info, err=%d\n", err);
		qlcnic_मुक्त_mbx_args(&cmd);
		वापस err;
	पूर्ण

	status = cmd.rsp.arg[2] & 0xffff;
	अगर (status & BIT_0)
		npar_info->min_tx_bw = MSW(cmd.rsp.arg[2]);
	अगर (status & BIT_1)
		npar_info->max_tx_bw = LSW(cmd.rsp.arg[3]);
	अगर (status & BIT_2)
		npar_info->max_tx_ques = MSW(cmd.rsp.arg[3]);
	अगर (status & BIT_3)
		npar_info->max_tx_mac_filters = LSW(cmd.rsp.arg[4]);
	अगर (status & BIT_4)
		npar_info->max_rx_mcast_mac_filters = MSW(cmd.rsp.arg[4]);
	अगर (status & BIT_5)
		npar_info->max_rx_ucast_mac_filters = LSW(cmd.rsp.arg[5]);
	अगर (status & BIT_6)
		npar_info->max_rx_ip_addr = MSW(cmd.rsp.arg[5]);
	अगर (status & BIT_7)
		npar_info->max_rx_lro_flow = LSW(cmd.rsp.arg[6]);
	अगर (status & BIT_8)
		npar_info->max_rx_status_rings = MSW(cmd.rsp.arg[6]);
	अगर (status & BIT_9)
		npar_info->max_rx_buf_rings = LSW(cmd.rsp.arg[7]);

	npar_info->max_rx_ques = MSW(cmd.rsp.arg[7]);
	npar_info->max_tx_vlan_keys = LSW(cmd.rsp.arg[8]);
	npar_info->max_local_ipv6_addrs = MSW(cmd.rsp.arg[8]);
	npar_info->max_remote_ipv6_addrs = LSW(cmd.rsp.arg[9]);

	dev_info(dev, "\n\tmin_tx_bw: %d, max_tx_bw: %d max_tx_ques: %d,\n"
		 "\tmax_tx_mac_filters: %d max_rx_mcast_mac_filters: %d,\n"
		 "\tmax_rx_ucast_mac_filters: 0x%x, max_rx_ip_addr: %d,\n"
		 "\tmax_rx_lro_flow: %d max_rx_status_rings: %d,\n"
		 "\tmax_rx_buf_rings: %d, max_rx_ques: %d, max_tx_vlan_keys %d\n"
		 "\tlocal_ipv6_addr: %d, remote_ipv6_addr: %d\n",
		 npar_info->min_tx_bw, npar_info->max_tx_bw,
		 npar_info->max_tx_ques, npar_info->max_tx_mac_filters,
		 npar_info->max_rx_mcast_mac_filters,
		 npar_info->max_rx_ucast_mac_filters, npar_info->max_rx_ip_addr,
		 npar_info->max_rx_lro_flow, npar_info->max_rx_status_rings,
		 npar_info->max_rx_buf_rings, npar_info->max_rx_ques,
		 npar_info->max_tx_vlan_keys, npar_info->max_local_ipv6_addrs,
		 npar_info->max_remote_ipv6_addrs);

	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_set_pvid_mode(काष्ठा qlcnic_adapter *adapter,
				      काष्ठा qlcnic_cmd_args *cmd)
अणु
	adapter->rx_pvid = MSW(cmd->rsp.arg[1]) & 0xffff;
	adapter->flags &= ~QLCNIC_TAGGING_ENABLED;
	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_set_guest_vlan_mode(काष्ठा qlcnic_adapter *adapter,
					    काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	पूर्णांक i, num_vlans;
	u16 *vlans;

	अगर (sriov->allowed_vlans)
		वापस 0;

	sriov->any_vlan = cmd->rsp.arg[2] & 0xf;
	sriov->num_allowed_vlans = cmd->rsp.arg[2] >> 16;
	dev_info(&adapter->pdev->dev, "Number of allowed Guest VLANs = %d\n",
		 sriov->num_allowed_vlans);

	qlcnic_sriov_alloc_vlans(adapter);

	अगर (!sriov->any_vlan)
		वापस 0;

	num_vlans = sriov->num_allowed_vlans;
	sriov->allowed_vlans = kसुस्मृति(num_vlans, माप(u16), GFP_KERNEL);
	अगर (!sriov->allowed_vlans)
		वापस -ENOMEM;

	vlans = (u16 *)&cmd->rsp.arg[3];
	क्रम (i = 0; i < num_vlans; i++)
		sriov->allowed_vlans[i] = vlans[i];

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_get_vf_acl(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक ret = 0;

	स_रखो(&cmd, 0, माप(cmd));
	ret = qlcnic_sriov_alloc_bc_mbx_args(&cmd, QLCNIC_BC_CMD_GET_ACL);
	अगर (ret)
		वापस ret;

	ret = qlcnic_issue_cmd(adapter, &cmd);
	अगर (ret) अणु
		dev_err(&adapter->pdev->dev, "Failed to get ACL, err=%d\n",
			ret);
	पूर्ण अन्यथा अणु
		sriov->vlan_mode = cmd.rsp.arg[1] & 0x3;
		चयन (sriov->vlan_mode) अणु
		हाल QLC_GUEST_VLAN_MODE:
			ret = qlcnic_sriov_set_guest_vlan_mode(adapter, &cmd);
			अवरोध;
		हाल QLC_PVID_MODE:
			ret = qlcnic_sriov_set_pvid_mode(adapter, &cmd);
			अवरोध;
		पूर्ण
	पूर्ण

	qlcnic_मुक्त_mbx_args(&cmd);
	वापस ret;
पूर्ण

अटल पूर्णांक qlcnic_sriov_vf_init_driver(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_info nic_info;
	पूर्णांक err;

	err = qlcnic_sriov_get_vf_vport_info(adapter, &nic_info, 0);
	अगर (err)
		वापस err;

	ahw->max_mc_count = nic_info.max_rx_mcast_mac_filters;

	err = qlcnic_get_nic_info(adapter, &nic_info, ahw->pci_func);
	अगर (err)
		वापस -EIO;

	अगर (qlcnic_83xx_get_port_info(adapter))
		वापस -EIO;

	qlcnic_sriov_vf_cfg_buff_desc(adapter);
	adapter->flags |= QLCNIC_ADAPTER_INITIALIZED;
	dev_info(&adapter->pdev->dev, "HAL Version: %d\n",
		 adapter->ahw->fw_hal_version);

	ahw->physical_port = (u8) nic_info.phys_port;
	ahw->चयन_mode = nic_info.चयन_mode;
	ahw->max_mtu = nic_info.max_mtu;
	ahw->op_mode = nic_info.op_mode;
	ahw->capabilities = nic_info.capabilities;
	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_setup_vf(काष्ठा qlcnic_adapter *adapter,
				 पूर्णांक pci_using_dac)
अणु
	पूर्णांक err;

	adapter->flags |= QLCNIC_VLAN_FILTERING;
	adapter->ahw->total_nic_func = 1;
	INIT_LIST_HEAD(&adapter->vf_mc_list);
	अगर (!qlcnic_use_msi_x && !!qlcnic_use_msi)
		dev_warn(&adapter->pdev->dev,
			 "Device does not support MSI interrupts\n");

	/* compute and set शेष and max tx/sds rings */
	qlcnic_set_tx_ring_count(adapter, QLCNIC_SINGLE_RING);
	qlcnic_set_sds_ring_count(adapter, QLCNIC_SINGLE_RING);

	err = qlcnic_setup_पूर्णांकr(adapter);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev, "Failed to setup interrupt\n");
		जाओ err_out_disable_msi;
	पूर्ण

	err = qlcnic_83xx_setup_mbx_पूर्णांकr(adapter);
	अगर (err)
		जाओ err_out_disable_msi;

	err = qlcnic_sriov_init(adapter, 1);
	अगर (err)
		जाओ err_out_disable_mbx_पूर्णांकr;

	err = qlcnic_sriov_cfg_bc_पूर्णांकr(adapter, 1);
	अगर (err)
		जाओ err_out_cleanup_sriov;

	err = qlcnic_sriov_channel_cfg_cmd(adapter, QLCNIC_BC_CMD_CHANNEL_INIT);
	अगर (err)
		जाओ err_out_disable_bc_पूर्णांकr;

	err = qlcnic_sriov_vf_init_driver(adapter);
	अगर (err)
		जाओ err_out_send_channel_term;

	err = qlcnic_sriov_get_vf_acl(adapter);
	अगर (err)
		जाओ err_out_send_channel_term;

	err = qlcnic_setup_netdev(adapter, adapter->netdev, pci_using_dac);
	अगर (err)
		जाओ err_out_send_channel_term;

	pci_set_drvdata(adapter->pdev, adapter);
	dev_info(&adapter->pdev->dev, "%s: XGbE port initialized\n",
		 adapter->netdev->name);

	qlcnic_schedule_work(adapter, qlcnic_sriov_vf_poll_dev_state,
			     adapter->ahw->idc.delay);
	वापस 0;

err_out_send_channel_term:
	qlcnic_sriov_channel_cfg_cmd(adapter, QLCNIC_BC_CMD_CHANNEL_TERM);

err_out_disable_bc_पूर्णांकr:
	qlcnic_sriov_cfg_bc_पूर्णांकr(adapter, 0);

err_out_cleanup_sriov:
	__qlcnic_sriov_cleanup(adapter);

err_out_disable_mbx_पूर्णांकr:
	qlcnic_83xx_मुक्त_mbx_पूर्णांकr(adapter);

err_out_disable_msi:
	qlcnic_tearकरोwn_पूर्णांकr(adapter);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_check_dev_पढ़ोy(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 state;

	करो अणु
		msleep(20);
		अगर (++adapter->fw_fail_cnt > QLC_BC_CMD_MAX_RETRY_CNT)
			वापस -EIO;
		state = QLCRDX(adapter->ahw, QLC_83XX_IDC_DEV_STATE);
	पूर्ण जबतक (state != QLC_83XX_IDC_DEV_READY);

	वापस 0;
पूर्ण

पूर्णांक qlcnic_sriov_vf_init(काष्ठा qlcnic_adapter *adapter, पूर्णांक pci_using_dac)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक err;

	set_bit(QLC_83XX_MODULE_LOADED, &ahw->idc.status);
	ahw->idc.delay = QLC_83XX_IDC_FW_POLL_DELAY;
	ahw->reset_context = 0;
	adapter->fw_fail_cnt = 0;
	ahw->msix_supported = 1;
	adapter->need_fw_reset = 0;
	adapter->flags |= QLCNIC_TX_INTR_SHARED;

	err = qlcnic_sriov_check_dev_पढ़ोy(adapter);
	अगर (err)
		वापस err;

	err = qlcnic_sriov_setup_vf(adapter, pci_using_dac);
	अगर (err)
		वापस err;

	अगर (qlcnic_पढ़ो_mac_addr(adapter))
		dev_warn(&adapter->pdev->dev, "failed to read mac addr\n");

	INIT_DELAYED_WORK(&adapter->idc_aen_work, qlcnic_83xx_idc_aen_work);

	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	वापस 0;
पूर्ण

व्योम qlcnic_sriov_vf_set_ops(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	ahw->op_mode = QLCNIC_SRIOV_VF_FUNC;
	dev_info(&adapter->pdev->dev,
		 "HAL Version: %d Non Privileged SRIOV function\n",
		 ahw->fw_hal_version);
	adapter->nic_ops = &qlcnic_sriov_vf_ops;
	set_bit(__QLCNIC_SRIOV_ENABLE, &adapter->state);
	वापस;
पूर्ण

व्योम qlcnic_sriov_vf_रेजिस्टर_map(काष्ठा qlcnic_hardware_context *ahw)
अणु
	ahw->hw_ops		= &qlcnic_sriov_vf_hw_ops;
	ahw->reg_tbl		= (u32 *)qlcnic_83xx_reg_tbl;
	ahw->ext_reg_tbl	= (u32 *)qlcnic_83xx_ext_reg_tbl;
पूर्ण

अटल u32 qlcnic_sriov_get_bc_paysize(u32 real_pay_size, u8 curr_frag)
अणु
	u32 pay_size;

	pay_size = real_pay_size / ((curr_frag + 1) * QLC_BC_PAYLOAD_SZ);

	अगर (pay_size)
		pay_size = QLC_BC_PAYLOAD_SZ;
	अन्यथा
		pay_size = real_pay_size % QLC_BC_PAYLOAD_SZ;

	वापस pay_size;
पूर्ण

पूर्णांक qlcnic_sriov_func_to_index(काष्ठा qlcnic_adapter *adapter, u8 pci_func)
अणु
	काष्ठा qlcnic_vf_info *vf_info = adapter->ahw->sriov->vf_info;
	u8 i;

	अगर (qlcnic_sriov_vf_check(adapter))
		वापस 0;

	क्रम (i = 0; i < adapter->ahw->sriov->num_vfs; i++) अणु
		अगर (vf_info[i].pci_func == pci_func)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_sriov_alloc_bc_trans(काष्ठा qlcnic_bc_trans **trans)
अणु
	*trans = kzalloc(माप(काष्ठा qlcnic_bc_trans), GFP_ATOMIC);
	अगर (!*trans)
		वापस -ENOMEM;

	init_completion(&(*trans)->resp_cmpl);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_sriov_alloc_bc_msg(काष्ठा qlcnic_bc_hdr **hdr,
					    u32 size)
अणु
	*hdr = kसुस्मृति(size, माप(काष्ठा qlcnic_bc_hdr), GFP_ATOMIC);
	अगर (!*hdr)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_alloc_bc_mbx_args(काष्ठा qlcnic_cmd_args *mbx, u32 type)
अणु
	स्थिर काष्ठा qlcnic_mailbox_metadata *mbx_tbl;
	पूर्णांक i, size;

	mbx_tbl = qlcnic_sriov_bc_mbx_tbl;
	size = ARRAY_SIZE(qlcnic_sriov_bc_mbx_tbl);

	क्रम (i = 0; i < size; i++) अणु
		अगर (type == mbx_tbl[i].cmd) अणु
			mbx->op_type = QLC_BC_CMD;
			mbx->req.num = mbx_tbl[i].in_args;
			mbx->rsp.num = mbx_tbl[i].out_args;
			mbx->req.arg = kसुस्मृति(mbx->req.num, माप(u32),
					       GFP_ATOMIC);
			अगर (!mbx->req.arg)
				वापस -ENOMEM;
			mbx->rsp.arg = kसुस्मृति(mbx->rsp.num, माप(u32),
					       GFP_ATOMIC);
			अगर (!mbx->rsp.arg) अणु
				kमुक्त(mbx->req.arg);
				mbx->req.arg = शून्य;
				वापस -ENOMEM;
			पूर्ण
			mbx->req.arg[0] = (type | (mbx->req.num << 16) |
					   (3 << 29));
			mbx->rsp.arg[0] = (type & 0xffff) | mbx->rsp.num << 16;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक qlcnic_sriov_prepare_bc_hdr(काष्ठा qlcnic_bc_trans *trans,
				       काष्ठा qlcnic_cmd_args *cmd,
				       u16 seq, u8 msg_type)
अणु
	काष्ठा qlcnic_bc_hdr *hdr;
	पूर्णांक i;
	u32 num_regs, bc_pay_sz;
	u16 reमुख्यder;
	u8 cmd_op, num_frags, t_num_frags;

	bc_pay_sz = QLC_BC_PAYLOAD_SZ;
	अगर (msg_type == QLC_BC_COMMAND) अणु
		trans->req_pay = (काष्ठा qlcnic_bc_payload *)cmd->req.arg;
		trans->rsp_pay = (काष्ठा qlcnic_bc_payload *)cmd->rsp.arg;
		num_regs = cmd->req.num;
		trans->req_pay_size = (num_regs * 4);
		num_regs = cmd->rsp.num;
		trans->rsp_pay_size = (num_regs * 4);
		cmd_op = cmd->req.arg[0] & 0xff;
		reमुख्यder = (trans->req_pay_size) % (bc_pay_sz);
		num_frags = (trans->req_pay_size) / (bc_pay_sz);
		अगर (reमुख्यder)
			num_frags++;
		t_num_frags = num_frags;
		अगर (qlcnic_sriov_alloc_bc_msg(&trans->req_hdr, num_frags))
			वापस -ENOMEM;
		reमुख्यder = (trans->rsp_pay_size) % (bc_pay_sz);
		num_frags = (trans->rsp_pay_size) / (bc_pay_sz);
		अगर (reमुख्यder)
			num_frags++;
		अगर (qlcnic_sriov_alloc_bc_msg(&trans->rsp_hdr, num_frags))
			वापस -ENOMEM;
		num_frags  = t_num_frags;
		hdr = trans->req_hdr;
	पूर्ण  अन्यथा अणु
		cmd->req.arg = (u32 *)trans->req_pay;
		cmd->rsp.arg = (u32 *)trans->rsp_pay;
		cmd_op = cmd->req.arg[0] & 0xff;
		cmd->cmd_op = cmd_op;
		reमुख्यder = (trans->rsp_pay_size) % (bc_pay_sz);
		num_frags = (trans->rsp_pay_size) / (bc_pay_sz);
		अगर (reमुख्यder)
			num_frags++;
		cmd->req.num = trans->req_pay_size / 4;
		cmd->rsp.num = trans->rsp_pay_size / 4;
		hdr = trans->rsp_hdr;
		cmd->op_type = trans->req_hdr->op_type;
	पूर्ण

	trans->trans_id = seq;
	trans->cmd_id = cmd_op;
	क्रम (i = 0; i < num_frags; i++) अणु
		hdr[i].version = 2;
		hdr[i].msg_type = msg_type;
		hdr[i].op_type = cmd->op_type;
		hdr[i].num_cmds = 1;
		hdr[i].num_frags = num_frags;
		hdr[i].frag_num = i + 1;
		hdr[i].cmd_op = cmd_op;
		hdr[i].seq_id = seq;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम qlcnic_sriov_cleanup_transaction(काष्ठा qlcnic_bc_trans *trans)
अणु
	अगर (!trans)
		वापस;
	kमुक्त(trans->req_hdr);
	kमुक्त(trans->rsp_hdr);
	kमुक्त(trans);
पूर्ण

अटल पूर्णांक qlcnic_sriov_clear_trans(काष्ठा qlcnic_vf_info *vf,
				    काष्ठा qlcnic_bc_trans *trans, u8 type)
अणु
	काष्ठा qlcnic_trans_list *t_list;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (type == QLC_BC_RESPONSE) अणु
		t_list = &vf->rcv_act;
		spin_lock_irqsave(&t_list->lock, flags);
		t_list->count--;
		list_del(&trans->list);
		अगर (t_list->count > 0)
			ret = 1;
		spin_unlock_irqrestore(&t_list->lock, flags);
	पूर्ण
	अगर (type == QLC_BC_COMMAND) अणु
		जबतक (test_and_set_bit(QLC_BC_VF_SEND, &vf->state))
			msleep(100);
		vf->send_cmd = शून्य;
		clear_bit(QLC_BC_VF_SEND, &vf->state);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम qlcnic_sriov_schedule_bc_cmd(काष्ठा qlcnic_sriov *sriov,
					 काष्ठा qlcnic_vf_info *vf,
					 work_func_t func)
अणु
	अगर (test_bit(QLC_BC_VF_FLR, &vf->state) ||
	    vf->adapter->need_fw_reset)
		वापस;

	queue_work(sriov->bc.bc_trans_wq, &vf->trans_work);
पूर्ण

अटल अंतरभूत व्योम qlcnic_sriov_रुको_क्रम_resp(काष्ठा qlcnic_bc_trans *trans)
अणु
	काष्ठा completion *cmpl = &trans->resp_cmpl;

	अगर (रुको_क्रम_completion_समयout(cmpl, QLC_MBOX_RESP_TIMEOUT))
		trans->trans_state = QLC_END;
	अन्यथा
		trans->trans_state = QLC_ABORT;

	वापस;
पूर्ण

अटल व्योम qlcnic_sriov_handle_multi_frags(काष्ठा qlcnic_bc_trans *trans,
					    u8 type)
अणु
	अगर (type == QLC_BC_RESPONSE) अणु
		trans->curr_rsp_frag++;
		अगर (trans->curr_rsp_frag < trans->rsp_hdr->num_frags)
			trans->trans_state = QLC_INIT;
		अन्यथा
			trans->trans_state = QLC_END;
	पूर्ण अन्यथा अणु
		trans->curr_req_frag++;
		अगर (trans->curr_req_frag < trans->req_hdr->num_frags)
			trans->trans_state = QLC_INIT;
		अन्यथा
			trans->trans_state = QLC_WAIT_FOR_RESP;
	पूर्ण
पूर्ण

अटल व्योम qlcnic_sriov_रुको_क्रम_channel_मुक्त(काष्ठा qlcnic_bc_trans *trans,
					       u8 type)
अणु
	काष्ठा qlcnic_vf_info *vf = trans->vf;
	काष्ठा completion *cmpl = &vf->ch_मुक्त_cmpl;

	अगर (!रुको_क्रम_completion_समयout(cmpl, QLC_MBOX_CH_FREE_TIMEOUT)) अणु
		trans->trans_state = QLC_ABORT;
		वापस;
	पूर्ण

	clear_bit(QLC_BC_VF_CHANNEL, &vf->state);
	qlcnic_sriov_handle_multi_frags(trans, type);
पूर्ण

अटल व्योम qlcnic_sriov_pull_bc_msg(काष्ठा qlcnic_adapter *adapter,
				     u32 *hdr, u32 *pay, u32 size)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	u8 i, max = 2, hdr_size, j;

	hdr_size = (माप(काष्ठा qlcnic_bc_hdr) / माप(u32));
	max = (size / माप(u32)) + hdr_size;

	क्रम (i = 2, j = 0; j < hdr_size; i++, j++)
		*(hdr++) = पढ़ोl(QLCNIC_MBX_FW(ahw, i));
	क्रम (; j < max; i++, j++)
		*(pay++) = पढ़ोl(QLCNIC_MBX_FW(ahw, i));
पूर्ण

अटल पूर्णांक __qlcnic_sriov_issue_bc_post(काष्ठा qlcnic_vf_info *vf)
अणु
	पूर्णांक ret = -EBUSY;
	u32 समयout = 10000;

	करो अणु
		अगर (!test_and_set_bit(QLC_BC_VF_CHANNEL, &vf->state)) अणु
			ret = 0;
			अवरोध;
		पूर्ण
		mdelay(1);
	पूर्ण जबतक (--समयout);

	वापस ret;
पूर्ण

अटल पूर्णांक qlcnic_sriov_issue_bc_post(काष्ठा qlcnic_bc_trans *trans, u8 type)
अणु
	काष्ठा qlcnic_vf_info *vf = trans->vf;
	u32 pay_size;
	u32 *hdr, *pay;
	पूर्णांक ret;
	u8 pci_func = trans->func_id;

	अगर (__qlcnic_sriov_issue_bc_post(vf))
		वापस -EBUSY;

	अगर (type == QLC_BC_COMMAND) अणु
		hdr = (u32 *)(trans->req_hdr + trans->curr_req_frag);
		pay = (u32 *)(trans->req_pay + trans->curr_req_frag);
		pay_size = qlcnic_sriov_get_bc_paysize(trans->req_pay_size,
						       trans->curr_req_frag);
		pay_size = (pay_size / माप(u32));
	पूर्ण अन्यथा अणु
		hdr = (u32 *)(trans->rsp_hdr + trans->curr_rsp_frag);
		pay = (u32 *)(trans->rsp_pay + trans->curr_rsp_frag);
		pay_size = qlcnic_sriov_get_bc_paysize(trans->rsp_pay_size,
						       trans->curr_rsp_frag);
		pay_size = (pay_size / माप(u32));
	पूर्ण

	ret = qlcnic_sriov_post_bc_msg(vf->adapter, hdr, pay,
				       pci_func, pay_size);
	वापस ret;
पूर्ण

अटल पूर्णांक __qlcnic_sriov_send_bc_msg(काष्ठा qlcnic_bc_trans *trans,
				      काष्ठा qlcnic_vf_info *vf, u8 type)
अणु
	bool flag = true;
	पूर्णांक err = -EIO;

	जबतक (flag) अणु
		अगर (test_bit(QLC_BC_VF_FLR, &vf->state) ||
		    vf->adapter->need_fw_reset)
			trans->trans_state = QLC_ABORT;

		चयन (trans->trans_state) अणु
		हाल QLC_INIT:
			trans->trans_state = QLC_WAIT_FOR_CHANNEL_FREE;
			अगर (qlcnic_sriov_issue_bc_post(trans, type))
				trans->trans_state = QLC_ABORT;
			अवरोध;
		हाल QLC_WAIT_FOR_CHANNEL_FREE:
			qlcnic_sriov_रुको_क्रम_channel_मुक्त(trans, type);
			अवरोध;
		हाल QLC_WAIT_FOR_RESP:
			qlcnic_sriov_रुको_क्रम_resp(trans);
			अवरोध;
		हाल QLC_END:
			err = 0;
			flag = false;
			अवरोध;
		हाल QLC_ABORT:
			err = -EIO;
			flag = false;
			clear_bit(QLC_BC_VF_CHANNEL, &vf->state);
			अवरोध;
		शेष:
			err = -EIO;
			flag = false;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_send_bc_cmd(काष्ठा qlcnic_adapter *adapter,
				    काष्ठा qlcnic_bc_trans *trans, पूर्णांक pci_func)
अणु
	काष्ठा qlcnic_vf_info *vf;
	पूर्णांक err, index = qlcnic_sriov_func_to_index(adapter, pci_func);

	अगर (index < 0)
		वापस -EIO;

	vf = &adapter->ahw->sriov->vf_info[index];
	trans->vf = vf;
	trans->func_id = pci_func;

	अगर (!test_bit(QLC_BC_VF_STATE, &vf->state)) अणु
		अगर (qlcnic_sriov_pf_check(adapter))
			वापस -EIO;
		अगर (qlcnic_sriov_vf_check(adapter) &&
		    trans->cmd_id != QLCNIC_BC_CMD_CHANNEL_INIT)
			वापस -EIO;
	पूर्ण

	mutex_lock(&vf->send_cmd_lock);
	vf->send_cmd = trans;
	err = __qlcnic_sriov_send_bc_msg(trans, vf, QLC_BC_COMMAND);
	qlcnic_sriov_clear_trans(vf, trans, QLC_BC_COMMAND);
	mutex_unlock(&vf->send_cmd_lock);
	वापस err;
पूर्ण

अटल व्योम __qlcnic_sriov_process_bc_cmd(काष्ठा qlcnic_adapter *adapter,
					  काष्ठा qlcnic_bc_trans *trans,
					  काष्ठा qlcnic_cmd_args *cmd)
अणु
#अगर_घोषित CONFIG_QLCNIC_SRIOV
	अगर (qlcnic_sriov_pf_check(adapter)) अणु
		qlcnic_sriov_pf_process_bc_cmd(adapter, trans, cmd);
		वापस;
	पूर्ण
#पूर्ण_अगर
	cmd->rsp.arg[0] |= (0x9 << 25);
	वापस;
पूर्ण

अटल व्योम qlcnic_sriov_process_bc_cmd(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlcnic_vf_info *vf = container_of(work, काष्ठा qlcnic_vf_info,
						 trans_work);
	काष्ठा qlcnic_bc_trans *trans = शून्य;
	काष्ठा qlcnic_adapter *adapter  = vf->adapter;
	काष्ठा qlcnic_cmd_args cmd;
	u8 req;

	अगर (adapter->need_fw_reset)
		वापस;

	अगर (test_bit(QLC_BC_VF_FLR, &vf->state))
		वापस;

	स_रखो(&cmd, 0, माप(काष्ठा qlcnic_cmd_args));
	trans = list_first_entry(&vf->rcv_act.रुको_list,
				 काष्ठा qlcnic_bc_trans, list);
	adapter = vf->adapter;

	अगर (qlcnic_sriov_prepare_bc_hdr(trans, &cmd, trans->req_hdr->seq_id,
					QLC_BC_RESPONSE))
		जाओ cleanup_trans;

	__qlcnic_sriov_process_bc_cmd(adapter, trans, &cmd);
	trans->trans_state = QLC_INIT;
	__qlcnic_sriov_send_bc_msg(trans, vf, QLC_BC_RESPONSE);

cleanup_trans:
	qlcnic_मुक्त_mbx_args(&cmd);
	req = qlcnic_sriov_clear_trans(vf, trans, QLC_BC_RESPONSE);
	qlcnic_sriov_cleanup_transaction(trans);
	अगर (req)
		qlcnic_sriov_schedule_bc_cmd(adapter->ahw->sriov, vf,
					     qlcnic_sriov_process_bc_cmd);
पूर्ण

अटल व्योम qlcnic_sriov_handle_bc_resp(काष्ठा qlcnic_bc_hdr *hdr,
					काष्ठा qlcnic_vf_info *vf)
अणु
	काष्ठा qlcnic_bc_trans *trans;
	u32 pay_size;

	अगर (test_and_set_bit(QLC_BC_VF_SEND, &vf->state))
		वापस;

	trans = vf->send_cmd;

	अगर (trans == शून्य)
		जाओ clear_send;

	अगर (trans->trans_id != hdr->seq_id)
		जाओ clear_send;

	pay_size = qlcnic_sriov_get_bc_paysize(trans->rsp_pay_size,
					       trans->curr_rsp_frag);
	qlcnic_sriov_pull_bc_msg(vf->adapter,
				 (u32 *)(trans->rsp_hdr + trans->curr_rsp_frag),
				 (u32 *)(trans->rsp_pay + trans->curr_rsp_frag),
				 pay_size);
	अगर (++trans->curr_rsp_frag < trans->rsp_hdr->num_frags)
		जाओ clear_send;

	complete(&trans->resp_cmpl);

clear_send:
	clear_bit(QLC_BC_VF_SEND, &vf->state);
पूर्ण

पूर्णांक __qlcnic_sriov_add_act_list(काष्ठा qlcnic_sriov *sriov,
				काष्ठा qlcnic_vf_info *vf,
				काष्ठा qlcnic_bc_trans *trans)
अणु
	काष्ठा qlcnic_trans_list *t_list = &vf->rcv_act;

	t_list->count++;
	list_add_tail(&trans->list, &t_list->रुको_list);
	अगर (t_list->count == 1)
		qlcnic_sriov_schedule_bc_cmd(sriov, vf,
					     qlcnic_sriov_process_bc_cmd);
	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_add_act_list(काष्ठा qlcnic_sriov *sriov,
				     काष्ठा qlcnic_vf_info *vf,
				     काष्ठा qlcnic_bc_trans *trans)
अणु
	काष्ठा qlcnic_trans_list *t_list = &vf->rcv_act;

	spin_lock(&t_list->lock);

	__qlcnic_sriov_add_act_list(sriov, vf, trans);

	spin_unlock(&t_list->lock);
	वापस 0;
पूर्ण

अटल व्योम qlcnic_sriov_handle_pending_trans(काष्ठा qlcnic_sriov *sriov,
					      काष्ठा qlcnic_vf_info *vf,
					      काष्ठा qlcnic_bc_hdr *hdr)
अणु
	काष्ठा qlcnic_bc_trans *trans = शून्य;
	काष्ठा list_head *node;
	u32 pay_size, curr_frag;
	u8 found = 0, active = 0;

	spin_lock(&vf->rcv_pend.lock);
	अगर (vf->rcv_pend.count > 0) अणु
		list_क्रम_each(node, &vf->rcv_pend.रुको_list) अणु
			trans = list_entry(node, काष्ठा qlcnic_bc_trans, list);
			अगर (trans->trans_id == hdr->seq_id) अणु
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (found) अणु
		curr_frag = trans->curr_req_frag;
		pay_size = qlcnic_sriov_get_bc_paysize(trans->req_pay_size,
						       curr_frag);
		qlcnic_sriov_pull_bc_msg(vf->adapter,
					 (u32 *)(trans->req_hdr + curr_frag),
					 (u32 *)(trans->req_pay + curr_frag),
					 pay_size);
		trans->curr_req_frag++;
		अगर (trans->curr_req_frag >= hdr->num_frags) अणु
			vf->rcv_pend.count--;
			list_del(&trans->list);
			active = 1;
		पूर्ण
	पूर्ण
	spin_unlock(&vf->rcv_pend.lock);

	अगर (active)
		अगर (qlcnic_sriov_add_act_list(sriov, vf, trans))
			qlcnic_sriov_cleanup_transaction(trans);

	वापस;
पूर्ण

अटल व्योम qlcnic_sriov_handle_bc_cmd(काष्ठा qlcnic_sriov *sriov,
				       काष्ठा qlcnic_bc_hdr *hdr,
				       काष्ठा qlcnic_vf_info *vf)
अणु
	काष्ठा qlcnic_bc_trans *trans;
	काष्ठा qlcnic_adapter *adapter = vf->adapter;
	काष्ठा qlcnic_cmd_args cmd;
	u32 pay_size;
	पूर्णांक err;
	u8 cmd_op;

	अगर (adapter->need_fw_reset)
		वापस;

	अगर (!test_bit(QLC_BC_VF_STATE, &vf->state) &&
	    hdr->op_type != QLC_BC_CMD &&
	    hdr->cmd_op != QLCNIC_BC_CMD_CHANNEL_INIT)
		वापस;

	अगर (hdr->frag_num > 1) अणु
		qlcnic_sriov_handle_pending_trans(sriov, vf, hdr);
		वापस;
	पूर्ण

	स_रखो(&cmd, 0, माप(काष्ठा qlcnic_cmd_args));
	cmd_op = hdr->cmd_op;
	अगर (qlcnic_sriov_alloc_bc_trans(&trans))
		वापस;

	अगर (hdr->op_type == QLC_BC_CMD)
		err = qlcnic_sriov_alloc_bc_mbx_args(&cmd, cmd_op);
	अन्यथा
		err = qlcnic_alloc_mbx_args(&cmd, adapter, cmd_op);

	अगर (err) अणु
		qlcnic_sriov_cleanup_transaction(trans);
		वापस;
	पूर्ण

	cmd.op_type = hdr->op_type;
	अगर (qlcnic_sriov_prepare_bc_hdr(trans, &cmd, hdr->seq_id,
					QLC_BC_COMMAND)) अणु
		qlcnic_मुक्त_mbx_args(&cmd);
		qlcnic_sriov_cleanup_transaction(trans);
		वापस;
	पूर्ण

	pay_size = qlcnic_sriov_get_bc_paysize(trans->req_pay_size,
					 trans->curr_req_frag);
	qlcnic_sriov_pull_bc_msg(vf->adapter,
				 (u32 *)(trans->req_hdr + trans->curr_req_frag),
				 (u32 *)(trans->req_pay + trans->curr_req_frag),
				 pay_size);
	trans->func_id = vf->pci_func;
	trans->vf = vf;
	trans->trans_id = hdr->seq_id;
	trans->curr_req_frag++;

	अगर (qlcnic_sriov_soft_flr_check(adapter, trans, vf))
		वापस;

	अगर (trans->curr_req_frag == trans->req_hdr->num_frags) अणु
		अगर (qlcnic_sriov_add_act_list(sriov, vf, trans)) अणु
			qlcnic_मुक्त_mbx_args(&cmd);
			qlcnic_sriov_cleanup_transaction(trans);
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_lock(&vf->rcv_pend.lock);
		list_add_tail(&trans->list, &vf->rcv_pend.रुको_list);
		vf->rcv_pend.count++;
		spin_unlock(&vf->rcv_pend.lock);
	पूर्ण
पूर्ण

अटल व्योम qlcnic_sriov_handle_msg_event(काष्ठा qlcnic_sriov *sriov,
					  काष्ठा qlcnic_vf_info *vf)
अणु
	काष्ठा qlcnic_bc_hdr hdr;
	u32 *ptr = (u32 *)&hdr;
	u8 msg_type, i;

	क्रम (i = 2; i < 6; i++)
		ptr[i - 2] = पढ़ोl(QLCNIC_MBX_FW(vf->adapter->ahw, i));
	msg_type = hdr.msg_type;

	चयन (msg_type) अणु
	हाल QLC_BC_COMMAND:
		qlcnic_sriov_handle_bc_cmd(sriov, &hdr, vf);
		अवरोध;
	हाल QLC_BC_RESPONSE:
		qlcnic_sriov_handle_bc_resp(&hdr, vf);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम qlcnic_sriov_handle_flr_event(काष्ठा qlcnic_sriov *sriov,
					  काष्ठा qlcnic_vf_info *vf)
अणु
	काष्ठा qlcnic_adapter *adapter = vf->adapter;

	अगर (qlcnic_sriov_pf_check(adapter))
		qlcnic_sriov_pf_handle_flr(sriov, vf);
	अन्यथा
		dev_err(&adapter->pdev->dev,
			"Invalid event to VF. VF should not get FLR event\n");
पूर्ण

व्योम qlcnic_sriov_handle_bc_event(काष्ठा qlcnic_adapter *adapter, u32 event)
अणु
	काष्ठा qlcnic_vf_info *vf;
	काष्ठा qlcnic_sriov *sriov;
	पूर्णांक index;
	u8 pci_func;

	sriov = adapter->ahw->sriov;
	pci_func = qlcnic_sriov_target_func_id(event);
	index = qlcnic_sriov_func_to_index(adapter, pci_func);

	अगर (index < 0)
		वापस;

	vf = &sriov->vf_info[index];
	vf->pci_func = pci_func;

	अगर (qlcnic_sriov_channel_मुक्त_check(event))
		complete(&vf->ch_मुक्त_cmpl);

	अगर (qlcnic_sriov_flr_check(event)) अणु
		qlcnic_sriov_handle_flr_event(sriov, vf);
		वापस;
	पूर्ण

	अगर (qlcnic_sriov_bc_msg_check(event))
		qlcnic_sriov_handle_msg_event(sriov, vf);
पूर्ण

पूर्णांक qlcnic_sriov_cfg_bc_पूर्णांकr(काष्ठा qlcnic_adapter *adapter, u8 enable)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक err;

	अगर (!test_bit(__QLCNIC_SRIOV_ENABLE, &adapter->state))
		वापस 0;

	अगर (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_BC_EVENT_SETUP))
		वापस -ENOMEM;

	अगर (enable)
		cmd.req.arg[1] = (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);

	err = qlcnic_83xx_issue_cmd(adapter, &cmd);

	अगर (err != QLCNIC_RCODE_SUCCESS) अणु
		dev_err(&adapter->pdev->dev,
			"Failed to %s bc events, err=%d\n",
			(enable ? "enable" : "disable"), err);
	पूर्ण

	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_retry_bc_cmd(काष्ठा qlcnic_adapter *adapter,
				     काष्ठा qlcnic_bc_trans *trans)
अणु
	u8 max = QLC_BC_CMD_MAX_RETRY_CNT;
	u32 state;

	state = QLCRDX(adapter->ahw, QLC_83XX_IDC_DEV_STATE);
	अगर (state == QLC_83XX_IDC_DEV_READY) अणु
		msleep(20);
		clear_bit(QLC_BC_VF_CHANNEL, &trans->vf->state);
		trans->trans_state = QLC_INIT;
		अगर (++adapter->fw_fail_cnt > max)
			वापस -EIO;
		अन्यथा
			वापस 0;
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक __qlcnic_sriov_issue_cmd(काष्ठा qlcnic_adapter *adapter,
				  काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_mailbox *mbx = ahw->mailbox;
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा qlcnic_bc_trans *trans;
	पूर्णांक err;
	u32 rsp_data, opcode, mbx_err_code, rsp;
	u16 seq = ++adapter->ahw->sriov->bc.trans_counter;
	u8 func = ahw->pci_func;

	rsp = qlcnic_sriov_alloc_bc_trans(&trans);
	अगर (rsp)
		जाओ मुक्त_cmd;

	rsp = qlcnic_sriov_prepare_bc_hdr(trans, cmd, seq, QLC_BC_COMMAND);
	अगर (rsp)
		जाओ cleanup_transaction;

retry:
	अगर (!test_bit(QLC_83XX_MBX_READY, &mbx->status)) अणु
		rsp = -EIO;
		QLCDB(adapter, DRV, "MBX not Ready!(cmd 0x%x) for VF 0x%x\n",
		      QLCNIC_MBX_RSP(cmd->req.arg[0]), func);
		जाओ err_out;
	पूर्ण

	err = qlcnic_sriov_send_bc_cmd(adapter, trans, func);
	अगर (err) अणु
		dev_err(dev, "MBX command 0x%x timed out for VF %d\n",
			(cmd->req.arg[0] & 0xffff), func);
		rsp = QLCNIC_RCODE_TIMEOUT;

		/* After adapter reset PF driver may take some समय to
		 * respond to VF's request. Retry request till maximum retries.
		 */
		अगर ((trans->req_hdr->cmd_op == QLCNIC_BC_CMD_CHANNEL_INIT) &&
		    !qlcnic_sriov_retry_bc_cmd(adapter, trans))
			जाओ retry;

		जाओ err_out;
	पूर्ण

	rsp_data = cmd->rsp.arg[0];
	mbx_err_code = QLCNIC_MBX_STATUS(rsp_data);
	opcode = QLCNIC_MBX_RSP(cmd->req.arg[0]);

	अगर ((mbx_err_code == QLCNIC_MBX_RSP_OK) ||
	    (mbx_err_code == QLCNIC_MBX_PORT_RSP_OK)) अणु
		rsp = QLCNIC_RCODE_SUCCESS;
	पूर्ण अन्यथा अणु
		अगर (cmd->type == QLC_83XX_MBX_CMD_NO_WAIT) अणु
			rsp = QLCNIC_RCODE_SUCCESS;
		पूर्ण अन्यथा अणु
			rsp = mbx_err_code;
			अगर (!rsp)
				rsp = 1;

			dev_err(dev,
				"MBX command 0x%x failed with err:0x%x for VF %d\n",
				opcode, mbx_err_code, func);
		पूर्ण
	पूर्ण

err_out:
	अगर (rsp == QLCNIC_RCODE_TIMEOUT) अणु
		ahw->reset_context = 1;
		adapter->need_fw_reset = 1;
		clear_bit(QLC_83XX_MBX_READY, &mbx->status);
	पूर्ण

cleanup_transaction:
	qlcnic_sriov_cleanup_transaction(trans);

मुक्त_cmd:
	अगर (cmd->type == QLC_83XX_MBX_CMD_NO_WAIT) अणु
		qlcnic_मुक्त_mbx_args(cmd);
		kमुक्त(cmd);
	पूर्ण

	वापस rsp;
पूर्ण


अटल पूर्णांक qlcnic_sriov_issue_cmd(काष्ठा qlcnic_adapter *adapter,
				  काष्ठा qlcnic_cmd_args *cmd)
अणु
	अगर (cmd->type == QLC_83XX_MBX_CMD_NO_WAIT)
		वापस qlcnic_sriov_async_issue_cmd(adapter, cmd);
	अन्यथा
		वापस __qlcnic_sriov_issue_cmd(adapter, cmd);
पूर्ण

अटल पूर्णांक qlcnic_sriov_channel_cfg_cmd(काष्ठा qlcnic_adapter *adapter, u8 cmd_op)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	काष्ठा qlcnic_vf_info *vf = &adapter->ahw->sriov->vf_info[0];
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	अगर (qlcnic_sriov_alloc_bc_mbx_args(&cmd, cmd_op))
		वापस -ENOMEM;

	ret = qlcnic_issue_cmd(adapter, &cmd);
	अगर (ret) अणु
		dev_err(&adapter->pdev->dev,
			"Failed bc channel %s %d\n", cmd_op ? "term" : "init",
			ret);
		जाओ out;
	पूर्ण

	cmd_op = (cmd.rsp.arg[0] & 0xff);
	अगर (cmd.rsp.arg[0] >> 25 == 2)
		वापस 2;
	अगर (cmd_op == QLCNIC_BC_CMD_CHANNEL_INIT)
		set_bit(QLC_BC_VF_STATE, &vf->state);
	अन्यथा
		clear_bit(QLC_BC_VF_STATE, &vf->state);

out:
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस ret;
पूर्ण

अटल व्योम qlcnic_vf_add_mc_list(काष्ठा net_device *netdev, स्थिर u8 *mac,
				  क्रमागत qlcnic_mac_type mac_type)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	काष्ठा qlcnic_vf_info *vf;
	u16 vlan_id;
	पूर्णांक i;

	vf = &adapter->ahw->sriov->vf_info[0];

	अगर (!qlcnic_sriov_check_any_vlan(vf)) अणु
		qlcnic_nic_add_mac(adapter, mac, 0, mac_type);
	पूर्ण अन्यथा अणु
		spin_lock(&vf->vlan_list_lock);
		क्रम (i = 0; i < sriov->num_allowed_vlans; i++) अणु
			vlan_id = vf->sriov_vlans[i];
			अगर (vlan_id)
				qlcnic_nic_add_mac(adapter, mac, vlan_id,
						   mac_type);
		पूर्ण
		spin_unlock(&vf->vlan_list_lock);
		अगर (qlcnic_84xx_check(adapter))
			qlcnic_nic_add_mac(adapter, mac, 0, mac_type);
	पूर्ण
पूर्ण

व्योम qlcnic_sriov_cleanup_async_list(काष्ठा qlcnic_back_channel *bc)
अणु
	काष्ठा list_head *head = &bc->async_cmd_list;
	काष्ठा qlcnic_async_cmd *entry;

	flush_workqueue(bc->bc_async_wq);
	cancel_work_sync(&bc->vf_async_work);

	spin_lock(&bc->queue_lock);
	जबतक (!list_empty(head)) अणु
		entry = list_entry(head->next, काष्ठा qlcnic_async_cmd,
				   list);
		list_del(&entry->list);
		kमुक्त(entry->cmd);
		kमुक्त(entry);
	पूर्ण
	spin_unlock(&bc->queue_lock);
पूर्ण

व्योम qlcnic_sriov_vf_set_multi(काष्ठा net_device *netdev)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	अटल स्थिर u8 bcast_addr[ETH_ALEN] = अणु
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	पूर्ण;
	काष्ठा netdev_hw_addr *ha;
	u32 mode = VPORT_MISS_MODE_DROP;

	अगर (!test_bit(__QLCNIC_FW_ATTACHED, &adapter->state))
		वापस;

	अगर (netdev->flags & IFF_PROMISC) अणु
		अगर (!(adapter->flags & QLCNIC_PROMISC_DISABLED))
			mode = VPORT_MISS_MODE_ACCEPT_ALL;
	पूर्ण अन्यथा अगर ((netdev->flags & IFF_ALLMULTI) ||
		   (netdev_mc_count(netdev) > ahw->max_mc_count)) अणु
		mode = VPORT_MISS_MODE_ACCEPT_MULTI;
	पूर्ण अन्यथा अणु
		qlcnic_vf_add_mc_list(netdev, bcast_addr, QLCNIC_BROADCAST_MAC);
		अगर (!netdev_mc_empty(netdev)) अणु
			qlcnic_flush_mcast_mac(adapter);
			netdev_क्रम_each_mc_addr(ha, netdev)
				qlcnic_vf_add_mc_list(netdev, ha->addr,
						      QLCNIC_MULTICAST_MAC);
		पूर्ण
	पूर्ण

	/* configure unicast MAC address, अगर there is not sufficient space
	 * to store all the unicast addresses then enable promiscuous mode
	 */
	अगर (netdev_uc_count(netdev) > ahw->max_uc_count) अणु
		mode = VPORT_MISS_MODE_ACCEPT_ALL;
	पूर्ण अन्यथा अगर (!netdev_uc_empty(netdev)) अणु
		netdev_क्रम_each_uc_addr(ha, netdev)
			qlcnic_vf_add_mc_list(netdev, ha->addr,
					      QLCNIC_UNICAST_MAC);
	पूर्ण

	अगर (adapter->pdev->is_virtfn) अणु
		अगर (mode == VPORT_MISS_MODE_ACCEPT_ALL &&
		    !adapter->fdb_mac_learn) अणु
			qlcnic_alloc_lb_filters_mem(adapter);
			adapter->drv_mac_learn = true;
			adapter->rx_mac_learn = true;
		पूर्ण अन्यथा अणु
			adapter->drv_mac_learn = false;
			adapter->rx_mac_learn = false;
		पूर्ण
	पूर्ण

	qlcnic_nic_set_promisc(adapter, mode);
पूर्ण

अटल व्योम qlcnic_sriov_handle_async_issue_cmd(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlcnic_async_cmd *entry, *पंचांगp;
	काष्ठा qlcnic_back_channel *bc;
	काष्ठा qlcnic_cmd_args *cmd;
	काष्ठा list_head *head;
	LIST_HEAD(del_list);

	bc = container_of(work, काष्ठा qlcnic_back_channel, vf_async_work);
	head = &bc->async_cmd_list;

	spin_lock(&bc->queue_lock);
	list_splice_init(head, &del_list);
	spin_unlock(&bc->queue_lock);

	list_क्रम_each_entry_safe(entry, पंचांगp, &del_list, list) अणु
		list_del(&entry->list);
		cmd = entry->cmd;
		__qlcnic_sriov_issue_cmd(bc->adapter, cmd);
		kमुक्त(entry);
	पूर्ण

	अगर (!list_empty(head))
		queue_work(bc->bc_async_wq, &bc->vf_async_work);

	वापस;
पूर्ण

अटल काष्ठा qlcnic_async_cmd *
qlcnic_sriov_alloc_async_cmd(काष्ठा qlcnic_back_channel *bc,
			     काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_async_cmd *entry = शून्य;

	entry = kzalloc(माप(*entry), GFP_ATOMIC);
	अगर (!entry)
		वापस शून्य;

	entry->cmd = cmd;

	spin_lock(&bc->queue_lock);
	list_add_tail(&entry->list, &bc->async_cmd_list);
	spin_unlock(&bc->queue_lock);

	वापस entry;
पूर्ण

अटल व्योम qlcnic_sriov_schedule_async_cmd(काष्ठा qlcnic_back_channel *bc,
					    काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_async_cmd *entry = शून्य;

	entry = qlcnic_sriov_alloc_async_cmd(bc, cmd);
	अगर (!entry) अणु
		qlcnic_मुक्त_mbx_args(cmd);
		kमुक्त(cmd);
		वापस;
	पूर्ण

	queue_work(bc->bc_async_wq, &bc->vf_async_work);
पूर्ण

अटल पूर्णांक qlcnic_sriov_async_issue_cmd(काष्ठा qlcnic_adapter *adapter,
					काष्ठा qlcnic_cmd_args *cmd)
अणु

	काष्ठा qlcnic_back_channel *bc = &adapter->ahw->sriov->bc;

	अगर (adapter->need_fw_reset)
		वापस -EIO;

	qlcnic_sriov_schedule_async_cmd(bc, cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_vf_reinit_driver(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक err;

	adapter->need_fw_reset = 0;
	qlcnic_83xx_reinit_mbx_work(adapter->ahw->mailbox);
	qlcnic_83xx_enable_mbx_पूर्णांकerrupt(adapter);

	err = qlcnic_sriov_cfg_bc_पूर्णांकr(adapter, 1);
	अगर (err)
		वापस err;

	err = qlcnic_sriov_channel_cfg_cmd(adapter, QLCNIC_BC_CMD_CHANNEL_INIT);
	अगर (err)
		जाओ err_out_cleanup_bc_पूर्णांकr;

	err = qlcnic_sriov_vf_init_driver(adapter);
	अगर (err)
		जाओ err_out_term_channel;

	वापस 0;

err_out_term_channel:
	qlcnic_sriov_channel_cfg_cmd(adapter, QLCNIC_BC_CMD_CHANNEL_TERM);

err_out_cleanup_bc_पूर्णांकr:
	qlcnic_sriov_cfg_bc_पूर्णांकr(adapter, 0);
	वापस err;
पूर्ण

अटल व्योम qlcnic_sriov_vf_attach(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (netअगर_running(netdev)) अणु
		अगर (!qlcnic_up(adapter, netdev))
			qlcnic_restore_indev_addr(netdev, NETDEV_UP);
	पूर्ण

	netअगर_device_attach(netdev);
पूर्ण

अटल व्योम qlcnic_sriov_vf_detach(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_पूर्णांकrpt_config *पूर्णांकr_tbl = ahw->पूर्णांकr_tbl;
	काष्ठा net_device *netdev = adapter->netdev;
	u8 i, max_पूर्णांकs = ahw->num_msix - 1;

	netअगर_device_detach(netdev);
	qlcnic_83xx_detach_mailbox_work(adapter);
	qlcnic_83xx_disable_mbx_पूर्णांकr(adapter);

	अगर (netअगर_running(netdev))
		qlcnic_करोwn(adapter, netdev);

	क्रम (i = 0; i < max_पूर्णांकs; i++) अणु
		पूर्णांकr_tbl[i].id = i;
		पूर्णांकr_tbl[i].enabled = 0;
		पूर्णांकr_tbl[i].src = 0;
	पूर्ण
	ahw->reset_context = 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_vf_handle_dev_पढ़ोy(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा qlc_83xx_idc *idc = &ahw->idc;
	u8 func = ahw->pci_func;
	u32 state;

	अगर ((idc->prev_state == QLC_83XX_IDC_DEV_NEED_RESET) ||
	    (idc->prev_state == QLC_83XX_IDC_DEV_INIT)) अणु
		अगर (!qlcnic_sriov_vf_reinit_driver(adapter)) अणु
			qlcnic_sriov_vf_attach(adapter);
			adapter->fw_fail_cnt = 0;
			dev_info(dev,
				 "%s: Reinitialization of VF 0x%x done after FW reset\n",
				 __func__, func);
		पूर्ण अन्यथा अणु
			dev_err(dev,
				"%s: Reinitialization of VF 0x%x failed after FW reset\n",
				__func__, func);
			state = QLCRDX(ahw, QLC_83XX_IDC_DEV_STATE);
			dev_info(dev, "Current state 0x%x after FW reset\n",
				 state);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_vf_handle_context_reset(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_mailbox *mbx = ahw->mailbox;
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा qlc_83xx_idc *idc = &ahw->idc;
	u8 func = ahw->pci_func;
	u32 state;

	adapter->reset_ctx_cnt++;

	/* Skip the context reset and check अगर FW is hung */
	अगर (adapter->reset_ctx_cnt < 3) अणु
		adapter->need_fw_reset = 1;
		clear_bit(QLC_83XX_MBX_READY, &mbx->status);
		dev_info(dev,
			 "Resetting context, wait here to check if FW is in failed state\n");
		वापस 0;
	पूर्ण

	/* Check अगर number of resets exceed the threshold.
	 * If it exceeds the threshold just fail the VF.
	 */
	अगर (adapter->reset_ctx_cnt > QLC_83XX_VF_RESET_FAIL_THRESH) अणु
		clear_bit(QLC_83XX_MODULE_LOADED, &idc->status);
		adapter->tx_समयo_cnt = 0;
		adapter->fw_fail_cnt = 0;
		adapter->reset_ctx_cnt = 0;
		qlcnic_sriov_vf_detach(adapter);
		dev_err(dev,
			"Device context resets have exceeded the threshold, device interface will be shutdown\n");
		वापस -EIO;
	पूर्ण

	dev_info(dev, "Resetting context of VF 0x%x\n", func);
	dev_info(dev, "%s: Context reset count %d for VF 0x%x\n",
		 __func__, adapter->reset_ctx_cnt, func);
	set_bit(__QLCNIC_RESETTING, &adapter->state);
	adapter->need_fw_reset = 1;
	clear_bit(QLC_83XX_MBX_READY, &mbx->status);
	qlcnic_sriov_vf_detach(adapter);
	adapter->need_fw_reset = 0;

	अगर (!qlcnic_sriov_vf_reinit_driver(adapter)) अणु
		qlcnic_sriov_vf_attach(adapter);
		adapter->tx_समयo_cnt = 0;
		adapter->reset_ctx_cnt = 0;
		adapter->fw_fail_cnt = 0;
		dev_info(dev, "Done resetting context for VF 0x%x\n", func);
	पूर्ण अन्यथा अणु
		dev_err(dev, "%s: Reinitialization of VF 0x%x failed\n",
			__func__, func);
		state = QLCRDX(ahw, QLC_83XX_IDC_DEV_STATE);
		dev_info(dev, "%s: Current state 0x%x\n", __func__, state);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_vf_idc_पढ़ोy_state(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक ret = 0;

	अगर (ahw->idc.prev_state != QLC_83XX_IDC_DEV_READY)
		ret = qlcnic_sriov_vf_handle_dev_पढ़ोy(adapter);
	अन्यथा अगर (ahw->reset_context)
		ret = qlcnic_sriov_vf_handle_context_reset(adapter);

	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	वापस ret;
पूर्ण

अटल पूर्णांक qlcnic_sriov_vf_idc_failed_state(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlc_83xx_idc *idc = &adapter->ahw->idc;

	dev_err(&adapter->pdev->dev, "Device is in failed state\n");
	अगर (idc->prev_state == QLC_83XX_IDC_DEV_READY)
		qlcnic_sriov_vf_detach(adapter);

	clear_bit(QLC_83XX_MODULE_LOADED, &idc->status);
	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	वापस -EIO;
पूर्ण

अटल पूर्णांक
qlcnic_sriov_vf_idc_need_quiescent_state(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_mailbox *mbx = adapter->ahw->mailbox;
	काष्ठा qlc_83xx_idc *idc = &adapter->ahw->idc;

	dev_info(&adapter->pdev->dev, "Device is in quiescent state\n");
	अगर (idc->prev_state == QLC_83XX_IDC_DEV_READY) अणु
		set_bit(__QLCNIC_RESETTING, &adapter->state);
		adapter->tx_समयo_cnt = 0;
		adapter->reset_ctx_cnt = 0;
		clear_bit(QLC_83XX_MBX_READY, &mbx->status);
		qlcnic_sriov_vf_detach(adapter);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_vf_idc_init_reset_state(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_mailbox *mbx = adapter->ahw->mailbox;
	काष्ठा qlc_83xx_idc *idc = &adapter->ahw->idc;
	u8 func = adapter->ahw->pci_func;

	अगर (idc->prev_state == QLC_83XX_IDC_DEV_READY) अणु
		dev_err(&adapter->pdev->dev,
			"Firmware hang detected by VF 0x%x\n", func);
		set_bit(__QLCNIC_RESETTING, &adapter->state);
		adapter->tx_समयo_cnt = 0;
		adapter->reset_ctx_cnt = 0;
		clear_bit(QLC_83XX_MBX_READY, &mbx->status);
		qlcnic_sriov_vf_detach(adapter);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_sriov_vf_idc_unknown_state(काष्ठा qlcnic_adapter *adapter)
अणु
	dev_err(&adapter->pdev->dev, "%s: Device in unknown state\n", __func__);
	वापस 0;
पूर्ण

अटल व्योम qlcnic_sriov_vf_periodic_tasks(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (adapter->fhash.fnum)
		qlcnic_prune_lb_filters(adapter);
पूर्ण

अटल व्योम qlcnic_sriov_vf_poll_dev_state(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlcnic_adapter *adapter;
	काष्ठा qlc_83xx_idc *idc;
	पूर्णांक ret = 0;

	adapter = container_of(work, काष्ठा qlcnic_adapter, fw_work.work);
	idc = &adapter->ahw->idc;
	idc->curr_state = QLCRDX(adapter->ahw, QLC_83XX_IDC_DEV_STATE);

	चयन (idc->curr_state) अणु
	हाल QLC_83XX_IDC_DEV_READY:
		ret = qlcnic_sriov_vf_idc_पढ़ोy_state(adapter);
		अवरोध;
	हाल QLC_83XX_IDC_DEV_NEED_RESET:
	हाल QLC_83XX_IDC_DEV_INIT:
		ret = qlcnic_sriov_vf_idc_init_reset_state(adapter);
		अवरोध;
	हाल QLC_83XX_IDC_DEV_NEED_QUISCENT:
		ret = qlcnic_sriov_vf_idc_need_quiescent_state(adapter);
		अवरोध;
	हाल QLC_83XX_IDC_DEV_FAILED:
		ret = qlcnic_sriov_vf_idc_failed_state(adapter);
		अवरोध;
	हाल QLC_83XX_IDC_DEV_QUISCENT:
		अवरोध;
	शेष:
		ret = qlcnic_sriov_vf_idc_unknown_state(adapter);
	पूर्ण

	idc->prev_state = idc->curr_state;
	qlcnic_sriov_vf_periodic_tasks(adapter);

	अगर (!ret && test_bit(QLC_83XX_MODULE_LOADED, &idc->status))
		qlcnic_schedule_work(adapter, qlcnic_sriov_vf_poll_dev_state,
				     idc->delay);
पूर्ण

अटल व्योम qlcnic_sriov_vf_cancel_fw_work(काष्ठा qlcnic_adapter *adapter)
अणु
	जबतक (test_and_set_bit(__QLCNIC_RESETTING, &adapter->state))
		msleep(20);

	clear_bit(QLC_83XX_MODULE_LOADED, &adapter->ahw->idc.status);
	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	cancel_delayed_work_sync(&adapter->fw_work);
पूर्ण

अटल पूर्णांक qlcnic_sriov_check_vlan_id(काष्ठा qlcnic_sriov *sriov,
				      काष्ठा qlcnic_vf_info *vf, u16 vlan_id)
अणु
	पूर्णांक i, err = -EINVAL;

	अगर (!vf->sriov_vlans)
		वापस err;

	spin_lock_bh(&vf->vlan_list_lock);

	क्रम (i = 0; i < sriov->num_allowed_vlans; i++) अणु
		अगर (vf->sriov_vlans[i] == vlan_id) अणु
			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&vf->vlan_list_lock);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_validate_num_vlans(काष्ठा qlcnic_sriov *sriov,
					   काष्ठा qlcnic_vf_info *vf)
अणु
	पूर्णांक err = 0;

	spin_lock_bh(&vf->vlan_list_lock);

	अगर (vf->num_vlan >= sriov->num_allowed_vlans)
		err = -EINVAL;

	spin_unlock_bh(&vf->vlan_list_lock);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_sriov_validate_vlan_cfg(काष्ठा qlcnic_adapter *adapter,
					  u16 vid, u8 enable)
अणु
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	काष्ठा qlcnic_vf_info *vf;
	bool vlan_exist;
	u8 allowed = 0;
	पूर्णांक i;

	vf = &adapter->ahw->sriov->vf_info[0];
	vlan_exist = qlcnic_sriov_check_any_vlan(vf);
	अगर (sriov->vlan_mode != QLC_GUEST_VLAN_MODE)
		वापस -EINVAL;

	अगर (enable) अणु
		अगर (qlcnic_83xx_vf_check(adapter) && vlan_exist)
			वापस -EINVAL;

		अगर (qlcnic_sriov_validate_num_vlans(sriov, vf))
			वापस -EINVAL;

		अगर (sriov->any_vlan) अणु
			क्रम (i = 0; i < sriov->num_allowed_vlans; i++) अणु
				अगर (sriov->allowed_vlans[i] == vid)
					allowed = 1;
			पूर्ण

			अगर (!allowed)
				वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!vlan_exist || qlcnic_sriov_check_vlan_id(sriov, vf, vid))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qlcnic_sriov_vlan_operation(काष्ठा qlcnic_vf_info *vf, u16 vlan_id,
					क्रमागत qlcnic_vlan_operations opcode)
अणु
	काष्ठा qlcnic_adapter *adapter = vf->adapter;
	काष्ठा qlcnic_sriov *sriov;

	sriov = adapter->ahw->sriov;

	अगर (!vf->sriov_vlans)
		वापस;

	spin_lock_bh(&vf->vlan_list_lock);

	चयन (opcode) अणु
	हाल QLC_VLAN_ADD:
		qlcnic_sriov_add_vlan_id(sriov, vf, vlan_id);
		अवरोध;
	हाल QLC_VLAN_DELETE:
		qlcnic_sriov_del_vlan_id(sriov, vf, vlan_id);
		अवरोध;
	शेष:
		netdev_err(adapter->netdev, "Invalid VLAN operation\n");
	पूर्ण

	spin_unlock_bh(&vf->vlan_list_lock);
	वापस;
पूर्ण

पूर्णांक qlcnic_sriov_cfg_vf_guest_vlan(काष्ठा qlcnic_adapter *adapter,
				   u16 vid, u8 enable)
अणु
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा qlcnic_vf_info *vf;
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	अगर (vid == 0)
		वापस 0;

	vf = &adapter->ahw->sriov->vf_info[0];
	ret = qlcnic_sriov_validate_vlan_cfg(adapter, vid, enable);
	अगर (ret)
		वापस ret;

	ret = qlcnic_sriov_alloc_bc_mbx_args(&cmd,
					     QLCNIC_BC_CMD_CFG_GUEST_VLAN);
	अगर (ret)
		वापस ret;

	cmd.req.arg[1] = (enable & 1) | vid << 16;

	qlcnic_sriov_cleanup_async_list(&sriov->bc);
	ret = qlcnic_issue_cmd(adapter, &cmd);
	अगर (ret) अणु
		dev_err(&adapter->pdev->dev,
			"Failed to configure guest VLAN, err=%d\n", ret);
	पूर्ण अन्यथा अणु
		netअगर_addr_lock_bh(netdev);
		qlcnic_मुक्त_mac_list(adapter);
		netअगर_addr_unlock_bh(netdev);

		अगर (enable)
			qlcnic_sriov_vlan_operation(vf, vid, QLC_VLAN_ADD);
		अन्यथा
			qlcnic_sriov_vlan_operation(vf, vid, QLC_VLAN_DELETE);

		netअगर_addr_lock_bh(netdev);
		qlcnic_set_multi(netdev);
		netअगर_addr_unlock_bh(netdev);
	पूर्ण

	qlcnic_मुक्त_mbx_args(&cmd);
	वापस ret;
पूर्ण

अटल व्योम qlcnic_sriov_vf_मुक्त_mac_list(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा list_head *head = &adapter->mac_list;
	काष्ठा qlcnic_mac_vlan_list *cur;

	जबतक (!list_empty(head)) अणु
		cur = list_entry(head->next, काष्ठा qlcnic_mac_vlan_list, list);
		qlcnic_sre_macaddr_change(adapter, cur->mac_addr, cur->vlan_id,
					  QLCNIC_MAC_DEL);
		list_del(&cur->list);
		kमुक्त(cur);
	पूर्ण
पूर्ण


अटल पूर्णांक qlcnic_sriov_vf_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qlcnic_adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = adapter->netdev;

	netअगर_device_detach(netdev);
	qlcnic_cancel_idc_work(adapter);

	अगर (netअगर_running(netdev))
		qlcnic_करोwn(adapter, netdev);

	qlcnic_sriov_channel_cfg_cmd(adapter, QLCNIC_BC_CMD_CHANNEL_TERM);
	qlcnic_sriov_cfg_bc_पूर्णांकr(adapter, 0);
	qlcnic_83xx_disable_mbx_पूर्णांकr(adapter);
	cancel_delayed_work_sync(&adapter->idc_aen_work);

	वापस pci_save_state(pdev);
पूर्ण

अटल पूर्णांक qlcnic_sriov_vf_resume(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlc_83xx_idc *idc = &adapter->ahw->idc;
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err;

	set_bit(QLC_83XX_MODULE_LOADED, &idc->status);
	qlcnic_83xx_enable_mbx_पूर्णांकerrupt(adapter);
	err = qlcnic_sriov_cfg_bc_पूर्णांकr(adapter, 1);
	अगर (err)
		वापस err;

	err = qlcnic_sriov_channel_cfg_cmd(adapter, QLCNIC_BC_CMD_CHANNEL_INIT);
	अगर (!err) अणु
		अगर (netअगर_running(netdev)) अणु
			err = qlcnic_up(adapter, netdev);
			अगर (!err)
				qlcnic_restore_indev_addr(netdev, NETDEV_UP);
		पूर्ण
	पूर्ण

	netअगर_device_attach(netdev);
	qlcnic_schedule_work(adapter, qlcnic_sriov_vf_poll_dev_state,
			     idc->delay);
	वापस err;
पूर्ण

व्योम qlcnic_sriov_alloc_vlans(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	काष्ठा qlcnic_vf_info *vf;
	पूर्णांक i;

	क्रम (i = 0; i < sriov->num_vfs; i++) अणु
		vf = &sriov->vf_info[i];
		vf->sriov_vlans = kसुस्मृति(sriov->num_allowed_vlans,
					  माप(*vf->sriov_vlans), GFP_KERNEL);
	पूर्ण
पूर्ण

व्योम qlcnic_sriov_मुक्त_vlans(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_sriov *sriov = adapter->ahw->sriov;
	काष्ठा qlcnic_vf_info *vf;
	पूर्णांक i;

	क्रम (i = 0; i < sriov->num_vfs; i++) अणु
		vf = &sriov->vf_info[i];
		kमुक्त(vf->sriov_vlans);
		vf->sriov_vlans = शून्य;
	पूर्ण
पूर्ण

व्योम qlcnic_sriov_add_vlan_id(काष्ठा qlcnic_sriov *sriov,
			      काष्ठा qlcnic_vf_info *vf, u16 vlan_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sriov->num_allowed_vlans; i++) अणु
		अगर (!vf->sriov_vlans[i]) अणु
			vf->sriov_vlans[i] = vlan_id;
			vf->num_vlan++;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

व्योम qlcnic_sriov_del_vlan_id(काष्ठा qlcnic_sriov *sriov,
			      काष्ठा qlcnic_vf_info *vf, u16 vlan_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sriov->num_allowed_vlans; i++) अणु
		अगर (vf->sriov_vlans[i] == vlan_id) अणु
			vf->sriov_vlans[i] = 0;
			vf->num_vlan--;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

bool qlcnic_sriov_check_any_vlan(काष्ठा qlcnic_vf_info *vf)
अणु
	bool err = false;

	spin_lock_bh(&vf->vlan_list_lock);

	अगर (vf->num_vlan)
		err = true;

	spin_unlock_bh(&vf->vlan_list_lock);
	वापस err;
पूर्ण
