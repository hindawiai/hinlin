<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/mutex.h>
#समावेश <net/sock.h>

#समावेश "nf_internals.h"

/* Sockopts only रेजिस्टरed and called from user context, so
   net locking would be overसमाप्त.  Also, [gs]etsockopt calls may
   sleep. */
अटल DEFINE_MUTEX(nf_sockopt_mutex);
अटल LIST_HEAD(nf_sockopts);

/* Do exclusive ranges overlap? */
अटल अंतरभूत पूर्णांक overlap(पूर्णांक min1, पूर्णांक max1, पूर्णांक min2, पूर्णांक max2)
अणु
	वापस max1 > min2 && min1 < max2;
पूर्ण

/* Functions to रेजिस्टर sockopt ranges (exclusive). */
पूर्णांक nf_रेजिस्टर_sockopt(काष्ठा nf_sockopt_ops *reg)
अणु
	काष्ठा nf_sockopt_ops *ops;
	पूर्णांक ret = 0;

	mutex_lock(&nf_sockopt_mutex);
	list_क्रम_each_entry(ops, &nf_sockopts, list) अणु
		अगर (ops->pf == reg->pf
		    && (overlap(ops->set_opपंचांगin, ops->set_opपंचांगax,
				reg->set_opपंचांगin, reg->set_opपंचांगax)
			|| overlap(ops->get_opपंचांगin, ops->get_opपंचांगax,
				   reg->get_opपंचांगin, reg->get_opपंचांगax))) अणु
			pr_debug("nf_sock overlap: %u-%u/%u-%u v %u-%u/%u-%u\n",
				ops->set_opपंचांगin, ops->set_opपंचांगax,
				ops->get_opपंचांगin, ops->get_opपंचांगax,
				reg->set_opपंचांगin, reg->set_opपंचांगax,
				reg->get_opपंचांगin, reg->get_opपंचांगax);
			ret = -EBUSY;
			जाओ out;
		पूर्ण
	पूर्ण

	list_add(&reg->list, &nf_sockopts);
out:
	mutex_unlock(&nf_sockopt_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(nf_रेजिस्टर_sockopt);

व्योम nf_unरेजिस्टर_sockopt(काष्ठा nf_sockopt_ops *reg)
अणु
	mutex_lock(&nf_sockopt_mutex);
	list_del(&reg->list);
	mutex_unlock(&nf_sockopt_mutex);
पूर्ण
EXPORT_SYMBOL(nf_unरेजिस्टर_sockopt);

अटल काष्ठा nf_sockopt_ops *nf_sockopt_find(काष्ठा sock *sk, u_पूर्णांक8_t pf,
		पूर्णांक val, पूर्णांक get)
अणु
	काष्ठा nf_sockopt_ops *ops;

	mutex_lock(&nf_sockopt_mutex);
	list_क्रम_each_entry(ops, &nf_sockopts, list) अणु
		अगर (ops->pf == pf) अणु
			अगर (!try_module_get(ops->owner))
				जाओ out_nosup;

			अगर (get) अणु
				अगर (val >= ops->get_opपंचांगin &&
						val < ops->get_opपंचांगax)
					जाओ out;
			पूर्ण अन्यथा अणु
				अगर (val >= ops->set_opपंचांगin &&
						val < ops->set_opपंचांगax)
					जाओ out;
			पूर्ण
			module_put(ops->owner);
		पूर्ण
	पूर्ण
out_nosup:
	ops = ERR_PTR(-ENOPROTOOPT);
out:
	mutex_unlock(&nf_sockopt_mutex);
	वापस ops;
पूर्ण

पूर्णांक nf_setsockopt(काष्ठा sock *sk, u_पूर्णांक8_t pf, पूर्णांक val, sockptr_t opt,
		  अचिन्हित पूर्णांक len)
अणु
	काष्ठा nf_sockopt_ops *ops;
	पूर्णांक ret;

	ops = nf_sockopt_find(sk, pf, val, 0);
	अगर (IS_ERR(ops))
		वापस PTR_ERR(ops);
	ret = ops->set(sk, val, opt, len);
	module_put(ops->owner);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(nf_setsockopt);

पूर्णांक nf_माला_लोockopt(काष्ठा sock *sk, u_पूर्णांक8_t pf, पूर्णांक val, अक्षर __user *opt,
		  पूर्णांक *len)
अणु
	काष्ठा nf_sockopt_ops *ops;
	पूर्णांक ret;

	ops = nf_sockopt_find(sk, pf, val, 1);
	अगर (IS_ERR(ops))
		वापस PTR_ERR(ops);
	ret = ops->get(sk, val, opt, len);
	module_put(ops->owner);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(nf_माला_लोockopt);
