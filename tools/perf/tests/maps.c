<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश "tests.h"
#समावेश "map.h"
#समावेश "maps.h"
#समावेश "dso.h"
#समावेश "debug.h"

काष्ठा map_def अणु
	स्थिर अक्षर *name;
	u64 start;
	u64 end;
पूर्ण;

अटल पूर्णांक check_maps(काष्ठा map_def *merged, अचिन्हित पूर्णांक size, काष्ठा maps *maps)
अणु
	काष्ठा map *map;
	अचिन्हित पूर्णांक i = 0;

	maps__क्रम_each_entry(maps, map) अणु
		अगर (i > 0)
			TEST_ASSERT_VAL("less maps expected", (map && i < size) || (!map && i == size));

		TEST_ASSERT_VAL("wrong map start",  map->start == merged[i].start);
		TEST_ASSERT_VAL("wrong map end",    map->end == merged[i].end);
		TEST_ASSERT_VAL("wrong map name",  !म_भेद(map->dso->name, merged[i].name));
		TEST_ASSERT_VAL("wrong map refcnt", refcount_पढ़ो(&map->refcnt) == 1);

		i++;
	पूर्ण

	वापस TEST_OK;
पूर्ण

पूर्णांक test__maps__merge_in(काष्ठा test *t __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा maps maps;
	अचिन्हित पूर्णांक i;
	काष्ठा map_def bpf_progs[] = अणु
		अणु "bpf_prog_1", 200, 300 पूर्ण,
		अणु "bpf_prog_2", 500, 600 पूर्ण,
		अणु "bpf_prog_3", 800, 900 पूर्ण,
	पूर्ण;
	काष्ठा map_def merged12[] = अणु
		अणु "kcore1",     100,  200 पूर्ण,
		अणु "bpf_prog_1", 200,  300 पूर्ण,
		अणु "kcore1",     300,  500 पूर्ण,
		अणु "bpf_prog_2", 500,  600 पूर्ण,
		अणु "kcore1",     600,  800 पूर्ण,
		अणु "bpf_prog_3", 800,  900 पूर्ण,
		अणु "kcore1",     900, 1000 पूर्ण,
	पूर्ण;
	काष्ठा map_def merged3[] = अणु
		अणु "kcore1",      100,  200 पूर्ण,
		अणु "bpf_prog_1",  200,  300 पूर्ण,
		अणु "kcore1",      300,  500 पूर्ण,
		अणु "bpf_prog_2",  500,  600 पूर्ण,
		अणु "kcore1",      600,  800 पूर्ण,
		अणु "bpf_prog_3",  800,  900 पूर्ण,
		अणु "kcore1",      900, 1000 पूर्ण,
		अणु "kcore3",     1000, 1100 पूर्ण,
	पूर्ण;
	काष्ठा map *map_kcore1, *map_kcore2, *map_kcore3;
	पूर्णांक ret;

	maps__init(&maps, शून्य);

	क्रम (i = 0; i < ARRAY_SIZE(bpf_progs); i++) अणु
		काष्ठा map *map;

		map = dso__new_map(bpf_progs[i].name);
		TEST_ASSERT_VAL("failed to create map", map);

		map->start = bpf_progs[i].start;
		map->end   = bpf_progs[i].end;
		maps__insert(&maps, map);
		map__put(map);
	पूर्ण

	map_kcore1 = dso__new_map("kcore1");
	TEST_ASSERT_VAL("failed to create map", map_kcore1);

	map_kcore2 = dso__new_map("kcore2");
	TEST_ASSERT_VAL("failed to create map", map_kcore2);

	map_kcore3 = dso__new_map("kcore3");
	TEST_ASSERT_VAL("failed to create map", map_kcore3);

	/* kcore1 map overlaps over all bpf maps */
	map_kcore1->start = 100;
	map_kcore1->end   = 1000;

	/* kcore2 map hides behind bpf_prog_2 */
	map_kcore2->start = 550;
	map_kcore2->end   = 570;

	/* kcore3 map hides behind bpf_prog_3, kcore1 and adds new map */
	map_kcore3->start = 880;
	map_kcore3->end   = 1100;

	ret = maps__merge_in(&maps, map_kcore1);
	TEST_ASSERT_VAL("failed to merge map", !ret);

	ret = check_maps(merged12, ARRAY_SIZE(merged12), &maps);
	TEST_ASSERT_VAL("merge check failed", !ret);

	ret = maps__merge_in(&maps, map_kcore2);
	TEST_ASSERT_VAL("failed to merge map", !ret);

	ret = check_maps(merged12, ARRAY_SIZE(merged12), &maps);
	TEST_ASSERT_VAL("merge check failed", !ret);

	ret = maps__merge_in(&maps, map_kcore3);
	TEST_ASSERT_VAL("failed to merge map", !ret);

	ret = check_maps(merged3, ARRAY_SIZE(merged3), &maps);
	TEST_ASSERT_VAL("merge check failed", !ret);
	वापस TEST_OK;
पूर्ण
