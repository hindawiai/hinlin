<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/linux/irqflags.h
 *
 * IRQ flags tracing: follow the state of the hardirq and softirq flags and
 * provide callbacks क्रम transitions between ON and OFF states.
 *
 * This file माला_लो included from lowlevel यंत्र headers too, to provide
 * wrapped versions of the local_irq_*() APIs, based on the
 * raw_local_irq_*() macros from the lowlevel headers.
 */
#अगर_अघोषित _LINUX_TRACE_IRQFLAGS_H
#घोषणा _LINUX_TRACE_IRQFLAGS_H

#समावेश <linux/typecheck.h>
#समावेश <यंत्र/irqflags.h>
#समावेश <यंत्र/percpu.h>

/* Currently lockdep_softirqs_on/off is used only by lockdep */
#अगर_घोषित CONFIG_PROVE_LOCKING
  बाह्य व्योम lockdep_softirqs_on(अचिन्हित दीर्घ ip);
  बाह्य व्योम lockdep_softirqs_off(अचिन्हित दीर्घ ip);
  बाह्य व्योम lockdep_hardirqs_on_prepare(अचिन्हित दीर्घ ip);
  बाह्य व्योम lockdep_hardirqs_on(अचिन्हित दीर्घ ip);
  बाह्य व्योम lockdep_hardirqs_off(अचिन्हित दीर्घ ip);
#अन्यथा
  अटल अंतरभूत व्योम lockdep_softirqs_on(अचिन्हित दीर्घ ip) अणु पूर्ण
  अटल अंतरभूत व्योम lockdep_softirqs_off(अचिन्हित दीर्घ ip) अणु पूर्ण
  अटल अंतरभूत व्योम lockdep_hardirqs_on_prepare(अचिन्हित दीर्घ ip) अणु पूर्ण
  अटल अंतरभूत व्योम lockdep_hardirqs_on(अचिन्हित दीर्घ ip) अणु पूर्ण
  अटल अंतरभूत व्योम lockdep_hardirqs_off(अचिन्हित दीर्घ ip) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRACE_IRQFLAGS

/* Per-task IRQ trace events inक्रमmation. */
काष्ठा irqtrace_events अणु
	अचिन्हित पूर्णांक	irq_events;
	अचिन्हित दीर्घ	hardirq_enable_ip;
	अचिन्हित दीर्घ	hardirq_disable_ip;
	अचिन्हित पूर्णांक	hardirq_enable_event;
	अचिन्हित पूर्णांक	hardirq_disable_event;
	अचिन्हित दीर्घ	softirq_disable_ip;
	अचिन्हित दीर्घ	softirq_enable_ip;
	अचिन्हित पूर्णांक	softirq_disable_event;
	अचिन्हित पूर्णांक	softirq_enable_event;
पूर्ण;

DECLARE_PER_CPU(पूर्णांक, hardirqs_enabled);
DECLARE_PER_CPU(पूर्णांक, hardirq_context);

बाह्य व्योम trace_hardirqs_on_prepare(व्योम);
बाह्य व्योम trace_hardirqs_off_finish(व्योम);
बाह्य व्योम trace_hardirqs_on(व्योम);
बाह्य व्योम trace_hardirqs_off(व्योम);

# define lockdep_hardirq_context()	(raw_cpu_पढ़ो(hardirq_context))
# define lockdep_softirq_context(p)	((p)->softirq_context)
# define lockdep_hardirqs_enabled()	(this_cpu_पढ़ो(hardirqs_enabled))
# define lockdep_softirqs_enabled(p)	((p)->softirqs_enabled)
# define lockdep_hardirq_enter()			\
करो अणु							\
	अगर (__this_cpu_inc_वापस(hardirq_context) == 1)\
		current->hardirq_thपढ़ोed = 0;		\
पूर्ण जबतक (0)
# define lockdep_hardirq_thपढ़ोed()		\
करो अणु						\
	current->hardirq_thपढ़ोed = 1;		\
पूर्ण जबतक (0)
# define lockdep_hardirq_निकास()			\
करो अणु						\
	__this_cpu_dec(hardirq_context);	\
पूर्ण जबतक (0)
# define lockdep_softirq_enter()		\
करो अणु						\
	current->softirq_context++;		\
पूर्ण जबतक (0)
# define lockdep_softirq_निकास()			\
करो अणु						\
	current->softirq_context--;		\
पूर्ण जबतक (0)

# define lockdep_hrसमयr_enter(__hrसमयr)		\
(अणु							\
	bool __expires_hardirq = true;			\
							\
	अगर (!__hrसमयr->is_hard) अणु			\
		current->irq_config = 1;		\
		__expires_hardirq = false;		\
	पूर्ण						\
	__expires_hardirq;				\
पूर्ण)

# define lockdep_hrसमयr_निकास(__expires_hardirq)	\
	करो अणु						\
		अगर (!__expires_hardirq)			\
			current->irq_config = 0;	\
	पूर्ण जबतक (0)

# define lockdep_posixसमयr_enter()				\
	  करो अणु							\
		  current->irq_config = 1;			\
	  पूर्ण जबतक (0)

# define lockdep_posixसमयr_निकास()				\
	  करो अणु							\
		  current->irq_config = 0;			\
	  पूर्ण जबतक (0)

# define lockdep_irq_work_enter(_flags)					\
	  करो अणु								\
		  अगर (!((_flags) & IRQ_WORK_HARD_IRQ))			\
			current->irq_config = 1;			\
	  पूर्ण जबतक (0)
# define lockdep_irq_work_निकास(_flags)					\
	  करो अणु								\
		  अगर (!((_flags) & IRQ_WORK_HARD_IRQ))			\
			current->irq_config = 0;			\
	  पूर्ण जबतक (0)

#अन्यथा
# define trace_hardirqs_on_prepare()		करो अणु पूर्ण जबतक (0)
# define trace_hardirqs_off_finish()		करो अणु पूर्ण जबतक (0)
# define trace_hardirqs_on()			करो अणु पूर्ण जबतक (0)
# define trace_hardirqs_off()			करो अणु पूर्ण जबतक (0)
# define lockdep_hardirq_context()		0
# define lockdep_softirq_context(p)		0
# define lockdep_hardirqs_enabled()		0
# define lockdep_softirqs_enabled(p)		0
# define lockdep_hardirq_enter()		करो अणु पूर्ण जबतक (0)
# define lockdep_hardirq_thपढ़ोed()		करो अणु पूर्ण जबतक (0)
# define lockdep_hardirq_निकास()			करो अणु पूर्ण जबतक (0)
# define lockdep_softirq_enter()		करो अणु पूर्ण जबतक (0)
# define lockdep_softirq_निकास()			करो अणु पूर्ण जबतक (0)
# define lockdep_hrसमयr_enter(__hrसमयr)	false
# define lockdep_hrसमयr_निकास(__context)	करो अणु पूर्ण जबतक (0)
# define lockdep_posixसमयr_enter()		करो अणु पूर्ण जबतक (0)
# define lockdep_posixसमयr_निकास()		करो अणु पूर्ण जबतक (0)
# define lockdep_irq_work_enter(__work)		करो अणु पूर्ण जबतक (0)
# define lockdep_irq_work_निकास(__work)		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर defined(CONFIG_IRQSOFF_TRACER) || \
	defined(CONFIG_PREEMPT_TRACER)
 बाह्य व्योम stop_critical_timings(व्योम);
 बाह्य व्योम start_critical_timings(व्योम);
#अन्यथा
# define stop_critical_timings() करो अणु पूर्ण जबतक (0)
# define start_critical_timings() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_IRQFLAGS
बाह्य व्योम warn_bogus_irq_restore(व्योम);
#घोषणा raw_check_bogus_irq_restore()			\
	करो अणु						\
		अगर (unlikely(!arch_irqs_disabled()))	\
			warn_bogus_irq_restore();	\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा raw_check_bogus_irq_restore() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * Wrap the arch provided IRQ routines to provide appropriate checks.
 */
#घोषणा raw_local_irq_disable()		arch_local_irq_disable()
#घोषणा raw_local_irq_enable()		arch_local_irq_enable()
#घोषणा raw_local_irq_save(flags)			\
	करो अणु						\
		typecheck(अचिन्हित दीर्घ, flags);	\
		flags = arch_local_irq_save();		\
	पूर्ण जबतक (0)
#घोषणा raw_local_irq_restore(flags)			\
	करो अणु						\
		typecheck(अचिन्हित दीर्घ, flags);	\
		raw_check_bogus_irq_restore();		\
		arch_local_irq_restore(flags);		\
	पूर्ण जबतक (0)
#घोषणा raw_local_save_flags(flags)			\
	करो अणु						\
		typecheck(अचिन्हित दीर्घ, flags);	\
		flags = arch_local_save_flags();	\
	पूर्ण जबतक (0)
#घोषणा raw_irqs_disabled_flags(flags)			\
	(अणु						\
		typecheck(अचिन्हित दीर्घ, flags);	\
		arch_irqs_disabled_flags(flags);	\
	पूर्ण)
#घोषणा raw_irqs_disabled()		(arch_irqs_disabled())
#घोषणा raw_safe_halt()			arch_safe_halt()

/*
 * The local_irq_*() APIs are equal to the raw_local_irq*()
 * अगर !TRACE_IRQFLAGS.
 */
#अगर_घोषित CONFIG_TRACE_IRQFLAGS

#घोषणा local_irq_enable()				\
	करो अणु						\
		trace_hardirqs_on();			\
		raw_local_irq_enable();			\
	पूर्ण जबतक (0)

#घोषणा local_irq_disable()				\
	करो अणु						\
		bool was_disabled = raw_irqs_disabled();\
		raw_local_irq_disable();		\
		अगर (!was_disabled)			\
			trace_hardirqs_off();		\
	पूर्ण जबतक (0)

#घोषणा local_irq_save(flags)				\
	करो अणु						\
		raw_local_irq_save(flags);		\
		अगर (!raw_irqs_disabled_flags(flags))	\
			trace_hardirqs_off();		\
	पूर्ण जबतक (0)

#घोषणा local_irq_restore(flags)			\
	करो अणु						\
		अगर (!raw_irqs_disabled_flags(flags))	\
			trace_hardirqs_on();		\
		raw_local_irq_restore(flags);		\
	पूर्ण जबतक (0)

#घोषणा safe_halt()				\
	करो अणु					\
		trace_hardirqs_on();		\
		raw_safe_halt();		\
	पूर्ण जबतक (0)


#अन्यथा /* !CONFIG_TRACE_IRQFLAGS */

#घोषणा local_irq_enable()	करो अणु raw_local_irq_enable(); पूर्ण जबतक (0)
#घोषणा local_irq_disable()	करो अणु raw_local_irq_disable(); पूर्ण जबतक (0)
#घोषणा local_irq_save(flags)	करो अणु raw_local_irq_save(flags); पूर्ण जबतक (0)
#घोषणा local_irq_restore(flags) करो अणु raw_local_irq_restore(flags); पूर्ण जबतक (0)
#घोषणा safe_halt()		करो अणु raw_safe_halt(); पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_TRACE_IRQFLAGS */

#घोषणा local_save_flags(flags)	raw_local_save_flags(flags)

/*
 * Some architectures करोn't define arch_irqs_disabled(), so even अगर either
 * definition would be fine we need to use dअगरferent ones क्रम the समय being
 * to aव्योम build issues.
 */
#अगर_घोषित CONFIG_TRACE_IRQFLAGS_SUPPORT
#घोषणा irqs_disabled()					\
	(अणु						\
		अचिन्हित दीर्घ _flags;			\
		raw_local_save_flags(_flags);		\
		raw_irqs_disabled_flags(_flags);	\
	पूर्ण)
#अन्यथा /* !CONFIG_TRACE_IRQFLAGS_SUPPORT */
#घोषणा irqs_disabled()	raw_irqs_disabled()
#पूर्ण_अगर /* CONFIG_TRACE_IRQFLAGS_SUPPORT */

#घोषणा irqs_disabled_flags(flags) raw_irqs_disabled_flags(flags)

#पूर्ण_अगर
