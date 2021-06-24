<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/अगर_bridge.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/refcount.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/workqueue.h>
#समावेश <net/arp.h>
#समावेश <net/gre.h>
#समावेश <net/lag.h>
#समावेश <net/ndisc.h>
#समावेश <net/ip6_tunnel.h>

#समावेश "spectrum.h"
#समावेश "spectrum_ipip.h"
#समावेश "spectrum_span.h"
#समावेश "spectrum_switchdev.h"

काष्ठा mlxsw_sp_span अणु
	काष्ठा work_काष्ठा work;
	काष्ठा mlxsw_sp *mlxsw_sp;
	स्थिर काष्ठा mlxsw_sp_span_trigger_ops **span_trigger_ops_arr;
	स्थिर काष्ठा mlxsw_sp_span_entry_ops **span_entry_ops_arr;
	माप_प्रकार span_entry_ops_arr_size;
	काष्ठा list_head analyzed_ports_list;
	काष्ठा mutex analyzed_ports_lock; /* Protects analyzed_ports_list */
	काष्ठा list_head trigger_entries_list;
	u16 policer_id_base;
	refcount_t policer_id_base_ref_count;
	atomic_t active_entries_count;
	पूर्णांक entries_count;
	काष्ठा mlxsw_sp_span_entry entries[];
पूर्ण;

काष्ठा mlxsw_sp_span_analyzed_port अणु
	काष्ठा list_head list; /* Member of analyzed_ports_list */
	refcount_t ref_count;
	u8 local_port;
	bool ingress;
पूर्ण;

काष्ठा mlxsw_sp_span_trigger_entry अणु
	काष्ठा list_head list; /* Member of trigger_entries_list */
	काष्ठा mlxsw_sp_span *span;
	स्थिर काष्ठा mlxsw_sp_span_trigger_ops *ops;
	refcount_t ref_count;
	u8 local_port;
	क्रमागत mlxsw_sp_span_trigger trigger;
	काष्ठा mlxsw_sp_span_trigger_parms parms;
पूर्ण;

क्रमागत mlxsw_sp_span_trigger_type अणु
	MLXSW_SP_SPAN_TRIGGER_TYPE_PORT,
	MLXSW_SP_SPAN_TRIGGER_TYPE_GLOBAL,
पूर्ण;

काष्ठा mlxsw_sp_span_trigger_ops अणु
	पूर्णांक (*bind)(काष्ठा mlxsw_sp_span_trigger_entry *trigger_entry);
	व्योम (*unbind)(काष्ठा mlxsw_sp_span_trigger_entry *trigger_entry);
	bool (*matches)(काष्ठा mlxsw_sp_span_trigger_entry *trigger_entry,
			क्रमागत mlxsw_sp_span_trigger trigger,
			काष्ठा mlxsw_sp_port *mlxsw_sp_port);
	पूर्णांक (*enable)(काष्ठा mlxsw_sp_span_trigger_entry *trigger_entry,
		      काष्ठा mlxsw_sp_port *mlxsw_sp_port, u8 tc);
	व्योम (*disable)(काष्ठा mlxsw_sp_span_trigger_entry *trigger_entry,
			काष्ठा mlxsw_sp_port *mlxsw_sp_port, u8 tc);
पूर्ण;

अटल व्योम mlxsw_sp_span_respin_work(काष्ठा work_काष्ठा *work);

अटल u64 mlxsw_sp_span_occ_get(व्योम *priv)
अणु
	स्थिर काष्ठा mlxsw_sp *mlxsw_sp = priv;

	वापस atomic_पढ़ो(&mlxsw_sp->span->active_entries_count);
पूर्ण

पूर्णांक mlxsw_sp_span_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);
	काष्ठा mlxsw_sp_span *span;
	पूर्णांक i, entries_count, err;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, MAX_SPAN))
		वापस -EIO;

	entries_count = MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_SPAN);
	span = kzalloc(काष्ठा_size(span, entries, entries_count), GFP_KERNEL);
	अगर (!span)
		वापस -ENOMEM;
	refcount_set(&span->policer_id_base_ref_count, 0);
	span->entries_count = entries_count;
	atomic_set(&span->active_entries_count, 0);
	mutex_init(&span->analyzed_ports_lock);
	INIT_LIST_HEAD(&span->analyzed_ports_list);
	INIT_LIST_HEAD(&span->trigger_entries_list);
	span->mlxsw_sp = mlxsw_sp;
	mlxsw_sp->span = span;

	क्रम (i = 0; i < mlxsw_sp->span->entries_count; i++)
		mlxsw_sp->span->entries[i].id = i;

	err = mlxsw_sp->span_ops->init(mlxsw_sp);
	अगर (err)
		जाओ err_init;

	devlink_resource_occ_get_रेजिस्टर(devlink, MLXSW_SP_RESOURCE_SPAN,
					  mlxsw_sp_span_occ_get, mlxsw_sp);
	INIT_WORK(&span->work, mlxsw_sp_span_respin_work);

	वापस 0;

err_init:
	mutex_destroy(&mlxsw_sp->span->analyzed_ports_lock);
	kमुक्त(mlxsw_sp->span);
	वापस err;
पूर्ण

व्योम mlxsw_sp_span_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);

	cancel_work_sync(&mlxsw_sp->span->work);
	devlink_resource_occ_get_unरेजिस्टर(devlink, MLXSW_SP_RESOURCE_SPAN);

	WARN_ON_ONCE(!list_empty(&mlxsw_sp->span->trigger_entries_list));
	WARN_ON_ONCE(!list_empty(&mlxsw_sp->span->analyzed_ports_list));
	mutex_destroy(&mlxsw_sp->span->analyzed_ports_lock);
	kमुक्त(mlxsw_sp->span);
पूर्ण

अटल bool mlxsw_sp1_span_cpu_can_handle(स्थिर काष्ठा net_device *dev)
अणु
	वापस !dev;
पूर्ण

अटल पूर्णांक mlxsw_sp1_span_entry_cpu_parms(काष्ठा mlxsw_sp *mlxsw_sp,
					  स्थिर काष्ठा net_device *to_dev,
					  काष्ठा mlxsw_sp_span_parms *sparmsp)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
mlxsw_sp1_span_entry_cpu_configure(काष्ठा mlxsw_sp_span_entry *span_entry,
				   काष्ठा mlxsw_sp_span_parms sparms)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम
mlxsw_sp1_span_entry_cpu_deconfigure(काष्ठा mlxsw_sp_span_entry *span_entry)
अणु
पूर्ण

अटल स्थिर
काष्ठा mlxsw_sp_span_entry_ops mlxsw_sp1_span_entry_ops_cpu = अणु
	.is_अटल = true,
	.can_handle = mlxsw_sp1_span_cpu_can_handle,
	.parms_set = mlxsw_sp1_span_entry_cpu_parms,
	.configure = mlxsw_sp1_span_entry_cpu_configure,
	.deconfigure = mlxsw_sp1_span_entry_cpu_deconfigure,
पूर्ण;

अटल पूर्णांक
mlxsw_sp_span_entry_phys_parms(काष्ठा mlxsw_sp *mlxsw_sp,
			       स्थिर काष्ठा net_device *to_dev,
			       काष्ठा mlxsw_sp_span_parms *sparmsp)
अणु
	sparmsp->dest_port = netdev_priv(to_dev);
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_span_entry_phys_configure(काष्ठा mlxsw_sp_span_entry *span_entry,
				   काष्ठा mlxsw_sp_span_parms sparms)
अणु
	काष्ठा mlxsw_sp_port *dest_port = sparms.dest_port;
	काष्ठा mlxsw_sp *mlxsw_sp = dest_port->mlxsw_sp;
	u8 local_port = dest_port->local_port;
	अक्षर mpat_pl[MLXSW_REG_MPAT_LEN];
	पूर्णांक pa_id = span_entry->id;

	/* Create a new port analayzer entry क्रम local_port. */
	mlxsw_reg_mpat_pack(mpat_pl, pa_id, local_port, true,
			    MLXSW_REG_MPAT_SPAN_TYPE_LOCAL_ETH);
	mlxsw_reg_mpat_session_id_set(mpat_pl, sparms.session_id);
	mlxsw_reg_mpat_pide_set(mpat_pl, sparms.policer_enable);
	mlxsw_reg_mpat_pid_set(mpat_pl, sparms.policer_id);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(mpat), mpat_pl);
पूर्ण

अटल व्योम
mlxsw_sp_span_entry_deconfigure_common(काष्ठा mlxsw_sp_span_entry *span_entry,
				       क्रमागत mlxsw_reg_mpat_span_type span_type)
अणु
	काष्ठा mlxsw_sp_port *dest_port = span_entry->parms.dest_port;
	काष्ठा mlxsw_sp *mlxsw_sp = dest_port->mlxsw_sp;
	u8 local_port = dest_port->local_port;
	अक्षर mpat_pl[MLXSW_REG_MPAT_LEN];
	पूर्णांक pa_id = span_entry->id;

	mlxsw_reg_mpat_pack(mpat_pl, pa_id, local_port, false, span_type);
	mlxsw_reg_mpat_session_id_set(mpat_pl, span_entry->parms.session_id);
	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(mpat), mpat_pl);
पूर्ण

अटल व्योम
mlxsw_sp_span_entry_phys_deconfigure(काष्ठा mlxsw_sp_span_entry *span_entry)
अणु
	mlxsw_sp_span_entry_deconfigure_common(span_entry,
					    MLXSW_REG_MPAT_SPAN_TYPE_LOCAL_ETH);
पूर्ण

अटल स्थिर
काष्ठा mlxsw_sp_span_entry_ops mlxsw_sp_span_entry_ops_phys = अणु
	.is_अटल = true,
	.can_handle = mlxsw_sp_port_dev_check,
	.parms_set = mlxsw_sp_span_entry_phys_parms,
	.configure = mlxsw_sp_span_entry_phys_configure,
	.deconfigure = mlxsw_sp_span_entry_phys_deconfigure,
पूर्ण;

अटल पूर्णांक mlxsw_sp_span_dmac(काष्ठा neigh_table *tbl,
			      स्थिर व्योम *pkey,
			      काष्ठा net_device *dev,
			      अचिन्हित अक्षर dmac[ETH_ALEN])
अणु
	काष्ठा neighbour *neigh = neigh_lookup(tbl, pkey, dev);
	पूर्णांक err = 0;

	अगर (!neigh) अणु
		neigh = neigh_create(tbl, pkey, dev);
		अगर (IS_ERR(neigh))
			वापस PTR_ERR(neigh);
	पूर्ण

	neigh_event_send(neigh, शून्य);

	पढ़ो_lock_bh(&neigh->lock);
	अगर ((neigh->nud_state & NUD_VALID) && !neigh->dead)
		स_नकल(dmac, neigh->ha, ETH_ALEN);
	अन्यथा
		err = -ENOENT;
	पढ़ो_unlock_bh(&neigh->lock);

	neigh_release(neigh);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_span_entry_unoffloadable(काष्ठा mlxsw_sp_span_parms *sparmsp)
अणु
	sparmsp->dest_port = शून्य;
	वापस 0;
पूर्ण

अटल काष्ठा net_device *
mlxsw_sp_span_entry_bridge_8021q(स्थिर काष्ठा net_device *br_dev,
				 अचिन्हित अक्षर *dmac,
				 u16 *p_vid)
अणु
	काष्ठा bridge_vlan_info vinfo;
	काष्ठा net_device *edev;
	u16 vid = *p_vid;

	अगर (!vid && WARN_ON(br_vlan_get_pvid(br_dev, &vid)))
		वापस शून्य;
	अगर (!vid ||
	    br_vlan_get_info(br_dev, vid, &vinfo) ||
	    !(vinfo.flags & BRIDGE_VLAN_INFO_BRENTRY))
		वापस शून्य;

	edev = br_fdb_find_port(br_dev, dmac, vid);
	अगर (!edev)
		वापस शून्य;

	अगर (br_vlan_get_info(edev, vid, &vinfo))
		वापस शून्य;
	अगर (vinfo.flags & BRIDGE_VLAN_INFO_UNTAGGED)
		*p_vid = 0;
	अन्यथा
		*p_vid = vid;
	वापस edev;
पूर्ण

अटल काष्ठा net_device *
mlxsw_sp_span_entry_bridge_8021d(स्थिर काष्ठा net_device *br_dev,
				 अचिन्हित अक्षर *dmac)
अणु
	वापस br_fdb_find_port(br_dev, dmac, 0);
पूर्ण

अटल काष्ठा net_device *
mlxsw_sp_span_entry_bridge(स्थिर काष्ठा net_device *br_dev,
			   अचिन्हित अक्षर dmac[ETH_ALEN],
			   u16 *p_vid)
अणु
	काष्ठा mlxsw_sp_bridge_port *bridge_port;
	क्रमागत mlxsw_reg_spms_state spms_state;
	काष्ठा net_device *dev = शून्य;
	काष्ठा mlxsw_sp_port *port;
	u8 stp_state;

	अगर (br_vlan_enabled(br_dev))
		dev = mlxsw_sp_span_entry_bridge_8021q(br_dev, dmac, p_vid);
	अन्यथा अगर (!*p_vid)
		dev = mlxsw_sp_span_entry_bridge_8021d(br_dev, dmac);
	अगर (!dev)
		वापस शून्य;

	port = mlxsw_sp_port_dev_lower_find(dev);
	अगर (!port)
		वापस शून्य;

	bridge_port = mlxsw_sp_bridge_port_find(port->mlxsw_sp->bridge, dev);
	अगर (!bridge_port)
		वापस शून्य;

	stp_state = mlxsw_sp_bridge_port_stp_state(bridge_port);
	spms_state = mlxsw_sp_stp_spms_state(stp_state);
	अगर (spms_state != MLXSW_REG_SPMS_STATE_FORWARDING)
		वापस शून्य;

	वापस dev;
पूर्ण

अटल काष्ठा net_device *
mlxsw_sp_span_entry_vlan(स्थिर काष्ठा net_device *vlan_dev,
			 u16 *p_vid)
अणु
	*p_vid = vlan_dev_vlan_id(vlan_dev);
	वापस vlan_dev_real_dev(vlan_dev);
पूर्ण

अटल काष्ठा net_device *
mlxsw_sp_span_entry_lag(काष्ठा net_device *lag_dev)
अणु
	काष्ठा net_device *dev;
	काष्ठा list_head *iter;

	netdev_क्रम_each_lower_dev(lag_dev, dev, iter)
		अगर (netअगर_carrier_ok(dev) &&
		    net_lag_port_dev_txable(dev) &&
		    mlxsw_sp_port_dev_check(dev))
			वापस dev;

	वापस शून्य;
पूर्ण

अटल __maybe_unused पूर्णांक
mlxsw_sp_span_entry_tunnel_parms_common(काष्ठा net_device *edev,
					जोड़ mlxsw_sp_l3addr saddr,
					जोड़ mlxsw_sp_l3addr daddr,
					जोड़ mlxsw_sp_l3addr gw,
					__u8 ttl,
					काष्ठा neigh_table *tbl,
					काष्ठा mlxsw_sp_span_parms *sparmsp)
अणु
	अचिन्हित अक्षर dmac[ETH_ALEN];
	u16 vid = 0;

	अगर (mlxsw_sp_l3addr_is_zero(gw))
		gw = daddr;

	अगर (!edev || mlxsw_sp_span_dmac(tbl, &gw, edev, dmac))
		जाओ unoffloadable;

	अगर (is_vlan_dev(edev))
		edev = mlxsw_sp_span_entry_vlan(edev, &vid);

	अगर (netअगर_is_bridge_master(edev)) अणु
		edev = mlxsw_sp_span_entry_bridge(edev, dmac, &vid);
		अगर (!edev)
			जाओ unoffloadable;
	पूर्ण

	अगर (is_vlan_dev(edev)) अणु
		अगर (vid || !(edev->flags & IFF_UP))
			जाओ unoffloadable;
		edev = mlxsw_sp_span_entry_vlan(edev, &vid);
	पूर्ण

	अगर (netअगर_is_lag_master(edev)) अणु
		अगर (!(edev->flags & IFF_UP))
			जाओ unoffloadable;
		edev = mlxsw_sp_span_entry_lag(edev);
		अगर (!edev)
			जाओ unoffloadable;
	पूर्ण

	अगर (!mlxsw_sp_port_dev_check(edev))
		जाओ unoffloadable;

	sparmsp->dest_port = netdev_priv(edev);
	sparmsp->ttl = ttl;
	स_नकल(sparmsp->dmac, dmac, ETH_ALEN);
	स_नकल(sparmsp->smac, edev->dev_addr, ETH_ALEN);
	sparmsp->saddr = saddr;
	sparmsp->daddr = daddr;
	sparmsp->vid = vid;
	वापस 0;

unoffloadable:
	वापस mlxsw_sp_span_entry_unoffloadable(sparmsp);
पूर्ण

#अगर IS_ENABLED(CONFIG_NET_IPGRE)
अटल काष्ठा net_device *
mlxsw_sp_span_gretap4_route(स्थिर काष्ठा net_device *to_dev,
			    __be32 *saddrp, __be32 *daddrp)
अणु
	काष्ठा ip_tunnel *tun = netdev_priv(to_dev);
	काष्ठा net_device *dev = शून्य;
	काष्ठा ip_tunnel_parm parms;
	काष्ठा rtable *rt = शून्य;
	काष्ठा flowi4 fl4;

	/* We assume "dev" stays valid after rt is put. */
	ASSERT_RTNL();

	parms = mlxsw_sp_ipip_netdev_parms4(to_dev);
	ip_tunnel_init_flow(&fl4, parms.iph.protocol, *daddrp, *saddrp,
			    0, 0, parms.link, tun->fwmark, 0);

	rt = ip_route_output_key(tun->net, &fl4);
	अगर (IS_ERR(rt))
		वापस शून्य;

	अगर (rt->rt_type != RTN_UNICAST)
		जाओ out;

	dev = rt->dst.dev;
	*saddrp = fl4.saddr;
	अगर (rt->rt_gw_family == AF_INET)
		*daddrp = rt->rt_gw4;
	/* can not offload अगर route has an IPv6 gateway */
	अन्यथा अगर (rt->rt_gw_family == AF_INET6)
		dev = शून्य;

out:
	ip_rt_put(rt);
	वापस dev;
पूर्ण

अटल पूर्णांक
mlxsw_sp_span_entry_gretap4_parms(काष्ठा mlxsw_sp *mlxsw_sp,
				  स्थिर काष्ठा net_device *to_dev,
				  काष्ठा mlxsw_sp_span_parms *sparmsp)
अणु
	काष्ठा ip_tunnel_parm tparm = mlxsw_sp_ipip_netdev_parms4(to_dev);
	जोड़ mlxsw_sp_l3addr saddr = अणु .addr4 = tparm.iph.saddr पूर्ण;
	जोड़ mlxsw_sp_l3addr daddr = अणु .addr4 = tparm.iph.daddr पूर्ण;
	bool inherit_tos = tparm.iph.tos & 0x1;
	bool inherit_ttl = !tparm.iph.ttl;
	जोड़ mlxsw_sp_l3addr gw = daddr;
	काष्ठा net_device *l3edev;

	अगर (!(to_dev->flags & IFF_UP) ||
	    /* Reject tunnels with GRE keys, checksums, etc. */
	    tparm.i_flags || tparm.o_flags ||
	    /* Require a fixed TTL and a TOS copied from the mirrored packet. */
	    inherit_ttl || !inherit_tos ||
	    /* A destination address may not be "any". */
	    mlxsw_sp_l3addr_is_zero(daddr))
		वापस mlxsw_sp_span_entry_unoffloadable(sparmsp);

	l3edev = mlxsw_sp_span_gretap4_route(to_dev, &saddr.addr4, &gw.addr4);
	वापस mlxsw_sp_span_entry_tunnel_parms_common(l3edev, saddr, daddr, gw,
						       tparm.iph.ttl,
						       &arp_tbl, sparmsp);
पूर्ण

अटल पूर्णांक
mlxsw_sp_span_entry_gretap4_configure(काष्ठा mlxsw_sp_span_entry *span_entry,
				      काष्ठा mlxsw_sp_span_parms sparms)
अणु
	काष्ठा mlxsw_sp_port *dest_port = sparms.dest_port;
	काष्ठा mlxsw_sp *mlxsw_sp = dest_port->mlxsw_sp;
	u8 local_port = dest_port->local_port;
	अक्षर mpat_pl[MLXSW_REG_MPAT_LEN];
	पूर्णांक pa_id = span_entry->id;

	/* Create a new port analayzer entry क्रम local_port. */
	mlxsw_reg_mpat_pack(mpat_pl, pa_id, local_port, true,
			    MLXSW_REG_MPAT_SPAN_TYPE_REMOTE_ETH_L3);
	mlxsw_reg_mpat_pide_set(mpat_pl, sparms.policer_enable);
	mlxsw_reg_mpat_pid_set(mpat_pl, sparms.policer_id);
	mlxsw_reg_mpat_eth_rspan_pack(mpat_pl, sparms.vid);
	mlxsw_reg_mpat_eth_rspan_l2_pack(mpat_pl,
				    MLXSW_REG_MPAT_ETH_RSPAN_VERSION_NO_HEADER,
				    sparms.dmac, !!sparms.vid);
	mlxsw_reg_mpat_eth_rspan_l3_ipv4_pack(mpat_pl,
					      sparms.ttl, sparms.smac,
					      be32_to_cpu(sparms.saddr.addr4),
					      be32_to_cpu(sparms.daddr.addr4));

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(mpat), mpat_pl);
पूर्ण

अटल व्योम
mlxsw_sp_span_entry_gretap4_deconfigure(काष्ठा mlxsw_sp_span_entry *span_entry)
अणु
	mlxsw_sp_span_entry_deconfigure_common(span_entry,
					MLXSW_REG_MPAT_SPAN_TYPE_REMOTE_ETH_L3);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_span_entry_ops mlxsw_sp_span_entry_ops_gretap4 = अणु
	.can_handle = netअगर_is_gretap,
	.parms_set = mlxsw_sp_span_entry_gretap4_parms,
	.configure = mlxsw_sp_span_entry_gretap4_configure,
	.deconfigure = mlxsw_sp_span_entry_gretap4_deconfigure,
पूर्ण;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6_GRE)
अटल काष्ठा net_device *
mlxsw_sp_span_gretap6_route(स्थिर काष्ठा net_device *to_dev,
			    काष्ठा in6_addr *saddrp,
			    काष्ठा in6_addr *daddrp)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(to_dev);
	काष्ठा flowi6 fl6 = t->fl.u.ip6;
	काष्ठा net_device *dev = शून्य;
	काष्ठा dst_entry *dst;
	काष्ठा rt6_info *rt6;

	/* We assume "dev" stays valid after dst is released. */
	ASSERT_RTNL();

	fl6.flowi6_mark = t->parms.fwmark;
	अगर (!ip6_tnl_xmit_ctl(t, &fl6.saddr, &fl6.daddr))
		वापस शून्य;

	dst = ip6_route_output(t->net, शून्य, &fl6);
	अगर (!dst || dst->error)
		जाओ out;

	rt6 = container_of(dst, काष्ठा rt6_info, dst);

	dev = dst->dev;
	*saddrp = fl6.saddr;
	*daddrp = rt6->rt6i_gateway;

out:
	dst_release(dst);
	वापस dev;
पूर्ण

अटल पूर्णांक
mlxsw_sp_span_entry_gretap6_parms(काष्ठा mlxsw_sp *mlxsw_sp,
				  स्थिर काष्ठा net_device *to_dev,
				  काष्ठा mlxsw_sp_span_parms *sparmsp)
अणु
	काष्ठा __ip6_tnl_parm tparm = mlxsw_sp_ipip_netdev_parms6(to_dev);
	bool inherit_tos = tparm.flags & IP6_TNL_F_USE_ORIG_TCLASS;
	जोड़ mlxsw_sp_l3addr saddr = अणु .addr6 = tparm.laddr पूर्ण;
	जोड़ mlxsw_sp_l3addr daddr = अणु .addr6 = tparm.raddr पूर्ण;
	bool inherit_ttl = !tparm.hop_limit;
	जोड़ mlxsw_sp_l3addr gw = daddr;
	काष्ठा net_device *l3edev;

	अगर (!(to_dev->flags & IFF_UP) ||
	    /* Reject tunnels with GRE keys, checksums, etc. */
	    tparm.i_flags || tparm.o_flags ||
	    /* Require a fixed TTL and a TOS copied from the mirrored packet. */
	    inherit_ttl || !inherit_tos ||
	    /* A destination address may not be "any". */
	    mlxsw_sp_l3addr_is_zero(daddr))
		वापस mlxsw_sp_span_entry_unoffloadable(sparmsp);

	l3edev = mlxsw_sp_span_gretap6_route(to_dev, &saddr.addr6, &gw.addr6);
	वापस mlxsw_sp_span_entry_tunnel_parms_common(l3edev, saddr, daddr, gw,
						       tparm.hop_limit,
						       &nd_tbl, sparmsp);
पूर्ण

अटल पूर्णांक
mlxsw_sp_span_entry_gretap6_configure(काष्ठा mlxsw_sp_span_entry *span_entry,
				      काष्ठा mlxsw_sp_span_parms sparms)
अणु
	काष्ठा mlxsw_sp_port *dest_port = sparms.dest_port;
	काष्ठा mlxsw_sp *mlxsw_sp = dest_port->mlxsw_sp;
	u8 local_port = dest_port->local_port;
	अक्षर mpat_pl[MLXSW_REG_MPAT_LEN];
	पूर्णांक pa_id = span_entry->id;

	/* Create a new port analayzer entry क्रम local_port. */
	mlxsw_reg_mpat_pack(mpat_pl, pa_id, local_port, true,
			    MLXSW_REG_MPAT_SPAN_TYPE_REMOTE_ETH_L3);
	mlxsw_reg_mpat_pide_set(mpat_pl, sparms.policer_enable);
	mlxsw_reg_mpat_pid_set(mpat_pl, sparms.policer_id);
	mlxsw_reg_mpat_eth_rspan_pack(mpat_pl, sparms.vid);
	mlxsw_reg_mpat_eth_rspan_l2_pack(mpat_pl,
				    MLXSW_REG_MPAT_ETH_RSPAN_VERSION_NO_HEADER,
				    sparms.dmac, !!sparms.vid);
	mlxsw_reg_mpat_eth_rspan_l3_ipv6_pack(mpat_pl, sparms.ttl, sparms.smac,
					      sparms.saddr.addr6,
					      sparms.daddr.addr6);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(mpat), mpat_pl);
पूर्ण

अटल व्योम
mlxsw_sp_span_entry_gretap6_deconfigure(काष्ठा mlxsw_sp_span_entry *span_entry)
अणु
	mlxsw_sp_span_entry_deconfigure_common(span_entry,
					MLXSW_REG_MPAT_SPAN_TYPE_REMOTE_ETH_L3);
पूर्ण

अटल स्थिर
काष्ठा mlxsw_sp_span_entry_ops mlxsw_sp_span_entry_ops_gretap6 = अणु
	.can_handle = netअगर_is_ip6gretap,
	.parms_set = mlxsw_sp_span_entry_gretap6_parms,
	.configure = mlxsw_sp_span_entry_gretap6_configure,
	.deconfigure = mlxsw_sp_span_entry_gretap6_deconfigure,
पूर्ण;
#पूर्ण_अगर

अटल bool
mlxsw_sp_span_vlan_can_handle(स्थिर काष्ठा net_device *dev)
अणु
	वापस is_vlan_dev(dev) &&
	       mlxsw_sp_port_dev_check(vlan_dev_real_dev(dev));
पूर्ण

अटल पूर्णांक
mlxsw_sp_span_entry_vlan_parms(काष्ठा mlxsw_sp *mlxsw_sp,
			       स्थिर काष्ठा net_device *to_dev,
			       काष्ठा mlxsw_sp_span_parms *sparmsp)
अणु
	काष्ठा net_device *real_dev;
	u16 vid;

	अगर (!(to_dev->flags & IFF_UP))
		वापस mlxsw_sp_span_entry_unoffloadable(sparmsp);

	real_dev = mlxsw_sp_span_entry_vlan(to_dev, &vid);
	sparmsp->dest_port = netdev_priv(real_dev);
	sparmsp->vid = vid;
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_span_entry_vlan_configure(काष्ठा mlxsw_sp_span_entry *span_entry,
				   काष्ठा mlxsw_sp_span_parms sparms)
अणु
	काष्ठा mlxsw_sp_port *dest_port = sparms.dest_port;
	काष्ठा mlxsw_sp *mlxsw_sp = dest_port->mlxsw_sp;
	u8 local_port = dest_port->local_port;
	अक्षर mpat_pl[MLXSW_REG_MPAT_LEN];
	पूर्णांक pa_id = span_entry->id;

	mlxsw_reg_mpat_pack(mpat_pl, pa_id, local_port, true,
			    MLXSW_REG_MPAT_SPAN_TYPE_REMOTE_ETH);
	mlxsw_reg_mpat_pide_set(mpat_pl, sparms.policer_enable);
	mlxsw_reg_mpat_pid_set(mpat_pl, sparms.policer_id);
	mlxsw_reg_mpat_eth_rspan_pack(mpat_pl, sparms.vid);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(mpat), mpat_pl);
पूर्ण

अटल व्योम
mlxsw_sp_span_entry_vlan_deconfigure(काष्ठा mlxsw_sp_span_entry *span_entry)
अणु
	mlxsw_sp_span_entry_deconfigure_common(span_entry,
					MLXSW_REG_MPAT_SPAN_TYPE_REMOTE_ETH);
पूर्ण

अटल स्थिर
काष्ठा mlxsw_sp_span_entry_ops mlxsw_sp_span_entry_ops_vlan = अणु
	.can_handle = mlxsw_sp_span_vlan_can_handle,
	.parms_set = mlxsw_sp_span_entry_vlan_parms,
	.configure = mlxsw_sp_span_entry_vlan_configure,
	.deconfigure = mlxsw_sp_span_entry_vlan_deconfigure,
पूर्ण;

अटल स्थिर
काष्ठा mlxsw_sp_span_entry_ops *mlxsw_sp1_span_entry_ops_arr[] = अणु
	&mlxsw_sp1_span_entry_ops_cpu,
	&mlxsw_sp_span_entry_ops_phys,
#अगर IS_ENABLED(CONFIG_NET_IPGRE)
	&mlxsw_sp_span_entry_ops_gretap4,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IPV6_GRE)
	&mlxsw_sp_span_entry_ops_gretap6,
#पूर्ण_अगर
	&mlxsw_sp_span_entry_ops_vlan,
पूर्ण;

अटल bool mlxsw_sp2_span_cpu_can_handle(स्थिर काष्ठा net_device *dev)
अणु
	वापस !dev;
पूर्ण

अटल पूर्णांक mlxsw_sp2_span_entry_cpu_parms(काष्ठा mlxsw_sp *mlxsw_sp,
					  स्थिर काष्ठा net_device *to_dev,
					  काष्ठा mlxsw_sp_span_parms *sparmsp)
अणु
	sparmsp->dest_port = mlxsw_sp->ports[MLXSW_PORT_CPU_PORT];
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp2_span_entry_cpu_configure(काष्ठा mlxsw_sp_span_entry *span_entry,
				   काष्ठा mlxsw_sp_span_parms sparms)
अणु
	/* Mirroring to the CPU port is like mirroring to any other physical
	 * port. Its local port is used instead of that of the physical port.
	 */
	वापस mlxsw_sp_span_entry_phys_configure(span_entry, sparms);
पूर्ण

अटल व्योम
mlxsw_sp2_span_entry_cpu_deconfigure(काष्ठा mlxsw_sp_span_entry *span_entry)
अणु
	क्रमागत mlxsw_reg_mpat_span_type span_type;

	span_type = MLXSW_REG_MPAT_SPAN_TYPE_LOCAL_ETH;
	mlxsw_sp_span_entry_deconfigure_common(span_entry, span_type);
पूर्ण

अटल स्थिर
काष्ठा mlxsw_sp_span_entry_ops mlxsw_sp2_span_entry_ops_cpu = अणु
	.is_अटल = true,
	.can_handle = mlxsw_sp2_span_cpu_can_handle,
	.parms_set = mlxsw_sp2_span_entry_cpu_parms,
	.configure = mlxsw_sp2_span_entry_cpu_configure,
	.deconfigure = mlxsw_sp2_span_entry_cpu_deconfigure,
पूर्ण;

अटल स्थिर
काष्ठा mlxsw_sp_span_entry_ops *mlxsw_sp2_span_entry_ops_arr[] = अणु
	&mlxsw_sp2_span_entry_ops_cpu,
	&mlxsw_sp_span_entry_ops_phys,
#अगर IS_ENABLED(CONFIG_NET_IPGRE)
	&mlxsw_sp_span_entry_ops_gretap4,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IPV6_GRE)
	&mlxsw_sp_span_entry_ops_gretap6,
#पूर्ण_अगर
	&mlxsw_sp_span_entry_ops_vlan,
पूर्ण;

अटल पूर्णांक
mlxsw_sp_span_entry_nop_parms(काष्ठा mlxsw_sp *mlxsw_sp,
			      स्थिर काष्ठा net_device *to_dev,
			      काष्ठा mlxsw_sp_span_parms *sparmsp)
अणु
	वापस mlxsw_sp_span_entry_unoffloadable(sparmsp);
पूर्ण

अटल पूर्णांक
mlxsw_sp_span_entry_nop_configure(काष्ठा mlxsw_sp_span_entry *span_entry,
				  काष्ठा mlxsw_sp_span_parms sparms)
अणु
	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_span_entry_nop_deconfigure(काष्ठा mlxsw_sp_span_entry *span_entry)
अणु
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_span_entry_ops mlxsw_sp_span_entry_ops_nop = अणु
	.parms_set = mlxsw_sp_span_entry_nop_parms,
	.configure = mlxsw_sp_span_entry_nop_configure,
	.deconfigure = mlxsw_sp_span_entry_nop_deconfigure,
पूर्ण;

अटल व्योम
mlxsw_sp_span_entry_configure(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_span_entry *span_entry,
			      काष्ठा mlxsw_sp_span_parms sparms)
अणु
	पूर्णांक err;

	अगर (!sparms.dest_port)
		जाओ set_parms;

	अगर (sparms.dest_port->mlxsw_sp != mlxsw_sp) अणु
		dev_err(mlxsw_sp->bus_info->dev,
			"Cannot mirror to a port which belongs to a different mlxsw instance\n");
		sparms.dest_port = शून्य;
		जाओ set_parms;
	पूर्ण

	err = span_entry->ops->configure(span_entry, sparms);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to offload mirror\n");
		sparms.dest_port = शून्य;
		जाओ set_parms;
	पूर्ण

set_parms:
	span_entry->parms = sparms;
पूर्ण

अटल व्योम
mlxsw_sp_span_entry_deconfigure(काष्ठा mlxsw_sp_span_entry *span_entry)
अणु
	अगर (span_entry->parms.dest_port)
		span_entry->ops->deconfigure(span_entry);
पूर्ण

अटल पूर्णांक mlxsw_sp_span_policer_id_base_set(काष्ठा mlxsw_sp_span *span,
					     u16 policer_id)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = span->mlxsw_sp;
	u16 policer_id_base;
	पूर्णांक err;

	/* Policers set on SPAN agents must be in the range of
	 * `policer_id_base .. policer_id_base + max_span_agents - 1`. If the
	 * base is set and the new policer is not within the range, then we
	 * must error out.
	 */
	अगर (refcount_पढ़ो(&span->policer_id_base_ref_count)) अणु
		अगर (policer_id < span->policer_id_base ||
		    policer_id >= span->policer_id_base + span->entries_count)
			वापस -EINVAL;

		refcount_inc(&span->policer_id_base_ref_count);
		वापस 0;
	पूर्ण

	/* Base must be even. */
	policer_id_base = policer_id % 2 == 0 ? policer_id : policer_id - 1;
	err = mlxsw_sp->span_ops->policer_id_base_set(mlxsw_sp,
						      policer_id_base);
	अगर (err)
		वापस err;

	span->policer_id_base = policer_id_base;
	refcount_set(&span->policer_id_base_ref_count, 1);

	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_span_policer_id_base_unset(काष्ठा mlxsw_sp_span *span)
अणु
	अगर (refcount_dec_and_test(&span->policer_id_base_ref_count))
		span->policer_id_base = 0;
पूर्ण

अटल काष्ठा mlxsw_sp_span_entry *
mlxsw_sp_span_entry_create(काष्ठा mlxsw_sp *mlxsw_sp,
			   स्थिर काष्ठा net_device *to_dev,
			   स्थिर काष्ठा mlxsw_sp_span_entry_ops *ops,
			   काष्ठा mlxsw_sp_span_parms sparms)
अणु
	काष्ठा mlxsw_sp_span_entry *span_entry = शून्य;
	पूर्णांक i;

	/* find a मुक्त entry to use */
	क्रम (i = 0; i < mlxsw_sp->span->entries_count; i++) अणु
		अगर (!refcount_पढ़ो(&mlxsw_sp->span->entries[i].ref_count)) अणु
			span_entry = &mlxsw_sp->span->entries[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!span_entry)
		वापस शून्य;

	अगर (sparms.policer_enable) अणु
		पूर्णांक err;

		err = mlxsw_sp_span_policer_id_base_set(mlxsw_sp->span,
							sparms.policer_id);
		अगर (err)
			वापस शून्य;
	पूर्ण

	atomic_inc(&mlxsw_sp->span->active_entries_count);
	span_entry->ops = ops;
	refcount_set(&span_entry->ref_count, 1);
	span_entry->to_dev = to_dev;
	mlxsw_sp_span_entry_configure(mlxsw_sp, span_entry, sparms);

	वापस span_entry;
पूर्ण

अटल व्योम mlxsw_sp_span_entry_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_span_entry *span_entry)
अणु
	mlxsw_sp_span_entry_deconfigure(span_entry);
	atomic_dec(&mlxsw_sp->span->active_entries_count);
	अगर (span_entry->parms.policer_enable)
		mlxsw_sp_span_policer_id_base_unset(mlxsw_sp->span);
पूर्ण

काष्ठा mlxsw_sp_span_entry *
mlxsw_sp_span_entry_find_by_port(काष्ठा mlxsw_sp *mlxsw_sp,
				 स्थिर काष्ठा net_device *to_dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mlxsw_sp->span->entries_count; i++) अणु
		काष्ठा mlxsw_sp_span_entry *curr = &mlxsw_sp->span->entries[i];

		अगर (refcount_पढ़ो(&curr->ref_count) && curr->to_dev == to_dev)
			वापस curr;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम mlxsw_sp_span_entry_invalidate(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_span_entry *span_entry)
अणु
	mlxsw_sp_span_entry_deconfigure(span_entry);
	span_entry->ops = &mlxsw_sp_span_entry_ops_nop;
पूर्ण

अटल काष्ठा mlxsw_sp_span_entry *
mlxsw_sp_span_entry_find_by_id(काष्ठा mlxsw_sp *mlxsw_sp, पूर्णांक span_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mlxsw_sp->span->entries_count; i++) अणु
		काष्ठा mlxsw_sp_span_entry *curr = &mlxsw_sp->span->entries[i];

		अगर (refcount_पढ़ो(&curr->ref_count) && curr->id == span_id)
			वापस curr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mlxsw_sp_span_entry *
mlxsw_sp_span_entry_find_by_parms(काष्ठा mlxsw_sp *mlxsw_sp,
				  स्थिर काष्ठा net_device *to_dev,
				  स्थिर काष्ठा mlxsw_sp_span_parms *sparms)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mlxsw_sp->span->entries_count; i++) अणु
		काष्ठा mlxsw_sp_span_entry *curr = &mlxsw_sp->span->entries[i];

		अगर (refcount_पढ़ो(&curr->ref_count) && curr->to_dev == to_dev &&
		    curr->parms.policer_enable == sparms->policer_enable &&
		    curr->parms.policer_id == sparms->policer_id &&
		    curr->parms.session_id == sparms->session_id)
			वापस curr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mlxsw_sp_span_entry *
mlxsw_sp_span_entry_get(काष्ठा mlxsw_sp *mlxsw_sp,
			स्थिर काष्ठा net_device *to_dev,
			स्थिर काष्ठा mlxsw_sp_span_entry_ops *ops,
			काष्ठा mlxsw_sp_span_parms sparms)
अणु
	काष्ठा mlxsw_sp_span_entry *span_entry;

	span_entry = mlxsw_sp_span_entry_find_by_parms(mlxsw_sp, to_dev,
						       &sparms);
	अगर (span_entry) अणु
		/* Alपढ़ोy exists, just take a reference */
		refcount_inc(&span_entry->ref_count);
		वापस span_entry;
	पूर्ण

	वापस mlxsw_sp_span_entry_create(mlxsw_sp, to_dev, ops, sparms);
पूर्ण

अटल पूर्णांक mlxsw_sp_span_entry_put(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_span_entry *span_entry)
अणु
	अगर (refcount_dec_and_test(&span_entry->ref_count))
		mlxsw_sp_span_entry_destroy(mlxsw_sp, span_entry);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_span_port_buffer_update(काष्ठा mlxsw_sp_port *mlxsw_sp_port, bool enable)
अणु
	काष्ठा mlxsw_sp_hdroom hdroom;

	hdroom = *mlxsw_sp_port->hdroom;
	hdroom.पूर्णांक_buf.enable = enable;
	mlxsw_sp_hdroom_bufs_reset_sizes(mlxsw_sp_port, &hdroom);

	वापस mlxsw_sp_hdroom_configure(mlxsw_sp_port, &hdroom);
पूर्ण

अटल पूर्णांक
mlxsw_sp_span_port_buffer_enable(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	वापस mlxsw_sp_span_port_buffer_update(mlxsw_sp_port, true);
पूर्ण

अटल व्योम mlxsw_sp_span_port_buffer_disable(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	mlxsw_sp_span_port_buffer_update(mlxsw_sp_port, false);
पूर्ण

अटल काष्ठा mlxsw_sp_span_analyzed_port *
mlxsw_sp_span_analyzed_port_find(काष्ठा mlxsw_sp_span *span, u8 local_port,
				 bool ingress)
अणु
	काष्ठा mlxsw_sp_span_analyzed_port *analyzed_port;

	list_क्रम_each_entry(analyzed_port, &span->analyzed_ports_list, list) अणु
		अगर (analyzed_port->local_port == local_port &&
		    analyzed_port->ingress == ingress)
			वापस analyzed_port;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_span_entry_ops *
mlxsw_sp_span_entry_ops(काष्ठा mlxsw_sp *mlxsw_sp,
			स्थिर काष्ठा net_device *to_dev)
अणु
	काष्ठा mlxsw_sp_span *span = mlxsw_sp->span;
	माप_प्रकार i;

	क्रम (i = 0; i < span->span_entry_ops_arr_size; ++i)
		अगर (span->span_entry_ops_arr[i]->can_handle(to_dev))
			वापस span->span_entry_ops_arr[i];

	वापस शून्य;
पूर्ण

अटल व्योम mlxsw_sp_span_respin_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_sp_span *span;
	काष्ठा mlxsw_sp *mlxsw_sp;
	पूर्णांक i, err;

	span = container_of(work, काष्ठा mlxsw_sp_span, work);
	mlxsw_sp = span->mlxsw_sp;

	rtnl_lock();
	क्रम (i = 0; i < mlxsw_sp->span->entries_count; i++) अणु
		काष्ठा mlxsw_sp_span_entry *curr = &mlxsw_sp->span->entries[i];
		काष्ठा mlxsw_sp_span_parms sparms = अणुशून्यपूर्ण;

		अगर (!refcount_पढ़ो(&curr->ref_count))
			जारी;

		अगर (curr->ops->is_अटल)
			जारी;

		err = curr->ops->parms_set(mlxsw_sp, curr->to_dev, &sparms);
		अगर (err)
			जारी;

		अगर (स_भेद(&sparms, &curr->parms, माप(sparms))) अणु
			mlxsw_sp_span_entry_deconfigure(curr);
			mlxsw_sp_span_entry_configure(mlxsw_sp, curr, sparms);
		पूर्ण
	पूर्ण
	rtnl_unlock();
पूर्ण

व्योम mlxsw_sp_span_respin(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अगर (atomic_पढ़ो(&mlxsw_sp->span->active_entries_count) == 0)
		वापस;
	mlxsw_core_schedule_work(&mlxsw_sp->span->work);
पूर्ण

पूर्णांक mlxsw_sp_span_agent_get(काष्ठा mlxsw_sp *mlxsw_sp, पूर्णांक *p_span_id,
			    स्थिर काष्ठा mlxsw_sp_span_agent_parms *parms)
अणु
	स्थिर काष्ठा net_device *to_dev = parms->to_dev;
	स्थिर काष्ठा mlxsw_sp_span_entry_ops *ops;
	काष्ठा mlxsw_sp_span_entry *span_entry;
	काष्ठा mlxsw_sp_span_parms sparms;
	पूर्णांक err;

	ASSERT_RTNL();

	ops = mlxsw_sp_span_entry_ops(mlxsw_sp, to_dev);
	अगर (!ops) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Cannot mirror to requested destination\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	स_रखो(&sparms, 0, माप(sparms));
	err = ops->parms_set(mlxsw_sp, to_dev, &sparms);
	अगर (err)
		वापस err;

	sparms.policer_id = parms->policer_id;
	sparms.policer_enable = parms->policer_enable;
	sparms.session_id = parms->session_id;
	span_entry = mlxsw_sp_span_entry_get(mlxsw_sp, to_dev, ops, sparms);
	अगर (!span_entry)
		वापस -ENOBUFS;

	*p_span_id = span_entry->id;

	वापस 0;
पूर्ण

व्योम mlxsw_sp_span_agent_put(काष्ठा mlxsw_sp *mlxsw_sp, पूर्णांक span_id)
अणु
	काष्ठा mlxsw_sp_span_entry *span_entry;

	ASSERT_RTNL();

	span_entry = mlxsw_sp_span_entry_find_by_id(mlxsw_sp, span_id);
	अगर (WARN_ON_ONCE(!span_entry))
		वापस;

	mlxsw_sp_span_entry_put(mlxsw_sp, span_entry);
पूर्ण

अटल काष्ठा mlxsw_sp_span_analyzed_port *
mlxsw_sp_span_analyzed_port_create(काष्ठा mlxsw_sp_span *span,
				   काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   bool ingress)
अणु
	काष्ठा mlxsw_sp_span_analyzed_port *analyzed_port;
	पूर्णांक err;

	analyzed_port = kzalloc(माप(*analyzed_port), GFP_KERNEL);
	अगर (!analyzed_port)
		वापस ERR_PTR(-ENOMEM);

	refcount_set(&analyzed_port->ref_count, 1);
	analyzed_port->local_port = mlxsw_sp_port->local_port;
	analyzed_port->ingress = ingress;
	list_add_tail(&analyzed_port->list, &span->analyzed_ports_list);

	/* An egress mirror buffer should be allocated on the egress port which
	 * करोes the mirroring.
	 */
	अगर (!ingress) अणु
		err = mlxsw_sp_span_port_buffer_enable(mlxsw_sp_port);
		अगर (err)
			जाओ err_buffer_update;
	पूर्ण

	वापस analyzed_port;

err_buffer_update:
	list_del(&analyzed_port->list);
	kमुक्त(analyzed_port);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_span_analyzed_port_destroy(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				    काष्ठा mlxsw_sp_span_analyzed_port *
				    analyzed_port)
अणु
	/* Remove egress mirror buffer now that port is no दीर्घer analyzed
	 * at egress.
	 */
	अगर (!analyzed_port->ingress)
		mlxsw_sp_span_port_buffer_disable(mlxsw_sp_port);

	list_del(&analyzed_port->list);
	kमुक्त(analyzed_port);
पूर्ण

पूर्णांक mlxsw_sp_span_analyzed_port_get(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				    bool ingress)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_span_analyzed_port *analyzed_port;
	u8 local_port = mlxsw_sp_port->local_port;
	पूर्णांक err = 0;

	mutex_lock(&mlxsw_sp->span->analyzed_ports_lock);

	analyzed_port = mlxsw_sp_span_analyzed_port_find(mlxsw_sp->span,
							 local_port, ingress);
	अगर (analyzed_port) अणु
		refcount_inc(&analyzed_port->ref_count);
		जाओ out_unlock;
	पूर्ण

	analyzed_port = mlxsw_sp_span_analyzed_port_create(mlxsw_sp->span,
							   mlxsw_sp_port,
							   ingress);
	अगर (IS_ERR(analyzed_port))
		err = PTR_ERR(analyzed_port);

out_unlock:
	mutex_unlock(&mlxsw_sp->span->analyzed_ports_lock);
	वापस err;
पूर्ण

व्योम mlxsw_sp_span_analyzed_port_put(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				     bool ingress)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_span_analyzed_port *analyzed_port;
	u8 local_port = mlxsw_sp_port->local_port;

	mutex_lock(&mlxsw_sp->span->analyzed_ports_lock);

	analyzed_port = mlxsw_sp_span_analyzed_port_find(mlxsw_sp->span,
							 local_port, ingress);
	अगर (WARN_ON_ONCE(!analyzed_port))
		जाओ out_unlock;

	अगर (!refcount_dec_and_test(&analyzed_port->ref_count))
		जाओ out_unlock;

	mlxsw_sp_span_analyzed_port_destroy(mlxsw_sp_port, analyzed_port);

out_unlock:
	mutex_unlock(&mlxsw_sp->span->analyzed_ports_lock);
पूर्ण

अटल पूर्णांक
__mlxsw_sp_span_trigger_port_bind(काष्ठा mlxsw_sp_span *span,
				  काष्ठा mlxsw_sp_span_trigger_entry *
				  trigger_entry, bool enable)
अणु
	अक्षर mpar_pl[MLXSW_REG_MPAR_LEN];
	क्रमागत mlxsw_reg_mpar_i_e i_e;

	चयन (trigger_entry->trigger) अणु
	हाल MLXSW_SP_SPAN_TRIGGER_INGRESS:
		i_e = MLXSW_REG_MPAR_TYPE_INGRESS;
		अवरोध;
	हाल MLXSW_SP_SPAN_TRIGGER_EGRESS:
		i_e = MLXSW_REG_MPAR_TYPE_EGRESS;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस -EINVAL;
	पूर्ण

	अगर (trigger_entry->parms.probability_rate > MLXSW_REG_MPAR_RATE_MAX)
		वापस -EINVAL;

	mlxsw_reg_mpar_pack(mpar_pl, trigger_entry->local_port, i_e, enable,
			    trigger_entry->parms.span_id,
			    trigger_entry->parms.probability_rate);
	वापस mlxsw_reg_ग_लिखो(span->mlxsw_sp->core, MLXSW_REG(mpar), mpar_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_span_trigger_port_bind(काष्ठा mlxsw_sp_span_trigger_entry *
				trigger_entry)
अणु
	वापस __mlxsw_sp_span_trigger_port_bind(trigger_entry->span,
						 trigger_entry, true);
पूर्ण

अटल व्योम
mlxsw_sp_span_trigger_port_unbind(काष्ठा mlxsw_sp_span_trigger_entry *
				  trigger_entry)
अणु
	__mlxsw_sp_span_trigger_port_bind(trigger_entry->span, trigger_entry,
					  false);
पूर्ण

अटल bool
mlxsw_sp_span_trigger_port_matches(काष्ठा mlxsw_sp_span_trigger_entry *
				   trigger_entry,
				   क्रमागत mlxsw_sp_span_trigger trigger,
				   काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	वापस trigger_entry->trigger == trigger &&
	       trigger_entry->local_port == mlxsw_sp_port->local_port;
पूर्ण

अटल पूर्णांक
mlxsw_sp_span_trigger_port_enable(काष्ठा mlxsw_sp_span_trigger_entry *
				  trigger_entry,
				  काष्ठा mlxsw_sp_port *mlxsw_sp_port, u8 tc)
अणु
	/* Port trigger are enabled during binding. */
	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_span_trigger_port_disable(काष्ठा mlxsw_sp_span_trigger_entry *
				   trigger_entry,
				   काष्ठा mlxsw_sp_port *mlxsw_sp_port, u8 tc)
अणु
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_span_trigger_ops
mlxsw_sp_span_trigger_port_ops = अणु
	.bind = mlxsw_sp_span_trigger_port_bind,
	.unbind = mlxsw_sp_span_trigger_port_unbind,
	.matches = mlxsw_sp_span_trigger_port_matches,
	.enable = mlxsw_sp_span_trigger_port_enable,
	.disable = mlxsw_sp_span_trigger_port_disable,
पूर्ण;

अटल पूर्णांक
mlxsw_sp1_span_trigger_global_bind(काष्ठा mlxsw_sp_span_trigger_entry *
				   trigger_entry)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम
mlxsw_sp1_span_trigger_global_unbind(काष्ठा mlxsw_sp_span_trigger_entry *
				     trigger_entry)
अणु
पूर्ण

अटल bool
mlxsw_sp1_span_trigger_global_matches(काष्ठा mlxsw_sp_span_trigger_entry *
				      trigger_entry,
				      क्रमागत mlxsw_sp_span_trigger trigger,
				      काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	WARN_ON_ONCE(1);
	वापस false;
पूर्ण

अटल पूर्णांक
mlxsw_sp1_span_trigger_global_enable(काष्ठा mlxsw_sp_span_trigger_entry *
				     trigger_entry,
				     काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				     u8 tc)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम
mlxsw_sp1_span_trigger_global_disable(काष्ठा mlxsw_sp_span_trigger_entry *
				      trigger_entry,
				      काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				      u8 tc)
अणु
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_span_trigger_ops
mlxsw_sp1_span_trigger_global_ops = अणु
	.bind = mlxsw_sp1_span_trigger_global_bind,
	.unbind = mlxsw_sp1_span_trigger_global_unbind,
	.matches = mlxsw_sp1_span_trigger_global_matches,
	.enable = mlxsw_sp1_span_trigger_global_enable,
	.disable = mlxsw_sp1_span_trigger_global_disable,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_span_trigger_ops *
mlxsw_sp1_span_trigger_ops_arr[] = अणु
	[MLXSW_SP_SPAN_TRIGGER_TYPE_PORT] = &mlxsw_sp_span_trigger_port_ops,
	[MLXSW_SP_SPAN_TRIGGER_TYPE_GLOBAL] =
		&mlxsw_sp1_span_trigger_global_ops,
पूर्ण;

अटल पूर्णांक
mlxsw_sp2_span_trigger_global_bind(काष्ठा mlxsw_sp_span_trigger_entry *
				   trigger_entry)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = trigger_entry->span->mlxsw_sp;
	क्रमागत mlxsw_reg_mpagr_trigger trigger;
	अक्षर mpagr_pl[MLXSW_REG_MPAGR_LEN];

	चयन (trigger_entry->trigger) अणु
	हाल MLXSW_SP_SPAN_TRIGGER_TAIL_DROP:
		trigger = MLXSW_REG_MPAGR_TRIGGER_INGRESS_SHARED_BUFFER;
		अवरोध;
	हाल MLXSW_SP_SPAN_TRIGGER_EARLY_DROP:
		trigger = MLXSW_REG_MPAGR_TRIGGER_INGRESS_WRED;
		अवरोध;
	हाल MLXSW_SP_SPAN_TRIGGER_ECN:
		trigger = MLXSW_REG_MPAGR_TRIGGER_EGRESS_ECN;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस -EINVAL;
	पूर्ण

	अगर (trigger_entry->parms.probability_rate > MLXSW_REG_MPAGR_RATE_MAX)
		वापस -EINVAL;

	mlxsw_reg_mpagr_pack(mpagr_pl, trigger, trigger_entry->parms.span_id,
			     trigger_entry->parms.probability_rate);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(mpagr), mpagr_pl);
पूर्ण

अटल व्योम
mlxsw_sp2_span_trigger_global_unbind(काष्ठा mlxsw_sp_span_trigger_entry *
				     trigger_entry)
अणु
	/* There is no unbinding क्रम global triggers. The trigger should be
	 * disabled on all ports by now.
	 */
पूर्ण

अटल bool
mlxsw_sp2_span_trigger_global_matches(काष्ठा mlxsw_sp_span_trigger_entry *
				      trigger_entry,
				      क्रमागत mlxsw_sp_span_trigger trigger,
				      काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	वापस trigger_entry->trigger == trigger;
पूर्ण

अटल पूर्णांक
__mlxsw_sp2_span_trigger_global_enable(काष्ठा mlxsw_sp_span_trigger_entry *
				       trigger_entry,
				       काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				       u8 tc, bool enable)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = trigger_entry->span->mlxsw_sp;
	अक्षर momte_pl[MLXSW_REG_MOMTE_LEN];
	क्रमागत mlxsw_reg_momte_type type;
	पूर्णांक err;

	चयन (trigger_entry->trigger) अणु
	हाल MLXSW_SP_SPAN_TRIGGER_TAIL_DROP:
		type = MLXSW_REG_MOMTE_TYPE_SHARED_BUFFER_TCLASS;
		अवरोध;
	हाल MLXSW_SP_SPAN_TRIGGER_EARLY_DROP:
		type = MLXSW_REG_MOMTE_TYPE_WRED;
		अवरोध;
	हाल MLXSW_SP_SPAN_TRIGGER_ECN:
		type = MLXSW_REG_MOMTE_TYPE_ECN;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस -EINVAL;
	पूर्ण

	/* Query existing configuration in order to only change the state of
	 * the specअगरied traffic class.
	 */
	mlxsw_reg_momte_pack(momte_pl, mlxsw_sp_port->local_port, type);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(momte), momte_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_momte_tclass_en_set(momte_pl, tc, enable);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(momte), momte_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp2_span_trigger_global_enable(काष्ठा mlxsw_sp_span_trigger_entry *
				     trigger_entry,
				     काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				     u8 tc)
अणु
	वापस __mlxsw_sp2_span_trigger_global_enable(trigger_entry,
						      mlxsw_sp_port, tc, true);
पूर्ण

अटल व्योम
mlxsw_sp2_span_trigger_global_disable(काष्ठा mlxsw_sp_span_trigger_entry *
				      trigger_entry,
				      काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				      u8 tc)
अणु
	__mlxsw_sp2_span_trigger_global_enable(trigger_entry, mlxsw_sp_port, tc,
					       false);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_span_trigger_ops
mlxsw_sp2_span_trigger_global_ops = अणु
	.bind = mlxsw_sp2_span_trigger_global_bind,
	.unbind = mlxsw_sp2_span_trigger_global_unbind,
	.matches = mlxsw_sp2_span_trigger_global_matches,
	.enable = mlxsw_sp2_span_trigger_global_enable,
	.disable = mlxsw_sp2_span_trigger_global_disable,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_span_trigger_ops *
mlxsw_sp2_span_trigger_ops_arr[] = अणु
	[MLXSW_SP_SPAN_TRIGGER_TYPE_PORT] = &mlxsw_sp_span_trigger_port_ops,
	[MLXSW_SP_SPAN_TRIGGER_TYPE_GLOBAL] =
		&mlxsw_sp2_span_trigger_global_ops,
पूर्ण;

अटल व्योम
mlxsw_sp_span_trigger_ops_set(काष्ठा mlxsw_sp_span_trigger_entry *trigger_entry)
अणु
	काष्ठा mlxsw_sp_span *span = trigger_entry->span;
	क्रमागत mlxsw_sp_span_trigger_type type;

	चयन (trigger_entry->trigger) अणु
	हाल MLXSW_SP_SPAN_TRIGGER_INGRESS:
	हाल MLXSW_SP_SPAN_TRIGGER_EGRESS:
		type = MLXSW_SP_SPAN_TRIGGER_TYPE_PORT;
		अवरोध;
	हाल MLXSW_SP_SPAN_TRIGGER_TAIL_DROP:
	हाल MLXSW_SP_SPAN_TRIGGER_EARLY_DROP:
	हाल MLXSW_SP_SPAN_TRIGGER_ECN:
		type = MLXSW_SP_SPAN_TRIGGER_TYPE_GLOBAL;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	trigger_entry->ops = span->span_trigger_ops_arr[type];
पूर्ण

अटल काष्ठा mlxsw_sp_span_trigger_entry *
mlxsw_sp_span_trigger_entry_create(काष्ठा mlxsw_sp_span *span,
				   क्रमागत mlxsw_sp_span_trigger trigger,
				   काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   स्थिर काष्ठा mlxsw_sp_span_trigger_parms
				   *parms)
अणु
	काष्ठा mlxsw_sp_span_trigger_entry *trigger_entry;
	पूर्णांक err;

	trigger_entry = kzalloc(माप(*trigger_entry), GFP_KERNEL);
	अगर (!trigger_entry)
		वापस ERR_PTR(-ENOMEM);

	refcount_set(&trigger_entry->ref_count, 1);
	trigger_entry->local_port = mlxsw_sp_port ? mlxsw_sp_port->local_port :
						    0;
	trigger_entry->trigger = trigger;
	स_नकल(&trigger_entry->parms, parms, माप(trigger_entry->parms));
	trigger_entry->span = span;
	mlxsw_sp_span_trigger_ops_set(trigger_entry);
	list_add_tail(&trigger_entry->list, &span->trigger_entries_list);

	err = trigger_entry->ops->bind(trigger_entry);
	अगर (err)
		जाओ err_trigger_entry_bind;

	वापस trigger_entry;

err_trigger_entry_bind:
	list_del(&trigger_entry->list);
	kमुक्त(trigger_entry);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_span_trigger_entry_destroy(काष्ठा mlxsw_sp_span *span,
				    काष्ठा mlxsw_sp_span_trigger_entry *
				    trigger_entry)
अणु
	trigger_entry->ops->unbind(trigger_entry);
	list_del(&trigger_entry->list);
	kमुक्त(trigger_entry);
पूर्ण

अटल काष्ठा mlxsw_sp_span_trigger_entry *
mlxsw_sp_span_trigger_entry_find(काष्ठा mlxsw_sp_span *span,
				 क्रमागत mlxsw_sp_span_trigger trigger,
				 काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp_span_trigger_entry *trigger_entry;

	list_क्रम_each_entry(trigger_entry, &span->trigger_entries_list, list) अणु
		अगर (trigger_entry->ops->matches(trigger_entry, trigger,
						mlxsw_sp_port))
			वापस trigger_entry;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक mlxsw_sp_span_agent_bind(काष्ठा mlxsw_sp *mlxsw_sp,
			     क्रमागत mlxsw_sp_span_trigger trigger,
			     काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			     स्थिर काष्ठा mlxsw_sp_span_trigger_parms *parms)
अणु
	काष्ठा mlxsw_sp_span_trigger_entry *trigger_entry;
	पूर्णांक err = 0;

	ASSERT_RTNL();

	अगर (!mlxsw_sp_span_entry_find_by_id(mlxsw_sp, parms->span_id))
		वापस -EINVAL;

	trigger_entry = mlxsw_sp_span_trigger_entry_find(mlxsw_sp->span,
							 trigger,
							 mlxsw_sp_port);
	अगर (trigger_entry) अणु
		अगर (trigger_entry->parms.span_id != parms->span_id ||
		    trigger_entry->parms.probability_rate !=
		    parms->probability_rate)
			वापस -EINVAL;
		refcount_inc(&trigger_entry->ref_count);
		जाओ out;
	पूर्ण

	trigger_entry = mlxsw_sp_span_trigger_entry_create(mlxsw_sp->span,
							   trigger,
							   mlxsw_sp_port,
							   parms);
	अगर (IS_ERR(trigger_entry))
		err = PTR_ERR(trigger_entry);

out:
	वापस err;
पूर्ण

व्योम mlxsw_sp_span_agent_unbind(काष्ठा mlxsw_sp *mlxsw_sp,
				क्रमागत mlxsw_sp_span_trigger trigger,
				काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				स्थिर काष्ठा mlxsw_sp_span_trigger_parms *parms)
अणु
	काष्ठा mlxsw_sp_span_trigger_entry *trigger_entry;

	ASSERT_RTNL();

	अगर (WARN_ON_ONCE(!mlxsw_sp_span_entry_find_by_id(mlxsw_sp,
							 parms->span_id)))
		वापस;

	trigger_entry = mlxsw_sp_span_trigger_entry_find(mlxsw_sp->span,
							 trigger,
							 mlxsw_sp_port);
	अगर (WARN_ON_ONCE(!trigger_entry))
		वापस;

	अगर (!refcount_dec_and_test(&trigger_entry->ref_count))
		वापस;

	mlxsw_sp_span_trigger_entry_destroy(mlxsw_sp->span, trigger_entry);
पूर्ण

पूर्णांक mlxsw_sp_span_trigger_enable(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				 क्रमागत mlxsw_sp_span_trigger trigger, u8 tc)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_span_trigger_entry *trigger_entry;

	ASSERT_RTNL();

	trigger_entry = mlxsw_sp_span_trigger_entry_find(mlxsw_sp->span,
							 trigger,
							 mlxsw_sp_port);
	अगर (WARN_ON_ONCE(!trigger_entry))
		वापस -EINVAL;

	वापस trigger_entry->ops->enable(trigger_entry, mlxsw_sp_port, tc);
पूर्ण

व्योम mlxsw_sp_span_trigger_disable(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   क्रमागत mlxsw_sp_span_trigger trigger, u8 tc)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_span_trigger_entry *trigger_entry;

	ASSERT_RTNL();

	trigger_entry = mlxsw_sp_span_trigger_entry_find(mlxsw_sp->span,
							 trigger,
							 mlxsw_sp_port);
	अगर (WARN_ON_ONCE(!trigger_entry))
		वापस;

	वापस trigger_entry->ops->disable(trigger_entry, mlxsw_sp_port, tc);
पूर्ण

अटल पूर्णांक mlxsw_sp1_span_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	माप_प्रकार arr_size = ARRAY_SIZE(mlxsw_sp1_span_entry_ops_arr);

	/* Must be first to aव्योम शून्य poपूर्णांकer dereference by subsequent
	 * can_handle() callbacks.
	 */
	अगर (WARN_ON(mlxsw_sp1_span_entry_ops_arr[0] !=
		    &mlxsw_sp1_span_entry_ops_cpu))
		वापस -EINVAL;

	mlxsw_sp->span->span_trigger_ops_arr = mlxsw_sp1_span_trigger_ops_arr;
	mlxsw_sp->span->span_entry_ops_arr = mlxsw_sp1_span_entry_ops_arr;
	mlxsw_sp->span->span_entry_ops_arr_size = arr_size;

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp1_span_policer_id_base_set(काष्ठा mlxsw_sp *mlxsw_sp,
					      u16 policer_id_base)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

स्थिर काष्ठा mlxsw_sp_span_ops mlxsw_sp1_span_ops = अणु
	.init = mlxsw_sp1_span_init,
	.policer_id_base_set = mlxsw_sp1_span_policer_id_base_set,
पूर्ण;

अटल पूर्णांक mlxsw_sp2_span_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	माप_प्रकार arr_size = ARRAY_SIZE(mlxsw_sp2_span_entry_ops_arr);

	/* Must be first to aव्योम शून्य poपूर्णांकer dereference by subsequent
	 * can_handle() callbacks.
	 */
	अगर (WARN_ON(mlxsw_sp2_span_entry_ops_arr[0] !=
		    &mlxsw_sp2_span_entry_ops_cpu))
		वापस -EINVAL;

	mlxsw_sp->span->span_trigger_ops_arr = mlxsw_sp2_span_trigger_ops_arr;
	mlxsw_sp->span->span_entry_ops_arr = mlxsw_sp2_span_entry_ops_arr;
	mlxsw_sp->span->span_entry_ops_arr_size = arr_size;

	वापस 0;
पूर्ण

#घोषणा MLXSW_SP2_SPAN_EG_MIRROR_BUFFER_FACTOR 38
#घोषणा MLXSW_SP3_SPAN_EG_MIRROR_BUFFER_FACTOR 50

अटल पूर्णांक mlxsw_sp2_span_policer_id_base_set(काष्ठा mlxsw_sp *mlxsw_sp,
					      u16 policer_id_base)
अणु
	अक्षर mogcr_pl[MLXSW_REG_MOGCR_LEN];
	पूर्णांक err;

	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(mogcr), mogcr_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_mogcr_mirroring_pid_base_set(mogcr_pl, policer_id_base);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(mogcr), mogcr_pl);
पूर्ण

स्थिर काष्ठा mlxsw_sp_span_ops mlxsw_sp2_span_ops = अणु
	.init = mlxsw_sp2_span_init,
	.policer_id_base_set = mlxsw_sp2_span_policer_id_base_set,
पूर्ण;

स्थिर काष्ठा mlxsw_sp_span_ops mlxsw_sp3_span_ops = अणु
	.init = mlxsw_sp2_span_init,
	.policer_id_base_set = mlxsw_sp2_span_policer_id_base_set,
पूर्ण;
