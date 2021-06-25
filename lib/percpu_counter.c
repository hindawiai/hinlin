<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Fast batching percpu counters.
 */

#समावेश <linux/percpu_counter.h>
#समावेश <linux/mutex.h>
#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <linux/module.h>
#समावेश <linux/debugobjects.h>

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल LIST_HEAD(percpu_counters);
अटल DEFINE_SPINLOCK(percpu_counters_lock);
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_OBJECTS_PERCPU_COUNTER

अटल स्थिर काष्ठा debug_obj_descr percpu_counter_debug_descr;

अटल bool percpu_counter_fixup_मुक्त(व्योम *addr, क्रमागत debug_obj_state state)
अणु
	काष्ठा percpu_counter *fbc = addr;

	चयन (state) अणु
	हाल ODEBUG_STATE_ACTIVE:
		percpu_counter_destroy(fbc);
		debug_object_मुक्त(fbc, &percpu_counter_debug_descr);
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा debug_obj_descr percpu_counter_debug_descr = अणु
	.name		= "percpu_counter",
	.fixup_मुक्त	= percpu_counter_fixup_मुक्त,
पूर्ण;

अटल अंतरभूत व्योम debug_percpu_counter_activate(काष्ठा percpu_counter *fbc)
अणु
	debug_object_init(fbc, &percpu_counter_debug_descr);
	debug_object_activate(fbc, &percpu_counter_debug_descr);
पूर्ण

अटल अंतरभूत व्योम debug_percpu_counter_deactivate(काष्ठा percpu_counter *fbc)
अणु
	debug_object_deactivate(fbc, &percpu_counter_debug_descr);
	debug_object_मुक्त(fbc, &percpu_counter_debug_descr);
पूर्ण

#अन्यथा	/* CONFIG_DEBUG_OBJECTS_PERCPU_COUNTER */
अटल अंतरभूत व्योम debug_percpu_counter_activate(काष्ठा percpu_counter *fbc)
अणु पूर्ण
अटल अंतरभूत व्योम debug_percpu_counter_deactivate(काष्ठा percpu_counter *fbc)
अणु पूर्ण
#पूर्ण_अगर	/* CONFIG_DEBUG_OBJECTS_PERCPU_COUNTER */

व्योम percpu_counter_set(काष्ठा percpu_counter *fbc, s64 amount)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&fbc->lock, flags);
	क्रम_each_possible_cpu(cpu) अणु
		s32 *pcount = per_cpu_ptr(fbc->counters, cpu);
		*pcount = 0;
	पूर्ण
	fbc->count = amount;
	raw_spin_unlock_irqrestore(&fbc->lock, flags);
पूर्ण
EXPORT_SYMBOL(percpu_counter_set);

/*
 * This function is both preempt and irq safe. The क्रमmer is due to explicit
 * preemption disable. The latter is guaranteed by the fact that the slow path
 * is explicitly रक्षित by an irq-safe spinlock whereas the fast patch uses
 * this_cpu_add which is irq-safe by definition. Hence there is no need muck
 * with irq state beक्रमe calling this one
 */
व्योम percpu_counter_add_batch(काष्ठा percpu_counter *fbc, s64 amount, s32 batch)
अणु
	s64 count;

	preempt_disable();
	count = __this_cpu_पढ़ो(*fbc->counters) + amount;
	अगर (असल(count) >= batch) अणु
		अचिन्हित दीर्घ flags;
		raw_spin_lock_irqsave(&fbc->lock, flags);
		fbc->count += count;
		__this_cpu_sub(*fbc->counters, count - amount);
		raw_spin_unlock_irqrestore(&fbc->lock, flags);
	पूर्ण अन्यथा अणु
		this_cpu_add(*fbc->counters, amount);
	पूर्ण
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(percpu_counter_add_batch);

/*
 * For percpu_counter with a big batch, the devication of its count could
 * be big, and there is requirement to reduce the deviation, like when the
 * counter's batch could be runसमय decreased to get a better accuracy,
 * which can be achieved by running this sync function on each CPU.
 */
व्योम percpu_counter_sync(काष्ठा percpu_counter *fbc)
अणु
	अचिन्हित दीर्घ flags;
	s64 count;

	raw_spin_lock_irqsave(&fbc->lock, flags);
	count = __this_cpu_पढ़ो(*fbc->counters);
	fbc->count += count;
	__this_cpu_sub(*fbc->counters, count);
	raw_spin_unlock_irqrestore(&fbc->lock, flags);
पूर्ण
EXPORT_SYMBOL(percpu_counter_sync);

/*
 * Add up all the per-cpu counts, वापस the result.  This is a more accurate
 * but much slower version of percpu_counter_पढ़ो_positive()
 */
s64 __percpu_counter_sum(काष्ठा percpu_counter *fbc)
अणु
	s64 ret;
	पूर्णांक cpu;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&fbc->lock, flags);
	ret = fbc->count;
	क्रम_each_online_cpu(cpu) अणु
		s32 *pcount = per_cpu_ptr(fbc->counters, cpu);
		ret += *pcount;
	पूर्ण
	raw_spin_unlock_irqrestore(&fbc->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__percpu_counter_sum);

पूर्णांक __percpu_counter_init(काष्ठा percpu_counter *fbc, s64 amount, gfp_t gfp,
			  काष्ठा lock_class_key *key)
अणु
	अचिन्हित दीर्घ flags __maybe_unused;

	raw_spin_lock_init(&fbc->lock);
	lockdep_set_class(&fbc->lock, key);
	fbc->count = amount;
	fbc->counters = alloc_percpu_gfp(s32, gfp);
	अगर (!fbc->counters)
		वापस -ENOMEM;

	debug_percpu_counter_activate(fbc);

#अगर_घोषित CONFIG_HOTPLUG_CPU
	INIT_LIST_HEAD(&fbc->list);
	spin_lock_irqsave(&percpu_counters_lock, flags);
	list_add(&fbc->list, &percpu_counters);
	spin_unlock_irqrestore(&percpu_counters_lock, flags);
#पूर्ण_अगर
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__percpu_counter_init);

व्योम percpu_counter_destroy(काष्ठा percpu_counter *fbc)
अणु
	अचिन्हित दीर्घ flags __maybe_unused;

	अगर (!fbc->counters)
		वापस;

	debug_percpu_counter_deactivate(fbc);

#अगर_घोषित CONFIG_HOTPLUG_CPU
	spin_lock_irqsave(&percpu_counters_lock, flags);
	list_del(&fbc->list);
	spin_unlock_irqrestore(&percpu_counters_lock, flags);
#पूर्ण_अगर
	मुक्त_percpu(fbc->counters);
	fbc->counters = शून्य;
पूर्ण
EXPORT_SYMBOL(percpu_counter_destroy);

पूर्णांक percpu_counter_batch __पढ़ो_mostly = 32;
EXPORT_SYMBOL(percpu_counter_batch);

अटल पूर्णांक compute_batch_value(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक nr = num_online_cpus();

	percpu_counter_batch = max(32, nr*2);
	वापस 0;
पूर्ण

अटल पूर्णांक percpu_counter_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_HOTPLUG_CPU
	काष्ठा percpu_counter *fbc;

	compute_batch_value(cpu);

	spin_lock_irq(&percpu_counters_lock);
	list_क्रम_each_entry(fbc, &percpu_counters, list) अणु
		s32 *pcount;

		raw_spin_lock(&fbc->lock);
		pcount = per_cpu_ptr(fbc->counters, cpu);
		fbc->count += *pcount;
		*pcount = 0;
		raw_spin_unlock(&fbc->lock);
	पूर्ण
	spin_unlock_irq(&percpu_counters_lock);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * Compare counter against given value.
 * Return 1 अगर greater, 0 अगर equal and -1 अगर less
 */
पूर्णांक __percpu_counter_compare(काष्ठा percpu_counter *fbc, s64 rhs, s32 batch)
अणु
	s64	count;

	count = percpu_counter_पढ़ो(fbc);
	/* Check to see अगर rough count will be sufficient क्रम comparison */
	अगर (असल(count - rhs) > (batch * num_online_cpus())) अणु
		अगर (count > rhs)
			वापस 1;
		अन्यथा
			वापस -1;
	पूर्ण
	/* Need to use precise count */
	count = percpu_counter_sum(fbc);
	अगर (count > rhs)
		वापस 1;
	अन्यथा अगर (count < rhs)
		वापस -1;
	अन्यथा
		वापस 0;
पूर्ण
EXPORT_SYMBOL(__percpu_counter_compare);

अटल पूर्णांक __init percpu_counter_startup(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "lib/percpu_cnt:online",
				compute_batch_value, शून्य);
	WARN_ON(ret < 0);
	ret = cpuhp_setup_state_nocalls(CPUHP_PERCPU_CNT_DEAD,
					"lib/percpu_cnt:dead", शून्य,
					percpu_counter_cpu_dead);
	WARN_ON(ret < 0);
	वापस 0;
पूर्ण
module_init(percpu_counter_startup);
