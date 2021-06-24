<शैली गुरु>
/*
 * Copyright(c) 2017 - 2020 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * This file contains HFI1 support क्रम VNIC functionality
 */

#समावेश <linux/पन.स>
#समावेश <linux/अगर_vlan.h>

#समावेश "vnic.h"
#समावेश "netdev.h"

#घोषणा HFI_TX_TIMEOUT_MS 1000

#घोषणा HFI1_VNIC_RCV_Q_SIZE   1024

#घोषणा HFI1_VNIC_UP 0

अटल DEFINE_SPINLOCK(vport_cntr_lock);

#घोषणा SUM_GRP_COUNTERS(stats, qstats, x_grp) करो अणु            \
		u64 *src64, *dst64;                            \
		क्रम (src64 = &qstats->x_grp.unicast,           \
			dst64 = &stats->x_grp.unicast;         \
			dst64 <= &stats->x_grp.s_1519_max;) अणु  \
			*dst64++ += *src64++;                  \
		पूर्ण                                              \
	पूर्ण जबतक (0)

#घोषणा VNIC_MASK (0xFF)
#घोषणा VNIC_ID(val) ((1ull << 24) | ((val) & VNIC_MASK))

/* hfi1_vnic_update_stats - update statistics */
अटल व्योम hfi1_vnic_update_stats(काष्ठा hfi1_vnic_vport_info *vinfo,
				   काष्ठा opa_vnic_stats *stats)
अणु
	काष्ठा net_device *netdev = vinfo->netdev;
	u8 i;

	/* add tx counters on dअगरferent queues */
	क्रम (i = 0; i < vinfo->num_tx_q; i++) अणु
		काष्ठा opa_vnic_stats *qstats = &vinfo->stats[i];
		काष्ठा rtnl_link_stats64 *qnstats = &vinfo->stats[i].netstats;

		stats->netstats.tx_fअगरo_errors += qnstats->tx_fअगरo_errors;
		stats->netstats.tx_carrier_errors += qnstats->tx_carrier_errors;
		stats->tx_drop_state += qstats->tx_drop_state;
		stats->tx_dlid_zero += qstats->tx_dlid_zero;

		SUM_GRP_COUNTERS(stats, qstats, tx_grp);
		stats->netstats.tx_packets += qnstats->tx_packets;
		stats->netstats.tx_bytes += qnstats->tx_bytes;
	पूर्ण

	/* add rx counters on dअगरferent queues */
	क्रम (i = 0; i < vinfo->num_rx_q; i++) अणु
		काष्ठा opa_vnic_stats *qstats = &vinfo->stats[i];
		काष्ठा rtnl_link_stats64 *qnstats = &vinfo->stats[i].netstats;

		stats->netstats.rx_fअगरo_errors += qnstats->rx_fअगरo_errors;
		stats->netstats.rx_nohandler += qnstats->rx_nohandler;
		stats->rx_drop_state += qstats->rx_drop_state;
		stats->rx_oversize += qstats->rx_oversize;
		stats->rx_runt += qstats->rx_runt;

		SUM_GRP_COUNTERS(stats, qstats, rx_grp);
		stats->netstats.rx_packets += qnstats->rx_packets;
		stats->netstats.rx_bytes += qnstats->rx_bytes;
	पूर्ण

	stats->netstats.tx_errors = stats->netstats.tx_fअगरo_errors +
				    stats->netstats.tx_carrier_errors +
				    stats->tx_drop_state + stats->tx_dlid_zero;
	stats->netstats.tx_dropped = stats->netstats.tx_errors;

	stats->netstats.rx_errors = stats->netstats.rx_fअगरo_errors +
				    stats->netstats.rx_nohandler +
				    stats->rx_drop_state + stats->rx_oversize +
				    stats->rx_runt;
	stats->netstats.rx_dropped = stats->netstats.rx_errors;

	netdev->stats.tx_packets = stats->netstats.tx_packets;
	netdev->stats.tx_bytes = stats->netstats.tx_bytes;
	netdev->stats.tx_fअगरo_errors = stats->netstats.tx_fअगरo_errors;
	netdev->stats.tx_carrier_errors = stats->netstats.tx_carrier_errors;
	netdev->stats.tx_errors = stats->netstats.tx_errors;
	netdev->stats.tx_dropped = stats->netstats.tx_dropped;

	netdev->stats.rx_packets = stats->netstats.rx_packets;
	netdev->stats.rx_bytes = stats->netstats.rx_bytes;
	netdev->stats.rx_fअगरo_errors = stats->netstats.rx_fअगरo_errors;
	netdev->stats.multicast = stats->rx_grp.mcastbcast;
	netdev->stats.rx_length_errors = stats->rx_oversize + stats->rx_runt;
	netdev->stats.rx_errors = stats->netstats.rx_errors;
	netdev->stats.rx_dropped = stats->netstats.rx_dropped;
पूर्ण

/* update_len_counters - update pkt's len histogram counters */
अटल अंतरभूत व्योम update_len_counters(काष्ठा opa_vnic_grp_stats *grp,
				       पूर्णांक len)
अणु
	/* account क्रम 4 byte FCS */
	अगर (len >= 1515)
		grp->s_1519_max++;
	अन्यथा अगर (len >= 1020)
		grp->s_1024_1518++;
	अन्यथा अगर (len >= 508)
		grp->s_512_1023++;
	अन्यथा अगर (len >= 252)
		grp->s_256_511++;
	अन्यथा अगर (len >= 124)
		grp->s_128_255++;
	अन्यथा अगर (len >= 61)
		grp->s_65_127++;
	अन्यथा
		grp->s_64++;
पूर्ण

/* hfi1_vnic_update_tx_counters - update transmit counters */
अटल व्योम hfi1_vnic_update_tx_counters(काष्ठा hfi1_vnic_vport_info *vinfo,
					 u8 q_idx, काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	काष्ठा ethhdr *mac_hdr = (काष्ठा ethhdr *)skb_mac_header(skb);
	काष्ठा opa_vnic_stats *stats = &vinfo->stats[q_idx];
	काष्ठा opa_vnic_grp_stats *tx_grp = &stats->tx_grp;
	u16 vlan_tci;

	stats->netstats.tx_packets++;
	stats->netstats.tx_bytes += skb->len + ETH_FCS_LEN;

	update_len_counters(tx_grp, skb->len);

	/* rest of the counts are क्रम good packets only */
	अगर (unlikely(err))
		वापस;

	अगर (is_multicast_ether_addr(mac_hdr->h_dest))
		tx_grp->mcastbcast++;
	अन्यथा
		tx_grp->unicast++;

	अगर (!__vlan_get_tag(skb, &vlan_tci))
		tx_grp->vlan++;
	अन्यथा
		tx_grp->untagged++;
पूर्ण

/* hfi1_vnic_update_rx_counters - update receive counters */
अटल व्योम hfi1_vnic_update_rx_counters(काष्ठा hfi1_vnic_vport_info *vinfo,
					 u8 q_idx, काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	काष्ठा ethhdr *mac_hdr = (काष्ठा ethhdr *)skb->data;
	काष्ठा opa_vnic_stats *stats = &vinfo->stats[q_idx];
	काष्ठा opa_vnic_grp_stats *rx_grp = &stats->rx_grp;
	u16 vlan_tci;

	stats->netstats.rx_packets++;
	stats->netstats.rx_bytes += skb->len + ETH_FCS_LEN;

	update_len_counters(rx_grp, skb->len);

	/* rest of the counts are क्रम good packets only */
	अगर (unlikely(err))
		वापस;

	अगर (is_multicast_ether_addr(mac_hdr->h_dest))
		rx_grp->mcastbcast++;
	अन्यथा
		rx_grp->unicast++;

	अगर (!__vlan_get_tag(skb, &vlan_tci))
		rx_grp->vlan++;
	अन्यथा
		rx_grp->untagged++;
पूर्ण

/* This function is overloaded क्रम opa_vnic specअगरic implementation */
अटल व्योम hfi1_vnic_get_stats64(काष्ठा net_device *netdev,
				  काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा opa_vnic_stats *vstats = (काष्ठा opa_vnic_stats *)stats;
	काष्ठा hfi1_vnic_vport_info *vinfo = opa_vnic_dev_priv(netdev);

	hfi1_vnic_update_stats(vinfo, vstats);
पूर्ण

अटल u64 create_bypass_pbc(u32 vl, u32 dw_len)
अणु
	u64 pbc;

	pbc = ((u64)PBC_IHCRC_NONE << PBC_INSERT_HCRC_SHIFT)
		| PBC_INSERT_BYPASS_ICRC | PBC_CREDIT_RETURN
		| PBC_PACKET_BYPASS
		| ((vl & PBC_VL_MASK) << PBC_VL_SHIFT)
		| (dw_len & PBC_LENGTH_DWS_MASK) << PBC_LENGTH_DWS_SHIFT;

	वापस pbc;
पूर्ण

/* hfi1_vnic_maybe_stop_tx - stop tx queue अगर required */
अटल व्योम hfi1_vnic_maybe_stop_tx(काष्ठा hfi1_vnic_vport_info *vinfo,
				    u8 q_idx)
अणु
	netअगर_stop_subqueue(vinfo->netdev, q_idx);
	अगर (!hfi1_vnic_sdma_ग_लिखो_avail(vinfo, q_idx))
		वापस;

	netअगर_start_subqueue(vinfo->netdev, q_idx);
पूर्ण

अटल netdev_tx_t hfi1_netdev_start_xmit(काष्ठा sk_buff *skb,
					  काष्ठा net_device *netdev)
अणु
	काष्ठा hfi1_vnic_vport_info *vinfo = opa_vnic_dev_priv(netdev);
	u8 pad_len, q_idx = skb->queue_mapping;
	काष्ठा hfi1_devdata *dd = vinfo->dd;
	काष्ठा opa_vnic_skb_mdata *mdata;
	u32 pkt_len, total_len;
	पूर्णांक err = -EINVAL;
	u64 pbc;

	v_dbg("xmit: queue %d skb len %d\n", q_idx, skb->len);
	अगर (unlikely(!netअगर_oper_up(netdev))) अणु
		vinfo->stats[q_idx].tx_drop_state++;
		जाओ tx_finish;
	पूर्ण

	/* take out meta data */
	mdata = (काष्ठा opa_vnic_skb_mdata *)skb->data;
	skb_pull(skb, माप(*mdata));
	अगर (unlikely(mdata->flags & OPA_VNIC_SKB_MDATA_ENCAP_ERR)) अणु
		vinfo->stats[q_idx].tx_dlid_zero++;
		जाओ tx_finish;
	पूर्ण

	/* add tail padding (क्रम 8 bytes size alignment) and icrc */
	pad_len = -(skb->len + OPA_VNIC_ICRC_TAIL_LEN) & 0x7;
	pad_len += OPA_VNIC_ICRC_TAIL_LEN;

	/*
	 * pkt_len is how much data we have to ग_लिखो, includes header and data.
	 * total_len is length of the packet in Dwords plus the PBC should not
	 * include the CRC.
	 */
	pkt_len = (skb->len + pad_len) >> 2;
	total_len = pkt_len + 2; /* PBC + packet */

	pbc = create_bypass_pbc(mdata->vl, total_len);

	skb_get(skb);
	v_dbg("pbc 0x%016llX len %d pad_len %d\n", pbc, skb->len, pad_len);
	err = dd->process_vnic_dma_send(dd, q_idx, vinfo, skb, pbc, pad_len);
	अगर (unlikely(err)) अणु
		अगर (err == -ENOMEM)
			vinfo->stats[q_idx].netstats.tx_fअगरo_errors++;
		अन्यथा अगर (err != -EBUSY)
			vinfo->stats[q_idx].netstats.tx_carrier_errors++;
	पूर्ण
	/* हटाओ the header beक्रमe updating tx counters */
	skb_pull(skb, OPA_VNIC_HDR_LEN);

	अगर (unlikely(err == -EBUSY)) अणु
		hfi1_vnic_maybe_stop_tx(vinfo, q_idx);
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_BUSY;
	पूर्ण

tx_finish:
	/* update tx counters */
	hfi1_vnic_update_tx_counters(vinfo, q_idx, skb, err);
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल u16 hfi1_vnic_select_queue(काष्ठा net_device *netdev,
				  काष्ठा sk_buff *skb,
				  काष्ठा net_device *sb_dev)
अणु
	काष्ठा hfi1_vnic_vport_info *vinfo = opa_vnic_dev_priv(netdev);
	काष्ठा opa_vnic_skb_mdata *mdata;
	काष्ठा sdma_engine *sde;

	mdata = (काष्ठा opa_vnic_skb_mdata *)skb->data;
	sde = sdma_select_engine_vl(vinfo->dd, mdata->entropy, mdata->vl);
	वापस sde->this_idx;
पूर्ण

/* hfi1_vnic_decap_skb - strip OPA header from the skb (ethernet) packet */
अटल अंतरभूत पूर्णांक hfi1_vnic_decap_skb(काष्ठा hfi1_vnic_rx_queue *rxq,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा hfi1_vnic_vport_info *vinfo = rxq->vinfo;
	पूर्णांक max_len = vinfo->netdev->mtu + VLAN_ETH_HLEN;
	पूर्णांक rc = -EFAULT;

	skb_pull(skb, OPA_VNIC_HDR_LEN);

	/* Validate Packet length */
	अगर (unlikely(skb->len > max_len))
		vinfo->stats[rxq->idx].rx_oversize++;
	अन्यथा अगर (unlikely(skb->len < ETH_ZLEN))
		vinfo->stats[rxq->idx].rx_runt++;
	अन्यथा
		rc = 0;
	वापस rc;
पूर्ण

अटल काष्ठा hfi1_vnic_vport_info *get_vnic_port(काष्ठा hfi1_devdata *dd,
						  पूर्णांक vesw_id)
अणु
	पूर्णांक vnic_id = VNIC_ID(vesw_id);

	वापस hfi1_netdev_get_data(dd, vnic_id);
पूर्ण

अटल काष्ठा hfi1_vnic_vport_info *get_first_vnic_port(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_vnic_vport_info *vinfo;
	पूर्णांक next_id = VNIC_ID(0);

	vinfo = hfi1_netdev_get_first_data(dd, &next_id);

	अगर (next_id > VNIC_ID(VNIC_MASK))
		वापस शून्य;

	वापस vinfo;
पूर्ण

व्योम hfi1_vnic_bypass_rcv(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_devdata *dd = packet->rcd->dd;
	काष्ठा hfi1_vnic_vport_info *vinfo = शून्य;
	काष्ठा hfi1_vnic_rx_queue *rxq;
	काष्ठा sk_buff *skb;
	पूर्णांक l4_type, vesw_id = -1, rc;
	u8 q_idx;
	अचिन्हित अक्षर *pad_info;

	l4_type = hfi1_16B_get_l4(packet->ebuf);
	अगर (likely(l4_type == OPA_16B_L4_ETHR)) अणु
		vesw_id = HFI1_VNIC_GET_VESWID(packet->ebuf);
		vinfo = get_vnic_port(dd, vesw_id);

		/*
		 * In हाल of invalid vesw id, count the error on
		 * the first available vport.
		 */
		अगर (unlikely(!vinfo)) अणु
			काष्ठा hfi1_vnic_vport_info *vinfo_पंचांगp;

			vinfo_पंचांगp = get_first_vnic_port(dd);
			अगर (vinfo_पंचांगp) अणु
				spin_lock(&vport_cntr_lock);
				vinfo_पंचांगp->stats[0].netstats.rx_nohandler++;
				spin_unlock(&vport_cntr_lock);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (unlikely(!vinfo)) अणु
		dd_dev_warn(dd, "vnic rcv err: l4 %d vesw id %d ctx %d\n",
			    l4_type, vesw_id, packet->rcd->ctxt);
		वापस;
	पूर्ण

	q_idx = packet->rcd->vnic_q_idx;
	rxq = &vinfo->rxq[q_idx];
	अगर (unlikely(!netअगर_oper_up(vinfo->netdev))) अणु
		vinfo->stats[q_idx].rx_drop_state++;
		वापस;
	पूर्ण

	skb = netdev_alloc_skb(vinfo->netdev, packet->tlen);
	अगर (unlikely(!skb)) अणु
		vinfo->stats[q_idx].netstats.rx_fअगरo_errors++;
		वापस;
	पूर्ण

	स_नकल(skb->data, packet->ebuf, packet->tlen);
	skb_put(skb, packet->tlen);

	pad_info = skb->data + skb->len - 1;
	skb_trim(skb, (skb->len - OPA_VNIC_ICRC_TAIL_LEN -
		       ((*pad_info) & 0x7)));

	rc = hfi1_vnic_decap_skb(rxq, skb);

	/* update rx counters */
	hfi1_vnic_update_rx_counters(vinfo, rxq->idx, skb, rc);
	अगर (unlikely(rc)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	skb_checksum_none_निश्चित(skb);
	skb->protocol = eth_type_trans(skb, rxq->netdev);

	napi_gro_receive(&rxq->napi, skb);
पूर्ण

अटल पूर्णांक hfi1_vnic_up(काष्ठा hfi1_vnic_vport_info *vinfo)
अणु
	काष्ठा hfi1_devdata *dd = vinfo->dd;
	काष्ठा net_device *netdev = vinfo->netdev;
	पूर्णांक rc;

	/* ensure भव eth चयन id is valid */
	अगर (!vinfo->vesw_id)
		वापस -EINVAL;

	rc = hfi1_netdev_add_data(dd, VNIC_ID(vinfo->vesw_id), vinfo);
	अगर (rc < 0)
		वापस rc;

	rc = hfi1_netdev_rx_init(dd);
	अगर (rc)
		जाओ err_हटाओ;

	netअगर_carrier_on(netdev);
	netअगर_tx_start_all_queues(netdev);
	set_bit(HFI1_VNIC_UP, &vinfo->flags);

	वापस 0;

err_हटाओ:
	hfi1_netdev_हटाओ_data(dd, VNIC_ID(vinfo->vesw_id));
	वापस rc;
पूर्ण

अटल व्योम hfi1_vnic_करोwn(काष्ठा hfi1_vnic_vport_info *vinfo)
अणु
	काष्ठा hfi1_devdata *dd = vinfo->dd;

	clear_bit(HFI1_VNIC_UP, &vinfo->flags);
	netअगर_carrier_off(vinfo->netdev);
	netअगर_tx_disable(vinfo->netdev);
	hfi1_netdev_हटाओ_data(dd, VNIC_ID(vinfo->vesw_id));

	hfi1_netdev_rx_destroy(dd);
पूर्ण

अटल पूर्णांक hfi1_netdev_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा hfi1_vnic_vport_info *vinfo = opa_vnic_dev_priv(netdev);
	पूर्णांक rc;

	mutex_lock(&vinfo->lock);
	rc = hfi1_vnic_up(vinfo);
	mutex_unlock(&vinfo->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक hfi1_netdev_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा hfi1_vnic_vport_info *vinfo = opa_vnic_dev_priv(netdev);

	mutex_lock(&vinfo->lock);
	अगर (test_bit(HFI1_VNIC_UP, &vinfo->flags))
		hfi1_vnic_करोwn(vinfo);
	mutex_unlock(&vinfo->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक hfi1_vnic_init(काष्ठा hfi1_vnic_vport_info *vinfo)
अणु
	काष्ठा hfi1_devdata *dd = vinfo->dd;
	पूर्णांक rc = 0;

	mutex_lock(&hfi1_mutex);
	अगर (!dd->vnic_num_vports) अणु
		rc = hfi1_vnic_txreq_init(dd);
		अगर (rc)
			जाओ txreq_fail;
	पूर्ण

	rc = hfi1_netdev_rx_init(dd);
	अगर (rc) अणु
		dd_dev_err(dd, "Unable to initialize netdev contexts\n");
		जाओ alloc_fail;
	पूर्ण

	hfi1_init_vnic_rsm(dd);

	dd->vnic_num_vports++;
	hfi1_vnic_sdma_init(vinfo);

alloc_fail:
	अगर (!dd->vnic_num_vports)
		hfi1_vnic_txreq_deinit(dd);
txreq_fail:
	mutex_unlock(&hfi1_mutex);
	वापस rc;
पूर्ण

अटल व्योम hfi1_vnic_deinit(काष्ठा hfi1_vnic_vport_info *vinfo)
अणु
	काष्ठा hfi1_devdata *dd = vinfo->dd;

	mutex_lock(&hfi1_mutex);
	अगर (--dd->vnic_num_vports == 0) अणु
		hfi1_deinit_vnic_rsm(dd);
		hfi1_vnic_txreq_deinit(dd);
	पूर्ण
	mutex_unlock(&hfi1_mutex);
	hfi1_netdev_rx_destroy(dd);
पूर्ण

अटल व्योम hfi1_vnic_set_vesw_id(काष्ठा net_device *netdev, पूर्णांक id)
अणु
	काष्ठा hfi1_vnic_vport_info *vinfo = opa_vnic_dev_priv(netdev);
	bool reखोलो = false;

	/*
	 * If vesw_id is being changed, and अगर the vnic port is up,
	 * reset the vnic port to ensure new vesw_id माला_लो picked up
	 */
	अगर (id != vinfo->vesw_id) अणु
		mutex_lock(&vinfo->lock);
		अगर (test_bit(HFI1_VNIC_UP, &vinfo->flags)) अणु
			hfi1_vnic_करोwn(vinfo);
			reखोलो = true;
		पूर्ण

		vinfo->vesw_id = id;
		अगर (reखोलो)
			hfi1_vnic_up(vinfo);

		mutex_unlock(&vinfo->lock);
	पूर्ण
पूर्ण

/* netdev ops */
अटल स्थिर काष्ठा net_device_ops hfi1_netdev_ops = अणु
	.nकरो_खोलो = hfi1_netdev_खोलो,
	.nकरो_stop = hfi1_netdev_बंद,
	.nकरो_start_xmit = hfi1_netdev_start_xmit,
	.nकरो_select_queue = hfi1_vnic_select_queue,
	.nकरो_get_stats64 = hfi1_vnic_get_stats64,
पूर्ण;

अटल व्योम hfi1_vnic_मुक्त_rn(काष्ठा net_device *netdev)
अणु
	काष्ठा hfi1_vnic_vport_info *vinfo = opa_vnic_dev_priv(netdev);

	hfi1_vnic_deinit(vinfo);
	mutex_destroy(&vinfo->lock);
	मुक्त_netdev(netdev);
पूर्ण

काष्ठा net_device *hfi1_vnic_alloc_rn(काष्ठा ib_device *device,
				      u32 port_num,
				      क्रमागत rdma_netdev_t type,
				      स्थिर अक्षर *name,
				      अचिन्हित अक्षर name_assign_type,
				      व्योम (*setup)(काष्ठा net_device *))
अणु
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(device);
	काष्ठा hfi1_vnic_vport_info *vinfo;
	काष्ठा net_device *netdev;
	काष्ठा rdma_netdev *rn;
	पूर्णांक i, size, rc;

	अगर (!dd->num_netdev_contexts)
		वापस ERR_PTR(-ENOMEM);

	अगर (!port_num || (port_num > dd->num_pports))
		वापस ERR_PTR(-EINVAL);

	अगर (type != RDMA_NETDEV_OPA_VNIC)
		वापस ERR_PTR(-EOPNOTSUPP);

	size = माप(काष्ठा opa_vnic_rdma_netdev) + माप(*vinfo);
	netdev = alloc_netdev_mqs(size, name, name_assign_type, setup,
				  chip_sdma_engines(dd),
				  dd->num_netdev_contexts);
	अगर (!netdev)
		वापस ERR_PTR(-ENOMEM);

	rn = netdev_priv(netdev);
	vinfo = opa_vnic_dev_priv(netdev);
	vinfo->dd = dd;
	vinfo->num_tx_q = chip_sdma_engines(dd);
	vinfo->num_rx_q = dd->num_netdev_contexts;
	vinfo->netdev = netdev;
	rn->मुक्त_rdma_netdev = hfi1_vnic_मुक्त_rn;
	rn->set_id = hfi1_vnic_set_vesw_id;

	netdev->features = NETIF_F_HIGHDMA | NETIF_F_SG;
	netdev->hw_features = netdev->features;
	netdev->vlan_features = netdev->features;
	netdev->watchकरोg_समयo = msecs_to_jअगरfies(HFI_TX_TIMEOUT_MS);
	netdev->netdev_ops = &hfi1_netdev_ops;
	mutex_init(&vinfo->lock);

	क्रम (i = 0; i < vinfo->num_rx_q; i++) अणु
		काष्ठा hfi1_vnic_rx_queue *rxq = &vinfo->rxq[i];

		rxq->idx = i;
		rxq->vinfo = vinfo;
		rxq->netdev = netdev;
	पूर्ण

	rc = hfi1_vnic_init(vinfo);
	अगर (rc)
		जाओ init_fail;

	वापस netdev;
init_fail:
	mutex_destroy(&vinfo->lock);
	मुक्त_netdev(netdev);
	वापस ERR_PTR(rc);
पूर्ण
