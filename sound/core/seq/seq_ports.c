<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA sequencer Ports
 *   Copyright (c) 1998 by Frank van de Pol <fvdpol@coil.demon.nl>
 *                         Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <sound/core.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश "seq_system.h"
#समावेश "seq_ports.h"
#समावेश "seq_clientmgr.h"

/*

   registration of client ports

 */


/* 

NOTE: the current implementation of the port काष्ठाure as a linked list is
not optimal क्रम clients that have many ports. For sending messages to all
subscribers of a port we first need to find the address of the port
काष्ठाure, which means we have to traverse the list. A direct access table
(array) would be better, but big pपुनः_स्मृतिated arrays waste memory.

Possible actions:

1) leave it this way, a client करोes normaly करोes not have more than a few
ports

2) replace the linked list of ports by a array of poपूर्णांकers which is
dynamicly kदो_स्मृतिed. When a port is added or deleted we can simply allocate
a new array, copy the corresponding poपूर्णांकers, and delete the old one. We
then only need a poपूर्णांकer to this array, and an पूर्णांकeger that tells us how
much elements are in array.

*/

/* वापस poपूर्णांकer to port काष्ठाure - port is locked अगर found */
काष्ठा snd_seq_client_port *snd_seq_port_use_ptr(काष्ठा snd_seq_client *client,
						 पूर्णांक num)
अणु
	काष्ठा snd_seq_client_port *port;

	अगर (client == शून्य)
		वापस शून्य;
	पढ़ो_lock(&client->ports_lock);
	list_क्रम_each_entry(port, &client->ports_list_head, list) अणु
		अगर (port->addr.port == num) अणु
			अगर (port->closing)
				अवरोध; /* deleting now */
			snd_use_lock_use(&port->use_lock);
			पढ़ो_unlock(&client->ports_lock);
			वापस port;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&client->ports_lock);
	वापस शून्य;		/* not found */
पूर्ण


/* search क्रम the next port - port is locked अगर found */
काष्ठा snd_seq_client_port *snd_seq_port_query_nearest(काष्ठा snd_seq_client *client,
						       काष्ठा snd_seq_port_info *pinfo)
अणु
	पूर्णांक num;
	काष्ठा snd_seq_client_port *port, *found;

	num = pinfo->addr.port;
	found = शून्य;
	पढ़ो_lock(&client->ports_lock);
	list_क्रम_each_entry(port, &client->ports_list_head, list) अणु
		अगर (port->addr.port < num)
			जारी;
		अगर (port->addr.port == num) अणु
			found = port;
			अवरोध;
		पूर्ण
		अगर (found == शून्य || port->addr.port < found->addr.port)
			found = port;
	पूर्ण
	अगर (found) अणु
		अगर (found->closing)
			found = शून्य;
		अन्यथा
			snd_use_lock_use(&found->use_lock);
	पूर्ण
	पढ़ो_unlock(&client->ports_lock);
	वापस found;
पूर्ण


/* initialize snd_seq_port_subs_info */
अटल व्योम port_subs_info_init(काष्ठा snd_seq_port_subs_info *grp)
अणु
	INIT_LIST_HEAD(&grp->list_head);
	grp->count = 0;
	grp->exclusive = 0;
	rwlock_init(&grp->list_lock);
	init_rwsem(&grp->list_mutex);
	grp->खोलो = शून्य;
	grp->बंद = शून्य;
पूर्ण


/* create a port, port number is वापसed (-1 on failure);
 * the caller needs to unref the port via snd_seq_port_unlock() appropriately
 */
काष्ठा snd_seq_client_port *snd_seq_create_port(काष्ठा snd_seq_client *client,
						पूर्णांक port)
अणु
	काष्ठा snd_seq_client_port *new_port, *p;
	पूर्णांक num = -1;
	
	/* sanity check */
	अगर (snd_BUG_ON(!client))
		वापस शून्य;

	अगर (client->num_ports >= SNDRV_SEQ_MAX_PORTS) अणु
		pr_warn("ALSA: seq: too many ports for client %d\n", client->number);
		वापस शून्य;
	पूर्ण

	/* create a new port */
	new_port = kzalloc(माप(*new_port), GFP_KERNEL);
	अगर (!new_port)
		वापस शून्य;	/* failure, out of memory */
	/* init port data */
	new_port->addr.client = client->number;
	new_port->addr.port = -1;
	new_port->owner = THIS_MODULE;
	प्र_लिखो(new_port->name, "port-%d", num);
	snd_use_lock_init(&new_port->use_lock);
	port_subs_info_init(&new_port->c_src);
	port_subs_info_init(&new_port->c_dest);
	snd_use_lock_use(&new_port->use_lock);

	num = port >= 0 ? port : 0;
	mutex_lock(&client->ports_mutex);
	ग_लिखो_lock_irq(&client->ports_lock);
	list_क्रम_each_entry(p, &client->ports_list_head, list) अणु
		अगर (p->addr.port > num)
			अवरोध;
		अगर (port < 0) /* स्वतः-probe mode */
			num = p->addr.port + 1;
	पूर्ण
	/* insert the new port */
	list_add_tail(&new_port->list, &p->list);
	client->num_ports++;
	new_port->addr.port = num;	/* store the port number in the port */
	प्र_लिखो(new_port->name, "port-%d", num);
	ग_लिखो_unlock_irq(&client->ports_lock);
	mutex_unlock(&client->ports_mutex);

	वापस new_port;
पूर्ण

/* */
अटल पूर्णांक subscribe_port(काष्ठा snd_seq_client *client,
			  काष्ठा snd_seq_client_port *port,
			  काष्ठा snd_seq_port_subs_info *grp,
			  काष्ठा snd_seq_port_subscribe *info, पूर्णांक send_ack);
अटल पूर्णांक unsubscribe_port(काष्ठा snd_seq_client *client,
			    काष्ठा snd_seq_client_port *port,
			    काष्ठा snd_seq_port_subs_info *grp,
			    काष्ठा snd_seq_port_subscribe *info, पूर्णांक send_ack);


अटल काष्ठा snd_seq_client_port *get_client_port(काष्ठा snd_seq_addr *addr,
						   काष्ठा snd_seq_client **cp)
अणु
	काष्ठा snd_seq_client_port *p;
	*cp = snd_seq_client_use_ptr(addr->client);
	अगर (*cp) अणु
		p = snd_seq_port_use_ptr(*cp, addr->port);
		अगर (! p) अणु
			snd_seq_client_unlock(*cp);
			*cp = शून्य;
		पूर्ण
		वापस p;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम delete_and_unsubscribe_port(काष्ठा snd_seq_client *client,
					काष्ठा snd_seq_client_port *port,
					काष्ठा snd_seq_subscribers *subs,
					bool is_src, bool ack);

अटल अंतरभूत काष्ठा snd_seq_subscribers *
get_subscriber(काष्ठा list_head *p, bool is_src)
अणु
	अगर (is_src)
		वापस list_entry(p, काष्ठा snd_seq_subscribers, src_list);
	अन्यथा
		वापस list_entry(p, काष्ठा snd_seq_subscribers, dest_list);
पूर्ण

/*
 * हटाओ all subscribers on the list
 * this is called from port_delete, क्रम each src and dest list.
 */
अटल व्योम clear_subscriber_list(काष्ठा snd_seq_client *client,
				  काष्ठा snd_seq_client_port *port,
				  काष्ठा snd_seq_port_subs_info *grp,
				  पूर्णांक is_src)
अणु
	काष्ठा list_head *p, *n;

	list_क्रम_each_safe(p, n, &grp->list_head) अणु
		काष्ठा snd_seq_subscribers *subs;
		काष्ठा snd_seq_client *c;
		काष्ठा snd_seq_client_port *aport;

		subs = get_subscriber(p, is_src);
		अगर (is_src)
			aport = get_client_port(&subs->info.dest, &c);
		अन्यथा
			aport = get_client_port(&subs->info.sender, &c);
		delete_and_unsubscribe_port(client, port, subs, is_src, false);

		अगर (!aport) अणु
			/* looks like the connected port is being deleted.
			 * we decrease the counter, and when both ports are deleted
			 * हटाओ the subscriber info
			 */
			अगर (atomic_dec_and_test(&subs->ref_count))
				kमुक्त(subs);
			जारी;
		पूर्ण

		/* ok we got the connected port */
		delete_and_unsubscribe_port(c, aport, subs, !is_src, true);
		kमुक्त(subs);
		snd_seq_port_unlock(aport);
		snd_seq_client_unlock(c);
	पूर्ण
पूर्ण

/* delete port data */
अटल पूर्णांक port_delete(काष्ठा snd_seq_client *client,
		       काष्ठा snd_seq_client_port *port)
अणु
	/* set closing flag and रुको क्रम all port access are gone */
	port->closing = 1;
	snd_use_lock_sync(&port->use_lock); 

	/* clear subscribers info */
	clear_subscriber_list(client, port, &port->c_src, true);
	clear_subscriber_list(client, port, &port->c_dest, false);

	अगर (port->निजी_मुक्त)
		port->निजी_मुक्त(port->निजी_data);

	snd_BUG_ON(port->c_src.count != 0);
	snd_BUG_ON(port->c_dest.count != 0);

	kमुक्त(port);
	वापस 0;
पूर्ण


/* delete a port with the given port id */
पूर्णांक snd_seq_delete_port(काष्ठा snd_seq_client *client, पूर्णांक port)
अणु
	काष्ठा snd_seq_client_port *found = शून्य, *p;

	mutex_lock(&client->ports_mutex);
	ग_लिखो_lock_irq(&client->ports_lock);
	list_क्रम_each_entry(p, &client->ports_list_head, list) अणु
		अगर (p->addr.port == port) अणु
			/* ok found.  delete from the list at first */
			list_del(&p->list);
			client->num_ports--;
			found = p;
			अवरोध;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock_irq(&client->ports_lock);
	mutex_unlock(&client->ports_mutex);
	अगर (found)
		वापस port_delete(client, found);
	अन्यथा
		वापस -ENOENT;
पूर्ण

/* delete the all ports beदीर्घing to the given client */
पूर्णांक snd_seq_delete_all_ports(काष्ठा snd_seq_client *client)
अणु
	काष्ठा list_head deleted_list;
	काष्ठा snd_seq_client_port *port, *पंचांगp;
	
	/* move the port list to deleted_list, and
	 * clear the port list in the client data.
	 */
	mutex_lock(&client->ports_mutex);
	ग_लिखो_lock_irq(&client->ports_lock);
	अगर (! list_empty(&client->ports_list_head)) अणु
		list_add(&deleted_list, &client->ports_list_head);
		list_del_init(&client->ports_list_head);
	पूर्ण अन्यथा अणु
		INIT_LIST_HEAD(&deleted_list);
	पूर्ण
	client->num_ports = 0;
	ग_लिखो_unlock_irq(&client->ports_lock);

	/* हटाओ each port in deleted_list */
	list_क्रम_each_entry_safe(port, पंचांगp, &deleted_list, list) अणु
		list_del(&port->list);
		snd_seq_प्रणाली_client_ev_port_निकास(port->addr.client, port->addr.port);
		port_delete(client, port);
	पूर्ण
	mutex_unlock(&client->ports_mutex);
	वापस 0;
पूर्ण

/* set port info fields */
पूर्णांक snd_seq_set_port_info(काष्ठा snd_seq_client_port * port,
			  काष्ठा snd_seq_port_info * info)
अणु
	अगर (snd_BUG_ON(!port || !info))
		वापस -EINVAL;

	/* set port name */
	अगर (info->name[0])
		strscpy(port->name, info->name, माप(port->name));
	
	/* set capabilities */
	port->capability = info->capability;
	
	/* get port type */
	port->type = info->type;

	/* inक्रमmation about supported channels/voices */
	port->midi_channels = info->midi_channels;
	port->midi_voices = info->midi_voices;
	port->synth_voices = info->synth_voices;

	/* बारtamping */
	port->बारtamping = (info->flags & SNDRV_SEQ_PORT_FLG_TIMESTAMP) ? 1 : 0;
	port->समय_real = (info->flags & SNDRV_SEQ_PORT_FLG_TIME_REAL) ? 1 : 0;
	port->समय_queue = info->समय_queue;

	वापस 0;
पूर्ण

/* get port info fields */
पूर्णांक snd_seq_get_port_info(काष्ठा snd_seq_client_port * port,
			  काष्ठा snd_seq_port_info * info)
अणु
	अगर (snd_BUG_ON(!port || !info))
		वापस -EINVAL;

	/* get port name */
	strscpy(info->name, port->name, माप(info->name));
	
	/* get capabilities */
	info->capability = port->capability;

	/* get port type */
	info->type = port->type;

	/* inक्रमmation about supported channels/voices */
	info->midi_channels = port->midi_channels;
	info->midi_voices = port->midi_voices;
	info->synth_voices = port->synth_voices;

	/* get subscriber counts */
	info->पढ़ो_use = port->c_src.count;
	info->ग_लिखो_use = port->c_dest.count;
	
	/* बारtamping */
	info->flags = 0;
	अगर (port->बारtamping) अणु
		info->flags |= SNDRV_SEQ_PORT_FLG_TIMESTAMP;
		अगर (port->समय_real)
			info->flags |= SNDRV_SEQ_PORT_FLG_TIME_REAL;
		info->समय_queue = port->समय_queue;
	पूर्ण

	वापस 0;
पूर्ण



/*
 * call callback functions (अगर any):
 * the callbacks are invoked only when the first (क्रम connection) or
 * the last subscription (क्रम disconnection) is करोne.  Second or later
 * subscription results in increment of counter, but no callback is
 * invoked.
 * This feature is useful अगर these callbacks are associated with
 * initialization or termination of devices (see seq_midi.c).
 */

अटल पूर्णांक subscribe_port(काष्ठा snd_seq_client *client,
			  काष्ठा snd_seq_client_port *port,
			  काष्ठा snd_seq_port_subs_info *grp,
			  काष्ठा snd_seq_port_subscribe *info,
			  पूर्णांक send_ack)
अणु
	पूर्णांक err = 0;

	अगर (!try_module_get(port->owner))
		वापस -EFAULT;
	grp->count++;
	अगर (grp->खोलो && grp->count == 1) अणु
		err = grp->खोलो(port->निजी_data, info);
		अगर (err < 0) अणु
			module_put(port->owner);
			grp->count--;
		पूर्ण
	पूर्ण
	अगर (err >= 0 && send_ack && client->type == USER_CLIENT)
		snd_seq_client_notअगरy_subscription(port->addr.client, port->addr.port,
						   info, SNDRV_SEQ_EVENT_PORT_SUBSCRIBED);

	वापस err;
पूर्ण

अटल पूर्णांक unsubscribe_port(काष्ठा snd_seq_client *client,
			    काष्ठा snd_seq_client_port *port,
			    काष्ठा snd_seq_port_subs_info *grp,
			    काष्ठा snd_seq_port_subscribe *info,
			    पूर्णांक send_ack)
अणु
	पूर्णांक err = 0;

	अगर (! grp->count)
		वापस -EINVAL;
	grp->count--;
	अगर (grp->बंद && grp->count == 0)
		err = grp->बंद(port->निजी_data, info);
	अगर (send_ack && client->type == USER_CLIENT)
		snd_seq_client_notअगरy_subscription(port->addr.client, port->addr.port,
						   info, SNDRV_SEQ_EVENT_PORT_UNSUBSCRIBED);
	module_put(port->owner);
	वापस err;
पूर्ण



/* check अगर both addresses are identical */
अटल अंतरभूत पूर्णांक addr_match(काष्ठा snd_seq_addr *r, काष्ठा snd_seq_addr *s)
अणु
	वापस (r->client == s->client) && (r->port == s->port);
पूर्ण

/* check the two subscribe info match */
/* अगर flags is zero, checks only sender and destination addresses */
अटल पूर्णांक match_subs_info(काष्ठा snd_seq_port_subscribe *r,
			   काष्ठा snd_seq_port_subscribe *s)
अणु
	अगर (addr_match(&r->sender, &s->sender) &&
	    addr_match(&r->dest, &s->dest)) अणु
		अगर (r->flags && r->flags == s->flags)
			वापस r->queue == s->queue;
		अन्यथा अगर (! r->flags)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_and_subscribe_port(काष्ठा snd_seq_client *client,
				    काष्ठा snd_seq_client_port *port,
				    काष्ठा snd_seq_subscribers *subs,
				    bool is_src, bool exclusive, bool ack)
अणु
	काष्ठा snd_seq_port_subs_info *grp;
	काष्ठा list_head *p;
	काष्ठा snd_seq_subscribers *s;
	पूर्णांक err;

	grp = is_src ? &port->c_src : &port->c_dest;
	err = -EBUSY;
	करोwn_ग_लिखो(&grp->list_mutex);
	अगर (exclusive) अणु
		अगर (!list_empty(&grp->list_head))
			जाओ __error;
	पूर्ण अन्यथा अणु
		अगर (grp->exclusive)
			जाओ __error;
		/* check whether alपढ़ोy exists */
		list_क्रम_each(p, &grp->list_head) अणु
			s = get_subscriber(p, is_src);
			अगर (match_subs_info(&subs->info, &s->info))
				जाओ __error;
		पूर्ण
	पूर्ण

	err = subscribe_port(client, port, grp, &subs->info, ack);
	अगर (err < 0) अणु
		grp->exclusive = 0;
		जाओ __error;
	पूर्ण

	/* add to list */
	ग_लिखो_lock_irq(&grp->list_lock);
	अगर (is_src)
		list_add_tail(&subs->src_list, &grp->list_head);
	अन्यथा
		list_add_tail(&subs->dest_list, &grp->list_head);
	grp->exclusive = exclusive;
	atomic_inc(&subs->ref_count);
	ग_लिखो_unlock_irq(&grp->list_lock);
	err = 0;

 __error:
	up_ग_लिखो(&grp->list_mutex);
	वापस err;
पूर्ण

अटल व्योम delete_and_unsubscribe_port(काष्ठा snd_seq_client *client,
					काष्ठा snd_seq_client_port *port,
					काष्ठा snd_seq_subscribers *subs,
					bool is_src, bool ack)
अणु
	काष्ठा snd_seq_port_subs_info *grp;
	काष्ठा list_head *list;
	bool empty;

	grp = is_src ? &port->c_src : &port->c_dest;
	list = is_src ? &subs->src_list : &subs->dest_list;
	करोwn_ग_लिखो(&grp->list_mutex);
	ग_लिखो_lock_irq(&grp->list_lock);
	empty = list_empty(list);
	अगर (!empty)
		list_del_init(list);
	grp->exclusive = 0;
	ग_लिखो_unlock_irq(&grp->list_lock);

	अगर (!empty)
		unsubscribe_port(client, port, grp, &subs->info, ack);
	up_ग_लिखो(&grp->list_mutex);
पूर्ण

/* connect two ports */
पूर्णांक snd_seq_port_connect(काष्ठा snd_seq_client *connector,
			 काष्ठा snd_seq_client *src_client,
			 काष्ठा snd_seq_client_port *src_port,
			 काष्ठा snd_seq_client *dest_client,
			 काष्ठा snd_seq_client_port *dest_port,
			 काष्ठा snd_seq_port_subscribe *info)
अणु
	काष्ठा snd_seq_subscribers *subs;
	bool exclusive;
	पूर्णांक err;

	subs = kzalloc(माप(*subs), GFP_KERNEL);
	अगर (!subs)
		वापस -ENOMEM;

	subs->info = *info;
	atomic_set(&subs->ref_count, 0);
	INIT_LIST_HEAD(&subs->src_list);
	INIT_LIST_HEAD(&subs->dest_list);

	exclusive = !!(info->flags & SNDRV_SEQ_PORT_SUBS_EXCLUSIVE);

	err = check_and_subscribe_port(src_client, src_port, subs, true,
				       exclusive,
				       connector->number != src_client->number);
	अगर (err < 0)
		जाओ error;
	err = check_and_subscribe_port(dest_client, dest_port, subs, false,
				       exclusive,
				       connector->number != dest_client->number);
	अगर (err < 0)
		जाओ error_dest;

	वापस 0;

 error_dest:
	delete_and_unsubscribe_port(src_client, src_port, subs, true,
				    connector->number != src_client->number);
 error:
	kमुक्त(subs);
	वापस err;
पूर्ण

/* हटाओ the connection */
पूर्णांक snd_seq_port_disconnect(काष्ठा snd_seq_client *connector,
			    काष्ठा snd_seq_client *src_client,
			    काष्ठा snd_seq_client_port *src_port,
			    काष्ठा snd_seq_client *dest_client,
			    काष्ठा snd_seq_client_port *dest_port,
			    काष्ठा snd_seq_port_subscribe *info)
अणु
	काष्ठा snd_seq_port_subs_info *src = &src_port->c_src;
	काष्ठा snd_seq_subscribers *subs;
	पूर्णांक err = -ENOENT;

	करोwn_ग_लिखो(&src->list_mutex);
	/* look क्रम the connection */
	list_क्रम_each_entry(subs, &src->list_head, src_list) अणु
		अगर (match_subs_info(info, &subs->info)) अणु
			atomic_dec(&subs->ref_count); /* mark as not पढ़ोy */
			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	up_ग_लिखो(&src->list_mutex);
	अगर (err < 0)
		वापस err;

	delete_and_unsubscribe_port(src_client, src_port, subs, true,
				    connector->number != src_client->number);
	delete_and_unsubscribe_port(dest_client, dest_port, subs, false,
				    connector->number != dest_client->number);
	kमुक्त(subs);
	वापस 0;
पूर्ण


/* get matched subscriber */
पूर्णांक snd_seq_port_get_subscription(काष्ठा snd_seq_port_subs_info *src_grp,
				  काष्ठा snd_seq_addr *dest_addr,
				  काष्ठा snd_seq_port_subscribe *subs)
अणु
	काष्ठा snd_seq_subscribers *s;
	पूर्णांक err = -ENOENT;

	करोwn_पढ़ो(&src_grp->list_mutex);
	list_क्रम_each_entry(s, &src_grp->list_head, src_list) अणु
		अगर (addr_match(dest_addr, &s->info.dest)) अणु
			*subs = s->info;
			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	up_पढ़ो(&src_grp->list_mutex);
	वापस err;
पूर्ण

/*
 * Attach a device driver that wants to receive events from the
 * sequencer.  Returns the new port number on success.
 * A driver that wants to receive the events converted to midi, will
 * use snd_seq_midisynth_रेजिस्टर_port().
 */
/* exported */
पूर्णांक snd_seq_event_port_attach(पूर्णांक client,
			      काष्ठा snd_seq_port_callback *pcbp,
			      पूर्णांक cap, पूर्णांक type, पूर्णांक midi_channels,
			      पूर्णांक midi_voices, अक्षर *portname)
अणु
	काष्ठा snd_seq_port_info portinfo;
	पूर्णांक  ret;

	/* Set up the port */
	स_रखो(&portinfo, 0, माप(portinfo));
	portinfo.addr.client = client;
	strscpy(portinfo.name, portname ? portname : "Unnamed port",
		माप(portinfo.name));

	portinfo.capability = cap;
	portinfo.type = type;
	portinfo.kernel = pcbp;
	portinfo.midi_channels = midi_channels;
	portinfo.midi_voices = midi_voices;

	/* Create it */
	ret = snd_seq_kernel_client_ctl(client,
					SNDRV_SEQ_IOCTL_CREATE_PORT,
					&portinfo);

	अगर (ret >= 0)
		ret = portinfo.addr.port;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(snd_seq_event_port_attach);

/*
 * Detach the driver from a port.
 */
/* exported */
पूर्णांक snd_seq_event_port_detach(पूर्णांक client, पूर्णांक port)
अणु
	काष्ठा snd_seq_port_info portinfo;
	पूर्णांक  err;

	स_रखो(&portinfo, 0, माप(portinfo));
	portinfo.addr.client = client;
	portinfo.addr.port   = port;
	err = snd_seq_kernel_client_ctl(client,
					SNDRV_SEQ_IOCTL_DELETE_PORT,
					&portinfo);

	वापस err;
पूर्ण
EXPORT_SYMBOL(snd_seq_event_port_detach);
