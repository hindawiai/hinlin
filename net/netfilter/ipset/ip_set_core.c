<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2000-2002 Joakim Axelsson <gozem@linux.nu>
 *                         Patrick Schaaf <bof@bof.de>
 * Copyright (C) 2003-2013 Jozsef Kadlecsik <kadlec@netfilter.org>
 */

/* Kernel module क्रम IP set management */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/ip.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rculist.h>
#समावेश <net/netlink.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/ipset/ip_set.h>

अटल LIST_HEAD(ip_set_type_list);		/* all रेजिस्टरed set types */
अटल DEFINE_MUTEX(ip_set_type_mutex);		/* protects ip_set_type_list */
अटल DEFINE_RWLOCK(ip_set_ref_lock);		/* protects the set refs */

काष्ठा ip_set_net अणु
	काष्ठा ip_set * __rcu *ip_set_list;	/* all inभागidual sets */
	ip_set_id_t	ip_set_max;	/* max number of sets */
	bool		is_deleted;	/* deleted by ip_set_net_निकास */
	bool		is_destroyed;	/* all sets are destroyed */
पूर्ण;

अटल अचिन्हित पूर्णांक ip_set_net_id __पढ़ो_mostly;

अटल काष्ठा ip_set_net *ip_set_pernet(काष्ठा net *net)
अणु
	वापस net_generic(net, ip_set_net_id);
पूर्ण

#घोषणा IP_SET_INC	64
#घोषणा STRNCMP(a, b)	(म_भेदन(a, b, IPSET_MAXNAMELEN) == 0)

अटल अचिन्हित पूर्णांक max_sets;

module_param(max_sets, पूर्णांक, 0600);
MODULE_PARM_DESC(max_sets, "maximal number of sets");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jozsef Kadlecsik <kadlec@netfilter.org>");
MODULE_DESCRIPTION("core IP set support");
MODULE_ALIAS_NFNL_SUBSYS(NFNL_SUBSYS_IPSET);

/* When the nfnl mutex or ip_set_ref_lock is held: */
#घोषणा ip_set_dereference(p)		\
	rcu_dereference_रक्षित(p,	\
		lockdep_nfnl_is_held(NFNL_SUBSYS_IPSET) || \
		lockdep_is_held(&ip_set_ref_lock))
#घोषणा ip_set(inst, id)		\
	ip_set_dereference((inst)->ip_set_list)[id]
#घोषणा ip_set_ref_netlink(inst,id)	\
	rcu_dereference_raw((inst)->ip_set_list)[id]

/* The set types are implemented in modules and रेजिस्टरed set types
 * can be found in ip_set_type_list. Adding/deleting types is
 * serialized by ip_set_type_mutex.
 */

अटल व्योम
ip_set_type_lock(व्योम)
अणु
	mutex_lock(&ip_set_type_mutex);
पूर्ण

अटल व्योम
ip_set_type_unlock(व्योम)
अणु
	mutex_unlock(&ip_set_type_mutex);
पूर्ण

/* Register and deरेजिस्टर settype */

अटल काष्ठा ip_set_type *
find_set_type(स्थिर अक्षर *name, u8 family, u8 revision)
अणु
	काष्ठा ip_set_type *type;

	list_क्रम_each_entry_rcu(type, &ip_set_type_list, list,
				lockdep_is_held(&ip_set_type_mutex))
		अगर (STRNCMP(type->name, name) &&
		    (type->family == family ||
		     type->family == NFPROTO_UNSPEC) &&
		    revision >= type->revision_min &&
		    revision <= type->revision_max)
			वापस type;
	वापस शून्य;
पूर्ण

/* Unlock, try to load a set type module and lock again */
अटल bool
load_settype(स्थिर अक्षर *name)
अणु
	nfnl_unlock(NFNL_SUBSYS_IPSET);
	pr_debug("try to load ip_set_%s\n", name);
	अगर (request_module("ip_set_%s", name) < 0) अणु
		pr_warn("Can't find ip_set type %s\n", name);
		nfnl_lock(NFNL_SUBSYS_IPSET);
		वापस false;
	पूर्ण
	nfnl_lock(NFNL_SUBSYS_IPSET);
	वापस true;
पूर्ण

/* Find a set type and reference it */
#घोषणा find_set_type_get(name, family, revision, found)	\
	__find_set_type_get(name, family, revision, found, false)

अटल पूर्णांक
__find_set_type_get(स्थिर अक्षर *name, u8 family, u8 revision,
		    काष्ठा ip_set_type **found, bool retry)
अणु
	काष्ठा ip_set_type *type;
	पूर्णांक err;

	अगर (retry && !load_settype(name))
		वापस -IPSET_ERR_FIND_TYPE;

	rcu_पढ़ो_lock();
	*found = find_set_type(name, family, revision);
	अगर (*found) अणु
		err = !try_module_get((*found)->me) ? -EFAULT : 0;
		जाओ unlock;
	पूर्ण
	/* Make sure the type is alपढ़ोy loaded
	 * but we करोn't support the revision
	 */
	list_क्रम_each_entry_rcu(type, &ip_set_type_list, list)
		अगर (STRNCMP(type->name, name)) अणु
			err = -IPSET_ERR_FIND_TYPE;
			जाओ unlock;
		पूर्ण
	rcu_पढ़ो_unlock();

	वापस retry ? -IPSET_ERR_FIND_TYPE :
		__find_set_type_get(name, family, revision, found, true);

unlock:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

/* Find a given set type by name and family.
 * If we succeeded, the supported minimal and maximum revisions are
 * filled out.
 */
#घोषणा find_set_type_minmax(name, family, min, max) \
	__find_set_type_minmax(name, family, min, max, false)

अटल पूर्णांक
__find_set_type_minmax(स्थिर अक्षर *name, u8 family, u8 *min, u8 *max,
		       bool retry)
अणु
	काष्ठा ip_set_type *type;
	bool found = false;

	अगर (retry && !load_settype(name))
		वापस -IPSET_ERR_FIND_TYPE;

	*min = 255; *max = 0;
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(type, &ip_set_type_list, list)
		अगर (STRNCMP(type->name, name) &&
		    (type->family == family ||
		     type->family == NFPROTO_UNSPEC)) अणु
			found = true;
			अगर (type->revision_min < *min)
				*min = type->revision_min;
			अगर (type->revision_max > *max)
				*max = type->revision_max;
		पूर्ण
	rcu_पढ़ो_unlock();
	अगर (found)
		वापस 0;

	वापस retry ? -IPSET_ERR_FIND_TYPE :
		__find_set_type_minmax(name, family, min, max, true);
पूर्ण

#घोषणा family_name(f)	((f) == NFPROTO_IPV4 ? "inet" : \
			 (f) == NFPROTO_IPV6 ? "inet6" : "any")

/* Register a set type काष्ठाure. The type is identअगरied by
 * the unique triple of name, family and revision.
 */
पूर्णांक
ip_set_type_रेजिस्टर(काष्ठा ip_set_type *type)
अणु
	पूर्णांक ret = 0;

	अगर (type->protocol != IPSET_PROTOCOL) अणु
		pr_warn("ip_set type %s, family %s, revision %u:%u uses wrong protocol version %u (want %u)\n",
			type->name, family_name(type->family),
			type->revision_min, type->revision_max,
			type->protocol, IPSET_PROTOCOL);
		वापस -EINVAL;
	पूर्ण

	ip_set_type_lock();
	अगर (find_set_type(type->name, type->family, type->revision_min)) अणु
		/* Duplicate! */
		pr_warn("ip_set type %s, family %s with revision min %u already registered!\n",
			type->name, family_name(type->family),
			type->revision_min);
		ip_set_type_unlock();
		वापस -EINVAL;
	पूर्ण
	list_add_rcu(&type->list, &ip_set_type_list);
	pr_debug("type %s, family %s, revision %u:%u registered.\n",
		 type->name, family_name(type->family),
		 type->revision_min, type->revision_max);
	ip_set_type_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_type_रेजिस्टर);

/* Unरेजिस्टर a set type. There's a small race with ip_set_create */
व्योम
ip_set_type_unरेजिस्टर(काष्ठा ip_set_type *type)
अणु
	ip_set_type_lock();
	अगर (!find_set_type(type->name, type->family, type->revision_min)) अणु
		pr_warn("ip_set type %s, family %s with revision min %u not registered\n",
			type->name, family_name(type->family),
			type->revision_min);
		ip_set_type_unlock();
		वापस;
	पूर्ण
	list_del_rcu(&type->list);
	pr_debug("type %s, family %s with revision min %u unregistered.\n",
		 type->name, family_name(type->family), type->revision_min);
	ip_set_type_unlock();

	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_type_unरेजिस्टर);

/* Utility functions */
व्योम *
ip_set_alloc(माप_प्रकार size)
अणु
	वापस kvzalloc(size, GFP_KERNEL_ACCOUNT);
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_alloc);

व्योम
ip_set_मुक्त(व्योम *members)
अणु
	pr_debug("%p: free with %s\n", members,
		 is_vदो_स्मृति_addr(members) ? "vfree" : "kfree");
	kvमुक्त(members);
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_मुक्त);

अटल bool
flag_nested(स्थिर काष्ठा nlattr *nla)
अणु
	वापस nla->nla_type & NLA_F_NESTED;
पूर्ण

अटल स्थिर काष्ठा nla_policy ipaddr_policy[IPSET_ATTR_IPADDR_MAX + 1] = अणु
	[IPSET_ATTR_IPADDR_IPV4]	= अणु .type = NLA_U32 पूर्ण,
	[IPSET_ATTR_IPADDR_IPV6]	= NLA_POLICY_EXACT_LEN(माप(काष्ठा in6_addr)),
पूर्ण;

पूर्णांक
ip_set_get_ipaddr4(काष्ठा nlattr *nla,  __be32 *ipaddr)
अणु
	काष्ठा nlattr *tb[IPSET_ATTR_IPADDR_MAX + 1];

	अगर (unlikely(!flag_nested(nla)))
		वापस -IPSET_ERR_PROTOCOL;
	अगर (nla_parse_nested(tb, IPSET_ATTR_IPADDR_MAX, nla,
			     ipaddr_policy, शून्य))
		वापस -IPSET_ERR_PROTOCOL;
	अगर (unlikely(!ip_set_attr_netorder(tb, IPSET_ATTR_IPADDR_IPV4)))
		वापस -IPSET_ERR_PROTOCOL;

	*ipaddr = nla_get_be32(tb[IPSET_ATTR_IPADDR_IPV4]);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_get_ipaddr4);

पूर्णांक
ip_set_get_ipaddr6(काष्ठा nlattr *nla, जोड़ nf_inet_addr *ipaddr)
अणु
	काष्ठा nlattr *tb[IPSET_ATTR_IPADDR_MAX + 1];

	अगर (unlikely(!flag_nested(nla)))
		वापस -IPSET_ERR_PROTOCOL;

	अगर (nla_parse_nested(tb, IPSET_ATTR_IPADDR_MAX, nla,
			     ipaddr_policy, शून्य))
		वापस -IPSET_ERR_PROTOCOL;
	अगर (unlikely(!ip_set_attr_netorder(tb, IPSET_ATTR_IPADDR_IPV6)))
		वापस -IPSET_ERR_PROTOCOL;

	स_नकल(ipaddr, nla_data(tb[IPSET_ATTR_IPADDR_IPV6]),
	       माप(काष्ठा in6_addr));
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_get_ipaddr6);

अटल u32
ip_set_समयout_get(स्थिर अचिन्हित दीर्घ *समयout)
अणु
	u32 t;

	अगर (*समयout == IPSET_ELEM_PERMANENT)
		वापस 0;

	t = jअगरfies_to_msecs(*समयout - jअगरfies) / MSEC_PER_SEC;
	/* Zero value in userspace means no समयout */
	वापस t == 0 ? 1 : t;
पूर्ण

अटल अक्षर *
ip_set_comment_uget(काष्ठा nlattr *tb)
अणु
	वापस nla_data(tb);
पूर्ण

/* Called from uadd only, रक्षित by the set spinlock.
 * The kadt functions करोn't use the comment extensions in any way.
 */
व्योम
ip_set_init_comment(काष्ठा ip_set *set, काष्ठा ip_set_comment *comment,
		    स्थिर काष्ठा ip_set_ext *ext)
अणु
	काष्ठा ip_set_comment_rcu *c = rcu_dereference_रक्षित(comment->c, 1);
	माप_प्रकार len = ext->comment ? म_माप(ext->comment) : 0;

	अगर (unlikely(c)) अणु
		set->ext_size -= माप(*c) + म_माप(c->str) + 1;
		kमुक्त_rcu(c, rcu);
		rcu_assign_poपूर्णांकer(comment->c, शून्य);
	पूर्ण
	अगर (!len)
		वापस;
	अगर (unlikely(len > IPSET_MAX_COMMENT_SIZE))
		len = IPSET_MAX_COMMENT_SIZE;
	c = kदो_स्मृति(माप(*c) + len + 1, GFP_ATOMIC);
	अगर (unlikely(!c))
		वापस;
	strlcpy(c->str, ext->comment, len + 1);
	set->ext_size += माप(*c) + म_माप(c->str) + 1;
	rcu_assign_poपूर्णांकer(comment->c, c);
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_init_comment);

/* Used only when dumping a set, रक्षित by rcu_पढ़ो_lock() */
अटल पूर्णांक
ip_set_put_comment(काष्ठा sk_buff *skb, स्थिर काष्ठा ip_set_comment *comment)
अणु
	काष्ठा ip_set_comment_rcu *c = rcu_dereference(comment->c);

	अगर (!c)
		वापस 0;
	वापस nla_put_string(skb, IPSET_ATTR_COMMENT, c->str);
पूर्ण

/* Called from uadd/udel, flush or the garbage collectors रक्षित
 * by the set spinlock.
 * Called when the set is destroyed and when there can't be any user
 * of the set data anymore.
 */
अटल व्योम
ip_set_comment_मुक्त(काष्ठा ip_set *set, व्योम *ptr)
अणु
	काष्ठा ip_set_comment *comment = ptr;
	काष्ठा ip_set_comment_rcu *c;

	c = rcu_dereference_रक्षित(comment->c, 1);
	अगर (unlikely(!c))
		वापस;
	set->ext_size -= माप(*c) + म_माप(c->str) + 1;
	kमुक्त_rcu(c, rcu);
	rcu_assign_poपूर्णांकer(comment->c, शून्य);
पूर्ण

प्रकार व्योम (*destroyer)(काष्ठा ip_set *, व्योम *);
/* ipset data extension types, in size order */

स्थिर काष्ठा ip_set_ext_type ip_set_extensions[] = अणु
	[IPSET_EXT_ID_COUNTER] = अणु
		.type	= IPSET_EXT_COUNTER,
		.flag	= IPSET_FLAG_WITH_COUNTERS,
		.len	= माप(काष्ठा ip_set_counter),
		.align	= __alignof__(काष्ठा ip_set_counter),
	पूर्ण,
	[IPSET_EXT_ID_TIMEOUT] = अणु
		.type	= IPSET_EXT_TIMEOUT,
		.len	= माप(अचिन्हित दीर्घ),
		.align	= __alignof__(अचिन्हित दीर्घ),
	पूर्ण,
	[IPSET_EXT_ID_SKBINFO] = अणु
		.type	= IPSET_EXT_SKBINFO,
		.flag	= IPSET_FLAG_WITH_SKBINFO,
		.len	= माप(काष्ठा ip_set_skbinfo),
		.align	= __alignof__(काष्ठा ip_set_skbinfo),
	पूर्ण,
	[IPSET_EXT_ID_COMMENT] = अणु
		.type	 = IPSET_EXT_COMMENT | IPSET_EXT_DESTROY,
		.flag	 = IPSET_FLAG_WITH_COMMENT,
		.len	 = माप(काष्ठा ip_set_comment),
		.align	 = __alignof__(काष्ठा ip_set_comment),
		.destroy = ip_set_comment_मुक्त,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(ip_set_extensions);

अटल bool
add_extension(क्रमागत ip_set_ext_id id, u32 flags, काष्ठा nlattr *tb[])
अणु
	वापस ip_set_extensions[id].flag ?
		(flags & ip_set_extensions[id].flag) :
		!!tb[IPSET_ATTR_TIMEOUT];
पूर्ण

माप_प्रकार
ip_set_elem_len(काष्ठा ip_set *set, काष्ठा nlattr *tb[], माप_प्रकार len,
		माप_प्रकार align)
अणु
	क्रमागत ip_set_ext_id id;
	u32 cadt_flags = 0;

	अगर (tb[IPSET_ATTR_CADT_FLAGS])
		cadt_flags = ip_set_get_h32(tb[IPSET_ATTR_CADT_FLAGS]);
	अगर (cadt_flags & IPSET_FLAG_WITH_FORCEADD)
		set->flags |= IPSET_CREATE_FLAG_FORCEADD;
	अगर (!align)
		align = 1;
	क्रम (id = 0; id < IPSET_EXT_ID_MAX; id++) अणु
		अगर (!add_extension(id, cadt_flags, tb))
			जारी;
		अगर (align < ip_set_extensions[id].align)
			align = ip_set_extensions[id].align;
		len = ALIGN(len, ip_set_extensions[id].align);
		set->offset[id] = len;
		set->extensions |= ip_set_extensions[id].type;
		len += ip_set_extensions[id].len;
	पूर्ण
	वापस ALIGN(len, align);
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_elem_len);

पूर्णांक
ip_set_get_extensions(काष्ठा ip_set *set, काष्ठा nlattr *tb[],
		      काष्ठा ip_set_ext *ext)
अणु
	u64 fullmark;

	अगर (unlikely(!ip_set_optattr_netorder(tb, IPSET_ATTR_TIMEOUT) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_PACKETS) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_BYTES) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_SKBMARK) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_SKBPRIO) ||
		     !ip_set_optattr_netorder(tb, IPSET_ATTR_SKBQUEUE)))
		वापस -IPSET_ERR_PROTOCOL;

	अगर (tb[IPSET_ATTR_TIMEOUT]) अणु
		अगर (!SET_WITH_TIMEOUT(set))
			वापस -IPSET_ERR_TIMEOUT;
		ext->समयout = ip_set_समयout_uget(tb[IPSET_ATTR_TIMEOUT]);
	पूर्ण
	अगर (tb[IPSET_ATTR_BYTES] || tb[IPSET_ATTR_PACKETS]) अणु
		अगर (!SET_WITH_COUNTER(set))
			वापस -IPSET_ERR_COUNTER;
		अगर (tb[IPSET_ATTR_BYTES])
			ext->bytes = be64_to_cpu(nla_get_be64(
						 tb[IPSET_ATTR_BYTES]));
		अगर (tb[IPSET_ATTR_PACKETS])
			ext->packets = be64_to_cpu(nla_get_be64(
						   tb[IPSET_ATTR_PACKETS]));
	पूर्ण
	अगर (tb[IPSET_ATTR_COMMENT]) अणु
		अगर (!SET_WITH_COMMENT(set))
			वापस -IPSET_ERR_COMMENT;
		ext->comment = ip_set_comment_uget(tb[IPSET_ATTR_COMMENT]);
	पूर्ण
	अगर (tb[IPSET_ATTR_SKBMARK]) अणु
		अगर (!SET_WITH_SKBINFO(set))
			वापस -IPSET_ERR_SKBINFO;
		fullmark = be64_to_cpu(nla_get_be64(tb[IPSET_ATTR_SKBMARK]));
		ext->skbinfo.skbmark = fullmark >> 32;
		ext->skbinfo.skbmarkmask = fullmark & 0xffffffff;
	पूर्ण
	अगर (tb[IPSET_ATTR_SKBPRIO]) अणु
		अगर (!SET_WITH_SKBINFO(set))
			वापस -IPSET_ERR_SKBINFO;
		ext->skbinfo.skbprio =
			be32_to_cpu(nla_get_be32(tb[IPSET_ATTR_SKBPRIO]));
	पूर्ण
	अगर (tb[IPSET_ATTR_SKBQUEUE]) अणु
		अगर (!SET_WITH_SKBINFO(set))
			वापस -IPSET_ERR_SKBINFO;
		ext->skbinfo.skbqueue =
			be16_to_cpu(nla_get_be16(tb[IPSET_ATTR_SKBQUEUE]));
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_get_extensions);

अटल u64
ip_set_get_bytes(स्थिर काष्ठा ip_set_counter *counter)
अणु
	वापस (u64)atomic64_पढ़ो(&(counter)->bytes);
पूर्ण

अटल u64
ip_set_get_packets(स्थिर काष्ठा ip_set_counter *counter)
अणु
	वापस (u64)atomic64_पढ़ो(&(counter)->packets);
पूर्ण

अटल bool
ip_set_put_counter(काष्ठा sk_buff *skb, स्थिर काष्ठा ip_set_counter *counter)
अणु
	वापस nla_put_net64(skb, IPSET_ATTR_BYTES,
			     cpu_to_be64(ip_set_get_bytes(counter)),
			     IPSET_ATTR_PAD) ||
	       nla_put_net64(skb, IPSET_ATTR_PACKETS,
			     cpu_to_be64(ip_set_get_packets(counter)),
			     IPSET_ATTR_PAD);
पूर्ण

अटल bool
ip_set_put_skbinfo(काष्ठा sk_buff *skb, स्थिर काष्ठा ip_set_skbinfo *skbinfo)
अणु
	/* Send nonzero parameters only */
	वापस ((skbinfo->skbmark || skbinfo->skbmarkmask) &&
		nla_put_net64(skb, IPSET_ATTR_SKBMARK,
			      cpu_to_be64((u64)skbinfo->skbmark << 32 |
					  skbinfo->skbmarkmask),
			      IPSET_ATTR_PAD)) ||
	       (skbinfo->skbprio &&
		nla_put_net32(skb, IPSET_ATTR_SKBPRIO,
			      cpu_to_be32(skbinfo->skbprio))) ||
	       (skbinfo->skbqueue &&
		nla_put_net16(skb, IPSET_ATTR_SKBQUEUE,
			      cpu_to_be16(skbinfo->skbqueue)));
पूर्ण

पूर्णांक
ip_set_put_extensions(काष्ठा sk_buff *skb, स्थिर काष्ठा ip_set *set,
		      स्थिर व्योम *e, bool active)
अणु
	अगर (SET_WITH_TIMEOUT(set)) अणु
		अचिन्हित दीर्घ *समयout = ext_समयout(e, set);

		अगर (nla_put_net32(skb, IPSET_ATTR_TIMEOUT,
			htonl(active ? ip_set_समयout_get(समयout)
				: *समयout)))
			वापस -EMSGSIZE;
	पूर्ण
	अगर (SET_WITH_COUNTER(set) &&
	    ip_set_put_counter(skb, ext_counter(e, set)))
		वापस -EMSGSIZE;
	अगर (SET_WITH_COMMENT(set) &&
	    ip_set_put_comment(skb, ext_comment(e, set)))
		वापस -EMSGSIZE;
	अगर (SET_WITH_SKBINFO(set) &&
	    ip_set_put_skbinfo(skb, ext_skbinfo(e, set)))
		वापस -EMSGSIZE;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_put_extensions);

अटल bool
ip_set_match_counter(u64 counter, u64 match, u8 op)
अणु
	चयन (op) अणु
	हाल IPSET_COUNTER_NONE:
		वापस true;
	हाल IPSET_COUNTER_EQ:
		वापस counter == match;
	हाल IPSET_COUNTER_NE:
		वापस counter != match;
	हाल IPSET_COUNTER_LT:
		वापस counter < match;
	हाल IPSET_COUNTER_GT:
		वापस counter > match;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम
ip_set_add_bytes(u64 bytes, काष्ठा ip_set_counter *counter)
अणु
	atomic64_add((दीर्घ दीर्घ)bytes, &(counter)->bytes);
पूर्ण

अटल व्योम
ip_set_add_packets(u64 packets, काष्ठा ip_set_counter *counter)
अणु
	atomic64_add((दीर्घ दीर्घ)packets, &(counter)->packets);
पूर्ण

अटल व्योम
ip_set_update_counter(काष्ठा ip_set_counter *counter,
		      स्थिर काष्ठा ip_set_ext *ext, u32 flags)
अणु
	अगर (ext->packets != ULदीर्घ_उच्च &&
	    !(flags & IPSET_FLAG_SKIP_COUNTER_UPDATE)) अणु
		ip_set_add_bytes(ext->bytes, counter);
		ip_set_add_packets(ext->packets, counter);
	पूर्ण
पूर्ण

अटल व्योम
ip_set_get_skbinfo(काष्ठा ip_set_skbinfo *skbinfo,
		   स्थिर काष्ठा ip_set_ext *ext,
		   काष्ठा ip_set_ext *mext, u32 flags)
अणु
	mext->skbinfo = *skbinfo;
पूर्ण

bool
ip_set_match_extensions(काष्ठा ip_set *set, स्थिर काष्ठा ip_set_ext *ext,
			काष्ठा ip_set_ext *mext, u32 flags, व्योम *data)
अणु
	अगर (SET_WITH_TIMEOUT(set) &&
	    ip_set_समयout_expired(ext_समयout(data, set)))
		वापस false;
	अगर (SET_WITH_COUNTER(set)) अणु
		काष्ठा ip_set_counter *counter = ext_counter(data, set);

		ip_set_update_counter(counter, ext, flags);

		अगर (flags & IPSET_FLAG_MATCH_COUNTERS &&
		    !(ip_set_match_counter(ip_set_get_packets(counter),
				mext->packets, mext->packets_op) &&
		      ip_set_match_counter(ip_set_get_bytes(counter),
				mext->bytes, mext->bytes_op)))
			वापस false;
	पूर्ण
	अगर (SET_WITH_SKBINFO(set))
		ip_set_get_skbinfo(ext_skbinfo(data, set),
				   ext, mext, flags);
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_match_extensions);

/* Creating/destroying/renaming/swapping affect the existence and
 * the properties of a set. All of these can be executed from userspace
 * only and serialized by the nfnl mutex indirectly from nfnetlink.
 *
 * Sets are identअगरied by their index in ip_set_list and the index
 * is used by the बाह्यal references (set/SET netfilter modules).
 *
 * The set behind an index may change by swapping only, from userspace.
 */

अटल व्योम
__ip_set_get(काष्ठा ip_set *set)
अणु
	ग_लिखो_lock_bh(&ip_set_ref_lock);
	set->ref++;
	ग_लिखो_unlock_bh(&ip_set_ref_lock);
पूर्ण

अटल व्योम
__ip_set_put(काष्ठा ip_set *set)
अणु
	ग_लिखो_lock_bh(&ip_set_ref_lock);
	BUG_ON(set->ref == 0);
	set->ref--;
	ग_लिखो_unlock_bh(&ip_set_ref_lock);
पूर्ण

/* set->ref can be swapped out by ip_set_swap, netlink events (like dump) need
 * a separate reference counter
 */
अटल व्योम
__ip_set_put_netlink(काष्ठा ip_set *set)
अणु
	ग_लिखो_lock_bh(&ip_set_ref_lock);
	BUG_ON(set->ref_netlink == 0);
	set->ref_netlink--;
	ग_लिखो_unlock_bh(&ip_set_ref_lock);
पूर्ण

/* Add, del and test set entries from kernel.
 *
 * The set behind the index must exist and must be referenced
 * so it can't be destroyed (or changed) under our foot.
 */

अटल काष्ठा ip_set *
ip_set_rcu_get(काष्ठा net *net, ip_set_id_t index)
अणु
	काष्ठा ip_set *set;
	काष्ठा ip_set_net *inst = ip_set_pernet(net);

	rcu_पढ़ो_lock();
	/* ip_set_list itself needs to be रक्षित */
	set = rcu_dereference(inst->ip_set_list)[index];
	rcu_पढ़ो_unlock();

	वापस set;
पूर्ण

अटल अंतरभूत व्योम
ip_set_lock(काष्ठा ip_set *set)
अणु
	अगर (!set->variant->region_lock)
		spin_lock_bh(&set->lock);
पूर्ण

अटल अंतरभूत व्योम
ip_set_unlock(काष्ठा ip_set *set)
अणु
	अगर (!set->variant->region_lock)
		spin_unlock_bh(&set->lock);
पूर्ण

पूर्णांक
ip_set_test(ip_set_id_t index, स्थिर काष्ठा sk_buff *skb,
	    स्थिर काष्ठा xt_action_param *par, काष्ठा ip_set_adt_opt *opt)
अणु
	काष्ठा ip_set *set = ip_set_rcu_get(xt_net(par), index);
	पूर्णांक ret = 0;

	BUG_ON(!set);
	pr_debug("set %s, index %u\n", set->name, index);

	अगर (opt->dim < set->type->dimension ||
	    !(opt->family == set->family || set->family == NFPROTO_UNSPEC))
		वापस 0;

	rcu_पढ़ो_lock_bh();
	ret = set->variant->kadt(set, skb, par, IPSET_TEST, opt);
	rcu_पढ़ो_unlock_bh();

	अगर (ret == -EAGAIN) अणु
		/* Type requests element to be completed */
		pr_debug("element must be completed, ADD is triggered\n");
		ip_set_lock(set);
		set->variant->kadt(set, skb, par, IPSET_ADD, opt);
		ip_set_unlock(set);
		ret = 1;
	पूर्ण अन्यथा अणु
		/* --वापस-nomatch: invert matched element */
		अगर ((opt->cmdflags & IPSET_FLAG_RETURN_NOMATCH) &&
		    (set->type->features & IPSET_TYPE_NOMATCH) &&
		    (ret > 0 || ret == -ENOTEMPTY))
			ret = -ret;
	पूर्ण

	/* Convert error codes to nomatch */
	वापस (ret < 0 ? 0 : ret);
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_test);

पूर्णांक
ip_set_add(ip_set_id_t index, स्थिर काष्ठा sk_buff *skb,
	   स्थिर काष्ठा xt_action_param *par, काष्ठा ip_set_adt_opt *opt)
अणु
	काष्ठा ip_set *set = ip_set_rcu_get(xt_net(par), index);
	पूर्णांक ret;

	BUG_ON(!set);
	pr_debug("set %s, index %u\n", set->name, index);

	अगर (opt->dim < set->type->dimension ||
	    !(opt->family == set->family || set->family == NFPROTO_UNSPEC))
		वापस -IPSET_ERR_TYPE_MISMATCH;

	ip_set_lock(set);
	ret = set->variant->kadt(set, skb, par, IPSET_ADD, opt);
	ip_set_unlock(set);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_add);

पूर्णांक
ip_set_del(ip_set_id_t index, स्थिर काष्ठा sk_buff *skb,
	   स्थिर काष्ठा xt_action_param *par, काष्ठा ip_set_adt_opt *opt)
अणु
	काष्ठा ip_set *set = ip_set_rcu_get(xt_net(par), index);
	पूर्णांक ret = 0;

	BUG_ON(!set);
	pr_debug("set %s, index %u\n", set->name, index);

	अगर (opt->dim < set->type->dimension ||
	    !(opt->family == set->family || set->family == NFPROTO_UNSPEC))
		वापस -IPSET_ERR_TYPE_MISMATCH;

	ip_set_lock(set);
	ret = set->variant->kadt(set, skb, par, IPSET_DEL, opt);
	ip_set_unlock(set);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_del);

/* Find set by name, reference it once. The reference makes sure the
 * thing poपूर्णांकed to, करोes not go away under our feet.
 *
 */
ip_set_id_t
ip_set_get_byname(काष्ठा net *net, स्थिर अक्षर *name, काष्ठा ip_set **set)
अणु
	ip_set_id_t i, index = IPSET_INVALID_ID;
	काष्ठा ip_set *s;
	काष्ठा ip_set_net *inst = ip_set_pernet(net);

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < inst->ip_set_max; i++) अणु
		s = rcu_dereference(inst->ip_set_list)[i];
		अगर (s && STRNCMP(s->name, name)) अणु
			__ip_set_get(s);
			index = i;
			*set = s;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस index;
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_get_byname);

/* If the given set poपूर्णांकer poपूर्णांकs to a valid set, decrement
 * reference count by 1. The caller shall not assume the index
 * to be valid, after calling this function.
 *
 */

अटल व्योम
__ip_set_put_byindex(काष्ठा ip_set_net *inst, ip_set_id_t index)
अणु
	काष्ठा ip_set *set;

	rcu_पढ़ो_lock();
	set = rcu_dereference(inst->ip_set_list)[index];
	अगर (set)
		__ip_set_put(set);
	rcu_पढ़ो_unlock();
पूर्ण

व्योम
ip_set_put_byindex(काष्ठा net *net, ip_set_id_t index)
अणु
	काष्ठा ip_set_net *inst = ip_set_pernet(net);

	__ip_set_put_byindex(inst, index);
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_put_byindex);

/* Get the name of a set behind a set index.
 * Set itself is रक्षित by RCU, but its name isn't: to protect against
 * renaming, grab ip_set_ref_lock as पढ़ोer (see ip_set_नाम()) and copy the
 * name.
 */
व्योम
ip_set_name_byindex(काष्ठा net *net, ip_set_id_t index, अक्षर *name)
अणु
	काष्ठा ip_set *set = ip_set_rcu_get(net, index);

	BUG_ON(!set);

	पढ़ो_lock_bh(&ip_set_ref_lock);
	म_नकलन(name, set->name, IPSET_MAXNAMELEN);
	पढ़ो_unlock_bh(&ip_set_ref_lock);
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_name_byindex);

/* Routines to call by बाह्यal subप्रणालीs, which करो not
 * call nfnl_lock क्रम us.
 */

/* Find set by index, reference it once. The reference makes sure the
 * thing poपूर्णांकed to, करोes not go away under our feet.
 *
 * The nfnl mutex is used in the function.
 */
ip_set_id_t
ip_set_nfnl_get_byindex(काष्ठा net *net, ip_set_id_t index)
अणु
	काष्ठा ip_set *set;
	काष्ठा ip_set_net *inst = ip_set_pernet(net);

	अगर (index >= inst->ip_set_max)
		वापस IPSET_INVALID_ID;

	nfnl_lock(NFNL_SUBSYS_IPSET);
	set = ip_set(inst, index);
	अगर (set)
		__ip_set_get(set);
	अन्यथा
		index = IPSET_INVALID_ID;
	nfnl_unlock(NFNL_SUBSYS_IPSET);

	वापस index;
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_nfnl_get_byindex);

/* If the given set poपूर्णांकer poपूर्णांकs to a valid set, decrement
 * reference count by 1. The caller shall not assume the index
 * to be valid, after calling this function.
 *
 * The nfnl mutex is used in the function.
 */
व्योम
ip_set_nfnl_put(काष्ठा net *net, ip_set_id_t index)
अणु
	काष्ठा ip_set *set;
	काष्ठा ip_set_net *inst = ip_set_pernet(net);

	nfnl_lock(NFNL_SUBSYS_IPSET);
	अगर (!inst->is_deleted) अणु /* alपढ़ोy deleted from ip_set_net_निकास() */
		set = ip_set(inst, index);
		अगर (set)
			__ip_set_put(set);
	पूर्ण
	nfnl_unlock(NFNL_SUBSYS_IPSET);
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_nfnl_put);

/* Communication protocol with userspace over netlink.
 *
 * The commands are serialized by the nfnl mutex.
 */

अटल अंतरभूत u8 protocol(स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	वापस nla_get_u8(tb[IPSET_ATTR_PROTOCOL]);
पूर्ण

अटल अंतरभूत bool
protocol_failed(स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	वापस !tb[IPSET_ATTR_PROTOCOL] || protocol(tb) != IPSET_PROTOCOL;
पूर्ण

अटल अंतरभूत bool
protocol_min_failed(स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	वापस !tb[IPSET_ATTR_PROTOCOL] || protocol(tb) < IPSET_PROTOCOL_MIN;
पूर्ण

अटल अंतरभूत u32
flag_exist(स्थिर काष्ठा nlmsghdr *nlh)
अणु
	वापस nlh->nlmsg_flags & NLM_F_EXCL ? 0 : IPSET_FLAG_EXIST;
पूर्ण

अटल काष्ठा nlmsghdr *
start_msg(काष्ठा sk_buff *skb, u32 portid, u32 seq, अचिन्हित पूर्णांक flags,
	  क्रमागत ipset_cmd cmd)
अणु
	वापस nfnl_msg_put(skb, portid, seq,
			    nfnl_msg_type(NFNL_SUBSYS_IPSET, cmd), flags,
			    NFPROTO_IPV4, NFNETLINK_V0, 0);
पूर्ण

/* Create a set */

अटल स्थिर काष्ठा nla_policy ip_set_create_policy[IPSET_ATTR_CMD_MAX + 1] = अणु
	[IPSET_ATTR_PROTOCOL]	= अणु .type = NLA_U8 पूर्ण,
	[IPSET_ATTR_SETNAME]	= अणु .type = NLA_NUL_STRING,
				    .len = IPSET_MAXNAMELEN - 1 पूर्ण,
	[IPSET_ATTR_TYPENAME]	= अणु .type = NLA_NUL_STRING,
				    .len = IPSET_MAXNAMELEN - 1पूर्ण,
	[IPSET_ATTR_REVISION]	= अणु .type = NLA_U8 पूर्ण,
	[IPSET_ATTR_FAMILY]	= अणु .type = NLA_U8 पूर्ण,
	[IPSET_ATTR_DATA]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल काष्ठा ip_set *
find_set_and_id(काष्ठा ip_set_net *inst, स्थिर अक्षर *name, ip_set_id_t *id)
अणु
	काष्ठा ip_set *set = शून्य;
	ip_set_id_t i;

	*id = IPSET_INVALID_ID;
	क्रम (i = 0; i < inst->ip_set_max; i++) अणु
		set = ip_set(inst, i);
		अगर (set && STRNCMP(set->name, name)) अणु
			*id = i;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस (*id == IPSET_INVALID_ID ? शून्य : set);
पूर्ण

अटल अंतरभूत काष्ठा ip_set *
find_set(काष्ठा ip_set_net *inst, स्थिर अक्षर *name)
अणु
	ip_set_id_t id;

	वापस find_set_and_id(inst, name, &id);
पूर्ण

अटल पूर्णांक
find_मुक्त_id(काष्ठा ip_set_net *inst, स्थिर अक्षर *name, ip_set_id_t *index,
	     काष्ठा ip_set **set)
अणु
	काष्ठा ip_set *s;
	ip_set_id_t i;

	*index = IPSET_INVALID_ID;
	क्रम (i = 0;  i < inst->ip_set_max; i++) अणु
		s = ip_set(inst, i);
		अगर (!s) अणु
			अगर (*index == IPSET_INVALID_ID)
				*index = i;
		पूर्ण अन्यथा अगर (STRNCMP(name, s->name)) अणु
			/* Name clash */
			*set = s;
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	अगर (*index == IPSET_INVALID_ID)
		/* No मुक्त slot reमुख्यed */
		वापस -IPSET_ERR_MAX_SETS;
	वापस 0;
पूर्ण

अटल पूर्णांक ip_set_none(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
		       स्थिर काष्ठा nlattr * स्थिर attr[])
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ip_set_create(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			 स्थिर काष्ठा nlattr * स्थिर attr[])
अणु
	काष्ठा ip_set_net *inst = ip_set_pernet(info->net);
	काष्ठा ip_set *set, *clash = शून्य;
	ip_set_id_t index = IPSET_INVALID_ID;
	काष्ठा nlattr *tb[IPSET_ATTR_CREATE_MAX + 1] = अणुपूर्ण;
	स्थिर अक्षर *name, *typename;
	u8 family, revision;
	u32 flags = flag_exist(info->nlh);
	पूर्णांक ret = 0;

	अगर (unlikely(protocol_min_failed(attr) ||
		     !attr[IPSET_ATTR_SETNAME] ||
		     !attr[IPSET_ATTR_TYPENAME] ||
		     !attr[IPSET_ATTR_REVISION] ||
		     !attr[IPSET_ATTR_FAMILY] ||
		     (attr[IPSET_ATTR_DATA] &&
		      !flag_nested(attr[IPSET_ATTR_DATA]))))
		वापस -IPSET_ERR_PROTOCOL;

	name = nla_data(attr[IPSET_ATTR_SETNAME]);
	typename = nla_data(attr[IPSET_ATTR_TYPENAME]);
	family = nla_get_u8(attr[IPSET_ATTR_FAMILY]);
	revision = nla_get_u8(attr[IPSET_ATTR_REVISION]);
	pr_debug("setname: %s, typename: %s, family: %s, revision: %u\n",
		 name, typename, family_name(family), revision);

	/* First, and without any locks, allocate and initialize
	 * a normal base set काष्ठाure.
	 */
	set = kzalloc(माप(*set), GFP_KERNEL);
	अगर (!set)
		वापस -ENOMEM;
	spin_lock_init(&set->lock);
	strlcpy(set->name, name, IPSET_MAXNAMELEN);
	set->family = family;
	set->revision = revision;

	/* Next, check that we know the type, and take
	 * a reference on the type, to make sure it stays available
	 * जबतक स्थिरructing our new set.
	 *
	 * After referencing the type, we try to create the type
	 * specअगरic part of the set without holding any locks.
	 */
	ret = find_set_type_get(typename, family, revision, &set->type);
	अगर (ret)
		जाओ out;

	/* Without holding any locks, create निजी part. */
	अगर (attr[IPSET_ATTR_DATA] &&
	    nla_parse_nested(tb, IPSET_ATTR_CREATE_MAX, attr[IPSET_ATTR_DATA],
			     set->type->create_policy, शून्य)) अणु
		ret = -IPSET_ERR_PROTOCOL;
		जाओ put_out;
	पूर्ण
	/* Set create flags depending on the type revision */
	set->flags |= set->type->create_flags[revision];

	ret = set->type->create(info->net, set, tb, flags);
	अगर (ret != 0)
		जाओ put_out;

	/* BTW, ret==0 here. */

	/* Here, we have a valid, स्थिरructed set and we are रक्षित
	 * by the nfnl mutex. Find the first मुक्त index in ip_set_list
	 * and check clashing.
	 */
	ret = find_मुक्त_id(inst, set->name, &index, &clash);
	अगर (ret == -EEXIST) अणु
		/* If this is the same set and requested, ignore error */
		अगर ((flags & IPSET_FLAG_EXIST) &&
		    STRNCMP(set->type->name, clash->type->name) &&
		    set->type->family == clash->type->family &&
		    set->type->revision_min == clash->type->revision_min &&
		    set->type->revision_max == clash->type->revision_max &&
		    set->variant->same_set(set, clash))
			ret = 0;
		जाओ cleanup;
	पूर्ण अन्यथा अगर (ret == -IPSET_ERR_MAX_SETS) अणु
		काष्ठा ip_set **list, **पंचांगp;
		ip_set_id_t i = inst->ip_set_max + IP_SET_INC;

		अगर (i < inst->ip_set_max || i == IPSET_INVALID_ID)
			/* Wraparound */
			जाओ cleanup;

		list = kvसुस्मृति(i, माप(काष्ठा ip_set *), GFP_KERNEL);
		अगर (!list)
			जाओ cleanup;
		/* nfnl mutex is held, both lists are valid */
		पंचांगp = ip_set_dereference(inst->ip_set_list);
		स_नकल(list, पंचांगp, माप(काष्ठा ip_set *) * inst->ip_set_max);
		rcu_assign_poपूर्णांकer(inst->ip_set_list, list);
		/* Make sure all current packets have passed through */
		synchronize_net();
		/* Use new list */
		index = inst->ip_set_max;
		inst->ip_set_max = i;
		kvमुक्त(पंचांगp);
		ret = 0;
	पूर्ण अन्यथा अगर (ret) अणु
		जाओ cleanup;
	पूर्ण

	/* Finally! Add our shiny new set to the list, and be करोne. */
	pr_debug("create: '%s' created with index %u!\n", set->name, index);
	ip_set(inst, index) = set;

	वापस ret;

cleanup:
	set->variant->destroy(set);
put_out:
	module_put(set->type->me);
out:
	kमुक्त(set);
	वापस ret;
पूर्ण

/* Destroy sets */

अटल स्थिर काष्ठा nla_policy
ip_set_setname_policy[IPSET_ATTR_CMD_MAX + 1] = अणु
	[IPSET_ATTR_PROTOCOL]	= अणु .type = NLA_U8 पूर्ण,
	[IPSET_ATTR_SETNAME]	= अणु .type = NLA_NUL_STRING,
				    .len = IPSET_MAXNAMELEN - 1 पूर्ण,
पूर्ण;

अटल व्योम
ip_set_destroy_set(काष्ठा ip_set *set)
अणु
	pr_debug("set: %s\n",  set->name);

	/* Must call it without holding any lock */
	set->variant->destroy(set);
	module_put(set->type->me);
	kमुक्त(set);
पूर्ण

अटल पूर्णांक ip_set_destroy(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			  स्थिर काष्ठा nlattr * स्थिर attr[])
अणु
	काष्ठा ip_set_net *inst = ip_set_pernet(info->net);
	काष्ठा ip_set *s;
	ip_set_id_t i;
	पूर्णांक ret = 0;

	अगर (unlikely(protocol_min_failed(attr)))
		वापस -IPSET_ERR_PROTOCOL;

	/* Must रुको क्रम flush to be really finished in list:set */
	rcu_barrier();

	/* Commands are serialized and references are
	 * रक्षित by the ip_set_ref_lock.
	 * External प्रणालीs (i.e. xt_set) must call
	 * ip_set_put|get_nfnl_* functions, that way we
	 * can safely check references here.
	 *
	 * list:set समयr can only decrement the reference
	 * counter, so अगर it's alपढ़ोy zero, we can proceed
	 * without holding the lock.
	 */
	पढ़ो_lock_bh(&ip_set_ref_lock);
	अगर (!attr[IPSET_ATTR_SETNAME]) अणु
		क्रम (i = 0; i < inst->ip_set_max; i++) अणु
			s = ip_set(inst, i);
			अगर (s && (s->ref || s->ref_netlink)) अणु
				ret = -IPSET_ERR_BUSY;
				जाओ out;
			पूर्ण
		पूर्ण
		inst->is_destroyed = true;
		पढ़ो_unlock_bh(&ip_set_ref_lock);
		क्रम (i = 0; i < inst->ip_set_max; i++) अणु
			s = ip_set(inst, i);
			अगर (s) अणु
				ip_set(inst, i) = शून्य;
				ip_set_destroy_set(s);
			पूर्ण
		पूर्ण
		/* Modअगरied by ip_set_destroy() only, which is serialized */
		inst->is_destroyed = false;
	पूर्ण अन्यथा अणु
		u32 flags = flag_exist(info->nlh);
		s = find_set_and_id(inst, nla_data(attr[IPSET_ATTR_SETNAME]),
				    &i);
		अगर (!s) अणु
			अगर (!(flags & IPSET_FLAG_EXIST))
				ret = -ENOENT;
			जाओ out;
		पूर्ण अन्यथा अगर (s->ref || s->ref_netlink) अणु
			ret = -IPSET_ERR_BUSY;
			जाओ out;
		पूर्ण
		ip_set(inst, i) = शून्य;
		पढ़ो_unlock_bh(&ip_set_ref_lock);

		ip_set_destroy_set(s);
	पूर्ण
	वापस 0;
out:
	पढ़ो_unlock_bh(&ip_set_ref_lock);
	वापस ret;
पूर्ण

/* Flush sets */

अटल व्योम
ip_set_flush_set(काष्ठा ip_set *set)
अणु
	pr_debug("set: %s\n",  set->name);

	ip_set_lock(set);
	set->variant->flush(set);
	ip_set_unlock(set);
पूर्ण

अटल पूर्णांक ip_set_flush(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			स्थिर काष्ठा nlattr * स्थिर attr[])
अणु
	काष्ठा ip_set_net *inst = ip_set_pernet(info->net);
	काष्ठा ip_set *s;
	ip_set_id_t i;

	अगर (unlikely(protocol_min_failed(attr)))
		वापस -IPSET_ERR_PROTOCOL;

	अगर (!attr[IPSET_ATTR_SETNAME]) अणु
		क्रम (i = 0; i < inst->ip_set_max; i++) अणु
			s = ip_set(inst, i);
			अगर (s)
				ip_set_flush_set(s);
		पूर्ण
	पूर्ण अन्यथा अणु
		s = find_set(inst, nla_data(attr[IPSET_ATTR_SETNAME]));
		अगर (!s)
			वापस -ENOENT;

		ip_set_flush_set(s);
	पूर्ण

	वापस 0;
पूर्ण

/* Rename a set */

अटल स्थिर काष्ठा nla_policy
ip_set_setname2_policy[IPSET_ATTR_CMD_MAX + 1] = अणु
	[IPSET_ATTR_PROTOCOL]	= अणु .type = NLA_U8 पूर्ण,
	[IPSET_ATTR_SETNAME]	= अणु .type = NLA_NUL_STRING,
				    .len = IPSET_MAXNAMELEN - 1 पूर्ण,
	[IPSET_ATTR_SETNAME2]	= अणु .type = NLA_NUL_STRING,
				    .len = IPSET_MAXNAMELEN - 1 पूर्ण,
पूर्ण;

अटल पूर्णांक ip_set_नाम(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			 स्थिर काष्ठा nlattr * स्थिर attr[])
अणु
	काष्ठा ip_set_net *inst = ip_set_pernet(info->net);
	काष्ठा ip_set *set, *s;
	स्थिर अक्षर *name2;
	ip_set_id_t i;
	पूर्णांक ret = 0;

	अगर (unlikely(protocol_min_failed(attr) ||
		     !attr[IPSET_ATTR_SETNAME] ||
		     !attr[IPSET_ATTR_SETNAME2]))
		वापस -IPSET_ERR_PROTOCOL;

	set = find_set(inst, nla_data(attr[IPSET_ATTR_SETNAME]));
	अगर (!set)
		वापस -ENOENT;

	ग_लिखो_lock_bh(&ip_set_ref_lock);
	अगर (set->ref != 0 || set->ref_netlink != 0) अणु
		ret = -IPSET_ERR_REFERENCED;
		जाओ out;
	पूर्ण

	name2 = nla_data(attr[IPSET_ATTR_SETNAME2]);
	क्रम (i = 0; i < inst->ip_set_max; i++) अणु
		s = ip_set(inst, i);
		अगर (s && STRNCMP(s->name, name2)) अणु
			ret = -IPSET_ERR_EXIST_SETNAME2;
			जाओ out;
		पूर्ण
	पूर्ण
	म_नकलन(set->name, name2, IPSET_MAXNAMELEN);

out:
	ग_लिखो_unlock_bh(&ip_set_ref_lock);
	वापस ret;
पूर्ण

/* Swap two sets so that name/index poपूर्णांकs to the other.
 * References and set names are also swapped.
 *
 * The commands are serialized by the nfnl mutex and references are
 * रक्षित by the ip_set_ref_lock. The kernel पूर्णांकerfaces
 * करो not hold the mutex but the poपूर्णांकer settings are atomic
 * so the ip_set_list always contains valid poपूर्णांकers to the sets.
 */

अटल पूर्णांक ip_set_swap(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
		       स्थिर काष्ठा nlattr * स्थिर attr[])
अणु
	काष्ठा ip_set_net *inst = ip_set_pernet(info->net);
	काष्ठा ip_set *from, *to;
	ip_set_id_t from_id, to_id;
	अक्षर from_name[IPSET_MAXNAMELEN];

	अगर (unlikely(protocol_min_failed(attr) ||
		     !attr[IPSET_ATTR_SETNAME] ||
		     !attr[IPSET_ATTR_SETNAME2]))
		वापस -IPSET_ERR_PROTOCOL;

	from = find_set_and_id(inst, nla_data(attr[IPSET_ATTR_SETNAME]),
			       &from_id);
	अगर (!from)
		वापस -ENOENT;

	to = find_set_and_id(inst, nla_data(attr[IPSET_ATTR_SETNAME2]),
			     &to_id);
	अगर (!to)
		वापस -IPSET_ERR_EXIST_SETNAME2;

	/* Features must not change.
	 * Not an artअगरical restriction anymore, as we must prevent
	 * possible loops created by swapping in setlist type of sets.
	 */
	अगर (!(from->type->features == to->type->features &&
	      from->family == to->family))
		वापस -IPSET_ERR_TYPE_MISMATCH;

	ग_लिखो_lock_bh(&ip_set_ref_lock);

	अगर (from->ref_netlink || to->ref_netlink) अणु
		ग_लिखो_unlock_bh(&ip_set_ref_lock);
		वापस -EBUSY;
	पूर्ण

	म_नकलन(from_name, from->name, IPSET_MAXNAMELEN);
	म_नकलन(from->name, to->name, IPSET_MAXNAMELEN);
	म_नकलन(to->name, from_name, IPSET_MAXNAMELEN);

	swap(from->ref, to->ref);
	ip_set(inst, from_id) = to;
	ip_set(inst, to_id) = from;
	ग_लिखो_unlock_bh(&ip_set_ref_lock);

	वापस 0;
पूर्ण

/* List/save set data */

#घोषणा DUMP_INIT	0
#घोषणा DUMP_ALL	1
#घोषणा DUMP_ONE	2
#घोषणा DUMP_LAST	3

#घोषणा DUMP_TYPE(arg)		(((u32)(arg)) & 0x0000FFFF)
#घोषणा DUMP_FLAGS(arg)		(((u32)(arg)) >> 16)

पूर्णांक
ip_set_put_flags(काष्ठा sk_buff *skb, काष्ठा ip_set *set)
अणु
	u32 cadt_flags = 0;

	अगर (SET_WITH_TIMEOUT(set))
		अगर (unlikely(nla_put_net32(skb, IPSET_ATTR_TIMEOUT,
					   htonl(set->समयout))))
			वापस -EMSGSIZE;
	अगर (SET_WITH_COUNTER(set))
		cadt_flags |= IPSET_FLAG_WITH_COUNTERS;
	अगर (SET_WITH_COMMENT(set))
		cadt_flags |= IPSET_FLAG_WITH_COMMENT;
	अगर (SET_WITH_SKBINFO(set))
		cadt_flags |= IPSET_FLAG_WITH_SKBINFO;
	अगर (SET_WITH_FORCEADD(set))
		cadt_flags |= IPSET_FLAG_WITH_FORCEADD;

	अगर (!cadt_flags)
		वापस 0;
	वापस nla_put_net32(skb, IPSET_ATTR_CADT_FLAGS, htonl(cadt_flags));
पूर्ण
EXPORT_SYMBOL_GPL(ip_set_put_flags);

अटल पूर्णांक
ip_set_dump_करोne(काष्ठा netlink_callback *cb)
अणु
	अगर (cb->args[IPSET_CB_ARG0]) अणु
		काष्ठा ip_set_net *inst =
			(काष्ठा ip_set_net *)cb->args[IPSET_CB_NET];
		ip_set_id_t index = (ip_set_id_t)cb->args[IPSET_CB_INDEX];
		काष्ठा ip_set *set = ip_set_ref_netlink(inst, index);

		अगर (set->variant->uref)
			set->variant->uref(set, cb, false);
		pr_debug("release set %s\n", set->name);
		__ip_set_put_netlink(set);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
dump_attrs(काष्ठा nlmsghdr *nlh)
अणु
	स्थिर काष्ठा nlattr *attr;
	पूर्णांक rem;

	pr_debug("dump nlmsg\n");
	nlmsg_क्रम_each_attr(attr, nlh, माप(काष्ठा nfgenmsg), rem) अणु
		pr_debug("type: %u, len %u\n", nla_type(attr), attr->nla_len);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nla_policy
ip_set_dump_policy[IPSET_ATTR_CMD_MAX + 1] = अणु
	[IPSET_ATTR_PROTOCOL]	= अणु .type = NLA_U8 पूर्ण,
	[IPSET_ATTR_SETNAME]	= अणु .type = NLA_NUL_STRING,
				    .len = IPSET_MAXNAMELEN - 1 पूर्ण,
	[IPSET_ATTR_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक
ip_set_dump_start(काष्ठा netlink_callback *cb)
अणु
	काष्ठा nlmsghdr *nlh = nlmsg_hdr(cb->skb);
	पूर्णांक min_len = nlmsg_total_size(माप(काष्ठा nfgenmsg));
	काष्ठा nlattr *cda[IPSET_ATTR_CMD_MAX + 1];
	काष्ठा nlattr *attr = (व्योम *)nlh + min_len;
	काष्ठा sk_buff *skb = cb->skb;
	काष्ठा ip_set_net *inst = ip_set_pernet(sock_net(skb->sk));
	u32 dump_type;
	पूर्णांक ret;

	ret = nla_parse(cda, IPSET_ATTR_CMD_MAX, attr,
			nlh->nlmsg_len - min_len,
			ip_set_dump_policy, शून्य);
	अगर (ret)
		जाओ error;

	cb->args[IPSET_CB_PROTO] = nla_get_u8(cda[IPSET_ATTR_PROTOCOL]);
	अगर (cda[IPSET_ATTR_SETNAME]) अणु
		ip_set_id_t index;
		काष्ठा ip_set *set;

		set = find_set_and_id(inst, nla_data(cda[IPSET_ATTR_SETNAME]),
				      &index);
		अगर (!set) अणु
			ret = -ENOENT;
			जाओ error;
		पूर्ण
		dump_type = DUMP_ONE;
		cb->args[IPSET_CB_INDEX] = index;
	पूर्ण अन्यथा अणु
		dump_type = DUMP_ALL;
	पूर्ण

	अगर (cda[IPSET_ATTR_FLAGS]) अणु
		u32 f = ip_set_get_h32(cda[IPSET_ATTR_FLAGS]);

		dump_type |= (f << 16);
	पूर्ण
	cb->args[IPSET_CB_NET] = (अचिन्हित दीर्घ)inst;
	cb->args[IPSET_CB_DUMP] = dump_type;

	वापस 0;

error:
	/* We have to create and send the error message manually :-( */
	अगर (nlh->nlmsg_flags & NLM_F_ACK) अणु
		netlink_ack(cb->skb, nlh, ret, शून्य);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
ip_set_dump_करो(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	ip_set_id_t index = IPSET_INVALID_ID, max;
	काष्ठा ip_set *set = शून्य;
	काष्ठा nlmsghdr *nlh = शून्य;
	अचिन्हित पूर्णांक flags = NETLINK_CB(cb->skb).portid ? NLM_F_MULTI : 0;
	काष्ठा ip_set_net *inst = ip_set_pernet(sock_net(skb->sk));
	u32 dump_type, dump_flags;
	bool is_destroyed;
	पूर्णांक ret = 0;

	अगर (!cb->args[IPSET_CB_DUMP])
		वापस -EINVAL;

	अगर (cb->args[IPSET_CB_INDEX] >= inst->ip_set_max)
		जाओ out;

	dump_type = DUMP_TYPE(cb->args[IPSET_CB_DUMP]);
	dump_flags = DUMP_FLAGS(cb->args[IPSET_CB_DUMP]);
	max = dump_type == DUMP_ONE ? cb->args[IPSET_CB_INDEX] + 1
				    : inst->ip_set_max;
dump_last:
	pr_debug("dump type, flag: %u %u index: %ld\n",
		 dump_type, dump_flags, cb->args[IPSET_CB_INDEX]);
	क्रम (; cb->args[IPSET_CB_INDEX] < max; cb->args[IPSET_CB_INDEX]++) अणु
		index = (ip_set_id_t)cb->args[IPSET_CB_INDEX];
		ग_लिखो_lock_bh(&ip_set_ref_lock);
		set = ip_set(inst, index);
		is_destroyed = inst->is_destroyed;
		अगर (!set || is_destroyed) अणु
			ग_लिखो_unlock_bh(&ip_set_ref_lock);
			अगर (dump_type == DUMP_ONE) अणु
				ret = -ENOENT;
				जाओ out;
			पूर्ण
			अगर (is_destroyed) अणु
				/* All sets are just being destroyed */
				ret = 0;
				जाओ out;
			पूर्ण
			जारी;
		पूर्ण
		/* When dumping all sets, we must dump "sorted"
		 * so that lists (जोड़s of sets) are dumped last.
		 */
		अगर (dump_type != DUMP_ONE &&
		    ((dump_type == DUMP_ALL) ==
		     !!(set->type->features & IPSET_DUMP_LAST))) अणु
			ग_लिखो_unlock_bh(&ip_set_ref_lock);
			जारी;
		पूर्ण
		pr_debug("List set: %s\n", set->name);
		अगर (!cb->args[IPSET_CB_ARG0]) अणु
			/* Start listing: make sure set won't be destroyed */
			pr_debug("reference set\n");
			set->ref_netlink++;
		पूर्ण
		ग_लिखो_unlock_bh(&ip_set_ref_lock);
		nlh = start_msg(skb, NETLINK_CB(cb->skb).portid,
				cb->nlh->nlmsg_seq, flags,
				IPSET_CMD_LIST);
		अगर (!nlh) अणु
			ret = -EMSGSIZE;
			जाओ release_refcount;
		पूर्ण
		अगर (nla_put_u8(skb, IPSET_ATTR_PROTOCOL,
			       cb->args[IPSET_CB_PROTO]) ||
		    nla_put_string(skb, IPSET_ATTR_SETNAME, set->name))
			जाओ nla_put_failure;
		अगर (dump_flags & IPSET_FLAG_LIST_SETNAME)
			जाओ next_set;
		चयन (cb->args[IPSET_CB_ARG0]) अणु
		हाल 0:
			/* Core header data */
			अगर (nla_put_string(skb, IPSET_ATTR_TYPENAME,
					   set->type->name) ||
			    nla_put_u8(skb, IPSET_ATTR_FAMILY,
				       set->family) ||
			    nla_put_u8(skb, IPSET_ATTR_REVISION,
				       set->revision))
				जाओ nla_put_failure;
			अगर (cb->args[IPSET_CB_PROTO] > IPSET_PROTOCOL_MIN &&
			    nla_put_net16(skb, IPSET_ATTR_INDEX, htons(index)))
				जाओ nla_put_failure;
			ret = set->variant->head(set, skb);
			अगर (ret < 0)
				जाओ release_refcount;
			अगर (dump_flags & IPSET_FLAG_LIST_HEADER)
				जाओ next_set;
			अगर (set->variant->uref)
				set->variant->uref(set, cb, true);
			fallthrough;
		शेष:
			ret = set->variant->list(set, skb, cb);
			अगर (!cb->args[IPSET_CB_ARG0])
				/* Set is करोne, proceed with next one */
				जाओ next_set;
			जाओ release_refcount;
		पूर्ण
	पूर्ण
	/* If we dump all sets, जारी with dumping last ones */
	अगर (dump_type == DUMP_ALL) अणु
		dump_type = DUMP_LAST;
		cb->args[IPSET_CB_DUMP] = dump_type | (dump_flags << 16);
		cb->args[IPSET_CB_INDEX] = 0;
		अगर (set && set->variant->uref)
			set->variant->uref(set, cb, false);
		जाओ dump_last;
	पूर्ण
	जाओ out;

nla_put_failure:
	ret = -EFAULT;
next_set:
	अगर (dump_type == DUMP_ONE)
		cb->args[IPSET_CB_INDEX] = IPSET_INVALID_ID;
	अन्यथा
		cb->args[IPSET_CB_INDEX]++;
release_refcount:
	/* If there was an error or set is करोne, release set */
	अगर (ret || !cb->args[IPSET_CB_ARG0]) अणु
		set = ip_set_ref_netlink(inst, index);
		अगर (set->variant->uref)
			set->variant->uref(set, cb, false);
		pr_debug("release set %s\n", set->name);
		__ip_set_put_netlink(set);
		cb->args[IPSET_CB_ARG0] = 0;
	पूर्ण
out:
	अगर (nlh) अणु
		nlmsg_end(skb, nlh);
		pr_debug("nlmsg_len: %u\n", nlh->nlmsg_len);
		dump_attrs(nlh);
	पूर्ण

	वापस ret < 0 ? ret : skb->len;
पूर्ण

अटल पूर्णांक ip_set_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
		       स्थिर काष्ठा nlattr * स्थिर attr[])
अणु
	अगर (unlikely(protocol_min_failed(attr)))
		वापस -IPSET_ERR_PROTOCOL;

	अणु
		काष्ठा netlink_dump_control c = अणु
			.start = ip_set_dump_start,
			.dump = ip_set_dump_करो,
			.करोne = ip_set_dump_करोne,
		पूर्ण;
		वापस netlink_dump_start(info->sk, skb, info->nlh, &c);
	पूर्ण
पूर्ण

/* Add, del and test */

अटल स्थिर काष्ठा nla_policy ip_set_adt_policy[IPSET_ATTR_CMD_MAX + 1] = अणु
	[IPSET_ATTR_PROTOCOL]	= अणु .type = NLA_U8 पूर्ण,
	[IPSET_ATTR_SETNAME]	= अणु .type = NLA_NUL_STRING,
				    .len = IPSET_MAXNAMELEN - 1 पूर्ण,
	[IPSET_ATTR_LINENO]	= अणु .type = NLA_U32 पूर्ण,
	[IPSET_ATTR_DATA]	= अणु .type = NLA_NESTED पूर्ण,
	[IPSET_ATTR_ADT]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक
call_ad(काष्ठा sock *ctnl, काष्ठा sk_buff *skb, काष्ठा ip_set *set,
	काष्ठा nlattr *tb[], क्रमागत ipset_adt adt,
	u32 flags, bool use_lineno)
अणु
	पूर्णांक ret;
	u32 lineno = 0;
	bool eexist = flags & IPSET_FLAG_EXIST, retried = false;

	करो अणु
		ip_set_lock(set);
		ret = set->variant->uadt(set, tb, adt, &lineno, flags, retried);
		ip_set_unlock(set);
		retried = true;
	पूर्ण जबतक (ret == -EAGAIN &&
		 set->variant->resize &&
		 (ret = set->variant->resize(set, retried)) == 0);

	अगर (!ret || (ret == -IPSET_ERR_EXIST && eexist))
		वापस 0;
	अगर (lineno && use_lineno) अणु
		/* Error in restore/batch mode: send back lineno */
		काष्ठा nlmsghdr *rep, *nlh = nlmsg_hdr(skb);
		काष्ठा sk_buff *skb2;
		काष्ठा nlmsgerr *errmsg;
		माप_प्रकार payload = min(SIZE_MAX,
				     माप(*errmsg) + nlmsg_len(nlh));
		पूर्णांक min_len = nlmsg_total_size(माप(काष्ठा nfgenmsg));
		काष्ठा nlattr *cda[IPSET_ATTR_CMD_MAX + 1];
		काष्ठा nlattr *cmdattr;
		u32 *errline;

		skb2 = nlmsg_new(payload, GFP_KERNEL);
		अगर (!skb2)
			वापस -ENOMEM;
		rep = __nlmsg_put(skb2, NETLINK_CB(skb).portid,
				  nlh->nlmsg_seq, NLMSG_ERROR, payload, 0);
		errmsg = nlmsg_data(rep);
		errmsg->error = ret;
		स_नकल(&errmsg->msg, nlh, nlh->nlmsg_len);
		cmdattr = (व्योम *)&errmsg->msg + min_len;

		ret = nla_parse(cda, IPSET_ATTR_CMD_MAX, cmdattr,
				nlh->nlmsg_len - min_len, ip_set_adt_policy,
				शून्य);

		अगर (ret) अणु
			nlmsg_मुक्त(skb2);
			वापस ret;
		पूर्ण
		errline = nla_data(cda[IPSET_ATTR_LINENO]);

		*errline = lineno;

		netlink_unicast(ctnl, skb2, NETLINK_CB(skb).portid,
				MSG_DONTWAIT);
		/* Signal netlink not to send its ACK/errmsg.  */
		वापस -EINTR;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ip_set_ad(काष्ठा net *net, काष्ठा sock *ctnl,
		     काष्ठा sk_buff *skb,
		     क्रमागत ipset_adt adt,
		     स्थिर काष्ठा nlmsghdr *nlh,
		     स्थिर काष्ठा nlattr * स्थिर attr[],
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip_set_net *inst = ip_set_pernet(net);
	काष्ठा ip_set *set;
	काष्ठा nlattr *tb[IPSET_ATTR_ADT_MAX + 1] = अणुपूर्ण;
	स्थिर काष्ठा nlattr *nla;
	u32 flags = flag_exist(nlh);
	bool use_lineno;
	पूर्णांक ret = 0;

	अगर (unlikely(protocol_min_failed(attr) ||
		     !attr[IPSET_ATTR_SETNAME] ||
		     !((attr[IPSET_ATTR_DATA] != शून्य) ^
		       (attr[IPSET_ATTR_ADT] != शून्य)) ||
		     (attr[IPSET_ATTR_DATA] &&
		      !flag_nested(attr[IPSET_ATTR_DATA])) ||
		     (attr[IPSET_ATTR_ADT] &&
		      (!flag_nested(attr[IPSET_ATTR_ADT]) ||
		       !attr[IPSET_ATTR_LINENO]))))
		वापस -IPSET_ERR_PROTOCOL;

	set = find_set(inst, nla_data(attr[IPSET_ATTR_SETNAME]));
	अगर (!set)
		वापस -ENOENT;

	use_lineno = !!attr[IPSET_ATTR_LINENO];
	अगर (attr[IPSET_ATTR_DATA]) अणु
		अगर (nla_parse_nested(tb, IPSET_ATTR_ADT_MAX,
				     attr[IPSET_ATTR_DATA],
				     set->type->adt_policy, शून्य))
			वापस -IPSET_ERR_PROTOCOL;
		ret = call_ad(ctnl, skb, set, tb, adt, flags,
			      use_lineno);
	पूर्ण अन्यथा अणु
		पूर्णांक nla_rem;

		nla_क्रम_each_nested(nla, attr[IPSET_ATTR_ADT], nla_rem) अणु
			अगर (nla_type(nla) != IPSET_ATTR_DATA ||
			    !flag_nested(nla) ||
			    nla_parse_nested(tb, IPSET_ATTR_ADT_MAX, nla,
					     set->type->adt_policy, शून्य))
				वापस -IPSET_ERR_PROTOCOL;
			ret = call_ad(ctnl, skb, set, tb, adt,
				      flags, use_lineno);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ip_set_uadd(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
		       स्थिर काष्ठा nlattr * स्थिर attr[])
अणु
	वापस ip_set_ad(info->net, info->sk, skb,
			 IPSET_ADD, info->nlh, attr, info->extack);
पूर्ण

अटल पूर्णांक ip_set_udel(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
		       स्थिर काष्ठा nlattr * स्थिर attr[])
अणु
	वापस ip_set_ad(info->net, info->sk, skb,
			 IPSET_DEL, info->nlh, attr, info->extack);
पूर्ण

अटल पूर्णांक ip_set_utest(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			स्थिर काष्ठा nlattr * स्थिर attr[])
अणु
	काष्ठा ip_set_net *inst = ip_set_pernet(info->net);
	काष्ठा ip_set *set;
	काष्ठा nlattr *tb[IPSET_ATTR_ADT_MAX + 1] = अणुपूर्ण;
	पूर्णांक ret = 0;
	u32 lineno;

	अगर (unlikely(protocol_min_failed(attr) ||
		     !attr[IPSET_ATTR_SETNAME] ||
		     !attr[IPSET_ATTR_DATA] ||
		     !flag_nested(attr[IPSET_ATTR_DATA])))
		वापस -IPSET_ERR_PROTOCOL;

	set = find_set(inst, nla_data(attr[IPSET_ATTR_SETNAME]));
	अगर (!set)
		वापस -ENOENT;

	अगर (nla_parse_nested(tb, IPSET_ATTR_ADT_MAX, attr[IPSET_ATTR_DATA],
			     set->type->adt_policy, शून्य))
		वापस -IPSET_ERR_PROTOCOL;

	rcu_पढ़ो_lock_bh();
	ret = set->variant->uadt(set, tb, IPSET_TEST, &lineno, 0, 0);
	rcu_पढ़ो_unlock_bh();
	/* Userspace can't trigger element to be re-added */
	अगर (ret == -EAGAIN)
		ret = 1;

	वापस ret > 0 ? 0 : -IPSET_ERR_EXIST;
पूर्ण

/* Get headed data of a set */

अटल पूर्णांक ip_set_header(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			 स्थिर काष्ठा nlattr * स्थिर attr[])
अणु
	काष्ठा ip_set_net *inst = ip_set_pernet(info->net);
	स्थिर काष्ठा ip_set *set;
	काष्ठा sk_buff *skb2;
	काष्ठा nlmsghdr *nlh2;
	पूर्णांक ret = 0;

	अगर (unlikely(protocol_min_failed(attr) ||
		     !attr[IPSET_ATTR_SETNAME]))
		वापस -IPSET_ERR_PROTOCOL;

	set = find_set(inst, nla_data(attr[IPSET_ATTR_SETNAME]));
	अगर (!set)
		वापस -ENOENT;

	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!skb2)
		वापस -ENOMEM;

	nlh2 = start_msg(skb2, NETLINK_CB(skb).portid, info->nlh->nlmsg_seq, 0,
			 IPSET_CMD_HEADER);
	अगर (!nlh2)
		जाओ nlmsg_failure;
	अगर (nla_put_u8(skb2, IPSET_ATTR_PROTOCOL, protocol(attr)) ||
	    nla_put_string(skb2, IPSET_ATTR_SETNAME, set->name) ||
	    nla_put_string(skb2, IPSET_ATTR_TYPENAME, set->type->name) ||
	    nla_put_u8(skb2, IPSET_ATTR_FAMILY, set->family) ||
	    nla_put_u8(skb2, IPSET_ATTR_REVISION, set->revision))
		जाओ nla_put_failure;
	nlmsg_end(skb2, nlh2);

	ret = netlink_unicast(info->sk, skb2, NETLINK_CB(skb).portid,
			      MSG_DONTWAIT);
	अगर (ret < 0)
		वापस ret;

	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb2, nlh2);
nlmsg_failure:
	kमुक्त_skb(skb2);
	वापस -EMSGSIZE;
पूर्ण

/* Get type data */

अटल स्थिर काष्ठा nla_policy ip_set_type_policy[IPSET_ATTR_CMD_MAX + 1] = अणु
	[IPSET_ATTR_PROTOCOL]	= अणु .type = NLA_U8 पूर्ण,
	[IPSET_ATTR_TYPENAME]	= अणु .type = NLA_NUL_STRING,
				    .len = IPSET_MAXNAMELEN - 1 पूर्ण,
	[IPSET_ATTR_FAMILY]	= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक ip_set_type(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
		       स्थिर काष्ठा nlattr * स्थिर attr[])
अणु
	काष्ठा sk_buff *skb2;
	काष्ठा nlmsghdr *nlh2;
	u8 family, min, max;
	स्थिर अक्षर *typename;
	पूर्णांक ret = 0;

	अगर (unlikely(protocol_min_failed(attr) ||
		     !attr[IPSET_ATTR_TYPENAME] ||
		     !attr[IPSET_ATTR_FAMILY]))
		वापस -IPSET_ERR_PROTOCOL;

	family = nla_get_u8(attr[IPSET_ATTR_FAMILY]);
	typename = nla_data(attr[IPSET_ATTR_TYPENAME]);
	ret = find_set_type_minmax(typename, family, &min, &max);
	अगर (ret)
		वापस ret;

	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!skb2)
		वापस -ENOMEM;

	nlh2 = start_msg(skb2, NETLINK_CB(skb).portid, info->nlh->nlmsg_seq, 0,
			 IPSET_CMD_TYPE);
	अगर (!nlh2)
		जाओ nlmsg_failure;
	अगर (nla_put_u8(skb2, IPSET_ATTR_PROTOCOL, protocol(attr)) ||
	    nla_put_string(skb2, IPSET_ATTR_TYPENAME, typename) ||
	    nla_put_u8(skb2, IPSET_ATTR_FAMILY, family) ||
	    nla_put_u8(skb2, IPSET_ATTR_REVISION, max) ||
	    nla_put_u8(skb2, IPSET_ATTR_REVISION_MIN, min))
		जाओ nla_put_failure;
	nlmsg_end(skb2, nlh2);

	pr_debug("Send TYPE, nlmsg_len: %u\n", nlh2->nlmsg_len);
	ret = netlink_unicast(info->sk, skb2, NETLINK_CB(skb).portid,
			      MSG_DONTWAIT);
	अगर (ret < 0)
		वापस ret;

	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb2, nlh2);
nlmsg_failure:
	kमुक्त_skb(skb2);
	वापस -EMSGSIZE;
पूर्ण

/* Get protocol version */

अटल स्थिर काष्ठा nla_policy
ip_set_protocol_policy[IPSET_ATTR_CMD_MAX + 1] = अणु
	[IPSET_ATTR_PROTOCOL]	= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक ip_set_protocol(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			   स्थिर काष्ठा nlattr * स्थिर attr[])
अणु
	काष्ठा sk_buff *skb2;
	काष्ठा nlmsghdr *nlh2;
	पूर्णांक ret = 0;

	अगर (unlikely(!attr[IPSET_ATTR_PROTOCOL]))
		वापस -IPSET_ERR_PROTOCOL;

	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!skb2)
		वापस -ENOMEM;

	nlh2 = start_msg(skb2, NETLINK_CB(skb).portid, info->nlh->nlmsg_seq, 0,
			 IPSET_CMD_PROTOCOL);
	अगर (!nlh2)
		जाओ nlmsg_failure;
	अगर (nla_put_u8(skb2, IPSET_ATTR_PROTOCOL, IPSET_PROTOCOL))
		जाओ nla_put_failure;
	अगर (nla_put_u8(skb2, IPSET_ATTR_PROTOCOL_MIN, IPSET_PROTOCOL_MIN))
		जाओ nla_put_failure;
	nlmsg_end(skb2, nlh2);

	ret = netlink_unicast(info->sk, skb2, NETLINK_CB(skb).portid,
			      MSG_DONTWAIT);
	अगर (ret < 0)
		वापस ret;

	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb2, nlh2);
nlmsg_failure:
	kमुक्त_skb(skb2);
	वापस -EMSGSIZE;
पूर्ण

/* Get set by name or index, from userspace */

अटल पूर्णांक ip_set_byname(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			 स्थिर काष्ठा nlattr * स्थिर attr[])
अणु
	काष्ठा ip_set_net *inst = ip_set_pernet(info->net);
	काष्ठा sk_buff *skb2;
	काष्ठा nlmsghdr *nlh2;
	ip_set_id_t id = IPSET_INVALID_ID;
	स्थिर काष्ठा ip_set *set;
	पूर्णांक ret = 0;

	अगर (unlikely(protocol_failed(attr) ||
		     !attr[IPSET_ATTR_SETNAME]))
		वापस -IPSET_ERR_PROTOCOL;

	set = find_set_and_id(inst, nla_data(attr[IPSET_ATTR_SETNAME]), &id);
	अगर (id == IPSET_INVALID_ID)
		वापस -ENOENT;

	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!skb2)
		वापस -ENOMEM;

	nlh2 = start_msg(skb2, NETLINK_CB(skb).portid, info->nlh->nlmsg_seq, 0,
			 IPSET_CMD_GET_BYNAME);
	अगर (!nlh2)
		जाओ nlmsg_failure;
	अगर (nla_put_u8(skb2, IPSET_ATTR_PROTOCOL, protocol(attr)) ||
	    nla_put_u8(skb2, IPSET_ATTR_FAMILY, set->family) ||
	    nla_put_net16(skb2, IPSET_ATTR_INDEX, htons(id)))
		जाओ nla_put_failure;
	nlmsg_end(skb2, nlh2);

	ret = netlink_unicast(info->sk, skb2, NETLINK_CB(skb).portid,
			      MSG_DONTWAIT);
	अगर (ret < 0)
		वापस ret;

	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb2, nlh2);
nlmsg_failure:
	kमुक्त_skb(skb2);
	वापस -EMSGSIZE;
पूर्ण

अटल स्थिर काष्ठा nla_policy ip_set_index_policy[IPSET_ATTR_CMD_MAX + 1] = अणु
	[IPSET_ATTR_PROTOCOL]	= अणु .type = NLA_U8 पूर्ण,
	[IPSET_ATTR_INDEX]	= अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल पूर्णांक ip_set_byindex(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			  स्थिर काष्ठा nlattr * स्थिर attr[])
अणु
	काष्ठा ip_set_net *inst = ip_set_pernet(info->net);
	काष्ठा sk_buff *skb2;
	काष्ठा nlmsghdr *nlh2;
	ip_set_id_t id = IPSET_INVALID_ID;
	स्थिर काष्ठा ip_set *set;
	पूर्णांक ret = 0;

	अगर (unlikely(protocol_failed(attr) ||
		     !attr[IPSET_ATTR_INDEX]))
		वापस -IPSET_ERR_PROTOCOL;

	id = ip_set_get_h16(attr[IPSET_ATTR_INDEX]);
	अगर (id >= inst->ip_set_max)
		वापस -ENOENT;
	set = ip_set(inst, id);
	अगर (set == शून्य)
		वापस -ENOENT;

	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!skb2)
		वापस -ENOMEM;

	nlh2 = start_msg(skb2, NETLINK_CB(skb).portid, info->nlh->nlmsg_seq, 0,
			 IPSET_CMD_GET_BYINDEX);
	अगर (!nlh2)
		जाओ nlmsg_failure;
	अगर (nla_put_u8(skb2, IPSET_ATTR_PROTOCOL, protocol(attr)) ||
	    nla_put_string(skb2, IPSET_ATTR_SETNAME, set->name))
		जाओ nla_put_failure;
	nlmsg_end(skb2, nlh2);

	ret = netlink_unicast(info->sk, skb2, NETLINK_CB(skb).portid,
			      MSG_DONTWAIT);
	अगर (ret < 0)
		वापस ret;

	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb2, nlh2);
nlmsg_failure:
	kमुक्त_skb(skb2);
	वापस -EMSGSIZE;
पूर्ण

अटल स्थिर काष्ठा nfnl_callback ip_set_netlink_subsys_cb[IPSET_MSG_MAX] = अणु
	[IPSET_CMD_NONE]	= अणु
		.call		= ip_set_none,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= IPSET_ATTR_CMD_MAX,
	पूर्ण,
	[IPSET_CMD_CREATE]	= अणु
		.call		= ip_set_create,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= IPSET_ATTR_CMD_MAX,
		.policy		= ip_set_create_policy,
	पूर्ण,
	[IPSET_CMD_DESTROY]	= अणु
		.call		= ip_set_destroy,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= IPSET_ATTR_CMD_MAX,
		.policy		= ip_set_setname_policy,
	पूर्ण,
	[IPSET_CMD_FLUSH]	= अणु
		.call		= ip_set_flush,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= IPSET_ATTR_CMD_MAX,
		.policy		= ip_set_setname_policy,
	पूर्ण,
	[IPSET_CMD_RENAME]	= अणु
		.call		= ip_set_नाम,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= IPSET_ATTR_CMD_MAX,
		.policy		= ip_set_setname2_policy,
	पूर्ण,
	[IPSET_CMD_SWAP]	= अणु
		.call		= ip_set_swap,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= IPSET_ATTR_CMD_MAX,
		.policy		= ip_set_setname2_policy,
	पूर्ण,
	[IPSET_CMD_LIST]	= अणु
		.call		= ip_set_dump,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= IPSET_ATTR_CMD_MAX,
		.policy		= ip_set_dump_policy,
	पूर्ण,
	[IPSET_CMD_SAVE]	= अणु
		.call		= ip_set_dump,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= IPSET_ATTR_CMD_MAX,
		.policy		= ip_set_setname_policy,
	पूर्ण,
	[IPSET_CMD_ADD]	= अणु
		.call		= ip_set_uadd,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= IPSET_ATTR_CMD_MAX,
		.policy		= ip_set_adt_policy,
	पूर्ण,
	[IPSET_CMD_DEL]	= अणु
		.call		= ip_set_udel,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= IPSET_ATTR_CMD_MAX,
		.policy		= ip_set_adt_policy,
	पूर्ण,
	[IPSET_CMD_TEST]	= अणु
		.call		= ip_set_utest,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= IPSET_ATTR_CMD_MAX,
		.policy		= ip_set_adt_policy,
	पूर्ण,
	[IPSET_CMD_HEADER]	= अणु
		.call		= ip_set_header,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= IPSET_ATTR_CMD_MAX,
		.policy		= ip_set_setname_policy,
	पूर्ण,
	[IPSET_CMD_TYPE]	= अणु
		.call		= ip_set_type,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= IPSET_ATTR_CMD_MAX,
		.policy		= ip_set_type_policy,
	पूर्ण,
	[IPSET_CMD_PROTOCOL]	= अणु
		.call		= ip_set_protocol,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= IPSET_ATTR_CMD_MAX,
		.policy		= ip_set_protocol_policy,
	पूर्ण,
	[IPSET_CMD_GET_BYNAME]	= अणु
		.call		= ip_set_byname,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= IPSET_ATTR_CMD_MAX,
		.policy		= ip_set_setname_policy,
	पूर्ण,
	[IPSET_CMD_GET_BYINDEX]	= अणु
		.call		= ip_set_byindex,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= IPSET_ATTR_CMD_MAX,
		.policy		= ip_set_index_policy,
	पूर्ण,
पूर्ण;

अटल काष्ठा nfnetlink_subप्रणाली ip_set_netlink_subsys __पढ़ो_mostly = अणु
	.name		= "ip_set",
	.subsys_id	= NFNL_SUBSYS_IPSET,
	.cb_count	= IPSET_MSG_MAX,
	.cb		= ip_set_netlink_subsys_cb,
पूर्ण;

/* Interface to iptables/ip6tables */

अटल पूर्णांक
ip_set_sockfn_get(काष्ठा sock *sk, पूर्णांक optval, व्योम __user *user, पूर्णांक *len)
अणु
	अचिन्हित पूर्णांक *op;
	व्योम *data;
	पूर्णांक copylen = *len, ret = 0;
	काष्ठा net *net = sock_net(sk);
	काष्ठा ip_set_net *inst = ip_set_pernet(net);

	अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;
	अगर (optval != SO_IP_SET)
		वापस -EBADF;
	अगर (*len < माप(अचिन्हित पूर्णांक))
		वापस -EINVAL;

	data = vदो_स्मृति(*len);
	अगर (!data)
		वापस -ENOMEM;
	अगर (copy_from_user(data, user, *len) != 0) अणु
		ret = -EFAULT;
		जाओ करोne;
	पूर्ण
	op = data;

	अगर (*op < IP_SET_OP_VERSION) अणु
		/* Check the version at the beginning of operations */
		काष्ठा ip_set_req_version *req_version = data;

		अगर (*len < माप(काष्ठा ip_set_req_version)) अणु
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण

		अगर (req_version->version < IPSET_PROTOCOL_MIN) अणु
			ret = -EPROTO;
			जाओ करोne;
		पूर्ण
	पूर्ण

	चयन (*op) अणु
	हाल IP_SET_OP_VERSION: अणु
		काष्ठा ip_set_req_version *req_version = data;

		अगर (*len != माप(काष्ठा ip_set_req_version)) अणु
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण

		req_version->version = IPSET_PROTOCOL;
		अगर (copy_to_user(user, req_version,
				 माप(काष्ठा ip_set_req_version)))
			ret = -EFAULT;
		जाओ करोne;
	पूर्ण
	हाल IP_SET_OP_GET_BYNAME: अणु
		काष्ठा ip_set_req_get_set *req_get = data;
		ip_set_id_t id;

		अगर (*len != माप(काष्ठा ip_set_req_get_set)) अणु
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण
		req_get->set.name[IPSET_MAXNAMELEN - 1] = '\0';
		nfnl_lock(NFNL_SUBSYS_IPSET);
		find_set_and_id(inst, req_get->set.name, &id);
		req_get->set.index = id;
		nfnl_unlock(NFNL_SUBSYS_IPSET);
		जाओ copy;
	पूर्ण
	हाल IP_SET_OP_GET_FNAME: अणु
		काष्ठा ip_set_req_get_set_family *req_get = data;
		ip_set_id_t id;

		अगर (*len != माप(काष्ठा ip_set_req_get_set_family)) अणु
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण
		req_get->set.name[IPSET_MAXNAMELEN - 1] = '\0';
		nfnl_lock(NFNL_SUBSYS_IPSET);
		find_set_and_id(inst, req_get->set.name, &id);
		req_get->set.index = id;
		अगर (id != IPSET_INVALID_ID)
			req_get->family = ip_set(inst, id)->family;
		nfnl_unlock(NFNL_SUBSYS_IPSET);
		जाओ copy;
	पूर्ण
	हाल IP_SET_OP_GET_BYINDEX: अणु
		काष्ठा ip_set_req_get_set *req_get = data;
		काष्ठा ip_set *set;

		अगर (*len != माप(काष्ठा ip_set_req_get_set) ||
		    req_get->set.index >= inst->ip_set_max) अणु
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण
		nfnl_lock(NFNL_SUBSYS_IPSET);
		set = ip_set(inst, req_get->set.index);
		ret = strscpy(req_get->set.name, set ? set->name : "",
			      IPSET_MAXNAMELEN);
		nfnl_unlock(NFNL_SUBSYS_IPSET);
		अगर (ret < 0)
			जाओ करोne;
		जाओ copy;
	पूर्ण
	शेष:
		ret = -EBADMSG;
		जाओ करोne;
	पूर्ण	/* end of चयन(op) */

copy:
	अगर (copy_to_user(user, data, copylen))
		ret = -EFAULT;

करोne:
	vमुक्त(data);
	अगर (ret > 0)
		ret = 0;
	वापस ret;
पूर्ण

अटल काष्ठा nf_sockopt_ops so_set __पढ़ो_mostly = अणु
	.pf		= PF_INET,
	.get_opपंचांगin	= SO_IP_SET,
	.get_opपंचांगax	= SO_IP_SET + 1,
	.get		= ip_set_sockfn_get,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __net_init
ip_set_net_init(काष्ठा net *net)
अणु
	काष्ठा ip_set_net *inst = ip_set_pernet(net);
	काष्ठा ip_set **list;

	inst->ip_set_max = max_sets ? max_sets : CONFIG_IP_SET_MAX;
	अगर (inst->ip_set_max >= IPSET_INVALID_ID)
		inst->ip_set_max = IPSET_INVALID_ID - 1;

	list = kvसुस्मृति(inst->ip_set_max, माप(काष्ठा ip_set *), GFP_KERNEL);
	अगर (!list)
		वापस -ENOMEM;
	inst->is_deleted = false;
	inst->is_destroyed = false;
	rcu_assign_poपूर्णांकer(inst->ip_set_list, list);
	वापस 0;
पूर्ण

अटल व्योम __net_निकास
ip_set_net_निकास(काष्ठा net *net)
अणु
	काष्ठा ip_set_net *inst = ip_set_pernet(net);

	काष्ठा ip_set *set = शून्य;
	ip_set_id_t i;

	inst->is_deleted = true; /* flag क्रम ip_set_nfnl_put */

	nfnl_lock(NFNL_SUBSYS_IPSET);
	क्रम (i = 0; i < inst->ip_set_max; i++) अणु
		set = ip_set(inst, i);
		अगर (set) अणु
			ip_set(inst, i) = शून्य;
			ip_set_destroy_set(set);
		पूर्ण
	पूर्ण
	nfnl_unlock(NFNL_SUBSYS_IPSET);
	kvमुक्त(rcu_dereference_रक्षित(inst->ip_set_list, 1));
पूर्ण

अटल काष्ठा pernet_operations ip_set_net_ops = अणु
	.init	= ip_set_net_init,
	.निकास   = ip_set_net_निकास,
	.id	= &ip_set_net_id,
	.size	= माप(काष्ठा ip_set_net),
पूर्ण;

अटल पूर्णांक __init
ip_set_init(व्योम)
अणु
	पूर्णांक ret = रेजिस्टर_pernet_subsys(&ip_set_net_ops);

	अगर (ret) अणु
		pr_err("ip_set: cannot register pernet_subsys.\n");
		वापस ret;
	पूर्ण

	ret = nfnetlink_subsys_रेजिस्टर(&ip_set_netlink_subsys);
	अगर (ret != 0) अणु
		pr_err("ip_set: cannot register with nfnetlink.\n");
		unरेजिस्टर_pernet_subsys(&ip_set_net_ops);
		वापस ret;
	पूर्ण

	ret = nf_रेजिस्टर_sockopt(&so_set);
	अगर (ret != 0) अणु
		pr_err("SO_SET registry failed: %d\n", ret);
		nfnetlink_subsys_unरेजिस्टर(&ip_set_netlink_subsys);
		unरेजिस्टर_pernet_subsys(&ip_set_net_ops);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास
ip_set_fini(व्योम)
अणु
	nf_unरेजिस्टर_sockopt(&so_set);
	nfnetlink_subsys_unरेजिस्टर(&ip_set_netlink_subsys);

	unरेजिस्टर_pernet_subsys(&ip_set_net_ops);
	pr_debug("these are the famous last words\n");
पूर्ण

module_init(ip_set_init);
module_निकास(ip_set_fini);

MODULE_DESCRIPTION("ip_set: protocol " __stringअगरy(IPSET_PROTOCOL));
