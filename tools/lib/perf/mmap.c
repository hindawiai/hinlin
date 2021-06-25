<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <sys/mman.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <यंत्र/bug.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <linux/ring_buffer.h>
#समावेश <linux/perf_event.h>
#समावेश <perf/mmap.h>
#समावेश <perf/event.h>
#समावेश <perf/evsel.h>
#समावेश <पूर्णांकernal/mmap.h>
#समावेश <पूर्णांकernal/lib.h>
#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश "internal.h"

व्योम perf_mmap__init(काष्ठा perf_mmap *map, काष्ठा perf_mmap *prev,
		     bool overग_लिखो, libperf_unmap_cb_t unmap_cb)
अणु
	map->fd = -1;
	map->overग_लिखो = overग_लिखो;
	map->unmap_cb  = unmap_cb;
	refcount_set(&map->refcnt, 0);
	अगर (prev)
		prev->next = map;
पूर्ण

माप_प्रकार perf_mmap__mmap_len(काष्ठा perf_mmap *map)
अणु
	वापस map->mask + 1 + page_size;
पूर्ण

पूर्णांक perf_mmap__mmap(काष्ठा perf_mmap *map, काष्ठा perf_mmap_param *mp,
		    पूर्णांक fd, पूर्णांक cpu)
अणु
	map->prev = 0;
	map->mask = mp->mask;
	map->base = mmap(शून्य, perf_mmap__mmap_len(map), mp->prot,
			 MAP_SHARED, fd, 0);
	अगर (map->base == MAP_FAILED) अणु
		map->base = शून्य;
		वापस -1;
	पूर्ण

	map->fd  = fd;
	map->cpu = cpu;
	वापस 0;
पूर्ण

व्योम perf_mmap__munmap(काष्ठा perf_mmap *map)
अणु
	अगर (map && map->base != शून्य) अणु
		munmap(map->base, perf_mmap__mmap_len(map));
		map->base = शून्य;
		map->fd = -1;
		refcount_set(&map->refcnt, 0);
	पूर्ण
	अगर (map && map->unmap_cb)
		map->unmap_cb(map);
पूर्ण

व्योम perf_mmap__get(काष्ठा perf_mmap *map)
अणु
	refcount_inc(&map->refcnt);
पूर्ण

व्योम perf_mmap__put(काष्ठा perf_mmap *map)
अणु
	BUG_ON(map->base && refcount_पढ़ो(&map->refcnt) == 0);

	अगर (refcount_dec_and_test(&map->refcnt))
		perf_mmap__munmap(map);
पूर्ण

अटल अंतरभूत व्योम perf_mmap__ग_लिखो_tail(काष्ठा perf_mmap *md, u64 tail)
अणु
	ring_buffer_ग_लिखो_tail(md->base, tail);
पूर्ण

u64 perf_mmap__पढ़ो_head(काष्ठा perf_mmap *map)
अणु
	वापस ring_buffer_पढ़ो_head(map->base);
पूर्ण

अटल bool perf_mmap__empty(काष्ठा perf_mmap *map)
अणु
	काष्ठा perf_event_mmap_page *pc = map->base;

	वापस perf_mmap__पढ़ो_head(map) == map->prev && !pc->aux_size;
पूर्ण

व्योम perf_mmap__consume(काष्ठा perf_mmap *map)
अणु
	अगर (!map->overग_लिखो) अणु
		u64 old = map->prev;

		perf_mmap__ग_लिखो_tail(map, old);
	पूर्ण

	अगर (refcount_पढ़ो(&map->refcnt) == 1 && perf_mmap__empty(map))
		perf_mmap__put(map);
पूर्ण

अटल पूर्णांक overग_लिखो_rb_find_range(व्योम *buf, पूर्णांक mask, u64 *start, u64 *end)
अणु
	काष्ठा perf_event_header *pheader;
	u64 evt_head = *start;
	पूर्णांक size = mask + 1;

	pr_debug2("%s: buf=%p, start=%"PRIx64"\n", __func__, buf, *start);
	pheader = (काष्ठा perf_event_header *)(buf + (*start & mask));
	जबतक (true) अणु
		अगर (evt_head - *start >= (अचिन्हित पूर्णांक)size) अणु
			pr_debug("Finished reading overwrite ring buffer: rewind\n");
			अगर (evt_head - *start > (अचिन्हित पूर्णांक)size)
				evt_head -= pheader->size;
			*end = evt_head;
			वापस 0;
		पूर्ण

		pheader = (काष्ठा perf_event_header *)(buf + (evt_head & mask));

		अगर (pheader->size == 0) अणु
			pr_debug("Finished reading overwrite ring buffer: get start\n");
			*end = evt_head;
			वापस 0;
		पूर्ण

		evt_head += pheader->size;
		pr_debug3("move evt_head: %"PRIx64"\n", evt_head);
	पूर्ण
	WARN_ONCE(1, "Shouldn't get here\n");
	वापस -1;
पूर्ण

/*
 * Report the start and end of the available data in ringbuffer
 */
अटल पूर्णांक __perf_mmap__पढ़ो_init(काष्ठा perf_mmap *md)
अणु
	u64 head = perf_mmap__पढ़ो_head(md);
	u64 old = md->prev;
	अचिन्हित अक्षर *data = md->base + page_size;
	अचिन्हित दीर्घ size;

	md->start = md->overग_लिखो ? head : old;
	md->end = md->overग_लिखो ? old : head;

	अगर ((md->end - md->start) < md->flush)
		वापस -EAGAIN;

	size = md->end - md->start;
	अगर (size > (अचिन्हित दीर्घ)(md->mask) + 1) अणु
		अगर (!md->overग_लिखो) अणु
			WARN_ONCE(1, "failed to keep up with mmap data. (warn only once)\n");

			md->prev = head;
			perf_mmap__consume(md);
			वापस -EAGAIN;
		पूर्ण

		/*
		 * Backward ring buffer is full. We still have a chance to पढ़ो
		 * most of data from it.
		 */
		अगर (overग_लिखो_rb_find_range(data, md->mask, &md->start, &md->end))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक perf_mmap__पढ़ो_init(काष्ठा perf_mmap *map)
अणु
	/*
	 * Check अगर event was unmapped due to a POLLHUP/POLLERR.
	 */
	अगर (!refcount_पढ़ो(&map->refcnt))
		वापस -ENOENT;

	वापस __perf_mmap__पढ़ो_init(map);
पूर्ण

/*
 * Mandatory क्रम overग_लिखो mode
 * The direction of overग_लिखो mode is backward.
 * The last perf_mmap__पढ़ो() will set tail to map->core.prev.
 * Need to correct the map->core.prev to head which is the end of next पढ़ो.
 */
व्योम perf_mmap__पढ़ो_करोne(काष्ठा perf_mmap *map)
अणु
	/*
	 * Check अगर event was unmapped due to a POLLHUP/POLLERR.
	 */
	अगर (!refcount_पढ़ो(&map->refcnt))
		वापस;

	map->prev = perf_mmap__पढ़ो_head(map);
पूर्ण

/* When check_messup is true, 'end' must poपूर्णांकs to a good entry */
अटल जोड़ perf_event *perf_mmap__पढ़ो(काष्ठा perf_mmap *map,
					 u64 *startp, u64 end)
अणु
	अचिन्हित अक्षर *data = map->base + page_size;
	जोड़ perf_event *event = शून्य;
	पूर्णांक dअगरf = end - *startp;

	अगर (dअगरf >= (पूर्णांक)माप(event->header)) अणु
		माप_प्रकार size;

		event = (जोड़ perf_event *)&data[*startp & map->mask];
		size = event->header.size;

		अगर (size < माप(event->header) || dअगरf < (पूर्णांक)size)
			वापस शून्य;

		/*
		 * Event straddles the mmap boundary -- header should always
		 * be inside due to u64 alignment of output.
		 */
		अगर ((*startp & map->mask) + size != ((*startp + size) & map->mask)) अणु
			अचिन्हित पूर्णांक offset = *startp;
			अचिन्हित पूर्णांक len = min(माप(*event), size), cpy;
			व्योम *dst = map->event_copy;

			करो अणु
				cpy = min(map->mask + 1 - (offset & map->mask), len);
				स_नकल(dst, &data[offset & map->mask], cpy);
				offset += cpy;
				dst += cpy;
				len -= cpy;
			पूर्ण जबतक (len);

			event = (जोड़ perf_event *)map->event_copy;
		पूर्ण

		*startp += size;
	पूर्ण

	वापस event;
पूर्ण

/*
 * Read event from ring buffer one by one.
 * Return one event क्रम each call.
 *
 * Usage:
 * perf_mmap__पढ़ो_init()
 * जबतक(event = perf_mmap__पढ़ो_event()) अणु
 *	//process the event
 *	perf_mmap__consume()
 * पूर्ण
 * perf_mmap__पढ़ो_करोne()
 */
जोड़ perf_event *perf_mmap__पढ़ो_event(काष्ठा perf_mmap *map)
अणु
	जोड़ perf_event *event;

	/*
	 * Check अगर event was unmapped due to a POLLHUP/POLLERR.
	 */
	अगर (!refcount_पढ़ो(&map->refcnt))
		वापस शून्य;

	/* non-overwirte करोesn't छोड़ो the ringbuffer */
	अगर (!map->overग_लिखो)
		map->end = perf_mmap__पढ़ो_head(map);

	event = perf_mmap__पढ़ो(map, &map->start, map->end);

	अगर (!map->overग_लिखो)
		map->prev = map->start;

	वापस event;
पूर्ण

#अगर defined(__i386__) || defined(__x86_64__)
अटल u64 पढ़ो_perf_counter(अचिन्हित पूर्णांक counter)
अणु
	अचिन्हित पूर्णांक low, high;

	यंत्र अस्थिर("rdpmc" : "=a" (low), "=d" (high) : "c" (counter));

	वापस low | ((u64)high) << 32;
पूर्ण

अटल u64 पढ़ो_बारtamp(व्योम)
अणु
	अचिन्हित पूर्णांक low, high;

	यंत्र अस्थिर("rdtsc" : "=a" (low), "=d" (high));

	वापस low | ((u64)high) << 32;
पूर्ण
#अन्यथा
अटल u64 पढ़ो_perf_counter(अचिन्हित पूर्णांक counter __maybe_unused) अणु वापस 0; पूर्ण
अटल u64 पढ़ो_बारtamp(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

पूर्णांक perf_mmap__पढ़ो_self(काष्ठा perf_mmap *map, काष्ठा perf_counts_values *count)
अणु
	काष्ठा perf_event_mmap_page *pc = map->base;
	u32 seq, idx, समय_mult = 0, समय_shअगरt = 0;
	u64 cnt, cyc = 0, समय_offset = 0, समय_cycles = 0, समय_mask = ~0ULL;

	अगर (!pc || !pc->cap_user_rdpmc)
		वापस -1;

	करो अणु
		seq = READ_ONCE(pc->lock);
		barrier();

		count->ena = READ_ONCE(pc->समय_enabled);
		count->run = READ_ONCE(pc->समय_running);

		अगर (pc->cap_user_समय && count->ena != count->run) अणु
			cyc = पढ़ो_बारtamp();
			समय_mult = READ_ONCE(pc->समय_mult);
			समय_shअगरt = READ_ONCE(pc->समय_shअगरt);
			समय_offset = READ_ONCE(pc->समय_offset);

			अगर (pc->cap_user_समय_लघु) अणु
				समय_cycles = READ_ONCE(pc->समय_cycles);
				समय_mask = READ_ONCE(pc->समय_mask);
			पूर्ण
		पूर्ण

		idx = READ_ONCE(pc->index);
		cnt = READ_ONCE(pc->offset);
		अगर (pc->cap_user_rdpmc && idx) अणु
			s64 evcnt = पढ़ो_perf_counter(idx - 1);
			u16 width = READ_ONCE(pc->pmc_width);

			evcnt <<= 64 - width;
			evcnt >>= 64 - width;
			cnt += evcnt;
		पूर्ण अन्यथा
			वापस -1;

		barrier();
	पूर्ण जबतक (READ_ONCE(pc->lock) != seq);

	अगर (count->ena != count->run) अणु
		u64 delta;

		/* Adjust क्रम cap_usr_समय_लघु, a nop अगर not */
		cyc = समय_cycles + ((cyc - समय_cycles) & समय_mask);

		delta = समय_offset + mul_u64_u32_shr(cyc, समय_mult, समय_shअगरt);

		count->ena += delta;
		अगर (idx)
			count->run += delta;

		cnt = mul_u64_u64_भाग64(cnt, count->ena, count->run);
	पूर्ण

	count->val = cnt;

	वापस 0;
पूर्ण
