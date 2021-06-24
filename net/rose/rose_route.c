<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 * Copyright (C) Terry Dawson VK2KTJ (terry@animats.net)
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/slab.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <net/arp.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/termios.h>	/* For TIOCINQ/OUTQ */
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/init.h>
#समावेश <net/rose.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/export.h>

अटल अचिन्हित पूर्णांक rose_neigh_no = 1;

अटल काष्ठा rose_node  *rose_node_list;
अटल DEFINE_SPINLOCK(rose_node_list_lock);
अटल काष्ठा rose_neigh *rose_neigh_list;
अटल DEFINE_SPINLOCK(rose_neigh_list_lock);
अटल काष्ठा rose_route *rose_route_list;
अटल DEFINE_SPINLOCK(rose_route_list_lock);

काष्ठा rose_neigh *rose_loopback_neigh;

/*
 *	Add a new route to a node, and in the process add the node and the
 *	neighbour अगर it is new.
 */
अटल पूर्णांक __must_check rose_add_node(काष्ठा rose_route_काष्ठा *rose_route,
	काष्ठा net_device *dev)
अणु
	काष्ठा rose_node  *rose_node, *rose_पंचांगpn, *rose_पंचांगpp;
	काष्ठा rose_neigh *rose_neigh;
	पूर्णांक i, res = 0;

	spin_lock_bh(&rose_node_list_lock);
	spin_lock_bh(&rose_neigh_list_lock);

	rose_node = rose_node_list;
	जबतक (rose_node != शून्य) अणु
		अगर ((rose_node->mask == rose_route->mask) &&
		    (rosecmpm(&rose_route->address, &rose_node->address,
			      rose_route->mask) == 0))
			अवरोध;
		rose_node = rose_node->next;
	पूर्ण

	अगर (rose_node != शून्य && rose_node->loopback) अणु
		res = -EINVAL;
		जाओ out;
	पूर्ण

	rose_neigh = rose_neigh_list;
	जबतक (rose_neigh != शून्य) अणु
		अगर (ax25cmp(&rose_route->neighbour,
			    &rose_neigh->callsign) == 0 &&
		    rose_neigh->dev == dev)
			अवरोध;
		rose_neigh = rose_neigh->next;
	पूर्ण

	अगर (rose_neigh == शून्य) अणु
		rose_neigh = kदो_स्मृति(माप(*rose_neigh), GFP_ATOMIC);
		अगर (rose_neigh == शून्य) अणु
			res = -ENOMEM;
			जाओ out;
		पूर्ण

		rose_neigh->callsign  = rose_route->neighbour;
		rose_neigh->digipeat  = शून्य;
		rose_neigh->ax25      = शून्य;
		rose_neigh->dev       = dev;
		rose_neigh->count     = 0;
		rose_neigh->use       = 0;
		rose_neigh->dce_mode  = 0;
		rose_neigh->loopback  = 0;
		rose_neigh->number    = rose_neigh_no++;
		rose_neigh->restarted = 0;

		skb_queue_head_init(&rose_neigh->queue);

		समयr_setup(&rose_neigh->fसमयr, शून्य, 0);
		समयr_setup(&rose_neigh->t0समयr, शून्य, 0);

		अगर (rose_route->ndigis != 0) अणु
			rose_neigh->digipeat =
				kदो_स्मृति(माप(ax25_digi), GFP_ATOMIC);
			अगर (rose_neigh->digipeat == शून्य) अणु
				kमुक्त(rose_neigh);
				res = -ENOMEM;
				जाओ out;
			पूर्ण

			rose_neigh->digipeat->ndigi      = rose_route->ndigis;
			rose_neigh->digipeat->lastrepeat = -1;

			क्रम (i = 0; i < rose_route->ndigis; i++) अणु
				rose_neigh->digipeat->calls[i]    =
					rose_route->digipeaters[i];
				rose_neigh->digipeat->repeated[i] = 0;
			पूर्ण
		पूर्ण

		rose_neigh->next = rose_neigh_list;
		rose_neigh_list  = rose_neigh;
	पूर्ण

	/*
	 * This is a new node to be inserted पूर्णांकo the list. Find where it needs
	 * to be inserted पूर्णांकo the list, and insert it. We want to be sure
	 * to order the list in descending order of mask size to ensure that
	 * later when we are searching this list the first match will be the
	 * best match.
	 */
	अगर (rose_node == शून्य) अणु
		rose_पंचांगpn = rose_node_list;
		rose_पंचांगpp = शून्य;

		जबतक (rose_पंचांगpn != शून्य) अणु
			अगर (rose_पंचांगpn->mask > rose_route->mask) अणु
				rose_पंचांगpp = rose_पंचांगpn;
				rose_पंचांगpn = rose_पंचांगpn->next;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण

		/* create new node */
		rose_node = kदो_स्मृति(माप(*rose_node), GFP_ATOMIC);
		अगर (rose_node == शून्य) अणु
			res = -ENOMEM;
			जाओ out;
		पूर्ण

		rose_node->address      = rose_route->address;
		rose_node->mask         = rose_route->mask;
		rose_node->count        = 1;
		rose_node->loopback     = 0;
		rose_node->neighbour[0] = rose_neigh;

		अगर (rose_पंचांगpn == शून्य) अणु
			अगर (rose_पंचांगpp == शून्य) अणु	/* Empty list */
				rose_node_list  = rose_node;
				rose_node->next = शून्य;
			पूर्ण अन्यथा अणु
				rose_पंचांगpp->next = rose_node;
				rose_node->next = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (rose_पंचांगpp == शून्य) अणु	/* 1st node */
				rose_node->next = rose_node_list;
				rose_node_list  = rose_node;
			पूर्ण अन्यथा अणु
				rose_पंचांगpp->next = rose_node;
				rose_node->next = rose_पंचांगpn;
			पूर्ण
		पूर्ण
		rose_neigh->count++;

		जाओ out;
	पूर्ण

	/* We have space, slot it in */
	अगर (rose_node->count < 3) अणु
		rose_node->neighbour[rose_node->count] = rose_neigh;
		rose_node->count++;
		rose_neigh->count++;
	पूर्ण

out:
	spin_unlock_bh(&rose_neigh_list_lock);
	spin_unlock_bh(&rose_node_list_lock);

	वापस res;
पूर्ण

/*
 * Caller is holding rose_node_list_lock.
 */
अटल व्योम rose_हटाओ_node(काष्ठा rose_node *rose_node)
अणु
	काष्ठा rose_node *s;

	अगर ((s = rose_node_list) == rose_node) अणु
		rose_node_list = rose_node->next;
		kमुक्त(rose_node);
		वापस;
	पूर्ण

	जबतक (s != शून्य && s->next != शून्य) अणु
		अगर (s->next == rose_node) अणु
			s->next = rose_node->next;
			kमुक्त(rose_node);
			वापस;
		पूर्ण

		s = s->next;
	पूर्ण
पूर्ण

/*
 * Caller is holding rose_neigh_list_lock.
 */
अटल व्योम rose_हटाओ_neigh(काष्ठा rose_neigh *rose_neigh)
अणु
	काष्ठा rose_neigh *s;

	rose_stop_fसमयr(rose_neigh);
	rose_stop_t0समयr(rose_neigh);

	skb_queue_purge(&rose_neigh->queue);

	अगर ((s = rose_neigh_list) == rose_neigh) अणु
		rose_neigh_list = rose_neigh->next;
		अगर (rose_neigh->ax25)
			ax25_cb_put(rose_neigh->ax25);
		kमुक्त(rose_neigh->digipeat);
		kमुक्त(rose_neigh);
		वापस;
	पूर्ण

	जबतक (s != शून्य && s->next != शून्य) अणु
		अगर (s->next == rose_neigh) अणु
			s->next = rose_neigh->next;
			अगर (rose_neigh->ax25)
				ax25_cb_put(rose_neigh->ax25);
			kमुक्त(rose_neigh->digipeat);
			kमुक्त(rose_neigh);
			वापस;
		पूर्ण

		s = s->next;
	पूर्ण
पूर्ण

/*
 * Caller is holding rose_route_list_lock.
 */
अटल व्योम rose_हटाओ_route(काष्ठा rose_route *rose_route)
अणु
	काष्ठा rose_route *s;

	अगर (rose_route->neigh1 != शून्य)
		rose_route->neigh1->use--;

	अगर (rose_route->neigh2 != शून्य)
		rose_route->neigh2->use--;

	अगर ((s = rose_route_list) == rose_route) अणु
		rose_route_list = rose_route->next;
		kमुक्त(rose_route);
		वापस;
	पूर्ण

	जबतक (s != शून्य && s->next != शून्य) अणु
		अगर (s->next == rose_route) अणु
			s->next = rose_route->next;
			kमुक्त(rose_route);
			वापस;
		पूर्ण

		s = s->next;
	पूर्ण
पूर्ण

/*
 *	"Delete" a node. Strictly speaking हटाओ a route to a node. The node
 *	is only deleted अगर no routes are left to it.
 */
अटल पूर्णांक rose_del_node(काष्ठा rose_route_काष्ठा *rose_route,
	काष्ठा net_device *dev)
अणु
	काष्ठा rose_node  *rose_node;
	काष्ठा rose_neigh *rose_neigh;
	पूर्णांक i, err = 0;

	spin_lock_bh(&rose_node_list_lock);
	spin_lock_bh(&rose_neigh_list_lock);

	rose_node = rose_node_list;
	जबतक (rose_node != शून्य) अणु
		अगर ((rose_node->mask == rose_route->mask) &&
		    (rosecmpm(&rose_route->address, &rose_node->address,
			      rose_route->mask) == 0))
			अवरोध;
		rose_node = rose_node->next;
	पूर्ण

	अगर (rose_node == शून्य || rose_node->loopback) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	rose_neigh = rose_neigh_list;
	जबतक (rose_neigh != शून्य) अणु
		अगर (ax25cmp(&rose_route->neighbour,
			    &rose_neigh->callsign) == 0 &&
		    rose_neigh->dev == dev)
			अवरोध;
		rose_neigh = rose_neigh->next;
	पूर्ण

	अगर (rose_neigh == शून्य) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < rose_node->count; i++) अणु
		अगर (rose_node->neighbour[i] == rose_neigh) अणु
			rose_neigh->count--;

			अगर (rose_neigh->count == 0 && rose_neigh->use == 0)
				rose_हटाओ_neigh(rose_neigh);

			rose_node->count--;

			अगर (rose_node->count == 0) अणु
				rose_हटाओ_node(rose_node);
			पूर्ण अन्यथा अणु
				चयन (i) अणु
				हाल 0:
					rose_node->neighbour[0] =
						rose_node->neighbour[1];
					fallthrough;
				हाल 1:
					rose_node->neighbour[1] =
						rose_node->neighbour[2];
					अवरोध;
				हाल 2:
					अवरोध;
				पूर्ण
			पूर्ण
			जाओ out;
		पूर्ण
	पूर्ण
	err = -EINVAL;

out:
	spin_unlock_bh(&rose_neigh_list_lock);
	spin_unlock_bh(&rose_node_list_lock);

	वापस err;
पूर्ण

/*
 *	Add the loopback neighbour.
 */
व्योम rose_add_loopback_neigh(व्योम)
अणु
	काष्ठा rose_neigh *sn;

	rose_loopback_neigh = kदो_स्मृति(माप(काष्ठा rose_neigh), GFP_KERNEL);
	अगर (!rose_loopback_neigh)
		वापस;
	sn = rose_loopback_neigh;

	sn->callsign  = null_ax25_address;
	sn->digipeat  = शून्य;
	sn->ax25      = शून्य;
	sn->dev       = शून्य;
	sn->count     = 0;
	sn->use       = 0;
	sn->dce_mode  = 1;
	sn->loopback  = 1;
	sn->number    = rose_neigh_no++;
	sn->restarted = 1;

	skb_queue_head_init(&sn->queue);

	समयr_setup(&sn->fसमयr, शून्य, 0);
	समयr_setup(&sn->t0समयr, शून्य, 0);

	spin_lock_bh(&rose_neigh_list_lock);
	sn->next = rose_neigh_list;
	rose_neigh_list           = sn;
	spin_unlock_bh(&rose_neigh_list_lock);
पूर्ण

/*
 *	Add a loopback node.
 */
पूर्णांक rose_add_loopback_node(rose_address *address)
अणु
	काष्ठा rose_node *rose_node;
	पूर्णांक err = 0;

	spin_lock_bh(&rose_node_list_lock);

	rose_node = rose_node_list;
	जबतक (rose_node != शून्य) अणु
		अगर ((rose_node->mask == 10) &&
		     (rosecmpm(address, &rose_node->address, 10) == 0) &&
		     rose_node->loopback)
			अवरोध;
		rose_node = rose_node->next;
	पूर्ण

	अगर (rose_node != शून्य)
		जाओ out;

	अगर ((rose_node = kदो_स्मृति(माप(*rose_node), GFP_ATOMIC)) == शून्य) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	rose_node->address      = *address;
	rose_node->mask         = 10;
	rose_node->count        = 1;
	rose_node->loopback     = 1;
	rose_node->neighbour[0] = rose_loopback_neigh;

	/* Insert at the head of list. Address is always mask=10 */
	rose_node->next = rose_node_list;
	rose_node_list  = rose_node;

	rose_loopback_neigh->count++;

out:
	spin_unlock_bh(&rose_node_list_lock);

	वापस err;
पूर्ण

/*
 *	Delete a loopback node.
 */
व्योम rose_del_loopback_node(rose_address *address)
अणु
	काष्ठा rose_node *rose_node;

	spin_lock_bh(&rose_node_list_lock);

	rose_node = rose_node_list;
	जबतक (rose_node != शून्य) अणु
		अगर ((rose_node->mask == 10) &&
		    (rosecmpm(address, &rose_node->address, 10) == 0) &&
		    rose_node->loopback)
			अवरोध;
		rose_node = rose_node->next;
	पूर्ण

	अगर (rose_node == शून्य)
		जाओ out;

	rose_हटाओ_node(rose_node);

	rose_loopback_neigh->count--;

out:
	spin_unlock_bh(&rose_node_list_lock);
पूर्ण

/*
 *	A device has been हटाओd. Remove its routes and neighbours.
 */
व्योम rose_rt_device_करोwn(काष्ठा net_device *dev)
अणु
	काष्ठा rose_neigh *s, *rose_neigh;
	काष्ठा rose_node  *t, *rose_node;
	पूर्णांक i;

	spin_lock_bh(&rose_node_list_lock);
	spin_lock_bh(&rose_neigh_list_lock);
	rose_neigh = rose_neigh_list;
	जबतक (rose_neigh != शून्य) अणु
		s          = rose_neigh;
		rose_neigh = rose_neigh->next;

		अगर (s->dev != dev)
			जारी;

		rose_node = rose_node_list;

		जबतक (rose_node != शून्य) अणु
			t         = rose_node;
			rose_node = rose_node->next;

			क्रम (i = 0; i < t->count; i++) अणु
				अगर (t->neighbour[i] != s)
					जारी;

				t->count--;

				चयन (i) अणु
				हाल 0:
					t->neighbour[0] = t->neighbour[1];
					fallthrough;
				हाल 1:
					t->neighbour[1] = t->neighbour[2];
					अवरोध;
				हाल 2:
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (t->count <= 0)
				rose_हटाओ_node(t);
		पूर्ण

		rose_हटाओ_neigh(s);
	पूर्ण
	spin_unlock_bh(&rose_neigh_list_lock);
	spin_unlock_bh(&rose_node_list_lock);
पूर्ण

#अगर 0 /* Currently unused */
/*
 *	A device has been हटाओd. Remove its links.
 */
व्योम rose_route_device_करोwn(काष्ठा net_device *dev)
अणु
	काष्ठा rose_route *s, *rose_route;

	spin_lock_bh(&rose_route_list_lock);
	rose_route = rose_route_list;
	जबतक (rose_route != शून्य) अणु
		s          = rose_route;
		rose_route = rose_route->next;

		अगर (s->neigh1->dev == dev || s->neigh2->dev == dev)
			rose_हटाओ_route(s);
	पूर्ण
	spin_unlock_bh(&rose_route_list_lock);
पूर्ण
#पूर्ण_अगर

/*
 *	Clear all nodes and neighbours out, except क्रम neighbours with
 *	active connections going through them.
 *  Do not clear loopback neighbour and nodes.
 */
अटल पूर्णांक rose_clear_routes(व्योम)
अणु
	काष्ठा rose_neigh *s, *rose_neigh;
	काष्ठा rose_node  *t, *rose_node;

	spin_lock_bh(&rose_node_list_lock);
	spin_lock_bh(&rose_neigh_list_lock);

	rose_neigh = rose_neigh_list;
	rose_node  = rose_node_list;

	जबतक (rose_node != शून्य) अणु
		t         = rose_node;
		rose_node = rose_node->next;
		अगर (!t->loopback)
			rose_हटाओ_node(t);
	पूर्ण

	जबतक (rose_neigh != शून्य) अणु
		s          = rose_neigh;
		rose_neigh = rose_neigh->next;

		अगर (s->use == 0 && !s->loopback) अणु
			s->count = 0;
			rose_हटाओ_neigh(s);
		पूर्ण
	पूर्ण

	spin_unlock_bh(&rose_neigh_list_lock);
	spin_unlock_bh(&rose_node_list_lock);

	वापस 0;
पूर्ण

/*
 *	Check that the device given is a valid AX.25 पूर्णांकerface that is "up".
 * 	called with RTNL
 */
अटल काष्ठा net_device *rose_ax25_dev_find(अक्षर *devname)
अणु
	काष्ठा net_device *dev;

	अगर ((dev = __dev_get_by_name(&init_net, devname)) == शून्य)
		वापस शून्य;

	अगर ((dev->flags & IFF_UP) && dev->type == ARPHRD_AX25)
		वापस dev;

	वापस शून्य;
पूर्ण

/*
 *	Find the first active ROSE device, usually "rose0".
 */
काष्ठा net_device *rose_dev_first(व्योम)
अणु
	काष्ठा net_device *dev, *first = शून्य;

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(&init_net, dev) अणु
		अगर ((dev->flags & IFF_UP) && dev->type == ARPHRD_ROSE)
			अगर (first == शून्य || म_भेदन(dev->name, first->name, 3) < 0)
				first = dev;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस first;
पूर्ण

/*
 *	Find the ROSE device क्रम the given address.
 */
काष्ठा net_device *rose_dev_get(rose_address *addr)
अणु
	काष्ठा net_device *dev;

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(&init_net, dev) अणु
		अगर ((dev->flags & IFF_UP) && dev->type == ARPHRD_ROSE && rosecmp(addr, (rose_address *)dev->dev_addr) == 0) अणु
			dev_hold(dev);
			जाओ out;
		पूर्ण
	पूर्ण
	dev = शून्य;
out:
	rcu_पढ़ो_unlock();
	वापस dev;
पूर्ण

अटल पूर्णांक rose_dev_exists(rose_address *addr)
अणु
	काष्ठा net_device *dev;

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(&init_net, dev) अणु
		अगर ((dev->flags & IFF_UP) && dev->type == ARPHRD_ROSE && rosecmp(addr, (rose_address *)dev->dev_addr) == 0)
			जाओ out;
	पूर्ण
	dev = शून्य;
out:
	rcu_पढ़ो_unlock();
	वापस dev != शून्य;
पूर्ण




काष्ठा rose_route *rose_route_मुक्त_lci(अचिन्हित पूर्णांक lci, काष्ठा rose_neigh *neigh)
अणु
	काष्ठा rose_route *rose_route;

	क्रम (rose_route = rose_route_list; rose_route != शून्य; rose_route = rose_route->next)
		अगर ((rose_route->neigh1 == neigh && rose_route->lci1 == lci) ||
		    (rose_route->neigh2 == neigh && rose_route->lci2 == lci))
			वापस rose_route;

	वापस शून्य;
पूर्ण

/*
 *	Find a neighbour or a route given a ROSE address.
 */
काष्ठा rose_neigh *rose_get_neigh(rose_address *addr, अचिन्हित अक्षर *cause,
	अचिन्हित अक्षर *diagnostic, पूर्णांक route_frame)
अणु
	काष्ठा rose_neigh *res = शून्य;
	काष्ठा rose_node *node;
	पूर्णांक failed = 0;
	पूर्णांक i;

	अगर (!route_frame) spin_lock_bh(&rose_node_list_lock);
	क्रम (node = rose_node_list; node != शून्य; node = node->next) अणु
		अगर (rosecmpm(addr, &node->address, node->mask) == 0) अणु
			क्रम (i = 0; i < node->count; i++) अणु
				अगर (node->neighbour[i]->restarted) अणु
					res = node->neighbour[i];
					जाओ out;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!route_frame) अणु /* connect request */
		क्रम (node = rose_node_list; node != शून्य; node = node->next) अणु
			अगर (rosecmpm(addr, &node->address, node->mask) == 0) अणु
				क्रम (i = 0; i < node->count; i++) अणु
					अगर (!rose_fसमयr_running(node->neighbour[i])) अणु
						res = node->neighbour[i];
						जाओ out;
					पूर्ण
					failed = 1;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (failed) अणु
		*cause      = ROSE_OUT_OF_ORDER;
		*diagnostic = 0;
	पूर्ण अन्यथा अणु
		*cause      = ROSE_NOT_OBTAINABLE;
		*diagnostic = 0;
	पूर्ण

out:
	अगर (!route_frame) spin_unlock_bh(&rose_node_list_lock);
	वापस res;
पूर्ण

/*
 *	Handle the ioctls that control the routing functions.
 */
पूर्णांक rose_rt_ioctl(अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा rose_route_काष्ठा rose_route;
	काष्ठा net_device *dev;
	पूर्णांक err;

	चयन (cmd) अणु
	हाल SIOCADDRT:
		अगर (copy_from_user(&rose_route, arg, माप(काष्ठा rose_route_काष्ठा)))
			वापस -EFAULT;
		अगर ((dev = rose_ax25_dev_find(rose_route.device)) == शून्य)
			वापस -EINVAL;
		अगर (rose_dev_exists(&rose_route.address)) /* Can't add routes to ourself */
			वापस -EINVAL;
		अगर (rose_route.mask > 10) /* Mask can't be more than 10 digits */
			वापस -EINVAL;
		अगर (rose_route.ndigis > AX25_MAX_DIGIS)
			वापस -EINVAL;
		err = rose_add_node(&rose_route, dev);
		वापस err;

	हाल SIOCDELRT:
		अगर (copy_from_user(&rose_route, arg, माप(काष्ठा rose_route_काष्ठा)))
			वापस -EFAULT;
		अगर ((dev = rose_ax25_dev_find(rose_route.device)) == शून्य)
			वापस -EINVAL;
		err = rose_del_node(&rose_route, dev);
		वापस err;

	हाल SIOCRSCLRRT:
		वापस rose_clear_routes();

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rose_del_route_by_neigh(काष्ठा rose_neigh *rose_neigh)
अणु
	काष्ठा rose_route *rose_route, *s;

	rose_neigh->restarted = 0;

	rose_stop_t0समयr(rose_neigh);
	rose_start_fसमयr(rose_neigh);

	skb_queue_purge(&rose_neigh->queue);

	spin_lock_bh(&rose_route_list_lock);

	rose_route = rose_route_list;

	जबतक (rose_route != शून्य) अणु
		अगर ((rose_route->neigh1 == rose_neigh && rose_route->neigh2 == rose_neigh) ||
		    (rose_route->neigh1 == rose_neigh && rose_route->neigh2 == शून्य)       ||
		    (rose_route->neigh2 == rose_neigh && rose_route->neigh1 == शून्य)) अणु
			s = rose_route->next;
			rose_हटाओ_route(rose_route);
			rose_route = s;
			जारी;
		पूर्ण

		अगर (rose_route->neigh1 == rose_neigh) अणु
			rose_route->neigh1->use--;
			rose_route->neigh1 = शून्य;
			rose_transmit_clear_request(rose_route->neigh2, rose_route->lci2, ROSE_OUT_OF_ORDER, 0);
		पूर्ण

		अगर (rose_route->neigh2 == rose_neigh) अणु
			rose_route->neigh2->use--;
			rose_route->neigh2 = शून्य;
			rose_transmit_clear_request(rose_route->neigh1, rose_route->lci1, ROSE_OUT_OF_ORDER, 0);
		पूर्ण

		rose_route = rose_route->next;
	पूर्ण
	spin_unlock_bh(&rose_route_list_lock);
पूर्ण

/*
 * 	A level 2 link has समयd out, thereक्रमe it appears to be a poor link,
 *	then करोn't use that neighbour until it is reset. Blow away all through
 *	routes and connections using this route.
 */
व्योम rose_link_failed(ax25_cb *ax25, पूर्णांक reason)
अणु
	काष्ठा rose_neigh *rose_neigh;

	spin_lock_bh(&rose_neigh_list_lock);
	rose_neigh = rose_neigh_list;
	जबतक (rose_neigh != शून्य) अणु
		अगर (rose_neigh->ax25 == ax25)
			अवरोध;
		rose_neigh = rose_neigh->next;
	पूर्ण

	अगर (rose_neigh != शून्य) अणु
		rose_neigh->ax25 = शून्य;
		ax25_cb_put(ax25);

		rose_del_route_by_neigh(rose_neigh);
		rose_समाप्त_by_neigh(rose_neigh);
	पूर्ण
	spin_unlock_bh(&rose_neigh_list_lock);
पूर्ण

/*
 * 	A device has been "downed" हटाओ its link status. Blow away all
 *	through routes and connections that use this device.
 */
व्योम rose_link_device_करोwn(काष्ठा net_device *dev)
अणु
	काष्ठा rose_neigh *rose_neigh;

	क्रम (rose_neigh = rose_neigh_list; rose_neigh != शून्य; rose_neigh = rose_neigh->next) अणु
		अगर (rose_neigh->dev == dev) अणु
			rose_del_route_by_neigh(rose_neigh);
			rose_समाप्त_by_neigh(rose_neigh);
		पूर्ण
	पूर्ण
पूर्ण

/*
 *	Route a frame to an appropriate AX.25 connection.
 *	A शून्य ax25_cb indicates an पूर्णांकernally generated frame.
 */
पूर्णांक rose_route_frame(काष्ठा sk_buff *skb, ax25_cb *ax25)
अणु
	काष्ठा rose_neigh *rose_neigh, *new_neigh;
	काष्ठा rose_route *rose_route;
	काष्ठा rose_facilities_काष्ठा facilities;
	rose_address *src_addr, *dest_addr;
	काष्ठा sock *sk;
	अचिन्हित लघु frametype;
	अचिन्हित पूर्णांक lci, new_lci;
	अचिन्हित अक्षर cause, diagnostic;
	काष्ठा net_device *dev;
	पूर्णांक res = 0;
	अक्षर buf[11];

	अगर (skb->len < ROSE_MIN_LEN)
		वापस res;

	अगर (!ax25)
		वापस rose_loopback_queue(skb, शून्य);

	frametype = skb->data[2];
	lci = ((skb->data[0] << 8) & 0xF00) + ((skb->data[1] << 0) & 0x0FF);
	अगर (frametype == ROSE_CALL_REQUEST &&
	    (skb->len <= ROSE_CALL_REQ_FACILITIES_OFF ||
	     skb->data[ROSE_CALL_REQ_ADDR_LEN_OFF] !=
	     ROSE_CALL_REQ_ADDR_LEN_VAL))
		वापस res;
	src_addr  = (rose_address *)(skb->data + ROSE_CALL_REQ_SRC_ADDR_OFF);
	dest_addr = (rose_address *)(skb->data + ROSE_CALL_REQ_DEST_ADDR_OFF);

	spin_lock_bh(&rose_neigh_list_lock);
	spin_lock_bh(&rose_route_list_lock);

	rose_neigh = rose_neigh_list;
	जबतक (rose_neigh != शून्य) अणु
		अगर (ax25cmp(&ax25->dest_addr, &rose_neigh->callsign) == 0 &&
		    ax25->ax25_dev->dev == rose_neigh->dev)
			अवरोध;
		rose_neigh = rose_neigh->next;
	पूर्ण

	अगर (rose_neigh == शून्य) अणु
		prपूर्णांकk("rose_route : unknown neighbour or device %s\n",
		       ax2asc(buf, &ax25->dest_addr));
		जाओ out;
	पूर्ण

	/*
	 *	Obviously the link is working, halt the fसमयr.
	 */
	rose_stop_fसमयr(rose_neigh);

	/*
	 *	LCI of zero is always क्रम us, and its always a restart
	 * 	frame.
	 */
	अगर (lci == 0) अणु
		rose_link_rx_restart(skb, rose_neigh, frametype);
		जाओ out;
	पूर्ण

	/*
	 *	Find an existing socket.
	 */
	अगर ((sk = rose_find_socket(lci, rose_neigh)) != शून्य) अणु
		अगर (frametype == ROSE_CALL_REQUEST) अणु
			काष्ठा rose_sock *rose = rose_sk(sk);

			/* Remove an existing unused socket */
			rose_clear_queues(sk);
			rose->cause	 = ROSE_NETWORK_CONGESTION;
			rose->diagnostic = 0;
			rose->neighbour->use--;
			rose->neighbour	 = शून्य;
			rose->lci	 = 0;
			rose->state	 = ROSE_STATE_0;
			sk->sk_state	 = TCP_CLOSE;
			sk->sk_err	 = 0;
			sk->sk_shutकरोwn	 |= SEND_SHUTDOWN;
			अगर (!sock_flag(sk, SOCK_DEAD)) अणु
				sk->sk_state_change(sk);
				sock_set_flag(sk, SOCK_DEAD);
			पूर्ण
		पूर्ण
		अन्यथा अणु
			skb_reset_transport_header(skb);
			res = rose_process_rx_frame(sk, skb);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 *	Is is a Call Request and is it क्रम us ?
	 */
	अगर (frametype == ROSE_CALL_REQUEST)
		अगर ((dev = rose_dev_get(dest_addr)) != शून्य) अणु
			res = rose_rx_call_request(skb, dev, rose_neigh, lci);
			dev_put(dev);
			जाओ out;
		पूर्ण

	अगर (!sysctl_rose_routing_control) अणु
		rose_transmit_clear_request(rose_neigh, lci, ROSE_NOT_OBTAINABLE, 0);
		जाओ out;
	पूर्ण

	/*
	 *	Route it to the next in line अगर we have an entry क्रम it.
	 */
	rose_route = rose_route_list;
	जबतक (rose_route != शून्य) अणु
		अगर (rose_route->lci1 == lci &&
		    rose_route->neigh1 == rose_neigh) अणु
			अगर (frametype == ROSE_CALL_REQUEST) अणु
				/* F6FBB - Remove an existing unused route */
				rose_हटाओ_route(rose_route);
				अवरोध;
			पूर्ण अन्यथा अगर (rose_route->neigh2 != शून्य) अणु
				skb->data[0] &= 0xF0;
				skb->data[0] |= (rose_route->lci2 >> 8) & 0x0F;
				skb->data[1]  = (rose_route->lci2 >> 0) & 0xFF;
				rose_transmit_link(skb, rose_route->neigh2);
				अगर (frametype == ROSE_CLEAR_CONFIRMATION)
					rose_हटाओ_route(rose_route);
				res = 1;
				जाओ out;
			पूर्ण अन्यथा अणु
				अगर (frametype == ROSE_CLEAR_CONFIRMATION)
					rose_हटाओ_route(rose_route);
				जाओ out;
			पूर्ण
		पूर्ण
		अगर (rose_route->lci2 == lci &&
		    rose_route->neigh2 == rose_neigh) अणु
			अगर (frametype == ROSE_CALL_REQUEST) अणु
				/* F6FBB - Remove an existing unused route */
				rose_हटाओ_route(rose_route);
				अवरोध;
			पूर्ण अन्यथा अगर (rose_route->neigh1 != शून्य) अणु
				skb->data[0] &= 0xF0;
				skb->data[0] |= (rose_route->lci1 >> 8) & 0x0F;
				skb->data[1]  = (rose_route->lci1 >> 0) & 0xFF;
				rose_transmit_link(skb, rose_route->neigh1);
				अगर (frametype == ROSE_CLEAR_CONFIRMATION)
					rose_हटाओ_route(rose_route);
				res = 1;
				जाओ out;
			पूर्ण अन्यथा अणु
				अगर (frametype == ROSE_CLEAR_CONFIRMATION)
					rose_हटाओ_route(rose_route);
				जाओ out;
			पूर्ण
		पूर्ण
		rose_route = rose_route->next;
	पूर्ण

	/*
	 *	We know that:
	 *	1. The frame isn't क्रम us,
	 *	2. It isn't "owned" by any existing route.
	 */
	अगर (frametype != ROSE_CALL_REQUEST) अणु	/* XXX */
		res = 0;
		जाओ out;
	पूर्ण

	स_रखो(&facilities, 0x00, माप(काष्ठा rose_facilities_काष्ठा));

	अगर (!rose_parse_facilities(skb->data + ROSE_CALL_REQ_FACILITIES_OFF,
				   skb->len - ROSE_CALL_REQ_FACILITIES_OFF,
				   &facilities)) अणु
		rose_transmit_clear_request(rose_neigh, lci, ROSE_INVALID_FACILITY, 76);
		जाओ out;
	पूर्ण

	/*
	 *	Check क्रम routing loops.
	 */
	rose_route = rose_route_list;
	जबतक (rose_route != शून्य) अणु
		अगर (rose_route->अक्रम == facilities.अक्रम &&
		    rosecmp(src_addr, &rose_route->src_addr) == 0 &&
		    ax25cmp(&facilities.dest_call, &rose_route->src_call) == 0 &&
		    ax25cmp(&facilities.source_call, &rose_route->dest_call) == 0) अणु
			rose_transmit_clear_request(rose_neigh, lci, ROSE_NOT_OBTAINABLE, 120);
			जाओ out;
		पूर्ण
		rose_route = rose_route->next;
	पूर्ण

	अगर ((new_neigh = rose_get_neigh(dest_addr, &cause, &diagnostic, 1)) == शून्य) अणु
		rose_transmit_clear_request(rose_neigh, lci, cause, diagnostic);
		जाओ out;
	पूर्ण

	अगर ((new_lci = rose_new_lci(new_neigh)) == 0) अणु
		rose_transmit_clear_request(rose_neigh, lci, ROSE_NETWORK_CONGESTION, 71);
		जाओ out;
	पूर्ण

	अगर ((rose_route = kदो_स्मृति(माप(*rose_route), GFP_ATOMIC)) == शून्य) अणु
		rose_transmit_clear_request(rose_neigh, lci, ROSE_NETWORK_CONGESTION, 120);
		जाओ out;
	पूर्ण

	rose_route->lci1      = lci;
	rose_route->src_addr  = *src_addr;
	rose_route->dest_addr = *dest_addr;
	rose_route->src_call  = facilities.dest_call;
	rose_route->dest_call = facilities.source_call;
	rose_route->अक्रम      = facilities.अक्रम;
	rose_route->neigh1    = rose_neigh;
	rose_route->lci2      = new_lci;
	rose_route->neigh2    = new_neigh;

	rose_route->neigh1->use++;
	rose_route->neigh2->use++;

	rose_route->next = rose_route_list;
	rose_route_list  = rose_route;

	skb->data[0] &= 0xF0;
	skb->data[0] |= (rose_route->lci2 >> 8) & 0x0F;
	skb->data[1]  = (rose_route->lci2 >> 0) & 0xFF;

	rose_transmit_link(skb, rose_route->neigh2);
	res = 1;

out:
	spin_unlock_bh(&rose_route_list_lock);
	spin_unlock_bh(&rose_neigh_list_lock);

	वापस res;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

अटल व्योम *rose_node_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(rose_node_list_lock)
अणु
	काष्ठा rose_node *rose_node;
	पूर्णांक i = 1;

	spin_lock_bh(&rose_node_list_lock);
	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	क्रम (rose_node = rose_node_list; rose_node && i < *pos;
	     rose_node = rose_node->next, ++i);

	वापस (i == *pos) ? rose_node : शून्य;
पूर्ण

अटल व्योम *rose_node_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	++*pos;

	वापस (v == SEQ_START_TOKEN) ? rose_node_list
		: ((काष्ठा rose_node *)v)->next;
पूर्ण

अटल व्योम rose_node_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(rose_node_list_lock)
अणु
	spin_unlock_bh(&rose_node_list_lock);
पूर्ण

अटल पूर्णांक rose_node_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अक्षर rsbuf[11];
	पूर्णांक i;

	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, "address    mask n neigh neigh neigh\n");
	अन्यथा अणु
		स्थिर काष्ठा rose_node *rose_node = v;
		/* अगर (rose_node->loopback) अणु
			seq_म_लिखो(seq, "%-10s %04d 1 loopback\n",
				   rose2asc(rsbuf, &rose_node->address),
				   rose_node->mask);
		पूर्ण अन्यथा अणु */
			seq_म_लिखो(seq, "%-10s %04d %d",
				   rose2asc(rsbuf, &rose_node->address),
				   rose_node->mask,
				   rose_node->count);

			क्रम (i = 0; i < rose_node->count; i++)
				seq_म_लिखो(seq, " %05d",
					rose_node->neighbour[i]->number);

			seq_माला_दो(seq, "\n");
		/* पूर्ण */
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा seq_operations rose_node_seqops = अणु
	.start = rose_node_start,
	.next = rose_node_next,
	.stop = rose_node_stop,
	.show = rose_node_show,
पूर्ण;

अटल व्योम *rose_neigh_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(rose_neigh_list_lock)
अणु
	काष्ठा rose_neigh *rose_neigh;
	पूर्णांक i = 1;

	spin_lock_bh(&rose_neigh_list_lock);
	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	क्रम (rose_neigh = rose_neigh_list; rose_neigh && i < *pos;
	     rose_neigh = rose_neigh->next, ++i);

	वापस (i == *pos) ? rose_neigh : शून्य;
पूर्ण

अटल व्योम *rose_neigh_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	++*pos;

	वापस (v == SEQ_START_TOKEN) ? rose_neigh_list
		: ((काष्ठा rose_neigh *)v)->next;
पूर्ण

अटल व्योम rose_neigh_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(rose_neigh_list_lock)
अणु
	spin_unlock_bh(&rose_neigh_list_lock);
पूर्ण

अटल पूर्णांक rose_neigh_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अक्षर buf[11];
	पूर्णांक i;

	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq,
			 "addr  callsign  dev  count use mode restart  t0  tf digipeaters\n");
	अन्यथा अणु
		काष्ठा rose_neigh *rose_neigh = v;

		/* अगर (!rose_neigh->loopback) अणु */
		seq_म_लिखो(seq, "%05d %-9s %-4s   %3d %3d  %3s     %3s %3lu %3lu",
			   rose_neigh->number,
			   (rose_neigh->loopback) ? "RSLOOP-0" : ax2asc(buf, &rose_neigh->callsign),
			   rose_neigh->dev ? rose_neigh->dev->name : "???",
			   rose_neigh->count,
			   rose_neigh->use,
			   (rose_neigh->dce_mode) ? "DCE" : "DTE",
			   (rose_neigh->restarted) ? "yes" : "no",
			   ax25_display_समयr(&rose_neigh->t0समयr) / HZ,
			   ax25_display_समयr(&rose_neigh->fसमयr)  / HZ);

		अगर (rose_neigh->digipeat != शून्य) अणु
			क्रम (i = 0; i < rose_neigh->digipeat->ndigi; i++)
				seq_म_लिखो(seq, " %s", ax2asc(buf, &rose_neigh->digipeat->calls[i]));
		पूर्ण

		seq_माला_दो(seq, "\n");
	पूर्ण
	वापस 0;
पूर्ण


स्थिर काष्ठा seq_operations rose_neigh_seqops = अणु
	.start = rose_neigh_start,
	.next = rose_neigh_next,
	.stop = rose_neigh_stop,
	.show = rose_neigh_show,
पूर्ण;

अटल व्योम *rose_route_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(rose_route_list_lock)
अणु
	काष्ठा rose_route *rose_route;
	पूर्णांक i = 1;

	spin_lock_bh(&rose_route_list_lock);
	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	क्रम (rose_route = rose_route_list; rose_route && i < *pos;
	     rose_route = rose_route->next, ++i);

	वापस (i == *pos) ? rose_route : शून्य;
पूर्ण

अटल व्योम *rose_route_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	++*pos;

	वापस (v == SEQ_START_TOKEN) ? rose_route_list
		: ((काष्ठा rose_route *)v)->next;
पूर्ण

अटल व्योम rose_route_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(rose_route_list_lock)
अणु
	spin_unlock_bh(&rose_route_list_lock);
पूर्ण

अटल पूर्णांक rose_route_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अक्षर buf[11], rsbuf[11];

	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq,
			 "lci  address     callsign   neigh  <-> lci  address     callsign   neigh\n");
	अन्यथा अणु
		काष्ठा rose_route *rose_route = v;

		अगर (rose_route->neigh1)
			seq_म_लिखो(seq,
				   "%3.3X  %-10s  %-9s  %05d      ",
				   rose_route->lci1,
				   rose2asc(rsbuf, &rose_route->src_addr),
				   ax2asc(buf, &rose_route->src_call),
				   rose_route->neigh1->number);
		अन्यथा
			seq_माला_दो(seq,
				 "000  *           *          00000      ");

		अगर (rose_route->neigh2)
			seq_म_लिखो(seq,
				   "%3.3X  %-10s  %-9s  %05d\n",
				   rose_route->lci2,
				   rose2asc(rsbuf, &rose_route->dest_addr),
				   ax2asc(buf, &rose_route->dest_call),
				   rose_route->neigh2->number);
		 अन्यथा
			 seq_माला_दो(seq,
				  "000  *           *          00000\n");
		पूर्ण
	वापस 0;
पूर्ण

काष्ठा seq_operations rose_route_seqops = अणु
	.start = rose_route_start,
	.next = rose_route_next,
	.stop = rose_route_stop,
	.show = rose_route_show,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PROC_FS */

/*
 *	Release all memory associated with ROSE routing काष्ठाures.
 */
व्योम __निकास rose_rt_मुक्त(व्योम)
अणु
	काष्ठा rose_neigh *s, *rose_neigh = rose_neigh_list;
	काष्ठा rose_node  *t, *rose_node  = rose_node_list;
	काष्ठा rose_route *u, *rose_route = rose_route_list;

	जबतक (rose_neigh != शून्य) अणु
		s          = rose_neigh;
		rose_neigh = rose_neigh->next;

		rose_हटाओ_neigh(s);
	पूर्ण

	जबतक (rose_node != शून्य) अणु
		t         = rose_node;
		rose_node = rose_node->next;

		rose_हटाओ_node(t);
	पूर्ण

	जबतक (rose_route != शून्य) अणु
		u          = rose_route;
		rose_route = rose_route->next;

		rose_हटाओ_route(u);
	पूर्ण
पूर्ण
