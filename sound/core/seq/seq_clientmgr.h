<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   ALSA sequencer Client Manager
 *   Copyright (c) 1998-1999 by Frank van de Pol <fvdpol@coil.demon.nl>
 */
#अगर_अघोषित __SND_SEQ_CLIENTMGR_H
#घोषणा __SND_SEQ_CLIENTMGR_H

#समावेश <sound/seq_kernel.h>
#समावेश <linux/bitops.h>
#समावेश "seq_fifo.h"
#समावेश "seq_ports.h"
#समावेश "seq_lock.h"


/* client manager */

काष्ठा snd_seq_user_client अणु
	काष्ठा file *file;	/* file काष्ठा of client */
	/* ... */
	काष्ठा pid *owner;
	
	/* fअगरo */
	काष्ठा snd_seq_fअगरo *fअगरo;	/* queue क्रम incoming events */
	पूर्णांक fअगरo_pool_size;
पूर्ण;

काष्ठा snd_seq_kernel_client अणु
	/* ... */
	काष्ठा snd_card *card;
पूर्ण;


काष्ठा snd_seq_client अणु
	snd_seq_client_type_t type;
	अचिन्हित पूर्णांक accept_input: 1,
		accept_output: 1;
	अक्षर name[64];		/* client name */
	पूर्णांक number;		/* client number */
	अचिन्हित पूर्णांक filter;	/* filter flags */
	DECLARE_BITMAP(event_filter, 256);
	snd_use_lock_t use_lock;
	पूर्णांक event_lost;
	/* ports */
	पूर्णांक num_ports;		/* number of ports */
	काष्ठा list_head ports_list_head;
	rwlock_t ports_lock;
	काष्ठा mutex ports_mutex;
	काष्ठा mutex ioctl_mutex;
	पूर्णांक convert32;		/* convert 32->64bit */

	/* output pool */
	काष्ठा snd_seq_pool *pool;		/* memory pool क्रम this client */

	जोड़ अणु
		काष्ठा snd_seq_user_client user;
		काष्ठा snd_seq_kernel_client kernel;
	पूर्ण data;
पूर्ण;

/* usage statistics */
काष्ठा snd_seq_usage अणु
	पूर्णांक cur;
	पूर्णांक peak;
पूर्ण;


पूर्णांक client_init_data(व्योम);
पूर्णांक snd_sequencer_device_init(व्योम);
व्योम snd_sequencer_device_करोne(व्योम);

/* get locked poपूर्णांकer to client */
काष्ठा snd_seq_client *snd_seq_client_use_ptr(पूर्णांक clientid);

/* unlock poपूर्णांकer to client */
#घोषणा snd_seq_client_unlock(client) snd_use_lock_मुक्त(&(client)->use_lock)

/* dispatch event to client(s) */
पूर्णांक snd_seq_dispatch_event(काष्ठा snd_seq_event_cell *cell, पूर्णांक atomic, पूर्णांक hop);

पूर्णांक snd_seq_kernel_client_ग_लिखो_poll(पूर्णांक clientid, काष्ठा file *file, poll_table *रुको);
पूर्णांक snd_seq_client_notअगरy_subscription(पूर्णांक client, पूर्णांक port,
				       काष्ठा snd_seq_port_subscribe *info, पूर्णांक evtype);

/* only क्रम OSS sequencer */
bool snd_seq_client_ioctl_lock(पूर्णांक clientid);
व्योम snd_seq_client_ioctl_unlock(पूर्णांक clientid);

बाह्य पूर्णांक seq_client_load[15];

#पूर्ण_अगर
