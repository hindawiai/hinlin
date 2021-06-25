<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pluggable TCP upper layer protocol support.
 *
 * Copyright (c) 2016-2017, Mellanox Technologies. All rights reserved.
 * Copyright (c) 2016-2017, Dave Watson <davejwatson@fb.com>. All rights reserved.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/gfp.h>
#समावेश <net/tcp.h>

अटल DEFINE_SPINLOCK(tcp_ulp_list_lock);
अटल LIST_HEAD(tcp_ulp_list);

/* Simple linear search, करोn't expect many entries! */
अटल काष्ठा tcp_ulp_ops *tcp_ulp_find(स्थिर अक्षर *name)
अणु
	काष्ठा tcp_ulp_ops *e;

	list_क्रम_each_entry_rcu(e, &tcp_ulp_list, list,
				lockdep_is_held(&tcp_ulp_list_lock)) अणु
		अगर (म_भेद(e->name, name) == 0)
			वापस e;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा tcp_ulp_ops *__tcp_ulp_find_स्वतःload(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा tcp_ulp_ops *ulp = शून्य;

	rcu_पढ़ो_lock();
	ulp = tcp_ulp_find(name);

#अगर_घोषित CONFIG_MODULES
	अगर (!ulp && capable(CAP_NET_ADMIN)) अणु
		rcu_पढ़ो_unlock();
		request_module("tcp-ulp-%s", name);
		rcu_पढ़ो_lock();
		ulp = tcp_ulp_find(name);
	पूर्ण
#पूर्ण_अगर
	अगर (!ulp || !try_module_get(ulp->owner))
		ulp = शून्य;

	rcu_पढ़ो_unlock();
	वापस ulp;
पूर्ण

/* Attach new upper layer protocol to the list
 * of available protocols.
 */
पूर्णांक tcp_रेजिस्टर_ulp(काष्ठा tcp_ulp_ops *ulp)
अणु
	पूर्णांक ret = 0;

	spin_lock(&tcp_ulp_list_lock);
	अगर (tcp_ulp_find(ulp->name))
		ret = -EEXIST;
	अन्यथा
		list_add_tail_rcu(&ulp->list, &tcp_ulp_list);
	spin_unlock(&tcp_ulp_list_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tcp_रेजिस्टर_ulp);

व्योम tcp_unरेजिस्टर_ulp(काष्ठा tcp_ulp_ops *ulp)
अणु
	spin_lock(&tcp_ulp_list_lock);
	list_del_rcu(&ulp->list);
	spin_unlock(&tcp_ulp_list_lock);

	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL_GPL(tcp_unरेजिस्टर_ulp);

/* Build string with list of available upper layer protocl values */
व्योम tcp_get_available_ulp(अक्षर *buf, माप_प्रकार maxlen)
अणु
	काष्ठा tcp_ulp_ops *ulp_ops;
	माप_प्रकार offs = 0;

	*buf = '\0';
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ulp_ops, &tcp_ulp_list, list) अणु
		offs += snम_लिखो(buf + offs, maxlen - offs,
				 "%s%s",
				 offs == 0 ? "" : " ", ulp_ops->name);

		अगर (WARN_ON_ONCE(offs >= maxlen))
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

व्योम tcp_update_ulp(काष्ठा sock *sk, काष्ठा proto *proto,
		    व्योम (*ग_लिखो_space)(काष्ठा sock *sk))
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	अगर (icsk->icsk_ulp_ops->update)
		icsk->icsk_ulp_ops->update(sk, proto, ग_लिखो_space);
पूर्ण

व्योम tcp_cleanup_ulp(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	/* No sock_owned_by_me() check here as at the समय the
	 * stack calls this function, the socket is dead and
	 * about to be destroyed.
	 */
	अगर (!icsk->icsk_ulp_ops)
		वापस;

	अगर (icsk->icsk_ulp_ops->release)
		icsk->icsk_ulp_ops->release(sk);
	module_put(icsk->icsk_ulp_ops->owner);

	icsk->icsk_ulp_ops = शून्य;
पूर्ण

अटल पूर्णांक __tcp_set_ulp(काष्ठा sock *sk, स्थिर काष्ठा tcp_ulp_ops *ulp_ops)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	पूर्णांक err;

	err = -EEXIST;
	अगर (icsk->icsk_ulp_ops)
		जाओ out_err;

	err = ulp_ops->init(sk);
	अगर (err)
		जाओ out_err;

	icsk->icsk_ulp_ops = ulp_ops;
	वापस 0;
out_err:
	module_put(ulp_ops->owner);
	वापस err;
पूर्ण

पूर्णांक tcp_set_ulp(काष्ठा sock *sk, स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा tcp_ulp_ops *ulp_ops;

	sock_owned_by_me(sk);

	ulp_ops = __tcp_ulp_find_स्वतःload(name);
	अगर (!ulp_ops)
		वापस -ENOENT;

	वापस __tcp_set_ulp(sk, ulp_ops);
पूर्ण
