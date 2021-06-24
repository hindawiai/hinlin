<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Connection tracking protocol helper module क्रम GRE.
 *
 * GRE is a generic encapsulation protocol, which is generally not very
 * suited क्रम NAT, as it has no protocol-specअगरic part as port numbers.
 *
 * It has an optional key field, which may help us distinguishing two
 * connections between the same two hosts.
 *
 * GRE is defined in RFC 1701 and RFC 1702, as well as RFC 2784
 *
 * PPTP is built on top of a modअगरied version of GRE, and has a mandatory
 * field called "CallID", which serves us क्रम the same purpose as the key
 * field in plain GRE.
 *
 * Documentation about PPTP can be found in RFC 2637
 *
 * (C) 2000-2005 by Harald Welte <laक्रमge@gnumonks.org>
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 *
 * (C) 2006-2012 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/in.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <net/dst.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_समयout.h>
#समावेश <linux/netfilter/nf_conntrack_proto_gre.h>
#समावेश <linux/netfilter/nf_conntrack_pptp.h>

अटल स्थिर अचिन्हित पूर्णांक gre_समयouts[GRE_CT_MAX] = अणु
	[GRE_CT_UNREPLIED]	= 30*HZ,
	[GRE_CT_REPLIED]	= 180*HZ,
पूर्ण;

/* used when expectation is added */
अटल DEFINE_SPINLOCK(keymap_lock);

अटल अंतरभूत काष्ठा nf_gre_net *gre_pernet(काष्ठा net *net)
अणु
	वापस &net->ct.nf_ct_proto.gre;
पूर्ण

व्योम nf_ct_gre_keymap_flush(काष्ठा net *net)
अणु
	काष्ठा nf_gre_net *net_gre = gre_pernet(net);
	काष्ठा nf_ct_gre_keymap *km, *पंचांगp;

	spin_lock_bh(&keymap_lock);
	list_क्रम_each_entry_safe(km, पंचांगp, &net_gre->keymap_list, list) अणु
		list_del_rcu(&km->list);
		kमुक्त_rcu(km, rcu);
	पूर्ण
	spin_unlock_bh(&keymap_lock);
पूर्ण

अटल अंतरभूत पूर्णांक gre_key_cmpfn(स्थिर काष्ठा nf_ct_gre_keymap *km,
				स्थिर काष्ठा nf_conntrack_tuple *t)
अणु
	वापस km->tuple.src.l3num == t->src.l3num &&
	       !स_भेद(&km->tuple.src.u3, &t->src.u3, माप(t->src.u3)) &&
	       !स_भेद(&km->tuple.dst.u3, &t->dst.u3, माप(t->dst.u3)) &&
	       km->tuple.dst.protonum == t->dst.protonum &&
	       km->tuple.dst.u.all == t->dst.u.all;
पूर्ण

/* look up the source key क्रम a given tuple */
अटल __be16 gre_keymap_lookup(काष्ठा net *net, काष्ठा nf_conntrack_tuple *t)
अणु
	काष्ठा nf_gre_net *net_gre = gre_pernet(net);
	काष्ठा nf_ct_gre_keymap *km;
	__be16 key = 0;

	list_क्रम_each_entry_rcu(km, &net_gre->keymap_list, list) अणु
		अगर (gre_key_cmpfn(km, t)) अणु
			key = km->tuple.src.u.gre.key;
			अवरोध;
		पूर्ण
	पूर्ण

	pr_debug("lookup src key 0x%x for ", key);
	nf_ct_dump_tuple(t);

	वापस key;
पूर्ण

/* add a single keymap entry, associate with specअगरied master ct */
पूर्णांक nf_ct_gre_keymap_add(काष्ठा nf_conn *ct, क्रमागत ip_conntrack_dir dir,
			 काष्ठा nf_conntrack_tuple *t)
अणु
	काष्ठा net *net = nf_ct_net(ct);
	काष्ठा nf_gre_net *net_gre = gre_pernet(net);
	काष्ठा nf_ct_pptp_master *ct_pptp_info = nfct_help_data(ct);
	काष्ठा nf_ct_gre_keymap **kmp, *km;

	kmp = &ct_pptp_info->keymap[dir];
	अगर (*kmp) अणु
		/* check whether it's a retransmission */
		list_क्रम_each_entry_rcu(km, &net_gre->keymap_list, list) अणु
			अगर (gre_key_cmpfn(km, t) && km == *kmp)
				वापस 0;
		पूर्ण
		pr_debug("trying to override keymap_%s for ct %p\n",
			 dir == IP_CT_सूची_REPLY ? "reply" : "orig", ct);
		वापस -EEXIST;
	पूर्ण

	km = kदो_स्मृति(माप(*km), GFP_ATOMIC);
	अगर (!km)
		वापस -ENOMEM;
	स_नकल(&km->tuple, t, माप(*t));
	*kmp = km;

	pr_debug("adding new entry %p: ", km);
	nf_ct_dump_tuple(&km->tuple);

	spin_lock_bh(&keymap_lock);
	list_add_tail(&km->list, &net_gre->keymap_list);
	spin_unlock_bh(&keymap_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_gre_keymap_add);

/* destroy the keymap entries associated with specअगरied master ct */
व्योम nf_ct_gre_keymap_destroy(काष्ठा nf_conn *ct)
अणु
	काष्ठा nf_ct_pptp_master *ct_pptp_info = nfct_help_data(ct);
	क्रमागत ip_conntrack_dir dir;

	pr_debug("entering for ct %p\n", ct);

	spin_lock_bh(&keymap_lock);
	क्रम (dir = IP_CT_सूची_ORIGINAL; dir < IP_CT_सूची_MAX; dir++) अणु
		अगर (ct_pptp_info->keymap[dir]) अणु
			pr_debug("removing %p from list\n",
				 ct_pptp_info->keymap[dir]);
			list_del_rcu(&ct_pptp_info->keymap[dir]->list);
			kमुक्त_rcu(ct_pptp_info->keymap[dir], rcu);
			ct_pptp_info->keymap[dir] = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&keymap_lock);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_gre_keymap_destroy);

/* PUBLIC CONNTRACK PROTO HELPER FUNCTIONS */

/* gre hdr info to tuple */
bool gre_pkt_to_tuple(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक dataoff,
		      काष्ठा net *net, काष्ठा nf_conntrack_tuple *tuple)
अणु
	स्थिर काष्ठा pptp_gre_header *pgrehdr;
	काष्ठा pptp_gre_header _pgrehdr;
	__be16 srckey;
	स्थिर काष्ठा gre_base_hdr *grehdr;
	काष्ठा gre_base_hdr _grehdr;

	/* first only delinearize old RFC1701 GRE header */
	grehdr = skb_header_poपूर्णांकer(skb, dataoff, माप(_grehdr), &_grehdr);
	अगर (!grehdr || (grehdr->flags & GRE_VERSION) != GRE_VERSION_1) अणु
		/* try to behave like "nf_conntrack_proto_generic" */
		tuple->src.u.all = 0;
		tuple->dst.u.all = 0;
		वापस true;
	पूर्ण

	/* PPTP header is variable length, only need up to the call_id field */
	pgrehdr = skb_header_poपूर्णांकer(skb, dataoff, 8, &_pgrehdr);
	अगर (!pgrehdr)
		वापस true;

	अगर (grehdr->protocol != GRE_PROTO_PPP) अणु
		pr_debug("Unsupported GRE proto(0x%x)\n", ntohs(grehdr->protocol));
		वापस false;
	पूर्ण

	tuple->dst.u.gre.key = pgrehdr->call_id;
	srckey = gre_keymap_lookup(net, tuple);
	tuple->src.u.gre.key = srckey;

	वापस true;
पूर्ण

#अगर_घोषित CONFIG_NF_CONNTRACK_PROCFS
/* prपूर्णांक निजी data क्रम conntrack */
अटल व्योम gre_prपूर्णांक_conntrack(काष्ठा seq_file *s, काष्ठा nf_conn *ct)
अणु
	seq_म_लिखो(s, "timeout=%u, stream_timeout=%u ",
		   (ct->proto.gre.समयout / HZ),
		   (ct->proto.gre.stream_समयout / HZ));
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक *gre_get_समयouts(काष्ठा net *net)
अणु
	वापस gre_pernet(net)->समयouts;
पूर्ण

/* Returns verdict क्रम packet, and may modअगरy conntrack */
पूर्णांक nf_conntrack_gre_packet(काष्ठा nf_conn *ct,
			    काष्ठा sk_buff *skb,
			    अचिन्हित पूर्णांक dataoff,
			    क्रमागत ip_conntrack_info ctinfo,
			    स्थिर काष्ठा nf_hook_state *state)
अणु
	अगर (!nf_ct_is_confirmed(ct)) अणु
		अचिन्हित पूर्णांक *समयouts = nf_ct_समयout_lookup(ct);

		अगर (!समयouts)
			समयouts = gre_get_समयouts(nf_ct_net(ct));

		/* initialize to sane value.  Ideally a conntrack helper
		 * (e.g. in हाल of pptp) is increasing them */
		ct->proto.gre.stream_समयout = समयouts[GRE_CT_REPLIED];
		ct->proto.gre.समयout = समयouts[GRE_CT_UNREPLIED];
	पूर्ण

	/* If we've seen traffic both ways, this is a GRE connection.
	 * Extend समयout. */
	अगर (ct->status & IPS_SEEN_REPLY) अणु
		nf_ct_refresh_acct(ct, ctinfo, skb,
				   ct->proto.gre.stream_समयout);
		/* Also, more likely to be important, and not a probe. */
		अगर (!test_and_set_bit(IPS_ASSURED_BIT, &ct->status))
			nf_conntrack_event_cache(IPCT_ASSURED, ct);
	पूर्ण अन्यथा
		nf_ct_refresh_acct(ct, ctinfo, skb,
				   ct->proto.gre.समयout);

	वापस NF_ACCEPT;
पूर्ण

#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_ctसमयout.h>

अटल पूर्णांक gre_समयout_nlattr_to_obj(काष्ठा nlattr *tb[],
				     काष्ठा net *net, व्योम *data)
अणु
	अचिन्हित पूर्णांक *समयouts = data;
	काष्ठा nf_gre_net *net_gre = gre_pernet(net);

	अगर (!समयouts)
		समयouts = gre_get_समयouts(net);
	/* set शेष समयouts क्रम GRE. */
	समयouts[GRE_CT_UNREPLIED] = net_gre->समयouts[GRE_CT_UNREPLIED];
	समयouts[GRE_CT_REPLIED] = net_gre->समयouts[GRE_CT_REPLIED];

	अगर (tb[CTA_TIMEOUT_GRE_UNREPLIED]) अणु
		समयouts[GRE_CT_UNREPLIED] =
			ntohl(nla_get_be32(tb[CTA_TIMEOUT_GRE_UNREPLIED])) * HZ;
	पूर्ण
	अगर (tb[CTA_TIMEOUT_GRE_REPLIED]) अणु
		समयouts[GRE_CT_REPLIED] =
			ntohl(nla_get_be32(tb[CTA_TIMEOUT_GRE_REPLIED])) * HZ;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
gre_समयout_obj_to_nlattr(काष्ठा sk_buff *skb, स्थिर व्योम *data)
अणु
	स्थिर अचिन्हित पूर्णांक *समयouts = data;

	अगर (nla_put_be32(skb, CTA_TIMEOUT_GRE_UNREPLIED,
			 htonl(समयouts[GRE_CT_UNREPLIED] / HZ)) ||
	    nla_put_be32(skb, CTA_TIMEOUT_GRE_REPLIED,
			 htonl(समयouts[GRE_CT_REPLIED] / HZ)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -ENOSPC;
पूर्ण

अटल स्थिर काष्ठा nla_policy
gre_समयout_nla_policy[CTA_TIMEOUT_GRE_MAX+1] = अणु
	[CTA_TIMEOUT_GRE_UNREPLIED]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_GRE_REPLIED]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */

व्योम nf_conntrack_gre_init_net(काष्ठा net *net)
अणु
	काष्ठा nf_gre_net *net_gre = gre_pernet(net);
	पूर्णांक i;

	INIT_LIST_HEAD(&net_gre->keymap_list);
	क्रम (i = 0; i < GRE_CT_MAX; i++)
		net_gre->समयouts[i] = gre_समयouts[i];
पूर्ण

/* protocol helper काष्ठा */
स्थिर काष्ठा nf_conntrack_l4proto nf_conntrack_l4proto_gre = अणु
	.l4proto	 = IPPROTO_GRE,
#अगर_घोषित CONFIG_NF_CONNTRACK_PROCFS
	.prपूर्णांक_conntrack = gre_prपूर्णांक_conntrack,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_NF_CT_NETLINK)
	.tuple_to_nlattr = nf_ct_port_tuple_to_nlattr,
	.nlattr_tuple_size = nf_ct_port_nlattr_tuple_size,
	.nlattr_to_tuple = nf_ct_port_nlattr_to_tuple,
	.nla_policy	 = nf_ct_port_nla_policy,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
	.ctnl_समयout    = अणु
		.nlattr_to_obj	= gre_समयout_nlattr_to_obj,
		.obj_to_nlattr	= gre_समयout_obj_to_nlattr,
		.nlattr_max	= CTA_TIMEOUT_GRE_MAX,
		.obj_size	= माप(अचिन्हित पूर्णांक) * GRE_CT_MAX,
		.nla_policy	= gre_समयout_nla_policy,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */
पूर्ण;
