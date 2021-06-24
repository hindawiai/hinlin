<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2017 Thomas Gleixner <tglx@linutronix.de>

#समावेश <linux/spinlock.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/percpu.h>
#समावेश <linux/cpu.h>
#समावेश <linux/irq.h>

#घोषणा IRQ_MATRIX_SIZE	(BITS_TO_LONGS(IRQ_MATRIX_BITS))

काष्ठा cpumap अणु
	अचिन्हित पूर्णांक		available;
	अचिन्हित पूर्णांक		allocated;
	अचिन्हित पूर्णांक		managed;
	अचिन्हित पूर्णांक		managed_allocated;
	bool			initialized;
	bool			online;
	अचिन्हित दीर्घ		alloc_map[IRQ_MATRIX_SIZE];
	अचिन्हित दीर्घ		managed_map[IRQ_MATRIX_SIZE];
पूर्ण;

काष्ठा irq_matrix अणु
	अचिन्हित पूर्णांक		matrix_bits;
	अचिन्हित पूर्णांक		alloc_start;
	अचिन्हित पूर्णांक		alloc_end;
	अचिन्हित पूर्णांक		alloc_size;
	अचिन्हित पूर्णांक		global_available;
	अचिन्हित पूर्णांक		global_reserved;
	अचिन्हित पूर्णांक		प्रणालीbits_inalloc;
	अचिन्हित पूर्णांक		total_allocated;
	अचिन्हित पूर्णांक		online_maps;
	काष्ठा cpumap __percpu	*maps;
	अचिन्हित दीर्घ		scratch_map[IRQ_MATRIX_SIZE];
	अचिन्हित दीर्घ		प्रणाली_map[IRQ_MATRIX_SIZE];
पूर्ण;

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/irq_matrix.h>

/**
 * irq_alloc_matrix - Allocate a irq_matrix काष्ठाure and initialize it
 * @matrix_bits:	Number of matrix bits must be <= IRQ_MATRIX_BITS
 * @alloc_start:	From which bit the allocation search starts
 * @alloc_end:		At which bit the allocation search ends, i.e first
 *			invalid bit
 */
__init काष्ठा irq_matrix *irq_alloc_matrix(अचिन्हित पूर्णांक matrix_bits,
					   अचिन्हित पूर्णांक alloc_start,
					   अचिन्हित पूर्णांक alloc_end)
अणु
	काष्ठा irq_matrix *m;

	अगर (matrix_bits > IRQ_MATRIX_BITS)
		वापस शून्य;

	m = kzalloc(माप(*m), GFP_KERNEL);
	अगर (!m)
		वापस शून्य;

	m->matrix_bits = matrix_bits;
	m->alloc_start = alloc_start;
	m->alloc_end = alloc_end;
	m->alloc_size = alloc_end - alloc_start;
	m->maps = alloc_percpu(*m->maps);
	अगर (!m->maps) अणु
		kमुक्त(m);
		वापस शून्य;
	पूर्ण
	वापस m;
पूर्ण

/**
 * irq_matrix_online - Bring the local CPU matrix online
 * @m:		Matrix poपूर्णांकer
 */
व्योम irq_matrix_online(काष्ठा irq_matrix *m)
अणु
	काष्ठा cpumap *cm = this_cpu_ptr(m->maps);

	BUG_ON(cm->online);

	अगर (!cm->initialized) अणु
		cm->available = m->alloc_size;
		cm->available -= cm->managed + m->प्रणालीbits_inalloc;
		cm->initialized = true;
	पूर्ण
	m->global_available += cm->available;
	cm->online = true;
	m->online_maps++;
	trace_irq_matrix_online(m);
पूर्ण

/**
 * irq_matrix_offline - Bring the local CPU matrix offline
 * @m:		Matrix poपूर्णांकer
 */
व्योम irq_matrix_offline(काष्ठा irq_matrix *m)
अणु
	काष्ठा cpumap *cm = this_cpu_ptr(m->maps);

	/* Update the global available size */
	m->global_available -= cm->available;
	cm->online = false;
	m->online_maps--;
	trace_irq_matrix_offline(m);
पूर्ण

अटल अचिन्हित पूर्णांक matrix_alloc_area(काष्ठा irq_matrix *m, काष्ठा cpumap *cm,
				      अचिन्हित पूर्णांक num, bool managed)
अणु
	अचिन्हित पूर्णांक area, start = m->alloc_start;
	अचिन्हित पूर्णांक end = m->alloc_end;

	biपंचांगap_or(m->scratch_map, cm->managed_map, m->प्रणाली_map, end);
	biपंचांगap_or(m->scratch_map, m->scratch_map, cm->alloc_map, end);
	area = biपंचांगap_find_next_zero_area(m->scratch_map, end, start, num, 0);
	अगर (area >= end)
		वापस area;
	अगर (managed)
		biपंचांगap_set(cm->managed_map, area, num);
	अन्यथा
		biपंचांगap_set(cm->alloc_map, area, num);
	वापस area;
पूर्ण

/* Find the best CPU which has the lowest vector allocation count */
अटल अचिन्हित पूर्णांक matrix_find_best_cpu(काष्ठा irq_matrix *m,
					स्थिर काष्ठा cpumask *msk)
अणु
	अचिन्हित पूर्णांक cpu, best_cpu, maxavl = 0;
	काष्ठा cpumap *cm;

	best_cpu = अच_पूर्णांक_उच्च;

	क्रम_each_cpu(cpu, msk) अणु
		cm = per_cpu_ptr(m->maps, cpu);

		अगर (!cm->online || cm->available <= maxavl)
			जारी;

		best_cpu = cpu;
		maxavl = cm->available;
	पूर्ण
	वापस best_cpu;
पूर्ण

/* Find the best CPU which has the lowest number of managed IRQs allocated */
अटल अचिन्हित पूर्णांक matrix_find_best_cpu_managed(काष्ठा irq_matrix *m,
						स्थिर काष्ठा cpumask *msk)
अणु
	अचिन्हित पूर्णांक cpu, best_cpu, allocated = अच_पूर्णांक_उच्च;
	काष्ठा cpumap *cm;

	best_cpu = अच_पूर्णांक_उच्च;

	क्रम_each_cpu(cpu, msk) अणु
		cm = per_cpu_ptr(m->maps, cpu);

		अगर (!cm->online || cm->managed_allocated > allocated)
			जारी;

		best_cpu = cpu;
		allocated = cm->managed_allocated;
	पूर्ण
	वापस best_cpu;
पूर्ण

/**
 * irq_matrix_assign_प्रणाली - Assign प्रणाली wide entry in the matrix
 * @m:		Matrix poपूर्णांकer
 * @bit:	Which bit to reserve
 * @replace:	Replace an alपढ़ोy allocated vector with a प्रणाली
 *		vector at the same bit position.
 *
 * The BUG_ON()s below are on purpose. If this goes wrong in the
 * early boot process, then the chance to survive is about zero.
 * If this happens when the प्रणाली is lअगरe, it's not much better.
 */
व्योम irq_matrix_assign_प्रणाली(काष्ठा irq_matrix *m, अचिन्हित पूर्णांक bit,
			      bool replace)
अणु
	काष्ठा cpumap *cm = this_cpu_ptr(m->maps);

	BUG_ON(bit > m->matrix_bits);
	BUG_ON(m->online_maps > 1 || (m->online_maps && !replace));

	set_bit(bit, m->प्रणाली_map);
	अगर (replace) अणु
		BUG_ON(!test_and_clear_bit(bit, cm->alloc_map));
		cm->allocated--;
		m->total_allocated--;
	पूर्ण
	अगर (bit >= m->alloc_start && bit < m->alloc_end)
		m->प्रणालीbits_inalloc++;

	trace_irq_matrix_assign_प्रणाली(bit, m);
पूर्ण

/**
 * irq_matrix_reserve_managed - Reserve a managed पूर्णांकerrupt in a CPU map
 * @m:		Matrix poपूर्णांकer
 * @msk:	On which CPUs the bits should be reserved.
 *
 * Can be called क्रम offline CPUs. Note, this will only reserve one bit
 * on all CPUs in @msk, but it's not guaranteed that the bits are at the
 * same offset on all CPUs
 */
पूर्णांक irq_matrix_reserve_managed(काष्ठा irq_matrix *m, स्थिर काष्ठा cpumask *msk)
अणु
	अचिन्हित पूर्णांक cpu, failed_cpu;

	क्रम_each_cpu(cpu, msk) अणु
		काष्ठा cpumap *cm = per_cpu_ptr(m->maps, cpu);
		अचिन्हित पूर्णांक bit;

		bit = matrix_alloc_area(m, cm, 1, true);
		अगर (bit >= m->alloc_end)
			जाओ cleanup;
		cm->managed++;
		अगर (cm->online) अणु
			cm->available--;
			m->global_available--;
		पूर्ण
		trace_irq_matrix_reserve_managed(bit, cpu, m, cm);
	पूर्ण
	वापस 0;
cleanup:
	failed_cpu = cpu;
	क्रम_each_cpu(cpu, msk) अणु
		अगर (cpu == failed_cpu)
			अवरोध;
		irq_matrix_हटाओ_managed(m, cpumask_of(cpu));
	पूर्ण
	वापस -ENOSPC;
पूर्ण

/**
 * irq_matrix_हटाओ_managed - Remove managed पूर्णांकerrupts in a CPU map
 * @m:		Matrix poपूर्णांकer
 * @msk:	On which CPUs the bits should be हटाओd
 *
 * Can be called क्रम offline CPUs
 *
 * This हटाओs not allocated managed पूर्णांकerrupts from the map. It करोes
 * not matter which one because the managed पूर्णांकerrupts मुक्त their
 * allocation when they shut करोwn. If not, the accounting is screwed,
 * but all what can be करोne at this poपूर्णांक is warn about it.
 */
व्योम irq_matrix_हटाओ_managed(काष्ठा irq_matrix *m, स्थिर काष्ठा cpumask *msk)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, msk) अणु
		काष्ठा cpumap *cm = per_cpu_ptr(m->maps, cpu);
		अचिन्हित पूर्णांक bit, end = m->alloc_end;

		अगर (WARN_ON_ONCE(!cm->managed))
			जारी;

		/* Get managed bit which are not allocated */
		biपंचांगap_andnot(m->scratch_map, cm->managed_map, cm->alloc_map, end);

		bit = find_first_bit(m->scratch_map, end);
		अगर (WARN_ON_ONCE(bit >= end))
			जारी;

		clear_bit(bit, cm->managed_map);

		cm->managed--;
		अगर (cm->online) अणु
			cm->available++;
			m->global_available++;
		पूर्ण
		trace_irq_matrix_हटाओ_managed(bit, cpu, m, cm);
	पूर्ण
पूर्ण

/**
 * irq_matrix_alloc_managed - Allocate a managed पूर्णांकerrupt in a CPU map
 * @m:		Matrix poपूर्णांकer
 * @cpu:	On which CPU the पूर्णांकerrupt should be allocated
 */
पूर्णांक irq_matrix_alloc_managed(काष्ठा irq_matrix *m, स्थिर काष्ठा cpumask *msk,
			     अचिन्हित पूर्णांक *mapped_cpu)
अणु
	अचिन्हित पूर्णांक bit, cpu, end = m->alloc_end;
	काष्ठा cpumap *cm;

	अगर (cpumask_empty(msk))
		वापस -EINVAL;

	cpu = matrix_find_best_cpu_managed(m, msk);
	अगर (cpu == अच_पूर्णांक_उच्च)
		वापस -ENOSPC;

	cm = per_cpu_ptr(m->maps, cpu);
	end = m->alloc_end;
	/* Get managed bit which are not allocated */
	biपंचांगap_andnot(m->scratch_map, cm->managed_map, cm->alloc_map, end);
	bit = find_first_bit(m->scratch_map, end);
	अगर (bit >= end)
		वापस -ENOSPC;
	set_bit(bit, cm->alloc_map);
	cm->allocated++;
	cm->managed_allocated++;
	m->total_allocated++;
	*mapped_cpu = cpu;
	trace_irq_matrix_alloc_managed(bit, cpu, m, cm);
	वापस bit;
पूर्ण

/**
 * irq_matrix_assign - Assign a pपुनः_स्मृतिated पूर्णांकerrupt in the local CPU map
 * @m:		Matrix poपूर्णांकer
 * @bit:	Which bit to mark
 *
 * This should only be used to mark pपुनः_स्मृतिated vectors
 */
व्योम irq_matrix_assign(काष्ठा irq_matrix *m, अचिन्हित पूर्णांक bit)
अणु
	काष्ठा cpumap *cm = this_cpu_ptr(m->maps);

	अगर (WARN_ON_ONCE(bit < m->alloc_start || bit >= m->alloc_end))
		वापस;
	अगर (WARN_ON_ONCE(test_and_set_bit(bit, cm->alloc_map)))
		वापस;
	cm->allocated++;
	m->total_allocated++;
	cm->available--;
	m->global_available--;
	trace_irq_matrix_assign(bit, smp_processor_id(), m, cm);
पूर्ण

/**
 * irq_matrix_reserve - Reserve पूर्णांकerrupts
 * @m:		Matrix poपूर्णांकer
 *
 * This is merely a book keeping call. It increments the number of globally
 * reserved पूर्णांकerrupt bits w/o actually allocating them. This allows to
 * setup पूर्णांकerrupt descriptors w/o assigning low level resources to it.
 * The actual allocation happens when the पूर्णांकerrupt माला_लो activated.
 */
व्योम irq_matrix_reserve(काष्ठा irq_matrix *m)
अणु
	अगर (m->global_reserved == m->global_available)
		pr_warn("Interrupt reservation exceeds available resources\n");

	m->global_reserved++;
	trace_irq_matrix_reserve(m);
पूर्ण

/**
 * irq_matrix_हटाओ_reserved - Remove पूर्णांकerrupt reservation
 * @m:		Matrix poपूर्णांकer
 *
 * This is merely a book keeping call. It decrements the number of globally
 * reserved पूर्णांकerrupt bits. This is used to unकरो irq_matrix_reserve() when the
 * पूर्णांकerrupt was never in use and a real vector allocated, which undid the
 * reservation.
 */
व्योम irq_matrix_हटाओ_reserved(काष्ठा irq_matrix *m)
अणु
	m->global_reserved--;
	trace_irq_matrix_हटाओ_reserved(m);
पूर्ण

/**
 * irq_matrix_alloc - Allocate a regular पूर्णांकerrupt in a CPU map
 * @m:		Matrix poपूर्णांकer
 * @msk:	Which CPUs to search in
 * @reserved:	Allocate previously reserved पूर्णांकerrupts
 * @mapped_cpu: Poपूर्णांकer to store the CPU क्रम which the irq was allocated
 */
पूर्णांक irq_matrix_alloc(काष्ठा irq_matrix *m, स्थिर काष्ठा cpumask *msk,
		     bool reserved, अचिन्हित पूर्णांक *mapped_cpu)
अणु
	अचिन्हित पूर्णांक cpu, bit;
	काष्ठा cpumap *cm;

	/*
	 * Not required in theory, but matrix_find_best_cpu() uses
	 * क्रम_each_cpu() which ignores the cpumask on UP .
	 */
	अगर (cpumask_empty(msk))
		वापस -EINVAL;

	cpu = matrix_find_best_cpu(m, msk);
	अगर (cpu == अच_पूर्णांक_उच्च)
		वापस -ENOSPC;

	cm = per_cpu_ptr(m->maps, cpu);
	bit = matrix_alloc_area(m, cm, 1, false);
	अगर (bit >= m->alloc_end)
		वापस -ENOSPC;
	cm->allocated++;
	cm->available--;
	m->total_allocated++;
	m->global_available--;
	अगर (reserved)
		m->global_reserved--;
	*mapped_cpu = cpu;
	trace_irq_matrix_alloc(bit, cpu, m, cm);
	वापस bit;

पूर्ण

/**
 * irq_matrix_मुक्त - Free allocated पूर्णांकerrupt in the matrix
 * @m:		Matrix poपूर्णांकer
 * @cpu:	Which CPU map needs be updated
 * @bit:	The bit to हटाओ
 * @managed:	If true, the पूर्णांकerrupt is managed and not accounted
 *		as available.
 */
व्योम irq_matrix_मुक्त(काष्ठा irq_matrix *m, अचिन्हित पूर्णांक cpu,
		     अचिन्हित पूर्णांक bit, bool managed)
अणु
	काष्ठा cpumap *cm = per_cpu_ptr(m->maps, cpu);

	अगर (WARN_ON_ONCE(bit < m->alloc_start || bit >= m->alloc_end))
		वापस;

	अगर (WARN_ON_ONCE(!test_and_clear_bit(bit, cm->alloc_map)))
		वापस;

	cm->allocated--;
	अगर(managed)
		cm->managed_allocated--;

	अगर (cm->online)
		m->total_allocated--;

	अगर (!managed) अणु
		cm->available++;
		अगर (cm->online)
			m->global_available++;
	पूर्ण
	trace_irq_matrix_मुक्त(bit, cpu, m, cm);
पूर्ण

/**
 * irq_matrix_available - Get the number of globally available irqs
 * @m:		Poपूर्णांकer to the matrix to query
 * @cpuकरोwn:	If true, the local CPU is about to go करोwn, adjust
 *		the number of available irqs accordingly
 */
अचिन्हित पूर्णांक irq_matrix_available(काष्ठा irq_matrix *m, bool cpuकरोwn)
अणु
	काष्ठा cpumap *cm = this_cpu_ptr(m->maps);

	अगर (!cpuकरोwn)
		वापस m->global_available;
	वापस m->global_available - cm->available;
पूर्ण

/**
 * irq_matrix_reserved - Get the number of globally reserved irqs
 * @m:		Poपूर्णांकer to the matrix to query
 */
अचिन्हित पूर्णांक irq_matrix_reserved(काष्ठा irq_matrix *m)
अणु
	वापस m->global_reserved;
पूर्ण

/**
 * irq_matrix_allocated - Get the number of allocated irqs on the local cpu
 * @m:		Poपूर्णांकer to the matrix to search
 *
 * This वापसs number of allocated irqs
 */
अचिन्हित पूर्णांक irq_matrix_allocated(काष्ठा irq_matrix *m)
अणु
	काष्ठा cpumap *cm = this_cpu_ptr(m->maps);

	वापस cm->allocated;
पूर्ण

#अगर_घोषित CONFIG_GENERIC_IRQ_DEBUGFS
/**
 * irq_matrix_debug_show - Show detailed allocation inक्रमmation
 * @sf:		Poपूर्णांकer to the seq_file to prपूर्णांक to
 * @m:		Poपूर्णांकer to the matrix allocator
 * @ind:	Indentation क्रम the prपूर्णांक क्रमmat
 *
 * Note, this is a lockless snapshot.
 */
व्योम irq_matrix_debug_show(काष्ठा seq_file *sf, काष्ठा irq_matrix *m, पूर्णांक ind)
अणु
	अचिन्हित पूर्णांक nsys = biपंचांगap_weight(m->प्रणाली_map, m->matrix_bits);
	पूर्णांक cpu;

	seq_म_लिखो(sf, "Online bitmaps:   %6u\n", m->online_maps);
	seq_म_लिखो(sf, "Global available: %6u\n", m->global_available);
	seq_म_लिखो(sf, "Global reserved:  %6u\n", m->global_reserved);
	seq_म_लिखो(sf, "Total allocated:  %6u\n", m->total_allocated);
	seq_म_लिखो(sf, "System: %u: %*pbl\n", nsys, m->matrix_bits,
		   m->प्रणाली_map);
	seq_म_लिखो(sf, "%*s| CPU | avl | man | mac | act | vectors\n", ind, " ");
	cpus_पढ़ो_lock();
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा cpumap *cm = per_cpu_ptr(m->maps, cpu);

		seq_म_लिखो(sf, "%*s %4d  %4u  %4u  %4u %4u  %*pbl\n", ind, " ",
			   cpu, cm->available, cm->managed,
			   cm->managed_allocated, cm->allocated,
			   m->matrix_bits, cm->alloc_map);
	पूर्ण
	cpus_पढ़ो_unlock();
पूर्ण
#पूर्ण_अगर
