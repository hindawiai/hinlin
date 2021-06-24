<शैली गुरु>
/* Netfilter messages via netlink socket. Allows क्रम user space
 * protocol helpers and general trouble making from userspace.
 *
 * (C) 2001 by Jay Schulist <jschlst@samba.org>,
 * (C) 2002-2005 by Harald Welte <laक्रमge@gnumonks.org>
 * (C) 2005-2017 by Pablo Neira Ayuso <pablo@netfilter.org>
 *
 * Initial netfilter messages via netlink development funded and
 * generally made possible by Network Robots, Inc. (www.networkrobots.com)
 *
 * Further development of this code funded by Astaro AG (http://www.astaro.com)
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/uaccess.h>
#समावेश <net/sock.h>
#समावेश <linux/init.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <net/netlink.h>
#समावेश <net/netns/generic.h>
#समावेश <linux/netfilter/nfnetlink.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harald Welte <laforge@netfilter.org>");
MODULE_ALIAS_NET_PF_PROTO(PF_NETLINK, NETLINK_NETFILTER);
MODULE_DESCRIPTION("Netfilter messages via netlink socket");

#घोषणा nfnl_dereference_रक्षित(id) \
	rcu_dereference_रक्षित(table[(id)].subsys, \
				  lockdep_nfnl_is_held((id)))

#घोषणा NFNL_MAX_ATTR_COUNT	32

अटल अचिन्हित पूर्णांक nfnetlink_pernet_id __पढ़ो_mostly;

काष्ठा nfnl_net अणु
	काष्ठा sock *nfnl;
पूर्ण;

अटल काष्ठा अणु
	काष्ठा mutex				mutex;
	स्थिर काष्ठा nfnetlink_subप्रणाली __rcu	*subsys;
पूर्ण table[NFNL_SUBSYS_COUNT];

अटल काष्ठा lock_class_key nfnl_lockdep_keys[NFNL_SUBSYS_COUNT];

अटल स्थिर अक्षर *स्थिर nfnl_lockdep_names[NFNL_SUBSYS_COUNT] = अणु
	[NFNL_SUBSYS_NONE] = "nfnl_subsys_none",
	[NFNL_SUBSYS_CTNETLINK] = "nfnl_subsys_ctnetlink",
	[NFNL_SUBSYS_CTNETLINK_EXP] = "nfnl_subsys_ctnetlink_exp",
	[NFNL_SUBSYS_QUEUE] = "nfnl_subsys_queue",
	[NFNL_SUBSYS_ULOG] = "nfnl_subsys_ulog",
	[NFNL_SUBSYS_OSF] = "nfnl_subsys_osf",
	[NFNL_SUBSYS_IPSET] = "nfnl_subsys_ipset",
	[NFNL_SUBSYS_ACCT] = "nfnl_subsys_acct",
	[NFNL_SUBSYS_CTNETLINK_TIMEOUT] = "nfnl_subsys_cttimeout",
	[NFNL_SUBSYS_CTHELPER] = "nfnl_subsys_cthelper",
	[NFNL_SUBSYS_NFTABLES] = "nfnl_subsys_nftables",
	[NFNL_SUBSYS_NFT_COMPAT] = "nfnl_subsys_nftcompat",
पूर्ण;

अटल स्थिर पूर्णांक nfnl_group2type[NFNLGRP_MAX+1] = अणु
	[NFNLGRP_CONNTRACK_NEW]		= NFNL_SUBSYS_CTNETLINK,
	[NFNLGRP_CONNTRACK_UPDATE]	= NFNL_SUBSYS_CTNETLINK,
	[NFNLGRP_CONNTRACK_DESTROY]	= NFNL_SUBSYS_CTNETLINK,
	[NFNLGRP_CONNTRACK_EXP_NEW]	= NFNL_SUBSYS_CTNETLINK_EXP,
	[NFNLGRP_CONNTRACK_EXP_UPDATE]	= NFNL_SUBSYS_CTNETLINK_EXP,
	[NFNLGRP_CONNTRACK_EXP_DESTROY] = NFNL_SUBSYS_CTNETLINK_EXP,
	[NFNLGRP_NFTABLES]		= NFNL_SUBSYS_NFTABLES,
	[NFNLGRP_ACCT_QUOTA]		= NFNL_SUBSYS_ACCT,
	[NFNLGRP_NFTRACE]		= NFNL_SUBSYS_NFTABLES,
पूर्ण;

अटल काष्ठा nfnl_net *nfnl_pernet(काष्ठा net *net)
अणु
	वापस net_generic(net, nfnetlink_pernet_id);
पूर्ण

व्योम nfnl_lock(__u8 subsys_id)
अणु
	mutex_lock(&table[subsys_id].mutex);
पूर्ण
EXPORT_SYMBOL_GPL(nfnl_lock);

व्योम nfnl_unlock(__u8 subsys_id)
अणु
	mutex_unlock(&table[subsys_id].mutex);
पूर्ण
EXPORT_SYMBOL_GPL(nfnl_unlock);

#अगर_घोषित CONFIG_PROVE_LOCKING
bool lockdep_nfnl_is_held(u8 subsys_id)
अणु
	वापस lockdep_is_held(&table[subsys_id].mutex);
पूर्ण
EXPORT_SYMBOL_GPL(lockdep_nfnl_is_held);
#पूर्ण_अगर

पूर्णांक nfnetlink_subsys_रेजिस्टर(स्थिर काष्ठा nfnetlink_subप्रणाली *n)
अणु
	u8 cb_id;

	/* Sanity-check attr_count size to aव्योम stack buffer overflow. */
	क्रम (cb_id = 0; cb_id < n->cb_count; cb_id++)
		अगर (WARN_ON(n->cb[cb_id].attr_count > NFNL_MAX_ATTR_COUNT))
			वापस -EINVAL;

	nfnl_lock(n->subsys_id);
	अगर (table[n->subsys_id].subsys) अणु
		nfnl_unlock(n->subsys_id);
		वापस -EBUSY;
	पूर्ण
	rcu_assign_poपूर्णांकer(table[n->subsys_id].subsys, n);
	nfnl_unlock(n->subsys_id);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfnetlink_subsys_रेजिस्टर);

पूर्णांक nfnetlink_subsys_unरेजिस्टर(स्थिर काष्ठा nfnetlink_subप्रणाली *n)
अणु
	nfnl_lock(n->subsys_id);
	table[n->subsys_id].subsys = शून्य;
	nfnl_unlock(n->subsys_id);
	synchronize_rcu();
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfnetlink_subsys_unरेजिस्टर);

अटल अंतरभूत स्थिर काष्ठा nfnetlink_subप्रणाली *nfnetlink_get_subsys(u16 type)
अणु
	u8 subsys_id = NFNL_SUBSYS_ID(type);

	अगर (subsys_id >= NFNL_SUBSYS_COUNT)
		वापस शून्य;

	वापस rcu_dereference(table[subsys_id].subsys);
पूर्ण

अटल अंतरभूत स्थिर काष्ठा nfnl_callback *
nfnetlink_find_client(u16 type, स्थिर काष्ठा nfnetlink_subप्रणाली *ss)
अणु
	u8 cb_id = NFNL_MSG_TYPE(type);

	अगर (cb_id >= ss->cb_count)
		वापस शून्य;

	वापस &ss->cb[cb_id];
पूर्ण

पूर्णांक nfnetlink_has_listeners(काष्ठा net *net, अचिन्हित पूर्णांक group)
अणु
	काष्ठा nfnl_net *nfnlnet = nfnl_pernet(net);

	वापस netlink_has_listeners(nfnlnet->nfnl, group);
पूर्ण
EXPORT_SYMBOL_GPL(nfnetlink_has_listeners);

पूर्णांक nfnetlink_send(काष्ठा sk_buff *skb, काष्ठा net *net, u32 portid,
		   अचिन्हित पूर्णांक group, पूर्णांक echo, gfp_t flags)
अणु
	काष्ठा nfnl_net *nfnlnet = nfnl_pernet(net);

	वापस nlmsg_notअगरy(nfnlnet->nfnl, skb, portid, group, echo, flags);
पूर्ण
EXPORT_SYMBOL_GPL(nfnetlink_send);

पूर्णांक nfnetlink_set_err(काष्ठा net *net, u32 portid, u32 group, पूर्णांक error)
अणु
	काष्ठा nfnl_net *nfnlnet = nfnl_pernet(net);

	वापस netlink_set_err(nfnlnet->nfnl, portid, group, error);
पूर्ण
EXPORT_SYMBOL_GPL(nfnetlink_set_err);

पूर्णांक nfnetlink_unicast(काष्ठा sk_buff *skb, काष्ठा net *net, u32 portid)
अणु
	काष्ठा nfnl_net *nfnlnet = nfnl_pernet(net);
	पूर्णांक err;

	err = nlmsg_unicast(nfnlnet->nfnl, skb, portid);
	अगर (err == -EAGAIN)
		err = -ENOBUFS;

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(nfnetlink_unicast);

व्योम nfnetlink_broadcast(काष्ठा net *net, काष्ठा sk_buff *skb, __u32 portid,
			 __u32 group, gfp_t allocation)
अणु
	काष्ठा nfnl_net *nfnlnet = nfnl_pernet(net);

	netlink_broadcast(nfnlnet->nfnl, skb, portid, group, allocation);
पूर्ण
EXPORT_SYMBOL_GPL(nfnetlink_broadcast);

/* Process one complete nfnetlink message. */
अटल पूर्णांक nfnetlink_rcv_msg(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	स्थिर काष्ठा nfnl_callback *nc;
	स्थिर काष्ठा nfnetlink_subप्रणाली *ss;
	पूर्णांक type, err;

	/* All the messages must at least contain nfgenmsg */
	अगर (nlmsg_len(nlh) < माप(काष्ठा nfgenmsg))
		वापस 0;

	type = nlh->nlmsg_type;
replay:
	rcu_पढ़ो_lock();

	ss = nfnetlink_get_subsys(type);
	अगर (!ss) अणु
#अगर_घोषित CONFIG_MODULES
		rcu_पढ़ो_unlock();
		request_module("nfnetlink-subsys-%d", NFNL_SUBSYS_ID(type));
		rcu_पढ़ो_lock();
		ss = nfnetlink_get_subsys(type);
		अगर (!ss)
#पूर्ण_अगर
		अणु
			rcu_पढ़ो_unlock();
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	nc = nfnetlink_find_client(type, ss);
	अगर (!nc) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण

	अणु
		पूर्णांक min_len = nlmsg_total_size(माप(काष्ठा nfgenmsg));
		काष्ठा nfnl_net *nfnlnet = nfnl_pernet(net);
		u8 cb_id = NFNL_MSG_TYPE(nlh->nlmsg_type);
		काष्ठा nlattr *cda[NFNL_MAX_ATTR_COUNT + 1];
		काष्ठा nlattr *attr = (व्योम *)nlh + min_len;
		पूर्णांक attrlen = nlh->nlmsg_len - min_len;
		__u8 subsys_id = NFNL_SUBSYS_ID(type);
		काष्ठा nfnl_info info = अणु
			.net	= net,
			.sk	= nfnlnet->nfnl,
			.nlh	= nlh,
			.extack	= extack,
		पूर्ण;

		/* Sanity-check NFNL_MAX_ATTR_COUNT */
		अगर (ss->cb[cb_id].attr_count > NFNL_MAX_ATTR_COUNT) अणु
			rcu_पढ़ो_unlock();
			वापस -ENOMEM;
		पूर्ण

		err = nla_parse_deprecated(cda, ss->cb[cb_id].attr_count,
					   attr, attrlen,
					   ss->cb[cb_id].policy, extack);
		अगर (err < 0) अणु
			rcu_पढ़ो_unlock();
			वापस err;
		पूर्ण

		अगर (!nc->call) अणु
			rcu_पढ़ो_unlock();
			वापस -EINVAL;
		पूर्ण

		चयन (nc->type) अणु
		हाल NFNL_CB_RCU:
			err = nc->call(skb, &info, (स्थिर काष्ठा nlattr **)cda);
			rcu_पढ़ो_unlock();
			अवरोध;
		हाल NFNL_CB_MUTEX:
			rcu_पढ़ो_unlock();
			nfnl_lock(subsys_id);
			अगर (nfnl_dereference_रक्षित(subsys_id) != ss ||
			    nfnetlink_find_client(type, ss) != nc) अणु
				err = -EAGAIN;
				अवरोध;
			पूर्ण
			err = nc->call(skb, &info, (स्थिर काष्ठा nlattr **)cda);
			nfnl_unlock(subsys_id);
			अवरोध;
		शेष:
			rcu_पढ़ो_unlock();
			err = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (err == -EAGAIN)
			जाओ replay;
		वापस err;
	पूर्ण
पूर्ण

काष्ठा nfnl_err अणु
	काष्ठा list_head	head;
	काष्ठा nlmsghdr		*nlh;
	पूर्णांक			err;
	काष्ठा netlink_ext_ack	extack;
पूर्ण;

अटल पूर्णांक nfnl_err_add(काष्ठा list_head *list, काष्ठा nlmsghdr *nlh, पूर्णांक err,
			स्थिर काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nfnl_err *nfnl_err;

	nfnl_err = kदो_स्मृति(माप(काष्ठा nfnl_err), GFP_KERNEL);
	अगर (nfnl_err == शून्य)
		वापस -ENOMEM;

	nfnl_err->nlh = nlh;
	nfnl_err->err = err;
	nfnl_err->extack = *extack;
	list_add_tail(&nfnl_err->head, list);

	वापस 0;
पूर्ण

अटल व्योम nfnl_err_del(काष्ठा nfnl_err *nfnl_err)
अणु
	list_del(&nfnl_err->head);
	kमुक्त(nfnl_err);
पूर्ण

अटल व्योम nfnl_err_reset(काष्ठा list_head *err_list)
अणु
	काष्ठा nfnl_err *nfnl_err, *next;

	list_क्रम_each_entry_safe(nfnl_err, next, err_list, head)
		nfnl_err_del(nfnl_err);
पूर्ण

अटल व्योम nfnl_err_deliver(काष्ठा list_head *err_list, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfnl_err *nfnl_err, *next;

	list_क्रम_each_entry_safe(nfnl_err, next, err_list, head) अणु
		netlink_ack(skb, nfnl_err->nlh, nfnl_err->err,
			    &nfnl_err->extack);
		nfnl_err_del(nfnl_err);
	पूर्ण
पूर्ण

क्रमागत अणु
	NFNL_BATCH_FAILURE	= (1 << 0),
	NFNL_BATCH_DONE		= (1 << 1),
	NFNL_BATCH_REPLAY	= (1 << 2),
पूर्ण;

अटल व्योम nfnetlink_rcv_batch(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
				u16 subsys_id, u32 genid)
अणु
	काष्ठा sk_buff *oskb = skb;
	काष्ठा net *net = sock_net(skb->sk);
	स्थिर काष्ठा nfnetlink_subप्रणाली *ss;
	स्थिर काष्ठा nfnl_callback *nc;
	काष्ठा netlink_ext_ack extack;
	LIST_HEAD(err_list);
	u32 status;
	पूर्णांक err;

	अगर (subsys_id >= NFNL_SUBSYS_COUNT)
		वापस netlink_ack(skb, nlh, -EINVAL, शून्य);
replay:
	status = 0;
replay_पात:
	skb = netlink_skb_clone(oskb, GFP_KERNEL);
	अगर (!skb)
		वापस netlink_ack(oskb, nlh, -ENOMEM, शून्य);

	nfnl_lock(subsys_id);
	ss = nfnl_dereference_रक्षित(subsys_id);
	अगर (!ss) अणु
#अगर_घोषित CONFIG_MODULES
		nfnl_unlock(subsys_id);
		request_module("nfnetlink-subsys-%d", subsys_id);
		nfnl_lock(subsys_id);
		ss = nfnl_dereference_रक्षित(subsys_id);
		अगर (!ss)
#पूर्ण_अगर
		अणु
			nfnl_unlock(subsys_id);
			netlink_ack(oskb, nlh, -EOPNOTSUPP, शून्य);
			वापस kमुक्त_skb(skb);
		पूर्ण
	पूर्ण

	अगर (!ss->valid_genid || !ss->commit || !ss->पात) अणु
		nfnl_unlock(subsys_id);
		netlink_ack(oskb, nlh, -EOPNOTSUPP, शून्य);
		वापस kमुक्त_skb(skb);
	पूर्ण

	अगर (!try_module_get(ss->owner)) अणु
		nfnl_unlock(subsys_id);
		netlink_ack(oskb, nlh, -EOPNOTSUPP, शून्य);
		वापस kमुक्त_skb(skb);
	पूर्ण

	अगर (!ss->valid_genid(net, genid)) अणु
		module_put(ss->owner);
		nfnl_unlock(subsys_id);
		netlink_ack(oskb, nlh, -ERESTART, शून्य);
		वापस kमुक्त_skb(skb);
	पूर्ण

	nfnl_unlock(subsys_id);

	जबतक (skb->len >= nlmsg_total_size(0)) अणु
		पूर्णांक msglen, type;

		अगर (fatal_संकेत_pending(current)) अणु
			nfnl_err_reset(&err_list);
			err = -EINTR;
			status = NFNL_BATCH_FAILURE;
			जाओ करोne;
		पूर्ण

		स_रखो(&extack, 0, माप(extack));
		nlh = nlmsg_hdr(skb);
		err = 0;

		अगर (nlh->nlmsg_len < NLMSG_HDRLEN ||
		    skb->len < nlh->nlmsg_len ||
		    nlmsg_len(nlh) < माप(काष्ठा nfgenmsg)) अणु
			nfnl_err_reset(&err_list);
			status |= NFNL_BATCH_FAILURE;
			जाओ करोne;
		पूर्ण

		/* Only requests are handled by the kernel */
		अगर (!(nlh->nlmsg_flags & NLM_F_REQUEST)) अणु
			err = -EINVAL;
			जाओ ack;
		पूर्ण

		type = nlh->nlmsg_type;
		अगर (type == NFNL_MSG_BATCH_BEGIN) अणु
			/* Malक्रमmed: Batch begin twice */
			nfnl_err_reset(&err_list);
			status |= NFNL_BATCH_FAILURE;
			जाओ करोne;
		पूर्ण अन्यथा अगर (type == NFNL_MSG_BATCH_END) अणु
			status |= NFNL_BATCH_DONE;
			जाओ करोne;
		पूर्ण अन्यथा अगर (type < NLMSG_MIN_TYPE) अणु
			err = -EINVAL;
			जाओ ack;
		पूर्ण

		/* We only accept a batch with messages क्रम the same
		 * subप्रणाली.
		 */
		अगर (NFNL_SUBSYS_ID(type) != subsys_id) अणु
			err = -EINVAL;
			जाओ ack;
		पूर्ण

		nc = nfnetlink_find_client(type, ss);
		अगर (!nc) अणु
			err = -EINVAL;
			जाओ ack;
		पूर्ण

		अगर (nc->type != NFNL_CB_BATCH) अणु
			err = -EINVAL;
			जाओ ack;
		पूर्ण

		अणु
			पूर्णांक min_len = nlmsg_total_size(माप(काष्ठा nfgenmsg));
			काष्ठा nfnl_net *nfnlnet = nfnl_pernet(net);
			काष्ठा nlattr *cda[NFNL_MAX_ATTR_COUNT + 1];
			काष्ठा nlattr *attr = (व्योम *)nlh + min_len;
			u8 cb_id = NFNL_MSG_TYPE(nlh->nlmsg_type);
			पूर्णांक attrlen = nlh->nlmsg_len - min_len;
			काष्ठा nfnl_info info = अणु
				.net	= net,
				.sk	= nfnlnet->nfnl,
				.nlh	= nlh,
				.extack	= &extack,
			पूर्ण;

			/* Sanity-check NFTA_MAX_ATTR */
			अगर (ss->cb[cb_id].attr_count > NFNL_MAX_ATTR_COUNT) अणु
				err = -ENOMEM;
				जाओ ack;
			पूर्ण

			err = nla_parse_deprecated(cda,
						   ss->cb[cb_id].attr_count,
						   attr, attrlen,
						   ss->cb[cb_id].policy, शून्य);
			अगर (err < 0)
				जाओ ack;

			err = nc->call(skb, &info, (स्थिर काष्ठा nlattr **)cda);

			/* The lock was released to स्वतःload some module, we
			 * have to पात and start from scratch using the
			 * original skb.
			 */
			अगर (err == -EAGAIN) अणु
				status |= NFNL_BATCH_REPLAY;
				जाओ करोne;
			पूर्ण
		पूर्ण
ack:
		अगर (nlh->nlmsg_flags & NLM_F_ACK || err) अणु
			/* Errors are delivered once the full batch has been
			 * processed, this aव्योमs that the same error is
			 * reported several बार when replaying the batch.
			 */
			अगर (nfnl_err_add(&err_list, nlh, err, &extack) < 0) अणु
				/* We failed to enqueue an error, reset the
				 * list of errors and send OOM to userspace
				 * poपूर्णांकing to the batch header.
				 */
				nfnl_err_reset(&err_list);
				netlink_ack(oskb, nlmsg_hdr(oskb), -ENOMEM,
					    शून्य);
				status |= NFNL_BATCH_FAILURE;
				जाओ करोne;
			पूर्ण
			/* We करोn't stop processing the batch on errors, thus,
			 * userspace माला_लो all the errors that the batch
			 * triggers.
			 */
			अगर (err)
				status |= NFNL_BATCH_FAILURE;
		पूर्ण

		msglen = NLMSG_ALIGN(nlh->nlmsg_len);
		अगर (msglen > skb->len)
			msglen = skb->len;
		skb_pull(skb, msglen);
	पूर्ण
करोne:
	अगर (status & NFNL_BATCH_REPLAY) अणु
		ss->पात(net, oskb, NFNL_ABORT_AUTOLOAD);
		nfnl_err_reset(&err_list);
		kमुक्त_skb(skb);
		module_put(ss->owner);
		जाओ replay;
	पूर्ण अन्यथा अगर (status == NFNL_BATCH_DONE) अणु
		err = ss->commit(net, oskb);
		अगर (err == -EAGAIN) अणु
			status |= NFNL_BATCH_REPLAY;
			जाओ करोne;
		पूर्ण अन्यथा अगर (err) अणु
			ss->पात(net, oskb, NFNL_ABORT_NONE);
			netlink_ack(oskb, nlmsg_hdr(oskb), err, शून्य);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रमागत nfnl_पात_action पात_action;

		अगर (status & NFNL_BATCH_FAILURE)
			पात_action = NFNL_ABORT_NONE;
		अन्यथा
			पात_action = NFNL_ABORT_VALIDATE;

		err = ss->पात(net, oskb, पात_action);
		अगर (err == -EAGAIN) अणु
			nfnl_err_reset(&err_list);
			kमुक्त_skb(skb);
			module_put(ss->owner);
			status |= NFNL_BATCH_FAILURE;
			जाओ replay_पात;
		पूर्ण
	पूर्ण
	अगर (ss->cleanup)
		ss->cleanup(net);

	nfnl_err_deliver(&err_list, oskb);
	kमुक्त_skb(skb);
	module_put(ss->owner);
पूर्ण

अटल स्थिर काष्ठा nla_policy nfnl_batch_policy[NFNL_BATCH_MAX + 1] = अणु
	[NFNL_BATCH_GENID]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल व्योम nfnetlink_rcv_skb_batch(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh)
अणु
	पूर्णांक min_len = nlmsg_total_size(माप(काष्ठा nfgenmsg));
	काष्ठा nlattr *attr = (व्योम *)nlh + min_len;
	काष्ठा nlattr *cda[NFNL_BATCH_MAX + 1];
	पूर्णांक attrlen = nlh->nlmsg_len - min_len;
	काष्ठा nfgenmsg *nfgenmsg;
	पूर्णांक msglen, err;
	u32 gen_id = 0;
	u16 res_id;

	msglen = NLMSG_ALIGN(nlh->nlmsg_len);
	अगर (msglen > skb->len)
		msglen = skb->len;

	अगर (skb->len < NLMSG_HDRLEN + माप(काष्ठा nfgenmsg))
		वापस;

	err = nla_parse_deprecated(cda, NFNL_BATCH_MAX, attr, attrlen,
				   nfnl_batch_policy, शून्य);
	अगर (err < 0) अणु
		netlink_ack(skb, nlh, err, शून्य);
		वापस;
	पूर्ण
	अगर (cda[NFNL_BATCH_GENID])
		gen_id = ntohl(nla_get_be32(cda[NFNL_BATCH_GENID]));

	nfgenmsg = nlmsg_data(nlh);
	skb_pull(skb, msglen);
	/* Work around old nft using host byte order */
	अगर (nfgenmsg->res_id == NFNL_SUBSYS_NFTABLES)
		res_id = NFNL_SUBSYS_NFTABLES;
	अन्यथा
		res_id = ntohs(nfgenmsg->res_id);

	nfnetlink_rcv_batch(skb, nlh, res_id, gen_id);
पूर्ण

अटल व्योम nfnetlink_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा nlmsghdr *nlh = nlmsg_hdr(skb);

	अगर (skb->len < NLMSG_HDRLEN ||
	    nlh->nlmsg_len < NLMSG_HDRLEN ||
	    skb->len < nlh->nlmsg_len)
		वापस;

	अगर (!netlink_net_capable(skb, CAP_NET_ADMIN)) अणु
		netlink_ack(skb, nlh, -EPERM, शून्य);
		वापस;
	पूर्ण

	अगर (nlh->nlmsg_type == NFNL_MSG_BATCH_BEGIN)
		nfnetlink_rcv_skb_batch(skb, nlh);
	अन्यथा
		netlink_rcv_skb(skb, nfnetlink_rcv_msg);
पूर्ण

#अगर_घोषित CONFIG_MODULES
अटल पूर्णांक nfnetlink_bind(काष्ठा net *net, पूर्णांक group)
अणु
	स्थिर काष्ठा nfnetlink_subप्रणाली *ss;
	पूर्णांक type;

	अगर (group <= NFNLGRP_NONE || group > NFNLGRP_MAX)
		वापस 0;

	type = nfnl_group2type[group];

	rcu_पढ़ो_lock();
	ss = nfnetlink_get_subsys(type << 8);
	rcu_पढ़ो_unlock();
	अगर (!ss)
		request_module_noरुको("nfnetlink-subsys-%d", type);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __net_init nfnetlink_net_init(काष्ठा net *net)
अणु
	काष्ठा nfnl_net *nfnlnet = nfnl_pernet(net);
	काष्ठा netlink_kernel_cfg cfg = अणु
		.groups	= NFNLGRP_MAX,
		.input	= nfnetlink_rcv,
#अगर_घोषित CONFIG_MODULES
		.bind	= nfnetlink_bind,
#पूर्ण_अगर
	पूर्ण;

	nfnlnet->nfnl = netlink_kernel_create(net, NETLINK_NETFILTER, &cfg);
	अगर (!nfnlnet->nfnl)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास nfnetlink_net_निकास_batch(काष्ठा list_head *net_निकास_list)
अणु
	काष्ठा nfnl_net *nfnlnet;
	काष्ठा net *net;

	list_क्रम_each_entry(net, net_निकास_list, निकास_list) अणु
		nfnlnet = nfnl_pernet(net);

		netlink_kernel_release(nfnlnet->nfnl);
	पूर्ण
पूर्ण

अटल काष्ठा pernet_operations nfnetlink_net_ops = अणु
	.init		= nfnetlink_net_init,
	.निकास_batch	= nfnetlink_net_निकास_batch,
	.id		= &nfnetlink_pernet_id,
	.size		= माप(काष्ठा nfnl_net),
पूर्ण;

अटल पूर्णांक __init nfnetlink_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = NFNLGRP_NONE + 1; i <= NFNLGRP_MAX; i++)
		BUG_ON(nfnl_group2type[i] == NFNL_SUBSYS_NONE);

	क्रम (i=0; i<NFNL_SUBSYS_COUNT; i++)
		__mutex_init(&table[i].mutex, nfnl_lockdep_names[i], &nfnl_lockdep_keys[i]);

	वापस रेजिस्टर_pernet_subsys(&nfnetlink_net_ops);
पूर्ण

अटल व्योम __निकास nfnetlink_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&nfnetlink_net_ops);
पूर्ण
module_init(nfnetlink_init);
module_निकास(nfnetlink_निकास);
