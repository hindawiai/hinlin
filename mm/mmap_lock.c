<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/mmap_lock.h>

#समावेश <linux/mm.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/mmap_lock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/percpu.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/smp.h>
#समावेश <linux/trace_events.h>

EXPORT_TRACEPOINT_SYMBOL(mmap_lock_start_locking);
EXPORT_TRACEPOINT_SYMBOL(mmap_lock_acquire_वापसed);
EXPORT_TRACEPOINT_SYMBOL(mmap_lock_released);

#अगर_घोषित CONFIG_MEMCG

/*
 * Our various events all share the same buffer (because we करोn't want or need
 * to allocate a set of buffers *per event type*), so we need to protect against
 * concurrent _reg() and _unreg() calls, and count how many _reg() calls have
 * been made.
 */
अटल DEFINE_MUTEX(reg_lock);
अटल पूर्णांक reg_refcount; /* Protected by reg_lock. */

/*
 * Size of the buffer क्रम memcg path names. Ignoring stack trace support,
 * trace_events_hist.c uses MAX_FILTER_STR_VAL क्रम this, so we also use it.
 */
#घोषणा MEMCG_PATH_BUF_SIZE MAX_FILTER_STR_VAL

/*
 * How many contexts our trace events might be called in: normal, softirq, irq,
 * and NMI.
 */
#घोषणा CONTEXT_COUNT 4

अटल DEFINE_PER_CPU(अक्षर __rcu *, memcg_path_buf);
अटल अक्षर **पंचांगp_bufs;
अटल DEFINE_PER_CPU(पूर्णांक, memcg_path_buf_idx);

/* Called with reg_lock held. */
अटल व्योम मुक्त_memcg_path_bufs(व्योम)
अणु
	पूर्णांक cpu;
	अक्षर **old = पंचांगp_bufs;

	क्रम_each_possible_cpu(cpu) अणु
		*(old++) = rcu_dereference_रक्षित(
			per_cpu(memcg_path_buf, cpu),
			lockdep_is_held(&reg_lock));
		rcu_assign_poपूर्णांकer(per_cpu(memcg_path_buf, cpu), शून्य);
	पूर्ण

	/* Wait क्रम inflight memcg_path_buf users to finish. */
	synchronize_rcu();

	old = पंचांगp_bufs;
	क्रम_each_possible_cpu(cpu) अणु
		kमुक्त(*(old++));
	पूर्ण

	kमुक्त(पंचांगp_bufs);
	पंचांगp_bufs = शून्य;
पूर्ण

पूर्णांक trace_mmap_lock_reg(व्योम)
अणु
	पूर्णांक cpu;
	अक्षर *new;

	mutex_lock(&reg_lock);

	/* If the refcount is going 0->1, proceed with allocating buffers. */
	अगर (reg_refcount++)
		जाओ out;

	पंचांगp_bufs = kदो_स्मृति_array(num_possible_cpus(), माप(*पंचांगp_bufs),
				 GFP_KERNEL);
	अगर (पंचांगp_bufs == शून्य)
		जाओ out_fail;

	क्रम_each_possible_cpu(cpu) अणु
		new = kदो_स्मृति(MEMCG_PATH_BUF_SIZE * CONTEXT_COUNT, GFP_KERNEL);
		अगर (new == शून्य)
			जाओ out_fail_मुक्त;
		rcu_assign_poपूर्णांकer(per_cpu(memcg_path_buf, cpu), new);
		/* Don't need to wait for inflights, they'd have gotten शून्य. */
	पूर्ण

out:
	mutex_unlock(&reg_lock);
	वापस 0;

out_fail_मुक्त:
	मुक्त_memcg_path_bufs();
out_fail:
	/* Since we failed, unकरो the earlier ref increment. */
	--reg_refcount;

	mutex_unlock(&reg_lock);
	वापस -ENOMEM;
पूर्ण

व्योम trace_mmap_lock_unreg(व्योम)
अणु
	mutex_lock(&reg_lock);

	/* If the refcount is going 1->0, proceed with मुक्तing buffers. */
	अगर (--reg_refcount)
		जाओ out;

	मुक्त_memcg_path_bufs();

out:
	mutex_unlock(&reg_lock);
पूर्ण

अटल अंतरभूत अक्षर *get_memcg_path_buf(व्योम)
अणु
	अक्षर *buf;
	पूर्णांक idx;

	rcu_पढ़ो_lock();
	buf = rcu_dereference(*this_cpu_ptr(&memcg_path_buf));
	अगर (buf == शून्य) अणु
		rcu_पढ़ो_unlock();
		वापस शून्य;
	पूर्ण
	idx = this_cpu_add_वापस(memcg_path_buf_idx, MEMCG_PATH_BUF_SIZE) -
	      MEMCG_PATH_BUF_SIZE;
	वापस &buf[idx];
पूर्ण

अटल अंतरभूत व्योम put_memcg_path_buf(व्योम)
अणु
	this_cpu_sub(memcg_path_buf_idx, MEMCG_PATH_BUF_SIZE);
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Write the given mm_काष्ठा's memcg path to a percpu buffer, and वापस a
 * poपूर्णांकer to it. If the path cannot be determined, or no buffer was available
 * (because the trace event is being unरेजिस्टरed), शून्य is वापसed.
 *
 * Note: buffers are allocated per-cpu to aव्योम locking, so preemption must be
 * disabled by the caller beक्रमe calling us, and re-enabled only after the
 * caller is करोne with the poपूर्णांकer.
 *
 * The caller must call put_memcg_path_buf() once the buffer is no दीर्घer
 * needed. This must be करोne जबतक preemption is still disabled.
 */
अटल स्थिर अक्षर *get_mm_memcg_path(काष्ठा mm_काष्ठा *mm)
अणु
	अक्षर *buf = शून्य;
	काष्ठा mem_cgroup *memcg = get_mem_cgroup_from_mm(mm);

	अगर (memcg == शून्य)
		जाओ out;
	अगर (unlikely(memcg->css.cgroup == शून्य))
		जाओ out_put;

	buf = get_memcg_path_buf();
	अगर (buf == शून्य)
		जाओ out_put;

	cgroup_path(memcg->css.cgroup, buf, MEMCG_PATH_BUF_SIZE);

out_put:
	css_put(&memcg->css);
out:
	वापस buf;
पूर्ण

#घोषणा TRACE_MMAP_LOCK_EVENT(type, mm, ...)                                   \
	करो अणु                                                                   \
		स्थिर अक्षर *memcg_path;                                        \
		preempt_disable();                                             \
		memcg_path = get_mm_memcg_path(mm);                            \
		trace_mmap_lock_##type(mm,                                     \
				       memcg_path != शून्य ? memcg_path : "",   \
				       ##__VA_ARGS__);                         \
		अगर (likely(memcg_path != शून्य))                                \
			put_memcg_path_buf();                                  \
		preempt_enable();                                              \
	पूर्ण जबतक (0)

#अन्यथा /* !CONFIG_MEMCG */

पूर्णांक trace_mmap_lock_reg(व्योम)
अणु
	वापस 0;
पूर्ण

व्योम trace_mmap_lock_unreg(व्योम)
अणु
पूर्ण

#घोषणा TRACE_MMAP_LOCK_EVENT(type, mm, ...)                                   \
	trace_mmap_lock_##type(mm, "", ##__VA_ARGS__)

#पूर्ण_अगर /* CONFIG_MEMCG */

/*
 * Trace calls must be in a separate file, as otherwise there's a circular
 * dependency between linux/mmap_lock.h and trace/events/mmap_lock.h.
 */

व्योम __mmap_lock_करो_trace_start_locking(काष्ठा mm_काष्ठा *mm, bool ग_लिखो)
अणु
	TRACE_MMAP_LOCK_EVENT(start_locking, mm, ग_लिखो);
पूर्ण
EXPORT_SYMBOL(__mmap_lock_करो_trace_start_locking);

व्योम __mmap_lock_करो_trace_acquire_वापसed(काष्ठा mm_काष्ठा *mm, bool ग_लिखो,
					   bool success)
अणु
	TRACE_MMAP_LOCK_EVENT(acquire_वापसed, mm, ग_लिखो, success);
पूर्ण
EXPORT_SYMBOL(__mmap_lock_करो_trace_acquire_वापसed);

व्योम __mmap_lock_करो_trace_released(काष्ठा mm_काष्ठा *mm, bool ग_लिखो)
अणु
	TRACE_MMAP_LOCK_EVENT(released, mm, ग_लिखो);
पूर्ण
EXPORT_SYMBOL(__mmap_lock_करो_trace_released);
