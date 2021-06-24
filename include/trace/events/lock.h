<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM lock

#अगर !defined(_TRACE_LOCK_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_LOCK_H

#समावेश <linux/lockdep.h>
#समावेश <linux/tracepoपूर्णांक.h>

#अगर_घोषित CONFIG_LOCKDEP

TRACE_EVENT(lock_acquire,

	TP_PROTO(काष्ठा lockdep_map *lock, अचिन्हित पूर्णांक subclass,
		पूर्णांक trylock, पूर्णांक पढ़ो, पूर्णांक check,
		काष्ठा lockdep_map *next_lock, अचिन्हित दीर्घ ip),

	TP_ARGS(lock, subclass, trylock, पढ़ो, check, next_lock, ip),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, flags)
		__string(name, lock->name)
		__field(व्योम *, lockdep_addr)
	),

	TP_fast_assign(
		__entry->flags = (trylock ? 1 : 0) | (पढ़ो ? 2 : 0);
		__assign_str(name, lock->name);
		__entry->lockdep_addr = lock;
	),

	TP_prपूर्णांकk("%p %s%s%s", __entry->lockdep_addr,
		  (__entry->flags & 1) ? "try " : "",
		  (__entry->flags & 2) ? "read " : "",
		  __get_str(name))
);

DECLARE_EVENT_CLASS(lock,

	TP_PROTO(काष्ठा lockdep_map *lock, अचिन्हित दीर्घ ip),

	TP_ARGS(lock, ip),

	TP_STRUCT__entry(
		__string(	name, 	lock->name	)
		__field(	व्योम *, lockdep_addr	)
	),

	TP_fast_assign(
		__assign_str(name, lock->name);
		__entry->lockdep_addr = lock;
	),

	TP_prपूर्णांकk("%p %s",  __entry->lockdep_addr, __get_str(name))
);

DEFINE_EVENT(lock, lock_release,

	TP_PROTO(काष्ठा lockdep_map *lock, अचिन्हित दीर्घ ip),

	TP_ARGS(lock, ip)
);

#अगर_घोषित CONFIG_LOCK_STAT

DEFINE_EVENT(lock, lock_contended,

	TP_PROTO(काष्ठा lockdep_map *lock, अचिन्हित दीर्घ ip),

	TP_ARGS(lock, ip)
);

DEFINE_EVENT(lock, lock_acquired,

	TP_PROTO(काष्ठा lockdep_map *lock, अचिन्हित दीर्घ ip),

	TP_ARGS(lock, ip)
);

#पूर्ण_अगर
#पूर्ण_अगर

#पूर्ण_अगर /* _TRACE_LOCK_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
