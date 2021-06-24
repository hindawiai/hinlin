<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * prपूर्णांकk_safe.c - Safe prपूर्णांकk क्रम prपूर्णांकk-deadlock-prone contexts
 */

#समावेश <linux/preempt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/debug_locks.h>
#समावेश <linux/kdb.h>
#समावेश <linux/smp.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/kprobes.h>

#समावेश "internal.h"

/*
 * In NMI and safe mode, prपूर्णांकk() aव्योमs taking locks. Instead,
 * it uses an alternative implementation that temporary stores
 * the strings पूर्णांकo a per-CPU buffer. The content of the buffer
 * is later flushed पूर्णांकo the मुख्य ring buffer via IRQ work.
 *
 * The alternative implementation is chosen transparently
 * by examining current prपूर्णांकk() context mask stored in @prपूर्णांकk_context
 * per-CPU variable.
 *
 * The implementation allows to flush the strings also from another CPU.
 * There are situations when we want to make sure that all buffers
 * were handled or when IRQs are blocked.
 */

#घोषणा SAFE_LOG_BUF_LEN ((1 << CONFIG_PRINTK_SAFE_LOG_BUF_SHIFT) -	\
				माप(atomic_t) -			\
				माप(atomic_t) -			\
				माप(काष्ठा irq_work))

काष्ठा prपूर्णांकk_safe_seq_buf अणु
	atomic_t		len;	/* length of written data */
	atomic_t		message_lost;
	काष्ठा irq_work		work;	/* IRQ work that flushes the buffer */
	अचिन्हित अक्षर		buffer[SAFE_LOG_BUF_LEN];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा prपूर्णांकk_safe_seq_buf, safe_prपूर्णांक_seq);
अटल DEFINE_PER_CPU(पूर्णांक, prपूर्णांकk_context);

अटल DEFINE_RAW_SPINLOCK(safe_पढ़ो_lock);

#अगर_घोषित CONFIG_PRINTK_NMI
अटल DEFINE_PER_CPU(काष्ठा prपूर्णांकk_safe_seq_buf, nmi_prपूर्णांक_seq);
#पूर्ण_अगर

/* Get flushed in a more safe context. */
अटल व्योम queue_flush_work(काष्ठा prपूर्णांकk_safe_seq_buf *s)
अणु
	अगर (prपूर्णांकk_percpu_data_पढ़ोy())
		irq_work_queue(&s->work);
पूर्ण

/*
 * Add a message to per-CPU context-dependent buffer. NMI and prपूर्णांकk-safe
 * have dedicated buffers, because otherwise prपूर्णांकk-safe preempted by
 * NMI-prपूर्णांकk would have overwritten the NMI messages.
 *
 * The messages are flushed from irq work (or from panic()), possibly,
 * from other CPU, concurrently with prपूर्णांकk_safe_log_store(). Should this
 * happen, prपूर्णांकk_safe_log_store() will notice the buffer->len mismatch
 * and repeat the ग_लिखो.
 */
अटल __म_लिखो(2, 0) पूर्णांक prपूर्णांकk_safe_log_store(काष्ठा prपूर्णांकk_safe_seq_buf *s,
						स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	पूर्णांक add;
	माप_प्रकार len;
	बहु_सूची ap;

again:
	len = atomic_पढ़ो(&s->len);

	/* The trailing '\0' is not counted पूर्णांकo len. */
	अगर (len >= माप(s->buffer) - 1) अणु
		atomic_inc(&s->message_lost);
		queue_flush_work(s);
		वापस 0;
	पूर्ण

	/*
	 * Make sure that all old data have been पढ़ो beक्रमe the buffer
	 * was reset. This is not needed when we just append data.
	 */
	अगर (!len)
		smp_rmb();

	va_copy(ap, args);
	add = vscnम_लिखो(s->buffer + len, माप(s->buffer) - len, fmt, ap);
	बहु_पूर्ण(ap);
	अगर (!add)
		वापस 0;

	/*
	 * Do it once again अगर the buffer has been flushed in the meanसमय.
	 * Note that atomic_cmpxchg() is an implicit memory barrier that
	 * makes sure that the data were written beक्रमe updating s->len.
	 */
	अगर (atomic_cmpxchg(&s->len, len, len + add) != len)
		जाओ again;

	queue_flush_work(s);
	वापस add;
पूर्ण

अटल अंतरभूत व्योम prपूर्णांकk_safe_flush_line(स्थिर अक्षर *text, पूर्णांक len)
अणु
	/*
	 * Aव्योम any console drivers calls from here, because we may be
	 * in NMI or prपूर्णांकk_safe context (when in panic). The messages
	 * must go only पूर्णांकo the ring buffer at this stage.  Consoles will
	 * get explicitly called later when a crashdump is not generated.
	 */
	prपूर्णांकk_deferred("%.*s", len, text);
पूर्ण

/* prपूर्णांकk part of the temporary buffer line by line */
अटल पूर्णांक prपूर्णांकk_safe_flush_buffer(स्थिर अक्षर *start, माप_प्रकार len)
अणु
	स्थिर अक्षर *c, *end;
	bool header;

	c = start;
	end = start + len;
	header = true;

	/* Prपूर्णांक line by line. */
	जबतक (c < end) अणु
		अगर (*c == '\n') अणु
			prपूर्णांकk_safe_flush_line(start, c - start + 1);
			start = ++c;
			header = true;
			जारी;
		पूर्ण

		/* Handle continuous lines or missing new line. */
		अगर ((c + 1 < end) && prपूर्णांकk_get_level(c)) अणु
			अगर (header) अणु
				c = prपूर्णांकk_skip_level(c);
				जारी;
			पूर्ण

			prपूर्णांकk_safe_flush_line(start, c - start);
			start = c++;
			header = true;
			जारी;
		पूर्ण

		header = false;
		c++;
	पूर्ण

	/* Check अगर there was a partial line. Ignore pure header. */
	अगर (start < end && !header) अणु
		अटल स्थिर अक्षर newline[] = KERN_CONT "\n";

		prपूर्णांकk_safe_flush_line(start, end - start);
		prपूर्णांकk_safe_flush_line(newline, म_माप(newline));
	पूर्ण

	वापस len;
पूर्ण

अटल व्योम report_message_lost(काष्ठा prपूर्णांकk_safe_seq_buf *s)
अणु
	पूर्णांक lost = atomic_xchg(&s->message_lost, 0);

	अगर (lost)
		prपूर्णांकk_deferred("Lost %d message(s)!\n", lost);
पूर्ण

/*
 * Flush data from the associated per-CPU buffer. The function
 * can be called either via IRQ work or independently.
 */
अटल व्योम __prपूर्णांकk_safe_flush(काष्ठा irq_work *work)
अणु
	काष्ठा prपूर्णांकk_safe_seq_buf *s =
		container_of(work, काष्ठा prपूर्णांकk_safe_seq_buf, work);
	अचिन्हित दीर्घ flags;
	माप_प्रकार len;
	पूर्णांक i;

	/*
	 * The lock has two functions. First, one पढ़ोer has to flush all
	 * available message to make the lockless synchronization with
	 * ग_लिखोrs easier. Second, we करो not want to mix messages from
	 * dअगरferent CPUs. This is especially important when prपूर्णांकing
	 * a backtrace.
	 */
	raw_spin_lock_irqsave(&safe_पढ़ो_lock, flags);

	i = 0;
more:
	len = atomic_पढ़ो(&s->len);

	/*
	 * This is just a paranoid check that nobody has manipulated
	 * the buffer an unexpected way. If we prपूर्णांकed something then
	 * @len must only increase. Also it should never overflow the
	 * buffer size.
	 */
	अगर ((i && i >= len) || len > माप(s->buffer)) अणु
		स्थिर अक्षर *msg = "printk_safe_flush: internal error\n";

		prपूर्णांकk_safe_flush_line(msg, म_माप(msg));
		len = 0;
	पूर्ण

	अगर (!len)
		जाओ out; /* Someone अन्यथा has alपढ़ोy flushed the buffer. */

	/* Make sure that data has been written up to the @len */
	smp_rmb();
	i += prपूर्णांकk_safe_flush_buffer(s->buffer + i, len - i);

	/*
	 * Check that nothing has got added in the meanसमय and truncate
	 * the buffer. Note that atomic_cmpxchg() is an implicit memory
	 * barrier that makes sure that the data were copied beक्रमe
	 * updating s->len.
	 */
	अगर (atomic_cmpxchg(&s->len, len, 0) != len)
		जाओ more;

out:
	report_message_lost(s);
	raw_spin_unlock_irqrestore(&safe_पढ़ो_lock, flags);
पूर्ण

/**
 * prपूर्णांकk_safe_flush - flush all per-cpu nmi buffers.
 *
 * The buffers are flushed स्वतःmatically via IRQ work. This function
 * is useful only when someone wants to be sure that all buffers have
 * been flushed at some poपूर्णांक.
 */
व्योम prपूर्णांकk_safe_flush(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
#अगर_घोषित CONFIG_PRINTK_NMI
		__prपूर्णांकk_safe_flush(&per_cpu(nmi_prपूर्णांक_seq, cpu).work);
#पूर्ण_अगर
		__prपूर्णांकk_safe_flush(&per_cpu(safe_prपूर्णांक_seq, cpu).work);
	पूर्ण
पूर्ण

/**
 * prपूर्णांकk_safe_flush_on_panic - flush all per-cpu nmi buffers when the प्रणाली
 *	goes करोwn.
 *
 * Similar to prपूर्णांकk_safe_flush() but it can be called even in NMI context when
 * the प्रणाली goes करोwn. It करोes the best efक्रमt to get NMI messages पूर्णांकo
 * the मुख्य ring buffer.
 *
 * Note that it could try harder when there is only one CPU online.
 */
व्योम prपूर्णांकk_safe_flush_on_panic(व्योम)
अणु
	/*
	 * Make sure that we could access the safe buffers.
	 * Do not risk a द्विगुन release when more CPUs are up.
	 */
	अगर (raw_spin_is_locked(&safe_पढ़ो_lock)) अणु
		अगर (num_online_cpus() > 1)
			वापस;

		debug_locks_off();
		raw_spin_lock_init(&safe_पढ़ो_lock);
	पूर्ण

	prपूर्णांकk_safe_flush();
पूर्ण

#अगर_घोषित CONFIG_PRINTK_NMI
/*
 * Safe prपूर्णांकk() क्रम NMI context. It uses a per-CPU buffer to
 * store the message. NMIs are not nested, so there is always only
 * one ग_लिखोr running. But the buffer might get flushed from another
 * CPU, so we need to be careful.
 */
अटल __म_लिखो(1, 0) पूर्णांक vprपूर्णांकk_nmi(स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	काष्ठा prपूर्णांकk_safe_seq_buf *s = this_cpu_ptr(&nmi_prपूर्णांक_seq);

	वापस prपूर्णांकk_safe_log_store(s, fmt, args);
पूर्ण

व्योम noinstr prपूर्णांकk_nmi_enter(व्योम)
अणु
	this_cpu_add(prपूर्णांकk_context, PRINTK_NMI_CONTEXT_OFFSET);
पूर्ण

व्योम noinstr prपूर्णांकk_nmi_निकास(व्योम)
अणु
	this_cpu_sub(prपूर्णांकk_context, PRINTK_NMI_CONTEXT_OFFSET);
पूर्ण

/*
 * Marks a code that might produce many messages in NMI context
 * and the risk of losing them is more critical than eventual
 * reordering.
 *
 * It has effect only when called in NMI context. Then prपूर्णांकk()
 * will store the messages पूर्णांकo the मुख्य logbuf directly.
 */
व्योम prपूर्णांकk_nmi_direct_enter(व्योम)
अणु
	अगर (this_cpu_पढ़ो(prपूर्णांकk_context) & PRINTK_NMI_CONTEXT_MASK)
		this_cpu_or(prपूर्णांकk_context, PRINTK_NMI_सूचीECT_CONTEXT_MASK);
पूर्ण

व्योम prपूर्णांकk_nmi_direct_निकास(व्योम)
अणु
	this_cpu_and(prपूर्णांकk_context, ~PRINTK_NMI_सूचीECT_CONTEXT_MASK);
पूर्ण

#अन्यथा

अटल __म_लिखो(1, 0) पूर्णांक vprपूर्णांकk_nmi(स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PRINTK_NMI */

/*
 * Lock-less prपूर्णांकk(), to aव्योम deadlocks should the prपूर्णांकk() recurse
 * पूर्णांकo itself. It uses a per-CPU buffer to store the message, just like
 * NMI.
 */
अटल __म_लिखो(1, 0) पूर्णांक vprपूर्णांकk_safe(स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	काष्ठा prपूर्णांकk_safe_seq_buf *s = this_cpu_ptr(&safe_prपूर्णांक_seq);

	वापस prपूर्णांकk_safe_log_store(s, fmt, args);
पूर्ण

/* Can be preempted by NMI. */
व्योम __prपूर्णांकk_safe_enter(व्योम)
अणु
	this_cpu_inc(prपूर्णांकk_context);
पूर्ण

/* Can be preempted by NMI. */
व्योम __prपूर्णांकk_safe_निकास(व्योम)
अणु
	this_cpu_dec(prपूर्णांकk_context);
पूर्ण

यंत्रlinkage पूर्णांक vprपूर्णांकk(स्थिर अक्षर *fmt, बहु_सूची args)
अणु
#अगर_घोषित CONFIG_KGDB_KDB
	/* Allow to pass prपूर्णांकk() to kdb but aव्योम a recursion. */
	अगर (unlikely(kdb_trap_prपूर्णांकk && kdb_म_लिखो_cpu < 0))
		वापस vkdb_म_लिखो(KDB_MSGSRC_PRINTK, fmt, args);
#पूर्ण_अगर

	/*
	 * Use the मुख्य logbuf even in NMI. But aव्योम calling console
	 * drivers that might have their own locks.
	 */
	अगर ((this_cpu_पढ़ो(prपूर्णांकk_context) & PRINTK_NMI_सूचीECT_CONTEXT_MASK)) अणु
		अचिन्हित दीर्घ flags;
		पूर्णांक len;

		prपूर्णांकk_safe_enter_irqsave(flags);
		len = vprपूर्णांकk_store(0, LOGLEVEL_DEFAULT, शून्य, fmt, args);
		prपूर्णांकk_safe_निकास_irqrestore(flags);
		defer_console_output();
		वापस len;
	पूर्ण

	/* Use extra buffer in NMI. */
	अगर (this_cpu_पढ़ो(prपूर्णांकk_context) & PRINTK_NMI_CONTEXT_MASK)
		वापस vprपूर्णांकk_nmi(fmt, args);

	/* Use extra buffer to prevent a recursion deadlock in safe mode. */
	अगर (this_cpu_पढ़ो(prपूर्णांकk_context) & PRINTK_SAFE_CONTEXT_MASK)
		वापस vprपूर्णांकk_safe(fmt, args);

	/* No obstacles. */
	वापस vprपूर्णांकk_शेष(fmt, args);
पूर्ण
EXPORT_SYMBOL(vprपूर्णांकk);

व्योम __init prपूर्णांकk_safe_init(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा prपूर्णांकk_safe_seq_buf *s;

		s = &per_cpu(safe_prपूर्णांक_seq, cpu);
		init_irq_work(&s->work, __prपूर्णांकk_safe_flush);

#अगर_घोषित CONFIG_PRINTK_NMI
		s = &per_cpu(nmi_prपूर्णांक_seq, cpu);
		init_irq_work(&s->work, __prपूर्णांकk_safe_flush);
#पूर्ण_अगर
	पूर्ण

	/* Flush pending messages that did not have scheduled IRQ works. */
	prपूर्णांकk_safe_flush();
पूर्ण
