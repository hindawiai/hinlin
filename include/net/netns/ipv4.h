<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ipv4 in net namespaces
 */

#अगर_अघोषित __NETNS_IPV4_H__
#घोषणा __NETNS_IPV4_H__

#समावेश <linux/uidgid.h>
#समावेश <net/inet_frag.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/siphash.h>

काष्ठा ctl_table_header;
काष्ठा ipv4_devconf;
काष्ठा fib_rules_ops;
काष्ठा hlist_head;
काष्ठा fib_table;
काष्ठा sock;
काष्ठा local_ports अणु
	seqlock_t	lock;
	पूर्णांक		range[2];
	bool		warned;
पूर्ण;

काष्ठा ping_group_range अणु
	seqlock_t	lock;
	kgid_t		range[2];
पूर्ण;

काष्ठा inet_hashinfo;

काष्ठा inet_समयरुको_death_row अणु
	atomic_t		tw_count;
	अक्षर			tw_pad[L1_CACHE_BYTES - माप(atomic_t)];

	काष्ठा inet_hashinfo 	*hashinfo;
	पूर्णांक			sysctl_max_tw_buckets;
पूर्ण;

काष्ठा tcp_fastखोलो_context;

काष्ठा netns_ipv4 अणु
	/* Please keep tcp_death_row at first field in netns_ipv4 */
	काष्ठा inet_समयरुको_death_row tcp_death_row ____cacheline_aligned_in_smp;

#अगर_घोषित CONFIG_SYSCTL
	काष्ठा ctl_table_header	*क्रमw_hdr;
	काष्ठा ctl_table_header	*frags_hdr;
	काष्ठा ctl_table_header	*ipv4_hdr;
	काष्ठा ctl_table_header *route_hdr;
	काष्ठा ctl_table_header *xfrm4_hdr;
#पूर्ण_अगर
	काष्ठा ipv4_devconf	*devconf_all;
	काष्ठा ipv4_devconf	*devconf_dflt;
	काष्ठा ip_ra_chain __rcu *ra_chain;
	काष्ठा mutex		ra_mutex;
#अगर_घोषित CONFIG_IP_MULTIPLE_TABLES
	काष्ठा fib_rules_ops	*rules_ops;
	काष्ठा fib_table __rcu	*fib_मुख्य;
	काष्ठा fib_table __rcu	*fib_शेष;
	अचिन्हित पूर्णांक		fib_rules_require_fldissect;
	bool			fib_has_custom_rules;
#पूर्ण_अगर
	bool			fib_has_custom_local_routes;
	bool			fib_offload_disabled;
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	पूर्णांक			fib_num_tclassid_users;
#पूर्ण_अगर
	काष्ठा hlist_head	*fib_table_hash;
	काष्ठा sock		*fibnl;

	काष्ठा sock  * __percpu	*icmp_sk;
	काष्ठा sock		*mc_स्वतःjoin_sk;

	काष्ठा inet_peer_base	*peers;
	काष्ठा sock  * __percpu	*tcp_sk;
	काष्ठा fqdir		*fqdir;

	u8 sysctl_icmp_echo_ignore_all;
	u8 sysctl_icmp_echo_enable_probe;
	u8 sysctl_icmp_echo_ignore_broadcasts;
	u8 sysctl_icmp_ignore_bogus_error_responses;
	u8 sysctl_icmp_errors_use_inbound_अगरaddr;
	पूर्णांक sysctl_icmp_ratelimit;
	पूर्णांक sysctl_icmp_ratemask;

	काष्ठा local_ports ip_local_ports;

	u8 sysctl_tcp_ecn;
	u8 sysctl_tcp_ecn_fallback;

	u8 sysctl_ip_शेष_ttl;
	u8 sysctl_ip_no_pmtu_disc;
	u8 sysctl_ip_fwd_use_pmtu;
	u8 sysctl_ip_fwd_update_priority;
	u8 sysctl_ip_nonlocal_bind;
	u8 sysctl_ip_स्वतःbind_reuse;
	/* Shall we try to damage output packets अगर routing dev changes? */
	u8 sysctl_ip_dynaddr;
	u8 sysctl_ip_early_demux;
#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
	u8 sysctl_raw_l3mdev_accept;
#पूर्ण_अगर
	u8 sysctl_tcp_early_demux;
	u8 sysctl_udp_early_demux;

	u8 sysctl_nexthop_compat_mode;

	u8 sysctl_fwmark_reflect;
	u8 sysctl_tcp_fwmark_accept;
#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
	u8 sysctl_tcp_l3mdev_accept;
#पूर्ण_अगर
	u8 sysctl_tcp_mtu_probing;
	पूर्णांक sysctl_tcp_mtu_probe_न्यूनमान;
	पूर्णांक sysctl_tcp_base_mss;
	पूर्णांक sysctl_tcp_min_snd_mss;
	पूर्णांक sysctl_tcp_probe_threshold;
	u32 sysctl_tcp_probe_पूर्णांकerval;

	पूर्णांक sysctl_tcp_keepalive_समय;
	पूर्णांक sysctl_tcp_keepalive_पूर्णांकvl;
	u8 sysctl_tcp_keepalive_probes;

	u8 sysctl_tcp_syn_retries;
	u8 sysctl_tcp_synack_retries;
	u8 sysctl_tcp_syncookies;
	पूर्णांक sysctl_tcp_reordering;
	u8 sysctl_tcp_retries1;
	u8 sysctl_tcp_retries2;
	u8 sysctl_tcp_orphan_retries;
	u8 sysctl_tcp_tw_reuse;
	पूर्णांक sysctl_tcp_fin_समयout;
	अचिन्हित पूर्णांक sysctl_tcp_notsent_lowat;
	u8 sysctl_tcp_sack;
	u8 sysctl_tcp_winकरोw_scaling;
	u8 sysctl_tcp_बारtamps;
	u8 sysctl_tcp_early_retrans;
	u8 sysctl_tcp_recovery;
	u8 sysctl_tcp_thin_linear_समयouts;
	u8 sysctl_tcp_slow_start_after_idle;
	u8 sysctl_tcp_retrans_collapse;
	u8 sysctl_tcp_stdurg;
	u8 sysctl_tcp_rfc1337;
	u8 sysctl_tcp_पात_on_overflow;
	u8 sysctl_tcp_fack; /* obsolete */
	पूर्णांक sysctl_tcp_max_reordering;
	पूर्णांक sysctl_tcp_adv_win_scale;
	u8 sysctl_tcp_dsack;
	u8 sysctl_tcp_app_win;
	u8 sysctl_tcp_frto;
	u8 sysctl_tcp_nometrics_save;
	u8 sysctl_tcp_no_ssthresh_metrics_save;
	u8 sysctl_tcp_moderate_rcvbuf;
	u8 sysctl_tcp_tso_win_भागisor;
	u8 sysctl_tcp_workaround_चिन्हित_winकरोws;
	पूर्णांक sysctl_tcp_limit_output_bytes;
	पूर्णांक sysctl_tcp_challenge_ack_limit;
	पूर्णांक sysctl_tcp_min_rtt_wlen;
	u8 sysctl_tcp_min_tso_segs;
	u8 sysctl_tcp_स्वतःcorking;
	u8 sysctl_tcp_reflect_tos;
	u8 sysctl_tcp_comp_sack_nr;
	पूर्णांक sysctl_tcp_invalid_ratelimit;
	पूर्णांक sysctl_tcp_pacing_ss_ratio;
	पूर्णांक sysctl_tcp_pacing_ca_ratio;
	पूर्णांक sysctl_tcp_wmem[3];
	पूर्णांक sysctl_tcp_rmem[3];
	अचिन्हित दीर्घ sysctl_tcp_comp_sack_delay_ns;
	अचिन्हित दीर्घ sysctl_tcp_comp_sack_slack_ns;
	पूर्णांक sysctl_max_syn_backlog;
	पूर्णांक sysctl_tcp_fastखोलो;
	स्थिर काष्ठा tcp_congestion_ops __rcu  *tcp_congestion_control;
	काष्ठा tcp_fastखोलो_context __rcu *tcp_fastखोलो_ctx;
	spinlock_t tcp_fastखोलो_ctx_lock;
	अचिन्हित पूर्णांक sysctl_tcp_fastखोलो_blackhole_समयout;
	atomic_t tfo_active_disable_बार;
	अचिन्हित दीर्घ tfo_active_disable_stamp;

	पूर्णांक sysctl_udp_wmem_min;
	पूर्णांक sysctl_udp_rmem_min;

	u8 sysctl_fib_notअगरy_on_flag_change;

#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
	u8 sysctl_udp_l3mdev_accept;
#पूर्ण_अगर

	u8 sysctl_igmp_llm_reports;
	पूर्णांक sysctl_igmp_max_memberships;
	पूर्णांक sysctl_igmp_max_msf;
	पूर्णांक sysctl_igmp_qrv;

	काष्ठा ping_group_range ping_group_range;

	atomic_t dev_addr_genid;

#अगर_घोषित CONFIG_SYSCTL
	अचिन्हित दीर्घ *sysctl_local_reserved_ports;
	पूर्णांक sysctl_ip_prot_sock;
#पूर्ण_अगर

#अगर_घोषित CONFIG_IP_MROUTE
#अगर_अघोषित CONFIG_IP_MROUTE_MULTIPLE_TABLES
	काष्ठा mr_table		*mrt;
#अन्यथा
	काष्ठा list_head	mr_tables;
	काष्ठा fib_rules_ops	*mr_rules_ops;
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
	u8 sysctl_fib_multipath_use_neigh;
	u8 sysctl_fib_multipath_hash_policy;
#पूर्ण_अगर

	काष्ठा fib_notअगरier_ops	*notअगरier_ops;
	अचिन्हित पूर्णांक	fib_seq;	/* रक्षित by rtnl_mutex */

	काष्ठा fib_notअगरier_ops	*ipmr_notअगरier_ops;
	अचिन्हित पूर्णांक	ipmr_seq;	/* रक्षित by rtnl_mutex */

	atomic_t	rt_genid;
	siphash_key_t	ip_id_key;
पूर्ण;
#पूर्ण_अगर
