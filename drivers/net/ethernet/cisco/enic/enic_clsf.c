<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_link.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/in.h>
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <net/flow_dissector.h>
#समावेश "enic_res.h"
#समावेश "enic_clsf.h"

/* enic_addfltr_5t - Add ipv4 5tuple filter
 *	@enic: enic काष्ठा of vnic
 *	@keys: flow_keys of ipv4 5tuple
 *	@rq: rq number to steer to
 *
 * This function वापसs filter_id(hardware_id) of the filter
 * added. In हाल of error it वापसs a negative number.
 */
पूर्णांक enic_addfltr_5t(काष्ठा enic *enic, काष्ठा flow_keys *keys, u16 rq)
अणु
	पूर्णांक res;
	काष्ठा filter data;

	चयन (keys->basic.ip_proto) अणु
	हाल IPPROTO_TCP:
		data.u.ipv4.protocol = PROTO_TCP;
		अवरोध;
	हाल IPPROTO_UDP:
		data.u.ipv4.protocol = PROTO_UDP;
		अवरोध;
	शेष:
		वापस -EPROTONOSUPPORT;
	पूर्ण

	data.type = FILTER_IPV4_5TUPLE;
	data.u.ipv4.src_addr = ntohl(keys->addrs.v4addrs.src);
	data.u.ipv4.dst_addr = ntohl(keys->addrs.v4addrs.dst);
	data.u.ipv4.src_port = ntohs(keys->ports.src);
	data.u.ipv4.dst_port = ntohs(keys->ports.dst);
	data.u.ipv4.flags = FILTER_FIELDS_IPV4_5TUPLE;

	spin_lock_bh(&enic->devcmd_lock);
	res = vnic_dev_classअगरier(enic->vdev, CLSF_ADD, &rq, &data);
	spin_unlock_bh(&enic->devcmd_lock);
	res = (res == 0) ? rq : res;

	वापस res;
पूर्ण

/* enic_delfltr - Delete clsf filter
 *	@enic: enic काष्ठा of vnic
 *	@filter_id: filter_is(hardware_id) of filter to be deleted
 *
 * This function वापसs zero in हाल of success, negative number inहाल of
 * error.
 */
पूर्णांक enic_delfltr(काष्ठा enic *enic, u16 filter_id)
अणु
	पूर्णांक ret;

	spin_lock_bh(&enic->devcmd_lock);
	ret = vnic_dev_classअगरier(enic->vdev, CLSF_DEL, &filter_id, शून्य);
	spin_unlock_bh(&enic->devcmd_lock);

	वापस ret;
पूर्ण

/* enic_rfs_flw_tbl_init - initialize enic->rfs_h members
 *	@enic: enic data
 */
व्योम enic_rfs_flw_tbl_init(काष्ठा enic *enic)
अणु
	पूर्णांक i;

	spin_lock_init(&enic->rfs_h.lock);
	क्रम (i = 0; i <= ENIC_RFS_FLW_MASK; i++)
		INIT_HLIST_HEAD(&enic->rfs_h.ht_head[i]);
	enic->rfs_h.max = enic->config.num_arfs;
	enic->rfs_h.मुक्त = enic->rfs_h.max;
	enic->rfs_h.toclean = 0;
पूर्ण

व्योम enic_rfs_flw_tbl_मुक्त(काष्ठा enic *enic)
अणु
	पूर्णांक i;

	enic_rfs_समयr_stop(enic);
	spin_lock_bh(&enic->rfs_h.lock);
	क्रम (i = 0; i < (1 << ENIC_RFS_FLW_BITSHIFT); i++) अणु
		काष्ठा hlist_head *hhead;
		काष्ठा hlist_node *पंचांगp;
		काष्ठा enic_rfs_fltr_node *n;

		hhead = &enic->rfs_h.ht_head[i];
		hlist_क्रम_each_entry_safe(n, पंचांगp, hhead, node) अणु
			enic_delfltr(enic, n->fltr_id);
			hlist_del(&n->node);
			kमुक्त(n);
			enic->rfs_h.मुक्त++;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&enic->rfs_h.lock);
पूर्ण

काष्ठा enic_rfs_fltr_node *htbl_fltr_search(काष्ठा enic *enic, u16 fltr_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < (1 << ENIC_RFS_FLW_BITSHIFT); i++) अणु
		काष्ठा hlist_head *hhead;
		काष्ठा hlist_node *पंचांगp;
		काष्ठा enic_rfs_fltr_node *n;

		hhead = &enic->rfs_h.ht_head[i];
		hlist_क्रम_each_entry_safe(n, पंचांगp, hhead, node)
			अगर (n->fltr_id == fltr_id)
				वापस n;
	पूर्ण

	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
व्योम enic_flow_may_expire(काष्ठा समयr_list *t)
अणु
	काष्ठा enic *enic = from_समयr(enic, t, rfs_h.rfs_may_expire);
	bool res;
	पूर्णांक j;

	spin_lock_bh(&enic->rfs_h.lock);
	क्रम (j = 0; j < ENIC_CLSF_EXPIRE_COUNT; j++) अणु
		काष्ठा hlist_head *hhead;
		काष्ठा hlist_node *पंचांगp;
		काष्ठा enic_rfs_fltr_node *n;

		hhead = &enic->rfs_h.ht_head[enic->rfs_h.toclean++];
		hlist_क्रम_each_entry_safe(n, पंचांगp, hhead, node) अणु
			res = rps_may_expire_flow(enic->netdev, n->rq_id,
						  n->flow_id, n->fltr_id);
			अगर (res) अणु
				res = enic_delfltr(enic, n->fltr_id);
				अगर (unlikely(res))
					जारी;
				hlist_del(&n->node);
				kमुक्त(n);
				enic->rfs_h.मुक्त++;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_bh(&enic->rfs_h.lock);
	mod_समयr(&enic->rfs_h.rfs_may_expire, jअगरfies + HZ/4);
पूर्ण

अटल काष्ठा enic_rfs_fltr_node *htbl_key_search(काष्ठा hlist_head *h,
						  काष्ठा flow_keys *k)
अणु
	काष्ठा enic_rfs_fltr_node *tpos;

	hlist_क्रम_each_entry(tpos, h, node)
		अगर (tpos->keys.addrs.v4addrs.src == k->addrs.v4addrs.src &&
		    tpos->keys.addrs.v4addrs.dst == k->addrs.v4addrs.dst &&
		    tpos->keys.ports.ports == k->ports.ports &&
		    tpos->keys.basic.ip_proto == k->basic.ip_proto &&
		    tpos->keys.basic.n_proto == k->basic.n_proto)
			वापस tpos;
	वापस शून्य;
पूर्ण

पूर्णांक enic_rx_flow_steer(काष्ठा net_device *dev, स्थिर काष्ठा sk_buff *skb,
		       u16 rxq_index, u32 flow_id)
अणु
	काष्ठा flow_keys keys;
	काष्ठा enic_rfs_fltr_node *n;
	काष्ठा enic *enic;
	u16 tbl_idx;
	पूर्णांक res, i;

	enic = netdev_priv(dev);
	res = skb_flow_dissect_flow_keys(skb, &keys, 0);
	अगर (!res || keys.basic.n_proto != htons(ETH_P_IP) ||
	    (keys.basic.ip_proto != IPPROTO_TCP &&
	     keys.basic.ip_proto != IPPROTO_UDP))
		वापस -EPROTONOSUPPORT;

	tbl_idx = skb_get_hash_raw(skb) & ENIC_RFS_FLW_MASK;
	spin_lock_bh(&enic->rfs_h.lock);
	n = htbl_key_search(&enic->rfs_h.ht_head[tbl_idx], &keys);

	अगर (n) अणु /* entry alपढ़ोy present  */
		अगर (rxq_index == n->rq_id) अणु
			res = -EEXIST;
			जाओ ret_unlock;
		पूर्ण

		/* desired rq changed क्रम the flow, we need to delete
		 * old fltr and add new one
		 *
		 * The moment we delete the fltr, the upcoming pkts
		 * are put it शेष rq based on rss. When we add
		 * new filter, upcoming pkts are put in desired queue.
		 * This could cause ooo pkts.
		 *
		 * Lets 1st try adding new fltr and then del old one.
		 */
		i = --enic->rfs_h.मुक्त;
		/* clsf tbl is full, we have to del old fltr first*/
		अगर (unlikely(i < 0)) अणु
			enic->rfs_h.मुक्त++;
			res = enic_delfltr(enic, n->fltr_id);
			अगर (unlikely(res < 0))
				जाओ ret_unlock;
			res = enic_addfltr_5t(enic, &keys, rxq_index);
			अगर (res < 0) अणु
				hlist_del(&n->node);
				enic->rfs_h.मुक्त++;
				जाओ ret_unlock;
			पूर्ण
		/* add new fltr 1st then del old fltr */
		पूर्ण अन्यथा अणु
			पूर्णांक ret;

			res = enic_addfltr_5t(enic, &keys, rxq_index);
			अगर (res < 0) अणु
				enic->rfs_h.मुक्त++;
				जाओ ret_unlock;
			पूर्ण
			ret = enic_delfltr(enic, n->fltr_id);
			/* deleting old fltr failed. Add old fltr to list.
			 * enic_flow_may_expire() will try to delete it later.
			 */
			अगर (unlikely(ret < 0)) अणु
				काष्ठा enic_rfs_fltr_node *d;
				काष्ठा hlist_head *head;

				head = &enic->rfs_h.ht_head[tbl_idx];
				d = kदो_स्मृति(माप(*d), GFP_ATOMIC);
				अगर (d) अणु
					d->fltr_id = n->fltr_id;
					INIT_HLIST_NODE(&d->node);
					hlist_add_head(&d->node, head);
				पूर्ण
			पूर्ण अन्यथा अणु
				enic->rfs_h.मुक्त++;
			पूर्ण
		पूर्ण
		n->rq_id = rxq_index;
		n->fltr_id = res;
		n->flow_id = flow_id;
	/* entry not present */
	पूर्ण अन्यथा अणु
		i = --enic->rfs_h.मुक्त;
		अगर (i <= 0) अणु
			enic->rfs_h.मुक्त++;
			res = -EBUSY;
			जाओ ret_unlock;
		पूर्ण

		n = kदो_स्मृति(माप(*n), GFP_ATOMIC);
		अगर (!n) अणु
			res = -ENOMEM;
			enic->rfs_h.मुक्त++;
			जाओ ret_unlock;
		पूर्ण

		res = enic_addfltr_5t(enic, &keys, rxq_index);
		अगर (res < 0) अणु
			kमुक्त(n);
			enic->rfs_h.मुक्त++;
			जाओ ret_unlock;
		पूर्ण
		n->rq_id = rxq_index;
		n->fltr_id = res;
		n->flow_id = flow_id;
		n->keys = keys;
		INIT_HLIST_NODE(&n->node);
		hlist_add_head(&n->node, &enic->rfs_h.ht_head[tbl_idx]);
	पूर्ण

ret_unlock:
	spin_unlock_bh(&enic->rfs_h.lock);
	वापस res;
पूर्ण

#पूर्ण_अगर /* CONFIG_RFS_ACCEL */
