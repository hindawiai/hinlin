<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file contains the handling of RX in wlan driver.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/etherdevice.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <net/cfg80211.h>

#समावेश "defs.h"
#समावेश "host.h"
#समावेश "radiotap.h"
#समावेश "decl.h"
#समावेश "dev.h"
#समावेश "mesh.h"

काष्ठा eth803hdr अणु
	u8 dest_addr[6];
	u8 src_addr[6];
	u16 h803_len;
पूर्ण __packed;

काष्ठा rfc1042hdr अणु
	u8 llc_dsap;
	u8 llc_ssap;
	u8 llc_ctrl;
	u8 snap_oui[3];
	u16 snap_type;
पूर्ण __packed;

काष्ठा rxpackethdr अणु
	काष्ठा eth803hdr eth803_hdr;
	काष्ठा rfc1042hdr rfc1042_hdr;
पूर्ण __packed;

काष्ठा rx80211packethdr अणु
	काष्ठा rxpd rx_pd;
	व्योम *eth80211_hdr;
पूर्ण __packed;

अटल पूर्णांक process_rxed_802_11_packet(काष्ठा lbs_निजी *priv,
	काष्ठा sk_buff *skb);

/**
 * lbs_process_rxed_packet - processes received packet and क्रमwards it
 * to kernel/upper layer
 *
 * @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी
 * @skb:	A poपूर्णांकer to skb which includes the received packet
 * वापसs:	0 or -1
 */
पूर्णांक lbs_process_rxed_packet(काष्ठा lbs_निजी *priv, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret = 0;
	काष्ठा net_device *dev = priv->dev;
	काष्ठा rxpackethdr *p_rx_pkt;
	काष्ठा rxpd *p_rx_pd;
	पूर्णांक hdrchop;
	काष्ठा ethhdr *p_ethhdr;

	BUG_ON(!skb);

	skb->ip_summed = CHECKSUM_NONE;

	अगर (priv->wdev->अगरtype == NL80211_IFTYPE_MONITOR) अणु
		ret = process_rxed_802_11_packet(priv, skb);
		जाओ करोne;
	पूर्ण

	p_rx_pd = (काष्ठा rxpd *) skb->data;
	p_rx_pkt = (काष्ठा rxpackethdr *) ((u8 *)p_rx_pd +
		le32_to_cpu(p_rx_pd->pkt_ptr));

	dev = lbs_mesh_set_dev(priv, dev, p_rx_pd);

	lbs_deb_hex(LBS_DEB_RX, "RX Data: Before chop rxpd", skb->data,
		 min_t(अचिन्हित पूर्णांक, skb->len, 100));

	अगर (skb->len < (ETH_HLEN + 8 + माप(काष्ठा rxpd))) अणु
		lbs_deb_rx("rx err: frame received with bad length\n");
		dev->stats.rx_length_errors++;
		ret = -EINVAL;
		dev_kमुक्त_skb(skb);
		जाओ करोne;
	पूर्ण

	lbs_deb_rx("rx data: skb->len - pkt_ptr = %d-%zd = %zd\n",
		skb->len, (माप_प्रकार)le32_to_cpu(p_rx_pd->pkt_ptr),
		skb->len - (माप_प्रकार)le32_to_cpu(p_rx_pd->pkt_ptr));

	lbs_deb_hex(LBS_DEB_RX, "RX Data: Dest", p_rx_pkt->eth803_hdr.dest_addr,
		माप(p_rx_pkt->eth803_hdr.dest_addr));
	lbs_deb_hex(LBS_DEB_RX, "RX Data: Src", p_rx_pkt->eth803_hdr.src_addr,
		माप(p_rx_pkt->eth803_hdr.src_addr));

	अगर (स_भेद(&p_rx_pkt->rfc1042_hdr,
		   rfc1042_header, माप(rfc1042_header)) == 0) अणु
		/*
		 *  Replace the 803 header and rfc1042 header (llc/snap) with an
		 *    EthernetII header, keep the src/dst and snap_type (ethertype)
		 *
		 *  The firmware only passes up SNAP frames converting
		 *    all RX Data from 802.11 to 802.2/LLC/SNAP frames.
		 *
		 *  To create the Ethernet II, just move the src, dst address right
		 *    beक्रमe the snap_type.
		 */
		p_ethhdr = (काष्ठा ethhdr *)
		    ((u8 *) &p_rx_pkt->eth803_hdr
		     + माप(p_rx_pkt->eth803_hdr) + माप(p_rx_pkt->rfc1042_hdr)
		     - माप(p_rx_pkt->eth803_hdr.dest_addr)
		     - माप(p_rx_pkt->eth803_hdr.src_addr)
		     - माप(p_rx_pkt->rfc1042_hdr.snap_type));

		स_नकल(p_ethhdr->h_source, p_rx_pkt->eth803_hdr.src_addr,
		       माप(p_ethhdr->h_source));
		स_नकल(p_ethhdr->h_dest, p_rx_pkt->eth803_hdr.dest_addr,
		       माप(p_ethhdr->h_dest));

		/* Chop off the rxpd + the excess memory from the 802.2/llc/snap header
		 *   that was हटाओd
		 */
		hdrchop = (u8 *)p_ethhdr - (u8 *)p_rx_pd;
	पूर्ण अन्यथा अणु
		lbs_deb_hex(LBS_DEB_RX, "RX Data: LLC/SNAP",
			(u8 *) &p_rx_pkt->rfc1042_hdr,
			माप(p_rx_pkt->rfc1042_hdr));

		/* Chop off the rxpd */
		hdrchop = (u8 *)&p_rx_pkt->eth803_hdr - (u8 *)p_rx_pd;
	पूर्ण

	/* Chop off the leading header bytes so the skb poपूर्णांकs to the start of
	 *   either the reस्थिरructed EthII frame or the 802.2/llc/snap frame
	 */
	skb_pull(skb, hdrchop);

	priv->cur_rate = lbs_fw_index_to_data_rate(p_rx_pd->rx_rate);

	lbs_deb_rx("rx data: size of actual packet %d\n", skb->len);
	dev->stats.rx_bytes += skb->len;
	dev->stats.rx_packets++;

	skb->protocol = eth_type_trans(skb, dev);
	netअगर_rx_any_context(skb);

	ret = 0;
करोne:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lbs_process_rxed_packet);

/**
 * convert_mv_rate_to_radiotap - converts Tx/Rx rates from Marvell WLAN क्रमmat
 * (see Table 2 in Section 3.1) to IEEE80211_RADIOTAP_RATE units (500 Kb/s)
 *
 * @rate:	Input rate
 * वापसs:	Output Rate (0 अगर invalid)
 */
अटल u8 convert_mv_rate_to_radiotap(u8 rate)
अणु
	चयन (rate) अणु
	हाल 0:		/*   1 Mbps */
		वापस 2;
	हाल 1:		/*   2 Mbps */
		वापस 4;
	हाल 2:		/* 5.5 Mbps */
		वापस 11;
	हाल 3:		/*  11 Mbps */
		वापस 22;
	/* हाल 4: reserved */
	हाल 5:		/*   6 Mbps */
		वापस 12;
	हाल 6:		/*   9 Mbps */
		वापस 18;
	हाल 7:		/*  12 Mbps */
		वापस 24;
	हाल 8:		/*  18 Mbps */
		वापस 36;
	हाल 9:		/*  24 Mbps */
		वापस 48;
	हाल 10:		/*  36 Mbps */
		वापस 72;
	हाल 11:		/*  48 Mbps */
		वापस 96;
	हाल 12:		/*  54 Mbps */
		वापस 108;
	पूर्ण
	pr_alert("Invalid Marvell WLAN rate %i\n", rate);
	वापस 0;
पूर्ण

/**
 * process_rxed_802_11_packet - processes a received 802.11 packet and क्रमwards
 * it to kernel/upper layer
 *
 * @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी
 * @skb:	A poपूर्णांकer to skb which includes the received packet
 * वापसs:	0 or -1
 */
अटल पूर्णांक process_rxed_802_11_packet(काष्ठा lbs_निजी *priv,
	काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret = 0;
	काष्ठा net_device *dev = priv->dev;
	काष्ठा rx80211packethdr *p_rx_pkt;
	काष्ठा rxpd *prxpd;
	काष्ठा rx_radiotap_hdr radiotap_hdr;
	काष्ठा rx_radiotap_hdr *pradiotap_hdr;

	p_rx_pkt = (काष्ठा rx80211packethdr *) skb->data;
	prxpd = &p_rx_pkt->rx_pd;

	/* lbs_deb_hex(LBS_DEB_RX, "RX Data: Before chop rxpd", skb->data, min(skb->len, 100)); */

	अगर (skb->len < (ETH_HLEN + 8 + माप(काष्ठा rxpd))) अणु
		lbs_deb_rx("rx err: frame received with bad length\n");
		dev->stats.rx_length_errors++;
		ret = -EINVAL;
		kमुक्त_skb(skb);
		जाओ करोne;
	पूर्ण

	lbs_deb_rx("rx data: skb->len-sizeof(RxPd) = %d-%zd = %zd\n",
	       skb->len, माप(काष्ठा rxpd), skb->len - माप(काष्ठा rxpd));

	/* create the exported radio header */

	/* radiotap header */
	स_रखो(&radiotap_hdr, 0, माप(radiotap_hdr));
	/* XXX must check radiotap_hdr.hdr.it_pad क्रम pad */
	radiotap_hdr.hdr.it_len = cpu_to_le16 (माप(काष्ठा rx_radiotap_hdr));
	radiotap_hdr.hdr.it_present = cpu_to_le32 (RX_RADIOTAP_PRESENT);
	radiotap_hdr.rate = convert_mv_rate_to_radiotap(prxpd->rx_rate);
	/* XXX must check no carryout */
	radiotap_hdr.antसंकेत = prxpd->snr + prxpd->nf;

	/* chop the rxpd */
	skb_pull(skb, माप(काष्ठा rxpd));

	/* add space क्रम the new radio header */
	अगर ((skb_headroom(skb) < माप(काष्ठा rx_radiotap_hdr)) &&
	    pskb_expand_head(skb, माप(काष्ठा rx_radiotap_hdr), 0, GFP_ATOMIC)) अणु
		netdev_alert(dev, "%s: couldn't pskb_expand_head\n", __func__);
		ret = -ENOMEM;
		kमुक्त_skb(skb);
		जाओ करोne;
	पूर्ण

	pradiotap_hdr = skb_push(skb, माप(काष्ठा rx_radiotap_hdr));
	स_नकल(pradiotap_hdr, &radiotap_hdr, माप(काष्ठा rx_radiotap_hdr));

	priv->cur_rate = lbs_fw_index_to_data_rate(prxpd->rx_rate);

	lbs_deb_rx("rx data: size of actual packet %d\n", skb->len);
	dev->stats.rx_bytes += skb->len;
	dev->stats.rx_packets++;

	skb->protocol = eth_type_trans(skb, priv->dev);
	netअगर_rx_any_context(skb);

	ret = 0;

करोne:
	वापस ret;
पूर्ण
