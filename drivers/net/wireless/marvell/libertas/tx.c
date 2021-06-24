<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file contains the handling of TX in wlan driver.
 */
#समावेश <linux/hardirq.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/sched.h>
#समावेश <linux/export.h>
#समावेश <net/cfg80211.h>

#समावेश "host.h"
#समावेश "radiotap.h"
#समावेश "decl.h"
#समावेश "defs.h"
#समावेश "dev.h"
#समावेश "mesh.h"

/**
 * convert_radiotap_rate_to_mv - converts Tx/Rx rates from IEEE80211_RADIOTAP_RATE
 * units (500 Kb/s) पूर्णांकo Marvell WLAN क्रमmat (see Table 8 in Section 3.2.1)
 *
 * @rate:	Input rate
 * वापसs:	Output Rate (0 अगर invalid)
 */
अटल u32 convert_radiotap_rate_to_mv(u8 rate)
अणु
	चयन (rate) अणु
	हाल 2:		/*   1 Mbps */
		वापस 0 | (1 << 4);
	हाल 4:		/*   2 Mbps */
		वापस 1 | (1 << 4);
	हाल 11:		/* 5.5 Mbps */
		वापस 2 | (1 << 4);
	हाल 22:		/*  11 Mbps */
		वापस 3 | (1 << 4);
	हाल 12:		/*   6 Mbps */
		वापस 4 | (1 << 4);
	हाल 18:		/*   9 Mbps */
		वापस 5 | (1 << 4);
	हाल 24:		/*  12 Mbps */
		वापस 6 | (1 << 4);
	हाल 36:		/*  18 Mbps */
		वापस 7 | (1 << 4);
	हाल 48:		/*  24 Mbps */
		वापस 8 | (1 << 4);
	हाल 72:		/*  36 Mbps */
		वापस 9 | (1 << 4);
	हाल 96:		/*  48 Mbps */
		वापस 10 | (1 << 4);
	हाल 108:		/*  54 Mbps */
		वापस 11 | (1 << 4);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * lbs_hard_start_xmit - checks the conditions and sends packet to IF
 * layer अगर everything is ok
 *
 * @skb:	A poपूर्णांकer to skb which includes TX packet
 * @dev:	A poपूर्णांकer to the &काष्ठा net_device
 * वापसs:	0 or -1
 */
netdev_tx_t lbs_hard_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा lbs_निजी *priv = dev->ml_priv;
	काष्ठा txpd *txpd;
	अक्षर *p802x_hdr;
	uपूर्णांक16_t pkt_len;
	netdev_tx_t ret = NETDEV_TX_OK;

	/* We need to protect against the queues being restarted beक्रमe
	   we get round to stopping them */
	spin_lock_irqsave(&priv->driver_lock, flags);

	अगर (priv->surpriseहटाओd)
		जाओ मुक्त;

	अगर (!skb->len || (skb->len > MRVDRV_ETH_TX_PACKET_BUFFER_SIZE)) अणु
		lbs_deb_tx("tx err: skb length %d 0 or > %zd\n",
		       skb->len, MRVDRV_ETH_TX_PACKET_BUFFER_SIZE);
		/* We'll never manage to send this one; drop it and return 'OK' */

		dev->stats.tx_dropped++;
		dev->stats.tx_errors++;
		जाओ मुक्त;
	पूर्ण


	netअगर_stop_queue(priv->dev);
	अगर (priv->mesh_dev)
		netअगर_stop_queue(priv->mesh_dev);

	अगर (priv->tx_pending_len) अणु
		/* This can happen अगर packets come in on the mesh and eth
		   device simultaneously -- there's no mutual exclusion on
		   hard_start_xmit() calls between devices. */
		lbs_deb_tx("Packet on %s while busy\n", dev->name);
		ret = NETDEV_TX_BUSY;
		जाओ unlock;
	पूर्ण

	priv->tx_pending_len = -1;
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	lbs_deb_hex(LBS_DEB_TX, "TX Data", skb->data, min_t(अचिन्हित पूर्णांक, skb->len, 100));

	txpd = (व्योम *)priv->tx_pending_buf;
	स_रखो(txpd, 0, माप(काष्ठा txpd));

	p802x_hdr = skb->data;
	pkt_len = skb->len;

	अगर (priv->wdev->अगरtype == NL80211_IFTYPE_MONITOR) अणु
		काष्ठा tx_radiotap_hdr *rtap_hdr = (व्योम *)skb->data;

		/* set txpd fields from the radiotap header */
		txpd->tx_control = cpu_to_le32(convert_radiotap_rate_to_mv(rtap_hdr->rate));

		/* skip the radiotap header */
		p802x_hdr += माप(*rtap_hdr);
		pkt_len -= माप(*rtap_hdr);

		/* copy destination address from 802.11 header */
		स_नकल(txpd->tx_dest_addr_high, p802x_hdr + 4, ETH_ALEN);
	पूर्ण अन्यथा अणु
		/* copy destination address from 802.3 header */
		स_नकल(txpd->tx_dest_addr_high, p802x_hdr, ETH_ALEN);
	पूर्ण

	txpd->tx_packet_length = cpu_to_le16(pkt_len);
	txpd->tx_packet_location = cpu_to_le32(माप(काष्ठा txpd));

	lbs_mesh_set_txpd(priv, dev, txpd);

	lbs_deb_hex(LBS_DEB_TX, "txpd", (u8 *) &txpd, माप(काष्ठा txpd));

	lbs_deb_hex(LBS_DEB_TX, "Tx Data", (u8 *) p802x_hdr, le16_to_cpu(txpd->tx_packet_length));

	स_नकल(&txpd[1], p802x_hdr, le16_to_cpu(txpd->tx_packet_length));

	spin_lock_irqsave(&priv->driver_lock, flags);
	priv->tx_pending_len = pkt_len + माप(काष्ठा txpd);

	lbs_deb_tx("%s lined up packet\n", __func__);

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	अगर (priv->wdev->अगरtype == NL80211_IFTYPE_MONITOR) अणु
		/* Keep the skb to echo it back once Tx feedback is
		   received from FW */
		skb_orphan(skb);

		/* Keep the skb around क्रम when we get feedback */
		priv->currenttxskb = skb;
	पूर्ण अन्यथा अणु
 मुक्त:
		dev_kमुक्त_skb_any(skb);
	पूर्ण

 unlock:
	spin_unlock_irqrestore(&priv->driver_lock, flags);
	wake_up(&priv->रुकोq);

	वापस ret;
पूर्ण

/**
 * lbs_send_tx_feedback - sends to the host the last transmitted packet,
 * filling the radiotap headers with transmission inक्रमmation.
 *
 * @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 * @try_count:	A 32-bit value containing transmission retry status.
 *
 * वापसs:	व्योम
 */
व्योम lbs_send_tx_feedback(काष्ठा lbs_निजी *priv, u32 try_count)
अणु
	काष्ठा tx_radiotap_hdr *radiotap_hdr;

	अगर (priv->wdev->अगरtype != NL80211_IFTYPE_MONITOR ||
	    priv->currenttxskb == शून्य)
		वापस;

	radiotap_hdr = (काष्ठा tx_radiotap_hdr *)priv->currenttxskb->data;

	radiotap_hdr->data_retries = try_count ?
		(1 + priv->txretrycount - try_count) : 0;

	priv->currenttxskb->protocol = eth_type_trans(priv->currenttxskb,
						      priv->dev);
	netअगर_rx(priv->currenttxskb);

	priv->currenttxskb = शून्य;

	अगर (priv->connect_status == LBS_CONNECTED)
		netअगर_wake_queue(priv->dev);

	अगर (priv->mesh_dev && netअगर_running(priv->mesh_dev))
		netअगर_wake_queue(priv->mesh_dev);
पूर्ण
EXPORT_SYMBOL_GPL(lbs_send_tx_feedback);
