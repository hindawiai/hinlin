<शैली गुरु>
#अगर_अघोषित INTERNAL_IO_WQ_H
#घोषणा INTERNAL_IO_WQ_H

#समावेश <linux/refcount.h>

काष्ठा io_wq;

क्रमागत अणु
	IO_WQ_WORK_CANCEL	= 1,
	IO_WQ_WORK_HASHED	= 2,
	IO_WQ_WORK_UNBOUND	= 4,
	IO_WQ_WORK_CONCURRENT	= 16,

	IO_WQ_HASH_SHIFT	= 24,	/* upper 8 bits are used क्रम hash key */
पूर्ण;

क्रमागत io_wq_cancel अणु
	IO_WQ_CANCEL_OK,	/* cancelled beक्रमe started */
	IO_WQ_CANCEL_RUNNING,	/* found, running, and attempted cancelled */
	IO_WQ_CANCEL_NOTFOUND,	/* work not found */
पूर्ण;

काष्ठा io_wq_work_node अणु
	काष्ठा io_wq_work_node *next;
पूर्ण;

काष्ठा io_wq_work_list अणु
	काष्ठा io_wq_work_node *first;
	काष्ठा io_wq_work_node *last;
पूर्ण;

अटल अंतरभूत व्योम wq_list_add_after(काष्ठा io_wq_work_node *node,
				     काष्ठा io_wq_work_node *pos,
				     काष्ठा io_wq_work_list *list)
अणु
	काष्ठा io_wq_work_node *next = pos->next;

	pos->next = node;
	node->next = next;
	अगर (!next)
		list->last = node;
पूर्ण

अटल अंतरभूत व्योम wq_list_add_tail(काष्ठा io_wq_work_node *node,
				    काष्ठा io_wq_work_list *list)
अणु
	अगर (!list->first) अणु
		list->last = node;
		WRITE_ONCE(list->first, node);
	पूर्ण अन्यथा अणु
		list->last->next = node;
		list->last = node;
	पूर्ण
	node->next = शून्य;
पूर्ण

अटल अंतरभूत व्योम wq_list_cut(काष्ठा io_wq_work_list *list,
			       काष्ठा io_wq_work_node *last,
			       काष्ठा io_wq_work_node *prev)
अणु
	/* first in the list, अगर prev==शून्य */
	अगर (!prev)
		WRITE_ONCE(list->first, last->next);
	अन्यथा
		prev->next = last->next;

	अगर (last == list->last)
		list->last = prev;
	last->next = शून्य;
पूर्ण

अटल अंतरभूत व्योम wq_list_del(काष्ठा io_wq_work_list *list,
			       काष्ठा io_wq_work_node *node,
			       काष्ठा io_wq_work_node *prev)
अणु
	wq_list_cut(list, node, prev);
पूर्ण

#घोषणा wq_list_क्रम_each(pos, prv, head)			\
	क्रम (pos = (head)->first, prv = शून्य; pos; prv = pos, pos = (pos)->next)

#घोषणा wq_list_empty(list)	(READ_ONCE((list)->first) == शून्य)
#घोषणा INIT_WQ_LIST(list)	करो अणु				\
	(list)->first = शून्य;					\
	(list)->last = शून्य;					\
पूर्ण जबतक (0)

काष्ठा io_wq_work अणु
	काष्ठा io_wq_work_node list;
	स्थिर काष्ठा cred *creds;
	अचिन्हित flags;
पूर्ण;

अटल अंतरभूत काष्ठा io_wq_work *wq_next_work(काष्ठा io_wq_work *work)
अणु
	अगर (!work->list.next)
		वापस शून्य;

	वापस container_of(work->list.next, काष्ठा io_wq_work, list);
पूर्ण

प्रकार काष्ठा io_wq_work *(मुक्त_work_fn)(काष्ठा io_wq_work *);
प्रकार व्योम (io_wq_work_fn)(काष्ठा io_wq_work *);

काष्ठा io_wq_hash अणु
	refcount_t refs;
	अचिन्हित दीर्घ map;
	काष्ठा रुको_queue_head रुको;
पूर्ण;

अटल अंतरभूत व्योम io_wq_put_hash(काष्ठा io_wq_hash *hash)
अणु
	अगर (refcount_dec_and_test(&hash->refs))
		kमुक्त(hash);
पूर्ण

काष्ठा io_wq_data अणु
	काष्ठा io_wq_hash *hash;
	काष्ठा task_काष्ठा *task;
	io_wq_work_fn *करो_work;
	मुक्त_work_fn *मुक्त_work;
पूर्ण;

काष्ठा io_wq *io_wq_create(अचिन्हित bounded, काष्ठा io_wq_data *data);
व्योम io_wq_निकास_start(काष्ठा io_wq *wq);
व्योम io_wq_put_and_निकास(काष्ठा io_wq *wq);

व्योम io_wq_enqueue(काष्ठा io_wq *wq, काष्ठा io_wq_work *work);
व्योम io_wq_hash_work(काष्ठा io_wq_work *work, व्योम *val);

अटल अंतरभूत bool io_wq_is_hashed(काष्ठा io_wq_work *work)
अणु
	वापस work->flags & IO_WQ_WORK_HASHED;
पूर्ण

प्रकार bool (work_cancel_fn)(काष्ठा io_wq_work *, व्योम *);

क्रमागत io_wq_cancel io_wq_cancel_cb(काष्ठा io_wq *wq, work_cancel_fn *cancel,
					व्योम *data, bool cancel_all);

#अगर defined(CONFIG_IO_WQ)
बाह्य व्योम io_wq_worker_sleeping(काष्ठा task_काष्ठा *);
बाह्य व्योम io_wq_worker_running(काष्ठा task_काष्ठा *);
#अन्यथा
अटल अंतरभूत व्योम io_wq_worker_sleeping(काष्ठा task_काष्ठा *tsk)
अणु
पूर्ण
अटल अंतरभूत व्योम io_wq_worker_running(काष्ठा task_काष्ठा *tsk)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool io_wq_current_is_worker(व्योम)
अणु
	वापस in_task() && (current->flags & PF_IO_WORKER) &&
		current->pf_io_worker;
पूर्ण
#पूर्ण_अगर
