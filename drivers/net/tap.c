<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_tap.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/compat.h>
#समावेश <linux/अगर_tun.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/cache.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/cdev.h>
#समावेश <linux/idr.h>
#समावेश <linux/fs.h>
#समावेश <linux/uपन.स>

#समावेश <net/net_namespace.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/sock.h>
#समावेश <linux/virtio_net.h>
#समावेश <linux/skb_array.h>

#घोषणा TAP_IFFEATURES (IFF_VNET_HDR | IFF_MULTI_QUEUE)

#घोषणा TAP_VNET_LE 0x80000000
#घोषणा TAP_VNET_BE 0x40000000

#अगर_घोषित CONFIG_TUN_VNET_CROSS_LE
अटल अंतरभूत bool tap_legacy_is_little_endian(काष्ठा tap_queue *q)
अणु
	वापस q->flags & TAP_VNET_BE ? false :
		virtio_legacy_is_little_endian();
पूर्ण

अटल दीर्घ tap_get_vnet_be(काष्ठा tap_queue *q, पूर्णांक __user *sp)
अणु
	पूर्णांक s = !!(q->flags & TAP_VNET_BE);

	अगर (put_user(s, sp))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ tap_set_vnet_be(काष्ठा tap_queue *q, पूर्णांक __user *sp)
अणु
	पूर्णांक s;

	अगर (get_user(s, sp))
		वापस -EFAULT;

	अगर (s)
		q->flags |= TAP_VNET_BE;
	अन्यथा
		q->flags &= ~TAP_VNET_BE;

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत bool tap_legacy_is_little_endian(काष्ठा tap_queue *q)
अणु
	वापस virtio_legacy_is_little_endian();
पूर्ण

अटल दीर्घ tap_get_vnet_be(काष्ठा tap_queue *q, पूर्णांक __user *argp)
अणु
	वापस -EINVAL;
पूर्ण

अटल दीर्घ tap_set_vnet_be(काष्ठा tap_queue *q, पूर्णांक __user *argp)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_TUN_VNET_CROSS_LE */

अटल अंतरभूत bool tap_is_little_endian(काष्ठा tap_queue *q)
अणु
	वापस q->flags & TAP_VNET_LE ||
		tap_legacy_is_little_endian(q);
पूर्ण

अटल अंतरभूत u16 tap16_to_cpu(काष्ठा tap_queue *q, __virtio16 val)
अणु
	वापस __virtio16_to_cpu(tap_is_little_endian(q), val);
पूर्ण

अटल अंतरभूत __virtio16 cpu_to_tap16(काष्ठा tap_queue *q, u16 val)
अणु
	वापस __cpu_to_virtio16(tap_is_little_endian(q), val);
पूर्ण

अटल काष्ठा proto tap_proto = अणु
	.name = "tap",
	.owner = THIS_MODULE,
	.obj_size = माप(काष्ठा tap_queue),
पूर्ण;

#घोषणा TAP_NUM_DEVS (1U << MINORBITS)

अटल LIST_HEAD(major_list);

काष्ठा major_info अणु
	काष्ठा rcu_head rcu;
	dev_t major;
	काष्ठा idr minor_idr;
	spinlock_t minor_lock;
	स्थिर अक्षर *device_name;
	काष्ठा list_head next;
पूर्ण;

#घोषणा GOODCOPY_LEN 128

अटल स्थिर काष्ठा proto_ops tap_socket_ops;

#घोषणा RX_OFFLOADS (NETIF_F_GRO | NETIF_F_LRO)
#घोषणा TAP_FEATURES (NETIF_F_GSO | NETIF_F_SG | NETIF_F_FRAGLIST)

अटल काष्ठा tap_dev *tap_dev_get_rcu(स्थिर काष्ठा net_device *dev)
अणु
	वापस rcu_dereference(dev->rx_handler_data);
पूर्ण

/*
 * RCU usage:
 * The tap_queue and the macvlan_dev are loosely coupled, the
 * poपूर्णांकers from one to the other can only be पढ़ो जबतक rcu_पढ़ो_lock
 * or rtnl is held.
 *
 * Both the file and the macvlan_dev hold a reference on the tap_queue
 * through sock_hold(&q->sk). When the macvlan_dev goes away first,
 * q->vlan becomes inaccessible. When the files माला_लो बंदd,
 * tap_get_queue() fails.
 *
 * There may still be references to the काष्ठा sock inside of the
 * queue from outbound SKBs, but these never reference back to the
 * file or the dev. The data काष्ठाure is मुक्तd through __sk_मुक्त
 * when both our references and any pending SKBs are gone.
 */

अटल पूर्णांक tap_enable_queue(काष्ठा tap_dev *tap, काष्ठा file *file,
			    काष्ठा tap_queue *q)
अणु
	पूर्णांक err = -EINVAL;

	ASSERT_RTNL();

	अगर (q->enabled)
		जाओ out;

	err = 0;
	rcu_assign_poपूर्णांकer(tap->taps[tap->numvtaps], q);
	q->queue_index = tap->numvtaps;
	q->enabled = true;

	tap->numvtaps++;
out:
	वापस err;
पूर्ण

/* Requires RTNL */
अटल पूर्णांक tap_set_queue(काष्ठा tap_dev *tap, काष्ठा file *file,
			 काष्ठा tap_queue *q)
अणु
	अगर (tap->numqueues == MAX_TAP_QUEUES)
		वापस -EBUSY;

	rcu_assign_poपूर्णांकer(q->tap, tap);
	rcu_assign_poपूर्णांकer(tap->taps[tap->numvtaps], q);
	sock_hold(&q->sk);

	q->file = file;
	q->queue_index = tap->numvtaps;
	q->enabled = true;
	file->निजी_data = q;
	list_add_tail(&q->next, &tap->queue_list);

	tap->numvtaps++;
	tap->numqueues++;

	वापस 0;
पूर्ण

अटल पूर्णांक tap_disable_queue(काष्ठा tap_queue *q)
अणु
	काष्ठा tap_dev *tap;
	काष्ठा tap_queue *nq;

	ASSERT_RTNL();
	अगर (!q->enabled)
		वापस -EINVAL;

	tap = rtnl_dereference(q->tap);

	अगर (tap) अणु
		पूर्णांक index = q->queue_index;
		BUG_ON(index >= tap->numvtaps);
		nq = rtnl_dereference(tap->taps[tap->numvtaps - 1]);
		nq->queue_index = index;

		rcu_assign_poपूर्णांकer(tap->taps[index], nq);
		RCU_INIT_POINTER(tap->taps[tap->numvtaps - 1], शून्य);
		q->enabled = false;

		tap->numvtaps--;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The file owning the queue got बंदd, give up both
 * the reference that the files holds as well as the
 * one from the macvlan_dev अगर that still exists.
 *
 * Using the spinlock makes sure that we करोn't get
 * to the queue again after destroying it.
 */
अटल व्योम tap_put_queue(काष्ठा tap_queue *q)
अणु
	काष्ठा tap_dev *tap;

	rtnl_lock();
	tap = rtnl_dereference(q->tap);

	अगर (tap) अणु
		अगर (q->enabled)
			BUG_ON(tap_disable_queue(q));

		tap->numqueues--;
		RCU_INIT_POINTER(q->tap, शून्य);
		sock_put(&q->sk);
		list_del_init(&q->next);
	पूर्ण

	rtnl_unlock();

	synchronize_rcu();
	sock_put(&q->sk);
पूर्ण

/*
 * Select a queue based on the rxq of the device on which this packet
 * arrived. If the incoming device is not mq, calculate a flow hash
 * to select a queue. If all fails, find the first available queue.
 * Cache vlan->numvtaps since it can become zero during the execution
 * of this function.
 */
अटल काष्ठा tap_queue *tap_get_queue(काष्ठा tap_dev *tap,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा tap_queue *queue = शून्य;
	/* Access to taps array is रक्षित by rcu, but access to numvtaps
	 * isn't. Below we use it to lookup a queue, but treat it as a hपूर्णांक
	 * and validate that the result isn't शून्य - in हाल we are
	 * racing against queue removal.
	 */
	पूर्णांक numvtaps = READ_ONCE(tap->numvtaps);
	__u32 rxq;

	अगर (!numvtaps)
		जाओ out;

	अगर (numvtaps == 1)
		जाओ single;

	/* Check अगर we can use flow to select a queue */
	rxq = skb_get_hash(skb);
	अगर (rxq) अणु
		queue = rcu_dereference(tap->taps[rxq % numvtaps]);
		जाओ out;
	पूर्ण

	अगर (likely(skb_rx_queue_recorded(skb))) अणु
		rxq = skb_get_rx_queue(skb);

		जबतक (unlikely(rxq >= numvtaps))
			rxq -= numvtaps;

		queue = rcu_dereference(tap->taps[rxq]);
		जाओ out;
	पूर्ण

single:
	queue = rcu_dereference(tap->taps[0]);
out:
	वापस queue;
पूर्ण

/*
 * The net_device is going away, give up the reference
 * that it holds on all queues and safely set the poपूर्णांकer
 * from the queues to शून्य.
 */
व्योम tap_del_queues(काष्ठा tap_dev *tap)
अणु
	काष्ठा tap_queue *q, *पंचांगp;

	ASSERT_RTNL();
	list_क्रम_each_entry_safe(q, पंचांगp, &tap->queue_list, next) अणु
		list_del_init(&q->next);
		RCU_INIT_POINTER(q->tap, शून्य);
		अगर (q->enabled)
			tap->numvtaps--;
		tap->numqueues--;
		sock_put(&q->sk);
	पूर्ण
	BUG_ON(tap->numvtaps);
	BUG_ON(tap->numqueues);
	/* guarantee that any future tap_set_queue will fail */
	tap->numvtaps = MAX_TAP_QUEUES;
पूर्ण
EXPORT_SYMBOL_GPL(tap_del_queues);

rx_handler_result_t tap_handle_frame(काष्ठा sk_buff **pskb)
अणु
	काष्ठा sk_buff *skb = *pskb;
	काष्ठा net_device *dev = skb->dev;
	काष्ठा tap_dev *tap;
	काष्ठा tap_queue *q;
	netdev_features_t features = TAP_FEATURES;

	tap = tap_dev_get_rcu(dev);
	अगर (!tap)
		वापस RX_HANDLER_PASS;

	q = tap_get_queue(tap, skb);
	अगर (!q)
		वापस RX_HANDLER_PASS;

	skb_push(skb, ETH_HLEN);

	/* Apply the क्रमward feature mask so that we perक्रमm segmentation
	 * according to users wishes.  This only works अगर VNET_HDR is
	 * enabled.
	 */
	अगर (q->flags & IFF_VNET_HDR)
		features |= tap->tap_features;
	अगर (netअगर_needs_gso(skb, features)) अणु
		काष्ठा sk_buff *segs = __skb_gso_segment(skb, features, false);
		काष्ठा sk_buff *next;

		अगर (IS_ERR(segs))
			जाओ drop;

		अगर (!segs) अणु
			अगर (ptr_ring_produce(&q->ring, skb))
				जाओ drop;
			जाओ wake_up;
		पूर्ण

		consume_skb(skb);
		skb_list_walk_safe(segs, skb, next) अणु
			skb_mark_not_on_list(skb);
			अगर (ptr_ring_produce(&q->ring, skb)) अणु
				kमुक्त_skb(skb);
				kमुक्त_skb_list(next);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If we receive a partial checksum and the tap side
		 * करोesn't support checksum offload, compute the checksum.
		 * Note: it करोesn't matter which checksum feature to
		 *	  check, we either support them all or none.
		 */
		अगर (skb->ip_summed == CHECKSUM_PARTIAL &&
		    !(features & NETIF_F_CSUM_MASK) &&
		    skb_checksum_help(skb))
			जाओ drop;
		अगर (ptr_ring_produce(&q->ring, skb))
			जाओ drop;
	पूर्ण

wake_up:
	wake_up_पूर्णांकerruptible_poll(sk_sleep(&q->sk), EPOLLIN | EPOLLRDNORM | EPOLLRDBAND);
	वापस RX_HANDLER_CONSUMED;

drop:
	/* Count errors/drops only here, thus करोn't care about args. */
	अगर (tap->count_rx_dropped)
		tap->count_rx_dropped(tap);
	kमुक्त_skb(skb);
	वापस RX_HANDLER_CONSUMED;
पूर्ण
EXPORT_SYMBOL_GPL(tap_handle_frame);

अटल काष्ठा major_info *tap_get_major(पूर्णांक major)
अणु
	काष्ठा major_info *tap_major;

	list_क्रम_each_entry_rcu(tap_major, &major_list, next) अणु
		अगर (tap_major->major == major)
			वापस tap_major;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक tap_get_minor(dev_t major, काष्ठा tap_dev *tap)
अणु
	पूर्णांक retval = -ENOMEM;
	काष्ठा major_info *tap_major;

	rcu_पढ़ो_lock();
	tap_major = tap_get_major(MAJOR(major));
	अगर (!tap_major) अणु
		retval = -EINVAL;
		जाओ unlock;
	पूर्ण

	spin_lock(&tap_major->minor_lock);
	retval = idr_alloc(&tap_major->minor_idr, tap, 1, TAP_NUM_DEVS, GFP_ATOMIC);
	अगर (retval >= 0) अणु
		tap->minor = retval;
	पूर्ण अन्यथा अगर (retval == -ENOSPC) अणु
		netdev_err(tap->dev, "Too many tap devices\n");
		retval = -EINVAL;
	पूर्ण
	spin_unlock(&tap_major->minor_lock);

unlock:
	rcu_पढ़ो_unlock();
	वापस retval < 0 ? retval : 0;
पूर्ण
EXPORT_SYMBOL_GPL(tap_get_minor);

व्योम tap_मुक्त_minor(dev_t major, काष्ठा tap_dev *tap)
अणु
	काष्ठा major_info *tap_major;

	rcu_पढ़ो_lock();
	tap_major = tap_get_major(MAJOR(major));
	अगर (!tap_major) अणु
		जाओ unlock;
	पूर्ण

	spin_lock(&tap_major->minor_lock);
	अगर (tap->minor) अणु
		idr_हटाओ(&tap_major->minor_idr, tap->minor);
		tap->minor = 0;
	पूर्ण
	spin_unlock(&tap_major->minor_lock);

unlock:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(tap_मुक्त_minor);

अटल काष्ठा tap_dev *dev_get_by_tap_file(पूर्णांक major, पूर्णांक minor)
अणु
	काष्ठा net_device *dev = शून्य;
	काष्ठा tap_dev *tap;
	काष्ठा major_info *tap_major;

	rcu_पढ़ो_lock();
	tap_major = tap_get_major(major);
	अगर (!tap_major) अणु
		tap = शून्य;
		जाओ unlock;
	पूर्ण

	spin_lock(&tap_major->minor_lock);
	tap = idr_find(&tap_major->minor_idr, minor);
	अगर (tap) अणु
		dev = tap->dev;
		dev_hold(dev);
	पूर्ण
	spin_unlock(&tap_major->minor_lock);

unlock:
	rcu_पढ़ो_unlock();
	वापस tap;
पूर्ण

अटल व्योम tap_sock_ग_लिखो_space(काष्ठा sock *sk)
अणु
	रुको_queue_head_t *wqueue;

	अगर (!sock_ग_लिखोable(sk) ||
	    !test_and_clear_bit(SOCKWQ_ASYNC_NOSPACE, &sk->sk_socket->flags))
		वापस;

	wqueue = sk_sleep(sk);
	अगर (wqueue && रुकोqueue_active(wqueue))
		wake_up_पूर्णांकerruptible_poll(wqueue, EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND);
पूर्ण

अटल व्योम tap_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा tap_queue *q = container_of(sk, काष्ठा tap_queue, sk);

	ptr_ring_cleanup(&q->ring, __skb_array_destroy_skb);
पूर्ण

अटल पूर्णांक tap_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा net *net = current->nsproxy->net_ns;
	काष्ठा tap_dev *tap;
	काष्ठा tap_queue *q;
	पूर्णांक err = -ENODEV;

	rtnl_lock();
	tap = dev_get_by_tap_file(imajor(inode), iminor(inode));
	अगर (!tap)
		जाओ err;

	err = -ENOMEM;
	q = (काष्ठा tap_queue *)sk_alloc(net, AF_UNSPEC, GFP_KERNEL,
					     &tap_proto, 0);
	अगर (!q)
		जाओ err;
	अगर (ptr_ring_init(&q->ring, tap->dev->tx_queue_len, GFP_KERNEL)) अणु
		sk_मुक्त(&q->sk);
		जाओ err;
	पूर्ण

	init_रुकोqueue_head(&q->sock.wq.रुको);
	q->sock.type = SOCK_RAW;
	q->sock.state = SS_CONNECTED;
	q->sock.file = file;
	q->sock.ops = &tap_socket_ops;
	sock_init_data(&q->sock, &q->sk);
	q->sk.sk_ग_लिखो_space = tap_sock_ग_लिखो_space;
	q->sk.sk_deकाष्ठा = tap_sock_deकाष्ठा;
	q->flags = IFF_VNET_HDR | IFF_NO_PI | IFF_TAP;
	q->vnet_hdr_sz = माप(काष्ठा virtio_net_hdr);

	/*
	 * so far only KVM virtio_net uses tap, enable zero copy between
	 * guest kernel and host kernel when lower device supports zerocopy
	 *
	 * The macvlan supports zerocopy अगरf the lower device supports zero
	 * copy so we करोn't have to look at the lower device directly.
	 */
	अगर ((tap->dev->features & NETIF_F_HIGHDMA) && (tap->dev->features & NETIF_F_SG))
		sock_set_flag(&q->sk, SOCK_ZEROCOPY);

	err = tap_set_queue(tap, file, q);
	अगर (err) अणु
		/* tap_sock_deकाष्ठा() will take care of मुक्तing ptr_ring */
		जाओ err_put;
	पूर्ण

	dev_put(tap->dev);

	rtnl_unlock();
	वापस err;

err_put:
	sock_put(&q->sk);
err:
	अगर (tap)
		dev_put(tap->dev);

	rtnl_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक tap_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा tap_queue *q = file->निजी_data;
	tap_put_queue(q);
	वापस 0;
पूर्ण

अटल __poll_t tap_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा tap_queue *q = file->निजी_data;
	__poll_t mask = EPOLLERR;

	अगर (!q)
		जाओ out;

	mask = 0;
	poll_रुको(file, &q->sock.wq.रुको, रुको);

	अगर (!ptr_ring_empty(&q->ring))
		mask |= EPOLLIN | EPOLLRDNORM;

	अगर (sock_ग_लिखोable(&q->sk) ||
	    (!test_and_set_bit(SOCKWQ_ASYNC_NOSPACE, &q->sock.flags) &&
	     sock_ग_लिखोable(&q->sk)))
		mask |= EPOLLOUT | EPOLLWRNORM;

out:
	वापस mask;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *tap_alloc_skb(काष्ठा sock *sk, माप_प्रकार prepad,
					    माप_प्रकार len, माप_प्रकार linear,
						पूर्णांक noblock, पूर्णांक *err)
अणु
	काष्ठा sk_buff *skb;

	/* Under a page?  Don't bother with paged skb. */
	अगर (prepad + len < PAGE_SIZE || !linear)
		linear = len;

	skb = sock_alloc_send_pskb(sk, prepad + linear, len - linear, noblock,
				   err, 0);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, prepad);
	skb_put(skb, linear);
	skb->data_len = len - linear;
	skb->len += len - linear;

	वापस skb;
पूर्ण

/* Neighbour code has some assumptions on HH_DATA_MOD alignment */
#घोषणा TAP_RESERVE HH_DATA_OFF(ETH_HLEN)

/* Get packet from user space buffer */
अटल sमाप_प्रकार tap_get_user(काष्ठा tap_queue *q, व्योम *msg_control,
			    काष्ठा iov_iter *from, पूर्णांक noblock)
अणु
	पूर्णांक good_linear = SKB_MAX_HEAD(TAP_RESERVE);
	काष्ठा sk_buff *skb;
	काष्ठा tap_dev *tap;
	अचिन्हित दीर्घ total_len = iov_iter_count(from);
	अचिन्हित दीर्घ len = total_len;
	पूर्णांक err;
	काष्ठा virtio_net_hdr vnet_hdr = अणु 0 पूर्ण;
	पूर्णांक vnet_hdr_len = 0;
	पूर्णांक copylen = 0;
	पूर्णांक depth;
	bool zerocopy = false;
	माप_प्रकार linear;

	अगर (q->flags & IFF_VNET_HDR) अणु
		vnet_hdr_len = READ_ONCE(q->vnet_hdr_sz);

		err = -EINVAL;
		अगर (len < vnet_hdr_len)
			जाओ err;
		len -= vnet_hdr_len;

		err = -EFAULT;
		अगर (!copy_from_iter_full(&vnet_hdr, माप(vnet_hdr), from))
			जाओ err;
		iov_iter_advance(from, vnet_hdr_len - माप(vnet_hdr));
		अगर ((vnet_hdr.flags & VIRTIO_NET_HDR_F_NEEDS_CSUM) &&
		     tap16_to_cpu(q, vnet_hdr.csum_start) +
		     tap16_to_cpu(q, vnet_hdr.csum_offset) + 2 >
			     tap16_to_cpu(q, vnet_hdr.hdr_len))
			vnet_hdr.hdr_len = cpu_to_tap16(q,
				 tap16_to_cpu(q, vnet_hdr.csum_start) +
				 tap16_to_cpu(q, vnet_hdr.csum_offset) + 2);
		err = -EINVAL;
		अगर (tap16_to_cpu(q, vnet_hdr.hdr_len) > len)
			जाओ err;
	पूर्ण

	err = -EINVAL;
	अगर (unlikely(len < ETH_HLEN))
		जाओ err;

	अगर (msg_control && sock_flag(&q->sk, SOCK_ZEROCOPY)) अणु
		काष्ठा iov_iter i;

		copylen = vnet_hdr.hdr_len ?
			tap16_to_cpu(q, vnet_hdr.hdr_len) : GOODCOPY_LEN;
		अगर (copylen > good_linear)
			copylen = good_linear;
		अन्यथा अगर (copylen < ETH_HLEN)
			copylen = ETH_HLEN;
		linear = copylen;
		i = *from;
		iov_iter_advance(&i, copylen);
		अगर (iov_iter_npages(&i, पूर्णांक_उच्च) <= MAX_SKB_FRAGS)
			zerocopy = true;
	पूर्ण

	अगर (!zerocopy) अणु
		copylen = len;
		linear = tap16_to_cpu(q, vnet_hdr.hdr_len);
		अगर (linear > good_linear)
			linear = good_linear;
		अन्यथा अगर (linear < ETH_HLEN)
			linear = ETH_HLEN;
	पूर्ण

	skb = tap_alloc_skb(&q->sk, TAP_RESERVE, copylen,
			    linear, noblock, &err);
	अगर (!skb)
		जाओ err;

	अगर (zerocopy)
		err = zerocopy_sg_from_iter(skb, from);
	अन्यथा
		err = skb_copy_datagram_from_iter(skb, 0, from, len);

	अगर (err)
		जाओ err_kमुक्त;

	skb_set_network_header(skb, ETH_HLEN);
	skb_reset_mac_header(skb);
	skb->protocol = eth_hdr(skb)->h_proto;

	अगर (vnet_hdr_len) अणु
		err = virtio_net_hdr_to_skb(skb, &vnet_hdr,
					    tap_is_little_endian(q));
		अगर (err)
			जाओ err_kमुक्त;
	पूर्ण

	skb_probe_transport_header(skb);

	/* Move network header to the right position क्रम VLAN tagged packets */
	अगर (eth_type_vlan(skb->protocol) &&
	    __vlan_get_protocol(skb, skb->protocol, &depth) != 0)
		skb_set_network_header(skb, depth);

	rcu_पढ़ो_lock();
	tap = rcu_dereference(q->tap);
	/* copy skb_ubuf_info क्रम callback when skb has no error */
	अगर (zerocopy) अणु
		skb_zcopy_init(skb, msg_control);
	पूर्ण अन्यथा अगर (msg_control) अणु
		काष्ठा ubuf_info *uarg = msg_control;
		uarg->callback(शून्य, uarg, false);
	पूर्ण

	अगर (tap) अणु
		skb->dev = tap->dev;
		dev_queue_xmit(skb);
	पूर्ण अन्यथा अणु
		kमुक्त_skb(skb);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस total_len;

err_kमुक्त:
	kमुक्त_skb(skb);

err:
	rcu_पढ़ो_lock();
	tap = rcu_dereference(q->tap);
	अगर (tap && tap->count_tx_dropped)
		tap->count_tx_dropped(tap);
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

अटल sमाप_प्रकार tap_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा tap_queue *q = file->निजी_data;

	वापस tap_get_user(q, शून्य, from, file->f_flags & O_NONBLOCK);
पूर्ण

/* Put packet to the user space buffer */
अटल sमाप_प्रकार tap_put_user(काष्ठा tap_queue *q,
			    स्थिर काष्ठा sk_buff *skb,
			    काष्ठा iov_iter *iter)
अणु
	पूर्णांक ret;
	पूर्णांक vnet_hdr_len = 0;
	पूर्णांक vlan_offset = 0;
	पूर्णांक total;

	अगर (q->flags & IFF_VNET_HDR) अणु
		पूर्णांक vlan_hlen = skb_vlan_tag_present(skb) ? VLAN_HLEN : 0;
		काष्ठा virtio_net_hdr vnet_hdr;

		vnet_hdr_len = READ_ONCE(q->vnet_hdr_sz);
		अगर (iov_iter_count(iter) < vnet_hdr_len)
			वापस -EINVAL;

		अगर (virtio_net_hdr_from_skb(skb, &vnet_hdr,
					    tap_is_little_endian(q), true,
					    vlan_hlen))
			BUG();

		अगर (copy_to_iter(&vnet_hdr, माप(vnet_hdr), iter) !=
		    माप(vnet_hdr))
			वापस -EFAULT;

		iov_iter_advance(iter, vnet_hdr_len - माप(vnet_hdr));
	पूर्ण
	total = vnet_hdr_len;
	total += skb->len;

	अगर (skb_vlan_tag_present(skb)) अणु
		काष्ठा अणु
			__be16 h_vlan_proto;
			__be16 h_vlan_TCI;
		पूर्ण veth;
		veth.h_vlan_proto = skb->vlan_proto;
		veth.h_vlan_TCI = htons(skb_vlan_tag_get(skb));

		vlan_offset = दुरत्व(काष्ठा vlan_ethhdr, h_vlan_proto);
		total += VLAN_HLEN;

		ret = skb_copy_datagram_iter(skb, 0, iter, vlan_offset);
		अगर (ret || !iov_iter_count(iter))
			जाओ करोne;

		ret = copy_to_iter(&veth, माप(veth), iter);
		अगर (ret != माप(veth) || !iov_iter_count(iter))
			जाओ करोne;
	पूर्ण

	ret = skb_copy_datagram_iter(skb, vlan_offset, iter,
				     skb->len - vlan_offset);

करोne:
	वापस ret ? ret : total;
पूर्ण

अटल sमाप_प्रकार tap_करो_पढ़ो(काष्ठा tap_queue *q,
			   काष्ठा iov_iter *to,
			   पूर्णांक noblock, काष्ठा sk_buff *skb)
अणु
	DEFINE_WAIT(रुको);
	sमाप_प्रकार ret = 0;

	अगर (!iov_iter_count(to)) अणु
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	अगर (skb)
		जाओ put;

	जबतक (1) अणु
		अगर (!noblock)
			prepare_to_रुको(sk_sleep(&q->sk), &रुको,
					TASK_INTERRUPTIBLE);

		/* Read frames from the queue */
		skb = ptr_ring_consume(&q->ring);
		अगर (skb)
			अवरोध;
		अगर (noblock) अणु
			ret = -EAGAIN;
			अवरोध;
		पूर्ण
		अगर (संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		/* Nothing to पढ़ो, let's sleep */
		schedule();
	पूर्ण
	अगर (!noblock)
		finish_रुको(sk_sleep(&q->sk), &रुको);

put:
	अगर (skb) अणु
		ret = tap_put_user(q, skb, to);
		अगर (unlikely(ret < 0))
			kमुक्त_skb(skb);
		अन्यथा
			consume_skb(skb);
	पूर्ण
	वापस ret;
पूर्ण

अटल sमाप_प्रकार tap_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा tap_queue *q = file->निजी_data;
	sमाप_प्रकार len = iov_iter_count(to), ret;

	ret = tap_करो_पढ़ो(q, to, file->f_flags & O_NONBLOCK, शून्य);
	ret = min_t(sमाप_प्रकार, ret, len);
	अगर (ret > 0)
		iocb->ki_pos = ret;
	वापस ret;
पूर्ण

अटल काष्ठा tap_dev *tap_get_tap_dev(काष्ठा tap_queue *q)
अणु
	काष्ठा tap_dev *tap;

	ASSERT_RTNL();
	tap = rtnl_dereference(q->tap);
	अगर (tap)
		dev_hold(tap->dev);

	वापस tap;
पूर्ण

अटल व्योम tap_put_tap_dev(काष्ठा tap_dev *tap)
अणु
	dev_put(tap->dev);
पूर्ण

अटल पूर्णांक tap_ioctl_set_queue(काष्ठा file *file, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा tap_queue *q = file->निजी_data;
	काष्ठा tap_dev *tap;
	पूर्णांक ret;

	tap = tap_get_tap_dev(q);
	अगर (!tap)
		वापस -EINVAL;

	अगर (flags & IFF_ATTACH_QUEUE)
		ret = tap_enable_queue(tap, file, q);
	अन्यथा अगर (flags & IFF_DETACH_QUEUE)
		ret = tap_disable_queue(q);
	अन्यथा
		ret = -EINVAL;

	tap_put_tap_dev(tap);
	वापस ret;
पूर्ण

अटल पूर्णांक set_offload(काष्ठा tap_queue *q, अचिन्हित दीर्घ arg)
अणु
	काष्ठा tap_dev *tap;
	netdev_features_t features;
	netdev_features_t feature_mask = 0;

	tap = rtnl_dereference(q->tap);
	अगर (!tap)
		वापस -ENOLINK;

	features = tap->dev->features;

	अगर (arg & TUN_F_CSUM) अणु
		feature_mask = NETIF_F_HW_CSUM;

		अगर (arg & (TUN_F_TSO4 | TUN_F_TSO6)) अणु
			अगर (arg & TUN_F_TSO_ECN)
				feature_mask |= NETIF_F_TSO_ECN;
			अगर (arg & TUN_F_TSO4)
				feature_mask |= NETIF_F_TSO;
			अगर (arg & TUN_F_TSO6)
				feature_mask |= NETIF_F_TSO6;
		पूर्ण
	पूर्ण

	/* tun/tap driver inverts the usage क्रम TSO offloads, where
	 * setting the TSO bit means that the userspace wants to
	 * accept TSO frames and turning it off means that user space
	 * करोes not support TSO.
	 * For tap, we have to invert it to mean the same thing.
	 * When user space turns off TSO, we turn off GSO/LRO so that
	 * user-space will not receive TSO frames.
	 */
	अगर (feature_mask & (NETIF_F_TSO | NETIF_F_TSO6))
		features |= RX_OFFLOADS;
	अन्यथा
		features &= ~RX_OFFLOADS;

	/* tap_features are the same as features on tun/tap and
	 * reflect user expectations.
	 */
	tap->tap_features = feature_mask;
	अगर (tap->update_features)
		tap->update_features(tap, features);

	वापस 0;
पूर्ण

/*
 * provide compatibility with generic tun/tap पूर्णांकerface
 */
अटल दीर्घ tap_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
		      अचिन्हित दीर्घ arg)
अणु
	काष्ठा tap_queue *q = file->निजी_data;
	काष्ठा tap_dev *tap;
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा अगरreq __user *अगरr = argp;
	अचिन्हित पूर्णांक __user *up = argp;
	अचिन्हित लघु u;
	पूर्णांक __user *sp = argp;
	काष्ठा sockaddr sa;
	पूर्णांक s;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल TUNSETIFF:
		/* ignore the name, just look at flags */
		अगर (get_user(u, &अगरr->अगरr_flags))
			वापस -EFAULT;

		ret = 0;
		अगर ((u & ~TAP_IFFEATURES) != (IFF_NO_PI | IFF_TAP))
			ret = -EINVAL;
		अन्यथा
			q->flags = (q->flags & ~TAP_IFFEATURES) | u;

		वापस ret;

	हाल TUNGETIFF:
		rtnl_lock();
		tap = tap_get_tap_dev(q);
		अगर (!tap) अणु
			rtnl_unlock();
			वापस -ENOLINK;
		पूर्ण

		ret = 0;
		u = q->flags;
		अगर (copy_to_user(&अगरr->अगरr_name, tap->dev->name, IFNAMSIZ) ||
		    put_user(u, &अगरr->अगरr_flags))
			ret = -EFAULT;
		tap_put_tap_dev(tap);
		rtnl_unlock();
		वापस ret;

	हाल TUNSETQUEUE:
		अगर (get_user(u, &अगरr->अगरr_flags))
			वापस -EFAULT;
		rtnl_lock();
		ret = tap_ioctl_set_queue(file, u);
		rtnl_unlock();
		वापस ret;

	हाल TUNGETFEATURES:
		अगर (put_user(IFF_TAP | IFF_NO_PI | TAP_IFFEATURES, up))
			वापस -EFAULT;
		वापस 0;

	हाल TUNSETSNDBUF:
		अगर (get_user(s, sp))
			वापस -EFAULT;
		अगर (s <= 0)
			वापस -EINVAL;

		q->sk.sk_sndbuf = s;
		वापस 0;

	हाल TUNGETVNETHDRSZ:
		s = q->vnet_hdr_sz;
		अगर (put_user(s, sp))
			वापस -EFAULT;
		वापस 0;

	हाल TUNSETVNETHDRSZ:
		अगर (get_user(s, sp))
			वापस -EFAULT;
		अगर (s < (पूर्णांक)माप(काष्ठा virtio_net_hdr))
			वापस -EINVAL;

		q->vnet_hdr_sz = s;
		वापस 0;

	हाल TUNGETVNETLE:
		s = !!(q->flags & TAP_VNET_LE);
		अगर (put_user(s, sp))
			वापस -EFAULT;
		वापस 0;

	हाल TUNSETVNETLE:
		अगर (get_user(s, sp))
			वापस -EFAULT;
		अगर (s)
			q->flags |= TAP_VNET_LE;
		अन्यथा
			q->flags &= ~TAP_VNET_LE;
		वापस 0;

	हाल TUNGETVNETBE:
		वापस tap_get_vnet_be(q, sp);

	हाल TUNSETVNETBE:
		वापस tap_set_vnet_be(q, sp);

	हाल TUNSETOFFLOAD:
		/* let the user check क्रम future flags */
		अगर (arg & ~(TUN_F_CSUM | TUN_F_TSO4 | TUN_F_TSO6 |
			    TUN_F_TSO_ECN | TUN_F_UFO))
			वापस -EINVAL;

		rtnl_lock();
		ret = set_offload(q, arg);
		rtnl_unlock();
		वापस ret;

	हाल SIOCGIFHWADDR:
		rtnl_lock();
		tap = tap_get_tap_dev(q);
		अगर (!tap) अणु
			rtnl_unlock();
			वापस -ENOLINK;
		पूर्ण
		ret = 0;
		dev_get_mac_address(&sa, dev_net(tap->dev), tap->dev->name);
		अगर (copy_to_user(&अगरr->अगरr_name, tap->dev->name, IFNAMSIZ) ||
		    copy_to_user(&अगरr->अगरr_hwaddr, &sa, माप(sa)))
			ret = -EFAULT;
		tap_put_tap_dev(tap);
		rtnl_unlock();
		वापस ret;

	हाल SIOCSIFHWADDR:
		अगर (copy_from_user(&sa, &अगरr->अगरr_hwaddr, माप(sa)))
			वापस -EFAULT;
		rtnl_lock();
		tap = tap_get_tap_dev(q);
		अगर (!tap) अणु
			rtnl_unlock();
			वापस -ENOLINK;
		पूर्ण
		ret = dev_set_mac_address_user(tap->dev, &sa, शून्य);
		tap_put_tap_dev(tap);
		rtnl_unlock();
		वापस ret;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations tap_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= tap_खोलो,
	.release	= tap_release,
	.पढ़ो_iter	= tap_पढ़ो_iter,
	.ग_लिखो_iter	= tap_ग_लिखो_iter,
	.poll		= tap_poll,
	.llseek		= no_llseek,
	.unlocked_ioctl	= tap_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
पूर्ण;

अटल पूर्णांक tap_get_user_xdp(काष्ठा tap_queue *q, काष्ठा xdp_buff *xdp)
अणु
	काष्ठा tun_xdp_hdr *hdr = xdp->data_hard_start;
	काष्ठा virtio_net_hdr *gso = &hdr->gso;
	पूर्णांक buflen = hdr->buflen;
	पूर्णांक vnet_hdr_len = 0;
	काष्ठा tap_dev *tap;
	काष्ठा sk_buff *skb;
	पूर्णांक err, depth;

	अगर (q->flags & IFF_VNET_HDR)
		vnet_hdr_len = READ_ONCE(q->vnet_hdr_sz);

	skb = build_skb(xdp->data_hard_start, buflen);
	अगर (!skb) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	skb_reserve(skb, xdp->data - xdp->data_hard_start);
	skb_put(skb, xdp->data_end - xdp->data);

	skb_set_network_header(skb, ETH_HLEN);
	skb_reset_mac_header(skb);
	skb->protocol = eth_hdr(skb)->h_proto;

	अगर (vnet_hdr_len) अणु
		err = virtio_net_hdr_to_skb(skb, gso, tap_is_little_endian(q));
		अगर (err)
			जाओ err_kमुक्त;
	पूर्ण

	/* Move network header to the right position क्रम VLAN tagged packets */
	अगर (eth_type_vlan(skb->protocol) &&
	    __vlan_get_protocol(skb, skb->protocol, &depth) != 0)
		skb_set_network_header(skb, depth);

	rcu_पढ़ो_lock();
	tap = rcu_dereference(q->tap);
	अगर (tap) अणु
		skb->dev = tap->dev;
		skb_probe_transport_header(skb);
		dev_queue_xmit(skb);
	पूर्ण अन्यथा अणु
		kमुक्त_skb(skb);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस 0;

err_kमुक्त:
	kमुक्त_skb(skb);
err:
	rcu_पढ़ो_lock();
	tap = rcu_dereference(q->tap);
	अगर (tap && tap->count_tx_dropped)
		tap->count_tx_dropped(tap);
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक tap_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *m,
		       माप_प्रकार total_len)
अणु
	काष्ठा tap_queue *q = container_of(sock, काष्ठा tap_queue, sock);
	काष्ठा tun_msg_ctl *ctl = m->msg_control;
	काष्ठा xdp_buff *xdp;
	पूर्णांक i;

	अगर (ctl && (ctl->type == TUN_MSG_PTR)) अणु
		क्रम (i = 0; i < ctl->num; i++) अणु
			xdp = &((काष्ठा xdp_buff *)ctl->ptr)[i];
			tap_get_user_xdp(q, xdp);
		पूर्ण
		वापस 0;
	पूर्ण

	वापस tap_get_user(q, ctl ? ctl->ptr : शून्य, &m->msg_iter,
			    m->msg_flags & MSG_DONTWAIT);
पूर्ण

अटल पूर्णांक tap_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *m,
		       माप_प्रकार total_len, पूर्णांक flags)
अणु
	काष्ठा tap_queue *q = container_of(sock, काष्ठा tap_queue, sock);
	काष्ठा sk_buff *skb = m->msg_control;
	पूर्णांक ret;
	अगर (flags & ~(MSG_DONTWAIT|MSG_TRUNC)) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण
	ret = tap_करो_पढ़ो(q, &m->msg_iter, flags & MSG_DONTWAIT, skb);
	अगर (ret > total_len) अणु
		m->msg_flags |= MSG_TRUNC;
		ret = flags & MSG_TRUNC ? ret : total_len;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक tap_peek_len(काष्ठा socket *sock)
अणु
	काष्ठा tap_queue *q = container_of(sock, काष्ठा tap_queue,
					       sock);
	वापस PTR_RING_PEEK_CALL(&q->ring, __skb_array_len_with_tag);
पूर्ण

/* Ops काष्ठाure to mimic raw sockets with tun */
अटल स्थिर काष्ठा proto_ops tap_socket_ops = अणु
	.sendmsg = tap_sendmsg,
	.recvmsg = tap_recvmsg,
	.peek_len = tap_peek_len,
पूर्ण;

/* Get an underlying socket object from tun file.  Returns error unless file is
 * attached to a device.  The वापसed object works like a packet socket, it
 * can be used क्रम sock_sendmsg/sock_recvmsg.  The caller is responsible क्रम
 * holding a reference to the file क्रम as दीर्घ as the socket is in use. */
काष्ठा socket *tap_get_socket(काष्ठा file *file)
अणु
	काष्ठा tap_queue *q;
	अगर (file->f_op != &tap_fops)
		वापस ERR_PTR(-EINVAL);
	q = file->निजी_data;
	अगर (!q)
		वापस ERR_PTR(-EBADFD);
	वापस &q->sock;
पूर्ण
EXPORT_SYMBOL_GPL(tap_get_socket);

काष्ठा ptr_ring *tap_get_ptr_ring(काष्ठा file *file)
अणु
	काष्ठा tap_queue *q;

	अगर (file->f_op != &tap_fops)
		वापस ERR_PTR(-EINVAL);
	q = file->निजी_data;
	अगर (!q)
		वापस ERR_PTR(-EBADFD);
	वापस &q->ring;
पूर्ण
EXPORT_SYMBOL_GPL(tap_get_ptr_ring);

पूर्णांक tap_queue_resize(काष्ठा tap_dev *tap)
अणु
	काष्ठा net_device *dev = tap->dev;
	काष्ठा tap_queue *q;
	काष्ठा ptr_ring **rings;
	पूर्णांक n = tap->numqueues;
	पूर्णांक ret, i = 0;

	rings = kदो_स्मृति_array(n, माप(*rings), GFP_KERNEL);
	अगर (!rings)
		वापस -ENOMEM;

	list_क्रम_each_entry(q, &tap->queue_list, next)
		rings[i++] = &q->ring;

	ret = ptr_ring_resize_multiple(rings, n,
				       dev->tx_queue_len, GFP_KERNEL,
				       __skb_array_destroy_skb);

	kमुक्त(rings);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tap_queue_resize);

अटल पूर्णांक tap_list_add(dev_t major, स्थिर अक्षर *device_name)
अणु
	काष्ठा major_info *tap_major;

	tap_major = kzalloc(माप(*tap_major), GFP_ATOMIC);
	अगर (!tap_major)
		वापस -ENOMEM;

	tap_major->major = MAJOR(major);

	idr_init(&tap_major->minor_idr);
	spin_lock_init(&tap_major->minor_lock);

	tap_major->device_name = device_name;

	list_add_tail_rcu(&tap_major->next, &major_list);
	वापस 0;
पूर्ण

पूर्णांक tap_create_cdev(काष्ठा cdev *tap_cdev, dev_t *tap_major,
		    स्थिर अक्षर *device_name, काष्ठा module *module)
अणु
	पूर्णांक err;

	err = alloc_chrdev_region(tap_major, 0, TAP_NUM_DEVS, device_name);
	अगर (err)
		जाओ out1;

	cdev_init(tap_cdev, &tap_fops);
	tap_cdev->owner = module;
	err = cdev_add(tap_cdev, *tap_major, TAP_NUM_DEVS);
	अगर (err)
		जाओ out2;

	err =  tap_list_add(*tap_major, device_name);
	अगर (err)
		जाओ out3;

	वापस 0;

out3:
	cdev_del(tap_cdev);
out2:
	unरेजिस्टर_chrdev_region(*tap_major, TAP_NUM_DEVS);
out1:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(tap_create_cdev);

व्योम tap_destroy_cdev(dev_t major, काष्ठा cdev *tap_cdev)
अणु
	काष्ठा major_info *tap_major, *पंचांगp;

	cdev_del(tap_cdev);
	unरेजिस्टर_chrdev_region(major, TAP_NUM_DEVS);
	list_क्रम_each_entry_safe(tap_major, पंचांगp, &major_list, next) अणु
		अगर (tap_major->major == MAJOR(major)) अणु
			idr_destroy(&tap_major->minor_idr);
			list_del_rcu(&tap_major->next);
			kमुक्त_rcu(tap_major, rcu);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(tap_destroy_cdev);

MODULE_AUTHOR("Arnd Bergmann <arnd@arndb.de>");
MODULE_AUTHOR("Sainath Grandhi <sainath.grandhi@intel.com>");
MODULE_LICENSE("GPL");
