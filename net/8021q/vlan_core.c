<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/netpoll.h>
#समावेश <linux/export.h>
#समावेश <net/gro.h>
#समावेश "vlan.h"

bool vlan_करो_receive(काष्ठा sk_buff **skbp)
अणु
	काष्ठा sk_buff *skb = *skbp;
	__be16 vlan_proto = skb->vlan_proto;
	u16 vlan_id = skb_vlan_tag_get_id(skb);
	काष्ठा net_device *vlan_dev;
	काष्ठा vlan_pcpu_stats *rx_stats;

	vlan_dev = vlan_find_dev(skb->dev, vlan_proto, vlan_id);
	अगर (!vlan_dev)
		वापस false;

	skb = *skbp = skb_share_check(skb, GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस false;

	अगर (unlikely(!(vlan_dev->flags & IFF_UP))) अणु
		kमुक्त_skb(skb);
		*skbp = शून्य;
		वापस false;
	पूर्ण

	skb->dev = vlan_dev;
	अगर (unlikely(skb->pkt_type == PACKET_OTHERHOST)) अणु
		/* Our lower layer thinks this is not local, let's make sure.
		 * This allows the VLAN to have a dअगरferent MAC than the
		 * underlying device, and still route correctly. */
		अगर (ether_addr_equal_64bits(eth_hdr(skb)->h_dest, vlan_dev->dev_addr))
			skb->pkt_type = PACKET_HOST;
	पूर्ण

	अगर (!(vlan_dev_priv(vlan_dev)->flags & VLAN_FLAG_REORDER_HDR) &&
	    !netअगर_is_macvlan_port(vlan_dev) &&
	    !netअगर_is_bridge_port(vlan_dev)) अणु
		अचिन्हित पूर्णांक offset = skb->data - skb_mac_header(skb);

		/*
		 * vlan_insert_tag expect skb->data poपूर्णांकing to mac header.
		 * So change skb->data beक्रमe calling it and change back to
		 * original position later
		 */
		skb_push(skb, offset);
		skb = *skbp = vlan_insert_inner_tag(skb, skb->vlan_proto,
						    skb->vlan_tci, skb->mac_len);
		अगर (!skb)
			वापस false;
		skb_pull(skb, offset + VLAN_HLEN);
		skb_reset_mac_len(skb);
	पूर्ण

	skb->priority = vlan_get_ingress_priority(vlan_dev, skb->vlan_tci);
	__vlan_hwaccel_clear_tag(skb);

	rx_stats = this_cpu_ptr(vlan_dev_priv(vlan_dev)->vlan_pcpu_stats);

	u64_stats_update_begin(&rx_stats->syncp);
	rx_stats->rx_packets++;
	rx_stats->rx_bytes += skb->len;
	अगर (skb->pkt_type == PACKET_MULTICAST)
		rx_stats->rx_multicast++;
	u64_stats_update_end(&rx_stats->syncp);

	वापस true;
पूर्ण

/* Must be invoked with rcu_पढ़ो_lock. */
काष्ठा net_device *__vlan_find_dev_deep_rcu(काष्ठा net_device *dev,
					__be16 vlan_proto, u16 vlan_id)
अणु
	काष्ठा vlan_info *vlan_info = rcu_dereference(dev->vlan_info);

	अगर (vlan_info) अणु
		वापस vlan_group_get_device(&vlan_info->grp,
					     vlan_proto, vlan_id);
	पूर्ण अन्यथा अणु
		/*
		 * Lower devices of master uppers (bonding, team) करो not have
		 * grp asचिन्हित to themselves. Grp is asचिन्हित to upper device
		 * instead.
		 */
		काष्ठा net_device *upper_dev;

		upper_dev = netdev_master_upper_dev_get_rcu(dev);
		अगर (upper_dev)
			वापस __vlan_find_dev_deep_rcu(upper_dev,
						    vlan_proto, vlan_id);
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(__vlan_find_dev_deep_rcu);

काष्ठा net_device *vlan_dev_real_dev(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा net_device *ret = vlan_dev_priv(dev)->real_dev;

	जबतक (is_vlan_dev(ret))
		ret = vlan_dev_priv(ret)->real_dev;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(vlan_dev_real_dev);

u16 vlan_dev_vlan_id(स्थिर काष्ठा net_device *dev)
अणु
	वापस vlan_dev_priv(dev)->vlan_id;
पूर्ण
EXPORT_SYMBOL(vlan_dev_vlan_id);

__be16 vlan_dev_vlan_proto(स्थिर काष्ठा net_device *dev)
अणु
	वापस vlan_dev_priv(dev)->vlan_proto;
पूर्ण
EXPORT_SYMBOL(vlan_dev_vlan_proto);

/*
 * vlan info and vid list
 */

अटल व्योम vlan_group_मुक्त(काष्ठा vlan_group *grp)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < VLAN_PROTO_NUM; i++)
		क्रम (j = 0; j < VLAN_GROUP_ARRAY_SPLIT_PARTS; j++)
			kमुक्त(grp->vlan_devices_arrays[i][j]);
पूर्ण

अटल व्योम vlan_info_मुक्त(काष्ठा vlan_info *vlan_info)
अणु
	vlan_group_मुक्त(&vlan_info->grp);
	kमुक्त(vlan_info);
पूर्ण

अटल व्योम vlan_info_rcu_मुक्त(काष्ठा rcu_head *rcu)
अणु
	vlan_info_मुक्त(container_of(rcu, काष्ठा vlan_info, rcu));
पूर्ण

अटल काष्ठा vlan_info *vlan_info_alloc(काष्ठा net_device *dev)
अणु
	काष्ठा vlan_info *vlan_info;

	vlan_info = kzalloc(माप(काष्ठा vlan_info), GFP_KERNEL);
	अगर (!vlan_info)
		वापस शून्य;

	vlan_info->real_dev = dev;
	INIT_LIST_HEAD(&vlan_info->vid_list);
	वापस vlan_info;
पूर्ण

काष्ठा vlan_vid_info अणु
	काष्ठा list_head list;
	__be16 proto;
	u16 vid;
	पूर्णांक refcount;
पूर्ण;

अटल bool vlan_hw_filter_capable(स्थिर काष्ठा net_device *dev, __be16 proto)
अणु
	अगर (proto == htons(ETH_P_8021Q) &&
	    dev->features & NETIF_F_HW_VLAN_CTAG_FILTER)
		वापस true;
	अगर (proto == htons(ETH_P_8021AD) &&
	    dev->features & NETIF_F_HW_VLAN_STAG_FILTER)
		वापस true;
	वापस false;
पूर्ण

अटल काष्ठा vlan_vid_info *vlan_vid_info_get(काष्ठा vlan_info *vlan_info,
					       __be16 proto, u16 vid)
अणु
	काष्ठा vlan_vid_info *vid_info;

	list_क्रम_each_entry(vid_info, &vlan_info->vid_list, list) अणु
		अगर (vid_info->proto == proto && vid_info->vid == vid)
			वापस vid_info;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा vlan_vid_info *vlan_vid_info_alloc(__be16 proto, u16 vid)
अणु
	काष्ठा vlan_vid_info *vid_info;

	vid_info = kzalloc(माप(काष्ठा vlan_vid_info), GFP_KERNEL);
	अगर (!vid_info)
		वापस शून्य;
	vid_info->proto = proto;
	vid_info->vid = vid;

	वापस vid_info;
पूर्ण

अटल पूर्णांक vlan_add_rx_filter_info(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	अगर (!vlan_hw_filter_capable(dev, proto))
		वापस 0;

	अगर (netअगर_device_present(dev))
		वापस dev->netdev_ops->nकरो_vlan_rx_add_vid(dev, proto, vid);
	अन्यथा
		वापस -ENODEV;
पूर्ण

अटल पूर्णांक vlan_समाप्त_rx_filter_info(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	अगर (!vlan_hw_filter_capable(dev, proto))
		वापस 0;

	अगर (netअगर_device_present(dev))
		वापस dev->netdev_ops->nकरो_vlan_rx_समाप्त_vid(dev, proto, vid);
	अन्यथा
		वापस -ENODEV;
पूर्ण

पूर्णांक vlan_क्रम_each(काष्ठा net_device *dev,
		  पूर्णांक (*action)(काष्ठा net_device *dev, पूर्णांक vid, व्योम *arg),
		  व्योम *arg)
अणु
	काष्ठा vlan_vid_info *vid_info;
	काष्ठा vlan_info *vlan_info;
	काष्ठा net_device *vdev;
	पूर्णांक ret;

	ASSERT_RTNL();

	vlan_info = rtnl_dereference(dev->vlan_info);
	अगर (!vlan_info)
		वापस 0;

	list_क्रम_each_entry(vid_info, &vlan_info->vid_list, list) अणु
		vdev = vlan_group_get_device(&vlan_info->grp, vid_info->proto,
					     vid_info->vid);
		ret = action(vdev, vid_info->vid, arg);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vlan_क्रम_each);

पूर्णांक vlan_filter_push_vids(काष्ठा vlan_info *vlan_info, __be16 proto)
अणु
	काष्ठा net_device *real_dev = vlan_info->real_dev;
	काष्ठा vlan_vid_info *vlan_vid_info;
	पूर्णांक err;

	list_क्रम_each_entry(vlan_vid_info, &vlan_info->vid_list, list) अणु
		अगर (vlan_vid_info->proto == proto) अणु
			err = vlan_add_rx_filter_info(real_dev, proto,
						      vlan_vid_info->vid);
			अगर (err)
				जाओ unwind;
		पूर्ण
	पूर्ण

	वापस 0;

unwind:
	list_क्रम_each_entry_जारी_reverse(vlan_vid_info,
					     &vlan_info->vid_list, list) अणु
		अगर (vlan_vid_info->proto == proto)
			vlan_समाप्त_rx_filter_info(real_dev, proto,
						 vlan_vid_info->vid);
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(vlan_filter_push_vids);

व्योम vlan_filter_drop_vids(काष्ठा vlan_info *vlan_info, __be16 proto)
अणु
	काष्ठा vlan_vid_info *vlan_vid_info;

	list_क्रम_each_entry(vlan_vid_info, &vlan_info->vid_list, list)
		अगर (vlan_vid_info->proto == proto)
			vlan_समाप्त_rx_filter_info(vlan_info->real_dev,
						 vlan_vid_info->proto,
						 vlan_vid_info->vid);
पूर्ण
EXPORT_SYMBOL(vlan_filter_drop_vids);

अटल पूर्णांक __vlan_vid_add(काष्ठा vlan_info *vlan_info, __be16 proto, u16 vid,
			  काष्ठा vlan_vid_info **pvid_info)
अणु
	काष्ठा net_device *dev = vlan_info->real_dev;
	काष्ठा vlan_vid_info *vid_info;
	पूर्णांक err;

	vid_info = vlan_vid_info_alloc(proto, vid);
	अगर (!vid_info)
		वापस -ENOMEM;

	err = vlan_add_rx_filter_info(dev, proto, vid);
	अगर (err) अणु
		kमुक्त(vid_info);
		वापस err;
	पूर्ण

	list_add(&vid_info->list, &vlan_info->vid_list);
	vlan_info->nr_vids++;
	*pvid_info = vid_info;
	वापस 0;
पूर्ण

पूर्णांक vlan_vid_add(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा vlan_info *vlan_info;
	काष्ठा vlan_vid_info *vid_info;
	bool vlan_info_created = false;
	पूर्णांक err;

	ASSERT_RTNL();

	vlan_info = rtnl_dereference(dev->vlan_info);
	अगर (!vlan_info) अणु
		vlan_info = vlan_info_alloc(dev);
		अगर (!vlan_info)
			वापस -ENOMEM;
		vlan_info_created = true;
	पूर्ण
	vid_info = vlan_vid_info_get(vlan_info, proto, vid);
	अगर (!vid_info) अणु
		err = __vlan_vid_add(vlan_info, proto, vid, &vid_info);
		अगर (err)
			जाओ out_मुक्त_vlan_info;
	पूर्ण
	vid_info->refcount++;

	अगर (vlan_info_created)
		rcu_assign_poपूर्णांकer(dev->vlan_info, vlan_info);

	वापस 0;

out_मुक्त_vlan_info:
	अगर (vlan_info_created)
		kमुक्त(vlan_info);
	वापस err;
पूर्ण
EXPORT_SYMBOL(vlan_vid_add);

अटल व्योम __vlan_vid_del(काष्ठा vlan_info *vlan_info,
			   काष्ठा vlan_vid_info *vid_info)
अणु
	काष्ठा net_device *dev = vlan_info->real_dev;
	__be16 proto = vid_info->proto;
	u16 vid = vid_info->vid;
	पूर्णांक err;

	err = vlan_समाप्त_rx_filter_info(dev, proto, vid);
	अगर (err && dev->reg_state != NETREG_UNREGISTERING)
		netdev_warn(dev, "failed to kill vid %04x/%d\n", proto, vid);

	list_del(&vid_info->list);
	kमुक्त(vid_info);
	vlan_info->nr_vids--;
पूर्ण

व्योम vlan_vid_del(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा vlan_info *vlan_info;
	काष्ठा vlan_vid_info *vid_info;

	ASSERT_RTNL();

	vlan_info = rtnl_dereference(dev->vlan_info);
	अगर (!vlan_info)
		वापस;

	vid_info = vlan_vid_info_get(vlan_info, proto, vid);
	अगर (!vid_info)
		वापस;
	vid_info->refcount--;
	अगर (vid_info->refcount == 0) अणु
		__vlan_vid_del(vlan_info, vid_info);
		अगर (vlan_info->nr_vids == 0) अणु
			RCU_INIT_POINTER(dev->vlan_info, शून्य);
			call_rcu(&vlan_info->rcu, vlan_info_rcu_मुक्त);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(vlan_vid_del);

पूर्णांक vlan_vids_add_by_dev(काष्ठा net_device *dev,
			 स्थिर काष्ठा net_device *by_dev)
अणु
	काष्ठा vlan_vid_info *vid_info;
	काष्ठा vlan_info *vlan_info;
	पूर्णांक err;

	ASSERT_RTNL();

	vlan_info = rtnl_dereference(by_dev->vlan_info);
	अगर (!vlan_info)
		वापस 0;

	list_क्रम_each_entry(vid_info, &vlan_info->vid_list, list) अणु
		err = vlan_vid_add(dev, vid_info->proto, vid_info->vid);
		अगर (err)
			जाओ unwind;
	पूर्ण
	वापस 0;

unwind:
	list_क्रम_each_entry_जारी_reverse(vid_info,
					     &vlan_info->vid_list,
					     list) अणु
		vlan_vid_del(dev, vid_info->proto, vid_info->vid);
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(vlan_vids_add_by_dev);

व्योम vlan_vids_del_by_dev(काष्ठा net_device *dev,
			  स्थिर काष्ठा net_device *by_dev)
अणु
	काष्ठा vlan_vid_info *vid_info;
	काष्ठा vlan_info *vlan_info;

	ASSERT_RTNL();

	vlan_info = rtnl_dereference(by_dev->vlan_info);
	अगर (!vlan_info)
		वापस;

	list_क्रम_each_entry(vid_info, &vlan_info->vid_list, list)
		vlan_vid_del(dev, vid_info->proto, vid_info->vid);
पूर्ण
EXPORT_SYMBOL(vlan_vids_del_by_dev);

bool vlan_uses_dev(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा vlan_info *vlan_info;

	ASSERT_RTNL();

	vlan_info = rtnl_dereference(dev->vlan_info);
	अगर (!vlan_info)
		वापस false;
	वापस vlan_info->grp.nr_vlan_devs ? true : false;
पूर्ण
EXPORT_SYMBOL(vlan_uses_dev);

अटल काष्ठा sk_buff *vlan_gro_receive(काष्ठा list_head *head,
					काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा packet_offload *ptype;
	अचिन्हित पूर्णांक hlen, off_vlan;
	काष्ठा sk_buff *pp = शून्य;
	काष्ठा vlan_hdr *vhdr;
	काष्ठा sk_buff *p;
	__be16 type;
	पूर्णांक flush = 1;

	off_vlan = skb_gro_offset(skb);
	hlen = off_vlan + माप(*vhdr);
	vhdr = skb_gro_header_fast(skb, off_vlan);
	अगर (skb_gro_header_hard(skb, hlen)) अणु
		vhdr = skb_gro_header_slow(skb, hlen, off_vlan);
		अगर (unlikely(!vhdr))
			जाओ out;
	पूर्ण

	type = vhdr->h_vlan_encapsulated_proto;

	rcu_पढ़ो_lock();
	ptype = gro_find_receive_by_type(type);
	अगर (!ptype)
		जाओ out_unlock;

	flush = 0;

	list_क्रम_each_entry(p, head, list) अणु
		काष्ठा vlan_hdr *vhdr2;

		अगर (!NAPI_GRO_CB(p)->same_flow)
			जारी;

		vhdr2 = (काष्ठा vlan_hdr *)(p->data + off_vlan);
		अगर (compare_vlan_header(vhdr, vhdr2))
			NAPI_GRO_CB(p)->same_flow = 0;
	पूर्ण

	skb_gro_pull(skb, माप(*vhdr));
	skb_gro_postpull_rcsum(skb, vhdr, माप(*vhdr));

	pp = indirect_call_gro_receive_inet(ptype->callbacks.gro_receive,
					    ipv6_gro_receive, inet_gro_receive,
					    head, skb);

out_unlock:
	rcu_पढ़ो_unlock();
out:
	skb_gro_flush_final(skb, pp, flush);

	वापस pp;
पूर्ण

अटल पूर्णांक vlan_gro_complete(काष्ठा sk_buff *skb, पूर्णांक nhoff)
अणु
	काष्ठा vlan_hdr *vhdr = (काष्ठा vlan_hdr *)(skb->data + nhoff);
	__be16 type = vhdr->h_vlan_encapsulated_proto;
	काष्ठा packet_offload *ptype;
	पूर्णांक err = -ENOENT;

	rcu_पढ़ो_lock();
	ptype = gro_find_complete_by_type(type);
	अगर (ptype)
		err = INसूचीECT_CALL_INET(ptype->callbacks.gro_complete,
					 ipv6_gro_complete, inet_gro_complete,
					 skb, nhoff + माप(*vhdr));

	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल काष्ठा packet_offload vlan_packet_offloads[] __पढ़ो_mostly = अणु
	अणु
		.type = cpu_to_be16(ETH_P_8021Q),
		.priority = 10,
		.callbacks = अणु
			.gro_receive = vlan_gro_receive,
			.gro_complete = vlan_gro_complete,
		पूर्ण,
	पूर्ण,
	अणु
		.type = cpu_to_be16(ETH_P_8021AD),
		.priority = 10,
		.callbacks = अणु
			.gro_receive = vlan_gro_receive,
			.gro_complete = vlan_gro_complete,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init vlan_offload_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vlan_packet_offloads); i++)
		dev_add_offload(&vlan_packet_offloads[i]);

	वापस 0;
पूर्ण

fs_initcall(vlan_offload_init);
