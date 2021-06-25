<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Crypto user configuration API.
 *
 * Copyright (C) 2011 secunet Security Networks AG
 * Copyright (C) 2011 Steffen Klनिश्चित <steffen.klनिश्चित@secunet.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/crypto.h>
#समावेश <linux/cryptouser.h>
#समावेश <linux/sched.h>
#समावेश <linux/security.h>
#समावेश <net/netlink.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/पूर्णांकernal/rng.h>
#समावेश <crypto/akcipher.h>
#समावेश <crypto/kpp.h>
#समावेश <crypto/पूर्णांकernal/cryptouser.h>

#समावेश "internal.h"

#घोषणा null_terminated(x)	(strnlen(x, माप(x)) < माप(x))

अटल DEFINE_MUTEX(crypto_cfg_mutex);

काष्ठा crypto_dump_info अणु
	काष्ठा sk_buff *in_skb;
	काष्ठा sk_buff *out_skb;
	u32 nlmsg_seq;
	u16 nlmsg_flags;
पूर्ण;

काष्ठा crypto_alg *crypto_alg_match(काष्ठा crypto_user_alg *p, पूर्णांक exact)
अणु
	काष्ठा crypto_alg *q, *alg = शून्य;

	करोwn_पढ़ो(&crypto_alg_sem);

	list_क्रम_each_entry(q, &crypto_alg_list, cra_list) अणु
		पूर्णांक match = 0;

		अगर (crypto_is_larval(q))
			जारी;

		अगर ((q->cra_flags ^ p->cru_type) & p->cru_mask)
			जारी;

		अगर (म_माप(p->cru_driver_name))
			match = !म_भेद(q->cra_driver_name,
					p->cru_driver_name);
		अन्यथा अगर (!exact)
			match = !म_भेद(q->cra_name, p->cru_name);

		अगर (!match)
			जारी;

		अगर (unlikely(!crypto_mod_get(q)))
			जारी;

		alg = q;
		अवरोध;
	पूर्ण

	up_पढ़ो(&crypto_alg_sem);

	वापस alg;
पूर्ण

अटल पूर्णांक crypto_report_cipher(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_report_cipher rcipher;

	स_रखो(&rcipher, 0, माप(rcipher));

	strscpy(rcipher.type, "cipher", माप(rcipher.type));

	rcipher.blocksize = alg->cra_blocksize;
	rcipher.min_keysize = alg->cra_cipher.cia_min_keysize;
	rcipher.max_keysize = alg->cra_cipher.cia_max_keysize;

	वापस nla_put(skb, CRYPTOCFGA_REPORT_CIPHER,
		       माप(rcipher), &rcipher);
पूर्ण

अटल पूर्णांक crypto_report_comp(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_report_comp rcomp;

	स_रखो(&rcomp, 0, माप(rcomp));

	strscpy(rcomp.type, "compression", माप(rcomp.type));

	वापस nla_put(skb, CRYPTOCFGA_REPORT_COMPRESS, माप(rcomp), &rcomp);
पूर्ण

अटल पूर्णांक crypto_report_one(काष्ठा crypto_alg *alg,
			     काष्ठा crypto_user_alg *ualg, काष्ठा sk_buff *skb)
अणु
	स_रखो(ualg, 0, माप(*ualg));

	strscpy(ualg->cru_name, alg->cra_name, माप(ualg->cru_name));
	strscpy(ualg->cru_driver_name, alg->cra_driver_name,
		माप(ualg->cru_driver_name));
	strscpy(ualg->cru_module_name, module_name(alg->cra_module),
		माप(ualg->cru_module_name));

	ualg->cru_type = 0;
	ualg->cru_mask = 0;
	ualg->cru_flags = alg->cra_flags;
	ualg->cru_refcnt = refcount_पढ़ो(&alg->cra_refcnt);

	अगर (nla_put_u32(skb, CRYPTOCFGA_PRIORITY_VAL, alg->cra_priority))
		जाओ nla_put_failure;
	अगर (alg->cra_flags & CRYPTO_ALG_LARVAL) अणु
		काष्ठा crypto_report_larval rl;

		स_रखो(&rl, 0, माप(rl));
		strscpy(rl.type, "larval", माप(rl.type));
		अगर (nla_put(skb, CRYPTOCFGA_REPORT_LARVAL, माप(rl), &rl))
			जाओ nla_put_failure;
		जाओ out;
	पूर्ण

	अगर (alg->cra_type && alg->cra_type->report) अणु
		अगर (alg->cra_type->report(skb, alg))
			जाओ nla_put_failure;

		जाओ out;
	पूर्ण

	चयन (alg->cra_flags & (CRYPTO_ALG_TYPE_MASK | CRYPTO_ALG_LARVAL)) अणु
	हाल CRYPTO_ALG_TYPE_CIPHER:
		अगर (crypto_report_cipher(skb, alg))
			जाओ nla_put_failure;

		अवरोध;
	हाल CRYPTO_ALG_TYPE_COMPRESS:
		अगर (crypto_report_comp(skb, alg))
			जाओ nla_put_failure;

		अवरोध;
	पूर्ण

out:
	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक crypto_report_alg(काष्ठा crypto_alg *alg,
			     काष्ठा crypto_dump_info *info)
अणु
	काष्ठा sk_buff *in_skb = info->in_skb;
	काष्ठा sk_buff *skb = info->out_skb;
	काष्ठा nlmsghdr *nlh;
	काष्ठा crypto_user_alg *ualg;
	पूर्णांक err = 0;

	nlh = nlmsg_put(skb, NETLINK_CB(in_skb).portid, info->nlmsg_seq,
			CRYPTO_MSG_GETALG, माप(*ualg), info->nlmsg_flags);
	अगर (!nlh) अणु
		err = -EMSGSIZE;
		जाओ out;
	पूर्ण

	ualg = nlmsg_data(nlh);

	err = crypto_report_one(alg, ualg, skb);
	अगर (err) अणु
		nlmsg_cancel(skb, nlh);
		जाओ out;
	पूर्ण

	nlmsg_end(skb, nlh);

out:
	वापस err;
पूर्ण

अटल पूर्णांक crypto_report(काष्ठा sk_buff *in_skb, काष्ठा nlmsghdr *in_nlh,
			 काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा crypto_user_alg *p = nlmsg_data(in_nlh);
	काष्ठा crypto_alg *alg;
	काष्ठा sk_buff *skb;
	काष्ठा crypto_dump_info info;
	पूर्णांक err;

	अगर (!null_terminated(p->cru_name) || !null_terminated(p->cru_driver_name))
		वापस -EINVAL;

	alg = crypto_alg_match(p, 0);
	अगर (!alg)
		वापस -ENOENT;

	err = -ENOMEM;
	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!skb)
		जाओ drop_alg;

	info.in_skb = in_skb;
	info.out_skb = skb;
	info.nlmsg_seq = in_nlh->nlmsg_seq;
	info.nlmsg_flags = 0;

	err = crypto_report_alg(alg, &info);

drop_alg:
	crypto_mod_put(alg);

	अगर (err) अणु
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण

	वापस nlmsg_unicast(net->crypto_nlsk, skb, NETLINK_CB(in_skb).portid);
पूर्ण

अटल पूर्णांक crypto_dump_report(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	स्थिर माप_प्रकार start_pos = cb->args[0];
	माप_प्रकार pos = 0;
	काष्ठा crypto_dump_info info;
	काष्ठा crypto_alg *alg;
	पूर्णांक res;

	info.in_skb = cb->skb;
	info.out_skb = skb;
	info.nlmsg_seq = cb->nlh->nlmsg_seq;
	info.nlmsg_flags = NLM_F_MULTI;

	करोwn_पढ़ो(&crypto_alg_sem);
	list_क्रम_each_entry(alg, &crypto_alg_list, cra_list) अणु
		अगर (pos >= start_pos) अणु
			res = crypto_report_alg(alg, &info);
			अगर (res == -EMSGSIZE)
				अवरोध;
			अगर (res)
				जाओ out;
		पूर्ण
		pos++;
	पूर्ण
	cb->args[0] = pos;
	res = skb->len;
out:
	up_पढ़ो(&crypto_alg_sem);
	वापस res;
पूर्ण

अटल पूर्णांक crypto_dump_report_करोne(काष्ठा netlink_callback *cb)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक crypto_update_alg(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			     काष्ठा nlattr **attrs)
अणु
	काष्ठा crypto_alg *alg;
	काष्ठा crypto_user_alg *p = nlmsg_data(nlh);
	काष्ठा nlattr *priority = attrs[CRYPTOCFGA_PRIORITY_VAL];
	LIST_HEAD(list);

	अगर (!netlink_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!null_terminated(p->cru_name) || !null_terminated(p->cru_driver_name))
		वापस -EINVAL;

	अगर (priority && !म_माप(p->cru_driver_name))
		वापस -EINVAL;

	alg = crypto_alg_match(p, 1);
	अगर (!alg)
		वापस -ENOENT;

	करोwn_ग_लिखो(&crypto_alg_sem);

	crypto_हटाओ_spawns(alg, &list, शून्य);

	अगर (priority)
		alg->cra_priority = nla_get_u32(priority);

	up_ग_लिखो(&crypto_alg_sem);

	crypto_mod_put(alg);
	crypto_हटाओ_final(&list);

	वापस 0;
पूर्ण

अटल पूर्णांक crypto_del_alg(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			  काष्ठा nlattr **attrs)
अणु
	काष्ठा crypto_alg *alg;
	काष्ठा crypto_user_alg *p = nlmsg_data(nlh);
	पूर्णांक err;

	अगर (!netlink_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!null_terminated(p->cru_name) || !null_terminated(p->cru_driver_name))
		वापस -EINVAL;

	alg = crypto_alg_match(p, 1);
	अगर (!alg)
		वापस -ENOENT;

	/* We can not unरेजिस्टर core algorithms such as aes-generic.
	 * We would loose the reference in the crypto_alg_list to this algorithm
	 * अगर we try to unरेजिस्टर. Unरेजिस्टरing such an algorithm without
	 * removing the module is not possible, so we restrict to crypto
	 * instances that are build from ढाँचाs. */
	err = -EINVAL;
	अगर (!(alg->cra_flags & CRYPTO_ALG_INSTANCE))
		जाओ drop_alg;

	err = -EBUSY;
	अगर (refcount_पढ़ो(&alg->cra_refcnt) > 2)
		जाओ drop_alg;

	crypto_unरेजिस्टर_instance((काष्ठा crypto_instance *)alg);
	err = 0;

drop_alg:
	crypto_mod_put(alg);
	वापस err;
पूर्ण

अटल पूर्णांक crypto_add_alg(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			  काष्ठा nlattr **attrs)
अणु
	पूर्णांक exact = 0;
	स्थिर अक्षर *name;
	काष्ठा crypto_alg *alg;
	काष्ठा crypto_user_alg *p = nlmsg_data(nlh);
	काष्ठा nlattr *priority = attrs[CRYPTOCFGA_PRIORITY_VAL];

	अगर (!netlink_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!null_terminated(p->cru_name) || !null_terminated(p->cru_driver_name))
		वापस -EINVAL;

	अगर (म_माप(p->cru_driver_name))
		exact = 1;

	अगर (priority && !exact)
		वापस -EINVAL;

	alg = crypto_alg_match(p, exact);
	अगर (alg) अणु
		crypto_mod_put(alg);
		वापस -EEXIST;
	पूर्ण

	अगर (म_माप(p->cru_driver_name))
		name = p->cru_driver_name;
	अन्यथा
		name = p->cru_name;

	alg = crypto_alg_mod_lookup(name, p->cru_type, p->cru_mask);
	अगर (IS_ERR(alg))
		वापस PTR_ERR(alg);

	करोwn_ग_लिखो(&crypto_alg_sem);

	अगर (priority)
		alg->cra_priority = nla_get_u32(priority);

	up_ग_लिखो(&crypto_alg_sem);

	crypto_mod_put(alg);

	वापस 0;
पूर्ण

अटल पूर्णांक crypto_del_rng(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			  काष्ठा nlattr **attrs)
अणु
	अगर (!netlink_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;
	वापस crypto_del_शेष_rng();
पूर्ण

#घोषणा MSGSIZE(type) माप(काष्ठा type)

अटल स्थिर पूर्णांक crypto_msg_min[CRYPTO_NR_MSGTYPES] = अणु
	[CRYPTO_MSG_NEWALG	- CRYPTO_MSG_BASE] = MSGSIZE(crypto_user_alg),
	[CRYPTO_MSG_DELALG	- CRYPTO_MSG_BASE] = MSGSIZE(crypto_user_alg),
	[CRYPTO_MSG_UPDATEALG	- CRYPTO_MSG_BASE] = MSGSIZE(crypto_user_alg),
	[CRYPTO_MSG_GETALG	- CRYPTO_MSG_BASE] = MSGSIZE(crypto_user_alg),
	[CRYPTO_MSG_DELRNG	- CRYPTO_MSG_BASE] = 0,
	[CRYPTO_MSG_GETSTAT	- CRYPTO_MSG_BASE] = MSGSIZE(crypto_user_alg),
पूर्ण;

अटल स्थिर काष्ठा nla_policy crypto_policy[CRYPTOCFGA_MAX+1] = अणु
	[CRYPTOCFGA_PRIORITY_VAL]   = अणु .type = NLA_U32पूर्ण,
पूर्ण;

#अघोषित MSGSIZE

अटल स्थिर काष्ठा crypto_link अणु
	पूर्णांक (*करोit)(काष्ठा sk_buff *, काष्ठा nlmsghdr *, काष्ठा nlattr **);
	पूर्णांक (*dump)(काष्ठा sk_buff *, काष्ठा netlink_callback *);
	पूर्णांक (*करोne)(काष्ठा netlink_callback *);
पूर्ण crypto_dispatch[CRYPTO_NR_MSGTYPES] = अणु
	[CRYPTO_MSG_NEWALG	- CRYPTO_MSG_BASE] = अणु .करोit = crypto_add_algपूर्ण,
	[CRYPTO_MSG_DELALG	- CRYPTO_MSG_BASE] = अणु .करोit = crypto_del_algपूर्ण,
	[CRYPTO_MSG_UPDATEALG	- CRYPTO_MSG_BASE] = अणु .करोit = crypto_update_algपूर्ण,
	[CRYPTO_MSG_GETALG	- CRYPTO_MSG_BASE] = अणु .करोit = crypto_report,
						       .dump = crypto_dump_report,
						       .करोne = crypto_dump_report_करोneपूर्ण,
	[CRYPTO_MSG_DELRNG	- CRYPTO_MSG_BASE] = अणु .करोit = crypto_del_rng पूर्ण,
	[CRYPTO_MSG_GETSTAT	- CRYPTO_MSG_BASE] = अणु .करोit = crypto_reportstatपूर्ण,
पूर्ण;

अटल पूर्णांक crypto_user_rcv_msg(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr *attrs[CRYPTOCFGA_MAX+1];
	स्थिर काष्ठा crypto_link *link;
	पूर्णांक type, err;

	type = nlh->nlmsg_type;
	अगर (type > CRYPTO_MSG_MAX)
		वापस -EINVAL;

	type -= CRYPTO_MSG_BASE;
	link = &crypto_dispatch[type];

	अगर ((type == (CRYPTO_MSG_GETALG - CRYPTO_MSG_BASE) &&
	    (nlh->nlmsg_flags & NLM_F_DUMP))) अणु
		काष्ठा crypto_alg *alg;
		अचिन्हित दीर्घ dump_alloc = 0;

		अगर (link->dump == शून्य)
			वापस -EINVAL;

		करोwn_पढ़ो(&crypto_alg_sem);
		list_क्रम_each_entry(alg, &crypto_alg_list, cra_list)
			dump_alloc += CRYPTO_REPORT_MAXSIZE;
		up_पढ़ो(&crypto_alg_sem);

		अणु
			काष्ठा netlink_dump_control c = अणु
				.dump = link->dump,
				.करोne = link->करोne,
				.min_dump_alloc = min(dump_alloc, 65535UL),
			पूर्ण;
			err = netlink_dump_start(net->crypto_nlsk, skb, nlh, &c);
		पूर्ण

		वापस err;
	पूर्ण

	err = nlmsg_parse_deprecated(nlh, crypto_msg_min[type], attrs,
				     CRYPTOCFGA_MAX, crypto_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (link->करोit == शून्य)
		वापस -EINVAL;

	वापस link->करोit(skb, nlh, attrs);
पूर्ण

अटल व्योम crypto_netlink_rcv(काष्ठा sk_buff *skb)
अणु
	mutex_lock(&crypto_cfg_mutex);
	netlink_rcv_skb(skb, &crypto_user_rcv_msg);
	mutex_unlock(&crypto_cfg_mutex);
पूर्ण

अटल पूर्णांक __net_init crypto_netlink_init(काष्ठा net *net)
अणु
	काष्ठा netlink_kernel_cfg cfg = अणु
		.input	= crypto_netlink_rcv,
	पूर्ण;

	net->crypto_nlsk = netlink_kernel_create(net, NETLINK_CRYPTO, &cfg);
	वापस net->crypto_nlsk == शून्य ? -ENOMEM : 0;
पूर्ण

अटल व्योम __net_निकास crypto_netlink_निकास(काष्ठा net *net)
अणु
	netlink_kernel_release(net->crypto_nlsk);
	net->crypto_nlsk = शून्य;
पूर्ण

अटल काष्ठा pernet_operations crypto_netlink_net_ops = अणु
	.init = crypto_netlink_init,
	.निकास = crypto_netlink_निकास,
पूर्ण;

अटल पूर्णांक __init crypto_user_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&crypto_netlink_net_ops);
पूर्ण

अटल व्योम __निकास crypto_user_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&crypto_netlink_net_ops);
पूर्ण

module_init(crypto_user_init);
module_निकास(crypto_user_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Steffen Klassert <steffen.klassert@secunet.com>");
MODULE_DESCRIPTION("Crypto userspace configuration API");
MODULE_ALIAS("net-pf-16-proto-21");
