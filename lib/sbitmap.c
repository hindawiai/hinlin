<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Facebook
 * Copyright (C) 2013-2014 Jens Axboe
 */

#समावेश <linux/sched.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sbiपंचांगap.h>
#समावेश <linux/seq_file.h>

अटल पूर्णांक init_alloc_hपूर्णांक(काष्ठा sbiपंचांगap *sb, gfp_t flags)
अणु
	अचिन्हित depth = sb->depth;

	sb->alloc_hपूर्णांक = alloc_percpu_gfp(अचिन्हित पूर्णांक, flags);
	अगर (!sb->alloc_hपूर्णांक)
		वापस -ENOMEM;

	अगर (depth && !sb->round_robin) अणु
		पूर्णांक i;

		क्रम_each_possible_cpu(i)
			*per_cpu_ptr(sb->alloc_hपूर्णांक, i) = pअक्रमom_u32() % depth;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित update_alloc_hपूर्णांक_beक्रमe_get(काष्ठा sbiपंचांगap *sb,
						    अचिन्हित पूर्णांक depth)
अणु
	अचिन्हित hपूर्णांक;

	hपूर्णांक = this_cpu_पढ़ो(*sb->alloc_hपूर्णांक);
	अगर (unlikely(hपूर्णांक >= depth)) अणु
		hपूर्णांक = depth ? pअक्रमom_u32() % depth : 0;
		this_cpu_ग_लिखो(*sb->alloc_hपूर्णांक, hपूर्णांक);
	पूर्ण

	वापस hपूर्णांक;
पूर्ण

अटल अंतरभूत व्योम update_alloc_hपूर्णांक_after_get(काष्ठा sbiपंचांगap *sb,
					       अचिन्हित पूर्णांक depth,
					       अचिन्हित पूर्णांक hपूर्णांक,
					       अचिन्हित पूर्णांक nr)
अणु
	अगर (nr == -1) अणु
		/* If the map is full, a hपूर्णांक won't करो us much good. */
		this_cpu_ग_लिखो(*sb->alloc_hपूर्णांक, 0);
	पूर्ण अन्यथा अगर (nr == hपूर्णांक || unlikely(sb->round_robin)) अणु
		/* Only update the hपूर्णांक अगर we used it. */
		hपूर्णांक = nr + 1;
		अगर (hपूर्णांक >= depth - 1)
			hपूर्णांक = 0;
		this_cpu_ग_लिखो(*sb->alloc_hपूर्णांक, hपूर्णांक);
	पूर्ण
पूर्ण

/*
 * See अगर we have deferred clears that we can batch move
 */
अटल अंतरभूत bool sbiपंचांगap_deferred_clear(काष्ठा sbiपंचांगap_word *map)
अणु
	अचिन्हित दीर्घ mask;

	अगर (!READ_ONCE(map->cleared))
		वापस false;

	/*
	 * First get a stable cleared mask, setting the old mask to 0.
	 */
	mask = xchg(&map->cleared, 0);

	/*
	 * Now clear the masked bits in our मुक्त word
	 */
	atomic_दीर्घ_andnot(mask, (atomic_दीर्घ_t *)&map->word);
	BUILD_BUG_ON(माप(atomic_दीर्घ_t) != माप(map->word));
	वापस true;
पूर्ण

पूर्णांक sbiपंचांगap_init_node(काष्ठा sbiपंचांगap *sb, अचिन्हित पूर्णांक depth, पूर्णांक shअगरt,
		      gfp_t flags, पूर्णांक node, bool round_robin,
		      bool alloc_hपूर्णांक)
अणु
	अचिन्हित पूर्णांक bits_per_word;
	अचिन्हित पूर्णांक i;

	अगर (shअगरt < 0)
		shअगरt = sbiपंचांगap_calculate_shअगरt(depth);

	bits_per_word = 1U << shअगरt;
	अगर (bits_per_word > BITS_PER_LONG)
		वापस -EINVAL;

	sb->shअगरt = shअगरt;
	sb->depth = depth;
	sb->map_nr = DIV_ROUND_UP(sb->depth, bits_per_word);
	sb->round_robin = round_robin;

	अगर (depth == 0) अणु
		sb->map = शून्य;
		वापस 0;
	पूर्ण

	अगर (alloc_hपूर्णांक) अणु
		अगर (init_alloc_hपूर्णांक(sb, flags))
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		sb->alloc_hपूर्णांक = शून्य;
	पूर्ण

	sb->map = kसुस्मृति_node(sb->map_nr, माप(*sb->map), flags, node);
	अगर (!sb->map) अणु
		मुक्त_percpu(sb->alloc_hपूर्णांक);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < sb->map_nr; i++) अणु
		sb->map[i].depth = min(depth, bits_per_word);
		depth -= sb->map[i].depth;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_init_node);

व्योम sbiपंचांगap_resize(काष्ठा sbiपंचांगap *sb, अचिन्हित पूर्णांक depth)
अणु
	अचिन्हित पूर्णांक bits_per_word = 1U << sb->shअगरt;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < sb->map_nr; i++)
		sbiपंचांगap_deferred_clear(&sb->map[i]);

	sb->depth = depth;
	sb->map_nr = DIV_ROUND_UP(sb->depth, bits_per_word);

	क्रम (i = 0; i < sb->map_nr; i++) अणु
		sb->map[i].depth = min(depth, bits_per_word);
		depth -= sb->map[i].depth;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_resize);

अटल पूर्णांक __sbiपंचांगap_get_word(अचिन्हित दीर्घ *word, अचिन्हित दीर्घ depth,
			      अचिन्हित पूर्णांक hपूर्णांक, bool wrap)
अणु
	पूर्णांक nr;

	/* करोn't wrap अगर starting from 0 */
	wrap = wrap && hपूर्णांक;

	जबतक (1) अणु
		nr = find_next_zero_bit(word, depth, hपूर्णांक);
		अगर (unlikely(nr >= depth)) अणु
			/*
			 * We started with an offset, and we didn't reset the
			 * offset to 0 in a failure हाल, so start from 0 to
			 * exhaust the map.
			 */
			अगर (hपूर्णांक && wrap) अणु
				hपूर्णांक = 0;
				जारी;
			पूर्ण
			वापस -1;
		पूर्ण

		अगर (!test_and_set_bit_lock(nr, word))
			अवरोध;

		hपूर्णांक = nr + 1;
		अगर (hपूर्णांक >= depth - 1)
			hपूर्णांक = 0;
	पूर्ण

	वापस nr;
पूर्ण

अटल पूर्णांक sbiपंचांगap_find_bit_in_index(काष्ठा sbiपंचांगap *sb, पूर्णांक index,
				     अचिन्हित पूर्णांक alloc_hपूर्णांक)
अणु
	काष्ठा sbiपंचांगap_word *map = &sb->map[index];
	पूर्णांक nr;

	करो अणु
		nr = __sbiपंचांगap_get_word(&map->word, map->depth, alloc_hपूर्णांक,
					!sb->round_robin);
		अगर (nr != -1)
			अवरोध;
		अगर (!sbiपंचांगap_deferred_clear(map))
			अवरोध;
	पूर्ण जबतक (1);

	वापस nr;
पूर्ण

अटल पूर्णांक __sbiपंचांगap_get(काष्ठा sbiपंचांगap *sb, अचिन्हित पूर्णांक alloc_hपूर्णांक)
अणु
	अचिन्हित पूर्णांक i, index;
	पूर्णांक nr = -1;

	index = SB_NR_TO_INDEX(sb, alloc_hपूर्णांक);

	/*
	 * Unless we're करोing round robin tag allocation, just use the
	 * alloc_hपूर्णांक to find the right word index. No poपूर्णांक in looping
	 * twice in find_next_zero_bit() क्रम that हाल.
	 */
	अगर (sb->round_robin)
		alloc_hपूर्णांक = SB_NR_TO_BIT(sb, alloc_hपूर्णांक);
	अन्यथा
		alloc_hपूर्णांक = 0;

	क्रम (i = 0; i < sb->map_nr; i++) अणु
		nr = sbiपंचांगap_find_bit_in_index(sb, index, alloc_hपूर्णांक);
		अगर (nr != -1) अणु
			nr += index << sb->shअगरt;
			अवरोध;
		पूर्ण

		/* Jump to next index. */
		alloc_hपूर्णांक = 0;
		अगर (++index >= sb->map_nr)
			index = 0;
	पूर्ण

	वापस nr;
पूर्ण

पूर्णांक sbiपंचांगap_get(काष्ठा sbiपंचांगap *sb)
अणु
	पूर्णांक nr;
	अचिन्हित पूर्णांक hपूर्णांक, depth;

	अगर (WARN_ON_ONCE(unlikely(!sb->alloc_hपूर्णांक)))
		वापस -1;

	depth = READ_ONCE(sb->depth);
	hपूर्णांक = update_alloc_hपूर्णांक_beक्रमe_get(sb, depth);
	nr = __sbiपंचांगap_get(sb, hपूर्णांक);
	update_alloc_hपूर्णांक_after_get(sb, depth, hपूर्णांक, nr);

	वापस nr;
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_get);

अटल पूर्णांक __sbiपंचांगap_get_shallow(काष्ठा sbiपंचांगap *sb,
				 अचिन्हित पूर्णांक alloc_hपूर्णांक,
				 अचिन्हित दीर्घ shallow_depth)
अणु
	अचिन्हित पूर्णांक i, index;
	पूर्णांक nr = -1;

	index = SB_NR_TO_INDEX(sb, alloc_hपूर्णांक);

	क्रम (i = 0; i < sb->map_nr; i++) अणु
again:
		nr = __sbiपंचांगap_get_word(&sb->map[index].word,
					min(sb->map[index].depth, shallow_depth),
					SB_NR_TO_BIT(sb, alloc_hपूर्णांक), true);
		अगर (nr != -1) अणु
			nr += index << sb->shअगरt;
			अवरोध;
		पूर्ण

		अगर (sbiपंचांगap_deferred_clear(&sb->map[index]))
			जाओ again;

		/* Jump to next index. */
		index++;
		alloc_hपूर्णांक = index << sb->shअगरt;

		अगर (index >= sb->map_nr) अणु
			index = 0;
			alloc_hपूर्णांक = 0;
		पूर्ण
	पूर्ण

	वापस nr;
पूर्ण

पूर्णांक sbiपंचांगap_get_shallow(काष्ठा sbiपंचांगap *sb, अचिन्हित दीर्घ shallow_depth)
अणु
	पूर्णांक nr;
	अचिन्हित पूर्णांक hपूर्णांक, depth;

	अगर (WARN_ON_ONCE(unlikely(!sb->alloc_hपूर्णांक)))
		वापस -1;

	depth = READ_ONCE(sb->depth);
	hपूर्णांक = update_alloc_hपूर्णांक_beक्रमe_get(sb, depth);
	nr = __sbiपंचांगap_get_shallow(sb, hपूर्णांक, shallow_depth);
	update_alloc_hपूर्णांक_after_get(sb, depth, hपूर्णांक, nr);

	वापस nr;
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_get_shallow);

bool sbiपंचांगap_any_bit_set(स्थिर काष्ठा sbiपंचांगap *sb)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < sb->map_nr; i++) अणु
		अगर (sb->map[i].word & ~sb->map[i].cleared)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_any_bit_set);

अटल अचिन्हित पूर्णांक __sbiपंचांगap_weight(स्थिर काष्ठा sbiपंचांगap *sb, bool set)
अणु
	अचिन्हित पूर्णांक i, weight = 0;

	क्रम (i = 0; i < sb->map_nr; i++) अणु
		स्थिर काष्ठा sbiपंचांगap_word *word = &sb->map[i];

		अगर (set)
			weight += biपंचांगap_weight(&word->word, word->depth);
		अन्यथा
			weight += biपंचांगap_weight(&word->cleared, word->depth);
	पूर्ण
	वापस weight;
पूर्ण

अटल अचिन्हित पूर्णांक sbiपंचांगap_cleared(स्थिर काष्ठा sbiपंचांगap *sb)
अणु
	वापस __sbiपंचांगap_weight(sb, false);
पूर्ण

अचिन्हित पूर्णांक sbiपंचांगap_weight(स्थिर काष्ठा sbiपंचांगap *sb)
अणु
	वापस __sbiपंचांगap_weight(sb, true) - sbiपंचांगap_cleared(sb);
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_weight);

व्योम sbiपंचांगap_show(काष्ठा sbiपंचांगap *sb, काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "depth=%u\n", sb->depth);
	seq_म_लिखो(m, "busy=%u\n", sbiपंचांगap_weight(sb));
	seq_म_लिखो(m, "cleared=%u\n", sbiपंचांगap_cleared(sb));
	seq_म_लिखो(m, "bits_per_word=%u\n", 1U << sb->shअगरt);
	seq_म_लिखो(m, "map_nr=%u\n", sb->map_nr);
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_show);

अटल अंतरभूत व्योम emit_byte(काष्ठा seq_file *m, अचिन्हित पूर्णांक offset, u8 byte)
अणु
	अगर ((offset & 0xf) == 0) अणु
		अगर (offset != 0)
			seq_अ_दो(m, '\n');
		seq_म_लिखो(m, "%08x:", offset);
	पूर्ण
	अगर ((offset & 0x1) == 0)
		seq_अ_दो(m, ' ');
	seq_म_लिखो(m, "%02x", byte);
पूर्ण

व्योम sbiपंचांगap_biपंचांगap_show(काष्ठा sbiपंचांगap *sb, काष्ठा seq_file *m)
अणु
	u8 byte = 0;
	अचिन्हित पूर्णांक byte_bits = 0;
	अचिन्हित पूर्णांक offset = 0;
	पूर्णांक i;

	क्रम (i = 0; i < sb->map_nr; i++) अणु
		अचिन्हित दीर्घ word = READ_ONCE(sb->map[i].word);
		अचिन्हित दीर्घ cleared = READ_ONCE(sb->map[i].cleared);
		अचिन्हित पूर्णांक word_bits = READ_ONCE(sb->map[i].depth);

		word &= ~cleared;

		जबतक (word_bits > 0) अणु
			अचिन्हित पूर्णांक bits = min(8 - byte_bits, word_bits);

			byte |= (word & (BIT(bits) - 1)) << byte_bits;
			byte_bits += bits;
			अगर (byte_bits == 8) अणु
				emit_byte(m, offset, byte);
				byte = 0;
				byte_bits = 0;
				offset++;
			पूर्ण
			word >>= bits;
			word_bits -= bits;
		पूर्ण
	पूर्ण
	अगर (byte_bits) अणु
		emit_byte(m, offset, byte);
		offset++;
	पूर्ण
	अगर (offset)
		seq_अ_दो(m, '\n');
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_biपंचांगap_show);

अटल अचिन्हित पूर्णांक sbq_calc_wake_batch(काष्ठा sbiपंचांगap_queue *sbq,
					अचिन्हित पूर्णांक depth)
अणु
	अचिन्हित पूर्णांक wake_batch;
	अचिन्हित पूर्णांक shallow_depth;

	/*
	 * For each batch, we wake up one queue. We need to make sure that our
	 * batch size is small enough that the full depth of the biपंचांगap,
	 * potentially limited by a shallow depth, is enough to wake up all of
	 * the queues.
	 *
	 * Each full word of the biपंचांगap has bits_per_word bits, and there might
	 * be a partial word. There are depth / bits_per_word full words and
	 * depth % bits_per_word bits left over. In bitwise arithmetic:
	 *
	 * bits_per_word = 1 << shअगरt
	 * depth / bits_per_word = depth >> shअगरt
	 * depth % bits_per_word = depth & ((1 << shअगरt) - 1)
	 *
	 * Each word can be limited to sbq->min_shallow_depth bits.
	 */
	shallow_depth = min(1U << sbq->sb.shअगरt, sbq->min_shallow_depth);
	depth = ((depth >> sbq->sb.shअगरt) * shallow_depth +
		 min(depth & ((1U << sbq->sb.shअगरt) - 1), shallow_depth));
	wake_batch = clamp_t(अचिन्हित पूर्णांक, depth / SBQ_WAIT_QUEUES, 1,
			     SBQ_WAKE_BATCH);

	वापस wake_batch;
पूर्ण

पूर्णांक sbiपंचांगap_queue_init_node(काष्ठा sbiपंचांगap_queue *sbq, अचिन्हित पूर्णांक depth,
			    पूर्णांक shअगरt, bool round_robin, gfp_t flags, पूर्णांक node)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	ret = sbiपंचांगap_init_node(&sbq->sb, depth, shअगरt, flags, node,
				round_robin, true);
	अगर (ret)
		वापस ret;

	sbq->min_shallow_depth = अच_पूर्णांक_उच्च;
	sbq->wake_batch = sbq_calc_wake_batch(sbq, depth);
	atomic_set(&sbq->wake_index, 0);
	atomic_set(&sbq->ws_active, 0);

	sbq->ws = kzalloc_node(SBQ_WAIT_QUEUES * माप(*sbq->ws), flags, node);
	अगर (!sbq->ws) अणु
		sbiपंचांगap_मुक्त(&sbq->sb);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < SBQ_WAIT_QUEUES; i++) अणु
		init_रुकोqueue_head(&sbq->ws[i].रुको);
		atomic_set(&sbq->ws[i].रुको_cnt, sbq->wake_batch);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_queue_init_node);

अटल व्योम sbiपंचांगap_queue_update_wake_batch(काष्ठा sbiपंचांगap_queue *sbq,
					    अचिन्हित पूर्णांक depth)
अणु
	अचिन्हित पूर्णांक wake_batch = sbq_calc_wake_batch(sbq, depth);
	पूर्णांक i;

	अगर (sbq->wake_batch != wake_batch) अणु
		WRITE_ONCE(sbq->wake_batch, wake_batch);
		/*
		 * Pairs with the memory barrier in sbiपंचांगap_queue_wake_up()
		 * to ensure that the batch size is updated beक्रमe the रुको
		 * counts.
		 */
		smp_mb();
		क्रम (i = 0; i < SBQ_WAIT_QUEUES; i++)
			atomic_set(&sbq->ws[i].रुको_cnt, 1);
	पूर्ण
पूर्ण

व्योम sbiपंचांगap_queue_resize(काष्ठा sbiपंचांगap_queue *sbq, अचिन्हित पूर्णांक depth)
अणु
	sbiपंचांगap_queue_update_wake_batch(sbq, depth);
	sbiपंचांगap_resize(&sbq->sb, depth);
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_queue_resize);

पूर्णांक __sbiपंचांगap_queue_get(काष्ठा sbiपंचांगap_queue *sbq)
अणु
	वापस sbiपंचांगap_get(&sbq->sb);
पूर्ण
EXPORT_SYMBOL_GPL(__sbiपंचांगap_queue_get);

पूर्णांक __sbiपंचांगap_queue_get_shallow(काष्ठा sbiपंचांगap_queue *sbq,
				अचिन्हित पूर्णांक shallow_depth)
अणु
	WARN_ON_ONCE(shallow_depth < sbq->min_shallow_depth);

	वापस sbiपंचांगap_get_shallow(&sbq->sb, shallow_depth);
पूर्ण
EXPORT_SYMBOL_GPL(__sbiपंचांगap_queue_get_shallow);

व्योम sbiपंचांगap_queue_min_shallow_depth(काष्ठा sbiपंचांगap_queue *sbq,
				     अचिन्हित पूर्णांक min_shallow_depth)
अणु
	sbq->min_shallow_depth = min_shallow_depth;
	sbiपंचांगap_queue_update_wake_batch(sbq, sbq->sb.depth);
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_queue_min_shallow_depth);

अटल काष्ठा sbq_रुको_state *sbq_wake_ptr(काष्ठा sbiपंचांगap_queue *sbq)
अणु
	पूर्णांक i, wake_index;

	अगर (!atomic_पढ़ो(&sbq->ws_active))
		वापस शून्य;

	wake_index = atomic_पढ़ो(&sbq->wake_index);
	क्रम (i = 0; i < SBQ_WAIT_QUEUES; i++) अणु
		काष्ठा sbq_रुको_state *ws = &sbq->ws[wake_index];

		अगर (रुकोqueue_active(&ws->रुको)) अणु
			अगर (wake_index != atomic_पढ़ो(&sbq->wake_index))
				atomic_set(&sbq->wake_index, wake_index);
			वापस ws;
		पूर्ण

		wake_index = sbq_index_inc(wake_index);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool __sbq_wake_up(काष्ठा sbiपंचांगap_queue *sbq)
अणु
	काष्ठा sbq_रुको_state *ws;
	अचिन्हित पूर्णांक wake_batch;
	पूर्णांक रुको_cnt;

	ws = sbq_wake_ptr(sbq);
	अगर (!ws)
		वापस false;

	रुको_cnt = atomic_dec_वापस(&ws->रुको_cnt);
	अगर (रुको_cnt <= 0) अणु
		पूर्णांक ret;

		wake_batch = READ_ONCE(sbq->wake_batch);

		/*
		 * Pairs with the memory barrier in sbiपंचांगap_queue_resize() to
		 * ensure that we see the batch size update beक्रमe the रुको
		 * count is reset.
		 */
		smp_mb__beक्रमe_atomic();

		/*
		 * For concurrent callers of this, the one that failed the
		 * atomic_cmpxhcg() race should call this function again
		 * to wakeup a new batch on a dअगरferent 'ws'.
		 */
		ret = atomic_cmpxchg(&ws->रुको_cnt, रुको_cnt, wake_batch);
		अगर (ret == रुको_cnt) अणु
			sbq_index_atomic_inc(&sbq->wake_index);
			wake_up_nr(&ws->रुको, wake_batch);
			वापस false;
		पूर्ण

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम sbiपंचांगap_queue_wake_up(काष्ठा sbiपंचांगap_queue *sbq)
अणु
	जबतक (__sbq_wake_up(sbq))
		;
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_queue_wake_up);

व्योम sbiपंचांगap_queue_clear(काष्ठा sbiपंचांगap_queue *sbq, अचिन्हित पूर्णांक nr,
			 अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * Once the clear bit is set, the bit may be allocated out.
	 *
	 * Orders READ/WRITE on the asssociated instance(such as request
	 * of blk_mq) by this bit क्रम aव्योमing race with re-allocation,
	 * and its pair is the memory barrier implied in __sbiपंचांगap_get_word.
	 *
	 * One invariant is that the clear bit has to be zero when the bit
	 * is in use.
	 */
	smp_mb__beक्रमe_atomic();
	sbiपंचांगap_deferred_clear_bit(&sbq->sb, nr);

	/*
	 * Pairs with the memory barrier in set_current_state() to ensure the
	 * proper ordering of clear_bit_unlock()/रुकोqueue_active() in the waker
	 * and test_and_set_bit_lock()/prepare_to_रुको()/finish_रुको() in the
	 * रुकोer. See the comment on रुकोqueue_active().
	 */
	smp_mb__after_atomic();
	sbiपंचांगap_queue_wake_up(sbq);

	अगर (likely(!sbq->sb.round_robin && nr < sbq->sb.depth))
		*per_cpu_ptr(sbq->sb.alloc_hपूर्णांक, cpu) = nr;
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_queue_clear);

व्योम sbiपंचांगap_queue_wake_all(काष्ठा sbiपंचांगap_queue *sbq)
अणु
	पूर्णांक i, wake_index;

	/*
	 * Pairs with the memory barrier in set_current_state() like in
	 * sbiपंचांगap_queue_wake_up().
	 */
	smp_mb();
	wake_index = atomic_पढ़ो(&sbq->wake_index);
	क्रम (i = 0; i < SBQ_WAIT_QUEUES; i++) अणु
		काष्ठा sbq_रुको_state *ws = &sbq->ws[wake_index];

		अगर (रुकोqueue_active(&ws->रुको))
			wake_up(&ws->रुको);

		wake_index = sbq_index_inc(wake_index);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_queue_wake_all);

व्योम sbiपंचांगap_queue_show(काष्ठा sbiपंचांगap_queue *sbq, काष्ठा seq_file *m)
अणु
	bool first;
	पूर्णांक i;

	sbiपंचांगap_show(&sbq->sb, m);

	seq_माला_दो(m, "alloc_hint={");
	first = true;
	क्रम_each_possible_cpu(i) अणु
		अगर (!first)
			seq_माला_दो(m, ", ");
		first = false;
		seq_म_लिखो(m, "%u", *per_cpu_ptr(sbq->sb.alloc_hपूर्णांक, i));
	पूर्ण
	seq_माला_दो(m, "}\n");

	seq_म_लिखो(m, "wake_batch=%u\n", sbq->wake_batch);
	seq_म_लिखो(m, "wake_index=%d\n", atomic_पढ़ो(&sbq->wake_index));
	seq_म_लिखो(m, "ws_active=%d\n", atomic_पढ़ो(&sbq->ws_active));

	seq_माला_दो(m, "ws={\n");
	क्रम (i = 0; i < SBQ_WAIT_QUEUES; i++) अणु
		काष्ठा sbq_रुको_state *ws = &sbq->ws[i];

		seq_म_लिखो(m, "\t{.wait_cnt=%d, .wait=%s},\n",
			   atomic_पढ़ो(&ws->रुको_cnt),
			   रुकोqueue_active(&ws->रुको) ? "active" : "inactive");
	पूर्ण
	seq_माला_दो(m, "}\n");

	seq_म_लिखो(m, "round_robin=%d\n", sbq->sb.round_robin);
	seq_म_लिखो(m, "min_shallow_depth=%u\n", sbq->min_shallow_depth);
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_queue_show);

व्योम sbiपंचांगap_add_रुको_queue(काष्ठा sbiपंचांगap_queue *sbq,
			    काष्ठा sbq_रुको_state *ws,
			    काष्ठा sbq_रुको *sbq_रुको)
अणु
	अगर (!sbq_रुको->sbq) अणु
		sbq_रुको->sbq = sbq;
		atomic_inc(&sbq->ws_active);
		add_रुको_queue(&ws->रुको, &sbq_रुको->रुको);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_add_रुको_queue);

व्योम sbiपंचांगap_del_रुको_queue(काष्ठा sbq_रुको *sbq_रुको)
अणु
	list_del_init(&sbq_रुको->रुको.entry);
	अगर (sbq_रुको->sbq) अणु
		atomic_dec(&sbq_रुको->sbq->ws_active);
		sbq_रुको->sbq = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_del_रुको_queue);

व्योम sbiपंचांगap_prepare_to_रुको(काष्ठा sbiपंचांगap_queue *sbq,
			     काष्ठा sbq_रुको_state *ws,
			     काष्ठा sbq_रुको *sbq_रुको, पूर्णांक state)
अणु
	अगर (!sbq_रुको->sbq) अणु
		atomic_inc(&sbq->ws_active);
		sbq_रुको->sbq = sbq;
	पूर्ण
	prepare_to_रुको_exclusive(&ws->रुको, &sbq_रुको->रुको, state);
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_prepare_to_रुको);

व्योम sbiपंचांगap_finish_रुको(काष्ठा sbiपंचांगap_queue *sbq, काष्ठा sbq_रुको_state *ws,
			 काष्ठा sbq_रुको *sbq_रुको)
अणु
	finish_रुको(&ws->रुको, &sbq_रुको->रुको);
	अगर (sbq_रुको->sbq) अणु
		atomic_dec(&sbq->ws_active);
		sbq_रुको->sbq = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sbiपंचांगap_finish_रुको);
