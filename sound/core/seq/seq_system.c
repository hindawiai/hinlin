<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA sequencer System services Client
 *   Copyright (c) 1998-1999 by Frank van de Pol <fvdpol@coil.demon.nl>
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश "seq_system.h"
#समावेश "seq_timer.h"
#समावेश "seq_queue.h"

/* पूर्णांकernal client that provide प्रणाली services, access to समयr etc. */

/*
 * Port "Timer"
 *      - send tempo /start/stop etc. events to this port to manipulate the 
 *        queue's समयr. The queue address is specअगरied in
 *	  data.queue.queue.
 *      - this port supports subscription. The received समयr events are 
 *        broadcasted to all subscribed clients. The modअगरied tempo
 *	  value is stored on data.queue.value.
 *	  The modअगरier client/port is not send.
 *
 * Port "Announce"
 *      - करोes not receive message
 *      - supports supscription. For each client or port attaching to or 
 *        detaching from the प्रणाली an announcement is send to the subscribed
 *        clients.
 *
 * Idea: the subscription mechanism might also work handy क्रम distributing 
 * synchronisation and timing inक्रमmation. In this हाल we would ideally have
 * a list of subscribers क्रम each type of sync (समय, tick), क्रम each timing
 * queue.
 *
 * NOTE: the queue to be started, stopped, etc. must be specअगरied
 *	 in data.queue.addr.queue field.  queue is used only क्रम
 *	 scheduling, and no दीर्घer referred as affected queue.
 *	 They are used only क्रम समयr broadcast (see above).
 *							-- iwai
 */


/* client id of our प्रणाली client */
अटल पूर्णांक sysclient = -1;

/* port id numbers क्रम this client */
अटल पूर्णांक announce_port = -1;



/* fill standard header data, source port & channel are filled in */
अटल पूर्णांक setheader(काष्ठा snd_seq_event * ev, पूर्णांक client, पूर्णांक port)
अणु
	अगर (announce_port < 0)
		वापस -ENODEV;

	स_रखो(ev, 0, माप(काष्ठा snd_seq_event));

	ev->flags &= ~SNDRV_SEQ_EVENT_LENGTH_MASK;
	ev->flags |= SNDRV_SEQ_EVENT_LENGTH_FIXED;

	ev->source.client = sysclient;
	ev->source.port = announce_port;
	ev->dest.client = SNDRV_SEQ_ADDRESS_SUBSCRIBERS;

	/* fill data */
	/*ev->data.addr.queue = SNDRV_SEQ_ADDRESS_UNKNOWN;*/
	ev->data.addr.client = client;
	ev->data.addr.port = port;

	वापस 0;
पूर्ण


/* entry poपूर्णांकs क्रम broadcasting प्रणाली events */
व्योम snd_seq_प्रणाली_broadcast(पूर्णांक client, पूर्णांक port, पूर्णांक type)
अणु
	काष्ठा snd_seq_event ev;
	
	अगर (setheader(&ev, client, port) < 0)
		वापस;
	ev.type = type;
	snd_seq_kernel_client_dispatch(sysclient, &ev, 0, 0);
पूर्ण

/* entry poपूर्णांकs क्रम broadcasting प्रणाली events */
पूर्णांक snd_seq_प्रणाली_notअगरy(पूर्णांक client, पूर्णांक port, काष्ठा snd_seq_event *ev)
अणु
	ev->flags = SNDRV_SEQ_EVENT_LENGTH_FIXED;
	ev->source.client = sysclient;
	ev->source.port = announce_port;
	ev->dest.client = client;
	ev->dest.port = port;
	वापस snd_seq_kernel_client_dispatch(sysclient, ev, 0, 0);
पूर्ण

/* call-back handler क्रम समयr events */
अटल पूर्णांक event_input_समयr(काष्ठा snd_seq_event * ev, पूर्णांक direct, व्योम *निजी_data, पूर्णांक atomic, पूर्णांक hop)
अणु
	वापस snd_seq_control_queue(ev, atomic, hop);
पूर्ण

/* रेजिस्टर our पूर्णांकernal client */
पूर्णांक __init snd_seq_प्रणाली_client_init(व्योम)
अणु
	काष्ठा snd_seq_port_callback pcallbacks;
	काष्ठा snd_seq_port_info *port;
	पूर्णांक err;

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	स_रखो(&pcallbacks, 0, माप(pcallbacks));
	pcallbacks.owner = THIS_MODULE;
	pcallbacks.event_input = event_input_समयr;

	/* रेजिस्टर client */
	sysclient = snd_seq_create_kernel_client(शून्य, 0, "System");
	अगर (sysclient < 0) अणु
		kमुक्त(port);
		वापस sysclient;
	पूर्ण

	/* रेजिस्टर समयr */
	म_नकल(port->name, "Timer");
	port->capability = SNDRV_SEQ_PORT_CAP_WRITE; /* accept queue control */
	port->capability |= SNDRV_SEQ_PORT_CAP_READ|SNDRV_SEQ_PORT_CAP_SUBS_READ; /* क्रम broadcast */
	port->kernel = &pcallbacks;
	port->type = 0;
	port->flags = SNDRV_SEQ_PORT_FLG_GIVEN_PORT;
	port->addr.client = sysclient;
	port->addr.port = SNDRV_SEQ_PORT_SYSTEM_TIMER;
	err = snd_seq_kernel_client_ctl(sysclient, SNDRV_SEQ_IOCTL_CREATE_PORT,
					port);
	अगर (err < 0)
		जाओ error_port;

	/* रेजिस्टर announcement port */
	म_नकल(port->name, "Announce");
	port->capability = SNDRV_SEQ_PORT_CAP_READ|SNDRV_SEQ_PORT_CAP_SUBS_READ; /* क्रम broadcast only */
	port->kernel = शून्य;
	port->type = 0;
	port->flags = SNDRV_SEQ_PORT_FLG_GIVEN_PORT;
	port->addr.client = sysclient;
	port->addr.port = SNDRV_SEQ_PORT_SYSTEM_ANNOUNCE;
	err = snd_seq_kernel_client_ctl(sysclient, SNDRV_SEQ_IOCTL_CREATE_PORT,
					port);
	अगर (err < 0)
		जाओ error_port;
	announce_port = port->addr.port;

	kमुक्त(port);
	वापस 0;

 error_port:
	snd_seq_प्रणाली_client_करोne();
	kमुक्त(port);
	वापस err;
पूर्ण


/* unरेजिस्टर our पूर्णांकernal client */
व्योम snd_seq_प्रणाली_client_करोne(व्योम)
अणु
	पूर्णांक oldsysclient = sysclient;

	अगर (oldsysclient >= 0) अणु
		sysclient = -1;
		announce_port = -1;
		snd_seq_delete_kernel_client(oldsysclient);
	पूर्ण
पूर्ण
