<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * auxtrace.c: AUX area trace support
 * Copyright (c) 2013-2015, Intel Corporation.
 */

#समावेश <पूर्णांकtypes.h>
#समावेश <sys/types.h>
#समावेश <sys/mman.h>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <सीमा.स>
#समावेश <त्रुटिसं.स>

#समावेश <linux/kernel.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/log2.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय64.h>

#समावेश <sys/param.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <linux/list.h>
#समावेश <linux/zभाग.स>

#समावेश "evlist.h"
#समावेश "dso.h"
#समावेश "map.h"
#समावेश "pmu.h"
#समावेश "evsel.h"
#समावेश "evsel_config.h"
#समावेश "symbol.h"
#समावेश "util/perf_api_probe.h"
#समावेश "util/synthetic-events.h"
#समावेश "thread_map.h"
#समावेश "asm/bug.h"
#समावेश "auxtrace.h"

#समावेश <linux/hash.h>

#समावेश "event.h"
#समावेश "record.h"
#समावेश "session.h"
#समावेश "debug.h"
#समावेश <subcmd/parse-options.h>

#समावेश "cs-etm.h"
#समावेश "intel-pt.h"
#समावेश "intel-bts.h"
#समावेश "arm-spe.h"
#समावेश "s390-cpumsf.h"
#समावेश "util/mmap.h"

#समावेश <linux/प्रकार.स>
#समावेश "symbol/kallsyms.h"
#समावेश <पूर्णांकernal/lib.h>

/*
 * Make a group from 'leader' to 'last', requiring that the events were not
 * alपढ़ोy grouped to a dअगरferent leader.
 */
अटल पूर्णांक evlist__regroup(काष्ठा evlist *evlist, काष्ठा evsel *leader, काष्ठा evsel *last)
अणु
	काष्ठा evsel *evsel;
	bool grp;

	अगर (!evsel__is_group_leader(leader))
		वापस -EINVAL;

	grp = false;
	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (grp) अणु
			अगर (!(evsel->leader == leader ||
			     (evsel->leader == evsel &&
			      evsel->core.nr_members <= 1)))
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (evsel == leader) अणु
			grp = true;
		पूर्ण
		अगर (evsel == last)
			अवरोध;
	पूर्ण

	grp = false;
	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (grp) अणु
			अगर (evsel->leader != leader) अणु
				evsel->leader = leader;
				अगर (leader->core.nr_members < 1)
					leader->core.nr_members = 1;
				leader->core.nr_members += 1;
			पूर्ण
		पूर्ण अन्यथा अगर (evsel == leader) अणु
			grp = true;
		पूर्ण
		अगर (evsel == last)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool auxtrace__करोnt_decode(काष्ठा perf_session *session)
अणु
	वापस !session->itrace_synth_opts ||
	       session->itrace_synth_opts->करोnt_decode;
पूर्ण

पूर्णांक auxtrace_mmap__mmap(काष्ठा auxtrace_mmap *mm,
			काष्ठा auxtrace_mmap_params *mp,
			व्योम *userpg, पूर्णांक fd)
अणु
	काष्ठा perf_event_mmap_page *pc = userpg;

	WARN_ONCE(mm->base, "Uninitialized auxtrace_mmap\n");

	mm->userpg = userpg;
	mm->mask = mp->mask;
	mm->len = mp->len;
	mm->prev = 0;
	mm->idx = mp->idx;
	mm->tid = mp->tid;
	mm->cpu = mp->cpu;

	अगर (!mp->len) अणु
		mm->base = शून्य;
		वापस 0;
	पूर्ण

#अगर BITS_PER_LONG != 64 && !defined(HAVE_SYNC_COMPARE_AND_SWAP_SUPPORT)
	pr_err("Cannot use AUX area tracing mmaps\n");
	वापस -1;
#पूर्ण_अगर

	pc->aux_offset = mp->offset;
	pc->aux_size = mp->len;

	mm->base = mmap(शून्य, mp->len, mp->prot, MAP_SHARED, fd, mp->offset);
	अगर (mm->base == MAP_FAILED) अणु
		pr_debug2("failed to mmap AUX area\n");
		mm->base = शून्य;
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम auxtrace_mmap__munmap(काष्ठा auxtrace_mmap *mm)
अणु
	अगर (mm->base) अणु
		munmap(mm->base, mm->len);
		mm->base = शून्य;
	पूर्ण
पूर्ण

व्योम auxtrace_mmap_params__init(काष्ठा auxtrace_mmap_params *mp,
				off_t auxtrace_offset,
				अचिन्हित पूर्णांक auxtrace_pages,
				bool auxtrace_overग_लिखो)
अणु
	अगर (auxtrace_pages) अणु
		mp->offset = auxtrace_offset;
		mp->len = auxtrace_pages * (माप_प्रकार)page_size;
		mp->mask = is_घातer_of_2(mp->len) ? mp->len - 1 : 0;
		mp->prot = PROT_READ | (auxtrace_overग_लिखो ? 0 : PROT_WRITE);
		pr_debug2("AUX area mmap length %zu\n", mp->len);
	पूर्ण अन्यथा अणु
		mp->len = 0;
	पूर्ण
पूर्ण

व्योम auxtrace_mmap_params__set_idx(काष्ठा auxtrace_mmap_params *mp,
				   काष्ठा evlist *evlist, पूर्णांक idx,
				   bool per_cpu)
अणु
	mp->idx = idx;

	अगर (per_cpu) अणु
		mp->cpu = evlist->core.cpus->map[idx];
		अगर (evlist->core.thपढ़ोs)
			mp->tid = perf_thपढ़ो_map__pid(evlist->core.thपढ़ोs, 0);
		अन्यथा
			mp->tid = -1;
	पूर्ण अन्यथा अणु
		mp->cpu = -1;
		mp->tid = perf_thपढ़ो_map__pid(evlist->core.thपढ़ोs, idx);
	पूर्ण
पूर्ण

#घोषणा AUXTRACE_INIT_NR_QUEUES	32

अटल काष्ठा auxtrace_queue *auxtrace_alloc_queue_array(अचिन्हित पूर्णांक nr_queues)
अणु
	काष्ठा auxtrace_queue *queue_array;
	अचिन्हित पूर्णांक max_nr_queues, i;

	max_nr_queues = अच_पूर्णांक_उच्च / माप(काष्ठा auxtrace_queue);
	अगर (nr_queues > max_nr_queues)
		वापस शून्य;

	queue_array = सुस्मृति(nr_queues, माप(काष्ठा auxtrace_queue));
	अगर (!queue_array)
		वापस शून्य;

	क्रम (i = 0; i < nr_queues; i++) अणु
		INIT_LIST_HEAD(&queue_array[i].head);
		queue_array[i].priv = शून्य;
	पूर्ण

	वापस queue_array;
पूर्ण

पूर्णांक auxtrace_queues__init(काष्ठा auxtrace_queues *queues)
अणु
	queues->nr_queues = AUXTRACE_INIT_NR_QUEUES;
	queues->queue_array = auxtrace_alloc_queue_array(queues->nr_queues);
	अगर (!queues->queue_array)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक auxtrace_queues__grow(काष्ठा auxtrace_queues *queues,
				 अचिन्हित पूर्णांक new_nr_queues)
अणु
	अचिन्हित पूर्णांक nr_queues = queues->nr_queues;
	काष्ठा auxtrace_queue *queue_array;
	अचिन्हित पूर्णांक i;

	अगर (!nr_queues)
		nr_queues = AUXTRACE_INIT_NR_QUEUES;

	जबतक (nr_queues && nr_queues < new_nr_queues)
		nr_queues <<= 1;

	अगर (nr_queues < queues->nr_queues || nr_queues < new_nr_queues)
		वापस -EINVAL;

	queue_array = auxtrace_alloc_queue_array(nr_queues);
	अगर (!queue_array)
		वापस -ENOMEM;

	क्रम (i = 0; i < queues->nr_queues; i++) अणु
		list_splice_tail(&queues->queue_array[i].head,
				 &queue_array[i].head);
		queue_array[i].tid = queues->queue_array[i].tid;
		queue_array[i].cpu = queues->queue_array[i].cpu;
		queue_array[i].set = queues->queue_array[i].set;
		queue_array[i].priv = queues->queue_array[i].priv;
	पूर्ण

	queues->nr_queues = nr_queues;
	queues->queue_array = queue_array;

	वापस 0;
पूर्ण

अटल व्योम *auxtrace_copy_data(u64 size, काष्ठा perf_session *session)
अणु
	पूर्णांक fd = perf_data__fd(session->data);
	व्योम *p;
	sमाप_प्रकार ret;

	अगर (size > SSIZE_MAX)
		वापस शून्य;

	p = दो_स्मृति(size);
	अगर (!p)
		वापस शून्य;

	ret = पढ़ोn(fd, p, size);
	अगर (ret != (sमाप_प्रकार)size) अणु
		मुक्त(p);
		वापस शून्य;
	पूर्ण

	वापस p;
पूर्ण

अटल पूर्णांक auxtrace_queues__queue_buffer(काष्ठा auxtrace_queues *queues,
					 अचिन्हित पूर्णांक idx,
					 काष्ठा auxtrace_buffer *buffer)
अणु
	काष्ठा auxtrace_queue *queue;
	पूर्णांक err;

	अगर (idx >= queues->nr_queues) अणु
		err = auxtrace_queues__grow(queues, idx + 1);
		अगर (err)
			वापस err;
	पूर्ण

	queue = &queues->queue_array[idx];

	अगर (!queue->set) अणु
		queue->set = true;
		queue->tid = buffer->tid;
		queue->cpu = buffer->cpu;
	पूर्ण

	buffer->buffer_nr = queues->next_buffer_nr++;

	list_add_tail(&buffer->list, &queue->head);

	queues->new_data = true;
	queues->populated = true;

	वापस 0;
पूर्ण

/* Limit buffers to 32MiB on 32-bit */
#घोषणा BUFFER_LIMIT_FOR_32_BIT (32 * 1024 * 1024)

अटल पूर्णांक auxtrace_queues__split_buffer(काष्ठा auxtrace_queues *queues,
					 अचिन्हित पूर्णांक idx,
					 काष्ठा auxtrace_buffer *buffer)
अणु
	u64 sz = buffer->size;
	bool consecutive = false;
	काष्ठा auxtrace_buffer *b;
	पूर्णांक err;

	जबतक (sz > BUFFER_LIMIT_FOR_32_BIT) अणु
		b = memdup(buffer, माप(काष्ठा auxtrace_buffer));
		अगर (!b)
			वापस -ENOMEM;
		b->size = BUFFER_LIMIT_FOR_32_BIT;
		b->consecutive = consecutive;
		err = auxtrace_queues__queue_buffer(queues, idx, b);
		अगर (err) अणु
			auxtrace_buffer__मुक्त(b);
			वापस err;
		पूर्ण
		buffer->data_offset += BUFFER_LIMIT_FOR_32_BIT;
		sz -= BUFFER_LIMIT_FOR_32_BIT;
		consecutive = true;
	पूर्ण

	buffer->size = sz;
	buffer->consecutive = consecutive;

	वापस 0;
पूर्ण

अटल bool filter_cpu(काष्ठा perf_session *session, पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ *cpu_biपंचांगap = session->itrace_synth_opts->cpu_biपंचांगap;

	वापस cpu_biपंचांगap && cpu != -1 && !test_bit(cpu, cpu_biपंचांगap);
पूर्ण

अटल पूर्णांक auxtrace_queues__add_buffer(काष्ठा auxtrace_queues *queues,
				       काष्ठा perf_session *session,
				       अचिन्हित पूर्णांक idx,
				       काष्ठा auxtrace_buffer *buffer,
				       काष्ठा auxtrace_buffer **buffer_ptr)
अणु
	पूर्णांक err = -ENOMEM;

	अगर (filter_cpu(session, buffer->cpu))
		वापस 0;

	buffer = memdup(buffer, माप(*buffer));
	अगर (!buffer)
		वापस -ENOMEM;

	अगर (session->one_mmap) अणु
		buffer->data = buffer->data_offset - session->one_mmap_offset +
			       session->one_mmap_addr;
	पूर्ण अन्यथा अगर (perf_data__is_pipe(session->data)) अणु
		buffer->data = auxtrace_copy_data(buffer->size, session);
		अगर (!buffer->data)
			जाओ out_मुक्त;
		buffer->data_needs_मुक्तing = true;
	पूर्ण अन्यथा अगर (BITS_PER_LONG == 32 &&
		   buffer->size > BUFFER_LIMIT_FOR_32_BIT) अणु
		err = auxtrace_queues__split_buffer(queues, idx, buffer);
		अगर (err)
			जाओ out_मुक्त;
	पूर्ण

	err = auxtrace_queues__queue_buffer(queues, idx, buffer);
	अगर (err)
		जाओ out_मुक्त;

	/* FIXME: Doesn't work क्रम split buffer */
	अगर (buffer_ptr)
		*buffer_ptr = buffer;

	वापस 0;

out_मुक्त:
	auxtrace_buffer__मुक्त(buffer);
	वापस err;
पूर्ण

पूर्णांक auxtrace_queues__add_event(काष्ठा auxtrace_queues *queues,
			       काष्ठा perf_session *session,
			       जोड़ perf_event *event, off_t data_offset,
			       काष्ठा auxtrace_buffer **buffer_ptr)
अणु
	काष्ठा auxtrace_buffer buffer = अणु
		.pid = -1,
		.tid = event->auxtrace.tid,
		.cpu = event->auxtrace.cpu,
		.data_offset = data_offset,
		.offset = event->auxtrace.offset,
		.reference = event->auxtrace.reference,
		.size = event->auxtrace.size,
	पूर्ण;
	अचिन्हित पूर्णांक idx = event->auxtrace.idx;

	वापस auxtrace_queues__add_buffer(queues, session, idx, &buffer,
					   buffer_ptr);
पूर्ण

अटल पूर्णांक auxtrace_queues__add_indexed_event(काष्ठा auxtrace_queues *queues,
					      काष्ठा perf_session *session,
					      off_t file_offset, माप_प्रकार sz)
अणु
	जोड़ perf_event *event;
	पूर्णांक err;
	अक्षर buf[PERF_SAMPLE_MAX_SIZE];

	err = perf_session__peek_event(session, file_offset, buf,
				       PERF_SAMPLE_MAX_SIZE, &event, शून्य);
	अगर (err)
		वापस err;

	अगर (event->header.type == PERF_RECORD_AUXTRACE) अणु
		अगर (event->header.size < माप(काष्ठा perf_record_auxtrace) ||
		    event->header.size != sz) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		file_offset += event->header.size;
		err = auxtrace_queues__add_event(queues, session, event,
						 file_offset, शून्य);
	पूर्ण
out:
	वापस err;
पूर्ण

व्योम auxtrace_queues__मुक्त(काष्ठा auxtrace_queues *queues)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < queues->nr_queues; i++) अणु
		जबतक (!list_empty(&queues->queue_array[i].head)) अणु
			काष्ठा auxtrace_buffer *buffer;

			buffer = list_entry(queues->queue_array[i].head.next,
					    काष्ठा auxtrace_buffer, list);
			list_del_init(&buffer->list);
			auxtrace_buffer__मुक्त(buffer);
		पूर्ण
	पूर्ण

	zमुक्त(&queues->queue_array);
	queues->nr_queues = 0;
पूर्ण

अटल व्योम auxtrace_heapअगरy(काष्ठा auxtrace_heap_item *heap_array,
			     अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक queue_nr,
			     u64 ordinal)
अणु
	अचिन्हित पूर्णांक parent;

	जबतक (pos) अणु
		parent = (pos - 1) >> 1;
		अगर (heap_array[parent].ordinal <= ordinal)
			अवरोध;
		heap_array[pos] = heap_array[parent];
		pos = parent;
	पूर्ण
	heap_array[pos].queue_nr = queue_nr;
	heap_array[pos].ordinal = ordinal;
पूर्ण

पूर्णांक auxtrace_heap__add(काष्ठा auxtrace_heap *heap, अचिन्हित पूर्णांक queue_nr,
		       u64 ordinal)
अणु
	काष्ठा auxtrace_heap_item *heap_array;

	अगर (queue_nr >= heap->heap_sz) अणु
		अचिन्हित पूर्णांक heap_sz = AUXTRACE_INIT_NR_QUEUES;

		जबतक (heap_sz <= queue_nr)
			heap_sz <<= 1;
		heap_array = पुनः_स्मृति(heap->heap_array,
				     heap_sz * माप(काष्ठा auxtrace_heap_item));
		अगर (!heap_array)
			वापस -ENOMEM;
		heap->heap_array = heap_array;
		heap->heap_sz = heap_sz;
	पूर्ण

	auxtrace_heapअगरy(heap->heap_array, heap->heap_cnt++, queue_nr, ordinal);

	वापस 0;
पूर्ण

व्योम auxtrace_heap__मुक्त(काष्ठा auxtrace_heap *heap)
अणु
	zमुक्त(&heap->heap_array);
	heap->heap_cnt = 0;
	heap->heap_sz = 0;
पूर्ण

व्योम auxtrace_heap__pop(काष्ठा auxtrace_heap *heap)
अणु
	अचिन्हित पूर्णांक pos, last, heap_cnt = heap->heap_cnt;
	काष्ठा auxtrace_heap_item *heap_array;

	अगर (!heap_cnt)
		वापस;

	heap->heap_cnt -= 1;

	heap_array = heap->heap_array;

	pos = 0;
	जबतक (1) अणु
		अचिन्हित पूर्णांक left, right;

		left = (pos << 1) + 1;
		अगर (left >= heap_cnt)
			अवरोध;
		right = left + 1;
		अगर (right >= heap_cnt) अणु
			heap_array[pos] = heap_array[left];
			वापस;
		पूर्ण
		अगर (heap_array[left].ordinal < heap_array[right].ordinal) अणु
			heap_array[pos] = heap_array[left];
			pos = left;
		पूर्ण अन्यथा अणु
			heap_array[pos] = heap_array[right];
			pos = right;
		पूर्ण
	पूर्ण

	last = heap_cnt - 1;
	auxtrace_heapअगरy(heap_array, pos, heap_array[last].queue_nr,
			 heap_array[last].ordinal);
पूर्ण

माप_प्रकार auxtrace_record__info_priv_size(काष्ठा auxtrace_record *itr,
				       काष्ठा evlist *evlist)
अणु
	अगर (itr)
		वापस itr->info_priv_size(itr, evlist);
	वापस 0;
पूर्ण

अटल पूर्णांक auxtrace_not_supported(व्योम)
अणु
	pr_err("AUX area tracing is not supported on this architecture\n");
	वापस -EINVAL;
पूर्ण

पूर्णांक auxtrace_record__info_fill(काष्ठा auxtrace_record *itr,
			       काष्ठा perf_session *session,
			       काष्ठा perf_record_auxtrace_info *auxtrace_info,
			       माप_प्रकार priv_size)
अणु
	अगर (itr)
		वापस itr->info_fill(itr, session, auxtrace_info, priv_size);
	वापस auxtrace_not_supported();
पूर्ण

व्योम auxtrace_record__मुक्त(काष्ठा auxtrace_record *itr)
अणु
	अगर (itr)
		itr->मुक्त(itr);
पूर्ण

पूर्णांक auxtrace_record__snapshot_start(काष्ठा auxtrace_record *itr)
अणु
	अगर (itr && itr->snapshot_start)
		वापस itr->snapshot_start(itr);
	वापस 0;
पूर्ण

पूर्णांक auxtrace_record__snapshot_finish(काष्ठा auxtrace_record *itr, bool on_निकास)
अणु
	अगर (!on_निकास && itr && itr->snapshot_finish)
		वापस itr->snapshot_finish(itr);
	वापस 0;
पूर्ण

पूर्णांक auxtrace_record__find_snapshot(काष्ठा auxtrace_record *itr, पूर्णांक idx,
				   काष्ठा auxtrace_mmap *mm,
				   अचिन्हित अक्षर *data, u64 *head, u64 *old)
अणु
	अगर (itr && itr->find_snapshot)
		वापस itr->find_snapshot(itr, idx, mm, data, head, old);
	वापस 0;
पूर्ण

पूर्णांक auxtrace_record__options(काष्ठा auxtrace_record *itr,
			     काष्ठा evlist *evlist,
			     काष्ठा record_opts *opts)
अणु
	अगर (itr) अणु
		itr->evlist = evlist;
		वापस itr->recording_options(itr, evlist, opts);
	पूर्ण
	वापस 0;
पूर्ण

u64 auxtrace_record__reference(काष्ठा auxtrace_record *itr)
अणु
	अगर (itr)
		वापस itr->reference(itr);
	वापस 0;
पूर्ण

पूर्णांक auxtrace_parse_snapshot_options(काष्ठा auxtrace_record *itr,
				    काष्ठा record_opts *opts, स्थिर अक्षर *str)
अणु
	अगर (!str)
		वापस 0;

	/* PMU-agnostic options */
	चयन (*str) अणु
	हाल 'e':
		opts->auxtrace_snapshot_on_निकास = true;
		str++;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (itr && itr->parse_snapshot_options)
		वापस itr->parse_snapshot_options(itr, opts, str);

	pr_err("No AUX area tracing to snapshot\n");
	वापस -EINVAL;
पूर्ण

पूर्णांक auxtrace_record__पढ़ो_finish(काष्ठा auxtrace_record *itr, पूर्णांक idx)
अणु
	काष्ठा evsel *evsel;

	अगर (!itr->evlist || !itr->pmu)
		वापस -EINVAL;

	evlist__क्रम_each_entry(itr->evlist, evsel) अणु
		अगर (evsel->core.attr.type == itr->pmu->type) अणु
			अगर (evsel->disabled)
				वापस 0;
			वापस evlist__enable_event_idx(itr->evlist, evsel, idx);
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * Event record size is 16-bit which results in a maximum size of about 64KiB.
 * Allow about 4KiB क्रम the rest of the sample record, to give a maximum
 * AUX area sample size of 60KiB.
 */
#घोषणा MAX_AUX_SAMPLE_SIZE (60 * 1024)

/* Arbitrary शेष size अगर no other शेष provided */
#घोषणा DEFAULT_AUX_SAMPLE_SIZE (4 * 1024)

अटल पूर्णांक auxtrace_validate_aux_sample_size(काष्ठा evlist *evlist,
					     काष्ठा record_opts *opts)
अणु
	काष्ठा evsel *evsel;
	bool has_aux_leader = false;
	u32 sz;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		sz = evsel->core.attr.aux_sample_size;
		अगर (evsel__is_group_leader(evsel)) अणु
			has_aux_leader = evsel__is_aux_event(evsel);
			अगर (sz) अणु
				अगर (has_aux_leader)
					pr_err("Cannot add AUX area sampling to an AUX area event\n");
				अन्यथा
					pr_err("Cannot add AUX area sampling to a group leader\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अगर (sz > MAX_AUX_SAMPLE_SIZE) अणु
			pr_err("AUX area sample size %u too big, max. %d\n",
			       sz, MAX_AUX_SAMPLE_SIZE);
			वापस -EINVAL;
		पूर्ण
		अगर (sz) अणु
			अगर (!has_aux_leader) अणु
				pr_err("Cannot add AUX area sampling because group leader is not an AUX area event\n");
				वापस -EINVAL;
			पूर्ण
			evsel__set_sample_bit(evsel, AUX);
			opts->auxtrace_sample_mode = true;
		पूर्ण अन्यथा अणु
			evsel__reset_sample_bit(evsel, AUX);
		पूर्ण
	पूर्ण

	अगर (!opts->auxtrace_sample_mode) अणु
		pr_err("AUX area sampling requires an AUX area event group leader plus other events to which to add samples\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!perf_can_aux_sample()) अणु
		pr_err("AUX area sampling is not supported by kernel\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक auxtrace_parse_sample_options(काष्ठा auxtrace_record *itr,
				  काष्ठा evlist *evlist,
				  काष्ठा record_opts *opts, स्थिर अक्षर *str)
अणु
	काष्ठा evsel_config_term *term;
	काष्ठा evsel *aux_evsel;
	bool has_aux_sample_size = false;
	bool has_aux_leader = false;
	काष्ठा evsel *evsel;
	अक्षर *endptr;
	अचिन्हित दीर्घ sz;

	अगर (!str)
		जाओ no_opt;

	अगर (!itr) अणु
		pr_err("No AUX area event to sample\n");
		वापस -EINVAL;
	पूर्ण

	sz = म_से_अदीर्घ(str, &endptr, 0);
	अगर (*endptr || sz > अच_पूर्णांक_उच्च) अणु
		pr_err("Bad AUX area sampling option: '%s'\n", str);
		वापस -EINVAL;
	पूर्ण

	अगर (!sz)
		sz = itr->शेष_aux_sample_size;

	अगर (!sz)
		sz = DEFAULT_AUX_SAMPLE_SIZE;

	/* Set aux_sample_size based on --aux-sample option */
	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel__is_group_leader(evsel)) अणु
			has_aux_leader = evsel__is_aux_event(evsel);
		पूर्ण अन्यथा अगर (has_aux_leader) अणु
			evsel->core.attr.aux_sample_size = sz;
		पूर्ण
	पूर्ण
no_opt:
	aux_evsel = शून्य;
	/* Override with aux_sample_size from config term */
	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel__is_aux_event(evsel))
			aux_evsel = evsel;
		term = evsel__get_config_term(evsel, AUX_SAMPLE_SIZE);
		अगर (term) अणु
			has_aux_sample_size = true;
			evsel->core.attr.aux_sample_size = term->val.aux_sample_size;
			/* If possible, group with the AUX event */
			अगर (aux_evsel && evsel->core.attr.aux_sample_size)
				evlist__regroup(evlist, aux_evsel, evsel);
		पूर्ण
	पूर्ण

	अगर (!str && !has_aux_sample_size)
		वापस 0;

	अगर (!itr) अणु
		pr_err("No AUX area event to sample\n");
		वापस -EINVAL;
	पूर्ण

	वापस auxtrace_validate_aux_sample_size(evlist, opts);
पूर्ण

व्योम auxtrace_regroup_aux_output(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel, *aux_evsel = शून्य;
	काष्ठा evsel_config_term *term;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel__is_aux_event(evsel))
			aux_evsel = evsel;
		term = evsel__get_config_term(evsel, AUX_OUTPUT);
		/* If possible, group with the AUX event */
		अगर (term && aux_evsel)
			evlist__regroup(evlist, aux_evsel, evsel);
	पूर्ण
पूर्ण

काष्ठा auxtrace_record *__weak
auxtrace_record__init(काष्ठा evlist *evlist __maybe_unused, पूर्णांक *err)
अणु
	*err = 0;
	वापस शून्य;
पूर्ण

अटल पूर्णांक auxtrace_index__alloc(काष्ठा list_head *head)
अणु
	काष्ठा auxtrace_index *auxtrace_index;

	auxtrace_index = दो_स्मृति(माप(काष्ठा auxtrace_index));
	अगर (!auxtrace_index)
		वापस -ENOMEM;

	auxtrace_index->nr = 0;
	INIT_LIST_HEAD(&auxtrace_index->list);

	list_add_tail(&auxtrace_index->list, head);

	वापस 0;
पूर्ण

व्योम auxtrace_index__मुक्त(काष्ठा list_head *head)
अणु
	काष्ठा auxtrace_index *auxtrace_index, *n;

	list_क्रम_each_entry_safe(auxtrace_index, n, head, list) अणु
		list_del_init(&auxtrace_index->list);
		मुक्त(auxtrace_index);
	पूर्ण
पूर्ण

अटल काष्ठा auxtrace_index *auxtrace_index__last(काष्ठा list_head *head)
अणु
	काष्ठा auxtrace_index *auxtrace_index;
	पूर्णांक err;

	अगर (list_empty(head)) अणु
		err = auxtrace_index__alloc(head);
		अगर (err)
			वापस शून्य;
	पूर्ण

	auxtrace_index = list_entry(head->prev, काष्ठा auxtrace_index, list);

	अगर (auxtrace_index->nr >= PERF_AUXTRACE_INDEX_ENTRY_COUNT) अणु
		err = auxtrace_index__alloc(head);
		अगर (err)
			वापस शून्य;
		auxtrace_index = list_entry(head->prev, काष्ठा auxtrace_index,
					    list);
	पूर्ण

	वापस auxtrace_index;
पूर्ण

पूर्णांक auxtrace_index__auxtrace_event(काष्ठा list_head *head,
				   जोड़ perf_event *event, off_t file_offset)
अणु
	काष्ठा auxtrace_index *auxtrace_index;
	माप_प्रकार nr;

	auxtrace_index = auxtrace_index__last(head);
	अगर (!auxtrace_index)
		वापस -ENOMEM;

	nr = auxtrace_index->nr;
	auxtrace_index->entries[nr].file_offset = file_offset;
	auxtrace_index->entries[nr].sz = event->header.size;
	auxtrace_index->nr += 1;

	वापस 0;
पूर्ण

अटल पूर्णांक auxtrace_index__करो_ग_लिखो(पूर्णांक fd,
				    काष्ठा auxtrace_index *auxtrace_index)
अणु
	काष्ठा auxtrace_index_entry ent;
	माप_प्रकार i;

	क्रम (i = 0; i < auxtrace_index->nr; i++) अणु
		ent.file_offset = auxtrace_index->entries[i].file_offset;
		ent.sz = auxtrace_index->entries[i].sz;
		अगर (ग_लिखोn(fd, &ent, माप(ent)) != माप(ent))
			वापस -त्रुटि_सं;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक auxtrace_index__ग_लिखो(पूर्णांक fd, काष्ठा list_head *head)
अणु
	काष्ठा auxtrace_index *auxtrace_index;
	u64 total = 0;
	पूर्णांक err;

	list_क्रम_each_entry(auxtrace_index, head, list)
		total += auxtrace_index->nr;

	अगर (ग_लिखोn(fd, &total, माप(total)) != माप(total))
		वापस -त्रुटि_सं;

	list_क्रम_each_entry(auxtrace_index, head, list) अणु
		err = auxtrace_index__करो_ग_लिखो(fd, auxtrace_index);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक auxtrace_index__process_entry(पूर्णांक fd, काष्ठा list_head *head,
					 bool needs_swap)
अणु
	काष्ठा auxtrace_index *auxtrace_index;
	काष्ठा auxtrace_index_entry ent;
	माप_प्रकार nr;

	अगर (पढ़ोn(fd, &ent, माप(ent)) != माप(ent))
		वापस -1;

	auxtrace_index = auxtrace_index__last(head);
	अगर (!auxtrace_index)
		वापस -1;

	nr = auxtrace_index->nr;
	अगर (needs_swap) अणु
		auxtrace_index->entries[nr].file_offset =
						bswap_64(ent.file_offset);
		auxtrace_index->entries[nr].sz = bswap_64(ent.sz);
	पूर्ण अन्यथा अणु
		auxtrace_index->entries[nr].file_offset = ent.file_offset;
		auxtrace_index->entries[nr].sz = ent.sz;
	पूर्ण

	auxtrace_index->nr = nr + 1;

	वापस 0;
पूर्ण

पूर्णांक auxtrace_index__process(पूर्णांक fd, u64 size, काष्ठा perf_session *session,
			    bool needs_swap)
अणु
	काष्ठा list_head *head = &session->auxtrace_index;
	u64 nr;

	अगर (पढ़ोn(fd, &nr, माप(u64)) != माप(u64))
		वापस -1;

	अगर (needs_swap)
		nr = bswap_64(nr);

	अगर (माप(u64) + nr * माप(काष्ठा auxtrace_index_entry) > size)
		वापस -1;

	जबतक (nr--) अणु
		पूर्णांक err;

		err = auxtrace_index__process_entry(fd, head, needs_swap);
		अगर (err)
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक auxtrace_queues__process_index_entry(काष्ठा auxtrace_queues *queues,
						काष्ठा perf_session *session,
						काष्ठा auxtrace_index_entry *ent)
अणु
	वापस auxtrace_queues__add_indexed_event(queues, session,
						  ent->file_offset, ent->sz);
पूर्ण

पूर्णांक auxtrace_queues__process_index(काष्ठा auxtrace_queues *queues,
				   काष्ठा perf_session *session)
अणु
	काष्ठा auxtrace_index *auxtrace_index;
	काष्ठा auxtrace_index_entry *ent;
	माप_प्रकार i;
	पूर्णांक err;

	अगर (auxtrace__करोnt_decode(session))
		वापस 0;

	list_क्रम_each_entry(auxtrace_index, &session->auxtrace_index, list) अणु
		क्रम (i = 0; i < auxtrace_index->nr; i++) अणु
			ent = &auxtrace_index->entries[i];
			err = auxtrace_queues__process_index_entry(queues,
								   session,
								   ent);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा auxtrace_buffer *auxtrace_buffer__next(काष्ठा auxtrace_queue *queue,
					      काष्ठा auxtrace_buffer *buffer)
अणु
	अगर (buffer) अणु
		अगर (list_is_last(&buffer->list, &queue->head))
			वापस शून्य;
		वापस list_entry(buffer->list.next, काष्ठा auxtrace_buffer,
				  list);
	पूर्ण अन्यथा अणु
		अगर (list_empty(&queue->head))
			वापस शून्य;
		वापस list_entry(queue->head.next, काष्ठा auxtrace_buffer,
				  list);
	पूर्ण
पूर्ण

काष्ठा auxtrace_queue *auxtrace_queues__sample_queue(काष्ठा auxtrace_queues *queues,
						     काष्ठा perf_sample *sample,
						     काष्ठा perf_session *session)
अणु
	काष्ठा perf_sample_id *sid;
	अचिन्हित पूर्णांक idx;
	u64 id;

	id = sample->id;
	अगर (!id)
		वापस शून्य;

	sid = evlist__id2sid(session->evlist, id);
	अगर (!sid)
		वापस शून्य;

	idx = sid->idx;

	अगर (idx >= queues->nr_queues)
		वापस शून्य;

	वापस &queues->queue_array[idx];
पूर्ण

पूर्णांक auxtrace_queues__add_sample(काष्ठा auxtrace_queues *queues,
				काष्ठा perf_session *session,
				काष्ठा perf_sample *sample, u64 data_offset,
				u64 reference)
अणु
	काष्ठा auxtrace_buffer buffer = अणु
		.pid = -1,
		.data_offset = data_offset,
		.reference = reference,
		.size = sample->aux_sample.size,
	पूर्ण;
	काष्ठा perf_sample_id *sid;
	u64 id = sample->id;
	अचिन्हित पूर्णांक idx;

	अगर (!id)
		वापस -EINVAL;

	sid = evlist__id2sid(session->evlist, id);
	अगर (!sid)
		वापस -ENOENT;

	idx = sid->idx;
	buffer.tid = sid->tid;
	buffer.cpu = sid->cpu;

	वापस auxtrace_queues__add_buffer(queues, session, idx, &buffer, शून्य);
पूर्ण

काष्ठा queue_data अणु
	bool samples;
	bool events;
पूर्ण;

अटल पूर्णांक auxtrace_queue_data_cb(काष्ठा perf_session *session,
				  जोड़ perf_event *event, u64 offset,
				  व्योम *data)
अणु
	काष्ठा queue_data *qd = data;
	काष्ठा perf_sample sample;
	पूर्णांक err;

	अगर (qd->events && event->header.type == PERF_RECORD_AUXTRACE) अणु
		अगर (event->header.size < माप(काष्ठा perf_record_auxtrace))
			वापस -EINVAL;
		offset += event->header.size;
		वापस session->auxtrace->queue_data(session, शून्य, event,
						     offset);
	पूर्ण

	अगर (!qd->samples || event->header.type != PERF_RECORD_SAMPLE)
		वापस 0;

	err = evlist__parse_sample(session->evlist, event, &sample);
	अगर (err)
		वापस err;

	अगर (!sample.aux_sample.size)
		वापस 0;

	offset += sample.aux_sample.data - (व्योम *)event;

	वापस session->auxtrace->queue_data(session, &sample, शून्य, offset);
पूर्ण

पूर्णांक auxtrace_queue_data(काष्ठा perf_session *session, bool samples, bool events)
अणु
	काष्ठा queue_data qd = अणु
		.samples = samples,
		.events = events,
	पूर्ण;

	अगर (auxtrace__करोnt_decode(session))
		वापस 0;

	अगर (!session->auxtrace || !session->auxtrace->queue_data)
		वापस -EINVAL;

	वापस perf_session__peek_events(session, session->header.data_offset,
					 session->header.data_size,
					 auxtrace_queue_data_cb, &qd);
पूर्ण

व्योम *auxtrace_buffer__get_data(काष्ठा auxtrace_buffer *buffer, पूर्णांक fd)
अणु
	माप_प्रकार adj = buffer->data_offset & (page_size - 1);
	माप_प्रकार size = buffer->size + adj;
	off_t file_offset = buffer->data_offset - adj;
	व्योम *addr;

	अगर (buffer->data)
		वापस buffer->data;

	addr = mmap(शून्य, size, PROT_READ, MAP_SHARED, fd, file_offset);
	अगर (addr == MAP_FAILED)
		वापस शून्य;

	buffer->mmap_addr = addr;
	buffer->mmap_size = size;

	buffer->data = addr + adj;

	वापस buffer->data;
पूर्ण

व्योम auxtrace_buffer__put_data(काष्ठा auxtrace_buffer *buffer)
अणु
	अगर (!buffer->data || !buffer->mmap_addr)
		वापस;
	munmap(buffer->mmap_addr, buffer->mmap_size);
	buffer->mmap_addr = शून्य;
	buffer->mmap_size = 0;
	buffer->data = शून्य;
	buffer->use_data = शून्य;
पूर्ण

व्योम auxtrace_buffer__drop_data(काष्ठा auxtrace_buffer *buffer)
अणु
	auxtrace_buffer__put_data(buffer);
	अगर (buffer->data_needs_मुक्तing) अणु
		buffer->data_needs_मुक्तing = false;
		zमुक्त(&buffer->data);
		buffer->use_data = शून्य;
		buffer->size = 0;
	पूर्ण
पूर्ण

व्योम auxtrace_buffer__मुक्त(काष्ठा auxtrace_buffer *buffer)
अणु
	auxtrace_buffer__drop_data(buffer);
	मुक्त(buffer);
पूर्ण

व्योम auxtrace_synth_error(काष्ठा perf_record_auxtrace_error *auxtrace_error, पूर्णांक type,
			  पूर्णांक code, पूर्णांक cpu, pid_t pid, pid_t tid, u64 ip,
			  स्थिर अक्षर *msg, u64 बारtamp)
अणु
	माप_प्रकार size;

	स_रखो(auxtrace_error, 0, माप(काष्ठा perf_record_auxtrace_error));

	auxtrace_error->header.type = PERF_RECORD_AUXTRACE_ERROR;
	auxtrace_error->type = type;
	auxtrace_error->code = code;
	auxtrace_error->cpu = cpu;
	auxtrace_error->pid = pid;
	auxtrace_error->tid = tid;
	auxtrace_error->fmt = 1;
	auxtrace_error->ip = ip;
	auxtrace_error->समय = बारtamp;
	strlcpy(auxtrace_error->msg, msg, MAX_AUXTRACE_ERROR_MSG);

	size = (व्योम *)auxtrace_error->msg - (व्योम *)auxtrace_error +
	       म_माप(auxtrace_error->msg) + 1;
	auxtrace_error->header.size = PERF_ALIGN(size, माप(u64));
पूर्ण

पूर्णांक perf_event__synthesize_auxtrace_info(काष्ठा auxtrace_record *itr,
					 काष्ठा perf_tool *tool,
					 काष्ठा perf_session *session,
					 perf_event__handler_t process)
अणु
	जोड़ perf_event *ev;
	माप_प्रकार priv_size;
	पूर्णांक err;

	pr_debug2("Synthesizing auxtrace information\n");
	priv_size = auxtrace_record__info_priv_size(itr, session->evlist);
	ev = zalloc(माप(काष्ठा perf_record_auxtrace_info) + priv_size);
	अगर (!ev)
		वापस -ENOMEM;

	ev->auxtrace_info.header.type = PERF_RECORD_AUXTRACE_INFO;
	ev->auxtrace_info.header.size = माप(काष्ठा perf_record_auxtrace_info) +
					priv_size;
	err = auxtrace_record__info_fill(itr, session, &ev->auxtrace_info,
					 priv_size);
	अगर (err)
		जाओ out_मुक्त;

	err = process(tool, ev, शून्य, शून्य);
out_मुक्त:
	मुक्त(ev);
	वापस err;
पूर्ण

अटल व्योम unleader_evsel(काष्ठा evlist *evlist, काष्ठा evsel *leader)
अणु
	काष्ठा evsel *new_leader = शून्य;
	काष्ठा evsel *evsel;

	/* Find new leader क्रम the group */
	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->leader != leader || evsel == leader)
			जारी;
		अगर (!new_leader)
			new_leader = evsel;
		evsel->leader = new_leader;
	पूर्ण

	/* Update group inक्रमmation */
	अगर (new_leader) अणु
		zमुक्त(&new_leader->group_name);
		new_leader->group_name = leader->group_name;
		leader->group_name = शून्य;

		new_leader->core.nr_members = leader->core.nr_members - 1;
		leader->core.nr_members = 1;
	पूर्ण
पूर्ण

अटल व्योम unleader_auxtrace(काष्ठा perf_session *session)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(session->evlist, evsel) अणु
		अगर (auxtrace__evsel_is_auxtrace(session, evsel) &&
		    evsel__is_group_leader(evsel)) अणु
			unleader_evsel(session->evlist, evsel);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक perf_event__process_auxtrace_info(काष्ठा perf_session *session,
				      जोड़ perf_event *event)
अणु
	क्रमागत auxtrace_type type = event->auxtrace_info.type;
	पूर्णांक err;

	अगर (dump_trace)
		ख_लिखो(मानक_निकास, " type: %u\n", type);

	चयन (type) अणु
	हाल PERF_AUXTRACE_INTEL_PT:
		err = पूर्णांकel_pt_process_auxtrace_info(event, session);
		अवरोध;
	हाल PERF_AUXTRACE_INTEL_BTS:
		err = पूर्णांकel_bts_process_auxtrace_info(event, session);
		अवरोध;
	हाल PERF_AUXTRACE_ARM_SPE:
		err = arm_spe_process_auxtrace_info(event, session);
		अवरोध;
	हाल PERF_AUXTRACE_CS_ETM:
		err = cs_eपंचांग__process_auxtrace_info(event, session);
		अवरोध;
	हाल PERF_AUXTRACE_S390_CPUMSF:
		err = s390_cpumsf_process_auxtrace_info(event, session);
		अवरोध;
	हाल PERF_AUXTRACE_UNKNOWN:
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (err)
		वापस err;

	unleader_auxtrace(session);

	वापस 0;
पूर्ण

s64 perf_event__process_auxtrace(काष्ठा perf_session *session,
				 जोड़ perf_event *event)
अणु
	s64 err;

	अगर (dump_trace)
		ख_लिखो(मानक_निकास, " size: %#"PRI_lx64"  offset: %#"PRI_lx64"  ref: %#"PRI_lx64"  idx: %u  tid: %d  cpu: %d\n",
			event->auxtrace.size, event->auxtrace.offset,
			event->auxtrace.reference, event->auxtrace.idx,
			event->auxtrace.tid, event->auxtrace.cpu);

	अगर (auxtrace__करोnt_decode(session))
		वापस event->auxtrace.size;

	अगर (!session->auxtrace || event->header.type != PERF_RECORD_AUXTRACE)
		वापस -EINVAL;

	err = session->auxtrace->process_auxtrace_event(session, event, session->tool);
	अगर (err < 0)
		वापस err;

	वापस event->auxtrace.size;
पूर्ण

#घोषणा PERF_ITRACE_DEFAULT_PERIOD_TYPE		PERF_ITRACE_PERIOD_न_अंकOSECS
#घोषणा PERF_ITRACE_DEFAULT_PERIOD		100000
#घोषणा PERF_ITRACE_DEFAULT_CALLCHAIN_SZ	16
#घोषणा PERF_ITRACE_MAX_CALLCHAIN_SZ		1024
#घोषणा PERF_ITRACE_DEFAULT_LAST_BRANCH_SZ	64
#घोषणा PERF_ITRACE_MAX_LAST_BRANCH_SZ		1024

व्योम itrace_synth_opts__set_शेष(काष्ठा itrace_synth_opts *synth_opts,
				    bool no_sample)
अणु
	synth_opts->branches = true;
	synth_opts->transactions = true;
	synth_opts->ptग_लिखोs = true;
	synth_opts->pwr_events = true;
	synth_opts->other_events = true;
	synth_opts->errors = true;
	synth_opts->flc = true;
	synth_opts->llc = true;
	synth_opts->tlb = true;
	synth_opts->mem = true;
	synth_opts->remote_access = true;

	अगर (no_sample) अणु
		synth_opts->period_type = PERF_ITRACE_PERIOD_INSTRUCTIONS;
		synth_opts->period = 1;
		synth_opts->calls = true;
	पूर्ण अन्यथा अणु
		synth_opts->inकाष्ठाions = true;
		synth_opts->period_type = PERF_ITRACE_DEFAULT_PERIOD_TYPE;
		synth_opts->period = PERF_ITRACE_DEFAULT_PERIOD;
	पूर्ण
	synth_opts->callchain_sz = PERF_ITRACE_DEFAULT_CALLCHAIN_SZ;
	synth_opts->last_branch_sz = PERF_ITRACE_DEFAULT_LAST_BRANCH_SZ;
	synth_opts->initial_skip = 0;
पूर्ण

अटल पूर्णांक get_flag(स्थिर अक्षर **ptr, अचिन्हित पूर्णांक *flags)
अणु
	जबतक (1) अणु
		अक्षर c = **ptr;

		अगर (c >= 'a' && c <= 'z') अणु
			*flags |= 1 << (c - 'a');
			++*ptr;
			वापस 0;
		पूर्ण अन्यथा अगर (c == ' ') अणु
			++*ptr;
			जारी;
		पूर्ण अन्यथा अणु
			वापस -1;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक get_flags(स्थिर अक्षर **ptr, अचिन्हित पूर्णांक *plus_flags, अचिन्हित पूर्णांक *minus_flags)
अणु
	जबतक (1) अणु
		चयन (**ptr) अणु
		हाल '+':
			++*ptr;
			अगर (get_flag(ptr, plus_flags))
				वापस -1;
			अवरोध;
		हाल '-':
			++*ptr;
			अगर (get_flag(ptr, minus_flags))
				वापस -1;
			अवरोध;
		हाल ' ':
			++*ptr;
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Please check tools/perf/Documentation/perf-script.txt क्रम inक्रमmation
 * about the options parsed here, which is पूर्णांकroduced after this cset,
 * when support in 'perf script' क्रम these options is पूर्णांकroduced.
 */
पूर्णांक itrace_parse_synth_opts(स्थिर काष्ठा option *opt, स्थिर अक्षर *str,
			    पूर्णांक unset)
अणु
	काष्ठा itrace_synth_opts *synth_opts = opt->value;
	स्थिर अक्षर *p;
	अक्षर *endptr;
	bool period_type_set = false;
	bool period_set = false;

	synth_opts->set = true;

	अगर (unset) अणु
		synth_opts->करोnt_decode = true;
		वापस 0;
	पूर्ण

	अगर (!str) अणु
		itrace_synth_opts__set_शेष(synth_opts,
					       synth_opts->शेष_no_sample);
		वापस 0;
	पूर्ण

	क्रम (p = str; *p;) अणु
		चयन (*p++) अणु
		हाल 'i':
			synth_opts->inकाष्ठाions = true;
			जबतक (*p == ' ' || *p == ',')
				p += 1;
			अगर (है_अंक(*p)) अणु
				synth_opts->period = म_से_अदीर्घl(p, &endptr, 10);
				period_set = true;
				p = endptr;
				जबतक (*p == ' ' || *p == ',')
					p += 1;
				चयन (*p++) अणु
				हाल 'i':
					synth_opts->period_type =
						PERF_ITRACE_PERIOD_INSTRUCTIONS;
					period_type_set = true;
					अवरोध;
				हाल 't':
					synth_opts->period_type =
						PERF_ITRACE_PERIOD_TICKS;
					period_type_set = true;
					अवरोध;
				हाल 'm':
					synth_opts->period *= 1000;
					/* Fall through */
				हाल 'u':
					synth_opts->period *= 1000;
					/* Fall through */
				हाल 'n':
					अगर (*p++ != 's')
						जाओ out_err;
					synth_opts->period_type =
						PERF_ITRACE_PERIOD_न_अंकOSECS;
					period_type_set = true;
					अवरोध;
				हाल '\0':
					जाओ out;
				शेष:
					जाओ out_err;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल 'b':
			synth_opts->branches = true;
			अवरोध;
		हाल 'x':
			synth_opts->transactions = true;
			अवरोध;
		हाल 'w':
			synth_opts->ptग_लिखोs = true;
			अवरोध;
		हाल 'p':
			synth_opts->pwr_events = true;
			अवरोध;
		हाल 'o':
			synth_opts->other_events = true;
			अवरोध;
		हाल 'e':
			synth_opts->errors = true;
			अगर (get_flags(&p, &synth_opts->error_plus_flags,
				      &synth_opts->error_minus_flags))
				जाओ out_err;
			अवरोध;
		हाल 'd':
			synth_opts->log = true;
			अगर (get_flags(&p, &synth_opts->log_plus_flags,
				      &synth_opts->log_minus_flags))
				जाओ out_err;
			अवरोध;
		हाल 'c':
			synth_opts->branches = true;
			synth_opts->calls = true;
			अवरोध;
		हाल 'r':
			synth_opts->branches = true;
			synth_opts->वापसs = true;
			अवरोध;
		हाल 'G':
		हाल 'g':
			अगर (p[-1] == 'G')
				synth_opts->add_callchain = true;
			अन्यथा
				synth_opts->callchain = true;
			synth_opts->callchain_sz =
					PERF_ITRACE_DEFAULT_CALLCHAIN_SZ;
			जबतक (*p == ' ' || *p == ',')
				p += 1;
			अगर (है_अंक(*p)) अणु
				अचिन्हित पूर्णांक val;

				val = म_से_अदीर्घ(p, &endptr, 10);
				p = endptr;
				अगर (!val || val > PERF_ITRACE_MAX_CALLCHAIN_SZ)
					जाओ out_err;
				synth_opts->callchain_sz = val;
			पूर्ण
			अवरोध;
		हाल 'L':
		हाल 'l':
			अगर (p[-1] == 'L')
				synth_opts->add_last_branch = true;
			अन्यथा
				synth_opts->last_branch = true;
			synth_opts->last_branch_sz =
					PERF_ITRACE_DEFAULT_LAST_BRANCH_SZ;
			जबतक (*p == ' ' || *p == ',')
				p += 1;
			अगर (है_अंक(*p)) अणु
				अचिन्हित पूर्णांक val;

				val = म_से_अदीर्घ(p, &endptr, 10);
				p = endptr;
				अगर (!val ||
				    val > PERF_ITRACE_MAX_LAST_BRANCH_SZ)
					जाओ out_err;
				synth_opts->last_branch_sz = val;
			पूर्ण
			अवरोध;
		हाल 's':
			synth_opts->initial_skip = म_से_अदीर्घ(p, &endptr, 10);
			अगर (p == endptr)
				जाओ out_err;
			p = endptr;
			अवरोध;
		हाल 'f':
			synth_opts->flc = true;
			अवरोध;
		हाल 'm':
			synth_opts->llc = true;
			अवरोध;
		हाल 't':
			synth_opts->tlb = true;
			अवरोध;
		हाल 'a':
			synth_opts->remote_access = true;
			अवरोध;
		हाल 'M':
			synth_opts->mem = true;
			अवरोध;
		हाल 'q':
			synth_opts->quick += 1;
			अवरोध;
		हाल ' ':
		हाल ',':
			अवरोध;
		शेष:
			जाओ out_err;
		पूर्ण
	पूर्ण
out:
	अगर (synth_opts->inकाष्ठाions) अणु
		अगर (!period_type_set)
			synth_opts->period_type =
					PERF_ITRACE_DEFAULT_PERIOD_TYPE;
		अगर (!period_set)
			synth_opts->period = PERF_ITRACE_DEFAULT_PERIOD;
	पूर्ण

	वापस 0;

out_err:
	pr_err("Bad Instruction Tracing options '%s'\n", str);
	वापस -EINVAL;
पूर्ण

अटल स्थिर अक्षर * स्थिर auxtrace_error_type_name[] = अणु
	[PERF_AUXTRACE_ERROR_ITRACE] = "instruction trace",
पूर्ण;

अटल स्थिर अक्षर *auxtrace_error_name(पूर्णांक type)
अणु
	स्थिर अक्षर *error_type_name = शून्य;

	अगर (type < PERF_AUXTRACE_ERROR_MAX)
		error_type_name = auxtrace_error_type_name[type];
	अगर (!error_type_name)
		error_type_name = "unknown AUX";
	वापस error_type_name;
पूर्ण

माप_प्रकार perf_event__ख_लिखो_auxtrace_error(जोड़ perf_event *event, खाता *fp)
अणु
	काष्ठा perf_record_auxtrace_error *e = &event->auxtrace_error;
	अचिन्हित दीर्घ दीर्घ nsecs = e->समय;
	स्थिर अक्षर *msg = e->msg;
	पूर्णांक ret;

	ret = ख_लिखो(fp, " %s error type %u",
		      auxtrace_error_name(e->type), e->type);

	अगर (e->fmt && nsecs) अणु
		अचिन्हित दीर्घ secs = nsecs / NSEC_PER_SEC;

		nsecs -= secs * NSEC_PER_SEC;
		ret += ख_लिखो(fp, " time %lu.%09llu", secs, nsecs);
	पूर्ण अन्यथा अणु
		ret += ख_लिखो(fp, " time 0");
	पूर्ण

	अगर (!e->fmt)
		msg = (स्थिर अक्षर *)&e->समय;

	ret += ख_लिखो(fp, " cpu %d pid %d tid %d ip %#"PRI_lx64" code %u: %s\n",
		       e->cpu, e->pid, e->tid, e->ip, e->code, msg);
	वापस ret;
पूर्ण

व्योम perf_session__auxtrace_error_inc(काष्ठा perf_session *session,
				      जोड़ perf_event *event)
अणु
	काष्ठा perf_record_auxtrace_error *e = &event->auxtrace_error;

	अगर (e->type < PERF_AUXTRACE_ERROR_MAX)
		session->evlist->stats.nr_auxtrace_errors[e->type] += 1;
पूर्ण

व्योम events_stats__auxtrace_error_warn(स्थिर काष्ठा events_stats *stats)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PERF_AUXTRACE_ERROR_MAX; i++) अणु
		अगर (!stats->nr_auxtrace_errors[i])
			जारी;
		ui__warning("%u %s errors\n",
			    stats->nr_auxtrace_errors[i],
			    auxtrace_error_name(i));
	पूर्ण
पूर्ण

पूर्णांक perf_event__process_auxtrace_error(काष्ठा perf_session *session,
				       जोड़ perf_event *event)
अणु
	अगर (auxtrace__करोnt_decode(session))
		वापस 0;

	perf_event__ख_लिखो_auxtrace_error(event, मानक_निकास);
	वापस 0;
पूर्ण

अटल पूर्णांक __auxtrace_mmap__पढ़ो(काष्ठा mmap *map,
				 काष्ठा auxtrace_record *itr,
				 काष्ठा perf_tool *tool, process_auxtrace_t fn,
				 bool snapshot, माप_प्रकार snapshot_size)
अणु
	काष्ठा auxtrace_mmap *mm = &map->auxtrace_mmap;
	u64 head, old = mm->prev, offset, ref;
	अचिन्हित अक्षर *data = mm->base;
	माप_प्रकार size, head_off, old_off, len1, len2, padding;
	जोड़ perf_event ev;
	व्योम *data1, *data2;

	अगर (snapshot) अणु
		head = auxtrace_mmap__पढ़ो_snapshot_head(mm);
		अगर (auxtrace_record__find_snapshot(itr, mm->idx, mm, data,
						   &head, &old))
			वापस -1;
	पूर्ण अन्यथा अणु
		head = auxtrace_mmap__पढ़ो_head(mm);
	पूर्ण

	अगर (old == head)
		वापस 0;

	pr_debug3("auxtrace idx %d old %#"PRIx64" head %#"PRIx64" diff %#"PRIx64"\n",
		  mm->idx, old, head, head - old);

	अगर (mm->mask) अणु
		head_off = head & mm->mask;
		old_off = old & mm->mask;
	पूर्ण अन्यथा अणु
		head_off = head % mm->len;
		old_off = old % mm->len;
	पूर्ण

	अगर (head_off > old_off)
		size = head_off - old_off;
	अन्यथा
		size = mm->len - (old_off - head_off);

	अगर (snapshot && size > snapshot_size)
		size = snapshot_size;

	ref = auxtrace_record__reference(itr);

	अगर (head > old || size <= head || mm->mask) अणु
		offset = head - size;
	पूर्ण अन्यथा अणु
		/*
		 * When the buffer size is not a घातer of 2, 'head' wraps at the
		 * highest multiple of the buffer size, so we have to subtract
		 * the reमुख्यder here.
		 */
		u64 rem = (0ULL - mm->len) % mm->len;

		offset = head - size - rem;
	पूर्ण

	अगर (size > head_off) अणु
		len1 = size - head_off;
		data1 = &data[mm->len - len1];
		len2 = head_off;
		data2 = &data[0];
	पूर्ण अन्यथा अणु
		len1 = size;
		data1 = &data[head_off - len1];
		len2 = 0;
		data2 = शून्य;
	पूर्ण

	अगर (itr->alignment) अणु
		अचिन्हित पूर्णांक unwanted = len1 % itr->alignment;

		len1 -= unwanted;
		size -= unwanted;
	पूर्ण

	/* padding must be written by fn() e.g. record__process_auxtrace() */
	padding = size & (PERF_AUXTRACE_RECORD_ALIGNMENT - 1);
	अगर (padding)
		padding = PERF_AUXTRACE_RECORD_ALIGNMENT - padding;

	स_रखो(&ev, 0, माप(ev));
	ev.auxtrace.header.type = PERF_RECORD_AUXTRACE;
	ev.auxtrace.header.size = माप(ev.auxtrace);
	ev.auxtrace.size = size + padding;
	ev.auxtrace.offset = offset;
	ev.auxtrace.reference = ref;
	ev.auxtrace.idx = mm->idx;
	ev.auxtrace.tid = mm->tid;
	ev.auxtrace.cpu = mm->cpu;

	अगर (fn(tool, map, &ev, data1, len1, data2, len2))
		वापस -1;

	mm->prev = head;

	अगर (!snapshot) अणु
		auxtrace_mmap__ग_लिखो_tail(mm, head);
		अगर (itr->पढ़ो_finish) अणु
			पूर्णांक err;

			err = itr->पढ़ो_finish(itr, mm->idx);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक auxtrace_mmap__पढ़ो(काष्ठा mmap *map, काष्ठा auxtrace_record *itr,
			काष्ठा perf_tool *tool, process_auxtrace_t fn)
अणु
	वापस __auxtrace_mmap__पढ़ो(map, itr, tool, fn, false, 0);
पूर्ण

पूर्णांक auxtrace_mmap__पढ़ो_snapshot(काष्ठा mmap *map,
				 काष्ठा auxtrace_record *itr,
				 काष्ठा perf_tool *tool, process_auxtrace_t fn,
				 माप_प्रकार snapshot_size)
अणु
	वापस __auxtrace_mmap__पढ़ो(map, itr, tool, fn, true, snapshot_size);
पूर्ण

/**
 * काष्ठा auxtrace_cache - hash table to implement a cache
 * @hashtable: the hashtable
 * @sz: hashtable size (number of hlists)
 * @entry_size: size of an entry
 * @limit: limit the number of entries to this maximum, when reached the cache
 *         is dropped and caching begins again with an empty cache
 * @cnt: current number of entries
 * @bits: hashtable size (@sz = 2^@bits)
 */
काष्ठा auxtrace_cache अणु
	काष्ठा hlist_head *hashtable;
	माप_प्रकार sz;
	माप_प्रकार entry_size;
	माप_प्रकार limit;
	माप_प्रकार cnt;
	अचिन्हित पूर्णांक bits;
पूर्ण;

काष्ठा auxtrace_cache *auxtrace_cache__new(अचिन्हित पूर्णांक bits, माप_प्रकार entry_size,
					   अचिन्हित पूर्णांक limit_percent)
अणु
	काष्ठा auxtrace_cache *c;
	काष्ठा hlist_head *ht;
	माप_प्रकार sz, i;

	c = zalloc(माप(काष्ठा auxtrace_cache));
	अगर (!c)
		वापस शून्य;

	sz = 1UL << bits;

	ht = सुस्मृति(sz, माप(काष्ठा hlist_head));
	अगर (!ht)
		जाओ out_मुक्त;

	क्रम (i = 0; i < sz; i++)
		INIT_HLIST_HEAD(&ht[i]);

	c->hashtable = ht;
	c->sz = sz;
	c->entry_size = entry_size;
	c->limit = (c->sz * limit_percent) / 100;
	c->bits = bits;

	वापस c;

out_मुक्त:
	मुक्त(c);
	वापस शून्य;
पूर्ण

अटल व्योम auxtrace_cache__drop(काष्ठा auxtrace_cache *c)
अणु
	काष्ठा auxtrace_cache_entry *entry;
	काष्ठा hlist_node *पंचांगp;
	माप_प्रकार i;

	अगर (!c)
		वापस;

	क्रम (i = 0; i < c->sz; i++) अणु
		hlist_क्रम_each_entry_safe(entry, पंचांगp, &c->hashtable[i], hash) अणु
			hlist_del(&entry->hash);
			auxtrace_cache__मुक्त_entry(c, entry);
		पूर्ण
	पूर्ण

	c->cnt = 0;
पूर्ण

व्योम auxtrace_cache__मुक्त(काष्ठा auxtrace_cache *c)
अणु
	अगर (!c)
		वापस;

	auxtrace_cache__drop(c);
	zमुक्त(&c->hashtable);
	मुक्त(c);
पूर्ण

व्योम *auxtrace_cache__alloc_entry(काष्ठा auxtrace_cache *c)
अणु
	वापस दो_स्मृति(c->entry_size);
पूर्ण

व्योम auxtrace_cache__मुक्त_entry(काष्ठा auxtrace_cache *c __maybe_unused,
				व्योम *entry)
अणु
	मुक्त(entry);
पूर्ण

पूर्णांक auxtrace_cache__add(काष्ठा auxtrace_cache *c, u32 key,
			काष्ठा auxtrace_cache_entry *entry)
अणु
	अगर (c->limit && ++c->cnt > c->limit)
		auxtrace_cache__drop(c);

	entry->key = key;
	hlist_add_head(&entry->hash, &c->hashtable[hash_32(key, c->bits)]);

	वापस 0;
पूर्ण

अटल काष्ठा auxtrace_cache_entry *auxtrace_cache__rm(काष्ठा auxtrace_cache *c,
						       u32 key)
अणु
	काष्ठा auxtrace_cache_entry *entry;
	काष्ठा hlist_head *hlist;
	काष्ठा hlist_node *n;

	अगर (!c)
		वापस शून्य;

	hlist = &c->hashtable[hash_32(key, c->bits)];
	hlist_क्रम_each_entry_safe(entry, n, hlist, hash) अणु
		अगर (entry->key == key) अणु
			hlist_del(&entry->hash);
			वापस entry;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम auxtrace_cache__हटाओ(काष्ठा auxtrace_cache *c, u32 key)
अणु
	काष्ठा auxtrace_cache_entry *entry = auxtrace_cache__rm(c, key);

	auxtrace_cache__मुक्त_entry(c, entry);
पूर्ण

व्योम *auxtrace_cache__lookup(काष्ठा auxtrace_cache *c, u32 key)
अणु
	काष्ठा auxtrace_cache_entry *entry;
	काष्ठा hlist_head *hlist;

	अगर (!c)
		वापस शून्य;

	hlist = &c->hashtable[hash_32(key, c->bits)];
	hlist_क्रम_each_entry(entry, hlist, hash) अणु
		अगर (entry->key == key)
			वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम addr_filter__मुक्त_str(काष्ठा addr_filter *filt)
अणु
	zमुक्त(&filt->str);
	filt->action   = शून्य;
	filt->sym_from = शून्य;
	filt->sym_to   = शून्य;
	filt->filename = शून्य;
पूर्ण

अटल काष्ठा addr_filter *addr_filter__new(व्योम)
अणु
	काष्ठा addr_filter *filt = zalloc(माप(*filt));

	अगर (filt)
		INIT_LIST_HEAD(&filt->list);

	वापस filt;
पूर्ण

अटल व्योम addr_filter__मुक्त(काष्ठा addr_filter *filt)
अणु
	अगर (filt)
		addr_filter__मुक्त_str(filt);
	मुक्त(filt);
पूर्ण

अटल व्योम addr_filters__add(काष्ठा addr_filters *filts,
			      काष्ठा addr_filter *filt)
अणु
	list_add_tail(&filt->list, &filts->head);
	filts->cnt += 1;
पूर्ण

अटल व्योम addr_filters__del(काष्ठा addr_filters *filts,
			      काष्ठा addr_filter *filt)
अणु
	list_del_init(&filt->list);
	filts->cnt -= 1;
पूर्ण

व्योम addr_filters__init(काष्ठा addr_filters *filts)
अणु
	INIT_LIST_HEAD(&filts->head);
	filts->cnt = 0;
पूर्ण

व्योम addr_filters__निकास(काष्ठा addr_filters *filts)
अणु
	काष्ठा addr_filter *filt, *n;

	list_क्रम_each_entry_safe(filt, n, &filts->head, list) अणु
		addr_filters__del(filts, filt);
		addr_filter__मुक्त(filt);
	पूर्ण
पूर्ण

अटल पूर्णांक parse_num_or_str(अक्षर **inp, u64 *num, स्थिर अक्षर **str,
			    स्थिर अक्षर *str_delim)
अणु
	*inp += म_अखोज(*inp, " ");

	अगर (है_अंक(**inp)) अणु
		अक्षर *endptr;

		अगर (!num)
			वापस -EINVAL;
		त्रुटि_सं = 0;
		*num = म_से_अदीर्घl(*inp, &endptr, 0);
		अगर (त्रुटि_सं)
			वापस -त्रुटि_सं;
		अगर (endptr == *inp)
			वापस -EINVAL;
		*inp = endptr;
	पूर्ण अन्यथा अणु
		माप_प्रकार n;

		अगर (!str)
			वापस -EINVAL;
		*inp += म_अखोज(*inp, " ");
		*str = *inp;
		n = म_खोज(*inp, str_delim);
		अगर (!n)
			वापस -EINVAL;
		*inp += n;
		अगर (**inp) अणु
			**inp = '\0';
			*inp += 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक parse_action(काष्ठा addr_filter *filt)
अणु
	अगर (!म_भेद(filt->action, "filter")) अणु
		filt->start = true;
		filt->range = true;
	पूर्ण अन्यथा अगर (!म_भेद(filt->action, "start")) अणु
		filt->start = true;
	पूर्ण अन्यथा अगर (!म_भेद(filt->action, "stop")) अणु
		filt->start = false;
	पूर्ण अन्यथा अगर (!म_भेद(filt->action, "tracestop")) अणु
		filt->start = false;
		filt->range = true;
		filt->action += 5; /* Change 'tracestop' to 'stop' */
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक parse_sym_idx(अक्षर **inp, पूर्णांक *idx)
अणु
	*idx = -1;

	*inp += म_अखोज(*inp, " ");

	अगर (**inp != '#')
		वापस 0;

	*inp += 1;

	अगर (**inp == 'g' || **inp == 'G') अणु
		*inp += 1;
		*idx = 0;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ num;
		अक्षर *endptr;

		त्रुटि_सं = 0;
		num = म_से_अदीर्घ(*inp, &endptr, 0);
		अगर (त्रुटि_सं)
			वापस -त्रुटि_सं;
		अगर (endptr == *inp || num > पूर्णांक_उच्च)
			वापस -EINVAL;
		*inp = endptr;
		*idx = num;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक parse_addr_size(अक्षर **inp, u64 *num, स्थिर अक्षर **str, पूर्णांक *idx)
अणु
	पूर्णांक err = parse_num_or_str(inp, num, str, " ");

	अगर (!err && *str)
		err = parse_sym_idx(inp, idx);

	वापस err;
पूर्ण

अटल पूर्णांक parse_one_filter(काष्ठा addr_filter *filt, स्थिर अक्षर **filter_inp)
अणु
	अक्षर *fstr;
	पूर्णांक err;

	filt->str = fstr = strdup(*filter_inp);
	अगर (!fstr)
		वापस -ENOMEM;

	err = parse_num_or_str(&fstr, शून्य, &filt->action, " ");
	अगर (err)
		जाओ out_err;

	err = parse_action(filt);
	अगर (err)
		जाओ out_err;

	err = parse_addr_size(&fstr, &filt->addr, &filt->sym_from,
			      &filt->sym_from_idx);
	अगर (err)
		जाओ out_err;

	fstr += म_अखोज(fstr, " ");

	अगर (*fstr == '/') अणु
		fstr += 1;
		err = parse_addr_size(&fstr, &filt->size, &filt->sym_to,
				      &filt->sym_to_idx);
		अगर (err)
			जाओ out_err;
		filt->range = true;
	पूर्ण

	fstr += म_अखोज(fstr, " ");

	अगर (*fstr == '@') अणु
		fstr += 1;
		err = parse_num_or_str(&fstr, शून्य, &filt->filename, " ,");
		अगर (err)
			जाओ out_err;
	पूर्ण

	fstr += म_अखोज(fstr, " ,");

	*filter_inp += fstr - filt->str;

	वापस 0;

out_err:
	addr_filter__मुक्त_str(filt);

	वापस err;
पूर्ण

पूर्णांक addr_filters__parse_bare_filter(काष्ठा addr_filters *filts,
				    स्थिर अक्षर *filter)
अणु
	काष्ठा addr_filter *filt;
	स्थिर अक्षर *fstr = filter;
	पूर्णांक err;

	जबतक (*fstr) अणु
		filt = addr_filter__new();
		err = parse_one_filter(filt, &fstr);
		अगर (err) अणु
			addr_filter__मुक्त(filt);
			addr_filters__निकास(filts);
			वापस err;
		पूर्ण
		addr_filters__add(filts, filt);
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा sym_args अणु
	स्थिर अक्षर	*name;
	u64		start;
	u64		size;
	पूर्णांक		idx;
	पूर्णांक		cnt;
	bool		started;
	bool		global;
	bool		selected;
	bool		duplicate;
	bool		near;
पूर्ण;

अटल bool kern_sym_match(काष्ठा sym_args *args, स्थिर अक्षर *name, अक्षर type)
अणु
	/* A function with the same name, and global or the n'th found or any */
	वापस kallsyms__is_function(type) &&
	       !म_भेद(name, args->name) &&
	       ((args->global && है_बड़ा(type)) ||
		(args->selected && ++(args->cnt) == args->idx) ||
		(!args->global && !args->selected));
पूर्ण

अटल पूर्णांक find_kern_sym_cb(व्योम *arg, स्थिर अक्षर *name, अक्षर type, u64 start)
अणु
	काष्ठा sym_args *args = arg;

	अगर (args->started) अणु
		अगर (!args->size)
			args->size = start - args->start;
		अगर (args->selected) अणु
			अगर (args->size)
				वापस 1;
		पूर्ण अन्यथा अगर (kern_sym_match(args, name, type)) अणु
			args->duplicate = true;
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अगर (kern_sym_match(args, name, type)) अणु
		args->started = true;
		args->start = start;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक prपूर्णांक_kern_sym_cb(व्योम *arg, स्थिर अक्षर *name, अक्षर type, u64 start)
अणु
	काष्ठा sym_args *args = arg;

	अगर (kern_sym_match(args, name, type)) अणु
		pr_err("#%d\t0x%"PRIx64"\t%c\t%s\n",
		       ++args->cnt, start, type, name);
		args->near = true;
	पूर्ण अन्यथा अगर (args->near) अणु
		args->near = false;
		pr_err("\t\twhich is near\t\t%s\n", name);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sym_not_found_error(स्थिर अक्षर *sym_name, पूर्णांक idx)
अणु
	अगर (idx > 0) अणु
		pr_err("N'th occurrence (N=%d) of symbol '%s' not found.\n",
		       idx, sym_name);
	पूर्ण अन्यथा अगर (!idx) अणु
		pr_err("Global symbol '%s' not found.\n", sym_name);
	पूर्ण अन्यथा अणु
		pr_err("Symbol '%s' not found.\n", sym_name);
	पूर्ण
	pr_err("Note that symbols must be functions.\n");

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक find_kern_sym(स्थिर अक्षर *sym_name, u64 *start, u64 *size, पूर्णांक idx)
अणु
	काष्ठा sym_args args = अणु
		.name = sym_name,
		.idx = idx,
		.global = !idx,
		.selected = idx > 0,
	पूर्ण;
	पूर्णांक err;

	*start = 0;
	*size = 0;

	err = kallsyms__parse("/proc/kallsyms", &args, find_kern_sym_cb);
	अगर (err < 0) अणु
		pr_err("Failed to parse /proc/kallsyms\n");
		वापस err;
	पूर्ण

	अगर (args.duplicate) अणु
		pr_err("Multiple kernel symbols with name '%s'\n", sym_name);
		args.cnt = 0;
		kallsyms__parse("/proc/kallsyms", &args, prपूर्णांक_kern_sym_cb);
		pr_err("Disambiguate symbol name by inserting #n after the name e.g. %s #2\n",
		       sym_name);
		pr_err("Or select a global symbol by inserting #0 or #g or #G\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!args.started) अणु
		pr_err("Kernel symbol lookup: ");
		वापस sym_not_found_error(sym_name, idx);
	पूर्ण

	*start = args.start;
	*size = args.size;

	वापस 0;
पूर्ण

अटल पूर्णांक find_entire_kern_cb(व्योम *arg, स्थिर अक्षर *name __maybe_unused,
			       अक्षर type, u64 start)
अणु
	काष्ठा sym_args *args = arg;

	अगर (!kallsyms__is_function(type))
		वापस 0;

	अगर (!args->started) अणु
		args->started = true;
		args->start = start;
	पूर्ण
	/* Don't know exactly where the kernel ends, so we add a page */
	args->size = round_up(start, page_size) + page_size - args->start;

	वापस 0;
पूर्ण

अटल पूर्णांक addr_filter__entire_kernel(काष्ठा addr_filter *filt)
अणु
	काष्ठा sym_args args = अणु .started = false पूर्ण;
	पूर्णांक err;

	err = kallsyms__parse("/proc/kallsyms", &args, find_entire_kern_cb);
	अगर (err < 0 || !args.started) अणु
		pr_err("Failed to parse /proc/kallsyms\n");
		वापस err;
	पूर्ण

	filt->addr = args.start;
	filt->size = args.size;

	वापस 0;
पूर्ण

अटल पूर्णांक check_end_after_start(काष्ठा addr_filter *filt, u64 start, u64 size)
अणु
	अगर (start + size >= filt->addr)
		वापस 0;

	अगर (filt->sym_from) अणु
		pr_err("Symbol '%s' (0x%"PRIx64") comes before '%s' (0x%"PRIx64")\n",
		       filt->sym_to, start, filt->sym_from, filt->addr);
	पूर्ण अन्यथा अणु
		pr_err("Symbol '%s' (0x%"PRIx64") comes before address 0x%"PRIx64")\n",
		       filt->sym_to, start, filt->addr);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक addr_filter__resolve_kernel_syms(काष्ठा addr_filter *filt)
अणु
	bool no_size = false;
	u64 start, size;
	पूर्णांक err;

	अगर (symbol_conf.kptr_restrict) अणु
		pr_err("Kernel addresses are restricted. Unable to resolve kernel symbols.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (filt->sym_from && !म_भेद(filt->sym_from, "*"))
		वापस addr_filter__entire_kernel(filt);

	अगर (filt->sym_from) अणु
		err = find_kern_sym(filt->sym_from, &start, &size,
				    filt->sym_from_idx);
		अगर (err)
			वापस err;
		filt->addr = start;
		अगर (filt->range && !filt->size && !filt->sym_to) अणु
			filt->size = size;
			no_size = !size;
		पूर्ण
	पूर्ण

	अगर (filt->sym_to) अणु
		err = find_kern_sym(filt->sym_to, &start, &size,
				    filt->sym_to_idx);
		अगर (err)
			वापस err;

		err = check_end_after_start(filt, start, size);
		अगर (err)
			वापस err;
		filt->size = start + size - filt->addr;
		no_size = !size;
	पूर्ण

	/* The very last symbol in kallsyms करोes not imply a particular size */
	अगर (no_size) अणु
		pr_err("Cannot determine size of symbol '%s'\n",
		       filt->sym_to ? filt->sym_to : filt->sym_from);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dso *load_dso(स्थिर अक्षर *name)
अणु
	काष्ठा map *map;
	काष्ठा dso *dso;

	map = dso__new_map(name);
	अगर (!map)
		वापस शून्य;

	अगर (map__load(map) < 0)
		pr_err("File '%s' not found or has no symbols.\n", name);

	dso = dso__get(map->dso);

	map__put(map);

	वापस dso;
पूर्ण

अटल bool dso_sym_match(काष्ठा symbol *sym, स्थिर अक्षर *name, पूर्णांक *cnt,
			  पूर्णांक idx)
अणु
	/* Same name, and global or the n'th found or any */
	वापस !arch__compare_symbol_names(name, sym->name) &&
	       ((!idx && sym->binding == STB_GLOBAL) ||
		(idx > 0 && ++*cnt == idx) ||
		idx < 0);
पूर्ण

अटल व्योम prपूर्णांक_duplicate_syms(काष्ठा dso *dso, स्थिर अक्षर *sym_name)
अणु
	काष्ठा symbol *sym;
	bool near = false;
	पूर्णांक cnt = 0;

	pr_err("Multiple symbols with name '%s'\n", sym_name);

	sym = dso__first_symbol(dso);
	जबतक (sym) अणु
		अगर (dso_sym_match(sym, sym_name, &cnt, -1)) अणु
			pr_err("#%d\t0x%"PRIx64"\t%c\t%s\n",
			       ++cnt, sym->start,
			       sym->binding == STB_GLOBAL ? 'g' :
			       sym->binding == STB_LOCAL  ? 'l' : 'w',
			       sym->name);
			near = true;
		पूर्ण अन्यथा अगर (near) अणु
			near = false;
			pr_err("\t\twhich is near\t\t%s\n", sym->name);
		पूर्ण
		sym = dso__next_symbol(sym);
	पूर्ण

	pr_err("Disambiguate symbol name by inserting #n after the name e.g. %s #2\n",
	       sym_name);
	pr_err("Or select a global symbol by inserting #0 or #g or #G\n");
पूर्ण

अटल पूर्णांक find_dso_sym(काष्ठा dso *dso, स्थिर अक्षर *sym_name, u64 *start,
			u64 *size, पूर्णांक idx)
अणु
	काष्ठा symbol *sym;
	पूर्णांक cnt = 0;

	*start = 0;
	*size = 0;

	sym = dso__first_symbol(dso);
	जबतक (sym) अणु
		अगर (*start) अणु
			अगर (!*size)
				*size = sym->start - *start;
			अगर (idx > 0) अणु
				अगर (*size)
					वापस 1;
			पूर्ण अन्यथा अगर (dso_sym_match(sym, sym_name, &cnt, idx)) अणु
				prपूर्णांक_duplicate_syms(dso, sym_name);
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अगर (dso_sym_match(sym, sym_name, &cnt, idx)) अणु
			*start = sym->start;
			*size = sym->end - sym->start;
		पूर्ण
		sym = dso__next_symbol(sym);
	पूर्ण

	अगर (!*start)
		वापस sym_not_found_error(sym_name, idx);

	वापस 0;
पूर्ण

अटल पूर्णांक addr_filter__entire_dso(काष्ठा addr_filter *filt, काष्ठा dso *dso)
अणु
	अगर (dso__data_file_size(dso, शून्य)) अणु
		pr_err("Failed to determine filter for %s\nCannot determine file size.\n",
		       filt->filename);
		वापस -EINVAL;
	पूर्ण

	filt->addr = 0;
	filt->size = dso->data.file_size;

	वापस 0;
पूर्ण

अटल पूर्णांक addr_filter__resolve_syms(काष्ठा addr_filter *filt)
अणु
	u64 start, size;
	काष्ठा dso *dso;
	पूर्णांक err = 0;

	अगर (!filt->sym_from && !filt->sym_to)
		वापस 0;

	अगर (!filt->filename)
		वापस addr_filter__resolve_kernel_syms(filt);

	dso = load_dso(filt->filename);
	अगर (!dso) अणु
		pr_err("Failed to load symbols from: %s\n", filt->filename);
		वापस -EINVAL;
	पूर्ण

	अगर (filt->sym_from && !म_भेद(filt->sym_from, "*")) अणु
		err = addr_filter__entire_dso(filt, dso);
		जाओ put_dso;
	पूर्ण

	अगर (filt->sym_from) अणु
		err = find_dso_sym(dso, filt->sym_from, &start, &size,
				   filt->sym_from_idx);
		अगर (err)
			जाओ put_dso;
		filt->addr = start;
		अगर (filt->range && !filt->size && !filt->sym_to)
			filt->size = size;
	पूर्ण

	अगर (filt->sym_to) अणु
		err = find_dso_sym(dso, filt->sym_to, &start, &size,
				   filt->sym_to_idx);
		अगर (err)
			जाओ put_dso;

		err = check_end_after_start(filt, start, size);
		अगर (err)
			वापस err;

		filt->size = start + size - filt->addr;
	पूर्ण

put_dso:
	dso__put(dso);

	वापस err;
पूर्ण

अटल अक्षर *addr_filter__to_str(काष्ठा addr_filter *filt)
अणु
	अक्षर filename_buf[PATH_MAX];
	स्थिर अक्षर *at = "";
	स्थिर अक्षर *fn = "";
	अक्षर *filter;
	पूर्णांक err;

	अगर (filt->filename) अणु
		at = "@";
		fn = realpath(filt->filename, filename_buf);
		अगर (!fn)
			वापस शून्य;
	पूर्ण

	अगर (filt->range) अणु
		err = aप्र_लिखो(&filter, "%s 0x%"PRIx64"/0x%"PRIx64"%s%s",
			       filt->action, filt->addr, filt->size, at, fn);
	पूर्ण अन्यथा अणु
		err = aप्र_लिखो(&filter, "%s 0x%"PRIx64"%s%s",
			       filt->action, filt->addr, at, fn);
	पूर्ण

	वापस err < 0 ? शून्य : filter;
पूर्ण

अटल पूर्णांक parse_addr_filter(काष्ठा evsel *evsel, स्थिर अक्षर *filter,
			     पूर्णांक max_nr)
अणु
	काष्ठा addr_filters filts;
	काष्ठा addr_filter *filt;
	पूर्णांक err;

	addr_filters__init(&filts);

	err = addr_filters__parse_bare_filter(&filts, filter);
	अगर (err)
		जाओ out_निकास;

	अगर (filts.cnt > max_nr) अणु
		pr_err("Error: number of address filters (%d) exceeds maximum (%d)\n",
		       filts.cnt, max_nr);
		err = -EINVAL;
		जाओ out_निकास;
	पूर्ण

	list_क्रम_each_entry(filt, &filts.head, list) अणु
		अक्षर *new_filter;

		err = addr_filter__resolve_syms(filt);
		अगर (err)
			जाओ out_निकास;

		new_filter = addr_filter__to_str(filt);
		अगर (!new_filter) अणु
			err = -ENOMEM;
			जाओ out_निकास;
		पूर्ण

		अगर (evsel__append_addr_filter(evsel, new_filter)) अणु
			err = -ENOMEM;
			जाओ out_निकास;
		पूर्ण
	पूर्ण

out_निकास:
	addr_filters__निकास(&filts);

	अगर (err) अणु
		pr_err("Failed to parse address filter: '%s'\n", filter);
		pr_err("Filter format is: filter|start|stop|tracestop <start symbol or address> [/ <end symbol or size>] [@<file name>]\n");
		pr_err("Where multiple filters are separated by space or comma.\n");
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक evsel__nr_addr_filter(काष्ठा evsel *evsel)
अणु
	काष्ठा perf_pmu *pmu = evsel__find_pmu(evsel);
	पूर्णांक nr_addr_filters = 0;

	अगर (!pmu)
		वापस 0;

	perf_pmu__scan_file(pmu, "nr_addr_filters", "%d", &nr_addr_filters);

	वापस nr_addr_filters;
पूर्ण

पूर्णांक auxtrace_parse_filters(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;
	अक्षर *filter;
	पूर्णांक err, max_nr;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		filter = evsel->filter;
		max_nr = evsel__nr_addr_filter(evsel);
		अगर (!filter || !max_nr)
			जारी;
		evsel->filter = शून्य;
		err = parse_addr_filter(evsel, filter, max_nr);
		मुक्त(filter);
		अगर (err)
			वापस err;
		pr_debug("Address filter: %s\n", evsel->filter);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक auxtrace__process_event(काष्ठा perf_session *session, जोड़ perf_event *event,
			    काष्ठा perf_sample *sample, काष्ठा perf_tool *tool)
अणु
	अगर (!session->auxtrace)
		वापस 0;

	वापस session->auxtrace->process_event(session, event, sample, tool);
पूर्ण

व्योम auxtrace__dump_auxtrace_sample(काष्ठा perf_session *session,
				    काष्ठा perf_sample *sample)
अणु
	अगर (!session->auxtrace || !session->auxtrace->dump_auxtrace_sample ||
	    auxtrace__करोnt_decode(session))
		वापस;

	session->auxtrace->dump_auxtrace_sample(session, sample);
पूर्ण

पूर्णांक auxtrace__flush_events(काष्ठा perf_session *session, काष्ठा perf_tool *tool)
अणु
	अगर (!session->auxtrace)
		वापस 0;

	वापस session->auxtrace->flush_events(session, tool);
पूर्ण

व्योम auxtrace__मुक्त_events(काष्ठा perf_session *session)
अणु
	अगर (!session->auxtrace)
		वापस;

	वापस session->auxtrace->मुक्त_events(session);
पूर्ण

व्योम auxtrace__मुक्त(काष्ठा perf_session *session)
अणु
	अगर (!session->auxtrace)
		वापस;

	वापस session->auxtrace->मुक्त(session);
पूर्ण

bool auxtrace__evsel_is_auxtrace(काष्ठा perf_session *session,
				 काष्ठा evsel *evsel)
अणु
	अगर (!session->auxtrace || !session->auxtrace->evsel_is_auxtrace)
		वापस false;

	वापस session->auxtrace->evsel_is_auxtrace(session, evsel);
पूर्ण
