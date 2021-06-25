<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Fast and scalable biपंचांगaps.
 *
 * Copyright (C) 2016 Facebook
 * Copyright (C) 2013-2014 Jens Axboe
 */

#अगर_अघोषित __LINUX_SCALE_BITMAP_H
#घोषणा __LINUX_SCALE_BITMAP_H

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

काष्ठा seq_file;

/**
 * काष्ठा sbiपंचांगap_word - Word in a &काष्ठा sbiपंचांगap.
 */
काष्ठा sbiपंचांगap_word अणु
	/**
	 * @depth: Number of bits being used in @word/@cleared
	 */
	अचिन्हित दीर्घ depth;

	/**
	 * @word: word holding मुक्त bits
	 */
	अचिन्हित दीर्घ word ____cacheline_aligned_in_smp;

	/**
	 * @cleared: word holding cleared bits
	 */
	अचिन्हित दीर्घ cleared ____cacheline_aligned_in_smp;
पूर्ण ____cacheline_aligned_in_smp;

/**
 * काष्ठा sbiपंचांगap - Scalable biपंचांगap.
 *
 * A &काष्ठा sbiपंचांगap is spपढ़ो over multiple cachelines to aव्योम ping-pong. This
 * trades off higher memory usage क्रम better scalability.
 */
काष्ठा sbiपंचांगap अणु
	/**
	 * @depth: Number of bits used in the whole biपंचांगap.
	 */
	अचिन्हित पूर्णांक depth;

	/**
	 * @shअगरt: log2(number of bits used per word)
	 */
	अचिन्हित पूर्णांक shअगरt;

	/**
	 * @map_nr: Number of words (cachelines) being used क्रम the biपंचांगap.
	 */
	अचिन्हित पूर्णांक map_nr;

	/**
	 * @round_robin: Allocate bits in strict round-robin order.
	 */
	bool round_robin;

	/**
	 * @map: Allocated biपंचांगap.
	 */
	काष्ठा sbiपंचांगap_word *map;

	/*
	 * @alloc_hपूर्णांक: Cache of last successfully allocated or मुक्तd bit.
	 *
	 * This is per-cpu, which allows multiple users to stick to dअगरferent
	 * cachelines until the map is exhausted.
	 */
	अचिन्हित पूर्णांक __percpu *alloc_hपूर्णांक;
पूर्ण;

#घोषणा SBQ_WAIT_QUEUES 8
#घोषणा SBQ_WAKE_BATCH 8

/**
 * काष्ठा sbq_रुको_state - Wait queue in a &काष्ठा sbiपंचांगap_queue.
 */
काष्ठा sbq_रुको_state अणु
	/**
	 * @रुको_cnt: Number of मुक्तs reमुख्यing beक्रमe we wake up.
	 */
	atomic_t रुको_cnt;

	/**
	 * @रुको: Wait queue.
	 */
	रुको_queue_head_t रुको;
पूर्ण ____cacheline_aligned_in_smp;

/**
 * काष्ठा sbiपंचांगap_queue - Scalable biपंचांगap with the added ability to रुको on मुक्त
 * bits.
 *
 * A &काष्ठा sbiपंचांगap_queue uses multiple रुको queues and rolling wakeups to
 * aव्योम contention on the रुको queue spinlock. This ensures that we करोn't hit a
 * scalability wall when we run out of मुक्त bits and have to start putting tasks
 * to sleep.
 */
काष्ठा sbiपंचांगap_queue अणु
	/**
	 * @sb: Scalable biपंचांगap.
	 */
	काष्ठा sbiपंचांगap sb;

	/**
	 * @wake_batch: Number of bits which must be मुक्तd beक्रमe we wake up any
	 * रुकोers.
	 */
	अचिन्हित पूर्णांक wake_batch;

	/**
	 * @wake_index: Next रुको queue in @ws to wake up.
	 */
	atomic_t wake_index;

	/**
	 * @ws: Wait queues.
	 */
	काष्ठा sbq_रुको_state *ws;

	/*
	 * @ws_active: count of currently active ws रुकोqueues
	 */
	atomic_t ws_active;

	/**
	 * @min_shallow_depth: The minimum shallow depth which may be passed to
	 * sbiपंचांगap_queue_get_shallow() or __sbiपंचांगap_queue_get_shallow().
	 */
	अचिन्हित पूर्णांक min_shallow_depth;
पूर्ण;

/**
 * sbiपंचांगap_init_node() - Initialize a &काष्ठा sbiपंचांगap on a specअगरic memory node.
 * @sb: Biपंचांगap to initialize.
 * @depth: Number of bits to allocate.
 * @shअगरt: Use 2^@shअगरt bits per word in the biपंचांगap; अगर a negative number अगर
 *         given, a good शेष is chosen.
 * @flags: Allocation flags.
 * @node: Memory node to allocate on.
 * @round_robin: If true, be stricter about allocation order; always allocate
 *               starting from the last allocated bit. This is less efficient
 *               than the शेष behavior (false).
 * @alloc_hपूर्णांक: If true, apply percpu hपूर्णांक क्रम where to start searching क्रम
 *              a मुक्त bit.
 *
 * Return: Zero on success or negative त्रुटि_सं on failure.
 */
पूर्णांक sbiपंचांगap_init_node(काष्ठा sbiपंचांगap *sb, अचिन्हित पूर्णांक depth, पूर्णांक shअगरt,
		      gfp_t flags, पूर्णांक node, bool round_robin, bool alloc_hपूर्णांक);

/**
 * sbiपंचांगap_मुक्त() - Free memory used by a &काष्ठा sbiपंचांगap.
 * @sb: Biपंचांगap to मुक्त.
 */
अटल अंतरभूत व्योम sbiपंचांगap_मुक्त(काष्ठा sbiपंचांगap *sb)
अणु
	मुक्त_percpu(sb->alloc_hपूर्णांक);
	kमुक्त(sb->map);
	sb->map = शून्य;
पूर्ण

/**
 * sbiपंचांगap_resize() - Resize a &काष्ठा sbiपंचांगap.
 * @sb: Biपंचांगap to resize.
 * @depth: New number of bits to resize to.
 *
 * Doesn't reallocate anything. It's up to the caller to ensure that the new
 * depth करोesn't exceed the depth that the sb was initialized with.
 */
व्योम sbiपंचांगap_resize(काष्ठा sbiपंचांगap *sb, अचिन्हित पूर्णांक depth);

/**
 * sbiपंचांगap_get() - Try to allocate a मुक्त bit from a &काष्ठा sbiपंचांगap.
 * @sb: Biपंचांगap to allocate from.
 *
 * This operation provides acquire barrier semantics अगर it succeeds.
 *
 * Return: Non-negative allocated bit number अगर successful, -1 otherwise.
 */
पूर्णांक sbiपंचांगap_get(काष्ठा sbiपंचांगap *sb);

/**
 * sbiपंचांगap_get_shallow() - Try to allocate a मुक्त bit from a &काष्ठा sbiपंचांगap,
 * limiting the depth used from each word.
 * @sb: Biपंचांगap to allocate from.
 * @shallow_depth: The maximum number of bits to allocate from a single word.
 *
 * This rather specअगरic operation allows क्रम having multiple users with
 * dअगरferent allocation limits. E.g., there can be a high-priority class that
 * uses sbiपंचांगap_get() and a low-priority class that uses sbiपंचांगap_get_shallow()
 * with a @shallow_depth of (1 << (@sb->shअगरt - 1)). Then, the low-priority
 * class can only allocate half of the total bits in the biपंचांगap, preventing it
 * from starving out the high-priority class.
 *
 * Return: Non-negative allocated bit number अगर successful, -1 otherwise.
 */
पूर्णांक sbiपंचांगap_get_shallow(काष्ठा sbiपंचांगap *sb, अचिन्हित दीर्घ shallow_depth);

/**
 * sbiपंचांगap_any_bit_set() - Check क्रम a set bit in a &काष्ठा sbiपंचांगap.
 * @sb: Biपंचांगap to check.
 *
 * Return: true अगर any bit in the biपंचांगap is set, false otherwise.
 */
bool sbiपंचांगap_any_bit_set(स्थिर काष्ठा sbiपंचांगap *sb);

#घोषणा SB_NR_TO_INDEX(sb, bitnr) ((bitnr) >> (sb)->shअगरt)
#घोषणा SB_NR_TO_BIT(sb, bitnr) ((bitnr) & ((1U << (sb)->shअगरt) - 1U))

प्रकार bool (*sb_क्रम_each_fn)(काष्ठा sbiपंचांगap *, अचिन्हित पूर्णांक, व्योम *);

/**
 * __sbiपंचांगap_क्रम_each_set() - Iterate over each set bit in a &काष्ठा sbiपंचांगap.
 * @start: Where to start the iteration.
 * @sb: Biपंचांगap to iterate over.
 * @fn: Callback. Should वापस true to जारी or false to अवरोध early.
 * @data: Poपूर्णांकer to pass to callback.
 *
 * This is अंतरभूत even though it's non-trivial so that the function calls to the
 * callback will hopefully get optimized away.
 */
अटल अंतरभूत व्योम __sbiपंचांगap_क्रम_each_set(काष्ठा sbiपंचांगap *sb,
					  अचिन्हित पूर्णांक start,
					  sb_क्रम_each_fn fn, व्योम *data)
अणु
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक nr;
	अचिन्हित पूर्णांक scanned = 0;

	अगर (start >= sb->depth)
		start = 0;
	index = SB_NR_TO_INDEX(sb, start);
	nr = SB_NR_TO_BIT(sb, start);

	जबतक (scanned < sb->depth) अणु
		अचिन्हित दीर्घ word;
		अचिन्हित पूर्णांक depth = min_t(अचिन्हित पूर्णांक,
					   sb->map[index].depth - nr,
					   sb->depth - scanned);

		scanned += depth;
		word = sb->map[index].word & ~sb->map[index].cleared;
		अगर (!word)
			जाओ next;

		/*
		 * On the first iteration of the outer loop, we need to add the
		 * bit offset back to the size of the word क्रम find_next_bit().
		 * On all other iterations, nr is zero, so this is a noop.
		 */
		depth += nr;
		जबतक (1) अणु
			nr = find_next_bit(&word, depth, nr);
			अगर (nr >= depth)
				अवरोध;
			अगर (!fn(sb, (index << sb->shअगरt) + nr, data))
				वापस;

			nr++;
		पूर्ण
next:
		nr = 0;
		अगर (++index >= sb->map_nr)
			index = 0;
	पूर्ण
पूर्ण

/**
 * sbiपंचांगap_क्रम_each_set() - Iterate over each set bit in a &काष्ठा sbiपंचांगap.
 * @sb: Biपंचांगap to iterate over.
 * @fn: Callback. Should वापस true to जारी or false to अवरोध early.
 * @data: Poपूर्णांकer to pass to callback.
 */
अटल अंतरभूत व्योम sbiपंचांगap_क्रम_each_set(काष्ठा sbiपंचांगap *sb, sb_क्रम_each_fn fn,
					व्योम *data)
अणु
	__sbiपंचांगap_क्रम_each_set(sb, 0, fn, data);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *__sbiपंचांगap_word(काष्ठा sbiपंचांगap *sb,
					    अचिन्हित पूर्णांक bitnr)
अणु
	वापस &sb->map[SB_NR_TO_INDEX(sb, bitnr)].word;
पूर्ण

/* Helpers equivalent to the operations in यंत्र/bitops.h and linux/biपंचांगap.h */

अटल अंतरभूत व्योम sbiपंचांगap_set_bit(काष्ठा sbiपंचांगap *sb, अचिन्हित पूर्णांक bitnr)
अणु
	set_bit(SB_NR_TO_BIT(sb, bitnr), __sbiपंचांगap_word(sb, bitnr));
पूर्ण

अटल अंतरभूत व्योम sbiपंचांगap_clear_bit(काष्ठा sbiपंचांगap *sb, अचिन्हित पूर्णांक bitnr)
अणु
	clear_bit(SB_NR_TO_BIT(sb, bitnr), __sbiपंचांगap_word(sb, bitnr));
पूर्ण

/*
 * This one is special, since it करोesn't actually clear the bit, rather it
 * sets the corresponding bit in the ->cleared mask instead. Paired with
 * the caller करोing sbiपंचांगap_deferred_clear() अगर a given index is full, which
 * will clear the previously मुक्तd entries in the corresponding ->word.
 */
अटल अंतरभूत व्योम sbiपंचांगap_deferred_clear_bit(काष्ठा sbiपंचांगap *sb, अचिन्हित पूर्णांक bitnr)
अणु
	अचिन्हित दीर्घ *addr = &sb->map[SB_NR_TO_INDEX(sb, bitnr)].cleared;

	set_bit(SB_NR_TO_BIT(sb, bitnr), addr);
पूर्ण

/*
 * Pair of sbiपंचांगap_get, and this one applies both cleared bit and
 * allocation hपूर्णांक.
 */
अटल अंतरभूत व्योम sbiपंचांगap_put(काष्ठा sbiपंचांगap *sb, अचिन्हित पूर्णांक bitnr)
अणु
	sbiपंचांगap_deferred_clear_bit(sb, bitnr);

	अगर (likely(sb->alloc_hपूर्णांक && !sb->round_robin && bitnr < sb->depth))
		*raw_cpu_ptr(sb->alloc_hपूर्णांक) = bitnr;
पूर्ण

अटल अंतरभूत पूर्णांक sbiपंचांगap_test_bit(काष्ठा sbiपंचांगap *sb, अचिन्हित पूर्णांक bitnr)
अणु
	वापस test_bit(SB_NR_TO_BIT(sb, bitnr), __sbiपंचांगap_word(sb, bitnr));
पूर्ण

अटल अंतरभूत पूर्णांक sbiपंचांगap_calculate_shअगरt(अचिन्हित पूर्णांक depth)
अणु
	पूर्णांक	shअगरt = ilog2(BITS_PER_LONG);

	/*
	 * If the biपंचांगap is small, shrink the number of bits per word so
	 * we spपढ़ो over a few cachelines, at least. If less than 4
	 * bits, just क्रमget about it, it's not going to work optimally
	 * anyway.
	 */
	अगर (depth >= 4) अणु
		जबतक ((4U << shअगरt) > depth)
			shअगरt--;
	पूर्ण

	वापस shअगरt;
पूर्ण

/**
 * sbiपंचांगap_show() - Dump &काष्ठा sbiपंचांगap inक्रमmation to a &काष्ठा seq_file.
 * @sb: Biपंचांगap to show.
 * @m: काष्ठा seq_file to ग_लिखो to.
 *
 * This is पूर्णांकended क्रम debugging. The क्रमmat may change at any समय.
 */
व्योम sbiपंचांगap_show(काष्ठा sbiपंचांगap *sb, काष्ठा seq_file *m);


/**
 * sbiपंचांगap_weight() - Return how many set and not cleared bits in a &काष्ठा
 * sbiपंचांगap.
 * @sb: Biपंचांगap to check.
 *
 * Return: How many set and not cleared bits set
 */
अचिन्हित पूर्णांक sbiपंचांगap_weight(स्थिर काष्ठा sbiपंचांगap *sb);

/**
 * sbiपंचांगap_biपंचांगap_show() - Write a hex dump of a &काष्ठा sbiपंचांगap to a &काष्ठा
 * seq_file.
 * @sb: Biपंचांगap to show.
 * @m: काष्ठा seq_file to ग_लिखो to.
 *
 * This is पूर्णांकended क्रम debugging. The output isn't guaranteed to be पूर्णांकernally
 * consistent.
 */
व्योम sbiपंचांगap_biपंचांगap_show(काष्ठा sbiपंचांगap *sb, काष्ठा seq_file *m);

/**
 * sbiपंचांगap_queue_init_node() - Initialize a &काष्ठा sbiपंचांगap_queue on a specअगरic
 * memory node.
 * @sbq: Biपंचांगap queue to initialize.
 * @depth: See sbiपंचांगap_init_node().
 * @shअगरt: See sbiपंचांगap_init_node().
 * @round_robin: See sbiपंचांगap_get().
 * @flags: Allocation flags.
 * @node: Memory node to allocate on.
 *
 * Return: Zero on success or negative त्रुटि_सं on failure.
 */
पूर्णांक sbiपंचांगap_queue_init_node(काष्ठा sbiपंचांगap_queue *sbq, अचिन्हित पूर्णांक depth,
			    पूर्णांक shअगरt, bool round_robin, gfp_t flags, पूर्णांक node);

/**
 * sbiपंचांगap_queue_मुक्त() - Free memory used by a &काष्ठा sbiपंचांगap_queue.
 *
 * @sbq: Biपंचांगap queue to मुक्त.
 */
अटल अंतरभूत व्योम sbiपंचांगap_queue_मुक्त(काष्ठा sbiपंचांगap_queue *sbq)
अणु
	kमुक्त(sbq->ws);
	sbiपंचांगap_मुक्त(&sbq->sb);
पूर्ण

/**
 * sbiपंचांगap_queue_resize() - Resize a &काष्ठा sbiपंचांगap_queue.
 * @sbq: Biपंचांगap queue to resize.
 * @depth: New number of bits to resize to.
 *
 * Like sbiपंचांगap_resize(), this करोesn't पुनः_स्मृतिate anything. It has to करो
 * some extra work on the &काष्ठा sbiपंचांगap_queue, so it's not safe to just
 * resize the underlying &काष्ठा sbiपंचांगap.
 */
व्योम sbiपंचांगap_queue_resize(काष्ठा sbiपंचांगap_queue *sbq, अचिन्हित पूर्णांक depth);

/**
 * __sbiपंचांगap_queue_get() - Try to allocate a मुक्त bit from a &काष्ठा
 * sbiपंचांगap_queue with preemption alपढ़ोy disabled.
 * @sbq: Biपंचांगap queue to allocate from.
 *
 * Return: Non-negative allocated bit number अगर successful, -1 otherwise.
 */
पूर्णांक __sbiपंचांगap_queue_get(काष्ठा sbiपंचांगap_queue *sbq);

/**
 * __sbiपंचांगap_queue_get_shallow() - Try to allocate a मुक्त bit from a &काष्ठा
 * sbiपंचांगap_queue, limiting the depth used from each word, with preemption
 * alपढ़ोy disabled.
 * @sbq: Biपंचांगap queue to allocate from.
 * @shallow_depth: The maximum number of bits to allocate from a single word.
 * See sbiपंचांगap_get_shallow().
 *
 * If you call this, make sure to call sbiपंचांगap_queue_min_shallow_depth() after
 * initializing @sbq.
 *
 * Return: Non-negative allocated bit number अगर successful, -1 otherwise.
 */
पूर्णांक __sbiपंचांगap_queue_get_shallow(काष्ठा sbiपंचांगap_queue *sbq,
				अचिन्हित पूर्णांक shallow_depth);

/**
 * sbiपंचांगap_queue_get() - Try to allocate a मुक्त bit from a &काष्ठा
 * sbiपंचांगap_queue.
 * @sbq: Biपंचांगap queue to allocate from.
 * @cpu: Output parameter; will contain the CPU we ran on (e.g., to be passed to
 *       sbiपंचांगap_queue_clear()).
 *
 * Return: Non-negative allocated bit number अगर successful, -1 otherwise.
 */
अटल अंतरभूत पूर्णांक sbiपंचांगap_queue_get(काष्ठा sbiपंचांगap_queue *sbq,
				    अचिन्हित पूर्णांक *cpu)
अणु
	पूर्णांक nr;

	*cpu = get_cpu();
	nr = __sbiपंचांगap_queue_get(sbq);
	put_cpu();
	वापस nr;
पूर्ण

/**
 * sbiपंचांगap_queue_get_shallow() - Try to allocate a मुक्त bit from a &काष्ठा
 * sbiपंचांगap_queue, limiting the depth used from each word.
 * @sbq: Biपंचांगap queue to allocate from.
 * @cpu: Output parameter; will contain the CPU we ran on (e.g., to be passed to
 *       sbiपंचांगap_queue_clear()).
 * @shallow_depth: The maximum number of bits to allocate from a single word.
 * See sbiपंचांगap_get_shallow().
 *
 * If you call this, make sure to call sbiपंचांगap_queue_min_shallow_depth() after
 * initializing @sbq.
 *
 * Return: Non-negative allocated bit number अगर successful, -1 otherwise.
 */
अटल अंतरभूत पूर्णांक sbiपंचांगap_queue_get_shallow(काष्ठा sbiपंचांगap_queue *sbq,
					    अचिन्हित पूर्णांक *cpu,
					    अचिन्हित पूर्णांक shallow_depth)
अणु
	पूर्णांक nr;

	*cpu = get_cpu();
	nr = __sbiपंचांगap_queue_get_shallow(sbq, shallow_depth);
	put_cpu();
	वापस nr;
पूर्ण

/**
 * sbiपंचांगap_queue_min_shallow_depth() - Inक्रमm a &काष्ठा sbiपंचांगap_queue of the
 * minimum shallow depth that will be used.
 * @sbq: Biपंचांगap queue in question.
 * @min_shallow_depth: The minimum shallow depth that will be passed to
 * sbiपंचांगap_queue_get_shallow() or __sbiपंचांगap_queue_get_shallow().
 *
 * sbiपंचांगap_queue_clear() batches wakeups as an optimization. The batch size
 * depends on the depth of the biपंचांगap. Since the shallow allocation functions
 * effectively operate with a dअगरferent depth, the shallow depth must be taken
 * पूर्णांकo account when calculating the batch size. This function must be called
 * with the minimum shallow depth that will be used. Failure to करो so can result
 * in missed wakeups.
 */
व्योम sbiपंचांगap_queue_min_shallow_depth(काष्ठा sbiपंचांगap_queue *sbq,
				     अचिन्हित पूर्णांक min_shallow_depth);

/**
 * sbiपंचांगap_queue_clear() - Free an allocated bit and wake up रुकोers on a
 * &काष्ठा sbiपंचांगap_queue.
 * @sbq: Biपंचांगap to मुक्त from.
 * @nr: Bit number to मुक्त.
 * @cpu: CPU the bit was allocated on.
 */
व्योम sbiपंचांगap_queue_clear(काष्ठा sbiपंचांगap_queue *sbq, अचिन्हित पूर्णांक nr,
			 अचिन्हित पूर्णांक cpu);

अटल अंतरभूत पूर्णांक sbq_index_inc(पूर्णांक index)
अणु
	वापस (index + 1) & (SBQ_WAIT_QUEUES - 1);
पूर्ण

अटल अंतरभूत व्योम sbq_index_atomic_inc(atomic_t *index)
अणु
	पूर्णांक old = atomic_पढ़ो(index);
	पूर्णांक new = sbq_index_inc(old);
	atomic_cmpxchg(index, old, new);
पूर्ण

/**
 * sbq_रुको_ptr() - Get the next रुको queue to use क्रम a &काष्ठा
 * sbiपंचांगap_queue.
 * @sbq: Biपंचांगap queue to रुको on.
 * @रुको_index: A counter per "user" of @sbq.
 */
अटल अंतरभूत काष्ठा sbq_रुको_state *sbq_रुको_ptr(काष्ठा sbiपंचांगap_queue *sbq,
						  atomic_t *रुको_index)
अणु
	काष्ठा sbq_रुको_state *ws;

	ws = &sbq->ws[atomic_पढ़ो(रुको_index)];
	sbq_index_atomic_inc(रुको_index);
	वापस ws;
पूर्ण

/**
 * sbiपंचांगap_queue_wake_all() - Wake up everything रुकोing on a &काष्ठा
 * sbiपंचांगap_queue.
 * @sbq: Biपंचांगap queue to wake up.
 */
व्योम sbiपंचांगap_queue_wake_all(काष्ठा sbiपंचांगap_queue *sbq);

/**
 * sbiपंचांगap_queue_wake_up() - Wake up some of रुकोers in one रुकोqueue
 * on a &काष्ठा sbiपंचांगap_queue.
 * @sbq: Biपंचांगap queue to wake up.
 */
व्योम sbiपंचांगap_queue_wake_up(काष्ठा sbiपंचांगap_queue *sbq);

/**
 * sbiपंचांगap_queue_show() - Dump &काष्ठा sbiपंचांगap_queue inक्रमmation to a &काष्ठा
 * seq_file.
 * @sbq: Biपंचांगap queue to show.
 * @m: काष्ठा seq_file to ग_लिखो to.
 *
 * This is पूर्णांकended क्रम debugging. The क्रमmat may change at any समय.
 */
व्योम sbiपंचांगap_queue_show(काष्ठा sbiपंचांगap_queue *sbq, काष्ठा seq_file *m);

काष्ठा sbq_रुको अणु
	काष्ठा sbiपंचांगap_queue *sbq;	/* अगर set, sbq_रुको is accounted */
	काष्ठा रुको_queue_entry रुको;
पूर्ण;

#घोषणा DEFINE_SBQ_WAIT(name)							\
	काष्ठा sbq_रुको name = अणु						\
		.sbq = शून्य,							\
		.रुको = अणु							\
			.निजी	= current,				\
			.func		= स्वतःहटाओ_wake_function,		\
			.entry		= LIST_HEAD_INIT((name).रुको.entry),	\
		पूर्ण								\
	पूर्ण

/*
 * Wrapper around prepare_to_रुको_exclusive(), which मुख्यtains some extra
 * पूर्णांकernal state.
 */
व्योम sbiपंचांगap_prepare_to_रुको(काष्ठा sbiपंचांगap_queue *sbq,
				काष्ठा sbq_रुको_state *ws,
				काष्ठा sbq_रुको *sbq_रुको, पूर्णांक state);

/*
 * Must be paired with sbiपंचांगap_prepare_to_रुको().
 */
व्योम sbiपंचांगap_finish_रुको(काष्ठा sbiपंचांगap_queue *sbq, काष्ठा sbq_रुको_state *ws,
				काष्ठा sbq_रुको *sbq_रुको);

/*
 * Wrapper around add_रुको_queue(), which मुख्यtains some extra पूर्णांकernal state
 */
व्योम sbiपंचांगap_add_रुको_queue(काष्ठा sbiपंचांगap_queue *sbq,
			    काष्ठा sbq_रुको_state *ws,
			    काष्ठा sbq_रुको *sbq_रुको);

/*
 * Must be paired with sbiपंचांगap_add_रुको_queue()
 */
व्योम sbiपंचांगap_del_रुको_queue(काष्ठा sbq_रुको *sbq_रुको);

#पूर्ण_अगर /* __LINUX_SCALE_BITMAP_H */
