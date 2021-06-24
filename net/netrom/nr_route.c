<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 * Copyright Alan Cox GW4PTS (alan@lxorguk.ukuu.org.uk)
 * Copyright Tomi Manninen OH2BNS (oh2bns@sral.fi)
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
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/termios.h>	/* For TIOCINQ/OUTQ */
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <net/netrom.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/export.h>

अटल अचिन्हित पूर्णांक nr_neigh_no = 1;

अटल HLIST_HEAD(nr_node_list);
अटल DEFINE_SPINLOCK(nr_node_list_lock);
अटल HLIST_HEAD(nr_neigh_list);
अटल DEFINE_SPINLOCK(nr_neigh_list_lock);

अटल काष्ठा nr_node *nr_node_get(ax25_address *callsign)
अणु
	काष्ठा nr_node *found = शून्य;
	काष्ठा nr_node *nr_node;

	spin_lock_bh(&nr_node_list_lock);
	nr_node_क्रम_each(nr_node, &nr_node_list)
		अगर (ax25cmp(callsign, &nr_node->callsign) == 0) अणु
			nr_node_hold(nr_node);
			found = nr_node;
			अवरोध;
		पूर्ण
	spin_unlock_bh(&nr_node_list_lock);
	वापस found;
पूर्ण

अटल काष्ठा nr_neigh *nr_neigh_get_dev(ax25_address *callsign,
					 काष्ठा net_device *dev)
अणु
	काष्ठा nr_neigh *found = शून्य;
	काष्ठा nr_neigh *nr_neigh;

	spin_lock_bh(&nr_neigh_list_lock);
	nr_neigh_क्रम_each(nr_neigh, &nr_neigh_list)
		अगर (ax25cmp(callsign, &nr_neigh->callsign) == 0 &&
		    nr_neigh->dev == dev) अणु
			nr_neigh_hold(nr_neigh);
			found = nr_neigh;
			अवरोध;
		पूर्ण
	spin_unlock_bh(&nr_neigh_list_lock);
	वापस found;
पूर्ण

अटल व्योम nr_हटाओ_neigh(काष्ठा nr_neigh *);

/*      re-sort the routes in quality order.    */
अटल व्योम re_sort_routes(काष्ठा nr_node *nr_node, पूर्णांक x, पूर्णांक y)
अणु
	अगर (nr_node->routes[y].quality > nr_node->routes[x].quality) अणु
		अगर (nr_node->which == x)
			nr_node->which = y;
		अन्यथा अगर (nr_node->which == y)
			nr_node->which = x;

		swap(nr_node->routes[x], nr_node->routes[y]);
	पूर्ण
पूर्ण

/*
 *	Add a new route to a node, and in the process add the node and the
 *	neighbour अगर it is new.
 */
अटल पूर्णांक __must_check nr_add_node(ax25_address *nr, स्थिर अक्षर *mnemonic,
	ax25_address *ax25, ax25_digi *ax25_digi, काष्ठा net_device *dev,
	पूर्णांक quality, पूर्णांक obs_count)
अणु
	काष्ठा nr_node  *nr_node;
	काष्ठा nr_neigh *nr_neigh;
	पूर्णांक i, found;
	काष्ठा net_device *odev;

	अगर ((odev=nr_dev_get(nr)) != शून्य) अणु	/* Can't add routes to ourself */
		dev_put(odev);
		वापस -EINVAL;
	पूर्ण

	nr_node = nr_node_get(nr);

	nr_neigh = nr_neigh_get_dev(ax25, dev);

	/*
	 * The L2 link to a neighbour has failed in the past
	 * and now a frame comes from this neighbour. We assume
	 * it was a temporary trouble with the link and reset the
	 * routes now (and not रुको क्रम a node broadcast).
	 */
	अगर (nr_neigh != शून्य && nr_neigh->failed != 0 && quality == 0) अणु
		काष्ठा nr_node *nr_nodet;

		spin_lock_bh(&nr_node_list_lock);
		nr_node_क्रम_each(nr_nodet, &nr_node_list) अणु
			nr_node_lock(nr_nodet);
			क्रम (i = 0; i < nr_nodet->count; i++)
				अगर (nr_nodet->routes[i].neighbour == nr_neigh)
					अगर (i < nr_nodet->which)
						nr_nodet->which = i;
			nr_node_unlock(nr_nodet);
		पूर्ण
		spin_unlock_bh(&nr_node_list_lock);
	पूर्ण

	अगर (nr_neigh != शून्य)
		nr_neigh->failed = 0;

	अगर (quality == 0 && nr_neigh != शून्य && nr_node != शून्य) अणु
		nr_neigh_put(nr_neigh);
		nr_node_put(nr_node);
		वापस 0;
	पूर्ण

	अगर (nr_neigh == शून्य) अणु
		अगर ((nr_neigh = kदो_स्मृति(माप(*nr_neigh), GFP_ATOMIC)) == शून्य) अणु
			अगर (nr_node)
				nr_node_put(nr_node);
			वापस -ENOMEM;
		पूर्ण

		nr_neigh->callsign = *ax25;
		nr_neigh->digipeat = शून्य;
		nr_neigh->ax25     = शून्य;
		nr_neigh->dev      = dev;
		nr_neigh->quality  = sysctl_netrom_शेष_path_quality;
		nr_neigh->locked   = 0;
		nr_neigh->count    = 0;
		nr_neigh->number   = nr_neigh_no++;
		nr_neigh->failed   = 0;
		refcount_set(&nr_neigh->refcount, 1);

		अगर (ax25_digi != शून्य && ax25_digi->ndigi > 0) अणु
			nr_neigh->digipeat = kmemdup(ax25_digi,
						     माप(*ax25_digi),
						     GFP_KERNEL);
			अगर (nr_neigh->digipeat == शून्य) अणु
				kमुक्त(nr_neigh);
				अगर (nr_node)
					nr_node_put(nr_node);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		spin_lock_bh(&nr_neigh_list_lock);
		hlist_add_head(&nr_neigh->neigh_node, &nr_neigh_list);
		nr_neigh_hold(nr_neigh);
		spin_unlock_bh(&nr_neigh_list_lock);
	पूर्ण

	अगर (quality != 0 && ax25cmp(nr, ax25) == 0 && !nr_neigh->locked)
		nr_neigh->quality = quality;

	अगर (nr_node == शून्य) अणु
		अगर ((nr_node = kदो_स्मृति(माप(*nr_node), GFP_ATOMIC)) == शून्य) अणु
			अगर (nr_neigh)
				nr_neigh_put(nr_neigh);
			वापस -ENOMEM;
		पूर्ण

		nr_node->callsign = *nr;
		म_नकल(nr_node->mnemonic, mnemonic);

		nr_node->which = 0;
		nr_node->count = 1;
		refcount_set(&nr_node->refcount, 1);
		spin_lock_init(&nr_node->node_lock);

		nr_node->routes[0].quality   = quality;
		nr_node->routes[0].obs_count = obs_count;
		nr_node->routes[0].neighbour = nr_neigh;

		nr_neigh_hold(nr_neigh);
		nr_neigh->count++;

		spin_lock_bh(&nr_node_list_lock);
		hlist_add_head(&nr_node->node_node, &nr_node_list);
		/* refcount initialized at 1 */
		spin_unlock_bh(&nr_node_list_lock);

		nr_neigh_put(nr_neigh);
		वापस 0;
	पूर्ण
	nr_node_lock(nr_node);

	अगर (quality != 0)
		म_नकल(nr_node->mnemonic, mnemonic);

	क्रम (found = 0, i = 0; i < nr_node->count; i++) अणु
		अगर (nr_node->routes[i].neighbour == nr_neigh) अणु
			nr_node->routes[i].quality   = quality;
			nr_node->routes[i].obs_count = obs_count;
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		/* We have space at the bottom, slot it in */
		अगर (nr_node->count < 3) अणु
			nr_node->routes[2] = nr_node->routes[1];
			nr_node->routes[1] = nr_node->routes[0];

			nr_node->routes[0].quality   = quality;
			nr_node->routes[0].obs_count = obs_count;
			nr_node->routes[0].neighbour = nr_neigh;

			nr_node->which++;
			nr_node->count++;
			nr_neigh_hold(nr_neigh);
			nr_neigh->count++;
		पूर्ण अन्यथा अणु
			/* It must be better than the worst */
			अगर (quality > nr_node->routes[2].quality) अणु
				nr_node->routes[2].neighbour->count--;
				nr_neigh_put(nr_node->routes[2].neighbour);

				अगर (nr_node->routes[2].neighbour->count == 0 && !nr_node->routes[2].neighbour->locked)
					nr_हटाओ_neigh(nr_node->routes[2].neighbour);

				nr_node->routes[2].quality   = quality;
				nr_node->routes[2].obs_count = obs_count;
				nr_node->routes[2].neighbour = nr_neigh;

				nr_neigh_hold(nr_neigh);
				nr_neigh->count++;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Now re-sort the routes in quality order */
	चयन (nr_node->count) अणु
	हाल 3:
		re_sort_routes(nr_node, 0, 1);
		re_sort_routes(nr_node, 1, 2);
		fallthrough;
	हाल 2:
		re_sort_routes(nr_node, 0, 1);
	हाल 1:
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < nr_node->count; i++) अणु
		अगर (nr_node->routes[i].neighbour == nr_neigh) अणु
			अगर (i < nr_node->which)
				nr_node->which = i;
			अवरोध;
		पूर्ण
	पूर्ण

	nr_neigh_put(nr_neigh);
	nr_node_unlock(nr_node);
	nr_node_put(nr_node);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __nr_हटाओ_node(काष्ठा nr_node *nr_node)
अणु
	hlist_del_init(&nr_node->node_node);
	nr_node_put(nr_node);
पूर्ण

#घोषणा nr_हटाओ_node_locked(__node) \
	__nr_हटाओ_node(__node)

अटल व्योम nr_हटाओ_node(काष्ठा nr_node *nr_node)
अणु
	spin_lock_bh(&nr_node_list_lock);
	__nr_हटाओ_node(nr_node);
	spin_unlock_bh(&nr_node_list_lock);
पूर्ण

अटल अंतरभूत व्योम __nr_हटाओ_neigh(काष्ठा nr_neigh *nr_neigh)
अणु
	hlist_del_init(&nr_neigh->neigh_node);
	nr_neigh_put(nr_neigh);
पूर्ण

#घोषणा nr_हटाओ_neigh_locked(__neigh) \
	__nr_हटाओ_neigh(__neigh)

अटल व्योम nr_हटाओ_neigh(काष्ठा nr_neigh *nr_neigh)
अणु
	spin_lock_bh(&nr_neigh_list_lock);
	__nr_हटाओ_neigh(nr_neigh);
	spin_unlock_bh(&nr_neigh_list_lock);
पूर्ण

/*
 *	"Delete" a node. Strictly speaking हटाओ a route to a node. The node
 *	is only deleted अगर no routes are left to it.
 */
अटल पूर्णांक nr_del_node(ax25_address *callsign, ax25_address *neighbour, काष्ठा net_device *dev)
अणु
	काष्ठा nr_node  *nr_node;
	काष्ठा nr_neigh *nr_neigh;
	पूर्णांक i;

	nr_node = nr_node_get(callsign);

	अगर (nr_node == शून्य)
		वापस -EINVAL;

	nr_neigh = nr_neigh_get_dev(neighbour, dev);

	अगर (nr_neigh == शून्य) अणु
		nr_node_put(nr_node);
		वापस -EINVAL;
	पूर्ण

	nr_node_lock(nr_node);
	क्रम (i = 0; i < nr_node->count; i++) अणु
		अगर (nr_node->routes[i].neighbour == nr_neigh) अणु
			nr_neigh->count--;
			nr_neigh_put(nr_neigh);

			अगर (nr_neigh->count == 0 && !nr_neigh->locked)
				nr_हटाओ_neigh(nr_neigh);
			nr_neigh_put(nr_neigh);

			nr_node->count--;

			अगर (nr_node->count == 0) अणु
				nr_हटाओ_node(nr_node);
			पूर्ण अन्यथा अणु
				चयन (i) अणु
				हाल 0:
					nr_node->routes[0] = nr_node->routes[1];
					fallthrough;
				हाल 1:
					nr_node->routes[1] = nr_node->routes[2];
				हाल 2:
					अवरोध;
				पूर्ण
				nr_node_put(nr_node);
			पूर्ण
			nr_node_unlock(nr_node);

			वापस 0;
		पूर्ण
	पूर्ण
	nr_neigh_put(nr_neigh);
	nr_node_unlock(nr_node);
	nr_node_put(nr_node);

	वापस -EINVAL;
पूर्ण

/*
 *	Lock a neighbour with a quality.
 */
अटल पूर्णांक __must_check nr_add_neigh(ax25_address *callsign,
	ax25_digi *ax25_digi, काष्ठा net_device *dev, अचिन्हित पूर्णांक quality)
अणु
	काष्ठा nr_neigh *nr_neigh;

	nr_neigh = nr_neigh_get_dev(callsign, dev);
	अगर (nr_neigh) अणु
		nr_neigh->quality = quality;
		nr_neigh->locked  = 1;
		nr_neigh_put(nr_neigh);
		वापस 0;
	पूर्ण

	अगर ((nr_neigh = kदो_स्मृति(माप(*nr_neigh), GFP_ATOMIC)) == शून्य)
		वापस -ENOMEM;

	nr_neigh->callsign = *callsign;
	nr_neigh->digipeat = शून्य;
	nr_neigh->ax25     = शून्य;
	nr_neigh->dev      = dev;
	nr_neigh->quality  = quality;
	nr_neigh->locked   = 1;
	nr_neigh->count    = 0;
	nr_neigh->number   = nr_neigh_no++;
	nr_neigh->failed   = 0;
	refcount_set(&nr_neigh->refcount, 1);

	अगर (ax25_digi != शून्य && ax25_digi->ndigi > 0) अणु
		nr_neigh->digipeat = kmemdup(ax25_digi, माप(*ax25_digi),
					     GFP_KERNEL);
		अगर (nr_neigh->digipeat == शून्य) अणु
			kमुक्त(nr_neigh);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	spin_lock_bh(&nr_neigh_list_lock);
	hlist_add_head(&nr_neigh->neigh_node, &nr_neigh_list);
	/* refcount is initialized at 1 */
	spin_unlock_bh(&nr_neigh_list_lock);

	वापस 0;
पूर्ण

/*
 *	"Delete" a neighbour. The neighbour is only हटाओd अगर the number
 *	of nodes that may use it is zero.
 */
अटल पूर्णांक nr_del_neigh(ax25_address *callsign, काष्ठा net_device *dev, अचिन्हित पूर्णांक quality)
अणु
	काष्ठा nr_neigh *nr_neigh;

	nr_neigh = nr_neigh_get_dev(callsign, dev);

	अगर (nr_neigh == शून्य) वापस -EINVAL;

	nr_neigh->quality = quality;
	nr_neigh->locked  = 0;

	अगर (nr_neigh->count == 0)
		nr_हटाओ_neigh(nr_neigh);
	nr_neigh_put(nr_neigh);

	वापस 0;
पूर्ण

/*
 *	Decrement the obsolescence count by one. If a route is reduced to a
 *	count of zero, हटाओ it. Also हटाओ any unlocked neighbours with
 *	zero nodes routing via it.
 */
अटल पूर्णांक nr_dec_obs(व्योम)
अणु
	काष्ठा nr_neigh *nr_neigh;
	काष्ठा nr_node  *s;
	काष्ठा hlist_node *nodet;
	पूर्णांक i;

	spin_lock_bh(&nr_node_list_lock);
	nr_node_क्रम_each_safe(s, nodet, &nr_node_list) अणु
		nr_node_lock(s);
		क्रम (i = 0; i < s->count; i++) अणु
			चयन (s->routes[i].obs_count) अणु
			हाल 0:		/* A locked entry */
				अवरोध;

			हाल 1:		/* From 1 -> 0 */
				nr_neigh = s->routes[i].neighbour;

				nr_neigh->count--;
				nr_neigh_put(nr_neigh);

				अगर (nr_neigh->count == 0 && !nr_neigh->locked)
					nr_हटाओ_neigh(nr_neigh);

				s->count--;

				चयन (i) अणु
				हाल 0:
					s->routes[0] = s->routes[1];
					fallthrough;
				हाल 1:
					s->routes[1] = s->routes[2];
				हाल 2:
					अवरोध;
				पूर्ण
				अवरोध;

			शेष:
				s->routes[i].obs_count--;
				अवरोध;

			पूर्ण
		पूर्ण

		अगर (s->count <= 0)
			nr_हटाओ_node_locked(s);
		nr_node_unlock(s);
	पूर्ण
	spin_unlock_bh(&nr_node_list_lock);

	वापस 0;
पूर्ण

/*
 *	A device has been हटाओd. Remove its routes and neighbours.
 */
व्योम nr_rt_device_करोwn(काष्ठा net_device *dev)
अणु
	काष्ठा nr_neigh *s;
	काष्ठा hlist_node *nodet, *node2t;
	काष्ठा nr_node  *t;
	पूर्णांक i;

	spin_lock_bh(&nr_neigh_list_lock);
	nr_neigh_क्रम_each_safe(s, nodet, &nr_neigh_list) अणु
		अगर (s->dev == dev) अणु
			spin_lock_bh(&nr_node_list_lock);
			nr_node_क्रम_each_safe(t, node2t, &nr_node_list) अणु
				nr_node_lock(t);
				क्रम (i = 0; i < t->count; i++) अणु
					अगर (t->routes[i].neighbour == s) अणु
						t->count--;

						चयन (i) अणु
						हाल 0:
							t->routes[0] = t->routes[1];
							fallthrough;
						हाल 1:
							t->routes[1] = t->routes[2];
						हाल 2:
							अवरोध;
						पूर्ण
					पूर्ण
				पूर्ण

				अगर (t->count <= 0)
					nr_हटाओ_node_locked(t);
				nr_node_unlock(t);
			पूर्ण
			spin_unlock_bh(&nr_node_list_lock);

			nr_हटाओ_neigh_locked(s);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&nr_neigh_list_lock);
पूर्ण

/*
 *	Check that the device given is a valid AX.25 पूर्णांकerface that is "up".
 *	Or a valid ethernet पूर्णांकerface with an AX.25 callsign binding.
 */
अटल काष्ठा net_device *nr_ax25_dev_get(अक्षर *devname)
अणु
	काष्ठा net_device *dev;

	अगर ((dev = dev_get_by_name(&init_net, devname)) == शून्य)
		वापस शून्य;

	अगर ((dev->flags & IFF_UP) && dev->type == ARPHRD_AX25)
		वापस dev;

	dev_put(dev);
	वापस शून्य;
पूर्ण

/*
 *	Find the first active NET/ROM device, usually "nr0".
 */
काष्ठा net_device *nr_dev_first(व्योम)
अणु
	काष्ठा net_device *dev, *first = शून्य;

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(&init_net, dev) अणु
		अगर ((dev->flags & IFF_UP) && dev->type == ARPHRD_NETROM)
			अगर (first == शून्य || म_भेदन(dev->name, first->name, 3) < 0)
				first = dev;
	पूर्ण
	अगर (first)
		dev_hold(first);
	rcu_पढ़ो_unlock();

	वापस first;
पूर्ण

/*
 *	Find the NET/ROM device क्रम the given callsign.
 */
काष्ठा net_device *nr_dev_get(ax25_address *addr)
अणु
	काष्ठा net_device *dev;

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(&init_net, dev) अणु
		अगर ((dev->flags & IFF_UP) && dev->type == ARPHRD_NETROM &&
		    ax25cmp(addr, (ax25_address *)dev->dev_addr) == 0) अणु
			dev_hold(dev);
			जाओ out;
		पूर्ण
	पूर्ण
	dev = शून्य;
out:
	rcu_पढ़ो_unlock();
	वापस dev;
पूर्ण

अटल ax25_digi *nr_call_to_digi(ax25_digi *digi, पूर्णांक ndigis,
	ax25_address *digipeaters)
अणु
	पूर्णांक i;

	अगर (ndigis == 0)
		वापस शून्य;

	क्रम (i = 0; i < ndigis; i++) अणु
		digi->calls[i]    = digipeaters[i];
		digi->repeated[i] = 0;
	पूर्ण

	digi->ndigi      = ndigis;
	digi->lastrepeat = -1;

	वापस digi;
पूर्ण

/*
 *	Handle the ioctls that control the routing functions.
 */
पूर्णांक nr_rt_ioctl(अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा nr_route_काष्ठा nr_route;
	काष्ठा net_device *dev;
	ax25_digi digi;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल SIOCADDRT:
		अगर (copy_from_user(&nr_route, arg, माप(काष्ठा nr_route_काष्ठा)))
			वापस -EFAULT;
		अगर (nr_route.ndigis > AX25_MAX_DIGIS)
			वापस -EINVAL;
		अगर ((dev = nr_ax25_dev_get(nr_route.device)) == शून्य)
			वापस -EINVAL;
		चयन (nr_route.type) अणु
		हाल NETROM_NODE:
			अगर (strnlen(nr_route.mnemonic, 7) == 7) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण

			ret = nr_add_node(&nr_route.callsign,
				nr_route.mnemonic,
				&nr_route.neighbour,
				nr_call_to_digi(&digi, nr_route.ndigis,
						nr_route.digipeaters),
				dev, nr_route.quality,
				nr_route.obs_count);
			अवरोध;
		हाल NETROM_NEIGH:
			ret = nr_add_neigh(&nr_route.callsign,
				nr_call_to_digi(&digi, nr_route.ndigis,
						nr_route.digipeaters),
				dev, nr_route.quality);
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		dev_put(dev);
		वापस ret;

	हाल SIOCDELRT:
		अगर (copy_from_user(&nr_route, arg, माप(काष्ठा nr_route_काष्ठा)))
			वापस -EFAULT;
		अगर ((dev = nr_ax25_dev_get(nr_route.device)) == शून्य)
			वापस -EINVAL;
		चयन (nr_route.type) अणु
		हाल NETROM_NODE:
			ret = nr_del_node(&nr_route.callsign,
				&nr_route.neighbour, dev);
			अवरोध;
		हाल NETROM_NEIGH:
			ret = nr_del_neigh(&nr_route.callsign,
				dev, nr_route.quality);
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		dev_put(dev);
		वापस ret;

	हाल SIOCNRDECOBS:
		वापस nr_dec_obs();

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * 	A level 2 link has समयd out, thereक्रमe it appears to be a poor link,
 *	then करोn't use that neighbour until it is reset.
 */
व्योम nr_link_failed(ax25_cb *ax25, पूर्णांक reason)
अणु
	काष्ठा nr_neigh *s, *nr_neigh = शून्य;
	काष्ठा nr_node  *nr_node = शून्य;

	spin_lock_bh(&nr_neigh_list_lock);
	nr_neigh_क्रम_each(s, &nr_neigh_list) अणु
		अगर (s->ax25 == ax25) अणु
			nr_neigh_hold(s);
			nr_neigh = s;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&nr_neigh_list_lock);

	अगर (nr_neigh == शून्य)
		वापस;

	nr_neigh->ax25 = शून्य;
	ax25_cb_put(ax25);

	अगर (++nr_neigh->failed < sysctl_netrom_link_fails_count) अणु
		nr_neigh_put(nr_neigh);
		वापस;
	पूर्ण
	spin_lock_bh(&nr_node_list_lock);
	nr_node_क्रम_each(nr_node, &nr_node_list) अणु
		nr_node_lock(nr_node);
		अगर (nr_node->which < nr_node->count &&
		    nr_node->routes[nr_node->which].neighbour == nr_neigh)
			nr_node->which++;
		nr_node_unlock(nr_node);
	पूर्ण
	spin_unlock_bh(&nr_node_list_lock);
	nr_neigh_put(nr_neigh);
पूर्ण

/*
 *	Route a frame to an appropriate AX.25 connection. A शून्य ax25_cb
 *	indicates an पूर्णांकernally generated frame.
 */
पूर्णांक nr_route_frame(काष्ठा sk_buff *skb, ax25_cb *ax25)
अणु
	ax25_address *nr_src, *nr_dest;
	काष्ठा nr_neigh *nr_neigh;
	काष्ठा nr_node  *nr_node;
	काष्ठा net_device *dev;
	अचिन्हित अक्षर *dptr;
	ax25_cb *ax25s;
	पूर्णांक ret;
	काष्ठा sk_buff *skbn;


	nr_src  = (ax25_address *)(skb->data + 0);
	nr_dest = (ax25_address *)(skb->data + 7);

	अगर (ax25 != शून्य) अणु
		ret = nr_add_node(nr_src, "", &ax25->dest_addr, ax25->digipeat,
				  ax25->ax25_dev->dev, 0,
				  sysctl_netrom_obsolescence_count_initialiser);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर ((dev = nr_dev_get(nr_dest)) != शून्य) अणु	/* Its क्रम me */
		अगर (ax25 == शून्य)			/* Its from me */
			ret = nr_loopback_queue(skb);
		अन्यथा
			ret = nr_rx_frame(skb, dev);
		dev_put(dev);
		वापस ret;
	पूर्ण

	अगर (!sysctl_netrom_routing_control && ax25 != शून्य)
		वापस 0;

	/* Its Time-To-Live has expired */
	अगर (skb->data[14] == 1) अणु
		वापस 0;
	पूर्ण

	nr_node = nr_node_get(nr_dest);
	अगर (nr_node == शून्य)
		वापस 0;
	nr_node_lock(nr_node);

	अगर (nr_node->which >= nr_node->count) अणु
		nr_node_unlock(nr_node);
		nr_node_put(nr_node);
		वापस 0;
	पूर्ण

	nr_neigh = nr_node->routes[nr_node->which].neighbour;

	अगर ((dev = nr_dev_first()) == शून्य) अणु
		nr_node_unlock(nr_node);
		nr_node_put(nr_node);
		वापस 0;
	पूर्ण

	/* We are going to change the netrom headers so we should get our
	   own skb, we also did not know until now how much header space
	   we had to reserve... - RXQ */
	अगर ((skbn=skb_copy_expand(skb, dev->hard_header_len, 0, GFP_ATOMIC)) == शून्य) अणु
		nr_node_unlock(nr_node);
		nr_node_put(nr_node);
		dev_put(dev);
		वापस 0;
	पूर्ण
	kमुक्त_skb(skb);
	skb=skbn;
	skb->data[14]--;

	dptr  = skb_push(skb, 1);
	*dptr = AX25_P_NETROM;

	ax25s = nr_neigh->ax25;
	nr_neigh->ax25 = ax25_send_frame(skb, 256,
					 (ax25_address *)dev->dev_addr,
					 &nr_neigh->callsign,
					 nr_neigh->digipeat, nr_neigh->dev);
	अगर (ax25s)
		ax25_cb_put(ax25s);

	dev_put(dev);
	ret = (nr_neigh->ax25 != शून्य);
	nr_node_unlock(nr_node);
	nr_node_put(nr_node);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

अटल व्योम *nr_node_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(&nr_node_list_lock)
अणु
	spin_lock_bh(&nr_node_list_lock);
	वापस seq_hlist_start_head(&nr_node_list, *pos);
पूर्ण

अटल व्योम *nr_node_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	वापस seq_hlist_next(v, &nr_node_list, pos);
पूर्ण

अटल व्योम nr_node_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(&nr_node_list_lock)
अणु
	spin_unlock_bh(&nr_node_list_lock);
पूर्ण

अटल पूर्णांक nr_node_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अक्षर buf[11];
	पूर्णांक i;

	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq,
			 "callsign  mnemonic w n qual obs neigh qual obs neigh qual obs neigh\n");
	अन्यथा अणु
		काष्ठा nr_node *nr_node = hlist_entry(v, काष्ठा nr_node,
						      node_node);

		nr_node_lock(nr_node);
		seq_म_लिखो(seq, "%-9s %-7s  %d %d",
			ax2asc(buf, &nr_node->callsign),
			(nr_node->mnemonic[0] == '\0') ? "*" : nr_node->mnemonic,
			nr_node->which + 1,
			nr_node->count);

		क्रम (i = 0; i < nr_node->count; i++) अणु
			seq_म_लिखो(seq, "  %3d   %d %05d",
				nr_node->routes[i].quality,
				nr_node->routes[i].obs_count,
				nr_node->routes[i].neighbour->number);
		पूर्ण
		nr_node_unlock(nr_node);

		seq_माला_दो(seq, "\n");
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा seq_operations nr_node_seqops = अणु
	.start = nr_node_start,
	.next = nr_node_next,
	.stop = nr_node_stop,
	.show = nr_node_show,
पूर्ण;

अटल व्योम *nr_neigh_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(&nr_neigh_list_lock)
अणु
	spin_lock_bh(&nr_neigh_list_lock);
	वापस seq_hlist_start_head(&nr_neigh_list, *pos);
पूर्ण

अटल व्योम *nr_neigh_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	वापस seq_hlist_next(v, &nr_neigh_list, pos);
पूर्ण

अटल व्योम nr_neigh_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(&nr_neigh_list_lock)
अणु
	spin_unlock_bh(&nr_neigh_list_lock);
पूर्ण

अटल पूर्णांक nr_neigh_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अक्षर buf[11];
	पूर्णांक i;

	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, "addr  callsign  dev  qual lock count failed digipeaters\n");
	अन्यथा अणु
		काष्ठा nr_neigh *nr_neigh;

		nr_neigh = hlist_entry(v, काष्ठा nr_neigh, neigh_node);
		seq_म_लिखो(seq, "%05d %-9s %-4s  %3d    %d   %3d    %3d",
			nr_neigh->number,
			ax2asc(buf, &nr_neigh->callsign),
			nr_neigh->dev ? nr_neigh->dev->name : "???",
			nr_neigh->quality,
			nr_neigh->locked,
			nr_neigh->count,
			nr_neigh->failed);

		अगर (nr_neigh->digipeat != शून्य) अणु
			क्रम (i = 0; i < nr_neigh->digipeat->ndigi; i++)
				seq_म_लिखो(seq, " %s",
					   ax2asc(buf, &nr_neigh->digipeat->calls[i]));
		पूर्ण

		seq_माला_दो(seq, "\n");
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा seq_operations nr_neigh_seqops = अणु
	.start = nr_neigh_start,
	.next = nr_neigh_next,
	.stop = nr_neigh_stop,
	.show = nr_neigh_show,
पूर्ण;
#पूर्ण_अगर

/*
 *	Free all memory associated with the nodes and routes lists.
 */
व्योम nr_rt_मुक्त(व्योम)
अणु
	काष्ठा nr_neigh *s = शून्य;
	काष्ठा nr_node  *t = शून्य;
	काष्ठा hlist_node *nodet;

	spin_lock_bh(&nr_neigh_list_lock);
	spin_lock_bh(&nr_node_list_lock);
	nr_node_क्रम_each_safe(t, nodet, &nr_node_list) अणु
		nr_node_lock(t);
		nr_हटाओ_node_locked(t);
		nr_node_unlock(t);
	पूर्ण
	nr_neigh_क्रम_each_safe(s, nodet, &nr_neigh_list) अणु
		जबतक(s->count) अणु
			s->count--;
			nr_neigh_put(s);
		पूर्ण
		nr_हटाओ_neigh_locked(s);
	पूर्ण
	spin_unlock_bh(&nr_node_list_lock);
	spin_unlock_bh(&nr_neigh_list_lock);
पूर्ण
