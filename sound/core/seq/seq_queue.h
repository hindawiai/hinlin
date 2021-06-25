<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   ALSA sequencer Queue handling
 *   Copyright (c) 1998-1999 by Frank van de Pol <fvdpol@coil.demon.nl>
 */
#अगर_अघोषित __SND_SEQ_QUEUE_H
#घोषणा __SND_SEQ_QUEUE_H

#समावेश "seq_memory.h"
#समावेश "seq_prioq.h"
#समावेश "seq_timer.h"
#समावेश "seq_lock.h"
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/bitops.h>

#घोषणा SEQ_QUEUE_NO_OWNER (-1)

काष्ठा snd_seq_queue अणु
	पूर्णांक queue;		/* queue number */

	अक्षर name[64];		/* name of this queue */

	काष्ठा snd_seq_prioq	*tickq;		/* midi tick event queue */
	काष्ठा snd_seq_prioq	*समयq;		/* real-समय event queue */	
	
	काष्ठा snd_seq_समयr *समयr;	/* समय keeper क्रम this queue */
	पूर्णांक	owner;		/* client that 'owns' the समयr */
	bool	locked;		/* समयr is only accesibble by owner अगर set */
	bool	klocked;	/* kernel lock (after START) */
	bool	check_again;	/* concurrent access happened during check */
	bool	check_blocked;	/* queue being checked */

	अचिन्हित पूर्णांक flags;		/* status flags */
	अचिन्हित पूर्णांक info_flags;	/* info क्रम sync */

	spinlock_t owner_lock;
	spinlock_t check_lock;

	/* clients which uses this queue (biपंचांगap) */
	DECLARE_BITMAP(clients_biपंचांगap, SNDRV_SEQ_MAX_CLIENTS);
	अचिन्हित पूर्णांक clients;	/* users of this queue */
	काष्ठा mutex समयr_mutex;

	snd_use_lock_t use_lock;
पूर्ण;


/* get the number of current queues */
पूर्णांक snd_seq_queue_get_cur_queues(व्योम);

/* delete queues */ 
व्योम snd_seq_queues_delete(व्योम);


/* create new queue (स्थिरructor) */
काष्ठा snd_seq_queue *snd_seq_queue_alloc(पूर्णांक client, पूर्णांक locked, अचिन्हित पूर्णांक flags);

/* delete queue (deकाष्ठाor) */
पूर्णांक snd_seq_queue_delete(पूर्णांक client, पूर्णांक queueid);

/* final stage */
व्योम snd_seq_queue_client_leave(पूर्णांक client);

/* enqueue a event received from one the clients */
पूर्णांक snd_seq_enqueue_event(काष्ठा snd_seq_event_cell *cell, पूर्णांक atomic, पूर्णांक hop);

/* Remove events */
व्योम snd_seq_queue_client_leave_cells(पूर्णांक client);
व्योम snd_seq_queue_हटाओ_cells(पूर्णांक client, काष्ठा snd_seq_हटाओ_events *info);

/* वापस poपूर्णांकer to queue काष्ठाure क्रम specअगरied id */
काष्ठा snd_seq_queue *queueptr(पूर्णांक queueid);
/* unlock */
#घोषणा queueमुक्त(q) snd_use_lock_मुक्त(&(q)->use_lock)

/* वापस the (first) queue matching with the specअगरied name */
काष्ठा snd_seq_queue *snd_seq_queue_find_name(अक्षर *name);

/* check single queue and dispatch events */
व्योम snd_seq_check_queue(काष्ठा snd_seq_queue *q, पूर्णांक atomic, पूर्णांक hop);

/* access to queue's parameters */
पूर्णांक snd_seq_queue_check_access(पूर्णांक queueid, पूर्णांक client);
पूर्णांक snd_seq_queue_समयr_set_tempo(पूर्णांक queueid, पूर्णांक client, काष्ठा snd_seq_queue_tempo *info);
पूर्णांक snd_seq_queue_set_owner(पूर्णांक queueid, पूर्णांक client, पूर्णांक locked);
पूर्णांक snd_seq_queue_set_locked(पूर्णांक queueid, पूर्णांक client, पूर्णांक locked);
पूर्णांक snd_seq_queue_समयr_खोलो(पूर्णांक queueid);
पूर्णांक snd_seq_queue_समयr_बंद(पूर्णांक queueid);
पूर्णांक snd_seq_queue_use(पूर्णांक queueid, पूर्णांक client, पूर्णांक use);
पूर्णांक snd_seq_queue_is_used(पूर्णांक queueid, पूर्णांक client);

पूर्णांक snd_seq_control_queue(काष्ठा snd_seq_event *ev, पूर्णांक atomic, पूर्णांक hop);

#पूर्ण_अगर
