<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   ALSA sequencer FIFO
 *   Copyright (c) 1998 by Frank van de Pol <fvdpol@coil.demon.nl>
 */
#अगर_अघोषित __SND_SEQ_FIFO_H
#घोषणा __SND_SEQ_FIFO_H

#समावेश "seq_memory.h"
#समावेश "seq_lock.h"


/* === FIFO === */

काष्ठा snd_seq_fअगरo अणु
	काष्ठा snd_seq_pool *pool;		/* FIFO pool */
	काष्ठा snd_seq_event_cell *head;    	/* poपूर्णांकer to head of fअगरo */
	काष्ठा snd_seq_event_cell *tail;    	/* poपूर्णांकer to tail of fअगरo */
	पूर्णांक cells;
	spinlock_t lock;
	snd_use_lock_t use_lock;
	रुको_queue_head_t input_sleep;
	atomic_t overflow;

पूर्ण;

/* create new fअगरo (स्थिरructor) */
काष्ठा snd_seq_fअगरo *snd_seq_fअगरo_new(पूर्णांक poolsize);

/* delete fअगरo (deकाष्ठाor) */
व्योम snd_seq_fअगरo_delete(काष्ठा snd_seq_fअगरo **f);


/* enqueue event to fअगरo */
पूर्णांक snd_seq_fअगरo_event_in(काष्ठा snd_seq_fअगरo *f, काष्ठा snd_seq_event *event);

/* lock fअगरo from release */
#घोषणा snd_seq_fअगरo_lock(fअगरo)		snd_use_lock_use(&(fअगरo)->use_lock)
#घोषणा snd_seq_fअगरo_unlock(fअगरo)	snd_use_lock_मुक्त(&(fअगरo)->use_lock)

/* get a cell from fअगरo - fअगरo should be locked */
पूर्णांक snd_seq_fअगरo_cell_out(काष्ठा snd_seq_fअगरo *f, काष्ठा snd_seq_event_cell **cellp, पूर्णांक nonblock);

/* मुक्त dequeued cell - fअगरo should be locked */
व्योम snd_seq_fअगरo_cell_putback(काष्ठा snd_seq_fअगरo *f, काष्ठा snd_seq_event_cell *cell);

/* clean up queue */
व्योम snd_seq_fअगरo_clear(काष्ठा snd_seq_fअगरo *f);

/* polling */
पूर्णांक snd_seq_fअगरo_poll_रुको(काष्ठा snd_seq_fअगरo *f, काष्ठा file *file, poll_table *रुको);

/* resize pool in fअगरo */
पूर्णांक snd_seq_fअगरo_resize(काष्ठा snd_seq_fअगरo *f, पूर्णांक poolsize);

/* get the number of unused cells safely */
पूर्णांक snd_seq_fअगरo_unused_cells(काष्ठा snd_seq_fअगरo *f);

#पूर्ण_अगर
