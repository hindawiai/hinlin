<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (C) 2013 Jozsef Kadlecsik <kadlec@netfilter.org> */

#अगर_अघोषित __IP_SET_BITMAP_IP_GEN_H
#घोषणा __IP_SET_BITMAP_IP_GEN_H

#घोषणा mtype_करो_test		IPSET_TOKEN(MTYPE, _करो_test)
#घोषणा mtype_gc_test		IPSET_TOKEN(MTYPE, _gc_test)
#घोषणा mtype_is_filled		IPSET_TOKEN(MTYPE, _is_filled)
#घोषणा mtype_करो_add		IPSET_TOKEN(MTYPE, _करो_add)
#घोषणा mtype_ext_cleanup	IPSET_TOKEN(MTYPE, _ext_cleanup)
#घोषणा mtype_करो_del		IPSET_TOKEN(MTYPE, _करो_del)
#घोषणा mtype_करो_list		IPSET_TOKEN(MTYPE, _करो_list)
#घोषणा mtype_करो_head		IPSET_TOKEN(MTYPE, _करो_head)
#घोषणा mtype_adt_elem		IPSET_TOKEN(MTYPE, _adt_elem)
#घोषणा mtype_add_समयout	IPSET_TOKEN(MTYPE, _add_समयout)
#घोषणा mtype_gc_init		IPSET_TOKEN(MTYPE, _gc_init)
#घोषणा mtype_kadt		IPSET_TOKEN(MTYPE, _kadt)
#घोषणा mtype_uadt		IPSET_TOKEN(MTYPE, _uadt)
#घोषणा mtype_destroy		IPSET_TOKEN(MTYPE, _destroy)
#घोषणा mtype_memsize		IPSET_TOKEN(MTYPE, _memsize)
#घोषणा mtype_flush		IPSET_TOKEN(MTYPE, _flush)
#घोषणा mtype_head		IPSET_TOKEN(MTYPE, _head)
#घोषणा mtype_same_set		IPSET_TOKEN(MTYPE, _same_set)
#घोषणा mtype_elem		IPSET_TOKEN(MTYPE, _elem)
#घोषणा mtype_test		IPSET_TOKEN(MTYPE, _test)
#घोषणा mtype_add		IPSET_TOKEN(MTYPE, _add)
#घोषणा mtype_del		IPSET_TOKEN(MTYPE, _del)
#घोषणा mtype_list		IPSET_TOKEN(MTYPE, _list)
#घोषणा mtype_gc		IPSET_TOKEN(MTYPE, _gc)
#घोषणा mtype			MTYPE

#घोषणा get_ext(set, map, id)	((map)->extensions + ((set)->dsize * (id)))

अटल व्योम
mtype_gc_init(काष्ठा ip_set *set, व्योम (*gc)(काष्ठा समयr_list *t))
अणु
	काष्ठा mtype *map = set->data;

	समयr_setup(&map->gc, gc, 0);
	mod_समयr(&map->gc, jअगरfies + IPSET_GC_PERIOD(set->समयout) * HZ);
पूर्ण

अटल व्योम
mtype_ext_cleanup(काष्ठा ip_set *set)
अणु
	काष्ठा mtype *map = set->data;
	u32 id;

	क्रम (id = 0; id < map->elements; id++)
		अगर (test_bit(id, map->members))
			ip_set_ext_destroy(set, get_ext(set, map, id));
पूर्ण

अटल व्योम
mtype_destroy(काष्ठा ip_set *set)
अणु
	काष्ठा mtype *map = set->data;

	अगर (SET_WITH_TIMEOUT(set))
		del_समयr_sync(&map->gc);

	अगर (set->dsize && set->extensions & IPSET_EXT_DESTROY)
		mtype_ext_cleanup(set);
	ip_set_मुक्त(map->members);
	ip_set_मुक्त(map);

	set->data = शून्य;
पूर्ण

अटल व्योम
mtype_flush(काष्ठा ip_set *set)
अणु
	काष्ठा mtype *map = set->data;

	अगर (set->extensions & IPSET_EXT_DESTROY)
		mtype_ext_cleanup(set);
	biपंचांगap_zero(map->members, map->elements);
	set->elements = 0;
	set->ext_size = 0;
पूर्ण

/* Calculate the actual memory size of the set data */
अटल माप_प्रकार
mtype_memsize(स्थिर काष्ठा mtype *map, माप_प्रकार dsize)
अणु
	वापस माप(*map) + map->memsize +
	       map->elements * dsize;
पूर्ण

अटल पूर्णांक
mtype_head(काष्ठा ip_set *set, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा mtype *map = set->data;
	काष्ठा nlattr *nested;
	माप_प्रकार memsize = mtype_memsize(map, set->dsize) + set->ext_size;

	nested = nla_nest_start(skb, IPSET_ATTR_DATA);
	अगर (!nested)
		जाओ nla_put_failure;
	अगर (mtype_करो_head(skb, map) ||
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
mtype_test(काष्ठा ip_set *set, व्योम *value, स्थिर काष्ठा ip_set_ext *ext,
	   काष्ठा ip_set_ext *mext, u32 flags)
अणु
	काष्ठा mtype *map = set->data;
	स्थिर काष्ठा mtype_adt_elem *e = value;
	व्योम *x = get_ext(set, map, e->id);
	पूर्णांक ret = mtype_करो_test(e, map, set->dsize);

	अगर (ret <= 0)
		वापस ret;
	वापस ip_set_match_extensions(set, ext, mext, flags, x);
पूर्ण

अटल पूर्णांक
mtype_add(काष्ठा ip_set *set, व्योम *value, स्थिर काष्ठा ip_set_ext *ext,
	  काष्ठा ip_set_ext *mext, u32 flags)
अणु
	काष्ठा mtype *map = set->data;
	स्थिर काष्ठा mtype_adt_elem *e = value;
	व्योम *x = get_ext(set, map, e->id);
	पूर्णांक ret = mtype_करो_add(e, map, flags, set->dsize);

	अगर (ret == IPSET_ADD_FAILED) अणु
		अगर (SET_WITH_TIMEOUT(set) &&
		    ip_set_समयout_expired(ext_समयout(x, set))) अणु
			set->elements--;
			ret = 0;
		पूर्ण अन्यथा अगर (!(flags & IPSET_FLAG_EXIST)) अणु
			set_bit(e->id, map->members);
			वापस -IPSET_ERR_EXIST;
		पूर्ण
		/* Element is re-added, cleanup extensions */
		ip_set_ext_destroy(set, x);
	पूर्ण
	अगर (ret > 0)
		set->elements--;

	अगर (SET_WITH_TIMEOUT(set))
#अगर_घोषित IP_SET_BITMAP_STORED_TIMEOUT
		mtype_add_समयout(ext_समयout(x, set), e, ext, set, map, ret);
#अन्यथा
		ip_set_समयout_set(ext_समयout(x, set), ext->समयout);
#पूर्ण_अगर

	अगर (SET_WITH_COUNTER(set))
		ip_set_init_counter(ext_counter(x, set), ext);
	अगर (SET_WITH_COMMENT(set))
		ip_set_init_comment(set, ext_comment(x, set), ext);
	अगर (SET_WITH_SKBINFO(set))
		ip_set_init_skbinfo(ext_skbinfo(x, set), ext);

	/* Activate element */
	set_bit(e->id, map->members);
	set->elements++;

	वापस 0;
पूर्ण

अटल पूर्णांक
mtype_del(काष्ठा ip_set *set, व्योम *value, स्थिर काष्ठा ip_set_ext *ext,
	  काष्ठा ip_set_ext *mext, u32 flags)
अणु
	काष्ठा mtype *map = set->data;
	स्थिर काष्ठा mtype_adt_elem *e = value;
	व्योम *x = get_ext(set, map, e->id);

	अगर (mtype_करो_del(e, map))
		वापस -IPSET_ERR_EXIST;

	ip_set_ext_destroy(set, x);
	set->elements--;
	अगर (SET_WITH_TIMEOUT(set) &&
	    ip_set_समयout_expired(ext_समयout(x, set)))
		वापस -IPSET_ERR_EXIST;

	वापस 0;
पूर्ण

#अगर_अघोषित IP_SET_BITMAP_STORED_TIMEOUT
अटल bool
mtype_is_filled(स्थिर काष्ठा mtype_elem *x)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
mtype_list(स्थिर काष्ठा ip_set *set,
	   काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा mtype *map = set->data;
	काष्ठा nlattr *adt, *nested;
	व्योम *x;
	u32 id, first = cb->args[IPSET_CB_ARG0];
	पूर्णांक ret = 0;

	adt = nla_nest_start(skb, IPSET_ATTR_ADT);
	अगर (!adt)
		वापस -EMSGSIZE;
	/* Extensions may be replaced */
	rcu_पढ़ो_lock();
	क्रम (; cb->args[IPSET_CB_ARG0] < map->elements;
	     cb->args[IPSET_CB_ARG0]++) अणु
		cond_resched_rcu();
		id = cb->args[IPSET_CB_ARG0];
		x = get_ext(set, map, id);
		अगर (!test_bit(id, map->members) ||
		    (SET_WITH_TIMEOUT(set) &&
#अगर_घोषित IP_SET_BITMAP_STORED_TIMEOUT
		     mtype_is_filled(x) &&
#पूर्ण_अगर
		     ip_set_समयout_expired(ext_समयout(x, set))))
			जारी;
		nested = nla_nest_start(skb, IPSET_ATTR_DATA);
		अगर (!nested) अणु
			अगर (id == first) अणु
				nla_nest_cancel(skb, adt);
				ret = -EMSGSIZE;
				जाओ out;
			पूर्ण

			जाओ nla_put_failure;
		पूर्ण
		अगर (mtype_करो_list(skb, map, id, set->dsize))
			जाओ nla_put_failure;
		अगर (ip_set_put_extensions(skb, set, x, mtype_is_filled(x)))
			जाओ nla_put_failure;
		nla_nest_end(skb, nested);
	पूर्ण
	nla_nest_end(skb, adt);

	/* Set listing finished */
	cb->args[IPSET_CB_ARG0] = 0;

	जाओ out;

nla_put_failure:
	nla_nest_cancel(skb, nested);
	अगर (unlikely(id == first)) अणु
		cb->args[IPSET_CB_ARG0] = 0;
		ret = -EMSGSIZE;
	पूर्ण
	nla_nest_end(skb, adt);
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल व्योम
mtype_gc(काष्ठा समयr_list *t)
अणु
	काष्ठा mtype *map = from_समयr(map, t, gc);
	काष्ठा ip_set *set = map->set;
	व्योम *x;
	u32 id;

	/* We run parallel with other पढ़ोers (test element)
	 * but adding/deleting new entries is locked out
	 */
	spin_lock_bh(&set->lock);
	क्रम (id = 0; id < map->elements; id++)
		अगर (mtype_gc_test(id, map, set->dsize)) अणु
			x = get_ext(set, map, id);
			अगर (ip_set_समयout_expired(ext_समयout(x, set))) अणु
				clear_bit(id, map->members);
				ip_set_ext_destroy(set, x);
				set->elements--;
			पूर्ण
		पूर्ण
	spin_unlock_bh(&set->lock);

	map->gc.expires = jअगरfies + IPSET_GC_PERIOD(set->समयout) * HZ;
	add_समयr(&map->gc);
पूर्ण

अटल स्थिर काष्ठा ip_set_type_variant mtype = अणु
	.kadt	= mtype_kadt,
	.uadt	= mtype_uadt,
	.adt	= अणु
		[IPSET_ADD] = mtype_add,
		[IPSET_DEL] = mtype_del,
		[IPSET_TEST] = mtype_test,
	पूर्ण,
	.destroy = mtype_destroy,
	.flush	= mtype_flush,
	.head	= mtype_head,
	.list	= mtype_list,
	.same_set = mtype_same_set,
पूर्ण;

#पूर्ण_अगर /* __IP_SET_BITMAP_IP_GEN_H */
