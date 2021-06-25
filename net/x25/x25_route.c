<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	X.25 Packet Layer release 002
 *
 *	This is ALPHA test software. This code may अवरोध your machine,
 *	अक्रमomly fail to work with new releases, misbehave and/or generally
 *	screw up. It might even work.
 *
 *	This code REQUIRES 2.1.15 or higher
 *
 *	History
 *	X.25 001	Jonathan Naylor	Started coding.
 */

#समावेश <linux/अगर_arp.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <net/x25.h>

LIST_HEAD(x25_route_list);
DEFINE_RWLOCK(x25_route_list_lock);

/*
 *	Add a new route.
 */
अटल पूर्णांक x25_add_route(काष्ठा x25_address *address, अचिन्हित पूर्णांक sigdigits,
			 काष्ठा net_device *dev)
अणु
	काष्ठा x25_route *rt;
	काष्ठा list_head *entry;
	पूर्णांक rc = -EINVAL;

	ग_लिखो_lock_bh(&x25_route_list_lock);

	list_क्रम_each(entry, &x25_route_list) अणु
		rt = list_entry(entry, काष्ठा x25_route, node);

		अगर (!स_भेद(&rt->address, address, sigdigits) &&
		    rt->sigdigits == sigdigits)
			जाओ out;
	पूर्ण

	rt = kदो_स्मृति(माप(*rt), GFP_ATOMIC);
	rc = -ENOMEM;
	अगर (!rt)
		जाओ out;

	म_नकल(rt->address.x25_addr, "000000000000000");
	स_नकल(rt->address.x25_addr, address->x25_addr, sigdigits);

	rt->sigdigits = sigdigits;
	rt->dev       = dev;
	refcount_set(&rt->refcnt, 1);

	list_add(&rt->node, &x25_route_list);
	rc = 0;
out:
	ग_लिखो_unlock_bh(&x25_route_list_lock);
	वापस rc;
पूर्ण

/**
 * __x25_हटाओ_route - हटाओ route from x25_route_list
 * @rt: route to हटाओ
 *
 * Remove route from x25_route_list. If it was there.
 * Caller must hold x25_route_list_lock.
 */
अटल व्योम __x25_हटाओ_route(काष्ठा x25_route *rt)
अणु
	अगर (rt->node.next) अणु
		list_del(&rt->node);
		x25_route_put(rt);
	पूर्ण
पूर्ण

अटल पूर्णांक x25_del_route(काष्ठा x25_address *address, अचिन्हित पूर्णांक sigdigits,
			 काष्ठा net_device *dev)
अणु
	काष्ठा x25_route *rt;
	काष्ठा list_head *entry;
	पूर्णांक rc = -EINVAL;

	ग_लिखो_lock_bh(&x25_route_list_lock);

	list_क्रम_each(entry, &x25_route_list) अणु
		rt = list_entry(entry, काष्ठा x25_route, node);

		अगर (!स_भेद(&rt->address, address, sigdigits) &&
		    rt->sigdigits == sigdigits && rt->dev == dev) अणु
			__x25_हटाओ_route(rt);
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	ग_लिखो_unlock_bh(&x25_route_list_lock);
	वापस rc;
पूर्ण

/*
 *	A device has been हटाओd, हटाओ its routes.
 */
व्योम x25_route_device_करोwn(काष्ठा net_device *dev)
अणु
	काष्ठा x25_route *rt;
	काष्ठा list_head *entry, *पंचांगp;

	ग_लिखो_lock_bh(&x25_route_list_lock);

	list_क्रम_each_safe(entry, पंचांगp, &x25_route_list) अणु
		rt = list_entry(entry, काष्ठा x25_route, node);

		अगर (rt->dev == dev)
			__x25_हटाओ_route(rt);
	पूर्ण
	ग_लिखो_unlock_bh(&x25_route_list_lock);
पूर्ण

/*
 *	Check that the device given is a valid X.25 पूर्णांकerface that is "up".
 */
काष्ठा net_device *x25_dev_get(अक्षर *devname)
अणु
	काष्ठा net_device *dev = dev_get_by_name(&init_net, devname);

	अगर (dev && (!(dev->flags & IFF_UP) || dev->type != ARPHRD_X25)) अणु
		dev_put(dev);
		dev = शून्य;
	पूर्ण

	वापस dev;
पूर्ण

/**
 * 	x25_get_route -	Find a route given an X.25 address.
 *	@addr: - address to find a route क्रम
 *
 * 	Find a route given an X.25 address.
 */
काष्ठा x25_route *x25_get_route(काष्ठा x25_address *addr)
अणु
	काष्ठा x25_route *rt, *use = शून्य;
	काष्ठा list_head *entry;

	पढ़ो_lock_bh(&x25_route_list_lock);

	list_क्रम_each(entry, &x25_route_list) अणु
		rt = list_entry(entry, काष्ठा x25_route, node);

		अगर (!स_भेद(&rt->address, addr, rt->sigdigits)) अणु
			अगर (!use)
				use = rt;
			अन्यथा अगर (rt->sigdigits > use->sigdigits)
				use = rt;
		पूर्ण
	पूर्ण

	अगर (use)
		x25_route_hold(use);

	पढ़ो_unlock_bh(&x25_route_list_lock);
	वापस use;
पूर्ण

/*
 *	Handle the ioctls that control the routing functions.
 */
पूर्णांक x25_route_ioctl(अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा x25_route_काष्ठा rt;
	काष्ठा net_device *dev;
	पूर्णांक rc = -EINVAL;

	अगर (cmd != SIOCADDRT && cmd != SIOCDELRT)
		जाओ out;

	rc = -EFAULT;
	अगर (copy_from_user(&rt, arg, माप(rt)))
		जाओ out;

	rc = -EINVAL;
	अगर (rt.sigdigits > 15)
		जाओ out;

	dev = x25_dev_get(rt.device);
	अगर (!dev)
		जाओ out;

	अगर (cmd == SIOCADDRT)
		rc = x25_add_route(&rt.address, rt.sigdigits, dev);
	अन्यथा
		rc = x25_del_route(&rt.address, rt.sigdigits, dev);
	dev_put(dev);
out:
	वापस rc;
पूर्ण

/*
 *	Release all memory associated with X.25 routing काष्ठाures.
 */
व्योम __निकास x25_route_मुक्त(व्योम)
अणु
	काष्ठा x25_route *rt;
	काष्ठा list_head *entry, *पंचांगp;

	ग_लिखो_lock_bh(&x25_route_list_lock);
	list_क्रम_each_safe(entry, पंचांगp, &x25_route_list) अणु
		rt = list_entry(entry, काष्ठा x25_route, node);
		__x25_हटाओ_route(rt);
	पूर्ण
	ग_लिखो_unlock_bh(&x25_route_list_lock);
पूर्ण
