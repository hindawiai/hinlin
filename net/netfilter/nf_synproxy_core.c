<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <net/tcp.h>
#समावेश <net/netns/generic.h>
#समावेश <linux/proc_fs.h>

#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter/nf_synproxy.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_extend.h>
#समावेश <net/netfilter/nf_conntrack_seqadj.h>
#समावेश <net/netfilter/nf_conntrack_synproxy.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>
#समावेश <net/netfilter/nf_synproxy.h>

अचिन्हित पूर्णांक synproxy_net_id;
EXPORT_SYMBOL_GPL(synproxy_net_id);

bool
synproxy_parse_options(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक करोff,
		       स्थिर काष्ठा tcphdr *th, काष्ठा synproxy_options *opts)
अणु
	पूर्णांक length = (th->करोff * 4) - माप(*th);
	u8 buf[40], *ptr;

	अगर (unlikely(length < 0))
		वापस false;

	ptr = skb_header_poपूर्णांकer(skb, करोff + माप(*th), length, buf);
	अगर (ptr == शून्य)
		वापस false;

	opts->options = 0;
	जबतक (length > 0) अणु
		पूर्णांक opcode = *ptr++;
		पूर्णांक opsize;

		चयन (opcode) अणु
		हाल TCPOPT_EOL:
			वापस true;
		हाल TCPOPT_NOP:
			length--;
			जारी;
		शेष:
			अगर (length < 2)
				वापस true;
			opsize = *ptr++;
			अगर (opsize < 2)
				वापस true;
			अगर (opsize > length)
				वापस true;

			चयन (opcode) अणु
			हाल TCPOPT_MSS:
				अगर (opsize == TCPOLEN_MSS) अणु
					opts->mss_option = get_unaligned_be16(ptr);
					opts->options |= NF_SYNPROXY_OPT_MSS;
				पूर्ण
				अवरोध;
			हाल TCPOPT_WINDOW:
				अगर (opsize == TCPOLEN_WINDOW) अणु
					opts->wscale = *ptr;
					अगर (opts->wscale > TCP_MAX_WSCALE)
						opts->wscale = TCP_MAX_WSCALE;
					opts->options |= NF_SYNPROXY_OPT_WSCALE;
				पूर्ण
				अवरोध;
			हाल TCPOPT_TIMESTAMP:
				अगर (opsize == TCPOLEN_TIMESTAMP) अणु
					opts->tsval = get_unaligned_be32(ptr);
					opts->tsecr = get_unaligned_be32(ptr + 4);
					opts->options |= NF_SYNPROXY_OPT_TIMESTAMP;
				पूर्ण
				अवरोध;
			हाल TCPOPT_SACK_PERM:
				अगर (opsize == TCPOLEN_SACK_PERM)
					opts->options |= NF_SYNPROXY_OPT_SACK_PERM;
				अवरोध;
			पूर्ण

			ptr += opsize - 2;
			length -= opsize;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(synproxy_parse_options);

अटल अचिन्हित पूर्णांक
synproxy_options_size(स्थिर काष्ठा synproxy_options *opts)
अणु
	अचिन्हित पूर्णांक size = 0;

	अगर (opts->options & NF_SYNPROXY_OPT_MSS)
		size += TCPOLEN_MSS_ALIGNED;
	अगर (opts->options & NF_SYNPROXY_OPT_TIMESTAMP)
		size += TCPOLEN_TSTAMP_ALIGNED;
	अन्यथा अगर (opts->options & NF_SYNPROXY_OPT_SACK_PERM)
		size += TCPOLEN_SACKPERM_ALIGNED;
	अगर (opts->options & NF_SYNPROXY_OPT_WSCALE)
		size += TCPOLEN_WSCALE_ALIGNED;

	वापस size;
पूर्ण

अटल व्योम
synproxy_build_options(काष्ठा tcphdr *th, स्थिर काष्ठा synproxy_options *opts)
अणु
	__be32 *ptr = (__be32 *)(th + 1);
	u8 options = opts->options;

	अगर (options & NF_SYNPROXY_OPT_MSS)
		*ptr++ = htonl((TCPOPT_MSS << 24) |
			       (TCPOLEN_MSS << 16) |
			       opts->mss_option);

	अगर (options & NF_SYNPROXY_OPT_TIMESTAMP) अणु
		अगर (options & NF_SYNPROXY_OPT_SACK_PERM)
			*ptr++ = htonl((TCPOPT_SACK_PERM << 24) |
				       (TCPOLEN_SACK_PERM << 16) |
				       (TCPOPT_TIMESTAMP << 8) |
				       TCPOLEN_TIMESTAMP);
		अन्यथा
			*ptr++ = htonl((TCPOPT_NOP << 24) |
				       (TCPOPT_NOP << 16) |
				       (TCPOPT_TIMESTAMP << 8) |
				       TCPOLEN_TIMESTAMP);

		*ptr++ = htonl(opts->tsval);
		*ptr++ = htonl(opts->tsecr);
	पूर्ण अन्यथा अगर (options & NF_SYNPROXY_OPT_SACK_PERM)
		*ptr++ = htonl((TCPOPT_NOP << 24) |
			       (TCPOPT_NOP << 16) |
			       (TCPOPT_SACK_PERM << 8) |
			       TCPOLEN_SACK_PERM);

	अगर (options & NF_SYNPROXY_OPT_WSCALE)
		*ptr++ = htonl((TCPOPT_NOP << 24) |
			       (TCPOPT_WINDOW << 16) |
			       (TCPOLEN_WINDOW << 8) |
			       opts->wscale);
पूर्ण

व्योम synproxy_init_बारtamp_cookie(स्थिर काष्ठा nf_synproxy_info *info,
				    काष्ठा synproxy_options *opts)
अणु
	opts->tsecr = opts->tsval;
	opts->tsval = tcp_समय_stamp_raw() & ~0x3f;

	अगर (opts->options & NF_SYNPROXY_OPT_WSCALE) अणु
		opts->tsval |= opts->wscale;
		opts->wscale = info->wscale;
	पूर्ण अन्यथा
		opts->tsval |= 0xf;

	अगर (opts->options & NF_SYNPROXY_OPT_SACK_PERM)
		opts->tsval |= 1 << 4;

	अगर (opts->options & NF_SYNPROXY_OPT_ECN)
		opts->tsval |= 1 << 5;
पूर्ण
EXPORT_SYMBOL_GPL(synproxy_init_बारtamp_cookie);

अटल व्योम
synproxy_check_बारtamp_cookie(काष्ठा synproxy_options *opts)
अणु
	opts->wscale = opts->tsecr & 0xf;
	अगर (opts->wscale != 0xf)
		opts->options |= NF_SYNPROXY_OPT_WSCALE;

	opts->options |= opts->tsecr & (1 << 4) ? NF_SYNPROXY_OPT_SACK_PERM : 0;

	opts->options |= opts->tsecr & (1 << 5) ? NF_SYNPROXY_OPT_ECN : 0;
पूर्ण

अटल अचिन्हित पूर्णांक
synproxy_tstamp_adjust(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
		       काष्ठा tcphdr *th, काष्ठा nf_conn *ct,
		       क्रमागत ip_conntrack_info ctinfo,
		       स्थिर काष्ठा nf_conn_synproxy *synproxy)
अणु
	अचिन्हित पूर्णांक optoff, optend;
	__be32 *ptr, old;

	अगर (synproxy->tsoff == 0)
		वापस 1;

	optoff = protoff + माप(काष्ठा tcphdr);
	optend = protoff + th->करोff * 4;

	अगर (skb_ensure_writable(skb, optend))
		वापस 0;

	जबतक (optoff < optend) अणु
		अचिन्हित अक्षर *op = skb->data + optoff;

		चयन (op[0]) अणु
		हाल TCPOPT_EOL:
			वापस 1;
		हाल TCPOPT_NOP:
			optoff++;
			जारी;
		शेष:
			अगर (optoff + 1 == optend ||
			    optoff + op[1] > optend ||
			    op[1] < 2)
				वापस 0;
			अगर (op[0] == TCPOPT_TIMESTAMP &&
			    op[1] == TCPOLEN_TIMESTAMP) अणु
				अगर (CTINFO2सूची(ctinfo) == IP_CT_सूची_REPLY) अणु
					ptr = (__be32 *)&op[2];
					old = *ptr;
					*ptr = htonl(ntohl(*ptr) -
						     synproxy->tsoff);
				पूर्ण अन्यथा अणु
					ptr = (__be32 *)&op[6];
					old = *ptr;
					*ptr = htonl(ntohl(*ptr) +
						     synproxy->tsoff);
				पूर्ण
				inet_proto_csum_replace4(&th->check, skb,
							 old, *ptr, false);
				वापस 1;
			पूर्ण
			optoff += op[1];
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल काष्ठा nf_ct_ext_type nf_ct_synproxy_extend __पढ़ो_mostly = अणु
	.len		= माप(काष्ठा nf_conn_synproxy),
	.align		= __alignof__(काष्ठा nf_conn_synproxy),
	.id		= NF_CT_EXT_SYNPROXY,
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम *synproxy_cpu_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा synproxy_net *snet = synproxy_pernet(seq_file_net(seq));
	पूर्णांक cpu;

	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	क्रम (cpu = *pos - 1; cpu < nr_cpu_ids; cpu++) अणु
		अगर (!cpu_possible(cpu))
			जारी;
		*pos = cpu + 1;
		वापस per_cpu_ptr(snet->stats, cpu);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *synproxy_cpu_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा synproxy_net *snet = synproxy_pernet(seq_file_net(seq));
	पूर्णांक cpu;

	क्रम (cpu = *pos; cpu < nr_cpu_ids; cpu++) अणु
		अगर (!cpu_possible(cpu))
			जारी;
		*pos = cpu + 1;
		वापस per_cpu_ptr(snet->stats, cpu);
	पूर्ण
	(*pos)++;
	वापस शून्य;
पूर्ण

अटल व्योम synproxy_cpu_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	वापस;
पूर्ण

अटल पूर्णांक synproxy_cpu_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा synproxy_stats *stats = v;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "entries\t\tsyn_received\t"
			      "cookie_invalid\tcookie_valid\t"
			      "cookie_retrans\tconn_reopened\n");
		वापस 0;
	पूर्ण

	seq_म_लिखो(seq, "%08x\t%08x\t%08x\t%08x\t%08x\t%08x\n", 0,
		   stats->syn_received,
		   stats->cookie_invalid,
		   stats->cookie_valid,
		   stats->cookie_retrans,
		   stats->conn_reखोलोed);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations synproxy_cpu_seq_ops = अणु
	.start		= synproxy_cpu_seq_start,
	.next		= synproxy_cpu_seq_next,
	.stop		= synproxy_cpu_seq_stop,
	.show		= synproxy_cpu_seq_show,
पूर्ण;

अटल पूर्णांक __net_init synproxy_proc_init(काष्ठा net *net)
अणु
	अगर (!proc_create_net("synproxy", 0444, net->proc_net_stat,
			&synproxy_cpu_seq_ops, माप(काष्ठा seq_net_निजी)))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास synproxy_proc_निकास(काष्ठा net *net)
अणु
	हटाओ_proc_entry("synproxy", net->proc_net_stat);
पूर्ण
#अन्यथा
अटल पूर्णांक __net_init synproxy_proc_init(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

अटल व्योम __net_निकास synproxy_proc_निकास(काष्ठा net *net)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल पूर्णांक __net_init synproxy_net_init(काष्ठा net *net)
अणु
	काष्ठा synproxy_net *snet = synproxy_pernet(net);
	काष्ठा nf_conn *ct;
	पूर्णांक err = -ENOMEM;

	ct = nf_ct_पंचांगpl_alloc(net, &nf_ct_zone_dflt, GFP_KERNEL);
	अगर (!ct)
		जाओ err1;

	अगर (!nfct_seqadj_ext_add(ct))
		जाओ err2;
	अगर (!nfct_synproxy_ext_add(ct))
		जाओ err2;

	__set_bit(IPS_CONFIRMED_BIT, &ct->status);
	nf_conntrack_get(&ct->ct_general);
	snet->पंचांगpl = ct;

	snet->stats = alloc_percpu(काष्ठा synproxy_stats);
	अगर (snet->stats == शून्य)
		जाओ err2;

	err = synproxy_proc_init(net);
	अगर (err < 0)
		जाओ err3;

	वापस 0;

err3:
	मुक्त_percpu(snet->stats);
err2:
	nf_ct_पंचांगpl_मुक्त(ct);
err1:
	वापस err;
पूर्ण

अटल व्योम __net_निकास synproxy_net_निकास(काष्ठा net *net)
अणु
	काष्ठा synproxy_net *snet = synproxy_pernet(net);

	nf_ct_put(snet->पंचांगpl);
	synproxy_proc_निकास(net);
	मुक्त_percpu(snet->stats);
पूर्ण

अटल काष्ठा pernet_operations synproxy_net_ops = अणु
	.init		= synproxy_net_init,
	.निकास		= synproxy_net_निकास,
	.id		= &synproxy_net_id,
	.size		= माप(काष्ठा synproxy_net),
पूर्ण;

अटल पूर्णांक __init synproxy_core_init(व्योम)
अणु
	पूर्णांक err;

	err = nf_ct_extend_रेजिस्टर(&nf_ct_synproxy_extend);
	अगर (err < 0)
		जाओ err1;

	err = रेजिस्टर_pernet_subsys(&synproxy_net_ops);
	अगर (err < 0)
		जाओ err2;

	वापस 0;

err2:
	nf_ct_extend_unरेजिस्टर(&nf_ct_synproxy_extend);
err1:
	वापस err;
पूर्ण

अटल व्योम __निकास synproxy_core_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&synproxy_net_ops);
	nf_ct_extend_unरेजिस्टर(&nf_ct_synproxy_extend);
पूर्ण

module_init(synproxy_core_init);
module_निकास(synproxy_core_निकास);

अटल काष्ठा iphdr *
synproxy_build_ip(काष्ठा net *net, काष्ठा sk_buff *skb, __be32 saddr,
		  __be32 daddr)
अणु
	काष्ठा iphdr *iph;

	skb_reset_network_header(skb);
	iph = skb_put(skb, माप(*iph));
	iph->version	= 4;
	iph->ihl	= माप(*iph) / 4;
	iph->tos	= 0;
	iph->id		= 0;
	iph->frag_off	= htons(IP_DF);
	iph->ttl	= net->ipv4.sysctl_ip_शेष_ttl;
	iph->protocol	= IPPROTO_TCP;
	iph->check	= 0;
	iph->saddr	= saddr;
	iph->daddr	= daddr;

	वापस iph;
पूर्ण

अटल व्योम
synproxy_send_tcp(काष्ठा net *net,
		  स्थिर काष्ठा sk_buff *skb, काष्ठा sk_buff *nskb,
		  काष्ठा nf_conntrack *nfct, क्रमागत ip_conntrack_info ctinfo,
		  काष्ठा iphdr *niph, काष्ठा tcphdr *nth,
		  अचिन्हित पूर्णांक tcp_hdr_size)
अणु
	nth->check = ~tcp_v4_check(tcp_hdr_size, niph->saddr, niph->daddr, 0);
	nskb->ip_summed   = CHECKSUM_PARTIAL;
	nskb->csum_start  = (अचिन्हित अक्षर *)nth - nskb->head;
	nskb->csum_offset = दुरत्व(काष्ठा tcphdr, check);

	skb_dst_set_noref(nskb, skb_dst(skb));
	nskb->protocol = htons(ETH_P_IP);
	अगर (ip_route_me_harder(net, nskb->sk, nskb, RTN_UNSPEC))
		जाओ मुक्त_nskb;

	अगर (nfct) अणु
		nf_ct_set(nskb, (काष्ठा nf_conn *)nfct, ctinfo);
		nf_conntrack_get(nfct);
	पूर्ण

	ip_local_out(net, nskb->sk, nskb);
	वापस;

मुक्त_nskb:
	kमुक्त_skb(nskb);
पूर्ण

व्योम
synproxy_send_client_synack(काष्ठा net *net,
			    स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा tcphdr *th,
			    स्थिर काष्ठा synproxy_options *opts)
अणु
	काष्ठा sk_buff *nskb;
	काष्ठा iphdr *iph, *niph;
	काष्ठा tcphdr *nth;
	अचिन्हित पूर्णांक tcp_hdr_size;
	u16 mss = opts->mss_encode;

	iph = ip_hdr(skb);

	tcp_hdr_size = माप(*nth) + synproxy_options_size(opts);
	nskb = alloc_skb(माप(*niph) + tcp_hdr_size + MAX_TCP_HEADER,
			 GFP_ATOMIC);
	अगर (!nskb)
		वापस;
	skb_reserve(nskb, MAX_TCP_HEADER);

	niph = synproxy_build_ip(net, nskb, iph->daddr, iph->saddr);

	skb_reset_transport_header(nskb);
	nth = skb_put(nskb, tcp_hdr_size);
	nth->source	= th->dest;
	nth->dest	= th->source;
	nth->seq	= htonl(__cookie_v4_init_sequence(iph, th, &mss));
	nth->ack_seq	= htonl(ntohl(th->seq) + 1);
	tcp_flag_word(nth) = TCP_FLAG_SYN | TCP_FLAG_ACK;
	अगर (opts->options & NF_SYNPROXY_OPT_ECN)
		tcp_flag_word(nth) |= TCP_FLAG_ECE;
	nth->करोff	= tcp_hdr_size / 4;
	nth->winकरोw	= 0;
	nth->check	= 0;
	nth->urg_ptr	= 0;

	synproxy_build_options(nth, opts);

	synproxy_send_tcp(net, skb, nskb, skb_nfct(skb),
			  IP_CT_ESTABLISHED_REPLY, niph, nth, tcp_hdr_size);
पूर्ण
EXPORT_SYMBOL_GPL(synproxy_send_client_synack);

अटल व्योम
synproxy_send_server_syn(काष्ठा net *net,
			 स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा tcphdr *th,
			 स्थिर काष्ठा synproxy_options *opts, u32 recv_seq)
अणु
	काष्ठा synproxy_net *snet = synproxy_pernet(net);
	काष्ठा sk_buff *nskb;
	काष्ठा iphdr *iph, *niph;
	काष्ठा tcphdr *nth;
	अचिन्हित पूर्णांक tcp_hdr_size;

	iph = ip_hdr(skb);

	tcp_hdr_size = माप(*nth) + synproxy_options_size(opts);
	nskb = alloc_skb(माप(*niph) + tcp_hdr_size + MAX_TCP_HEADER,
			 GFP_ATOMIC);
	अगर (!nskb)
		वापस;
	skb_reserve(nskb, MAX_TCP_HEADER);

	niph = synproxy_build_ip(net, nskb, iph->saddr, iph->daddr);

	skb_reset_transport_header(nskb);
	nth = skb_put(nskb, tcp_hdr_size);
	nth->source	= th->source;
	nth->dest	= th->dest;
	nth->seq	= htonl(recv_seq - 1);
	/* ack_seq is used to relay our ISN to the synproxy hook to initialize
	 * sequence number translation once a connection tracking entry exists.
	 */
	nth->ack_seq	= htonl(ntohl(th->ack_seq) - 1);
	tcp_flag_word(nth) = TCP_FLAG_SYN;
	अगर (opts->options & NF_SYNPROXY_OPT_ECN)
		tcp_flag_word(nth) |= TCP_FLAG_ECE | TCP_FLAG_CWR;
	nth->करोff	= tcp_hdr_size / 4;
	nth->winकरोw	= th->winकरोw;
	nth->check	= 0;
	nth->urg_ptr	= 0;

	synproxy_build_options(nth, opts);

	synproxy_send_tcp(net, skb, nskb, &snet->पंचांगpl->ct_general, IP_CT_NEW,
			  niph, nth, tcp_hdr_size);
पूर्ण

अटल व्योम
synproxy_send_server_ack(काष्ठा net *net,
			 स्थिर काष्ठा ip_ct_tcp *state,
			 स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा tcphdr *th,
			 स्थिर काष्ठा synproxy_options *opts)
अणु
	काष्ठा sk_buff *nskb;
	काष्ठा iphdr *iph, *niph;
	काष्ठा tcphdr *nth;
	अचिन्हित पूर्णांक tcp_hdr_size;

	iph = ip_hdr(skb);

	tcp_hdr_size = माप(*nth) + synproxy_options_size(opts);
	nskb = alloc_skb(माप(*niph) + tcp_hdr_size + MAX_TCP_HEADER,
			 GFP_ATOMIC);
	अगर (!nskb)
		वापस;
	skb_reserve(nskb, MAX_TCP_HEADER);

	niph = synproxy_build_ip(net, nskb, iph->daddr, iph->saddr);

	skb_reset_transport_header(nskb);
	nth = skb_put(nskb, tcp_hdr_size);
	nth->source	= th->dest;
	nth->dest	= th->source;
	nth->seq	= htonl(ntohl(th->ack_seq));
	nth->ack_seq	= htonl(ntohl(th->seq) + 1);
	tcp_flag_word(nth) = TCP_FLAG_ACK;
	nth->करोff	= tcp_hdr_size / 4;
	nth->winकरोw	= htons(state->seen[IP_CT_सूची_ORIGINAL].td_maxwin);
	nth->check	= 0;
	nth->urg_ptr	= 0;

	synproxy_build_options(nth, opts);

	synproxy_send_tcp(net, skb, nskb, शून्य, 0, niph, nth, tcp_hdr_size);
पूर्ण

अटल व्योम
synproxy_send_client_ack(काष्ठा net *net,
			 स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा tcphdr *th,
			 स्थिर काष्ठा synproxy_options *opts)
अणु
	काष्ठा sk_buff *nskb;
	काष्ठा iphdr *iph, *niph;
	काष्ठा tcphdr *nth;
	अचिन्हित पूर्णांक tcp_hdr_size;

	iph = ip_hdr(skb);

	tcp_hdr_size = माप(*nth) + synproxy_options_size(opts);
	nskb = alloc_skb(माप(*niph) + tcp_hdr_size + MAX_TCP_HEADER,
			 GFP_ATOMIC);
	अगर (!nskb)
		वापस;
	skb_reserve(nskb, MAX_TCP_HEADER);

	niph = synproxy_build_ip(net, nskb, iph->saddr, iph->daddr);

	skb_reset_transport_header(nskb);
	nth = skb_put(nskb, tcp_hdr_size);
	nth->source	= th->source;
	nth->dest	= th->dest;
	nth->seq	= htonl(ntohl(th->seq) + 1);
	nth->ack_seq	= th->ack_seq;
	tcp_flag_word(nth) = TCP_FLAG_ACK;
	nth->करोff	= tcp_hdr_size / 4;
	nth->winकरोw	= htons(ntohs(th->winकरोw) >> opts->wscale);
	nth->check	= 0;
	nth->urg_ptr	= 0;

	synproxy_build_options(nth, opts);

	synproxy_send_tcp(net, skb, nskb, skb_nfct(skb),
			  IP_CT_ESTABLISHED_REPLY, niph, nth, tcp_hdr_size);
पूर्ण

bool
synproxy_recv_client_ack(काष्ठा net *net,
			 स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा tcphdr *th,
			 काष्ठा synproxy_options *opts, u32 recv_seq)
अणु
	काष्ठा synproxy_net *snet = synproxy_pernet(net);
	पूर्णांक mss;

	mss = __cookie_v4_check(ip_hdr(skb), th, ntohl(th->ack_seq) - 1);
	अगर (mss == 0) अणु
		this_cpu_inc(snet->stats->cookie_invalid);
		वापस false;
	पूर्ण

	this_cpu_inc(snet->stats->cookie_valid);
	opts->mss_option = mss;
	opts->options |= NF_SYNPROXY_OPT_MSS;

	अगर (opts->options & NF_SYNPROXY_OPT_TIMESTAMP)
		synproxy_check_बारtamp_cookie(opts);

	synproxy_send_server_syn(net, skb, th, opts, recv_seq);
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(synproxy_recv_client_ack);

अचिन्हित पूर्णांक
ipv4_synproxy_hook(व्योम *priv, काष्ठा sk_buff *skb,
		   स्थिर काष्ठा nf_hook_state *nhs)
अणु
	काष्ठा net *net = nhs->net;
	काष्ठा synproxy_net *snet = synproxy_pernet(net);
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;
	काष्ठा nf_conn_synproxy *synproxy;
	काष्ठा synproxy_options opts = अणुपूर्ण;
	स्थिर काष्ठा ip_ct_tcp *state;
	काष्ठा tcphdr *th, _th;
	अचिन्हित पूर्णांक thoff;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (!ct)
		वापस NF_ACCEPT;

	synproxy = nfct_synproxy(ct);
	अगर (!synproxy)
		वापस NF_ACCEPT;

	अगर (nf_is_loopback_packet(skb) ||
	    ip_hdr(skb)->protocol != IPPROTO_TCP)
		वापस NF_ACCEPT;

	thoff = ip_hdrlen(skb);
	th = skb_header_poपूर्णांकer(skb, thoff, माप(_th), &_th);
	अगर (!th)
		वापस NF_DROP;

	state = &ct->proto.tcp;
	चयन (state->state) अणु
	हाल TCP_CONNTRACK_CLOSE:
		अगर (th->rst && CTINFO2सूची(ctinfo) != IP_CT_सूची_ORIGINAL) अणु
			nf_ct_seqadj_init(ct, ctinfo, synproxy->isn -
						      ntohl(th->seq) + 1);
			अवरोध;
		पूर्ण

		अगर (!th->syn || th->ack ||
		    CTINFO2सूची(ctinfo) != IP_CT_सूची_ORIGINAL)
			अवरोध;

		/* Reखोलोed connection - reset the sequence number and बारtamp
		 * adjusपंचांगents, they will get initialized once the connection is
		 * reestablished.
		 */
		nf_ct_seqadj_init(ct, ctinfo, 0);
		synproxy->tsoff = 0;
		this_cpu_inc(snet->stats->conn_reखोलोed);
		fallthrough;
	हाल TCP_CONNTRACK_SYN_SENT:
		अगर (!synproxy_parse_options(skb, thoff, th, &opts))
			वापस NF_DROP;

		अगर (!th->syn && th->ack &&
		    CTINFO2सूची(ctinfo) == IP_CT_सूची_ORIGINAL) अणु
			/* Keep-Alives are sent with SEG.SEQ = SND.NXT-1,
			 * thereक्रमe we need to add 1 to make the SYN sequence
			 * number match the one of first SYN.
			 */
			अगर (synproxy_recv_client_ack(net, skb, th, &opts,
						     ntohl(th->seq) + 1)) अणु
				this_cpu_inc(snet->stats->cookie_retrans);
				consume_skb(skb);
				वापस NF_STOLEN;
			पूर्ण अन्यथा अणु
				वापस NF_DROP;
			पूर्ण
		पूर्ण

		synproxy->isn = ntohl(th->ack_seq);
		अगर (opts.options & NF_SYNPROXY_OPT_TIMESTAMP)
			synproxy->its = opts.tsecr;

		nf_conntrack_event_cache(IPCT_SYNPROXY, ct);
		अवरोध;
	हाल TCP_CONNTRACK_SYN_RECV:
		अगर (!th->syn || !th->ack)
			अवरोध;

		अगर (!synproxy_parse_options(skb, thoff, th, &opts))
			वापस NF_DROP;

		अगर (opts.options & NF_SYNPROXY_OPT_TIMESTAMP) अणु
			synproxy->tsoff = opts.tsval - synproxy->its;
			nf_conntrack_event_cache(IPCT_SYNPROXY, ct);
		पूर्ण

		opts.options &= ~(NF_SYNPROXY_OPT_MSS |
				  NF_SYNPROXY_OPT_WSCALE |
				  NF_SYNPROXY_OPT_SACK_PERM);

		swap(opts.tsval, opts.tsecr);
		synproxy_send_server_ack(net, state, skb, th, &opts);

		nf_ct_seqadj_init(ct, ctinfo, synproxy->isn - ntohl(th->seq));
		nf_conntrack_event_cache(IPCT_SEQADJ, ct);

		swap(opts.tsval, opts.tsecr);
		synproxy_send_client_ack(net, skb, th, &opts);

		consume_skb(skb);
		वापस NF_STOLEN;
	शेष:
		अवरोध;
	पूर्ण

	synproxy_tstamp_adjust(skb, thoff, th, ct, ctinfo, synproxy);
	वापस NF_ACCEPT;
पूर्ण
EXPORT_SYMBOL_GPL(ipv4_synproxy_hook);

अटल स्थिर काष्ठा nf_hook_ops ipv4_synproxy_ops[] = अणु
	अणु
		.hook		= ipv4_synproxy_hook,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_LOCAL_IN,
		.priority	= NF_IP_PRI_CONNTRACK_CONFIRM - 1,
	पूर्ण,
	अणु
		.hook		= ipv4_synproxy_hook,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_POST_ROUTING,
		.priority	= NF_IP_PRI_CONNTRACK_CONFIRM - 1,
	पूर्ण,
पूर्ण;

पूर्णांक nf_synproxy_ipv4_init(काष्ठा synproxy_net *snet, काष्ठा net *net)
अणु
	पूर्णांक err;

	अगर (snet->hook_ref4 == 0) अणु
		err = nf_रेजिस्टर_net_hooks(net, ipv4_synproxy_ops,
					    ARRAY_SIZE(ipv4_synproxy_ops));
		अगर (err)
			वापस err;
	पूर्ण

	snet->hook_ref4++;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nf_synproxy_ipv4_init);

व्योम nf_synproxy_ipv4_fini(काष्ठा synproxy_net *snet, काष्ठा net *net)
अणु
	snet->hook_ref4--;
	अगर (snet->hook_ref4 == 0)
		nf_unरेजिस्टर_net_hooks(net, ipv4_synproxy_ops,
					ARRAY_SIZE(ipv4_synproxy_ops));
पूर्ण
EXPORT_SYMBOL_GPL(nf_synproxy_ipv4_fini);

#अगर IS_ENABLED(CONFIG_IPV6)
अटल काष्ठा ipv6hdr *
synproxy_build_ip_ipv6(काष्ठा net *net, काष्ठा sk_buff *skb,
		       स्थिर काष्ठा in6_addr *saddr,
		       स्थिर काष्ठा in6_addr *daddr)
अणु
	काष्ठा ipv6hdr *iph;

	skb_reset_network_header(skb);
	iph = skb_put(skb, माप(*iph));
	ip6_flow_hdr(iph, 0, 0);
	iph->hop_limit	= net->ipv6.devconf_all->hop_limit;
	iph->nexthdr	= IPPROTO_TCP;
	iph->saddr	= *saddr;
	iph->daddr	= *daddr;

	वापस iph;
पूर्ण

अटल व्योम
synproxy_send_tcp_ipv6(काष्ठा net *net,
		       स्थिर काष्ठा sk_buff *skb, काष्ठा sk_buff *nskb,
		       काष्ठा nf_conntrack *nfct, क्रमागत ip_conntrack_info ctinfo,
		       काष्ठा ipv6hdr *niph, काष्ठा tcphdr *nth,
		       अचिन्हित पूर्णांक tcp_hdr_size)
अणु
	काष्ठा dst_entry *dst;
	काष्ठा flowi6 fl6;
	पूर्णांक err;

	nth->check = ~tcp_v6_check(tcp_hdr_size, &niph->saddr, &niph->daddr, 0);
	nskb->ip_summed   = CHECKSUM_PARTIAL;
	nskb->csum_start  = (अचिन्हित अक्षर *)nth - nskb->head;
	nskb->csum_offset = दुरत्व(काष्ठा tcphdr, check);

	स_रखो(&fl6, 0, माप(fl6));
	fl6.flowi6_proto = IPPROTO_TCP;
	fl6.saddr = niph->saddr;
	fl6.daddr = niph->daddr;
	fl6.fl6_sport = nth->source;
	fl6.fl6_dport = nth->dest;
	security_skb_classअगरy_flow((काष्ठा sk_buff *)skb,
				   flowi6_to_flowi_common(&fl6));
	err = nf_ip6_route(net, &dst, flowi6_to_flowi(&fl6), false);
	अगर (err) अणु
		जाओ मुक्त_nskb;
	पूर्ण

	dst = xfrm_lookup(net, dst, flowi6_to_flowi(&fl6), शून्य, 0);
	अगर (IS_ERR(dst))
		जाओ मुक्त_nskb;

	skb_dst_set(nskb, dst);

	अगर (nfct) अणु
		nf_ct_set(nskb, (काष्ठा nf_conn *)nfct, ctinfo);
		nf_conntrack_get(nfct);
	पूर्ण

	ip6_local_out(net, nskb->sk, nskb);
	वापस;

मुक्त_nskb:
	kमुक्त_skb(nskb);
पूर्ण

व्योम
synproxy_send_client_synack_ipv6(काष्ठा net *net,
				 स्थिर काष्ठा sk_buff *skb,
				 स्थिर काष्ठा tcphdr *th,
				 स्थिर काष्ठा synproxy_options *opts)
अणु
	काष्ठा sk_buff *nskb;
	काष्ठा ipv6hdr *iph, *niph;
	काष्ठा tcphdr *nth;
	अचिन्हित पूर्णांक tcp_hdr_size;
	u16 mss = opts->mss_encode;

	iph = ipv6_hdr(skb);

	tcp_hdr_size = माप(*nth) + synproxy_options_size(opts);
	nskb = alloc_skb(माप(*niph) + tcp_hdr_size + MAX_TCP_HEADER,
			 GFP_ATOMIC);
	अगर (!nskb)
		वापस;
	skb_reserve(nskb, MAX_TCP_HEADER);

	niph = synproxy_build_ip_ipv6(net, nskb, &iph->daddr, &iph->saddr);

	skb_reset_transport_header(nskb);
	nth = skb_put(nskb, tcp_hdr_size);
	nth->source	= th->dest;
	nth->dest	= th->source;
	nth->seq	= htonl(nf_ipv6_cookie_init_sequence(iph, th, &mss));
	nth->ack_seq	= htonl(ntohl(th->seq) + 1);
	tcp_flag_word(nth) = TCP_FLAG_SYN | TCP_FLAG_ACK;
	अगर (opts->options & NF_SYNPROXY_OPT_ECN)
		tcp_flag_word(nth) |= TCP_FLAG_ECE;
	nth->करोff	= tcp_hdr_size / 4;
	nth->winकरोw	= 0;
	nth->check	= 0;
	nth->urg_ptr	= 0;

	synproxy_build_options(nth, opts);

	synproxy_send_tcp_ipv6(net, skb, nskb, skb_nfct(skb),
			       IP_CT_ESTABLISHED_REPLY, niph, nth,
			       tcp_hdr_size);
पूर्ण
EXPORT_SYMBOL_GPL(synproxy_send_client_synack_ipv6);

अटल व्योम
synproxy_send_server_syn_ipv6(काष्ठा net *net, स्थिर काष्ठा sk_buff *skb,
			      स्थिर काष्ठा tcphdr *th,
			      स्थिर काष्ठा synproxy_options *opts, u32 recv_seq)
अणु
	काष्ठा synproxy_net *snet = synproxy_pernet(net);
	काष्ठा sk_buff *nskb;
	काष्ठा ipv6hdr *iph, *niph;
	काष्ठा tcphdr *nth;
	अचिन्हित पूर्णांक tcp_hdr_size;

	iph = ipv6_hdr(skb);

	tcp_hdr_size = माप(*nth) + synproxy_options_size(opts);
	nskb = alloc_skb(माप(*niph) + tcp_hdr_size + MAX_TCP_HEADER,
			 GFP_ATOMIC);
	अगर (!nskb)
		वापस;
	skb_reserve(nskb, MAX_TCP_HEADER);

	niph = synproxy_build_ip_ipv6(net, nskb, &iph->saddr, &iph->daddr);

	skb_reset_transport_header(nskb);
	nth = skb_put(nskb, tcp_hdr_size);
	nth->source	= th->source;
	nth->dest	= th->dest;
	nth->seq	= htonl(recv_seq - 1);
	/* ack_seq is used to relay our ISN to the synproxy hook to initialize
	 * sequence number translation once a connection tracking entry exists.
	 */
	nth->ack_seq	= htonl(ntohl(th->ack_seq) - 1);
	tcp_flag_word(nth) = TCP_FLAG_SYN;
	अगर (opts->options & NF_SYNPROXY_OPT_ECN)
		tcp_flag_word(nth) |= TCP_FLAG_ECE | TCP_FLAG_CWR;
	nth->करोff	= tcp_hdr_size / 4;
	nth->winकरोw	= th->winकरोw;
	nth->check	= 0;
	nth->urg_ptr	= 0;

	synproxy_build_options(nth, opts);

	synproxy_send_tcp_ipv6(net, skb, nskb, &snet->पंचांगpl->ct_general,
			       IP_CT_NEW, niph, nth, tcp_hdr_size);
पूर्ण

अटल व्योम
synproxy_send_server_ack_ipv6(काष्ठा net *net, स्थिर काष्ठा ip_ct_tcp *state,
			      स्थिर काष्ठा sk_buff *skb,
			      स्थिर काष्ठा tcphdr *th,
			      स्थिर काष्ठा synproxy_options *opts)
अणु
	काष्ठा sk_buff *nskb;
	काष्ठा ipv6hdr *iph, *niph;
	काष्ठा tcphdr *nth;
	अचिन्हित पूर्णांक tcp_hdr_size;

	iph = ipv6_hdr(skb);

	tcp_hdr_size = माप(*nth) + synproxy_options_size(opts);
	nskb = alloc_skb(माप(*niph) + tcp_hdr_size + MAX_TCP_HEADER,
			 GFP_ATOMIC);
	अगर (!nskb)
		वापस;
	skb_reserve(nskb, MAX_TCP_HEADER);

	niph = synproxy_build_ip_ipv6(net, nskb, &iph->daddr, &iph->saddr);

	skb_reset_transport_header(nskb);
	nth = skb_put(nskb, tcp_hdr_size);
	nth->source	= th->dest;
	nth->dest	= th->source;
	nth->seq	= htonl(ntohl(th->ack_seq));
	nth->ack_seq	= htonl(ntohl(th->seq) + 1);
	tcp_flag_word(nth) = TCP_FLAG_ACK;
	nth->करोff	= tcp_hdr_size / 4;
	nth->winकरोw	= htons(state->seen[IP_CT_सूची_ORIGINAL].td_maxwin);
	nth->check	= 0;
	nth->urg_ptr	= 0;

	synproxy_build_options(nth, opts);

	synproxy_send_tcp_ipv6(net, skb, nskb, शून्य, 0, niph, nth,
			       tcp_hdr_size);
पूर्ण

अटल व्योम
synproxy_send_client_ack_ipv6(काष्ठा net *net, स्थिर काष्ठा sk_buff *skb,
			      स्थिर काष्ठा tcphdr *th,
			      स्थिर काष्ठा synproxy_options *opts)
अणु
	काष्ठा sk_buff *nskb;
	काष्ठा ipv6hdr *iph, *niph;
	काष्ठा tcphdr *nth;
	अचिन्हित पूर्णांक tcp_hdr_size;

	iph = ipv6_hdr(skb);

	tcp_hdr_size = माप(*nth) + synproxy_options_size(opts);
	nskb = alloc_skb(माप(*niph) + tcp_hdr_size + MAX_TCP_HEADER,
			 GFP_ATOMIC);
	अगर (!nskb)
		वापस;
	skb_reserve(nskb, MAX_TCP_HEADER);

	niph = synproxy_build_ip_ipv6(net, nskb, &iph->saddr, &iph->daddr);

	skb_reset_transport_header(nskb);
	nth = skb_put(nskb, tcp_hdr_size);
	nth->source	= th->source;
	nth->dest	= th->dest;
	nth->seq	= htonl(ntohl(th->seq) + 1);
	nth->ack_seq	= th->ack_seq;
	tcp_flag_word(nth) = TCP_FLAG_ACK;
	nth->करोff	= tcp_hdr_size / 4;
	nth->winकरोw	= htons(ntohs(th->winकरोw) >> opts->wscale);
	nth->check	= 0;
	nth->urg_ptr	= 0;

	synproxy_build_options(nth, opts);

	synproxy_send_tcp_ipv6(net, skb, nskb, skb_nfct(skb),
			       IP_CT_ESTABLISHED_REPLY, niph, nth,
			       tcp_hdr_size);
पूर्ण

bool
synproxy_recv_client_ack_ipv6(काष्ठा net *net,
			      स्थिर काष्ठा sk_buff *skb,
			      स्थिर काष्ठा tcphdr *th,
			      काष्ठा synproxy_options *opts, u32 recv_seq)
अणु
	काष्ठा synproxy_net *snet = synproxy_pernet(net);
	पूर्णांक mss;

	mss = nf_cookie_v6_check(ipv6_hdr(skb), th, ntohl(th->ack_seq) - 1);
	अगर (mss == 0) अणु
		this_cpu_inc(snet->stats->cookie_invalid);
		वापस false;
	पूर्ण

	this_cpu_inc(snet->stats->cookie_valid);
	opts->mss_option = mss;
	opts->options |= NF_SYNPROXY_OPT_MSS;

	अगर (opts->options & NF_SYNPROXY_OPT_TIMESTAMP)
		synproxy_check_बारtamp_cookie(opts);

	synproxy_send_server_syn_ipv6(net, skb, th, opts, recv_seq);
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(synproxy_recv_client_ack_ipv6);

अचिन्हित पूर्णांक
ipv6_synproxy_hook(व्योम *priv, काष्ठा sk_buff *skb,
		   स्थिर काष्ठा nf_hook_state *nhs)
अणु
	काष्ठा net *net = nhs->net;
	काष्ठा synproxy_net *snet = synproxy_pernet(net);
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;
	काष्ठा nf_conn_synproxy *synproxy;
	काष्ठा synproxy_options opts = अणुपूर्ण;
	स्थिर काष्ठा ip_ct_tcp *state;
	काष्ठा tcphdr *th, _th;
	__be16 frag_off;
	u8 nexthdr;
	पूर्णांक thoff;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (!ct)
		वापस NF_ACCEPT;

	synproxy = nfct_synproxy(ct);
	अगर (!synproxy)
		वापस NF_ACCEPT;

	अगर (nf_is_loopback_packet(skb))
		वापस NF_ACCEPT;

	nexthdr = ipv6_hdr(skb)->nexthdr;
	thoff = ipv6_skip_exthdr(skb, माप(काष्ठा ipv6hdr), &nexthdr,
				 &frag_off);
	अगर (thoff < 0 || nexthdr != IPPROTO_TCP)
		वापस NF_ACCEPT;

	th = skb_header_poपूर्णांकer(skb, thoff, माप(_th), &_th);
	अगर (!th)
		वापस NF_DROP;

	state = &ct->proto.tcp;
	चयन (state->state) अणु
	हाल TCP_CONNTRACK_CLOSE:
		अगर (th->rst && CTINFO2सूची(ctinfo) != IP_CT_सूची_ORIGINAL) अणु
			nf_ct_seqadj_init(ct, ctinfo, synproxy->isn -
						      ntohl(th->seq) + 1);
			अवरोध;
		पूर्ण

		अगर (!th->syn || th->ack ||
		    CTINFO2सूची(ctinfo) != IP_CT_सूची_ORIGINAL)
			अवरोध;

		/* Reखोलोed connection - reset the sequence number and बारtamp
		 * adjusपंचांगents, they will get initialized once the connection is
		 * reestablished.
		 */
		nf_ct_seqadj_init(ct, ctinfo, 0);
		synproxy->tsoff = 0;
		this_cpu_inc(snet->stats->conn_reखोलोed);
		fallthrough;
	हाल TCP_CONNTRACK_SYN_SENT:
		अगर (!synproxy_parse_options(skb, thoff, th, &opts))
			वापस NF_DROP;

		अगर (!th->syn && th->ack &&
		    CTINFO2सूची(ctinfo) == IP_CT_सूची_ORIGINAL) अणु
			/* Keep-Alives are sent with SEG.SEQ = SND.NXT-1,
			 * thereक्रमe we need to add 1 to make the SYN sequence
			 * number match the one of first SYN.
			 */
			अगर (synproxy_recv_client_ack_ipv6(net, skb, th, &opts,
							  ntohl(th->seq) + 1)) अणु
				this_cpu_inc(snet->stats->cookie_retrans);
				consume_skb(skb);
				वापस NF_STOLEN;
			पूर्ण अन्यथा अणु
				वापस NF_DROP;
			पूर्ण
		पूर्ण

		synproxy->isn = ntohl(th->ack_seq);
		अगर (opts.options & NF_SYNPROXY_OPT_TIMESTAMP)
			synproxy->its = opts.tsecr;

		nf_conntrack_event_cache(IPCT_SYNPROXY, ct);
		अवरोध;
	हाल TCP_CONNTRACK_SYN_RECV:
		अगर (!th->syn || !th->ack)
			अवरोध;

		अगर (!synproxy_parse_options(skb, thoff, th, &opts))
			वापस NF_DROP;

		अगर (opts.options & NF_SYNPROXY_OPT_TIMESTAMP) अणु
			synproxy->tsoff = opts.tsval - synproxy->its;
			nf_conntrack_event_cache(IPCT_SYNPROXY, ct);
		पूर्ण

		opts.options &= ~(NF_SYNPROXY_OPT_MSS |
				  NF_SYNPROXY_OPT_WSCALE |
				  NF_SYNPROXY_OPT_SACK_PERM);

		swap(opts.tsval, opts.tsecr);
		synproxy_send_server_ack_ipv6(net, state, skb, th, &opts);

		nf_ct_seqadj_init(ct, ctinfo, synproxy->isn - ntohl(th->seq));
		nf_conntrack_event_cache(IPCT_SEQADJ, ct);

		swap(opts.tsval, opts.tsecr);
		synproxy_send_client_ack_ipv6(net, skb, th, &opts);

		consume_skb(skb);
		वापस NF_STOLEN;
	शेष:
		अवरोध;
	पूर्ण

	synproxy_tstamp_adjust(skb, thoff, th, ct, ctinfo, synproxy);
	वापस NF_ACCEPT;
पूर्ण
EXPORT_SYMBOL_GPL(ipv6_synproxy_hook);

अटल स्थिर काष्ठा nf_hook_ops ipv6_synproxy_ops[] = अणु
	अणु
		.hook		= ipv6_synproxy_hook,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_LOCAL_IN,
		.priority	= NF_IP_PRI_CONNTRACK_CONFIRM - 1,
	पूर्ण,
	अणु
		.hook		= ipv6_synproxy_hook,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_POST_ROUTING,
		.priority	= NF_IP_PRI_CONNTRACK_CONFIRM - 1,
	पूर्ण,
पूर्ण;

पूर्णांक
nf_synproxy_ipv6_init(काष्ठा synproxy_net *snet, काष्ठा net *net)
अणु
	पूर्णांक err;

	अगर (snet->hook_ref6 == 0) अणु
		err = nf_रेजिस्टर_net_hooks(net, ipv6_synproxy_ops,
					    ARRAY_SIZE(ipv6_synproxy_ops));
		अगर (err)
			वापस err;
	पूर्ण

	snet->hook_ref6++;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nf_synproxy_ipv6_init);

व्योम
nf_synproxy_ipv6_fini(काष्ठा synproxy_net *snet, काष्ठा net *net)
अणु
	snet->hook_ref6--;
	अगर (snet->hook_ref6 == 0)
		nf_unरेजिस्टर_net_hooks(net, ipv6_synproxy_ops,
					ARRAY_SIZE(ipv6_synproxy_ops));
पूर्ण
EXPORT_SYMBOL_GPL(nf_synproxy_ipv6_fini);
#पूर्ण_अगर /* CONFIG_IPV6 */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_DESCRIPTION("nftables SYNPROXY expression support");
