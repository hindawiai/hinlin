<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_TRACE_RECURSION_H
#घोषणा _LINUX_TRACE_RECURSION_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>

#अगर_घोषित CONFIG_TRACING

/* Only current can touch trace_recursion */

/*
 * For function tracing recursion:
 *  The order of these bits are important.
 *
 *  When function tracing occurs, the following steps are made:
 *   If arch करोes not support a ftrace feature:
 *    call पूर्णांकernal function (uses INTERNAL bits) which calls...
 *   If callback is रेजिस्टरed to the "global" list, the list
 *    function is called and recursion checks the GLOBAL bits.
 *    then this function calls...
 *   The function callback, which can use the FTRACE bits to
 *    check क्रम recursion.
 *
 * Now अगर the arch करोes not support a feature, and it calls
 * the global list function which calls the ftrace callback
 * all three of these steps will करो a recursion protection.
 * There's no reason to करो one अगर the previous caller alपढ़ोy
 * did. The recursion that we are protecting against will
 * go through the same steps again.
 *
 * To prevent the multiple recursion checks, अगर a recursion
 * bit is set that is higher than the MAX bit of the current
 * check, then we know that the check was made by the previous
 * caller, and we can skip the current check.
 */
क्रमागत अणु
	/* Function recursion bits */
	TRACE_FTRACE_BIT,
	TRACE_FTRACE_NMI_BIT,
	TRACE_FTRACE_IRQ_BIT,
	TRACE_FTRACE_SIRQ_BIT,

	/* INTERNAL_BITs must be greater than FTRACE_BITs */
	TRACE_INTERNAL_BIT,
	TRACE_INTERNAL_NMI_BIT,
	TRACE_INTERNAL_IRQ_BIT,
	TRACE_INTERNAL_SIRQ_BIT,

	TRACE_BRANCH_BIT,
/*
 * Abuse of the trace_recursion.
 * As we need a way to मुख्यtain state अगर we are tracing the function
 * graph in irq because we want to trace a particular function that
 * was called in irq context but we have irq tracing off. Since this
 * can only be modअगरied by current, we can reuse trace_recursion.
 */
	TRACE_IRQ_BIT,

	/* Set अगर the function is in the set_graph_function file */
	TRACE_GRAPH_BIT,

	/*
	 * In the very unlikely हाल that an पूर्णांकerrupt came in
	 * at a start of graph tracing, and we want to trace
	 * the function in that पूर्णांकerrupt, the depth can be greater
	 * than zero, because of the preempted start of a previous
	 * trace. In an even more unlikely हाल, depth could be 2
	 * अगर a softirq पूर्णांकerrupted the start of graph tracing,
	 * followed by an पूर्णांकerrupt preempting a start of graph
	 * tracing in the softirq, and depth can even be 3
	 * अगर an NMI came in at the start of an पूर्णांकerrupt function
	 * that preempted a softirq start of a function that
	 * preempted normal context!!!! Luckily, it can't be
	 * greater than 3, so the next two bits are a mask
	 * of what the depth is when we set TRACE_GRAPH_BIT
	 */

	TRACE_GRAPH_DEPTH_START_BIT,
	TRACE_GRAPH_DEPTH_END_BIT,

	/*
	 * To implement set_graph_notrace, अगर this bit is set, we ignore
	 * function graph tracing of called functions, until the वापस
	 * function is called to clear it.
	 */
	TRACE_GRAPH_NOTRACE_BIT,

	/*
	 * When transitioning between context, the preempt_count() may
	 * not be correct. Allow क्रम a single recursion to cover this हाल.
	 */
	TRACE_TRANSITION_BIT,

	/* Used to prevent recursion recording from recursing. */
	TRACE_RECORD_RECURSION_BIT,
पूर्ण;

#घोषणा trace_recursion_set(bit)	करो अणु (current)->trace_recursion |= (1<<(bit)); पूर्ण जबतक (0)
#घोषणा trace_recursion_clear(bit)	करो अणु (current)->trace_recursion &= ~(1<<(bit)); पूर्ण जबतक (0)
#घोषणा trace_recursion_test(bit)	((current)->trace_recursion & (1<<(bit)))

#घोषणा trace_recursion_depth() \
	(((current)->trace_recursion >> TRACE_GRAPH_DEPTH_START_BIT) & 3)
#घोषणा trace_recursion_set_depth(depth) \
	करो अणु								\
		current->trace_recursion &=				\
			~(3 << TRACE_GRAPH_DEPTH_START_BIT);		\
		current->trace_recursion |=				\
			((depth) & 3) << TRACE_GRAPH_DEPTH_START_BIT;	\
	पूर्ण जबतक (0)

#घोषणा TRACE_CONTEXT_BITS	4

#घोषणा TRACE_FTRACE_START	TRACE_FTRACE_BIT
#घोषणा TRACE_FTRACE_MAX	((1 << (TRACE_FTRACE_START + TRACE_CONTEXT_BITS)) - 1)

#घोषणा TRACE_LIST_START	TRACE_INTERNAL_BIT
#घोषणा TRACE_LIST_MAX		((1 << (TRACE_LIST_START + TRACE_CONTEXT_BITS)) - 1)

#घोषणा TRACE_CONTEXT_MASK	TRACE_LIST_MAX

/*
 * Used क्रम setting context
 *  NMI     = 0
 *  IRQ     = 1
 *  SOFTIRQ = 2
 *  NORMAL  = 3
 */
क्रमागत अणु
	TRACE_CTX_NMI,
	TRACE_CTX_IRQ,
	TRACE_CTX_SOFTIRQ,
	TRACE_CTX_NORMAL,
पूर्ण;

अटल __always_अंतरभूत पूर्णांक trace_get_context_bit(व्योम)
अणु
	अचिन्हित दीर्घ pc = preempt_count();

	अगर (!(pc & (NMI_MASK | HARसूचीQ_MASK | SOFTIRQ_OFFSET)))
		वापस TRACE_CTX_NORMAL;
	अन्यथा
		वापस pc & NMI_MASK ? TRACE_CTX_NMI :
			pc & HARसूचीQ_MASK ? TRACE_CTX_IRQ : TRACE_CTX_SOFTIRQ;
पूर्ण

#अगर_घोषित CONFIG_FTRACE_RECORD_RECURSION
बाह्य व्योम ftrace_record_recursion(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip);
# define करो_ftrace_record_recursion(ip, pip)				\
	करो अणु								\
		अगर (!trace_recursion_test(TRACE_RECORD_RECURSION_BIT)) अणु \
			trace_recursion_set(TRACE_RECORD_RECURSION_BIT); \
			ftrace_record_recursion(ip, pip);		\
			trace_recursion_clear(TRACE_RECORD_RECURSION_BIT); \
		पूर्ण							\
	पूर्ण जबतक (0)
#अन्यथा
# define करो_ftrace_record_recursion(ip, pip)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल __always_अंतरभूत पूर्णांक trace_test_and_set_recursion(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ pip,
							पूर्णांक start, पूर्णांक max)
अणु
	अचिन्हित पूर्णांक val = READ_ONCE(current->trace_recursion);
	पूर्णांक bit;

	/* A previous recursion check was made */
	अगर ((val & TRACE_CONTEXT_MASK) > max)
		वापस 0;

	bit = trace_get_context_bit() + start;
	अगर (unlikely(val & (1 << bit))) अणु
		/*
		 * It could be that preempt_count has not been updated during
		 * a चयन between contexts. Allow क्रम a single recursion.
		 */
		bit = TRACE_TRANSITION_BIT;
		अगर (val & (1 << bit)) अणु
			करो_ftrace_record_recursion(ip, pip);
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Normal check passed, clear the transition to allow it again */
		val &= ~(1 << TRACE_TRANSITION_BIT);
	पूर्ण

	val |= 1 << bit;
	current->trace_recursion = val;
	barrier();

	वापस bit + 1;
पूर्ण

अटल __always_अंतरभूत व्योम trace_clear_recursion(पूर्णांक bit)
अणु
	अगर (!bit)
		वापस;

	barrier();
	bit--;
	trace_recursion_clear(bit);
पूर्ण

/**
 * ftrace_test_recursion_trylock - tests क्रम recursion in same context
 *
 * Use this क्रम ftrace callbacks. This will detect अगर the function
 * tracing recursed in the same context (normal vs पूर्णांकerrupt),
 *
 * Returns: -1 अगर a recursion happened.
 *           >= 0 अगर no recursion
 */
अटल __always_अंतरभूत पूर्णांक ftrace_test_recursion_trylock(अचिन्हित दीर्घ ip,
							 अचिन्हित दीर्घ parent_ip)
अणु
	वापस trace_test_and_set_recursion(ip, parent_ip, TRACE_FTRACE_START, TRACE_FTRACE_MAX);
पूर्ण

/**
 * ftrace_test_recursion_unlock - called when function callback is complete
 * @bit: The वापस of a successful ftrace_test_recursion_trylock()
 *
 * This is used at the end of a ftrace callback.
 */
अटल __always_अंतरभूत व्योम ftrace_test_recursion_unlock(पूर्णांक bit)
अणु
	trace_clear_recursion(bit);
पूर्ण

#पूर्ण_अगर /* CONFIG_TRACING */
#पूर्ण_अगर /* _LINUX_TRACE_RECURSION_H */
