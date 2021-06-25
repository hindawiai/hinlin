<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <net/flow_offload.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rhashtable.h>

काष्ठा flow_rule *flow_rule_alloc(अचिन्हित पूर्णांक num_actions)
अणु
	काष्ठा flow_rule *rule;
	पूर्णांक i;

	rule = kzalloc(काष्ठा_size(rule, action.entries, num_actions),
		       GFP_KERNEL);
	अगर (!rule)
		वापस शून्य;

	rule->action.num_entries = num_actions;
	/* Pre-fill each action hw_stats with DONT_CARE.
	 * Caller can override this अगर it wants stats क्रम a given action.
	 */
	क्रम (i = 0; i < num_actions; i++)
		rule->action.entries[i].hw_stats = FLOW_ACTION_HW_STATS_DONT_CARE;

	वापस rule;
पूर्ण
EXPORT_SYMBOL(flow_rule_alloc);

#घोषणा FLOW_DISSECTOR_MATCH(__rule, __type, __out)				\
	स्थिर काष्ठा flow_match *__m = &(__rule)->match;			\
	काष्ठा flow_dissector *__d = (__m)->dissector;				\
										\
	(__out)->key = skb_flow_dissector_target(__d, __type, (__m)->key);	\
	(__out)->mask = skb_flow_dissector_target(__d, __type, (__m)->mask);	\

व्योम flow_rule_match_meta(स्थिर काष्ठा flow_rule *rule,
			  काष्ठा flow_match_meta *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_META, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_meta);

व्योम flow_rule_match_basic(स्थिर काष्ठा flow_rule *rule,
			   काष्ठा flow_match_basic *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_BASIC, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_basic);

व्योम flow_rule_match_control(स्थिर काष्ठा flow_rule *rule,
			     काष्ठा flow_match_control *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_CONTROL, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_control);

व्योम flow_rule_match_eth_addrs(स्थिर काष्ठा flow_rule *rule,
			       काष्ठा flow_match_eth_addrs *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_eth_addrs);

व्योम flow_rule_match_vlan(स्थिर काष्ठा flow_rule *rule,
			  काष्ठा flow_match_vlan *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_VLAN, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_vlan);

व्योम flow_rule_match_cvlan(स्थिर काष्ठा flow_rule *rule,
			   काष्ठा flow_match_vlan *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_CVLAN, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_cvlan);

व्योम flow_rule_match_ipv4_addrs(स्थिर काष्ठा flow_rule *rule,
				काष्ठा flow_match_ipv4_addrs *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_IPV4_ADDRS, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_ipv4_addrs);

व्योम flow_rule_match_ipv6_addrs(स्थिर काष्ठा flow_rule *rule,
				काष्ठा flow_match_ipv6_addrs *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_IPV6_ADDRS, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_ipv6_addrs);

व्योम flow_rule_match_ip(स्थिर काष्ठा flow_rule *rule,
			काष्ठा flow_match_ip *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_IP, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_ip);

व्योम flow_rule_match_ports(स्थिर काष्ठा flow_rule *rule,
			   काष्ठा flow_match_ports *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_PORTS, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_ports);

व्योम flow_rule_match_tcp(स्थिर काष्ठा flow_rule *rule,
			 काष्ठा flow_match_tcp *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_TCP, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_tcp);

व्योम flow_rule_match_icmp(स्थिर काष्ठा flow_rule *rule,
			  काष्ठा flow_match_icmp *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_ICMP, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_icmp);

व्योम flow_rule_match_mpls(स्थिर काष्ठा flow_rule *rule,
			  काष्ठा flow_match_mpls *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_MPLS, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_mpls);

व्योम flow_rule_match_enc_control(स्थिर काष्ठा flow_rule *rule,
				 काष्ठा flow_match_control *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_ENC_CONTROL, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_enc_control);

व्योम flow_rule_match_enc_ipv4_addrs(स्थिर काष्ठा flow_rule *rule,
				    काष्ठा flow_match_ipv4_addrs *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_enc_ipv4_addrs);

व्योम flow_rule_match_enc_ipv6_addrs(स्थिर काष्ठा flow_rule *rule,
				    काष्ठा flow_match_ipv6_addrs *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_enc_ipv6_addrs);

व्योम flow_rule_match_enc_ip(स्थिर काष्ठा flow_rule *rule,
			    काष्ठा flow_match_ip *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_ENC_IP, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_enc_ip);

व्योम flow_rule_match_enc_ports(स्थिर काष्ठा flow_rule *rule,
			       काष्ठा flow_match_ports *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_ENC_PORTS, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_enc_ports);

व्योम flow_rule_match_enc_keyid(स्थिर काष्ठा flow_rule *rule,
			       काष्ठा flow_match_enc_keyid *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_ENC_KEYID, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_enc_keyid);

व्योम flow_rule_match_enc_opts(स्थिर काष्ठा flow_rule *rule,
			      काष्ठा flow_match_enc_opts *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_ENC_OPTS, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_enc_opts);

काष्ठा flow_action_cookie *flow_action_cookie_create(व्योम *data,
						     अचिन्हित पूर्णांक len,
						     gfp_t gfp)
अणु
	काष्ठा flow_action_cookie *cookie;

	cookie = kदो_स्मृति(माप(*cookie) + len, gfp);
	अगर (!cookie)
		वापस शून्य;
	cookie->cookie_len = len;
	स_नकल(cookie->cookie, data, len);
	वापस cookie;
पूर्ण
EXPORT_SYMBOL(flow_action_cookie_create);

व्योम flow_action_cookie_destroy(काष्ठा flow_action_cookie *cookie)
अणु
	kमुक्त(cookie);
पूर्ण
EXPORT_SYMBOL(flow_action_cookie_destroy);

व्योम flow_rule_match_ct(स्थिर काष्ठा flow_rule *rule,
			काष्ठा flow_match_ct *out)
अणु
	FLOW_DISSECTOR_MATCH(rule, FLOW_DISSECTOR_KEY_CT, out);
पूर्ण
EXPORT_SYMBOL(flow_rule_match_ct);

काष्ठा flow_block_cb *flow_block_cb_alloc(flow_setup_cb_t *cb,
					  व्योम *cb_ident, व्योम *cb_priv,
					  व्योम (*release)(व्योम *cb_priv))
अणु
	काष्ठा flow_block_cb *block_cb;

	block_cb = kzalloc(माप(*block_cb), GFP_KERNEL);
	अगर (!block_cb)
		वापस ERR_PTR(-ENOMEM);

	block_cb->cb = cb;
	block_cb->cb_ident = cb_ident;
	block_cb->cb_priv = cb_priv;
	block_cb->release = release;

	वापस block_cb;
पूर्ण
EXPORT_SYMBOL(flow_block_cb_alloc);

व्योम flow_block_cb_मुक्त(काष्ठा flow_block_cb *block_cb)
अणु
	अगर (block_cb->release)
		block_cb->release(block_cb->cb_priv);

	kमुक्त(block_cb);
पूर्ण
EXPORT_SYMBOL(flow_block_cb_मुक्त);

काष्ठा flow_block_cb *flow_block_cb_lookup(काष्ठा flow_block *block,
					   flow_setup_cb_t *cb, व्योम *cb_ident)
अणु
	काष्ठा flow_block_cb *block_cb;

	list_क्रम_each_entry(block_cb, &block->cb_list, list) अणु
		अगर (block_cb->cb == cb &&
		    block_cb->cb_ident == cb_ident)
			वापस block_cb;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(flow_block_cb_lookup);

व्योम *flow_block_cb_priv(काष्ठा flow_block_cb *block_cb)
अणु
	वापस block_cb->cb_priv;
पूर्ण
EXPORT_SYMBOL(flow_block_cb_priv);

व्योम flow_block_cb_incref(काष्ठा flow_block_cb *block_cb)
अणु
	block_cb->refcnt++;
पूर्ण
EXPORT_SYMBOL(flow_block_cb_incref);

अचिन्हित पूर्णांक flow_block_cb_decref(काष्ठा flow_block_cb *block_cb)
अणु
	वापस --block_cb->refcnt;
पूर्ण
EXPORT_SYMBOL(flow_block_cb_decref);

bool flow_block_cb_is_busy(flow_setup_cb_t *cb, व्योम *cb_ident,
			   काष्ठा list_head *driver_block_list)
अणु
	काष्ठा flow_block_cb *block_cb;

	list_क्रम_each_entry(block_cb, driver_block_list, driver_list) अणु
		अगर (block_cb->cb == cb &&
		    block_cb->cb_ident == cb_ident)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL(flow_block_cb_is_busy);

पूर्णांक flow_block_cb_setup_simple(काष्ठा flow_block_offload *f,
			       काष्ठा list_head *driver_block_list,
			       flow_setup_cb_t *cb,
			       व्योम *cb_ident, व्योम *cb_priv,
			       bool ingress_only)
अणु
	काष्ठा flow_block_cb *block_cb;

	अगर (ingress_only &&
	    f->binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS)
		वापस -EOPNOTSUPP;

	f->driver_block_list = driver_block_list;

	चयन (f->command) अणु
	हाल FLOW_BLOCK_BIND:
		अगर (flow_block_cb_is_busy(cb, cb_ident, driver_block_list))
			वापस -EBUSY;

		block_cb = flow_block_cb_alloc(cb, cb_ident, cb_priv, शून्य);
		अगर (IS_ERR(block_cb))
			वापस PTR_ERR(block_cb);

		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list, driver_block_list);
		वापस 0;
	हाल FLOW_BLOCK_UNBIND:
		block_cb = flow_block_cb_lookup(f->block, cb, cb_ident);
		अगर (!block_cb)
			वापस -ENOENT;

		flow_block_cb_हटाओ(block_cb, f);
		list_del(&block_cb->driver_list);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(flow_block_cb_setup_simple);

अटल DEFINE_MUTEX(flow_indr_block_lock);
अटल LIST_HEAD(flow_block_indr_list);
अटल LIST_HEAD(flow_block_indr_dev_list);

काष्ठा flow_indr_dev अणु
	काष्ठा list_head		list;
	flow_indr_block_bind_cb_t	*cb;
	व्योम				*cb_priv;
	refcount_t			refcnt;
	काष्ठा rcu_head			rcu;
पूर्ण;

अटल काष्ठा flow_indr_dev *flow_indr_dev_alloc(flow_indr_block_bind_cb_t *cb,
						 व्योम *cb_priv)
अणु
	काष्ठा flow_indr_dev *indr_dev;

	indr_dev = kदो_स्मृति(माप(*indr_dev), GFP_KERNEL);
	अगर (!indr_dev)
		वापस शून्य;

	indr_dev->cb		= cb;
	indr_dev->cb_priv	= cb_priv;
	refcount_set(&indr_dev->refcnt, 1);

	वापस indr_dev;
पूर्ण

पूर्णांक flow_indr_dev_रेजिस्टर(flow_indr_block_bind_cb_t *cb, व्योम *cb_priv)
अणु
	काष्ठा flow_indr_dev *indr_dev;

	mutex_lock(&flow_indr_block_lock);
	list_क्रम_each_entry(indr_dev, &flow_block_indr_dev_list, list) अणु
		अगर (indr_dev->cb == cb &&
		    indr_dev->cb_priv == cb_priv) अणु
			refcount_inc(&indr_dev->refcnt);
			mutex_unlock(&flow_indr_block_lock);
			वापस 0;
		पूर्ण
	पूर्ण

	indr_dev = flow_indr_dev_alloc(cb, cb_priv);
	अगर (!indr_dev) अणु
		mutex_unlock(&flow_indr_block_lock);
		वापस -ENOMEM;
	पूर्ण

	list_add(&indr_dev->list, &flow_block_indr_dev_list);
	mutex_unlock(&flow_indr_block_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(flow_indr_dev_रेजिस्टर);

अटल व्योम __flow_block_indr_cleanup(व्योम (*release)(व्योम *cb_priv),
				      व्योम *cb_priv,
				      काष्ठा list_head *cleanup_list)
अणु
	काष्ठा flow_block_cb *this, *next;

	list_क्रम_each_entry_safe(this, next, &flow_block_indr_list, indr.list) अणु
		अगर (this->release == release &&
		    this->indr.cb_priv == cb_priv)
			list_move(&this->indr.list, cleanup_list);
	पूर्ण
पूर्ण

अटल व्योम flow_block_indr_notअगरy(काष्ठा list_head *cleanup_list)
अणु
	काष्ठा flow_block_cb *this, *next;

	list_क्रम_each_entry_safe(this, next, cleanup_list, indr.list) अणु
		list_del(&this->indr.list);
		this->indr.cleanup(this);
	पूर्ण
पूर्ण

व्योम flow_indr_dev_unरेजिस्टर(flow_indr_block_bind_cb_t *cb, व्योम *cb_priv,
			      व्योम (*release)(व्योम *cb_priv))
अणु
	काष्ठा flow_indr_dev *this, *next, *indr_dev = शून्य;
	LIST_HEAD(cleanup_list);

	mutex_lock(&flow_indr_block_lock);
	list_क्रम_each_entry_safe(this, next, &flow_block_indr_dev_list, list) अणु
		अगर (this->cb == cb &&
		    this->cb_priv == cb_priv &&
		    refcount_dec_and_test(&this->refcnt)) अणु
			indr_dev = this;
			list_del(&indr_dev->list);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!indr_dev) अणु
		mutex_unlock(&flow_indr_block_lock);
		वापस;
	पूर्ण

	__flow_block_indr_cleanup(release, cb_priv, &cleanup_list);
	mutex_unlock(&flow_indr_block_lock);

	flow_block_indr_notअगरy(&cleanup_list);
	kमुक्त(indr_dev);
पूर्ण
EXPORT_SYMBOL(flow_indr_dev_unरेजिस्टर);

अटल व्योम flow_block_indr_init(काष्ठा flow_block_cb *flow_block,
				 काष्ठा flow_block_offload *bo,
				 काष्ठा net_device *dev, काष्ठा Qdisc *sch, व्योम *data,
				 व्योम *cb_priv,
				 व्योम (*cleanup)(काष्ठा flow_block_cb *block_cb))
अणु
	flow_block->indr.binder_type = bo->binder_type;
	flow_block->indr.data = data;
	flow_block->indr.cb_priv = cb_priv;
	flow_block->indr.dev = dev;
	flow_block->indr.sch = sch;
	flow_block->indr.cleanup = cleanup;
पूर्ण

काष्ठा flow_block_cb *flow_indr_block_cb_alloc(flow_setup_cb_t *cb,
					       व्योम *cb_ident, व्योम *cb_priv,
					       व्योम (*release)(व्योम *cb_priv),
					       काष्ठा flow_block_offload *bo,
					       काष्ठा net_device *dev,
					       काष्ठा Qdisc *sch, व्योम *data,
					       व्योम *indr_cb_priv,
					       व्योम (*cleanup)(काष्ठा flow_block_cb *block_cb))
अणु
	काष्ठा flow_block_cb *block_cb;

	block_cb = flow_block_cb_alloc(cb, cb_ident, cb_priv, release);
	अगर (IS_ERR(block_cb))
		जाओ out;

	flow_block_indr_init(block_cb, bo, dev, sch, data, indr_cb_priv, cleanup);
	list_add(&block_cb->indr.list, &flow_block_indr_list);

out:
	वापस block_cb;
पूर्ण
EXPORT_SYMBOL(flow_indr_block_cb_alloc);

पूर्णांक flow_indr_dev_setup_offload(काष्ठा net_device *dev, काष्ठा Qdisc *sch,
				क्रमागत tc_setup_type type, व्योम *data,
				काष्ठा flow_block_offload *bo,
				व्योम (*cleanup)(काष्ठा flow_block_cb *block_cb))
अणु
	काष्ठा flow_indr_dev *this;

	mutex_lock(&flow_indr_block_lock);
	list_क्रम_each_entry(this, &flow_block_indr_dev_list, list)
		this->cb(dev, sch, this->cb_priv, type, bo, data, cleanup);

	mutex_unlock(&flow_indr_block_lock);

	वापस list_empty(&bo->cb_list) ? -EOPNOTSUPP : 0;
पूर्ण
EXPORT_SYMBOL(flow_indr_dev_setup_offload);
