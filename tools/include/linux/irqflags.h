<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LIBLOCKDEP_LINUX_TRACE_IRQFLAGS_H_
#घोषणा _LIBLOCKDEP_LINUX_TRACE_IRQFLAGS_H_

# define lockdep_hardirq_context()	0
# define lockdep_softirq_context(p)	0
# define lockdep_hardirqs_enabled()	0
# define lockdep_softirqs_enabled(p)	0
# define lockdep_hardirq_enter()	करो अणु पूर्ण जबतक (0)
# define lockdep_hardirq_निकास()		करो अणु पूर्ण जबतक (0)
# define lockdep_softirq_enter()	करो अणु पूर्ण जबतक (0)
# define lockdep_softirq_निकास()		करो अणु पूर्ण जबतक (0)
# define INIT_TRACE_IRQFLAGS

# define stop_critical_timings() करो अणु पूर्ण जबतक (0)
# define start_critical_timings() करो अणु पूर्ण जबतक (0)

#घोषणा raw_local_irq_disable() करो अणु पूर्ण जबतक (0)
#घोषणा raw_local_irq_enable() करो अणु पूर्ण जबतक (0)
#घोषणा raw_local_irq_save(flags) ((flags) = 0)
#घोषणा raw_local_irq_restore(flags) ((व्योम)(flags))
#घोषणा raw_local_save_flags(flags) ((flags) = 0)
#घोषणा raw_irqs_disabled_flags(flags) ((व्योम)(flags))
#घोषणा raw_irqs_disabled() 0
#घोषणा raw_safe_halt()

#घोषणा local_irq_enable() करो अणु पूर्ण जबतक (0)
#घोषणा local_irq_disable() करो अणु पूर्ण जबतक (0)
#घोषणा local_irq_save(flags) ((flags) = 0)
#घोषणा local_irq_restore(flags) ((व्योम)(flags))
#घोषणा local_save_flags(flags)	((flags) = 0)
#घोषणा irqs_disabled() (1)
#घोषणा irqs_disabled_flags(flags) ((व्योम)(flags), 0)
#घोषणा safe_halt() करो अणु पूर्ण जबतक (0)

#घोषणा trace_lock_release(x, y)
#घोषणा trace_lock_acquire(a, b, c, d, e, f, g)

#पूर्ण_अगर
