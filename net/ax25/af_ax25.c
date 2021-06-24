<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Alan Cox GW4PTS (alan@lxorguk.ukuu.org.uk)
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 * Copyright (C) Darryl Miles G7LED (dlm@g7led.demon.co.uk)
 * Copyright (C) Steven Whitehouse GW7RRM (stevew@acm.org)
 * Copyright (C) Joerg Reuter DL1BKE (jreuter@yaina.de)
 * Copyright (C) Hans-Joachim Hetscher DD8NE (dd8ne@bnv-bamberg.de)
 * Copyright (C) Hans Alblas PE1AYX (hans@esrac.ele.tue.nl)
 * Copyright (C) Frederic Rible F1OAT (frible@teaser.fr)
 */
#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/slab.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/termios.h>	/* For TIOCINQ/OUTQ */
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/sysctl.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <net/net_namespace.h>
#समावेश <net/tcp_states.h>
#समावेश <net/ip.h>
#समावेश <net/arp.h>



HLIST_HEAD(ax25_list);
DEFINE_SPINLOCK(ax25_list_lock);

अटल स्थिर काष्ठा proto_ops ax25_proto_ops;

अटल व्योम ax25_मुक्त_sock(काष्ठा sock *sk)
अणु
	ax25_cb_put(sk_to_ax25(sk));
पूर्ण

/*
 *	Socket removal during an पूर्णांकerrupt is now safe.
 */
अटल व्योम ax25_cb_del(ax25_cb *ax25)
अणु
	अगर (!hlist_unhashed(&ax25->ax25_node)) अणु
		spin_lock_bh(&ax25_list_lock);
		hlist_del_init(&ax25->ax25_node);
		spin_unlock_bh(&ax25_list_lock);
		ax25_cb_put(ax25);
	पूर्ण
पूर्ण

/*
 *	Kill all bound sockets on a dropped device.
 */
अटल व्योम ax25_समाप्त_by_device(काष्ठा net_device *dev)
अणु
	ax25_dev *ax25_dev;
	ax25_cb *s;

	अगर ((ax25_dev = ax25_dev_ax25dev(dev)) == शून्य)
		वापस;

	spin_lock_bh(&ax25_list_lock);
again:
	ax25_क्रम_each(s, &ax25_list) अणु
		अगर (s->ax25_dev == ax25_dev) अणु
			s->ax25_dev = शून्य;
			spin_unlock_bh(&ax25_list_lock);
			ax25_disconnect(s, ENETUNREACH);
			spin_lock_bh(&ax25_list_lock);

			/* The entry could have been deleted from the
			 * list meanजबतक and thus the next poपूर्णांकer is
			 * no दीर्घer valid.  Play it safe and restart
			 * the scan.  Forward progress is ensured
			 * because we set s->ax25_dev to शून्य and we
			 * are never passed a शून्य 'dev' argument.
			 */
			जाओ again;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ax25_list_lock);
पूर्ण

/*
 *	Handle device status changes.
 */
अटल पूर्णांक ax25_device_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			     व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (!net_eq(dev_net(dev), &init_net))
		वापस NOTIFY_DONE;

	/* Reject non AX.25 devices */
	अगर (dev->type != ARPHRD_AX25)
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_UP:
		ax25_dev_device_up(dev);
		अवरोध;
	हाल NETDEV_DOWN:
		ax25_समाप्त_by_device(dev);
		ax25_rt_device_करोwn(dev);
		ax25_dev_device_करोwn(dev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/*
 *	Add a socket to the bound sockets list.
 */
व्योम ax25_cb_add(ax25_cb *ax25)
अणु
	spin_lock_bh(&ax25_list_lock);
	ax25_cb_hold(ax25);
	hlist_add_head(&ax25->ax25_node, &ax25_list);
	spin_unlock_bh(&ax25_list_lock);
पूर्ण

/*
 *	Find a socket that wants to accept the SABM we have just
 *	received.
 */
काष्ठा sock *ax25_find_listener(ax25_address *addr, पूर्णांक digi,
	काष्ठा net_device *dev, पूर्णांक type)
अणु
	ax25_cb *s;

	spin_lock(&ax25_list_lock);
	ax25_क्रम_each(s, &ax25_list) अणु
		अगर ((s->iamdigi && !digi) || (!s->iamdigi && digi))
			जारी;
		अगर (s->sk && !ax25cmp(&s->source_addr, addr) &&
		    s->sk->sk_type == type && s->sk->sk_state == TCP_LISTEN) अणु
			/* If device is null we match any device */
			अगर (s->ax25_dev == शून्य || s->ax25_dev->dev == dev) अणु
				sock_hold(s->sk);
				spin_unlock(&ax25_list_lock);
				वापस s->sk;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&ax25_list_lock);

	वापस शून्य;
पूर्ण

/*
 *	Find an AX.25 socket given both ends.
 */
काष्ठा sock *ax25_get_socket(ax25_address *my_addr, ax25_address *dest_addr,
	पूर्णांक type)
अणु
	काष्ठा sock *sk = शून्य;
	ax25_cb *s;

	spin_lock(&ax25_list_lock);
	ax25_क्रम_each(s, &ax25_list) अणु
		अगर (s->sk && !ax25cmp(&s->source_addr, my_addr) &&
		    !ax25cmp(&s->dest_addr, dest_addr) &&
		    s->sk->sk_type == type) अणु
			sk = s->sk;
			sock_hold(sk);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock(&ax25_list_lock);

	वापस sk;
पूर्ण

/*
 *	Find an AX.25 control block given both ends. It will only pick up
 *	भग्नing AX.25 control blocks or non Raw socket bound control blocks.
 */
ax25_cb *ax25_find_cb(ax25_address *src_addr, ax25_address *dest_addr,
	ax25_digi *digi, काष्ठा net_device *dev)
अणु
	ax25_cb *s;

	spin_lock_bh(&ax25_list_lock);
	ax25_क्रम_each(s, &ax25_list) अणु
		अगर (s->sk && s->sk->sk_type != SOCK_SEQPACKET)
			जारी;
		अगर (s->ax25_dev == शून्य)
			जारी;
		अगर (ax25cmp(&s->source_addr, src_addr) == 0 && ax25cmp(&s->dest_addr, dest_addr) == 0 && s->ax25_dev->dev == dev) अणु
			अगर (digi != शून्य && digi->ndigi != 0) अणु
				अगर (s->digipeat == शून्य)
					जारी;
				अगर (ax25digicmp(s->digipeat, digi) != 0)
					जारी;
			पूर्ण अन्यथा अणु
				अगर (s->digipeat != शून्य && s->digipeat->ndigi != 0)
					जारी;
			पूर्ण
			ax25_cb_hold(s);
			spin_unlock_bh(&ax25_list_lock);

			वापस s;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ax25_list_lock);

	वापस शून्य;
पूर्ण

EXPORT_SYMBOL(ax25_find_cb);

व्योम ax25_send_to_raw(ax25_address *addr, काष्ठा sk_buff *skb, पूर्णांक proto)
अणु
	ax25_cb *s;
	काष्ठा sk_buff *copy;

	spin_lock(&ax25_list_lock);
	ax25_क्रम_each(s, &ax25_list) अणु
		अगर (s->sk != शून्य && ax25cmp(&s->source_addr, addr) == 0 &&
		    s->sk->sk_type == SOCK_RAW &&
		    s->sk->sk_protocol == proto &&
		    s->ax25_dev->dev == skb->dev &&
		    atomic_पढ़ो(&s->sk->sk_rmem_alloc) <= s->sk->sk_rcvbuf) अणु
			अगर ((copy = skb_clone(skb, GFP_ATOMIC)) == शून्य)
				जारी;
			अगर (sock_queue_rcv_skb(s->sk, copy) != 0)
				kमुक्त_skb(copy);
		पूर्ण
	पूर्ण
	spin_unlock(&ax25_list_lock);
पूर्ण

/*
 *	Deferred destroy.
 */
व्योम ax25_destroy_socket(ax25_cb *);

/*
 *	Handler क्रम deferred समाप्तs.
 */
अटल व्योम ax25_destroy_समयr(काष्ठा समयr_list *t)
अणु
	ax25_cb *ax25 = from_समयr(ax25, t, dसमयr);
	काष्ठा sock *sk;

	sk=ax25->sk;

	bh_lock_sock(sk);
	sock_hold(sk);
	ax25_destroy_socket(ax25);
	bh_unlock_sock(sk);
	sock_put(sk);
पूर्ण

/*
 *	This is called from user mode and the समयrs. Thus it protects itself
 *	against पूर्णांकerrupt users but करोesn't worry about being called during
 *	work. Once it is हटाओd from the queue no पूर्णांकerrupt or bottom half
 *	will touch it and we are (fairly 8-) ) safe.
 */
व्योम ax25_destroy_socket(ax25_cb *ax25)
अणु
	काष्ठा sk_buff *skb;

	ax25_cb_del(ax25);

	ax25_stop_heartbeat(ax25);
	ax25_stop_t1समयr(ax25);
	ax25_stop_t2समयr(ax25);
	ax25_stop_t3समयr(ax25);
	ax25_stop_idleसमयr(ax25);

	ax25_clear_queues(ax25);	/* Flush the queues */

	अगर (ax25->sk != शून्य) अणु
		जबतक ((skb = skb_dequeue(&ax25->sk->sk_receive_queue)) != शून्य) अणु
			अगर (skb->sk != ax25->sk) अणु
				/* A pending connection */
				ax25_cb *sax25 = sk_to_ax25(skb->sk);

				/* Queue the unaccepted socket क्रम death */
				sock_orphan(skb->sk);

				/* 9A4GL: hack to release unaccepted sockets */
				skb->sk->sk_state = TCP_LISTEN;

				ax25_start_heartbeat(sax25);
				sax25->state = AX25_STATE_0;
			पूर्ण

			kमुक्त_skb(skb);
		पूर्ण
		skb_queue_purge(&ax25->sk->sk_ग_लिखो_queue);
	पूर्ण

	अगर (ax25->sk != शून्य) अणु
		अगर (sk_has_allocations(ax25->sk)) अणु
			/* Defer: outstanding buffers */
			समयr_setup(&ax25->dसमयr, ax25_destroy_समयr, 0);
			ax25->dसमयr.expires  = jअगरfies + 2 * HZ;
			add_समयr(&ax25->dसमयr);
		पूर्ण अन्यथा अणु
			काष्ठा sock *sk=ax25->sk;
			ax25->sk=शून्य;
			sock_put(sk);
		पूर्ण
	पूर्ण अन्यथा अणु
		ax25_cb_put(ax25);
	पूर्ण
पूर्ण

/*
 * dl1bke 960311: set parameters क्रम existing AX.25 connections,
 *		  includes a KILL command to पात any connection.
 *		  VERY useful क्रम debugging ;-)
 */
अटल पूर्णांक ax25_ctl_ioctl(स्थिर अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा ax25_ctl_काष्ठा ax25_ctl;
	ax25_digi digi;
	ax25_dev *ax25_dev;
	ax25_cb *ax25;
	अचिन्हित पूर्णांक k;
	पूर्णांक ret = 0;

	अगर (copy_from_user(&ax25_ctl, arg, माप(ax25_ctl)))
		वापस -EFAULT;

	अगर ((ax25_dev = ax25_addr_ax25dev(&ax25_ctl.port_addr)) == शून्य)
		वापस -ENODEV;

	अगर (ax25_ctl.digi_count > AX25_MAX_DIGIS)
		वापस -EINVAL;

	अगर (ax25_ctl.arg > अच_दीर्घ_उच्च / HZ && ax25_ctl.cmd != AX25_KILL)
		वापस -EINVAL;

	digi.ndigi = ax25_ctl.digi_count;
	क्रम (k = 0; k < digi.ndigi; k++)
		digi.calls[k] = ax25_ctl.digi_addr[k];

	अगर ((ax25 = ax25_find_cb(&ax25_ctl.source_addr, &ax25_ctl.dest_addr, &digi, ax25_dev->dev)) == शून्य)
		वापस -ENOTCONN;

	चयन (ax25_ctl.cmd) अणु
	हाल AX25_KILL:
		ax25_send_control(ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
#अगर_घोषित CONFIG_AX25_DAMA_SLAVE
		अगर (ax25_dev->dama.slave && ax25->ax25_dev->values[AX25_VALUES_PROTOCOL] == AX25_PROTO_DAMA_SLAVE)
			ax25_dama_off(ax25);
#पूर्ण_अगर
		ax25_disconnect(ax25, ENETRESET);
		अवरोध;

	हाल AX25_WINDOW:
		अगर (ax25->modulus == AX25_MODULUS) अणु
			अगर (ax25_ctl.arg < 1 || ax25_ctl.arg > 7)
				जाओ einval_put;
		पूर्ण अन्यथा अणु
			अगर (ax25_ctl.arg < 1 || ax25_ctl.arg > 63)
				जाओ einval_put;
		पूर्ण
		ax25->winकरोw = ax25_ctl.arg;
		अवरोध;

	हाल AX25_T1:
		अगर (ax25_ctl.arg < 1 || ax25_ctl.arg > अच_दीर्घ_उच्च / HZ)
			जाओ einval_put;
		ax25->rtt = (ax25_ctl.arg * HZ) / 2;
		ax25->t1  = ax25_ctl.arg * HZ;
		अवरोध;

	हाल AX25_T2:
		अगर (ax25_ctl.arg < 1 || ax25_ctl.arg > अच_दीर्घ_उच्च / HZ)
			जाओ einval_put;
		ax25->t2 = ax25_ctl.arg * HZ;
		अवरोध;

	हाल AX25_N2:
		अगर (ax25_ctl.arg < 1 || ax25_ctl.arg > 31)
			जाओ einval_put;
		ax25->n2count = 0;
		ax25->n2 = ax25_ctl.arg;
		अवरोध;

	हाल AX25_T3:
		अगर (ax25_ctl.arg > अच_दीर्घ_उच्च / HZ)
			जाओ einval_put;
		ax25->t3 = ax25_ctl.arg * HZ;
		अवरोध;

	हाल AX25_IDLE:
		अगर (ax25_ctl.arg > अच_दीर्घ_उच्च / (60 * HZ))
			जाओ einval_put;

		ax25->idle = ax25_ctl.arg * 60 * HZ;
		अवरोध;

	हाल AX25_PACLEN:
		अगर (ax25_ctl.arg < 16 || ax25_ctl.arg > 65535)
			जाओ einval_put;
		ax25->paclen = ax25_ctl.arg;
		अवरोध;

	शेष:
		जाओ einval_put;
	  पूर्ण

out_put:
	ax25_cb_put(ax25);
	वापस ret;

einval_put:
	ret = -EINVAL;
	जाओ out_put;
पूर्ण

अटल व्योम ax25_fillin_cb_from_dev(ax25_cb *ax25, ax25_dev *ax25_dev)
अणु
	ax25->rtt     = msecs_to_jअगरfies(ax25_dev->values[AX25_VALUES_T1]) / 2;
	ax25->t1      = msecs_to_jअगरfies(ax25_dev->values[AX25_VALUES_T1]);
	ax25->t2      = msecs_to_jअगरfies(ax25_dev->values[AX25_VALUES_T2]);
	ax25->t3      = msecs_to_jअगरfies(ax25_dev->values[AX25_VALUES_T3]);
	ax25->n2      = ax25_dev->values[AX25_VALUES_N2];
	ax25->paclen  = ax25_dev->values[AX25_VALUES_PACLEN];
	ax25->idle    = msecs_to_jअगरfies(ax25_dev->values[AX25_VALUES_IDLE]);
	ax25->backoff = ax25_dev->values[AX25_VALUES_BACKOFF];

	अगर (ax25_dev->values[AX25_VALUES_AXDEFMODE]) अणु
		ax25->modulus = AX25_EMODULUS;
		ax25->winकरोw  = ax25_dev->values[AX25_VALUES_EWINDOW];
	पूर्ण अन्यथा अणु
		ax25->modulus = AX25_MODULUS;
		ax25->winकरोw  = ax25_dev->values[AX25_VALUES_WINDOW];
	पूर्ण
पूर्ण

/*
 *	Fill in a created AX.25 created control block with the शेष
 *	values क्रम a particular device.
 */
व्योम ax25_fillin_cb(ax25_cb *ax25, ax25_dev *ax25_dev)
अणु
	ax25->ax25_dev = ax25_dev;

	अगर (ax25->ax25_dev != शून्य) अणु
		ax25_fillin_cb_from_dev(ax25, ax25_dev);
		वापस;
	पूर्ण

	/*
	 * No device, use kernel / AX.25 spec शेष values
	 */
	ax25->rtt     = msecs_to_jअगरfies(AX25_DEF_T1) / 2;
	ax25->t1      = msecs_to_jअगरfies(AX25_DEF_T1);
	ax25->t2      = msecs_to_jअगरfies(AX25_DEF_T2);
	ax25->t3      = msecs_to_jअगरfies(AX25_DEF_T3);
	ax25->n2      = AX25_DEF_N2;
	ax25->paclen  = AX25_DEF_PACLEN;
	ax25->idle    = msecs_to_jअगरfies(AX25_DEF_IDLE);
	ax25->backoff = AX25_DEF_BACKOFF;

	अगर (AX25_DEF_AXDEFMODE) अणु
		ax25->modulus = AX25_EMODULUS;
		ax25->winकरोw  = AX25_DEF_EWINDOW;
	पूर्ण अन्यथा अणु
		ax25->modulus = AX25_MODULUS;
		ax25->winकरोw  = AX25_DEF_WINDOW;
	पूर्ण
पूर्ण

/*
 * Create an empty AX.25 control block.
 */
ax25_cb *ax25_create_cb(व्योम)
अणु
	ax25_cb *ax25;

	अगर ((ax25 = kzalloc(माप(*ax25), GFP_ATOMIC)) == शून्य)
		वापस शून्य;

	refcount_set(&ax25->refcount, 1);

	skb_queue_head_init(&ax25->ग_लिखो_queue);
	skb_queue_head_init(&ax25->frag_queue);
	skb_queue_head_init(&ax25->ack_queue);
	skb_queue_head_init(&ax25->reseq_queue);

	ax25_setup_समयrs(ax25);

	ax25_fillin_cb(ax25, शून्य);

	ax25->state = AX25_STATE_0;

	वापस ax25;
पूर्ण

/*
 *	Handling क्रम प्रणाली calls applied via the various पूर्णांकerfaces to an
 *	AX25 socket object
 */

अटल पूर्णांक ax25_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
		sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	ax25_cb *ax25;
	काष्ठा net_device *dev;
	अक्षर devname[IFNAMSIZ];
	अचिन्हित दीर्घ opt;
	पूर्णांक res = 0;

	अगर (level != SOL_AX25)
		वापस -ENOPROTOOPT;

	अगर (optlen < माप(अचिन्हित पूर्णांक))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&opt, optval, माप(अचिन्हित पूर्णांक)))
		वापस -EFAULT;

	lock_sock(sk);
	ax25 = sk_to_ax25(sk);

	चयन (optname) अणु
	हाल AX25_WINDOW:
		अगर (ax25->modulus == AX25_MODULUS) अणु
			अगर (opt < 1 || opt > 7) अणु
				res = -EINVAL;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (opt < 1 || opt > 63) अणु
				res = -EINVAL;
				अवरोध;
			पूर्ण
		पूर्ण
		ax25->winकरोw = opt;
		अवरोध;

	हाल AX25_T1:
		अगर (opt < 1 || opt > अच_दीर्घ_उच्च / HZ) अणु
			res = -EINVAL;
			अवरोध;
		पूर्ण
		ax25->rtt = (opt * HZ) >> 1;
		ax25->t1  = opt * HZ;
		अवरोध;

	हाल AX25_T2:
		अगर (opt < 1 || opt > अच_दीर्घ_उच्च / HZ) अणु
			res = -EINVAL;
			अवरोध;
		पूर्ण
		ax25->t2 = opt * HZ;
		अवरोध;

	हाल AX25_N2:
		अगर (opt < 1 || opt > 31) अणु
			res = -EINVAL;
			अवरोध;
		पूर्ण
		ax25->n2 = opt;
		अवरोध;

	हाल AX25_T3:
		अगर (opt < 1 || opt > अच_दीर्घ_उच्च / HZ) अणु
			res = -EINVAL;
			अवरोध;
		पूर्ण
		ax25->t3 = opt * HZ;
		अवरोध;

	हाल AX25_IDLE:
		अगर (opt > अच_दीर्घ_उच्च / (60 * HZ)) अणु
			res = -EINVAL;
			अवरोध;
		पूर्ण
		ax25->idle = opt * 60 * HZ;
		अवरोध;

	हाल AX25_BACKOFF:
		अगर (opt > 2) अणु
			res = -EINVAL;
			अवरोध;
		पूर्ण
		ax25->backoff = opt;
		अवरोध;

	हाल AX25_EXTSEQ:
		ax25->modulus = opt ? AX25_EMODULUS : AX25_MODULUS;
		अवरोध;

	हाल AX25_PIDINCL:
		ax25->pidincl = opt ? 1 : 0;
		अवरोध;

	हाल AX25_IAMDIGI:
		ax25->iamdigi = opt ? 1 : 0;
		अवरोध;

	हाल AX25_PACLEN:
		अगर (opt < 16 || opt > 65535) अणु
			res = -EINVAL;
			अवरोध;
		पूर्ण
		ax25->paclen = opt;
		अवरोध;

	हाल SO_BINDTODEVICE:
		अगर (optlen > IFNAMSIZ - 1)
			optlen = IFNAMSIZ - 1;

		स_रखो(devname, 0, माप(devname));

		अगर (copy_from_sockptr(devname, optval, optlen)) अणु
			res = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (sk->sk_type == SOCK_SEQPACKET &&
		   (sock->state != SS_UNCONNECTED ||
		    sk->sk_state == TCP_LISTEN)) अणु
			res = -EADDRNOTAVAIL;
			अवरोध;
		पूर्ण

		rtnl_lock();
		dev = __dev_get_by_name(&init_net, devname);
		अगर (!dev) अणु
			rtnl_unlock();
			res = -ENODEV;
			अवरोध;
		पूर्ण

		ax25->ax25_dev = ax25_dev_ax25dev(dev);
		अगर (!ax25->ax25_dev) अणु
			rtnl_unlock();
			res = -ENODEV;
			अवरोध;
		पूर्ण
		ax25_fillin_cb(ax25, ax25->ax25_dev);
		rtnl_unlock();
		अवरोध;

	शेष:
		res = -ENOPROTOOPT;
	पूर्ण
	release_sock(sk);

	वापस res;
पूर्ण

अटल पूर्णांक ax25_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
	अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	ax25_cb *ax25;
	काष्ठा ax25_dev *ax25_dev;
	अक्षर devname[IFNAMSIZ];
	व्योम *valptr;
	पूर्णांक val = 0;
	पूर्णांक maxlen, length;

	अगर (level != SOL_AX25)
		वापस -ENOPROTOOPT;

	अगर (get_user(maxlen, optlen))
		वापस -EFAULT;

	अगर (maxlen < 1)
		वापस -EFAULT;

	valptr = (व्योम *) &val;
	length = min_t(अचिन्हित पूर्णांक, maxlen, माप(पूर्णांक));

	lock_sock(sk);
	ax25 = sk_to_ax25(sk);

	चयन (optname) अणु
	हाल AX25_WINDOW:
		val = ax25->winकरोw;
		अवरोध;

	हाल AX25_T1:
		val = ax25->t1 / HZ;
		अवरोध;

	हाल AX25_T2:
		val = ax25->t2 / HZ;
		अवरोध;

	हाल AX25_N2:
		val = ax25->n2;
		अवरोध;

	हाल AX25_T3:
		val = ax25->t3 / HZ;
		अवरोध;

	हाल AX25_IDLE:
		val = ax25->idle / (60 * HZ);
		अवरोध;

	हाल AX25_BACKOFF:
		val = ax25->backoff;
		अवरोध;

	हाल AX25_EXTSEQ:
		val = (ax25->modulus == AX25_EMODULUS);
		अवरोध;

	हाल AX25_PIDINCL:
		val = ax25->pidincl;
		अवरोध;

	हाल AX25_IAMDIGI:
		val = ax25->iamdigi;
		अवरोध;

	हाल AX25_PACLEN:
		val = ax25->paclen;
		अवरोध;

	हाल SO_BINDTODEVICE:
		ax25_dev = ax25->ax25_dev;

		अगर (ax25_dev != शून्य && ax25_dev->dev != शून्य) अणु
			strlcpy(devname, ax25_dev->dev->name, माप(devname));
			length = म_माप(devname) + 1;
		पूर्ण अन्यथा अणु
			*devname = '\0';
			length = 1;
		पूर्ण

		valptr = (व्योम *) devname;
		अवरोध;

	शेष:
		release_sock(sk);
		वापस -ENOPROTOOPT;
	पूर्ण
	release_sock(sk);

	अगर (put_user(length, optlen))
		वापस -EFAULT;

	वापस copy_to_user(optval, valptr, length) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक ax25_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक res = 0;

	lock_sock(sk);
	अगर (sk->sk_type == SOCK_SEQPACKET && sk->sk_state != TCP_LISTEN) अणु
		sk->sk_max_ack_backlog = backlog;
		sk->sk_state           = TCP_LISTEN;
		जाओ out;
	पूर्ण
	res = -EOPNOTSUPP;

out:
	release_sock(sk);

	वापस res;
पूर्ण

/*
 * XXX: when creating ax25_sock we should update the .obj_size setting
 * below.
 */
अटल काष्ठा proto ax25_proto = अणु
	.name	  = "AX25",
	.owner	  = THIS_MODULE,
	.obj_size = माप(काष्ठा ax25_sock),
पूर्ण;

अटल पूर्णांक ax25_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
		       पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	ax25_cb *ax25;

	अगर (protocol < 0 || protocol > U8_MAX)
		वापस -EINVAL;

	अगर (!net_eq(net, &init_net))
		वापस -EAFNOSUPPORT;

	चयन (sock->type) अणु
	हाल SOCK_DGRAM:
		अगर (protocol == 0 || protocol == PF_AX25)
			protocol = AX25_P_TEXT;
		अवरोध;

	हाल SOCK_SEQPACKET:
		चयन (protocol) अणु
		हाल 0:
		हाल PF_AX25:	/* For CLX */
			protocol = AX25_P_TEXT;
			अवरोध;
		हाल AX25_P_SEGMENT:
#अगर_घोषित CONFIG_INET
		हाल AX25_P_ARP:
		हाल AX25_P_IP:
#पूर्ण_अगर
#अगर_घोषित CONFIG_NETROM
		हाल AX25_P_NETROM:
#पूर्ण_अगर
#अगर_घोषित CONFIG_ROSE
		हाल AX25_P_ROSE:
#पूर्ण_अगर
			वापस -ESOCKTNOSUPPORT;
#अगर_घोषित CONFIG_NETROM_MODULE
		हाल AX25_P_NETROM:
			अगर (ax25_protocol_is_रेजिस्टरed(AX25_P_NETROM))
				वापस -ESOCKTNOSUPPORT;
			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ROSE_MODULE
		हाल AX25_P_ROSE:
			अगर (ax25_protocol_is_रेजिस्टरed(AX25_P_ROSE))
				वापस -ESOCKTNOSUPPORT;
			अवरोध;
#पूर्ण_अगर
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल SOCK_RAW:
		अगर (!capable(CAP_NET_RAW))
			वापस -EPERM;
		अवरोध;
	शेष:
		वापस -ESOCKTNOSUPPORT;
	पूर्ण

	sk = sk_alloc(net, PF_AX25, GFP_ATOMIC, &ax25_proto, kern);
	अगर (sk == शून्य)
		वापस -ENOMEM;

	ax25 = ax25_sk(sk)->cb = ax25_create_cb();
	अगर (!ax25) अणु
		sk_मुक्त(sk);
		वापस -ENOMEM;
	पूर्ण

	sock_init_data(sock, sk);

	sk->sk_deकाष्ठा = ax25_मुक्त_sock;
	sock->ops    = &ax25_proto_ops;
	sk->sk_protocol = protocol;

	ax25->sk    = sk;

	वापस 0;
पूर्ण

काष्ठा sock *ax25_make_new(काष्ठा sock *osk, काष्ठा ax25_dev *ax25_dev)
अणु
	काष्ठा sock *sk;
	ax25_cb *ax25, *oax25;

	sk = sk_alloc(sock_net(osk), PF_AX25, GFP_ATOMIC, osk->sk_prot, 0);
	अगर (sk == शून्य)
		वापस शून्य;

	अगर ((ax25 = ax25_create_cb()) == शून्य) अणु
		sk_मुक्त(sk);
		वापस शून्य;
	पूर्ण

	चयन (osk->sk_type) अणु
	हाल SOCK_DGRAM:
		अवरोध;
	हाल SOCK_SEQPACKET:
		अवरोध;
	शेष:
		sk_मुक्त(sk);
		ax25_cb_put(ax25);
		वापस शून्य;
	पूर्ण

	sock_init_data(शून्य, sk);

	sk->sk_type     = osk->sk_type;
	sk->sk_priority = osk->sk_priority;
	sk->sk_protocol = osk->sk_protocol;
	sk->sk_rcvbuf   = osk->sk_rcvbuf;
	sk->sk_sndbuf   = osk->sk_sndbuf;
	sk->sk_state    = TCP_ESTABLISHED;
	sock_copy_flags(sk, osk);

	oax25 = sk_to_ax25(osk);

	ax25->modulus = oax25->modulus;
	ax25->backoff = oax25->backoff;
	ax25->pidincl = oax25->pidincl;
	ax25->iamdigi = oax25->iamdigi;
	ax25->rtt     = oax25->rtt;
	ax25->t1      = oax25->t1;
	ax25->t2      = oax25->t2;
	ax25->t3      = oax25->t3;
	ax25->n2      = oax25->n2;
	ax25->idle    = oax25->idle;
	ax25->paclen  = oax25->paclen;
	ax25->winकरोw  = oax25->winकरोw;

	ax25->ax25_dev    = ax25_dev;
	ax25->source_addr = oax25->source_addr;

	अगर (oax25->digipeat != शून्य) अणु
		ax25->digipeat = kmemdup(oax25->digipeat, माप(ax25_digi),
					 GFP_ATOMIC);
		अगर (ax25->digipeat == शून्य) अणु
			sk_मुक्त(sk);
			ax25_cb_put(ax25);
			वापस शून्य;
		पूर्ण
	पूर्ण

	ax25_sk(sk)->cb = ax25;
	sk->sk_deकाष्ठा = ax25_मुक्त_sock;
	ax25->sk    = sk;

	वापस sk;
पूर्ण

अटल पूर्णांक ax25_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	ax25_cb *ax25;

	अगर (sk == शून्य)
		वापस 0;

	sock_hold(sk);
	sock_orphan(sk);
	lock_sock(sk);
	ax25 = sk_to_ax25(sk);

	अगर (sk->sk_type == SOCK_SEQPACKET) अणु
		चयन (ax25->state) अणु
		हाल AX25_STATE_0:
			release_sock(sk);
			ax25_disconnect(ax25, 0);
			lock_sock(sk);
			ax25_destroy_socket(ax25);
			अवरोध;

		हाल AX25_STATE_1:
		हाल AX25_STATE_2:
			ax25_send_control(ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
			release_sock(sk);
			ax25_disconnect(ax25, 0);
			lock_sock(sk);
			अगर (!sock_flag(ax25->sk, SOCK_DESTROY))
				ax25_destroy_socket(ax25);
			अवरोध;

		हाल AX25_STATE_3:
		हाल AX25_STATE_4:
			ax25_clear_queues(ax25);
			ax25->n2count = 0;

			चयन (ax25->ax25_dev->values[AX25_VALUES_PROTOCOL]) अणु
			हाल AX25_PROTO_STD_SIMPLEX:
			हाल AX25_PROTO_STD_DUPLEX:
				ax25_send_control(ax25,
						  AX25_DISC,
						  AX25_POLLON,
						  AX25_COMMAND);
				ax25_stop_t2समयr(ax25);
				ax25_stop_t3समयr(ax25);
				ax25_stop_idleसमयr(ax25);
				अवरोध;
#अगर_घोषित CONFIG_AX25_DAMA_SLAVE
			हाल AX25_PROTO_DAMA_SLAVE:
				ax25_stop_t3समयr(ax25);
				ax25_stop_idleसमयr(ax25);
				अवरोध;
#पूर्ण_अगर
			पूर्ण
			ax25_calculate_t1(ax25);
			ax25_start_t1समयr(ax25);
			ax25->state = AX25_STATE_2;
			sk->sk_state                = TCP_CLOSE;
			sk->sk_shutकरोwn            |= SEND_SHUTDOWN;
			sk->sk_state_change(sk);
			sock_set_flag(sk, SOCK_DESTROY);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		sk->sk_state     = TCP_CLOSE;
		sk->sk_shutकरोwn |= SEND_SHUTDOWN;
		sk->sk_state_change(sk);
		ax25_destroy_socket(ax25);
	पूर्ण

	sock->sk   = शून्य;
	release_sock(sk);
	sock_put(sk);

	वापस 0;
पूर्ण

/*
 *	We support a funny extension here so you can (as root) give any callsign
 *	digipeated via a local address as source. This hack is obsolete now
 *	that we've implemented support क्रम SO_BINDTODEVICE. It is however small
 *	and trivially backward compatible.
 */
अटल पूर्णांक ax25_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा full_sockaddr_ax25 *addr = (काष्ठा full_sockaddr_ax25 *)uaddr;
	ax25_dev *ax25_dev = शून्य;
	ax25_uid_assoc *user;
	ax25_address call;
	ax25_cb *ax25;
	पूर्णांक err = 0;

	अगर (addr_len != माप(काष्ठा sockaddr_ax25) &&
	    addr_len != माप(काष्ठा full_sockaddr_ax25))
		/* support क्रम old काष्ठाure may go away some समय
		 * ax25_bind(): uses old (6 digipeater) socket काष्ठाure.
		 */
		अगर ((addr_len < माप(काष्ठा sockaddr_ax25) + माप(ax25_address) * 6) ||
		    (addr_len > माप(काष्ठा full_sockaddr_ax25)))
			वापस -EINVAL;

	अगर (addr->fsa_ax25.sax25_family != AF_AX25)
		वापस -EINVAL;

	user = ax25_findbyuid(current_euid());
	अगर (user) अणु
		call = user->call;
		ax25_uid_put(user);
	पूर्ण अन्यथा अणु
		अगर (ax25_uid_policy && !capable(CAP_NET_ADMIN))
			वापस -EACCES;

		call = addr->fsa_ax25.sax25_call;
	पूर्ण

	lock_sock(sk);

	ax25 = sk_to_ax25(sk);
	अगर (!sock_flag(sk, SOCK_ZAPPED)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	ax25->source_addr = call;

	/*
	 * User alपढ़ोy set पूर्णांकerface with SO_BINDTODEVICE
	 */
	अगर (ax25->ax25_dev != शून्य)
		जाओ करोne;

	अगर (addr_len > माप(काष्ठा sockaddr_ax25) && addr->fsa_ax25.sax25_ndigis == 1) अणु
		अगर (ax25cmp(&addr->fsa_digipeater[0], &null_ax25_address) != 0 &&
		    (ax25_dev = ax25_addr_ax25dev(&addr->fsa_digipeater[0])) == शून्य) अणु
			err = -EADDRNOTAVAIL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((ax25_dev = ax25_addr_ax25dev(&addr->fsa_ax25.sax25_call)) == शून्य) अणु
			err = -EADDRNOTAVAIL;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (ax25_dev != शून्य)
		ax25_fillin_cb(ax25, ax25_dev);

करोne:
	ax25_cb_add(ax25);
	sock_reset_flag(sk, SOCK_ZAPPED);

out:
	release_sock(sk);

	वापस err;
पूर्ण

/*
 *	FIXME: nonblock behaviour looks like it may have a bug.
 */
अटल पूर्णांक __must_check ax25_connect(काष्ठा socket *sock,
	काष्ठा sockaddr *uaddr, पूर्णांक addr_len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	ax25_cb *ax25 = sk_to_ax25(sk), *ax25t;
	काष्ठा full_sockaddr_ax25 *fsa = (काष्ठा full_sockaddr_ax25 *)uaddr;
	ax25_digi *digi = शून्य;
	पूर्णांक ct = 0, err = 0;

	/*
	 * some sanity checks. code further करोwn depends on this
	 */

	अगर (addr_len == माप(काष्ठा sockaddr_ax25))
		/* support क्रम this will go away in early 2.5.x
		 * ax25_connect(): uses obsolete socket काष्ठाure
		 */
		;
	अन्यथा अगर (addr_len != माप(काष्ठा full_sockaddr_ax25))
		/* support क्रम old काष्ठाure may go away some समय
		 * ax25_connect(): uses old (6 digipeater) socket काष्ठाure.
		 */
		अगर ((addr_len < माप(काष्ठा sockaddr_ax25) + माप(ax25_address) * 6) ||
		    (addr_len > माप(काष्ठा full_sockaddr_ax25)))
			वापस -EINVAL;


	अगर (fsa->fsa_ax25.sax25_family != AF_AX25)
		वापस -EINVAL;

	lock_sock(sk);

	/* deal with restarts */
	अगर (sock->state == SS_CONNECTING) अणु
		चयन (sk->sk_state) अणु
		हाल TCP_SYN_SENT: /* still trying */
			err = -EINPROGRESS;
			जाओ out_release;

		हाल TCP_ESTABLISHED: /* connection established */
			sock->state = SS_CONNECTED;
			जाओ out_release;

		हाल TCP_CLOSE: /* connection refused */
			sock->state = SS_UNCONNECTED;
			err = -ECONNREFUSED;
			जाओ out_release;
		पूर्ण
	पूर्ण

	अगर (sk->sk_state == TCP_ESTABLISHED && sk->sk_type == SOCK_SEQPACKET) अणु
		err = -EISCONN;	/* No reconnect on a seqpacket socket */
		जाओ out_release;
	पूर्ण

	sk->sk_state   = TCP_CLOSE;
	sock->state = SS_UNCONNECTED;

	kमुक्त(ax25->digipeat);
	ax25->digipeat = शून्य;

	/*
	 *	Handle digi-peaters to be used.
	 */
	अगर (addr_len > माप(काष्ठा sockaddr_ax25) &&
	    fsa->fsa_ax25.sax25_ndigis != 0) अणु
		/* Valid number of digipeaters ? */
		अगर (fsa->fsa_ax25.sax25_ndigis < 1 ||
		    fsa->fsa_ax25.sax25_ndigis > AX25_MAX_DIGIS ||
		    addr_len < माप(काष्ठा sockaddr_ax25) +
		    माप(ax25_address) * fsa->fsa_ax25.sax25_ndigis) अणु
			err = -EINVAL;
			जाओ out_release;
		पूर्ण

		अगर ((digi = kदो_स्मृति(माप(ax25_digi), GFP_KERNEL)) == शून्य) अणु
			err = -ENOBUFS;
			जाओ out_release;
		पूर्ण

		digi->ndigi      = fsa->fsa_ax25.sax25_ndigis;
		digi->lastrepeat = -1;

		जबतक (ct < fsa->fsa_ax25.sax25_ndigis) अणु
			अगर ((fsa->fsa_digipeater[ct].ax25_call[6] &
			     AX25_HBIT) && ax25->iamdigi) अणु
				digi->repeated[ct] = 1;
				digi->lastrepeat   = ct;
			पूर्ण अन्यथा अणु
				digi->repeated[ct] = 0;
			पूर्ण
			digi->calls[ct] = fsa->fsa_digipeater[ct];
			ct++;
		पूर्ण
	पूर्ण

	/*
	 *	Must bind first - स्वतःbinding in this may or may not work. If
	 *	the socket is alपढ़ोy bound, check to see अगर the device has
	 *	been filled in, error अगर it hasn't.
	 */
	अगर (sock_flag(sk, SOCK_ZAPPED)) अणु
		/* check अगर we can हटाओ this feature. It is broken. */
		prपूर्णांकk(KERN_WARNING "ax25_connect(): %s uses autobind, please contact jreuter@yaina.de\n",
			current->comm);
		अगर ((err = ax25_rt_स्वतःbind(ax25, &fsa->fsa_ax25.sax25_call)) < 0) अणु
			kमुक्त(digi);
			जाओ out_release;
		पूर्ण

		ax25_fillin_cb(ax25, ax25->ax25_dev);
		ax25_cb_add(ax25);
	पूर्ण अन्यथा अणु
		अगर (ax25->ax25_dev == शून्य) अणु
			kमुक्त(digi);
			err = -EHOSTUNREACH;
			जाओ out_release;
		पूर्ण
	पूर्ण

	अगर (sk->sk_type == SOCK_SEQPACKET &&
	    (ax25t=ax25_find_cb(&ax25->source_addr, &fsa->fsa_ax25.sax25_call, digi,
			 ax25->ax25_dev->dev))) अणु
		kमुक्त(digi);
		err = -EADDRINUSE;		/* Alपढ़ोy such a connection */
		ax25_cb_put(ax25t);
		जाओ out_release;
	पूर्ण

	ax25->dest_addr = fsa->fsa_ax25.sax25_call;
	ax25->digipeat  = digi;

	/* First the easy one */
	अगर (sk->sk_type != SOCK_SEQPACKET) अणु
		sock->state = SS_CONNECTED;
		sk->sk_state   = TCP_ESTABLISHED;
		जाओ out_release;
	पूर्ण

	/* Move to connecting socket, ax.25 lapb WAIT_UA.. */
	sock->state        = SS_CONNECTING;
	sk->sk_state          = TCP_SYN_SENT;

	चयन (ax25->ax25_dev->values[AX25_VALUES_PROTOCOL]) अणु
	हाल AX25_PROTO_STD_SIMPLEX:
	हाल AX25_PROTO_STD_DUPLEX:
		ax25_std_establish_data_link(ax25);
		अवरोध;

#अगर_घोषित CONFIG_AX25_DAMA_SLAVE
	हाल AX25_PROTO_DAMA_SLAVE:
		ax25->modulus = AX25_MODULUS;
		ax25->winकरोw  = ax25->ax25_dev->values[AX25_VALUES_WINDOW];
		अगर (ax25->ax25_dev->dama.slave)
			ax25_ds_establish_data_link(ax25);
		अन्यथा
			ax25_std_establish_data_link(ax25);
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	ax25->state = AX25_STATE_1;

	ax25_start_heartbeat(ax25);

	/* Now the loop */
	अगर (sk->sk_state != TCP_ESTABLISHED && (flags & O_NONBLOCK)) अणु
		err = -EINPROGRESS;
		जाओ out_release;
	पूर्ण

	अगर (sk->sk_state == TCP_SYN_SENT) अणु
		DEFINE_WAIT(रुको);

		क्रम (;;) अणु
			prepare_to_रुको(sk_sleep(sk), &रुको,
					TASK_INTERRUPTIBLE);
			अगर (sk->sk_state != TCP_SYN_SENT)
				अवरोध;
			अगर (!संकेत_pending(current)) अणु
				release_sock(sk);
				schedule();
				lock_sock(sk);
				जारी;
			पूर्ण
			err = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		finish_रुको(sk_sleep(sk), &रुको);

		अगर (err)
			जाओ out_release;
	पूर्ण

	अगर (sk->sk_state != TCP_ESTABLISHED) अणु
		/* Not in ABM, not in WAIT_UA -> failed */
		sock->state = SS_UNCONNECTED;
		err = sock_error(sk);	/* Always set at this poपूर्णांक */
		जाओ out_release;
	पूर्ण

	sock->state = SS_CONNECTED;

	err = 0;
out_release:
	release_sock(sk);

	वापस err;
पूर्ण

अटल पूर्णांक ax25_accept(काष्ठा socket *sock, काष्ठा socket *newsock, पूर्णांक flags,
		       bool kern)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sock *newsk;
	DEFINE_WAIT(रुको);
	काष्ठा sock *sk;
	पूर्णांक err = 0;

	अगर (sock->state != SS_UNCONNECTED)
		वापस -EINVAL;

	अगर ((sk = sock->sk) == शून्य)
		वापस -EINVAL;

	lock_sock(sk);
	अगर (sk->sk_type != SOCK_SEQPACKET) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (sk->sk_state != TCP_LISTEN) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 *	The पढ़ो queue this समय is holding sockets पढ़ोy to use
	 *	hooked पूर्णांकo the SABM we saved
	 */
	क्रम (;;) अणु
		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
		skb = skb_dequeue(&sk->sk_receive_queue);
		अगर (skb)
			अवरोध;

		अगर (flags & O_NONBLOCK) अणु
			err = -EWOULDBLOCK;
			अवरोध;
		पूर्ण
		अगर (!संकेत_pending(current)) अणु
			release_sock(sk);
			schedule();
			lock_sock(sk);
			जारी;
		पूर्ण
		err = -ERESTARTSYS;
		अवरोध;
	पूर्ण
	finish_रुको(sk_sleep(sk), &रुको);

	अगर (err)
		जाओ out;

	newsk		 = skb->sk;
	sock_graft(newsk, newsock);

	/* Now attach up the new socket */
	kमुक्त_skb(skb);
	sk_acceptq_हटाओd(sk);
	newsock->state = SS_CONNECTED;

out:
	release_sock(sk);

	वापस err;
पूर्ण

अटल पूर्णांक ax25_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
	पूर्णांक peer)
अणु
	काष्ठा full_sockaddr_ax25 *fsa = (काष्ठा full_sockaddr_ax25 *)uaddr;
	काष्ठा sock *sk = sock->sk;
	अचिन्हित अक्षर ndigi, i;
	ax25_cb *ax25;
	पूर्णांक err = 0;

	स_रखो(fsa, 0, माप(*fsa));
	lock_sock(sk);
	ax25 = sk_to_ax25(sk);

	अगर (peer != 0) अणु
		अगर (sk->sk_state != TCP_ESTABLISHED) अणु
			err = -ENOTCONN;
			जाओ out;
		पूर्ण

		fsa->fsa_ax25.sax25_family = AF_AX25;
		fsa->fsa_ax25.sax25_call   = ax25->dest_addr;

		अगर (ax25->digipeat != शून्य) अणु
			ndigi = ax25->digipeat->ndigi;
			fsa->fsa_ax25.sax25_ndigis = ndigi;
			क्रम (i = 0; i < ndigi; i++)
				fsa->fsa_digipeater[i] =
						ax25->digipeat->calls[i];
		पूर्ण
	पूर्ण अन्यथा अणु
		fsa->fsa_ax25.sax25_family = AF_AX25;
		fsa->fsa_ax25.sax25_call   = ax25->source_addr;
		fsa->fsa_ax25.sax25_ndigis = 1;
		अगर (ax25->ax25_dev != शून्य) अणु
			स_नकल(&fsa->fsa_digipeater[0],
			       ax25->ax25_dev->dev->dev_addr, AX25_ADDR_LEN);
		पूर्ण अन्यथा अणु
			fsa->fsa_digipeater[0] = null_ax25_address;
		पूर्ण
	पूर्ण
	err = माप (काष्ठा full_sockaddr_ax25);

out:
	release_sock(sk);

	वापस err;
पूर्ण

अटल पूर्णांक ax25_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	DECLARE_SOCKADDR(काष्ठा sockaddr_ax25 *, usax, msg->msg_name);
	काष्ठा sock *sk = sock->sk;
	काष्ठा sockaddr_ax25 sax;
	काष्ठा sk_buff *skb;
	ax25_digi dपंचांगp, *dp;
	ax25_cb *ax25;
	माप_प्रकार size;
	पूर्णांक lv, err, addr_len = msg->msg_namelen;

	अगर (msg->msg_flags & ~(MSG_DONTWAIT|MSG_EOR|MSG_CMSG_COMPAT))
		वापस -EINVAL;

	lock_sock(sk);
	ax25 = sk_to_ax25(sk);

	अगर (sock_flag(sk, SOCK_ZAPPED)) अणु
		err = -EADDRNOTAVAIL;
		जाओ out;
	पूर्ण

	अगर (sk->sk_shutकरोwn & SEND_SHUTDOWN) अणु
		send_sig(SIGPIPE, current, 0);
		err = -EPIPE;
		जाओ out;
	पूर्ण

	अगर (ax25->ax25_dev == शून्य) अणु
		err = -ENETUNREACH;
		जाओ out;
	पूर्ण

	अगर (len > ax25->ax25_dev->dev->mtu) अणु
		err = -EMSGSIZE;
		जाओ out;
	पूर्ण

	अगर (usax != शून्य) अणु
		अगर (usax->sax25_family != AF_AX25) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (addr_len == माप(काष्ठा sockaddr_ax25))
			/* ax25_sendmsg(): uses obsolete socket काष्ठाure */
			;
		अन्यथा अगर (addr_len != माप(काष्ठा full_sockaddr_ax25))
			/* support क्रम old काष्ठाure may go away some समय
			 * ax25_sendmsg(): uses old (6 digipeater)
			 * socket काष्ठाure.
			 */
			अगर ((addr_len < माप(काष्ठा sockaddr_ax25) + माप(ax25_address) * 6) ||
			    (addr_len > माप(काष्ठा full_sockaddr_ax25))) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण


		अगर (addr_len > माप(काष्ठा sockaddr_ax25) && usax->sax25_ndigis != 0) अणु
			पूर्णांक ct           = 0;
			काष्ठा full_sockaddr_ax25 *fsa = (काष्ठा full_sockaddr_ax25 *)usax;

			/* Valid number of digipeaters ? */
			अगर (usax->sax25_ndigis < 1 ||
			    usax->sax25_ndigis > AX25_MAX_DIGIS ||
			    addr_len < माप(काष्ठा sockaddr_ax25) +
			    माप(ax25_address) * usax->sax25_ndigis) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण

			dपंचांगp.ndigi      = usax->sax25_ndigis;

			जबतक (ct < usax->sax25_ndigis) अणु
				dपंचांगp.repeated[ct] = 0;
				dपंचांगp.calls[ct]    = fsa->fsa_digipeater[ct];
				ct++;
			पूर्ण

			dपंचांगp.lastrepeat = 0;
		पूर्ण

		sax = *usax;
		अगर (sk->sk_type == SOCK_SEQPACKET &&
		    ax25cmp(&ax25->dest_addr, &sax.sax25_call)) अणु
			err = -EISCONN;
			जाओ out;
		पूर्ण
		अगर (usax->sax25_ndigis == 0)
			dp = शून्य;
		अन्यथा
			dp = &dपंचांगp;
	पूर्ण अन्यथा अणु
		/*
		 *	FIXME: 1003.1g - अगर the socket is like this because
		 *	it has become बंदd (not started बंदd) and is VC
		 *	we ought to SIGPIPE, EPIPE
		 */
		अगर (sk->sk_state != TCP_ESTABLISHED) अणु
			err = -ENOTCONN;
			जाओ out;
		पूर्ण
		sax.sax25_family = AF_AX25;
		sax.sax25_call   = ax25->dest_addr;
		dp = ax25->digipeat;
	पूर्ण

	/* Build a packet */
	/* Assume the worst हाल */
	size = len + ax25->ax25_dev->dev->hard_header_len;

	skb = sock_alloc_send_skb(sk, size, msg->msg_flags&MSG_DONTWAIT, &err);
	अगर (skb == शून्य)
		जाओ out;

	skb_reserve(skb, size - len);

	/* User data follows immediately after the AX.25 data */
	अगर (स_नकल_from_msg(skb_put(skb, len), msg, len)) अणु
		err = -EFAULT;
		kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	skb_reset_network_header(skb);

	/* Add the PID अगर one is not supplied by the user in the skb */
	अगर (!ax25->pidincl)
		*(u8 *)skb_push(skb, 1) = sk->sk_protocol;

	अगर (sk->sk_type == SOCK_SEQPACKET) अणु
		/* Connected mode sockets go via the LAPB machine */
		अगर (sk->sk_state != TCP_ESTABLISHED) अणु
			kमुक्त_skb(skb);
			err = -ENOTCONN;
			जाओ out;
		पूर्ण

		/* Shove it onto the queue and kick */
		ax25_output(ax25, ax25->paclen, skb);

		err = len;
		जाओ out;
	पूर्ण

	skb_push(skb, 1 + ax25_addr_size(dp));

	/* Building AX.25 Header */

	/* Build an AX.25 header */
	lv = ax25_addr_build(skb->data, &ax25->source_addr, &sax.sax25_call,
			     dp, AX25_COMMAND, AX25_MODULUS);

	skb_set_transport_header(skb, lv);

	*skb_transport_header(skb) = AX25_UI;

	/* Datagram frames go straight out of the करोor as UI */
	ax25_queue_xmit(skb, ax25->ax25_dev->dev);

	err = len;

out:
	release_sock(sk);

	वापस err;
पूर्ण

अटल पूर्णांक ax25_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
			पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb;
	पूर्णांक copied;
	पूर्णांक err = 0;

	lock_sock(sk);
	/*
	 * 	This works क्रम seqpacket too. The receiver has ordered the
	 *	queue क्रम us! We करो one quick check first though
	 */
	अगर (sk->sk_type == SOCK_SEQPACKET && sk->sk_state != TCP_ESTABLISHED) अणु
		err =  -ENOTCONN;
		जाओ out;
	पूर्ण

	/* Now we can treat all alike */
	skb = skb_recv_datagram(sk, flags & ~MSG_DONTWAIT,
				flags & MSG_DONTWAIT, &err);
	अगर (skb == शून्य)
		जाओ out;

	अगर (!sk_to_ax25(sk)->pidincl)
		skb_pull(skb, 1);		/* Remove PID */

	skb_reset_transport_header(skb);
	copied = skb->len;

	अगर (copied > size) अणु
		copied = size;
		msg->msg_flags |= MSG_TRUNC;
	पूर्ण

	skb_copy_datagram_msg(skb, 0, msg, copied);

	अगर (msg->msg_name) अणु
		ax25_digi digi;
		ax25_address src;
		स्थिर अचिन्हित अक्षर *mac = skb_mac_header(skb);
		DECLARE_SOCKADDR(काष्ठा sockaddr_ax25 *, sax, msg->msg_name);

		स_रखो(sax, 0, माप(काष्ठा full_sockaddr_ax25));
		ax25_addr_parse(mac + 1, skb->data - mac - 1, &src, शून्य,
				&digi, शून्य, शून्य);
		sax->sax25_family = AF_AX25;
		/* We set this correctly, even though we may not let the
		   application know the digi calls further करोwn (because it
		   did NOT ask to know them).  This could get political... **/
		sax->sax25_ndigis = digi.ndigi;
		sax->sax25_call   = src;

		अगर (sax->sax25_ndigis != 0) अणु
			पूर्णांक ct;
			काष्ठा full_sockaddr_ax25 *fsa = (काष्ठा full_sockaddr_ax25 *)sax;

			क्रम (ct = 0; ct < digi.ndigi; ct++)
				fsa->fsa_digipeater[ct] = digi.calls[ct];
		पूर्ण
		msg->msg_namelen = माप(काष्ठा full_sockaddr_ax25);
	पूर्ण

	skb_मुक्त_datagram(sk, skb);
	err = copied;

out:
	release_sock(sk);

	वापस err;
पूर्ण

अटल पूर्णांक ax25_shutकरोwn(काष्ठा socket *sk, पूर्णांक how)
अणु
	/* FIXME - generate DM and RNR states */
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ax25_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sock *sk = sock->sk;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक res = 0;

	lock_sock(sk);
	चयन (cmd) अणु
	हाल TIOCOUTQ: अणु
		दीर्घ amount;

		amount = sk->sk_sndbuf - sk_wmem_alloc_get(sk);
		अगर (amount < 0)
			amount = 0;
		res = put_user(amount, (पूर्णांक __user *)argp);
		अवरोध;
	पूर्ण

	हाल TIOCINQ: अणु
		काष्ठा sk_buff *skb;
		दीर्घ amount = 0L;
		/* These two are safe on a single CPU प्रणाली as only user tasks fiddle here */
		अगर ((skb = skb_peek(&sk->sk_receive_queue)) != शून्य)
			amount = skb->len;
		res = put_user(amount, (पूर्णांक __user *) argp);
		अवरोध;
	पूर्ण

	हाल SIOCAX25ADDUID:	/* Add a uid to the uid/call map table */
	हाल SIOCAX25DELUID:	/* Delete a uid from the uid/call map table */
	हाल SIOCAX25GETUID: अणु
		काष्ठा sockaddr_ax25 sax25;
		अगर (copy_from_user(&sax25, argp, माप(sax25))) अणु
			res = -EFAULT;
			अवरोध;
		पूर्ण
		res = ax25_uid_ioctl(cmd, &sax25);
		अवरोध;
	पूर्ण

	हाल SIOCAX25NOUID: अणु	/* Set the शेष policy (शेष/bar) */
		दीर्घ amount;
		अगर (!capable(CAP_NET_ADMIN)) अणु
			res = -EPERM;
			अवरोध;
		पूर्ण
		अगर (get_user(amount, (दीर्घ __user *)argp)) अणु
			res = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (amount < 0 || amount > AX25_NOUID_BLOCK) अणु
			res = -EINVAL;
			अवरोध;
		पूर्ण
		ax25_uid_policy = amount;
		res = 0;
		अवरोध;
	पूर्ण

	हाल SIOCADDRT:
	हाल SIOCDELRT:
	हाल SIOCAX25OPTRT:
		अगर (!capable(CAP_NET_ADMIN)) अणु
			res = -EPERM;
			अवरोध;
		पूर्ण
		res = ax25_rt_ioctl(cmd, argp);
		अवरोध;

	हाल SIOCAX25CTLCON:
		अगर (!capable(CAP_NET_ADMIN)) अणु
			res = -EPERM;
			अवरोध;
		पूर्ण
		res = ax25_ctl_ioctl(cmd, argp);
		अवरोध;

	हाल SIOCAX25GETINFO:
	हाल SIOCAX25GETINFOOLD: अणु
		ax25_cb *ax25 = sk_to_ax25(sk);
		काष्ठा ax25_info_काष्ठा ax25_info;

		ax25_info.t1        = ax25->t1   / HZ;
		ax25_info.t2        = ax25->t2   / HZ;
		ax25_info.t3        = ax25->t3   / HZ;
		ax25_info.idle      = ax25->idle / (60 * HZ);
		ax25_info.n2        = ax25->n2;
		ax25_info.t1समयr   = ax25_display_समयr(&ax25->t1समयr)   / HZ;
		ax25_info.t2समयr   = ax25_display_समयr(&ax25->t2समयr)   / HZ;
		ax25_info.t3समयr   = ax25_display_समयr(&ax25->t3समयr)   / HZ;
		ax25_info.idleसमयr = ax25_display_समयr(&ax25->idleसमयr) / (60 * HZ);
		ax25_info.n2count   = ax25->n2count;
		ax25_info.state     = ax25->state;
		ax25_info.rcv_q     = sk_rmem_alloc_get(sk);
		ax25_info.snd_q     = sk_wmem_alloc_get(sk);
		ax25_info.vs        = ax25->vs;
		ax25_info.vr        = ax25->vr;
		ax25_info.va        = ax25->va;
		ax25_info.vs_max    = ax25->vs; /* reserved */
		ax25_info.paclen    = ax25->paclen;
		ax25_info.winकरोw    = ax25->winकरोw;

		/* old काष्ठाure? */
		अगर (cmd == SIOCAX25GETINFOOLD) अणु
			अटल पूर्णांक warned = 0;
			अगर (!warned) अणु
				prपूर्णांकk(KERN_INFO "%s uses old SIOCAX25GETINFO\n",
					current->comm);
				warned=1;
			पूर्ण

			अगर (copy_to_user(argp, &ax25_info, माप(काष्ठा ax25_info_काष्ठा_deprecated))) अणु
				res = -EFAULT;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (copy_to_user(argp, &ax25_info, माप(काष्ठा ax25_info_काष्ठा))) अणु
				res = -EINVAL;
				अवरोध;
			पूर्ण
		पूर्ण
		res = 0;
		अवरोध;
	पूर्ण

	हाल SIOCAX25ADDFWD:
	हाल SIOCAX25DELFWD: अणु
		काष्ठा ax25_fwd_काष्ठा ax25_fwd;
		अगर (!capable(CAP_NET_ADMIN)) अणु
			res = -EPERM;
			अवरोध;
		पूर्ण
		अगर (copy_from_user(&ax25_fwd, argp, माप(ax25_fwd))) अणु
			res = -EFAULT;
			अवरोध;
		पूर्ण
		res = ax25_fwd_ioctl(cmd, &ax25_fwd);
		अवरोध;
	पूर्ण

	हाल SIOCGIFADDR:
	हाल SIOCSIFADDR:
	हाल SIOCGIFDSTADDR:
	हाल SIOCSIFDSTADDR:
	हाल SIOCGIFBRDADDR:
	हाल SIOCSIFBRDADDR:
	हाल SIOCGIFNETMASK:
	हाल SIOCSIFNETMASK:
	हाल SIOCGIFMETRIC:
	हाल SIOCSIFMETRIC:
		res = -EINVAL;
		अवरोध;

	शेष:
		res = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण
	release_sock(sk);

	वापस res;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

अटल व्योम *ax25_info_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(ax25_list_lock)
अणु
	spin_lock_bh(&ax25_list_lock);
	वापस seq_hlist_start(&ax25_list, *pos);
पूर्ण

अटल व्योम *ax25_info_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	वापस seq_hlist_next(v, &ax25_list, pos);
पूर्ण

अटल व्योम ax25_info_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(ax25_list_lock)
अणु
	spin_unlock_bh(&ax25_list_lock);
पूर्ण

अटल पूर्णांक ax25_info_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	ax25_cb *ax25 = hlist_entry(v, काष्ठा ax25_cb, ax25_node);
	अक्षर buf[11];
	पूर्णांक k;


	/*
	 * New क्रमmat:
	 * magic dev src_addr dest_addr,digi1,digi2,.. st vs vr va t1 t1 t2 t2 t3 t3 idle idle n2 n2 rtt winकरोw paclen Snd-Q Rcv-Q inode
	 */

	seq_म_लिखो(seq, "%p %s %s%s ",
		   ax25,
		   ax25->ax25_dev == शून्य? "???" : ax25->ax25_dev->dev->name,
		   ax2asc(buf, &ax25->source_addr),
		   ax25->iamdigi? "*":"");
	seq_म_लिखो(seq, "%s", ax2asc(buf, &ax25->dest_addr));

	क्रम (k=0; (ax25->digipeat != शून्य) && (k < ax25->digipeat->ndigi); k++) अणु
		seq_म_लिखो(seq, ",%s%s",
			   ax2asc(buf, &ax25->digipeat->calls[k]),
			   ax25->digipeat->repeated[k]? "*":"");
	पूर्ण

	seq_म_लिखो(seq, " %d %d %d %d %lu %lu %lu %lu %lu %lu %lu %lu %d %d %lu %d %d",
		   ax25->state,
		   ax25->vs, ax25->vr, ax25->va,
		   ax25_display_समयr(&ax25->t1समयr) / HZ, ax25->t1 / HZ,
		   ax25_display_समयr(&ax25->t2समयr) / HZ, ax25->t2 / HZ,
		   ax25_display_समयr(&ax25->t3समयr) / HZ, ax25->t3 / HZ,
		   ax25_display_समयr(&ax25->idleसमयr) / (60 * HZ),
		   ax25->idle / (60 * HZ),
		   ax25->n2count, ax25->n2,
		   ax25->rtt / HZ,
		   ax25->winकरोw,
		   ax25->paclen);

	अगर (ax25->sk != शून्य) अणु
		seq_म_लिखो(seq, " %d %d %lu\n",
			   sk_wmem_alloc_get(ax25->sk),
			   sk_rmem_alloc_get(ax25->sk),
			   sock_i_ino(ax25->sk));
	पूर्ण अन्यथा अणु
		seq_माला_दो(seq, " * * *\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ax25_info_seqops = अणु
	.start = ax25_info_start,
	.next = ax25_info_next,
	.stop = ax25_info_stop,
	.show = ax25_info_show,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा net_proto_family ax25_family_ops = अणु
	.family =	PF_AX25,
	.create =	ax25_create,
	.owner	=	THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा proto_ops ax25_proto_ops = अणु
	.family		= PF_AX25,
	.owner		= THIS_MODULE,
	.release	= ax25_release,
	.bind		= ax25_bind,
	.connect	= ax25_connect,
	.socketpair	= sock_no_socketpair,
	.accept		= ax25_accept,
	.getname	= ax25_getname,
	.poll		= datagram_poll,
	.ioctl		= ax25_ioctl,
	.gettstamp	= sock_gettstamp,
	.listen		= ax25_listen,
	.shutकरोwn	= ax25_shutकरोwn,
	.setsockopt	= ax25_setsockopt,
	.माला_लोockopt	= ax25_माला_लोockopt,
	.sendmsg	= ax25_sendmsg,
	.recvmsg	= ax25_recvmsg,
	.mmap		= sock_no_mmap,
	.sendpage	= sock_no_sendpage,
पूर्ण;

/*
 *	Called by socket.c on kernel start up
 */
अटल काष्ठा packet_type ax25_packet_type __पढ़ो_mostly = अणु
	.type	=	cpu_to_be16(ETH_P_AX25),
	.func	=	ax25_kiss_rcv,
पूर्ण;

अटल काष्ठा notअगरier_block ax25_dev_notअगरier = अणु
	.notअगरier_call = ax25_device_event,
पूर्ण;

अटल पूर्णांक __init ax25_init(व्योम)
अणु
	पूर्णांक rc = proto_रेजिस्टर(&ax25_proto, 0);

	अगर (rc != 0)
		जाओ out;

	sock_रेजिस्टर(&ax25_family_ops);
	dev_add_pack(&ax25_packet_type);
	रेजिस्टर_netdevice_notअगरier(&ax25_dev_notअगरier);

	proc_create_seq("ax25_route", 0444, init_net.proc_net, &ax25_rt_seqops);
	proc_create_seq("ax25", 0444, init_net.proc_net, &ax25_info_seqops);
	proc_create_seq("ax25_calls", 0444, init_net.proc_net,
			&ax25_uid_seqops);
out:
	वापस rc;
पूर्ण
module_init(ax25_init);


MODULE_AUTHOR("Jonathan Naylor G4KLX <g4klx@g4klx.demon.co.uk>");
MODULE_DESCRIPTION("The amateur radio AX.25 link layer protocol");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_AX25);

अटल व्योम __निकास ax25_निकास(व्योम)
अणु
	हटाओ_proc_entry("ax25_route", init_net.proc_net);
	हटाओ_proc_entry("ax25", init_net.proc_net);
	हटाओ_proc_entry("ax25_calls", init_net.proc_net);

	unरेजिस्टर_netdevice_notअगरier(&ax25_dev_notअगरier);

	dev_हटाओ_pack(&ax25_packet_type);

	sock_unरेजिस्टर(PF_AX25);
	proto_unरेजिस्टर(&ax25_proto);

	ax25_rt_मुक्त();
	ax25_uid_मुक्त();
	ax25_dev_मुक्त();
पूर्ण
module_निकास(ax25_निकास);
