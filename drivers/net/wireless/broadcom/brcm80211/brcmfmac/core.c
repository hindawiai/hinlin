<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/inetdevice.h>
#समावेश <net/cfg80211.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/addrconf.h>
#समावेश <net/ieee80211_radiotap.h>
#समावेश <net/ipv6.h>
#समावेश <brcmu_utils.h>
#समावेश <brcmu_wअगरi.h>

#समावेश "core.h"
#समावेश "bus.h"
#समावेश "debug.h"
#समावेश "fwil_types.h"
#समावेश "p2p.h"
#समावेश "pno.h"
#समावेश "cfg80211.h"
#समावेश "fwil.h"
#समावेश "feature.h"
#समावेश "proto.h"
#समावेश "pcie.h"
#समावेश "common.h"

#घोषणा MAX_WAIT_FOR_8021X_TX			msecs_to_jअगरfies(950)

#घोषणा BRCMF_BSSIDX_INVALID			-1

#घोषणा	RXS_PBPRES				BIT(2)

#घोषणा	D11_PHY_HDR_LEN				6

काष्ठा d11rxhdr_le अणु
	__le16 RxFrameSize;
	u16 PAD;
	__le16 PhyRxStatus_0;
	__le16 PhyRxStatus_1;
	__le16 PhyRxStatus_2;
	__le16 PhyRxStatus_3;
	__le16 PhyRxStatus_4;
	__le16 PhyRxStatus_5;
	__le16 RxStatus1;
	__le16 RxStatus2;
	__le16 RxTSFTime;
	__le16 RxChan;
	u8 unknown[12];
पूर्ण __packed;

काष्ठा wlc_d11rxhdr अणु
	काष्ठा d11rxhdr_le rxhdr;
	__le32 tsf_l;
	s8 rssi;
	s8 rxpwr0;
	s8 rxpwr1;
	s8 करो_rssi_ma;
	s8 rxpwr[4];
पूर्ण __packed;

अक्षर *brcmf_अगरname(काष्ठा brcmf_अगर *अगरp)
अणु
	अगर (!अगरp)
		वापस "<if_null>";

	अगर (अगरp->ndev)
		वापस अगरp->ndev->name;

	वापस "<if_none>";
पूर्ण

काष्ठा brcmf_अगर *brcmf_get_अगरp(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx)
अणु
	काष्ठा brcmf_अगर *अगरp;
	s32 bsscfgidx;

	अगर (अगरidx < 0 || अगरidx >= BRCMF_MAX_IFS) अणु
		bphy_err(drvr, "ifidx %d out of range\n", अगरidx);
		वापस शून्य;
	पूर्ण

	अगरp = शून्य;
	bsscfgidx = drvr->अगर2bss[अगरidx];
	अगर (bsscfgidx >= 0)
		अगरp = drvr->अगरlist[bsscfgidx];

	वापस अगरp;
पूर्ण

व्योम brcmf_configure_arp_nd_offload(काष्ठा brcmf_अगर *अगरp, bool enable)
अणु
	s32 err;
	u32 mode;

	अगर (enable)
		mode = BRCMF_ARP_OL_AGENT | BRCMF_ARP_OL_PEER_AUTO_REPLY;
	अन्यथा
		mode = 0;

	/* Try to set and enable ARP offload feature, this may fail, then it  */
	/* is simply not supported and err 0 will be वापसed                 */
	err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "arp_ol", mode);
	अगर (err) अणु
		brcmf_dbg(TRACE, "failed to set ARP offload mode to 0x%x, err = %d\n",
			  mode, err);
	पूर्ण अन्यथा अणु
		err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "arpoe", enable);
		अगर (err) अणु
			brcmf_dbg(TRACE, "failed to configure (%d) ARP offload err = %d\n",
				  enable, err);
		पूर्ण अन्यथा अणु
			brcmf_dbg(TRACE, "successfully configured (%d) ARP offload to 0x%x\n",
				  enable, mode);
		पूर्ण
	पूर्ण

	err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "ndoe", enable);
	अगर (err) अणु
		brcmf_dbg(TRACE, "failed to configure (%d) ND offload err = %d\n",
			  enable, err);
	पूर्ण अन्यथा अणु
		brcmf_dbg(TRACE, "successfully configured (%d) ND offload to 0x%x\n",
			  enable, mode);
	पूर्ण
पूर्ण

अटल व्योम _brcmf_set_multicast_list(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा brcmf_अगर *अगरp = container_of(work, काष्ठा brcmf_अगर,
					    multicast_work);
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा net_device *ndev;
	काष्ठा netdev_hw_addr *ha;
	u32 cmd_value, cnt;
	__le32 cnt_le;
	अक्षर *buf, *bufp;
	u32 buflen;
	s32 err;

	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d\n", अगरp->bsscfgidx);

	ndev = अगरp->ndev;

	/* Determine initial value of allmulti flag */
	cmd_value = (ndev->flags & IFF_ALLMULTI) ? true : false;

	/* Send करोwn the multicast list first. */
	cnt = netdev_mc_count(ndev);
	buflen = माप(cnt) + (cnt * ETH_ALEN);
	buf = kदो_स्मृति(buflen, GFP_KERNEL);
	अगर (!buf)
		वापस;
	bufp = buf;

	cnt_le = cpu_to_le32(cnt);
	स_नकल(bufp, &cnt_le, माप(cnt_le));
	bufp += माप(cnt_le);

	netdev_क्रम_each_mc_addr(ha, ndev) अणु
		अगर (!cnt)
			अवरोध;
		स_नकल(bufp, ha->addr, ETH_ALEN);
		bufp += ETH_ALEN;
		cnt--;
	पूर्ण

	err = brcmf_fil_iovar_data_set(अगरp, "mcast_list", buf, buflen);
	अगर (err < 0) अणु
		bphy_err(drvr, "Setting mcast_list failed, %d\n", err);
		cmd_value = cnt ? true : cmd_value;
	पूर्ण

	kमुक्त(buf);

	/*
	 * Now send the allmulti setting.  This is based on the setting in the
	 * net_device flags, but might be modअगरied above to be turned on अगर we
	 * were trying to set some addresses and करोngle rejected it...
	 */
	err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "allmulti", cmd_value);
	अगर (err < 0)
		bphy_err(drvr, "Setting allmulti failed, %d\n", err);

	/*Finally, pick up the PROMISC flag */
	cmd_value = (ndev->flags & IFF_PROMISC) ? true : false;
	err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_PROMISC, cmd_value);
	अगर (err < 0)
		bphy_err(drvr, "Setting BRCMF_C_SET_PROMISC failed, %d\n",
			 err);
	brcmf_configure_arp_nd_offload(अगरp, !cmd_value);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम _brcmf_update_ndtable(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा brcmf_अगर *अगरp = container_of(work, काष्ठा brcmf_अगर,
					    nकरोffload_work);
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	पूर्णांक i, ret;

	/* clear the table in firmware */
	ret = brcmf_fil_iovar_data_set(अगरp, "nd_hostip_clear", शून्य, 0);
	अगर (ret) अणु
		brcmf_dbg(TRACE, "fail to clear nd ip table err:%d\n", ret);
		वापस;
	पूर्ण

	क्रम (i = 0; i < अगरp->ipv6addr_idx; i++) अणु
		ret = brcmf_fil_iovar_data_set(अगरp, "nd_hostip",
					       &अगरp->ipv6_addr_tbl[i],
					       माप(काष्ठा in6_addr));
		अगर (ret)
			bphy_err(drvr, "add nd ip err %d\n", ret);
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम _brcmf_update_ndtable(काष्ठा work_काष्ठा *work)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक brcmf_netdev_set_mac_address(काष्ठा net_device *ndev, व्योम *addr)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा sockaddr *sa = (काष्ठा sockaddr *)addr;
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	पूर्णांक err;

	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d\n", अगरp->bsscfgidx);

	err = brcmf_fil_iovar_data_set(अगरp, "cur_etheraddr", sa->sa_data,
				       ETH_ALEN);
	अगर (err < 0) अणु
		bphy_err(drvr, "Setting cur_etheraddr failed, %d\n", err);
	पूर्ण अन्यथा अणु
		brcmf_dbg(TRACE, "updated to %pM\n", sa->sa_data);
		स_नकल(अगरp->mac_addr, sa->sa_data, ETH_ALEN);
		स_नकल(अगरp->ndev->dev_addr, अगरp->mac_addr, ETH_ALEN);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम brcmf_netdev_set_multicast_list(काष्ठा net_device *ndev)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);

	schedule_work(&अगरp->multicast_work);
पूर्ण

/**
 * brcmf_skb_is_iapp - checks अगर skb is an IAPP packet
 *
 * @skb: skb to check
 */
अटल bool brcmf_skb_is_iapp(काष्ठा sk_buff *skb)
अणु
	अटल स्थिर u8 iapp_l2_update_packet[6] __aligned(2) = अणु
		0x00, 0x01, 0xaf, 0x81, 0x01, 0x00,
	पूर्ण;
	अचिन्हित अक्षर *eth_data;
#अगर !defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
	स्थिर u16 *a, *b;
#पूर्ण_अगर

	अगर (skb->len - skb->mac_len != 6 ||
	    !is_multicast_ether_addr(eth_hdr(skb)->h_dest))
		वापस false;

	eth_data = skb_mac_header(skb) + ETH_HLEN;
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
	वापस !(((*(स्थिर u32 *)eth_data) ^ (*(स्थिर u32 *)iapp_l2_update_packet)) |
		 ((*(स्थिर u16 *)(eth_data + 4)) ^ (*(स्थिर u16 *)(iapp_l2_update_packet + 4))));
#अन्यथा
	a = (स्थिर u16 *)eth_data;
	b = (स्थिर u16 *)iapp_l2_update_packet;

	वापस !((a[0] ^ b[0]) | (a[1] ^ b[1]) | (a[2] ^ b[2]));
#पूर्ण_अगर
पूर्ण

अटल netdev_tx_t brcmf_netdev_start_xmit(काष्ठा sk_buff *skb,
					   काष्ठा net_device *ndev)
अणु
	पूर्णांक ret;
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा ethhdr *eh;
	पूर्णांक head_delta;

	brcmf_dbg(DATA, "Enter, bsscfgidx=%d\n", अगरp->bsscfgidx);

	/* Can the device send data? */
	अगर (drvr->bus_अगर->state != BRCMF_BUS_UP) अणु
		bphy_err(drvr, "xmit rejected state=%d\n", drvr->bus_अगर->state);
		netअगर_stop_queue(ndev);
		dev_kमुक्त_skb(skb);
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	/* Some recent Broadcom's firmwares disassociate STA when they receive
	 * an 802.11f ADD frame. This behavior can lead to a local DoS security
	 * issue. Attacker may trigger disassociation of any STA by sending a
	 * proper Ethernet frame to the wireless पूर्णांकerface.
	 *
	 * Moreover this feature may अवरोध AP पूर्णांकerfaces in some specअगरic
	 * setups. This applies e.g. to the bridge with hairpin mode enabled and
	 * IFLA_BRPORT_MCAST_TO_UCAST set. IAPP packet generated by a firmware
	 * will get passed back to the wireless पूर्णांकerface and cause immediate
	 * disassociation of a just-connected STA.
	 */
	अगर (!drvr->settings->iapp && brcmf_skb_is_iapp(skb)) अणु
		dev_kमुक्त_skb(skb);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	/* Make sure there's enough ग_लिखोable headroom */
	अगर (skb_headroom(skb) < drvr->hdrlen || skb_header_cloned(skb)) अणु
		head_delta = max_t(पूर्णांक, drvr->hdrlen - skb_headroom(skb), 0);

		brcmf_dbg(INFO, "%s: insufficient headroom (%d)\n",
			  brcmf_अगरname(अगरp), head_delta);
		atomic_inc(&drvr->bus_अगर->stats.pktcowed);
		ret = pskb_expand_head(skb, ALIGN(head_delta, NET_SKB_PAD), 0,
				       GFP_ATOMIC);
		अगर (ret < 0) अणु
			bphy_err(drvr, "%s: failed to expand headroom\n",
				 brcmf_अगरname(अगरp));
			atomic_inc(&drvr->bus_अगर->stats.pktcow_failed);
			जाओ करोne;
		पूर्ण
	पूर्ण

	/* validate length क्रम ether packet */
	अगर (skb->len < माप(*eh)) अणु
		ret = -EINVAL;
		dev_kमुक्त_skb(skb);
		जाओ करोne;
	पूर्ण

	eh = (काष्ठा ethhdr *)(skb->data);

	अगर (eh->h_proto == htons(ETH_P_PAE))
		atomic_inc(&अगरp->pend_8021x_cnt);

	/* determine the priority */
	अगर ((skb->priority == 0) || (skb->priority > 7))
		skb->priority = cfg80211_classअगरy8021d(skb, शून्य);

	/* set pacing shअगरt क्रम packet aggregation */
	sk_pacing_shअगरt_update(skb->sk, 8);

	ret = brcmf_proto_tx_queue_data(drvr, अगरp->अगरidx, skb);
	अगर (ret < 0)
		brcmf_txfinalize(अगरp, skb, false);

करोne:
	अगर (ret) अणु
		ndev->stats.tx_dropped++;
	पूर्ण अन्यथा अणु
		ndev->stats.tx_packets++;
		ndev->stats.tx_bytes += skb->len;
	पूर्ण

	/* Return ok: we always eat the packet */
	वापस NETDEV_TX_OK;
पूर्ण

व्योम brcmf_txflowblock_अगर(काष्ठा brcmf_अगर *अगरp,
			  क्रमागत brcmf_netअगर_stop_reason reason, bool state)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!अगरp || !अगरp->ndev)
		वापस;

	brcmf_dbg(TRACE, "enter: bsscfgidx=%d stop=0x%X reason=%d state=%d\n",
		  अगरp->bsscfgidx, अगरp->netअगर_stop, reason, state);

	spin_lock_irqsave(&अगरp->netअगर_stop_lock, flags);
	अगर (state) अणु
		अगर (!अगरp->netअगर_stop)
			netअगर_stop_queue(अगरp->ndev);
		अगरp->netअगर_stop |= reason;
	पूर्ण अन्यथा अणु
		अगरp->netअगर_stop &= ~reason;
		अगर (!अगरp->netअगर_stop)
			netअगर_wake_queue(अगरp->ndev);
	पूर्ण
	spin_unlock_irqrestore(&अगरp->netअगर_stop_lock, flags);
पूर्ण

व्योम brcmf_netअगर_rx(काष्ठा brcmf_अगर *अगरp, काष्ठा sk_buff *skb, bool inirq)
अणु
	/* Most of Broadcom's firmwares send 802.11f ADD frame every समय a new
	 * STA connects to the AP पूर्णांकerface. This is an obsoleted standard most
	 * users करोn't use, so don't pass these frames up unless requested.
	 */
	अगर (!अगरp->drvr->settings->iapp && brcmf_skb_is_iapp(skb)) अणु
		brcmu_pkt_buf_मुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर (skb->pkt_type == PACKET_MULTICAST)
		अगरp->ndev->stats.multicast++;

	अगर (!(अगरp->ndev->flags & IFF_UP)) अणु
		brcmu_pkt_buf_मुक्त_skb(skb);
		वापस;
	पूर्ण

	अगरp->ndev->stats.rx_bytes += skb->len;
	अगरp->ndev->stats.rx_packets++;

	brcmf_dbg(DATA, "rx proto=0x%X\n", ntohs(skb->protocol));
	अगर (inirq) अणु
		netअगर_rx(skb);
	पूर्ण अन्यथा अणु
		/* If the receive is not processed inside an ISR,
		 * the softirqd must be woken explicitly to service
		 * the NET_RX_SOFTIRQ.  This is handled by netअगर_rx_ni().
		 */
		netअगर_rx_ni(skb);
	पूर्ण
पूर्ण

व्योम brcmf_netअगर_mon_rx(काष्ठा brcmf_अगर *अगरp, काष्ठा sk_buff *skb)
अणु
	अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_MONITOR_FMT_RADIOTAP)) अणु
		/* Do nothing */
	पूर्ण अन्यथा अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_MONITOR_FMT_HW_RX_HDR)) अणु
		काष्ठा wlc_d11rxhdr *wlc_rxhdr = (काष्ठा wlc_d11rxhdr *)skb->data;
		काष्ठा ieee80211_radiotap_header *radiotap;
		अचिन्हित पूर्णांक offset;
		u16 RxStatus1;

		RxStatus1 = le16_to_cpu(wlc_rxhdr->rxhdr.RxStatus1);

		offset = माप(काष्ठा wlc_d11rxhdr);
		/* MAC inserts 2 pad bytes क्रम a4 headers or QoS or A-MSDU
		 * subframes
		 */
		अगर (RxStatus1 & RXS_PBPRES)
			offset += 2;
		offset += D11_PHY_HDR_LEN;

		skb_pull(skb, offset);

		/* TODO: use RX header to fill some radiotap data */
		radiotap = skb_push(skb, माप(*radiotap));
		स_रखो(radiotap, 0, माप(*radiotap));
		radiotap->it_len = cpu_to_le16(माप(*radiotap));

		/* TODO: 4 bytes with receive status? */
		skb->len -= 4;
	पूर्ण अन्यथा अणु
		काष्ठा ieee80211_radiotap_header *radiotap;

		/* TODO: use RX status to fill some radiotap data */
		radiotap = skb_push(skb, माप(*radiotap));
		स_रखो(radiotap, 0, माप(*radiotap));
		radiotap->it_len = cpu_to_le16(माप(*radiotap));

		/* TODO: 4 bytes with receive status? */
		skb->len -= 4;
	पूर्ण

	skb->dev = अगरp->ndev;
	skb_reset_mac_header(skb);
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(ETH_P_802_2);

	brcmf_netअगर_rx(अगरp, skb, false);
पूर्ण

अटल पूर्णांक brcmf_rx_hdrpull(काष्ठा brcmf_pub *drvr, काष्ठा sk_buff *skb,
			    काष्ठा brcmf_अगर **अगरp)
अणु
	पूर्णांक ret;

	/* process and हटाओ protocol-specअगरic header */
	ret = brcmf_proto_hdrpull(drvr, true, skb, अगरp);

	अगर (ret || !(*अगरp) || !(*अगरp)->ndev) अणु
		अगर (ret != -ENODATA && *अगरp && (*अगरp)->ndev)
			(*अगरp)->ndev->stats.rx_errors++;
		brcmu_pkt_buf_मुक्त_skb(skb);
		वापस -ENODATA;
	पूर्ण

	skb->protocol = eth_type_trans(skb, (*अगरp)->ndev);
	वापस 0;
पूर्ण

व्योम brcmf_rx_frame(काष्ठा device *dev, काष्ठा sk_buff *skb, bool handle_event,
		    bool inirq)
अणु
	काष्ठा brcmf_अगर *अगरp;
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_pub *drvr = bus_अगर->drvr;

	brcmf_dbg(DATA, "Enter: %s: rxp=%p\n", dev_name(dev), skb);

	अगर (brcmf_rx_hdrpull(drvr, skb, &अगरp))
		वापस;

	अगर (brcmf_proto_is_reorder_skb(skb)) अणु
		brcmf_proto_rxreorder(अगरp, skb, inirq);
	पूर्ण अन्यथा अणु
		/* Process special event packets */
		अगर (handle_event) अणु
			gfp_t gfp = inirq ? GFP_ATOMIC : GFP_KERNEL;

			brcmf_fweh_process_skb(अगरp->drvr, skb,
					       BCMILCP_SUBTYPE_VENDOR_LONG, gfp);
		पूर्ण
		brcmf_netअगर_rx(अगरp, skb, inirq);
	पूर्ण
पूर्ण

व्योम brcmf_rx_event(काष्ठा device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा brcmf_अगर *अगरp;
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_pub *drvr = bus_अगर->drvr;

	brcmf_dbg(EVENT, "Enter: %s: rxp=%p\n", dev_name(dev), skb);

	अगर (brcmf_rx_hdrpull(drvr, skb, &अगरp))
		वापस;

	brcmf_fweh_process_skb(अगरp->drvr, skb, 0, GFP_KERNEL);
	brcmu_pkt_buf_मुक्त_skb(skb);
पूर्ण

व्योम brcmf_txfinalize(काष्ठा brcmf_अगर *अगरp, काष्ठा sk_buff *txp, bool success)
अणु
	काष्ठा ethhdr *eh;
	u16 type;

	eh = (काष्ठा ethhdr *)(txp->data);
	type = ntohs(eh->h_proto);

	अगर (type == ETH_P_PAE) अणु
		atomic_dec(&अगरp->pend_8021x_cnt);
		अगर (रुकोqueue_active(&अगरp->pend_8021x_रुको))
			wake_up(&अगरp->pend_8021x_रुको);
	पूर्ण

	अगर (!success)
		अगरp->ndev->stats.tx_errors++;

	brcmu_pkt_buf_मुक्त_skb(txp);
पूर्ण

अटल व्योम brcmf_ethtool_get_drvinfo(काष्ठा net_device *ndev,
				    काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	अक्षर drev[BRCMU_DOTREV_LEN] = "n/a";

	अगर (drvr->revinfo.result == 0)
		brcmu_करोtrev_str(drvr->revinfo.driverrev, drev);
	strlcpy(info->driver, KBUILD_MODNAME, माप(info->driver));
	strlcpy(info->version, drev, माप(info->version));
	strlcpy(info->fw_version, drvr->fwver, माप(info->fw_version));
	strlcpy(info->bus_info, dev_name(drvr->bus_अगर->dev),
		माप(info->bus_info));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops brcmf_ethtool_ops = अणु
	.get_drvinfo = brcmf_ethtool_get_drvinfo,
पूर्ण;

अटल पूर्णांक brcmf_netdev_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);

	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d\n", अगरp->bsscfgidx);

	brcmf_cfg80211_करोwn(ndev);

	brcmf_net_setcarrier(अगरp, false);

	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_netdev_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_bus *bus_अगर = drvr->bus_अगर;
	u32 toe_ol;

	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d\n", अगरp->bsscfgidx);

	/* If bus is not पढ़ोy, can't जारी */
	अगर (bus_अगर->state != BRCMF_BUS_UP) अणु
		bphy_err(drvr, "failed bus is not ready\n");
		वापस -EAGAIN;
	पूर्ण

	atomic_set(&अगरp->pend_8021x_cnt, 0);

	/* Get current TOE mode from करोngle */
	अगर (brcmf_fil_iovar_पूर्णांक_get(अगरp, "toe_ol", &toe_ol) >= 0
	    && (toe_ol & TOE_TX_CSUM_OL) != 0)
		ndev->features |= NETIF_F_IP_CSUM;
	अन्यथा
		ndev->features &= ~NETIF_F_IP_CSUM;

	अगर (brcmf_cfg80211_up(ndev)) अणु
		bphy_err(drvr, "failed to bring up cfg80211\n");
		वापस -EIO;
	पूर्ण

	/* Clear, carrier, set when connected or AP mode. */
	netअगर_carrier_off(ndev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops brcmf_netdev_ops_pri = अणु
	.nकरो_खोलो = brcmf_netdev_खोलो,
	.nकरो_stop = brcmf_netdev_stop,
	.nकरो_start_xmit = brcmf_netdev_start_xmit,
	.nकरो_set_mac_address = brcmf_netdev_set_mac_address,
	.nकरो_set_rx_mode = brcmf_netdev_set_multicast_list
पूर्ण;

पूर्णांक brcmf_net_attach(काष्ठा brcmf_अगर *अगरp, bool locked)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा net_device *ndev;
	s32 err;

	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d mac=%pM\n", अगरp->bsscfgidx,
		  अगरp->mac_addr);
	ndev = अगरp->ndev;

	/* set appropriate operations */
	ndev->netdev_ops = &brcmf_netdev_ops_pri;

	ndev->needed_headroom += drvr->hdrlen;
	ndev->ethtool_ops = &brcmf_ethtool_ops;

	/* set the mac address & netns */
	स_नकल(ndev->dev_addr, अगरp->mac_addr, ETH_ALEN);
	dev_net_set(ndev, wiphy_net(cfg_to_wiphy(drvr->config)));

	INIT_WORK(&अगरp->multicast_work, _brcmf_set_multicast_list);
	INIT_WORK(&अगरp->nकरोffload_work, _brcmf_update_ndtable);

	अगर (locked)
		err = cfg80211_रेजिस्टर_netdevice(ndev);
	अन्यथा
		err = रेजिस्टर_netdev(ndev);
	अगर (err != 0) अणु
		bphy_err(drvr, "couldn't register the net device\n");
		जाओ fail;
	पूर्ण

	netअगर_carrier_off(ndev);

	ndev->priv_deकाष्ठाor = brcmf_cfg80211_मुक्त_netdev;
	brcmf_dbg(INFO, "%s: Broadcom Dongle Host Driver\n", ndev->name);
	वापस 0;

fail:
	drvr->अगरlist[अगरp->bsscfgidx] = शून्य;
	ndev->netdev_ops = शून्य;
	वापस -EBADE;
पूर्ण

व्योम brcmf_net_detach(काष्ठा net_device *ndev, bool locked)
अणु
	अगर (ndev->reg_state == NETREG_REGISTERED) अणु
		अगर (locked)
			cfg80211_unरेजिस्टर_netdevice(ndev);
		अन्यथा
			unरेजिस्टर_netdev(ndev);
	पूर्ण अन्यथा अणु
		brcmf_cfg80211_मुक्त_netdev(ndev);
		मुक्त_netdev(ndev);
	पूर्ण
पूर्ण

अटल पूर्णांक brcmf_net_mon_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	u32 monitor;
	पूर्णांक err;

	brcmf_dbg(TRACE, "Enter\n");

	err = brcmf_fil_cmd_पूर्णांक_get(अगरp, BRCMF_C_GET_MONITOR, &monitor);
	अगर (err) अणु
		bphy_err(drvr, "BRCMF_C_GET_MONITOR error (%d)\n", err);
		वापस err;
	पूर्ण अन्यथा अगर (monitor) अणु
		bphy_err(drvr, "Monitor mode is already enabled\n");
		वापस -EEXIST;
	पूर्ण

	monitor = 3;
	err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_MONITOR, monitor);
	अगर (err)
		bphy_err(drvr, "BRCMF_C_SET_MONITOR error (%d)\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक brcmf_net_mon_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा brcmf_अगर *अगरp = netdev_priv(ndev);
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	u32 monitor;
	पूर्णांक err;

	brcmf_dbg(TRACE, "Enter\n");

	monitor = 0;
	err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_MONITOR, monitor);
	अगर (err)
		bphy_err(drvr, "BRCMF_C_SET_MONITOR error (%d)\n", err);

	वापस err;
पूर्ण

अटल netdev_tx_t brcmf_net_mon_start_xmit(काष्ठा sk_buff *skb,
					    काष्ठा net_device *ndev)
अणु
	dev_kमुक्त_skb_any(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops brcmf_netdev_ops_mon = अणु
	.nकरो_खोलो = brcmf_net_mon_खोलो,
	.nकरो_stop = brcmf_net_mon_stop,
	.nकरो_start_xmit = brcmf_net_mon_start_xmit,
पूर्ण;

पूर्णांक brcmf_net_mon_attach(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा net_device *ndev;
	पूर्णांक err;

	brcmf_dbg(TRACE, "Enter\n");

	ndev = अगरp->ndev;
	ndev->netdev_ops = &brcmf_netdev_ops_mon;

	err = cfg80211_रेजिस्टर_netdevice(ndev);
	अगर (err)
		bphy_err(drvr, "Failed to register %s device\n", ndev->name);

	वापस err;
पूर्ण

व्योम brcmf_net_setcarrier(काष्ठा brcmf_अगर *अगरp, bool on)
अणु
	काष्ठा net_device *ndev;

	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d carrier=%d\n", अगरp->bsscfgidx,
		  on);

	ndev = अगरp->ndev;
	brcmf_txflowblock_अगर(अगरp, BRCMF_NETIF_STOP_REASON_DISCONNECTED, !on);
	अगर (on) अणु
		अगर (!netअगर_carrier_ok(ndev))
			netअगर_carrier_on(ndev);

	पूर्ण अन्यथा अणु
		अगर (netअगर_carrier_ok(ndev))
			netअगर_carrier_off(ndev);
	पूर्ण
पूर्ण

अटल पूर्णांक brcmf_net_p2p_खोलो(काष्ठा net_device *ndev)
अणु
	brcmf_dbg(TRACE, "Enter\n");

	वापस brcmf_cfg80211_up(ndev);
पूर्ण

अटल पूर्णांक brcmf_net_p2p_stop(काष्ठा net_device *ndev)
अणु
	brcmf_dbg(TRACE, "Enter\n");

	वापस brcmf_cfg80211_करोwn(ndev);
पूर्ण

अटल netdev_tx_t brcmf_net_p2p_start_xmit(काष्ठा sk_buff *skb,
					    काष्ठा net_device *ndev)
अणु
	अगर (skb)
		dev_kमुक्त_skb_any(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops brcmf_netdev_ops_p2p = अणु
	.nकरो_खोलो = brcmf_net_p2p_खोलो,
	.nकरो_stop = brcmf_net_p2p_stop,
	.nकरो_start_xmit = brcmf_net_p2p_start_xmit
पूर्ण;

अटल पूर्णांक brcmf_net_p2p_attach(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा net_device *ndev;

	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d mac=%pM\n", अगरp->bsscfgidx,
		  अगरp->mac_addr);
	ndev = अगरp->ndev;

	ndev->netdev_ops = &brcmf_netdev_ops_p2p;

	/* set the mac address */
	स_नकल(ndev->dev_addr, अगरp->mac_addr, ETH_ALEN);

	अगर (रेजिस्टर_netdev(ndev) != 0) अणु
		bphy_err(drvr, "couldn't register the p2p net device\n");
		जाओ fail;
	पूर्ण

	brcmf_dbg(INFO, "%s: Broadcom Dongle Host Driver\n", ndev->name);

	वापस 0;

fail:
	अगरp->drvr->अगरlist[अगरp->bsscfgidx] = शून्य;
	ndev->netdev_ops = शून्य;
	वापस -EBADE;
पूर्ण

काष्ठा brcmf_अगर *brcmf_add_अगर(काष्ठा brcmf_pub *drvr, s32 bsscfgidx, s32 अगरidx,
			      bool is_p2pdev, स्थिर अक्षर *name, u8 *mac_addr)
अणु
	काष्ठा brcmf_अगर *अगरp;
	काष्ठा net_device *ndev;

	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d, ifidx=%d\n", bsscfgidx, अगरidx);

	अगरp = drvr->अगरlist[bsscfgidx];
	/*
	 * Delete the existing पूर्णांकerface beक्रमe overwriting it
	 * in हाल we missed the BRCMF_E_IF_DEL event.
	 */
	अगर (अगरp) अणु
		अगर (अगरidx) अणु
			bphy_err(drvr, "ERROR: netdev:%s already exists\n",
				 अगरp->ndev->name);
			netअगर_stop_queue(अगरp->ndev);
			brcmf_net_detach(अगरp->ndev, false);
			drvr->अगरlist[bsscfgidx] = शून्य;
		पूर्ण अन्यथा अणु
			brcmf_dbg(INFO, "netdev:%s ignore IF event\n",
				  अगरp->ndev->name);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	अगर (!drvr->settings->p2p_enable && is_p2pdev) अणु
		/* this is P2P_DEVICE पूर्णांकerface */
		brcmf_dbg(INFO, "allocate non-netdev interface\n");
		अगरp = kzalloc(माप(*अगरp), GFP_KERNEL);
		अगर (!अगरp)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण अन्यथा अणु
		brcmf_dbg(INFO, "allocate netdev interface\n");
		/* Allocate netdev, including space क्रम निजी काष्ठाure */
		ndev = alloc_netdev(माप(*अगरp), is_p2pdev ? "p2p%d" : name,
				    NET_NAME_UNKNOWN, ether_setup);
		अगर (!ndev)
			वापस ERR_PTR(-ENOMEM);

		ndev->needs_मुक्त_netdev = true;
		अगरp = netdev_priv(ndev);
		अगरp->ndev = ndev;
		/* store mapping अगरidx to bsscfgidx */
		अगर (drvr->अगर2bss[अगरidx] == BRCMF_BSSIDX_INVALID)
			drvr->अगर2bss[अगरidx] = bsscfgidx;
	पूर्ण

	अगरp->drvr = drvr;
	drvr->अगरlist[bsscfgidx] = अगरp;
	अगरp->अगरidx = अगरidx;
	अगरp->bsscfgidx = bsscfgidx;

	init_रुकोqueue_head(&अगरp->pend_8021x_रुको);
	spin_lock_init(&अगरp->netअगर_stop_lock);

	अगर (mac_addr != शून्य)
		स_नकल(अगरp->mac_addr, mac_addr, ETH_ALEN);

	brcmf_dbg(TRACE, " ==== pid:%x, if:%s (%pM) created ===\n",
		  current->pid, name, अगरp->mac_addr);

	वापस अगरp;
पूर्ण

अटल व्योम brcmf_del_अगर(काष्ठा brcmf_pub *drvr, s32 bsscfgidx,
			 bool locked)
अणु
	काष्ठा brcmf_अगर *अगरp;
	पूर्णांक अगरidx;

	अगरp = drvr->अगरlist[bsscfgidx];
	अगर (!अगरp) अणु
		bphy_err(drvr, "Null interface, bsscfgidx=%d\n", bsscfgidx);
		वापस;
	पूर्ण
	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d, ifidx=%d\n", bsscfgidx,
		  अगरp->अगरidx);
	अगरidx = अगरp->अगरidx;

	अगर (अगरp->ndev) अणु
		अगर (bsscfgidx == 0) अणु
			अगर (अगरp->ndev->netdev_ops == &brcmf_netdev_ops_pri) अणु
				rtnl_lock();
				brcmf_netdev_stop(अगरp->ndev);
				rtnl_unlock();
			पूर्ण
		पूर्ण अन्यथा अणु
			netअगर_stop_queue(अगरp->ndev);
		पूर्ण

		अगर (अगरp->ndev->netdev_ops == &brcmf_netdev_ops_pri) अणु
			cancel_work_sync(&अगरp->multicast_work);
			cancel_work_sync(&अगरp->nकरोffload_work);
		पूर्ण
		brcmf_net_detach(अगरp->ndev, locked);
	पूर्ण अन्यथा अणु
		/* Only p2p device पूर्णांकerfaces which get dynamically created
		 * end up here. In this हाल the p2p module should be inक्रमmed
		 * about the removal of the पूर्णांकerface within the firmware. If
		 * not then p2p commands towards the firmware will cause some
		 * serious troublesome side effects. The p2p module will clean
		 * up the अगरp अगर needed.
		 */
		brcmf_p2p_अगरp_हटाओd(अगरp, locked);
		kमुक्त(अगरp);
	पूर्ण

	drvr->अगरlist[bsscfgidx] = शून्य;
	अगर (drvr->अगर2bss[अगरidx] == bsscfgidx)
		drvr->अगर2bss[अगरidx] = BRCMF_BSSIDX_INVALID;
पूर्ण

व्योम brcmf_हटाओ_पूर्णांकerface(काष्ठा brcmf_अगर *अगरp, bool locked)
अणु
	अगर (!अगरp || WARN_ON(अगरp->drvr->अगरlist[अगरp->bsscfgidx] != अगरp))
		वापस;
	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d, ifidx=%d\n", अगरp->bsscfgidx,
		  अगरp->अगरidx);
	brcmf_proto_del_अगर(अगरp->drvr, अगरp);
	brcmf_del_अगर(अगरp->drvr, अगरp->bsscfgidx, locked);
पूर्ण

अटल पूर्णांक brcmf_psm_watchकरोg_notअगरy(काष्ठा brcmf_अगर *अगरp,
				     स्थिर काष्ठा brcmf_event_msg *evपंचांगsg,
				     व्योम *data)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	पूर्णांक err;

	brcmf_dbg(TRACE, "enter: bsscfgidx=%d\n", अगरp->bsscfgidx);

	bphy_err(drvr, "PSM's watchdog has fired!\n");

	err = brcmf_debug_create_memdump(अगरp->drvr->bus_अगर, data,
					 evपंचांगsg->datalen);
	अगर (err)
		bphy_err(drvr, "Failed to get memory dump, %d\n", err);

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_INET
#घोषणा ARPOL_MAX_ENTRIES	8
अटल पूर्णांक brcmf_inetaddr_changed(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा brcmf_pub *drvr = container_of(nb, काष्ठा brcmf_pub,
					      inetaddr_notअगरier);
	काष्ठा in_अगरaddr *अगरa = data;
	काष्ठा net_device *ndev = अगरa->अगरa_dev->dev;
	काष्ठा brcmf_अगर *अगरp;
	पूर्णांक idx, i, ret;
	u32 val;
	__be32 addr_table[ARPOL_MAX_ENTRIES] = अणु0पूर्ण;

	/* Find out अगर the notअगरication is meant क्रम us */
	क्रम (idx = 0; idx < BRCMF_MAX_IFS; idx++) अणु
		अगरp = drvr->अगरlist[idx];
		अगर (अगरp && अगरp->ndev == ndev)
			अवरोध;
		अगर (idx == BRCMF_MAX_IFS - 1)
			वापस NOTIFY_DONE;
	पूर्ण

	/* check अगर arp offload is supported */
	ret = brcmf_fil_iovar_पूर्णांक_get(अगरp, "arpoe", &val);
	अगर (ret)
		वापस NOTIFY_OK;

	/* old version only support primary index */
	ret = brcmf_fil_iovar_पूर्णांक_get(अगरp, "arp_version", &val);
	अगर (ret)
		val = 1;
	अगर (val == 1)
		अगरp = drvr->अगरlist[0];

	/* retrieve the table from firmware */
	ret = brcmf_fil_iovar_data_get(अगरp, "arp_hostip", addr_table,
				       माप(addr_table));
	अगर (ret) अणु
		bphy_err(drvr, "fail to get arp ip table err:%d\n", ret);
		वापस NOTIFY_OK;
	पूर्ण

	क्रम (i = 0; i < ARPOL_MAX_ENTRIES; i++)
		अगर (अगरa->अगरa_address == addr_table[i])
			अवरोध;

	चयन (action) अणु
	हाल NETDEV_UP:
		अगर (i == ARPOL_MAX_ENTRIES) अणु
			brcmf_dbg(TRACE, "add %pI4 to arp table\n",
				  &अगरa->अगरa_address);
			/* set it directly */
			ret = brcmf_fil_iovar_data_set(अगरp, "arp_hostip",
				&अगरa->अगरa_address, माप(अगरa->अगरa_address));
			अगर (ret)
				bphy_err(drvr, "add arp ip err %d\n", ret);
		पूर्ण
		अवरोध;
	हाल NETDEV_DOWN:
		अगर (i < ARPOL_MAX_ENTRIES) अणु
			addr_table[i] = 0;
			brcmf_dbg(TRACE, "remove %pI4 from arp table\n",
				  &अगरa->अगरa_address);
			/* clear the table in firmware */
			ret = brcmf_fil_iovar_data_set(अगरp, "arp_hostip_clear",
						       शून्य, 0);
			अगर (ret) अणु
				bphy_err(drvr, "fail to clear arp ip table err:%d\n",
					 ret);
				वापस NOTIFY_OK;
			पूर्ण
			क्रम (i = 0; i < ARPOL_MAX_ENTRIES; i++) अणु
				अगर (addr_table[i] == 0)
					जारी;
				ret = brcmf_fil_iovar_data_set(अगरp, "arp_hostip",
							       &addr_table[i],
							       माप(addr_table[i]));
				अगर (ret)
					bphy_err(drvr, "add arp ip err %d\n",
						 ret);
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक brcmf_inet6addr_changed(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा brcmf_pub *drvr = container_of(nb, काष्ठा brcmf_pub,
					      inet6addr_notअगरier);
	काष्ठा inet6_अगरaddr *अगरa = data;
	काष्ठा brcmf_अगर *अगरp;
	पूर्णांक i;
	काष्ठा in6_addr *table;

	/* Only handle primary पूर्णांकerface */
	अगरp = drvr->अगरlist[0];
	अगर (!अगरp)
		वापस NOTIFY_DONE;
	अगर (अगरp->ndev != अगरa->idev->dev)
		वापस NOTIFY_DONE;

	table = अगरp->ipv6_addr_tbl;
	क्रम (i = 0; i < NDOL_MAX_ENTRIES; i++)
		अगर (ipv6_addr_equal(&अगरa->addr, &table[i]))
			अवरोध;

	चयन (action) अणु
	हाल NETDEV_UP:
		अगर (i == NDOL_MAX_ENTRIES) अणु
			अगर (अगरp->ipv6addr_idx < NDOL_MAX_ENTRIES) अणु
				table[अगरp->ipv6addr_idx++] = अगरa->addr;
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < NDOL_MAX_ENTRIES - 1; i++)
					table[i] = table[i + 1];
				table[NDOL_MAX_ENTRIES - 1] = अगरa->addr;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल NETDEV_DOWN:
		अगर (i < NDOL_MAX_ENTRIES) अणु
			क्रम (; i < अगरp->ipv6addr_idx - 1; i++)
				table[i] = table[i + 1];
			स_रखो(&table[i], 0, माप(table[i]));
			अगरp->ipv6addr_idx--;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	schedule_work(&अगरp->nकरोffload_work);

	वापस NOTIFY_OK;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक brcmf_revinfo_पढ़ो(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(s->निजी);
	काष्ठा brcmf_rev_info *ri = &bus_अगर->drvr->revinfo;
	अक्षर drev[BRCMU_DOTREV_LEN];
	अक्षर brev[BRCMU_BOARDREV_LEN];

	seq_म_लिखो(s, "vendorid: 0x%04x\n", ri->venकरोrid);
	seq_म_लिखो(s, "deviceid: 0x%04x\n", ri->deviceid);
	seq_म_लिखो(s, "radiorev: %s\n", brcmu_करोtrev_str(ri->radiorev, drev));
	seq_म_लिखो(s, "chip: %s\n", ri->chipname);
	seq_म_लिखो(s, "chippkg: %u\n", ri->chippkg);
	seq_म_लिखो(s, "corerev: %u\n", ri->corerev);
	seq_म_लिखो(s, "boardid: 0x%04x\n", ri->boardid);
	seq_म_लिखो(s, "boardvendor: 0x%04x\n", ri->boardvenकरोr);
	seq_म_लिखो(s, "boardrev: %s\n", brcmu_boardrev_str(ri->boardrev, brev));
	seq_म_लिखो(s, "driverrev: %s\n", brcmu_करोtrev_str(ri->driverrev, drev));
	seq_म_लिखो(s, "ucoderev: %u\n", ri->ucoderev);
	seq_म_लिखो(s, "bus: %u\n", ri->bus);
	seq_म_लिखो(s, "phytype: %u\n", ri->phytype);
	seq_म_लिखो(s, "phyrev: %u\n", ri->phyrev);
	seq_म_लिखो(s, "anarev: %u\n", ri->anarev);
	seq_म_लिखो(s, "nvramrev: %08x\n", ri->nvramrev);

	seq_म_लिखो(s, "clmver: %s\n", bus_अगर->drvr->clmver);

	वापस 0;
पूर्ण

अटल व्योम brcmf_core_bus_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा brcmf_pub *drvr = container_of(work, काष्ठा brcmf_pub,
					      bus_reset);

	brcmf_bus_reset(drvr->bus_अगर);
पूर्ण

अटल sमाप_प्रकार bus_reset_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा brcmf_pub *drvr = file->निजी_data;
	u8 value;

	अगर (kstrtou8_from_user(user_buf, count, 0, &value))
		वापस -EINVAL;

	अगर (value != 1)
		वापस -EINVAL;

	schedule_work(&drvr->bus_reset);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations bus_reset_fops = अणु
	.खोलो	= simple_खोलो,
	.llseek	= no_llseek,
	.ग_लिखो	= bus_reset_ग_लिखो,
पूर्ण;

अटल पूर्णांक brcmf_bus_started(काष्ठा brcmf_pub *drvr, काष्ठा cfg80211_ops *ops)
अणु
	पूर्णांक ret = -1;
	काष्ठा brcmf_bus *bus_अगर = drvr->bus_अगर;
	काष्ठा brcmf_अगर *अगरp;
	काष्ठा brcmf_अगर *p2p_अगरp;

	brcmf_dbg(TRACE, "\n");

	/* add primary networking पूर्णांकerface */
	अगरp = brcmf_add_अगर(drvr, 0, 0, false, "wlan%d", शून्य);
	अगर (IS_ERR(अगरp))
		वापस PTR_ERR(अगरp);

	p2p_अगरp = शून्य;

	/* संकेत bus पढ़ोy */
	brcmf_bus_change_state(bus_अगर, BRCMF_BUS_UP);

	/* करो bus specअगरic preinit here */
	ret = brcmf_bus_preinit(bus_अगर);
	अगर (ret < 0)
		जाओ fail;

	/* Bus is पढ़ोy, करो any initialization */
	ret = brcmf_c_preinit_dcmds(अगरp);
	अगर (ret < 0)
		जाओ fail;

	brcmf_feat_attach(drvr);

	ret = brcmf_proto_init_करोne(drvr);
	अगर (ret < 0)
		जाओ fail;

	brcmf_proto_add_अगर(drvr, अगरp);

	drvr->config = brcmf_cfg80211_attach(drvr, ops,
					     drvr->settings->p2p_enable);
	अगर (drvr->config == शून्य) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	ret = brcmf_net_attach(अगरp, false);

	अगर ((!ret) && (drvr->settings->p2p_enable)) अणु
		p2p_अगरp = drvr->अगरlist[1];
		अगर (p2p_अगरp)
			ret = brcmf_net_p2p_attach(p2p_अगरp);
	पूर्ण

	अगर (ret)
		जाओ fail;

#अगर_घोषित CONFIG_INET
	drvr->inetaddr_notअगरier.notअगरier_call = brcmf_inetaddr_changed;
	ret = रेजिस्टर_inetaddr_notअगरier(&drvr->inetaddr_notअगरier);
	अगर (ret)
		जाओ fail;

#अगर IS_ENABLED(CONFIG_IPV6)
	drvr->inet6addr_notअगरier.notअगरier_call = brcmf_inet6addr_changed;
	ret = रेजिस्टर_inet6addr_notअगरier(&drvr->inet6addr_notअगरier);
	अगर (ret) अणु
		unरेजिस्टर_inetaddr_notअगरier(&drvr->inetaddr_notअगरier);
		जाओ fail;
	पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_INET */

	INIT_WORK(&drvr->bus_reset, brcmf_core_bus_reset);

	/* populate debugfs */
	brcmf_debugfs_add_entry(drvr, "revinfo", brcmf_revinfo_पढ़ो);
	debugfs_create_file("reset", 0600, brcmf_debugfs_get_devdir(drvr), drvr,
			    &bus_reset_fops);
	brcmf_feat_debugfs_create(drvr);
	brcmf_proto_debugfs_create(drvr);
	brcmf_bus_debugfs_create(bus_अगर);

	वापस 0;

fail:
	bphy_err(drvr, "failed: %d\n", ret);
	अगर (drvr->config) अणु
		brcmf_cfg80211_detach(drvr->config);
		drvr->config = शून्य;
	पूर्ण
	brcmf_net_detach(अगरp->ndev, false);
	अगर (p2p_अगरp)
		brcmf_net_detach(p2p_अगरp->ndev, false);
	drvr->अगरlist[0] = शून्य;
	drvr->अगरlist[1] = शून्य;
	अगर (drvr->settings->ignore_probe_fail)
		ret = 0;

	वापस ret;
पूर्ण

पूर्णांक brcmf_alloc(काष्ठा device *dev, काष्ठा brcmf_mp_device *settings)
अणु
	काष्ठा wiphy *wiphy;
	काष्ठा cfg80211_ops *ops;
	काष्ठा brcmf_pub *drvr = शून्य;

	brcmf_dbg(TRACE, "Enter\n");

	ops = brcmf_cfg80211_get_ops(settings);
	अगर (!ops)
		वापस -ENOMEM;

	wiphy = wiphy_new(ops, माप(*drvr));
	अगर (!wiphy) अणु
		kमुक्त(ops);
		वापस -ENOMEM;
	पूर्ण

	set_wiphy_dev(wiphy, dev);
	drvr = wiphy_priv(wiphy);
	drvr->wiphy = wiphy;
	drvr->ops = ops;
	drvr->bus_अगर = dev_get_drvdata(dev);
	drvr->bus_अगर->drvr = drvr;
	drvr->settings = settings;

	वापस 0;
पूर्ण

पूर्णांक brcmf_attach(काष्ठा device *dev)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_pub *drvr = bus_अगर->drvr;
	पूर्णांक ret = 0;
	पूर्णांक i;

	brcmf_dbg(TRACE, "Enter\n");

	क्रम (i = 0; i < ARRAY_SIZE(drvr->अगर2bss); i++)
		drvr->अगर2bss[i] = BRCMF_BSSIDX_INVALID;

	mutex_init(&drvr->proto_block);

	/* Link to bus module */
	drvr->hdrlen = 0;

	/* Attach and link in the protocol */
	ret = brcmf_proto_attach(drvr);
	अगर (ret != 0) अणु
		bphy_err(drvr, "brcmf_prot_attach failed\n");
		जाओ fail;
	पूर्ण

	/* Attach to events important क्रम core code */
	brcmf_fweh_रेजिस्टर(drvr, BRCMF_E_PSM_WATCHDOG,
			    brcmf_psm_watchकरोg_notअगरy);

	/* attach firmware event handler */
	brcmf_fweh_attach(drvr);

	ret = brcmf_bus_started(drvr, drvr->ops);
	अगर (ret != 0) अणु
		bphy_err(drvr, "dongle is not responding: err=%d\n", ret);
		जाओ fail;
	पूर्ण

	वापस 0;

fail:
	brcmf_detach(dev);

	वापस ret;
पूर्ण

व्योम brcmf_bus_add_txhdrlen(काष्ठा device *dev, uपूर्णांक len)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_pub *drvr = bus_अगर->drvr;

	अगर (drvr) अणु
		drvr->hdrlen += len;
	पूर्ण
पूर्ण

व्योम brcmf_dev_reset(काष्ठा device *dev)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_pub *drvr = bus_अगर->drvr;

	अगर (drvr == शून्य)
		वापस;

	अगर (drvr->अगरlist[0])
		brcmf_fil_cmd_पूर्णांक_set(drvr->अगरlist[0], BRCMF_C_TERMINATED, 1);
पूर्ण

व्योम brcmf_dev_coredump(काष्ठा device *dev)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);

	अगर (brcmf_debug_create_memdump(bus_अगर, शून्य, 0) < 0)
		brcmf_dbg(TRACE, "failed to create coredump\n");
पूर्ण

व्योम brcmf_fw_crashed(काष्ठा device *dev)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_pub *drvr = bus_अगर->drvr;

	bphy_err(drvr, "Firmware has halted or crashed\n");

	brcmf_dev_coredump(dev);

	schedule_work(&drvr->bus_reset);
पूर्ण

व्योम brcmf_detach(काष्ठा device *dev)
अणु
	s32 i;
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_pub *drvr = bus_अगर->drvr;

	brcmf_dbg(TRACE, "Enter\n");

	अगर (drvr == शून्य)
		वापस;

#अगर_घोषित CONFIG_INET
	unरेजिस्टर_inetaddr_notअगरier(&drvr->inetaddr_notअगरier);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6)
	unरेजिस्टर_inet6addr_notअगरier(&drvr->inet6addr_notअगरier);
#पूर्ण_अगर

	brcmf_bus_change_state(bus_अगर, BRCMF_BUS_DOWN);
	/* make sure primary पूर्णांकerface हटाओd last */
	क्रम (i = BRCMF_MAX_IFS - 1; i > -1; i--) अणु
		अगर (drvr->अगरlist[i])
			brcmf_हटाओ_पूर्णांकerface(drvr->अगरlist[i], false);
	पूर्ण
	brcmf_bus_stop(drvr->bus_अगर);

	brcmf_fweh_detach(drvr);
	brcmf_proto_detach(drvr);

	अगर (drvr->mon_अगर) अणु
		brcmf_net_detach(drvr->mon_अगर->ndev, false);
		drvr->mon_अगर = शून्य;
	पूर्ण

	अगर (drvr->config) अणु
		brcmf_p2p_detach(&drvr->config->p2p);
		brcmf_cfg80211_detach(drvr->config);
		drvr->config = शून्य;
	पूर्ण
पूर्ण

व्योम brcmf_मुक्त(काष्ठा device *dev)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_pub *drvr = bus_अगर->drvr;

	अगर (!drvr)
		वापस;

	bus_अगर->drvr = शून्य;

	kमुक्त(drvr->ops);

	wiphy_मुक्त(drvr->wiphy);
पूर्ण

s32 brcmf_iovar_data_set(काष्ठा device *dev, अक्षर *name, व्योम *data, u32 len)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_अगर *अगरp = bus_अगर->drvr->अगरlist[0];

	वापस brcmf_fil_iovar_data_set(अगरp, name, data, len);
पूर्ण

अटल पूर्णांक brcmf_get_pend_8021x_cnt(काष्ठा brcmf_अगर *अगरp)
अणु
	वापस atomic_पढ़ो(&अगरp->pend_8021x_cnt);
पूर्ण

पूर्णांक brcmf_netdev_रुको_pend8021x(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	पूर्णांक err;

	err = रुको_event_समयout(अगरp->pend_8021x_रुको,
				 !brcmf_get_pend_8021x_cnt(अगरp),
				 MAX_WAIT_FOR_8021X_TX);

	अगर (!err)
		bphy_err(drvr, "Timed out waiting for no pending 802.1x packets\n");

	वापस !err;
पूर्ण

व्योम brcmf_bus_change_state(काष्ठा brcmf_bus *bus, क्रमागत brcmf_bus_state state)
अणु
	काष्ठा brcmf_pub *drvr = bus->drvr;
	काष्ठा net_device *ndev;
	पूर्णांक अगरidx;

	brcmf_dbg(TRACE, "%d -> %d\n", bus->state, state);

	अगर (!drvr) अणु
		brcmf_dbg(INFO, "ignoring transition, bus not attached yet\n");
		वापस;
	पूर्ण

	bus->state = state;

	अगर (state == BRCMF_BUS_UP) अणु
		क्रम (अगरidx = 0; अगरidx < BRCMF_MAX_IFS; अगरidx++) अणु
			अगर ((drvr->अगरlist[अगरidx]) &&
			    (drvr->अगरlist[अगरidx]->ndev)) अणु
				ndev = drvr->अगरlist[अगरidx]->ndev;
				अगर (netअगर_queue_stopped(ndev))
					netअगर_wake_queue(ndev);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक __init brcmf_core_init(व्योम)
अणु
	पूर्णांक err;

	err = brcmf_sdio_रेजिस्टर();
	अगर (err)
		वापस err;

	err = brcmf_usb_रेजिस्टर();
	अगर (err)
		जाओ error_usb_रेजिस्टर;

	err = brcmf_pcie_रेजिस्टर();
	अगर (err)
		जाओ error_pcie_रेजिस्टर;
	वापस 0;

error_pcie_रेजिस्टर:
	brcmf_usb_निकास();
error_usb_रेजिस्टर:
	brcmf_sdio_निकास();
	वापस err;
पूर्ण

व्योम __निकास brcmf_core_निकास(व्योम)
अणु
	brcmf_sdio_निकास();
	brcmf_usb_निकास();
	brcmf_pcie_निकास();
पूर्ण

