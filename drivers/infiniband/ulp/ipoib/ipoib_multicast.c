<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2004 Voltaire, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/ip.h>
#समावेश <linux/in.h>
#समावेश <linux/igmp.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/completion.h>
#समावेश <linux/slab.h>

#समावेश <net/dst.h>

#समावेश "ipoib.h"

#अगर_घोषित CONFIG_INFINIBAND_IPOIB_DEBUG
अटल पूर्णांक mcast_debug_level;

module_param(mcast_debug_level, पूर्णांक, 0644);
MODULE_PARM_DESC(mcast_debug_level,
		 "Enable multicast debug tracing if > 0");
#पूर्ण_अगर

काष्ठा ipoib_mcast_iter अणु
	काष्ठा net_device *dev;
	जोड़ ib_gid       mgid;
	अचिन्हित दीर्घ      created;
	अचिन्हित पूर्णांक       queuelen;
	अचिन्हित पूर्णांक       complete;
	अचिन्हित पूर्णांक       send_only;
पूर्ण;

/* join state that allows creating mcg with senकरोnly member request */
#घोषणा SENDONLY_FULLMEMBER_JOIN	8

/*
 * This should be called with the priv->lock held
 */
अटल व्योम __ipoib_mcast_schedule_join_thपढ़ो(काष्ठा ipoib_dev_priv *priv,
					       काष्ठा ipoib_mcast *mcast,
					       bool delay)
अणु
	अगर (!test_bit(IPOIB_FLAG_OPER_UP, &priv->flags))
		वापस;

	/*
	 * We will be scheduling *something*, so cancel whatever is
	 * currently scheduled first
	 */
	cancel_delayed_work(&priv->mcast_task);
	अगर (mcast && delay) अणु
		/*
		 * We had a failure and want to schedule a retry later
		 */
		mcast->backoff *= 2;
		अगर (mcast->backoff > IPOIB_MAX_BACKOFF_SECONDS)
			mcast->backoff = IPOIB_MAX_BACKOFF_SECONDS;
		mcast->delay_until = jअगरfies + (mcast->backoff * HZ);
		/*
		 * Mark this mcast क्रम its delay, but restart the
		 * task immediately.  The join task will make sure to
		 * clear out all entries without delays, and then
		 * schedule itself to run again when the earliest
		 * delay expires
		 */
		queue_delayed_work(priv->wq, &priv->mcast_task, 0);
	पूर्ण अन्यथा अगर (delay) अणु
		/*
		 * Special हाल of retrying after a failure to
		 * allocate the broadcast multicast group, रुको
		 * 1 second and try again
		 */
		queue_delayed_work(priv->wq, &priv->mcast_task, HZ);
	पूर्ण अन्यथा
		queue_delayed_work(priv->wq, &priv->mcast_task, 0);
पूर्ण

अटल व्योम ipoib_mcast_मुक्त(काष्ठा ipoib_mcast *mcast)
अणु
	काष्ठा net_device *dev = mcast->dev;
	पूर्णांक tx_dropped = 0;

	ipoib_dbg_mcast(ipoib_priv(dev), "deleting multicast group %pI6\n",
			mcast->mcmember.mgid.raw);

	/* हटाओ all neigh connected to this mcast */
	ipoib_del_neighs_by_gid(dev, mcast->mcmember.mgid.raw);

	अगर (mcast->ah)
		ipoib_put_ah(mcast->ah);

	जबतक (!skb_queue_empty(&mcast->pkt_queue)) अणु
		++tx_dropped;
		dev_kमुक्त_skb_any(skb_dequeue(&mcast->pkt_queue));
	पूर्ण

	netअगर_tx_lock_bh(dev);
	dev->stats.tx_dropped += tx_dropped;
	netअगर_tx_unlock_bh(dev);

	kमुक्त(mcast);
पूर्ण

अटल काष्ठा ipoib_mcast *ipoib_mcast_alloc(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_mcast *mcast;

	mcast = kzalloc(माप(*mcast), GFP_ATOMIC);
	अगर (!mcast)
		वापस शून्य;

	mcast->dev = dev;
	mcast->created = jअगरfies;
	mcast->delay_until = jअगरfies;
	mcast->backoff = 1;

	INIT_LIST_HEAD(&mcast->list);
	INIT_LIST_HEAD(&mcast->neigh_list);
	skb_queue_head_init(&mcast->pkt_queue);

	वापस mcast;
पूर्ण

अटल काष्ठा ipoib_mcast *__ipoib_mcast_find(काष्ठा net_device *dev, व्योम *mgid)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा rb_node *n = priv->multicast_tree.rb_node;

	जबतक (n) अणु
		काष्ठा ipoib_mcast *mcast;
		पूर्णांक ret;

		mcast = rb_entry(n, काष्ठा ipoib_mcast, rb_node);

		ret = स_भेद(mgid, mcast->mcmember.mgid.raw,
			     माप (जोड़ ib_gid));
		अगर (ret < 0)
			n = n->rb_left;
		अन्यथा अगर (ret > 0)
			n = n->rb_right;
		अन्यथा
			वापस mcast;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक __ipoib_mcast_add(काष्ठा net_device *dev, काष्ठा ipoib_mcast *mcast)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा rb_node **n = &priv->multicast_tree.rb_node, *pn = शून्य;

	जबतक (*n) अणु
		काष्ठा ipoib_mcast *पंचांगcast;
		पूर्णांक ret;

		pn = *n;
		पंचांगcast = rb_entry(pn, काष्ठा ipoib_mcast, rb_node);

		ret = स_भेद(mcast->mcmember.mgid.raw, पंचांगcast->mcmember.mgid.raw,
			     माप (जोड़ ib_gid));
		अगर (ret < 0)
			n = &pn->rb_left;
		अन्यथा अगर (ret > 0)
			n = &pn->rb_right;
		अन्यथा
			वापस -EEXIST;
	पूर्ण

	rb_link_node(&mcast->rb_node, pn, n);
	rb_insert_color(&mcast->rb_node, &priv->multicast_tree);

	वापस 0;
पूर्ण

अटल पूर्णांक ipoib_mcast_join_finish(काष्ठा ipoib_mcast *mcast,
				   काष्ठा ib_sa_mcmember_rec *mcmember)
अणु
	काष्ठा net_device *dev = mcast->dev;
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा rdma_netdev *rn = netdev_priv(dev);
	काष्ठा ipoib_ah *ah;
	काष्ठा rdma_ah_attr av;
	पूर्णांक ret;
	पूर्णांक set_qkey = 0;
	पूर्णांक mtu;

	mcast->mcmember = *mcmember;

	/* Set the multicast MTU and cached Q_Key beक्रमe we attach अगर it's
	 * the broadcast group.
	 */
	अगर (!स_भेद(mcast->mcmember.mgid.raw, priv->dev->broadcast + 4,
		    माप (जोड़ ib_gid))) अणु
		spin_lock_irq(&priv->lock);
		अगर (!priv->broadcast) अणु
			spin_unlock_irq(&priv->lock);
			वापस -EAGAIN;
		पूर्ण
		/*update priv member according to the new mcast*/
		priv->broadcast->mcmember.qkey = mcmember->qkey;
		priv->broadcast->mcmember.mtu = mcmember->mtu;
		priv->broadcast->mcmember.traffic_class = mcmember->traffic_class;
		priv->broadcast->mcmember.rate = mcmember->rate;
		priv->broadcast->mcmember.sl = mcmember->sl;
		priv->broadcast->mcmember.flow_label = mcmember->flow_label;
		priv->broadcast->mcmember.hop_limit = mcmember->hop_limit;
		/* assume अगर the admin and the mcast are the same both can be changed */
		mtu = rdma_mtu_क्रमागत_to_पूर्णांक(priv->ca,  priv->port,
					   priv->broadcast->mcmember.mtu);
		अगर (priv->mcast_mtu == priv->admin_mtu)
			priv->admin_mtu = IPOIB_UD_MTU(mtu);
		priv->mcast_mtu = IPOIB_UD_MTU(mtu);
		rn->mtu = priv->mcast_mtu;

		priv->qkey = be32_to_cpu(priv->broadcast->mcmember.qkey);
		spin_unlock_irq(&priv->lock);
		priv->tx_wr.remote_qkey = priv->qkey;
		set_qkey = 1;
	पूर्ण

	अगर (!test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags)) अणु
		अगर (test_and_set_bit(IPOIB_MCAST_FLAG_ATTACHED, &mcast->flags)) अणु
			ipoib_warn(priv, "multicast group %pI6 already attached\n",
				   mcast->mcmember.mgid.raw);

			वापस 0;
		पूर्ण

		ret = rn->attach_mcast(dev, priv->ca, &mcast->mcmember.mgid,
				       be16_to_cpu(mcast->mcmember.mlid),
				       set_qkey, priv->qkey);
		अगर (ret < 0) अणु
			ipoib_warn(priv, "couldn't attach QP to multicast group %pI6\n",
				   mcast->mcmember.mgid.raw);

			clear_bit(IPOIB_MCAST_FLAG_ATTACHED, &mcast->flags);
			वापस ret;
		पूर्ण
	पूर्ण

	स_रखो(&av, 0, माप(av));
	av.type = rdma_ah_find_type(priv->ca, priv->port);
	rdma_ah_set_dlid(&av, be16_to_cpu(mcast->mcmember.mlid));
	rdma_ah_set_port_num(&av, priv->port);
	rdma_ah_set_sl(&av, mcast->mcmember.sl);
	rdma_ah_set_अटल_rate(&av, mcast->mcmember.rate);

	rdma_ah_set_grh(&av, &mcast->mcmember.mgid,
			be32_to_cpu(mcast->mcmember.flow_label),
			0, mcast->mcmember.hop_limit,
			mcast->mcmember.traffic_class);

	ah = ipoib_create_ah(dev, priv->pd, &av);
	अगर (IS_ERR(ah)) अणु
		ipoib_warn(priv, "ib_address_create failed %ld\n",
			   -PTR_ERR(ah));
		/* use original error */
		वापस PTR_ERR(ah);
	पूर्ण
	spin_lock_irq(&priv->lock);
	mcast->ah = ah;
	spin_unlock_irq(&priv->lock);

	ipoib_dbg_mcast(priv, "MGID %pI6 AV %p, LID 0x%04x, SL %d\n",
			mcast->mcmember.mgid.raw,
			mcast->ah->ah,
			be16_to_cpu(mcast->mcmember.mlid),
			mcast->mcmember.sl);

	/* actually send any queued packets */
	netअगर_tx_lock_bh(dev);
	जबतक (!skb_queue_empty(&mcast->pkt_queue)) अणु
		काष्ठा sk_buff *skb = skb_dequeue(&mcast->pkt_queue);

		netअगर_tx_unlock_bh(dev);

		skb->dev = dev;

		ret = dev_queue_xmit(skb);
		अगर (ret)
			ipoib_warn(priv, "%s:dev_queue_xmit failed to re-queue packet, ret:%d\n",
				   __func__, ret);
		netअगर_tx_lock_bh(dev);
	पूर्ण
	netअगर_tx_unlock_bh(dev);

	वापस 0;
पूर्ण

व्योम ipoib_mcast_carrier_on_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipoib_dev_priv *priv = container_of(work, काष्ठा ipoib_dev_priv,
						   carrier_on_task);
	काष्ठा ib_port_attr attr;

	अगर (ib_query_port(priv->ca, priv->port, &attr) ||
	    attr.state != IB_PORT_ACTIVE) अणु
		ipoib_dbg(priv, "Keeping carrier off until IB port is active\n");
		वापस;
	पूर्ण
	/*
	 * Take rtnl_lock to aव्योम racing with ipoib_stop() and
	 * turning the carrier back on जबतक a device is being
	 * हटाओd.  However, ipoib_stop() will attempt to flush
	 * the workqueue जबतक holding the rtnl lock, so loop
	 * on trylock until either we get the lock or we see
	 * FLAG_OPER_UP go away as that संकेतs that we are bailing
	 * and can safely ignore the carrier on work.
	 */
	जबतक (!rtnl_trylock()) अणु
		अगर (!test_bit(IPOIB_FLAG_OPER_UP, &priv->flags))
			वापस;
		अन्यथा
			msleep(20);
	पूर्ण
	अगर (!ipoib_cm_admin_enabled(priv->dev))
		dev_set_mtu(priv->dev, min(priv->mcast_mtu, priv->admin_mtu));
	netअगर_carrier_on(priv->dev);
	rtnl_unlock();
पूर्ण

अटल पूर्णांक ipoib_mcast_join_complete(पूर्णांक status,
				     काष्ठा ib_sa_multicast *multicast)
अणु
	काष्ठा ipoib_mcast *mcast = multicast->context;
	काष्ठा net_device *dev = mcast->dev;
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_dbg_mcast(priv, "%sjoin completion for %pI6 (status %d)\n",
			test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags) ?
			"sendonly " : "",
			mcast->mcmember.mgid.raw, status);

	/* We trap क्रम port events ourselves. */
	अगर (status == -ENETRESET) अणु
		status = 0;
		जाओ out;
	पूर्ण

	अगर (!status)
		status = ipoib_mcast_join_finish(mcast, &multicast->rec);

	अगर (!status) अणु
		mcast->backoff = 1;
		mcast->delay_until = jअगरfies;

		/*
		 * Defer carrier on work to priv->wq to aव्योम a
		 * deadlock on rtnl_lock here.  Requeue our multicast
		 * work too, which will end up happening right after
		 * our carrier on task work and will allow us to
		 * send out all of the non-broadcast joins
		 */
		अगर (mcast == priv->broadcast) अणु
			spin_lock_irq(&priv->lock);
			queue_work(priv->wq, &priv->carrier_on_task);
			__ipoib_mcast_schedule_join_thपढ़ो(priv, शून्य, 0);
			जाओ out_locked;
		पूर्ण
	पूर्ण अन्यथा अणु
		bool silent_fail =
		    test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags) &&
		    status == -EINVAL;

		अगर (mcast->logcount < 20) अणु
			अगर (status == -ETIMEDOUT || status == -EAGAIN ||
			    silent_fail) अणु
				ipoib_dbg_mcast(priv, "%smulticast join failed for %pI6, status %d\n",
						test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags) ? "sendonly " : "",
						mcast->mcmember.mgid.raw, status);
			पूर्ण अन्यथा अणु
				ipoib_warn(priv, "%smulticast join failed for %pI6, status %d\n",
						test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags) ? "sendonly " : "",
					   mcast->mcmember.mgid.raw, status);
			पूर्ण

			अगर (!silent_fail)
				mcast->logcount++;
		पूर्ण

		अगर (test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags) &&
		    mcast->backoff >= 2) अणु
			/*
			 * We only retry senकरोnly joins once beक्रमe we drop
			 * the packet and quit trying to deal with the
			 * group.  However, we leave the group in the
			 * mcast list as an unjoined group.  If we want to
			 * try joining again, we simply queue up a packet
			 * and restart the join thपढ़ो.  The empty queue
			 * is why the join thपढ़ो ignores this group.
			 */
			mcast->backoff = 1;
			netअगर_tx_lock_bh(dev);
			जबतक (!skb_queue_empty(&mcast->pkt_queue)) अणु
				++dev->stats.tx_dropped;
				dev_kमुक्त_skb_any(skb_dequeue(&mcast->pkt_queue));
			पूर्ण
			netअगर_tx_unlock_bh(dev);
		पूर्ण अन्यथा अणु
			spin_lock_irq(&priv->lock);
			/* Requeue this join task with a backoff delay */
			__ipoib_mcast_schedule_join_thपढ़ो(priv, mcast, 1);
			जाओ out_locked;
		पूर्ण
	पूर्ण
out:
	spin_lock_irq(&priv->lock);
out_locked:
	/*
	 * Make sure to set mcast->mc beक्रमe we clear the busy flag to aव्योम
	 * racing with code that checks क्रम BUSY beक्रमe checking mcast->mc
	 */
	अगर (status)
		mcast->mc = शून्य;
	अन्यथा
		mcast->mc = multicast;
	clear_bit(IPOIB_MCAST_FLAG_BUSY, &mcast->flags);
	spin_unlock_irq(&priv->lock);
	complete(&mcast->करोne);

	वापस status;
पूर्ण

/*
 * Caller must hold 'priv->lock'
 */
अटल पूर्णांक ipoib_mcast_join(काष्ठा net_device *dev, काष्ठा ipoib_mcast *mcast)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा ib_sa_multicast *multicast;
	काष्ठा ib_sa_mcmember_rec rec = अणु
		.join_state = 1
	पूर्ण;
	ib_sa_comp_mask comp_mask;
	पूर्णांक ret = 0;

	अगर (!priv->broadcast ||
	    !test_bit(IPOIB_FLAG_OPER_UP, &priv->flags))
		वापस -EINVAL;

	init_completion(&mcast->करोne);
	set_bit(IPOIB_MCAST_FLAG_BUSY, &mcast->flags);

	ipoib_dbg_mcast(priv, "joining MGID %pI6\n", mcast->mcmember.mgid.raw);

	rec.mgid     = mcast->mcmember.mgid;
	rec.port_gid = priv->local_gid;
	rec.pkey     = cpu_to_be16(priv->pkey);

	comp_mask =
		IB_SA_MCMEMBER_REC_MGID		|
		IB_SA_MCMEMBER_REC_PORT_GID	|
		IB_SA_MCMEMBER_REC_PKEY		|
		IB_SA_MCMEMBER_REC_JOIN_STATE;

	अगर (mcast != priv->broadcast) अणु
		/*
		 * RFC 4391:
		 *  The MGID MUST use the same P_Key, Q_Key, SL, MTU,
		 *  and HopLimit as those used in the broadcast-GID.  The rest
		 *  of attributes SHOULD follow the values used in the
		 *  broadcast-GID as well.
		 */
		comp_mask |=
			IB_SA_MCMEMBER_REC_QKEY			|
			IB_SA_MCMEMBER_REC_MTU_SELECTOR		|
			IB_SA_MCMEMBER_REC_MTU			|
			IB_SA_MCMEMBER_REC_TRAFFIC_CLASS	|
			IB_SA_MCMEMBER_REC_RATE_SELECTOR	|
			IB_SA_MCMEMBER_REC_RATE			|
			IB_SA_MCMEMBER_REC_SL			|
			IB_SA_MCMEMBER_REC_FLOW_LABEL		|
			IB_SA_MCMEMBER_REC_HOP_LIMIT;

		rec.qkey	  = priv->broadcast->mcmember.qkey;
		rec.mtu_selector  = IB_SA_EQ;
		rec.mtu		  = priv->broadcast->mcmember.mtu;
		rec.traffic_class = priv->broadcast->mcmember.traffic_class;
		rec.rate_selector = IB_SA_EQ;
		rec.rate	  = priv->broadcast->mcmember.rate;
		rec.sl		  = priv->broadcast->mcmember.sl;
		rec.flow_label	  = priv->broadcast->mcmember.flow_label;
		rec.hop_limit	  = priv->broadcast->mcmember.hop_limit;

		/*
		 * Send-only IB Multicast joins work at the core IB layer but
		 * require specअगरic SM support.
		 * We can use such joins here only अगर the current SM supports that feature.
		 * However, अगर not, we emulate an Ethernet multicast send,
		 * which करोes not require a multicast subscription and will
		 * still send properly. The most appropriate thing to
		 * करो is to create the group अगर it करोesn't exist as that
		 * most बंदly emulates the behavior, from a user space
		 * application perspective, of Ethernet multicast operation.
		 */
		अगर (test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags))
			rec.join_state = SENDONLY_FULLMEMBER_JOIN;
	पूर्ण
	spin_unlock_irq(&priv->lock);

	multicast = ib_sa_join_multicast(&ipoib_sa_client, priv->ca, priv->port,
					 &rec, comp_mask, GFP_KERNEL,
					 ipoib_mcast_join_complete, mcast);
	spin_lock_irq(&priv->lock);
	अगर (IS_ERR(multicast)) अणु
		ret = PTR_ERR(multicast);
		ipoib_warn(priv, "ib_sa_join_multicast failed, status %d\n", ret);
		/* Requeue this join task with a backoff delay */
		__ipoib_mcast_schedule_join_thपढ़ो(priv, mcast, 1);
		clear_bit(IPOIB_MCAST_FLAG_BUSY, &mcast->flags);
		spin_unlock_irq(&priv->lock);
		complete(&mcast->करोne);
		spin_lock_irq(&priv->lock);
	पूर्ण
	वापस 0;
पूर्ण

व्योम ipoib_mcast_join_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipoib_dev_priv *priv =
		container_of(work, काष्ठा ipoib_dev_priv, mcast_task.work);
	काष्ठा net_device *dev = priv->dev;
	काष्ठा ib_port_attr port_attr;
	अचिन्हित दीर्घ delay_until = 0;
	काष्ठा ipoib_mcast *mcast = शून्य;

	अगर (!test_bit(IPOIB_FLAG_OPER_UP, &priv->flags))
		वापस;

	अगर (ib_query_port(priv->ca, priv->port, &port_attr)) अणु
		ipoib_dbg(priv, "ib_query_port() failed\n");
		वापस;
	पूर्ण
	अगर (port_attr.state != IB_PORT_ACTIVE) अणु
		ipoib_dbg(priv, "port state is not ACTIVE (state = %d) suspending join task\n",
			  port_attr.state);
		वापस;
	पूर्ण
	priv->local_lid = port_attr.lid;
	netअगर_addr_lock_bh(dev);

	अगर (!test_bit(IPOIB_FLAG_DEV_ADDR_SET, &priv->flags)) अणु
		netअगर_addr_unlock_bh(dev);
		वापस;
	पूर्ण
	netअगर_addr_unlock_bh(dev);

	spin_lock_irq(&priv->lock);
	अगर (!test_bit(IPOIB_FLAG_OPER_UP, &priv->flags))
		जाओ out;

	अगर (!priv->broadcast) अणु
		काष्ठा ipoib_mcast *broadcast;

		broadcast = ipoib_mcast_alloc(dev);
		अगर (!broadcast) अणु
			ipoib_warn(priv, "failed to allocate broadcast group\n");
			/*
			 * Restart us after a 1 second delay to retry
			 * creating our broadcast group and attaching to
			 * it.  Until this succeeds, this ipoib dev is
			 * completely stalled (multicast wise).
			 */
			__ipoib_mcast_schedule_join_thपढ़ो(priv, शून्य, 1);
			जाओ out;
		पूर्ण

		स_नकल(broadcast->mcmember.mgid.raw, priv->dev->broadcast + 4,
		       माप (जोड़ ib_gid));
		priv->broadcast = broadcast;

		__ipoib_mcast_add(dev, priv->broadcast);
	पूर्ण

	अगर (!test_bit(IPOIB_MCAST_FLAG_ATTACHED, &priv->broadcast->flags)) अणु
		अगर (IS_ERR_OR_शून्य(priv->broadcast->mc) &&
		    !test_bit(IPOIB_MCAST_FLAG_BUSY, &priv->broadcast->flags)) अणु
			mcast = priv->broadcast;
			अगर (mcast->backoff > 1 &&
			    समय_beक्रमe(jअगरfies, mcast->delay_until)) अणु
				delay_until = mcast->delay_until;
				mcast = शून्य;
			पूर्ण
		पूर्ण
		जाओ out;
	पूर्ण

	/*
	 * We'll never get here until the broadcast group is both allocated
	 * and attached
	 */
	list_क्रम_each_entry(mcast, &priv->multicast_list, list) अणु
		अगर (IS_ERR_OR_शून्य(mcast->mc) &&
		    !test_bit(IPOIB_MCAST_FLAG_BUSY, &mcast->flags) &&
		    (!test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags) ||
		     !skb_queue_empty(&mcast->pkt_queue))) अणु
			अगर (mcast->backoff == 1 ||
			    समय_after_eq(jअगरfies, mcast->delay_until)) अणु
				/* Found the next unjoined group */
				अगर (ipoib_mcast_join(dev, mcast)) अणु
					spin_unlock_irq(&priv->lock);
					वापस;
				पूर्ण
			पूर्ण अन्यथा अगर (!delay_until ||
				 समय_beक्रमe(mcast->delay_until, delay_until))
				delay_until = mcast->delay_until;
		पूर्ण
	पूर्ण

	mcast = शून्य;
	ipoib_dbg_mcast(priv, "successfully started all multicast joins\n");

out:
	अगर (delay_until) अणु
		cancel_delayed_work(&priv->mcast_task);
		queue_delayed_work(priv->wq, &priv->mcast_task,
				   delay_until - jअगरfies);
	पूर्ण
	अगर (mcast)
		ipoib_mcast_join(dev, mcast);

	spin_unlock_irq(&priv->lock);
पूर्ण

व्योम ipoib_mcast_start_thपढ़ो(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	अचिन्हित दीर्घ flags;

	ipoib_dbg_mcast(priv, "starting multicast thread\n");

	spin_lock_irqsave(&priv->lock, flags);
	__ipoib_mcast_schedule_join_thपढ़ो(priv, शून्य, 0);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

व्योम ipoib_mcast_stop_thपढ़ो(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_dbg_mcast(priv, "stopping multicast thread\n");

	cancel_delayed_work_sync(&priv->mcast_task);
पूर्ण

अटल पूर्णांक ipoib_mcast_leave(काष्ठा net_device *dev, काष्ठा ipoib_mcast *mcast)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा rdma_netdev *rn = netdev_priv(dev);
	पूर्णांक ret = 0;

	अगर (test_and_clear_bit(IPOIB_MCAST_FLAG_BUSY, &mcast->flags))
		ipoib_warn(priv, "ipoib_mcast_leave on an in-flight join\n");

	अगर (!IS_ERR_OR_शून्य(mcast->mc))
		ib_sa_मुक्त_multicast(mcast->mc);

	अगर (test_and_clear_bit(IPOIB_MCAST_FLAG_ATTACHED, &mcast->flags)) अणु
		ipoib_dbg_mcast(priv, "leaving MGID %pI6\n",
				mcast->mcmember.mgid.raw);

		/* Remove ourselves from the multicast group */
		ret = rn->detach_mcast(dev, priv->ca, &mcast->mcmember.mgid,
				       be16_to_cpu(mcast->mcmember.mlid));
		अगर (ret)
			ipoib_warn(priv, "ib_detach_mcast failed (result = %d)\n", ret);
	पूर्ण अन्यथा अगर (!test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags))
		ipoib_dbg(priv, "leaving with no mcmember but not a "
			  "SENDONLY join\n");

	वापस 0;
पूर्ण

/*
 * Check अगर the multicast group is senकरोnly. If so हटाओ it from the maps
 * and add to the हटाओ list
 */
व्योम ipoib_check_and_add_mcast_senकरोnly(काष्ठा ipoib_dev_priv *priv, u8 *mgid,
				काष्ठा list_head *हटाओ_list)
अणु
	/* Is this multicast ? */
	अगर (*mgid == 0xff) अणु
		काष्ठा ipoib_mcast *mcast = __ipoib_mcast_find(priv->dev, mgid);

		अगर (mcast && test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags)) अणु
			list_del(&mcast->list);
			rb_erase(&mcast->rb_node, &priv->multicast_tree);
			list_add_tail(&mcast->list, हटाओ_list);
		पूर्ण
	पूर्ण
पूर्ण

व्योम ipoib_mcast_हटाओ_list(काष्ठा list_head *हटाओ_list)
अणु
	काष्ठा ipoib_mcast *mcast, *पंचांगcast;

	/*
	 * make sure the in-flight joins have finished beक्रमe we attempt
	 * to leave
	 */
	list_क्रम_each_entry_safe(mcast, पंचांगcast, हटाओ_list, list)
		अगर (test_bit(IPOIB_MCAST_FLAG_BUSY, &mcast->flags))
			रुको_क्रम_completion(&mcast->करोne);

	list_क्रम_each_entry_safe(mcast, पंचांगcast, हटाओ_list, list) अणु
		ipoib_mcast_leave(mcast->dev, mcast);
		ipoib_mcast_मुक्त(mcast);
	पूर्ण
पूर्ण

व्योम ipoib_mcast_send(काष्ठा net_device *dev, u8 *daddr, काष्ठा sk_buff *skb)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	काष्ठा rdma_netdev *rn = netdev_priv(dev);
	काष्ठा ipoib_mcast *mcast;
	अचिन्हित दीर्घ flags;
	व्योम *mgid = daddr + 4;

	spin_lock_irqsave(&priv->lock, flags);

	अगर (!test_bit(IPOIB_FLAG_OPER_UP, &priv->flags)		||
	    !priv->broadcast					||
	    !test_bit(IPOIB_MCAST_FLAG_ATTACHED, &priv->broadcast->flags)) अणु
		++dev->stats.tx_dropped;
		dev_kमुक्त_skb_any(skb);
		जाओ unlock;
	पूर्ण

	mcast = __ipoib_mcast_find(dev, mgid);
	अगर (!mcast || !mcast->ah) अणु
		अगर (!mcast) अणु
			/* Let's create a new send only group now */
			ipoib_dbg_mcast(priv, "setting up send only multicast group for %pI6\n",
					mgid);

			mcast = ipoib_mcast_alloc(dev);
			अगर (!mcast) अणु
				ipoib_warn(priv, "unable to allocate memory "
					   "for multicast structure\n");
				++dev->stats.tx_dropped;
				dev_kमुक्त_skb_any(skb);
				जाओ unlock;
			पूर्ण

			set_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags);
			स_नकल(mcast->mcmember.mgid.raw, mgid,
			       माप (जोड़ ib_gid));
			__ipoib_mcast_add(dev, mcast);
			list_add_tail(&mcast->list, &priv->multicast_list);
		पूर्ण
		अगर (skb_queue_len(&mcast->pkt_queue) < IPOIB_MAX_MCAST_QUEUE) अणु
			/* put pseuकरोheader back on क्रम next समय */
			skb_push(skb, माप(काष्ठा ipoib_pseuकरो_header));
			skb_queue_tail(&mcast->pkt_queue, skb);
		पूर्ण अन्यथा अणु
			++dev->stats.tx_dropped;
			dev_kमुक्त_skb_any(skb);
		पूर्ण
		अगर (!test_bit(IPOIB_MCAST_FLAG_BUSY, &mcast->flags)) अणु
			__ipoib_mcast_schedule_join_thपढ़ो(priv, शून्य, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा ipoib_neigh *neigh;

		spin_unlock_irqrestore(&priv->lock, flags);
		neigh = ipoib_neigh_get(dev, daddr);
		spin_lock_irqsave(&priv->lock, flags);
		अगर (!neigh) अणु
			neigh = ipoib_neigh_alloc(daddr, dev);
			/* Make sure that the neigh will be added only
			 * once to mcast list.
			 */
			अगर (neigh && list_empty(&neigh->list)) अणु
				kref_get(&mcast->ah->ref);
				neigh->ah	= mcast->ah;
				neigh->ah->valid = 1;
				list_add_tail(&neigh->list, &mcast->neigh_list);
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&priv->lock, flags);
		mcast->ah->last_send = rn->send(dev, skb, mcast->ah->ah,
						IB_MULTICAST_QPN);
		अगर (neigh)
			ipoib_neigh_put(neigh);
		वापस;
	पूर्ण

unlock:
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

व्योम ipoib_mcast_dev_flush(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
	LIST_HEAD(हटाओ_list);
	काष्ठा ipoib_mcast *mcast, *पंचांगcast;
	अचिन्हित दीर्घ flags;

	mutex_lock(&priv->mcast_mutex);
	ipoib_dbg_mcast(priv, "flushing multicast list\n");

	spin_lock_irqsave(&priv->lock, flags);

	list_क्रम_each_entry_safe(mcast, पंचांगcast, &priv->multicast_list, list) अणु
		list_del(&mcast->list);
		rb_erase(&mcast->rb_node, &priv->multicast_tree);
		list_add_tail(&mcast->list, &हटाओ_list);
	पूर्ण

	अगर (priv->broadcast) अणु
		rb_erase(&priv->broadcast->rb_node, &priv->multicast_tree);
		list_add_tail(&priv->broadcast->list, &हटाओ_list);
		priv->broadcast = शून्य;
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);

	ipoib_mcast_हटाओ_list(&हटाओ_list);
	mutex_unlock(&priv->mcast_mutex);
पूर्ण

अटल पूर्णांक ipoib_mcast_addr_is_valid(स्थिर u8 *addr, स्थिर u8 *broadcast)
अणु
	/* reserved QPN, prefix, scope */
	अगर (स_भेद(addr, broadcast, 6))
		वापस 0;
	/* signature lower, pkey */
	अगर (स_भेद(addr + 7, broadcast + 7, 3))
		वापस 0;
	वापस 1;
पूर्ण

व्योम ipoib_mcast_restart_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipoib_dev_priv *priv =
		container_of(work, काष्ठा ipoib_dev_priv, restart_task);
	काष्ठा net_device *dev = priv->dev;
	काष्ठा netdev_hw_addr *ha;
	काष्ठा ipoib_mcast *mcast, *पंचांगcast;
	LIST_HEAD(हटाओ_list);
	काष्ठा ib_sa_mcmember_rec rec;

	अगर (!test_bit(IPOIB_FLAG_OPER_UP, &priv->flags))
		/*
		 * लघुcut...on shutकरोwn flush is called next, just
		 * let it करो all the work
		 */
		वापस;

	ipoib_dbg_mcast(priv, "restarting multicast task\n");

	netअगर_addr_lock_bh(dev);
	spin_lock_irq(&priv->lock);

	/*
	 * Unक्रमtunately, the networking core only gives us a list of all of
	 * the multicast hardware addresses. We need to figure out which ones
	 * are new and which ones have been हटाओd
	 */

	/* Clear out the found flag */
	list_क्रम_each_entry(mcast, &priv->multicast_list, list)
		clear_bit(IPOIB_MCAST_FLAG_FOUND, &mcast->flags);

	/* Mark all of the entries that are found or करोn't exist */
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		जोड़ ib_gid mgid;

		अगर (!ipoib_mcast_addr_is_valid(ha->addr, dev->broadcast))
			जारी;

		स_नकल(mgid.raw, ha->addr + 4, माप(mgid));

		mcast = __ipoib_mcast_find(dev, &mgid);
		अगर (!mcast || test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags)) अणु
			काष्ठा ipoib_mcast *nmcast;

			/* ignore group which is directly joined by userspace */
			अगर (test_bit(IPOIB_FLAG_UMCAST, &priv->flags) &&
			    !ib_sa_get_mcmember_rec(priv->ca, priv->port, &mgid, &rec)) अणु
				ipoib_dbg_mcast(priv, "ignoring multicast entry for mgid %pI6\n",
						mgid.raw);
				जारी;
			पूर्ण

			/* Not found or send-only group, let's add a new entry */
			ipoib_dbg_mcast(priv, "adding multicast entry for mgid %pI6\n",
					mgid.raw);

			nmcast = ipoib_mcast_alloc(dev);
			अगर (!nmcast) अणु
				ipoib_warn(priv, "unable to allocate memory for multicast structure\n");
				जारी;
			पूर्ण

			set_bit(IPOIB_MCAST_FLAG_FOUND, &nmcast->flags);

			nmcast->mcmember.mgid = mgid;

			अगर (mcast) अणु
				/* Destroy the send only entry */
				list_move_tail(&mcast->list, &हटाओ_list);

				rb_replace_node(&mcast->rb_node,
						&nmcast->rb_node,
						&priv->multicast_tree);
			पूर्ण अन्यथा
				__ipoib_mcast_add(dev, nmcast);

			list_add_tail(&nmcast->list, &priv->multicast_list);
		पूर्ण

		अगर (mcast)
			set_bit(IPOIB_MCAST_FLAG_FOUND, &mcast->flags);
	पूर्ण

	/* Remove all of the entries करोn't exist anymore */
	list_क्रम_each_entry_safe(mcast, पंचांगcast, &priv->multicast_list, list) अणु
		अगर (!test_bit(IPOIB_MCAST_FLAG_FOUND, &mcast->flags) &&
		    !test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags)) अणु
			ipoib_dbg_mcast(priv, "deleting multicast group %pI6\n",
					mcast->mcmember.mgid.raw);

			rb_erase(&mcast->rb_node, &priv->multicast_tree);

			/* Move to the हटाओ list */
			list_move_tail(&mcast->list, &हटाओ_list);
		पूर्ण
	पूर्ण

	spin_unlock_irq(&priv->lock);
	netअगर_addr_unlock_bh(dev);

	ipoib_mcast_हटाओ_list(&हटाओ_list);

	/*
	 * Double check that we are still up
	 */
	अगर (test_bit(IPOIB_FLAG_OPER_UP, &priv->flags)) अणु
		spin_lock_irq(&priv->lock);
		__ipoib_mcast_schedule_join_thपढ़ो(priv, शून्य, 0);
		spin_unlock_irq(&priv->lock);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_INFINIBAND_IPOIB_DEBUG

काष्ठा ipoib_mcast_iter *ipoib_mcast_iter_init(काष्ठा net_device *dev)
अणु
	काष्ठा ipoib_mcast_iter *iter;

	iter = kदो_स्मृति(माप(*iter), GFP_KERNEL);
	अगर (!iter)
		वापस शून्य;

	iter->dev = dev;
	स_रखो(iter->mgid.raw, 0, 16);

	अगर (ipoib_mcast_iter_next(iter)) अणु
		kमुक्त(iter);
		वापस शून्य;
	पूर्ण

	वापस iter;
पूर्ण

पूर्णांक ipoib_mcast_iter_next(काष्ठा ipoib_mcast_iter *iter)
अणु
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(iter->dev);
	काष्ठा rb_node *n;
	काष्ठा ipoib_mcast *mcast;
	पूर्णांक ret = 1;

	spin_lock_irq(&priv->lock);

	n = rb_first(&priv->multicast_tree);

	जबतक (n) अणु
		mcast = rb_entry(n, काष्ठा ipoib_mcast, rb_node);

		अगर (स_भेद(iter->mgid.raw, mcast->mcmember.mgid.raw,
			   माप (जोड़ ib_gid)) < 0) अणु
			iter->mgid      = mcast->mcmember.mgid;
			iter->created   = mcast->created;
			iter->queuelen  = skb_queue_len(&mcast->pkt_queue);
			iter->complete  = !!mcast->ah;
			iter->send_only = !!(mcast->flags & (1 << IPOIB_MCAST_FLAG_SENDONLY));

			ret = 0;

			अवरोध;
		पूर्ण

		n = rb_next(n);
	पूर्ण

	spin_unlock_irq(&priv->lock);

	वापस ret;
पूर्ण

व्योम ipoib_mcast_iter_पढ़ो(काष्ठा ipoib_mcast_iter *iter,
			   जोड़ ib_gid *mgid,
			   अचिन्हित दीर्घ *created,
			   अचिन्हित पूर्णांक *queuelen,
			   अचिन्हित पूर्णांक *complete,
			   अचिन्हित पूर्णांक *send_only)
अणु
	*mgid      = iter->mgid;
	*created   = iter->created;
	*queuelen  = iter->queuelen;
	*complete  = iter->complete;
	*send_only = iter->send_only;
पूर्ण

#पूर्ण_अगर /* CONFIG_INFINIBAND_IPOIB_DEBUG */
