<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/team/team_mode_loadbalance.c - Load-balancing mode क्रम team
 * Copyright (c) 2012 Jiri Pirko <jpirko@redhat.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/filter.h>
#समावेश <linux/अगर_team.h>

अटल rx_handler_result_t lb_receive(काष्ठा team *team, काष्ठा team_port *port,
				      काष्ठा sk_buff *skb)
अणु
	अगर (unlikely(skb->protocol == htons(ETH_P_SLOW))) अणु
		/* LACPDU packets should go to exact delivery */
		स्थिर अचिन्हित अक्षर *dest = eth_hdr(skb)->h_dest;

		अगर (is_link_local_ether_addr(dest) && dest[5] == 0x02)
			वापस RX_HANDLER_EXACT;
	पूर्ण
	वापस RX_HANDLER_ANOTHER;
पूर्ण

काष्ठा lb_priv;

प्रकार काष्ठा team_port *lb_select_tx_port_func_t(काष्ठा team *,
						   काष्ठा lb_priv *,
						   काष्ठा sk_buff *,
						   अचिन्हित अक्षर);

#घोषणा LB_TX_HASHTABLE_SIZE 256 /* hash is a अक्षर */

काष्ठा lb_stats अणु
	u64 tx_bytes;
पूर्ण;

काष्ठा lb_pcpu_stats अणु
	काष्ठा lb_stats hash_stats[LB_TX_HASHTABLE_SIZE];
	काष्ठा u64_stats_sync syncp;
पूर्ण;

काष्ठा lb_stats_info अणु
	काष्ठा lb_stats stats;
	काष्ठा lb_stats last_stats;
	काष्ठा team_option_inst_info *opt_inst_info;
पूर्ण;

काष्ठा lb_port_mapping अणु
	काष्ठा team_port __rcu *port;
	काष्ठा team_option_inst_info *opt_inst_info;
पूर्ण;

काष्ठा lb_priv_ex अणु
	काष्ठा team *team;
	काष्ठा lb_port_mapping tx_hash_to_port_mapping[LB_TX_HASHTABLE_SIZE];
	काष्ठा sock_fprog_kern *orig_fprog;
	काष्ठा अणु
		अचिन्हित पूर्णांक refresh_पूर्णांकerval; /* in tenths of second */
		काष्ठा delayed_work refresh_dw;
		काष्ठा lb_stats_info info[LB_TX_HASHTABLE_SIZE];
	पूर्ण stats;
पूर्ण;

काष्ठा lb_priv अणु
	काष्ठा bpf_prog __rcu *fp;
	lb_select_tx_port_func_t __rcu *select_tx_port_func;
	काष्ठा lb_pcpu_stats __percpu *pcpu_stats;
	काष्ठा lb_priv_ex *ex; /* priv extension */
पूर्ण;

अटल काष्ठा lb_priv *get_lb_priv(काष्ठा team *team)
अणु
	वापस (काष्ठा lb_priv *) &team->mode_priv;
पूर्ण

काष्ठा lb_port_priv अणु
	काष्ठा lb_stats __percpu *pcpu_stats;
	काष्ठा lb_stats_info stats_info;
पूर्ण;

अटल काष्ठा lb_port_priv *get_lb_port_priv(काष्ठा team_port *port)
अणु
	वापस (काष्ठा lb_port_priv *) &port->mode_priv;
पूर्ण

#घोषणा LB_HTPM_PORT_BY_HASH(lp_priv, hash) \
	(lb_priv)->ex->tx_hash_to_port_mapping[hash].port

#घोषणा LB_HTPM_OPT_INST_INFO_BY_HASH(lp_priv, hash) \
	(lb_priv)->ex->tx_hash_to_port_mapping[hash].opt_inst_info

अटल व्योम lb_tx_hash_to_port_mapping_null_port(काष्ठा team *team,
						 काष्ठा team_port *port)
अणु
	काष्ठा lb_priv *lb_priv = get_lb_priv(team);
	bool changed = false;
	पूर्णांक i;

	क्रम (i = 0; i < LB_TX_HASHTABLE_SIZE; i++) अणु
		काष्ठा lb_port_mapping *pm;

		pm = &lb_priv->ex->tx_hash_to_port_mapping[i];
		अगर (rcu_access_poपूर्णांकer(pm->port) == port) अणु
			RCU_INIT_POINTER(pm->port, शून्य);
			team_option_inst_set_change(pm->opt_inst_info);
			changed = true;
		पूर्ण
	पूर्ण
	अगर (changed)
		team_options_change_check(team);
पूर्ण

/* Basic tx selection based solely by hash */
अटल काष्ठा team_port *lb_hash_select_tx_port(काष्ठा team *team,
						काष्ठा lb_priv *lb_priv,
						काष्ठा sk_buff *skb,
						अचिन्हित अक्षर hash)
अणु
	पूर्णांक port_index = team_num_to_port_index(team, hash);

	वापस team_get_port_by_index_rcu(team, port_index);
पूर्ण

/* Hash to port mapping select tx port */
अटल काष्ठा team_port *lb_htpm_select_tx_port(काष्ठा team *team,
						काष्ठा lb_priv *lb_priv,
						काष्ठा sk_buff *skb,
						अचिन्हित अक्षर hash)
अणु
	काष्ठा team_port *port;

	port = rcu_dereference_bh(LB_HTPM_PORT_BY_HASH(lb_priv, hash));
	अगर (likely(port))
		वापस port;
	/* If no valid port in the table, fall back to simple hash */
	वापस lb_hash_select_tx_port(team, lb_priv, skb, hash);
पूर्ण

काष्ठा lb_select_tx_port अणु
	अक्षर *name;
	lb_select_tx_port_func_t *func;
पूर्ण;

अटल स्थिर काष्ठा lb_select_tx_port lb_select_tx_port_list[] = अणु
	अणु
		.name = "hash",
		.func = lb_hash_select_tx_port,
	पूर्ण,
	अणु
		.name = "hash_to_port_mapping",
		.func = lb_htpm_select_tx_port,
	पूर्ण,
पूर्ण;
#घोषणा LB_SELECT_TX_PORT_LIST_COUNT ARRAY_SIZE(lb_select_tx_port_list)

अटल अक्षर *lb_select_tx_port_get_name(lb_select_tx_port_func_t *func)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < LB_SELECT_TX_PORT_LIST_COUNT; i++) अणु
		स्थिर काष्ठा lb_select_tx_port *item;

		item = &lb_select_tx_port_list[i];
		अगर (item->func == func)
			वापस item->name;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल lb_select_tx_port_func_t *lb_select_tx_port_get_func(स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < LB_SELECT_TX_PORT_LIST_COUNT; i++) अणु
		स्थिर काष्ठा lb_select_tx_port *item;

		item = &lb_select_tx_port_list[i];
		अगर (!म_भेद(item->name, name))
			वापस item->func;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक lb_get_skb_hash(काष्ठा lb_priv *lb_priv,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा bpf_prog *fp;
	uपूर्णांक32_t lhash;
	अचिन्हित अक्षर *c;

	fp = rcu_dereference_bh(lb_priv->fp);
	अगर (unlikely(!fp))
		वापस 0;
	lhash = BPF_PROG_RUN(fp, skb);
	c = (अक्षर *) &lhash;
	वापस c[0] ^ c[1] ^ c[2] ^ c[3];
पूर्ण

अटल व्योम lb_update_tx_stats(अचिन्हित पूर्णांक tx_bytes, काष्ठा lb_priv *lb_priv,
			       काष्ठा lb_port_priv *lb_port_priv,
			       अचिन्हित अक्षर hash)
अणु
	काष्ठा lb_pcpu_stats *pcpu_stats;
	काष्ठा lb_stats *port_stats;
	काष्ठा lb_stats *hash_stats;

	pcpu_stats = this_cpu_ptr(lb_priv->pcpu_stats);
	port_stats = this_cpu_ptr(lb_port_priv->pcpu_stats);
	hash_stats = &pcpu_stats->hash_stats[hash];
	u64_stats_update_begin(&pcpu_stats->syncp);
	port_stats->tx_bytes += tx_bytes;
	hash_stats->tx_bytes += tx_bytes;
	u64_stats_update_end(&pcpu_stats->syncp);
पूर्ण

अटल bool lb_transmit(काष्ठा team *team, काष्ठा sk_buff *skb)
अणु
	काष्ठा lb_priv *lb_priv = get_lb_priv(team);
	lb_select_tx_port_func_t *select_tx_port_func;
	काष्ठा team_port *port;
	अचिन्हित अक्षर hash;
	अचिन्हित पूर्णांक tx_bytes = skb->len;

	hash = lb_get_skb_hash(lb_priv, skb);
	select_tx_port_func = rcu_dereference_bh(lb_priv->select_tx_port_func);
	port = select_tx_port_func(team, lb_priv, skb, hash);
	अगर (unlikely(!port))
		जाओ drop;
	अगर (team_dev_queue_xmit(team, port, skb))
		वापस false;
	lb_update_tx_stats(tx_bytes, lb_priv, get_lb_port_priv(port), hash);
	वापस true;

drop:
	dev_kमुक्त_skb_any(skb);
	वापस false;
पूर्ण

अटल पूर्णांक lb_bpf_func_get(काष्ठा team *team, काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा lb_priv *lb_priv = get_lb_priv(team);

	अगर (!lb_priv->ex->orig_fprog) अणु
		ctx->data.bin_val.len = 0;
		ctx->data.bin_val.ptr = शून्य;
		वापस 0;
	पूर्ण
	ctx->data.bin_val.len = lb_priv->ex->orig_fprog->len *
				माप(काष्ठा sock_filter);
	ctx->data.bin_val.ptr = lb_priv->ex->orig_fprog->filter;
	वापस 0;
पूर्ण

अटल पूर्णांक __fprog_create(काष्ठा sock_fprog_kern **pfprog, u32 data_len,
			  स्थिर व्योम *data)
अणु
	काष्ठा sock_fprog_kern *fprog;
	काष्ठा sock_filter *filter = (काष्ठा sock_filter *) data;

	अगर (data_len % माप(काष्ठा sock_filter))
		वापस -EINVAL;
	fprog = kदो_स्मृति(माप(*fprog), GFP_KERNEL);
	अगर (!fprog)
		वापस -ENOMEM;
	fprog->filter = kmemdup(filter, data_len, GFP_KERNEL);
	अगर (!fprog->filter) अणु
		kमुक्त(fprog);
		वापस -ENOMEM;
	पूर्ण
	fprog->len = data_len / माप(काष्ठा sock_filter);
	*pfprog = fprog;
	वापस 0;
पूर्ण

अटल व्योम __fprog_destroy(काष्ठा sock_fprog_kern *fprog)
अणु
	kमुक्त(fprog->filter);
	kमुक्त(fprog);
पूर्ण

अटल पूर्णांक lb_bpf_func_set(काष्ठा team *team, काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा lb_priv *lb_priv = get_lb_priv(team);
	काष्ठा bpf_prog *fp = शून्य;
	काष्ठा bpf_prog *orig_fp = शून्य;
	काष्ठा sock_fprog_kern *fprog = शून्य;
	पूर्णांक err;

	अगर (ctx->data.bin_val.len) अणु
		err = __fprog_create(&fprog, ctx->data.bin_val.len,
				     ctx->data.bin_val.ptr);
		अगर (err)
			वापस err;
		err = bpf_prog_create(&fp, fprog);
		अगर (err) अणु
			__fprog_destroy(fprog);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (lb_priv->ex->orig_fprog) अणु
		/* Clear old filter data */
		__fprog_destroy(lb_priv->ex->orig_fprog);
		orig_fp = rcu_dereference_रक्षित(lb_priv->fp,
						lockdep_is_held(&team->lock));
	पूर्ण

	rcu_assign_poपूर्णांकer(lb_priv->fp, fp);
	lb_priv->ex->orig_fprog = fprog;

	अगर (orig_fp) अणु
		synchronize_rcu();
		bpf_prog_destroy(orig_fp);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम lb_bpf_func_मुक्त(काष्ठा team *team)
अणु
	काष्ठा lb_priv *lb_priv = get_lb_priv(team);
	काष्ठा bpf_prog *fp;

	अगर (!lb_priv->ex->orig_fprog)
		वापस;

	__fprog_destroy(lb_priv->ex->orig_fprog);
	fp = rcu_dereference_रक्षित(lb_priv->fp,
				       lockdep_is_held(&team->lock));
	bpf_prog_destroy(fp);
पूर्ण

अटल पूर्णांक lb_tx_method_get(काष्ठा team *team, काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा lb_priv *lb_priv = get_lb_priv(team);
	lb_select_tx_port_func_t *func;
	अक्षर *name;

	func = rcu_dereference_रक्षित(lb_priv->select_tx_port_func,
					 lockdep_is_held(&team->lock));
	name = lb_select_tx_port_get_name(func);
	BUG_ON(!name);
	ctx->data.str_val = name;
	वापस 0;
पूर्ण

अटल पूर्णांक lb_tx_method_set(काष्ठा team *team, काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा lb_priv *lb_priv = get_lb_priv(team);
	lb_select_tx_port_func_t *func;

	func = lb_select_tx_port_get_func(ctx->data.str_val);
	अगर (!func)
		वापस -EINVAL;
	rcu_assign_poपूर्णांकer(lb_priv->select_tx_port_func, func);
	वापस 0;
पूर्ण

अटल पूर्णांक lb_tx_hash_to_port_mapping_init(काष्ठा team *team,
					   काष्ठा team_option_inst_info *info)
अणु
	काष्ठा lb_priv *lb_priv = get_lb_priv(team);
	अचिन्हित अक्षर hash = info->array_index;

	LB_HTPM_OPT_INST_INFO_BY_HASH(lb_priv, hash) = info;
	वापस 0;
पूर्ण

अटल पूर्णांक lb_tx_hash_to_port_mapping_get(काष्ठा team *team,
					  काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा lb_priv *lb_priv = get_lb_priv(team);
	काष्ठा team_port *port;
	अचिन्हित अक्षर hash = ctx->info->array_index;

	port = LB_HTPM_PORT_BY_HASH(lb_priv, hash);
	ctx->data.u32_val = port ? port->dev->अगरindex : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक lb_tx_hash_to_port_mapping_set(काष्ठा team *team,
					  काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा lb_priv *lb_priv = get_lb_priv(team);
	काष्ठा team_port *port;
	अचिन्हित अक्षर hash = ctx->info->array_index;

	list_क्रम_each_entry(port, &team->port_list, list) अणु
		अगर (ctx->data.u32_val == port->dev->अगरindex &&
		    team_port_enabled(port)) अणु
			rcu_assign_poपूर्णांकer(LB_HTPM_PORT_BY_HASH(lb_priv, hash),
					   port);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक lb_hash_stats_init(काष्ठा team *team,
			      काष्ठा team_option_inst_info *info)
अणु
	काष्ठा lb_priv *lb_priv = get_lb_priv(team);
	अचिन्हित अक्षर hash = info->array_index;

	lb_priv->ex->stats.info[hash].opt_inst_info = info;
	वापस 0;
पूर्ण

अटल पूर्णांक lb_hash_stats_get(काष्ठा team *team, काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा lb_priv *lb_priv = get_lb_priv(team);
	अचिन्हित अक्षर hash = ctx->info->array_index;

	ctx->data.bin_val.ptr = &lb_priv->ex->stats.info[hash].stats;
	ctx->data.bin_val.len = माप(काष्ठा lb_stats);
	वापस 0;
पूर्ण

अटल पूर्णांक lb_port_stats_init(काष्ठा team *team,
			      काष्ठा team_option_inst_info *info)
अणु
	काष्ठा team_port *port = info->port;
	काष्ठा lb_port_priv *lb_port_priv = get_lb_port_priv(port);

	lb_port_priv->stats_info.opt_inst_info = info;
	वापस 0;
पूर्ण

अटल पूर्णांक lb_port_stats_get(काष्ठा team *team, काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा team_port *port = ctx->info->port;
	काष्ठा lb_port_priv *lb_port_priv = get_lb_port_priv(port);

	ctx->data.bin_val.ptr = &lb_port_priv->stats_info.stats;
	ctx->data.bin_val.len = माप(काष्ठा lb_stats);
	वापस 0;
पूर्ण

अटल व्योम __lb_stats_info_refresh_prepare(काष्ठा lb_stats_info *s_info)
अणु
	स_नकल(&s_info->last_stats, &s_info->stats, माप(काष्ठा lb_stats));
	स_रखो(&s_info->stats, 0, माप(काष्ठा lb_stats));
पूर्ण

अटल bool __lb_stats_info_refresh_check(काष्ठा lb_stats_info *s_info,
					  काष्ठा team *team)
अणु
	अगर (स_भेद(&s_info->last_stats, &s_info->stats,
	    माप(काष्ठा lb_stats))) अणु
		team_option_inst_set_change(s_info->opt_inst_info);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम __lb_one_cpu_stats_add(काष्ठा lb_stats *acc_stats,
				   काष्ठा lb_stats *cpu_stats,
				   काष्ठा u64_stats_sync *syncp)
अणु
	अचिन्हित पूर्णांक start;
	काष्ठा lb_stats पंचांगp;

	करो अणु
		start = u64_stats_fetch_begin_irq(syncp);
		पंचांगp.tx_bytes = cpu_stats->tx_bytes;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(syncp, start));
	acc_stats->tx_bytes += पंचांगp.tx_bytes;
पूर्ण

अटल व्योम lb_stats_refresh(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा team *team;
	काष्ठा lb_priv *lb_priv;
	काष्ठा lb_priv_ex *lb_priv_ex;
	काष्ठा lb_pcpu_stats *pcpu_stats;
	काष्ठा lb_stats *stats;
	काष्ठा lb_stats_info *s_info;
	काष्ठा team_port *port;
	bool changed = false;
	पूर्णांक i;
	पूर्णांक j;

	lb_priv_ex = container_of(work, काष्ठा lb_priv_ex,
				  stats.refresh_dw.work);

	team = lb_priv_ex->team;
	lb_priv = get_lb_priv(team);

	अगर (!mutex_trylock(&team->lock)) अणु
		schedule_delayed_work(&lb_priv_ex->stats.refresh_dw, 0);
		वापस;
	पूर्ण

	क्रम (j = 0; j < LB_TX_HASHTABLE_SIZE; j++) अणु
		s_info = &lb_priv->ex->stats.info[j];
		__lb_stats_info_refresh_prepare(s_info);
		क्रम_each_possible_cpu(i) अणु
			pcpu_stats = per_cpu_ptr(lb_priv->pcpu_stats, i);
			stats = &pcpu_stats->hash_stats[j];
			__lb_one_cpu_stats_add(&s_info->stats, stats,
					       &pcpu_stats->syncp);
		पूर्ण
		changed |= __lb_stats_info_refresh_check(s_info, team);
	पूर्ण

	list_क्रम_each_entry(port, &team->port_list, list) अणु
		काष्ठा lb_port_priv *lb_port_priv = get_lb_port_priv(port);

		s_info = &lb_port_priv->stats_info;
		__lb_stats_info_refresh_prepare(s_info);
		क्रम_each_possible_cpu(i) अणु
			pcpu_stats = per_cpu_ptr(lb_priv->pcpu_stats, i);
			stats = per_cpu_ptr(lb_port_priv->pcpu_stats, i);
			__lb_one_cpu_stats_add(&s_info->stats, stats,
					       &pcpu_stats->syncp);
		पूर्ण
		changed |= __lb_stats_info_refresh_check(s_info, team);
	पूर्ण

	अगर (changed)
		team_options_change_check(team);

	schedule_delayed_work(&lb_priv_ex->stats.refresh_dw,
			      (lb_priv_ex->stats.refresh_पूर्णांकerval * HZ) / 10);

	mutex_unlock(&team->lock);
पूर्ण

अटल पूर्णांक lb_stats_refresh_पूर्णांकerval_get(काष्ठा team *team,
					 काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा lb_priv *lb_priv = get_lb_priv(team);

	ctx->data.u32_val = lb_priv->ex->stats.refresh_पूर्णांकerval;
	वापस 0;
पूर्ण

अटल पूर्णांक lb_stats_refresh_पूर्णांकerval_set(काष्ठा team *team,
					 काष्ठा team_gsetter_ctx *ctx)
अणु
	काष्ठा lb_priv *lb_priv = get_lb_priv(team);
	अचिन्हित पूर्णांक पूर्णांकerval;

	पूर्णांकerval = ctx->data.u32_val;
	अगर (lb_priv->ex->stats.refresh_पूर्णांकerval == पूर्णांकerval)
		वापस 0;
	lb_priv->ex->stats.refresh_पूर्णांकerval = पूर्णांकerval;
	अगर (पूर्णांकerval)
		schedule_delayed_work(&lb_priv->ex->stats.refresh_dw, 0);
	अन्यथा
		cancel_delayed_work(&lb_priv->ex->stats.refresh_dw);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा team_option lb_options[] = अणु
	अणु
		.name = "bpf_hash_func",
		.type = TEAM_OPTION_TYPE_BINARY,
		.getter = lb_bpf_func_get,
		.setter = lb_bpf_func_set,
	पूर्ण,
	अणु
		.name = "lb_tx_method",
		.type = TEAM_OPTION_TYPE_STRING,
		.getter = lb_tx_method_get,
		.setter = lb_tx_method_set,
	पूर्ण,
	अणु
		.name = "lb_tx_hash_to_port_mapping",
		.array_size = LB_TX_HASHTABLE_SIZE,
		.type = TEAM_OPTION_TYPE_U32,
		.init = lb_tx_hash_to_port_mapping_init,
		.getter = lb_tx_hash_to_port_mapping_get,
		.setter = lb_tx_hash_to_port_mapping_set,
	पूर्ण,
	अणु
		.name = "lb_hash_stats",
		.array_size = LB_TX_HASHTABLE_SIZE,
		.type = TEAM_OPTION_TYPE_BINARY,
		.init = lb_hash_stats_init,
		.getter = lb_hash_stats_get,
	पूर्ण,
	अणु
		.name = "lb_port_stats",
		.per_port = true,
		.type = TEAM_OPTION_TYPE_BINARY,
		.init = lb_port_stats_init,
		.getter = lb_port_stats_get,
	पूर्ण,
	अणु
		.name = "lb_stats_refresh_interval",
		.type = TEAM_OPTION_TYPE_U32,
		.getter = lb_stats_refresh_पूर्णांकerval_get,
		.setter = lb_stats_refresh_पूर्णांकerval_set,
	पूर्ण,
पूर्ण;

अटल पूर्णांक lb_init(काष्ठा team *team)
अणु
	काष्ठा lb_priv *lb_priv = get_lb_priv(team);
	lb_select_tx_port_func_t *func;
	पूर्णांक i, err;

	/* set शेष tx port selector */
	func = lb_select_tx_port_get_func("hash");
	BUG_ON(!func);
	rcu_assign_poपूर्णांकer(lb_priv->select_tx_port_func, func);

	lb_priv->ex = kzalloc(माप(*lb_priv->ex), GFP_KERNEL);
	अगर (!lb_priv->ex)
		वापस -ENOMEM;
	lb_priv->ex->team = team;

	lb_priv->pcpu_stats = alloc_percpu(काष्ठा lb_pcpu_stats);
	अगर (!lb_priv->pcpu_stats) अणु
		err = -ENOMEM;
		जाओ err_alloc_pcpu_stats;
	पूर्ण

	क्रम_each_possible_cpu(i) अणु
		काष्ठा lb_pcpu_stats *team_lb_stats;
		team_lb_stats = per_cpu_ptr(lb_priv->pcpu_stats, i);
		u64_stats_init(&team_lb_stats->syncp);
	पूर्ण


	INIT_DELAYED_WORK(&lb_priv->ex->stats.refresh_dw, lb_stats_refresh);

	err = team_options_रेजिस्टर(team, lb_options, ARRAY_SIZE(lb_options));
	अगर (err)
		जाओ err_options_रेजिस्टर;
	वापस 0;

err_options_रेजिस्टर:
	मुक्त_percpu(lb_priv->pcpu_stats);
err_alloc_pcpu_stats:
	kमुक्त(lb_priv->ex);
	वापस err;
पूर्ण

अटल व्योम lb_निकास(काष्ठा team *team)
अणु
	काष्ठा lb_priv *lb_priv = get_lb_priv(team);

	team_options_unरेजिस्टर(team, lb_options,
				ARRAY_SIZE(lb_options));
	lb_bpf_func_मुक्त(team);
	cancel_delayed_work_sync(&lb_priv->ex->stats.refresh_dw);
	मुक्त_percpu(lb_priv->pcpu_stats);
	kमुक्त(lb_priv->ex);
पूर्ण

अटल पूर्णांक lb_port_enter(काष्ठा team *team, काष्ठा team_port *port)
अणु
	काष्ठा lb_port_priv *lb_port_priv = get_lb_port_priv(port);

	lb_port_priv->pcpu_stats = alloc_percpu(काष्ठा lb_stats);
	अगर (!lb_port_priv->pcpu_stats)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम lb_port_leave(काष्ठा team *team, काष्ठा team_port *port)
अणु
	काष्ठा lb_port_priv *lb_port_priv = get_lb_port_priv(port);

	मुक्त_percpu(lb_port_priv->pcpu_stats);
पूर्ण

अटल व्योम lb_port_disabled(काष्ठा team *team, काष्ठा team_port *port)
अणु
	lb_tx_hash_to_port_mapping_null_port(team, port);
पूर्ण

अटल स्थिर काष्ठा team_mode_ops lb_mode_ops = अणु
	.init			= lb_init,
	.निकास			= lb_निकास,
	.port_enter		= lb_port_enter,
	.port_leave		= lb_port_leave,
	.port_disabled		= lb_port_disabled,
	.receive		= lb_receive,
	.transmit		= lb_transmit,
पूर्ण;

अटल स्थिर काष्ठा team_mode lb_mode = अणु
	.kind		= "loadbalance",
	.owner		= THIS_MODULE,
	.priv_size	= माप(काष्ठा lb_priv),
	.port_priv_size	= माप(काष्ठा lb_port_priv),
	.ops		= &lb_mode_ops,
	.lag_tx_type	= NETDEV_LAG_TX_TYPE_HASH,
पूर्ण;

अटल पूर्णांक __init lb_init_module(व्योम)
अणु
	वापस team_mode_रेजिस्टर(&lb_mode);
पूर्ण

अटल व्योम __निकास lb_cleanup_module(व्योम)
अणु
	team_mode_unरेजिस्टर(&lb_mode);
पूर्ण

module_init(lb_init_module);
module_निकास(lb_cleanup_module);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jiri Pirko <jpirko@redhat.com>");
MODULE_DESCRIPTION("Load-balancing mode for team");
MODULE_ALIAS_TEAM_MODE("loadbalance");
