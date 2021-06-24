<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NETNS_CONNTRACK_H
#घोषणा __NETNS_CONNTRACK_H

#समावेश <linux/list.h>
#समावेश <linux/list_nulls.h>
#समावेश <linux/atomic.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/netfilter/nf_conntrack_tcp.h>
#अगर_घोषित CONFIG_NF_CT_PROTO_DCCP
#समावेश <linux/netfilter/nf_conntrack_dccp.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_SCTP
#समावेश <linux/netfilter/nf_conntrack_sctp.h>
#पूर्ण_अगर
#समावेश <linux/seqlock.h>

काष्ठा ctl_table_header;
काष्ठा nf_conntrack_ecache;

काष्ठा nf_generic_net अणु
	अचिन्हित पूर्णांक समयout;
पूर्ण;

काष्ठा nf_tcp_net अणु
	अचिन्हित पूर्णांक समयouts[TCP_CONNTRACK_TIMEOUT_MAX];
	u8 tcp_loose;
	u8 tcp_be_liberal;
	u8 tcp_max_retrans;
पूर्ण;

क्रमागत udp_conntrack अणु
	UDP_CT_UNREPLIED,
	UDP_CT_REPLIED,
	UDP_CT_MAX
पूर्ण;

काष्ठा nf_udp_net अणु
	अचिन्हित पूर्णांक समयouts[UDP_CT_MAX];
पूर्ण;

काष्ठा nf_icmp_net अणु
	अचिन्हित पूर्णांक समयout;
पूर्ण;

#अगर_घोषित CONFIG_NF_CT_PROTO_DCCP
काष्ठा nf_dccp_net अणु
	u8 dccp_loose;
	अचिन्हित पूर्णांक dccp_समयout[CT_DCCP_MAX + 1];
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_CT_PROTO_SCTP
काष्ठा nf_sctp_net अणु
	अचिन्हित पूर्णांक समयouts[SCTP_CONNTRACK_MAX];
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_CT_PROTO_GRE
क्रमागत gre_conntrack अणु
	GRE_CT_UNREPLIED,
	GRE_CT_REPLIED,
	GRE_CT_MAX
पूर्ण;

काष्ठा nf_gre_net अणु
	काष्ठा list_head	keymap_list;
	अचिन्हित पूर्णांक		समयouts[GRE_CT_MAX];
पूर्ण;
#पूर्ण_अगर

काष्ठा nf_ip_net अणु
	काष्ठा nf_generic_net   generic;
	काष्ठा nf_tcp_net	tcp;
	काष्ठा nf_udp_net	udp;
	काष्ठा nf_icmp_net	icmp;
	काष्ठा nf_icmp_net	icmpv6;
#अगर_घोषित CONFIG_NF_CT_PROTO_DCCP
	काष्ठा nf_dccp_net	dccp;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_SCTP
	काष्ठा nf_sctp_net	sctp;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_GRE
	काष्ठा nf_gre_net	gre;
#पूर्ण_अगर
पूर्ण;

काष्ठा ct_pcpu अणु
	spinlock_t		lock;
	काष्ठा hlist_nulls_head unconfirmed;
	काष्ठा hlist_nulls_head dying;
पूर्ण;

काष्ठा netns_ct अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
	bool ecache_dwork_pending;
#पूर्ण_अगर
	u8			sysctl_log_invalid; /* Log invalid packets */
	u8			sysctl_events;
	u8			sysctl_acct;
	u8			sysctl_स्वतः_assign_helper;
	u8			sysctl_tstamp;
	u8			sysctl_checksum;

	काष्ठा ct_pcpu __percpu *pcpu_lists;
	काष्ठा ip_conntrack_stat __percpu *stat;
	काष्ठा nf_ct_event_notअगरier __rcu *nf_conntrack_event_cb;
	काष्ठा nf_exp_event_notअगरier __rcu *nf_expect_event_cb;
	काष्ठा nf_ip_net	nf_ct_proto;
#अगर defined(CONFIG_NF_CONNTRACK_LABELS)
	अचिन्हित पूर्णांक		labels_used;
#पूर्ण_अगर
पूर्ण;
#पूर्ण_अगर
