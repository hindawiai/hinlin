<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BPF_CGROUP_H
#घोषणा _BPF_CGROUP_H

#समावेश <linux/bpf.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/jump_label.h>
#समावेश <linux/percpu.h>
#समावेश <linux/percpu-refcount.h>
#समावेश <linux/rbtree.h>
#समावेश <uapi/linux/bpf.h>

काष्ठा sock;
काष्ठा sockaddr;
काष्ठा cgroup;
काष्ठा sk_buff;
काष्ठा bpf_map;
काष्ठा bpf_prog;
काष्ठा bpf_sock_ops_kern;
काष्ठा bpf_cgroup_storage;
काष्ठा ctl_table;
काष्ठा ctl_table_header;
काष्ठा task_काष्ठा;

#अगर_घोषित CONFIG_CGROUP_BPF

बाह्य काष्ठा अटल_key_false cgroup_bpf_enabled_key[MAX_BPF_ATTACH_TYPE];
#घोषणा cgroup_bpf_enabled(type) अटल_branch_unlikely(&cgroup_bpf_enabled_key[type])

#घोषणा BPF_CGROUP_STORAGE_NEST_MAX	8

काष्ठा bpf_cgroup_storage_info अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा bpf_cgroup_storage *storage[MAX_BPF_CGROUP_STORAGE_TYPE];
पूर्ण;

/* For each cpu, permit maximum BPF_CGROUP_STORAGE_NEST_MAX number of tasks
 * to use bpf cgroup storage simultaneously.
 */
DECLARE_PER_CPU(काष्ठा bpf_cgroup_storage_info,
		bpf_cgroup_storage_info[BPF_CGROUP_STORAGE_NEST_MAX]);

#घोषणा क्रम_each_cgroup_storage_type(stype) \
	क्रम (stype = 0; stype < MAX_BPF_CGROUP_STORAGE_TYPE; stype++)

काष्ठा bpf_cgroup_storage_map;

काष्ठा bpf_storage_buffer अणु
	काष्ठा rcu_head rcu;
	अक्षर data[];
पूर्ण;

काष्ठा bpf_cgroup_storage अणु
	जोड़ अणु
		काष्ठा bpf_storage_buffer *buf;
		व्योम __percpu *percpu_buf;
	पूर्ण;
	काष्ठा bpf_cgroup_storage_map *map;
	काष्ठा bpf_cgroup_storage_key key;
	काष्ठा list_head list_map;
	काष्ठा list_head list_cg;
	काष्ठा rb_node node;
	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा bpf_cgroup_link अणु
	काष्ठा bpf_link link;
	काष्ठा cgroup *cgroup;
	क्रमागत bpf_attach_type type;
पूर्ण;

काष्ठा bpf_prog_list अणु
	काष्ठा list_head node;
	काष्ठा bpf_prog *prog;
	काष्ठा bpf_cgroup_link *link;
	काष्ठा bpf_cgroup_storage *storage[MAX_BPF_CGROUP_STORAGE_TYPE];
पूर्ण;

काष्ठा bpf_prog_array;

काष्ठा cgroup_bpf अणु
	/* array of effective progs in this cgroup */
	काष्ठा bpf_prog_array __rcu *effective[MAX_BPF_ATTACH_TYPE];

	/* attached progs to this cgroup and attach flags
	 * when flags == 0 or BPF_F_ALLOW_OVERRIDE the progs list will
	 * have either zero or one element
	 * when BPF_F_ALLOW_MULTI the list can have up to BPF_CGROUP_MAX_PROGS
	 */
	काष्ठा list_head progs[MAX_BPF_ATTACH_TYPE];
	u32 flags[MAX_BPF_ATTACH_TYPE];

	/* list of cgroup shared storages */
	काष्ठा list_head storages;

	/* temp storage क्रम effective prog array used by prog_attach/detach */
	काष्ठा bpf_prog_array *inactive;

	/* reference counter used to detach bpf programs after cgroup removal */
	काष्ठा percpu_ref refcnt;

	/* cgroup_bpf is released using a work queue */
	काष्ठा work_काष्ठा release_work;
पूर्ण;

पूर्णांक cgroup_bpf_inherit(काष्ठा cgroup *cgrp);
व्योम cgroup_bpf_offline(काष्ठा cgroup *cgrp);

पूर्णांक __cgroup_bpf_attach(काष्ठा cgroup *cgrp,
			काष्ठा bpf_prog *prog, काष्ठा bpf_prog *replace_prog,
			काष्ठा bpf_cgroup_link *link,
			क्रमागत bpf_attach_type type, u32 flags);
पूर्णांक __cgroup_bpf_detach(काष्ठा cgroup *cgrp, काष्ठा bpf_prog *prog,
			काष्ठा bpf_cgroup_link *link,
			क्रमागत bpf_attach_type type);
पूर्णांक __cgroup_bpf_query(काष्ठा cgroup *cgrp, स्थिर जोड़ bpf_attr *attr,
		       जोड़ bpf_attr __user *uattr);

/* Wrapper क्रम __cgroup_bpf_*() रक्षित by cgroup_mutex */
पूर्णांक cgroup_bpf_attach(काष्ठा cgroup *cgrp,
		      काष्ठा bpf_prog *prog, काष्ठा bpf_prog *replace_prog,
		      काष्ठा bpf_cgroup_link *link, क्रमागत bpf_attach_type type,
		      u32 flags);
पूर्णांक cgroup_bpf_detach(काष्ठा cgroup *cgrp, काष्ठा bpf_prog *prog,
		      क्रमागत bpf_attach_type type);
पूर्णांक cgroup_bpf_query(काष्ठा cgroup *cgrp, स्थिर जोड़ bpf_attr *attr,
		     जोड़ bpf_attr __user *uattr);

पूर्णांक __cgroup_bpf_run_filter_skb(काष्ठा sock *sk,
				काष्ठा sk_buff *skb,
				क्रमागत bpf_attach_type type);

पूर्णांक __cgroup_bpf_run_filter_sk(काष्ठा sock *sk,
			       क्रमागत bpf_attach_type type);

पूर्णांक __cgroup_bpf_run_filter_sock_addr(काष्ठा sock *sk,
				      काष्ठा sockaddr *uaddr,
				      क्रमागत bpf_attach_type type,
				      व्योम *t_ctx,
				      u32 *flags);

पूर्णांक __cgroup_bpf_run_filter_sock_ops(काष्ठा sock *sk,
				     काष्ठा bpf_sock_ops_kern *sock_ops,
				     क्रमागत bpf_attach_type type);

पूर्णांक __cgroup_bpf_check_dev_permission(लघु dev_type, u32 major, u32 minor,
				      लघु access, क्रमागत bpf_attach_type type);

पूर्णांक __cgroup_bpf_run_filter_sysctl(काष्ठा ctl_table_header *head,
				   काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				   अक्षर **buf, माप_प्रकार *pcount, loff_t *ppos,
				   क्रमागत bpf_attach_type type);

पूर्णांक __cgroup_bpf_run_filter_setsockopt(काष्ठा sock *sock, पूर्णांक *level,
				       पूर्णांक *optname, अक्षर __user *optval,
				       पूर्णांक *optlen, अक्षर **kernel_optval);
पूर्णांक __cgroup_bpf_run_filter_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level,
				       पूर्णांक optname, अक्षर __user *optval,
				       पूर्णांक __user *optlen, पूर्णांक max_optlen,
				       पूर्णांक retval);

पूर्णांक __cgroup_bpf_run_filter_माला_लोockopt_kern(काष्ठा sock *sk, पूर्णांक level,
					    पूर्णांक optname, व्योम *optval,
					    पूर्णांक *optlen, पूर्णांक retval);

अटल अंतरभूत क्रमागत bpf_cgroup_storage_type cgroup_storage_type(
	काष्ठा bpf_map *map)
अणु
	अगर (map->map_type == BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE)
		वापस BPF_CGROUP_STORAGE_PERCPU;

	वापस BPF_CGROUP_STORAGE_SHARED;
पूर्ण

अटल अंतरभूत पूर्णांक bpf_cgroup_storage_set(काष्ठा bpf_cgroup_storage
					 *storage[MAX_BPF_CGROUP_STORAGE_TYPE])
अणु
	क्रमागत bpf_cgroup_storage_type stype;
	पूर्णांक i, err = 0;

	preempt_disable();
	क्रम (i = 0; i < BPF_CGROUP_STORAGE_NEST_MAX; i++) अणु
		अगर (unlikely(this_cpu_पढ़ो(bpf_cgroup_storage_info[i].task) != शून्य))
			जारी;

		this_cpu_ग_लिखो(bpf_cgroup_storage_info[i].task, current);
		क्रम_each_cgroup_storage_type(stype)
			this_cpu_ग_लिखो(bpf_cgroup_storage_info[i].storage[stype],
				       storage[stype]);
		जाओ out;
	पूर्ण
	err = -EBUSY;
	WARN_ON_ONCE(1);

out:
	preempt_enable();
	वापस err;
पूर्ण

अटल अंतरभूत व्योम bpf_cgroup_storage_unset(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BPF_CGROUP_STORAGE_NEST_MAX; i++) अणु
		अगर (unlikely(this_cpu_पढ़ो(bpf_cgroup_storage_info[i].task) != current))
			जारी;

		this_cpu_ग_लिखो(bpf_cgroup_storage_info[i].task, शून्य);
		वापस;
	पूर्ण
पूर्ण

काष्ठा bpf_cgroup_storage *
cgroup_storage_lookup(काष्ठा bpf_cgroup_storage_map *map,
		      व्योम *key, bool locked);
काष्ठा bpf_cgroup_storage *bpf_cgroup_storage_alloc(काष्ठा bpf_prog *prog,
					क्रमागत bpf_cgroup_storage_type stype);
व्योम bpf_cgroup_storage_मुक्त(काष्ठा bpf_cgroup_storage *storage);
व्योम bpf_cgroup_storage_link(काष्ठा bpf_cgroup_storage *storage,
			     काष्ठा cgroup *cgroup,
			     क्रमागत bpf_attach_type type);
व्योम bpf_cgroup_storage_unlink(काष्ठा bpf_cgroup_storage *storage);
पूर्णांक bpf_cgroup_storage_assign(काष्ठा bpf_prog_aux *aux, काष्ठा bpf_map *map);

पूर्णांक bpf_percpu_cgroup_storage_copy(काष्ठा bpf_map *map, व्योम *key, व्योम *value);
पूर्णांक bpf_percpu_cgroup_storage_update(काष्ठा bpf_map *map, व्योम *key,
				     व्योम *value, u64 flags);

/* Wrappers क्रम __cgroup_bpf_run_filter_skb() guarded by cgroup_bpf_enabled. */
#घोषणा BPF_CGROUP_RUN_PROG_INET_INGRESS(sk, skb)			      \
(अणु									      \
	पूर्णांक __ret = 0;							      \
	अगर (cgroup_bpf_enabled(BPF_CGROUP_INET_INGRESS))		      \
		__ret = __cgroup_bpf_run_filter_skb(sk, skb,		      \
						    BPF_CGROUP_INET_INGRESS); \
									      \
	__ret;								      \
पूर्ण)

#घोषणा BPF_CGROUP_RUN_PROG_INET_EGRESS(sk, skb)			       \
(अणु									       \
	पूर्णांक __ret = 0;							       \
	अगर (cgroup_bpf_enabled(BPF_CGROUP_INET_EGRESS) && sk && sk == skb->sk) अणु \
		typeof(sk) __sk = sk_to_full_sk(sk);			       \
		अगर (sk_fullsock(__sk))					       \
			__ret = __cgroup_bpf_run_filter_skb(__sk, skb,	       \
						      BPF_CGROUP_INET_EGRESS); \
	पूर्ण								       \
	__ret;								       \
पूर्ण)

#घोषणा BPF_CGROUP_RUN_SK_PROG(sk, type)				       \
(अणु									       \
	पूर्णांक __ret = 0;							       \
	अगर (cgroup_bpf_enabled(type)) अणु					       \
		__ret = __cgroup_bpf_run_filter_sk(sk, type);		       \
	पूर्ण								       \
	__ret;								       \
पूर्ण)

#घोषणा BPF_CGROUP_RUN_PROG_INET_SOCK(sk)				       \
	BPF_CGROUP_RUN_SK_PROG(sk, BPF_CGROUP_INET_SOCK_CREATE)

#घोषणा BPF_CGROUP_RUN_PROG_INET_SOCK_RELEASE(sk)			       \
	BPF_CGROUP_RUN_SK_PROG(sk, BPF_CGROUP_INET_SOCK_RELEASE)

#घोषणा BPF_CGROUP_RUN_PROG_INET4_POST_BIND(sk)				       \
	BPF_CGROUP_RUN_SK_PROG(sk, BPF_CGROUP_INET4_POST_BIND)

#घोषणा BPF_CGROUP_RUN_PROG_INET6_POST_BIND(sk)				       \
	BPF_CGROUP_RUN_SK_PROG(sk, BPF_CGROUP_INET6_POST_BIND)

#घोषणा BPF_CGROUP_RUN_SA_PROG(sk, uaddr, type)				       \
(अणु									       \
	u32 __unused_flags;						       \
	पूर्णांक __ret = 0;							       \
	अगर (cgroup_bpf_enabled(type))					       \
		__ret = __cgroup_bpf_run_filter_sock_addr(sk, uaddr, type,     \
							  शून्य,		       \
							  &__unused_flags);    \
	__ret;								       \
पूर्ण)

#घोषणा BPF_CGROUP_RUN_SA_PROG_LOCK(sk, uaddr, type, t_ctx)		       \
(अणु									       \
	u32 __unused_flags;						       \
	पूर्णांक __ret = 0;							       \
	अगर (cgroup_bpf_enabled(type))	अणु				       \
		lock_sock(sk);						       \
		__ret = __cgroup_bpf_run_filter_sock_addr(sk, uaddr, type,     \
							  t_ctx,	       \
							  &__unused_flags);    \
		release_sock(sk);					       \
	पूर्ण								       \
	__ret;								       \
पूर्ण)

/* BPF_CGROUP_INET4_BIND and BPF_CGROUP_INET6_BIND can वापस extra flags
 * via upper bits of वापस code. The only flag that is supported
 * (at bit position 0) is to indicate CAP_NET_BIND_SERVICE capability check
 * should be bypassed (BPF_RET_BIND_NO_CAP_NET_BIND_SERVICE).
 */
#घोषणा BPF_CGROUP_RUN_PROG_INET_BIND_LOCK(sk, uaddr, type, bind_flags)	       \
(अणु									       \
	u32 __flags = 0;						       \
	पूर्णांक __ret = 0;							       \
	अगर (cgroup_bpf_enabled(type))	अणु				       \
		lock_sock(sk);						       \
		__ret = __cgroup_bpf_run_filter_sock_addr(sk, uaddr, type,     \
							  शून्य, &__flags);     \
		release_sock(sk);					       \
		अगर (__flags & BPF_RET_BIND_NO_CAP_NET_BIND_SERVICE)	       \
			*bind_flags |= BIND_NO_CAP_NET_BIND_SERVICE;	       \
	पूर्ण								       \
	__ret;								       \
पूर्ण)

#घोषणा BPF_CGROUP_PRE_CONNECT_ENABLED(sk)				       \
	((cgroup_bpf_enabled(BPF_CGROUP_INET4_CONNECT) ||		       \
	  cgroup_bpf_enabled(BPF_CGROUP_INET6_CONNECT)) &&		       \
	 (sk)->sk_prot->pre_connect)

#घोषणा BPF_CGROUP_RUN_PROG_INET4_CONNECT(sk, uaddr)			       \
	BPF_CGROUP_RUN_SA_PROG(sk, uaddr, BPF_CGROUP_INET4_CONNECT)

#घोषणा BPF_CGROUP_RUN_PROG_INET6_CONNECT(sk, uaddr)			       \
	BPF_CGROUP_RUN_SA_PROG(sk, uaddr, BPF_CGROUP_INET6_CONNECT)

#घोषणा BPF_CGROUP_RUN_PROG_INET4_CONNECT_LOCK(sk, uaddr)		       \
	BPF_CGROUP_RUN_SA_PROG_LOCK(sk, uaddr, BPF_CGROUP_INET4_CONNECT, शून्य)

#घोषणा BPF_CGROUP_RUN_PROG_INET6_CONNECT_LOCK(sk, uaddr)		       \
	BPF_CGROUP_RUN_SA_PROG_LOCK(sk, uaddr, BPF_CGROUP_INET6_CONNECT, शून्य)

#घोषणा BPF_CGROUP_RUN_PROG_UDP4_SENDMSG_LOCK(sk, uaddr, t_ctx)		       \
	BPF_CGROUP_RUN_SA_PROG_LOCK(sk, uaddr, BPF_CGROUP_UDP4_SENDMSG, t_ctx)

#घोषणा BPF_CGROUP_RUN_PROG_UDP6_SENDMSG_LOCK(sk, uaddr, t_ctx)		       \
	BPF_CGROUP_RUN_SA_PROG_LOCK(sk, uaddr, BPF_CGROUP_UDP6_SENDMSG, t_ctx)

#घोषणा BPF_CGROUP_RUN_PROG_UDP4_RECVMSG_LOCK(sk, uaddr)			\
	BPF_CGROUP_RUN_SA_PROG_LOCK(sk, uaddr, BPF_CGROUP_UDP4_RECVMSG, शून्य)

#घोषणा BPF_CGROUP_RUN_PROG_UDP6_RECVMSG_LOCK(sk, uaddr)			\
	BPF_CGROUP_RUN_SA_PROG_LOCK(sk, uaddr, BPF_CGROUP_UDP6_RECVMSG, शून्य)

/* The SOCK_OPS"_SK" macro should be used when sock_ops->sk is not a
 * fullsock and its parent fullsock cannot be traced by
 * sk_to_full_sk().
 *
 * e.g. sock_ops->sk is a request_sock and it is under syncookie mode.
 * Its listener-sk is not attached to the rsk_listener.
 * In this हाल, the caller holds the listener-sk (unlocked),
 * set its sock_ops->sk to req_sk, and call this SOCK_OPS"_SK" with
 * the listener-sk such that the cgroup-bpf-progs of the
 * listener-sk will be run.
 *
 * Regardless of syncookie mode or not,
 * calling bpf_setsockopt on listener-sk will not make sense anyway,
 * so passing 'sock_ops->sk == req_sk' to the bpf prog is appropriate here.
 */
#घोषणा BPF_CGROUP_RUN_PROG_SOCK_OPS_SK(sock_ops, sk)			\
(अणु									\
	पूर्णांक __ret = 0;							\
	अगर (cgroup_bpf_enabled(BPF_CGROUP_SOCK_OPS))			\
		__ret = __cgroup_bpf_run_filter_sock_ops(sk,		\
							 sock_ops,	\
							 BPF_CGROUP_SOCK_OPS); \
	__ret;								\
पूर्ण)

#घोषणा BPF_CGROUP_RUN_PROG_SOCK_OPS(sock_ops)				       \
(अणु									       \
	पूर्णांक __ret = 0;							       \
	अगर (cgroup_bpf_enabled(BPF_CGROUP_SOCK_OPS) && (sock_ops)->sk) अणु       \
		typeof(sk) __sk = sk_to_full_sk((sock_ops)->sk);	       \
		अगर (__sk && sk_fullsock(__sk))				       \
			__ret = __cgroup_bpf_run_filter_sock_ops(__sk,	       \
								 sock_ops,     \
							 BPF_CGROUP_SOCK_OPS); \
	पूर्ण								       \
	__ret;								       \
पूर्ण)

#घोषणा BPF_CGROUP_RUN_PROG_DEVICE_CGROUP(type, major, minor, access)	      \
(अणु									      \
	पूर्णांक __ret = 0;							      \
	अगर (cgroup_bpf_enabled(BPF_CGROUP_DEVICE))			      \
		__ret = __cgroup_bpf_check_dev_permission(type, major, minor, \
							  access,	      \
							  BPF_CGROUP_DEVICE); \
									      \
	__ret;								      \
पूर्ण)


#घोषणा BPF_CGROUP_RUN_PROG_SYSCTL(head, table, ग_लिखो, buf, count, pos)  \
(अणु									       \
	पूर्णांक __ret = 0;							       \
	अगर (cgroup_bpf_enabled(BPF_CGROUP_SYSCTL))			       \
		__ret = __cgroup_bpf_run_filter_sysctl(head, table, ग_लिखो,     \
						       buf, count, pos,        \
						       BPF_CGROUP_SYSCTL);     \
	__ret;								       \
पूर्ण)

#घोषणा BPF_CGROUP_RUN_PROG_SETSOCKOPT(sock, level, optname, optval, optlen,   \
				       kernel_optval)			       \
(अणु									       \
	पूर्णांक __ret = 0;							       \
	अगर (cgroup_bpf_enabled(BPF_CGROUP_SETSOCKOPT))			       \
		__ret = __cgroup_bpf_run_filter_setsockopt(sock, level,	       \
							   optname, optval,    \
							   optlen,	       \
							   kernel_optval);     \
	__ret;								       \
पूर्ण)

#घोषणा BPF_CGROUP_GETSOCKOPT_MAX_OPTLEN(optlen)			       \
(अणु									       \
	पूर्णांक __ret = 0;							       \
	अगर (cgroup_bpf_enabled(BPF_CGROUP_GETSOCKOPT))			       \
		get_user(__ret, optlen);				       \
	__ret;								       \
पूर्ण)

#घोषणा BPF_CGROUP_RUN_PROG_GETSOCKOPT(sock, level, optname, optval, optlen,   \
				       max_optlen, retval)		       \
(अणु									       \
	पूर्णांक __ret = retval;						       \
	अगर (cgroup_bpf_enabled(BPF_CGROUP_GETSOCKOPT))			       \
		अगर (!(sock)->sk_prot->bpf_bypass_माला_लोockopt ||		       \
		    !INसूचीECT_CALL_INET_1((sock)->sk_prot->bpf_bypass_माला_लोockopt, \
					tcp_bpf_bypass_माला_लोockopt,	       \
					level, optname))		       \
			__ret = __cgroup_bpf_run_filter_माला_लोockopt(	       \
				sock, level, optname, optval, optlen,	       \
				max_optlen, retval);			       \
	__ret;								       \
पूर्ण)

#घोषणा BPF_CGROUP_RUN_PROG_GETSOCKOPT_KERN(sock, level, optname, optval,      \
					    optlen, retval)		       \
(अणु									       \
	पूर्णांक __ret = retval;						       \
	अगर (cgroup_bpf_enabled(BPF_CGROUP_GETSOCKOPT))			       \
		__ret = __cgroup_bpf_run_filter_माला_लोockopt_kern(	       \
			sock, level, optname, optval, optlen, retval);	       \
	__ret;								       \
पूर्ण)

पूर्णांक cgroup_bpf_prog_attach(स्थिर जोड़ bpf_attr *attr,
			   क्रमागत bpf_prog_type ptype, काष्ठा bpf_prog *prog);
पूर्णांक cgroup_bpf_prog_detach(स्थिर जोड़ bpf_attr *attr,
			   क्रमागत bpf_prog_type ptype);
पूर्णांक cgroup_bpf_link_attach(स्थिर जोड़ bpf_attr *attr, काष्ठा bpf_prog *prog);
पूर्णांक cgroup_bpf_prog_query(स्थिर जोड़ bpf_attr *attr,
			  जोड़ bpf_attr __user *uattr);
#अन्यथा

काष्ठा cgroup_bpf अणुपूर्ण;
अटल अंतरभूत पूर्णांक cgroup_bpf_inherit(काष्ठा cgroup *cgrp) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम cgroup_bpf_offline(काष्ठा cgroup *cgrp) अणुपूर्ण

अटल अंतरभूत पूर्णांक cgroup_bpf_prog_attach(स्थिर जोड़ bpf_attr *attr,
					 क्रमागत bpf_prog_type ptype,
					 काष्ठा bpf_prog *prog)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक cgroup_bpf_prog_detach(स्थिर जोड़ bpf_attr *attr,
					 क्रमागत bpf_prog_type ptype)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक cgroup_bpf_link_attach(स्थिर जोड़ bpf_attr *attr,
					 काष्ठा bpf_prog *prog)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक cgroup_bpf_prog_query(स्थिर जोड़ bpf_attr *attr,
					जोड़ bpf_attr __user *uattr)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक bpf_cgroup_storage_set(
	काष्ठा bpf_cgroup_storage *storage[MAX_BPF_CGROUP_STORAGE_TYPE]) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम bpf_cgroup_storage_unset(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक bpf_cgroup_storage_assign(काष्ठा bpf_prog_aux *aux,
					    काष्ठा bpf_map *map) अणु वापस 0; पूर्ण
अटल अंतरभूत काष्ठा bpf_cgroup_storage *bpf_cgroup_storage_alloc(
	काष्ठा bpf_prog *prog, क्रमागत bpf_cgroup_storage_type stype) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम bpf_cgroup_storage_मुक्त(
	काष्ठा bpf_cgroup_storage *storage) अणुपूर्ण
अटल अंतरभूत पूर्णांक bpf_percpu_cgroup_storage_copy(काष्ठा bpf_map *map, व्योम *key,
						 व्योम *value) अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक bpf_percpu_cgroup_storage_update(काष्ठा bpf_map *map,
					व्योम *key, व्योम *value, u64 flags) अणु
	वापस 0;
पूर्ण

#घोषणा cgroup_bpf_enabled(type) (0)
#घोषणा BPF_CGROUP_RUN_SA_PROG_LOCK(sk, uaddr, type, t_ctx) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_PRE_CONNECT_ENABLED(sk) (0)
#घोषणा BPF_CGROUP_RUN_PROG_INET_INGRESS(sk,skb) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_INET_EGRESS(sk,skb) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_INET_SOCK(sk) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_INET_SOCK_RELEASE(sk) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_INET_BIND_LOCK(sk, uaddr, type, flags) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_INET4_POST_BIND(sk) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_INET6_POST_BIND(sk) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_INET4_CONNECT(sk, uaddr) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_INET4_CONNECT_LOCK(sk, uaddr) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_INET6_CONNECT(sk, uaddr) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_INET6_CONNECT_LOCK(sk, uaddr) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_UDP4_SENDMSG_LOCK(sk, uaddr, t_ctx) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_UDP6_SENDMSG_LOCK(sk, uaddr, t_ctx) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_UDP4_RECVMSG_LOCK(sk, uaddr) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_UDP6_RECVMSG_LOCK(sk, uaddr) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_SOCK_OPS(sock_ops) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_DEVICE_CGROUP(type,major,minor,access) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_SYSCTL(head,table,ग_लिखो,buf,count,pos) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_GETSOCKOPT_MAX_OPTLEN(optlen) (अणु 0; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_GETSOCKOPT(sock, level, optname, optval, \
				       optlen, max_optlen, retval) (अणु retval; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_GETSOCKOPT_KERN(sock, level, optname, optval, \
					    optlen, retval) (अणु retval; पूर्ण)
#घोषणा BPF_CGROUP_RUN_PROG_SETSOCKOPT(sock, level, optname, optval, optlen, \
				       kernel_optval) (अणु 0; पूर्ण)

#घोषणा क्रम_each_cgroup_storage_type(stype) क्रम (; false; )

#पूर्ण_अगर /* CONFIG_CGROUP_BPF */

#पूर्ण_अगर /* _BPF_CGROUP_H */
