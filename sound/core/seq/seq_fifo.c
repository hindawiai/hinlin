<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA sequencer FIFO
 *   Copyright (c) 1998 by Frank van de Pol <fvdpol@coil.demon.nl>
 */

#समावेश <sound/core.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "seq_fifo.h"
#समावेश "seq_lock.h"


/* FIFO */

/* create new fअगरo */
काष्ठा snd_seq_fअगरo *snd_seq_fअगरo_new(पूर्णांक poolsize)
अणु
	काष्ठा snd_seq_fअगरo *f;

	f = kzalloc(माप(*f), GFP_KERNEL);
	अगर (!f)
		वापस शून्य;

	f->pool = snd_seq_pool_new(poolsize);
	अगर (f->pool == शून्य) अणु
		kमुक्त(f);
		वापस शून्य;
	पूर्ण
	अगर (snd_seq_pool_init(f->pool) < 0) अणु
		snd_seq_pool_delete(&f->pool);
		kमुक्त(f);
		वापस शून्य;
	पूर्ण

	spin_lock_init(&f->lock);
	snd_use_lock_init(&f->use_lock);
	init_रुकोqueue_head(&f->input_sleep);
	atomic_set(&f->overflow, 0);

	f->head = शून्य;
	f->tail = शून्य;
	f->cells = 0;
	
	वापस f;
पूर्ण

व्योम snd_seq_fअगरo_delete(काष्ठा snd_seq_fअगरo **fअगरo)
अणु
	काष्ठा snd_seq_fअगरo *f;

	अगर (snd_BUG_ON(!fअगरo))
		वापस;
	f = *fअगरo;
	अगर (snd_BUG_ON(!f))
		वापस;
	*fअगरo = शून्य;

	अगर (f->pool)
		snd_seq_pool_mark_closing(f->pool);

	snd_seq_fअगरo_clear(f);

	/* wake up clients अगर any */
	अगर (रुकोqueue_active(&f->input_sleep))
		wake_up(&f->input_sleep);

	/* release resources...*/
	/*....................*/

	अगर (f->pool) अणु
		snd_seq_pool_करोne(f->pool);
		snd_seq_pool_delete(&f->pool);
	पूर्ण
	
	kमुक्त(f);
पूर्ण

अटल काष्ठा snd_seq_event_cell *fअगरo_cell_out(काष्ठा snd_seq_fअगरo *f);

/* clear queue */
व्योम snd_seq_fअगरo_clear(काष्ठा snd_seq_fअगरo *f)
अणु
	काष्ठा snd_seq_event_cell *cell;

	/* clear overflow flag */
	atomic_set(&f->overflow, 0);

	snd_use_lock_sync(&f->use_lock);
	spin_lock_irq(&f->lock);
	/* drain the fअगरo */
	जबतक ((cell = fअगरo_cell_out(f)) != शून्य) अणु
		snd_seq_cell_मुक्त(cell);
	पूर्ण
	spin_unlock_irq(&f->lock);
पूर्ण


/* enqueue event to fअगरo */
पूर्णांक snd_seq_fअगरo_event_in(काष्ठा snd_seq_fअगरo *f,
			  काष्ठा snd_seq_event *event)
अणु
	काष्ठा snd_seq_event_cell *cell;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (snd_BUG_ON(!f))
		वापस -EINVAL;

	snd_use_lock_use(&f->use_lock);
	err = snd_seq_event_dup(f->pool, event, &cell, 1, शून्य, शून्य); /* always non-blocking */
	अगर (err < 0) अणु
		अगर ((err == -ENOMEM) || (err == -EAGAIN))
			atomic_inc(&f->overflow);
		snd_use_lock_मुक्त(&f->use_lock);
		वापस err;
	पूर्ण
		
	/* append new cells to fअगरo */
	spin_lock_irqsave(&f->lock, flags);
	अगर (f->tail != शून्य)
		f->tail->next = cell;
	f->tail = cell;
	अगर (f->head == शून्य)
		f->head = cell;
	cell->next = शून्य;
	f->cells++;
	spin_unlock_irqrestore(&f->lock, flags);

	/* wakeup client */
	अगर (रुकोqueue_active(&f->input_sleep))
		wake_up(&f->input_sleep);

	snd_use_lock_मुक्त(&f->use_lock);

	वापस 0; /* success */

पूर्ण

/* dequeue cell from fअगरo */
अटल काष्ठा snd_seq_event_cell *fअगरo_cell_out(काष्ठा snd_seq_fअगरo *f)
अणु
	काष्ठा snd_seq_event_cell *cell;

	अगर ((cell = f->head) != शून्य) अणु
		f->head = cell->next;

		/* reset tail अगर this was the last element */
		अगर (f->tail == cell)
			f->tail = शून्य;

		cell->next = शून्य;
		f->cells--;
	पूर्ण

	वापस cell;
पूर्ण

/* dequeue cell from fअगरo and copy on user space */
पूर्णांक snd_seq_fअगरo_cell_out(काष्ठा snd_seq_fअगरo *f,
			  काष्ठा snd_seq_event_cell **cellp, पूर्णांक nonblock)
अणु
	काष्ठा snd_seq_event_cell *cell;
	अचिन्हित दीर्घ flags;
	रुको_queue_entry_t रुको;

	अगर (snd_BUG_ON(!f))
		वापस -EINVAL;

	*cellp = शून्य;
	init_रुकोqueue_entry(&रुको, current);
	spin_lock_irqsave(&f->lock, flags);
	जबतक ((cell = fअगरo_cell_out(f)) == शून्य) अणु
		अगर (nonblock) अणु
			/* non-blocking - वापस immediately */
			spin_unlock_irqrestore(&f->lock, flags);
			वापस -EAGAIN;
		पूर्ण
		set_current_state(TASK_INTERRUPTIBLE);
		add_रुको_queue(&f->input_sleep, &रुको);
		spin_unlock_irqrestore(&f->lock, flags);
		schedule();
		spin_lock_irqsave(&f->lock, flags);
		हटाओ_रुको_queue(&f->input_sleep, &रुको);
		अगर (संकेत_pending(current)) अणु
			spin_unlock_irqrestore(&f->lock, flags);
			वापस -ERESTARTSYS;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&f->lock, flags);
	*cellp = cell;

	वापस 0;
पूर्ण


व्योम snd_seq_fअगरo_cell_putback(काष्ठा snd_seq_fअगरo *f,
			       काष्ठा snd_seq_event_cell *cell)
अणु
	अचिन्हित दीर्घ flags;

	अगर (cell) अणु
		spin_lock_irqsave(&f->lock, flags);
		cell->next = f->head;
		f->head = cell;
		अगर (!f->tail)
			f->tail = cell;
		f->cells++;
		spin_unlock_irqrestore(&f->lock, flags);
	पूर्ण
पूर्ण


/* polling; वापस non-zero अगर queue is available */
पूर्णांक snd_seq_fअगरo_poll_रुको(काष्ठा snd_seq_fअगरo *f, काष्ठा file *file,
			   poll_table *रुको)
अणु
	poll_रुको(file, &f->input_sleep, रुको);
	वापस (f->cells > 0);
पूर्ण

/* change the size of pool; all old events are हटाओd */
पूर्णांक snd_seq_fअगरo_resize(काष्ठा snd_seq_fअगरo *f, पूर्णांक poolsize)
अणु
	काष्ठा snd_seq_pool *newpool, *oldpool;
	काष्ठा snd_seq_event_cell *cell, *next, *oldhead;

	अगर (snd_BUG_ON(!f || !f->pool))
		वापस -EINVAL;

	/* allocate new pool */
	newpool = snd_seq_pool_new(poolsize);
	अगर (newpool == शून्य)
		वापस -ENOMEM;
	अगर (snd_seq_pool_init(newpool) < 0) अणु
		snd_seq_pool_delete(&newpool);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irq(&f->lock);
	/* remember old pool */
	oldpool = f->pool;
	oldhead = f->head;
	/* exchange pools */
	f->pool = newpool;
	f->head = शून्य;
	f->tail = शून्य;
	f->cells = 0;
	/* NOTE: overflow flag is not cleared */
	spin_unlock_irq(&f->lock);

	/* बंद the old pool and रुको until all users are gone */
	snd_seq_pool_mark_closing(oldpool);
	snd_use_lock_sync(&f->use_lock);

	/* release cells in old pool */
	क्रम (cell = oldhead; cell; cell = next) अणु
		next = cell->next;
		snd_seq_cell_मुक्त(cell);
	पूर्ण
	snd_seq_pool_delete(&oldpool);

	वापस 0;
पूर्ण

/* get the number of unused cells safely */
पूर्णांक snd_seq_fअगरo_unused_cells(काष्ठा snd_seq_fअगरo *f)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक cells;

	अगर (!f)
		वापस 0;

	snd_use_lock_use(&f->use_lock);
	spin_lock_irqsave(&f->lock, flags);
	cells = snd_seq_unused_cells(f->pool);
	spin_unlock_irqrestore(&f->lock, flags);
	snd_use_lock_मुक्त(&f->use_lock);
	वापस cells;
पूर्ण
