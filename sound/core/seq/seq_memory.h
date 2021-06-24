<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  ALSA sequencer Memory Manager
 *  Copyright (c) 1998 by Frank van de Pol <fvdpol@coil.demon.nl>
 */
#अगर_अघोषित __SND_SEQ_MEMORYMGR_H
#घोषणा __SND_SEQ_MEMORYMGR_H

#समावेश <sound/seq_kernel.h>
#समावेश <linux/poll.h>

काष्ठा snd_info_buffer;

/* container क्रम sequencer event (पूर्णांकernal use) */
काष्ठा snd_seq_event_cell अणु
	काष्ठा snd_seq_event event;
	काष्ठा snd_seq_pool *pool;				/* used pool */
	काष्ठा snd_seq_event_cell *next;	/* next cell */
पूर्ण;

/* design note: the pool is a contiguous block of memory, अगर we dynamicly
   want to add additional cells to the pool be better store this in another
   pool as we need to know the base address of the pool when releasing
   memory. */

काष्ठा snd_seq_pool अणु
	काष्ठा snd_seq_event_cell *ptr;	/* poपूर्णांकer to first event chunk */
	काष्ठा snd_seq_event_cell *मुक्त;	/* poपूर्णांकer to the head of the मुक्त list */

	पूर्णांक total_elements;	/* pool size actually allocated */
	atomic_t counter;	/* cells मुक्त */

	पूर्णांक size;		/* pool size to be allocated */
	पूर्णांक room;		/* watermark क्रम sleep/wakeup */

	पूर्णांक closing;

	/* statistics */
	पूर्णांक max_used;
	पूर्णांक event_alloc_nopool;
	पूर्णांक event_alloc_failures;
	पूर्णांक event_alloc_success;

	/* Write locking */
	रुको_queue_head_t output_sleep;

	/* Pool lock */
	spinlock_t lock;
पूर्ण;

व्योम snd_seq_cell_मुक्त(काष्ठा snd_seq_event_cell *cell);

पूर्णांक snd_seq_event_dup(काष्ठा snd_seq_pool *pool, काष्ठा snd_seq_event *event,
		      काष्ठा snd_seq_event_cell **cellp, पूर्णांक nonblock,
		      काष्ठा file *file, काष्ठा mutex *mutexp);

/* वापस number of unused (मुक्त) cells */
अटल अंतरभूत पूर्णांक snd_seq_unused_cells(काष्ठा snd_seq_pool *pool)
अणु
	वापस pool ? pool->total_elements - atomic_पढ़ो(&pool->counter) : 0;
पूर्ण

/* वापस total number of allocated cells */
अटल अंतरभूत पूर्णांक snd_seq_total_cells(काष्ठा snd_seq_pool *pool)
अणु
	वापस pool ? pool->total_elements : 0;
पूर्ण

/* init pool - allocate events */
पूर्णांक snd_seq_pool_init(काष्ठा snd_seq_pool *pool);

/* करोne pool - मुक्त events */
व्योम snd_seq_pool_mark_closing(काष्ठा snd_seq_pool *pool);
पूर्णांक snd_seq_pool_करोne(काष्ठा snd_seq_pool *pool);

/* create pool */
काष्ठा snd_seq_pool *snd_seq_pool_new(पूर्णांक poolsize);

/* हटाओ pool */
पूर्णांक snd_seq_pool_delete(काष्ठा snd_seq_pool **pool);

/* polling */
पूर्णांक snd_seq_pool_poll_रुको(काष्ठा snd_seq_pool *pool, काष्ठा file *file, poll_table *रुको);

व्योम snd_seq_info_pool(काष्ठा snd_info_buffer *buffer,
		       काष्ठा snd_seq_pool *pool, अक्षर *space);

#पूर्ण_अगर
