<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
#समावेश <linux/pci.h>
#समावेश <linux/अगर_vlan.h>
#समावेश "liquidio_common.h"
#समावेश "octeon_droq.h"
#समावेश "octeon_iq.h"
#समावेश "response_manager.h"
#समावेश "octeon_device.h"
#समावेश "octeon_nic.h"
#समावेश "octeon_main.h"
#समावेश "octeon_network.h"

/* OOM task polling पूर्णांकerval */
#घोषणा LIO_OOM_POLL_INTERVAL_MS 250

#घोषणा OCTNIC_MAX_SG  MAX_SKB_FRAGS

/**
 * lio_delete_glists - Delete gather lists
 * @lio: per-network निजी data
 */
व्योम lio_delete_glists(काष्ठा lio *lio)
अणु
	काष्ठा octnic_gather *g;
	पूर्णांक i;

	kमुक्त(lio->glist_lock);
	lio->glist_lock = शून्य;

	अगर (!lio->glist)
		वापस;

	क्रम (i = 0; i < lio->oct_dev->num_iqs; i++) अणु
		करो अणु
			g = (काष्ठा octnic_gather *)
			    lio_list_delete_head(&lio->glist[i]);
			kमुक्त(g);
		पूर्ण जबतक (g);

		अगर (lio->glists_virt_base && lio->glists_virt_base[i] &&
		    lio->glists_dma_base && lio->glists_dma_base[i]) अणु
			lio_dma_मुक्त(lio->oct_dev,
				     lio->glist_entry_size * lio->tx_qsize,
				     lio->glists_virt_base[i],
				     lio->glists_dma_base[i]);
		पूर्ण
	पूर्ण

	kमुक्त(lio->glists_virt_base);
	lio->glists_virt_base = शून्य;

	kमुक्त(lio->glists_dma_base);
	lio->glists_dma_base = शून्य;

	kमुक्त(lio->glist);
	lio->glist = शून्य;
पूर्ण

/**
 * lio_setup_glists - Setup gather lists
 * @oct: octeon_device
 * @lio: per-network निजी data
 * @num_iqs: count of iqs to allocate
 */
पूर्णांक lio_setup_glists(काष्ठा octeon_device *oct, काष्ठा lio *lio, पूर्णांक num_iqs)
अणु
	काष्ठा octnic_gather *g;
	पूर्णांक i, j;

	lio->glist_lock =
	    kसुस्मृति(num_iqs, माप(*lio->glist_lock), GFP_KERNEL);
	अगर (!lio->glist_lock)
		वापस -ENOMEM;

	lio->glist =
	    kसुस्मृति(num_iqs, माप(*lio->glist), GFP_KERNEL);
	अगर (!lio->glist) अणु
		kमुक्त(lio->glist_lock);
		lio->glist_lock = शून्य;
		वापस -ENOMEM;
	पूर्ण

	lio->glist_entry_size =
		ROUNDUP8((ROUNDUP4(OCTNIC_MAX_SG) >> 2) * OCT_SG_ENTRY_SIZE);

	/* allocate memory to store भव and dma base address of
	 * per glist consistent memory
	 */
	lio->glists_virt_base = kसुस्मृति(num_iqs, माप(*lio->glists_virt_base),
					GFP_KERNEL);
	lio->glists_dma_base = kसुस्मृति(num_iqs, माप(*lio->glists_dma_base),
				       GFP_KERNEL);

	अगर (!lio->glists_virt_base || !lio->glists_dma_base) अणु
		lio_delete_glists(lio);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < num_iqs; i++) अणु
		पूर्णांक numa_node = dev_to_node(&oct->pci_dev->dev);

		spin_lock_init(&lio->glist_lock[i]);

		INIT_LIST_HEAD(&lio->glist[i]);

		lio->glists_virt_base[i] =
			lio_dma_alloc(oct,
				      lio->glist_entry_size * lio->tx_qsize,
				      &lio->glists_dma_base[i]);

		अगर (!lio->glists_virt_base[i]) अणु
			lio_delete_glists(lio);
			वापस -ENOMEM;
		पूर्ण

		क्रम (j = 0; j < lio->tx_qsize; j++) अणु
			g = kzalloc_node(माप(*g), GFP_KERNEL,
					 numa_node);
			अगर (!g)
				g = kzalloc(माप(*g), GFP_KERNEL);
			अगर (!g)
				अवरोध;

			g->sg = lio->glists_virt_base[i] +
				(j * lio->glist_entry_size);

			g->sg_dma_ptr = lio->glists_dma_base[i] +
					(j * lio->glist_entry_size);

			list_add_tail(&g->list, &lio->glist[i]);
		पूर्ण

		अगर (j != lio->tx_qsize) अणु
			lio_delete_glists(lio);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक liquidio_set_feature(काष्ठा net_device *netdev, पूर्णांक cmd, u16 param1)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octnic_ctrl_pkt nctrl;
	पूर्णांक ret = 0;

	स_रखो(&nctrl, 0, माप(काष्ठा octnic_ctrl_pkt));

	nctrl.ncmd.u64 = 0;
	nctrl.ncmd.s.cmd = cmd;
	nctrl.ncmd.s.param1 = param1;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.netpndev = (u64)netdev;
	nctrl.cb_fn = liquidio_link_ctrl_cmd_completion;

	ret = octnet_send_nic_ctrl_pkt(lio->oct_dev, &nctrl);
	अगर (ret) अणु
		dev_err(&oct->pci_dev->dev, "Feature change failed in core (ret: 0x%x)\n",
			ret);
		अगर (ret > 0)
			ret = -EIO;
	पूर्ण
	वापस ret;
पूर्ण

व्योम octeon_report_tx_completion_to_bql(व्योम *txq, अचिन्हित पूर्णांक pkts_compl,
					अचिन्हित पूर्णांक bytes_compl)
अणु
	काष्ठा netdev_queue *netdev_queue = txq;

	netdev_tx_completed_queue(netdev_queue, pkts_compl, bytes_compl);
पूर्ण

व्योम octeon_update_tx_completion_counters(व्योम *buf, पूर्णांक reqtype,
					  अचिन्हित पूर्णांक *pkts_compl,
					  अचिन्हित पूर्णांक *bytes_compl)
अणु
	काष्ठा octnet_buf_मुक्त_info *finfo;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा octeon_soft_command *sc;

	चयन (reqtype) अणु
	हाल REQTYPE_NORESP_NET:
	हाल REQTYPE_NORESP_NET_SG:
		finfo = buf;
		skb = finfo->skb;
		अवरोध;

	हाल REQTYPE_RESP_NET_SG:
	हाल REQTYPE_RESP_NET:
		sc = buf;
		skb = sc->callback_arg;
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	(*pkts_compl)++;
	*bytes_compl += skb->len;
पूर्ण

पूर्णांक octeon_report_sent_bytes_to_bql(व्योम *buf, पूर्णांक reqtype)
अणु
	काष्ठा octnet_buf_मुक्त_info *finfo;
	काष्ठा sk_buff *skb;
	काष्ठा octeon_soft_command *sc;
	काष्ठा netdev_queue *txq;

	चयन (reqtype) अणु
	हाल REQTYPE_NORESP_NET:
	हाल REQTYPE_NORESP_NET_SG:
		finfo = buf;
		skb = finfo->skb;
		अवरोध;

	हाल REQTYPE_RESP_NET_SG:
	हाल REQTYPE_RESP_NET:
		sc = buf;
		skb = sc->callback_arg;
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	txq = netdev_get_tx_queue(skb->dev, skb_get_queue_mapping(skb));
	netdev_tx_sent_queue(txq, skb->len);

	वापस netअगर_xmit_stopped(txq);
पूर्ण

व्योम liquidio_link_ctrl_cmd_completion(व्योम *nctrl_ptr)
अणु
	काष्ठा octnic_ctrl_pkt *nctrl = (काष्ठा octnic_ctrl_pkt *)nctrl_ptr;
	काष्ठा net_device *netdev = (काष्ठा net_device *)nctrl->netpndev;
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	u8 *mac;

	अगर (nctrl->sc_status)
		वापस;

	चयन (nctrl->ncmd.s.cmd) अणु
	हाल OCTNET_CMD_CHANGE_DEVFLAGS:
	हाल OCTNET_CMD_SET_MULTI_LIST:
	हाल OCTNET_CMD_SET_UC_LIST:
		अवरोध;

	हाल OCTNET_CMD_CHANGE_MACADDR:
		mac = ((u8 *)&nctrl->udd[0]) + 2;
		अगर (nctrl->ncmd.s.param1) अणु
			/* vfidx is 0 based, but vf_num (param1) is 1 based */
			पूर्णांक vfidx = nctrl->ncmd.s.param1 - 1;
			bool mac_is_admin_asचिन्हित = nctrl->ncmd.s.param2;

			अगर (mac_is_admin_asचिन्हित)
				netअगर_info(lio, probe, lio->netdev,
					   "MAC Address %pM is configured for VF %d\n",
					   mac, vfidx);
		पूर्ण अन्यथा अणु
			netअगर_info(lio, probe, lio->netdev,
				   " MACAddr changed to %pM\n",
				   mac);
		पूर्ण
		अवरोध;

	हाल OCTNET_CMD_GPIO_ACCESS:
		netअगर_info(lio, probe, lio->netdev, "LED Flashing visual identification\n");

		अवरोध;

	हाल OCTNET_CMD_ID_ACTIVE:
		netअगर_info(lio, probe, lio->netdev, "LED Flashing visual identification\n");

		अवरोध;

	हाल OCTNET_CMD_LRO_ENABLE:
		dev_info(&oct->pci_dev->dev, "%s LRO Enabled\n", netdev->name);
		अवरोध;

	हाल OCTNET_CMD_LRO_DISABLE:
		dev_info(&oct->pci_dev->dev, "%s LRO Disabled\n",
			 netdev->name);
		अवरोध;

	हाल OCTNET_CMD_VERBOSE_ENABLE:
		dev_info(&oct->pci_dev->dev, "%s Firmware debug enabled\n",
			 netdev->name);
		अवरोध;

	हाल OCTNET_CMD_VERBOSE_DISABLE:
		dev_info(&oct->pci_dev->dev, "%s Firmware debug disabled\n",
			 netdev->name);
		अवरोध;

	हाल OCTNET_CMD_VLAN_FILTER_CTL:
		अगर (nctrl->ncmd.s.param1)
			dev_info(&oct->pci_dev->dev,
				 "%s VLAN filter enabled\n", netdev->name);
		अन्यथा
			dev_info(&oct->pci_dev->dev,
				 "%s VLAN filter disabled\n", netdev->name);
		अवरोध;

	हाल OCTNET_CMD_ADD_VLAN_FILTER:
		dev_info(&oct->pci_dev->dev, "%s VLAN filter %d added\n",
			 netdev->name, nctrl->ncmd.s.param1);
		अवरोध;

	हाल OCTNET_CMD_DEL_VLAN_FILTER:
		dev_info(&oct->pci_dev->dev, "%s VLAN filter %d removed\n",
			 netdev->name, nctrl->ncmd.s.param1);
		अवरोध;

	हाल OCTNET_CMD_SET_SETTINGS:
		dev_info(&oct->pci_dev->dev, "%s settings changed\n",
			 netdev->name);

		अवरोध;

	/* Case to handle "OCTNET_CMD_TNL_RX_CSUM_CTL"
	 * Command passed by NIC driver
	 */
	हाल OCTNET_CMD_TNL_RX_CSUM_CTL:
		अगर (nctrl->ncmd.s.param1 == OCTNET_CMD_RXCSUM_ENABLE) अणु
			netअगर_info(lio, probe, lio->netdev,
				   "RX Checksum Offload Enabled\n");
		पूर्ण अन्यथा अगर (nctrl->ncmd.s.param1 ==
			   OCTNET_CMD_RXCSUM_DISABLE) अणु
			netअगर_info(lio, probe, lio->netdev,
				   "RX Checksum Offload Disabled\n");
		पूर्ण
		अवरोध;

		/* Case to handle "OCTNET_CMD_TNL_TX_CSUM_CTL"
		 * Command passed by NIC driver
		 */
	हाल OCTNET_CMD_TNL_TX_CSUM_CTL:
		अगर (nctrl->ncmd.s.param1 == OCTNET_CMD_TXCSUM_ENABLE) अणु
			netअगर_info(lio, probe, lio->netdev,
				   "TX Checksum Offload Enabled\n");
		पूर्ण अन्यथा अगर (nctrl->ncmd.s.param1 ==
			   OCTNET_CMD_TXCSUM_DISABLE) अणु
			netअगर_info(lio, probe, lio->netdev,
				   "TX Checksum Offload Disabled\n");
		पूर्ण
		अवरोध;

		/* Case to handle "OCTNET_CMD_VXLAN_PORT_CONFIG"
		 * Command passed by NIC driver
		 */
	हाल OCTNET_CMD_VXLAN_PORT_CONFIG:
		अगर (nctrl->ncmd.s.more == OCTNET_CMD_VXLAN_PORT_ADD) अणु
			netअगर_info(lio, probe, lio->netdev,
				   "VxLAN Destination UDP PORT:%d ADDED\n",
				   nctrl->ncmd.s.param1);
		पूर्ण अन्यथा अगर (nctrl->ncmd.s.more ==
			   OCTNET_CMD_VXLAN_PORT_DEL) अणु
			netअगर_info(lio, probe, lio->netdev,
				   "VxLAN Destination UDP PORT:%d DELETED\n",
				   nctrl->ncmd.s.param1);
		पूर्ण
		अवरोध;

	हाल OCTNET_CMD_SET_FLOW_CTL:
		netअगर_info(lio, probe, lio->netdev, "Set RX/TX flow control parameters\n");
		अवरोध;

	हाल OCTNET_CMD_QUEUE_COUNT_CTL:
		netअगर_info(lio, probe, lio->netdev, "Queue count updated to %d\n",
			   nctrl->ncmd.s.param1);
		अवरोध;

	शेष:
		dev_err(&oct->pci_dev->dev, "%s Unknown cmd %d\n", __func__,
			nctrl->ncmd.s.cmd);
	पूर्ण
पूर्ण

व्योम octeon_pf_changed_vf_macaddr(काष्ठा octeon_device *oct, u8 *mac)
अणु
	bool macaddr_changed = false;
	काष्ठा net_device *netdev;
	काष्ठा lio *lio;

	rtnl_lock();

	netdev = oct->props[0].netdev;
	lio = GET_LIO(netdev);

	lio->linfo.macaddr_is_admin_asgnd = true;

	अगर (!ether_addr_equal(netdev->dev_addr, mac)) अणु
		macaddr_changed = true;
		ether_addr_copy(netdev->dev_addr, mac);
		ether_addr_copy(((u8 *)&lio->linfo.hw_addr) + 2, mac);
		call_netdevice_notअगरiers(NETDEV_CHANGEADDR, netdev);
	पूर्ण

	rtnl_unlock();

	अगर (macaddr_changed)
		dev_info(&oct->pci_dev->dev,
			 "PF changed VF's MAC address to %pM\n", mac);

	/* no need to notअगरy the firmware of the macaddr change because
	 * the PF did that alपढ़ोy
	 */
पूर्ण

व्योम octeon_schedule_rxq_oom_work(काष्ठा octeon_device *oct,
				  काष्ठा octeon_droq *droq)
अणु
	काष्ठा net_device *netdev = oct->props[0].netdev;
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा cavium_wq *wq = &lio->rxq_status_wq[droq->q_no];

	queue_delayed_work(wq->wq, &wq->wk.work,
			   msecs_to_jअगरfies(LIO_OOM_POLL_INTERVAL_MS));
पूर्ण

अटल व्योम octnet_poll_check_rxq_oom_status(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cavium_wk *wk = (काष्ठा cavium_wk *)work;
	काष्ठा lio *lio = (काष्ठा lio *)wk->ctxptr;
	काष्ठा octeon_device *oct = lio->oct_dev;
	पूर्णांक q_no = wk->ctxul;
	काष्ठा octeon_droq *droq = oct->droq[q_no];

	अगर (!अगरstate_check(lio, LIO_IFSTATE_RUNNING) || !droq)
		वापस;

	अगर (octeon_retry_droq_refill(droq))
		octeon_schedule_rxq_oom_work(oct, droq);
पूर्ण

पूर्णांक setup_rx_oom_poll_fn(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा cavium_wq *wq;
	पूर्णांक q, q_no;

	क्रम (q = 0; q < oct->num_oqs; q++) अणु
		q_no = lio->linfo.rxpciq[q].s.q_no;
		wq = &lio->rxq_status_wq[q_no];
		wq->wq = alloc_workqueue("rxq-oom-status",
					 WQ_MEM_RECLAIM, 0);
		अगर (!wq->wq) अणु
			dev_err(&oct->pci_dev->dev, "unable to create cavium rxq oom status wq\n");
			वापस -ENOMEM;
		पूर्ण

		INIT_DELAYED_WORK(&wq->wk.work,
				  octnet_poll_check_rxq_oom_status);
		wq->wk.ctxptr = lio;
		wq->wk.ctxul = q_no;
	पूर्ण

	वापस 0;
पूर्ण

व्योम cleanup_rx_oom_poll_fn(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा cavium_wq *wq;
	पूर्णांक q_no;

	क्रम (q_no = 0; q_no < oct->num_oqs; q_no++) अणु
		wq = &lio->rxq_status_wq[q_no];
		अगर (wq->wq) अणु
			cancel_delayed_work_sync(&wq->wk.work);
			flush_workqueue(wq->wq);
			destroy_workqueue(wq->wq);
			wq->wq = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/* Runs in पूर्णांकerrupt context. */
अटल व्योम lio_update_txq_status(काष्ठा octeon_device *oct, पूर्णांक iq_num)
अणु
	काष्ठा octeon_instr_queue *iq = oct->instr_queue[iq_num];
	काष्ठा net_device *netdev;
	काष्ठा lio *lio;

	netdev = oct->props[iq->अगरidx].netdev;

	/* This is needed because the first IQ करोes not have
	 * a netdev associated with it.
	 */
	अगर (!netdev)
		वापस;

	lio = GET_LIO(netdev);
	अगर (__netअगर_subqueue_stopped(netdev, iq->q_index) &&
	    lio->linfo.link.s.link_up &&
	    (!octnet_iq_is_full(oct, iq_num))) अणु
		netअगर_wake_subqueue(netdev, iq->q_index);
		INCR_INSTRQUEUE_PKT_COUNT(lio->oct_dev, iq_num,
					  tx_restart, 1);
	पूर्ण
पूर्ण

/**
 * octeon_setup_droq - Setup output queue
 * @oct: octeon device
 * @q_no: which queue
 * @num_descs: how many descriptors
 * @desc_size: size of each descriptor
 * @app_ctx: application context
 */
अटल पूर्णांक octeon_setup_droq(काष्ठा octeon_device *oct, पूर्णांक q_no, पूर्णांक num_descs,
			     पूर्णांक desc_size, व्योम *app_ctx)
अणु
	पूर्णांक ret_val;

	dev_dbg(&oct->pci_dev->dev, "Creating Droq: %d\n", q_no);
	/* droq creation and local रेजिस्टर settings. */
	ret_val = octeon_create_droq(oct, q_no, num_descs, desc_size, app_ctx);
	अगर (ret_val < 0)
		वापस ret_val;

	अगर (ret_val == 1) अणु
		dev_dbg(&oct->pci_dev->dev, "Using default droq %d\n", q_no);
		वापस 0;
	पूर्ण

	/* Enable the droq queues */
	octeon_set_droq_pkt_op(oct, q_no, 1);

	/* Send Credit क्रम Octeon Output queues. Credits are always
	 * sent after the output queue is enabled.
	 */
	ग_लिखोl(oct->droq[q_no]->max_count, oct->droq[q_no]->pkts_credit_reg);

	वापस ret_val;
पूर्ण

/**
 * liquidio_push_packet - Routine to push packets arriving on Octeon पूर्णांकerface upto network layer.
 * @octeon_id:octeon device id.
 * @skbuff:   skbuff काष्ठा to be passed to network layer.
 * @len:      size of total data received.
 * @rh:       Control header associated with the packet
 * @param:    additional control data with the packet
 * @arg:      farg रेजिस्टरed in droq_ops
 */
अटल व्योम
liquidio_push_packet(u32 __maybe_unused octeon_id,
		     व्योम *skbuff,
		     u32 len,
		     जोड़ octeon_rh *rh,
		     व्योम *param,
		     व्योम *arg)
अणु
	काष्ठा net_device *netdev = (काष्ठा net_device *)arg;
	काष्ठा octeon_droq *droq =
	    container_of(param, काष्ठा octeon_droq, napi);
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *)skbuff;
	काष्ठा skb_shared_hwtstamps *shhwtstamps;
	काष्ठा napi_काष्ठा *napi = param;
	u16 vtag = 0;
	u32 r_dh_off;
	u64 ns;

	अगर (netdev) अणु
		काष्ठा lio *lio = GET_LIO(netdev);
		काष्ठा octeon_device *oct = lio->oct_dev;

		/* Do not proceed अगर the पूर्णांकerface is not in RUNNING state. */
		अगर (!अगरstate_check(lio, LIO_IFSTATE_RUNNING)) अणु
			recv_buffer_मुक्त(skb);
			droq->stats.rx_dropped++;
			वापस;
		पूर्ण

		skb->dev = netdev;

		skb_record_rx_queue(skb, droq->q_no);
		अगर (likely(len > MIN_SKB_SIZE)) अणु
			काष्ठा octeon_skb_page_info *pg_info;
			अचिन्हित अक्षर *va;

			pg_info = ((काष्ठा octeon_skb_page_info *)(skb->cb));
			अगर (pg_info->page) अणु
				/* For Paged allocation use the frags */
				va = page_address(pg_info->page) +
					pg_info->page_offset;
				स_नकल(skb->data, va, MIN_SKB_SIZE);
				skb_put(skb, MIN_SKB_SIZE);
				skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
						pg_info->page,
						pg_info->page_offset +
						MIN_SKB_SIZE,
						len - MIN_SKB_SIZE,
						LIO_RXBUFFER_SZ);
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा octeon_skb_page_info *pg_info =
				((काष्ठा octeon_skb_page_info *)(skb->cb));
			skb_copy_to_linear_data(skb, page_address(pg_info->page)
						+ pg_info->page_offset, len);
			skb_put(skb, len);
			put_page(pg_info->page);
		पूर्ण

		r_dh_off = (rh->r_dh.len - 1) * BYTES_PER_DHLEN_UNIT;

		अगर (oct->ptp_enable) अणु
			अगर (rh->r_dh.has_hwtstamp) अणु
				/* बारtamp is included from the hardware at
				 * the beginning of the packet.
				 */
				अगर (अगरstate_check
					(lio,
					 LIO_IFSTATE_RX_TIMESTAMP_ENABLED)) अणु
					/* Nanoseconds are in the first 64-bits
					 * of the packet.
					 */
					स_नकल(&ns, (skb->data + r_dh_off),
					       माप(ns));
					r_dh_off -= BYTES_PER_DHLEN_UNIT;
					shhwtstamps = skb_hwtstamps(skb);
					shhwtstamps->hwtstamp =
						ns_to_kसमय(ns +
							    lio->ptp_adjust);
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (rh->r_dh.has_hash) अणु
			__be32 *hash_be = (__be32 *)(skb->data + r_dh_off);
			u32 hash = be32_to_cpu(*hash_be);

			skb_set_hash(skb, hash, PKT_HASH_TYPE_L4);
			r_dh_off -= BYTES_PER_DHLEN_UNIT;
		पूर्ण

		skb_pull(skb, rh->r_dh.len * BYTES_PER_DHLEN_UNIT);
		skb->protocol = eth_type_trans(skb, skb->dev);

		अगर ((netdev->features & NETIF_F_RXCSUM) &&
		    (((rh->r_dh.encap_on) &&
		      (rh->r_dh.csum_verअगरied & CNNIC_TUN_CSUM_VERIFIED)) ||
		     (!(rh->r_dh.encap_on) &&
		      ((rh->r_dh.csum_verअगरied & CNNIC_CSUM_VERIFIED) ==
			CNNIC_CSUM_VERIFIED))))
			/* checksum has alपढ़ोy been verअगरied */
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		अन्यथा
			skb->ip_summed = CHECKSUM_NONE;

		/* Setting Encapsulation field on basis of status received
		 * from the firmware
		 */
		अगर (rh->r_dh.encap_on) अणु
			skb->encapsulation = 1;
			skb->csum_level = 1;
			droq->stats.rx_vxlan++;
		पूर्ण

		/* inbound VLAN tag */
		अगर ((netdev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
		    rh->r_dh.vlan) अणु
			u16 priority = rh->r_dh.priority;
			u16 vid = rh->r_dh.vlan;

			vtag = (priority << VLAN_PRIO_SHIFT) | vid;
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vtag);
		पूर्ण

		napi_gro_receive(napi, skb);

		droq->stats.rx_bytes_received += len -
			rh->r_dh.len * BYTES_PER_DHLEN_UNIT;
		droq->stats.rx_pkts_received++;
	पूर्ण अन्यथा अणु
		recv_buffer_मुक्त(skb);
	पूर्ण
पूर्ण

/**
 * napi_schedule_wrapper - wrapper क्रम calling napi_schedule
 * @param: parameters to pass to napi_schedule
 *
 * Used when scheduling on dअगरferent CPUs
 */
अटल व्योम napi_schedule_wrapper(व्योम *param)
अणु
	काष्ठा napi_काष्ठा *napi = param;

	napi_schedule(napi);
पूर्ण

/**
 * liquidio_napi_drv_callback - callback when receive पूर्णांकerrupt occurs and we are in NAPI mode
 * @arg: poपूर्णांकer to octeon output queue
 */
अटल व्योम liquidio_napi_drv_callback(व्योम *arg)
अणु
	काष्ठा octeon_device *oct;
	काष्ठा octeon_droq *droq = arg;
	पूर्णांक this_cpu = smp_processor_id();

	oct = droq->oct_dev;

	अगर (OCTEON_CN23XX_PF(oct) || OCTEON_CN23XX_VF(oct) ||
	    droq->cpu_id == this_cpu) अणु
		napi_schedule_irqoff(&droq->napi);
	पूर्ण अन्यथा अणु
		INIT_CSD(&droq->csd, napi_schedule_wrapper, &droq->napi);
		smp_call_function_single_async(droq->cpu_id, &droq->csd);
	पूर्ण
पूर्ण

/**
 * liquidio_napi_poll - Entry poपूर्णांक क्रम NAPI polling
 * @napi: NAPI काष्ठाure
 * @budget: maximum number of items to process
 */
अटल पूर्णांक liquidio_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा octeon_instr_queue *iq;
	काष्ठा octeon_device *oct;
	काष्ठा octeon_droq *droq;
	पूर्णांक tx_करोne = 0, iq_no;
	पूर्णांक work_करोne;

	droq = container_of(napi, काष्ठा octeon_droq, napi);
	oct = droq->oct_dev;
	iq_no = droq->q_no;

	/* Handle Droq descriptors */
	work_करोne = octeon_droq_process_poll_pkts(oct, droq, budget);

	/* Flush the inकाष्ठाion queue */
	iq = oct->instr_queue[iq_no];
	अगर (iq) अणु
		/* TODO: move this check to inside octeon_flush_iq,
		 * once check_db_समयout is हटाओd
		 */
		अगर (atomic_पढ़ो(&iq->instr_pending))
			/* Process iq buffers with in the budget limits */
			tx_करोne = octeon_flush_iq(oct, iq, budget);
		अन्यथा
			tx_करोne = 1;
		/* Update iq पढ़ो-index rather than रुकोing क्रम next पूर्णांकerrupt.
		 * Return back अगर tx_करोne is false.
		 */
		/* sub-queue status update */
		lio_update_txq_status(oct, iq_no);
	पूर्ण अन्यथा अणु
		dev_err(&oct->pci_dev->dev, "%s:  iq (%d) num invalid\n",
			__func__, iq_no);
	पूर्ण

#घोषणा MAX_REG_CNT  2000000U
	/* क्रमce enable पूर्णांकerrupt अगर reg cnts are high to aव्योम wraparound */
	अगर ((work_करोne < budget && tx_करोne) ||
	    (iq && iq->pkt_in_करोne >= MAX_REG_CNT) ||
	    (droq->pkt_count >= MAX_REG_CNT)) अणु
		napi_complete_करोne(napi, work_करोne);

		octeon_enable_irq(droq->oct_dev, droq->q_no);
		वापस 0;
	पूर्ण

	वापस (!tx_करोne) ? (budget) : (work_करोne);
पूर्ण

/**
 * liquidio_setup_io_queues - Setup input and output queues
 * @octeon_dev: octeon device
 * @अगरidx: Interface index
 * @num_iqs: input io queue count
 * @num_oqs: output io queue count
 *
 * Note: Queues are with respect to the octeon device. Thus
 * an input queue is क्रम egress packets, and output queues
 * are क्रम ingress packets.
 */
पूर्णांक liquidio_setup_io_queues(काष्ठा octeon_device *octeon_dev, पूर्णांक अगरidx,
			     u32 num_iqs, u32 num_oqs)
अणु
	काष्ठा octeon_droq_ops droq_ops;
	काष्ठा net_device *netdev;
	काष्ठा octeon_droq *droq;
	काष्ठा napi_काष्ठा *napi;
	पूर्णांक cpu_id_modulus;
	पूर्णांक num_tx_descs;
	काष्ठा lio *lio;
	पूर्णांक retval = 0;
	पूर्णांक q, q_no;
	पूर्णांक cpu_id;

	netdev = octeon_dev->props[अगरidx].netdev;

	lio = GET_LIO(netdev);

	स_रखो(&droq_ops, 0, माप(काष्ठा octeon_droq_ops));

	droq_ops.fptr = liquidio_push_packet;
	droq_ops.farg = netdev;

	droq_ops.poll_mode = 1;
	droq_ops.napi_fn = liquidio_napi_drv_callback;
	cpu_id = 0;
	cpu_id_modulus = num_present_cpus();

	/* set up DROQs. */
	क्रम (q = 0; q < num_oqs; q++) अणु
		q_no = lio->linfo.rxpciq[q].s.q_no;
		dev_dbg(&octeon_dev->pci_dev->dev,
			"%s index:%d linfo.rxpciq.s.q_no:%d\n",
			__func__, q, q_no);
		retval = octeon_setup_droq(
		    octeon_dev, q_no,
		    CFG_GET_NUM_RX_DESCS_NIC_IF(octeon_get_conf(octeon_dev),
						lio->अगरidx),
		    CFG_GET_NUM_RX_BUF_SIZE_NIC_IF(octeon_get_conf(octeon_dev),
						   lio->अगरidx),
		    शून्य);
		अगर (retval) अणु
			dev_err(&octeon_dev->pci_dev->dev,
				"%s : Runtime DROQ(RxQ) creation failed.\n",
				__func__);
			वापस 1;
		पूर्ण

		droq = octeon_dev->droq[q_no];
		napi = &droq->napi;
		dev_dbg(&octeon_dev->pci_dev->dev, "netif_napi_add netdev:%llx oct:%llx\n",
			(u64)netdev, (u64)octeon_dev);
		netअगर_napi_add(netdev, napi, liquidio_napi_poll, 64);

		/* designate a CPU क्रम this droq */
		droq->cpu_id = cpu_id;
		cpu_id++;
		अगर (cpu_id >= cpu_id_modulus)
			cpu_id = 0;

		octeon_रेजिस्टर_droq_ops(octeon_dev, q_no, &droq_ops);
	पूर्ण

	अगर (OCTEON_CN23XX_PF(octeon_dev) || OCTEON_CN23XX_VF(octeon_dev)) अणु
		/* 23XX PF/VF can send/recv control messages (via the first
		 * PF/VF-owned droq) from the firmware even अगर the ethX
		 * पूर्णांकerface is करोwn, so that's why poll_mode must be off
		 * क्रम the first droq.
		 */
		octeon_dev->droq[0]->ops.poll_mode = 0;
	पूर्ण

	/* set up IQs. */
	क्रम (q = 0; q < num_iqs; q++) अणु
		num_tx_descs = CFG_GET_NUM_TX_DESCS_NIC_IF(
		    octeon_get_conf(octeon_dev), lio->अगरidx);
		retval = octeon_setup_iq(octeon_dev, अगरidx, q,
					 lio->linfo.txpciq[q], num_tx_descs,
					 netdev_get_tx_queue(netdev, q));
		अगर (retval) अणु
			dev_err(&octeon_dev->pci_dev->dev,
				" %s : Runtime IQ(TxQ) creation failed.\n",
				__func__);
			वापस 1;
		पूर्ण

		/* XPS */
		अगर (!OCTEON_CN23XX_VF(octeon_dev) && octeon_dev->msix_on &&
		    octeon_dev->ioq_vector) अणु
			काष्ठा octeon_ioq_vector    *ioq_vector;

			ioq_vector = &octeon_dev->ioq_vector[q];
			netअगर_set_xps_queue(netdev,
					    &ioq_vector->affinity_mask,
					    ioq_vector->iq_index);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल
पूर्णांक liquidio_schedule_msix_droq_pkt_handler(काष्ठा octeon_droq *droq, u64 ret)
अणु
	काष्ठा octeon_device *oct = droq->oct_dev;
	काष्ठा octeon_device_priv *oct_priv =
	    (काष्ठा octeon_device_priv *)oct->priv;

	अगर (droq->ops.poll_mode) अणु
		droq->ops.napi_fn(droq);
	पूर्ण अन्यथा अणु
		अगर (ret & MSIX_PO_INT) अणु
			अगर (OCTEON_CN23XX_VF(oct))
				dev_err(&oct->pci_dev->dev,
					"should not come here should not get rx when poll mode = 0 for vf\n");
			tasklet_schedule(&oct_priv->droq_tasklet);
			वापस 1;
		पूर्ण
		/* this will be flushed periodically by check iq db */
		अगर (ret & MSIX_PI_INT)
			वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

irqवापस_t
liquidio_msix_पूर्णांकr_handler(पूर्णांक __maybe_unused irq, व्योम *dev)
अणु
	काष्ठा octeon_ioq_vector *ioq_vector = (काष्ठा octeon_ioq_vector *)dev;
	काष्ठा octeon_device *oct = ioq_vector->oct_dev;
	काष्ठा octeon_droq *droq = oct->droq[ioq_vector->droq_index];
	u64 ret;

	ret = oct->fn_list.msix_पूर्णांकerrupt_handler(ioq_vector);

	अगर (ret & MSIX_PO_INT || ret & MSIX_PI_INT)
		liquidio_schedule_msix_droq_pkt_handler(droq, ret);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * liquidio_schedule_droq_pkt_handlers - Droq packet processor sceduler
 * @oct: octeon device
 */
अटल व्योम liquidio_schedule_droq_pkt_handlers(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_device_priv *oct_priv =
		(काष्ठा octeon_device_priv *)oct->priv;
	काष्ठा octeon_droq *droq;
	u64 oq_no;

	अगर (oct->पूर्णांक_status & OCT_DEV_INTR_PKT_DATA) अणु
		क्रम (oq_no = 0; oq_no < MAX_OCTEON_OUTPUT_QUEUES(oct);
		     oq_no++) अणु
			अगर (!(oct->droq_पूर्णांकr & BIT_ULL(oq_no)))
				जारी;

			droq = oct->droq[oq_no];

			अगर (droq->ops.poll_mode) अणु
				droq->ops.napi_fn(droq);
				oct_priv->napi_mask |= BIT_ULL(oq_no);
			पूर्ण अन्यथा अणु
				tasklet_schedule(&oct_priv->droq_tasklet);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * liquidio_legacy_पूर्णांकr_handler - Interrupt handler क्रम octeon
 * @irq: unused
 * @dev: octeon device
 */
अटल
irqवापस_t liquidio_legacy_पूर्णांकr_handler(पूर्णांक __maybe_unused irq, व्योम *dev)
अणु
	काष्ठा octeon_device *oct = (काष्ठा octeon_device *)dev;
	irqवापस_t ret;

	/* Disable our पूर्णांकerrupts क्रम the duration of ISR */
	oct->fn_list.disable_पूर्णांकerrupt(oct, OCTEON_ALL_INTR);

	ret = oct->fn_list.process_पूर्णांकerrupt_regs(oct);

	अगर (ret == IRQ_HANDLED)
		liquidio_schedule_droq_pkt_handlers(oct);

	/* Re-enable our पूर्णांकerrupts  */
	अगर (!(atomic_पढ़ो(&oct->status) == OCT_DEV_IN_RESET))
		oct->fn_list.enable_पूर्णांकerrupt(oct, OCTEON_ALL_INTR);

	वापस ret;
पूर्ण

/**
 * octeon_setup_पूर्णांकerrupt - Setup पूर्णांकerrupt क्रम octeon device
 * @oct: octeon device
 * @num_ioqs: number of queues
 *
 *  Enable पूर्णांकerrupt in Octeon device as given in the PCI पूर्णांकerrupt mask.
 */
पूर्णांक octeon_setup_पूर्णांकerrupt(काष्ठा octeon_device *oct, u32 num_ioqs)
अणु
	काष्ठा msix_entry *msix_entries;
	अक्षर *queue_irq_names = शून्य;
	पूर्णांक i, num_पूर्णांकerrupts = 0;
	पूर्णांक num_alloc_ioq_vectors;
	अक्षर *aux_irq_name = शून्य;
	पूर्णांक num_ioq_vectors;
	पूर्णांक irqret, err;

	अगर (oct->msix_on) अणु
		oct->num_msix_irqs = num_ioqs;
		अगर (OCTEON_CN23XX_PF(oct)) अणु
			num_पूर्णांकerrupts = MAX_IOQ_INTERRUPTS_PER_PF + 1;

			/* one non ioq पूर्णांकerrupt क्रम handling
			 * sli_mac_pf_पूर्णांक_sum
			 */
			oct->num_msix_irqs += 1;
		पूर्ण अन्यथा अगर (OCTEON_CN23XX_VF(oct)) अणु
			num_पूर्णांकerrupts = MAX_IOQ_INTERRUPTS_PER_VF;
		पूर्ण

		/* allocate storage क्रम the names asचिन्हित to each irq */
		oct->irq_name_storage =
			kसुस्मृति(num_पूर्णांकerrupts, INTRNAMSIZ, GFP_KERNEL);
		अगर (!oct->irq_name_storage) अणु
			dev_err(&oct->pci_dev->dev, "Irq name storage alloc failed...\n");
			वापस -ENOMEM;
		पूर्ण

		queue_irq_names = oct->irq_name_storage;

		अगर (OCTEON_CN23XX_PF(oct))
			aux_irq_name = &queue_irq_names
				[IRQ_NAME_OFF(MAX_IOQ_INTERRUPTS_PER_PF)];

		oct->msix_entries = kसुस्मृति(oct->num_msix_irqs,
					    माप(काष्ठा msix_entry),
					    GFP_KERNEL);
		अगर (!oct->msix_entries) अणु
			dev_err(&oct->pci_dev->dev, "Memory Alloc failed...\n");
			kमुक्त(oct->irq_name_storage);
			oct->irq_name_storage = शून्य;
			वापस -ENOMEM;
		पूर्ण

		msix_entries = (काष्ठा msix_entry *)oct->msix_entries;

		/*Assumption is that pf msix vectors start from pf srn to pf to
		 * trs and not from 0. अगर not change this code
		 */
		अगर (OCTEON_CN23XX_PF(oct)) अणु
			क्रम (i = 0; i < oct->num_msix_irqs - 1; i++)
				msix_entries[i].entry =
					oct->sriov_info.pf_srn + i;

			msix_entries[oct->num_msix_irqs - 1].entry =
				oct->sriov_info.trs;
		पूर्ण अन्यथा अगर (OCTEON_CN23XX_VF(oct)) अणु
			क्रम (i = 0; i < oct->num_msix_irqs; i++)
				msix_entries[i].entry = i;
		पूर्ण
		num_alloc_ioq_vectors = pci_enable_msix_range(
						oct->pci_dev, msix_entries,
						oct->num_msix_irqs,
						oct->num_msix_irqs);
		अगर (num_alloc_ioq_vectors < 0) अणु
			dev_err(&oct->pci_dev->dev, "unable to Allocate MSI-X interrupts\n");
			kमुक्त(oct->msix_entries);
			oct->msix_entries = शून्य;
			kमुक्त(oct->irq_name_storage);
			oct->irq_name_storage = शून्य;
			वापस num_alloc_ioq_vectors;
		पूर्ण

		dev_dbg(&oct->pci_dev->dev, "OCTEON: Enough MSI-X interrupts are allocated...\n");

		num_ioq_vectors = oct->num_msix_irqs;
		/* For PF, there is one non-ioq पूर्णांकerrupt handler */
		अगर (OCTEON_CN23XX_PF(oct)) अणु
			num_ioq_vectors -= 1;

			snम_लिखो(aux_irq_name, INTRNAMSIZ,
				 "LiquidIO%u-pf%u-aux", oct->octeon_id,
				 oct->pf_num);
			irqret = request_irq(
					msix_entries[num_ioq_vectors].vector,
					liquidio_legacy_पूर्णांकr_handler, 0,
					aux_irq_name, oct);
			अगर (irqret) अणु
				dev_err(&oct->pci_dev->dev,
					"Request_irq failed for MSIX interrupt Error: %d\n",
					irqret);
				pci_disable_msix(oct->pci_dev);
				kमुक्त(oct->msix_entries);
				kमुक्त(oct->irq_name_storage);
				oct->irq_name_storage = शून्य;
				oct->msix_entries = शून्य;
				वापस irqret;
			पूर्ण
		पूर्ण
		क्रम (i = 0 ; i < num_ioq_vectors ; i++) अणु
			अगर (OCTEON_CN23XX_PF(oct))
				snम_लिखो(&queue_irq_names[IRQ_NAME_OFF(i)],
					 INTRNAMSIZ, "LiquidIO%u-pf%u-rxtx-%u",
					 oct->octeon_id, oct->pf_num, i);

			अगर (OCTEON_CN23XX_VF(oct))
				snम_लिखो(&queue_irq_names[IRQ_NAME_OFF(i)],
					 INTRNAMSIZ, "LiquidIO%u-vf%u-rxtx-%u",
					 oct->octeon_id, oct->vf_num, i);

			irqret = request_irq(msix_entries[i].vector,
					     liquidio_msix_पूर्णांकr_handler, 0,
					     &queue_irq_names[IRQ_NAME_OFF(i)],
					     &oct->ioq_vector[i]);

			अगर (irqret) अणु
				dev_err(&oct->pci_dev->dev,
					"Request_irq failed for MSIX interrupt Error: %d\n",
					irqret);
				/* Freeing the non-ioq irq vector here . */
				मुक्त_irq(msix_entries[num_ioq_vectors].vector,
					 oct);

				जबतक (i) अणु
					i--;
					/* clearing affinity mask. */
					irq_set_affinity_hपूर्णांक(
						      msix_entries[i].vector,
						      शून्य);
					मुक्त_irq(msix_entries[i].vector,
						 &oct->ioq_vector[i]);
				पूर्ण
				pci_disable_msix(oct->pci_dev);
				kमुक्त(oct->msix_entries);
				kमुक्त(oct->irq_name_storage);
				oct->irq_name_storage = शून्य;
				oct->msix_entries = शून्य;
				वापस irqret;
			पूर्ण
			oct->ioq_vector[i].vector = msix_entries[i].vector;
			/* assign the cpu mask क्रम this msix पूर्णांकerrupt vector */
			irq_set_affinity_hपूर्णांक(msix_entries[i].vector,
					      &oct->ioq_vector[i].affinity_mask
					      );
		पूर्ण
		dev_dbg(&oct->pci_dev->dev, "OCTEON[%d]: MSI-X enabled\n",
			oct->octeon_id);
	पूर्ण अन्यथा अणु
		err = pci_enable_msi(oct->pci_dev);
		अगर (err)
			dev_warn(&oct->pci_dev->dev, "Reverting to legacy interrupts. Error: %d\n",
				 err);
		अन्यथा
			oct->flags |= LIO_FLAG_MSI_ENABLED;

		/* allocate storage क्रम the names asचिन्हित to the irq */
		oct->irq_name_storage = kzalloc(INTRNAMSIZ, GFP_KERNEL);
		अगर (!oct->irq_name_storage)
			वापस -ENOMEM;

		queue_irq_names = oct->irq_name_storage;

		अगर (OCTEON_CN23XX_PF(oct))
			snम_लिखो(&queue_irq_names[IRQ_NAME_OFF(0)], INTRNAMSIZ,
				 "LiquidIO%u-pf%u-rxtx-%u",
				 oct->octeon_id, oct->pf_num, 0);

		अगर (OCTEON_CN23XX_VF(oct))
			snम_लिखो(&queue_irq_names[IRQ_NAME_OFF(0)], INTRNAMSIZ,
				 "LiquidIO%u-vf%u-rxtx-%u",
				 oct->octeon_id, oct->vf_num, 0);

		irqret = request_irq(oct->pci_dev->irq,
				     liquidio_legacy_पूर्णांकr_handler,
				     IRQF_SHARED,
				     &queue_irq_names[IRQ_NAME_OFF(0)], oct);
		अगर (irqret) अणु
			अगर (oct->flags & LIO_FLAG_MSI_ENABLED)
				pci_disable_msi(oct->pci_dev);
			dev_err(&oct->pci_dev->dev, "Request IRQ failed with code: %d\n",
				irqret);
			kमुक्त(oct->irq_name_storage);
			oct->irq_name_storage = शून्य;
			वापस irqret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * liquidio_change_mtu - Net device change_mtu
 * @netdev: network device
 * @new_mtu: the new max transmit unit size
 */
पूर्णांक liquidio_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा octeon_soft_command *sc;
	जोड़ octnet_cmd *ncmd;
	पूर्णांक ret = 0;

	sc = (काष्ठा octeon_soft_command *)
		octeon_alloc_soft_command(oct, OCTNET_CMD_SIZE, 16, 0);
	अगर (!sc) अणु
		netअगर_info(lio, rx_err, lio->netdev,
			   "Failed to allocate soft command\n");
		वापस -ENOMEM;
	पूर्ण

	ncmd = (जोड़ octnet_cmd *)sc->virtdptr;

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	ncmd->u64 = 0;
	ncmd->s.cmd = OCTNET_CMD_CHANGE_MTU;
	ncmd->s.param1 = new_mtu;

	octeon_swap_8B_data((u64 *)ncmd, (OCTNET_CMD_SIZE >> 3));

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	octeon_prepare_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_CMD, 0, 0, 0);

	ret = octeon_send_soft_command(oct, sc);
	अगर (ret == IQ_SEND_FAILED) अणु
		netअगर_info(lio, rx_err, lio->netdev, "Failed to change MTU\n");
		octeon_मुक्त_soft_command(oct, sc);
		वापस -EINVAL;
	पूर्ण
	/* Sleep on a रुको queue till the cond flag indicates that the
	 * response arrived or समयd-out.
	 */
	ret = रुको_क्रम_sc_completion_समयout(oct, sc, 0);
	अगर (ret)
		वापस ret;

	अगर (sc->sc_status) अणु
		WRITE_ONCE(sc->caller_is_करोne, true);
		वापस -EINVAL;
	पूर्ण

	netdev->mtu = new_mtu;
	lio->mtu = new_mtu;

	WRITE_ONCE(sc->caller_is_करोne, true);
	वापस 0;
पूर्ण

पूर्णांक lio_रुको_क्रम_clean_oq(काष्ठा octeon_device *oct)
अणु
	पूर्णांक retry = 100, pending_pkts = 0;
	पूर्णांक idx;

	करो अणु
		pending_pkts = 0;

		क्रम (idx = 0; idx < MAX_OCTEON_OUTPUT_QUEUES(oct); idx++) अणु
			अगर (!(oct->io_qmask.oq & BIT_ULL(idx)))
				जारी;
			pending_pkts +=
				atomic_पढ़ो(&oct->droq[idx]->pkts_pending);
		पूर्ण

		अगर (pending_pkts > 0)
			schedule_समयout_unपूर्णांकerruptible(1);

	पूर्ण जबतक (retry-- && pending_pkts);

	वापस pending_pkts;
पूर्ण

अटल व्योम
octnet_nic_stats_callback(काष्ठा octeon_device *oct_dev,
			  u32 status, व्योम *ptr)
अणु
	काष्ठा octeon_soft_command *sc = (काष्ठा octeon_soft_command *)ptr;
	काष्ठा oct_nic_stats_resp *resp =
	    (काष्ठा oct_nic_stats_resp *)sc->virtrptr;
	काष्ठा nic_rx_stats *rsp_rstats = &resp->stats.fromwire;
	काष्ठा nic_tx_stats *rsp_tstats = &resp->stats.fromhost;
	काष्ठा nic_rx_stats *rstats = &oct_dev->link_stats.fromwire;
	काष्ठा nic_tx_stats *tstats = &oct_dev->link_stats.fromhost;

	अगर (status != OCTEON_REQUEST_TIMEOUT && !resp->status) अणु
		octeon_swap_8B_data((u64 *)&resp->stats,
				    (माप(काष्ठा oct_link_stats)) >> 3);

		/* RX link-level stats */
		rstats->total_rcvd = rsp_rstats->total_rcvd;
		rstats->bytes_rcvd = rsp_rstats->bytes_rcvd;
		rstats->total_bcst = rsp_rstats->total_bcst;
		rstats->total_mcst = rsp_rstats->total_mcst;
		rstats->runts      = rsp_rstats->runts;
		rstats->ctl_rcvd   = rsp_rstats->ctl_rcvd;
		/* Accounts क्रम over/under-run of buffers */
		rstats->fअगरo_err  = rsp_rstats->fअगरo_err;
		rstats->dmac_drop = rsp_rstats->dmac_drop;
		rstats->fcs_err   = rsp_rstats->fcs_err;
		rstats->jabber_err = rsp_rstats->jabber_err;
		rstats->l2_err    = rsp_rstats->l2_err;
		rstats->frame_err = rsp_rstats->frame_err;
		rstats->red_drops = rsp_rstats->red_drops;

		/* RX firmware stats */
		rstats->fw_total_rcvd = rsp_rstats->fw_total_rcvd;
		rstats->fw_total_fwd = rsp_rstats->fw_total_fwd;
		rstats->fw_total_mcast = rsp_rstats->fw_total_mcast;
		rstats->fw_total_bcast = rsp_rstats->fw_total_bcast;
		rstats->fw_err_pko = rsp_rstats->fw_err_pko;
		rstats->fw_err_link = rsp_rstats->fw_err_link;
		rstats->fw_err_drop = rsp_rstats->fw_err_drop;
		rstats->fw_rx_vxlan = rsp_rstats->fw_rx_vxlan;
		rstats->fw_rx_vxlan_err = rsp_rstats->fw_rx_vxlan_err;

		/* Number of packets that are LROed      */
		rstats->fw_lro_pkts = rsp_rstats->fw_lro_pkts;
		/* Number of octets that are LROed       */
		rstats->fw_lro_octs = rsp_rstats->fw_lro_octs;
		/* Number of LRO packets क्रमmed          */
		rstats->fw_total_lro = rsp_rstats->fw_total_lro;
		/* Number of बार lRO of packet पातed */
		rstats->fw_lro_पातs = rsp_rstats->fw_lro_पातs;
		rstats->fw_lro_पातs_port = rsp_rstats->fw_lro_पातs_port;
		rstats->fw_lro_पातs_seq = rsp_rstats->fw_lro_पातs_seq;
		rstats->fw_lro_पातs_tsval = rsp_rstats->fw_lro_पातs_tsval;
		rstats->fw_lro_पातs_समयr = rsp_rstats->fw_lro_पातs_समयr;
		/* पूर्णांकrmod: packet क्रमward rate */
		rstats->fwd_rate = rsp_rstats->fwd_rate;

		/* TX link-level stats */
		tstats->total_pkts_sent = rsp_tstats->total_pkts_sent;
		tstats->total_bytes_sent = rsp_tstats->total_bytes_sent;
		tstats->mcast_pkts_sent = rsp_tstats->mcast_pkts_sent;
		tstats->bcast_pkts_sent = rsp_tstats->bcast_pkts_sent;
		tstats->ctl_sent = rsp_tstats->ctl_sent;
		/* Packets sent after one collision*/
		tstats->one_collision_sent = rsp_tstats->one_collision_sent;
		/* Packets sent after multiple collision*/
		tstats->multi_collision_sent = rsp_tstats->multi_collision_sent;
		/* Packets not sent due to max collisions */
		tstats->max_collision_fail = rsp_tstats->max_collision_fail;
		/* Packets not sent due to max deferrals */
		tstats->max_deferral_fail = rsp_tstats->max_deferral_fail;
		/* Accounts क्रम over/under-run of buffers */
		tstats->fअगरo_err = rsp_tstats->fअगरo_err;
		tstats->runts = rsp_tstats->runts;
		/* Total number of collisions detected */
		tstats->total_collisions = rsp_tstats->total_collisions;

		/* firmware stats */
		tstats->fw_total_sent = rsp_tstats->fw_total_sent;
		tstats->fw_total_fwd = rsp_tstats->fw_total_fwd;
		tstats->fw_total_mcast_sent = rsp_tstats->fw_total_mcast_sent;
		tstats->fw_total_bcast_sent = rsp_tstats->fw_total_bcast_sent;
		tstats->fw_err_pko = rsp_tstats->fw_err_pko;
		tstats->fw_err_pki = rsp_tstats->fw_err_pki;
		tstats->fw_err_link = rsp_tstats->fw_err_link;
		tstats->fw_err_drop = rsp_tstats->fw_err_drop;
		tstats->fw_tso = rsp_tstats->fw_tso;
		tstats->fw_tso_fwd = rsp_tstats->fw_tso_fwd;
		tstats->fw_err_tso = rsp_tstats->fw_err_tso;
		tstats->fw_tx_vxlan = rsp_tstats->fw_tx_vxlan;

		resp->status = 1;
	पूर्ण अन्यथा अणु
		dev_err(&oct_dev->pci_dev->dev, "sc OPCODE_NIC_PORT_STATS command failed\n");
		resp->status = -1;
	पूर्ण
पूर्ण

अटल पूर्णांक lio_fetch_vf_stats(काष्ठा lio *lio)
अणु
	काष्ठा octeon_device *oct_dev = lio->oct_dev;
	काष्ठा octeon_soft_command *sc;
	काष्ठा oct_nic_vf_stats_resp *resp;

	पूर्णांक retval;

	/* Alloc soft command */
	sc = (काष्ठा octeon_soft_command *)
		octeon_alloc_soft_command(oct_dev,
					  0,
					  माप(काष्ठा oct_nic_vf_stats_resp),
					  0);

	अगर (!sc) अणु
		dev_err(&oct_dev->pci_dev->dev, "Soft command allocation failed\n");
		retval = -ENOMEM;
		जाओ lio_fetch_vf_stats_निकास;
	पूर्ण

	resp = (काष्ठा oct_nic_vf_stats_resp *)sc->virtrptr;
	स_रखो(resp, 0, माप(काष्ठा oct_nic_vf_stats_resp));

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	octeon_prepare_soft_command(oct_dev, sc, OPCODE_NIC,
				    OPCODE_NIC_VF_PORT_STATS, 0, 0, 0);

	retval = octeon_send_soft_command(oct_dev, sc);
	अगर (retval == IQ_SEND_FAILED) अणु
		octeon_मुक्त_soft_command(oct_dev, sc);
		जाओ lio_fetch_vf_stats_निकास;
	पूर्ण

	retval =
		रुको_क्रम_sc_completion_समयout(oct_dev, sc,
					       (2 * LIO_SC_MAX_TMO_MS));
	अगर (retval)  अणु
		dev_err(&oct_dev->pci_dev->dev,
			"sc OPCODE_NIC_VF_PORT_STATS command failed\n");
		जाओ lio_fetch_vf_stats_निकास;
	पूर्ण

	अगर (sc->sc_status != OCTEON_REQUEST_TIMEOUT && !resp->status) अणु
		octeon_swap_8B_data((u64 *)&resp->spoofmac_cnt,
				    (माप(u64)) >> 3);

		अगर (resp->spoofmac_cnt != 0) अणु
			dev_warn(&oct_dev->pci_dev->dev,
				 "%llu Spoofed packets detected\n",
				 resp->spoofmac_cnt);
		पूर्ण
	पूर्ण
	WRITE_ONCE(sc->caller_is_करोne, 1);

lio_fetch_vf_stats_निकास:
	वापस retval;
पूर्ण

व्योम lio_fetch_stats(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cavium_wk *wk = (काष्ठा cavium_wk *)work;
	काष्ठा lio *lio = wk->ctxptr;
	काष्ठा octeon_device *oct_dev = lio->oct_dev;
	काष्ठा octeon_soft_command *sc;
	काष्ठा oct_nic_stats_resp *resp;
	अचिन्हित दीर्घ समय_in_jअगरfies;
	पूर्णांक retval;

	अगर (OCTEON_CN23XX_PF(oct_dev)) अणु
		/* report spoofchk every 2 seconds */
		अगर (!(oct_dev->vख_स्थितिs_poll % LIO_VFSTATS_POLL) &&
		    (oct_dev->fw_info.app_cap_flags & LIQUIDIO_SPOOFCHK_CAP) &&
		    oct_dev->sriov_info.num_vfs_alloced) अणु
			lio_fetch_vf_stats(lio);
		पूर्ण

		oct_dev->vख_स्थितिs_poll++;
	पूर्ण

	/* Alloc soft command */
	sc = (काष्ठा octeon_soft_command *)
		octeon_alloc_soft_command(oct_dev,
					  0,
					  माप(काष्ठा oct_nic_stats_resp),
					  0);

	अगर (!sc) अणु
		dev_err(&oct_dev->pci_dev->dev, "Soft command allocation failed\n");
		जाओ lio_fetch_stats_निकास;
	पूर्ण

	resp = (काष्ठा oct_nic_stats_resp *)sc->virtrptr;
	स_रखो(resp, 0, माप(काष्ठा oct_nic_stats_resp));

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	octeon_prepare_soft_command(oct_dev, sc, OPCODE_NIC,
				    OPCODE_NIC_PORT_STATS, 0, 0, 0);

	retval = octeon_send_soft_command(oct_dev, sc);
	अगर (retval == IQ_SEND_FAILED) अणु
		octeon_मुक्त_soft_command(oct_dev, sc);
		जाओ lio_fetch_stats_निकास;
	पूर्ण

	retval = रुको_क्रम_sc_completion_समयout(oct_dev, sc,
						(2 * LIO_SC_MAX_TMO_MS));
	अगर (retval)  अणु
		dev_err(&oct_dev->pci_dev->dev, "sc OPCODE_NIC_PORT_STATS command failed\n");
		जाओ lio_fetch_stats_निकास;
	पूर्ण

	octnet_nic_stats_callback(oct_dev, sc->sc_status, sc);
	WRITE_ONCE(sc->caller_is_करोne, true);

lio_fetch_stats_निकास:
	समय_in_jअगरfies = msecs_to_jअगरfies(LIQUIDIO_NDEV_STATS_POLL_TIME_MS);
	अगर (अगरstate_check(lio, LIO_IFSTATE_RUNNING))
		schedule_delayed_work(&lio->stats_wk.work, समय_in_jअगरfies);

	वापस;
पूर्ण

पूर्णांक liquidio_set_speed(काष्ठा lio *lio, पूर्णांक speed)
अणु
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा oct_nic_seapi_resp *resp;
	काष्ठा octeon_soft_command *sc;
	जोड़ octnet_cmd *ncmd;
	पूर्णांक retval;
	u32 var;

	अगर (oct->speed_setting == speed)
		वापस 0;

	अगर (!OCTEON_CN23XX_PF(oct)) अणु
		dev_err(&oct->pci_dev->dev, "%s: SET SPEED only for PF\n",
			__func__);
		वापस -EOPNOTSUPP;
	पूर्ण

	sc = octeon_alloc_soft_command(oct, OCTNET_CMD_SIZE,
				       माप(काष्ठा oct_nic_seapi_resp),
				       0);
	अगर (!sc)
		वापस -ENOMEM;

	ncmd = sc->virtdptr;
	resp = sc->virtrptr;
	स_रखो(resp, 0, माप(काष्ठा oct_nic_seapi_resp));

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	ncmd->u64 = 0;
	ncmd->s.cmd = SEAPI_CMD_SPEED_SET;
	ncmd->s.param1 = speed;

	octeon_swap_8B_data((u64 *)ncmd, (OCTNET_CMD_SIZE >> 3));

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	octeon_prepare_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_UBOOT_CTL, 0, 0, 0);

	retval = octeon_send_soft_command(oct, sc);
	अगर (retval == IQ_SEND_FAILED) अणु
		dev_info(&oct->pci_dev->dev, "Failed to send soft command\n");
		octeon_मुक्त_soft_command(oct, sc);
		retval = -EBUSY;
	पूर्ण अन्यथा अणु
		/* Wait क्रम response or समयout */
		retval = रुको_क्रम_sc_completion_समयout(oct, sc, 0);
		अगर (retval)
			वापस retval;

		retval = resp->status;

		अगर (retval) अणु
			dev_err(&oct->pci_dev->dev, "%s failed, retval=%d\n",
				__func__, retval);
			WRITE_ONCE(sc->caller_is_करोne, true);

			वापस -EIO;
		पूर्ण

		var = be32_to_cpu((__क्रमce __be32)resp->speed);
		अगर (var != speed) अणु
			dev_err(&oct->pci_dev->dev,
				"%s: setting failed speed= %x, expect %x\n",
				__func__, var, speed);
		पूर्ण

		oct->speed_setting = var;
		WRITE_ONCE(sc->caller_is_करोne, true);
	पूर्ण

	वापस retval;
पूर्ण

पूर्णांक liquidio_get_speed(काष्ठा lio *lio)
अणु
	काष्ठा octeon_device *oct = lio->oct_dev;
	काष्ठा oct_nic_seapi_resp *resp;
	काष्ठा octeon_soft_command *sc;
	जोड़ octnet_cmd *ncmd;
	पूर्णांक retval;

	sc = octeon_alloc_soft_command(oct, OCTNET_CMD_SIZE,
				       माप(काष्ठा oct_nic_seapi_resp),
				       0);
	अगर (!sc)
		वापस -ENOMEM;

	ncmd = sc->virtdptr;
	resp = sc->virtrptr;
	स_रखो(resp, 0, माप(काष्ठा oct_nic_seapi_resp));

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	ncmd->u64 = 0;
	ncmd->s.cmd = SEAPI_CMD_SPEED_GET;

	octeon_swap_8B_data((u64 *)ncmd, (OCTNET_CMD_SIZE >> 3));

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	octeon_prepare_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_UBOOT_CTL, 0, 0, 0);

	retval = octeon_send_soft_command(oct, sc);
	अगर (retval == IQ_SEND_FAILED) अणु
		dev_info(&oct->pci_dev->dev, "Failed to send soft command\n");
		octeon_मुक्त_soft_command(oct, sc);
		retval = -EIO;
	पूर्ण अन्यथा अणु
		retval = रुको_क्रम_sc_completion_समयout(oct, sc, 0);
		अगर (retval)
			वापस retval;

		retval = resp->status;
		अगर (retval) अणु
			dev_err(&oct->pci_dev->dev,
				"%s failed retval=%d\n", __func__, retval);
			retval = -EIO;
		पूर्ण अन्यथा अणु
			u32 var;

			var = be32_to_cpu((__क्रमce __be32)resp->speed);
			oct->speed_setting = var;
			अगर (var == 0xffff) अणु
				/* unable to access boot variables
				 * get the शेष value based on the NIC type
				 */
				अगर (oct->subप्रणाली_id ==
						OCTEON_CN2350_25GB_SUBSYS_ID ||
				    oct->subप्रणाली_id ==
						OCTEON_CN2360_25GB_SUBSYS_ID) अणु
					oct->no_speed_setting = 1;
					oct->speed_setting = 25;
				पूर्ण अन्यथा अणु
					oct->speed_setting = 10;
				पूर्ण
			पूर्ण

		पूर्ण
		WRITE_ONCE(sc->caller_is_करोne, true);
	पूर्ण

	वापस retval;
पूर्ण

पूर्णांक liquidio_set_fec(काष्ठा lio *lio, पूर्णांक on_off)
अणु
	काष्ठा oct_nic_seapi_resp *resp;
	काष्ठा octeon_soft_command *sc;
	काष्ठा octeon_device *oct;
	जोड़ octnet_cmd *ncmd;
	पूर्णांक retval;
	u32 var;

	oct = lio->oct_dev;

	अगर (oct->props[lio->अगरidx].fec == on_off)
		वापस 0;

	अगर (!OCTEON_CN23XX_PF(oct)) अणु
		dev_err(&oct->pci_dev->dev, "%s: SET FEC only for PF\n",
			__func__);
		वापस -1;
	पूर्ण

	अगर (oct->speed_boot != 25)  अणु
		dev_err(&oct->pci_dev->dev,
			"Set FEC only when link speed is 25G during insmod\n");
		वापस -1;
	पूर्ण

	sc = octeon_alloc_soft_command(oct, OCTNET_CMD_SIZE,
				       माप(काष्ठा oct_nic_seapi_resp), 0);
	अगर (!sc) अणु
		dev_err(&oct->pci_dev->dev,
			"Failed to allocate soft command\n");
		वापस -ENOMEM;
	पूर्ण

	ncmd = sc->virtdptr;
	resp = sc->virtrptr;
	स_रखो(resp, 0, माप(काष्ठा oct_nic_seapi_resp));

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	ncmd->u64 = 0;
	ncmd->s.cmd = SEAPI_CMD_FEC_SET;
	ncmd->s.param1 = on_off;
	/* SEAPI_CMD_FEC_DISABLE(0) or SEAPI_CMD_FEC_RS(1) */

	octeon_swap_8B_data((u64 *)ncmd, (OCTNET_CMD_SIZE >> 3));

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	octeon_prepare_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_UBOOT_CTL, 0, 0, 0);

	retval = octeon_send_soft_command(oct, sc);
	अगर (retval == IQ_SEND_FAILED) अणु
		dev_info(&oct->pci_dev->dev, "Failed to send soft command\n");
		octeon_मुक्त_soft_command(oct, sc);
		वापस -EIO;
	पूर्ण

	retval = रुको_क्रम_sc_completion_समयout(oct, sc, 0);
	अगर (retval)
		वापस (-EIO);

	var = be32_to_cpu(resp->fec_setting);
	resp->fec_setting = var;
	अगर (var != on_off) अणु
		dev_err(&oct->pci_dev->dev,
			"Setting failed fec= %x, expect %x\n",
			var, on_off);
		oct->props[lio->अगरidx].fec = var;
		अगर (resp->fec_setting == SEAPI_CMD_FEC_SET_RS)
			oct->props[lio->अगरidx].fec = 1;
		अन्यथा
			oct->props[lio->अगरidx].fec = 0;
	पूर्ण

	WRITE_ONCE(sc->caller_is_करोne, true);

	अगर (oct->props[lio->अगरidx].fec !=
	    oct->props[lio->अगरidx].fec_boot) अणु
		dev_dbg(&oct->pci_dev->dev,
			"Reload driver to change fec to %s\n",
			oct->props[lio->अगरidx].fec ? "on" : "off");
	पूर्ण

	वापस retval;
पूर्ण

पूर्णांक liquidio_get_fec(काष्ठा lio *lio)
अणु
	काष्ठा oct_nic_seapi_resp *resp;
	काष्ठा octeon_soft_command *sc;
	काष्ठा octeon_device *oct;
	जोड़ octnet_cmd *ncmd;
	पूर्णांक retval;
	u32 var;

	oct = lio->oct_dev;

	sc = octeon_alloc_soft_command(oct, OCTNET_CMD_SIZE,
				       माप(काष्ठा oct_nic_seapi_resp), 0);
	अगर (!sc)
		वापस -ENOMEM;

	ncmd = sc->virtdptr;
	resp = sc->virtrptr;
	स_रखो(resp, 0, माप(काष्ठा oct_nic_seapi_resp));

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	ncmd->u64 = 0;
	ncmd->s.cmd = SEAPI_CMD_FEC_GET;

	octeon_swap_8B_data((u64 *)ncmd, (OCTNET_CMD_SIZE >> 3));

	sc->iq_no = lio->linfo.txpciq[0].s.q_no;

	octeon_prepare_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_UBOOT_CTL, 0, 0, 0);

	retval = octeon_send_soft_command(oct, sc);
	अगर (retval == IQ_SEND_FAILED) अणु
		dev_info(&oct->pci_dev->dev,
			 "%s: Failed to send soft command\n", __func__);
		octeon_मुक्त_soft_command(oct, sc);
		वापस -EIO;
	पूर्ण

	retval = रुको_क्रम_sc_completion_समयout(oct, sc, 0);
	अगर (retval)
		वापस retval;

	var = be32_to_cpu(resp->fec_setting);
	resp->fec_setting = var;
	अगर (resp->fec_setting == SEAPI_CMD_FEC_SET_RS)
		oct->props[lio->अगरidx].fec = 1;
	अन्यथा
		oct->props[lio->अगरidx].fec = 0;

	WRITE_ONCE(sc->caller_is_करोne, true);

	अगर (oct->props[lio->अगरidx].fec !=
	    oct->props[lio->अगरidx].fec_boot) अणु
		dev_dbg(&oct->pci_dev->dev,
			"Reload driver to change fec to %s\n",
			oct->props[lio->अगरidx].fec ? "on" : "off");
	पूर्ण

	वापस retval;
पूर्ण
