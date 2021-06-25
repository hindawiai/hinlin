<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Helper functions to sync execution between parent and child processes.
 *
 * Copyright 2018, Thiago Jung Bauermann, IBM Corporation.
 */
#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <semaphore.h>

/*
 * Inक्रमmation in a shared memory location क्रम synchronization between child and
 * parent.
 */
काष्ठा child_sync अणु
	/* The parent रुकोs on this semaphore. */
	sem_t sem_parent;

	/* If true, the child should give up as well. */
	bool parent_gave_up;

	/* The child रुकोs on this semaphore. */
	sem_t sem_child;

	/* If true, the parent should give up as well. */
	bool child_gave_up;
पूर्ण;

#घोषणा CHILD_FAIL_IF(x, sync)						\
	करो अणु								\
		अगर (x) अणु						\
			ख_लिखो(मानक_त्रुटि,					\
				"[FAIL] Test FAILED on line %d\n", __LINE__); \
			(sync)->child_gave_up = true;			\
			prod_parent(sync);				\
			वापस 1;					\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा PARENT_FAIL_IF(x, sync)						\
	करो अणु								\
		अगर (x) अणु						\
			ख_लिखो(मानक_त्रुटि,					\
				"[FAIL] Test FAILED on line %d\n", __LINE__); \
			(sync)->parent_gave_up = true;			\
			prod_child(sync);				\
			वापस 1;					\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा PARENT_SKIP_IF_UNSUPPORTED(x, sync)				\
	करो अणु								\
		अगर ((x) == -1 && (त्रुटि_सं == ENODEV || त्रुटि_सं == EINVAL)) अणु \
			(sync)->parent_gave_up = true;			\
			prod_child(sync);				\
			SKIP_IF(1);					\
		पूर्ण							\
	पूर्ण जबतक (0)

पूर्णांक init_child_sync(काष्ठा child_sync *sync)
अणु
	पूर्णांक ret;

	ret = sem_init(&sync->sem_parent, 1, 0);
	अगर (ret) अणु
		लिखो_त्रुटि("Semaphore initialization failed");
		वापस 1;
	पूर्ण

	ret = sem_init(&sync->sem_child, 1, 0);
	अगर (ret) अणु
		लिखो_त्रुटि("Semaphore initialization failed");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम destroy_child_sync(काष्ठा child_sync *sync)
अणु
	sem_destroy(&sync->sem_parent);
	sem_destroy(&sync->sem_child);
पूर्ण

पूर्णांक रुको_child(काष्ठा child_sync *sync)
अणु
	पूर्णांक ret;

	/* Wait until the child prods us. */
	ret = sem_रुको(&sync->sem_parent);
	अगर (ret) अणु
		लिखो_त्रुटि("Error waiting for child");
		वापस 1;
	पूर्ण

	वापस sync->child_gave_up;
पूर्ण

पूर्णांक prod_child(काष्ठा child_sync *sync)
अणु
	पूर्णांक ret;

	/* Unblock the child now. */
	ret = sem_post(&sync->sem_child);
	अगर (ret) अणु
		लिखो_त्रुटि("Error prodding child");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक रुको_parent(काष्ठा child_sync *sync)
अणु
	पूर्णांक ret;

	/* Wait until the parent prods us. */
	ret = sem_रुको(&sync->sem_child);
	अगर (ret) अणु
		लिखो_त्रुटि("Error waiting for parent");
		वापस 1;
	पूर्ण

	वापस sync->parent_gave_up;
पूर्ण

पूर्णांक prod_parent(काष्ठा child_sync *sync)
अणु
	पूर्णांक ret;

	/* Unblock the parent now. */
	ret = sem_post(&sync->sem_parent);
	अगर (ret) अणु
		लिखो_त्रुटि("Error prodding parent");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
