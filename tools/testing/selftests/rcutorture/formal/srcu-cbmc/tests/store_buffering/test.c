<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <src/combined_source.c>

पूर्णांक x;
पूर्णांक y;

पूर्णांक __unbuffered_tpr_x;
पूर्णांक __unbuffered_tpr_y;

DEFINE_SRCU(ss);

व्योम rcu_पढ़ोer(व्योम)
अणु
	पूर्णांक idx;

#अगर_अघोषित FORCE_FAILURE_3
	idx = srcu_पढ़ो_lock(&ss);
#पूर्ण_अगर
	might_sleep();

	__unbuffered_tpr_y = READ_ONCE(y);
#अगर_घोषित FORCE_FAILURE
	srcu_पढ़ो_unlock(&ss, idx);
	idx = srcu_पढ़ो_lock(&ss);
#पूर्ण_अगर
	WRITE_ONCE(x, 1);

#अगर_अघोषित FORCE_FAILURE_3
	srcu_पढ़ो_unlock(&ss, idx);
#पूर्ण_अगर
	might_sleep();
पूर्ण

व्योम *thपढ़ो_update(व्योम *arg)
अणु
	WRITE_ONCE(y, 1);
#अगर_अघोषित FORCE_FAILURE_2
	synchronize_srcu(&ss);
#पूर्ण_अगर
	might_sleep();
	__unbuffered_tpr_x = READ_ONCE(x);

	वापस शून्य;
पूर्ण

व्योम *thपढ़ो_process_पढ़ोer(व्योम *arg)
अणु
	rcu_पढ़ोer();

	वापस शून्य;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	pthपढ़ो_t tu;
	pthपढ़ो_t tpr;

	अगर (pthपढ़ो_create(&tu, शून्य, thपढ़ो_update, शून्य))
		पात();
	अगर (pthपढ़ो_create(&tpr, शून्य, thपढ़ो_process_पढ़ोer, शून्य))
		पात();
	अगर (pthपढ़ो_join(tu, शून्य))
		पात();
	अगर (pthपढ़ो_join(tpr, शून्य))
		पात();
	निश्चित(__unbuffered_tpr_y != 0 || __unbuffered_tpr_x != 0);

#अगर_घोषित ASSERT_END
	निश्चित(0);
#पूर्ण_अगर

	वापस 0;
पूर्ण
