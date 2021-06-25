<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* net/aपंचांग/common.c - ATM sockets (common part क्रम PVC and SVC) */

/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/module.h>
#समावेश <linux/kmod.h>
#समावेश <linux/net.h>		/* काष्ठा socket, काष्ठा proto_ops */
#समावेश <linux/aपंचांग.h>		/* ATM stuff */
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/socket.h>	/* SOL_SOCKET */
#समावेश <linux/त्रुटिसं.स>	/* error codes */
#समावेश <linux/capability.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/समय64.h>	/* 64-bit समय क्रम seconds */
#समावेश <linux/skbuff.h>
#समावेश <linux/bitops.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>		/* काष्ठा sock */
#समावेश <linux/uaccess.h>
#समावेश <linux/poll.h>

#समावेश <linux/atomic.h>

#समावेश "resources.h"		/* aपंचांग_find_dev */
#समावेश "common.h"		/* prototypes */
#समावेश "protocols.h"		/* aपंचांग_init_<transport> */
#समावेश "addr.h"		/* address registry */
#समावेश "signaling.h"		/* क्रम WAITING and sigd_attach */

काष्ठा hlist_head vcc_hash[VCC_HTABLE_SIZE];
EXPORT_SYMBOL(vcc_hash);

DEFINE_RWLOCK(vcc_sklist_lock);
EXPORT_SYMBOL(vcc_sklist_lock);

अटल ATOMIC_NOTIFIER_HEAD(aपंचांग_dev_notअगरy_chain);

अटल व्योम __vcc_insert_socket(काष्ठा sock *sk)
अणु
	काष्ठा aपंचांग_vcc *vcc = aपंचांग_sk(sk);
	काष्ठा hlist_head *head = &vcc_hash[vcc->vci & (VCC_HTABLE_SIZE - 1)];
	sk->sk_hash = vcc->vci & (VCC_HTABLE_SIZE - 1);
	sk_add_node(sk, head);
पूर्ण

व्योम vcc_insert_socket(काष्ठा sock *sk)
अणु
	ग_लिखो_lock_irq(&vcc_sklist_lock);
	__vcc_insert_socket(sk);
	ग_लिखो_unlock_irq(&vcc_sklist_lock);
पूर्ण
EXPORT_SYMBOL(vcc_insert_socket);

अटल व्योम vcc_हटाओ_socket(काष्ठा sock *sk)
अणु
	ग_लिखो_lock_irq(&vcc_sklist_lock);
	sk_del_node_init(sk);
	ग_लिखो_unlock_irq(&vcc_sklist_lock);
पूर्ण

अटल bool vcc_tx_पढ़ोy(काष्ठा aपंचांग_vcc *vcc, अचिन्हित पूर्णांक size)
अणु
	काष्ठा sock *sk = sk_aपंचांग(vcc);

	अगर (sk_wmem_alloc_get(sk) && !aपंचांग_may_send(vcc, size)) अणु
		pr_debug("Sorry: wmem_alloc = %d, size = %d, sndbuf = %d\n",
			 sk_wmem_alloc_get(sk), size, sk->sk_sndbuf);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम vcc_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc))
		prपूर्णांकk(KERN_DEBUG "%s: rmem leakage (%d bytes) detected.\n",
		       __func__, atomic_पढ़ो(&sk->sk_rmem_alloc));

	अगर (refcount_पढ़ो(&sk->sk_wmem_alloc))
		prपूर्णांकk(KERN_DEBUG "%s: wmem leakage (%d bytes) detected.\n",
		       __func__, refcount_पढ़ो(&sk->sk_wmem_alloc));
पूर्ण

अटल व्योम vcc_def_wakeup(काष्ठा sock *sk)
अणु
	काष्ठा socket_wq *wq;

	rcu_पढ़ो_lock();
	wq = rcu_dereference(sk->sk_wq);
	अगर (skwq_has_sleeper(wq))
		wake_up(&wq->रुको);
	rcu_पढ़ो_unlock();
पूर्ण

अटल अंतरभूत पूर्णांक vcc_writable(काष्ठा sock *sk)
अणु
	काष्ठा aपंचांग_vcc *vcc = aपंचांग_sk(sk);

	वापस (vcc->qos.txtp.max_sdu +
		refcount_पढ़ो(&sk->sk_wmem_alloc)) <= sk->sk_sndbuf;
पूर्ण

अटल व्योम vcc_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा socket_wq *wq;

	rcu_पढ़ो_lock();

	अगर (vcc_writable(sk)) अणु
		wq = rcu_dereference(sk->sk_wq);
		अगर (skwq_has_sleeper(wq))
			wake_up_पूर्णांकerruptible(&wq->रुको);

		sk_wake_async(sk, SOCK_WAKE_SPACE, POLL_OUT);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम vcc_release_cb(काष्ठा sock *sk)
अणु
	काष्ठा aपंचांग_vcc *vcc = aपंचांग_sk(sk);

	अगर (vcc->release_cb)
		vcc->release_cb(vcc);
पूर्ण

अटल काष्ठा proto vcc_proto = अणु
	.name	  = "VCC",
	.owner	  = THIS_MODULE,
	.obj_size = माप(काष्ठा aपंचांग_vcc),
	.release_cb = vcc_release_cb,
पूर्ण;

पूर्णांक vcc_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol, पूर्णांक family, पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	काष्ठा aपंचांग_vcc *vcc;

	sock->sk = शून्य;
	अगर (sock->type == SOCK_STREAM)
		वापस -EINVAL;
	sk = sk_alloc(net, family, GFP_KERNEL, &vcc_proto, kern);
	अगर (!sk)
		वापस -ENOMEM;
	sock_init_data(sock, sk);
	sk->sk_state_change = vcc_def_wakeup;
	sk->sk_ग_लिखो_space = vcc_ग_लिखो_space;

	vcc = aपंचांग_sk(sk);
	vcc->dev = शून्य;
	स_रखो(&vcc->local, 0, माप(काष्ठा sockaddr_aपंचांगsvc));
	स_रखो(&vcc->remote, 0, माप(काष्ठा sockaddr_aपंचांगsvc));
	vcc->qos.txtp.max_sdu = 1 << 16; /* क्रम meta VCs */
	refcount_set(&sk->sk_wmem_alloc, 1);
	atomic_set(&sk->sk_rmem_alloc, 0);
	vcc->push = शून्य;
	vcc->pop = शून्य;
	vcc->owner = शून्य;
	vcc->push_oam = शून्य;
	vcc->release_cb = शून्य;
	vcc->vpi = vcc->vci = 0; /* no VCI/VPI yet */
	vcc->aपंचांग_options = vcc->aal_options = 0;
	sk->sk_deकाष्ठा = vcc_sock_deकाष्ठा;
	वापस 0;
पूर्ण

अटल व्योम vcc_destroy_socket(काष्ठा sock *sk)
अणु
	काष्ठा aपंचांग_vcc *vcc = aपंचांग_sk(sk);
	काष्ठा sk_buff *skb;

	set_bit(ATM_VF_CLOSE, &vcc->flags);
	clear_bit(ATM_VF_READY, &vcc->flags);
	अगर (vcc->dev && vcc->dev->ops->बंद)
		vcc->dev->ops->बंद(vcc);
	अगर (vcc->push)
		vcc->push(vcc, शून्य); /* aपंचांगarpd has no push */
	module_put(vcc->owner);

	जबतक ((skb = skb_dequeue(&sk->sk_receive_queue)) != शून्य) अणु
		aपंचांग_वापस(vcc, skb->truesize);
		kमुक्त_skb(skb);
	पूर्ण

	अगर (vcc->dev && vcc->dev->ops->owner) अणु
		module_put(vcc->dev->ops->owner);
		aपंचांग_dev_put(vcc->dev);
	पूर्ण

	vcc_हटाओ_socket(sk);
पूर्ण

पूर्णांक vcc_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (sk) अणु
		lock_sock(sk);
		vcc_destroy_socket(sock->sk);
		release_sock(sk);
		sock_put(sk);
	पूर्ण

	वापस 0;
पूर्ण

व्योम vcc_release_async(काष्ठा aपंचांग_vcc *vcc, पूर्णांक reply)
अणु
	काष्ठा sock *sk = sk_aपंचांग(vcc);

	set_bit(ATM_VF_CLOSE, &vcc->flags);
	sk->sk_shutकरोwn |= RCV_SHUTDOWN;
	sk->sk_err = -reply;
	clear_bit(ATM_VF_WAITING, &vcc->flags);
	sk->sk_state_change(sk);
पूर्ण
EXPORT_SYMBOL(vcc_release_async);

व्योम vcc_process_recv_queue(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा sk_buff_head queue, *rq;
	काष्ठा sk_buff *skb, *पंचांगp;
	अचिन्हित दीर्घ flags;

	__skb_queue_head_init(&queue);
	rq = &sk_aपंचांग(vcc)->sk_receive_queue;

	spin_lock_irqsave(&rq->lock, flags);
	skb_queue_splice_init(rq, &queue);
	spin_unlock_irqrestore(&rq->lock, flags);

	skb_queue_walk_safe(&queue, skb, पंचांगp) अणु
		__skb_unlink(skb, &queue);
		vcc->push(vcc, skb);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(vcc_process_recv_queue);

व्योम aपंचांग_dev_संकेत_change(काष्ठा aपंचांग_dev *dev, अक्षर संकेत)
अणु
	pr_debug("%s signal=%d dev=%p number=%d dev->signal=%d\n",
		__func__, संकेत, dev, dev->number, dev->संकेत);

	/* aपंचांग driver sending invalid संकेत */
	WARN_ON(संकेत < ATM_PHY_SIG_LOST || संकेत > ATM_PHY_SIG_FOUND);

	अगर (dev->संकेत == संकेत)
		वापस; /* no change */

	dev->संकेत = संकेत;

	atomic_notअगरier_call_chain(&aपंचांग_dev_notअगरy_chain, संकेत, dev);
पूर्ण
EXPORT_SYMBOL(aपंचांग_dev_संकेत_change);

व्योम aपंचांग_dev_release_vccs(काष्ठा aपंचांग_dev *dev)
अणु
	पूर्णांक i;

	ग_लिखो_lock_irq(&vcc_sklist_lock);
	क्रम (i = 0; i < VCC_HTABLE_SIZE; i++) अणु
		काष्ठा hlist_head *head = &vcc_hash[i];
		काष्ठा hlist_node *पंचांगp;
		काष्ठा sock *s;
		काष्ठा aपंचांग_vcc *vcc;

		sk_क्रम_each_safe(s, पंचांगp, head) अणु
			vcc = aपंचांग_sk(s);
			अगर (vcc->dev == dev) अणु
				vcc_release_async(vcc, -EPIPE);
				sk_del_node_init(s);
			पूर्ण
		पूर्ण
	पूर्ण
	ग_लिखो_unlock_irq(&vcc_sklist_lock);
पूर्ण
EXPORT_SYMBOL(aपंचांग_dev_release_vccs);

अटल पूर्णांक adjust_tp(काष्ठा aपंचांग_trafprm *tp, अचिन्हित अक्षर aal)
अणु
	पूर्णांक max_sdu;

	अगर (!tp->traffic_class)
		वापस 0;
	चयन (aal) अणु
	हाल ATM_AAL0:
		max_sdu = ATM_CELL_SIZE-1;
		अवरोध;
	हाल ATM_AAL34:
		max_sdu = ATM_MAX_AAL34_PDU;
		अवरोध;
	शेष:
		pr_warn("AAL problems ... (%d)\n", aal);
		fallthrough;
	हाल ATM_AAL5:
		max_sdu = ATM_MAX_AAL5_PDU;
	पूर्ण
	अगर (!tp->max_sdu)
		tp->max_sdu = max_sdu;
	अन्यथा अगर (tp->max_sdu > max_sdu)
		वापस -EINVAL;
	अगर (!tp->max_cdv)
		tp->max_cdv = ATM_MAX_CDV;
	वापस 0;
पूर्ण

अटल पूर्णांक check_ci(स्थिर काष्ठा aपंचांग_vcc *vcc, लघु vpi, पूर्णांक vci)
अणु
	काष्ठा hlist_head *head = &vcc_hash[vci & (VCC_HTABLE_SIZE - 1)];
	काष्ठा sock *s;
	काष्ठा aपंचांग_vcc *walk;

	sk_क्रम_each(s, head) अणु
		walk = aपंचांग_sk(s);
		अगर (walk->dev != vcc->dev)
			जारी;
		अगर (test_bit(ATM_VF_ADDR, &walk->flags) && walk->vpi == vpi &&
		    walk->vci == vci && ((walk->qos.txtp.traffic_class !=
		    ATM_NONE && vcc->qos.txtp.traffic_class != ATM_NONE) ||
		    (walk->qos.rxtp.traffic_class != ATM_NONE &&
		    vcc->qos.rxtp.traffic_class != ATM_NONE)))
			वापस -EADDRINUSE;
	पूर्ण

	/* allow VCCs with same VPI/VCI अगरf they करोn't collide on
	   TX/RX (but we may refuse such sharing क्रम other reasons,
	   e.g. अगर protocol requires to have both channels) */

	वापस 0;
पूर्ण

अटल पूर्णांक find_ci(स्थिर काष्ठा aपंचांग_vcc *vcc, लघु *vpi, पूर्णांक *vci)
अणु
	अटल लघु p;        /* poor man's per-device cache */
	अटल पूर्णांक c;
	लघु old_p;
	पूर्णांक old_c;
	पूर्णांक err;

	अगर (*vpi != ATM_VPI_ANY && *vci != ATM_VCI_ANY) अणु
		err = check_ci(vcc, *vpi, *vci);
		वापस err;
	पूर्ण
	/* last scan may have left values out of bounds क्रम current device */
	अगर (*vpi != ATM_VPI_ANY)
		p = *vpi;
	अन्यथा अगर (p >= 1 << vcc->dev->ci_range.vpi_bits)
		p = 0;
	अगर (*vci != ATM_VCI_ANY)
		c = *vci;
	अन्यथा अगर (c < ATM_NOT_RSV_VCI || c >= 1 << vcc->dev->ci_range.vci_bits)
			c = ATM_NOT_RSV_VCI;
	old_p = p;
	old_c = c;
	करो अणु
		अगर (!check_ci(vcc, p, c)) अणु
			*vpi = p;
			*vci = c;
			वापस 0;
		पूर्ण
		अगर (*vci == ATM_VCI_ANY) अणु
			c++;
			अगर (c >= 1 << vcc->dev->ci_range.vci_bits)
				c = ATM_NOT_RSV_VCI;
		पूर्ण
		अगर ((c == ATM_NOT_RSV_VCI || *vci != ATM_VCI_ANY) &&
		    *vpi == ATM_VPI_ANY) अणु
			p++;
			अगर (p >= 1 << vcc->dev->ci_range.vpi_bits)
				p = 0;
		पूर्ण
	पूर्ण जबतक (old_p != p || old_c != c);
	वापस -EADDRINUSE;
पूर्ण

अटल पूर्णांक __vcc_connect(काष्ठा aपंचांग_vcc *vcc, काष्ठा aपंचांग_dev *dev, लघु vpi,
			 पूर्णांक vci)
अणु
	काष्ठा sock *sk = sk_aपंचांग(vcc);
	पूर्णांक error;

	अगर ((vpi != ATM_VPI_UNSPEC && vpi != ATM_VPI_ANY &&
	    vpi >> dev->ci_range.vpi_bits) || (vci != ATM_VCI_UNSPEC &&
	    vci != ATM_VCI_ANY && vci >> dev->ci_range.vci_bits))
		वापस -EINVAL;
	अगर (vci > 0 && vci < ATM_NOT_RSV_VCI && !capable(CAP_NET_BIND_SERVICE))
		वापस -EPERM;
	error = -ENODEV;
	अगर (!try_module_get(dev->ops->owner))
		वापस error;
	vcc->dev = dev;
	ग_लिखो_lock_irq(&vcc_sklist_lock);
	अगर (test_bit(ATM_DF_REMOVED, &dev->flags) ||
	    (error = find_ci(vcc, &vpi, &vci))) अणु
		ग_लिखो_unlock_irq(&vcc_sklist_lock);
		जाओ fail_module_put;
	पूर्ण
	vcc->vpi = vpi;
	vcc->vci = vci;
	__vcc_insert_socket(sk);
	ग_लिखो_unlock_irq(&vcc_sklist_lock);
	चयन (vcc->qos.aal) अणु
	हाल ATM_AAL0:
		error = aपंचांग_init_aal0(vcc);
		vcc->stats = &dev->stats.aal0;
		अवरोध;
	हाल ATM_AAL34:
		error = aपंचांग_init_aal34(vcc);
		vcc->stats = &dev->stats.aal34;
		अवरोध;
	हाल ATM_NO_AAL:
		/* ATM_AAL5 is also used in the "0 for default" हाल */
		vcc->qos.aal = ATM_AAL5;
		fallthrough;
	हाल ATM_AAL5:
		error = aपंचांग_init_aal5(vcc);
		vcc->stats = &dev->stats.aal5;
		अवरोध;
	शेष:
		error = -EPROTOTYPE;
	पूर्ण
	अगर (!error)
		error = adjust_tp(&vcc->qos.txtp, vcc->qos.aal);
	अगर (!error)
		error = adjust_tp(&vcc->qos.rxtp, vcc->qos.aal);
	अगर (error)
		जाओ fail;
	pr_debug("VCC %d.%d, AAL %d\n", vpi, vci, vcc->qos.aal);
	pr_debug("  TX: %d, PCR %d..%d, SDU %d\n",
		 vcc->qos.txtp.traffic_class,
		 vcc->qos.txtp.min_pcr,
		 vcc->qos.txtp.max_pcr,
		 vcc->qos.txtp.max_sdu);
	pr_debug("  RX: %d, PCR %d..%d, SDU %d\n",
		 vcc->qos.rxtp.traffic_class,
		 vcc->qos.rxtp.min_pcr,
		 vcc->qos.rxtp.max_pcr,
		 vcc->qos.rxtp.max_sdu);

	अगर (dev->ops->खोलो) अणु
		error = dev->ops->खोलो(vcc);
		अगर (error)
			जाओ fail;
	पूर्ण
	वापस 0;

fail:
	vcc_हटाओ_socket(sk);
fail_module_put:
	module_put(dev->ops->owner);
	/* ensure we get dev module ref count correct */
	vcc->dev = शून्य;
	वापस error;
पूर्ण

पूर्णांक vcc_connect(काष्ठा socket *sock, पूर्णांक itf, लघु vpi, पूर्णांक vci)
अणु
	काष्ठा aपंचांग_dev *dev;
	काष्ठा aपंचांग_vcc *vcc = ATM_SD(sock);
	पूर्णांक error;

	pr_debug("(vpi %d, vci %d)\n", vpi, vci);
	अगर (sock->state == SS_CONNECTED)
		वापस -EISCONN;
	अगर (sock->state != SS_UNCONNECTED)
		वापस -EINVAL;
	अगर (!(vpi || vci))
		वापस -EINVAL;

	अगर (vpi != ATM_VPI_UNSPEC && vci != ATM_VCI_UNSPEC)
		clear_bit(ATM_VF_PARTIAL, &vcc->flags);
	अन्यथा
		अगर (test_bit(ATM_VF_PARTIAL, &vcc->flags))
			वापस -EINVAL;
	pr_debug("(TX: cl %d,bw %d-%d,sdu %d; "
		 "RX: cl %d,bw %d-%d,sdu %d,AAL %s%d)\n",
		 vcc->qos.txtp.traffic_class, vcc->qos.txtp.min_pcr,
		 vcc->qos.txtp.max_pcr, vcc->qos.txtp.max_sdu,
		 vcc->qos.rxtp.traffic_class, vcc->qos.rxtp.min_pcr,
		 vcc->qos.rxtp.max_pcr, vcc->qos.rxtp.max_sdu,
		 vcc->qos.aal == ATM_AAL5 ? "" :
		 vcc->qos.aal == ATM_AAL0 ? "" : " ??? code ",
		 vcc->qos.aal == ATM_AAL0 ? 0 : vcc->qos.aal);
	अगर (!test_bit(ATM_VF_HASQOS, &vcc->flags))
		वापस -EBADFD;
	अगर (vcc->qos.txtp.traffic_class == ATM_ANYCLASS ||
	    vcc->qos.rxtp.traffic_class == ATM_ANYCLASS)
		वापस -EINVAL;
	अगर (likely(itf != ATM_ITF_ANY)) अणु
		dev = try_then_request_module(aपंचांग_dev_lookup(itf),
					      "atm-device-%d", itf);
	पूर्ण अन्यथा अणु
		dev = शून्य;
		mutex_lock(&aपंचांग_dev_mutex);
		अगर (!list_empty(&aपंचांग_devs)) अणु
			dev = list_entry(aपंचांग_devs.next,
					 काष्ठा aपंचांग_dev, dev_list);
			aपंचांग_dev_hold(dev);
		पूर्ण
		mutex_unlock(&aपंचांग_dev_mutex);
	पूर्ण
	अगर (!dev)
		वापस -ENODEV;
	error = __vcc_connect(vcc, dev, vpi, vci);
	अगर (error) अणु
		aपंचांग_dev_put(dev);
		वापस error;
	पूर्ण
	अगर (vpi == ATM_VPI_UNSPEC || vci == ATM_VCI_UNSPEC)
		set_bit(ATM_VF_PARTIAL, &vcc->flags);
	अगर (test_bit(ATM_VF_READY, &ATM_SD(sock)->flags))
		sock->state = SS_CONNECTED;
	वापस 0;
पूर्ण

पूर्णांक vcc_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
		पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा sk_buff *skb;
	पूर्णांक copied, error = -EINVAL;

	अगर (sock->state != SS_CONNECTED)
		वापस -ENOTCONN;

	/* only handle MSG_DONTWAIT and MSG_PEEK */
	अगर (flags & ~(MSG_DONTWAIT | MSG_PEEK))
		वापस -EOPNOTSUPP;

	vcc = ATM_SD(sock);
	अगर (test_bit(ATM_VF_RELEASED, &vcc->flags) ||
	    test_bit(ATM_VF_CLOSE, &vcc->flags) ||
	    !test_bit(ATM_VF_READY, &vcc->flags))
		वापस 0;

	skb = skb_recv_datagram(sk, flags, flags & MSG_DONTWAIT, &error);
	अगर (!skb)
		वापस error;

	copied = skb->len;
	अगर (copied > size) अणु
		copied = size;
		msg->msg_flags |= MSG_TRUNC;
	पूर्ण

	error = skb_copy_datagram_msg(skb, 0, msg, copied);
	अगर (error)
		वापस error;
	sock_recv_ts_and_drops(msg, sk, skb);

	अगर (!(flags & MSG_PEEK)) अणु
		pr_debug("%d -= %d\n", atomic_पढ़ो(&sk->sk_rmem_alloc),
			 skb->truesize);
		aपंचांग_वापस(vcc, skb->truesize);
	पूर्ण

	skb_मुक्त_datagram(sk, skb);
	वापस copied;
पूर्ण

पूर्णांक vcc_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *m, माप_प्रकार size)
अणु
	काष्ठा sock *sk = sock->sk;
	DEFINE_WAIT(रुको);
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा sk_buff *skb;
	पूर्णांक eff, error;

	lock_sock(sk);
	अगर (sock->state != SS_CONNECTED) अणु
		error = -ENOTCONN;
		जाओ out;
	पूर्ण
	अगर (m->msg_name) अणु
		error = -EISCONN;
		जाओ out;
	पूर्ण
	vcc = ATM_SD(sock);
	अगर (test_bit(ATM_VF_RELEASED, &vcc->flags) ||
	    test_bit(ATM_VF_CLOSE, &vcc->flags) ||
	    !test_bit(ATM_VF_READY, &vcc->flags)) अणु
		error = -EPIPE;
		send_sig(SIGPIPE, current, 0);
		जाओ out;
	पूर्ण
	अगर (!size) अणु
		error = 0;
		जाओ out;
	पूर्ण
	अगर (size > vcc->qos.txtp.max_sdu) अणु
		error = -EMSGSIZE;
		जाओ out;
	पूर्ण

	eff = (size+3) & ~3; /* align to word boundary */
	prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
	error = 0;
	जबतक (!vcc_tx_पढ़ोy(vcc, eff)) अणु
		अगर (m->msg_flags & MSG_DONTWAIT) अणु
			error = -EAGAIN;
			अवरोध;
		पूर्ण
		schedule();
		अगर (संकेत_pending(current)) अणु
			error = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		अगर (test_bit(ATM_VF_RELEASED, &vcc->flags) ||
		    test_bit(ATM_VF_CLOSE, &vcc->flags) ||
		    !test_bit(ATM_VF_READY, &vcc->flags)) अणु
			error = -EPIPE;
			send_sig(SIGPIPE, current, 0);
			अवरोध;
		पूर्ण
		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
	पूर्ण
	finish_रुको(sk_sleep(sk), &रुको);
	अगर (error)
		जाओ out;

	skb = alloc_skb(eff, GFP_KERNEL);
	अगर (!skb) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण
	pr_debug("%d += %d\n", sk_wmem_alloc_get(sk), skb->truesize);
	aपंचांग_account_tx(vcc, skb);

	skb->dev = शून्य; /* क्रम paths shared with net_device पूर्णांकerfaces */
	अगर (!copy_from_iter_full(skb_put(skb, size), size, &m->msg_iter)) अणु
		kमुक्त_skb(skb);
		error = -EFAULT;
		जाओ out;
	पूर्ण
	अगर (eff != size)
		स_रखो(skb->data + size, 0, eff-size);
	error = vcc->dev->ops->send(vcc, skb);
	error = error ? error : size;
out:
	release_sock(sk);
	वापस error;
पूर्ण

__poll_t vcc_poll(काष्ठा file *file, काष्ठा socket *sock, poll_table *रुको)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा aपंचांग_vcc *vcc;
	__poll_t mask;

	sock_poll_रुको(file, sock, रुको);
	mask = 0;

	vcc = ATM_SD(sock);

	/* exceptional events */
	अगर (sk->sk_err)
		mask = EPOLLERR;

	अगर (test_bit(ATM_VF_RELEASED, &vcc->flags) ||
	    test_bit(ATM_VF_CLOSE, &vcc->flags))
		mask |= EPOLLHUP;

	/* पढ़ोable? */
	अगर (!skb_queue_empty_lockless(&sk->sk_receive_queue))
		mask |= EPOLLIN | EPOLLRDNORM;

	/* writable? */
	अगर (sock->state == SS_CONNECTING &&
	    test_bit(ATM_VF_WAITING, &vcc->flags))
		वापस mask;

	अगर (vcc->qos.txtp.traffic_class != ATM_NONE &&
	    vcc_writable(sk))
		mask |= EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND;

	वापस mask;
पूर्ण

अटल पूर्णांक aपंचांग_change_qos(काष्ठा aपंचांग_vcc *vcc, काष्ठा aपंचांग_qos *qos)
अणु
	पूर्णांक error;

	/*
	 * Don't let the QoS change the alपढ़ोy connected AAL type nor the
	 * traffic class.
	 */
	अगर (qos->aal != vcc->qos.aal ||
	    qos->rxtp.traffic_class != vcc->qos.rxtp.traffic_class ||
	    qos->txtp.traffic_class != vcc->qos.txtp.traffic_class)
		वापस -EINVAL;
	error = adjust_tp(&qos->txtp, qos->aal);
	अगर (!error)
		error = adjust_tp(&qos->rxtp, qos->aal);
	अगर (error)
		वापस error;
	अगर (!vcc->dev->ops->change_qos)
		वापस -EOPNOTSUPP;
	अगर (sk_aपंचांग(vcc)->sk_family == AF_ATMPVC)
		वापस vcc->dev->ops->change_qos(vcc, qos, ATM_MF_SET);
	वापस svc_change_qos(vcc, qos);
पूर्ण

अटल पूर्णांक check_tp(स्थिर काष्ठा aपंचांग_trafprm *tp)
अणु
	/* @@@ Should be merged with adjust_tp */
	अगर (!tp->traffic_class || tp->traffic_class == ATM_ANYCLASS)
		वापस 0;
	अगर (tp->traffic_class != ATM_UBR && !tp->min_pcr && !tp->pcr &&
	    !tp->max_pcr)
		वापस -EINVAL;
	अगर (tp->min_pcr == ATM_MAX_PCR)
		वापस -EINVAL;
	अगर (tp->min_pcr && tp->max_pcr && tp->max_pcr != ATM_MAX_PCR &&
	    tp->min_pcr > tp->max_pcr)
		वापस -EINVAL;
	/*
	 * We allow pcr to be outside [min_pcr,max_pcr], because later
	 * adjusपंचांगent may still push it in the valid range.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक check_qos(स्थिर काष्ठा aपंचांग_qos *qos)
अणु
	पूर्णांक error;

	अगर (!qos->txtp.traffic_class && !qos->rxtp.traffic_class)
		वापस -EINVAL;
	अगर (qos->txtp.traffic_class != qos->rxtp.traffic_class &&
	    qos->txtp.traffic_class && qos->rxtp.traffic_class &&
	    qos->txtp.traffic_class != ATM_ANYCLASS &&
	    qos->rxtp.traffic_class != ATM_ANYCLASS)
		वापस -EINVAL;
	error = check_tp(&qos->txtp);
	अगर (error)
		वापस error;
	वापस check_tp(&qos->rxtp);
पूर्ण

पूर्णांक vcc_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
		   sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा aपंचांग_vcc *vcc;
	अचिन्हित दीर्घ value;
	पूर्णांक error;

	अगर (__SO_LEVEL_MATCH(optname, level) && optlen != __SO_SIZE(optname))
		वापस -EINVAL;

	vcc = ATM_SD(sock);
	चयन (optname) अणु
	हाल SO_ATMQOS:
	अणु
		काष्ठा aपंचांग_qos qos;

		अगर (copy_from_sockptr(&qos, optval, माप(qos)))
			वापस -EFAULT;
		error = check_qos(&qos);
		अगर (error)
			वापस error;
		अगर (sock->state == SS_CONNECTED)
			वापस aपंचांग_change_qos(vcc, &qos);
		अगर (sock->state != SS_UNCONNECTED)
			वापस -EBADFD;
		vcc->qos = qos;
		set_bit(ATM_VF_HASQOS, &vcc->flags);
		वापस 0;
	पूर्ण
	हाल SO_SETCLP:
		अगर (copy_from_sockptr(&value, optval, माप(value)))
			वापस -EFAULT;
		अगर (value)
			vcc->aपंचांग_options |= ATM_ATMOPT_CLP;
		अन्यथा
			vcc->aपंचांग_options &= ~ATM_ATMOPT_CLP;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक vcc_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
		   अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा aपंचांग_vcc *vcc;
	पूर्णांक len;

	अगर (get_user(len, optlen))
		वापस -EFAULT;
	अगर (__SO_LEVEL_MATCH(optname, level) && len != __SO_SIZE(optname))
		वापस -EINVAL;

	vcc = ATM_SD(sock);
	चयन (optname) अणु
	हाल SO_ATMQOS:
		अगर (!test_bit(ATM_VF_HASQOS, &vcc->flags))
			वापस -EINVAL;
		वापस copy_to_user(optval, &vcc->qos, माप(vcc->qos))
			? -EFAULT : 0;
	हाल SO_SETCLP:
		वापस put_user(vcc->aपंचांग_options & ATM_ATMOPT_CLP ? 1 : 0,
				(अचिन्हित दीर्घ __user *)optval) ? -EFAULT : 0;
	हाल SO_ATMPVC:
	अणु
		काष्ठा sockaddr_aपंचांगpvc pvc;

		अगर (!vcc->dev || !test_bit(ATM_VF_ADDR, &vcc->flags))
			वापस -ENOTCONN;
		स_रखो(&pvc, 0, माप(pvc));
		pvc.sap_family = AF_ATMPVC;
		pvc.sap_addr.itf = vcc->dev->number;
		pvc.sap_addr.vpi = vcc->vpi;
		pvc.sap_addr.vci = vcc->vci;
		वापस copy_to_user(optval, &pvc, माप(pvc)) ? -EFAULT : 0;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक रेजिस्टर_aपंचांगdevice_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&aपंचांग_dev_notअगरy_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_aपंचांगdevice_notअगरier);

व्योम unरेजिस्टर_aपंचांगdevice_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	atomic_notअगरier_chain_unरेजिस्टर(&aपंचांग_dev_notअगरy_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_aपंचांगdevice_notअगरier);

अटल पूर्णांक __init aपंचांग_init(व्योम)
अणु
	पूर्णांक error;

	error = proto_रेजिस्टर(&vcc_proto, 0);
	अगर (error < 0)
		जाओ out;
	error = aपंचांगpvc_init();
	अगर (error < 0) अणु
		pr_err("atmpvc_init() failed with %d\n", error);
		जाओ out_unरेजिस्टर_vcc_proto;
	पूर्ण
	error = aपंचांगsvc_init();
	अगर (error < 0) अणु
		pr_err("atmsvc_init() failed with %d\n", error);
		जाओ out_aपंचांगpvc_निकास;
	पूर्ण
	error = aपंचांग_proc_init();
	अगर (error < 0) अणु
		pr_err("atm_proc_init() failed with %d\n", error);
		जाओ out_aपंचांगsvc_निकास;
	पूर्ण
	error = aपंचांग_sysfs_init();
	अगर (error < 0) अणु
		pr_err("atm_sysfs_init() failed with %d\n", error);
		जाओ out_aपंचांगproc_निकास;
	पूर्ण
out:
	वापस error;
out_aपंचांगproc_निकास:
	aपंचांग_proc_निकास();
out_aपंचांगsvc_निकास:
	aपंचांगsvc_निकास();
out_aपंचांगpvc_निकास:
	aपंचांगsvc_निकास();
out_unरेजिस्टर_vcc_proto:
	proto_unरेजिस्टर(&vcc_proto);
	जाओ out;
पूर्ण

अटल व्योम __निकास aपंचांग_निकास(व्योम)
अणु
	aपंचांग_proc_निकास();
	aपंचांग_sysfs_निकास();
	aपंचांगsvc_निकास();
	aपंचांगpvc_निकास();
	proto_unरेजिस्टर(&vcc_proto);
पूर्ण

subsys_initcall(aपंचांग_init);

module_निकास(aपंचांग_निकास);

MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_ATMPVC);
MODULE_ALIAS_NETPROTO(PF_ATMSVC);
