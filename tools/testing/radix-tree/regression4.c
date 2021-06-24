<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/slab.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/rcupdate.h>
#समावेश <मानककोष.स>
#समावेश <pthपढ़ो.h>
#समावेश <मानकपन.स>
#समावेश <निश्चित.स>

#समावेश "regression.h"

अटल pthपढ़ो_barrier_t worker_barrier;
अटल पूर्णांक obj0, obj1;
अटल RADIX_TREE(mt_tree, GFP_KERNEL);

अटल व्योम *पढ़ोer_fn(व्योम *arg)
अणु
	पूर्णांक i;
	व्योम *entry;

	rcu_रेजिस्टर_thपढ़ो();
	pthपढ़ो_barrier_रुको(&worker_barrier);

	क्रम (i = 0; i < 1000000; i++) अणु
		rcu_पढ़ो_lock();
		entry = radix_tree_lookup(&mt_tree, 0);
		rcu_पढ़ो_unlock();
		अगर (entry != &obj0) अणु
			म_लिखो("iteration %d bad entry = %p\n", i, entry);
			पात();
		पूर्ण
	पूर्ण

	rcu_unरेजिस्टर_thपढ़ो();

	वापस शून्य;
पूर्ण

अटल व्योम *ग_लिखोr_fn(व्योम *arg)
अणु
	पूर्णांक i;

	rcu_रेजिस्टर_thपढ़ो();
	pthपढ़ो_barrier_रुको(&worker_barrier);

	क्रम (i = 0; i < 1000000; i++) अणु
		radix_tree_insert(&mt_tree, 1, &obj1);
		radix_tree_delete(&mt_tree, 1);
	पूर्ण

	rcu_unरेजिस्टर_thपढ़ो();

	वापस शून्य;
पूर्ण

व्योम regression4_test(व्योम)
अणु
	pthपढ़ो_t पढ़ोer, ग_लिखोr;

	prपूर्णांकv(1, "regression test 4 starting\n");

	radix_tree_insert(&mt_tree, 0, &obj0);
	pthपढ़ो_barrier_init(&worker_barrier, शून्य, 2);

	अगर (pthपढ़ो_create(&पढ़ोer, शून्य, पढ़ोer_fn, शून्य) ||
	    pthपढ़ो_create(&ग_लिखोr, शून्य, ग_लिखोr_fn, शून्य)) अणु
		लिखो_त्रुटि("pthread_create");
		निकास(1);
	पूर्ण

	अगर (pthपढ़ो_join(पढ़ोer, शून्य) || pthपढ़ो_join(ग_लिखोr, शून्य)) अणु
		लिखो_त्रुटि("pthread_join");
		निकास(1);
	पूर्ण

	prपूर्णांकv(1, "regression test 4 passed\n");
पूर्ण
