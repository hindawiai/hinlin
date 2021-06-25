<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <perf/thपढ़ोmap.h>
#समावेश <मानककोष.स>
#समावेश <linux/refcount.h>
#समावेश <पूर्णांकernal/thपढ़ोmap.h>
#समावेश <माला.स>
#समावेश <यंत्र/bug.h>
#समावेश <मानकपन.स>

अटल व्योम perf_thपढ़ो_map__reset(काष्ठा perf_thपढ़ो_map *map, पूर्णांक start, पूर्णांक nr)
अणु
	माप_प्रकार size = (nr - start) * माप(map->map[0]);

	स_रखो(&map->map[start], 0, size);
	map->err_thपढ़ो = -1;
पूर्ण

काष्ठा perf_thपढ़ो_map *perf_thपढ़ो_map__पुनः_स्मृति(काष्ठा perf_thपढ़ो_map *map, पूर्णांक nr)
अणु
	माप_प्रकार size = माप(*map) + माप(map->map[0]) * nr;
	पूर्णांक start = map ? map->nr : 0;

	map = पुनः_स्मृति(map, size);
	/*
	 * We only पुनः_स्मृति to add more items, let's reset new items.
	 */
	अगर (map)
		perf_thपढ़ो_map__reset(map, start, nr);

	वापस map;
पूर्ण

#घोषणा thपढ़ो_map__alloc(__nr) perf_thपढ़ो_map__पुनः_स्मृति(शून्य, __nr)

व्योम perf_thपढ़ो_map__set_pid(काष्ठा perf_thपढ़ो_map *map, पूर्णांक thपढ़ो, pid_t pid)
अणु
	map->map[thपढ़ो].pid = pid;
पूर्ण

अक्षर *perf_thपढ़ो_map__comm(काष्ठा perf_thपढ़ो_map *map, पूर्णांक thपढ़ो)
अणु
	वापस map->map[thपढ़ो].comm;
पूर्ण

काष्ठा perf_thपढ़ो_map *perf_thपढ़ो_map__new_dummy(व्योम)
अणु
	काष्ठा perf_thपढ़ो_map *thपढ़ोs = thपढ़ो_map__alloc(1);

	अगर (thपढ़ोs != शून्य) अणु
		perf_thपढ़ो_map__set_pid(thपढ़ोs, 0, -1);
		thपढ़ोs->nr = 1;
		refcount_set(&thपढ़ोs->refcnt, 1);
	पूर्ण
	वापस thपढ़ोs;
पूर्ण

अटल व्योम perf_thपढ़ो_map__delete(काष्ठा perf_thपढ़ो_map *thपढ़ोs)
अणु
	अगर (thपढ़ोs) अणु
		पूर्णांक i;

		WARN_ONCE(refcount_पढ़ो(&thपढ़ोs->refcnt) != 0,
			  "thread map refcnt unbalanced\n");
		क्रम (i = 0; i < thपढ़ोs->nr; i++)
			मुक्त(perf_thपढ़ो_map__comm(thपढ़ोs, i));
		मुक्त(thपढ़ोs);
	पूर्ण
पूर्ण

काष्ठा perf_thपढ़ो_map *perf_thपढ़ो_map__get(काष्ठा perf_thपढ़ो_map *map)
अणु
	अगर (map)
		refcount_inc(&map->refcnt);
	वापस map;
पूर्ण

व्योम perf_thपढ़ो_map__put(काष्ठा perf_thपढ़ो_map *map)
अणु
	अगर (map && refcount_dec_and_test(&map->refcnt))
		perf_thपढ़ो_map__delete(map);
पूर्ण

पूर्णांक perf_thपढ़ो_map__nr(काष्ठा perf_thपढ़ो_map *thपढ़ोs)
अणु
	वापस thपढ़ोs ? thपढ़ोs->nr : 1;
पूर्ण

pid_t perf_thपढ़ो_map__pid(काष्ठा perf_thपढ़ो_map *map, पूर्णांक thपढ़ो)
अणु
	वापस map->map[thपढ़ो].pid;
पूर्ण
