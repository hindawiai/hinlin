<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* net/aपंचांग/svc.c - ATM SVC sockets */

/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/माला.स>
#समावेश <linux/net.h>		/* काष्ठा socket, काष्ठा proto_ops */
#समावेश <linux/त्रुटिसं.स>	/* error codes */
#समावेश <linux/kernel.h>	/* prपूर्णांकk */
#समावेश <linux/skbuff.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/fcntl.h>	/* O_NONBLOCK */
#समावेश <linux/init.h>
#समावेश <linux/aपंचांग.h>		/* ATM stuff */
#समावेश <linux/aपंचांगsap.h>
#समावेश <linux/aपंचांगsvc.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/bitops.h>
#समावेश <net/sock.h>		/* क्रम sock_no_* */
#समावेश <linux/uaccess.h>
#समावेश <linux/export.h>

#समावेश "resources.h"
#समावेश "common.h"		/* common क्रम PVCs and SVCs */
#समावेश "signaling.h"
#समावेश "addr.h"

अटल पूर्णांक svc_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
		      पूर्णांक kern);

/*
 * Note: since all this is still nicely synchronized with the संकेतing demon,
 *       there's no need to protect sleep loops with clis. If संकेतing is
 *       moved पूर्णांकo the kernel, that would change.
 */


अटल पूर्णांक svc_shutकरोwn(काष्ठा socket *sock, पूर्णांक how)
अणु
	वापस 0;
पूर्ण

अटल व्योम svc_disconnect(काष्ठा aपंचांग_vcc *vcc)
अणु
	DEFINE_WAIT(रुको);
	काष्ठा sk_buff *skb;
	काष्ठा sock *sk = sk_aपंचांग(vcc);

	pr_debug("%p\n", vcc);
	अगर (test_bit(ATM_VF_REGIS, &vcc->flags)) अणु
		sigd_enq(vcc, as_बंद, शून्य, शून्य, शून्य);
		क्रम (;;) अणु
			prepare_to_रुको(sk_sleep(sk), &रुको, TASK_UNINTERRUPTIBLE);
			अगर (test_bit(ATM_VF_RELEASED, &vcc->flags) || !sigd)
				अवरोध;
			schedule();
		पूर्ण
		finish_रुको(sk_sleep(sk), &रुको);
	पूर्ण
	/* beware - socket is still in use by aपंचांगsigd until the last
	   as_indicate has been answered */
	जबतक ((skb = skb_dequeue(&sk->sk_receive_queue)) != शून्य) अणु
		aपंचांग_वापस(vcc, skb->truesize);
		pr_debug("LISTEN REL\n");
		sigd_enq2(शून्य, as_reject, vcc, शून्य, शून्य, &vcc->qos, 0);
		dev_kमुक्त_skb(skb);
	पूर्ण
	clear_bit(ATM_VF_REGIS, &vcc->flags);
	/* ... may retry later */
पूर्ण

अटल पूर्णांक svc_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा aपंचांग_vcc *vcc;

	अगर (sk) अणु
		vcc = ATM_SD(sock);
		pr_debug("%p\n", vcc);
		clear_bit(ATM_VF_READY, &vcc->flags);
		/*
		 * VCC poपूर्णांकer is used as a reference,
		 * so we must not मुक्त it (thereby subjecting it to re-use)
		 * beक्रमe all pending connections are बंदd
		 */
		svc_disconnect(vcc);
		vcc_release(sock);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक svc_bind(काष्ठा socket *sock, काष्ठा sockaddr *sockaddr,
		    पूर्णांक sockaddr_len)
अणु
	DEFINE_WAIT(रुको);
	काष्ठा sock *sk = sock->sk;
	काष्ठा sockaddr_aपंचांगsvc *addr;
	काष्ठा aपंचांग_vcc *vcc;
	पूर्णांक error;

	अगर (sockaddr_len != माप(काष्ठा sockaddr_aपंचांगsvc))
		वापस -EINVAL;
	lock_sock(sk);
	अगर (sock->state == SS_CONNECTED) अणु
		error = -EISCONN;
		जाओ out;
	पूर्ण
	अगर (sock->state != SS_UNCONNECTED) अणु
		error = -EINVAL;
		जाओ out;
	पूर्ण
	vcc = ATM_SD(sock);
	addr = (काष्ठा sockaddr_aपंचांगsvc *) sockaddr;
	अगर (addr->sas_family != AF_ATMSVC) अणु
		error = -EAFNOSUPPORT;
		जाओ out;
	पूर्ण
	clear_bit(ATM_VF_BOUND, &vcc->flags);
	    /* failing rebind will समाप्त old binding */
	/* @@@ check memory (de)allocation on rebind */
	अगर (!test_bit(ATM_VF_HASQOS, &vcc->flags)) अणु
		error = -EBADFD;
		जाओ out;
	पूर्ण
	vcc->local = *addr;
	set_bit(ATM_VF_WAITING, &vcc->flags);
	sigd_enq(vcc, as_bind, शून्य, शून्य, &vcc->local);
	क्रम (;;) अणु
		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_UNINTERRUPTIBLE);
		अगर (!test_bit(ATM_VF_WAITING, &vcc->flags) || !sigd)
			अवरोध;
		schedule();
	पूर्ण
	finish_रुको(sk_sleep(sk), &रुको);
	clear_bit(ATM_VF_REGIS, &vcc->flags); /* करोesn't count */
	अगर (!sigd) अणु
		error = -EUNATCH;
		जाओ out;
	पूर्ण
	अगर (!sk->sk_err)
		set_bit(ATM_VF_BOUND, &vcc->flags);
	error = -sk->sk_err;
out:
	release_sock(sk);
	वापस error;
पूर्ण

अटल पूर्णांक svc_connect(काष्ठा socket *sock, काष्ठा sockaddr *sockaddr,
		       पूर्णांक sockaddr_len, पूर्णांक flags)
अणु
	DEFINE_WAIT(रुको);
	काष्ठा sock *sk = sock->sk;
	काष्ठा sockaddr_aपंचांगsvc *addr;
	काष्ठा aपंचांग_vcc *vcc = ATM_SD(sock);
	पूर्णांक error;

	pr_debug("%p\n", vcc);
	lock_sock(sk);
	अगर (sockaddr_len != माप(काष्ठा sockaddr_aपंचांगsvc)) अणु
		error = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (sock->state) अणु
	शेष:
		error = -EINVAL;
		जाओ out;
	हाल SS_CONNECTED:
		error = -EISCONN;
		जाओ out;
	हाल SS_CONNECTING:
		अगर (test_bit(ATM_VF_WAITING, &vcc->flags)) अणु
			error = -EALREADY;
			जाओ out;
		पूर्ण
		sock->state = SS_UNCONNECTED;
		अगर (sk->sk_err) अणु
			error = -sk->sk_err;
			जाओ out;
		पूर्ण
		अवरोध;
	हाल SS_UNCONNECTED:
		addr = (काष्ठा sockaddr_aपंचांगsvc *) sockaddr;
		अगर (addr->sas_family != AF_ATMSVC) अणु
			error = -EAFNOSUPPORT;
			जाओ out;
		पूर्ण
		अगर (!test_bit(ATM_VF_HASQOS, &vcc->flags)) अणु
			error = -EBADFD;
			जाओ out;
		पूर्ण
		अगर (vcc->qos.txtp.traffic_class == ATM_ANYCLASS ||
		    vcc->qos.rxtp.traffic_class == ATM_ANYCLASS) अणु
			error = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (!vcc->qos.txtp.traffic_class &&
		    !vcc->qos.rxtp.traffic_class) अणु
			error = -EINVAL;
			जाओ out;
		पूर्ण
		vcc->remote = *addr;
		set_bit(ATM_VF_WAITING, &vcc->flags);
		sigd_enq(vcc, as_connect, शून्य, शून्य, &vcc->remote);
		अगर (flags & O_NONBLOCK) अणु
			sock->state = SS_CONNECTING;
			error = -EINPROGRESS;
			जाओ out;
		पूर्ण
		error = 0;
		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
		जबतक (test_bit(ATM_VF_WAITING, &vcc->flags) && sigd) अणु
			schedule();
			अगर (!संकेत_pending(current)) अणु
				prepare_to_रुको(sk_sleep(sk), &रुको,
						TASK_INTERRUPTIBLE);
				जारी;
			पूर्ण
			pr_debug("*ABORT*\n");
			/*
			 * This is tricky:
			 *   Kernel ---बंद--> Demon
			 *   Kernel <--बंद--- Demon
			 * or
			 *   Kernel ---बंद--> Demon
			 *   Kernel <--error--- Demon
			 * or
			 *   Kernel ---बंद--> Demon
			 *   Kernel <--okay---- Demon
			 *   Kernel <--बंद--- Demon
			 */
			sigd_enq(vcc, as_बंद, शून्य, शून्य, शून्य);
			जबतक (test_bit(ATM_VF_WAITING, &vcc->flags) && sigd) अणु
				prepare_to_रुको(sk_sleep(sk), &रुको,
						TASK_INTERRUPTIBLE);
				schedule();
			पूर्ण
			अगर (!sk->sk_err)
				जबतक (!test_bit(ATM_VF_RELEASED, &vcc->flags) &&
				       sigd) अणु
					prepare_to_रुको(sk_sleep(sk), &रुको,
							TASK_INTERRUPTIBLE);
					schedule();
				पूर्ण
			clear_bit(ATM_VF_REGIS, &vcc->flags);
			clear_bit(ATM_VF_RELEASED, &vcc->flags);
			clear_bit(ATM_VF_CLOSE, &vcc->flags);
			    /* we're gone now but may connect later */
			error = -EINTR;
			अवरोध;
		पूर्ण
		finish_रुको(sk_sleep(sk), &रुको);
		अगर (error)
			जाओ out;
		अगर (!sigd) अणु
			error = -EUNATCH;
			जाओ out;
		पूर्ण
		अगर (sk->sk_err) अणु
			error = -sk->sk_err;
			जाओ out;
		पूर्ण
	पूर्ण

	vcc->qos.txtp.max_pcr = SELECT_TOP_PCR(vcc->qos.txtp);
	vcc->qos.txtp.pcr = 0;
	vcc->qos.txtp.min_pcr = 0;

	error = vcc_connect(sock, vcc->itf, vcc->vpi, vcc->vci);
	अगर (!error)
		sock->state = SS_CONNECTED;
	अन्यथा
		(व्योम)svc_disconnect(vcc);
out:
	release_sock(sk);
	वापस error;
पूर्ण

अटल पूर्णांक svc_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	DEFINE_WAIT(रुको);
	काष्ठा sock *sk = sock->sk;
	काष्ठा aपंचांग_vcc *vcc = ATM_SD(sock);
	पूर्णांक error;

	pr_debug("%p\n", vcc);
	lock_sock(sk);
	/* let server handle listen on unbound sockets */
	अगर (test_bit(ATM_VF_SESSION, &vcc->flags)) अणु
		error = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (test_bit(ATM_VF_LISTEN, &vcc->flags)) अणु
		error = -EADDRINUSE;
		जाओ out;
	पूर्ण
	set_bit(ATM_VF_WAITING, &vcc->flags);
	sigd_enq(vcc, as_listen, शून्य, शून्य, &vcc->local);
	क्रम (;;) अणु
		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_UNINTERRUPTIBLE);
		अगर (!test_bit(ATM_VF_WAITING, &vcc->flags) || !sigd)
			अवरोध;
		schedule();
	पूर्ण
	finish_रुको(sk_sleep(sk), &रुको);
	अगर (!sigd) अणु
		error = -EUNATCH;
		जाओ out;
	पूर्ण
	set_bit(ATM_VF_LISTEN, &vcc->flags);
	vcc_insert_socket(sk);
	sk->sk_max_ack_backlog = backlog > 0 ? backlog : ATM_BACKLOG_DEFAULT;
	error = -sk->sk_err;
out:
	release_sock(sk);
	वापस error;
पूर्ण

अटल पूर्णांक svc_accept(काष्ठा socket *sock, काष्ठा socket *newsock, पूर्णांक flags,
		      bool kern)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb;
	काष्ठा aपंचांगsvc_msg *msg;
	काष्ठा aपंचांग_vcc *old_vcc = ATM_SD(sock);
	काष्ठा aपंचांग_vcc *new_vcc;
	पूर्णांक error;

	lock_sock(sk);

	error = svc_create(sock_net(sk), newsock, 0, kern);
	अगर (error)
		जाओ out;

	new_vcc = ATM_SD(newsock);

	pr_debug("%p -> %p\n", old_vcc, new_vcc);
	जबतक (1) अणु
		DEFINE_WAIT(रुको);

		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
		जबतक (!(skb = skb_dequeue(&sk->sk_receive_queue)) &&
		       sigd) अणु
			अगर (test_bit(ATM_VF_RELEASED, &old_vcc->flags))
				अवरोध;
			अगर (test_bit(ATM_VF_CLOSE, &old_vcc->flags)) अणु
				error = -sk->sk_err;
				अवरोध;
			पूर्ण
			अगर (flags & O_NONBLOCK) अणु
				error = -EAGAIN;
				अवरोध;
			पूर्ण
			release_sock(sk);
			schedule();
			lock_sock(sk);
			अगर (संकेत_pending(current)) अणु
				error = -ERESTARTSYS;
				अवरोध;
			पूर्ण
			prepare_to_रुको(sk_sleep(sk), &रुको,
					TASK_INTERRUPTIBLE);
		पूर्ण
		finish_रुको(sk_sleep(sk), &रुको);
		अगर (error)
			जाओ out;
		अगर (!skb) अणु
			error = -EUNATCH;
			जाओ out;
		पूर्ण
		msg = (काष्ठा aपंचांगsvc_msg *)skb->data;
		new_vcc->qos = msg->qos;
		set_bit(ATM_VF_HASQOS, &new_vcc->flags);
		new_vcc->remote = msg->svc;
		new_vcc->local = msg->local;
		new_vcc->sap = msg->sap;
		error = vcc_connect(newsock, msg->pvc.sap_addr.itf,
				    msg->pvc.sap_addr.vpi,
				    msg->pvc.sap_addr.vci);
		dev_kमुक्त_skb(skb);
		sk_acceptq_हटाओd(sk);
		अगर (error) अणु
			sigd_enq2(शून्य, as_reject, old_vcc, शून्य, शून्य,
				  &old_vcc->qos, error);
			error = error == -EAGAIN ? -EBUSY : error;
			जाओ out;
		पूर्ण
		/* रुको should be लघु, so we ignore the non-blocking flag */
		set_bit(ATM_VF_WAITING, &new_vcc->flags);
		sigd_enq(new_vcc, as_accept, old_vcc, शून्य, शून्य);
		क्रम (;;) अणु
			prepare_to_रुको(sk_sleep(sk_aपंचांग(new_vcc)), &रुको,
					TASK_UNINTERRUPTIBLE);
			अगर (!test_bit(ATM_VF_WAITING, &new_vcc->flags) || !sigd)
				अवरोध;
			release_sock(sk);
			schedule();
			lock_sock(sk);
		पूर्ण
		finish_रुको(sk_sleep(sk_aपंचांग(new_vcc)), &रुको);
		अगर (!sigd) अणु
			error = -EUNATCH;
			जाओ out;
		पूर्ण
		अगर (!sk_aपंचांग(new_vcc)->sk_err)
			अवरोध;
		अगर (sk_aपंचांग(new_vcc)->sk_err != ERESTARTSYS) अणु
			error = -sk_aपंचांग(new_vcc)->sk_err;
			जाओ out;
		पूर्ण
	पूर्ण
	newsock->state = SS_CONNECTED;
out:
	release_sock(sk);
	वापस error;
पूर्ण

अटल पूर्णांक svc_getname(काष्ठा socket *sock, काष्ठा sockaddr *sockaddr,
		       पूर्णांक peer)
अणु
	काष्ठा sockaddr_aपंचांगsvc *addr;

	addr = (काष्ठा sockaddr_aपंचांगsvc *) sockaddr;
	स_नकल(addr, peer ? &ATM_SD(sock)->remote : &ATM_SD(sock)->local,
	       माप(काष्ठा sockaddr_aपंचांगsvc));
	वापस माप(काष्ठा sockaddr_aपंचांगsvc);
पूर्ण

पूर्णांक svc_change_qos(काष्ठा aपंचांग_vcc *vcc, काष्ठा aपंचांग_qos *qos)
अणु
	काष्ठा sock *sk = sk_aपंचांग(vcc);
	DEFINE_WAIT(रुको);

	set_bit(ATM_VF_WAITING, &vcc->flags);
	sigd_enq2(vcc, as_modअगरy, शून्य, शून्य, &vcc->local, qos, 0);
	क्रम (;;) अणु
		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_UNINTERRUPTIBLE);
		अगर (!test_bit(ATM_VF_WAITING, &vcc->flags) ||
		    test_bit(ATM_VF_RELEASED, &vcc->flags) || !sigd) अणु
			अवरोध;
		पूर्ण
		schedule();
	पूर्ण
	finish_रुको(sk_sleep(sk), &रुको);
	अगर (!sigd)
		वापस -EUNATCH;
	वापस -sk->sk_err;
पूर्ण

अटल पूर्णांक svc_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			  sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा aपंचांग_vcc *vcc = ATM_SD(sock);
	पूर्णांक value, error = 0;

	lock_sock(sk);
	चयन (optname) अणु
	हाल SO_ATMSAP:
		अगर (level != SOL_ATM || optlen != माप(काष्ठा aपंचांग_sap)) अणु
			error = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (copy_from_sockptr(&vcc->sap, optval, optlen)) अणु
			error = -EFAULT;
			जाओ out;
		पूर्ण
		set_bit(ATM_VF_HASSAP, &vcc->flags);
		अवरोध;
	हाल SO_MULTIPOINT:
		अगर (level != SOL_ATM || optlen != माप(पूर्णांक)) अणु
			error = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (copy_from_sockptr(&value, optval, माप(पूर्णांक))) अणु
			error = -EFAULT;
			जाओ out;
		पूर्ण
		अगर (value == 1)
			set_bit(ATM_VF_SESSION, &vcc->flags);
		अन्यथा अगर (value == 0)
			clear_bit(ATM_VF_SESSION, &vcc->flags);
		अन्यथा
			error = -EINVAL;
		अवरोध;
	शेष:
		error = vcc_setsockopt(sock, level, optname, optval, optlen);
	पूर्ण

out:
	release_sock(sk);
	वापस error;
पूर्ण

अटल पूर्णांक svc_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			  अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक error = 0, len;

	lock_sock(sk);
	अगर (!__SO_LEVEL_MATCH(optname, level) || optname != SO_ATMSAP) अणु
		error = vcc_माला_लोockopt(sock, level, optname, optval, optlen);
		जाओ out;
	पूर्ण
	अगर (get_user(len, optlen)) अणु
		error = -EFAULT;
		जाओ out;
	पूर्ण
	अगर (len != माप(काष्ठा aपंचांग_sap)) अणु
		error = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (copy_to_user(optval, &ATM_SD(sock)->sap, माप(काष्ठा aपंचांग_sap))) अणु
		error = -EFAULT;
		जाओ out;
	पूर्ण
out:
	release_sock(sk);
	वापस error;
पूर्ण

अटल पूर्णांक svc_addparty(काष्ठा socket *sock, काष्ठा sockaddr *sockaddr,
			पूर्णांक sockaddr_len, पूर्णांक flags)
अणु
	DEFINE_WAIT(रुको);
	काष्ठा sock *sk = sock->sk;
	काष्ठा aपंचांग_vcc *vcc = ATM_SD(sock);
	पूर्णांक error;

	lock_sock(sk);
	set_bit(ATM_VF_WAITING, &vcc->flags);
	sigd_enq(vcc, as_addparty, शून्य, शून्य,
		 (काष्ठा sockaddr_aपंचांगsvc *) sockaddr);
	अगर (flags & O_NONBLOCK) अणु
		error = -EINPROGRESS;
		जाओ out;
	पूर्ण
	pr_debug("added wait queue\n");
	क्रम (;;) अणु
		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
		अगर (!test_bit(ATM_VF_WAITING, &vcc->flags) || !sigd)
			अवरोध;
		schedule();
	पूर्ण
	finish_रुको(sk_sleep(sk), &रुको);
	error = -xchg(&sk->sk_err_soft, 0);
out:
	release_sock(sk);
	वापस error;
पूर्ण

अटल पूर्णांक svc_dropparty(काष्ठा socket *sock, पूर्णांक ep_ref)
अणु
	DEFINE_WAIT(रुको);
	काष्ठा sock *sk = sock->sk;
	काष्ठा aपंचांग_vcc *vcc = ATM_SD(sock);
	पूर्णांक error;

	lock_sock(sk);
	set_bit(ATM_VF_WAITING, &vcc->flags);
	sigd_enq2(vcc, as_dropparty, शून्य, शून्य, शून्य, शून्य, ep_ref);
	क्रम (;;) अणु
		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
		अगर (!test_bit(ATM_VF_WAITING, &vcc->flags) || !sigd)
			अवरोध;
		schedule();
	पूर्ण
	finish_रुको(sk_sleep(sk), &रुको);
	अगर (!sigd) अणु
		error = -EUNATCH;
		जाओ out;
	पूर्ण
	error = -xchg(&sk->sk_err_soft, 0);
out:
	release_sock(sk);
	वापस error;
पूर्ण

अटल पूर्णांक svc_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक error, ep_ref;
	काष्ठा sockaddr_aपंचांगsvc sa;
	काष्ठा aपंचांग_vcc *vcc = ATM_SD(sock);

	चयन (cmd) अणु
	हाल ATM_ADDPARTY:
		अगर (!test_bit(ATM_VF_SESSION, &vcc->flags))
			वापस -EINVAL;
		अगर (copy_from_user(&sa, (व्योम __user *) arg, माप(sa)))
			वापस -EFAULT;
		error = svc_addparty(sock, (काष्ठा sockaddr *)&sa, माप(sa),
				     0);
		अवरोध;
	हाल ATM_DROPPARTY:
		अगर (!test_bit(ATM_VF_SESSION, &vcc->flags))
			वापस -EINVAL;
		अगर (copy_from_user(&ep_ref, (व्योम __user *) arg, माप(पूर्णांक)))
			वापस -EFAULT;
		error = svc_dropparty(sock, ep_ref);
		अवरोध;
	शेष:
		error = vcc_ioctl(sock, cmd, arg);
	पूर्ण

	वापस error;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक svc_compat_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg)
अणु
	/* The definition of ATM_ADDPARTY uses the size of काष्ठा aपंचांग_iobuf.
	   But actually it takes a काष्ठा sockaddr_aपंचांगsvc, which करोesn't need
	   compat handling. So all we have to करो is fix up cmd... */
	अगर (cmd == COMPAT_ATM_ADDPARTY)
		cmd = ATM_ADDPARTY;

	अगर (cmd == ATM_ADDPARTY || cmd == ATM_DROPPARTY)
		वापस svc_ioctl(sock, cmd, arg);
	अन्यथा
		वापस vcc_compat_ioctl(sock, cmd, arg);
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

अटल स्थिर काष्ठा proto_ops svc_proto_ops = अणु
	.family =	PF_ATMSVC,
	.owner =	THIS_MODULE,

	.release =	svc_release,
	.bind =		svc_bind,
	.connect =	svc_connect,
	.socketpair =	sock_no_socketpair,
	.accept =	svc_accept,
	.getname =	svc_getname,
	.poll =		vcc_poll,
	.ioctl =	svc_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl =	svc_compat_ioctl,
#पूर्ण_अगर
	.gettstamp =	sock_gettstamp,
	.listen =	svc_listen,
	.shutकरोwn =	svc_shutकरोwn,
	.setsockopt =	svc_setsockopt,
	.माला_लोockopt =	svc_माला_लोockopt,
	.sendmsg =	vcc_sendmsg,
	.recvmsg =	vcc_recvmsg,
	.mmap =		sock_no_mmap,
	.sendpage =	sock_no_sendpage,
पूर्ण;


अटल पूर्णांक svc_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
		      पूर्णांक kern)
अणु
	पूर्णांक error;

	अगर (!net_eq(net, &init_net))
		वापस -EAFNOSUPPORT;

	sock->ops = &svc_proto_ops;
	error = vcc_create(net, sock, protocol, AF_ATMSVC, kern);
	अगर (error)
		वापस error;
	ATM_SD(sock)->local.sas_family = AF_ATMSVC;
	ATM_SD(sock)->remote.sas_family = AF_ATMSVC;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_proto_family svc_family_ops = अणु
	.family = PF_ATMSVC,
	.create = svc_create,
	.owner = THIS_MODULE,
पूर्ण;


/*
 *	Initialize the ATM SVC protocol family
 */

पूर्णांक __init aपंचांगsvc_init(व्योम)
अणु
	वापस sock_रेजिस्टर(&svc_family_ops);
पूर्ण

व्योम aपंचांगsvc_निकास(व्योम)
अणु
	sock_unरेजिस्टर(PF_ATMSVC);
पूर्ण
