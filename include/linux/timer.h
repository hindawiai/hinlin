<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_TIMER_H
#घोषणा _LINUX_TIMER_H

#समावेश <linux/list.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/debugobjects.h>
#समावेश <linux/stringअगरy.h>

काष्ठा समयr_list अणु
	/*
	 * All fields that change during normal runसमय grouped to the
	 * same cacheline
	 */
	काष्ठा hlist_node	entry;
	अचिन्हित दीर्घ		expires;
	व्योम			(*function)(काष्ठा समयr_list *);
	u32			flags;

#अगर_घोषित CONFIG_LOCKDEP
	काष्ठा lockdep_map	lockdep_map;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_LOCKDEP
/*
 * NB: because we have to copy the lockdep_map, setting the lockdep_map key
 * (second argument) here is required, otherwise it could be initialised to
 * the copy of the lockdep_map later! We use the poपूर्णांकer to and the string
 * "<file>:<line>" as the key resp. the name of the lockdep_map.
 */
#घोषणा __TIMER_LOCKDEP_MAP_INITIALIZER(_kn)				\
	.lockdep_map = STATIC_LOCKDEP_MAP_INIT(_kn, &_kn),
#अन्यथा
#घोषणा __TIMER_LOCKDEP_MAP_INITIALIZER(_kn)
#पूर्ण_अगर

/**
 * @TIMER_DEFERRABLE: A deferrable समयr will work normally when the
 * प्रणाली is busy, but will not cause a CPU to come out of idle just
 * to service it; instead, the समयr will be serviced when the CPU
 * eventually wakes up with a subsequent non-deferrable समयr.
 *
 * @TIMER_IRQSAFE: An irqsafe समयr is executed with IRQ disabled and
 * it's safe to रुको क्रम the completion of the running instance from
 * IRQ handlers, क्रम example, by calling del_समयr_sync().
 *
 * Note: The irq disabled callback execution is a special हाल क्रम
 * workqueue locking issues. It's not meant क्रम executing अक्रमom crap
 * with पूर्णांकerrupts disabled. Abuse is monitored!
 *
 * @TIMER_PINNED: A pinned समयr will not be affected by any समयr
 * placement heuristics (like, NOHZ) and will always expire on the CPU
 * on which the समयr was enqueued.
 *
 * Note: Because enqueuing of समयrs can migrate the समयr from one
 * CPU to another, pinned समयrs are not guaranteed to stay on the
 * initialy selected CPU.  They move to the CPU on which the enqueue
 * function is invoked via mod_समयr() or add_समयr().  If the समयr
 * should be placed on a particular CPU, then add_समयr_on() has to be
 * used.
 */
#घोषणा TIMER_CPUMASK		0x0003FFFF
#घोषणा TIMER_MIGRATING		0x00040000
#घोषणा TIMER_BASEMASK		(TIMER_CPUMASK | TIMER_MIGRATING)
#घोषणा TIMER_DEFERRABLE	0x00080000
#घोषणा TIMER_PINNED		0x00100000
#घोषणा TIMER_IRQSAFE		0x00200000
#घोषणा TIMER_INIT_FLAGS	(TIMER_DEFERRABLE | TIMER_PINNED | TIMER_IRQSAFE)
#घोषणा TIMER_ARRAYSHIFT	22
#घोषणा TIMER_ARRAYMASK		0xFFC00000

#घोषणा TIMER_TRACE_FLAGMASK	(TIMER_MIGRATING | TIMER_DEFERRABLE | TIMER_PINNED | TIMER_IRQSAFE)

#घोषणा __TIMER_INITIALIZER(_function, _flags) अणु		\
		.entry = अणु .next = TIMER_ENTRY_STATIC पूर्ण,	\
		.function = (_function),			\
		.flags = (_flags),				\
		__TIMER_LOCKDEP_MAP_INITIALIZER(		\
			__खाता__ ":" __stringअगरy(__LINE__))	\
	पूर्ण

#घोषणा DEFINE_TIMER(_name, _function)				\
	काष्ठा समयr_list _name =				\
		__TIMER_INITIALIZER(_function, 0)

/*
 * LOCKDEP and DEBUG समयr पूर्णांकerfaces.
 */
व्योम init_समयr_key(काष्ठा समयr_list *समयr,
		    व्योम (*func)(काष्ठा समयr_list *), अचिन्हित पूर्णांक flags,
		    स्थिर अक्षर *name, काष्ठा lock_class_key *key);

#अगर_घोषित CONFIG_DEBUG_OBJECTS_TIMERS
बाह्य व्योम init_समयr_on_stack_key(काष्ठा समयr_list *समयr,
				    व्योम (*func)(काष्ठा समयr_list *),
				    अचिन्हित पूर्णांक flags, स्थिर अक्षर *name,
				    काष्ठा lock_class_key *key);
#अन्यथा
अटल अंतरभूत व्योम init_समयr_on_stack_key(काष्ठा समयr_list *समयr,
					   व्योम (*func)(काष्ठा समयr_list *),
					   अचिन्हित पूर्णांक flags,
					   स्थिर अक्षर *name,
					   काष्ठा lock_class_key *key)
अणु
	init_समयr_key(समयr, func, flags, name, key);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_LOCKDEP
#घोषणा __init_समयr(_समयr, _fn, _flags)				\
	करो अणु								\
		अटल काष्ठा lock_class_key __key;			\
		init_समयr_key((_समयr), (_fn), (_flags), #_समयr, &__key);\
	पूर्ण जबतक (0)

#घोषणा __init_समयr_on_stack(_समयr, _fn, _flags)			\
	करो अणु								\
		अटल काष्ठा lock_class_key __key;			\
		init_समयr_on_stack_key((_समयr), (_fn), (_flags),	\
					#_समयr, &__key);		 \
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा __init_समयr(_समयr, _fn, _flags)				\
	init_समयr_key((_समयr), (_fn), (_flags), शून्य, शून्य)
#घोषणा __init_समयr_on_stack(_समयr, _fn, _flags)			\
	init_समयr_on_stack_key((_समयr), (_fn), (_flags), शून्य, शून्य)
#पूर्ण_अगर

/**
 * समयr_setup - prepare a समयr क्रम first use
 * @समयr: the समयr in question
 * @callback: the function to call when समयr expires
 * @flags: any TIMER_* flags
 *
 * Regular समयr initialization should use either DEFINE_TIMER() above,
 * or समयr_setup(). For समयrs on the stack, समयr_setup_on_stack() must
 * be used and must be balanced with a call to destroy_समयr_on_stack().
 */
#घोषणा समयr_setup(समयr, callback, flags)			\
	__init_समयr((समयr), (callback), (flags))

#घोषणा समयr_setup_on_stack(समयr, callback, flags)		\
	__init_समयr_on_stack((समयr), (callback), (flags))

#अगर_घोषित CONFIG_DEBUG_OBJECTS_TIMERS
बाह्य व्योम destroy_समयr_on_stack(काष्ठा समयr_list *समयr);
#अन्यथा
अटल अंतरभूत व्योम destroy_समयr_on_stack(काष्ठा समयr_list *समयr) अणु पूर्ण
#पूर्ण_अगर

#घोषणा from_समयr(var, callback_समयr, समयr_fieldname) \
	container_of(callback_समयr, typeof(*var), समयr_fieldname)

/**
 * समयr_pending - is a समयr pending?
 * @समयr: the समयr in question
 *
 * समयr_pending will tell whether a given समयr is currently pending,
 * or not. Callers must ensure serialization wrt. other operations करोne
 * to this समयr, eg. पूर्णांकerrupt contexts, or other CPUs on SMP.
 *
 * वापस value: 1 अगर the समयr is pending, 0 अगर not.
 */
अटल अंतरभूत पूर्णांक समयr_pending(स्थिर काष्ठा समयr_list * समयr)
अणु
	वापस !hlist_unhashed_lockless(&समयr->entry);
पूर्ण

बाह्य व्योम add_समयr_on(काष्ठा समयr_list *समयr, पूर्णांक cpu);
बाह्य पूर्णांक del_समयr(काष्ठा समयr_list * समयr);
बाह्य पूर्णांक mod_समयr(काष्ठा समयr_list *समयr, अचिन्हित दीर्घ expires);
बाह्य पूर्णांक mod_समयr_pending(काष्ठा समयr_list *समयr, अचिन्हित दीर्घ expires);
बाह्य पूर्णांक समयr_reduce(काष्ठा समयr_list *समयr, अचिन्हित दीर्घ expires);

/*
 * The jअगरfies value which is added to now, when there is no समयr
 * in the समयr wheel:
 */
#घोषणा NEXT_TIMER_MAX_DELTA	((1UL << 30) - 1)

बाह्य व्योम add_समयr(काष्ठा समयr_list *समयr);

बाह्य पूर्णांक try_to_del_समयr_sync(काष्ठा समयr_list *समयr);

#अगर defined(CONFIG_SMP) || defined(CONFIG_PREEMPT_RT)
  बाह्य पूर्णांक del_समयr_sync(काष्ठा समयr_list *समयr);
#अन्यथा
# define del_समयr_sync(t)		del_समयr(t)
#पूर्ण_अगर

#घोषणा del_singleshot_समयr_sync(t) del_समयr_sync(t)

बाह्य bool समयr_curr_running(काष्ठा समयr_list *समयr);

बाह्य व्योम init_समयrs(व्योम);
काष्ठा hrसमयr;
बाह्य क्रमागत hrसमयr_restart it_real_fn(काष्ठा hrसमयr *);

#अगर defined(CONFIG_SMP) && defined(CONFIG_NO_HZ_COMMON)
काष्ठा ctl_table;

बाह्य अचिन्हित पूर्णांक sysctl_समयr_migration;
पूर्णांक समयr_migration_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			    व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
#पूर्ण_अगर

अचिन्हित दीर्घ __round_jअगरfies(अचिन्हित दीर्घ j, पूर्णांक cpu);
अचिन्हित दीर्घ __round_jअगरfies_relative(अचिन्हित दीर्घ j, पूर्णांक cpu);
अचिन्हित दीर्घ round_jअगरfies(अचिन्हित दीर्घ j);
अचिन्हित दीर्घ round_jअगरfies_relative(अचिन्हित दीर्घ j);

अचिन्हित दीर्घ __round_jअगरfies_up(अचिन्हित दीर्घ j, पूर्णांक cpu);
अचिन्हित दीर्घ __round_jअगरfies_up_relative(अचिन्हित दीर्घ j, पूर्णांक cpu);
अचिन्हित दीर्घ round_jअगरfies_up(अचिन्हित दीर्घ j);
अचिन्हित दीर्घ round_jअगरfies_up_relative(अचिन्हित दीर्घ j);

#अगर_घोषित CONFIG_HOTPLUG_CPU
पूर्णांक समयrs_prepare_cpu(अचिन्हित पूर्णांक cpu);
पूर्णांक समयrs_dead_cpu(अचिन्हित पूर्णांक cpu);
#अन्यथा
#घोषणा समयrs_prepare_cpu	शून्य
#घोषणा समयrs_dead_cpu		शून्य
#पूर्ण_अगर

#पूर्ण_अगर
