<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Authors:	Sjur Brendeland
 *		Daniel Martensson
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s(): " fmt, __func__

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/ip.h>
#समावेश <linux/sched.h>
#समावेश <linux/sockios.h>
#समावेश <linux/caअगर/अगर_caअगर.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/cfpkt.h>
#समावेश <net/caअगर/caअगर_dev.h>

/* GPRS PDP connection has MTU to 1500 */
#घोषणा GPRS_PDP_MTU 1500
/* 5 sec. connect समयout */
#घोषणा CONNECT_TIMEOUT (5 * HZ)
#घोषणा CAIF_NET_DEFAULT_QUEUE_LEN 500
#घोषणा UNDEF_CONNID 0xffffffff

/*This list is रक्षित by the rtnl lock. */
अटल LIST_HEAD(chnl_net_list);

MODULE_LICENSE("GPL");
MODULE_ALIAS_RTNL_LINK("caif");

क्रमागत caअगर_states अणु
	CAIF_CONNECTED		= 1,
	CAIF_CONNECTING,
	CAIF_DISCONNECTED,
	CAIF_SHUTDOWN
पूर्ण;

काष्ठा chnl_net अणु
	काष्ठा cflayer chnl;
	काष्ठा caअगर_connect_request conn_req;
	काष्ठा list_head list_field;
	काष्ठा net_device *netdev;
	अक्षर name[256];
	रुको_queue_head_t neपंचांगgmt_wq;
	/* Flow status to remember and control the transmission. */
	bool flowenabled;
	क्रमागत caअगर_states state;
पूर्ण;

अटल व्योम robust_list_del(काष्ठा list_head *delete_node)
अणु
	काष्ठा list_head *list_node;
	काष्ठा list_head *n;
	ASSERT_RTNL();
	list_क्रम_each_safe(list_node, n, &chnl_net_list) अणु
		अगर (list_node == delete_node) अणु
			list_del(list_node);
			वापस;
		पूर्ण
	पूर्ण
	WARN_ON(1);
पूर्ण

अटल पूर्णांक chnl_recv_cb(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा chnl_net *priv;
	पूर्णांक pktlen;
	स्थिर u8 *ip_version;
	u8 buf;

	priv = container_of(layr, काष्ठा chnl_net, chnl);
	अगर (!priv)
		वापस -EINVAL;

	skb = (काष्ठा sk_buff *) cfpkt_tonative(pkt);

	/* Get length of CAIF packet. */
	pktlen = skb->len;

	/* Pass some minimum inक्रमmation and
	 * send the packet to the net stack.
	 */
	skb->dev = priv->netdev;

	/* check the version of IP */
	ip_version = skb_header_poपूर्णांकer(skb, 0, 1, &buf);
	अगर (!ip_version) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	चयन (*ip_version >> 4) अणु
	हाल 4:
		skb->protocol = htons(ETH_P_IP);
		अवरोध;
	हाल 6:
		skb->protocol = htons(ETH_P_IPV6);
		अवरोध;
	शेष:
		kमुक्त_skb(skb);
		priv->netdev->stats.rx_errors++;
		वापस -EINVAL;
	पूर्ण

	/* If we change the header in loop mode, the checksum is corrupted. */
	अगर (priv->conn_req.protocol == CAIFPROTO_DATAGRAM_LOOP)
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	अन्यथा
		skb->ip_summed = CHECKSUM_NONE;

	netअगर_rx_any_context(skb);

	/* Update statistics. */
	priv->netdev->stats.rx_packets++;
	priv->netdev->stats.rx_bytes += pktlen;

	वापस 0;
पूर्ण

अटल पूर्णांक delete_device(काष्ठा chnl_net *dev)
अणु
	ASSERT_RTNL();
	अगर (dev->netdev)
		unरेजिस्टर_netdevice(dev->netdev);
	वापस 0;
पूर्ण

अटल व्योम बंद_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा chnl_net *dev = शून्य;
	काष्ठा list_head *list_node;
	काष्ठा list_head *_पंचांगp;

	rtnl_lock();
	list_क्रम_each_safe(list_node, _पंचांगp, &chnl_net_list) अणु
		dev = list_entry(list_node, काष्ठा chnl_net, list_field);
		अगर (dev->state == CAIF_SHUTDOWN)
			dev_बंद(dev->netdev);
	पूर्ण
	rtnl_unlock();
पूर्ण
अटल DECLARE_WORK(बंद_worker, बंद_work);

अटल व्योम chnl_hold(काष्ठा cflayer *lyr)
अणु
	काष्ठा chnl_net *priv = container_of(lyr, काष्ठा chnl_net, chnl);
	dev_hold(priv->netdev);
पूर्ण

अटल व्योम chnl_put(काष्ठा cflayer *lyr)
अणु
	काष्ठा chnl_net *priv = container_of(lyr, काष्ठा chnl_net, chnl);
	dev_put(priv->netdev);
पूर्ण

अटल व्योम chnl_flowctrl_cb(काष्ठा cflayer *layr, क्रमागत caअगर_ctrlcmd flow,
			     पूर्णांक phyid)
अणु
	काष्ठा chnl_net *priv = container_of(layr, काष्ठा chnl_net, chnl);
	pr_debug("NET flowctrl func called flow: %s\n",
		flow == CAIF_CTRLCMD_FLOW_ON_IND ? "ON" :
		flow == CAIF_CTRLCMD_INIT_RSP ? "INIT" :
		flow == CAIF_CTRLCMD_FLOW_OFF_IND ? "OFF" :
		flow == CAIF_CTRLCMD_DEINIT_RSP ? "CLOSE/DEINIT" :
		flow == CAIF_CTRLCMD_INIT_FAIL_RSP ? "OPEN_FAIL" :
		flow == CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND ?
		 "REMOTE_SHUTDOWN" : "UNKNOWN CTRL COMMAND");



	चयन (flow) अणु
	हाल CAIF_CTRLCMD_FLOW_OFF_IND:
		priv->flowenabled = false;
		netअगर_stop_queue(priv->netdev);
		अवरोध;
	हाल CAIF_CTRLCMD_DEINIT_RSP:
		priv->state = CAIF_DISCONNECTED;
		अवरोध;
	हाल CAIF_CTRLCMD_INIT_FAIL_RSP:
		priv->state = CAIF_DISCONNECTED;
		wake_up_पूर्णांकerruptible(&priv->neपंचांगgmt_wq);
		अवरोध;
	हाल CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND:
		priv->state = CAIF_SHUTDOWN;
		netअगर_tx_disable(priv->netdev);
		schedule_work(&बंद_worker);
		अवरोध;
	हाल CAIF_CTRLCMD_FLOW_ON_IND:
		priv->flowenabled = true;
		netअगर_wake_queue(priv->netdev);
		अवरोध;
	हाल CAIF_CTRLCMD_INIT_RSP:
		caअगर_client_रेजिस्टर_refcnt(&priv->chnl, chnl_hold, chnl_put);
		priv->state = CAIF_CONNECTED;
		priv->flowenabled = true;
		netअगर_wake_queue(priv->netdev);
		wake_up_पूर्णांकerruptible(&priv->neपंचांगgmt_wq);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल netdev_tx_t chnl_net_start_xmit(काष्ठा sk_buff *skb,
				       काष्ठा net_device *dev)
अणु
	काष्ठा chnl_net *priv;
	काष्ठा cfpkt *pkt = शून्य;
	पूर्णांक len;
	पूर्णांक result = -1;
	/* Get our निजी data. */
	priv = netdev_priv(dev);

	अगर (skb->len > priv->netdev->mtu) अणु
		pr_warn("Size of skb exceeded MTU\n");
		kमुक्त_skb(skb);
		dev->stats.tx_errors++;
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (!priv->flowenabled) अणु
		pr_debug("dropping packets flow off\n");
		kमुक्त_skb(skb);
		dev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (priv->conn_req.protocol == CAIFPROTO_DATAGRAM_LOOP)
		swap(ip_hdr(skb)->saddr, ip_hdr(skb)->daddr);

	/* Store original SKB length. */
	len = skb->len;

	pkt = cfpkt_fromnative(CAIF_सूची_OUT, (व्योम *) skb);

	/* Send the packet करोwn the stack. */
	result = priv->chnl.dn->transmit(priv->chnl.dn, pkt);
	अगर (result) अणु
		dev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	/* Update statistics. */
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += len;

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक chnl_net_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा chnl_net *priv = शून्य;
	पूर्णांक result = -1;
	पूर्णांक llअगरindex, headroom, tailroom, mtu;
	काष्ठा net_device *lldev;
	ASSERT_RTNL();
	priv = netdev_priv(dev);
	अगर (!priv) अणु
		pr_debug("chnl_net_open: no priv\n");
		वापस -ENODEV;
	पूर्ण

	अगर (priv->state != CAIF_CONNECTING) अणु
		priv->state = CAIF_CONNECTING;
		result = caअगर_connect_client(dev_net(dev), &priv->conn_req,
						&priv->chnl, &llअगरindex,
						&headroom, &tailroom);
		अगर (result != 0) अणु
				pr_debug("err: "
					 "Unable to register and open device,"
					 " Err:%d\n",
					 result);
				जाओ error;
		पूर्ण

		lldev = __dev_get_by_index(dev_net(dev), llअगरindex);

		अगर (lldev == शून्य) अणु
			pr_debug("no interface?\n");
			result = -ENODEV;
			जाओ error;
		पूर्ण

		dev->needed_tailroom = tailroom + lldev->needed_tailroom;
		dev->hard_header_len = headroom + lldev->hard_header_len +
			lldev->needed_tailroom;

		/*
		 * MTU, head-room etc is not know beक्रमe we have a
		 * CAIF link layer device available. MTU calculation may
		 * override initial RTNL configuration.
		 * MTU is minimum of current mtu, link layer mtu pluss
		 * CAIF head and tail, and PDP GPRS contexts max MTU.
		 */
		mtu = min_t(पूर्णांक, dev->mtu, lldev->mtu - (headroom + tailroom));
		mtu = min_t(पूर्णांक, GPRS_PDP_MTU, mtu);
		dev_set_mtu(dev, mtu);

		अगर (mtu < 100) अणु
			pr_warn("CAIF Interface MTU too small (%d)\n", mtu);
			result = -ENODEV;
			जाओ error;
		पूर्ण
	पूर्ण

	rtnl_unlock();  /* Release RTNL lock during connect रुको */

	result = रुको_event_पूर्णांकerruptible_समयout(priv->neपंचांगgmt_wq,
						priv->state != CAIF_CONNECTING,
						CONNECT_TIMEOUT);

	rtnl_lock();

	अगर (result == -ERESTARTSYS) अणु
		pr_debug("wait_event_interruptible woken by a signal\n");
		result = -ERESTARTSYS;
		जाओ error;
	पूर्ण

	अगर (result == 0) अणु
		pr_debug("connect timeout\n");
		caअगर_disconnect_client(dev_net(dev), &priv->chnl);
		priv->state = CAIF_DISCONNECTED;
		pr_debug("state disconnected\n");
		result = -ETIMEDOUT;
		जाओ error;
	पूर्ण

	अगर (priv->state != CAIF_CONNECTED) अणु
		pr_debug("connect failed\n");
		result = -ECONNREFUSED;
		जाओ error;
	पूर्ण
	pr_debug("CAIF Netdevice connected\n");
	वापस 0;

error:
	caअगर_disconnect_client(dev_net(dev), &priv->chnl);
	priv->state = CAIF_DISCONNECTED;
	pr_debug("state disconnected\n");
	वापस result;

पूर्ण

अटल पूर्णांक chnl_net_stop(काष्ठा net_device *dev)
अणु
	काष्ठा chnl_net *priv;

	ASSERT_RTNL();
	priv = netdev_priv(dev);
	priv->state = CAIF_DISCONNECTED;
	caअगर_disconnect_client(dev_net(dev), &priv->chnl);
	वापस 0;
पूर्ण

अटल पूर्णांक chnl_net_init(काष्ठा net_device *dev)
अणु
	काष्ठा chnl_net *priv;
	ASSERT_RTNL();
	priv = netdev_priv(dev);
	म_नकलन(priv->name, dev->name, माप(priv->name));
	वापस 0;
पूर्ण

अटल व्योम chnl_net_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा chnl_net *priv;
	ASSERT_RTNL();
	priv = netdev_priv(dev);
	robust_list_del(&priv->list_field);
पूर्ण

अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_खोलो = chnl_net_खोलो,
	.nकरो_stop = chnl_net_stop,
	.nकरो_init = chnl_net_init,
	.nकरो_uninit = chnl_net_uninit,
	.nकरो_start_xmit = chnl_net_start_xmit,
पूर्ण;

अटल व्योम chnl_net_deकाष्ठाor(काष्ठा net_device *dev)
अणु
	काष्ठा chnl_net *priv = netdev_priv(dev);
	caअगर_मुक्त_client(&priv->chnl);
पूर्ण

अटल व्योम ipcaअगर_net_setup(काष्ठा net_device *dev)
अणु
	काष्ठा chnl_net *priv;
	dev->netdev_ops = &netdev_ops;
	dev->needs_मुक्त_netdev = true;
	dev->priv_deकाष्ठाor = chnl_net_deकाष्ठाor;
	dev->flags |= IFF_NOARP;
	dev->flags |= IFF_POINTOPOINT;
	dev->mtu = GPRS_PDP_MTU;
	dev->tx_queue_len = CAIF_NET_DEFAULT_QUEUE_LEN;

	priv = netdev_priv(dev);
	priv->chnl.receive = chnl_recv_cb;
	priv->chnl.ctrlcmd = chnl_flowctrl_cb;
	priv->netdev = dev;
	priv->conn_req.protocol = CAIFPROTO_DATAGRAM;
	priv->conn_req.link_selector = CAIF_LINK_HIGH_BANDW;
	priv->conn_req.priority = CAIF_PRIO_LOW;
	/* Insert illegal value */
	priv->conn_req.sockaddr.u.dgm.connection_id = UNDEF_CONNID;
	priv->flowenabled = false;

	init_रुकोqueue_head(&priv->neपंचांगgmt_wq);
पूर्ण


अटल पूर्णांक ipcaअगर_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा chnl_net *priv;
	u8 loop;
	priv = netdev_priv(dev);
	अगर (nla_put_u32(skb, IFLA_CAIF_IPV4_CONNID,
			priv->conn_req.sockaddr.u.dgm.connection_id) ||
	    nla_put_u32(skb, IFLA_CAIF_IPV6_CONNID,
			priv->conn_req.sockaddr.u.dgm.connection_id))
		जाओ nla_put_failure;
	loop = priv->conn_req.protocol == CAIFPROTO_DATAGRAM_LOOP;
	अगर (nla_put_u8(skb, IFLA_CAIF_LOOPBACK, loop))
		जाओ nla_put_failure;
	वापस 0;
nla_put_failure:
	वापस -EMSGSIZE;

पूर्ण

अटल व्योम caअगर_netlink_parms(काष्ठा nlattr *data[],
			       काष्ठा caअगर_connect_request *conn_req)
अणु
	अगर (!data) अणु
		pr_warn("no params data found\n");
		वापस;
	पूर्ण
	अगर (data[IFLA_CAIF_IPV4_CONNID])
		conn_req->sockaddr.u.dgm.connection_id =
			nla_get_u32(data[IFLA_CAIF_IPV4_CONNID]);
	अगर (data[IFLA_CAIF_IPV6_CONNID])
		conn_req->sockaddr.u.dgm.connection_id =
			nla_get_u32(data[IFLA_CAIF_IPV6_CONNID]);
	अगर (data[IFLA_CAIF_LOOPBACK]) अणु
		अगर (nla_get_u8(data[IFLA_CAIF_LOOPBACK]))
			conn_req->protocol = CAIFPROTO_DATAGRAM_LOOP;
		अन्यथा
			conn_req->protocol = CAIFPROTO_DATAGRAM;
	पूर्ण
पूर्ण

अटल पूर्णांक ipcaअगर_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			  काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			  काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक ret;
	काष्ठा chnl_net *caअगरdev;
	ASSERT_RTNL();
	caअगरdev = netdev_priv(dev);
	caअगर_netlink_parms(data, &caअगरdev->conn_req);

	ret = रेजिस्टर_netdevice(dev);
	अगर (ret)
		pr_warn("device rtml registration failed\n");
	अन्यथा
		list_add(&caअगरdev->list_field, &chnl_net_list);

	/* Use अगरindex as connection id, and use loopback channel शेष. */
	अगर (caअगरdev->conn_req.sockaddr.u.dgm.connection_id == UNDEF_CONNID) अणु
		caअगरdev->conn_req.sockaddr.u.dgm.connection_id = dev->अगरindex;
		caअगरdev->conn_req.protocol = CAIFPROTO_DATAGRAM_LOOP;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ipcaअगर_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			     काष्ठा nlattr *data[],
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा chnl_net *caअगरdev;
	ASSERT_RTNL();
	caअगरdev = netdev_priv(dev);
	caअगर_netlink_parms(data, &caअगरdev->conn_req);
	netdev_state_change(dev);
	वापस 0;
पूर्ण

अटल माप_प्रकार ipcaअगर_get_size(स्थिर काष्ठा net_device *dev)
अणु
	वापस
		/* IFLA_CAIF_IPV4_CONNID */
		nla_total_size(4) +
		/* IFLA_CAIF_IPV6_CONNID */
		nla_total_size(4) +
		/* IFLA_CAIF_LOOPBACK */
		nla_total_size(2) +
		0;
पूर्ण

अटल स्थिर काष्ठा nla_policy ipcaअगर_policy[IFLA_CAIF_MAX + 1] = अणु
	[IFLA_CAIF_IPV4_CONNID]	      = अणु .type = NLA_U32 पूर्ण,
	[IFLA_CAIF_IPV6_CONNID]	      = अणु .type = NLA_U32 पूर्ण,
	[IFLA_CAIF_LOOPBACK]	      = अणु .type = NLA_U8 पूर्ण
पूर्ण;


अटल काष्ठा rtnl_link_ops ipcaअगर_link_ops __पढ़ो_mostly = अणु
	.kind		= "caif",
	.priv_size	= माप(काष्ठा chnl_net),
	.setup		= ipcaअगर_net_setup,
	.maxtype	= IFLA_CAIF_MAX,
	.policy		= ipcaअगर_policy,
	.newlink	= ipcaअगर_newlink,
	.changelink	= ipcaअगर_changelink,
	.get_size	= ipcaअगर_get_size,
	.fill_info	= ipcaअगर_fill_info,

पूर्ण;

अटल पूर्णांक __init chnl_init_module(व्योम)
अणु
	वापस rtnl_link_रेजिस्टर(&ipcaअगर_link_ops);
पूर्ण

अटल व्योम __निकास chnl_निकास_module(व्योम)
अणु
	काष्ठा chnl_net *dev = शून्य;
	काष्ठा list_head *list_node;
	काष्ठा list_head *_पंचांगp;
	rtnl_link_unरेजिस्टर(&ipcaअगर_link_ops);
	rtnl_lock();
	list_क्रम_each_safe(list_node, _पंचांगp, &chnl_net_list) अणु
		dev = list_entry(list_node, काष्ठा chnl_net, list_field);
		list_del(list_node);
		delete_device(dev);
	पूर्ण
	rtnl_unlock();
पूर्ण

module_init(chnl_init_module);
module_निकास(chnl_निकास_module);
