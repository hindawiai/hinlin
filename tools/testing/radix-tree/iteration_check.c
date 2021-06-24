<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * iteration_check.c: test races having to करो with xarray iteration
 * Copyright (c) 2016 Intel Corporation
 * Author: Ross Zwisler <ross.zwisler@linux.पूर्णांकel.com>
 */
#समावेश <pthपढ़ो.h>
#समावेश "test.h"

#घोषणा NUM_THREADS	5
#घोषणा MAX_IDX		100
#घोषणा TAG		XA_MARK_0
#घोषणा NEW_TAG		XA_MARK_1

अटल pthपढ़ो_t thपढ़ोs[NUM_THREADS];
अटल अचिन्हित पूर्णांक seeds[3];
अटल DEFINE_XARRAY(array);
अटल bool test_complete;
अटल पूर्णांक max_order;

व्योम my_item_insert(काष्ठा xarray *xa, अचिन्हित दीर्घ index)
अणु
	XA_STATE(xas, xa, index);
	काष्ठा item *item = item_create(index, 0);
	पूर्णांक order;

retry:
	xas_lock(&xas);
	क्रम (order = max_order; order >= 0; order--) अणु
		xas_set_order(&xas, index, order);
		item->order = order;
		अगर (xas_find_conflict(&xas))
			जारी;
		xas_store(&xas, item);
		xas_set_mark(&xas, TAG);
		अवरोध;
	पूर्ण
	xas_unlock(&xas);
	अगर (xas_nomem(&xas, GFP_KERNEL))
		जाओ retry;
	अगर (order < 0)
		मुक्त(item);
पूर्ण

/* relentlessly fill the array with tagged entries */
अटल व्योम *add_entries_fn(व्योम *arg)
अणु
	rcu_रेजिस्टर_thपढ़ो();

	जबतक (!test_complete) अणु
		अचिन्हित दीर्घ pgoff;

		क्रम (pgoff = 0; pgoff < MAX_IDX; pgoff++) अणु
			my_item_insert(&array, pgoff);
		पूर्ण
	पूर्ण

	rcu_unरेजिस्टर_thपढ़ो();

	वापस शून्य;
पूर्ण

/*
 * Iterate over tagged entries, retrying when we find ourselves in a deleted
 * node and अक्रमomly pausing the iteration.
 */
अटल व्योम *tagged_iteration_fn(व्योम *arg)
अणु
	XA_STATE(xas, &array, 0);
	व्योम *entry;

	rcu_रेजिस्टर_thपढ़ो();

	जबतक (!test_complete) अणु
		xas_set(&xas, 0);
		rcu_पढ़ो_lock();
		xas_क्रम_each_marked(&xas, entry, अच_दीर्घ_उच्च, TAG) अणु
			अगर (xas_retry(&xas, entry))
				जारी;

			अगर (अक्रम_r(&seeds[0]) % 50 == 0) अणु
				xas_छोड़ो(&xas);
				rcu_पढ़ो_unlock();
				rcu_barrier();
				rcu_पढ़ो_lock();
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	rcu_unरेजिस्टर_thपढ़ो();

	वापस शून्य;
पूर्ण

/*
 * Iterate over the entries, retrying when we find ourselves in a deleted
 * node and अक्रमomly pausing the iteration.
 */
अटल व्योम *untagged_iteration_fn(व्योम *arg)
अणु
	XA_STATE(xas, &array, 0);
	व्योम *entry;

	rcu_रेजिस्टर_thपढ़ो();

	जबतक (!test_complete) अणु
		xas_set(&xas, 0);
		rcu_पढ़ो_lock();
		xas_क्रम_each(&xas, entry, अच_दीर्घ_उच्च) अणु
			अगर (xas_retry(&xas, entry))
				जारी;

			अगर (अक्रम_r(&seeds[1]) % 50 == 0) अणु
				xas_छोड़ो(&xas);
				rcu_पढ़ो_unlock();
				rcu_barrier();
				rcu_पढ़ो_lock();
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	rcu_unरेजिस्टर_thपढ़ो();

	वापस शून्य;
पूर्ण

/*
 * Ranकरोmly हटाओ entries to help induce retries in the
 * two iteration functions.
 */
अटल व्योम *हटाओ_entries_fn(व्योम *arg)
अणु
	rcu_रेजिस्टर_thपढ़ो();

	जबतक (!test_complete) अणु
		पूर्णांक pgoff;
		काष्ठा item *item;

		pgoff = अक्रम_r(&seeds[2]) % MAX_IDX;

		item = xa_erase(&array, pgoff);
		अगर (item)
			item_मुक्त(item, pgoff);
	पूर्ण

	rcu_unरेजिस्टर_thपढ़ो();

	वापस शून्य;
पूर्ण

अटल व्योम *tag_entries_fn(व्योम *arg)
अणु
	rcu_रेजिस्टर_thपढ़ो();

	जबतक (!test_complete) अणु
		tag_tagged_items(&array, 0, MAX_IDX, 10, TAG, NEW_TAG);
	पूर्ण
	rcu_unरेजिस्टर_thपढ़ो();
	वापस शून्य;
पूर्ण

/* This is a unit test क्रम a bug found by the syzkaller tester */
व्योम iteration_test(अचिन्हित order, अचिन्हित test_duration)
अणु
	पूर्णांक i;

	prपूर्णांकv(1, "Running %siteration tests for %d seconds\n",
			order > 0 ? "multiorder " : "", test_duration);

	max_order = order;
	test_complete = false;

	क्रम (i = 0; i < 3; i++)
		seeds[i] = अक्रम();

	अगर (pthपढ़ो_create(&thपढ़ोs[0], शून्य, tagged_iteration_fn, शून्य)) अणु
		लिखो_त्रुटि("create tagged iteration thread");
		निकास(1);
	पूर्ण
	अगर (pthपढ़ो_create(&thपढ़ोs[1], शून्य, untagged_iteration_fn, शून्य)) अणु
		लिखो_त्रुटि("create untagged iteration thread");
		निकास(1);
	पूर्ण
	अगर (pthपढ़ो_create(&thपढ़ोs[2], शून्य, add_entries_fn, शून्य)) अणु
		लिखो_त्रुटि("create add entry thread");
		निकास(1);
	पूर्ण
	अगर (pthपढ़ो_create(&thपढ़ोs[3], शून्य, हटाओ_entries_fn, शून्य)) अणु
		लिखो_त्रुटि("create remove entry thread");
		निकास(1);
	पूर्ण
	अगर (pthपढ़ो_create(&thपढ़ोs[4], शून्य, tag_entries_fn, शून्य)) अणु
		लिखो_त्रुटि("create tag entry thread");
		निकास(1);
	पूर्ण

	sleep(test_duration);
	test_complete = true;

	क्रम (i = 0; i < NUM_THREADS; i++) अणु
		अगर (pthपढ़ो_join(thपढ़ोs[i], शून्य)) अणु
			लिखो_त्रुटि("pthread_join");
			निकास(1);
		पूर्ण
	पूर्ण

	item_समाप्त_tree(&array);
पूर्ण
