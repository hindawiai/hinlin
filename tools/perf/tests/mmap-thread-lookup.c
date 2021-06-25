<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <पूर्णांकtypes.h>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <sys/mman.h>
#समावेश <pthपढ़ो.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश "debug.h"
#समावेश "event.h"
#समावेश "tests.h"
#समावेश "machine.h"
#समावेश "thread_map.h"
#समावेश "map.h"
#समावेश "symbol.h"
#समावेश "util/synthetic-events.h"
#समावेश "thread.h"
#समावेश <पूर्णांकernal/lib.h> // page_size

#घोषणा THREADS 4

अटल पूर्णांक go_away;

काष्ठा thपढ़ो_data अणु
	pthपढ़ो_t	pt;
	pid_t		tid;
	व्योम		*map;
	पूर्णांक		पढ़ोy[2];
पूर्ण;

अटल काष्ठा thपढ़ो_data thपढ़ोs[THREADS];

अटल पूर्णांक thपढ़ो_init(काष्ठा thपढ़ो_data *td)
अणु
	व्योम *map;

	map = mmap(शून्य, page_size,
		   PROT_READ|PROT_WRITE|PROT_EXEC,
		   MAP_SHARED|MAP_ANONYMOUS, -1, 0);

	अगर (map == MAP_FAILED) अणु
		लिखो_त्रुटि("mmap failed");
		वापस -1;
	पूर्ण

	td->map = map;
	td->tid = syscall(SYS_gettid);

	pr_debug("tid = %d, map = %p\n", td->tid, map);
	वापस 0;
पूर्ण

अटल व्योम *thपढ़ो_fn(व्योम *arg)
अणु
	काष्ठा thपढ़ो_data *td = arg;
	sमाप_प्रकार ret;
	पूर्णांक go = 0;

	अगर (thपढ़ो_init(td))
		वापस शून्य;

	/* Signal thपढ़ो_create thपढ़ो is initialized. */
	ret = ग_लिखो(td->पढ़ोy[1], &go, माप(पूर्णांक));
	अगर (ret != माप(पूर्णांक)) अणु
		pr_err("failed to notify\n");
		वापस शून्य;
	पूर्ण

	जबतक (!go_away) अणु
		/* Waiting क्रम मुख्य thपढ़ो to समाप्त us. */
		usleep(100);
	पूर्ण

	munmap(td->map, page_size);
	वापस शून्य;
पूर्ण

अटल पूर्णांक thपढ़ो_create(पूर्णांक i)
अणु
	काष्ठा thपढ़ो_data *td = &thपढ़ोs[i];
	पूर्णांक err, go;

	अगर (pipe(td->पढ़ोy))
		वापस -1;

	err = pthपढ़ो_create(&td->pt, शून्य, thपढ़ो_fn, td);
	अगर (!err) अणु
		/* Wait क्रम thपढ़ो initialization. */
		sमाप_प्रकार ret = पढ़ो(td->पढ़ोy[0], &go, माप(पूर्णांक));
		err = ret != माप(पूर्णांक);
	पूर्ण

	बंद(td->पढ़ोy[0]);
	बंद(td->पढ़ोy[1]);
	वापस err;
पूर्ण

अटल पूर्णांक thपढ़ोs_create(व्योम)
अणु
	काष्ठा thपढ़ो_data *td0 = &thपढ़ोs[0];
	पूर्णांक i, err = 0;

	go_away = 0;

	/* 0 is मुख्य thपढ़ो */
	अगर (thपढ़ो_init(td0))
		वापस -1;

	क्रम (i = 1; !err && i < THREADS; i++)
		err = thपढ़ो_create(i);

	वापस err;
पूर्ण

अटल पूर्णांक thपढ़ोs_destroy(व्योम)
अणु
	काष्ठा thपढ़ो_data *td0 = &thपढ़ोs[0];
	पूर्णांक i, err = 0;

	/* cleanup the मुख्य thपढ़ो */
	munmap(td0->map, page_size);

	go_away = 1;

	क्रम (i = 1; !err && i < THREADS; i++)
		err = pthपढ़ो_join(thपढ़ोs[i].pt, शून्य);

	वापस err;
पूर्ण

प्रकार पूर्णांक (*synth_cb)(काष्ठा machine *machine);

अटल पूर्णांक synth_all(काष्ठा machine *machine)
अणु
	वापस perf_event__syntheमाप_प्रकारhपढ़ोs(शून्य,
					      perf_event__process,
					      machine, 0, 1);
पूर्ण

अटल पूर्णांक synth_process(काष्ठा machine *machine)
अणु
	काष्ठा perf_thपढ़ो_map *map;
	पूर्णांक err;

	map = thपढ़ो_map__new_by_pid(getpid());

	err = perf_event__syntheमाप_प्रकारhपढ़ो_map(शून्य, map,
						perf_event__process,
						machine, 0);

	perf_thपढ़ो_map__put(map);
	वापस err;
पूर्ण

अटल पूर्णांक mmap_events(synth_cb synth)
अणु
	काष्ठा machine *machine;
	पूर्णांक err, i;

	/*
	 * The thपढ़ोs_create will not वापस beक्रमe all thपढ़ोs
	 * are spawned and all created memory map.
	 *
	 * They will loop until thपढ़ोs_destroy is called, so we
	 * can safely run synthesizing function.
	 */
	TEST_ASSERT_VAL("failed to create threads", !thपढ़ोs_create());

	machine = machine__new_host();

	dump_trace = verbose > 1 ? 1 : 0;

	err = synth(machine);

	dump_trace = 0;

	TEST_ASSERT_VAL("failed to destroy threads", !thपढ़ोs_destroy());
	TEST_ASSERT_VAL("failed to synthesize maps", !err);

	/*
	 * All data is synthesized, try to find map क्रम each
	 * thपढ़ो object.
	 */
	क्रम (i = 0; i < THREADS; i++) अणु
		काष्ठा thपढ़ो_data *td = &thपढ़ोs[i];
		काष्ठा addr_location al;
		काष्ठा thपढ़ो *thपढ़ो;

		thपढ़ो = machine__findnew_thपढ़ो(machine, getpid(), td->tid);

		pr_debug("looking for map %p\n", td->map);

		thपढ़ो__find_map(thपढ़ो, PERF_RECORD_MISC_USER,
				 (अचिन्हित दीर्घ) (td->map + 1), &al);

		thपढ़ो__put(thपढ़ो);

		अगर (!al.map) अणु
			pr_debug("failed, couldn't find map\n");
			err = -1;
			अवरोध;
		पूर्ण

		pr_debug("map %p, addr %" PRIx64 "\n", al.map, al.map->start);
	पूर्ण

	machine__delete_thपढ़ोs(machine);
	machine__delete(machine);
	वापस err;
पूर्ण

/*
 * This test creates 'THREADS' number of thपढ़ोs (including
 * मुख्य thपढ़ो) and each thपढ़ो creates memory map.
 *
 * When thपढ़ोs are created, we synthesize them with both
 * (separate tests):
 *   perf_event__syntheमाप_प्रकारhपढ़ो_map (process based)
 *   perf_event__syntheमाप_प्रकारhपढ़ोs    (global)
 *
 * We test we can find all memory maps via:
 *   thपढ़ो__find_map
 *
 * by using all thपढ़ो objects.
 */
पूर्णांक test__mmap_thपढ़ो_lookup(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	/* perf_event__syntheमाप_प्रकारhपढ़ोs synthesize */
	TEST_ASSERT_VAL("failed with sythesizing all",
			!mmap_events(synth_all));

	/* perf_event__syntheमाप_प्रकारhपढ़ो_map synthesize */
	TEST_ASSERT_VAL("failed with sythesizing process",
			!mmap_events(synth_process));

	वापस 0;
पूर्ण
