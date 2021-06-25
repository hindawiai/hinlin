<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "comm.h"
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <linux/refcount.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/zभाग.स>
#समावेश "rwsem.h"

काष्ठा comm_str अणु
	अक्षर *str;
	काष्ठा rb_node rb_node;
	refcount_t refcnt;
पूर्ण;

/* Should perhaps be moved to काष्ठा machine */
अटल काष्ठा rb_root comm_str_root;
अटल काष्ठा rw_semaphore comm_str_lock = अणु.lock = PTHREAD_RWLOCK_INITIALIZER,पूर्ण;

अटल काष्ठा comm_str *comm_str__get(काष्ठा comm_str *cs)
अणु
	अगर (cs && refcount_inc_not_zero(&cs->refcnt))
		वापस cs;

	वापस शून्य;
पूर्ण

अटल व्योम comm_str__put(काष्ठा comm_str *cs)
अणु
	अगर (cs && refcount_dec_and_test(&cs->refcnt)) अणु
		करोwn_ग_लिखो(&comm_str_lock);
		rb_erase(&cs->rb_node, &comm_str_root);
		up_ग_लिखो(&comm_str_lock);
		zमुक्त(&cs->str);
		मुक्त(cs);
	पूर्ण
पूर्ण

अटल काष्ठा comm_str *comm_str__alloc(स्थिर अक्षर *str)
अणु
	काष्ठा comm_str *cs;

	cs = zalloc(माप(*cs));
	अगर (!cs)
		वापस शून्य;

	cs->str = strdup(str);
	अगर (!cs->str) अणु
		मुक्त(cs);
		वापस शून्य;
	पूर्ण

	refcount_set(&cs->refcnt, 1);

	वापस cs;
पूर्ण

अटल
काष्ठा comm_str *__comm_str__findnew(स्थिर अक्षर *str, काष्ठा rb_root *root)
अणु
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा comm_str *iter, *new;
	पूर्णांक cmp;

	जबतक (*p != शून्य) अणु
		parent = *p;
		iter = rb_entry(parent, काष्ठा comm_str, rb_node);

		/*
		 * If we race with comm_str__put, iter->refcnt is 0
		 * and it will be हटाओd within comm_str__put call
		 * लघुly, ignore it in this search.
		 */
		cmp = म_भेद(str, iter->str);
		अगर (!cmp && comm_str__get(iter))
			वापस iter;

		अगर (cmp < 0)
			p = &(*p)->rb_left;
		अन्यथा
			p = &(*p)->rb_right;
	पूर्ण

	new = comm_str__alloc(str);
	अगर (!new)
		वापस शून्य;

	rb_link_node(&new->rb_node, parent, p);
	rb_insert_color(&new->rb_node, root);

	वापस new;
पूर्ण

अटल काष्ठा comm_str *comm_str__findnew(स्थिर अक्षर *str, काष्ठा rb_root *root)
अणु
	काष्ठा comm_str *cs;

	करोwn_ग_लिखो(&comm_str_lock);
	cs = __comm_str__findnew(str, root);
	up_ग_लिखो(&comm_str_lock);

	वापस cs;
पूर्ण

काष्ठा comm *comm__new(स्थिर अक्षर *str, u64 बारtamp, bool exec)
अणु
	काष्ठा comm *comm = zalloc(माप(*comm));

	अगर (!comm)
		वापस शून्य;

	comm->start = बारtamp;
	comm->exec = exec;

	comm->comm_str = comm_str__findnew(str, &comm_str_root);
	अगर (!comm->comm_str) अणु
		मुक्त(comm);
		वापस शून्य;
	पूर्ण

	वापस comm;
पूर्ण

पूर्णांक comm__override(काष्ठा comm *comm, स्थिर अक्षर *str, u64 बारtamp, bool exec)
अणु
	काष्ठा comm_str *new, *old = comm->comm_str;

	new = comm_str__findnew(str, &comm_str_root);
	अगर (!new)
		वापस -ENOMEM;

	comm_str__put(old);
	comm->comm_str = new;
	comm->start = बारtamp;
	अगर (exec)
		comm->exec = true;

	वापस 0;
पूर्ण

व्योम comm__मुक्त(काष्ठा comm *comm)
अणु
	comm_str__put(comm->comm_str);
	मुक्त(comm);
पूर्ण

स्थिर अक्षर *comm__str(स्थिर काष्ठा comm *comm)
अणु
	वापस comm->comm_str->str;
पूर्ण
