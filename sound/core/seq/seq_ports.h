<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   ALSA sequencer Ports 
 *   Copyright (c) 1998 by Frank van de Pol <fvdpol@coil.demon.nl>
 */
#अगर_अघोषित __SND_SEQ_PORTS_H
#घोषणा __SND_SEQ_PORTS_H

#समावेश <sound/seq_kernel.h>
#समावेश "seq_lock.h"

/* list of 'exported' ports */

/* Client ports that are not exported are still accessible, but are
 anonymous ports. 
 
 If a port supports SUBSCRIPTION, that port can send events to all
 subscribersto a special address, with address
 (queue==SNDRV_SEQ_ADDRESS_SUBSCRIBERS). The message is then send to all
 recipients that are रेजिस्टरed in the subscription list. A typical
 application क्रम these SUBSCRIPTION events is handling of incoming MIDI
 data. The port करोesn't 'know' what other clients are पूर्णांकerested in this
 message. If क्रम instance a MIDI recording application would like to receive
 the events from that port, it will first have to subscribe with that port.
 
*/

काष्ठा snd_seq_subscribers अणु
	काष्ठा snd_seq_port_subscribe info;	/* additional info */
	काष्ठा list_head src_list;	/* link of sources */
	काष्ठा list_head dest_list;	/* link of destinations */
	atomic_t ref_count;
पूर्ण;

काष्ठा snd_seq_port_subs_info अणु
	काष्ठा list_head list_head;	/* list of subscribed ports */
	अचिन्हित पूर्णांक count;		/* count of subscribers */
	अचिन्हित पूर्णांक exclusive: 1;	/* exclusive mode */
	काष्ठा rw_semaphore list_mutex;
	rwlock_t list_lock;
	पूर्णांक (*खोलो)(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe *info);
	पूर्णांक (*बंद)(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe *info);
पूर्ण;

काष्ठा snd_seq_client_port अणु

	काष्ठा snd_seq_addr addr;	/* client/port number */
	काष्ठा module *owner;		/* owner of this port */
	अक्षर name[64];			/* port name */	
	काष्ठा list_head list;		/* port list */
	snd_use_lock_t use_lock;

	/* subscribers */
	काष्ठा snd_seq_port_subs_info c_src;	/* पढ़ो (sender) list */
	काष्ठा snd_seq_port_subs_info c_dest;	/* ग_लिखो (dest) list */

	पूर्णांक (*event_input)(काष्ठा snd_seq_event *ev, पूर्णांक direct, व्योम *निजी_data,
			   पूर्णांक atomic, पूर्णांक hop);
	व्योम (*निजी_मुक्त)(व्योम *निजी_data);
	व्योम *निजी_data;
	अचिन्हित पूर्णांक closing : 1;
	अचिन्हित पूर्णांक बारtamping: 1;
	अचिन्हित पूर्णांक समय_real: 1;
	पूर्णांक समय_queue;
	
	/* capability, inport, output, sync */
	अचिन्हित पूर्णांक capability;	/* port capability bits */
	अचिन्हित पूर्णांक type;		/* port type bits */

	/* supported channels */
	पूर्णांक midi_channels;
	पूर्णांक midi_voices;
	पूर्णांक synth_voices;
		
पूर्ण;

काष्ठा snd_seq_client;

/* वापस poपूर्णांकer to port काष्ठाure and lock port */
काष्ठा snd_seq_client_port *snd_seq_port_use_ptr(काष्ठा snd_seq_client *client, पूर्णांक num);

/* search क्रम next port - port is locked अगर found */
काष्ठा snd_seq_client_port *snd_seq_port_query_nearest(काष्ठा snd_seq_client *client,
						       काष्ठा snd_seq_port_info *pinfo);

/* unlock the port */
#घोषणा snd_seq_port_unlock(port) snd_use_lock_मुक्त(&(port)->use_lock)

/* create a port, port number is वापसed (-1 on failure) */
काष्ठा snd_seq_client_port *snd_seq_create_port(काष्ठा snd_seq_client *client, पूर्णांक port_index);

/* delete a port */
पूर्णांक snd_seq_delete_port(काष्ठा snd_seq_client *client, पूर्णांक port);

/* delete all ports */
पूर्णांक snd_seq_delete_all_ports(काष्ठा snd_seq_client *client);

/* set port info fields */
पूर्णांक snd_seq_set_port_info(काष्ठा snd_seq_client_port *port,
			  काष्ठा snd_seq_port_info *info);

/* get port info fields */
पूर्णांक snd_seq_get_port_info(काष्ठा snd_seq_client_port *port,
			  काष्ठा snd_seq_port_info *info);

/* add subscriber to subscription list */
पूर्णांक snd_seq_port_connect(काष्ठा snd_seq_client *caller,
			 काष्ठा snd_seq_client *s, काष्ठा snd_seq_client_port *sp,
			 काष्ठा snd_seq_client *d, काष्ठा snd_seq_client_port *dp,
			 काष्ठा snd_seq_port_subscribe *info);

/* हटाओ subscriber from subscription list */ 
पूर्णांक snd_seq_port_disconnect(काष्ठा snd_seq_client *caller,
			    काष्ठा snd_seq_client *s, काष्ठा snd_seq_client_port *sp,
			    काष्ठा snd_seq_client *d, काष्ठा snd_seq_client_port *dp,
			    काष्ठा snd_seq_port_subscribe *info);

/* subscribe port */
पूर्णांक snd_seq_port_subscribe(काष्ठा snd_seq_client_port *port,
			   काष्ठा snd_seq_port_subscribe *info);

/* get matched subscriber */
पूर्णांक snd_seq_port_get_subscription(काष्ठा snd_seq_port_subs_info *src_grp,
				  काष्ठा snd_seq_addr *dest_addr,
				  काष्ठा snd_seq_port_subscribe *subs);

#पूर्ण_अगर
