<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#समावेश <net/ip_tunnels.h>
#समावेश <net/ip6_tunnel.h>
#समावेश <net/inet_ecn.h>

#समावेश "spectrum_ipip.h"
#समावेश "reg.h"

काष्ठा ip_tunnel_parm
mlxsw_sp_ipip_netdev_parms4(स्थिर काष्ठा net_device *ol_dev)
अणु
	काष्ठा ip_tunnel *tun = netdev_priv(ol_dev);

	वापस tun->parms;
पूर्ण

काष्ठा __ip6_tnl_parm
mlxsw_sp_ipip_netdev_parms6(स्थिर काष्ठा net_device *ol_dev)
अणु
	काष्ठा ip6_tnl *tun = netdev_priv(ol_dev);

	वापस tun->parms;
पूर्ण

अटल bool mlxsw_sp_ipip_parms4_has_ikey(काष्ठा ip_tunnel_parm parms)
अणु
	वापस !!(parms.i_flags & TUNNEL_KEY);
पूर्ण

अटल bool mlxsw_sp_ipip_parms4_has_okey(काष्ठा ip_tunnel_parm parms)
अणु
	वापस !!(parms.o_flags & TUNNEL_KEY);
पूर्ण

अटल u32 mlxsw_sp_ipip_parms4_ikey(काष्ठा ip_tunnel_parm parms)
अणु
	वापस mlxsw_sp_ipip_parms4_has_ikey(parms) ?
		be32_to_cpu(parms.i_key) : 0;
पूर्ण

अटल u32 mlxsw_sp_ipip_parms4_okey(काष्ठा ip_tunnel_parm parms)
अणु
	वापस mlxsw_sp_ipip_parms4_has_okey(parms) ?
		be32_to_cpu(parms.o_key) : 0;
पूर्ण

अटल जोड़ mlxsw_sp_l3addr
mlxsw_sp_ipip_parms4_saddr(काष्ठा ip_tunnel_parm parms)
अणु
	वापस (जोड़ mlxsw_sp_l3addr) अणु .addr4 = parms.iph.saddr पूर्ण;
पूर्ण

अटल जोड़ mlxsw_sp_l3addr
mlxsw_sp_ipip_parms6_saddr(काष्ठा __ip6_tnl_parm parms)
अणु
	वापस (जोड़ mlxsw_sp_l3addr) अणु .addr6 = parms.laddr पूर्ण;
पूर्ण

अटल जोड़ mlxsw_sp_l3addr
mlxsw_sp_ipip_parms4_daddr(काष्ठा ip_tunnel_parm parms)
अणु
	वापस (जोड़ mlxsw_sp_l3addr) अणु .addr4 = parms.iph.daddr पूर्ण;
पूर्ण

अटल जोड़ mlxsw_sp_l3addr
mlxsw_sp_ipip_parms6_daddr(काष्ठा __ip6_tnl_parm parms)
अणु
	वापस (जोड़ mlxsw_sp_l3addr) अणु .addr6 = parms.raddr पूर्ण;
पूर्ण

जोड़ mlxsw_sp_l3addr
mlxsw_sp_ipip_netdev_saddr(क्रमागत mlxsw_sp_l3proto proto,
			   स्थिर काष्ठा net_device *ol_dev)
अणु
	काष्ठा ip_tunnel_parm parms4;
	काष्ठा __ip6_tnl_parm parms6;

	चयन (proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		parms4 = mlxsw_sp_ipip_netdev_parms4(ol_dev);
		वापस mlxsw_sp_ipip_parms4_saddr(parms4);
	हाल MLXSW_SP_L3_PROTO_IPV6:
		parms6 = mlxsw_sp_ipip_netdev_parms6(ol_dev);
		वापस mlxsw_sp_ipip_parms6_saddr(parms6);
	पूर्ण

	WARN_ON(1);
	वापस (जोड़ mlxsw_sp_l3addr) अणु0पूर्ण;
पूर्ण

अटल __be32 mlxsw_sp_ipip_netdev_daddr4(स्थिर काष्ठा net_device *ol_dev)
अणु

	काष्ठा ip_tunnel_parm parms4 = mlxsw_sp_ipip_netdev_parms4(ol_dev);

	वापस mlxsw_sp_ipip_parms4_daddr(parms4).addr4;
पूर्ण

अटल जोड़ mlxsw_sp_l3addr
mlxsw_sp_ipip_netdev_daddr(क्रमागत mlxsw_sp_l3proto proto,
			   स्थिर काष्ठा net_device *ol_dev)
अणु
	काष्ठा ip_tunnel_parm parms4;
	काष्ठा __ip6_tnl_parm parms6;

	चयन (proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		parms4 = mlxsw_sp_ipip_netdev_parms4(ol_dev);
		वापस mlxsw_sp_ipip_parms4_daddr(parms4);
	हाल MLXSW_SP_L3_PROTO_IPV6:
		parms6 = mlxsw_sp_ipip_netdev_parms6(ol_dev);
		वापस mlxsw_sp_ipip_parms6_daddr(parms6);
	पूर्ण

	WARN_ON(1);
	वापस (जोड़ mlxsw_sp_l3addr) अणु0पूर्ण;
पूर्ण

bool mlxsw_sp_l3addr_is_zero(जोड़ mlxsw_sp_l3addr addr)
अणु
	जोड़ mlxsw_sp_l3addr naddr = अणु0पूर्ण;

	वापस !स_भेद(&addr, &naddr, माप(naddr));
पूर्ण

अटल पूर्णांक
mlxsw_sp_ipip_nexthop_update_gre4(काष्ठा mlxsw_sp *mlxsw_sp, u32 adj_index,
				  काष्ठा mlxsw_sp_ipip_entry *ipip_entry,
				  bool क्रमce, अक्षर *ratr_pl)
अणु
	u16 rअगर_index = mlxsw_sp_ipip_lb_rअगर_index(ipip_entry->ol_lb);
	__be32 daddr4 = mlxsw_sp_ipip_netdev_daddr4(ipip_entry->ol_dev);
	क्रमागत mlxsw_reg_ratr_op op;

	op = क्रमce ? MLXSW_REG_RATR_OP_WRITE_WRITE_ENTRY :
		     MLXSW_REG_RATR_OP_WRITE_WRITE_ENTRY_ON_ACTIVITY;
	mlxsw_reg_ratr_pack(ratr_pl, op, true, MLXSW_REG_RATR_TYPE_IPIP,
			    adj_index, rअगर_index);
	mlxsw_reg_ratr_ipip4_entry_pack(ratr_pl, be32_to_cpu(daddr4));

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ratr), ratr_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_ipip_decap_config_gre4(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_ipip_entry *ipip_entry,
				u32 tunnel_index)
अणु
	u16 rअगर_index = mlxsw_sp_ipip_lb_rअगर_index(ipip_entry->ol_lb);
	u16 ul_rअगर_id = mlxsw_sp_ipip_lb_ul_rअगर_id(ipip_entry->ol_lb);
	अक्षर rtdp_pl[MLXSW_REG_RTDP_LEN];
	काष्ठा ip_tunnel_parm parms;
	अचिन्हित पूर्णांक type_check;
	bool has_ikey;
	u32 daddr4;
	u32 ikey;

	parms = mlxsw_sp_ipip_netdev_parms4(ipip_entry->ol_dev);
	has_ikey = mlxsw_sp_ipip_parms4_has_ikey(parms);
	ikey = mlxsw_sp_ipip_parms4_ikey(parms);

	mlxsw_reg_rtdp_pack(rtdp_pl, MLXSW_REG_RTDP_TYPE_IPIP, tunnel_index);
	mlxsw_reg_rtdp_egress_router_पूर्णांकerface_set(rtdp_pl, ul_rअगर_id);

	type_check = has_ikey ?
		MLXSW_REG_RTDP_IPIP_TYPE_CHECK_ALLOW_GRE_KEY :
		MLXSW_REG_RTDP_IPIP_TYPE_CHECK_ALLOW_GRE;

	/* Linux demuxes tunnels based on packet SIP (which must match tunnel
	 * remote IP). Thus configure decap so that it filters out packets that
	 * are not IPv4 or have the wrong SIP. IPIP_DECAP_ERROR trap is
	 * generated क्रम packets that fail this criterion. Linux then handles
	 * such packets in slow path and generates ICMP destination unreachable.
	 */
	daddr4 = be32_to_cpu(mlxsw_sp_ipip_netdev_daddr4(ipip_entry->ol_dev));
	mlxsw_reg_rtdp_ipip4_pack(rtdp_pl, rअगर_index,
				  MLXSW_REG_RTDP_IPIP_SIP_CHECK_FILTER_IPV4,
				  type_check, has_ikey, daddr4, ikey);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rtdp), rtdp_pl);
पूर्ण

अटल bool mlxsw_sp_ipip_tunnel_complete(क्रमागत mlxsw_sp_l3proto proto,
					  स्थिर काष्ठा net_device *ol_dev)
अणु
	जोड़ mlxsw_sp_l3addr saddr = mlxsw_sp_ipip_netdev_saddr(proto, ol_dev);
	जोड़ mlxsw_sp_l3addr daddr = mlxsw_sp_ipip_netdev_daddr(proto, ol_dev);

	/* Tunnels with unset local or remote address are valid in Linux and
	 * used क्रम lightweight tunnels (LWT) and Non-Broadcast Multi-Access
	 * (NBMA) tunnels. In principle these can be offloaded, but the driver
	 * currently करोesn't support this. So punt.
	 */
	वापस !mlxsw_sp_l3addr_is_zero(saddr) &&
	       !mlxsw_sp_l3addr_is_zero(daddr);
पूर्ण

अटल bool mlxsw_sp_ipip_can_offload_gre4(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
					   स्थिर काष्ठा net_device *ol_dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(ol_dev);
	__be16 okflags = TUNNEL_KEY; /* We can't offload any other features. */
	bool inherit_ttl = tunnel->parms.iph.ttl == 0;
	bool inherit_tos = tunnel->parms.iph.tos & 0x1;

	वापस (tunnel->parms.i_flags & ~okflags) == 0 &&
	       (tunnel->parms.o_flags & ~okflags) == 0 &&
	       inherit_ttl && inherit_tos &&
	       mlxsw_sp_ipip_tunnel_complete(MLXSW_SP_L3_PROTO_IPV4, ol_dev);
पूर्ण

अटल काष्ठा mlxsw_sp_rअगर_ipip_lb_config
mlxsw_sp_ipip_ol_loopback_config_gre4(काष्ठा mlxsw_sp *mlxsw_sp,
				      स्थिर काष्ठा net_device *ol_dev)
अणु
	काष्ठा ip_tunnel_parm parms = mlxsw_sp_ipip_netdev_parms4(ol_dev);
	क्रमागत mlxsw_reg_ritr_loopback_ipip_type lb_ipipt;

	lb_ipipt = mlxsw_sp_ipip_parms4_has_okey(parms) ?
		MLXSW_REG_RITR_LOOPBACK_IPIP_TYPE_IP_IN_GRE_KEY_IN_IP :
		MLXSW_REG_RITR_LOOPBACK_IPIP_TYPE_IP_IN_GRE_IN_IP;
	वापस (काष्ठा mlxsw_sp_rअगर_ipip_lb_config)अणु
		.lb_ipipt = lb_ipipt,
		.okey = mlxsw_sp_ipip_parms4_okey(parms),
		.ul_protocol = MLXSW_SP_L3_PROTO_IPV4,
		.saddr = mlxsw_sp_ipip_netdev_saddr(MLXSW_SP_L3_PROTO_IPV4,
						    ol_dev),
	पूर्ण;
पूर्ण

अटल पूर्णांक
mlxsw_sp_ipip_ol_netdev_change_gre4(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_ipip_entry *ipip_entry,
				    काष्ठा netlink_ext_ack *extack)
अणु
	जोड़ mlxsw_sp_l3addr old_saddr, new_saddr;
	जोड़ mlxsw_sp_l3addr old_daddr, new_daddr;
	काष्ठा ip_tunnel_parm new_parms;
	bool update_tunnel = false;
	bool update_decap = false;
	bool update_nhs = false;
	पूर्णांक err = 0;

	new_parms = mlxsw_sp_ipip_netdev_parms4(ipip_entry->ol_dev);

	new_saddr = mlxsw_sp_ipip_parms4_saddr(new_parms);
	old_saddr = mlxsw_sp_ipip_parms4_saddr(ipip_entry->parms4);
	new_daddr = mlxsw_sp_ipip_parms4_daddr(new_parms);
	old_daddr = mlxsw_sp_ipip_parms4_daddr(ipip_entry->parms4);

	अगर (!mlxsw_sp_l3addr_eq(&new_saddr, &old_saddr)) अणु
		u16 ul_tb_id = mlxsw_sp_ipip_dev_ul_tb_id(ipip_entry->ol_dev);

		/* Since the local address has changed, अगर there is another
		 * tunnel with a matching saddr, both need to be demoted.
		 */
		अगर (mlxsw_sp_ipip_demote_tunnel_by_saddr(mlxsw_sp,
							 MLXSW_SP_L3_PROTO_IPV4,
							 new_saddr, ul_tb_id,
							 ipip_entry)) अणु
			mlxsw_sp_ipip_entry_demote_tunnel(mlxsw_sp, ipip_entry);
			वापस 0;
		पूर्ण

		update_tunnel = true;
	पूर्ण अन्यथा अगर ((mlxsw_sp_ipip_parms4_okey(ipip_entry->parms4) !=
		    mlxsw_sp_ipip_parms4_okey(new_parms)) ||
		   ipip_entry->parms4.link != new_parms.link) अणु
		update_tunnel = true;
	पूर्ण अन्यथा अगर (!mlxsw_sp_l3addr_eq(&new_daddr, &old_daddr)) अणु
		update_nhs = true;
	पूर्ण अन्यथा अगर (mlxsw_sp_ipip_parms4_ikey(ipip_entry->parms4) !=
		   mlxsw_sp_ipip_parms4_ikey(new_parms)) अणु
		update_decap = true;
	पूर्ण

	अगर (update_tunnel)
		err = __mlxsw_sp_ipip_entry_update_tunnel(mlxsw_sp, ipip_entry,
							  true, true, true,
							  extack);
	अन्यथा अगर (update_nhs)
		err = __mlxsw_sp_ipip_entry_update_tunnel(mlxsw_sp, ipip_entry,
							  false, false, true,
							  extack);
	अन्यथा अगर (update_decap)
		err = __mlxsw_sp_ipip_entry_update_tunnel(mlxsw_sp, ipip_entry,
							  false, false, false,
							  extack);

	ipip_entry->parms4 = new_parms;
	वापस err;
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_ipip_ops mlxsw_sp_ipip_gre4_ops = अणु
	.dev_type = ARPHRD_IPGRE,
	.ul_proto = MLXSW_SP_L3_PROTO_IPV4,
	.nexthop_update = mlxsw_sp_ipip_nexthop_update_gre4,
	.decap_config = mlxsw_sp_ipip_decap_config_gre4,
	.can_offload = mlxsw_sp_ipip_can_offload_gre4,
	.ol_loopback_config = mlxsw_sp_ipip_ol_loopback_config_gre4,
	.ol_netdev_change = mlxsw_sp_ipip_ol_netdev_change_gre4,
पूर्ण;

स्थिर काष्ठा mlxsw_sp_ipip_ops *mlxsw_sp_ipip_ops_arr[] = अणु
	[MLXSW_SP_IPIP_TYPE_GRE4] = &mlxsw_sp_ipip_gre4_ops,
पूर्ण;

अटल पूर्णांक mlxsw_sp_ipip_ecn_encap_init_one(काष्ठा mlxsw_sp *mlxsw_sp,
					    u8 inner_ecn, u8 outer_ecn)
अणु
	अक्षर tieem_pl[MLXSW_REG_TIEEM_LEN];

	mlxsw_reg_tieem_pack(tieem_pl, inner_ecn, outer_ecn);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(tieem), tieem_pl);
पूर्ण

पूर्णांक mlxsw_sp_ipip_ecn_encap_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	पूर्णांक i;

	/* Iterate over inner ECN values */
	क्रम (i = INET_ECN_NOT_ECT; i <= INET_ECN_CE; i++) अणु
		u8 outer_ecn = INET_ECN_encapsulate(0, i);
		पूर्णांक err;

		err = mlxsw_sp_ipip_ecn_encap_init_one(mlxsw_sp, i, outer_ecn);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_ipip_ecn_decap_init_one(काष्ठा mlxsw_sp *mlxsw_sp,
					    u8 inner_ecn, u8 outer_ecn)
अणु
	अक्षर tidem_pl[MLXSW_REG_TIDEM_LEN];
	u8 new_inner_ecn;
	bool trap_en;

	new_inner_ecn = mlxsw_sp_tunnel_ecn_decap(outer_ecn, inner_ecn,
						  &trap_en);
	mlxsw_reg_tidem_pack(tidem_pl, outer_ecn, inner_ecn, new_inner_ecn,
			     trap_en, trap_en ? MLXSW_TRAP_ID_DECAP_ECN0 : 0);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(tidem), tidem_pl);
पूर्ण

पूर्णांक mlxsw_sp_ipip_ecn_decap_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	पूर्णांक i, j, err;

	/* Iterate over inner ECN values */
	क्रम (i = INET_ECN_NOT_ECT; i <= INET_ECN_CE; i++) अणु
		/* Iterate over outer ECN values */
		क्रम (j = INET_ECN_NOT_ECT; j <= INET_ECN_CE; j++) अणु
			err = mlxsw_sp_ipip_ecn_decap_init_one(mlxsw_sp, i, j);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
