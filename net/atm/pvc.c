<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* net/aपंचांग/pvc.c - ATM PVC sockets */

/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */


#समावेश <linux/net.h>		/* काष्ठा socket, काष्ठा proto_ops */
#समावेश <linux/aपंचांग.h>		/* ATM stuff */
#समावेश <linux/aपंचांगdev.h>	/* ATM devices */
#समावेश <linux/त्रुटिसं.स>	/* error codes */
#समावेश <linux/kernel.h>	/* prपूर्णांकk */
#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/bitops.h>
#समावेश <linux/export.h>
#समावेश <net/sock.h>		/* क्रम sock_no_* */

#समावेश "resources.h"		/* devs and vccs */
#समावेश "common.h"		/* common क्रम PVCs and SVCs */


अटल पूर्णांक pvc_shutकरोwn(काष्ठा socket *sock, पूर्णांक how)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक pvc_bind(काष्ठा socket *sock, काष्ठा sockaddr *sockaddr,
		    पूर्णांक sockaddr_len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sockaddr_aपंचांगpvc *addr;
	काष्ठा aपंचांग_vcc *vcc;
	पूर्णांक error;

	अगर (sockaddr_len != माप(काष्ठा sockaddr_aपंचांगpvc))
		वापस -EINVAL;
	addr = (काष्ठा sockaddr_aपंचांगpvc *)sockaddr;
	अगर (addr->sap_family != AF_ATMPVC)
		वापस -EAFNOSUPPORT;
	lock_sock(sk);
	vcc = ATM_SD(sock);
	अगर (!test_bit(ATM_VF_HASQOS, &vcc->flags)) अणु
		error = -EBADFD;
		जाओ out;
	पूर्ण
	अगर (test_bit(ATM_VF_PARTIAL, &vcc->flags)) अणु
		अगर (vcc->vpi != ATM_VPI_UNSPEC)
			addr->sap_addr.vpi = vcc->vpi;
		अगर (vcc->vci != ATM_VCI_UNSPEC)
			addr->sap_addr.vci = vcc->vci;
	पूर्ण
	error = vcc_connect(sock, addr->sap_addr.itf, addr->sap_addr.vpi,
			    addr->sap_addr.vci);
out:
	release_sock(sk);
	वापस error;
पूर्ण

अटल पूर्णांक pvc_connect(काष्ठा socket *sock, काष्ठा sockaddr *sockaddr,
		       पूर्णांक sockaddr_len, पूर्णांक flags)
अणु
	वापस pvc_bind(sock, sockaddr, sockaddr_len);
पूर्ण

अटल पूर्णांक pvc_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			  sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक error;

	lock_sock(sk);
	error = vcc_setsockopt(sock, level, optname, optval, optlen);
	release_sock(sk);
	वापस error;
पूर्ण

अटल पूर्णांक pvc_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			  अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक error;

	lock_sock(sk);
	error = vcc_माला_लोockopt(sock, level, optname, optval, optlen);
	release_sock(sk);
	वापस error;
पूर्ण

अटल पूर्णांक pvc_getname(काष्ठा socket *sock, काष्ठा sockaddr *sockaddr,
		       पूर्णांक peer)
अणु
	काष्ठा sockaddr_aपंचांगpvc *addr;
	काष्ठा aपंचांग_vcc *vcc = ATM_SD(sock);

	अगर (!vcc->dev || !test_bit(ATM_VF_ADDR, &vcc->flags))
		वापस -ENOTCONN;
	addr = (काष्ठा sockaddr_aपंचांगpvc *)sockaddr;
	स_रखो(addr, 0, माप(*addr));
	addr->sap_family = AF_ATMPVC;
	addr->sap_addr.itf = vcc->dev->number;
	addr->sap_addr.vpi = vcc->vpi;
	addr->sap_addr.vci = vcc->vci;
	वापस माप(काष्ठा sockaddr_aपंचांगpvc);
पूर्ण

अटल स्थिर काष्ठा proto_ops pvc_proto_ops = अणु
	.family =	PF_ATMPVC,
	.owner =	THIS_MODULE,

	.release =	vcc_release,
	.bind =		pvc_bind,
	.connect =	pvc_connect,
	.socketpair =	sock_no_socketpair,
	.accept =	sock_no_accept,
	.getname =	pvc_getname,
	.poll =		vcc_poll,
	.ioctl =	vcc_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = vcc_compat_ioctl,
#पूर्ण_अगर
	.gettstamp =	sock_gettstamp,
	.listen =	sock_no_listen,
	.shutकरोwn =	pvc_shutकरोwn,
	.setsockopt =	pvc_setsockopt,
	.माला_लोockopt =	pvc_माला_लोockopt,
	.sendmsg =	vcc_sendmsg,
	.recvmsg =	vcc_recvmsg,
	.mmap =		sock_no_mmap,
	.sendpage =	sock_no_sendpage,
पूर्ण;


अटल पूर्णांक pvc_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
		      पूर्णांक kern)
अणु
	अगर (net != &init_net)
		वापस -EAFNOSUPPORT;

	sock->ops = &pvc_proto_ops;
	वापस vcc_create(net, sock, protocol, PF_ATMPVC, kern);
पूर्ण

अटल स्थिर काष्ठा net_proto_family pvc_family_ops = अणु
	.family = PF_ATMPVC,
	.create = pvc_create,
	.owner = THIS_MODULE,
पूर्ण;


/*
 *	Initialize the ATM PVC protocol family
 */


पूर्णांक __init aपंचांगpvc_init(व्योम)
अणु
	वापस sock_रेजिस्टर(&pvc_family_ops);
पूर्ण

व्योम aपंचांगpvc_निकास(व्योम)
अणु
	sock_unरेजिस्टर(PF_ATMPVC);
पूर्ण
