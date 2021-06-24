<शैली गुरु>
/* License: GPL */

#समावेश <linux/mutex.h>
#समावेश <linux/socket.h>
#समावेश <linux/skbuff.h>
#समावेश <net/netlink.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/module.h>
#समावेश <net/sock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/tcp.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/nospec.h>
#समावेश <linux/cookie.h>
#समावेश <linux/inet_diag.h>
#समावेश <linux/sock_diag.h>

अटल स्थिर काष्ठा sock_diag_handler *sock_diag_handlers[AF_MAX];
अटल पूर्णांक (*inet_rcv_compat)(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh);
अटल DEFINE_MUTEX(sock_diag_table_mutex);
अटल काष्ठा workqueue_काष्ठा *broadcast_wq;

DEFINE_COOKIE(sock_cookie);

u64 __sock_gen_cookie(काष्ठा sock *sk)
अणु
	जबतक (1) अणु
		u64 res = atomic64_पढ़ो(&sk->sk_cookie);

		अगर (res)
			वापस res;
		res = gen_cookie_next(&sock_cookie);
		atomic64_cmpxchg(&sk->sk_cookie, 0, res);
	पूर्ण
पूर्ण

पूर्णांक sock_diag_check_cookie(काष्ठा sock *sk, स्थिर __u32 *cookie)
अणु
	u64 res;

	अगर (cookie[0] == INET_DIAG_NOCOOKIE && cookie[1] == INET_DIAG_NOCOOKIE)
		वापस 0;

	res = sock_gen_cookie(sk);
	अगर ((u32)res != cookie[0] || (u32)(res >> 32) != cookie[1])
		वापस -ESTALE;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sock_diag_check_cookie);

व्योम sock_diag_save_cookie(काष्ठा sock *sk, __u32 *cookie)
अणु
	u64 res = sock_gen_cookie(sk);

	cookie[0] = (u32)res;
	cookie[1] = (u32)(res >> 32);
पूर्ण
EXPORT_SYMBOL_GPL(sock_diag_save_cookie);

पूर्णांक sock_diag_put_meminfo(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक attrtype)
अणु
	u32 mem[SK_MEMINFO_VARS];

	sk_get_meminfo(sk, mem);

	वापस nla_put(skb, attrtype, माप(mem), &mem);
पूर्ण
EXPORT_SYMBOL_GPL(sock_diag_put_meminfo);

पूर्णांक sock_diag_put_filterinfo(bool may_report_filterinfo, काष्ठा sock *sk,
			     काष्ठा sk_buff *skb, पूर्णांक attrtype)
अणु
	काष्ठा sock_fprog_kern *fprog;
	काष्ठा sk_filter *filter;
	काष्ठा nlattr *attr;
	अचिन्हित पूर्णांक flen;
	पूर्णांक err = 0;

	अगर (!may_report_filterinfo) अणु
		nla_reserve(skb, attrtype, 0);
		वापस 0;
	पूर्ण

	rcu_पढ़ो_lock();
	filter = rcu_dereference(sk->sk_filter);
	अगर (!filter)
		जाओ out;

	fprog = filter->prog->orig_prog;
	अगर (!fprog)
		जाओ out;

	flen = bpf_classic_proglen(fprog);

	attr = nla_reserve(skb, attrtype, flen);
	अगर (attr == शून्य) अणु
		err = -EMSGSIZE;
		जाओ out;
	पूर्ण

	स_नकल(nla_data(attr), fprog->filter, flen);
out:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL(sock_diag_put_filterinfo);

काष्ठा broadcast_sk अणु
	काष्ठा sock *sk;
	काष्ठा work_काष्ठा work;
पूर्ण;

अटल माप_प्रकार sock_diag_nlmsg_size(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा inet_diag_msg)
	       + nla_total_size(माप(u8)) /* INET_DIAG_PROTOCOL */
	       + nla_total_size_64bit(माप(काष्ठा tcp_info))); /* INET_DIAG_INFO */
पूर्ण

अटल व्योम sock_diag_broadcast_destroy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा broadcast_sk *bsk =
		container_of(work, काष्ठा broadcast_sk, work);
	काष्ठा sock *sk = bsk->sk;
	स्थिर काष्ठा sock_diag_handler *hndl;
	काष्ठा sk_buff *skb;
	स्थिर क्रमागत sknetlink_groups group = sock_diag_destroy_group(sk);
	पूर्णांक err = -1;

	WARN_ON(group == SKNLGRP_NONE);

	skb = nlmsg_new(sock_diag_nlmsg_size(), GFP_KERNEL);
	अगर (!skb)
		जाओ out;

	mutex_lock(&sock_diag_table_mutex);
	hndl = sock_diag_handlers[sk->sk_family];
	अगर (hndl && hndl->get_info)
		err = hndl->get_info(skb, sk);
	mutex_unlock(&sock_diag_table_mutex);

	अगर (!err)
		nlmsg_multicast(sock_net(sk)->diag_nlsk, skb, 0, group,
				GFP_KERNEL);
	अन्यथा
		kमुक्त_skb(skb);
out:
	sk_deकाष्ठा(sk);
	kमुक्त(bsk);
पूर्ण

व्योम sock_diag_broadcast_destroy(काष्ठा sock *sk)
अणु
	/* Note, this function is often called from an पूर्णांकerrupt context. */
	काष्ठा broadcast_sk *bsk =
		kदो_स्मृति(माप(काष्ठा broadcast_sk), GFP_ATOMIC);
	अगर (!bsk)
		वापस sk_deकाष्ठा(sk);
	bsk->sk = sk;
	INIT_WORK(&bsk->work, sock_diag_broadcast_destroy_work);
	queue_work(broadcast_wq, &bsk->work);
पूर्ण

व्योम sock_diag_रेजिस्टर_inet_compat(पूर्णांक (*fn)(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh))
अणु
	mutex_lock(&sock_diag_table_mutex);
	inet_rcv_compat = fn;
	mutex_unlock(&sock_diag_table_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(sock_diag_रेजिस्टर_inet_compat);

व्योम sock_diag_unरेजिस्टर_inet_compat(पूर्णांक (*fn)(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh))
अणु
	mutex_lock(&sock_diag_table_mutex);
	inet_rcv_compat = शून्य;
	mutex_unlock(&sock_diag_table_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(sock_diag_unरेजिस्टर_inet_compat);

पूर्णांक sock_diag_रेजिस्टर(स्थिर काष्ठा sock_diag_handler *hndl)
अणु
	पूर्णांक err = 0;

	अगर (hndl->family >= AF_MAX)
		वापस -EINVAL;

	mutex_lock(&sock_diag_table_mutex);
	अगर (sock_diag_handlers[hndl->family])
		err = -EBUSY;
	अन्यथा
		sock_diag_handlers[hndl->family] = hndl;
	mutex_unlock(&sock_diag_table_mutex);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(sock_diag_रेजिस्टर);

व्योम sock_diag_unरेजिस्टर(स्थिर काष्ठा sock_diag_handler *hnld)
अणु
	पूर्णांक family = hnld->family;

	अगर (family >= AF_MAX)
		वापस;

	mutex_lock(&sock_diag_table_mutex);
	BUG_ON(sock_diag_handlers[family] != hnld);
	sock_diag_handlers[family] = शून्य;
	mutex_unlock(&sock_diag_table_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(sock_diag_unरेजिस्टर);

अटल पूर्णांक __sock_diag_cmd(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh)
अणु
	पूर्णांक err;
	काष्ठा sock_diag_req *req = nlmsg_data(nlh);
	स्थिर काष्ठा sock_diag_handler *hndl;

	अगर (nlmsg_len(nlh) < माप(*req))
		वापस -EINVAL;

	अगर (req->sdiag_family >= AF_MAX)
		वापस -EINVAL;
	req->sdiag_family = array_index_nospec(req->sdiag_family, AF_MAX);

	अगर (sock_diag_handlers[req->sdiag_family] == शून्य)
		sock_load_diag_module(req->sdiag_family, 0);

	mutex_lock(&sock_diag_table_mutex);
	hndl = sock_diag_handlers[req->sdiag_family];
	अगर (hndl == शून्य)
		err = -ENOENT;
	अन्यथा अगर (nlh->nlmsg_type == SOCK_DIAG_BY_FAMILY)
		err = hndl->dump(skb, nlh);
	अन्यथा अगर (nlh->nlmsg_type == SOCK_DESTROY && hndl->destroy)
		err = hndl->destroy(skb, nlh);
	अन्यथा
		err = -EOPNOTSUPP;
	mutex_unlock(&sock_diag_table_mutex);

	वापस err;
पूर्ण

अटल पूर्णांक sock_diag_rcv_msg(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक ret;

	चयन (nlh->nlmsg_type) अणु
	हाल TCPDIAG_GETSOCK:
	हाल DCCPDIAG_GETSOCK:
		अगर (inet_rcv_compat == शून्य)
			sock_load_diag_module(AF_INET, 0);

		mutex_lock(&sock_diag_table_mutex);
		अगर (inet_rcv_compat != शून्य)
			ret = inet_rcv_compat(skb, nlh);
		अन्यथा
			ret = -EOPNOTSUPP;
		mutex_unlock(&sock_diag_table_mutex);

		वापस ret;
	हाल SOCK_DIAG_BY_FAMILY:
	हाल SOCK_DESTROY:
		वापस __sock_diag_cmd(skb, nlh);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल DEFINE_MUTEX(sock_diag_mutex);

अटल व्योम sock_diag_rcv(काष्ठा sk_buff *skb)
अणु
	mutex_lock(&sock_diag_mutex);
	netlink_rcv_skb(skb, &sock_diag_rcv_msg);
	mutex_unlock(&sock_diag_mutex);
पूर्ण

अटल पूर्णांक sock_diag_bind(काष्ठा net *net, पूर्णांक group)
अणु
	चयन (group) अणु
	हाल SKNLGRP_INET_TCP_DESTROY:
	हाल SKNLGRP_INET_UDP_DESTROY:
		अगर (!sock_diag_handlers[AF_INET])
			sock_load_diag_module(AF_INET, 0);
		अवरोध;
	हाल SKNLGRP_INET6_TCP_DESTROY:
	हाल SKNLGRP_INET6_UDP_DESTROY:
		अगर (!sock_diag_handlers[AF_INET6])
			sock_load_diag_module(AF_INET6, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक sock_diag_destroy(काष्ठा sock *sk, पूर्णांक err)
अणु
	अगर (!ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!sk->sk_prot->diag_destroy)
		वापस -EOPNOTSUPP;

	वापस sk->sk_prot->diag_destroy(sk, err);
पूर्ण
EXPORT_SYMBOL_GPL(sock_diag_destroy);

अटल पूर्णांक __net_init diag_net_init(काष्ठा net *net)
अणु
	काष्ठा netlink_kernel_cfg cfg = अणु
		.groups	= SKNLGRP_MAX,
		.input	= sock_diag_rcv,
		.bind	= sock_diag_bind,
		.flags	= NL_CFG_F_NONROOT_RECV,
	पूर्ण;

	net->diag_nlsk = netlink_kernel_create(net, NETLINK_SOCK_DIAG, &cfg);
	वापस net->diag_nlsk == शून्य ? -ENOMEM : 0;
पूर्ण

अटल व्योम __net_निकास diag_net_निकास(काष्ठा net *net)
अणु
	netlink_kernel_release(net->diag_nlsk);
	net->diag_nlsk = शून्य;
पूर्ण

अटल काष्ठा pernet_operations diag_net_ops = अणु
	.init = diag_net_init,
	.निकास = diag_net_निकास,
पूर्ण;

अटल पूर्णांक __init sock_diag_init(व्योम)
अणु
	broadcast_wq = alloc_workqueue("sock_diag_events", 0, 0);
	BUG_ON(!broadcast_wq);
	वापस रेजिस्टर_pernet_subsys(&diag_net_ops);
पूर्ण
device_initcall(sock_diag_init);
