<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sysctl_net_ipv4.c: sysctl पूर्णांकerface to net IPV4 subप्रणाली.
 *
 * Begun April 1, 1996, Mike Shaver.
 * Added /proc/sys/net/ipv4 directory entry (empty =) ). [MS]
 */

#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/igmp.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/swap.h>
#समावेश <net/snmp.h>
#समावेश <net/icmp.h>
#समावेश <net/ip.h>
#समावेश <net/route.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>
#समावेश <net/cipso_ipv4.h>
#समावेश <net/inet_frag.h>
#समावेश <net/ping.h>
#समावेश <net/protocol.h>
#समावेश <net/netevent.h>

अटल पूर्णांक two = 2;
अटल पूर्णांक four = 4;
अटल पूर्णांक thousand = 1000;
अटल पूर्णांक tcp_retr1_max = 255;
अटल पूर्णांक ip_local_port_range_min[] = अणु 1, 1 पूर्ण;
अटल पूर्णांक ip_local_port_range_max[] = अणु 65535, 65535 पूर्ण;
अटल पूर्णांक tcp_adv_win_scale_min = -31;
अटल पूर्णांक tcp_adv_win_scale_max = 31;
अटल पूर्णांक tcp_min_snd_mss_min = TCP_MIN_SND_MSS;
अटल पूर्णांक tcp_min_snd_mss_max = 65535;
अटल पूर्णांक ip_privileged_port_min;
अटल पूर्णांक ip_privileged_port_max = 65535;
अटल पूर्णांक ip_ttl_min = 1;
अटल पूर्णांक ip_ttl_max = 255;
अटल पूर्णांक tcp_syn_retries_min = 1;
अटल पूर्णांक tcp_syn_retries_max = MAX_TCP_SYNCNT;
अटल पूर्णांक ip_ping_group_range_min[] = अणु 0, 0 पूर्ण;
अटल पूर्णांक ip_ping_group_range_max[] = अणु GID_T_MAX, GID_T_MAX पूर्ण;
अटल u32 u32_max_भाग_HZ = अच_पूर्णांक_उच्च / HZ;
अटल पूर्णांक one_day_secs = 24 * 3600;

/* obsolete */
अटल पूर्णांक sysctl_tcp_low_latency __पढ़ो_mostly;

/* Update प्रणाली visible IP port range */
अटल व्योम set_local_port_range(काष्ठा net *net, पूर्णांक range[2])
अणु
	bool same_parity = !((range[0] ^ range[1]) & 1);

	ग_लिखो_seqlock_bh(&net->ipv4.ip_local_ports.lock);
	अगर (same_parity && !net->ipv4.ip_local_ports.warned) अणु
		net->ipv4.ip_local_ports.warned = true;
		pr_err_ratelimited("ip_local_port_range: prefer different parity for start/end values.\n");
	पूर्ण
	net->ipv4.ip_local_ports.range[0] = range[0];
	net->ipv4.ip_local_ports.range[1] = range[1];
	ग_लिखो_sequnlock_bh(&net->ipv4.ip_local_ports.lock);
पूर्ण

/* Validate changes from /proc पूर्णांकerface. */
अटल पूर्णांक ipv4_local_port_range(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				 व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा net *net =
		container_of(table->data, काष्ठा net, ipv4.ip_local_ports.range);
	पूर्णांक ret;
	पूर्णांक range[2];
	काष्ठा ctl_table पंचांगp = अणु
		.data = &range,
		.maxlen = माप(range),
		.mode = table->mode,
		.extra1 = &ip_local_port_range_min,
		.extra2 = &ip_local_port_range_max,
	पूर्ण;

	inet_get_local_port_range(net, &range[0], &range[1]);

	ret = proc_करोपूर्णांकvec_minmax(&पंचांगp, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो && ret == 0) अणु
		/* Ensure that the upper limit is not smaller than the lower,
		 * and that the lower करोes not encroach upon the privileged
		 * port limit.
		 */
		अगर ((range[1] < range[0]) ||
		    (range[0] < net->ipv4.sysctl_ip_prot_sock))
			ret = -EINVAL;
		अन्यथा
			set_local_port_range(net, range);
	पूर्ण

	वापस ret;
पूर्ण

/* Validate changes from /proc पूर्णांकerface. */
अटल पूर्णांक ipv4_privileged_ports(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा net *net = container_of(table->data, काष्ठा net,
	    ipv4.sysctl_ip_prot_sock);
	पूर्णांक ret;
	पूर्णांक pports;
	पूर्णांक range[2];
	काष्ठा ctl_table पंचांगp = अणु
		.data = &pports,
		.maxlen = माप(pports),
		.mode = table->mode,
		.extra1 = &ip_privileged_port_min,
		.extra2 = &ip_privileged_port_max,
	पूर्ण;

	pports = net->ipv4.sysctl_ip_prot_sock;

	ret = proc_करोपूर्णांकvec_minmax(&पंचांगp, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो && ret == 0) अणु
		inet_get_local_port_range(net, &range[0], &range[1]);
		/* Ensure that the local port range करोesn't overlap with the
		 * privileged port range.
		 */
		अगर (range[0] < pports)
			ret = -EINVAL;
		अन्यथा
			net->ipv4.sysctl_ip_prot_sock = pports;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम inet_get_ping_group_range_table(काष्ठा ctl_table *table, kgid_t *low, kgid_t *high)
अणु
	kgid_t *data = table->data;
	काष्ठा net *net =
		container_of(table->data, काष्ठा net, ipv4.ping_group_range.range);
	अचिन्हित पूर्णांक seq;
	करो अणु
		seq = पढ़ो_seqbegin(&net->ipv4.ping_group_range.lock);

		*low = data[0];
		*high = data[1];
	पूर्ण जबतक (पढ़ो_seqretry(&net->ipv4.ping_group_range.lock, seq));
पूर्ण

/* Update प्रणाली visible IP port range */
अटल व्योम set_ping_group_range(काष्ठा ctl_table *table, kgid_t low, kgid_t high)
अणु
	kgid_t *data = table->data;
	काष्ठा net *net =
		container_of(table->data, काष्ठा net, ipv4.ping_group_range.range);
	ग_लिखो_seqlock(&net->ipv4.ping_group_range.lock);
	data[0] = low;
	data[1] = high;
	ग_लिखो_sequnlock(&net->ipv4.ping_group_range.lock);
पूर्ण

/* Validate changes from /proc पूर्णांकerface. */
अटल पूर्णांक ipv4_ping_group_range(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				 व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा user_namespace *user_ns = current_user_ns();
	पूर्णांक ret;
	gid_t urange[2];
	kgid_t low, high;
	काष्ठा ctl_table पंचांगp = अणु
		.data = &urange,
		.maxlen = माप(urange),
		.mode = table->mode,
		.extra1 = &ip_ping_group_range_min,
		.extra2 = &ip_ping_group_range_max,
	पूर्ण;

	inet_get_ping_group_range_table(table, &low, &high);
	urange[0] = from_kgid_munged(user_ns, low);
	urange[1] = from_kgid_munged(user_ns, high);
	ret = proc_करोपूर्णांकvec_minmax(&पंचांगp, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो && ret == 0) अणु
		low = make_kgid(user_ns, urange[0]);
		high = make_kgid(user_ns, urange[1]);
		अगर (!gid_valid(low) || !gid_valid(high))
			वापस -EINVAL;
		अगर (urange[1] < urange[0] || gid_lt(high, low)) अणु
			low = make_kgid(&init_user_ns, 1);
			high = make_kgid(&init_user_ns, 0);
		पूर्ण
		set_ping_group_range(table, low, high);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ipv4_fwd_update_priority(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				    व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा net *net;
	पूर्णांक ret;

	net = container_of(table->data, काष्ठा net,
			   ipv4.sysctl_ip_fwd_update_priority);
	ret = proc_करोu8vec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && ret == 0)
		call_netevent_notअगरiers(NETEVENT_IPV4_FWD_UPDATE_PRIORITY_UPDATE,
					net);

	वापस ret;
पूर्ण

अटल पूर्णांक proc_tcp_congestion_control(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				       व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा net *net = container_of(ctl->data, काष्ठा net,
				       ipv4.tcp_congestion_control);
	अक्षर val[TCP_CA_NAME_MAX];
	काष्ठा ctl_table tbl = अणु
		.data = val,
		.maxlen = TCP_CA_NAME_MAX,
	पूर्ण;
	पूर्णांक ret;

	tcp_get_शेष_congestion_control(net, val);

	ret = proc_करोstring(&tbl, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && ret == 0)
		ret = tcp_set_शेष_congestion_control(net, val);
	वापस ret;
पूर्ण

अटल पूर्णांक proc_tcp_available_congestion_control(काष्ठा ctl_table *ctl,
						 पूर्णांक ग_लिखो, व्योम *buffer,
						 माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table tbl = अणु .maxlen = TCP_CA_BUF_MAX, पूर्ण;
	पूर्णांक ret;

	tbl.data = kदो_स्मृति(tbl.maxlen, GFP_USER);
	अगर (!tbl.data)
		वापस -ENOMEM;
	tcp_get_available_congestion_control(tbl.data, TCP_CA_BUF_MAX);
	ret = proc_करोstring(&tbl, ग_लिखो, buffer, lenp, ppos);
	kमुक्त(tbl.data);
	वापस ret;
पूर्ण

अटल पूर्णांक proc_allowed_congestion_control(काष्ठा ctl_table *ctl,
					   पूर्णांक ग_लिखो, व्योम *buffer,
					   माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table tbl = अणु .maxlen = TCP_CA_BUF_MAX पूर्ण;
	पूर्णांक ret;

	tbl.data = kदो_स्मृति(tbl.maxlen, GFP_USER);
	अगर (!tbl.data)
		वापस -ENOMEM;

	tcp_get_allowed_congestion_control(tbl.data, tbl.maxlen);
	ret = proc_करोstring(&tbl, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && ret == 0)
		ret = tcp_set_allowed_congestion_control(tbl.data);
	kमुक्त(tbl.data);
	वापस ret;
पूर्ण

अटल पूर्णांक माला_पूछो_key(अक्षर *buf, __le32 *key)
अणु
	u32 user_key[4];
	पूर्णांक i, ret = 0;

	अगर (माला_पूछो(buf, "%x-%x-%x-%x", user_key, user_key + 1,
		   user_key + 2, user_key + 3) != 4) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ARRAY_SIZE(user_key); i++)
			key[i] = cpu_to_le32(user_key[i]);
	पूर्ण
	pr_debug("proc TFO key set 0x%x-%x-%x-%x <- 0x%s: %u\n",
		 user_key[0], user_key[1], user_key[2], user_key[3], buf, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक proc_tcp_fastखोलो_key(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				 व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा net *net = container_of(table->data, काष्ठा net,
	    ipv4.sysctl_tcp_fastखोलो);
	/* maxlen to prपूर्णांक the list of keys in hex (*2), with dashes
	 * separating द्विगुनwords and a comma in between keys.
	 */
	काष्ठा ctl_table tbl = अणु .maxlen = ((TCP_FASTOPEN_KEY_LENGTH *
					    2 * TCP_FASTOPEN_KEY_MAX) +
					    (TCP_FASTOPEN_KEY_MAX * 5)) पूर्ण;
	u32 user_key[TCP_FASTOPEN_KEY_BUF_LENGTH / माप(u32)];
	__le32 key[TCP_FASTOPEN_KEY_BUF_LENGTH / माप(__le32)];
	अक्षर *backup_data;
	पूर्णांक ret, i = 0, off = 0, n_keys;

	tbl.data = kदो_स्मृति(tbl.maxlen, GFP_KERNEL);
	अगर (!tbl.data)
		वापस -ENOMEM;

	n_keys = tcp_fastखोलो_get_cipher(net, शून्य, (u64 *)key);
	अगर (!n_keys) अणु
		स_रखो(&key[0], 0, TCP_FASTOPEN_KEY_LENGTH);
		n_keys = 1;
	पूर्ण

	क्रम (i = 0; i < n_keys * 4; i++)
		user_key[i] = le32_to_cpu(key[i]);

	क्रम (i = 0; i < n_keys; i++) अणु
		off += snम_लिखो(tbl.data + off, tbl.maxlen - off,
				"%08x-%08x-%08x-%08x",
				user_key[i * 4],
				user_key[i * 4 + 1],
				user_key[i * 4 + 2],
				user_key[i * 4 + 3]);

		अगर (WARN_ON_ONCE(off >= tbl.maxlen - 1))
			अवरोध;

		अगर (i + 1 < n_keys)
			off += snम_लिखो(tbl.data + off, tbl.maxlen - off, ",");
	पूर्ण

	ret = proc_करोstring(&tbl, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो && ret == 0) अणु
		backup_data = म_अक्षर(tbl.data, ',');
		अगर (backup_data) अणु
			*backup_data = '\0';
			backup_data++;
		पूर्ण
		अगर (माला_पूछो_key(tbl.data, key)) अणु
			ret = -EINVAL;
			जाओ bad_key;
		पूर्ण
		अगर (backup_data) अणु
			अगर (माला_पूछो_key(backup_data, key + 4)) अणु
				ret = -EINVAL;
				जाओ bad_key;
			पूर्ण
		पूर्ण
		tcp_fastखोलो_reset_cipher(net, शून्य, key,
					  backup_data ? key + 4 : शून्य);
	पूर्ण

bad_key:
	kमुक्त(tbl.data);
	वापस ret;
पूर्ण

अटल व्योम proc_configure_early_demux(पूर्णांक enabled, पूर्णांक protocol)
अणु
	काष्ठा net_protocol *ipprot;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा inet6_protocol *ip6prot;
#पूर्ण_अगर

	rcu_पढ़ो_lock();

	ipprot = rcu_dereference(inet_protos[protocol]);
	अगर (ipprot)
		ipprot->early_demux = enabled ? ipprot->early_demux_handler :
						शून्य;

#अगर IS_ENABLED(CONFIG_IPV6)
	ip6prot = rcu_dereference(inet6_protos[protocol]);
	अगर (ip6prot)
		ip6prot->early_demux = enabled ? ip6prot->early_demux_handler :
						 शून्य;
#पूर्ण_अगर
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक proc_tcp_early_demux(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret = 0;

	ret = proc_करोu8vec_minmax(table, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो && !ret) अणु
		पूर्णांक enabled = init_net.ipv4.sysctl_tcp_early_demux;

		proc_configure_early_demux(enabled, IPPROTO_TCP);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक proc_udp_early_demux(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret = 0;

	ret = proc_करोu8vec_minmax(table, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो && !ret) अणु
		पूर्णांक enabled = init_net.ipv4.sysctl_udp_early_demux;

		proc_configure_early_demux(enabled, IPPROTO_UDP);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक proc_tfo_blackhole_detect_समयout(काष्ठा ctl_table *table,
					     पूर्णांक ग_लिखो, व्योम *buffer,
					     माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा net *net = container_of(table->data, काष्ठा net,
	    ipv4.sysctl_tcp_fastखोलो_blackhole_समयout);
	पूर्णांक ret;

	ret = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && ret == 0)
		atomic_set(&net->ipv4.tfo_active_disable_बार, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक proc_tcp_available_ulp(काष्ठा ctl_table *ctl,
				  पूर्णांक ग_लिखो, व्योम *buffer, माप_प्रकार *lenp,
				  loff_t *ppos)
अणु
	काष्ठा ctl_table tbl = अणु .maxlen = TCP_ULP_BUF_MAX, पूर्ण;
	पूर्णांक ret;

	tbl.data = kदो_स्मृति(tbl.maxlen, GFP_USER);
	अगर (!tbl.data)
		वापस -ENOMEM;
	tcp_get_available_ulp(tbl.data, TCP_ULP_BUF_MAX);
	ret = proc_करोstring(&tbl, ग_लिखो, buffer, lenp, ppos);
	kमुक्त(tbl.data);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
अटल पूर्णांक proc_fib_multipath_hash_policy(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
					  व्योम *buffer, माप_प्रकार *lenp,
					  loff_t *ppos)
अणु
	काष्ठा net *net = container_of(table->data, काष्ठा net,
	    ipv4.sysctl_fib_multipath_hash_policy);
	पूर्णांक ret;

	ret = proc_करोu8vec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && ret == 0)
		call_netevent_notअगरiers(NETEVENT_IPV4_MPATH_HASH_UPDATE, net);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा ctl_table ipv4_table[] = अणु
	अणु
		.procname	= "tcp_max_orphans",
		.data		= &sysctl_tcp_max_orphans,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "inet_peer_threshold",
		.data		= &inet_peer_threshold,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "inet_peer_minttl",
		.data		= &inet_peer_mपूर्णांकtl,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "inet_peer_maxttl",
		.data		= &inet_peer_maxttl,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "tcp_mem",
		.maxlen		= माप(sysctl_tcp_mem),
		.data		= &sysctl_tcp_mem,
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_low_latency",
		.data		= &sysctl_tcp_low_latency,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
#अगर_घोषित CONFIG_NETLABEL
	अणु
		.procname	= "cipso_cache_enable",
		.data		= &cipso_v4_cache_enabled,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "cipso_cache_bucket_size",
		.data		= &cipso_v4_cache_bucketsize,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "cipso_rbm_optfmt",
		.data		= &cipso_v4_rbm_optfmt,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "cipso_rbm_strictvalid",
		.data		= &cipso_v4_rbm_strictvalid,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_NETLABEL */
	अणु
		.procname	= "tcp_available_ulp",
		.maxlen		= TCP_ULP_BUF_MAX,
		.mode		= 0444,
		.proc_handler   = proc_tcp_available_ulp,
	पूर्ण,
	अणु
		.procname	= "icmp_msgs_per_sec",
		.data		= &sysctl_icmp_msgs_per_sec,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "icmp_msgs_burst",
		.data		= &sysctl_icmp_msgs_burst,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "udp_mem",
		.data		= &sysctl_udp_mem,
		.maxlen		= माप(sysctl_udp_mem),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "fib_sync_mem",
		.data		= &sysctl_fib_sync_mem,
		.maxlen		= माप(sysctl_fib_sync_mem),
		.mode		= 0644,
		.proc_handler	= proc_करोuपूर्णांकvec_minmax,
		.extra1		= &sysctl_fib_sync_mem_min,
		.extra2		= &sysctl_fib_sync_mem_max,
	पूर्ण,
	अणु
		.procname	= "tcp_rx_skb_cache",
		.data		= &tcp_rx_skb_cache_key.key,
		.mode		= 0644,
		.proc_handler	= proc_करो_अटल_key,
	पूर्ण,
	अणु
		.procname	= "tcp_tx_skb_cache",
		.data		= &tcp_tx_skb_cache_key.key,
		.mode		= 0644,
		.proc_handler	= proc_करो_अटल_key,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table ipv4_net_table[] = अणु
	अणु
		.procname	= "icmp_echo_ignore_all",
		.data		= &init_net.ipv4.sysctl_icmp_echo_ignore_all,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "icmp_echo_enable_probe",
		.data		= &init_net.ipv4.sysctl_icmp_echo_enable_probe,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE
	पूर्ण,
	अणु
		.procname	= "icmp_echo_ignore_broadcasts",
		.data		= &init_net.ipv4.sysctl_icmp_echo_ignore_broadcasts,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "icmp_ignore_bogus_error_responses",
		.data		= &init_net.ipv4.sysctl_icmp_ignore_bogus_error_responses,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "icmp_errors_use_inbound_ifaddr",
		.data		= &init_net.ipv4.sysctl_icmp_errors_use_inbound_अगरaddr,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "icmp_ratelimit",
		.data		= &init_net.ipv4.sysctl_icmp_ratelimit,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_ms_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "icmp_ratemask",
		.data		= &init_net.ipv4.sysctl_icmp_ratemask,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "ping_group_range",
		.data		= &init_net.ipv4.ping_group_range.range,
		.maxlen		= माप(gid_t)*2,
		.mode		= 0644,
		.proc_handler	= ipv4_ping_group_range,
	पूर्ण,
#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
	अणु
		.procname	= "raw_l3mdev_accept",
		.data		= &init_net.ipv4.sysctl_raw_l3mdev_accept,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "tcp_ecn",
		.data		= &init_net.ipv4.sysctl_tcp_ecn,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_ecn_fallback",
		.data		= &init_net.ipv4.sysctl_tcp_ecn_fallback,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "ip_dynaddr",
		.data		= &init_net.ipv4.sysctl_ip_dynaddr,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "ip_early_demux",
		.data		= &init_net.ipv4.sysctl_ip_early_demux,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname       = "udp_early_demux",
		.data           = &init_net.ipv4.sysctl_udp_early_demux,
		.maxlen         = माप(u8),
		.mode           = 0644,
		.proc_handler   = proc_udp_early_demux
	पूर्ण,
	अणु
		.procname       = "tcp_early_demux",
		.data           = &init_net.ipv4.sysctl_tcp_early_demux,
		.maxlen         = माप(u8),
		.mode           = 0644,
		.proc_handler   = proc_tcp_early_demux
	पूर्ण,
	अणु
		.procname       = "nexthop_compat_mode",
		.data           = &init_net.ipv4.sysctl_nexthop_compat_mode,
		.maxlen         = माप(u8),
		.mode           = 0644,
		.proc_handler   = proc_करोu8vec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "ip_default_ttl",
		.data		= &init_net.ipv4.sysctl_ip_शेष_ttl,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1		= &ip_ttl_min,
		.extra2		= &ip_ttl_max,
	पूर्ण,
	अणु
		.procname	= "ip_local_port_range",
		.maxlen		= माप(init_net.ipv4.ip_local_ports.range),
		.data		= &init_net.ipv4.ip_local_ports.range,
		.mode		= 0644,
		.proc_handler	= ipv4_local_port_range,
	पूर्ण,
	अणु
		.procname	= "ip_local_reserved_ports",
		.data		= &init_net.ipv4.sysctl_local_reserved_ports,
		.maxlen		= 65536,
		.mode		= 0644,
		.proc_handler	= proc_करो_large_biपंचांगap,
	पूर्ण,
	अणु
		.procname	= "ip_no_pmtu_disc",
		.data		= &init_net.ipv4.sysctl_ip_no_pmtu_disc,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "ip_forward_use_pmtu",
		.data		= &init_net.ipv4.sysctl_ip_fwd_use_pmtu,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "ip_forward_update_priority",
		.data		= &init_net.ipv4.sysctl_ip_fwd_update_priority,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler   = ipv4_fwd_update_priority,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "ip_nonlocal_bind",
		.data		= &init_net.ipv4.sysctl_ip_nonlocal_bind,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "ip_autobind_reuse",
		.data		= &init_net.ipv4.sysctl_ip_स्वतःbind_reuse,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1         = SYSCTL_ZERO,
		.extra2         = SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "fwmark_reflect",
		.data		= &init_net.ipv4.sysctl_fwmark_reflect,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_fwmark_accept",
		.data		= &init_net.ipv4.sysctl_tcp_fwmark_accept,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
	अणु
		.procname	= "tcp_l3mdev_accept",
		.data		= &init_net.ipv4.sysctl_tcp_l3mdev_accept,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "tcp_mtu_probing",
		.data		= &init_net.ipv4.sysctl_tcp_mtu_probing,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_base_mss",
		.data		= &init_net.ipv4.sysctl_tcp_base_mss,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "tcp_min_snd_mss",
		.data		= &init_net.ipv4.sysctl_tcp_min_snd_mss,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &tcp_min_snd_mss_min,
		.extra2		= &tcp_min_snd_mss_max,
	पूर्ण,
	अणु
		.procname	= "tcp_mtu_probe_floor",
		.data		= &init_net.ipv4.sysctl_tcp_mtu_probe_न्यूनमान,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &tcp_min_snd_mss_min,
		.extra2		= &tcp_min_snd_mss_max,
	पूर्ण,
	अणु
		.procname	= "tcp_probe_threshold",
		.data		= &init_net.ipv4.sysctl_tcp_probe_threshold,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "tcp_probe_interval",
		.data		= &init_net.ipv4.sysctl_tcp_probe_पूर्णांकerval,
		.maxlen		= माप(u32),
		.mode		= 0644,
		.proc_handler	= proc_करोuपूर्णांकvec_minmax,
		.extra2		= &u32_max_भाग_HZ,
	पूर्ण,
	अणु
		.procname	= "igmp_link_local_mcast_reports",
		.data		= &init_net.ipv4.sysctl_igmp_llm_reports,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "igmp_max_memberships",
		.data		= &init_net.ipv4.sysctl_igmp_max_memberships,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "igmp_max_msf",
		.data		= &init_net.ipv4.sysctl_igmp_max_msf,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
#अगर_घोषित CONFIG_IP_MULTICAST
	अणु
		.procname	= "igmp_qrv",
		.data		= &init_net.ipv4.sysctl_igmp_qrv,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "tcp_congestion_control",
		.data		= &init_net.ipv4.tcp_congestion_control,
		.mode		= 0644,
		.maxlen		= TCP_CA_NAME_MAX,
		.proc_handler	= proc_tcp_congestion_control,
	पूर्ण,
	अणु
		.procname	= "tcp_available_congestion_control",
		.maxlen		= TCP_CA_BUF_MAX,
		.mode		= 0444,
		.proc_handler   = proc_tcp_available_congestion_control,
	पूर्ण,
	अणु
		.procname	= "tcp_allowed_congestion_control",
		.maxlen		= TCP_CA_BUF_MAX,
		.mode		= 0644,
		.proc_handler   = proc_allowed_congestion_control,
	पूर्ण,
	अणु
		.procname	= "tcp_keepalive_time",
		.data		= &init_net.ipv4.sysctl_tcp_keepalive_समय,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "tcp_keepalive_probes",
		.data		= &init_net.ipv4.sysctl_tcp_keepalive_probes,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_keepalive_intvl",
		.data		= &init_net.ipv4.sysctl_tcp_keepalive_पूर्णांकvl,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "tcp_syn_retries",
		.data		= &init_net.ipv4.sysctl_tcp_syn_retries,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1		= &tcp_syn_retries_min,
		.extra2		= &tcp_syn_retries_max
	पूर्ण,
	अणु
		.procname	= "tcp_synack_retries",
		.data		= &init_net.ipv4.sysctl_tcp_synack_retries,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
#अगर_घोषित CONFIG_SYN_COOKIES
	अणु
		.procname	= "tcp_syncookies",
		.data		= &init_net.ipv4.sysctl_tcp_syncookies,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "tcp_reordering",
		.data		= &init_net.ipv4.sysctl_tcp_reordering,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "tcp_retries1",
		.data		= &init_net.ipv4.sysctl_tcp_retries1,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra2		= &tcp_retr1_max
	पूर्ण,
	अणु
		.procname	= "tcp_retries2",
		.data		= &init_net.ipv4.sysctl_tcp_retries2,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_orphan_retries",
		.data		= &init_net.ipv4.sysctl_tcp_orphan_retries,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_fin_timeout",
		.data		= &init_net.ipv4.sysctl_tcp_fin_समयout,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "tcp_notsent_lowat",
		.data		= &init_net.ipv4.sysctl_tcp_notsent_lowat,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोuपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "tcp_tw_reuse",
		.data		= &init_net.ipv4.sysctl_tcp_tw_reuse,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &two,
	पूर्ण,
	अणु
		.procname	= "tcp_max_tw_buckets",
		.data		= &init_net.ipv4.tcp_death_row.sysctl_max_tw_buckets,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "tcp_max_syn_backlog",
		.data		= &init_net.ipv4.sysctl_max_syn_backlog,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "tcp_fastopen",
		.data		= &init_net.ipv4.sysctl_tcp_fastखोलो,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "tcp_fastopen_key",
		.mode		= 0600,
		.data		= &init_net.ipv4.sysctl_tcp_fastखोलो,
		/* maxlen to prपूर्णांक the list of keys in hex (*2), with dashes
		 * separating द्विगुनwords and a comma in between keys.
		 */
		.maxlen		= ((TCP_FASTOPEN_KEY_LENGTH *
				   2 * TCP_FASTOPEN_KEY_MAX) +
				   (TCP_FASTOPEN_KEY_MAX * 5)),
		.proc_handler	= proc_tcp_fastखोलो_key,
	पूर्ण,
	अणु
		.procname	= "tcp_fastopen_blackhole_timeout_sec",
		.data		= &init_net.ipv4.sysctl_tcp_fastखोलो_blackhole_समयout,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_tfo_blackhole_detect_समयout,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
	अणु
		.procname	= "fib_multipath_use_neigh",
		.data		= &init_net.ipv4.sysctl_fib_multipath_use_neigh,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "fib_multipath_hash_policy",
		.data		= &init_net.ipv4.sysctl_fib_multipath_hash_policy,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_fib_multipath_hash_policy,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &two,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "ip_unprivileged_port_start",
		.maxlen		= माप(पूर्णांक),
		.data		= &init_net.ipv4.sysctl_ip_prot_sock,
		.mode		= 0644,
		.proc_handler	= ipv4_privileged_ports,
	पूर्ण,
#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
	अणु
		.procname	= "udp_l3mdev_accept",
		.data		= &init_net.ipv4.sysctl_udp_l3mdev_accept,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "tcp_sack",
		.data		= &init_net.ipv4.sysctl_tcp_sack,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_window_scaling",
		.data		= &init_net.ipv4.sysctl_tcp_winकरोw_scaling,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_timestamps",
		.data		= &init_net.ipv4.sysctl_tcp_बारtamps,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_early_retrans",
		.data		= &init_net.ipv4.sysctl_tcp_early_retrans,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &four,
	पूर्ण,
	अणु
		.procname	= "tcp_recovery",
		.data		= &init_net.ipv4.sysctl_tcp_recovery,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname       = "tcp_thin_linear_timeouts",
		.data           = &init_net.ipv4.sysctl_tcp_thin_linear_समयouts,
		.maxlen         = माप(u8),
		.mode           = 0644,
		.proc_handler   = proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_slow_start_after_idle",
		.data		= &init_net.ipv4.sysctl_tcp_slow_start_after_idle,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_retrans_collapse",
		.data		= &init_net.ipv4.sysctl_tcp_retrans_collapse,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_stdurg",
		.data		= &init_net.ipv4.sysctl_tcp_stdurg,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_rfc1337",
		.data		= &init_net.ipv4.sysctl_tcp_rfc1337,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_abort_on_overflow",
		.data		= &init_net.ipv4.sysctl_tcp_पात_on_overflow,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_fack",
		.data		= &init_net.ipv4.sysctl_tcp_fack,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_max_reordering",
		.data		= &init_net.ipv4.sysctl_tcp_max_reordering,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "tcp_dsack",
		.data		= &init_net.ipv4.sysctl_tcp_dsack,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_app_win",
		.data		= &init_net.ipv4.sysctl_tcp_app_win,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_adv_win_scale",
		.data		= &init_net.ipv4.sysctl_tcp_adv_win_scale,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &tcp_adv_win_scale_min,
		.extra2		= &tcp_adv_win_scale_max,
	पूर्ण,
	अणु
		.procname	= "tcp_frto",
		.data		= &init_net.ipv4.sysctl_tcp_frto,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_no_metrics_save",
		.data		= &init_net.ipv4.sysctl_tcp_nometrics_save,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_no_ssthresh_metrics_save",
		.data		= &init_net.ipv4.sysctl_tcp_no_ssthresh_metrics_save,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "tcp_moderate_rcvbuf",
		.data		= &init_net.ipv4.sysctl_tcp_moderate_rcvbuf,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_tso_win_divisor",
		.data		= &init_net.ipv4.sysctl_tcp_tso_win_भागisor,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_workaround_signed_windows",
		.data		= &init_net.ipv4.sysctl_tcp_workaround_चिन्हित_winकरोws,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_limit_output_bytes",
		.data		= &init_net.ipv4.sysctl_tcp_limit_output_bytes,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "tcp_challenge_ack_limit",
		.data		= &init_net.ipv4.sysctl_tcp_challenge_ack_limit,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "tcp_min_tso_segs",
		.data		= &init_net.ipv4.sysctl_tcp_min_tso_segs,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "tcp_min_rtt_wlen",
		.data		= &init_net.ipv4.sysctl_tcp_min_rtt_wlen,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &one_day_secs
	पूर्ण,
	अणु
		.procname	= "tcp_autocorking",
		.data		= &init_net.ipv4.sysctl_tcp_स्वतःcorking,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "tcp_invalid_ratelimit",
		.data		= &init_net.ipv4.sysctl_tcp_invalid_ratelimit,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_ms_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "tcp_pacing_ss_ratio",
		.data		= &init_net.ipv4.sysctl_tcp_pacing_ss_ratio,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &thousand,
	पूर्ण,
	अणु
		.procname	= "tcp_pacing_ca_ratio",
		.data		= &init_net.ipv4.sysctl_tcp_pacing_ca_ratio,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &thousand,
	पूर्ण,
	अणु
		.procname	= "tcp_wmem",
		.data		= &init_net.ipv4.sysctl_tcp_wmem,
		.maxlen		= माप(init_net.ipv4.sysctl_tcp_wmem),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "tcp_rmem",
		.data		= &init_net.ipv4.sysctl_tcp_rmem,
		.maxlen		= माप(init_net.ipv4.sysctl_tcp_rmem),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "tcp_comp_sack_delay_ns",
		.data		= &init_net.ipv4.sysctl_tcp_comp_sack_delay_ns,
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_comp_sack_slack_ns",
		.data		= &init_net.ipv4.sysctl_tcp_comp_sack_slack_ns,
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "tcp_comp_sack_nr",
		.data		= &init_net.ipv4.sysctl_tcp_comp_sack_nr,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname       = "tcp_reflect_tos",
		.data           = &init_net.ipv4.sysctl_tcp_reflect_tos,
		.maxlen         = माप(u8),
		.mode           = 0644,
		.proc_handler   = proc_करोu8vec_minmax,
		.extra1         = SYSCTL_ZERO,
		.extra2         = SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "udp_rmem_min",
		.data		= &init_net.ipv4.sysctl_udp_rmem_min,
		.maxlen		= माप(init_net.ipv4.sysctl_udp_rmem_min),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE
	पूर्ण,
	अणु
		.procname	= "udp_wmem_min",
		.data		= &init_net.ipv4.sysctl_udp_wmem_min,
		.maxlen		= माप(init_net.ipv4.sysctl_udp_wmem_min),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE
	पूर्ण,
	अणु
		.procname	= "fib_notify_on_flag_change",
		.data		= &init_net.ipv4.sysctl_fib_notअगरy_on_flag_change,
		.maxlen		= माप(u8),
		.mode		= 0644,
		.proc_handler	= proc_करोu8vec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &two,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल __net_init पूर्णांक ipv4_sysctl_init_net(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;

	table = ipv4_net_table;
	अगर (!net_eq(net, &init_net)) अणु
		पूर्णांक i;

		table = kmemdup(table, माप(ipv4_net_table), GFP_KERNEL);
		अगर (!table)
			जाओ err_alloc;

		क्रम (i = 0; i < ARRAY_SIZE(ipv4_net_table) - 1; i++) अणु
			अगर (table[i].data) अणु
				/* Update the variables to poपूर्णांक पूर्णांकo
				 * the current काष्ठा net
				 */
				table[i].data += (व्योम *)net - (व्योम *)&init_net;
			पूर्ण अन्यथा अणु
				/* Entries without data poपूर्णांकer are global;
				 * Make them पढ़ो-only in non-init_net ns
				 */
				table[i].mode &= ~0222;
			पूर्ण
		पूर्ण
	पूर्ण

	net->ipv4.ipv4_hdr = रेजिस्टर_net_sysctl(net, "net/ipv4", table);
	अगर (!net->ipv4.ipv4_hdr)
		जाओ err_reg;

	net->ipv4.sysctl_local_reserved_ports = kzalloc(65536 / 8, GFP_KERNEL);
	अगर (!net->ipv4.sysctl_local_reserved_ports)
		जाओ err_ports;

	वापस 0;

err_ports:
	unरेजिस्टर_net_sysctl_table(net->ipv4.ipv4_hdr);
err_reg:
	अगर (!net_eq(net, &init_net))
		kमुक्त(table);
err_alloc:
	वापस -ENOMEM;
पूर्ण

अटल __net_निकास व्योम ipv4_sysctl_निकास_net(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;

	kमुक्त(net->ipv4.sysctl_local_reserved_ports);
	table = net->ipv4.ipv4_hdr->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(net->ipv4.ipv4_hdr);
	kमुक्त(table);
पूर्ण

अटल __net_initdata काष्ठा pernet_operations ipv4_sysctl_ops = अणु
	.init = ipv4_sysctl_init_net,
	.निकास = ipv4_sysctl_निकास_net,
पूर्ण;

अटल __init पूर्णांक sysctl_ipv4_init(व्योम)
अणु
	काष्ठा ctl_table_header *hdr;

	hdr = रेजिस्टर_net_sysctl(&init_net, "net/ipv4", ipv4_table);
	अगर (!hdr)
		वापस -ENOMEM;

	अगर (रेजिस्टर_pernet_subsys(&ipv4_sysctl_ops)) अणु
		unरेजिस्टर_net_sysctl_table(hdr);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

__initcall(sysctl_ipv4_init);
