<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Test module क्रम stress and analyze perक्रमmance of vदो_स्मृति allocator.
 * (C) 2018 Uladzislau Rezki (Sony) <urezki@gmail.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/mm.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/slab.h>

#घोषणा __param(type, name, init, msg)		\
	अटल type name = init;				\
	module_param(name, type, 0444);			\
	MODULE_PARM_DESC(name, msg)				\

__param(पूर्णांक, nr_thपढ़ोs, 0,
	"Number of workers to perform tests(min: 1 max: USHRT_MAX)");

__param(bool, sequential_test_order, false,
	"Use sequential stress tests order");

__param(पूर्णांक, test_repeat_count, 1,
	"Set test repeat counter");

__param(पूर्णांक, test_loop_count, 1000000,
	"Set test loop counter");

__param(पूर्णांक, run_test_mask, पूर्णांक_उच्च,
	"Set tests specified in the mask.\n\n"
		"\t\tid: 1,    name: fix_size_alloc_test\n"
		"\t\tid: 2,    name: full_fit_alloc_test\n"
		"\t\tid: 4,    name: long_busy_list_alloc_test\n"
		"\t\tid: 8,    name: random_size_alloc_test\n"
		"\t\tid: 16,   name: fix_align_alloc_test\n"
		"\t\tid: 32,   name: random_size_align_alloc_test\n"
		"\t\tid: 64,   name: align_shift_alloc_test\n"
		"\t\tid: 128,  name: pcpu_alloc_test\n"
		"\t\tid: 256,  name: kvfree_rcu_1_arg_vmalloc_test\n"
		"\t\tid: 512,  name: kvfree_rcu_2_arg_vmalloc_test\n"
		/* Add a new test हाल description here. */
);

/*
 * Read ग_लिखो semaphore क्रम synchronization of setup
 * phase that is करोne in मुख्य thपढ़ो and workers.
 */
अटल DECLARE_RWSEM(prepare_क्रम_test_rwsem);

/*
 * Completion tracking क्रम worker thपढ़ोs.
 */
अटल DECLARE_COMPLETION(test_all_करोne_comp);
अटल atomic_t test_n_unकरोne = ATOMIC_INIT(0);

अटल अंतरभूत व्योम
test_report_one_करोne(व्योम)
अणु
	अगर (atomic_dec_and_test(&test_n_unकरोne))
		complete(&test_all_करोne_comp);
पूर्ण

अटल पूर्णांक अक्रमom_size_align_alloc_test(व्योम)
अणु
	अचिन्हित दीर्घ size, align, rnd;
	व्योम *ptr;
	पूर्णांक i;

	क्रम (i = 0; i < test_loop_count; i++) अणु
		get_अक्रमom_bytes(&rnd, माप(rnd));

		/*
		 * Maximum 1024 pages, अगर PAGE_SIZE is 4096.
		 */
		align = 1 << (rnd % 23);

		/*
		 * Maximum 10 pages.
		 */
		size = ((rnd % 10) + 1) * PAGE_SIZE;

		ptr = __vदो_स्मृति_node(size, align, GFP_KERNEL | __GFP_ZERO, 0,
				__builtin_वापस_address(0));
		अगर (!ptr)
			वापस -1;

		vमुक्त(ptr);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This test हाल is supposed to be failed.
 */
अटल पूर्णांक align_shअगरt_alloc_test(व्योम)
अणु
	अचिन्हित दीर्घ align;
	व्योम *ptr;
	पूर्णांक i;

	क्रम (i = 0; i < BITS_PER_LONG; i++) अणु
		align = ((अचिन्हित दीर्घ) 1) << i;

		ptr = __vदो_स्मृति_node(PAGE_SIZE, align, GFP_KERNEL|__GFP_ZERO, 0,
				__builtin_वापस_address(0));
		अगर (!ptr)
			वापस -1;

		vमुक्त(ptr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fix_align_alloc_test(व्योम)
अणु
	व्योम *ptr;
	पूर्णांक i;

	क्रम (i = 0; i < test_loop_count; i++) अणु
		ptr = __vदो_स्मृति_node(5 * PAGE_SIZE, THREAD_ALIGN << 1,
				GFP_KERNEL | __GFP_ZERO, 0,
				__builtin_वापस_address(0));
		अगर (!ptr)
			वापस -1;

		vमुक्त(ptr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक अक्रमom_size_alloc_test(व्योम)
अणु
	अचिन्हित पूर्णांक n;
	व्योम *p;
	पूर्णांक i;

	क्रम (i = 0; i < test_loop_count; i++) अणु
		get_अक्रमom_bytes(&n, माप(i));
		n = (n % 100) + 1;

		p = vदो_स्मृति(n * PAGE_SIZE);

		अगर (!p)
			वापस -1;

		*((__u8 *)p) = 1;
		vमुक्त(p);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक दीर्घ_busy_list_alloc_test(व्योम)
अणु
	व्योम *ptr_1, *ptr_2;
	व्योम **ptr;
	पूर्णांक rv = -1;
	पूर्णांक i;

	ptr = vदो_स्मृति(माप(व्योम *) * 15000);
	अगर (!ptr)
		वापस rv;

	क्रम (i = 0; i < 15000; i++)
		ptr[i] = vदो_स्मृति(1 * PAGE_SIZE);

	क्रम (i = 0; i < test_loop_count; i++) अणु
		ptr_1 = vदो_स्मृति(100 * PAGE_SIZE);
		अगर (!ptr_1)
			जाओ leave;

		ptr_2 = vदो_स्मृति(1 * PAGE_SIZE);
		अगर (!ptr_2) अणु
			vमुक्त(ptr_1);
			जाओ leave;
		पूर्ण

		*((__u8 *)ptr_1) = 0;
		*((__u8 *)ptr_2) = 1;

		vमुक्त(ptr_1);
		vमुक्त(ptr_2);
	पूर्ण

	/*  Success */
	rv = 0;

leave:
	क्रम (i = 0; i < 15000; i++)
		vमुक्त(ptr[i]);

	vमुक्त(ptr);
	वापस rv;
पूर्ण

अटल पूर्णांक full_fit_alloc_test(व्योम)
अणु
	व्योम **ptr, **junk_ptr, *पंचांगp;
	पूर्णांक junk_length;
	पूर्णांक rv = -1;
	पूर्णांक i;

	junk_length = fls(num_online_cpus());
	junk_length *= (32 * 1024 * 1024 / PAGE_SIZE);

	ptr = vदो_स्मृति(माप(व्योम *) * junk_length);
	अगर (!ptr)
		वापस rv;

	junk_ptr = vदो_स्मृति(माप(व्योम *) * junk_length);
	अगर (!junk_ptr) अणु
		vमुक्त(ptr);
		वापस rv;
	पूर्ण

	क्रम (i = 0; i < junk_length; i++) अणु
		ptr[i] = vदो_स्मृति(1 * PAGE_SIZE);
		junk_ptr[i] = vदो_स्मृति(1 * PAGE_SIZE);
	पूर्ण

	क्रम (i = 0; i < junk_length; i++)
		vमुक्त(junk_ptr[i]);

	क्रम (i = 0; i < test_loop_count; i++) अणु
		पंचांगp = vदो_स्मृति(1 * PAGE_SIZE);

		अगर (!पंचांगp)
			जाओ error;

		*((__u8 *)पंचांगp) = 1;
		vमुक्त(पंचांगp);
	पूर्ण

	/* Success */
	rv = 0;

error:
	क्रम (i = 0; i < junk_length; i++)
		vमुक्त(ptr[i]);

	vमुक्त(ptr);
	vमुक्त(junk_ptr);

	वापस rv;
पूर्ण

अटल पूर्णांक fix_size_alloc_test(व्योम)
अणु
	व्योम *ptr;
	पूर्णांक i;

	क्रम (i = 0; i < test_loop_count; i++) अणु
		ptr = vदो_स्मृति(3 * PAGE_SIZE);

		अगर (!ptr)
			वापस -1;

		*((__u8 *)ptr) = 0;

		vमुक्त(ptr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
pcpu_alloc_test(व्योम)
अणु
	पूर्णांक rv = 0;
#अगर_अघोषित CONFIG_NEED_PER_CPU_KM
	व्योम __percpu **pcpu;
	माप_प्रकार size, align;
	पूर्णांक i;

	pcpu = vदो_स्मृति(माप(व्योम __percpu *) * 35000);
	अगर (!pcpu)
		वापस -1;

	क्रम (i = 0; i < 35000; i++) अणु
		अचिन्हित पूर्णांक r;

		get_अक्रमom_bytes(&r, माप(i));
		size = (r % (PAGE_SIZE / 4)) + 1;

		/*
		 * Maximum PAGE_SIZE
		 */
		get_अक्रमom_bytes(&r, माप(i));
		align = 1 << ((i % 11) + 1);

		pcpu[i] = __alloc_percpu(size, align);
		अगर (!pcpu[i])
			rv = -1;
	पूर्ण

	क्रम (i = 0; i < 35000; i++)
		मुक्त_percpu(pcpu[i]);

	vमुक्त(pcpu);
#पूर्ण_अगर
	वापस rv;
पूर्ण

काष्ठा test_kvमुक्त_rcu अणु
	काष्ठा rcu_head rcu;
	अचिन्हित अक्षर array[20];
पूर्ण;

अटल पूर्णांक
kvमुक्त_rcu_1_arg_vदो_स्मृति_test(व्योम)
अणु
	काष्ठा test_kvमुक्त_rcu *p;
	पूर्णांक i;

	क्रम (i = 0; i < test_loop_count; i++) अणु
		p = vदो_स्मृति(1 * PAGE_SIZE);
		अगर (!p)
			वापस -1;

		p->array[0] = 'a';
		kvमुक्त_rcu(p);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
kvमुक्त_rcu_2_arg_vदो_स्मृति_test(व्योम)
अणु
	काष्ठा test_kvमुक्त_rcu *p;
	पूर्णांक i;

	क्रम (i = 0; i < test_loop_count; i++) अणु
		p = vदो_स्मृति(1 * PAGE_SIZE);
		अगर (!p)
			वापस -1;

		p->array[0] = 'a';
		kvमुक्त_rcu(p, rcu);
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा test_हाल_desc अणु
	स्थिर अक्षर *test_name;
	पूर्णांक (*test_func)(व्योम);
पूर्ण;

अटल काष्ठा test_हाल_desc test_हाल_array[] = अणु
	अणु "fix_size_alloc_test", fix_size_alloc_test पूर्ण,
	अणु "full_fit_alloc_test", full_fit_alloc_test पूर्ण,
	अणु "long_busy_list_alloc_test", दीर्घ_busy_list_alloc_test पूर्ण,
	अणु "random_size_alloc_test", अक्रमom_size_alloc_test पूर्ण,
	अणु "fix_align_alloc_test", fix_align_alloc_test पूर्ण,
	अणु "random_size_align_alloc_test", अक्रमom_size_align_alloc_test पूर्ण,
	अणु "align_shift_alloc_test", align_shअगरt_alloc_test पूर्ण,
	अणु "pcpu_alloc_test", pcpu_alloc_test पूर्ण,
	अणु "kvfree_rcu_1_arg_vmalloc_test", kvमुक्त_rcu_1_arg_vदो_स्मृति_test पूर्ण,
	अणु "kvfree_rcu_2_arg_vmalloc_test", kvमुक्त_rcu_2_arg_vदो_स्मृति_test पूर्ण,
	/* Add a new test हाल here. */
पूर्ण;

काष्ठा test_हाल_data अणु
	पूर्णांक test_failed;
	पूर्णांक test_passed;
	u64 समय;
पूर्ण;

अटल काष्ठा test_driver अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा test_हाल_data data[ARRAY_SIZE(test_हाल_array)];

	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ stop;
पूर्ण *tdriver;

अटल व्योम shuffle_array(पूर्णांक *arr, पूर्णांक n)
अणु
	अचिन्हित पूर्णांक rnd;
	पूर्णांक i, j, x;

	क्रम (i = n - 1; i > 0; i--)  अणु
		get_अक्रमom_bytes(&rnd, माप(rnd));

		/* Cut the range. */
		j = rnd % i;

		/* Swap indexes. */
		x = arr[i];
		arr[i] = arr[j];
		arr[j] = x;
	पूर्ण
पूर्ण

अटल पूर्णांक test_func(व्योम *निजी)
अणु
	काष्ठा test_driver *t = निजी;
	पूर्णांक अक्रमom_array[ARRAY_SIZE(test_हाल_array)];
	पूर्णांक index, i, j;
	kसमय_प्रकार kt;
	u64 delta;

	क्रम (i = 0; i < ARRAY_SIZE(test_हाल_array); i++)
		अक्रमom_array[i] = i;

	अगर (!sequential_test_order)
		shuffle_array(अक्रमom_array, ARRAY_SIZE(test_हाल_array));

	/*
	 * Block until initialization is करोne.
	 */
	करोwn_पढ़ो(&prepare_क्रम_test_rwsem);

	t->start = get_cycles();
	क्रम (i = 0; i < ARRAY_SIZE(test_हाल_array); i++) अणु
		index = अक्रमom_array[i];

		/*
		 * Skip tests अगर run_test_mask has been specअगरied.
		 */
		अगर (!((run_test_mask & (1 << index)) >> index))
			जारी;

		kt = kसमय_get();
		क्रम (j = 0; j < test_repeat_count; j++) अणु
			अगर (!test_हाल_array[index].test_func())
				t->data[index].test_passed++;
			अन्यथा
				t->data[index].test_failed++;
		पूर्ण

		/*
		 * Take an average समय that test took.
		 */
		delta = (u64) kसमय_us_delta(kसमय_get(), kt);
		करो_भाग(delta, (u32) test_repeat_count);

		t->data[index].समय = delta;
	पूर्ण
	t->stop = get_cycles();

	up_पढ़ो(&prepare_क्रम_test_rwsem);
	test_report_one_करोne();

	/*
	 * Wait क्रम the kthपढ़ो_stop() call.
	 */
	जबतक (!kthपढ़ो_should_stop())
		msleep(10);

	वापस 0;
पूर्ण

अटल पूर्णांक
init_test_configurtion(व्योम)
अणु
	/*
	 * A maximum number of workers is defined as hard-coded
	 * value and set to अच_लघु_उच्च. We add such gap just in
	 * हाल and क्रम potential heavy stressing.
	 */
	nr_thपढ़ोs = clamp(nr_thपढ़ोs, 1, (पूर्णांक) अच_लघु_उच्च);

	/* Allocate the space क्रम test instances. */
	tdriver = kvसुस्मृति(nr_thपढ़ोs, माप(*tdriver), GFP_KERNEL);
	अगर (tdriver == शून्य)
		वापस -1;

	अगर (test_repeat_count <= 0)
		test_repeat_count = 1;

	अगर (test_loop_count <= 0)
		test_loop_count = 1;

	वापस 0;
पूर्ण

अटल व्योम करो_concurrent_test(व्योम)
अणु
	पूर्णांक i, ret;

	/*
	 * Set some basic configurations plus sanity check.
	 */
	ret = init_test_configurtion();
	अगर (ret < 0)
		वापस;

	/*
	 * Put on hold all workers.
	 */
	करोwn_ग_लिखो(&prepare_क्रम_test_rwsem);

	क्रम (i = 0; i < nr_thपढ़ोs; i++) अणु
		काष्ठा test_driver *t = &tdriver[i];

		t->task = kthपढ़ो_run(test_func, t, "vmalloc_test/%d", i);

		अगर (!IS_ERR(t->task))
			/* Success. */
			atomic_inc(&test_n_unकरोne);
		अन्यथा
			pr_err("Failed to start %d kthread\n", i);
	पूर्ण

	/*
	 * Now let the workers करो their job.
	 */
	up_ग_लिखो(&prepare_क्रम_test_rwsem);

	/*
	 * Sleep quiet until all workers are करोne with 1 second
	 * पूर्णांकerval. Since the test can take a lot of समय we
	 * can run पूर्णांकo a stack trace of the hung task. That is
	 * why we go with completion_समयout and HZ value.
	 */
	करो अणु
		ret = रुको_क्रम_completion_समयout(&test_all_करोne_comp, HZ);
	पूर्ण जबतक (!ret);

	क्रम (i = 0; i < nr_thपढ़ोs; i++) अणु
		काष्ठा test_driver *t = &tdriver[i];
		पूर्णांक j;

		अगर (!IS_ERR(t->task))
			kthपढ़ो_stop(t->task);

		क्रम (j = 0; j < ARRAY_SIZE(test_हाल_array); j++) अणु
			अगर (!((run_test_mask & (1 << j)) >> j))
				जारी;

			pr_info(
				"Summary: %s passed: %d failed: %d repeat: %d loops: %d avg: %llu usec\n",
				test_हाल_array[j].test_name,
				t->data[j].test_passed,
				t->data[j].test_failed,
				test_repeat_count, test_loop_count,
				t->data[j].समय);
		पूर्ण

		pr_info("All test took worker%d=%lu cycles\n",
			i, t->stop - t->start);
	पूर्ण

	kvमुक्त(tdriver);
पूर्ण

अटल पूर्णांक vदो_स्मृति_test_init(व्योम)
अणु
	करो_concurrent_test();
	वापस -EAGAIN; /* Fail will directly unload the module */
पूर्ण

अटल व्योम vदो_स्मृति_test_निकास(व्योम)
अणु
पूर्ण

module_init(vदो_स्मृति_test_init)
module_निकास(vदो_स्मृति_test_निकास)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Uladzislau Rezki");
MODULE_DESCRIPTION("vmalloc test module");
