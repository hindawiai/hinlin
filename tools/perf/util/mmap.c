<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011-2017, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 *
 * Parts came from evlist.c builtin-अणुtop,stat,recordपूर्ण.c, see those files क्रम further
 * copyright notes.
 */

#समावेश <sys/mman.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <यंत्र/bug.h>
#समावेश <linux/zभाग.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h> // sysconf()
#समावेश <perf/mmap.h>
#अगर_घोषित HAVE_LIBNUMA_SUPPORT
#समावेश <numaअगर.h>
#पूर्ण_अगर
#समावेश "cpumap.h"
#समावेश "debug.h"
#समावेश "event.h"
#समावेश "mmap.h"
#समावेश "../perf.h"
#समावेश <पूर्णांकernal/lib.h> /* page_size */
#समावेश <linux/biपंचांगap.h>

#घोषणा MASK_SIZE 1023
व्योम mmap_cpu_mask__scnम_लिखो(काष्ठा mmap_cpu_mask *mask, स्थिर अक्षर *tag)
अणु
	अक्षर buf[MASK_SIZE + 1];
	माप_प्रकार len;

	len = biपंचांगap_scnम_लिखो(mask->bits, mask->nbits, buf, MASK_SIZE);
	buf[len] = '\0';
	pr_debug("%p: %s mask[%zd]: %s\n", mask, tag, mask->nbits, buf);
पूर्ण

माप_प्रकार mmap__mmap_len(काष्ठा mmap *map)
अणु
	वापस perf_mmap__mmap_len(&map->core);
पूर्ण

पूर्णांक __weak auxtrace_mmap__mmap(काष्ठा auxtrace_mmap *mm __maybe_unused,
			       काष्ठा auxtrace_mmap_params *mp __maybe_unused,
			       व्योम *userpg __maybe_unused,
			       पूर्णांक fd __maybe_unused)
अणु
	वापस 0;
पूर्ण

व्योम __weak auxtrace_mmap__munmap(काष्ठा auxtrace_mmap *mm __maybe_unused)
अणु
पूर्ण

व्योम __weak auxtrace_mmap_params__init(काष्ठा auxtrace_mmap_params *mp __maybe_unused,
				       off_t auxtrace_offset __maybe_unused,
				       अचिन्हित पूर्णांक auxtrace_pages __maybe_unused,
				       bool auxtrace_overग_लिखो __maybe_unused)
अणु
पूर्ण

व्योम __weak auxtrace_mmap_params__set_idx(काष्ठा auxtrace_mmap_params *mp __maybe_unused,
					  काष्ठा evlist *evlist __maybe_unused,
					  पूर्णांक idx __maybe_unused,
					  bool per_cpu __maybe_unused)
अणु
पूर्ण

#अगर_घोषित HAVE_AIO_SUPPORT
अटल पूर्णांक perf_mmap__aio_enabled(काष्ठा mmap *map)
अणु
	वापस map->aio.nr_cblocks > 0;
पूर्ण

#अगर_घोषित HAVE_LIBNUMA_SUPPORT
अटल पूर्णांक perf_mmap__aio_alloc(काष्ठा mmap *map, पूर्णांक idx)
अणु
	map->aio.data[idx] = mmap(शून्य, mmap__mmap_len(map), PROT_READ|PROT_WRITE,
				  MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);
	अगर (map->aio.data[idx] == MAP_FAILED) अणु
		map->aio.data[idx] = शून्य;
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम perf_mmap__aio_मुक्त(काष्ठा mmap *map, पूर्णांक idx)
अणु
	अगर (map->aio.data[idx]) अणु
		munmap(map->aio.data[idx], mmap__mmap_len(map));
		map->aio.data[idx] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक perf_mmap__aio_bind(काष्ठा mmap *map, पूर्णांक idx, पूर्णांक cpu, पूर्णांक affinity)
अणु
	व्योम *data;
	माप_प्रकार mmap_len;
	अचिन्हित दीर्घ *node_mask;
	अचिन्हित दीर्घ node_index;
	पूर्णांक err = 0;

	अगर (affinity != PERF_AFFINITY_SYS && cpu__max_node() > 1) अणु
		data = map->aio.data[idx];
		mmap_len = mmap__mmap_len(map);
		node_index = cpu__get_node(cpu);
		node_mask = biपंचांगap_alloc(node_index + 1);
		अगर (!node_mask) अणु
			pr_err("Failed to allocate node mask for mbind: error %m\n");
			वापस -1;
		पूर्ण
		set_bit(node_index, node_mask);
		अगर (mbind(data, mmap_len, MPOL_BIND, node_mask, node_index + 1 + 1, 0)) अणु
			pr_err("Failed to bind [%p-%p] AIO buffer to node %lu: error %m\n",
				data, data + mmap_len, node_index);
			err = -1;
		पूर्ण
		biपंचांगap_मुक्त(node_mask);
	पूर्ण

	वापस err;
पूर्ण
#अन्यथा /* !HAVE_LIBNUMA_SUPPORT */
अटल पूर्णांक perf_mmap__aio_alloc(काष्ठा mmap *map, पूर्णांक idx)
अणु
	map->aio.data[idx] = दो_स्मृति(mmap__mmap_len(map));
	अगर (map->aio.data[idx] == शून्य)
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम perf_mmap__aio_मुक्त(काष्ठा mmap *map, पूर्णांक idx)
अणु
	zमुक्त(&(map->aio.data[idx]));
पूर्ण

अटल पूर्णांक perf_mmap__aio_bind(काष्ठा mmap *map __maybe_unused, पूर्णांक idx __maybe_unused,
		पूर्णांक cpu __maybe_unused, पूर्णांक affinity __maybe_unused)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक perf_mmap__aio_mmap(काष्ठा mmap *map, काष्ठा mmap_params *mp)
अणु
	पूर्णांक delta_max, i, prio, ret;

	map->aio.nr_cblocks = mp->nr_cblocks;
	अगर (map->aio.nr_cblocks) अणु
		map->aio.aiocb = सुस्मृति(map->aio.nr_cblocks, माप(काष्ठा aiocb *));
		अगर (!map->aio.aiocb) अणु
			pr_debug2("failed to allocate aiocb for data buffer, error %m\n");
			वापस -1;
		पूर्ण
		map->aio.cblocks = सुस्मृति(map->aio.nr_cblocks, माप(काष्ठा aiocb));
		अगर (!map->aio.cblocks) अणु
			pr_debug2("failed to allocate cblocks for data buffer, error %m\n");
			वापस -1;
		पूर्ण
		map->aio.data = सुस्मृति(map->aio.nr_cblocks, माप(व्योम *));
		अगर (!map->aio.data) अणु
			pr_debug2("failed to allocate data buffer, error %m\n");
			वापस -1;
		पूर्ण
		delta_max = sysconf(_SC_AIO_PRIO_DELTA_MAX);
		क्रम (i = 0; i < map->aio.nr_cblocks; ++i) अणु
			ret = perf_mmap__aio_alloc(map, i);
			अगर (ret == -1) अणु
				pr_debug2("failed to allocate data buffer area, error %m");
				वापस -1;
			पूर्ण
			ret = perf_mmap__aio_bind(map, i, map->core.cpu, mp->affinity);
			अगर (ret == -1)
				वापस -1;
			/*
			 * Use cblock.aio_fildes value dअगरferent from -1
			 * to denote started aio ग_लिखो operation on the
			 * cblock so it requires explicit record__aio_sync()
			 * call prior the cblock may be reused again.
			 */
			map->aio.cblocks[i].aio_fildes = -1;
			/*
			 * Allocate cblocks with priority delta to have
			 * faster aio ग_लिखो प्रणाली calls because queued requests
			 * are kept in separate per-prio queues and adding
			 * a new request will iterate thru लघुer per-prio
			 * list. Blocks with numbers higher than
			 *  _SC_AIO_PRIO_DELTA_MAX go with priority 0.
			 */
			prio = delta_max - i;
			map->aio.cblocks[i].aio_reqprio = prio >= 0 ? prio : 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम perf_mmap__aio_munmap(काष्ठा mmap *map)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < map->aio.nr_cblocks; ++i)
		perf_mmap__aio_मुक्त(map, i);
	अगर (map->aio.data)
		zमुक्त(&map->aio.data);
	zमुक्त(&map->aio.cblocks);
	zमुक्त(&map->aio.aiocb);
पूर्ण
#अन्यथा /* !HAVE_AIO_SUPPORT */
अटल पूर्णांक perf_mmap__aio_enabled(काष्ठा mmap *map __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक perf_mmap__aio_mmap(काष्ठा mmap *map __maybe_unused,
			       काष्ठा mmap_params *mp __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल व्योम perf_mmap__aio_munmap(काष्ठा mmap *map __maybe_unused)
अणु
पूर्ण
#पूर्ण_अगर

व्योम mmap__munmap(काष्ठा mmap *map)
अणु
	biपंचांगap_मुक्त(map->affinity_mask.bits);

	perf_mmap__aio_munmap(map);
	अगर (map->data != शून्य) अणु
		munmap(map->data, mmap__mmap_len(map));
		map->data = शून्य;
	पूर्ण
	auxtrace_mmap__munmap(&map->auxtrace_mmap);
पूर्ण

अटल व्योम build_node_mask(पूर्णांक node, काष्ठा mmap_cpu_mask *mask)
अणु
	पूर्णांक c, cpu, nr_cpus;
	स्थिर काष्ठा perf_cpu_map *cpu_map = शून्य;

	cpu_map = cpu_map__online();
	अगर (!cpu_map)
		वापस;

	nr_cpus = perf_cpu_map__nr(cpu_map);
	क्रम (c = 0; c < nr_cpus; c++) अणु
		cpu = cpu_map->map[c]; /* map c index to online cpu index */
		अगर (cpu__get_node(cpu) == node)
			set_bit(cpu, mask->bits);
	पूर्ण
पूर्ण

अटल पूर्णांक perf_mmap__setup_affinity_mask(काष्ठा mmap *map, काष्ठा mmap_params *mp)
अणु
	map->affinity_mask.nbits = cpu__max_cpu();
	map->affinity_mask.bits = biपंचांगap_alloc(map->affinity_mask.nbits);
	अगर (!map->affinity_mask.bits)
		वापस -1;

	अगर (mp->affinity == PERF_AFFINITY_NODE && cpu__max_node() > 1)
		build_node_mask(cpu__get_node(map->core.cpu), &map->affinity_mask);
	अन्यथा अगर (mp->affinity == PERF_AFFINITY_CPU)
		set_bit(map->core.cpu, map->affinity_mask.bits);

	वापस 0;
पूर्ण

पूर्णांक mmap__mmap(काष्ठा mmap *map, काष्ठा mmap_params *mp, पूर्णांक fd, पूर्णांक cpu)
अणु
	अगर (perf_mmap__mmap(&map->core, &mp->core, fd, cpu)) अणु
		pr_debug2("failed to mmap perf event ring buffer, error %d\n",
			  त्रुटि_सं);
		वापस -1;
	पूर्ण

	अगर (mp->affinity != PERF_AFFINITY_SYS &&
		perf_mmap__setup_affinity_mask(map, mp)) अणु
		pr_debug2("failed to alloc mmap affinity mask, error %d\n",
			  त्रुटि_सं);
		वापस -1;
	पूर्ण

	अगर (verbose == 2)
		mmap_cpu_mask__scnम_लिखो(&map->affinity_mask, "mmap");

	map->core.flush = mp->flush;

	map->comp_level = mp->comp_level;

	अगर (map->comp_level && !perf_mmap__aio_enabled(map)) अणु
		map->data = mmap(शून्य, mmap__mmap_len(map), PROT_READ|PROT_WRITE,
				 MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);
		अगर (map->data == MAP_FAILED) अणु
			pr_debug2("failed to mmap data buffer, error %d\n",
					त्रुटि_सं);
			map->data = शून्य;
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (auxtrace_mmap__mmap(&map->auxtrace_mmap,
				&mp->auxtrace_mp, map->core.base, fd))
		वापस -1;

	वापस perf_mmap__aio_mmap(map, mp);
पूर्ण

पूर्णांक perf_mmap__push(काष्ठा mmap *md, व्योम *to,
		    पूर्णांक push(काष्ठा mmap *map, व्योम *to, व्योम *buf, माप_प्रकार size))
अणु
	u64 head = perf_mmap__पढ़ो_head(&md->core);
	अचिन्हित अक्षर *data = md->core.base + page_size;
	अचिन्हित दीर्घ size;
	व्योम *buf;
	पूर्णांक rc = 0;

	rc = perf_mmap__पढ़ो_init(&md->core);
	अगर (rc < 0)
		वापस (rc == -EAGAIN) ? 1 : -1;

	size = md->core.end - md->core.start;

	अगर ((md->core.start & md->core.mask) + size != (md->core.end & md->core.mask)) अणु
		buf = &data[md->core.start & md->core.mask];
		size = md->core.mask + 1 - (md->core.start & md->core.mask);
		md->core.start += size;

		अगर (push(md, to, buf, size) < 0) अणु
			rc = -1;
			जाओ out;
		पूर्ण
	पूर्ण

	buf = &data[md->core.start & md->core.mask];
	size = md->core.end - md->core.start;
	md->core.start += size;

	अगर (push(md, to, buf, size) < 0) अणु
		rc = -1;
		जाओ out;
	पूर्ण

	md->core.prev = head;
	perf_mmap__consume(&md->core);
out:
	वापस rc;
पूर्ण
