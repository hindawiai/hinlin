<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * xfrm_device.c - IPsec device offloading code.
 *
 * Copyright (c) 2015 secunet Security Networks AG
 *
 * Author:
 * Steffen Klनिश्चित <steffen.klनिश्चित@secunet.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <net/dst.h>
#समावेश <net/xfrm.h>
#समावेश <linux/notअगरier.h>

#अगर_घोषित CONFIG_XFRM_OFFLOAD
अटल व्योम __xfrm_transport_prep(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb,
				  अचिन्हित पूर्णांक hsize)
अणु
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);

	skb_reset_mac_len(skb);
	अगर (xo->flags & XFRM_GSO_SEGMENT)
		skb->transport_header -= x->props.header_len;

	pskb_pull(skb, skb_transport_offset(skb) + x->props.header_len);
पूर्ण

अटल व्योम __xfrm_mode_tunnel_prep(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb,
				    अचिन्हित पूर्णांक hsize)

अणु
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);

	अगर (xo->flags & XFRM_GSO_SEGMENT)
		skb->transport_header = skb->network_header + hsize;

	skb_reset_mac_len(skb);
	pskb_pull(skb, skb->mac_len + x->props.header_len);
पूर्ण

अटल व्योम __xfrm_mode_beet_prep(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb,
				  अचिन्हित पूर्णांक hsize)
अणु
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);
	पूर्णांक phlen = 0;

	अगर (xo->flags & XFRM_GSO_SEGMENT)
		skb->transport_header = skb->network_header + hsize;

	skb_reset_mac_len(skb);
	अगर (x->sel.family != AF_INET6) अणु
		phlen = IPV4_BEET_PHMAXLEN;
		अगर (x->outer_mode.family == AF_INET6)
			phlen += माप(काष्ठा ipv6hdr) - माप(काष्ठा iphdr);
	पूर्ण

	pskb_pull(skb, skb->mac_len + hsize + (x->props.header_len - phlen));
पूर्ण

/* Adjust poपूर्णांकers पूर्णांकo the packet when IPsec is करोne at layer2 */
अटल व्योम xfrm_outer_mode_prep(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	चयन (x->outer_mode.encap) अणु
	हाल XFRM_MODE_TUNNEL:
		अगर (x->outer_mode.family == AF_INET)
			वापस __xfrm_mode_tunnel_prep(x, skb,
						       माप(काष्ठा iphdr));
		अगर (x->outer_mode.family == AF_INET6)
			वापस __xfrm_mode_tunnel_prep(x, skb,
						       माप(काष्ठा ipv6hdr));
		अवरोध;
	हाल XFRM_MODE_TRANSPORT:
		अगर (x->outer_mode.family == AF_INET)
			वापस __xfrm_transport_prep(x, skb,
						     माप(काष्ठा iphdr));
		अगर (x->outer_mode.family == AF_INET6)
			वापस __xfrm_transport_prep(x, skb,
						     माप(काष्ठा ipv6hdr));
		अवरोध;
	हाल XFRM_MODE_BEET:
		अगर (x->outer_mode.family == AF_INET)
			वापस __xfrm_mode_beet_prep(x, skb,
						     माप(काष्ठा iphdr));
		अगर (x->outer_mode.family == AF_INET6)
			वापस __xfrm_mode_beet_prep(x, skb,
						     माप(काष्ठा ipv6hdr));
		अवरोध;
	हाल XFRM_MODE_ROUTEOPTIMIZATION:
	हाल XFRM_MODE_IN_TRIGGER:
		अवरोध;
	पूर्ण
पूर्ण

काष्ठा sk_buff *validate_xmit_xfrm(काष्ठा sk_buff *skb, netdev_features_t features, bool *again)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ flags;
	काष्ठा xfrm_state *x;
	काष्ठा softnet_data *sd;
	काष्ठा sk_buff *skb2, *nskb, *pskb = शून्य;
	netdev_features_t esp_features = features;
	काष्ठा xfrm_offload *xo = xfrm_offload(skb);
	काष्ठा net_device *dev = skb->dev;
	काष्ठा sec_path *sp;

	अगर (!xo || (xo->flags & XFRM_XMIT))
		वापस skb;

	अगर (!(features & NETIF_F_HW_ESP))
		esp_features = features & ~(NETIF_F_SG | NETIF_F_CSUM_MASK);

	sp = skb_sec_path(skb);
	x = sp->xvec[sp->len - 1];
	अगर (xo->flags & XFRM_GRO || x->xso.flags & XFRM_OFFLOAD_INBOUND)
		वापस skb;

	/* This skb was alपढ़ोy validated on the upper/भव dev */
	अगर ((x->xso.dev != dev) && (x->xso.real_dev == dev))
		वापस skb;

	local_irq_save(flags);
	sd = this_cpu_ptr(&softnet_data);
	err = !skb_queue_empty(&sd->xfrm_backlog);
	local_irq_restore(flags);

	अगर (err) अणु
		*again = true;
		वापस skb;
	पूर्ण

	अगर (skb_is_gso(skb) && unlikely(x->xso.dev != dev)) अणु
		काष्ठा sk_buff *segs;

		/* Packet got rerouted, fixup features and segment it. */
		esp_features = esp_features & ~(NETIF_F_HW_ESP | NETIF_F_GSO_ESP);

		segs = skb_gso_segment(skb, esp_features);
		अगर (IS_ERR(segs)) अणु
			kमुक्त_skb(skb);
			atomic_दीर्घ_inc(&dev->tx_dropped);
			वापस शून्य;
		पूर्ण अन्यथा अणु
			consume_skb(skb);
			skb = segs;
		पूर्ण
	पूर्ण

	अगर (!skb->next) अणु
		esp_features |= skb->dev->gso_partial_features;
		xfrm_outer_mode_prep(x, skb);

		xo->flags |= XFRM_DEV_RESUME;

		err = x->type_offload->xmit(x, skb, esp_features);
		अगर (err) अणु
			अगर (err == -EINPROGRESS)
				वापस शून्य;

			XFRM_INC_STATS(xs_net(x), LINUX_MIB_XFRMOUTSTATEPROTOERROR);
			kमुक्त_skb(skb);
			वापस शून्य;
		पूर्ण

		skb_push(skb, skb->data - skb_mac_header(skb));

		वापस skb;
	पूर्ण

	skb_list_walk_safe(skb, skb2, nskb) अणु
		esp_features |= skb->dev->gso_partial_features;
		skb_mark_not_on_list(skb2);

		xo = xfrm_offload(skb2);
		xo->flags |= XFRM_DEV_RESUME;

		xfrm_outer_mode_prep(x, skb2);

		err = x->type_offload->xmit(x, skb2, esp_features);
		अगर (!err) अणु
			skb2->next = nskb;
		पूर्ण अन्यथा अगर (err != -EINPROGRESS) अणु
			XFRM_INC_STATS(xs_net(x), LINUX_MIB_XFRMOUTSTATEPROTOERROR);
			skb2->next = nskb;
			kमुक्त_skb_list(skb2);
			वापस शून्य;
		पूर्ण अन्यथा अणु
			अगर (skb == skb2)
				skb = nskb;
			अन्यथा
				pskb->next = nskb;

			जारी;
		पूर्ण

		skb_push(skb2, skb2->data - skb_mac_header(skb2));
		pskb = skb2;
	पूर्ण

	वापस skb;
पूर्ण
EXPORT_SYMBOL_GPL(validate_xmit_xfrm);

पूर्णांक xfrm_dev_state_add(काष्ठा net *net, काष्ठा xfrm_state *x,
		       काष्ठा xfrm_user_offload *xuo)
अणु
	पूर्णांक err;
	काष्ठा dst_entry *dst;
	काष्ठा net_device *dev;
	काष्ठा xfrm_state_offload *xso = &x->xso;
	xfrm_address_t *saddr;
	xfrm_address_t *daddr;

	अगर (!x->type_offload)
		वापस -EINVAL;

	/* We करोn't yet support UDP encapsulation and TFC padding. */
	अगर (x->encap || x->tfcpad)
		वापस -EINVAL;

	dev = dev_get_by_index(net, xuo->अगरindex);
	अगर (!dev) अणु
		अगर (!(xuo->flags & XFRM_OFFLOAD_INBOUND)) अणु
			saddr = &x->props.saddr;
			daddr = &x->id.daddr;
		पूर्ण अन्यथा अणु
			saddr = &x->id.daddr;
			daddr = &x->props.saddr;
		पूर्ण

		dst = __xfrm_dst_lookup(net, 0, 0, saddr, daddr,
					x->props.family,
					xfrm_smark_get(0, x));
		अगर (IS_ERR(dst))
			वापस 0;

		dev = dst->dev;

		dev_hold(dev);
		dst_release(dst);
	पूर्ण

	अगर (!dev->xfrmdev_ops || !dev->xfrmdev_ops->xकरो_dev_state_add) अणु
		xso->dev = शून्य;
		dev_put(dev);
		वापस 0;
	पूर्ण

	अगर (x->props.flags & XFRM_STATE_ESN &&
	    !dev->xfrmdev_ops->xकरो_dev_state_advance_esn) अणु
		xso->dev = शून्य;
		dev_put(dev);
		वापस -EINVAL;
	पूर्ण

	xso->dev = dev;
	xso->real_dev = dev;
	xso->num_exthdrs = 1;
	xso->flags = xuo->flags;

	err = dev->xfrmdev_ops->xकरो_dev_state_add(x);
	अगर (err) अणु
		xso->num_exthdrs = 0;
		xso->flags = 0;
		xso->dev = शून्य;
		dev_put(dev);

		अगर (err != -EOPNOTSUPP)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_dev_state_add);

bool xfrm_dev_offload_ok(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x)
अणु
	पूर्णांक mtu;
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा xfrm_dst *xdst = (काष्ठा xfrm_dst *)dst;
	काष्ठा net_device *dev = x->xso.dev;

	अगर (!x->type_offload || x->encap)
		वापस false;

	अगर ((!dev || (dev == xfrm_dst_path(dst)->dev)) &&
	    (!xdst->child->xfrm)) अणु
		mtu = xfrm_state_mtu(x, xdst->child_mtu_cached);
		अगर (skb->len <= mtu)
			जाओ ok;

		अगर (skb_is_gso(skb) && skb_gso_validate_network_len(skb, mtu))
			जाओ ok;
	पूर्ण

	वापस false;

ok:
	अगर (dev && dev->xfrmdev_ops && dev->xfrmdev_ops->xकरो_dev_offload_ok)
		वापस x->xso.dev->xfrmdev_ops->xकरो_dev_offload_ok(skb, x);

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_dev_offload_ok);

व्योम xfrm_dev_resume(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;
	पूर्णांक ret = NETDEV_TX_BUSY;
	काष्ठा netdev_queue *txq;
	काष्ठा softnet_data *sd;
	अचिन्हित दीर्घ flags;

	rcu_पढ़ो_lock();
	txq = netdev_core_pick_tx(dev, skb, शून्य);

	HARD_TX_LOCK(dev, txq, smp_processor_id());
	अगर (!netअगर_xmit_frozen_or_stopped(txq))
		skb = dev_hard_start_xmit(skb, dev, txq, &ret);
	HARD_TX_UNLOCK(dev, txq);

	अगर (!dev_xmit_complete(ret)) अणु
		local_irq_save(flags);
		sd = this_cpu_ptr(&softnet_data);
		skb_queue_tail(&sd->xfrm_backlog, skb);
		उठाओ_softirq_irqoff(NET_TX_SOFTIRQ);
		local_irq_restore(flags);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_dev_resume);

व्योम xfrm_dev_backlog(काष्ठा softnet_data *sd)
अणु
	काष्ठा sk_buff_head *xfrm_backlog = &sd->xfrm_backlog;
	काष्ठा sk_buff_head list;
	काष्ठा sk_buff *skb;

	अगर (skb_queue_empty(xfrm_backlog))
		वापस;

	__skb_queue_head_init(&list);

	spin_lock(&xfrm_backlog->lock);
	skb_queue_splice_init(xfrm_backlog, &list);
	spin_unlock(&xfrm_backlog->lock);

	जबतक (!skb_queue_empty(&list)) अणु
		skb = __skb_dequeue(&list);
		xfrm_dev_resume(skb);
	पूर्ण

पूर्ण
#पूर्ण_अगर

अटल पूर्णांक xfrm_api_check(काष्ठा net_device *dev)
अणु
#अगर_घोषित CONFIG_XFRM_OFFLOAD
	अगर ((dev->features & NETIF_F_HW_ESP_TX_CSUM) &&
	    !(dev->features & NETIF_F_HW_ESP))
		वापस NOTIFY_BAD;

	अगर ((dev->features & NETIF_F_HW_ESP) &&
	    (!(dev->xfrmdev_ops &&
	       dev->xfrmdev_ops->xकरो_dev_state_add &&
	       dev->xfrmdev_ops->xकरो_dev_state_delete)))
		वापस NOTIFY_BAD;
#अन्यथा
	अगर (dev->features & (NETIF_F_HW_ESP | NETIF_F_HW_ESP_TX_CSUM))
		वापस NOTIFY_BAD;
#पूर्ण_अगर

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक xfrm_dev_रेजिस्टर(काष्ठा net_device *dev)
अणु
	वापस xfrm_api_check(dev);
पूर्ण

अटल पूर्णांक xfrm_dev_feat_change(काष्ठा net_device *dev)
अणु
	वापस xfrm_api_check(dev);
पूर्ण

अटल पूर्णांक xfrm_dev_करोwn(काष्ठा net_device *dev)
अणु
	अगर (dev->features & NETIF_F_HW_ESP)
		xfrm_dev_state_flush(dev_net(dev), dev, true);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक xfrm_dev_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	चयन (event) अणु
	हाल NETDEV_REGISTER:
		वापस xfrm_dev_रेजिस्टर(dev);

	हाल NETDEV_FEAT_CHANGE:
		वापस xfrm_dev_feat_change(dev);

	हाल NETDEV_DOWN:
	हाल NETDEV_UNREGISTER:
		वापस xfrm_dev_करोwn(dev);
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block xfrm_dev_notअगरier = अणु
	.notअगरier_call	= xfrm_dev_event,
पूर्ण;

व्योम __init xfrm_dev_init(व्योम)
अणु
	रेजिस्टर_netdevice_notअगरier(&xfrm_dev_notअगरier);
पूर्ण
