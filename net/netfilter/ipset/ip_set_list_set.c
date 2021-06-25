<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2008-2013 Jozsef Kadlecsik <kadlec@netfilter.org> */

/* Kernel module implementing an IP set type: the list:set type */

#समावेश <linux/module.h>
#समावेश <linux/ip.h>
#समावेश <linux/rculist.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश <linux/netfilter/ipset/ip_set.h>
#समावेश <linux/netfilter/ipset/ip_set_list.h>

#घोषणा IPSET_TYPE_REV_MIN	0
/*				1    Counters support added */
/*				2    Comments support added */
#घोषणा IPSET_TYPE_REV_MAX	3 /* skbinfo support added */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jozsef Kadlecsik <kadlec@netfilter.org>");
IP_SET_MODULE_DESC("list:set", IPSET_TYPE_REV_MIN, IPSET_TYPE_REV_MAX);
MODULE_ALIAS("ip_set_list:set");

/* Member elements  */
काष्ठा set_elem अणु
	काष्ठा rcu_head rcu;
	काष्ठा list_head list;
	काष्ठा ip_set *set;	/* Sigh, in order to cleanup reference */
	ip_set_id_t id;
पूर्ण __aligned(__alignof__(u64));

काष्ठा set_adt_elem अणु
	ip_set_id_t id;
	ip_set_id_t refid;
	पूर्णांक beक्रमe;
पूर्ण;

/* Type काष्ठाure */
काष्ठा list_set अणु
	u32 size;		/* size of set list array */
	काष्ठा समयr_list gc;	/* garbage collection */
	काष्ठा ip_set *set;	/* attached to this ip_set */
	काष्ठा net *net;	/* namespace */
	काष्ठा list_head members; /* the set members */
पूर्ण;

अटल पूर्णांक
list_set_ktest(काष्ठा ip_set *set, स्थिर काष्ठा sk_buff *skb,
	       स्थिर काष्ठा xt_action_param *par,
	       काष्ठा ip_set_adt_opt *opt, स्थिर काष्ठा ip_set_ext *ext)
अणु
	काष्ठा list_set *map = set->data;
	काष्ठा ip_set_ext *mext = &opt->ext;
	काष्ठा set_elem *e;
	u32 flags = opt->cmdflags;
	पूर्णांक ret;

	/* Don't lookup sub-counters at all */
	opt->cmdflags &= ~IPSET_FLAG_MATCH_COUNTERS;
	अगर (opt->cmdflags & IPSET_FLAG_SKIP_SUBCOUNTER_UPDATE)
		opt->cmdflags |= IPSET_FLAG_SKIP_COUNTER_UPDATE;
	list_क्रम_each_entry_rcu(e, &map->members, list) अणु
		ret = ip_set_test(e->id, skb, par, opt);
		अगर (ret <= 0)
			जारी;
		अगर (ip_set_match_extensions(set, ext, mext, flags, e))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
list_set_kadd(काष्ठा ip_set *set, स्थिर काष्ठा sk_buff *skb,
	      स्थिर काष्ठा xt_action_param *par,
	      काष्ठा ip_set_adt_opt *opt, स्थिर काष्ठा ip_set_ext *ext)
अणु
	काष्ठा list_set *map = set->data;
	काष्ठा set_elem *e;
	पूर्णांक ret;

	list_क्रम_each_entry(e, &map->members, list) अणु
		अगर (SET_WITH_TIMEOUT(set) &&
		    ip_set_समयout_expired(ext_समयout(e, set)))
			जारी;
		ret = ip_set_add(e->id, skb, par, opt);
		अगर (ret == 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
list_set_kdel(काष्ठा ip_set *set, स्थिर काष्ठा sk_buff *skb,
	      स्थिर काष्ठा xt_action_param *par,
	      काष्ठा ip_set_adt_opt *opt, स्थिर काष्ठा ip_set_ext *ext)
अणु
	काष्ठा list_set *map = set->data;
	काष्ठा set_elem *e;
	पूर्णांक ret;

	list_क्रम_each_entry(e, &map->members, list) अणु
		अगर (SET_WITH_TIMEOUT(set) &&
		    ip_set_समयout_expired(ext_समयout(e, set)))
			जारी;
		ret = ip_set_del(e->id, skb, par, opt);
		अगर (ret == 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
list_set_kadt(काष्ठा ip_set *set, स्थिर काष्ठा sk_buff *skb,
	      स्थिर काष्ठा xt_action_param *par,
	      क्रमागत ipset_adt adt, काष्ठा ip_set_adt_opt *opt)
अणु
	काष्ठा ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);
	पूर्णांक ret = -EINVAL;

	rcu_पढ़ो_lock();
	चयन (adt) अणु
	हाल IPSET_TEST:
		ret = list_set_ktest(set, skb, par, opt, &ext);
		अवरोध;
	हाल IPSET_ADD:
		ret = list_set_kadd(set, skb, par, opt, &ext);
		अवरोध;
	हाल IPSET_DEL:
		ret = list_set_kdel(set, skb, par, opt, &ext);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/* Userspace पूर्णांकerfaces: we are रक्षित by the nfnl mutex */

अटल व्योम
__list_set_del_rcu(काष्ठा rcu_head * rcu)
अणु
	काष्ठा set_elem *e = container_of(rcu, काष्ठा set_elem, rcu);
	काष्ठा ip_set *set = e->set;

	ip_set_ext_destroy(set, e);
	kमुक्त(e);
पूर्ण

अटल व्योम
list_set_del(काष्ठा ip_set *set, काष्ठा set_elem *e)
अणु
	काष्ठा list_set *map = set->data;

	set->elements--;
	list_del_rcu(&e->list);
	ip_set_put_byindex(map->net, e->id);
	call_rcu(&e->rcu, __list_set_del_rcu);
पूर्ण

अटल व्योम
list_set_replace(काष्ठा ip_set *set, काष्ठा set_elem *e, काष्ठा set_elem *old)
अणु
	काष्ठा list_set *map = set->data;

	list_replace_rcu(&old->list, &e->list);
	ip_set_put_byindex(map->net, old->id);
	call_rcu(&old->rcu, __list_set_del_rcu);
पूर्ण

अटल व्योम
set_cleanup_entries(काष्ठा ip_set *set)
अणु
	काष्ठा list_set *map = set->data;
	काष्ठा set_elem *e, *n;

	list_क्रम_each_entry_safe(e, n, &map->members, list)
		अगर (ip_set_समयout_expired(ext_समयout(e, set)))
			list_set_del(set, e);
पूर्ण

अटल पूर्णांक
list_set_utest(काष्ठा ip_set *set, व्योम *value, स्थिर काष्ठा ip_set_ext *ext,
	       काष्ठा ip_set_ext *mext, u32 flags)
अणु
	काष्ठा list_set *map = set->data;
	काष्ठा set_adt_elem *d = value;
	काष्ठा set_elem *e, *next, *prev = शून्य;
	पूर्णांक ret;

	list_क्रम_each_entry(e, &map->members, list) अणु
		अगर (SET_WITH_TIMEOUT(set) &&
		    ip_set_समयout_expired(ext_समयout(e, set)))
			जारी;
		अन्यथा अगर (e->id != d->id) अणु
			prev = e;
			जारी;
		पूर्ण

		अगर (d->beक्रमe == 0) अणु
			ret = 1;
		पूर्ण अन्यथा अगर (d->beक्रमe > 0) अणु
			next = list_next_entry(e, list);
			ret = !list_is_last(&e->list, &map->members) &&
			      next->id == d->refid;
		पूर्ण अन्यथा अणु
			ret = prev && prev->id == d->refid;
		पूर्ण
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
list_set_init_extensions(काष्ठा ip_set *set, स्थिर काष्ठा ip_set_ext *ext,
			 काष्ठा set_elem *e)
अणु
	अगर (SET_WITH_COUNTER(set))
		ip_set_init_counter(ext_counter(e, set), ext);
	अगर (SET_WITH_COMMENT(set))
		ip_set_init_comment(set, ext_comment(e, set), ext);
	अगर (SET_WITH_SKBINFO(set))
		ip_set_init_skbinfo(ext_skbinfo(e, set), ext);
	/* Update समयout last */
	अगर (SET_WITH_TIMEOUT(set))
		ip_set_समयout_set(ext_समयout(e, set), ext->समयout);
पूर्ण

अटल पूर्णांक
list_set_uadd(काष्ठा ip_set *set, व्योम *value, स्थिर काष्ठा ip_set_ext *ext,
	      काष्ठा ip_set_ext *mext, u32 flags)
अणु
	काष्ठा list_set *map = set->data;
	काष्ठा set_adt_elem *d = value;
	काष्ठा set_elem *e, *n, *prev, *next;
	bool flag_exist = flags & IPSET_FLAG_EXIST;

	/* Find where to add the new entry */
	n = prev = next = शून्य;
	list_क्रम_each_entry(e, &map->members, list) अणु
		अगर (SET_WITH_TIMEOUT(set) &&
		    ip_set_समयout_expired(ext_समयout(e, set)))
			जारी;
		अन्यथा अगर (d->id == e->id)
			n = e;
		अन्यथा अगर (d->beक्रमe == 0 || e->id != d->refid)
			जारी;
		अन्यथा अगर (d->beक्रमe > 0)
			next = e;
		अन्यथा
			prev = e;
	पूर्ण

	/* If beक्रमe/after is used on an empty set */
	अगर ((d->beक्रमe > 0 && !next) ||
	    (d->beक्रमe < 0 && !prev))
		वापस -IPSET_ERR_REF_EXIST;

	/* Re-add alपढ़ोy existing element */
	अगर (n) अणु
		अगर (!flag_exist)
			वापस -IPSET_ERR_EXIST;
		/* Update extensions */
		ip_set_ext_destroy(set, n);
		list_set_init_extensions(set, ext, n);

		/* Set is alपढ़ोy added to the list */
		ip_set_put_byindex(map->net, d->id);
		वापस 0;
	पूर्ण
	/* Add new entry */
	अगर (d->beक्रमe == 0) अणु
		/* Append  */
		n = list_empty(&map->members) ? शून्य :
		    list_last_entry(&map->members, काष्ठा set_elem, list);
	पूर्ण अन्यथा अगर (d->beक्रमe > 0) अणु
		/* Insert after next element */
		अगर (!list_is_last(&next->list, &map->members))
			n = list_next_entry(next, list);
	पूर्ण अन्यथा अणु
		/* Insert beक्रमe prev element */
		अगर (prev->list.prev != &map->members)
			n = list_prev_entry(prev, list);
	पूर्ण
	/* Can we replace a समयd out entry? */
	अगर (n &&
	    !(SET_WITH_TIMEOUT(set) &&
	      ip_set_समयout_expired(ext_समयout(n, set))))
		n = शून्य;

	e = kzalloc(set->dsize, GFP_ATOMIC);
	अगर (!e)
		वापस -ENOMEM;
	e->id = d->id;
	e->set = set;
	INIT_LIST_HEAD(&e->list);
	list_set_init_extensions(set, ext, e);
	अगर (n)
		list_set_replace(set, e, n);
	अन्यथा अगर (next)
		list_add_tail_rcu(&e->list, &next->list);
	अन्यथा अगर (prev)
		list_add_rcu(&e->list, &prev->list);
	अन्यथा
		list_add_tail_rcu(&e->list, &map->members);
	set->elements++;

	वापस 0;
पूर्ण

अटल पूर्णांक
list_set_udel(काष्ठा ip_set *set, व्योम *value, स्थिर काष्ठा ip_set_ext *ext,
	      काष्ठा ip_set_ext *mext, u32 flags)
अणु
	काष्ठा list_set *map = set->data;
	काष्ठा set_adt_elem *d = value;
	काष्ठा set_elem *e, *next, *prev = शून्य;

	list_क्रम_each_entry(e, &map->members, list) अणु
		अगर (SET_WITH_TIMEOUT(set) &&
		    ip_set_समयout_expired(ext_समयout(e, set)))
			जारी;
		अन्यथा अगर (e->id != d->id) अणु
			prev = e;
			जारी;
		पूर्ण

		अगर (d->beक्रमe > 0) अणु
			next = list_next_entry(e, list);
			अगर (list_is_last(&e->list, &map->members) ||
			    next->id != d->refid)
				वापस -IPSET_ERR_REF_EXIST;
		पूर्ण अन्यथा अगर (d->beक्रमe < 0) अणु
			अगर (!prev || prev->id != d->refid)
				वापस -IPSET_ERR_REF_EXIST;
		पूर्ण
		list_set_del(set, e);
		वापस 0;
	पूर्ण
	वापस d->beक्रमe != 0 ? -IPSET_ERR_REF_EXIST : -IPSET_ERR_EXIST;
पूर्ण

अटल पूर्णांक
list_set_uadt(काष्ठा ip_set *set, काष्ठा nlattr *tb[],
	      क्रमागत ipset_adt adt, u32 *lineno, u32 flags, bool retried)
अणु
	काष्ठा list_set *map = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	काष्ठा set_adt_elem e = अणु .refid = IPSET_INVALID_ID पूर्ण;
	काष्ठा ip_set_ext ext = IP_SET_INIT_UEXT(set);
	काष्ठा ip_set *s;
	पूर्णांक ret = 0;

	अगर (tb[IPSET_ATTR_LINENO])
		*lineno = nla_get_u32(tb[IPSET_ATTR_LINENO]);

	अगर (unlikely(!tb[IPSET_ATTR_NAME] ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_CADT_FLAGS)))
		वापस -IPSET_ERR_PROTOCOL;

	ret = ip_set_get_extensions(set, tb, &ext);
	अगर (ret)
		वापस ret;
	e.id = ip_set_get_byname(map->net, nla_data(tb[IPSET_ATTR_NAME]), &s);
	अगर (e.id == IPSET_INVALID_ID)
		वापस -IPSET_ERR_NAME;
	/* "Loop detection" */
	अगर (s->type->features & IPSET_TYPE_NAME) अणु
		ret = -IPSET_ERR_LOOP;
		जाओ finish;
	पूर्ण

	अगर (tb[IPSET_ATTR_CADT_FLAGS]) अणु
		u32 f = ip_set_get_h32(tb[IPSET_ATTR_CADT_FLAGS]);

		e.beक्रमe = f & IPSET_FLAG_BEFORE;
	पूर्ण

	अगर (e.beक्रमe && !tb[IPSET_ATTR_NAMEREF]) अणु
		ret = -IPSET_ERR_BEFORE;
		जाओ finish;
	पूर्ण

	अगर (tb[IPSET_ATTR_NAMEREF]) अणु
		e.refid = ip_set_get_byname(map->net,
					    nla_data(tb[IPSET_ATTR_NAMEREF]),
					    &s);
		अगर (e.refid == IPSET_INVALID_ID) अणु
			ret = -IPSET_ERR_NAMEREF;
			जाओ finish;
		पूर्ण
		अगर (!e.beक्रमe)
			e.beक्रमe = -1;
	पूर्ण
	अगर (adt != IPSET_TEST && SET_WITH_TIMEOUT(set))
		set_cleanup_entries(set);

	ret = adtfn(set, &e, &ext, &ext, flags);

finish:
	अगर (e.refid != IPSET_INVALID_ID)
		ip_set_put_byindex(map->net, e.refid);
	अगर (adt != IPSET_ADD || ret)
		ip_set_put_byindex(map->net, e.id);

	वापस ip_set_eexist(ret, flags) ? 0 : ret;
पूर्ण

अटल व्योम
list_set_flush(काष्ठा ip_set *set)
अणु
	काष्ठा list_set *map = set->data;
	काष्ठा set_elem *e, *n;

	list_क्रम_each_entry_safe(e, n, &map->members, list)
		list_set_del(set, e);
	set->elements = 0;
	set->ext_size = 0;
पूर्ण

अटल व्योम
list_set_destroy(काष्ठा ip_set *set)
अणु
	काष्ठा list_set *map = set->data;
	काष्ठा set_elem *e, *n;

	अगर (SET_WITH_TIMEOUT(set))
		del_समयr_sync(&map->gc);

	list_क्रम_each_entry_safe(e, n, &map->members, list) अणु
		list_del(&e->list);
		ip_set_put_byindex(map->net, e->id);
		ip_set_ext_destroy(set, e);
		kमुक्त(e);
	पूर्ण
	kमुक्त(map);

	set->data = शून्य;
पूर्ण

/* Calculate the actual memory size of the set data */
अटल माप_प्रकार
list_set_memsize(स्थिर काष्ठा list_set *map, माप_प्रकार dsize)
अणु
	काष्ठा set_elem *e;
	u32 n = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(e, &map->members, list)
		n++;
	rcu_पढ़ो_unlock();

	वापस (माप(*map) + n * dsize);
पूर्ण

अटल पूर्णांक
list_set_head(काष्ठा ip_set *set, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा list_set *map = set->data;
	काष्ठा nlattr *nested;
	माप_प्रकार memsize = list_set_memsize(map, set->dsize) + set->ext_size;

	nested = nla_nest_start(skb, IPSET_ATTR_DATA);
	अगर (!nested)
		जाओ nla_put_failure;
	अगर (nla_put_net32(skb, IPSET_ATTR_SIZE, htonl(map->size)) ||
	    nla_put_net32(skb, IPSET_ATTR_REFERENCES, htonl(set->ref)) ||
	    nla_put_net32(skb, IPSET_ATTR_MEMSIZE, htonl(memsize)) ||
	    nla_put_net32(skb, IPSET_ATTR_ELEMENTS, htonl(set->elements)))
		जाओ nla_put_failure;
	अगर (unlikely(ip_set_put_flags(skb, set)))
		जाओ nla_put_failure;
	nla_nest_end(skb, nested);

	वापस 0;
nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक
list_set_list(स्थिर काष्ठा ip_set *set,
	      काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा list_set *map = set->data;
	काष्ठा nlattr *atd, *nested;
	u32 i = 0, first = cb->args[IPSET_CB_ARG0];
	अक्षर name[IPSET_MAXNAMELEN];
	काष्ठा set_elem *e;
	पूर्णांक ret = 0;

	atd = nla_nest_start(skb, IPSET_ATTR_ADT);
	अगर (!atd)
		वापस -EMSGSIZE;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(e, &map->members, list) अणु
		अगर (i < first ||
		    (SET_WITH_TIMEOUT(set) &&
		     ip_set_समयout_expired(ext_समयout(e, set)))) अणु
			i++;
			जारी;
		पूर्ण
		nested = nla_nest_start(skb, IPSET_ATTR_DATA);
		अगर (!nested)
			जाओ nla_put_failure;
		ip_set_name_byindex(map->net, e->id, name);
		अगर (nla_put_string(skb, IPSET_ATTR_NAME, name))
			जाओ nla_put_failure;
		अगर (ip_set_put_extensions(skb, set, e, true))
			जाओ nla_put_failure;
		nla_nest_end(skb, nested);
		i++;
	पूर्ण

	nla_nest_end(skb, atd);
	/* Set listing finished */
	cb->args[IPSET_CB_ARG0] = 0;
	जाओ out;

nla_put_failure:
	nla_nest_cancel(skb, nested);
	अगर (unlikely(i == first)) अणु
		nla_nest_cancel(skb, atd);
		cb->args[IPSET_CB_ARG0] = 0;
		ret = -EMSGSIZE;
	पूर्ण अन्यथा अणु
		cb->args[IPSET_CB_ARG0] = i;
		nla_nest_end(skb, atd);
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल bool
list_set_same_set(स्थिर काष्ठा ip_set *a, स्थिर काष्ठा ip_set *b)
अणु
	स्थिर काष्ठा list_set *x = a->data;
	स्थिर काष्ठा list_set *y = b->data;

	वापस x->size == y->size &&
	       a->समयout == b->समयout &&
	       a->extensions == b->extensions;
पूर्ण

अटल स्थिर काष्ठा ip_set_type_variant set_variant = अणु
	.kadt	= list_set_kadt,
	.uadt	= list_set_uadt,
	.adt	= अणु
		[IPSET_ADD] = list_set_uadd,
		[IPSET_DEL] = list_set_udel,
		[IPSET_TEST] = list_set_utest,
	पूर्ण,
	.destroy = list_set_destroy,
	.flush	= list_set_flush,
	.head	= list_set_head,
	.list	= list_set_list,
	.same_set = list_set_same_set,
पूर्ण;

अटल व्योम
list_set_gc(काष्ठा समयr_list *t)
अणु
	काष्ठा list_set *map = from_समयr(map, t, gc);
	काष्ठा ip_set *set = map->set;

	spin_lock_bh(&set->lock);
	set_cleanup_entries(set);
	spin_unlock_bh(&set->lock);

	map->gc.expires = jअगरfies + IPSET_GC_PERIOD(set->समयout) * HZ;
	add_समयr(&map->gc);
पूर्ण

अटल व्योम
list_set_gc_init(काष्ठा ip_set *set, व्योम (*gc)(काष्ठा समयr_list *t))
अणु
	काष्ठा list_set *map = set->data;

	समयr_setup(&map->gc, gc, 0);
	mod_समयr(&map->gc, jअगरfies + IPSET_GC_PERIOD(set->समयout) * HZ);
पूर्ण

/* Create list:set type of sets */

अटल bool
init_list_set(काष्ठा net *net, काष्ठा ip_set *set, u32 size)
अणु
	काष्ठा list_set *map;

	map = kzalloc(माप(*map), GFP_KERNEL);
	अगर (!map)
		वापस false;

	map->size = size;
	map->net = net;
	map->set = set;
	INIT_LIST_HEAD(&map->members);
	set->data = map;

	वापस true;
पूर्ण

अटल पूर्णांक
list_set_create(काष्ठा net *net, काष्ठा ip_set *set, काष्ठा nlattr *tb[],
		u32 flags)
अणु
	u32 size = IP_SET_LIST_DEFAULT_SIZE;

	अगर (unlikely(!ip_set_optattr_netorder(tb, IPSET_ATTR_SIZE) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_TIMEOUT) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_CADT_FLAGS)))
		वापस -IPSET_ERR_PROTOCOL;

	अगर (tb[IPSET_ATTR_SIZE])
		size = ip_set_get_h32(tb[IPSET_ATTR_SIZE]);
	अगर (size < IP_SET_LIST_MIN_SIZE)
		size = IP_SET_LIST_MIN_SIZE;

	set->variant = &set_variant;
	set->dsize = ip_set_elem_len(set, tb, माप(काष्ठा set_elem),
				     __alignof__(काष्ठा set_elem));
	अगर (!init_list_set(net, set, size))
		वापस -ENOMEM;
	अगर (tb[IPSET_ATTR_TIMEOUT]) अणु
		set->समयout = ip_set_समयout_uget(tb[IPSET_ATTR_TIMEOUT]);
		list_set_gc_init(set, list_set_gc);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा ip_set_type list_set_type __पढ़ो_mostly = अणु
	.name		= "list:set",
	.protocol	= IPSET_PROTOCOL,
	.features	= IPSET_TYPE_NAME | IPSET_DUMP_LAST,
	.dimension	= IPSET_DIM_ONE,
	.family		= NFPROTO_UNSPEC,
	.revision_min	= IPSET_TYPE_REV_MIN,
	.revision_max	= IPSET_TYPE_REV_MAX,
	.create		= list_set_create,
	.create_policy	= अणु
		[IPSET_ATTR_SIZE]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_TIMEOUT]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_CADT_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
	पूर्ण,
	.adt_policy	= अणु
		[IPSET_ATTR_NAME]	= अणु .type = NLA_STRING,
					    .len = IPSET_MAXNAMELEN पूर्ण,
		[IPSET_ATTR_NAMEREF]	= अणु .type = NLA_STRING,
					    .len = IPSET_MAXNAMELEN पूर्ण,
		[IPSET_ATTR_TIMEOUT]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_LINENO]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_CADT_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_BYTES]	= अणु .type = NLA_U64 पूर्ण,
		[IPSET_ATTR_PACKETS]	= अणु .type = NLA_U64 पूर्ण,
		[IPSET_ATTR_COMMENT]	= अणु .type = NLA_NUL_STRING,
					    .len  = IPSET_MAX_COMMENT_SIZE पूर्ण,
		[IPSET_ATTR_SKBMARK]	= अणु .type = NLA_U64 पूर्ण,
		[IPSET_ATTR_SKBPRIO]	= अणु .type = NLA_U32 पूर्ण,
		[IPSET_ATTR_SKBQUEUE]	= अणु .type = NLA_U16 पूर्ण,
	पूर्ण,
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init
list_set_init(व्योम)
अणु
	वापस ip_set_type_रेजिस्टर(&list_set_type);
पूर्ण

अटल व्योम __निकास
list_set_fini(व्योम)
अणु
	rcu_barrier();
	ip_set_type_unरेजिस्टर(&list_set_type);
पूर्ण

module_init(list_set_init);
module_निकास(list_set_fini);
