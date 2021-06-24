<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Bridge netlink control पूर्णांकerface
 *
 *	Authors:
 *	Stephen Hemminger		<shemminger@osdl.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/अगर_bridge.h>

#समावेश "br_private.h"
#समावेश "br_private_stp.h"
#समावेश "br_private_cfm.h"
#समावेश "br_private_tunnel.h"
#समावेश "br_private_mcast_eht.h"

अटल पूर्णांक __get_num_vlan_infos(काष्ठा net_bridge_vlan_group *vg,
				u32 filter_mask)
अणु
	काष्ठा net_bridge_vlan *v;
	u16 vid_range_start = 0, vid_range_end = 0, vid_range_flags = 0;
	u16 flags, pvid;
	पूर्णांक num_vlans = 0;

	अगर (!(filter_mask & RTEXT_FILTER_BRVLAN_COMPRESSED))
		वापस 0;

	pvid = br_get_pvid(vg);
	/* Count number of vlan infos */
	list_क्रम_each_entry_rcu(v, &vg->vlan_list, vlist) अणु
		flags = 0;
		/* only a context, bridge vlan not activated */
		अगर (!br_vlan_should_use(v))
			जारी;
		अगर (v->vid == pvid)
			flags |= BRIDGE_VLAN_INFO_PVID;

		अगर (v->flags & BRIDGE_VLAN_INFO_UNTAGGED)
			flags |= BRIDGE_VLAN_INFO_UNTAGGED;

		अगर (vid_range_start == 0) अणु
			जाओ initvars;
		पूर्ण अन्यथा अगर ((v->vid - vid_range_end) == 1 &&
			flags == vid_range_flags) अणु
			vid_range_end = v->vid;
			जारी;
		पूर्ण अन्यथा अणु
			अगर ((vid_range_end - vid_range_start) > 0)
				num_vlans += 2;
			अन्यथा
				num_vlans += 1;
		पूर्ण
initvars:
		vid_range_start = v->vid;
		vid_range_end = v->vid;
		vid_range_flags = flags;
	पूर्ण

	अगर (vid_range_start != 0) अणु
		अगर ((vid_range_end - vid_range_start) > 0)
			num_vlans += 2;
		अन्यथा
			num_vlans += 1;
	पूर्ण

	वापस num_vlans;
पूर्ण

अटल पूर्णांक br_get_num_vlan_infos(काष्ठा net_bridge_vlan_group *vg,
				 u32 filter_mask)
अणु
	पूर्णांक num_vlans;

	अगर (!vg)
		वापस 0;

	अगर (filter_mask & RTEXT_FILTER_BRVLAN)
		वापस vg->num_vlans;

	rcu_पढ़ो_lock();
	num_vlans = __get_num_vlan_infos(vg, filter_mask);
	rcu_पढ़ो_unlock();

	वापस num_vlans;
पूर्ण

अटल माप_प्रकार br_get_link_af_size_filtered(स्थिर काष्ठा net_device *dev,
					   u32 filter_mask)
अणु
	काष्ठा net_bridge_vlan_group *vg = शून्य;
	काष्ठा net_bridge_port *p = शून्य;
	काष्ठा net_bridge *br = शून्य;
	u32 num_cfm_peer_mep_infos;
	u32 num_cfm_mep_infos;
	माप_प्रकार vinfo_sz = 0;
	पूर्णांक num_vlan_infos;

	rcu_पढ़ो_lock();
	अगर (netअगर_is_bridge_port(dev)) अणु
		p = br_port_get_check_rcu(dev);
		अगर (p)
			vg = nbp_vlan_group_rcu(p);
	पूर्ण अन्यथा अगर (dev->priv_flags & IFF_EBRIDGE) अणु
		br = netdev_priv(dev);
		vg = br_vlan_group_rcu(br);
	पूर्ण
	num_vlan_infos = br_get_num_vlan_infos(vg, filter_mask);
	rcu_पढ़ो_unlock();

	अगर (p && (p->flags & BR_VLAN_TUNNEL))
		vinfo_sz += br_get_vlan_tunnel_info_size(vg);

	/* Each VLAN is वापसed in bridge_vlan_info aदीर्घ with flags */
	vinfo_sz += num_vlan_infos * nla_total_size(माप(काष्ठा bridge_vlan_info));

	अगर (!(filter_mask & RTEXT_FILTER_CFM_STATUS))
		वापस vinfo_sz;

	अगर (!br)
		वापस vinfo_sz;

	/* CFM status info must be added */
	br_cfm_mep_count(br, &num_cfm_mep_infos);
	br_cfm_peer_mep_count(br, &num_cfm_peer_mep_infos);

	vinfo_sz += nla_total_size(0);	/* IFLA_BRIDGE_CFM */
	/* For each status काष्ठा the MEP instance (u32) is added */
	/* MEP instance (u32) + br_cfm_mep_status */
	vinfo_sz += num_cfm_mep_infos *
		     /*IFLA_BRIDGE_CFM_MEP_STATUS_INSTANCE */
		    (nla_total_size(माप(u32))
		     /* IFLA_BRIDGE_CFM_MEP_STATUS_OPCODE_UNEXP_SEEN */
		     + nla_total_size(माप(u32))
		     /* IFLA_BRIDGE_CFM_MEP_STATUS_VERSION_UNEXP_SEEN */
		     + nla_total_size(माप(u32))
		     /* IFLA_BRIDGE_CFM_MEP_STATUS_RX_LEVEL_LOW_SEEN */
		     + nla_total_size(माप(u32)));
	/* MEP instance (u32) + br_cfm_cc_peer_status */
	vinfo_sz += num_cfm_peer_mep_infos *
		     /* IFLA_BRIDGE_CFM_CC_PEER_STATUS_INSTANCE */
		    (nla_total_size(माप(u32))
		     /* IFLA_BRIDGE_CFM_CC_PEER_STATUS_PEER_MEPID */
		     + nla_total_size(माप(u32))
		     /* IFLA_BRIDGE_CFM_CC_PEER_STATUS_CCM_DEFECT */
		     + nla_total_size(माप(u32))
		     /* IFLA_BRIDGE_CFM_CC_PEER_STATUS_RDI */
		     + nla_total_size(माप(u32))
		     /* IFLA_BRIDGE_CFM_CC_PEER_STATUS_PORT_TLV_VALUE */
		     + nla_total_size(माप(u8))
		     /* IFLA_BRIDGE_CFM_CC_PEER_STATUS_IF_TLV_VALUE */
		     + nla_total_size(माप(u8))
		     /* IFLA_BRIDGE_CFM_CC_PEER_STATUS_SEEN */
		     + nla_total_size(माप(u32))
		     /* IFLA_BRIDGE_CFM_CC_PEER_STATUS_TLV_SEEN */
		     + nla_total_size(माप(u32))
		     /* IFLA_BRIDGE_CFM_CC_PEER_STATUS_SEQ_UNEXP_SEEN */
		     + nla_total_size(माप(u32)));

	वापस vinfo_sz;
पूर्ण

अटल अंतरभूत माप_प्रकार br_port_info_size(व्योम)
अणु
	वापस nla_total_size(1)	/* IFLA_BRPORT_STATE  */
		+ nla_total_size(2)	/* IFLA_BRPORT_PRIORITY */
		+ nla_total_size(4)	/* IFLA_BRPORT_COST */
		+ nla_total_size(1)	/* IFLA_BRPORT_MODE */
		+ nla_total_size(1)	/* IFLA_BRPORT_GUARD */
		+ nla_total_size(1)	/* IFLA_BRPORT_PROTECT */
		+ nla_total_size(1)	/* IFLA_BRPORT_FAST_LEAVE */
		+ nla_total_size(1)	/* IFLA_BRPORT_MCAST_TO_UCAST */
		+ nla_total_size(1)	/* IFLA_BRPORT_LEARNING */
		+ nla_total_size(1)	/* IFLA_BRPORT_UNICAST_FLOOD */
		+ nla_total_size(1)	/* IFLA_BRPORT_MCAST_FLOOD */
		+ nla_total_size(1)	/* IFLA_BRPORT_BCAST_FLOOD */
		+ nla_total_size(1)	/* IFLA_BRPORT_PROXYARP */
		+ nla_total_size(1)	/* IFLA_BRPORT_PROXYARP_WIFI */
		+ nla_total_size(1)	/* IFLA_BRPORT_VLAN_TUNNEL */
		+ nla_total_size(1)	/* IFLA_BRPORT_NEIGH_SUPPRESS */
		+ nla_total_size(1)	/* IFLA_BRPORT_ISOLATED */
		+ nla_total_size(माप(काष्ठा अगरla_bridge_id))	/* IFLA_BRPORT_ROOT_ID */
		+ nla_total_size(माप(काष्ठा अगरla_bridge_id))	/* IFLA_BRPORT_BRIDGE_ID */
		+ nla_total_size(माप(u16))	/* IFLA_BRPORT_DESIGNATED_PORT */
		+ nla_total_size(माप(u16))	/* IFLA_BRPORT_DESIGNATED_COST */
		+ nla_total_size(माप(u16))	/* IFLA_BRPORT_ID */
		+ nla_total_size(माप(u16))	/* IFLA_BRPORT_NO */
		+ nla_total_size(माप(u8))	/* IFLA_BRPORT_TOPOLOGY_CHANGE_ACK */
		+ nla_total_size(माप(u8))	/* IFLA_BRPORT_CONFIG_PENDING */
		+ nla_total_size_64bit(माप(u64)) /* IFLA_BRPORT_MESSAGE_AGE_TIMER */
		+ nla_total_size_64bit(माप(u64)) /* IFLA_BRPORT_FORWARD_DELAY_TIMER */
		+ nla_total_size_64bit(माप(u64)) /* IFLA_BRPORT_HOLD_TIMER */
#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
		+ nla_total_size(माप(u8))	/* IFLA_BRPORT_MULTICAST_ROUTER */
#पूर्ण_अगर
		+ nla_total_size(माप(u16))	/* IFLA_BRPORT_GROUP_FWD_MASK */
		+ nla_total_size(माप(u8))	/* IFLA_BRPORT_MRP_RING_OPEN */
		+ nla_total_size(माप(u8))	/* IFLA_BRPORT_MRP_IN_OPEN */
		+ nla_total_size(माप(u32))	/* IFLA_BRPORT_MCAST_EHT_HOSTS_LIMIT */
		+ nla_total_size(माप(u32))	/* IFLA_BRPORT_MCAST_EHT_HOSTS_CNT */
		+ 0;
पूर्ण

अटल अंतरभूत माप_प्रकार br_nlmsg_size(काष्ठा net_device *dev, u32 filter_mask)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा अगरinfomsg))
		+ nla_total_size(IFNAMSIZ) /* IFLA_IFNAME */
		+ nla_total_size(MAX_ADDR_LEN) /* IFLA_ADDRESS */
		+ nla_total_size(4) /* IFLA_MASTER */
		+ nla_total_size(4) /* IFLA_MTU */
		+ nla_total_size(4) /* IFLA_LINK */
		+ nla_total_size(1) /* IFLA_OPERSTATE */
		+ nla_total_size(br_port_info_size()) /* IFLA_PROTINFO */
		+ nla_total_size(br_get_link_af_size_filtered(dev,
				 filter_mask)) /* IFLA_AF_SPEC */
		+ nla_total_size(4); /* IFLA_BRPORT_BACKUP_PORT */
पूर्ण

अटल पूर्णांक br_port_fill_attrs(काष्ठा sk_buff *skb,
			      स्थिर काष्ठा net_bridge_port *p)
अणु
	u8 mode = !!(p->flags & BR_HAIRPIN_MODE);
	काष्ठा net_bridge_port *backup_p;
	u64 समयrval;

	अगर (nla_put_u8(skb, IFLA_BRPORT_STATE, p->state) ||
	    nla_put_u16(skb, IFLA_BRPORT_PRIORITY, p->priority) ||
	    nla_put_u32(skb, IFLA_BRPORT_COST, p->path_cost) ||
	    nla_put_u8(skb, IFLA_BRPORT_MODE, mode) ||
	    nla_put_u8(skb, IFLA_BRPORT_GUARD, !!(p->flags & BR_BPDU_GUARD)) ||
	    nla_put_u8(skb, IFLA_BRPORT_PROTECT,
		       !!(p->flags & BR_ROOT_BLOCK)) ||
	    nla_put_u8(skb, IFLA_BRPORT_FAST_LEAVE,
		       !!(p->flags & BR_MULTICAST_FAST_LEAVE)) ||
	    nla_put_u8(skb, IFLA_BRPORT_MCAST_TO_UCAST,
		       !!(p->flags & BR_MULTICAST_TO_UNICAST)) ||
	    nla_put_u8(skb, IFLA_BRPORT_LEARNING, !!(p->flags & BR_LEARNING)) ||
	    nla_put_u8(skb, IFLA_BRPORT_UNICAST_FLOOD,
		       !!(p->flags & BR_FLOOD)) ||
	    nla_put_u8(skb, IFLA_BRPORT_MCAST_FLOOD,
		       !!(p->flags & BR_MCAST_FLOOD)) ||
	    nla_put_u8(skb, IFLA_BRPORT_BCAST_FLOOD,
		       !!(p->flags & BR_BCAST_FLOOD)) ||
	    nla_put_u8(skb, IFLA_BRPORT_PROXYARP, !!(p->flags & BR_PROXYARP)) ||
	    nla_put_u8(skb, IFLA_BRPORT_PROXYARP_WIFI,
		       !!(p->flags & BR_PROXYARP_WIFI)) ||
	    nla_put(skb, IFLA_BRPORT_ROOT_ID, माप(काष्ठा अगरla_bridge_id),
		    &p->designated_root) ||
	    nla_put(skb, IFLA_BRPORT_BRIDGE_ID, माप(काष्ठा अगरla_bridge_id),
		    &p->designated_bridge) ||
	    nla_put_u16(skb, IFLA_BRPORT_DESIGNATED_PORT, p->designated_port) ||
	    nla_put_u16(skb, IFLA_BRPORT_DESIGNATED_COST, p->designated_cost) ||
	    nla_put_u16(skb, IFLA_BRPORT_ID, p->port_id) ||
	    nla_put_u16(skb, IFLA_BRPORT_NO, p->port_no) ||
	    nla_put_u8(skb, IFLA_BRPORT_TOPOLOGY_CHANGE_ACK,
		       p->topology_change_ack) ||
	    nla_put_u8(skb, IFLA_BRPORT_CONFIG_PENDING, p->config_pending) ||
	    nla_put_u8(skb, IFLA_BRPORT_VLAN_TUNNEL, !!(p->flags &
							BR_VLAN_TUNNEL)) ||
	    nla_put_u16(skb, IFLA_BRPORT_GROUP_FWD_MASK, p->group_fwd_mask) ||
	    nla_put_u8(skb, IFLA_BRPORT_NEIGH_SUPPRESS,
		       !!(p->flags & BR_NEIGH_SUPPRESS)) ||
	    nla_put_u8(skb, IFLA_BRPORT_MRP_RING_OPEN, !!(p->flags &
							  BR_MRP_LOST_CONT)) ||
	    nla_put_u8(skb, IFLA_BRPORT_MRP_IN_OPEN,
		       !!(p->flags & BR_MRP_LOST_IN_CONT)) ||
	    nla_put_u8(skb, IFLA_BRPORT_ISOLATED, !!(p->flags & BR_ISOLATED)))
		वापस -EMSGSIZE;

	समयrval = br_समयr_value(&p->message_age_समयr);
	अगर (nla_put_u64_64bit(skb, IFLA_BRPORT_MESSAGE_AGE_TIMER, समयrval,
			      IFLA_BRPORT_PAD))
		वापस -EMSGSIZE;
	समयrval = br_समयr_value(&p->क्रमward_delay_समयr);
	अगर (nla_put_u64_64bit(skb, IFLA_BRPORT_FORWARD_DELAY_TIMER, समयrval,
			      IFLA_BRPORT_PAD))
		वापस -EMSGSIZE;
	समयrval = br_समयr_value(&p->hold_समयr);
	अगर (nla_put_u64_64bit(skb, IFLA_BRPORT_HOLD_TIMER, समयrval,
			      IFLA_BRPORT_PAD))
		वापस -EMSGSIZE;

#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
	अगर (nla_put_u8(skb, IFLA_BRPORT_MULTICAST_ROUTER,
		       p->multicast_router) ||
	    nla_put_u32(skb, IFLA_BRPORT_MCAST_EHT_HOSTS_LIMIT,
			p->multicast_eht_hosts_limit) ||
	    nla_put_u32(skb, IFLA_BRPORT_MCAST_EHT_HOSTS_CNT,
			p->multicast_eht_hosts_cnt))
		वापस -EMSGSIZE;
#पूर्ण_अगर

	/* we might be called only with br->lock */
	rcu_पढ़ो_lock();
	backup_p = rcu_dereference(p->backup_port);
	अगर (backup_p)
		nla_put_u32(skb, IFLA_BRPORT_BACKUP_PORT,
			    backup_p->dev->अगरindex);
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक br_fill_अगरvlaninfo_range(काष्ठा sk_buff *skb, u16 vid_start,
				    u16 vid_end, u16 flags)
अणु
	काष्ठा  bridge_vlan_info vinfo;

	अगर ((vid_end - vid_start) > 0) अणु
		/* add range to skb */
		vinfo.vid = vid_start;
		vinfo.flags = flags | BRIDGE_VLAN_INFO_RANGE_BEGIN;
		अगर (nla_put(skb, IFLA_BRIDGE_VLAN_INFO,
			    माप(vinfo), &vinfo))
			जाओ nla_put_failure;

		vinfo.vid = vid_end;
		vinfo.flags = flags | BRIDGE_VLAN_INFO_RANGE_END;
		अगर (nla_put(skb, IFLA_BRIDGE_VLAN_INFO,
			    माप(vinfo), &vinfo))
			जाओ nla_put_failure;
	पूर्ण अन्यथा अणु
		vinfo.vid = vid_start;
		vinfo.flags = flags;
		अगर (nla_put(skb, IFLA_BRIDGE_VLAN_INFO,
			    माप(vinfo), &vinfo))
			जाओ nla_put_failure;
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक br_fill_अगरvlaninfo_compressed(काष्ठा sk_buff *skb,
					 काष्ठा net_bridge_vlan_group *vg)
अणु
	काष्ठा net_bridge_vlan *v;
	u16 vid_range_start = 0, vid_range_end = 0, vid_range_flags = 0;
	u16 flags, pvid;
	पूर्णांक err = 0;

	/* Pack IFLA_BRIDGE_VLAN_INFO's क्रम every vlan
	 * and mark vlan info with begin and end flags
	 * अगर vlaninfo represents a range
	 */
	pvid = br_get_pvid(vg);
	list_क्रम_each_entry_rcu(v, &vg->vlan_list, vlist) अणु
		flags = 0;
		अगर (!br_vlan_should_use(v))
			जारी;
		अगर (v->vid == pvid)
			flags |= BRIDGE_VLAN_INFO_PVID;

		अगर (v->flags & BRIDGE_VLAN_INFO_UNTAGGED)
			flags |= BRIDGE_VLAN_INFO_UNTAGGED;

		अगर (vid_range_start == 0) अणु
			जाओ initvars;
		पूर्ण अन्यथा अगर ((v->vid - vid_range_end) == 1 &&
			flags == vid_range_flags) अणु
			vid_range_end = v->vid;
			जारी;
		पूर्ण अन्यथा अणु
			err = br_fill_अगरvlaninfo_range(skb, vid_range_start,
						       vid_range_end,
						       vid_range_flags);
			अगर (err)
				वापस err;
		पूर्ण

initvars:
		vid_range_start = v->vid;
		vid_range_end = v->vid;
		vid_range_flags = flags;
	पूर्ण

	अगर (vid_range_start != 0) अणु
		/* Call it once more to send any left over vlans */
		err = br_fill_अगरvlaninfo_range(skb, vid_range_start,
					       vid_range_end,
					       vid_range_flags);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक br_fill_अगरvlaninfo(काष्ठा sk_buff *skb,
			      काष्ठा net_bridge_vlan_group *vg)
अणु
	काष्ठा bridge_vlan_info vinfo;
	काष्ठा net_bridge_vlan *v;
	u16 pvid;

	pvid = br_get_pvid(vg);
	list_क्रम_each_entry_rcu(v, &vg->vlan_list, vlist) अणु
		अगर (!br_vlan_should_use(v))
			जारी;

		vinfo.vid = v->vid;
		vinfo.flags = 0;
		अगर (v->vid == pvid)
			vinfo.flags |= BRIDGE_VLAN_INFO_PVID;

		अगर (v->flags & BRIDGE_VLAN_INFO_UNTAGGED)
			vinfo.flags |= BRIDGE_VLAN_INFO_UNTAGGED;

		अगर (nla_put(skb, IFLA_BRIDGE_VLAN_INFO,
			    माप(vinfo), &vinfo))
			जाओ nla_put_failure;
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

/*
 * Create one netlink message क्रम one पूर्णांकerface
 * Contains port and master info as well as carrier and bridge state.
 */
अटल पूर्णांक br_fill_अगरinfo(काष्ठा sk_buff *skb,
			  स्थिर काष्ठा net_bridge_port *port,
			  u32 pid, u32 seq, पूर्णांक event, अचिन्हित पूर्णांक flags,
			  u32 filter_mask, स्थिर काष्ठा net_device *dev,
			  bool getlink)
अणु
	u8 operstate = netअगर_running(dev) ? dev->operstate : IF_OPER_DOWN;
	काष्ठा nlattr *af = शून्य;
	काष्ठा net_bridge *br;
	काष्ठा अगरinfomsg *hdr;
	काष्ठा nlmsghdr *nlh;

	अगर (port)
		br = port->br;
	अन्यथा
		br = netdev_priv(dev);

	br_debug(br, "br_fill_info event %d port %s master %s\n",
		     event, dev->name, br->dev->name);

	nlh = nlmsg_put(skb, pid, seq, event, माप(*hdr), flags);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	hdr = nlmsg_data(nlh);
	hdr->अगरi_family = AF_BRIDGE;
	hdr->__अगरi_pad = 0;
	hdr->अगरi_type = dev->type;
	hdr->अगरi_index = dev->अगरindex;
	hdr->अगरi_flags = dev_get_flags(dev);
	hdr->अगरi_change = 0;

	अगर (nla_put_string(skb, IFLA_IFNAME, dev->name) ||
	    nla_put_u32(skb, IFLA_MASTER, br->dev->अगरindex) ||
	    nla_put_u32(skb, IFLA_MTU, dev->mtu) ||
	    nla_put_u8(skb, IFLA_OPERSTATE, operstate) ||
	    (dev->addr_len &&
	     nla_put(skb, IFLA_ADDRESS, dev->addr_len, dev->dev_addr)) ||
	    (dev->अगरindex != dev_get_अगरlink(dev) &&
	     nla_put_u32(skb, IFLA_LINK, dev_get_अगरlink(dev))))
		जाओ nla_put_failure;

	अगर (event == RTM_NEWLINK && port) अणु
		काष्ठा nlattr *nest;

		nest = nla_nest_start(skb, IFLA_PROTINFO);
		अगर (nest == शून्य || br_port_fill_attrs(skb, port) < 0)
			जाओ nla_put_failure;
		nla_nest_end(skb, nest);
	पूर्ण

	अगर (filter_mask & (RTEXT_FILTER_BRVLAN |
			   RTEXT_FILTER_BRVLAN_COMPRESSED |
			   RTEXT_FILTER_MRP |
			   RTEXT_FILTER_CFM_CONFIG |
			   RTEXT_FILTER_CFM_STATUS)) अणु
		af = nla_nest_start_noflag(skb, IFLA_AF_SPEC);
		अगर (!af)
			जाओ nla_put_failure;
	पूर्ण

	/* Check अगर  the VID inक्रमmation is requested */
	अगर ((filter_mask & RTEXT_FILTER_BRVLAN) ||
	    (filter_mask & RTEXT_FILTER_BRVLAN_COMPRESSED)) अणु
		काष्ठा net_bridge_vlan_group *vg;
		पूर्णांक err;

		/* RCU needed because of the VLAN locking rules (rcu || rtnl) */
		rcu_पढ़ो_lock();
		अगर (port)
			vg = nbp_vlan_group_rcu(port);
		अन्यथा
			vg = br_vlan_group_rcu(br);

		अगर (!vg || !vg->num_vlans) अणु
			rcu_पढ़ो_unlock();
			जाओ करोne;
		पूर्ण
		अगर (filter_mask & RTEXT_FILTER_BRVLAN_COMPRESSED)
			err = br_fill_अगरvlaninfo_compressed(skb, vg);
		अन्यथा
			err = br_fill_अगरvlaninfo(skb, vg);

		अगर (port && (port->flags & BR_VLAN_TUNNEL))
			err = br_fill_vlan_tunnel_info(skb, vg);
		rcu_पढ़ो_unlock();
		अगर (err)
			जाओ nla_put_failure;
	पूर्ण

	अगर (filter_mask & RTEXT_FILTER_MRP) अणु
		पूर्णांक err;

		अगर (!br_mrp_enabled(br) || port)
			जाओ करोne;

		rcu_पढ़ो_lock();
		err = br_mrp_fill_info(skb, br);
		rcu_पढ़ो_unlock();

		अगर (err)
			जाओ nla_put_failure;
	पूर्ण

	अगर (filter_mask & (RTEXT_FILTER_CFM_CONFIG | RTEXT_FILTER_CFM_STATUS)) अणु
		काष्ठा nlattr *cfm_nest = शून्य;
		पूर्णांक err;

		अगर (!br_cfm_created(br) || port)
			जाओ करोne;

		cfm_nest = nla_nest_start(skb, IFLA_BRIDGE_CFM);
		अगर (!cfm_nest)
			जाओ nla_put_failure;

		अगर (filter_mask & RTEXT_FILTER_CFM_CONFIG) अणु
			rcu_पढ़ो_lock();
			err = br_cfm_config_fill_info(skb, br);
			rcu_पढ़ो_unlock();
			अगर (err)
				जाओ nla_put_failure;
		पूर्ण

		अगर (filter_mask & RTEXT_FILTER_CFM_STATUS) अणु
			rcu_पढ़ो_lock();
			err = br_cfm_status_fill_info(skb, br, getlink);
			rcu_पढ़ो_unlock();
			अगर (err)
				जाओ nla_put_failure;
		पूर्ण

		nla_nest_end(skb, cfm_nest);
	पूर्ण

करोne:
	अगर (af)
		nla_nest_end(skb, af);
	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

व्योम br_info_notअगरy(पूर्णांक event, स्थिर काष्ठा net_bridge *br,
		    स्थिर काष्ठा net_bridge_port *port, u32 filter)
अणु
	काष्ठा net_device *dev;
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;
	काष्ठा net *net;
	u16 port_no = 0;

	अगर (WARN_ON(!port && !br))
		वापस;

	अगर (port) अणु
		dev = port->dev;
		br = port->br;
		port_no = port->port_no;
	पूर्ण अन्यथा अणु
		dev = br->dev;
	पूर्ण

	net = dev_net(dev);
	br_debug(br, "port %u(%s) event %d\n", port_no, dev->name, event);

	skb = nlmsg_new(br_nlmsg_size(dev, filter), GFP_ATOMIC);
	अगर (skb == शून्य)
		जाओ errout;

	err = br_fill_अगरinfo(skb, port, 0, 0, event, 0, filter, dev, false);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in br_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	rtnl_notअगरy(skb, net, 0, RTNLGRP_LINK, शून्य, GFP_ATOMIC);
	वापस;
errout:
	rtnl_set_sk_err(net, RTNLGRP_LINK, err);
पूर्ण

/* Notअगरy listeners of a change in bridge or port inक्रमmation */
व्योम br_अगरinfo_notअगरy(पूर्णांक event, स्थिर काष्ठा net_bridge *br,
		      स्थिर काष्ठा net_bridge_port *port)
अणु
	u32 filter = RTEXT_FILTER_BRVLAN_COMPRESSED;

	वापस br_info_notअगरy(event, br, port, filter);
पूर्ण

/*
 * Dump inक्रमmation about all ports, in response to GETLINK
 */
पूर्णांक br_getlink(काष्ठा sk_buff *skb, u32 pid, u32 seq,
	       काष्ठा net_device *dev, u32 filter_mask, पूर्णांक nlflags)
अणु
	काष्ठा net_bridge_port *port = br_port_get_rtnl(dev);

	अगर (!port && !(filter_mask & RTEXT_FILTER_BRVLAN) &&
	    !(filter_mask & RTEXT_FILTER_BRVLAN_COMPRESSED) &&
	    !(filter_mask & RTEXT_FILTER_MRP) &&
	    !(filter_mask & RTEXT_FILTER_CFM_CONFIG) &&
	    !(filter_mask & RTEXT_FILTER_CFM_STATUS))
		वापस 0;

	वापस br_fill_अगरinfo(skb, port, pid, seq, RTM_NEWLINK, nlflags,
			      filter_mask, dev, true);
पूर्ण

अटल पूर्णांक br_vlan_info(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p,
			पूर्णांक cmd, काष्ठा bridge_vlan_info *vinfo, bool *changed,
			काष्ठा netlink_ext_ack *extack)
अणु
	bool curr_change;
	पूर्णांक err = 0;

	चयन (cmd) अणु
	हाल RTM_SETLINK:
		अगर (p) अणु
			/* अगर the MASTER flag is set this will act on the global
			 * per-VLAN entry as well
			 */
			err = nbp_vlan_add(p, vinfo->vid, vinfo->flags,
					   &curr_change, extack);
		पूर्ण अन्यथा अणु
			vinfo->flags |= BRIDGE_VLAN_INFO_BRENTRY;
			err = br_vlan_add(br, vinfo->vid, vinfo->flags,
					  &curr_change, extack);
		पूर्ण
		अगर (curr_change)
			*changed = true;
		अवरोध;

	हाल RTM_DELLINK:
		अगर (p) अणु
			अगर (!nbp_vlan_delete(p, vinfo->vid))
				*changed = true;

			अगर ((vinfo->flags & BRIDGE_VLAN_INFO_MASTER) &&
			    !br_vlan_delete(p->br, vinfo->vid))
				*changed = true;
		पूर्ण अन्यथा अगर (!br_vlan_delete(br, vinfo->vid)) अणु
			*changed = true;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक br_process_vlan_info(काष्ठा net_bridge *br,
			 काष्ठा net_bridge_port *p, पूर्णांक cmd,
			 काष्ठा bridge_vlan_info *vinfo_curr,
			 काष्ठा bridge_vlan_info **vinfo_last,
			 bool *changed,
			 काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err, rपंचांग_cmd;

	अगर (!br_vlan_valid_id(vinfo_curr->vid, extack))
		वापस -EINVAL;

	/* needed क्रम vlan-only NEWVLAN/DELVLAN notअगरications */
	rपंचांग_cmd = br_afspec_cmd_to_rपंचांग(cmd);

	अगर (vinfo_curr->flags & BRIDGE_VLAN_INFO_RANGE_BEGIN) अणु
		अगर (!br_vlan_valid_range(vinfo_curr, *vinfo_last, extack))
			वापस -EINVAL;
		*vinfo_last = vinfo_curr;
		वापस 0;
	पूर्ण

	अगर (*vinfo_last) अणु
		काष्ठा bridge_vlan_info पंचांगp_vinfo;
		पूर्णांक v, v_change_start = 0;

		अगर (!br_vlan_valid_range(vinfo_curr, *vinfo_last, extack))
			वापस -EINVAL;

		स_नकल(&पंचांगp_vinfo, *vinfo_last,
		       माप(काष्ठा bridge_vlan_info));
		क्रम (v = (*vinfo_last)->vid; v <= vinfo_curr->vid; v++) अणु
			bool curr_change = false;

			पंचांगp_vinfo.vid = v;
			err = br_vlan_info(br, p, cmd, &पंचांगp_vinfo, &curr_change,
					   extack);
			अगर (err)
				अवरोध;
			अगर (curr_change) अणु
				*changed = curr_change;
				अगर (!v_change_start)
					v_change_start = v;
			पूर्ण अन्यथा अणु
				/* nothing to notअगरy yet */
				अगर (!v_change_start)
					जारी;
				br_vlan_notअगरy(br, p, v_change_start,
					       v - 1, rपंचांग_cmd);
				v_change_start = 0;
			पूर्ण
			cond_resched();
		पूर्ण
		/* v_change_start is set only अगर the last/whole range changed */
		अगर (v_change_start)
			br_vlan_notअगरy(br, p, v_change_start,
				       v - 1, rपंचांग_cmd);

		*vinfo_last = शून्य;

		वापस err;
	पूर्ण

	err = br_vlan_info(br, p, cmd, vinfo_curr, changed, extack);
	अगर (*changed)
		br_vlan_notअगरy(br, p, vinfo_curr->vid, 0, rपंचांग_cmd);

	वापस err;
पूर्ण

अटल पूर्णांक br_afspec(काष्ठा net_bridge *br,
		     काष्ठा net_bridge_port *p,
		     काष्ठा nlattr *af_spec,
		     पूर्णांक cmd, bool *changed,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा bridge_vlan_info *vinfo_curr = शून्य;
	काष्ठा bridge_vlan_info *vinfo_last = शून्य;
	काष्ठा nlattr *attr;
	काष्ठा vtunnel_info tinfo_last = अणुपूर्ण;
	काष्ठा vtunnel_info tinfo_curr = अणुपूर्ण;
	पूर्णांक err = 0, rem;

	nla_क्रम_each_nested(attr, af_spec, rem) अणु
		err = 0;
		चयन (nla_type(attr)) अणु
		हाल IFLA_BRIDGE_VLAN_TUNNEL_INFO:
			अगर (!p || !(p->flags & BR_VLAN_TUNNEL))
				वापस -EINVAL;
			err = br_parse_vlan_tunnel_info(attr, &tinfo_curr);
			अगर (err)
				वापस err;
			err = br_process_vlan_tunnel_info(br, p, cmd,
							  &tinfo_curr,
							  &tinfo_last,
							  changed);
			अगर (err)
				वापस err;
			अवरोध;
		हाल IFLA_BRIDGE_VLAN_INFO:
			अगर (nla_len(attr) != माप(काष्ठा bridge_vlan_info))
				वापस -EINVAL;
			vinfo_curr = nla_data(attr);
			err = br_process_vlan_info(br, p, cmd, vinfo_curr,
						   &vinfo_last, changed,
						   extack);
			अगर (err)
				वापस err;
			अवरोध;
		हाल IFLA_BRIDGE_MRP:
			err = br_mrp_parse(br, p, attr, cmd, extack);
			अगर (err)
				वापस err;
			अवरोध;
		हाल IFLA_BRIDGE_CFM:
			err = br_cfm_parse(br, p, attr, cmd, extack);
			अगर (err)
				वापस err;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा nla_policy br_port_policy[IFLA_BRPORT_MAX + 1] = अणु
	[IFLA_BRPORT_STATE]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BRPORT_COST]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRPORT_PRIORITY]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_BRPORT_MODE]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BRPORT_GUARD]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BRPORT_PROTECT]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BRPORT_FAST_LEAVE]= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BRPORT_LEARNING]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BRPORT_UNICAST_FLOOD] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BRPORT_PROXYARP]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BRPORT_PROXYARP_WIFI] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BRPORT_MULTICAST_ROUTER] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BRPORT_MCAST_TO_UCAST] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BRPORT_MCAST_FLOOD] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BRPORT_BCAST_FLOOD] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BRPORT_VLAN_TUNNEL] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BRPORT_GROUP_FWD_MASK] = अणु .type = NLA_U16 पूर्ण,
	[IFLA_BRPORT_NEIGH_SUPPRESS] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BRPORT_ISOLATED]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_BRPORT_BACKUP_PORT] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_BRPORT_MCAST_EHT_HOSTS_LIMIT] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

/* Change the state of the port and notअगरy spanning tree */
अटल पूर्णांक br_set_port_state(काष्ठा net_bridge_port *p, u8 state)
अणु
	अगर (state > BR_STATE_BLOCKING)
		वापस -EINVAL;

	/* अगर kernel STP is running, करोn't allow changes */
	अगर (p->br->stp_enabled == BR_KERNEL_STP)
		वापस -EBUSY;

	/* अगर device is not up, change is not allowed
	 * अगर link is not present, only allowable state is disabled
	 */
	अगर (!netअगर_running(p->dev) ||
	    (!netअगर_oper_up(p->dev) && state != BR_STATE_DISABLED))
		वापस -ENETDOWN;

	br_set_state(p, state);
	br_port_state_selection(p->br);
	वापस 0;
पूर्ण

/* Set/clear or port flags based on attribute */
अटल व्योम br_set_port_flag(काष्ठा net_bridge_port *p, काष्ठा nlattr *tb[],
			     पूर्णांक attrtype, अचिन्हित दीर्घ mask)
अणु
	अगर (!tb[attrtype])
		वापस;

	अगर (nla_get_u8(tb[attrtype]))
		p->flags |= mask;
	अन्यथा
		p->flags &= ~mask;
पूर्ण

/* Process bridge protocol info on port */
अटल पूर्णांक br_setport(काष्ठा net_bridge_port *p, काष्ठा nlattr *tb[],
		      काष्ठा netlink_ext_ack *extack)
अणु
	अचिन्हित दीर्घ old_flags, changed_mask;
	bool br_vlan_tunnel_old;
	पूर्णांक err;

	old_flags = p->flags;
	br_vlan_tunnel_old = (old_flags & BR_VLAN_TUNNEL) ? true : false;

	br_set_port_flag(p, tb, IFLA_BRPORT_MODE, BR_HAIRPIN_MODE);
	br_set_port_flag(p, tb, IFLA_BRPORT_GUARD, BR_BPDU_GUARD);
	br_set_port_flag(p, tb, IFLA_BRPORT_FAST_LEAVE,
			 BR_MULTICAST_FAST_LEAVE);
	br_set_port_flag(p, tb, IFLA_BRPORT_PROTECT, BR_ROOT_BLOCK);
	br_set_port_flag(p, tb, IFLA_BRPORT_LEARNING, BR_LEARNING);
	br_set_port_flag(p, tb, IFLA_BRPORT_UNICAST_FLOOD, BR_FLOOD);
	br_set_port_flag(p, tb, IFLA_BRPORT_MCAST_FLOOD, BR_MCAST_FLOOD);
	br_set_port_flag(p, tb, IFLA_BRPORT_MCAST_TO_UCAST,
			 BR_MULTICAST_TO_UNICAST);
	br_set_port_flag(p, tb, IFLA_BRPORT_BCAST_FLOOD, BR_BCAST_FLOOD);
	br_set_port_flag(p, tb, IFLA_BRPORT_PROXYARP, BR_PROXYARP);
	br_set_port_flag(p, tb, IFLA_BRPORT_PROXYARP_WIFI, BR_PROXYARP_WIFI);
	br_set_port_flag(p, tb, IFLA_BRPORT_VLAN_TUNNEL, BR_VLAN_TUNNEL);
	br_set_port_flag(p, tb, IFLA_BRPORT_NEIGH_SUPPRESS, BR_NEIGH_SUPPRESS);
	br_set_port_flag(p, tb, IFLA_BRPORT_ISOLATED, BR_ISOLATED);

	changed_mask = old_flags ^ p->flags;

	err = br_चयनdev_set_port_flag(p, p->flags, changed_mask, extack);
	अगर (err) अणु
		p->flags = old_flags;
		वापस err;
	पूर्ण

	अगर (br_vlan_tunnel_old && !(p->flags & BR_VLAN_TUNNEL))
		nbp_vlan_tunnel_info_flush(p);

	br_port_flags_change(p, changed_mask);

	अगर (tb[IFLA_BRPORT_COST]) अणु
		err = br_stp_set_path_cost(p, nla_get_u32(tb[IFLA_BRPORT_COST]));
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRPORT_PRIORITY]) अणु
		err = br_stp_set_port_priority(p, nla_get_u16(tb[IFLA_BRPORT_PRIORITY]));
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRPORT_STATE]) अणु
		err = br_set_port_state(p, nla_get_u8(tb[IFLA_BRPORT_STATE]));
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRPORT_FLUSH])
		br_fdb_delete_by_port(p->br, p, 0, 0);

#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
	अगर (tb[IFLA_BRPORT_MULTICAST_ROUTER]) अणु
		u8 mcast_router = nla_get_u8(tb[IFLA_BRPORT_MULTICAST_ROUTER]);

		err = br_multicast_set_port_router(p, mcast_router);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_BRPORT_MCAST_EHT_HOSTS_LIMIT]) अणु
		u32 hlimit;

		hlimit = nla_get_u32(tb[IFLA_BRPORT_MCAST_EHT_HOSTS_LIMIT]);
		err = br_multicast_eht_set_hosts_limit(p, hlimit);
		अगर (err)
			वापस err;
	पूर्ण
#पूर्ण_अगर

	अगर (tb[IFLA_BRPORT_GROUP_FWD_MASK]) अणु
		u16 fwd_mask = nla_get_u16(tb[IFLA_BRPORT_GROUP_FWD_MASK]);

		अगर (fwd_mask & BR_GROUPFWD_MACPAUSE)
			वापस -EINVAL;
		p->group_fwd_mask = fwd_mask;
	पूर्ण

	अगर (tb[IFLA_BRPORT_BACKUP_PORT]) अणु
		काष्ठा net_device *backup_dev = शून्य;
		u32 backup_अगरindex;

		backup_अगरindex = nla_get_u32(tb[IFLA_BRPORT_BACKUP_PORT]);
		अगर (backup_अगरindex) अणु
			backup_dev = __dev_get_by_index(dev_net(p->dev),
							backup_अगरindex);
			अगर (!backup_dev)
				वापस -ENOENT;
		पूर्ण

		err = nbp_backup_change(p, backup_dev);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* Change state and parameters on port. */
पूर्णांक br_setlink(काष्ठा net_device *dev, काष्ठा nlmsghdr *nlh, u16 flags,
	       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_bridge *br = (काष्ठा net_bridge *)netdev_priv(dev);
	काष्ठा nlattr *tb[IFLA_BRPORT_MAX + 1];
	काष्ठा net_bridge_port *p;
	काष्ठा nlattr *protinfo;
	काष्ठा nlattr *afspec;
	bool changed = false;
	पूर्णांक err = 0;

	protinfo = nlmsg_find_attr(nlh, माप(काष्ठा अगरinfomsg), IFLA_PROTINFO);
	afspec = nlmsg_find_attr(nlh, माप(काष्ठा अगरinfomsg), IFLA_AF_SPEC);
	अगर (!protinfo && !afspec)
		वापस 0;

	p = br_port_get_rtnl(dev);
	/* We want to accept dev as bridge itself अगर the AF_SPEC
	 * is set to see अगर someone is setting vlan info on the bridge
	 */
	अगर (!p && !afspec)
		वापस -EINVAL;

	अगर (p && protinfo) अणु
		अगर (protinfo->nla_type & NLA_F_NESTED) अणु
			err = nla_parse_nested_deprecated(tb, IFLA_BRPORT_MAX,
							  protinfo,
							  br_port_policy,
							  शून्य);
			अगर (err)
				वापस err;

			spin_lock_bh(&p->br->lock);
			err = br_setport(p, tb, extack);
			spin_unlock_bh(&p->br->lock);
		पूर्ण अन्यथा अणु
			/* Binary compatibility with old RSTP */
			अगर (nla_len(protinfo) < माप(u8))
				वापस -EINVAL;

			spin_lock_bh(&p->br->lock);
			err = br_set_port_state(p, nla_get_u8(protinfo));
			spin_unlock_bh(&p->br->lock);
		पूर्ण
		अगर (err)
			जाओ out;
		changed = true;
	पूर्ण

	अगर (afspec)
		err = br_afspec(br, p, afspec, RTM_SETLINK, &changed, extack);

	अगर (changed)
		br_अगरinfo_notअगरy(RTM_NEWLINK, br, p);
out:
	वापस err;
पूर्ण

/* Delete port inक्रमmation */
पूर्णांक br_dellink(काष्ठा net_device *dev, काष्ठा nlmsghdr *nlh, u16 flags)
अणु
	काष्ठा net_bridge *br = (काष्ठा net_bridge *)netdev_priv(dev);
	काष्ठा net_bridge_port *p;
	काष्ठा nlattr *afspec;
	bool changed = false;
	पूर्णांक err = 0;

	afspec = nlmsg_find_attr(nlh, माप(काष्ठा अगरinfomsg), IFLA_AF_SPEC);
	अगर (!afspec)
		वापस 0;

	p = br_port_get_rtnl(dev);
	/* We want to accept dev as bridge itself as well */
	अगर (!p && !(dev->priv_flags & IFF_EBRIDGE))
		वापस -EINVAL;

	err = br_afspec(br, p, afspec, RTM_DELLINK, &changed, शून्य);
	अगर (changed)
		/* Send RTM_NEWLINK because userspace
		 * expects RTM_NEWLINK क्रम vlan dels
		 */
		br_अगरinfo_notअगरy(RTM_NEWLINK, br, p);

	वापस err;
पूर्ण

अटल पूर्णांक br_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
		       काष्ठा netlink_ext_ack *extack)
अणु
	अगर (tb[IFLA_ADDRESS]) अणु
		अगर (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN)
			वापस -EINVAL;
		अगर (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS])))
			वापस -EADDRNOTAVAIL;
	पूर्ण

	अगर (!data)
		वापस 0;

#अगर_घोषित CONFIG_BRIDGE_VLAN_FILTERING
	अगर (data[IFLA_BR_VLAN_PROTOCOL] &&
	    !eth_type_vlan(nla_get_be16(data[IFLA_BR_VLAN_PROTOCOL])))
		वापस -EPROTONOSUPPORT;

	अगर (data[IFLA_BR_VLAN_DEFAULT_PVID]) अणु
		__u16 defpvid = nla_get_u16(data[IFLA_BR_VLAN_DEFAULT_PVID]);

		अगर (defpvid >= VLAN_VID_MASK)
			वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक br_port_slave_changelink(काष्ठा net_device *brdev,
				    काष्ठा net_device *dev,
				    काष्ठा nlattr *tb[],
				    काष्ठा nlattr *data[],
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_bridge *br = netdev_priv(brdev);
	पूर्णांक ret;

	अगर (!data)
		वापस 0;

	spin_lock_bh(&br->lock);
	ret = br_setport(br_port_get_rtnl(dev), data, extack);
	spin_unlock_bh(&br->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक br_port_fill_slave_info(काष्ठा sk_buff *skb,
				   स्थिर काष्ठा net_device *brdev,
				   स्थिर काष्ठा net_device *dev)
अणु
	वापस br_port_fill_attrs(skb, br_port_get_rtnl(dev));
पूर्ण

अटल माप_प्रकार br_port_get_slave_size(स्थिर काष्ठा net_device *brdev,
				     स्थिर काष्ठा net_device *dev)
अणु
	वापस br_port_info_size();
पूर्ण

अटल स्थिर काष्ठा nla_policy br_policy[IFLA_BR_MAX + 1] = अणु
	[IFLA_BR_FORWARD_DELAY]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BR_HELLO_TIME]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BR_MAX_AGE]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_BR_AGEING_TIME] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_BR_STP_STATE] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_BR_PRIORITY] = अणु .type = NLA_U16 पूर्ण,
	[IFLA_BR_VLAN_FILTERING] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BR_VLAN_PROTOCOL] = अणु .type = NLA_U16 पूर्ण,
	[IFLA_BR_GROUP_FWD_MASK] = अणु .type = NLA_U16 पूर्ण,
	[IFLA_BR_GROUP_ADDR] = अणु .type = NLA_BINARY,
				 .len  = ETH_ALEN पूर्ण,
	[IFLA_BR_MCAST_ROUTER] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BR_MCAST_SNOOPING] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BR_MCAST_QUERY_USE_IFADDR] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BR_MCAST_QUERIER] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BR_MCAST_HASH_ELASTICITY] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_BR_MCAST_HASH_MAX] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_BR_MCAST_LAST_MEMBER_CNT] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_BR_MCAST_STARTUP_QUERY_CNT] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_BR_MCAST_LAST_MEMBER_INTVL] = अणु .type = NLA_U64 पूर्ण,
	[IFLA_BR_MCAST_MEMBERSHIP_INTVL] = अणु .type = NLA_U64 पूर्ण,
	[IFLA_BR_MCAST_QUERIER_INTVL] = अणु .type = NLA_U64 पूर्ण,
	[IFLA_BR_MCAST_QUERY_INTVL] = अणु .type = NLA_U64 पूर्ण,
	[IFLA_BR_MCAST_QUERY_RESPONSE_INTVL] = अणु .type = NLA_U64 पूर्ण,
	[IFLA_BR_MCAST_STARTUP_QUERY_INTVL] = अणु .type = NLA_U64 पूर्ण,
	[IFLA_BR_NF_CALL_IPTABLES] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BR_NF_CALL_IP6TABLES] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BR_NF_CALL_ARPTABLES] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BR_VLAN_DEFAULT_PVID] = अणु .type = NLA_U16 पूर्ण,
	[IFLA_BR_VLAN_STATS_ENABLED] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BR_MCAST_STATS_ENABLED] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BR_MCAST_IGMP_VERSION] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BR_MCAST_MLD_VERSION] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BR_VLAN_STATS_PER_PORT] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_BR_MULTI_BOOLOPT] =
		NLA_POLICY_EXACT_LEN(माप(काष्ठा br_boolopt_multi)),
पूर्ण;

अटल पूर्णांक br_changelink(काष्ठा net_device *brdev, काष्ठा nlattr *tb[],
			 काष्ठा nlattr *data[],
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_bridge *br = netdev_priv(brdev);
	पूर्णांक err;

	अगर (!data)
		वापस 0;

	अगर (data[IFLA_BR_FORWARD_DELAY]) अणु
		err = br_set_क्रमward_delay(br, nla_get_u32(data[IFLA_BR_FORWARD_DELAY]));
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_BR_HELLO_TIME]) अणु
		err = br_set_hello_समय(br, nla_get_u32(data[IFLA_BR_HELLO_TIME]));
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_BR_MAX_AGE]) अणु
		err = br_set_max_age(br, nla_get_u32(data[IFLA_BR_MAX_AGE]));
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_BR_AGEING_TIME]) अणु
		err = br_set_ageing_समय(br, nla_get_u32(data[IFLA_BR_AGEING_TIME]));
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_BR_STP_STATE]) अणु
		u32 stp_enabled = nla_get_u32(data[IFLA_BR_STP_STATE]);

		err = br_stp_set_enabled(br, stp_enabled, extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_BR_PRIORITY]) अणु
		u32 priority = nla_get_u16(data[IFLA_BR_PRIORITY]);

		br_stp_set_bridge_priority(br, priority);
	पूर्ण

	अगर (data[IFLA_BR_VLAN_FILTERING]) अणु
		u8 vlan_filter = nla_get_u8(data[IFLA_BR_VLAN_FILTERING]);

		err = br_vlan_filter_toggle(br, vlan_filter, extack);
		अगर (err)
			वापस err;
	पूर्ण

#अगर_घोषित CONFIG_BRIDGE_VLAN_FILTERING
	अगर (data[IFLA_BR_VLAN_PROTOCOL]) अणु
		__be16 vlan_proto = nla_get_be16(data[IFLA_BR_VLAN_PROTOCOL]);

		err = __br_vlan_set_proto(br, vlan_proto, extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_BR_VLAN_DEFAULT_PVID]) अणु
		__u16 defpvid = nla_get_u16(data[IFLA_BR_VLAN_DEFAULT_PVID]);

		err = __br_vlan_set_शेष_pvid(br, defpvid, extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_BR_VLAN_STATS_ENABLED]) अणु
		__u8 vlan_stats = nla_get_u8(data[IFLA_BR_VLAN_STATS_ENABLED]);

		err = br_vlan_set_stats(br, vlan_stats);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_BR_VLAN_STATS_PER_PORT]) अणु
		__u8 per_port = nla_get_u8(data[IFLA_BR_VLAN_STATS_PER_PORT]);

		err = br_vlan_set_stats_per_port(br, per_port);
		अगर (err)
			वापस err;
	पूर्ण
#पूर्ण_अगर

	अगर (data[IFLA_BR_GROUP_FWD_MASK]) अणु
		u16 fwd_mask = nla_get_u16(data[IFLA_BR_GROUP_FWD_MASK]);

		अगर (fwd_mask & BR_GROUPFWD_RESTRICTED)
			वापस -EINVAL;
		br->group_fwd_mask = fwd_mask;
	पूर्ण

	अगर (data[IFLA_BR_GROUP_ADDR]) अणु
		u8 new_addr[ETH_ALEN];

		अगर (nla_len(data[IFLA_BR_GROUP_ADDR]) != ETH_ALEN)
			वापस -EINVAL;
		स_नकल(new_addr, nla_data(data[IFLA_BR_GROUP_ADDR]), ETH_ALEN);
		अगर (!is_link_local_ether_addr(new_addr))
			वापस -EINVAL;
		अगर (new_addr[5] == 1 ||		/* 802.3x Pause address */
		    new_addr[5] == 2 ||		/* 802.3ad Slow protocols */
		    new_addr[5] == 3)		/* 802.1X PAE address */
			वापस -EINVAL;
		spin_lock_bh(&br->lock);
		स_नकल(br->group_addr, new_addr, माप(br->group_addr));
		spin_unlock_bh(&br->lock);
		br_opt_toggle(br, BROPT_GROUP_ADDR_SET, true);
		br_recalculate_fwd_mask(br);
	पूर्ण

	अगर (data[IFLA_BR_FDB_FLUSH])
		br_fdb_flush(br);

#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
	अगर (data[IFLA_BR_MCAST_ROUTER]) अणु
		u8 multicast_router = nla_get_u8(data[IFLA_BR_MCAST_ROUTER]);

		err = br_multicast_set_router(br, multicast_router);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_BR_MCAST_SNOOPING]) अणु
		u8 mcast_snooping = nla_get_u8(data[IFLA_BR_MCAST_SNOOPING]);

		err = br_multicast_toggle(br, mcast_snooping, extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_BR_MCAST_QUERY_USE_IFADDR]) अणु
		u8 val;

		val = nla_get_u8(data[IFLA_BR_MCAST_QUERY_USE_IFADDR]);
		br_opt_toggle(br, BROPT_MULTICAST_QUERY_USE_IFADDR, !!val);
	पूर्ण

	अगर (data[IFLA_BR_MCAST_QUERIER]) अणु
		u8 mcast_querier = nla_get_u8(data[IFLA_BR_MCAST_QUERIER]);

		err = br_multicast_set_querier(br, mcast_querier);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data[IFLA_BR_MCAST_HASH_ELASTICITY])
		br_warn(br, "the hash_elasticity option has been deprecated and is always %u\n",
			RHT_ELASTICITY);

	अगर (data[IFLA_BR_MCAST_HASH_MAX])
		br->hash_max = nla_get_u32(data[IFLA_BR_MCAST_HASH_MAX]);

	अगर (data[IFLA_BR_MCAST_LAST_MEMBER_CNT]) अणु
		u32 val = nla_get_u32(data[IFLA_BR_MCAST_LAST_MEMBER_CNT]);

		br->multicast_last_member_count = val;
	पूर्ण

	अगर (data[IFLA_BR_MCAST_STARTUP_QUERY_CNT]) अणु
		u32 val = nla_get_u32(data[IFLA_BR_MCAST_STARTUP_QUERY_CNT]);

		br->multicast_startup_query_count = val;
	पूर्ण

	अगर (data[IFLA_BR_MCAST_LAST_MEMBER_INTVL]) अणु
		u64 val = nla_get_u64(data[IFLA_BR_MCAST_LAST_MEMBER_INTVL]);

		br->multicast_last_member_पूर्णांकerval = घड़ी_प्रकार_to_jअगरfies(val);
	पूर्ण

	अगर (data[IFLA_BR_MCAST_MEMBERSHIP_INTVL]) अणु
		u64 val = nla_get_u64(data[IFLA_BR_MCAST_MEMBERSHIP_INTVL]);

		br->multicast_membership_पूर्णांकerval = घड़ी_प्रकार_to_jअगरfies(val);
	पूर्ण

	अगर (data[IFLA_BR_MCAST_QUERIER_INTVL]) अणु
		u64 val = nla_get_u64(data[IFLA_BR_MCAST_QUERIER_INTVL]);

		br->multicast_querier_पूर्णांकerval = घड़ी_प्रकार_to_jअगरfies(val);
	पूर्ण

	अगर (data[IFLA_BR_MCAST_QUERY_INTVL]) अणु
		u64 val = nla_get_u64(data[IFLA_BR_MCAST_QUERY_INTVL]);

		br->multicast_query_पूर्णांकerval = घड़ी_प्रकार_to_jअगरfies(val);
	पूर्ण

	अगर (data[IFLA_BR_MCAST_QUERY_RESPONSE_INTVL]) अणु
		u64 val = nla_get_u64(data[IFLA_BR_MCAST_QUERY_RESPONSE_INTVL]);

		br->multicast_query_response_पूर्णांकerval = घड़ी_प्रकार_to_jअगरfies(val);
	पूर्ण

	अगर (data[IFLA_BR_MCAST_STARTUP_QUERY_INTVL]) अणु
		u64 val = nla_get_u64(data[IFLA_BR_MCAST_STARTUP_QUERY_INTVL]);

		br->multicast_startup_query_पूर्णांकerval = घड़ी_प्रकार_to_jअगरfies(val);
	पूर्ण

	अगर (data[IFLA_BR_MCAST_STATS_ENABLED]) अणु
		__u8 mcast_stats;

		mcast_stats = nla_get_u8(data[IFLA_BR_MCAST_STATS_ENABLED]);
		br_opt_toggle(br, BROPT_MULTICAST_STATS_ENABLED, !!mcast_stats);
	पूर्ण

	अगर (data[IFLA_BR_MCAST_IGMP_VERSION]) अणु
		__u8 igmp_version;

		igmp_version = nla_get_u8(data[IFLA_BR_MCAST_IGMP_VERSION]);
		err = br_multicast_set_igmp_version(br, igmp_version);
		अगर (err)
			वापस err;
	पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (data[IFLA_BR_MCAST_MLD_VERSION]) अणु
		__u8 mld_version;

		mld_version = nla_get_u8(data[IFLA_BR_MCAST_MLD_VERSION]);
		err = br_multicast_set_mld_version(br, mld_version);
		अगर (err)
			वापस err;
	पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	अगर (data[IFLA_BR_NF_CALL_IPTABLES]) अणु
		u8 val = nla_get_u8(data[IFLA_BR_NF_CALL_IPTABLES]);

		br_opt_toggle(br, BROPT_NF_CALL_IPTABLES, !!val);
	पूर्ण

	अगर (data[IFLA_BR_NF_CALL_IP6TABLES]) अणु
		u8 val = nla_get_u8(data[IFLA_BR_NF_CALL_IP6TABLES]);

		br_opt_toggle(br, BROPT_NF_CALL_IP6TABLES, !!val);
	पूर्ण

	अगर (data[IFLA_BR_NF_CALL_ARPTABLES]) अणु
		u8 val = nla_get_u8(data[IFLA_BR_NF_CALL_ARPTABLES]);

		br_opt_toggle(br, BROPT_NF_CALL_ARPTABLES, !!val);
	पूर्ण
#पूर्ण_अगर

	अगर (data[IFLA_BR_MULTI_BOOLOPT]) अणु
		काष्ठा br_boolopt_multi *bm;

		bm = nla_data(data[IFLA_BR_MULTI_BOOLOPT]);
		err = br_boolopt_multi_toggle(br, bm, extack);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक br_dev_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			  काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_bridge *br = netdev_priv(dev);
	पूर्णांक err;

	err = रेजिस्टर_netdevice(dev);
	अगर (err)
		वापस err;

	अगर (tb[IFLA_ADDRESS]) अणु
		spin_lock_bh(&br->lock);
		br_stp_change_bridge_id(br, nla_data(tb[IFLA_ADDRESS]));
		spin_unlock_bh(&br->lock);
	पूर्ण

	err = br_changelink(dev, tb, data, extack);
	अगर (err)
		br_dev_delete(dev, शून्य);

	वापस err;
पूर्ण

अटल माप_प्रकार br_get_size(स्थिर काष्ठा net_device *brdev)
अणु
	वापस nla_total_size(माप(u32)) +	/* IFLA_BR_FORWARD_DELAY  */
	       nla_total_size(माप(u32)) +	/* IFLA_BR_HELLO_TIME */
	       nla_total_size(माप(u32)) +	/* IFLA_BR_MAX_AGE */
	       nla_total_size(माप(u32)) +    /* IFLA_BR_AGEING_TIME */
	       nla_total_size(माप(u32)) +    /* IFLA_BR_STP_STATE */
	       nla_total_size(माप(u16)) +    /* IFLA_BR_PRIORITY */
	       nla_total_size(माप(u8)) +     /* IFLA_BR_VLAN_FILTERING */
#अगर_घोषित CONFIG_BRIDGE_VLAN_FILTERING
	       nla_total_size(माप(__be16)) +	/* IFLA_BR_VLAN_PROTOCOL */
	       nla_total_size(माप(u16)) +    /* IFLA_BR_VLAN_DEFAULT_PVID */
	       nla_total_size(माप(u8)) +     /* IFLA_BR_VLAN_STATS_ENABLED */
	       nla_total_size(माप(u8)) +	/* IFLA_BR_VLAN_STATS_PER_PORT */
#पूर्ण_अगर
	       nla_total_size(माप(u16)) +    /* IFLA_BR_GROUP_FWD_MASK */
	       nla_total_size(माप(काष्ठा अगरla_bridge_id)) +   /* IFLA_BR_ROOT_ID */
	       nla_total_size(माप(काष्ठा अगरla_bridge_id)) +   /* IFLA_BR_BRIDGE_ID */
	       nla_total_size(माप(u16)) +    /* IFLA_BR_ROOT_PORT */
	       nla_total_size(माप(u32)) +    /* IFLA_BR_ROOT_PATH_COST */
	       nla_total_size(माप(u8)) +     /* IFLA_BR_TOPOLOGY_CHANGE */
	       nla_total_size(माप(u8)) +     /* IFLA_BR_TOPOLOGY_CHANGE_DETECTED */
	       nla_total_size_64bit(माप(u64)) + /* IFLA_BR_HELLO_TIMER */
	       nla_total_size_64bit(माप(u64)) + /* IFLA_BR_TCN_TIMER */
	       nla_total_size_64bit(माप(u64)) + /* IFLA_BR_TOPOLOGY_CHANGE_TIMER */
	       nla_total_size_64bit(माप(u64)) + /* IFLA_BR_GC_TIMER */
	       nla_total_size(ETH_ALEN) +       /* IFLA_BR_GROUP_ADDR */
#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
	       nla_total_size(माप(u8)) +     /* IFLA_BR_MCAST_ROUTER */
	       nla_total_size(माप(u8)) +     /* IFLA_BR_MCAST_SNOOPING */
	       nla_total_size(माप(u8)) +     /* IFLA_BR_MCAST_QUERY_USE_IFADDR */
	       nla_total_size(माप(u8)) +     /* IFLA_BR_MCAST_QUERIER */
	       nla_total_size(माप(u8)) +     /* IFLA_BR_MCAST_STATS_ENABLED */
	       nla_total_size(माप(u32)) +    /* IFLA_BR_MCAST_HASH_ELASTICITY */
	       nla_total_size(माप(u32)) +    /* IFLA_BR_MCAST_HASH_MAX */
	       nla_total_size(माप(u32)) +    /* IFLA_BR_MCAST_LAST_MEMBER_CNT */
	       nla_total_size(माप(u32)) +    /* IFLA_BR_MCAST_STARTUP_QUERY_CNT */
	       nla_total_size_64bit(माप(u64)) + /* IFLA_BR_MCAST_LAST_MEMBER_INTVL */
	       nla_total_size_64bit(माप(u64)) + /* IFLA_BR_MCAST_MEMBERSHIP_INTVL */
	       nla_total_size_64bit(माप(u64)) + /* IFLA_BR_MCAST_QUERIER_INTVL */
	       nla_total_size_64bit(माप(u64)) + /* IFLA_BR_MCAST_QUERY_INTVL */
	       nla_total_size_64bit(माप(u64)) + /* IFLA_BR_MCAST_QUERY_RESPONSE_INTVL */
	       nla_total_size_64bit(माप(u64)) + /* IFLA_BR_MCAST_STARTUP_QUERY_INTVL */
	       nla_total_size(माप(u8)) +	/* IFLA_BR_MCAST_IGMP_VERSION */
	       nla_total_size(माप(u8)) +	/* IFLA_BR_MCAST_MLD_VERSION */
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	       nla_total_size(माप(u8)) +     /* IFLA_BR_NF_CALL_IPTABLES */
	       nla_total_size(माप(u8)) +     /* IFLA_BR_NF_CALL_IP6TABLES */
	       nla_total_size(माप(u8)) +     /* IFLA_BR_NF_CALL_ARPTABLES */
#पूर्ण_अगर
	       nla_total_size(माप(काष्ठा br_boolopt_multi)) + /* IFLA_BR_MULTI_BOOLOPT */
	       0;
पूर्ण

अटल पूर्णांक br_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *brdev)
अणु
	काष्ठा net_bridge *br = netdev_priv(brdev);
	u32 क्रमward_delay = jअगरfies_to_घड़ी_प्रकार(br->क्रमward_delay);
	u32 hello_समय = jअगरfies_to_घड़ी_प्रकार(br->hello_समय);
	u32 age_समय = jअगरfies_to_घड़ी_प्रकार(br->max_age);
	u32 ageing_समय = jअगरfies_to_घड़ी_प्रकार(br->ageing_समय);
	u32 stp_enabled = br->stp_enabled;
	u16 priority = (br->bridge_id.prio[0] << 8) | br->bridge_id.prio[1];
	u8 vlan_enabled = br_vlan_enabled(br->dev);
	काष्ठा br_boolopt_multi bm;
	u64 घड़ीval;

	घड़ीval = br_समयr_value(&br->hello_समयr);
	अगर (nla_put_u64_64bit(skb, IFLA_BR_HELLO_TIMER, घड़ीval, IFLA_BR_PAD))
		वापस -EMSGSIZE;
	घड़ीval = br_समयr_value(&br->tcn_समयr);
	अगर (nla_put_u64_64bit(skb, IFLA_BR_TCN_TIMER, घड़ीval, IFLA_BR_PAD))
		वापस -EMSGSIZE;
	घड़ीval = br_समयr_value(&br->topology_change_समयr);
	अगर (nla_put_u64_64bit(skb, IFLA_BR_TOPOLOGY_CHANGE_TIMER, घड़ीval,
			      IFLA_BR_PAD))
		वापस -EMSGSIZE;
	घड़ीval = br_समयr_value(&br->gc_work.समयr);
	अगर (nla_put_u64_64bit(skb, IFLA_BR_GC_TIMER, घड़ीval, IFLA_BR_PAD))
		वापस -EMSGSIZE;

	br_boolopt_multi_get(br, &bm);
	अगर (nla_put_u32(skb, IFLA_BR_FORWARD_DELAY, क्रमward_delay) ||
	    nla_put_u32(skb, IFLA_BR_HELLO_TIME, hello_समय) ||
	    nla_put_u32(skb, IFLA_BR_MAX_AGE, age_समय) ||
	    nla_put_u32(skb, IFLA_BR_AGEING_TIME, ageing_समय) ||
	    nla_put_u32(skb, IFLA_BR_STP_STATE, stp_enabled) ||
	    nla_put_u16(skb, IFLA_BR_PRIORITY, priority) ||
	    nla_put_u8(skb, IFLA_BR_VLAN_FILTERING, vlan_enabled) ||
	    nla_put_u16(skb, IFLA_BR_GROUP_FWD_MASK, br->group_fwd_mask) ||
	    nla_put(skb, IFLA_BR_BRIDGE_ID, माप(काष्ठा अगरla_bridge_id),
		    &br->bridge_id) ||
	    nla_put(skb, IFLA_BR_ROOT_ID, माप(काष्ठा अगरla_bridge_id),
		    &br->designated_root) ||
	    nla_put_u16(skb, IFLA_BR_ROOT_PORT, br->root_port) ||
	    nla_put_u32(skb, IFLA_BR_ROOT_PATH_COST, br->root_path_cost) ||
	    nla_put_u8(skb, IFLA_BR_TOPOLOGY_CHANGE, br->topology_change) ||
	    nla_put_u8(skb, IFLA_BR_TOPOLOGY_CHANGE_DETECTED,
		       br->topology_change_detected) ||
	    nla_put(skb, IFLA_BR_GROUP_ADDR, ETH_ALEN, br->group_addr) ||
	    nla_put(skb, IFLA_BR_MULTI_BOOLOPT, माप(bm), &bm))
		वापस -EMSGSIZE;

#अगर_घोषित CONFIG_BRIDGE_VLAN_FILTERING
	अगर (nla_put_be16(skb, IFLA_BR_VLAN_PROTOCOL, br->vlan_proto) ||
	    nla_put_u16(skb, IFLA_BR_VLAN_DEFAULT_PVID, br->शेष_pvid) ||
	    nla_put_u8(skb, IFLA_BR_VLAN_STATS_ENABLED,
		       br_opt_get(br, BROPT_VLAN_STATS_ENABLED)) ||
	    nla_put_u8(skb, IFLA_BR_VLAN_STATS_PER_PORT,
		       br_opt_get(br, BROPT_VLAN_STATS_PER_PORT)))
		वापस -EMSGSIZE;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
	अगर (nla_put_u8(skb, IFLA_BR_MCAST_ROUTER, br->multicast_router) ||
	    nla_put_u8(skb, IFLA_BR_MCAST_SNOOPING,
		       br_opt_get(br, BROPT_MULTICAST_ENABLED)) ||
	    nla_put_u8(skb, IFLA_BR_MCAST_QUERY_USE_IFADDR,
		       br_opt_get(br, BROPT_MULTICAST_QUERY_USE_IFADDR)) ||
	    nla_put_u8(skb, IFLA_BR_MCAST_QUERIER,
		       br_opt_get(br, BROPT_MULTICAST_QUERIER)) ||
	    nla_put_u8(skb, IFLA_BR_MCAST_STATS_ENABLED,
		       br_opt_get(br, BROPT_MULTICAST_STATS_ENABLED)) ||
	    nla_put_u32(skb, IFLA_BR_MCAST_HASH_ELASTICITY, RHT_ELASTICITY) ||
	    nla_put_u32(skb, IFLA_BR_MCAST_HASH_MAX, br->hash_max) ||
	    nla_put_u32(skb, IFLA_BR_MCAST_LAST_MEMBER_CNT,
			br->multicast_last_member_count) ||
	    nla_put_u32(skb, IFLA_BR_MCAST_STARTUP_QUERY_CNT,
			br->multicast_startup_query_count) ||
	    nla_put_u8(skb, IFLA_BR_MCAST_IGMP_VERSION,
		       br->multicast_igmp_version))
		वापस -EMSGSIZE;
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (nla_put_u8(skb, IFLA_BR_MCAST_MLD_VERSION,
		       br->multicast_mld_version))
		वापस -EMSGSIZE;
#पूर्ण_अगर
	घड़ीval = jअगरfies_to_घड़ी_प्रकार(br->multicast_last_member_पूर्णांकerval);
	अगर (nla_put_u64_64bit(skb, IFLA_BR_MCAST_LAST_MEMBER_INTVL, घड़ीval,
			      IFLA_BR_PAD))
		वापस -EMSGSIZE;
	घड़ीval = jअगरfies_to_घड़ी_प्रकार(br->multicast_membership_पूर्णांकerval);
	अगर (nla_put_u64_64bit(skb, IFLA_BR_MCAST_MEMBERSHIP_INTVL, घड़ीval,
			      IFLA_BR_PAD))
		वापस -EMSGSIZE;
	घड़ीval = jअगरfies_to_घड़ी_प्रकार(br->multicast_querier_पूर्णांकerval);
	अगर (nla_put_u64_64bit(skb, IFLA_BR_MCAST_QUERIER_INTVL, घड़ीval,
			      IFLA_BR_PAD))
		वापस -EMSGSIZE;
	घड़ीval = jअगरfies_to_घड़ी_प्रकार(br->multicast_query_पूर्णांकerval);
	अगर (nla_put_u64_64bit(skb, IFLA_BR_MCAST_QUERY_INTVL, घड़ीval,
			      IFLA_BR_PAD))
		वापस -EMSGSIZE;
	घड़ीval = jअगरfies_to_घड़ी_प्रकार(br->multicast_query_response_पूर्णांकerval);
	अगर (nla_put_u64_64bit(skb, IFLA_BR_MCAST_QUERY_RESPONSE_INTVL, घड़ीval,
			      IFLA_BR_PAD))
		वापस -EMSGSIZE;
	घड़ीval = jअगरfies_to_घड़ी_प्रकार(br->multicast_startup_query_पूर्णांकerval);
	अगर (nla_put_u64_64bit(skb, IFLA_BR_MCAST_STARTUP_QUERY_INTVL, घड़ीval,
			      IFLA_BR_PAD))
		वापस -EMSGSIZE;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	अगर (nla_put_u8(skb, IFLA_BR_NF_CALL_IPTABLES,
		       br_opt_get(br, BROPT_NF_CALL_IPTABLES) ? 1 : 0) ||
	    nla_put_u8(skb, IFLA_BR_NF_CALL_IP6TABLES,
		       br_opt_get(br, BROPT_NF_CALL_IP6TABLES) ? 1 : 0) ||
	    nla_put_u8(skb, IFLA_BR_NF_CALL_ARPTABLES,
		       br_opt_get(br, BROPT_NF_CALL_ARPTABLES) ? 1 : 0))
		वापस -EMSGSIZE;
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल माप_प्रकार br_get_linkxstats_size(स्थिर काष्ठा net_device *dev, पूर्णांक attr)
अणु
	काष्ठा net_bridge_port *p = शून्य;
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_vlan *v;
	काष्ठा net_bridge *br;
	पूर्णांक numvls = 0;

	चयन (attr) अणु
	हाल IFLA_STATS_LINK_XSTATS:
		br = netdev_priv(dev);
		vg = br_vlan_group(br);
		अवरोध;
	हाल IFLA_STATS_LINK_XSTATS_SLAVE:
		p = br_port_get_rtnl(dev);
		अगर (!p)
			वापस 0;
		br = p->br;
		vg = nbp_vlan_group(p);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (vg) अणु
		/* we need to count all, even placeholder entries */
		list_क्रम_each_entry(v, &vg->vlan_list, vlist)
			numvls++;
	पूर्ण

	वापस numvls * nla_total_size(माप(काष्ठा bridge_vlan_xstats)) +
	       nla_total_size(माप(काष्ठा br_mcast_stats)) +
	       nla_total_size(0);
पूर्ण

अटल पूर्णांक br_fill_linkxstats(काष्ठा sk_buff *skb,
			      स्थिर काष्ठा net_device *dev,
			      पूर्णांक *prividx, पूर्णांक attr)
अणु
	काष्ठा nlattr *nla __maybe_unused;
	काष्ठा net_bridge_port *p = शून्य;
	काष्ठा net_bridge_vlan_group *vg;
	काष्ठा net_bridge_vlan *v;
	काष्ठा net_bridge *br;
	काष्ठा nlattr *nest;
	पूर्णांक vl_idx = 0;

	चयन (attr) अणु
	हाल IFLA_STATS_LINK_XSTATS:
		br = netdev_priv(dev);
		vg = br_vlan_group(br);
		अवरोध;
	हाल IFLA_STATS_LINK_XSTATS_SLAVE:
		p = br_port_get_rtnl(dev);
		अगर (!p)
			वापस 0;
		br = p->br;
		vg = nbp_vlan_group(p);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	nest = nla_nest_start_noflag(skb, LINK_XSTATS_TYPE_BRIDGE);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (vg) अणु
		u16 pvid;

		pvid = br_get_pvid(vg);
		list_क्रम_each_entry(v, &vg->vlan_list, vlist) अणु
			काष्ठा bridge_vlan_xstats vxi;
			काष्ठा pcpu_sw_netstats stats;

			अगर (++vl_idx < *prividx)
				जारी;
			स_रखो(&vxi, 0, माप(vxi));
			vxi.vid = v->vid;
			vxi.flags = v->flags;
			अगर (v->vid == pvid)
				vxi.flags |= BRIDGE_VLAN_INFO_PVID;
			br_vlan_get_stats(v, &stats);
			vxi.rx_bytes = stats.rx_bytes;
			vxi.rx_packets = stats.rx_packets;
			vxi.tx_bytes = stats.tx_bytes;
			vxi.tx_packets = stats.tx_packets;

			अगर (nla_put(skb, BRIDGE_XSTATS_VLAN, माप(vxi), &vxi))
				जाओ nla_put_failure;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
	अगर (++vl_idx >= *prividx) अणु
		nla = nla_reserve_64bit(skb, BRIDGE_XSTATS_MCAST,
					माप(काष्ठा br_mcast_stats),
					BRIDGE_XSTATS_PAD);
		अगर (!nla)
			जाओ nla_put_failure;
		br_multicast_get_stats(br, p, nla_data(nla));
	पूर्ण
#पूर्ण_अगर

	अगर (p) अणु
		nla = nla_reserve_64bit(skb, BRIDGE_XSTATS_STP,
					माप(p->stp_xstats),
					BRIDGE_XSTATS_PAD);
		अगर (!nla)
			जाओ nla_put_failure;

		spin_lock_bh(&br->lock);
		स_नकल(nla_data(nla), &p->stp_xstats, माप(p->stp_xstats));
		spin_unlock_bh(&br->lock);
	पूर्ण

	nla_nest_end(skb, nest);
	*prividx = 0;

	वापस 0;

nla_put_failure:
	nla_nest_end(skb, nest);
	*prividx = vl_idx;

	वापस -EMSGSIZE;
पूर्ण

अटल काष्ठा rtnl_af_ops br_af_ops __पढ़ो_mostly = अणु
	.family			= AF_BRIDGE,
	.get_link_af_size	= br_get_link_af_size_filtered,
पूर्ण;

काष्ठा rtnl_link_ops br_link_ops __पढ़ो_mostly = अणु
	.kind			= "bridge",
	.priv_size		= माप(काष्ठा net_bridge),
	.setup			= br_dev_setup,
	.maxtype		= IFLA_BR_MAX,
	.policy			= br_policy,
	.validate		= br_validate,
	.newlink		= br_dev_newlink,
	.changelink		= br_changelink,
	.dellink		= br_dev_delete,
	.get_size		= br_get_size,
	.fill_info		= br_fill_info,
	.fill_linkxstats	= br_fill_linkxstats,
	.get_linkxstats_size	= br_get_linkxstats_size,

	.slave_maxtype		= IFLA_BRPORT_MAX,
	.slave_policy		= br_port_policy,
	.slave_changelink	= br_port_slave_changelink,
	.get_slave_size		= br_port_get_slave_size,
	.fill_slave_info	= br_port_fill_slave_info,
पूर्ण;

पूर्णांक __init br_netlink_init(व्योम)
अणु
	पूर्णांक err;

	br_mdb_init();
	br_vlan_rtnl_init();
	rtnl_af_रेजिस्टर(&br_af_ops);

	err = rtnl_link_रेजिस्टर(&br_link_ops);
	अगर (err)
		जाओ out_af;

	वापस 0;

out_af:
	rtnl_af_unरेजिस्टर(&br_af_ops);
	br_mdb_uninit();
	वापस err;
पूर्ण

व्योम br_netlink_fini(व्योम)
अणु
	br_mdb_uninit();
	br_vlan_rtnl_uninit();
	rtnl_af_unरेजिस्टर(&br_af_ops);
	rtnl_link_unरेजिस्टर(&br_link_ops);
पूर्ण
