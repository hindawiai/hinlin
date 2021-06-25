<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2018 Mellanox Technologies. */

#अगर_अघोषित __MLX5E_FLOW_STEER_H__
#घोषणा __MLX5E_FLOW_STEER_H__

#समावेश "mod_hdr.h"

क्रमागत अणु
	MLX5E_TC_FT_LEVEL = 0,
	MLX5E_TC_TTC_FT_LEVEL,
पूर्ण;

काष्ठा mlx5e_tc_table अणु
	/* Protects the dynamic assignment of the t parameter
	 * which is the nic tc root table.
	 */
	काष्ठा mutex			t_lock;
	काष्ठा mlx5_flow_table		*t;
	काष्ठा mlx5_fs_chains           *chains;

	काष्ठा rhashtable               ht;

	काष्ठा mod_hdr_tbl mod_hdr;
	काष्ठा mutex hairpin_tbl_lock; /* protects hairpin_tbl */
	DECLARE_HASHTABLE(hairpin_tbl, 8);

	काष्ठा notअगरier_block     netdevice_nb;
	काष्ठा netdev_net_notअगरier	netdevice_nn;

	काष्ठा mlx5_tc_ct_priv         *ct;
	काष्ठा mapping_ctx             *mapping;
पूर्ण;

काष्ठा mlx5e_flow_table अणु
	पूर्णांक num_groups;
	काष्ठा mlx5_flow_table *t;
	काष्ठा mlx5_flow_group **g;
पूर्ण;

काष्ठा mlx5e_l2_rule अणु
	u8  addr[ETH_ALEN + 2];
	काष्ठा mlx5_flow_handle *rule;
पूर्ण;

#घोषणा MLX5E_L2_ADDR_HASH_SIZE BIT(BITS_PER_BYTE)

काष्ठा mlx5e_promisc_table अणु
	काष्ठा mlx5e_flow_table	ft;
	काष्ठा mlx5_flow_handle	*rule;
पूर्ण;

/* Forward declaration and APIs to get निजी fields of vlan_table */
काष्ठा mlx5e_vlan_table;
अचिन्हित दीर्घ *mlx5e_vlan_get_active_svlans(काष्ठा mlx5e_vlan_table *vlan);
काष्ठा mlx5_flow_table *mlx5e_vlan_get_flowtable(काष्ठा mlx5e_vlan_table *vlan);

काष्ठा mlx5e_l2_table अणु
	काष्ठा mlx5e_flow_table    ft;
	काष्ठा hlist_head          netdev_uc[MLX5E_L2_ADDR_HASH_SIZE];
	काष्ठा hlist_head          netdev_mc[MLX5E_L2_ADDR_HASH_SIZE];
	काष्ठा mlx5e_l2_rule	   broadcast;
	काष्ठा mlx5e_l2_rule	   allmulti;
	काष्ठा mlx5_flow_handle    *trap_rule;
	bool                       broadcast_enabled;
	bool                       allmulti_enabled;
	bool                       promisc_enabled;
पूर्ण;

क्रमागत mlx5e_traffic_types अणु
	MLX5E_TT_IPV4_TCP,
	MLX5E_TT_IPV6_TCP,
	MLX5E_TT_IPV4_UDP,
	MLX5E_TT_IPV6_UDP,
	MLX5E_TT_IPV4_IPSEC_AH,
	MLX5E_TT_IPV6_IPSEC_AH,
	MLX5E_TT_IPV4_IPSEC_ESP,
	MLX5E_TT_IPV6_IPSEC_ESP,
	MLX5E_TT_IPV4,
	MLX5E_TT_IPV6,
	MLX5E_TT_ANY,
	MLX5E_NUM_TT,
	MLX5E_NUM_INसूची_TIRS = MLX5E_TT_ANY,
पूर्ण;

काष्ठा mlx5e_tirc_config अणु
	u8 l3_prot_type;
	u8 l4_prot_type;
	u32 rx_hash_fields;
पूर्ण;

#घोषणा MLX5_HASH_IP		(MLX5_HASH_FIELD_SEL_SRC_IP   |\
				 MLX5_HASH_FIELD_SEL_DST_IP)
#घोषणा MLX5_HASH_IP_L4PORTS	(MLX5_HASH_FIELD_SEL_SRC_IP   |\
				 MLX5_HASH_FIELD_SEL_DST_IP   |\
				 MLX5_HASH_FIELD_SEL_L4_SPORT |\
				 MLX5_HASH_FIELD_SEL_L4_DPORT)
#घोषणा MLX5_HASH_IP_IPSEC_SPI	(MLX5_HASH_FIELD_SEL_SRC_IP   |\
				 MLX5_HASH_FIELD_SEL_DST_IP   |\
				 MLX5_HASH_FIELD_SEL_IPSEC_SPI)

क्रमागत mlx5e_tunnel_types अणु
	MLX5E_TT_IPV4_GRE,
	MLX5E_TT_IPV6_GRE,
	MLX5E_TT_IPV4_IPIP,
	MLX5E_TT_IPV6_IPIP,
	MLX5E_TT_IPV4_IPV6,
	MLX5E_TT_IPV6_IPV6,
	MLX5E_NUM_TUNNEL_TT,
पूर्ण;

bool mlx5e_tunnel_inner_ft_supported(काष्ठा mlx5_core_dev *mdev);

काष्ठा mlx5e_ttc_rule अणु
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5_flow_destination शेष_dest;
पूर्ण;

/* L3/L4 traffic type classअगरier */
काष्ठा mlx5e_ttc_table अणु
	काष्ठा mlx5e_flow_table ft;
	काष्ठा mlx5e_ttc_rule rules[MLX5E_NUM_TT];
	काष्ठा mlx5_flow_handle *tunnel_rules[MLX5E_NUM_TUNNEL_TT];
पूर्ण;

/* NIC prio FTS */
क्रमागत अणु
	MLX5E_PROMISC_FT_LEVEL,
	MLX5E_VLAN_FT_LEVEL,
	MLX5E_L2_FT_LEVEL,
	MLX5E_TTC_FT_LEVEL,
	MLX5E_INNER_TTC_FT_LEVEL,
	MLX5E_FS_TT_UDP_FT_LEVEL = MLX5E_INNER_TTC_FT_LEVEL + 1,
	MLX5E_FS_TT_ANY_FT_LEVEL = MLX5E_INNER_TTC_FT_LEVEL + 1,
#अगर_घोषित CONFIG_MLX5_EN_TLS
	MLX5E_ACCEL_FS_TCP_FT_LEVEL = MLX5E_INNER_TTC_FT_LEVEL + 1,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MLX5_EN_ARFS
	MLX5E_ARFS_FT_LEVEL = MLX5E_INNER_TTC_FT_LEVEL + 1,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MLX5_EN_IPSEC
	MLX5E_ACCEL_FS_ESP_FT_LEVEL = MLX5E_INNER_TTC_FT_LEVEL + 1,
	MLX5E_ACCEL_FS_ESP_FT_ERR_LEVEL,
#पूर्ण_अगर
पूर्ण;

#घोषणा MLX5E_TTC_NUM_GROUPS	3
#घोषणा MLX5E_TTC_GROUP1_SIZE	(BIT(3) + MLX5E_NUM_TUNNEL_TT)
#घोषणा MLX5E_TTC_GROUP2_SIZE	 BIT(1)
#घोषणा MLX5E_TTC_GROUP3_SIZE	 BIT(0)
#घोषणा MLX5E_TTC_TABLE_SIZE	(MLX5E_TTC_GROUP1_SIZE +\
				 MLX5E_TTC_GROUP2_SIZE +\
				 MLX5E_TTC_GROUP3_SIZE)

#घोषणा MLX5E_INNER_TTC_NUM_GROUPS	3
#घोषणा MLX5E_INNER_TTC_GROUP1_SIZE	BIT(3)
#घोषणा MLX5E_INNER_TTC_GROUP2_SIZE	BIT(1)
#घोषणा MLX5E_INNER_TTC_GROUP3_SIZE	BIT(0)
#घोषणा MLX5E_INNER_TTC_TABLE_SIZE	(MLX5E_INNER_TTC_GROUP1_SIZE +\
					 MLX5E_INNER_TTC_GROUP2_SIZE +\
					 MLX5E_INNER_TTC_GROUP3_SIZE)

#अगर_घोषित CONFIG_MLX5_EN_RXNFC

काष्ठा mlx5e_ethtool_table अणु
	काष्ठा mlx5_flow_table *ft;
	पूर्णांक                    num_rules;
पूर्ण;

#घोषणा ETHTOOL_NUM_L3_L4_FTS 7
#घोषणा ETHTOOL_NUM_L2_FTS 4

काष्ठा mlx5e_ethtool_steering अणु
	काष्ठा mlx5e_ethtool_table      l3_l4_ft[ETHTOOL_NUM_L3_L4_FTS];
	काष्ठा mlx5e_ethtool_table      l2_ft[ETHTOOL_NUM_L2_FTS];
	काष्ठा list_head                rules;
	पूर्णांक                             tot_num_rules;
पूर्ण;

व्योम mlx5e_ethtool_init_steering(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_ethtool_cleanup_steering(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_ethtool_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd);
पूर्णांक mlx5e_ethtool_get_rxnfc(काष्ठा net_device *dev,
			    काष्ठा ethtool_rxnfc *info, u32 *rule_locs);
#अन्यथा
अटल अंतरभूत व्योम mlx5e_ethtool_init_steering(काष्ठा mlx5e_priv *priv)    अणु पूर्ण
अटल अंतरभूत व्योम mlx5e_ethtool_cleanup_steering(काष्ठा mlx5e_priv *priv) अणु पूर्ण
अटल अंतरभूत पूर्णांक mlx5e_ethtool_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd)
अणु वापस -EOPNOTSUPP; पूर्ण
अटल अंतरभूत पूर्णांक mlx5e_ethtool_get_rxnfc(काष्ठा net_device *dev,
					  काष्ठा ethtool_rxnfc *info, u32 *rule_locs)
अणु वापस -EOPNOTSUPP; पूर्ण
#पूर्ण_अगर /* CONFIG_MLX5_EN_RXNFC */

#अगर_घोषित CONFIG_MLX5_EN_ARFS
काष्ठा mlx5e_arfs_tables;

पूर्णांक mlx5e_arfs_create_tables(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_arfs_destroy_tables(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_arfs_enable(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_arfs_disable(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_rx_flow_steer(काष्ठा net_device *dev, स्थिर काष्ठा sk_buff *skb,
			u16 rxq_index, u32 flow_id);
#अन्यथा
अटल अंतरभूत पूर्णांक mlx5e_arfs_create_tables(काष्ठा mlx5e_priv *priv) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mlx5e_arfs_destroy_tables(काष्ठा mlx5e_priv *priv) अणुपूर्ण
अटल अंतरभूत पूर्णांक mlx5e_arfs_enable(काष्ठा mlx5e_priv *priv) अणु वापस -EOPNOTSUPP; पूर्ण
अटल अंतरभूत पूर्णांक mlx5e_arfs_disable(काष्ठा mlx5e_priv *priv) अणु	वापस -EOPNOTSUPP; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MLX5_EN_TLS
काष्ठा mlx5e_accel_fs_tcp;
#पूर्ण_अगर

काष्ठा mlx5e_fs_udp;
काष्ठा mlx5e_fs_any;
काष्ठा mlx5e_ptp_fs;

काष्ठा mlx5e_flow_steering अणु
	काष्ठा mlx5_flow_namespace      *ns;
	काष्ठा mlx5_flow_namespace      *egress_ns;
#अगर_घोषित CONFIG_MLX5_EN_RXNFC
	काष्ठा mlx5e_ethtool_steering   ethtool;
#पूर्ण_अगर
	काष्ठा mlx5e_tc_table           tc;
	काष्ठा mlx5e_promisc_table      promisc;
	काष्ठा mlx5e_vlan_table         *vlan;
	काष्ठा mlx5e_l2_table           l2;
	काष्ठा mlx5e_ttc_table          ttc;
	काष्ठा mlx5e_ttc_table          inner_ttc;
#अगर_घोषित CONFIG_MLX5_EN_ARFS
	काष्ठा mlx5e_arfs_tables       *arfs;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MLX5_EN_TLS
	काष्ठा mlx5e_accel_fs_tcp      *accel_tcp;
#पूर्ण_अगर
	काष्ठा mlx5e_fs_udp            *udp;
	काष्ठा mlx5e_fs_any            *any;
	काष्ठा mlx5e_ptp_fs            *ptp_fs;
पूर्ण;

काष्ठा ttc_params अणु
	काष्ठा mlx5_flow_table_attr ft_attr;
	u32 any_tt_tirn;
	u32 indir_tirn[MLX5E_NUM_INसूची_TIRS];
	काष्ठा mlx5e_ttc_table *inner_ttc;
पूर्ण;

व्योम mlx5e_set_ttc_basic_params(काष्ठा mlx5e_priv *priv, काष्ठा ttc_params *ttc_params);
व्योम mlx5e_set_ttc_ft_params(काष्ठा ttc_params *ttc_params);
व्योम mlx5e_set_inner_ttc_ft_params(काष्ठा ttc_params *ttc_params);

पूर्णांक mlx5e_create_ttc_table(काष्ठा mlx5e_priv *priv, काष्ठा ttc_params *params,
			   काष्ठा mlx5e_ttc_table *ttc);
व्योम mlx5e_destroy_ttc_table(काष्ठा mlx5e_priv *priv,
			     काष्ठा mlx5e_ttc_table *ttc);

पूर्णांक mlx5e_create_inner_ttc_table(काष्ठा mlx5e_priv *priv, काष्ठा ttc_params *params,
				 काष्ठा mlx5e_ttc_table *ttc);
व्योम mlx5e_destroy_inner_ttc_table(काष्ठा mlx5e_priv *priv,
				   काष्ठा mlx5e_ttc_table *ttc);

व्योम mlx5e_destroy_flow_table(काष्ठा mlx5e_flow_table *ft);
पूर्णांक mlx5e_ttc_fwd_dest(काष्ठा mlx5e_priv *priv, क्रमागत mlx5e_traffic_types type,
		       काष्ठा mlx5_flow_destination *new_dest);
काष्ठा mlx5_flow_destination
mlx5e_ttc_get_शेष_dest(काष्ठा mlx5e_priv *priv, क्रमागत mlx5e_traffic_types type);
पूर्णांक mlx5e_ttc_fwd_शेष_dest(काष्ठा mlx5e_priv *priv, क्रमागत mlx5e_traffic_types type);

व्योम mlx5e_enable_cvlan_filter(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_disable_cvlan_filter(काष्ठा mlx5e_priv *priv);

पूर्णांक mlx5e_create_flow_steering(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_destroy_flow_steering(काष्ठा mlx5e_priv *priv);

u8 mlx5e_get_proto_by_tunnel_type(क्रमागत mlx5e_tunnel_types tt);
पूर्णांक mlx5e_add_vlan_trap(काष्ठा mlx5e_priv *priv, पूर्णांक  trap_id, पूर्णांक tir_num);
व्योम mlx5e_हटाओ_vlan_trap(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_add_mac_trap(काष्ठा mlx5e_priv *priv, पूर्णांक  trap_id, पूर्णांक tir_num);
व्योम mlx5e_हटाओ_mac_trap(काष्ठा mlx5e_priv *priv);

#पूर्ण_अगर /* __MLX5E_FLOW_STEER_H__ */

