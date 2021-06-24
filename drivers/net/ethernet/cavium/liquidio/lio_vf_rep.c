<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2017 Cavium, Inc.
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
#समावेश "lio_vf_rep.h"

अटल पूर्णांक lio_vf_rep_खोलो(काष्ठा net_device *ndev);
अटल पूर्णांक lio_vf_rep_stop(काष्ठा net_device *ndev);
अटल netdev_tx_t lio_vf_rep_pkt_xmit(काष्ठा sk_buff *skb,
				       काष्ठा net_device *ndev);
अटल व्योम lio_vf_rep_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue);
अटल पूर्णांक lio_vf_rep_phys_port_name(काष्ठा net_device *dev,
				     अक्षर *buf, माप_प्रकार len);
अटल व्योम lio_vf_rep_get_stats64(काष्ठा net_device *dev,
				   काष्ठा rtnl_link_stats64 *stats64);
अटल पूर्णांक lio_vf_rep_change_mtu(काष्ठा net_device *ndev, पूर्णांक new_mtu);
अटल पूर्णांक lio_vf_get_port_parent_id(काष्ठा net_device *dev,
				     काष्ठा netdev_phys_item_id *ppid);

अटल स्थिर काष्ठा net_device_ops lio_vf_rep_ndev_ops = अणु
	.nकरो_खोलो = lio_vf_rep_खोलो,
	.nकरो_stop = lio_vf_rep_stop,
	.nकरो_start_xmit = lio_vf_rep_pkt_xmit,
	.nकरो_tx_समयout = lio_vf_rep_tx_समयout,
	.nकरो_get_phys_port_name = lio_vf_rep_phys_port_name,
	.nकरो_get_stats64 = lio_vf_rep_get_stats64,
	.nकरो_change_mtu = lio_vf_rep_change_mtu,
	.nकरो_get_port_parent_id = lio_vf_get_port_parent_id,
पूर्ण;

अटल पूर्णांक
lio_vf_rep_send_soft_command(काष्ठा octeon_device *oct,
			     व्योम *req, पूर्णांक req_size,
			     व्योम *resp, पूर्णांक resp_size)
अणु
	पूर्णांक tot_resp_size = माप(काष्ठा lio_vf_rep_resp) + resp_size;
	काष्ठा octeon_soft_command *sc = शून्य;
	काष्ठा lio_vf_rep_resp *rep_resp;
	व्योम *sc_req;
	पूर्णांक err;

	sc = (काष्ठा octeon_soft_command *)
		octeon_alloc_soft_command(oct, req_size,
					  tot_resp_size, 0);
	अगर (!sc)
		वापस -ENOMEM;

	init_completion(&sc->complete);
	sc->sc_status = OCTEON_REQUEST_PENDING;

	sc_req = (काष्ठा lio_vf_rep_req *)sc->virtdptr;
	स_नकल(sc_req, req, req_size);

	rep_resp = (काष्ठा lio_vf_rep_resp *)sc->virtrptr;
	स_रखो(rep_resp, 0, tot_resp_size);
	WRITE_ONCE(rep_resp->status, 1);

	sc->iq_no = 0;
	octeon_prepare_soft_command(oct, sc, OPCODE_NIC,
				    OPCODE_NIC_VF_REP_CMD, 0, 0, 0);

	err = octeon_send_soft_command(oct, sc);
	अगर (err == IQ_SEND_FAILED)
		जाओ मुक्त_buff;

	err = रुको_क्रम_sc_completion_समयout(oct, sc, 0);
	अगर (err)
		वापस err;

	err = READ_ONCE(rep_resp->status) ? -EBUSY : 0;
	अगर (err)
		dev_err(&oct->pci_dev->dev, "VF rep send config failed\n");
	अन्यथा अगर (resp)
		स_नकल(resp, (rep_resp + 1), resp_size);

	WRITE_ONCE(sc->caller_is_करोne, true);
	वापस err;

मुक्त_buff:
	octeon_मुक्त_soft_command(oct, sc);

	वापस err;
पूर्ण

अटल पूर्णांक
lio_vf_rep_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा lio_vf_rep_desc *vf_rep = netdev_priv(ndev);
	काष्ठा lio_vf_rep_req rep_cfg;
	काष्ठा octeon_device *oct;
	पूर्णांक ret;

	oct = vf_rep->oct;

	स_रखो(&rep_cfg, 0, माप(rep_cfg));
	rep_cfg.req_type = LIO_VF_REP_REQ_STATE;
	rep_cfg.अगरidx = vf_rep->अगरidx;
	rep_cfg.rep_state.state = LIO_VF_REP_STATE_UP;

	ret = lio_vf_rep_send_soft_command(oct, &rep_cfg,
					   माप(rep_cfg), शून्य, 0);

	अगर (ret) अणु
		dev_err(&oct->pci_dev->dev,
			"VF_REP open failed with err %d\n", ret);
		वापस -EIO;
	पूर्ण

	atomic_set(&vf_rep->अगरstate, (atomic_पढ़ो(&vf_rep->अगरstate) |
				      LIO_IFSTATE_RUNNING));

	netअगर_carrier_on(ndev);
	netअगर_start_queue(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक
lio_vf_rep_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा lio_vf_rep_desc *vf_rep = netdev_priv(ndev);
	काष्ठा lio_vf_rep_req rep_cfg;
	काष्ठा octeon_device *oct;
	पूर्णांक ret;

	oct = vf_rep->oct;

	स_रखो(&rep_cfg, 0, माप(rep_cfg));
	rep_cfg.req_type = LIO_VF_REP_REQ_STATE;
	rep_cfg.अगरidx = vf_rep->अगरidx;
	rep_cfg.rep_state.state = LIO_VF_REP_STATE_DOWN;

	ret = lio_vf_rep_send_soft_command(oct, &rep_cfg,
					   माप(rep_cfg), शून्य, 0);

	अगर (ret) अणु
		dev_err(&oct->pci_dev->dev,
			"VF_REP dev stop failed with err %d\n", ret);
		वापस -EIO;
	पूर्ण

	atomic_set(&vf_rep->अगरstate, (atomic_पढ़ो(&vf_rep->अगरstate) &
				      ~LIO_IFSTATE_RUNNING));

	netअगर_tx_disable(ndev);
	netअगर_carrier_off(ndev);

	वापस 0;
पूर्ण

अटल व्योम
lio_vf_rep_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	netअगर_trans_update(ndev);

	netअगर_wake_queue(ndev);
पूर्ण

अटल व्योम
lio_vf_rep_get_stats64(काष्ठा net_device *dev,
		       काष्ठा rtnl_link_stats64 *stats64)
अणु
	काष्ठा lio_vf_rep_desc *vf_rep = netdev_priv(dev);

	/* Swap tx and rx stats as VF rep is a चयन port */
	stats64->tx_packets = vf_rep->stats.rx_packets;
	stats64->tx_bytes   = vf_rep->stats.rx_bytes;
	stats64->tx_dropped = vf_rep->stats.rx_dropped;

	stats64->rx_packets = vf_rep->stats.tx_packets;
	stats64->rx_bytes   = vf_rep->stats.tx_bytes;
	stats64->rx_dropped = vf_rep->stats.tx_dropped;
पूर्ण

अटल पूर्णांक
lio_vf_rep_change_mtu(काष्ठा net_device *ndev, पूर्णांक new_mtu)
अणु
	काष्ठा lio_vf_rep_desc *vf_rep = netdev_priv(ndev);
	काष्ठा lio_vf_rep_req rep_cfg;
	काष्ठा octeon_device *oct;
	पूर्णांक ret;

	oct = vf_rep->oct;

	स_रखो(&rep_cfg, 0, माप(rep_cfg));
	rep_cfg.req_type = LIO_VF_REP_REQ_MTU;
	rep_cfg.अगरidx = vf_rep->अगरidx;
	rep_cfg.rep_mtu.mtu = cpu_to_be32(new_mtu);

	ret = lio_vf_rep_send_soft_command(oct, &rep_cfg,
					   माप(rep_cfg), शून्य, 0);
	अगर (ret) अणु
		dev_err(&oct->pci_dev->dev,
			"Change MTU failed with err %d\n", ret);
		वापस -EIO;
	पूर्ण

	ndev->mtu = new_mtu;

	वापस 0;
पूर्ण

अटल पूर्णांक
lio_vf_rep_phys_port_name(काष्ठा net_device *dev,
			  अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा lio_vf_rep_desc *vf_rep = netdev_priv(dev);
	काष्ठा octeon_device *oct = vf_rep->oct;
	पूर्णांक ret;

	ret = snम_लिखो(buf, len, "pf%dvf%d", oct->pf_num,
		       vf_rep->अगरidx - oct->pf_num * 64 - 1);
	अगर (ret >= len)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल काष्ठा net_device *
lio_vf_rep_get_ndev(काष्ठा octeon_device *oct, पूर्णांक अगरidx)
अणु
	पूर्णांक vf_id, max_vfs = CN23XX_MAX_VFS_PER_PF + 1;
	पूर्णांक vfid_mask = max_vfs - 1;

	अगर (अगरidx <= oct->pf_num * max_vfs ||
	    अगरidx >= oct->pf_num * max_vfs + max_vfs)
		वापस शून्य;

	/* अगरidx 1-63 क्रम PF0 VFs
	 * अगरidx 65-127 क्रम PF1 VFs
	 */
	vf_id = (अगरidx & vfid_mask) - 1;

	वापस oct->vf_rep_list.ndev[vf_id];
पूर्ण

अटल व्योम
lio_vf_rep_copy_packet(काष्ठा octeon_device *oct,
		       काष्ठा sk_buff *skb,
		       पूर्णांक len)
अणु
	अगर (likely(len > MIN_SKB_SIZE)) अणु
		काष्ठा octeon_skb_page_info *pg_info;
		अचिन्हित अक्षर *va;

		pg_info = ((काष्ठा octeon_skb_page_info *)(skb->cb));
		अगर (pg_info->page) अणु
			va = page_address(pg_info->page) +
				pg_info->page_offset;
			स_नकल(skb->data, va, MIN_SKB_SIZE);
			skb_put(skb, MIN_SKB_SIZE);
		पूर्ण

		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
				pg_info->page,
				pg_info->page_offset + MIN_SKB_SIZE,
				len - MIN_SKB_SIZE,
				LIO_RXBUFFER_SZ);
	पूर्ण अन्यथा अणु
		काष्ठा octeon_skb_page_info *pg_info =
			((काष्ठा octeon_skb_page_info *)(skb->cb));

		skb_copy_to_linear_data(skb, page_address(pg_info->page) +
					pg_info->page_offset, len);
		skb_put(skb, len);
		put_page(pg_info->page);
	पूर्ण
पूर्ण

अटल पूर्णांक
lio_vf_rep_pkt_recv(काष्ठा octeon_recv_info *recv_info, व्योम *buf)
अणु
	काष्ठा octeon_recv_pkt *recv_pkt = recv_info->recv_pkt;
	काष्ठा lio_vf_rep_desc *vf_rep;
	काष्ठा net_device *vf_ndev;
	काष्ठा octeon_device *oct;
	जोड़ octeon_rh *rh;
	काष्ठा sk_buff *skb;
	पूर्णांक i, अगरidx;

	oct = lio_get_device(recv_pkt->octeon_id);
	अगर (!oct)
		जाओ मुक्त_buffers;

	skb = recv_pkt->buffer_ptr[0];
	rh = &recv_pkt->rh;
	अगरidx = rh->r.ossp;

	vf_ndev = lio_vf_rep_get_ndev(oct, अगरidx);
	अगर (!vf_ndev)
		जाओ मुक्त_buffers;

	vf_rep = netdev_priv(vf_ndev);
	अगर (!(atomic_पढ़ो(&vf_rep->अगरstate) & LIO_IFSTATE_RUNNING) ||
	    recv_pkt->buffer_count > 1)
		जाओ मुक्त_buffers;

	skb->dev = vf_ndev;

	/* Multiple buffers are not used क्रम vf_rep packets.
	 * So just buffer_size[0] is valid.
	 */
	lio_vf_rep_copy_packet(oct, skb, recv_pkt->buffer_size[0]);

	skb_pull(skb, rh->r_dh.len * BYTES_PER_DHLEN_UNIT);
	skb->protocol = eth_type_trans(skb, skb->dev);
	skb->ip_summed = CHECKSUM_NONE;

	netअगर_rx(skb);

	octeon_मुक्त_recv_info(recv_info);

	वापस 0;

मुक्त_buffers:
	क्रम (i = 0; i < recv_pkt->buffer_count; i++)
		recv_buffer_मुक्त(recv_pkt->buffer_ptr[i]);

	octeon_मुक्त_recv_info(recv_info);

	वापस 0;
पूर्ण

अटल व्योम
lio_vf_rep_packet_sent_callback(काष्ठा octeon_device *oct,
				u32 status, व्योम *buf)
अणु
	काष्ठा octeon_soft_command *sc = (काष्ठा octeon_soft_command *)buf;
	काष्ठा sk_buff *skb = sc->ctxptr;
	काष्ठा net_device *ndev = skb->dev;
	u32 iq_no;

	dma_unmap_single(&oct->pci_dev->dev, sc->dmadptr,
			 sc->datasize, DMA_TO_DEVICE);
	dev_kमुक्त_skb_any(skb);
	iq_no = sc->iq_no;
	octeon_मुक्त_soft_command(oct, sc);

	अगर (octnet_iq_is_full(oct, iq_no))
		वापस;

	अगर (netअगर_queue_stopped(ndev))
		netअगर_wake_queue(ndev);
पूर्ण

अटल netdev_tx_t
lio_vf_rep_pkt_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा lio_vf_rep_desc *vf_rep = netdev_priv(ndev);
	काष्ठा net_device *parent_ndev = vf_rep->parent_ndev;
	काष्ठा octeon_device *oct = vf_rep->oct;
	काष्ठा octeon_instr_pki_ih3 *pki_ih3;
	काष्ठा octeon_soft_command *sc;
	काष्ठा lio *parent_lio;
	पूर्णांक status;

	parent_lio = GET_LIO(parent_ndev);

	अगर (!(atomic_पढ़ो(&vf_rep->अगरstate) & LIO_IFSTATE_RUNNING) ||
	    skb->len <= 0)
		जाओ xmit_failed;

	अगर (octnet_iq_is_full(vf_rep->oct, parent_lio->txq)) अणु
		dev_err(&oct->pci_dev->dev, "VF rep: Device IQ full\n");
		netअगर_stop_queue(ndev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	sc = (काष्ठा octeon_soft_command *)
		octeon_alloc_soft_command(oct, 0, 16, 0);
	अगर (!sc) अणु
		dev_err(&oct->pci_dev->dev, "VF rep: Soft command alloc failed\n");
		जाओ xmit_failed;
	पूर्ण

	/* Multiple buffers are not used क्रम vf_rep packets. */
	अगर (skb_shinfo(skb)->nr_frags != 0) अणु
		dev_err(&oct->pci_dev->dev, "VF rep: nr_frags != 0. Dropping packet\n");
		octeon_मुक्त_soft_command(oct, sc);
		जाओ xmit_failed;
	पूर्ण

	sc->dmadptr = dma_map_single(&oct->pci_dev->dev,
				     skb->data, skb->len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&oct->pci_dev->dev, sc->dmadptr)) अणु
		dev_err(&oct->pci_dev->dev, "VF rep: DMA mapping failed\n");
		octeon_मुक्त_soft_command(oct, sc);
		जाओ xmit_failed;
	पूर्ण

	sc->virtdptr = skb->data;
	sc->datasize = skb->len;
	sc->ctxptr = skb;
	sc->iq_no = parent_lio->txq;

	octeon_prepare_soft_command(oct, sc, OPCODE_NIC, OPCODE_NIC_VF_REP_PKT,
				    vf_rep->अगरidx, 0, 0);
	pki_ih3 = (काष्ठा octeon_instr_pki_ih3 *)&sc->cmd.cmd3.pki_ih3;
	pki_ih3->tagtype = ORDERED_TAG;

	sc->callback = lio_vf_rep_packet_sent_callback;
	sc->callback_arg = sc;

	status = octeon_send_soft_command(oct, sc);
	अगर (status == IQ_SEND_FAILED) अणु
		dma_unmap_single(&oct->pci_dev->dev, sc->dmadptr,
				 sc->datasize, DMA_TO_DEVICE);
		octeon_मुक्त_soft_command(oct, sc);
		जाओ xmit_failed;
	पूर्ण

	अगर (status == IQ_SEND_STOP)
		netअगर_stop_queue(ndev);

	netअगर_trans_update(ndev);

	वापस NETDEV_TX_OK;

xmit_failed:
	dev_kमुक्त_skb_any(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक lio_vf_get_port_parent_id(काष्ठा net_device *dev,
				     काष्ठा netdev_phys_item_id *ppid)
अणु
	काष्ठा lio_vf_rep_desc *vf_rep = netdev_priv(dev);
	काष्ठा net_device *parent_ndev = vf_rep->parent_ndev;
	काष्ठा lio *lio = GET_LIO(parent_ndev);

	ppid->id_len = ETH_ALEN;
	ether_addr_copy(ppid->id, (व्योम *)&lio->linfo.hw_addr + 2);

	वापस 0;
पूर्ण

अटल व्योम
lio_vf_rep_fetch_stats(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cavium_wk *wk = (काष्ठा cavium_wk *)work;
	काष्ठा lio_vf_rep_desc *vf_rep = wk->ctxptr;
	काष्ठा lio_vf_rep_stats stats;
	काष्ठा lio_vf_rep_req rep_cfg;
	काष्ठा octeon_device *oct;
	पूर्णांक ret;

	oct = vf_rep->oct;

	स_रखो(&rep_cfg, 0, माप(rep_cfg));
	rep_cfg.req_type = LIO_VF_REP_REQ_STATS;
	rep_cfg.अगरidx = vf_rep->अगरidx;

	ret = lio_vf_rep_send_soft_command(oct, &rep_cfg, माप(rep_cfg),
					   &stats, माप(stats));

	अगर (!ret) अणु
		octeon_swap_8B_data((u64 *)&stats, (माप(stats) >> 3));
		स_नकल(&vf_rep->stats, &stats, माप(stats));
	पूर्ण

	schedule_delayed_work(&vf_rep->stats_wk.work,
			      msecs_to_jअगरfies(LIO_VF_REP_STATS_POLL_TIME_MS));
पूर्ण

पूर्णांक
lio_vf_rep_create(काष्ठा octeon_device *oct)
अणु
	काष्ठा lio_vf_rep_desc *vf_rep;
	काष्ठा net_device *ndev;
	पूर्णांक i, num_vfs;

	अगर (oct->eचयन_mode != DEVLINK_ESWITCH_MODE_SWITCHDEV)
		वापस 0;

	अगर (!oct->sriov_info.sriov_enabled)
		वापस 0;

	num_vfs = oct->sriov_info.num_vfs_alloced;

	oct->vf_rep_list.num_vfs = 0;
	क्रम (i = 0; i < num_vfs; i++) अणु
		ndev = alloc_etherdev(माप(काष्ठा lio_vf_rep_desc));

		अगर (!ndev) अणु
			dev_err(&oct->pci_dev->dev,
				"VF rep device %d creation failed\n", i);
			जाओ cleanup;
		पूर्ण

		ndev->min_mtu = LIO_MIN_MTU_SIZE;
		ndev->max_mtu = LIO_MAX_MTU_SIZE;
		ndev->netdev_ops = &lio_vf_rep_ndev_ops;

		vf_rep = netdev_priv(ndev);
		स_रखो(vf_rep, 0, माप(*vf_rep));

		vf_rep->ndev = ndev;
		vf_rep->oct = oct;
		vf_rep->parent_ndev = oct->props[0].netdev;
		vf_rep->अगरidx = (oct->pf_num * 64) + i + 1;

		eth_hw_addr_अक्रमom(ndev);

		अगर (रेजिस्टर_netdev(ndev)) अणु
			dev_err(&oct->pci_dev->dev, "VF rep nerdev registration failed\n");

			मुक्त_netdev(ndev);
			जाओ cleanup;
		पूर्ण

		netअगर_carrier_off(ndev);

		INIT_DELAYED_WORK(&vf_rep->stats_wk.work,
				  lio_vf_rep_fetch_stats);
		vf_rep->stats_wk.ctxptr = (व्योम *)vf_rep;
		schedule_delayed_work(&vf_rep->stats_wk.work,
				      msecs_to_jअगरfies
				      (LIO_VF_REP_STATS_POLL_TIME_MS));
		oct->vf_rep_list.num_vfs++;
		oct->vf_rep_list.ndev[i] = ndev;
	पूर्ण

	अगर (octeon_रेजिस्टर_dispatch_fn(oct, OPCODE_NIC,
					OPCODE_NIC_VF_REP_PKT,
					lio_vf_rep_pkt_recv, oct)) अणु
		dev_err(&oct->pci_dev->dev, "VF rep Dispatch func registration failed\n");

		जाओ cleanup;
	पूर्ण

	वापस 0;

cleanup:
	क्रम (i = 0; i < oct->vf_rep_list.num_vfs; i++) अणु
		ndev = oct->vf_rep_list.ndev[i];
		oct->vf_rep_list.ndev[i] = शून्य;
		अगर (ndev) अणु
			vf_rep = netdev_priv(ndev);
			cancel_delayed_work_sync
				(&vf_rep->stats_wk.work);
			unरेजिस्टर_netdev(ndev);
			मुक्त_netdev(ndev);
		पूर्ण
	पूर्ण

	oct->vf_rep_list.num_vfs = 0;

	वापस -1;
पूर्ण

व्योम
lio_vf_rep_destroy(काष्ठा octeon_device *oct)
अणु
	काष्ठा lio_vf_rep_desc *vf_rep;
	काष्ठा net_device *ndev;
	पूर्णांक i;

	अगर (oct->eचयन_mode != DEVLINK_ESWITCH_MODE_SWITCHDEV)
		वापस;

	अगर (!oct->sriov_info.sriov_enabled)
		वापस;

	क्रम (i = 0; i < oct->vf_rep_list.num_vfs; i++) अणु
		ndev = oct->vf_rep_list.ndev[i];
		oct->vf_rep_list.ndev[i] = शून्य;
		अगर (ndev) अणु
			vf_rep = netdev_priv(ndev);
			cancel_delayed_work_sync
				(&vf_rep->stats_wk.work);
			netअगर_tx_disable(ndev);
			netअगर_carrier_off(ndev);

			unरेजिस्टर_netdev(ndev);
			मुक्त_netdev(ndev);
		पूर्ण
	पूर्ण

	oct->vf_rep_list.num_vfs = 0;
पूर्ण

अटल पूर्णांक
lio_vf_rep_netdev_event(काष्ठा notअगरier_block *nb,
			अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *ndev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा lio_vf_rep_desc *vf_rep;
	काष्ठा lio_vf_rep_req rep_cfg;
	काष्ठा octeon_device *oct;
	पूर्णांक ret;

	चयन (event) अणु
	हाल NETDEV_REGISTER:
	हाल NETDEV_CHANGENAME:
		अवरोध;

	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	अगर (ndev->netdev_ops != &lio_vf_rep_ndev_ops)
		वापस NOTIFY_DONE;

	vf_rep = netdev_priv(ndev);
	oct = vf_rep->oct;

	अगर (म_माप(ndev->name) > LIO_IF_NAME_SIZE) अणु
		dev_err(&oct->pci_dev->dev,
			"Device name change sync failed as the size is > %d\n",
			LIO_IF_NAME_SIZE);
		वापस NOTIFY_DONE;
	पूर्ण

	स_रखो(&rep_cfg, 0, माप(rep_cfg));
	rep_cfg.req_type = LIO_VF_REP_REQ_DEVNAME;
	rep_cfg.अगरidx = vf_rep->अगरidx;
	म_नकलन(rep_cfg.rep_name.name, ndev->name, LIO_IF_NAME_SIZE);

	ret = lio_vf_rep_send_soft_command(oct, &rep_cfg,
					   माप(rep_cfg), शून्य, 0);
	अगर (ret)
		dev_err(&oct->pci_dev->dev,
			"vf_rep netdev name change failed with err %d\n", ret);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block lio_vf_rep_netdev_notअगरier = अणु
	.notअगरier_call = lio_vf_rep_netdev_event,
पूर्ण;

पूर्णांक
lio_vf_rep_modinit(व्योम)
अणु
	अगर (रेजिस्टर_netdevice_notअगरier(&lio_vf_rep_netdev_notअगरier)) अणु
		pr_err("netdev notifier registration failed\n");
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

व्योम
lio_vf_rep_modनिकास(व्योम)
अणु
	अगर (unरेजिस्टर_netdevice_notअगरier(&lio_vf_rep_netdev_notअगरier))
		pr_err("netdev notifier unregister failed\n");
पूर्ण
