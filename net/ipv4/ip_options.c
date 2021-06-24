<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		The options processing module क्रम ip.c
 *
 * Authors:	A.N.Kuznetsov
 *
 */

#घोषणा pr_fmt(fmt) "IPv4: " fmt

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ip.h>
#समावेश <linux/icmp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/sock.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/route.h>
#समावेश <net/cipso_ipv4.h>
#समावेश <net/ip_fib.h>

/*
 * Write options to IP header, record destination address to
 * source route option, address of outgoing पूर्णांकerface
 * (we should alपढ़ोy know it, so that this  function is allowed be
 * called only after routing decision) and बारtamp,
 * अगर we originate this datagram.
 *
 * daddr is real destination address, next hop is recorded in IP header.
 * saddr is address of outgoing पूर्णांकerface.
 */

व्योम ip_options_build(काष्ठा sk_buff *skb, काष्ठा ip_options *opt,
		      __be32 daddr, काष्ठा rtable *rt, पूर्णांक is_frag)
अणु
	अचिन्हित अक्षर *iph = skb_network_header(skb);

	स_नकल(&(IPCB(skb)->opt), opt, माप(काष्ठा ip_options));
	स_नकल(iph + माप(काष्ठा iphdr), opt->__data, opt->optlen);
	opt = &(IPCB(skb)->opt);

	अगर (opt->srr)
		स_नकल(iph + opt->srr + iph[opt->srr + 1] - 4, &daddr, 4);

	अगर (!is_frag) अणु
		अगर (opt->rr_needaddr)
			ip_rt_get_source(iph + opt->rr + iph[opt->rr + 2] - 5, skb, rt);
		अगर (opt->ts_needaddr)
			ip_rt_get_source(iph + opt->ts + iph[opt->ts + 2] - 9, skb, rt);
		अगर (opt->ts_needसमय) अणु
			__be32 midसमय;

			midसमय = inet_current_बारtamp();
			स_नकल(iph + opt->ts + iph[opt->ts + 2] - 5, &midसमय, 4);
		पूर्ण
		वापस;
	पूर्ण
	अगर (opt->rr) अणु
		स_रखो(iph + opt->rr, IPOPT_NOP, iph[opt->rr + 1]);
		opt->rr = 0;
		opt->rr_needaddr = 0;
	पूर्ण
	अगर (opt->ts) अणु
		स_रखो(iph + opt->ts, IPOPT_NOP, iph[opt->ts + 1]);
		opt->ts = 0;
		opt->ts_needaddr = opt->ts_needसमय = 0;
	पूर्ण
पूर्ण

/*
 * Provided (sopt, skb) poपूर्णांकs to received options,
 * build in करोpt compiled option set appropriate क्रम answering.
 * i.e. invert SRR option, copy anothers,
 * and grab room in RR/TS options.
 *
 * NOTE: करोpt cannot poपूर्णांक to skb.
 */

पूर्णांक __ip_options_echo(काष्ठा net *net, काष्ठा ip_options *करोpt,
		      काष्ठा sk_buff *skb, स्थिर काष्ठा ip_options *sopt)
अणु
	अचिन्हित अक्षर *sptr, *dptr;
	पूर्णांक soffset, करोffset;
	पूर्णांक	optlen;

	स_रखो(करोpt, 0, माप(काष्ठा ip_options));

	अगर (sopt->optlen == 0)
		वापस 0;

	sptr = skb_network_header(skb);
	dptr = करोpt->__data;

	अगर (sopt->rr) अणु
		optlen  = sptr[sopt->rr+1];
		soffset = sptr[sopt->rr+2];
		करोpt->rr = करोpt->optlen + माप(काष्ठा iphdr);
		स_नकल(dptr, sptr+sopt->rr, optlen);
		अगर (sopt->rr_needaddr && soffset <= optlen) अणु
			अगर (soffset + 3 > optlen)
				वापस -EINVAL;
			dptr[2] = soffset + 4;
			करोpt->rr_needaddr = 1;
		पूर्ण
		dptr += optlen;
		करोpt->optlen += optlen;
	पूर्ण
	अगर (sopt->ts) अणु
		optlen = sptr[sopt->ts+1];
		soffset = sptr[sopt->ts+2];
		करोpt->ts = करोpt->optlen + माप(काष्ठा iphdr);
		स_नकल(dptr, sptr+sopt->ts, optlen);
		अगर (soffset <= optlen) अणु
			अगर (sopt->ts_needaddr) अणु
				अगर (soffset + 3 > optlen)
					वापस -EINVAL;
				करोpt->ts_needaddr = 1;
				soffset += 4;
			पूर्ण
			अगर (sopt->ts_needसमय) अणु
				अगर (soffset + 3 > optlen)
					वापस -EINVAL;
				अगर ((dptr[3]&0xF) != IPOPT_TS_PRESPEC) अणु
					करोpt->ts_needसमय = 1;
					soffset += 4;
				पूर्ण अन्यथा अणु
					करोpt->ts_needसमय = 0;

					अगर (soffset + 7 <= optlen) अणु
						__be32 addr;

						स_नकल(&addr, dptr+soffset-1, 4);
						अगर (inet_addr_type(net, addr) != RTN_UNICAST) अणु
							करोpt->ts_needसमय = 1;
							soffset += 8;
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
			dptr[2] = soffset;
		पूर्ण
		dptr += optlen;
		करोpt->optlen += optlen;
	पूर्ण
	अगर (sopt->srr) अणु
		अचिन्हित अक्षर *start = sptr+sopt->srr;
		__be32 faddr;

		optlen  = start[1];
		soffset = start[2];
		करोffset = 0;
		अगर (soffset > optlen)
			soffset = optlen + 1;
		soffset -= 4;
		अगर (soffset > 3) अणु
			स_नकल(&faddr, &start[soffset-1], 4);
			क्रम (soffset -= 4, करोffset = 4; soffset > 3; soffset -= 4, करोffset += 4)
				स_नकल(&dptr[करोffset-1], &start[soffset-1], 4);
			/*
			 * RFC1812 requires to fix illegal source routes.
			 */
			अगर (स_भेद(&ip_hdr(skb)->saddr,
				   &start[soffset + 3], 4) == 0)
				करोffset -= 4;
		पूर्ण
		अगर (करोffset > 3) अणु
			करोpt->faddr = faddr;
			dptr[0] = start[0];
			dptr[1] = करोffset+3;
			dptr[2] = 4;
			dptr += करोffset+3;
			करोpt->srr = करोpt->optlen + माप(काष्ठा iphdr);
			करोpt->optlen += करोffset+3;
			करोpt->is_strictroute = sopt->is_strictroute;
		पूर्ण
	पूर्ण
	अगर (sopt->cipso) अणु
		optlen  = sptr[sopt->cipso+1];
		करोpt->cipso = करोpt->optlen+माप(काष्ठा iphdr);
		स_नकल(dptr, sptr+sopt->cipso, optlen);
		dptr += optlen;
		करोpt->optlen += optlen;
	पूर्ण
	जबतक (करोpt->optlen & 3) अणु
		*dptr++ = IPOPT_END;
		करोpt->optlen++;
	पूर्ण
	वापस 0;
पूर्ण

/*
 *	Options "fragmenting", just fill options not
 *	allowed in fragments with NOOPs.
 *	Simple and stupid 8), but the most efficient way.
 */

व्योम ip_options_fragment(काष्ठा sk_buff *skb)
अणु
	अचिन्हित अक्षर *optptr = skb_network_header(skb) + माप(काष्ठा iphdr);
	काष्ठा ip_options *opt = &(IPCB(skb)->opt);
	पूर्णांक  l = opt->optlen;
	पूर्णांक  optlen;

	जबतक (l > 0) अणु
		चयन (*optptr) अणु
		हाल IPOPT_END:
			वापस;
		हाल IPOPT_NOOP:
			l--;
			optptr++;
			जारी;
		पूर्ण
		optlen = optptr[1];
		अगर (optlen < 2 || optlen > l)
		  वापस;
		अगर (!IPOPT_COPIED(*optptr))
			स_रखो(optptr, IPOPT_NOOP, optlen);
		l -= optlen;
		optptr += optlen;
	पूर्ण
	opt->ts = 0;
	opt->rr = 0;
	opt->rr_needaddr = 0;
	opt->ts_needaddr = 0;
	opt->ts_needसमय = 0;
पूर्ण

/* helper used by ip_options_compile() to call fib_compute_spec_dst()
 * at most one समय.
 */
अटल व्योम spec_dst_fill(__be32 *spec_dst, काष्ठा sk_buff *skb)
अणु
	अगर (*spec_dst == htonl(INADDR_ANY))
		*spec_dst = fib_compute_spec_dst(skb);
पूर्ण

/*
 * Verअगरy options and fill poपूर्णांकers in काष्ठा options.
 * Caller should clear *opt, and set opt->data.
 * If opt == शून्य, then skb->data should poपूर्णांक to IP header.
 */

पूर्णांक __ip_options_compile(काष्ठा net *net,
			 काष्ठा ip_options *opt, काष्ठा sk_buff *skb,
			 __be32 *info)
अणु
	__be32 spec_dst = htonl(INADDR_ANY);
	अचिन्हित अक्षर *pp_ptr = शून्य;
	काष्ठा rtable *rt = शून्य;
	अचिन्हित अक्षर *optptr;
	अचिन्हित अक्षर *iph;
	पूर्णांक optlen, l;

	अगर (skb) अणु
		rt = skb_rtable(skb);
		optptr = (अचिन्हित अक्षर *)&(ip_hdr(skb)[1]);
	पूर्ण अन्यथा
		optptr = opt->__data;
	iph = optptr - माप(काष्ठा iphdr);

	क्रम (l = opt->optlen; l > 0; ) अणु
		चयन (*optptr) अणु
		हाल IPOPT_END:
			क्रम (optptr++, l--; l > 0; optptr++, l--) अणु
				अगर (*optptr != IPOPT_END) अणु
					*optptr = IPOPT_END;
					opt->is_changed = 1;
				पूर्ण
			पूर्ण
			जाओ eol;
		हाल IPOPT_NOOP:
			l--;
			optptr++;
			जारी;
		पूर्ण
		अगर (unlikely(l < 2)) अणु
			pp_ptr = optptr;
			जाओ error;
		पूर्ण
		optlen = optptr[1];
		अगर (optlen < 2 || optlen > l) अणु
			pp_ptr = optptr;
			जाओ error;
		पूर्ण
		चयन (*optptr) अणु
		हाल IPOPT_SSRR:
		हाल IPOPT_LSRR:
			अगर (optlen < 3) अणु
				pp_ptr = optptr + 1;
				जाओ error;
			पूर्ण
			अगर (optptr[2] < 4) अणु
				pp_ptr = optptr + 2;
				जाओ error;
			पूर्ण
			/* NB: cf RFC-1812 5.2.4.1 */
			अगर (opt->srr) अणु
				pp_ptr = optptr;
				जाओ error;
			पूर्ण
			अगर (!skb) अणु
				अगर (optptr[2] != 4 || optlen < 7 || ((optlen-3) & 3)) अणु
					pp_ptr = optptr + 1;
					जाओ error;
				पूर्ण
				स_नकल(&opt->faddr, &optptr[3], 4);
				अगर (optlen > 7)
					स_हटाओ(&optptr[3], &optptr[7], optlen-7);
			पूर्ण
			opt->is_strictroute = (optptr[0] == IPOPT_SSRR);
			opt->srr = optptr - iph;
			अवरोध;
		हाल IPOPT_RR:
			अगर (opt->rr) अणु
				pp_ptr = optptr;
				जाओ error;
			पूर्ण
			अगर (optlen < 3) अणु
				pp_ptr = optptr + 1;
				जाओ error;
			पूर्ण
			अगर (optptr[2] < 4) अणु
				pp_ptr = optptr + 2;
				जाओ error;
			पूर्ण
			अगर (optptr[2] <= optlen) अणु
				अगर (optptr[2]+3 > optlen) अणु
					pp_ptr = optptr + 2;
					जाओ error;
				पूर्ण
				अगर (rt) अणु
					spec_dst_fill(&spec_dst, skb);
					स_नकल(&optptr[optptr[2]-1], &spec_dst, 4);
					opt->is_changed = 1;
				पूर्ण
				optptr[2] += 4;
				opt->rr_needaddr = 1;
			पूर्ण
			opt->rr = optptr - iph;
			अवरोध;
		हाल IPOPT_TIMESTAMP:
			अगर (opt->ts) अणु
				pp_ptr = optptr;
				जाओ error;
			पूर्ण
			अगर (optlen < 4) अणु
				pp_ptr = optptr + 1;
				जाओ error;
			पूर्ण
			अगर (optptr[2] < 5) अणु
				pp_ptr = optptr + 2;
				जाओ error;
			पूर्ण
			अगर (optptr[2] <= optlen) अणु
				अचिन्हित अक्षर *समयptr = शून्य;
				अगर (optptr[2]+3 > optlen) अणु
					pp_ptr = optptr + 2;
					जाओ error;
				पूर्ण
				चयन (optptr[3]&0xF) अणु
				हाल IPOPT_TS_TSONLY:
					अगर (skb)
						समयptr = &optptr[optptr[2]-1];
					opt->ts_needसमय = 1;
					optptr[2] += 4;
					अवरोध;
				हाल IPOPT_TS_TSANDADDR:
					अगर (optptr[2]+7 > optlen) अणु
						pp_ptr = optptr + 2;
						जाओ error;
					पूर्ण
					अगर (rt)  अणु
						spec_dst_fill(&spec_dst, skb);
						स_नकल(&optptr[optptr[2]-1], &spec_dst, 4);
						समयptr = &optptr[optptr[2]+3];
					पूर्ण
					opt->ts_needaddr = 1;
					opt->ts_needसमय = 1;
					optptr[2] += 8;
					अवरोध;
				हाल IPOPT_TS_PRESPEC:
					अगर (optptr[2]+7 > optlen) अणु
						pp_ptr = optptr + 2;
						जाओ error;
					पूर्ण
					अणु
						__be32 addr;
						स_नकल(&addr, &optptr[optptr[2]-1], 4);
						अगर (inet_addr_type(net, addr) == RTN_UNICAST)
							अवरोध;
						अगर (skb)
							समयptr = &optptr[optptr[2]+3];
					पूर्ण
					opt->ts_needसमय = 1;
					optptr[2] += 8;
					अवरोध;
				शेष:
					अगर (!skb && !ns_capable(net->user_ns, CAP_NET_RAW)) अणु
						pp_ptr = optptr + 3;
						जाओ error;
					पूर्ण
					अवरोध;
				पूर्ण
				अगर (समयptr) अणु
					__be32 midसमय;

					midसमय = inet_current_बारtamp();
					स_नकल(समयptr, &midसमय, 4);
					opt->is_changed = 1;
				पूर्ण
			पूर्ण अन्यथा अगर ((optptr[3]&0xF) != IPOPT_TS_PRESPEC) अणु
				अचिन्हित पूर्णांक overflow = optptr[3]>>4;
				अगर (overflow == 15) अणु
					pp_ptr = optptr + 3;
					जाओ error;
				पूर्ण
				अगर (skb) अणु
					optptr[3] = (optptr[3]&0xF)|((overflow+1)<<4);
					opt->is_changed = 1;
				पूर्ण
			पूर्ण
			opt->ts = optptr - iph;
			अवरोध;
		हाल IPOPT_RA:
			अगर (optlen < 4) अणु
				pp_ptr = optptr + 1;
				जाओ error;
			पूर्ण
			अगर (optptr[2] == 0 && optptr[3] == 0)
				opt->router_alert = optptr - iph;
			अवरोध;
		हाल IPOPT_CIPSO:
			अगर ((!skb && !ns_capable(net->user_ns, CAP_NET_RAW)) || opt->cipso) अणु
				pp_ptr = optptr;
				जाओ error;
			पूर्ण
			opt->cipso = optptr - iph;
			अगर (cipso_v4_validate(skb, &optptr)) अणु
				pp_ptr = optptr;
				जाओ error;
			पूर्ण
			अवरोध;
		हाल IPOPT_SEC:
		हाल IPOPT_SID:
		शेष:
			अगर (!skb && !ns_capable(net->user_ns, CAP_NET_RAW)) अणु
				pp_ptr = optptr;
				जाओ error;
			पूर्ण
			अवरोध;
		पूर्ण
		l -= optlen;
		optptr += optlen;
	पूर्ण

eol:
	अगर (!pp_ptr)
		वापस 0;

error:
	अगर (info)
		*info = htonl((pp_ptr-iph)<<24);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(__ip_options_compile);

पूर्णांक ip_options_compile(काष्ठा net *net,
		       काष्ठा ip_options *opt, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;
	__be32 info;

	ret = __ip_options_compile(net, opt, skb, &info);
	अगर (ret != 0 && skb)
		icmp_send(skb, ICMP_PARAMETERPROB, 0, info);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ip_options_compile);

/*
 *	Unकरो all the changes करोne by ip_options_compile().
 */

व्योम ip_options_unकरो(काष्ठा ip_options *opt)
अणु
	अगर (opt->srr) अणु
		अचिन्हित अक्षर *optptr = opt->__data + opt->srr - माप(काष्ठा iphdr);

		स_हटाओ(optptr + 7, optptr + 3, optptr[1] - 7);
		स_नकल(optptr + 3, &opt->faddr, 4);
	पूर्ण
	अगर (opt->rr_needaddr) अणु
		अचिन्हित अक्षर *optptr = opt->__data + opt->rr - माप(काष्ठा iphdr);

		optptr[2] -= 4;
		स_रखो(&optptr[optptr[2] - 1], 0, 4);
	पूर्ण
	अगर (opt->ts) अणु
		अचिन्हित अक्षर *optptr = opt->__data + opt->ts - माप(काष्ठा iphdr);

		अगर (opt->ts_needसमय) अणु
			optptr[2] -= 4;
			स_रखो(&optptr[optptr[2] - 1], 0, 4);
			अगर ((optptr[3] & 0xF) == IPOPT_TS_PRESPEC)
				optptr[2] -= 4;
		पूर्ण
		अगर (opt->ts_needaddr) अणु
			optptr[2] -= 4;
			स_रखो(&optptr[optptr[2] - 1], 0, 4);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक ip_options_get(काष्ठा net *net, काष्ठा ip_options_rcu **optp,
		   sockptr_t data, पूर्णांक optlen)
अणु
	काष्ठा ip_options_rcu *opt;

	opt = kzalloc(माप(काष्ठा ip_options_rcu) + ((optlen + 3) & ~3),
		       GFP_KERNEL);
	अगर (!opt)
		वापस -ENOMEM;
	अगर (optlen && copy_from_sockptr(opt->opt.__data, data, optlen)) अणु
		kमुक्त(opt);
		वापस -EFAULT;
	पूर्ण

	जबतक (optlen & 3)
		opt->opt.__data[optlen++] = IPOPT_END;
	opt->opt.optlen = optlen;
	अगर (optlen && ip_options_compile(net, &opt->opt, शून्य)) अणु
		kमुक्त(opt);
		वापस -EINVAL;
	पूर्ण
	kमुक्त(*optp);
	*optp = opt;
	वापस 0;
पूर्ण

व्योम ip_क्रमward_options(काष्ठा sk_buff *skb)
अणु
	काष्ठा   ip_options *opt	= &(IPCB(skb)->opt);
	अचिन्हित अक्षर *optptr;
	काष्ठा rtable *rt = skb_rtable(skb);
	अचिन्हित अक्षर *raw = skb_network_header(skb);

	अगर (opt->rr_needaddr) अणु
		optptr = (अचिन्हित अक्षर *)raw + opt->rr;
		ip_rt_get_source(&optptr[optptr[2]-5], skb, rt);
		opt->is_changed = 1;
	पूर्ण
	अगर (opt->srr_is_hit) अणु
		पूर्णांक srrptr, srrspace;

		optptr = raw + opt->srr;

		क्रम ( srrptr = optptr[2], srrspace = optptr[1];
		     srrptr <= srrspace;
		     srrptr += 4
		     ) अणु
			अगर (srrptr + 3 > srrspace)
				अवरोध;
			अगर (स_भेद(&opt->nexthop, &optptr[srrptr-1], 4) == 0)
				अवरोध;
		पूर्ण
		अगर (srrptr + 3 <= srrspace) अणु
			opt->is_changed = 1;
			ip_hdr(skb)->daddr = opt->nexthop;
			ip_rt_get_source(&optptr[srrptr-1], skb, rt);
			optptr[2] = srrptr+4;
		पूर्ण अन्यथा अणु
			net_crit_ratelimited("%s(): Argh! Destination lost!\n",
					     __func__);
		पूर्ण
		अगर (opt->ts_needaddr) अणु
			optptr = raw + opt->ts;
			ip_rt_get_source(&optptr[optptr[2]-9], skb, rt);
			opt->is_changed = 1;
		पूर्ण
	पूर्ण
	अगर (opt->is_changed) अणु
		opt->is_changed = 0;
		ip_send_check(ip_hdr(skb));
	पूर्ण
पूर्ण

पूर्णांक ip_options_rcv_srr(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ip_options *opt = &(IPCB(skb)->opt);
	पूर्णांक srrspace, srrptr;
	__be32 nexthop;
	काष्ठा iphdr *iph = ip_hdr(skb);
	अचिन्हित अक्षर *optptr = skb_network_header(skb) + opt->srr;
	काष्ठा rtable *rt = skb_rtable(skb);
	काष्ठा rtable *rt2;
	अचिन्हित दीर्घ orefdst;
	पूर्णांक err;

	अगर (!rt)
		वापस 0;

	अगर (skb->pkt_type != PACKET_HOST)
		वापस -EINVAL;
	अगर (rt->rt_type == RTN_UNICAST) अणु
		अगर (!opt->is_strictroute)
			वापस 0;
		icmp_send(skb, ICMP_PARAMETERPROB, 0, htonl(16<<24));
		वापस -EINVAL;
	पूर्ण
	अगर (rt->rt_type != RTN_LOCAL)
		वापस -EINVAL;

	क्रम (srrptr = optptr[2], srrspace = optptr[1]; srrptr <= srrspace; srrptr += 4) अणु
		अगर (srrptr + 3 > srrspace) अणु
			icmp_send(skb, ICMP_PARAMETERPROB, 0, htonl((opt->srr+2)<<24));
			वापस -EINVAL;
		पूर्ण
		स_नकल(&nexthop, &optptr[srrptr-1], 4);

		orefdst = skb->_skb_refdst;
		skb_dst_set(skb, शून्य);
		err = ip_route_input(skb, nexthop, iph->saddr, iph->tos, dev);
		rt2 = skb_rtable(skb);
		अगर (err || (rt2->rt_type != RTN_UNICAST && rt2->rt_type != RTN_LOCAL)) अणु
			skb_dst_drop(skb);
			skb->_skb_refdst = orefdst;
			वापस -EINVAL;
		पूर्ण
		refdst_drop(orefdst);
		अगर (rt2->rt_type != RTN_LOCAL)
			अवरोध;
		/* Superfast 8) loopback क्रमward */
		iph->daddr = nexthop;
		opt->is_changed = 1;
	पूर्ण
	अगर (srrptr <= srrspace) अणु
		opt->srr_is_hit = 1;
		opt->nexthop = nexthop;
		opt->is_changed = 1;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ip_options_rcv_srr);
