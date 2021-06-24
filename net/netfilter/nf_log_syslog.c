<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/icmp.h>
#समावेश <net/udp.h>
#समावेश <net/tcp.h>
#समावेश <net/route.h>

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_bridge.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter/xt_LOG.h>
#समावेश <net/netfilter/nf_log.h>

अटल स्थिर काष्ठा nf_loginfo शेष_loginfo = अणु
	.type	= NF_LOG_TYPE_LOG,
	.u = अणु
		.log = अणु
			.level	  = LOGLEVEL_NOTICE,
			.logflags = NF_LOG_DEFAULT_MASK,
		पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा arppayload अणु
	अचिन्हित अक्षर mac_src[ETH_ALEN];
	अचिन्हित अक्षर ip_src[4];
	अचिन्हित अक्षर mac_dst[ETH_ALEN];
	अचिन्हित अक्षर ip_dst[4];
पूर्ण;

अटल व्योम nf_log_dump_vlan(काष्ठा nf_log_buf *m, स्थिर काष्ठा sk_buff *skb)
अणु
	u16 vid;

	अगर (!skb_vlan_tag_present(skb))
		वापस;

	vid = skb_vlan_tag_get(skb);
	nf_log_buf_add(m, "VPROTO=%04x VID=%u ", ntohs(skb->vlan_proto), vid);
पूर्ण
अटल व्योम noअंतरभूत_क्रम_stack
dump_arp_packet(काष्ठा nf_log_buf *m,
		स्थिर काष्ठा nf_loginfo *info,
		स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक nhoff)
अणु
	स्थिर काष्ठा arppayload *ap;
	काष्ठा arppayload _arpp;
	स्थिर काष्ठा arphdr *ah;
	अचिन्हित पूर्णांक logflags;
	काष्ठा arphdr _arph;

	ah = skb_header_poपूर्णांकer(skb, 0, माप(_arph), &_arph);
	अगर (!ah) अणु
		nf_log_buf_add(m, "TRUNCATED");
		वापस;
	पूर्ण

	अगर (info->type == NF_LOG_TYPE_LOG)
		logflags = info->u.log.logflags;
	अन्यथा
		logflags = NF_LOG_DEFAULT_MASK;

	अगर (logflags & NF_LOG_MACDECODE) अणु
		nf_log_buf_add(m, "MACSRC=%pM MACDST=%pM ",
			       eth_hdr(skb)->h_source, eth_hdr(skb)->h_dest);
		nf_log_dump_vlan(m, skb);
		nf_log_buf_add(m, "MACPROTO=%04x ",
			       ntohs(eth_hdr(skb)->h_proto));
	पूर्ण

	nf_log_buf_add(m, "ARP HTYPE=%d PTYPE=0x%04x OPCODE=%d",
		       ntohs(ah->ar_hrd), ntohs(ah->ar_pro), ntohs(ah->ar_op));
	/* If it's क्रम Ethernet and the lengths are OK, then log the ARP
	 * payload.
	 */
	अगर (ah->ar_hrd != htons(ARPHRD_ETHER) ||
	    ah->ar_hln != ETH_ALEN ||
	    ah->ar_pln != माप(__be32))
		वापस;

	ap = skb_header_poपूर्णांकer(skb, माप(_arph), माप(_arpp), &_arpp);
	अगर (!ap) अणु
		nf_log_buf_add(m, " INCOMPLETE [%zu bytes]",
			       skb->len - माप(_arph));
		वापस;
	पूर्ण
	nf_log_buf_add(m, " MACSRC=%pM IPSRC=%pI4 MACDST=%pM IPDST=%pI4",
		       ap->mac_src, ap->ip_src, ap->mac_dst, ap->ip_dst);
पूर्ण

अटल व्योम
nf_log_dump_packet_common(काष्ठा nf_log_buf *m, u8 pf,
			  अचिन्हित पूर्णांक hooknum, स्थिर काष्ठा sk_buff *skb,
			  स्थिर काष्ठा net_device *in,
			  स्थिर काष्ठा net_device *out,
			  स्थिर काष्ठा nf_loginfo *loginfo, स्थिर अक्षर *prefix)
अणु
	स्थिर काष्ठा net_device *physoutdev __maybe_unused;
	स्थिर काष्ठा net_device *physindev __maybe_unused;

	nf_log_buf_add(m, KERN_SOH "%c%sIN=%s OUT=%s ",
		       '0' + loginfo->u.log.level, prefix,
			in ? in->name : "",
			out ? out->name : "");
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	physindev = nf_bridge_get_physindev(skb);
	अगर (physindev && in != physindev)
		nf_log_buf_add(m, "PHYSIN=%s ", physindev->name);
	physoutdev = nf_bridge_get_physoutdev(skb);
	अगर (physoutdev && out != physoutdev)
		nf_log_buf_add(m, "PHYSOUT=%s ", physoutdev->name);
#पूर्ण_अगर
पूर्ण

अटल व्योम nf_log_arp_packet(काष्ठा net *net, u_पूर्णांक8_t pf,
			      अचिन्हित पूर्णांक hooknum, स्थिर काष्ठा sk_buff *skb,
			      स्थिर काष्ठा net_device *in,
			      स्थिर काष्ठा net_device *out,
			      स्थिर काष्ठा nf_loginfo *loginfo,
			      स्थिर अक्षर *prefix)
अणु
	काष्ठा nf_log_buf *m;

	/* FIXME: Disabled from containers until syslog ns is supported */
	अगर (!net_eq(net, &init_net) && !sysctl_nf_log_all_netns)
		वापस;

	m = nf_log_buf_खोलो();

	अगर (!loginfo)
		loginfo = &शेष_loginfo;

	nf_log_dump_packet_common(m, pf, hooknum, skb, in, out, loginfo,
				  prefix);
	dump_arp_packet(m, loginfo, skb, 0);

	nf_log_buf_बंद(m);
पूर्ण

अटल काष्ठा nf_logger nf_arp_logger __पढ़ो_mostly = अणु
	.name		= "nf_log_arp",
	.type		= NF_LOG_TYPE_LOG,
	.logfn		= nf_log_arp_packet,
	.me		= THIS_MODULE,
पूर्ण;

अटल व्योम nf_log_dump_sk_uid_gid(काष्ठा net *net, काष्ठा nf_log_buf *m,
				   काष्ठा sock *sk)
अणु
	अगर (!sk || !sk_fullsock(sk) || !net_eq(net, sock_net(sk)))
		वापस;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	अगर (sk->sk_socket && sk->sk_socket->file) अणु
		स्थिर काष्ठा cred *cred = sk->sk_socket->file->f_cred;

		nf_log_buf_add(m, "UID=%u GID=%u ",
			       from_kuid_munged(&init_user_ns, cred->fsuid),
			       from_kgid_munged(&init_user_ns, cred->fsgid));
	पूर्ण
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
nf_log_dump_tcp_header(काष्ठा nf_log_buf *m,
		       स्थिर काष्ठा sk_buff *skb,
		       u8 proto, पूर्णांक fragment,
		       अचिन्हित पूर्णांक offset,
		       अचिन्हित पूर्णांक logflags)
अणु
	काष्ठा tcphdr _tcph;
	स्थिर काष्ठा tcphdr *th;

	/* Max length: 10 "PROTO=TCP " */
	nf_log_buf_add(m, "PROTO=TCP ");

	अगर (fragment)
		वापस 0;

	/* Max length: 25 "INCOMPLETE [65535 bytes] " */
	th = skb_header_poपूर्णांकer(skb, offset, माप(_tcph), &_tcph);
	अगर (!th) अणु
		nf_log_buf_add(m, "INCOMPLETE [%u bytes] ", skb->len - offset);
		वापस 1;
	पूर्ण

	/* Max length: 20 "SPT=65535 DPT=65535 " */
	nf_log_buf_add(m, "SPT=%u DPT=%u ",
		       ntohs(th->source), ntohs(th->dest));
	/* Max length: 30 "SEQ=4294967295 ACK=4294967295 " */
	अगर (logflags & NF_LOG_TCPSEQ) अणु
		nf_log_buf_add(m, "SEQ=%u ACK=%u ",
			       ntohl(th->seq), ntohl(th->ack_seq));
	पूर्ण

	/* Max length: 13 "WINDOW=65535 " */
	nf_log_buf_add(m, "WINDOW=%u ", ntohs(th->winकरोw));
	/* Max length: 9 "RES=0x3C " */
	nf_log_buf_add(m, "RES=0x%02x ", (u_पूर्णांक8_t)(ntohl(tcp_flag_word(th) &
					    TCP_RESERVED_BITS) >> 22));
	/* Max length: 32 "CWR ECE URG ACK PSH RST SYN FIN " */
	अगर (th->cwr)
		nf_log_buf_add(m, "CWR ");
	अगर (th->ece)
		nf_log_buf_add(m, "ECE ");
	अगर (th->urg)
		nf_log_buf_add(m, "URG ");
	अगर (th->ack)
		nf_log_buf_add(m, "ACK ");
	अगर (th->psh)
		nf_log_buf_add(m, "PSH ");
	अगर (th->rst)
		nf_log_buf_add(m, "RST ");
	अगर (th->syn)
		nf_log_buf_add(m, "SYN ");
	अगर (th->fin)
		nf_log_buf_add(m, "FIN ");
	/* Max length: 11 "URGP=65535 " */
	nf_log_buf_add(m, "URGP=%u ", ntohs(th->urg_ptr));

	अगर ((logflags & NF_LOG_TCPOPT) && th->करोff * 4 > माप(काष्ठा tcphdr)) अणु
		अचिन्हित पूर्णांक optsize = th->करोff * 4 - माप(काष्ठा tcphdr);
		u8 _opt[60 - माप(काष्ठा tcphdr)];
		अचिन्हित पूर्णांक i;
		स्थिर u8 *op;

		op = skb_header_poपूर्णांकer(skb, offset + माप(काष्ठा tcphdr),
					optsize, _opt);
		अगर (!op) अणु
			nf_log_buf_add(m, "OPT (TRUNCATED)");
			वापस 1;
		पूर्ण

		/* Max length: 127 "OPT (" 15*4*2अक्षरs ") " */
		nf_log_buf_add(m, "OPT (");
		क्रम (i = 0; i < optsize; i++)
			nf_log_buf_add(m, "%02X", op[i]);

		nf_log_buf_add(m, ") ");
	पूर्ण

	वापस 0;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
nf_log_dump_udp_header(काष्ठा nf_log_buf *m,
		       स्थिर काष्ठा sk_buff *skb,
		       u8 proto, पूर्णांक fragment,
		       अचिन्हित पूर्णांक offset)
अणु
	काष्ठा udphdr _udph;
	स्थिर काष्ठा udphdr *uh;

	अगर (proto == IPPROTO_UDP)
		/* Max length: 10 "PROTO=UDP "     */
		nf_log_buf_add(m, "PROTO=UDP ");
	अन्यथा	/* Max length: 14 "PROTO=UDPLITE " */
		nf_log_buf_add(m, "PROTO=UDPLITE ");

	अगर (fragment)
		जाओ out;

	/* Max length: 25 "INCOMPLETE [65535 bytes] " */
	uh = skb_header_poपूर्णांकer(skb, offset, माप(_udph), &_udph);
	अगर (!uh) अणु
		nf_log_buf_add(m, "INCOMPLETE [%u bytes] ", skb->len - offset);

		वापस 1;
	पूर्ण

	/* Max length: 20 "SPT=65535 DPT=65535 " */
	nf_log_buf_add(m, "SPT=%u DPT=%u LEN=%u ",
		       ntohs(uh->source), ntohs(uh->dest), ntohs(uh->len));

out:
	वापस 0;
पूर्ण

/* One level of recursion won't समाप्त us */
अटल noअंतरभूत_क्रम_stack व्योम
dump_ipv4_packet(काष्ठा net *net, काष्ठा nf_log_buf *m,
		 स्थिर काष्ठा nf_loginfo *info,
		 स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक iphoff)
अणु
	स्थिर काष्ठा iphdr *ih;
	अचिन्हित पूर्णांक logflags;
	काष्ठा iphdr _iph;

	अगर (info->type == NF_LOG_TYPE_LOG)
		logflags = info->u.log.logflags;
	अन्यथा
		logflags = NF_LOG_DEFAULT_MASK;

	ih = skb_header_poपूर्णांकer(skb, iphoff, माप(_iph), &_iph);
	अगर (!ih) अणु
		nf_log_buf_add(m, "TRUNCATED");
		वापस;
	पूर्ण

	/* Important fields:
	 * TOS, len, DF/MF, fragment offset, TTL, src, dst, options.
	 * Max length: 40 "SRC=255.255.255.255 DST=255.255.255.255 "
	 */
	nf_log_buf_add(m, "SRC=%pI4 DST=%pI4 ", &ih->saddr, &ih->daddr);

	/* Max length: 46 "LEN=65535 TOS=0xFF PREC=0xFF TTL=255 ID=65535 " */
	nf_log_buf_add(m, "LEN=%u TOS=0x%02X PREC=0x%02X TTL=%u ID=%u ",
		       ntohs(ih->tot_len), ih->tos & IPTOS_TOS_MASK,
		       ih->tos & IPTOS_PREC_MASK, ih->ttl, ntohs(ih->id));

	/* Max length: 6 "CE DF MF " */
	अगर (ntohs(ih->frag_off) & IP_CE)
		nf_log_buf_add(m, "CE ");
	अगर (ntohs(ih->frag_off) & IP_DF)
		nf_log_buf_add(m, "DF ");
	अगर (ntohs(ih->frag_off) & IP_MF)
		nf_log_buf_add(m, "MF ");

	/* Max length: 11 "FRAG:65535 " */
	अगर (ntohs(ih->frag_off) & IP_OFFSET)
		nf_log_buf_add(m, "FRAG:%u ", ntohs(ih->frag_off) & IP_OFFSET);

	अगर ((logflags & NF_LOG_IPOPT) &&
	    ih->ihl * 4 > माप(काष्ठा iphdr)) अणु
		अचिन्हित अक्षर _opt[4 * 15 - माप(काष्ठा iphdr)];
		स्थिर अचिन्हित अक्षर *op;
		अचिन्हित पूर्णांक i, optsize;

		optsize = ih->ihl * 4 - माप(काष्ठा iphdr);
		op = skb_header_poपूर्णांकer(skb, iphoff + माप(_iph),
					optsize, _opt);
		अगर (!op) अणु
			nf_log_buf_add(m, "TRUNCATED");
			वापस;
		पूर्ण

		/* Max length: 127 "OPT (" 15*4*2अक्षरs ") " */
		nf_log_buf_add(m, "OPT (");
		क्रम (i = 0; i < optsize; i++)
			nf_log_buf_add(m, "%02X", op[i]);
		nf_log_buf_add(m, ") ");
	पूर्ण

	चयन (ih->protocol) अणु
	हाल IPPROTO_TCP:
		अगर (nf_log_dump_tcp_header(m, skb, ih->protocol,
					   ntohs(ih->frag_off) & IP_OFFSET,
					   iphoff + ih->ihl * 4, logflags))
			वापस;
		अवरोध;
	हाल IPPROTO_UDP:
	हाल IPPROTO_UDPLITE:
		अगर (nf_log_dump_udp_header(m, skb, ih->protocol,
					   ntohs(ih->frag_off) & IP_OFFSET,
					   iphoff + ih->ihl * 4))
			वापस;
		अवरोध;
	हाल IPPROTO_ICMP: अणु
		अटल स्थिर माप_प्रकार required_len[NR_ICMP_TYPES + 1] = अणु
			[ICMP_ECHOREPLY] = 4,
			[ICMP_DEST_UNREACH] = 8 + माप(काष्ठा iphdr),
			[ICMP_SOURCE_QUENCH] = 8 + माप(काष्ठा iphdr),
			[ICMP_REसूचीECT] = 8 + माप(काष्ठा iphdr),
			[ICMP_ECHO] = 4,
			[ICMP_TIME_EXCEEDED] = 8 + माप(काष्ठा iphdr),
			[ICMP_PARAMETERPROB] = 8 + माप(काष्ठा iphdr),
			[ICMP_TIMESTAMP] = 20,
			[ICMP_TIMESTAMPREPLY] = 20,
			[ICMP_ADDRESS] = 12,
			[ICMP_ADDRESSREPLY] = 12 पूर्ण;
		स्थिर काष्ठा icmphdr *ich;
		काष्ठा icmphdr _icmph;

		/* Max length: 11 "PROTO=ICMP " */
		nf_log_buf_add(m, "PROTO=ICMP ");

		अगर (ntohs(ih->frag_off) & IP_OFFSET)
			अवरोध;

		/* Max length: 25 "INCOMPLETE [65535 bytes] " */
		ich = skb_header_poपूर्णांकer(skb, iphoff + ih->ihl * 4,
					 माप(_icmph), &_icmph);
		अगर (!ich) अणु
			nf_log_buf_add(m, "INCOMPLETE [%u bytes] ",
				       skb->len - iphoff - ih->ihl * 4);
			अवरोध;
		पूर्ण

		/* Max length: 18 "TYPE=255 CODE=255 " */
		nf_log_buf_add(m, "TYPE=%u CODE=%u ", ich->type, ich->code);

		/* Max length: 25 "INCOMPLETE [65535 bytes] " */
		अगर (ich->type <= NR_ICMP_TYPES &&
		    required_len[ich->type] &&
		    skb->len - iphoff - ih->ihl * 4 < required_len[ich->type]) अणु
			nf_log_buf_add(m, "INCOMPLETE [%u bytes] ",
				       skb->len - iphoff - ih->ihl * 4);
			अवरोध;
		पूर्ण

		चयन (ich->type) अणु
		हाल ICMP_ECHOREPLY:
		हाल ICMP_ECHO:
			/* Max length: 19 "ID=65535 SEQ=65535 " */
			nf_log_buf_add(m, "ID=%u SEQ=%u ",
				       ntohs(ich->un.echo.id),
				       ntohs(ich->un.echo.sequence));
			अवरोध;

		हाल ICMP_PARAMETERPROB:
			/* Max length: 14 "PARAMETER=255 " */
			nf_log_buf_add(m, "PARAMETER=%u ",
				       ntohl(ich->un.gateway) >> 24);
			अवरोध;
		हाल ICMP_REसूचीECT:
			/* Max length: 24 "GATEWAY=255.255.255.255 " */
			nf_log_buf_add(m, "GATEWAY=%pI4 ", &ich->un.gateway);
			fallthrough;
		हाल ICMP_DEST_UNREACH:
		हाल ICMP_SOURCE_QUENCH:
		हाल ICMP_TIME_EXCEEDED:
			/* Max length: 3+maxlen */
			अगर (!iphoff) अणु /* Only recurse once. */
				nf_log_buf_add(m, "[");
				dump_ipv4_packet(net, m, info, skb,
						 iphoff + ih->ihl * 4 + माप(_icmph));
				nf_log_buf_add(m, "] ");
			पूर्ण

			/* Max length: 10 "MTU=65535 " */
			अगर (ich->type == ICMP_DEST_UNREACH &&
			    ich->code == ICMP_FRAG_NEEDED) अणु
				nf_log_buf_add(m, "MTU=%u ",
					       ntohs(ich->un.frag.mtu));
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	/* Max Length */
	हाल IPPROTO_AH: अणु
		स्थिर काष्ठा ip_auth_hdr *ah;
		काष्ठा ip_auth_hdr _ahdr;

		अगर (ntohs(ih->frag_off) & IP_OFFSET)
			अवरोध;

		/* Max length: 9 "PROTO=AH " */
		nf_log_buf_add(m, "PROTO=AH ");

		/* Max length: 25 "INCOMPLETE [65535 bytes] " */
		ah = skb_header_poपूर्णांकer(skb, iphoff + ih->ihl * 4,
					माप(_ahdr), &_ahdr);
		अगर (!ah) अणु
			nf_log_buf_add(m, "INCOMPLETE [%u bytes] ",
				       skb->len - iphoff - ih->ihl * 4);
			अवरोध;
		पूर्ण

		/* Length: 15 "SPI=0xF1234567 " */
		nf_log_buf_add(m, "SPI=0x%x ", ntohl(ah->spi));
		अवरोध;
	पूर्ण
	हाल IPPROTO_ESP: अणु
		स्थिर काष्ठा ip_esp_hdr *eh;
		काष्ठा ip_esp_hdr _esph;

		/* Max length: 10 "PROTO=ESP " */
		nf_log_buf_add(m, "PROTO=ESP ");

		अगर (ntohs(ih->frag_off) & IP_OFFSET)
			अवरोध;

		/* Max length: 25 "INCOMPLETE [65535 bytes] " */
		eh = skb_header_poपूर्णांकer(skb, iphoff + ih->ihl * 4,
					माप(_esph), &_esph);
		अगर (!eh) अणु
			nf_log_buf_add(m, "INCOMPLETE [%u bytes] ",
				       skb->len - iphoff - ih->ihl * 4);
			अवरोध;
		पूर्ण

		/* Length: 15 "SPI=0xF1234567 " */
		nf_log_buf_add(m, "SPI=0x%x ", ntohl(eh->spi));
		अवरोध;
	पूर्ण
	/* Max length: 10 "PROTO 255 " */
	शेष:
		nf_log_buf_add(m, "PROTO=%u ", ih->protocol);
	पूर्ण

	/* Max length: 15 "UID=4294967295 " */
	अगर ((logflags & NF_LOG_UID) && !iphoff)
		nf_log_dump_sk_uid_gid(net, m, skb->sk);

	/* Max length: 16 "MARK=0xFFFFFFFF " */
	अगर (!iphoff && skb->mark)
		nf_log_buf_add(m, "MARK=0x%x ", skb->mark);

	/* Proto    Max log string length */
	/* IP:	    40+46+6+11+127 = 230 */
	/* TCP:     10+max(25,20+30+13+9+32+11+127) = 252 */
	/* UDP:     10+max(25,20) = 35 */
	/* UDPLITE: 14+max(25,20) = 39 */
	/* ICMP:    11+max(25, 18+25+max(19,14,24+3+n+10,3+n+10)) = 91+n */
	/* ESP:     10+max(25)+15 = 50 */
	/* AH:	    9+max(25)+15 = 49 */
	/* unknown: 10 */

	/* (ICMP allows recursion one level deep) */
	/* maxlen =  IP + ICMP +  IP + max(TCP,UDP,ICMP,unknown) */
	/* maxlen = 230+   91  + 230 + 252 = 803 */
पूर्ण

अटल noअंतरभूत_क्रम_stack व्योम
dump_ipv6_packet(काष्ठा net *net, काष्ठा nf_log_buf *m,
		 स्थिर काष्ठा nf_loginfo *info,
		 स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक ip6hoff,
		 पूर्णांक recurse)
अणु
	स्थिर काष्ठा ipv6hdr *ih;
	अचिन्हित पूर्णांक hdrlen = 0;
	अचिन्हित पूर्णांक logflags;
	काष्ठा ipv6hdr _ip6h;
	अचिन्हित पूर्णांक ptr;
	u8 currenthdr;
	पूर्णांक fragment;

	अगर (info->type == NF_LOG_TYPE_LOG)
		logflags = info->u.log.logflags;
	अन्यथा
		logflags = NF_LOG_DEFAULT_MASK;

	ih = skb_header_poपूर्णांकer(skb, ip6hoff, माप(_ip6h), &_ip6h);
	अगर (!ih) अणु
		nf_log_buf_add(m, "TRUNCATED");
		वापस;
	पूर्ण

	/* Max length: 88 "SRC=0000.0000.0000.0000.0000.0000.0000.0000 DST=0000.0000.0000.0000.0000.0000.0000.0000 " */
	nf_log_buf_add(m, "SRC=%pI6 DST=%pI6 ", &ih->saddr, &ih->daddr);

	/* Max length: 44 "LEN=65535 TC=255 HOPLIMIT=255 FLOWLBL=FFFFF " */
	nf_log_buf_add(m, "LEN=%zu TC=%u HOPLIMIT=%u FLOWLBL=%u ",
		       ntohs(ih->payload_len) + माप(काष्ठा ipv6hdr),
		       (ntohl(*(__be32 *)ih) & 0x0ff00000) >> 20,
		       ih->hop_limit,
		       (ntohl(*(__be32 *)ih) & 0x000fffff));

	fragment = 0;
	ptr = ip6hoff + माप(काष्ठा ipv6hdr);
	currenthdr = ih->nexthdr;
	जबतक (currenthdr != NEXTHDR_NONE && nf_ip6_ext_hdr(currenthdr)) अणु
		काष्ठा ipv6_opt_hdr _hdr;
		स्थिर काष्ठा ipv6_opt_hdr *hp;

		hp = skb_header_poपूर्णांकer(skb, ptr, माप(_hdr), &_hdr);
		अगर (!hp) अणु
			nf_log_buf_add(m, "TRUNCATED");
			वापस;
		पूर्ण

		/* Max length: 48 "OPT (...) " */
		अगर (logflags & NF_LOG_IPOPT)
			nf_log_buf_add(m, "OPT ( ");

		चयन (currenthdr) अणु
		हाल IPPROTO_FRAGMENT: अणु
			काष्ठा frag_hdr _fhdr;
			स्थिर काष्ठा frag_hdr *fh;

			nf_log_buf_add(m, "FRAG:");
			fh = skb_header_poपूर्णांकer(skb, ptr, माप(_fhdr),
						&_fhdr);
			अगर (!fh) अणु
				nf_log_buf_add(m, "TRUNCATED ");
				वापस;
			पूर्ण

			/* Max length: 6 "65535 " */
			nf_log_buf_add(m, "%u ", ntohs(fh->frag_off) & 0xFFF8);

			/* Max length: 11 "INCOMPLETE " */
			अगर (fh->frag_off & htons(0x0001))
				nf_log_buf_add(m, "INCOMPLETE ");

			nf_log_buf_add(m, "ID:%08x ",
				       ntohl(fh->identअगरication));

			अगर (ntohs(fh->frag_off) & 0xFFF8)
				fragment = 1;

			hdrlen = 8;
			अवरोध;
		पूर्ण
		हाल IPPROTO_DSTOPTS:
		हाल IPPROTO_ROUTING:
		हाल IPPROTO_HOPOPTS:
			अगर (fragment) अणु
				अगर (logflags & NF_LOG_IPOPT)
					nf_log_buf_add(m, ")");
				वापस;
			पूर्ण
			hdrlen = ipv6_optlen(hp);
			अवरोध;
		/* Max Length */
		हाल IPPROTO_AH:
			अगर (logflags & NF_LOG_IPOPT) अणु
				काष्ठा ip_auth_hdr _ahdr;
				स्थिर काष्ठा ip_auth_hdr *ah;

				/* Max length: 3 "AH " */
				nf_log_buf_add(m, "AH ");

				अगर (fragment) अणु
					nf_log_buf_add(m, ")");
					वापस;
				पूर्ण

				ah = skb_header_poपूर्णांकer(skb, ptr, माप(_ahdr),
							&_ahdr);
				अगर (!ah) अणु
					/* Max length: 26 "INCOMPLETE [65535 bytes] )" */
					nf_log_buf_add(m, "INCOMPLETE [%u bytes] )",
						       skb->len - ptr);
					वापस;
				पूर्ण

				/* Length: 15 "SPI=0xF1234567 */
				nf_log_buf_add(m, "SPI=0x%x ", ntohl(ah->spi));
			पूर्ण

			hdrlen = ipv6_authlen(hp);
			अवरोध;
		हाल IPPROTO_ESP:
			अगर (logflags & NF_LOG_IPOPT) अणु
				काष्ठा ip_esp_hdr _esph;
				स्थिर काष्ठा ip_esp_hdr *eh;

				/* Max length: 4 "ESP " */
				nf_log_buf_add(m, "ESP ");

				अगर (fragment) अणु
					nf_log_buf_add(m, ")");
					वापस;
				पूर्ण

				/* Max length: 26 "INCOMPLETE [65535 bytes] )" */
				eh = skb_header_poपूर्णांकer(skb, ptr, माप(_esph),
							&_esph);
				अगर (!eh) अणु
					nf_log_buf_add(m, "INCOMPLETE [%u bytes] )",
						       skb->len - ptr);
					वापस;
				पूर्ण

				/* Length: 16 "SPI=0xF1234567 )" */
				nf_log_buf_add(m, "SPI=0x%x )",
					       ntohl(eh->spi));
			पूर्ण
			वापस;
		शेष:
			/* Max length: 20 "Unknown Ext Hdr 255" */
			nf_log_buf_add(m, "Unknown Ext Hdr %u", currenthdr);
			वापस;
		पूर्ण
		अगर (logflags & NF_LOG_IPOPT)
			nf_log_buf_add(m, ") ");

		currenthdr = hp->nexthdr;
		ptr += hdrlen;
	पूर्ण

	चयन (currenthdr) अणु
	हाल IPPROTO_TCP:
		अगर (nf_log_dump_tcp_header(m, skb, currenthdr, fragment,
					   ptr, logflags))
			वापस;
		अवरोध;
	हाल IPPROTO_UDP:
	हाल IPPROTO_UDPLITE:
		अगर (nf_log_dump_udp_header(m, skb, currenthdr, fragment, ptr))
			वापस;
		अवरोध;
	हाल IPPROTO_ICMPV6: अणु
		काष्ठा icmp6hdr _icmp6h;
		स्थिर काष्ठा icmp6hdr *ic;

		/* Max length: 13 "PROTO=ICMPv6 " */
		nf_log_buf_add(m, "PROTO=ICMPv6 ");

		अगर (fragment)
			अवरोध;

		/* Max length: 25 "INCOMPLETE [65535 bytes] " */
		ic = skb_header_poपूर्णांकer(skb, ptr, माप(_icmp6h), &_icmp6h);
		अगर (!ic) अणु
			nf_log_buf_add(m, "INCOMPLETE [%u bytes] ",
				       skb->len - ptr);
			वापस;
		पूर्ण

		/* Max length: 18 "TYPE=255 CODE=255 " */
		nf_log_buf_add(m, "TYPE=%u CODE=%u ",
			       ic->icmp6_type, ic->icmp6_code);

		चयन (ic->icmp6_type) अणु
		हाल ICMPV6_ECHO_REQUEST:
		हाल ICMPV6_ECHO_REPLY:
			/* Max length: 19 "ID=65535 SEQ=65535 " */
			nf_log_buf_add(m, "ID=%u SEQ=%u ",
				       ntohs(ic->icmp6_identअगरier),
				       ntohs(ic->icmp6_sequence));
			अवरोध;
		हाल ICMPV6_MGM_QUERY:
		हाल ICMPV6_MGM_REPORT:
		हाल ICMPV6_MGM_REDUCTION:
			अवरोध;

		हाल ICMPV6_PARAMPROB:
			/* Max length: 17 "POINTER=ffffffff " */
			nf_log_buf_add(m, "POINTER=%08x ",
				       ntohl(ic->icmp6_poपूर्णांकer));
			fallthrough;
		हाल ICMPV6_DEST_UNREACH:
		हाल ICMPV6_PKT_TOOBIG:
		हाल ICMPV6_TIME_EXCEED:
			/* Max length: 3+maxlen */
			अगर (recurse) अणु
				nf_log_buf_add(m, "[");
				dump_ipv6_packet(net, m, info, skb,
						 ptr + माप(_icmp6h), 0);
				nf_log_buf_add(m, "] ");
			पूर्ण

			/* Max length: 10 "MTU=65535 " */
			अगर (ic->icmp6_type == ICMPV6_PKT_TOOBIG) अणु
				nf_log_buf_add(m, "MTU=%u ",
					       ntohl(ic->icmp6_mtu));
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	/* Max length: 10 "PROTO=255 " */
	शेष:
		nf_log_buf_add(m, "PROTO=%u ", currenthdr);
	पूर्ण

	/* Max length: 15 "UID=4294967295 " */
	अगर ((logflags & NF_LOG_UID) && recurse)
		nf_log_dump_sk_uid_gid(net, m, skb->sk);

	/* Max length: 16 "MARK=0xFFFFFFFF " */
	अगर (recurse && skb->mark)
		nf_log_buf_add(m, "MARK=0x%x ", skb->mark);
पूर्ण

अटल व्योम dump_ipv4_mac_header(काष्ठा nf_log_buf *m,
				 स्थिर काष्ठा nf_loginfo *info,
				 स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;
	अचिन्हित पूर्णांक logflags = 0;

	अगर (info->type == NF_LOG_TYPE_LOG)
		logflags = info->u.log.logflags;

	अगर (!(logflags & NF_LOG_MACDECODE))
		जाओ fallback;

	चयन (dev->type) अणु
	हाल ARPHRD_ETHER:
		nf_log_buf_add(m, "MACSRC=%pM MACDST=%pM ",
			       eth_hdr(skb)->h_source, eth_hdr(skb)->h_dest);
		nf_log_dump_vlan(m, skb);
		nf_log_buf_add(m, "MACPROTO=%04x ",
			       ntohs(eth_hdr(skb)->h_proto));
		वापस;
	शेष:
		अवरोध;
	पूर्ण

fallback:
	nf_log_buf_add(m, "MAC=");
	अगर (dev->hard_header_len &&
	    skb->mac_header != skb->network_header) अणु
		स्थिर अचिन्हित अक्षर *p = skb_mac_header(skb);
		अचिन्हित पूर्णांक i;

		nf_log_buf_add(m, "%02x", *p++);
		क्रम (i = 1; i < dev->hard_header_len; i++, p++)
			nf_log_buf_add(m, ":%02x", *p);
	पूर्ण
	nf_log_buf_add(m, " ");
पूर्ण

अटल व्योम nf_log_ip_packet(काष्ठा net *net, u_पूर्णांक8_t pf,
			     अचिन्हित पूर्णांक hooknum, स्थिर काष्ठा sk_buff *skb,
			     स्थिर काष्ठा net_device *in,
			     स्थिर काष्ठा net_device *out,
			     स्थिर काष्ठा nf_loginfo *loginfo,
			     स्थिर अक्षर *prefix)
अणु
	काष्ठा nf_log_buf *m;

	/* FIXME: Disabled from containers until syslog ns is supported */
	अगर (!net_eq(net, &init_net) && !sysctl_nf_log_all_netns)
		वापस;

	m = nf_log_buf_खोलो();

	अगर (!loginfo)
		loginfo = &शेष_loginfo;

	nf_log_dump_packet_common(m, pf, hooknum, skb, in,
				  out, loginfo, prefix);

	अगर (in)
		dump_ipv4_mac_header(m, loginfo, skb);

	dump_ipv4_packet(net, m, loginfo, skb, 0);

	nf_log_buf_बंद(m);
पूर्ण

अटल काष्ठा nf_logger nf_ip_logger __पढ़ो_mostly = अणु
	.name		= "nf_log_ipv4",
	.type		= NF_LOG_TYPE_LOG,
	.logfn		= nf_log_ip_packet,
	.me		= THIS_MODULE,
पूर्ण;

अटल व्योम dump_ipv6_mac_header(काष्ठा nf_log_buf *m,
				 स्थिर काष्ठा nf_loginfo *info,
				 स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;
	अचिन्हित पूर्णांक logflags = 0;

	अगर (info->type == NF_LOG_TYPE_LOG)
		logflags = info->u.log.logflags;

	अगर (!(logflags & NF_LOG_MACDECODE))
		जाओ fallback;

	चयन (dev->type) अणु
	हाल ARPHRD_ETHER:
		nf_log_buf_add(m, "MACSRC=%pM MACDST=%pM ",
			       eth_hdr(skb)->h_source, eth_hdr(skb)->h_dest);
		nf_log_dump_vlan(m, skb);
		nf_log_buf_add(m, "MACPROTO=%04x ",
			       ntohs(eth_hdr(skb)->h_proto));
		वापस;
	शेष:
		अवरोध;
	पूर्ण

fallback:
	nf_log_buf_add(m, "MAC=");
	अगर (dev->hard_header_len &&
	    skb->mac_header != skb->network_header) अणु
		स्थिर अचिन्हित अक्षर *p = skb_mac_header(skb);
		अचिन्हित पूर्णांक len = dev->hard_header_len;
		अचिन्हित पूर्णांक i;

		अगर (dev->type == ARPHRD_SIT) अणु
			p -= ETH_HLEN;

			अगर (p < skb->head)
				p = शून्य;
		पूर्ण

		अगर (p) अणु
			nf_log_buf_add(m, "%02x", *p++);
			क्रम (i = 1; i < len; i++)
				nf_log_buf_add(m, ":%02x", *p++);
		पूर्ण
		nf_log_buf_add(m, " ");

		अगर (dev->type == ARPHRD_SIT) अणु
			स्थिर काष्ठा iphdr *iph =
				(काष्ठा iphdr *)skb_mac_header(skb);
			nf_log_buf_add(m, "TUNNEL=%pI4->%pI4 ", &iph->saddr,
				       &iph->daddr);
		पूर्ण
	पूर्ण अन्यथा अणु
		nf_log_buf_add(m, " ");
	पूर्ण
पूर्ण

अटल व्योम nf_log_ip6_packet(काष्ठा net *net, u_पूर्णांक8_t pf,
			      अचिन्हित पूर्णांक hooknum, स्थिर काष्ठा sk_buff *skb,
			      स्थिर काष्ठा net_device *in,
			      स्थिर काष्ठा net_device *out,
			      स्थिर काष्ठा nf_loginfo *loginfo,
			      स्थिर अक्षर *prefix)
अणु
	काष्ठा nf_log_buf *m;

	/* FIXME: Disabled from containers until syslog ns is supported */
	अगर (!net_eq(net, &init_net) && !sysctl_nf_log_all_netns)
		वापस;

	m = nf_log_buf_खोलो();

	अगर (!loginfo)
		loginfo = &शेष_loginfo;

	nf_log_dump_packet_common(m, pf, hooknum, skb, in, out,
				  loginfo, prefix);

	अगर (in)
		dump_ipv6_mac_header(m, loginfo, skb);

	dump_ipv6_packet(net, m, loginfo, skb, skb_network_offset(skb), 1);

	nf_log_buf_बंद(m);
पूर्ण

अटल काष्ठा nf_logger nf_ip6_logger __पढ़ो_mostly = अणु
	.name		= "nf_log_ipv6",
	.type		= NF_LOG_TYPE_LOG,
	.logfn		= nf_log_ip6_packet,
	.me		= THIS_MODULE,
पूर्ण;

अटल व्योम nf_log_netdev_packet(काष्ठा net *net, u_पूर्णांक8_t pf,
				 अचिन्हित पूर्णांक hooknum,
				 स्थिर काष्ठा sk_buff *skb,
				 स्थिर काष्ठा net_device *in,
				 स्थिर काष्ठा net_device *out,
				 स्थिर काष्ठा nf_loginfo *loginfo,
				 स्थिर अक्षर *prefix)
अणु
	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		nf_log_ip_packet(net, pf, hooknum, skb, in, out, loginfo, prefix);
		अवरोध;
	हाल htons(ETH_P_IPV6):
		nf_log_ip6_packet(net, pf, hooknum, skb, in, out, loginfo, prefix);
		अवरोध;
	हाल htons(ETH_P_ARP):
	हाल htons(ETH_P_RARP):
		nf_log_arp_packet(net, pf, hooknum, skb, in, out, loginfo, prefix);
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा nf_logger nf_netdev_logger __पढ़ो_mostly = अणु
	.name		= "nf_log_netdev",
	.type		= NF_LOG_TYPE_LOG,
	.logfn		= nf_log_netdev_packet,
	.me		= THIS_MODULE,
पूर्ण;

अटल काष्ठा nf_logger nf_bridge_logger __पढ़ो_mostly = अणु
	.name		= "nf_log_bridge",
	.type		= NF_LOG_TYPE_LOG,
	.logfn		= nf_log_netdev_packet,
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __net_init nf_log_syslog_net_init(काष्ठा net *net)
अणु
	पूर्णांक ret = nf_log_set(net, NFPROTO_IPV4, &nf_ip_logger);

	अगर (ret)
		वापस ret;

	ret = nf_log_set(net, NFPROTO_ARP, &nf_arp_logger);
	अगर (ret)
		जाओ err1;

	ret = nf_log_set(net, NFPROTO_IPV6, &nf_ip6_logger);
	अगर (ret)
		जाओ err2;

	ret = nf_log_set(net, NFPROTO_NETDEV, &nf_netdev_logger);
	अगर (ret)
		जाओ err3;

	ret = nf_log_set(net, NFPROTO_BRIDGE, &nf_bridge_logger);
	अगर (ret)
		जाओ err4;
	वापस 0;
err4:
	nf_log_unset(net, &nf_netdev_logger);
err3:
	nf_log_unset(net, &nf_ip6_logger);
err2:
	nf_log_unset(net, &nf_arp_logger);
err1:
	nf_log_unset(net, &nf_ip_logger);
	वापस ret;
पूर्ण

अटल व्योम __net_निकास nf_log_syslog_net_निकास(काष्ठा net *net)
अणु
	nf_log_unset(net, &nf_ip_logger);
	nf_log_unset(net, &nf_arp_logger);
	nf_log_unset(net, &nf_ip6_logger);
	nf_log_unset(net, &nf_netdev_logger);
	nf_log_unset(net, &nf_bridge_logger);
पूर्ण

अटल काष्ठा pernet_operations nf_log_syslog_net_ops = अणु
	.init = nf_log_syslog_net_init,
	.निकास = nf_log_syslog_net_निकास,
पूर्ण;

अटल पूर्णांक __init nf_log_syslog_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_pernet_subsys(&nf_log_syslog_net_ops);
	अगर (ret < 0)
		वापस ret;

	ret = nf_log_रेजिस्टर(NFPROTO_IPV4, &nf_ip_logger);
	अगर (ret < 0)
		जाओ err1;

	ret = nf_log_रेजिस्टर(NFPROTO_ARP, &nf_arp_logger);
	अगर (ret < 0)
		जाओ err2;

	ret = nf_log_रेजिस्टर(NFPROTO_IPV6, &nf_ip6_logger);
	अगर (ret < 0)
		जाओ err3;

	ret = nf_log_रेजिस्टर(NFPROTO_NETDEV, &nf_netdev_logger);
	अगर (ret < 0)
		जाओ err4;

	ret = nf_log_रेजिस्टर(NFPROTO_BRIDGE, &nf_bridge_logger);
	अगर (ret < 0)
		जाओ err5;

	वापस 0;
err5:
	nf_log_unरेजिस्टर(&nf_netdev_logger);
err4:
	nf_log_unरेजिस्टर(&nf_ip6_logger);
err3:
	nf_log_unरेजिस्टर(&nf_arp_logger);
err2:
	nf_log_unरेजिस्टर(&nf_ip_logger);
err1:
	pr_err("failed to register logger\n");
	unरेजिस्टर_pernet_subsys(&nf_log_syslog_net_ops);
	वापस ret;
पूर्ण

अटल व्योम __निकास nf_log_syslog_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&nf_log_syslog_net_ops);
	nf_log_unरेजिस्टर(&nf_ip_logger);
	nf_log_unरेजिस्टर(&nf_arp_logger);
	nf_log_unरेजिस्टर(&nf_ip6_logger);
	nf_log_unरेजिस्टर(&nf_netdev_logger);
	nf_log_unरेजिस्टर(&nf_bridge_logger);
पूर्ण

module_init(nf_log_syslog_init);
module_निकास(nf_log_syslog_निकास);

MODULE_AUTHOR("Netfilter Core Team <coreteam@netfilter.org>");
MODULE_DESCRIPTION("Netfilter syslog packet logging");
MODULE_LICENSE("GPL");
MODULE_ALIAS("nf_log_arp");
MODULE_ALIAS("nf_log_bridge");
MODULE_ALIAS("nf_log_ipv4");
MODULE_ALIAS("nf_log_ipv6");
MODULE_ALIAS("nf_log_netdev");
MODULE_ALIAS_NF_LOGGER(AF_BRIDGE, 0);
MODULE_ALIAS_NF_LOGGER(AF_INET, 0);
MODULE_ALIAS_NF_LOGGER(3, 0);
MODULE_ALIAS_NF_LOGGER(5, 0); /* NFPROTO_NETDEV */
MODULE_ALIAS_NF_LOGGER(AF_INET6, 0);
