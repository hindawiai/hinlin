<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_ROUTER_H_
#घोषणा _MLXSW_ROUTER_H_

#समावेश "spectrum.h"
#समावेश "reg.h"

काष्ठा mlxsw_sp_router_nve_decap अणु
	u32 ul_tb_id;
	u32 tunnel_index;
	क्रमागत mlxsw_sp_l3proto ul_proto;
	जोड़ mlxsw_sp_l3addr ul_sip;
	u8 valid:1;
पूर्ण;

काष्ठा mlxsw_sp_fib_entry_op_ctx अणु
	u8 bulk_ok:1, /* Indicate to the low-level op it is ok to bulk
		       * the actual entry with the one that is the next
		       * in queue.
		       */
	   initialized:1; /* Bit that the low-level op sets in हाल
			   * the context priv is initialized.
			   */
	काष्ठा list_head fib_entry_priv_list;
	अचिन्हित दीर्घ event;
	अचिन्हित दीर्घ ll_priv[];
पूर्ण;

अटल अंतरभूत व्योम
mlxsw_sp_fib_entry_op_ctx_clear(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx)
अणु
	WARN_ON_ONCE(!list_empty(&op_ctx->fib_entry_priv_list));
	स_रखो(op_ctx, 0, माप(*op_ctx));
	INIT_LIST_HEAD(&op_ctx->fib_entry_priv_list);
पूर्ण

काष्ठा mlxsw_sp_router अणु
	काष्ठा mlxsw_sp *mlxsw_sp;
	काष्ठा mlxsw_sp_rअगर **rअगरs;
	काष्ठा mlxsw_sp_vr *vrs;
	काष्ठा rhashtable neigh_ht;
	काष्ठा rhashtable nexthop_group_ht;
	काष्ठा rhashtable nexthop_ht;
	काष्ठा list_head nexthop_list;
	काष्ठा अणु
		/* One tree क्रम each protocol: IPv4 and IPv6 */
		काष्ठा mlxsw_sp_lpm_tree *proto_trees[2];
		काष्ठा mlxsw_sp_lpm_tree *trees;
		अचिन्हित पूर्णांक tree_count;
	पूर्ण lpm;
	काष्ठा अणु
		काष्ठा delayed_work dw;
		अचिन्हित दीर्घ पूर्णांकerval;	/* ms */
	पूर्ण neighs_update;
	काष्ठा delayed_work nexthop_probe_dw;
#घोषणा MLXSW_SP_UNRESOLVED_NH_PROBE_INTERVAL 5000 /* ms */
	काष्ठा list_head nexthop_neighs_list;
	काष्ठा list_head ipip_list;
	bool पातed;
	काष्ठा notअगरier_block nexthop_nb;
	काष्ठा notअगरier_block fib_nb;
	काष्ठा notअगरier_block netevent_nb;
	काष्ठा notअगरier_block inetaddr_nb;
	काष्ठा notअगरier_block inet6addr_nb;
	स्थिर काष्ठा mlxsw_sp_rअगर_ops **rअगर_ops_arr;
	स्थिर काष्ठा mlxsw_sp_ipip_ops **ipip_ops_arr;
	u32 adj_discard_index;
	bool adj_discard_index_valid;
	काष्ठा mlxsw_sp_router_nve_decap nve_decap_config;
	काष्ठा mutex lock; /* Protects shared router resources */
	काष्ठा work_काष्ठा fib_event_work;
	काष्ठा list_head fib_event_queue;
	spinlock_t fib_event_queue_lock; /* Protects fib event queue list */
	/* One set of ops क्रम each protocol: IPv4 and IPv6 */
	स्थिर काष्ठा mlxsw_sp_router_ll_ops *proto_ll_ops[MLXSW_SP_L3_PROTO_MAX];
	काष्ठा mlxsw_sp_fib_entry_op_ctx *ll_op_ctx;
	u16 lb_rअगर_index;
	काष्ठा mlxsw_sp_router_xm *xm;
	स्थिर काष्ठा mlxsw_sp_adj_grp_size_range *adj_grp_size_ranges;
	माप_प्रकार adj_grp_size_ranges_count;
	काष्ठा delayed_work nh_grp_activity_dw;
	काष्ठा list_head nh_res_grp_list;
पूर्ण;

काष्ठा mlxsw_sp_fib_entry_priv अणु
	refcount_t refcnt;
	काष्ठा list_head list; /* Member in op_ctx->fib_entry_priv_list */
	अचिन्हित दीर्घ priv[];
पूर्ण;

क्रमागत mlxsw_sp_fib_entry_op अणु
	MLXSW_SP_FIB_ENTRY_OP_WRITE,
	MLXSW_SP_FIB_ENTRY_OP_UPDATE,
	MLXSW_SP_FIB_ENTRY_OP_DELETE,
पूर्ण;

/* Low-level router ops. Basically this is to handle the dअगरferent
 * रेजिस्टर sets to work with ordinary and XM trees and FIB entries.
 */
काष्ठा mlxsw_sp_router_ll_ops अणु
	पूर्णांक (*init)(काष्ठा mlxsw_sp *mlxsw_sp, u16 vr_id,
		    क्रमागत mlxsw_sp_l3proto proto);
	पूर्णांक (*ralta_ग_लिखो)(काष्ठा mlxsw_sp *mlxsw_sp, अक्षर *xralta_pl);
	पूर्णांक (*ralst_ग_लिखो)(काष्ठा mlxsw_sp *mlxsw_sp, अक्षर *xralst_pl);
	पूर्णांक (*raltb_ग_लिखो)(काष्ठा mlxsw_sp *mlxsw_sp, अक्षर *xraltb_pl);
	माप_प्रकार fib_entry_op_ctx_size;
	माप_प्रकार fib_entry_priv_size;
	व्योम (*fib_entry_pack)(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
			       क्रमागत mlxsw_sp_l3proto proto, क्रमागत mlxsw_sp_fib_entry_op op,
			       u16 भव_router, u8 prefix_len, अचिन्हित अक्षर *addr,
			       काष्ठा mlxsw_sp_fib_entry_priv *priv);
	व्योम (*fib_entry_act_remote_pack)(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
					  क्रमागत mlxsw_reg_ralue_trap_action trap_action,
					  u16 trap_id, u32 adjacency_index, u16 ecmp_size);
	व्योम (*fib_entry_act_local_pack)(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
					 क्रमागत mlxsw_reg_ralue_trap_action trap_action,
					 u16 trap_id, u16 local_erअगर);
	व्योम (*fib_entry_act_ip2me_pack)(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx);
	व्योम (*fib_entry_act_ip2me_tun_pack)(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
					     u32 tunnel_ptr);
	पूर्णांक (*fib_entry_commit)(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
				bool *postponed_क्रम_bulk);
	bool (*fib_entry_is_committed)(काष्ठा mlxsw_sp_fib_entry_priv *priv);
पूर्ण;

काष्ठा mlxsw_sp_rअगर_ipip_lb;
काष्ठा mlxsw_sp_rअगर_ipip_lb_config अणु
	क्रमागत mlxsw_reg_ritr_loopback_ipip_type lb_ipipt;
	u32 okey;
	क्रमागत mlxsw_sp_l3proto ul_protocol; /* Underlay. */
	जोड़ mlxsw_sp_l3addr saddr;
पूर्ण;

क्रमागत mlxsw_sp_rअगर_counter_dir अणु
	MLXSW_SP_RIF_COUNTER_INGRESS,
	MLXSW_SP_RIF_COUNTER_EGRESS,
पूर्ण;

काष्ठा mlxsw_sp_neigh_entry;
काष्ठा mlxsw_sp_nexthop;
काष्ठा mlxsw_sp_ipip_entry;

काष्ठा mlxsw_sp_rअगर *mlxsw_sp_rअगर_by_index(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
					   u16 rअगर_index);
u16 mlxsw_sp_rअगर_index(स्थिर काष्ठा mlxsw_sp_rअगर *rअगर);
u16 mlxsw_sp_ipip_lb_rअगर_index(स्थिर काष्ठा mlxsw_sp_rअगर_ipip_lb *rअगर);
u16 mlxsw_sp_ipip_lb_ul_vr_id(स्थिर काष्ठा mlxsw_sp_rअगर_ipip_lb *rअगर);
u16 mlxsw_sp_ipip_lb_ul_rअगर_id(स्थिर काष्ठा mlxsw_sp_rअगर_ipip_lb *lb_rअगर);
u32 mlxsw_sp_ipip_dev_ul_tb_id(स्थिर काष्ठा net_device *ol_dev);
पूर्णांक mlxsw_sp_rअगर_dev_अगरindex(स्थिर काष्ठा mlxsw_sp_rअगर *rअगर);
स्थिर काष्ठा net_device *mlxsw_sp_rअगर_dev(स्थिर काष्ठा mlxsw_sp_rअगर *rअगर);
पूर्णांक mlxsw_sp_rअगर_counter_value_get(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_rअगर *rअगर,
				   क्रमागत mlxsw_sp_rअगर_counter_dir dir,
				   u64 *cnt);
व्योम mlxsw_sp_rअगर_counter_मुक्त(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_rअगर *rअगर,
			       क्रमागत mlxsw_sp_rअगर_counter_dir dir);
पूर्णांक mlxsw_sp_rअगर_counter_alloc(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_rअगर *rअगर,
			       क्रमागत mlxsw_sp_rअगर_counter_dir dir);
काष्ठा mlxsw_sp_neigh_entry *
mlxsw_sp_rअगर_neigh_next(काष्ठा mlxsw_sp_rअगर *rअगर,
			काष्ठा mlxsw_sp_neigh_entry *neigh_entry);
पूर्णांक mlxsw_sp_neigh_entry_type(काष्ठा mlxsw_sp_neigh_entry *neigh_entry);
अचिन्हित अक्षर *
mlxsw_sp_neigh_entry_ha(काष्ठा mlxsw_sp_neigh_entry *neigh_entry);
u32 mlxsw_sp_neigh4_entry_dip(काष्ठा mlxsw_sp_neigh_entry *neigh_entry);
काष्ठा in6_addr *
mlxsw_sp_neigh6_entry_dip(काष्ठा mlxsw_sp_neigh_entry *neigh_entry);

#घोषणा mlxsw_sp_rअगर_neigh_क्रम_each(neigh_entry, rअगर)				\
	क्रम (neigh_entry = mlxsw_sp_rअगर_neigh_next(rअगर, शून्य); neigh_entry;	\
	     neigh_entry = mlxsw_sp_rअगर_neigh_next(rअगर, neigh_entry))
पूर्णांक mlxsw_sp_neigh_counter_get(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_neigh_entry *neigh_entry,
			       u64 *p_counter);
व्योम
mlxsw_sp_neigh_entry_counter_update(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_neigh_entry *neigh_entry,
				    bool adding);
bool mlxsw_sp_neigh_ipv6_ignore(काष्ठा mlxsw_sp_neigh_entry *neigh_entry);
पूर्णांक __mlxsw_sp_ipip_entry_update_tunnel(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_ipip_entry *ipip_entry,
					bool recreate_loopback,
					bool keep_encap,
					bool update_nexthops,
					काष्ठा netlink_ext_ack *extack);
व्योम mlxsw_sp_ipip_entry_demote_tunnel(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_ipip_entry *ipip_entry);
bool
mlxsw_sp_ipip_demote_tunnel_by_saddr(काष्ठा mlxsw_sp *mlxsw_sp,
				     क्रमागत mlxsw_sp_l3proto ul_proto,
				     जोड़ mlxsw_sp_l3addr saddr,
				     u32 ul_tb_id,
				     स्थिर काष्ठा mlxsw_sp_ipip_entry *except);
काष्ठा mlxsw_sp_nexthop *mlxsw_sp_nexthop_next(काष्ठा mlxsw_sp_router *router,
					       काष्ठा mlxsw_sp_nexthop *nh);
bool mlxsw_sp_nexthop_is_क्रमward(स्थिर काष्ठा mlxsw_sp_nexthop *nh);
अचिन्हित अक्षर *mlxsw_sp_nexthop_ha(काष्ठा mlxsw_sp_nexthop *nh);
पूर्णांक mlxsw_sp_nexthop_indexes(काष्ठा mlxsw_sp_nexthop *nh, u32 *p_adj_index,
			     u32 *p_adj_size, u32 *p_adj_hash_index);
काष्ठा mlxsw_sp_rअगर *mlxsw_sp_nexthop_rअगर(काष्ठा mlxsw_sp_nexthop *nh);
bool mlxsw_sp_nexthop_group_has_ipip(काष्ठा mlxsw_sp_nexthop *nh);
#घोषणा mlxsw_sp_nexthop_क्रम_each(nh, router)				\
	क्रम (nh = mlxsw_sp_nexthop_next(router, शून्य); nh;		\
	     nh = mlxsw_sp_nexthop_next(router, nh))
पूर्णांक mlxsw_sp_nexthop_counter_get(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_nexthop *nh, u64 *p_counter);
पूर्णांक mlxsw_sp_nexthop_eth_update(काष्ठा mlxsw_sp *mlxsw_sp, u32 adj_index,
				काष्ठा mlxsw_sp_nexthop *nh, bool क्रमce,
				अक्षर *ratr_pl);
व्योम mlxsw_sp_nexthop_counter_alloc(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_nexthop *nh);
व्योम mlxsw_sp_nexthop_counter_मुक्त(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_nexthop *nh);

अटल अंतरभूत bool mlxsw_sp_l3addr_eq(स्थिर जोड़ mlxsw_sp_l3addr *addr1,
				      स्थिर जोड़ mlxsw_sp_l3addr *addr2)
अणु
	वापस !स_भेद(addr1, addr2, माप(*addr1));
पूर्ण

पूर्णांक mlxsw_sp_ipip_ecn_encap_init(काष्ठा mlxsw_sp *mlxsw_sp);
पूर्णांक mlxsw_sp_ipip_ecn_decap_init(काष्ठा mlxsw_sp *mlxsw_sp);

बाह्य स्थिर काष्ठा mlxsw_sp_router_ll_ops mlxsw_sp_router_ll_xm_ops;

पूर्णांक mlxsw_sp_router_xm_init(काष्ठा mlxsw_sp *mlxsw_sp);
व्योम mlxsw_sp_router_xm_fini(काष्ठा mlxsw_sp *mlxsw_sp);
bool mlxsw_sp_router_xm_ipv4_is_supported(स्थिर काष्ठा mlxsw_sp *mlxsw_sp);

#पूर्ण_अगर /* _MLXSW_ROUTER_H_*/
