<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * benchmark.c:
 * Author: Konstantin Khlebnikov <koct9i@gmail.com>
 */
#समावेश <linux/radix-tree.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <समय.स>
#समावेश "test.h"

#घोषणा NSEC_PER_SEC	1000000000L

अटल दीर्घ दीर्घ benchmark_iter(काष्ठा radix_tree_root *root, bool tagged)
अणु
	अस्थिर अचिन्हित दीर्घ sink = 0;
	काष्ठा radix_tree_iter iter;
	काष्ठा बारpec start, finish;
	दीर्घ दीर्घ nsec;
	पूर्णांक l, loops = 1;
	व्योम **slot;

#अगर_घोषित BENCHMARK
again:
#पूर्ण_अगर
	घड़ी_समय_लो(CLOCK_MONOTONIC, &start);
	क्रम (l = 0; l < loops; l++) अणु
		अगर (tagged) अणु
			radix_tree_क्रम_each_tagged(slot, root, &iter, 0, 0)
				sink ^= (अचिन्हित दीर्घ)slot;
		पूर्ण अन्यथा अणु
			radix_tree_क्रम_each_slot(slot, root, &iter, 0)
				sink ^= (अचिन्हित दीर्घ)slot;
		पूर्ण
	पूर्ण
	घड़ी_समय_लो(CLOCK_MONOTONIC, &finish);

	nsec = (finish.tv_sec - start.tv_sec) * NSEC_PER_SEC +
	       (finish.tv_nsec - start.tv_nsec);

#अगर_घोषित BENCHMARK
	अगर (loops == 1 && nsec * 5 < NSEC_PER_SEC) अणु
		loops = NSEC_PER_SEC / nsec / 4 + 1;
		जाओ again;
	पूर्ण
#पूर्ण_अगर

	nsec /= loops;
	वापस nsec;
पूर्ण

अटल व्योम benchmark_insert(काष्ठा radix_tree_root *root,
			     अचिन्हित दीर्घ size, अचिन्हित दीर्घ step)
अणु
	काष्ठा बारpec start, finish;
	अचिन्हित दीर्घ index;
	दीर्घ दीर्घ nsec;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &start);

	क्रम (index = 0 ; index < size ; index += step)
		item_insert(root, index);

	घड़ी_समय_लो(CLOCK_MONOTONIC, &finish);

	nsec = (finish.tv_sec - start.tv_sec) * NSEC_PER_SEC +
	       (finish.tv_nsec - start.tv_nsec);

	prपूर्णांकv(2, "Size: %8ld, step: %8ld, insertion: %15lld ns\n",
		size, step, nsec);
पूर्ण

अटल व्योम benchmark_tagging(काष्ठा radix_tree_root *root,
			     अचिन्हित दीर्घ size, अचिन्हित दीर्घ step)
अणु
	काष्ठा बारpec start, finish;
	अचिन्हित दीर्घ index;
	दीर्घ दीर्घ nsec;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &start);

	क्रम (index = 0 ; index < size ; index += step)
		radix_tree_tag_set(root, index, 0);

	घड़ी_समय_लो(CLOCK_MONOTONIC, &finish);

	nsec = (finish.tv_sec - start.tv_sec) * NSEC_PER_SEC +
	       (finish.tv_nsec - start.tv_nsec);

	prपूर्णांकv(2, "Size: %8ld, step: %8ld, tagging: %17lld ns\n",
		size, step, nsec);
पूर्ण

अटल व्योम benchmark_delete(काष्ठा radix_tree_root *root,
			     अचिन्हित दीर्घ size, अचिन्हित दीर्घ step)
अणु
	काष्ठा बारpec start, finish;
	अचिन्हित दीर्घ index;
	दीर्घ दीर्घ nsec;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &start);

	क्रम (index = 0 ; index < size ; index += step)
		item_delete(root, index);

	घड़ी_समय_लो(CLOCK_MONOTONIC, &finish);

	nsec = (finish.tv_sec - start.tv_sec) * NSEC_PER_SEC +
	       (finish.tv_nsec - start.tv_nsec);

	prपूर्णांकv(2, "Size: %8ld, step: %8ld, deletion: %16lld ns\n",
		size, step, nsec);
पूर्ण

अटल व्योम benchmark_size(अचिन्हित दीर्घ size, अचिन्हित दीर्घ step)
अणु
	RADIX_TREE(tree, GFP_KERNEL);
	दीर्घ दीर्घ normal, tagged;

	benchmark_insert(&tree, size, step);
	benchmark_tagging(&tree, size, step);

	tagged = benchmark_iter(&tree, true);
	normal = benchmark_iter(&tree, false);

	prपूर्णांकv(2, "Size: %8ld, step: %8ld, tagged iteration: %8lld ns\n",
		size, step, tagged);
	prपूर्णांकv(2, "Size: %8ld, step: %8ld, normal iteration: %8lld ns\n",
		size, step, normal);

	benchmark_delete(&tree, size, step);

	item_समाप्त_tree(&tree);
	rcu_barrier();
पूर्ण

व्योम benchmark(व्योम)
अणु
	अचिन्हित दीर्घ size[] = अणु1 << 10, 1 << 20, 0पूर्ण;
	अचिन्हित दीर्घ step[] = अणु1, 2, 7, 15, 63, 64, 65,
				128, 256, 512, 12345, 0पूर्ण;
	पूर्णांक c, s;

	prपूर्णांकv(1, "starting benchmarks\n");
	prपूर्णांकv(1, "RADIX_TREE_MAP_SHIFT = %d\n", RADIX_TREE_MAP_SHIFT);

	क्रम (c = 0; size[c]; c++)
		क्रम (s = 0; step[s]; s++)
			benchmark_size(size[c], step[s]);
पूर्ण
