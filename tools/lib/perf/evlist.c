<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <perf/evlist.h>
#समावेश <perf/evsel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/list.h>
#समावेश <linux/hash.h>
#समावेश <sys/ioctl.h>
#समावेश <पूर्णांकernal/evlist.h>
#समावेश <पूर्णांकernal/evsel.h>
#समावेश <पूर्णांकernal/xyarray.h>
#समावेश <पूर्णांकernal/mmap.h>
#समावेश <पूर्णांकernal/cpumap.h>
#समावेश <पूर्णांकernal/thपढ़ोmap.h>
#समावेश <पूर्णांकernal/lib.h>
#समावेश <linux/zभाग.स>
#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <संकेत.स>
#समावेश <poll.h>
#समावेश <sys/mman.h>
#समावेश <perf/cpumap.h>
#समावेश <perf/thपढ़ोmap.h>
#समावेश <api/fd/array.h>

व्योम perf_evlist__init(काष्ठा perf_evlist *evlist)
अणु
	INIT_LIST_HEAD(&evlist->entries);
	evlist->nr_entries = 0;
	fdarray__init(&evlist->pollfd, 64);
	perf_evlist__reset_id_hash(evlist);
पूर्ण

अटल व्योम __perf_evlist__propagate_maps(काष्ठा perf_evlist *evlist,
					  काष्ठा perf_evsel *evsel)
अणु
	/*
	 * We alपढ़ोy have cpus क्रम evsel (via PMU sysfs) so
	 * keep it, अगर there's no target cpu list defined.
	 */
	अगर (!evsel->own_cpus || evlist->has_user_cpus) अणु
		perf_cpu_map__put(evsel->cpus);
		evsel->cpus = perf_cpu_map__get(evlist->cpus);
	पूर्ण अन्यथा अगर (!evsel->प्रणाली_wide && perf_cpu_map__empty(evlist->cpus)) अणु
		perf_cpu_map__put(evsel->cpus);
		evsel->cpus = perf_cpu_map__get(evlist->cpus);
	पूर्ण अन्यथा अगर (evsel->cpus != evsel->own_cpus) अणु
		perf_cpu_map__put(evsel->cpus);
		evsel->cpus = perf_cpu_map__get(evsel->own_cpus);
	पूर्ण

	perf_thपढ़ो_map__put(evsel->thपढ़ोs);
	evsel->thपढ़ोs = perf_thपढ़ो_map__get(evlist->thपढ़ोs);
	evlist->all_cpus = perf_cpu_map__merge(evlist->all_cpus, evsel->cpus);
पूर्ण

अटल व्योम perf_evlist__propagate_maps(काष्ठा perf_evlist *evlist)
अणु
	काष्ठा perf_evsel *evsel;

	perf_evlist__क्रम_each_evsel(evlist, evsel)
		__perf_evlist__propagate_maps(evlist, evsel);
पूर्ण

व्योम perf_evlist__add(काष्ठा perf_evlist *evlist,
		      काष्ठा perf_evsel *evsel)
अणु
	list_add_tail(&evsel->node, &evlist->entries);
	evlist->nr_entries += 1;
	__perf_evlist__propagate_maps(evlist, evsel);
पूर्ण

व्योम perf_evlist__हटाओ(काष्ठा perf_evlist *evlist,
			 काष्ठा perf_evsel *evsel)
अणु
	list_del_init(&evsel->node);
	evlist->nr_entries -= 1;
पूर्ण

काष्ठा perf_evlist *perf_evlist__new(व्योम)
अणु
	काष्ठा perf_evlist *evlist = zalloc(माप(*evlist));

	अगर (evlist != शून्य)
		perf_evlist__init(evlist);

	वापस evlist;
पूर्ण

काष्ठा perf_evsel *
perf_evlist__next(काष्ठा perf_evlist *evlist, काष्ठा perf_evsel *prev)
अणु
	काष्ठा perf_evsel *next;

	अगर (!prev) अणु
		next = list_first_entry(&evlist->entries,
					काष्ठा perf_evsel,
					node);
	पूर्ण अन्यथा अणु
		next = list_next_entry(prev, node);
	पूर्ण

	/* Empty list is noticed here so करोn't need checking on entry. */
	अगर (&next->node == &evlist->entries)
		वापस शून्य;

	वापस next;
पूर्ण

अटल व्योम perf_evlist__purge(काष्ठा perf_evlist *evlist)
अणु
	काष्ठा perf_evsel *pos, *n;

	perf_evlist__क्रम_each_entry_safe(evlist, n, pos) अणु
		list_del_init(&pos->node);
		perf_evsel__delete(pos);
	पूर्ण

	evlist->nr_entries = 0;
पूर्ण

व्योम perf_evlist__निकास(काष्ठा perf_evlist *evlist)
अणु
	perf_cpu_map__put(evlist->cpus);
	perf_cpu_map__put(evlist->all_cpus);
	perf_thपढ़ो_map__put(evlist->thपढ़ोs);
	evlist->cpus = शून्य;
	evlist->all_cpus = शून्य;
	evlist->thपढ़ोs = शून्य;
	fdarray__निकास(&evlist->pollfd);
पूर्ण

व्योम perf_evlist__delete(काष्ठा perf_evlist *evlist)
अणु
	अगर (evlist == शून्य)
		वापस;

	perf_evlist__munmap(evlist);
	perf_evlist__बंद(evlist);
	perf_evlist__purge(evlist);
	perf_evlist__निकास(evlist);
	मुक्त(evlist);
पूर्ण

व्योम perf_evlist__set_maps(काष्ठा perf_evlist *evlist,
			   काष्ठा perf_cpu_map *cpus,
			   काष्ठा perf_thपढ़ो_map *thपढ़ोs)
अणु
	/*
	 * Allow क्रम the possibility that one or another of the maps isn't being
	 * changed i.e. करोn't put it.  Note we are assuming the maps that are
	 * being applied are bअक्रम new and evlist is taking ownership of the
	 * original reference count of 1.  If that is not the हाल it is up to
	 * the caller to increase the reference count.
	 */
	अगर (cpus != evlist->cpus) अणु
		perf_cpu_map__put(evlist->cpus);
		evlist->cpus = perf_cpu_map__get(cpus);
	पूर्ण

	अगर (thपढ़ोs != evlist->thपढ़ोs) अणु
		perf_thपढ़ो_map__put(evlist->thपढ़ोs);
		evlist->thपढ़ोs = perf_thपढ़ो_map__get(thपढ़ोs);
	पूर्ण

	अगर (!evlist->all_cpus && cpus)
		evlist->all_cpus = perf_cpu_map__get(cpus);

	perf_evlist__propagate_maps(evlist);
पूर्ण

पूर्णांक perf_evlist__खोलो(काष्ठा perf_evlist *evlist)
अणु
	काष्ठा perf_evsel *evsel;
	पूर्णांक err;

	perf_evlist__क्रम_each_entry(evlist, evsel) अणु
		err = perf_evsel__खोलो(evsel, evsel->cpus, evsel->thपढ़ोs);
		अगर (err < 0)
			जाओ out_err;
	पूर्ण

	वापस 0;

out_err:
	perf_evlist__बंद(evlist);
	वापस err;
पूर्ण

व्योम perf_evlist__बंद(काष्ठा perf_evlist *evlist)
अणु
	काष्ठा perf_evsel *evsel;

	perf_evlist__क्रम_each_entry_reverse(evlist, evsel)
		perf_evsel__बंद(evsel);
पूर्ण

व्योम perf_evlist__enable(काष्ठा perf_evlist *evlist)
अणु
	काष्ठा perf_evsel *evsel;

	perf_evlist__क्रम_each_entry(evlist, evsel)
		perf_evsel__enable(evsel);
पूर्ण

व्योम perf_evlist__disable(काष्ठा perf_evlist *evlist)
अणु
	काष्ठा perf_evsel *evsel;

	perf_evlist__क्रम_each_entry(evlist, evsel)
		perf_evsel__disable(evsel);
पूर्ण

u64 perf_evlist__पढ़ो_क्रमmat(काष्ठा perf_evlist *evlist)
अणु
	काष्ठा perf_evsel *first = perf_evlist__first(evlist);

	वापस first->attr.पढ़ो_क्रमmat;
पूर्ण

#घोषणा SID(e, x, y) xyarray__entry(e->sample_id, x, y)

अटल व्योम perf_evlist__id_hash(काष्ठा perf_evlist *evlist,
				 काष्ठा perf_evsel *evsel,
				 पूर्णांक cpu, पूर्णांक thपढ़ो, u64 id)
अणु
	पूर्णांक hash;
	काष्ठा perf_sample_id *sid = SID(evsel, cpu, thपढ़ो);

	sid->id = id;
	sid->evsel = evsel;
	hash = hash_64(sid->id, PERF_EVLIST__HLIST_BITS);
	hlist_add_head(&sid->node, &evlist->heads[hash]);
पूर्ण

व्योम perf_evlist__reset_id_hash(काष्ठा perf_evlist *evlist)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PERF_EVLIST__HLIST_SIZE; ++i)
		INIT_HLIST_HEAD(&evlist->heads[i]);
पूर्ण

व्योम perf_evlist__id_add(काष्ठा perf_evlist *evlist,
			 काष्ठा perf_evsel *evsel,
			 पूर्णांक cpu, पूर्णांक thपढ़ो, u64 id)
अणु
	perf_evlist__id_hash(evlist, evsel, cpu, thपढ़ो, id);
	evsel->id[evsel->ids++] = id;
पूर्ण

पूर्णांक perf_evlist__id_add_fd(काष्ठा perf_evlist *evlist,
			   काष्ठा perf_evsel *evsel,
			   पूर्णांक cpu, पूर्णांक thपढ़ो, पूर्णांक fd)
अणु
	u64 पढ़ो_data[4] = अणु 0, पूर्ण;
	पूर्णांक id_idx = 1; /* The first entry is the counter value */
	u64 id;
	पूर्णांक ret;

	ret = ioctl(fd, PERF_EVENT_IOC_ID, &id);
	अगर (!ret)
		जाओ add;

	अगर (त्रुटि_सं != ENOTTY)
		वापस -1;

	/* Legacy way to get event id.. All hail to old kernels! */

	/*
	 * This way करोes not work with group क्रमmat पढ़ो, so bail
	 * out in that हाल.
	 */
	अगर (perf_evlist__पढ़ो_क्रमmat(evlist) & PERF_FORMAT_GROUP)
		वापस -1;

	अगर (!(evsel->attr.पढ़ो_क्रमmat & PERF_FORMAT_ID) ||
	    पढ़ो(fd, &पढ़ो_data, माप(पढ़ो_data)) == -1)
		वापस -1;

	अगर (evsel->attr.पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_ENABLED)
		++id_idx;
	अगर (evsel->attr.पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_RUNNING)
		++id_idx;

	id = पढ़ो_data[id_idx];

add:
	perf_evlist__id_add(evlist, evsel, cpu, thपढ़ो, id);
	वापस 0;
पूर्ण

पूर्णांक perf_evlist__alloc_pollfd(काष्ठा perf_evlist *evlist)
अणु
	पूर्णांक nr_cpus = perf_cpu_map__nr(evlist->cpus);
	पूर्णांक nr_thपढ़ोs = perf_thपढ़ो_map__nr(evlist->thपढ़ोs);
	पूर्णांक nfds = 0;
	काष्ठा perf_evsel *evsel;

	perf_evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->प्रणाली_wide)
			nfds += nr_cpus;
		अन्यथा
			nfds += nr_cpus * nr_thपढ़ोs;
	पूर्ण

	अगर (fdarray__available_entries(&evlist->pollfd) < nfds &&
	    fdarray__grow(&evlist->pollfd, nfds) < 0)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक perf_evlist__add_pollfd(काष्ठा perf_evlist *evlist, पूर्णांक fd,
			    व्योम *ptr, लघु revent, क्रमागत fdarray_flags flags)
अणु
	पूर्णांक pos = fdarray__add(&evlist->pollfd, fd, revent | POLLERR | POLLHUP, flags);

	अगर (pos >= 0) अणु
		evlist->pollfd.priv[pos].ptr = ptr;
		fcntl(fd, F_SETFL, O_NONBLOCK);
	पूर्ण

	वापस pos;
पूर्ण

अटल व्योम perf_evlist__munmap_filtered(काष्ठा fdarray *fda, पूर्णांक fd,
					 व्योम *arg __maybe_unused)
अणु
	काष्ठा perf_mmap *map = fda->priv[fd].ptr;

	अगर (map)
		perf_mmap__put(map);
पूर्ण

पूर्णांक perf_evlist__filter_pollfd(काष्ठा perf_evlist *evlist, लघु revents_and_mask)
अणु
	वापस fdarray__filter(&evlist->pollfd, revents_and_mask,
			       perf_evlist__munmap_filtered, शून्य);
पूर्ण

पूर्णांक perf_evlist__poll(काष्ठा perf_evlist *evlist, पूर्णांक समयout)
अणु
	वापस fdarray__poll(&evlist->pollfd, समयout);
पूर्ण

अटल काष्ठा perf_mmap* perf_evlist__alloc_mmap(काष्ठा perf_evlist *evlist, bool overग_लिखो)
अणु
	पूर्णांक i;
	काष्ठा perf_mmap *map;

	map = zalloc(evlist->nr_mmaps * माप(काष्ठा perf_mmap));
	अगर (!map)
		वापस शून्य;

	क्रम (i = 0; i < evlist->nr_mmaps; i++) अणु
		काष्ठा perf_mmap *prev = i ? &map[i - 1] : शून्य;

		/*
		 * When the perf_mmap() call is made we grab one refcount, plus
		 * one extra to let perf_mmap__consume() get the last
		 * events after all real references (perf_mmap__get()) are
		 * dropped.
		 *
		 * Each PERF_EVENT_IOC_SET_OUTPUT poपूर्णांकs to this mmap and
		 * thus करोes perf_mmap__get() on it.
		 */
		perf_mmap__init(&map[i], prev, overग_लिखो, शून्य);
	पूर्ण

	वापस map;
पूर्ण

अटल व्योम perf_evsel__set_sid_idx(काष्ठा perf_evsel *evsel, पूर्णांक idx, पूर्णांक cpu, पूर्णांक thपढ़ो)
अणु
	काष्ठा perf_sample_id *sid = SID(evsel, cpu, thपढ़ो);

	sid->idx = idx;
	sid->cpu = perf_cpu_map__cpu(evsel->cpus, cpu);
	sid->tid = perf_thपढ़ो_map__pid(evsel->thपढ़ोs, thपढ़ो);
पूर्ण

अटल काष्ठा perf_mmap*
perf_evlist__mmap_cb_get(काष्ठा perf_evlist *evlist, bool overग_लिखो, पूर्णांक idx)
अणु
	काष्ठा perf_mmap *maps;

	maps = overग_लिखो ? evlist->mmap_ovw : evlist->mmap;

	अगर (!maps) अणु
		maps = perf_evlist__alloc_mmap(evlist, overग_लिखो);
		अगर (!maps)
			वापस शून्य;

		अगर (overग_लिखो)
			evlist->mmap_ovw = maps;
		अन्यथा
			evlist->mmap = maps;
	पूर्ण

	वापस &maps[idx];
पूर्ण

#घोषणा FD(e, x, y) (*(पूर्णांक *) xyarray__entry(e->fd, x, y))

अटल पूर्णांक
perf_evlist__mmap_cb_mmap(काष्ठा perf_mmap *map, काष्ठा perf_mmap_param *mp,
			  पूर्णांक output, पूर्णांक cpu)
अणु
	वापस perf_mmap__mmap(map, mp, output, cpu);
पूर्ण

अटल व्योम perf_evlist__set_mmap_first(काष्ठा perf_evlist *evlist, काष्ठा perf_mmap *map,
					bool overग_लिखो)
अणु
	अगर (overग_लिखो)
		evlist->mmap_ovw_first = map;
	अन्यथा
		evlist->mmap_first = map;
पूर्ण

अटल पूर्णांक
mmap_per_evsel(काष्ठा perf_evlist *evlist, काष्ठा perf_evlist_mmap_ops *ops,
	       पूर्णांक idx, काष्ठा perf_mmap_param *mp, पूर्णांक cpu_idx,
	       पूर्णांक thपढ़ो, पूर्णांक *_output, पूर्णांक *_output_overग_लिखो)
अणु
	पूर्णांक evlist_cpu = perf_cpu_map__cpu(evlist->cpus, cpu_idx);
	काष्ठा perf_evsel *evsel;
	पूर्णांक revent;

	perf_evlist__क्रम_each_entry(evlist, evsel) अणु
		bool overग_लिखो = evsel->attr.ग_लिखो_backward;
		काष्ठा perf_mmap *map;
		पूर्णांक *output, fd, cpu;

		अगर (evsel->प्रणाली_wide && thपढ़ो)
			जारी;

		cpu = perf_cpu_map__idx(evsel->cpus, evlist_cpu);
		अगर (cpu == -1)
			जारी;

		map = ops->get(evlist, overग_लिखो, idx);
		अगर (map == शून्य)
			वापस -ENOMEM;

		अगर (overग_लिखो) अणु
			mp->prot = PROT_READ;
			output   = _output_overग_लिखो;
		पूर्ण अन्यथा अणु
			mp->prot = PROT_READ | PROT_WRITE;
			output   = _output;
		पूर्ण

		fd = FD(evsel, cpu, thपढ़ो);

		अगर (*output == -1) अणु
			*output = fd;

			/*
			 * The last one will be करोne at perf_mmap__consume(), so that we
			 * make sure we करोn't prevent tools from consuming every last event in
			 * the ring buffer.
			 *
			 * I.e. we can get the POLLHUP meaning that the fd करोesn't exist
			 * anymore, but the last events क्रम it are still in the ring buffer,
			 * रुकोing to be consumed.
			 *
			 * Tools can chose to ignore this at their own discretion, but the
			 * evlist layer can't just drop it when filtering events in
			 * perf_evlist__filter_pollfd().
			 */
			refcount_set(&map->refcnt, 2);

			अगर (ops->mmap(map, mp, *output, evlist_cpu) < 0)
				वापस -1;

			अगर (!idx)
				perf_evlist__set_mmap_first(evlist, map, overग_लिखो);
		पूर्ण अन्यथा अणु
			अगर (ioctl(fd, PERF_EVENT_IOC_SET_OUTPUT, *output) != 0)
				वापस -1;

			perf_mmap__get(map);
		पूर्ण

		revent = !overग_लिखो ? POLLIN : 0;

		अगर (!evsel->प्रणाली_wide &&
		    perf_evlist__add_pollfd(evlist, fd, map, revent, fdarray_flag__शेष) < 0) अणु
			perf_mmap__put(map);
			वापस -1;
		पूर्ण

		अगर (evsel->attr.पढ़ो_क्रमmat & PERF_FORMAT_ID) अणु
			अगर (perf_evlist__id_add_fd(evlist, evsel, cpu, thपढ़ो,
						   fd) < 0)
				वापस -1;
			perf_evsel__set_sid_idx(evsel, idx, cpu, thपढ़ो);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mmap_per_thपढ़ो(काष्ठा perf_evlist *evlist, काष्ठा perf_evlist_mmap_ops *ops,
		काष्ठा perf_mmap_param *mp)
अणु
	पूर्णांक thपढ़ो;
	पूर्णांक nr_thपढ़ोs = perf_thपढ़ो_map__nr(evlist->thपढ़ोs);

	क्रम (thपढ़ो = 0; thपढ़ो < nr_thपढ़ोs; thपढ़ो++) अणु
		पूर्णांक output = -1;
		पूर्णांक output_overग_लिखो = -1;

		अगर (ops->idx)
			ops->idx(evlist, mp, thपढ़ो, false);

		अगर (mmap_per_evsel(evlist, ops, thपढ़ो, mp, 0, thपढ़ो,
				   &output, &output_overग_लिखो))
			जाओ out_unmap;
	पूर्ण

	वापस 0;

out_unmap:
	perf_evlist__munmap(evlist);
	वापस -1;
पूर्ण

अटल पूर्णांक
mmap_per_cpu(काष्ठा perf_evlist *evlist, काष्ठा perf_evlist_mmap_ops *ops,
	     काष्ठा perf_mmap_param *mp)
अणु
	पूर्णांक nr_thपढ़ोs = perf_thपढ़ो_map__nr(evlist->thपढ़ोs);
	पूर्णांक nr_cpus    = perf_cpu_map__nr(evlist->cpus);
	पूर्णांक cpu, thपढ़ो;

	क्रम (cpu = 0; cpu < nr_cpus; cpu++) अणु
		पूर्णांक output = -1;
		पूर्णांक output_overग_लिखो = -1;

		अगर (ops->idx)
			ops->idx(evlist, mp, cpu, true);

		क्रम (thपढ़ो = 0; thपढ़ो < nr_thपढ़ोs; thपढ़ो++) अणु
			अगर (mmap_per_evsel(evlist, ops, cpu, mp, cpu,
					   thपढ़ो, &output, &output_overग_लिखो))
				जाओ out_unmap;
		पूर्ण
	पूर्ण

	वापस 0;

out_unmap:
	perf_evlist__munmap(evlist);
	वापस -1;
पूर्ण

अटल पूर्णांक perf_evlist__nr_mmaps(काष्ठा perf_evlist *evlist)
अणु
	पूर्णांक nr_mmaps;

	nr_mmaps = perf_cpu_map__nr(evlist->cpus);
	अगर (perf_cpu_map__empty(evlist->cpus))
		nr_mmaps = perf_thपढ़ो_map__nr(evlist->thपढ़ोs);

	वापस nr_mmaps;
पूर्ण

पूर्णांक perf_evlist__mmap_ops(काष्ठा perf_evlist *evlist,
			  काष्ठा perf_evlist_mmap_ops *ops,
			  काष्ठा perf_mmap_param *mp)
अणु
	काष्ठा perf_evsel *evsel;
	स्थिर काष्ठा perf_cpu_map *cpus = evlist->cpus;
	स्थिर काष्ठा perf_thपढ़ो_map *thपढ़ोs = evlist->thपढ़ोs;

	अगर (!ops || !ops->get || !ops->mmap)
		वापस -EINVAL;

	mp->mask = evlist->mmap_len - page_size - 1;

	evlist->nr_mmaps = perf_evlist__nr_mmaps(evlist);

	perf_evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर ((evsel->attr.पढ़ो_क्रमmat & PERF_FORMAT_ID) &&
		    evsel->sample_id == शून्य &&
		    perf_evsel__alloc_id(evsel, perf_cpu_map__nr(cpus), thपढ़ोs->nr) < 0)
			वापस -ENOMEM;
	पूर्ण

	अगर (evlist->pollfd.entries == शून्य && perf_evlist__alloc_pollfd(evlist) < 0)
		वापस -ENOMEM;

	अगर (perf_cpu_map__empty(cpus))
		वापस mmap_per_thपढ़ो(evlist, ops, mp);

	वापस mmap_per_cpu(evlist, ops, mp);
पूर्ण

पूर्णांक perf_evlist__mmap(काष्ठा perf_evlist *evlist, पूर्णांक pages)
अणु
	काष्ठा perf_mmap_param mp;
	काष्ठा perf_evlist_mmap_ops ops = अणु
		.get  = perf_evlist__mmap_cb_get,
		.mmap = perf_evlist__mmap_cb_mmap,
	पूर्ण;

	evlist->mmap_len = (pages + 1) * page_size;

	वापस perf_evlist__mmap_ops(evlist, &ops, &mp);
पूर्ण

व्योम perf_evlist__munmap(काष्ठा perf_evlist *evlist)
अणु
	पूर्णांक i;

	अगर (evlist->mmap) अणु
		क्रम (i = 0; i < evlist->nr_mmaps; i++)
			perf_mmap__munmap(&evlist->mmap[i]);
	पूर्ण

	अगर (evlist->mmap_ovw) अणु
		क्रम (i = 0; i < evlist->nr_mmaps; i++)
			perf_mmap__munmap(&evlist->mmap_ovw[i]);
	पूर्ण

	zमुक्त(&evlist->mmap);
	zमुक्त(&evlist->mmap_ovw);
पूर्ण

काष्ठा perf_mmap*
perf_evlist__next_mmap(काष्ठा perf_evlist *evlist, काष्ठा perf_mmap *map,
		       bool overग_लिखो)
अणु
	अगर (map)
		वापस map->next;

	वापस overग_लिखो ? evlist->mmap_ovw_first : evlist->mmap_first;
पूर्ण
