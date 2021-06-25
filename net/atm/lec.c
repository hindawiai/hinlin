<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * lec.c: Lan Emulation driver
 *
 * Marko Kiiskila <mkiiskila@yahoo.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/capability.h>

/* We are ethernet device */
#समावेश <linux/अगर_ether.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/sock.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>
#समावेश <net/arp.h>
#समावेश <net/dst.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/seq_file.h>

/* And aपंचांग device */
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/aपंचांगlec.h>

/* Proxy LEC knows about bridging */
#अगर IS_ENABLED(CONFIG_BRIDGE)
#समावेश "../bridge/br_private.h"

अटल अचिन्हित अक्षर bridge_ula_lec[] = अणु 0x01, 0x80, 0xc2, 0x00, 0x00 पूर्ण;
#पूर्ण_अगर

/* Modular too */
#समावेश <linux/module.h>
#समावेश <linux/init.h>

/* Hardening क्रम Spectre-v1 */
#समावेश <linux/nospec.h>

#समावेश "lec.h"
#समावेश "lec_arpc.h"
#समावेश "resources.h"

#घोषणा DUMP_PACKETS 0		/*
				 * 0 = None,
				 * 1 = 30 first bytes
				 * 2 = Whole packet
				 */

#घोषणा LEC_UNRES_QUE_LEN 8	/*
				 * number of tx packets to queue क्रम a
				 * single destination जबतक रुकोing क्रम SVC
				 */

अटल पूर्णांक lec_खोलो(काष्ठा net_device *dev);
अटल netdev_tx_t lec_start_xmit(काष्ठा sk_buff *skb,
				  काष्ठा net_device *dev);
अटल पूर्णांक lec_बंद(काष्ठा net_device *dev);
अटल काष्ठा lec_arp_table *lec_arp_find(काष्ठा lec_priv *priv,
					  स्थिर अचिन्हित अक्षर *mac_addr);
अटल पूर्णांक lec_arp_हटाओ(काष्ठा lec_priv *priv,
			  काष्ठा lec_arp_table *to_हटाओ);
/* LANE2 functions */
अटल व्योम lane2_associate_ind(काष्ठा net_device *dev, स्थिर u8 *mac_address,
				स्थिर u8 *tlvs, u32 मापtlvs);
अटल पूर्णांक lane2_resolve(काष्ठा net_device *dev, स्थिर u8 *dst_mac, पूर्णांक क्रमce,
			 u8 **tlvs, u32 *मापtlvs);
अटल पूर्णांक lane2_associate_req(काष्ठा net_device *dev, स्थिर u8 *lan_dst,
			       स्थिर u8 *tlvs, u32 मापtlvs);

अटल पूर्णांक lec_addr_delete(काष्ठा lec_priv *priv, स्थिर अचिन्हित अक्षर *aपंचांग_addr,
			   अचिन्हित दीर्घ permanent);
अटल व्योम lec_arp_check_empties(काष्ठा lec_priv *priv,
				  काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb);
अटल व्योम lec_arp_destroy(काष्ठा lec_priv *priv);
अटल व्योम lec_arp_init(काष्ठा lec_priv *priv);
अटल काष्ठा aपंचांग_vcc *lec_arp_resolve(काष्ठा lec_priv *priv,
				       स्थिर अचिन्हित अक्षर *mac_to_find,
				       पूर्णांक is_rdesc,
				       काष्ठा lec_arp_table **ret_entry);
अटल व्योम lec_arp_update(काष्ठा lec_priv *priv, स्थिर अचिन्हित अक्षर *mac_addr,
			   स्थिर अचिन्हित अक्षर *aपंचांग_addr,
			   अचिन्हित दीर्घ remoteflag,
			   अचिन्हित पूर्णांक targetless_le_arp);
अटल व्योम lec_flush_complete(काष्ठा lec_priv *priv, अचिन्हित दीर्घ tran_id);
अटल पूर्णांक lec_mcast_make(काष्ठा lec_priv *priv, काष्ठा aपंचांग_vcc *vcc);
अटल व्योम lec_set_flush_tran_id(काष्ठा lec_priv *priv,
				  स्थिर अचिन्हित अक्षर *aपंचांग_addr,
				  अचिन्हित दीर्घ tran_id);
अटल व्योम lec_vcc_added(काष्ठा lec_priv *priv,
			  स्थिर काष्ठा aपंचांगlec_ioc *ioc_data,
			  काष्ठा aपंचांग_vcc *vcc,
			  व्योम (*old_push)(काष्ठा aपंचांग_vcc *vcc,
					   काष्ठा sk_buff *skb));
अटल व्योम lec_vcc_बंद(काष्ठा lec_priv *priv, काष्ठा aपंचांग_vcc *vcc);

/* must be करोne under lec_arp_lock */
अटल अंतरभूत व्योम lec_arp_hold(काष्ठा lec_arp_table *entry)
अणु
	refcount_inc(&entry->usage);
पूर्ण

अटल अंतरभूत व्योम lec_arp_put(काष्ठा lec_arp_table *entry)
अणु
	अगर (refcount_dec_and_test(&entry->usage))
		kमुक्त(entry);
पूर्ण

अटल काष्ठा lane2_ops lane2_ops = अणु
	.resolve = lane2_resolve,		/* spec 3.1.3 */
	.associate_req = lane2_associate_req,	/* spec 3.1.4 */
	.associate_indicator = शून्य             /* spec 3.1.5 */
पूर्ण;

अटल अचिन्हित अक्षर bus_mac[ETH_ALEN] = अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण;

/* Device काष्ठाures */
अटल काष्ठा net_device *dev_lec[MAX_LEC_ITF];

#अगर IS_ENABLED(CONFIG_BRIDGE)
अटल व्योम lec_handle_bridge(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	अक्षर *buff;
	काष्ठा lec_priv *priv;

	/*
	 * Check अगर this is a BPDU. If so, ask zeppelin to send
	 * LE_TOPOLOGY_REQUEST with the same value of Topology Change bit
	 * as the Config BPDU has
	 */
	buff = skb->data + skb->dev->hard_header_len;
	अगर (*buff++ == 0x42 && *buff++ == 0x42 && *buff++ == 0x03) अणु
		काष्ठा sock *sk;
		काष्ठा sk_buff *skb2;
		काष्ठा aपंचांगlec_msg *mesg;

		skb2 = alloc_skb(माप(काष्ठा aपंचांगlec_msg), GFP_ATOMIC);
		अगर (skb2 == शून्य)
			वापस;
		skb2->len = माप(काष्ठा aपंचांगlec_msg);
		mesg = (काष्ठा aपंचांगlec_msg *)skb2->data;
		mesg->type = l_topology_change;
		buff += 4;
		mesg->content.normal.flag = *buff & 0x01;
					/* 0x01 is topology change */

		priv = netdev_priv(dev);
		aपंचांग_क्रमce_अक्षरge(priv->lecd, skb2->truesize);
		sk = sk_aपंचांग(priv->lecd);
		skb_queue_tail(&sk->sk_receive_queue, skb2);
		sk->sk_data_पढ़ोy(sk);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_BRIDGE) */

/*
 * Open/initialize the netdevice. This is called (in the current kernel)
 * someसमय after booting when the 'ifconfig' program is run.
 *
 * This routine should set everything up anew at each खोलो, even
 * रेजिस्टरs that "should" only need to be set once at boot, so that
 * there is non-reboot way to recover अगर something goes wrong.
 */

अटल पूर्णांक lec_खोलो(काष्ठा net_device *dev)
अणु
	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

अटल व्योम
lec_send(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;

	ATM_SKB(skb)->vcc = vcc;
	aपंचांग_account_tx(vcc, skb);

	अगर (vcc->send(vcc, skb) < 0) अणु
		dev->stats.tx_dropped++;
		वापस;
	पूर्ण

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;
पूर्ण

अटल व्योम lec_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	pr_info("%s\n", dev->name);
	netअगर_trans_update(dev);
	netअगर_wake_queue(dev);
पूर्ण

अटल netdev_tx_t lec_start_xmit(काष्ठा sk_buff *skb,
				  काष्ठा net_device *dev)
अणु
	काष्ठा sk_buff *skb2;
	काष्ठा lec_priv *priv = netdev_priv(dev);
	काष्ठा lecdatahdr_8023 *lec_h;
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा lec_arp_table *entry;
	अचिन्हित अक्षर *dst;
	पूर्णांक min_frame_size;
	पूर्णांक is_rdesc;

	pr_debug("called\n");
	अगर (!priv->lecd) अणु
		pr_info("%s:No lecd attached\n", dev->name);
		dev->stats.tx_errors++;
		netअगर_stop_queue(dev);
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	pr_debug("skbuff head:%lx data:%lx tail:%lx end:%lx\n",
		 (दीर्घ)skb->head, (दीर्घ)skb->data, (दीर्घ)skb_tail_poपूर्णांकer(skb),
		 (दीर्घ)skb_end_poपूर्णांकer(skb));
#अगर IS_ENABLED(CONFIG_BRIDGE)
	अगर (स_भेद(skb->data, bridge_ula_lec, माप(bridge_ula_lec)) == 0)
		lec_handle_bridge(skb, dev);
#पूर्ण_अगर

	/* Make sure we have room क्रम lec_id */
	अगर (skb_headroom(skb) < 2) अणु
		pr_debug("reallocating skb\n");
		skb2 = skb_पुनः_स्मृति_headroom(skb, LEC_HEADER_LEN);
		अगर (unlikely(!skb2)) अणु
			kमुक्त_skb(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
		consume_skb(skb);
		skb = skb2;
	पूर्ण
	skb_push(skb, 2);

	/* Put le header to place */
	lec_h = (काष्ठा lecdatahdr_8023 *)skb->data;
	lec_h->le_header = htons(priv->lecid);

#अगर DUMP_PACKETS >= 2
#घोषणा MAX_DUMP_SKB 99
#या_अगर DUMP_PACKETS >= 1
#घोषणा MAX_DUMP_SKB 30
#पूर्ण_अगर
#अगर DUMP_PACKETS >= 1
	prपूर्णांकk(KERN_DEBUG "%s: send datalen:%ld lecid:%4.4x\n",
	       dev->name, skb->len, priv->lecid);
	prपूर्णांक_hex_dump(KERN_DEBUG, "", DUMP_OFFSET, 16, 1,
		       skb->data, min(skb->len, MAX_DUMP_SKB), true);
#पूर्ण_अगर /* DUMP_PACKETS >= 1 */

	/* Minimum ethernet-frame size */
	min_frame_size = LEC_MINIMUM_8023_SIZE;
	अगर (skb->len < min_frame_size) अणु
		अगर ((skb->len + skb_tailroom(skb)) < min_frame_size) अणु
			skb2 = skb_copy_expand(skb, 0,
					       min_frame_size - skb->truesize,
					       GFP_ATOMIC);
			dev_kमुक्त_skb(skb);
			अगर (skb2 == शून्य) अणु
				dev->stats.tx_dropped++;
				वापस NETDEV_TX_OK;
			पूर्ण
			skb = skb2;
		पूर्ण
		skb_put(skb, min_frame_size - skb->len);
	पूर्ण

	/* Send to right vcc */
	is_rdesc = 0;
	dst = lec_h->h_dest;
	entry = शून्य;
	vcc = lec_arp_resolve(priv, dst, is_rdesc, &entry);
	pr_debug("%s:vcc:%p vcc_flags:%lx, entry:%p\n",
		 dev->name, vcc, vcc ? vcc->flags : 0, entry);
	अगर (!vcc || !test_bit(ATM_VF_READY, &vcc->flags)) अणु
		अगर (entry && (entry->tx_रुको.qlen < LEC_UNRES_QUE_LEN)) अणु
			pr_debug("%s:queuing packet, MAC address %pM\n",
				 dev->name, lec_h->h_dest);
			skb_queue_tail(&entry->tx_रुको, skb);
		पूर्ण अन्यथा अणु
			pr_debug("%s:tx queue full or no arp entry, dropping, MAC address: %pM\n",
				 dev->name, lec_h->h_dest);
			dev->stats.tx_dropped++;
			dev_kमुक्त_skb(skb);
		पूर्ण
		जाओ out;
	पूर्ण
#अगर DUMP_PACKETS > 0
	prपूर्णांकk(KERN_DEBUG "%s:sending to vpi:%d vci:%d\n",
	       dev->name, vcc->vpi, vcc->vci);
#पूर्ण_अगर /* DUMP_PACKETS > 0 */

	जबतक (entry && (skb2 = skb_dequeue(&entry->tx_रुको))) अणु
		pr_debug("emptying tx queue, MAC address %pM\n", lec_h->h_dest);
		lec_send(vcc, skb2);
	पूर्ण

	lec_send(vcc, skb);

	अगर (!aपंचांग_may_send(vcc, 0)) अणु
		काष्ठा lec_vcc_priv *vpriv = LEC_VCC_PRIV(vcc);

		vpriv->xoff = 1;
		netअगर_stop_queue(dev);

		/*
		 * vcc->pop() might have occurred in between, making
		 * the vcc usuable again.  Since xmit is serialized,
		 * this is the only situation we have to re-test.
		 */

		अगर (aपंचांग_may_send(vcc, 0))
			netअगर_wake_queue(dev);
	पूर्ण

out:
	अगर (entry)
		lec_arp_put(entry);
	netअगर_trans_update(dev);
	वापस NETDEV_TX_OK;
पूर्ण

/* The inverse routine to net_खोलो(). */
अटल पूर्णांक lec_बंद(काष्ठा net_device *dev)
अणु
	netअगर_stop_queue(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक lec_aपंचांग_send(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा net_device *dev = (काष्ठा net_device *)vcc->proto_data;
	काष्ठा lec_priv *priv = netdev_priv(dev);
	काष्ठा aपंचांगlec_msg *mesg;
	काष्ठा lec_arp_table *entry;
	पूर्णांक i;
	अक्षर *पंचांगp;		/* FIXME */

	WARN_ON(refcount_sub_and_test(skb->truesize, &sk_aपंचांग(vcc)->sk_wmem_alloc));
	mesg = (काष्ठा aपंचांगlec_msg *)skb->data;
	पंचांगp = skb->data;
	पंचांगp += माप(काष्ठा aपंचांगlec_msg);
	pr_debug("%s: msg from zeppelin:%d\n", dev->name, mesg->type);
	चयन (mesg->type) अणु
	हाल l_set_mac_addr:
		क्रम (i = 0; i < 6; i++)
			dev->dev_addr[i] = mesg->content.normal.mac_addr[i];
		अवरोध;
	हाल l_del_mac_addr:
		क्रम (i = 0; i < 6; i++)
			dev->dev_addr[i] = 0;
		अवरोध;
	हाल l_addr_delete:
		lec_addr_delete(priv, mesg->content.normal.aपंचांग_addr,
				mesg->content.normal.flag);
		अवरोध;
	हाल l_topology_change:
		priv->topology_change = mesg->content.normal.flag;
		अवरोध;
	हाल l_flush_complete:
		lec_flush_complete(priv, mesg->content.normal.flag);
		अवरोध;
	हाल l_narp_req:	/* LANE2: see 7.1.35 in the lane2 spec */
		spin_lock_irqsave(&priv->lec_arp_lock, flags);
		entry = lec_arp_find(priv, mesg->content.normal.mac_addr);
		lec_arp_हटाओ(priv, entry);
		spin_unlock_irqrestore(&priv->lec_arp_lock, flags);

		अगर (mesg->content.normal.no_source_le_narp)
			अवरोध;
		fallthrough;
	हाल l_arp_update:
		lec_arp_update(priv, mesg->content.normal.mac_addr,
			       mesg->content.normal.aपंचांग_addr,
			       mesg->content.normal.flag,
			       mesg->content.normal.targetless_le_arp);
		pr_debug("in l_arp_update\n");
		अगर (mesg->मापtlvs != 0) अणु	/* LANE2 3.1.5 */
			pr_debug("LANE2 3.1.5, got tlvs, size %d\n",
				 mesg->मापtlvs);
			lane2_associate_ind(dev, mesg->content.normal.mac_addr,
					    पंचांगp, mesg->मापtlvs);
		पूर्ण
		अवरोध;
	हाल l_config:
		priv->maximum_unknown_frame_count =
		    mesg->content.config.maximum_unknown_frame_count;
		priv->max_unknown_frame_समय =
		    (mesg->content.config.max_unknown_frame_समय * HZ);
		priv->max_retry_count = mesg->content.config.max_retry_count;
		priv->aging_समय = (mesg->content.config.aging_समय * HZ);
		priv->क्रमward_delay_समय =
		    (mesg->content.config.क्रमward_delay_समय * HZ);
		priv->arp_response_समय =
		    (mesg->content.config.arp_response_समय * HZ);
		priv->flush_समयout = (mesg->content.config.flush_समयout * HZ);
		priv->path_चयनing_delay =
		    (mesg->content.config.path_चयनing_delay * HZ);
		priv->lane_version = mesg->content.config.lane_version;
					/* LANE2 */
		priv->lane2_ops = शून्य;
		अगर (priv->lane_version > 1)
			priv->lane2_ops = &lane2_ops;
		rtnl_lock();
		अगर (dev_set_mtu(dev, mesg->content.config.mtu))
			pr_info("%s: change_mtu to %d failed\n",
				dev->name, mesg->content.config.mtu);
		rtnl_unlock();
		priv->is_proxy = mesg->content.config.is_proxy;
		अवरोध;
	हाल l_flush_tran_id:
		lec_set_flush_tran_id(priv, mesg->content.normal.aपंचांग_addr,
				      mesg->content.normal.flag);
		अवरोध;
	हाल l_set_lecid:
		priv->lecid =
		    (अचिन्हित लघु)(0xffff & mesg->content.normal.flag);
		अवरोध;
	हाल l_should_bridge:
#अगर IS_ENABLED(CONFIG_BRIDGE)
	अणु
		pr_debug("%s: bridge zeppelin asks about %pM\n",
			 dev->name, mesg->content.proxy.mac_addr);

		अगर (br_fdb_test_addr_hook == शून्य)
			अवरोध;

		अगर (br_fdb_test_addr_hook(dev, mesg->content.proxy.mac_addr)) अणु
			/* hit from bridge table, send LE_ARP_RESPONSE */
			काष्ठा sk_buff *skb2;
			काष्ठा sock *sk;

			pr_debug("%s: entry found, responding to zeppelin\n",
				 dev->name);
			skb2 = alloc_skb(माप(काष्ठा aपंचांगlec_msg), GFP_ATOMIC);
			अगर (skb2 == शून्य)
				अवरोध;
			skb2->len = माप(काष्ठा aपंचांगlec_msg);
			skb_copy_to_linear_data(skb2, mesg, माप(*mesg));
			aपंचांग_क्रमce_अक्षरge(priv->lecd, skb2->truesize);
			sk = sk_aपंचांग(priv->lecd);
			skb_queue_tail(&sk->sk_receive_queue, skb2);
			sk->sk_data_पढ़ोy(sk);
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_BRIDGE) */
		अवरोध;
	शेष:
		pr_info("%s: Unknown message type %d\n", dev->name, mesg->type);
		dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण
	dev_kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल व्योम lec_aपंचांग_बंद(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा net_device *dev = (काष्ठा net_device *)vcc->proto_data;
	काष्ठा lec_priv *priv = netdev_priv(dev);

	priv->lecd = शून्य;
	/* Do something needful? */

	netअगर_stop_queue(dev);
	lec_arp_destroy(priv);

	अगर (skb_peek(&sk_aपंचांग(vcc)->sk_receive_queue))
		pr_info("%s closing with messages pending\n", dev->name);
	जबतक ((skb = skb_dequeue(&sk_aपंचांग(vcc)->sk_receive_queue))) अणु
		aपंचांग_वापस(vcc, skb->truesize);
		dev_kमुक्त_skb(skb);
	पूर्ण

	pr_info("%s: Shut down!\n", dev->name);
	module_put(THIS_MODULE);
पूर्ण

अटल स्थिर काष्ठा aपंचांगdev_ops lecdev_ops = अणु
	.बंद = lec_aपंचांग_बंद,
	.send = lec_aपंचांग_send
पूर्ण;

अटल काष्ठा aपंचांग_dev lecaपंचांग_dev = अणु
	.ops = &lecdev_ops,
	.type = "lec",
	.number = 999,		/* dummy device number */
	.lock = __SPIN_LOCK_UNLOCKED(lecaपंचांग_dev.lock)
पूर्ण;

/*
 * LANE2: new argument काष्ठा sk_buff *data contains
 * the LE_ARP based TLVs पूर्णांकroduced in the LANE2 spec
 */
अटल पूर्णांक
send_to_lecd(काष्ठा lec_priv *priv, aपंचांगlec_msg_type type,
	     स्थिर अचिन्हित अक्षर *mac_addr, स्थिर अचिन्हित अक्षर *aपंचांग_addr,
	     काष्ठा sk_buff *data)
अणु
	काष्ठा sock *sk;
	काष्ठा sk_buff *skb;
	काष्ठा aपंचांगlec_msg *mesg;

	अगर (!priv || !priv->lecd)
		वापस -1;
	skb = alloc_skb(माप(काष्ठा aपंचांगlec_msg), GFP_ATOMIC);
	अगर (!skb)
		वापस -1;
	skb->len = माप(काष्ठा aपंचांगlec_msg);
	mesg = (काष्ठा aपंचांगlec_msg *)skb->data;
	स_रखो(mesg, 0, माप(काष्ठा aपंचांगlec_msg));
	mesg->type = type;
	अगर (data != शून्य)
		mesg->मापtlvs = data->len;
	अगर (mac_addr)
		ether_addr_copy(mesg->content.normal.mac_addr, mac_addr);
	अन्यथा
		mesg->content.normal.targetless_le_arp = 1;
	अगर (aपंचांग_addr)
		स_नकल(&mesg->content.normal.aपंचांग_addr, aपंचांग_addr, ATM_ESA_LEN);

	aपंचांग_क्रमce_अक्षरge(priv->lecd, skb->truesize);
	sk = sk_aपंचांग(priv->lecd);
	skb_queue_tail(&sk->sk_receive_queue, skb);
	sk->sk_data_पढ़ोy(sk);

	अगर (data != शून्य) अणु
		pr_debug("about to send %d bytes of data\n", data->len);
		aपंचांग_क्रमce_अक्षरge(priv->lecd, data->truesize);
		skb_queue_tail(&sk->sk_receive_queue, data);
		sk->sk_data_पढ़ोy(sk);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lec_set_multicast_list(काष्ठा net_device *dev)
अणु
	/*
	 * by शेष, all multicast frames arrive over the bus.
	 * eventually support selective multicast service
	 */
पूर्ण

अटल स्थिर काष्ठा net_device_ops lec_netdev_ops = अणु
	.nकरो_खोलो		= lec_खोलो,
	.nकरो_stop		= lec_बंद,
	.nकरो_start_xmit		= lec_start_xmit,
	.nकरो_tx_समयout		= lec_tx_समयout,
	.nकरो_set_rx_mode	= lec_set_multicast_list,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर lec_ctrl_magic[] = अणु
	0xff,
	0x00,
	0x01,
	0x01
पूर्ण;

#घोषणा LEC_DATA_सूचीECT_8023  2
#घोषणा LEC_DATA_सूचीECT_8025  3

अटल पूर्णांक lec_is_data_direct(काष्ठा aपंचांग_vcc *vcc)
अणु
	वापस ((vcc->sap.blli[0].l3.tr9577.snap[4] == LEC_DATA_सूचीECT_8023) ||
		(vcc->sap.blli[0].l3.tr9577.snap[4] == LEC_DATA_सूचीECT_8025));
पूर्ण

अटल व्योम lec_push(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा net_device *dev = (काष्ठा net_device *)vcc->proto_data;
	काष्ठा lec_priv *priv = netdev_priv(dev);

#अगर DUMP_PACKETS > 0
	prपूर्णांकk(KERN_DEBUG "%s: vcc vpi:%d vci:%d\n",
	       dev->name, vcc->vpi, vcc->vci);
#पूर्ण_अगर
	अगर (!skb) अणु
		pr_debug("%s: null skb\n", dev->name);
		lec_vcc_बंद(priv, vcc);
		वापस;
	पूर्ण
#अगर DUMP_PACKETS >= 2
#घोषणा MAX_SKB_DUMP 99
#या_अगर DUMP_PACKETS >= 1
#घोषणा MAX_SKB_DUMP 30
#पूर्ण_अगर
#अगर DUMP_PACKETS > 0
	prपूर्णांकk(KERN_DEBUG "%s: rcv datalen:%ld lecid:%4.4x\n",
	       dev->name, skb->len, priv->lecid);
	prपूर्णांक_hex_dump(KERN_DEBUG, "", DUMP_OFFSET, 16, 1,
		       skb->data, min(MAX_SKB_DUMP, skb->len), true);
#पूर्ण_अगर /* DUMP_PACKETS > 0 */
	अगर (स_भेद(skb->data, lec_ctrl_magic, 4) == 0) अणु
				/* Control frame, to daemon */
		काष्ठा sock *sk = sk_aपंचांग(vcc);

		pr_debug("%s: To daemon\n", dev->name);
		skb_queue_tail(&sk->sk_receive_queue, skb);
		sk->sk_data_पढ़ोy(sk);
	पूर्ण अन्यथा अणु		/* Data frame, queue to protocol handlers */
		काष्ठा lec_arp_table *entry;
		अचिन्हित अक्षर *src, *dst;

		aपंचांग_वापस(vcc, skb->truesize);
		अगर (*(__be16 *) skb->data == htons(priv->lecid) ||
		    !priv->lecd || !(dev->flags & IFF_UP)) अणु
			/*
			 * Probably looping back, or अगर lecd is missing,
			 * lecd has gone करोwn
			 */
			pr_debug("Ignoring frame...\n");
			dev_kमुक्त_skb(skb);
			वापस;
		पूर्ण
		dst = ((काष्ठा lecdatahdr_8023 *)skb->data)->h_dest;

		/*
		 * If this is a Data Direct VCC, and the VCC करोes not match
		 * the LE_ARP cache entry, delete the LE_ARP cache entry.
		 */
		spin_lock_irqsave(&priv->lec_arp_lock, flags);
		अगर (lec_is_data_direct(vcc)) अणु
			src = ((काष्ठा lecdatahdr_8023 *)skb->data)->h_source;
			entry = lec_arp_find(priv, src);
			अगर (entry && entry->vcc != vcc) अणु
				lec_arp_हटाओ(priv, entry);
				lec_arp_put(entry);
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&priv->lec_arp_lock, flags);

		अगर (!(dst[0] & 0x01) &&	/* Never filter Multi/Broadcast */
		    !priv->is_proxy &&	/* Proxy wants all the packets */
		    स_भेद(dst, dev->dev_addr, dev->addr_len)) अणु
			dev_kमुक्त_skb(skb);
			वापस;
		पूर्ण
		अगर (!hlist_empty(&priv->lec_arp_empty_ones))
			lec_arp_check_empties(priv, vcc, skb);
		skb_pull(skb, 2);	/* skip lec_id */
		skb->protocol = eth_type_trans(skb, dev);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb->len;
		स_रखो(ATM_SKB(skb), 0, माप(काष्ठा aपंचांग_skb_data));
		netअगर_rx(skb);
	पूर्ण
पूर्ण

अटल व्योम lec_pop(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	काष्ठा lec_vcc_priv *vpriv = LEC_VCC_PRIV(vcc);
	काष्ठा net_device *dev = skb->dev;

	अगर (vpriv == शून्य) अणु
		pr_info("vpriv = NULL!?!?!?\n");
		वापस;
	पूर्ण

	vpriv->old_pop(vcc, skb);

	अगर (vpriv->xoff && aपंचांग_may_send(vcc, 0)) अणु
		vpriv->xoff = 0;
		अगर (netअगर_running(dev) && netअगर_queue_stopped(dev))
			netअगर_wake_queue(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक lec_vcc_attach(काष्ठा aपंचांग_vcc *vcc, व्योम __user *arg)
अणु
	काष्ठा lec_vcc_priv *vpriv;
	पूर्णांक bytes_left;
	काष्ठा aपंचांगlec_ioc ioc_data;

	/* Lecd must be up in this हाल */
	bytes_left = copy_from_user(&ioc_data, arg, माप(काष्ठा aपंचांगlec_ioc));
	अगर (bytes_left != 0)
		pr_info("copy from user failed for %d bytes\n", bytes_left);
	अगर (ioc_data.dev_num < 0 || ioc_data.dev_num >= MAX_LEC_ITF)
		वापस -EINVAL;
	ioc_data.dev_num = array_index_nospec(ioc_data.dev_num, MAX_LEC_ITF);
	अगर (!dev_lec[ioc_data.dev_num])
		वापस -EINVAL;
	vpriv = kदो_स्मृति(माप(काष्ठा lec_vcc_priv), GFP_KERNEL);
	अगर (!vpriv)
		वापस -ENOMEM;
	vpriv->xoff = 0;
	vpriv->old_pop = vcc->pop;
	vcc->user_back = vpriv;
	vcc->pop = lec_pop;
	lec_vcc_added(netdev_priv(dev_lec[ioc_data.dev_num]),
		      &ioc_data, vcc, vcc->push);
	vcc->proto_data = dev_lec[ioc_data.dev_num];
	vcc->push = lec_push;
	वापस 0;
पूर्ण

अटल पूर्णांक lec_mcast_attach(काष्ठा aपंचांग_vcc *vcc, पूर्णांक arg)
अणु
	अगर (arg < 0 || arg >= MAX_LEC_ITF)
		वापस -EINVAL;
	arg = array_index_nospec(arg, MAX_LEC_ITF);
	अगर (!dev_lec[arg])
		वापस -EINVAL;
	vcc->proto_data = dev_lec[arg];
	वापस lec_mcast_make(netdev_priv(dev_lec[arg]), vcc);
पूर्ण

/* Initialize device. */
अटल पूर्णांक lecd_attach(काष्ठा aपंचांग_vcc *vcc, पूर्णांक arg)
अणु
	पूर्णांक i;
	काष्ठा lec_priv *priv;

	अगर (arg < 0)
		arg = 0;
	अगर (arg >= MAX_LEC_ITF)
		वापस -EINVAL;
	i = array_index_nospec(arg, MAX_LEC_ITF);
	अगर (!dev_lec[i]) अणु
		पूर्णांक size;

		size = माप(काष्ठा lec_priv);
		dev_lec[i] = alloc_etherdev(size);
		अगर (!dev_lec[i])
			वापस -ENOMEM;
		dev_lec[i]->netdev_ops = &lec_netdev_ops;
		dev_lec[i]->max_mtu = 18190;
		snम_लिखो(dev_lec[i]->name, IFNAMSIZ, "lec%d", i);
		अगर (रेजिस्टर_netdev(dev_lec[i])) अणु
			मुक्त_netdev(dev_lec[i]);
			वापस -EINVAL;
		पूर्ण

		priv = netdev_priv(dev_lec[i]);
	पूर्ण अन्यथा अणु
		priv = netdev_priv(dev_lec[i]);
		अगर (priv->lecd)
			वापस -EADDRINUSE;
	पूर्ण
	lec_arp_init(priv);
	priv->itfnum = i;	/* LANE2 addition */
	priv->lecd = vcc;
	vcc->dev = &lecaपंचांग_dev;
	vcc_insert_socket(sk_aपंचांग(vcc));

	vcc->proto_data = dev_lec[i];
	set_bit(ATM_VF_META, &vcc->flags);
	set_bit(ATM_VF_READY, &vcc->flags);

	/* Set शेष values to these variables */
	priv->maximum_unknown_frame_count = 1;
	priv->max_unknown_frame_समय = (1 * HZ);
	priv->vcc_समयout_period = (1200 * HZ);
	priv->max_retry_count = 1;
	priv->aging_समय = (300 * HZ);
	priv->क्रमward_delay_समय = (15 * HZ);
	priv->topology_change = 0;
	priv->arp_response_समय = (1 * HZ);
	priv->flush_समयout = (4 * HZ);
	priv->path_चयनing_delay = (6 * HZ);

	अगर (dev_lec[i]->flags & IFF_UP)
		netअगर_start_queue(dev_lec[i]);
	__module_get(THIS_MODULE);
	वापस i;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल स्थिर अक्षर *lec_arp_get_status_string(अचिन्हित अक्षर status)
अणु
	अटल स्थिर अक्षर *स्थिर lec_arp_status_string[] = अणु
		"ESI_UNKNOWN       ",
		"ESI_ARP_PENDING   ",
		"ESI_VC_PENDING    ",
		"<Undefined>       ",
		"ESI_FLUSH_PENDING ",
		"ESI_FORWARD_DIRECT"
	पूर्ण;

	अगर (status > ESI_FORWARD_सूचीECT)
		status = 3;	/* ESI_UNDEFINED */
	वापस lec_arp_status_string[status];
पूर्ण

अटल व्योम lec_info(काष्ठा seq_file *seq, काष्ठा lec_arp_table *entry)
अणु
	seq_म_लिखो(seq, "%pM ", entry->mac_addr);
	seq_म_लिखो(seq, "%*phN ", ATM_ESA_LEN, entry->aपंचांग_addr);
	seq_म_लिखो(seq, "%s %4.4x", lec_arp_get_status_string(entry->status),
		   entry->flags & 0xffff);
	अगर (entry->vcc)
		seq_म_लिखो(seq, "%3d %3d ", entry->vcc->vpi, entry->vcc->vci);
	अन्यथा
		seq_म_लिखो(seq, "        ");
	अगर (entry->recv_vcc) अणु
		seq_म_लिखो(seq, "     %3d %3d", entry->recv_vcc->vpi,
			   entry->recv_vcc->vci);
	पूर्ण
	seq_अ_दो(seq, '\n');
पूर्ण

काष्ठा lec_state अणु
	अचिन्हित दीर्घ flags;
	काष्ठा lec_priv *locked;
	काष्ठा hlist_node *node;
	काष्ठा net_device *dev;
	पूर्णांक itf;
	पूर्णांक arp_table;
	पूर्णांक misc_table;
पूर्ण;

अटल व्योम *lec_tbl_walk(काष्ठा lec_state *state, काष्ठा hlist_head *tbl,
			  loff_t *l)
अणु
	काष्ठा hlist_node *e = state->node;

	अगर (!e)
		e = tbl->first;
	अगर (e == SEQ_START_TOKEN) अणु
		e = tbl->first;
		--*l;
	पूर्ण

	क्रम (; e; e = e->next) अणु
		अगर (--*l < 0)
			अवरोध;
	पूर्ण
	state->node = e;

	वापस (*l < 0) ? state : शून्य;
पूर्ण

अटल व्योम *lec_arp_walk(काष्ठा lec_state *state, loff_t *l,
			  काष्ठा lec_priv *priv)
अणु
	व्योम *v = शून्य;
	पूर्णांक p;

	क्रम (p = state->arp_table; p < LEC_ARP_TABLE_SIZE; p++) अणु
		v = lec_tbl_walk(state, &priv->lec_arp_tables[p], l);
		अगर (v)
			अवरोध;
	पूर्ण
	state->arp_table = p;
	वापस v;
पूर्ण

अटल व्योम *lec_misc_walk(काष्ठा lec_state *state, loff_t *l,
			   काष्ठा lec_priv *priv)
अणु
	काष्ठा hlist_head *lec_misc_tables[] = अणु
		&priv->lec_arp_empty_ones,
		&priv->lec_no_क्रमward,
		&priv->mcast_fwds
	पूर्ण;
	व्योम *v = शून्य;
	पूर्णांक q;

	क्रम (q = state->misc_table; q < ARRAY_SIZE(lec_misc_tables); q++) अणु
		v = lec_tbl_walk(state, lec_misc_tables[q], l);
		अगर (v)
			अवरोध;
	पूर्ण
	state->misc_table = q;
	वापस v;
पूर्ण

अटल व्योम *lec_priv_walk(काष्ठा lec_state *state, loff_t *l,
			   काष्ठा lec_priv *priv)
अणु
	अगर (!state->locked) अणु
		state->locked = priv;
		spin_lock_irqsave(&priv->lec_arp_lock, state->flags);
	पूर्ण
	अगर (!lec_arp_walk(state, l, priv) && !lec_misc_walk(state, l, priv)) अणु
		spin_unlock_irqrestore(&priv->lec_arp_lock, state->flags);
		state->locked = शून्य;
		/* Partial state reset क्रम the next समय we get called */
		state->arp_table = state->misc_table = 0;
	पूर्ण
	वापस state->locked;
पूर्ण

अटल व्योम *lec_itf_walk(काष्ठा lec_state *state, loff_t *l)
अणु
	काष्ठा net_device *dev;
	व्योम *v;

	dev = state->dev ? state->dev : dev_lec[state->itf];
	v = (dev && netdev_priv(dev)) ?
		lec_priv_walk(state, l, netdev_priv(dev)) : शून्य;
	अगर (!v && dev) अणु
		dev_put(dev);
		/* Partial state reset क्रम the next समय we get called */
		dev = शून्य;
	पूर्ण
	state->dev = dev;
	वापस v;
पूर्ण

अटल व्योम *lec_get_idx(काष्ठा lec_state *state, loff_t l)
अणु
	व्योम *v = शून्य;

	क्रम (; state->itf < MAX_LEC_ITF; state->itf++) अणु
		v = lec_itf_walk(state, &l);
		अगर (v)
			अवरोध;
	पूर्ण
	वापस v;
पूर्ण

अटल व्योम *lec_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा lec_state *state = seq->निजी;

	state->itf = 0;
	state->dev = शून्य;
	state->locked = शून्य;
	state->arp_table = 0;
	state->misc_table = 0;
	state->node = SEQ_START_TOKEN;

	वापस *pos ? lec_get_idx(state, *pos) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम lec_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा lec_state *state = seq->निजी;

	अगर (state->dev) अणु
		spin_unlock_irqrestore(&state->locked->lec_arp_lock,
				       state->flags);
		dev_put(state->dev);
	पूर्ण
पूर्ण

अटल व्योम *lec_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा lec_state *state = seq->निजी;

	++*pos;
	वापस lec_get_idx(state, 1);
पूर्ण

अटल पूर्णांक lec_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अटल स्थिर अक्षर lec_banner[] =
	    "Itf  MAC          ATM destination"
	    "                          Status            Flags "
	    "VPI/VCI Recv VPI/VCI\n";

	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, lec_banner);
	अन्यथा अणु
		काष्ठा lec_state *state = seq->निजी;
		काष्ठा net_device *dev = state->dev;
		काष्ठा lec_arp_table *entry = hlist_entry(state->node,
							  काष्ठा lec_arp_table,
							  next);

		seq_म_लिखो(seq, "%s ", dev->name);
		lec_info(seq, entry);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations lec_seq_ops = अणु
	.start = lec_seq_start,
	.next = lec_seq_next,
	.stop = lec_seq_stop,
	.show = lec_seq_show,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक lane_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा aपंचांग_vcc *vcc = ATM_SD(sock);
	पूर्णांक err = 0;

	चयन (cmd) अणु
	हाल ATMLEC_CTRL:
	हाल ATMLEC_MCAST:
	हाल ATMLEC_DATA:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अवरोध;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	चयन (cmd) अणु
	हाल ATMLEC_CTRL:
		err = lecd_attach(vcc, (पूर्णांक)arg);
		अगर (err >= 0)
			sock->state = SS_CONNECTED;
		अवरोध;
	हाल ATMLEC_MCAST:
		err = lec_mcast_attach(vcc, (पूर्णांक)arg);
		अवरोध;
	हाल ATMLEC_DATA:
		err = lec_vcc_attach(vcc, (व्योम __user *)arg);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा aपंचांग_ioctl lane_ioctl_ops = अणु
	.owner = THIS_MODULE,
	.ioctl = lane_ioctl,
पूर्ण;

अटल पूर्णांक __init lane_module_init(व्योम)
अणु
#अगर_घोषित CONFIG_PROC_FS
	काष्ठा proc_dir_entry *p;

	p = proc_create_seq_निजी("lec", 0444, aपंचांग_proc_root, &lec_seq_ops,
			माप(काष्ठा lec_state), शून्य);
	अगर (!p) अणु
		pr_err("Unable to initialize /proc/net/atm/lec\n");
		वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर

	रेजिस्टर_aपंचांग_ioctl(&lane_ioctl_ops);
	pr_info("lec.c: initialized\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास lane_module_cleanup(व्योम)
अणु
	पूर्णांक i;

#अगर_घोषित CONFIG_PROC_FS
	हटाओ_proc_entry("lec", aपंचांग_proc_root);
#पूर्ण_अगर

	deरेजिस्टर_aपंचांग_ioctl(&lane_ioctl_ops);

	क्रम (i = 0; i < MAX_LEC_ITF; i++) अणु
		अगर (dev_lec[i] != शून्य) अणु
			unरेजिस्टर_netdev(dev_lec[i]);
			मुक्त_netdev(dev_lec[i]);
			dev_lec[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

module_init(lane_module_init);
module_निकास(lane_module_cleanup);

/*
 * LANE2: 3.1.3, LE_RESOLVE.request
 * Non क्रमce allocates memory and fills in *tlvs, fills in *मापtlvs.
 * If मापtlvs == शून्य the शेष TLVs associated with this
 * lec will be used.
 * If dst_mac == शून्य, targetless LE_ARP will be sent
 */
अटल पूर्णांक lane2_resolve(काष्ठा net_device *dev, स्थिर u8 *dst_mac, पूर्णांक क्रमce,
			 u8 **tlvs, u32 *मापtlvs)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा lec_priv *priv = netdev_priv(dev);
	काष्ठा lec_arp_table *table;
	काष्ठा sk_buff *skb;
	पूर्णांक retval;

	अगर (क्रमce == 0) अणु
		spin_lock_irqsave(&priv->lec_arp_lock, flags);
		table = lec_arp_find(priv, dst_mac);
		spin_unlock_irqrestore(&priv->lec_arp_lock, flags);
		अगर (table == शून्य)
			वापस -1;

		*tlvs = kmemdup(table->tlvs, table->मापtlvs, GFP_ATOMIC);
		अगर (*tlvs == शून्य)
			वापस -1;

		*मापtlvs = table->मापtlvs;

		वापस 0;
	पूर्ण

	अगर (मापtlvs == शून्य)
		retval = send_to_lecd(priv, l_arp_xmt, dst_mac, शून्य, शून्य);

	अन्यथा अणु
		skb = alloc_skb(*मापtlvs, GFP_ATOMIC);
		अगर (skb == शून्य)
			वापस -1;
		skb->len = *मापtlvs;
		skb_copy_to_linear_data(skb, *tlvs, *मापtlvs);
		retval = send_to_lecd(priv, l_arp_xmt, dst_mac, शून्य, skb);
	पूर्ण
	वापस retval;
पूर्ण

/*
 * LANE2: 3.1.4, LE_ASSOCIATE.request
 * Associate the *tlvs with the *lan_dst address.
 * Will overग_लिखो any previous association
 * Returns 1 क्रम success, 0 क्रम failure (out of memory)
 *
 */
अटल पूर्णांक lane2_associate_req(काष्ठा net_device *dev, स्थिर u8 *lan_dst,
			       स्थिर u8 *tlvs, u32 मापtlvs)
अणु
	पूर्णांक retval;
	काष्ठा sk_buff *skb;
	काष्ठा lec_priv *priv = netdev_priv(dev);

	अगर (!ether_addr_equal(lan_dst, dev->dev_addr))
		वापस 0;	/* not our mac address */

	kमुक्त(priv->tlvs);	/* शून्य अगर there was no previous association */

	priv->tlvs = kmemdup(tlvs, मापtlvs, GFP_KERNEL);
	अगर (priv->tlvs == शून्य)
		वापस 0;
	priv->मापtlvs = मापtlvs;

	skb = alloc_skb(मापtlvs, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस 0;
	skb->len = मापtlvs;
	skb_copy_to_linear_data(skb, tlvs, मापtlvs);
	retval = send_to_lecd(priv, l_associate_req, शून्य, शून्य, skb);
	अगर (retval != 0)
		pr_info("lec.c: lane2_associate_req() failed\n");
	/*
	 * If the previous association has changed we must
	 * somehow notअगरy other LANE entities about the change
	 */
	वापस 1;
पूर्ण

/*
 * LANE2: 3.1.5, LE_ASSOCIATE.indication
 *
 */
अटल व्योम lane2_associate_ind(काष्ठा net_device *dev, स्थिर u8 *mac_addr,
				स्थिर u8 *tlvs, u32 मापtlvs)
अणु
#अगर 0
	पूर्णांक i = 0;
#पूर्ण_अगर
	काष्ठा lec_priv *priv = netdev_priv(dev);
#अगर 0				/*
				 * Why have the TLVs in LE_ARP entries
				 * since we करो not use them? When you
				 * uncomment this code, make sure the
				 * TLVs get मुक्तd when entry is समाप्तed
				 */
	काष्ठा lec_arp_table *entry = lec_arp_find(priv, mac_addr);

	अगर (entry == शून्य)
		वापस;		/* should not happen */

	kमुक्त(entry->tlvs);

	entry->tlvs = kmemdup(tlvs, मापtlvs, GFP_KERNEL);
	अगर (entry->tlvs == शून्य)
		वापस;
	entry->मापtlvs = मापtlvs;
#पूर्ण_अगर
#अगर 0
	pr_info("\n");
	pr_info("dump of tlvs, sizeoftlvs=%d\n", मापtlvs);
	जबतक (i < मापtlvs)
		pr_cont("%02x ", tlvs[i++]);

	pr_cont("\n");
#पूर्ण_अगर

	/* tell MPOA about the TLVs we saw */
	अगर (priv->lane2_ops && priv->lane2_ops->associate_indicator) अणु
		priv->lane2_ops->associate_indicator(dev, mac_addr,
						     tlvs, मापtlvs);
	पूर्ण
पूर्ण

/*
 * Here starts what used to lec_arpc.c
 *
 * lec_arpc.c was added here when making
 * lane client modular. October 1997
 */

#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/param.h>
#समावेश <linux/atomic.h>
#समावेश <linux/inetdevice.h>
#समावेश <net/route.h>

#अगर 0
#घोषणा pr_debug(क्रमmat, args...)
/*
  #घोषणा pr_debug prपूर्णांकk
*/
#पूर्ण_अगर
#घोषणा DEBUG_ARP_TABLE 0

#घोषणा LEC_ARP_REFRESH_INTERVAL (3*HZ)

अटल व्योम lec_arp_check_expire(काष्ठा work_काष्ठा *work);
अटल व्योम lec_arp_expire_arp(काष्ठा समयr_list *t);

/*
 * Arp table funcs
 */

#घोषणा HASH(ch) (ch & (LEC_ARP_TABLE_SIZE - 1))

/*
 * Initialization of arp-cache
 */
अटल व्योम lec_arp_init(काष्ठा lec_priv *priv)
अणु
	अचिन्हित लघु i;

	क्रम (i = 0; i < LEC_ARP_TABLE_SIZE; i++)
		INIT_HLIST_HEAD(&priv->lec_arp_tables[i]);
	INIT_HLIST_HEAD(&priv->lec_arp_empty_ones);
	INIT_HLIST_HEAD(&priv->lec_no_क्रमward);
	INIT_HLIST_HEAD(&priv->mcast_fwds);
	spin_lock_init(&priv->lec_arp_lock);
	INIT_DELAYED_WORK(&priv->lec_arp_work, lec_arp_check_expire);
	schedule_delayed_work(&priv->lec_arp_work, LEC_ARP_REFRESH_INTERVAL);
पूर्ण

अटल व्योम lec_arp_clear_vccs(काष्ठा lec_arp_table *entry)
अणु
	अगर (entry->vcc) अणु
		काष्ठा aपंचांग_vcc *vcc = entry->vcc;
		काष्ठा lec_vcc_priv *vpriv = LEC_VCC_PRIV(vcc);
		काष्ठा net_device *dev = (काष्ठा net_device *)vcc->proto_data;

		vcc->pop = vpriv->old_pop;
		अगर (vpriv->xoff)
			netअगर_wake_queue(dev);
		kमुक्त(vpriv);
		vcc->user_back = शून्य;
		vcc->push = entry->old_push;
		vcc_release_async(vcc, -EPIPE);
		entry->vcc = शून्य;
	पूर्ण
	अगर (entry->recv_vcc) अणु
		काष्ठा aपंचांग_vcc *vcc = entry->recv_vcc;
		काष्ठा lec_vcc_priv *vpriv = LEC_VCC_PRIV(vcc);

		kमुक्त(vpriv);
		vcc->user_back = शून्य;

		entry->recv_vcc->push = entry->old_recv_push;
		vcc_release_async(entry->recv_vcc, -EPIPE);
		entry->recv_vcc = शून्य;
	पूर्ण
पूर्ण

/*
 * Insert entry to lec_arp_table
 * LANE2: Add to the end of the list to satisfy 8.1.13
 */
अटल अंतरभूत व्योम
lec_arp_add(काष्ठा lec_priv *priv, काष्ठा lec_arp_table *entry)
अणु
	काष्ठा hlist_head *पंचांगp;

	पंचांगp = &priv->lec_arp_tables[HASH(entry->mac_addr[ETH_ALEN - 1])];
	hlist_add_head(&entry->next, पंचांगp);

	pr_debug("Added entry:%pM\n", entry->mac_addr);
पूर्ण

/*
 * Remove entry from lec_arp_table
 */
अटल पूर्णांक
lec_arp_हटाओ(काष्ठा lec_priv *priv, काष्ठा lec_arp_table *to_हटाओ)
अणु
	काष्ठा lec_arp_table *entry;
	पूर्णांक i, हटाओ_vcc = 1;

	अगर (!to_हटाओ)
		वापस -1;

	hlist_del(&to_हटाओ->next);
	del_समयr(&to_हटाओ->समयr);

	/*
	 * If this is the only MAC connected to this VCC,
	 * also tear करोwn the VCC
	 */
	अगर (to_हटाओ->status >= ESI_FLUSH_PENDING) अणु
		/*
		 * ESI_FLUSH_PENDING, ESI_FORWARD_सूचीECT
		 */
		क्रम (i = 0; i < LEC_ARP_TABLE_SIZE; i++) अणु
			hlist_क्रम_each_entry(entry,
					     &priv->lec_arp_tables[i], next) अणु
				अगर (स_भेद(to_हटाओ->aपंचांग_addr,
					   entry->aपंचांग_addr, ATM_ESA_LEN) == 0) अणु
					हटाओ_vcc = 0;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (हटाओ_vcc)
			lec_arp_clear_vccs(to_हटाओ);
	पूर्ण
	skb_queue_purge(&to_हटाओ->tx_रुको);	/* FIXME: good place क्रम this? */

	pr_debug("Removed entry:%pM\n", to_हटाओ->mac_addr);
	वापस 0;
पूर्ण

#अगर DEBUG_ARP_TABLE
अटल स्थिर अक्षर *get_status_string(अचिन्हित अक्षर st)
अणु
	चयन (st) अणु
	हाल ESI_UNKNOWN:
		वापस "ESI_UNKNOWN";
	हाल ESI_ARP_PENDING:
		वापस "ESI_ARP_PENDING";
	हाल ESI_VC_PENDING:
		वापस "ESI_VC_PENDING";
	हाल ESI_FLUSH_PENDING:
		वापस "ESI_FLUSH_PENDING";
	हाल ESI_FORWARD_सूचीECT:
		वापस "ESI_FORWARD_DIRECT";
	पूर्ण
	वापस "<UNKNOWN>";
पूर्ण

अटल व्योम dump_arp_table(काष्ठा lec_priv *priv)
अणु
	काष्ठा lec_arp_table *rulla;
	अक्षर buf[256];
	पूर्णांक i, offset;

	pr_info("Dump %p:\n", priv);
	क्रम (i = 0; i < LEC_ARP_TABLE_SIZE; i++) अणु
		hlist_क्रम_each_entry(rulla,
				     &priv->lec_arp_tables[i], next) अणु
			offset = 0;
			offset += प्र_लिखो(buf, "%d: %p\n", i, rulla);
			offset += प्र_लिखो(buf + offset, "Mac: %pM ",
					  rulla->mac_addr);
			offset += प्र_लिखो(buf + offset, "Atm: %*ph ", ATM_ESA_LEN,
					  rulla->aपंचांग_addr);
			offset += प्र_लिखो(buf + offset,
					  "Vcc vpi:%d vci:%d, Recv_vcc vpi:%d vci:%d Last_used:%lx, Timestamp:%lx, No_tries:%d ",
					  rulla->vcc ? rulla->vcc->vpi : 0,
					  rulla->vcc ? rulla->vcc->vci : 0,
					  rulla->recv_vcc ? rulla->recv_vcc->
					  vpi : 0,
					  rulla->recv_vcc ? rulla->recv_vcc->
					  vci : 0, rulla->last_used,
					  rulla->बारtamp, rulla->no_tries);
			offset +=
			    प्र_लिखो(buf + offset,
				    "Flags:%x, Packets_flooded:%x, Status: %s ",
				    rulla->flags, rulla->packets_flooded,
				    get_status_string(rulla->status));
			pr_info("%s\n", buf);
		पूर्ण
	पूर्ण

	अगर (!hlist_empty(&priv->lec_no_क्रमward))
		pr_info("No forward\n");
	hlist_क्रम_each_entry(rulla, &priv->lec_no_क्रमward, next) अणु
		offset = 0;
		offset += प्र_लिखो(buf + offset, "Mac: %pM ", rulla->mac_addr);
		offset += प्र_लिखो(buf + offset, "Atm: %*ph ", ATM_ESA_LEN,
				  rulla->aपंचांग_addr);
		offset += प्र_लिखो(buf + offset,
				  "Vcc vpi:%d vci:%d, Recv_vcc vpi:%d vci:%d Last_used:%lx, Timestamp:%lx, No_tries:%d ",
				  rulla->vcc ? rulla->vcc->vpi : 0,
				  rulla->vcc ? rulla->vcc->vci : 0,
				  rulla->recv_vcc ? rulla->recv_vcc->vpi : 0,
				  rulla->recv_vcc ? rulla->recv_vcc->vci : 0,
				  rulla->last_used,
				  rulla->बारtamp, rulla->no_tries);
		offset += प्र_लिखो(buf + offset,
				  "Flags:%x, Packets_flooded:%x, Status: %s ",
				  rulla->flags, rulla->packets_flooded,
				  get_status_string(rulla->status));
		pr_info("%s\n", buf);
	पूर्ण

	अगर (!hlist_empty(&priv->lec_arp_empty_ones))
		pr_info("Empty ones\n");
	hlist_क्रम_each_entry(rulla, &priv->lec_arp_empty_ones, next) अणु
		offset = 0;
		offset += प्र_लिखो(buf + offset, "Mac: %pM ", rulla->mac_addr);
		offset += प्र_लिखो(buf + offset, "Atm: %*ph ", ATM_ESA_LEN,
				  rulla->aपंचांग_addr);
		offset += प्र_लिखो(buf + offset,
				  "Vcc vpi:%d vci:%d, Recv_vcc vpi:%d vci:%d Last_used:%lx, Timestamp:%lx, No_tries:%d ",
				  rulla->vcc ? rulla->vcc->vpi : 0,
				  rulla->vcc ? rulla->vcc->vci : 0,
				  rulla->recv_vcc ? rulla->recv_vcc->vpi : 0,
				  rulla->recv_vcc ? rulla->recv_vcc->vci : 0,
				  rulla->last_used,
				  rulla->बारtamp, rulla->no_tries);
		offset += प्र_लिखो(buf + offset,
				  "Flags:%x, Packets_flooded:%x, Status: %s ",
				  rulla->flags, rulla->packets_flooded,
				  get_status_string(rulla->status));
		pr_info("%s", buf);
	पूर्ण

	अगर (!hlist_empty(&priv->mcast_fwds))
		pr_info("Multicast Forward VCCs\n");
	hlist_क्रम_each_entry(rulla, &priv->mcast_fwds, next) अणु
		offset = 0;
		offset += प्र_लिखो(buf + offset, "Mac: %pM ", rulla->mac_addr);
		offset += प्र_लिखो(buf + offset, "Atm: %*ph ", ATM_ESA_LEN,
				  rulla->aपंचांग_addr);
		offset += प्र_लिखो(buf + offset,
				  "Vcc vpi:%d vci:%d, Recv_vcc vpi:%d vci:%d Last_used:%lx, Timestamp:%lx, No_tries:%d ",
				  rulla->vcc ? rulla->vcc->vpi : 0,
				  rulla->vcc ? rulla->vcc->vci : 0,
				  rulla->recv_vcc ? rulla->recv_vcc->vpi : 0,
				  rulla->recv_vcc ? rulla->recv_vcc->vci : 0,
				  rulla->last_used,
				  rulla->बारtamp, rulla->no_tries);
		offset += प्र_लिखो(buf + offset,
				  "Flags:%x, Packets_flooded:%x, Status: %s ",
				  rulla->flags, rulla->packets_flooded,
				  get_status_string(rulla->status));
		pr_info("%s\n", buf);
	पूर्ण

पूर्ण
#अन्यथा
#घोषणा dump_arp_table(priv) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * Deकाष्ठाion of arp-cache
 */
अटल व्योम lec_arp_destroy(काष्ठा lec_priv *priv)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hlist_node *next;
	काष्ठा lec_arp_table *entry;
	पूर्णांक i;

	cancel_delayed_work_sync(&priv->lec_arp_work);

	/*
	 * Remove all entries
	 */

	spin_lock_irqsave(&priv->lec_arp_lock, flags);
	क्रम (i = 0; i < LEC_ARP_TABLE_SIZE; i++) अणु
		hlist_क्रम_each_entry_safe(entry, next,
					  &priv->lec_arp_tables[i], next) अणु
			lec_arp_हटाओ(priv, entry);
			lec_arp_put(entry);
		पूर्ण
		INIT_HLIST_HEAD(&priv->lec_arp_tables[i]);
	पूर्ण

	hlist_क्रम_each_entry_safe(entry, next,
				  &priv->lec_arp_empty_ones, next) अणु
		del_समयr_sync(&entry->समयr);
		lec_arp_clear_vccs(entry);
		hlist_del(&entry->next);
		lec_arp_put(entry);
	पूर्ण
	INIT_HLIST_HEAD(&priv->lec_arp_empty_ones);

	hlist_क्रम_each_entry_safe(entry, next,
				  &priv->lec_no_क्रमward, next) अणु
		del_समयr_sync(&entry->समयr);
		lec_arp_clear_vccs(entry);
		hlist_del(&entry->next);
		lec_arp_put(entry);
	पूर्ण
	INIT_HLIST_HEAD(&priv->lec_no_क्रमward);

	hlist_क्रम_each_entry_safe(entry, next, &priv->mcast_fwds, next) अणु
		/* No समयr, LANEv2 7.1.20 and 2.3.5.3 */
		lec_arp_clear_vccs(entry);
		hlist_del(&entry->next);
		lec_arp_put(entry);
	पूर्ण
	INIT_HLIST_HEAD(&priv->mcast_fwds);
	priv->mcast_vcc = शून्य;
	spin_unlock_irqrestore(&priv->lec_arp_lock, flags);
पूर्ण

/*
 * Find entry by mac_address
 */
अटल काष्ठा lec_arp_table *lec_arp_find(काष्ठा lec_priv *priv,
					  स्थिर अचिन्हित अक्षर *mac_addr)
अणु
	काष्ठा hlist_head *head;
	काष्ठा lec_arp_table *entry;

	pr_debug("%pM\n", mac_addr);

	head = &priv->lec_arp_tables[HASH(mac_addr[ETH_ALEN - 1])];
	hlist_क्रम_each_entry(entry, head, next) अणु
		अगर (ether_addr_equal(mac_addr, entry->mac_addr))
			वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा lec_arp_table *make_entry(काष्ठा lec_priv *priv,
					स्थिर अचिन्हित अक्षर *mac_addr)
अणु
	काष्ठा lec_arp_table *to_वापस;

	to_वापस = kzalloc(माप(काष्ठा lec_arp_table), GFP_ATOMIC);
	अगर (!to_वापस)
		वापस शून्य;
	ether_addr_copy(to_वापस->mac_addr, mac_addr);
	INIT_HLIST_NODE(&to_वापस->next);
	समयr_setup(&to_वापस->समयr, lec_arp_expire_arp, 0);
	to_वापस->last_used = jअगरfies;
	to_वापस->priv = priv;
	skb_queue_head_init(&to_वापस->tx_रुको);
	refcount_set(&to_वापस->usage, 1);
	वापस to_वापस;
पूर्ण

/* Arp sent समयr expired */
अटल व्योम lec_arp_expire_arp(काष्ठा समयr_list *t)
अणु
	काष्ठा lec_arp_table *entry;

	entry = from_समयr(entry, t, समयr);

	pr_debug("\n");
	अगर (entry->status == ESI_ARP_PENDING) अणु
		अगर (entry->no_tries <= entry->priv->max_retry_count) अणु
			अगर (entry->is_rdesc)
				send_to_lecd(entry->priv, l_rdesc_arp_xmt,
					     entry->mac_addr, शून्य, शून्य);
			अन्यथा
				send_to_lecd(entry->priv, l_arp_xmt,
					     entry->mac_addr, शून्य, शून्य);
			entry->no_tries++;
		पूर्ण
		mod_समयr(&entry->समयr, jअगरfies + (1 * HZ));
	पूर्ण
पूर्ण

/* Unknown/unused vcc expire, हटाओ associated entry */
अटल व्योम lec_arp_expire_vcc(काष्ठा समयr_list *t)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा lec_arp_table *to_हटाओ = from_समयr(to_हटाओ, t, समयr);
	काष्ठा lec_priv *priv = to_हटाओ->priv;

	del_समयr(&to_हटाओ->समयr);

	pr_debug("%p %p: vpi:%d vci:%d\n",
		 to_हटाओ, priv,
		 to_हटाओ->vcc ? to_हटाओ->recv_vcc->vpi : 0,
		 to_हटाओ->vcc ? to_हटाओ->recv_vcc->vci : 0);

	spin_lock_irqsave(&priv->lec_arp_lock, flags);
	hlist_del(&to_हटाओ->next);
	spin_unlock_irqrestore(&priv->lec_arp_lock, flags);

	lec_arp_clear_vccs(to_हटाओ);
	lec_arp_put(to_हटाओ);
पूर्ण

अटल bool __lec_arp_check_expire(काष्ठा lec_arp_table *entry,
				   अचिन्हित दीर्घ now,
				   काष्ठा lec_priv *priv)
अणु
	अचिन्हित दीर्घ समय_प्रकारo_check;

	अगर ((entry->flags) & LEC_REMOTE_FLAG && priv->topology_change)
		समय_प्रकारo_check = priv->क्रमward_delay_समय;
	अन्यथा
		समय_प्रकारo_check = priv->aging_समय;

	pr_debug("About to expire: %lx - %lx > %lx\n",
		 now, entry->last_used, समय_प्रकारo_check);
	अगर (समय_after(now, entry->last_used + समय_प्रकारo_check) &&
	    !(entry->flags & LEC_PERMANENT_FLAG) &&
	    !(entry->mac_addr[0] & 0x01)) अणु	/* LANE2: 7.1.20 */
		/* Remove entry */
		pr_debug("Entry timed out\n");
		lec_arp_हटाओ(priv, entry);
		lec_arp_put(entry);
	पूर्ण अन्यथा अणु
		/* Something अन्यथा */
		अगर ((entry->status == ESI_VC_PENDING ||
		     entry->status == ESI_ARP_PENDING) &&
		    समय_after_eq(now, entry->बारtamp +
				       priv->max_unknown_frame_समय)) अणु
			entry->बारtamp = jअगरfies;
			entry->packets_flooded = 0;
			अगर (entry->status == ESI_VC_PENDING)
				send_to_lecd(priv, l_svc_setup,
					     entry->mac_addr,
					     entry->aपंचांग_addr,
					     शून्य);
		पूर्ण
		अगर (entry->status == ESI_FLUSH_PENDING &&
		    समय_after_eq(now, entry->बारtamp +
				       priv->path_चयनing_delay)) अणु
			lec_arp_hold(entry);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण
/*
 * Expire entries.
 * 1. Re-set समयr
 * 2. For each entry, delete entries that have aged past the age limit.
 * 3. For each entry, depending on the status of the entry, perक्रमm
 *    the following मुख्यtenance.
 *    a. If status is ESI_VC_PENDING or ESI_ARP_PENDING then अगर the
 *       tick_count is above the max_unknown_frame_समय, clear
 *       the tick_count to zero and clear the packets_flooded counter
 *       to zero. This supports the packet rate limit per address
 *       जबतक flooding unknowns.
 *    b. If the status is ESI_FLUSH_PENDING and the tick_count is greater
 *       than or equal to the path_चयनing_delay, change the status
 *       to ESI_FORWARD_सूचीECT. This causes the flush period to end
 *       regardless of the progress of the flush protocol.
 */
अटल व्योम lec_arp_check_expire(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा lec_priv *priv =
		container_of(work, काष्ठा lec_priv, lec_arp_work.work);
	काष्ठा hlist_node *next;
	काष्ठा lec_arp_table *entry;
	अचिन्हित दीर्घ now;
	पूर्णांक i;

	pr_debug("%p\n", priv);
	now = jअगरfies;
restart:
	spin_lock_irqsave(&priv->lec_arp_lock, flags);
	क्रम (i = 0; i < LEC_ARP_TABLE_SIZE; i++) अणु
		hlist_क्रम_each_entry_safe(entry, next,
					  &priv->lec_arp_tables[i], next) अणु
			अगर (__lec_arp_check_expire(entry, now, priv)) अणु
				काष्ठा sk_buff *skb;
				काष्ठा aपंचांग_vcc *vcc = entry->vcc;

				spin_unlock_irqrestore(&priv->lec_arp_lock,
						       flags);
				जबतक ((skb = skb_dequeue(&entry->tx_रुको)))
					lec_send(vcc, skb);
				entry->last_used = jअगरfies;
				entry->status = ESI_FORWARD_सूचीECT;
				lec_arp_put(entry);

				जाओ restart;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&priv->lec_arp_lock, flags);

	schedule_delayed_work(&priv->lec_arp_work, LEC_ARP_REFRESH_INTERVAL);
पूर्ण

/*
 * Try to find vcc where mac_address is attached.
 *
 */
अटल काष्ठा aपंचांग_vcc *lec_arp_resolve(काष्ठा lec_priv *priv,
				       स्थिर अचिन्हित अक्षर *mac_to_find,
				       पूर्णांक is_rdesc,
				       काष्ठा lec_arp_table **ret_entry)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा lec_arp_table *entry;
	काष्ठा aपंचांग_vcc *found;

	अगर (mac_to_find[0] & 0x01) अणु
		चयन (priv->lane_version) अणु
		हाल 1:
			वापस priv->mcast_vcc;
		हाल 2:	/* LANE2 wants arp क्रम multicast addresses */
			अगर (ether_addr_equal(mac_to_find, bus_mac))
				वापस priv->mcast_vcc;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&priv->lec_arp_lock, flags);
	entry = lec_arp_find(priv, mac_to_find);

	अगर (entry) अणु
		अगर (entry->status == ESI_FORWARD_सूचीECT) अणु
			/* Connection Ok */
			entry->last_used = jअगरfies;
			lec_arp_hold(entry);
			*ret_entry = entry;
			found = entry->vcc;
			जाओ out;
		पूर्ण
		/*
		 * If the LE_ARP cache entry is still pending, reset count to 0
		 * so another LE_ARP request can be made क्रम this frame.
		 */
		अगर (entry->status == ESI_ARP_PENDING)
			entry->no_tries = 0;
		/*
		 * Data direct VC not yet set up, check to see अगर the unknown
		 * frame count is greater than the limit. If the limit has
		 * not been reached, allow the caller to send packet to
		 * BUS.
		 */
		अगर (entry->status != ESI_FLUSH_PENDING &&
		    entry->packets_flooded <
		    priv->maximum_unknown_frame_count) अणु
			entry->packets_flooded++;
			pr_debug("Flooding..\n");
			found = priv->mcast_vcc;
			जाओ out;
		पूर्ण
		/*
		 * We got here because entry->status == ESI_FLUSH_PENDING
		 * or BUS flood limit was reached क्रम an entry which is
		 * in ESI_ARP_PENDING or ESI_VC_PENDING state.
		 */
		lec_arp_hold(entry);
		*ret_entry = entry;
		pr_debug("entry->status %d entry->vcc %p\n", entry->status,
			 entry->vcc);
		found = शून्य;
	पूर्ण अन्यथा अणु
		/* No matching entry was found */
		entry = make_entry(priv, mac_to_find);
		pr_debug("Making entry\n");
		अगर (!entry) अणु
			found = priv->mcast_vcc;
			जाओ out;
		पूर्ण
		lec_arp_add(priv, entry);
		/* We want arp-request(s) to be sent */
		entry->packets_flooded = 1;
		entry->status = ESI_ARP_PENDING;
		entry->no_tries = 1;
		entry->last_used = entry->बारtamp = jअगरfies;
		entry->is_rdesc = is_rdesc;
		अगर (entry->is_rdesc)
			send_to_lecd(priv, l_rdesc_arp_xmt, mac_to_find, शून्य,
				     शून्य);
		अन्यथा
			send_to_lecd(priv, l_arp_xmt, mac_to_find, शून्य, शून्य);
		entry->समयr.expires = jअगरfies + (1 * HZ);
		entry->समयr.function = lec_arp_expire_arp;
		add_समयr(&entry->समयr);
		found = priv->mcast_vcc;
	पूर्ण

out:
	spin_unlock_irqrestore(&priv->lec_arp_lock, flags);
	वापस found;
पूर्ण

अटल पूर्णांक
lec_addr_delete(काष्ठा lec_priv *priv, स्थिर अचिन्हित अक्षर *aपंचांग_addr,
		अचिन्हित दीर्घ permanent)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hlist_node *next;
	काष्ठा lec_arp_table *entry;
	पूर्णांक i;

	pr_debug("\n");
	spin_lock_irqsave(&priv->lec_arp_lock, flags);
	क्रम (i = 0; i < LEC_ARP_TABLE_SIZE; i++) अणु
		hlist_क्रम_each_entry_safe(entry, next,
					  &priv->lec_arp_tables[i], next) अणु
			अगर (!स_भेद(aपंचांग_addr, entry->aपंचांग_addr, ATM_ESA_LEN) &&
			    (permanent ||
			     !(entry->flags & LEC_PERMANENT_FLAG))) अणु
				lec_arp_हटाओ(priv, entry);
				lec_arp_put(entry);
			पूर्ण
			spin_unlock_irqrestore(&priv->lec_arp_lock, flags);
			वापस 0;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&priv->lec_arp_lock, flags);
	वापस -1;
पूर्ण

/*
 * Notअगरies:  Response to arp_request (aपंचांग_addr != शून्य)
 */
अटल व्योम
lec_arp_update(काष्ठा lec_priv *priv, स्थिर अचिन्हित अक्षर *mac_addr,
	       स्थिर अचिन्हित अक्षर *aपंचांग_addr, अचिन्हित दीर्घ remoteflag,
	       अचिन्हित पूर्णांक targetless_le_arp)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hlist_node *next;
	काष्ठा lec_arp_table *entry, *पंचांगp;
	पूर्णांक i;

	pr_debug("%smac:%pM\n",
		 (targetless_le_arp) ? "targetless " : "", mac_addr);

	spin_lock_irqsave(&priv->lec_arp_lock, flags);
	entry = lec_arp_find(priv, mac_addr);
	अगर (entry == शून्य && targetless_le_arp)
		जाओ out;	/*
				 * LANE2: ignore targetless LE_ARPs क्रम which
				 * we have no entry in the cache. 7.1.30
				 */
	अगर (!hlist_empty(&priv->lec_arp_empty_ones)) अणु
		hlist_क्रम_each_entry_safe(entry, next,
					  &priv->lec_arp_empty_ones, next) अणु
			अगर (स_भेद(entry->aपंचांग_addr, aपंचांग_addr, ATM_ESA_LEN) == 0) अणु
				hlist_del(&entry->next);
				del_समयr(&entry->समयr);
				पंचांगp = lec_arp_find(priv, mac_addr);
				अगर (पंचांगp) अणु
					del_समयr(&पंचांगp->समयr);
					पंचांगp->status = ESI_FORWARD_सूचीECT;
					स_नकल(पंचांगp->aपंचांग_addr, aपंचांग_addr, ATM_ESA_LEN);
					पंचांगp->vcc = entry->vcc;
					पंचांगp->old_push = entry->old_push;
					पंचांगp->last_used = jअगरfies;
					del_समयr(&entry->समयr);
					lec_arp_put(entry);
					entry = पंचांगp;
				पूर्ण अन्यथा अणु
					entry->status = ESI_FORWARD_सूचीECT;
					ether_addr_copy(entry->mac_addr,
							mac_addr);
					entry->last_used = jअगरfies;
					lec_arp_add(priv, entry);
				पूर्ण
				अगर (remoteflag)
					entry->flags |= LEC_REMOTE_FLAG;
				अन्यथा
					entry->flags &= ~LEC_REMOTE_FLAG;
				pr_debug("After update\n");
				dump_arp_table(priv);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	entry = lec_arp_find(priv, mac_addr);
	अगर (!entry) अणु
		entry = make_entry(priv, mac_addr);
		अगर (!entry)
			जाओ out;
		entry->status = ESI_UNKNOWN;
		lec_arp_add(priv, entry);
		/* Temporary, changes beक्रमe end of function */
	पूर्ण
	स_नकल(entry->aपंचांग_addr, aपंचांग_addr, ATM_ESA_LEN);
	del_समयr(&entry->समयr);
	क्रम (i = 0; i < LEC_ARP_TABLE_SIZE; i++) अणु
		hlist_क्रम_each_entry(पंचांगp,
				     &priv->lec_arp_tables[i], next) अणु
			अगर (entry != पंचांगp &&
			    !स_भेद(पंचांगp->aपंचांग_addr, aपंचांग_addr, ATM_ESA_LEN)) अणु
				/* Vcc to this host exists */
				अगर (पंचांगp->status > ESI_VC_PENDING) अणु
					/*
					 * ESI_FLUSH_PENDING,
					 * ESI_FORWARD_सूचीECT
					 */
					entry->vcc = पंचांगp->vcc;
					entry->old_push = पंचांगp->old_push;
				पूर्ण
				entry->status = पंचांगp->status;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (remoteflag)
		entry->flags |= LEC_REMOTE_FLAG;
	अन्यथा
		entry->flags &= ~LEC_REMOTE_FLAG;
	अगर (entry->status == ESI_ARP_PENDING || entry->status == ESI_UNKNOWN) अणु
		entry->status = ESI_VC_PENDING;
		send_to_lecd(priv, l_svc_setup, entry->mac_addr, aपंचांग_addr, शून्य);
	पूर्ण
	pr_debug("After update2\n");
	dump_arp_table(priv);
out:
	spin_unlock_irqrestore(&priv->lec_arp_lock, flags);
पूर्ण

/*
 * Notअगरies: Vcc setup पढ़ोy
 */
अटल व्योम
lec_vcc_added(काष्ठा lec_priv *priv, स्थिर काष्ठा aपंचांगlec_ioc *ioc_data,
	      काष्ठा aपंचांग_vcc *vcc,
	      व्योम (*old_push) (काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb))
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा lec_arp_table *entry;
	पूर्णांक i, found_entry = 0;

	spin_lock_irqsave(&priv->lec_arp_lock, flags);
	/* Vcc क्रम Multicast Forward. No समयr, LANEv2 7.1.20 and 2.3.5.3 */
	अगर (ioc_data->receive == 2) अणु
		pr_debug("LEC_ARP: Attaching mcast forward\n");
#अगर 0
		entry = lec_arp_find(priv, bus_mac);
		अगर (!entry) अणु
			pr_info("LEC_ARP: Multicast entry not found!\n");
			जाओ out;
		पूर्ण
		स_नकल(entry->aपंचांग_addr, ioc_data->aपंचांग_addr, ATM_ESA_LEN);
		entry->recv_vcc = vcc;
		entry->old_recv_push = old_push;
#पूर्ण_अगर
		entry = make_entry(priv, bus_mac);
		अगर (entry == शून्य)
			जाओ out;
		del_समयr(&entry->समयr);
		स_नकल(entry->aपंचांग_addr, ioc_data->aपंचांग_addr, ATM_ESA_LEN);
		entry->recv_vcc = vcc;
		entry->old_recv_push = old_push;
		hlist_add_head(&entry->next, &priv->mcast_fwds);
		जाओ out;
	पूर्ण अन्यथा अगर (ioc_data->receive == 1) अणु
		/*
		 * Vcc which we करोn't want to make शेष vcc,
		 * attach it anyway.
		 */
		pr_debug("LEC_ARP:Attaching data direct, not default: %*phN\n",
			 ATM_ESA_LEN, ioc_data->aपंचांग_addr);
		entry = make_entry(priv, bus_mac);
		अगर (entry == शून्य)
			जाओ out;
		स_नकल(entry->aपंचांग_addr, ioc_data->aपंचांग_addr, ATM_ESA_LEN);
		eth_zero_addr(entry->mac_addr);
		entry->recv_vcc = vcc;
		entry->old_recv_push = old_push;
		entry->status = ESI_UNKNOWN;
		entry->समयr.expires = jअगरfies + priv->vcc_समयout_period;
		entry->समयr.function = lec_arp_expire_vcc;
		hlist_add_head(&entry->next, &priv->lec_no_क्रमward);
		add_समयr(&entry->समयr);
		dump_arp_table(priv);
		जाओ out;
	पूर्ण
	pr_debug("LEC_ARP:Attaching data direct, default: %*phN\n",
		 ATM_ESA_LEN, ioc_data->aपंचांग_addr);
	क्रम (i = 0; i < LEC_ARP_TABLE_SIZE; i++) अणु
		hlist_क्रम_each_entry(entry,
				     &priv->lec_arp_tables[i], next) अणु
			अगर (स_भेद
			    (ioc_data->aपंचांग_addr, entry->aपंचांग_addr,
			     ATM_ESA_LEN) == 0) अणु
				pr_debug("LEC_ARP: Attaching data direct\n");
				pr_debug("Currently -> Vcc: %d, Rvcc:%d\n",
					 entry->vcc ? entry->vcc->vci : 0,
					 entry->recv_vcc ? entry->recv_vcc->
					 vci : 0);
				found_entry = 1;
				del_समयr(&entry->समयr);
				entry->vcc = vcc;
				entry->old_push = old_push;
				अगर (entry->status == ESI_VC_PENDING) अणु
					अगर (priv->maximum_unknown_frame_count
					    == 0)
						entry->status =
						    ESI_FORWARD_सूचीECT;
					अन्यथा अणु
						entry->बारtamp = jअगरfies;
						entry->status =
						    ESI_FLUSH_PENDING;
#अगर 0
						send_to_lecd(priv, l_flush_xmt,
							     शून्य,
							     entry->aपंचांग_addr,
							     शून्य);
#पूर्ण_अगर
					पूर्ण
				पूर्ण अन्यथा अणु
					/*
					 * They were क्रमming a connection
					 * to us, and we to them. Our
					 * ATM address is numerically lower
					 * than theirs, so we make connection
					 * we क्रमmed पूर्णांकo शेष VCC (8.1.11).
					 * Connection they made माला_लो torn
					 * करोwn. This might confuse some
					 * clients. Can be changed अगर
					 * someone reports trouble...
					 */
					;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (found_entry) अणु
		pr_debug("After vcc was added\n");
		dump_arp_table(priv);
		जाओ out;
	पूर्ण
	/*
	 * Not found, snatch address from first data packet that arrives
	 * from this vcc
	 */
	entry = make_entry(priv, bus_mac);
	अगर (!entry)
		जाओ out;
	entry->vcc = vcc;
	entry->old_push = old_push;
	स_नकल(entry->aपंचांग_addr, ioc_data->aपंचांग_addr, ATM_ESA_LEN);
	eth_zero_addr(entry->mac_addr);
	entry->status = ESI_UNKNOWN;
	hlist_add_head(&entry->next, &priv->lec_arp_empty_ones);
	entry->समयr.expires = jअगरfies + priv->vcc_समयout_period;
	entry->समयr.function = lec_arp_expire_vcc;
	add_समयr(&entry->समयr);
	pr_debug("After vcc was added\n");
	dump_arp_table(priv);
out:
	spin_unlock_irqrestore(&priv->lec_arp_lock, flags);
पूर्ण

अटल व्योम lec_flush_complete(काष्ठा lec_priv *priv, अचिन्हित दीर्घ tran_id)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा lec_arp_table *entry;
	पूर्णांक i;

	pr_debug("%lx\n", tran_id);
restart:
	spin_lock_irqsave(&priv->lec_arp_lock, flags);
	क्रम (i = 0; i < LEC_ARP_TABLE_SIZE; i++) अणु
		hlist_क्रम_each_entry(entry,
				     &priv->lec_arp_tables[i], next) अणु
			अगर (entry->flush_tran_id == tran_id &&
			    entry->status == ESI_FLUSH_PENDING) अणु
				काष्ठा sk_buff *skb;
				काष्ठा aपंचांग_vcc *vcc = entry->vcc;

				lec_arp_hold(entry);
				spin_unlock_irqrestore(&priv->lec_arp_lock,
						       flags);
				जबतक ((skb = skb_dequeue(&entry->tx_रुको)))
					lec_send(vcc, skb);
				entry->last_used = jअगरfies;
				entry->status = ESI_FORWARD_सूचीECT;
				lec_arp_put(entry);
				pr_debug("LEC_ARP: Flushed\n");
				जाओ restart;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&priv->lec_arp_lock, flags);
	dump_arp_table(priv);
पूर्ण

अटल व्योम
lec_set_flush_tran_id(काष्ठा lec_priv *priv,
		      स्थिर अचिन्हित अक्षर *aपंचांग_addr, अचिन्हित दीर्घ tran_id)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा lec_arp_table *entry;
	पूर्णांक i;

	spin_lock_irqsave(&priv->lec_arp_lock, flags);
	क्रम (i = 0; i < LEC_ARP_TABLE_SIZE; i++)
		hlist_क्रम_each_entry(entry,
				     &priv->lec_arp_tables[i], next) अणु
			अगर (!स_भेद(aपंचांग_addr, entry->aपंचांग_addr, ATM_ESA_LEN)) अणु
				entry->flush_tran_id = tran_id;
				pr_debug("Set flush transaction id to %lx for %p\n",
					 tran_id, entry);
			पूर्ण
		पूर्ण
	spin_unlock_irqrestore(&priv->lec_arp_lock, flags);
पूर्ण

अटल पूर्णांक lec_mcast_make(काष्ठा lec_priv *priv, काष्ठा aपंचांग_vcc *vcc)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर mac_addr[] = अणु
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	पूर्ण;
	काष्ठा lec_arp_table *to_add;
	काष्ठा lec_vcc_priv *vpriv;
	पूर्णांक err = 0;

	vpriv = kदो_स्मृति(माप(काष्ठा lec_vcc_priv), GFP_KERNEL);
	अगर (!vpriv)
		वापस -ENOMEM;
	vpriv->xoff = 0;
	vpriv->old_pop = vcc->pop;
	vcc->user_back = vpriv;
	vcc->pop = lec_pop;
	spin_lock_irqsave(&priv->lec_arp_lock, flags);
	to_add = make_entry(priv, mac_addr);
	अगर (!to_add) अणु
		vcc->pop = vpriv->old_pop;
		kमुक्त(vpriv);
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	स_नकल(to_add->aपंचांग_addr, vcc->remote.sas_addr.prv, ATM_ESA_LEN);
	to_add->status = ESI_FORWARD_सूचीECT;
	to_add->flags |= LEC_PERMANENT_FLAG;
	to_add->vcc = vcc;
	to_add->old_push = vcc->push;
	vcc->push = lec_push;
	priv->mcast_vcc = vcc;
	lec_arp_add(priv, to_add);
out:
	spin_unlock_irqrestore(&priv->lec_arp_lock, flags);
	वापस err;
पूर्ण

अटल व्योम lec_vcc_बंद(काष्ठा lec_priv *priv, काष्ठा aपंचांग_vcc *vcc)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hlist_node *next;
	काष्ठा lec_arp_table *entry;
	पूर्णांक i;

	pr_debug("LEC_ARP: lec_vcc_close vpi:%d vci:%d\n", vcc->vpi, vcc->vci);
	dump_arp_table(priv);

	spin_lock_irqsave(&priv->lec_arp_lock, flags);

	क्रम (i = 0; i < LEC_ARP_TABLE_SIZE; i++) अणु
		hlist_क्रम_each_entry_safe(entry, next,
					  &priv->lec_arp_tables[i], next) अणु
			अगर (vcc == entry->vcc) अणु
				lec_arp_हटाओ(priv, entry);
				lec_arp_put(entry);
				अगर (priv->mcast_vcc == vcc)
					priv->mcast_vcc = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	hlist_क्रम_each_entry_safe(entry, next,
				  &priv->lec_arp_empty_ones, next) अणु
		अगर (entry->vcc == vcc) अणु
			lec_arp_clear_vccs(entry);
			del_समयr(&entry->समयr);
			hlist_del(&entry->next);
			lec_arp_put(entry);
		पूर्ण
	पूर्ण

	hlist_क्रम_each_entry_safe(entry, next,
				  &priv->lec_no_क्रमward, next) अणु
		अगर (entry->recv_vcc == vcc) अणु
			lec_arp_clear_vccs(entry);
			del_समयr(&entry->समयr);
			hlist_del(&entry->next);
			lec_arp_put(entry);
		पूर्ण
	पूर्ण

	hlist_क्रम_each_entry_safe(entry, next, &priv->mcast_fwds, next) अणु
		अगर (entry->recv_vcc == vcc) अणु
			lec_arp_clear_vccs(entry);
			/* No समयr, LANEv2 7.1.20 and 2.3.5.3 */
			hlist_del(&entry->next);
			lec_arp_put(entry);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&priv->lec_arp_lock, flags);
	dump_arp_table(priv);
पूर्ण

अटल व्योम
lec_arp_check_empties(काष्ठा lec_priv *priv,
		      काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hlist_node *next;
	काष्ठा lec_arp_table *entry, *पंचांगp;
	काष्ठा lecdatahdr_8023 *hdr = (काष्ठा lecdatahdr_8023 *)skb->data;
	अचिन्हित अक्षर *src = hdr->h_source;

	spin_lock_irqsave(&priv->lec_arp_lock, flags);
	hlist_क्रम_each_entry_safe(entry, next,
				  &priv->lec_arp_empty_ones, next) अणु
		अगर (vcc == entry->vcc) अणु
			del_समयr(&entry->समयr);
			ether_addr_copy(entry->mac_addr, src);
			entry->status = ESI_FORWARD_सूचीECT;
			entry->last_used = jअगरfies;
			/* We might have got an entry */
			पंचांगp = lec_arp_find(priv, src);
			अगर (पंचांगp) अणु
				lec_arp_हटाओ(priv, पंचांगp);
				lec_arp_put(पंचांगp);
			पूर्ण
			hlist_del(&entry->next);
			lec_arp_add(priv, entry);
			जाओ out;
		पूर्ण
	पूर्ण
	pr_debug("LEC_ARP: Arp_check_empties: entry not found!\n");
out:
	spin_unlock_irqrestore(&priv->lec_arp_lock, flags);
पूर्ण

MODULE_LICENSE("GPL");
