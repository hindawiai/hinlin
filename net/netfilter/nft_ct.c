<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008-2009 Patrick McHardy <kaber@trash.net>
 * Copyright (c) 2016 Pablo Neira Ayuso <pablo@netfilter.org>
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_acct.h>
#समावेश <net/netfilter/nf_conntrack_tuple.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_labels.h>
#समावेश <net/netfilter/nf_conntrack_समयout.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>

काष्ठा nft_ct अणु
	क्रमागत nft_ct_keys	key:8;
	क्रमागत ip_conntrack_dir	dir:8;
	जोड़ अणु
		u8		dreg;
		u8		sreg;
	पूर्ण;
पूर्ण;

काष्ठा nft_ct_helper_obj  अणु
	काष्ठा nf_conntrack_helper *helper4;
	काष्ठा nf_conntrack_helper *helper6;
	u8 l4proto;
पूर्ण;

#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
अटल DEFINE_PER_CPU(काष्ठा nf_conn *, nft_ct_pcpu_ढाँचा);
अटल अचिन्हित पूर्णांक nft_ct_pcpu_ढाँचा_refcnt __पढ़ो_mostly;
#पूर्ण_अगर

अटल u64 nft_ct_get_eval_counter(स्थिर काष्ठा nf_conn_counter *c,
				   क्रमागत nft_ct_keys k,
				   क्रमागत ip_conntrack_dir d)
अणु
	अगर (d < IP_CT_सूची_MAX)
		वापस k == NFT_CT_BYTES ? atomic64_पढ़ो(&c[d].bytes) :
					   atomic64_पढ़ो(&c[d].packets);

	वापस nft_ct_get_eval_counter(c, k, IP_CT_सूची_ORIGINAL) +
	       nft_ct_get_eval_counter(c, k, IP_CT_सूची_REPLY);
पूर्ण

अटल व्योम nft_ct_get_eval(स्थिर काष्ठा nft_expr *expr,
			    काष्ठा nft_regs *regs,
			    स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_ct *priv = nft_expr_priv(expr);
	u32 *dest = &regs->data[priv->dreg];
	क्रमागत ip_conntrack_info ctinfo;
	स्थिर काष्ठा nf_conn *ct;
	स्थिर काष्ठा nf_conn_help *help;
	स्थिर काष्ठा nf_conntrack_tuple *tuple;
	स्थिर काष्ठा nf_conntrack_helper *helper;
	अचिन्हित पूर्णांक state;

	ct = nf_ct_get(pkt->skb, &ctinfo);

	चयन (priv->key) अणु
	हाल NFT_CT_STATE:
		अगर (ct)
			state = NF_CT_STATE_BIT(ctinfo);
		अन्यथा अगर (ctinfo == IP_CT_UNTRACKED)
			state = NF_CT_STATE_UNTRACKED_BIT;
		अन्यथा
			state = NF_CT_STATE_INVALID_BIT;
		*dest = state;
		वापस;
	शेष:
		अवरोध;
	पूर्ण

	अगर (ct == शून्य)
		जाओ err;

	चयन (priv->key) अणु
	हाल NFT_CT_सूचीECTION:
		nft_reg_store8(dest, CTINFO2सूची(ctinfo));
		वापस;
	हाल NFT_CT_STATUS:
		*dest = ct->status;
		वापस;
#अगर_घोषित CONFIG_NF_CONNTRACK_MARK
	हाल NFT_CT_MARK:
		*dest = ct->mark;
		वापस;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_SECMARK
	हाल NFT_CT_SECMARK:
		*dest = ct->secmark;
		वापस;
#पूर्ण_अगर
	हाल NFT_CT_EXPIRATION:
		*dest = jअगरfies_to_msecs(nf_ct_expires(ct));
		वापस;
	हाल NFT_CT_HELPER:
		अगर (ct->master == शून्य)
			जाओ err;
		help = nfct_help(ct->master);
		अगर (help == शून्य)
			जाओ err;
		helper = rcu_dereference(help->helper);
		अगर (helper == शून्य)
			जाओ err;
		म_नकलन((अक्षर *)dest, helper->name, NF_CT_HELPER_NAME_LEN);
		वापस;
#अगर_घोषित CONFIG_NF_CONNTRACK_LABELS
	हाल NFT_CT_LABELS: अणु
		काष्ठा nf_conn_labels *labels = nf_ct_labels_find(ct);

		अगर (labels)
			स_नकल(dest, labels->bits, NF_CT_LABELS_MAX_SIZE);
		अन्यथा
			स_रखो(dest, 0, NF_CT_LABELS_MAX_SIZE);
		वापस;
	पूर्ण
#पूर्ण_अगर
	हाल NFT_CT_BYTES:
	हाल NFT_CT_PKTS: अणु
		स्थिर काष्ठा nf_conn_acct *acct = nf_conn_acct_find(ct);
		u64 count = 0;

		अगर (acct)
			count = nft_ct_get_eval_counter(acct->counter,
							priv->key, priv->dir);
		स_नकल(dest, &count, माप(count));
		वापस;
	पूर्ण
	हाल NFT_CT_AVGPKT: अणु
		स्थिर काष्ठा nf_conn_acct *acct = nf_conn_acct_find(ct);
		u64 avgcnt = 0, bcnt = 0, pcnt = 0;

		अगर (acct) अणु
			pcnt = nft_ct_get_eval_counter(acct->counter,
						       NFT_CT_PKTS, priv->dir);
			bcnt = nft_ct_get_eval_counter(acct->counter,
						       NFT_CT_BYTES, priv->dir);
			अगर (pcnt != 0)
				avgcnt = भाग64_u64(bcnt, pcnt);
		पूर्ण

		स_नकल(dest, &avgcnt, माप(avgcnt));
		वापस;
	पूर्ण
	हाल NFT_CT_L3PROTOCOL:
		nft_reg_store8(dest, nf_ct_l3num(ct));
		वापस;
	हाल NFT_CT_PROTOCOL:
		nft_reg_store8(dest, nf_ct_protonum(ct));
		वापस;
#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
	हाल NFT_CT_ZONE: अणु
		स्थिर काष्ठा nf_conntrack_zone *zone = nf_ct_zone(ct);
		u16 zoneid;

		अगर (priv->dir < IP_CT_सूची_MAX)
			zoneid = nf_ct_zone_id(zone, priv->dir);
		अन्यथा
			zoneid = zone->id;

		nft_reg_store16(dest, zoneid);
		वापस;
	पूर्ण
#पूर्ण_अगर
	हाल NFT_CT_ID:
		*dest = nf_ct_get_id(ct);
		वापस;
	शेष:
		अवरोध;
	पूर्ण

	tuple = &ct->tuplehash[priv->dir].tuple;
	चयन (priv->key) अणु
	हाल NFT_CT_SRC:
		स_नकल(dest, tuple->src.u3.all,
		       nf_ct_l3num(ct) == NFPROTO_IPV4 ? 4 : 16);
		वापस;
	हाल NFT_CT_DST:
		स_नकल(dest, tuple->dst.u3.all,
		       nf_ct_l3num(ct) == NFPROTO_IPV4 ? 4 : 16);
		वापस;
	हाल NFT_CT_PROTO_SRC:
		nft_reg_store16(dest, (__क्रमce u16)tuple->src.u.all);
		वापस;
	हाल NFT_CT_PROTO_DST:
		nft_reg_store16(dest, (__क्रमce u16)tuple->dst.u.all);
		वापस;
	हाल NFT_CT_SRC_IP:
		अगर (nf_ct_l3num(ct) != NFPROTO_IPV4)
			जाओ err;
		*dest = tuple->src.u3.ip;
		वापस;
	हाल NFT_CT_DST_IP:
		अगर (nf_ct_l3num(ct) != NFPROTO_IPV4)
			जाओ err;
		*dest = tuple->dst.u3.ip;
		वापस;
	हाल NFT_CT_SRC_IP6:
		अगर (nf_ct_l3num(ct) != NFPROTO_IPV6)
			जाओ err;
		स_नकल(dest, tuple->src.u3.ip6, माप(काष्ठा in6_addr));
		वापस;
	हाल NFT_CT_DST_IP6:
		अगर (nf_ct_l3num(ct) != NFPROTO_IPV6)
			जाओ err;
		स_नकल(dest, tuple->dst.u3.ip6, माप(काष्ठा in6_addr));
		वापस;
	शेष:
		अवरोध;
	पूर्ण
	वापस;
err:
	regs->verdict.code = NFT_BREAK;
पूर्ण

#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
अटल व्योम nft_ct_set_zone_eval(स्थिर काष्ठा nft_expr *expr,
				 काष्ठा nft_regs *regs,
				 स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nf_conntrack_zone zone = अणु .dir = NF_CT_DEFAULT_ZONE_सूची पूर्ण;
	स्थिर काष्ठा nft_ct *priv = nft_expr_priv(expr);
	काष्ठा sk_buff *skb = pkt->skb;
	क्रमागत ip_conntrack_info ctinfo;
	u16 value = nft_reg_load16(&regs->data[priv->sreg]);
	काष्ठा nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct) /* alपढ़ोy tracked */
		वापस;

	zone.id = value;

	चयन (priv->dir) अणु
	हाल IP_CT_सूची_ORIGINAL:
		zone.dir = NF_CT_ZONE_सूची_ORIG;
		अवरोध;
	हाल IP_CT_सूची_REPLY:
		zone.dir = NF_CT_ZONE_सूची_REPL;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ct = this_cpu_पढ़ो(nft_ct_pcpu_ढाँचा);

	अगर (likely(atomic_पढ़ो(&ct->ct_general.use) == 1)) अणु
		nf_ct_zone_add(ct, &zone);
	पूर्ण अन्यथा अणु
		/* previous skb got queued to userspace */
		ct = nf_ct_पंचांगpl_alloc(nft_net(pkt), &zone, GFP_ATOMIC);
		अगर (!ct) अणु
			regs->verdict.code = NF_DROP;
			वापस;
		पूर्ण
	पूर्ण

	atomic_inc(&ct->ct_general.use);
	nf_ct_set(skb, ct, IP_CT_NEW);
पूर्ण
#पूर्ण_अगर

अटल व्योम nft_ct_set_eval(स्थिर काष्ठा nft_expr *expr,
			    काष्ठा nft_regs *regs,
			    स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_ct *priv = nft_expr_priv(expr);
	काष्ठा sk_buff *skb = pkt->skb;
#अगर defined(CONFIG_NF_CONNTRACK_MARK) || defined(CONFIG_NF_CONNTRACK_SECMARK)
	u32 value = regs->data[priv->sreg];
#पूर्ण_अगर
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct == शून्य || nf_ct_is_ढाँचा(ct))
		वापस;

	चयन (priv->key) अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_MARK
	हाल NFT_CT_MARK:
		अगर (ct->mark != value) अणु
			ct->mark = value;
			nf_conntrack_event_cache(IPCT_MARK, ct);
		पूर्ण
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_SECMARK
	हाल NFT_CT_SECMARK:
		अगर (ct->secmark != value) अणु
			ct->secmark = value;
			nf_conntrack_event_cache(IPCT_SECMARK, ct);
		पूर्ण
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_LABELS
	हाल NFT_CT_LABELS:
		nf_connlabels_replace(ct,
				      &regs->data[priv->sreg],
				      &regs->data[priv->sreg],
				      NF_CT_LABELS_MAX_SIZE / माप(u32));
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
	हाल NFT_CT_EVENTMASK: अणु
		काष्ठा nf_conntrack_ecache *e = nf_ct_ecache_find(ct);
		u32 cपंचांगask = regs->data[priv->sreg];

		अगर (e) अणु
			अगर (e->cपंचांगask != cपंचांगask)
				e->cपंचांगask = cपंचांगask;
			अवरोध;
		पूर्ण

		अगर (cपंचांगask && !nf_ct_is_confirmed(ct))
			nf_ct_ecache_ext_add(ct, cपंचांगask, 0, GFP_ATOMIC);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_ct_policy[NFTA_CT_MAX + 1] = अणु
	[NFTA_CT_DREG]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_CT_KEY]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_CT_सूचीECTION]	= अणु .type = NLA_U8 पूर्ण,
	[NFTA_CT_SREG]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
अटल व्योम nft_ct_पंचांगpl_put_pcpu(व्योम)
अणु
	काष्ठा nf_conn *ct;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		ct = per_cpu(nft_ct_pcpu_ढाँचा, cpu);
		अगर (!ct)
			अवरोध;
		nf_ct_put(ct);
		per_cpu(nft_ct_pcpu_ढाँचा, cpu) = शून्य;
	पूर्ण
पूर्ण

अटल bool nft_ct_पंचांगpl_alloc_pcpu(व्योम)
अणु
	काष्ठा nf_conntrack_zone zone = अणु .id = 0 पूर्ण;
	काष्ठा nf_conn *पंचांगp;
	पूर्णांक cpu;

	अगर (nft_ct_pcpu_ढाँचा_refcnt)
		वापस true;

	क्रम_each_possible_cpu(cpu) अणु
		पंचांगp = nf_ct_पंचांगpl_alloc(&init_net, &zone, GFP_KERNEL);
		अगर (!पंचांगp) अणु
			nft_ct_पंचांगpl_put_pcpu();
			वापस false;
		पूर्ण

		atomic_set(&पंचांगp->ct_general.use, 1);
		per_cpu(nft_ct_pcpu_ढाँचा, cpu) = पंचांगp;
	पूर्ण

	वापस true;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक nft_ct_get_init(स्थिर काष्ठा nft_ctx *ctx,
			   स्थिर काष्ठा nft_expr *expr,
			   स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_ct *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक len;
	पूर्णांक err;

	priv->key = ntohl(nla_get_be32(tb[NFTA_CT_KEY]));
	priv->dir = IP_CT_सूची_MAX;
	चयन (priv->key) अणु
	हाल NFT_CT_सूचीECTION:
		अगर (tb[NFTA_CT_सूचीECTION] != शून्य)
			वापस -EINVAL;
		len = माप(u8);
		अवरोध;
	हाल NFT_CT_STATE:
	हाल NFT_CT_STATUS:
#अगर_घोषित CONFIG_NF_CONNTRACK_MARK
	हाल NFT_CT_MARK:
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_SECMARK
	हाल NFT_CT_SECMARK:
#पूर्ण_अगर
	हाल NFT_CT_EXPIRATION:
		अगर (tb[NFTA_CT_सूचीECTION] != शून्य)
			वापस -EINVAL;
		len = माप(u32);
		अवरोध;
#अगर_घोषित CONFIG_NF_CONNTRACK_LABELS
	हाल NFT_CT_LABELS:
		अगर (tb[NFTA_CT_सूचीECTION] != शून्य)
			वापस -EINVAL;
		len = NF_CT_LABELS_MAX_SIZE;
		अवरोध;
#पूर्ण_अगर
	हाल NFT_CT_HELPER:
		अगर (tb[NFTA_CT_सूचीECTION] != शून्य)
			वापस -EINVAL;
		len = NF_CT_HELPER_NAME_LEN;
		अवरोध;

	हाल NFT_CT_L3PROTOCOL:
	हाल NFT_CT_PROTOCOL:
		/* For compatibility, करो not report error अगर NFTA_CT_सूचीECTION
		 * attribute is specअगरied.
		 */
		len = माप(u8);
		अवरोध;
	हाल NFT_CT_SRC:
	हाल NFT_CT_DST:
		अगर (tb[NFTA_CT_सूचीECTION] == शून्य)
			वापस -EINVAL;

		चयन (ctx->family) अणु
		हाल NFPROTO_IPV4:
			len = माप_field(काष्ठा nf_conntrack_tuple,
					   src.u3.ip);
			अवरोध;
		हाल NFPROTO_IPV6:
		हाल NFPROTO_INET:
			len = माप_field(काष्ठा nf_conntrack_tuple,
					   src.u3.ip6);
			अवरोध;
		शेष:
			वापस -EAFNOSUPPORT;
		पूर्ण
		अवरोध;
	हाल NFT_CT_SRC_IP:
	हाल NFT_CT_DST_IP:
		अगर (tb[NFTA_CT_सूचीECTION] == शून्य)
			वापस -EINVAL;

		len = माप_field(काष्ठा nf_conntrack_tuple, src.u3.ip);
		अवरोध;
	हाल NFT_CT_SRC_IP6:
	हाल NFT_CT_DST_IP6:
		अगर (tb[NFTA_CT_सूचीECTION] == शून्य)
			वापस -EINVAL;

		len = माप_field(काष्ठा nf_conntrack_tuple, src.u3.ip6);
		अवरोध;
	हाल NFT_CT_PROTO_SRC:
	हाल NFT_CT_PROTO_DST:
		अगर (tb[NFTA_CT_सूचीECTION] == शून्य)
			वापस -EINVAL;
		len = माप_field(काष्ठा nf_conntrack_tuple, src.u.all);
		अवरोध;
	हाल NFT_CT_BYTES:
	हाल NFT_CT_PKTS:
	हाल NFT_CT_AVGPKT:
		len = माप(u64);
		अवरोध;
#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
	हाल NFT_CT_ZONE:
		len = माप(u16);
		अवरोध;
#पूर्ण_अगर
	हाल NFT_CT_ID:
		len = माप(u32);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (tb[NFTA_CT_सूचीECTION] != शून्य) अणु
		priv->dir = nla_get_u8(tb[NFTA_CT_सूचीECTION]);
		चयन (priv->dir) अणु
		हाल IP_CT_सूची_ORIGINAL:
		हाल IP_CT_सूची_REPLY:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	err = nft_parse_रेजिस्टर_store(ctx, tb[NFTA_CT_DREG], &priv->dreg, शून्य,
				       NFT_DATA_VALUE, len);
	अगर (err < 0)
		वापस err;

	err = nf_ct_netns_get(ctx->net, ctx->family);
	अगर (err < 0)
		वापस err;

	अगर (priv->key == NFT_CT_BYTES ||
	    priv->key == NFT_CT_PKTS  ||
	    priv->key == NFT_CT_AVGPKT)
		nf_ct_set_acct(ctx->net, true);

	वापस 0;
पूर्ण

अटल व्योम __nft_ct_set_destroy(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_ct *priv)
अणु
	चयन (priv->key) अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_LABELS
	हाल NFT_CT_LABELS:
		nf_connlabels_put(ctx->net);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
	हाल NFT_CT_ZONE:
		अगर (--nft_ct_pcpu_ढाँचा_refcnt == 0)
			nft_ct_पंचांगpl_put_pcpu();
		अवरोध;
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक nft_ct_set_init(स्थिर काष्ठा nft_ctx *ctx,
			   स्थिर काष्ठा nft_expr *expr,
			   स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_ct *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक len;
	पूर्णांक err;

	priv->dir = IP_CT_सूची_MAX;
	priv->key = ntohl(nla_get_be32(tb[NFTA_CT_KEY]));
	चयन (priv->key) अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_MARK
	हाल NFT_CT_MARK:
		अगर (tb[NFTA_CT_सूचीECTION])
			वापस -EINVAL;
		len = माप_field(काष्ठा nf_conn, mark);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_LABELS
	हाल NFT_CT_LABELS:
		अगर (tb[NFTA_CT_सूचीECTION])
			वापस -EINVAL;
		len = NF_CT_LABELS_MAX_SIZE;
		err = nf_connlabels_get(ctx->net, (len * BITS_PER_BYTE) - 1);
		अगर (err)
			वापस err;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
	हाल NFT_CT_ZONE:
		अगर (!nft_ct_पंचांगpl_alloc_pcpu())
			वापस -ENOMEM;
		nft_ct_pcpu_ढाँचा_refcnt++;
		len = माप(u16);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
	हाल NFT_CT_EVENTMASK:
		अगर (tb[NFTA_CT_सूचीECTION])
			वापस -EINVAL;
		len = माप(u32);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_SECMARK
	हाल NFT_CT_SECMARK:
		अगर (tb[NFTA_CT_सूचीECTION])
			वापस -EINVAL;
		len = माप(u32);
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (tb[NFTA_CT_सूचीECTION]) अणु
		priv->dir = nla_get_u8(tb[NFTA_CT_सूचीECTION]);
		चयन (priv->dir) अणु
		हाल IP_CT_सूची_ORIGINAL:
		हाल IP_CT_सूची_REPLY:
			अवरोध;
		शेष:
			err = -EINVAL;
			जाओ err1;
		पूर्ण
	पूर्ण

	err = nft_parse_रेजिस्टर_load(tb[NFTA_CT_SREG], &priv->sreg, len);
	अगर (err < 0)
		जाओ err1;

	err = nf_ct_netns_get(ctx->net, ctx->family);
	अगर (err < 0)
		जाओ err1;

	वापस 0;

err1:
	__nft_ct_set_destroy(ctx, priv);
	वापस err;
पूर्ण

अटल व्योम nft_ct_get_destroy(स्थिर काष्ठा nft_ctx *ctx,
			       स्थिर काष्ठा nft_expr *expr)
अणु
	nf_ct_netns_put(ctx->net, ctx->family);
पूर्ण

अटल व्योम nft_ct_set_destroy(स्थिर काष्ठा nft_ctx *ctx,
			       स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_ct *priv = nft_expr_priv(expr);

	__nft_ct_set_destroy(ctx, priv);
	nf_ct_netns_put(ctx->net, ctx->family);
पूर्ण

अटल पूर्णांक nft_ct_get_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_ct *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_CT_DREG, priv->dreg))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_CT_KEY, htonl(priv->key)))
		जाओ nla_put_failure;

	चयन (priv->key) अणु
	हाल NFT_CT_SRC:
	हाल NFT_CT_DST:
	हाल NFT_CT_SRC_IP:
	हाल NFT_CT_DST_IP:
	हाल NFT_CT_SRC_IP6:
	हाल NFT_CT_DST_IP6:
	हाल NFT_CT_PROTO_SRC:
	हाल NFT_CT_PROTO_DST:
		अगर (nla_put_u8(skb, NFTA_CT_सूचीECTION, priv->dir))
			जाओ nla_put_failure;
		अवरोध;
	हाल NFT_CT_BYTES:
	हाल NFT_CT_PKTS:
	हाल NFT_CT_AVGPKT:
	हाल NFT_CT_ZONE:
		अगर (priv->dir < IP_CT_सूची_MAX &&
		    nla_put_u8(skb, NFTA_CT_सूचीECTION, priv->dir))
			जाओ nla_put_failure;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nft_ct_set_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_ct *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_CT_SREG, priv->sreg))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_CT_KEY, htonl(priv->key)))
		जाओ nla_put_failure;

	चयन (priv->key) अणु
	हाल NFT_CT_ZONE:
		अगर (priv->dir < IP_CT_सूची_MAX &&
		    nla_put_u8(skb, NFTA_CT_सूचीECTION, priv->dir))
			जाओ nla_put_failure;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल काष्ठा nft_expr_type nft_ct_type;
अटल स्थिर काष्ठा nft_expr_ops nft_ct_get_ops = अणु
	.type		= &nft_ct_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_ct)),
	.eval		= nft_ct_get_eval,
	.init		= nft_ct_get_init,
	.destroy	= nft_ct_get_destroy,
	.dump		= nft_ct_get_dump,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops nft_ct_set_ops = अणु
	.type		= &nft_ct_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_ct)),
	.eval		= nft_ct_set_eval,
	.init		= nft_ct_set_init,
	.destroy	= nft_ct_set_destroy,
	.dump		= nft_ct_set_dump,
पूर्ण;

#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
अटल स्थिर काष्ठा nft_expr_ops nft_ct_set_zone_ops = अणु
	.type		= &nft_ct_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_ct)),
	.eval		= nft_ct_set_zone_eval,
	.init		= nft_ct_set_init,
	.destroy	= nft_ct_set_destroy,
	.dump		= nft_ct_set_dump,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा nft_expr_ops *
nft_ct_select_ops(स्थिर काष्ठा nft_ctx *ctx,
		    स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	अगर (tb[NFTA_CT_KEY] == शून्य)
		वापस ERR_PTR(-EINVAL);

	अगर (tb[NFTA_CT_DREG] && tb[NFTA_CT_SREG])
		वापस ERR_PTR(-EINVAL);

	अगर (tb[NFTA_CT_DREG])
		वापस &nft_ct_get_ops;

	अगर (tb[NFTA_CT_SREG]) अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
		अगर (nla_get_be32(tb[NFTA_CT_KEY]) == htonl(NFT_CT_ZONE))
			वापस &nft_ct_set_zone_ops;
#पूर्ण_अगर
		वापस &nft_ct_set_ops;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा nft_expr_type nft_ct_type __पढ़ो_mostly = अणु
	.name		= "ct",
	.select_ops	= nft_ct_select_ops,
	.policy		= nft_ct_policy,
	.maxattr	= NFTA_CT_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल व्योम nft_notrack_eval(स्थिर काष्ठा nft_expr *expr,
			     काष्ठा nft_regs *regs,
			     स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा sk_buff *skb = pkt->skb;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;

	ct = nf_ct_get(pkt->skb, &ctinfo);
	/* Previously seen (loopback or untracked)?  Ignore. */
	अगर (ct || ctinfo == IP_CT_UNTRACKED)
		वापस;

	nf_ct_set(skb, ct, IP_CT_UNTRACKED);
पूर्ण

अटल काष्ठा nft_expr_type nft_notrack_type;
अटल स्थिर काष्ठा nft_expr_ops nft_notrack_ops = अणु
	.type		= &nft_notrack_type,
	.size		= NFT_EXPR_SIZE(0),
	.eval		= nft_notrack_eval,
पूर्ण;

अटल काष्ठा nft_expr_type nft_notrack_type __पढ़ो_mostly = अणु
	.name		= "notrack",
	.ops		= &nft_notrack_ops,
	.owner		= THIS_MODULE,
पूर्ण;

#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
अटल पूर्णांक
nft_ct_समयout_parse_policy(व्योम *समयouts,
			    स्थिर काष्ठा nf_conntrack_l4proto *l4proto,
			    काष्ठा net *net, स्थिर काष्ठा nlattr *attr)
अणु
	काष्ठा nlattr **tb;
	पूर्णांक ret = 0;

	tb = kसुस्मृति(l4proto->ctnl_समयout.nlattr_max + 1, माप(*tb),
		     GFP_KERNEL);

	अगर (!tb)
		वापस -ENOMEM;

	ret = nla_parse_nested_deprecated(tb,
					  l4proto->ctnl_समयout.nlattr_max,
					  attr,
					  l4proto->ctnl_समयout.nla_policy,
					  शून्य);
	अगर (ret < 0)
		जाओ err;

	ret = l4proto->ctnl_समयout.nlattr_to_obj(tb, net, समयouts);

err:
	kमुक्त(tb);
	वापस ret;
पूर्ण

काष्ठा nft_ct_समयout_obj अणु
	काष्ठा nf_ct_समयout    *समयout;
	u8			l4proto;
पूर्ण;

अटल व्योम nft_ct_समयout_obj_eval(काष्ठा nft_object *obj,
				    काष्ठा nft_regs *regs,
				    स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_ct_समयout_obj *priv = nft_obj_data(obj);
	काष्ठा nf_conn *ct = (काष्ठा nf_conn *)skb_nfct(pkt->skb);
	काष्ठा nf_conn_समयout *समयout;
	स्थिर अचिन्हित पूर्णांक *values;

	अगर (priv->l4proto != pkt->tprot)
		वापस;

	अगर (!ct || nf_ct_is_ढाँचा(ct) || nf_ct_is_confirmed(ct))
		वापस;

	समयout = nf_ct_समयout_find(ct);
	अगर (!समयout) अणु
		समयout = nf_ct_समयout_ext_add(ct, priv->समयout, GFP_ATOMIC);
		अगर (!समयout) अणु
			regs->verdict.code = NF_DROP;
			वापस;
		पूर्ण
	पूर्ण

	rcu_assign_poपूर्णांकer(समयout->समयout, priv->समयout);

	/* adjust the समयout as per 'new' state. ct is unconfirmed,
	 * so the current बारtamp must not be added.
	 */
	values = nf_ct_समयout_data(समयout);
	अगर (values)
		nf_ct_refresh(ct, pkt->skb, values[0]);
पूर्ण

अटल पूर्णांक nft_ct_समयout_obj_init(स्थिर काष्ठा nft_ctx *ctx,
				   स्थिर काष्ठा nlattr * स्थिर tb[],
				   काष्ठा nft_object *obj)
अणु
	काष्ठा nft_ct_समयout_obj *priv = nft_obj_data(obj);
	स्थिर काष्ठा nf_conntrack_l4proto *l4proto;
	काष्ठा nf_ct_समयout *समयout;
	पूर्णांक l3num = ctx->family;
	__u8 l4num;
	पूर्णांक ret;

	अगर (!tb[NFTA_CT_TIMEOUT_L4PROTO] ||
	    !tb[NFTA_CT_TIMEOUT_DATA])
		वापस -EINVAL;

	अगर (tb[NFTA_CT_TIMEOUT_L3PROTO])
		l3num = ntohs(nla_get_be16(tb[NFTA_CT_TIMEOUT_L3PROTO]));

	l4num = nla_get_u8(tb[NFTA_CT_TIMEOUT_L4PROTO]);
	priv->l4proto = l4num;

	l4proto = nf_ct_l4proto_find(l4num);

	अगर (l4proto->l4proto != l4num) अणु
		ret = -EOPNOTSUPP;
		जाओ err_proto_put;
	पूर्ण

	समयout = kzalloc(माप(काष्ठा nf_ct_समयout) +
			  l4proto->ctnl_समयout.obj_size, GFP_KERNEL);
	अगर (समयout == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_proto_put;
	पूर्ण

	ret = nft_ct_समयout_parse_policy(&समयout->data, l4proto, ctx->net,
					  tb[NFTA_CT_TIMEOUT_DATA]);
	अगर (ret < 0)
		जाओ err_मुक्त_समयout;

	समयout->l3num = l3num;
	समयout->l4proto = l4proto;

	ret = nf_ct_netns_get(ctx->net, ctx->family);
	अगर (ret < 0)
		जाओ err_मुक्त_समयout;

	priv->समयout = समयout;
	वापस 0;

err_मुक्त_समयout:
	kमुक्त(समयout);
err_proto_put:
	वापस ret;
पूर्ण

अटल व्योम nft_ct_समयout_obj_destroy(स्थिर काष्ठा nft_ctx *ctx,
				       काष्ठा nft_object *obj)
अणु
	काष्ठा nft_ct_समयout_obj *priv = nft_obj_data(obj);
	काष्ठा nf_ct_समयout *समयout = priv->समयout;

	nf_ct_unसमयout(ctx->net, समयout);
	nf_ct_netns_put(ctx->net, ctx->family);
	kमुक्त(priv->समयout);
पूर्ण

अटल पूर्णांक nft_ct_समयout_obj_dump(काष्ठा sk_buff *skb,
				   काष्ठा nft_object *obj, bool reset)
अणु
	स्थिर काष्ठा nft_ct_समयout_obj *priv = nft_obj_data(obj);
	स्थिर काष्ठा nf_ct_समयout *समयout = priv->समयout;
	काष्ठा nlattr *nest_params;
	पूर्णांक ret;

	अगर (nla_put_u8(skb, NFTA_CT_TIMEOUT_L4PROTO, समयout->l4proto->l4proto) ||
	    nla_put_be16(skb, NFTA_CT_TIMEOUT_L3PROTO, htons(समयout->l3num)))
		वापस -1;

	nest_params = nla_nest_start(skb, NFTA_CT_TIMEOUT_DATA);
	अगर (!nest_params)
		वापस -1;

	ret = समयout->l4proto->ctnl_समयout.obj_to_nlattr(skb, &समयout->data);
	अगर (ret < 0)
		वापस -1;
	nla_nest_end(skb, nest_params);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_ct_समयout_policy[NFTA_CT_TIMEOUT_MAX + 1] = अणु
	[NFTA_CT_TIMEOUT_L3PROTO] = अणु.type = NLA_U16 पूर्ण,
	[NFTA_CT_TIMEOUT_L4PROTO] = अणु.type = NLA_U8 पूर्ण,
	[NFTA_CT_TIMEOUT_DATA]	  = अणु.type = NLA_NESTED पूर्ण,
पूर्ण;

अटल काष्ठा nft_object_type nft_ct_समयout_obj_type;

अटल स्थिर काष्ठा nft_object_ops nft_ct_समयout_obj_ops = अणु
	.type		= &nft_ct_समयout_obj_type,
	.size		= माप(काष्ठा nft_ct_समयout_obj),
	.eval		= nft_ct_समयout_obj_eval,
	.init		= nft_ct_समयout_obj_init,
	.destroy	= nft_ct_समयout_obj_destroy,
	.dump		= nft_ct_समयout_obj_dump,
पूर्ण;

अटल काष्ठा nft_object_type nft_ct_समयout_obj_type __पढ़ो_mostly = अणु
	.type		= NFT_OBJECT_CT_TIMEOUT,
	.ops		= &nft_ct_समयout_obj_ops,
	.maxattr	= NFTA_CT_TIMEOUT_MAX,
	.policy		= nft_ct_समयout_policy,
	.owner		= THIS_MODULE,
पूर्ण;
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */

अटल पूर्णांक nft_ct_helper_obj_init(स्थिर काष्ठा nft_ctx *ctx,
				  स्थिर काष्ठा nlattr * स्थिर tb[],
				  काष्ठा nft_object *obj)
अणु
	काष्ठा nft_ct_helper_obj *priv = nft_obj_data(obj);
	काष्ठा nf_conntrack_helper *help4, *help6;
	अक्षर name[NF_CT_HELPER_NAME_LEN];
	पूर्णांक family = ctx->family;
	पूर्णांक err;

	अगर (!tb[NFTA_CT_HELPER_NAME] || !tb[NFTA_CT_HELPER_L4PROTO])
		वापस -EINVAL;

	priv->l4proto = nla_get_u8(tb[NFTA_CT_HELPER_L4PROTO]);
	अगर (!priv->l4proto)
		वापस -ENOENT;

	nla_strscpy(name, tb[NFTA_CT_HELPER_NAME], माप(name));

	अगर (tb[NFTA_CT_HELPER_L3PROTO])
		family = ntohs(nla_get_be16(tb[NFTA_CT_HELPER_L3PROTO]));

	help4 = शून्य;
	help6 = शून्य;

	चयन (family) अणु
	हाल NFPROTO_IPV4:
		अगर (ctx->family == NFPROTO_IPV6)
			वापस -EINVAL;

		help4 = nf_conntrack_helper_try_module_get(name, family,
							   priv->l4proto);
		अवरोध;
	हाल NFPROTO_IPV6:
		अगर (ctx->family == NFPROTO_IPV4)
			वापस -EINVAL;

		help6 = nf_conntrack_helper_try_module_get(name, family,
							   priv->l4proto);
		अवरोध;
	हाल NFPROTO_NETDEV:
	हाल NFPROTO_BRIDGE:
	हाल NFPROTO_INET:
		help4 = nf_conntrack_helper_try_module_get(name, NFPROTO_IPV4,
							   priv->l4proto);
		help6 = nf_conntrack_helper_try_module_get(name, NFPROTO_IPV6,
							   priv->l4proto);
		अवरोध;
	शेष:
		वापस -EAFNOSUPPORT;
	पूर्ण

	/* && is पूर्णांकentional; only error अगर INET found neither ipv4 or ipv6 */
	अगर (!help4 && !help6)
		वापस -ENOENT;

	priv->helper4 = help4;
	priv->helper6 = help6;

	err = nf_ct_netns_get(ctx->net, ctx->family);
	अगर (err < 0)
		जाओ err_put_helper;

	वापस 0;

err_put_helper:
	अगर (priv->helper4)
		nf_conntrack_helper_put(priv->helper4);
	अगर (priv->helper6)
		nf_conntrack_helper_put(priv->helper6);
	वापस err;
पूर्ण

अटल व्योम nft_ct_helper_obj_destroy(स्थिर काष्ठा nft_ctx *ctx,
				      काष्ठा nft_object *obj)
अणु
	काष्ठा nft_ct_helper_obj *priv = nft_obj_data(obj);

	अगर (priv->helper4)
		nf_conntrack_helper_put(priv->helper4);
	अगर (priv->helper6)
		nf_conntrack_helper_put(priv->helper6);

	nf_ct_netns_put(ctx->net, ctx->family);
पूर्ण

अटल व्योम nft_ct_helper_obj_eval(काष्ठा nft_object *obj,
				   काष्ठा nft_regs *regs,
				   स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_ct_helper_obj *priv = nft_obj_data(obj);
	काष्ठा nf_conn *ct = (काष्ठा nf_conn *)skb_nfct(pkt->skb);
	काष्ठा nf_conntrack_helper *to_assign = शून्य;
	काष्ठा nf_conn_help *help;

	अगर (!ct ||
	    nf_ct_is_confirmed(ct) ||
	    nf_ct_is_ढाँचा(ct) ||
	    priv->l4proto != nf_ct_protonum(ct))
		वापस;

	चयन (nf_ct_l3num(ct)) अणु
	हाल NFPROTO_IPV4:
		to_assign = priv->helper4;
		अवरोध;
	हाल NFPROTO_IPV6:
		to_assign = priv->helper6;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	अगर (!to_assign)
		वापस;

	अगर (test_bit(IPS_HELPER_BIT, &ct->status))
		वापस;

	help = nf_ct_helper_ext_add(ct, GFP_ATOMIC);
	अगर (help) अणु
		rcu_assign_poपूर्णांकer(help->helper, to_assign);
		set_bit(IPS_HELPER_BIT, &ct->status);
	पूर्ण
पूर्ण

अटल पूर्णांक nft_ct_helper_obj_dump(काष्ठा sk_buff *skb,
				  काष्ठा nft_object *obj, bool reset)
अणु
	स्थिर काष्ठा nft_ct_helper_obj *priv = nft_obj_data(obj);
	स्थिर काष्ठा nf_conntrack_helper *helper;
	u16 family;

	अगर (priv->helper4 && priv->helper6) अणु
		family = NFPROTO_INET;
		helper = priv->helper4;
	पूर्ण अन्यथा अगर (priv->helper6) अणु
		family = NFPROTO_IPV6;
		helper = priv->helper6;
	पूर्ण अन्यथा अणु
		family = NFPROTO_IPV4;
		helper = priv->helper4;
	पूर्ण

	अगर (nla_put_string(skb, NFTA_CT_HELPER_NAME, helper->name))
		वापस -1;

	अगर (nla_put_u8(skb, NFTA_CT_HELPER_L4PROTO, priv->l4proto))
		वापस -1;

	अगर (nla_put_be16(skb, NFTA_CT_HELPER_L3PROTO, htons(family)))
		वापस -1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_ct_helper_policy[NFTA_CT_HELPER_MAX + 1] = अणु
	[NFTA_CT_HELPER_NAME] = अणु .type = NLA_STRING,
				  .len = NF_CT_HELPER_NAME_LEN - 1 पूर्ण,
	[NFTA_CT_HELPER_L3PROTO] = अणु .type = NLA_U16 पूर्ण,
	[NFTA_CT_HELPER_L4PROTO] = अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल काष्ठा nft_object_type nft_ct_helper_obj_type;
अटल स्थिर काष्ठा nft_object_ops nft_ct_helper_obj_ops = अणु
	.type		= &nft_ct_helper_obj_type,
	.size		= माप(काष्ठा nft_ct_helper_obj),
	.eval		= nft_ct_helper_obj_eval,
	.init		= nft_ct_helper_obj_init,
	.destroy	= nft_ct_helper_obj_destroy,
	.dump		= nft_ct_helper_obj_dump,
पूर्ण;

अटल काष्ठा nft_object_type nft_ct_helper_obj_type __पढ़ो_mostly = अणु
	.type		= NFT_OBJECT_CT_HELPER,
	.ops		= &nft_ct_helper_obj_ops,
	.maxattr	= NFTA_CT_HELPER_MAX,
	.policy		= nft_ct_helper_policy,
	.owner		= THIS_MODULE,
पूर्ण;

काष्ठा nft_ct_expect_obj अणु
	u16		l3num;
	__be16		dport;
	u8		l4proto;
	u8		size;
	u32		समयout;
पूर्ण;

अटल पूर्णांक nft_ct_expect_obj_init(स्थिर काष्ठा nft_ctx *ctx,
				  स्थिर काष्ठा nlattr * स्थिर tb[],
				  काष्ठा nft_object *obj)
अणु
	काष्ठा nft_ct_expect_obj *priv = nft_obj_data(obj);

	अगर (!tb[NFTA_CT_EXPECT_L4PROTO] ||
	    !tb[NFTA_CT_EXPECT_DPORT] ||
	    !tb[NFTA_CT_EXPECT_TIMEOUT] ||
	    !tb[NFTA_CT_EXPECT_SIZE])
		वापस -EINVAL;

	priv->l3num = ctx->family;
	अगर (tb[NFTA_CT_EXPECT_L3PROTO])
		priv->l3num = ntohs(nla_get_be16(tb[NFTA_CT_EXPECT_L3PROTO]));

	priv->l4proto = nla_get_u8(tb[NFTA_CT_EXPECT_L4PROTO]);
	priv->dport = nla_get_be16(tb[NFTA_CT_EXPECT_DPORT]);
	priv->समयout = nla_get_u32(tb[NFTA_CT_EXPECT_TIMEOUT]);
	priv->size = nla_get_u8(tb[NFTA_CT_EXPECT_SIZE]);

	वापस nf_ct_netns_get(ctx->net, ctx->family);
पूर्ण

अटल व्योम nft_ct_expect_obj_destroy(स्थिर काष्ठा nft_ctx *ctx,
				       काष्ठा nft_object *obj)
अणु
	nf_ct_netns_put(ctx->net, ctx->family);
पूर्ण

अटल पूर्णांक nft_ct_expect_obj_dump(काष्ठा sk_buff *skb,
				  काष्ठा nft_object *obj, bool reset)
अणु
	स्थिर काष्ठा nft_ct_expect_obj *priv = nft_obj_data(obj);

	अगर (nla_put_be16(skb, NFTA_CT_EXPECT_L3PROTO, htons(priv->l3num)) ||
	    nla_put_u8(skb, NFTA_CT_EXPECT_L4PROTO, priv->l4proto) ||
	    nla_put_be16(skb, NFTA_CT_EXPECT_DPORT, priv->dport) ||
	    nla_put_u32(skb, NFTA_CT_EXPECT_TIMEOUT, priv->समयout) ||
	    nla_put_u8(skb, NFTA_CT_EXPECT_SIZE, priv->size))
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम nft_ct_expect_obj_eval(काष्ठा nft_object *obj,
				   काष्ठा nft_regs *regs,
				   स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_ct_expect_obj *priv = nft_obj_data(obj);
	काष्ठा nf_conntrack_expect *exp;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn_help *help;
	क्रमागत ip_conntrack_dir dir;
	u16 l3num = priv->l3num;
	काष्ठा nf_conn *ct;

	ct = nf_ct_get(pkt->skb, &ctinfo);
	अगर (!ct || nf_ct_is_confirmed(ct) || nf_ct_is_ढाँचा(ct)) अणु
		regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण
	dir = CTINFO2सूची(ctinfo);

	help = nfct_help(ct);
	अगर (!help)
		help = nf_ct_helper_ext_add(ct, GFP_ATOMIC);
	अगर (!help) अणु
		regs->verdict.code = NF_DROP;
		वापस;
	पूर्ण

	अगर (help->expecting[NF_CT_EXPECT_CLASS_DEFAULT] >= priv->size) अणु
		regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण
	अगर (l3num == NFPROTO_INET)
		l3num = nf_ct_l3num(ct);

	exp = nf_ct_expect_alloc(ct);
	अगर (exp == शून्य) अणु
		regs->verdict.code = NF_DROP;
		वापस;
	पूर्ण
	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, l3num,
		          &ct->tuplehash[!dir].tuple.src.u3,
		          &ct->tuplehash[!dir].tuple.dst.u3,
		          priv->l4proto, शून्य, &priv->dport);
	exp->समयout.expires = jअगरfies + priv->समयout * HZ;

	अगर (nf_ct_expect_related(exp, 0) != 0)
		regs->verdict.code = NF_DROP;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_ct_expect_policy[NFTA_CT_EXPECT_MAX + 1] = अणु
	[NFTA_CT_EXPECT_L3PROTO]	= अणु .type = NLA_U16 पूर्ण,
	[NFTA_CT_EXPECT_L4PROTO]	= अणु .type = NLA_U8 पूर्ण,
	[NFTA_CT_EXPECT_DPORT]		= अणु .type = NLA_U16 पूर्ण,
	[NFTA_CT_EXPECT_TIMEOUT]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_CT_EXPECT_SIZE]		= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल काष्ठा nft_object_type nft_ct_expect_obj_type;

अटल स्थिर काष्ठा nft_object_ops nft_ct_expect_obj_ops = अणु
	.type		= &nft_ct_expect_obj_type,
	.size		= माप(काष्ठा nft_ct_expect_obj),
	.eval		= nft_ct_expect_obj_eval,
	.init		= nft_ct_expect_obj_init,
	.destroy	= nft_ct_expect_obj_destroy,
	.dump		= nft_ct_expect_obj_dump,
पूर्ण;

अटल काष्ठा nft_object_type nft_ct_expect_obj_type __पढ़ो_mostly = अणु
	.type		= NFT_OBJECT_CT_EXPECT,
	.ops		= &nft_ct_expect_obj_ops,
	.maxattr	= NFTA_CT_EXPECT_MAX,
	.policy		= nft_ct_expect_policy,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_ct_module_init(व्योम)
अणु
	पूर्णांक err;

	BUILD_BUG_ON(NF_CT_LABELS_MAX_SIZE > NFT_REG_SIZE);

	err = nft_रेजिस्टर_expr(&nft_ct_type);
	अगर (err < 0)
		वापस err;

	err = nft_रेजिस्टर_expr(&nft_notrack_type);
	अगर (err < 0)
		जाओ err1;

	err = nft_रेजिस्टर_obj(&nft_ct_helper_obj_type);
	अगर (err < 0)
		जाओ err2;

	err = nft_रेजिस्टर_obj(&nft_ct_expect_obj_type);
	अगर (err < 0)
		जाओ err3;
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
	err = nft_रेजिस्टर_obj(&nft_ct_समयout_obj_type);
	अगर (err < 0)
		जाओ err4;
#पूर्ण_अगर
	वापस 0;

#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
err4:
	nft_unरेजिस्टर_obj(&nft_ct_expect_obj_type);
#पूर्ण_अगर
err3:
	nft_unरेजिस्टर_obj(&nft_ct_helper_obj_type);
err2:
	nft_unरेजिस्टर_expr(&nft_notrack_type);
err1:
	nft_unरेजिस्टर_expr(&nft_ct_type);
	वापस err;
पूर्ण

अटल व्योम __निकास nft_ct_module_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
	nft_unरेजिस्टर_obj(&nft_ct_समयout_obj_type);
#पूर्ण_अगर
	nft_unरेजिस्टर_obj(&nft_ct_expect_obj_type);
	nft_unरेजिस्टर_obj(&nft_ct_helper_obj_type);
	nft_unरेजिस्टर_expr(&nft_notrack_type);
	nft_unरेजिस्टर_expr(&nft_ct_type);
पूर्ण

module_init(nft_ct_module_init);
module_निकास(nft_ct_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_ALIAS_NFT_EXPR("ct");
MODULE_ALIAS_NFT_EXPR("notrack");
MODULE_ALIAS_NFT_OBJ(NFT_OBJECT_CT_HELPER);
MODULE_ALIAS_NFT_OBJ(NFT_OBJECT_CT_TIMEOUT);
MODULE_ALIAS_NFT_OBJ(NFT_OBJECT_CT_EXPECT);
MODULE_DESCRIPTION("Netfilter nf_tables conntrack module");
