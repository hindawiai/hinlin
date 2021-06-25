<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Routines to manage notअगरier chains क्रम passing status changes to any
 *	पूर्णांकerested routines. We need this instead of hard coded call lists so
 *	that modules can poke their nose पूर्णांकo the innards. The network devices
 *	needed them so here they are क्रम the rest of you.
 *
 *				Alan Cox <Alan.Cox@linux.org>
 */
 
#अगर_अघोषित _LINUX_NOTIFIER_H
#घोषणा _LINUX_NOTIFIER_H
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mutex.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/srcu.h>

/*
 * Notअगरier chains are of four types:
 *
 *	Atomic notअगरier chains: Chain callbacks run in पूर्णांकerrupt/atomic
 *		context. Callouts are not allowed to block.
 *	Blocking notअगरier chains: Chain callbacks run in process context.
 *		Callouts are allowed to block.
 *	Raw notअगरier chains: There are no restrictions on callbacks,
 *		registration, or unregistration.  All locking and protection
 *		must be provided by the caller.
 *	SRCU notअगरier chains: A variant of blocking notअगरier chains, with
 *		the same restrictions.
 *
 * atomic_notअगरier_chain_रेजिस्टर() may be called from an atomic context,
 * but blocking_notअगरier_chain_रेजिस्टर() and srcu_notअगरier_chain_रेजिस्टर()
 * must be called from a process context.  Ditto क्रम the corresponding
 * _unरेजिस्टर() routines.
 *
 * atomic_notअगरier_chain_unरेजिस्टर(), blocking_notअगरier_chain_unरेजिस्टर(),
 * and srcu_notअगरier_chain_unरेजिस्टर() _must not_ be called from within
 * the call chain.
 *
 * SRCU notअगरier chains are an alternative क्रमm of blocking notअगरier chains.
 * They use SRCU (Sleepable Read-Copy Update) instead of rw-semaphores क्रम
 * protection of the chain links.  This means there is _very_ low overhead
 * in srcu_notअगरier_call_chain(): no cache bounces and no memory barriers.
 * As compensation, srcu_notअगरier_chain_unरेजिस्टर() is rather expensive.
 * SRCU notअगरier chains should be used when the chain will be called very
 * often but notअगरier_blocks will selकरोm be हटाओd.
 */

काष्ठा notअगरier_block;

प्रकार	पूर्णांक (*notअगरier_fn_t)(काष्ठा notअगरier_block *nb,
			अचिन्हित दीर्घ action, व्योम *data);

काष्ठा notअगरier_block अणु
	notअगरier_fn_t notअगरier_call;
	काष्ठा notअगरier_block __rcu *next;
	पूर्णांक priority;
पूर्ण;

काष्ठा atomic_notअगरier_head अणु
	spinlock_t lock;
	काष्ठा notअगरier_block __rcu *head;
पूर्ण;

काष्ठा blocking_notअगरier_head अणु
	काष्ठा rw_semaphore rwsem;
	काष्ठा notअगरier_block __rcu *head;
पूर्ण;

काष्ठा raw_notअगरier_head अणु
	काष्ठा notअगरier_block __rcu *head;
पूर्ण;

काष्ठा srcu_notअगरier_head अणु
	काष्ठा mutex mutex;
	काष्ठा srcu_काष्ठा srcu;
	काष्ठा notअगरier_block __rcu *head;
पूर्ण;

#घोषणा ATOMIC_INIT_NOTIFIER_HEAD(name) करो अणु	\
		spin_lock_init(&(name)->lock);	\
		(name)->head = शून्य;		\
	पूर्ण जबतक (0)
#घोषणा BLOCKING_INIT_NOTIFIER_HEAD(name) करो अणु	\
		init_rwsem(&(name)->rwsem);	\
		(name)->head = शून्य;		\
	पूर्ण जबतक (0)
#घोषणा RAW_INIT_NOTIFIER_HEAD(name) करो अणु	\
		(name)->head = शून्य;		\
	पूर्ण जबतक (0)

/* srcu_notअगरier_heads must be cleaned up dynamically */
बाह्य व्योम srcu_init_notअगरier_head(काष्ठा srcu_notअगरier_head *nh);
#घोषणा srcu_cleanup_notअगरier_head(name)	\
		cleanup_srcu_काष्ठा(&(name)->srcu);

#घोषणा ATOMIC_NOTIFIER_INIT(name) अणु				\
		.lock = __SPIN_LOCK_UNLOCKED(name.lock),	\
		.head = शून्य पूर्ण
#घोषणा BLOCKING_NOTIFIER_INIT(name) अणु				\
		.rwsem = __RWSEM_INITIALIZER((name).rwsem),	\
		.head = शून्य पूर्ण
#घोषणा RAW_NOTIFIER_INIT(name)	अणु				\
		.head = शून्य पूर्ण

#घोषणा SRCU_NOTIFIER_INIT(name, pcpu)				\
	अणु							\
		.mutex = __MUTEX_INITIALIZER(name.mutex),	\
		.head = शून्य,					\
		.srcu = __SRCU_STRUCT_INIT(name.srcu, pcpu),	\
	पूर्ण

#घोषणा ATOMIC_NOTIFIER_HEAD(name)				\
	काष्ठा atomic_notअगरier_head name =			\
		ATOMIC_NOTIFIER_INIT(name)
#घोषणा BLOCKING_NOTIFIER_HEAD(name)				\
	काष्ठा blocking_notअगरier_head name =			\
		BLOCKING_NOTIFIER_INIT(name)
#घोषणा RAW_NOTIFIER_HEAD(name)					\
	काष्ठा raw_notअगरier_head name =				\
		RAW_NOTIFIER_INIT(name)

#अगर_घोषित CONFIG_TREE_SRCU
#घोषणा _SRCU_NOTIFIER_HEAD(name, mod)				\
	अटल DEFINE_PER_CPU(काष्ठा srcu_data, name##_head_srcu_data); \
	mod काष्ठा srcu_notअगरier_head name =			\
			SRCU_NOTIFIER_INIT(name, name##_head_srcu_data)

#अन्यथा
#घोषणा _SRCU_NOTIFIER_HEAD(name, mod)				\
	mod काष्ठा srcu_notअगरier_head name =			\
			SRCU_NOTIFIER_INIT(name, name)

#पूर्ण_अगर

#घोषणा SRCU_NOTIFIER_HEAD(name)				\
	_SRCU_NOTIFIER_HEAD(name, /* not अटल */)

#घोषणा SRCU_NOTIFIER_HEAD_STATIC(name)				\
	_SRCU_NOTIFIER_HEAD(name, अटल)

#अगर_घोषित __KERNEL__

बाह्य पूर्णांक atomic_notअगरier_chain_रेजिस्टर(काष्ठा atomic_notअगरier_head *nh,
		काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक blocking_notअगरier_chain_रेजिस्टर(काष्ठा blocking_notअगरier_head *nh,
		काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक raw_notअगरier_chain_रेजिस्टर(काष्ठा raw_notअगरier_head *nh,
		काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक srcu_notअगरier_chain_रेजिस्टर(काष्ठा srcu_notअगरier_head *nh,
		काष्ठा notअगरier_block *nb);

बाह्य पूर्णांक atomic_notअगरier_chain_unरेजिस्टर(काष्ठा atomic_notअगरier_head *nh,
		काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक blocking_notअगरier_chain_unरेजिस्टर(काष्ठा blocking_notअगरier_head *nh,
		काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक raw_notअगरier_chain_unरेजिस्टर(काष्ठा raw_notअगरier_head *nh,
		काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक srcu_notअगरier_chain_unरेजिस्टर(काष्ठा srcu_notअगरier_head *nh,
		काष्ठा notअगरier_block *nb);

बाह्य पूर्णांक atomic_notअगरier_call_chain(काष्ठा atomic_notअगरier_head *nh,
		अचिन्हित दीर्घ val, व्योम *v);
बाह्य पूर्णांक blocking_notअगरier_call_chain(काष्ठा blocking_notअगरier_head *nh,
		अचिन्हित दीर्घ val, व्योम *v);
बाह्य पूर्णांक raw_notअगरier_call_chain(काष्ठा raw_notअगरier_head *nh,
		अचिन्हित दीर्घ val, व्योम *v);
बाह्य पूर्णांक srcu_notअगरier_call_chain(काष्ठा srcu_notअगरier_head *nh,
		अचिन्हित दीर्घ val, व्योम *v);

बाह्य पूर्णांक atomic_notअगरier_call_chain_robust(काष्ठा atomic_notअगरier_head *nh,
		अचिन्हित दीर्घ val_up, अचिन्हित दीर्घ val_करोwn, व्योम *v);
बाह्य पूर्णांक blocking_notअगरier_call_chain_robust(काष्ठा blocking_notअगरier_head *nh,
		अचिन्हित दीर्घ val_up, अचिन्हित दीर्घ val_करोwn, व्योम *v);
बाह्य पूर्णांक raw_notअगरier_call_chain_robust(काष्ठा raw_notअगरier_head *nh,
		अचिन्हित दीर्घ val_up, अचिन्हित दीर्घ val_करोwn, व्योम *v);

#घोषणा NOTIFY_DONE		0x0000		/* Don't care */
#घोषणा NOTIFY_OK		0x0001		/* Suits me */
#घोषणा NOTIFY_STOP_MASK	0x8000		/* Don't call further */
#घोषणा NOTIFY_BAD		(NOTIFY_STOP_MASK|0x0002)
						/* Bad/Veto action */
/*
 * Clean way to वापस from the notअगरier and stop further calls.
 */
#घोषणा NOTIFY_STOP		(NOTIFY_OK|NOTIFY_STOP_MASK)

/* Encapsulate (negative) त्रुटि_सं value (in particular, NOTIFY_BAD <=> EPERM). */
अटल अंतरभूत पूर्णांक notअगरier_from_त्रुटि_सं(पूर्णांक err)
अणु
	अगर (err)
		वापस NOTIFY_STOP_MASK | (NOTIFY_OK - err);

	वापस NOTIFY_OK;
पूर्ण

/* Restore (negative) त्रुटि_सं value from notअगरy वापस value. */
अटल अंतरभूत पूर्णांक notअगरier_to_त्रुटि_सं(पूर्णांक ret)
अणु
	ret &= ~NOTIFY_STOP_MASK;
	वापस ret > NOTIFY_OK ? NOTIFY_OK - ret : 0;
पूर्ण

/*
 *	Declared notअगरiers so far. I can imagine quite a few more chains
 *	over समय (eg laptop घातer reset chains, reboot chain (to clean 
 *	device units up), device [un]mount chain, module load/unload chain,
 *	low memory chain, screenblank chain (क्रम plug in modular screenblankers) 
 *	VC चयन chains (क्रम loadable kernel svgalib VC चयन helpers) etc...
 */
 
/* CPU notfiers are defined in include/linux/cpu.h. */

/* netdevice notअगरiers are defined in include/linux/netdevice.h */

/* reboot notअगरiers are defined in include/linux/reboot.h. */

/* Hibernation and suspend events are defined in include/linux/suspend.h. */

/* Virtual Terminal events are defined in include/linux/vt.h. */

#घोषणा NETLINK_URELEASE	0x0001	/* Unicast netlink socket released */

/* Console keyboard events.
 * Note: KBD_KEYCODE is always sent beक्रमe KBD_UNBOUND_KEYCODE, KBD_UNICODE and
 * KBD_KEYSYM. */
#घोषणा KBD_KEYCODE		0x0001 /* Keyboard keycode, called beक्रमe any other */
#घोषणा KBD_UNBOUND_KEYCODE	0x0002 /* Keyboard keycode which is not bound to any other */
#घोषणा KBD_UNICODE		0x0003 /* Keyboard unicode */
#घोषणा KBD_KEYSYM		0x0004 /* Keyboard keysym */
#घोषणा KBD_POST_KEYSYM		0x0005 /* Called after keyboard keysym पूर्णांकerpretation */

बाह्य काष्ठा blocking_notअगरier_head reboot_notअगरier_list;

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _LINUX_NOTIFIER_H */
