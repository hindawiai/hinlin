<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * kernel/lockdep_proc.c
 *
 * Runसमय locking correctness validator
 *
 * Started by Ingo Molnar:
 *
 *  Copyright (C) 2006,2007 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *  Copyright (C) 2007 Red Hat, Inc., Peter Zijlstra
 *
 * Code क्रम /proc/lockdep and /proc/lockdep_stats:
 *
 */
#समावेश <linux/export.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/debug_locks.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sort.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/भाग64.h>

#समावेश "lockdep_internals.h"

अटल व्योम *l_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	वापस seq_list_next(v, &all_lock_classes, pos);
पूर्ण

अटल व्योम *l_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	वापस seq_list_start_head(&all_lock_classes, *pos);
पूर्ण

अटल व्योम l_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

अटल व्योम prपूर्णांक_name(काष्ठा seq_file *m, काष्ठा lock_class *class)
अणु
	अक्षर str[KSYM_NAME_LEN];
	स्थिर अक्षर *name = class->name;

	अगर (!name) अणु
		name = __get_key_name(class->key, str);
		seq_म_लिखो(m, "%s", name);
	पूर्ण अन्यथाअणु
		seq_म_लिखो(m, "%s", name);
		अगर (class->name_version > 1)
			seq_म_लिखो(m, "#%d", class->name_version);
		अगर (class->subclass)
			seq_म_लिखो(m, "/%d", class->subclass);
	पूर्ण
पूर्ण

अटल पूर्णांक l_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा lock_class *class = list_entry(v, काष्ठा lock_class, lock_entry);
	काष्ठा lock_list *entry;
	अक्षर usage[LOCK_USAGE_CHARS];

	अगर (v == &all_lock_classes) अणु
		seq_म_लिखो(m, "all lock classes:\n");
		वापस 0;
	पूर्ण

	seq_म_लिखो(m, "%p", class->key);
#अगर_घोषित CONFIG_DEBUG_LOCKDEP
	seq_म_लिखो(m, " OPS:%8ld", debug_class_ops_पढ़ो(class));
#पूर्ण_अगर
#अगर_घोषित CONFIG_PROVE_LOCKING
	seq_म_लिखो(m, " FD:%5ld", lockdep_count_क्रमward_deps(class));
	seq_म_लिखो(m, " BD:%5ld", lockdep_count_backward_deps(class));
#पूर्ण_अगर

	get_usage_अक्षरs(class, usage);
	seq_म_लिखो(m, " %s", usage);

	seq_म_लिखो(m, ": ");
	prपूर्णांक_name(m, class);
	seq_माला_दो(m, "\n");

	list_क्रम_each_entry(entry, &class->locks_after, entry) अणु
		अगर (entry->distance == 1) अणु
			seq_म_लिखो(m, " -> [%p] ", entry->class->key);
			prपूर्णांक_name(m, entry->class);
			seq_माला_दो(m, "\n");
		पूर्ण
	पूर्ण
	seq_माला_दो(m, "\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations lockdep_ops = अणु
	.start	= l_start,
	.next	= l_next,
	.stop	= l_stop,
	.show	= l_show,
पूर्ण;

#अगर_घोषित CONFIG_PROVE_LOCKING
अटल व्योम *lc_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	अगर (*pos < 0)
		वापस शून्य;

	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	वापस lock_chains + (*pos - 1);
पूर्ण

अटल व्योम *lc_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	*pos = lockdep_next_lockchain(*pos - 1) + 1;
	वापस lc_start(m, pos);
पूर्ण

अटल व्योम lc_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक lc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा lock_chain *chain = v;
	काष्ठा lock_class *class;
	पूर्णांक i;
	अटल स्थिर अक्षर * स्थिर irq_strs[] = अणु
		[0]			     = "0",
		[LOCK_CHAIN_HARसूचीQ_CONTEXT] = "hardirq",
		[LOCK_CHAIN_SOFTIRQ_CONTEXT] = "softirq",
		[LOCK_CHAIN_SOFTIRQ_CONTEXT|
		 LOCK_CHAIN_HARसूचीQ_CONTEXT] = "hardirq|softirq",
	पूर्ण;

	अगर (v == SEQ_START_TOKEN) अणु
		अगर (!nr_मुक्त_chain_hlocks)
			seq_म_लिखो(m, "(buggered) ");
		seq_म_लिखो(m, "all lock chains:\n");
		वापस 0;
	पूर्ण

	seq_म_लिखो(m, "irq_context: %s\n", irq_strs[chain->irq_context]);

	क्रम (i = 0; i < chain->depth; i++) अणु
		class = lock_chain_get_class(chain, i);
		अगर (!class->key)
			जारी;

		seq_म_लिखो(m, "[%p] ", class->key);
		prपूर्णांक_name(m, class);
		seq_माला_दो(m, "\n");
	पूर्ण
	seq_माला_दो(m, "\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations lockdep_chains_ops = अणु
	.start	= lc_start,
	.next	= lc_next,
	.stop	= lc_stop,
	.show	= lc_show,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PROVE_LOCKING */

अटल व्योम lockdep_stats_debug_show(काष्ठा seq_file *m)
अणु
#अगर_घोषित CONFIG_DEBUG_LOCKDEP
	अचिन्हित दीर्घ दीर्घ hi1 = debug_atomic_पढ़ो(hardirqs_on_events),
			   hi2 = debug_atomic_पढ़ो(hardirqs_off_events),
			   hr1 = debug_atomic_पढ़ो(redundant_hardirqs_on),
			   hr2 = debug_atomic_पढ़ो(redundant_hardirqs_off),
			   si1 = debug_atomic_पढ़ो(softirqs_on_events),
			   si2 = debug_atomic_पढ़ो(softirqs_off_events),
			   sr1 = debug_atomic_पढ़ो(redundant_softirqs_on),
			   sr2 = debug_atomic_पढ़ो(redundant_softirqs_off);

	seq_म_लिखो(m, " chain lookup misses:           %11llu\n",
		debug_atomic_पढ़ो(chain_lookup_misses));
	seq_म_लिखो(m, " chain lookup hits:             %11llu\n",
		debug_atomic_पढ़ो(chain_lookup_hits));
	seq_म_लिखो(m, " cyclic checks:                 %11llu\n",
		debug_atomic_पढ़ो(nr_cyclic_checks));
	seq_म_लिखो(m, " redundant checks:              %11llu\n",
		debug_atomic_पढ़ो(nr_redundant_checks));
	seq_म_लिखो(m, " redundant links:               %11llu\n",
		debug_atomic_पढ़ो(nr_redundant));
	seq_म_लिखो(m, " find-mask forwards checks:     %11llu\n",
		debug_atomic_पढ़ो(nr_find_usage_क्रमwards_checks));
	seq_म_लिखो(m, " find-mask backwards checks:    %11llu\n",
		debug_atomic_पढ़ो(nr_find_usage_backwards_checks));

	seq_म_लिखो(m, " hardirq on events:             %11llu\n", hi1);
	seq_म_लिखो(m, " hardirq off events:            %11llu\n", hi2);
	seq_म_लिखो(m, " redundant hardirq ons:         %11llu\n", hr1);
	seq_म_लिखो(m, " redundant hardirq offs:        %11llu\n", hr2);
	seq_म_लिखो(m, " softirq on events:             %11llu\n", si1);
	seq_म_लिखो(m, " softirq off events:            %11llu\n", si2);
	seq_म_लिखो(m, " redundant softirq ons:         %11llu\n", sr1);
	seq_म_लिखो(m, " redundant softirq offs:        %11llu\n", sr2);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक lockdep_stats_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित दीर्घ nr_unused = 0, nr_uncategorized = 0,
		      nr_irq_safe = 0, nr_irq_unsafe = 0,
		      nr_softirq_safe = 0, nr_softirq_unsafe = 0,
		      nr_hardirq_safe = 0, nr_hardirq_unsafe = 0,
		      nr_irq_पढ़ो_safe = 0, nr_irq_पढ़ो_unsafe = 0,
		      nr_softirq_पढ़ो_safe = 0, nr_softirq_पढ़ो_unsafe = 0,
		      nr_hardirq_पढ़ो_safe = 0, nr_hardirq_पढ़ो_unsafe = 0,
		      sum_क्रमward_deps = 0;

#अगर_घोषित CONFIG_PROVE_LOCKING
	काष्ठा lock_class *class;

	list_क्रम_each_entry(class, &all_lock_classes, lock_entry) अणु

		अगर (class->usage_mask == 0)
			nr_unused++;
		अगर (class->usage_mask == LOCKF_USED)
			nr_uncategorized++;
		अगर (class->usage_mask & LOCKF_USED_IN_IRQ)
			nr_irq_safe++;
		अगर (class->usage_mask & LOCKF_ENABLED_IRQ)
			nr_irq_unsafe++;
		अगर (class->usage_mask & LOCKF_USED_IN_SOFTIRQ)
			nr_softirq_safe++;
		अगर (class->usage_mask & LOCKF_ENABLED_SOFTIRQ)
			nr_softirq_unsafe++;
		अगर (class->usage_mask & LOCKF_USED_IN_HARसूचीQ)
			nr_hardirq_safe++;
		अगर (class->usage_mask & LOCKF_ENABLED_HARसूचीQ)
			nr_hardirq_unsafe++;
		अगर (class->usage_mask & LOCKF_USED_IN_IRQ_READ)
			nr_irq_पढ़ो_safe++;
		अगर (class->usage_mask & LOCKF_ENABLED_IRQ_READ)
			nr_irq_पढ़ो_unsafe++;
		अगर (class->usage_mask & LOCKF_USED_IN_SOFTIRQ_READ)
			nr_softirq_पढ़ो_safe++;
		अगर (class->usage_mask & LOCKF_ENABLED_SOFTIRQ_READ)
			nr_softirq_पढ़ो_unsafe++;
		अगर (class->usage_mask & LOCKF_USED_IN_HARसूचीQ_READ)
			nr_hardirq_पढ़ो_safe++;
		अगर (class->usage_mask & LOCKF_ENABLED_HARसूचीQ_READ)
			nr_hardirq_पढ़ो_unsafe++;

		sum_क्रमward_deps += lockdep_count_क्रमward_deps(class);
	पूर्ण
#अगर_घोषित CONFIG_DEBUG_LOCKDEP
	DEBUG_LOCKS_WARN_ON(debug_atomic_पढ़ो(nr_unused_locks) != nr_unused);
#पूर्ण_अगर

#पूर्ण_अगर
	seq_म_लिखो(m, " lock-classes:                  %11lu [max: %lu]\n",
			nr_lock_classes, MAX_LOCKDEP_KEYS);
	seq_म_लिखो(m, " direct dependencies:           %11lu [max: %lu]\n",
			nr_list_entries, MAX_LOCKDEP_ENTRIES);
	seq_म_लिखो(m, " indirect dependencies:         %11lu\n",
			sum_क्रमward_deps);

	/*
	 * Total number of dependencies:
	 *
	 * All irq-safe locks may nest inside irq-unsafe locks,
	 * plus all the other known dependencies:
	 */
	seq_म_लिखो(m, " all direct dependencies:       %11lu\n",
			nr_irq_unsafe * nr_irq_safe +
			nr_hardirq_unsafe * nr_hardirq_safe +
			nr_list_entries);

#अगर_घोषित CONFIG_PROVE_LOCKING
	seq_म_लिखो(m, " dependency chains:             %11lu [max: %lu]\n",
			lock_chain_count(), MAX_LOCKDEP_CHAINS);
	seq_म_लिखो(m, " dependency chain hlocks used:  %11lu [max: %lu]\n",
			MAX_LOCKDEP_CHAIN_HLOCKS -
			(nr_मुक्त_chain_hlocks + nr_lost_chain_hlocks),
			MAX_LOCKDEP_CHAIN_HLOCKS);
	seq_म_लिखो(m, " dependency chain hlocks lost:  %11u\n",
			nr_lost_chain_hlocks);
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRACE_IRQFLAGS
	seq_म_लिखो(m, " in-hardirq chains:             %11u\n",
			nr_hardirq_chains);
	seq_म_लिखो(m, " in-softirq chains:             %11u\n",
			nr_softirq_chains);
#पूर्ण_अगर
	seq_म_लिखो(m, " in-process chains:             %11u\n",
			nr_process_chains);
	seq_म_लिखो(m, " stack-trace entries:           %11lu [max: %lu]\n",
			nr_stack_trace_entries, MAX_STACK_TRACE_ENTRIES);
#अगर defined(CONFIG_TRACE_IRQFLAGS) && defined(CONFIG_PROVE_LOCKING)
	seq_म_लिखो(m, " number of stack traces:        %11llu\n",
		   lockdep_stack_trace_count());
	seq_म_लिखो(m, " number of stack hash chains:   %11llu\n",
		   lockdep_stack_hash_count());
#पूर्ण_अगर
	seq_म_लिखो(m, " combined max dependencies:     %11u\n",
			(nr_hardirq_chains + 1) *
			(nr_softirq_chains + 1) *
			(nr_process_chains + 1)
	);
	seq_म_लिखो(m, " hardirq-safe locks:            %11lu\n",
			nr_hardirq_safe);
	seq_म_लिखो(m, " hardirq-unsafe locks:          %11lu\n",
			nr_hardirq_unsafe);
	seq_म_लिखो(m, " softirq-safe locks:            %11lu\n",
			nr_softirq_safe);
	seq_म_लिखो(m, " softirq-unsafe locks:          %11lu\n",
			nr_softirq_unsafe);
	seq_म_लिखो(m, " irq-safe locks:                %11lu\n",
			nr_irq_safe);
	seq_म_लिखो(m, " irq-unsafe locks:              %11lu\n",
			nr_irq_unsafe);

	seq_म_लिखो(m, " hardirq-read-safe locks:       %11lu\n",
			nr_hardirq_पढ़ो_safe);
	seq_म_लिखो(m, " hardirq-read-unsafe locks:     %11lu\n",
			nr_hardirq_पढ़ो_unsafe);
	seq_म_लिखो(m, " softirq-read-safe locks:       %11lu\n",
			nr_softirq_पढ़ो_safe);
	seq_म_लिखो(m, " softirq-read-unsafe locks:     %11lu\n",
			nr_softirq_पढ़ो_unsafe);
	seq_म_लिखो(m, " irq-read-safe locks:           %11lu\n",
			nr_irq_पढ़ो_safe);
	seq_म_लिखो(m, " irq-read-unsafe locks:         %11lu\n",
			nr_irq_पढ़ो_unsafe);

	seq_म_लिखो(m, " uncategorized locks:           %11lu\n",
			nr_uncategorized);
	seq_म_लिखो(m, " unused locks:                  %11lu\n",
			nr_unused);
	seq_म_लिखो(m, " max locking depth:             %11u\n",
			max_lockdep_depth);
#अगर_घोषित CONFIG_PROVE_LOCKING
	seq_म_लिखो(m, " max bfs queue depth:           %11u\n",
			max_bfs_queue_depth);
#पूर्ण_अगर
	lockdep_stats_debug_show(m);
	seq_म_लिखो(m, " debug_locks:                   %11u\n",
			debug_locks);

	/*
	 * Zapped classes and lockdep data buffers reuse statistics.
	 */
	seq_माला_दो(m, "\n");
	seq_म_लिखो(m, " zapped classes:                %11lu\n",
			nr_zapped_classes);
#अगर_घोषित CONFIG_PROVE_LOCKING
	seq_म_लिखो(m, " zapped lock chains:            %11lu\n",
			nr_zapped_lock_chains);
	seq_म_लिखो(m, " large chain blocks:            %11u\n",
			nr_large_chain_blocks);
#पूर्ण_अगर
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_LOCK_STAT

काष्ठा lock_stat_data अणु
	काष्ठा lock_class *class;
	काष्ठा lock_class_stats stats;
पूर्ण;

काष्ठा lock_stat_seq अणु
	काष्ठा lock_stat_data *iter_end;
	काष्ठा lock_stat_data stats[MAX_LOCKDEP_KEYS];
पूर्ण;

/*
 * sort on असलolute number of contentions
 */
अटल पूर्णांक lock_stat_cmp(स्थिर व्योम *l, स्थिर व्योम *r)
अणु
	स्थिर काष्ठा lock_stat_data *dl = l, *dr = r;
	अचिन्हित दीर्घ nl, nr;

	nl = dl->stats.पढ़ो_रुकोसमय.nr + dl->stats.ग_लिखो_रुकोसमय.nr;
	nr = dr->stats.पढ़ो_रुकोसमय.nr + dr->stats.ग_लिखो_रुकोसमय.nr;

	वापस nr - nl;
पूर्ण

अटल व्योम seq_line(काष्ठा seq_file *m, अक्षर c, पूर्णांक offset, पूर्णांक length)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < offset; i++)
		seq_माला_दो(m, " ");
	क्रम (i = 0; i < length; i++)
		seq_म_लिखो(m, "%c", c);
	seq_माला_दो(m, "\n");
पूर्ण

अटल व्योम snprपूर्णांक_समय(अक्षर *buf, माप_प्रकार bufsiz, s64 nr)
अणु
	s64 भाग;
	s32 rem;

	nr += 5; /* क्रम display rounding */
	भाग = भाग_s64_rem(nr, 1000, &rem);
	snम_लिखो(buf, bufsiz, "%lld.%02d", (दीर्घ दीर्घ)भाग, (पूर्णांक)rem/10);
पूर्ण

अटल व्योम seq_समय(काष्ठा seq_file *m, s64 समय)
अणु
	अक्षर num[15];

	snprपूर्णांक_समय(num, माप(num), समय);
	seq_म_लिखो(m, " %14s", num);
पूर्ण

अटल व्योम seq_lock_समय(काष्ठा seq_file *m, काष्ठा lock_समय *lt)
अणु
	seq_म_लिखो(m, "%14lu", lt->nr);
	seq_समय(m, lt->min);
	seq_समय(m, lt->max);
	seq_समय(m, lt->total);
	seq_समय(m, lt->nr ? भाग64_u64(lt->total, lt->nr) : 0);
पूर्ण

अटल व्योम seq_stats(काष्ठा seq_file *m, काष्ठा lock_stat_data *data)
अणु
	स्थिर काष्ठा lockdep_subclass_key *ckey;
	काष्ठा lock_class_stats *stats;
	काष्ठा lock_class *class;
	स्थिर अक्षर *cname;
	पूर्णांक i, namelen;
	अक्षर name[39];

	class = data->class;
	stats = &data->stats;

	namelen = 38;
	अगर (class->name_version > 1)
		namelen -= 2; /* XXX truncates versions > 9 */
	अगर (class->subclass)
		namelen -= 2;

	rcu_पढ़ो_lock_sched();
	cname = rcu_dereference_sched(class->name);
	ckey  = rcu_dereference_sched(class->key);

	अगर (!cname && !ckey) अणु
		rcu_पढ़ो_unlock_sched();
		वापस;

	पूर्ण अन्यथा अगर (!cname) अणु
		अक्षर str[KSYM_NAME_LEN];
		स्थिर अक्षर *key_name;

		key_name = __get_key_name(ckey, str);
		snम_लिखो(name, namelen, "%s", key_name);
	पूर्ण अन्यथा अणु
		snम_लिखो(name, namelen, "%s", cname);
	पूर्ण
	rcu_पढ़ो_unlock_sched();

	namelen = म_माप(name);
	अगर (class->name_version > 1) अणु
		snम_लिखो(name+namelen, 3, "#%d", class->name_version);
		namelen += 2;
	पूर्ण
	अगर (class->subclass) अणु
		snम_लिखो(name+namelen, 3, "/%d", class->subclass);
		namelen += 2;
	पूर्ण

	अगर (stats->ग_लिखो_holdसमय.nr) अणु
		अगर (stats->पढ़ो_holdसमय.nr)
			seq_म_लिखो(m, "%38s-W:", name);
		अन्यथा
			seq_म_लिखो(m, "%40s:", name);

		seq_म_लिखो(m, "%14lu ", stats->bounces[bounce_contended_ग_लिखो]);
		seq_lock_समय(m, &stats->ग_लिखो_रुकोसमय);
		seq_म_लिखो(m, " %14lu ", stats->bounces[bounce_acquired_ग_लिखो]);
		seq_lock_समय(m, &stats->ग_लिखो_holdसमय);
		seq_माला_दो(m, "\n");
	पूर्ण

	अगर (stats->पढ़ो_holdसमय.nr) अणु
		seq_म_लिखो(m, "%38s-R:", name);
		seq_म_लिखो(m, "%14lu ", stats->bounces[bounce_contended_पढ़ो]);
		seq_lock_समय(m, &stats->पढ़ो_रुकोसमय);
		seq_म_लिखो(m, " %14lu ", stats->bounces[bounce_acquired_पढ़ो]);
		seq_lock_समय(m, &stats->पढ़ो_holdसमय);
		seq_माला_दो(m, "\n");
	पूर्ण

	अगर (stats->पढ़ो_रुकोसमय.nr + stats->ग_लिखो_रुकोसमय.nr == 0)
		वापस;

	अगर (stats->पढ़ो_holdसमय.nr)
		namelen += 2;

	क्रम (i = 0; i < LOCKSTAT_POINTS; i++) अणु
		अक्षर ip[32];

		अगर (class->contention_poपूर्णांक[i] == 0)
			अवरोध;

		अगर (!i)
			seq_line(m, '-', 40-namelen, namelen);

		snम_लिखो(ip, माप(ip), "[<%p>]",
				(व्योम *)class->contention_poपूर्णांक[i]);
		seq_म_लिखो(m, "%40s %14lu %29s %pS\n",
			   name, stats->contention_poपूर्णांक[i],
			   ip, (व्योम *)class->contention_poपूर्णांक[i]);
	पूर्ण
	क्रम (i = 0; i < LOCKSTAT_POINTS; i++) अणु
		अक्षर ip[32];

		अगर (class->contending_poपूर्णांक[i] == 0)
			अवरोध;

		अगर (!i)
			seq_line(m, '-', 40-namelen, namelen);

		snम_लिखो(ip, माप(ip), "[<%p>]",
				(व्योम *)class->contending_poपूर्णांक[i]);
		seq_म_लिखो(m, "%40s %14lu %29s %pS\n",
			   name, stats->contending_poपूर्णांक[i],
			   ip, (व्योम *)class->contending_poपूर्णांक[i]);
	पूर्ण
	अगर (i) अणु
		seq_माला_दो(m, "\n");
		seq_line(m, '.', 0, 40 + 1 + 12 * (14 + 1));
		seq_माला_दो(m, "\n");
	पूर्ण
पूर्ण

अटल व्योम seq_header(काष्ठा seq_file *m)
अणु
	seq_माला_दो(m, "lock_stat version 0.4\n");

	अगर (unlikely(!debug_locks))
		seq_म_लिखो(m, "*WARNING* lock debugging disabled!! - possibly due to a lockdep warning\n");

	seq_line(m, '-', 0, 40 + 1 + 12 * (14 + 1));
	seq_म_लिखो(m, "%40s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s "
			"%14s %14s\n",
			"class name",
			"con-bounces",
			"contentions",
			"waittime-min",
			"waittime-max",
			"waittime-total",
			"waittime-avg",
			"acq-bounces",
			"acquisitions",
			"holdtime-min",
			"holdtime-max",
			"holdtime-total",
			"holdtime-avg");
	seq_line(m, '-', 0, 40 + 1 + 12 * (14 + 1));
	seq_म_लिखो(m, "\n");
पूर्ण

अटल व्योम *ls_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा lock_stat_seq *data = m->निजी;
	काष्ठा lock_stat_data *iter;

	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	iter = data->stats + (*pos - 1);
	अगर (iter >= data->iter_end)
		iter = शून्य;

	वापस iter;
पूर्ण

अटल व्योम *ls_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस ls_start(m, pos);
पूर्ण

अटल व्योम ls_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक ls_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN)
		seq_header(m);
	अन्यथा
		seq_stats(m, v);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations lockstat_ops = अणु
	.start	= ls_start,
	.next	= ls_next,
	.stop	= ls_stop,
	.show	= ls_show,
पूर्ण;

अटल पूर्णांक lock_stat_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक res;
	काष्ठा lock_class *class;
	काष्ठा lock_stat_seq *data = vदो_स्मृति(माप(काष्ठा lock_stat_seq));

	अगर (!data)
		वापस -ENOMEM;

	res = seq_खोलो(file, &lockstat_ops);
	अगर (!res) अणु
		काष्ठा lock_stat_data *iter = data->stats;
		काष्ठा seq_file *m = file->निजी_data;

		list_क्रम_each_entry(class, &all_lock_classes, lock_entry) अणु
			iter->class = class;
			iter->stats = lock_stats(class);
			iter++;
		पूर्ण
		data->iter_end = iter;

		sort(data->stats, data->iter_end - data->stats,
				माप(काष्ठा lock_stat_data),
				lock_stat_cmp, शून्य);

		m->निजी = data;
	पूर्ण अन्यथा
		vमुक्त(data);

	वापस res;
पूर्ण

अटल sमाप_प्रकार lock_stat_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा lock_class *class;
	अक्षर c;

	अगर (count) अणु
		अगर (get_user(c, buf))
			वापस -EFAULT;

		अगर (c != '0')
			वापस count;

		list_क्रम_each_entry(class, &all_lock_classes, lock_entry)
			clear_lock_stats(class);
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक lock_stat_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = file->निजी_data;

	vमुक्त(seq->निजी);
	वापस seq_release(inode, file);
पूर्ण

अटल स्थिर काष्ठा proc_ops lock_stat_proc_ops = अणु
	.proc_खोलो	= lock_stat_खोलो,
	.proc_ग_लिखो	= lock_stat_ग_लिखो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= lock_stat_release,
पूर्ण;
#पूर्ण_अगर /* CONFIG_LOCK_STAT */

अटल पूर्णांक __init lockdep_proc_init(व्योम)
अणु
	proc_create_seq("lockdep", S_IRUSR, शून्य, &lockdep_ops);
#अगर_घोषित CONFIG_PROVE_LOCKING
	proc_create_seq("lockdep_chains", S_IRUSR, शून्य, &lockdep_chains_ops);
#पूर्ण_अगर
	proc_create_single("lockdep_stats", S_IRUSR, शून्य, lockdep_stats_show);
#अगर_घोषित CONFIG_LOCK_STAT
	proc_create("lock_stat", S_IRUSR | S_IWUSR, शून्य, &lock_stat_proc_ops);
#पूर्ण_अगर

	वापस 0;
पूर्ण

__initcall(lockdep_proc_init);

