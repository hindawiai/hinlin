<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	Bridge per vlan tunnels
 *
 *	Authors:
 *	Roopa Prabhu		<roopa@cumulusnetworks.com>
 */

#अगर_अघोषित _BR_PRIVATE_TUNNEL_H
#घोषणा _BR_PRIVATE_TUNNEL_H

काष्ठा vtunnel_info अणु
	u32	tunid;
	u16	vid;
	u16	flags;
पूर्ण;

/* br_netlink_tunnel.c */
पूर्णांक br_parse_vlan_tunnel_info(काष्ठा nlattr *attr,
			      काष्ठा vtunnel_info *tinfo);
पूर्णांक br_process_vlan_tunnel_info(स्थिर काष्ठा net_bridge *br,
				स्थिर काष्ठा net_bridge_port *p,
				पूर्णांक cmd,
				काष्ठा vtunnel_info *tinfo_curr,
				काष्ठा vtunnel_info *tinfo_last,
				bool *changed);
पूर्णांक br_get_vlan_tunnel_info_size(काष्ठा net_bridge_vlan_group *vg);
पूर्णांक br_fill_vlan_tunnel_info(काष्ठा sk_buff *skb,
			     काष्ठा net_bridge_vlan_group *vg);

#अगर_घोषित CONFIG_BRIDGE_VLAN_FILTERING
/* br_vlan_tunnel.c */
पूर्णांक vlan_tunnel_init(काष्ठा net_bridge_vlan_group *vg);
व्योम vlan_tunnel_deinit(काष्ठा net_bridge_vlan_group *vg);
पूर्णांक nbp_vlan_tunnel_info_delete(स्थिर काष्ठा net_bridge_port *port, u16 vid);
पूर्णांक nbp_vlan_tunnel_info_add(स्थिर काष्ठा net_bridge_port *port, u16 vid,
			     u32 tun_id);
व्योम nbp_vlan_tunnel_info_flush(काष्ठा net_bridge_port *port);
व्योम vlan_tunnel_info_del(काष्ठा net_bridge_vlan_group *vg,
			  काष्ठा net_bridge_vlan *vlan);
पूर्णांक br_handle_ingress_vlan_tunnel(काष्ठा sk_buff *skb,
				  काष्ठा net_bridge_port *p,
				  काष्ठा net_bridge_vlan_group *vg);
पूर्णांक br_handle_egress_vlan_tunnel(काष्ठा sk_buff *skb,
				 काष्ठा net_bridge_vlan *vlan);
bool vlan_tunid_inrange(स्थिर काष्ठा net_bridge_vlan *v_curr,
			स्थिर काष्ठा net_bridge_vlan *v_last);
पूर्णांक br_vlan_tunnel_info(स्थिर काष्ठा net_bridge_port *p, पूर्णांक cmd,
			u16 vid, u32 tun_id, bool *changed);
#अन्यथा
अटल अंतरभूत पूर्णांक vlan_tunnel_init(काष्ठा net_bridge_vlan_group *vg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक nbp_vlan_tunnel_info_delete(स्थिर काष्ठा net_bridge_port *port,
					      u16 vid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक nbp_vlan_tunnel_info_add(स्थिर काष्ठा net_bridge_port *port,
					   u16 vid, u32 tun_id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nbp_vlan_tunnel_info_flush(काष्ठा net_bridge_port *port)
अणु
पूर्ण

अटल अंतरभूत व्योम vlan_tunnel_info_del(काष्ठा net_bridge_vlan_group *vg,
					काष्ठा net_bridge_vlan *vlan)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक br_handle_ingress_vlan_tunnel(काष्ठा sk_buff *skb,
						काष्ठा net_bridge_port *p,
						काष्ठा net_bridge_vlan_group *vg)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
