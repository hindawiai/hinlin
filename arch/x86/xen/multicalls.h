<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _XEN_MULTICALLS_H
#घोषणा _XEN_MULTICALLS_H

#समावेश <trace/events/xen.h>

#समावेश "xen-ops.h"

/* Multicalls */
काष्ठा multicall_space
अणु
	काष्ठा multicall_entry *mc;
	व्योम *args;
पूर्ण;

/* Allocate room क्रम a multicall and its args */
काष्ठा multicall_space __xen_mc_entry(माप_प्रकार args);

DECLARE_PER_CPU(अचिन्हित दीर्घ, xen_mc_irq_flags);

/* Call to start a batch of multiple __xen_mc_entry()s.  Must be
   paired with xen_mc_issue() */
अटल अंतरभूत व्योम xen_mc_batch(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	/* need to disable पूर्णांकerrupts until this entry is complete */
	local_irq_save(flags);
	trace_xen_mc_batch(paravirt_get_lazy_mode());
	__this_cpu_ग_लिखो(xen_mc_irq_flags, flags);
पूर्ण

अटल अंतरभूत काष्ठा multicall_space xen_mc_entry(माप_प्रकार args)
अणु
	xen_mc_batch();
	वापस __xen_mc_entry(args);
पूर्ण

/* Flush all pending multicalls */
व्योम xen_mc_flush(व्योम);

/* Issue a multicall अगर we're not in a lazy mode */
अटल अंतरभूत व्योम xen_mc_issue(अचिन्हित mode)
अणु
	trace_xen_mc_issue(mode);

	अगर ((paravirt_get_lazy_mode() & mode) == 0)
		xen_mc_flush();

	/* restore flags saved in xen_mc_batch */
	local_irq_restore(this_cpu_पढ़ो(xen_mc_irq_flags));
पूर्ण

/* Set up a callback to be called when the current batch is flushed */
व्योम xen_mc_callback(व्योम (*fn)(व्योम *), व्योम *data);

/*
 * Try to extend the arguments of the previous multicall command.  The
 * previous command's op must match.  If it करोes, then it attempts to
 * extend the argument space allocated to the multicall entry by
 * arg_size bytes.
 *
 * The वापसed multicall_space will वापस with mc poपूर्णांकing to the
 * command on success, or शून्य on failure, and args poपूर्णांकing to the
 * newly allocated space.
 */
काष्ठा multicall_space xen_mc_extend_args(अचिन्हित दीर्घ op, माप_प्रकार arg_size);

#पूर्ण_अगर /* _XEN_MULTICALLS_H */
