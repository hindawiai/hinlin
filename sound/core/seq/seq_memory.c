<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ALSA sequencer Memory Manager
 *  Copyright (c) 1998 by Frank van de Pol <fvdpol@coil.demon.nl>
 *                        Jaroslav Kysela <perex@perex.cz>
 *                2000 by Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/mm.h>
#समावेश <sound/core.h>

#समावेश <sound/seq_kernel.h>
#समावेश "seq_memory.h"
#समावेश "seq_queue.h"
#समावेश "seq_info.h"
#समावेश "seq_lock.h"

अटल अंतरभूत पूर्णांक snd_seq_pool_available(काष्ठा snd_seq_pool *pool)
अणु
	वापस pool->total_elements - atomic_पढ़ो(&pool->counter);
पूर्ण

अटल अंतरभूत पूर्णांक snd_seq_output_ok(काष्ठा snd_seq_pool *pool)
अणु
	वापस snd_seq_pool_available(pool) >= pool->room;
पूर्ण

/*
 * Variable length event:
 * The event like sysex uses variable length type.
 * The बाह्यal data may be stored in three dअगरferent क्रमmats.
 * 1) kernel space
 *    This is the normal हाल.
 *      ext.data.len = length
 *      ext.data.ptr = buffer poपूर्णांकer
 * 2) user space
 *    When an event is generated via पढ़ो(), the बाह्यal data is
 *    kept in user space until expanded.
 *      ext.data.len = length | SNDRV_SEQ_EXT_USRPTR
 *      ext.data.ptr = userspace poपूर्णांकer
 * 3) chained cells
 *    When the variable length event is enqueued (in prioq or fअगरo),
 *    the बाह्यal data is decomposed to several cells.
 *      ext.data.len = length | SNDRV_SEQ_EXT_CHAINED
 *      ext.data.ptr = the additiona cell head
 *         -> cell.next -> cell.next -> ..
 */

/*
 * exported:
 * call dump function to expand बाह्यal data.
 */

अटल पूर्णांक get_var_len(स्थिर काष्ठा snd_seq_event *event)
अणु
	अगर ((event->flags & SNDRV_SEQ_EVENT_LENGTH_MASK) != SNDRV_SEQ_EVENT_LENGTH_VARIABLE)
		वापस -EINVAL;

	वापस event->data.ext.len & ~SNDRV_SEQ_EXT_MASK;
पूर्ण

पूर्णांक snd_seq_dump_var_event(स्थिर काष्ठा snd_seq_event *event,
			   snd_seq_dump_func_t func, व्योम *निजी_data)
अणु
	पूर्णांक len, err;
	काष्ठा snd_seq_event_cell *cell;

	अगर ((len = get_var_len(event)) <= 0)
		वापस len;

	अगर (event->data.ext.len & SNDRV_SEQ_EXT_USRPTR) अणु
		अक्षर buf[32];
		अक्षर __user *curptr = (अक्षर __क्रमce __user *)event->data.ext.ptr;
		जबतक (len > 0) अणु
			पूर्णांक size = माप(buf);
			अगर (len < size)
				size = len;
			अगर (copy_from_user(buf, curptr, size))
				वापस -EFAULT;
			err = func(निजी_data, buf, size);
			अगर (err < 0)
				वापस err;
			curptr += size;
			len -= size;
		पूर्ण
		वापस 0;
	पूर्ण
	अगर (!(event->data.ext.len & SNDRV_SEQ_EXT_CHAINED))
		वापस func(निजी_data, event->data.ext.ptr, len);

	cell = (काष्ठा snd_seq_event_cell *)event->data.ext.ptr;
	क्रम (; len > 0 && cell; cell = cell->next) अणु
		पूर्णांक size = माप(काष्ठा snd_seq_event);
		अगर (len < size)
			size = len;
		err = func(निजी_data, &cell->event, size);
		अगर (err < 0)
			वापस err;
		len -= size;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_seq_dump_var_event);


/*
 * exported:
 * expand the variable length event to linear buffer space.
 */

अटल पूर्णांक seq_copy_in_kernel(अक्षर **bufptr, स्थिर व्योम *src, पूर्णांक size)
अणु
	स_नकल(*bufptr, src, size);
	*bufptr += size;
	वापस 0;
पूर्ण

अटल पूर्णांक seq_copy_in_user(अक्षर __user **bufptr, स्थिर व्योम *src, पूर्णांक size)
अणु
	अगर (copy_to_user(*bufptr, src, size))
		वापस -EFAULT;
	*bufptr += size;
	वापस 0;
पूर्ण

पूर्णांक snd_seq_expand_var_event(स्थिर काष्ठा snd_seq_event *event, पूर्णांक count, अक्षर *buf,
			     पूर्णांक in_kernel, पूर्णांक size_aligned)
अणु
	पूर्णांक len, newlen;
	पूर्णांक err;

	अगर ((len = get_var_len(event)) < 0)
		वापस len;
	newlen = len;
	अगर (size_aligned > 0)
		newlen = roundup(len, size_aligned);
	अगर (count < newlen)
		वापस -EAGAIN;

	अगर (event->data.ext.len & SNDRV_SEQ_EXT_USRPTR) अणु
		अगर (! in_kernel)
			वापस -EINVAL;
		अगर (copy_from_user(buf, (व्योम __क्रमce __user *)event->data.ext.ptr, len))
			वापस -EFAULT;
		वापस newlen;
	पूर्ण
	err = snd_seq_dump_var_event(event,
				     in_kernel ? (snd_seq_dump_func_t)seq_copy_in_kernel :
				     (snd_seq_dump_func_t)seq_copy_in_user,
				     &buf);
	वापस err < 0 ? err : newlen;
पूर्ण
EXPORT_SYMBOL(snd_seq_expand_var_event);

/*
 * release this cell, मुक्त extended data अगर available
 */

अटल अंतरभूत व्योम मुक्त_cell(काष्ठा snd_seq_pool *pool,
			     काष्ठा snd_seq_event_cell *cell)
अणु
	cell->next = pool->मुक्त;
	pool->मुक्त = cell;
	atomic_dec(&pool->counter);
पूर्ण

व्योम snd_seq_cell_मुक्त(काष्ठा snd_seq_event_cell * cell)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_seq_pool *pool;

	अगर (snd_BUG_ON(!cell))
		वापस;
	pool = cell->pool;
	अगर (snd_BUG_ON(!pool))
		वापस;

	spin_lock_irqsave(&pool->lock, flags);
	मुक्त_cell(pool, cell);
	अगर (snd_seq_ev_is_variable(&cell->event)) अणु
		अगर (cell->event.data.ext.len & SNDRV_SEQ_EXT_CHAINED) अणु
			काष्ठा snd_seq_event_cell *curp, *nextptr;
			curp = cell->event.data.ext.ptr;
			क्रम (; curp; curp = nextptr) अणु
				nextptr = curp->next;
				curp->next = pool->मुक्त;
				मुक्त_cell(pool, curp);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (रुकोqueue_active(&pool->output_sleep)) अणु
		/* has enough space now? */
		अगर (snd_seq_output_ok(pool))
			wake_up(&pool->output_sleep);
	पूर्ण
	spin_unlock_irqrestore(&pool->lock, flags);
पूर्ण


/*
 * allocate an event cell.
 */
अटल पूर्णांक snd_seq_cell_alloc(काष्ठा snd_seq_pool *pool,
			      काष्ठा snd_seq_event_cell **cellp,
			      पूर्णांक nonblock, काष्ठा file *file,
			      काष्ठा mutex *mutexp)
अणु
	काष्ठा snd_seq_event_cell *cell;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = -EAGAIN;
	रुको_queue_entry_t रुको;

	अगर (pool == शून्य)
		वापस -EINVAL;

	*cellp = शून्य;

	init_रुकोqueue_entry(&रुको, current);
	spin_lock_irqsave(&pool->lock, flags);
	अगर (pool->ptr == शून्य) अणु	/* not initialized */
		pr_debug("ALSA: seq: pool is not initialized\n");
		err = -EINVAL;
		जाओ __error;
	पूर्ण
	जबतक (pool->मुक्त == शून्य && ! nonblock && ! pool->closing) अणु

		set_current_state(TASK_INTERRUPTIBLE);
		add_रुको_queue(&pool->output_sleep, &रुको);
		spin_unlock_irqrestore(&pool->lock, flags);
		अगर (mutexp)
			mutex_unlock(mutexp);
		schedule();
		अगर (mutexp)
			mutex_lock(mutexp);
		spin_lock_irqsave(&pool->lock, flags);
		हटाओ_रुको_queue(&pool->output_sleep, &रुको);
		/* पूर्णांकerrupted? */
		अगर (संकेत_pending(current)) अणु
			err = -ERESTARTSYS;
			जाओ __error;
		पूर्ण
	पूर्ण
	अगर (pool->closing) अणु /* closing.. */
		err = -ENOMEM;
		जाओ __error;
	पूर्ण

	cell = pool->मुक्त;
	अगर (cell) अणु
		पूर्णांक used;
		pool->मुक्त = cell->next;
		atomic_inc(&pool->counter);
		used = atomic_पढ़ो(&pool->counter);
		अगर (pool->max_used < used)
			pool->max_used = used;
		pool->event_alloc_success++;
		/* clear cell poपूर्णांकers */
		cell->next = शून्य;
		err = 0;
	पूर्ण अन्यथा
		pool->event_alloc_failures++;
	*cellp = cell;

__error:
	spin_unlock_irqrestore(&pool->lock, flags);
	वापस err;
पूर्ण


/*
 * duplicate the event to a cell.
 * अगर the event has बाह्यal data, the data is decomposed to additional
 * cells.
 */
पूर्णांक snd_seq_event_dup(काष्ठा snd_seq_pool *pool, काष्ठा snd_seq_event *event,
		      काष्ठा snd_seq_event_cell **cellp, पूर्णांक nonblock,
		      काष्ठा file *file, काष्ठा mutex *mutexp)
अणु
	पूर्णांक ncells, err;
	अचिन्हित पूर्णांक extlen;
	काष्ठा snd_seq_event_cell *cell;

	*cellp = शून्य;

	ncells = 0;
	extlen = 0;
	अगर (snd_seq_ev_is_variable(event)) अणु
		extlen = event->data.ext.len & ~SNDRV_SEQ_EXT_MASK;
		ncells = DIV_ROUND_UP(extlen, माप(काष्ठा snd_seq_event));
	पूर्ण
	अगर (ncells >= pool->total_elements)
		वापस -ENOMEM;

	err = snd_seq_cell_alloc(pool, &cell, nonblock, file, mutexp);
	अगर (err < 0)
		वापस err;

	/* copy the event */
	cell->event = *event;

	/* decompose */
	अगर (snd_seq_ev_is_variable(event)) अणु
		पूर्णांक len = extlen;
		पूर्णांक is_chained = event->data.ext.len & SNDRV_SEQ_EXT_CHAINED;
		पूर्णांक is_usrptr = event->data.ext.len & SNDRV_SEQ_EXT_USRPTR;
		काष्ठा snd_seq_event_cell *src, *पंचांगp, *tail;
		अक्षर *buf;

		cell->event.data.ext.len = extlen | SNDRV_SEQ_EXT_CHAINED;
		cell->event.data.ext.ptr = शून्य;

		src = (काष्ठा snd_seq_event_cell *)event->data.ext.ptr;
		buf = (अक्षर *)event->data.ext.ptr;
		tail = शून्य;

		जबतक (ncells-- > 0) अणु
			पूर्णांक size = माप(काष्ठा snd_seq_event);
			अगर (len < size)
				size = len;
			err = snd_seq_cell_alloc(pool, &पंचांगp, nonblock, file,
						 mutexp);
			अगर (err < 0)
				जाओ __error;
			अगर (cell->event.data.ext.ptr == शून्य)
				cell->event.data.ext.ptr = पंचांगp;
			अगर (tail)
				tail->next = पंचांगp;
			tail = पंचांगp;
			/* copy chunk */
			अगर (is_chained && src) अणु
				पंचांगp->event = src->event;
				src = src->next;
			पूर्ण अन्यथा अगर (is_usrptr) अणु
				अगर (copy_from_user(&पंचांगp->event, (अक्षर __क्रमce __user *)buf, size)) अणु
					err = -EFAULT;
					जाओ __error;
				पूर्ण
			पूर्ण अन्यथा अणु
				स_नकल(&पंचांगp->event, buf, size);
			पूर्ण
			buf += size;
			len -= size;
		पूर्ण
	पूर्ण

	*cellp = cell;
	वापस 0;

__error:
	snd_seq_cell_मुक्त(cell);
	वापस err;
पूर्ण
  

/* poll रुको */
पूर्णांक snd_seq_pool_poll_रुको(काष्ठा snd_seq_pool *pool, काष्ठा file *file,
			   poll_table *रुको)
अणु
	poll_रुको(file, &pool->output_sleep, रुको);
	वापस snd_seq_output_ok(pool);
पूर्ण


/* allocate room specअगरied number of events */
पूर्णांक snd_seq_pool_init(काष्ठा snd_seq_pool *pool)
अणु
	पूर्णांक cell;
	काष्ठा snd_seq_event_cell *cellptr;

	अगर (snd_BUG_ON(!pool))
		वापस -EINVAL;

	cellptr = kvदो_स्मृति_array(माप(काष्ठा snd_seq_event_cell), pool->size,
				 GFP_KERNEL);
	अगर (!cellptr)
		वापस -ENOMEM;

	/* add new cells to the मुक्त cell list */
	spin_lock_irq(&pool->lock);
	अगर (pool->ptr) अणु
		spin_unlock_irq(&pool->lock);
		kvमुक्त(cellptr);
		वापस 0;
	पूर्ण

	pool->ptr = cellptr;
	pool->मुक्त = शून्य;

	क्रम (cell = 0; cell < pool->size; cell++) अणु
		cellptr = pool->ptr + cell;
		cellptr->pool = pool;
		cellptr->next = pool->मुक्त;
		pool->मुक्त = cellptr;
	पूर्ण
	pool->room = (pool->size + 1) / 2;

	/* init statistics */
	pool->max_used = 0;
	pool->total_elements = pool->size;
	spin_unlock_irq(&pool->lock);
	वापस 0;
पूर्ण

/* refuse the further insertion to the pool */
व्योम snd_seq_pool_mark_closing(काष्ठा snd_seq_pool *pool)
अणु
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!pool))
		वापस;
	spin_lock_irqsave(&pool->lock, flags);
	pool->closing = 1;
	spin_unlock_irqrestore(&pool->lock, flags);
पूर्ण

/* हटाओ events */
पूर्णांक snd_seq_pool_करोne(काष्ठा snd_seq_pool *pool)
अणु
	काष्ठा snd_seq_event_cell *ptr;

	अगर (snd_BUG_ON(!pool))
		वापस -EINVAL;

	/* रुको क्रम closing all thपढ़ोs */
	अगर (रुकोqueue_active(&pool->output_sleep))
		wake_up(&pool->output_sleep);

	जबतक (atomic_पढ़ो(&pool->counter) > 0)
		schedule_समयout_unपूर्णांकerruptible(1);
	
	/* release all resources */
	spin_lock_irq(&pool->lock);
	ptr = pool->ptr;
	pool->ptr = शून्य;
	pool->मुक्त = शून्य;
	pool->total_elements = 0;
	spin_unlock_irq(&pool->lock);

	kvमुक्त(ptr);

	spin_lock_irq(&pool->lock);
	pool->closing = 0;
	spin_unlock_irq(&pool->lock);

	वापस 0;
पूर्ण


/* init new memory pool */
काष्ठा snd_seq_pool *snd_seq_pool_new(पूर्णांक poolsize)
अणु
	काष्ठा snd_seq_pool *pool;

	/* create pool block */
	pool = kzalloc(माप(*pool), GFP_KERNEL);
	अगर (!pool)
		वापस शून्य;
	spin_lock_init(&pool->lock);
	pool->ptr = शून्य;
	pool->मुक्त = शून्य;
	pool->total_elements = 0;
	atomic_set(&pool->counter, 0);
	pool->closing = 0;
	init_रुकोqueue_head(&pool->output_sleep);
	
	pool->size = poolsize;

	/* init statistics */
	pool->max_used = 0;
	वापस pool;
पूर्ण

/* हटाओ memory pool */
पूर्णांक snd_seq_pool_delete(काष्ठा snd_seq_pool **ppool)
अणु
	काष्ठा snd_seq_pool *pool = *ppool;

	*ppool = शून्य;
	अगर (pool == शून्य)
		वापस 0;
	snd_seq_pool_mark_closing(pool);
	snd_seq_pool_करोne(pool);
	kमुक्त(pool);
	वापस 0;
पूर्ण

/* exported to seq_clienपंचांगgr.c */
व्योम snd_seq_info_pool(काष्ठा snd_info_buffer *buffer,
		       काष्ठा snd_seq_pool *pool, अक्षर *space)
अणु
	अगर (pool == शून्य)
		वापस;
	snd_iम_लिखो(buffer, "%sPool size          : %d\n", space, pool->total_elements);
	snd_iम_लिखो(buffer, "%sCells in use       : %d\n", space, atomic_पढ़ो(&pool->counter));
	snd_iम_लिखो(buffer, "%sPeak cells in use  : %d\n", space, pool->max_used);
	snd_iम_लिखो(buffer, "%sAlloc success      : %d\n", space, pool->event_alloc_success);
	snd_iम_लिखो(buffer, "%sAlloc failures     : %d\n", space, pool->event_alloc_failures);
पूर्ण
