<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RTL8188EU monitor पूर्णांकerface
 *
 * Copyright (C) 2015 Jakub Sitnicki
 */

#समावेश <linux/ieee80211.h>
#समावेश <linux/netdevice.h>
#समावेश <net/cfg80211.h>

#समावेश <drv_types.h>
#समावेश <rtw_recv.h>
#समावेश <rtw_xmit.h>
#समावेश <mon.h>

/**
 * unprotect_frame() - unset Protected flag and strip off IV and ICV/MIC
 */
अटल व्योम unprotect_frame(काष्ठा sk_buff *skb, पूर्णांक iv_len, पूर्णांक icv_len)
अणु
	काष्ठा ieee80211_hdr *hdr;
	पूर्णांक hdr_len;

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	hdr_len = ieee80211_hdrlen(hdr->frame_control);

	अगर (skb->len < hdr_len + iv_len + icv_len)
		वापस;
	अगर (!ieee80211_has_रक्षित(hdr->frame_control))
		वापस;

	hdr->frame_control &= ~cpu_to_le16(IEEE80211_FCTL_PROTECTED);

	स_हटाओ(skb->data + iv_len, skb->data, hdr_len);
	skb_pull(skb, iv_len);
	skb_trim(skb, skb->len - icv_len);
पूर्ण

अटल व्योम mon_recv_decrypted(काष्ठा net_device *dev, स्थिर u8 *data,
			       पूर्णांक data_len, पूर्णांक iv_len, पूर्णांक icv_len)
अणु
	काष्ठा sk_buff *skb;

	skb = netdev_alloc_skb(dev, data_len);
	अगर (!skb)
		वापस;
	skb_put_data(skb, data, data_len);

	/*
	 * Frame data is not encrypted. Strip off protection so
	 * userspace करोesn't think that it is.
	 */
	unprotect_frame(skb, iv_len, icv_len);

	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->protocol = eth_type_trans(skb, dev);
	netअगर_rx(skb);
पूर्ण

अटल व्योम mon_recv_encrypted(काष्ठा net_device *dev, स्थिर u8 *data,
			       पूर्णांक data_len)
अणु
	अगर (net_ratelimit())
		netdev_info(dev, "Encrypted packets are not supported");
पूर्ण

/**
 * rtl88eu_mon_recv_hook() - क्रमward received frame to the monitor पूर्णांकerface
 *
 * Assumes that the frame contains an IV and an ICV/MIC, and that
 * encrypt field in frame->attrib have been set accordingly.
 */
व्योम rtl88eu_mon_recv_hook(काष्ठा net_device *dev, काष्ठा recv_frame *frame)
अणु
	काष्ठा rx_pkt_attrib *attr;
	पूर्णांक iv_len, icv_len;
	पूर्णांक data_len;
	u8 *data;

	अगर (!dev || !frame)
		वापस;
	अगर (!netअगर_running(dev))
		वापस;

	attr = &frame->attrib;
	data = frame->pkt->data;
	data_len = frame->pkt->len;

	/* Broadcast and multicast frames करोn't have attr->अणुiv,icvपूर्ण_len set */
	SET_ICE_IV_LEN(iv_len, icv_len, attr->encrypt);

	अगर (attr->bdecrypted)
		mon_recv_decrypted(dev, data, data_len, iv_len, icv_len);
	अन्यथा
		mon_recv_encrypted(dev, data, data_len);
पूर्ण

/**
 * rtl88eu_mon_xmit_hook() - क्रमward trयंत्रitted frame to the monitor पूर्णांकerface
 *
 * Assumes that:
 * - frame header contains an IV and frame->attrib.iv_len is set accordingly,
 * - data is not encrypted and ICV/MIC has not been appended yet.
 */
व्योम rtl88eu_mon_xmit_hook(काष्ठा net_device *dev, काष्ठा xmit_frame *frame,
			   uपूर्णांक frag_len)
अणु
	काष्ठा pkt_attrib *attr;
	u8 *data;
	पूर्णांक i, offset;

	अगर (!dev || !frame)
		वापस;
	अगर (!netअगर_running(dev))
		वापस;

	attr = &frame->attrib;

	offset = TXDESC_SIZE + frame->pkt_offset * PACKET_OFFSET_SZ;
	data = frame->buf_addr + offset;

	क्रम (i = 0; i < attr->nr_frags - 1; i++) अणु
		mon_recv_decrypted(dev, data, frag_len, attr->iv_len, 0);
		data += frag_len;
		data = (u8 *)round_up((माप_प्रकार)data, 4);
	पूर्ण
	/* Last fragment has dअगरferent length */
	mon_recv_decrypted(dev, data, attr->last_txcmdsz, attr->iv_len, 0);
पूर्ण

अटल netdev_tx_t mon_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops mon_netdev_ops = अणु
	.nकरो_start_xmit		= mon_xmit,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल व्योम mon_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops = &mon_netdev_ops;
	dev->needs_मुक्त_netdev = true;
	ether_setup(dev);
	dev->priv_flags |= IFF_NO_QUEUE;
	dev->type = ARPHRD_IEEE80211;
	/*
	 * Use a locally administered address (IEEE 802)
	 * XXX: Copied from mac80211_hwsim driver. Revisit.
	 */
	eth_zero_addr(dev->dev_addr);
	dev->dev_addr[0] = 0x12;
पूर्ण

काष्ठा net_device *rtl88eu_mon_init(व्योम)
अणु
	काष्ठा net_device *dev;
	पूर्णांक err;

	dev = alloc_netdev(0, "mon%d", NET_NAME_UNKNOWN, mon_setup);
	अगर (!dev)
		जाओ fail;

	err = रेजिस्टर_netdev(dev);
	अगर (err < 0)
		जाओ fail_मुक्त_dev;

	वापस dev;

fail_मुक्त_dev:
	मुक्त_netdev(dev);
fail:
	वापस शून्य;
पूर्ण

व्योम rtl88eu_mon_deinit(काष्ठा net_device *dev)
अणु
	अगर (!dev)
		वापस;

	unरेजिस्टर_netdev(dev);
पूर्ण
