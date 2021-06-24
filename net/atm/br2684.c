<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Ethernet netdevice using ATM AAL5 as underlying carrier
 * (RFC1483 obsoleted by RFC2684) क्रम Linux
 *
 * Authors: Marcell GAL, 2000, XDSL Ltd, Hungary
 *          Eric Kinzie, 2006-2007, US Naval Research Laboratory
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/ip.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <net/arp.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/capability.h>
#समावेश <linux/seq_file.h>

#समावेश <linux/aपंचांगbr2684.h>

#समावेश "common.h"

अटल व्योम skb_debug(स्थिर काष्ठा sk_buff *skb)
अणु
#अगर_घोषित SKB_DEBUG
#घोषणा NUM2PRINT 50
	prपूर्णांक_hex_dump(KERN_DEBUG, "br2684: skb: ", DUMP_OFFSET,
		       16, 1, skb->data, min(NUM2PRINT, skb->len), true);
#पूर्ण_अगर
पूर्ण

#घोषणा BR2684_ETHERTYPE_LEN	2
#घोषणा BR2684_PAD_LEN		2

#घोषणा LLC		0xaa, 0xaa, 0x03
#घोषणा SNAP_BRIDGED	0x00, 0x80, 0xc2
#घोषणा SNAP_ROUTED	0x00, 0x00, 0x00
#घोषणा PID_ETHERNET	0x00, 0x07
#घोषणा ETHERTYPE_IPV4	0x08, 0x00
#घोषणा ETHERTYPE_IPV6	0x86, 0xdd
#घोषणा PAD_BRIDGED	0x00, 0x00

अटल स्थिर अचिन्हित अक्षर ethertype_ipv4[] = अणु ETHERTYPE_IPV4 पूर्ण;
अटल स्थिर अचिन्हित अक्षर ethertype_ipv6[] = अणु ETHERTYPE_IPV6 पूर्ण;
अटल स्थिर अचिन्हित अक्षर llc_oui_pid_pad[] =
			अणु LLC, SNAP_BRIDGED, PID_ETHERNET, PAD_BRIDGED पूर्ण;
अटल स्थिर अचिन्हित अक्षर pad[] = अणु PAD_BRIDGED पूर्ण;
अटल स्थिर अचिन्हित अक्षर llc_oui_ipv4[] = अणु LLC, SNAP_ROUTED, ETHERTYPE_IPV4 पूर्ण;
अटल स्थिर अचिन्हित अक्षर llc_oui_ipv6[] = अणु LLC, SNAP_ROUTED, ETHERTYPE_IPV6 पूर्ण;

क्रमागत br2684_encaps अणु
	e_vc = BR2684_ENCAPS_VC,
	e_llc = BR2684_ENCAPS_LLC,
पूर्ण;

काष्ठा br2684_vcc अणु
	काष्ठा aपंचांग_vcc *aपंचांगvcc;
	काष्ठा net_device *device;
	/* keep old push, pop functions क्रम chaining */
	व्योम (*old_push)(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb);
	व्योम (*old_pop)(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb);
	व्योम (*old_release_cb)(काष्ठा aपंचांग_vcc *vcc);
	काष्ठा module *old_owner;
	क्रमागत br2684_encaps encaps;
	काष्ठा list_head brvccs;
#अगर_घोषित CONFIG_ATM_BR2684_IPFILTER
	काष्ठा br2684_filter filter;
#पूर्ण_अगर /* CONFIG_ATM_BR2684_IPFILTER */
	अचिन्हित पूर्णांक copies_needed, copies_failed;
	atomic_t qspace;
पूर्ण;

काष्ठा br2684_dev अणु
	काष्ठा net_device *net_dev;
	काष्ठा list_head br2684_devs;
	पूर्णांक number;
	काष्ठा list_head brvccs;	/* one device <=> one vcc (beक्रमe xmas) */
	पूर्णांक mac_was_set;
	क्रमागत br2684_payload payload;
पूर्ण;

/*
 * This lock should be held क्रम writing any समय the list of devices or
 * their attached vcc's could be altered.  It should be held क्रम पढ़ोing
 * any समय these are being queried.  Note that we someबार need to
 * करो पढ़ो-locking under पूर्णांकerrupt context, so ग_लिखो locking must block
 * the current CPU's पूर्णांकerrupts
 */
अटल DEFINE_RWLOCK(devs_lock);

अटल LIST_HEAD(br2684_devs);

अटल अंतरभूत काष्ठा br2684_dev *BRPRIV(स्थिर काष्ठा net_device *net_dev)
अणु
	वापस netdev_priv(net_dev);
पूर्ण

अटल अंतरभूत काष्ठा net_device *list_entry_brdev(स्थिर काष्ठा list_head *le)
अणु
	वापस list_entry(le, काष्ठा br2684_dev, br2684_devs)->net_dev;
पूर्ण

अटल अंतरभूत काष्ठा br2684_vcc *BR2684_VCC(स्थिर काष्ठा aपंचांग_vcc *aपंचांगvcc)
अणु
	वापस (काष्ठा br2684_vcc *)(aपंचांगvcc->user_back);
पूर्ण

अटल अंतरभूत काष्ठा br2684_vcc *list_entry_brvcc(स्थिर काष्ठा list_head *le)
अणु
	वापस list_entry(le, काष्ठा br2684_vcc, brvccs);
पूर्ण

/* Caller should hold पढ़ो_lock(&devs_lock) */
अटल काष्ठा net_device *br2684_find_dev(स्थिर काष्ठा br2684_अगर_spec *s)
अणु
	काष्ठा list_head *lh;
	काष्ठा net_device *net_dev;
	चयन (s->method) अणु
	हाल BR2684_FIND_BYNUM:
		list_क्रम_each(lh, &br2684_devs) अणु
			net_dev = list_entry_brdev(lh);
			अगर (BRPRIV(net_dev)->number == s->spec.devnum)
				वापस net_dev;
		पूर्ण
		अवरोध;
	हाल BR2684_FIND_BYIFNAME:
		list_क्रम_each(lh, &br2684_devs) अणु
			net_dev = list_entry_brdev(lh);
			अगर (!म_भेदन(net_dev->name, s->spec.अगरname, IFNAMSIZ))
				वापस net_dev;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक aपंचांग_dev_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
		 व्योम *arg)
अणु
	काष्ठा aपंचांग_dev *aपंचांग_dev = arg;
	काष्ठा list_head *lh;
	काष्ठा net_device *net_dev;
	काष्ठा br2684_vcc *brvcc;
	काष्ठा aपंचांग_vcc *aपंचांग_vcc;
	अचिन्हित दीर्घ flags;

	pr_debug("event=%ld dev=%p\n", event, aपंचांग_dev);

	पढ़ो_lock_irqsave(&devs_lock, flags);
	list_क्रम_each(lh, &br2684_devs) अणु
		net_dev = list_entry_brdev(lh);

		list_क्रम_each_entry(brvcc, &BRPRIV(net_dev)->brvccs, brvccs) अणु
			aपंचांग_vcc = brvcc->aपंचांगvcc;
			अगर (aपंचांग_vcc && brvcc->aपंचांगvcc->dev == aपंचांग_dev) अणु

				अगर (aपंचांग_vcc->dev->संकेत == ATM_PHY_SIG_LOST)
					netअगर_carrier_off(net_dev);
				अन्यथा
					netअगर_carrier_on(net_dev);

			पूर्ण
		पूर्ण
	पूर्ण
	पढ़ो_unlock_irqrestore(&devs_lock, flags);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block aपंचांग_dev_notअगरier = अणु
	.notअगरier_call = aपंचांग_dev_event,
पूर्ण;

/* chained vcc->pop function.  Check अगर we should wake the netअगर_queue */
अटल व्योम br2684_pop(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	काष्ठा br2684_vcc *brvcc = BR2684_VCC(vcc);

	pr_debug("(vcc %p ; net_dev %p )\n", vcc, brvcc->device);
	brvcc->old_pop(vcc, skb);

	/* If the queue space just went up from zero, wake */
	अगर (atomic_inc_वापस(&brvcc->qspace) == 1)
		netअगर_wake_queue(brvcc->device);
पूर्ण

/*
 * Send a packet out a particular vcc.  Not to useful right now, but paves
 * the way क्रम multiple vcc's per itf.  Returns true अगर we can send,
 * otherwise false
 */
अटल पूर्णांक br2684_xmit_vcc(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			   काष्ठा br2684_vcc *brvcc)
अणु
	काष्ठा br2684_dev *brdev = BRPRIV(dev);
	काष्ठा aपंचांग_vcc *aपंचांगvcc;
	पूर्णांक minheadroom = (brvcc->encaps == e_llc) ?
		((brdev->payload == p_bridged) ?
			माप(llc_oui_pid_pad) : माप(llc_oui_ipv4)) :
		((brdev->payload == p_bridged) ? BR2684_PAD_LEN : 0);

	अगर (skb_headroom(skb) < minheadroom) अणु
		काष्ठा sk_buff *skb2 = skb_पुनः_स्मृति_headroom(skb, minheadroom);
		brvcc->copies_needed++;
		dev_kमुक्त_skb(skb);
		अगर (skb2 == शून्य) अणु
			brvcc->copies_failed++;
			वापस 0;
		पूर्ण
		skb = skb2;
	पूर्ण

	अगर (brvcc->encaps == e_llc) अणु
		अगर (brdev->payload == p_bridged) अणु
			skb_push(skb, माप(llc_oui_pid_pad));
			skb_copy_to_linear_data(skb, llc_oui_pid_pad,
						माप(llc_oui_pid_pad));
		पूर्ण अन्यथा अगर (brdev->payload == p_routed) अणु
			अचिन्हित लघु prot = ntohs(skb->protocol);

			skb_push(skb, माप(llc_oui_ipv4));
			चयन (prot) अणु
			हाल ETH_P_IP:
				skb_copy_to_linear_data(skb, llc_oui_ipv4,
							माप(llc_oui_ipv4));
				अवरोध;
			हाल ETH_P_IPV6:
				skb_copy_to_linear_data(skb, llc_oui_ipv6,
							माप(llc_oui_ipv6));
				अवरोध;
			शेष:
				dev_kमुक्त_skb(skb);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु /* e_vc */
		अगर (brdev->payload == p_bridged) अणु
			skb_push(skb, 2);
			स_रखो(skb->data, 0, 2);
		पूर्ण
	पूर्ण
	skb_debug(skb);

	ATM_SKB(skb)->vcc = aपंचांगvcc = brvcc->aपंचांगvcc;
	pr_debug("atm_skb(%p)->vcc(%p)->dev(%p)\n", skb, aपंचांगvcc, aपंचांगvcc->dev);
	aपंचांग_account_tx(aपंचांगvcc, skb);
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	अगर (atomic_dec_वापस(&brvcc->qspace) < 1) अणु
		/* No more please! */
		netअगर_stop_queue(brvcc->device);
		/* We might have raced with br2684_pop() */
		अगर (unlikely(atomic_पढ़ो(&brvcc->qspace) > 0))
			netअगर_wake_queue(brvcc->device);
	पूर्ण

	/* If this fails immediately, the skb will be मुक्तd and br2684_pop()
	   will wake the queue अगर appropriate. Just वापस an error so that
	   the stats are updated correctly */
	वापस !aपंचांगvcc->send(aपंचांगvcc, skb);
पूर्ण

अटल व्योम br2684_release_cb(काष्ठा aपंचांग_vcc *aपंचांगvcc)
अणु
	काष्ठा br2684_vcc *brvcc = BR2684_VCC(aपंचांगvcc);

	अगर (atomic_पढ़ो(&brvcc->qspace) > 0)
		netअगर_wake_queue(brvcc->device);

	अगर (brvcc->old_release_cb)
		brvcc->old_release_cb(aपंचांगvcc);
पूर्ण

अटल अंतरभूत काष्ठा br2684_vcc *pick_outgoing_vcc(स्थिर काष्ठा sk_buff *skb,
						   स्थिर काष्ठा br2684_dev *brdev)
अणु
	वापस list_empty(&brdev->brvccs) ? शून्य : list_entry_brvcc(brdev->brvccs.next);	/* 1 vcc/dev right now */
पूर्ण

अटल netdev_tx_t br2684_start_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev)
अणु
	काष्ठा br2684_dev *brdev = BRPRIV(dev);
	काष्ठा br2684_vcc *brvcc;
	काष्ठा aपंचांग_vcc *aपंचांगvcc;
	netdev_tx_t ret = NETDEV_TX_OK;

	pr_debug("skb_dst(skb)=%p\n", skb_dst(skb));
	पढ़ो_lock(&devs_lock);
	brvcc = pick_outgoing_vcc(skb, brdev);
	अगर (brvcc == शून्य) अणु
		pr_debug("no vcc attached to dev %s\n", dev->name);
		dev->stats.tx_errors++;
		dev->stats.tx_carrier_errors++;
		/* netअगर_stop_queue(dev); */
		dev_kमुक्त_skb(skb);
		जाओ out_devs;
	पूर्ण
	aपंचांगvcc = brvcc->aपंचांगvcc;

	bh_lock_sock(sk_aपंचांग(aपंचांगvcc));

	अगर (test_bit(ATM_VF_RELEASED, &aपंचांगvcc->flags) ||
	    test_bit(ATM_VF_CLOSE, &aपंचांगvcc->flags) ||
	    !test_bit(ATM_VF_READY, &aपंचांगvcc->flags)) अणु
		dev->stats.tx_dropped++;
		dev_kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	अगर (sock_owned_by_user(sk_aपंचांग(aपंचांगvcc))) अणु
		netअगर_stop_queue(brvcc->device);
		ret = NETDEV_TX_BUSY;
		जाओ out;
	पूर्ण

	अगर (!br2684_xmit_vcc(skb, dev, brvcc)) अणु
		/*
		 * We should probably use netअगर_*_queue() here, but that
		 * involves added complication.  We need to walk beक्रमe
		 * we can run.
		 *
		 * Don't मुक्त here! this poपूर्णांकer might be no दीर्घer valid!
		 */
		dev->stats.tx_errors++;
		dev->stats.tx_fअगरo_errors++;
	पूर्ण
 out:
	bh_unlock_sock(sk_aपंचांग(aपंचांगvcc));
 out_devs:
	पढ़ो_unlock(&devs_lock);
	वापस ret;
पूर्ण

/*
 * We remember when the MAC माला_लो set, so we करोn't override it later with
 * the ESI of the ATM card of the first VC
 */
अटल पूर्णांक br2684_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	पूर्णांक err = eth_mac_addr(dev, p);
	अगर (!err)
		BRPRIV(dev)->mac_was_set = 1;
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_ATM_BR2684_IPFILTER
/* this IOCTL is experimental. */
अटल पूर्णांक br2684_setfilt(काष्ठा aपंचांग_vcc *aपंचांगvcc, व्योम __user * arg)
अणु
	काष्ठा br2684_vcc *brvcc;
	काष्ठा br2684_filter_set fs;

	अगर (copy_from_user(&fs, arg, माप fs))
		वापस -EFAULT;
	अगर (fs.अगरspec.method != BR2684_FIND_BYNOTHING) अणु
		/*
		 * This is really a per-vcc thing, but we can also search
		 * by device.
		 */
		काष्ठा br2684_dev *brdev;
		पढ़ो_lock(&devs_lock);
		brdev = BRPRIV(br2684_find_dev(&fs.अगरspec));
		अगर (brdev == शून्य || list_empty(&brdev->brvccs) ||
		    brdev->brvccs.next != brdev->brvccs.prev)	/* >1 VCC */
			brvcc = शून्य;
		अन्यथा
			brvcc = list_entry_brvcc(brdev->brvccs.next);
		पढ़ो_unlock(&devs_lock);
		अगर (brvcc == शून्य)
			वापस -ESRCH;
	पूर्ण अन्यथा
		brvcc = BR2684_VCC(aपंचांगvcc);
	स_नकल(&brvcc->filter, &fs.filter, माप(brvcc->filter));
	वापस 0;
पूर्ण

/* Returns 1 अगर packet should be dropped */
अटल अंतरभूत पूर्णांक
packet_fails_filter(__be16 type, काष्ठा br2684_vcc *brvcc, काष्ठा sk_buff *skb)
अणु
	अगर (brvcc->filter.neपंचांगask == 0)
		वापस 0;	/* no filter in place */
	अगर (type == htons(ETH_P_IP) &&
	    (((काष्ठा iphdr *)(skb->data))->daddr & brvcc->filter.
	     neपंचांगask) == brvcc->filter.prefix)
		वापस 0;
	अगर (type == htons(ETH_P_ARP))
		वापस 0;
	/*
	 * TODO: we should probably filter ARPs too.. करोn't want to have
	 * them वापसing values that करोn't make sense, or is that ok?
	 */
	वापस 1;		/* drop */
पूर्ण
#पूर्ण_अगर /* CONFIG_ATM_BR2684_IPFILTER */

अटल व्योम br2684_बंद_vcc(काष्ठा br2684_vcc *brvcc)
अणु
	pr_debug("removing VCC %p from dev %p\n", brvcc, brvcc->device);
	ग_लिखो_lock_irq(&devs_lock);
	list_del(&brvcc->brvccs);
	ग_लिखो_unlock_irq(&devs_lock);
	brvcc->aपंचांगvcc->user_back = शून्य;	/* what about vcc->recvq ??? */
	brvcc->aपंचांगvcc->release_cb = brvcc->old_release_cb;
	brvcc->old_push(brvcc->aपंचांगvcc, शून्य);	/* pass on the bad news */
	module_put(brvcc->old_owner);
	kमुक्त(brvcc);
पूर्ण

/* when AAL5 PDU comes in: */
अटल व्योम br2684_push(काष्ठा aपंचांग_vcc *aपंचांगvcc, काष्ठा sk_buff *skb)
अणु
	काष्ठा br2684_vcc *brvcc = BR2684_VCC(aपंचांगvcc);
	काष्ठा net_device *net_dev = brvcc->device;
	काष्ठा br2684_dev *brdev = BRPRIV(net_dev);

	pr_debug("\n");

	अगर (unlikely(skb == शून्य)) अणु
		/* skb==शून्य means VCC is being destroyed */
		br2684_बंद_vcc(brvcc);
		अगर (list_empty(&brdev->brvccs)) अणु
			ग_लिखो_lock_irq(&devs_lock);
			list_del(&brdev->br2684_devs);
			ग_लिखो_unlock_irq(&devs_lock);
			unरेजिस्टर_netdev(net_dev);
			मुक्त_netdev(net_dev);
		पूर्ण
		वापस;
	पूर्ण

	skb_debug(skb);
	aपंचांग_वापस(aपंचांगvcc, skb->truesize);
	pr_debug("skb from brdev %p\n", brdev);
	अगर (brvcc->encaps == e_llc) अणु

		अगर (skb->len > 7 && skb->data[7] == 0x01)
			__skb_trim(skb, skb->len - 4);

		/* accept packets that have "ipv[46]" in the snap header */
		अगर ((skb->len >= (माप(llc_oui_ipv4))) &&
		    (स_भेद(skb->data, llc_oui_ipv4,
			    माप(llc_oui_ipv4) - BR2684_ETHERTYPE_LEN) == 0)) अणु
			अगर (स_भेद(skb->data + 6, ethertype_ipv6,
				   माप(ethertype_ipv6)) == 0)
				skb->protocol = htons(ETH_P_IPV6);
			अन्यथा अगर (स_भेद(skb->data + 6, ethertype_ipv4,
					माप(ethertype_ipv4)) == 0)
				skb->protocol = htons(ETH_P_IP);
			अन्यथा
				जाओ error;
			skb_pull(skb, माप(llc_oui_ipv4));
			skb_reset_network_header(skb);
			skb->pkt_type = PACKET_HOST;
		/*
		 * Let us waste some समय क्रम checking the encapsulation.
		 * Note, that only 7 अक्षर is checked so frames with a valid FCS
		 * are also accepted (but FCS is not checked of course).
		 */
		पूर्ण अन्यथा अगर ((skb->len >= माप(llc_oui_pid_pad)) &&
			   (स_भेद(skb->data, llc_oui_pid_pad, 7) == 0)) अणु
			skb_pull(skb, माप(llc_oui_pid_pad));
			skb->protocol = eth_type_trans(skb, net_dev);
		पूर्ण अन्यथा
			जाओ error;

	पूर्ण अन्यथा अणु /* e_vc */
		अगर (brdev->payload == p_routed) अणु
			काष्ठा iphdr *iph;

			skb_reset_network_header(skb);
			iph = ip_hdr(skb);
			अगर (iph->version == 4)
				skb->protocol = htons(ETH_P_IP);
			अन्यथा अगर (iph->version == 6)
				skb->protocol = htons(ETH_P_IPV6);
			अन्यथा
				जाओ error;
			skb->pkt_type = PACKET_HOST;
		पूर्ण अन्यथा अणु /* p_bridged */
			/* first 2 अक्षरs should be 0 */
			अगर (स_भेद(skb->data, pad, BR2684_PAD_LEN) != 0)
				जाओ error;
			skb_pull(skb, BR2684_PAD_LEN);
			skb->protocol = eth_type_trans(skb, net_dev);
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_ATM_BR2684_IPFILTER
	अगर (unlikely(packet_fails_filter(skb->protocol, brvcc, skb)))
		जाओ dropped;
#पूर्ण_अगर /* CONFIG_ATM_BR2684_IPFILTER */
	skb->dev = net_dev;
	ATM_SKB(skb)->vcc = aपंचांगvcc;	/* needed ? */
	pr_debug("received packet's protocol: %x\n", ntohs(skb->protocol));
	skb_debug(skb);
	/* sigh, पूर्णांकerface is करोwn? */
	अगर (unlikely(!(net_dev->flags & IFF_UP)))
		जाओ dropped;
	net_dev->stats.rx_packets++;
	net_dev->stats.rx_bytes += skb->len;
	स_रखो(ATM_SKB(skb), 0, माप(काष्ठा aपंचांग_skb_data));
	netअगर_rx(skb);
	वापस;

dropped:
	net_dev->stats.rx_dropped++;
	जाओ मुक्त_skb;
error:
	net_dev->stats.rx_errors++;
मुक्त_skb:
	dev_kमुक्त_skb(skb);
पूर्ण

/*
 * Assign a vcc to a dev
 * Note: we करो not have explicit unassign, but look at _push()
 */
अटल पूर्णांक br2684_regvcc(काष्ठा aपंचांग_vcc *aपंचांगvcc, व्योम __user * arg)
अणु
	काष्ठा br2684_vcc *brvcc;
	काष्ठा br2684_dev *brdev;
	काष्ठा net_device *net_dev;
	काष्ठा aपंचांग_backend_br2684 be;
	पूर्णांक err;

	अगर (copy_from_user(&be, arg, माप be))
		वापस -EFAULT;
	brvcc = kzalloc(माप(काष्ठा br2684_vcc), GFP_KERNEL);
	अगर (!brvcc)
		वापस -ENOMEM;
	/*
	 * Allow two packets in the ATM queue. One actually being sent, and one
	 * क्रम the ATM 'TX done' handler to send. It shouldn't take दीर्घ to get
	 * the next one from the netdev queue, when we need it. More than that
	 * would be bufferbloat.
	 */
	atomic_set(&brvcc->qspace, 2);
	ग_लिखो_lock_irq(&devs_lock);
	net_dev = br2684_find_dev(&be.अगरspec);
	अगर (net_dev == शून्य) अणु
		pr_err("tried to attach to non-existent device\n");
		err = -ENXIO;
		जाओ error;
	पूर्ण
	brdev = BRPRIV(net_dev);
	अगर (aपंचांगvcc->push == शून्य) अणु
		err = -EBADFD;
		जाओ error;
	पूर्ण
	अगर (!list_empty(&brdev->brvccs)) अणु
		/* Only 1 VCC/dev right now */
		err = -EEXIST;
		जाओ error;
	पूर्ण
	अगर (be.fcs_in != BR2684_FCSIN_NO ||
	    be.fcs_out != BR2684_FCSOUT_NO ||
	    be.fcs_स्वतः || be.has_vpiid || be.send_padding ||
	    (be.encaps != BR2684_ENCAPS_VC &&
	     be.encaps != BR2684_ENCAPS_LLC) ||
	    be.min_size != 0) अणु
		err = -EINVAL;
		जाओ error;
	पूर्ण
	pr_debug("vcc=%p, encaps=%d, brvcc=%p\n", aपंचांगvcc, be.encaps, brvcc);
	अगर (list_empty(&brdev->brvccs) && !brdev->mac_was_set) अणु
		अचिन्हित अक्षर *esi = aपंचांगvcc->dev->esi;
		अगर (esi[0] | esi[1] | esi[2] | esi[3] | esi[4] | esi[5])
			स_नकल(net_dev->dev_addr, esi, net_dev->addr_len);
		अन्यथा
			net_dev->dev_addr[2] = 1;
	पूर्ण
	list_add(&brvcc->brvccs, &brdev->brvccs);
	ग_लिखो_unlock_irq(&devs_lock);
	brvcc->device = net_dev;
	brvcc->aपंचांगvcc = aपंचांगvcc;
	aपंचांगvcc->user_back = brvcc;
	brvcc->encaps = (क्रमागत br2684_encaps)be.encaps;
	brvcc->old_push = aपंचांगvcc->push;
	brvcc->old_pop = aपंचांगvcc->pop;
	brvcc->old_release_cb = aपंचांगvcc->release_cb;
	brvcc->old_owner = aपंचांगvcc->owner;
	barrier();
	aपंचांगvcc->push = br2684_push;
	aपंचांगvcc->pop = br2684_pop;
	aपंचांगvcc->release_cb = br2684_release_cb;
	aपंचांगvcc->owner = THIS_MODULE;

	/* initialize netdev carrier state */
	अगर (aपंचांगvcc->dev->संकेत == ATM_PHY_SIG_LOST)
		netअगर_carrier_off(net_dev);
	अन्यथा
		netअगर_carrier_on(net_dev);

	__module_get(THIS_MODULE);

	/* re-process everything received between connection setup and
	   backend setup */
	vcc_process_recv_queue(aपंचांगvcc);
	वापस 0;

error:
	ग_लिखो_unlock_irq(&devs_lock);
	kमुक्त(brvcc);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा net_device_ops br2684_netdev_ops = अणु
	.nकरो_start_xmit 	= br2684_start_xmit,
	.nकरो_set_mac_address	= br2684_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops br2684_netdev_ops_routed = अणु
	.nकरो_start_xmit 	= br2684_start_xmit,
	.nकरो_set_mac_address	= br2684_mac_addr,
पूर्ण;

अटल व्योम br2684_setup(काष्ठा net_device *netdev)
अणु
	काष्ठा br2684_dev *brdev = BRPRIV(netdev);

	ether_setup(netdev);
	netdev->hard_header_len += माप(llc_oui_pid_pad); /* worst हाल */
	brdev->net_dev = netdev;

	netdev->netdev_ops = &br2684_netdev_ops;

	INIT_LIST_HEAD(&brdev->brvccs);
पूर्ण

अटल व्योम br2684_setup_routed(काष्ठा net_device *netdev)
अणु
	काष्ठा br2684_dev *brdev = BRPRIV(netdev);

	brdev->net_dev = netdev;
	netdev->hard_header_len = माप(llc_oui_ipv4); /* worst हाल */
	netdev->netdev_ops = &br2684_netdev_ops_routed;
	netdev->addr_len = 0;
	netdev->mtu = ETH_DATA_LEN;
	netdev->min_mtu = 0;
	netdev->max_mtu = ETH_MAX_MTU;
	netdev->type = ARPHRD_PPP;
	netdev->flags = IFF_POINTOPOINT | IFF_NOARP | IFF_MULTICAST;
	netdev->tx_queue_len = 100;
	INIT_LIST_HEAD(&brdev->brvccs);
पूर्ण

अटल पूर्णांक br2684_create(व्योम __user *arg)
अणु
	पूर्णांक err;
	काष्ठा net_device *netdev;
	काष्ठा br2684_dev *brdev;
	काष्ठा aपंचांग_newअगर_br2684 ni;
	क्रमागत br2684_payload payload;

	pr_debug("\n");

	अगर (copy_from_user(&ni, arg, माप ni))
		वापस -EFAULT;

	अगर (ni.media & BR2684_FLAG_ROUTED)
		payload = p_routed;
	अन्यथा
		payload = p_bridged;
	ni.media &= 0xffff;	/* strip flags */

	अगर (ni.media != BR2684_MEDIA_ETHERNET || ni.mtu != 1500)
		वापस -EINVAL;

	netdev = alloc_netdev(माप(काष्ठा br2684_dev),
			      ni.अगरname[0] ? ni.अगरname : "nas%d",
			      NET_NAME_UNKNOWN,
			      (payload == p_routed) ? br2684_setup_routed : br2684_setup);
	अगर (!netdev)
		वापस -ENOMEM;

	brdev = BRPRIV(netdev);

	pr_debug("registered netdev %s\n", netdev->name);
	/* खोलो, stop, करो_ioctl ? */
	err = रेजिस्टर_netdev(netdev);
	अगर (err < 0) अणु
		pr_err("register_netdev failed\n");
		मुक्त_netdev(netdev);
		वापस err;
	पूर्ण

	ग_लिखो_lock_irq(&devs_lock);

	brdev->payload = payload;

	अगर (list_empty(&br2684_devs)) अणु
		/* 1st br2684 device */
		brdev->number = 1;
	पूर्ण अन्यथा
		brdev->number = BRPRIV(list_entry_brdev(br2684_devs.prev))->number + 1;

	list_add_tail(&brdev->br2684_devs, &br2684_devs);
	ग_लिखो_unlock_irq(&devs_lock);
	वापस 0;
पूर्ण

/*
 * This handles ioctls actually perक्रमmed on our vcc - we must वापस
 * -ENOIOCTLCMD क्रम any unrecognized ioctl
 */
अटल पूर्णांक br2684_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	काष्ठा aपंचांग_vcc *aपंचांगvcc = ATM_SD(sock);
	व्योम __user *argp = (व्योम __user *)arg;
	aपंचांग_backend_t b;

	पूर्णांक err;
	चयन (cmd) अणु
	हाल ATM_SETBACKEND:
	हाल ATM_NEWBACKENDIF:
		err = get_user(b, (aपंचांग_backend_t __user *) argp);
		अगर (err)
			वापस -EFAULT;
		अगर (b != ATM_BACKEND_BR2684)
			वापस -ENOIOCTLCMD;
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (cmd == ATM_SETBACKEND) अणु
			अगर (sock->state != SS_CONNECTED)
				वापस -EINVAL;
			वापस br2684_regvcc(aपंचांगvcc, argp);
		पूर्ण अन्यथा अणु
			वापस br2684_create(argp);
		पूर्ण
#अगर_घोषित CONFIG_ATM_BR2684_IPFILTER
	हाल BR2684_SETFILT:
		अगर (aपंचांगvcc->push != br2684_push)
			वापस -ENOIOCTLCMD;
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		err = br2684_setfilt(aपंचांगvcc, argp);

		वापस err;
#पूर्ण_अगर /* CONFIG_ATM_BR2684_IPFILTER */
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण

अटल काष्ठा aपंचांग_ioctl br2684_ioctl_ops = अणु
	.owner = THIS_MODULE,
	.ioctl = br2684_ioctl,
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम *br2684_seq_start(काष्ठा seq_file *seq, loff_t * pos)
	__acquires(devs_lock)
अणु
	पढ़ो_lock(&devs_lock);
	वापस seq_list_start(&br2684_devs, *pos);
पूर्ण

अटल व्योम *br2684_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t * pos)
अणु
	वापस seq_list_next(v, &br2684_devs, pos);
पूर्ण

अटल व्योम br2684_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(devs_lock)
अणु
	पढ़ो_unlock(&devs_lock);
पूर्ण

अटल पूर्णांक br2684_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	स्थिर काष्ठा br2684_dev *brdev = list_entry(v, काष्ठा br2684_dev,
						    br2684_devs);
	स्थिर काष्ठा net_device *net_dev = brdev->net_dev;
	स्थिर काष्ठा br2684_vcc *brvcc;

	seq_म_लिखो(seq, "dev %.16s: num=%d, mac=%pM (%s)\n",
		   net_dev->name,
		   brdev->number,
		   net_dev->dev_addr,
		   brdev->mac_was_set ? "set" : "auto");

	list_क्रम_each_entry(brvcc, &brdev->brvccs, brvccs) अणु
		seq_म_लिखो(seq, "  vcc %d.%d.%d: encaps=%s payload=%s"
			   ", failed copies %u/%u"
			   "\n", brvcc->aपंचांगvcc->dev->number,
			   brvcc->aपंचांगvcc->vpi, brvcc->aपंचांगvcc->vci,
			   (brvcc->encaps == e_llc) ? "LLC" : "VC",
			   (brdev->payload == p_bridged) ? "bridged" : "routed",
			   brvcc->copies_failed, brvcc->copies_needed);
#अगर_घोषित CONFIG_ATM_BR2684_IPFILTER
		अगर (brvcc->filter.neपंचांगask != 0)
			seq_म_लिखो(seq, "    filter=%pI4/%pI4\n",
				   &brvcc->filter.prefix,
				   &brvcc->filter.neपंचांगask);
#पूर्ण_अगर /* CONFIG_ATM_BR2684_IPFILTER */
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations br2684_seq_ops = अणु
	.start = br2684_seq_start,
	.next = br2684_seq_next,
	.stop = br2684_seq_stop,
	.show = br2684_seq_show,
पूर्ण;

बाह्य काष्ठा proc_dir_entry *aपंचांग_proc_root;	/* from proc.c */
#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल पूर्णांक __init br2684_init(व्योम)
अणु
#अगर_घोषित CONFIG_PROC_FS
	काष्ठा proc_dir_entry *p;
	p = proc_create_seq("br2684", 0, aपंचांग_proc_root, &br2684_seq_ops);
	अगर (p == शून्य)
		वापस -ENOMEM;
#पूर्ण_अगर
	रेजिस्टर_aपंचांग_ioctl(&br2684_ioctl_ops);
	रेजिस्टर_aपंचांगdevice_notअगरier(&aपंचांग_dev_notअगरier);
	वापस 0;
पूर्ण

अटल व्योम __निकास br2684_निकास(व्योम)
अणु
	काष्ठा net_device *net_dev;
	काष्ठा br2684_dev *brdev;
	काष्ठा br2684_vcc *brvcc;
	deरेजिस्टर_aपंचांग_ioctl(&br2684_ioctl_ops);

#अगर_घोषित CONFIG_PROC_FS
	हटाओ_proc_entry("br2684", aपंचांग_proc_root);
#पूर्ण_अगर


	unरेजिस्टर_aपंचांगdevice_notअगरier(&aपंचांग_dev_notअगरier);

	जबतक (!list_empty(&br2684_devs)) अणु
		net_dev = list_entry_brdev(br2684_devs.next);
		brdev = BRPRIV(net_dev);
		जबतक (!list_empty(&brdev->brvccs)) अणु
			brvcc = list_entry_brvcc(brdev->brvccs.next);
			br2684_बंद_vcc(brvcc);
		पूर्ण

		list_del(&brdev->br2684_devs);
		unरेजिस्टर_netdev(net_dev);
		मुक्त_netdev(net_dev);
	पूर्ण
पूर्ण

module_init(br2684_init);
module_निकास(br2684_निकास);

MODULE_AUTHOR("Marcell GAL");
MODULE_DESCRIPTION("RFC2684 bridged protocols over ATM/AAL5");
MODULE_LICENSE("GPL");
