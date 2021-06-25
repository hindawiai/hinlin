<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित WORKQUEUES_H
#घोषणा WORKQUEUES_H

#समावेश <stdbool.h>

#समावेश "barriers.h"
#समावेश "bug_on.h"
#समावेश "int_typedefs.h"

#समावेश <linux/types.h>

/* Stub workqueue implementation. */

काष्ठा work_काष्ठा;
प्रकार व्योम (*work_func_t)(काष्ठा work_काष्ठा *work);
व्योम delayed_work_समयr_fn(अचिन्हित दीर्घ __data);

काष्ठा work_काष्ठा अणु
/*	atomic_दीर्घ_t data; */
	अचिन्हित दीर्घ data;

	काष्ठा list_head entry;
	work_func_t func;
#अगर_घोषित CONFIG_LOCKDEP
	काष्ठा lockdep_map lockdep_map;
#पूर्ण_अगर
पूर्ण;

काष्ठा समयr_list अणु
	काष्ठा hlist_node	entry;
	अचिन्हित दीर्घ		expires;
	व्योम			(*function)(अचिन्हित दीर्घ);
	अचिन्हित दीर्घ		data;
	u32			flags;
	पूर्णांक			slack;
पूर्ण;

काष्ठा delayed_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा समयr_list समयr;

	/* target workqueue and CPU ->समयr uses to queue ->work */
	काष्ठा workqueue_काष्ठा *wq;
	पूर्णांक cpu;
पूर्ण;


अटल अंतरभूत bool schedule_work(काष्ठा work_काष्ठा *work)
अणु
	BUG();
	वापस true;
पूर्ण

अटल अंतरभूत bool schedule_work_on(पूर्णांक cpu, काष्ठा work_काष्ठा *work)
अणु
	BUG();
	वापस true;
पूर्ण

अटल अंतरभूत bool queue_work(काष्ठा workqueue_काष्ठा *wq,
			      काष्ठा work_काष्ठा *work)
अणु
	BUG();
	वापस true;
पूर्ण

अटल अंतरभूत bool queue_delayed_work(काष्ठा workqueue_काष्ठा *wq,
				      काष्ठा delayed_work *dwork,
				      अचिन्हित दीर्घ delay)
अणु
	BUG();
	वापस true;
पूर्ण

#घोषणा INIT_WORK(w, f) \
	करो अणु \
		(w)->data = 0; \
		(w)->func = (f); \
	पूर्ण जबतक (0)

#घोषणा INIT_DELAYED_WORK(w, f) INIT_WORK(&(w)->work, (f))

#घोषणा __WORK_INITIALIZER(n, f) अणु \
		.data = 0, \
		.entry = अणु &(n).entry, &(n).entry पूर्ण, \
		.func = f \
	पूर्ण

/* Don't bother initializing समयr. */
#घोषणा __DELAYED_WORK_INITIALIZER(n, f, tflags) अणु \
	.work = __WORK_INITIALIZER((n).work, (f)), \
	पूर्ण

#घोषणा DECLARE_WORK(n, f) \
	काष्ठा workqueue_काष्ठा n = __WORK_INITIALIZER

#घोषणा DECLARE_DELAYED_WORK(n, f) \
	काष्ठा delayed_work n = __DELAYED_WORK_INITIALIZER(n, f, 0)

#घोषणा प्रणाली_घातer_efficient_wq ((काष्ठा workqueue_काष्ठा *) शून्य)

#पूर्ण_अगर
