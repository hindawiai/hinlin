<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/* raw.c - Raw sockets क्रम protocol family CAN
 *
 * Copyright (c) 2002-2007 Volkswagen Group Electronic Research
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of Volkswagen nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which हाल the provisions of the
 * GPL apply INSTEAD OF those given above.
 *
 * The provided data काष्ठाures and बाह्यal पूर्णांकerfaces from this code
 * are not restricted to be used by modules with a GPL compatible license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/uपन.स>
#समावेश <linux/net.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/socket.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/can.h>
#समावेश <linux/can/core.h>
#समावेश <linux/can/skb.h>
#समावेश <linux/can/raw.h>
#समावेश <net/sock.h>
#समावेश <net/net_namespace.h>

MODULE_DESCRIPTION("PF_CAN raw protocol");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Urs Thuermann <urs.thuermann@volkswagen.de>");
MODULE_ALIAS("can-proto-1");

#घोषणा RAW_MIN_NAMELEN CAN_REQUIRED_SIZE(काष्ठा sockaddr_can, can_अगरindex)

#घोषणा MASK_ALL 0

/* A raw socket has a list of can_filters attached to it, each receiving
 * the CAN frames matching that filter.  If the filter list is empty,
 * no CAN frames will be received by the socket.  The शेष after
 * खोलोing the socket, is to have one filter which receives all frames.
 * The filter list is allocated dynamically with the exception of the
 * list containing only one item.  This common हाल is optimized by
 * storing the single filter in dfilter, to aव्योम using dynamic memory.
 */

काष्ठा uniqframe अणु
	पूर्णांक skbcnt;
	स्थिर काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक join_rx_count;
पूर्ण;

काष्ठा raw_sock अणु
	काष्ठा sock sk;
	पूर्णांक bound;
	पूर्णांक अगरindex;
	काष्ठा list_head notअगरier;
	पूर्णांक loopback;
	पूर्णांक recv_own_msgs;
	पूर्णांक fd_frames;
	पूर्णांक join_filters;
	पूर्णांक count;                 /* number of active filters */
	काष्ठा can_filter dfilter; /* शेष/single filter */
	काष्ठा can_filter *filter; /* poपूर्णांकer to filter(s) */
	can_err_mask_t err_mask;
	काष्ठा uniqframe __percpu *uniq;
पूर्ण;

अटल LIST_HEAD(raw_notअगरier_list);
अटल DEFINE_SPINLOCK(raw_notअगरier_lock);
अटल काष्ठा raw_sock *raw_busy_notअगरier;

/* Return poपूर्णांकer to store the extra msg flags क्रम raw_recvmsg().
 * We use the space of one अचिन्हित पूर्णांक beyond the 'struct sockaddr_can'
 * in skb->cb.
 */
अटल अंतरभूत अचिन्हित पूर्णांक *raw_flags(काष्ठा sk_buff *skb)
अणु
	sock_skb_cb_check_size(माप(काष्ठा sockaddr_can) +
			       माप(अचिन्हित पूर्णांक));

	/* वापस poपूर्णांकer after काष्ठा sockaddr_can */
	वापस (अचिन्हित पूर्णांक *)(&((काष्ठा sockaddr_can *)skb->cb)[1]);
पूर्ण

अटल अंतरभूत काष्ठा raw_sock *raw_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा raw_sock *)sk;
पूर्ण

अटल व्योम raw_rcv(काष्ठा sk_buff *oskb, व्योम *data)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)data;
	काष्ठा raw_sock *ro = raw_sk(sk);
	काष्ठा sockaddr_can *addr;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक *pflags;

	/* check the received tx sock reference */
	अगर (!ro->recv_own_msgs && oskb->sk == sk)
		वापस;

	/* करो not pass non-CAN2.0 frames to a legacy socket */
	अगर (!ro->fd_frames && oskb->len != CAN_MTU)
		वापस;

	/* eliminate multiple filter matches क्रम the same skb */
	अगर (this_cpu_ptr(ro->uniq)->skb == oskb &&
	    this_cpu_ptr(ro->uniq)->skbcnt == can_skb_prv(oskb)->skbcnt) अणु
		अगर (ro->join_filters) अणु
			this_cpu_inc(ro->uniq->join_rx_count);
			/* drop frame until all enabled filters matched */
			अगर (this_cpu_ptr(ro->uniq)->join_rx_count < ro->count)
				वापस;
		पूर्ण अन्यथा अणु
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		this_cpu_ptr(ro->uniq)->skb = oskb;
		this_cpu_ptr(ro->uniq)->skbcnt = can_skb_prv(oskb)->skbcnt;
		this_cpu_ptr(ro->uniq)->join_rx_count = 1;
		/* drop first frame to check all enabled filters? */
		अगर (ro->join_filters && ro->count > 1)
			वापस;
	पूर्ण

	/* clone the given skb to be able to enqueue it पूर्णांकo the rcv queue */
	skb = skb_clone(oskb, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	/* Put the datagram to the queue so that raw_recvmsg() can get
	 * it from there. We need to pass the पूर्णांकerface index to
	 * raw_recvmsg(). We pass a whole काष्ठा sockaddr_can in
	 * skb->cb containing the पूर्णांकerface index.
	 */

	sock_skb_cb_check_size(माप(काष्ठा sockaddr_can));
	addr = (काष्ठा sockaddr_can *)skb->cb;
	स_रखो(addr, 0, माप(*addr));
	addr->can_family = AF_CAN;
	addr->can_अगरindex = skb->dev->अगरindex;

	/* add CAN specअगरic message flags क्रम raw_recvmsg() */
	pflags = raw_flags(skb);
	*pflags = 0;
	अगर (oskb->sk)
		*pflags |= MSG_DONTROUTE;
	अगर (oskb->sk == sk)
		*pflags |= MSG_CONFIRM;

	अगर (sock_queue_rcv_skb(sk, skb) < 0)
		kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक raw_enable_filters(काष्ठा net *net, काष्ठा net_device *dev,
			      काष्ठा sock *sk, काष्ठा can_filter *filter,
			      पूर्णांक count)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		err = can_rx_रेजिस्टर(net, dev, filter[i].can_id,
				      filter[i].can_mask,
				      raw_rcv, sk, "raw", sk);
		अगर (err) अणु
			/* clean up successfully रेजिस्टरed filters */
			जबतक (--i >= 0)
				can_rx_unरेजिस्टर(net, dev, filter[i].can_id,
						  filter[i].can_mask,
						  raw_rcv, sk);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक raw_enable_errfilter(काष्ठा net *net, काष्ठा net_device *dev,
				काष्ठा sock *sk, can_err_mask_t err_mask)
अणु
	पूर्णांक err = 0;

	अगर (err_mask)
		err = can_rx_रेजिस्टर(net, dev, 0, err_mask | CAN_ERR_FLAG,
				      raw_rcv, sk, "raw", sk);

	वापस err;
पूर्ण

अटल व्योम raw_disable_filters(काष्ठा net *net, काष्ठा net_device *dev,
				काष्ठा sock *sk, काष्ठा can_filter *filter,
				पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		can_rx_unरेजिस्टर(net, dev, filter[i].can_id,
				  filter[i].can_mask, raw_rcv, sk);
पूर्ण

अटल अंतरभूत व्योम raw_disable_errfilter(काष्ठा net *net,
					 काष्ठा net_device *dev,
					 काष्ठा sock *sk,
					 can_err_mask_t err_mask)

अणु
	अगर (err_mask)
		can_rx_unरेजिस्टर(net, dev, 0, err_mask | CAN_ERR_FLAG,
				  raw_rcv, sk);
पूर्ण

अटल अंतरभूत व्योम raw_disable_allfilters(काष्ठा net *net,
					  काष्ठा net_device *dev,
					  काष्ठा sock *sk)
अणु
	काष्ठा raw_sock *ro = raw_sk(sk);

	raw_disable_filters(net, dev, sk, ro->filter, ro->count);
	raw_disable_errfilter(net, dev, sk, ro->err_mask);
पूर्ण

अटल पूर्णांक raw_enable_allfilters(काष्ठा net *net, काष्ठा net_device *dev,
				 काष्ठा sock *sk)
अणु
	काष्ठा raw_sock *ro = raw_sk(sk);
	पूर्णांक err;

	err = raw_enable_filters(net, dev, sk, ro->filter, ro->count);
	अगर (!err) अणु
		err = raw_enable_errfilter(net, dev, sk, ro->err_mask);
		अगर (err)
			raw_disable_filters(net, dev, sk, ro->filter,
					    ro->count);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम raw_notअगरy(काष्ठा raw_sock *ro, अचिन्हित दीर्घ msg,
		       काष्ठा net_device *dev)
अणु
	काष्ठा sock *sk = &ro->sk;

	अगर (!net_eq(dev_net(dev), sock_net(sk)))
		वापस;

	अगर (ro->अगरindex != dev->अगरindex)
		वापस;

	चयन (msg) अणु
	हाल NETDEV_UNREGISTER:
		lock_sock(sk);
		/* हटाओ current filters & unरेजिस्टर */
		अगर (ro->bound)
			raw_disable_allfilters(dev_net(dev), dev, sk);

		अगर (ro->count > 1)
			kमुक्त(ro->filter);

		ro->अगरindex = 0;
		ro->bound = 0;
		ro->count = 0;
		release_sock(sk);

		sk->sk_err = ENODEV;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_error_report(sk);
		अवरोध;

	हाल NETDEV_DOWN:
		sk->sk_err = ENETDOWN;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_error_report(sk);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक raw_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ msg,
			व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (dev->type != ARPHRD_CAN)
		वापस NOTIFY_DONE;
	अगर (msg != NETDEV_UNREGISTER && msg != NETDEV_DOWN)
		वापस NOTIFY_DONE;
	अगर (unlikely(raw_busy_notअगरier)) /* Check क्रम reentrant bug. */
		वापस NOTIFY_DONE;

	spin_lock(&raw_notअगरier_lock);
	list_क्रम_each_entry(raw_busy_notअगरier, &raw_notअगरier_list, notअगरier) अणु
		spin_unlock(&raw_notअगरier_lock);
		raw_notअगरy(raw_busy_notअगरier, msg, dev);
		spin_lock(&raw_notअगरier_lock);
	पूर्ण
	raw_busy_notअगरier = शून्य;
	spin_unlock(&raw_notअगरier_lock);
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक raw_init(काष्ठा sock *sk)
अणु
	काष्ठा raw_sock *ro = raw_sk(sk);

	ro->bound            = 0;
	ro->अगरindex          = 0;

	/* set शेष filter to single entry dfilter */
	ro->dfilter.can_id   = 0;
	ro->dfilter.can_mask = MASK_ALL;
	ro->filter           = &ro->dfilter;
	ro->count            = 1;

	/* set शेष loopback behaviour */
	ro->loopback         = 1;
	ro->recv_own_msgs    = 0;
	ro->fd_frames        = 0;
	ro->join_filters     = 0;

	/* alloc_percpu provides zero'ed memory */
	ro->uniq = alloc_percpu(काष्ठा uniqframe);
	अगर (unlikely(!ro->uniq))
		वापस -ENOMEM;

	/* set notअगरier */
	spin_lock(&raw_notअगरier_lock);
	list_add_tail(&ro->notअगरier, &raw_notअगरier_list);
	spin_unlock(&raw_notअगरier_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक raw_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा raw_sock *ro;

	अगर (!sk)
		वापस 0;

	ro = raw_sk(sk);

	spin_lock(&raw_notअगरier_lock);
	जबतक (raw_busy_notअगरier == ro) अणु
		spin_unlock(&raw_notअगरier_lock);
		schedule_समयout_unपूर्णांकerruptible(1);
		spin_lock(&raw_notअगरier_lock);
	पूर्ण
	list_del(&ro->notअगरier);
	spin_unlock(&raw_notअगरier_lock);

	lock_sock(sk);

	/* हटाओ current filters & unरेजिस्टर */
	अगर (ro->bound) अणु
		अगर (ro->अगरindex) अणु
			काष्ठा net_device *dev;

			dev = dev_get_by_index(sock_net(sk), ro->अगरindex);
			अगर (dev) अणु
				raw_disable_allfilters(dev_net(dev), dev, sk);
				dev_put(dev);
			पूर्ण
		पूर्ण अन्यथा अणु
			raw_disable_allfilters(sock_net(sk), शून्य, sk);
		पूर्ण
	पूर्ण

	अगर (ro->count > 1)
		kमुक्त(ro->filter);

	ro->अगरindex = 0;
	ro->bound = 0;
	ro->count = 0;
	मुक्त_percpu(ro->uniq);

	sock_orphan(sk);
	sock->sk = शून्य;

	release_sock(sk);
	sock_put(sk);

	वापस 0;
पूर्ण

अटल पूर्णांक raw_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक len)
अणु
	काष्ठा sockaddr_can *addr = (काष्ठा sockaddr_can *)uaddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा raw_sock *ro = raw_sk(sk);
	पूर्णांक अगरindex;
	पूर्णांक err = 0;
	पूर्णांक notअगरy_enetकरोwn = 0;

	अगर (len < RAW_MIN_NAMELEN)
		वापस -EINVAL;
	अगर (addr->can_family != AF_CAN)
		वापस -EINVAL;

	lock_sock(sk);

	अगर (ro->bound && addr->can_अगरindex == ro->अगरindex)
		जाओ out;

	अगर (addr->can_अगरindex) अणु
		काष्ठा net_device *dev;

		dev = dev_get_by_index(sock_net(sk), addr->can_अगरindex);
		अगर (!dev) अणु
			err = -ENODEV;
			जाओ out;
		पूर्ण
		अगर (dev->type != ARPHRD_CAN) अणु
			dev_put(dev);
			err = -ENODEV;
			जाओ out;
		पूर्ण
		अगर (!(dev->flags & IFF_UP))
			notअगरy_enetकरोwn = 1;

		अगरindex = dev->अगरindex;

		/* filters set by शेष/setsockopt */
		err = raw_enable_allfilters(sock_net(sk), dev, sk);
		dev_put(dev);
	पूर्ण अन्यथा अणु
		अगरindex = 0;

		/* filters set by शेष/setsockopt */
		err = raw_enable_allfilters(sock_net(sk), शून्य, sk);
	पूर्ण

	अगर (!err) अणु
		अगर (ro->bound) अणु
			/* unरेजिस्टर old filters */
			अगर (ro->अगरindex) अणु
				काष्ठा net_device *dev;

				dev = dev_get_by_index(sock_net(sk),
						       ro->अगरindex);
				अगर (dev) अणु
					raw_disable_allfilters(dev_net(dev),
							       dev, sk);
					dev_put(dev);
				पूर्ण
			पूर्ण अन्यथा अणु
				raw_disable_allfilters(sock_net(sk), शून्य, sk);
			पूर्ण
		पूर्ण
		ro->अगरindex = अगरindex;
		ro->bound = 1;
	पूर्ण

 out:
	release_sock(sk);

	अगर (notअगरy_enetकरोwn) अणु
		sk->sk_err = ENETDOWN;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_error_report(sk);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक raw_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
		       पूर्णांक peer)
अणु
	काष्ठा sockaddr_can *addr = (काष्ठा sockaddr_can *)uaddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा raw_sock *ro = raw_sk(sk);

	अगर (peer)
		वापस -EOPNOTSUPP;

	स_रखो(addr, 0, RAW_MIN_NAMELEN);
	addr->can_family  = AF_CAN;
	addr->can_अगरindex = ro->अगरindex;

	वापस RAW_MIN_NAMELEN;
पूर्ण

अटल पूर्णांक raw_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			  sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा raw_sock *ro = raw_sk(sk);
	काष्ठा can_filter *filter = शून्य;  /* dyn. alloc'ed filters */
	काष्ठा can_filter sfilter;         /* single filter */
	काष्ठा net_device *dev = शून्य;
	can_err_mask_t err_mask = 0;
	पूर्णांक count = 0;
	पूर्णांक err = 0;

	अगर (level != SOL_CAN_RAW)
		वापस -EINVAL;

	चयन (optname) अणु
	हाल CAN_RAW_FILTER:
		अगर (optlen % माप(काष्ठा can_filter) != 0)
			वापस -EINVAL;

		अगर (optlen > CAN_RAW_FILTER_MAX * माप(काष्ठा can_filter))
			वापस -EINVAL;

		count = optlen / माप(काष्ठा can_filter);

		अगर (count > 1) अणु
			/* filter करोes not fit पूर्णांकo dfilter => alloc space */
			filter = memdup_sockptr(optval, optlen);
			अगर (IS_ERR(filter))
				वापस PTR_ERR(filter);
		पूर्ण अन्यथा अगर (count == 1) अणु
			अगर (copy_from_sockptr(&sfilter, optval, माप(sfilter)))
				वापस -EFAULT;
		पूर्ण

		lock_sock(sk);

		अगर (ro->bound && ro->अगरindex)
			dev = dev_get_by_index(sock_net(sk), ro->अगरindex);

		अगर (ro->bound) अणु
			/* (try to) रेजिस्टर the new filters */
			अगर (count == 1)
				err = raw_enable_filters(sock_net(sk), dev, sk,
							 &sfilter, 1);
			अन्यथा
				err = raw_enable_filters(sock_net(sk), dev, sk,
							 filter, count);
			अगर (err) अणु
				अगर (count > 1)
					kमुक्त(filter);
				जाओ out_fil;
			पूर्ण

			/* हटाओ old filter registrations */
			raw_disable_filters(sock_net(sk), dev, sk, ro->filter,
					    ro->count);
		पूर्ण

		/* हटाओ old filter space */
		अगर (ro->count > 1)
			kमुक्त(ro->filter);

		/* link new filters to the socket */
		अगर (count == 1) अणु
			/* copy filter data क्रम single filter */
			ro->dfilter = sfilter;
			filter = &ro->dfilter;
		पूर्ण
		ro->filter = filter;
		ro->count  = count;

 out_fil:
		अगर (dev)
			dev_put(dev);

		release_sock(sk);

		अवरोध;

	हाल CAN_RAW_ERR_FILTER:
		अगर (optlen != माप(err_mask))
			वापस -EINVAL;

		अगर (copy_from_sockptr(&err_mask, optval, optlen))
			वापस -EFAULT;

		err_mask &= CAN_ERR_MASK;

		lock_sock(sk);

		अगर (ro->bound && ro->अगरindex)
			dev = dev_get_by_index(sock_net(sk), ro->अगरindex);

		/* हटाओ current error mask */
		अगर (ro->bound) अणु
			/* (try to) रेजिस्टर the new err_mask */
			err = raw_enable_errfilter(sock_net(sk), dev, sk,
						   err_mask);

			अगर (err)
				जाओ out_err;

			/* हटाओ old err_mask registration */
			raw_disable_errfilter(sock_net(sk), dev, sk,
					      ro->err_mask);
		पूर्ण

		/* link new err_mask to the socket */
		ro->err_mask = err_mask;

 out_err:
		अगर (dev)
			dev_put(dev);

		release_sock(sk);

		अवरोध;

	हाल CAN_RAW_LOOPBACK:
		अगर (optlen != माप(ro->loopback))
			वापस -EINVAL;

		अगर (copy_from_sockptr(&ro->loopback, optval, optlen))
			वापस -EFAULT;

		अवरोध;

	हाल CAN_RAW_RECV_OWN_MSGS:
		अगर (optlen != माप(ro->recv_own_msgs))
			वापस -EINVAL;

		अगर (copy_from_sockptr(&ro->recv_own_msgs, optval, optlen))
			वापस -EFAULT;

		अवरोध;

	हाल CAN_RAW_FD_FRAMES:
		अगर (optlen != माप(ro->fd_frames))
			वापस -EINVAL;

		अगर (copy_from_sockptr(&ro->fd_frames, optval, optlen))
			वापस -EFAULT;

		अवरोध;

	हाल CAN_RAW_JOIN_FILTERS:
		अगर (optlen != माप(ro->join_filters))
			वापस -EINVAL;

		अगर (copy_from_sockptr(&ro->join_filters, optval, optlen))
			वापस -EFAULT;

		अवरोध;

	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक raw_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			  अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा raw_sock *ro = raw_sk(sk);
	पूर्णांक len;
	व्योम *val;
	पूर्णांक err = 0;

	अगर (level != SOL_CAN_RAW)
		वापस -EINVAL;
	अगर (get_user(len, optlen))
		वापस -EFAULT;
	अगर (len < 0)
		वापस -EINVAL;

	चयन (optname) अणु
	हाल CAN_RAW_FILTER:
		lock_sock(sk);
		अगर (ro->count > 0) अणु
			पूर्णांक fsize = ro->count * माप(काष्ठा can_filter);

			/* user space buffer to small क्रम filter list? */
			अगर (len < fsize) अणु
				/* वापस -दुस्फल and needed space in optlen */
				err = -दुस्फल;
				अगर (put_user(fsize, optlen))
					err = -EFAULT;
			पूर्ण अन्यथा अणु
				अगर (len > fsize)
					len = fsize;
				अगर (copy_to_user(optval, ro->filter, len))
					err = -EFAULT;
			पूर्ण
		पूर्ण अन्यथा अणु
			len = 0;
		पूर्ण
		release_sock(sk);

		अगर (!err)
			err = put_user(len, optlen);
		वापस err;

	हाल CAN_RAW_ERR_FILTER:
		अगर (len > माप(can_err_mask_t))
			len = माप(can_err_mask_t);
		val = &ro->err_mask;
		अवरोध;

	हाल CAN_RAW_LOOPBACK:
		अगर (len > माप(पूर्णांक))
			len = माप(पूर्णांक);
		val = &ro->loopback;
		अवरोध;

	हाल CAN_RAW_RECV_OWN_MSGS:
		अगर (len > माप(पूर्णांक))
			len = माप(पूर्णांक);
		val = &ro->recv_own_msgs;
		अवरोध;

	हाल CAN_RAW_FD_FRAMES:
		अगर (len > माप(पूर्णांक))
			len = माप(पूर्णांक);
		val = &ro->fd_frames;
		अवरोध;

	हाल CAN_RAW_JOIN_FILTERS:
		अगर (len > माप(पूर्णांक))
			len = माप(पूर्णांक);
		val = &ro->join_filters;
		अवरोध;

	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, val, len))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक raw_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा raw_sock *ro = raw_sk(sk);
	काष्ठा sk_buff *skb;
	काष्ठा net_device *dev;
	पूर्णांक अगरindex;
	पूर्णांक err;

	अगर (msg->msg_name) अणु
		DECLARE_SOCKADDR(काष्ठा sockaddr_can *, addr, msg->msg_name);

		अगर (msg->msg_namelen < RAW_MIN_NAMELEN)
			वापस -EINVAL;

		अगर (addr->can_family != AF_CAN)
			वापस -EINVAL;

		अगरindex = addr->can_अगरindex;
	पूर्ण अन्यथा अणु
		अगरindex = ro->अगरindex;
	पूर्ण

	dev = dev_get_by_index(sock_net(sk), अगरindex);
	अगर (!dev)
		वापस -ENXIO;

	err = -EINVAL;
	अगर (ro->fd_frames && dev->mtu == CANFD_MTU) अणु
		अगर (unlikely(size != CANFD_MTU && size != CAN_MTU))
			जाओ put_dev;
	पूर्ण अन्यथा अणु
		अगर (unlikely(size != CAN_MTU))
			जाओ put_dev;
	पूर्ण

	skb = sock_alloc_send_skb(sk, size + माप(काष्ठा can_skb_priv),
				  msg->msg_flags & MSG_DONTWAIT, &err);
	अगर (!skb)
		जाओ put_dev;

	can_skb_reserve(skb);
	can_skb_prv(skb)->अगरindex = dev->अगरindex;
	can_skb_prv(skb)->skbcnt = 0;

	err = स_नकल_from_msg(skb_put(skb, size), msg, size);
	अगर (err < 0)
		जाओ मुक्त_skb;

	skb_setup_tx_बारtamp(skb, sk->sk_tsflags);

	skb->dev = dev;
	skb->sk = sk;
	skb->priority = sk->sk_priority;

	err = can_send(skb, ro->loopback);

	dev_put(dev);

	अगर (err)
		जाओ send_failed;

	वापस size;

मुक्त_skb:
	kमुक्त_skb(skb);
put_dev:
	dev_put(dev);
send_failed:
	वापस err;
पूर्ण

अटल पूर्णांक raw_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
		       पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb;
	पूर्णांक err = 0;
	पूर्णांक noblock;

	noblock = flags & MSG_DONTWAIT;
	flags &= ~MSG_DONTWAIT;

	अगर (flags & MSG_ERRQUEUE)
		वापस sock_recv_errqueue(sk, msg, size,
					  SOL_CAN_RAW, SCM_CAN_RAW_ERRQUEUE);

	skb = skb_recv_datagram(sk, flags, noblock, &err);
	अगर (!skb)
		वापस err;

	अगर (size < skb->len)
		msg->msg_flags |= MSG_TRUNC;
	अन्यथा
		size = skb->len;

	err = स_नकल_to_msg(msg, skb->data, size);
	अगर (err < 0) अणु
		skb_मुक्त_datagram(sk, skb);
		वापस err;
	पूर्ण

	sock_recv_ts_and_drops(msg, sk, skb);

	अगर (msg->msg_name) अणु
		__sockaddr_check_size(RAW_MIN_NAMELEN);
		msg->msg_namelen = RAW_MIN_NAMELEN;
		स_नकल(msg->msg_name, skb->cb, msg->msg_namelen);
	पूर्ण

	/* assign the flags that have been recorded in raw_rcv() */
	msg->msg_flags |= *(raw_flags(skb));

	skb_मुक्त_datagram(sk, skb);

	वापस size;
पूर्ण

अटल पूर्णांक raw_sock_no_ioctlcmd(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	/* no ioctls क्रम socket layer -> hand it करोwn to NIC layer */
	वापस -ENOIOCTLCMD;
पूर्ण

अटल स्थिर काष्ठा proto_ops raw_ops = अणु
	.family        = PF_CAN,
	.release       = raw_release,
	.bind          = raw_bind,
	.connect       = sock_no_connect,
	.socketpair    = sock_no_socketpair,
	.accept        = sock_no_accept,
	.getname       = raw_getname,
	.poll          = datagram_poll,
	.ioctl         = raw_sock_no_ioctlcmd,
	.gettstamp     = sock_gettstamp,
	.listen        = sock_no_listen,
	.shutकरोwn      = sock_no_shutकरोwn,
	.setsockopt    = raw_setsockopt,
	.माला_लोockopt    = raw_माला_लोockopt,
	.sendmsg       = raw_sendmsg,
	.recvmsg       = raw_recvmsg,
	.mmap          = sock_no_mmap,
	.sendpage      = sock_no_sendpage,
पूर्ण;

अटल काष्ठा proto raw_proto __पढ़ो_mostly = अणु
	.name       = "CAN_RAW",
	.owner      = THIS_MODULE,
	.obj_size   = माप(काष्ठा raw_sock),
	.init       = raw_init,
पूर्ण;

अटल स्थिर काष्ठा can_proto raw_can_proto = अणु
	.type       = SOCK_RAW,
	.protocol   = CAN_RAW,
	.ops        = &raw_ops,
	.prot       = &raw_proto,
पूर्ण;

अटल काष्ठा notअगरier_block canraw_notअगरier = अणु
	.notअगरier_call = raw_notअगरier
पूर्ण;

अटल __init पूर्णांक raw_module_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("can: raw protocol\n");

	err = can_proto_रेजिस्टर(&raw_can_proto);
	अगर (err < 0)
		pr_err("can: registration of raw protocol failed\n");
	अन्यथा
		रेजिस्टर_netdevice_notअगरier(&canraw_notअगरier);

	वापस err;
पूर्ण

अटल __निकास व्योम raw_module_निकास(व्योम)
अणु
	can_proto_unरेजिस्टर(&raw_can_proto);
	unरेजिस्टर_netdevice_notअगरier(&canraw_notअगरier);
पूर्ण

module_init(raw_module_init);
module_निकास(raw_module_निकास);
