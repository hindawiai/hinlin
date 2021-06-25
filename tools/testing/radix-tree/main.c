<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <समय.स>
#समावेश <निश्चित.स>
#समावेश <सीमा.स>

#समावेश <linux/slab.h>
#समावेश <linux/radix-tree.h>

#समावेश "test.h"
#समावेश "regression.h"

व्योम __gang_check(अचिन्हित दीर्घ middle, दीर्घ करोwn, दीर्घ up, पूर्णांक chunk, पूर्णांक hop)
अणु
	दीर्घ idx;
	RADIX_TREE(tree, GFP_KERNEL);

	middle = 1 << 30;

	क्रम (idx = -करोwn; idx < up; idx++)
		item_insert(&tree, middle + idx);

	item_check_असलent(&tree, middle - करोwn - 1);
	क्रम (idx = -करोwn; idx < up; idx++)
		item_check_present(&tree, middle + idx);
	item_check_असलent(&tree, middle + up);

	अगर (chunk > 0) अणु
		item_gang_check_present(&tree, middle - करोwn, up + करोwn,
				chunk, hop);
		item_full_scan(&tree, middle - करोwn, करोwn + up, chunk);
	पूर्ण
	item_समाप्त_tree(&tree);
पूर्ण

व्योम gang_check(व्योम)
अणु
	__gang_check(1UL << 30, 128, 128, 35, 2);
	__gang_check(1UL << 31, 128, 128, 32, 32);
	__gang_check(1UL << 31, 128, 128, 32, 100);
	__gang_check(1UL << 31, 128, 128, 17, 7);
	__gang_check(0xffff0000UL, 0, 65536, 17, 7);
	__gang_check(0xfffffffeUL, 1, 1, 17, 7);
पूर्ण

व्योम __big_gang_check(व्योम)
अणु
	अचिन्हित दीर्घ start;
	पूर्णांक wrapped = 0;

	start = 0;
	करो अणु
		अचिन्हित दीर्घ old_start;

//		म_लिखो("0x%08lx\n", start);
		__gang_check(start, अक्रम() % 113 + 1, अक्रम() % 71,
				अक्रम() % 157, अक्रम() % 91 + 1);
		old_start = start;
		start += अक्रम() % 1000000;
		start %= 1ULL << 33;
		अगर (start < old_start)
			wrapped = 1;
	पूर्ण जबतक (!wrapped);
पूर्ण

व्योम big_gang_check(bool दीर्घ_run)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < (दीर्घ_run ? 1000 : 3); i++) अणु
		__big_gang_check();
		prपूर्णांकv(2, "%d ", i);
		ख_साफ(मानक_निकास);
	पूर्ण
पूर्ण

व्योम add_and_check(व्योम)
अणु
	RADIX_TREE(tree, GFP_KERNEL);

	item_insert(&tree, 44);
	item_check_present(&tree, 44);
	item_check_असलent(&tree, 43);
	item_समाप्त_tree(&tree);
पूर्ण

व्योम dynamic_height_check(व्योम)
अणु
	पूर्णांक i;
	RADIX_TREE(tree, GFP_KERNEL);
	tree_verअगरy_min_height(&tree, 0);

	item_insert(&tree, 42);
	tree_verअगरy_min_height(&tree, 42);

	item_insert(&tree, 1000000);
	tree_verअगरy_min_height(&tree, 1000000);

	निश्चित(item_delete(&tree, 1000000));
	tree_verअगरy_min_height(&tree, 42);

	निश्चित(item_delete(&tree, 42));
	tree_verअगरy_min_height(&tree, 0);

	क्रम (i = 0; i < 1000; i++) अणु
		item_insert(&tree, i);
		tree_verअगरy_min_height(&tree, i);
	पूर्ण

	i--;
	क्रम (;;) अणु
		निश्चित(item_delete(&tree, i));
		अगर (i == 0) अणु
			tree_verअगरy_min_height(&tree, 0);
			अवरोध;
		पूर्ण
		i--;
		tree_verअगरy_min_height(&tree, i);
	पूर्ण

	item_समाप्त_tree(&tree);
पूर्ण

व्योम check_copied_tags(काष्ठा radix_tree_root *tree, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, अचिन्हित दीर्घ *idx, पूर्णांक count, पूर्णांक fromtag, पूर्णांक totag)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
/*		अगर (i % 1000 == 0)
			अक्षर_दो('.'); */
		अगर (idx[i] < start || idx[i] > end) अणु
			अगर (item_tag_get(tree, idx[i], totag)) अणु
				prपूर्णांकv(2, "%lu-%lu: %lu, tags %d-%d\n", start,
				       end, idx[i], item_tag_get(tree, idx[i],
								 fromtag),
				       item_tag_get(tree, idx[i], totag));
			पूर्ण
			निश्चित(!item_tag_get(tree, idx[i], totag));
			जारी;
		पूर्ण
		अगर (item_tag_get(tree, idx[i], fromtag) ^
			item_tag_get(tree, idx[i], totag)) अणु
			prपूर्णांकv(2, "%lu-%lu: %lu, tags %d-%d\n", start, end,
			       idx[i], item_tag_get(tree, idx[i], fromtag),
			       item_tag_get(tree, idx[i], totag));
		पूर्ण
		निश्चित(!(item_tag_get(tree, idx[i], fromtag) ^
			 item_tag_get(tree, idx[i], totag)));
	पूर्ण
पूर्ण

#घोषणा ITEMS 50000

व्योम copy_tag_check(व्योम)
अणु
	RADIX_TREE(tree, GFP_KERNEL);
	अचिन्हित दीर्घ idx[ITEMS];
	अचिन्हित दीर्घ start, end, count = 0, tagged, cur, पंचांगp;
	पूर्णांक i;

//	म_लिखो("generating radix tree indices...\n");
	start = अक्रम();
	end = अक्रम();
	अगर (start > end && (अक्रम() % 10)) अणु
		cur = start;
		start = end;
		end = cur;
	पूर्ण
	/* Specअगरically create items around the start and the end of the range
	 * with high probability to check क्रम off by one errors */
	cur = अक्रम();
	अगर (cur & 1) अणु
		item_insert(&tree, start);
		अगर (cur & 2) अणु
			अगर (start <= end)
				count++;
			item_tag_set(&tree, start, 0);
		पूर्ण
	पूर्ण
	अगर (cur & 4) अणु
		item_insert(&tree, start-1);
		अगर (cur & 8)
			item_tag_set(&tree, start-1, 0);
	पूर्ण
	अगर (cur & 16) अणु
		item_insert(&tree, end);
		अगर (cur & 32) अणु
			अगर (start <= end)
				count++;
			item_tag_set(&tree, end, 0);
		पूर्ण
	पूर्ण
	अगर (cur & 64) अणु
		item_insert(&tree, end+1);
		अगर (cur & 128)
			item_tag_set(&tree, end+1, 0);
	पूर्ण

	क्रम (i = 0; i < ITEMS; i++) अणु
		करो अणु
			idx[i] = अक्रम();
		पूर्ण जबतक (item_lookup(&tree, idx[i]));

		item_insert(&tree, idx[i]);
		अगर (अक्रम() & 1) अणु
			item_tag_set(&tree, idx[i], 0);
			अगर (idx[i] >= start && idx[i] <= end)
				count++;
		पूर्ण
/*		अगर (i % 1000 == 0)
			अक्षर_दो('.'); */
	पूर्ण

//	म_लिखो("\ncopying tags...\n");
	tagged = tag_tagged_items(&tree, start, end, ITEMS, XA_MARK_0, XA_MARK_1);

//	म_लिखो("checking copied tags\n");
	निश्चित(tagged == count);
	check_copied_tags(&tree, start, end, idx, ITEMS, 0, 1);

	/* Copy tags in several rounds */
//	म_लिखो("\ncopying tags...\n");
	पंचांगp = अक्रम() % (count / 10 + 2);
	tagged = tag_tagged_items(&tree, start, end, पंचांगp, XA_MARK_0, XA_MARK_2);
	निश्चित(tagged == count);

//	म_लिखो("%lu %lu %lu\n", tagged, पंचांगp, count);
//	म_लिखो("checking copied tags\n");
	check_copied_tags(&tree, start, end, idx, ITEMS, 0, 2);
	verअगरy_tag_consistency(&tree, 0);
	verअगरy_tag_consistency(&tree, 1);
	verअगरy_tag_consistency(&tree, 2);
//	म_लिखो("\n");
	item_समाप्त_tree(&tree);
पूर्ण

अटल व्योम single_thपढ़ो_tests(bool दीर्घ_run)
अणु
	पूर्णांक i;

	prपूर्णांकv(1, "starting single_thread_tests: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	multiorder_checks();
	rcu_barrier();
	prपूर्णांकv(2, "after multiorder_check: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	tag_check();
	rcu_barrier();
	prपूर्णांकv(2, "after tag_check: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	gang_check();
	rcu_barrier();
	prपूर्णांकv(2, "after gang_check: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	add_and_check();
	rcu_barrier();
	prपूर्णांकv(2, "after add_and_check: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	dynamic_height_check();
	rcu_barrier();
	prपूर्णांकv(2, "after dynamic_height_check: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	idr_checks();
	ida_tests();
	rcu_barrier();
	prपूर्णांकv(2, "after idr_checks: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	big_gang_check(दीर्घ_run);
	rcu_barrier();
	prपूर्णांकv(2, "after big_gang_check: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	क्रम (i = 0; i < (दीर्घ_run ? 2000 : 3); i++) अणु
		copy_tag_check();
		prपूर्णांकv(2, "%d ", i);
		ख_साफ(मानक_निकास);
	पूर्ण
	rcu_barrier();
	prपूर्णांकv(2, "after copy_tag_check: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	bool दीर्घ_run = false;
	पूर्णांक opt;
	अचिन्हित पूर्णांक seed = समय(शून्य);

	जबतक ((opt = getopt(argc, argv, "ls:v")) != -1) अणु
		अगर (opt == 'l')
			दीर्घ_run = true;
		अन्यथा अगर (opt == 's')
			seed = म_से_अदीर्घ(optarg, शून्य, 0);
		अन्यथा अगर (opt == 'v')
			test_verbose++;
	पूर्ण

	म_लिखो("random seed %u\n", seed);
	बेक्रम(seed);

	म_लिखो("running tests\n");

	rcu_रेजिस्टर_thपढ़ो();
	radix_tree_init();

	xarray_tests();
	regression1_test();
	regression2_test();
	regression3_test();
	regression4_test();
	iteration_test(0, 10 + 90 * दीर्घ_run);
	iteration_test(7, 10 + 90 * दीर्घ_run);
	iteration_test2(10 + 90 * दीर्घ_run);
	single_thपढ़ो_tests(दीर्घ_run);

	/* Free any reमुख्यing pपुनः_स्मृतिated nodes */
	radix_tree_cpu_dead(0);

	benchmark();

	rcu_barrier();
	prपूर्णांकv(2, "after rcu_barrier: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	rcu_unरेजिस्टर_thपढ़ो();

	म_लिखो("tests completed\n");

	निकास(0);
पूर्ण
