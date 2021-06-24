<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* -*- linux-c -*-
 * sysctl_net_core.c: sysctl पूर्णांकerface to net core subप्रणाली.
 *
 * Begun April 1, 1996, Mike Shaver.
 * Added /proc/sys/net/core directory entry (empty =) ). [MS]
 */

#समावेश <linux/mm.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/module.h>
#समावेश <linux/socket.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>

#समावेश <net/ip.h>
#समावेश <net/sock.h>
#समावेश <net/net_ratelimit.h>
#समावेश <net/busy_poll.h>
#समावेश <net/pkt_sched.h>

अटल पूर्णांक two = 2;
अटल पूर्णांक three = 3;
अटल पूर्णांक पूर्णांक_3600 = 3600;
अटल पूर्णांक min_sndbuf = SOCK_MIN_SNDBUF;
अटल पूर्णांक min_rcvbuf = SOCK_MIN_RCVBUF;
अटल पूर्णांक max_skb_frags = MAX_SKB_FRAGS;
अटल दीर्घ दीर्घ_one __maybe_unused = 1;
अटल दीर्घ दीर्घ_max __maybe_unused = दीर्घ_उच्च;

अटल पूर्णांक net_msg_warn;	/* Unused, but still a sysctl */

पूर्णांक sysctl_fb_tunnels_only_क्रम_init_net __पढ़ो_mostly = 0;
EXPORT_SYMBOL(sysctl_fb_tunnels_only_क्रम_init_net);

/* 0 - Keep current behavior:
 *     IPv4: inherit all current settings from init_net
 *     IPv6: reset all settings to शेष
 * 1 - Both inherit all current settings from init_net
 * 2 - Both reset all settings to शेष
 * 3 - Both inherit all settings from current netns
 */
पूर्णांक sysctl_devconf_inherit_init_net __पढ़ो_mostly;
EXPORT_SYMBOL(sysctl_devconf_inherit_init_net);

#अगर_घोषित CONFIG_RPS
अटल पूर्णांक rps_sock_flow_sysctl(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक orig_size, size;
	पूर्णांक ret, i;
	काष्ठा ctl_table पंचांगp = अणु
		.data = &size,
		.maxlen = माप(size),
		.mode = table->mode
	पूर्ण;
	काष्ठा rps_sock_flow_table *orig_sock_table, *sock_table;
	अटल DEFINE_MUTEX(sock_flow_mutex);

	mutex_lock(&sock_flow_mutex);

	orig_sock_table = rcu_dereference_रक्षित(rps_sock_flow_table,
					lockdep_is_held(&sock_flow_mutex));
	size = orig_size = orig_sock_table ? orig_sock_table->mask + 1 : 0;

	ret = proc_करोपूर्णांकvec(&पंचांगp, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो) अणु
		अगर (size) अणु
			अगर (size > 1<<29) अणु
				/* Enक्रमce limit to prevent overflow */
				mutex_unlock(&sock_flow_mutex);
				वापस -EINVAL;
			पूर्ण
			size = roundup_घात_of_two(size);
			अगर (size != orig_size) अणु
				sock_table =
				    vदो_स्मृति(RPS_SOCK_FLOW_TABLE_SIZE(size));
				अगर (!sock_table) अणु
					mutex_unlock(&sock_flow_mutex);
					वापस -ENOMEM;
				पूर्ण
				rps_cpu_mask = roundup_घात_of_two(nr_cpu_ids) - 1;
				sock_table->mask = size - 1;
			पूर्ण अन्यथा
				sock_table = orig_sock_table;

			क्रम (i = 0; i < size; i++)
				sock_table->ents[i] = RPS_NO_CPU;
		पूर्ण अन्यथा
			sock_table = शून्य;

		अगर (sock_table != orig_sock_table) अणु
			rcu_assign_poपूर्णांकer(rps_sock_flow_table, sock_table);
			अगर (sock_table) अणु
				अटल_branch_inc(&rps_needed);
				अटल_branch_inc(&rfs_needed);
			पूर्ण
			अगर (orig_sock_table) अणु
				अटल_branch_dec(&rps_needed);
				अटल_branch_dec(&rfs_needed);
				synchronize_rcu();
				vमुक्त(orig_sock_table);
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&sock_flow_mutex);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_RPS */

#अगर_घोषित CONFIG_NET_FLOW_LIMIT
अटल DEFINE_MUTEX(flow_limit_update_mutex);

अटल पूर्णांक flow_limit_cpu_sysctl(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				 व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा sd_flow_limit *cur;
	काष्ठा softnet_data *sd;
	cpumask_var_t mask;
	पूर्णांक i, len, ret = 0;

	अगर (!alloc_cpumask_var(&mask, GFP_KERNEL))
		वापस -ENOMEM;

	अगर (ग_लिखो) अणु
		ret = cpumask_parse(buffer, mask);
		अगर (ret)
			जाओ करोne;

		mutex_lock(&flow_limit_update_mutex);
		len = माप(*cur) + netdev_flow_limit_table_len;
		क्रम_each_possible_cpu(i) अणु
			sd = &per_cpu(softnet_data, i);
			cur = rcu_dereference_रक्षित(sd->flow_limit,
				     lockdep_is_held(&flow_limit_update_mutex));
			अगर (cur && !cpumask_test_cpu(i, mask)) अणु
				RCU_INIT_POINTER(sd->flow_limit, शून्य);
				synchronize_rcu();
				kमुक्त(cur);
			पूर्ण अन्यथा अगर (!cur && cpumask_test_cpu(i, mask)) अणु
				cur = kzalloc_node(len, GFP_KERNEL,
						   cpu_to_node(i));
				अगर (!cur) अणु
					/* not unwinding previous changes */
					ret = -ENOMEM;
					जाओ ग_लिखो_unlock;
				पूर्ण
				cur->num_buckets = netdev_flow_limit_table_len;
				rcu_assign_poपूर्णांकer(sd->flow_limit, cur);
			पूर्ण
		पूर्ण
ग_लिखो_unlock:
		mutex_unlock(&flow_limit_update_mutex);
	पूर्ण अन्यथा अणु
		अक्षर kbuf[128];

		अगर (*ppos || !*lenp) अणु
			*lenp = 0;
			जाओ करोne;
		पूर्ण

		cpumask_clear(mask);
		rcu_पढ़ो_lock();
		क्रम_each_possible_cpu(i) अणु
			sd = &per_cpu(softnet_data, i);
			अगर (rcu_dereference(sd->flow_limit))
				cpumask_set_cpu(i, mask);
		पूर्ण
		rcu_पढ़ो_unlock();

		len = min(माप(kbuf) - 1, *lenp);
		len = scnम_लिखो(kbuf, len, "%*pb", cpumask_pr_args(mask));
		अगर (!len) अणु
			*lenp = 0;
			जाओ करोne;
		पूर्ण
		अगर (len < *lenp)
			kbuf[len++] = '\n';
		स_नकल(buffer, kbuf, len);
		*lenp = len;
		*ppos += len;
	पूर्ण

करोne:
	मुक्त_cpumask_var(mask);
	वापस ret;
पूर्ण

अटल पूर्णांक flow_limit_table_len_sysctl(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				       व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक old, *ptr;
	पूर्णांक ret;

	mutex_lock(&flow_limit_update_mutex);

	ptr = table->data;
	old = *ptr;
	ret = proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos);
	अगर (!ret && ग_लिखो && !is_घातer_of_2(*ptr)) अणु
		*ptr = old;
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&flow_limit_update_mutex);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_NET_FLOW_LIMIT */

#अगर_घोषित CONFIG_NET_SCHED
अटल पूर्णांक set_शेष_qdisc(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अक्षर id[IFNAMSIZ];
	काष्ठा ctl_table tbl = अणु
		.data = id,
		.maxlen = IFNAMSIZ,
	पूर्ण;
	पूर्णांक ret;

	qdisc_get_शेष(id, IFNAMSIZ);

	ret = proc_करोstring(&tbl, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && ret == 0)
		ret = qdisc_set_शेष(id);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक proc_करो_dev_weight(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret;

	ret = proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos);
	अगर (ret != 0)
		वापस ret;

	dev_rx_weight = weight_p * dev_weight_rx_bias;
	dev_tx_weight = weight_p * dev_weight_tx_bias;

	वापस ret;
पूर्ण

अटल पूर्णांक proc_करो_rss_key(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table fake_table;
	अक्षर buf[NETDEV_RSS_KEY_LEN * 3];

	snम_लिखो(buf, माप(buf), "%*phC", NETDEV_RSS_KEY_LEN, netdev_rss_key);
	fake_table.data = buf;
	fake_table.maxlen = माप(buf);
	वापस proc_करोstring(&fake_table, ग_लिखो, buffer, lenp, ppos);
पूर्ण

#अगर_घोषित CONFIG_BPF_JIT
अटल पूर्णांक proc_करोपूर्णांकvec_minmax_bpf_enable(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
					   व्योम *buffer, माप_प्रकार *lenp,
					   loff_t *ppos)
अणु
	पूर्णांक ret, jit_enable = *(पूर्णांक *)table->data;
	काष्ठा ctl_table पंचांगp = *table;

	अगर (ग_लिखो && !capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	पंचांगp.data = &jit_enable;
	ret = proc_करोपूर्णांकvec_minmax(&पंचांगp, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && !ret) अणु
		अगर (jit_enable < 2 ||
		    (jit_enable == 2 && bpf_dump_raw_ok(current_cred()))) अणु
			*(पूर्णांक *)table->data = jit_enable;
			अगर (jit_enable == 2)
				pr_warn("bpf_jit_enable = 2 was set! NEVER use this in production, only for JIT debugging!\n");
		पूर्ण अन्यथा अणु
			ret = -EPERM;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

# अगरdef CONFIG_HAVE_EBPF_JIT
अटल पूर्णांक
proc_करोपूर्णांकvec_minmax_bpf_restricted(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				    व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	वापस proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
पूर्ण
# endअगर /* CONFIG_HAVE_EBPF_JIT */

अटल पूर्णांक
proc_करोदीर्घvec_minmax_bpf_restricted(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	वापस proc_करोuदीर्घvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा ctl_table net_core_table[] = अणु
	अणु
		.procname	= "wmem_max",
		.data		= &sysctl_wmem_max,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_sndbuf,
	पूर्ण,
	अणु
		.procname	= "rmem_max",
		.data		= &sysctl_rmem_max,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_rcvbuf,
	पूर्ण,
	अणु
		.procname	= "wmem_default",
		.data		= &sysctl_wmem_शेष,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_sndbuf,
	पूर्ण,
	अणु
		.procname	= "rmem_default",
		.data		= &sysctl_rmem_शेष,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_rcvbuf,
	पूर्ण,
	अणु
		.procname	= "dev_weight",
		.data		= &weight_p,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करो_dev_weight,
	पूर्ण,
	अणु
		.procname	= "dev_weight_rx_bias",
		.data		= &dev_weight_rx_bias,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करो_dev_weight,
	पूर्ण,
	अणु
		.procname	= "dev_weight_tx_bias",
		.data		= &dev_weight_tx_bias,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करो_dev_weight,
	पूर्ण,
	अणु
		.procname	= "netdev_max_backlog",
		.data		= &netdev_max_backlog,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "netdev_rss_key",
		.data		= &netdev_rss_key,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0444,
		.proc_handler	= proc_करो_rss_key,
	पूर्ण,
#अगर_घोषित CONFIG_BPF_JIT
	अणु
		.procname	= "bpf_jit_enable",
		.data		= &bpf_jit_enable,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax_bpf_enable,
# अगरdef CONFIG_BPF_JIT_ALWAYS_ON
		.extra1		= SYSCTL_ONE,
		.extra2		= SYSCTL_ONE,
# अन्यथा
		.extra1		= SYSCTL_ZERO,
		.extra2		= &two,
# endअगर
	पूर्ण,
# अगरdef CONFIG_HAVE_EBPF_JIT
	अणु
		.procname	= "bpf_jit_harden",
		.data		= &bpf_jit_harden,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0600,
		.proc_handler	= proc_करोपूर्णांकvec_minmax_bpf_restricted,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &two,
	पूर्ण,
	अणु
		.procname	= "bpf_jit_kallsyms",
		.data		= &bpf_jit_kallsyms,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0600,
		.proc_handler	= proc_करोपूर्णांकvec_minmax_bpf_restricted,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
# endअगर
	अणु
		.procname	= "bpf_jit_limit",
		.data		= &bpf_jit_limit,
		.maxlen		= माप(दीर्घ),
		.mode		= 0600,
		.proc_handler	= proc_करोदीर्घvec_minmax_bpf_restricted,
		.extra1		= &दीर्घ_one,
		.extra2		= &दीर्घ_max,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "netdev_tstamp_prequeue",
		.data		= &netdev_tstamp_prequeue,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "message_cost",
		.data		= &net_ratelimit_state.पूर्णांकerval,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "message_burst",
		.data		= &net_ratelimit_state.burst,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "optmem_max",
		.data		= &sysctl_opपंचांगem_max,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "tstamp_allow_data",
		.data		= &sysctl_tstamp_allow_data,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE
	पूर्ण,
#अगर_घोषित CONFIG_RPS
	अणु
		.procname	= "rps_sock_flow_entries",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= rps_sock_flow_sysctl
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NET_FLOW_LIMIT
	अणु
		.procname	= "flow_limit_cpu_bitmap",
		.mode		= 0644,
		.proc_handler	= flow_limit_cpu_sysctl
	पूर्ण,
	अणु
		.procname	= "flow_limit_table_len",
		.data		= &netdev_flow_limit_table_len,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= flow_limit_table_len_sysctl
	पूर्ण,
#पूर्ण_अगर /* CONFIG_NET_FLOW_LIMIT */
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	अणु
		.procname	= "busy_poll",
		.data		= &sysctl_net_busy_poll,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "busy_read",
		.data		= &sysctl_net_busy_पढ़ो,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NET_SCHED
	अणु
		.procname	= "default_qdisc",
		.mode		= 0644,
		.maxlen		= IFNAMSIZ,
		.proc_handler	= set_शेष_qdisc
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "netdev_budget",
		.data		= &netdev_budget,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "warnings",
		.data		= &net_msg_warn,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "max_skb_frags",
		.data		= &sysctl_max_skb_frags,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE,
		.extra2		= &max_skb_frags,
	पूर्ण,
	अणु
		.procname	= "netdev_budget_usecs",
		.data		= &netdev_budget_usecs,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "fb_tunnels_only_for_init_net",
		.data		= &sysctl_fb_tunnels_only_क्रम_init_net,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &two,
	पूर्ण,
	अणु
		.procname	= "devconf_inherit_init_net",
		.data		= &sysctl_devconf_inherit_init_net,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &three,
	पूर्ण,
	अणु
		.procname	= "high_order_alloc_disable",
		.data		= &net_high_order_alloc_disable_key.key,
		.maxlen         = माप(net_high_order_alloc_disable_key),
		.mode		= 0644,
		.proc_handler	= proc_करो_अटल_key,
	पूर्ण,
	अणु
		.procname	= "gro_normal_batch",
		.data		= &gro_normal_batch,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "netdev_unregister_timeout_secs",
		.data		= &netdev_unरेजिस्टर_समयout_secs,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE,
		.extra2		= &पूर्णांक_3600,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table netns_core_table[] = अणु
	अणु
		.procname	= "somaxconn",
		.data		= &init_net.core.sysctl_somaxconn,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.extra1		= SYSCTL_ZERO,
		.proc_handler	= proc_करोपूर्णांकvec_minmax
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __init fb_tunnels_only_क्रम_init_net_sysctl_setup(अक्षर *str)
अणु
	/* fallback tunnels क्रम initns only */
	अगर (!म_भेदन(str, "initns", 6))
		sysctl_fb_tunnels_only_क्रम_init_net = 1;
	/* no fallback tunnels anywhere */
	अन्यथा अगर (!म_भेदन(str, "none", 4))
		sysctl_fb_tunnels_only_क्रम_init_net = 2;

	वापस 1;
पूर्ण
__setup("fb_tunnels=", fb_tunnels_only_क्रम_init_net_sysctl_setup);

अटल __net_init पूर्णांक sysctl_core_net_init(काष्ठा net *net)
अणु
	काष्ठा ctl_table *tbl;

	tbl = netns_core_table;
	अगर (!net_eq(net, &init_net)) अणु
		tbl = kmemdup(tbl, माप(netns_core_table), GFP_KERNEL);
		अगर (tbl == शून्य)
			जाओ err_dup;

		tbl[0].data = &net->core.sysctl_somaxconn;

		/* Don't export any sysctls to unprivileged users */
		अगर (net->user_ns != &init_user_ns) अणु
			tbl[0].procname = शून्य;
		पूर्ण
	पूर्ण

	net->core.sysctl_hdr = रेजिस्टर_net_sysctl(net, "net/core", tbl);
	अगर (net->core.sysctl_hdr == शून्य)
		जाओ err_reg;

	वापस 0;

err_reg:
	अगर (tbl != netns_core_table)
		kमुक्त(tbl);
err_dup:
	वापस -ENOMEM;
पूर्ण

अटल __net_निकास व्योम sysctl_core_net_निकास(काष्ठा net *net)
अणु
	काष्ठा ctl_table *tbl;

	tbl = net->core.sysctl_hdr->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(net->core.sysctl_hdr);
	BUG_ON(tbl == netns_core_table);
	kमुक्त(tbl);
पूर्ण

अटल __net_initdata काष्ठा pernet_operations sysctl_core_ops = अणु
	.init = sysctl_core_net_init,
	.निकास = sysctl_core_net_निकास,
पूर्ण;

अटल __init पूर्णांक sysctl_core_init(व्योम)
अणु
	रेजिस्टर_net_sysctl(&init_net, "net/core", net_core_table);
	वापस रेजिस्टर_pernet_subsys(&sysctl_core_ops);
पूर्ण

fs_initcall(sysctl_core_init);
