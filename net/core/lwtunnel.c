<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lwtunnel	Infraकाष्ठाure क्रम light weight tunnels like mpls
 *
 * Authors:	Roopa Prabhu, <roopa@cumulusnetworks.com>
 */

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/lwtunnel.h>
#समावेश <linux/in.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>

#समावेश <net/lwtunnel.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/rtnh.h>

#अगर_घोषित CONFIG_MODULES

अटल स्थिर अक्षर *lwtunnel_encap_str(क्रमागत lwtunnel_encap_types encap_type)
अणु
	/* Only lwt encaps implemented without using an पूर्णांकerface क्रम
	 * the encap need to वापस a string here.
	 */
	चयन (encap_type) अणु
	हाल LWTUNNEL_ENCAP_MPLS:
		वापस "MPLS";
	हाल LWTUNNEL_ENCAP_ILA:
		वापस "ILA";
	हाल LWTUNNEL_ENCAP_SEG6:
		वापस "SEG6";
	हाल LWTUNNEL_ENCAP_BPF:
		वापस "BPF";
	हाल LWTUNNEL_ENCAP_SEG6_LOCAL:
		वापस "SEG6LOCAL";
	हाल LWTUNNEL_ENCAP_RPL:
		वापस "RPL";
	हाल LWTUNNEL_ENCAP_IP6:
	हाल LWTUNNEL_ENCAP_IP:
	हाल LWTUNNEL_ENCAP_NONE:
	हाल __LWTUNNEL_ENCAP_MAX:
		/* should not have got here */
		WARN_ON(1);
		अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_MODULES */

काष्ठा lwtunnel_state *lwtunnel_state_alloc(पूर्णांक encap_len)
अणु
	काष्ठा lwtunnel_state *lws;

	lws = kzalloc(माप(*lws) + encap_len, GFP_ATOMIC);

	वापस lws;
पूर्ण
EXPORT_SYMBOL_GPL(lwtunnel_state_alloc);

अटल स्थिर काष्ठा lwtunnel_encap_ops __rcu *
		lwtun_encaps[LWTUNNEL_ENCAP_MAX + 1] __पढ़ो_mostly;

पूर्णांक lwtunnel_encap_add_ops(स्थिर काष्ठा lwtunnel_encap_ops *ops,
			   अचिन्हित पूर्णांक num)
अणु
	अगर (num > LWTUNNEL_ENCAP_MAX)
		वापस -दुस्फल;

	वापस !cmpxchg((स्थिर काष्ठा lwtunnel_encap_ops **)
			&lwtun_encaps[num],
			शून्य, ops) ? 0 : -1;
पूर्ण
EXPORT_SYMBOL_GPL(lwtunnel_encap_add_ops);

पूर्णांक lwtunnel_encap_del_ops(स्थिर काष्ठा lwtunnel_encap_ops *ops,
			   अचिन्हित पूर्णांक encap_type)
अणु
	पूर्णांक ret;

	अगर (encap_type == LWTUNNEL_ENCAP_NONE ||
	    encap_type > LWTUNNEL_ENCAP_MAX)
		वापस -दुस्फल;

	ret = (cmpxchg((स्थिर काष्ठा lwtunnel_encap_ops **)
		       &lwtun_encaps[encap_type],
		       ops, शून्य) == ops) ? 0 : -1;

	synchronize_net();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lwtunnel_encap_del_ops);

पूर्णांक lwtunnel_build_state(काष्ठा net *net, u16 encap_type,
			 काष्ठा nlattr *encap, अचिन्हित पूर्णांक family,
			 स्थिर व्योम *cfg, काष्ठा lwtunnel_state **lws,
			 काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा lwtunnel_encap_ops *ops;
	bool found = false;
	पूर्णांक ret = -EINVAL;

	अगर (encap_type == LWTUNNEL_ENCAP_NONE ||
	    encap_type > LWTUNNEL_ENCAP_MAX) अणु
		NL_SET_ERR_MSG_ATTR(extack, encap,
				    "Unknown LWT encapsulation type");
		वापस ret;
	पूर्ण

	ret = -EOPNOTSUPP;
	rcu_पढ़ो_lock();
	ops = rcu_dereference(lwtun_encaps[encap_type]);
	अगर (likely(ops && ops->build_state && try_module_get(ops->owner)))
		found = true;
	rcu_पढ़ो_unlock();

	अगर (found) अणु
		ret = ops->build_state(net, encap, family, cfg, lws, extack);
		अगर (ret)
			module_put(ops->owner);
	पूर्ण अन्यथा अणु
		/* करोn't rely on -EOPNOTSUPP to detect match as build_state
		 * handlers could वापस it
		 */
		NL_SET_ERR_MSG_ATTR(extack, encap,
				    "LWT encapsulation type not supported");
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lwtunnel_build_state);

पूर्णांक lwtunnel_valid_encap_type(u16 encap_type, काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा lwtunnel_encap_ops *ops;
	पूर्णांक ret = -EINVAL;

	अगर (encap_type == LWTUNNEL_ENCAP_NONE ||
	    encap_type > LWTUNNEL_ENCAP_MAX) अणु
		NL_SET_ERR_MSG(extack, "Unknown lwt encapsulation type");
		वापस ret;
	पूर्ण

	rcu_पढ़ो_lock();
	ops = rcu_dereference(lwtun_encaps[encap_type]);
	rcu_पढ़ो_unlock();
#अगर_घोषित CONFIG_MODULES
	अगर (!ops) अणु
		स्थिर अक्षर *encap_type_str = lwtunnel_encap_str(encap_type);

		अगर (encap_type_str) अणु
			__rtnl_unlock();
			request_module("rtnl-lwt-%s", encap_type_str);
			rtnl_lock();

			rcu_पढ़ो_lock();
			ops = rcu_dereference(lwtun_encaps[encap_type]);
			rcu_पढ़ो_unlock();
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	ret = ops ? 0 : -EOPNOTSUPP;
	अगर (ret < 0)
		NL_SET_ERR_MSG(extack, "lwt encapsulation type not supported");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lwtunnel_valid_encap_type);

पूर्णांक lwtunnel_valid_encap_type_attr(काष्ठा nlattr *attr, पूर्णांक reमुख्यing,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rtnexthop *rtnh = (काष्ठा rtnexthop *)attr;
	काष्ठा nlattr *nla_entype;
	काष्ठा nlattr *attrs;
	u16 encap_type;
	पूर्णांक attrlen;

	जबतक (rtnh_ok(rtnh, reमुख्यing)) अणु
		attrlen = rtnh_attrlen(rtnh);
		अगर (attrlen > 0) अणु
			attrs = rtnh_attrs(rtnh);
			nla_entype = nla_find(attrs, attrlen, RTA_ENCAP_TYPE);

			अगर (nla_entype) अणु
				encap_type = nla_get_u16(nla_entype);

				अगर (lwtunnel_valid_encap_type(encap_type,
							      extack) != 0)
					वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण
		rtnh = rtnh_next(rtnh, &reमुख्यing);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lwtunnel_valid_encap_type_attr);

व्योम lwtstate_मुक्त(काष्ठा lwtunnel_state *lws)
अणु
	स्थिर काष्ठा lwtunnel_encap_ops *ops = lwtun_encaps[lws->type];

	अगर (ops->destroy_state) अणु
		ops->destroy_state(lws);
		kमुक्त_rcu(lws, rcu);
	पूर्ण अन्यथा अणु
		kमुक्त(lws);
	पूर्ण
	module_put(ops->owner);
पूर्ण
EXPORT_SYMBOL_GPL(lwtstate_मुक्त);

पूर्णांक lwtunnel_fill_encap(काष्ठा sk_buff *skb, काष्ठा lwtunnel_state *lwtstate,
			पूर्णांक encap_attr, पूर्णांक encap_type_attr)
अणु
	स्थिर काष्ठा lwtunnel_encap_ops *ops;
	काष्ठा nlattr *nest;
	पूर्णांक ret;

	अगर (!lwtstate)
		वापस 0;

	अगर (lwtstate->type == LWTUNNEL_ENCAP_NONE ||
	    lwtstate->type > LWTUNNEL_ENCAP_MAX)
		वापस 0;

	nest = nla_nest_start_noflag(skb, encap_attr);
	अगर (!nest)
		वापस -EMSGSIZE;

	ret = -EOPNOTSUPP;
	rcu_पढ़ो_lock();
	ops = rcu_dereference(lwtun_encaps[lwtstate->type]);
	अगर (likely(ops && ops->fill_encap))
		ret = ops->fill_encap(skb, lwtstate);
	rcu_पढ़ो_unlock();

	अगर (ret)
		जाओ nla_put_failure;
	nla_nest_end(skb, nest);
	ret = nla_put_u16(skb, encap_type_attr, lwtstate->type);
	अगर (ret)
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nest);

	वापस (ret == -EOPNOTSUPP ? 0 : ret);
पूर्ण
EXPORT_SYMBOL_GPL(lwtunnel_fill_encap);

पूर्णांक lwtunnel_get_encap_size(काष्ठा lwtunnel_state *lwtstate)
अणु
	स्थिर काष्ठा lwtunnel_encap_ops *ops;
	पूर्णांक ret = 0;

	अगर (!lwtstate)
		वापस 0;

	अगर (lwtstate->type == LWTUNNEL_ENCAP_NONE ||
	    lwtstate->type > LWTUNNEL_ENCAP_MAX)
		वापस 0;

	rcu_पढ़ो_lock();
	ops = rcu_dereference(lwtun_encaps[lwtstate->type]);
	अगर (likely(ops && ops->get_encap_size))
		ret = nla_total_size(ops->get_encap_size(lwtstate));
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lwtunnel_get_encap_size);

पूर्णांक lwtunnel_cmp_encap(काष्ठा lwtunnel_state *a, काष्ठा lwtunnel_state *b)
अणु
	स्थिर काष्ठा lwtunnel_encap_ops *ops;
	पूर्णांक ret = 0;

	अगर (!a && !b)
		वापस 0;

	अगर (!a || !b)
		वापस 1;

	अगर (a->type != b->type)
		वापस 1;

	अगर (a->type == LWTUNNEL_ENCAP_NONE ||
	    a->type > LWTUNNEL_ENCAP_MAX)
		वापस 0;

	rcu_पढ़ो_lock();
	ops = rcu_dereference(lwtun_encaps[a->type]);
	अगर (likely(ops && ops->cmp_encap))
		ret = ops->cmp_encap(a, b);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lwtunnel_cmp_encap);

पूर्णांक lwtunnel_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	स्थिर काष्ठा lwtunnel_encap_ops *ops;
	काष्ठा lwtunnel_state *lwtstate;
	पूर्णांक ret = -EINVAL;

	अगर (!dst)
		जाओ drop;
	lwtstate = dst->lwtstate;

	अगर (lwtstate->type == LWTUNNEL_ENCAP_NONE ||
	    lwtstate->type > LWTUNNEL_ENCAP_MAX)
		वापस 0;

	ret = -EOPNOTSUPP;
	rcu_पढ़ो_lock();
	ops = rcu_dereference(lwtun_encaps[lwtstate->type]);
	अगर (likely(ops && ops->output))
		ret = ops->output(net, sk, skb);
	rcu_पढ़ो_unlock();

	अगर (ret == -EOPNOTSUPP)
		जाओ drop;

	वापस ret;

drop:
	kमुक्त_skb(skb);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lwtunnel_output);

पूर्णांक lwtunnel_xmit(काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	स्थिर काष्ठा lwtunnel_encap_ops *ops;
	काष्ठा lwtunnel_state *lwtstate;
	पूर्णांक ret = -EINVAL;

	अगर (!dst)
		जाओ drop;

	lwtstate = dst->lwtstate;

	अगर (lwtstate->type == LWTUNNEL_ENCAP_NONE ||
	    lwtstate->type > LWTUNNEL_ENCAP_MAX)
		वापस 0;

	ret = -EOPNOTSUPP;
	rcu_पढ़ो_lock();
	ops = rcu_dereference(lwtun_encaps[lwtstate->type]);
	अगर (likely(ops && ops->xmit))
		ret = ops->xmit(skb);
	rcu_पढ़ो_unlock();

	अगर (ret == -EOPNOTSUPP)
		जाओ drop;

	वापस ret;

drop:
	kमुक्त_skb(skb);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lwtunnel_xmit);

पूर्णांक lwtunnel_input(काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	स्थिर काष्ठा lwtunnel_encap_ops *ops;
	काष्ठा lwtunnel_state *lwtstate;
	पूर्णांक ret = -EINVAL;

	अगर (!dst)
		जाओ drop;
	lwtstate = dst->lwtstate;

	अगर (lwtstate->type == LWTUNNEL_ENCAP_NONE ||
	    lwtstate->type > LWTUNNEL_ENCAP_MAX)
		वापस 0;

	ret = -EOPNOTSUPP;
	rcu_पढ़ो_lock();
	ops = rcu_dereference(lwtun_encaps[lwtstate->type]);
	अगर (likely(ops && ops->input))
		ret = ops->input(skb);
	rcu_पढ़ो_unlock();

	अगर (ret == -EOPNOTSUPP)
		जाओ drop;

	वापस ret;

drop:
	kमुक्त_skb(skb);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lwtunnel_input);
