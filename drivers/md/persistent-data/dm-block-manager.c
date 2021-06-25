<शैली गुरु>
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */
#समावेश "dm-block-manager.h"
#समावेश "dm-persistent-data-internal.h"

#समावेश <linux/dm-bufपन.स>
#समावेश <linux/crc32c.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/device-mapper.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/sched/task.h>

#घोषणा DM_MSG_PREFIX "block manager"

/*----------------------------------------------------------------*/

#अगर_घोषित CONFIG_DM_DEBUG_BLOCK_MANAGER_LOCKING

/*
 * This is a पढ़ो/ग_लिखो semaphore with a couple of dअगरferences.
 *
 * i) There is a restriction on the number of concurrent पढ़ो locks that
 * may be held at once.  This is just an implementation detail.
 *
 * ii) Recursive locking attempts are detected and वापस EINVAL.  A stack
 * trace is also emitted क्रम the previous lock acquisition.
 *
 * iii) Priority is given to ग_लिखो locks.
 */
#घोषणा MAX_HOLDERS 4
#घोषणा MAX_STACK 10

काष्ठा stack_store अणु
	अचिन्हित पूर्णांक	nr_entries;
	अचिन्हित दीर्घ	entries[MAX_STACK];
पूर्ण;

काष्ठा block_lock अणु
	spinlock_t lock;
	__s32 count;
	काष्ठा list_head रुकोers;
	काष्ठा task_काष्ठा *holders[MAX_HOLDERS];

#अगर_घोषित CONFIG_DM_DEBUG_BLOCK_STACK_TRACING
	काष्ठा stack_store traces[MAX_HOLDERS];
#पूर्ण_अगर
पूर्ण;

काष्ठा रुकोer अणु
	काष्ठा list_head list;
	काष्ठा task_काष्ठा *task;
	पूर्णांक wants_ग_लिखो;
पूर्ण;

अटल अचिन्हित __find_holder(काष्ठा block_lock *lock,
			      काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < MAX_HOLDERS; i++)
		अगर (lock->holders[i] == task)
			अवरोध;

	BUG_ON(i == MAX_HOLDERS);
	वापस i;
पूर्ण

/* call this *after* you increment lock->count */
अटल व्योम __add_holder(काष्ठा block_lock *lock, काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित h = __find_holder(lock, शून्य);
#अगर_घोषित CONFIG_DM_DEBUG_BLOCK_STACK_TRACING
	काष्ठा stack_store *t;
#पूर्ण_अगर

	get_task_काष्ठा(task);
	lock->holders[h] = task;

#अगर_घोषित CONFIG_DM_DEBUG_BLOCK_STACK_TRACING
	t = lock->traces + h;
	t->nr_entries = stack_trace_save(t->entries, MAX_STACK, 2);
#पूर्ण_अगर
पूर्ण

/* call this *beक्रमe* you decrement lock->count */
अटल व्योम __del_holder(काष्ठा block_lock *lock, काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित h = __find_holder(lock, task);
	lock->holders[h] = शून्य;
	put_task_काष्ठा(task);
पूर्ण

अटल पूर्णांक __check_holder(काष्ठा block_lock *lock)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < MAX_HOLDERS; i++) अणु
		अगर (lock->holders[i] == current) अणु
			DMERR("recursive lock detected in metadata");
#अगर_घोषित CONFIG_DM_DEBUG_BLOCK_STACK_TRACING
			DMERR("previously held here:");
			stack_trace_prपूर्णांक(lock->traces[i].entries,
					  lock->traces[i].nr_entries, 4);

			DMERR("subsequent acquisition attempted here:");
			dump_stack();
#पूर्ण_अगर
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __रुको(काष्ठा रुकोer *w)
अणु
	क्रम (;;) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);

		अगर (!w->task)
			अवरोध;

		schedule();
	पूर्ण

	set_current_state(TASK_RUNNING);
पूर्ण

अटल व्योम __wake_रुकोer(काष्ठा रुकोer *w)
अणु
	काष्ठा task_काष्ठा *task;

	list_del(&w->list);
	task = w->task;
	smp_mb();
	w->task = शून्य;
	wake_up_process(task);
पूर्ण

/*
 * We either wake a few पढ़ोers or a single ग_लिखोr.
 */
अटल व्योम __wake_many(काष्ठा block_lock *lock)
अणु
	काष्ठा रुकोer *w, *पंचांगp;

	BUG_ON(lock->count < 0);
	list_क्रम_each_entry_safe(w, पंचांगp, &lock->रुकोers, list) अणु
		अगर (lock->count >= MAX_HOLDERS)
			वापस;

		अगर (w->wants_ग_लिखो) अणु
			अगर (lock->count > 0)
				वापस; /* still पढ़ो locked */

			lock->count = -1;
			__add_holder(lock, w->task);
			__wake_रुकोer(w);
			वापस;
		पूर्ण

		lock->count++;
		__add_holder(lock, w->task);
		__wake_रुकोer(w);
	पूर्ण
पूर्ण

अटल व्योम bl_init(काष्ठा block_lock *lock)
अणु
	पूर्णांक i;

	spin_lock_init(&lock->lock);
	lock->count = 0;
	INIT_LIST_HEAD(&lock->रुकोers);
	क्रम (i = 0; i < MAX_HOLDERS; i++)
		lock->holders[i] = शून्य;
पूर्ण

अटल पूर्णांक __available_क्रम_पढ़ो(काष्ठा block_lock *lock)
अणु
	वापस lock->count >= 0 &&
		lock->count < MAX_HOLDERS &&
		list_empty(&lock->रुकोers);
पूर्ण

अटल पूर्णांक bl_करोwn_पढ़ो(काष्ठा block_lock *lock)
अणु
	पूर्णांक r;
	काष्ठा रुकोer w;

	spin_lock(&lock->lock);
	r = __check_holder(lock);
	अगर (r) अणु
		spin_unlock(&lock->lock);
		वापस r;
	पूर्ण

	अगर (__available_क्रम_पढ़ो(lock)) अणु
		lock->count++;
		__add_holder(lock, current);
		spin_unlock(&lock->lock);
		वापस 0;
	पूर्ण

	get_task_काष्ठा(current);

	w.task = current;
	w.wants_ग_लिखो = 0;
	list_add_tail(&w.list, &lock->रुकोers);
	spin_unlock(&lock->lock);

	__रुको(&w);
	put_task_काष्ठा(current);
	वापस 0;
पूर्ण

अटल पूर्णांक bl_करोwn_पढ़ो_nonblock(काष्ठा block_lock *lock)
अणु
	पूर्णांक r;

	spin_lock(&lock->lock);
	r = __check_holder(lock);
	अगर (r)
		जाओ out;

	अगर (__available_क्रम_पढ़ो(lock)) अणु
		lock->count++;
		__add_holder(lock, current);
		r = 0;
	पूर्ण अन्यथा
		r = -EWOULDBLOCK;

out:
	spin_unlock(&lock->lock);
	वापस r;
पूर्ण

अटल व्योम bl_up_पढ़ो(काष्ठा block_lock *lock)
अणु
	spin_lock(&lock->lock);
	BUG_ON(lock->count <= 0);
	__del_holder(lock, current);
	--lock->count;
	अगर (!list_empty(&lock->रुकोers))
		__wake_many(lock);
	spin_unlock(&lock->lock);
पूर्ण

अटल पूर्णांक bl_करोwn_ग_लिखो(काष्ठा block_lock *lock)
अणु
	पूर्णांक r;
	काष्ठा रुकोer w;

	spin_lock(&lock->lock);
	r = __check_holder(lock);
	अगर (r) अणु
		spin_unlock(&lock->lock);
		वापस r;
	पूर्ण

	अगर (lock->count == 0 && list_empty(&lock->रुकोers)) अणु
		lock->count = -1;
		__add_holder(lock, current);
		spin_unlock(&lock->lock);
		वापस 0;
	पूर्ण

	get_task_काष्ठा(current);
	w.task = current;
	w.wants_ग_लिखो = 1;

	/*
	 * Writers given priority. We know there's only one mutator in the
	 * प्रणाली, so ignoring the ordering reversal.
	 */
	list_add(&w.list, &lock->रुकोers);
	spin_unlock(&lock->lock);

	__रुको(&w);
	put_task_काष्ठा(current);

	वापस 0;
पूर्ण

अटल व्योम bl_up_ग_लिखो(काष्ठा block_lock *lock)
अणु
	spin_lock(&lock->lock);
	__del_holder(lock, current);
	lock->count = 0;
	अगर (!list_empty(&lock->रुकोers))
		__wake_many(lock);
	spin_unlock(&lock->lock);
पूर्ण

अटल व्योम report_recursive_bug(dm_block_t b, पूर्णांक r)
अणु
	अगर (r == -EINVAL)
		DMERR("recursive acquisition of block %llu requested.",
		      (अचिन्हित दीर्घ दीर्घ) b);
पूर्ण

#अन्यथा  /* !CONFIG_DM_DEBUG_BLOCK_MANAGER_LOCKING */

#घोषणा bl_init(x) करो अणु पूर्ण जबतक (0)
#घोषणा bl_करोwn_पढ़ो(x) 0
#घोषणा bl_करोwn_पढ़ो_nonblock(x) 0
#घोषणा bl_up_पढ़ो(x) करो अणु पूर्ण जबतक (0)
#घोषणा bl_करोwn_ग_लिखो(x) 0
#घोषणा bl_up_ग_लिखो(x) करो अणु पूर्ण जबतक (0)
#घोषणा report_recursive_bug(x, y) करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_DM_DEBUG_BLOCK_MANAGER_LOCKING */

/*----------------------------------------------------------------*/

/*
 * Block manager is currently implemented using dm-bufio.  काष्ठा
 * dm_block_manager and काष्ठा dm_block map directly onto a couple of
 * काष्ठाs in the bufio पूर्णांकerface.  I want to retain the मुक्तकरोm to move
 * away from bufio in the future.  So these काष्ठाs are just cast within
 * this .c file, rather than making it through to the खुला पूर्णांकerface.
 */
अटल काष्ठा dm_buffer *to_buffer(काष्ठा dm_block *b)
अणु
	वापस (काष्ठा dm_buffer *) b;
पूर्ण

dm_block_t dm_block_location(काष्ठा dm_block *b)
अणु
	वापस dm_bufio_get_block_number(to_buffer(b));
पूर्ण
EXPORT_SYMBOL_GPL(dm_block_location);

व्योम *dm_block_data(काष्ठा dm_block *b)
अणु
	वापस dm_bufio_get_block_data(to_buffer(b));
पूर्ण
EXPORT_SYMBOL_GPL(dm_block_data);

काष्ठा buffer_aux अणु
	काष्ठा dm_block_validator *validator;
	पूर्णांक ग_लिखो_locked;

#अगर_घोषित CONFIG_DM_DEBUG_BLOCK_MANAGER_LOCKING
	काष्ठा block_lock lock;
#पूर्ण_अगर
पूर्ण;

अटल व्योम dm_block_manager_alloc_callback(काष्ठा dm_buffer *buf)
अणु
	काष्ठा buffer_aux *aux = dm_bufio_get_aux_data(buf);
	aux->validator = शून्य;
	bl_init(&aux->lock);
पूर्ण

अटल व्योम dm_block_manager_ग_लिखो_callback(काष्ठा dm_buffer *buf)
अणु
	काष्ठा buffer_aux *aux = dm_bufio_get_aux_data(buf);
	अगर (aux->validator) अणु
		aux->validator->prepare_क्रम_ग_लिखो(aux->validator, (काष्ठा dm_block *) buf,
			 dm_bufio_get_block_size(dm_bufio_get_client(buf)));
	पूर्ण
पूर्ण

/*----------------------------------------------------------------
 * Public पूर्णांकerface
 *--------------------------------------------------------------*/
काष्ठा dm_block_manager अणु
	काष्ठा dm_bufio_client *bufio;
	bool पढ़ो_only:1;
पूर्ण;

काष्ठा dm_block_manager *dm_block_manager_create(काष्ठा block_device *bdev,
						 अचिन्हित block_size,
						 अचिन्हित max_held_per_thपढ़ो)
अणु
	पूर्णांक r;
	काष्ठा dm_block_manager *bm;

	bm = kदो_स्मृति(माप(*bm), GFP_KERNEL);
	अगर (!bm) अणु
		r = -ENOMEM;
		जाओ bad;
	पूर्ण

	bm->bufio = dm_bufio_client_create(bdev, block_size, max_held_per_thपढ़ो,
					   माप(काष्ठा buffer_aux),
					   dm_block_manager_alloc_callback,
					   dm_block_manager_ग_लिखो_callback);
	अगर (IS_ERR(bm->bufio)) अणु
		r = PTR_ERR(bm->bufio);
		kमुक्त(bm);
		जाओ bad;
	पूर्ण

	bm->पढ़ो_only = false;

	वापस bm;

bad:
	वापस ERR_PTR(r);
पूर्ण
EXPORT_SYMBOL_GPL(dm_block_manager_create);

व्योम dm_block_manager_destroy(काष्ठा dm_block_manager *bm)
अणु
	dm_bufio_client_destroy(bm->bufio);
	kमुक्त(bm);
पूर्ण
EXPORT_SYMBOL_GPL(dm_block_manager_destroy);

अचिन्हित dm_bm_block_size(काष्ठा dm_block_manager *bm)
अणु
	वापस dm_bufio_get_block_size(bm->bufio);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bm_block_size);

dm_block_t dm_bm_nr_blocks(काष्ठा dm_block_manager *bm)
अणु
	वापस dm_bufio_get_device_size(bm->bufio);
पूर्ण

अटल पूर्णांक dm_bm_validate_buffer(काष्ठा dm_block_manager *bm,
				 काष्ठा dm_buffer *buf,
				 काष्ठा buffer_aux *aux,
				 काष्ठा dm_block_validator *v)
अणु
	अगर (unlikely(!aux->validator)) अणु
		पूर्णांक r;
		अगर (!v)
			वापस 0;
		r = v->check(v, (काष्ठा dm_block *) buf, dm_bufio_get_block_size(bm->bufio));
		अगर (unlikely(r)) अणु
			DMERR_LIMIT("%s validator check failed for block %llu", v->name,
				    (अचिन्हित दीर्घ दीर्घ) dm_bufio_get_block_number(buf));
			वापस r;
		पूर्ण
		aux->validator = v;
	पूर्ण अन्यथा अणु
		अगर (unlikely(aux->validator != v)) अणु
			DMERR_LIMIT("validator mismatch (old=%s vs new=%s) for block %llu",
				    aux->validator->name, v ? v->name : "NULL",
				    (अचिन्हित दीर्घ दीर्घ) dm_bufio_get_block_number(buf));
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
पूर्णांक dm_bm_पढ़ो_lock(काष्ठा dm_block_manager *bm, dm_block_t b,
		    काष्ठा dm_block_validator *v,
		    काष्ठा dm_block **result)
अणु
	काष्ठा buffer_aux *aux;
	व्योम *p;
	पूर्णांक r;

	p = dm_bufio_पढ़ो(bm->bufio, b, (काष्ठा dm_buffer **) result);
	अगर (IS_ERR(p))
		वापस PTR_ERR(p);

	aux = dm_bufio_get_aux_data(to_buffer(*result));
	r = bl_करोwn_पढ़ो(&aux->lock);
	अगर (unlikely(r)) अणु
		dm_bufio_release(to_buffer(*result));
		report_recursive_bug(b, r);
		वापस r;
	पूर्ण

	aux->ग_लिखो_locked = 0;

	r = dm_bm_validate_buffer(bm, to_buffer(*result), aux, v);
	अगर (unlikely(r)) अणु
		bl_up_पढ़ो(&aux->lock);
		dm_bufio_release(to_buffer(*result));
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bm_पढ़ो_lock);

पूर्णांक dm_bm_ग_लिखो_lock(काष्ठा dm_block_manager *bm,
		     dm_block_t b, काष्ठा dm_block_validator *v,
		     काष्ठा dm_block **result)
अणु
	काष्ठा buffer_aux *aux;
	व्योम *p;
	पूर्णांक r;

	अगर (dm_bm_is_पढ़ो_only(bm))
		वापस -EPERM;

	p = dm_bufio_पढ़ो(bm->bufio, b, (काष्ठा dm_buffer **) result);
	अगर (IS_ERR(p))
		वापस PTR_ERR(p);

	aux = dm_bufio_get_aux_data(to_buffer(*result));
	r = bl_करोwn_ग_लिखो(&aux->lock);
	अगर (r) अणु
		dm_bufio_release(to_buffer(*result));
		report_recursive_bug(b, r);
		वापस r;
	पूर्ण

	aux->ग_लिखो_locked = 1;

	r = dm_bm_validate_buffer(bm, to_buffer(*result), aux, v);
	अगर (unlikely(r)) अणु
		bl_up_ग_लिखो(&aux->lock);
		dm_bufio_release(to_buffer(*result));
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bm_ग_लिखो_lock);

पूर्णांक dm_bm_पढ़ो_try_lock(काष्ठा dm_block_manager *bm,
			dm_block_t b, काष्ठा dm_block_validator *v,
			काष्ठा dm_block **result)
अणु
	काष्ठा buffer_aux *aux;
	व्योम *p;
	पूर्णांक r;

	p = dm_bufio_get(bm->bufio, b, (काष्ठा dm_buffer **) result);
	अगर (IS_ERR(p))
		वापस PTR_ERR(p);
	अगर (unlikely(!p))
		वापस -EWOULDBLOCK;

	aux = dm_bufio_get_aux_data(to_buffer(*result));
	r = bl_करोwn_पढ़ो_nonblock(&aux->lock);
	अगर (r < 0) अणु
		dm_bufio_release(to_buffer(*result));
		report_recursive_bug(b, r);
		वापस r;
	पूर्ण
	aux->ग_लिखो_locked = 0;

	r = dm_bm_validate_buffer(bm, to_buffer(*result), aux, v);
	अगर (unlikely(r)) अणु
		bl_up_पढ़ो(&aux->lock);
		dm_bufio_release(to_buffer(*result));
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dm_bm_ग_लिखो_lock_zero(काष्ठा dm_block_manager *bm,
			  dm_block_t b, काष्ठा dm_block_validator *v,
			  काष्ठा dm_block **result)
अणु
	पूर्णांक r;
	काष्ठा buffer_aux *aux;
	व्योम *p;

	अगर (dm_bm_is_पढ़ो_only(bm))
		वापस -EPERM;

	p = dm_bufio_new(bm->bufio, b, (काष्ठा dm_buffer **) result);
	अगर (IS_ERR(p))
		वापस PTR_ERR(p);

	स_रखो(p, 0, dm_bm_block_size(bm));

	aux = dm_bufio_get_aux_data(to_buffer(*result));
	r = bl_करोwn_ग_लिखो(&aux->lock);
	अगर (r) अणु
		dm_bufio_release(to_buffer(*result));
		वापस r;
	पूर्ण

	aux->ग_लिखो_locked = 1;
	aux->validator = v;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bm_ग_लिखो_lock_zero);

व्योम dm_bm_unlock(काष्ठा dm_block *b)
अणु
	काष्ठा buffer_aux *aux;
	aux = dm_bufio_get_aux_data(to_buffer(b));

	अगर (aux->ग_लिखो_locked) अणु
		dm_bufio_mark_buffer_dirty(to_buffer(b));
		bl_up_ग_लिखो(&aux->lock);
	पूर्ण अन्यथा
		bl_up_पढ़ो(&aux->lock);

	dm_bufio_release(to_buffer(b));
पूर्ण
EXPORT_SYMBOL_GPL(dm_bm_unlock);

पूर्णांक dm_bm_flush(काष्ठा dm_block_manager *bm)
अणु
	अगर (dm_bm_is_पढ़ो_only(bm))
		वापस -EPERM;

	वापस dm_bufio_ग_लिखो_dirty_buffers(bm->bufio);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bm_flush);

व्योम dm_bm_prefetch(काष्ठा dm_block_manager *bm, dm_block_t b)
अणु
	dm_bufio_prefetch(bm->bufio, b, 1);
पूर्ण

bool dm_bm_is_पढ़ो_only(काष्ठा dm_block_manager *bm)
अणु
	वापस (bm ? bm->पढ़ो_only : true);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bm_is_पढ़ो_only);

व्योम dm_bm_set_पढ़ो_only(काष्ठा dm_block_manager *bm)
अणु
	अगर (bm)
		bm->पढ़ो_only = true;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bm_set_पढ़ो_only);

व्योम dm_bm_set_पढ़ो_ग_लिखो(काष्ठा dm_block_manager *bm)
अणु
	अगर (bm)
		bm->पढ़ो_only = false;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bm_set_पढ़ो_ग_लिखो);

u32 dm_bm_checksum(स्थिर व्योम *data, माप_प्रकार len, u32 init_xor)
अणु
	वापस crc32c(~(u32) 0, data, len) ^ init_xor;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bm_checksum);

/*----------------------------------------------------------------*/

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joe Thornber <dm-devel@redhat.com>");
MODULE_DESCRIPTION("Immutable metadata library for dm");

/*----------------------------------------------------------------*/
