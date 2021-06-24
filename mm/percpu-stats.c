<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mm/percpu-debug.c
 *
 * Copyright (C) 2017		Facebook Inc.
 * Copyright (C) 2017		Dennis Zhou <dennis@kernel.org>
 *
 * Prपूर्णांकs statistics about the percpu allocator and backing chunks.
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/list.h>
#समावेश <linux/percpu.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sort.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "percpu-internal.h"

#घोषणा P(X, Y) \
	seq_म_लिखो(m, "  %-20s: %12lld\n", X, (दीर्घ दीर्घ पूर्णांक)Y)

काष्ठा percpu_stats pcpu_stats;
काष्ठा pcpu_alloc_info pcpu_stats_ai;

अटल पूर्णांक cmpपूर्णांक(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस *(पूर्णांक *)a - *(पूर्णांक *)b;
पूर्ण

/*
 * Iterates over all chunks to find the max nr_alloc entries.
 */
अटल पूर्णांक find_max_nr_alloc(व्योम)
अणु
	काष्ठा pcpu_chunk *chunk;
	पूर्णांक slot, max_nr_alloc;
	क्रमागत pcpu_chunk_type type;

	max_nr_alloc = 0;
	क्रम (type = 0; type < PCPU_NR_CHUNK_TYPES; type++)
		क्रम (slot = 0; slot < pcpu_nr_slots; slot++)
			list_क्रम_each_entry(chunk, &pcpu_chunk_list(type)[slot],
					    list)
				max_nr_alloc = max(max_nr_alloc,
						   chunk->nr_alloc);

	वापस max_nr_alloc;
पूर्ण

/*
 * Prपूर्णांकs out chunk state. Fragmentation is considered between
 * the beginning of the chunk to the last allocation.
 *
 * All statistics are in bytes unless stated otherwise.
 */
अटल व्योम chunk_map_stats(काष्ठा seq_file *m, काष्ठा pcpu_chunk *chunk,
			    पूर्णांक *buffer)
अणु
	काष्ठा pcpu_block_md *chunk_md = &chunk->chunk_md;
	पूर्णांक i, last_alloc, as_len, start, end;
	पूर्णांक *alloc_sizes, *p;
	/* statistics */
	पूर्णांक sum_frag = 0, max_frag = 0;
	पूर्णांक cur_min_alloc = 0, cur_med_alloc = 0, cur_max_alloc = 0;

	alloc_sizes = buffer;

	/*
	 * find_last_bit वापसs the start value अगर nothing found.
	 * Thereक्रमe, we must determine अगर it is a failure of find_last_bit
	 * and set the appropriate value.
	 */
	last_alloc = find_last_bit(chunk->alloc_map,
				   pcpu_chunk_map_bits(chunk) -
				   chunk->end_offset / PCPU_MIN_ALLOC_SIZE - 1);
	last_alloc = test_bit(last_alloc, chunk->alloc_map) ?
		     last_alloc + 1 : 0;

	as_len = 0;
	start = chunk->start_offset / PCPU_MIN_ALLOC_SIZE;

	/*
	 * If a bit is set in the allocation map, the bound_map identअगरies
	 * where the allocation ends.  If the allocation is not set, the
	 * bound_map करोes not identअगरy मुक्त areas as it is only kept accurate
	 * on allocation, not मुक्त.
	 *
	 * Positive values are allocations and negative values are मुक्त
	 * fragments.
	 */
	जबतक (start < last_alloc) अणु
		अगर (test_bit(start, chunk->alloc_map)) अणु
			end = find_next_bit(chunk->bound_map, last_alloc,
					    start + 1);
			alloc_sizes[as_len] = 1;
		पूर्ण अन्यथा अणु
			end = find_next_bit(chunk->alloc_map, last_alloc,
					    start + 1);
			alloc_sizes[as_len] = -1;
		पूर्ण

		alloc_sizes[as_len++] *= (end - start) * PCPU_MIN_ALLOC_SIZE;

		start = end;
	पूर्ण

	/*
	 * The negative values are मुक्त fragments and thus sorting gives the
	 * मुक्त fragments at the beginning in largest first order.
	 */
	अगर (as_len > 0) अणु
		sort(alloc_sizes, as_len, माप(पूर्णांक), cmpपूर्णांक, शून्य);

		/* iterate through the unallocated fragments */
		क्रम (i = 0, p = alloc_sizes; *p < 0 && i < as_len; i++, p++) अणु
			sum_frag -= *p;
			max_frag = max(max_frag, -1 * (*p));
		पूर्ण

		cur_min_alloc = alloc_sizes[i];
		cur_med_alloc = alloc_sizes[(i + as_len - 1) / 2];
		cur_max_alloc = alloc_sizes[as_len - 1];
	पूर्ण

	P("nr_alloc", chunk->nr_alloc);
	P("max_alloc_size", chunk->max_alloc_size);
	P("empty_pop_pages", chunk->nr_empty_pop_pages);
	P("first_bit", chunk_md->first_मुक्त);
	P("free_bytes", chunk->मुक्त_bytes);
	P("contig_bytes", chunk_md->contig_hपूर्णांक * PCPU_MIN_ALLOC_SIZE);
	P("sum_frag", sum_frag);
	P("max_frag", max_frag);
	P("cur_min_alloc", cur_min_alloc);
	P("cur_med_alloc", cur_med_alloc);
	P("cur_max_alloc", cur_max_alloc);
#अगर_घोषित CONFIG_MEMCG_KMEM
	P("memcg_aware", pcpu_is_memcg_chunk(pcpu_chunk_type(chunk)));
#पूर्ण_अगर
	seq_अ_दो(m, '\n');
पूर्ण

अटल पूर्णांक percpu_stats_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा pcpu_chunk *chunk;
	पूर्णांक slot, max_nr_alloc;
	पूर्णांक *buffer;
	क्रमागत pcpu_chunk_type type;
	पूर्णांक nr_empty_pop_pages;

alloc_buffer:
	spin_lock_irq(&pcpu_lock);
	max_nr_alloc = find_max_nr_alloc();
	spin_unlock_irq(&pcpu_lock);

	/* there can be at most this many मुक्त and allocated fragments */
	buffer = vदो_स्मृति(array_size(माप(पूर्णांक), (2 * max_nr_alloc + 1)));
	अगर (!buffer)
		वापस -ENOMEM;

	spin_lock_irq(&pcpu_lock);

	/* अगर the buffer allocated earlier is too small */
	अगर (max_nr_alloc < find_max_nr_alloc()) अणु
		spin_unlock_irq(&pcpu_lock);
		vमुक्त(buffer);
		जाओ alloc_buffer;
	पूर्ण

	nr_empty_pop_pages = 0;
	क्रम (type = 0; type < PCPU_NR_CHUNK_TYPES; type++)
		nr_empty_pop_pages += pcpu_nr_empty_pop_pages[type];

#घोषणा PL(X)								\
	seq_म_लिखो(m, "  %-20s: %12lld\n", #X, (दीर्घ दीर्घ पूर्णांक)pcpu_stats_ai.X)

	seq_म_लिखो(m,
			"Percpu Memory Statistics\n"
			"Allocation Info:\n"
			"----------------------------------------\n");
	PL(unit_size);
	PL(अटल_size);
	PL(reserved_size);
	PL(dyn_size);
	PL(atom_size);
	PL(alloc_size);
	seq_अ_दो(m, '\n');

#अघोषित PL

#घोषणा PU(X) \
	seq_म_लिखो(m, "  %-20s: %12llu\n", #X, (अचिन्हित दीर्घ दीर्घ)pcpu_stats.X)

	seq_म_लिखो(m,
			"Global Stats:\n"
			"----------------------------------------\n");
	PU(nr_alloc);
	PU(nr_dealloc);
	PU(nr_cur_alloc);
	PU(nr_max_alloc);
	PU(nr_chunks);
	PU(nr_max_chunks);
	PU(min_alloc_size);
	PU(max_alloc_size);
	P("empty_pop_pages", nr_empty_pop_pages);
	seq_अ_दो(m, '\n');

#अघोषित PU

	seq_म_लिखो(m,
			"Per Chunk Stats:\n"
			"----------------------------------------\n");

	अगर (pcpu_reserved_chunk) अणु
		seq_माला_दो(m, "Chunk: <- Reserved Chunk\n");
		chunk_map_stats(m, pcpu_reserved_chunk, buffer);
	पूर्ण

	क्रम (type = 0; type < PCPU_NR_CHUNK_TYPES; type++) अणु
		क्रम (slot = 0; slot < pcpu_nr_slots; slot++) अणु
			list_क्रम_each_entry(chunk, &pcpu_chunk_list(type)[slot],
					    list) अणु
				अगर (chunk == pcpu_first_chunk) अणु
					seq_माला_दो(m, "Chunk: <- First Chunk\n");
					chunk_map_stats(m, chunk, buffer);
				पूर्ण अन्यथा अणु
					seq_माला_दो(m, "Chunk:\n");
					chunk_map_stats(m, chunk, buffer);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_irq(&pcpu_lock);

	vमुक्त(buffer);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(percpu_stats);

अटल पूर्णांक __init init_percpu_stats_debugfs(व्योम)
अणु
	debugfs_create_file("percpu_stats", 0444, शून्य, शून्य,
			&percpu_stats_fops);

	वापस 0;
पूर्ण

late_initcall(init_percpu_stats_debugfs);
