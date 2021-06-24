<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2020 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/rhashtable.h>

#समावेश "spectrum.h"
#समावेश "core.h"
#समावेश "reg.h"
#समावेश "spectrum_router.h"

#घोषणा MLXSW_SP_ROUTER_XM_M_VAL 16

अटल स्थिर u8 mlxsw_sp_router_xm_m_val[] = अणु
	[MLXSW_SP_L3_PROTO_IPV4] = MLXSW_SP_ROUTER_XM_M_VAL,
	[MLXSW_SP_L3_PROTO_IPV6] = 0, /* Currently unused. */
पूर्ण;

#घोषणा MLXSW_SP_ROUTER_XM_L_VAL_MAX 16

काष्ठा mlxsw_sp_router_xm अणु
	bool ipv4_supported;
	bool ipv6_supported;
	अचिन्हित पूर्णांक entries_size;
	काष्ठा rhashtable ltable_ht;
	काष्ठा rhashtable flush_ht; /* Stores items about to be flushed from cache */
	अचिन्हित पूर्णांक flush_count;
	bool flush_all_mode;
पूर्ण;

काष्ठा mlxsw_sp_router_xm_ltable_node अणु
	काष्ठा rhash_head ht_node; /* Member of router_xm->ltable_ht */
	u16 mindex;
	u8 current_lvalue;
	refcount_t refcnt;
	अचिन्हित पूर्णांक lvalue_ref[MLXSW_SP_ROUTER_XM_L_VAL_MAX + 1];
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_router_xm_ltable_ht_params = अणु
	.key_offset = दुरत्व(काष्ठा mlxsw_sp_router_xm_ltable_node, mindex),
	.head_offset = दुरत्व(काष्ठा mlxsw_sp_router_xm_ltable_node, ht_node),
	.key_len = माप(u16),
	.स्वतःmatic_shrinking = true,
पूर्ण;

काष्ठा mlxsw_sp_router_xm_flush_info अणु
	bool all;
	क्रमागत mlxsw_sp_l3proto proto;
	u16 भव_router;
	u8 prefix_len;
	अचिन्हित अक्षर addr[माप(काष्ठा in6_addr)];
पूर्ण;

काष्ठा mlxsw_sp_router_xm_fib_entry अणु
	bool committed;
	काष्ठा mlxsw_sp_router_xm_ltable_node *ltable_node; /* Parent node */
	u16 mindex; /* Store क्रम processing from commit op */
	u8 lvalue;
	काष्ठा mlxsw_sp_router_xm_flush_info flush_info;
पूर्ण;

#घोषणा MLXSW_SP_ROUTE_LL_XM_ENTRIES_MAX \
	(MLXSW_REG_XMDR_TRANS_LEN / MLXSW_REG_XMDR_C_LT_ROUTE_V4_LEN)

काष्ठा mlxsw_sp_fib_entry_op_ctx_xm अणु
	bool initialized;
	अक्षर xmdr_pl[MLXSW_REG_XMDR_LEN];
	अचिन्हित पूर्णांक trans_offset; /* Offset of the current command within one
				    * transaction of XMDR रेजिस्टर.
				    */
	अचिन्हित पूर्णांक trans_item_len; /* The current command length. This is used
				      * to advance 'trans_offset' when the next
				      * command is appended.
				      */
	अचिन्हित पूर्णांक entries_count;
	काष्ठा mlxsw_sp_router_xm_fib_entry *entries[MLXSW_SP_ROUTE_LL_XM_ENTRIES_MAX];
पूर्ण;

अटल पूर्णांक mlxsw_sp_router_ll_xm_init(काष्ठा mlxsw_sp *mlxsw_sp, u16 vr_id,
				      क्रमागत mlxsw_sp_l3proto proto)
अणु
	अक्षर rxlte_pl[MLXSW_REG_RXLTE_LEN];

	mlxsw_reg_rxlte_pack(rxlte_pl, vr_id,
			     (क्रमागत mlxsw_reg_rxlte_protocol) proto, true);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rxlte), rxlte_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_router_ll_xm_ralta_ग_लिखो(काष्ठा mlxsw_sp *mlxsw_sp, अक्षर *xralta_pl)
अणु
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(xralta), xralta_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_router_ll_xm_ralst_ग_लिखो(काष्ठा mlxsw_sp *mlxsw_sp, अक्षर *xralst_pl)
अणु
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(xralst), xralst_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp_router_ll_xm_raltb_ग_लिखो(काष्ठा mlxsw_sp *mlxsw_sp, अक्षर *xraltb_pl)
अणु
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(xraltb), xraltb_pl);
पूर्ण

अटल u16 mlxsw_sp_router_ll_xm_mindex_get4(स्थिर u32 addr)
अणु
	/* Currently the M-index is set to linear mode. That means it is defined
	 * as 16 MSB of IP address.
	 */
	वापस addr >> MLXSW_SP_ROUTER_XM_L_VAL_MAX;
पूर्ण

अटल u16 mlxsw_sp_router_ll_xm_mindex_get6(स्थिर अचिन्हित अक्षर *addr)
अणु
	WARN_ON_ONCE(1);
	वापस 0; /* currently unused */
पूर्ण

अटल व्योम mlxsw_sp_router_ll_xm_op_ctx_check_init(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
						    काष्ठा mlxsw_sp_fib_entry_op_ctx_xm *op_ctx_xm)
अणु
	अगर (op_ctx->initialized)
		वापस;
	op_ctx->initialized = true;

	mlxsw_reg_xmdr_pack(op_ctx_xm->xmdr_pl, true);
	op_ctx_xm->trans_offset = 0;
	op_ctx_xm->entries_count = 0;
पूर्ण

अटल व्योम mlxsw_sp_router_ll_xm_fib_entry_pack(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
						 क्रमागत mlxsw_sp_l3proto proto,
						 क्रमागत mlxsw_sp_fib_entry_op op,
						 u16 भव_router, u8 prefix_len,
						 अचिन्हित अक्षर *addr,
						 काष्ठा mlxsw_sp_fib_entry_priv *priv)
अणु
	काष्ठा mlxsw_sp_fib_entry_op_ctx_xm *op_ctx_xm = (व्योम *) op_ctx->ll_priv;
	काष्ठा mlxsw_sp_router_xm_fib_entry *fib_entry = (व्योम *) priv->priv;
	काष्ठा mlxsw_sp_router_xm_flush_info *flush_info;
	क्रमागत mlxsw_reg_xmdr_c_ltr_op xmdr_c_ltr_op;
	अचिन्हित पूर्णांक len;

	mlxsw_sp_router_ll_xm_op_ctx_check_init(op_ctx, op_ctx_xm);

	चयन (op) अणु
	हाल MLXSW_SP_FIB_ENTRY_OP_WRITE:
		xmdr_c_ltr_op = MLXSW_REG_XMDR_C_LTR_OP_WRITE;
		अवरोध;
	हाल MLXSW_SP_FIB_ENTRY_OP_UPDATE:
		xmdr_c_ltr_op = MLXSW_REG_XMDR_C_LTR_OP_UPDATE;
		अवरोध;
	हाल MLXSW_SP_FIB_ENTRY_OP_DELETE:
		xmdr_c_ltr_op = MLXSW_REG_XMDR_C_LTR_OP_DELETE;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	चयन (proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		len = mlxsw_reg_xmdr_c_ltr_pack4(op_ctx_xm->xmdr_pl, op_ctx_xm->trans_offset,
						 op_ctx_xm->entries_count, xmdr_c_ltr_op,
						 भव_router, prefix_len, (u32 *) addr);
		fib_entry->mindex = mlxsw_sp_router_ll_xm_mindex_get4(*((u32 *) addr));
		अवरोध;
	हाल MLXSW_SP_L3_PROTO_IPV6:
		len = mlxsw_reg_xmdr_c_ltr_pack6(op_ctx_xm->xmdr_pl, op_ctx_xm->trans_offset,
						 op_ctx_xm->entries_count, xmdr_c_ltr_op,
						 भव_router, prefix_len, addr);
		fib_entry->mindex = mlxsw_sp_router_ll_xm_mindex_get6(addr);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण
	अगर (!op_ctx_xm->trans_offset)
		op_ctx_xm->trans_item_len = len;
	अन्यथा
		WARN_ON_ONCE(op_ctx_xm->trans_item_len != len);

	op_ctx_xm->entries[op_ctx_xm->entries_count] = fib_entry;

	fib_entry->lvalue = prefix_len > mlxsw_sp_router_xm_m_val[proto] ?
			       prefix_len - mlxsw_sp_router_xm_m_val[proto] : 0;

	flush_info = &fib_entry->flush_info;
	flush_info->proto = proto;
	flush_info->भव_router = भव_router;
	flush_info->prefix_len = prefix_len;
	अगर (addr)
		स_नकल(flush_info->addr, addr, माप(flush_info->addr));
	अन्यथा
		स_रखो(flush_info->addr, 0, माप(flush_info->addr));
पूर्ण

अटल व्योम
mlxsw_sp_router_ll_xm_fib_entry_act_remote_pack(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
						क्रमागत mlxsw_reg_ralue_trap_action trap_action,
						u16 trap_id, u32 adjacency_index, u16 ecmp_size)
अणु
	काष्ठा mlxsw_sp_fib_entry_op_ctx_xm *op_ctx_xm = (व्योम *) op_ctx->ll_priv;

	mlxsw_reg_xmdr_c_ltr_act_remote_pack(op_ctx_xm->xmdr_pl, op_ctx_xm->trans_offset,
					     trap_action, trap_id, adjacency_index, ecmp_size);
पूर्ण

अटल व्योम
mlxsw_sp_router_ll_xm_fib_entry_act_local_pack(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
					      क्रमागत mlxsw_reg_ralue_trap_action trap_action,
					       u16 trap_id, u16 local_erअगर)
अणु
	काष्ठा mlxsw_sp_fib_entry_op_ctx_xm *op_ctx_xm = (व्योम *) op_ctx->ll_priv;

	mlxsw_reg_xmdr_c_ltr_act_local_pack(op_ctx_xm->xmdr_pl, op_ctx_xm->trans_offset,
					    trap_action, trap_id, local_erअगर);
पूर्ण

अटल व्योम
mlxsw_sp_router_ll_xm_fib_entry_act_ip2me_pack(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx)
अणु
	काष्ठा mlxsw_sp_fib_entry_op_ctx_xm *op_ctx_xm = (व्योम *) op_ctx->ll_priv;

	mlxsw_reg_xmdr_c_ltr_act_ip2me_pack(op_ctx_xm->xmdr_pl, op_ctx_xm->trans_offset);
पूर्ण

अटल व्योम
mlxsw_sp_router_ll_xm_fib_entry_act_ip2me_tun_pack(काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
						   u32 tunnel_ptr)
अणु
	काष्ठा mlxsw_sp_fib_entry_op_ctx_xm *op_ctx_xm = (व्योम *) op_ctx->ll_priv;

	mlxsw_reg_xmdr_c_ltr_act_ip2me_tun_pack(op_ctx_xm->xmdr_pl, op_ctx_xm->trans_offset,
						tunnel_ptr);
पूर्ण

अटल काष्ठा mlxsw_sp_router_xm_ltable_node *
mlxsw_sp_router_xm_ltable_node_get(काष्ठा mlxsw_sp_router_xm *router_xm, u16 mindex)
अणु
	काष्ठा mlxsw_sp_router_xm_ltable_node *ltable_node;
	पूर्णांक err;

	ltable_node = rhashtable_lookup_fast(&router_xm->ltable_ht, &mindex,
					     mlxsw_sp_router_xm_ltable_ht_params);
	अगर (ltable_node) अणु
		refcount_inc(&ltable_node->refcnt);
		वापस ltable_node;
	पूर्ण
	ltable_node = kzalloc(माप(*ltable_node), GFP_KERNEL);
	अगर (!ltable_node)
		वापस ERR_PTR(-ENOMEM);
	ltable_node->mindex = mindex;
	refcount_set(&ltable_node->refcnt, 1);

	err = rhashtable_insert_fast(&router_xm->ltable_ht, &ltable_node->ht_node,
				     mlxsw_sp_router_xm_ltable_ht_params);
	अगर (err)
		जाओ err_insert;

	वापस ltable_node;

err_insert:
	kमुक्त(ltable_node);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_sp_router_xm_ltable_node_put(काष्ठा mlxsw_sp_router_xm *router_xm,
					       काष्ठा mlxsw_sp_router_xm_ltable_node *ltable_node)
अणु
	अगर (!refcount_dec_and_test(&ltable_node->refcnt))
		वापस;
	rhashtable_हटाओ_fast(&router_xm->ltable_ht, &ltable_node->ht_node,
			       mlxsw_sp_router_xm_ltable_ht_params);
	kमुक्त(ltable_node);
पूर्ण

अटल पूर्णांक mlxsw_sp_router_xm_ltable_lvalue_set(काष्ठा mlxsw_sp *mlxsw_sp,
						काष्ठा mlxsw_sp_router_xm_ltable_node *ltable_node)
अणु
	अक्षर xrmt_pl[MLXSW_REG_XRMT_LEN];

	mlxsw_reg_xrmt_pack(xrmt_pl, ltable_node->mindex, ltable_node->current_lvalue);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(xrmt), xrmt_pl);
पूर्ण

काष्ठा mlxsw_sp_router_xm_flush_node अणु
	काष्ठा rhash_head ht_node; /* Member of router_xm->flush_ht */
	काष्ठा list_head list;
	काष्ठा mlxsw_sp_router_xm_flush_info flush_info;
	काष्ठा delayed_work dw;
	काष्ठा mlxsw_sp *mlxsw_sp;
	अचिन्हित दीर्घ start_jअगरfies;
	अचिन्हित पूर्णांक reuses; /* By how many flush calls this was reused. */
	refcount_t refcnt;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_router_xm_flush_ht_params = अणु
	.key_offset = दुरत्व(काष्ठा mlxsw_sp_router_xm_flush_node, flush_info),
	.head_offset = दुरत्व(काष्ठा mlxsw_sp_router_xm_flush_node, ht_node),
	.key_len = माप(काष्ठा mlxsw_sp_router_xm_flush_info),
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल काष्ठा mlxsw_sp_router_xm_flush_node *
mlxsw_sp_router_xm_cache_flush_node_create(काष्ठा mlxsw_sp *mlxsw_sp,
					   काष्ठा mlxsw_sp_router_xm_flush_info *flush_info)
अणु
	काष्ठा mlxsw_sp_router_xm *router_xm = mlxsw_sp->router->xm;
	काष्ठा mlxsw_sp_router_xm_flush_node *flush_node;
	पूर्णांक err;

	flush_node = kzalloc(माप(*flush_node), GFP_KERNEL);
	अगर (!flush_node)
		वापस ERR_PTR(-ENOMEM);

	flush_node->flush_info = *flush_info;
	err = rhashtable_insert_fast(&router_xm->flush_ht, &flush_node->ht_node,
				     mlxsw_sp_router_xm_flush_ht_params);
	अगर (err) अणु
		kमुक्त(flush_node);
		वापस ERR_PTR(err);
	पूर्ण
	router_xm->flush_count++;
	flush_node->mlxsw_sp = mlxsw_sp;
	flush_node->start_jअगरfies = jअगरfies;
	refcount_set(&flush_node->refcnt, 1);
	वापस flush_node;
पूर्ण

अटल व्योम
mlxsw_sp_router_xm_cache_flush_node_hold(काष्ठा mlxsw_sp_router_xm_flush_node *flush_node)
अणु
	अगर (!flush_node)
		वापस;
	refcount_inc(&flush_node->refcnt);
पूर्ण

अटल व्योम
mlxsw_sp_router_xm_cache_flush_node_put(काष्ठा mlxsw_sp_router_xm_flush_node *flush_node)
अणु
	अगर (!flush_node || !refcount_dec_and_test(&flush_node->refcnt))
		वापस;
	kमुक्त(flush_node);
पूर्ण

अटल व्योम
mlxsw_sp_router_xm_cache_flush_node_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
					    काष्ठा mlxsw_sp_router_xm_flush_node *flush_node)
अणु
	काष्ठा mlxsw_sp_router_xm *router_xm = mlxsw_sp->router->xm;

	router_xm->flush_count--;
	rhashtable_हटाओ_fast(&router_xm->flush_ht, &flush_node->ht_node,
			       mlxsw_sp_router_xm_flush_ht_params);
	mlxsw_sp_router_xm_cache_flush_node_put(flush_node);
पूर्ण

अटल u32 mlxsw_sp_router_xm_flush_mask4(u8 prefix_len)
अणु
	वापस GENMASK(31, 32 - prefix_len);
पूर्ण

अटल अचिन्हित अक्षर *mlxsw_sp_router_xm_flush_mask6(u8 prefix_len)
अणु
	अटल अचिन्हित अक्षर mask[माप(काष्ठा in6_addr)];

	स_रखो(mask, 0, माप(mask));
	स_रखो(mask, 0xff, prefix_len / 8);
	mask[prefix_len / 8] = GENMASK(8, 8 - prefix_len % 8);
	वापस mask;
पूर्ण

#घोषणा MLXSW_SP_ROUTER_XM_CACHE_PARALLEL_FLUSHES_LIMIT 15
#घोषणा MLXSW_SP_ROUTER_XM_CACHE_FLUSH_ALL_MIN_REUSES 15
#घोषणा MLXSW_SP_ROUTER_XM_CACHE_DELAY 50 /* usecs */
#घोषणा MLXSW_SP_ROUTER_XM_CACHE_MAX_WAIT (MLXSW_SP_ROUTER_XM_CACHE_DELAY * 10)

अटल व्योम mlxsw_sp_router_xm_cache_flush_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_sp_router_xm_flush_info *flush_info;
	काष्ठा mlxsw_sp_router_xm_flush_node *flush_node;
	अक्षर rlcmld_pl[MLXSW_REG_RLCMLD_LEN];
	क्रमागत mlxsw_reg_rlcmld_select select;
	काष्ठा mlxsw_sp *mlxsw_sp;
	u32 addr4;
	पूर्णांक err;

	flush_node = container_of(work, काष्ठा mlxsw_sp_router_xm_flush_node,
				  dw.work);
	mlxsw_sp = flush_node->mlxsw_sp;
	flush_info = &flush_node->flush_info;

	अगर (flush_info->all) अणु
		अक्षर rlpmce_pl[MLXSW_REG_RLPMCE_LEN];

		mlxsw_reg_rlpmce_pack(rlpmce_pl, true, false);
		err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rlpmce),
				      rlpmce_pl);
		अगर (err)
			dev_err(mlxsw_sp->bus_info->dev, "Failed to flush XM cache\n");

		अगर (flush_node->reuses <
		    MLXSW_SP_ROUTER_XM_CACHE_FLUSH_ALL_MIN_REUSES)
			/* Leaving flush-all mode. */
			mlxsw_sp->router->xm->flush_all_mode = false;
		जाओ out;
	पूर्ण

	select = MLXSW_REG_RLCMLD_SELECT_M_AND_ML_ENTRIES;

	चयन (flush_info->proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		addr4 = *((u32 *) flush_info->addr);
		addr4 &= mlxsw_sp_router_xm_flush_mask4(flush_info->prefix_len);

		/* In हाल the flush prefix length is bigger than M-value,
		 * it makes no sense to flush M entries. So just flush
		 * the ML entries.
		 */
		अगर (flush_info->prefix_len > MLXSW_SP_ROUTER_XM_M_VAL)
			select = MLXSW_REG_RLCMLD_SELECT_ML_ENTRIES;

		mlxsw_reg_rlcmld_pack4(rlcmld_pl, select,
				       flush_info->भव_router, addr4,
				       mlxsw_sp_router_xm_flush_mask4(flush_info->prefix_len));
		अवरोध;
	हाल MLXSW_SP_L3_PROTO_IPV6:
		mlxsw_reg_rlcmld_pack6(rlcmld_pl, select,
				       flush_info->भव_router, flush_info->addr,
				       mlxsw_sp_router_xm_flush_mask6(flush_info->prefix_len));
		अवरोध;
	शेष:
		WARN_ON(true);
		जाओ out;
	पूर्ण
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rlcmld), rlcmld_pl);
	अगर (err)
		dev_err(mlxsw_sp->bus_info->dev, "Failed to flush XM cache\n");

out:
	mlxsw_sp_router_xm_cache_flush_node_destroy(mlxsw_sp, flush_node);
पूर्ण

अटल bool
mlxsw_sp_router_xm_cache_flush_may_cancel(काष्ठा mlxsw_sp_router_xm_flush_node *flush_node)
अणु
	अचिन्हित दीर्घ max_रुको = usecs_to_jअगरfies(MLXSW_SP_ROUTER_XM_CACHE_MAX_WAIT);
	अचिन्हित दीर्घ delay = usecs_to_jअगरfies(MLXSW_SP_ROUTER_XM_CACHE_DELAY);

	/* In हाल there is the same flushing work pending, check
	 * अगर we can consolidate with it. We can करो it up to MAX_WAIT.
	 * Cancel the delayed work. If the work was still pending.
	 */
	अगर (समय_is_beक्रमe_jअगरfies(flush_node->start_jअगरfies + max_रुको - delay) &&
	    cancel_delayed_work_sync(&flush_node->dw))
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक
mlxsw_sp_router_xm_cache_flush_schedule(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_router_xm_flush_info *flush_info)
अणु
	अचिन्हित दीर्घ delay = usecs_to_jअगरfies(MLXSW_SP_ROUTER_XM_CACHE_DELAY);
	काष्ठा mlxsw_sp_router_xm_flush_info flush_all_info = अणु.all = trueपूर्ण;
	काष्ठा mlxsw_sp_router_xm *router_xm = mlxsw_sp->router->xm;
	काष्ठा mlxsw_sp_router_xm_flush_node *flush_node;

	/* Check अगर the queued number of flushes reached critical amount after
	 * which it is better to just flush the whole cache.
	 */
	अगर (router_xm->flush_count == MLXSW_SP_ROUTER_XM_CACHE_PARALLEL_FLUSHES_LIMIT)
		/* Entering flush-all mode. */
		router_xm->flush_all_mode = true;

	अगर (router_xm->flush_all_mode)
		flush_info = &flush_all_info;

	rcu_पढ़ो_lock();
	flush_node = rhashtable_lookup_fast(&router_xm->flush_ht, flush_info,
					    mlxsw_sp_router_xm_flush_ht_params);
	/* Take a reference so the object is not मुक्तd beक्रमe possible
	 * delayed work cancel could be करोne.
	 */
	mlxsw_sp_router_xm_cache_flush_node_hold(flush_node);
	rcu_पढ़ो_unlock();

	अगर (flush_node && mlxsw_sp_router_xm_cache_flush_may_cancel(flush_node)) अणु
		flush_node->reuses++;
		mlxsw_sp_router_xm_cache_flush_node_put(flush_node);
		 /* Original work was within रुको period and was canceled.
		  * That means that the reference is still held and the
		  * flush_node_put() call above did not मुक्त the flush_node.
		  * Reschedule it with fresh delay.
		  */
		जाओ schedule_work;
	पूर्ण अन्यथा अणु
		mlxsw_sp_router_xm_cache_flush_node_put(flush_node);
	पूर्ण

	flush_node = mlxsw_sp_router_xm_cache_flush_node_create(mlxsw_sp, flush_info);
	अगर (IS_ERR(flush_node))
		वापस PTR_ERR(flush_node);
	INIT_DELAYED_WORK(&flush_node->dw, mlxsw_sp_router_xm_cache_flush_work);

schedule_work:
	mlxsw_core_schedule_dw(&flush_node->dw, delay);
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_router_xm_ml_entry_add(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_router_xm_fib_entry *fib_entry)
अणु
	काष्ठा mlxsw_sp_router_xm *router_xm = mlxsw_sp->router->xm;
	काष्ठा mlxsw_sp_router_xm_ltable_node *ltable_node;
	u8 lvalue = fib_entry->lvalue;
	पूर्णांक err;

	ltable_node = mlxsw_sp_router_xm_ltable_node_get(router_xm,
							 fib_entry->mindex);
	अगर (IS_ERR(ltable_node))
		वापस PTR_ERR(ltable_node);
	अगर (lvalue > ltable_node->current_lvalue) अणु
		/* The L-value is bigger then the one currently set, update. */
		ltable_node->current_lvalue = lvalue;
		err = mlxsw_sp_router_xm_ltable_lvalue_set(mlxsw_sp,
							   ltable_node);
		अगर (err)
			जाओ err_lvalue_set;

		/* The L value क्रम prefix/M is increased.
		 * Thereक्रमe, all entries in M and ML caches matching
		 * अणुprefix/M, proto, VRपूर्ण need to be flushed. Set the flush
		 * prefix length to M to achieve that.
		 */
		fib_entry->flush_info.prefix_len = MLXSW_SP_ROUTER_XM_M_VAL;
	पूर्ण

	ltable_node->lvalue_ref[lvalue]++;
	fib_entry->ltable_node = ltable_node;

	वापस 0;

err_lvalue_set:
	mlxsw_sp_router_xm_ltable_node_put(router_xm, ltable_node);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_router_xm_ml_entry_del(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_router_xm_fib_entry *fib_entry)
अणु
	काष्ठा mlxsw_sp_router_xm_ltable_node *ltable_node =
							fib_entry->ltable_node;
	काष्ठा mlxsw_sp_router_xm *router_xm = mlxsw_sp->router->xm;
	u8 lvalue = fib_entry->lvalue;

	ltable_node->lvalue_ref[lvalue]--;
	अगर (lvalue == ltable_node->current_lvalue && lvalue &&
	    !ltable_node->lvalue_ref[lvalue]) अणु
		u8 new_lvalue = lvalue - 1;

		/* Find the biggest L-value left out there. */
		जबतक (new_lvalue > 0 && !ltable_node->lvalue_ref[lvalue])
			new_lvalue--;

		ltable_node->current_lvalue = new_lvalue;
		mlxsw_sp_router_xm_ltable_lvalue_set(mlxsw_sp, ltable_node);

		/* The L value क्रम prefix/M is decreased.
		 * Thereक्रमe, all entries in M and ML caches matching
		 * अणुprefix/M, proto, VRपूर्ण need to be flushed. Set the flush
		 * prefix length to M to achieve that.
		 */
		fib_entry->flush_info.prefix_len = MLXSW_SP_ROUTER_XM_M_VAL;
	पूर्ण
	mlxsw_sp_router_xm_ltable_node_put(router_xm, ltable_node);
पूर्ण

अटल पूर्णांक
mlxsw_sp_router_xm_ml_entries_add(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_fib_entry_op_ctx_xm *op_ctx_xm)
अणु
	काष्ठा mlxsw_sp_router_xm_fib_entry *fib_entry;
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < op_ctx_xm->entries_count; i++) अणु
		fib_entry = op_ctx_xm->entries[i];
		err = mlxsw_sp_router_xm_ml_entry_add(mlxsw_sp, fib_entry);
		अगर (err)
			जाओ rollback;
	पूर्ण
	वापस 0;

rollback:
	क्रम (i--; i >= 0; i--) अणु
		fib_entry = op_ctx_xm->entries[i];
		mlxsw_sp_router_xm_ml_entry_del(mlxsw_sp, fib_entry);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_router_xm_ml_entries_del(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_fib_entry_op_ctx_xm *op_ctx_xm)
अणु
	काष्ठा mlxsw_sp_router_xm_fib_entry *fib_entry;
	पूर्णांक i;

	क्रम (i = 0; i < op_ctx_xm->entries_count; i++) अणु
		fib_entry = op_ctx_xm->entries[i];
		mlxsw_sp_router_xm_ml_entry_del(mlxsw_sp, fib_entry);
	पूर्ण
पूर्ण

अटल व्योम
mlxsw_sp_router_xm_ml_entries_cache_flush(काष्ठा mlxsw_sp *mlxsw_sp,
					  काष्ठा mlxsw_sp_fib_entry_op_ctx_xm *op_ctx_xm)
अणु
	काष्ठा mlxsw_sp_router_xm_fib_entry *fib_entry;
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < op_ctx_xm->entries_count; i++) अणु
		fib_entry = op_ctx_xm->entries[i];
		err = mlxsw_sp_router_xm_cache_flush_schedule(mlxsw_sp,
							      &fib_entry->flush_info);
		अगर (err)
			dev_err(mlxsw_sp->bus_info->dev, "Failed to flush XM cache\n");
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_router_ll_xm_fib_entry_commit(काष्ठा mlxsw_sp *mlxsw_sp,
						  काष्ठा mlxsw_sp_fib_entry_op_ctx *op_ctx,
						  bool *postponed_क्रम_bulk)
अणु
	काष्ठा mlxsw_sp_fib_entry_op_ctx_xm *op_ctx_xm = (व्योम *) op_ctx->ll_priv;
	काष्ठा mlxsw_sp_router_xm_fib_entry *fib_entry;
	u8 num_rec;
	पूर्णांक err;
	पूर्णांक i;

	op_ctx_xm->trans_offset += op_ctx_xm->trans_item_len;
	op_ctx_xm->entries_count++;

	/* Check अगर bulking is possible and there is still room क्रम another
	 * FIB entry record. The size of 'trans_item_len' is either size of IPv4
	 * command or size of IPv6 command. Not possible to mix those in a
	 * single XMDR ग_लिखो.
	 */
	अगर (op_ctx->bulk_ok &&
	    op_ctx_xm->trans_offset + op_ctx_xm->trans_item_len <= MLXSW_REG_XMDR_TRANS_LEN) अणु
		अगर (postponed_क्रम_bulk)
			*postponed_क्रम_bulk = true;
		वापस 0;
	पूर्ण

	अगर (op_ctx->event == FIB_EVENT_ENTRY_REPLACE) अणु
		/* The L-table is updated inside. It has to be करोne beक्रमe
		 * the prefix is inserted.
		 */
		err = mlxsw_sp_router_xm_ml_entries_add(mlxsw_sp, op_ctx_xm);
		अगर (err)
			जाओ out;
	पूर्ण

	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(xmdr), op_ctx_xm->xmdr_pl);
	अगर (err)
		जाओ out;
	num_rec = mlxsw_reg_xmdr_num_rec_get(op_ctx_xm->xmdr_pl);
	अगर (num_rec > op_ctx_xm->entries_count) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Invalid XMDR number of records\n");
		err = -EIO;
		जाओ out;
	पूर्ण
	क्रम (i = 0; i < num_rec; i++) अणु
		अगर (!mlxsw_reg_xmdr_reply_vect_get(op_ctx_xm->xmdr_pl, i)) अणु
			dev_err(mlxsw_sp->bus_info->dev, "Command send over XMDR failed\n");
			err = -EIO;
			जाओ out;
		पूर्ण अन्यथा अणु
			fib_entry = op_ctx_xm->entries[i];
			fib_entry->committed = true;
		पूर्ण
	पूर्ण

	अगर (op_ctx->event == FIB_EVENT_ENTRY_DEL)
		/* The L-table is updated inside. It has to be करोne after
		 * the prefix was हटाओd.
		 */
		mlxsw_sp_router_xm_ml_entries_del(mlxsw_sp, op_ctx_xm);

	/* At the very end, करो the XLT cache flushing to evict stale
	 * M and ML cache entries after prefixes were inserted/हटाओd.
	 */
	mlxsw_sp_router_xm_ml_entries_cache_flush(mlxsw_sp, op_ctx_xm);

out:
	/* Next pack call is going to करो reinitialization */
	op_ctx->initialized = false;
	वापस err;
पूर्ण

अटल bool mlxsw_sp_router_ll_xm_fib_entry_is_committed(काष्ठा mlxsw_sp_fib_entry_priv *priv)
अणु
	काष्ठा mlxsw_sp_router_xm_fib_entry *fib_entry = (व्योम *) priv->priv;

	वापस fib_entry->committed;
पूर्ण

स्थिर काष्ठा mlxsw_sp_router_ll_ops mlxsw_sp_router_ll_xm_ops = अणु
	.init = mlxsw_sp_router_ll_xm_init,
	.ralta_ग_लिखो = mlxsw_sp_router_ll_xm_ralta_ग_लिखो,
	.ralst_ग_लिखो = mlxsw_sp_router_ll_xm_ralst_ग_लिखो,
	.raltb_ग_लिखो = mlxsw_sp_router_ll_xm_raltb_ग_लिखो,
	.fib_entry_op_ctx_size = माप(काष्ठा mlxsw_sp_fib_entry_op_ctx_xm),
	.fib_entry_priv_size = माप(काष्ठा mlxsw_sp_router_xm_fib_entry),
	.fib_entry_pack = mlxsw_sp_router_ll_xm_fib_entry_pack,
	.fib_entry_act_remote_pack = mlxsw_sp_router_ll_xm_fib_entry_act_remote_pack,
	.fib_entry_act_local_pack = mlxsw_sp_router_ll_xm_fib_entry_act_local_pack,
	.fib_entry_act_ip2me_pack = mlxsw_sp_router_ll_xm_fib_entry_act_ip2me_pack,
	.fib_entry_act_ip2me_tun_pack = mlxsw_sp_router_ll_xm_fib_entry_act_ip2me_tun_pack,
	.fib_entry_commit = mlxsw_sp_router_ll_xm_fib_entry_commit,
	.fib_entry_is_committed = mlxsw_sp_router_ll_xm_fib_entry_is_committed,
पूर्ण;

#घोषणा MLXSW_SP_ROUTER_XM_MINDEX_SIZE (64 * 1024)

पूर्णांक mlxsw_sp_router_xm_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_router_xm *router_xm;
	अक्षर rxlपंचांग_pl[MLXSW_REG_RXLTM_LEN];
	अक्षर xltq_pl[MLXSW_REG_XLTQ_LEN];
	u32 mindex_size;
	u16 device_id;
	पूर्णांक err;

	अगर (!mlxsw_sp->bus_info->xm_exists)
		वापस 0;

	router_xm = kzalloc(माप(*router_xm), GFP_KERNEL);
	अगर (!router_xm)
		वापस -ENOMEM;

	mlxsw_reg_xltq_pack(xltq_pl);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(xltq), xltq_pl);
	अगर (err)
		जाओ err_xltq_query;
	mlxsw_reg_xltq_unpack(xltq_pl, &device_id, &router_xm->ipv4_supported,
			      &router_xm->ipv6_supported, &router_xm->entries_size, &mindex_size);

	अगर (device_id != MLXSW_REG_XLTQ_XM_DEVICE_ID_XLT) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Invalid XM device id\n");
		err = -EINVAL;
		जाओ err_device_id_check;
	पूर्ण

	अगर (mindex_size != MLXSW_SP_ROUTER_XM_MINDEX_SIZE) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Unexpected M-index size\n");
		err = -EINVAL;
		जाओ err_mindex_size_check;
	पूर्ण

	mlxsw_reg_rxlपंचांग_pack(rxlपंचांग_pl, mlxsw_sp_router_xm_m_val[MLXSW_SP_L3_PROTO_IPV4],
			     mlxsw_sp_router_xm_m_val[MLXSW_SP_L3_PROTO_IPV6]);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rxlपंचांग), rxlपंचांग_pl);
	अगर (err)
		जाओ err_rxlपंचांग_ग_लिखो;

	err = rhashtable_init(&router_xm->ltable_ht, &mlxsw_sp_router_xm_ltable_ht_params);
	अगर (err)
		जाओ err_ltable_ht_init;

	err = rhashtable_init(&router_xm->flush_ht, &mlxsw_sp_router_xm_flush_ht_params);
	अगर (err)
		जाओ err_flush_ht_init;

	mlxsw_sp->router->xm = router_xm;
	वापस 0;

err_flush_ht_init:
	rhashtable_destroy(&router_xm->ltable_ht);
err_ltable_ht_init:
err_rxlपंचांग_ग_लिखो:
err_mindex_size_check:
err_device_id_check:
err_xltq_query:
	kमुक्त(router_xm);
	वापस err;
पूर्ण

व्योम mlxsw_sp_router_xm_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_router_xm *router_xm = mlxsw_sp->router->xm;

	अगर (!mlxsw_sp->bus_info->xm_exists)
		वापस;

	rhashtable_destroy(&router_xm->flush_ht);
	rhashtable_destroy(&router_xm->ltable_ht);
	kमुक्त(router_xm);
पूर्ण

bool mlxsw_sp_router_xm_ipv4_is_supported(स्थिर काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_router_xm *router_xm = mlxsw_sp->router->xm;

	वापस router_xm && router_xm->ipv4_supported;
पूर्ण
