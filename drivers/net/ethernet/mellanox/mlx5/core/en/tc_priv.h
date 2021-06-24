<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2021 Mellanox Technologies. */

#अगर_अघोषित __MLX5_EN_TC_PRIV_H__
#घोषणा __MLX5_EN_TC_PRIV_H__

#समावेश "en_tc.h"

#घोषणा MLX5E_TC_FLOW_BASE (MLX5E_TC_FLAG_LAST_EXPORTED_BIT + 1)

#घोषणा MLX5E_TC_MAX_SPLITS 1

क्रमागत अणु
	MLX5E_TC_FLOW_FLAG_INGRESS               = MLX5E_TC_FLAG_INGRESS_BIT,
	MLX5E_TC_FLOW_FLAG_EGRESS                = MLX5E_TC_FLAG_EGRESS_BIT,
	MLX5E_TC_FLOW_FLAG_ESWITCH               = MLX5E_TC_FLAG_ESW_OFFLOAD_BIT,
	MLX5E_TC_FLOW_FLAG_FT                    = MLX5E_TC_FLAG_FT_OFFLOAD_BIT,
	MLX5E_TC_FLOW_FLAG_NIC                   = MLX5E_TC_FLAG_NIC_OFFLOAD_BIT,
	MLX5E_TC_FLOW_FLAG_OFFLOADED             = MLX5E_TC_FLOW_BASE,
	MLX5E_TC_FLOW_FLAG_HAIRPIN               = MLX5E_TC_FLOW_BASE + 1,
	MLX5E_TC_FLOW_FLAG_HAIRPIN_RSS           = MLX5E_TC_FLOW_BASE + 2,
	MLX5E_TC_FLOW_FLAG_SLOW                  = MLX5E_TC_FLOW_BASE + 3,
	MLX5E_TC_FLOW_FLAG_DUP                   = MLX5E_TC_FLOW_BASE + 4,
	MLX5E_TC_FLOW_FLAG_NOT_READY             = MLX5E_TC_FLOW_BASE + 5,
	MLX5E_TC_FLOW_FLAG_DELETED               = MLX5E_TC_FLOW_BASE + 6,
	MLX5E_TC_FLOW_FLAG_CT                    = MLX5E_TC_FLOW_BASE + 7,
	MLX5E_TC_FLOW_FLAG_L3_TO_L2_DECAP        = MLX5E_TC_FLOW_BASE + 8,
	MLX5E_TC_FLOW_FLAG_TUN_RX                = MLX5E_TC_FLOW_BASE + 9,
	MLX5E_TC_FLOW_FLAG_FAILED                = MLX5E_TC_FLOW_BASE + 10,
	MLX5E_TC_FLOW_FLAG_SAMPLE                = MLX5E_TC_FLOW_BASE + 11,
पूर्ण;

काष्ठा mlx5e_tc_flow_parse_attr अणु
	स्थिर काष्ठा ip_tunnel_info *tun_info[MLX5_MAX_FLOW_FWD_VPORTS];
	काष्ठा net_device *filter_dev;
	काष्ठा mlx5_flow_spec spec;
	काष्ठा mlx5e_tc_mod_hdr_acts mod_hdr_acts;
	पूर्णांक mirred_अगरindex[MLX5_MAX_FLOW_FWD_VPORTS];
	काष्ठा ethhdr eth;
पूर्ण;

/* Helper काष्ठा क्रम accessing a काष्ठा containing list_head array.
 * Containing काष्ठा
 *   |- Helper array
 *      [0] Helper item 0
 *          |- list_head item 0
 *          |- index (0)
 *      [1] Helper item 1
 *          |- list_head item 1
 *          |- index (1)
 * To access the containing काष्ठा from one of the list_head items:
 * 1. Get the helper item from the list_head item using
 *    helper item =
 *        container_of(list_head item, helper काष्ठा type, list_head field)
 * 2. Get the contining काष्ठा from the helper item and its index in the array:
 *    containing काष्ठा =
 *        container_of(helper item, containing काष्ठा type, helper field[index])
 */
काष्ठा encap_flow_item अणु
	काष्ठा mlx5e_encap_entry *e; /* attached encap instance */
	काष्ठा list_head list;
	पूर्णांक index;
पूर्ण;

काष्ठा encap_route_flow_item अणु
	काष्ठा mlx5e_route_entry *r; /* attached route instance */
	पूर्णांक index;
पूर्ण;

काष्ठा mlx5e_tc_flow अणु
	काष्ठा rhash_head node;
	काष्ठा mlx5e_priv *priv;
	u64 cookie;
	अचिन्हित दीर्घ flags;
	काष्ठा mlx5_flow_handle *rule[MLX5E_TC_MAX_SPLITS + 1];

	/* flows sharing the same reक्रमmat object - currently mpls decap */
	काष्ठा list_head l3_to_l2_reक्रमmat;
	काष्ठा mlx5e_decap_entry *decap_reक्रमmat;

	/* flows sharing same route entry */
	काष्ठा list_head decap_routes;
	काष्ठा mlx5e_route_entry *decap_route;
	काष्ठा encap_route_flow_item encap_routes[MLX5_MAX_FLOW_FWD_VPORTS];

	/* Flow can be associated with multiple encap IDs.
	 * The number of encaps is bounded by the number of supported
	 * destinations.
	 */
	काष्ठा encap_flow_item encaps[MLX5_MAX_FLOW_FWD_VPORTS];
	काष्ठा mlx5e_tc_flow *peer_flow;
	काष्ठा mlx5e_mod_hdr_handle *mh; /* attached mod header instance */
	काष्ठा mlx5e_hairpin_entry *hpe; /* attached hairpin instance */
	काष्ठा list_head hairpin; /* flows sharing the same hairpin */
	काष्ठा list_head peer;    /* flows with peer flow */
	काष्ठा list_head unपढ़ोy; /* flows not पढ़ोy to be offloaded (e.g
				   * due to missing route)
				   */
	काष्ठा net_device *orig_dev; /* netdev adding flow first */
	पूर्णांक पंचांगp_entry_index;
	काष्ठा list_head पंचांगp_list; /* temporary flow list used by neigh update */
	refcount_t refcnt;
	काष्ठा rcu_head rcu_head;
	काष्ठा completion init_करोne;
	पूर्णांक tunnel_id; /* the mapped tunnel id of this flow */
	काष्ठा mlx5_flow_attr *attr;
पूर्ण;

u8 mlx5e_tc_get_ip_version(काष्ठा mlx5_flow_spec *spec, bool outer);

काष्ठा mlx5_flow_handle *
mlx5e_tc_offload_fdb_rules(काष्ठा mlx5_eचयन *esw,
			   काष्ठा mlx5e_tc_flow *flow,
			   काष्ठा mlx5_flow_spec *spec,
			   काष्ठा mlx5_flow_attr *attr);

bool mlx5e_is_offloaded_flow(काष्ठा mlx5e_tc_flow *flow);

अटल अंतरभूत व्योम __flow_flag_set(काष्ठा mlx5e_tc_flow *flow, अचिन्हित दीर्घ flag)
अणु
	/* Complete all memory stores beक्रमe setting bit. */
	smp_mb__beक्रमe_atomic();
	set_bit(flag, &flow->flags);
पूर्ण

#घोषणा flow_flag_set(flow, flag) __flow_flag_set(flow, MLX5E_TC_FLOW_FLAG_##flag)

अटल अंतरभूत bool __flow_flag_test_and_set(काष्ठा mlx5e_tc_flow *flow,
					    अचिन्हित दीर्घ flag)
अणु
	/* test_and_set_bit() provides all necessary barriers */
	वापस test_and_set_bit(flag, &flow->flags);
पूर्ण

#घोषणा flow_flag_test_and_set(flow, flag)			\
	__flow_flag_test_and_set(flow,				\
				 MLX5E_TC_FLOW_FLAG_##flag)

अटल अंतरभूत व्योम __flow_flag_clear(काष्ठा mlx5e_tc_flow *flow, अचिन्हित दीर्घ flag)
अणु
	/* Complete all memory stores beक्रमe clearing bit. */
	smp_mb__beक्रमe_atomic();
	clear_bit(flag, &flow->flags);
पूर्ण

#घोषणा flow_flag_clear(flow, flag) __flow_flag_clear(flow,		\
						      MLX5E_TC_FLOW_FLAG_##flag)

अटल अंतरभूत bool __flow_flag_test(काष्ठा mlx5e_tc_flow *flow, अचिन्हित दीर्घ flag)
अणु
	bool ret = test_bit(flag, &flow->flags);

	/* Read fields of flow काष्ठाure only after checking flags. */
	smp_mb__after_atomic();
	वापस ret;
पूर्ण

#घोषणा flow_flag_test(flow, flag) __flow_flag_test(flow,		\
						    MLX5E_TC_FLOW_FLAG_##flag)

व्योम mlx5e_tc_unoffload_from_slow_path(काष्ठा mlx5_eचयन *esw,
				       काष्ठा mlx5e_tc_flow *flow);
काष्ठा mlx5_flow_handle *
mlx5e_tc_offload_to_slow_path(काष्ठा mlx5_eचयन *esw,
			      काष्ठा mlx5e_tc_flow *flow,
			      काष्ठा mlx5_flow_spec *spec);
व्योम mlx5e_tc_unoffload_fdb_rules(काष्ठा mlx5_eचयन *esw,
				  काष्ठा mlx5e_tc_flow *flow,
				  काष्ठा mlx5_flow_attr *attr);

काष्ठा mlx5e_tc_flow *mlx5e_flow_get(काष्ठा mlx5e_tc_flow *flow);
व्योम mlx5e_flow_put(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_tc_flow *flow);

काष्ठा mlx5_fc *mlx5e_tc_get_counter(काष्ठा mlx5e_tc_flow *flow);

#पूर्ण_अगर /* __MLX5_EN_TC_PRIV_H__ */
