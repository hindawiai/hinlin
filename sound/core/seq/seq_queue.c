<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA sequencer Timing queue handling
 *   Copyright (c) 1998-1999 by Frank van de Pol <fvdpol@coil.demon.nl>
 *
 * MAJOR CHANGES
 *   Nov. 13, 1999	Takashi Iwai <iwai@ww.uni-erlangen.de>
 *     - Queues are allocated dynamically via ioctl.
 *     - When owner client is deleted, all owned queues are deleted, too.
 *     - Owner of unlocked queue is kept unmodअगरied even अगर it is
 *	 manipulated by other clients.
 *     - Owner field in SET_QUEUE_OWNER ioctl must be identical with the
 *       caller client.  i.e. Changing owner to a third client is not
 *       allowed.
 *
 *  Aug. 30, 2000	Takashi Iwai
 *     - Queues are managed in अटल array again, but with better way.
 *       The API itself is identical.
 *     - The queue is locked when काष्ठा snd_seq_queue poपूर्णांकer is वापसed via
 *       queueptr().  This poपूर्णांकer *MUST* be released afterward by
 *       queueमुक्त(ptr).
 *     - Addition of experimental sync support.
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>

#समावेश "seq_memory.h"
#समावेश "seq_queue.h"
#समावेश "seq_clientmgr.h"
#समावेश "seq_fifo.h"
#समावेश "seq_timer.h"
#समावेश "seq_info.h"

/* list of allocated queues */
अटल काष्ठा snd_seq_queue *queue_list[SNDRV_SEQ_MAX_QUEUES];
अटल DEFINE_SPINLOCK(queue_list_lock);
/* number of queues allocated */
अटल पूर्णांक num_queues;

पूर्णांक snd_seq_queue_get_cur_queues(व्योम)
अणु
	वापस num_queues;
पूर्ण

/*----------------------------------------------------------------*/

/* assign queue id and insert to list */
अटल पूर्णांक queue_list_add(काष्ठा snd_seq_queue *q)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue_list_lock, flags);
	क्रम (i = 0; i < SNDRV_SEQ_MAX_QUEUES; i++) अणु
		अगर (! queue_list[i]) अणु
			queue_list[i] = q;
			q->queue = i;
			num_queues++;
			spin_unlock_irqrestore(&queue_list_lock, flags);
			वापस i;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&queue_list_lock, flags);
	वापस -1;
पूर्ण

अटल काष्ठा snd_seq_queue *queue_list_हटाओ(पूर्णांक id, पूर्णांक client)
अणु
	काष्ठा snd_seq_queue *q;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue_list_lock, flags);
	q = queue_list[id];
	अगर (q) अणु
		spin_lock(&q->owner_lock);
		अगर (q->owner == client) अणु
			/* found */
			q->klocked = 1;
			spin_unlock(&q->owner_lock);
			queue_list[id] = शून्य;
			num_queues--;
			spin_unlock_irqrestore(&queue_list_lock, flags);
			वापस q;
		पूर्ण
		spin_unlock(&q->owner_lock);
	पूर्ण
	spin_unlock_irqrestore(&queue_list_lock, flags);
	वापस शून्य;
पूर्ण

/*----------------------------------------------------------------*/

/* create new queue (स्थिरructor) */
अटल काष्ठा snd_seq_queue *queue_new(पूर्णांक owner, पूर्णांक locked)
अणु
	काष्ठा snd_seq_queue *q;

	q = kzalloc(माप(*q), GFP_KERNEL);
	अगर (!q)
		वापस शून्य;

	spin_lock_init(&q->owner_lock);
	spin_lock_init(&q->check_lock);
	mutex_init(&q->समयr_mutex);
	snd_use_lock_init(&q->use_lock);
	q->queue = -1;

	q->tickq = snd_seq_prioq_new();
	q->समयq = snd_seq_prioq_new();
	q->समयr = snd_seq_समयr_new();
	अगर (q->tickq == शून्य || q->समयq == शून्य || q->समयr == शून्य) अणु
		snd_seq_prioq_delete(&q->tickq);
		snd_seq_prioq_delete(&q->समयq);
		snd_seq_समयr_delete(&q->समयr);
		kमुक्त(q);
		वापस शून्य;
	पूर्ण

	q->owner = owner;
	q->locked = locked;
	q->klocked = 0;

	वापस q;
पूर्ण

/* delete queue (deकाष्ठाor) */
अटल व्योम queue_delete(काष्ठा snd_seq_queue *q)
अणु
	/* stop and release the समयr */
	mutex_lock(&q->समयr_mutex);
	snd_seq_समयr_stop(q->समयr);
	snd_seq_समयr_बंद(q);
	mutex_unlock(&q->समयr_mutex);
	/* रुको until access मुक्त */
	snd_use_lock_sync(&q->use_lock);
	/* release resources... */
	snd_seq_prioq_delete(&q->tickq);
	snd_seq_prioq_delete(&q->समयq);
	snd_seq_समयr_delete(&q->समयr);

	kमुक्त(q);
पूर्ण


/*----------------------------------------------------------------*/

/* delete all existing queues */
व्योम snd_seq_queues_delete(व्योम)
अणु
	पूर्णांक i;

	/* clear list */
	क्रम (i = 0; i < SNDRV_SEQ_MAX_QUEUES; i++) अणु
		अगर (queue_list[i])
			queue_delete(queue_list[i]);
	पूर्ण
पूर्ण

अटल व्योम queue_use(काष्ठा snd_seq_queue *queue, पूर्णांक client, पूर्णांक use);

/* allocate a new queue -
 * वापस poपूर्णांकer to new queue or ERR_PTR(-त्रुटि_सं) क्रम error
 * The new queue's use_lock is set to 1. It is the caller's responsibility to
 * call snd_use_lock_मुक्त(&q->use_lock).
 */
काष्ठा snd_seq_queue *snd_seq_queue_alloc(पूर्णांक client, पूर्णांक locked, अचिन्हित पूर्णांक info_flags)
अणु
	काष्ठा snd_seq_queue *q;

	q = queue_new(client, locked);
	अगर (q == शून्य)
		वापस ERR_PTR(-ENOMEM);
	q->info_flags = info_flags;
	queue_use(q, client, 1);
	snd_use_lock_use(&q->use_lock);
	अगर (queue_list_add(q) < 0) अणु
		snd_use_lock_मुक्त(&q->use_lock);
		queue_delete(q);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	वापस q;
पूर्ण

/* delete a queue - queue must be owned by the client */
पूर्णांक snd_seq_queue_delete(पूर्णांक client, पूर्णांक queueid)
अणु
	काष्ठा snd_seq_queue *q;

	अगर (queueid < 0 || queueid >= SNDRV_SEQ_MAX_QUEUES)
		वापस -EINVAL;
	q = queue_list_हटाओ(queueid, client);
	अगर (q == शून्य)
		वापस -EINVAL;
	queue_delete(q);

	वापस 0;
पूर्ण


/* वापस poपूर्णांकer to queue काष्ठाure क्रम specअगरied id */
काष्ठा snd_seq_queue *queueptr(पूर्णांक queueid)
अणु
	काष्ठा snd_seq_queue *q;
	अचिन्हित दीर्घ flags;

	अगर (queueid < 0 || queueid >= SNDRV_SEQ_MAX_QUEUES)
		वापस शून्य;
	spin_lock_irqsave(&queue_list_lock, flags);
	q = queue_list[queueid];
	अगर (q)
		snd_use_lock_use(&q->use_lock);
	spin_unlock_irqrestore(&queue_list_lock, flags);
	वापस q;
पूर्ण

/* वापस the (first) queue matching with the specअगरied name */
काष्ठा snd_seq_queue *snd_seq_queue_find_name(अक्षर *name)
अणु
	पूर्णांक i;
	काष्ठा snd_seq_queue *q;

	क्रम (i = 0; i < SNDRV_SEQ_MAX_QUEUES; i++) अणु
		अगर ((q = queueptr(i)) != शून्य) अणु
			अगर (म_भेदन(q->name, name, माप(q->name)) == 0)
				वापस q;
			queueमुक्त(q);
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण


/* -------------------------------------------------------- */

व्योम snd_seq_check_queue(काष्ठा snd_seq_queue *q, पूर्णांक atomic, पूर्णांक hop)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_seq_event_cell *cell;
	snd_seq_tick_समय_प्रकार cur_tick;
	snd_seq_real_समय_प्रकार cur_समय;

	अगर (q == शून्य)
		वापस;

	/* make this function non-reentrant */
	spin_lock_irqsave(&q->check_lock, flags);
	अगर (q->check_blocked) अणु
		q->check_again = 1;
		spin_unlock_irqrestore(&q->check_lock, flags);
		वापस;		/* other thपढ़ो is alपढ़ोy checking queues */
	पूर्ण
	q->check_blocked = 1;
	spin_unlock_irqrestore(&q->check_lock, flags);

      __again:
	/* Process tick queue... */
	cur_tick = snd_seq_समयr_get_cur_tick(q->समयr);
	क्रम (;;) अणु
		cell = snd_seq_prioq_cell_out(q->tickq, &cur_tick);
		अगर (!cell)
			अवरोध;
		snd_seq_dispatch_event(cell, atomic, hop);
	पूर्ण

	/* Process समय queue... */
	cur_समय = snd_seq_समयr_get_cur_समय(q->समयr, false);
	क्रम (;;) अणु
		cell = snd_seq_prioq_cell_out(q->समयq, &cur_समय);
		अगर (!cell)
			अवरोध;
		snd_seq_dispatch_event(cell, atomic, hop);
	पूर्ण

	/* मुक्त lock */
	spin_lock_irqsave(&q->check_lock, flags);
	अगर (q->check_again) अणु
		q->check_again = 0;
		spin_unlock_irqrestore(&q->check_lock, flags);
		जाओ __again;
	पूर्ण
	q->check_blocked = 0;
	spin_unlock_irqrestore(&q->check_lock, flags);
पूर्ण


/* enqueue a event to singe queue */
पूर्णांक snd_seq_enqueue_event(काष्ठा snd_seq_event_cell *cell, पूर्णांक atomic, पूर्णांक hop)
अणु
	पूर्णांक dest, err;
	काष्ठा snd_seq_queue *q;

	अगर (snd_BUG_ON(!cell))
		वापस -EINVAL;
	dest = cell->event.queue;	/* destination queue */
	q = queueptr(dest);
	अगर (q == शून्य)
		वापस -EINVAL;
	/* handle relative समय stamps, convert them पूर्णांकo असलolute */
	अगर ((cell->event.flags & SNDRV_SEQ_TIME_MODE_MASK) == SNDRV_SEQ_TIME_MODE_REL) अणु
		चयन (cell->event.flags & SNDRV_SEQ_TIME_STAMP_MASK) अणु
		हाल SNDRV_SEQ_TIME_STAMP_TICK:
			cell->event.समय.tick += q->समयr->tick.cur_tick;
			अवरोध;

		हाल SNDRV_SEQ_TIME_STAMP_REAL:
			snd_seq_inc_real_समय(&cell->event.समय.समय,
					      &q->समयr->cur_समय);
			अवरोध;
		पूर्ण
		cell->event.flags &= ~SNDRV_SEQ_TIME_MODE_MASK;
		cell->event.flags |= SNDRV_SEQ_TIME_MODE_ABS;
	पूर्ण
	/* enqueue event in the real-समय or midi queue */
	चयन (cell->event.flags & SNDRV_SEQ_TIME_STAMP_MASK) अणु
	हाल SNDRV_SEQ_TIME_STAMP_TICK:
		err = snd_seq_prioq_cell_in(q->tickq, cell);
		अवरोध;

	हाल SNDRV_SEQ_TIME_STAMP_REAL:
	शेष:
		err = snd_seq_prioq_cell_in(q->समयq, cell);
		अवरोध;
	पूर्ण

	अगर (err < 0) अणु
		queueमुक्त(q); /* unlock */
		वापस err;
	पूर्ण

	/* trigger dispatching */
	snd_seq_check_queue(q, atomic, hop);

	queueमुक्त(q); /* unlock */

	वापस 0;
पूर्ण


/*----------------------------------------------------------------*/

अटल अंतरभूत पूर्णांक check_access(काष्ठा snd_seq_queue *q, पूर्णांक client)
अणु
	वापस (q->owner == client) || (!q->locked && !q->klocked);
पूर्ण

/* check अगर the client has permission to modअगरy queue parameters.
 * अगर it करोes, lock the queue
 */
अटल पूर्णांक queue_access_lock(काष्ठा snd_seq_queue *q, पूर्णांक client)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक access_ok;
	
	spin_lock_irqsave(&q->owner_lock, flags);
	access_ok = check_access(q, client);
	अगर (access_ok)
		q->klocked = 1;
	spin_unlock_irqrestore(&q->owner_lock, flags);
	वापस access_ok;
पूर्ण

/* unlock the queue */
अटल अंतरभूत व्योम queue_access_unlock(काष्ठा snd_seq_queue *q)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q->owner_lock, flags);
	q->klocked = 0;
	spin_unlock_irqrestore(&q->owner_lock, flags);
पूर्ण

/* exported - only checking permission */
पूर्णांक snd_seq_queue_check_access(पूर्णांक queueid, पूर्णांक client)
अणु
	काष्ठा snd_seq_queue *q = queueptr(queueid);
	पूर्णांक access_ok;
	अचिन्हित दीर्घ flags;

	अगर (! q)
		वापस 0;
	spin_lock_irqsave(&q->owner_lock, flags);
	access_ok = check_access(q, client);
	spin_unlock_irqrestore(&q->owner_lock, flags);
	queueमुक्त(q);
	वापस access_ok;
पूर्ण

/*----------------------------------------------------------------*/

/*
 * change queue's owner and permission
 */
पूर्णांक snd_seq_queue_set_owner(पूर्णांक queueid, पूर्णांक client, पूर्णांक locked)
अणु
	काष्ठा snd_seq_queue *q = queueptr(queueid);
	अचिन्हित दीर्घ flags;

	अगर (q == शून्य)
		वापस -EINVAL;

	अगर (! queue_access_lock(q, client)) अणु
		queueमुक्त(q);
		वापस -EPERM;
	पूर्ण

	spin_lock_irqsave(&q->owner_lock, flags);
	q->locked = locked ? 1 : 0;
	q->owner = client;
	spin_unlock_irqrestore(&q->owner_lock, flags);
	queue_access_unlock(q);
	queueमुक्त(q);

	वापस 0;
पूर्ण


/*----------------------------------------------------------------*/

/* खोलो समयr -
 * q->use mutex should be करोwn beक्रमe calling this function to aव्योम
 * confliction with snd_seq_queue_use()
 */
पूर्णांक snd_seq_queue_समयr_खोलो(पूर्णांक queueid)
अणु
	पूर्णांक result = 0;
	काष्ठा snd_seq_queue *queue;
	काष्ठा snd_seq_समयr *पंचांगr;

	queue = queueptr(queueid);
	अगर (queue == शून्य)
		वापस -EINVAL;
	पंचांगr = queue->समयr;
	अगर ((result = snd_seq_समयr_खोलो(queue)) < 0) अणु
		snd_seq_समयr_शेषs(पंचांगr);
		result = snd_seq_समयr_खोलो(queue);
	पूर्ण
	queueमुक्त(queue);
	वापस result;
पूर्ण

/* बंद समयr -
 * q->use mutex should be करोwn beक्रमe calling this function
 */
पूर्णांक snd_seq_queue_समयr_बंद(पूर्णांक queueid)
अणु
	काष्ठा snd_seq_queue *queue;
	पूर्णांक result = 0;

	queue = queueptr(queueid);
	अगर (queue == शून्य)
		वापस -EINVAL;
	snd_seq_समयr_बंद(queue);
	queueमुक्त(queue);
	वापस result;
पूर्ण

/* change queue tempo and ppq */
पूर्णांक snd_seq_queue_समयr_set_tempo(पूर्णांक queueid, पूर्णांक client,
				  काष्ठा snd_seq_queue_tempo *info)
अणु
	काष्ठा snd_seq_queue *q = queueptr(queueid);
	पूर्णांक result;

	अगर (q == शून्य)
		वापस -EINVAL;
	अगर (! queue_access_lock(q, client)) अणु
		queueमुक्त(q);
		वापस -EPERM;
	पूर्ण

	result = snd_seq_समयr_set_tempo_ppq(q->समयr, info->tempo, info->ppq);
	अगर (result >= 0 && info->skew_base > 0)
		result = snd_seq_समयr_set_skew(q->समयr, info->skew_value,
						info->skew_base);
	queue_access_unlock(q);
	queueमुक्त(q);
	वापस result;
पूर्ण

/* use or unuse this queue */
अटल व्योम queue_use(काष्ठा snd_seq_queue *queue, पूर्णांक client, पूर्णांक use)
अणु
	अगर (use) अणु
		अगर (!test_and_set_bit(client, queue->clients_biपंचांगap))
			queue->clients++;
	पूर्ण अन्यथा अणु
		अगर (test_and_clear_bit(client, queue->clients_biपंचांगap))
			queue->clients--;
	पूर्ण
	अगर (queue->clients) अणु
		अगर (use && queue->clients == 1)
			snd_seq_समयr_शेषs(queue->समयr);
		snd_seq_समयr_खोलो(queue);
	पूर्ण अन्यथा अणु
		snd_seq_समयr_बंद(queue);
	पूर्ण
पूर्ण

/* use or unuse this queue -
 * अगर it is the first client, starts the समयr.
 * अगर it is not दीर्घer used by any clients, stop the समयr.
 */
पूर्णांक snd_seq_queue_use(पूर्णांक queueid, पूर्णांक client, पूर्णांक use)
अणु
	काष्ठा snd_seq_queue *queue;

	queue = queueptr(queueid);
	अगर (queue == शून्य)
		वापस -EINVAL;
	mutex_lock(&queue->समयr_mutex);
	queue_use(queue, client, use);
	mutex_unlock(&queue->समयr_mutex);
	queueमुक्त(queue);
	वापस 0;
पूर्ण

/*
 * check अगर queue is used by the client
 * वापस negative value अगर the queue is invalid.
 * वापस 0 अगर not used, 1 अगर used.
 */
पूर्णांक snd_seq_queue_is_used(पूर्णांक queueid, पूर्णांक client)
अणु
	काष्ठा snd_seq_queue *q;
	पूर्णांक result;

	q = queueptr(queueid);
	अगर (q == शून्य)
		वापस -EINVAL; /* invalid queue */
	result = test_bit(client, q->clients_biपंचांगap) ? 1 : 0;
	queueमुक्त(q);
	वापस result;
पूर्ण


/*----------------------------------------------------------------*/

/* final stage notअगरication -
 * हटाओ cells क्रम no दीर्घer exist client (क्रम non-owned queue)
 * or delete this queue (क्रम owned queue)
 */
व्योम snd_seq_queue_client_leave(पूर्णांक client)
अणु
	पूर्णांक i;
	काष्ठा snd_seq_queue *q;

	/* delete own queues from queue list */
	क्रम (i = 0; i < SNDRV_SEQ_MAX_QUEUES; i++) अणु
		अगर ((q = queue_list_हटाओ(i, client)) != शून्य)
			queue_delete(q);
	पूर्ण

	/* हटाओ cells from existing queues -
	 * they are not owned by this client
	 */
	क्रम (i = 0; i < SNDRV_SEQ_MAX_QUEUES; i++) अणु
		अगर ((q = queueptr(i)) == शून्य)
			जारी;
		अगर (test_bit(client, q->clients_biपंचांगap)) अणु
			snd_seq_prioq_leave(q->tickq, client, 0);
			snd_seq_prioq_leave(q->समयq, client, 0);
			snd_seq_queue_use(q->queue, client, 0);
		पूर्ण
		queueमुक्त(q);
	पूर्ण
पूर्ण



/*----------------------------------------------------------------*/

/* हटाओ cells from all queues */
व्योम snd_seq_queue_client_leave_cells(पूर्णांक client)
अणु
	पूर्णांक i;
	काष्ठा snd_seq_queue *q;

	क्रम (i = 0; i < SNDRV_SEQ_MAX_QUEUES; i++) अणु
		अगर ((q = queueptr(i)) == शून्य)
			जारी;
		snd_seq_prioq_leave(q->tickq, client, 0);
		snd_seq_prioq_leave(q->समयq, client, 0);
		queueमुक्त(q);
	पूर्ण
पूर्ण

/* हटाओ cells based on flush criteria */
व्योम snd_seq_queue_हटाओ_cells(पूर्णांक client, काष्ठा snd_seq_हटाओ_events *info)
अणु
	पूर्णांक i;
	काष्ठा snd_seq_queue *q;

	क्रम (i = 0; i < SNDRV_SEQ_MAX_QUEUES; i++) अणु
		अगर ((q = queueptr(i)) == शून्य)
			जारी;
		अगर (test_bit(client, q->clients_biपंचांगap) &&
		    (! (info->हटाओ_mode & SNDRV_SEQ_REMOVE_DEST) ||
		     q->queue == info->queue)) अणु
			snd_seq_prioq_हटाओ_events(q->tickq, client, info);
			snd_seq_prioq_हटाओ_events(q->समयq, client, info);
		पूर्ण
		queueमुक्त(q);
	पूर्ण
पूर्ण

/*----------------------------------------------------------------*/

/*
 * send events to all subscribed ports
 */
अटल व्योम queue_broadcast_event(काष्ठा snd_seq_queue *q, काष्ठा snd_seq_event *ev,
				  पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा snd_seq_event sev;

	sev = *ev;
	
	sev.flags = SNDRV_SEQ_TIME_STAMP_TICK|SNDRV_SEQ_TIME_MODE_ABS;
	sev.समय.tick = q->समयr->tick.cur_tick;
	sev.queue = q->queue;
	sev.data.queue.queue = q->queue;

	/* broadcast events from Timer port */
	sev.source.client = SNDRV_SEQ_CLIENT_SYSTEM;
	sev.source.port = SNDRV_SEQ_PORT_SYSTEM_TIMER;
	sev.dest.client = SNDRV_SEQ_ADDRESS_SUBSCRIBERS;
	snd_seq_kernel_client_dispatch(SNDRV_SEQ_CLIENT_SYSTEM, &sev, atomic, hop);
पूर्ण

/*
 * process a received queue-control event.
 * this function is exported क्रम seq_sync.c.
 */
अटल व्योम snd_seq_queue_process_event(काष्ठा snd_seq_queue *q,
					काष्ठा snd_seq_event *ev,
					पूर्णांक atomic, पूर्णांक hop)
अणु
	चयन (ev->type) अणु
	हाल SNDRV_SEQ_EVENT_START:
		snd_seq_prioq_leave(q->tickq, ev->source.client, 1);
		snd_seq_prioq_leave(q->समयq, ev->source.client, 1);
		अगर (! snd_seq_समयr_start(q->समयr))
			queue_broadcast_event(q, ev, atomic, hop);
		अवरोध;

	हाल SNDRV_SEQ_EVENT_CONTINUE:
		अगर (! snd_seq_समयr_जारी(q->समयr))
			queue_broadcast_event(q, ev, atomic, hop);
		अवरोध;

	हाल SNDRV_SEQ_EVENT_STOP:
		snd_seq_समयr_stop(q->समयr);
		queue_broadcast_event(q, ev, atomic, hop);
		अवरोध;

	हाल SNDRV_SEQ_EVENT_TEMPO:
		snd_seq_समयr_set_tempo(q->समयr, ev->data.queue.param.value);
		queue_broadcast_event(q, ev, atomic, hop);
		अवरोध;

	हाल SNDRV_SEQ_EVENT_SETPOS_TICK:
		अगर (snd_seq_समयr_set_position_tick(q->समयr, ev->data.queue.param.समय.tick) == 0) अणु
			queue_broadcast_event(q, ev, atomic, hop);
		पूर्ण
		अवरोध;

	हाल SNDRV_SEQ_EVENT_SETPOS_TIME:
		अगर (snd_seq_समयr_set_position_समय(q->समयr, ev->data.queue.param.समय.समय) == 0) अणु
			queue_broadcast_event(q, ev, atomic, hop);
		पूर्ण
		अवरोध;
	हाल SNDRV_SEQ_EVENT_QUEUE_SKEW:
		अगर (snd_seq_समयr_set_skew(q->समयr,
					   ev->data.queue.param.skew.value,
					   ev->data.queue.param.skew.base) == 0) अणु
			queue_broadcast_event(q, ev, atomic, hop);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण


/*
 * Queue control via समयr control port:
 * this function is exported as a callback of समयr port.
 */
पूर्णांक snd_seq_control_queue(काष्ठा snd_seq_event *ev, पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा snd_seq_queue *q;

	अगर (snd_BUG_ON(!ev))
		वापस -EINVAL;
	q = queueptr(ev->data.queue.queue);

	अगर (q == शून्य)
		वापस -EINVAL;

	अगर (! queue_access_lock(q, ev->source.client)) अणु
		queueमुक्त(q);
		वापस -EPERM;
	पूर्ण

	snd_seq_queue_process_event(q, ev, atomic, hop);

	queue_access_unlock(q);
	queueमुक्त(q);
	वापस 0;
पूर्ण


/*----------------------------------------------------------------*/

#अगर_घोषित CONFIG_SND_PROC_FS
/* exported to seq_info.c */
व्योम snd_seq_info_queues_पढ़ो(काष्ठा snd_info_entry *entry, 
			      काष्ठा snd_info_buffer *buffer)
अणु
	पूर्णांक i, bpm;
	काष्ठा snd_seq_queue *q;
	काष्ठा snd_seq_समयr *पंचांगr;
	bool locked;
	पूर्णांक owner;

	क्रम (i = 0; i < SNDRV_SEQ_MAX_QUEUES; i++) अणु
		अगर ((q = queueptr(i)) == शून्य)
			जारी;

		पंचांगr = q->समयr;
		अगर (पंचांगr->tempo)
			bpm = 60000000 / पंचांगr->tempo;
		अन्यथा
			bpm = 0;

		spin_lock_irq(&q->owner_lock);
		locked = q->locked;
		owner = q->owner;
		spin_unlock_irq(&q->owner_lock);

		snd_iम_लिखो(buffer, "queue %d: [%s]\n", q->queue, q->name);
		snd_iम_लिखो(buffer, "owned by client    : %d\n", owner);
		snd_iम_लिखो(buffer, "lock status        : %s\n", locked ? "Locked" : "Free");
		snd_iम_लिखो(buffer, "queued time events : %d\n", snd_seq_prioq_avail(q->समयq));
		snd_iम_लिखो(buffer, "queued tick events : %d\n", snd_seq_prioq_avail(q->tickq));
		snd_iम_लिखो(buffer, "timer state        : %s\n", पंचांगr->running ? "Running" : "Stopped");
		snd_iम_लिखो(buffer, "timer PPQ          : %d\n", पंचांगr->ppq);
		snd_iम_लिखो(buffer, "current tempo      : %d\n", पंचांगr->tempo);
		snd_iम_लिखो(buffer, "current BPM        : %d\n", bpm);
		snd_iम_लिखो(buffer, "current time       : %d.%09d s\n", पंचांगr->cur_समय.tv_sec, पंचांगr->cur_समय.tv_nsec);
		snd_iम_लिखो(buffer, "current tick       : %d\n", पंचांगr->tick.cur_tick);
		snd_iम_लिखो(buffer, "\n");
		queueमुक्त(q);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_PROC_FS */

