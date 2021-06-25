<शैली गुरु>
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM neigh

#अगर !defined(_TRACE_NEIGH_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_NEIGH_H

#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <net/neighbour.h>

#घोषणा neigh_state_str(state)				\
	__prपूर्णांक_symbolic(state,				\
		अणु NUD_INCOMPLETE, "incomplete" पूर्ण,	\
		अणु NUD_REACHABLE, "reachable" पूर्ण,		\
		अणु NUD_STALE, "stale" पूर्ण,			\
		अणु NUD_DELAY, "delay" पूर्ण,			\
		अणु NUD_PROBE, "probe" पूर्ण,			\
		अणु NUD_FAILED, "failed" पूर्ण,		\
		अणु NUD_NOARP, "noarp" पूर्ण,			\
		अणु NUD_PERMANENT, "permanent"पूर्ण)

TRACE_EVENT(neigh_create,

	TP_PROTO(काष्ठा neigh_table *tbl, काष्ठा net_device *dev,
		 स्थिर व्योम *pkey, स्थिर काष्ठा neighbour *n,
		 bool exempt_from_gc),

	TP_ARGS(tbl, dev, pkey, n, exempt_from_gc),

	TP_STRUCT__entry(
		__field(u32, family)
		__dynamic_array(अक्षर,  dev,   IFNAMSIZ )
		__field(पूर्णांक, entries)
		__field(u8, created)
		__field(u8, gc_exempt)
		__array(u8, primary_key4, 4)
		__array(u8, primary_key6, 16)
	),

	TP_fast_assign(
		काष्ठा in6_addr *pin6;
		__be32 *p32;

		__entry->family = tbl->family;
		__assign_str(dev, (dev ? dev->name : "NULL"));
		__entry->entries = atomic_पढ़ो(&tbl->gc_entries);
		__entry->created = n != शून्य;
		__entry->gc_exempt = exempt_from_gc;
		pin6 = (काष्ठा in6_addr *)__entry->primary_key6;
		p32 = (__be32 *)__entry->primary_key4;

		अगर (tbl->family == AF_INET)
			*p32 = *(__be32 *)pkey;
		अन्यथा
			*p32 = 0;

#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (tbl->family == AF_INET6) अणु
			pin6 = (काष्ठा in6_addr *)__entry->primary_key6;
			*pin6 = *(काष्ठा in6_addr *)pkey;
		पूर्ण
#पूर्ण_अगर
	),

	TP_prपूर्णांकk("family %d dev %s entries %d primary_key4 %pI4 primary_key6 %pI6c created %d gc_exempt %d",
		  __entry->family, __get_str(dev), __entry->entries,
		  __entry->primary_key4, __entry->primary_key6,
		  __entry->created, __entry->gc_exempt)
);

TRACE_EVENT(neigh_update,

	TP_PROTO(काष्ठा neighbour *n, स्थिर u8 *lladdr, u8 new,
		 u32 flags, u32 nlmsg_pid),

	TP_ARGS(n, lladdr, new, flags, nlmsg_pid),

	TP_STRUCT__entry(
		__field(u32, family)
		__string(dev, (n->dev ? n->dev->name : "NULL"))
		__array(u8, lladdr, MAX_ADDR_LEN)
		__field(u8, lladdr_len)
		__field(u8, flags)
		__field(u8, nud_state)
		__field(u8, type)
		__field(u8, dead)
		__field(पूर्णांक, refcnt)
		__array(__u8, primary_key4, 4)
		__array(__u8, primary_key6, 16)
		__field(अचिन्हित दीर्घ, confirmed)
		__field(अचिन्हित दीर्घ, updated)
		__field(अचिन्हित दीर्घ, used)
		__array(u8, new_lladdr, MAX_ADDR_LEN)
		__field(u8, new_state)
		__field(u32, update_flags)
		__field(u32, pid)
	),

	TP_fast_assign(
		पूर्णांक lladdr_len = (n->dev ? n->dev->addr_len : MAX_ADDR_LEN);
		काष्ठा in6_addr *pin6;
		__be32 *p32;

		__entry->family = n->tbl->family;
		__assign_str(dev, (n->dev ? n->dev->name : "NULL"));
		__entry->lladdr_len = lladdr_len;
		स_नकल(__entry->lladdr, n->ha, lladdr_len);
		__entry->flags = n->flags;
		__entry->nud_state = n->nud_state;
		__entry->type = n->type;
		__entry->dead = n->dead;
		__entry->refcnt = refcount_पढ़ो(&n->refcnt);
		pin6 = (काष्ठा in6_addr *)__entry->primary_key6;
		p32 = (__be32 *)__entry->primary_key4;

		अगर (n->tbl->family == AF_INET)
			*p32 = *(__be32 *)n->primary_key;
		अन्यथा
			*p32 = 0;

#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (n->tbl->family == AF_INET6) अणु
			pin6 = (काष्ठा in6_addr *)__entry->primary_key6;
			*pin6 = *(काष्ठा in6_addr *)n->primary_key;
		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			ipv6_addr_set_v4mapped(*p32, pin6);
		पूर्ण
		__entry->confirmed = n->confirmed;
		__entry->updated = n->updated;
		__entry->used = n->used;
		अगर (lladdr)
			स_नकल(__entry->new_lladdr, lladdr, lladdr_len);
		__entry->new_state = new;
		__entry->update_flags = flags;
		__entry->pid = nlmsg_pid;
	),

	TP_prपूर्णांकk("family %d dev %s lladdr %s flags %02x nud_state %s type %02x "
		  "dead %d refcnt %d primary_key4 %pI4 primary_key6 %pI6c "
		  "confirmed %lu updated %lu used %lu new_lladdr %s "
		  "new_state %s update_flags %02x pid %d",
		  __entry->family, __get_str(dev),
		  __prपूर्णांक_hex_str(__entry->lladdr, __entry->lladdr_len),
		  __entry->flags, neigh_state_str(__entry->nud_state),
		  __entry->type, __entry->dead, __entry->refcnt,
		  __entry->primary_key4, __entry->primary_key6,
		  __entry->confirmed, __entry->updated, __entry->used,
		  __prपूर्णांक_hex_str(__entry->new_lladdr, __entry->lladdr_len),
		  neigh_state_str(__entry->new_state),
		  __entry->update_flags, __entry->pid)
);

DECLARE_EVENT_CLASS(neigh__update,
	TP_PROTO(काष्ठा neighbour *n, पूर्णांक err),
	TP_ARGS(n, err),
	TP_STRUCT__entry(
		__field(u32, family)
		__string(dev, (n->dev ? n->dev->name : "NULL"))
		__array(u8, lladdr, MAX_ADDR_LEN)
		__field(u8, lladdr_len)
		__field(u8, flags)
		__field(u8, nud_state)
		__field(u8, type)
		__field(u8, dead)
		__field(पूर्णांक, refcnt)
		__array(__u8, primary_key4, 4)
		__array(__u8, primary_key6, 16)
		__field(अचिन्हित दीर्घ, confirmed)
		__field(अचिन्हित दीर्घ, updated)
		__field(अचिन्हित दीर्घ, used)
		__field(u32, err)
	),

	TP_fast_assign(
		पूर्णांक lladdr_len = (n->dev ? n->dev->addr_len : MAX_ADDR_LEN);
		काष्ठा in6_addr *pin6;
		__be32 *p32;

		__entry->family = n->tbl->family;
		__assign_str(dev, (n->dev ? n->dev->name : "NULL"));
		__entry->lladdr_len = lladdr_len;
		स_नकल(__entry->lladdr, n->ha, lladdr_len);
		__entry->flags = n->flags;
		__entry->nud_state = n->nud_state;
		__entry->type = n->type;
		__entry->dead = n->dead;
		__entry->refcnt = refcount_पढ़ो(&n->refcnt);
		pin6 = (काष्ठा in6_addr *)__entry->primary_key6;
		p32 = (__be32 *)__entry->primary_key4;

		अगर (n->tbl->family == AF_INET)
			*p32 = *(__be32 *)n->primary_key;
		अन्यथा
			*p32 = 0;

#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (n->tbl->family == AF_INET6) अणु
			pin6 = (काष्ठा in6_addr *)__entry->primary_key6;
			*pin6 = *(काष्ठा in6_addr *)n->primary_key;
		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			ipv6_addr_set_v4mapped(*p32, pin6);
		पूर्ण

		__entry->confirmed = n->confirmed;
		__entry->updated = n->updated;
		__entry->used = n->used;
		__entry->err = err;
	),

	TP_prपूर्णांकk("family %d dev %s lladdr %s flags %02x nud_state %s type %02x "
		  "dead %d refcnt %d primary_key4 %pI4 primary_key6 %pI6c "
		  "confirmed %lu updated %lu used %lu err %d",
		  __entry->family, __get_str(dev),
		  __prपूर्णांक_hex_str(__entry->lladdr, __entry->lladdr_len),
		  __entry->flags, neigh_state_str(__entry->nud_state),
		  __entry->type, __entry->dead, __entry->refcnt,
		  __entry->primary_key4, __entry->primary_key6,
		  __entry->confirmed, __entry->updated, __entry->used,
		  __entry->err)
);

DEFINE_EVENT(neigh__update, neigh_update_करोne,
	TP_PROTO(काष्ठा neighbour *neigh, पूर्णांक err),
	TP_ARGS(neigh, err)
);

DEFINE_EVENT(neigh__update, neigh_समयr_handler,
	TP_PROTO(काष्ठा neighbour *neigh, पूर्णांक err),
	TP_ARGS(neigh, err)
);

DEFINE_EVENT(neigh__update, neigh_event_send_करोne,
	TP_PROTO(काष्ठा neighbour *neigh, पूर्णांक err),
	TP_ARGS(neigh, err)
);

DEFINE_EVENT(neigh__update, neigh_event_send_dead,
	TP_PROTO(काष्ठा neighbour *neigh, पूर्णांक err),
	TP_ARGS(neigh, err)
);

DEFINE_EVENT(neigh__update, neigh_cleanup_and_release,
	TP_PROTO(काष्ठा neighbour *neigh, पूर्णांक rc),
	TP_ARGS(neigh, rc)
);

#पूर्ण_अगर /* _TRACE_NEIGH_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
