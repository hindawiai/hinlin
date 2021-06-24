<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2018 Mellanox Technologies. */

#अगर_अघोषित __MLX5_EN_TC_TUNNEL_H__
#घोषणा __MLX5_EN_TC_TUNNEL_H__

#समावेश <linux/netdevice.h>
#समावेश <linux/mlx5/fs.h>
#समावेश <net/pkt_cls.h>
#समावेश <linux/netlink.h>
#समावेश "en.h"
#समावेश "en_rep.h"

#अगर_घोषित CONFIG_MLX5_ESWITCH

क्रमागत अणु
	MLX5E_TC_TUNNEL_TYPE_UNKNOWN,
	MLX5E_TC_TUNNEL_TYPE_VXLAN,
	MLX5E_TC_TUNNEL_TYPE_GENEVE,
	MLX5E_TC_TUNNEL_TYPE_GRETAP,
	MLX5E_TC_TUNNEL_TYPE_MPLSOUDP,
पूर्ण;

काष्ठा mlx5e_encap_key अणु
	स्थिर काष्ठा ip_tunnel_key *ip_tun_key;
	काष्ठा mlx5e_tc_tunnel     *tc_tunnel;
पूर्ण;

काष्ठा mlx5e_tc_tunnel अणु
	पूर्णांक tunnel_type;
	क्रमागत mlx5_flow_match_level match_level;

	bool (*can_offload)(काष्ठा mlx5e_priv *priv);
	पूर्णांक (*calc_hlen)(काष्ठा mlx5e_encap_entry *e);
	पूर्णांक (*init_encap_attr)(काष्ठा net_device *tunnel_dev,
			       काष्ठा mlx5e_priv *priv,
			       काष्ठा mlx5e_encap_entry *e,
			       काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*generate_ip_tun_hdr)(अक्षर buf[],
				   __u8 *ip_proto,
				   काष्ठा mlx5e_encap_entry *e);
	पूर्णांक (*parse_udp_ports)(काष्ठा mlx5e_priv *priv,
			       काष्ठा mlx5_flow_spec *spec,
			       काष्ठा flow_cls_offload *f,
			       व्योम *headers_c,
			       व्योम *headers_v);
	पूर्णांक (*parse_tunnel)(काष्ठा mlx5e_priv *priv,
			    काष्ठा mlx5_flow_spec *spec,
			    काष्ठा flow_cls_offload *f,
			    व्योम *headers_c,
			    व्योम *headers_v);
	bool (*encap_info_equal)(काष्ठा mlx5e_encap_key *a,
				 काष्ठा mlx5e_encap_key *b);
पूर्ण;

बाह्य काष्ठा mlx5e_tc_tunnel vxlan_tunnel;
बाह्य काष्ठा mlx5e_tc_tunnel geneve_tunnel;
बाह्य काष्ठा mlx5e_tc_tunnel gre_tunnel;
बाह्य काष्ठा mlx5e_tc_tunnel mplsoudp_tunnel;

काष्ठा mlx5e_tc_tunnel *mlx5e_get_tc_tun(काष्ठा net_device *tunnel_dev);

पूर्णांक mlx5e_tc_tun_init_encap_attr(काष्ठा net_device *tunnel_dev,
				 काष्ठा mlx5e_priv *priv,
				 काष्ठा mlx5e_encap_entry *e,
				 काष्ठा netlink_ext_ack *extack);

पूर्णांक mlx5e_tc_tun_create_header_ipv4(काष्ठा mlx5e_priv *priv,
				    काष्ठा net_device *mirred_dev,
				    काष्ठा mlx5e_encap_entry *e);
पूर्णांक mlx5e_tc_tun_update_header_ipv4(काष्ठा mlx5e_priv *priv,
				    काष्ठा net_device *mirred_dev,
				    काष्ठा mlx5e_encap_entry *e);

#अगर IS_ENABLED(CONFIG_INET) && IS_ENABLED(CONFIG_IPV6)
पूर्णांक mlx5e_tc_tun_create_header_ipv6(काष्ठा mlx5e_priv *priv,
				    काष्ठा net_device *mirred_dev,
				    काष्ठा mlx5e_encap_entry *e);
पूर्णांक mlx5e_tc_tun_update_header_ipv6(काष्ठा mlx5e_priv *priv,
				    काष्ठा net_device *mirred_dev,
				    काष्ठा mlx5e_encap_entry *e);
#अन्यथा
अटल अंतरभूत पूर्णांक
mlx5e_tc_tun_create_header_ipv6(काष्ठा mlx5e_priv *priv,
				काष्ठा net_device *mirred_dev,
				काष्ठा mlx5e_encap_entry *e)
अणु वापस -EOPNOTSUPP; पूर्ण
अटल अंतरभूत पूर्णांक
mlx5e_tc_tun_update_header_ipv6(काष्ठा mlx5e_priv *priv,
				काष्ठा net_device *mirred_dev,
				काष्ठा mlx5e_encap_entry *e)
अणु वापस -EOPNOTSUPP; पूर्ण
#पूर्ण_अगर
पूर्णांक mlx5e_tc_tun_route_lookup(काष्ठा mlx5e_priv *priv,
			      काष्ठा mlx5_flow_spec *spec,
			      काष्ठा mlx5_flow_attr *attr);

bool mlx5e_tc_tun_device_to_offload(काष्ठा mlx5e_priv *priv,
				    काष्ठा net_device *netdev);

पूर्णांक mlx5e_tc_tun_parse(काष्ठा net_device *filter_dev,
		       काष्ठा mlx5e_priv *priv,
		       काष्ठा mlx5_flow_spec *spec,
		       काष्ठा flow_cls_offload *f,
		       u8 *match_level);

पूर्णांक mlx5e_tc_tun_parse_udp_ports(काष्ठा mlx5e_priv *priv,
				 काष्ठा mlx5_flow_spec *spec,
				 काष्ठा flow_cls_offload *f,
				 व्योम *headers_c,
				 व्योम *headers_v);

bool mlx5e_tc_tun_encap_info_equal_generic(काष्ठा mlx5e_encap_key *a,
					   काष्ठा mlx5e_encap_key *b);

#पूर्ण_अगर /* CONFIG_MLX5_ESWITCH */

#पूर्ण_अगर //__MLX5_EN_TC_TUNNEL_H__
