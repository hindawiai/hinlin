<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#समावेश "queueing.h"
#समावेश "socket.h"
#समावेश "timers.h"
#समावेश "device.h"
#समावेश "ratelimiter.h"
#समावेश "peer.h"
#समावेश "messages.h"

#समावेश <linux/module.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/icmp.h>
#समावेश <linux/suspend.h>
#समावेश <net/icmp.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/addrconf.h>

अटल LIST_HEAD(device_list);

अटल पूर्णांक wg_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा in_device *dev_v4 = __in_dev_get_rtnl(dev);
	काष्ठा inet6_dev *dev_v6 = __in6_dev_get(dev);
	काष्ठा wg_device *wg = netdev_priv(dev);
	काष्ठा wg_peer *peer;
	पूर्णांक ret;

	अगर (dev_v4) अणु
		/* At some poपूर्णांक we might put this check near the ip_rt_send_
		 * redirect call of ip_क्रमward in net/ipv4/ip_क्रमward.c, similar
		 * to the current secpath check.
		 */
		IN_DEV_CONF_SET(dev_v4, SEND_REसूचीECTS, false);
		IPV4_DEVCONF_ALL(dev_net(dev), SEND_REसूचीECTS) = false;
	पूर्ण
	अगर (dev_v6)
		dev_v6->cnf.addr_gen_mode = IN6_ADDR_GEN_MODE_NONE;

	mutex_lock(&wg->device_update_lock);
	ret = wg_socket_init(wg, wg->incoming_port);
	अगर (ret < 0)
		जाओ out;
	list_क्रम_each_entry(peer, &wg->peer_list, peer_list) अणु
		wg_packet_send_staged_packets(peer);
		अगर (peer->persistent_keepalive_पूर्णांकerval)
			wg_packet_send_keepalive(peer);
	पूर्ण
out:
	mutex_unlock(&wg->device_update_lock);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक wg_pm_notअगरication(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			      व्योम *data)
अणु
	काष्ठा wg_device *wg;
	काष्ठा wg_peer *peer;

	/* If the machine is स्थिरantly suspending and resuming, as part of
	 * its normal operation rather than as a somewhat rare event, then we
	 * करोn't actually want to clear keys.
	 */
	अगर (IS_ENABLED(CONFIG_PM_AUTOSLEEP) || IS_ENABLED(CONFIG_ANDROID))
		वापस 0;

	अगर (action != PM_HIBERNATION_PREPARE && action != PM_SUSPEND_PREPARE)
		वापस 0;

	rtnl_lock();
	list_क्रम_each_entry(wg, &device_list, device_list) अणु
		mutex_lock(&wg->device_update_lock);
		list_क्रम_each_entry(peer, &wg->peer_list, peer_list) अणु
			del_समयr(&peer->समयr_zero_key_material);
			wg_noise_handshake_clear(&peer->handshake);
			wg_noise_keypairs_clear(&peer->keypairs);
		पूर्ण
		mutex_unlock(&wg->device_update_lock);
	पूर्ण
	rtnl_unlock();
	rcu_barrier();
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block pm_notअगरier = अणु .notअगरier_call = wg_pm_notअगरication पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक wg_stop(काष्ठा net_device *dev)
अणु
	काष्ठा wg_device *wg = netdev_priv(dev);
	काष्ठा wg_peer *peer;

	mutex_lock(&wg->device_update_lock);
	list_क्रम_each_entry(peer, &wg->peer_list, peer_list) अणु
		wg_packet_purge_staged_packets(peer);
		wg_समयrs_stop(peer);
		wg_noise_handshake_clear(&peer->handshake);
		wg_noise_keypairs_clear(&peer->keypairs);
		wg_noise_reset_last_sent_handshake(&peer->last_sent_handshake);
	पूर्ण
	mutex_unlock(&wg->device_update_lock);
	skb_queue_purge(&wg->incoming_handshakes);
	wg_socket_reinit(wg, शून्य, शून्य);
	वापस 0;
पूर्ण

अटल netdev_tx_t wg_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा wg_device *wg = netdev_priv(dev);
	काष्ठा sk_buff_head packets;
	काष्ठा wg_peer *peer;
	काष्ठा sk_buff *next;
	sa_family_t family;
	u32 mtu;
	पूर्णांक ret;

	अगर (unlikely(!wg_check_packet_protocol(skb))) अणु
		ret = -EPROTONOSUPPORT;
		net_dbg_ratelimited("%s: Invalid IP packet\n", dev->name);
		जाओ err;
	पूर्ण

	peer = wg_allowedips_lookup_dst(&wg->peer_allowedips, skb);
	अगर (unlikely(!peer)) अणु
		ret = -ENOKEY;
		अगर (skb->protocol == htons(ETH_P_IP))
			net_dbg_ratelimited("%s: No peer has allowed IPs matching %pI4\n",
					    dev->name, &ip_hdr(skb)->daddr);
		अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
			net_dbg_ratelimited("%s: No peer has allowed IPs matching %pI6\n",
					    dev->name, &ipv6_hdr(skb)->daddr);
		जाओ err_icmp;
	पूर्ण

	family = READ_ONCE(peer->endpoपूर्णांक.addr.sa_family);
	अगर (unlikely(family != AF_INET && family != AF_INET6)) अणु
		ret = -EDESTADDRREQ;
		net_dbg_ratelimited("%s: No valid endpoint has been configured or discovered for peer %llu\n",
				    dev->name, peer->पूर्णांकernal_id);
		जाओ err_peer;
	पूर्ण

	mtu = skb_dst(skb) ? dst_mtu(skb_dst(skb)) : dev->mtu;

	__skb_queue_head_init(&packets);
	अगर (!skb_is_gso(skb)) अणु
		skb_mark_not_on_list(skb);
	पूर्ण अन्यथा अणु
		काष्ठा sk_buff *segs = skb_gso_segment(skb, 0);

		अगर (IS_ERR(segs)) अणु
			ret = PTR_ERR(segs);
			जाओ err_peer;
		पूर्ण
		dev_kमुक्त_skb(skb);
		skb = segs;
	पूर्ण

	skb_list_walk_safe(skb, skb, next) अणु
		skb_mark_not_on_list(skb);

		skb = skb_share_check(skb, GFP_ATOMIC);
		अगर (unlikely(!skb))
			जारी;

		/* We only need to keep the original dst around क्रम icmp,
		 * so at this poपूर्णांक we're in a position to drop it.
		 */
		skb_dst_drop(skb);

		PACKET_CB(skb)->mtu = mtu;

		__skb_queue_tail(&packets, skb);
	पूर्ण

	spin_lock_bh(&peer->staged_packet_queue.lock);
	/* If the queue is getting too big, we start removing the oldest packets
	 * until it's small again. We करो this beक्रमe adding the new packet, so
	 * we करोn't हटाओ GSO segments that are in excess.
	 */
	जबतक (skb_queue_len(&peer->staged_packet_queue) > MAX_STAGED_PACKETS) अणु
		dev_kमुक्त_skb(__skb_dequeue(&peer->staged_packet_queue));
		++dev->stats.tx_dropped;
	पूर्ण
	skb_queue_splice_tail(&packets, &peer->staged_packet_queue);
	spin_unlock_bh(&peer->staged_packet_queue.lock);

	wg_packet_send_staged_packets(peer);

	wg_peer_put(peer);
	वापस NETDEV_TX_OK;

err_peer:
	wg_peer_put(peer);
err_icmp:
	अगर (skb->protocol == htons(ETH_P_IP))
		icmp_nकरो_send(skb, ICMP_DEST_UNREACH, ICMP_HOST_UNREACH, 0);
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
		icmpv6_nकरो_send(skb, ICMPV6_DEST_UNREACH, ICMPV6_ADDR_UNREACH, 0);
err:
	++dev->stats.tx_errors;
	kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_खोलो		= wg_खोलो,
	.nकरो_stop		= wg_stop,
	.nकरो_start_xmit		= wg_xmit,
	.nकरो_get_stats64	= dev_get_tstats64
पूर्ण;

अटल व्योम wg_deकाष्ठा(काष्ठा net_device *dev)
अणु
	काष्ठा wg_device *wg = netdev_priv(dev);

	rtnl_lock();
	list_del(&wg->device_list);
	rtnl_unlock();
	mutex_lock(&wg->device_update_lock);
	rcu_assign_poपूर्णांकer(wg->creating_net, शून्य);
	wg->incoming_port = 0;
	wg_socket_reinit(wg, शून्य, शून्य);
	/* The final references are cleared in the below calls to destroy_workqueue. */
	wg_peer_हटाओ_all(wg);
	destroy_workqueue(wg->handshake_receive_wq);
	destroy_workqueue(wg->handshake_send_wq);
	destroy_workqueue(wg->packet_crypt_wq);
	wg_packet_queue_मुक्त(&wg->decrypt_queue);
	wg_packet_queue_मुक्त(&wg->encrypt_queue);
	rcu_barrier(); /* Wait क्रम all the peers to be actually मुक्तd. */
	wg_ratelimiter_uninit();
	memzero_explicit(&wg->अटल_identity, माप(wg->अटल_identity));
	skb_queue_purge(&wg->incoming_handshakes);
	मुक्त_percpu(dev->tstats);
	मुक्त_percpu(wg->incoming_handshakes_worker);
	kvमुक्त(wg->index_hashtable);
	kvमुक्त(wg->peer_hashtable);
	mutex_unlock(&wg->device_update_lock);

	pr_debug("%s: Interface destroyed\n", dev->name);
	मुक्त_netdev(dev);
पूर्ण

अटल स्थिर काष्ठा device_type device_type = अणु .name = KBUILD_MODNAME पूर्ण;

अटल व्योम wg_setup(काष्ठा net_device *dev)
अणु
	काष्ठा wg_device *wg = netdev_priv(dev);
	क्रमागत अणु WG_NETDEV_FEATURES = NETIF_F_HW_CSUM | NETIF_F_RXCSUM |
				    NETIF_F_SG | NETIF_F_GSO |
				    NETIF_F_GSO_SOFTWARE | NETIF_F_HIGHDMA पूर्ण;
	स्थिर पूर्णांक overhead = MESSAGE_MINIMUM_LENGTH + माप(काष्ठा udphdr) +
			     max(माप(काष्ठा ipv6hdr), माप(काष्ठा iphdr));

	dev->netdev_ops = &netdev_ops;
	dev->header_ops = &ip_tunnel_header_ops;
	dev->hard_header_len = 0;
	dev->addr_len = 0;
	dev->needed_headroom = DATA_PACKET_HEAD_ROOM;
	dev->needed_tailroom = noise_encrypted_len(MESSAGE_PADDING_MULTIPLE);
	dev->type = ARPHRD_NONE;
	dev->flags = IFF_POINTOPOINT | IFF_NOARP;
	dev->priv_flags |= IFF_NO_QUEUE;
	dev->features |= NETIF_F_LLTX;
	dev->features |= WG_NETDEV_FEATURES;
	dev->hw_features |= WG_NETDEV_FEATURES;
	dev->hw_enc_features |= WG_NETDEV_FEATURES;
	dev->mtu = ETH_DATA_LEN - overhead;
	dev->max_mtu = round_करोwn(पूर्णांक_उच्च, MESSAGE_PADDING_MULTIPLE) - overhead;

	SET_NETDEV_DEVTYPE(dev, &device_type);

	/* We need to keep the dst around in हाल of icmp replies. */
	netअगर_keep_dst(dev);

	स_रखो(wg, 0, माप(*wg));
	wg->dev = dev;
पूर्ण

अटल पूर्णांक wg_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
		      काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा wg_device *wg = netdev_priv(dev);
	पूर्णांक ret = -ENOMEM;

	rcu_assign_poपूर्णांकer(wg->creating_net, src_net);
	init_rwsem(&wg->अटल_identity.lock);
	mutex_init(&wg->socket_update_lock);
	mutex_init(&wg->device_update_lock);
	skb_queue_head_init(&wg->incoming_handshakes);
	wg_allowedips_init(&wg->peer_allowedips);
	wg_cookie_checker_init(&wg->cookie_checker, wg);
	INIT_LIST_HEAD(&wg->peer_list);
	wg->device_update_gen = 1;

	wg->peer_hashtable = wg_pubkey_hashtable_alloc();
	अगर (!wg->peer_hashtable)
		वापस ret;

	wg->index_hashtable = wg_index_hashtable_alloc();
	अगर (!wg->index_hashtable)
		जाओ err_मुक्त_peer_hashtable;

	dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!dev->tstats)
		जाओ err_मुक्त_index_hashtable;

	wg->incoming_handshakes_worker =
		wg_packet_percpu_multicore_worker_alloc(
				wg_packet_handshake_receive_worker, wg);
	अगर (!wg->incoming_handshakes_worker)
		जाओ err_मुक्त_tstats;

	wg->handshake_receive_wq = alloc_workqueue("wg-kex-%s",
			WQ_CPU_INTENSIVE | WQ_FREEZABLE, 0, dev->name);
	अगर (!wg->handshake_receive_wq)
		जाओ err_मुक्त_incoming_handshakes;

	wg->handshake_send_wq = alloc_workqueue("wg-kex-%s",
			WQ_UNBOUND | WQ_FREEZABLE, 0, dev->name);
	अगर (!wg->handshake_send_wq)
		जाओ err_destroy_handshake_receive;

	wg->packet_crypt_wq = alloc_workqueue("wg-crypt-%s",
			WQ_CPU_INTENSIVE | WQ_MEM_RECLAIM, 0, dev->name);
	अगर (!wg->packet_crypt_wq)
		जाओ err_destroy_handshake_send;

	ret = wg_packet_queue_init(&wg->encrypt_queue, wg_packet_encrypt_worker,
				   MAX_QUEUED_PACKETS);
	अगर (ret < 0)
		जाओ err_destroy_packet_crypt;

	ret = wg_packet_queue_init(&wg->decrypt_queue, wg_packet_decrypt_worker,
				   MAX_QUEUED_PACKETS);
	अगर (ret < 0)
		जाओ err_मुक्त_encrypt_queue;

	ret = wg_ratelimiter_init();
	अगर (ret < 0)
		जाओ err_मुक्त_decrypt_queue;

	ret = रेजिस्टर_netdevice(dev);
	अगर (ret < 0)
		जाओ err_uninit_ratelimiter;

	list_add(&wg->device_list, &device_list);

	/* We रुको until the end to assign priv_deकाष्ठाor, so that
	 * रेजिस्टर_netdevice करोesn't call it क्रम us अगर it fails.
	 */
	dev->priv_deकाष्ठाor = wg_deकाष्ठा;

	pr_debug("%s: Interface created\n", dev->name);
	वापस ret;

err_uninit_ratelimiter:
	wg_ratelimiter_uninit();
err_मुक्त_decrypt_queue:
	wg_packet_queue_मुक्त(&wg->decrypt_queue);
err_मुक्त_encrypt_queue:
	wg_packet_queue_मुक्त(&wg->encrypt_queue);
err_destroy_packet_crypt:
	destroy_workqueue(wg->packet_crypt_wq);
err_destroy_handshake_send:
	destroy_workqueue(wg->handshake_send_wq);
err_destroy_handshake_receive:
	destroy_workqueue(wg->handshake_receive_wq);
err_मुक्त_incoming_handshakes:
	मुक्त_percpu(wg->incoming_handshakes_worker);
err_मुक्त_tstats:
	मुक्त_percpu(dev->tstats);
err_मुक्त_index_hashtable:
	kvमुक्त(wg->index_hashtable);
err_मुक्त_peer_hashtable:
	kvमुक्त(wg->peer_hashtable);
	वापस ret;
पूर्ण

अटल काष्ठा rtnl_link_ops link_ops __पढ़ो_mostly = अणु
	.kind			= KBUILD_MODNAME,
	.priv_size		= माप(काष्ठा wg_device),
	.setup			= wg_setup,
	.newlink		= wg_newlink,
पूर्ण;

अटल व्योम wg_netns_pre_निकास(काष्ठा net *net)
अणु
	काष्ठा wg_device *wg;

	rtnl_lock();
	list_क्रम_each_entry(wg, &device_list, device_list) अणु
		अगर (rcu_access_poपूर्णांकer(wg->creating_net) == net) अणु
			pr_debug("%s: Creating namespace exiting\n", wg->dev->name);
			netअगर_carrier_off(wg->dev);
			mutex_lock(&wg->device_update_lock);
			rcu_assign_poपूर्णांकer(wg->creating_net, शून्य);
			wg_socket_reinit(wg, शून्य, शून्य);
			mutex_unlock(&wg->device_update_lock);
		पूर्ण
	पूर्ण
	rtnl_unlock();
पूर्ण

अटल काष्ठा pernet_operations pernet_ops = अणु
	.pre_निकास = wg_netns_pre_निकास
पूर्ण;

पूर्णांक __init wg_device_init(व्योम)
अणु
	पूर्णांक ret;

#अगर_घोषित CONFIG_PM_SLEEP
	ret = रेजिस्टर_pm_notअगरier(&pm_notअगरier);
	अगर (ret)
		वापस ret;
#पूर्ण_अगर

	ret = रेजिस्टर_pernet_device(&pernet_ops);
	अगर (ret)
		जाओ error_pm;

	ret = rtnl_link_रेजिस्टर(&link_ops);
	अगर (ret)
		जाओ error_pernet;

	वापस 0;

error_pernet:
	unरेजिस्टर_pernet_device(&pernet_ops);
error_pm:
#अगर_घोषित CONFIG_PM_SLEEP
	unरेजिस्टर_pm_notअगरier(&pm_notअगरier);
#पूर्ण_अगर
	वापस ret;
पूर्ण

व्योम wg_device_uninit(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&link_ops);
	unरेजिस्टर_pernet_device(&pernet_ops);
#अगर_घोषित CONFIG_PM_SLEEP
	unरेजिस्टर_pm_notअगरier(&pm_notअगरier);
#पूर्ण_अगर
	rcu_barrier();
पूर्ण
