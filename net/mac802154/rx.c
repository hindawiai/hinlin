<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007-2012 Siemens AG
 *
 * Written by:
 * Pavel Smolenskiy <pavel.smolenskiy@gmail.com>
 * Maxim Gorbachyov <maxim.gorbachev@siemens.com>
 * Dmitry Eremin-Solenikov <dbaryshkov@gmail.com>
 * Alexander Smirnov <alex.bluesman.smirnov@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/crc-ccitt.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/mac802154.h>
#समावेश <net/ieee802154_netdev.h>
#समावेश <net/nl802154.h>

#समावेश "ieee802154_i.h"

अटल पूर्णांक ieee802154_deliver_skb(काष्ठा sk_buff *skb)
अणु
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->protocol = htons(ETH_P_IEEE802154);

	वापस netअगर_receive_skb(skb);
पूर्ण

अटल पूर्णांक
ieee802154_subअगर_frame(काष्ठा ieee802154_sub_अगर_data *sdata,
		       काष्ठा sk_buff *skb, स्थिर काष्ठा ieee802154_hdr *hdr)
अणु
	काष्ठा wpan_dev *wpan_dev = &sdata->wpan_dev;
	__le16 span, sलघु;
	पूर्णांक rc;

	pr_debug("getting packet via slave interface %s\n", sdata->dev->name);

	span = wpan_dev->pan_id;
	sलघु = wpan_dev->लघु_addr;

	चयन (mac_cb(skb)->dest.mode) अणु
	हाल IEEE802154_ADDR_NONE:
		अगर (mac_cb(skb)->dest.mode != IEEE802154_ADDR_NONE)
			/* FIXME: check अगर we are PAN coordinator */
			skb->pkt_type = PACKET_OTHERHOST;
		अन्यथा
			/* ACK comes with both addresses empty */
			skb->pkt_type = PACKET_HOST;
		अवरोध;
	हाल IEEE802154_ADDR_LONG:
		अगर (mac_cb(skb)->dest.pan_id != span &&
		    mac_cb(skb)->dest.pan_id != cpu_to_le16(IEEE802154_PANID_BROADCAST))
			skb->pkt_type = PACKET_OTHERHOST;
		अन्यथा अगर (mac_cb(skb)->dest.extended_addr == wpan_dev->extended_addr)
			skb->pkt_type = PACKET_HOST;
		अन्यथा
			skb->pkt_type = PACKET_OTHERHOST;
		अवरोध;
	हाल IEEE802154_ADDR_SHORT:
		अगर (mac_cb(skb)->dest.pan_id != span &&
		    mac_cb(skb)->dest.pan_id != cpu_to_le16(IEEE802154_PANID_BROADCAST))
			skb->pkt_type = PACKET_OTHERHOST;
		अन्यथा अगर (mac_cb(skb)->dest.लघु_addr == sलघु)
			skb->pkt_type = PACKET_HOST;
		अन्यथा अगर (mac_cb(skb)->dest.लघु_addr ==
			  cpu_to_le16(IEEE802154_ADDR_BROADCAST))
			skb->pkt_type = PACKET_BROADCAST;
		अन्यथा
			skb->pkt_type = PACKET_OTHERHOST;
		अवरोध;
	शेष:
		pr_debug("invalid dest mode\n");
		जाओ fail;
	पूर्ण

	skb->dev = sdata->dev;

	/* TODO this should be moved after netअगर_receive_skb call, otherwise
	 * wireshark will show a mac header with security fields and the
	 * payload is alपढ़ोy decrypted.
	 */
	rc = mac802154_llsec_decrypt(&sdata->sec, skb);
	अगर (rc) अणु
		pr_debug("decryption failed: %i\n", rc);
		जाओ fail;
	पूर्ण

	sdata->dev->stats.rx_packets++;
	sdata->dev->stats.rx_bytes += skb->len;

	चयन (mac_cb(skb)->type) अणु
	हाल IEEE802154_FC_TYPE_BEACON:
	हाल IEEE802154_FC_TYPE_ACK:
	हाल IEEE802154_FC_TYPE_MAC_CMD:
		जाओ fail;

	हाल IEEE802154_FC_TYPE_DATA:
		वापस ieee802154_deliver_skb(skb);
	शेष:
		pr_warn_ratelimited("ieee802154: bad frame received "
				    "(type = %d)\n", mac_cb(skb)->type);
		जाओ fail;
	पूर्ण

fail:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

अटल व्योम
ieee802154_prपूर्णांक_addr(स्थिर अक्षर *name, स्थिर काष्ठा ieee802154_addr *addr)
अणु
	अगर (addr->mode == IEEE802154_ADDR_NONE)
		pr_debug("%s not present\n", name);

	pr_debug("%s PAN ID: %04x\n", name, le16_to_cpu(addr->pan_id));
	अगर (addr->mode == IEEE802154_ADDR_SHORT) अणु
		pr_debug("%s is short: %04x\n", name,
			 le16_to_cpu(addr->लघु_addr));
	पूर्ण अन्यथा अणु
		u64 hw = swab64((__क्रमce u64)addr->extended_addr);

		pr_debug("%s is hardware: %8phC\n", name, &hw);
	पूर्ण
पूर्ण

अटल पूर्णांक
ieee802154_parse_frame_start(काष्ठा sk_buff *skb, काष्ठा ieee802154_hdr *hdr)
अणु
	पूर्णांक hlen;
	काष्ठा ieee802154_mac_cb *cb = mac_cb_init(skb);

	skb_reset_mac_header(skb);

	hlen = ieee802154_hdr_pull(skb, hdr);
	अगर (hlen < 0)
		वापस -EINVAL;

	skb->mac_len = hlen;

	pr_debug("fc: %04x dsn: %02x\n", le16_to_cpup((__le16 *)&hdr->fc),
		 hdr->seq);

	cb->type = hdr->fc.type;
	cb->ackreq = hdr->fc.ack_request;
	cb->secen = hdr->fc.security_enabled;

	ieee802154_prपूर्णांक_addr("destination", &hdr->dest);
	ieee802154_prपूर्णांक_addr("source", &hdr->source);

	cb->source = hdr->source;
	cb->dest = hdr->dest;

	अगर (hdr->fc.security_enabled) अणु
		u64 key;

		pr_debug("seclevel %i\n", hdr->sec.level);

		चयन (hdr->sec.key_id_mode) अणु
		हाल IEEE802154_SCF_KEY_IMPLICIT:
			pr_debug("implicit key\n");
			अवरोध;

		हाल IEEE802154_SCF_KEY_INDEX:
			pr_debug("key %02x\n", hdr->sec.key_id);
			अवरोध;

		हाल IEEE802154_SCF_KEY_SHORT_INDEX:
			pr_debug("key %04x:%04x %02x\n",
				 le32_to_cpu(hdr->sec.लघु_src) >> 16,
				 le32_to_cpu(hdr->sec.लघु_src) & 0xffff,
				 hdr->sec.key_id);
			अवरोध;

		हाल IEEE802154_SCF_KEY_HW_INDEX:
			key = swab64((__क्रमce u64)hdr->sec.extended_src);
			pr_debug("key source %8phC %02x\n", &key,
				 hdr->sec.key_id);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
__ieee802154_rx_handle_packet(काष्ठा ieee802154_local *local,
			      काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा ieee802154_sub_अगर_data *sdata;
	काष्ठा ieee802154_hdr hdr;

	ret = ieee802154_parse_frame_start(skb, &hdr);
	अगर (ret) अणु
		pr_debug("got invalid frame\n");
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (sdata->wpan_dev.अगरtype != NL802154_IFTYPE_NODE)
			जारी;

		अगर (!ieee802154_sdata_running(sdata))
			जारी;

		ieee802154_subअगर_frame(sdata, skb, &hdr);
		skb = शून्य;
		अवरोध;
	पूर्ण

	kमुक्त_skb(skb);
पूर्ण

अटल व्योम
ieee802154_monitors_rx(काष्ठा ieee802154_local *local, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *skb2;
	काष्ठा ieee802154_sub_अगर_data *sdata;

	skb_reset_mac_header(skb);
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(ETH_P_IEEE802154);

	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (sdata->wpan_dev.अगरtype != NL802154_IFTYPE_MONITOR)
			जारी;

		अगर (!ieee802154_sdata_running(sdata))
			जारी;

		skb2 = skb_clone(skb, GFP_ATOMIC);
		अगर (skb2) अणु
			skb2->dev = sdata->dev;
			ieee802154_deliver_skb(skb2);

			sdata->dev->stats.rx_packets++;
			sdata->dev->stats.rx_bytes += skb->len;
		पूर्ण
	पूर्ण
पूर्ण

व्योम ieee802154_rx(काष्ठा ieee802154_local *local, काष्ठा sk_buff *skb)
अणु
	u16 crc;

	WARN_ON_ONCE(softirq_count() == 0);

	अगर (local->suspended)
		जाओ drop;

	/* TODO: When a transceiver omits the checksum here, we
	 * add an own calculated one. This is currently an ugly
	 * solution because the monitor needs a crc here.
	 */
	अगर (local->hw.flags & IEEE802154_HW_RX_OMIT_CKSUM) अणु
		crc = crc_ccitt(0, skb->data, skb->len);
		put_unaligned_le16(crc, skb_put(skb, 2));
	पूर्ण

	rcu_पढ़ो_lock();

	ieee802154_monitors_rx(local, skb);

	/* Check अगर transceiver करोesn't validate the checksum.
	 * If not we validate the checksum here.
	 */
	अगर (local->hw.flags & IEEE802154_HW_RX_DROP_BAD_CKSUM) अणु
		crc = crc_ccitt(0, skb->data, skb->len);
		अगर (crc) अणु
			rcu_पढ़ो_unlock();
			जाओ drop;
		पूर्ण
	पूर्ण
	/* हटाओ crc */
	skb_trim(skb, skb->len - 2);

	__ieee802154_rx_handle_packet(local, skb);

	rcu_पढ़ो_unlock();

	वापस;
drop:
	kमुक्त_skb(skb);
पूर्ण

व्योम
ieee802154_rx_irqsafe(काष्ठा ieee802154_hw *hw, काष्ठा sk_buff *skb, u8 lqi)
अणु
	काष्ठा ieee802154_local *local = hw_to_local(hw);

	mac_cb(skb)->lqi = lqi;
	skb->pkt_type = IEEE802154_RX_MSG;
	skb_queue_tail(&local->skb_queue, skb);
	tasklet_schedule(&local->tasklet);
पूर्ण
EXPORT_SYMBOL(ieee802154_rx_irqsafe);
