<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * iteration_check_2.c: Check that deleting a tagged entry करोesn't cause
 * an RCU walker to finish early.
 * Copyright (c) 2020 Oracle
 * Author: Matthew Wilcox <willy@infradead.org>
 */
#समावेश <pthपढ़ो.h>
#समावेश "test.h"

अटल अस्थिर bool test_complete;

अटल व्योम *iterator(व्योम *arg)
अणु
	XA_STATE(xas, arg, 0);
	व्योम *entry;

	rcu_रेजिस्टर_thपढ़ो();

	जबतक (!test_complete) अणु
		xas_set(&xas, 0);
		rcu_पढ़ो_lock();
		xas_क्रम_each_marked(&xas, entry, अच_दीर्घ_उच्च, XA_MARK_0)
			;
		rcu_पढ़ो_unlock();
		निश्चित(xas.xa_index >= 100);
	पूर्ण

	rcu_unरेजिस्टर_thपढ़ो();
	वापस शून्य;
पूर्ण

अटल व्योम *throbber(व्योम *arg)
अणु
	काष्ठा xarray *xa = arg;

	rcu_रेजिस्टर_thपढ़ो();

	जबतक (!test_complete) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 100; i++) अणु
			xa_store(xa, i, xa_mk_value(i), GFP_KERNEL);
			xa_set_mark(xa, i, XA_MARK_0);
		पूर्ण
		क्रम (i = 0; i < 100; i++)
			xa_erase(xa, i);
	पूर्ण

	rcu_unरेजिस्टर_thपढ़ो();
	वापस शून्य;
पूर्ण

व्योम iteration_test2(अचिन्हित test_duration)
अणु
	pthपढ़ो_t thपढ़ोs[2];
	DEFINE_XARRAY(array);
	पूर्णांक i;

	prपूर्णांकv(1, "Running iteration test 2 for %d seconds\n", test_duration);

	test_complete = false;

	xa_store(&array, 100, xa_mk_value(100), GFP_KERNEL);
	xa_set_mark(&array, 100, XA_MARK_0);

	अगर (pthपढ़ो_create(&thपढ़ोs[0], शून्य, iterator, &array)) अणु
		लिखो_त्रुटि("create iterator thread");
		निकास(1);
	पूर्ण
	अगर (pthपढ़ो_create(&thपढ़ोs[1], शून्य, throbber, &array)) अणु
		लिखो_त्रुटि("create throbber thread");
		निकास(1);
	पूर्ण

	sleep(test_duration);
	test_complete = true;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (pthपढ़ो_join(thपढ़ोs[i], शून्य)) अणु
			लिखो_त्रुटि("pthread_join");
			निकास(1);
		पूर्ण
	पूर्ण

	xa_destroy(&array);
पूर्ण
