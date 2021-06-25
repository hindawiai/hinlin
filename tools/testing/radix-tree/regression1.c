<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Regression1
 * Description:
 * Salman Qazi describes the following radix-tree bug:
 *
 * In the following हाल, we get can get a deadlock:
 *
 * 0.  The radix tree contains two items, one has the index 0.
 * 1.  The पढ़ोer (in this हाल find_get_pages) takes the rcu_पढ़ो_lock.
 * 2.  The पढ़ोer acquires slot(s) क्रम item(s) including the index 0 item.
 * 3.  The non-zero index item is deleted, and as a consequence the other item
 *     is moved to the root of the tree. The place where it used to be is queued
 *     क्रम deletion after the पढ़ोers finish.
 * 3b. The zero item is deleted, removing it from the direct slot, it reमुख्यs in
 *     the rcu-delayed indirect node.
 * 4.  The पढ़ोer looks at the index 0 slot, and finds that the page has 0 ref
 *     count
 * 5.  The पढ़ोer looks at it again, hoping that the item will either be मुक्तd
 *     or the ref count will increase. This never happens, as the slot it is
 *     looking at will never be updated. Also, this slot can never be reclaimed
 *     because the पढ़ोer is holding rcu_पढ़ो_lock and is in an infinite loop.
 *
 * The fix is to re-use the same "indirect" poपूर्णांकer हाल that requires a slot
 * lookup retry पूर्णांकo a general "retry the lookup" bit.
 *
 * Running:
 * This test should run to completion in a few seconds. The above bug would
 * cause it to hang indefinitely.
 *
 * Upstream commit:
 * Not yet
 */
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

अटल RADIX_TREE(mt_tree, GFP_KERNEL);

काष्ठा page अणु
	pthपढ़ो_mutex_t lock;
	काष्ठा rcu_head rcu;
	पूर्णांक count;
	अचिन्हित दीर्घ index;
पूर्ण;

अटल काष्ठा page *page_alloc(पूर्णांक index)
अणु
	काष्ठा page *p;
	p = दो_स्मृति(माप(काष्ठा page));
	p->count = 1;
	p->index = index;
	pthपढ़ो_mutex_init(&p->lock, शून्य);

	वापस p;
पूर्ण

अटल व्योम page_rcu_मुक्त(काष्ठा rcu_head *rcu)
अणु
	काष्ठा page *p = container_of(rcu, काष्ठा page, rcu);
	निश्चित(!p->count);
	pthपढ़ो_mutex_destroy(&p->lock);
	मुक्त(p);
पूर्ण

अटल व्योम page_मुक्त(काष्ठा page *p)
अणु
	call_rcu(&p->rcu, page_rcu_मुक्त);
पूर्ण

अटल अचिन्हित find_get_pages(अचिन्हित दीर्घ start,
			    अचिन्हित पूर्णांक nr_pages, काष्ठा page **pages)
अणु
	XA_STATE(xas, &mt_tree, start);
	काष्ठा page *page;
	अचिन्हित पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	xas_क्रम_each(&xas, page, अच_दीर्घ_उच्च) अणु
		अगर (xas_retry(&xas, page))
			जारी;

		pthपढ़ो_mutex_lock(&page->lock);
		अगर (!page->count)
			जाओ unlock;

		/* करोn't actually update page refcount */
		pthपढ़ो_mutex_unlock(&page->lock);

		/* Has the page moved? */
		अगर (unlikely(page != xas_reload(&xas)))
			जाओ put_page;

		pages[ret] = page;
		ret++;
		जारी;
unlock:
		pthपढ़ो_mutex_unlock(&page->lock);
put_page:
		xas_reset(&xas);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल pthपढ़ो_barrier_t worker_barrier;

अटल व्योम *regression1_fn(व्योम *arg)
अणु
	rcu_रेजिस्टर_thपढ़ो();

	अगर (pthपढ़ो_barrier_रुको(&worker_barrier) ==
			PTHREAD_BARRIER_SERIAL_THREAD) अणु
		पूर्णांक j;

		क्रम (j = 0; j < 1000000; j++) अणु
			काष्ठा page *p;

			p = page_alloc(0);
			xa_lock(&mt_tree);
			radix_tree_insert(&mt_tree, 0, p);
			xa_unlock(&mt_tree);

			p = page_alloc(1);
			xa_lock(&mt_tree);
			radix_tree_insert(&mt_tree, 1, p);
			xa_unlock(&mt_tree);

			xa_lock(&mt_tree);
			p = radix_tree_delete(&mt_tree, 1);
			pthपढ़ो_mutex_lock(&p->lock);
			p->count--;
			pthपढ़ो_mutex_unlock(&p->lock);
			xa_unlock(&mt_tree);
			page_मुक्त(p);

			xa_lock(&mt_tree);
			p = radix_tree_delete(&mt_tree, 0);
			pthपढ़ो_mutex_lock(&p->lock);
			p->count--;
			pthपढ़ो_mutex_unlock(&p->lock);
			xa_unlock(&mt_tree);
			page_मुक्त(p);
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक j;

		क्रम (j = 0; j < 100000000; j++) अणु
			काष्ठा page *pages[10];

			find_get_pages(0, 10, pages);
		पूर्ण
	पूर्ण

	rcu_unरेजिस्टर_thपढ़ो();

	वापस शून्य;
पूर्ण

अटल pthपढ़ो_t *thपढ़ोs;
व्योम regression1_test(व्योम)
अणु
	पूर्णांक nr_thपढ़ोs;
	पूर्णांक i;
	दीर्घ arg;

	/* Regression #1 */
	prपूर्णांकv(1, "running regression test 1, should finish in under a minute\n");
	nr_thपढ़ोs = 2;
	pthपढ़ो_barrier_init(&worker_barrier, शून्य, nr_thपढ़ोs);

	thपढ़ोs = दो_स्मृति(nr_thपढ़ोs * माप(pthपढ़ो_t *));

	क्रम (i = 0; i < nr_thपढ़ोs; i++) अणु
		arg = i;
		अगर (pthपढ़ो_create(&thपढ़ोs[i], शून्य, regression1_fn, (व्योम *)arg)) अणु
			लिखो_त्रुटि("pthread_create");
			निकास(1);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < nr_thपढ़ोs; i++) अणु
		अगर (pthपढ़ो_join(thपढ़ोs[i], शून्य)) अणु
			लिखो_त्रुटि("pthread_join");
			निकास(1);
		पूर्ण
	पूर्ण

	मुक्त(thपढ़ोs);

	prपूर्णांकv(1, "regression test 1, done\n");
पूर्ण
