<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (C) 2012 by Pablo Neira Ayuso <pablo@netfilter.org>
 * (C) 2012 by Vyatta Inc. <http://www.vyatta.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/err.h>
#समावेश <linux/percpu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_extend.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_समयout.h>

काष्ठा nf_ct_समयout *
(*nf_ct_समयout_find_get_hook)(काष्ठा net *net, स्थिर अक्षर *name) __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_ct_समयout_find_get_hook);

व्योम (*nf_ct_समयout_put_hook)(काष्ठा nf_ct_समयout *समयout) __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_ct_समयout_put_hook);

अटल पूर्णांक unसमयout(काष्ठा nf_conn *ct, व्योम *समयout)
अणु
	काष्ठा nf_conn_समयout *समयout_ext = nf_ct_समयout_find(ct);

	अगर (समयout_ext && (!समयout || समयout_ext->समयout == समयout))
		RCU_INIT_POINTER(समयout_ext->समयout, शून्य);

	/* We are not पूर्णांकended to delete this conntrack. */
	वापस 0;
पूर्ण

व्योम nf_ct_unसमयout(काष्ठा net *net, काष्ठा nf_ct_समयout *समयout)
अणु
	nf_ct_iterate_cleanup_net(net, unसमयout, समयout, 0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_unसमयout);

अटल व्योम __nf_ct_समयout_put(काष्ठा nf_ct_समयout *समयout)
अणु
	typeof(nf_ct_समयout_put_hook) समयout_put;

	समयout_put = rcu_dereference(nf_ct_समयout_put_hook);
	अगर (समयout_put)
		समयout_put(समयout);
पूर्ण

पूर्णांक nf_ct_set_समयout(काष्ठा net *net, काष्ठा nf_conn *ct,
		      u8 l3num, u8 l4num, स्थिर अक्षर *समयout_name)
अणु
	typeof(nf_ct_समयout_find_get_hook) समयout_find_get;
	काष्ठा nf_ct_समयout *समयout;
	काष्ठा nf_conn_समयout *समयout_ext;
	स्थिर अक्षर *errmsg = शून्य;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	समयout_find_get = rcu_dereference(nf_ct_समयout_find_get_hook);
	अगर (!समयout_find_get) अणु
		ret = -ENOENT;
		errmsg = "Timeout policy base is empty";
		जाओ out;
	पूर्ण

	समयout = समयout_find_get(net, समयout_name);
	अगर (!समयout) अणु
		ret = -ENOENT;
		pr_info_ratelimited("No such timeout policy \"%s\"\n",
				    समयout_name);
		जाओ out;
	पूर्ण

	अगर (समयout->l3num != l3num) अणु
		ret = -EINVAL;
		pr_info_ratelimited("Timeout policy `%s' can only be used by "
				    "L%d protocol number %d\n",
				    समयout_name, 3, समयout->l3num);
		जाओ err_put_समयout;
	पूर्ण
	/* Make sure the समयout policy matches any existing protocol tracker,
	 * otherwise शेष to generic.
	 */
	अगर (समयout->l4proto->l4proto != l4num) अणु
		ret = -EINVAL;
		pr_info_ratelimited("Timeout policy `%s' can only be used by "
				    "L%d protocol number %d\n",
				    समयout_name, 4, समयout->l4proto->l4proto);
		जाओ err_put_समयout;
	पूर्ण
	समयout_ext = nf_ct_समयout_ext_add(ct, समयout, GFP_ATOMIC);
	अगर (!समयout_ext) अणु
		ret = -ENOMEM;
		जाओ err_put_समयout;
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस ret;

err_put_समयout:
	__nf_ct_समयout_put(समयout);
out:
	rcu_पढ़ो_unlock();
	अगर (errmsg)
		pr_info_ratelimited("%s\n", errmsg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_set_समयout);

व्योम nf_ct_destroy_समयout(काष्ठा nf_conn *ct)
अणु
	काष्ठा nf_conn_समयout *समयout_ext;
	typeof(nf_ct_समयout_put_hook) समयout_put;

	rcu_पढ़ो_lock();
	समयout_put = rcu_dereference(nf_ct_समयout_put_hook);

	अगर (समयout_put) अणु
		समयout_ext = nf_ct_समयout_find(ct);
		अगर (समयout_ext) अणु
			समयout_put(समयout_ext->समयout);
			RCU_INIT_POINTER(समयout_ext->समयout, शून्य);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_destroy_समयout);

अटल स्थिर काष्ठा nf_ct_ext_type समयout_extend = अणु
	.len	= माप(काष्ठा nf_conn_समयout),
	.align	= __alignof__(काष्ठा nf_conn_समयout),
	.id	= NF_CT_EXT_TIMEOUT,
पूर्ण;

पूर्णांक nf_conntrack_समयout_init(व्योम)
अणु
	पूर्णांक ret = nf_ct_extend_रेजिस्टर(&समयout_extend);
	अगर (ret < 0)
		pr_err("nf_ct_timeout: Unable to register timeout extension.\n");
	वापस ret;
पूर्ण

व्योम nf_conntrack_समयout_fini(व्योम)
अणु
	nf_ct_extend_unरेजिस्टर(&समयout_extend);
पूर्ण
