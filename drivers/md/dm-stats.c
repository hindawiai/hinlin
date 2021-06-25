<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/numa.h>
#समावेश <linux/slab.h>
#समावेश <linux/rculist.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/preempt.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/device-mapper.h>

#समावेश "dm-core.h"
#समावेश "dm-stats.h"

#घोषणा DM_MSG_PREFIX "stats"

अटल पूर्णांक dm_stat_need_rcu_barrier;

/*
 * Using 64-bit values to aव्योम overflow (which is a
 * problem that block/genhd.c's IO accounting has).
 */
काष्ठा dm_stat_percpu अणु
	अचिन्हित दीर्घ दीर्घ sectors[2];
	अचिन्हित दीर्घ दीर्घ ios[2];
	अचिन्हित दीर्घ दीर्घ merges[2];
	अचिन्हित दीर्घ दीर्घ ticks[2];
	अचिन्हित दीर्घ दीर्घ io_ticks[2];
	अचिन्हित दीर्घ दीर्घ io_ticks_total;
	अचिन्हित दीर्घ दीर्घ समय_in_queue;
	अचिन्हित दीर्घ दीर्घ *histogram;
पूर्ण;

काष्ठा dm_stat_shared अणु
	atomic_t in_flight[2];
	अचिन्हित दीर्घ दीर्घ stamp;
	काष्ठा dm_stat_percpu पंचांगp;
पूर्ण;

काष्ठा dm_stat अणु
	काष्ठा list_head list_entry;
	पूर्णांक id;
	अचिन्हित stat_flags;
	माप_प्रकार n_entries;
	sector_t start;
	sector_t end;
	sector_t step;
	अचिन्हित n_histogram_entries;
	अचिन्हित दीर्घ दीर्घ *histogram_boundaries;
	स्थिर अक्षर *program_id;
	स्थिर अक्षर *aux_data;
	काष्ठा rcu_head rcu_head;
	माप_प्रकार shared_alloc_size;
	माप_प्रकार percpu_alloc_size;
	माप_प्रकार histogram_alloc_size;
	काष्ठा dm_stat_percpu *stat_percpu[NR_CPUS];
	काष्ठा dm_stat_shared stat_shared[];
पूर्ण;

#घोषणा STAT_PRECISE_TIMESTAMPS		1

काष्ठा dm_stats_last_position अणु
	sector_t last_sector;
	अचिन्हित last_rw;
पूर्ण;

/*
 * A typo on the command line could possibly make the kernel run out of memory
 * and crash. To prevent the crash we account all used memory. We fail अगर we
 * exhaust 1/4 of all memory or 1/2 of vदो_स्मृति space.
 */
#घोषणा DM_STATS_MEMORY_FACTOR		4
#घोषणा DM_STATS_VMALLOC_FACTOR		2

अटल DEFINE_SPINLOCK(shared_memory_lock);

अटल अचिन्हित दीर्घ shared_memory_amount;

अटल bool __check_shared_memory(माप_प्रकार alloc_size)
अणु
	माप_प्रकार a;

	a = shared_memory_amount + alloc_size;
	अगर (a < shared_memory_amount)
		वापस false;
	अगर (a >> PAGE_SHIFT > totalram_pages() / DM_STATS_MEMORY_FACTOR)
		वापस false;
#अगर_घोषित CONFIG_MMU
	अगर (a > (VMALLOC_END - VMALLOC_START) / DM_STATS_VMALLOC_FACTOR)
		वापस false;
#पूर्ण_अगर
	वापस true;
पूर्ण

अटल bool check_shared_memory(माप_प्रकार alloc_size)
अणु
	bool ret;

	spin_lock_irq(&shared_memory_lock);

	ret = __check_shared_memory(alloc_size);

	spin_unlock_irq(&shared_memory_lock);

	वापस ret;
पूर्ण

अटल bool claim_shared_memory(माप_प्रकार alloc_size)
अणु
	spin_lock_irq(&shared_memory_lock);

	अगर (!__check_shared_memory(alloc_size)) अणु
		spin_unlock_irq(&shared_memory_lock);
		वापस false;
	पूर्ण

	shared_memory_amount += alloc_size;

	spin_unlock_irq(&shared_memory_lock);

	वापस true;
पूर्ण

अटल व्योम मुक्त_shared_memory(माप_प्रकार alloc_size)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&shared_memory_lock, flags);

	अगर (WARN_ON_ONCE(shared_memory_amount < alloc_size)) अणु
		spin_unlock_irqrestore(&shared_memory_lock, flags);
		DMCRIT("Memory usage accounting bug.");
		वापस;
	पूर्ण

	shared_memory_amount -= alloc_size;

	spin_unlock_irqrestore(&shared_memory_lock, flags);
पूर्ण

अटल व्योम *dm_kvzalloc(माप_प्रकार alloc_size, पूर्णांक node)
अणु
	व्योम *p;

	अगर (!claim_shared_memory(alloc_size))
		वापस शून्य;

	p = kvzalloc_node(alloc_size, GFP_KERNEL | __GFP_NOMEMALLOC, node);
	अगर (p)
		वापस p;

	मुक्त_shared_memory(alloc_size);

	वापस शून्य;
पूर्ण

अटल व्योम dm_kvमुक्त(व्योम *ptr, माप_प्रकार alloc_size)
अणु
	अगर (!ptr)
		वापस;

	मुक्त_shared_memory(alloc_size);

	kvमुक्त(ptr);
पूर्ण

अटल व्योम dm_stat_मुक्त(काष्ठा rcu_head *head)
अणु
	पूर्णांक cpu;
	काष्ठा dm_stat *s = container_of(head, काष्ठा dm_stat, rcu_head);

	kमुक्त(s->histogram_boundaries);
	kमुक्त(s->program_id);
	kमुक्त(s->aux_data);
	क्रम_each_possible_cpu(cpu) अणु
		dm_kvमुक्त(s->stat_percpu[cpu][0].histogram, s->histogram_alloc_size);
		dm_kvमुक्त(s->stat_percpu[cpu], s->percpu_alloc_size);
	पूर्ण
	dm_kvमुक्त(s->stat_shared[0].पंचांगp.histogram, s->histogram_alloc_size);
	dm_kvमुक्त(s, s->shared_alloc_size);
पूर्ण

अटल पूर्णांक dm_stat_in_flight(काष्ठा dm_stat_shared *shared)
अणु
	वापस atomic_पढ़ो(&shared->in_flight[READ]) +
	       atomic_पढ़ो(&shared->in_flight[WRITE]);
पूर्ण

व्योम dm_stats_init(काष्ठा dm_stats *stats)
अणु
	पूर्णांक cpu;
	काष्ठा dm_stats_last_position *last;

	mutex_init(&stats->mutex);
	INIT_LIST_HEAD(&stats->list);
	stats->last = alloc_percpu(काष्ठा dm_stats_last_position);
	क्रम_each_possible_cpu(cpu) अणु
		last = per_cpu_ptr(stats->last, cpu);
		last->last_sector = (sector_t)ULदीर्घ_उच्च;
		last->last_rw = अच_पूर्णांक_उच्च;
	पूर्ण
पूर्ण

व्योम dm_stats_cleanup(काष्ठा dm_stats *stats)
अणु
	माप_प्रकार ni;
	काष्ठा dm_stat *s;
	काष्ठा dm_stat_shared *shared;

	जबतक (!list_empty(&stats->list)) अणु
		s = container_of(stats->list.next, काष्ठा dm_stat, list_entry);
		list_del(&s->list_entry);
		क्रम (ni = 0; ni < s->n_entries; ni++) अणु
			shared = &s->stat_shared[ni];
			अगर (WARN_ON(dm_stat_in_flight(shared))) अणु
				DMCRIT("leaked in-flight counter at index %lu "
				       "(start %llu, end %llu, step %llu): reads %d, writes %d",
				       (अचिन्हित दीर्घ)ni,
				       (अचिन्हित दीर्घ दीर्घ)s->start,
				       (अचिन्हित दीर्घ दीर्घ)s->end,
				       (अचिन्हित दीर्घ दीर्घ)s->step,
				       atomic_पढ़ो(&shared->in_flight[READ]),
				       atomic_पढ़ो(&shared->in_flight[WRITE]));
			पूर्ण
		पूर्ण
		dm_stat_मुक्त(&s->rcu_head);
	पूर्ण
	मुक्त_percpu(stats->last);
	mutex_destroy(&stats->mutex);
पूर्ण

अटल पूर्णांक dm_stats_create(काष्ठा dm_stats *stats, sector_t start, sector_t end,
			   sector_t step, अचिन्हित stat_flags,
			   अचिन्हित n_histogram_entries,
			   अचिन्हित दीर्घ दीर्घ *histogram_boundaries,
			   स्थिर अक्षर *program_id, स्थिर अक्षर *aux_data,
			   व्योम (*suspend_callback)(काष्ठा mapped_device *),
			   व्योम (*resume_callback)(काष्ठा mapped_device *),
			   काष्ठा mapped_device *md)
अणु
	काष्ठा list_head *l;
	काष्ठा dm_stat *s, *पंचांगp_s;
	sector_t n_entries;
	माप_प्रकार ni;
	माप_प्रकार shared_alloc_size;
	माप_प्रकार percpu_alloc_size;
	माप_प्रकार histogram_alloc_size;
	काष्ठा dm_stat_percpu *p;
	पूर्णांक cpu;
	पूर्णांक ret_id;
	पूर्णांक r;

	अगर (end < start || !step)
		वापस -EINVAL;

	n_entries = end - start;
	अगर (dm_sector_भाग64(n_entries, step))
		n_entries++;

	अगर (n_entries != (माप_प्रकार)n_entries || !(माप_प्रकार)(n_entries + 1))
		वापस -EOVERFLOW;

	shared_alloc_size = काष्ठा_size(s, stat_shared, n_entries);
	अगर ((shared_alloc_size - माप(काष्ठा dm_stat)) / माप(काष्ठा dm_stat_shared) != n_entries)
		वापस -EOVERFLOW;

	percpu_alloc_size = (माप_प्रकार)n_entries * माप(काष्ठा dm_stat_percpu);
	अगर (percpu_alloc_size / माप(काष्ठा dm_stat_percpu) != n_entries)
		वापस -EOVERFLOW;

	histogram_alloc_size = (n_histogram_entries + 1) * (माप_प्रकार)n_entries * माप(अचिन्हित दीर्घ दीर्घ);
	अगर (histogram_alloc_size / (n_histogram_entries + 1) != (माप_प्रकार)n_entries * माप(अचिन्हित दीर्घ दीर्घ))
		वापस -EOVERFLOW;

	अगर (!check_shared_memory(shared_alloc_size + histogram_alloc_size +
				 num_possible_cpus() * (percpu_alloc_size + histogram_alloc_size)))
		वापस -ENOMEM;

	s = dm_kvzalloc(shared_alloc_size, NUMA_NO_NODE);
	अगर (!s)
		वापस -ENOMEM;

	s->stat_flags = stat_flags;
	s->n_entries = n_entries;
	s->start = start;
	s->end = end;
	s->step = step;
	s->shared_alloc_size = shared_alloc_size;
	s->percpu_alloc_size = percpu_alloc_size;
	s->histogram_alloc_size = histogram_alloc_size;

	s->n_histogram_entries = n_histogram_entries;
	s->histogram_boundaries = kmemdup(histogram_boundaries,
					  s->n_histogram_entries * माप(अचिन्हित दीर्घ दीर्घ), GFP_KERNEL);
	अगर (!s->histogram_boundaries) अणु
		r = -ENOMEM;
		जाओ out;
	पूर्ण

	s->program_id = kstrdup(program_id, GFP_KERNEL);
	अगर (!s->program_id) अणु
		r = -ENOMEM;
		जाओ out;
	पूर्ण
	s->aux_data = kstrdup(aux_data, GFP_KERNEL);
	अगर (!s->aux_data) अणु
		r = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (ni = 0; ni < n_entries; ni++) अणु
		atomic_set(&s->stat_shared[ni].in_flight[READ], 0);
		atomic_set(&s->stat_shared[ni].in_flight[WRITE], 0);
	पूर्ण

	अगर (s->n_histogram_entries) अणु
		अचिन्हित दीर्घ दीर्घ *hi;
		hi = dm_kvzalloc(s->histogram_alloc_size, NUMA_NO_NODE);
		अगर (!hi) अणु
			r = -ENOMEM;
			जाओ out;
		पूर्ण
		क्रम (ni = 0; ni < n_entries; ni++) अणु
			s->stat_shared[ni].पंचांगp.histogram = hi;
			hi += s->n_histogram_entries + 1;
		पूर्ण
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		p = dm_kvzalloc(percpu_alloc_size, cpu_to_node(cpu));
		अगर (!p) अणु
			r = -ENOMEM;
			जाओ out;
		पूर्ण
		s->stat_percpu[cpu] = p;
		अगर (s->n_histogram_entries) अणु
			अचिन्हित दीर्घ दीर्घ *hi;
			hi = dm_kvzalloc(s->histogram_alloc_size, cpu_to_node(cpu));
			अगर (!hi) अणु
				r = -ENOMEM;
				जाओ out;
			पूर्ण
			क्रम (ni = 0; ni < n_entries; ni++) अणु
				p[ni].histogram = hi;
				hi += s->n_histogram_entries + 1;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Suspend/resume to make sure there is no i/o in flight,
	 * so that newly created statistics will be exact.
	 *
	 * (note: we couldn't suspend earlier because we must not
	 * allocate memory जबतक suspended)
	 */
	suspend_callback(md);

	mutex_lock(&stats->mutex);
	s->id = 0;
	list_क्रम_each(l, &stats->list) अणु
		पंचांगp_s = container_of(l, काष्ठा dm_stat, list_entry);
		अगर (WARN_ON(पंचांगp_s->id < s->id)) अणु
			r = -EINVAL;
			जाओ out_unlock_resume;
		पूर्ण
		अगर (पंचांगp_s->id > s->id)
			अवरोध;
		अगर (unlikely(s->id == पूर्णांक_उच्च)) अणु
			r = -ENखाता;
			जाओ out_unlock_resume;
		पूर्ण
		s->id++;
	पूर्ण
	ret_id = s->id;
	list_add_tail_rcu(&s->list_entry, l);
	mutex_unlock(&stats->mutex);

	resume_callback(md);

	वापस ret_id;

out_unlock_resume:
	mutex_unlock(&stats->mutex);
	resume_callback(md);
out:
	dm_stat_मुक्त(&s->rcu_head);
	वापस r;
पूर्ण

अटल काष्ठा dm_stat *__dm_stats_find(काष्ठा dm_stats *stats, पूर्णांक id)
अणु
	काष्ठा dm_stat *s;

	list_क्रम_each_entry(s, &stats->list, list_entry) अणु
		अगर (s->id > id)
			अवरोध;
		अगर (s->id == id)
			वापस s;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक dm_stats_delete(काष्ठा dm_stats *stats, पूर्णांक id)
अणु
	काष्ठा dm_stat *s;
	पूर्णांक cpu;

	mutex_lock(&stats->mutex);

	s = __dm_stats_find(stats, id);
	अगर (!s) अणु
		mutex_unlock(&stats->mutex);
		वापस -ENOENT;
	पूर्ण

	list_del_rcu(&s->list_entry);
	mutex_unlock(&stats->mutex);

	/*
	 * vमुक्त can't be called from RCU callback
	 */
	क्रम_each_possible_cpu(cpu)
		अगर (is_vदो_स्मृति_addr(s->stat_percpu) ||
		    is_vदो_स्मृति_addr(s->stat_percpu[cpu][0].histogram))
			जाओ करो_sync_मुक्त;
	अगर (is_vदो_स्मृति_addr(s) ||
	    is_vदो_स्मृति_addr(s->stat_shared[0].पंचांगp.histogram)) अणु
करो_sync_मुक्त:
		synchronize_rcu_expedited();
		dm_stat_मुक्त(&s->rcu_head);
	पूर्ण अन्यथा अणु
		WRITE_ONCE(dm_stat_need_rcu_barrier, 1);
		call_rcu(&s->rcu_head, dm_stat_मुक्त);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dm_stats_list(काष्ठा dm_stats *stats, स्थिर अक्षर *program,
			 अक्षर *result, अचिन्हित maxlen)
अणु
	काष्ठा dm_stat *s;
	sector_t len;
	अचिन्हित sz = 0;

	/*
	 * Output क्रमmat:
	 *   <region_id>: <start_sector>+<length> <step> <program_id> <aux_data>
	 */

	mutex_lock(&stats->mutex);
	list_क्रम_each_entry(s, &stats->list, list_entry) अणु
		अगर (!program || !म_भेद(program, s->program_id)) अणु
			len = s->end - s->start;
			DMEMIT("%d: %llu+%llu %llu %s %s", s->id,
				(अचिन्हित दीर्घ दीर्घ)s->start,
				(अचिन्हित दीर्घ दीर्घ)len,
				(अचिन्हित दीर्घ दीर्घ)s->step,
				s->program_id,
				s->aux_data);
			अगर (s->stat_flags & STAT_PRECISE_TIMESTAMPS)
				DMEMIT(" precise_timestamps");
			अगर (s->n_histogram_entries) अणु
				अचिन्हित i;
				DMEMIT(" histogram:");
				क्रम (i = 0; i < s->n_histogram_entries; i++) अणु
					अगर (i)
						DMEMIT(",");
					DMEMIT("%llu", s->histogram_boundaries[i]);
				पूर्ण
			पूर्ण
			DMEMIT("\n");
		पूर्ण
	पूर्ण
	mutex_unlock(&stats->mutex);

	वापस 1;
पूर्ण

अटल व्योम dm_stat_round(काष्ठा dm_stat *s, काष्ठा dm_stat_shared *shared,
			  काष्ठा dm_stat_percpu *p)
अणु
	/*
	 * This is racy, but so is part_round_stats_single.
	 */
	अचिन्हित दीर्घ दीर्घ now, dअगरference;
	अचिन्हित in_flight_पढ़ो, in_flight_ग_लिखो;

	अगर (likely(!(s->stat_flags & STAT_PRECISE_TIMESTAMPS)))
		now = jअगरfies;
	अन्यथा
		now = kसमय_प्रकारo_ns(kसमय_get());

	dअगरference = now - shared->stamp;
	अगर (!dअगरference)
		वापस;

	in_flight_पढ़ो = (अचिन्हित)atomic_पढ़ो(&shared->in_flight[READ]);
	in_flight_ग_लिखो = (अचिन्हित)atomic_पढ़ो(&shared->in_flight[WRITE]);
	अगर (in_flight_पढ़ो)
		p->io_ticks[READ] += dअगरference;
	अगर (in_flight_ग_लिखो)
		p->io_ticks[WRITE] += dअगरference;
	अगर (in_flight_पढ़ो + in_flight_ग_लिखो) अणु
		p->io_ticks_total += dअगरference;
		p->समय_in_queue += (in_flight_पढ़ो + in_flight_ग_लिखो) * dअगरference;
	पूर्ण
	shared->stamp = now;
पूर्ण

अटल व्योम dm_stat_क्रम_entry(काष्ठा dm_stat *s, माप_प्रकार entry,
			      पूर्णांक idx, sector_t len,
			      काष्ठा dm_stats_aux *stats_aux, bool end,
			      अचिन्हित दीर्घ duration_jअगरfies)
अणु
	काष्ठा dm_stat_shared *shared = &s->stat_shared[entry];
	काष्ठा dm_stat_percpu *p;

	/*
	 * For strict correctness we should use local_irq_save/restore
	 * instead of preempt_disable/enable.
	 *
	 * preempt_disable/enable is racy अगर the driver finishes bios
	 * from non-पूर्णांकerrupt context as well as from पूर्णांकerrupt context
	 * or from more dअगरferent पूर्णांकerrupts.
	 *
	 * On 64-bit architectures the race only results in not counting some
	 * events, so it is acceptable.  On 32-bit architectures the race could
	 * cause the counter going off by 2^32, so we need to करो proper locking
	 * there.
	 *
	 * part_stat_lock()/part_stat_unlock() have this race too.
	 */
#अगर BITS_PER_LONG == 32
	अचिन्हित दीर्घ flags;
	local_irq_save(flags);
#अन्यथा
	preempt_disable();
#पूर्ण_अगर
	p = &s->stat_percpu[smp_processor_id()][entry];

	अगर (!end) अणु
		dm_stat_round(s, shared, p);
		atomic_inc(&shared->in_flight[idx]);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ दीर्घ duration;
		dm_stat_round(s, shared, p);
		atomic_dec(&shared->in_flight[idx]);
		p->sectors[idx] += len;
		p->ios[idx] += 1;
		p->merges[idx] += stats_aux->merged;
		अगर (!(s->stat_flags & STAT_PRECISE_TIMESTAMPS)) अणु
			p->ticks[idx] += duration_jअगरfies;
			duration = jअगरfies_to_msecs(duration_jअगरfies);
		पूर्ण अन्यथा अणु
			p->ticks[idx] += stats_aux->duration_ns;
			duration = stats_aux->duration_ns;
		पूर्ण
		अगर (s->n_histogram_entries) अणु
			अचिन्हित lo = 0, hi = s->n_histogram_entries + 1;
			जबतक (lo + 1 < hi) अणु
				अचिन्हित mid = (lo + hi) / 2;
				अगर (s->histogram_boundaries[mid - 1] > duration) अणु
					hi = mid;
				पूर्ण अन्यथा अणु
					lo = mid;
				पूर्ण

			पूर्ण
			p->histogram[lo]++;
		पूर्ण
	पूर्ण

#अगर BITS_PER_LONG == 32
	local_irq_restore(flags);
#अन्यथा
	preempt_enable();
#पूर्ण_अगर
पूर्ण

अटल व्योम __dm_stat_bio(काष्ठा dm_stat *s, पूर्णांक bi_rw,
			  sector_t bi_sector, sector_t end_sector,
			  bool end, अचिन्हित दीर्घ duration_jअगरfies,
			  काष्ठा dm_stats_aux *stats_aux)
अणु
	sector_t rel_sector, offset, toकरो, fragment_len;
	माप_प्रकार entry;

	अगर (end_sector <= s->start || bi_sector >= s->end)
		वापस;
	अगर (unlikely(bi_sector < s->start)) अणु
		rel_sector = 0;
		toकरो = end_sector - s->start;
	पूर्ण अन्यथा अणु
		rel_sector = bi_sector - s->start;
		toकरो = end_sector - bi_sector;
	पूर्ण
	अगर (unlikely(end_sector > s->end))
		toकरो -= (end_sector - s->end);

	offset = dm_sector_भाग64(rel_sector, s->step);
	entry = rel_sector;
	करो अणु
		अगर (WARN_ON_ONCE(entry >= s->n_entries)) अणु
			DMCRIT("Invalid area access in region id %d", s->id);
			वापस;
		पूर्ण
		fragment_len = toकरो;
		अगर (fragment_len > s->step - offset)
			fragment_len = s->step - offset;
		dm_stat_क्रम_entry(s, entry, bi_rw, fragment_len,
				  stats_aux, end, duration_jअगरfies);
		toकरो -= fragment_len;
		entry++;
		offset = 0;
	पूर्ण जबतक (unlikely(toकरो != 0));
पूर्ण

व्योम dm_stats_account_io(काष्ठा dm_stats *stats, अचिन्हित दीर्घ bi_rw,
			 sector_t bi_sector, अचिन्हित bi_sectors, bool end,
			 अचिन्हित दीर्घ duration_jअगरfies,
			 काष्ठा dm_stats_aux *stats_aux)
अणु
	काष्ठा dm_stat *s;
	sector_t end_sector;
	काष्ठा dm_stats_last_position *last;
	bool got_precise_समय;

	अगर (unlikely(!bi_sectors))
		वापस;

	end_sector = bi_sector + bi_sectors;

	अगर (!end) अणु
		/*
		 * A race condition can at worst result in the merged flag being
		 * misrepresented, so we करोn't have to disable preemption here.
		 */
		last = raw_cpu_ptr(stats->last);
		stats_aux->merged =
			(bi_sector == (READ_ONCE(last->last_sector) &&
				       ((bi_rw == WRITE) ==
					(READ_ONCE(last->last_rw) == WRITE))
				       ));
		WRITE_ONCE(last->last_sector, end_sector);
		WRITE_ONCE(last->last_rw, bi_rw);
	पूर्ण

	rcu_पढ़ो_lock();

	got_precise_समय = false;
	list_क्रम_each_entry_rcu(s, &stats->list, list_entry) अणु
		अगर (s->stat_flags & STAT_PRECISE_TIMESTAMPS && !got_precise_समय) अणु
			अगर (!end)
				stats_aux->duration_ns = kसमय_प्रकारo_ns(kसमय_get());
			अन्यथा
				stats_aux->duration_ns = kसमय_प्रकारo_ns(kसमय_get()) - stats_aux->duration_ns;
			got_precise_समय = true;
		पूर्ण
		__dm_stat_bio(s, bi_rw, bi_sector, end_sector, end, duration_jअगरfies, stats_aux);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम __dm_stat_init_temporary_percpu_totals(काष्ठा dm_stat_shared *shared,
						   काष्ठा dm_stat *s, माप_प्रकार x)
अणु
	पूर्णांक cpu;
	काष्ठा dm_stat_percpu *p;

	local_irq_disable();
	p = &s->stat_percpu[smp_processor_id()][x];
	dm_stat_round(s, shared, p);
	local_irq_enable();

	shared->पंचांगp.sectors[READ] = 0;
	shared->पंचांगp.sectors[WRITE] = 0;
	shared->पंचांगp.ios[READ] = 0;
	shared->पंचांगp.ios[WRITE] = 0;
	shared->पंचांगp.merges[READ] = 0;
	shared->पंचांगp.merges[WRITE] = 0;
	shared->पंचांगp.ticks[READ] = 0;
	shared->पंचांगp.ticks[WRITE] = 0;
	shared->पंचांगp.io_ticks[READ] = 0;
	shared->पंचांगp.io_ticks[WRITE] = 0;
	shared->पंचांगp.io_ticks_total = 0;
	shared->पंचांगp.समय_in_queue = 0;

	अगर (s->n_histogram_entries)
		स_रखो(shared->पंचांगp.histogram, 0, (s->n_histogram_entries + 1) * माप(अचिन्हित दीर्घ दीर्घ));

	क्रम_each_possible_cpu(cpu) अणु
		p = &s->stat_percpu[cpu][x];
		shared->पंचांगp.sectors[READ] += READ_ONCE(p->sectors[READ]);
		shared->पंचांगp.sectors[WRITE] += READ_ONCE(p->sectors[WRITE]);
		shared->पंचांगp.ios[READ] += READ_ONCE(p->ios[READ]);
		shared->पंचांगp.ios[WRITE] += READ_ONCE(p->ios[WRITE]);
		shared->पंचांगp.merges[READ] += READ_ONCE(p->merges[READ]);
		shared->पंचांगp.merges[WRITE] += READ_ONCE(p->merges[WRITE]);
		shared->पंचांगp.ticks[READ] += READ_ONCE(p->ticks[READ]);
		shared->पंचांगp.ticks[WRITE] += READ_ONCE(p->ticks[WRITE]);
		shared->पंचांगp.io_ticks[READ] += READ_ONCE(p->io_ticks[READ]);
		shared->पंचांगp.io_ticks[WRITE] += READ_ONCE(p->io_ticks[WRITE]);
		shared->पंचांगp.io_ticks_total += READ_ONCE(p->io_ticks_total);
		shared->पंचांगp.समय_in_queue += READ_ONCE(p->समय_in_queue);
		अगर (s->n_histogram_entries) अणु
			अचिन्हित i;
			क्रम (i = 0; i < s->n_histogram_entries + 1; i++)
				shared->पंचांगp.histogram[i] += READ_ONCE(p->histogram[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __dm_stat_clear(काष्ठा dm_stat *s, माप_प्रकार idx_start, माप_प्रकार idx_end,
			    bool init_पंचांगp_percpu_totals)
अणु
	माप_प्रकार x;
	काष्ठा dm_stat_shared *shared;
	काष्ठा dm_stat_percpu *p;

	क्रम (x = idx_start; x < idx_end; x++) अणु
		shared = &s->stat_shared[x];
		अगर (init_पंचांगp_percpu_totals)
			__dm_stat_init_temporary_percpu_totals(shared, s, x);
		local_irq_disable();
		p = &s->stat_percpu[smp_processor_id()][x];
		p->sectors[READ] -= shared->पंचांगp.sectors[READ];
		p->sectors[WRITE] -= shared->पंचांगp.sectors[WRITE];
		p->ios[READ] -= shared->पंचांगp.ios[READ];
		p->ios[WRITE] -= shared->पंचांगp.ios[WRITE];
		p->merges[READ] -= shared->पंचांगp.merges[READ];
		p->merges[WRITE] -= shared->पंचांगp.merges[WRITE];
		p->ticks[READ] -= shared->पंचांगp.ticks[READ];
		p->ticks[WRITE] -= shared->पंचांगp.ticks[WRITE];
		p->io_ticks[READ] -= shared->पंचांगp.io_ticks[READ];
		p->io_ticks[WRITE] -= shared->पंचांगp.io_ticks[WRITE];
		p->io_ticks_total -= shared->पंचांगp.io_ticks_total;
		p->समय_in_queue -= shared->पंचांगp.समय_in_queue;
		local_irq_enable();
		अगर (s->n_histogram_entries) अणु
			अचिन्हित i;
			क्रम (i = 0; i < s->n_histogram_entries + 1; i++) अणु
				local_irq_disable();
				p = &s->stat_percpu[smp_processor_id()][x];
				p->histogram[i] -= shared->पंचांगp.histogram[i];
				local_irq_enable();
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dm_stats_clear(काष्ठा dm_stats *stats, पूर्णांक id)
अणु
	काष्ठा dm_stat *s;

	mutex_lock(&stats->mutex);

	s = __dm_stats_find(stats, id);
	अगर (!s) अणु
		mutex_unlock(&stats->mutex);
		वापस -ENOENT;
	पूर्ण

	__dm_stat_clear(s, 0, s->n_entries, true);

	mutex_unlock(&stats->mutex);

	वापस 1;
पूर्ण

/*
 * This is like jअगरfies_to_msec, but works क्रम 64-bit values.
 */
अटल अचिन्हित दीर्घ दीर्घ dm_jअगरfies_to_msec64(काष्ठा dm_stat *s, अचिन्हित दीर्घ दीर्घ j)
अणु
	अचिन्हित दीर्घ दीर्घ result;
	अचिन्हित mult;

	अगर (s->stat_flags & STAT_PRECISE_TIMESTAMPS)
		वापस j;

	result = 0;
	अगर (j)
		result = jअगरfies_to_msecs(j & 0x3fffff);
	अगर (j >= 1 << 22) अणु
		mult = jअगरfies_to_msecs(1 << 22);
		result += (अचिन्हित दीर्घ दीर्घ)mult * (अचिन्हित दीर्घ दीर्घ)jअगरfies_to_msecs((j >> 22) & 0x3fffff);
	पूर्ण
	अगर (j >= 1ULL << 44)
		result += (अचिन्हित दीर्घ दीर्घ)mult * (अचिन्हित दीर्घ दीर्घ)mult * (अचिन्हित दीर्घ दीर्घ)jअगरfies_to_msecs(j >> 44);

	वापस result;
पूर्ण

अटल पूर्णांक dm_stats_prपूर्णांक(काष्ठा dm_stats *stats, पूर्णांक id,
			  माप_प्रकार idx_start, माप_प्रकार idx_len,
			  bool clear, अक्षर *result, अचिन्हित maxlen)
अणु
	अचिन्हित sz = 0;
	काष्ठा dm_stat *s;
	माप_प्रकार x;
	sector_t start, end, step;
	माप_प्रकार idx_end;
	काष्ठा dm_stat_shared *shared;

	/*
	 * Output क्रमmat:
	 *   <start_sector>+<length> counters
	 */

	mutex_lock(&stats->mutex);

	s = __dm_stats_find(stats, id);
	अगर (!s) अणु
		mutex_unlock(&stats->mutex);
		वापस -ENOENT;
	पूर्ण

	idx_end = idx_start + idx_len;
	अगर (idx_end < idx_start ||
	    idx_end > s->n_entries)
		idx_end = s->n_entries;

	अगर (idx_start > idx_end)
		idx_start = idx_end;

	step = s->step;
	start = s->start + (step * idx_start);

	क्रम (x = idx_start; x < idx_end; x++, start = end) अणु
		shared = &s->stat_shared[x];
		end = start + step;
		अगर (unlikely(end > s->end))
			end = s->end;

		__dm_stat_init_temporary_percpu_totals(shared, s, x);

		DMEMIT("%llu+%llu %llu %llu %llu %llu %llu %llu %llu %llu %d %llu %llu %llu %llu",
		       (अचिन्हित दीर्घ दीर्घ)start,
		       (अचिन्हित दीर्घ दीर्घ)step,
		       shared->पंचांगp.ios[READ],
		       shared->पंचांगp.merges[READ],
		       shared->पंचांगp.sectors[READ],
		       dm_jअगरfies_to_msec64(s, shared->पंचांगp.ticks[READ]),
		       shared->पंचांगp.ios[WRITE],
		       shared->पंचांगp.merges[WRITE],
		       shared->पंचांगp.sectors[WRITE],
		       dm_jअगरfies_to_msec64(s, shared->पंचांगp.ticks[WRITE]),
		       dm_stat_in_flight(shared),
		       dm_jअगरfies_to_msec64(s, shared->पंचांगp.io_ticks_total),
		       dm_jअगरfies_to_msec64(s, shared->पंचांगp.समय_in_queue),
		       dm_jअगरfies_to_msec64(s, shared->पंचांगp.io_ticks[READ]),
		       dm_jअगरfies_to_msec64(s, shared->पंचांगp.io_ticks[WRITE]));
		अगर (s->n_histogram_entries) अणु
			अचिन्हित i;
			क्रम (i = 0; i < s->n_histogram_entries + 1; i++) अणु
				DMEMIT("%s%llu", !i ? " " : ":", shared->पंचांगp.histogram[i]);
			पूर्ण
		पूर्ण
		DMEMIT("\n");

		अगर (unlikely(sz + 1 >= maxlen))
			जाओ buffer_overflow;
	पूर्ण

	अगर (clear)
		__dm_stat_clear(s, idx_start, idx_end, false);

buffer_overflow:
	mutex_unlock(&stats->mutex);

	वापस 1;
पूर्ण

अटल पूर्णांक dm_stats_set_aux(काष्ठा dm_stats *stats, पूर्णांक id, स्थिर अक्षर *aux_data)
अणु
	काष्ठा dm_stat *s;
	स्थिर अक्षर *new_aux_data;

	mutex_lock(&stats->mutex);

	s = __dm_stats_find(stats, id);
	अगर (!s) अणु
		mutex_unlock(&stats->mutex);
		वापस -ENOENT;
	पूर्ण

	new_aux_data = kstrdup(aux_data, GFP_KERNEL);
	अगर (!new_aux_data) अणु
		mutex_unlock(&stats->mutex);
		वापस -ENOMEM;
	पूर्ण

	kमुक्त(s->aux_data);
	s->aux_data = new_aux_data;

	mutex_unlock(&stats->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक parse_histogram(स्थिर अक्षर *h, अचिन्हित *n_histogram_entries,
			   अचिन्हित दीर्घ दीर्घ **histogram_boundaries)
अणु
	स्थिर अक्षर *q;
	अचिन्हित n;
	अचिन्हित दीर्घ दीर्घ last;

	*n_histogram_entries = 1;
	क्रम (q = h; *q; q++)
		अगर (*q == ',')
			(*n_histogram_entries)++;

	*histogram_boundaries = kदो_स्मृति_array(*n_histogram_entries,
					      माप(अचिन्हित दीर्घ दीर्घ),
					      GFP_KERNEL);
	अगर (!*histogram_boundaries)
		वापस -ENOMEM;

	n = 0;
	last = 0;
	जबतक (1) अणु
		अचिन्हित दीर्घ दीर्घ hi;
		पूर्णांक s;
		अक्षर ch;
		s = माला_पूछो(h, "%llu%c", &hi, &ch);
		अगर (!s || (s == 2 && ch != ','))
			वापस -EINVAL;
		अगर (hi <= last)
			वापस -EINVAL;
		last = hi;
		(*histogram_boundaries)[n] = hi;
		अगर (s == 1)
			वापस 0;
		h = म_अक्षर(h, ',') + 1;
		n++;
	पूर्ण
पूर्ण

अटल पूर्णांक message_stats_create(काष्ठा mapped_device *md,
				अचिन्हित argc, अक्षर **argv,
				अक्षर *result, अचिन्हित maxlen)
अणु
	पूर्णांक r;
	पूर्णांक id;
	अक्षर dummy;
	अचिन्हित दीर्घ दीर्घ start, end, len, step;
	अचिन्हित भागisor;
	स्थिर अक्षर *program_id, *aux_data;
	अचिन्हित stat_flags = 0;

	अचिन्हित n_histogram_entries = 0;
	अचिन्हित दीर्घ दीर्घ *histogram_boundaries = शून्य;

	काष्ठा dm_arg_set as, as_backup;
	स्थिर अक्षर *a;
	अचिन्हित feature_args;

	/*
	 * Input क्रमmat:
	 *   <range> <step> [<extra_parameters> <parameters>] [<program_id> [<aux_data>]]
	 */

	अगर (argc < 3)
		जाओ ret_einval;

	as.argc = argc;
	as.argv = argv;
	dm_consume_args(&as, 1);

	a = dm_shअगरt_arg(&as);
	अगर (!म_भेद(a, "-")) अणु
		start = 0;
		len = dm_get_size(md);
		अगर (!len)
			len = 1;
	पूर्ण अन्यथा अगर (माला_पूछो(a, "%llu+%llu%c", &start, &len, &dummy) != 2 ||
		   start != (sector_t)start || len != (sector_t)len)
		जाओ ret_einval;

	end = start + len;
	अगर (start >= end)
		जाओ ret_einval;

	a = dm_shअगरt_arg(&as);
	अगर (माला_पूछो(a, "/%u%c", &भागisor, &dummy) == 1) अणु
		अगर (!भागisor)
			वापस -EINVAL;
		step = end - start;
		अगर (करो_भाग(step, भागisor))
			step++;
		अगर (!step)
			step = 1;
	पूर्ण अन्यथा अगर (माला_पूछो(a, "%llu%c", &step, &dummy) != 1 ||
		   step != (sector_t)step || !step)
		जाओ ret_einval;

	as_backup = as;
	a = dm_shअगरt_arg(&as);
	अगर (a && माला_पूछो(a, "%u%c", &feature_args, &dummy) == 1) अणु
		जबतक (feature_args--) अणु
			a = dm_shअगरt_arg(&as);
			अगर (!a)
				जाओ ret_einval;
			अगर (!strहालcmp(a, "precise_timestamps"))
				stat_flags |= STAT_PRECISE_TIMESTAMPS;
			अन्यथा अगर (!strnहालcmp(a, "histogram:", 10)) अणु
				अगर (n_histogram_entries)
					जाओ ret_einval;
				अगर ((r = parse_histogram(a + 10, &n_histogram_entries, &histogram_boundaries)))
					जाओ ret;
			पूर्ण अन्यथा
				जाओ ret_einval;
		पूर्ण
	पूर्ण अन्यथा अणु
		as = as_backup;
	पूर्ण

	program_id = "-";
	aux_data = "-";

	a = dm_shअगरt_arg(&as);
	अगर (a)
		program_id = a;

	a = dm_shअगरt_arg(&as);
	अगर (a)
		aux_data = a;

	अगर (as.argc)
		जाओ ret_einval;

	/*
	 * If a buffer overflow happens after we created the region,
	 * it's too late (the userspace would retry with a larger
	 * buffer, but the region id that caused the overflow is alपढ़ोy
	 * leaked).  So we must detect buffer overflow in advance.
	 */
	snम_लिखो(result, maxlen, "%d", पूर्णांक_उच्च);
	अगर (dm_message_test_buffer_overflow(result, maxlen)) अणु
		r = 1;
		जाओ ret;
	पूर्ण

	id = dm_stats_create(dm_get_stats(md), start, end, step, stat_flags,
			     n_histogram_entries, histogram_boundaries, program_id, aux_data,
			     dm_पूर्णांकernal_suspend_fast, dm_पूर्णांकernal_resume_fast, md);
	अगर (id < 0) अणु
		r = id;
		जाओ ret;
	पूर्ण

	snम_लिखो(result, maxlen, "%d", id);

	r = 1;
	जाओ ret;

ret_einval:
	r = -EINVAL;
ret:
	kमुक्त(histogram_boundaries);
	वापस r;
पूर्ण

अटल पूर्णांक message_stats_delete(काष्ठा mapped_device *md,
				अचिन्हित argc, अक्षर **argv)
अणु
	पूर्णांक id;
	अक्षर dummy;

	अगर (argc != 2)
		वापस -EINVAL;

	अगर (माला_पूछो(argv[1], "%d%c", &id, &dummy) != 1 || id < 0)
		वापस -EINVAL;

	वापस dm_stats_delete(dm_get_stats(md), id);
पूर्ण

अटल पूर्णांक message_stats_clear(काष्ठा mapped_device *md,
			       अचिन्हित argc, अक्षर **argv)
अणु
	पूर्णांक id;
	अक्षर dummy;

	अगर (argc != 2)
		वापस -EINVAL;

	अगर (माला_पूछो(argv[1], "%d%c", &id, &dummy) != 1 || id < 0)
		वापस -EINVAL;

	वापस dm_stats_clear(dm_get_stats(md), id);
पूर्ण

अटल पूर्णांक message_stats_list(काष्ठा mapped_device *md,
			      अचिन्हित argc, अक्षर **argv,
			      अक्षर *result, अचिन्हित maxlen)
अणु
	पूर्णांक r;
	स्थिर अक्षर *program = शून्य;

	अगर (argc < 1 || argc > 2)
		वापस -EINVAL;

	अगर (argc > 1) अणु
		program = kstrdup(argv[1], GFP_KERNEL);
		अगर (!program)
			वापस -ENOMEM;
	पूर्ण

	r = dm_stats_list(dm_get_stats(md), program, result, maxlen);

	kमुक्त(program);

	वापस r;
पूर्ण

अटल पूर्णांक message_stats_prपूर्णांक(काष्ठा mapped_device *md,
			       अचिन्हित argc, अक्षर **argv, bool clear,
			       अक्षर *result, अचिन्हित maxlen)
अणु
	पूर्णांक id;
	अक्षर dummy;
	अचिन्हित दीर्घ idx_start = 0, idx_len = अच_दीर्घ_उच्च;

	अगर (argc != 2 && argc != 4)
		वापस -EINVAL;

	अगर (माला_पूछो(argv[1], "%d%c", &id, &dummy) != 1 || id < 0)
		वापस -EINVAL;

	अगर (argc > 3) अणु
		अगर (म_भेद(argv[2], "-") &&
		    माला_पूछो(argv[2], "%lu%c", &idx_start, &dummy) != 1)
			वापस -EINVAL;
		अगर (म_भेद(argv[3], "-") &&
		    माला_पूछो(argv[3], "%lu%c", &idx_len, &dummy) != 1)
			वापस -EINVAL;
	पूर्ण

	वापस dm_stats_prपूर्णांक(dm_get_stats(md), id, idx_start, idx_len, clear,
			      result, maxlen);
पूर्ण

अटल पूर्णांक message_stats_set_aux(काष्ठा mapped_device *md,
				 अचिन्हित argc, अक्षर **argv)
अणु
	पूर्णांक id;
	अक्षर dummy;

	अगर (argc != 3)
		वापस -EINVAL;

	अगर (माला_पूछो(argv[1], "%d%c", &id, &dummy) != 1 || id < 0)
		वापस -EINVAL;

	वापस dm_stats_set_aux(dm_get_stats(md), id, argv[2]);
पूर्ण

पूर्णांक dm_stats_message(काष्ठा mapped_device *md, अचिन्हित argc, अक्षर **argv,
		     अक्षर *result, अचिन्हित maxlen)
अणु
	पूर्णांक r;

	/* All messages here must start with '@' */
	अगर (!strहालcmp(argv[0], "@stats_create"))
		r = message_stats_create(md, argc, argv, result, maxlen);
	अन्यथा अगर (!strहालcmp(argv[0], "@stats_delete"))
		r = message_stats_delete(md, argc, argv);
	अन्यथा अगर (!strहालcmp(argv[0], "@stats_clear"))
		r = message_stats_clear(md, argc, argv);
	अन्यथा अगर (!strहालcmp(argv[0], "@stats_list"))
		r = message_stats_list(md, argc, argv, result, maxlen);
	अन्यथा अगर (!strहालcmp(argv[0], "@stats_print"))
		r = message_stats_prपूर्णांक(md, argc, argv, false, result, maxlen);
	अन्यथा अगर (!strहालcmp(argv[0], "@stats_print_clear"))
		r = message_stats_prपूर्णांक(md, argc, argv, true, result, maxlen);
	अन्यथा अगर (!strहालcmp(argv[0], "@stats_set_aux"))
		r = message_stats_set_aux(md, argc, argv);
	अन्यथा
		वापस 2; /* this wasn't a stats message */

	अगर (r == -EINVAL)
		DMWARN("Invalid parameters for message %s", argv[0]);

	वापस r;
पूर्ण

पूर्णांक __init dm_statistics_init(व्योम)
अणु
	shared_memory_amount = 0;
	dm_stat_need_rcu_barrier = 0;
	वापस 0;
पूर्ण

व्योम dm_statistics_निकास(व्योम)
अणु
	अगर (dm_stat_need_rcu_barrier)
		rcu_barrier();
	अगर (WARN_ON(shared_memory_amount))
		DMCRIT("shared_memory_amount leaked: %lu", shared_memory_amount);
पूर्ण

module_param_named(stats_current_allocated_bytes, shared_memory_amount, uदीर्घ, S_IRUGO);
MODULE_PARM_DESC(stats_current_allocated_bytes, "Memory currently used by statistics");
