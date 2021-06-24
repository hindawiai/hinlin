<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * net.c - Networking component क्रम Mostcore
 *
 * Copyright (C) 2015, Microchip Technology Germany II GmbH & Co. KG
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश <linux/kobject.h>
#समावेश <linux/most.h>

#घोषणा MEP_HDR_LEN 8
#घोषणा MDP_HDR_LEN 16
#घोषणा MAMAC_DATA_LEN (1024 - MDP_HDR_LEN)

#घोषणा PMHL 5

#घोषणा PMS_TELID_UNSEGM_MAMAC	0x0A
#घोषणा PMS_FIFONO_MDP		0x01
#घोषणा PMS_FIFONO_MEP		0x04
#घोषणा PMS_MSGTYPE_DATA	0x04
#घोषणा PMS_DEF_PRIO		0
#घोषणा MEP_DEF_RETRY		15

#घोषणा PMS_FIFONO_MASK		0x07
#घोषणा PMS_FIFONO_SHIFT	3
#घोषणा PMS_RETRY_SHIFT		4
#घोषणा PMS_TELID_MASK		0x0F
#घोषणा PMS_TELID_SHIFT		4

#घोषणा HB(value)		((u8)((u16)(value) >> 8))
#घोषणा LB(value)		((u8)(value))

#घोषणा EXTRACT_BIT_SET(bitset_name, value) \
	(((value) >> bitset_name##_SHIFT) & bitset_name##_MASK)

#घोषणा PMS_IS_MEP(buf, len) \
	((len) > MEP_HDR_LEN && \
	 EXTRACT_BIT_SET(PMS_FIFONO, (buf)[3]) == PMS_FIFONO_MEP)

अटल अंतरभूत bool pms_is_mamac(अक्षर *buf, u32 len)
अणु
	वापस (len > MDP_HDR_LEN &&
		EXTRACT_BIT_SET(PMS_FIFONO, buf[3]) == PMS_FIFONO_MDP &&
		EXTRACT_BIT_SET(PMS_TELID, buf[14]) == PMS_TELID_UNSEGM_MAMAC);
पूर्ण

काष्ठा net_dev_channel अणु
	bool linked;
	पूर्णांक ch_id;
पूर्ण;

काष्ठा net_dev_context अणु
	काष्ठा most_पूर्णांकerface *अगरace;
	bool is_mamac;
	काष्ठा net_device *dev;
	काष्ठा net_dev_channel rx;
	काष्ठा net_dev_channel tx;
	काष्ठा list_head list;
पूर्ण;

अटल काष्ठा list_head net_devices = LIST_HEAD_INIT(net_devices);
अटल DEFINE_MUTEX(probe_disc_mt); /* ch->linked = true, most_nd_खोलो */
अटल DEFINE_SPINLOCK(list_lock); /* list_head, ch->linked = false, dev_hold */
अटल काष्ठा most_component comp;

अटल पूर्णांक skb_to_mamac(स्थिर काष्ठा sk_buff *skb, काष्ठा mbo *mbo)
अणु
	u8 *buff = mbo->virt_address;
	अटल स्थिर u8 broadcast[] = अणु 0x03, 0xFF पूर्ण;
	स्थिर u8 *dest_addr = skb->data + 4;
	स्थिर u8 *eth_type = skb->data + 12;
	अचिन्हित पूर्णांक payload_len = skb->len - ETH_HLEN;
	अचिन्हित पूर्णांक mdp_len = payload_len + MDP_HDR_LEN;

	अगर (mdp_len < skb->len) अणु
		pr_err("drop: too large packet! (%u)\n", skb->len);
		वापस -EINVAL;
	पूर्ण

	अगर (mbo->buffer_length < mdp_len) अणु
		pr_err("drop: too small buffer! (%d for %d)\n",
		       mbo->buffer_length, mdp_len);
		वापस -EINVAL;
	पूर्ण

	अगर (skb->len < ETH_HLEN) अणु
		pr_err("drop: too small packet! (%d)\n", skb->len);
		वापस -EINVAL;
	पूर्ण

	अगर (dest_addr[0] == 0xFF && dest_addr[1] == 0xFF)
		dest_addr = broadcast;

	*buff++ = HB(mdp_len - 2);
	*buff++ = LB(mdp_len - 2);

	*buff++ = PMHL;
	*buff++ = (PMS_FIFONO_MDP << PMS_FIFONO_SHIFT) | PMS_MSGTYPE_DATA;
	*buff++ = PMS_DEF_PRIO;
	*buff++ = dest_addr[0];
	*buff++ = dest_addr[1];
	*buff++ = 0x00;

	*buff++ = HB(payload_len + 6);
	*buff++ = LB(payload_len + 6);

	/* end of FPH here */

	*buff++ = eth_type[0];
	*buff++ = eth_type[1];
	*buff++ = 0;
	*buff++ = 0;

	*buff++ = PMS_TELID_UNSEGM_MAMAC << 4 | HB(payload_len);
	*buff++ = LB(payload_len);

	स_नकल(buff, skb->data + ETH_HLEN, payload_len);
	mbo->buffer_length = mdp_len;
	वापस 0;
पूर्ण

अटल पूर्णांक skb_to_mep(स्थिर काष्ठा sk_buff *skb, काष्ठा mbo *mbo)
अणु
	u8 *buff = mbo->virt_address;
	अचिन्हित पूर्णांक mep_len = skb->len + MEP_HDR_LEN;

	अगर (mep_len < skb->len) अणु
		pr_err("drop: too large packet! (%u)\n", skb->len);
		वापस -EINVAL;
	पूर्ण

	अगर (mbo->buffer_length < mep_len) अणु
		pr_err("drop: too small buffer! (%d for %d)\n",
		       mbo->buffer_length, mep_len);
		वापस -EINVAL;
	पूर्ण

	*buff++ = HB(mep_len - 2);
	*buff++ = LB(mep_len - 2);

	*buff++ = PMHL;
	*buff++ = (PMS_FIFONO_MEP << PMS_FIFONO_SHIFT) | PMS_MSGTYPE_DATA;
	*buff++ = (MEP_DEF_RETRY << PMS_RETRY_SHIFT) | PMS_DEF_PRIO;
	*buff++ = 0;
	*buff++ = 0;
	*buff++ = 0;

	स_नकल(buff, skb->data, skb->len);
	mbo->buffer_length = mep_len;
	वापस 0;
पूर्ण

अटल पूर्णांक most_nd_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा net_dev_context *nd = netdev_priv(dev);
	पूर्णांक err = eth_mac_addr(dev, p);

	अगर (err)
		वापस err;

	nd->is_mamac =
		(dev->dev_addr[0] == 0 && dev->dev_addr[1] == 0 &&
		 dev->dev_addr[2] == 0 && dev->dev_addr[3] == 0);

	/*
	 * Set शेष MTU क्रम the given packet type.
	 * It is still possible to change MTU using ip tools afterwards.
	 */
	dev->mtu = nd->is_mamac ? MAMAC_DATA_LEN : ETH_DATA_LEN;

	वापस 0;
पूर्ण

अटल व्योम on_netinfo(काष्ठा most_पूर्णांकerface *अगरace,
		       अचिन्हित अक्षर link_stat, अचिन्हित अक्षर *mac_addr);

अटल पूर्णांक most_nd_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा net_dev_context *nd = netdev_priv(dev);
	पूर्णांक ret = 0;

	mutex_lock(&probe_disc_mt);

	अगर (most_start_channel(nd->अगरace, nd->rx.ch_id, &comp)) अणु
		netdev_err(dev, "most_start_channel() failed\n");
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	अगर (most_start_channel(nd->अगरace, nd->tx.ch_id, &comp)) अणु
		netdev_err(dev, "most_start_channel() failed\n");
		most_stop_channel(nd->अगरace, nd->rx.ch_id, &comp);
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	netअगर_carrier_off(dev);
	अगर (is_valid_ether_addr(dev->dev_addr))
		netअगर_करोrmant_off(dev);
	अन्यथा
		netअगर_करोrmant_on(dev);
	netअगर_wake_queue(dev);
	अगर (nd->अगरace->request_netinfo)
		nd->अगरace->request_netinfo(nd->अगरace, nd->tx.ch_id, on_netinfo);

unlock:
	mutex_unlock(&probe_disc_mt);
	वापस ret;
पूर्ण

अटल पूर्णांक most_nd_stop(काष्ठा net_device *dev)
अणु
	काष्ठा net_dev_context *nd = netdev_priv(dev);

	netअगर_stop_queue(dev);
	अगर (nd->अगरace->request_netinfo)
		nd->अगरace->request_netinfo(nd->अगरace, nd->tx.ch_id, शून्य);
	most_stop_channel(nd->अगरace, nd->rx.ch_id, &comp);
	most_stop_channel(nd->अगरace, nd->tx.ch_id, &comp);

	वापस 0;
पूर्ण

अटल netdev_tx_t most_nd_start_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	काष्ठा net_dev_context *nd = netdev_priv(dev);
	काष्ठा mbo *mbo;
	पूर्णांक ret;

	mbo = most_get_mbo(nd->अगरace, nd->tx.ch_id, &comp);

	अगर (!mbo) अणु
		netअगर_stop_queue(dev);
		dev->stats.tx_fअगरo_errors++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (nd->is_mamac)
		ret = skb_to_mamac(skb, mbo);
	अन्यथा
		ret = skb_to_mep(skb, mbo);

	अगर (ret) अणु
		most_put_mbo(mbo);
		dev->stats.tx_dropped++;
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	most_submit_mbo(mbo);
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;
	kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops most_nd_ops = अणु
	.nकरो_खोलो = most_nd_खोलो,
	.nकरो_stop = most_nd_stop,
	.nकरो_start_xmit = most_nd_start_xmit,
	.nकरो_set_mac_address = most_nd_set_mac_address,
पूर्ण;

अटल व्योम most_nd_setup(काष्ठा net_device *dev)
अणु
	ether_setup(dev);
	dev->netdev_ops = &most_nd_ops;
पूर्ण

अटल काष्ठा net_dev_context *get_net_dev(काष्ठा most_पूर्णांकerface *अगरace)
अणु
	काष्ठा net_dev_context *nd;

	list_क्रम_each_entry(nd, &net_devices, list)
		अगर (nd->अगरace == अगरace)
			वापस nd;
	वापस शून्य;
पूर्ण

अटल काष्ठा net_dev_context *get_net_dev_hold(काष्ठा most_पूर्णांकerface *अगरace)
अणु
	काष्ठा net_dev_context *nd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&list_lock, flags);
	nd = get_net_dev(अगरace);
	अगर (nd && nd->rx.linked && nd->tx.linked)
		dev_hold(nd->dev);
	अन्यथा
		nd = शून्य;
	spin_unlock_irqrestore(&list_lock, flags);
	वापस nd;
पूर्ण

अटल पूर्णांक comp_probe_channel(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_idx,
			      काष्ठा most_channel_config *ccfg, अक्षर *name,
			      अक्षर *args)
अणु
	काष्ठा net_dev_context *nd;
	काष्ठा net_dev_channel *ch;
	काष्ठा net_device *dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!अगरace)
		वापस -EINVAL;

	अगर (ccfg->data_type != MOST_CH_ASYNC)
		वापस -EINVAL;

	mutex_lock(&probe_disc_mt);
	nd = get_net_dev(अगरace);
	अगर (!nd) अणु
		dev = alloc_netdev(माप(काष्ठा net_dev_context), "meth%d",
				   NET_NAME_UNKNOWN, most_nd_setup);
		अगर (!dev) अणु
			ret = -ENOMEM;
			जाओ unlock;
		पूर्ण

		nd = netdev_priv(dev);
		nd->अगरace = अगरace;
		nd->dev = dev;

		spin_lock_irqsave(&list_lock, flags);
		list_add(&nd->list, &net_devices);
		spin_unlock_irqrestore(&list_lock, flags);

		ch = ccfg->direction == MOST_CH_TX ? &nd->tx : &nd->rx;
	पूर्ण अन्यथा अणु
		ch = ccfg->direction == MOST_CH_TX ? &nd->tx : &nd->rx;
		अगर (ch->linked) अणु
			pr_err("direction is allocated\n");
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण

		अगर (रेजिस्टर_netdev(nd->dev)) अणु
			pr_err("register_netdev() failed\n");
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण
	पूर्ण
	ch->ch_id = channel_idx;
	ch->linked = true;

unlock:
	mutex_unlock(&probe_disc_mt);
	वापस ret;
पूर्ण

अटल पूर्णांक comp_disconnect_channel(काष्ठा most_पूर्णांकerface *अगरace,
				   पूर्णांक channel_idx)
अणु
	काष्ठा net_dev_context *nd;
	काष्ठा net_dev_channel *ch;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	mutex_lock(&probe_disc_mt);
	nd = get_net_dev(अगरace);
	अगर (!nd) अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	अगर (nd->rx.linked && channel_idx == nd->rx.ch_id) अणु
		ch = &nd->rx;
	पूर्ण अन्यथा अगर (nd->tx.linked && channel_idx == nd->tx.ch_id) अणु
		ch = &nd->tx;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	अगर (nd->rx.linked && nd->tx.linked) अणु
		spin_lock_irqsave(&list_lock, flags);
		ch->linked = false;
		spin_unlock_irqrestore(&list_lock, flags);

		/*
		 * करो not call most_stop_channel() here, because channels are
		 * going to be बंदd in nकरो_stop() after unरेजिस्टर_netdev()
		 */
		unरेजिस्टर_netdev(nd->dev);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&list_lock, flags);
		list_del(&nd->list);
		spin_unlock_irqrestore(&list_lock, flags);

		मुक्त_netdev(nd->dev);
	पूर्ण

unlock:
	mutex_unlock(&probe_disc_mt);
	वापस ret;
पूर्ण

अटल पूर्णांक comp_resume_tx_channel(काष्ठा most_पूर्णांकerface *अगरace,
				  पूर्णांक channel_idx)
अणु
	काष्ठा net_dev_context *nd;

	nd = get_net_dev_hold(अगरace);
	अगर (!nd)
		वापस 0;

	अगर (nd->tx.ch_id != channel_idx)
		जाओ put_nd;

	netअगर_wake_queue(nd->dev);

put_nd:
	dev_put(nd->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक comp_rx_data(काष्ठा mbo *mbo)
अणु
	स्थिर u32 zero = 0;
	काष्ठा net_dev_context *nd;
	अक्षर *buf = mbo->virt_address;
	u32 len = mbo->processed_length;
	काष्ठा sk_buff *skb;
	काष्ठा net_device *dev;
	अचिन्हित पूर्णांक skb_len;
	पूर्णांक ret = 0;

	nd = get_net_dev_hold(mbo->अगरp);
	अगर (!nd)
		वापस -EIO;

	अगर (nd->rx.ch_id != mbo->hdm_channel_id) अणु
		ret = -EIO;
		जाओ put_nd;
	पूर्ण

	dev = nd->dev;

	अगर (nd->is_mamac) अणु
		अगर (!pms_is_mamac(buf, len)) अणु
			ret = -EIO;
			जाओ put_nd;
		पूर्ण

		skb = dev_alloc_skb(len - MDP_HDR_LEN + 2 * ETH_ALEN + 2);
	पूर्ण अन्यथा अणु
		अगर (!PMS_IS_MEP(buf, len)) अणु
			ret = -EIO;
			जाओ put_nd;
		पूर्ण

		skb = dev_alloc_skb(len - MEP_HDR_LEN);
	पूर्ण

	अगर (!skb) अणु
		dev->stats.rx_dropped++;
		pr_err_once("drop packet: no memory for skb\n");
		जाओ out;
	पूर्ण

	skb->dev = dev;

	अगर (nd->is_mamac) अणु
		/* dest */
		ether_addr_copy(skb_put(skb, ETH_ALEN), dev->dev_addr);

		/* src */
		skb_put_data(skb, &zero, 4);
		skb_put_data(skb, buf + 5, 2);

		/* eth type */
		skb_put_data(skb, buf + 10, 2);

		buf += MDP_HDR_LEN;
		len -= MDP_HDR_LEN;
	पूर्ण अन्यथा अणु
		buf += MEP_HDR_LEN;
		len -= MEP_HDR_LEN;
	पूर्ण

	skb_put_data(skb, buf, len);
	skb->protocol = eth_type_trans(skb, dev);
	skb_len = skb->len;
	अगर (netअगर_rx(skb) == NET_RX_SUCCESS) अणु
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb_len;
	पूर्ण अन्यथा अणु
		dev->stats.rx_dropped++;
	पूर्ण

out:
	most_put_mbo(mbo);

put_nd:
	dev_put(nd->dev);
	वापस ret;
पूर्ण

अटल काष्ठा most_component comp = अणु
	.mod = THIS_MODULE,
	.name = "net",
	.probe_channel = comp_probe_channel,
	.disconnect_channel = comp_disconnect_channel,
	.tx_completion = comp_resume_tx_channel,
	.rx_completion = comp_rx_data,
पूर्ण;

अटल पूर्णांक __init most_net_init(व्योम)
अणु
	पूर्णांक err;

	err = most_रेजिस्टर_component(&comp);
	अगर (err)
		वापस err;
	err = most_रेजिस्टर_configfs_subsys(&comp);
	अगर (err) अणु
		most_deरेजिस्टर_component(&comp);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास most_net_निकास(व्योम)
अणु
	most_deरेजिस्टर_configfs_subsys(&comp);
	most_deरेजिस्टर_component(&comp);
पूर्ण

/**
 * on_netinfo - callback क्रम HDM to be inक्रमmed about HW's MAC
 * @param अगरace - most पूर्णांकerface instance
 * @param link_stat - link status
 * @param mac_addr - MAC address
 */
अटल व्योम on_netinfo(काष्ठा most_पूर्णांकerface *अगरace,
		       अचिन्हित अक्षर link_stat, अचिन्हित अक्षर *mac_addr)
अणु
	काष्ठा net_dev_context *nd;
	काष्ठा net_device *dev;
	स्थिर u8 *m = mac_addr;

	nd = get_net_dev_hold(अगरace);
	अगर (!nd)
		वापस;

	dev = nd->dev;

	अगर (link_stat)
		netअगर_carrier_on(dev);
	अन्यथा
		netअगर_carrier_off(dev);

	अगर (m && is_valid_ether_addr(m)) अणु
		अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
			netdev_info(dev, "set mac %pM\n", m);
			ether_addr_copy(dev->dev_addr, m);
			netअगर_करोrmant_off(dev);
		पूर्ण अन्यथा अगर (!ether_addr_equal(dev->dev_addr, m)) अणु
			netdev_warn(dev, "reject mac %pM\n", m);
		पूर्ण
	पूर्ण

	dev_put(nd->dev);
पूर्ण

module_init(most_net_init);
module_निकास(most_net_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrey Shvetsov <andrey.shvetsov@k2l.de>");
MODULE_DESCRIPTION("Networking Component Module for Mostcore");
