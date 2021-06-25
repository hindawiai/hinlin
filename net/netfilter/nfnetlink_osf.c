<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

#समावेश <linux/capability.h>
#समावेश <linux/अगर.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/list.h>
#समावेश <linux/rculist.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/tcp.h>

#समावेश <net/ip.h>
#समावेश <net/tcp.h>

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <net/netfilter/nf_log.h>
#समावेश <linux/netfilter/nfnetlink_osf.h>

/*
 * Indexed by करोnt-fragment bit.
 * It is the only स्थिरant value in the fingerprपूर्णांक.
 */
काष्ठा list_head nf_osf_fingers[2];
EXPORT_SYMBOL_GPL(nf_osf_fingers);

अटल अंतरभूत पूर्णांक nf_osf_ttl(स्थिर काष्ठा sk_buff *skb,
			     पूर्णांक ttl_check, अचिन्हित अक्षर f_ttl)
अणु
	काष्ठा in_device *in_dev = __in_dev_get_rcu(skb->dev);
	स्थिर काष्ठा iphdr *ip = ip_hdr(skb);
	स्थिर काष्ठा in_अगरaddr *अगरa;
	पूर्णांक ret = 0;

	अगर (ttl_check == NF_OSF_TTL_TRUE)
		वापस ip->ttl == f_ttl;
	अगर (ttl_check == NF_OSF_TTL_NOCHECK)
		वापस 1;
	अन्यथा अगर (ip->ttl <= f_ttl)
		वापस 1;

	in_dev_क्रम_each_अगरa_rcu(अगरa, in_dev) अणु
		अगर (inet_अगरa_match(ip->saddr, अगरa)) अणु
			ret = (ip->ttl == f_ttl);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा nf_osf_hdr_ctx अणु
	bool			df;
	u16			winकरोw;
	u16			totlen;
	स्थिर अचिन्हित अक्षर	*optp;
	अचिन्हित पूर्णांक		optsize;
पूर्ण;

अटल bool nf_osf_match_one(स्थिर काष्ठा sk_buff *skb,
			     स्थिर काष्ठा nf_osf_user_finger *f,
			     पूर्णांक ttl_check,
			     काष्ठा nf_osf_hdr_ctx *ctx)
अणु
	स्थिर __u8 *optpinit = ctx->optp;
	अचिन्हित पूर्णांक check_WSS = 0;
	पूर्णांक fmatch = FMATCH_WRONG;
	पूर्णांक foptsize, optnum;
	u16 mss = 0;

	अगर (ctx->totlen != f->ss || !nf_osf_ttl(skb, ttl_check, f->ttl))
		वापस false;

	/*
	 * Should not happen अगर userspace parser was written correctly.
	 */
	अगर (f->wss.wc >= OSF_WSS_MAX)
		वापस false;

	/* Check options */

	foptsize = 0;
	क्रम (optnum = 0; optnum < f->opt_num; ++optnum)
		foptsize += f->opt[optnum].length;

	अगर (foptsize > MAX_IPOPTLEN ||
	    ctx->optsize > MAX_IPOPTLEN ||
	    ctx->optsize != foptsize)
		वापस false;

	check_WSS = f->wss.wc;

	क्रम (optnum = 0; optnum < f->opt_num; ++optnum) अणु
		अगर (f->opt[optnum].kind == *ctx->optp) अणु
			__u32 len = f->opt[optnum].length;
			स्थिर __u8 *optend = ctx->optp + len;

			fmatch = FMATCH_OK;

			चयन (*ctx->optp) अणु
			हाल OSFOPT_MSS:
				mss = ctx->optp[3];
				mss <<= 8;
				mss |= ctx->optp[2];

				mss = ntohs((__क्रमce __be16)mss);
				अवरोध;
			हाल OSFOPT_TS:
				अवरोध;
			पूर्ण

			ctx->optp = optend;
		पूर्ण अन्यथा
			fmatch = FMATCH_OPT_WRONG;

		अगर (fmatch != FMATCH_OK)
			अवरोध;
	पूर्ण

	अगर (fmatch != FMATCH_OPT_WRONG) अणु
		fmatch = FMATCH_WRONG;

		चयन (check_WSS) अणु
		हाल OSF_WSS_PLAIN:
			अगर (f->wss.val == 0 || ctx->winकरोw == f->wss.val)
				fmatch = FMATCH_OK;
			अवरोध;
		हाल OSF_WSS_MSS:
			/*
			 * Some smart modems decrease mangle MSS to
			 * SMART_MSS_2, so we check standard, decreased
			 * and the one provided in the fingerprपूर्णांक MSS
			 * values.
			 */
#घोषणा SMART_MSS_1	1460
#घोषणा SMART_MSS_2	1448
			अगर (ctx->winकरोw == f->wss.val * mss ||
			    ctx->winकरोw == f->wss.val * SMART_MSS_1 ||
			    ctx->winकरोw == f->wss.val * SMART_MSS_2)
				fmatch = FMATCH_OK;
			अवरोध;
		हाल OSF_WSS_MTU:
			अगर (ctx->winकरोw == f->wss.val * (mss + 40) ||
			    ctx->winकरोw == f->wss.val * (SMART_MSS_1 + 40) ||
			    ctx->winकरोw == f->wss.val * (SMART_MSS_2 + 40))
				fmatch = FMATCH_OK;
			अवरोध;
		हाल OSF_WSS_MODULO:
			अगर ((ctx->winकरोw % f->wss.val) == 0)
				fmatch = FMATCH_OK;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (fmatch != FMATCH_OK)
		ctx->optp = optpinit;

	वापस fmatch == FMATCH_OK;
पूर्ण

अटल स्थिर काष्ठा tcphdr *nf_osf_hdr_ctx_init(काष्ठा nf_osf_hdr_ctx *ctx,
						स्थिर काष्ठा sk_buff *skb,
						स्थिर काष्ठा iphdr *ip,
						अचिन्हित अक्षर *opts,
						काष्ठा tcphdr *_tcph)
अणु
	स्थिर काष्ठा tcphdr *tcp;

	tcp = skb_header_poपूर्णांकer(skb, ip_hdrlen(skb), माप(काष्ठा tcphdr), _tcph);
	अगर (!tcp)
		वापस शून्य;

	अगर (!tcp->syn)
		वापस शून्य;

	ctx->totlen = ntohs(ip->tot_len);
	ctx->df = ntohs(ip->frag_off) & IP_DF;
	ctx->winकरोw = ntohs(tcp->winकरोw);

	अगर (tcp->करोff * 4 > माप(काष्ठा tcphdr)) अणु
		ctx->optsize = tcp->करोff * 4 - माप(काष्ठा tcphdr);

		ctx->optp = skb_header_poपूर्णांकer(skb, ip_hdrlen(skb) +
				माप(काष्ठा tcphdr), ctx->optsize, opts);
		अगर (!ctx->optp)
			वापस शून्य;
	पूर्ण

	वापस tcp;
पूर्ण

bool
nf_osf_match(स्थिर काष्ठा sk_buff *skb, u_पूर्णांक8_t family,
	     पूर्णांक hooknum, काष्ठा net_device *in, काष्ठा net_device *out,
	     स्थिर काष्ठा nf_osf_info *info, काष्ठा net *net,
	     स्थिर काष्ठा list_head *nf_osf_fingers)
अणु
	स्थिर काष्ठा iphdr *ip = ip_hdr(skb);
	स्थिर काष्ठा nf_osf_user_finger *f;
	अचिन्हित अक्षर opts[MAX_IPOPTLEN];
	स्थिर काष्ठा nf_osf_finger *kf;
	पूर्णांक fcount = 0, ttl_check;
	पूर्णांक fmatch = FMATCH_WRONG;
	काष्ठा nf_osf_hdr_ctx ctx;
	स्थिर काष्ठा tcphdr *tcp;
	काष्ठा tcphdr _tcph;

	स_रखो(&ctx, 0, माप(ctx));

	tcp = nf_osf_hdr_ctx_init(&ctx, skb, ip, opts, &_tcph);
	अगर (!tcp)
		वापस false;

	ttl_check = (info->flags & NF_OSF_TTL) ? info->ttl : 0;

	list_क्रम_each_entry_rcu(kf, &nf_osf_fingers[ctx.df], finger_entry) अणु

		f = &kf->finger;

		अगर (!(info->flags & NF_OSF_LOG) && म_भेद(info->genre, f->genre))
			जारी;

		अगर (!nf_osf_match_one(skb, f, ttl_check, &ctx))
			जारी;

		fmatch = FMATCH_OK;

		fcount++;

		अगर (info->flags & NF_OSF_LOG)
			nf_log_packet(net, family, hooknum, skb,
				      in, out, शून्य,
				      "%s [%s:%s] : %pI4:%d -> %pI4:%d hops=%d\n",
				      f->genre, f->version, f->subtype,
				      &ip->saddr, ntohs(tcp->source),
				      &ip->daddr, ntohs(tcp->dest),
				      f->ttl - ip->ttl);

		अगर ((info->flags & NF_OSF_LOG) &&
		    info->loglevel == NF_OSF_LOGLEVEL_FIRST)
			अवरोध;
	पूर्ण

	अगर (!fcount && (info->flags & NF_OSF_LOG))
		nf_log_packet(net, family, hooknum, skb, in, out, शून्य,
			      "Remote OS is not known: %pI4:%u -> %pI4:%u\n",
			      &ip->saddr, ntohs(tcp->source),
			      &ip->daddr, ntohs(tcp->dest));

	अगर (fcount)
		fmatch = FMATCH_OK;

	वापस fmatch == FMATCH_OK;
पूर्ण
EXPORT_SYMBOL_GPL(nf_osf_match);

bool nf_osf_find(स्थिर काष्ठा sk_buff *skb,
		 स्थिर काष्ठा list_head *nf_osf_fingers,
		 स्थिर पूर्णांक ttl_check, काष्ठा nf_osf_data *data)
अणु
	स्थिर काष्ठा iphdr *ip = ip_hdr(skb);
	स्थिर काष्ठा nf_osf_user_finger *f;
	अचिन्हित अक्षर opts[MAX_IPOPTLEN];
	स्थिर काष्ठा nf_osf_finger *kf;
	काष्ठा nf_osf_hdr_ctx ctx;
	स्थिर काष्ठा tcphdr *tcp;
	काष्ठा tcphdr _tcph;

	स_रखो(&ctx, 0, माप(ctx));

	tcp = nf_osf_hdr_ctx_init(&ctx, skb, ip, opts, &_tcph);
	अगर (!tcp)
		वापस false;

	list_क्रम_each_entry_rcu(kf, &nf_osf_fingers[ctx.df], finger_entry) अणु
		f = &kf->finger;
		अगर (!nf_osf_match_one(skb, f, ttl_check, &ctx))
			जारी;

		data->genre = f->genre;
		data->version = f->version;
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(nf_osf_find);

अटल स्थिर काष्ठा nla_policy nfnl_osf_policy[OSF_ATTR_MAX + 1] = अणु
	[OSF_ATTR_FINGER]	= अणु .len = माप(काष्ठा nf_osf_user_finger) पूर्ण,
पूर्ण;

अटल पूर्णांक nfnl_osf_add_callback(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा nfnl_info *info,
				 स्थिर काष्ठा nlattr * स्थिर osf_attrs[])
अणु
	काष्ठा nf_osf_user_finger *f;
	काष्ठा nf_osf_finger *kf = शून्य, *sf;
	पूर्णांक err = 0;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!osf_attrs[OSF_ATTR_FINGER])
		वापस -EINVAL;

	अगर (!(info->nlh->nlmsg_flags & NLM_F_CREATE))
		वापस -EINVAL;

	f = nla_data(osf_attrs[OSF_ATTR_FINGER]);

	kf = kदो_स्मृति(माप(काष्ठा nf_osf_finger), GFP_KERNEL);
	अगर (!kf)
		वापस -ENOMEM;

	स_नकल(&kf->finger, f, माप(काष्ठा nf_osf_user_finger));

	list_क्रम_each_entry(sf, &nf_osf_fingers[!!f->df], finger_entry) अणु
		अगर (स_भेद(&sf->finger, f, माप(काष्ठा nf_osf_user_finger)))
			जारी;

		kमुक्त(kf);
		kf = शून्य;

		अगर (info->nlh->nlmsg_flags & NLM_F_EXCL)
			err = -EEXIST;
		अवरोध;
	पूर्ण

	/*
	 * We are रक्षित by nfnl mutex.
	 */
	अगर (kf)
		list_add_tail_rcu(&kf->finger_entry, &nf_osf_fingers[!!f->df]);

	वापस err;
पूर्ण

अटल पूर्णांक nfnl_osf_हटाओ_callback(काष्ठा sk_buff *skb,
				    स्थिर काष्ठा nfnl_info *info,
				    स्थिर काष्ठा nlattr * स्थिर osf_attrs[])
अणु
	काष्ठा nf_osf_user_finger *f;
	काष्ठा nf_osf_finger *sf;
	पूर्णांक err = -ENOENT;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!osf_attrs[OSF_ATTR_FINGER])
		वापस -EINVAL;

	f = nla_data(osf_attrs[OSF_ATTR_FINGER]);

	list_क्रम_each_entry(sf, &nf_osf_fingers[!!f->df], finger_entry) अणु
		अगर (स_भेद(&sf->finger, f, माप(काष्ठा nf_osf_user_finger)))
			जारी;

		/*
		 * We are रक्षित by nfnl mutex.
		 */
		list_del_rcu(&sf->finger_entry);
		kमुक्त_rcu(sf, rcu_head);

		err = 0;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा nfnl_callback nfnl_osf_callbacks[OSF_MSG_MAX] = अणु
	[OSF_MSG_ADD]	= अणु
		.call		= nfnl_osf_add_callback,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= OSF_ATTR_MAX,
		.policy		= nfnl_osf_policy,
	पूर्ण,
	[OSF_MSG_REMOVE]	= अणु
		.call		= nfnl_osf_हटाओ_callback,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= OSF_ATTR_MAX,
		.policy		= nfnl_osf_policy,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nfnetlink_subप्रणाली nfnl_osf_subsys = अणु
	.name			= "osf",
	.subsys_id		= NFNL_SUBSYS_OSF,
	.cb_count		= OSF_MSG_MAX,
	.cb			= nfnl_osf_callbacks,
पूर्ण;

अटल पूर्णांक __init nfnl_osf_init(व्योम)
अणु
	पूर्णांक err = -EINVAL;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nf_osf_fingers); ++i)
		INIT_LIST_HEAD(&nf_osf_fingers[i]);

	err = nfnetlink_subsys_रेजिस्टर(&nfnl_osf_subsys);
	अगर (err < 0) अणु
		pr_err("Failed to register OSF nsfnetlink helper (%d)\n", err);
		जाओ err_out_निकास;
	पूर्ण
	वापस 0;

err_out_निकास:
	वापस err;
पूर्ण

अटल व्योम __निकास nfnl_osf_fini(व्योम)
अणु
	काष्ठा nf_osf_finger *f;
	पूर्णांक i;

	nfnetlink_subsys_unरेजिस्टर(&nfnl_osf_subsys);

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < ARRAY_SIZE(nf_osf_fingers); ++i) अणु
		list_क्रम_each_entry_rcu(f, &nf_osf_fingers[i], finger_entry) अणु
			list_del_rcu(&f->finger_entry);
			kमुक्त_rcu(f, rcu_head);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	rcu_barrier();
पूर्ण

module_init(nfnl_osf_init);
module_निकास(nfnl_osf_fini);

MODULE_LICENSE("GPL");
