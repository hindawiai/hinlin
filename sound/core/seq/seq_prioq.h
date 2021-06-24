<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   ALSA sequencer Priority Queue
 *   Copyright (c) 1998 by Frank van de Pol <fvdpol@coil.demon.nl>
 */
#अगर_अघोषित __SND_SEQ_PRIOQ_H
#घोषणा __SND_SEQ_PRIOQ_H

#समावेश "seq_memory.h"


/* === PRIOQ === */

काष्ठा snd_seq_prioq अणु
	काष्ठा snd_seq_event_cell *head;      /* poपूर्णांकer to head of prioq */
	काष्ठा snd_seq_event_cell *tail;      /* poपूर्णांकer to tail of prioq */
	पूर्णांक cells;
	spinlock_t lock;
पूर्ण;


/* create new prioq (स्थिरructor) */
काष्ठा snd_seq_prioq *snd_seq_prioq_new(व्योम);

/* delete prioq (deकाष्ठाor) */
व्योम snd_seq_prioq_delete(काष्ठा snd_seq_prioq **fअगरo);

/* enqueue cell to prioq */
पूर्णांक snd_seq_prioq_cell_in(काष्ठा snd_seq_prioq *f, काष्ठा snd_seq_event_cell *cell);

/* dequeue cell from prioq */ 
काष्ठा snd_seq_event_cell *snd_seq_prioq_cell_out(काष्ठा snd_seq_prioq *f,
						  व्योम *current_समय);

/* वापस number of events available in prioq */
पूर्णांक snd_seq_prioq_avail(काष्ठा snd_seq_prioq *f);

/* client left queue */
व्योम snd_seq_prioq_leave(काष्ठा snd_seq_prioq *f, पूर्णांक client, पूर्णांक बारtamp);        

/* Remove events */
व्योम snd_seq_prioq_हटाओ_events(काष्ठा snd_seq_prioq *f, पूर्णांक client,
				 काष्ठा snd_seq_हटाओ_events *info);

#पूर्ण_अगर
