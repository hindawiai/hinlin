<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_IPIP_H_
#घोषणा _MLXSW_IPIP_H_

#समावेश "spectrum_router.h"
#समावेश <net/ip_fib.h>
#समावेश <linux/अगर_tunnel.h>

काष्ठा ip_tunnel_parm
mlxsw_sp_ipip_netdev_parms4(स्थिर काष्ठा net_device *ol_dev);
काष्ठा __ip6_tnl_parm
mlxsw_sp_ipip_netdev_parms6(स्थिर काष्ठा net_device *ol_dev);

जोड़ mlxsw_sp_l3addr
mlxsw_sp_ipip_netdev_saddr(क्रमागत mlxsw_sp_l3proto proto,
			   स्थिर काष्ठा net_device *ol_dev);

bool mlxsw_sp_l3addr_is_zero(जोड़ mlxsw_sp_l3addr addr);

क्रमागत mlxsw_sp_ipip_type अणु
	MLXSW_SP_IPIP_TYPE_GRE4,
	MLXSW_SP_IPIP_TYPE_MAX,
पूर्ण;

काष्ठा mlxsw_sp_ipip_entry अणु
	क्रमागत mlxsw_sp_ipip_type ipipt;
	काष्ठा net_device *ol_dev; /* Overlay. */
	काष्ठा mlxsw_sp_rअगर_ipip_lb *ol_lb;
	काष्ठा mlxsw_sp_fib_entry *decap_fib_entry;
	काष्ठा list_head ipip_list_node;
	जोड़ अणु
		काष्ठा ip_tunnel_parm parms4;
	पूर्ण;
पूर्ण;

काष्ठा mlxsw_sp_ipip_ops अणु
	पूर्णांक dev_type;
	क्रमागत mlxsw_sp_l3proto ul_proto; /* Underlay. */

	पूर्णांक (*nexthop_update)(काष्ठा mlxsw_sp *mlxsw_sp, u32 adj_index,
			      काष्ठा mlxsw_sp_ipip_entry *ipip_entry,
			      bool क्रमce, अक्षर *ratr_pl);

	bool (*can_offload)(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
			    स्थिर काष्ठा net_device *ol_dev);

	/* Return a configuration क्रम creating an overlay loopback RIF. */
	काष्ठा mlxsw_sp_rअगर_ipip_lb_config
	(*ol_loopback_config)(काष्ठा mlxsw_sp *mlxsw_sp,
			      स्थिर काष्ठा net_device *ol_dev);

	पूर्णांक (*decap_config)(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_ipip_entry *ipip_entry,
			    u32 tunnel_index);

	पूर्णांक (*ol_netdev_change)(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_ipip_entry *ipip_entry,
				काष्ठा netlink_ext_ack *extack);
पूर्ण;

बाह्य स्थिर काष्ठा mlxsw_sp_ipip_ops *mlxsw_sp_ipip_ops_arr[];

#पूर्ण_अगर /* _MLXSW_IPIP_H_*/
