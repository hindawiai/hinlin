<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/kernel.h>
#समावेश <linux/zभाग.स>
#समावेश <perf/cpumap.h>
#समावेश <पूर्णांकernal/cpumap.h>
#समावेश "debug.h"
#समावेश "env.h"
#समावेश "mem2node.h"
#समावेश "tests.h"

अटल काष्ठा node अणु
	पूर्णांक		 node;
	स्थिर अक्षर 	*map;
पूर्ण test_nodes[] = अणु
	अणु .node = 0, .map = "0"     पूर्ण,
	अणु .node = 1, .map = "1-2"   पूर्ण,
	अणु .node = 3, .map = "5-7,9" पूर्ण,
पूर्ण;

#घोषणा T TEST_ASSERT_VAL

अटल अचिन्हित दीर्घ *get_biपंचांगap(स्थिर अक्षर *str, पूर्णांक nbits)
अणु
	काष्ठा perf_cpu_map *map = perf_cpu_map__new(str);
	अचिन्हित दीर्घ *bm = शून्य;
	पूर्णांक i;

	bm = biपंचांगap_alloc(nbits);

	अगर (map && bm) अणु
		क्रम (i = 0; i < map->nr; i++) अणु
			set_bit(map->map[i], bm);
		पूर्ण
	पूर्ण

	अगर (map)
		perf_cpu_map__put(map);
	अन्यथा
		मुक्त(bm);

	वापस bm && map ? bm : शून्य;
पूर्ण

पूर्णांक test__mem2node(काष्ठा test *t __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा mem2node map;
	काष्ठा memory_node nodes[3];
	काष्ठा perf_env env = अणु
		.memory_nodes    = (काष्ठा memory_node *) &nodes[0],
		.nr_memory_nodes = ARRAY_SIZE(nodes),
		.memory_bsize    = 0x100,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nodes); i++) अणु
		nodes[i].node = test_nodes[i].node;
		nodes[i].size = 10;

		T("failed: alloc bitmap",
		  (nodes[i].set = get_biपंचांगap(test_nodes[i].map, 10)));
	पूर्ण

	T("failed: mem2node__init", !mem2node__init(&map, &env));
	T("failed: mem2node__node",  0 == mem2node__node(&map,   0x50));
	T("failed: mem2node__node",  1 == mem2node__node(&map,  0x100));
	T("failed: mem2node__node",  1 == mem2node__node(&map,  0x250));
	T("failed: mem2node__node",  3 == mem2node__node(&map,  0x500));
	T("failed: mem2node__node",  3 == mem2node__node(&map,  0x650));
	T("failed: mem2node__node", -1 == mem2node__node(&map,  0x450));
	T("failed: mem2node__node", -1 == mem2node__node(&map, 0x1050));

	क्रम (i = 0; i < ARRAY_SIZE(nodes); i++)
		zमुक्त(&nodes[i].set);

	mem2node__निकास(&map);
	वापस 0;
पूर्ण
