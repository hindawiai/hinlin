<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ALSA sequencer Client Manager
 *  Copyright (c) 1998-2001 by Frank van de Pol <fvdpol@coil.demon.nl>
 *                             Jaroslav Kysela <perex@perex.cz>
 *                             Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/minors.h>
#समावेश <linux/kmod.h>

#समावेश <sound/seq_kernel.h>
#समावेश "seq_clientmgr.h"
#समावेश "seq_memory.h"
#समावेश "seq_queue.h"
#समावेश "seq_timer.h"
#समावेश "seq_info.h"
#समावेश "seq_system.h"
#समावेश <sound/seq_device.h>
#अगर_घोषित CONFIG_COMPAT
#समावेश <linux/compat.h>
#पूर्ण_अगर

/* Client Manager

 * this module handles the connections of userland and kernel clients
 * 
 */

/*
 * There are four ranges of client numbers (last two shared):
 * 0..15: global clients
 * 16..127: अटलally allocated client numbers क्रम cards 0..27
 * 128..191: dynamically allocated client numbers क्रम cards 28..31
 * 128..191: dynamically allocated client numbers क्रम applications
 */

/* number of kernel non-card clients */
#घोषणा SNDRV_SEQ_GLOBAL_CLIENTS	16
/* clients per cards, क्रम अटल clients */
#घोषणा SNDRV_SEQ_CLIENTS_PER_CARD	4
/* dynamically allocated client numbers (both kernel drivers and user space) */
#घोषणा SNDRV_SEQ_DYNAMIC_CLIENTS_BEGIN	128

#घोषणा SNDRV_SEQ_LFLG_INPUT	0x0001
#घोषणा SNDRV_SEQ_LFLG_OUTPUT	0x0002
#घोषणा SNDRV_SEQ_LFLG_OPEN	(SNDRV_SEQ_LFLG_INPUT|SNDRV_SEQ_LFLG_OUTPUT)

अटल DEFINE_SPINLOCK(clients_lock);
अटल DEFINE_MUTEX(रेजिस्टर_mutex);

/*
 * client table
 */
अटल अक्षर clienttablock[SNDRV_SEQ_MAX_CLIENTS];
अटल काष्ठा snd_seq_client *clienttab[SNDRV_SEQ_MAX_CLIENTS];
अटल काष्ठा snd_seq_usage client_usage;

/*
 * prototypes
 */
अटल पूर्णांक bounce_error_event(काष्ठा snd_seq_client *client,
			      काष्ठा snd_seq_event *event,
			      पूर्णांक err, पूर्णांक atomic, पूर्णांक hop);
अटल पूर्णांक snd_seq_deliver_single_event(काष्ठा snd_seq_client *client,
					काष्ठा snd_seq_event *event,
					पूर्णांक filter, पूर्णांक atomic, पूर्णांक hop);

/*
 */
अटल अंतरभूत अचिन्हित लघु snd_seq_file_flags(काष्ठा file *file)
अणु
        चयन (file->f_mode & (FMODE_READ | FMODE_WRITE)) अणु
        हाल FMODE_WRITE:
                वापस SNDRV_SEQ_LFLG_OUTPUT;
        हाल FMODE_READ:
                वापस SNDRV_SEQ_LFLG_INPUT;
        शेष:
                वापस SNDRV_SEQ_LFLG_OPEN;
        पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक snd_seq_ग_लिखो_pool_allocated(काष्ठा snd_seq_client *client)
अणु
	वापस snd_seq_total_cells(client->pool) > 0;
पूर्ण

/* वापस poपूर्णांकer to client काष्ठाure क्रम specअगरied id */
अटल काष्ठा snd_seq_client *clientptr(पूर्णांक clientid)
अणु
	अगर (clientid < 0 || clientid >= SNDRV_SEQ_MAX_CLIENTS) अणु
		pr_debug("ALSA: seq: oops. Trying to get pointer to client %d\n",
			   clientid);
		वापस शून्य;
	पूर्ण
	वापस clienttab[clientid];
पूर्ण

काष्ठा snd_seq_client *snd_seq_client_use_ptr(पूर्णांक clientid)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_seq_client *client;

	अगर (clientid < 0 || clientid >= SNDRV_SEQ_MAX_CLIENTS) अणु
		pr_debug("ALSA: seq: oops. Trying to get pointer to client %d\n",
			   clientid);
		वापस शून्य;
	पूर्ण
	spin_lock_irqsave(&clients_lock, flags);
	client = clientptr(clientid);
	अगर (client)
		जाओ __lock;
	अगर (clienttablock[clientid]) अणु
		spin_unlock_irqrestore(&clients_lock, flags);
		वापस शून्य;
	पूर्ण
	spin_unlock_irqrestore(&clients_lock, flags);
#अगर_घोषित CONFIG_MODULES
	अगर (!in_पूर्णांकerrupt()) अणु
		अटल अक्षर client_requested[SNDRV_SEQ_GLOBAL_CLIENTS];
		अटल अक्षर card_requested[SNDRV_CARDS];
		अगर (clientid < SNDRV_SEQ_GLOBAL_CLIENTS) अणु
			पूर्णांक idx;
			
			अगर (!client_requested[clientid]) अणु
				client_requested[clientid] = 1;
				क्रम (idx = 0; idx < 15; idx++) अणु
					अगर (seq_client_load[idx] < 0)
						अवरोध;
					अगर (seq_client_load[idx] == clientid) अणु
						request_module("snd-seq-client-%i",
							       clientid);
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (clientid < SNDRV_SEQ_DYNAMIC_CLIENTS_BEGIN) अणु
			पूर्णांक card = (clientid - SNDRV_SEQ_GLOBAL_CLIENTS) /
				SNDRV_SEQ_CLIENTS_PER_CARD;
			अगर (card < snd_ecards_limit) अणु
				अगर (! card_requested[card]) अणु
					card_requested[card] = 1;
					snd_request_card(card);
				पूर्ण
				snd_seq_device_load_drivers();
			पूर्ण
		पूर्ण
		spin_lock_irqsave(&clients_lock, flags);
		client = clientptr(clientid);
		अगर (client)
			जाओ __lock;
		spin_unlock_irqrestore(&clients_lock, flags);
	पूर्ण
#पूर्ण_अगर
	वापस शून्य;

      __lock:
	snd_use_lock_use(&client->use_lock);
	spin_unlock_irqrestore(&clients_lock, flags);
	वापस client;
पूर्ण

/* Take refcount and perक्रमm ioctl_mutex lock on the given client;
 * used only क्रम OSS sequencer
 * Unlock via snd_seq_client_ioctl_unlock() below
 */
bool snd_seq_client_ioctl_lock(पूर्णांक clientid)
अणु
	काष्ठा snd_seq_client *client;

	client = snd_seq_client_use_ptr(clientid);
	अगर (!client)
		वापस false;
	mutex_lock(&client->ioctl_mutex);
	/* The client isn't unrefed here; see snd_seq_client_ioctl_unlock() */
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(snd_seq_client_ioctl_lock);

/* Unlock and unref the given client; क्रम OSS sequencer use only */
व्योम snd_seq_client_ioctl_unlock(पूर्णांक clientid)
अणु
	काष्ठा snd_seq_client *client;

	client = snd_seq_client_use_ptr(clientid);
	अगर (WARN_ON(!client))
		वापस;
	mutex_unlock(&client->ioctl_mutex);
	/* The करोubly unrefs below are पूर्णांकentional; the first one releases the
	 * leftover from snd_seq_client_ioctl_lock() above, and the second one
	 * is क्रम releasing snd_seq_client_use_ptr() in this function
	 */
	snd_seq_client_unlock(client);
	snd_seq_client_unlock(client);
पूर्ण
EXPORT_SYMBOL_GPL(snd_seq_client_ioctl_unlock);

अटल व्योम usage_alloc(काष्ठा snd_seq_usage *res, पूर्णांक num)
अणु
	res->cur += num;
	अगर (res->cur > res->peak)
		res->peak = res->cur;
पूर्ण

अटल व्योम usage_मुक्त(काष्ठा snd_seq_usage *res, पूर्णांक num)
अणु
	res->cur -= num;
पूर्ण

/* initialise data काष्ठाures */
पूर्णांक __init client_init_data(व्योम)
अणु
	/* zap out the client table */
	स_रखो(&clienttablock, 0, माप(clienttablock));
	स_रखो(&clienttab, 0, माप(clienttab));
	वापस 0;
पूर्ण


अटल काष्ठा snd_seq_client *seq_create_client1(पूर्णांक client_index, पूर्णांक poolsize)
अणु
	पूर्णांक c;
	काष्ठा snd_seq_client *client;

	/* init client data */
	client = kzalloc(माप(*client), GFP_KERNEL);
	अगर (client == शून्य)
		वापस शून्य;
	client->pool = snd_seq_pool_new(poolsize);
	अगर (client->pool == शून्य) अणु
		kमुक्त(client);
		वापस शून्य;
	पूर्ण
	client->type = NO_CLIENT;
	snd_use_lock_init(&client->use_lock);
	rwlock_init(&client->ports_lock);
	mutex_init(&client->ports_mutex);
	INIT_LIST_HEAD(&client->ports_list_head);
	mutex_init(&client->ioctl_mutex);

	/* find मुक्त slot in the client table */
	spin_lock_irq(&clients_lock);
	अगर (client_index < 0) अणु
		क्रम (c = SNDRV_SEQ_DYNAMIC_CLIENTS_BEGIN;
		     c < SNDRV_SEQ_MAX_CLIENTS;
		     c++) अणु
			अगर (clienttab[c] || clienttablock[c])
				जारी;
			clienttab[client->number = c] = client;
			spin_unlock_irq(&clients_lock);
			वापस client;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (clienttab[client_index] == शून्य && !clienttablock[client_index]) अणु
			clienttab[client->number = client_index] = client;
			spin_unlock_irq(&clients_lock);
			वापस client;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&clients_lock);
	snd_seq_pool_delete(&client->pool);
	kमुक्त(client);
	वापस शून्य;	/* no मुक्त slot found or busy, वापस failure code */
पूर्ण


अटल पूर्णांक seq_मुक्त_client1(काष्ठा snd_seq_client *client)
अणु
	अगर (!client)
		वापस 0;
	spin_lock_irq(&clients_lock);
	clienttablock[client->number] = 1;
	clienttab[client->number] = शून्य;
	spin_unlock_irq(&clients_lock);
	snd_seq_delete_all_ports(client);
	snd_seq_queue_client_leave(client->number);
	snd_use_lock_sync(&client->use_lock);
	अगर (client->pool)
		snd_seq_pool_delete(&client->pool);
	spin_lock_irq(&clients_lock);
	clienttablock[client->number] = 0;
	spin_unlock_irq(&clients_lock);
	वापस 0;
पूर्ण


अटल व्योम seq_मुक्त_client(काष्ठा snd_seq_client * client)
अणु
	mutex_lock(&रेजिस्टर_mutex);
	चयन (client->type) अणु
	हाल NO_CLIENT:
		pr_warn("ALSA: seq: Trying to free unused client %d\n",
			client->number);
		अवरोध;
	हाल USER_CLIENT:
	हाल KERNEL_CLIENT:
		seq_मुक्त_client1(client);
		usage_मुक्त(&client_usage, 1);
		अवरोध;

	शेष:
		pr_err("ALSA: seq: Trying to free client %d with undefined type = %d\n",
			   client->number, client->type);
	पूर्ण
	mutex_unlock(&रेजिस्टर_mutex);

	snd_seq_प्रणाली_client_ev_client_निकास(client->number);
पूर्ण



/* -------------------------------------------------------- */

/* create a user client */
अटल पूर्णांक snd_seq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक c, mode;			/* client id */
	काष्ठा snd_seq_client *client;
	काष्ठा snd_seq_user_client *user;
	पूर्णांक err;

	err = stream_खोलो(inode, file);
	अगर (err < 0)
		वापस err;

	mutex_lock(&रेजिस्टर_mutex);
	client = seq_create_client1(-1, SNDRV_SEQ_DEFAULT_EVENTS);
	अगर (!client) अणु
		mutex_unlock(&रेजिस्टर_mutex);
		वापस -ENOMEM;	/* failure code */
	पूर्ण

	mode = snd_seq_file_flags(file);
	अगर (mode & SNDRV_SEQ_LFLG_INPUT)
		client->accept_input = 1;
	अगर (mode & SNDRV_SEQ_LFLG_OUTPUT)
		client->accept_output = 1;

	user = &client->data.user;
	user->fअगरo = शून्य;
	user->fअगरo_pool_size = 0;

	अगर (mode & SNDRV_SEQ_LFLG_INPUT) अणु
		user->fअगरo_pool_size = SNDRV_SEQ_DEFAULT_CLIENT_EVENTS;
		user->fअगरo = snd_seq_fअगरo_new(user->fअगरo_pool_size);
		अगर (user->fअगरo == शून्य) अणु
			seq_मुक्त_client1(client);
			kमुक्त(client);
			mutex_unlock(&रेजिस्टर_mutex);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	usage_alloc(&client_usage, 1);
	client->type = USER_CLIENT;
	mutex_unlock(&रेजिस्टर_mutex);

	c = client->number;
	file->निजी_data = client;

	/* fill client data */
	user->file = file;
	प्र_लिखो(client->name, "Client-%d", c);
	client->data.user.owner = get_pid(task_pid(current));

	/* make others aware this new client */
	snd_seq_प्रणाली_client_ev_client_start(c);

	वापस 0;
पूर्ण

/* delete a user client */
अटल पूर्णांक snd_seq_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा snd_seq_client *client = file->निजी_data;

	अगर (client) अणु
		seq_मुक्त_client(client);
		अगर (client->data.user.fअगरo)
			snd_seq_fअगरo_delete(&client->data.user.fअगरo);
		put_pid(client->data.user.owner);
		kमुक्त(client);
	पूर्ण

	वापस 0;
पूर्ण


/* handle client पढ़ो() */
/* possible error values:
 *	-ENXIO	invalid client or file खोलो mode
 *	-ENOSPC	FIFO overflow (the flag is cleared after this error report)
 *	-EINVAL	no enough user-space buffer to ग_लिखो the whole event
 *	-EFAULT	seg. fault during copy to user space
 */
अटल sमाप_प्रकार snd_seq_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			    loff_t *offset)
अणु
	काष्ठा snd_seq_client *client = file->निजी_data;
	काष्ठा snd_seq_fअगरo *fअगरo;
	पूर्णांक err;
	दीर्घ result = 0;
	काष्ठा snd_seq_event_cell *cell;

	अगर (!(snd_seq_file_flags(file) & SNDRV_SEQ_LFLG_INPUT))
		वापस -ENXIO;

	अगर (!access_ok(buf, count))
		वापस -EFAULT;

	/* check client काष्ठाures are in place */
	अगर (snd_BUG_ON(!client))
		वापस -ENXIO;

	अगर (!client->accept_input || (fअगरo = client->data.user.fअगरo) == शून्य)
		वापस -ENXIO;

	अगर (atomic_पढ़ो(&fअगरo->overflow) > 0) अणु
		/* buffer overflow is detected */
		snd_seq_fअगरo_clear(fअगरo);
		/* वापस error code */
		वापस -ENOSPC;
	पूर्ण

	cell = शून्य;
	err = 0;
	snd_seq_fअगरo_lock(fअगरo);

	/* जबतक data available in queue */
	जबतक (count >= माप(काष्ठा snd_seq_event)) अणु
		पूर्णांक nonblock;

		nonblock = (file->f_flags & O_NONBLOCK) || result > 0;
		अगर ((err = snd_seq_fअगरo_cell_out(fअगरo, &cell, nonblock)) < 0) अणु
			अवरोध;
		पूर्ण
		अगर (snd_seq_ev_is_variable(&cell->event)) अणु
			काष्ठा snd_seq_event पंचांगpev;
			पंचांगpev = cell->event;
			पंचांगpev.data.ext.len &= ~SNDRV_SEQ_EXT_MASK;
			अगर (copy_to_user(buf, &पंचांगpev, माप(काष्ठा snd_seq_event))) अणु
				err = -EFAULT;
				अवरोध;
			पूर्ण
			count -= माप(काष्ठा snd_seq_event);
			buf += माप(काष्ठा snd_seq_event);
			err = snd_seq_expand_var_event(&cell->event, count,
						       (अक्षर __क्रमce *)buf, 0,
						       माप(काष्ठा snd_seq_event));
			अगर (err < 0)
				अवरोध;
			result += err;
			count -= err;
			buf += err;
		पूर्ण अन्यथा अणु
			अगर (copy_to_user(buf, &cell->event, माप(काष्ठा snd_seq_event))) अणु
				err = -EFAULT;
				अवरोध;
			पूर्ण
			count -= माप(काष्ठा snd_seq_event);
			buf += माप(काष्ठा snd_seq_event);
		पूर्ण
		snd_seq_cell_मुक्त(cell);
		cell = शून्य; /* to be sure */
		result += माप(काष्ठा snd_seq_event);
	पूर्ण

	अगर (err < 0) अणु
		अगर (cell)
			snd_seq_fअगरo_cell_putback(fअगरo, cell);
		अगर (err == -EAGAIN && result > 0)
			err = 0;
	पूर्ण
	snd_seq_fअगरo_unlock(fअगरo);

	वापस (err < 0) ? err : result;
पूर्ण


/*
 * check access permission to the port
 */
अटल पूर्णांक check_port_perm(काष्ठा snd_seq_client_port *port, अचिन्हित पूर्णांक flags)
अणु
	अगर ((port->capability & flags) != flags)
		वापस 0;
	वापस flags;
पूर्ण

/*
 * check अगर the destination client is available, and वापस the poपूर्णांकer
 * अगर filter is non-zero, client filter biपंचांगap is tested.
 */
अटल काष्ठा snd_seq_client *get_event_dest_client(काष्ठा snd_seq_event *event,
						    पूर्णांक filter)
अणु
	काष्ठा snd_seq_client *dest;

	dest = snd_seq_client_use_ptr(event->dest.client);
	अगर (dest == शून्य)
		वापस शून्य;
	अगर (! dest->accept_input)
		जाओ __not_avail;
	अगर ((dest->filter & SNDRV_SEQ_FILTER_USE_EVENT) &&
	    ! test_bit(event->type, dest->event_filter))
		जाओ __not_avail;
	अगर (filter && !(dest->filter & filter))
		जाओ __not_avail;

	वापस dest; /* ok - accessible */
__not_avail:
	snd_seq_client_unlock(dest);
	वापस शून्य;
पूर्ण


/*
 * Return the error event.
 *
 * If the receiver client is a user client, the original event is
 * encapsulated in SNDRV_SEQ_EVENT_BOUNCE as variable length event.  If
 * the original event is also variable length, the बाह्यal data is
 * copied after the event record. 
 * If the receiver client is a kernel client, the original event is
 * quoted in SNDRV_SEQ_EVENT_KERNEL_ERROR, since this requires no extra
 * kदो_स्मृति.
 */
अटल पूर्णांक bounce_error_event(काष्ठा snd_seq_client *client,
			      काष्ठा snd_seq_event *event,
			      पूर्णांक err, पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा snd_seq_event bounce_ev;
	पूर्णांक result;

	अगर (client == शून्य ||
	    ! (client->filter & SNDRV_SEQ_FILTER_BOUNCE) ||
	    ! client->accept_input)
		वापस 0; /* ignored */

	/* set up quoted error */
	स_रखो(&bounce_ev, 0, माप(bounce_ev));
	bounce_ev.type = SNDRV_SEQ_EVENT_KERNEL_ERROR;
	bounce_ev.flags = SNDRV_SEQ_EVENT_LENGTH_FIXED;
	bounce_ev.queue = SNDRV_SEQ_QUEUE_सूचीECT;
	bounce_ev.source.client = SNDRV_SEQ_CLIENT_SYSTEM;
	bounce_ev.source.port = SNDRV_SEQ_PORT_SYSTEM_ANNOUNCE;
	bounce_ev.dest.client = client->number;
	bounce_ev.dest.port = event->source.port;
	bounce_ev.data.quote.origin = event->dest;
	bounce_ev.data.quote.event = event;
	bounce_ev.data.quote.value = -err; /* use positive value */
	result = snd_seq_deliver_single_event(शून्य, &bounce_ev, 0, atomic, hop + 1);
	अगर (result < 0) अणु
		client->event_lost++;
		वापस result;
	पूर्ण

	वापस result;
पूर्ण


/*
 * reग_लिखो the समय-stamp of the event record with the curren समय
 * of the given queue.
 * वापस non-zero अगर updated.
 */
अटल पूर्णांक update_बारtamp_of_queue(काष्ठा snd_seq_event *event,
				     पूर्णांक queue, पूर्णांक real_समय)
अणु
	काष्ठा snd_seq_queue *q;

	q = queueptr(queue);
	अगर (! q)
		वापस 0;
	event->queue = queue;
	event->flags &= ~SNDRV_SEQ_TIME_STAMP_MASK;
	अगर (real_समय) अणु
		event->समय.समय = snd_seq_समयr_get_cur_समय(q->समयr, true);
		event->flags |= SNDRV_SEQ_TIME_STAMP_REAL;
	पूर्ण अन्यथा अणु
		event->समय.tick = snd_seq_समयr_get_cur_tick(q->समयr);
		event->flags |= SNDRV_SEQ_TIME_STAMP_TICK;
	पूर्ण
	queueमुक्त(q);
	वापस 1;
पूर्ण


/*
 * deliver an event to the specअगरied destination.
 * अगर filter is non-zero, client filter biपंचांगap is tested.
 *
 *  RETURN VALUE: 0 : अगर succeeded
 *		 <0 : error
 */
अटल पूर्णांक snd_seq_deliver_single_event(काष्ठा snd_seq_client *client,
					काष्ठा snd_seq_event *event,
					पूर्णांक filter, पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा snd_seq_client *dest = शून्य;
	काष्ठा snd_seq_client_port *dest_port = शून्य;
	पूर्णांक result = -ENOENT;
	पूर्णांक direct;

	direct = snd_seq_ev_is_direct(event);

	dest = get_event_dest_client(event, filter);
	अगर (dest == शून्य)
		जाओ __skip;
	dest_port = snd_seq_port_use_ptr(dest, event->dest.port);
	अगर (dest_port == शून्य)
		जाओ __skip;

	/* check permission */
	अगर (! check_port_perm(dest_port, SNDRV_SEQ_PORT_CAP_WRITE)) अणु
		result = -EPERM;
		जाओ __skip;
	पूर्ण
		
	अगर (dest_port->बारtamping)
		update_बारtamp_of_queue(event, dest_port->समय_queue,
					  dest_port->समय_real);

	चयन (dest->type) अणु
	हाल USER_CLIENT:
		अगर (dest->data.user.fअगरo)
			result = snd_seq_fअगरo_event_in(dest->data.user.fअगरo, event);
		अवरोध;

	हाल KERNEL_CLIENT:
		अगर (dest_port->event_input == शून्य)
			अवरोध;
		result = dest_port->event_input(event, direct,
						dest_port->निजी_data,
						atomic, hop);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

  __skip:
	अगर (dest_port)
		snd_seq_port_unlock(dest_port);
	अगर (dest)
		snd_seq_client_unlock(dest);

	अगर (result < 0 && !direct) अणु
		result = bounce_error_event(client, event, result, atomic, hop);
	पूर्ण
	वापस result;
पूर्ण


/*
 * send the event to all subscribers:
 */
अटल पूर्णांक deliver_to_subscribers(काष्ठा snd_seq_client *client,
				  काष्ठा snd_seq_event *event,
				  पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा snd_seq_subscribers *subs;
	पूर्णांक err, result = 0, num_ev = 0;
	काष्ठा snd_seq_event event_saved;
	काष्ठा snd_seq_client_port *src_port;
	काष्ठा snd_seq_port_subs_info *grp;

	src_port = snd_seq_port_use_ptr(client, event->source.port);
	अगर (src_port == शून्य)
		वापस -EINVAL; /* invalid source port */
	/* save original event record */
	event_saved = *event;
	grp = &src_port->c_src;
	
	/* lock list */
	अगर (atomic)
		पढ़ो_lock(&grp->list_lock);
	अन्यथा
		करोwn_पढ़ो_nested(&grp->list_mutex, hop);
	list_क्रम_each_entry(subs, &grp->list_head, src_list) अणु
		/* both ports पढ़ोy? */
		अगर (atomic_पढ़ो(&subs->ref_count) != 2)
			जारी;
		event->dest = subs->info.dest;
		अगर (subs->info.flags & SNDRV_SEQ_PORT_SUBS_TIMESTAMP)
			/* convert समय according to flag with subscription */
			update_बारtamp_of_queue(event, subs->info.queue,
						  subs->info.flags & SNDRV_SEQ_PORT_SUBS_TIME_REAL);
		err = snd_seq_deliver_single_event(client, event,
						   0, atomic, hop);
		अगर (err < 0) अणु
			/* save first error that occurs and जारी */
			अगर (!result)
				result = err;
			जारी;
		पूर्ण
		num_ev++;
		/* restore original event record */
		*event = event_saved;
	पूर्ण
	अगर (atomic)
		पढ़ो_unlock(&grp->list_lock);
	अन्यथा
		up_पढ़ो(&grp->list_mutex);
	*event = event_saved; /* restore */
	snd_seq_port_unlock(src_port);
	वापस (result < 0) ? result : num_ev;
पूर्ण


#अगर_घोषित SUPPORT_BROADCAST 
/*
 * broadcast to all ports:
 */
अटल पूर्णांक port_broadcast_event(काष्ठा snd_seq_client *client,
				काष्ठा snd_seq_event *event,
				पूर्णांक atomic, पूर्णांक hop)
अणु
	पूर्णांक num_ev = 0, err, result = 0;
	काष्ठा snd_seq_client *dest_client;
	काष्ठा snd_seq_client_port *port;

	dest_client = get_event_dest_client(event, SNDRV_SEQ_FILTER_BROADCAST);
	अगर (dest_client == शून्य)
		वापस 0; /* no matching destination */

	पढ़ो_lock(&dest_client->ports_lock);
	list_क्रम_each_entry(port, &dest_client->ports_list_head, list) अणु
		event->dest.port = port->addr.port;
		/* pass शून्य as source client to aव्योम error bounce */
		err = snd_seq_deliver_single_event(शून्य, event,
						   SNDRV_SEQ_FILTER_BROADCAST,
						   atomic, hop);
		अगर (err < 0) अणु
			/* save first error that occurs and जारी */
			अगर (!result)
				result = err;
			जारी;
		पूर्ण
		num_ev++;
	पूर्ण
	पढ़ो_unlock(&dest_client->ports_lock);
	snd_seq_client_unlock(dest_client);
	event->dest.port = SNDRV_SEQ_ADDRESS_BROADCAST; /* restore */
	वापस (result < 0) ? result : num_ev;
पूर्ण

/*
 * send the event to all clients:
 * अगर destination port is also ADDRESS_BROADCAST, deliver to all ports.
 */
अटल पूर्णांक broadcast_event(काष्ठा snd_seq_client *client,
			   काष्ठा snd_seq_event *event, पूर्णांक atomic, पूर्णांक hop)
अणु
	पूर्णांक err, result = 0, num_ev = 0;
	पूर्णांक dest;
	काष्ठा snd_seq_addr addr;

	addr = event->dest; /* save */

	क्रम (dest = 0; dest < SNDRV_SEQ_MAX_CLIENTS; dest++) अणु
		/* करोn't send to itself */
		अगर (dest == client->number)
			जारी;
		event->dest.client = dest;
		event->dest.port = addr.port;
		अगर (addr.port == SNDRV_SEQ_ADDRESS_BROADCAST)
			err = port_broadcast_event(client, event, atomic, hop);
		अन्यथा
			/* pass शून्य as source client to aव्योम error bounce */
			err = snd_seq_deliver_single_event(शून्य, event,
							   SNDRV_SEQ_FILTER_BROADCAST,
							   atomic, hop);
		अगर (err < 0) अणु
			/* save first error that occurs and जारी */
			अगर (!result)
				result = err;
			जारी;
		पूर्ण
		num_ev += err;
	पूर्ण
	event->dest = addr; /* restore */
	वापस (result < 0) ? result : num_ev;
पूर्ण


/* multicast - not supported yet */
अटल पूर्णांक multicast_event(काष्ठा snd_seq_client *client, काष्ठा snd_seq_event *event,
			   पूर्णांक atomic, पूर्णांक hop)
अणु
	pr_debug("ALSA: seq: multicast not supported yet.\n");
	वापस 0; /* ignored */
पूर्ण
#पूर्ण_अगर /* SUPPORT_BROADCAST */


/* deliver an event to the destination port(s).
 * अगर the event is to subscribers or broadcast, the event is dispatched
 * to multiple tarमाला_लो.
 *
 * RETURN VALUE: n > 0  : the number of delivered events.
 *               n == 0 : the event was not passed to any client.
 *               n < 0  : error - event was not processed.
 */
अटल पूर्णांक snd_seq_deliver_event(काष्ठा snd_seq_client *client, काष्ठा snd_seq_event *event,
				 पूर्णांक atomic, पूर्णांक hop)
अणु
	पूर्णांक result;

	hop++;
	अगर (hop >= SNDRV_SEQ_MAX_HOPS) अणु
		pr_debug("ALSA: seq: too long delivery path (%d:%d->%d:%d)\n",
			   event->source.client, event->source.port,
			   event->dest.client, event->dest.port);
		वापस -EMLINK;
	पूर्ण

	अगर (snd_seq_ev_is_variable(event) &&
	    snd_BUG_ON(atomic && (event->data.ext.len & SNDRV_SEQ_EXT_USRPTR)))
		वापस -EINVAL;

	अगर (event->queue == SNDRV_SEQ_ADDRESS_SUBSCRIBERS ||
	    event->dest.client == SNDRV_SEQ_ADDRESS_SUBSCRIBERS)
		result = deliver_to_subscribers(client, event, atomic, hop);
#अगर_घोषित SUPPORT_BROADCAST
	अन्यथा अगर (event->queue == SNDRV_SEQ_ADDRESS_BROADCAST ||
		 event->dest.client == SNDRV_SEQ_ADDRESS_BROADCAST)
		result = broadcast_event(client, event, atomic, hop);
	अन्यथा अगर (event->dest.client >= SNDRV_SEQ_MAX_CLIENTS)
		result = multicast_event(client, event, atomic, hop);
	अन्यथा अगर (event->dest.port == SNDRV_SEQ_ADDRESS_BROADCAST)
		result = port_broadcast_event(client, event, atomic, hop);
#पूर्ण_अगर
	अन्यथा
		result = snd_seq_deliver_single_event(client, event, 0, atomic, hop);

	वापस result;
पूर्ण

/*
 * dispatch an event cell:
 * This function is called only from queue check routines in समयr
 * पूर्णांकerrupts or after enqueued.
 * The event cell shall be released or re-queued in this function.
 *
 * RETURN VALUE: n > 0  : the number of delivered events.
 *		 n == 0 : the event was not passed to any client.
 *		 n < 0  : error - event was not processed.
 */
पूर्णांक snd_seq_dispatch_event(काष्ठा snd_seq_event_cell *cell, पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा snd_seq_client *client;
	पूर्णांक result;

	अगर (snd_BUG_ON(!cell))
		वापस -EINVAL;

	client = snd_seq_client_use_ptr(cell->event.source.client);
	अगर (client == शून्य) अणु
		snd_seq_cell_मुक्त(cell); /* release this cell */
		वापस -EINVAL;
	पूर्ण

	अगर (cell->event.type == SNDRV_SEQ_EVENT_NOTE) अणु
		/* NOTE event:
		 * the event cell is re-used as a NOTE-OFF event and
		 * enqueued again.
		 */
		काष्ठा snd_seq_event पंचांगpev, *ev;

		/* reserve this event to enqueue note-off later */
		पंचांगpev = cell->event;
		पंचांगpev.type = SNDRV_SEQ_EVENT_NOTEON;
		result = snd_seq_deliver_event(client, &पंचांगpev, atomic, hop);

		/*
		 * This was originally a note event.  We now re-use the
		 * cell क्रम the note-off event.
		 */

		ev = &cell->event;
		ev->type = SNDRV_SEQ_EVENT_NOTखातापूर्णF;
		ev->flags |= SNDRV_SEQ_PRIORITY_HIGH;

		/* add the duration समय */
		चयन (ev->flags & SNDRV_SEQ_TIME_STAMP_MASK) अणु
		हाल SNDRV_SEQ_TIME_STAMP_TICK:
			ev->समय.tick += ev->data.note.duration;
			अवरोध;
		हाल SNDRV_SEQ_TIME_STAMP_REAL:
			/* unit क्रम duration is ms */
			ev->समय.समय.tv_nsec += 1000000 * (ev->data.note.duration % 1000);
			ev->समय.समय.tv_sec += ev->data.note.duration / 1000 +
						ev->समय.समय.tv_nsec / 1000000000;
			ev->समय.समय.tv_nsec %= 1000000000;
			अवरोध;
		पूर्ण
		ev->data.note.velocity = ev->data.note.off_velocity;

		/* Now queue this cell as the note off event */
		अगर (snd_seq_enqueue_event(cell, atomic, hop) < 0)
			snd_seq_cell_मुक्त(cell); /* release this cell */

	पूर्ण अन्यथा अणु
		/* Normal events:
		 * event cell is मुक्तd after processing the event
		 */

		result = snd_seq_deliver_event(client, &cell->event, atomic, hop);
		snd_seq_cell_मुक्त(cell);
	पूर्ण

	snd_seq_client_unlock(client);
	वापस result;
पूर्ण


/* Allocate a cell from client pool and enqueue it to queue:
 * अगर pool is empty and blocking is TRUE, sleep until a new cell is
 * available.
 */
अटल पूर्णांक snd_seq_client_enqueue_event(काष्ठा snd_seq_client *client,
					काष्ठा snd_seq_event *event,
					काष्ठा file *file, पूर्णांक blocking,
					पूर्णांक atomic, पूर्णांक hop,
					काष्ठा mutex *mutexp)
अणु
	काष्ठा snd_seq_event_cell *cell;
	पूर्णांक err;

	/* special queue values - क्रमce direct passing */
	अगर (event->queue == SNDRV_SEQ_ADDRESS_SUBSCRIBERS) अणु
		event->dest.client = SNDRV_SEQ_ADDRESS_SUBSCRIBERS;
		event->queue = SNDRV_SEQ_QUEUE_सूचीECT;
	पूर्ण अन्यथा
#अगर_घोषित SUPPORT_BROADCAST
		अगर (event->queue == SNDRV_SEQ_ADDRESS_BROADCAST) अणु
			event->dest.client = SNDRV_SEQ_ADDRESS_BROADCAST;
			event->queue = SNDRV_SEQ_QUEUE_सूचीECT;
		पूर्ण
#पूर्ण_अगर
	अगर (event->dest.client == SNDRV_SEQ_ADDRESS_SUBSCRIBERS) अणु
		/* check presence of source port */
		काष्ठा snd_seq_client_port *src_port = snd_seq_port_use_ptr(client, event->source.port);
		अगर (src_port == शून्य)
			वापस -EINVAL;
		snd_seq_port_unlock(src_port);
	पूर्ण

	/* direct event processing without enqueued */
	अगर (snd_seq_ev_is_direct(event)) अणु
		अगर (event->type == SNDRV_SEQ_EVENT_NOTE)
			वापस -EINVAL; /* this event must be enqueued! */
		वापस snd_seq_deliver_event(client, event, atomic, hop);
	पूर्ण

	/* Not direct, normal queuing */
	अगर (snd_seq_queue_is_used(event->queue, client->number) <= 0)
		वापस -EINVAL;  /* invalid queue */
	अगर (! snd_seq_ग_लिखो_pool_allocated(client))
		वापस -ENXIO; /* queue is not allocated */

	/* allocate an event cell */
	err = snd_seq_event_dup(client->pool, event, &cell, !blocking || atomic,
				file, mutexp);
	अगर (err < 0)
		वापस err;

	/* we got a cell. enqueue it. */
	अगर ((err = snd_seq_enqueue_event(cell, atomic, hop)) < 0) अणु
		snd_seq_cell_मुक्त(cell);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * check validity of event type and data length.
 * वापस non-zero अगर invalid.
 */
अटल पूर्णांक check_event_type_and_length(काष्ठा snd_seq_event *ev)
अणु
	चयन (snd_seq_ev_length_type(ev)) अणु
	हाल SNDRV_SEQ_EVENT_LENGTH_FIXED:
		अगर (snd_seq_ev_is_variable_type(ev))
			वापस -EINVAL;
		अवरोध;
	हाल SNDRV_SEQ_EVENT_LENGTH_VARIABLE:
		अगर (! snd_seq_ev_is_variable_type(ev) ||
		    (ev->data.ext.len & ~SNDRV_SEQ_EXT_MASK) >= SNDRV_SEQ_MAX_EVENT_LEN)
			वापस -EINVAL;
		अवरोध;
	हाल SNDRV_SEQ_EVENT_LENGTH_VARUSR:
		अगर (! snd_seq_ev_is_direct(ev))
			वापस -EINVAL;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण


/* handle ग_लिखो() */
/* possible error values:
 *	-ENXIO	invalid client or file खोलो mode
 *	-ENOMEM	दो_स्मृति failed
 *	-EFAULT	seg. fault during copy from user space
 *	-EINVAL	invalid event
 *	-EAGAIN	no space in output pool
 *	-EINTR	पूर्णांकerrupts जबतक sleep
 *	-EMLINK	too many hops
 *	others	depends on वापस value from driver callback
 */
अटल sमाप_प्रकार snd_seq_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा snd_seq_client *client = file->निजी_data;
	पूर्णांक written = 0, len;
	पूर्णांक err, handled;
	काष्ठा snd_seq_event event;

	अगर (!(snd_seq_file_flags(file) & SNDRV_SEQ_LFLG_OUTPUT))
		वापस -ENXIO;

	/* check client काष्ठाures are in place */
	अगर (snd_BUG_ON(!client))
		वापस -ENXIO;
		
	अगर (!client->accept_output || client->pool == शून्य)
		वापस -ENXIO;

 repeat:
	handled = 0;
	/* allocate the pool now अगर the pool is not allocated yet */ 
	mutex_lock(&client->ioctl_mutex);
	अगर (client->pool->size > 0 && !snd_seq_ग_लिखो_pool_allocated(client)) अणु
		err = snd_seq_pool_init(client->pool);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	/* only process whole events */
	err = -EINVAL;
	जबतक (count >= माप(काष्ठा snd_seq_event)) अणु
		/* Read in the event header from the user */
		len = माप(event);
		अगर (copy_from_user(&event, buf, len)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		event.source.client = client->number;	/* fill in client number */
		/* Check क्रम extension data length */
		अगर (check_event_type_and_length(&event)) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		/* check क्रम special events */
		अगर (event.type == SNDRV_SEQ_EVENT_NONE)
			जाओ __skip_event;
		अन्यथा अगर (snd_seq_ev_is_reserved(&event)) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (snd_seq_ev_is_variable(&event)) अणु
			पूर्णांक extlen = event.data.ext.len & ~SNDRV_SEQ_EXT_MASK;
			अगर ((माप_प्रकार)(extlen + len) > count) अणु
				/* back out, will get an error this समय or next */
				err = -EINVAL;
				अवरोध;
			पूर्ण
			/* set user space poपूर्णांकer */
			event.data.ext.len = extlen | SNDRV_SEQ_EXT_USRPTR;
			event.data.ext.ptr = (अक्षर __क्रमce *)buf
						+ माप(काष्ठा snd_seq_event);
			len += extlen; /* increment data length */
		पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_COMPAT
			अगर (client->convert32 && snd_seq_ev_is_varusr(&event)) अणु
				व्योम *ptr = (व्योम __क्रमce *)compat_ptr(event.data.raw32.d[1]);
				event.data.ext.ptr = ptr;
			पूर्ण
#पूर्ण_अगर
		पूर्ण

		/* ok, enqueue it */
		err = snd_seq_client_enqueue_event(client, &event, file,
						   !(file->f_flags & O_NONBLOCK),
						   0, 0, &client->ioctl_mutex);
		अगर (err < 0)
			अवरोध;
		handled++;

	__skip_event:
		/* Update poपूर्णांकers and counts */
		count -= len;
		buf += len;
		written += len;

		/* let's have a coffee अवरोध अगर too many events are queued */
		अगर (++handled >= 200) अणु
			mutex_unlock(&client->ioctl_mutex);
			जाओ repeat;
		पूर्ण
	पूर्ण

 out:
	mutex_unlock(&client->ioctl_mutex);
	वापस written ? written : err;
पूर्ण


/*
 * handle polling
 */
अटल __poll_t snd_seq_poll(काष्ठा file *file, poll_table * रुको)
अणु
	काष्ठा snd_seq_client *client = file->निजी_data;
	__poll_t mask = 0;

	/* check client काष्ठाures are in place */
	अगर (snd_BUG_ON(!client))
		वापस EPOLLERR;

	अगर ((snd_seq_file_flags(file) & SNDRV_SEQ_LFLG_INPUT) &&
	    client->data.user.fअगरo) अणु

		/* check अगर data is available in the outqueue */
		अगर (snd_seq_fअगरo_poll_रुको(client->data.user.fअगरo, file, रुको))
			mask |= EPOLLIN | EPOLLRDNORM;
	पूर्ण

	अगर (snd_seq_file_flags(file) & SNDRV_SEQ_LFLG_OUTPUT) अणु

		/* check अगर data is available in the pool */
		अगर (!snd_seq_ग_लिखो_pool_allocated(client) ||
		    snd_seq_pool_poll_रुको(client->pool, file, रुको))
			mask |= EPOLLOUT | EPOLLWRNORM;
	पूर्ण

	वापस mask;
पूर्ण


/*-----------------------------------------------------*/

अटल पूर्णांक snd_seq_ioctl_pversion(काष्ठा snd_seq_client *client, व्योम *arg)
अणु
	पूर्णांक *pversion = arg;

	*pversion = SNDRV_SEQ_VERSION;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_seq_ioctl_client_id(काष्ठा snd_seq_client *client, व्योम *arg)
अणु
	पूर्णांक *client_id = arg;

	*client_id = client->number;
	वापस 0;
पूर्ण

/* SYSTEM_INFO ioctl() */
अटल पूर्णांक snd_seq_ioctl_प्रणाली_info(काष्ठा snd_seq_client *client, व्योम *arg)
अणु
	काष्ठा snd_seq_प्रणाली_info *info = arg;

	स_रखो(info, 0, माप(*info));
	/* fill the info fields */
	info->queues = SNDRV_SEQ_MAX_QUEUES;
	info->clients = SNDRV_SEQ_MAX_CLIENTS;
	info->ports = SNDRV_SEQ_MAX_PORTS;
	info->channels = 256;	/* fixed limit */
	info->cur_clients = client_usage.cur;
	info->cur_queues = snd_seq_queue_get_cur_queues();

	वापस 0;
पूर्ण


/* RUNNING_MODE ioctl() */
अटल पूर्णांक snd_seq_ioctl_running_mode(काष्ठा snd_seq_client *client, व्योम  *arg)
अणु
	काष्ठा snd_seq_running_info *info = arg;
	काष्ठा snd_seq_client *cptr;
	पूर्णांक err = 0;

	/* requested client number */
	cptr = snd_seq_client_use_ptr(info->client);
	अगर (cptr == शून्य)
		वापस -ENOENT;		/* करोn't change !!! */

#अगर_घोषित SNDRV_BIG_ENDIAN
	अगर (!info->big_endian) अणु
		err = -EINVAL;
		जाओ __err;
	पूर्ण
#अन्यथा
	अगर (info->big_endian) अणु
		err = -EINVAL;
		जाओ __err;
	पूर्ण

#पूर्ण_अगर
	अगर (info->cpu_mode > माप(दीर्घ)) अणु
		err = -EINVAL;
		जाओ __err;
	पूर्ण
	cptr->convert32 = (info->cpu_mode < माप(दीर्घ));
 __err:
	snd_seq_client_unlock(cptr);
	वापस err;
पूर्ण

/* CLIENT_INFO ioctl() */
अटल व्योम get_client_info(काष्ठा snd_seq_client *cptr,
			    काष्ठा snd_seq_client_info *info)
अणु
	info->client = cptr->number;

	/* fill the info fields */
	info->type = cptr->type;
	म_नकल(info->name, cptr->name);
	info->filter = cptr->filter;
	info->event_lost = cptr->event_lost;
	स_नकल(info->event_filter, cptr->event_filter, 32);
	info->num_ports = cptr->num_ports;

	अगर (cptr->type == USER_CLIENT)
		info->pid = pid_vnr(cptr->data.user.owner);
	अन्यथा
		info->pid = -1;

	अगर (cptr->type == KERNEL_CLIENT)
		info->card = cptr->data.kernel.card ? cptr->data.kernel.card->number : -1;
	अन्यथा
		info->card = -1;

	स_रखो(info->reserved, 0, माप(info->reserved));
पूर्ण

अटल पूर्णांक snd_seq_ioctl_get_client_info(काष्ठा snd_seq_client *client,
					 व्योम *arg)
अणु
	काष्ठा snd_seq_client_info *client_info = arg;
	काष्ठा snd_seq_client *cptr;

	/* requested client number */
	cptr = snd_seq_client_use_ptr(client_info->client);
	अगर (cptr == शून्य)
		वापस -ENOENT;		/* करोn't change !!! */

	get_client_info(cptr, client_info);
	snd_seq_client_unlock(cptr);

	वापस 0;
पूर्ण


/* CLIENT_INFO ioctl() */
अटल पूर्णांक snd_seq_ioctl_set_client_info(काष्ठा snd_seq_client *client,
					 व्योम *arg)
अणु
	काष्ठा snd_seq_client_info *client_info = arg;

	/* it is not allowed to set the info fields क्रम an another client */
	अगर (client->number != client_info->client)
		वापस -EPERM;
	/* also client type must be set now */
	अगर (client->type != client_info->type)
		वापस -EINVAL;

	/* fill the info fields */
	अगर (client_info->name[0])
		strscpy(client->name, client_info->name, माप(client->name));

	client->filter = client_info->filter;
	client->event_lost = client_info->event_lost;
	स_नकल(client->event_filter, client_info->event_filter, 32);

	वापस 0;
पूर्ण


/* 
 * CREATE PORT ioctl() 
 */
अटल पूर्णांक snd_seq_ioctl_create_port(काष्ठा snd_seq_client *client, व्योम *arg)
अणु
	काष्ठा snd_seq_port_info *info = arg;
	काष्ठा snd_seq_client_port *port;
	काष्ठा snd_seq_port_callback *callback;
	पूर्णांक port_idx;

	/* it is not allowed to create the port क्रम an another client */
	अगर (info->addr.client != client->number)
		वापस -EPERM;

	port = snd_seq_create_port(client, (info->flags & SNDRV_SEQ_PORT_FLG_GIVEN_PORT) ? info->addr.port : -1);
	अगर (port == शून्य)
		वापस -ENOMEM;

	अगर (client->type == USER_CLIENT && info->kernel) अणु
		port_idx = port->addr.port;
		snd_seq_port_unlock(port);
		snd_seq_delete_port(client, port_idx);
		वापस -EINVAL;
	पूर्ण
	अगर (client->type == KERNEL_CLIENT) अणु
		अगर ((callback = info->kernel) != शून्य) अणु
			अगर (callback->owner)
				port->owner = callback->owner;
			port->निजी_data = callback->निजी_data;
			port->निजी_मुक्त = callback->निजी_मुक्त;
			port->event_input = callback->event_input;
			port->c_src.खोलो = callback->subscribe;
			port->c_src.बंद = callback->unsubscribe;
			port->c_dest.खोलो = callback->use;
			port->c_dest.बंद = callback->unuse;
		पूर्ण
	पूर्ण

	info->addr = port->addr;

	snd_seq_set_port_info(port, info);
	snd_seq_प्रणाली_client_ev_port_start(port->addr.client, port->addr.port);
	snd_seq_port_unlock(port);

	वापस 0;
पूर्ण

/* 
 * DELETE PORT ioctl() 
 */
अटल पूर्णांक snd_seq_ioctl_delete_port(काष्ठा snd_seq_client *client, व्योम *arg)
अणु
	काष्ठा snd_seq_port_info *info = arg;
	पूर्णांक err;

	/* it is not allowed to हटाओ the port क्रम an another client */
	अगर (info->addr.client != client->number)
		वापस -EPERM;

	err = snd_seq_delete_port(client, info->addr.port);
	अगर (err >= 0)
		snd_seq_प्रणाली_client_ev_port_निकास(client->number, info->addr.port);
	वापस err;
पूर्ण


/* 
 * GET_PORT_INFO ioctl() (on any client) 
 */
अटल पूर्णांक snd_seq_ioctl_get_port_info(काष्ठा snd_seq_client *client, व्योम *arg)
अणु
	काष्ठा snd_seq_port_info *info = arg;
	काष्ठा snd_seq_client *cptr;
	काष्ठा snd_seq_client_port *port;

	cptr = snd_seq_client_use_ptr(info->addr.client);
	अगर (cptr == शून्य)
		वापस -ENXIO;

	port = snd_seq_port_use_ptr(cptr, info->addr.port);
	अगर (port == शून्य) अणु
		snd_seq_client_unlock(cptr);
		वापस -ENOENT;			/* करोn't change */
	पूर्ण

	/* get port info */
	snd_seq_get_port_info(port, info);
	snd_seq_port_unlock(port);
	snd_seq_client_unlock(cptr);

	वापस 0;
पूर्ण


/* 
 * SET_PORT_INFO ioctl() (only ports on this/own client) 
 */
अटल पूर्णांक snd_seq_ioctl_set_port_info(काष्ठा snd_seq_client *client, व्योम *arg)
अणु
	काष्ठा snd_seq_port_info *info = arg;
	काष्ठा snd_seq_client_port *port;

	अगर (info->addr.client != client->number) /* only set our own ports ! */
		वापस -EPERM;
	port = snd_seq_port_use_ptr(client, info->addr.port);
	अगर (port) अणु
		snd_seq_set_port_info(port, info);
		snd_seq_port_unlock(port);
	पूर्ण
	वापस 0;
पूर्ण


/*
 * port subscription (connection)
 */
#घोषणा PERM_RD		(SNDRV_SEQ_PORT_CAP_READ|SNDRV_SEQ_PORT_CAP_SUBS_READ)
#घोषणा PERM_WR		(SNDRV_SEQ_PORT_CAP_WRITE|SNDRV_SEQ_PORT_CAP_SUBS_WRITE)

अटल पूर्णांक check_subscription_permission(काष्ठा snd_seq_client *client,
					 काष्ठा snd_seq_client_port *sport,
					 काष्ठा snd_seq_client_port *dport,
					 काष्ठा snd_seq_port_subscribe *subs)
अणु
	अगर (client->number != subs->sender.client &&
	    client->number != subs->dest.client) अणु
		/* connection by third client - check export permission */
		अगर (check_port_perm(sport, SNDRV_SEQ_PORT_CAP_NO_EXPORT))
			वापस -EPERM;
		अगर (check_port_perm(dport, SNDRV_SEQ_PORT_CAP_NO_EXPORT))
			वापस -EPERM;
	पूर्ण

	/* check पढ़ो permission */
	/* अगर sender or receiver is the subscribing client itself,
	 * no permission check is necessary
	 */
	अगर (client->number != subs->sender.client) अणु
		अगर (! check_port_perm(sport, PERM_RD))
			वापस -EPERM;
	पूर्ण
	/* check ग_लिखो permission */
	अगर (client->number != subs->dest.client) अणु
		अगर (! check_port_perm(dport, PERM_WR))
			वापस -EPERM;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * send an subscription notअगरy event to user client:
 * client must be user client.
 */
पूर्णांक snd_seq_client_notअगरy_subscription(पूर्णांक client, पूर्णांक port,
				       काष्ठा snd_seq_port_subscribe *info,
				       पूर्णांक evtype)
अणु
	काष्ठा snd_seq_event event;

	स_रखो(&event, 0, माप(event));
	event.type = evtype;
	event.data.connect.dest = info->dest;
	event.data.connect.sender = info->sender;

	वापस snd_seq_प्रणाली_notअगरy(client, port, &event);  /* non-atomic */
पूर्ण


/* 
 * add to port's subscription list IOCTL पूर्णांकerface 
 */
अटल पूर्णांक snd_seq_ioctl_subscribe_port(काष्ठा snd_seq_client *client,
					व्योम *arg)
अणु
	काष्ठा snd_seq_port_subscribe *subs = arg;
	पूर्णांक result = -EINVAL;
	काष्ठा snd_seq_client *receiver = शून्य, *sender = शून्य;
	काष्ठा snd_seq_client_port *sport = शून्य, *dport = शून्य;

	अगर ((receiver = snd_seq_client_use_ptr(subs->dest.client)) == शून्य)
		जाओ __end;
	अगर ((sender = snd_seq_client_use_ptr(subs->sender.client)) == शून्य)
		जाओ __end;
	अगर ((sport = snd_seq_port_use_ptr(sender, subs->sender.port)) == शून्य)
		जाओ __end;
	अगर ((dport = snd_seq_port_use_ptr(receiver, subs->dest.port)) == शून्य)
		जाओ __end;

	result = check_subscription_permission(client, sport, dport, subs);
	अगर (result < 0)
		जाओ __end;

	/* connect them */
	result = snd_seq_port_connect(client, sender, sport, receiver, dport, subs);
	अगर (! result) /* broadcast announce */
		snd_seq_client_notअगरy_subscription(SNDRV_SEQ_ADDRESS_SUBSCRIBERS, 0,
						   subs, SNDRV_SEQ_EVENT_PORT_SUBSCRIBED);
      __end:
      	अगर (sport)
		snd_seq_port_unlock(sport);
	अगर (dport)
		snd_seq_port_unlock(dport);
	अगर (sender)
		snd_seq_client_unlock(sender);
	अगर (receiver)
		snd_seq_client_unlock(receiver);
	वापस result;
पूर्ण


/* 
 * हटाओ from port's subscription list 
 */
अटल पूर्णांक snd_seq_ioctl_unsubscribe_port(काष्ठा snd_seq_client *client,
					  व्योम *arg)
अणु
	काष्ठा snd_seq_port_subscribe *subs = arg;
	पूर्णांक result = -ENXIO;
	काष्ठा snd_seq_client *receiver = शून्य, *sender = शून्य;
	काष्ठा snd_seq_client_port *sport = शून्य, *dport = शून्य;

	अगर ((receiver = snd_seq_client_use_ptr(subs->dest.client)) == शून्य)
		जाओ __end;
	अगर ((sender = snd_seq_client_use_ptr(subs->sender.client)) == शून्य)
		जाओ __end;
	अगर ((sport = snd_seq_port_use_ptr(sender, subs->sender.port)) == शून्य)
		जाओ __end;
	अगर ((dport = snd_seq_port_use_ptr(receiver, subs->dest.port)) == शून्य)
		जाओ __end;

	result = check_subscription_permission(client, sport, dport, subs);
	अगर (result < 0)
		जाओ __end;

	result = snd_seq_port_disconnect(client, sender, sport, receiver, dport, subs);
	अगर (! result) /* broadcast announce */
		snd_seq_client_notअगरy_subscription(SNDRV_SEQ_ADDRESS_SUBSCRIBERS, 0,
						   subs, SNDRV_SEQ_EVENT_PORT_UNSUBSCRIBED);
      __end:
      	अगर (sport)
		snd_seq_port_unlock(sport);
	अगर (dport)
		snd_seq_port_unlock(dport);
	अगर (sender)
		snd_seq_client_unlock(sender);
	अगर (receiver)
		snd_seq_client_unlock(receiver);
	वापस result;
पूर्ण


/* CREATE_QUEUE ioctl() */
अटल पूर्णांक snd_seq_ioctl_create_queue(काष्ठा snd_seq_client *client, व्योम *arg)
अणु
	काष्ठा snd_seq_queue_info *info = arg;
	काष्ठा snd_seq_queue *q;

	q = snd_seq_queue_alloc(client->number, info->locked, info->flags);
	अगर (IS_ERR(q))
		वापस PTR_ERR(q);

	info->queue = q->queue;
	info->locked = q->locked;
	info->owner = q->owner;

	/* set queue name */
	अगर (!info->name[0])
		snम_लिखो(info->name, माप(info->name), "Queue-%d", q->queue);
	strscpy(q->name, info->name, माप(q->name));
	snd_use_lock_मुक्त(&q->use_lock);

	वापस 0;
पूर्ण

/* DELETE_QUEUE ioctl() */
अटल पूर्णांक snd_seq_ioctl_delete_queue(काष्ठा snd_seq_client *client, व्योम *arg)
अणु
	काष्ठा snd_seq_queue_info *info = arg;

	वापस snd_seq_queue_delete(client->number, info->queue);
पूर्ण

/* GET_QUEUE_INFO ioctl() */
अटल पूर्णांक snd_seq_ioctl_get_queue_info(काष्ठा snd_seq_client *client,
					व्योम *arg)
अणु
	काष्ठा snd_seq_queue_info *info = arg;
	काष्ठा snd_seq_queue *q;

	q = queueptr(info->queue);
	अगर (q == शून्य)
		वापस -EINVAL;

	स_रखो(info, 0, माप(*info));
	info->queue = q->queue;
	info->owner = q->owner;
	info->locked = q->locked;
	strscpy(info->name, q->name, माप(info->name));
	queueमुक्त(q);

	वापस 0;
पूर्ण

/* SET_QUEUE_INFO ioctl() */
अटल पूर्णांक snd_seq_ioctl_set_queue_info(काष्ठा snd_seq_client *client,
					व्योम *arg)
अणु
	काष्ठा snd_seq_queue_info *info = arg;
	काष्ठा snd_seq_queue *q;

	अगर (info->owner != client->number)
		वापस -EINVAL;

	/* change owner/locked permission */
	अगर (snd_seq_queue_check_access(info->queue, client->number)) अणु
		अगर (snd_seq_queue_set_owner(info->queue, client->number, info->locked) < 0)
			वापस -EPERM;
		अगर (info->locked)
			snd_seq_queue_use(info->queue, client->number, 1);
	पूर्ण अन्यथा अणु
		वापस -EPERM;
	पूर्ण	

	q = queueptr(info->queue);
	अगर (! q)
		वापस -EINVAL;
	अगर (q->owner != client->number) अणु
		queueमुक्त(q);
		वापस -EPERM;
	पूर्ण
	strscpy(q->name, info->name, माप(q->name));
	queueमुक्त(q);

	वापस 0;
पूर्ण

/* GET_NAMED_QUEUE ioctl() */
अटल पूर्णांक snd_seq_ioctl_get_named_queue(काष्ठा snd_seq_client *client,
					 व्योम *arg)
अणु
	काष्ठा snd_seq_queue_info *info = arg;
	काष्ठा snd_seq_queue *q;

	q = snd_seq_queue_find_name(info->name);
	अगर (q == शून्य)
		वापस -EINVAL;
	info->queue = q->queue;
	info->owner = q->owner;
	info->locked = q->locked;
	queueमुक्त(q);

	वापस 0;
पूर्ण

/* GET_QUEUE_STATUS ioctl() */
अटल पूर्णांक snd_seq_ioctl_get_queue_status(काष्ठा snd_seq_client *client,
					  व्योम *arg)
अणु
	काष्ठा snd_seq_queue_status *status = arg;
	काष्ठा snd_seq_queue *queue;
	काष्ठा snd_seq_समयr *पंचांगr;

	queue = queueptr(status->queue);
	अगर (queue == शून्य)
		वापस -EINVAL;
	स_रखो(status, 0, माप(*status));
	status->queue = queue->queue;
	
	पंचांगr = queue->समयr;
	status->events = queue->tickq->cells + queue->समयq->cells;

	status->समय = snd_seq_समयr_get_cur_समय(पंचांगr, true);
	status->tick = snd_seq_समयr_get_cur_tick(पंचांगr);

	status->running = पंचांगr->running;

	status->flags = queue->flags;
	queueमुक्त(queue);

	वापस 0;
पूर्ण


/* GET_QUEUE_TEMPO ioctl() */
अटल पूर्णांक snd_seq_ioctl_get_queue_tempo(काष्ठा snd_seq_client *client,
					 व्योम *arg)
अणु
	काष्ठा snd_seq_queue_tempo *tempo = arg;
	काष्ठा snd_seq_queue *queue;
	काष्ठा snd_seq_समयr *पंचांगr;

	queue = queueptr(tempo->queue);
	अगर (queue == शून्य)
		वापस -EINVAL;
	स_रखो(tempo, 0, माप(*tempo));
	tempo->queue = queue->queue;
	
	पंचांगr = queue->समयr;

	tempo->tempo = पंचांगr->tempo;
	tempo->ppq = पंचांगr->ppq;
	tempo->skew_value = पंचांगr->skew;
	tempo->skew_base = पंचांगr->skew_base;
	queueमुक्त(queue);

	वापस 0;
पूर्ण


/* SET_QUEUE_TEMPO ioctl() */
पूर्णांक snd_seq_set_queue_tempo(पूर्णांक client, काष्ठा snd_seq_queue_tempo *tempo)
अणु
	अगर (!snd_seq_queue_check_access(tempo->queue, client))
		वापस -EPERM;
	वापस snd_seq_queue_समयr_set_tempo(tempo->queue, client, tempo);
पूर्ण
EXPORT_SYMBOL(snd_seq_set_queue_tempo);

अटल पूर्णांक snd_seq_ioctl_set_queue_tempo(काष्ठा snd_seq_client *client,
					 व्योम *arg)
अणु
	काष्ठा snd_seq_queue_tempo *tempo = arg;
	पूर्णांक result;

	result = snd_seq_set_queue_tempo(client->number, tempo);
	वापस result < 0 ? result : 0;
पूर्ण


/* GET_QUEUE_TIMER ioctl() */
अटल पूर्णांक snd_seq_ioctl_get_queue_समयr(काष्ठा snd_seq_client *client,
					 व्योम *arg)
अणु
	काष्ठा snd_seq_queue_समयr *समयr = arg;
	काष्ठा snd_seq_queue *queue;
	काष्ठा snd_seq_समयr *पंचांगr;

	queue = queueptr(समयr->queue);
	अगर (queue == शून्य)
		वापस -EINVAL;

	mutex_lock(&queue->समयr_mutex);
	पंचांगr = queue->समयr;
	स_रखो(समयr, 0, माप(*समयr));
	समयr->queue = queue->queue;

	समयr->type = पंचांगr->type;
	अगर (पंचांगr->type == SNDRV_SEQ_TIMER_ALSA) अणु
		समयr->u.alsa.id = पंचांगr->alsa_id;
		समयr->u.alsa.resolution = पंचांगr->preferred_resolution;
	पूर्ण
	mutex_unlock(&queue->समयr_mutex);
	queueमुक्त(queue);
	
	वापस 0;
पूर्ण


/* SET_QUEUE_TIMER ioctl() */
अटल पूर्णांक snd_seq_ioctl_set_queue_समयr(काष्ठा snd_seq_client *client,
					 व्योम *arg)
अणु
	काष्ठा snd_seq_queue_समयr *समयr = arg;
	पूर्णांक result = 0;

	अगर (समयr->type != SNDRV_SEQ_TIMER_ALSA)
		वापस -EINVAL;

	अगर (snd_seq_queue_check_access(समयr->queue, client->number)) अणु
		काष्ठा snd_seq_queue *q;
		काष्ठा snd_seq_समयr *पंचांगr;

		q = queueptr(समयr->queue);
		अगर (q == शून्य)
			वापस -ENXIO;
		mutex_lock(&q->समयr_mutex);
		पंचांगr = q->समयr;
		snd_seq_queue_समयr_बंद(समयr->queue);
		पंचांगr->type = समयr->type;
		अगर (पंचांगr->type == SNDRV_SEQ_TIMER_ALSA) अणु
			पंचांगr->alsa_id = समयr->u.alsa.id;
			पंचांगr->preferred_resolution = समयr->u.alsa.resolution;
		पूर्ण
		result = snd_seq_queue_समयr_खोलो(समयr->queue);
		mutex_unlock(&q->समयr_mutex);
		queueमुक्त(q);
	पूर्ण अन्यथा अणु
		वापस -EPERM;
	पूर्ण	

	वापस result;
पूर्ण


/* GET_QUEUE_CLIENT ioctl() */
अटल पूर्णांक snd_seq_ioctl_get_queue_client(काष्ठा snd_seq_client *client,
					  व्योम *arg)
अणु
	काष्ठा snd_seq_queue_client *info = arg;
	पूर्णांक used;

	used = snd_seq_queue_is_used(info->queue, client->number);
	अगर (used < 0)
		वापस -EINVAL;
	info->used = used;
	info->client = client->number;

	वापस 0;
पूर्ण


/* SET_QUEUE_CLIENT ioctl() */
अटल पूर्णांक snd_seq_ioctl_set_queue_client(काष्ठा snd_seq_client *client,
					  व्योम *arg)
अणु
	काष्ठा snd_seq_queue_client *info = arg;
	पूर्णांक err;

	अगर (info->used >= 0) अणु
		err = snd_seq_queue_use(info->queue, client->number, info->used);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस snd_seq_ioctl_get_queue_client(client, arg);
पूर्ण


/* GET_CLIENT_POOL ioctl() */
अटल पूर्णांक snd_seq_ioctl_get_client_pool(काष्ठा snd_seq_client *client,
					 व्योम *arg)
अणु
	काष्ठा snd_seq_client_pool *info = arg;
	काष्ठा snd_seq_client *cptr;

	cptr = snd_seq_client_use_ptr(info->client);
	अगर (cptr == शून्य)
		वापस -ENOENT;
	स_रखो(info, 0, माप(*info));
	info->client = cptr->number;
	info->output_pool = cptr->pool->size;
	info->output_room = cptr->pool->room;
	info->output_मुक्त = info->output_pool;
	info->output_मुक्त = snd_seq_unused_cells(cptr->pool);
	अगर (cptr->type == USER_CLIENT) अणु
		info->input_pool = cptr->data.user.fअगरo_pool_size;
		info->input_मुक्त = info->input_pool;
		info->input_मुक्त = snd_seq_fअगरo_unused_cells(cptr->data.user.fअगरo);
	पूर्ण अन्यथा अणु
		info->input_pool = 0;
		info->input_मुक्त = 0;
	पूर्ण
	snd_seq_client_unlock(cptr);
	
	वापस 0;
पूर्ण

/* SET_CLIENT_POOL ioctl() */
अटल पूर्णांक snd_seq_ioctl_set_client_pool(काष्ठा snd_seq_client *client,
					 व्योम *arg)
अणु
	काष्ठा snd_seq_client_pool *info = arg;
	पूर्णांक rc;

	अगर (client->number != info->client)
		वापस -EINVAL; /* can't change other clients */

	अगर (info->output_pool >= 1 && info->output_pool <= SNDRV_SEQ_MAX_EVENTS &&
	    (! snd_seq_ग_लिखो_pool_allocated(client) ||
	     info->output_pool != client->pool->size)) अणु
		अगर (snd_seq_ग_लिखो_pool_allocated(client)) अणु
			/* is the pool in use? */
			अगर (atomic_पढ़ो(&client->pool->counter))
				वापस -EBUSY;
			/* हटाओ all existing cells */
			snd_seq_pool_mark_closing(client->pool);
			snd_seq_pool_करोne(client->pool);
		पूर्ण
		client->pool->size = info->output_pool;
		rc = snd_seq_pool_init(client->pool);
		अगर (rc < 0)
			वापस rc;
	पूर्ण
	अगर (client->type == USER_CLIENT && client->data.user.fअगरo != शून्य &&
	    info->input_pool >= 1 &&
	    info->input_pool <= SNDRV_SEQ_MAX_CLIENT_EVENTS &&
	    info->input_pool != client->data.user.fअगरo_pool_size) अणु
		/* change pool size */
		rc = snd_seq_fअगरo_resize(client->data.user.fअगरo, info->input_pool);
		अगर (rc < 0)
			वापस rc;
		client->data.user.fअगरo_pool_size = info->input_pool;
	पूर्ण
	अगर (info->output_room >= 1 &&
	    info->output_room <= client->pool->size) अणु
		client->pool->room  = info->output_room;
	पूर्ण

	वापस snd_seq_ioctl_get_client_pool(client, arg);
पूर्ण


/* REMOVE_EVENTS ioctl() */
अटल पूर्णांक snd_seq_ioctl_हटाओ_events(काष्ठा snd_seq_client *client,
				       व्योम *arg)
अणु
	काष्ठा snd_seq_हटाओ_events *info = arg;

	/*
	 * Input mostly not implemented XXX.
	 */
	अगर (info->हटाओ_mode & SNDRV_SEQ_REMOVE_INPUT) अणु
		/*
		 * No restrictions so क्रम a user client we can clear
		 * the whole fअगरo
		 */
		अगर (client->type == USER_CLIENT && client->data.user.fअगरo)
			snd_seq_fअगरo_clear(client->data.user.fअगरo);
	पूर्ण

	अगर (info->हटाओ_mode & SNDRV_SEQ_REMOVE_OUTPUT)
		snd_seq_queue_हटाओ_cells(client->number, info);

	वापस 0;
पूर्ण


/*
 * get subscription info
 */
अटल पूर्णांक snd_seq_ioctl_get_subscription(काष्ठा snd_seq_client *client,
					  व्योम *arg)
अणु
	काष्ठा snd_seq_port_subscribe *subs = arg;
	पूर्णांक result;
	काष्ठा snd_seq_client *sender = शून्य;
	काष्ठा snd_seq_client_port *sport = शून्य;

	result = -EINVAL;
	अगर ((sender = snd_seq_client_use_ptr(subs->sender.client)) == शून्य)
		जाओ __end;
	अगर ((sport = snd_seq_port_use_ptr(sender, subs->sender.port)) == शून्य)
		जाओ __end;
	result = snd_seq_port_get_subscription(&sport->c_src, &subs->dest,
					       subs);
      __end:
      	अगर (sport)
		snd_seq_port_unlock(sport);
	अगर (sender)
		snd_seq_client_unlock(sender);

	वापस result;
पूर्ण


/*
 * get subscription info - check only its presence
 */
अटल पूर्णांक snd_seq_ioctl_query_subs(काष्ठा snd_seq_client *client, व्योम *arg)
अणु
	काष्ठा snd_seq_query_subs *subs = arg;
	पूर्णांक result = -ENXIO;
	काष्ठा snd_seq_client *cptr = शून्य;
	काष्ठा snd_seq_client_port *port = शून्य;
	काष्ठा snd_seq_port_subs_info *group;
	काष्ठा list_head *p;
	पूर्णांक i;

	अगर ((cptr = snd_seq_client_use_ptr(subs->root.client)) == शून्य)
		जाओ __end;
	अगर ((port = snd_seq_port_use_ptr(cptr, subs->root.port)) == शून्य)
		जाओ __end;

	चयन (subs->type) अणु
	हाल SNDRV_SEQ_QUERY_SUBS_READ:
		group = &port->c_src;
		अवरोध;
	हाल SNDRV_SEQ_QUERY_SUBS_WRITE:
		group = &port->c_dest;
		अवरोध;
	शेष:
		जाओ __end;
	पूर्ण

	करोwn_पढ़ो(&group->list_mutex);
	/* search क्रम the subscriber */
	subs->num_subs = group->count;
	i = 0;
	result = -ENOENT;
	list_क्रम_each(p, &group->list_head) अणु
		अगर (i++ == subs->index) अणु
			/* found! */
			काष्ठा snd_seq_subscribers *s;
			अगर (subs->type == SNDRV_SEQ_QUERY_SUBS_READ) अणु
				s = list_entry(p, काष्ठा snd_seq_subscribers, src_list);
				subs->addr = s->info.dest;
			पूर्ण अन्यथा अणु
				s = list_entry(p, काष्ठा snd_seq_subscribers, dest_list);
				subs->addr = s->info.sender;
			पूर्ण
			subs->flags = s->info.flags;
			subs->queue = s->info.queue;
			result = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	up_पढ़ो(&group->list_mutex);

      __end:
   	अगर (port)
		snd_seq_port_unlock(port);
	अगर (cptr)
		snd_seq_client_unlock(cptr);

	वापस result;
पूर्ण


/*
 * query next client
 */
अटल पूर्णांक snd_seq_ioctl_query_next_client(काष्ठा snd_seq_client *client,
					   व्योम *arg)
अणु
	काष्ठा snd_seq_client_info *info = arg;
	काष्ठा snd_seq_client *cptr = शून्य;

	/* search क्रम next client */
	अगर (info->client < पूर्णांक_उच्च)
		info->client++;
	अगर (info->client < 0)
		info->client = 0;
	क्रम (; info->client < SNDRV_SEQ_MAX_CLIENTS; info->client++) अणु
		cptr = snd_seq_client_use_ptr(info->client);
		अगर (cptr)
			अवरोध; /* found */
	पूर्ण
	अगर (cptr == शून्य)
		वापस -ENOENT;

	get_client_info(cptr, info);
	snd_seq_client_unlock(cptr);

	वापस 0;
पूर्ण

/* 
 * query next port
 */
अटल पूर्णांक snd_seq_ioctl_query_next_port(काष्ठा snd_seq_client *client,
					 व्योम *arg)
अणु
	काष्ठा snd_seq_port_info *info = arg;
	काष्ठा snd_seq_client *cptr;
	काष्ठा snd_seq_client_port *port = शून्य;

	cptr = snd_seq_client_use_ptr(info->addr.client);
	अगर (cptr == शून्य)
		वापस -ENXIO;

	/* search क्रम next port */
	info->addr.port++;
	port = snd_seq_port_query_nearest(cptr, info);
	अगर (port == शून्य) अणु
		snd_seq_client_unlock(cptr);
		वापस -ENOENT;
	पूर्ण

	/* get port info */
	info->addr = port->addr;
	snd_seq_get_port_info(port, info);
	snd_seq_port_unlock(port);
	snd_seq_client_unlock(cptr);

	वापस 0;
पूर्ण

/* -------------------------------------------------------- */

अटल स्थिर काष्ठा ioctl_handler अणु
	अचिन्हित पूर्णांक cmd;
	पूर्णांक (*func)(काष्ठा snd_seq_client *client, व्योम *arg);
पूर्ण ioctl_handlers[] = अणु
	अणु SNDRV_SEQ_IOCTL_PVERSION, snd_seq_ioctl_pversion पूर्ण,
	अणु SNDRV_SEQ_IOCTL_CLIENT_ID, snd_seq_ioctl_client_id पूर्ण,
	अणु SNDRV_SEQ_IOCTL_SYSTEM_INFO, snd_seq_ioctl_प्रणाली_info पूर्ण,
	अणु SNDRV_SEQ_IOCTL_RUNNING_MODE, snd_seq_ioctl_running_mode पूर्ण,
	अणु SNDRV_SEQ_IOCTL_GET_CLIENT_INFO, snd_seq_ioctl_get_client_info पूर्ण,
	अणु SNDRV_SEQ_IOCTL_SET_CLIENT_INFO, snd_seq_ioctl_set_client_info पूर्ण,
	अणु SNDRV_SEQ_IOCTL_CREATE_PORT, snd_seq_ioctl_create_port पूर्ण,
	अणु SNDRV_SEQ_IOCTL_DELETE_PORT, snd_seq_ioctl_delete_port पूर्ण,
	अणु SNDRV_SEQ_IOCTL_GET_PORT_INFO, snd_seq_ioctl_get_port_info पूर्ण,
	अणु SNDRV_SEQ_IOCTL_SET_PORT_INFO, snd_seq_ioctl_set_port_info पूर्ण,
	अणु SNDRV_SEQ_IOCTL_SUBSCRIBE_PORT, snd_seq_ioctl_subscribe_port पूर्ण,
	अणु SNDRV_SEQ_IOCTL_UNSUBSCRIBE_PORT, snd_seq_ioctl_unsubscribe_port पूर्ण,
	अणु SNDRV_SEQ_IOCTL_CREATE_QUEUE, snd_seq_ioctl_create_queue पूर्ण,
	अणु SNDRV_SEQ_IOCTL_DELETE_QUEUE, snd_seq_ioctl_delete_queue पूर्ण,
	अणु SNDRV_SEQ_IOCTL_GET_QUEUE_INFO, snd_seq_ioctl_get_queue_info पूर्ण,
	अणु SNDRV_SEQ_IOCTL_SET_QUEUE_INFO, snd_seq_ioctl_set_queue_info पूर्ण,
	अणु SNDRV_SEQ_IOCTL_GET_NAMED_QUEUE, snd_seq_ioctl_get_named_queue पूर्ण,
	अणु SNDRV_SEQ_IOCTL_GET_QUEUE_STATUS, snd_seq_ioctl_get_queue_status पूर्ण,
	अणु SNDRV_SEQ_IOCTL_GET_QUEUE_TEMPO, snd_seq_ioctl_get_queue_tempo पूर्ण,
	अणु SNDRV_SEQ_IOCTL_SET_QUEUE_TEMPO, snd_seq_ioctl_set_queue_tempo पूर्ण,
	अणु SNDRV_SEQ_IOCTL_GET_QUEUE_TIMER, snd_seq_ioctl_get_queue_समयr पूर्ण,
	अणु SNDRV_SEQ_IOCTL_SET_QUEUE_TIMER, snd_seq_ioctl_set_queue_समयr पूर्ण,
	अणु SNDRV_SEQ_IOCTL_GET_QUEUE_CLIENT, snd_seq_ioctl_get_queue_client पूर्ण,
	अणु SNDRV_SEQ_IOCTL_SET_QUEUE_CLIENT, snd_seq_ioctl_set_queue_client पूर्ण,
	अणु SNDRV_SEQ_IOCTL_GET_CLIENT_POOL, snd_seq_ioctl_get_client_pool पूर्ण,
	अणु SNDRV_SEQ_IOCTL_SET_CLIENT_POOL, snd_seq_ioctl_set_client_pool पूर्ण,
	अणु SNDRV_SEQ_IOCTL_GET_SUBSCRIPTION, snd_seq_ioctl_get_subscription पूर्ण,
	अणु SNDRV_SEQ_IOCTL_QUERY_NEXT_CLIENT, snd_seq_ioctl_query_next_client पूर्ण,
	अणु SNDRV_SEQ_IOCTL_QUERY_NEXT_PORT, snd_seq_ioctl_query_next_port पूर्ण,
	अणु SNDRV_SEQ_IOCTL_REMOVE_EVENTS, snd_seq_ioctl_हटाओ_events पूर्ण,
	अणु SNDRV_SEQ_IOCTL_QUERY_SUBS, snd_seq_ioctl_query_subs पूर्ण,
	अणु 0, शून्य पूर्ण,
पूर्ण;

अटल दीर्घ snd_seq_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_seq_client *client = file->निजी_data;
	/* To use kernel stack क्रम ioctl data. */
	जोड़ अणु
		पूर्णांक pversion;
		पूर्णांक client_id;
		काष्ठा snd_seq_प्रणाली_info	प्रणाली_info;
		काष्ठा snd_seq_running_info	running_info;
		काष्ठा snd_seq_client_info	client_info;
		काष्ठा snd_seq_port_info	port_info;
		काष्ठा snd_seq_port_subscribe	port_subscribe;
		काष्ठा snd_seq_queue_info	queue_info;
		काष्ठा snd_seq_queue_status	queue_status;
		काष्ठा snd_seq_queue_tempo	tempo;
		काष्ठा snd_seq_queue_समयr	queue_समयr;
		काष्ठा snd_seq_queue_client	queue_client;
		काष्ठा snd_seq_client_pool	client_pool;
		काष्ठा snd_seq_हटाओ_events	हटाओ_events;
		काष्ठा snd_seq_query_subs	query_subs;
	पूर्ण buf;
	स्थिर काष्ठा ioctl_handler *handler;
	अचिन्हित दीर्घ size;
	पूर्णांक err;

	अगर (snd_BUG_ON(!client))
		वापस -ENXIO;

	क्रम (handler = ioctl_handlers; handler->cmd > 0; ++handler) अणु
		अगर (handler->cmd == cmd)
			अवरोध;
	पूर्ण
	अगर (handler->cmd == 0)
		वापस -ENOTTY;

	स_रखो(&buf, 0, माप(buf));

	/*
	 * All of ioctl commands क्रम ALSA sequencer get an argument of size
	 * within 13 bits. We can safely pick up the size from the command.
	 */
	size = _IOC_SIZE(handler->cmd);
	अगर (handler->cmd & IOC_IN) अणु
		अगर (copy_from_user(&buf, (स्थिर व्योम __user *)arg, size))
			वापस -EFAULT;
	पूर्ण

	mutex_lock(&client->ioctl_mutex);
	err = handler->func(client, &buf);
	mutex_unlock(&client->ioctl_mutex);
	अगर (err >= 0) अणु
		/* Some commands includes a bug in 'dir' field. */
		अगर (handler->cmd == SNDRV_SEQ_IOCTL_SET_QUEUE_CLIENT ||
		    handler->cmd == SNDRV_SEQ_IOCTL_SET_CLIENT_POOL ||
		    (handler->cmd & IOC_OUT))
			अगर (copy_to_user((व्योम __user *)arg, &buf, size))
				वापस -EFAULT;
	पूर्ण

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
#समावेश "seq_compat.c"
#अन्यथा
#घोषणा snd_seq_ioctl_compat	शून्य
#पूर्ण_अगर

/* -------------------------------------------------------- */


/* exported to kernel modules */
पूर्णांक snd_seq_create_kernel_client(काष्ठा snd_card *card, पूर्णांक client_index,
				 स्थिर अक्षर *name_fmt, ...)
अणु
	काष्ठा snd_seq_client *client;
	बहु_सूची args;

	अगर (snd_BUG_ON(in_पूर्णांकerrupt()))
		वापस -EBUSY;

	अगर (card && client_index >= SNDRV_SEQ_CLIENTS_PER_CARD)
		वापस -EINVAL;
	अगर (card == शून्य && client_index >= SNDRV_SEQ_GLOBAL_CLIENTS)
		वापस -EINVAL;

	mutex_lock(&रेजिस्टर_mutex);

	अगर (card) अणु
		client_index += SNDRV_SEQ_GLOBAL_CLIENTS
			+ card->number * SNDRV_SEQ_CLIENTS_PER_CARD;
		अगर (client_index >= SNDRV_SEQ_DYNAMIC_CLIENTS_BEGIN)
			client_index = -1;
	पूर्ण

	/* empty ग_लिखो queue as शेष */
	client = seq_create_client1(client_index, 0);
	अगर (client == शून्य) अणु
		mutex_unlock(&रेजिस्टर_mutex);
		वापस -EBUSY;	/* failure code */
	पूर्ण
	usage_alloc(&client_usage, 1);

	client->accept_input = 1;
	client->accept_output = 1;
	client->data.kernel.card = card;
		
	बहु_शुरू(args, name_fmt);
	vsnम_लिखो(client->name, माप(client->name), name_fmt, args);
	बहु_पूर्ण(args);

	client->type = KERNEL_CLIENT;
	mutex_unlock(&रेजिस्टर_mutex);

	/* make others aware this new client */
	snd_seq_प्रणाली_client_ev_client_start(client->number);
	
	/* वापस client number to caller */
	वापस client->number;
पूर्ण
EXPORT_SYMBOL(snd_seq_create_kernel_client);

/* exported to kernel modules */
पूर्णांक snd_seq_delete_kernel_client(पूर्णांक client)
अणु
	काष्ठा snd_seq_client *ptr;

	अगर (snd_BUG_ON(in_पूर्णांकerrupt()))
		वापस -EBUSY;

	ptr = clientptr(client);
	अगर (ptr == शून्य)
		वापस -EINVAL;

	seq_मुक्त_client(ptr);
	kमुक्त(ptr);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_seq_delete_kernel_client);

/*
 * exported, called by kernel clients to enqueue events (w/o blocking)
 *
 * RETURN VALUE: zero अगर succeed, negative अगर error
 */
पूर्णांक snd_seq_kernel_client_enqueue(पूर्णांक client, काष्ठा snd_seq_event *ev,
				  काष्ठा file *file, bool blocking)
अणु
	काष्ठा snd_seq_client *cptr;
	पूर्णांक result;

	अगर (snd_BUG_ON(!ev))
		वापस -EINVAL;

	अगर (ev->type == SNDRV_SEQ_EVENT_NONE)
		वापस 0; /* ignore this */
	अगर (ev->type == SNDRV_SEQ_EVENT_KERNEL_ERROR)
		वापस -EINVAL; /* quoted events can't be enqueued */

	/* fill in client number */
	ev->source.client = client;

	अगर (check_event_type_and_length(ev))
		वापस -EINVAL;

	cptr = snd_seq_client_use_ptr(client);
	अगर (cptr == शून्य)
		वापस -EINVAL;
	
	अगर (!cptr->accept_output) अणु
		result = -EPERM;
	पूर्ण अन्यथा अणु /* send it */
		mutex_lock(&cptr->ioctl_mutex);
		result = snd_seq_client_enqueue_event(cptr, ev, file, blocking,
						      false, 0,
						      &cptr->ioctl_mutex);
		mutex_unlock(&cptr->ioctl_mutex);
	पूर्ण

	snd_seq_client_unlock(cptr);
	वापस result;
पूर्ण
EXPORT_SYMBOL(snd_seq_kernel_client_enqueue);

/* 
 * exported, called by kernel clients to dispatch events directly to other
 * clients, bypassing the queues.  Event समय-stamp will be updated.
 *
 * RETURN VALUE: negative = delivery failed,
 *		 zero, or positive: the number of delivered events
 */
पूर्णांक snd_seq_kernel_client_dispatch(पूर्णांक client, काष्ठा snd_seq_event * ev,
				   पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा snd_seq_client *cptr;
	पूर्णांक result;

	अगर (snd_BUG_ON(!ev))
		वापस -EINVAL;

	/* fill in client number */
	ev->queue = SNDRV_SEQ_QUEUE_सूचीECT;
	ev->source.client = client;

	अगर (check_event_type_and_length(ev))
		वापस -EINVAL;

	cptr = snd_seq_client_use_ptr(client);
	अगर (cptr == शून्य)
		वापस -EINVAL;

	अगर (!cptr->accept_output)
		result = -EPERM;
	अन्यथा
		result = snd_seq_deliver_event(cptr, ev, atomic, hop);

	snd_seq_client_unlock(cptr);
	वापस result;
पूर्ण
EXPORT_SYMBOL(snd_seq_kernel_client_dispatch);

/**
 * snd_seq_kernel_client_ctl - operate a command क्रम a client with data in
 *			       kernel space.
 * @clientid:	A numerical ID क्रम a client.
 * @cmd:	An ioctl(2) command क्रम ALSA sequencer operation.
 * @arg:	A poपूर्णांकer to data in kernel space.
 *
 * Against its name, both kernel/application client can be handled by this
 * kernel API. A poपूर्णांकer of 'arg' argument should be in kernel space.
 *
 * Return: 0 at success. Negative error code at failure.
 */
पूर्णांक snd_seq_kernel_client_ctl(पूर्णांक clientid, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	स्थिर काष्ठा ioctl_handler *handler;
	काष्ठा snd_seq_client *client;

	client = clientptr(clientid);
	अगर (client == शून्य)
		वापस -ENXIO;

	क्रम (handler = ioctl_handlers; handler->cmd > 0; ++handler) अणु
		अगर (handler->cmd == cmd)
			वापस handler->func(client, arg);
	पूर्ण

	pr_debug("ALSA: seq unknown ioctl() 0x%x (type='%c', number=0x%02x)\n",
		 cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
	वापस -ENOTTY;
पूर्ण
EXPORT_SYMBOL(snd_seq_kernel_client_ctl);

/* exported (क्रम OSS emulator) */
पूर्णांक snd_seq_kernel_client_ग_लिखो_poll(पूर्णांक clientid, काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा snd_seq_client *client;

	client = clientptr(clientid);
	अगर (client == शून्य)
		वापस -ENXIO;

	अगर (! snd_seq_ग_लिखो_pool_allocated(client))
		वापस 1;
	अगर (snd_seq_pool_poll_रुको(client->pool, file, रुको))
		वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_seq_kernel_client_ग_लिखो_poll);

/*---------------------------------------------------------------------------*/

#अगर_घोषित CONFIG_SND_PROC_FS
/*
 *  /proc पूर्णांकerface
 */
अटल व्योम snd_seq_info_dump_subscribers(काष्ठा snd_info_buffer *buffer,
					  काष्ठा snd_seq_port_subs_info *group,
					  पूर्णांक is_src, अक्षर *msg)
अणु
	काष्ठा list_head *p;
	काष्ठा snd_seq_subscribers *s;
	पूर्णांक count = 0;

	करोwn_पढ़ो(&group->list_mutex);
	अगर (list_empty(&group->list_head)) अणु
		up_पढ़ो(&group->list_mutex);
		वापस;
	पूर्ण
	snd_iम_लिखो(buffer, msg);
	list_क्रम_each(p, &group->list_head) अणु
		अगर (is_src)
			s = list_entry(p, काष्ठा snd_seq_subscribers, src_list);
		अन्यथा
			s = list_entry(p, काष्ठा snd_seq_subscribers, dest_list);
		अगर (count++)
			snd_iम_लिखो(buffer, ", ");
		snd_iम_लिखो(buffer, "%d:%d",
			    is_src ? s->info.dest.client : s->info.sender.client,
			    is_src ? s->info.dest.port : s->info.sender.port);
		अगर (s->info.flags & SNDRV_SEQ_PORT_SUBS_TIMESTAMP)
			snd_iम_लिखो(buffer, "[%c:%d]", ((s->info.flags & SNDRV_SEQ_PORT_SUBS_TIME_REAL) ? 'r' : 't'), s->info.queue);
		अगर (group->exclusive)
			snd_iम_लिखो(buffer, "[ex]");
	पूर्ण
	up_पढ़ो(&group->list_mutex);
	snd_iम_लिखो(buffer, "\n");
पूर्ण

#घोषणा FLAG_PERM_RD(perm) ((perm) & SNDRV_SEQ_PORT_CAP_READ ? ((perm) & SNDRV_SEQ_PORT_CAP_SUBS_READ ? 'R' : 'r') : '-')
#घोषणा FLAG_PERM_WR(perm) ((perm) & SNDRV_SEQ_PORT_CAP_WRITE ? ((perm) & SNDRV_SEQ_PORT_CAP_SUBS_WRITE ? 'W' : 'w') : '-')
#घोषणा FLAG_PERM_EX(perm) ((perm) & SNDRV_SEQ_PORT_CAP_NO_EXPORT ? '-' : 'e')

#घोषणा FLAG_PERM_DUPLEX(perm) ((perm) & SNDRV_SEQ_PORT_CAP_DUPLEX ? 'X' : '-')

अटल व्योम snd_seq_info_dump_ports(काष्ठा snd_info_buffer *buffer,
				    काष्ठा snd_seq_client *client)
अणु
	काष्ठा snd_seq_client_port *p;

	mutex_lock(&client->ports_mutex);
	list_क्रम_each_entry(p, &client->ports_list_head, list) अणु
		snd_iम_लिखो(buffer, "  Port %3d : \"%s\" (%c%c%c%c)\n",
			    p->addr.port, p->name,
			    FLAG_PERM_RD(p->capability),
			    FLAG_PERM_WR(p->capability),
			    FLAG_PERM_EX(p->capability),
			    FLAG_PERM_DUPLEX(p->capability));
		snd_seq_info_dump_subscribers(buffer, &p->c_src, 1, "    Connecting To: ");
		snd_seq_info_dump_subscribers(buffer, &p->c_dest, 0, "    Connected From: ");
	पूर्ण
	mutex_unlock(&client->ports_mutex);
पूर्ण


/* exported to seq_info.c */
व्योम snd_seq_info_clients_पढ़ो(काष्ठा snd_info_entry *entry, 
			       काष्ठा snd_info_buffer *buffer)
अणु
	पूर्णांक c;
	काष्ठा snd_seq_client *client;

	snd_iम_लिखो(buffer, "Client info\n");
	snd_iम_लिखो(buffer, "  cur  clients : %d\n", client_usage.cur);
	snd_iम_लिखो(buffer, "  peak clients : %d\n", client_usage.peak);
	snd_iम_लिखो(buffer, "  max  clients : %d\n", SNDRV_SEQ_MAX_CLIENTS);
	snd_iम_लिखो(buffer, "\n");

	/* list the client table */
	क्रम (c = 0; c < SNDRV_SEQ_MAX_CLIENTS; c++) अणु
		client = snd_seq_client_use_ptr(c);
		अगर (client == शून्य)
			जारी;
		अगर (client->type == NO_CLIENT) अणु
			snd_seq_client_unlock(client);
			जारी;
		पूर्ण

		snd_iम_लिखो(buffer, "Client %3d : \"%s\" [%s]\n",
			    c, client->name,
			    client->type == USER_CLIENT ? "User" : "Kernel");
		snd_seq_info_dump_ports(buffer, client);
		अगर (snd_seq_ग_लिखो_pool_allocated(client)) अणु
			snd_iम_लिखो(buffer, "  Output pool :\n");
			snd_seq_info_pool(buffer, client->pool, "    ");
		पूर्ण
		अगर (client->type == USER_CLIENT && client->data.user.fअगरo &&
		    client->data.user.fअगरo->pool) अणु
			snd_iम_लिखो(buffer, "  Input pool :\n");
			snd_seq_info_pool(buffer, client->data.user.fअगरo->pool, "    ");
		पूर्ण
		snd_seq_client_unlock(client);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_PROC_FS */

/*---------------------------------------------------------------------------*/


/*
 *  REGISTRATION PART
 */

अटल स्थिर काष्ठा file_operations snd_seq_f_ops =
अणु
	.owner =	THIS_MODULE,
	.पढ़ो =		snd_seq_पढ़ो,
	.ग_लिखो =	snd_seq_ग_लिखो,
	.खोलो =		snd_seq_खोलो,
	.release =	snd_seq_release,
	.llseek =	no_llseek,
	.poll =		snd_seq_poll,
	.unlocked_ioctl =	snd_seq_ioctl,
	.compat_ioctl =	snd_seq_ioctl_compat,
पूर्ण;

अटल काष्ठा device seq_dev;

/* 
 * रेजिस्टर sequencer device 
 */
पूर्णांक __init snd_sequencer_device_init(व्योम)
अणु
	पूर्णांक err;

	snd_device_initialize(&seq_dev, शून्य);
	dev_set_name(&seq_dev, "seq");

	mutex_lock(&रेजिस्टर_mutex);
	err = snd_रेजिस्टर_device(SNDRV_DEVICE_TYPE_SEQUENCER, शून्य, 0,
				  &snd_seq_f_ops, शून्य, &seq_dev);
	mutex_unlock(&रेजिस्टर_mutex);
	अगर (err < 0) अणु
		put_device(&seq_dev);
		वापस err;
	पूर्ण
	
	वापस 0;
पूर्ण



/* 
 * unरेजिस्टर sequencer device 
 */
व्योम snd_sequencer_device_करोne(व्योम)
अणु
	snd_unरेजिस्टर_device(&seq_dev);
	put_device(&seq_dev);
पूर्ण
