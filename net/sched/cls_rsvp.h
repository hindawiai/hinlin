<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * net/sched/cls_rsvp.h	Template file क्रम RSVPv[46] classअगरiers.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 */

/*
   Comparing to general packet classअगरication problem,
   RSVP needs only sevaral relatively simple rules:

   * (dst, protocol) are always specअगरied,
     so that we are able to hash them.
   * src may be exact, or may be wildcard, so that
     we can keep a hash table plus one wildcard entry.
   * source port (or flow label) is important only अगर src is given.

   IMPLEMENTATION.

   We use a two level hash table: The top level is keyed by
   destination address and protocol ID, every bucket contains a list
   of "rsvp sessions", identअगरied by destination address, protocol and
   DPI(="Destination Port ID"): triple (key, mask, offset).

   Every bucket has a smaller hash table keyed by source address
   (cf. RSVP flowspec) and one wildcard entry क्रम wildcard reservations.
   Every bucket is again a list of "RSVP flows", selected by
   source address and SPI(="Source Port ID" here rather than
   "security parameter index"): triple (key, mask, offset).


   NOTE 1. All the packets with IPv6 extension headers (but AH and ESP)
   and all fragmented packets go to the best-efक्रमt traffic class.


   NOTE 2. Two "port id"'s seems to be redundant, rfc2207 requires
   only one "Generalized Port Identifier". So that क्रम classic
   ah, esp (and udp,tcp) both *pi should coincide or one of them
   should be wildcard.

   At first sight, this redundancy is just a waste of CPU
   resources. But DPI and SPI add the possibility to assign dअगरferent
   priorities to GPIs. Look also at note 4 about tunnels below.


   NOTE 3. One complication is the हाल of tunneled packets.
   We implement it as following: अगर the first lookup
   matches a special session with "tunnelhdr" value not zero,
   flowid करोesn't contain the true flow ID, but the tunnel ID (1...255).
   In this हाल, we pull tunnelhdr bytes and restart lookup
   with tunnel ID added to the list of keys. Simple and stupid 8)8)
   It's enough क्रम PIMREG and IPIP.


   NOTE 4. Two GPIs make it possible to parse even GRE packets.
   F.e. DPI can select ETH_P_IP (and necessary flags to make
   tunnelhdr correct) in GRE protocol field and SPI matches
   GRE key. Is it not nice? 8)8)


   Well, as result, despite its simplicity, we get a pretty
   घातerful classअगरication engine.  */


काष्ठा rsvp_head अणु
	u32			पंचांगap[256/32];
	u32			hgenerator;
	u8			tgenerator;
	काष्ठा rsvp_session __rcu *ht[256];
	काष्ठा rcu_head		rcu;
पूर्ण;

काष्ठा rsvp_session अणु
	काष्ठा rsvp_session __rcu	*next;
	__be32				dst[RSVP_DST_LEN];
	काष्ठा tc_rsvp_gpi		dpi;
	u8				protocol;
	u8				tunnelid;
	/* 16 (src,sport) hash slots, and one wildcard source slot */
	काष्ठा rsvp_filter __rcu	*ht[16 + 1];
	काष्ठा rcu_head			rcu;
पूर्ण;


काष्ठा rsvp_filter अणु
	काष्ठा rsvp_filter __rcu	*next;
	__be32				src[RSVP_DST_LEN];
	काष्ठा tc_rsvp_gpi		spi;
	u8				tunnelhdr;

	काष्ठा tcf_result		res;
	काष्ठा tcf_exts			exts;

	u32				handle;
	काष्ठा rsvp_session		*sess;
	काष्ठा rcu_work			rwork;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक hash_dst(__be32 *dst, u8 protocol, u8 tunnelid)
अणु
	अचिन्हित पूर्णांक h = (__क्रमce __u32)dst[RSVP_DST_LEN - 1];

	h ^= h>>16;
	h ^= h>>8;
	वापस (h ^ protocol ^ tunnelid) & 0xFF;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक hash_src(__be32 *src)
अणु
	अचिन्हित पूर्णांक h = (__क्रमce __u32)src[RSVP_DST_LEN-1];

	h ^= h>>16;
	h ^= h>>8;
	h ^= h>>4;
	वापस h & 0xF;
पूर्ण

#घोषणा RSVP_APPLY_RESULT()				\
अणु							\
	पूर्णांक r = tcf_exts_exec(skb, &f->exts, res);	\
	अगर (r < 0)					\
		जारी;				\
	अन्यथा अगर (r > 0)					\
		वापस r;				\
पूर्ण

अटल पूर्णांक rsvp_classअगरy(काष्ठा sk_buff *skb, स्थिर काष्ठा tcf_proto *tp,
			 काष्ठा tcf_result *res)
अणु
	काष्ठा rsvp_head *head = rcu_dereference_bh(tp->root);
	काष्ठा rsvp_session *s;
	काष्ठा rsvp_filter *f;
	अचिन्हित पूर्णांक h1, h2;
	__be32 *dst, *src;
	u8 protocol;
	u8 tunnelid = 0;
	u8 *xprt;
#अगर RSVP_DST_LEN == 4
	काष्ठा ipv6hdr *nhptr;

	अगर (!pskb_network_may_pull(skb, माप(*nhptr)))
		वापस -1;
	nhptr = ipv6_hdr(skb);
#अन्यथा
	काष्ठा iphdr *nhptr;

	अगर (!pskb_network_may_pull(skb, माप(*nhptr)))
		वापस -1;
	nhptr = ip_hdr(skb);
#पूर्ण_अगर
restart:

#अगर RSVP_DST_LEN == 4
	src = &nhptr->saddr.s6_addr32[0];
	dst = &nhptr->daddr.s6_addr32[0];
	protocol = nhptr->nexthdr;
	xprt = ((u8 *)nhptr) + माप(काष्ठा ipv6hdr);
#अन्यथा
	src = &nhptr->saddr;
	dst = &nhptr->daddr;
	protocol = nhptr->protocol;
	xprt = ((u8 *)nhptr) + (nhptr->ihl<<2);
	अगर (ip_is_fragment(nhptr))
		वापस -1;
#पूर्ण_अगर

	h1 = hash_dst(dst, protocol, tunnelid);
	h2 = hash_src(src);

	क्रम (s = rcu_dereference_bh(head->ht[h1]); s;
	     s = rcu_dereference_bh(s->next)) अणु
		अगर (dst[RSVP_DST_LEN-1] == s->dst[RSVP_DST_LEN - 1] &&
		    protocol == s->protocol &&
		    !(s->dpi.mask &
		      (*(u32 *)(xprt + s->dpi.offset) ^ s->dpi.key)) &&
#अगर RSVP_DST_LEN == 4
		    dst[0] == s->dst[0] &&
		    dst[1] == s->dst[1] &&
		    dst[2] == s->dst[2] &&
#पूर्ण_अगर
		    tunnelid == s->tunnelid) अणु

			क्रम (f = rcu_dereference_bh(s->ht[h2]); f;
			     f = rcu_dereference_bh(f->next)) अणु
				अगर (src[RSVP_DST_LEN-1] == f->src[RSVP_DST_LEN - 1] &&
				    !(f->spi.mask & (*(u32 *)(xprt + f->spi.offset) ^ f->spi.key))
#अगर RSVP_DST_LEN == 4
				    &&
				    src[0] == f->src[0] &&
				    src[1] == f->src[1] &&
				    src[2] == f->src[2]
#पूर्ण_अगर
				    ) अणु
					*res = f->res;
					RSVP_APPLY_RESULT();

matched:
					अगर (f->tunnelhdr == 0)
						वापस 0;

					tunnelid = f->res.classid;
					nhptr = (व्योम *)(xprt + f->tunnelhdr - माप(*nhptr));
					जाओ restart;
				पूर्ण
			पूर्ण

			/* And wildcard bucket... */
			क्रम (f = rcu_dereference_bh(s->ht[16]); f;
			     f = rcu_dereference_bh(f->next)) अणु
				*res = f->res;
				RSVP_APPLY_RESULT();
				जाओ matched;
			पूर्ण
			वापस -1;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम rsvp_replace(काष्ठा tcf_proto *tp, काष्ठा rsvp_filter *n, u32 h)
अणु
	काष्ठा rsvp_head *head = rtnl_dereference(tp->root);
	काष्ठा rsvp_session *s;
	काष्ठा rsvp_filter __rcu **ins;
	काष्ठा rsvp_filter *pins;
	अचिन्हित पूर्णांक h1 = h & 0xFF;
	अचिन्हित पूर्णांक h2 = (h >> 8) & 0xFF;

	क्रम (s = rtnl_dereference(head->ht[h1]); s;
	     s = rtnl_dereference(s->next)) अणु
		क्रम (ins = &s->ht[h2], pins = rtnl_dereference(*ins); ;
		     ins = &pins->next, pins = rtnl_dereference(*ins)) अणु
			अगर (pins->handle == h) अणु
				RCU_INIT_POINTER(n->next, pins->next);
				rcu_assign_poपूर्णांकer(*ins, n);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Something went wrong अगर we are trying to replace a non-existent
	 * node. Mind as well halt instead of silently failing.
	 */
	BUG_ON(1);
पूर्ण

अटल व्योम *rsvp_get(काष्ठा tcf_proto *tp, u32 handle)
अणु
	काष्ठा rsvp_head *head = rtnl_dereference(tp->root);
	काष्ठा rsvp_session *s;
	काष्ठा rsvp_filter *f;
	अचिन्हित पूर्णांक h1 = handle & 0xFF;
	अचिन्हित पूर्णांक h2 = (handle >> 8) & 0xFF;

	अगर (h2 > 16)
		वापस शून्य;

	क्रम (s = rtnl_dereference(head->ht[h1]); s;
	     s = rtnl_dereference(s->next)) अणु
		क्रम (f = rtnl_dereference(s->ht[h2]); f;
		     f = rtnl_dereference(f->next)) अणु
			अगर (f->handle == handle)
				वापस f;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक rsvp_init(काष्ठा tcf_proto *tp)
अणु
	काष्ठा rsvp_head *data;

	data = kzalloc(माप(काष्ठा rsvp_head), GFP_KERNEL);
	अगर (data) अणु
		rcu_assign_poपूर्णांकer(tp->root, data);
		वापस 0;
	पूर्ण
	वापस -ENOBUFS;
पूर्ण

अटल व्योम __rsvp_delete_filter(काष्ठा rsvp_filter *f)
अणु
	tcf_exts_destroy(&f->exts);
	tcf_exts_put_net(&f->exts);
	kमुक्त(f);
पूर्ण

अटल व्योम rsvp_delete_filter_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rsvp_filter *f = container_of(to_rcu_work(work),
					     काष्ठा rsvp_filter,
					     rwork);
	rtnl_lock();
	__rsvp_delete_filter(f);
	rtnl_unlock();
पूर्ण

अटल व्योम rsvp_delete_filter(काष्ठा tcf_proto *tp, काष्ठा rsvp_filter *f)
अणु
	tcf_unbind_filter(tp, &f->res);
	/* all classअगरiers are required to call tcf_exts_destroy() after rcu
	 * grace period, since converted-to-rcu actions are relying on that
	 * in cleanup() callback
	 */
	अगर (tcf_exts_get_net(&f->exts))
		tcf_queue_work(&f->rwork, rsvp_delete_filter_work);
	अन्यथा
		__rsvp_delete_filter(f);
पूर्ण

अटल व्योम rsvp_destroy(काष्ठा tcf_proto *tp, bool rtnl_held,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rsvp_head *data = rtnl_dereference(tp->root);
	पूर्णांक h1, h2;

	अगर (data == शून्य)
		वापस;

	क्रम (h1 = 0; h1 < 256; h1++) अणु
		काष्ठा rsvp_session *s;

		जबतक ((s = rtnl_dereference(data->ht[h1])) != शून्य) अणु
			RCU_INIT_POINTER(data->ht[h1], s->next);

			क्रम (h2 = 0; h2 <= 16; h2++) अणु
				काष्ठा rsvp_filter *f;

				जबतक ((f = rtnl_dereference(s->ht[h2])) != शून्य) अणु
					rcu_assign_poपूर्णांकer(s->ht[h2], f->next);
					rsvp_delete_filter(tp, f);
				पूर्ण
			पूर्ण
			kमुक्त_rcu(s, rcu);
		पूर्ण
	पूर्ण
	kमुक्त_rcu(data, rcu);
पूर्ण

अटल पूर्णांक rsvp_delete(काष्ठा tcf_proto *tp, व्योम *arg, bool *last,
		       bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rsvp_head *head = rtnl_dereference(tp->root);
	काष्ठा rsvp_filter *nfp, *f = arg;
	काष्ठा rsvp_filter __rcu **fp;
	अचिन्हित पूर्णांक h = f->handle;
	काष्ठा rsvp_session __rcu **sp;
	काष्ठा rsvp_session *nsp, *s = f->sess;
	पूर्णांक i, h1;

	fp = &s->ht[(h >> 8) & 0xFF];
	क्रम (nfp = rtnl_dereference(*fp); nfp;
	     fp = &nfp->next, nfp = rtnl_dereference(*fp)) अणु
		अगर (nfp == f) अणु
			RCU_INIT_POINTER(*fp, f->next);
			rsvp_delete_filter(tp, f);

			/* Strip tree */

			क्रम (i = 0; i <= 16; i++)
				अगर (s->ht[i])
					जाओ out;

			/* OK, session has no flows */
			sp = &head->ht[h & 0xFF];
			क्रम (nsp = rtnl_dereference(*sp); nsp;
			     sp = &nsp->next, nsp = rtnl_dereference(*sp)) अणु
				अगर (nsp == s) अणु
					RCU_INIT_POINTER(*sp, s->next);
					kमुक्त_rcu(s, rcu);
					जाओ out;
				पूर्ण
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण

out:
	*last = true;
	क्रम (h1 = 0; h1 < 256; h1++) अणु
		अगर (rcu_access_poपूर्णांकer(head->ht[h1])) अणु
			*last = false;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक gen_handle(काष्ठा tcf_proto *tp, अचिन्हित salt)
अणु
	काष्ठा rsvp_head *data = rtnl_dereference(tp->root);
	पूर्णांक i = 0xFFFF;

	जबतक (i-- > 0) अणु
		u32 h;

		अगर ((data->hgenerator += 0x10000) == 0)
			data->hgenerator = 0x10000;
		h = data->hgenerator|salt;
		अगर (!rsvp_get(tp, h))
			वापस h;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tunnel_bts(काष्ठा rsvp_head *data)
अणु
	पूर्णांक n = data->tgenerator >> 5;
	u32 b = 1 << (data->tgenerator & 0x1F);

	अगर (data->पंचांगap[n] & b)
		वापस 0;
	data->पंचांगap[n] |= b;
	वापस 1;
पूर्ण

अटल व्योम tunnel_recycle(काष्ठा rsvp_head *data)
अणु
	काष्ठा rsvp_session __rcu **sht = data->ht;
	u32 पंचांगap[256/32];
	पूर्णांक h1, h2;

	स_रखो(पंचांगap, 0, माप(पंचांगap));

	क्रम (h1 = 0; h1 < 256; h1++) अणु
		काष्ठा rsvp_session *s;
		क्रम (s = rtnl_dereference(sht[h1]); s;
		     s = rtnl_dereference(s->next)) अणु
			क्रम (h2 = 0; h2 <= 16; h2++) अणु
				काष्ठा rsvp_filter *f;

				क्रम (f = rtnl_dereference(s->ht[h2]); f;
				     f = rtnl_dereference(f->next)) अणु
					अगर (f->tunnelhdr == 0)
						जारी;
					data->tgenerator = f->res.classid;
					tunnel_bts(data);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	स_नकल(data->पंचांगap, पंचांगap, माप(पंचांगap));
पूर्ण

अटल u32 gen_tunnel(काष्ठा rsvp_head *data)
अणु
	पूर्णांक i, k;

	क्रम (k = 0; k < 2; k++) अणु
		क्रम (i = 255; i > 0; i--) अणु
			अगर (++data->tgenerator == 0)
				data->tgenerator = 1;
			अगर (tunnel_bts(data))
				वापस data->tgenerator;
		पूर्ण
		tunnel_recycle(data);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy rsvp_policy[TCA_RSVP_MAX + 1] = अणु
	[TCA_RSVP_CLASSID]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_RSVP_DST]		= अणु .len = RSVP_DST_LEN * माप(u32) पूर्ण,
	[TCA_RSVP_SRC]		= अणु .len = RSVP_DST_LEN * माप(u32) पूर्ण,
	[TCA_RSVP_PINFO]	= अणु .len = माप(काष्ठा tc_rsvp_pinfo) पूर्ण,
पूर्ण;

अटल पूर्णांक rsvp_change(काष्ठा net *net, काष्ठा sk_buff *in_skb,
		       काष्ठा tcf_proto *tp, अचिन्हित दीर्घ base,
		       u32 handle,
		       काष्ठा nlattr **tca,
		       व्योम **arg, bool ovr, bool rtnl_held,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rsvp_head *data = rtnl_dereference(tp->root);
	काष्ठा rsvp_filter *f, *nfp;
	काष्ठा rsvp_filter __rcu **fp;
	काष्ठा rsvp_session *nsp, *s;
	काष्ठा rsvp_session __rcu **sp;
	काष्ठा tc_rsvp_pinfo *pinfo = शून्य;
	काष्ठा nlattr *opt = tca[TCA_OPTIONS];
	काष्ठा nlattr *tb[TCA_RSVP_MAX + 1];
	काष्ठा tcf_exts e;
	अचिन्हित पूर्णांक h1, h2;
	__be32 *dst;
	पूर्णांक err;

	अगर (opt == शून्य)
		वापस handle ? -EINVAL : 0;

	err = nla_parse_nested_deprecated(tb, TCA_RSVP_MAX, opt, rsvp_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	err = tcf_exts_init(&e, net, TCA_RSVP_ACT, TCA_RSVP_POLICE);
	अगर (err < 0)
		वापस err;
	err = tcf_exts_validate(net, tp, tb, tca[TCA_RATE], &e, ovr, true,
				extack);
	अगर (err < 0)
		जाओ errout2;

	f = *arg;
	अगर (f) अणु
		/* Node exists: adjust only classid */
		काष्ठा rsvp_filter *n;

		अगर (f->handle != handle && handle)
			जाओ errout2;

		n = kmemdup(f, माप(*f), GFP_KERNEL);
		अगर (!n) अणु
			err = -ENOMEM;
			जाओ errout2;
		पूर्ण

		err = tcf_exts_init(&n->exts, net, TCA_RSVP_ACT,
				    TCA_RSVP_POLICE);
		अगर (err < 0) अणु
			kमुक्त(n);
			जाओ errout2;
		पूर्ण

		अगर (tb[TCA_RSVP_CLASSID]) अणु
			n->res.classid = nla_get_u32(tb[TCA_RSVP_CLASSID]);
			tcf_bind_filter(tp, &n->res, base);
		पूर्ण

		tcf_exts_change(&n->exts, &e);
		rsvp_replace(tp, n, handle);
		वापस 0;
	पूर्ण

	/* Now more serious part... */
	err = -EINVAL;
	अगर (handle)
		जाओ errout2;
	अगर (tb[TCA_RSVP_DST] == शून्य)
		जाओ errout2;

	err = -ENOBUFS;
	f = kzalloc(माप(काष्ठा rsvp_filter), GFP_KERNEL);
	अगर (f == शून्य)
		जाओ errout2;

	err = tcf_exts_init(&f->exts, net, TCA_RSVP_ACT, TCA_RSVP_POLICE);
	अगर (err < 0)
		जाओ errout;
	h2 = 16;
	अगर (tb[TCA_RSVP_SRC]) अणु
		स_नकल(f->src, nla_data(tb[TCA_RSVP_SRC]), माप(f->src));
		h2 = hash_src(f->src);
	पूर्ण
	अगर (tb[TCA_RSVP_PINFO]) अणु
		pinfo = nla_data(tb[TCA_RSVP_PINFO]);
		f->spi = pinfo->spi;
		f->tunnelhdr = pinfo->tunnelhdr;
	पूर्ण
	अगर (tb[TCA_RSVP_CLASSID])
		f->res.classid = nla_get_u32(tb[TCA_RSVP_CLASSID]);

	dst = nla_data(tb[TCA_RSVP_DST]);
	h1 = hash_dst(dst, pinfo ? pinfo->protocol : 0, pinfo ? pinfo->tunnelid : 0);

	err = -ENOMEM;
	अगर ((f->handle = gen_handle(tp, h1 | (h2<<8))) == 0)
		जाओ errout;

	अगर (f->tunnelhdr) अणु
		err = -EINVAL;
		अगर (f->res.classid > 255)
			जाओ errout;

		err = -ENOMEM;
		अगर (f->res.classid == 0 &&
		    (f->res.classid = gen_tunnel(data)) == 0)
			जाओ errout;
	पूर्ण

	क्रम (sp = &data->ht[h1];
	     (s = rtnl_dereference(*sp)) != शून्य;
	     sp = &s->next) अणु
		अगर (dst[RSVP_DST_LEN-1] == s->dst[RSVP_DST_LEN-1] &&
		    pinfo && pinfo->protocol == s->protocol &&
		    स_भेद(&pinfo->dpi, &s->dpi, माप(s->dpi)) == 0 &&
#अगर RSVP_DST_LEN == 4
		    dst[0] == s->dst[0] &&
		    dst[1] == s->dst[1] &&
		    dst[2] == s->dst[2] &&
#पूर्ण_अगर
		    pinfo->tunnelid == s->tunnelid) अणु

insert:
			/* OK, we found appropriate session */

			fp = &s->ht[h2];

			f->sess = s;
			अगर (f->tunnelhdr == 0)
				tcf_bind_filter(tp, &f->res, base);

			tcf_exts_change(&f->exts, &e);

			fp = &s->ht[h2];
			क्रम (nfp = rtnl_dereference(*fp); nfp;
			     fp = &nfp->next, nfp = rtnl_dereference(*fp)) अणु
				__u32 mask = nfp->spi.mask & f->spi.mask;

				अगर (mask != f->spi.mask)
					अवरोध;
			पूर्ण
			RCU_INIT_POINTER(f->next, nfp);
			rcu_assign_poपूर्णांकer(*fp, f);

			*arg = f;
			वापस 0;
		पूर्ण
	पूर्ण

	/* No session found. Create new one. */

	err = -ENOBUFS;
	s = kzalloc(माप(काष्ठा rsvp_session), GFP_KERNEL);
	अगर (s == शून्य)
		जाओ errout;
	स_नकल(s->dst, dst, माप(s->dst));

	अगर (pinfo) अणु
		s->dpi = pinfo->dpi;
		s->protocol = pinfo->protocol;
		s->tunnelid = pinfo->tunnelid;
	पूर्ण
	sp = &data->ht[h1];
	क्रम (nsp = rtnl_dereference(*sp); nsp;
	     sp = &nsp->next, nsp = rtnl_dereference(*sp)) अणु
		अगर ((nsp->dpi.mask & s->dpi.mask) != s->dpi.mask)
			अवरोध;
	पूर्ण
	RCU_INIT_POINTER(s->next, nsp);
	rcu_assign_poपूर्णांकer(*sp, s);

	जाओ insert;

errout:
	tcf_exts_destroy(&f->exts);
	kमुक्त(f);
errout2:
	tcf_exts_destroy(&e);
	वापस err;
पूर्ण

अटल व्योम rsvp_walk(काष्ठा tcf_proto *tp, काष्ठा tcf_walker *arg,
		      bool rtnl_held)
अणु
	काष्ठा rsvp_head *head = rtnl_dereference(tp->root);
	अचिन्हित पूर्णांक h, h1;

	अगर (arg->stop)
		वापस;

	क्रम (h = 0; h < 256; h++) अणु
		काष्ठा rsvp_session *s;

		क्रम (s = rtnl_dereference(head->ht[h]); s;
		     s = rtnl_dereference(s->next)) अणु
			क्रम (h1 = 0; h1 <= 16; h1++) अणु
				काष्ठा rsvp_filter *f;

				क्रम (f = rtnl_dereference(s->ht[h1]); f;
				     f = rtnl_dereference(f->next)) अणु
					अगर (arg->count < arg->skip) अणु
						arg->count++;
						जारी;
					पूर्ण
					अगर (arg->fn(tp, f, arg) < 0) अणु
						arg->stop = 1;
						वापस;
					पूर्ण
					arg->count++;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक rsvp_dump(काष्ठा net *net, काष्ठा tcf_proto *tp, व्योम *fh,
		     काष्ठा sk_buff *skb, काष्ठा tcmsg *t, bool rtnl_held)
अणु
	काष्ठा rsvp_filter *f = fh;
	काष्ठा rsvp_session *s;
	काष्ठा nlattr *nest;
	काष्ठा tc_rsvp_pinfo pinfo;

	अगर (f == शून्य)
		वापस skb->len;
	s = f->sess;

	t->tcm_handle = f->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	अगर (nla_put(skb, TCA_RSVP_DST, माप(s->dst), &s->dst))
		जाओ nla_put_failure;
	pinfo.dpi = s->dpi;
	pinfo.spi = f->spi;
	pinfo.protocol = s->protocol;
	pinfo.tunnelid = s->tunnelid;
	pinfo.tunnelhdr = f->tunnelhdr;
	pinfo.pad = 0;
	अगर (nla_put(skb, TCA_RSVP_PINFO, माप(pinfo), &pinfo))
		जाओ nla_put_failure;
	अगर (f->res.classid &&
	    nla_put_u32(skb, TCA_RSVP_CLASSID, f->res.classid))
		जाओ nla_put_failure;
	अगर (((f->handle >> 8) & 0xFF) != 16 &&
	    nla_put(skb, TCA_RSVP_SRC, माप(f->src), f->src))
		जाओ nla_put_failure;

	अगर (tcf_exts_dump(skb, &f->exts) < 0)
		जाओ nla_put_failure;

	nla_nest_end(skb, nest);

	अगर (tcf_exts_dump_stats(skb, &f->exts) < 0)
		जाओ nla_put_failure;
	वापस skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल व्योम rsvp_bind_class(व्योम *fh, u32 classid, अचिन्हित दीर्घ cl, व्योम *q,
			    अचिन्हित दीर्घ base)
अणु
	काष्ठा rsvp_filter *f = fh;

	अगर (f && f->res.classid == classid) अणु
		अगर (cl)
			__tcf_bind_filter(q, &f->res, base);
		अन्यथा
			__tcf_unbind_filter(q, &f->res);
	पूर्ण
पूर्ण

अटल काष्ठा tcf_proto_ops RSVP_OPS __पढ़ो_mostly = अणु
	.kind		=	RSVP_ID,
	.classअगरy	=	rsvp_classअगरy,
	.init		=	rsvp_init,
	.destroy	=	rsvp_destroy,
	.get		=	rsvp_get,
	.change		=	rsvp_change,
	.delete		=	rsvp_delete,
	.walk		=	rsvp_walk,
	.dump		=	rsvp_dump,
	.bind_class	=	rsvp_bind_class,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init init_rsvp(व्योम)
अणु
	वापस रेजिस्टर_tcf_proto_ops(&RSVP_OPS);
पूर्ण

अटल व्योम __निकास निकास_rsvp(व्योम)
अणु
	unरेजिस्टर_tcf_proto_ops(&RSVP_OPS);
पूर्ण

module_init(init_rsvp)
module_निकास(निकास_rsvp)
