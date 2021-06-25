<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2016-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/bitops.h>
#समावेश <linux/in6.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/socket.h>
#समावेश <linux/route.h>
#समावेश <linux/gcd.h>
#समावेश <linux/अगर_macvlan.h>
#समावेश <linux/refcount.h>
#समावेश <linux/jhash.h>
#समावेश <linux/net_namespace.h>
#समावेश <linux/mutex.h>
#समावेश <net/netevent.h>
#समावेश <net/neighbour.h>
#समावेश <net/arp.h>
#समावेश <net/ip_fib.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/nexthop.h>
#समावेश <net/fib_rules.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/l3mdev.h>
#समावेश <net/addrconf.h>
#समावेश <net/ndisc.h>
#समावेश <net/ipv6.h>
#समावेश <net/fib_notअगरier.h>
#समावेश <net/चयनdev.h>

#समावेश "spectrum.h"
#समावेश "core.h"
#समावेश "reg.h"
#समावेश "spectrum_cnt.h"
#समावेश "spectrum_dpipe.h"
#समावेश "spectrum_ipip.h"
#समावेश "spectrum_mr.h"
#समावेश "spectrum_mr_tcam.h"
#समावेश "spectrum_router.h"
#समावेश "spectrum_span.h"

काष्ठा mlxsw_sp_fib;
काष्ठा mlxsw_sp_vr;
काष्ठा mlxsw_sp_lpm_tree;
काष्ठा mlxsw_sp_rअगर_ops;

काष्ठा mlxsw_sp_rअगर अणु
	काष्ठा list_head nexthop_list;
	काष्ठा list_head neigh_list;
	काष्ठा net_device *dev; /* शून्य क्रम underlay RIF */
	काष्ठा mlxsw_sp_fid *fid;
	अचिन्हित अक्षर addr[ETH_ALEN];
	पूर्णांक mtu;
	u16 rअगर_index;
	u16 vr_id;
	स्थिर काष्ठा mlxsw_sp_rअगर_ops *ops;
	काष्ठा mlxsw_sp *mlxsw_sp;

	अचिन्हित पूर्णांक counter_ingress;
	bool counter_ingress_valid;
	अचिन्हित पूर्णांक counter_egress;
	bool counter_egress_valid;
पूर्ण;

काष्ठा mlxsw_sp_rअगर_params अणु
	काष्ठा net_device *dev;
	जोड़ अणु
		u16 प्रणाली_port;
		u16 lag_id;
	पूर्ण;
	u16 vid;
	bool lag;
पूर्ण;

काष्ठा mlxsw_sp_rअगर_subport अणु
	काष्ठा mlxsw_sp_rअगर common;
	refcount_t ref_count;
	जोड़ अणु
		u16 प्रणाली_port;
		u16 lag_id;
	पूर्ण;
	u16 vid;
	bool lag;
पूर्ण;

काष्ठा mlxsw_sp_rअगर_ipip_lb अणु
	काष्ठा mlxsw_sp_rअगर common;
	काष्ठा mlxsw_sp_rअगर_ipip_lb_config lb_config;
	u16 ul_vr_id; /* Reserved क्रम Spectrum-2. */
	u16 ul_rअगर_id; /* Reserved क्रम Spectrum. */
पूर्ण;

काष्ठा mlxsw_sp_rअगर_params_ipip_lb अणु
	काष्ठा mlxsw_sp_rअगर_params common;
	काष्ठा mlxsw_sp_rअगर_ipip_lb_config lb_config;
पूर्ण;

काष्ठा mlxsw_sp_rअगर_ops अणु
	क्रमागत mlxsw_sp_rअगर_type type;
	माप_प्रकार rअगर_size;

	व्योम (*setup)(काष्ठा mlxsw_sp_rअगर *rअगर,
		      स्थिर काष्ठा mlxsw_sp_rअगर_params *params);
	पूर्णांक (*configure)(काष्ठा mlxsw_sp_rअगर *rअगर);
	व्योम (*deconfigure)(काष्ठा mlxsw_sp_rअगर *rअगर);
	काष्ठा mlxsw_sp_fid * (*fid_get)(काष्ठा mlxsw_sp_rअगर *rअगर,
					 काष्ठा netlink_ext_ack *extack);
	व्योम (*fdb_del)(काष्ठा mlxsw_sp_rअगर *rअगर, स्थिर अक्षर *mac);
पूर्ण;

काष्ठा mlxsw_sp_router_ops अणु
	पूर्णांक (*init)(काष्ठा mlxsw_sp *mlxsw_sp);
पूर्ण;

अटल काष्ठा mlxsw_sp_rअगर *
mlxsw_sp_rअगर_find_by_dev(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
			 स्थिर काष्ठा net_device *dev);
अटल व्योम mlxsw_sp_rअगर_destroy(काष्ठा mlxsw_sp_rअगर *rअगर);
अटल व्योम mlxsw_sp_lpm_tree_hold(काष्ठा mlxsw_sp_lpm_tree *lpm_tree);
अटल व्योम mlxsw_sp_lpm_tree_put(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_lpm_tree *lpm_tree);
अटल पूर्णांक mlxsw_sp_vr_lpm_tree_bind(काष्ठा mlxsw_sp *mlxsw_sp,
				     स्थिर काष्ठा mlxsw_sp_fib *fib,
				     u8 tree_id);
अटल पूर्णांक mlxsw_sp_vr_lpm_tree_unbind(काष्ठा mlxsw_sp *mlxsw_sp,
				       स्थिर काष्ठा mlxsw_sp_fib *fib);

अटल अचिन्हित पूर्णांक *
mlxsw_sp_rअगर_p_counter_get(काष्ठा mlxsw_sp_rअगर *rअगर,
			   क्रमागत mlxsw_sp_rअगर_counter_dir dir)
अणु
	चयन (dir) अणु
	हाल MLXSW_SP_RIF_COUNTER_EGRESS:
		वापस &rअगर->counter_egress;
	हाल MLXSW_SP_RIF_COUNTER_INGRESS:
		वापस &rअगर->counter_ingress;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल bool
mlxsw_sp_rअगर_counter_valid_get(काष्ठा mlxsw_sp_rअगर *rअगर,
			       क्रमागत mlxsw_sp_rअगर_counter_dir dir)
अणु
	चयन (dir) अणु
	हाल MLXSW_SP_RIF_COUNTER_EGRESS:
		वापस rअगर->counter_egress_valid;
	हाल MLXSW_SP_RIF_COUNTER_INGRESS:
		वापस rअगर->counter_ingress_valid;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम
mlxsw_sp_rअगर_counter_valid_set(काष्ठा mlxsw_sp_rअगर *rअगर,
			       क्रमागत mlxsw_sp_rअगर_counter_dir dir,
			       bool valid)
अणु
	चयन (dir) अणु
	हाल MLXSW_SP_RIF_COUNTER_EGRESS:
		rअगर->counter_egress_valid = valid;
		अवरोध;
	हाल MLXSW_SP_RIF_COUNTER_INGRESS:
		rअगर->counter_ingress_valid = valid;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_rअगर_counter_edit(काष्ठा mlxsw_sp *mlxsw_sp, u16 rअगर_index,
				     अचिन्हित पूर्णांक counter_index, bool enable,
				     क्रमागत mlxsw_sp_rअगर_counter_dir dir)
अणु
	अक्षर ritr_pl[MLXSW_REG_RITR_LEN];
	bool is_egress = false;
	पूर्णांक err;

	अगर (dir == MLXSW_SP_RIF_COUNTER_EGRESS)
		is_egress = true;
	mlxsw_reg_ritr_rअगर_pack(ritr_pl, rअगर_index);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ritr), ritr_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_ritr_counter_pack(ritr_pl, counter_index, enable,
				    is_egress);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ritr), ritr_pl);
पूर्ण

पूर्णांक mlxsw_sp_rअगर_counter_value_get(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_rअगर *rअगर,
				   क्रमागत mlxsw_sp_rअगर_counter_dir dir, u64 *cnt)
अणु
	अक्षर ricnt_pl[MLXSW_REG_RICNT_LEN];
	अचिन्हित पूर्णांक *p_counter_index;
	bool valid;
	पूर्णांक err;

	valid = mlxsw_sp_rअगर_counter_valid_get(rअगर, dir);
	अगर (!valid)
		वापस -EINVAL;

	p_counter_index = mlxsw_sp_rअगर_p_counter_get(rअगर, dir);
	अगर (!p_counter_index)
		वापस -EINVAL;
	mlxsw_reg_ricnt_pack(ricnt_pl, *p_counter_index,
			     MLXSW_REG_RICNT_OPCODE_NOP);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ricnt), ricnt_pl);
	अगर (err)
		वापस err;
	*cnt = mlxsw_reg_ricnt_good_unicast_packets_get(ricnt_pl);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_rअगर_counter_clear(काष्ठा mlxsw_sp *mlxsw_sp,
				      अचिन्हित पूर्णांक counter_index)
अणु
	अक्षर ricnt_pl[MLXSW_REG_RICNT_LEN];

	mlxsw_reg_ricnt_pack(ricnt_pl, counter_index,
			     MLXSW_REG_RICNT_OPCODE_CLEAR);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ricnt), ricnt_pl);
पूर्ण

पूर्णांक mlxsw_sp_rअगर_counter_alloc(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_rअगर *rअगर,
			       क्रमागत mlxsw_sp_rअगर_counter_dir dir)
अणु
	अचिन्हित पूर्णांक *p_counter_index;
	पूर्णांक err;

	p_counter_index = mlxsw_sp_rअगर_p_counter_get(rअगर, dir);
	अगर (!p_counter_index)
		वापस -EINVAL;
	err = mlxsw_sp_counter_alloc(mlxsw_sp, MLXSW_SP_COUNTER_SUB_POOL_RIF,
				     p_counter_index);
	अगर (err)
		वापस err;

	err = mlxsw_sp_rअगर_counter_clear(mlxsw_sp, *p_counter_index);
	अगर (err)
		जाओ err_counter_clear;

	err = mlxsw_sp_rअगर_counter_edit(mlxsw_sp, rअगर->rअगर_index,
					*p_counter_index, true, dir);
	अगर (err)
		जाओ err_counter_edit;
	mlxsw_sp_rअगर_counter_valid_set(rअगर, dir, true);
	वापस 0;

err_counter_edit:
err_counter_clear:
	mlxsw_sp_counter_मुक्त(mlxsw_sp, MLXSW_SP_COUNTER_SUB_POOL_RIF,
			      *p_counter_index);
	वापस err;
पूर्ण

व्योम mlxsw_sp_rअगर_counter_मुक्त(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_rअगर *rअगर,
			       क्रमागत mlxsw_sp_rअगर_counter_dir dir)
अणु
	अचिन्हित पूर्णांक *p_counter_index;

	अगर (!mlxsw_sp_rअगर_counter_valid_get(rअगर, dir))
		वापस;

	p_counter_index = mlxsw_sp_rअगर_p_counter_get(rअगर, dir);
	अगर (WARN_ON(!p_counter_index))
		वापस;
	mlxsw_sp_rअगर_counter_edit(mlxsw_sp, rअगर->rअगर_index,
				  *p_counter_index, false, dir);
	mlxsw_sp_counter_मुक्त(mlxsw_sp, MLXSW_SP_COUNTER_SUB_POOL_RIF,
			      *p_counter_index);
	mlxsw_sp_rअगर_counter_valid_set(rअगर, dir, false);
पूर्ण

अटल व्योम mlxsw_sp_rअगर_counters_alloc(काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = rअगर->mlxsw_sp;
	काष्ठा devlink *devlink;

	devlink = priv_to_devlink(mlxsw_sp->core);
	अगर (!devlink_dpipe_table_counter_enabled(devlink,
						 MLXSW_SP_DPIPE_TABLE_NAME_ERIF))
		वापस;
	mlxsw_sp_rअगर_counter_alloc(mlxsw_sp, rअगर, MLXSW_SP_RIF_COUNTER_EGRESS);
पूर्ण

अटल व्योम mlxsw_sp_rअगर_counters_मुक्त(काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = rअगर->mlxsw_sp;

	mlxsw_sp_rअगर_counter_मुक्त(mlxsw_sp, rअगर, MLXSW_SP_RIF_COUNTER_EGRESS);
पूर्ण

#घोषणा MLXSW_SP_PREFIX_COUNT (माप(काष्ठा in6_addr) * BITS_PER_BYTE + 1)

काष्ठा mlxsw_sp_prefix_usage अणु
	DECLARE_BITMAP(b, MLXSW_SP_PREFIX_COUNT);
पूर्ण;

#घोषणा mlxsw_sp_prefix_usage_क्रम_each(prefix, prefix_usage) \
	क्रम_each_set_bit(prefix, (prefix_usage)->b, MLXSW_SP_PREFIX_COUNT)

अटल bool
mlxsw_sp_prefix_usage_eq(काष्ठा mlxsw_sp_prefix_usage *prefix_usage1,
			 काष्ठा mlxsw_sp_prefix_usage *prefix_usage2)
अणु
	वापस !स_भेद(prefix_usage1, prefix_usage2, माप(*prefix_usage1));
पूर्ण

अटल व्योम
mlxsw_sp_prefix_usage_cpy(काष्ठा mlxsw_sp_prefix_usage *prefix_usage1,
			  काष्ठा mlxsw_sp_prefix_usage *prefix_usage2)
अणु
	स_नकल(prefix_usage1, prefix_usage2, माप(*prefix_usage1));
पूर्ण

अटल व्योम
mlxsw_sp_prefix_usage_set(काष्ठा mlxsw_sp_prefix_usage *prefix_usage,
			  अचिन्हित अक्षर prefix_len)
अणु
	set_bit(prefix_len, prefix_usage->b);
पूर्ण

अटल व्योम
mlxsw_sp_prefix_usage_clear(काष्ठा mlxsw_sp_prefix_usage *prefix_usage,
			    अचिन्हित अक्षर prefix_len)
अणु
	clear_bit(prefix_len, prefix_usage->b);
पूर्ण

काष्ठा mlxsw_sp_fib_key अणु
	अचिन्हित अक्षर addr[माप(काष्ठा in6_addr)];
	अचिन्हित अक्षर prefix_len;
पूर्ण;

क्रमागत mlxsw_sp_fib_entry_type अणु
	MLXSW_SP_FIB_ENTRY_TYPE_REMOTE,
	MLXSW_SP_FIB_ENTRY_TYPE_LOCAL,
	MLXSW_SP_FIB_ENTRY_TYPE_TRAP,
	MLXSW_SP_FIB_ENTRY_TYPE_BLACKHOLE,
	MLXSW_SP_FIB_ENTRY_TYPE_UNREACHABLE,

	/* This is a special हाल of local delivery, where a packet should be
	 * decapsulated on reception. Note that there is no corresponding ENCAP,
	 * because that's a type of next hop, not of FIB entry. (There can be
	 * several next hops in a REMOTE entry, and some of them may be
	 * encapsulating entries.)
	 */
	MLXSW_SP_FIB_ENTRY_TYPE_IPIP_DECAP,
	MLXSW_SP_FIB_ENTRY_TYPE_NVE_DECAP,
पूर्ण;

काष्ठा mlxsw_sp_nexthop_group_info;
काष्ठा mlxsw_sp_nexthop_group;
काष्ठा mlxsw_sp_fib_entry;

काष्ठा mlxsw_sp_fib_node अणु
	काष्ठा mlxsw_sp_fib_entry *fib_entry;
	काष्ठा list_head list;
	काष्ठा rhash_head ht_node;
	काष्ठा mlxsw_sp_fib *fib;
	काष्ठा mlxsw_sp_fib_key key;
पूर्ण;

काष्ठा mlxsw_sp_fib_entry_decap अणु
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry;
	u32 tunnel_index;
पूर्ण;

अटल काष्ठा mlxsw_sp_fib_entry_priv *
mlxsw_sp_fib_entry_priv_create(स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops)
अणु
	काष्ठा mlxsw_sp_fib_entry_priv *priv;

	अगर (!ll_ops->fib_entry_priv_size)
		/* No need to have priv */
		वापस शून्य;

	priv = kzalloc(माप(*priv) + ll_ops->fib_entry_priv_size, GFP_KERNEL);
	अगर (!priv)
		वापस ERR_PTR(-ENOMEM);
	refcount_set(&priv->refcnt, 1);
	वापस priv;
पूर्ण

अटल व्योम
mlxsw_sp_fib_entry_priv_destroy(काष्ठा mlxsw_sp_fib_entry_priv *priv)
अणु
	kमुक्त(priv);
पूर्ण

अटल व्योम mlxsw_sp_fib_entry_priv_hold(काष्ठा mlxsw_sp_fib_entry_priv *priv)
अणु
	refcount_inc(&priv->refcnt);
पूर्ण

अटल व्योम mlxsw_sp_fib_entry_priv_put(काष्ठा mlxsw_sp_fib_entry_priv *priv)
अणु
	अगर (!priv || !refcount_dec_and_test(&priv->refcnt))
		वापस;
	mlxsw_sp_fib_entry_priv_destroy(priv);
पूर्ण

अटल व्योम mlxsw_sp_fib_entry_op_ctx_priv_hold(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
						काष्ठा mlxsw_sp_fib_entry_priv *priv)
अणु
	अगर (!priv)
		वापस;
	mlxsw_sp_fib_entry_priv_hold(priv);
	list_add(&priv->list, &op_ctx->fib_entry_priv_list);
पूर्ण

अटल व्योम mlxsw_sp_fib_entry_op_ctx_priv_put_all(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx)
अणु
	काष्ठा mlxsw_sp_fib_entry_priv *priv, *पंचांगp;

	list_क्रम_each_entry_safe(priv, पंचांगp, &op_ctx->fib_entry_priv_list, list)
		mlxsw_sp_fib_entry_priv_put(priv);
	INIT_LIST_HEAD(&op_ctx->fib_entry_priv_list);
पूर्ण

काष्ठा mlxsw_sp_fib_entry अणु
	काष्ठा mlxsw_sp_fib_node *fib_node;
	क्रमागत mlxsw_sp_fib_entry_type type;
	काष्ठा list_head nexthop_group_node;
	काष्ठा mlxsw_sp_nexthop_group *nh_group;
	काष्ठा mlxsw_sp_fib_entry_decap decap; /* Valid क्रम decap entries. */
	काष्ठा mlxsw_sp_fib_entry_priv *priv;
पूर्ण;

काष्ठा mlxsw_sp_fib4_entry अणु
	काष्ठा mlxsw_sp_fib_entry common;
	काष्ठा fib_info *fi;
	u32 tb_id;
	u8 tos;
	u8 type;
पूर्ण;

काष्ठा mlxsw_sp_fib6_entry अणु
	काष्ठा mlxsw_sp_fib_entry common;
	काष्ठा list_head rt6_list;
	अचिन्हित पूर्णांक nrt6;
पूर्ण;

काष्ठा mlxsw_sp_rt6 अणु
	काष्ठा list_head list;
	काष्ठा fib6_info *rt;
पूर्ण;

काष्ठा mlxsw_sp_lpm_tree अणु
	u8 id; /* tree ID */
	अचिन्हित पूर्णांक ref_count;
	क्रमागत mlxsw_sp_l3proto proto;
	अचिन्हित दीर्घ prefix_ref_count[MLXSW_SP_PREFIX_COUNT];
	काष्ठा mlxsw_sp_prefix_usage prefix_usage;
पूर्ण;

काष्ठा mlxsw_sp_fib अणु
	काष्ठा rhashtable ht;
	काष्ठा list_head node_list;
	काष्ठा mlxsw_sp_vr *vr;
	काष्ठा mlxsw_sp_lpm_tree *lpm_tree;
	क्रमागत mlxsw_sp_l3proto proto;
	स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops;
पूर्ण;

काष्ठा mlxsw_sp_vr अणु
	u16 id; /* भव router ID */
	u32 tb_id; /* kernel fib table id */
	अचिन्हित पूर्णांक rअगर_count;
	काष्ठा mlxsw_sp_fib *fib4;
	काष्ठा mlxsw_sp_fib *fib6;
	काष्ठा mlxsw_sp_mr_table *mr_table[MLXSW_SP_L3_PROTO_MAX];
	काष्ठा mlxsw_sp_rअगर *ul_rअगर;
	refcount_t ul_rअगर_refcnt;
पूर्ण;

अटल पूर्णांक mlxsw_sp_router_ll_basic_init(काष्ठा mlxsw_sp *mlxsw_sp, u16 vr_id,
					 क्रमागत mlxsw_sp_l3proto proto)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_router_ll_basic_ralta_ग_लिखो(काष्ठा mlxsw_sp *mlxsw_sp, अक्षर *xralta_pl)
अणु
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ralta),
			       xralta_pl + MLXSW_REG_XRALTA_RALTA_OFFSET);
पूर्ण

अटल पूर्णांक mlxsw_sp_router_ll_basic_ralst_ग_लिखो(काष्ठा mlxsw_sp *mlxsw_sp, अक्षर *xralst_pl)
अणु
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ralst),
			       xralst_pl + MLXSW_REG_XRALST_RALST_OFFSET);
पूर्ण

अटल पूर्णांक mlxsw_sp_router_ll_basic_raltb_ग_लिखो(काष्ठा mlxsw_sp *mlxsw_sp, अक्षर *xraltb_pl)
अणु
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(raltb),
			       xraltb_pl + MLXSW_REG_XRALTB_RALTB_OFFSET);
पूर्ण

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_fib_ht_params;

अटल काष्ठा mlxsw_sp_fib *mlxsw_sp_fib_create(काष्ठा mlxsw_sp *mlxsw_sp,
						काष्ठा mlxsw_sp_vr *vr,
						क्रमागत mlxsw_sp_l3proto proto)
अणु
	स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops = mlxsw_sp->router->proto_ll_ops[proto];
	काष्ठा mlxsw_sp_lpm_tree *lpm_tree;
	काष्ठा mlxsw_sp_fib *fib;
	पूर्णांक err;

	err = ll_ops->init(mlxsw_sp, vr->id, proto);
	अगर (err)
		वापस ERR_PTR(err);

	lpm_tree = mlxsw_sp->router->lpm.proto_trees[proto];
	fib = kzalloc(माप(*fib), GFP_KERNEL);
	अगर (!fib)
		वापस ERR_PTR(-ENOMEM);
	err = rhashtable_init(&fib->ht, &mlxsw_sp_fib_ht_params);
	अगर (err)
		जाओ err_rhashtable_init;
	INIT_LIST_HEAD(&fib->node_list);
	fib->proto = proto;
	fib->vr = vr;
	fib->lpm_tree = lpm_tree;
	fib->ll_ops = ll_ops;
	mlxsw_sp_lpm_tree_hold(lpm_tree);
	err = mlxsw_sp_vr_lpm_tree_bind(mlxsw_sp, fib, lpm_tree->id);
	अगर (err)
		जाओ err_lpm_tree_bind;
	वापस fib;

err_lpm_tree_bind:
	mlxsw_sp_lpm_tree_put(mlxsw_sp, lpm_tree);
err_rhashtable_init:
	kमुक्त(fib);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_sp_fib_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_fib *fib)
अणु
	mlxsw_sp_vr_lpm_tree_unbind(mlxsw_sp, fib);
	mlxsw_sp_lpm_tree_put(mlxsw_sp, fib->lpm_tree);
	WARN_ON(!list_empty(&fib->node_list));
	rhashtable_destroy(&fib->ht);
	kमुक्त(fib);
पूर्ण

अटल काष्ठा mlxsw_sp_lpm_tree *
mlxsw_sp_lpm_tree_find_unused(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अटल काष्ठा mlxsw_sp_lpm_tree *lpm_tree;
	पूर्णांक i;

	क्रम (i = 0; i < mlxsw_sp->router->lpm.tree_count; i++) अणु
		lpm_tree = &mlxsw_sp->router->lpm.trees[i];
		अगर (lpm_tree->ref_count == 0)
			वापस lpm_tree;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक mlxsw_sp_lpm_tree_alloc(काष्ठा mlxsw_sp *mlxsw_sp,
				   स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops,
				   काष्ठा mlxsw_sp_lpm_tree *lpm_tree)
अणु
	अक्षर xralta_pl[MLXSW_REG_XRALTA_LEN];

	mlxsw_reg_xralta_pack(xralta_pl, true,
			      (क्रमागत mlxsw_reg_ralxx_protocol) lpm_tree->proto,
			      lpm_tree->id);
	वापस ll_ops->ralta_ग_लिखो(mlxsw_sp, xralta_pl);
पूर्ण

अटल व्योम mlxsw_sp_lpm_tree_मुक्त(काष्ठा mlxsw_sp *mlxsw_sp,
				   स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops,
				   काष्ठा mlxsw_sp_lpm_tree *lpm_tree)
अणु
	अक्षर xralta_pl[MLXSW_REG_XRALTA_LEN];

	mlxsw_reg_xralta_pack(xralta_pl, false,
			      (क्रमागत mlxsw_reg_ralxx_protocol) lpm_tree->proto,
			      lpm_tree->id);
	ll_ops->ralta_ग_लिखो(mlxsw_sp, xralta_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_lpm_tree_left_काष्ठा_set(काष्ठा mlxsw_sp *mlxsw_sp,
				  स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops,
				  काष्ठा mlxsw_sp_prefix_usage *prefix_usage,
				  काष्ठा mlxsw_sp_lpm_tree *lpm_tree)
अणु
	अक्षर xralst_pl[MLXSW_REG_XRALST_LEN];
	u8 root_bin = 0;
	u8 prefix;
	u8 last_prefix = MLXSW_REG_RALST_BIN_NO_CHILD;

	mlxsw_sp_prefix_usage_क्रम_each(prefix, prefix_usage)
		root_bin = prefix;

	mlxsw_reg_xralst_pack(xralst_pl, root_bin, lpm_tree->id);
	mlxsw_sp_prefix_usage_क्रम_each(prefix, prefix_usage) अणु
		अगर (prefix == 0)
			जारी;
		mlxsw_reg_xralst_bin_pack(xralst_pl, prefix, last_prefix,
					  MLXSW_REG_RALST_BIN_NO_CHILD);
		last_prefix = prefix;
	पूर्ण
	वापस ll_ops->ralst_ग_लिखो(mlxsw_sp, xralst_pl);
पूर्ण

अटल काष्ठा mlxsw_sp_lpm_tree *
mlxsw_sp_lpm_tree_create(काष्ठा mlxsw_sp *mlxsw_sp,
			 स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops,
			 काष्ठा mlxsw_sp_prefix_usage *prefix_usage,
			 क्रमागत mlxsw_sp_l3proto proto)
अणु
	काष्ठा mlxsw_sp_lpm_tree *lpm_tree;
	पूर्णांक err;

	lpm_tree = mlxsw_sp_lpm_tree_find_unused(mlxsw_sp);
	अगर (!lpm_tree)
		वापस ERR_PTR(-EBUSY);
	lpm_tree->proto = proto;
	err = mlxsw_sp_lpm_tree_alloc(mlxsw_sp, ll_ops, lpm_tree);
	अगर (err)
		वापस ERR_PTR(err);

	err = mlxsw_sp_lpm_tree_left_काष्ठा_set(mlxsw_sp, ll_ops, prefix_usage, lpm_tree);
	अगर (err)
		जाओ err_left_काष्ठा_set;
	स_नकल(&lpm_tree->prefix_usage, prefix_usage,
	       माप(lpm_tree->prefix_usage));
	स_रखो(&lpm_tree->prefix_ref_count, 0,
	       माप(lpm_tree->prefix_ref_count));
	lpm_tree->ref_count = 1;
	वापस lpm_tree;

err_left_काष्ठा_set:
	mlxsw_sp_lpm_tree_मुक्त(mlxsw_sp, ll_ops, lpm_tree);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_sp_lpm_tree_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
				      स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops,
				      काष्ठा mlxsw_sp_lpm_tree *lpm_tree)
अणु
	mlxsw_sp_lpm_tree_मुक्त(mlxsw_sp, ll_ops, lpm_tree);
पूर्ण

अटल काष्ठा mlxsw_sp_lpm_tree *
mlxsw_sp_lpm_tree_get(काष्ठा mlxsw_sp *mlxsw_sp,
		      काष्ठा mlxsw_sp_prefix_usage *prefix_usage,
		      क्रमागत mlxsw_sp_l3proto proto)
अणु
	स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops = mlxsw_sp->router->proto_ll_ops[proto];
	काष्ठा mlxsw_sp_lpm_tree *lpm_tree;
	पूर्णांक i;

	क्रम (i = 0; i < mlxsw_sp->router->lpm.tree_count; i++) अणु
		lpm_tree = &mlxsw_sp->router->lpm.trees[i];
		अगर (lpm_tree->ref_count != 0 &&
		    lpm_tree->proto == proto &&
		    mlxsw_sp_prefix_usage_eq(&lpm_tree->prefix_usage,
					     prefix_usage)) अणु
			mlxsw_sp_lpm_tree_hold(lpm_tree);
			वापस lpm_tree;
		पूर्ण
	पूर्ण
	वापस mlxsw_sp_lpm_tree_create(mlxsw_sp, ll_ops, prefix_usage, proto);
पूर्ण

अटल व्योम mlxsw_sp_lpm_tree_hold(काष्ठा mlxsw_sp_lpm_tree *lpm_tree)
अणु
	lpm_tree->ref_count++;
पूर्ण

अटल व्योम mlxsw_sp_lpm_tree_put(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_lpm_tree *lpm_tree)
अणु
	स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops =
				mlxsw_sp->router->proto_ll_ops[lpm_tree->proto];

	अगर (--lpm_tree->ref_count == 0)
		mlxsw_sp_lpm_tree_destroy(mlxsw_sp, ll_ops, lpm_tree);
पूर्ण

#घोषणा MLXSW_SP_LPM_TREE_MIN 1 /* tree 0 is reserved */

अटल पूर्णांक mlxsw_sp_lpm_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_prefix_usage req_prefix_usage = अणुअणु 0 पूर्ण पूर्ण;
	काष्ठा mlxsw_sp_lpm_tree *lpm_tree;
	u64 max_trees;
	पूर्णांक err, i;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, MAX_LPM_TREES))
		वापस -EIO;

	max_trees = MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_LPM_TREES);
	mlxsw_sp->router->lpm.tree_count = max_trees - MLXSW_SP_LPM_TREE_MIN;
	mlxsw_sp->router->lpm.trees = kसुस्मृति(mlxsw_sp->router->lpm.tree_count,
					     माप(काष्ठा mlxsw_sp_lpm_tree),
					     GFP_KERNEL);
	अगर (!mlxsw_sp->router->lpm.trees)
		वापस -ENOMEM;

	क्रम (i = 0; i < mlxsw_sp->router->lpm.tree_count; i++) अणु
		lpm_tree = &mlxsw_sp->router->lpm.trees[i];
		lpm_tree->id = i + MLXSW_SP_LPM_TREE_MIN;
	पूर्ण

	lpm_tree = mlxsw_sp_lpm_tree_get(mlxsw_sp, &req_prefix_usage,
					 MLXSW_SP_L3_PROTO_IPV4);
	अगर (IS_ERR(lpm_tree)) अणु
		err = PTR_ERR(lpm_tree);
		जाओ err_ipv4_tree_get;
	पूर्ण
	mlxsw_sp->router->lpm.proto_trees[MLXSW_SP_L3_PROTO_IPV4] = lpm_tree;

	lpm_tree = mlxsw_sp_lpm_tree_get(mlxsw_sp, &req_prefix_usage,
					 MLXSW_SP_L3_PROTO_IPV6);
	अगर (IS_ERR(lpm_tree)) अणु
		err = PTR_ERR(lpm_tree);
		जाओ err_ipv6_tree_get;
	पूर्ण
	mlxsw_sp->router->lpm.proto_trees[MLXSW_SP_L3_PROTO_IPV6] = lpm_tree;

	वापस 0;

err_ipv6_tree_get:
	lpm_tree = mlxsw_sp->router->lpm.proto_trees[MLXSW_SP_L3_PROTO_IPV4];
	mlxsw_sp_lpm_tree_put(mlxsw_sp, lpm_tree);
err_ipv4_tree_get:
	kमुक्त(mlxsw_sp->router->lpm.trees);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_lpm_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_lpm_tree *lpm_tree;

	lpm_tree = mlxsw_sp->router->lpm.proto_trees[MLXSW_SP_L3_PROTO_IPV6];
	mlxsw_sp_lpm_tree_put(mlxsw_sp, lpm_tree);

	lpm_tree = mlxsw_sp->router->lpm.proto_trees[MLXSW_SP_L3_PROTO_IPV4];
	mlxsw_sp_lpm_tree_put(mlxsw_sp, lpm_tree);

	kमुक्त(mlxsw_sp->router->lpm.trees);
पूर्ण

अटल bool mlxsw_sp_vr_is_used(स्थिर काष्ठा mlxsw_sp_vr *vr)
अणु
	वापस !!vr->fib4 || !!vr->fib6 ||
	       !!vr->mr_table[MLXSW_SP_L3_PROTO_IPV4] ||
	       !!vr->mr_table[MLXSW_SP_L3_PROTO_IPV6];
पूर्ण

अटल काष्ठा mlxsw_sp_vr *mlxsw_sp_vr_find_unused(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_vr *vr;
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_VRS); i++) अणु
		vr = &mlxsw_sp->router->vrs[i];
		अगर (!mlxsw_sp_vr_is_used(vr))
			वापस vr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक mlxsw_sp_vr_lpm_tree_bind(काष्ठा mlxsw_sp *mlxsw_sp,
				     स्थिर काष्ठा mlxsw_sp_fib *fib, u8 tree_id)
अणु
	अक्षर xraltb_pl[MLXSW_REG_XRALTB_LEN];

	mlxsw_reg_xraltb_pack(xraltb_pl, fib->vr->id,
			      (क्रमागत mlxsw_reg_ralxx_protocol) fib->proto,
			      tree_id);
	वापस fib->ll_ops->raltb_ग_लिखो(mlxsw_sp, xraltb_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_vr_lpm_tree_unbind(काष्ठा mlxsw_sp *mlxsw_sp,
				       स्थिर काष्ठा mlxsw_sp_fib *fib)
अणु
	अक्षर xraltb_pl[MLXSW_REG_XRALTB_LEN];

	/* Bind to tree 0 which is शेष */
	mlxsw_reg_xraltb_pack(xraltb_pl, fib->vr->id,
			      (क्रमागत mlxsw_reg_ralxx_protocol) fib->proto, 0);
	वापस fib->ll_ops->raltb_ग_लिखो(mlxsw_sp, xraltb_pl);
पूर्ण

अटल u32 mlxsw_sp_fix_tb_id(u32 tb_id)
अणु
	/* For our purpose, squash मुख्य, शेष and local tables पूर्णांकo one */
	अगर (tb_id == RT_TABLE_LOCAL || tb_id == RT_TABLE_DEFAULT)
		tb_id = RT_TABLE_MAIN;
	वापस tb_id;
पूर्ण

अटल काष्ठा mlxsw_sp_vr *mlxsw_sp_vr_find(काष्ठा mlxsw_sp *mlxsw_sp,
					    u32 tb_id)
अणु
	काष्ठा mlxsw_sp_vr *vr;
	पूर्णांक i;

	tb_id = mlxsw_sp_fix_tb_id(tb_id);

	क्रम (i = 0; i < MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_VRS); i++) अणु
		vr = &mlxsw_sp->router->vrs[i];
		अगर (mlxsw_sp_vr_is_used(vr) && vr->tb_id == tb_id)
			वापस vr;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक mlxsw_sp_router_tb_id_vr_id(काष्ठा mlxsw_sp *mlxsw_sp, u32 tb_id,
				u16 *vr_id)
अणु
	काष्ठा mlxsw_sp_vr *vr;
	पूर्णांक err = 0;

	mutex_lock(&mlxsw_sp->router->lock);
	vr = mlxsw_sp_vr_find(mlxsw_sp, tb_id);
	अगर (!vr) अणु
		err = -ESRCH;
		जाओ out;
	पूर्ण
	*vr_id = vr->id;
out:
	mutex_unlock(&mlxsw_sp->router->lock);
	वापस err;
पूर्ण

अटल काष्ठा mlxsw_sp_fib *mlxsw_sp_vr_fib(स्थिर काष्ठा mlxsw_sp_vr *vr,
					    क्रमागत mlxsw_sp_l3proto proto)
अणु
	चयन (proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		वापस vr->fib4;
	हाल MLXSW_SP_L3_PROTO_IPV6:
		वापस vr->fib6;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mlxsw_sp_vr *mlxsw_sp_vr_create(काष्ठा mlxsw_sp *mlxsw_sp,
					      u32 tb_id,
					      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_mr_table *mr4_table, *mr6_table;
	काष्ठा mlxsw_sp_fib *fib4;
	काष्ठा mlxsw_sp_fib *fib6;
	काष्ठा mlxsw_sp_vr *vr;
	पूर्णांक err;

	vr = mlxsw_sp_vr_find_unused(mlxsw_sp);
	अगर (!vr) अणु
		NL_SET_ERR_MSG_MOD(extack, "Exceeded number of supported virtual routers");
		वापस ERR_PTR(-EBUSY);
	पूर्ण
	fib4 = mlxsw_sp_fib_create(mlxsw_sp, vr, MLXSW_SP_L3_PROTO_IPV4);
	अगर (IS_ERR(fib4))
		वापस ERR_CAST(fib4);
	fib6 = mlxsw_sp_fib_create(mlxsw_sp, vr, MLXSW_SP_L3_PROTO_IPV6);
	अगर (IS_ERR(fib6)) अणु
		err = PTR_ERR(fib6);
		जाओ err_fib6_create;
	पूर्ण
	mr4_table = mlxsw_sp_mr_table_create(mlxsw_sp, vr->id,
					     MLXSW_SP_L3_PROTO_IPV4);
	अगर (IS_ERR(mr4_table)) अणु
		err = PTR_ERR(mr4_table);
		जाओ err_mr4_table_create;
	पूर्ण
	mr6_table = mlxsw_sp_mr_table_create(mlxsw_sp, vr->id,
					     MLXSW_SP_L3_PROTO_IPV6);
	अगर (IS_ERR(mr6_table)) अणु
		err = PTR_ERR(mr6_table);
		जाओ err_mr6_table_create;
	पूर्ण

	vr->fib4 = fib4;
	vr->fib6 = fib6;
	vr->mr_table[MLXSW_SP_L3_PROTO_IPV4] = mr4_table;
	vr->mr_table[MLXSW_SP_L3_PROTO_IPV6] = mr6_table;
	vr->tb_id = tb_id;
	वापस vr;

err_mr6_table_create:
	mlxsw_sp_mr_table_destroy(mr4_table);
err_mr4_table_create:
	mlxsw_sp_fib_destroy(mlxsw_sp, fib6);
err_fib6_create:
	mlxsw_sp_fib_destroy(mlxsw_sp, fib4);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_sp_vr_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_vr *vr)
अणु
	mlxsw_sp_mr_table_destroy(vr->mr_table[MLXSW_SP_L3_PROTO_IPV6]);
	vr->mr_table[MLXSW_SP_L3_PROTO_IPV6] = शून्य;
	mlxsw_sp_mr_table_destroy(vr->mr_table[MLXSW_SP_L3_PROTO_IPV4]);
	vr->mr_table[MLXSW_SP_L3_PROTO_IPV4] = शून्य;
	mlxsw_sp_fib_destroy(mlxsw_sp, vr->fib6);
	vr->fib6 = शून्य;
	mlxsw_sp_fib_destroy(mlxsw_sp, vr->fib4);
	vr->fib4 = शून्य;
पूर्ण

अटल काष्ठा mlxsw_sp_vr *mlxsw_sp_vr_get(काष्ठा mlxsw_sp *mlxsw_sp, u32 tb_id,
					   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_vr *vr;

	tb_id = mlxsw_sp_fix_tb_id(tb_id);
	vr = mlxsw_sp_vr_find(mlxsw_sp, tb_id);
	अगर (!vr)
		vr = mlxsw_sp_vr_create(mlxsw_sp, tb_id, extack);
	वापस vr;
पूर्ण

अटल व्योम mlxsw_sp_vr_put(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा mlxsw_sp_vr *vr)
अणु
	अगर (!vr->rअगर_count && list_empty(&vr->fib4->node_list) &&
	    list_empty(&vr->fib6->node_list) &&
	    mlxsw_sp_mr_table_empty(vr->mr_table[MLXSW_SP_L3_PROTO_IPV4]) &&
	    mlxsw_sp_mr_table_empty(vr->mr_table[MLXSW_SP_L3_PROTO_IPV6]))
		mlxsw_sp_vr_destroy(mlxsw_sp, vr);
पूर्ण

अटल bool
mlxsw_sp_vr_lpm_tree_should_replace(काष्ठा mlxsw_sp_vr *vr,
				    क्रमागत mlxsw_sp_l3proto proto, u8 tree_id)
अणु
	काष्ठा mlxsw_sp_fib *fib = mlxsw_sp_vr_fib(vr, proto);

	अगर (!mlxsw_sp_vr_is_used(vr))
		वापस false;
	अगर (fib->lpm_tree->id == tree_id)
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक mlxsw_sp_vr_lpm_tree_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_fib *fib,
					काष्ठा mlxsw_sp_lpm_tree *new_tree)
अणु
	काष्ठा mlxsw_sp_lpm_tree *old_tree = fib->lpm_tree;
	पूर्णांक err;

	fib->lpm_tree = new_tree;
	mlxsw_sp_lpm_tree_hold(new_tree);
	err = mlxsw_sp_vr_lpm_tree_bind(mlxsw_sp, fib, new_tree->id);
	अगर (err)
		जाओ err_tree_bind;
	mlxsw_sp_lpm_tree_put(mlxsw_sp, old_tree);
	वापस 0;

err_tree_bind:
	mlxsw_sp_lpm_tree_put(mlxsw_sp, new_tree);
	fib->lpm_tree = old_tree;
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_vrs_lpm_tree_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					 काष्ठा mlxsw_sp_fib *fib,
					 काष्ठा mlxsw_sp_lpm_tree *new_tree)
अणु
	क्रमागत mlxsw_sp_l3proto proto = fib->proto;
	काष्ठा mlxsw_sp_lpm_tree *old_tree;
	u8 old_id, new_id = new_tree->id;
	काष्ठा mlxsw_sp_vr *vr;
	पूर्णांक i, err;

	old_tree = mlxsw_sp->router->lpm.proto_trees[proto];
	old_id = old_tree->id;

	क्रम (i = 0; i < MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_VRS); i++) अणु
		vr = &mlxsw_sp->router->vrs[i];
		अगर (!mlxsw_sp_vr_lpm_tree_should_replace(vr, proto, old_id))
			जारी;
		err = mlxsw_sp_vr_lpm_tree_replace(mlxsw_sp,
						   mlxsw_sp_vr_fib(vr, proto),
						   new_tree);
		अगर (err)
			जाओ err_tree_replace;
	पूर्ण

	स_नकल(new_tree->prefix_ref_count, old_tree->prefix_ref_count,
	       माप(new_tree->prefix_ref_count));
	mlxsw_sp->router->lpm.proto_trees[proto] = new_tree;
	mlxsw_sp_lpm_tree_put(mlxsw_sp, old_tree);

	वापस 0;

err_tree_replace:
	क्रम (i--; i >= 0; i--) अणु
		अगर (!mlxsw_sp_vr_lpm_tree_should_replace(vr, proto, new_id))
			जारी;
		mlxsw_sp_vr_lpm_tree_replace(mlxsw_sp,
					     mlxsw_sp_vr_fib(vr, proto),
					     old_tree);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_vrs_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_vr *vr;
	u64 max_vrs;
	पूर्णांक i;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, MAX_VRS))
		वापस -EIO;

	max_vrs = MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_VRS);
	mlxsw_sp->router->vrs = kसुस्मृति(max_vrs, माप(काष्ठा mlxsw_sp_vr),
					GFP_KERNEL);
	अगर (!mlxsw_sp->router->vrs)
		वापस -ENOMEM;

	क्रम (i = 0; i < max_vrs; i++) अणु
		vr = &mlxsw_sp->router->vrs[i];
		vr->id = i;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_router_fib_flush(काष्ठा mlxsw_sp *mlxsw_sp);

अटल व्योम mlxsw_sp_vrs_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	/* At this stage we're guaranteed not to have new incoming
	 * FIB notअगरications and the work queue is मुक्त from FIBs
	 * sitting on top of mlxsw netdevs. However, we can still
	 * have other FIBs queued. Flush the queue beक्रमe flushing
	 * the device's tables. No need for locks, as we're the only
	 * ग_लिखोr.
	 */
	mlxsw_core_flush_owq();
	mlxsw_sp_router_fib_flush(mlxsw_sp);
	kमुक्त(mlxsw_sp->router->vrs);
पूर्ण

अटल काष्ठा net_device *
__mlxsw_sp_ipip_netdev_ul_dev_get(स्थिर काष्ठा net_device *ol_dev)
अणु
	काष्ठा ip_tunnel *tun = netdev_priv(ol_dev);
	काष्ठा net *net = dev_net(ol_dev);

	वापस dev_get_by_index_rcu(net, tun->parms.link);
पूर्ण

u32 mlxsw_sp_ipip_dev_ul_tb_id(स्थिर काष्ठा net_device *ol_dev)
अणु
	काष्ठा net_device *d;
	u32 tb_id;

	rcu_पढ़ो_lock();
	d = __mlxsw_sp_ipip_netdev_ul_dev_get(ol_dev);
	अगर (d)
		tb_id = l3mdev_fib_table(d) ? : RT_TABLE_MAIN;
	अन्यथा
		tb_id = RT_TABLE_MAIN;
	rcu_पढ़ो_unlock();

	वापस tb_id;
पूर्ण

अटल काष्ठा mlxsw_sp_rअगर *
mlxsw_sp_rअगर_create(काष्ठा mlxsw_sp *mlxsw_sp,
		    स्थिर काष्ठा mlxsw_sp_rअगर_params *params,
		    काष्ठा netlink_ext_ack *extack);

अटल काष्ठा mlxsw_sp_rअगर_ipip_lb *
mlxsw_sp_ipip_ol_ipip_lb_create(काष्ठा mlxsw_sp *mlxsw_sp,
				क्रमागत mlxsw_sp_ipip_type ipipt,
				काष्ठा net_device *ol_dev,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_rअगर_params_ipip_lb lb_params;
	स्थिर काष्ठा mlxsw_sp_ipip_ops *ipip_ops;
	काष्ठा mlxsw_sp_rअगर *rअगर;

	ipip_ops = mlxsw_sp->router->ipip_ops_arr[ipipt];
	lb_params = (काष्ठा mlxsw_sp_rअगर_params_ipip_lb) अणु
		.common.dev = ol_dev,
		.common.lag = false,
		.lb_config = ipip_ops->ol_loopback_config(mlxsw_sp, ol_dev),
	पूर्ण;

	rअगर = mlxsw_sp_rअगर_create(mlxsw_sp, &lb_params.common, extack);
	अगर (IS_ERR(rअगर))
		वापस ERR_CAST(rअगर);
	वापस container_of(rअगर, काष्ठा mlxsw_sp_rअगर_ipip_lb, common);
पूर्ण

अटल काष्ठा mlxsw_sp_ipip_entry *
mlxsw_sp_ipip_entry_alloc(काष्ठा mlxsw_sp *mlxsw_sp,
			  क्रमागत mlxsw_sp_ipip_type ipipt,
			  काष्ठा net_device *ol_dev)
अणु
	स्थिर काष्ठा mlxsw_sp_ipip_ops *ipip_ops;
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry;
	काष्ठा mlxsw_sp_ipip_entry *ret = शून्य;

	ipip_ops = mlxsw_sp->router->ipip_ops_arr[ipipt];
	ipip_entry = kzalloc(माप(*ipip_entry), GFP_KERNEL);
	अगर (!ipip_entry)
		वापस ERR_PTR(-ENOMEM);

	ipip_entry->ol_lb = mlxsw_sp_ipip_ol_ipip_lb_create(mlxsw_sp, ipipt,
							    ol_dev, शून्य);
	अगर (IS_ERR(ipip_entry->ol_lb)) अणु
		ret = ERR_CAST(ipip_entry->ol_lb);
		जाओ err_ol_ipip_lb_create;
	पूर्ण

	ipip_entry->ipipt = ipipt;
	ipip_entry->ol_dev = ol_dev;

	चयन (ipip_ops->ul_proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		ipip_entry->parms4 = mlxsw_sp_ipip_netdev_parms4(ol_dev);
		अवरोध;
	हाल MLXSW_SP_L3_PROTO_IPV6:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	वापस ipip_entry;

err_ol_ipip_lb_create:
	kमुक्त(ipip_entry);
	वापस ret;
पूर्ण

अटल व्योम
mlxsw_sp_ipip_entry_dealloc(काष्ठा mlxsw_sp_ipip_entry *ipip_entry)
अणु
	mlxsw_sp_rअगर_destroy(&ipip_entry->ol_lb->common);
	kमुक्त(ipip_entry);
पूर्ण

अटल bool
mlxsw_sp_ipip_entry_saddr_matches(काष्ठा mlxsw_sp *mlxsw_sp,
				  स्थिर क्रमागत mlxsw_sp_l3proto ul_proto,
				  जोड़ mlxsw_sp_l3addr saddr,
				  u32 ul_tb_id,
				  काष्ठा mlxsw_sp_ipip_entry *ipip_entry)
अणु
	u32 tun_ul_tb_id = mlxsw_sp_ipip_dev_ul_tb_id(ipip_entry->ol_dev);
	क्रमागत mlxsw_sp_ipip_type ipipt = ipip_entry->ipipt;
	जोड़ mlxsw_sp_l3addr tun_saddr;

	अगर (mlxsw_sp->router->ipip_ops_arr[ipipt]->ul_proto != ul_proto)
		वापस false;

	tun_saddr = mlxsw_sp_ipip_netdev_saddr(ul_proto, ipip_entry->ol_dev);
	वापस tun_ul_tb_id == ul_tb_id &&
	       mlxsw_sp_l3addr_eq(&tun_saddr, &saddr);
पूर्ण

अटल पूर्णांक
mlxsw_sp_fib_entry_decap_init(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_fib_entry *fib_entry,
			      काष्ठा mlxsw_sp_ipip_entry *ipip_entry)
अणु
	u32 tunnel_index;
	पूर्णांक err;

	err = mlxsw_sp_kvdl_alloc(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ,
				  1, &tunnel_index);
	अगर (err)
		वापस err;

	ipip_entry->decap_fib_entry = fib_entry;
	fib_entry->decap.ipip_entry = ipip_entry;
	fib_entry->decap.tunnel_index = tunnel_index;
	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_fib_entry_decap_fini(काष्ठा mlxsw_sp *mlxsw_sp,
					  काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	/* Unlink this node from the IPIP entry that it's the decap entry of. */
	fib_entry->decap.ipip_entry->decap_fib_entry = शून्य;
	fib_entry->decap.ipip_entry = शून्य;
	mlxsw_sp_kvdl_मुक्त(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ,
			   1, fib_entry->decap.tunnel_index);
पूर्ण

अटल काष्ठा mlxsw_sp_fib_node *
mlxsw_sp_fib_node_lookup(काष्ठा mlxsw_sp_fib *fib, स्थिर व्योम *addr,
			 माप_प्रकार addr_len, अचिन्हित अक्षर prefix_len);
अटल पूर्णांक mlxsw_sp_fib_entry_update(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_fib_entry *fib_entry);

अटल व्योम
mlxsw_sp_ipip_entry_demote_decap(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_ipip_entry *ipip_entry)
अणु
	काष्ठा mlxsw_sp_fib_entry *fib_entry = ipip_entry->decap_fib_entry;

	mlxsw_sp_fib_entry_decap_fini(mlxsw_sp, fib_entry);
	fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_TRAP;

	mlxsw_sp_fib_entry_update(mlxsw_sp, fib_entry);
पूर्ण

अटल व्योम
mlxsw_sp_ipip_entry_promote_decap(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_ipip_entry *ipip_entry,
				  काष्ठा mlxsw_sp_fib_entry *decap_fib_entry)
अणु
	अगर (mlxsw_sp_fib_entry_decap_init(mlxsw_sp, decap_fib_entry,
					  ipip_entry))
		वापस;
	decap_fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_IPIP_DECAP;

	अगर (mlxsw_sp_fib_entry_update(mlxsw_sp, decap_fib_entry))
		mlxsw_sp_ipip_entry_demote_decap(mlxsw_sp, ipip_entry);
पूर्ण

अटल काष्ठा mlxsw_sp_fib_entry *
mlxsw_sp_router_ip2me_fib_entry_find(काष्ठा mlxsw_sp *mlxsw_sp, u32 tb_id,
				     क्रमागत mlxsw_sp_l3proto proto,
				     स्थिर जोड़ mlxsw_sp_l3addr *addr,
				     क्रमागत mlxsw_sp_fib_entry_type type)
अणु
	काष्ठा mlxsw_sp_fib_node *fib_node;
	अचिन्हित अक्षर addr_prefix_len;
	काष्ठा mlxsw_sp_fib *fib;
	काष्ठा mlxsw_sp_vr *vr;
	स्थिर व्योम *addrp;
	माप_प्रकार addr_len;
	u32 addr4;

	vr = mlxsw_sp_vr_find(mlxsw_sp, tb_id);
	अगर (!vr)
		वापस शून्य;
	fib = mlxsw_sp_vr_fib(vr, proto);

	चयन (proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		addr4 = be32_to_cpu(addr->addr4);
		addrp = &addr4;
		addr_len = 4;
		addr_prefix_len = 32;
		अवरोध;
	हाल MLXSW_SP_L3_PROTO_IPV6:
	शेष:
		WARN_ON(1);
		वापस शून्य;
	पूर्ण

	fib_node = mlxsw_sp_fib_node_lookup(fib, addrp, addr_len,
					    addr_prefix_len);
	अगर (!fib_node || fib_node->fib_entry->type != type)
		वापस शून्य;

	वापस fib_node->fib_entry;
पूर्ण

/* Given an IPIP entry, find the corresponding decap route. */
अटल काष्ठा mlxsw_sp_fib_entry *
mlxsw_sp_ipip_entry_find_decap(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_ipip_entry *ipip_entry)
अणु
	अटल काष्ठा mlxsw_sp_fib_node *fib_node;
	स्थिर काष्ठा mlxsw_sp_ipip_ops *ipip_ops;
	अचिन्हित अक्षर saddr_prefix_len;
	जोड़ mlxsw_sp_l3addr saddr;
	काष्ठा mlxsw_sp_fib *ul_fib;
	काष्ठा mlxsw_sp_vr *ul_vr;
	स्थिर व्योम *saddrp;
	माप_प्रकार saddr_len;
	u32 ul_tb_id;
	u32 saddr4;

	ipip_ops = mlxsw_sp->router->ipip_ops_arr[ipip_entry->ipipt];

	ul_tb_id = mlxsw_sp_ipip_dev_ul_tb_id(ipip_entry->ol_dev);
	ul_vr = mlxsw_sp_vr_find(mlxsw_sp, ul_tb_id);
	अगर (!ul_vr)
		वापस शून्य;

	ul_fib = mlxsw_sp_vr_fib(ul_vr, ipip_ops->ul_proto);
	saddr = mlxsw_sp_ipip_netdev_saddr(ipip_ops->ul_proto,
					   ipip_entry->ol_dev);

	चयन (ipip_ops->ul_proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		saddr4 = be32_to_cpu(saddr.addr4);
		saddrp = &saddr4;
		saddr_len = 4;
		saddr_prefix_len = 32;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस शून्य;
	पूर्ण

	fib_node = mlxsw_sp_fib_node_lookup(ul_fib, saddrp, saddr_len,
					    saddr_prefix_len);
	अगर (!fib_node ||
	    fib_node->fib_entry->type != MLXSW_SP_FIB_ENTRY_TYPE_TRAP)
		वापस शून्य;

	वापस fib_node->fib_entry;
पूर्ण

अटल काष्ठा mlxsw_sp_ipip_entry *
mlxsw_sp_ipip_entry_create(काष्ठा mlxsw_sp *mlxsw_sp,
			   क्रमागत mlxsw_sp_ipip_type ipipt,
			   काष्ठा net_device *ol_dev)
अणु
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry;

	ipip_entry = mlxsw_sp_ipip_entry_alloc(mlxsw_sp, ipipt, ol_dev);
	अगर (IS_ERR(ipip_entry))
		वापस ipip_entry;

	list_add_tail(&ipip_entry->ipip_list_node,
		      &mlxsw_sp->router->ipip_list);

	वापस ipip_entry;
पूर्ण

अटल व्योम
mlxsw_sp_ipip_entry_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_ipip_entry *ipip_entry)
अणु
	list_del(&ipip_entry->ipip_list_node);
	mlxsw_sp_ipip_entry_dealloc(ipip_entry);
पूर्ण

अटल bool
mlxsw_sp_ipip_entry_matches_decap(काष्ठा mlxsw_sp *mlxsw_sp,
				  स्थिर काष्ठा net_device *ul_dev,
				  क्रमागत mlxsw_sp_l3proto ul_proto,
				  जोड़ mlxsw_sp_l3addr ul_dip,
				  काष्ठा mlxsw_sp_ipip_entry *ipip_entry)
अणु
	u32 ul_tb_id = l3mdev_fib_table(ul_dev) ? : RT_TABLE_MAIN;
	क्रमागत mlxsw_sp_ipip_type ipipt = ipip_entry->ipipt;

	अगर (mlxsw_sp->router->ipip_ops_arr[ipipt]->ul_proto != ul_proto)
		वापस false;

	वापस mlxsw_sp_ipip_entry_saddr_matches(mlxsw_sp, ul_proto, ul_dip,
						 ul_tb_id, ipip_entry);
पूर्ण

/* Given decap parameters, find the corresponding IPIP entry. */
अटल काष्ठा mlxsw_sp_ipip_entry *
mlxsw_sp_ipip_entry_find_by_decap(काष्ठा mlxsw_sp *mlxsw_sp, पूर्णांक ul_dev_अगरindex,
				  क्रमागत mlxsw_sp_l3proto ul_proto,
				  जोड़ mlxsw_sp_l3addr ul_dip)
अणु
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry = शून्य;
	काष्ठा net_device *ul_dev;

	rcu_पढ़ो_lock();

	ul_dev = dev_get_by_index_rcu(mlxsw_sp_net(mlxsw_sp), ul_dev_अगरindex);
	अगर (!ul_dev)
		जाओ out_unlock;

	list_क्रम_each_entry(ipip_entry, &mlxsw_sp->router->ipip_list,
			    ipip_list_node)
		अगर (mlxsw_sp_ipip_entry_matches_decap(mlxsw_sp, ul_dev,
						      ul_proto, ul_dip,
						      ipip_entry))
			जाओ out_unlock;

	rcu_पढ़ो_unlock();

	वापस शून्य;

out_unlock:
	rcu_पढ़ो_unlock();
	वापस ipip_entry;
पूर्ण

अटल bool mlxsw_sp_netdev_ipip_type(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
				      स्थिर काष्ठा net_device *dev,
				      क्रमागत mlxsw_sp_ipip_type *p_type)
अणु
	काष्ठा mlxsw_sp_router *router = mlxsw_sp->router;
	स्थिर काष्ठा mlxsw_sp_ipip_ops *ipip_ops;
	क्रमागत mlxsw_sp_ipip_type ipipt;

	क्रम (ipipt = 0; ipipt < MLXSW_SP_IPIP_TYPE_MAX; ++ipipt) अणु
		ipip_ops = router->ipip_ops_arr[ipipt];
		अगर (dev->type == ipip_ops->dev_type) अणु
			अगर (p_type)
				*p_type = ipipt;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

bool mlxsw_sp_netdev_is_ipip_ol(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
				स्थिर काष्ठा net_device *dev)
अणु
	वापस mlxsw_sp_netdev_ipip_type(mlxsw_sp, dev, शून्य);
पूर्ण

अटल काष्ठा mlxsw_sp_ipip_entry *
mlxsw_sp_ipip_entry_find_by_ol_dev(काष्ठा mlxsw_sp *mlxsw_sp,
				   स्थिर काष्ठा net_device *ol_dev)
अणु
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry;

	list_क्रम_each_entry(ipip_entry, &mlxsw_sp->router->ipip_list,
			    ipip_list_node)
		अगर (ipip_entry->ol_dev == ol_dev)
			वापस ipip_entry;

	वापस शून्य;
पूर्ण

अटल काष्ठा mlxsw_sp_ipip_entry *
mlxsw_sp_ipip_entry_find_by_ul_dev(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
				   स्थिर काष्ठा net_device *ul_dev,
				   काष्ठा mlxsw_sp_ipip_entry *start)
अणु
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry;

	ipip_entry = list_prepare_entry(start, &mlxsw_sp->router->ipip_list,
					ipip_list_node);
	list_क्रम_each_entry_जारी(ipip_entry, &mlxsw_sp->router->ipip_list,
				     ipip_list_node) अणु
		काष्ठा net_device *ol_dev = ipip_entry->ol_dev;
		काष्ठा net_device *ipip_ul_dev;

		rcu_पढ़ो_lock();
		ipip_ul_dev = __mlxsw_sp_ipip_netdev_ul_dev_get(ol_dev);
		rcu_पढ़ो_unlock();

		अगर (ipip_ul_dev == ul_dev)
			वापस ipip_entry;
	पूर्ण

	वापस शून्य;
पूर्ण

bool mlxsw_sp_netdev_is_ipip_ul(काष्ठा mlxsw_sp *mlxsw_sp,
				स्थिर काष्ठा net_device *dev)
अणु
	bool is_ipip_ul;

	mutex_lock(&mlxsw_sp->router->lock);
	is_ipip_ul = mlxsw_sp_ipip_entry_find_by_ul_dev(mlxsw_sp, dev, शून्य);
	mutex_unlock(&mlxsw_sp->router->lock);

	वापस is_ipip_ul;
पूर्ण

अटल bool mlxsw_sp_netdevice_ipip_can_offload(काष्ठा mlxsw_sp *mlxsw_sp,
						स्थिर काष्ठा net_device *ol_dev,
						क्रमागत mlxsw_sp_ipip_type ipipt)
अणु
	स्थिर काष्ठा mlxsw_sp_ipip_ops *ops
		= mlxsw_sp->router->ipip_ops_arr[ipipt];

	वापस ops->can_offload(mlxsw_sp, ol_dev);
पूर्ण

अटल पूर्णांक mlxsw_sp_netdevice_ipip_ol_reg_event(काष्ठा mlxsw_sp *mlxsw_sp,
						काष्ठा net_device *ol_dev)
अणु
	क्रमागत mlxsw_sp_ipip_type ipipt = MLXSW_SP_IPIP_TYPE_MAX;
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry;
	क्रमागत mlxsw_sp_l3proto ul_proto;
	जोड़ mlxsw_sp_l3addr saddr;
	u32 ul_tb_id;

	mlxsw_sp_netdev_ipip_type(mlxsw_sp, ol_dev, &ipipt);
	अगर (mlxsw_sp_netdevice_ipip_can_offload(mlxsw_sp, ol_dev, ipipt)) अणु
		ul_tb_id = mlxsw_sp_ipip_dev_ul_tb_id(ol_dev);
		ul_proto = mlxsw_sp->router->ipip_ops_arr[ipipt]->ul_proto;
		saddr = mlxsw_sp_ipip_netdev_saddr(ul_proto, ol_dev);
		अगर (!mlxsw_sp_ipip_demote_tunnel_by_saddr(mlxsw_sp, ul_proto,
							  saddr, ul_tb_id,
							  शून्य)) अणु
			ipip_entry = mlxsw_sp_ipip_entry_create(mlxsw_sp, ipipt,
								ol_dev);
			अगर (IS_ERR(ipip_entry))
				वापस PTR_ERR(ipip_entry);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_netdevice_ipip_ol_unreg_event(काष्ठा mlxsw_sp *mlxsw_sp,
						   काष्ठा net_device *ol_dev)
अणु
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry;

	ipip_entry = mlxsw_sp_ipip_entry_find_by_ol_dev(mlxsw_sp, ol_dev);
	अगर (ipip_entry)
		mlxsw_sp_ipip_entry_destroy(mlxsw_sp, ipip_entry);
पूर्ण

अटल व्योम
mlxsw_sp_ipip_entry_ol_up_event(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_ipip_entry *ipip_entry)
अणु
	काष्ठा mlxsw_sp_fib_entry *decap_fib_entry;

	decap_fib_entry = mlxsw_sp_ipip_entry_find_decap(mlxsw_sp, ipip_entry);
	अगर (decap_fib_entry)
		mlxsw_sp_ipip_entry_promote_decap(mlxsw_sp, ipip_entry,
						  decap_fib_entry);
पूर्ण

अटल पूर्णांक
mlxsw_sp_rअगर_ipip_lb_op(काष्ठा mlxsw_sp_rअगर_ipip_lb *lb_rअगर, u16 ul_vr_id,
			u16 ul_rअगर_id, bool enable)
अणु
	काष्ठा mlxsw_sp_rअगर_ipip_lb_config lb_cf = lb_rअगर->lb_config;
	काष्ठा mlxsw_sp_rअगर *rअगर = &lb_rअगर->common;
	काष्ठा mlxsw_sp *mlxsw_sp = rअगर->mlxsw_sp;
	अक्षर ritr_pl[MLXSW_REG_RITR_LEN];
	u32 saddr4;

	चयन (lb_cf.ul_protocol) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		saddr4 = be32_to_cpu(lb_cf.saddr.addr4);
		mlxsw_reg_ritr_pack(ritr_pl, enable, MLXSW_REG_RITR_LOOPBACK_IF,
				    rअगर->rअगर_index, rअगर->vr_id, rअगर->dev->mtu);
		mlxsw_reg_ritr_loopback_ipip4_pack(ritr_pl, lb_cf.lb_ipipt,
			    MLXSW_REG_RITR_LOOPBACK_IPIP_OPTIONS_GRE_KEY_PRESET,
			    ul_vr_id, ul_rअगर_id, saddr4, lb_cf.okey);
		अवरोध;

	हाल MLXSW_SP_L3_PROTO_IPV6:
		वापस -EAFNOSUPPORT;
	पूर्ण

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ritr), ritr_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_netdevice_ipip_ol_update_mtu(काष्ठा mlxsw_sp *mlxsw_sp,
						 काष्ठा net_device *ol_dev)
अणु
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry;
	काष्ठा mlxsw_sp_rअगर_ipip_lb *lb_rअगर;
	पूर्णांक err = 0;

	ipip_entry = mlxsw_sp_ipip_entry_find_by_ol_dev(mlxsw_sp, ol_dev);
	अगर (ipip_entry) अणु
		lb_rअगर = ipip_entry->ol_lb;
		err = mlxsw_sp_rअगर_ipip_lb_op(lb_rअगर, lb_rअगर->ul_vr_id,
					      lb_rअगर->ul_rअगर_id, true);
		अगर (err)
			जाओ out;
		lb_rअगर->common.mtu = ol_dev->mtu;
	पूर्ण

out:
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_netdevice_ipip_ol_up_event(काष्ठा mlxsw_sp *mlxsw_sp,
						काष्ठा net_device *ol_dev)
अणु
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry;

	ipip_entry = mlxsw_sp_ipip_entry_find_by_ol_dev(mlxsw_sp, ol_dev);
	अगर (ipip_entry)
		mlxsw_sp_ipip_entry_ol_up_event(mlxsw_sp, ipip_entry);
पूर्ण

अटल व्योम
mlxsw_sp_ipip_entry_ol_करोwn_event(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_ipip_entry *ipip_entry)
अणु
	अगर (ipip_entry->decap_fib_entry)
		mlxsw_sp_ipip_entry_demote_decap(mlxsw_sp, ipip_entry);
पूर्ण

अटल व्योम mlxsw_sp_netdevice_ipip_ol_करोwn_event(काष्ठा mlxsw_sp *mlxsw_sp,
						  काष्ठा net_device *ol_dev)
अणु
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry;

	ipip_entry = mlxsw_sp_ipip_entry_find_by_ol_dev(mlxsw_sp, ol_dev);
	अगर (ipip_entry)
		mlxsw_sp_ipip_entry_ol_करोwn_event(mlxsw_sp, ipip_entry);
पूर्ण

अटल व्योम mlxsw_sp_nexthop_rअगर_migrate(काष्ठा mlxsw_sp *mlxsw_sp,
					 काष्ठा mlxsw_sp_rअगर *old_rअगर,
					 काष्ठा mlxsw_sp_rअगर *new_rअगर);
अटल पूर्णांक
mlxsw_sp_ipip_entry_ol_lb_update(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_ipip_entry *ipip_entry,
				 bool keep_encap,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_rअगर_ipip_lb *old_lb_rअगर = ipip_entry->ol_lb;
	काष्ठा mlxsw_sp_rअगर_ipip_lb *new_lb_rअगर;

	new_lb_rअगर = mlxsw_sp_ipip_ol_ipip_lb_create(mlxsw_sp,
						     ipip_entry->ipipt,
						     ipip_entry->ol_dev,
						     extack);
	अगर (IS_ERR(new_lb_rअगर))
		वापस PTR_ERR(new_lb_rअगर);
	ipip_entry->ol_lb = new_lb_rअगर;

	अगर (keep_encap)
		mlxsw_sp_nexthop_rअगर_migrate(mlxsw_sp, &old_lb_rअगर->common,
					     &new_lb_rअगर->common);

	mlxsw_sp_rअगर_destroy(&old_lb_rअगर->common);

	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_nexthop_rअगर_update(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_rअगर *rअगर);

/**
 * __mlxsw_sp_ipip_entry_update_tunnel - Update offload related to IPIP entry.
 * @mlxsw_sp: mlxsw_sp.
 * @ipip_entry: IPIP entry.
 * @recreate_loopback: Recreates the associated loopback RIF.
 * @keep_encap: Updates next hops that use the tunnel netdevice. This is only
 *              relevant when recreate_loopback is true.
 * @update_nexthops: Updates next hops, keeping the current loopback RIF. This
 *                   is only relevant when recreate_loopback is false.
 * @extack: extack.
 *
 * Return: Non-zero value on failure.
 */
पूर्णांक __mlxsw_sp_ipip_entry_update_tunnel(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_ipip_entry *ipip_entry,
					bool recreate_loopback,
					bool keep_encap,
					bool update_nexthops,
					काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	/* RIFs can't be edited, so to update loopback, we need to destroy and
	 * recreate it. That creates a winकरोw of opportunity where RALUE and
	 * RATR रेजिस्टरs end up referencing a RIF that's alपढ़ोy gone. RATRs
	 * are handled in mlxsw_sp_ipip_entry_ol_lb_update(), and to take care
	 * of RALUE, demote the decap route back.
	 */
	अगर (ipip_entry->decap_fib_entry)
		mlxsw_sp_ipip_entry_demote_decap(mlxsw_sp, ipip_entry);

	अगर (recreate_loopback) अणु
		err = mlxsw_sp_ipip_entry_ol_lb_update(mlxsw_sp, ipip_entry,
						       keep_encap, extack);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (update_nexthops) अणु
		mlxsw_sp_nexthop_rअगर_update(mlxsw_sp,
					    &ipip_entry->ol_lb->common);
	पूर्ण

	अगर (ipip_entry->ol_dev->flags & IFF_UP)
		mlxsw_sp_ipip_entry_ol_up_event(mlxsw_sp, ipip_entry);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_netdevice_ipip_ol_vrf_event(काष्ठा mlxsw_sp *mlxsw_sp,
						काष्ठा net_device *ol_dev,
						काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry =
		mlxsw_sp_ipip_entry_find_by_ol_dev(mlxsw_sp, ol_dev);

	अगर (!ipip_entry)
		वापस 0;

	वापस __mlxsw_sp_ipip_entry_update_tunnel(mlxsw_sp, ipip_entry,
						   true, false, false, extack);
पूर्ण

अटल पूर्णांक
mlxsw_sp_netdevice_ipip_ul_vrf_event(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_ipip_entry *ipip_entry,
				     काष्ठा net_device *ul_dev,
				     bool *demote_this,
				     काष्ठा netlink_ext_ack *extack)
अणु
	u32 ul_tb_id = l3mdev_fib_table(ul_dev) ? : RT_TABLE_MAIN;
	क्रमागत mlxsw_sp_l3proto ul_proto;
	जोड़ mlxsw_sp_l3addr saddr;

	/* Moving underlay to a dअगरferent VRF might cause local address
	 * conflict, and the conflicting tunnels need to be demoted.
	 */
	ul_proto = mlxsw_sp->router->ipip_ops_arr[ipip_entry->ipipt]->ul_proto;
	saddr = mlxsw_sp_ipip_netdev_saddr(ul_proto, ipip_entry->ol_dev);
	अगर (mlxsw_sp_ipip_demote_tunnel_by_saddr(mlxsw_sp, ul_proto,
						 saddr, ul_tb_id,
						 ipip_entry)) अणु
		*demote_this = true;
		वापस 0;
	पूर्ण

	वापस __mlxsw_sp_ipip_entry_update_tunnel(mlxsw_sp, ipip_entry,
						   true, true, false, extack);
पूर्ण

अटल पूर्णांक
mlxsw_sp_netdevice_ipip_ul_up_event(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_ipip_entry *ipip_entry,
				    काष्ठा net_device *ul_dev)
अणु
	वापस __mlxsw_sp_ipip_entry_update_tunnel(mlxsw_sp, ipip_entry,
						   false, false, true, शून्य);
पूर्ण

अटल पूर्णांक
mlxsw_sp_netdevice_ipip_ul_करोwn_event(काष्ठा mlxsw_sp *mlxsw_sp,
				      काष्ठा mlxsw_sp_ipip_entry *ipip_entry,
				      काष्ठा net_device *ul_dev)
अणु
	/* A करोwn underlay device causes encapsulated packets to not be
	 * क्रमwarded, but decap still works. So refresh next hops without
	 * touching anything अन्यथा.
	 */
	वापस __mlxsw_sp_ipip_entry_update_tunnel(mlxsw_sp, ipip_entry,
						   false, false, true, शून्य);
पूर्ण

अटल पूर्णांक
mlxsw_sp_netdevice_ipip_ol_change_event(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा net_device *ol_dev,
					काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा mlxsw_sp_ipip_ops *ipip_ops;
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry;
	पूर्णांक err;

	ipip_entry = mlxsw_sp_ipip_entry_find_by_ol_dev(mlxsw_sp, ol_dev);
	अगर (!ipip_entry)
		/* A change might make a tunnel eligible क्रम offloading, but
		 * that is currently not implemented. What falls to slow path
		 * stays there.
		 */
		वापस 0;

	/* A change might make a tunnel not eligible क्रम offloading. */
	अगर (!mlxsw_sp_netdevice_ipip_can_offload(mlxsw_sp, ol_dev,
						 ipip_entry->ipipt)) अणु
		mlxsw_sp_ipip_entry_demote_tunnel(mlxsw_sp, ipip_entry);
		वापस 0;
	पूर्ण

	ipip_ops = mlxsw_sp->router->ipip_ops_arr[ipip_entry->ipipt];
	err = ipip_ops->ol_netdev_change(mlxsw_sp, ipip_entry, extack);
	वापस err;
पूर्ण

व्योम mlxsw_sp_ipip_entry_demote_tunnel(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_ipip_entry *ipip_entry)
अणु
	काष्ठा net_device *ol_dev = ipip_entry->ol_dev;

	अगर (ol_dev->flags & IFF_UP)
		mlxsw_sp_ipip_entry_ol_करोwn_event(mlxsw_sp, ipip_entry);
	mlxsw_sp_ipip_entry_destroy(mlxsw_sp, ipip_entry);
पूर्ण

/* The configuration where several tunnels have the same local address in the
 * same underlay table needs special treaपंचांगent in the HW. That is currently not
 * implemented in the driver. This function finds and demotes the first tunnel
 * with a given source address, except the one passed in in the argument
 * `except'.
 */
bool
mlxsw_sp_ipip_demote_tunnel_by_saddr(काष्ठा mlxsw_sp *mlxsw_sp,
				     क्रमागत mlxsw_sp_l3proto ul_proto,
				     जोड़ mlxsw_sp_l3addr saddr,
				     u32 ul_tb_id,
				     स्थिर काष्ठा mlxsw_sp_ipip_entry *except)
अणु
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry, *पंचांगp;

	list_क्रम_each_entry_safe(ipip_entry, पंचांगp, &mlxsw_sp->router->ipip_list,
				 ipip_list_node) अणु
		अगर (ipip_entry != except &&
		    mlxsw_sp_ipip_entry_saddr_matches(mlxsw_sp, ul_proto, saddr,
						      ul_tb_id, ipip_entry)) अणु
			mlxsw_sp_ipip_entry_demote_tunnel(mlxsw_sp, ipip_entry);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम mlxsw_sp_ipip_demote_tunnel_by_ul_netdev(काष्ठा mlxsw_sp *mlxsw_sp,
						     काष्ठा net_device *ul_dev)
अणु
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry, *पंचांगp;

	list_क्रम_each_entry_safe(ipip_entry, पंचांगp, &mlxsw_sp->router->ipip_list,
				 ipip_list_node) अणु
		काष्ठा net_device *ol_dev = ipip_entry->ol_dev;
		काष्ठा net_device *ipip_ul_dev;

		rcu_पढ़ो_lock();
		ipip_ul_dev = __mlxsw_sp_ipip_netdev_ul_dev_get(ol_dev);
		rcu_पढ़ो_unlock();
		अगर (ipip_ul_dev == ul_dev)
			mlxsw_sp_ipip_entry_demote_tunnel(mlxsw_sp, ipip_entry);
	पूर्ण
पूर्ण

पूर्णांक mlxsw_sp_netdevice_ipip_ol_event(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा net_device *ol_dev,
				     अचिन्हित दीर्घ event,
				     काष्ठा netdev_notअगरier_info *info)
अणु
	काष्ठा netdev_notअगरier_changeupper_info *chup;
	काष्ठा netlink_ext_ack *extack;
	पूर्णांक err = 0;

	mutex_lock(&mlxsw_sp->router->lock);
	चयन (event) अणु
	हाल NETDEV_REGISTER:
		err = mlxsw_sp_netdevice_ipip_ol_reg_event(mlxsw_sp, ol_dev);
		अवरोध;
	हाल NETDEV_UNREGISTER:
		mlxsw_sp_netdevice_ipip_ol_unreg_event(mlxsw_sp, ol_dev);
		अवरोध;
	हाल NETDEV_UP:
		mlxsw_sp_netdevice_ipip_ol_up_event(mlxsw_sp, ol_dev);
		अवरोध;
	हाल NETDEV_DOWN:
		mlxsw_sp_netdevice_ipip_ol_करोwn_event(mlxsw_sp, ol_dev);
		अवरोध;
	हाल NETDEV_CHANGEUPPER:
		chup = container_of(info, typeof(*chup), info);
		extack = info->extack;
		अगर (netअगर_is_l3_master(chup->upper_dev))
			err = mlxsw_sp_netdevice_ipip_ol_vrf_event(mlxsw_sp,
								   ol_dev,
								   extack);
		अवरोध;
	हाल NETDEV_CHANGE:
		extack = info->extack;
		err = mlxsw_sp_netdevice_ipip_ol_change_event(mlxsw_sp,
							      ol_dev, extack);
		अवरोध;
	हाल NETDEV_CHANGEMTU:
		err = mlxsw_sp_netdevice_ipip_ol_update_mtu(mlxsw_sp, ol_dev);
		अवरोध;
	पूर्ण
	mutex_unlock(&mlxsw_sp->router->lock);
	वापस err;
पूर्ण

अटल पूर्णांक
__mlxsw_sp_netdevice_ipip_ul_event(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_ipip_entry *ipip_entry,
				   काष्ठा net_device *ul_dev,
				   bool *demote_this,
				   अचिन्हित दीर्घ event,
				   काष्ठा netdev_notअगरier_info *info)
अणु
	काष्ठा netdev_notअगरier_changeupper_info *chup;
	काष्ठा netlink_ext_ack *extack;

	चयन (event) अणु
	हाल NETDEV_CHANGEUPPER:
		chup = container_of(info, typeof(*chup), info);
		extack = info->extack;
		अगर (netअगर_is_l3_master(chup->upper_dev))
			वापस mlxsw_sp_netdevice_ipip_ul_vrf_event(mlxsw_sp,
								    ipip_entry,
								    ul_dev,
								    demote_this,
								    extack);
		अवरोध;

	हाल NETDEV_UP:
		वापस mlxsw_sp_netdevice_ipip_ul_up_event(mlxsw_sp, ipip_entry,
							   ul_dev);
	हाल NETDEV_DOWN:
		वापस mlxsw_sp_netdevice_ipip_ul_करोwn_event(mlxsw_sp,
							     ipip_entry,
							     ul_dev);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
mlxsw_sp_netdevice_ipip_ul_event(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा net_device *ul_dev,
				 अचिन्हित दीर्घ event,
				 काष्ठा netdev_notअगरier_info *info)
अणु
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry = शून्य;
	पूर्णांक err = 0;

	mutex_lock(&mlxsw_sp->router->lock);
	जबतक ((ipip_entry = mlxsw_sp_ipip_entry_find_by_ul_dev(mlxsw_sp,
								ul_dev,
								ipip_entry))) अणु
		काष्ठा mlxsw_sp_ipip_entry *prev;
		bool demote_this = false;

		err = __mlxsw_sp_netdevice_ipip_ul_event(mlxsw_sp, ipip_entry,
							 ul_dev, &demote_this,
							 event, info);
		अगर (err) अणु
			mlxsw_sp_ipip_demote_tunnel_by_ul_netdev(mlxsw_sp,
								 ul_dev);
			अवरोध;
		पूर्ण

		अगर (demote_this) अणु
			अगर (list_is_first(&ipip_entry->ipip_list_node,
					  &mlxsw_sp->router->ipip_list))
				prev = शून्य;
			अन्यथा
				/* This can't be cached from previous iteration,
				 * because that entry could be gone now.
				 */
				prev = list_prev_entry(ipip_entry,
						       ipip_list_node);
			mlxsw_sp_ipip_entry_demote_tunnel(mlxsw_sp, ipip_entry);
			ipip_entry = prev;
		पूर्ण
	पूर्ण
	mutex_unlock(&mlxsw_sp->router->lock);

	वापस err;
पूर्ण

पूर्णांक mlxsw_sp_router_nve_promote_decap(काष्ठा mlxsw_sp *mlxsw_sp, u32 ul_tb_id,
				      क्रमागत mlxsw_sp_l3proto ul_proto,
				      स्थिर जोड़ mlxsw_sp_l3addr *ul_sip,
				      u32 tunnel_index)
अणु
	क्रमागत mlxsw_sp_fib_entry_type type = MLXSW_SP_FIB_ENTRY_TYPE_TRAP;
	काष्ठा mlxsw_sp_router *router = mlxsw_sp->router;
	काष्ठा mlxsw_sp_fib_entry *fib_entry;
	पूर्णांक err = 0;

	mutex_lock(&mlxsw_sp->router->lock);

	अगर (WARN_ON_ONCE(router->nve_decap_config.valid)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	router->nve_decap_config.ul_tb_id = ul_tb_id;
	router->nve_decap_config.tunnel_index = tunnel_index;
	router->nve_decap_config.ul_proto = ul_proto;
	router->nve_decap_config.ul_sip = *ul_sip;
	router->nve_decap_config.valid = true;

	/* It is valid to create a tunnel with a local IP and only later
	 * assign this IP address to a local पूर्णांकerface
	 */
	fib_entry = mlxsw_sp_router_ip2me_fib_entry_find(mlxsw_sp, ul_tb_id,
							 ul_proto, ul_sip,
							 type);
	अगर (!fib_entry)
		जाओ out;

	fib_entry->decap.tunnel_index = tunnel_index;
	fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_NVE_DECAP;

	err = mlxsw_sp_fib_entry_update(mlxsw_sp, fib_entry);
	अगर (err)
		जाओ err_fib_entry_update;

	जाओ out;

err_fib_entry_update:
	fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_TRAP;
	mlxsw_sp_fib_entry_update(mlxsw_sp, fib_entry);
out:
	mutex_unlock(&mlxsw_sp->router->lock);
	वापस err;
पूर्ण

व्योम mlxsw_sp_router_nve_demote_decap(काष्ठा mlxsw_sp *mlxsw_sp, u32 ul_tb_id,
				      क्रमागत mlxsw_sp_l3proto ul_proto,
				      स्थिर जोड़ mlxsw_sp_l3addr *ul_sip)
अणु
	क्रमागत mlxsw_sp_fib_entry_type type = MLXSW_SP_FIB_ENTRY_TYPE_NVE_DECAP;
	काष्ठा mlxsw_sp_router *router = mlxsw_sp->router;
	काष्ठा mlxsw_sp_fib_entry *fib_entry;

	mutex_lock(&mlxsw_sp->router->lock);

	अगर (WARN_ON_ONCE(!router->nve_decap_config.valid))
		जाओ out;

	router->nve_decap_config.valid = false;

	fib_entry = mlxsw_sp_router_ip2me_fib_entry_find(mlxsw_sp, ul_tb_id,
							 ul_proto, ul_sip,
							 type);
	अगर (!fib_entry)
		जाओ out;

	fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_TRAP;
	mlxsw_sp_fib_entry_update(mlxsw_sp, fib_entry);
out:
	mutex_unlock(&mlxsw_sp->router->lock);
पूर्ण

अटल bool mlxsw_sp_router_nve_is_decap(काष्ठा mlxsw_sp *mlxsw_sp,
					 u32 ul_tb_id,
					 क्रमागत mlxsw_sp_l3proto ul_proto,
					 स्थिर जोड़ mlxsw_sp_l3addr *ul_sip)
अणु
	काष्ठा mlxsw_sp_router *router = mlxsw_sp->router;

	वापस router->nve_decap_config.valid &&
	       router->nve_decap_config.ul_tb_id == ul_tb_id &&
	       router->nve_decap_config.ul_proto == ul_proto &&
	       !स_भेद(&router->nve_decap_config.ul_sip, ul_sip,
		       माप(*ul_sip));
पूर्ण

काष्ठा mlxsw_sp_neigh_key अणु
	काष्ठा neighbour *n;
पूर्ण;

काष्ठा mlxsw_sp_neigh_entry अणु
	काष्ठा list_head rअगर_list_node;
	काष्ठा rhash_head ht_node;
	काष्ठा mlxsw_sp_neigh_key key;
	u16 rअगर;
	bool connected;
	अचिन्हित अक्षर ha[ETH_ALEN];
	काष्ठा list_head nexthop_list; /* list of nexthops using
					* this neigh entry
					*/
	काष्ठा list_head nexthop_neighs_list_node;
	अचिन्हित पूर्णांक counter_index;
	bool counter_valid;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_neigh_ht_params = अणु
	.key_offset = दुरत्व(काष्ठा mlxsw_sp_neigh_entry, key),
	.head_offset = दुरत्व(काष्ठा mlxsw_sp_neigh_entry, ht_node),
	.key_len = माप(काष्ठा mlxsw_sp_neigh_key),
पूर्ण;

काष्ठा mlxsw_sp_neigh_entry *
mlxsw_sp_rअगर_neigh_next(काष्ठा mlxsw_sp_rअगर *rअगर,
			काष्ठा mlxsw_sp_neigh_entry *neigh_entry)
अणु
	अगर (!neigh_entry) अणु
		अगर (list_empty(&rअगर->neigh_list))
			वापस शून्य;
		अन्यथा
			वापस list_first_entry(&rअगर->neigh_list,
						typeof(*neigh_entry),
						rअगर_list_node);
	पूर्ण
	अगर (list_is_last(&neigh_entry->rअगर_list_node, &rअगर->neigh_list))
		वापस शून्य;
	वापस list_next_entry(neigh_entry, rअगर_list_node);
पूर्ण

पूर्णांक mlxsw_sp_neigh_entry_type(काष्ठा mlxsw_sp_neigh_entry *neigh_entry)
अणु
	वापस neigh_entry->key.n->tbl->family;
पूर्ण

अचिन्हित अक्षर *
mlxsw_sp_neigh_entry_ha(काष्ठा mlxsw_sp_neigh_entry *neigh_entry)
अणु
	वापस neigh_entry->ha;
पूर्ण

u32 mlxsw_sp_neigh4_entry_dip(काष्ठा mlxsw_sp_neigh_entry *neigh_entry)
अणु
	काष्ठा neighbour *n;

	n = neigh_entry->key.n;
	वापस ntohl(*((__be32 *) n->primary_key));
पूर्ण

काष्ठा in6_addr *
mlxsw_sp_neigh6_entry_dip(काष्ठा mlxsw_sp_neigh_entry *neigh_entry)
अणु
	काष्ठा neighbour *n;

	n = neigh_entry->key.n;
	वापस (काष्ठा in6_addr *) &n->primary_key;
पूर्ण

पूर्णांक mlxsw_sp_neigh_counter_get(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_neigh_entry *neigh_entry,
			       u64 *p_counter)
अणु
	अगर (!neigh_entry->counter_valid)
		वापस -EINVAL;

	वापस mlxsw_sp_flow_counter_get(mlxsw_sp, neigh_entry->counter_index,
					 p_counter, शून्य);
पूर्ण

अटल काष्ठा mlxsw_sp_neigh_entry *
mlxsw_sp_neigh_entry_alloc(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा neighbour *n,
			   u16 rअगर)
अणु
	काष्ठा mlxsw_sp_neigh_entry *neigh_entry;

	neigh_entry = kzalloc(माप(*neigh_entry), GFP_KERNEL);
	अगर (!neigh_entry)
		वापस शून्य;

	neigh_entry->key.n = n;
	neigh_entry->rअगर = rअगर;
	INIT_LIST_HEAD(&neigh_entry->nexthop_list);

	वापस neigh_entry;
पूर्ण

अटल व्योम mlxsw_sp_neigh_entry_मुक्त(काष्ठा mlxsw_sp_neigh_entry *neigh_entry)
अणु
	kमुक्त(neigh_entry);
पूर्ण

अटल पूर्णांक
mlxsw_sp_neigh_entry_insert(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_neigh_entry *neigh_entry)
अणु
	वापस rhashtable_insert_fast(&mlxsw_sp->router->neigh_ht,
				      &neigh_entry->ht_node,
				      mlxsw_sp_neigh_ht_params);
पूर्ण

अटल व्योम
mlxsw_sp_neigh_entry_हटाओ(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_neigh_entry *neigh_entry)
अणु
	rhashtable_हटाओ_fast(&mlxsw_sp->router->neigh_ht,
			       &neigh_entry->ht_node,
			       mlxsw_sp_neigh_ht_params);
पूर्ण

अटल bool
mlxsw_sp_neigh_counter_should_alloc(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_neigh_entry *neigh_entry)
अणु
	काष्ठा devlink *devlink;
	स्थिर अक्षर *table_name;

	चयन (mlxsw_sp_neigh_entry_type(neigh_entry)) अणु
	हाल AF_INET:
		table_name = MLXSW_SP_DPIPE_TABLE_NAME_HOST4;
		अवरोध;
	हाल AF_INET6:
		table_name = MLXSW_SP_DPIPE_TABLE_NAME_HOST6;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस false;
	पूर्ण

	devlink = priv_to_devlink(mlxsw_sp->core);
	वापस devlink_dpipe_table_counter_enabled(devlink, table_name);
पूर्ण

अटल व्योम
mlxsw_sp_neigh_counter_alloc(काष्ठा mlxsw_sp *mlxsw_sp,
			     काष्ठा mlxsw_sp_neigh_entry *neigh_entry)
अणु
	अगर (!mlxsw_sp_neigh_counter_should_alloc(mlxsw_sp, neigh_entry))
		वापस;

	अगर (mlxsw_sp_flow_counter_alloc(mlxsw_sp, &neigh_entry->counter_index))
		वापस;

	neigh_entry->counter_valid = true;
पूर्ण

अटल व्योम
mlxsw_sp_neigh_counter_मुक्त(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_neigh_entry *neigh_entry)
अणु
	अगर (!neigh_entry->counter_valid)
		वापस;
	mlxsw_sp_flow_counter_मुक्त(mlxsw_sp,
				   neigh_entry->counter_index);
	neigh_entry->counter_valid = false;
पूर्ण

अटल काष्ठा mlxsw_sp_neigh_entry *
mlxsw_sp_neigh_entry_create(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा neighbour *n)
अणु
	काष्ठा mlxsw_sp_neigh_entry *neigh_entry;
	काष्ठा mlxsw_sp_rअगर *rअगर;
	पूर्णांक err;

	rअगर = mlxsw_sp_rअगर_find_by_dev(mlxsw_sp, n->dev);
	अगर (!rअगर)
		वापस ERR_PTR(-EINVAL);

	neigh_entry = mlxsw_sp_neigh_entry_alloc(mlxsw_sp, n, rअगर->rअगर_index);
	अगर (!neigh_entry)
		वापस ERR_PTR(-ENOMEM);

	err = mlxsw_sp_neigh_entry_insert(mlxsw_sp, neigh_entry);
	अगर (err)
		जाओ err_neigh_entry_insert;

	mlxsw_sp_neigh_counter_alloc(mlxsw_sp, neigh_entry);
	list_add(&neigh_entry->rअगर_list_node, &rअगर->neigh_list);

	वापस neigh_entry;

err_neigh_entry_insert:
	mlxsw_sp_neigh_entry_मुक्त(neigh_entry);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_neigh_entry_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
			     काष्ठा mlxsw_sp_neigh_entry *neigh_entry)
अणु
	list_del(&neigh_entry->rअगर_list_node);
	mlxsw_sp_neigh_counter_मुक्त(mlxsw_sp, neigh_entry);
	mlxsw_sp_neigh_entry_हटाओ(mlxsw_sp, neigh_entry);
	mlxsw_sp_neigh_entry_मुक्त(neigh_entry);
पूर्ण

अटल काष्ठा mlxsw_sp_neigh_entry *
mlxsw_sp_neigh_entry_lookup(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा neighbour *n)
अणु
	काष्ठा mlxsw_sp_neigh_key key;

	key.n = n;
	वापस rhashtable_lookup_fast(&mlxsw_sp->router->neigh_ht,
				      &key, mlxsw_sp_neigh_ht_params);
पूर्ण

अटल व्योम
mlxsw_sp_router_neighs_update_पूर्णांकerval_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अचिन्हित दीर्घ पूर्णांकerval;

#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्णांकerval = min_t(अचिन्हित दीर्घ,
			 NEIGH_VAR(&arp_tbl.parms, DELAY_PROBE_TIME),
			 NEIGH_VAR(&nd_tbl.parms, DELAY_PROBE_TIME));
#अन्यथा
	पूर्णांकerval = NEIGH_VAR(&arp_tbl.parms, DELAY_PROBE_TIME);
#पूर्ण_अगर
	mlxsw_sp->router->neighs_update.पूर्णांकerval = jअगरfies_to_msecs(पूर्णांकerval);
पूर्ण

अटल व्योम mlxsw_sp_router_neigh_ent_ipv4_process(काष्ठा mlxsw_sp *mlxsw_sp,
						   अक्षर *rauhtd_pl,
						   पूर्णांक ent_index)
अणु
	काष्ठा net_device *dev;
	काष्ठा neighbour *n;
	__be32 dipn;
	u32 dip;
	u16 rअगर;

	mlxsw_reg_rauhtd_ent_ipv4_unpack(rauhtd_pl, ent_index, &rअगर, &dip);

	अगर (!mlxsw_sp->router->rअगरs[rअगर]) अणु
		dev_err_ratelimited(mlxsw_sp->bus_info->dev, "Incorrect RIF in neighbour entry\n");
		वापस;
	पूर्ण

	dipn = htonl(dip);
	dev = mlxsw_sp->router->rअगरs[rअगर]->dev;
	n = neigh_lookup(&arp_tbl, &dipn, dev);
	अगर (!n)
		वापस;

	netdev_dbg(dev, "Updating neighbour with IP=%pI4h\n", &dip);
	neigh_event_send(n, शून्य);
	neigh_release(n);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम mlxsw_sp_router_neigh_ent_ipv6_process(काष्ठा mlxsw_sp *mlxsw_sp,
						   अक्षर *rauhtd_pl,
						   पूर्णांक rec_index)
अणु
	काष्ठा net_device *dev;
	काष्ठा neighbour *n;
	काष्ठा in6_addr dip;
	u16 rअगर;

	mlxsw_reg_rauhtd_ent_ipv6_unpack(rauhtd_pl, rec_index, &rअगर,
					 (अक्षर *) &dip);

	अगर (!mlxsw_sp->router->rअगरs[rअगर]) अणु
		dev_err_ratelimited(mlxsw_sp->bus_info->dev, "Incorrect RIF in neighbour entry\n");
		वापस;
	पूर्ण

	dev = mlxsw_sp->router->rअगरs[rअगर]->dev;
	n = neigh_lookup(&nd_tbl, &dip, dev);
	अगर (!n)
		वापस;

	netdev_dbg(dev, "Updating neighbour with IP=%pI6c\n", &dip);
	neigh_event_send(n, शून्य);
	neigh_release(n);
पूर्ण
#अन्यथा
अटल व्योम mlxsw_sp_router_neigh_ent_ipv6_process(काष्ठा mlxsw_sp *mlxsw_sp,
						   अक्षर *rauhtd_pl,
						   पूर्णांक rec_index)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम mlxsw_sp_router_neigh_rec_ipv4_process(काष्ठा mlxsw_sp *mlxsw_sp,
						   अक्षर *rauhtd_pl,
						   पूर्णांक rec_index)
अणु
	u8 num_entries;
	पूर्णांक i;

	num_entries = mlxsw_reg_rauhtd_ipv4_rec_num_entries_get(rauhtd_pl,
								rec_index);
	/* Hardware starts counting at 0, so add 1. */
	num_entries++;

	/* Each record consists of several neighbour entries. */
	क्रम (i = 0; i < num_entries; i++) अणु
		पूर्णांक ent_index;

		ent_index = rec_index * MLXSW_REG_RAUHTD_IPV4_ENT_PER_REC + i;
		mlxsw_sp_router_neigh_ent_ipv4_process(mlxsw_sp, rauhtd_pl,
						       ent_index);
	पूर्ण

पूर्ण

अटल व्योम mlxsw_sp_router_neigh_rec_ipv6_process(काष्ठा mlxsw_sp *mlxsw_sp,
						   अक्षर *rauhtd_pl,
						   पूर्णांक rec_index)
अणु
	/* One record contains one entry. */
	mlxsw_sp_router_neigh_ent_ipv6_process(mlxsw_sp, rauhtd_pl,
					       rec_index);
पूर्ण

अटल व्योम mlxsw_sp_router_neigh_rec_process(काष्ठा mlxsw_sp *mlxsw_sp,
					      अक्षर *rauhtd_pl, पूर्णांक rec_index)
अणु
	चयन (mlxsw_reg_rauhtd_rec_type_get(rauhtd_pl, rec_index)) अणु
	हाल MLXSW_REG_RAUHTD_TYPE_IPV4:
		mlxsw_sp_router_neigh_rec_ipv4_process(mlxsw_sp, rauhtd_pl,
						       rec_index);
		अवरोध;
	हाल MLXSW_REG_RAUHTD_TYPE_IPV6:
		mlxsw_sp_router_neigh_rec_ipv6_process(mlxsw_sp, rauhtd_pl,
						       rec_index);
		अवरोध;
	पूर्ण
पूर्ण

अटल bool mlxsw_sp_router_rauhtd_is_full(अक्षर *rauhtd_pl)
अणु
	u8 num_rec, last_rec_index, num_entries;

	num_rec = mlxsw_reg_rauhtd_num_rec_get(rauhtd_pl);
	last_rec_index = num_rec - 1;

	अगर (num_rec < MLXSW_REG_RAUHTD_REC_MAX_NUM)
		वापस false;
	अगर (mlxsw_reg_rauhtd_rec_type_get(rauhtd_pl, last_rec_index) ==
	    MLXSW_REG_RAUHTD_TYPE_IPV6)
		वापस true;

	num_entries = mlxsw_reg_rauhtd_ipv4_rec_num_entries_get(rauhtd_pl,
								last_rec_index);
	अगर (++num_entries == MLXSW_REG_RAUHTD_IPV4_ENT_PER_REC)
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक
__mlxsw_sp_router_neighs_update_rauhtd(काष्ठा mlxsw_sp *mlxsw_sp,
				       अक्षर *rauhtd_pl,
				       क्रमागत mlxsw_reg_rauhtd_type type)
अणु
	पूर्णांक i, num_rec;
	पूर्णांक err;

	/* Ensure the RIF we पढ़ो from the device करोes not change mid-dump. */
	mutex_lock(&mlxsw_sp->router->lock);
	करो अणु
		mlxsw_reg_rauhtd_pack(rauhtd_pl, type);
		err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(rauhtd),
				      rauhtd_pl);
		अगर (err) अणु
			dev_err_ratelimited(mlxsw_sp->bus_info->dev, "Failed to dump neighbour table\n");
			अवरोध;
		पूर्ण
		num_rec = mlxsw_reg_rauhtd_num_rec_get(rauhtd_pl);
		क्रम (i = 0; i < num_rec; i++)
			mlxsw_sp_router_neigh_rec_process(mlxsw_sp, rauhtd_pl,
							  i);
	पूर्ण जबतक (mlxsw_sp_router_rauhtd_is_full(rauhtd_pl));
	mutex_unlock(&mlxsw_sp->router->lock);

	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_router_neighs_update_rauhtd(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	क्रमागत mlxsw_reg_rauhtd_type type;
	अक्षर *rauhtd_pl;
	पूर्णांक err;

	rauhtd_pl = kदो_स्मृति(MLXSW_REG_RAUHTD_LEN, GFP_KERNEL);
	अगर (!rauhtd_pl)
		वापस -ENOMEM;

	type = MLXSW_REG_RAUHTD_TYPE_IPV4;
	err = __mlxsw_sp_router_neighs_update_rauhtd(mlxsw_sp, rauhtd_pl, type);
	अगर (err)
		जाओ out;

	type = MLXSW_REG_RAUHTD_TYPE_IPV6;
	err = __mlxsw_sp_router_neighs_update_rauhtd(mlxsw_sp, rauhtd_pl, type);
out:
	kमुक्त(rauhtd_pl);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_router_neighs_update_nh(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_neigh_entry *neigh_entry;

	mutex_lock(&mlxsw_sp->router->lock);
	list_क्रम_each_entry(neigh_entry, &mlxsw_sp->router->nexthop_neighs_list,
			    nexthop_neighs_list_node)
		/* If this neigh have nexthops, make the kernel think this neigh
		 * is active regardless of the traffic.
		 */
		neigh_event_send(neigh_entry->key.n, शून्य);
	mutex_unlock(&mlxsw_sp->router->lock);
पूर्ण

अटल व्योम
mlxsw_sp_router_neighs_update_work_schedule(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अचिन्हित दीर्घ पूर्णांकerval = mlxsw_sp->router->neighs_update.पूर्णांकerval;

	mlxsw_core_schedule_dw(&mlxsw_sp->router->neighs_update.dw,
			       msecs_to_jअगरfies(पूर्णांकerval));
पूर्ण

अटल व्योम mlxsw_sp_router_neighs_update_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_sp_router *router;
	पूर्णांक err;

	router = container_of(work, काष्ठा mlxsw_sp_router,
			      neighs_update.dw.work);
	err = mlxsw_sp_router_neighs_update_rauhtd(router->mlxsw_sp);
	अगर (err)
		dev_err(router->mlxsw_sp->bus_info->dev, "Could not update kernel for neigh activity");

	mlxsw_sp_router_neighs_update_nh(router->mlxsw_sp);

	mlxsw_sp_router_neighs_update_work_schedule(router->mlxsw_sp);
पूर्ण

अटल व्योम mlxsw_sp_router_probe_unresolved_nexthops(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_sp_neigh_entry *neigh_entry;
	काष्ठा mlxsw_sp_router *router;

	router = container_of(work, काष्ठा mlxsw_sp_router,
			      nexthop_probe_dw.work);
	/* Iterate over nexthop neighbours, find those who are unresolved and
	 * send arp on them. This solves the chicken-egg problem when
	 * the nexthop wouldn't get offloaded until the neighbor is resolved
	 * but it wouldn't get resolved ever in हाल traffic is flowing in HW
	 * using dअगरferent nexthop.
	 */
	mutex_lock(&router->lock);
	list_क्रम_each_entry(neigh_entry, &router->nexthop_neighs_list,
			    nexthop_neighs_list_node)
		अगर (!neigh_entry->connected)
			neigh_event_send(neigh_entry->key.n, शून्य);
	mutex_unlock(&router->lock);

	mlxsw_core_schedule_dw(&router->nexthop_probe_dw,
			       MLXSW_SP_UNRESOLVED_NH_PROBE_INTERVAL);
पूर्ण

अटल व्योम
mlxsw_sp_nexthop_neigh_update(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_neigh_entry *neigh_entry,
			      bool removing, bool dead);

अटल क्रमागत mlxsw_reg_rauht_op mlxsw_sp_rauht_op(bool adding)
अणु
	वापस adding ? MLXSW_REG_RAUHT_OP_WRITE_ADD :
			MLXSW_REG_RAUHT_OP_WRITE_DELETE;
पूर्ण

अटल पूर्णांक
mlxsw_sp_router_neigh_entry_op4(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_neigh_entry *neigh_entry,
				क्रमागत mlxsw_reg_rauht_op op)
अणु
	काष्ठा neighbour *n = neigh_entry->key.n;
	u32 dip = ntohl(*((__be32 *) n->primary_key));
	अक्षर rauht_pl[MLXSW_REG_RAUHT_LEN];

	mlxsw_reg_rauht_pack4(rauht_pl, op, neigh_entry->rअगर, neigh_entry->ha,
			      dip);
	अगर (neigh_entry->counter_valid)
		mlxsw_reg_rauht_pack_counter(rauht_pl,
					     neigh_entry->counter_index);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rauht), rauht_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_router_neigh_entry_op6(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_neigh_entry *neigh_entry,
				क्रमागत mlxsw_reg_rauht_op op)
अणु
	काष्ठा neighbour *n = neigh_entry->key.n;
	अक्षर rauht_pl[MLXSW_REG_RAUHT_LEN];
	स्थिर अक्षर *dip = n->primary_key;

	mlxsw_reg_rauht_pack6(rauht_pl, op, neigh_entry->rअगर, neigh_entry->ha,
			      dip);
	अगर (neigh_entry->counter_valid)
		mlxsw_reg_rauht_pack_counter(rauht_pl,
					     neigh_entry->counter_index);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rauht), rauht_pl);
पूर्ण

bool mlxsw_sp_neigh_ipv6_ignore(काष्ठा mlxsw_sp_neigh_entry *neigh_entry)
अणु
	काष्ठा neighbour *n = neigh_entry->key.n;

	/* Packets with a link-local destination address are trapped
	 * after LPM lookup and never reach the neighbour table, so
	 * there is no need to program such neighbours to the device.
	 */
	अगर (ipv6_addr_type((काष्ठा in6_addr *) &n->primary_key) &
	    IPV6_ADDR_LINKLOCAL)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम
mlxsw_sp_neigh_entry_update(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_neigh_entry *neigh_entry,
			    bool adding)
अणु
	क्रमागत mlxsw_reg_rauht_op op = mlxsw_sp_rauht_op(adding);
	पूर्णांक err;

	अगर (!adding && !neigh_entry->connected)
		वापस;
	neigh_entry->connected = adding;
	अगर (neigh_entry->key.n->tbl->family == AF_INET) अणु
		err = mlxsw_sp_router_neigh_entry_op4(mlxsw_sp, neigh_entry,
						      op);
		अगर (err)
			वापस;
	पूर्ण अन्यथा अगर (neigh_entry->key.n->tbl->family == AF_INET6) अणु
		अगर (mlxsw_sp_neigh_ipv6_ignore(neigh_entry))
			वापस;
		err = mlxsw_sp_router_neigh_entry_op6(mlxsw_sp, neigh_entry,
						      op);
		अगर (err)
			वापस;
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	अगर (adding)
		neigh_entry->key.n->flags |= NTF_OFFLOADED;
	अन्यथा
		neigh_entry->key.n->flags &= ~NTF_OFFLOADED;
पूर्ण

व्योम
mlxsw_sp_neigh_entry_counter_update(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_neigh_entry *neigh_entry,
				    bool adding)
अणु
	अगर (adding)
		mlxsw_sp_neigh_counter_alloc(mlxsw_sp, neigh_entry);
	अन्यथा
		mlxsw_sp_neigh_counter_मुक्त(mlxsw_sp, neigh_entry);
	mlxsw_sp_neigh_entry_update(mlxsw_sp, neigh_entry, true);
पूर्ण

काष्ठा mlxsw_sp_netevent_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा mlxsw_sp *mlxsw_sp;
	काष्ठा neighbour *n;
पूर्ण;

अटल व्योम mlxsw_sp_router_neigh_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_sp_netevent_work *net_work =
		container_of(work, काष्ठा mlxsw_sp_netevent_work, work);
	काष्ठा mlxsw_sp *mlxsw_sp = net_work->mlxsw_sp;
	काष्ठा mlxsw_sp_neigh_entry *neigh_entry;
	काष्ठा neighbour *n = net_work->n;
	अचिन्हित अक्षर ha[ETH_ALEN];
	bool entry_connected;
	u8 nud_state, dead;

	/* If these parameters are changed after we release the lock,
	 * then we are guaranteed to receive another event letting us
	 * know about it.
	 */
	पढ़ो_lock_bh(&n->lock);
	स_नकल(ha, n->ha, ETH_ALEN);
	nud_state = n->nud_state;
	dead = n->dead;
	पढ़ो_unlock_bh(&n->lock);

	mutex_lock(&mlxsw_sp->router->lock);
	mlxsw_sp_span_respin(mlxsw_sp);

	entry_connected = nud_state & NUD_VALID && !dead;
	neigh_entry = mlxsw_sp_neigh_entry_lookup(mlxsw_sp, n);
	अगर (!entry_connected && !neigh_entry)
		जाओ out;
	अगर (!neigh_entry) अणु
		neigh_entry = mlxsw_sp_neigh_entry_create(mlxsw_sp, n);
		अगर (IS_ERR(neigh_entry))
			जाओ out;
	पूर्ण

	अगर (neigh_entry->connected && entry_connected &&
	    !स_भेद(neigh_entry->ha, ha, ETH_ALEN))
		जाओ out;

	स_नकल(neigh_entry->ha, ha, ETH_ALEN);
	mlxsw_sp_neigh_entry_update(mlxsw_sp, neigh_entry, entry_connected);
	mlxsw_sp_nexthop_neigh_update(mlxsw_sp, neigh_entry, !entry_connected,
				      dead);

	अगर (!neigh_entry->connected && list_empty(&neigh_entry->nexthop_list))
		mlxsw_sp_neigh_entry_destroy(mlxsw_sp, neigh_entry);

out:
	mutex_unlock(&mlxsw_sp->router->lock);
	neigh_release(n);
	kमुक्त(net_work);
पूर्ण

अटल पूर्णांक mlxsw_sp_mp_hash_init(काष्ठा mlxsw_sp *mlxsw_sp);

अटल व्योम mlxsw_sp_router_mp_hash_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_sp_netevent_work *net_work =
		container_of(work, काष्ठा mlxsw_sp_netevent_work, work);
	काष्ठा mlxsw_sp *mlxsw_sp = net_work->mlxsw_sp;

	mlxsw_sp_mp_hash_init(mlxsw_sp);
	kमुक्त(net_work);
पूर्ण

अटल पूर्णांक __mlxsw_sp_router_init(काष्ठा mlxsw_sp *mlxsw_sp);

अटल व्योम mlxsw_sp_router_update_priority_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_sp_netevent_work *net_work =
		container_of(work, काष्ठा mlxsw_sp_netevent_work, work);
	काष्ठा mlxsw_sp *mlxsw_sp = net_work->mlxsw_sp;

	__mlxsw_sp_router_init(mlxsw_sp);
	kमुक्त(net_work);
पूर्ण

अटल पूर्णांक mlxsw_sp_router_schedule_work(काष्ठा net *net,
					 काष्ठा notअगरier_block *nb,
					 व्योम (*cb)(काष्ठा work_काष्ठा *))
अणु
	काष्ठा mlxsw_sp_netevent_work *net_work;
	काष्ठा mlxsw_sp_router *router;

	router = container_of(nb, काष्ठा mlxsw_sp_router, netevent_nb);
	अगर (!net_eq(net, mlxsw_sp_net(router->mlxsw_sp)))
		वापस NOTIFY_DONE;

	net_work = kzalloc(माप(*net_work), GFP_ATOMIC);
	अगर (!net_work)
		वापस NOTIFY_BAD;

	INIT_WORK(&net_work->work, cb);
	net_work->mlxsw_sp = router->mlxsw_sp;
	mlxsw_core_schedule_work(&net_work->work);
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक mlxsw_sp_router_netevent_event(काष्ठा notअगरier_block *nb,
					  अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा mlxsw_sp_netevent_work *net_work;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	काष्ठा mlxsw_sp *mlxsw_sp;
	अचिन्हित दीर्घ पूर्णांकerval;
	काष्ठा neigh_parms *p;
	काष्ठा neighbour *n;

	चयन (event) अणु
	हाल NETEVENT_DELAY_PROBE_TIME_UPDATE:
		p = ptr;

		/* We करोn't care about changes in the शेष table. */
		अगर (!p->dev || (p->tbl->family != AF_INET &&
				p->tbl->family != AF_INET6))
			वापस NOTIFY_DONE;

		/* We are in atomic context and can't take RTNL mutex,
		 * so use RCU variant to walk the device chain.
		 */
		mlxsw_sp_port = mlxsw_sp_port_lower_dev_hold(p->dev);
		अगर (!mlxsw_sp_port)
			वापस NOTIFY_DONE;

		mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
		पूर्णांकerval = jअगरfies_to_msecs(NEIGH_VAR(p, DELAY_PROBE_TIME));
		mlxsw_sp->router->neighs_update.पूर्णांकerval = पूर्णांकerval;

		mlxsw_sp_port_dev_put(mlxsw_sp_port);
		अवरोध;
	हाल NETEVENT_NEIGH_UPDATE:
		n = ptr;

		अगर (n->tbl->family != AF_INET && n->tbl->family != AF_INET6)
			वापस NOTIFY_DONE;

		mlxsw_sp_port = mlxsw_sp_port_lower_dev_hold(n->dev);
		अगर (!mlxsw_sp_port)
			वापस NOTIFY_DONE;

		net_work = kzalloc(माप(*net_work), GFP_ATOMIC);
		अगर (!net_work) अणु
			mlxsw_sp_port_dev_put(mlxsw_sp_port);
			वापस NOTIFY_BAD;
		पूर्ण

		INIT_WORK(&net_work->work, mlxsw_sp_router_neigh_event_work);
		net_work->mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
		net_work->n = n;

		/* Take a reference to ensure the neighbour won't be
		 * deकाष्ठाed until we drop the reference in delayed
		 * work.
		 */
		neigh_clone(n);
		mlxsw_core_schedule_work(&net_work->work);
		mlxsw_sp_port_dev_put(mlxsw_sp_port);
		अवरोध;
	हाल NETEVENT_IPV4_MPATH_HASH_UPDATE:
	हाल NETEVENT_IPV6_MPATH_HASH_UPDATE:
		वापस mlxsw_sp_router_schedule_work(ptr, nb,
				mlxsw_sp_router_mp_hash_event_work);

	हाल NETEVENT_IPV4_FWD_UPDATE_PRIORITY_UPDATE:
		वापस mlxsw_sp_router_schedule_work(ptr, nb,
				mlxsw_sp_router_update_priority_work);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक mlxsw_sp_neigh_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	पूर्णांक err;

	err = rhashtable_init(&mlxsw_sp->router->neigh_ht,
			      &mlxsw_sp_neigh_ht_params);
	अगर (err)
		वापस err;

	/* Initialize the polling पूर्णांकerval according to the शेष
	 * table.
	 */
	mlxsw_sp_router_neighs_update_पूर्णांकerval_init(mlxsw_sp);

	/* Create the delayed works क्रम the activity_update */
	INIT_DELAYED_WORK(&mlxsw_sp->router->neighs_update.dw,
			  mlxsw_sp_router_neighs_update_work);
	INIT_DELAYED_WORK(&mlxsw_sp->router->nexthop_probe_dw,
			  mlxsw_sp_router_probe_unresolved_nexthops);
	mlxsw_core_schedule_dw(&mlxsw_sp->router->neighs_update.dw, 0);
	mlxsw_core_schedule_dw(&mlxsw_sp->router->nexthop_probe_dw, 0);
	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_neigh_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	cancel_delayed_work_sync(&mlxsw_sp->router->neighs_update.dw);
	cancel_delayed_work_sync(&mlxsw_sp->router->nexthop_probe_dw);
	rhashtable_destroy(&mlxsw_sp->router->neigh_ht);
पूर्ण

अटल व्योम mlxsw_sp_neigh_rअगर_gone_sync(काष्ठा mlxsw_sp *mlxsw_sp,
					 काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा mlxsw_sp_neigh_entry *neigh_entry, *पंचांगp;

	list_क्रम_each_entry_safe(neigh_entry, पंचांगp, &rअगर->neigh_list,
				 rअगर_list_node) अणु
		mlxsw_sp_neigh_entry_update(mlxsw_sp, neigh_entry, false);
		mlxsw_sp_neigh_entry_destroy(mlxsw_sp, neigh_entry);
	पूर्ण
पूर्ण

क्रमागत mlxsw_sp_nexthop_type अणु
	MLXSW_SP_NEXTHOP_TYPE_ETH,
	MLXSW_SP_NEXTHOP_TYPE_IPIP,
पूर्ण;

क्रमागत mlxsw_sp_nexthop_action अणु
	/* Nexthop क्रमwards packets to an egress RIF */
	MLXSW_SP_NEXTHOP_ACTION_FORWARD,
	/* Nexthop discards packets */
	MLXSW_SP_NEXTHOP_ACTION_DISCARD,
	/* Nexthop traps packets */
	MLXSW_SP_NEXTHOP_ACTION_TRAP,
पूर्ण;

काष्ठा mlxsw_sp_nexthop_key अणु
	काष्ठा fib_nh *fib_nh;
पूर्ण;

काष्ठा mlxsw_sp_nexthop अणु
	काष्ठा list_head neigh_list_node; /* member of neigh entry list */
	काष्ठा list_head rअगर_list_node;
	काष्ठा list_head router_list_node;
	काष्ठा mlxsw_sp_nexthop_group_info *nhgi; /* poपूर्णांकer back to the group
						   * this nexthop beदीर्घs to
						   */
	काष्ठा rhash_head ht_node;
	काष्ठा neigh_table *neigh_tbl;
	काष्ठा mlxsw_sp_nexthop_key key;
	अचिन्हित अक्षर gw_addr[माप(काष्ठा in6_addr)];
	पूर्णांक अगरindex;
	पूर्णांक nh_weight;
	पूर्णांक norm_nh_weight;
	पूर्णांक num_adj_entries;
	काष्ठा mlxsw_sp_rअगर *rअगर;
	u8 should_offload:1, /* set indicates this nexthop should be written
			      * to the adjacency table.
			      */
	   offloaded:1, /* set indicates this nexthop was written to the
			 * adjacency table.
			 */
	   update:1; /* set indicates this nexthop should be updated in the
		      * adjacency table (f.e., its MAC changed).
		      */
	क्रमागत mlxsw_sp_nexthop_action action;
	क्रमागत mlxsw_sp_nexthop_type type;
	जोड़ अणु
		काष्ठा mlxsw_sp_neigh_entry *neigh_entry;
		काष्ठा mlxsw_sp_ipip_entry *ipip_entry;
	पूर्ण;
	अचिन्हित पूर्णांक counter_index;
	bool counter_valid;
पूर्ण;

क्रमागत mlxsw_sp_nexthop_group_type अणु
	MLXSW_SP_NEXTHOP_GROUP_TYPE_IPV4,
	MLXSW_SP_NEXTHOP_GROUP_TYPE_IPV6,
	MLXSW_SP_NEXTHOP_GROUP_TYPE_OBJ,
पूर्ण;

काष्ठा mlxsw_sp_nexthop_group_info अणु
	काष्ठा mlxsw_sp_nexthop_group *nh_grp;
	u32 adj_index;
	u16 ecmp_size;
	u16 count;
	पूर्णांक sum_norm_weight;
	u8 adj_index_valid:1,
	   gateway:1, /* routes using the group use a gateway */
	   is_resilient:1;
	काष्ठा list_head list; /* member in nh_res_grp_list */
	काष्ठा mlxsw_sp_nexthop nexthops[0];
#घोषणा nh_rअगर	nexthops[0].rअगर
पूर्ण;

काष्ठा mlxsw_sp_nexthop_group_vr_key अणु
	u16 vr_id;
	क्रमागत mlxsw_sp_l3proto proto;
पूर्ण;

काष्ठा mlxsw_sp_nexthop_group_vr_entry अणु
	काष्ठा list_head list; /* member in vr_list */
	काष्ठा rhash_head ht_node; /* member in vr_ht */
	refcount_t ref_count;
	काष्ठा mlxsw_sp_nexthop_group_vr_key key;
पूर्ण;

काष्ठा mlxsw_sp_nexthop_group अणु
	काष्ठा rhash_head ht_node;
	काष्ठा list_head fib_list; /* list of fib entries that use this group */
	जोड़ अणु
		काष्ठा अणु
			काष्ठा fib_info *fi;
		पूर्ण ipv4;
		काष्ठा अणु
			u32 id;
		पूर्ण obj;
	पूर्ण;
	काष्ठा mlxsw_sp_nexthop_group_info *nhgi;
	काष्ठा list_head vr_list;
	काष्ठा rhashtable vr_ht;
	क्रमागत mlxsw_sp_nexthop_group_type type;
	bool can_destroy;
पूर्ण;

व्योम mlxsw_sp_nexthop_counter_alloc(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_nexthop *nh)
अणु
	काष्ठा devlink *devlink;

	devlink = priv_to_devlink(mlxsw_sp->core);
	अगर (!devlink_dpipe_table_counter_enabled(devlink,
						 MLXSW_SP_DPIPE_TABLE_NAME_ADJ))
		वापस;

	अगर (mlxsw_sp_flow_counter_alloc(mlxsw_sp, &nh->counter_index))
		वापस;

	nh->counter_valid = true;
पूर्ण

व्योम mlxsw_sp_nexthop_counter_मुक्त(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_nexthop *nh)
अणु
	अगर (!nh->counter_valid)
		वापस;
	mlxsw_sp_flow_counter_मुक्त(mlxsw_sp, nh->counter_index);
	nh->counter_valid = false;
पूर्ण

पूर्णांक mlxsw_sp_nexthop_counter_get(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_nexthop *nh, u64 *p_counter)
अणु
	अगर (!nh->counter_valid)
		वापस -EINVAL;

	वापस mlxsw_sp_flow_counter_get(mlxsw_sp, nh->counter_index,
					 p_counter, शून्य);
पूर्ण

काष्ठा mlxsw_sp_nexthop *mlxsw_sp_nexthop_next(काष्ठा mlxsw_sp_router *router,
					       काष्ठा mlxsw_sp_nexthop *nh)
अणु
	अगर (!nh) अणु
		अगर (list_empty(&router->nexthop_list))
			वापस शून्य;
		अन्यथा
			वापस list_first_entry(&router->nexthop_list,
						typeof(*nh), router_list_node);
	पूर्ण
	अगर (list_is_last(&nh->router_list_node, &router->nexthop_list))
		वापस शून्य;
	वापस list_next_entry(nh, router_list_node);
पूर्ण

bool mlxsw_sp_nexthop_is_क्रमward(स्थिर काष्ठा mlxsw_sp_nexthop *nh)
अणु
	वापस nh->offloaded && nh->action == MLXSW_SP_NEXTHOP_ACTION_FORWARD;
पूर्ण

अचिन्हित अक्षर *mlxsw_sp_nexthop_ha(काष्ठा mlxsw_sp_nexthop *nh)
अणु
	अगर (nh->type != MLXSW_SP_NEXTHOP_TYPE_ETH ||
	    !mlxsw_sp_nexthop_is_क्रमward(nh))
		वापस शून्य;
	वापस nh->neigh_entry->ha;
पूर्ण

पूर्णांक mlxsw_sp_nexthop_indexes(काष्ठा mlxsw_sp_nexthop *nh, u32 *p_adj_index,
			     u32 *p_adj_size, u32 *p_adj_hash_index)
अणु
	काष्ठा mlxsw_sp_nexthop_group_info *nhgi = nh->nhgi;
	u32 adj_hash_index = 0;
	पूर्णांक i;

	अगर (!nh->offloaded || !nhgi->adj_index_valid)
		वापस -EINVAL;

	*p_adj_index = nhgi->adj_index;
	*p_adj_size = nhgi->ecmp_size;

	क्रम (i = 0; i < nhgi->count; i++) अणु
		काष्ठा mlxsw_sp_nexthop *nh_iter = &nhgi->nexthops[i];

		अगर (nh_iter == nh)
			अवरोध;
		अगर (nh_iter->offloaded)
			adj_hash_index += nh_iter->num_adj_entries;
	पूर्ण

	*p_adj_hash_index = adj_hash_index;
	वापस 0;
पूर्ण

काष्ठा mlxsw_sp_rअगर *mlxsw_sp_nexthop_rअगर(काष्ठा mlxsw_sp_nexthop *nh)
अणु
	वापस nh->rअगर;
पूर्ण

bool mlxsw_sp_nexthop_group_has_ipip(काष्ठा mlxsw_sp_nexthop *nh)
अणु
	काष्ठा mlxsw_sp_nexthop_group_info *nhgi = nh->nhgi;
	पूर्णांक i;

	क्रम (i = 0; i < nhgi->count; i++) अणु
		काष्ठा mlxsw_sp_nexthop *nh_iter = &nhgi->nexthops[i];

		अगर (nh_iter->type == MLXSW_SP_NEXTHOP_TYPE_IPIP)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_nexthop_group_vr_ht_params = अणु
	.key_offset = दुरत्व(काष्ठा mlxsw_sp_nexthop_group_vr_entry, key),
	.head_offset = दुरत्व(काष्ठा mlxsw_sp_nexthop_group_vr_entry, ht_node),
	.key_len = माप(काष्ठा mlxsw_sp_nexthop_group_vr_key),
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल काष्ठा mlxsw_sp_nexthop_group_vr_entry *
mlxsw_sp_nexthop_group_vr_entry_lookup(काष्ठा mlxsw_sp_nexthop_group *nh_grp,
				       स्थिर काष्ठा mlxsw_sp_fib *fib)
अणु
	काष्ठा mlxsw_sp_nexthop_group_vr_key key;

	स_रखो(&key, 0, माप(key));
	key.vr_id = fib->vr->id;
	key.proto = fib->proto;
	वापस rhashtable_lookup_fast(&nh_grp->vr_ht, &key,
				      mlxsw_sp_nexthop_group_vr_ht_params);
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop_group_vr_entry_create(काष्ठा mlxsw_sp_nexthop_group *nh_grp,
				       स्थिर काष्ठा mlxsw_sp_fib *fib)
अणु
	काष्ठा mlxsw_sp_nexthop_group_vr_entry *vr_entry;
	पूर्णांक err;

	vr_entry = kzalloc(माप(*vr_entry), GFP_KERNEL);
	अगर (!vr_entry)
		वापस -ENOMEM;

	vr_entry->key.vr_id = fib->vr->id;
	vr_entry->key.proto = fib->proto;
	refcount_set(&vr_entry->ref_count, 1);

	err = rhashtable_insert_fast(&nh_grp->vr_ht, &vr_entry->ht_node,
				     mlxsw_sp_nexthop_group_vr_ht_params);
	अगर (err)
		जाओ err_hashtable_insert;

	list_add(&vr_entry->list, &nh_grp->vr_list);

	वापस 0;

err_hashtable_insert:
	kमुक्त(vr_entry);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_nexthop_group_vr_entry_destroy(काष्ठा mlxsw_sp_nexthop_group *nh_grp,
					काष्ठा mlxsw_sp_nexthop_group_vr_entry *vr_entry)
अणु
	list_del(&vr_entry->list);
	rhashtable_हटाओ_fast(&nh_grp->vr_ht, &vr_entry->ht_node,
			       mlxsw_sp_nexthop_group_vr_ht_params);
	kमुक्त(vr_entry);
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop_group_vr_link(काष्ठा mlxsw_sp_nexthop_group *nh_grp,
			       स्थिर काष्ठा mlxsw_sp_fib *fib)
अणु
	काष्ठा mlxsw_sp_nexthop_group_vr_entry *vr_entry;

	vr_entry = mlxsw_sp_nexthop_group_vr_entry_lookup(nh_grp, fib);
	अगर (vr_entry) अणु
		refcount_inc(&vr_entry->ref_count);
		वापस 0;
	पूर्ण

	वापस mlxsw_sp_nexthop_group_vr_entry_create(nh_grp, fib);
पूर्ण

अटल व्योम
mlxsw_sp_nexthop_group_vr_unlink(काष्ठा mlxsw_sp_nexthop_group *nh_grp,
				 स्थिर काष्ठा mlxsw_sp_fib *fib)
अणु
	काष्ठा mlxsw_sp_nexthop_group_vr_entry *vr_entry;

	vr_entry = mlxsw_sp_nexthop_group_vr_entry_lookup(nh_grp, fib);
	अगर (WARN_ON_ONCE(!vr_entry))
		वापस;

	अगर (!refcount_dec_and_test(&vr_entry->ref_count))
		वापस;

	mlxsw_sp_nexthop_group_vr_entry_destroy(nh_grp, vr_entry);
पूर्ण

काष्ठा mlxsw_sp_nexthop_group_cmp_arg अणु
	क्रमागत mlxsw_sp_nexthop_group_type type;
	जोड़ अणु
		काष्ठा fib_info *fi;
		काष्ठा mlxsw_sp_fib6_entry *fib6_entry;
		u32 id;
	पूर्ण;
पूर्ण;

अटल bool
mlxsw_sp_nexthop6_group_has_nexthop(स्थिर काष्ठा mlxsw_sp_nexthop_group *nh_grp,
				    स्थिर काष्ठा in6_addr *gw, पूर्णांक अगरindex,
				    पूर्णांक weight)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nh_grp->nhgi->count; i++) अणु
		स्थिर काष्ठा mlxsw_sp_nexthop *nh;

		nh = &nh_grp->nhgi->nexthops[i];
		अगर (nh->अगरindex == अगरindex && nh->nh_weight == weight &&
		    ipv6_addr_equal(gw, (काष्ठा in6_addr *) nh->gw_addr))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool
mlxsw_sp_nexthop6_group_cmp(स्थिर काष्ठा mlxsw_sp_nexthop_group *nh_grp,
			    स्थिर काष्ठा mlxsw_sp_fib6_entry *fib6_entry)
अणु
	काष्ठा mlxsw_sp_rt6 *mlxsw_sp_rt6;

	अगर (nh_grp->nhgi->count != fib6_entry->nrt6)
		वापस false;

	list_क्रम_each_entry(mlxsw_sp_rt6, &fib6_entry->rt6_list, list) अणु
		काष्ठा fib6_nh *fib6_nh = mlxsw_sp_rt6->rt->fib6_nh;
		काष्ठा in6_addr *gw;
		पूर्णांक अगरindex, weight;

		अगरindex = fib6_nh->fib_nh_dev->अगरindex;
		weight = fib6_nh->fib_nh_weight;
		gw = &fib6_nh->fib_nh_gw6;
		अगर (!mlxsw_sp_nexthop6_group_has_nexthop(nh_grp, gw, अगरindex,
							 weight))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop_group_cmp(काष्ठा rhashtable_compare_arg *arg, स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा mlxsw_sp_nexthop_group_cmp_arg *cmp_arg = arg->key;
	स्थिर काष्ठा mlxsw_sp_nexthop_group *nh_grp = ptr;

	अगर (nh_grp->type != cmp_arg->type)
		वापस 1;

	चयन (cmp_arg->type) अणु
	हाल MLXSW_SP_NEXTHOP_GROUP_TYPE_IPV4:
		वापस cmp_arg->fi != nh_grp->ipv4.fi;
	हाल MLXSW_SP_NEXTHOP_GROUP_TYPE_IPV6:
		वापस !mlxsw_sp_nexthop6_group_cmp(nh_grp,
						    cmp_arg->fib6_entry);
	हाल MLXSW_SP_NEXTHOP_GROUP_TYPE_OBJ:
		वापस cmp_arg->id != nh_grp->obj.id;
	शेष:
		WARN_ON(1);
		वापस 1;
	पूर्ण
पूर्ण

अटल u32 mlxsw_sp_nexthop_group_hash_obj(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा mlxsw_sp_nexthop_group *nh_grp = data;
	स्थिर काष्ठा mlxsw_sp_nexthop *nh;
	काष्ठा fib_info *fi;
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	चयन (nh_grp->type) अणु
	हाल MLXSW_SP_NEXTHOP_GROUP_TYPE_IPV4:
		fi = nh_grp->ipv4.fi;
		वापस jhash(&fi, माप(fi), seed);
	हाल MLXSW_SP_NEXTHOP_GROUP_TYPE_IPV6:
		val = nh_grp->nhgi->count;
		क्रम (i = 0; i < nh_grp->nhgi->count; i++) अणु
			nh = &nh_grp->nhgi->nexthops[i];
			val ^= jhash(&nh->अगरindex, माप(nh->अगरindex), seed);
			val ^= jhash(&nh->gw_addr, माप(nh->gw_addr), seed);
		पूर्ण
		वापस jhash(&val, माप(val), seed);
	हाल MLXSW_SP_NEXTHOP_GROUP_TYPE_OBJ:
		वापस jhash(&nh_grp->obj.id, माप(nh_grp->obj.id), seed);
	शेष:
		WARN_ON(1);
		वापस 0;
	पूर्ण
पूर्ण

अटल u32
mlxsw_sp_nexthop6_group_hash(काष्ठा mlxsw_sp_fib6_entry *fib6_entry, u32 seed)
अणु
	अचिन्हित पूर्णांक val = fib6_entry->nrt6;
	काष्ठा mlxsw_sp_rt6 *mlxsw_sp_rt6;

	list_क्रम_each_entry(mlxsw_sp_rt6, &fib6_entry->rt6_list, list) अणु
		काष्ठा fib6_nh *fib6_nh = mlxsw_sp_rt6->rt->fib6_nh;
		काष्ठा net_device *dev = fib6_nh->fib_nh_dev;
		काष्ठा in6_addr *gw = &fib6_nh->fib_nh_gw6;

		val ^= jhash(&dev->अगरindex, माप(dev->अगरindex), seed);
		val ^= jhash(gw, माप(*gw), seed);
	पूर्ण

	वापस jhash(&val, माप(val), seed);
पूर्ण

अटल u32
mlxsw_sp_nexthop_group_hash(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा mlxsw_sp_nexthop_group_cmp_arg *cmp_arg = data;

	चयन (cmp_arg->type) अणु
	हाल MLXSW_SP_NEXTHOP_GROUP_TYPE_IPV4:
		वापस jhash(&cmp_arg->fi, माप(cmp_arg->fi), seed);
	हाल MLXSW_SP_NEXTHOP_GROUP_TYPE_IPV6:
		वापस mlxsw_sp_nexthop6_group_hash(cmp_arg->fib6_entry, seed);
	हाल MLXSW_SP_NEXTHOP_GROUP_TYPE_OBJ:
		वापस jhash(&cmp_arg->id, माप(cmp_arg->id), seed);
	शेष:
		WARN_ON(1);
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_nexthop_group_ht_params = अणु
	.head_offset = दुरत्व(काष्ठा mlxsw_sp_nexthop_group, ht_node),
	.hashfn	     = mlxsw_sp_nexthop_group_hash,
	.obj_hashfn  = mlxsw_sp_nexthop_group_hash_obj,
	.obj_cmpfn   = mlxsw_sp_nexthop_group_cmp,
पूर्ण;

अटल पूर्णांक mlxsw_sp_nexthop_group_insert(काष्ठा mlxsw_sp *mlxsw_sp,
					 काष्ठा mlxsw_sp_nexthop_group *nh_grp)
अणु
	अगर (nh_grp->type == MLXSW_SP_NEXTHOP_GROUP_TYPE_IPV6 &&
	    !nh_grp->nhgi->gateway)
		वापस 0;

	वापस rhashtable_insert_fast(&mlxsw_sp->router->nexthop_group_ht,
				      &nh_grp->ht_node,
				      mlxsw_sp_nexthop_group_ht_params);
पूर्ण

अटल व्योम mlxsw_sp_nexthop_group_हटाओ(काष्ठा mlxsw_sp *mlxsw_sp,
					  काष्ठा mlxsw_sp_nexthop_group *nh_grp)
अणु
	अगर (nh_grp->type == MLXSW_SP_NEXTHOP_GROUP_TYPE_IPV6 &&
	    !nh_grp->nhgi->gateway)
		वापस;

	rhashtable_हटाओ_fast(&mlxsw_sp->router->nexthop_group_ht,
			       &nh_grp->ht_node,
			       mlxsw_sp_nexthop_group_ht_params);
पूर्ण

अटल काष्ठा mlxsw_sp_nexthop_group *
mlxsw_sp_nexthop4_group_lookup(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा fib_info *fi)
अणु
	काष्ठा mlxsw_sp_nexthop_group_cmp_arg cmp_arg;

	cmp_arg.type = MLXSW_SP_NEXTHOP_GROUP_TYPE_IPV4;
	cmp_arg.fi = fi;
	वापस rhashtable_lookup_fast(&mlxsw_sp->router->nexthop_group_ht,
				      &cmp_arg,
				      mlxsw_sp_nexthop_group_ht_params);
पूर्ण

अटल काष्ठा mlxsw_sp_nexthop_group *
mlxsw_sp_nexthop6_group_lookup(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_fib6_entry *fib6_entry)
अणु
	काष्ठा mlxsw_sp_nexthop_group_cmp_arg cmp_arg;

	cmp_arg.type = MLXSW_SP_NEXTHOP_GROUP_TYPE_IPV6;
	cmp_arg.fib6_entry = fib6_entry;
	वापस rhashtable_lookup_fast(&mlxsw_sp->router->nexthop_group_ht,
				      &cmp_arg,
				      mlxsw_sp_nexthop_group_ht_params);
पूर्ण

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_nexthop_ht_params = अणु
	.key_offset = दुरत्व(काष्ठा mlxsw_sp_nexthop, key),
	.head_offset = दुरत्व(काष्ठा mlxsw_sp_nexthop, ht_node),
	.key_len = माप(काष्ठा mlxsw_sp_nexthop_key),
पूर्ण;

अटल पूर्णांक mlxsw_sp_nexthop_insert(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_nexthop *nh)
अणु
	वापस rhashtable_insert_fast(&mlxsw_sp->router->nexthop_ht,
				      &nh->ht_node, mlxsw_sp_nexthop_ht_params);
पूर्ण

अटल व्योम mlxsw_sp_nexthop_हटाओ(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_nexthop *nh)
अणु
	rhashtable_हटाओ_fast(&mlxsw_sp->router->nexthop_ht, &nh->ht_node,
			       mlxsw_sp_nexthop_ht_params);
पूर्ण

अटल काष्ठा mlxsw_sp_nexthop *
mlxsw_sp_nexthop_lookup(काष्ठा mlxsw_sp *mlxsw_sp,
			काष्ठा mlxsw_sp_nexthop_key key)
अणु
	वापस rhashtable_lookup_fast(&mlxsw_sp->router->nexthop_ht, &key,
				      mlxsw_sp_nexthop_ht_params);
पूर्ण

अटल पूर्णांक mlxsw_sp_adj_index_mass_update_vr(काष्ठा mlxsw_sp *mlxsw_sp,
					     क्रमागत mlxsw_sp_l3proto proto,
					     u16 vr_id,
					     u32 adj_index, u16 ecmp_size,
					     u32 new_adj_index,
					     u16 new_ecmp_size)
अणु
	अक्षर raleu_pl[MLXSW_REG_RALEU_LEN];

	mlxsw_reg_raleu_pack(raleu_pl,
			     (क्रमागत mlxsw_reg_ralxx_protocol) proto, vr_id,
			     adj_index, ecmp_size, new_adj_index,
			     new_ecmp_size);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(raleu), raleu_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_adj_index_mass_update(काष्ठा mlxsw_sp *mlxsw_sp,
					  काष्ठा mlxsw_sp_nexthop_group *nh_grp,
					  u32 old_adj_index, u16 old_ecmp_size)
अणु
	काष्ठा mlxsw_sp_nexthop_group_info *nhgi = nh_grp->nhgi;
	काष्ठा mlxsw_sp_nexthop_group_vr_entry *vr_entry;
	पूर्णांक err;

	list_क्रम_each_entry(vr_entry, &nh_grp->vr_list, list) अणु
		err = mlxsw_sp_adj_index_mass_update_vr(mlxsw_sp,
							vr_entry->key.proto,
							vr_entry->key.vr_id,
							old_adj_index,
							old_ecmp_size,
							nhgi->adj_index,
							nhgi->ecmp_size);
		अगर (err)
			जाओ err_mass_update_vr;
	पूर्ण
	वापस 0;

err_mass_update_vr:
	list_क्रम_each_entry_जारी_reverse(vr_entry, &nh_grp->vr_list, list)
		mlxsw_sp_adj_index_mass_update_vr(mlxsw_sp, vr_entry->key.proto,
						  vr_entry->key.vr_id,
						  nhgi->adj_index,
						  nhgi->ecmp_size,
						  old_adj_index, old_ecmp_size);
	वापस err;
पूर्ण

अटल पूर्णांक __mlxsw_sp_nexthop_eth_update(काष्ठा mlxsw_sp *mlxsw_sp,
					 u32 adj_index,
					 काष्ठा mlxsw_sp_nexthop *nh,
					 bool क्रमce, अक्षर *ratr_pl)
अणु
	काष्ठा mlxsw_sp_neigh_entry *neigh_entry = nh->neigh_entry;
	क्रमागत mlxsw_reg_ratr_op op;
	u16 rअगर_index;

	rअगर_index = nh->rअगर ? nh->rअगर->rअगर_index :
			      mlxsw_sp->router->lb_rअगर_index;
	op = क्रमce ? MLXSW_REG_RATR_OP_WRITE_WRITE_ENTRY :
		     MLXSW_REG_RATR_OP_WRITE_WRITE_ENTRY_ON_ACTIVITY;
	mlxsw_reg_ratr_pack(ratr_pl, op, true, MLXSW_REG_RATR_TYPE_ETHERNET,
			    adj_index, rअगर_index);
	चयन (nh->action) अणु
	हाल MLXSW_SP_NEXTHOP_ACTION_FORWARD:
		mlxsw_reg_ratr_eth_entry_pack(ratr_pl, neigh_entry->ha);
		अवरोध;
	हाल MLXSW_SP_NEXTHOP_ACTION_DISCARD:
		mlxsw_reg_ratr_trap_action_set(ratr_pl,
					       MLXSW_REG_RATR_TRAP_ACTION_DISCARD_ERRORS);
		अवरोध;
	हाल MLXSW_SP_NEXTHOP_ACTION_TRAP:
		mlxsw_reg_ratr_trap_action_set(ratr_pl,
					       MLXSW_REG_RATR_TRAP_ACTION_TRAP);
		mlxsw_reg_ratr_trap_id_set(ratr_pl, MLXSW_TRAP_ID_RTR_EGRESS0);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस -EINVAL;
	पूर्ण
	अगर (nh->counter_valid)
		mlxsw_reg_ratr_counter_pack(ratr_pl, nh->counter_index, true);
	अन्यथा
		mlxsw_reg_ratr_counter_pack(ratr_pl, 0, false);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ratr), ratr_pl);
पूर्ण

पूर्णांक mlxsw_sp_nexthop_eth_update(काष्ठा mlxsw_sp *mlxsw_sp, u32 adj_index,
				काष्ठा mlxsw_sp_nexthop *nh, bool क्रमce,
				अक्षर *ratr_pl)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nh->num_adj_entries; i++) अणु
		पूर्णांक err;

		err = __mlxsw_sp_nexthop_eth_update(mlxsw_sp, adj_index + i,
						    nh, क्रमce, ratr_pl);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __mlxsw_sp_nexthop_ipip_update(काष्ठा mlxsw_sp *mlxsw_sp,
					  u32 adj_index,
					  काष्ठा mlxsw_sp_nexthop *nh,
					  bool क्रमce, अक्षर *ratr_pl)
अणु
	स्थिर काष्ठा mlxsw_sp_ipip_ops *ipip_ops;

	ipip_ops = mlxsw_sp->router->ipip_ops_arr[nh->ipip_entry->ipipt];
	वापस ipip_ops->nexthop_update(mlxsw_sp, adj_index, nh->ipip_entry,
					क्रमce, ratr_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_nexthop_ipip_update(काष्ठा mlxsw_sp *mlxsw_sp,
					u32 adj_index,
					काष्ठा mlxsw_sp_nexthop *nh, bool क्रमce,
					अक्षर *ratr_pl)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nh->num_adj_entries; i++) अणु
		पूर्णांक err;

		err = __mlxsw_sp_nexthop_ipip_update(mlxsw_sp, adj_index + i,
						     nh, क्रमce, ratr_pl);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_nexthop_update(काष्ठा mlxsw_sp *mlxsw_sp, u32 adj_index,
				   काष्ठा mlxsw_sp_nexthop *nh, bool क्रमce,
				   अक्षर *ratr_pl)
अणु
	/* When action is discard or trap, the nexthop must be
	 * programmed as an Ethernet nexthop.
	 */
	अगर (nh->type == MLXSW_SP_NEXTHOP_TYPE_ETH ||
	    nh->action == MLXSW_SP_NEXTHOP_ACTION_DISCARD ||
	    nh->action == MLXSW_SP_NEXTHOP_ACTION_TRAP)
		वापस mlxsw_sp_nexthop_eth_update(mlxsw_sp, adj_index, nh,
						   क्रमce, ratr_pl);
	अन्यथा
		वापस mlxsw_sp_nexthop_ipip_update(mlxsw_sp, adj_index, nh,
						    क्रमce, ratr_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop_group_update(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_nexthop_group_info *nhgi,
			      bool पुनः_स्मृतिate)
अणु
	अक्षर ratr_pl[MLXSW_REG_RATR_LEN];
	u32 adj_index = nhgi->adj_index; /* base */
	काष्ठा mlxsw_sp_nexthop *nh;
	पूर्णांक i;

	क्रम (i = 0; i < nhgi->count; i++) अणु
		nh = &nhgi->nexthops[i];

		अगर (!nh->should_offload) अणु
			nh->offloaded = 0;
			जारी;
		पूर्ण

		अगर (nh->update || पुनः_स्मृतिate) अणु
			पूर्णांक err = 0;

			err = mlxsw_sp_nexthop_update(mlxsw_sp, adj_index, nh,
						      true, ratr_pl);
			अगर (err)
				वापस err;
			nh->update = 0;
			nh->offloaded = 1;
		पूर्ण
		adj_index += nh->num_adj_entries;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop_fib_entries_update(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_nexthop_group *nh_grp)
अणु
	काष्ठा mlxsw_sp_fib_entry *fib_entry;
	पूर्णांक err;

	list_क्रम_each_entry(fib_entry, &nh_grp->fib_list, nexthop_group_node) अणु
		err = mlxsw_sp_fib_entry_update(mlxsw_sp, fib_entry);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा mlxsw_sp_adj_grp_size_range अणु
	u16 start; /* Inclusive */
	u16 end; /* Inclusive */
पूर्ण;

/* Ordered by range start value */
अटल स्थिर काष्ठा mlxsw_sp_adj_grp_size_range
mlxsw_sp1_adj_grp_size_ranges[] = अणु
	अणु .start = 1, .end = 64 पूर्ण,
	अणु .start = 512, .end = 512 पूर्ण,
	अणु .start = 1024, .end = 1024 पूर्ण,
	अणु .start = 2048, .end = 2048 पूर्ण,
	अणु .start = 4096, .end = 4096 पूर्ण,
पूर्ण;

/* Ordered by range start value */
अटल स्थिर काष्ठा mlxsw_sp_adj_grp_size_range
mlxsw_sp2_adj_grp_size_ranges[] = अणु
	अणु .start = 1, .end = 128 पूर्ण,
	अणु .start = 256, .end = 256 पूर्ण,
	अणु .start = 512, .end = 512 पूर्ण,
	अणु .start = 1024, .end = 1024 पूर्ण,
	अणु .start = 2048, .end = 2048 पूर्ण,
	अणु .start = 4096, .end = 4096 पूर्ण,
पूर्ण;

अटल व्योम mlxsw_sp_adj_grp_size_round_up(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
					   u16 *p_adj_grp_size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mlxsw_sp->router->adj_grp_size_ranges_count; i++) अणु
		स्थिर काष्ठा mlxsw_sp_adj_grp_size_range *size_range;

		size_range = &mlxsw_sp->router->adj_grp_size_ranges[i];

		अगर (*p_adj_grp_size >= size_range->start &&
		    *p_adj_grp_size <= size_range->end)
			वापस;

		अगर (*p_adj_grp_size <= size_range->end) अणु
			*p_adj_grp_size = size_range->end;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp_adj_grp_size_round_करोwn(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
					     u16 *p_adj_grp_size,
					     अचिन्हित पूर्णांक alloc_size)
अणु
	पूर्णांक i;

	क्रम (i = mlxsw_sp->router->adj_grp_size_ranges_count - 1; i >= 0; i--) अणु
		स्थिर काष्ठा mlxsw_sp_adj_grp_size_range *size_range;

		size_range = &mlxsw_sp->router->adj_grp_size_ranges[i];

		अगर (alloc_size >= size_range->end) अणु
			*p_adj_grp_size = size_range->end;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_fix_adj_grp_size(काष्ठा mlxsw_sp *mlxsw_sp,
				     u16 *p_adj_grp_size)
अणु
	अचिन्हित पूर्णांक alloc_size;
	पूर्णांक err;

	/* Round up the requested group size to the next size supported
	 * by the device and make sure the request can be satisfied.
	 */
	mlxsw_sp_adj_grp_size_round_up(mlxsw_sp, p_adj_grp_size);
	err = mlxsw_sp_kvdl_alloc_count_query(mlxsw_sp,
					      MLXSW_SP_KVDL_ENTRY_TYPE_ADJ,
					      *p_adj_grp_size, &alloc_size);
	अगर (err)
		वापस err;
	/* It is possible the allocation results in more allocated
	 * entries than requested. Try to use as much of them as
	 * possible.
	 */
	mlxsw_sp_adj_grp_size_round_करोwn(mlxsw_sp, p_adj_grp_size, alloc_size);

	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_nexthop_group_normalize(काष्ठा mlxsw_sp_nexthop_group_info *nhgi)
अणु
	पूर्णांक i, g = 0, sum_norm_weight = 0;
	काष्ठा mlxsw_sp_nexthop *nh;

	क्रम (i = 0; i < nhgi->count; i++) अणु
		nh = &nhgi->nexthops[i];

		अगर (!nh->should_offload)
			जारी;
		अगर (g > 0)
			g = gcd(nh->nh_weight, g);
		अन्यथा
			g = nh->nh_weight;
	पूर्ण

	क्रम (i = 0; i < nhgi->count; i++) अणु
		nh = &nhgi->nexthops[i];

		अगर (!nh->should_offload)
			जारी;
		nh->norm_nh_weight = nh->nh_weight / g;
		sum_norm_weight += nh->norm_nh_weight;
	पूर्ण

	nhgi->sum_norm_weight = sum_norm_weight;
पूर्ण

अटल व्योम
mlxsw_sp_nexthop_group_rebalance(काष्ठा mlxsw_sp_nexthop_group_info *nhgi)
अणु
	पूर्णांक i, weight = 0, lower_bound = 0;
	पूर्णांक total = nhgi->sum_norm_weight;
	u16 ecmp_size = nhgi->ecmp_size;

	क्रम (i = 0; i < nhgi->count; i++) अणु
		काष्ठा mlxsw_sp_nexthop *nh = &nhgi->nexthops[i];
		पूर्णांक upper_bound;

		अगर (!nh->should_offload)
			जारी;
		weight += nh->norm_nh_weight;
		upper_bound = DIV_ROUND_CLOSEST(ecmp_size * weight, total);
		nh->num_adj_entries = upper_bound - lower_bound;
		lower_bound = upper_bound;
	पूर्ण
पूर्ण

अटल काष्ठा mlxsw_sp_nexthop *
mlxsw_sp_rt6_nexthop(काष्ठा mlxsw_sp_nexthop_group *nh_grp,
		     स्थिर काष्ठा mlxsw_sp_rt6 *mlxsw_sp_rt6);

अटल व्योम
mlxsw_sp_nexthop4_group_offload_refresh(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_nexthop_group *nh_grp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nh_grp->nhgi->count; i++) अणु
		काष्ठा mlxsw_sp_nexthop *nh = &nh_grp->nhgi->nexthops[i];

		अगर (nh->offloaded)
			nh->key.fib_nh->fib_nh_flags |= RTNH_F_OFFLOAD;
		अन्यथा
			nh->key.fib_nh->fib_nh_flags &= ~RTNH_F_OFFLOAD;
	पूर्ण
पूर्ण

अटल व्योम
__mlxsw_sp_nexthop6_group_offload_refresh(काष्ठा mlxsw_sp_nexthop_group *nh_grp,
					  काष्ठा mlxsw_sp_fib6_entry *fib6_entry)
अणु
	काष्ठा mlxsw_sp_rt6 *mlxsw_sp_rt6;

	list_क्रम_each_entry(mlxsw_sp_rt6, &fib6_entry->rt6_list, list) अणु
		काष्ठा fib6_nh *fib6_nh = mlxsw_sp_rt6->rt->fib6_nh;
		काष्ठा mlxsw_sp_nexthop *nh;

		nh = mlxsw_sp_rt6_nexthop(nh_grp, mlxsw_sp_rt6);
		अगर (nh && nh->offloaded)
			fib6_nh->fib_nh_flags |= RTNH_F_OFFLOAD;
		अन्यथा
			fib6_nh->fib_nh_flags &= ~RTNH_F_OFFLOAD;
	पूर्ण
पूर्ण

अटल व्योम
mlxsw_sp_nexthop6_group_offload_refresh(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_nexthop_group *nh_grp)
अणु
	काष्ठा mlxsw_sp_fib6_entry *fib6_entry;

	/* Unक्रमtunately, in IPv6 the route and the nexthop are described by
	 * the same काष्ठा, so we need to iterate over all the routes using the
	 * nexthop group and set / clear the offload indication क्रम them.
	 */
	list_क्रम_each_entry(fib6_entry, &nh_grp->fib_list,
			    common.nexthop_group_node)
		__mlxsw_sp_nexthop6_group_offload_refresh(nh_grp, fib6_entry);
पूर्ण

अटल व्योम
mlxsw_sp_nexthop_bucket_offload_refresh(काष्ठा mlxsw_sp *mlxsw_sp,
					स्थिर काष्ठा mlxsw_sp_nexthop *nh,
					u16 bucket_index)
अणु
	काष्ठा mlxsw_sp_nexthop_group *nh_grp = nh->nhgi->nh_grp;
	bool offload = false, trap = false;

	अगर (nh->offloaded) अणु
		अगर (nh->action == MLXSW_SP_NEXTHOP_ACTION_TRAP)
			trap = true;
		अन्यथा
			offload = true;
	पूर्ण
	nexthop_bucket_set_hw_flags(mlxsw_sp_net(mlxsw_sp), nh_grp->obj.id,
				    bucket_index, offload, trap);
पूर्ण

अटल व्योम
mlxsw_sp_nexthop_obj_group_offload_refresh(काष्ठा mlxsw_sp *mlxsw_sp,
					   काष्ठा mlxsw_sp_nexthop_group *nh_grp)
अणु
	पूर्णांक i;

	/* Do not update the flags अगर the nexthop group is being destroyed
	 * since:
	 * 1. The nexthop objects is being deleted, in which हाल the flags are
	 * irrelevant.
	 * 2. The nexthop group was replaced by a newer group, in which हाल
	 * the flags of the nexthop object were alपढ़ोy updated based on the
	 * new group.
	 */
	अगर (nh_grp->can_destroy)
		वापस;

	nexthop_set_hw_flags(mlxsw_sp_net(mlxsw_sp), nh_grp->obj.id,
			     nh_grp->nhgi->adj_index_valid, false);

	/* Update flags of inभागidual nexthop buckets in हाल of a resilient
	 * nexthop group.
	 */
	अगर (!nh_grp->nhgi->is_resilient)
		वापस;

	क्रम (i = 0; i < nh_grp->nhgi->count; i++) अणु
		काष्ठा mlxsw_sp_nexthop *nh = &nh_grp->nhgi->nexthops[i];

		mlxsw_sp_nexthop_bucket_offload_refresh(mlxsw_sp, nh, i);
	पूर्ण
पूर्ण

अटल व्योम
mlxsw_sp_nexthop_group_offload_refresh(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_nexthop_group *nh_grp)
अणु
	चयन (nh_grp->type) अणु
	हाल MLXSW_SP_NEXTHOP_GROUP_TYPE_IPV4:
		mlxsw_sp_nexthop4_group_offload_refresh(mlxsw_sp, nh_grp);
		अवरोध;
	हाल MLXSW_SP_NEXTHOP_GROUP_TYPE_IPV6:
		mlxsw_sp_nexthop6_group_offload_refresh(mlxsw_sp, nh_grp);
		अवरोध;
	हाल MLXSW_SP_NEXTHOP_GROUP_TYPE_OBJ:
		mlxsw_sp_nexthop_obj_group_offload_refresh(mlxsw_sp, nh_grp);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop_group_refresh(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_nexthop_group *nh_grp)
अणु
	काष्ठा mlxsw_sp_nexthop_group_info *nhgi = nh_grp->nhgi;
	u16 ecmp_size, old_ecmp_size;
	काष्ठा mlxsw_sp_nexthop *nh;
	bool offload_change = false;
	u32 adj_index;
	bool old_adj_index_valid;
	पूर्णांक i, err2, err = 0;
	u32 old_adj_index;

	अगर (!nhgi->gateway)
		वापस mlxsw_sp_nexthop_fib_entries_update(mlxsw_sp, nh_grp);

	क्रम (i = 0; i < nhgi->count; i++) अणु
		nh = &nhgi->nexthops[i];

		अगर (nh->should_offload != nh->offloaded) अणु
			offload_change = true;
			अगर (nh->should_offload)
				nh->update = 1;
		पूर्ण
	पूर्ण
	अगर (!offload_change) अणु
		/* Nothing was added or हटाओd, so no need to पुनः_स्मृतिate. Just
		 * update MAC on existing adjacency indexes.
		 */
		err = mlxsw_sp_nexthop_group_update(mlxsw_sp, nhgi, false);
		अगर (err) अणु
			dev_warn(mlxsw_sp->bus_info->dev, "Failed to update neigh MAC in adjacency table.\n");
			जाओ set_trap;
		पूर्ण
		/* Flags of inभागidual nexthop buckets might need to be
		 * updated.
		 */
		mlxsw_sp_nexthop_group_offload_refresh(mlxsw_sp, nh_grp);
		वापस 0;
	पूर्ण
	mlxsw_sp_nexthop_group_normalize(nhgi);
	अगर (!nhgi->sum_norm_weight)
		/* No neigh of this group is connected so we just set
		 * the trap and let everthing flow through kernel.
		 */
		जाओ set_trap;

	ecmp_size = nhgi->sum_norm_weight;
	err = mlxsw_sp_fix_adj_grp_size(mlxsw_sp, &ecmp_size);
	अगर (err)
		/* No valid allocation size available. */
		जाओ set_trap;

	err = mlxsw_sp_kvdl_alloc(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ,
				  ecmp_size, &adj_index);
	अगर (err) अणु
		/* We ran out of KVD linear space, just set the
		 * trap and let everything flow through kernel.
		 */
		dev_warn(mlxsw_sp->bus_info->dev, "Failed to allocate KVD linear area for nexthop group.\n");
		जाओ set_trap;
	पूर्ण
	old_adj_index_valid = nhgi->adj_index_valid;
	old_adj_index = nhgi->adj_index;
	old_ecmp_size = nhgi->ecmp_size;
	nhgi->adj_index_valid = 1;
	nhgi->adj_index = adj_index;
	nhgi->ecmp_size = ecmp_size;
	mlxsw_sp_nexthop_group_rebalance(nhgi);
	err = mlxsw_sp_nexthop_group_update(mlxsw_sp, nhgi, true);
	अगर (err) अणु
		dev_warn(mlxsw_sp->bus_info->dev, "Failed to update neigh MAC in adjacency table.\n");
		जाओ set_trap;
	पूर्ण

	mlxsw_sp_nexthop_group_offload_refresh(mlxsw_sp, nh_grp);

	अगर (!old_adj_index_valid) अणु
		/* The trap was set क्रम fib entries, so we have to call
		 * fib entry update to unset it and use adjacency index.
		 */
		err = mlxsw_sp_nexthop_fib_entries_update(mlxsw_sp, nh_grp);
		अगर (err) अणु
			dev_warn(mlxsw_sp->bus_info->dev, "Failed to add adjacency index to fib entries.\n");
			जाओ set_trap;
		पूर्ण
		वापस 0;
	पूर्ण

	err = mlxsw_sp_adj_index_mass_update(mlxsw_sp, nh_grp,
					     old_adj_index, old_ecmp_size);
	mlxsw_sp_kvdl_मुक्त(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ,
			   old_ecmp_size, old_adj_index);
	अगर (err) अणु
		dev_warn(mlxsw_sp->bus_info->dev, "Failed to mass-update adjacency index for nexthop group.\n");
		जाओ set_trap;
	पूर्ण

	वापस 0;

set_trap:
	old_adj_index_valid = nhgi->adj_index_valid;
	nhgi->adj_index_valid = 0;
	क्रम (i = 0; i < nhgi->count; i++) अणु
		nh = &nhgi->nexthops[i];
		nh->offloaded = 0;
	पूर्ण
	err2 = mlxsw_sp_nexthop_fib_entries_update(mlxsw_sp, nh_grp);
	अगर (err2)
		dev_warn(mlxsw_sp->bus_info->dev, "Failed to set traps for fib entries.\n");
	mlxsw_sp_nexthop_group_offload_refresh(mlxsw_sp, nh_grp);
	अगर (old_adj_index_valid)
		mlxsw_sp_kvdl_मुक्त(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ,
				   nhgi->ecmp_size, nhgi->adj_index);
	वापस err;
पूर्ण

अटल व्योम __mlxsw_sp_nexthop_neigh_update(काष्ठा mlxsw_sp_nexthop *nh,
					    bool removing)
अणु
	अगर (!removing) अणु
		nh->action = MLXSW_SP_NEXTHOP_ACTION_FORWARD;
		nh->should_offload = 1;
	पूर्ण अन्यथा अगर (nh->nhgi->is_resilient) अणु
		nh->action = MLXSW_SP_NEXTHOP_ACTION_TRAP;
		nh->should_offload = 1;
	पूर्ण अन्यथा अणु
		nh->should_offload = 0;
	पूर्ण
	nh->update = 1;
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop_dead_neigh_replace(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_neigh_entry *neigh_entry)
अणु
	काष्ठा neighbour *n, *old_n = neigh_entry->key.n;
	काष्ठा mlxsw_sp_nexthop *nh;
	bool entry_connected;
	u8 nud_state, dead;
	पूर्णांक err;

	nh = list_first_entry(&neigh_entry->nexthop_list,
			      काष्ठा mlxsw_sp_nexthop, neigh_list_node);

	n = neigh_lookup(nh->neigh_tbl, &nh->gw_addr, nh->rअगर->dev);
	अगर (!n) अणु
		n = neigh_create(nh->neigh_tbl, &nh->gw_addr, nh->rअगर->dev);
		अगर (IS_ERR(n))
			वापस PTR_ERR(n);
		neigh_event_send(n, शून्य);
	पूर्ण

	mlxsw_sp_neigh_entry_हटाओ(mlxsw_sp, neigh_entry);
	neigh_entry->key.n = n;
	err = mlxsw_sp_neigh_entry_insert(mlxsw_sp, neigh_entry);
	अगर (err)
		जाओ err_neigh_entry_insert;

	पढ़ो_lock_bh(&n->lock);
	nud_state = n->nud_state;
	dead = n->dead;
	पढ़ो_unlock_bh(&n->lock);
	entry_connected = nud_state & NUD_VALID && !dead;

	list_क्रम_each_entry(nh, &neigh_entry->nexthop_list,
			    neigh_list_node) अणु
		neigh_release(old_n);
		neigh_clone(n);
		__mlxsw_sp_nexthop_neigh_update(nh, !entry_connected);
		mlxsw_sp_nexthop_group_refresh(mlxsw_sp, nh->nhgi->nh_grp);
	पूर्ण

	neigh_release(n);

	वापस 0;

err_neigh_entry_insert:
	neigh_entry->key.n = old_n;
	mlxsw_sp_neigh_entry_insert(mlxsw_sp, neigh_entry);
	neigh_release(n);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_nexthop_neigh_update(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_neigh_entry *neigh_entry,
			      bool removing, bool dead)
अणु
	काष्ठा mlxsw_sp_nexthop *nh;

	अगर (list_empty(&neigh_entry->nexthop_list))
		वापस;

	अगर (dead) अणु
		पूर्णांक err;

		err = mlxsw_sp_nexthop_dead_neigh_replace(mlxsw_sp,
							  neigh_entry);
		अगर (err)
			dev_err(mlxsw_sp->bus_info->dev, "Failed to replace dead neigh\n");
		वापस;
	पूर्ण

	list_क्रम_each_entry(nh, &neigh_entry->nexthop_list,
			    neigh_list_node) अणु
		__mlxsw_sp_nexthop_neigh_update(nh, removing);
		mlxsw_sp_nexthop_group_refresh(mlxsw_sp, nh->nhgi->nh_grp);
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp_nexthop_rअगर_init(काष्ठा mlxsw_sp_nexthop *nh,
				      काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	अगर (nh->rअगर)
		वापस;

	nh->rअगर = rअगर;
	list_add(&nh->rअगर_list_node, &rअगर->nexthop_list);
पूर्ण

अटल व्योम mlxsw_sp_nexthop_rअगर_fini(काष्ठा mlxsw_sp_nexthop *nh)
अणु
	अगर (!nh->rअगर)
		वापस;

	list_del(&nh->rअगर_list_node);
	nh->rअगर = शून्य;
पूर्ण

अटल पूर्णांक mlxsw_sp_nexthop_neigh_init(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_nexthop *nh)
अणु
	काष्ठा mlxsw_sp_neigh_entry *neigh_entry;
	काष्ठा neighbour *n;
	u8 nud_state, dead;
	पूर्णांक err;

	अगर (!nh->nhgi->gateway || nh->neigh_entry)
		वापस 0;

	/* Take a reference of neigh here ensuring that neigh would
	 * not be deकाष्ठाed beक्रमe the nexthop entry is finished.
	 * The reference is taken either in neigh_lookup() or
	 * in neigh_create() in हाल n is not found.
	 */
	n = neigh_lookup(nh->neigh_tbl, &nh->gw_addr, nh->rअगर->dev);
	अगर (!n) अणु
		n = neigh_create(nh->neigh_tbl, &nh->gw_addr, nh->rअगर->dev);
		अगर (IS_ERR(n))
			वापस PTR_ERR(n);
		neigh_event_send(n, शून्य);
	पूर्ण
	neigh_entry = mlxsw_sp_neigh_entry_lookup(mlxsw_sp, n);
	अगर (!neigh_entry) अणु
		neigh_entry = mlxsw_sp_neigh_entry_create(mlxsw_sp, n);
		अगर (IS_ERR(neigh_entry)) अणु
			err = -EINVAL;
			जाओ err_neigh_entry_create;
		पूर्ण
	पूर्ण

	/* If that is the first nexthop connected to that neigh, add to
	 * nexthop_neighs_list
	 */
	अगर (list_empty(&neigh_entry->nexthop_list))
		list_add_tail(&neigh_entry->nexthop_neighs_list_node,
			      &mlxsw_sp->router->nexthop_neighs_list);

	nh->neigh_entry = neigh_entry;
	list_add_tail(&nh->neigh_list_node, &neigh_entry->nexthop_list);
	पढ़ो_lock_bh(&n->lock);
	nud_state = n->nud_state;
	dead = n->dead;
	पढ़ो_unlock_bh(&n->lock);
	__mlxsw_sp_nexthop_neigh_update(nh, !(nud_state & NUD_VALID && !dead));

	वापस 0;

err_neigh_entry_create:
	neigh_release(n);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_nexthop_neigh_fini(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_nexthop *nh)
अणु
	काष्ठा mlxsw_sp_neigh_entry *neigh_entry = nh->neigh_entry;
	काष्ठा neighbour *n;

	अगर (!neigh_entry)
		वापस;
	n = neigh_entry->key.n;

	__mlxsw_sp_nexthop_neigh_update(nh, true);
	list_del(&nh->neigh_list_node);
	nh->neigh_entry = शून्य;

	/* If that is the last nexthop connected to that neigh, हटाओ from
	 * nexthop_neighs_list
	 */
	अगर (list_empty(&neigh_entry->nexthop_list))
		list_del(&neigh_entry->nexthop_neighs_list_node);

	अगर (!neigh_entry->connected && list_empty(&neigh_entry->nexthop_list))
		mlxsw_sp_neigh_entry_destroy(mlxsw_sp, neigh_entry);

	neigh_release(n);
पूर्ण

अटल bool mlxsw_sp_ipip_netdev_ul_up(काष्ठा net_device *ol_dev)
अणु
	काष्ठा net_device *ul_dev;
	bool is_up;

	rcu_पढ़ो_lock();
	ul_dev = __mlxsw_sp_ipip_netdev_ul_dev_get(ol_dev);
	is_up = ul_dev ? (ul_dev->flags & IFF_UP) : true;
	rcu_पढ़ो_unlock();

	वापस is_up;
पूर्ण

अटल व्योम mlxsw_sp_nexthop_ipip_init(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_nexthop *nh,
				       काष्ठा mlxsw_sp_ipip_entry *ipip_entry)
अणु
	bool removing;

	अगर (!nh->nhgi->gateway || nh->ipip_entry)
		वापस;

	nh->ipip_entry = ipip_entry;
	removing = !mlxsw_sp_ipip_netdev_ul_up(ipip_entry->ol_dev);
	__mlxsw_sp_nexthop_neigh_update(nh, removing);
	mlxsw_sp_nexthop_rअगर_init(nh, &ipip_entry->ol_lb->common);
पूर्ण

अटल व्योम mlxsw_sp_nexthop_ipip_fini(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_nexthop *nh)
अणु
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry = nh->ipip_entry;

	अगर (!ipip_entry)
		वापस;

	__mlxsw_sp_nexthop_neigh_update(nh, true);
	nh->ipip_entry = शून्य;
पूर्ण

अटल bool mlxsw_sp_nexthop4_ipip_type(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
					स्थिर काष्ठा fib_nh *fib_nh,
					क्रमागत mlxsw_sp_ipip_type *p_ipipt)
अणु
	काष्ठा net_device *dev = fib_nh->fib_nh_dev;

	वापस dev &&
	       fib_nh->nh_parent->fib_type == RTN_UNICAST &&
	       mlxsw_sp_netdev_ipip_type(mlxsw_sp, dev, p_ipipt);
पूर्ण

अटल पूर्णांक mlxsw_sp_nexthop_type_init(काष्ठा mlxsw_sp *mlxsw_sp,
				      काष्ठा mlxsw_sp_nexthop *nh,
				      स्थिर काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा mlxsw_sp_ipip_ops *ipip_ops;
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry;
	काष्ठा mlxsw_sp_rअगर *rअगर;
	पूर्णांक err;

	ipip_entry = mlxsw_sp_ipip_entry_find_by_ol_dev(mlxsw_sp, dev);
	अगर (ipip_entry) अणु
		ipip_ops = mlxsw_sp->router->ipip_ops_arr[ipip_entry->ipipt];
		अगर (ipip_ops->can_offload(mlxsw_sp, dev)) अणु
			nh->type = MLXSW_SP_NEXTHOP_TYPE_IPIP;
			mlxsw_sp_nexthop_ipip_init(mlxsw_sp, nh, ipip_entry);
			वापस 0;
		पूर्ण
	पूर्ण

	nh->type = MLXSW_SP_NEXTHOP_TYPE_ETH;
	rअगर = mlxsw_sp_rअगर_find_by_dev(mlxsw_sp, dev);
	अगर (!rअगर)
		वापस 0;

	mlxsw_sp_nexthop_rअगर_init(nh, rअगर);
	err = mlxsw_sp_nexthop_neigh_init(mlxsw_sp, nh);
	अगर (err)
		जाओ err_neigh_init;

	वापस 0;

err_neigh_init:
	mlxsw_sp_nexthop_rअगर_fini(nh);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_nexthop_type_fini(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_nexthop *nh)
अणु
	चयन (nh->type) अणु
	हाल MLXSW_SP_NEXTHOP_TYPE_ETH:
		mlxsw_sp_nexthop_neigh_fini(mlxsw_sp, nh);
		mlxsw_sp_nexthop_rअगर_fini(nh);
		अवरोध;
	हाल MLXSW_SP_NEXTHOP_TYPE_IPIP:
		mlxsw_sp_nexthop_rअगर_fini(nh);
		mlxsw_sp_nexthop_ipip_fini(mlxsw_sp, nh);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_nexthop4_init(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_nexthop_group *nh_grp,
				  काष्ठा mlxsw_sp_nexthop *nh,
				  काष्ठा fib_nh *fib_nh)
अणु
	काष्ठा net_device *dev = fib_nh->fib_nh_dev;
	काष्ठा in_device *in_dev;
	पूर्णांक err;

	nh->nhgi = nh_grp->nhgi;
	nh->key.fib_nh = fib_nh;
#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
	nh->nh_weight = fib_nh->fib_nh_weight;
#अन्यथा
	nh->nh_weight = 1;
#पूर्ण_अगर
	स_नकल(&nh->gw_addr, &fib_nh->fib_nh_gw4, माप(fib_nh->fib_nh_gw4));
	nh->neigh_tbl = &arp_tbl;
	err = mlxsw_sp_nexthop_insert(mlxsw_sp, nh);
	अगर (err)
		वापस err;

	mlxsw_sp_nexthop_counter_alloc(mlxsw_sp, nh);
	list_add_tail(&nh->router_list_node, &mlxsw_sp->router->nexthop_list);

	अगर (!dev)
		वापस 0;
	nh->अगरindex = dev->अगरindex;

	rcu_पढ़ो_lock();
	in_dev = __in_dev_get_rcu(dev);
	अगर (in_dev && IN_DEV_IGNORE_ROUTES_WITH_LINKDOWN(in_dev) &&
	    fib_nh->fib_nh_flags & RTNH_F_LINKDOWN) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण
	rcu_पढ़ो_unlock();

	err = mlxsw_sp_nexthop_type_init(mlxsw_sp, nh, dev);
	अगर (err)
		जाओ err_nexthop_neigh_init;

	वापस 0;

err_nexthop_neigh_init:
	mlxsw_sp_nexthop_हटाओ(mlxsw_sp, nh);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_nexthop4_fini(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_nexthop *nh)
अणु
	mlxsw_sp_nexthop_type_fini(mlxsw_sp, nh);
	list_del(&nh->router_list_node);
	mlxsw_sp_nexthop_counter_मुक्त(mlxsw_sp, nh);
	mlxsw_sp_nexthop_हटाओ(mlxsw_sp, nh);
पूर्ण

अटल व्योम mlxsw_sp_nexthop4_event(काष्ठा mlxsw_sp *mlxsw_sp,
				    अचिन्हित दीर्घ event, काष्ठा fib_nh *fib_nh)
अणु
	काष्ठा mlxsw_sp_nexthop_key key;
	काष्ठा mlxsw_sp_nexthop *nh;

	अगर (mlxsw_sp->router->पातed)
		वापस;

	key.fib_nh = fib_nh;
	nh = mlxsw_sp_nexthop_lookup(mlxsw_sp, key);
	अगर (!nh)
		वापस;

	चयन (event) अणु
	हाल FIB_EVENT_NH_ADD:
		mlxsw_sp_nexthop_type_init(mlxsw_sp, nh, fib_nh->fib_nh_dev);
		अवरोध;
	हाल FIB_EVENT_NH_DEL:
		mlxsw_sp_nexthop_type_fini(mlxsw_sp, nh);
		अवरोध;
	पूर्ण

	mlxsw_sp_nexthop_group_refresh(mlxsw_sp, nh->nhgi->nh_grp);
पूर्ण

अटल व्योम mlxsw_sp_nexthop_rअगर_update(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा mlxsw_sp_nexthop *nh;
	bool removing;

	list_क्रम_each_entry(nh, &rअगर->nexthop_list, rअगर_list_node) अणु
		चयन (nh->type) अणु
		हाल MLXSW_SP_NEXTHOP_TYPE_ETH:
			removing = false;
			अवरोध;
		हाल MLXSW_SP_NEXTHOP_TYPE_IPIP:
			removing = !mlxsw_sp_ipip_netdev_ul_up(rअगर->dev);
			अवरोध;
		शेष:
			WARN_ON(1);
			जारी;
		पूर्ण

		__mlxsw_sp_nexthop_neigh_update(nh, removing);
		mlxsw_sp_nexthop_group_refresh(mlxsw_sp, nh->nhgi->nh_grp);
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp_nexthop_rअगर_migrate(काष्ठा mlxsw_sp *mlxsw_sp,
					 काष्ठा mlxsw_sp_rअगर *old_rअगर,
					 काष्ठा mlxsw_sp_rअगर *new_rअगर)
अणु
	काष्ठा mlxsw_sp_nexthop *nh;

	list_splice_init(&old_rअगर->nexthop_list, &new_rअगर->nexthop_list);
	list_क्रम_each_entry(nh, &new_rअगर->nexthop_list, rअगर_list_node)
		nh->rअगर = new_rअगर;
	mlxsw_sp_nexthop_rअगर_update(mlxsw_sp, new_rअगर);
पूर्ण

अटल व्योम mlxsw_sp_nexthop_rअगर_gone_sync(काष्ठा mlxsw_sp *mlxsw_sp,
					   काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा mlxsw_sp_nexthop *nh, *पंचांगp;

	list_क्रम_each_entry_safe(nh, पंचांगp, &rअगर->nexthop_list, rअगर_list_node) अणु
		mlxsw_sp_nexthop_type_fini(mlxsw_sp, nh);
		mlxsw_sp_nexthop_group_refresh(mlxsw_sp, nh->nhgi->nh_grp);
	पूर्ण
पूर्ण

अटल व्योम
mlxsw_sp_nh_grp_activity_get(काष्ठा mlxsw_sp *mlxsw_sp,
			     स्थिर काष्ठा mlxsw_sp_nexthop_group *nh_grp,
			     अचिन्हित दीर्घ *activity)
अणु
	अक्षर *ratrad_pl;
	पूर्णांक i, err;

	ratrad_pl = kदो_स्मृति(MLXSW_REG_RATRAD_LEN, GFP_KERNEL);
	अगर (!ratrad_pl)
		वापस;

	mlxsw_reg_ratrad_pack(ratrad_pl, nh_grp->nhgi->adj_index,
			      nh_grp->nhgi->count);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ratrad), ratrad_pl);
	अगर (err)
		जाओ out;

	क्रम (i = 0; i < nh_grp->nhgi->count; i++) अणु
		अगर (!mlxsw_reg_ratrad_activity_vector_get(ratrad_pl, i))
			जारी;
		biपंचांगap_set(activity, i, 1);
	पूर्ण

out:
	kमुक्त(ratrad_pl);
पूर्ण

#घोषणा MLXSW_SP_NH_GRP_ACTIVITY_UPDATE_INTERVAL 1000 /* ms */

अटल व्योम
mlxsw_sp_nh_grp_activity_update(काष्ठा mlxsw_sp *mlxsw_sp,
				स्थिर काष्ठा mlxsw_sp_nexthop_group *nh_grp)
अणु
	अचिन्हित दीर्घ *activity;

	activity = biपंचांगap_zalloc(nh_grp->nhgi->count, GFP_KERNEL);
	अगर (!activity)
		वापस;

	mlxsw_sp_nh_grp_activity_get(mlxsw_sp, nh_grp, activity);
	nexthop_res_grp_activity_update(mlxsw_sp_net(mlxsw_sp), nh_grp->obj.id,
					nh_grp->nhgi->count, activity);

	biपंचांगap_मुक्त(activity);
पूर्ण

अटल व्योम
mlxsw_sp_nh_grp_activity_work_schedule(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अचिन्हित पूर्णांक पूर्णांकerval = MLXSW_SP_NH_GRP_ACTIVITY_UPDATE_INTERVAL;

	mlxsw_core_schedule_dw(&mlxsw_sp->router->nh_grp_activity_dw,
			       msecs_to_jअगरfies(पूर्णांकerval));
पूर्ण

अटल व्योम mlxsw_sp_nh_grp_activity_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_sp_nexthop_group_info *nhgi;
	काष्ठा mlxsw_sp_router *router;
	bool reschedule = false;

	router = container_of(work, काष्ठा mlxsw_sp_router,
			      nh_grp_activity_dw.work);

	mutex_lock(&router->lock);

	list_क्रम_each_entry(nhgi, &router->nh_res_grp_list, list) अणु
		mlxsw_sp_nh_grp_activity_update(router->mlxsw_sp, nhgi->nh_grp);
		reschedule = true;
	पूर्ण

	mutex_unlock(&router->lock);

	अगर (!reschedule)
		वापस;
	mlxsw_sp_nh_grp_activity_work_schedule(router->mlxsw_sp);
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop_obj_single_validate(काष्ठा mlxsw_sp *mlxsw_sp,
				     स्थिर काष्ठा nh_notअगरier_single_info *nh,
				     काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err = -EINVAL;

	अगर (nh->is_fdb)
		NL_SET_ERR_MSG_MOD(extack, "FDB nexthops are not supported");
	अन्यथा अगर (nh->has_encap)
		NL_SET_ERR_MSG_MOD(extack, "Encapsulating nexthops are not supported");
	अन्यथा
		err = 0;

	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop_obj_group_entry_validate(काष्ठा mlxsw_sp *mlxsw_sp,
					  स्थिर काष्ठा nh_notअगरier_single_info *nh,
					  काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	err = mlxsw_sp_nexthop_obj_single_validate(mlxsw_sp, nh, extack);
	अगर (err)
		वापस err;

	/* Device only nexthops with an IPIP device are programmed as
	 * encapsulating adjacency entries.
	 */
	अगर (!nh->gw_family && !nh->is_reject &&
	    !mlxsw_sp_netdev_ipip_type(mlxsw_sp, nh->dev, शून्य)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Nexthop group entry does not have a gateway");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop_obj_group_validate(काष्ठा mlxsw_sp *mlxsw_sp,
				    स्थिर काष्ठा nh_notअगरier_grp_info *nh_grp,
				    काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक i;

	अगर (nh_grp->is_fdb) अणु
		NL_SET_ERR_MSG_MOD(extack, "FDB nexthop groups are not supported");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < nh_grp->num_nh; i++) अणु
		स्थिर काष्ठा nh_notअगरier_single_info *nh;
		पूर्णांक err;

		nh = &nh_grp->nh_entries[i].nh;
		err = mlxsw_sp_nexthop_obj_group_entry_validate(mlxsw_sp, nh,
								extack);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop_obj_res_group_size_validate(काष्ठा mlxsw_sp *mlxsw_sp,
					     स्थिर काष्ठा nh_notअगरier_res_table_info *nh_res_table,
					     काष्ठा netlink_ext_ack *extack)
अणु
	अचिन्हित पूर्णांक alloc_size;
	bool valid_size = false;
	पूर्णांक err, i;

	अगर (nh_res_table->num_nh_buckets < 32) अणु
		NL_SET_ERR_MSG_MOD(extack, "Minimum number of buckets is 32");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < mlxsw_sp->router->adj_grp_size_ranges_count; i++) अणु
		स्थिर काष्ठा mlxsw_sp_adj_grp_size_range *size_range;

		size_range = &mlxsw_sp->router->adj_grp_size_ranges[i];

		अगर (nh_res_table->num_nh_buckets >= size_range->start &&
		    nh_res_table->num_nh_buckets <= size_range->end) अणु
			valid_size = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!valid_size) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid number of buckets");
		वापस -EINVAL;
	पूर्ण

	err = mlxsw_sp_kvdl_alloc_count_query(mlxsw_sp,
					      MLXSW_SP_KVDL_ENTRY_TYPE_ADJ,
					      nh_res_table->num_nh_buckets,
					      &alloc_size);
	अगर (err || nh_res_table->num_nh_buckets != alloc_size) अणु
		NL_SET_ERR_MSG_MOD(extack, "Number of buckets does not fit allocation size of any KVDL partition");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop_obj_res_group_validate(काष्ठा mlxsw_sp *mlxsw_sp,
					स्थिर काष्ठा nh_notअगरier_res_table_info *nh_res_table,
					काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;
	u16 i;

	err = mlxsw_sp_nexthop_obj_res_group_size_validate(mlxsw_sp,
							   nh_res_table,
							   extack);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < nh_res_table->num_nh_buckets; i++) अणु
		स्थिर काष्ठा nh_notअगरier_single_info *nh;
		पूर्णांक err;

		nh = &nh_res_table->nhs[i];
		err = mlxsw_sp_nexthop_obj_group_entry_validate(mlxsw_sp, nh,
								extack);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_nexthop_obj_validate(काष्ठा mlxsw_sp *mlxsw_sp,
					 अचिन्हित दीर्घ event,
					 काष्ठा nh_notअगरier_info *info)
अणु
	काष्ठा nh_notअगरier_single_info *nh;

	अगर (event != NEXTHOP_EVENT_REPLACE &&
	    event != NEXTHOP_EVENT_RES_TABLE_PRE_REPLACE &&
	    event != NEXTHOP_EVENT_BUCKET_REPLACE)
		वापस 0;

	चयन (info->type) अणु
	हाल NH_NOTIFIER_INFO_TYPE_SINGLE:
		वापस mlxsw_sp_nexthop_obj_single_validate(mlxsw_sp, info->nh,
							    info->extack);
	हाल NH_NOTIFIER_INFO_TYPE_GRP:
		वापस mlxsw_sp_nexthop_obj_group_validate(mlxsw_sp,
							   info->nh_grp,
							   info->extack);
	हाल NH_NOTIFIER_INFO_TYPE_RES_TABLE:
		वापस mlxsw_sp_nexthop_obj_res_group_validate(mlxsw_sp,
							       info->nh_res_table,
							       info->extack);
	हाल NH_NOTIFIER_INFO_TYPE_RES_BUCKET:
		nh = &info->nh_res_bucket->new_nh;
		वापस mlxsw_sp_nexthop_obj_group_entry_validate(mlxsw_sp, nh,
								 info->extack);
	शेष:
		NL_SET_ERR_MSG_MOD(info->extack, "Unsupported nexthop type");
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल bool mlxsw_sp_nexthop_obj_is_gateway(काष्ठा mlxsw_sp *mlxsw_sp,
					    स्थिर काष्ठा nh_notअगरier_info *info)
अणु
	स्थिर काष्ठा net_device *dev;

	चयन (info->type) अणु
	हाल NH_NOTIFIER_INFO_TYPE_SINGLE:
		dev = info->nh->dev;
		वापस info->nh->gw_family || info->nh->is_reject ||
		       mlxsw_sp_netdev_ipip_type(mlxsw_sp, dev, शून्य);
	हाल NH_NOTIFIER_INFO_TYPE_GRP:
	हाल NH_NOTIFIER_INFO_TYPE_RES_TABLE:
		/* Alपढ़ोy validated earlier. */
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp_nexthop_obj_blackhole_init(काष्ठा mlxsw_sp *mlxsw_sp,
						काष्ठा mlxsw_sp_nexthop *nh)
अणु
	u16 lb_rअगर_index = mlxsw_sp->router->lb_rअगर_index;

	nh->action = MLXSW_SP_NEXTHOP_ACTION_DISCARD;
	nh->should_offload = 1;
	/* While nexthops that discard packets करो not क्रमward packets
	 * via an egress RIF, they still need to be programmed using a
	 * valid RIF, so use the loopback RIF created during init.
	 */
	nh->rअगर = mlxsw_sp->router->rअगरs[lb_rअगर_index];
पूर्ण

अटल व्योम mlxsw_sp_nexthop_obj_blackhole_fini(काष्ठा mlxsw_sp *mlxsw_sp,
						काष्ठा mlxsw_sp_nexthop *nh)
अणु
	nh->rअगर = शून्य;
	nh->should_offload = 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop_obj_init(काष्ठा mlxsw_sp *mlxsw_sp,
			  काष्ठा mlxsw_sp_nexthop_group *nh_grp,
			  काष्ठा mlxsw_sp_nexthop *nh,
			  काष्ठा nh_notअगरier_single_info *nh_obj, पूर्णांक weight)
अणु
	काष्ठा net_device *dev = nh_obj->dev;
	पूर्णांक err;

	nh->nhgi = nh_grp->nhgi;
	nh->nh_weight = weight;

	चयन (nh_obj->gw_family) अणु
	हाल AF_INET:
		स_नकल(&nh->gw_addr, &nh_obj->ipv4, माप(nh_obj->ipv4));
		nh->neigh_tbl = &arp_tbl;
		अवरोध;
	हाल AF_INET6:
		स_नकल(&nh->gw_addr, &nh_obj->ipv6, माप(nh_obj->ipv6));
#अगर IS_ENABLED(CONFIG_IPV6)
		nh->neigh_tbl = &nd_tbl;
#पूर्ण_अगर
		अवरोध;
	पूर्ण

	mlxsw_sp_nexthop_counter_alloc(mlxsw_sp, nh);
	list_add_tail(&nh->router_list_node, &mlxsw_sp->router->nexthop_list);
	nh->अगरindex = dev->अगरindex;

	err = mlxsw_sp_nexthop_type_init(mlxsw_sp, nh, dev);
	अगर (err)
		जाओ err_type_init;

	अगर (nh_obj->is_reject)
		mlxsw_sp_nexthop_obj_blackhole_init(mlxsw_sp, nh);

	/* In a resilient nexthop group, all the nexthops must be written to
	 * the adjacency table. Even अगर they करो not have a valid neighbour or
	 * RIF.
	 */
	अगर (nh_grp->nhgi->is_resilient && !nh->should_offload) अणु
		nh->action = MLXSW_SP_NEXTHOP_ACTION_TRAP;
		nh->should_offload = 1;
	पूर्ण

	वापस 0;

err_type_init:
	list_del(&nh->router_list_node);
	mlxsw_sp_nexthop_counter_मुक्त(mlxsw_sp, nh);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_nexthop_obj_fini(काष्ठा mlxsw_sp *mlxsw_sp,
				      काष्ठा mlxsw_sp_nexthop *nh)
अणु
	अगर (nh->action == MLXSW_SP_NEXTHOP_ACTION_DISCARD)
		mlxsw_sp_nexthop_obj_blackhole_fini(mlxsw_sp, nh);
	mlxsw_sp_nexthop_type_fini(mlxsw_sp, nh);
	list_del(&nh->router_list_node);
	mlxsw_sp_nexthop_counter_मुक्त(mlxsw_sp, nh);
	nh->should_offload = 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop_obj_group_info_init(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_nexthop_group *nh_grp,
				     काष्ठा nh_notअगरier_info *info)
अणु
	काष्ठा mlxsw_sp_nexthop_group_info *nhgi;
	काष्ठा mlxsw_sp_nexthop *nh;
	bool is_resilient = false;
	अचिन्हित पूर्णांक nhs;
	पूर्णांक err, i;

	चयन (info->type) अणु
	हाल NH_NOTIFIER_INFO_TYPE_SINGLE:
		nhs = 1;
		अवरोध;
	हाल NH_NOTIFIER_INFO_TYPE_GRP:
		nhs = info->nh_grp->num_nh;
		अवरोध;
	हाल NH_NOTIFIER_INFO_TYPE_RES_TABLE:
		nhs = info->nh_res_table->num_nh_buckets;
		is_resilient = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	nhgi = kzalloc(काष्ठा_size(nhgi, nexthops, nhs), GFP_KERNEL);
	अगर (!nhgi)
		वापस -ENOMEM;
	nh_grp->nhgi = nhgi;
	nhgi->nh_grp = nh_grp;
	nhgi->gateway = mlxsw_sp_nexthop_obj_is_gateway(mlxsw_sp, info);
	nhgi->is_resilient = is_resilient;
	nhgi->count = nhs;
	क्रम (i = 0; i < nhgi->count; i++) अणु
		काष्ठा nh_notअगरier_single_info *nh_obj;
		पूर्णांक weight;

		nh = &nhgi->nexthops[i];
		चयन (info->type) अणु
		हाल NH_NOTIFIER_INFO_TYPE_SINGLE:
			nh_obj = info->nh;
			weight = 1;
			अवरोध;
		हाल NH_NOTIFIER_INFO_TYPE_GRP:
			nh_obj = &info->nh_grp->nh_entries[i].nh;
			weight = info->nh_grp->nh_entries[i].weight;
			अवरोध;
		हाल NH_NOTIFIER_INFO_TYPE_RES_TABLE:
			nh_obj = &info->nh_res_table->nhs[i];
			weight = 1;
			अवरोध;
		शेष:
			err = -EINVAL;
			जाओ err_nexthop_obj_init;
		पूर्ण
		err = mlxsw_sp_nexthop_obj_init(mlxsw_sp, nh_grp, nh, nh_obj,
						weight);
		अगर (err)
			जाओ err_nexthop_obj_init;
	पूर्ण
	err = mlxsw_sp_nexthop_group_refresh(mlxsw_sp, nh_grp);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(info->extack, "Failed to write adjacency entries to the device");
		जाओ err_group_refresh;
	पूर्ण

	/* Add resilient nexthop groups to a list so that the activity of their
	 * nexthop buckets will be periodically queried and cleared.
	 */
	अगर (nhgi->is_resilient) अणु
		अगर (list_empty(&mlxsw_sp->router->nh_res_grp_list))
			mlxsw_sp_nh_grp_activity_work_schedule(mlxsw_sp);
		list_add(&nhgi->list, &mlxsw_sp->router->nh_res_grp_list);
	पूर्ण

	वापस 0;

err_group_refresh:
	i = nhgi->count;
err_nexthop_obj_init:
	क्रम (i--; i >= 0; i--) अणु
		nh = &nhgi->nexthops[i];
		mlxsw_sp_nexthop_obj_fini(mlxsw_sp, nh);
	पूर्ण
	kमुक्त(nhgi);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_nexthop_obj_group_info_fini(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_nexthop_group *nh_grp)
अणु
	काष्ठा mlxsw_sp_nexthop_group_info *nhgi = nh_grp->nhgi;
	काष्ठा mlxsw_sp_router *router = mlxsw_sp->router;
	पूर्णांक i;

	अगर (nhgi->is_resilient) अणु
		list_del(&nhgi->list);
		अगर (list_empty(&mlxsw_sp->router->nh_res_grp_list))
			cancel_delayed_work(&router->nh_grp_activity_dw);
	पूर्ण

	क्रम (i = nhgi->count - 1; i >= 0; i--) अणु
		काष्ठा mlxsw_sp_nexthop *nh = &nhgi->nexthops[i];

		mlxsw_sp_nexthop_obj_fini(mlxsw_sp, nh);
	पूर्ण
	mlxsw_sp_nexthop_group_refresh(mlxsw_sp, nh_grp);
	WARN_ON_ONCE(nhgi->adj_index_valid);
	kमुक्त(nhgi);
पूर्ण

अटल काष्ठा mlxsw_sp_nexthop_group *
mlxsw_sp_nexthop_obj_group_create(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा nh_notअगरier_info *info)
अणु
	काष्ठा mlxsw_sp_nexthop_group *nh_grp;
	पूर्णांक err;

	nh_grp = kzalloc(माप(*nh_grp), GFP_KERNEL);
	अगर (!nh_grp)
		वापस ERR_PTR(-ENOMEM);
	INIT_LIST_HEAD(&nh_grp->vr_list);
	err = rhashtable_init(&nh_grp->vr_ht,
			      &mlxsw_sp_nexthop_group_vr_ht_params);
	अगर (err)
		जाओ err_nexthop_group_vr_ht_init;
	INIT_LIST_HEAD(&nh_grp->fib_list);
	nh_grp->type = MLXSW_SP_NEXTHOP_GROUP_TYPE_OBJ;
	nh_grp->obj.id = info->id;

	err = mlxsw_sp_nexthop_obj_group_info_init(mlxsw_sp, nh_grp, info);
	अगर (err)
		जाओ err_nexthop_group_info_init;

	nh_grp->can_destroy = false;

	वापस nh_grp;

err_nexthop_group_info_init:
	rhashtable_destroy(&nh_grp->vr_ht);
err_nexthop_group_vr_ht_init:
	kमुक्त(nh_grp);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_nexthop_obj_group_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_nexthop_group *nh_grp)
अणु
	अगर (!nh_grp->can_destroy)
		वापस;
	mlxsw_sp_nexthop_obj_group_info_fini(mlxsw_sp, nh_grp);
	WARN_ON_ONCE(!list_empty(&nh_grp->fib_list));
	WARN_ON_ONCE(!list_empty(&nh_grp->vr_list));
	rhashtable_destroy(&nh_grp->vr_ht);
	kमुक्त(nh_grp);
पूर्ण

अटल काष्ठा mlxsw_sp_nexthop_group *
mlxsw_sp_nexthop_obj_group_lookup(काष्ठा mlxsw_sp *mlxsw_sp, u32 id)
अणु
	काष्ठा mlxsw_sp_nexthop_group_cmp_arg cmp_arg;

	cmp_arg.type = MLXSW_SP_NEXTHOP_GROUP_TYPE_OBJ;
	cmp_arg.id = id;
	वापस rhashtable_lookup_fast(&mlxsw_sp->router->nexthop_group_ht,
				      &cmp_arg,
				      mlxsw_sp_nexthop_group_ht_params);
पूर्ण

अटल पूर्णांक mlxsw_sp_nexthop_obj_group_add(काष्ठा mlxsw_sp *mlxsw_sp,
					  काष्ठा mlxsw_sp_nexthop_group *nh_grp)
अणु
	वापस mlxsw_sp_nexthop_group_insert(mlxsw_sp, nh_grp);
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop_obj_group_replace(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_nexthop_group *nh_grp,
				   काष्ठा mlxsw_sp_nexthop_group *old_nh_grp,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_nexthop_group_info *old_nhgi = old_nh_grp->nhgi;
	काष्ठा mlxsw_sp_nexthop_group_info *new_nhgi = nh_grp->nhgi;
	पूर्णांक err;

	old_nh_grp->nhgi = new_nhgi;
	new_nhgi->nh_grp = old_nh_grp;
	nh_grp->nhgi = old_nhgi;
	old_nhgi->nh_grp = nh_grp;

	अगर (old_nhgi->adj_index_valid && new_nhgi->adj_index_valid) अणु
		/* Both the old adjacency index and the new one are valid.
		 * Routes are currently using the old one. Tell the device to
		 * replace the old adjacency index with the new one.
		 */
		err = mlxsw_sp_adj_index_mass_update(mlxsw_sp, old_nh_grp,
						     old_nhgi->adj_index,
						     old_nhgi->ecmp_size);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack, "Failed to replace old adjacency index with new one");
			जाओ err_out;
		पूर्ण
	पूर्ण अन्यथा अगर (old_nhgi->adj_index_valid && !new_nhgi->adj_index_valid) अणु
		/* The old adjacency index is valid, जबतक the new one is not.
		 * Iterate over all the routes using the group and change them
		 * to trap packets to the CPU.
		 */
		err = mlxsw_sp_nexthop_fib_entries_update(mlxsw_sp, old_nh_grp);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack, "Failed to update routes to trap packets");
			जाओ err_out;
		पूर्ण
	पूर्ण अन्यथा अगर (!old_nhgi->adj_index_valid && new_nhgi->adj_index_valid) अणु
		/* The old adjacency index is invalid, जबतक the new one is.
		 * Iterate over all the routes using the group and change them
		 * to क्रमward packets using the new valid index.
		 */
		err = mlxsw_sp_nexthop_fib_entries_update(mlxsw_sp, old_nh_grp);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack, "Failed to update routes to forward packets");
			जाओ err_out;
		पूर्ण
	पूर्ण

	/* Make sure the flags are set / cleared based on the new nexthop group
	 * inक्रमmation.
	 */
	mlxsw_sp_nexthop_obj_group_offload_refresh(mlxsw_sp, old_nh_grp);

	/* At this poपूर्णांक 'nh_grp' is just a shell that is not used by anyone
	 * and its nexthop group info is the old info that was just replaced
	 * with the new one. Remove it.
	 */
	nh_grp->can_destroy = true;
	mlxsw_sp_nexthop_obj_group_destroy(mlxsw_sp, nh_grp);

	वापस 0;

err_out:
	old_nhgi->nh_grp = old_nh_grp;
	nh_grp->nhgi = new_nhgi;
	new_nhgi->nh_grp = nh_grp;
	old_nh_grp->nhgi = old_nhgi;
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_nexthop_obj_new(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा nh_notअगरier_info *info)
अणु
	काष्ठा mlxsw_sp_nexthop_group *nh_grp, *old_nh_grp;
	काष्ठा netlink_ext_ack *extack = info->extack;
	पूर्णांक err;

	nh_grp = mlxsw_sp_nexthop_obj_group_create(mlxsw_sp, info);
	अगर (IS_ERR(nh_grp))
		वापस PTR_ERR(nh_grp);

	old_nh_grp = mlxsw_sp_nexthop_obj_group_lookup(mlxsw_sp, info->id);
	अगर (!old_nh_grp)
		err = mlxsw_sp_nexthop_obj_group_add(mlxsw_sp, nh_grp);
	अन्यथा
		err = mlxsw_sp_nexthop_obj_group_replace(mlxsw_sp, nh_grp,
							 old_nh_grp, extack);

	अगर (err) अणु
		nh_grp->can_destroy = true;
		mlxsw_sp_nexthop_obj_group_destroy(mlxsw_sp, nh_grp);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_nexthop_obj_del(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा nh_notअगरier_info *info)
अणु
	काष्ठा mlxsw_sp_nexthop_group *nh_grp;

	nh_grp = mlxsw_sp_nexthop_obj_group_lookup(mlxsw_sp, info->id);
	अगर (!nh_grp)
		वापस;

	nh_grp->can_destroy = true;
	mlxsw_sp_nexthop_group_हटाओ(mlxsw_sp, nh_grp);

	/* If the group still has routes using it, then defer the delete
	 * operation until the last route using it is deleted.
	 */
	अगर (!list_empty(&nh_grp->fib_list))
		वापस;
	mlxsw_sp_nexthop_obj_group_destroy(mlxsw_sp, nh_grp);
पूर्ण

अटल पूर्णांक mlxsw_sp_nexthop_obj_bucket_query(काष्ठा mlxsw_sp *mlxsw_sp,
					     u32 adj_index, अक्षर *ratr_pl)
अणु
	MLXSW_REG_ZERO(ratr, ratr_pl);
	mlxsw_reg_ratr_op_set(ratr_pl, MLXSW_REG_RATR_OP_QUERY_READ);
	mlxsw_reg_ratr_adjacency_index_low_set(ratr_pl, adj_index);
	mlxsw_reg_ratr_adjacency_index_high_set(ratr_pl, adj_index >> 16);

	वापस mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ratr), ratr_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_nexthop_obj_bucket_compare(अक्षर *ratr_pl, अक्षर *ratr_pl_new)
अणु
	/* Clear the opcode and activity on both the old and new payload as
	 * they are irrelevant क्रम the comparison.
	 */
	mlxsw_reg_ratr_op_set(ratr_pl, MLXSW_REG_RATR_OP_QUERY_READ);
	mlxsw_reg_ratr_a_set(ratr_pl, 0);
	mlxsw_reg_ratr_op_set(ratr_pl_new, MLXSW_REG_RATR_OP_QUERY_READ);
	mlxsw_reg_ratr_a_set(ratr_pl_new, 0);

	/* If the contents of the adjacency entry are consistent with the
	 * replacement request, then replacement was successful.
	 */
	अगर (!स_भेद(ratr_pl, ratr_pl_new, MLXSW_REG_RATR_LEN))
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop_obj_bucket_adj_update(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_nexthop *nh,
				       काष्ठा nh_notअगरier_info *info)
अणु
	u16 bucket_index = info->nh_res_bucket->bucket_index;
	काष्ठा netlink_ext_ack *extack = info->extack;
	bool क्रमce = info->nh_res_bucket->क्रमce;
	अक्षर ratr_pl_new[MLXSW_REG_RATR_LEN];
	अक्षर ratr_pl[MLXSW_REG_RATR_LEN];
	u32 adj_index;
	पूर्णांक err;

	/* No poपूर्णांक in trying an atomic replacement अगर the idle समयr पूर्णांकerval
	 * is smaller than the पूर्णांकerval in which we query and clear activity.
	 */
	अगर (!क्रमce && info->nh_res_bucket->idle_समयr_ms <
	    MLXSW_SP_NH_GRP_ACTIVITY_UPDATE_INTERVAL)
		क्रमce = true;

	adj_index = nh->nhgi->adj_index + bucket_index;
	err = mlxsw_sp_nexthop_update(mlxsw_sp, adj_index, nh, क्रमce, ratr_pl);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to overwrite nexthop bucket");
		वापस err;
	पूर्ण

	अगर (!क्रमce) अणु
		err = mlxsw_sp_nexthop_obj_bucket_query(mlxsw_sp, adj_index,
							ratr_pl_new);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack, "Failed to query nexthop bucket state after replacement. State might be inconsistent");
			वापस err;
		पूर्ण

		err = mlxsw_sp_nexthop_obj_bucket_compare(ratr_pl, ratr_pl_new);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack, "Nexthop bucket was not replaced because it was active during replacement");
			वापस err;
		पूर्ण
	पूर्ण

	nh->update = 0;
	nh->offloaded = 1;
	mlxsw_sp_nexthop_bucket_offload_refresh(mlxsw_sp, nh, bucket_index);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_nexthop_obj_bucket_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					       काष्ठा nh_notअगरier_info *info)
अणु
	u16 bucket_index = info->nh_res_bucket->bucket_index;
	काष्ठा netlink_ext_ack *extack = info->extack;
	काष्ठा mlxsw_sp_nexthop_group_info *nhgi;
	काष्ठा nh_notअगरier_single_info *nh_obj;
	काष्ठा mlxsw_sp_nexthop_group *nh_grp;
	काष्ठा mlxsw_sp_nexthop *nh;
	पूर्णांक err;

	nh_grp = mlxsw_sp_nexthop_obj_group_lookup(mlxsw_sp, info->id);
	अगर (!nh_grp) अणु
		NL_SET_ERR_MSG_MOD(extack, "Nexthop group was not found");
		वापस -EINVAL;
	पूर्ण

	nhgi = nh_grp->nhgi;

	अगर (bucket_index >= nhgi->count) अणु
		NL_SET_ERR_MSG_MOD(extack, "Nexthop bucket index out of range");
		वापस -EINVAL;
	पूर्ण

	nh = &nhgi->nexthops[bucket_index];
	mlxsw_sp_nexthop_obj_fini(mlxsw_sp, nh);

	nh_obj = &info->nh_res_bucket->new_nh;
	err = mlxsw_sp_nexthop_obj_init(mlxsw_sp, nh_grp, nh, nh_obj, 1);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to initialize nexthop object for nexthop bucket replacement");
		जाओ err_nexthop_obj_init;
	पूर्ण

	err = mlxsw_sp_nexthop_obj_bucket_adj_update(mlxsw_sp, nh, info);
	अगर (err)
		जाओ err_nexthop_obj_bucket_adj_update;

	वापस 0;

err_nexthop_obj_bucket_adj_update:
	mlxsw_sp_nexthop_obj_fini(mlxsw_sp, nh);
err_nexthop_obj_init:
	nh_obj = &info->nh_res_bucket->old_nh;
	mlxsw_sp_nexthop_obj_init(mlxsw_sp, nh_grp, nh, nh_obj, 1);
	/* The old adjacency entry was not overwritten */
	nh->update = 0;
	nh->offloaded = 1;
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_nexthop_obj_event(काष्ठा notअगरier_block *nb,
				      अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा nh_notअगरier_info *info = ptr;
	काष्ठा mlxsw_sp_router *router;
	पूर्णांक err = 0;

	router = container_of(nb, काष्ठा mlxsw_sp_router, nexthop_nb);
	err = mlxsw_sp_nexthop_obj_validate(router->mlxsw_sp, event, info);
	अगर (err)
		जाओ out;

	mutex_lock(&router->lock);

	चयन (event) अणु
	हाल NEXTHOP_EVENT_REPLACE:
		err = mlxsw_sp_nexthop_obj_new(router->mlxsw_sp, info);
		अवरोध;
	हाल NEXTHOP_EVENT_DEL:
		mlxsw_sp_nexthop_obj_del(router->mlxsw_sp, info);
		अवरोध;
	हाल NEXTHOP_EVENT_BUCKET_REPLACE:
		err = mlxsw_sp_nexthop_obj_bucket_replace(router->mlxsw_sp,
							  info);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	mutex_unlock(&router->lock);

out:
	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

अटल bool mlxsw_sp_fi_is_gateway(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा fib_info *fi)
अणु
	स्थिर काष्ठा fib_nh *nh = fib_info_nh(fi, 0);

	वापस nh->fib_nh_scope == RT_SCOPE_LINK ||
	       mlxsw_sp_nexthop4_ipip_type(mlxsw_sp, nh, शून्य);
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop4_group_info_init(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_nexthop_group *nh_grp)
अणु
	अचिन्हित पूर्णांक nhs = fib_info_num_path(nh_grp->ipv4.fi);
	काष्ठा mlxsw_sp_nexthop_group_info *nhgi;
	काष्ठा mlxsw_sp_nexthop *nh;
	पूर्णांक err, i;

	nhgi = kzalloc(काष्ठा_size(nhgi, nexthops, nhs), GFP_KERNEL);
	अगर (!nhgi)
		वापस -ENOMEM;
	nh_grp->nhgi = nhgi;
	nhgi->nh_grp = nh_grp;
	nhgi->gateway = mlxsw_sp_fi_is_gateway(mlxsw_sp, nh_grp->ipv4.fi);
	nhgi->count = nhs;
	क्रम (i = 0; i < nhgi->count; i++) अणु
		काष्ठा fib_nh *fib_nh;

		nh = &nhgi->nexthops[i];
		fib_nh = fib_info_nh(nh_grp->ipv4.fi, i);
		err = mlxsw_sp_nexthop4_init(mlxsw_sp, nh_grp, nh, fib_nh);
		अगर (err)
			जाओ err_nexthop4_init;
	पूर्ण
	err = mlxsw_sp_nexthop_group_refresh(mlxsw_sp, nh_grp);
	अगर (err)
		जाओ err_group_refresh;

	वापस 0;

err_group_refresh:
	i = nhgi->count;
err_nexthop4_init:
	क्रम (i--; i >= 0; i--) अणु
		nh = &nhgi->nexthops[i];
		mlxsw_sp_nexthop4_fini(mlxsw_sp, nh);
	पूर्ण
	kमुक्त(nhgi);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_nexthop4_group_info_fini(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_nexthop_group *nh_grp)
अणु
	काष्ठा mlxsw_sp_nexthop_group_info *nhgi = nh_grp->nhgi;
	पूर्णांक i;

	क्रम (i = nhgi->count - 1; i >= 0; i--) अणु
		काष्ठा mlxsw_sp_nexthop *nh = &nhgi->nexthops[i];

		mlxsw_sp_nexthop4_fini(mlxsw_sp, nh);
	पूर्ण
	mlxsw_sp_nexthop_group_refresh(mlxsw_sp, nh_grp);
	WARN_ON_ONCE(nhgi->adj_index_valid);
	kमुक्त(nhgi);
पूर्ण

अटल काष्ठा mlxsw_sp_nexthop_group *
mlxsw_sp_nexthop4_group_create(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा fib_info *fi)
अणु
	काष्ठा mlxsw_sp_nexthop_group *nh_grp;
	पूर्णांक err;

	nh_grp = kzalloc(माप(*nh_grp), GFP_KERNEL);
	अगर (!nh_grp)
		वापस ERR_PTR(-ENOMEM);
	INIT_LIST_HEAD(&nh_grp->vr_list);
	err = rhashtable_init(&nh_grp->vr_ht,
			      &mlxsw_sp_nexthop_group_vr_ht_params);
	अगर (err)
		जाओ err_nexthop_group_vr_ht_init;
	INIT_LIST_HEAD(&nh_grp->fib_list);
	nh_grp->type = MLXSW_SP_NEXTHOP_GROUP_TYPE_IPV4;
	nh_grp->ipv4.fi = fi;
	fib_info_hold(fi);

	err = mlxsw_sp_nexthop4_group_info_init(mlxsw_sp, nh_grp);
	अगर (err)
		जाओ err_nexthop_group_info_init;

	err = mlxsw_sp_nexthop_group_insert(mlxsw_sp, nh_grp);
	अगर (err)
		जाओ err_nexthop_group_insert;

	nh_grp->can_destroy = true;

	वापस nh_grp;

err_nexthop_group_insert:
	mlxsw_sp_nexthop4_group_info_fini(mlxsw_sp, nh_grp);
err_nexthop_group_info_init:
	fib_info_put(fi);
	rhashtable_destroy(&nh_grp->vr_ht);
err_nexthop_group_vr_ht_init:
	kमुक्त(nh_grp);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_nexthop4_group_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_nexthop_group *nh_grp)
अणु
	अगर (!nh_grp->can_destroy)
		वापस;
	mlxsw_sp_nexthop_group_हटाओ(mlxsw_sp, nh_grp);
	mlxsw_sp_nexthop4_group_info_fini(mlxsw_sp, nh_grp);
	fib_info_put(nh_grp->ipv4.fi);
	WARN_ON_ONCE(!list_empty(&nh_grp->vr_list));
	rhashtable_destroy(&nh_grp->vr_ht);
	kमुक्त(nh_grp);
पूर्ण

अटल पूर्णांक mlxsw_sp_nexthop4_group_get(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_fib_entry *fib_entry,
				       काष्ठा fib_info *fi)
अणु
	काष्ठा mlxsw_sp_nexthop_group *nh_grp;

	अगर (fi->nh) अणु
		nh_grp = mlxsw_sp_nexthop_obj_group_lookup(mlxsw_sp,
							   fi->nh->id);
		अगर (WARN_ON_ONCE(!nh_grp))
			वापस -EINVAL;
		जाओ out;
	पूर्ण

	nh_grp = mlxsw_sp_nexthop4_group_lookup(mlxsw_sp, fi);
	अगर (!nh_grp) अणु
		nh_grp = mlxsw_sp_nexthop4_group_create(mlxsw_sp, fi);
		अगर (IS_ERR(nh_grp))
			वापस PTR_ERR(nh_grp);
	पूर्ण
out:
	list_add_tail(&fib_entry->nexthop_group_node, &nh_grp->fib_list);
	fib_entry->nh_group = nh_grp;
	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_nexthop4_group_put(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	काष्ठा mlxsw_sp_nexthop_group *nh_grp = fib_entry->nh_group;

	list_del(&fib_entry->nexthop_group_node);
	अगर (!list_empty(&nh_grp->fib_list))
		वापस;

	अगर (nh_grp->type == MLXSW_SP_NEXTHOP_GROUP_TYPE_OBJ) अणु
		mlxsw_sp_nexthop_obj_group_destroy(mlxsw_sp, nh_grp);
		वापस;
	पूर्ण

	mlxsw_sp_nexthop4_group_destroy(mlxsw_sp, nh_grp);
पूर्ण

अटल bool
mlxsw_sp_fib4_entry_should_offload(स्थिर काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	काष्ठा mlxsw_sp_fib4_entry *fib4_entry;

	fib4_entry = container_of(fib_entry, काष्ठा mlxsw_sp_fib4_entry,
				  common);
	वापस !fib4_entry->tos;
पूर्ण

अटल bool
mlxsw_sp_fib_entry_should_offload(स्थिर काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	काष्ठा mlxsw_sp_nexthop_group *nh_group = fib_entry->nh_group;

	चयन (fib_entry->fib_node->fib->proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		अगर (!mlxsw_sp_fib4_entry_should_offload(fib_entry))
			वापस false;
		अवरोध;
	हाल MLXSW_SP_L3_PROTO_IPV6:
		अवरोध;
	पूर्ण

	चयन (fib_entry->type) अणु
	हाल MLXSW_SP_FIB_ENTRY_TYPE_REMOTE:
		वापस !!nh_group->nhgi->adj_index_valid;
	हाल MLXSW_SP_FIB_ENTRY_TYPE_LOCAL:
		वापस !!nh_group->nhgi->nh_rअगर;
	हाल MLXSW_SP_FIB_ENTRY_TYPE_BLACKHOLE:
	हाल MLXSW_SP_FIB_ENTRY_TYPE_IPIP_DECAP:
	हाल MLXSW_SP_FIB_ENTRY_TYPE_NVE_DECAP:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल काष्ठा mlxsw_sp_nexthop *
mlxsw_sp_rt6_nexthop(काष्ठा mlxsw_sp_nexthop_group *nh_grp,
		     स्थिर काष्ठा mlxsw_sp_rt6 *mlxsw_sp_rt6)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nh_grp->nhgi->count; i++) अणु
		काष्ठा mlxsw_sp_nexthop *nh = &nh_grp->nhgi->nexthops[i];
		काष्ठा fib6_info *rt = mlxsw_sp_rt6->rt;

		अगर (nh->rअगर && nh->rअगर->dev == rt->fib6_nh->fib_nh_dev &&
		    ipv6_addr_equal((स्थिर काष्ठा in6_addr *) &nh->gw_addr,
				    &rt->fib6_nh->fib_nh_gw6))
			वापस nh;
		जारी;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम
mlxsw_sp_fib4_offload_failed_flag_set(काष्ठा mlxsw_sp *mlxsw_sp,
				      काष्ठा fib_entry_notअगरier_info *fen_info)
अणु
	u32 *p_dst = (u32 *) &fen_info->dst;
	काष्ठा fib_rt_info fri;

	fri.fi = fen_info->fi;
	fri.tb_id = fen_info->tb_id;
	fri.dst = cpu_to_be32(*p_dst);
	fri.dst_len = fen_info->dst_len;
	fri.tos = fen_info->tos;
	fri.type = fen_info->type;
	fri.offload = false;
	fri.trap = false;
	fri.offload_failed = true;
	fib_alias_hw_flags_set(mlxsw_sp_net(mlxsw_sp), &fri);
पूर्ण

अटल व्योम
mlxsw_sp_fib4_entry_hw_flags_set(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	u32 *p_dst = (u32 *) fib_entry->fib_node->key.addr;
	पूर्णांक dst_len = fib_entry->fib_node->key.prefix_len;
	काष्ठा mlxsw_sp_fib4_entry *fib4_entry;
	काष्ठा fib_rt_info fri;
	bool should_offload;

	should_offload = mlxsw_sp_fib_entry_should_offload(fib_entry);
	fib4_entry = container_of(fib_entry, काष्ठा mlxsw_sp_fib4_entry,
				  common);
	fri.fi = fib4_entry->fi;
	fri.tb_id = fib4_entry->tb_id;
	fri.dst = cpu_to_be32(*p_dst);
	fri.dst_len = dst_len;
	fri.tos = fib4_entry->tos;
	fri.type = fib4_entry->type;
	fri.offload = should_offload;
	fri.trap = !should_offload;
	fri.offload_failed = false;
	fib_alias_hw_flags_set(mlxsw_sp_net(mlxsw_sp), &fri);
पूर्ण

अटल व्योम
mlxsw_sp_fib4_entry_hw_flags_clear(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	u32 *p_dst = (u32 *) fib_entry->fib_node->key.addr;
	पूर्णांक dst_len = fib_entry->fib_node->key.prefix_len;
	काष्ठा mlxsw_sp_fib4_entry *fib4_entry;
	काष्ठा fib_rt_info fri;

	fib4_entry = container_of(fib_entry, काष्ठा mlxsw_sp_fib4_entry,
				  common);
	fri.fi = fib4_entry->fi;
	fri.tb_id = fib4_entry->tb_id;
	fri.dst = cpu_to_be32(*p_dst);
	fri.dst_len = dst_len;
	fri.tos = fib4_entry->tos;
	fri.type = fib4_entry->type;
	fri.offload = false;
	fri.trap = false;
	fri.offload_failed = false;
	fib_alias_hw_flags_set(mlxsw_sp_net(mlxsw_sp), &fri);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम
mlxsw_sp_fib6_offload_failed_flag_set(काष्ठा mlxsw_sp *mlxsw_sp,
				      काष्ठा fib6_info **rt_arr,
				      अचिन्हित पूर्णांक nrt6)
अणु
	पूर्णांक i;

	/* In IPv6 a multipath route is represented using multiple routes, so
	 * we need to set the flags on all of them.
	 */
	क्रम (i = 0; i < nrt6; i++)
		fib6_info_hw_flags_set(mlxsw_sp_net(mlxsw_sp), rt_arr[i],
				       false, false, true);
पूर्ण
#अन्यथा
अटल व्योम
mlxsw_sp_fib6_offload_failed_flag_set(काष्ठा mlxsw_sp *mlxsw_sp,
				      काष्ठा fib6_info **rt_arr,
				      अचिन्हित पूर्णांक nrt6)
अणु
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम
mlxsw_sp_fib6_entry_hw_flags_set(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	काष्ठा mlxsw_sp_fib6_entry *fib6_entry;
	काष्ठा mlxsw_sp_rt6 *mlxsw_sp_rt6;
	bool should_offload;

	should_offload = mlxsw_sp_fib_entry_should_offload(fib_entry);

	/* In IPv6 a multipath route is represented using multiple routes, so
	 * we need to set the flags on all of them.
	 */
	fib6_entry = container_of(fib_entry, काष्ठा mlxsw_sp_fib6_entry,
				  common);
	list_क्रम_each_entry(mlxsw_sp_rt6, &fib6_entry->rt6_list, list)
		fib6_info_hw_flags_set(mlxsw_sp_net(mlxsw_sp), mlxsw_sp_rt6->rt,
				       should_offload, !should_offload, false);
पूर्ण
#अन्यथा
अटल व्योम
mlxsw_sp_fib6_entry_hw_flags_set(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम
mlxsw_sp_fib6_entry_hw_flags_clear(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	काष्ठा mlxsw_sp_fib6_entry *fib6_entry;
	काष्ठा mlxsw_sp_rt6 *mlxsw_sp_rt6;

	fib6_entry = container_of(fib_entry, काष्ठा mlxsw_sp_fib6_entry,
				  common);
	list_क्रम_each_entry(mlxsw_sp_rt6, &fib6_entry->rt6_list, list)
		fib6_info_hw_flags_set(mlxsw_sp_net(mlxsw_sp), mlxsw_sp_rt6->rt,
				       false, false, false);
पूर्ण
#अन्यथा
अटल व्योम
mlxsw_sp_fib6_entry_hw_flags_clear(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम
mlxsw_sp_fib_entry_hw_flags_set(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	चयन (fib_entry->fib_node->fib->proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		mlxsw_sp_fib4_entry_hw_flags_set(mlxsw_sp, fib_entry);
		अवरोध;
	हाल MLXSW_SP_L3_PROTO_IPV6:
		mlxsw_sp_fib6_entry_hw_flags_set(mlxsw_sp, fib_entry);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
mlxsw_sp_fib_entry_hw_flags_clear(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	चयन (fib_entry->fib_node->fib->proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		mlxsw_sp_fib4_entry_hw_flags_clear(mlxsw_sp, fib_entry);
		अवरोध;
	हाल MLXSW_SP_L3_PROTO_IPV6:
		mlxsw_sp_fib6_entry_hw_flags_clear(mlxsw_sp, fib_entry);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
mlxsw_sp_fib_entry_hw_flags_refresh(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_fib_entry *fib_entry,
				    क्रमागत mlxsw_sp_fib_entry_op op)
अणु
	चयन (op) अणु
	हाल MLXSW_SP_FIB_ENTRY_OP_WRITE:
	हाल MLXSW_SP_FIB_ENTRY_OP_UPDATE:
		mlxsw_sp_fib_entry_hw_flags_set(mlxsw_sp, fib_entry);
		अवरोध;
	हाल MLXSW_SP_FIB_ENTRY_OP_DELETE:
		mlxsw_sp_fib_entry_hw_flags_clear(mlxsw_sp, fib_entry);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

काष्ठा mlxsw_sp_fib_entry_op_ctx_basic अणु
	अक्षर ralue_pl[MLXSW_REG_RALUE_LEN];
पूर्ण;

अटल व्योम
mlxsw_sp_router_ll_basic_fib_entry_pack(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
					क्रमागत mlxsw_sp_l3proto proto,
					क्रमागत mlxsw_sp_fib_entry_op op,
					u16 भव_router, u8 prefix_len,
					अचिन्हित अक्षर *addr,
					काष्ठा mlxsw_sp_fib_entry_priv *priv)
अणु
	काष्ठा mlxsw_sp_fib_entry_op_ctx_basic *op_ctx_basic = (व्योम *) op_ctx->ll_priv;
	क्रमागत mlxsw_reg_ralxx_protocol ralxx_proto;
	अक्षर *ralue_pl = op_ctx_basic->ralue_pl;
	क्रमागत mlxsw_reg_ralue_op ralue_op;

	ralxx_proto = (क्रमागत mlxsw_reg_ralxx_protocol) proto;

	चयन (op) अणु
	हाल MLXSW_SP_FIB_ENTRY_OP_WRITE:
	हाल MLXSW_SP_FIB_ENTRY_OP_UPDATE:
		ralue_op = MLXSW_REG_RALUE_OP_WRITE_WRITE;
		अवरोध;
	हाल MLXSW_SP_FIB_ENTRY_OP_DELETE:
		ralue_op = MLXSW_REG_RALUE_OP_WRITE_DELETE;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	चयन (proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		mlxsw_reg_ralue_pack4(ralue_pl, ralxx_proto, ralue_op,
				      भव_router, prefix_len, (u32 *) addr);
		अवरोध;
	हाल MLXSW_SP_L3_PROTO_IPV6:
		mlxsw_reg_ralue_pack6(ralue_pl, ralxx_proto, ralue_op,
				      भव_router, prefix_len, addr);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
mlxsw_sp_router_ll_basic_fib_entry_act_remote_pack(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
						   क्रमागत mlxsw_reg_ralue_trap_action trap_action,
						   u16 trap_id, u32 adjacency_index, u16 ecmp_size)
अणु
	काष्ठा mlxsw_sp_fib_entry_op_ctx_basic *op_ctx_basic = (व्योम *) op_ctx->ll_priv;

	mlxsw_reg_ralue_act_remote_pack(op_ctx_basic->ralue_pl, trap_action,
					trap_id, adjacency_index, ecmp_size);
पूर्ण

अटल व्योम
mlxsw_sp_router_ll_basic_fib_entry_act_local_pack(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
						  क्रमागत mlxsw_reg_ralue_trap_action trap_action,
						  u16 trap_id, u16 local_erअगर)
अणु
	काष्ठा mlxsw_sp_fib_entry_op_ctx_basic *op_ctx_basic = (व्योम *) op_ctx->ll_priv;

	mlxsw_reg_ralue_act_local_pack(op_ctx_basic->ralue_pl, trap_action,
				       trap_id, local_erअगर);
पूर्ण

अटल व्योम
mlxsw_sp_router_ll_basic_fib_entry_act_ip2me_pack(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx)
अणु
	काष्ठा mlxsw_sp_fib_entry_op_ctx_basic *op_ctx_basic = (व्योम *) op_ctx->ll_priv;

	mlxsw_reg_ralue_act_ip2me_pack(op_ctx_basic->ralue_pl);
पूर्ण

अटल व्योम
mlxsw_sp_router_ll_basic_fib_entry_act_ip2me_tun_pack(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
						      u32 tunnel_ptr)
अणु
	काष्ठा mlxsw_sp_fib_entry_op_ctx_basic *op_ctx_basic = (व्योम *) op_ctx->ll_priv;

	mlxsw_reg_ralue_act_ip2me_tun_pack(op_ctx_basic->ralue_pl, tunnel_ptr);
पूर्ण

अटल पूर्णांक
mlxsw_sp_router_ll_basic_fib_entry_commit(काष्ठा mlxsw_sp *mlxsw_sp,
					  काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
					  bool *postponed_क्रम_bulk)
अणु
	काष्ठा mlxsw_sp_fib_entry_op_ctx_basic *op_ctx_basic = (व्योम *) op_ctx->ll_priv;

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ralue),
			       op_ctx_basic->ralue_pl);
पूर्ण

अटल bool
mlxsw_sp_router_ll_basic_fib_entry_is_committed(काष्ठा mlxsw_sp_fib_entry_priv *priv)
अणु
	वापस true;
पूर्ण

अटल व्योम mlxsw_sp_fib_entry_pack(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
				    काष्ठा mlxsw_sp_fib_entry *fib_entry,
				    क्रमागत mlxsw_sp_fib_entry_op op)
अणु
	काष्ठा mlxsw_sp_fib *fib = fib_entry->fib_node->fib;

	mlxsw_sp_fib_entry_op_ctx_priv_hold(op_ctx, fib_entry->priv);
	fib->ll_ops->fib_entry_pack(op_ctx, fib->proto, op, fib->vr->id,
				    fib_entry->fib_node->key.prefix_len,
				    fib_entry->fib_node->key.addr,
				    fib_entry->priv);
पूर्ण

अटल पूर्णांक mlxsw_sp_fib_entry_commit(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
				     स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops)
अणु
	bool postponed_क्रम_bulk = false;
	पूर्णांक err;

	err = ll_ops->fib_entry_commit(mlxsw_sp, op_ctx, &postponed_क्रम_bulk);
	अगर (!postponed_क्रम_bulk)
		mlxsw_sp_fib_entry_op_ctx_priv_put_all(op_ctx);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_adj_discard_ग_लिखो(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	क्रमागत mlxsw_reg_ratr_trap_action trap_action;
	अक्षर ratr_pl[MLXSW_REG_RATR_LEN];
	पूर्णांक err;

	अगर (mlxsw_sp->router->adj_discard_index_valid)
		वापस 0;

	err = mlxsw_sp_kvdl_alloc(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ, 1,
				  &mlxsw_sp->router->adj_discard_index);
	अगर (err)
		वापस err;

	trap_action = MLXSW_REG_RATR_TRAP_ACTION_TRAP;
	mlxsw_reg_ratr_pack(ratr_pl, MLXSW_REG_RATR_OP_WRITE_WRITE_ENTRY, true,
			    MLXSW_REG_RATR_TYPE_ETHERNET,
			    mlxsw_sp->router->adj_discard_index,
			    mlxsw_sp->router->lb_rअगर_index);
	mlxsw_reg_ratr_trap_action_set(ratr_pl, trap_action);
	mlxsw_reg_ratr_trap_id_set(ratr_pl, MLXSW_TRAP_ID_RTR_EGRESS0);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ratr), ratr_pl);
	अगर (err)
		जाओ err_ratr_ग_लिखो;

	mlxsw_sp->router->adj_discard_index_valid = true;

	वापस 0;

err_ratr_ग_लिखो:
	mlxsw_sp_kvdl_मुक्त(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ, 1,
			   mlxsw_sp->router->adj_discard_index);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_fib_entry_op_remote(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
					काष्ठा mlxsw_sp_fib_entry *fib_entry,
					क्रमागत mlxsw_sp_fib_entry_op op)
अणु
	स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops = fib_entry->fib_node->fib->ll_ops;
	काष्ठा mlxsw_sp_nexthop_group *nh_group = fib_entry->nh_group;
	काष्ठा mlxsw_sp_nexthop_group_info *nhgi = nh_group->nhgi;
	क्रमागत mlxsw_reg_ralue_trap_action trap_action;
	u16 trap_id = 0;
	u32 adjacency_index = 0;
	u16 ecmp_size = 0;
	पूर्णांक err;

	/* In हाल the nexthop group adjacency index is valid, use it
	 * with provided ECMP size. Otherwise, setup trap and pass
	 * traffic to kernel.
	 */
	अगर (mlxsw_sp_fib_entry_should_offload(fib_entry)) अणु
		trap_action = MLXSW_REG_RALUE_TRAP_ACTION_NOP;
		adjacency_index = nhgi->adj_index;
		ecmp_size = nhgi->ecmp_size;
	पूर्ण अन्यथा अगर (!nhgi->adj_index_valid && nhgi->count && nhgi->nh_rअगर) अणु
		err = mlxsw_sp_adj_discard_ग_लिखो(mlxsw_sp);
		अगर (err)
			वापस err;
		trap_action = MLXSW_REG_RALUE_TRAP_ACTION_NOP;
		adjacency_index = mlxsw_sp->router->adj_discard_index;
		ecmp_size = 1;
	पूर्ण अन्यथा अणु
		trap_action = MLXSW_REG_RALUE_TRAP_ACTION_TRAP;
		trap_id = MLXSW_TRAP_ID_RTR_INGRESS0;
	पूर्ण

	mlxsw_sp_fib_entry_pack(op_ctx, fib_entry, op);
	ll_ops->fib_entry_act_remote_pack(op_ctx, trap_action, trap_id,
					  adjacency_index, ecmp_size);
	वापस mlxsw_sp_fib_entry_commit(mlxsw_sp, op_ctx, ll_ops);
पूर्ण

अटल पूर्णांक mlxsw_sp_fib_entry_op_local(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
				       काष्ठा mlxsw_sp_fib_entry *fib_entry,
				       क्रमागत mlxsw_sp_fib_entry_op op)
अणु
	स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops = fib_entry->fib_node->fib->ll_ops;
	काष्ठा mlxsw_sp_rअगर *rअगर = fib_entry->nh_group->nhgi->nh_rअगर;
	क्रमागत mlxsw_reg_ralue_trap_action trap_action;
	u16 trap_id = 0;
	u16 rअगर_index = 0;

	अगर (mlxsw_sp_fib_entry_should_offload(fib_entry)) अणु
		trap_action = MLXSW_REG_RALUE_TRAP_ACTION_NOP;
		rअगर_index = rअगर->rअगर_index;
	पूर्ण अन्यथा अणु
		trap_action = MLXSW_REG_RALUE_TRAP_ACTION_TRAP;
		trap_id = MLXSW_TRAP_ID_RTR_INGRESS0;
	पूर्ण

	mlxsw_sp_fib_entry_pack(op_ctx, fib_entry, op);
	ll_ops->fib_entry_act_local_pack(op_ctx, trap_action, trap_id, rअगर_index);
	वापस mlxsw_sp_fib_entry_commit(mlxsw_sp, op_ctx, ll_ops);
पूर्ण

अटल पूर्णांक mlxsw_sp_fib_entry_op_trap(काष्ठा mlxsw_sp *mlxsw_sp,
				      काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
				      काष्ठा mlxsw_sp_fib_entry *fib_entry,
				      क्रमागत mlxsw_sp_fib_entry_op op)
अणु
	स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops = fib_entry->fib_node->fib->ll_ops;

	mlxsw_sp_fib_entry_pack(op_ctx, fib_entry, op);
	ll_ops->fib_entry_act_ip2me_pack(op_ctx);
	वापस mlxsw_sp_fib_entry_commit(mlxsw_sp, op_ctx, ll_ops);
पूर्ण

अटल पूर्णांक mlxsw_sp_fib_entry_op_blackhole(काष्ठा mlxsw_sp *mlxsw_sp,
					   काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
					   काष्ठा mlxsw_sp_fib_entry *fib_entry,
					   क्रमागत mlxsw_sp_fib_entry_op op)
अणु
	स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops = fib_entry->fib_node->fib->ll_ops;
	क्रमागत mlxsw_reg_ralue_trap_action trap_action;

	trap_action = MLXSW_REG_RALUE_TRAP_ACTION_DISCARD_ERROR;
	mlxsw_sp_fib_entry_pack(op_ctx, fib_entry, op);
	ll_ops->fib_entry_act_local_pack(op_ctx, trap_action, 0, 0);
	वापस mlxsw_sp_fib_entry_commit(mlxsw_sp, op_ctx, ll_ops);
पूर्ण

अटल पूर्णांक
mlxsw_sp_fib_entry_op_unreachable(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
				  काष्ठा mlxsw_sp_fib_entry *fib_entry,
				  क्रमागत mlxsw_sp_fib_entry_op op)
अणु
	स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops = fib_entry->fib_node->fib->ll_ops;
	क्रमागत mlxsw_reg_ralue_trap_action trap_action;
	u16 trap_id;

	trap_action = MLXSW_REG_RALUE_TRAP_ACTION_TRAP;
	trap_id = MLXSW_TRAP_ID_RTR_INGRESS1;

	mlxsw_sp_fib_entry_pack(op_ctx, fib_entry, op);
	ll_ops->fib_entry_act_local_pack(op_ctx, trap_action, trap_id, 0);
	वापस mlxsw_sp_fib_entry_commit(mlxsw_sp, op_ctx, ll_ops);
पूर्ण

अटल पूर्णांक
mlxsw_sp_fib_entry_op_ipip_decap(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
				 काष्ठा mlxsw_sp_fib_entry *fib_entry,
				 क्रमागत mlxsw_sp_fib_entry_op op)
अणु
	स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops = fib_entry->fib_node->fib->ll_ops;
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry = fib_entry->decap.ipip_entry;
	स्थिर काष्ठा mlxsw_sp_ipip_ops *ipip_ops;
	पूर्णांक err;

	अगर (WARN_ON(!ipip_entry))
		वापस -EINVAL;

	ipip_ops = mlxsw_sp->router->ipip_ops_arr[ipip_entry->ipipt];
	err = ipip_ops->decap_config(mlxsw_sp, ipip_entry,
				     fib_entry->decap.tunnel_index);
	अगर (err)
		वापस err;

	mlxsw_sp_fib_entry_pack(op_ctx, fib_entry, op);
	ll_ops->fib_entry_act_ip2me_tun_pack(op_ctx,
					     fib_entry->decap.tunnel_index);
	वापस mlxsw_sp_fib_entry_commit(mlxsw_sp, op_ctx, ll_ops);
पूर्ण

अटल पूर्णांक mlxsw_sp_fib_entry_op_nve_decap(काष्ठा mlxsw_sp *mlxsw_sp,
					   काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
					   काष्ठा mlxsw_sp_fib_entry *fib_entry,
					   क्रमागत mlxsw_sp_fib_entry_op op)
अणु
	स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops = fib_entry->fib_node->fib->ll_ops;

	mlxsw_sp_fib_entry_pack(op_ctx, fib_entry, op);
	ll_ops->fib_entry_act_ip2me_tun_pack(op_ctx,
					     fib_entry->decap.tunnel_index);
	वापस mlxsw_sp_fib_entry_commit(mlxsw_sp, op_ctx, ll_ops);
पूर्ण

अटल पूर्णांक __mlxsw_sp_fib_entry_op(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
				   काष्ठा mlxsw_sp_fib_entry *fib_entry,
				   क्रमागत mlxsw_sp_fib_entry_op op)
अणु
	चयन (fib_entry->type) अणु
	हाल MLXSW_SP_FIB_ENTRY_TYPE_REMOTE:
		वापस mlxsw_sp_fib_entry_op_remote(mlxsw_sp, op_ctx, fib_entry, op);
	हाल MLXSW_SP_FIB_ENTRY_TYPE_LOCAL:
		वापस mlxsw_sp_fib_entry_op_local(mlxsw_sp, op_ctx, fib_entry, op);
	हाल MLXSW_SP_FIB_ENTRY_TYPE_TRAP:
		वापस mlxsw_sp_fib_entry_op_trap(mlxsw_sp, op_ctx, fib_entry, op);
	हाल MLXSW_SP_FIB_ENTRY_TYPE_BLACKHOLE:
		वापस mlxsw_sp_fib_entry_op_blackhole(mlxsw_sp, op_ctx, fib_entry, op);
	हाल MLXSW_SP_FIB_ENTRY_TYPE_UNREACHABLE:
		वापस mlxsw_sp_fib_entry_op_unreachable(mlxsw_sp, op_ctx, fib_entry, op);
	हाल MLXSW_SP_FIB_ENTRY_TYPE_IPIP_DECAP:
		वापस mlxsw_sp_fib_entry_op_ipip_decap(mlxsw_sp, op_ctx, fib_entry, op);
	हाल MLXSW_SP_FIB_ENTRY_TYPE_NVE_DECAP:
		वापस mlxsw_sp_fib_entry_op_nve_decap(mlxsw_sp, op_ctx, fib_entry, op);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mlxsw_sp_fib_entry_op(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
				 काष्ठा mlxsw_sp_fib_entry *fib_entry,
				 क्रमागत mlxsw_sp_fib_entry_op op)
अणु
	पूर्णांक err = __mlxsw_sp_fib_entry_op(mlxsw_sp, op_ctx, fib_entry, op);

	अगर (err)
		वापस err;

	mlxsw_sp_fib_entry_hw_flags_refresh(mlxsw_sp, fib_entry, op);

	वापस err;
पूर्ण

अटल पूर्णांक __mlxsw_sp_fib_entry_update(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
				       काष्ठा mlxsw_sp_fib_entry *fib_entry,
				       bool is_new)
अणु
	वापस mlxsw_sp_fib_entry_op(mlxsw_sp, op_ctx, fib_entry,
				     is_new ? MLXSW_SP_FIB_ENTRY_OP_WRITE :
					      MLXSW_SP_FIB_ENTRY_OP_UPDATE);
पूर्ण

अटल पूर्णांक mlxsw_sp_fib_entry_update(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx = mlxsw_sp->router->ll_op_ctx;

	mlxsw_sp_fib_entry_op_ctx_clear(op_ctx);
	वापस __mlxsw_sp_fib_entry_update(mlxsw_sp, op_ctx, fib_entry, false);
पूर्ण

अटल पूर्णांक mlxsw_sp_fib_entry_del(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
				  काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops = fib_entry->fib_node->fib->ll_ops;

	अगर (!ll_ops->fib_entry_is_committed(fib_entry->priv))
		वापस 0;
	वापस mlxsw_sp_fib_entry_op(mlxsw_sp, op_ctx, fib_entry,
				     MLXSW_SP_FIB_ENTRY_OP_DELETE);
पूर्ण

अटल पूर्णांक
mlxsw_sp_fib4_entry_type_set(काष्ठा mlxsw_sp *mlxsw_sp,
			     स्थिर काष्ठा fib_entry_notअगरier_info *fen_info,
			     काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	काष्ठा mlxsw_sp_nexthop_group_info *nhgi = fib_entry->nh_group->nhgi;
	जोड़ mlxsw_sp_l3addr dip = अणु .addr4 = htonl(fen_info->dst) पूर्ण;
	काष्ठा mlxsw_sp_router *router = mlxsw_sp->router;
	u32 tb_id = mlxsw_sp_fix_tb_id(fen_info->tb_id);
	पूर्णांक अगरindex = nhgi->nexthops[0].अगरindex;
	काष्ठा mlxsw_sp_ipip_entry *ipip_entry;

	चयन (fen_info->type) अणु
	हाल RTN_LOCAL:
		ipip_entry = mlxsw_sp_ipip_entry_find_by_decap(mlxsw_sp, अगरindex,
							       MLXSW_SP_L3_PROTO_IPV4, dip);
		अगर (ipip_entry && ipip_entry->ol_dev->flags & IFF_UP) अणु
			fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_IPIP_DECAP;
			वापस mlxsw_sp_fib_entry_decap_init(mlxsw_sp,
							     fib_entry,
							     ipip_entry);
		पूर्ण
		अगर (mlxsw_sp_router_nve_is_decap(mlxsw_sp, tb_id,
						 MLXSW_SP_L3_PROTO_IPV4,
						 &dip)) अणु
			u32 tunnel_index;

			tunnel_index = router->nve_decap_config.tunnel_index;
			fib_entry->decap.tunnel_index = tunnel_index;
			fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_NVE_DECAP;
			वापस 0;
		पूर्ण
		fallthrough;
	हाल RTN_BROADCAST:
		fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_TRAP;
		वापस 0;
	हाल RTN_BLACKHOLE:
		fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_BLACKHOLE;
		वापस 0;
	हाल RTN_UNREACHABLE:
	हाल RTN_PROHIBIT:
		/* Packets hitting these routes need to be trapped, but
		 * can करो so with a lower priority than packets directed
		 * at the host, so use action type local instead of trap.
		 */
		fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_UNREACHABLE;
		वापस 0;
	हाल RTN_UNICAST:
		अगर (nhgi->gateway)
			fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_REMOTE;
		अन्यथा
			fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_LOCAL;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम
mlxsw_sp_fib4_entry_type_unset(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	चयन (fib_entry->type) अणु
	हाल MLXSW_SP_FIB_ENTRY_TYPE_IPIP_DECAP:
		mlxsw_sp_fib_entry_decap_fini(mlxsw_sp, fib_entry);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा mlxsw_sp_fib4_entry *
mlxsw_sp_fib4_entry_create(काष्ठा mlxsw_sp *mlxsw_sp,
			   काष्ठा mlxsw_sp_fib_node *fib_node,
			   स्थिर काष्ठा fib_entry_notअगरier_info *fen_info)
अणु
	काष्ठा mlxsw_sp_fib4_entry *fib4_entry;
	काष्ठा mlxsw_sp_fib_entry *fib_entry;
	पूर्णांक err;

	fib4_entry = kzalloc(माप(*fib4_entry), GFP_KERNEL);
	अगर (!fib4_entry)
		वापस ERR_PTR(-ENOMEM);
	fib_entry = &fib4_entry->common;

	fib_entry->priv = mlxsw_sp_fib_entry_priv_create(fib_node->fib->ll_ops);
	अगर (IS_ERR(fib_entry->priv)) अणु
		err = PTR_ERR(fib_entry->priv);
		जाओ err_fib_entry_priv_create;
	पूर्ण

	err = mlxsw_sp_nexthop4_group_get(mlxsw_sp, fib_entry, fen_info->fi);
	अगर (err)
		जाओ err_nexthop4_group_get;

	err = mlxsw_sp_nexthop_group_vr_link(fib_entry->nh_group,
					     fib_node->fib);
	अगर (err)
		जाओ err_nexthop_group_vr_link;

	err = mlxsw_sp_fib4_entry_type_set(mlxsw_sp, fen_info, fib_entry);
	अगर (err)
		जाओ err_fib4_entry_type_set;

	fib4_entry->fi = fen_info->fi;
	fib_info_hold(fib4_entry->fi);
	fib4_entry->tb_id = fen_info->tb_id;
	fib4_entry->type = fen_info->type;
	fib4_entry->tos = fen_info->tos;

	fib_entry->fib_node = fib_node;

	वापस fib4_entry;

err_fib4_entry_type_set:
	mlxsw_sp_nexthop_group_vr_unlink(fib_entry->nh_group, fib_node->fib);
err_nexthop_group_vr_link:
	mlxsw_sp_nexthop4_group_put(mlxsw_sp, &fib4_entry->common);
err_nexthop4_group_get:
	mlxsw_sp_fib_entry_priv_put(fib_entry->priv);
err_fib_entry_priv_create:
	kमुक्त(fib4_entry);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_sp_fib4_entry_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_fib4_entry *fib4_entry)
अणु
	काष्ठा mlxsw_sp_fib_node *fib_node = fib4_entry->common.fib_node;

	fib_info_put(fib4_entry->fi);
	mlxsw_sp_fib4_entry_type_unset(mlxsw_sp, &fib4_entry->common);
	mlxsw_sp_nexthop_group_vr_unlink(fib4_entry->common.nh_group,
					 fib_node->fib);
	mlxsw_sp_nexthop4_group_put(mlxsw_sp, &fib4_entry->common);
	mlxsw_sp_fib_entry_priv_put(fib4_entry->common.priv);
	kमुक्त(fib4_entry);
पूर्ण

अटल काष्ठा mlxsw_sp_fib4_entry *
mlxsw_sp_fib4_entry_lookup(काष्ठा mlxsw_sp *mlxsw_sp,
			   स्थिर काष्ठा fib_entry_notअगरier_info *fen_info)
अणु
	काष्ठा mlxsw_sp_fib4_entry *fib4_entry;
	काष्ठा mlxsw_sp_fib_node *fib_node;
	काष्ठा mlxsw_sp_fib *fib;
	काष्ठा mlxsw_sp_vr *vr;

	vr = mlxsw_sp_vr_find(mlxsw_sp, fen_info->tb_id);
	अगर (!vr)
		वापस शून्य;
	fib = mlxsw_sp_vr_fib(vr, MLXSW_SP_L3_PROTO_IPV4);

	fib_node = mlxsw_sp_fib_node_lookup(fib, &fen_info->dst,
					    माप(fen_info->dst),
					    fen_info->dst_len);
	अगर (!fib_node)
		वापस शून्य;

	fib4_entry = container_of(fib_node->fib_entry,
				  काष्ठा mlxsw_sp_fib4_entry, common);
	अगर (fib4_entry->tb_id == fen_info->tb_id &&
	    fib4_entry->tos == fen_info->tos &&
	    fib4_entry->type == fen_info->type &&
	    fib4_entry->fi == fen_info->fi)
		वापस fib4_entry;

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_fib_ht_params = अणु
	.key_offset = दुरत्व(काष्ठा mlxsw_sp_fib_node, key),
	.head_offset = दुरत्व(काष्ठा mlxsw_sp_fib_node, ht_node),
	.key_len = माप(काष्ठा mlxsw_sp_fib_key),
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल पूर्णांक mlxsw_sp_fib_node_insert(काष्ठा mlxsw_sp_fib *fib,
				    काष्ठा mlxsw_sp_fib_node *fib_node)
अणु
	वापस rhashtable_insert_fast(&fib->ht, &fib_node->ht_node,
				      mlxsw_sp_fib_ht_params);
पूर्ण

अटल व्योम mlxsw_sp_fib_node_हटाओ(काष्ठा mlxsw_sp_fib *fib,
				     काष्ठा mlxsw_sp_fib_node *fib_node)
अणु
	rhashtable_हटाओ_fast(&fib->ht, &fib_node->ht_node,
			       mlxsw_sp_fib_ht_params);
पूर्ण

अटल काष्ठा mlxsw_sp_fib_node *
mlxsw_sp_fib_node_lookup(काष्ठा mlxsw_sp_fib *fib, स्थिर व्योम *addr,
			 माप_प्रकार addr_len, अचिन्हित अक्षर prefix_len)
अणु
	काष्ठा mlxsw_sp_fib_key key;

	स_रखो(&key, 0, माप(key));
	स_नकल(key.addr, addr, addr_len);
	key.prefix_len = prefix_len;
	वापस rhashtable_lookup_fast(&fib->ht, &key, mlxsw_sp_fib_ht_params);
पूर्ण

अटल काष्ठा mlxsw_sp_fib_node *
mlxsw_sp_fib_node_create(काष्ठा mlxsw_sp_fib *fib, स्थिर व्योम *addr,
			 माप_प्रकार addr_len, अचिन्हित अक्षर prefix_len)
अणु
	काष्ठा mlxsw_sp_fib_node *fib_node;

	fib_node = kzalloc(माप(*fib_node), GFP_KERNEL);
	अगर (!fib_node)
		वापस शून्य;

	list_add(&fib_node->list, &fib->node_list);
	स_नकल(fib_node->key.addr, addr, addr_len);
	fib_node->key.prefix_len = prefix_len;

	वापस fib_node;
पूर्ण

अटल व्योम mlxsw_sp_fib_node_destroy(काष्ठा mlxsw_sp_fib_node *fib_node)
अणु
	list_del(&fib_node->list);
	kमुक्त(fib_node);
पूर्ण

अटल पूर्णांक mlxsw_sp_fib_lpm_tree_link(काष्ठा mlxsw_sp *mlxsw_sp,
				      काष्ठा mlxsw_sp_fib_node *fib_node)
अणु
	काष्ठा mlxsw_sp_prefix_usage req_prefix_usage;
	काष्ठा mlxsw_sp_fib *fib = fib_node->fib;
	काष्ठा mlxsw_sp_lpm_tree *lpm_tree;
	पूर्णांक err;

	lpm_tree = mlxsw_sp->router->lpm.proto_trees[fib->proto];
	अगर (lpm_tree->prefix_ref_count[fib_node->key.prefix_len] != 0)
		जाओ out;

	mlxsw_sp_prefix_usage_cpy(&req_prefix_usage, &lpm_tree->prefix_usage);
	mlxsw_sp_prefix_usage_set(&req_prefix_usage, fib_node->key.prefix_len);
	lpm_tree = mlxsw_sp_lpm_tree_get(mlxsw_sp, &req_prefix_usage,
					 fib->proto);
	अगर (IS_ERR(lpm_tree))
		वापस PTR_ERR(lpm_tree);

	err = mlxsw_sp_vrs_lpm_tree_replace(mlxsw_sp, fib, lpm_tree);
	अगर (err)
		जाओ err_lpm_tree_replace;

out:
	lpm_tree->prefix_ref_count[fib_node->key.prefix_len]++;
	वापस 0;

err_lpm_tree_replace:
	mlxsw_sp_lpm_tree_put(mlxsw_sp, lpm_tree);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_fib_lpm_tree_unlink(काष्ठा mlxsw_sp *mlxsw_sp,
					 काष्ठा mlxsw_sp_fib_node *fib_node)
अणु
	काष्ठा mlxsw_sp_lpm_tree *lpm_tree = fib_node->fib->lpm_tree;
	काष्ठा mlxsw_sp_prefix_usage req_prefix_usage;
	काष्ठा mlxsw_sp_fib *fib = fib_node->fib;
	पूर्णांक err;

	अगर (--lpm_tree->prefix_ref_count[fib_node->key.prefix_len] != 0)
		वापस;
	/* Try to स्थिरruct a new LPM tree from the current prefix usage
	 * minus the unused one. If we fail, जारी using the old one.
	 */
	mlxsw_sp_prefix_usage_cpy(&req_prefix_usage, &lpm_tree->prefix_usage);
	mlxsw_sp_prefix_usage_clear(&req_prefix_usage,
				    fib_node->key.prefix_len);
	lpm_tree = mlxsw_sp_lpm_tree_get(mlxsw_sp, &req_prefix_usage,
					 fib->proto);
	अगर (IS_ERR(lpm_tree))
		वापस;

	err = mlxsw_sp_vrs_lpm_tree_replace(mlxsw_sp, fib, lpm_tree);
	अगर (err)
		जाओ err_lpm_tree_replace;

	वापस;

err_lpm_tree_replace:
	mlxsw_sp_lpm_tree_put(mlxsw_sp, lpm_tree);
पूर्ण

अटल पूर्णांक mlxsw_sp_fib_node_init(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_fib_node *fib_node,
				  काष्ठा mlxsw_sp_fib *fib)
अणु
	पूर्णांक err;

	err = mlxsw_sp_fib_node_insert(fib, fib_node);
	अगर (err)
		वापस err;
	fib_node->fib = fib;

	err = mlxsw_sp_fib_lpm_tree_link(mlxsw_sp, fib_node);
	अगर (err)
		जाओ err_fib_lpm_tree_link;

	वापस 0;

err_fib_lpm_tree_link:
	fib_node->fib = शून्य;
	mlxsw_sp_fib_node_हटाओ(fib, fib_node);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_fib_node_fini(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_fib_node *fib_node)
अणु
	काष्ठा mlxsw_sp_fib *fib = fib_node->fib;

	mlxsw_sp_fib_lpm_tree_unlink(mlxsw_sp, fib_node);
	fib_node->fib = शून्य;
	mlxsw_sp_fib_node_हटाओ(fib, fib_node);
पूर्ण

अटल काष्ठा mlxsw_sp_fib_node *
mlxsw_sp_fib_node_get(काष्ठा mlxsw_sp *mlxsw_sp, u32 tb_id, स्थिर व्योम *addr,
		      माप_प्रकार addr_len, अचिन्हित अक्षर prefix_len,
		      क्रमागत mlxsw_sp_l3proto proto)
अणु
	काष्ठा mlxsw_sp_fib_node *fib_node;
	काष्ठा mlxsw_sp_fib *fib;
	काष्ठा mlxsw_sp_vr *vr;
	पूर्णांक err;

	vr = mlxsw_sp_vr_get(mlxsw_sp, tb_id, शून्य);
	अगर (IS_ERR(vr))
		वापस ERR_CAST(vr);
	fib = mlxsw_sp_vr_fib(vr, proto);

	fib_node = mlxsw_sp_fib_node_lookup(fib, addr, addr_len, prefix_len);
	अगर (fib_node)
		वापस fib_node;

	fib_node = mlxsw_sp_fib_node_create(fib, addr, addr_len, prefix_len);
	अगर (!fib_node) अणु
		err = -ENOMEM;
		जाओ err_fib_node_create;
	पूर्ण

	err = mlxsw_sp_fib_node_init(mlxsw_sp, fib_node, fib);
	अगर (err)
		जाओ err_fib_node_init;

	वापस fib_node;

err_fib_node_init:
	mlxsw_sp_fib_node_destroy(fib_node);
err_fib_node_create:
	mlxsw_sp_vr_put(mlxsw_sp, vr);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_sp_fib_node_put(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_fib_node *fib_node)
अणु
	काष्ठा mlxsw_sp_vr *vr = fib_node->fib->vr;

	अगर (fib_node->fib_entry)
		वापस;
	mlxsw_sp_fib_node_fini(mlxsw_sp, fib_node);
	mlxsw_sp_fib_node_destroy(fib_node);
	mlxsw_sp_vr_put(mlxsw_sp, vr);
पूर्ण

अटल पूर्णांक mlxsw_sp_fib_node_entry_link(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
					काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	काष्ठा mlxsw_sp_fib_node *fib_node = fib_entry->fib_node;
	bool is_new = !fib_node->fib_entry;
	पूर्णांक err;

	fib_node->fib_entry = fib_entry;

	err = __mlxsw_sp_fib_entry_update(mlxsw_sp, op_ctx, fib_entry, is_new);
	अगर (err)
		जाओ err_fib_entry_update;

	वापस 0;

err_fib_entry_update:
	fib_node->fib_entry = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक __mlxsw_sp_fib_node_entry_unlink(काष्ठा mlxsw_sp *mlxsw_sp,
					    काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
					    काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	काष्ठा mlxsw_sp_fib_node *fib_node = fib_entry->fib_node;
	पूर्णांक err;

	err = mlxsw_sp_fib_entry_del(mlxsw_sp, op_ctx, fib_entry);
	fib_node->fib_entry = शून्य;
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_fib_node_entry_unlink(काष्ठा mlxsw_sp *mlxsw_sp,
					   काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx = mlxsw_sp->router->ll_op_ctx;

	mlxsw_sp_fib_entry_op_ctx_clear(op_ctx);
	__mlxsw_sp_fib_node_entry_unlink(mlxsw_sp, op_ctx, fib_entry);
पूर्ण

अटल bool mlxsw_sp_fib4_allow_replace(काष्ठा mlxsw_sp_fib4_entry *fib4_entry)
अणु
	काष्ठा mlxsw_sp_fib_node *fib_node = fib4_entry->common.fib_node;
	काष्ठा mlxsw_sp_fib4_entry *fib4_replaced;

	अगर (!fib_node->fib_entry)
		वापस true;

	fib4_replaced = container_of(fib_node->fib_entry,
				     काष्ठा mlxsw_sp_fib4_entry, common);
	अगर (fib4_entry->tb_id == RT_TABLE_MAIN &&
	    fib4_replaced->tb_id == RT_TABLE_LOCAL)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक
mlxsw_sp_router_fib4_replace(काष्ठा mlxsw_sp *mlxsw_sp,
			     काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
			     स्थिर काष्ठा fib_entry_notअगरier_info *fen_info)
अणु
	काष्ठा mlxsw_sp_fib4_entry *fib4_entry, *fib4_replaced;
	काष्ठा mlxsw_sp_fib_entry *replaced;
	काष्ठा mlxsw_sp_fib_node *fib_node;
	पूर्णांक err;

	अगर (mlxsw_sp->router->पातed)
		वापस 0;

	अगर (fen_info->fi->nh &&
	    !mlxsw_sp_nexthop_obj_group_lookup(mlxsw_sp, fen_info->fi->nh->id))
		वापस 0;

	fib_node = mlxsw_sp_fib_node_get(mlxsw_sp, fen_info->tb_id,
					 &fen_info->dst, माप(fen_info->dst),
					 fen_info->dst_len,
					 MLXSW_SP_L3_PROTO_IPV4);
	अगर (IS_ERR(fib_node)) अणु
		dev_warn(mlxsw_sp->bus_info->dev, "Failed to get FIB node\n");
		वापस PTR_ERR(fib_node);
	पूर्ण

	fib4_entry = mlxsw_sp_fib4_entry_create(mlxsw_sp, fib_node, fen_info);
	अगर (IS_ERR(fib4_entry)) अणु
		dev_warn(mlxsw_sp->bus_info->dev, "Failed to create FIB entry\n");
		err = PTR_ERR(fib4_entry);
		जाओ err_fib4_entry_create;
	पूर्ण

	अगर (!mlxsw_sp_fib4_allow_replace(fib4_entry)) अणु
		mlxsw_sp_fib4_entry_destroy(mlxsw_sp, fib4_entry);
		mlxsw_sp_fib_node_put(mlxsw_sp, fib_node);
		वापस 0;
	पूर्ण

	replaced = fib_node->fib_entry;
	err = mlxsw_sp_fib_node_entry_link(mlxsw_sp, op_ctx, &fib4_entry->common);
	अगर (err) अणु
		dev_warn(mlxsw_sp->bus_info->dev, "Failed to link FIB entry to node\n");
		जाओ err_fib_node_entry_link;
	पूर्ण

	/* Nothing to replace */
	अगर (!replaced)
		वापस 0;

	mlxsw_sp_fib_entry_hw_flags_clear(mlxsw_sp, replaced);
	fib4_replaced = container_of(replaced, काष्ठा mlxsw_sp_fib4_entry,
				     common);
	mlxsw_sp_fib4_entry_destroy(mlxsw_sp, fib4_replaced);

	वापस 0;

err_fib_node_entry_link:
	fib_node->fib_entry = replaced;
	mlxsw_sp_fib4_entry_destroy(mlxsw_sp, fib4_entry);
err_fib4_entry_create:
	mlxsw_sp_fib_node_put(mlxsw_sp, fib_node);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_router_fib4_del(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
				    काष्ठा fib_entry_notअगरier_info *fen_info)
अणु
	काष्ठा mlxsw_sp_fib4_entry *fib4_entry;
	काष्ठा mlxsw_sp_fib_node *fib_node;
	पूर्णांक err;

	अगर (mlxsw_sp->router->पातed)
		वापस 0;

	fib4_entry = mlxsw_sp_fib4_entry_lookup(mlxsw_sp, fen_info);
	अगर (!fib4_entry)
		वापस 0;
	fib_node = fib4_entry->common.fib_node;

	err = __mlxsw_sp_fib_node_entry_unlink(mlxsw_sp, op_ctx, &fib4_entry->common);
	mlxsw_sp_fib4_entry_destroy(mlxsw_sp, fib4_entry);
	mlxsw_sp_fib_node_put(mlxsw_sp, fib_node);
	वापस err;
पूर्ण

अटल bool mlxsw_sp_fib6_rt_should_ignore(स्थिर काष्ठा fib6_info *rt)
अणु
	/* Multicast routes aren't supported, so ignore them. Neighbour
	 * Discovery packets are specअगरically trapped.
	 */
	अगर (ipv6_addr_type(&rt->fib6_dst.addr) & IPV6_ADDR_MULTICAST)
		वापस true;

	/* Cloned routes are irrelevant in the क्रमwarding path. */
	अगर (rt->fib6_flags & RTF_CACHE)
		वापस true;

	वापस false;
पूर्ण

अटल काष्ठा mlxsw_sp_rt6 *mlxsw_sp_rt6_create(काष्ठा fib6_info *rt)
अणु
	काष्ठा mlxsw_sp_rt6 *mlxsw_sp_rt6;

	mlxsw_sp_rt6 = kzalloc(माप(*mlxsw_sp_rt6), GFP_KERNEL);
	अगर (!mlxsw_sp_rt6)
		वापस ERR_PTR(-ENOMEM);

	/* In हाल of route replace, replaced route is deleted with
	 * no notअगरication. Take reference to prevent accessing मुक्तd
	 * memory.
	 */
	mlxsw_sp_rt6->rt = rt;
	fib6_info_hold(rt);

	वापस mlxsw_sp_rt6;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम mlxsw_sp_rt6_release(काष्ठा fib6_info *rt)
अणु
	fib6_info_release(rt);
पूर्ण
#अन्यथा
अटल व्योम mlxsw_sp_rt6_release(काष्ठा fib6_info *rt)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम mlxsw_sp_rt6_destroy(काष्ठा mlxsw_sp_rt6 *mlxsw_sp_rt6)
अणु
	काष्ठा fib6_nh *fib6_nh = mlxsw_sp_rt6->rt->fib6_nh;

	अगर (!mlxsw_sp_rt6->rt->nh)
		fib6_nh->fib_nh_flags &= ~RTNH_F_OFFLOAD;
	mlxsw_sp_rt6_release(mlxsw_sp_rt6->rt);
	kमुक्त(mlxsw_sp_rt6);
पूर्ण

अटल काष्ठा fib6_info *
mlxsw_sp_fib6_entry_rt(स्थिर काष्ठा mlxsw_sp_fib6_entry *fib6_entry)
अणु
	वापस list_first_entry(&fib6_entry->rt6_list, काष्ठा mlxsw_sp_rt6,
				list)->rt;
पूर्ण

अटल काष्ठा mlxsw_sp_rt6 *
mlxsw_sp_fib6_entry_rt_find(स्थिर काष्ठा mlxsw_sp_fib6_entry *fib6_entry,
			    स्थिर काष्ठा fib6_info *rt)
अणु
	काष्ठा mlxsw_sp_rt6 *mlxsw_sp_rt6;

	list_क्रम_each_entry(mlxsw_sp_rt6, &fib6_entry->rt6_list, list) अणु
		अगर (mlxsw_sp_rt6->rt == rt)
			वापस mlxsw_sp_rt6;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool mlxsw_sp_nexthop6_ipip_type(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
					स्थिर काष्ठा fib6_info *rt,
					क्रमागत mlxsw_sp_ipip_type *ret)
अणु
	वापस rt->fib6_nh->fib_nh_dev &&
	       mlxsw_sp_netdev_ipip_type(mlxsw_sp, rt->fib6_nh->fib_nh_dev, ret);
पूर्ण

अटल पूर्णांक mlxsw_sp_nexthop6_init(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_nexthop_group *nh_grp,
				  काष्ठा mlxsw_sp_nexthop *nh,
				  स्थिर काष्ठा fib6_info *rt)
अणु
	काष्ठा net_device *dev = rt->fib6_nh->fib_nh_dev;

	nh->nhgi = nh_grp->nhgi;
	nh->nh_weight = rt->fib6_nh->fib_nh_weight;
	स_नकल(&nh->gw_addr, &rt->fib6_nh->fib_nh_gw6, माप(nh->gw_addr));
#अगर IS_ENABLED(CONFIG_IPV6)
	nh->neigh_tbl = &nd_tbl;
#पूर्ण_अगर
	mlxsw_sp_nexthop_counter_alloc(mlxsw_sp, nh);

	list_add_tail(&nh->router_list_node, &mlxsw_sp->router->nexthop_list);

	अगर (!dev)
		वापस 0;
	nh->अगरindex = dev->अगरindex;

	वापस mlxsw_sp_nexthop_type_init(mlxsw_sp, nh, dev);
पूर्ण

अटल व्योम mlxsw_sp_nexthop6_fini(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_nexthop *nh)
अणु
	mlxsw_sp_nexthop_type_fini(mlxsw_sp, nh);
	list_del(&nh->router_list_node);
	mlxsw_sp_nexthop_counter_मुक्त(mlxsw_sp, nh);
पूर्ण

अटल bool mlxsw_sp_rt6_is_gateway(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
				    स्थिर काष्ठा fib6_info *rt)
अणु
	वापस rt->fib6_nh->fib_nh_gw_family ||
	       mlxsw_sp_nexthop6_ipip_type(mlxsw_sp, rt, शून्य);
पूर्ण

अटल पूर्णांक
mlxsw_sp_nexthop6_group_info_init(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_nexthop_group *nh_grp,
				  काष्ठा mlxsw_sp_fib6_entry *fib6_entry)
अणु
	काष्ठा mlxsw_sp_nexthop_group_info *nhgi;
	काष्ठा mlxsw_sp_rt6 *mlxsw_sp_rt6;
	काष्ठा mlxsw_sp_nexthop *nh;
	पूर्णांक err, i;

	nhgi = kzalloc(काष्ठा_size(nhgi, nexthops, fib6_entry->nrt6),
		       GFP_KERNEL);
	अगर (!nhgi)
		वापस -ENOMEM;
	nh_grp->nhgi = nhgi;
	nhgi->nh_grp = nh_grp;
	mlxsw_sp_rt6 = list_first_entry(&fib6_entry->rt6_list,
					काष्ठा mlxsw_sp_rt6, list);
	nhgi->gateway = mlxsw_sp_rt6_is_gateway(mlxsw_sp, mlxsw_sp_rt6->rt);
	nhgi->count = fib6_entry->nrt6;
	क्रम (i = 0; i < nhgi->count; i++) अणु
		काष्ठा fib6_info *rt = mlxsw_sp_rt6->rt;

		nh = &nhgi->nexthops[i];
		err = mlxsw_sp_nexthop6_init(mlxsw_sp, nh_grp, nh, rt);
		अगर (err)
			जाओ err_nexthop6_init;
		mlxsw_sp_rt6 = list_next_entry(mlxsw_sp_rt6, list);
	पूर्ण
	nh_grp->nhgi = nhgi;
	err = mlxsw_sp_nexthop_group_refresh(mlxsw_sp, nh_grp);
	अगर (err)
		जाओ err_group_refresh;

	वापस 0;

err_group_refresh:
	i = nhgi->count;
err_nexthop6_init:
	क्रम (i--; i >= 0; i--) अणु
		nh = &nhgi->nexthops[i];
		mlxsw_sp_nexthop6_fini(mlxsw_sp, nh);
	पूर्ण
	kमुक्त(nhgi);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_nexthop6_group_info_fini(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_nexthop_group *nh_grp)
अणु
	काष्ठा mlxsw_sp_nexthop_group_info *nhgi = nh_grp->nhgi;
	पूर्णांक i;

	क्रम (i = nhgi->count - 1; i >= 0; i--) अणु
		काष्ठा mlxsw_sp_nexthop *nh = &nhgi->nexthops[i];

		mlxsw_sp_nexthop6_fini(mlxsw_sp, nh);
	पूर्ण
	mlxsw_sp_nexthop_group_refresh(mlxsw_sp, nh_grp);
	WARN_ON_ONCE(nhgi->adj_index_valid);
	kमुक्त(nhgi);
पूर्ण

अटल काष्ठा mlxsw_sp_nexthop_group *
mlxsw_sp_nexthop6_group_create(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_fib6_entry *fib6_entry)
अणु
	काष्ठा mlxsw_sp_nexthop_group *nh_grp;
	पूर्णांक err;

	nh_grp = kzalloc(माप(*nh_grp), GFP_KERNEL);
	अगर (!nh_grp)
		वापस ERR_PTR(-ENOMEM);
	INIT_LIST_HEAD(&nh_grp->vr_list);
	err = rhashtable_init(&nh_grp->vr_ht,
			      &mlxsw_sp_nexthop_group_vr_ht_params);
	अगर (err)
		जाओ err_nexthop_group_vr_ht_init;
	INIT_LIST_HEAD(&nh_grp->fib_list);
	nh_grp->type = MLXSW_SP_NEXTHOP_GROUP_TYPE_IPV6;

	err = mlxsw_sp_nexthop6_group_info_init(mlxsw_sp, nh_grp, fib6_entry);
	अगर (err)
		जाओ err_nexthop_group_info_init;

	err = mlxsw_sp_nexthop_group_insert(mlxsw_sp, nh_grp);
	अगर (err)
		जाओ err_nexthop_group_insert;

	nh_grp->can_destroy = true;

	वापस nh_grp;

err_nexthop_group_insert:
	mlxsw_sp_nexthop6_group_info_fini(mlxsw_sp, nh_grp);
err_nexthop_group_info_init:
	rhashtable_destroy(&nh_grp->vr_ht);
err_nexthop_group_vr_ht_init:
	kमुक्त(nh_grp);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_nexthop6_group_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_nexthop_group *nh_grp)
अणु
	अगर (!nh_grp->can_destroy)
		वापस;
	mlxsw_sp_nexthop_group_हटाओ(mlxsw_sp, nh_grp);
	mlxsw_sp_nexthop6_group_info_fini(mlxsw_sp, nh_grp);
	WARN_ON_ONCE(!list_empty(&nh_grp->vr_list));
	rhashtable_destroy(&nh_grp->vr_ht);
	kमुक्त(nh_grp);
पूर्ण

अटल पूर्णांक mlxsw_sp_nexthop6_group_get(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_fib6_entry *fib6_entry)
अणु
	काष्ठा fib6_info *rt = mlxsw_sp_fib6_entry_rt(fib6_entry);
	काष्ठा mlxsw_sp_nexthop_group *nh_grp;

	अगर (rt->nh) अणु
		nh_grp = mlxsw_sp_nexthop_obj_group_lookup(mlxsw_sp,
							   rt->nh->id);
		अगर (WARN_ON_ONCE(!nh_grp))
			वापस -EINVAL;
		जाओ out;
	पूर्ण

	nh_grp = mlxsw_sp_nexthop6_group_lookup(mlxsw_sp, fib6_entry);
	अगर (!nh_grp) अणु
		nh_grp = mlxsw_sp_nexthop6_group_create(mlxsw_sp, fib6_entry);
		अगर (IS_ERR(nh_grp))
			वापस PTR_ERR(nh_grp);
	पूर्ण

	/* The route and the nexthop are described by the same काष्ठा, so we
	 * need to the update the nexthop offload indication क्रम the new route.
	 */
	__mlxsw_sp_nexthop6_group_offload_refresh(nh_grp, fib6_entry);

out:
	list_add_tail(&fib6_entry->common.nexthop_group_node,
		      &nh_grp->fib_list);
	fib6_entry->common.nh_group = nh_grp;

	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_nexthop6_group_put(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_fib_entry *fib_entry)
अणु
	काष्ठा mlxsw_sp_nexthop_group *nh_grp = fib_entry->nh_group;

	list_del(&fib_entry->nexthop_group_node);
	अगर (!list_empty(&nh_grp->fib_list))
		वापस;

	अगर (nh_grp->type == MLXSW_SP_NEXTHOP_GROUP_TYPE_OBJ) अणु
		mlxsw_sp_nexthop_obj_group_destroy(mlxsw_sp, nh_grp);
		वापस;
	पूर्ण

	mlxsw_sp_nexthop6_group_destroy(mlxsw_sp, nh_grp);
पूर्ण

अटल पूर्णांक mlxsw_sp_nexthop6_group_update(काष्ठा mlxsw_sp *mlxsw_sp,
					  काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
					  काष्ठा mlxsw_sp_fib6_entry *fib6_entry)
अणु
	काष्ठा mlxsw_sp_nexthop_group *old_nh_grp = fib6_entry->common.nh_group;
	काष्ठा mlxsw_sp_fib_node *fib_node = fib6_entry->common.fib_node;
	पूर्णांक err;

	mlxsw_sp_nexthop_group_vr_unlink(old_nh_grp, fib_node->fib);
	fib6_entry->common.nh_group = शून्य;
	list_del(&fib6_entry->common.nexthop_group_node);

	err = mlxsw_sp_nexthop6_group_get(mlxsw_sp, fib6_entry);
	अगर (err)
		जाओ err_nexthop6_group_get;

	err = mlxsw_sp_nexthop_group_vr_link(fib6_entry->common.nh_group,
					     fib_node->fib);
	अगर (err)
		जाओ err_nexthop_group_vr_link;

	/* In हाल this entry is offloaded, then the adjacency index
	 * currently associated with it in the device's table is that
	 * of the old group. Start using the new one instead.
	 */
	err = __mlxsw_sp_fib_entry_update(mlxsw_sp, op_ctx,
					  &fib6_entry->common, false);
	अगर (err)
		जाओ err_fib_entry_update;

	अगर (list_empty(&old_nh_grp->fib_list))
		mlxsw_sp_nexthop6_group_destroy(mlxsw_sp, old_nh_grp);

	वापस 0;

err_fib_entry_update:
	mlxsw_sp_nexthop_group_vr_unlink(fib6_entry->common.nh_group,
					 fib_node->fib);
err_nexthop_group_vr_link:
	mlxsw_sp_nexthop6_group_put(mlxsw_sp, &fib6_entry->common);
err_nexthop6_group_get:
	list_add_tail(&fib6_entry->common.nexthop_group_node,
		      &old_nh_grp->fib_list);
	fib6_entry->common.nh_group = old_nh_grp;
	mlxsw_sp_nexthop_group_vr_link(old_nh_grp, fib_node->fib);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_fib6_entry_nexthop_add(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
				काष्ठा mlxsw_sp_fib6_entry *fib6_entry,
				काष्ठा fib6_info **rt_arr, अचिन्हित पूर्णांक nrt6)
अणु
	काष्ठा mlxsw_sp_rt6 *mlxsw_sp_rt6;
	पूर्णांक err, i;

	क्रम (i = 0; i < nrt6; i++) अणु
		mlxsw_sp_rt6 = mlxsw_sp_rt6_create(rt_arr[i]);
		अगर (IS_ERR(mlxsw_sp_rt6)) अणु
			err = PTR_ERR(mlxsw_sp_rt6);
			जाओ err_rt6_create;
		पूर्ण

		list_add_tail(&mlxsw_sp_rt6->list, &fib6_entry->rt6_list);
		fib6_entry->nrt6++;
	पूर्ण

	err = mlxsw_sp_nexthop6_group_update(mlxsw_sp, op_ctx, fib6_entry);
	अगर (err)
		जाओ err_nexthop6_group_update;

	वापस 0;

err_nexthop6_group_update:
	i = nrt6;
err_rt6_create:
	क्रम (i--; i >= 0; i--) अणु
		fib6_entry->nrt6--;
		mlxsw_sp_rt6 = list_last_entry(&fib6_entry->rt6_list,
					       काष्ठा mlxsw_sp_rt6, list);
		list_del(&mlxsw_sp_rt6->list);
		mlxsw_sp_rt6_destroy(mlxsw_sp_rt6);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_fib6_entry_nexthop_del(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
				काष्ठा mlxsw_sp_fib6_entry *fib6_entry,
				काष्ठा fib6_info **rt_arr, अचिन्हित पूर्णांक nrt6)
अणु
	काष्ठा mlxsw_sp_rt6 *mlxsw_sp_rt6;
	पूर्णांक i;

	क्रम (i = 0; i < nrt6; i++) अणु
		mlxsw_sp_rt6 = mlxsw_sp_fib6_entry_rt_find(fib6_entry,
							   rt_arr[i]);
		अगर (WARN_ON_ONCE(!mlxsw_sp_rt6))
			जारी;

		fib6_entry->nrt6--;
		list_del(&mlxsw_sp_rt6->list);
		mlxsw_sp_rt6_destroy(mlxsw_sp_rt6);
	पूर्ण

	mlxsw_sp_nexthop6_group_update(mlxsw_sp, op_ctx, fib6_entry);
पूर्ण

अटल व्योम mlxsw_sp_fib6_entry_type_set(काष्ठा mlxsw_sp *mlxsw_sp,
					 काष्ठा mlxsw_sp_fib_entry *fib_entry,
					 स्थिर काष्ठा fib6_info *rt)
अणु
	अगर (rt->fib6_flags & (RTF_LOCAL | RTF_ANYCAST))
		fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_TRAP;
	अन्यथा अगर (rt->fib6_type == RTN_BLACKHOLE)
		fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_BLACKHOLE;
	अन्यथा अगर (rt->fib6_flags & RTF_REJECT)
		fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_UNREACHABLE;
	अन्यथा अगर (fib_entry->nh_group->nhgi->gateway)
		fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_REMOTE;
	अन्यथा
		fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_LOCAL;
पूर्ण

अटल व्योम
mlxsw_sp_fib6_entry_rt_destroy_all(काष्ठा mlxsw_sp_fib6_entry *fib6_entry)
अणु
	काष्ठा mlxsw_sp_rt6 *mlxsw_sp_rt6, *पंचांगp;

	list_क्रम_each_entry_safe(mlxsw_sp_rt6, पंचांगp, &fib6_entry->rt6_list,
				 list) अणु
		fib6_entry->nrt6--;
		list_del(&mlxsw_sp_rt6->list);
		mlxsw_sp_rt6_destroy(mlxsw_sp_rt6);
	पूर्ण
पूर्ण

अटल काष्ठा mlxsw_sp_fib6_entry *
mlxsw_sp_fib6_entry_create(काष्ठा mlxsw_sp *mlxsw_sp,
			   काष्ठा mlxsw_sp_fib_node *fib_node,
			   काष्ठा fib6_info **rt_arr, अचिन्हित पूर्णांक nrt6)
अणु
	काष्ठा mlxsw_sp_fib6_entry *fib6_entry;
	काष्ठा mlxsw_sp_fib_entry *fib_entry;
	काष्ठा mlxsw_sp_rt6 *mlxsw_sp_rt6;
	पूर्णांक err, i;

	fib6_entry = kzalloc(माप(*fib6_entry), GFP_KERNEL);
	अगर (!fib6_entry)
		वापस ERR_PTR(-ENOMEM);
	fib_entry = &fib6_entry->common;

	fib_entry->priv = mlxsw_sp_fib_entry_priv_create(fib_node->fib->ll_ops);
	अगर (IS_ERR(fib_entry->priv)) अणु
		err = PTR_ERR(fib_entry->priv);
		जाओ err_fib_entry_priv_create;
	पूर्ण

	INIT_LIST_HEAD(&fib6_entry->rt6_list);

	क्रम (i = 0; i < nrt6; i++) अणु
		mlxsw_sp_rt6 = mlxsw_sp_rt6_create(rt_arr[i]);
		अगर (IS_ERR(mlxsw_sp_rt6)) अणु
			err = PTR_ERR(mlxsw_sp_rt6);
			जाओ err_rt6_create;
		पूर्ण
		list_add_tail(&mlxsw_sp_rt6->list, &fib6_entry->rt6_list);
		fib6_entry->nrt6++;
	पूर्ण

	err = mlxsw_sp_nexthop6_group_get(mlxsw_sp, fib6_entry);
	अगर (err)
		जाओ err_nexthop6_group_get;

	err = mlxsw_sp_nexthop_group_vr_link(fib_entry->nh_group,
					     fib_node->fib);
	अगर (err)
		जाओ err_nexthop_group_vr_link;

	mlxsw_sp_fib6_entry_type_set(mlxsw_sp, fib_entry, rt_arr[0]);

	fib_entry->fib_node = fib_node;

	वापस fib6_entry;

err_nexthop_group_vr_link:
	mlxsw_sp_nexthop6_group_put(mlxsw_sp, fib_entry);
err_nexthop6_group_get:
	i = nrt6;
err_rt6_create:
	क्रम (i--; i >= 0; i--) अणु
		fib6_entry->nrt6--;
		mlxsw_sp_rt6 = list_last_entry(&fib6_entry->rt6_list,
					       काष्ठा mlxsw_sp_rt6, list);
		list_del(&mlxsw_sp_rt6->list);
		mlxsw_sp_rt6_destroy(mlxsw_sp_rt6);
	पूर्ण
	mlxsw_sp_fib_entry_priv_put(fib_entry->priv);
err_fib_entry_priv_create:
	kमुक्त(fib6_entry);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_sp_fib6_entry_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_fib6_entry *fib6_entry)
अणु
	काष्ठा mlxsw_sp_fib_node *fib_node = fib6_entry->common.fib_node;

	mlxsw_sp_nexthop_group_vr_unlink(fib6_entry->common.nh_group,
					 fib_node->fib);
	mlxsw_sp_nexthop6_group_put(mlxsw_sp, &fib6_entry->common);
	mlxsw_sp_fib6_entry_rt_destroy_all(fib6_entry);
	WARN_ON(fib6_entry->nrt6);
	mlxsw_sp_fib_entry_priv_put(fib6_entry->common.priv);
	kमुक्त(fib6_entry);
पूर्ण

अटल काष्ठा mlxsw_sp_fib6_entry *
mlxsw_sp_fib6_entry_lookup(काष्ठा mlxsw_sp *mlxsw_sp,
			   स्थिर काष्ठा fib6_info *rt)
अणु
	काष्ठा mlxsw_sp_fib6_entry *fib6_entry;
	काष्ठा mlxsw_sp_fib_node *fib_node;
	काष्ठा mlxsw_sp_fib *fib;
	काष्ठा fib6_info *cmp_rt;
	काष्ठा mlxsw_sp_vr *vr;

	vr = mlxsw_sp_vr_find(mlxsw_sp, rt->fib6_table->tb6_id);
	अगर (!vr)
		वापस शून्य;
	fib = mlxsw_sp_vr_fib(vr, MLXSW_SP_L3_PROTO_IPV6);

	fib_node = mlxsw_sp_fib_node_lookup(fib, &rt->fib6_dst.addr,
					    माप(rt->fib6_dst.addr),
					    rt->fib6_dst.plen);
	अगर (!fib_node)
		वापस शून्य;

	fib6_entry = container_of(fib_node->fib_entry,
				  काष्ठा mlxsw_sp_fib6_entry, common);
	cmp_rt = mlxsw_sp_fib6_entry_rt(fib6_entry);
	अगर (rt->fib6_table->tb6_id == cmp_rt->fib6_table->tb6_id &&
	    rt->fib6_metric == cmp_rt->fib6_metric &&
	    mlxsw_sp_fib6_entry_rt_find(fib6_entry, rt))
		वापस fib6_entry;

	वापस शून्य;
पूर्ण

अटल bool mlxsw_sp_fib6_allow_replace(काष्ठा mlxsw_sp_fib6_entry *fib6_entry)
अणु
	काष्ठा mlxsw_sp_fib_node *fib_node = fib6_entry->common.fib_node;
	काष्ठा mlxsw_sp_fib6_entry *fib6_replaced;
	काष्ठा fib6_info *rt, *rt_replaced;

	अगर (!fib_node->fib_entry)
		वापस true;

	fib6_replaced = container_of(fib_node->fib_entry,
				     काष्ठा mlxsw_sp_fib6_entry,
				     common);
	rt = mlxsw_sp_fib6_entry_rt(fib6_entry);
	rt_replaced = mlxsw_sp_fib6_entry_rt(fib6_replaced);
	अगर (rt->fib6_table->tb6_id == RT_TABLE_MAIN &&
	    rt_replaced->fib6_table->tb6_id == RT_TABLE_LOCAL)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक mlxsw_sp_router_fib6_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
					काष्ठा fib6_info **rt_arr, अचिन्हित पूर्णांक nrt6)
अणु
	काष्ठा mlxsw_sp_fib6_entry *fib6_entry, *fib6_replaced;
	काष्ठा mlxsw_sp_fib_entry *replaced;
	काष्ठा mlxsw_sp_fib_node *fib_node;
	काष्ठा fib6_info *rt = rt_arr[0];
	पूर्णांक err;

	अगर (mlxsw_sp->router->पातed)
		वापस 0;

	अगर (rt->fib6_src.plen)
		वापस -EINVAL;

	अगर (mlxsw_sp_fib6_rt_should_ignore(rt))
		वापस 0;

	अगर (rt->nh && !mlxsw_sp_nexthop_obj_group_lookup(mlxsw_sp, rt->nh->id))
		वापस 0;

	fib_node = mlxsw_sp_fib_node_get(mlxsw_sp, rt->fib6_table->tb6_id,
					 &rt->fib6_dst.addr,
					 माप(rt->fib6_dst.addr),
					 rt->fib6_dst.plen,
					 MLXSW_SP_L3_PROTO_IPV6);
	अगर (IS_ERR(fib_node))
		वापस PTR_ERR(fib_node);

	fib6_entry = mlxsw_sp_fib6_entry_create(mlxsw_sp, fib_node, rt_arr,
						nrt6);
	अगर (IS_ERR(fib6_entry)) अणु
		err = PTR_ERR(fib6_entry);
		जाओ err_fib6_entry_create;
	पूर्ण

	अगर (!mlxsw_sp_fib6_allow_replace(fib6_entry)) अणु
		mlxsw_sp_fib6_entry_destroy(mlxsw_sp, fib6_entry);
		mlxsw_sp_fib_node_put(mlxsw_sp, fib_node);
		वापस 0;
	पूर्ण

	replaced = fib_node->fib_entry;
	err = mlxsw_sp_fib_node_entry_link(mlxsw_sp, op_ctx, &fib6_entry->common);
	अगर (err)
		जाओ err_fib_node_entry_link;

	/* Nothing to replace */
	अगर (!replaced)
		वापस 0;

	mlxsw_sp_fib_entry_hw_flags_clear(mlxsw_sp, replaced);
	fib6_replaced = container_of(replaced, काष्ठा mlxsw_sp_fib6_entry,
				     common);
	mlxsw_sp_fib6_entry_destroy(mlxsw_sp, fib6_replaced);

	वापस 0;

err_fib_node_entry_link:
	fib_node->fib_entry = replaced;
	mlxsw_sp_fib6_entry_destroy(mlxsw_sp, fib6_entry);
err_fib6_entry_create:
	mlxsw_sp_fib_node_put(mlxsw_sp, fib_node);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_router_fib6_append(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
				       काष्ठा fib6_info **rt_arr, अचिन्हित पूर्णांक nrt6)
अणु
	काष्ठा mlxsw_sp_fib6_entry *fib6_entry;
	काष्ठा mlxsw_sp_fib_node *fib_node;
	काष्ठा fib6_info *rt = rt_arr[0];
	पूर्णांक err;

	अगर (mlxsw_sp->router->पातed)
		वापस 0;

	अगर (rt->fib6_src.plen)
		वापस -EINVAL;

	अगर (mlxsw_sp_fib6_rt_should_ignore(rt))
		वापस 0;

	fib_node = mlxsw_sp_fib_node_get(mlxsw_sp, rt->fib6_table->tb6_id,
					 &rt->fib6_dst.addr,
					 माप(rt->fib6_dst.addr),
					 rt->fib6_dst.plen,
					 MLXSW_SP_L3_PROTO_IPV6);
	अगर (IS_ERR(fib_node))
		वापस PTR_ERR(fib_node);

	अगर (WARN_ON_ONCE(!fib_node->fib_entry)) अणु
		mlxsw_sp_fib_node_put(mlxsw_sp, fib_node);
		वापस -EINVAL;
	पूर्ण

	fib6_entry = container_of(fib_node->fib_entry,
				  काष्ठा mlxsw_sp_fib6_entry, common);
	err = mlxsw_sp_fib6_entry_nexthop_add(mlxsw_sp, op_ctx, fib6_entry, rt_arr, nrt6);
	अगर (err)
		जाओ err_fib6_entry_nexthop_add;

	वापस 0;

err_fib6_entry_nexthop_add:
	mlxsw_sp_fib_node_put(mlxsw_sp, fib_node);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_router_fib6_del(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
				    काष्ठा fib6_info **rt_arr, अचिन्हित पूर्णांक nrt6)
अणु
	काष्ठा mlxsw_sp_fib6_entry *fib6_entry;
	काष्ठा mlxsw_sp_fib_node *fib_node;
	काष्ठा fib6_info *rt = rt_arr[0];
	पूर्णांक err;

	अगर (mlxsw_sp->router->पातed)
		वापस 0;

	अगर (mlxsw_sp_fib6_rt_should_ignore(rt))
		वापस 0;

	/* Multipath routes are first added to the FIB trie and only then
	 * notअगरied. If we vetoed the addition, we will get a delete
	 * notअगरication क्रम a route we करो not have. Thereक्रमe, करो not warn अगर
	 * route was not found.
	 */
	fib6_entry = mlxsw_sp_fib6_entry_lookup(mlxsw_sp, rt);
	अगर (!fib6_entry)
		वापस 0;

	/* If not all the nexthops are deleted, then only reduce the nexthop
	 * group.
	 */
	अगर (nrt6 != fib6_entry->nrt6) अणु
		mlxsw_sp_fib6_entry_nexthop_del(mlxsw_sp, op_ctx, fib6_entry, rt_arr, nrt6);
		वापस 0;
	पूर्ण

	fib_node = fib6_entry->common.fib_node;

	err = __mlxsw_sp_fib_node_entry_unlink(mlxsw_sp, op_ctx, &fib6_entry->common);
	mlxsw_sp_fib6_entry_destroy(mlxsw_sp, fib6_entry);
	mlxsw_sp_fib_node_put(mlxsw_sp, fib_node);
	वापस err;
पूर्ण

अटल पूर्णांक __mlxsw_sp_router_set_पात_trap(काष्ठा mlxsw_sp *mlxsw_sp,
					    क्रमागत mlxsw_sp_l3proto proto,
					    u8 tree_id)
अणु
	स्थिर काष्ठा mlxsw_sp_router_ll_ops *ll_ops = mlxsw_sp->router->proto_ll_ops[proto];
	क्रमागत mlxsw_reg_ralxx_protocol ralxx_proto =
				(क्रमागत mlxsw_reg_ralxx_protocol) proto;
	काष्ठा mlxsw_sp_fib_entry_priv *priv;
	अक्षर xralta_pl[MLXSW_REG_XRALTA_LEN];
	अक्षर xralst_pl[MLXSW_REG_XRALST_LEN];
	पूर्णांक i, err;

	mlxsw_reg_xralta_pack(xralta_pl, true, ralxx_proto, tree_id);
	err = ll_ops->ralta_ग_लिखो(mlxsw_sp, xralta_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_xralst_pack(xralst_pl, 0xff, tree_id);
	err = ll_ops->ralst_ग_लिखो(mlxsw_sp, xralst_pl);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_VRS); i++) अणु
		काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx = mlxsw_sp->router->ll_op_ctx;
		काष्ठा mlxsw_sp_vr *vr = &mlxsw_sp->router->vrs[i];
		अक्षर xraltb_pl[MLXSW_REG_XRALTB_LEN];

		mlxsw_sp_fib_entry_op_ctx_clear(op_ctx);
		mlxsw_reg_xraltb_pack(xraltb_pl, vr->id, ralxx_proto, tree_id);
		err = ll_ops->raltb_ग_लिखो(mlxsw_sp, xraltb_pl);
		अगर (err)
			वापस err;

		priv = mlxsw_sp_fib_entry_priv_create(ll_ops);
		अगर (IS_ERR(priv))
			वापस PTR_ERR(priv);

		ll_ops->fib_entry_pack(op_ctx, proto, MLXSW_SP_FIB_ENTRY_OP_WRITE,
				       vr->id, 0, शून्य, priv);
		ll_ops->fib_entry_act_ip2me_pack(op_ctx);
		err = ll_ops->fib_entry_commit(mlxsw_sp, op_ctx, शून्य);
		mlxsw_sp_fib_entry_priv_put(priv);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा mlxsw_sp_mr_table *
mlxsw_sp_router_fibmr_family_to_table(काष्ठा mlxsw_sp_vr *vr, पूर्णांक family)
अणु
	अगर (family == RTNL_FAMILY_IPMR)
		वापस vr->mr_table[MLXSW_SP_L3_PROTO_IPV4];
	अन्यथा
		वापस vr->mr_table[MLXSW_SP_L3_PROTO_IPV6];
पूर्ण

अटल पूर्णांक mlxsw_sp_router_fibmr_add(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mfc_entry_notअगरier_info *men_info,
				     bool replace)
अणु
	काष्ठा mlxsw_sp_mr_table *mrt;
	काष्ठा mlxsw_sp_vr *vr;

	अगर (mlxsw_sp->router->पातed)
		वापस 0;

	vr = mlxsw_sp_vr_get(mlxsw_sp, men_info->tb_id, शून्य);
	अगर (IS_ERR(vr))
		वापस PTR_ERR(vr);

	mrt = mlxsw_sp_router_fibmr_family_to_table(vr, men_info->info.family);
	वापस mlxsw_sp_mr_route_add(mrt, men_info->mfc, replace);
पूर्ण

अटल व्योम mlxsw_sp_router_fibmr_del(काष्ठा mlxsw_sp *mlxsw_sp,
				      काष्ठा mfc_entry_notअगरier_info *men_info)
अणु
	काष्ठा mlxsw_sp_mr_table *mrt;
	काष्ठा mlxsw_sp_vr *vr;

	अगर (mlxsw_sp->router->पातed)
		वापस;

	vr = mlxsw_sp_vr_find(mlxsw_sp, men_info->tb_id);
	अगर (WARN_ON(!vr))
		वापस;

	mrt = mlxsw_sp_router_fibmr_family_to_table(vr, men_info->info.family);
	mlxsw_sp_mr_route_del(mrt, men_info->mfc);
	mlxsw_sp_vr_put(mlxsw_sp, vr);
पूर्ण

अटल पूर्णांक
mlxsw_sp_router_fibmr_vअगर_add(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा vअगर_entry_notअगरier_info *ven_info)
अणु
	काष्ठा mlxsw_sp_mr_table *mrt;
	काष्ठा mlxsw_sp_rअगर *rअगर;
	काष्ठा mlxsw_sp_vr *vr;

	अगर (mlxsw_sp->router->पातed)
		वापस 0;

	vr = mlxsw_sp_vr_get(mlxsw_sp, ven_info->tb_id, शून्य);
	अगर (IS_ERR(vr))
		वापस PTR_ERR(vr);

	mrt = mlxsw_sp_router_fibmr_family_to_table(vr, ven_info->info.family);
	rअगर = mlxsw_sp_rअगर_find_by_dev(mlxsw_sp, ven_info->dev);
	वापस mlxsw_sp_mr_vअगर_add(mrt, ven_info->dev,
				   ven_info->vअगर_index,
				   ven_info->vअगर_flags, rअगर);
पूर्ण

अटल व्योम
mlxsw_sp_router_fibmr_vअगर_del(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा vअगर_entry_notअगरier_info *ven_info)
अणु
	काष्ठा mlxsw_sp_mr_table *mrt;
	काष्ठा mlxsw_sp_vr *vr;

	अगर (mlxsw_sp->router->पातed)
		वापस;

	vr = mlxsw_sp_vr_find(mlxsw_sp, ven_info->tb_id);
	अगर (WARN_ON(!vr))
		वापस;

	mrt = mlxsw_sp_router_fibmr_family_to_table(vr, ven_info->info.family);
	mlxsw_sp_mr_vअगर_del(mrt, ven_info->vअगर_index);
	mlxsw_sp_vr_put(mlxsw_sp, vr);
पूर्ण

अटल पूर्णांक mlxsw_sp_router_set_पात_trap(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	क्रमागत mlxsw_sp_l3proto proto = MLXSW_SP_L3_PROTO_IPV4;
	पूर्णांक err;

	err = __mlxsw_sp_router_set_पात_trap(mlxsw_sp, proto,
					       MLXSW_SP_LPM_TREE_MIN);
	अगर (err)
		वापस err;

	/* The multicast router code करोes not need an पात trap as by शेष,
	 * packets that करोn't match any routes are trapped to the CPU.
	 */

	proto = MLXSW_SP_L3_PROTO_IPV6;
	वापस __mlxsw_sp_router_set_पात_trap(mlxsw_sp, proto,
						MLXSW_SP_LPM_TREE_MIN + 1);
पूर्ण

अटल व्योम mlxsw_sp_fib4_node_flush(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_fib_node *fib_node)
अणु
	काष्ठा mlxsw_sp_fib4_entry *fib4_entry;

	fib4_entry = container_of(fib_node->fib_entry,
				  काष्ठा mlxsw_sp_fib4_entry, common);
	mlxsw_sp_fib_node_entry_unlink(mlxsw_sp, fib_node->fib_entry);
	mlxsw_sp_fib4_entry_destroy(mlxsw_sp, fib4_entry);
	mlxsw_sp_fib_node_put(mlxsw_sp, fib_node);
पूर्ण

अटल व्योम mlxsw_sp_fib6_node_flush(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_fib_node *fib_node)
अणु
	काष्ठा mlxsw_sp_fib6_entry *fib6_entry;

	fib6_entry = container_of(fib_node->fib_entry,
				  काष्ठा mlxsw_sp_fib6_entry, common);
	mlxsw_sp_fib_node_entry_unlink(mlxsw_sp, fib_node->fib_entry);
	mlxsw_sp_fib6_entry_destroy(mlxsw_sp, fib6_entry);
	mlxsw_sp_fib_node_put(mlxsw_sp, fib_node);
पूर्ण

अटल व्योम mlxsw_sp_fib_node_flush(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_fib_node *fib_node)
अणु
	चयन (fib_node->fib->proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		mlxsw_sp_fib4_node_flush(mlxsw_sp, fib_node);
		अवरोध;
	हाल MLXSW_SP_L3_PROTO_IPV6:
		mlxsw_sp_fib6_node_flush(mlxsw_sp, fib_node);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp_vr_fib_flush(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_vr *vr,
				  क्रमागत mlxsw_sp_l3proto proto)
अणु
	काष्ठा mlxsw_sp_fib *fib = mlxsw_sp_vr_fib(vr, proto);
	काष्ठा mlxsw_sp_fib_node *fib_node, *पंचांगp;

	list_क्रम_each_entry_safe(fib_node, पंचांगp, &fib->node_list, list) अणु
		bool करो_अवरोध = &पंचांगp->list == &fib->node_list;

		mlxsw_sp_fib_node_flush(mlxsw_sp, fib_node);
		अगर (करो_अवरोध)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp_router_fib_flush(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_VRS); i++) अणु
		काष्ठा mlxsw_sp_vr *vr = &mlxsw_sp->router->vrs[i];

		अगर (!mlxsw_sp_vr_is_used(vr))
			जारी;

		क्रम (j = 0; j < MLXSW_SP_L3_PROTO_MAX; j++)
			mlxsw_sp_mr_table_flush(vr->mr_table[j]);
		mlxsw_sp_vr_fib_flush(mlxsw_sp, vr, MLXSW_SP_L3_PROTO_IPV4);

		/* If भव router was only used क्रम IPv4, then it's no
		 * दीर्घer used.
		 */
		अगर (!mlxsw_sp_vr_is_used(vr))
			जारी;
		mlxsw_sp_vr_fib_flush(mlxsw_sp, vr, MLXSW_SP_L3_PROTO_IPV6);
	पूर्ण

	/* After flushing all the routes, it is not possible anyone is still
	 * using the adjacency index that is discarding packets, so मुक्त it in
	 * हाल it was allocated.
	 */
	अगर (!mlxsw_sp->router->adj_discard_index_valid)
		वापस;
	mlxsw_sp_kvdl_मुक्त(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ, 1,
			   mlxsw_sp->router->adj_discard_index);
	mlxsw_sp->router->adj_discard_index_valid = false;
पूर्ण

अटल व्योम mlxsw_sp_router_fib_पात(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	पूर्णांक err;

	अगर (mlxsw_sp->router->पातed)
		वापस;
	dev_warn(mlxsw_sp->bus_info->dev, "FIB abort triggered. Note that FIB entries are no longer being offloaded to this device.\n");
	mlxsw_sp_router_fib_flush(mlxsw_sp);
	mlxsw_sp->router->पातed = true;
	err = mlxsw_sp_router_set_पात_trap(mlxsw_sp);
	अगर (err)
		dev_warn(mlxsw_sp->bus_info->dev, "Failed to set abort trap.\n");
पूर्ण

काष्ठा mlxsw_sp_fib6_event अणु
	काष्ठा fib6_info **rt_arr;
	अचिन्हित पूर्णांक nrt6;
पूर्ण;

काष्ठा mlxsw_sp_fib_event अणु
	काष्ठा list_head list; /* node in fib queue */
	जोड़ अणु
		काष्ठा mlxsw_sp_fib6_event fib6_event;
		काष्ठा fib_entry_notअगरier_info fen_info;
		काष्ठा fib_rule_notअगरier_info fr_info;
		काष्ठा fib_nh_notअगरier_info fnh_info;
		काष्ठा mfc_entry_notअगरier_info men_info;
		काष्ठा vअगर_entry_notअगरier_info ven_info;
	पूर्ण;
	काष्ठा mlxsw_sp *mlxsw_sp;
	अचिन्हित दीर्घ event;
	पूर्णांक family;
पूर्ण;

अटल पूर्णांक
mlxsw_sp_router_fib6_event_init(काष्ठा mlxsw_sp_fib6_event *fib6_event,
				काष्ठा fib6_entry_notअगरier_info *fen6_info)
अणु
	काष्ठा fib6_info *rt = fen6_info->rt;
	काष्ठा fib6_info **rt_arr;
	काष्ठा fib6_info *iter;
	अचिन्हित पूर्णांक nrt6;
	पूर्णांक i = 0;

	nrt6 = fen6_info->nsiblings + 1;

	rt_arr = kसुस्मृति(nrt6, माप(काष्ठा fib6_info *), GFP_ATOMIC);
	अगर (!rt_arr)
		वापस -ENOMEM;

	fib6_event->rt_arr = rt_arr;
	fib6_event->nrt6 = nrt6;

	rt_arr[0] = rt;
	fib6_info_hold(rt);

	अगर (!fen6_info->nsiblings)
		वापस 0;

	list_क्रम_each_entry(iter, &rt->fib6_siblings, fib6_siblings) अणु
		अगर (i == fen6_info->nsiblings)
			अवरोध;

		rt_arr[i + 1] = iter;
		fib6_info_hold(iter);
		i++;
	पूर्ण
	WARN_ON_ONCE(i != fen6_info->nsiblings);

	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_router_fib6_event_fini(काष्ठा mlxsw_sp_fib6_event *fib6_event)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < fib6_event->nrt6; i++)
		mlxsw_sp_rt6_release(fib6_event->rt_arr[i]);
	kमुक्त(fib6_event->rt_arr);
पूर्ण

अटल व्योम mlxsw_sp_router_fib4_event_process(काष्ठा mlxsw_sp *mlxsw_sp,
					       काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
					       काष्ठा mlxsw_sp_fib_event *fib_event)
अणु
	पूर्णांक err;

	mlxsw_sp_span_respin(mlxsw_sp);

	चयन (fib_event->event) अणु
	हाल FIB_EVENT_ENTRY_REPLACE:
		err = mlxsw_sp_router_fib4_replace(mlxsw_sp, op_ctx, &fib_event->fen_info);
		अगर (err) अणु
			mlxsw_sp_fib_entry_op_ctx_priv_put_all(op_ctx);
			mlxsw_sp_router_fib_पात(mlxsw_sp);
			mlxsw_sp_fib4_offload_failed_flag_set(mlxsw_sp,
							      &fib_event->fen_info);
		पूर्ण
		fib_info_put(fib_event->fen_info.fi);
		अवरोध;
	हाल FIB_EVENT_ENTRY_DEL:
		err = mlxsw_sp_router_fib4_del(mlxsw_sp, op_ctx, &fib_event->fen_info);
		अगर (err)
			mlxsw_sp_fib_entry_op_ctx_priv_put_all(op_ctx);
		fib_info_put(fib_event->fen_info.fi);
		अवरोध;
	हाल FIB_EVENT_NH_ADD:
	हाल FIB_EVENT_NH_DEL:
		mlxsw_sp_nexthop4_event(mlxsw_sp, fib_event->event, fib_event->fnh_info.fib_nh);
		fib_info_put(fib_event->fnh_info.fib_nh->nh_parent);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp_router_fib6_event_process(काष्ठा mlxsw_sp *mlxsw_sp,
					       काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
					       काष्ठा mlxsw_sp_fib_event *fib_event)
अणु
	काष्ठा mlxsw_sp_fib6_event *fib6_event = &fib_event->fib6_event;
	पूर्णांक err;

	mlxsw_sp_span_respin(mlxsw_sp);

	चयन (fib_event->event) अणु
	हाल FIB_EVENT_ENTRY_REPLACE:
		err = mlxsw_sp_router_fib6_replace(mlxsw_sp, op_ctx, fib_event->fib6_event.rt_arr,
						   fib_event->fib6_event.nrt6);
		अगर (err) अणु
			mlxsw_sp_fib_entry_op_ctx_priv_put_all(op_ctx);
			mlxsw_sp_router_fib_पात(mlxsw_sp);
			mlxsw_sp_fib6_offload_failed_flag_set(mlxsw_sp,
							      fib6_event->rt_arr,
							      fib6_event->nrt6);
		पूर्ण
		mlxsw_sp_router_fib6_event_fini(&fib_event->fib6_event);
		अवरोध;
	हाल FIB_EVENT_ENTRY_APPEND:
		err = mlxsw_sp_router_fib6_append(mlxsw_sp, op_ctx, fib_event->fib6_event.rt_arr,
						  fib_event->fib6_event.nrt6);
		अगर (err) अणु
			mlxsw_sp_fib_entry_op_ctx_priv_put_all(op_ctx);
			mlxsw_sp_router_fib_पात(mlxsw_sp);
			mlxsw_sp_fib6_offload_failed_flag_set(mlxsw_sp,
							      fib6_event->rt_arr,
							      fib6_event->nrt6);
		पूर्ण
		mlxsw_sp_router_fib6_event_fini(&fib_event->fib6_event);
		अवरोध;
	हाल FIB_EVENT_ENTRY_DEL:
		err = mlxsw_sp_router_fib6_del(mlxsw_sp, op_ctx, fib_event->fib6_event.rt_arr,
					       fib_event->fib6_event.nrt6);
		अगर (err)
			mlxsw_sp_fib_entry_op_ctx_priv_put_all(op_ctx);
		mlxsw_sp_router_fib6_event_fini(&fib_event->fib6_event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp_router_fibmr_event_process(काष्ठा mlxsw_sp *mlxsw_sp,
						काष्ठा mlxsw_sp_fib_event *fib_event)
अणु
	bool replace;
	पूर्णांक err;

	rtnl_lock();
	mutex_lock(&mlxsw_sp->router->lock);
	चयन (fib_event->event) अणु
	हाल FIB_EVENT_ENTRY_REPLACE:
	हाल FIB_EVENT_ENTRY_ADD:
		replace = fib_event->event == FIB_EVENT_ENTRY_REPLACE;

		err = mlxsw_sp_router_fibmr_add(mlxsw_sp, &fib_event->men_info, replace);
		अगर (err)
			mlxsw_sp_router_fib_पात(mlxsw_sp);
		mr_cache_put(fib_event->men_info.mfc);
		अवरोध;
	हाल FIB_EVENT_ENTRY_DEL:
		mlxsw_sp_router_fibmr_del(mlxsw_sp, &fib_event->men_info);
		mr_cache_put(fib_event->men_info.mfc);
		अवरोध;
	हाल FIB_EVENT_VIF_ADD:
		err = mlxsw_sp_router_fibmr_vअगर_add(mlxsw_sp,
						    &fib_event->ven_info);
		अगर (err)
			mlxsw_sp_router_fib_पात(mlxsw_sp);
		dev_put(fib_event->ven_info.dev);
		अवरोध;
	हाल FIB_EVENT_VIF_DEL:
		mlxsw_sp_router_fibmr_vअगर_del(mlxsw_sp, &fib_event->ven_info);
		dev_put(fib_event->ven_info.dev);
		अवरोध;
	पूर्ण
	mutex_unlock(&mlxsw_sp->router->lock);
	rtnl_unlock();
पूर्ण

अटल व्योम mlxsw_sp_router_fib_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_sp_router *router = container_of(work, काष्ठा mlxsw_sp_router, fib_event_work);
	काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx = router->ll_op_ctx;
	काष्ठा mlxsw_sp *mlxsw_sp = router->mlxsw_sp;
	काष्ठा mlxsw_sp_fib_event *next_fib_event;
	काष्ठा mlxsw_sp_fib_event *fib_event;
	पूर्णांक last_family = AF_UNSPEC;
	LIST_HEAD(fib_event_queue);

	spin_lock_bh(&router->fib_event_queue_lock);
	list_splice_init(&router->fib_event_queue, &fib_event_queue);
	spin_unlock_bh(&router->fib_event_queue_lock);

	/* Router lock is held here to make sure per-instance
	 * operation context is not used in between FIB4/6 events
	 * processing.
	 */
	mutex_lock(&router->lock);
	mlxsw_sp_fib_entry_op_ctx_clear(op_ctx);
	list_क्रम_each_entry_safe(fib_event, next_fib_event,
				 &fib_event_queue, list) अणु
		/* Check अगर the next entry in the queue exists and it is
		 * of the same type (family and event) as the currect one.
		 * In that हाल it is permitted to करो the bulking
		 * of multiple FIB entries to a single रेजिस्टर ग_लिखो.
		 */
		op_ctx->bulk_ok = !list_is_last(&fib_event->list, &fib_event_queue) &&
				  fib_event->family == next_fib_event->family &&
				  fib_event->event == next_fib_event->event;
		op_ctx->event = fib_event->event;

		/* In हाल family of this and the previous entry are dअगरferent, context
		 * reinitialization is going to be needed now, indicate that.
		 * Note that since last_family is initialized to AF_UNSPEC, this is always
		 * going to happen क्रम the first entry processed in the work.
		 */
		अगर (fib_event->family != last_family)
			op_ctx->initialized = false;

		चयन (fib_event->family) अणु
		हाल AF_INET:
			mlxsw_sp_router_fib4_event_process(mlxsw_sp, op_ctx,
							   fib_event);
			अवरोध;
		हाल AF_INET6:
			mlxsw_sp_router_fib6_event_process(mlxsw_sp, op_ctx,
							   fib_event);
			अवरोध;
		हाल RTNL_FAMILY_IP6MR:
		हाल RTNL_FAMILY_IPMR:
			/* Unlock here as inside FIBMR the lock is taken again
			 * under RTNL. The per-instance operation context
			 * is not used by FIBMR.
			 */
			mutex_unlock(&router->lock);
			mlxsw_sp_router_fibmr_event_process(mlxsw_sp,
							    fib_event);
			mutex_lock(&router->lock);
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
		पूर्ण
		last_family = fib_event->family;
		kमुक्त(fib_event);
		cond_resched();
	पूर्ण
	WARN_ON_ONCE(!list_empty(&router->ll_op_ctx->fib_entry_priv_list));
	mutex_unlock(&router->lock);
पूर्ण

अटल व्योम mlxsw_sp_router_fib4_event(काष्ठा mlxsw_sp_fib_event *fib_event,
				       काष्ठा fib_notअगरier_info *info)
अणु
	काष्ठा fib_entry_notअगरier_info *fen_info;
	काष्ठा fib_nh_notअगरier_info *fnh_info;

	चयन (fib_event->event) अणु
	हाल FIB_EVENT_ENTRY_REPLACE:
	हाल FIB_EVENT_ENTRY_DEL:
		fen_info = container_of(info, काष्ठा fib_entry_notअगरier_info,
					info);
		fib_event->fen_info = *fen_info;
		/* Take reference on fib_info to prevent it from being
		 * मुक्तd जबतक event is queued. Release it afterwards.
		 */
		fib_info_hold(fib_event->fen_info.fi);
		अवरोध;
	हाल FIB_EVENT_NH_ADD:
	हाल FIB_EVENT_NH_DEL:
		fnh_info = container_of(info, काष्ठा fib_nh_notअगरier_info,
					info);
		fib_event->fnh_info = *fnh_info;
		fib_info_hold(fib_event->fnh_info.fib_nh->nh_parent);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_router_fib6_event(काष्ठा mlxsw_sp_fib_event *fib_event,
				      काष्ठा fib_notअगरier_info *info)
अणु
	काष्ठा fib6_entry_notअगरier_info *fen6_info;
	पूर्णांक err;

	चयन (fib_event->event) अणु
	हाल FIB_EVENT_ENTRY_REPLACE:
	हाल FIB_EVENT_ENTRY_APPEND:
	हाल FIB_EVENT_ENTRY_DEL:
		fen6_info = container_of(info, काष्ठा fib6_entry_notअगरier_info,
					 info);
		err = mlxsw_sp_router_fib6_event_init(&fib_event->fib6_event,
						      fen6_info);
		अगर (err)
			वापस err;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_router_fibmr_event(काष्ठा mlxsw_sp_fib_event *fib_event,
			    काष्ठा fib_notअगरier_info *info)
अणु
	चयन (fib_event->event) अणु
	हाल FIB_EVENT_ENTRY_REPLACE:
	हाल FIB_EVENT_ENTRY_ADD:
	हाल FIB_EVENT_ENTRY_DEL:
		स_नकल(&fib_event->men_info, info, माप(fib_event->men_info));
		mr_cache_hold(fib_event->men_info.mfc);
		अवरोध;
	हाल FIB_EVENT_VIF_ADD:
	हाल FIB_EVENT_VIF_DEL:
		स_नकल(&fib_event->ven_info, info, माप(fib_event->ven_info));
		dev_hold(fib_event->ven_info.dev);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_router_fib_rule_event(अचिन्हित दीर्घ event,
					  काष्ठा fib_notअगरier_info *info,
					  काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा netlink_ext_ack *extack = info->extack;
	काष्ठा fib_rule_notअगरier_info *fr_info;
	काष्ठा fib_rule *rule;
	पूर्णांक err = 0;

	/* nothing to करो at the moment */
	अगर (event == FIB_EVENT_RULE_DEL)
		वापस 0;

	अगर (mlxsw_sp->router->पातed)
		वापस 0;

	fr_info = container_of(info, काष्ठा fib_rule_notअगरier_info, info);
	rule = fr_info->rule;

	/* Rule only affects locally generated traffic */
	अगर (rule->iअगरindex == mlxsw_sp_net(mlxsw_sp)->loopback_dev->अगरindex)
		वापस 0;

	चयन (info->family) अणु
	हाल AF_INET:
		अगर (!fib4_rule_शेष(rule) && !rule->l3mdev)
			err = -EOPNOTSUPP;
		अवरोध;
	हाल AF_INET6:
		अगर (!fib6_rule_शेष(rule) && !rule->l3mdev)
			err = -EOPNOTSUPP;
		अवरोध;
	हाल RTNL_FAMILY_IPMR:
		अगर (!ipmr_rule_शेष(rule) && !rule->l3mdev)
			err = -EOPNOTSUPP;
		अवरोध;
	हाल RTNL_FAMILY_IP6MR:
		अगर (!ip6mr_rule_शेष(rule) && !rule->l3mdev)
			err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	अगर (err < 0)
		NL_SET_ERR_MSG_MOD(extack, "FIB rules not supported");

	वापस err;
पूर्ण

/* Called with rcu_पढ़ो_lock() */
अटल पूर्णांक mlxsw_sp_router_fib_event(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा mlxsw_sp_fib_event *fib_event;
	काष्ठा fib_notअगरier_info *info = ptr;
	काष्ठा mlxsw_sp_router *router;
	पूर्णांक err;

	अगर ((info->family != AF_INET && info->family != AF_INET6 &&
	     info->family != RTNL_FAMILY_IPMR &&
	     info->family != RTNL_FAMILY_IP6MR))
		वापस NOTIFY_DONE;

	router = container_of(nb, काष्ठा mlxsw_sp_router, fib_nb);

	चयन (event) अणु
	हाल FIB_EVENT_RULE_ADD:
	हाल FIB_EVENT_RULE_DEL:
		err = mlxsw_sp_router_fib_rule_event(event, info,
						     router->mlxsw_sp);
		वापस notअगरier_from_त्रुटि_सं(err);
	हाल FIB_EVENT_ENTRY_ADD:
	हाल FIB_EVENT_ENTRY_REPLACE:
	हाल FIB_EVENT_ENTRY_APPEND:
		अगर (router->पातed) अणु
			NL_SET_ERR_MSG_MOD(info->extack, "FIB offload was aborted. Not configuring route");
			वापस notअगरier_from_त्रुटि_सं(-EINVAL);
		पूर्ण
		अगर (info->family == AF_INET) अणु
			काष्ठा fib_entry_notअगरier_info *fen_info = ptr;

			अगर (fen_info->fi->fib_nh_is_v6) अणु
				NL_SET_ERR_MSG_MOD(info->extack, "IPv6 gateway with IPv4 route is not supported");
				वापस notअगरier_from_त्रुटि_सं(-EINVAL);
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	fib_event = kzalloc(माप(*fib_event), GFP_ATOMIC);
	अगर (!fib_event)
		वापस NOTIFY_BAD;

	fib_event->mlxsw_sp = router->mlxsw_sp;
	fib_event->event = event;
	fib_event->family = info->family;

	चयन (info->family) अणु
	हाल AF_INET:
		mlxsw_sp_router_fib4_event(fib_event, info);
		अवरोध;
	हाल AF_INET6:
		err = mlxsw_sp_router_fib6_event(fib_event, info);
		अगर (err)
			जाओ err_fib_event;
		अवरोध;
	हाल RTNL_FAMILY_IP6MR:
	हाल RTNL_FAMILY_IPMR:
		mlxsw_sp_router_fibmr_event(fib_event, info);
		अवरोध;
	पूर्ण

	/* Enqueue the event and trigger the work */
	spin_lock_bh(&router->fib_event_queue_lock);
	list_add_tail(&fib_event->list, &router->fib_event_queue);
	spin_unlock_bh(&router->fib_event_queue_lock);
	mlxsw_core_schedule_work(&router->fib_event_work);

	वापस NOTIFY_DONE;

err_fib_event:
	kमुक्त(fib_event);
	वापस NOTIFY_BAD;
पूर्ण

अटल काष्ठा mlxsw_sp_rअगर *
mlxsw_sp_rअगर_find_by_dev(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
			 स्थिर काष्ठा net_device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS); i++)
		अगर (mlxsw_sp->router->rअगरs[i] &&
		    mlxsw_sp->router->rअगरs[i]->dev == dev)
			वापस mlxsw_sp->router->rअगरs[i];

	वापस शून्य;
पूर्ण

bool mlxsw_sp_rअगर_exists(काष्ठा mlxsw_sp *mlxsw_sp,
			 स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा mlxsw_sp_rअगर *rअगर;

	mutex_lock(&mlxsw_sp->router->lock);
	rअगर = mlxsw_sp_rअगर_find_by_dev(mlxsw_sp, dev);
	mutex_unlock(&mlxsw_sp->router->lock);

	वापस rअगर;
पूर्ण

u16 mlxsw_sp_rअगर_vid(काष्ठा mlxsw_sp *mlxsw_sp, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा mlxsw_sp_rअगर *rअगर;
	u16 vid = 0;

	mutex_lock(&mlxsw_sp->router->lock);
	rअगर = mlxsw_sp_rअगर_find_by_dev(mlxsw_sp, dev);
	अगर (!rअगर)
		जाओ out;

	/* We only वापस the VID क्रम VLAN RIFs. Otherwise we वापस an
	 * invalid value (0).
	 */
	अगर (rअगर->ops->type != MLXSW_SP_RIF_TYPE_VLAN)
		जाओ out;

	vid = mlxsw_sp_fid_8021q_vid(rअगर->fid);

out:
	mutex_unlock(&mlxsw_sp->router->lock);
	वापस vid;
पूर्ण

अटल पूर्णांक mlxsw_sp_router_rअगर_disable(काष्ठा mlxsw_sp *mlxsw_sp, u16 rअगर)
अणु
	अक्षर ritr_pl[MLXSW_REG_RITR_LEN];
	पूर्णांक err;

	mlxsw_reg_ritr_rअगर_pack(ritr_pl, rअगर);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ritr), ritr_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_ritr_enable_set(ritr_pl, false);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ritr), ritr_pl);
पूर्ण

अटल व्योम mlxsw_sp_router_rअगर_gone_sync(काष्ठा mlxsw_sp *mlxsw_sp,
					  काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	mlxsw_sp_router_rअगर_disable(mlxsw_sp, rअगर->rअगर_index);
	mlxsw_sp_nexthop_rअगर_gone_sync(mlxsw_sp, rअगर);
	mlxsw_sp_neigh_rअगर_gone_sync(mlxsw_sp, rअगर);
पूर्ण

अटल bool
mlxsw_sp_rअगर_should_config(काष्ठा mlxsw_sp_rअगर *rअगर, काष्ठा net_device *dev,
			   अचिन्हित दीर्घ event)
अणु
	काष्ठा inet6_dev *inet6_dev;
	bool addr_list_empty = true;
	काष्ठा in_device *idev;

	चयन (event) अणु
	हाल NETDEV_UP:
		वापस rअगर == शून्य;
	हाल NETDEV_DOWN:
		rcu_पढ़ो_lock();
		idev = __in_dev_get_rcu(dev);
		अगर (idev && idev->अगरa_list)
			addr_list_empty = false;

		inet6_dev = __in6_dev_get(dev);
		अगर (addr_list_empty && inet6_dev &&
		    !list_empty(&inet6_dev->addr_list))
			addr_list_empty = false;
		rcu_पढ़ो_unlock();

		/* macvlans करो not have a RIF, but rather piggy back on the
		 * RIF of their lower device.
		 */
		अगर (netअगर_is_macvlan(dev) && addr_list_empty)
			वापस true;

		अगर (rअगर && addr_list_empty &&
		    !netअगर_is_l3_slave(rअगर->dev))
			वापस true;
		/* It is possible we alपढ़ोy हटाओd the RIF ourselves
		 * अगर it was asचिन्हित to a netdev that is now a bridge
		 * or LAG slave.
		 */
		वापस false;
	पूर्ण

	वापस false;
पूर्ण

अटल क्रमागत mlxsw_sp_rअगर_type
mlxsw_sp_dev_rअगर_type(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
		      स्थिर काष्ठा net_device *dev)
अणु
	क्रमागत mlxsw_sp_fid_type type;

	अगर (mlxsw_sp_netdev_ipip_type(mlxsw_sp, dev, शून्य))
		वापस MLXSW_SP_RIF_TYPE_IPIP_LB;

	/* Otherwise RIF type is derived from the type of the underlying FID. */
	अगर (is_vlan_dev(dev) && netअगर_is_bridge_master(vlan_dev_real_dev(dev)))
		type = MLXSW_SP_FID_TYPE_8021Q;
	अन्यथा अगर (netअगर_is_bridge_master(dev) && br_vlan_enabled(dev))
		type = MLXSW_SP_FID_TYPE_8021Q;
	अन्यथा अगर (netअगर_is_bridge_master(dev))
		type = MLXSW_SP_FID_TYPE_8021D;
	अन्यथा
		type = MLXSW_SP_FID_TYPE_RFID;

	वापस mlxsw_sp_fid_type_rअगर_type(mlxsw_sp, type);
पूर्ण

अटल पूर्णांक mlxsw_sp_rअगर_index_alloc(काष्ठा mlxsw_sp *mlxsw_sp, u16 *p_rअगर_index)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS); i++) अणु
		अगर (!mlxsw_sp->router->rअगरs[i]) अणु
			*p_rअगर_index = i;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOBUFS;
पूर्ण

अटल काष्ठा mlxsw_sp_rअगर *mlxsw_sp_rअगर_alloc(माप_प्रकार rअगर_size, u16 rअगर_index,
					       u16 vr_id,
					       काष्ठा net_device *l3_dev)
अणु
	काष्ठा mlxsw_sp_rअगर *rअगर;

	rअगर = kzalloc(rअगर_size, GFP_KERNEL);
	अगर (!rअगर)
		वापस शून्य;

	INIT_LIST_HEAD(&rअगर->nexthop_list);
	INIT_LIST_HEAD(&rअगर->neigh_list);
	अगर (l3_dev) अणु
		ether_addr_copy(rअगर->addr, l3_dev->dev_addr);
		rअगर->mtu = l3_dev->mtu;
		rअगर->dev = l3_dev;
	पूर्ण
	rअगर->vr_id = vr_id;
	rअगर->rअगर_index = rअगर_index;

	वापस rअगर;
पूर्ण

काष्ठा mlxsw_sp_rअगर *mlxsw_sp_rअगर_by_index(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
					   u16 rअगर_index)
अणु
	वापस mlxsw_sp->router->rअगरs[rअगर_index];
पूर्ण

u16 mlxsw_sp_rअगर_index(स्थिर काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	वापस rअगर->rअगर_index;
पूर्ण

u16 mlxsw_sp_ipip_lb_rअगर_index(स्थिर काष्ठा mlxsw_sp_rअगर_ipip_lb *lb_rअगर)
अणु
	वापस lb_rअगर->common.rअगर_index;
पूर्ण

u16 mlxsw_sp_ipip_lb_ul_vr_id(स्थिर काष्ठा mlxsw_sp_rअगर_ipip_lb *lb_rअगर)
अणु
	u32 ul_tb_id = mlxsw_sp_ipip_dev_ul_tb_id(lb_rअगर->common.dev);
	काष्ठा mlxsw_sp_vr *ul_vr;

	ul_vr = mlxsw_sp_vr_get(lb_rअगर->common.mlxsw_sp, ul_tb_id, शून्य);
	अगर (WARN_ON(IS_ERR(ul_vr)))
		वापस 0;

	वापस ul_vr->id;
पूर्ण

u16 mlxsw_sp_ipip_lb_ul_rअगर_id(स्थिर काष्ठा mlxsw_sp_rअगर_ipip_lb *lb_rअगर)
अणु
	वापस lb_rअगर->ul_rअगर_id;
पूर्ण

पूर्णांक mlxsw_sp_rअगर_dev_अगरindex(स्थिर काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	वापस rअगर->dev->अगरindex;
पूर्ण

स्थिर काष्ठा net_device *mlxsw_sp_rअगर_dev(स्थिर काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	वापस rअगर->dev;
पूर्ण

अटल काष्ठा mlxsw_sp_rअगर *
mlxsw_sp_rअगर_create(काष्ठा mlxsw_sp *mlxsw_sp,
		    स्थिर काष्ठा mlxsw_sp_rअगर_params *params,
		    काष्ठा netlink_ext_ack *extack)
अणु
	u32 tb_id = l3mdev_fib_table(params->dev);
	स्थिर काष्ठा mlxsw_sp_rअगर_ops *ops;
	काष्ठा mlxsw_sp_fid *fid = शून्य;
	क्रमागत mlxsw_sp_rअगर_type type;
	काष्ठा mlxsw_sp_rअगर *rअगर;
	काष्ठा mlxsw_sp_vr *vr;
	u16 rअगर_index;
	पूर्णांक i, err;

	type = mlxsw_sp_dev_rअगर_type(mlxsw_sp, params->dev);
	ops = mlxsw_sp->router->rअगर_ops_arr[type];

	vr = mlxsw_sp_vr_get(mlxsw_sp, tb_id ? : RT_TABLE_MAIN, extack);
	अगर (IS_ERR(vr))
		वापस ERR_CAST(vr);
	vr->rअगर_count++;

	err = mlxsw_sp_rअगर_index_alloc(mlxsw_sp, &rअगर_index);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Exceeded number of supported router interfaces");
		जाओ err_rअगर_index_alloc;
	पूर्ण

	rअगर = mlxsw_sp_rअगर_alloc(ops->rअगर_size, rअगर_index, vr->id, params->dev);
	अगर (!rअगर) अणु
		err = -ENOMEM;
		जाओ err_rअगर_alloc;
	पूर्ण
	dev_hold(rअगर->dev);
	mlxsw_sp->router->rअगरs[rअगर_index] = rअगर;
	rअगर->mlxsw_sp = mlxsw_sp;
	rअगर->ops = ops;

	अगर (ops->fid_get) अणु
		fid = ops->fid_get(rअगर, extack);
		अगर (IS_ERR(fid)) अणु
			err = PTR_ERR(fid);
			जाओ err_fid_get;
		पूर्ण
		rअगर->fid = fid;
	पूर्ण

	अगर (ops->setup)
		ops->setup(rअगर, params);

	err = ops->configure(rअगर);
	अगर (err)
		जाओ err_configure;

	क्रम (i = 0; i < MLXSW_SP_L3_PROTO_MAX; i++) अणु
		err = mlxsw_sp_mr_rअगर_add(vr->mr_table[i], rअगर);
		अगर (err)
			जाओ err_mr_rअगर_add;
	पूर्ण

	mlxsw_sp_rअगर_counters_alloc(rअगर);

	वापस rअगर;

err_mr_rअगर_add:
	क्रम (i--; i >= 0; i--)
		mlxsw_sp_mr_rअगर_del(vr->mr_table[i], rअगर);
	ops->deconfigure(rअगर);
err_configure:
	अगर (fid)
		mlxsw_sp_fid_put(fid);
err_fid_get:
	mlxsw_sp->router->rअगरs[rअगर_index] = शून्य;
	dev_put(rअगर->dev);
	kमुक्त(rअगर);
err_rअगर_alloc:
err_rअगर_index_alloc:
	vr->rअगर_count--;
	mlxsw_sp_vr_put(mlxsw_sp, vr);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_sp_rअगर_destroy(काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	स्थिर काष्ठा mlxsw_sp_rअगर_ops *ops = rअगर->ops;
	काष्ठा mlxsw_sp *mlxsw_sp = rअगर->mlxsw_sp;
	काष्ठा mlxsw_sp_fid *fid = rअगर->fid;
	काष्ठा mlxsw_sp_vr *vr;
	पूर्णांक i;

	mlxsw_sp_router_rअगर_gone_sync(mlxsw_sp, rअगर);
	vr = &mlxsw_sp->router->vrs[rअगर->vr_id];

	mlxsw_sp_rअगर_counters_मुक्त(rअगर);
	क्रम (i = 0; i < MLXSW_SP_L3_PROTO_MAX; i++)
		mlxsw_sp_mr_rअगर_del(vr->mr_table[i], rअगर);
	ops->deconfigure(rअगर);
	अगर (fid)
		/* Loopback RIFs are not associated with a FID. */
		mlxsw_sp_fid_put(fid);
	mlxsw_sp->router->rअगरs[rअगर->rअगर_index] = शून्य;
	dev_put(rअगर->dev);
	kमुक्त(rअगर);
	vr->rअगर_count--;
	mlxsw_sp_vr_put(mlxsw_sp, vr);
पूर्ण

व्योम mlxsw_sp_rअगर_destroy_by_dev(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा net_device *dev)
अणु
	काष्ठा mlxsw_sp_rअगर *rअगर;

	mutex_lock(&mlxsw_sp->router->lock);
	rअगर = mlxsw_sp_rअगर_find_by_dev(mlxsw_sp, dev);
	अगर (!rअगर)
		जाओ out;
	mlxsw_sp_rअगर_destroy(rअगर);
out:
	mutex_unlock(&mlxsw_sp->router->lock);
पूर्ण

अटल व्योम
mlxsw_sp_rअगर_subport_params_init(काष्ठा mlxsw_sp_rअगर_params *params,
				 काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = mlxsw_sp_port_vlan->mlxsw_sp_port;

	params->vid = mlxsw_sp_port_vlan->vid;
	params->lag = mlxsw_sp_port->lagged;
	अगर (params->lag)
		params->lag_id = mlxsw_sp_port->lag_id;
	अन्यथा
		params->प्रणाली_port = mlxsw_sp_port->local_port;
पूर्ण

अटल काष्ठा mlxsw_sp_rअगर_subport *
mlxsw_sp_rअगर_subport_rअगर(स्थिर काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	वापस container_of(rअगर, काष्ठा mlxsw_sp_rअगर_subport, common);
पूर्ण

अटल काष्ठा mlxsw_sp_rअगर *
mlxsw_sp_rअगर_subport_get(काष्ठा mlxsw_sp *mlxsw_sp,
			 स्थिर काष्ठा mlxsw_sp_rअगर_params *params,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_rअगर_subport *rअगर_subport;
	काष्ठा mlxsw_sp_rअगर *rअगर;

	rअगर = mlxsw_sp_rअगर_find_by_dev(mlxsw_sp, params->dev);
	अगर (!rअगर)
		वापस mlxsw_sp_rअगर_create(mlxsw_sp, params, extack);

	rअगर_subport = mlxsw_sp_rअगर_subport_rअगर(rअगर);
	refcount_inc(&rअगर_subport->ref_count);
	वापस rअगर;
पूर्ण

अटल व्योम mlxsw_sp_rअगर_subport_put(काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा mlxsw_sp_rअगर_subport *rअगर_subport;

	rअगर_subport = mlxsw_sp_rअगर_subport_rअगर(rअगर);
	अगर (!refcount_dec_and_test(&rअगर_subport->ref_count))
		वापस;

	mlxsw_sp_rअगर_destroy(rअगर);
पूर्ण

अटल पूर्णांक
__mlxsw_sp_port_vlan_router_join(काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan,
				 काष्ठा net_device *l3_dev,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = mlxsw_sp_port_vlan->mlxsw_sp_port;
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_rअगर_params params = अणु
		.dev = l3_dev,
	पूर्ण;
	u16 vid = mlxsw_sp_port_vlan->vid;
	काष्ठा mlxsw_sp_rअगर *rअगर;
	काष्ठा mlxsw_sp_fid *fid;
	पूर्णांक err;

	mlxsw_sp_rअगर_subport_params_init(&params, mlxsw_sp_port_vlan);
	rअगर = mlxsw_sp_rअगर_subport_get(mlxsw_sp, &params, extack);
	अगर (IS_ERR(rअगर))
		वापस PTR_ERR(rअगर);

	/* FID was alपढ़ोy created, just take a reference */
	fid = rअगर->ops->fid_get(rअगर, extack);
	err = mlxsw_sp_fid_port_vid_map(fid, mlxsw_sp_port, vid);
	अगर (err)
		जाओ err_fid_port_vid_map;

	err = mlxsw_sp_port_vid_learning_set(mlxsw_sp_port, vid, false);
	अगर (err)
		जाओ err_port_vid_learning_set;

	err = mlxsw_sp_port_vid_stp_set(mlxsw_sp_port, vid,
					BR_STATE_FORWARDING);
	अगर (err)
		जाओ err_port_vid_stp_set;

	mlxsw_sp_port_vlan->fid = fid;

	वापस 0;

err_port_vid_stp_set:
	mlxsw_sp_port_vid_learning_set(mlxsw_sp_port, vid, true);
err_port_vid_learning_set:
	mlxsw_sp_fid_port_vid_unmap(fid, mlxsw_sp_port, vid);
err_fid_port_vid_map:
	mlxsw_sp_fid_put(fid);
	mlxsw_sp_rअगर_subport_put(rअगर);
	वापस err;
पूर्ण

अटल व्योम
__mlxsw_sp_port_vlan_router_leave(काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = mlxsw_sp_port_vlan->mlxsw_sp_port;
	काष्ठा mlxsw_sp_fid *fid = mlxsw_sp_port_vlan->fid;
	काष्ठा mlxsw_sp_rअगर *rअगर = mlxsw_sp_fid_rअगर(fid);
	u16 vid = mlxsw_sp_port_vlan->vid;

	अगर (WARN_ON(mlxsw_sp_fid_type(fid) != MLXSW_SP_FID_TYPE_RFID))
		वापस;

	mlxsw_sp_port_vlan->fid = शून्य;
	mlxsw_sp_port_vid_stp_set(mlxsw_sp_port, vid, BR_STATE_BLOCKING);
	mlxsw_sp_port_vid_learning_set(mlxsw_sp_port, vid, true);
	mlxsw_sp_fid_port_vid_unmap(fid, mlxsw_sp_port, vid);
	mlxsw_sp_fid_put(fid);
	mlxsw_sp_rअगर_subport_put(rअगर);
पूर्ण

पूर्णांक
mlxsw_sp_port_vlan_router_join(काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan,
			       काष्ठा net_device *l3_dev,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port_vlan->mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_rअगर *rअगर;
	पूर्णांक err = 0;

	mutex_lock(&mlxsw_sp->router->lock);
	rअगर = mlxsw_sp_rअगर_find_by_dev(mlxsw_sp, l3_dev);
	अगर (!rअगर)
		जाओ out;

	err = __mlxsw_sp_port_vlan_router_join(mlxsw_sp_port_vlan, l3_dev,
					       extack);
out:
	mutex_unlock(&mlxsw_sp->router->lock);
	वापस err;
पूर्ण

व्योम
mlxsw_sp_port_vlan_router_leave(काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port_vlan->mlxsw_sp_port->mlxsw_sp;

	mutex_lock(&mlxsw_sp->router->lock);
	__mlxsw_sp_port_vlan_router_leave(mlxsw_sp_port_vlan);
	mutex_unlock(&mlxsw_sp->router->lock);
पूर्ण

अटल पूर्णांक mlxsw_sp_inetaddr_port_vlan_event(काष्ठा net_device *l3_dev,
					     काष्ठा net_device *port_dev,
					     अचिन्हित दीर्घ event, u16 vid,
					     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(port_dev);
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;

	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_vid(mlxsw_sp_port, vid);
	अगर (WARN_ON(!mlxsw_sp_port_vlan))
		वापस -EINVAL;

	चयन (event) अणु
	हाल NETDEV_UP:
		वापस __mlxsw_sp_port_vlan_router_join(mlxsw_sp_port_vlan,
							l3_dev, extack);
	हाल NETDEV_DOWN:
		__mlxsw_sp_port_vlan_router_leave(mlxsw_sp_port_vlan);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_inetaddr_port_event(काष्ठा net_device *port_dev,
					अचिन्हित दीर्घ event,
					काष्ठा netlink_ext_ack *extack)
अणु
	अगर (netअगर_is_bridge_port(port_dev) ||
	    netअगर_is_lag_port(port_dev) ||
	    netअगर_is_ovs_port(port_dev))
		वापस 0;

	वापस mlxsw_sp_inetaddr_port_vlan_event(port_dev, port_dev, event,
						 MLXSW_SP_DEFAULT_VID, extack);
पूर्ण

अटल पूर्णांक __mlxsw_sp_inetaddr_lag_event(काष्ठा net_device *l3_dev,
					 काष्ठा net_device *lag_dev,
					 अचिन्हित दीर्घ event, u16 vid,
					 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *port_dev;
	काष्ठा list_head *iter;
	पूर्णांक err;

	netdev_क्रम_each_lower_dev(lag_dev, port_dev, iter) अणु
		अगर (mlxsw_sp_port_dev_check(port_dev)) अणु
			err = mlxsw_sp_inetaddr_port_vlan_event(l3_dev,
								port_dev,
								event, vid,
								extack);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_inetaddr_lag_event(काष्ठा net_device *lag_dev,
				       अचिन्हित दीर्घ event,
				       काष्ठा netlink_ext_ack *extack)
अणु
	अगर (netअगर_is_bridge_port(lag_dev))
		वापस 0;

	वापस __mlxsw_sp_inetaddr_lag_event(lag_dev, lag_dev, event,
					     MLXSW_SP_DEFAULT_VID, extack);
पूर्ण

अटल पूर्णांक mlxsw_sp_inetaddr_bridge_event(काष्ठा mlxsw_sp *mlxsw_sp,
					  काष्ठा net_device *l3_dev,
					  अचिन्हित दीर्घ event,
					  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_rअगर_params params = अणु
		.dev = l3_dev,
	पूर्ण;
	काष्ठा mlxsw_sp_rअगर *rअगर;

	चयन (event) अणु
	हाल NETDEV_UP:
		अगर (netअगर_is_bridge_master(l3_dev) && br_vlan_enabled(l3_dev)) अणु
			u16 proto;

			br_vlan_get_proto(l3_dev, &proto);
			अगर (proto == ETH_P_8021AD) अणु
				NL_SET_ERR_MSG_MOD(extack, "Adding an IP address to 802.1ad bridge is not supported");
				वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण
		rअगर = mlxsw_sp_rअगर_create(mlxsw_sp, &params, extack);
		अगर (IS_ERR(rअगर))
			वापस PTR_ERR(rअगर);
		अवरोध;
	हाल NETDEV_DOWN:
		rअगर = mlxsw_sp_rअगर_find_by_dev(mlxsw_sp, l3_dev);
		mlxsw_sp_rअगर_destroy(rअगर);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_inetaddr_vlan_event(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा net_device *vlan_dev,
					अचिन्हित दीर्घ event,
					काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *real_dev = vlan_dev_real_dev(vlan_dev);
	u16 vid = vlan_dev_vlan_id(vlan_dev);

	अगर (netअगर_is_bridge_port(vlan_dev))
		वापस 0;

	अगर (mlxsw_sp_port_dev_check(real_dev))
		वापस mlxsw_sp_inetaddr_port_vlan_event(vlan_dev, real_dev,
							 event, vid, extack);
	अन्यथा अगर (netअगर_is_lag_master(real_dev))
		वापस __mlxsw_sp_inetaddr_lag_event(vlan_dev, real_dev, event,
						     vid, extack);
	अन्यथा अगर (netअगर_is_bridge_master(real_dev) && br_vlan_enabled(real_dev))
		वापस mlxsw_sp_inetaddr_bridge_event(mlxsw_sp, vlan_dev, event,
						      extack);

	वापस 0;
पूर्ण

अटल bool mlxsw_sp_rअगर_macvlan_is_vrrp4(स्थिर u8 *mac)
अणु
	u8 vrrp4[ETH_ALEN] = अणु 0x00, 0x00, 0x5e, 0x00, 0x01, 0x00 पूर्ण;
	u8 mask[ETH_ALEN] = अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0x00 पूर्ण;

	वापस ether_addr_equal_masked(mac, vrrp4, mask);
पूर्ण

अटल bool mlxsw_sp_rअगर_macvlan_is_vrrp6(स्थिर u8 *mac)
अणु
	u8 vrrp6[ETH_ALEN] = अणु 0x00, 0x00, 0x5e, 0x00, 0x02, 0x00 पूर्ण;
	u8 mask[ETH_ALEN] = अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0x00 पूर्ण;

	वापस ether_addr_equal_masked(mac, vrrp6, mask);
पूर्ण

अटल पूर्णांक mlxsw_sp_rअगर_vrrp_op(काष्ठा mlxsw_sp *mlxsw_sp, u16 rअगर_index,
				स्थिर u8 *mac, bool adding)
अणु
	अक्षर ritr_pl[MLXSW_REG_RITR_LEN];
	u8 vrrp_id = adding ? mac[5] : 0;
	पूर्णांक err;

	अगर (!mlxsw_sp_rअगर_macvlan_is_vrrp4(mac) &&
	    !mlxsw_sp_rअगर_macvlan_is_vrrp6(mac))
		वापस 0;

	mlxsw_reg_ritr_rअगर_pack(ritr_pl, rअगर_index);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ritr), ritr_pl);
	अगर (err)
		वापस err;

	अगर (mlxsw_sp_rअगर_macvlan_is_vrrp4(mac))
		mlxsw_reg_ritr_अगर_vrrp_id_ipv4_set(ritr_pl, vrrp_id);
	अन्यथा
		mlxsw_reg_ritr_अगर_vrrp_id_ipv6_set(ritr_pl, vrrp_id);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ritr), ritr_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_rअगर_macvlan_add(काष्ठा mlxsw_sp *mlxsw_sp,
				    स्थिर काष्ठा net_device *macvlan_dev,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(macvlan_dev);
	काष्ठा mlxsw_sp_rअगर *rअगर;
	पूर्णांक err;

	rअगर = mlxsw_sp_rअगर_find_by_dev(mlxsw_sp, vlan->lowerdev);
	अगर (!rअगर) अणु
		NL_SET_ERR_MSG_MOD(extack, "macvlan is only supported on top of router interfaces");
		वापस -EOPNOTSUPP;
	पूर्ण

	err = mlxsw_sp_rअगर_fdb_op(mlxsw_sp, macvlan_dev->dev_addr,
				  mlxsw_sp_fid_index(rअगर->fid), true);
	अगर (err)
		वापस err;

	err = mlxsw_sp_rअगर_vrrp_op(mlxsw_sp, rअगर->rअगर_index,
				   macvlan_dev->dev_addr, true);
	अगर (err)
		जाओ err_rअगर_vrrp_add;

	/* Make sure the bridge driver करोes not have this MAC poपूर्णांकing at
	 * some other port.
	 */
	अगर (rअगर->ops->fdb_del)
		rअगर->ops->fdb_del(rअगर, macvlan_dev->dev_addr);

	वापस 0;

err_rअगर_vrrp_add:
	mlxsw_sp_rअगर_fdb_op(mlxsw_sp, macvlan_dev->dev_addr,
			    mlxsw_sp_fid_index(rअगर->fid), false);
	वापस err;
पूर्ण

अटल व्योम __mlxsw_sp_rअगर_macvlan_del(काष्ठा mlxsw_sp *mlxsw_sp,
				       स्थिर काष्ठा net_device *macvlan_dev)
अणु
	काष्ठा macvlan_dev *vlan = netdev_priv(macvlan_dev);
	काष्ठा mlxsw_sp_rअगर *rअगर;

	rअगर = mlxsw_sp_rअगर_find_by_dev(mlxsw_sp, vlan->lowerdev);
	/* If we करो not have a RIF, then we alपढ़ोy took care of
	 * removing the macvlan's MAC during RIF deletion.
	 */
	अगर (!rअगर)
		वापस;
	mlxsw_sp_rअगर_vrrp_op(mlxsw_sp, rअगर->rअगर_index, macvlan_dev->dev_addr,
			     false);
	mlxsw_sp_rअगर_fdb_op(mlxsw_sp, macvlan_dev->dev_addr,
			    mlxsw_sp_fid_index(rअगर->fid), false);
पूर्ण

व्योम mlxsw_sp_rअगर_macvlan_del(काष्ठा mlxsw_sp *mlxsw_sp,
			      स्थिर काष्ठा net_device *macvlan_dev)
अणु
	mutex_lock(&mlxsw_sp->router->lock);
	__mlxsw_sp_rअगर_macvlan_del(mlxsw_sp, macvlan_dev);
	mutex_unlock(&mlxsw_sp->router->lock);
पूर्ण

अटल पूर्णांक mlxsw_sp_inetaddr_macvlan_event(काष्ठा mlxsw_sp *mlxsw_sp,
					   काष्ठा net_device *macvlan_dev,
					   अचिन्हित दीर्घ event,
					   काष्ठा netlink_ext_ack *extack)
अणु
	चयन (event) अणु
	हाल NETDEV_UP:
		वापस mlxsw_sp_rअगर_macvlan_add(mlxsw_sp, macvlan_dev, extack);
	हाल NETDEV_DOWN:
		__mlxsw_sp_rअगर_macvlan_del(mlxsw_sp, macvlan_dev);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_router_port_check_rअगर_addr(काष्ठा mlxsw_sp *mlxsw_sp,
					       काष्ठा net_device *dev,
					       स्थिर अचिन्हित अक्षर *dev_addr,
					       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_rअगर *rअगर;
	पूर्णांक i;

	/* A RIF is not created क्रम macvlan netdevs. Their MAC is used to
	 * populate the FDB
	 */
	अगर (netअगर_is_macvlan(dev) || netअगर_is_l3_master(dev))
		वापस 0;

	क्रम (i = 0; i < MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS); i++) अणु
		rअगर = mlxsw_sp->router->rअगरs[i];
		अगर (rअगर && rअगर->ops &&
		    rअगर->ops->type == MLXSW_SP_RIF_TYPE_IPIP_LB)
			जारी;
		अगर (rअगर && rअगर->dev && rअगर->dev != dev &&
		    !ether_addr_equal_masked(rअगर->dev->dev_addr, dev_addr,
					     mlxsw_sp->mac_mask)) अणु
			NL_SET_ERR_MSG_MOD(extack, "All router interface MAC addresses must have the same prefix");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __mlxsw_sp_inetaddr_event(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा net_device *dev,
				     अचिन्हित दीर्घ event,
				     काष्ठा netlink_ext_ack *extack)
अणु
	अगर (mlxsw_sp_port_dev_check(dev))
		वापस mlxsw_sp_inetaddr_port_event(dev, event, extack);
	अन्यथा अगर (netअगर_is_lag_master(dev))
		वापस mlxsw_sp_inetaddr_lag_event(dev, event, extack);
	अन्यथा अगर (netअगर_is_bridge_master(dev))
		वापस mlxsw_sp_inetaddr_bridge_event(mlxsw_sp, dev, event,
						      extack);
	अन्यथा अगर (is_vlan_dev(dev))
		वापस mlxsw_sp_inetaddr_vlan_event(mlxsw_sp, dev, event,
						    extack);
	अन्यथा अगर (netअगर_is_macvlan(dev))
		वापस mlxsw_sp_inetaddr_macvlan_event(mlxsw_sp, dev, event,
						       extack);
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_inetaddr_event(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा in_अगरaddr *अगरa = (काष्ठा in_अगरaddr *) ptr;
	काष्ठा net_device *dev = अगरa->अगरa_dev->dev;
	काष्ठा mlxsw_sp_router *router;
	काष्ठा mlxsw_sp_rअगर *rअगर;
	पूर्णांक err = 0;

	/* NETDEV_UP event is handled by mlxsw_sp_inetaddr_valid_event */
	अगर (event == NETDEV_UP)
		वापस NOTIFY_DONE;

	router = container_of(nb, काष्ठा mlxsw_sp_router, inetaddr_nb);
	mutex_lock(&router->lock);
	rअगर = mlxsw_sp_rअगर_find_by_dev(router->mlxsw_sp, dev);
	अगर (!mlxsw_sp_rअगर_should_config(rअगर, dev, event))
		जाओ out;

	err = __mlxsw_sp_inetaddr_event(router->mlxsw_sp, dev, event, शून्य);
out:
	mutex_unlock(&router->lock);
	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

पूर्णांक mlxsw_sp_inetaddr_valid_event(काष्ठा notअगरier_block *unused,
				  अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा in_validator_info *ivi = (काष्ठा in_validator_info *) ptr;
	काष्ठा net_device *dev = ivi->ivi_dev->dev;
	काष्ठा mlxsw_sp *mlxsw_sp;
	काष्ठा mlxsw_sp_rअगर *rअगर;
	पूर्णांक err = 0;

	mlxsw_sp = mlxsw_sp_lower_get(dev);
	अगर (!mlxsw_sp)
		वापस NOTIFY_DONE;

	mutex_lock(&mlxsw_sp->router->lock);
	rअगर = mlxsw_sp_rअगर_find_by_dev(mlxsw_sp, dev);
	अगर (!mlxsw_sp_rअगर_should_config(rअगर, dev, event))
		जाओ out;

	err = mlxsw_sp_router_port_check_rअगर_addr(mlxsw_sp, dev, dev->dev_addr,
						  ivi->extack);
	अगर (err)
		जाओ out;

	err = __mlxsw_sp_inetaddr_event(mlxsw_sp, dev, event, ivi->extack);
out:
	mutex_unlock(&mlxsw_sp->router->lock);
	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

काष्ठा mlxsw_sp_inet6addr_event_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा mlxsw_sp *mlxsw_sp;
	काष्ठा net_device *dev;
	अचिन्हित दीर्घ event;
पूर्ण;

अटल व्योम mlxsw_sp_inet6addr_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_sp_inet6addr_event_work *inet6addr_work =
		container_of(work, काष्ठा mlxsw_sp_inet6addr_event_work, work);
	काष्ठा mlxsw_sp *mlxsw_sp = inet6addr_work->mlxsw_sp;
	काष्ठा net_device *dev = inet6addr_work->dev;
	अचिन्हित दीर्घ event = inet6addr_work->event;
	काष्ठा mlxsw_sp_rअगर *rअगर;

	rtnl_lock();
	mutex_lock(&mlxsw_sp->router->lock);

	rअगर = mlxsw_sp_rअगर_find_by_dev(mlxsw_sp, dev);
	अगर (!mlxsw_sp_rअगर_should_config(rअगर, dev, event))
		जाओ out;

	__mlxsw_sp_inetaddr_event(mlxsw_sp, dev, event, शून्य);
out:
	mutex_unlock(&mlxsw_sp->router->lock);
	rtnl_unlock();
	dev_put(dev);
	kमुक्त(inet6addr_work);
पूर्ण

/* Called with rcu_पढ़ो_lock() */
अटल पूर्णांक mlxsw_sp_inet6addr_event(काष्ठा notअगरier_block *nb,
				    अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा inet6_अगरaddr *अगर6 = (काष्ठा inet6_अगरaddr *) ptr;
	काष्ठा mlxsw_sp_inet6addr_event_work *inet6addr_work;
	काष्ठा net_device *dev = अगर6->idev->dev;
	काष्ठा mlxsw_sp_router *router;

	/* NETDEV_UP event is handled by mlxsw_sp_inet6addr_valid_event */
	अगर (event == NETDEV_UP)
		वापस NOTIFY_DONE;

	inet6addr_work = kzalloc(माप(*inet6addr_work), GFP_ATOMIC);
	अगर (!inet6addr_work)
		वापस NOTIFY_BAD;

	router = container_of(nb, काष्ठा mlxsw_sp_router, inet6addr_nb);
	INIT_WORK(&inet6addr_work->work, mlxsw_sp_inet6addr_event_work);
	inet6addr_work->mlxsw_sp = router->mlxsw_sp;
	inet6addr_work->dev = dev;
	inet6addr_work->event = event;
	dev_hold(dev);
	mlxsw_core_schedule_work(&inet6addr_work->work);

	वापस NOTIFY_DONE;
पूर्ण

पूर्णांक mlxsw_sp_inet6addr_valid_event(काष्ठा notअगरier_block *unused,
				   अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा in6_validator_info *i6vi = (काष्ठा in6_validator_info *) ptr;
	काष्ठा net_device *dev = i6vi->i6vi_dev->dev;
	काष्ठा mlxsw_sp *mlxsw_sp;
	काष्ठा mlxsw_sp_rअगर *rअगर;
	पूर्णांक err = 0;

	mlxsw_sp = mlxsw_sp_lower_get(dev);
	अगर (!mlxsw_sp)
		वापस NOTIFY_DONE;

	mutex_lock(&mlxsw_sp->router->lock);
	rअगर = mlxsw_sp_rअगर_find_by_dev(mlxsw_sp, dev);
	अगर (!mlxsw_sp_rअगर_should_config(rअगर, dev, event))
		जाओ out;

	err = mlxsw_sp_router_port_check_rअगर_addr(mlxsw_sp, dev, dev->dev_addr,
						  i6vi->extack);
	अगर (err)
		जाओ out;

	err = __mlxsw_sp_inetaddr_event(mlxsw_sp, dev, event, i6vi->extack);
out:
	mutex_unlock(&mlxsw_sp->router->lock);
	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

अटल पूर्णांक mlxsw_sp_rअगर_edit(काष्ठा mlxsw_sp *mlxsw_sp, u16 rअगर_index,
			     स्थिर अक्षर *mac, पूर्णांक mtu)
अणु
	अक्षर ritr_pl[MLXSW_REG_RITR_LEN];
	पूर्णांक err;

	mlxsw_reg_ritr_rअगर_pack(ritr_pl, rअगर_index);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ritr), ritr_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_ritr_mtu_set(ritr_pl, mtu);
	mlxsw_reg_ritr_अगर_mac_स_नकल_to(ritr_pl, mac);
	mlxsw_reg_ritr_op_set(ritr_pl, MLXSW_REG_RITR_RIF_CREATE);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ritr), ritr_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_router_port_change_event(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा net_device *dev = rअगर->dev;
	u16 fid_index;
	पूर्णांक err;

	fid_index = mlxsw_sp_fid_index(rअगर->fid);

	err = mlxsw_sp_rअगर_fdb_op(mlxsw_sp, rअगर->addr, fid_index, false);
	अगर (err)
		वापस err;

	err = mlxsw_sp_rअगर_edit(mlxsw_sp, rअगर->rअगर_index, dev->dev_addr,
				dev->mtu);
	अगर (err)
		जाओ err_rअगर_edit;

	err = mlxsw_sp_rअगर_fdb_op(mlxsw_sp, dev->dev_addr, fid_index, true);
	अगर (err)
		जाओ err_rअगर_fdb_op;

	अगर (rअगर->mtu != dev->mtu) अणु
		काष्ठा mlxsw_sp_vr *vr;
		पूर्णांक i;

		/* The RIF is relevant only to its mr_table instance, as unlike
		 * unicast routing, in multicast routing a RIF cannot be shared
		 * between several multicast routing tables.
		 */
		vr = &mlxsw_sp->router->vrs[rअगर->vr_id];
		क्रम (i = 0; i < MLXSW_SP_L3_PROTO_MAX; i++)
			mlxsw_sp_mr_rअगर_mtu_update(vr->mr_table[i],
						   rअगर, dev->mtu);
	पूर्ण

	ether_addr_copy(rअगर->addr, dev->dev_addr);
	rअगर->mtu = dev->mtu;

	netdev_dbg(dev, "Updated RIF=%d\n", rअगर->rअगर_index);

	वापस 0;

err_rअगर_fdb_op:
	mlxsw_sp_rअगर_edit(mlxsw_sp, rअगर->rअगर_index, rअगर->addr, rअगर->mtu);
err_rअगर_edit:
	mlxsw_sp_rअगर_fdb_op(mlxsw_sp, rअगर->addr, fid_index, true);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_router_port_pre_changeaddr_event(काष्ठा mlxsw_sp_rअगर *rअगर,
			    काष्ठा netdev_notअगरier_pre_changeaddr_info *info)
अणु
	काष्ठा netlink_ext_ack *extack;

	extack = netdev_notअगरier_info_to_extack(&info->info);
	वापस mlxsw_sp_router_port_check_rअगर_addr(rअगर->mlxsw_sp, rअगर->dev,
						   info->dev_addr, extack);
पूर्ण

पूर्णांक mlxsw_sp_netdevice_router_port_event(काष्ठा net_device *dev,
					 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp;
	काष्ठा mlxsw_sp_rअगर *rअगर;
	पूर्णांक err = 0;

	mlxsw_sp = mlxsw_sp_lower_get(dev);
	अगर (!mlxsw_sp)
		वापस 0;

	mutex_lock(&mlxsw_sp->router->lock);
	rअगर = mlxsw_sp_rअगर_find_by_dev(mlxsw_sp, dev);
	अगर (!rअगर)
		जाओ out;

	चयन (event) अणु
	हाल NETDEV_CHANGEMTU:
	हाल NETDEV_CHANGEADDR:
		err = mlxsw_sp_router_port_change_event(mlxsw_sp, rअगर);
		अवरोध;
	हाल NETDEV_PRE_CHANGEADDR:
		err = mlxsw_sp_router_port_pre_changeaddr_event(rअगर, ptr);
		अवरोध;
	पूर्ण

out:
	mutex_unlock(&mlxsw_sp->router->lock);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_vrf_join(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा net_device *l3_dev,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_rअगर *rअगर;

	/* If netdev is alपढ़ोy associated with a RIF, then we need to
	 * destroy it and create a new one with the new भव router ID.
	 */
	rअगर = mlxsw_sp_rअगर_find_by_dev(mlxsw_sp, l3_dev);
	अगर (rअगर)
		__mlxsw_sp_inetaddr_event(mlxsw_sp, l3_dev, NETDEV_DOWN,
					  extack);

	वापस __mlxsw_sp_inetaddr_event(mlxsw_sp, l3_dev, NETDEV_UP, extack);
पूर्ण

अटल व्योम mlxsw_sp_port_vrf_leave(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा net_device *l3_dev)
अणु
	काष्ठा mlxsw_sp_rअगर *rअगर;

	rअगर = mlxsw_sp_rअगर_find_by_dev(mlxsw_sp, l3_dev);
	अगर (!rअगर)
		वापस;
	__mlxsw_sp_inetaddr_event(mlxsw_sp, l3_dev, NETDEV_DOWN, शून्य);
पूर्ण

पूर्णांक mlxsw_sp_netdevice_vrf_event(काष्ठा net_device *l3_dev, अचिन्हित दीर्घ event,
				 काष्ठा netdev_notअगरier_changeupper_info *info)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_lower_get(l3_dev);
	पूर्णांक err = 0;

	/* We करो not create a RIF क्रम a macvlan, but only use it to
	 * direct more MAC addresses to the router.
	 */
	अगर (!mlxsw_sp || netअगर_is_macvlan(l3_dev))
		वापस 0;

	mutex_lock(&mlxsw_sp->router->lock);
	चयन (event) अणु
	हाल NETDEV_PRECHANGEUPPER:
		अवरोध;
	हाल NETDEV_CHANGEUPPER:
		अगर (info->linking) अणु
			काष्ठा netlink_ext_ack *extack;

			extack = netdev_notअगरier_info_to_extack(&info->info);
			err = mlxsw_sp_port_vrf_join(mlxsw_sp, l3_dev, extack);
		पूर्ण अन्यथा अणु
			mlxsw_sp_port_vrf_leave(mlxsw_sp, l3_dev);
		पूर्ण
		अवरोध;
	पूर्ण
	mutex_unlock(&mlxsw_sp->router->lock);

	वापस err;
पूर्ण

अटल पूर्णांक __mlxsw_sp_rअगर_macvlan_flush(काष्ठा net_device *dev,
					काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा mlxsw_sp_rअगर *rअगर = (काष्ठा mlxsw_sp_rअगर *)priv->data;

	अगर (!netअगर_is_macvlan(dev))
		वापस 0;

	वापस mlxsw_sp_rअगर_fdb_op(rअगर->mlxsw_sp, dev->dev_addr,
				   mlxsw_sp_fid_index(rअगर->fid), false);
पूर्ण

अटल पूर्णांक mlxsw_sp_rअगर_macvlan_flush(काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.data = (व्योम *)rअगर,
	पूर्ण;

	अगर (!netअगर_is_macvlan_port(rअगर->dev))
		वापस 0;

	netdev_warn(rअगर->dev, "Router interface is deleted. Upper macvlans will not work\n");
	वापस netdev_walk_all_upper_dev_rcu(rअगर->dev,
					     __mlxsw_sp_rअगर_macvlan_flush, &priv);
पूर्ण

अटल व्योम mlxsw_sp_rअगर_subport_setup(काष्ठा mlxsw_sp_rअगर *rअगर,
				       स्थिर काष्ठा mlxsw_sp_rअगर_params *params)
अणु
	काष्ठा mlxsw_sp_rअगर_subport *rअगर_subport;

	rअगर_subport = mlxsw_sp_rअगर_subport_rअगर(rअगर);
	refcount_set(&rअगर_subport->ref_count, 1);
	rअगर_subport->vid = params->vid;
	rअगर_subport->lag = params->lag;
	अगर (params->lag)
		rअगर_subport->lag_id = params->lag_id;
	अन्यथा
		rअगर_subport->प्रणाली_port = params->प्रणाली_port;
पूर्ण

अटल पूर्णांक mlxsw_sp_rअगर_subport_op(काष्ठा mlxsw_sp_rअगर *rअगर, bool enable)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = rअगर->mlxsw_sp;
	काष्ठा mlxsw_sp_rअगर_subport *rअगर_subport;
	अक्षर ritr_pl[MLXSW_REG_RITR_LEN];

	rअगर_subport = mlxsw_sp_rअगर_subport_rअगर(rअगर);
	mlxsw_reg_ritr_pack(ritr_pl, enable, MLXSW_REG_RITR_SP_IF,
			    rअगर->rअगर_index, rअगर->vr_id, rअगर->dev->mtu);
	mlxsw_reg_ritr_mac_pack(ritr_pl, rअगर->dev->dev_addr);
	mlxsw_reg_ritr_sp_अगर_pack(ritr_pl, rअगर_subport->lag,
				  rअगर_subport->lag ? rअगर_subport->lag_id :
						     rअगर_subport->प्रणाली_port,
				  rअगर_subport->vid);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ritr), ritr_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_rअगर_subport_configure(काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	पूर्णांक err;

	err = mlxsw_sp_rअगर_subport_op(rअगर, true);
	अगर (err)
		वापस err;

	err = mlxsw_sp_rअगर_fdb_op(rअगर->mlxsw_sp, rअगर->dev->dev_addr,
				  mlxsw_sp_fid_index(rअगर->fid), true);
	अगर (err)
		जाओ err_rअगर_fdb_op;

	mlxsw_sp_fid_rअगर_set(rअगर->fid, rअगर);
	वापस 0;

err_rअगर_fdb_op:
	mlxsw_sp_rअगर_subport_op(rअगर, false);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_rअगर_subport_deconfigure(काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा mlxsw_sp_fid *fid = rअगर->fid;

	mlxsw_sp_fid_rअगर_set(fid, शून्य);
	mlxsw_sp_rअगर_fdb_op(rअगर->mlxsw_sp, rअगर->dev->dev_addr,
			    mlxsw_sp_fid_index(fid), false);
	mlxsw_sp_rअगर_macvlan_flush(rअगर);
	mlxsw_sp_rअगर_subport_op(rअगर, false);
पूर्ण

अटल काष्ठा mlxsw_sp_fid *
mlxsw_sp_rअगर_subport_fid_get(काष्ठा mlxsw_sp_rअगर *rअगर,
			     काष्ठा netlink_ext_ack *extack)
अणु
	वापस mlxsw_sp_fid_rfid_get(rअगर->mlxsw_sp, rअगर->rअगर_index);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_rअगर_ops mlxsw_sp_rअगर_subport_ops = अणु
	.type			= MLXSW_SP_RIF_TYPE_SUBPORT,
	.rअगर_size		= माप(काष्ठा mlxsw_sp_rअगर_subport),
	.setup			= mlxsw_sp_rअगर_subport_setup,
	.configure		= mlxsw_sp_rअगर_subport_configure,
	.deconfigure		= mlxsw_sp_rअगर_subport_deconfigure,
	.fid_get		= mlxsw_sp_rअगर_subport_fid_get,
पूर्ण;

अटल पूर्णांक mlxsw_sp_rअगर_vlan_fid_op(काष्ठा mlxsw_sp_rअगर *rअगर,
				    क्रमागत mlxsw_reg_ritr_अगर_type type,
				    u16 vid_fid, bool enable)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = rअगर->mlxsw_sp;
	अक्षर ritr_pl[MLXSW_REG_RITR_LEN];

	mlxsw_reg_ritr_pack(ritr_pl, enable, type, rअगर->rअगर_index, rअगर->vr_id,
			    rअगर->dev->mtu);
	mlxsw_reg_ritr_mac_pack(ritr_pl, rअगर->dev->dev_addr);
	mlxsw_reg_ritr_fid_set(ritr_pl, type, vid_fid);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ritr), ritr_pl);
पूर्ण

u8 mlxsw_sp_router_port(स्थिर काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	वापस mlxsw_core_max_ports(mlxsw_sp->core) + 1;
पूर्ण

अटल पूर्णांक mlxsw_sp_rअगर_fid_configure(काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = rअगर->mlxsw_sp;
	u16 fid_index = mlxsw_sp_fid_index(rअगर->fid);
	पूर्णांक err;

	err = mlxsw_sp_rअगर_vlan_fid_op(rअगर, MLXSW_REG_RITR_FID_IF, fid_index,
				       true);
	अगर (err)
		वापस err;

	err = mlxsw_sp_fid_flood_set(rअगर->fid, MLXSW_SP_FLOOD_TYPE_MC,
				     mlxsw_sp_router_port(mlxsw_sp), true);
	अगर (err)
		जाओ err_fid_mc_flood_set;

	err = mlxsw_sp_fid_flood_set(rअगर->fid, MLXSW_SP_FLOOD_TYPE_BC,
				     mlxsw_sp_router_port(mlxsw_sp), true);
	अगर (err)
		जाओ err_fid_bc_flood_set;

	err = mlxsw_sp_rअगर_fdb_op(rअगर->mlxsw_sp, rअगर->dev->dev_addr,
				  mlxsw_sp_fid_index(rअगर->fid), true);
	अगर (err)
		जाओ err_rअगर_fdb_op;

	mlxsw_sp_fid_rअगर_set(rअगर->fid, rअगर);
	वापस 0;

err_rअगर_fdb_op:
	mlxsw_sp_fid_flood_set(rअगर->fid, MLXSW_SP_FLOOD_TYPE_BC,
			       mlxsw_sp_router_port(mlxsw_sp), false);
err_fid_bc_flood_set:
	mlxsw_sp_fid_flood_set(rअगर->fid, MLXSW_SP_FLOOD_TYPE_MC,
			       mlxsw_sp_router_port(mlxsw_sp), false);
err_fid_mc_flood_set:
	mlxsw_sp_rअगर_vlan_fid_op(rअगर, MLXSW_REG_RITR_FID_IF, fid_index, false);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_rअगर_fid_deconfigure(काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	u16 fid_index = mlxsw_sp_fid_index(rअगर->fid);
	काष्ठा mlxsw_sp *mlxsw_sp = rअगर->mlxsw_sp;
	काष्ठा mlxsw_sp_fid *fid = rअगर->fid;

	mlxsw_sp_fid_rअगर_set(fid, शून्य);
	mlxsw_sp_rअगर_fdb_op(rअगर->mlxsw_sp, rअगर->dev->dev_addr,
			    mlxsw_sp_fid_index(fid), false);
	mlxsw_sp_rअगर_macvlan_flush(rअगर);
	mlxsw_sp_fid_flood_set(rअगर->fid, MLXSW_SP_FLOOD_TYPE_BC,
			       mlxsw_sp_router_port(mlxsw_sp), false);
	mlxsw_sp_fid_flood_set(rअगर->fid, MLXSW_SP_FLOOD_TYPE_MC,
			       mlxsw_sp_router_port(mlxsw_sp), false);
	mlxsw_sp_rअगर_vlan_fid_op(rअगर, MLXSW_REG_RITR_FID_IF, fid_index, false);
पूर्ण

अटल काष्ठा mlxsw_sp_fid *
mlxsw_sp_rअगर_fid_fid_get(काष्ठा mlxsw_sp_rअगर *rअगर,
			 काष्ठा netlink_ext_ack *extack)
अणु
	वापस mlxsw_sp_fid_8021d_get(rअगर->mlxsw_sp, rअगर->dev->अगरindex);
पूर्ण

अटल व्योम mlxsw_sp_rअगर_fid_fdb_del(काष्ठा mlxsw_sp_rअगर *rअगर, स्थिर अक्षर *mac)
अणु
	काष्ठा चयनdev_notअगरier_fdb_info info;
	काष्ठा net_device *dev;

	dev = br_fdb_find_port(rअगर->dev, mac, 0);
	अगर (!dev)
		वापस;

	info.addr = mac;
	info.vid = 0;
	call_चयनdev_notअगरiers(SWITCHDEV_FDB_DEL_TO_BRIDGE, dev, &info.info,
				 शून्य);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_rअगर_ops mlxsw_sp_rअगर_fid_ops = अणु
	.type			= MLXSW_SP_RIF_TYPE_FID,
	.rअगर_size		= माप(काष्ठा mlxsw_sp_rअगर),
	.configure		= mlxsw_sp_rअगर_fid_configure,
	.deconfigure		= mlxsw_sp_rअगर_fid_deconfigure,
	.fid_get		= mlxsw_sp_rअगर_fid_fid_get,
	.fdb_del		= mlxsw_sp_rअगर_fid_fdb_del,
पूर्ण;

अटल काष्ठा mlxsw_sp_fid *
mlxsw_sp_rअगर_vlan_fid_get(काष्ठा mlxsw_sp_rअगर *rअगर,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *br_dev;
	u16 vid;
	पूर्णांक err;

	अगर (is_vlan_dev(rअगर->dev)) अणु
		vid = vlan_dev_vlan_id(rअगर->dev);
		br_dev = vlan_dev_real_dev(rअगर->dev);
		अगर (WARN_ON(!netअगर_is_bridge_master(br_dev)))
			वापस ERR_PTR(-EINVAL);
	पूर्ण अन्यथा अणु
		err = br_vlan_get_pvid(rअगर->dev, &vid);
		अगर (err < 0 || !vid) अणु
			NL_SET_ERR_MSG_MOD(extack, "Couldn't determine bridge PVID");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	वापस mlxsw_sp_fid_8021q_get(rअगर->mlxsw_sp, vid);
पूर्ण

अटल व्योम mlxsw_sp_rअगर_vlan_fdb_del(काष्ठा mlxsw_sp_rअगर *rअगर, स्थिर अक्षर *mac)
अणु
	u16 vid = mlxsw_sp_fid_8021q_vid(rअगर->fid);
	काष्ठा चयनdev_notअगरier_fdb_info info;
	काष्ठा net_device *br_dev;
	काष्ठा net_device *dev;

	br_dev = is_vlan_dev(rअगर->dev) ? vlan_dev_real_dev(rअगर->dev) : rअगर->dev;
	dev = br_fdb_find_port(br_dev, mac, vid);
	अगर (!dev)
		वापस;

	info.addr = mac;
	info.vid = vid;
	call_चयनdev_notअगरiers(SWITCHDEV_FDB_DEL_TO_BRIDGE, dev, &info.info,
				 शून्य);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_rअगर_ops mlxsw_sp_rअगर_vlan_emu_ops = अणु
	.type			= MLXSW_SP_RIF_TYPE_VLAN,
	.rअगर_size		= माप(काष्ठा mlxsw_sp_rअगर),
	.configure		= mlxsw_sp_rअगर_fid_configure,
	.deconfigure		= mlxsw_sp_rअगर_fid_deconfigure,
	.fid_get		= mlxsw_sp_rअगर_vlan_fid_get,
	.fdb_del		= mlxsw_sp_rअगर_vlan_fdb_del,
पूर्ण;

अटल काष्ठा mlxsw_sp_rअगर_ipip_lb *
mlxsw_sp_rअगर_ipip_lb_rअगर(काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	वापस container_of(rअगर, काष्ठा mlxsw_sp_rअगर_ipip_lb, common);
पूर्ण

अटल व्योम
mlxsw_sp_rअगर_ipip_lb_setup(काष्ठा mlxsw_sp_rअगर *rअगर,
			   स्थिर काष्ठा mlxsw_sp_rअगर_params *params)
अणु
	काष्ठा mlxsw_sp_rअगर_params_ipip_lb *params_lb;
	काष्ठा mlxsw_sp_rअगर_ipip_lb *rअगर_lb;

	params_lb = container_of(params, काष्ठा mlxsw_sp_rअगर_params_ipip_lb,
				 common);
	rअगर_lb = mlxsw_sp_rअगर_ipip_lb_rअगर(rअगर);
	rअगर_lb->lb_config = params_lb->lb_config;
पूर्ण

अटल पूर्णांक
mlxsw_sp1_rअगर_ipip_lb_configure(काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा mlxsw_sp_rअगर_ipip_lb *lb_rअगर = mlxsw_sp_rअगर_ipip_lb_rअगर(rअगर);
	u32 ul_tb_id = mlxsw_sp_ipip_dev_ul_tb_id(rअगर->dev);
	काष्ठा mlxsw_sp *mlxsw_sp = rअगर->mlxsw_sp;
	काष्ठा mlxsw_sp_vr *ul_vr;
	पूर्णांक err;

	ul_vr = mlxsw_sp_vr_get(mlxsw_sp, ul_tb_id, शून्य);
	अगर (IS_ERR(ul_vr))
		वापस PTR_ERR(ul_vr);

	err = mlxsw_sp_rअगर_ipip_lb_op(lb_rअगर, ul_vr->id, 0, true);
	अगर (err)
		जाओ err_loopback_op;

	lb_rअगर->ul_vr_id = ul_vr->id;
	lb_rअगर->ul_rअगर_id = 0;
	++ul_vr->rअगर_count;
	वापस 0;

err_loopback_op:
	mlxsw_sp_vr_put(mlxsw_sp, ul_vr);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp1_rअगर_ipip_lb_deconfigure(काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा mlxsw_sp_rअगर_ipip_lb *lb_rअगर = mlxsw_sp_rअगर_ipip_lb_rअगर(rअगर);
	काष्ठा mlxsw_sp *mlxsw_sp = rअगर->mlxsw_sp;
	काष्ठा mlxsw_sp_vr *ul_vr;

	ul_vr = &mlxsw_sp->router->vrs[lb_rअगर->ul_vr_id];
	mlxsw_sp_rअगर_ipip_lb_op(lb_rअगर, ul_vr->id, 0, false);

	--ul_vr->rअगर_count;
	mlxsw_sp_vr_put(mlxsw_sp, ul_vr);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_rअगर_ops mlxsw_sp1_rअगर_ipip_lb_ops = अणु
	.type			= MLXSW_SP_RIF_TYPE_IPIP_LB,
	.rअगर_size		= माप(काष्ठा mlxsw_sp_rअगर_ipip_lb),
	.setup                  = mlxsw_sp_rअगर_ipip_lb_setup,
	.configure		= mlxsw_sp1_rअगर_ipip_lb_configure,
	.deconfigure		= mlxsw_sp1_rअगर_ipip_lb_deconfigure,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_rअगर_ops *mlxsw_sp1_rअगर_ops_arr[] = अणु
	[MLXSW_SP_RIF_TYPE_SUBPORT]	= &mlxsw_sp_rअगर_subport_ops,
	[MLXSW_SP_RIF_TYPE_VLAN]	= &mlxsw_sp_rअगर_vlan_emu_ops,
	[MLXSW_SP_RIF_TYPE_FID]		= &mlxsw_sp_rअगर_fid_ops,
	[MLXSW_SP_RIF_TYPE_IPIP_LB]	= &mlxsw_sp1_rअगर_ipip_lb_ops,
पूर्ण;

अटल पूर्णांक
mlxsw_sp_rअगर_ipip_lb_ul_rअगर_op(काष्ठा mlxsw_sp_rअगर *ul_rअगर, bool enable)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = ul_rअगर->mlxsw_sp;
	अक्षर ritr_pl[MLXSW_REG_RITR_LEN];

	mlxsw_reg_ritr_pack(ritr_pl, enable, MLXSW_REG_RITR_LOOPBACK_IF,
			    ul_rअगर->rअगर_index, ul_rअगर->vr_id, IP_MAX_MTU);
	mlxsw_reg_ritr_loopback_protocol_set(ritr_pl,
					     MLXSW_REG_RITR_LOOPBACK_GENERIC);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ritr), ritr_pl);
पूर्ण

अटल काष्ठा mlxsw_sp_rअगर *
mlxsw_sp_ul_rअगर_create(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा mlxsw_sp_vr *vr,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_rअगर *ul_rअगर;
	u16 rअगर_index;
	पूर्णांक err;

	err = mlxsw_sp_rअगर_index_alloc(mlxsw_sp, &rअगर_index);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Exceeded number of supported router interfaces");
		वापस ERR_PTR(err);
	पूर्ण

	ul_rअगर = mlxsw_sp_rअगर_alloc(माप(*ul_rअगर), rअगर_index, vr->id, शून्य);
	अगर (!ul_rअगर)
		वापस ERR_PTR(-ENOMEM);

	mlxsw_sp->router->rअगरs[rअगर_index] = ul_rअगर;
	ul_rअगर->mlxsw_sp = mlxsw_sp;
	err = mlxsw_sp_rअगर_ipip_lb_ul_rअगर_op(ul_rअगर, true);
	अगर (err)
		जाओ ul_rअगर_op_err;

	वापस ul_rअगर;

ul_rअगर_op_err:
	mlxsw_sp->router->rअगरs[rअगर_index] = शून्य;
	kमुक्त(ul_rअगर);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_sp_ul_rअगर_destroy(काष्ठा mlxsw_sp_rअगर *ul_rअगर)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = ul_rअगर->mlxsw_sp;

	mlxsw_sp_rअगर_ipip_lb_ul_rअगर_op(ul_rअगर, false);
	mlxsw_sp->router->rअगरs[ul_rअगर->rअगर_index] = शून्य;
	kमुक्त(ul_rअगर);
पूर्ण

अटल काष्ठा mlxsw_sp_rअगर *
mlxsw_sp_ul_rअगर_get(काष्ठा mlxsw_sp *mlxsw_sp, u32 tb_id,
		    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_vr *vr;
	पूर्णांक err;

	vr = mlxsw_sp_vr_get(mlxsw_sp, tb_id, extack);
	अगर (IS_ERR(vr))
		वापस ERR_CAST(vr);

	अगर (refcount_inc_not_zero(&vr->ul_rअगर_refcnt))
		वापस vr->ul_rअगर;

	vr->ul_rअगर = mlxsw_sp_ul_rअगर_create(mlxsw_sp, vr, extack);
	अगर (IS_ERR(vr->ul_rअगर)) अणु
		err = PTR_ERR(vr->ul_rअगर);
		जाओ err_ul_rअगर_create;
	पूर्ण

	vr->rअगर_count++;
	refcount_set(&vr->ul_rअगर_refcnt, 1);

	वापस vr->ul_rअगर;

err_ul_rअगर_create:
	mlxsw_sp_vr_put(mlxsw_sp, vr);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_sp_ul_rअगर_put(काष्ठा mlxsw_sp_rअगर *ul_rअगर)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = ul_rअगर->mlxsw_sp;
	काष्ठा mlxsw_sp_vr *vr;

	vr = &mlxsw_sp->router->vrs[ul_rअगर->vr_id];

	अगर (!refcount_dec_and_test(&vr->ul_rअगर_refcnt))
		वापस;

	vr->rअगर_count--;
	mlxsw_sp_ul_rअगर_destroy(ul_rअगर);
	mlxsw_sp_vr_put(mlxsw_sp, vr);
पूर्ण

पूर्णांक mlxsw_sp_router_ul_rअगर_get(काष्ठा mlxsw_sp *mlxsw_sp, u32 ul_tb_id,
			       u16 *ul_rअगर_index)
अणु
	काष्ठा mlxsw_sp_rअगर *ul_rअगर;
	पूर्णांक err = 0;

	mutex_lock(&mlxsw_sp->router->lock);
	ul_rअगर = mlxsw_sp_ul_rअगर_get(mlxsw_sp, ul_tb_id, शून्य);
	अगर (IS_ERR(ul_rअगर)) अणु
		err = PTR_ERR(ul_rअगर);
		जाओ out;
	पूर्ण
	*ul_rअगर_index = ul_rअगर->rअगर_index;
out:
	mutex_unlock(&mlxsw_sp->router->lock);
	वापस err;
पूर्ण

व्योम mlxsw_sp_router_ul_rअगर_put(काष्ठा mlxsw_sp *mlxsw_sp, u16 ul_rअगर_index)
अणु
	काष्ठा mlxsw_sp_rअगर *ul_rअगर;

	mutex_lock(&mlxsw_sp->router->lock);
	ul_rअगर = mlxsw_sp->router->rअगरs[ul_rअगर_index];
	अगर (WARN_ON(!ul_rअगर))
		जाओ out;

	mlxsw_sp_ul_rअगर_put(ul_rअगर);
out:
	mutex_unlock(&mlxsw_sp->router->lock);
पूर्ण

अटल पूर्णांक
mlxsw_sp2_rअगर_ipip_lb_configure(काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा mlxsw_sp_rअगर_ipip_lb *lb_rअगर = mlxsw_sp_rअगर_ipip_lb_rअगर(rअगर);
	u32 ul_tb_id = mlxsw_sp_ipip_dev_ul_tb_id(rअगर->dev);
	काष्ठा mlxsw_sp *mlxsw_sp = rअगर->mlxsw_sp;
	काष्ठा mlxsw_sp_rअगर *ul_rअगर;
	पूर्णांक err;

	ul_rअगर = mlxsw_sp_ul_rअगर_get(mlxsw_sp, ul_tb_id, शून्य);
	अगर (IS_ERR(ul_rअगर))
		वापस PTR_ERR(ul_rअगर);

	err = mlxsw_sp_rअगर_ipip_lb_op(lb_rअगर, 0, ul_rअगर->rअगर_index, true);
	अगर (err)
		जाओ err_loopback_op;

	lb_rअगर->ul_vr_id = 0;
	lb_rअगर->ul_rअगर_id = ul_rअगर->rअगर_index;

	वापस 0;

err_loopback_op:
	mlxsw_sp_ul_rअगर_put(ul_rअगर);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp2_rअगर_ipip_lb_deconfigure(काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा mlxsw_sp_rअगर_ipip_lb *lb_rअगर = mlxsw_sp_rअगर_ipip_lb_rअगर(rअगर);
	काष्ठा mlxsw_sp *mlxsw_sp = rअगर->mlxsw_sp;
	काष्ठा mlxsw_sp_rअगर *ul_rअगर;

	ul_rअगर = mlxsw_sp_rअगर_by_index(mlxsw_sp, lb_rअगर->ul_rअगर_id);
	mlxsw_sp_rअगर_ipip_lb_op(lb_rअगर, 0, lb_rअगर->ul_rअगर_id, false);
	mlxsw_sp_ul_rअगर_put(ul_rअगर);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_rअगर_ops mlxsw_sp2_rअगर_ipip_lb_ops = अणु
	.type			= MLXSW_SP_RIF_TYPE_IPIP_LB,
	.rअगर_size		= माप(काष्ठा mlxsw_sp_rअगर_ipip_lb),
	.setup                  = mlxsw_sp_rअगर_ipip_lb_setup,
	.configure		= mlxsw_sp2_rअगर_ipip_lb_configure,
	.deconfigure		= mlxsw_sp2_rअगर_ipip_lb_deconfigure,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_rअगर_ops *mlxsw_sp2_rअगर_ops_arr[] = अणु
	[MLXSW_SP_RIF_TYPE_SUBPORT]	= &mlxsw_sp_rअगर_subport_ops,
	[MLXSW_SP_RIF_TYPE_VLAN]	= &mlxsw_sp_rअगर_vlan_emu_ops,
	[MLXSW_SP_RIF_TYPE_FID]		= &mlxsw_sp_rअगर_fid_ops,
	[MLXSW_SP_RIF_TYPE_IPIP_LB]	= &mlxsw_sp2_rअगर_ipip_lb_ops,
पूर्ण;

अटल पूर्णांक mlxsw_sp_rअगरs_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	u64 max_rअगरs = MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS);

	mlxsw_sp->router->rअगरs = kसुस्मृति(max_rअगरs,
					 माप(काष्ठा mlxsw_sp_rअगर *),
					 GFP_KERNEL);
	अगर (!mlxsw_sp->router->rअगरs)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_rअगरs_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS); i++)
		WARN_ON_ONCE(mlxsw_sp->router->rअगरs[i]);

	kमुक्त(mlxsw_sp->router->rअगरs);
पूर्ण

अटल पूर्णांक
mlxsw_sp_ipip_config_tigcr(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अक्षर tigcr_pl[MLXSW_REG_TIGCR_LEN];

	mlxsw_reg_tigcr_pack(tigcr_pl, true, 0);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(tigcr), tigcr_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_ipips_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	पूर्णांक err;

	mlxsw_sp->router->ipip_ops_arr = mlxsw_sp_ipip_ops_arr;
	INIT_LIST_HEAD(&mlxsw_sp->router->ipip_list);

	err = mlxsw_sp_ipip_ecn_encap_init(mlxsw_sp);
	अगर (err)
		वापस err;
	err = mlxsw_sp_ipip_ecn_decap_init(mlxsw_sp);
	अगर (err)
		वापस err;

	वापस mlxsw_sp_ipip_config_tigcr(mlxsw_sp);
पूर्ण

अटल व्योम mlxsw_sp_ipips_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	WARN_ON(!list_empty(&mlxsw_sp->router->ipip_list));
पूर्ण

अटल व्योम mlxsw_sp_router_fib_dump_flush(काष्ठा notअगरier_block *nb)
अणु
	काष्ठा mlxsw_sp_router *router;

	/* Flush pending FIB notअगरications and then flush the device's
	 * table beक्रमe requesting another dump. The FIB notअगरication
	 * block is unरेजिस्टरed, so no need to take RTNL.
	 */
	mlxsw_core_flush_owq();
	router = container_of(nb, काष्ठा mlxsw_sp_router, fib_nb);
	mlxsw_sp_router_fib_flush(router->mlxsw_sp);
पूर्ण

#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
अटल व्योम mlxsw_sp_mp_hash_header_set(अक्षर *recr2_pl, पूर्णांक header)
अणु
	mlxsw_reg_recr2_outer_header_enables_set(recr2_pl, header, true);
पूर्ण

अटल व्योम mlxsw_sp_mp_hash_field_set(अक्षर *recr2_pl, पूर्णांक field)
अणु
	mlxsw_reg_recr2_outer_header_fields_enable_set(recr2_pl, field, true);
पूर्ण

अटल व्योम mlxsw_sp_mp4_hash_init(काष्ठा mlxsw_sp *mlxsw_sp, अक्षर *recr2_pl)
अणु
	काष्ठा net *net = mlxsw_sp_net(mlxsw_sp);
	bool only_l3 = !net->ipv4.sysctl_fib_multipath_hash_policy;

	mlxsw_sp_mp_hash_header_set(recr2_pl,
				    MLXSW_REG_RECR2_IPV4_EN_NOT_TCP_NOT_UDP);
	mlxsw_sp_mp_hash_header_set(recr2_pl, MLXSW_REG_RECR2_IPV4_EN_TCP_UDP);
	mlxsw_reg_recr2_ipv4_sip_enable(recr2_pl);
	mlxsw_reg_recr2_ipv4_dip_enable(recr2_pl);
	अगर (only_l3)
		वापस;
	mlxsw_sp_mp_hash_header_set(recr2_pl, MLXSW_REG_RECR2_TCP_UDP_EN_IPV4);
	mlxsw_sp_mp_hash_field_set(recr2_pl, MLXSW_REG_RECR2_IPV4_PROTOCOL);
	mlxsw_sp_mp_hash_field_set(recr2_pl, MLXSW_REG_RECR2_TCP_UDP_SPORT);
	mlxsw_sp_mp_hash_field_set(recr2_pl, MLXSW_REG_RECR2_TCP_UDP_DPORT);
पूर्ण

अटल व्योम mlxsw_sp_mp6_hash_init(काष्ठा mlxsw_sp *mlxsw_sp, अक्षर *recr2_pl)
अणु
	bool only_l3 = !ip6_multipath_hash_policy(mlxsw_sp_net(mlxsw_sp));

	mlxsw_sp_mp_hash_header_set(recr2_pl,
				    MLXSW_REG_RECR2_IPV6_EN_NOT_TCP_NOT_UDP);
	mlxsw_sp_mp_hash_header_set(recr2_pl, MLXSW_REG_RECR2_IPV6_EN_TCP_UDP);
	mlxsw_reg_recr2_ipv6_sip_enable(recr2_pl);
	mlxsw_reg_recr2_ipv6_dip_enable(recr2_pl);
	mlxsw_sp_mp_hash_field_set(recr2_pl, MLXSW_REG_RECR2_IPV6_NEXT_HEADER);
	अगर (only_l3) अणु
		mlxsw_sp_mp_hash_field_set(recr2_pl,
					   MLXSW_REG_RECR2_IPV6_FLOW_LABEL);
	पूर्ण अन्यथा अणु
		mlxsw_sp_mp_hash_header_set(recr2_pl,
					    MLXSW_REG_RECR2_TCP_UDP_EN_IPV6);
		mlxsw_sp_mp_hash_field_set(recr2_pl,
					   MLXSW_REG_RECR2_TCP_UDP_SPORT);
		mlxsw_sp_mp_hash_field_set(recr2_pl,
					   MLXSW_REG_RECR2_TCP_UDP_DPORT);
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_mp_hash_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अक्षर recr2_pl[MLXSW_REG_RECR2_LEN];
	u32 seed;

	seed = jhash(mlxsw_sp->base_mac, माप(mlxsw_sp->base_mac), 0);
	mlxsw_reg_recr2_pack(recr2_pl, seed);
	mlxsw_sp_mp4_hash_init(mlxsw_sp, recr2_pl);
	mlxsw_sp_mp6_hash_init(mlxsw_sp, recr2_pl);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(recr2), recr2_pl);
पूर्ण
#अन्यथा
अटल पूर्णांक mlxsw_sp_mp_hash_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mlxsw_sp_dscp_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अक्षर rdpm_pl[MLXSW_REG_RDPM_LEN];
	अचिन्हित पूर्णांक i;

	MLXSW_REG_ZERO(rdpm, rdpm_pl);

	/* HW is determining चयन priority based on DSCP-bits, but the
	 * kernel is still करोing that based on the ToS. Since there's a
	 * mismatch in bits we need to make sure to translate the right
	 * value ToS would observe, skipping the 2 least-signअगरicant ECN bits.
	 */
	क्रम (i = 0; i < MLXSW_REG_RDPM_DSCP_ENTRY_REC_MAX_COUNT; i++)
		mlxsw_reg_rdpm_pack(rdpm_pl, i, rt_tos2priority(i << 2));

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rdpm), rdpm_pl);
पूर्ण

अटल पूर्णांक __mlxsw_sp_router_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा net *net = mlxsw_sp_net(mlxsw_sp);
	bool usp = net->ipv4.sysctl_ip_fwd_update_priority;
	अक्षर rgcr_pl[MLXSW_REG_RGCR_LEN];
	u64 max_rअगरs;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, MAX_RIFS))
		वापस -EIO;
	max_rअगरs = MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS);

	mlxsw_reg_rgcr_pack(rgcr_pl, true, true);
	mlxsw_reg_rgcr_max_router_पूर्णांकerfaces_set(rgcr_pl, max_rअगरs);
	mlxsw_reg_rgcr_usp_set(rgcr_pl, usp);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rgcr), rgcr_pl);
पूर्ण

अटल व्योम __mlxsw_sp_router_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अक्षर rgcr_pl[MLXSW_REG_RGCR_LEN];

	mlxsw_reg_rgcr_pack(rgcr_pl, false, false);
	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rgcr), rgcr_pl);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_router_ll_ops mlxsw_sp_router_ll_basic_ops = अणु
	.init = mlxsw_sp_router_ll_basic_init,
	.ralta_ग_लिखो = mlxsw_sp_router_ll_basic_ralta_ग_लिखो,
	.ralst_ग_लिखो = mlxsw_sp_router_ll_basic_ralst_ग_लिखो,
	.raltb_ग_लिखो = mlxsw_sp_router_ll_basic_raltb_ग_लिखो,
	.fib_entry_op_ctx_size = माप(काष्ठा mlxsw_sp_fib_entry_op_ctx_basic),
	.fib_entry_pack = mlxsw_sp_router_ll_basic_fib_entry_pack,
	.fib_entry_act_remote_pack = mlxsw_sp_router_ll_basic_fib_entry_act_remote_pack,
	.fib_entry_act_local_pack = mlxsw_sp_router_ll_basic_fib_entry_act_local_pack,
	.fib_entry_act_ip2me_pack = mlxsw_sp_router_ll_basic_fib_entry_act_ip2me_pack,
	.fib_entry_act_ip2me_tun_pack = mlxsw_sp_router_ll_basic_fib_entry_act_ip2me_tun_pack,
	.fib_entry_commit = mlxsw_sp_router_ll_basic_fib_entry_commit,
	.fib_entry_is_committed = mlxsw_sp_router_ll_basic_fib_entry_is_committed,
पूर्ण;

अटल पूर्णांक mlxsw_sp_router_ll_op_ctx_init(काष्ठा mlxsw_sp_router *router)
अणु
	माप_प्रकार max_size = 0;
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP_L3_PROTO_MAX; i++) अणु
		माप_प्रकार size = router->proto_ll_ops[i]->fib_entry_op_ctx_size;

		अगर (size > max_size)
			max_size = size;
	पूर्ण
	router->ll_op_ctx = kzalloc(माप(*router->ll_op_ctx) + max_size,
				    GFP_KERNEL);
	अगर (!router->ll_op_ctx)
		वापस -ENOMEM;
	INIT_LIST_HEAD(&router->ll_op_ctx->fib_entry_priv_list);
	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_router_ll_op_ctx_fini(काष्ठा mlxsw_sp_router *router)
अणु
	WARN_ON(!list_empty(&router->ll_op_ctx->fib_entry_priv_list));
	kमुक्त(router->ll_op_ctx);
पूर्ण

अटल पूर्णांक mlxsw_sp_lb_rअगर_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	u16 lb_rअगर_index;
	पूर्णांक err;

	/* Create a generic loopback RIF associated with the मुख्य table
	 * (शेष VRF). Any table can be used, but the मुख्य table exists
	 * anyway, so we करो not waste resources.
	 */
	err = mlxsw_sp_router_ul_rअगर_get(mlxsw_sp, RT_TABLE_MAIN,
					 &lb_rअगर_index);
	अगर (err)
		वापस err;

	mlxsw_sp->router->lb_rअगर_index = lb_rअगर_index;

	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_lb_rअगर_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	mlxsw_sp_router_ul_rअगर_put(mlxsw_sp, mlxsw_sp->router->lb_rअगर_index);
पूर्ण

अटल पूर्णांक mlxsw_sp1_router_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	माप_प्रकार size_ranges_count = ARRAY_SIZE(mlxsw_sp1_adj_grp_size_ranges);

	mlxsw_sp->router->rअगर_ops_arr = mlxsw_sp1_rअगर_ops_arr;
	mlxsw_sp->router->adj_grp_size_ranges = mlxsw_sp1_adj_grp_size_ranges;
	mlxsw_sp->router->adj_grp_size_ranges_count = size_ranges_count;

	वापस 0;
पूर्ण

स्थिर काष्ठा mlxsw_sp_router_ops mlxsw_sp1_router_ops = अणु
	.init = mlxsw_sp1_router_init,
पूर्ण;

अटल पूर्णांक mlxsw_sp2_router_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	माप_प्रकार size_ranges_count = ARRAY_SIZE(mlxsw_sp2_adj_grp_size_ranges);

	mlxsw_sp->router->rअगर_ops_arr = mlxsw_sp2_rअगर_ops_arr;
	mlxsw_sp->router->adj_grp_size_ranges = mlxsw_sp2_adj_grp_size_ranges;
	mlxsw_sp->router->adj_grp_size_ranges_count = size_ranges_count;

	वापस 0;
पूर्ण

स्थिर काष्ठा mlxsw_sp_router_ops mlxsw_sp2_router_ops = अणु
	.init = mlxsw_sp2_router_init,
पूर्ण;

पूर्णांक mlxsw_sp_router_init(काष्ठा mlxsw_sp *mlxsw_sp,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_router *router;
	पूर्णांक err;

	router = kzalloc(माप(*mlxsw_sp->router), GFP_KERNEL);
	अगर (!router)
		वापस -ENOMEM;
	mutex_init(&router->lock);
	mlxsw_sp->router = router;
	router->mlxsw_sp = mlxsw_sp;

	err = mlxsw_sp->router_ops->init(mlxsw_sp);
	अगर (err)
		जाओ err_router_ops_init;

	err = mlxsw_sp_router_xm_init(mlxsw_sp);
	अगर (err)
		जाओ err_xm_init;

	router->proto_ll_ops[MLXSW_SP_L3_PROTO_IPV4] = mlxsw_sp_router_xm_ipv4_is_supported(mlxsw_sp) ?
						       &mlxsw_sp_router_ll_xm_ops :
						       &mlxsw_sp_router_ll_basic_ops;
	router->proto_ll_ops[MLXSW_SP_L3_PROTO_IPV6] = &mlxsw_sp_router_ll_basic_ops;

	err = mlxsw_sp_router_ll_op_ctx_init(router);
	अगर (err)
		जाओ err_ll_op_ctx_init;

	INIT_LIST_HEAD(&mlxsw_sp->router->nh_res_grp_list);
	INIT_DELAYED_WORK(&mlxsw_sp->router->nh_grp_activity_dw,
			  mlxsw_sp_nh_grp_activity_work);

	INIT_LIST_HEAD(&mlxsw_sp->router->nexthop_neighs_list);
	err = __mlxsw_sp_router_init(mlxsw_sp);
	अगर (err)
		जाओ err_router_init;

	err = mlxsw_sp_rअगरs_init(mlxsw_sp);
	अगर (err)
		जाओ err_rअगरs_init;

	err = mlxsw_sp_ipips_init(mlxsw_sp);
	अगर (err)
		जाओ err_ipips_init;

	err = rhashtable_init(&mlxsw_sp->router->nexthop_ht,
			      &mlxsw_sp_nexthop_ht_params);
	अगर (err)
		जाओ err_nexthop_ht_init;

	err = rhashtable_init(&mlxsw_sp->router->nexthop_group_ht,
			      &mlxsw_sp_nexthop_group_ht_params);
	अगर (err)
		जाओ err_nexthop_group_ht_init;

	INIT_LIST_HEAD(&mlxsw_sp->router->nexthop_list);
	err = mlxsw_sp_lpm_init(mlxsw_sp);
	अगर (err)
		जाओ err_lpm_init;

	err = mlxsw_sp_mr_init(mlxsw_sp, &mlxsw_sp_mr_tcam_ops);
	अगर (err)
		जाओ err_mr_init;

	err = mlxsw_sp_vrs_init(mlxsw_sp);
	अगर (err)
		जाओ err_vrs_init;

	err = mlxsw_sp_lb_rअगर_init(mlxsw_sp);
	अगर (err)
		जाओ err_lb_rअगर_init;

	err = mlxsw_sp_neigh_init(mlxsw_sp);
	अगर (err)
		जाओ err_neigh_init;

	err = mlxsw_sp_mp_hash_init(mlxsw_sp);
	अगर (err)
		जाओ err_mp_hash_init;

	err = mlxsw_sp_dscp_init(mlxsw_sp);
	अगर (err)
		जाओ err_dscp_init;

	INIT_WORK(&router->fib_event_work, mlxsw_sp_router_fib_event_work);
	INIT_LIST_HEAD(&router->fib_event_queue);
	spin_lock_init(&router->fib_event_queue_lock);

	router->inetaddr_nb.notअगरier_call = mlxsw_sp_inetaddr_event;
	err = रेजिस्टर_inetaddr_notअगरier(&router->inetaddr_nb);
	अगर (err)
		जाओ err_रेजिस्टर_inetaddr_notअगरier;

	router->inet6addr_nb.notअगरier_call = mlxsw_sp_inet6addr_event;
	err = रेजिस्टर_inet6addr_notअगरier(&router->inet6addr_nb);
	अगर (err)
		जाओ err_रेजिस्टर_inet6addr_notअगरier;

	mlxsw_sp->router->netevent_nb.notअगरier_call =
		mlxsw_sp_router_netevent_event;
	err = रेजिस्टर_netevent_notअगरier(&mlxsw_sp->router->netevent_nb);
	अगर (err)
		जाओ err_रेजिस्टर_netevent_notअगरier;

	mlxsw_sp->router->nexthop_nb.notअगरier_call =
		mlxsw_sp_nexthop_obj_event;
	err = रेजिस्टर_nexthop_notअगरier(mlxsw_sp_net(mlxsw_sp),
					&mlxsw_sp->router->nexthop_nb,
					extack);
	अगर (err)
		जाओ err_रेजिस्टर_nexthop_notअगरier;

	mlxsw_sp->router->fib_nb.notअगरier_call = mlxsw_sp_router_fib_event;
	err = रेजिस्टर_fib_notअगरier(mlxsw_sp_net(mlxsw_sp),
				    &mlxsw_sp->router->fib_nb,
				    mlxsw_sp_router_fib_dump_flush, extack);
	अगर (err)
		जाओ err_रेजिस्टर_fib_notअगरier;

	वापस 0;

err_रेजिस्टर_fib_notअगरier:
	unरेजिस्टर_nexthop_notअगरier(mlxsw_sp_net(mlxsw_sp),
				    &mlxsw_sp->router->nexthop_nb);
err_रेजिस्टर_nexthop_notअगरier:
	unरेजिस्टर_netevent_notअगरier(&mlxsw_sp->router->netevent_nb);
err_रेजिस्टर_netevent_notअगरier:
	unरेजिस्टर_inet6addr_notअगरier(&router->inet6addr_nb);
err_रेजिस्टर_inet6addr_notअगरier:
	unरेजिस्टर_inetaddr_notअगरier(&router->inetaddr_nb);
err_रेजिस्टर_inetaddr_notअगरier:
	mlxsw_core_flush_owq();
	WARN_ON(!list_empty(&router->fib_event_queue));
err_dscp_init:
err_mp_hash_init:
	mlxsw_sp_neigh_fini(mlxsw_sp);
err_neigh_init:
	mlxsw_sp_lb_rअगर_fini(mlxsw_sp);
err_lb_rअगर_init:
	mlxsw_sp_vrs_fini(mlxsw_sp);
err_vrs_init:
	mlxsw_sp_mr_fini(mlxsw_sp);
err_mr_init:
	mlxsw_sp_lpm_fini(mlxsw_sp);
err_lpm_init:
	rhashtable_destroy(&mlxsw_sp->router->nexthop_group_ht);
err_nexthop_group_ht_init:
	rhashtable_destroy(&mlxsw_sp->router->nexthop_ht);
err_nexthop_ht_init:
	mlxsw_sp_ipips_fini(mlxsw_sp);
err_ipips_init:
	mlxsw_sp_rअगरs_fini(mlxsw_sp);
err_rअगरs_init:
	__mlxsw_sp_router_fini(mlxsw_sp);
err_router_init:
	cancel_delayed_work_sync(&mlxsw_sp->router->nh_grp_activity_dw);
	mlxsw_sp_router_ll_op_ctx_fini(router);
err_ll_op_ctx_init:
	mlxsw_sp_router_xm_fini(mlxsw_sp);
err_xm_init:
err_router_ops_init:
	mutex_destroy(&mlxsw_sp->router->lock);
	kमुक्त(mlxsw_sp->router);
	वापस err;
पूर्ण

व्योम mlxsw_sp_router_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	unरेजिस्टर_fib_notअगरier(mlxsw_sp_net(mlxsw_sp),
				&mlxsw_sp->router->fib_nb);
	unरेजिस्टर_nexthop_notअगरier(mlxsw_sp_net(mlxsw_sp),
				    &mlxsw_sp->router->nexthop_nb);
	unरेजिस्टर_netevent_notअगरier(&mlxsw_sp->router->netevent_nb);
	unरेजिस्टर_inet6addr_notअगरier(&mlxsw_sp->router->inet6addr_nb);
	unरेजिस्टर_inetaddr_notअगरier(&mlxsw_sp->router->inetaddr_nb);
	mlxsw_core_flush_owq();
	WARN_ON(!list_empty(&mlxsw_sp->router->fib_event_queue));
	mlxsw_sp_neigh_fini(mlxsw_sp);
	mlxsw_sp_lb_rअगर_fini(mlxsw_sp);
	mlxsw_sp_vrs_fini(mlxsw_sp);
	mlxsw_sp_mr_fini(mlxsw_sp);
	mlxsw_sp_lpm_fini(mlxsw_sp);
	rhashtable_destroy(&mlxsw_sp->router->nexthop_group_ht);
	rhashtable_destroy(&mlxsw_sp->router->nexthop_ht);
	mlxsw_sp_ipips_fini(mlxsw_sp);
	mlxsw_sp_rअगरs_fini(mlxsw_sp);
	__mlxsw_sp_router_fini(mlxsw_sp);
	cancel_delayed_work_sync(&mlxsw_sp->router->nh_grp_activity_dw);
	mlxsw_sp_router_ll_op_ctx_fini(mlxsw_sp->router);
	mlxsw_sp_router_xm_fini(mlxsw_sp);
	mutex_destroy(&mlxsw_sp->router->lock);
	kमुक्त(mlxsw_sp->router);
पूर्ण
